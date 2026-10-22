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
ಎಣಿಕೆ impl_conv {
  ic_argpass,
  ic_ನಿಯೋಜಿಸು,
  ic_init,
  ic_init_const,
  ic_return
};

/* The level of nesting inside "__alignof__".  */
ಪೂರ್ಣಾಂಕ ಒಳ_alignof;

/* The level of nesting inside "sizeof".  */
ಪೂರ್ಣಾಂಕ ಒಳ_sizeof;

/* The level of nesting inside "countof".  */
ಪೂರ್ಣಾಂಕ ಒಳ_countof;

/* The level of nesting inside "typeof".  */
ಪೂರ್ಣಾಂಕ ಒಳ_typeof;

/* The level of nesting inside "_Generic".  */
ಪೂರ್ಣಾಂಕ ಒಳ_generic;

/* True when parsing OpenMP loop expressions.  */
ತಾರ್ಕಿಕ c_ಒಳ_omp_for;

/* True when parsing OpenMP map clause.  */
ತಾರ್ಕಿಕ c_omp_array_section_p;

/* The argument of last parsed sizeof expression, only to be tested
   if expr.original_code == SIZEOF_EXPR.  */
ವೃಕ್ಷ c_ಕೊನೆಯ_sizeof_arg;
location_t c_ಕೊನೆಯ_sizeof_loc;

/* Nonzero if we might need to print a "missing braces around
   initializer" message within this initializer.  */
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ ಸಿಕ್ಕಿತು_missing_braces;

ಸ್ಥಿರ ತಾರ್ಕಿಕ require_constant_ಮೌಲ್ಯ;
ಸ್ಥಿರ ತಾರ್ಕಿಕ require_constant_elements;
ಸ್ಥಿರ ತಾರ್ಕಿಕ require_constexpr_ಮೌಲ್ಯ;

ಸ್ಥಿರ ವೃಕ್ಷ qualify_type (ವೃಕ್ಷ, ವೃಕ್ಷ);
ರಚನೆ comptypes_ದತ್ತಾಂಶ;
ಸ್ಥಿರ ತಾರ್ಕಿಕ tagged_types_tu_compatible_p (const_ವೃಕ್ಷ, const_ವೃಕ್ಷ,
					  ರಚನೆ comptypes_ದತ್ತಾಂಶ *);
ಸ್ಥಿರ ತಾರ್ಕಿಕ comp_ಗುರಿ_types (location_t, ವೃಕ್ಷ, ವೃಕ್ಷ);
ಸ್ಥಿರ ತಾರ್ಕಿಕ function_types_compatible_p (const_ವೃಕ್ಷ, const_ವೃಕ್ಷ,
					 ರಚನೆ comptypes_ದತ್ತಾಂಶ *);
ಸ್ಥಿರ ತಾರ್ಕಿಕ type_lists_compatible_p (const_ವೃಕ್ಷ, const_ವೃಕ್ಷ,
				     ರಚನೆ comptypes_ದತ್ತಾಂಶ *);
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ convert_arguments (location_t, vec<location_t>, ವೃಕ್ಷ,
			      vec<ವೃಕ್ಷ, va_gc> *, vec<ವೃಕ್ಷ, va_gc> *, ವೃಕ್ಷ,
			      ವೃಕ್ಷ);
ಸ್ಥಿರ ವೃಕ್ಷ ಸೂಚಕ_diff (location_t, ವೃಕ್ಷ, ವೃಕ್ಷ, ವೃಕ್ಷ *);
ಸ್ಥಿರ ವೃಕ್ಷ convert_for_assignment (location_t, location_t, ವೃಕ್ಷ, ವೃಕ್ಷ, ವೃಕ್ಷ,
				    ಎಣಿಕೆ impl_conv, ತಾರ್ಕಿಕ, ವೃಕ್ಷ, ವೃಕ್ಷ, ಪೂರ್ಣಾಂಕ,
				    ಪೂರ್ಣಾಂಕ = 0);
ಸ್ಥಿರ ವೃಕ್ಷ valid_compound_ಅಭಿವ್ಯಕ್ತಿ_initializer (ವೃಕ್ಷ, ವೃಕ್ಷ);
ಸ್ಥಿರ ಶೂನ್ಯ ತಳ್ಳು_string (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *);
ಸ್ಥಿರ ಶೂನ್ಯ ತಳ್ಳು_member_name (ವೃಕ್ಷ);
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ spelling_ಉದ್ದಳತೆ (ಶೂನ್ಯ);
ಸ್ಥಿರ ಅಕ್ಷರ *print_spelling (ಅಕ್ಷರ *);
ಸ್ಥಿರ ಶೂನ್ಯ warning_init (location_t, ಪೂರ್ಣಾಂಕ, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *);
ಸ್ಥಿರ ವೃಕ್ಷ digest_init (location_t, ವೃಕ್ಷ, ವೃಕ್ಷ, ವೃಕ್ಷ, ವೃಕ್ಷ, ತಾರ್ಕಿಕ, ತಾರ್ಕಿಕ, ತಾರ್ಕಿಕ,
			 ತಾರ್ಕಿಕ, ತಾರ್ಕಿಕ, ತಾರ್ಕಿಕ);
ಸ್ಥಿರ ಶೂನ್ಯ output_init_element (location_t, ವೃಕ್ಷ, ವೃಕ್ಷ, ತಾರ್ಕಿಕ, ವೃಕ್ಷ, ವೃಕ್ಷ, ತಾರ್ಕಿಕ,
				 ತಾರ್ಕಿಕ, ರಚನೆ obstack *);
ಸ್ಥಿರ ಶೂನ್ಯ output_pending_init_elements (ಪೂರ್ಣಾಂಕ, ರಚನೆ obstack *);
ಸ್ಥಿರ ತಾರ್ಕಿಕ ಗಣ_designator (location_t, ತಾರ್ಕಿಕ, ರಚನೆ obstack *);
ಸ್ಥಿರ ಶೂನ್ಯ ತಳ್ಳು_range_ರಾಶಿ (ವೃಕ್ಷ, ರಚನೆ obstack *);
ಸ್ಥಿರ ಶೂನ್ಯ ಕೂಡಿಸು_pending_init (location_t, ವೃಕ್ಷ, ವೃಕ್ಷ, ವೃಕ್ಷ, ತಾರ್ಕಿಕ,
			      ರಚನೆ obstack *);
ಸ್ಥಿರ ಶೂನ್ಯ ಗಣ_nonincremental_init (ರಚನೆ obstack *);
ಸ್ಥಿರ ಶೂನ್ಯ ಗಣ_nonincremental_init_from_string (ವೃಕ್ಷ, ರಚನೆ obstack *);
ಸ್ಥಿರ ವೃಕ್ಷ ಕಂಡುಹಿಡಿ_init_member (ವೃಕ್ಷ, ರಚನೆ obstack *);
ಸ್ಥಿರ ಶೂನ್ಯ readonly_warning (ವೃಕ್ಷ, ಎಣಿಕೆ lvalue_use);
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ lvalue_or_else (location_t, const_ವೃಕ್ಷ, ಎಣಿಕೆ lvalue_use);
ಸ್ಥಿರ ಶೂನ್ಯ ದಾಖಲೆ_maybe_ಬಳಸಿದ_decl (ವೃಕ್ಷ, ತಾರ್ಕಿಕ ವಿಳಾಸ);
ಸ್ಥಿರ ತಾರ್ಕಿಕ comptypes_ಆಂತರಿಕ (const_ವೃಕ್ಷ, const_ವೃಕ್ಷ,
				ರಚನೆ comptypes_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ);
ಸ್ಥಿರ ತಾರ್ಕಿಕ comptypes_check_for_ಸಂಯುಕ್ತ (ವೃಕ್ಷ t1, ವೃಕ್ಷ t2);
ಸ್ಥಿರ ತಾರ್ಕಿಕ handle_counted_by_p (ವೃಕ್ಷ);
ಸ್ಥಿರ ತಾರ್ಕಿಕ ತುದಿ_array_vla_p (const_ವೃಕ್ಷ type);


/* Return true if EXP is a null pointer constant, false otherwise.  */

ತಾರ್ಕಿಕ
null_ಸೂಚಕ_constant_p (const_ವೃಕ್ಷ ಅಭಿವ್ಯಕ್ತಿ)
{
  /* This should really operate on c_expr structures, but they aren't
     yet available everywhere required.  */
  ವೃಕ್ಷ type = ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ);

  /* An integer constant expression with the value 0, such an expression
     cast to type void*, or the predefined constant nullptr, are a null
     pointer constant.  */
  ಆದರೆ (ಅಭಿವ್ಯಕ್ತಿ == nullptr_ಗಂಟು)
    ಹಿಂತಿರುಗಿ ನಿಜ;

  ಹಿಂತಿರುಗಿ (ವೃಕ್ಷ_ಸಂಕೇತ (ಅಭಿವ್ಯಕ್ತಿ) == INTEGER_CST
	  && !ವೃಕ್ಷ_ಅತಿಪ್ರವಾಹ (ಅಭಿವ್ಯಕ್ತಿ)
	  && integer_zerop (ಅಭಿವ್ಯಕ್ತಿ)
	  && (INTEGRAL_TYPE_P (type)
	      || (ವೃಕ್ಷ_ಸಂಕೇತ (type) == ಸೂಚಕ_TYPE
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
  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ಅಭಿವ್ಯಕ್ತಿ) == INTEGER_CST && ಒಳ_late_ದ್ವಿಮಾನ_op)
    {
      ret = copy_ಗಂಟು (ಅಭಿವ್ಯಕ್ತಿ);
      ವೃಕ್ಷ_ಅತಿಪ್ರವಾಹ (ret) = 1;
    }
  ಇಲ್ಲದಿದ್ದರೆ
    {
      ret = build2 (C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ), NULL_ವೃಕ್ಷ, ಅಭಿವ್ಯಕ್ತಿ);
      C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ_INT_OPERANDS (ret) = 1;
    }
  ಹಿಂತಿರುಗಿ ret;
}

/* Having checked whether EXPR may appear in an unevaluated part of an
   integer constant expression and found that it may, remove any
   C_MAYBE_CONST_EXPR noting this fact and return the resulting
   expression.  */

ಸ್ಥಿರ ಸಾಲೊಳಗೆ ವೃಕ್ಷ
remove_c_maybe_const_ಅಭಿವ್ಯಕ್ತಿ (ವೃಕ್ಷ ಅಭಿವ್ಯಕ್ತಿ)
{
  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ಅಭಿವ್ಯಕ್ತಿ) == C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ)
    ಹಿಂತಿರುಗಿ C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ_ಅಭಿವ್ಯಕ್ತಿ (ಅಭಿವ್ಯಕ್ತಿ);
  ಇಲ್ಲದಿದ್ದರೆ
    ಹಿಂತಿರುಗಿ ಅಭಿವ್ಯಕ್ತಿ;
}

/* This is a cache to hold if two types are seen.  */

ರಚನೆ tagged_tu_ನೋಡಿದ_cache {
  ಸ್ಥಿರಾಂಕ ರಚನೆ tagged_tu_ನೋಡಿದ_cache * ಮುಂದಿನ;
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

  ಆದರೆ (error_ಕಾರ್ಯಾಂಶ_p (ಮೌಲ್ಯ))
    ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;

  /* First, detect a valid value with a complete type.  */
  ಆದರೆ (COMPLETE_TYPE_P (type))
    ಹಿಂತಿರುಗಿ ಮೌಲ್ಯ;

  c_incomplete_type_error (loc, ಮೌಲ್ಯ, type);
  ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
}

/* Print an error message for invalid use of an incomplete type.
   VALUE is the expression that was used (or 0 if that isn't known)
   and TYPE is the type that was invalid.  LOC is the location for
   the error.  */

ಶೂನ್ಯ
c_incomplete_type_error (location_t loc, const_ವೃಕ್ಷ ಮೌಲ್ಯ, const_ವೃಕ್ಷ type)
{
  /* Avoid duplicate error message.  */
  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (type) == ERROR_MARK)
    ಹಿಂತಿರುಗಿ;

  ಆದರೆ (ಮೌಲ್ಯ != NULL_ವೃಕ್ಷ && (VAR_P (ಮೌಲ್ಯ) || ವೃಕ್ಷ_ಸಂಕೇತ (ಮೌಲ್ಯ) == PARM_DECL))
    error_at (loc, "%qD has an incomplete type %qT", ಮೌಲ್ಯ, type);
  ಇಲ್ಲದಿದ್ದರೆ
    {
    retry:
      /* We must print an error message.  Be clever about what it says.  */

      ಆಯ್ಕೆ (ವೃಕ್ಷ_ಸಂಕೇತ (type))
	{
	ಸ್ಥಿತಿ ದಾಖಲೆ_TYPE:
	ಸ್ಥಿತಿ UNION_TYPE:
	ಸ್ಥಿತಿ ENUMERAL_TYPE:
	  ನಿಲ್ಲಿಸು;

	ಸ್ಥಿತಿ VOID_TYPE:
	  error_at (loc, "invalid use of void expression");
	  ಹಿಂತಿರುಗಿ;

	ಸ್ಥಿತಿ ARRAY_TYPE:
	  ಆದರೆ (TYPE_DOMAIN (type))
	    {
	      ಆದರೆ (flexible_array_member_type_p (type))
		{
		  error_at (loc, "invalid use of flexible array member");
		  ಹಿಂತಿರುಗಿ;
		}
	      type = ವೃಕ್ಷ_TYPE (type);
	      ಹೋಗು retry;
	    }
	  error_at (loc, "invalid use of array with unspecified bounds");
	  ಹಿಂತಿರುಗಿ;

	ಪೂರ್ವನಿಯೋಜಿತ:
	  gcc_unreachable ();
	}

      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (TYPE_NAME (type)) == IDENTIFIER_ಗಂಟು)
	error_at (loc, "invalid use of undefined type %qT", type);
      ಇಲ್ಲದಿದ್ದರೆ
	/* If this type has a typedef-name, the TYPE_NAME is a TYPE_DECL.  */
	error_at (loc, "invalid use of incomplete typedef %qT", type);
    }
}

/* Given a type, apply default promotions wrt unnamed function
   arguments and return the new type.  */

ವೃಕ್ಷ
c_type_promotes_ಗಮ್ಯ (ವೃಕ್ಷ type)
{
  ವೃಕ್ಷ ret = NULL_ವೃಕ್ಷ;

  ಆದರೆ (TYPE_MAIN_VARIANT (type) == float_type_ಗಂಟು)
    ret = double_type_ಗಂಟು;
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (c_promoting_integer_type_p (type))
    {
      /* Preserve unsignedness if not really getting any wider.  */
      ಆದರೆ (TYPE_UNSIGNED (type)
	  && (TYPE_PRECISION (type) == TYPE_PRECISION (integer_type_ಗಂಟು)))
	ret = unsigned_type_ಗಂಟು;
      ಇಲ್ಲದಿದ್ದರೆ
	ret = integer_type_ಗಂಟು;
    }

  ಆದರೆ (ret != NULL_ವೃಕ್ಷ)
    ಹಿಂತಿರುಗಿ (TYPE_ATOMIC (type)
	    ? c_build_qualified_type (ret, TYPE_QUAL_ATOMIC)
	    : ret);

  ಹಿಂತಿರುಗಿ type;
}

/* Return true if between two named address spaces, whether there is a superset
   named address space that encompasses both address spaces.  If there is a
   superset, return which address space is the superset.  */

ಸ್ಥಿರ ತಾರ್ಕಿಕ
addr_space_superset (addr_space_t as1, addr_space_t as2, addr_space_t *common)
{
  ಆದರೆ (as1 == as2)
    {
      *common = as1;
      ಹಿಂತಿರುಗಿ ನಿಜ;
    }
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (targetm.addr_space.subset_p (as1, as2))
    {
      *common = as2;
      ಹಿಂತಿರುಗಿ ನಿಜ;
    }
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (targetm.addr_space.subset_p (as2, as1))
    {
      *common = as1;
      ಹಿಂತಿರುಗಿ ನಿಜ;
    }
  ಇಲ್ಲದಿದ್ದರೆ
    ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
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
  ಆದರೆ (!addr_space_superset (as_type, as_like, &as_common))
    {
      as_common = as_type;
      error ("%qT and %qT are in disjoint named address spaces",
	     type, like);
    }

  ಹಿಂತಿರುಗಿ c_build_qualified_type (type,
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
  ಆಯ್ಕೆ (ವೃಕ್ಷ_ಸಂಕೇತ (type))
    {
    ಸ್ಥಿತಿ ಸೂಚಕ_TYPE:
    ಸ್ಥಿತಿ FUNCTION_TYPE:
    ಸ್ಥಿತಿ ARRAY_TYPE:
      /* Pointer, array, functions are variably modified if and only if the
	 target, element, return type is variably modified.  */
      ಆದರೆ (!TYPE_STRUCTURAL_EQUALITY_P (type)
	  && (C_TYPE_VARIABLY_MODIFIED (type)
	      != C_TYPE_VARIABLY_MODIFIED (ವೃಕ್ಷ_TYPE (type))))
	ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
      /* If the target type is structural equality, the type should also. */
      ಆದರೆ (!TYPE_STRUCTURAL_EQUALITY_P (type)
	  && TYPE_STRUCTURAL_EQUALITY_P (ವೃಕ್ಷ_TYPE (type)))
	ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
    ಪೂರ್ವನಿಯೋಜಿತ:
       ನಿಲ್ಲಿಸು;
    }

  ಆಯ್ಕೆ (ವೃಕ್ಷ_ಸಂಕೇತ (type))
    {
    ಸ್ಥಿತಿ ಸೂಚಕ_TYPE:
    ಸ್ಥಿತಿ FUNCTION_TYPE:
      /* Pointer and functions can not have variable size.  */
      ಆದರೆ (C_TYPE_VARIABLE_ಗಾತ್ರ (type))
	ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
      ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ ARRAY_TYPE:
      /* An array has variable size if and only if it has a non-constant
	 dimensions or its element type has variable size.  */
      ಆದರೆ ((C_TYPE_VARIABLE_ಗಾತ್ರ (ವೃಕ್ಷ_TYPE (type))
	   || ತುದಿ_array_vla_p (type))
	  != C_TYPE_VARIABLE_ಗಾತ್ರ (type))
	ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
      /* If the element type or the array has variable size, then the
	 array has variable size and is variably modified.  */
      ಆದರೆ (C_TYPE_VARIABLE_ಗಾತ್ರ (ವೃಕ್ಷ_TYPE (type))
	  || C_TYPE_VARIABLE_ಗಾತ್ರ (type))
	{
	  ಆದರೆ (!C_TYPE_VARIABLE_ಗಾತ್ರ (type))
	    ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
	  ಆದರೆ (!C_TYPE_VARIABLY_MODIFIED (type))
	    ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
	}

      /* va_list violates this, accept such types here.  */
      ಆದರೆ (!COMPLETE_TYPE_P (ವೃಕ್ಷ_TYPE (type)))
	ಹಿಂತಿರುಗಿ ನಿಜ;

      ಆದರೆ (COMPLETE_TYPE_P (type))
	{
	  /* If the size is unknown, it can not be complete.  */
	  ಆದರೆ (NULL_ವೃಕ್ಷ == TYPE_DOMAIN (type))
	    ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;

	  /* Zero-length arrays must have size zero.  */
	  ಆದರೆ (zero_ಉದ್ದಳತೆ_array_type_p (type)
	      && !integer_zerop (TYPE_ಗಾತ್ರ (type)))
	    ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
	}
      ಇಲ್ಲದಿದ್ದರೆ
	{
	  /* If not complete but has a domain, it must be a FAM.  */
	  ಆದರೆ (NULL_ವೃಕ್ಷ != TYPE_DOMAIN (type)
	      && !flexible_array_member_type_p (type))
	    ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
	}
    ಪೂರ್ವನಿಯೋಜಿತ:
      ನಿಲ್ಲಿಸು;
    }
  ಹಿಂತಿರುಗಿ ನಿಜ;
}

/* Propagate C_TYPE_VARIABLY_MODIFIED and C_TYPE_VARIABLE_SIZE
   from a base type to a newly built derived or qualified type.  */

ಸ್ಥಿರ ವೃಕ್ಷ
c_ಗಣ_type_ಬಿಟ್ಟುಗಳು (ವೃಕ್ಷ new_type, ವೃಕ್ಷ old_type)
{
  gcc_checking_assert (c_verify_type (old_type));

  ಆದರೆ (c_type_variably_modified_p (old_type))
    C_TYPE_VARIABLY_MODIFIED (new_type) = ನಿಜ;

  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (new_type) == ARRAY_TYPE && C_TYPE_VARIABLE_ಗಾತ್ರ (old_type))
    {
      C_TYPE_VARIABLY_MODIFIED (new_type) = ನಿಜ;
      C_TYPE_VARIABLE_ಗಾತ್ರ (new_type) = ನಿಜ;
    }
  ಹಿಂತಿರುಗಿ new_type;
}

/* Build a pointer type using the default pointer mode.  */

ವೃಕ್ಷ
c_build_ಸೂಚಕ_type (ವೃಕ್ಷ ಗಮ್ಯ_type)
{
  addr_space_t as = ಗಮ್ಯ_type == error_mark_ಗಂಟು ? ADDR_SPACE_GENERIC
					       : TYPE_ADDR_SPACE (ಗಮ್ಯ_type);
  machine_ಬಹುಲಕ ಸೂಚಕ_ಬಹುಲಕ;

  ಆದರೆ (as != ADDR_SPACE_GENERIC || c_default_ಸೂಚಕ_ಬಹುಲಕ == VOIDmode)
    ಸೂಚಕ_ಬಹುಲಕ = targetm.addr_space.ಸೂಚಕ_ಬಹುಲಕ (as);
  ಇಲ್ಲದಿದ್ದರೆ
    ಸೂಚಕ_ಬಹುಲಕ = c_default_ಸೂಚಕ_ಬಹುಲಕ;

  ಹಿಂತಿರುಗಿ c_build_ಸೂಚಕ_type_for_ಬಹುಲಕ (ಗಮ್ಯ_type, ಸೂಚಕ_ಬಹುಲಕ, ಸುಳ್ಳು);
}

/* Build a pointer type using the given mode.  */

ವೃಕ್ಷ
c_build_ಸೂಚಕ_type_for_ಬಹುಲಕ (ವೃಕ್ಷ type, machine_ಬಹುಲಕ ಬಹುಲಕ, ತಾರ್ಕಿಕ m)
{
  ವೃಕ್ಷ ret = build_ಸೂಚಕ_type_for_ಬಹುಲಕ (type, ಬಹುಲಕ, m);
  ಹಿಂತಿರುಗಿ c_ಗಣ_type_ಬಿಟ್ಟುಗಳು (ret, type);
}

/* Build a function type.  */

ವೃಕ್ಷ
c_build_function_type (ವೃಕ್ಷ type, ವೃಕ್ಷ ವಾದಗಳು, ತಾರ್ಕಿಕ no)
{
  ವೃಕ್ಷ ret = build_function_type (type, ವಾದಗಳು, no);
  ಹಿಂತಿರುಗಿ c_ಗಣ_type_ಬಿಟ್ಟುಗಳು (ret, type);
}

/* Build an array type.  This sets typeless storage as required
   by C2Y and C_TYPE_VARIABLY_MODIFIED and C_TYPE_VARIABLE_SIZE
   based on the element type and domain.  */

ವೃಕ್ಷ
c_build_array_type (ವೃಕ್ಷ type, ವೃಕ್ಷ domain)
{
  ಪೂರ್ಣಾಂಕ type_quals = TYPE_QUALS (type);

  /* Identify typeless storage as introduced in C2Y
     and supported also in earlier language modes.  */
  ತಾರ್ಕಿಕ typeless = (char_type_p (type) && !(type_quals & TYPE_QUAL_ATOMIC))
		  || (AGGREGATE_TYPE_P (type) && TYPE_TYPELESS_STORAGE (type));

  ವೃಕ್ಷ ret = build_array_type (type, domain, typeless);

  ಆದರೆ (ತುದಿ_array_vla_p (ret))
    {
      C_TYPE_VARIABLE_ಗಾತ್ರ (ret) = 1;
      C_TYPE_VARIABLY_MODIFIED (ret) = 1;
    }

  ಹಿಂತಿರುಗಿ c_ಗಣ_type_ಬಿಟ್ಟುಗಳು (ret, type);
}

/* Build an array type of unspecified size.  */
ವೃಕ್ಷ
c_build_array_type_unspecified (ವೃಕ್ಷ type)
{
  ವೃಕ್ಷ ಊರ್ಧ್ವ = build2 (COMPOUND_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (ಗಾತ್ರ_zero_ಗಂಟು),
		       integer_zero_ಗಂಟು, ಗಾತ್ರ_zero_ಗಂಟು);
  ಹಿಂತಿರುಗಿ c_build_array_type (type, build_ಸೂಚ್ಯಂಕ_type (ಊರ್ಧ್ವ));
}

/* Build an array type of zero size.  */
ವೃಕ್ಷ
c_build_array_type_zero_ಗಾತ್ರ (ವೃಕ್ಷ type)
{
  /* The GCC extension for zero-length arrays differs from
     ISO flexible array members in that sizeof yields
     zero.  */
  type = c_build_array_type (type, build_ಸೂಚ್ಯಂಕ_type (NULL_ವೃಕ್ಷ));
  type = build_distinct_type_copy (TYPE_MAIN_VARIANT (type));
  TYPE_ಗಾತ್ರ (type) = bitsize_zero_ಗಂಟು;
  TYPE_ಗಾತ್ರ_UNIT (type) = ಗಾತ್ರ_zero_ಗಂಟು;
  ಗಣ_TYPE_STRUCTURAL_EQUALITY (type);
  ಹಿಂತಿರುಗಿ type;
}

ವೃಕ್ಷ
c_build_type_attribute_qual_variant (ವೃಕ್ಷ type, ವೃಕ್ಷ attrs, ಪೂರ್ಣಾಂಕ quals)
{
  ವೃಕ್ಷ ret = build_type_attribute_qual_variant (type, attrs, quals);
  ಹಿಂತಿರುಗಿ c_ಗಣ_type_ಬಿಟ್ಟುಗಳು (ret, type);
}

ವೃಕ್ಷ
c_build_type_attribute_variant (ವೃಕ್ಷ type, ವೃಕ್ಷ attrs)
{
  ಹಿಂತಿರುಗಿ c_build_type_attribute_qual_variant (type, attrs, TYPE_QUALS (type));
}

/* Reconstruct a complex derived type.  This is used to re-construct types
   with the vector attribute.  It is called via a langhook.  */

ವೃಕ್ಷ
c_reconstruct_complex_type (ವೃಕ್ಷ type, ವೃಕ್ಷ bottom)
{
  ವೃಕ್ಷ inner, outer;

  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (type) == ಸೂಚಕ_TYPE)
    {
      inner = c_reconstruct_complex_type (ವೃಕ್ಷ_TYPE (type), bottom);
      outer = c_build_ಸೂಚಕ_type_for_ಬಹುಲಕ (inner, TYPE_ಬಹುಲಕ (type),
					     TYPE_REF_CAN_ALIAS_ALL (type));
    }
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (type) == ARRAY_TYPE)
    {
      ತಾರ್ಕಿಕ rso = TYPE_ಹಿಮ್ಮುಖ_STORAGE_ಕ್ರಮ (type);
      inner = c_reconstruct_complex_type (ವೃಕ್ಷ_TYPE (type), bottom);
      outer = c_build_array_type (inner, TYPE_DOMAIN (type));
      ಆದರೆ (rso)
	{
	  outer = build_distinct_type_copy (outer);
	  TYPE_ಹಿಮ್ಮುಖ_STORAGE_ಕ್ರಮ (outer) = 1;
	}

      gcc_checking_assert (C_TYPE_VARIABLE_ಗಾತ್ರ (type)
			   == C_TYPE_VARIABLE_ಗಾತ್ರ (outer));
    }
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (type) == FUNCTION_TYPE)
    {
      inner = c_reconstruct_complex_type (ವೃಕ್ಷ_TYPE (type), bottom);
      outer = c_build_function_type (inner, TYPE_ARG_TYPES (type),
				     TYPE_NO_NAMED_ವಾದಗಳು_STDARG_P (type));
    }
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (type) == REFERENCE_TYPE
	   || ವೃಕ್ಷ_ಸಂಕೇತ (type) == ಸ್ಥಾನಾಂತರ_TYPE)
    gcc_unreachable ();
  ಇಲ್ಲದಿದ್ದರೆ
    ಹಿಂತಿರುಗಿ bottom;

  ಹಿಂತಿರುಗಿ c_build_type_attribute_qual_variant (outer, TYPE_ಗುಣಲಕ್ಷಣಗಳು (type),
					      TYPE_QUALS (type));
}


/* Helper function for c_canonical_type.  Check whether FIELD
   contains a pointer to a structure or union with tag,
   possibly nested in other type derivations, and return the
   type of this nested structure or union.  */
ಸ್ಥಿರ ವೃಕ್ಷ
ptr_ಗಮ್ಯ_tagged_member (ವೃಕ್ಷ ಕ್ಷೇತ್ರ_2)
{
  gcc_assert (ಕ್ಷೇತ್ರ_DECL == ವೃಕ್ಷ_ಸಂಕೇತ (ಕ್ಷೇತ್ರ_2));
  ವೃಕ್ಷ type = ವೃಕ್ಷ_TYPE (ಕ್ಷೇತ್ರ_2);
  ತಾರ್ಕಿಕ ptr_ನೋಡಿದ = ಸುಳ್ಳು;
  ಆಗ (ವೃಕ್ಷ_ಸಂಕೇತ (type) == ARRAY_TYPE
	 || ವೃಕ್ಷ_ಸಂಕೇತ (type) == FUNCTION_TYPE
	 || ವೃಕ್ಷ_ಸಂಕೇತ (type) == ಸೂಚಕ_TYPE)
    {
      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (type) == ಸೂಚಕ_TYPE)
	ptr_ನೋಡಿದ = ನಿಜ;
      type = ವೃಕ್ಷ_TYPE (type);
    }

  ಆದರೆ (ptr_ನೋಡಿದ
      && ದಾಖಲೆ_OR_UNION_TYPE_P (type)
      && NULL_ವೃಕ್ಷ != c_type_ಟ್ಯಾಗ್ (type))
    ಹಿಂತಿರುಗಿ type;

  ಹಿಂತಿರುಗಿ NULL_ವೃಕ್ಷ;
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
  gcc_assert (ದಾಖಲೆ_OR_UNION_TYPE_P (type));

  ತಾರ್ಕಿಕ needs_mod = ಸುಳ್ಳು;
  ಗಾಗಿ (ವೃಕ್ಷ x = TYPE_FIELDS (type); x; x = DECL_CHAIN (x))
    {
      ಆದರೆ (!ptr_ಗಮ್ಯ_tagged_member (x))
	ಮುಂದುವರಿ;
      needs_mod = ನಿಜ;
      ನಿಲ್ಲಿಸು;
    }
  ಆದರೆ (!needs_mod)
    ಹಿಂತಿರುಗಿ type;

  /* Construct new version with such members replaced.  */
  ವೃಕ್ಷ n = build_distinct_type_copy (type);
  ವೃಕ್ಷ *fields = &TYPE_FIELDS (n);
  ಗಾಗಿ (ವೃಕ್ಷ x = TYPE_FIELDS (type); x; x = DECL_CHAIN (x))
    {
      ವೃಕ್ಷ f = copy_ಗಂಟು (x);
      ಆದರೆ (ವೃಕ್ಷ m = ptr_ಗಮ್ಯ_tagged_member (x))
	{
	  ವೃಕ್ಷ new_ಗಂಟು = make_ಗಂಟು (ವೃಕ್ಷ_ಸಂಕೇತ (m));
	  TYPE_NAME (new_ಗಂಟು) = TYPE_NAME (m);
	  ಗಣ_TYPE_STRUCTURAL_EQUALITY (new_ಗಂಟು);
	  new_ಗಂಟು = qualify_type (new_ಗಂಟು, m);
	  ವೃಕ್ಷ_TYPE (f) = c_reconstruct_complex_type (ವೃಕ್ಷ_TYPE (x),
						      new_ಗಂಟು);
	}
      *fields = f;
      fields = &DECL_CHAIN (f);
    }
  TYPE_CANONICAL (n) = n;
  ಹಿಂತಿರುಗಿ n;
}


/* If NTYPE is a type of a non-variadic function with a prototype
   and OTYPE is a type of a function without a prototype and ATTRS
   contains attribute format, diagnosess and removes it from ATTRS.
   Returns the result of build_type_attribute_variant of NTYPE and
   the (possibly) modified ATTRS.  */

ಸ್ಥಿರ ವೃಕ್ಷ
c_build_functype_attribute_variant (ವೃಕ್ಷ ntype, ವೃಕ್ಷ otype, ವೃಕ್ಷ attrs)
{
  ಆದರೆ (!prototype_p (otype)
      && prototype_p (ntype)
      && lookup_attribute ("format", attrs))
    {
      warning_at (ಒಳಹರಿವು_location, OPT_Wattributes,
		  "%qs attribute can only be applied to variadic functions",
		  "format");
      attrs = remove_attribute ("format", attrs);
    }
  ಹಿಂತಿರುಗಿ c_build_type_attribute_variant (ntype, attrs);

}

/* Given a type which could be a typedef name, make sure to return the
   original type.  See set_underlying_type. */
ಸ್ಥಿರ const_ವೃಕ್ಷ
c_type_original (const_ವೃಕ್ಷ t)
{
  /* It may even be a typedef of a typedef...
     In the case of compiler-created builtin structs the TYPE_DECL
     may be a dummy, with no DECL_ORIGINAL_TYPE.  Don't fault.  */
  ಆಗ (TYPE_NAME (t)
	 && ವೃಕ್ಷ_ಸಂಕೇತ (TYPE_NAME (t)) == TYPE_DECL
	 && DECL_ORIGINAL_TYPE (TYPE_NAME (t)))
    t = DECL_ORIGINAL_TYPE (TYPE_NAME (t));
  ಹಿಂತಿರುಗಿ t;
}

/* Return the tag for a tagged type.  */
ವೃಕ್ಷ
c_type_ಟ್ಯಾಗ್ (const_ವೃಕ್ಷ t)
{
  gcc_assert (ದಾಖಲೆ_OR_UNION_TYPE_P (t) || ವೃಕ್ಷ_ಸಂಕೇತ (t) == ENUMERAL_TYPE);
  const_ವೃಕ್ಷ orig = c_type_original (t);
  ವೃಕ್ಷ name = TYPE_NAME (orig);
  ಆದರೆ (!name)
    ಹಿಂತಿರುಗಿ NULL_ವೃಕ್ಷ;
  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (name) == TYPE_DECL)
    {
      ಆದರೆ (!DECL_NAME (name))
	ಹಿಂತಿರುಗಿ NULL_ವೃಕ್ಷ;
      name = DECL_NAME (name);
    }
  gcc_checking_assert (ವೃಕ್ಷ_ಸಂಕೇತ (name) == IDENTIFIER_ಗಂಟು);
  ಹಿಂತಿರುಗಿ name;
}

/* Remove qualifiers but not atomic.  For arrays remove qualifiers
   on the element type but also do not remove atomic.  */
ಸ್ಥಿರ ವೃಕ್ಷ
remove_qualifiers (ವೃಕ್ಷ t)
{
  ಆದರೆ (!t || t == error_mark_ಗಂಟು)
    ಹಿಂತಿರುಗಿ t;
  ಹಿಂತಿರುಗಿ TYPE_ATOMIC (strip_array_types (t))
	 ? c_build_qualified_type (TYPE_MAIN_VARIANT (t), TYPE_QUAL_ATOMIC)
	 : TYPE_MAIN_VARIANT (t);
}


/* Helper function for composite_type_internal.  Find a compatible type
   in a (transparent) union U compatible to T.  If found, return the
   type of the corresponding member.  Otherwise, return the union type U.  */
ಸ್ಥಿರ ವೃಕ್ಷ
transparent_union_replacement (ವೃಕ್ಷ u, ವೃಕ್ಷ t)
{
  ಆದರೆ (u == error_mark_ಗಂಟು || t == error_mark_ಗಂಟು
      || ವೃಕ್ಷ_ಸಂಕೇತ (u) != UNION_TYPE
      || !(TYPE_TRANSPARENT_AGGR (u) || TYPE_NAME (u) == NULL_ವೃಕ್ಷ)
      || comptypes (u, t))
    ಹಿಂತಿರುಗಿ u;

  ಗಾಗಿ (ವೃಕ್ಷ memb = TYPE_FIELDS (u); memb; memb = DECL_CHAIN (memb))
    {
      ವೃಕ್ಷ m = remove_qualifiers (ವೃಕ್ಷ_TYPE (memb));
      ಆದರೆ (comptypes (m, t))
	{
	  pedwarn (ಒಳಹರಿವು_location, OPT_Wpedantic,
		    "function types not truly compatible in ISO C");
	  ಹಿಂತಿರುಗಿ m;
	}
    }

  ಹಿಂತಿರುಗಿ u;
}



/* Return the composite type of two compatible types.

   We assume that comptypes has already been done and returned
   nonzero; if that isn't so, this may crash.  In particular, we
   assume that qualifiers match.  */

ರಚನೆ ಸಂಯುಕ್ತ_cache {
  ವೃಕ್ಷ t1;
  ವೃಕ್ಷ t2;
  ವೃಕ್ಷ ಸಂಯುಕ್ತ;
  ರಚನೆ ಸಂಯುಕ್ತ_cache* ಮುಂದಿನ;
};

ವೃಕ್ಷ
ಸಂಯುಕ್ತ_type_ಆಂತರಿಕ (ವೃಕ್ಷ t1, ವೃಕ್ಷ t2, ವೃಕ್ಷ cond,
			 ರಚನೆ ಸಂಯುಕ್ತ_cache* cache)
{
  ಎಣಿಕೆ ವೃಕ್ಷ_ಸಂಕೇತ_2 code1;
  ಎಣಿಕೆ ವೃಕ್ಷ_ಸಂಕೇತ_2 code2;
  ವೃಕ್ಷ ಗುಣಲಕ್ಷಣಗಳು;

  /* Save time if the two types are the same.  */

  ಆದರೆ (t1 == t2) ಹಿಂತಿರುಗಿ t1;

  /* If one type is nonsense, use the other.  */
  ಆದರೆ (t1 == error_mark_ಗಂಟು)
    ಹಿಂತಿರುಗಿ t2;
  ಆದರೆ (t2 == error_mark_ಗಂಟು)
    ಹಿಂತಿರುಗಿ t1;

  code1 = ವೃಕ್ಷ_ಸಂಕೇತ (t1);
  code2 = ವೃಕ್ಷ_ಸಂಕೇತ (t2);

  /* Merge the attributes.  */
  ಗುಣಲಕ್ಷಣಗಳು = targetm.ವಿಲೀನ_type_ಗುಣಲಕ್ಷಣಗಳು (t1, t2);

  /* If one is an enumerated type and the other is the compatible
     integer type, the composite type might be either of the two
     (DR#013 question 3).  For consistency, use the enumerated type as
     the composite type.  */

  ಆದರೆ (code1 == ENUMERAL_TYPE
      && (code2 == INTEGER_TYPE
	  || code2 == BOOLEAN_TYPE))
    ಹಿಂತಿರುಗಿ t1;
  ಆದರೆ (code2 == ENUMERAL_TYPE
      && (code1 == INTEGER_TYPE
	  || code1 == BOOLEAN_TYPE))
    ಹಿಂತಿರುಗಿ t2;

  gcc_assert (code1 == code2);

  ಆಯ್ಕೆ (code1)
    {
    ಸ್ಥಿತಿ ಸೂಚಕ_TYPE:
      /* For two pointers, do this recursively on the target type.  */
      {
	gcc_checking_assert (TYPE_QUALS (t1) == TYPE_QUALS (t2));
	ವೃಕ್ಷ ಗುರಿ = ಸಂಯುಕ್ತ_type_ಆಂತರಿಕ (ವೃಕ್ಷ_TYPE (t1), ವೃಕ್ಷ_TYPE (t2),
					       cond, cache);
	ವೃಕ್ಷ n = c_build_ಸೂಚಕ_type_for_ಬಹುಲಕ (ಗುರಿ, TYPE_ಬಹುಲಕ (t1), ಸುಳ್ಳು);
	ಹಿಂತಿರುಗಿ c_build_type_attribute_qual_variant (n, ಗುಣಲಕ್ಷಣಗಳು,
						    TYPE_QUALS (t2));
      }

    ಸ್ಥಿತಿ ARRAY_TYPE:
      {
	ವೃಕ್ಷ d1 = TYPE_DOMAIN (t1);
	ವೃಕ್ಷ d2 = TYPE_DOMAIN (t2);

	/* We should not have any type quals on arrays at all.  */
	gcc_assert (!TYPE_QUALS_NO_ADDR_SPACE (t1)
		    && !TYPE_QUALS_NO_ADDR_SPACE (t2));

	ತಾರ್ಕಿಕ d1_zero = zero_ಉದ್ದಳತೆ_array_type_p (t1)
		       || flexible_array_member_type_p (t1);
	ತಾರ್ಕಿಕ d2_zero = zero_ಉದ್ದಳತೆ_array_type_p (t2)
		       || flexible_array_member_type_p (t2);

	ತಾರ್ಕಿಕ d1_variable = ತುದಿ_array_vla_p (t1);
	ತಾರ್ಕಿಕ d2_variable = ತುದಿ_array_vla_p (t2);

	ತಾರ್ಕಿಕ use1 = d1 && (d2_variable || !d2 || d2_zero || !d1_variable);
	ತಾರ್ಕಿಕ use2 = d2 && (d1_variable || !d1 || d1_zero || !d2_variable);

	/* If the first is an unspecified size pick the other one.  */
	ಆದರೆ (d2_variable && c_type_unspecified_p (t1))
	  {
	    gcc_assert (use1 && use2);
	    use1 = ಸುಳ್ಳು;
	  }

	/* If both are VLAs but not unspecified and we are in the
	   conditional operator, we create a conditional to select
	   the size of the active branch.  */
	ತಾರ್ಕಿಕ use0 = cond && d1_variable && !c_type_unspecified_p (t1)
			 && d2_variable && !c_type_unspecified_p (t2);

	ವೃಕ್ಷ td;
	ವೃಕ್ಷ elt = ಸಂಯುಕ್ತ_type_ಆಂತರಿಕ (ವೃಕ್ಷ_TYPE (t1), ವೃಕ್ಷ_TYPE (t2),
					    cond, cache);

	ಆದರೆ (!use0)
	  {
	    /* Save space: see if the result is identical to one of the args.  */
	    ಆದರೆ (elt == ವೃಕ್ಷ_TYPE (t1) && use1)
	      ಹಿಂತಿರುಗಿ c_build_type_attribute_variant (t1, ಗುಣಲಕ್ಷಣಗಳು);
	    ಆದರೆ (elt == ವೃಕ್ಷ_TYPE (t2) && use2)
	      ಹಿಂತಿರುಗಿ c_build_type_attribute_variant (t2, ಗುಣಲಕ್ಷಣಗಳು);

	    ಆದರೆ (elt == ವೃಕ್ಷ_TYPE (t1) && !TYPE_DOMAIN (t2) && !TYPE_DOMAIN (t1))
	      ಹಿಂತಿರುಗಿ c_build_type_attribute_variant (t1, ಗುಣಲಕ್ಷಣಗಳು);
	    ಆದರೆ (elt == ವೃಕ್ಷ_TYPE (t2) && !TYPE_DOMAIN (t2) && !TYPE_DOMAIN (t1))
	      ಹಿಂತಿರುಗಿ c_build_type_attribute_variant (t2, ಗುಣಲಕ್ಷಣಗಳು);

	    td = TYPE_DOMAIN (use1 ? t1 : t2);
	  }
	ಇಲ್ಲದಿದ್ದರೆ
	  {
	    /* Not used in C.  */
	    gcc_assert (ಗಾತ್ರ_zero_ಗಂಟು == TYPE_MIN_ಮೌಲ್ಯ (d1));
	    gcc_assert (ಗಾತ್ರ_zero_ಗಂಟು == TYPE_MIN_ಮೌಲ್ಯ (d2));

	    ವೃಕ್ಷ d = fold_build3_loc (UNKNOWN_LOCATION, COND_ಅಭಿವ್ಯಕ್ತಿ, sizetype,
				      cond, TYPE_MAX_ಮೌಲ್ಯ (d1),
				      TYPE_MAX_ಮೌಲ್ಯ (d2));

	    td = build_ಸೂಚ್ಯಂಕ_type (d);
	  }

	/* Merge the element types, and have a size if either arg has
	   one.  We may have qualifiers on the element types.  To set
	   up TYPE_MAIN_VARIANT correctly, we need to form the
	   composite of the unqualified types and add the qualifiers
	   back at the end.  */
	ಪೂರ್ಣಾಂಕ quals = TYPE_QUALS (strip_array_types (elt));
	ವೃಕ್ಷ unqual_elt = c_build_qualified_type (elt, TYPE_UNQUALIFIED);

	ಆದರೆ ((!d1 || d1_zero) && (!d2 || d2_zero) && (d1 || d2))
	  t1 = c_build_array_type_zero_ಗಾತ್ರ (unqual_elt);
	ಇಲ್ಲದಿದ್ದರೆ
	  t1 = c_build_array_type (unqual_elt, td);

	/* Check that a type which has a varying outermost dimension
	   got marked as having a variable size.  */
	ತಾರ್ಕಿಕ varsize = (d1_variable && d2_variable)
		       || (d1_variable && !d2)
		       || (d2_variable && !d1);
	gcc_checking_assert (!varsize || C_TYPE_VARIABLE_ಗಾತ್ರ (t1));

	t1 = c_build_qualified_type (t1, quals);
	ಹಿಂತಿರುಗಿ c_build_type_attribute_variant (t1, ಗುಣಲಕ್ಷಣಗಳು);
      }

    ಸ್ಥಿತಿ ದಾಖಲೆ_TYPE:
    ಸ್ಥಿತಿ UNION_TYPE:
      ಆದರೆ (flag_isoc23 && !comptypes_same_p (t1, t2))
	{
	  /* Go to the original type to get the right tag.  */
	  ವೃಕ್ಷ ಟ್ಯಾಗ್ = c_type_ಟ್ಯಾಗ್ (t1);

	  gcc_checking_assert (COMPLETE_TYPE_P (t1) && COMPLETE_TYPE_P (t2));
	  gcc_checking_assert (!ಟ್ಯಾಗ್ || comptypes (t1, t2));

	  /* If a composite type for these two types is already under
	     construction, return it.  */

	  ಗಾಗಿ (ರಚನೆ ಸಂಯುಕ್ತ_cache *c = cache; c != ಖಾಲಿ; c = c->ಮುಂದಿನ)
	    ಆದರೆ ((c->t1 == t1 && c->t2 == t2) || (c->t1 == t2 && c->t2 == t1))
	       ಹಿಂತಿರುಗಿ c->ಸಂಯುಕ್ತ;

	  /* Otherwise, create a new type node and link it into the cache.  */

	  ವೃಕ್ಷ n = make_ಗಂಟು (code1);
	  ಗಣ_TYPE_STRUCTURAL_EQUALITY (n);
	  TYPE_NAME (n) = ಟ್ಯಾಗ್;

	  ರಚನೆ ಸಂಯುಕ್ತ_cache cache2 = { t1, t2, n, cache };
	  cache = &cache2;

	  ವೃಕ್ಷ f1 = TYPE_FIELDS (t1);
	  ವೃಕ್ಷ f2 = TYPE_FIELDS (t2);
	  ವೃಕ್ಷ fields = NULL_ವೃಕ್ಷ;

	  ಗಾಗಿ (ವೃಕ್ಷ a = f1, b = f2; a && b;
	       a = DECL_CHAIN (a), b = DECL_CHAIN (b))
	    {
	      ವೃಕ್ಷ ta = ವೃಕ್ಷ_TYPE (a);
	      ವೃಕ್ಷ tb = ವೃಕ್ಷ_TYPE (b);

	      ಆದರೆ (DECL_C_ಬಿಟ್_ಕ್ಷೇತ್ರ (a))
		{
		  ta = DECL_ಬಿಟ್_ಕ್ಷೇತ್ರ_TYPE (a);
		  tb = DECL_ಬಿಟ್_ಕ್ಷೇತ್ರ_TYPE (b);
		}

	      gcc_assert (DECL_NAME (a) == DECL_NAME (b));
	      gcc_checking_assert (!DECL_NAME (a) || comptypes (ta, tb));

	      ವೃಕ್ಷ t = ಸಂಯುಕ್ತ_type_ಆಂತರಿಕ (ta, tb, cond, cache);
	      ವೃಕ್ಷ f = build_decl (ಒಳಹರಿವು_location, ಕ್ಷೇತ್ರ_DECL, DECL_NAME (a), t);

	      DECL_PACKED (f) = DECL_PACKED (a);
	      ಗಣ_DECL_ALIGN (f, DECL_ALIGN (a));
	      DECL_ಗುಣಲಕ್ಷಣಗಳು (f) = DECL_ಗುಣಲಕ್ಷಣಗಳು (a);
	      C_DECL_VARIABLE_ಗಾತ್ರ (f) = C_TYPE_VARIABLE_ಗಾತ್ರ (t);

	      decl_ಗುಣಲಕ್ಷಣಗಳು (&f, DECL_ಗುಣಲಕ್ಷಣಗಳು (f), 0);

	      ಮುಕ್ತಾಯ_decl (f, ಒಳಹರಿವು_location, ಖಾಲಿ, ಖಾಲಿ, ಖಾಲಿ);

	      ಆದರೆ (DECL_C_ಬಿಟ್_ಕ್ಷೇತ್ರ (a))
		{
		  /* This will be processed by finish_struct.  */
		  ಗಣ_DECL_C_ಬಿಟ್_ಕ್ಷೇತ್ರ (f);
		  DECL_INITIAL (f) = build_int_cst (integer_type_ಗಂಟು,
						    ವೃಕ್ಷ_ಗಮ್ಯ_uhwi (DECL_ಗಾತ್ರ (a)));
		  DECL_NONADDRESSABLE_P (f) = ನಿಜ;
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

	  n = ಮುಕ್ತಾಯ_struct (ಒಳಹರಿವು_location, n, fields, ಗುಣಲಕ್ಷಣಗಳು, ಖಾಲಿ,
			     &ಅಭಿವ್ಯಕ್ತಿ);

	  ಹಿಂತಿರುಗಿ qualify_type (n, t1);
	}
      /* FALLTHRU */
    ಸ್ಥಿತಿ ENUMERAL_TYPE:
      ಆದರೆ (ಗುಣಲಕ್ಷಣಗಳು != ಖಾಲಿ)
	{
	  /* Try harder not to create a new aggregate type.  */
	  ಆದರೆ (attribute_list_equal (TYPE_ಗುಣಲಕ್ಷಣಗಳು (t1), ಗುಣಲಕ್ಷಣಗಳು))
	    ಹಿಂತಿರುಗಿ t1;
	  ಆದರೆ (attribute_list_equal (TYPE_ಗುಣಲಕ್ಷಣಗಳು (t2), ಗುಣಲಕ್ಷಣಗಳು))
	    ಹಿಂತಿರುಗಿ t2;
	}
      ಹಿಂತಿರುಗಿ c_build_type_attribute_variant (t1, ಗುಣಲಕ್ಷಣಗಳು);

    ಸ್ಥಿತಿ FUNCTION_TYPE:
      /* Function types: prefer the one that specified arg types.
	 If both do, merge the arg types.  Also merge the return types.  */
      {
	ವೃಕ್ಷ valtype = ಸಂಯುಕ್ತ_type_ಆಂತರಿಕ (ವೃಕ್ಷ_TYPE (t1), ವೃಕ್ಷ_TYPE (t2),
						cond, cache);
	ವೃಕ್ಷ p1 = TYPE_ARG_TYPES (t1);
	ವೃಕ್ಷ p2 = TYPE_ARG_TYPES (t2);

	/* Save space: see if the result is identical to one of the args.  */
	ಆದರೆ (valtype == ವೃಕ್ಷ_TYPE (t1) && !TYPE_ARG_TYPES (t2))
	  ಹಿಂತಿರುಗಿ c_build_functype_attribute_variant (t1, t2, ಗುಣಲಕ್ಷಣಗಳು);
	ಆದರೆ (valtype == ವೃಕ್ಷ_TYPE (t2) && !TYPE_ARG_TYPES (t1))
	  ಹಿಂತಿರುಗಿ c_build_functype_attribute_variant (t2, t1, ಗುಣಲಕ್ಷಣಗಳು);

	/* Simple way if one arg fails to specify argument types.  */
	ಆದರೆ (TYPE_ARG_TYPES (t1) == NULL_ವೃಕ್ಷ)
	  {
	    t1 = c_build_function_type (valtype, TYPE_ARG_TYPES (t2),
					TYPE_NO_NAMED_ವಾದಗಳು_STDARG_P (t2));
	    t1 = c_build_type_attribute_variant (t1, ಗುಣಲಕ್ಷಣಗಳು);
	    ಹಿಂತಿರುಗಿ qualify_type (t1, t2);
	 }
	ಆದರೆ (TYPE_ARG_TYPES (t2) == NULL_ವೃಕ್ಷ)
	  {
	    t1 = c_build_function_type (valtype, TYPE_ARG_TYPES (t1),
					TYPE_NO_NAMED_ವಾದಗಳು_STDARG_P (t1));
	    t1 = c_build_type_attribute_variant (t1, ಗುಣಲಕ್ಷಣಗಳು);
	    ಹಿಂತಿರುಗಿ qualify_type (t1, t2);
	  }

	/* If both args specify argument types, we must merge the two
	   lists, argument by argument.  */
	ವೃಕ್ಷ newargs = NULL_ವೃಕ್ಷ;
	ವೃಕ್ಷ *endp = &newargs;

	ಗಾಗಿ (; p1; p1 = ವೃಕ್ಷ_CHAIN (p1), p2 = ವೃಕ್ಷ_CHAIN (p2))
	  {
	    ಆದರೆ (p1 == void_list_ಗಂಟು)
	      {
		*endp = void_list_ಗಂಟು;
		ನಿಲ್ಲಿಸು;
	      }
	    ವೃಕ್ಷ mv1 = remove_qualifiers (ವೃಕ್ಷ_ಮೌಲ್ಯ (p1));
	    ವೃಕ್ಷ mv2 = remove_qualifiers (ವೃಕ್ಷ_ಮೌಲ್ಯ (p2));

	    gcc_assert (mv1);
	    gcc_assert (mv2);

	    mv1 = transparent_union_replacement (mv1, mv2);
	    mv2 = transparent_union_replacement (mv2, mv1);

	    *endp = ವೃಕ್ಷ_cons (NULL_ವೃಕ್ಷ,
			       ಸಂಯುಕ್ತ_type_ಆಂತರಿಕ (mv1, mv2, cond, cache),
			       NULL_ವೃಕ್ಷ);

	    endp = &ವೃಕ್ಷ_CHAIN (*endp);
	  }

	t1 = c_build_function_type (valtype, newargs);
	t1 = qualify_type (t1, t2);
      }
      /* FALLTHRU */

    ಪೂರ್ವನಿಯೋಜಿತ:
      ಹಿಂತಿರುಗಿ c_build_type_attribute_variant (t1, ಗುಣಲಕ್ಷಣಗಳು);
    }
}

ವೃಕ್ಷ
ಸಂಯುಕ್ತ_type_cond (ವೃಕ್ಷ t1, ವೃಕ್ಷ t2, ವೃಕ್ಷ cond)
{
  gcc_checking_assert (comptypes_check_for_ಸಂಯುಕ್ತ (t1, t2));

  ರಚನೆ ಸಂಯುಕ್ತ_cache cache = { };
  ವೃಕ್ಷ n = ಸಂಯುಕ್ತ_type_ಆಂತರಿಕ (t1, t2, cond, &cache);

  gcc_checking_assert (comptypes_check_for_ಸಂಯುಕ್ತ (n, t1));
  gcc_checking_assert (comptypes_check_for_ಸಂಯುಕ್ತ (n, t2));
  ಹಿಂತಿರುಗಿ n;
}


ವೃಕ್ಷ
ಸಂಯುಕ್ತ_type (ವೃಕ್ಷ t1, ವೃಕ್ಷ t2)
{
  ಹಿಂತಿರುಗಿ ಸಂಯುಕ್ತ_type_cond (t1, t2, NULL_ವೃಕ್ಷ);
}

/* Return the type of a conditional expression between pointers to
   possibly differently qualified versions of compatible types.

   We assume that comp_target_types has already been done and returned
   true; if that isn't so, this may crash.  */

ಸ್ಥಿರ ವೃಕ್ಷ
common_ಸೂಚಕ_type (ವೃಕ್ಷ t1, ವೃಕ್ಷ t2, ವೃಕ್ಷ cond)
{
  ವೃಕ್ಷ ಗುಣಲಕ್ಷಣಗಳು;
  ಚಿಹ್ನೆರಹಿತ ಗುರಿ_quals;
  addr_space_t as1, as2, as_common;
  ಪೂರ್ಣಾಂಕ quals1, quals2;

  /* Save time if the two types are the same.  */

  ಆದರೆ (t1 == t2) ಹಿಂತಿರುಗಿ t1;

  /* If one type is nonsense, use the other.  */
  ಆದರೆ (t1 == error_mark_ಗಂಟು)
    ಹಿಂತಿರುಗಿ t2;
  ಆದರೆ (t2 == error_mark_ಗಂಟು)
    ಹಿಂತಿರುಗಿ t1;

  gcc_assert (ವೃಕ್ಷ_ಸಂಕೇತ (t1) == ಸೂಚಕ_TYPE
	      && ವೃಕ್ಷ_ಸಂಕೇತ (t2) == ಸೂಚಕ_TYPE);

  /* Merge the attributes.  */
  ಗುಣಲಕ್ಷಣಗಳು = targetm.ವಿಲೀನ_type_ಗುಣಲಕ್ಷಣಗಳು (t1, t2);

  /* Find the composite type of the target types, and combine the
     qualifiers of the two types' targets.  */
  ವೃಕ್ಷ pointed_ಗಮ್ಯ_1 = ವೃಕ್ಷ_TYPE (t1);
  ವೃಕ್ಷ pointed_ಗಮ್ಯ_2 = ವೃಕ್ಷ_TYPE (t2);
  ವೃಕ್ಷ ಗುರಿ = ಸಂಯುಕ್ತ_type_cond (TYPE_MAIN_VARIANT (pointed_ಗಮ್ಯ_1),
				     TYPE_MAIN_VARIANT (pointed_ಗಮ್ಯ_2), cond);

  /* Strip array types to get correct qualifier for pointers to arrays */
  quals1 = TYPE_QUALS_NO_ADDR_SPACE (strip_array_types (pointed_ಗಮ್ಯ_1));
  quals2 = TYPE_QUALS_NO_ADDR_SPACE (strip_array_types (pointed_ಗಮ್ಯ_2));

  /* For function types do not merge const qualifiers, but drop them
     if used inconsistently.  The middle-end uses these to mark const
     and noreturn functions.  */
  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (pointed_ಗಮ್ಯ_1) == FUNCTION_TYPE)
    ಗುರಿ_quals = (quals1 & quals2);
  ಇಲ್ಲದಿದ್ದರೆ
    ಗುರಿ_quals = (quals1 | quals2);

  /* If the two named address spaces are different, determine the common
     superset address space.  This is guaranteed to exist due to the
     assumption that comp_target_type returned true.  */
  as1 = TYPE_ADDR_SPACE (pointed_ಗಮ್ಯ_1);
  as2 = TYPE_ADDR_SPACE (pointed_ಗಮ್ಯ_2);
  ಆದರೆ (!addr_space_superset (as1, as2, &as_common))
    gcc_unreachable ();

  ಗುರಿ_quals |= ENCODE_QUAL_ADDR_SPACE (as_common);

  t1 = c_build_ಸೂಚಕ_type (c_build_qualified_type (ಗುರಿ, ಗುರಿ_quals));
  ಹಿಂತಿರುಗಿ c_build_type_attribute_variant (t1, ಗುಣಲಕ್ಷಣಗಳು);
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
  ಎಣಿಕೆ ವೃಕ್ಷ_ಸಂಕೇತ_2 code1;
  ಎಣಿಕೆ ವೃಕ್ಷ_ಸಂಕೇತ_2 code2;

  /* If one type is nonsense, use the other.  */
  ಆದರೆ (t1 == error_mark_ಗಂಟು)
    ಹಿಂತಿರುಗಿ t2;
  ಆದರೆ (t2 == error_mark_ಗಂಟು)
    ಹಿಂತಿರುಗಿ t1;

  ಆದರೆ (TYPE_QUALS (t1) != TYPE_UNQUALIFIED)
    t1 = TYPE_MAIN_VARIANT (t1);

  ಆದರೆ (TYPE_QUALS (t2) != TYPE_UNQUALIFIED)
    t2 = TYPE_MAIN_VARIANT (t2);

  ಆದರೆ (TYPE_ಗುಣಲಕ್ಷಣಗಳು (t1) != NULL_ವೃಕ್ಷ)
    {
      ವೃಕ್ಷ attrs = affects_type_ತಟಸ್ಥ_ಗುಣಲಕ್ಷಣಗಳು (TYPE_ಗುಣಲಕ್ಷಣಗಳು (t1));
      t1 = c_build_type_attribute_variant (t1, attrs);
    }

  ಆದರೆ (TYPE_ಗುಣಲಕ್ಷಣಗಳು (t2) != NULL_ವೃಕ್ಷ)
    {
      ವೃಕ್ಷ attrs = affects_type_ತಟಸ್ಥ_ಗುಣಲಕ್ಷಣಗಳು (TYPE_ಗುಣಲಕ್ಷಣಗಳು (t2));
      t2 = c_build_type_attribute_variant (t2, attrs);
    }

  /* Save time if the two types are the same.  */

  ಆದರೆ (t1 == t2) ಹಿಂತಿರುಗಿ t1;

  code1 = ವೃಕ್ಷ_ಸಂಕೇತ (t1);
  code2 = ವೃಕ್ಷ_ಸಂಕೇತ (t2);

  gcc_assert (code1 == ಸದಿಶ_TYPE || code1 == COMPLEX_TYPE
	      || code1 == FIXED_ಬಿಂದು_TYPE || code1 == REAL_TYPE
	      || code1 == INTEGER_TYPE || code1 == BITINT_TYPE);
  gcc_assert (code2 == ಸದಿಶ_TYPE || code2 == COMPLEX_TYPE
	      || code2 == FIXED_ಬಿಂದು_TYPE || code2 == REAL_TYPE
	      || code2 == INTEGER_TYPE || code2 == BITINT_TYPE);

  /* When one operand is a decimal float type, the other operand cannot be
     a generic float type or a complex type.  We also disallow vector types
     here.  */
  ಆದರೆ ((DECIMAL_FLOAT_TYPE_P (t1) || DECIMAL_FLOAT_TYPE_P (t2))
      && !(DECIMAL_FLOAT_TYPE_P (t1) && DECIMAL_FLOAT_TYPE_P (t2)))
    {
      ಆದರೆ (code1 == ಸದಿಶ_TYPE || code2 == ಸದಿಶ_TYPE)
	{
	  error ("cannot mix operands of decimal floating and vector types");
	  ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
	}
      ಆದರೆ (code1 == COMPLEX_TYPE || code2 == COMPLEX_TYPE)
	{
	  error ("cannot mix operands of decimal floating and complex types");
	  ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
	}
      ಆದರೆ (code1 == REAL_TYPE && code2 == REAL_TYPE)
	{
	  error ("cannot mix operands of decimal floating "
		 "and other floating types");
	  ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
	}
    }

  /* If one type is a vector type, return that type.  (How the usual
     arithmetic conversions apply to the vector types extension is not
     precisely specified.)  */
  ಆದರೆ (code1 == ಸದಿಶ_TYPE)
    ಹಿಂತಿರುಗಿ t1;

  ಆದರೆ (code2 == ಸದಿಶ_TYPE)
    ಹಿಂತಿರುಗಿ t2;

  /* If one type is complex, form the common type of the non-complex
     components, then make that complex.  Use T1 or T2 if it is the
     required type.  */
  ಆದರೆ (code1 == COMPLEX_TYPE || code2 == COMPLEX_TYPE)
    {
      ವೃಕ್ಷ subtype1 = code1 == COMPLEX_TYPE ? ವೃಕ್ಷ_TYPE (t1) : t1;
      ವೃಕ್ಷ subtype2 = code2 == COMPLEX_TYPE ? ವೃಕ್ಷ_TYPE (t2) : t2;
      ವೃಕ್ಷ subtype = c_common_type (subtype1, subtype2);

      ಆದರೆ (code1 == COMPLEX_TYPE && ವೃಕ್ಷ_TYPE (t1) == subtype)
	ಹಿಂತಿರುಗಿ t1;
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (code2 == COMPLEX_TYPE && ವೃಕ್ಷ_TYPE (t2) == subtype)
	ಹಿಂತಿರುಗಿ t2;
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (subtype) == BITINT_TYPE)
	{
	  sorry ("%<_Complex _BitInt(%d)%> unsupported",
		 TYPE_PRECISION (subtype));
	  ಹಿಂತಿರುಗಿ code1 == COMPLEX_TYPE ? t1 : t2;
	}
      ಇಲ್ಲದಿದ್ದರೆ
	ಹಿಂತಿರುಗಿ build_complex_type (subtype);
    }

  /* If only one is real, use it as the result.  */

  ಆದರೆ (code1 == REAL_TYPE && code2 != REAL_TYPE)
    ಹಿಂತಿರುಗಿ t1;

  ಆದರೆ (code2 == REAL_TYPE && code1 != REAL_TYPE)
    ಹಿಂತಿರುಗಿ t2;

  /* If both are real and either are decimal floating point types, use
     the decimal floating point type with the greater precision. */

  ಆದರೆ (code1 == REAL_TYPE && code2 == REAL_TYPE)
    {
      ಆದರೆ (TYPE_MAIN_VARIANT (t1) == dfloat128_type_ಗಂಟು
	  || TYPE_MAIN_VARIANT (t2) == dfloat128_type_ಗಂಟು)
	ಹಿಂತಿರುಗಿ dfloat128_type_ಗಂಟು;
      /* And prefer _Decimal128 over _Decimal64x which has in GCC's
	 implementation the same mode.  */
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (TYPE_MAIN_VARIANT (t1) == dfloat64x_type_ಗಂಟು
	       || TYPE_MAIN_VARIANT (t2) == dfloat64x_type_ಗಂಟು)
	ಹಿಂತಿರುಗಿ dfloat64x_type_ಗಂಟು;
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (TYPE_MAIN_VARIANT (t1) == dfloat64_type_ಗಂಟು
	       || TYPE_MAIN_VARIANT (t2) == dfloat64_type_ಗಂಟು)
	ಹಿಂತಿರುಗಿ dfloat64_type_ಗಂಟು;
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (TYPE_MAIN_VARIANT (t1) == dfloat32_type_ಗಂಟು
	       || TYPE_MAIN_VARIANT (t2) == dfloat32_type_ಗಂಟು)
	ಹಿಂತಿರುಗಿ dfloat32_type_ಗಂಟು;
    }

  /* Deal with fixed-point types.  */
  ಆದರೆ (code1 == FIXED_ಬಿಂದು_TYPE || code2 == FIXED_ಬಿಂದು_TYPE)
    {
      ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ unsignedp = 0, satp = 0;
      scalar_ಬಹುಲಕ m1, m2;
      ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ fbit1, ibit1, fbit2, ibit2, max_fbit, max_ibit;

      m1 = SCALAR_TYPE_ಬಹುಲಕ (t1);
      m2 = SCALAR_TYPE_ಬಹುಲಕ (t2);

      /* If one input type is saturating, the result type is saturating.  */
      ಆದರೆ (TYPE_SATURATING (t1) || TYPE_SATURATING (t2))
	satp = 1;

      /* If both fixed-point types are unsigned, the result type is unsigned.
	 When mixing fixed-point and integer types, follow the sign of the
	 fixed-point type.
	 Otherwise, the result type is signed.  */
      ಆದರೆ ((TYPE_UNSIGNED (t1) && TYPE_UNSIGNED (t2)
	   && code1 == FIXED_ಬಿಂದು_TYPE && code2 == FIXED_ಬಿಂದು_TYPE)
	  || (code1 == FIXED_ಬಿಂದು_TYPE && code2 != FIXED_ಬಿಂದು_TYPE
	      && TYPE_UNSIGNED (t1))
	  || (code1 != FIXED_ಬಿಂದು_TYPE && code2 == FIXED_ಬಿಂದು_TYPE
	      && TYPE_UNSIGNED (t2)))
	unsignedp = 1;

      /* The result type is signed.  */
      ಆದರೆ (unsignedp == 0)
	{
	  /* If the input type is unsigned, we need to convert to the
	     signed type.  */
	  ಆದರೆ (code1 == FIXED_ಬಿಂದು_TYPE && TYPE_UNSIGNED (t1))
	    {
	      ಎಣಿಕೆ ಬಹುಲಕ_class mclass = (ಎಣಿಕೆ ಬಹುಲಕ_class) 0;
	      ಆದರೆ (GET_ಬಹುಲಕ_CLASS (m1) == ಬಹುಲಕ_UFRACT)
		mclass = ಬಹುಲಕ_FRACT;
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (GET_ಬಹುಲಕ_CLASS (m1) == ಬಹುಲಕ_UACCUM)
		mclass = ಬಹುಲಕ_ACCUM;
	      ಇಲ್ಲದಿದ್ದರೆ
		gcc_unreachable ();
	      m1 = as_a <scalar_ಬಹುಲಕ>
		(ಬಹುಲಕ_for_ಗಾತ್ರ (GET_ಬಹುಲಕ_PRECISION (m1), mclass, 0));
	    }
	  ಆದರೆ (code2 == FIXED_ಬಿಂದು_TYPE && TYPE_UNSIGNED (t2))
	    {
	      ಎಣಿಕೆ ಬಹುಲಕ_class mclass = (ಎಣಿಕೆ ಬಹುಲಕ_class) 0;
	      ಆದರೆ (GET_ಬಹುಲಕ_CLASS (m2) == ಬಹುಲಕ_UFRACT)
		mclass = ಬಹುಲಕ_FRACT;
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (GET_ಬಹುಲಕ_CLASS (m2) == ಬಹುಲಕ_UACCUM)
		mclass = ಬಹುಲಕ_ACCUM;
	      ಇಲ್ಲದಿದ್ದರೆ
		gcc_unreachable ();
	      m2 = as_a <scalar_ಬಹುಲಕ>
		(ಬಹುಲಕ_for_ಗಾತ್ರ (GET_ಬಹುಲಕ_PRECISION (m2), mclass, 0));
	    }
	}

      ಆದರೆ (code1 == FIXED_ಬಿಂದು_TYPE)
	{
	  fbit1 = GET_ಬಹುಲಕ_FBIT (m1);
	  ibit1 = GET_ಬಹುಲಕ_IBIT (m1);
	}
      ಇಲ್ಲದಿದ್ದರೆ
	{
	  fbit1 = 0;
	  /* Signed integers need to subtract one sign bit.  */
	  ibit1 = TYPE_PRECISION (t1) - (!TYPE_UNSIGNED (t1));
	}

      ಆದರೆ (code2 == FIXED_ಬಿಂದು_TYPE)
	{
	  fbit2 = GET_ಬಹುಲಕ_FBIT (m2);
	  ibit2 = GET_ಬಹುಲಕ_IBIT (m2);
	}
      ಇಲ್ಲದಿದ್ದರೆ
	{
	  fbit2 = 0;
	  /* Signed integers need to subtract one sign bit.  */
	  ibit2 = TYPE_PRECISION (t2) - (!TYPE_UNSIGNED (t2));
	}

      max_ibit = ibit1 >= ibit2 ?  ibit1 : ibit2;
      max_fbit = fbit1 >= fbit2 ?  fbit1 : fbit2;
      ಹಿಂತಿರುಗಿ c_common_fixed_ಬಿಂದು_type_for_ಗಾತ್ರ (max_ibit, max_fbit, unsignedp,
						 satp);
    }

  /* Both real or both integers; use the one with greater precision.  */

  ಆದರೆ (TYPE_PRECISION (t1) > TYPE_PRECISION (t2))
    ಹಿಂತಿರುಗಿ t1;
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (TYPE_PRECISION (t2) > TYPE_PRECISION (t1))
    ಹಿಂತಿರುಗಿ t2;

  /* Same precision.  Prefer long longs to longs to ints when the
     same precision, following the C99 rules on integer type rank
     (which are equivalent to the C90 rules for C90 types).  */

  ಆದರೆ (TYPE_MAIN_VARIANT (t1) == long_long_unsigned_type_ಗಂಟು
      || TYPE_MAIN_VARIANT (t2) == long_long_unsigned_type_ಗಂಟು)
    ಹಿಂತಿರುಗಿ long_long_unsigned_type_ಗಂಟು;

  ಆದರೆ (TYPE_MAIN_VARIANT (t1) == long_long_integer_type_ಗಂಟು
      || TYPE_MAIN_VARIANT (t2) == long_long_integer_type_ಗಂಟು)
    {
      ಆದರೆ (TYPE_UNSIGNED (t1) || TYPE_UNSIGNED (t2))
	ಹಿಂತಿರುಗಿ long_long_unsigned_type_ಗಂಟು;
      ಇಲ್ಲದಿದ್ದರೆ
	ಹಿಂತಿರುಗಿ long_long_integer_type_ಗಂಟು;
    }

  ಆದರೆ (TYPE_MAIN_VARIANT (t1) == long_unsigned_type_ಗಂಟು
      || TYPE_MAIN_VARIANT (t2) == long_unsigned_type_ಗಂಟು)
    ಹಿಂತಿರುಗಿ long_unsigned_type_ಗಂಟು;

  ಆದರೆ (TYPE_MAIN_VARIANT (t1) == long_integer_type_ಗಂಟು
      || TYPE_MAIN_VARIANT (t2) == long_integer_type_ಗಂಟು)
    {
      /* But preserve unsignedness from the other type,
	 since long cannot hold all the values of an unsigned int.  */
      ಆದರೆ (TYPE_UNSIGNED (t1) || TYPE_UNSIGNED (t2))
	ಹಿಂತಿರುಗಿ long_unsigned_type_ಗಂಟು;
      ಇಲ್ಲದಿದ್ದರೆ
	ಹಿಂತಿರುಗಿ long_integer_type_ಗಂಟು;
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

  ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = ಅಂಕೆ_FLOATN_TYPES - 1; i >= 0; i--)
    ಆದರೆ (mv1 == FLOATN_TYPE_ಗಂಟು (i) || mv2 == FLOATN_TYPE_ಗಂಟು (i))
      ಹಿಂತಿರುಗಿ FLOATN_TYPE_ಗಂಟು (i);

  /* Likewise, prefer long double to double even if same size.  */
  ಆದರೆ (mv1 == long_double_type_ಗಂಟು || mv2 == long_double_type_ಗಂಟು)
    ಹಿಂತಿರುಗಿ long_double_type_ಗಂಟು;

  /* Likewise, prefer double to float even if same size.
     We got a couple of embedded targets with 32 bit doubles, and the
     pdp11 might have 64 bit floats.  */
  ಆದರೆ (mv1 == double_type_ಗಂಟು || mv2 == double_type_ಗಂಟು)
    ಹಿಂತಿರುಗಿ double_type_ಗಂಟು;

  ಆದರೆ (mv1 == float_type_ಗಂಟು || mv2 == float_type_ಗಂಟು)
    ಹಿಂತಿರುಗಿ float_type_ಗಂಟು;

  ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = ಅಂಕೆ_FLOATNX_TYPES - 1; i >= 0; i--)
    ಆದರೆ (mv1 == FLOATNX_TYPE_ಗಂಟು (i) || mv2 == FLOATNX_TYPE_ಗಂಟು (i))
      ಹಿಂತಿರುಗಿ FLOATNX_TYPE_ಗಂಟು (i);

  ಆದರೆ ((code1 == BITINT_TYPE || code2 == BITINT_TYPE) && code1 != code2)
    {
      /* Prefer any other integral types over bit-precise integer types.  */
      ಆದರೆ (TYPE_UNSIGNED (t1) == TYPE_UNSIGNED (t2))
	ಹಿಂತಿರುಗಿ code1 == BITINT_TYPE ? t2 : t1;
      /* If BITINT_TYPE is unsigned and the other type is signed
	 non-BITINT_TYPE with the same precision, the latter has higher rank.
	 In that case:
	 Otherwise, both operands are converted to the unsigned integer type
	 corresponding to the type of the operand with signed integer type.  */
      ಆದರೆ (TYPE_UNSIGNED (code1 == BITINT_TYPE ? t1 : t2))
	ಹಿಂತಿರುಗಿ c_common_unsigned_type (code1 == BITINT_TYPE ? t2 : t1);
    }

  /* Otherwise prefer the unsigned one.  */

  ಆದರೆ (TYPE_UNSIGNED (t1))
    ಹಿಂತಿರುಗಿ t1;
  ಇಲ್ಲದಿದ್ದರೆ
    ಹಿಂತಿರುಗಿ t2;
}

/* Wrapper around c_common_type that is used by c-common.cc and other
   front end optimizations that remove promotions.  ENUMERAL_TYPEs
   are allowed here and are converted to their compatible integer types.
   BOOLEAN_TYPEs are allowed here and return either boolean_type_node or
   preferably a non-Boolean type as the common type.  */
ವೃಕ್ಷ
common_type (ವೃಕ್ಷ t1, ವೃಕ್ಷ t2)
{
  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (t1) == ENUMERAL_TYPE)
    t1 = ENUM_UNDERLYING_TYPE (t1);
  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (t2) == ENUMERAL_TYPE)
    t2 = ENUM_UNDERLYING_TYPE (t2);

  /* If both types are BOOLEAN_TYPE, then return boolean_type_node.  */
  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (t1) == BOOLEAN_TYPE
      && ವೃಕ್ಷ_ಸಂಕೇತ (t2) == BOOLEAN_TYPE)
    ಹಿಂತಿರುಗಿ boolean_type_ಗಂಟು;

  /* If either type is BOOLEAN_TYPE, then return the other.  */
  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (t1) == BOOLEAN_TYPE)
    ಹಿಂತಿರುಗಿ t2;
  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (t2) == BOOLEAN_TYPE)
    ಹಿಂತಿರುಗಿ t1;

  ಹಿಂತಿರುಗಿ c_common_type (t1, t2);
}



/* Helper function for comptypes.  For two compatible types, return 1
   if they pass consistency checks.  In particular we test that
   TYPE_CANONICAL is set correctly, i.e. the two types can alias.  */

ಸ್ಥಿರ ತಾರ್ಕಿಕ
comptypes_verify (ವೃಕ್ಷ type1, ವೃಕ್ಷ type2)
{
  ಆದರೆ (type1 == type2 || !type1 || !type2
      || ವೃಕ್ಷ_ಸಂಕೇತ (type1) == ERROR_MARK || ವೃಕ್ಷ_ಸಂಕೇತ (type2) == ERROR_MARK)
    ಹಿಂತಿರುಗಿ ನಿಜ;

  gcc_checking_assert (c_verify_type (type1));
  gcc_checking_assert (c_verify_type (type2));

  ಆದರೆ (TYPE_CANONICAL (type1) != TYPE_CANONICAL (type2)
      && !TYPE_STRUCTURAL_EQUALITY_P (type1)
      && !TYPE_STRUCTURAL_EQUALITY_P (type2))
    {
      /* FIXME: check other types. */
      ಆದರೆ (ದಾಖಲೆ_OR_UNION_TYPE_P (type1)
	  || ವೃಕ್ಷ_ಸಂಕೇತ (type1) == ENUMERAL_TYPE
	  || ವೃಕ್ಷ_ಸಂಕೇತ (type2) == ENUMERAL_TYPE)
	ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
    }
  ಹಿಂತಿರುಗಿ ನಿಜ;
}

ರಚನೆ comptypes_ದತ್ತಾಂಶ {

  /* output */
  ತಾರ್ಕಿಕ enum_and_int_p;
  ತಾರ್ಕಿಕ different_types_p;
  ತಾರ್ಕಿಕ warning_needed;

  /* context */
  ತಾರ್ಕಿಕ anon_ಕ್ಷೇತ್ರ;
  ತಾರ್ಕಿಕ pointedto;

  /* configuration */
  ತಾರ್ಕಿಕ equiv;
  ತಾರ್ಕಿಕ ignore_promoting_ವಾದಗಳು;

  ಸ್ಥಿರಾಂಕ ರಚನೆ tagged_tu_ನೋಡಿದ_cache* cache;
};


/* Helper function for composite_type.  This function ignores when the
   function type of an old-style declaration is incompatible with a type
   of a declaration with prototype because some are arguments are not
   self-promoting.  This is ignored only for function types but not
   ignored in a nested context.  */

ಸ್ಥಿರ ತಾರ್ಕಿಕ
comptypes_check_for_ಸಂಯುಕ್ತ (ವೃಕ್ಷ t1, ವೃಕ್ಷ t2)
{
  ರಚನೆ comptypes_ದತ್ತಾಂಶ ದತ್ತಾಂಶ = { };
  ದತ್ತಾಂಶ.ignore_promoting_ವಾದಗಳು = FUNCTION_TYPE == ವೃಕ್ಷ_ಸಂಕೇತ (t1);
  ಹಿಂತಿರುಗಿ comptypes_ಆಂತರಿಕ (t1, t2, &ದತ್ತಾಂಶ);
}


/* C implementation of compatible_types_for_indirection_note_p.  */

ತಾರ್ಕಿಕ
compatible_types_for_indirection_note_p (ವೃಕ್ಷ type1, ವೃಕ್ಷ type2)
{
  ಹಿಂತಿರುಗಿ comptypes (type1, type2);
}

/* Return true if TYPE1 and TYPE2 are compatible types for assignment
   or various other operations.  */

ತಾರ್ಕಿಕ
comptypes (ವೃಕ್ಷ type1, ವೃಕ್ಷ type2)
{
  ರಚನೆ comptypes_ದತ್ತಾಂಶ ದತ್ತಾಂಶ = { };
  ತಾರ್ಕಿಕ ret = comptypes_ಆಂತರಿಕ (type1, type2, &ದತ್ತಾಂಶ);

  gcc_checking_assert (!ret || comptypes_verify (type1, type2));

  ಹಿಂತಿರುಗಿ ret;
}


/* Like comptypes, but it returns non-zero only for identical
   types.  */

ತಾರ್ಕಿಕ
comptypes_same_p (ವೃಕ್ಷ type1, ವೃಕ್ಷ type2)
{
  ರಚನೆ comptypes_ದತ್ತಾಂಶ ದತ್ತಾಂಶ = { };
  ತಾರ್ಕಿಕ ret = comptypes_ಆಂತರಿಕ (type1, type2, &ದತ್ತಾಂಶ);

  gcc_checking_assert (!ret || comptypes_verify (type1, type2));

  ಆದರೆ (ದತ್ತಾಂಶ.different_types_p)
    ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;

  ಹಿಂತಿರುಗಿ ret;
}


/* Like comptypes, but if it returns true because enum and int are
   compatible, it sets *ENUM_AND_INT_P to true.  */

ತಾರ್ಕಿಕ
comptypes_check_enum_int (ವೃಕ್ಷ type1, ವೃಕ್ಷ type2, ತಾರ್ಕಿಕ *enum_and_int_p)
{
  ರಚನೆ comptypes_ದತ್ತಾಂಶ ದತ್ತಾಂಶ = { };
  ತಾರ್ಕಿಕ ret = comptypes_ಆಂತರಿಕ (type1, type2, &ದತ್ತಾಂಶ);
  *enum_and_int_p = ದತ್ತಾಂಶ.enum_and_int_p;

  gcc_checking_assert (!ret || comptypes_verify (type1, type2));

  ಹಿಂತಿರುಗಿ ret;
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
  ರಚನೆ comptypes_ದತ್ತಾಂಶ ದತ್ತಾಂಶ = { };
  ದತ್ತಾಂಶ.equiv = ನಿಜ;
  ತಾರ್ಕಿಕ ret = comptypes_ಆಂತರಿಕ (type1, type2, &ದತ್ತಾಂಶ);

  /* check that different equivance classes are assigned only
     to types that are not compatible.  */
  gcc_checking_assert (ret || !comptypes (type1, type2));

  ಹಿಂತಿರುಗಿ ret;
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
comptypes_ಆಂತರಿಕ (const_ವೃಕ್ಷ type1, const_ವೃಕ್ಷ type2,
		    ರಚನೆ comptypes_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ)
{
  const_ವೃಕ್ಷ t1 = type1;
  const_ವೃಕ್ಷ t2 = type2;

  /* Suppress errors caused by previously reported errors.  */

  ಆದರೆ (t1 == t2 || !t1 || !t2
      || ವೃಕ್ಷ_ಸಂಕೇತ (t1) == ERROR_MARK || ವೃಕ್ಷ_ಸಂಕೇತ (t2) == ERROR_MARK)
    ಹಿಂತಿರುಗಿ ನಿಜ;

  /* Qualifiers must match. C99 6.7.3p9 */

  ಆದರೆ (TYPE_QUALS (t1) != TYPE_QUALS (t2))
    ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;

  /* Enumerated types are compatible with integer types, but this is
     not transitive: two enumerated types in the same translation unit
     are compatible with each other only if they are the same type.  */

  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (t1) == ENUMERAL_TYPE
      && COMPLETE_TYPE_P (t1)
      && ವೃಕ್ಷ_ಸಂಕೇತ (t2) != ENUMERAL_TYPE)
    {
      t1 = ENUM_UNDERLYING_TYPE (t1);
      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (t2) != VOID_TYPE)
	{
	  ದತ್ತಾಂಶ->enum_and_int_p = ನಿಜ;
	  ದತ್ತಾಂಶ->different_types_p = ನಿಜ;
	}
    }
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (t2) == ENUMERAL_TYPE
	   && COMPLETE_TYPE_P (t2)
	   && ವೃಕ್ಷ_ಸಂಕೇತ (t1) != ENUMERAL_TYPE)
    {
      t2 = ENUM_UNDERLYING_TYPE (t2);
      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (t1) != VOID_TYPE)
	{
	  ದತ್ತಾಂಶ->enum_and_int_p = ನಿಜ;
	  ದತ್ತಾಂಶ->different_types_p = ನಿಜ;
	}
    }

  ಆದರೆ (t1 == t2)
    ಹಿಂತಿರುಗಿ ನಿಜ;

  /* Different classes of types can't be compatible.  */

  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (t1) != ವೃಕ್ಷ_ಸಂಕೇತ (t2))
    ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;

  /* Allow for two different type nodes which have essentially the same
     definition.  Note that we already checked for equality of the type
     qualifiers (just above).  */

  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (t1) != ARRAY_TYPE
      && TYPE_MAIN_VARIANT (t1) == TYPE_MAIN_VARIANT (t2))
    ಹಿಂತಿರುಗಿ ನಿಜ;

  ಪೂರ್ಣಾಂಕ attrval;

  /* 1 if no need for warning yet, 2 if warning cause has been seen.  */
  ಆದರೆ (!(attrval = comp_type_ಗುಣಲಕ್ಷಣಗಳು (t1, t2)))
    ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;

  ಆದರೆ (2 == attrval)
    ದತ್ತಾಂಶ->warning_needed = ನಿಜ;

  ಆಯ್ಕೆ (ವೃಕ್ಷ_ಸಂಕೇತ (t1))
    {
    ಸ್ಥಿತಿ INTEGER_TYPE:
    ಸ್ಥಿತಿ FIXED_ಬಿಂದು_TYPE:
    ಸ್ಥಿತಿ REAL_TYPE:
    ಸ್ಥಿತಿ BITINT_TYPE:
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
      ಹಿಂತಿರುಗಿ TYPE_CANONICAL (t1) == TYPE_CANONICAL (t2);

    ಸ್ಥಿತಿ ಸೂಚಕ_TYPE:
      /* Do not remove mode information.  */
      ಆದರೆ (TYPE_ಬಹುಲಕ (t1) != TYPE_ಬಹುಲಕ (t2))
	ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
      ದತ್ತಾಂಶ->pointedto = ನಿಜ;
      ಹಿಂತಿರುಗಿ comptypes_ಆಂತರಿಕ (ವೃಕ್ಷ_TYPE (t1), ವೃಕ್ಷ_TYPE (t2), ದತ್ತಾಂಶ);

    ಸ್ಥಿತಿ FUNCTION_TYPE:
      ಹಿಂತಿರುಗಿ function_types_compatible_p (t1, t2, ದತ್ತಾಂಶ);

    ಸ್ಥಿತಿ ARRAY_TYPE:
      {
	ವೃಕ್ಷ d1 = TYPE_DOMAIN (t1);
	ವೃಕ್ಷ d2 = TYPE_DOMAIN (t2);

	/* Target types must match incl. qualifiers.  */
	ಆದರೆ (!comptypes_ಆಂತರಿಕ (ವೃಕ್ಷ_TYPE (t1), ವೃಕ್ಷ_TYPE (t2), ದತ್ತಾಂಶ))
	  ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;

	ಆದರೆ ((d1 == NULL_ವೃಕ್ಷ) != (d2 == NULL_ವೃಕ್ಷ))
	  ದತ್ತಾಂಶ->different_types_p = ನಿಜ;
	/* Ignore size mismatches when forming equivalence classes.  */
	ಆದರೆ (ದತ್ತಾಂಶ->equiv)
	  ಹಿಂತಿರುಗಿ ನಿಜ;
	/* Sizes must match unless one is missing or variable.  */
	ಆದರೆ (d1 == NULL_ವೃಕ್ಷ || d2 == NULL_ವೃಕ್ಷ || d1 == d2)
	  ಹಿಂತಿರುಗಿ ನಿಜ;

	ತಾರ್ಕಿಕ d1_variable = ತುದಿ_array_vla_p (t1);
	ತಾರ್ಕಿಕ d2_variable = ತುದಿ_array_vla_p (t2);

	ಆದರೆ (d1_variable != d2_variable)
	  ದತ್ತಾಂಶ->different_types_p = ನಿಜ;
	ಆದರೆ (d1_variable || d2_variable)
	  ಹಿಂತಿರುಗಿ ನಿಜ;

	ತಾರ್ಕಿಕ d1_zero = zero_ಉದ್ದಳತೆ_array_type_p (t1)
		       || flexible_array_member_type_p (t1);

	ತಾರ್ಕಿಕ d2_zero = zero_ಉದ್ದಳತೆ_array_type_p (t2)
		       || flexible_array_member_type_p (t2);

	ಆದರೆ (d1_zero && d2_zero)
	  ಹಿಂತಿರುಗಿ ನಿಜ;
	ಆದರೆ (d1_zero || d2_zero)
	  ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;

	ಆದರೆ (!ವೃಕ್ಷ_int_cst_equal (TYPE_MIN_ಮೌಲ್ಯ (d1), TYPE_MIN_ಮೌಲ್ಯ (d2))
	    || !ವೃಕ್ಷ_int_cst_equal (TYPE_MAX_ಮೌಲ್ಯ (d1), TYPE_MAX_ಮೌಲ್ಯ (d2)))
	  ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;

	ಹಿಂತಿರುಗಿ ನಿಜ;
      }

    ಸ್ಥಿತಿ ENUMERAL_TYPE:
    ಸ್ಥಿತಿ ದಾಖಲೆ_TYPE:
    ಸ್ಥಿತಿ UNION_TYPE:

      ಆದರೆ (!flag_isoc23)
	ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;

      ಹಿಂತಿರುಗಿ tagged_types_tu_compatible_p (t1, t2, ದತ್ತಾಂಶ);

    ಸ್ಥಿತಿ ಸದಿಶ_TYPE:
      ಹಿಂತಿರುಗಿ ತಿಳಿದ_eq (TYPE_ಸದಿಶ_SUBPARTS (t1), TYPE_ಸದಿಶ_SUBPARTS (t2))
	     && comptypes_ಆಂತರಿಕ (ವೃಕ್ಷ_TYPE (t1), ವೃಕ್ಷ_TYPE (t2), ದತ್ತಾಂಶ);

    ಪೂರ್ವನಿಯೋಜಿತ:
      ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
    }
  gcc_unreachable ();
}

/* Return true if TTL and TTR are pointers to types that are equivalent, ignoring
   their qualifiers, except for named address spaces.  If the pointers point to
   different named addresses, then we must determine if one address space is a
   subset of the other.  */

ಸ್ಥಿರ ತಾರ್ಕಿಕ
comp_ಗುರಿ_types (location_t location, ವೃಕ್ಷ ttl, ವೃಕ್ಷ ttr)
{
  ವೃಕ್ಷ mvl = ವೃಕ್ಷ_TYPE (ttl);
  ವೃಕ್ಷ mvr = ವೃಕ್ಷ_TYPE (ttr);
  addr_space_t asl = TYPE_ADDR_SPACE (mvl);
  addr_space_t asr = TYPE_ADDR_SPACE (mvr);
  addr_space_t as_common;

  /* Fail if pointers point to incompatible address spaces.  */
  ಆದರೆ (!addr_space_superset (asl, asr, &as_common))
    ಹಿಂತಿರುಗಿ 0;

  /* Qualifiers on element types of array types that are
     pointer targets are also removed.  */
  ರಚನೆ comptypes_ದತ್ತಾಂಶ ದತ್ತಾಂಶ = { };
  ಆದರೆ (!comptypes_ಆಂತರಿಕ (remove_qualifiers (mvl),
			   remove_qualifiers (mvr), &ದತ್ತಾಂಶ))
    ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;

  /* For pedantic use comptypes on arrays before removing
     qualifiers on the element type. */
  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (mvl) == ARRAY_TYPE
      && ವೃಕ್ಷ_ಸಂಕೇತ (mvr) == ARRAY_TYPE
      && !comptypes (mvl, mvr))
    pedwarn_c11 (location, OPT_Wpedantic, "invalid use of pointers to arrays "
					  "with different qualifiers in ISO C "
					  "before C23");

  ಆದರೆ (ದತ್ತಾಂಶ.warning_needed)
    pedwarn (location, OPT_Wpedantic, "types are not quite compatible");

  ಆದರೆ (ದತ್ತಾಂಶ.enum_and_int_p && warn_cxx_compat)
    warning_at (location, OPT_Wc___compat,
		"pointer target types incompatible in C++");

  ಹಿಂತಿರುಗಿ ನಿಜ;
}

/* Subroutines of `comptypes'.  */

/* Return true if two 'struct', 'union', or 'enum' types T1 and T2 are
   compatible.  The two types are not the same (which has been
   checked earlier in comptypes_internal).  */

ಸ್ಥಿರ ತಾರ್ಕಿಕ
tagged_types_tu_compatible_p (const_ವೃಕ್ಷ t1, const_ವೃಕ್ಷ t2,
			      ರಚನೆ comptypes_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ)
{
  ವೃಕ್ಷ s1, s2;

  ಆದರೆ (c_type_ಟ್ಯಾಗ್ (t1) != c_type_ಟ್ಯಾಗ್ (t2))
    ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;

  /* When forming equivalence classes for TYPE_CANONICAL in C23, we treat
     structs with the same tag as equivalent, but only when they are targets
     of pointers inside other structs.  */
  ಆದರೆ (ದತ್ತಾಂಶ->equiv && ದತ್ತಾಂಶ->pointedto && NULL_ವೃಕ್ಷ != c_type_ಟ್ಯಾಗ್ (t1))
    ಹಿಂತಿರುಗಿ ನಿಜ;

  /* Different types without tag are incompatible except as an anonymous
     field or when forming equivalence classes for TYPE_CANONICAL.  */
  ಆದರೆ (!ದತ್ತಾಂಶ->anon_ಕ್ಷೇತ್ರ && !ದತ್ತಾಂಶ->equiv && NULL_ವೃಕ್ಷ == c_type_ಟ್ಯಾಗ್ (t1))
    ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;

  ಆದರೆ (!ದತ್ತಾಂಶ->anon_ಕ್ಷೇತ್ರ && TYPE_STUB_DECL (t1) != TYPE_STUB_DECL (t2))
    ದತ್ತಾಂಶ->different_types_p = ನಿಜ;

  /* Incomplete types are incompatible inside a TU.  */
  ಆದರೆ (TYPE_ಗಾತ್ರ (t1) == ಖಾಲಿ || TYPE_ಗಾತ್ರ (t2) == ಖಾಲಿ)
    ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;

  ಆದರೆ (ENUMERAL_TYPE != ವೃಕ್ಷ_ಸಂಕೇತ (t1)
      && (TYPE_ಹಿಮ್ಮುಖ_STORAGE_ಕ್ರಮ (t1)
	  != TYPE_ಹಿಮ್ಮುಖ_STORAGE_ಕ್ರಮ (t2)))
    ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;

  ಆದರೆ (TYPE_USER_ALIGN (t1) != TYPE_USER_ALIGN (t2))
    ದತ್ತಾಂಶ->different_types_p = ನಿಜ;

  /* For types already being looked at in some active
     invocation of this function, assume compatibility.
     The cache is built as a linked list on the stack
     with the head of the list passed downwards.  */
  ಗಾಗಿ (ಸ್ಥಿರಾಂಕ ರಚನೆ tagged_tu_ನೋಡಿದ_cache *t = ದತ್ತಾಂಶ->cache;
       t != ಖಾಲಿ; t = t->ಮುಂದಿನ)
    ಆದರೆ (t->t1 == t1 && t->t2 == t2)
      ಹಿಂತಿರುಗಿ ನಿಜ;

  ಸ್ಥಿರಾಂಕ ರಚನೆ tagged_tu_ನೋಡಿದ_cache ನಮೂದು = { ದತ್ತಾಂಶ->cache, t1, t2 };

  ಆಯ್ಕೆ (ವೃಕ್ಷ_ಸಂಕೇತ (t1))
    {
    ಸ್ಥಿತಿ ENUMERAL_TYPE:
      {
	ಆದರೆ (!comptypes (ENUM_UNDERLYING_TYPE (t1), ENUM_UNDERLYING_TYPE (t2)))
	  ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;

	/* Speed up the case where the type values are in the same order.  */
	ವೃಕ್ಷ tv1 = TYPE_ಮೌಲ್ಯಗಳು (t1);
	ವೃಕ್ಷ tv2 = TYPE_ಮೌಲ್ಯಗಳು (t2);

	ಆದರೆ (tv1 == tv2)
	  ಹಿಂತಿರುಗಿ ನಿಜ;

	ಗಾಗಿ (;tv1 && tv2; tv1 = ವೃಕ್ಷ_CHAIN (tv1), tv2 = ವೃಕ್ಷ_CHAIN (tv2))
	  {
	    ಆದರೆ (ವೃಕ್ಷ_PURPOSE (tv1) != ವೃಕ್ಷ_PURPOSE (tv2))
	      ನಿಲ್ಲಿಸು;

	    ಆದರೆ (simple_cst_equal (DECL_INITIAL (ವೃಕ್ಷ_ಮೌಲ್ಯ (tv1)),
				  DECL_INITIAL (ವೃಕ್ಷ_ಮೌಲ್ಯ (tv2))) != 1)
	      ನಿಲ್ಲಿಸು;
	  }

	ಆದರೆ (tv1 == NULL_ವೃಕ್ಷ && tv2 == NULL_ವೃಕ್ಷ)
	  ಹಿಂತಿರುಗಿ ನಿಜ;

	ಆದರೆ (tv1 == NULL_ವೃಕ್ಷ || tv2 == NULL_ವೃಕ್ಷ)
	  ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;

	ಆದರೆ (list_ಉದ್ದಳತೆ (TYPE_ಮೌಲ್ಯಗಳು (t1)) != list_ಉದ್ದಳತೆ (TYPE_ಮೌಲ್ಯಗಳು (t2)))
	  ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;

	ಗಾಗಿ (s1 = TYPE_ಮೌಲ್ಯಗಳು (t1); s1; s1 = ವೃಕ್ಷ_CHAIN (s1))
	  {
	    s2 = purpose_member (ವೃಕ್ಷ_PURPOSE (s1), TYPE_ಮೌಲ್ಯಗಳು (t2));

	    ಆದರೆ (s2 == ಖಾಲಿ
		|| simple_cst_equal (DECL_INITIAL (ವೃಕ್ಷ_ಮೌಲ್ಯ (s1)),
				     DECL_INITIAL (ವೃಕ್ಷ_ಮೌಲ್ಯ (s2))) != 1)
	      ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
	  }

	ಹಿಂತಿರುಗಿ ನಿಜ;
      }

    ಸ್ಥಿತಿ UNION_TYPE:
    ಸ್ಥಿತಿ ದಾಖಲೆ_TYPE:

	ಆದರೆ (list_ಉದ್ದಳತೆ (TYPE_FIELDS (t1)) != list_ಉದ್ದಳತೆ (TYPE_FIELDS (t2)))
	  ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;

	ಗಾಗಿ (s1 = TYPE_FIELDS (t1), s2 = TYPE_FIELDS (t2);
	     s1 && s2;
	     s1 = DECL_CHAIN (s1), s2 = DECL_CHAIN (s2))
	  {
	    gcc_assert (ವೃಕ್ಷ_ಸಂಕೇತ (s1) == ಕ್ಷೇತ್ರ_DECL);
	    gcc_assert (ವೃಕ್ಷ_ಸಂಕೇತ (s2) == ಕ್ಷೇತ್ರ_DECL);

	    ವೃಕ್ಷ ft1 = ವೃಕ್ಷ_TYPE (s1);
	    ವೃಕ್ಷ ft2 = ವೃಕ್ಷ_TYPE (s2);

	    ಆದರೆ (DECL_NAME (s1) != DECL_NAME (s2))
	      ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;

	    ಆದರೆ (DECL_ALIGN (s1) != DECL_ALIGN (s2))
	      ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;

	    ಆದರೆ (DECL_C_ಬಿಟ್_ಕ್ಷೇತ್ರ (s1) != DECL_C_ಬಿಟ್_ಕ್ಷೇತ್ರ (s2))
	       ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;

	    ಆದರೆ (DECL_C_ಬಿಟ್_ಕ್ಷೇತ್ರ (s1))
	      {
		ಆದರೆ (!ವೃಕ್ಷ_int_cst_equal (DECL_ಗಾತ್ರ (s1), DECL_ಗಾತ್ರ (s2)))
		  ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;

		ft1 = DECL_ಬಿಟ್_ಕ್ಷೇತ್ರ_TYPE (s1);
		ft2 = DECL_ಬಿಟ್_ಕ್ಷೇತ್ರ_TYPE (s2);
	      }

	    ಆದರೆ (!ft1 || !ft2)
	      ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;

	    ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ft1) == ERROR_MARK || ವೃಕ್ಷ_ಸಂಕೇತ (ft2) == ERROR_MARK)
	      ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;

	    ದತ್ತಾಂಶ->anon_ಕ್ಷೇತ್ರ = !DECL_NAME (s1);
	    ದತ್ತಾಂಶ->pointedto = ಸುಳ್ಳು;

	    ಸ್ಥಿರಾಂಕ ರಚನೆ tagged_tu_ನೋಡಿದ_cache *cache = ದತ್ತಾಂಶ->cache;
	    ದತ್ತಾಂಶ->cache = &ನಮೂದು;
	    ತಾರ್ಕಿಕ ret = comptypes_ಆಂತರಿಕ (ft1, ft2, ದತ್ತಾಂಶ);
	    ದತ್ತಾಂಶ->cache = cache;
	    ಆದರೆ (!ret)
	      ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;

	    ವೃಕ್ಷ st1 = TYPE_ಗಾತ್ರ (ವೃಕ್ಷ_TYPE (s1));
	    ವೃಕ್ಷ st2 = TYPE_ಗಾತ್ರ (ವೃಕ್ಷ_TYPE (s2));

	    ಆದರೆ (ದತ್ತಾಂಶ->equiv
		&& st1 && ವೃಕ್ಷ_ಸಂಕೇತ (st1) == INTEGER_CST
		&& st2 && ವೃಕ್ಷ_ಸಂಕೇತ (st2) == INTEGER_CST
		&& !ವೃಕ್ಷ_int_cst_equal (st1, st2))
	     ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;

	    ವೃಕ್ಷ counted_by1 = lookup_attribute ("counted_by",
						 DECL_ಗುಣಲಕ್ಷಣಗಳು (s1));
	    ವೃಕ್ಷ counted_by2 = lookup_attribute ("counted_by",
						 DECL_ಗುಣಲಕ್ಷಣಗಳು (s2));
	    /* If there is no counted_by attribute for both fields.  */
	    ಆದರೆ (!counted_by1 && !counted_by2)
	      ಮುಂದುವರಿ;

	    /* If only one field has counted_by attribute.  */
	    ಆದರೆ ((counted_by1 && !counted_by2)
		|| (!counted_by1 && counted_by2))
	      ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;

	    /* Now both s1 and s2 have counted_by attributes, check
	       whether they are the same.  */

	    ವೃಕ್ಷ counted_by_field1
	      = lookup_ಕ್ಷೇತ್ರ (t1, ವೃಕ್ಷ_ಮೌಲ್ಯ (ವೃಕ್ಷ_ಮೌಲ್ಯ (counted_by1)));
	    ವೃಕ್ಷ counted_by_field2
	      = lookup_ಕ್ಷೇತ್ರ (t2, ವೃಕ್ಷ_ಮೌಲ್ಯ (ವೃಕ್ಷ_ಮೌಲ್ಯ (counted_by2)));

	    gcc_assert (counted_by_field1 && counted_by_field2);

	    ಆಗ (ವೃಕ್ಷ_CHAIN (counted_by_field1))
	      counted_by_field1 = ವೃಕ್ಷ_CHAIN (counted_by_field1);
	    ಆಗ (ವೃಕ್ಷ_CHAIN (counted_by_field2))
	      counted_by_field2 = ವೃಕ್ಷ_CHAIN (counted_by_field2);

	    ಆದರೆ (DECL_NAME (ವೃಕ್ಷ_ಮೌಲ್ಯ (counted_by_field1))
		!= DECL_NAME (ವೃಕ್ಷ_ಮೌಲ್ಯ (counted_by_field2)))
	      ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
	  }
	ಹಿಂತಿರುಗಿ ನಿಜ;

    ಪೂರ್ವನಿಯೋಜಿತ:
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
			     ರಚನೆ comptypes_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ)
{
  ವೃಕ್ಷ ret1 = ವೃಕ್ಷ_TYPE (f1);
  ವೃಕ್ಷ ret2 = ವೃಕ್ಷ_TYPE (f2);

  /* 'volatile' qualifiers on a function's return type used to mean
     the function is noreturn.  */
  ಆದರೆ (TYPE_VOLATILE (ret1) != TYPE_VOLATILE (ret2))
    pedwarn (ಒಳಹರಿವು_location, 0, "function return types not compatible due to %<volatile%>");
  ಆದರೆ (TYPE_VOLATILE (ret1))
    ret1 = build_qualified_type (TYPE_MAIN_VARIANT (ret1),
				 TYPE_QUALS (ret1) & ~TYPE_QUAL_VOLATILE);
  ಆದರೆ (TYPE_VOLATILE (ret2))
    ret2 = build_qualified_type (TYPE_MAIN_VARIANT (ret2),
				 TYPE_QUALS (ret2) & ~TYPE_QUAL_VOLATILE);

  ತಾರ್ಕಿಕ ignore_pargs = ದತ್ತಾಂಶ->ignore_promoting_ವಾದಗಳು;
  ದತ್ತಾಂಶ->ignore_promoting_ವಾದಗಳು = ಸುಳ್ಳು;

  ಆದರೆ (!comptypes_ಆಂತರಿಕ (ret1, ret2, ದತ್ತಾಂಶ))
    ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;

  ದತ್ತಾಂಶ->ignore_promoting_ವಾದಗಳು = ignore_pargs;

  ವೃಕ್ಷ args1 = TYPE_ARG_TYPES (f1);
  ವೃಕ್ಷ args2 = TYPE_ARG_TYPES (f2);

  ಆದರೆ ((args1 == NULL_ವೃಕ್ಷ) != (args2 == NULL_ವೃಕ್ಷ))
    ದತ್ತಾಂಶ->different_types_p = ನಿಜ;

  /* An unspecified parmlist matches any specified parmlist
     whose argument types don't need default promotions.  */

  ಆದರೆ (args1 == NULL_ವೃಕ್ಷ)
    {
      ಆದರೆ (TYPE_NO_NAMED_ವಾದಗಳು_STDARG_P (f1) != TYPE_NO_NAMED_ವಾದಗಳು_STDARG_P (f2))
	ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
      ಆದರೆ (!(ದತ್ತಾಂಶ->ignore_promoting_ವಾದಗಳು || self_promoting_ವಾದಗಳು_p (args2)))
	ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
      ದತ್ತಾಂಶ->ignore_promoting_ವಾದಗಳು = ಸುಳ್ಳು;
      /* If one of these types comes from a non-prototype fn definition,
	 compare that with the other type's arglist.
	 If they don't match, ask for a warning (but no error).  */
      ಆದರೆ (TYPE_ACTUAL_ARG_TYPES (f1)
	  && !type_lists_compatible_p (args2, TYPE_ACTUAL_ARG_TYPES (f1), ದತ್ತಾಂಶ))
	 ದತ್ತಾಂಶ->warning_needed = ನಿಜ;
      ಹಿಂತಿರುಗಿ ನಿಜ;
    }
  ಆದರೆ (args2 == NULL_ವೃಕ್ಷ)
    {
      ಆದರೆ (TYPE_NO_NAMED_ವಾದಗಳು_STDARG_P (f1) != TYPE_NO_NAMED_ವಾದಗಳು_STDARG_P (f2))
	ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
      ಆದರೆ (!(ದತ್ತಾಂಶ->ignore_promoting_ವಾದಗಳು || self_promoting_ವಾದಗಳು_p (args1)))
	ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
      ದತ್ತಾಂಶ->ignore_promoting_ವಾದಗಳು = ಸುಳ್ಳು;
      ಆದರೆ (TYPE_ACTUAL_ARG_TYPES (f2)
	  && !type_lists_compatible_p (args1, TYPE_ACTUAL_ARG_TYPES (f2), ದತ್ತಾಂಶ))
	ದತ್ತಾಂಶ->warning_needed = ನಿಜ;
      ಹಿಂತಿರುಗಿ ನಿಜ;
    }

  /* Both types have argument lists: compare them and propagate results.  */
  ಹಿಂತಿರುಗಿ type_lists_compatible_p (args1, args2, ದತ್ತಾಂಶ);
}

/* Check two lists of types for compatibility, returning false for
   incompatible, true for compatible.  */

ಸ್ಥಿರ ತಾರ್ಕಿಕ
type_lists_compatible_p (const_ವೃಕ್ಷ args1, const_ವೃಕ್ಷ args2,
			 ರಚನೆ comptypes_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ)
{
  ಆಗ (1)
    {
      ಆದರೆ (args1 == NULL_ವೃಕ್ಷ && args2 == NULL_ವೃಕ್ಷ)
	ಹಿಂತಿರುಗಿ ನಿಜ;
      /* If one list is shorter than the other,
	 they fail to match.  */
      ಆದರೆ (args1 == NULL_ವೃಕ್ಷ || args2 == NULL_ವೃಕ್ಷ)
	ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
      ವೃಕ್ಷ a1 = ವೃಕ್ಷ_ಮೌಲ್ಯ (args1);
      ವೃಕ್ಷ a2 = ವೃಕ್ಷ_ಮೌಲ್ಯ (args2);
      ವೃಕ್ಷ mv1 = remove_qualifiers (a1);
      ವೃಕ್ಷ mv2 = remove_qualifiers (a2);

      gcc_assert (mv2);
      gcc_assert (mv2);

      /* If one of the lists has an error marker, ignore this arg.  */
      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (a1) == ERROR_MARK
	       || ವೃಕ್ಷ_ಸಂಕೇತ (a2) == ERROR_MARK)
	;
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!comptypes_ಆಂತರಿಕ (mv1, mv2, ದತ್ತಾಂಶ))
	{
	  ದತ್ತಾಂಶ->different_types_p = ನಿಜ;
	  /* Allow  wait (union {union wait *u; int *i} *)
	     and  wait (union wait *)  to be compatible.  */
	  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (a1) == UNION_TYPE
	      && (TYPE_NAME (a1) == NULL_ವೃಕ್ಷ
		  || TYPE_TRANSPARENT_AGGR (a1))
	      && ವೃಕ್ಷ_ಸಂಕೇತ (TYPE_ಗಾತ್ರ (a1)) == INTEGER_CST
	      && ವೃಕ್ಷ_int_cst_equal (TYPE_ಗಾತ್ರ (a1),
				     TYPE_ಗಾತ್ರ (a2)))
	    {
	      ವೃಕ್ಷ memb;
	      ಗಾಗಿ (memb = TYPE_FIELDS (a1);
		   memb; memb = DECL_CHAIN (memb))
		{
		  ವೃಕ್ಷ mv3 = remove_qualifiers (ವೃಕ್ಷ_TYPE (memb));
		  ಆದರೆ (comptypes_ಆಂತರಿಕ (mv3, mv2, ದತ್ತಾಂಶ))
		    ನಿಲ್ಲಿಸು;
		}
	      ಆದರೆ (memb == NULL_ವೃಕ್ಷ)
		ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
	    }
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (a2) == UNION_TYPE
		   && (TYPE_NAME (a2) == NULL_ವೃಕ್ಷ
		       || TYPE_TRANSPARENT_AGGR (a2))
		   && ವೃಕ್ಷ_ಸಂಕೇತ (TYPE_ಗಾತ್ರ (a2)) == INTEGER_CST
		   && ವೃಕ್ಷ_int_cst_equal (TYPE_ಗಾತ್ರ (a2),
					  TYPE_ಗಾತ್ರ (a1)))
	    {
	      ವೃಕ್ಷ memb;
	      ಗಾಗಿ (memb = TYPE_FIELDS (a2);
		   memb; memb = DECL_CHAIN (memb))
		{
		  ವೃಕ್ಷ mv3 = remove_qualifiers (ವೃಕ್ಷ_TYPE (memb));
		  ಆದರೆ (comptypes_ಆಂತರಿಕ (mv3, mv1, ದತ್ತಾಂಶ))
		    ನಿಲ್ಲಿಸು;
		}
	      ಆದರೆ (memb == NULL_ವೃಕ್ಷ)
		ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
	    }
	  ಇಲ್ಲದಿದ್ದರೆ
	    ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
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
c_ಗಾತ್ರ_ಒಳ_ಬೈಟುಗಳು (const_ವೃಕ್ಷ type)
{
  ಎಣಿಕೆ ವೃಕ್ಷ_ಸಂಕೇತ_2 ಸಂಕೇತ_2 = ವೃಕ್ಷ_ಸಂಕೇತ (type);

  ಆದರೆ (ಸಂಕೇತ_2 == FUNCTION_TYPE || ಸಂಕೇತ_2 == VOID_TYPE || ಸಂಕೇತ_2 == ERROR_MARK
      || !COMPLETE_TYPE_P (type))
    ಹಿಂತಿರುಗಿ ಗಾತ್ರ_one_ಗಂಟು;

  /* Convert in case a char is more than one unit.  */
  ಹಿಂತಿರುಗಿ ಗಾತ್ರ_binop_loc (ಒಳಹರಿವು_location, CEIL_DIV_ಅಭಿವ್ಯಕ್ತಿ, TYPE_ಗಾತ್ರ_UNIT (type),
			 ಗಾತ್ರ_int (TYPE_PRECISION (char_type_ಗಂಟು)
				   / ಬಿಟ್ಟುಗಳು_ಪ್ರತಿ_UNIT));
}

/* Return either DECL or its known constant value (if it has one).  */

ವೃಕ್ಷ
decl_constant_ಮೌಲ್ಯ_1 (ವೃಕ್ಷ decl, ತಾರ್ಕಿಕ ಒಳ_init)
{
  ಆದರೆ (/* Note that DECL_INITIAL isn't valid for a PARM_DECL.  */
      ವೃಕ್ಷ_ಸಂಕೇತ (decl) != PARM_DECL
      && !ವೃಕ್ಷ_THIS_VOLATILE (decl)
      && ವೃಕ್ಷ_READONLY (decl)
      && DECL_INITIAL (decl) != NULL_ವೃಕ್ಷ
      && !error_ಕಾರ್ಯಾಂಶ_p (DECL_INITIAL (decl))
      /* This is invalid if initial value is not constant.
	 If it has either a function call, a memory reference,
	 or a variable, then re-evaluating it could give different results.  */
      && ವೃಕ್ಷ_CONSTANT (DECL_INITIAL (decl))
      /* Check for cases where this is sub-optimal, even though valid.  */
      && (ಒಳ_init || ವೃಕ್ಷ_ಸಂಕೇತ (DECL_INITIAL (decl)) != CONSTRUCTOR))
    ಹಿಂತಿರುಗಿ DECL_INITIAL (decl);
  ಹಿಂತಿರುಗಿ decl;
}

/* Return either DECL or its known constant value (if it has one).
   Like the above, but always return decl outside of functions.  */

ವೃಕ್ಷ
decl_constant_ಮೌಲ್ಯ (ವೃಕ್ಷ decl)
{
  /* Don't change a variable array bound or initial value to a constant
     in a place where a variable is invalid.  */
  ಹಿಂತಿರುಗಿ current_function_decl ? decl_constant_ಮೌಲ್ಯ_1 (decl, ಸುಳ್ಳು) : decl;
}

/* Convert the array expression EXP to a pointer.  */
ಸ್ಥಿರ ವೃಕ್ಷ
array_ಗಮ್ಯ_ಸೂಚಕ_conversion (location_t loc, ವೃಕ್ಷ ಘಾತಾಂಕ)
{
  ವೃಕ್ಷ orig_exp = ಘಾತಾಂಕ;
  ವೃಕ್ಷ type = ವೃಕ್ಷ_TYPE (ಘಾತಾಂಕ);
  ವೃಕ್ಷ adr;
  ವೃಕ್ಷ restype = ವೃಕ್ಷ_TYPE (type);
  ವೃಕ್ಷ ptrtype;

  gcc_assert (ವೃಕ್ಷ_ಸಂಕೇತ (type) == ARRAY_TYPE);

  STRIP_TYPE_NOPS (ಘಾತಾಂಕ);

  copy_warning (ಘಾತಾಂಕ, orig_exp);

  ptrtype = c_build_ಸೂಚಕ_type (restype);

  ಆದರೆ (ಪರೋಕ್ಷ_REF_P (ಘಾತಾಂಕ))
    ಹಿಂತಿರುಗಿ convert (ptrtype, ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (ಘಾತಾಂಕ, 0));

  /* In C++ array compound literals are temporary objects unless they are
     const or appear in namespace scope, so they are destroyed too soon
     to use them for much of anything  (c++/53220).  */
  ಆದರೆ (warn_cxx_compat && ವೃಕ್ಷ_ಸಂಕೇತ (ಘಾತಾಂಕ) == COMPOUND_LITERAL_ಅಭಿವ್ಯಕ್ತಿ)
    {
      ವೃಕ್ಷ decl = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (ಘಾತಾಂಕ, 0), 0);
      ಆದರೆ (!ವೃಕ್ಷ_READONLY (decl) && !ವೃಕ್ಷ_STATIC (decl))
	warning_at (DECL_ಮೂಲ_LOCATION (decl), OPT_Wc___compat,
		    "converting an array compound literal to a pointer "
		    "leads to a dangling pointer in C++");
    }

  adr = build_unary_op (loc, ADDR_ಅಭಿವ್ಯಕ್ತಿ, ಘಾತಾಂಕ, ನಿಜ);
  ಹಿಂತಿರುಗಿ convert (ptrtype, adr);
}

/* Convert the function expression EXP to a pointer.  */
ಸ್ಥಿರ ವೃಕ್ಷ
function_ಗಮ್ಯ_ಸೂಚಕ_conversion (location_t loc, ವೃಕ್ಷ ಘಾತಾಂಕ)
{
  ವೃಕ್ಷ orig_exp = ಘಾತಾಂಕ;

  gcc_assert (ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (ಘಾತಾಂಕ)) == FUNCTION_TYPE);

  STRIP_TYPE_NOPS (ಘಾತಾಂಕ);

  copy_warning (ಘಾತಾಂಕ, orig_exp);

  ವೃಕ್ಷ exp2 = build_unary_op (loc, ADDR_ಅಭಿವ್ಯಕ್ತಿ, ಘಾತಾಂಕ, ಸುಳ್ಳು);

  /* If the function is defined and known to not require a non-local
     context, make sure no trampoline is generated.  */
  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ಘಾತಾಂಕ) == FUNCTION_DECL
      && DECL_INITIAL (ಘಾತಾಂಕ) && !C_FUNC_NONLOCAL_CONTEXT (ಘಾತಾಂಕ))
   ವೃಕ್ಷ_NO_TRAMPOLINE (exp2) = 1;

  ಹಿಂತಿರುಗಿ exp2;
}

/* Mark EXP as read, not just set, for set but not used -Wunused
   warning purposes.  */

ಶೂನ್ಯ
mark_exp_read (ವೃಕ್ಷ ಘಾತಾಂಕ)
{
  ಆಯ್ಕೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ಘಾತಾಂಕ))
    {
    ಸ್ಥಿತಿ VAR_DECL:
    ಸ್ಥಿತಿ PARM_DECL:
      DECL_READ_P (ಘಾತಾಂಕ) = 1;
      ನಿಲ್ಲಿಸು;
    CASE_CONVERT:
      ಆದರೆ (VOID_TYPE_P (ವೃಕ್ಷ_TYPE (ಘಾತಾಂಕ)))
	ಆಯ್ಕೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (ಘಾತಾಂಕ, 0)))
	  {
	  ಸ್ಥಿತಿ PREINCREMENT_ಅಭಿವ್ಯಕ್ತಿ:
	  ಸ್ಥಿತಿ PREDECREMENT_ಅಭಿವ್ಯಕ್ತಿ:
	  ಸ್ಥಿತಿ POSTINCREMENT_ಅಭಿವ್ಯಕ್ತಿ:
	  ಸ್ಥಿತಿ POSTDECREMENT_ಅಭಿವ್ಯಕ್ತಿ:
	    ಹಿಂತಿರುಗಿ;
	  ಪೂರ್ವನಿಯೋಜಿತ:
	    ನಿಲ್ಲಿಸು;
	  }
      /* FALLTHRU */
    ಸ್ಥಿತಿ ARRAY_REF:
    ಸ್ಥಿತಿ COMPONENT_REF:
    ಸ್ಥಿತಿ MODIFY_ಅಭಿವ್ಯಕ್ತಿ:
    ಸ್ಥಿತಿ REALPART_ಅಭಿವ್ಯಕ್ತಿ:
    ಸ್ಥಿತಿ IMAGPART_ಅಭಿವ್ಯಕ್ತಿ:
    ಸ್ಥಿತಿ ADDR_ಅಭಿವ್ಯಕ್ತಿ:
    ಸ್ಥಿತಿ VIEW_CONVERT_ಅಭಿವ್ಯಕ್ತಿ:
    ಸ್ಥಿತಿ PREINCREMENT_ಅಭಿವ್ಯಕ್ತಿ:
    ಸ್ಥಿತಿ PREDECREMENT_ಅಭಿವ್ಯಕ್ತಿ:
    ಸ್ಥಿತಿ POSTINCREMENT_ಅಭಿವ್ಯಕ್ತಿ:
    ಸ್ಥಿತಿ POSTDECREMENT_ಅಭಿವ್ಯಕ್ತಿ:
      mark_exp_read (ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (ಘಾತಾಂಕ, 0));
      ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ COMPOUND_ಅಭಿವ್ಯಕ್ತಿ:
      /* Pattern match what build_atomic_assign produces with modifycode
	 NOP_EXPR.  */
      ಆದರೆ (VAR_P (ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (ಘಾತಾಂಕ, 1))
	  && DECL_ARTIFICIAL (ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (ಘಾತಾಂಕ, 1))
	  && ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (ಘಾತಾಂಕ, 0)) == COMPOUND_ಅಭಿವ್ಯಕ್ತಿ)
	{
	  ವೃಕ್ಷ t1 = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (ಘಾತಾಂಕ, 0), 0);
	  ವೃಕ್ಷ t2 = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (ಘಾತಾಂಕ, 0), 1);
	  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (t1) == ಗುರಿ_ಅಭಿವ್ಯಕ್ತಿ
	      && ಗುರಿ_ಅಭಿವ್ಯಕ್ತಿ_ಸ್ಥಾನ (t1) == ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (ಘಾತಾಂಕ, 1)
	      && ವೃಕ್ಷ_ಸಂಕೇತ (t2) == CALL_ಅಭಿವ್ಯಕ್ತಿ)
	    {
	      ವೃಕ್ಷ fndecl = get_callee_fndecl (t2);
	      ವೃಕ್ಷ arg = NULL_ವೃಕ್ಷ;
	      ಆದರೆ (fndecl
		  && ವೃಕ್ಷ_ಸಂಕೇತ (fndecl) == FUNCTION_DECL
		  && fndecl_built_ಒಳ_p (fndecl, BUILT_ಒಳ_ಸಾಮಾನ್ಯ)
		  && call_ಅಭಿವ್ಯಕ್ತಿ_nargs (t2) >= 2)
		ಆಯ್ಕೆ (DECL_FUNCTION_ಸಂಕೇತ (fndecl))
		  {
		  ಸ್ಥಿತಿ BUILT_ಒಳ_ATOMIC_STORE:
		    arg = CALL_ಅಭಿವ್ಯಕ್ತಿ_ARG (t2, 1);
		    ನಿಲ್ಲಿಸು;
		  ಸ್ಥಿತಿ BUILT_ಒಳ_ATOMIC_STORE_1:
		  ಸ್ಥಿತಿ BUILT_ಒಳ_ATOMIC_STORE_2:
		  ಸ್ಥಿತಿ BUILT_ಒಳ_ATOMIC_STORE_4:
		  ಸ್ಥಿತಿ BUILT_ಒಳ_ATOMIC_STORE_8:
		  ಸ್ಥಿತಿ BUILT_ಒಳ_ATOMIC_STORE_16:
		    arg = CALL_ಅಭಿವ್ಯಕ್ತಿ_ARG (t2, 0);
		    ನಿಲ್ಲಿಸು;
		  ಪೂರ್ವನಿಯೋಜಿತ:
		    ನಿಲ್ಲಿಸು;
		  }
	      ಆದರೆ (arg)
		{
		  STRIP_NOPS (arg);
		  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (arg) == ADDR_ಅಭಿವ್ಯಕ್ತಿ
		      && DECL_P (ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (arg, 0))
		      && TYPE_ATOMIC (ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (arg, 0))))
		    mark_exp_read (ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (arg, 0));
		}
	    }
	}
      /* FALLTHRU */
    ಸ್ಥಿತಿ C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ:
      mark_exp_read (ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (ಘಾತಾಂಕ, 1));
      ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ OMP_ARRAY_SECTION:
      mark_exp_read (ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (ಘಾತಾಂಕ, 0));
      ಆದರೆ (ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (ಘಾತಾಂಕ, 1))
	mark_exp_read (ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (ಘಾತಾಂಕ, 1));
      ಆದರೆ (ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (ಘಾತಾಂಕ, 2))
	mark_exp_read (ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (ಘಾತಾಂಕ, 2));
      ನಿಲ್ಲಿಸು;
    ಪೂರ್ವನಿಯೋಜಿತ:
      ನಿಲ್ಲಿಸು;
    }
}

/* Perform the default conversion of arrays and functions to pointers.
   Return the result of converting EXP.  For any other expression, just
   return EXP.

   LOC is the location of the expression.  */

ರಚನೆ c_ಅಭಿವ್ಯಕ್ತಿ
default_function_array_conversion (location_t loc, ರಚನೆ c_ಅಭಿವ್ಯಕ್ತಿ ಘಾತಾಂಕ)
{
  ವೃಕ್ಷ orig_exp = ಘಾತಾಂಕ.ಮೌಲ್ಯ;
  ವೃಕ್ಷ type = ವೃಕ್ಷ_TYPE (ಘಾತಾಂಕ.ಮೌಲ್ಯ);
  ಎಣಿಕೆ ವೃಕ್ಷ_ಸಂಕೇತ_2 ಸಂಕೇತ_2 = ವೃಕ್ಷ_ಸಂಕೇತ (type);

  ಆಯ್ಕೆ (ಸಂಕೇತ_2)
    {
    ಸ್ಥಿತಿ ARRAY_TYPE:
      {
	ತಾರ್ಕಿಕ not_lvalue = ಸುಳ್ಳು;
	ತಾರ್ಕಿಕ lvalue_array_p;

	ಆಗ ((ವೃಕ್ಷ_ಸಂಕೇತ (ಘಾತಾಂಕ.ಮೌಲ್ಯ) == NON_LVALUE_ಅಭಿವ್ಯಕ್ತಿ
		|| CONVERT_ಅಭಿವ್ಯಕ್ತಿ_P (ಘಾತಾಂಕ.ಮೌಲ್ಯ))
	       && ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (ಘಾತಾಂಕ.ಮೌಲ್ಯ, 0)) == type)
	  {
	    ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ಘಾತಾಂಕ.ಮೌಲ್ಯ) == NON_LVALUE_ಅಭಿವ್ಯಕ್ತಿ)
	      not_lvalue = ನಿಜ;
	    ಘಾತಾಂಕ.ಮೌಲ್ಯ = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (ಘಾತಾಂಕ.ಮೌಲ್ಯ, 0);
	  }

	copy_warning (ಘಾತಾಂಕ.ಮೌಲ್ಯ, orig_exp);

	lvalue_array_p = !not_lvalue && lvalue_p (ಘಾತಾಂಕ.ಮೌಲ್ಯ);
	ಆದರೆ (!flag_isoc99 && !lvalue_array_p)
	  {
	    /* Before C99, non-lvalue arrays do not decay to pointers.
	       Normally, using such an array would be invalid; but it can
	       be used correctly inside sizeof or as a statement expression.
	       Thus, do not give an error here; an error will result later.  */
	    ಹಿಂತಿರುಗಿ ಘಾತಾಂಕ;
	  }

	ಘಾತಾಂಕ.ಮೌಲ್ಯ = array_ಗಮ್ಯ_ಸೂಚಕ_conversion (loc, ಘಾತಾಂಕ.ಮೌಲ್ಯ);
      }
      ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ FUNCTION_TYPE:
      ಘಾತಾಂಕ.ಮೌಲ್ಯ = function_ಗಮ್ಯ_ಸೂಚಕ_conversion (loc, ಘಾತಾಂಕ.ಮೌಲ್ಯ);
      ನಿಲ್ಲಿಸು;
    ಪೂರ್ವನಿಯೋಜಿತ:
      ನಿಲ್ಲಿಸು;
    }

  ಹಿಂತಿರುಗಿ ಘಾತಾಂಕ;
}

ರಚನೆ c_ಅಭಿವ್ಯಕ್ತಿ
default_function_array_read_conversion (location_t loc, ರಚನೆ c_ಅಭಿವ್ಯಕ್ತಿ ಘಾತಾಂಕ)
{
  mark_exp_read (ಘಾತಾಂಕ.ಮೌಲ್ಯ);
  /* We only generate a call to .ACCESS_WITH_SIZE when it is a read.  */
  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ಘಾತಾಂಕ.ಮೌಲ್ಯ) == COMPONENT_REF
      && handle_counted_by_p (ಘಾತಾಂಕ.ಮೌಲ್ಯ))
    ಘಾತಾಂಕ.ಮೌಲ್ಯ = handle_counted_by_for_component_ref (loc, ಘಾತಾಂಕ.ಮೌಲ್ಯ);
  ಹಿಂತಿರುಗಿ default_function_array_conversion (loc, ಘಾತಾಂಕ);
}

/* Return whether EXPR should be treated as an atomic lvalue for the
   purposes of load and store handling.  */

ಸ್ಥಿರ ತಾರ್ಕಿಕ
really_atomic_lvalue (ವೃಕ್ಷ ಅಭಿವ್ಯಕ್ತಿ)
{
  ಆದರೆ (error_ಕಾರ್ಯಾಂಶ_p (ಅಭಿವ್ಯಕ್ತಿ))
    ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
  ಆದರೆ (!TYPE_ATOMIC (ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ)))
    ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
  ಆದರೆ (!COMPLETE_TYPE_P (ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ)))
    ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
  ಆದರೆ (!lvalue_p (ಅಭಿವ್ಯಕ್ತಿ))
    ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;

  /* Ignore _Atomic on register variables, since their addresses can't
     be taken so (a) atomicity is irrelevant and (b) the normal atomic
     sequences wouldn't work.  Ignore _Atomic on structures containing
     bit-fields, since accessing elements of atomic structures or
     unions is undefined behavior (C11 6.5.2.3#5), but it's unclear if
     it's undefined at translation time or execution time, and the
     normal atomic sequences again wouldn't work.  */
  ಆಗ (handled_component_p (ಅಭಿವ್ಯಕ್ತಿ))
    {
      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ಅಭಿವ್ಯಕ್ತಿ) == COMPONENT_REF
	  && DECL_C_ಬಿಟ್_ಕ್ಷೇತ್ರ (ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (ಅಭಿವ್ಯಕ್ತಿ, 1)))
	ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
      ಅಭಿವ್ಯಕ್ತಿ = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (ಅಭಿವ್ಯಕ್ತಿ, 0);
    }
  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ಅಭಿವ್ಯಕ್ತಿ) == COMPOUND_LITERAL_ಅಭಿವ್ಯಕ್ತಿ)
    ಅಭಿವ್ಯಕ್ತಿ = COMPOUND_LITERAL_ಅಭಿವ್ಯಕ್ತಿ_DECL (ಅಭಿವ್ಯಕ್ತಿ);
  ಆದರೆ (DECL_P (ಅಭಿವ್ಯಕ್ತಿ) && C_DECL_ರಿಜಿಸ್ಟರ್ (ಅಭಿವ್ಯಕ್ತಿ))
    ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
  ಹಿಂತಿರುಗಿ ನಿಜ;
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
  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ಅಭಿವ್ಯಕ್ತಿ) == VAR_DECL)
    decl = ಅಭಿವ್ಯಕ್ತಿ;
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ಅಭಿವ್ಯಕ್ತಿ) == COMPOUND_LITERAL_ಅಭಿವ್ಯಕ್ತಿ)
    decl = COMPOUND_LITERAL_ಅಭಿವ್ಯಕ್ತಿ_DECL (ಅಭಿವ್ಯಕ್ತಿ);
  ಆದರೆ (decl
      && C_DECL_DECLARED_CONSTEXPR (decl)
      && DECL_INITIAL (decl) != NULL_ವೃಕ್ಷ
      && !error_ಕಾರ್ಯಾಂಶ_p (DECL_INITIAL (decl)))
    ಹಿಂತಿರುಗಿ DECL_INITIAL (decl);
  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ಅಭಿವ್ಯಕ್ತಿ) != COMPONENT_REF)
    ಹಿಂತಿರುಗಿ NULL_ವೃಕ್ಷ;
  ವೃಕ್ಷ inner = maybe_get_constexpr_init (ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (ಅಭಿವ್ಯಕ್ತಿ, 0));
  ಆದರೆ (inner == NULL_ವೃಕ್ಷ)
    ಹಿಂತಿರುಗಿ NULL_ವೃಕ್ಷ;
  ಆಗ ((CONVERT_ಅಭಿವ್ಯಕ್ತಿ_P (inner) || ವೃಕ್ಷ_ಸಂಕೇತ (inner) == NON_LVALUE_ಅಭಿವ್ಯಕ್ತಿ)
	 && !error_ಕಾರ್ಯಾಂಶ_p (inner)
	 && (TYPE_MAIN_VARIANT (ವೃಕ್ಷ_TYPE (inner))
	     == TYPE_MAIN_VARIANT (ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (inner, 0)))))
    inner = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (inner, 0);
  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (inner) != CONSTRUCTOR)
    ಹಿಂತಿರುಗಿ NULL_ವೃಕ್ಷ;
  ವೃಕ್ಷ ಕ್ಷೇತ್ರ_2 = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (ಅಭಿವ್ಯಕ್ತಿ, 1);
  ಚಿಹ್ನೆರಹಿತ HOST_WIDE_INT cidx;
  ವೃಕ್ಷ cfield, cvalue;
  ತಾರ್ಕಿಕ have_other_init = ಸುಳ್ಳು;
  FOR_EACH_CONSTRUCTOR_ELT (CONSTRUCTOR_ELTS (inner), cidx, cfield, cvalue)
    {
      ಆದರೆ (cfield == ಕ್ಷೇತ್ರ_2)
	ಹಿಂತಿರುಗಿ cvalue;
      have_other_init = ನಿಜ;
    }
  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (inner)) == UNION_TYPE
      && (have_other_init || ಕ್ಷೇತ್ರ_2 != TYPE_FIELDS (ವೃಕ್ಷ_TYPE (inner))))
    ಹಿಂತಿರುಗಿ NULL_ವೃಕ್ಷ;
  /* Return a default initializer.  */
  ಆದರೆ (ದಾಖಲೆ_OR_UNION_TYPE_P (ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ)))
    ಹಿಂತಿರುಗಿ build_constructor (ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ), ಖಾಲಿ);
  ಹಿಂತಿರುಗಿ build_zero_cst (ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ));
}

/* Helper function for convert_lvalue_to_rvalue called via
   walk_tree_without_duplicates.  Find DATA inside of the expression.  */

ಸ್ಥಿರ ವೃಕ್ಷ
c_ಕಂಡುಹಿಡಿ_var_r (ವೃಕ್ಷ *tp, ಪೂರ್ಣಾಂಕ *walk_subtrees, ಶೂನ್ಯ *ದತ್ತಾಂಶ)
{
  ಆದರೆ (TYPE_P (*tp))
    *walk_subtrees = 0;
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (*tp == (ವೃಕ್ಷ) ದತ್ತಾಂಶ)
    ಹಿಂತಿರುಗಿ *tp;
  ಹಿಂತಿರುಗಿ NULL_ವೃಕ್ಷ;
}

/* Convert expression EXP (location LOC) from lvalue to rvalue,
   including converting functions and arrays to pointers if CONVERT_P.
   If READ_P, also mark the expression as having been read.  If
   FOR_INIT, constexpr expressions of structure and union type should
   be replaced by the corresponding CONSTRUCTOR; otherwise, only
   constexpr scalars (including elements of structures and unions) are
   replaced by their initializers.  */

ರಚನೆ c_ಅಭಿವ್ಯಕ್ತಿ
convert_lvalue_ಗಮ್ಯ_rvalue (location_t loc, ರಚನೆ c_ಅಭಿವ್ಯಕ್ತಿ ಘಾತಾಂಕ,
			  ತಾರ್ಕಿಕ convert_p, ತಾರ್ಕಿಕ read_p, ತಾರ್ಕಿಕ for_init)
{
  ತಾರ್ಕಿಕ force_non_npc = ಸುಳ್ಳು;
  ಆದರೆ (read_p)
    mark_exp_read (ಘಾತಾಂಕ.ಮೌಲ್ಯ);
  /* We only generate a call to .ACCESS_WITH_SIZE when it is a read.  */
  ಆದರೆ (read_p && ವೃಕ್ಷ_ಸಂಕೇತ (ಘಾತಾಂಕ.ಮೌಲ್ಯ) == COMPONENT_REF
      && handle_counted_by_p (ಘಾತಾಂಕ.ಮೌಲ್ಯ))
    ಘಾತಾಂಕ.ಮೌಲ್ಯ = handle_counted_by_for_component_ref (loc, ಘಾತಾಂಕ.ಮೌಲ್ಯ);

  ಆದರೆ (convert_p)
    ಘಾತಾಂಕ = default_function_array_conversion (loc, ಘಾತಾಂಕ);
  ಆದರೆ (!VOID_TYPE_P (ವೃಕ್ಷ_TYPE (ಘಾತಾಂಕ.ಮೌಲ್ಯ))
      || (flag_isoc2y
	  && TYPE_QUALS (ವೃಕ್ಷ_TYPE (ಘಾತಾಂಕ.ಮೌಲ್ಯ)) != TYPE_UNQUALIFIED))
    ಘಾತಾಂಕ.ಮೌಲ್ಯ = require_complete_type (loc, ಘಾತಾಂಕ.ಮೌಲ್ಯ);
  ಆದರೆ (for_init || !ದಾಖಲೆ_OR_UNION_TYPE_P (ವೃಕ್ಷ_TYPE (ಘಾತಾಂಕ.ಮೌಲ್ಯ)))
    {
      ವೃಕ್ಷ init = maybe_get_constexpr_init (ಘಾತಾಂಕ.ಮೌಲ್ಯ);
      ಆದರೆ (init != NULL_ವೃಕ್ಷ)
	{
	  /* A named constant of pointer type or type nullptr_t is not
	     a null pointer constant even if the initializer is
	     one.  */
	  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (init) == INTEGER_CST
	      && !INTEGRAL_TYPE_P (ವೃಕ್ಷ_TYPE (init))
	      && integer_zerop (init))
	    force_non_npc = ನಿಜ;
	  ಘಾತಾಂಕ.ಮೌಲ್ಯ = init;
	}
    }
  ಆದರೆ (really_atomic_lvalue (ಘಾತಾಂಕ.ಮೌಲ್ಯ))
    {
      vec<ವೃಕ್ಷ, va_gc> *params;
      ವೃಕ್ಷ nonatomic_type, tmp, tmp_addr, fndecl, func_call;
      ವೃಕ್ಷ ಅಭಿವ್ಯಕ್ತಿ_type = ವೃಕ್ಷ_TYPE (ಘಾತಾಂಕ.ಮೌಲ್ಯ);
      ವೃಕ್ಷ ಅಭಿವ್ಯಕ್ತಿ_addr = build_unary_op (loc, ADDR_ಅಭಿವ್ಯಕ್ತಿ, ಘಾತಾಂಕ.ಮೌಲ್ಯ, ಸುಳ್ಳು);
      ವೃಕ್ಷ seq_cst = build_int_cst (integer_type_ಗಂಟು, MEMMODEL_SEQ_CST);

      gcc_assert (TYPE_ATOMIC (ಅಭಿವ್ಯಕ್ತಿ_type));

      /* Expansion of a generic atomic load may require an addition
	 element, so allocate enough to prevent a resize.  */
      vec_alloc (params, 4);

      /* Remove the qualifiers for the rest of the expressions and
	 create the VAL temp variable to hold the RHS.  */
      nonatomic_type = build_qualified_type (ಅಭಿವ್ಯಕ್ತಿ_type, TYPE_UNQUALIFIED);
      tmp = create_tmp_var_raw (nonatomic_type);
      tmp_addr = build_unary_op (loc, ADDR_ಅಭಿವ್ಯಕ್ತಿ, tmp, ಸುಳ್ಳು);
      ವೃಕ್ಷ_ADDRESSABLE (tmp) = 1;
      /* Do not disable warnings for TMP even though it's artificial.
	 -Winvalid-memory-model depends on it.  */

      /* Issue __atomic_load (&expr, &tmp, SEQ_CST);  */
      fndecl = builtin_decl_explicit (BUILT_ಒಳ_ATOMIC_ತುಂಬು);
      params->ಶೀಘ್ರ_ತಳ್ಳು (ಅಭಿವ್ಯಕ್ತಿ_addr);
      params->ಶೀಘ್ರ_ತಳ್ಳು (tmp_addr);
      params->ಶೀಘ್ರ_ತಳ್ಳು (seq_cst);
      func_call = c_build_function_call_vec (loc, vNULL, fndecl, params, ಖಾಲಿ);

      /* EXPR is always read.  */
      mark_exp_read (ಘಾತಾಂಕ.ಮೌಲ್ಯ);

      /* Optimize the common case where c_build_function_call_vec
	 immediately folds __atomic_load (&expr, &tmp, SEQ_CST); into
	 tmp = __atomic_load_<N> (&expr, SEQ_CST);
	 In that case tmp is not addressable and can be initialized
	 fully by the rhs of the MODIFY_EXPR.  */
      ವೃಕ್ಷ tem = func_call;
      ಆದರೆ (CONVERT_ಅಭಿವ್ಯಕ್ತಿ_P (tem) && VOID_TYPE_P (ವೃಕ್ಷ_TYPE (tem)))
	{
	  tem = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (tem, 0);
	  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (tem) == MODIFY_ಅಭಿವ್ಯಕ್ತಿ
	      && ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (tem, 0) == tmp
	      && !walk_ವೃಕ್ಷ_without_duplicates (&ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (tem, 1),
						c_ಕಂಡುಹಿಡಿ_var_r, tmp))
	    {
	      ವೃಕ್ಷ_ADDRESSABLE (tmp) = 0;
	      func_call = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (tem, 1);
	    }
	}

      /* Return tmp which contains the value loaded.  */
      ಘಾತಾಂಕ.ಮೌಲ್ಯ = build4 (ಗುರಿ_ಅಭಿವ್ಯಕ್ತಿ, nonatomic_type, tmp, func_call,
			  NULL_ವೃಕ್ಷ, NULL_ವೃಕ್ಷ);
    }
  ಆದರೆ (convert_p && !error_ಕಾರ್ಯಾಂಶ_p (ಘಾತಾಂಕ.ಮೌಲ್ಯ)
      && (ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (ಘಾತಾಂಕ.ಮೌಲ್ಯ)) != ARRAY_TYPE))
    ಘಾತಾಂಕ.ಮೌಲ್ಯ = convert (build_qualified_type (ವೃಕ್ಷ_TYPE (ಘಾತಾಂಕ.ಮೌಲ್ಯ), TYPE_UNQUALIFIED), ಘಾತಾಂಕ.ಮೌಲ್ಯ);
  ಆದರೆ (force_non_npc)
    ಘಾತಾಂಕ.ಮೌಲ್ಯ = build1 (NOP_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (ಘಾತಾಂಕ.ಮೌಲ್ಯ), ಘಾತಾಂಕ.ಮೌಲ್ಯ);

  {
    ವೃಕ್ಷ false_ಮೌಲ್ಯ, true_ಮೌಲ್ಯ;
    ಆದರೆ (convert_p && !error_ಕಾರ್ಯಾಂಶ_p (ಘಾತಾಂಕ.ಮೌಲ್ಯ)
	&& c_hardbool_type_attr (ವೃಕ್ಷ_TYPE (ಘಾತಾಂಕ.ಮೌಲ್ಯ),
				 &false_ಮೌಲ್ಯ, &true_ಮೌಲ್ಯ))
      {
	ವೃಕ್ಷ t = save_ಅಭಿವ್ಯಕ್ತಿ (ಘಾತಾಂಕ.ಮೌಲ್ಯ);

	mark_exp_read (ಘಾತಾಂಕ.ಮೌಲ್ಯ);

	ವೃಕ್ಷ trapfn = builtin_decl_explicit (BUILT_ಒಳ_TRAP);
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

	ಘಾತಾಂಕ.ಮೌಲ್ಯ = ಅಭಿವ್ಯಕ್ತಿ;
      }
  }

  ಹಿಂತಿರುಗಿ ಘಾತಾಂಕ;
}

/* Wrapper for the overload above, same arguments but for tree rather than
   c_expr.  This is important for hardbools to decay to bools.  */

ಸ್ಥಿರ ಸಾಲೊಳಗೆ ವೃಕ್ಷ
convert_lvalue_ಗಮ್ಯ_rvalue (location_t loc, ವೃಕ್ಷ val,
			  ತಾರ್ಕಿಕ convert_p, ತಾರ್ಕಿಕ read_p, ತಾರ್ಕಿಕ for_init = ಸುಳ್ಳು)
{
  ರಚನೆ c_ಅಭಿವ್ಯಕ್ತಿ ಅಭಿವ್ಯಕ್ತಿ;
  memset (&ಅಭಿವ್ಯಕ್ತಿ, 0, ಗಾತ್ರ (ಅಭಿವ್ಯಕ್ತಿ));
  ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ = val;
  ಅಭಿವ್ಯಕ್ತಿ = convert_lvalue_ಗಮ್ಯ_rvalue (loc, ಅಭಿವ್ಯಕ್ತಿ, convert_p, read_p, for_init);
  ಹಿಂತಿರುಗಿ ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ;
}

/* EXP is an expression of integer type.  Apply the integer promotions
   to it and return the promoted value.  */

ವೃಕ್ಷ
perform_integral_promotions (ವೃಕ್ಷ ಘಾತಾಂಕ)
{
  ವೃಕ್ಷ type = ವೃಕ್ಷ_TYPE (ಘಾತಾಂಕ);
  ಎಣಿಕೆ ವೃಕ್ಷ_ಸಂಕೇತ_2 ಸಂಕೇತ_2 = ವೃಕ್ಷ_ಸಂಕೇತ (type);

  gcc_assert (INTEGRAL_TYPE_P (type));

  /* Convert enums to the result of applying the integer promotions to
     their underlying type.  */
  ಆದರೆ (ಸಂಕೇತ_2 == ENUMERAL_TYPE)
    {
      type = ENUM_UNDERLYING_TYPE (type);
      ಆದರೆ (c_promoting_integer_type_p (type))
	{
	  ಆದರೆ (TYPE_UNSIGNED (type)
	      && TYPE_PRECISION (type) == TYPE_PRECISION (integer_type_ಗಂಟು))
	    type = unsigned_type_ಗಂಟು;
	  ಇಲ್ಲದಿದ್ದರೆ
	    type = integer_type_ಗಂಟು;
	}

      ಹಿಂತಿರುಗಿ convert (type, ಘಾತಾಂಕ);
    }

  /* ??? This should no longer be needed now bit-fields have their
     proper types.  */
  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ಘಾತಾಂಕ) == COMPONENT_REF
      && DECL_C_ಬಿಟ್_ಕ್ಷೇತ್ರ (ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (ಘಾತಾಂಕ, 1)))
    {
      ಆದರೆ (BITINT_TYPE_P (DECL_ಬಿಟ್_ಕ್ಷೇತ್ರ_TYPE (ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (ಘಾತಾಂಕ, 1))))
	{
	  ವೃಕ್ಷ btype = DECL_ಬಿಟ್_ಕ್ಷೇತ್ರ_TYPE (ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (ಘಾತಾಂಕ, 1));
	  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (btype) == BITINT_TYPE)
	    ಹಿಂತಿರುಗಿ convert (btype, ಘಾತಾಂಕ);
	  ಇಲ್ಲದಿದ್ದರೆ
	    ಹಿಂತಿರುಗಿ convert (ENUM_UNDERLYING_TYPE (btype), ಘಾತಾಂಕ);
	}
      /* If it's thinner than an int, promote it like a
	 c_promoting_integer_type_p, otherwise leave it alone.  */
      ಆದರೆ (compare_ವೃಕ್ಷ_int (DECL_ಗಾತ್ರ (ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (ಘಾತಾಂಕ, 1)),
			    TYPE_PRECISION (integer_type_ಗಂಟು)) < 0)
	ಹಿಂತಿರುಗಿ convert (integer_type_ಗಂಟು, ಘಾತಾಂಕ);
    }

  ಆದರೆ (c_promoting_integer_type_p (type))
    {
      /* Preserve unsignedness if not really getting any wider.  */
      ಆದರೆ (TYPE_UNSIGNED (type)
	  && TYPE_PRECISION (type) == TYPE_PRECISION (integer_type_ಗಂಟು))
	ಹಿಂತಿರುಗಿ convert (unsigned_type_ಗಂಟು, ಘಾತಾಂಕ);

      ಹಿಂತಿರುಗಿ convert (integer_type_ಗಂಟು, ಘಾತಾಂಕ);
    }

  ಹಿಂತಿರುಗಿ ಘಾತಾಂಕ;
}


/* Perform default promotions for C data used in expressions.
   Enumeral types or short or char are converted to int.
   In addition, manifest constants symbols are replaced by their values.  */

ವೃಕ್ಷ
default_conversion (ವೃಕ್ಷ ಘಾತಾಂಕ)
{
  ವೃಕ್ಷ orig_exp;
  ವೃಕ್ಷ type = ವೃಕ್ಷ_TYPE (ಘಾತಾಂಕ);
  ಎಣಿಕೆ ವೃಕ್ಷ_ಸಂಕೇತ_2 ಸಂಕೇತ_2 = ವೃಕ್ಷ_ಸಂಕೇತ (type);
  ವೃಕ್ಷ promoted_type;

  mark_exp_read (ಘಾತಾಂಕ);
  /* We only generate a call to .ACCESS_WITH_SIZE when it is a read.  */
  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ಘಾತಾಂಕ) == COMPONENT_REF
      && handle_counted_by_p (ಘಾತಾಂಕ))
    ಘಾತಾಂಕ = handle_counted_by_for_component_ref (ಅಭಿವ್ಯಕ್ತಿ_LOCATION (ಘಾತಾಂಕ), ಘಾತಾಂಕ);

  /* Functions and arrays have been converted during parsing.  */
  gcc_assert (ಸಂಕೇತ_2 != FUNCTION_TYPE);
  ಆದರೆ (ಸಂಕೇತ_2 == ARRAY_TYPE)
    ಹಿಂತಿರುಗಿ ಘಾತಾಂಕ;

  /* Constants can be used directly unless they're not loadable.  */
  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ಘಾತಾಂಕ) == CONST_DECL)
    ಘಾತಾಂಕ = DECL_INITIAL (ಘಾತಾಂಕ);

  /* Strip no-op conversions.  */
  orig_exp = ಘಾತಾಂಕ;
  STRIP_TYPE_NOPS (ಘಾತಾಂಕ);

  copy_warning (ಘಾತಾಂಕ, orig_exp);

  ಆದರೆ (ಸಂಕೇತ_2 == VOID_TYPE)
    {
      error_at (ಅಭಿವ್ಯಕ್ತಿ_LOC_OR_LOC (ಘಾತಾಂಕ, ಒಳಹರಿವು_location),
		"void value not ignored as it ought to be");
      ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
    }

  ಘಾತಾಂಕ = require_complete_type (ಅಭಿವ್ಯಕ್ತಿ_LOC_OR_LOC (ಘಾತಾಂಕ, ಒಳಹರಿವು_location), ಘಾತಾಂಕ);
  ಆದರೆ (ಘಾತಾಂಕ == error_mark_ಗಂಟು)
    ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;

  promoted_type = targetm.promoted_type (type);
  ಆದರೆ (promoted_type)
    ಹಿಂತಿರುಗಿ convert (promoted_type, ಘಾತಾಂಕ);

  ಆದರೆ (INTEGRAL_TYPE_P (type))
    {
      /* Avoid performing integral promotion of bit-precise integer
	 type bit-field to its corresponding bit-precise integer if
	 orig_exp is a cast to it to its underlying type.  */
      ಆದರೆ (orig_exp != ಘಾತಾಂಕ
	  && ವೃಕ್ಷ_ಸಂಕೇತ (ಘಾತಾಂಕ) == COMPONENT_REF
	  && DECL_C_ಬಿಟ್_ಕ್ಷೇತ್ರ (ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (ಘಾತಾಂಕ, 1))
	  && BITINT_TYPE_P (DECL_ಬಿಟ್_ಕ್ಷೇತ್ರ_TYPE (ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (ಘಾತಾಂಕ, 1))))
	ಹಿಂತಿರುಗಿ perform_integral_promotions (orig_exp);
      ಹಿಂತಿರುಗಿ perform_integral_promotions (ಘಾತಾಂಕ);
    }

  ಹಿಂತಿರುಗಿ ಘಾತಾಂಕ;
}

/* Look up COMPONENT in a structure or union TYPE.

   If the component name is not found, returns NULL_TREE.  Otherwise,
   the return value is a TREE_LIST, with each TREE_VALUE a FIELD_DECL
   stepping down the chain to the component, which is in the last
   TREE_VALUE of the list.  Normally the list is of length one, but if
   the component is embedded within (nested) anonymous structures or
   unions, the list steps down the chain to the component.  */

ವೃಕ್ಷ
lookup_ಕ್ಷೇತ್ರ (const_ವೃಕ್ಷ type, ವೃಕ್ಷ component)
{
  ವೃಕ್ಷ ಕ್ಷೇತ್ರ_2;

  /* If TYPE_LANG_SPECIFIC is set, then it is a sorted array of pointers
     to the field elements.  Use a binary search on this array to quickly
     find the element.  Otherwise, do a linear search.  TYPE_LANG_SPECIFIC
     will always be set for structures which have many elements.

     Duplicate field checking replaces duplicates with NULL_TREE so
     TYPE_LANG_SPECIFIC arrays are potentially no longer sorted.  In that
     case just iterate using DECL_CHAIN.  */

  ಆದರೆ (TYPE_LANG_SPECIFIC (type) && TYPE_LANG_SPECIFIC (type)->s
      && !ನೋಡಿದ_error ())
    {
      ಪೂರ್ಣಾಂಕ bot, ತುದಿ, half;
      ವೃಕ್ಷ *ಕ್ಷೇತ್ರ_array = &TYPE_LANG_SPECIFIC (type)->s->elts[0];

      ಕ್ಷೇತ್ರ_2 = TYPE_FIELDS (type);
      bot = 0;
      ತುದಿ = TYPE_LANG_SPECIFIC (type)->s->len;
      ಆಗ (ತುದಿ - bot > 1)
	{
	  half = (ತುದಿ - bot + 1) >> 1;
	  ಕ್ಷೇತ್ರ_2 = ಕ್ಷೇತ್ರ_array[bot+half];

	  ಆದರೆ (DECL_NAME (ಕ್ಷೇತ್ರ_2) == NULL_ವೃಕ್ಷ)
	    {
	      /* Step through all anon unions in linear fashion.  */
	      ಆಗ (DECL_NAME (ಕ್ಷೇತ್ರ_array[bot]) == NULL_ವೃಕ್ಷ)
		{
		  ಕ್ಷೇತ್ರ_2 = ಕ್ಷೇತ್ರ_array[bot++];
		  ಆದರೆ (ದಾಖಲೆ_OR_UNION_TYPE_P (ವೃಕ್ಷ_TYPE (ಕ್ಷೇತ್ರ_2)))
		    {
		      ವೃಕ್ಷ anon = lookup_ಕ್ಷೇತ್ರ (ವೃಕ್ಷ_TYPE (ಕ್ಷೇತ್ರ_2), component);

		      ಆದರೆ (anon)
			ಹಿಂತಿರುಗಿ ವೃಕ್ಷ_cons (NULL_ವೃಕ್ಷ, ಕ್ಷೇತ್ರ_2, anon);

		      /* The Plan 9 compiler permits referring
			 directly to an anonymous struct/union field
			 using a typedef name.  */
		      ಆದರೆ (flag_plan9_extensions
			  && TYPE_NAME (ವೃಕ್ಷ_TYPE (ಕ್ಷೇತ್ರ_2)) != NULL_ವೃಕ್ಷ
			  && (ವೃಕ್ಷ_ಸಂಕೇತ (TYPE_NAME (ವೃಕ್ಷ_TYPE (ಕ್ಷೇತ್ರ_2)))
			      == TYPE_DECL)
			  && (DECL_NAME (TYPE_NAME (ವೃಕ್ಷ_TYPE (ಕ್ಷೇತ್ರ_2)))
			      == component))
			ನಿಲ್ಲಿಸು;
		    }
		}

	      /* Entire record is only anon unions.  */
	      ಆದರೆ (bot > ತುದಿ)
		ಹಿಂತಿರುಗಿ NULL_ವೃಕ್ಷ;

	      /* Restart the binary search, with new lower bound.  */
	      ಮುಂದುವರಿ;
	    }

	  ಆದರೆ (DECL_NAME (ಕ್ಷೇತ್ರ_2) == component)
	    ನಿಲ್ಲಿಸು;
	  ಆದರೆ (DECL_NAME (ಕ್ಷೇತ್ರ_2) < component)
	    bot += half;
	  ಇಲ್ಲದಿದ್ದರೆ
	    ತುದಿ = bot + half;
	}

      ಆದರೆ (DECL_NAME (ಕ್ಷೇತ್ರ_array[bot]) == component)
	ಕ್ಷೇತ್ರ_2 = ಕ್ಷೇತ್ರ_array[bot];
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (DECL_NAME (ಕ್ಷೇತ್ರ_2) != component)
	ಹಿಂತಿರುಗಿ NULL_ವೃಕ್ಷ;
    }
  ಇಲ್ಲದಿದ್ದರೆ
    {
      ಗಾಗಿ (ಕ್ಷೇತ್ರ_2 = TYPE_FIELDS (type); ಕ್ಷೇತ್ರ_2; ಕ್ಷೇತ್ರ_2 = DECL_CHAIN (ಕ್ಷೇತ್ರ_2))
	{
	  ಆದರೆ (DECL_NAME (ಕ್ಷೇತ್ರ_2) == NULL_ವೃಕ್ಷ
	      && ದಾಖಲೆ_OR_UNION_TYPE_P (ವೃಕ್ಷ_TYPE (ಕ್ಷೇತ್ರ_2)))
	    {
	      ವೃಕ್ಷ anon = lookup_ಕ್ಷೇತ್ರ (ವೃಕ್ಷ_TYPE (ಕ್ಷೇತ್ರ_2), component);

	      ಆದರೆ (anon)
		ಹಿಂತಿರುಗಿ ವೃಕ್ಷ_cons (NULL_ವೃಕ್ಷ, ಕ್ಷೇತ್ರ_2, anon);

	      /* The Plan 9 compiler permits referring directly to an
		 anonymous struct/union field using a typedef
		 name.  */
	      ಆದರೆ (flag_plan9_extensions
		  && TYPE_NAME (ವೃಕ್ಷ_TYPE (ಕ್ಷೇತ್ರ_2)) != NULL_ವೃಕ್ಷ
		  && ವೃಕ್ಷ_ಸಂಕೇತ (TYPE_NAME (ವೃಕ್ಷ_TYPE (ಕ್ಷೇತ್ರ_2))) == TYPE_DECL
		  && (DECL_NAME (TYPE_NAME (ವೃಕ್ಷ_TYPE (ಕ್ಷೇತ್ರ_2)))
		      == component))
		ನಿಲ್ಲಿಸು;
	    }

	  ಆದರೆ (DECL_NAME (ಕ್ಷೇತ್ರ_2) == component)
	    ನಿಲ್ಲಿಸು;
	}

      ಆದರೆ (ಕ್ಷೇತ್ರ_2 == NULL_ವೃಕ್ಷ)
	ಹಿಂತಿರುಗಿ NULL_ವೃಕ್ಷ;
    }

  ಹಿಂತಿರುಗಿ ವೃಕ್ಷ_cons (NULL_ವೃಕ್ಷ, ಕ್ಷೇತ್ರ_2, NULL_ವೃಕ್ಷ);
}

/* Recursively append candidate IDENTIFIER_NODEs to CANDIDATES.  */

ಸ್ಥಿರ ಶೂನ್ಯ
lookup_ಕ್ಷೇತ್ರ_fuzzy_ಕಂಡುಹಿಡಿ_candidates (ವೃಕ್ಷ type, ವೃಕ್ಷ component,
				    vec<ವೃಕ್ಷ> *candidates)
{
  ವೃಕ್ಷ ಕ್ಷೇತ್ರ_2;
  ಗಾಗಿ (ಕ್ಷೇತ್ರ_2 = TYPE_FIELDS (type); ಕ್ಷೇತ್ರ_2; ಕ್ಷೇತ್ರ_2 = DECL_CHAIN (ಕ್ಷೇತ್ರ_2))
    {
      ಆದರೆ (DECL_NAME (ಕ್ಷೇತ್ರ_2) == NULL_ವೃಕ್ಷ
	  && ದಾಖಲೆ_OR_UNION_TYPE_P (ವೃಕ್ಷ_TYPE (ಕ್ಷೇತ್ರ_2)))
	lookup_ಕ್ಷೇತ್ರ_fuzzy_ಕಂಡುಹಿಡಿ_candidates (ವೃಕ್ಷ_TYPE (ಕ್ಷೇತ್ರ_2), component,
					    candidates);

      ಆದರೆ (DECL_NAME (ಕ್ಷೇತ್ರ_2))
	candidates->ಸುರಕ್ಷಿತ_ತಳ್ಳು (DECL_NAME (ಕ್ಷೇತ್ರ_2));
    }
}

/* Like "lookup_field", but find the closest matching IDENTIFIER_NODE,
   rather than returning a TREE_LIST for an exact match.  */

ಸ್ಥಿರ ವೃಕ್ಷ
lookup_ಕ್ಷೇತ್ರ_fuzzy (ವೃಕ್ಷ type, ವೃಕ್ಷ component)
{
  gcc_assert (ವೃಕ್ಷ_ಸಂಕೇತ (component) == IDENTIFIER_ಗಂಟು);

  /* First, gather a list of candidates.  */
  auto_vec <ವೃಕ್ಷ> candidates;

  lookup_ಕ್ಷೇತ್ರ_fuzzy_ಕಂಡುಹಿಡಿ_candidates (type, component,
				      &candidates);

  ಹಿಂತಿರುಗಿ ಕಂಡುಹಿಡಿ_closest_identifier (component, &candidates);
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
  ಆದರೆ (c_dialect_objc ())
    ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;

  /* Only suggest it for pointers...  */
  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (datum_type) != ಸೂಚಕ_TYPE)
    ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;

  /* ...to structs/unions.  */
  ವೃಕ್ಷ underlying_type = ವೃಕ್ಷ_TYPE (datum_type);
  ಎಣಿಕೆ ವೃಕ್ಷ_ಸಂಕೇತ_2 ಸಂಕೇತ_2 = ವೃಕ್ಷ_ಸಂಕೇತ (underlying_type);
  ಆದರೆ (ಸಂಕೇತ_2 == ದಾಖಲೆ_TYPE || ಸಂಕೇತ_2 == UNION_TYPE)
    ಹಿಂತಿರುಗಿ ನಿಜ;
  ಇಲ್ಲದಿದ್ದರೆ
    ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
}

/* Give a component ref REF, decide whether we should handle its counted_by
   attribute based on its context:
   Do not handle counted_by when in offsetof, typeof and alignof operator.  */

ಸ್ಥಿರ ತಾರ್ಕಿಕ
handle_counted_by_p (ವೃಕ್ಷ ref)
{
  gcc_assert (ವೃಕ್ಷ_ಸಂಕೇತ (ref) == COMPONENT_REF);
  ವೃಕ್ಷ datum = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (ref, 0);
  /* If the component_ref is build for a offsetof, i.e., the datum
     of the component_ref is a indirect_ref of null_pointer_node,
     we should not generate call to .ACCESS_WITH_SIZE.  */
  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (datum) == ಪರೋಕ್ಷ_REF
      && ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (datum, 0) == null_ಸೂಚಕ_ಗಂಟು)
    ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
  ಆದರೆ (ಒಳ_typeof || ಒಳ_alignof)
    ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
  ಹಿಂತಿರುಗಿ ನಿಜ;
}

/* Given a component ref REF, if there is a counted_by attribute attached,
   issue error when the element_type is a structure or union including a
   flexible array member.  */

ಸ್ಥಿರ ಶೂನ್ಯ
check_counted_by_attribute (location_t loc, ವೃಕ್ಷ ref)
{
  ವೃಕ್ಷ subdatum = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (ref, 1);
  ವೃಕ್ಷ sub_type = ವೃಕ್ಷ_TYPE (subdatum);

  ಆದರೆ (!flexible_array_member_type_p (sub_type)
      && ವೃಕ್ಷ_ಸಂಕೇತ (sub_type) != ಸೂಚಕ_TYPE)
    ಹಿಂತಿರುಗಿ;

  ವೃಕ್ಷ element_type = ವೃಕ್ಷ_TYPE (sub_type);

  ವೃಕ್ಷ attr_counted_by = lookup_attribute ("counted_by",
					   DECL_ಗುಣಲಕ್ಷಣಗಳು (subdatum));
  ಆದರೆ (attr_counted_by)
    {
      /* Issue error when the element_type is a structure or
	union including a flexible array member.  */
      ಆದರೆ (ದಾಖಲೆ_OR_UNION_TYPE_P (element_type)
	  && TYPE_INCLUDES_FLEXARRAY (element_type))
	{
	  error_at (loc,
		    "%<counted_by%> attribute is not allowed for a pointer to"
		    " structure or union with flexible array member");
	  ಹಿಂತಿರುಗಿ;
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
  ಆದರೆ (!flexible_array_member_type_p (sub_type)
      && ವೃಕ್ಷ_ಸಂಕೇತ (sub_type) != ಸೂಚಕ_TYPE)
    ಹಿಂತಿರುಗಿ NULL_ವೃಕ್ಷ;

  ವೃಕ್ಷ attr_counted_by = lookup_attribute ("counted_by",
					   DECL_ಗುಣಲಕ್ಷಣಗಳು (subdatum));
  ಆದರೆ (!attr_counted_by)
    ಹಿಂತಿರುಗಿ NULL_ವೃಕ್ಷ;

  ವೃಕ್ಷ counted_by_ref = NULL_ವೃಕ್ಷ;
  *counted_by_type = NULL_ವೃಕ್ಷ;

  ವೃಕ್ಷ type = ವೃಕ್ಷ_TYPE (datum);

  /* If the type of the containing structure is an anonymous struct/union,
     and this anonymous struct/union is not a root type, get the first
     outer named structure/union type.  */
  ಆಗ (ವೃಕ್ಷ_ಸಂಕೇತ (datum) == COMPONENT_REF
	 && c_type_ಟ್ಯಾಗ್ (type) == NULL_ವೃಕ್ಷ
	 && DECL_NAME (ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (datum, 1)) == NULL_ವೃಕ್ಷ)
    {
      datum = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (datum, 0);
      type = ವೃಕ್ಷ_TYPE (datum);
    }

  ವೃಕ್ಷ ಕ್ಷೇತ್ರ_id = ವೃಕ್ಷ_ಮೌಲ್ಯ (ವೃಕ್ಷ_ಮೌಲ್ಯ (attr_counted_by));
  ವೃಕ್ಷ counted_by_ಕ್ಷೇತ್ರ = lookup_ಕ್ಷೇತ್ರ (type, ಕ್ಷೇತ್ರ_id);
  gcc_assert (counted_by_ಕ್ಷೇತ್ರ);

  ವೃಕ್ಷ counted_by_subdatum;
  ಮಾಡು
    {
      counted_by_subdatum = ವೃಕ್ಷ_ಮೌಲ್ಯ (counted_by_ಕ್ಷೇತ್ರ);
      /* Get the TYPE of the counted_by field.  */
      *counted_by_type = ವೃಕ್ಷ_TYPE (counted_by_subdatum);

      counted_by_ref
	= build3 (COMPONENT_REF, ವೃಕ್ಷ_TYPE (counted_by_subdatum),
		  datum, counted_by_subdatum, NULL_ವೃಕ್ಷ);

      datum = counted_by_ref;
      counted_by_ಕ್ಷೇತ್ರ = ವೃಕ್ಷ_CHAIN (counted_by_ಕ್ಷೇತ್ರ);
    }
  ಆಗ (counted_by_ಕ್ಷೇತ್ರ);

  counted_by_ref = build_fold_addr_ಅಭಿವ್ಯಕ್ತಿ (counted_by_ref);
  ಹಿಂತಿರುಗಿ counted_by_ref;
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
build_access_with_ಗಾತ್ರ_for_counted_by (location_t loc, ವೃಕ್ಷ ref,
				       ವೃಕ್ಷ counted_by_ref,
				       ವೃಕ್ಷ counted_by_type)
{
  gcc_assert (flexible_array_member_type_p (ವೃಕ್ಷ_TYPE (ref))
	      || ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (ref)) == ಸೂಚಕ_TYPE);

  ತಾರ್ಕಿಕ is_fam = flexible_array_member_type_p (ವೃಕ್ಷ_TYPE (ref));

  /* The result type of the call is a pointer to the flexible array type;
     or is the original pointer type to the pointer field with counted_by.  */
  ವೃಕ್ಷ ಫಲಿತಾಂಶ_type = is_fam ? c_build_ಸೂಚಕ_type (ವೃಕ್ಷ_TYPE (ref))
		     : ವೃಕ್ಷ_TYPE (ref);

  ವೃಕ್ಷ element_type = ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_TYPE (ref));
  ವೃಕ್ಷ element_ಗಾತ್ರ = VOID_TYPE_P (element_type)
		      ? ಗಾತ್ರ_one_ಗಂಟು
		      : TYPE_ಗಾತ್ರ_UNIT (element_type);
  ಆದರೆ (element_ಗಾತ್ರ == NULL_ವೃಕ್ಷ)
    ಹಿಂತಿರುಗಿ ref;

  ವೃಕ್ಷ ಮೊದಲ_param = is_fam
		     ? c_fully_fold (array_ಗಮ್ಯ_ಸೂಚಕ_conversion (loc, ref),
				     ಸುಳ್ಳು, ಖಾಲಿ)
		     : c_fully_fold (ref, ಸುಳ್ಳು, ಖಾಲಿ);
  ವೃಕ್ಷ ಎರಡನೇ_param
    = c_fully_fold (counted_by_ref, ಸುಳ್ಳು, ಖಾಲಿ);
  ವೃಕ್ಷ ಮೂರನೇ_param = build_int_cst (c_build_ಸೂಚಕ_type (counted_by_type), 0);

  ವೃಕ್ಷ call
    = build_call_ಅಭಿವ್ಯಕ್ತಿ_ಆಂತರಿಕ_loc (loc, IFN_ACCESS_WITH_ಗಾತ್ರ,
				    ಫಲಿತಾಂಶ_type, 4,
				    ಮೊದಲ_param,
				    ಎರಡನೇ_param,
				    ಮೂರನೇ_param,
				    element_ಗಾತ್ರ);

  /* Wrap the call with an INDIRECT_REF with the flexible array type.  */
  ಆದರೆ (is_fam)
    call = build1 (ಪರೋಕ್ಷ_REF, ವೃಕ್ಷ_TYPE (ref), call);
  ಗಣ_ಅಭಿವ್ಯಕ್ತಿ_LOCATION (call, loc);
  ಹಿಂತಿರುಗಿ call;
}

/* For the COMPONENT_REF ref, check whether it has a counted_by attribute,
   if so, wrap this COMPONENT_REF with the corresponding CALL to the
   function .ACCESS_WITH_SIZE.
   Otherwise, return the ref itself.  */

ವೃಕ್ಷ
handle_counted_by_for_component_ref (location_t loc, ವೃಕ್ಷ ref)
{
  gcc_assert (ವೃಕ್ಷ_ಸಂಕೇತ (ref) == COMPONENT_REF);
  ವೃಕ್ಷ datum = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (ref, 0);
  ವೃಕ್ಷ subdatum = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (ref, 1);
  ವೃಕ್ಷ counted_by_type = NULL_ವೃಕ್ಷ;

  ಆದರೆ (!(flexible_array_member_type_p (ವೃಕ್ಷ_TYPE (ref))
	|| ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (ref)) == ಸೂಚಕ_TYPE))
    ಹಿಂತಿರುಗಿ ref;

  ವೃಕ್ಷ counted_by_ref = build_counted_by_ref (datum, subdatum,
					      &counted_by_type);
  ಆದರೆ (counted_by_ref)
    ref = build_access_with_ಗಾತ್ರ_for_counted_by (loc, ref,
						 counted_by_ref,
						 counted_by_type);
  ಹಿಂತಿರುಗಿ ref;
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
  ಎಣಿಕೆ ವೃಕ್ಷ_ಸಂಕೇತ_2 ಸಂಕೇತ_2 = ವೃಕ್ಷ_ಸಂಕೇತ (type);
  ವೃಕ್ಷ ಕ್ಷೇತ್ರ_2 = ಖಾಲಿ;
  ವೃಕ್ಷ ref;
  ತಾರ್ಕಿಕ datum_lvalue = lvalue_p (datum);

  ಆದರೆ (!objc_is_ಬಹಿರಂಗ (datum, component))
    ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;

  /* Detect Objective-C property syntax object.property.  */
  ಆದರೆ (c_dialect_objc ()
      && (ref = objc_maybe_build_component_ref (datum, component)))
    ಹಿಂತಿರುಗಿ ref;

  /* See if there is a field or component with name COMPONENT.  */

  ಆದರೆ (ಸಂಕೇತ_2 == ದಾಖಲೆ_TYPE || ಸಂಕೇತ_2 == UNION_TYPE)
    {
      ಆದರೆ (!COMPLETE_TYPE_P (type))
	{
	  c_incomplete_type_error (loc, NULL_ವೃಕ್ಷ, type);
	  ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
	}

      ಕ್ಷೇತ್ರ_2 = lookup_ಕ್ಷೇತ್ರ (type, component);

      ಆದರೆ (!ಕ್ಷೇತ್ರ_2)
	{
	  ವೃಕ್ಷ guessed_id = lookup_ಕ್ಷೇತ್ರ_fuzzy (type, component);
	  ಆದರೆ (guessed_id)
	    {
	      /* Attempt to provide a fixit replacement hint, if
		 we have a valid range for the component.  */
	      location_t reported_loc
		= (component_loc != UNKNOWN_LOCATION) ? component_loc : loc;
	      gcc_rich_location rich_loc (reported_loc);
	      ಆದರೆ (component_loc != UNKNOWN_LOCATION)
		rich_loc.ಕೂಡಿಸು_fixit_misspelled_id (component_loc, guessed_id);
	      error_at (&rich_loc,
			"%qT has no member named %qE; did you mean %qE?",
			type, component, guessed_id);
	    }
	  ಇಲ್ಲದಿದ್ದರೆ
	    error_at (loc, "%qT has no member named %qE", type, component);
	  ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
	}

      /* Accessing elements of atomic structures or unions is undefined
	 behavior (C11 6.5.2.3#5).  */
      ಆದರೆ (TYPE_ATOMIC (type) && c_inhibit_evaluation_warnings == 0)
	{
	  ಆದರೆ (ಸಂಕೇತ_2 == ದಾಖಲೆ_TYPE)
	    warning_at (loc, 0, "accessing a member %qE of an atomic "
			"structure %qE", component, datum);
	  ಇಲ್ಲದಿದ್ದರೆ
	    warning_at (loc, 0, "accessing a member %qE of an atomic "
			"union %qE", component, datum);
	}

      /* Chain the COMPONENT_REFs if necessary down to the FIELD.
	 This might be better solved in future the way the C++ front
	 end does it - by giving the anonymous entities each a
	 separate name and type, and then have build_component_ref
	 recursively call itself.  We can't do that here.  */
      ಮಾಡು
	{
	  ವೃಕ್ಷ subdatum = ವೃಕ್ಷ_ಮೌಲ್ಯ (ಕ್ಷೇತ್ರ_2);
	  ಪೂರ್ಣಾಂಕ quals;
	  ವೃಕ್ಷ subtype;
	  ತಾರ್ಕಿಕ use_datum_quals;

	  ಆದರೆ (ವೃಕ್ಷ_TYPE (subdatum) == error_mark_ಗಂಟು)
	    ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;

	  /* If this is an rvalue, it does not have qualifiers in C
	     standard terms and we must avoid propagating such
	     qualifiers down to a non-lvalue array that is then
	     converted to a pointer.  */
	  use_datum_quals = (datum_lvalue
			     || ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (subdatum)) != ARRAY_TYPE);

	  quals = TYPE_QUALS (strip_array_types (ವೃಕ್ಷ_TYPE (subdatum)));
	  ಆದರೆ (use_datum_quals)
	    quals |= TYPE_QUALS (ವೃಕ್ಷ_TYPE (datum));
	  subtype = c_build_qualified_type (ವೃಕ್ಷ_TYPE (subdatum), quals);

	  ref = build3 (COMPONENT_REF, subtype, datum, subdatum,
			NULL_ವೃಕ್ಷ);
	  ಗಣ_ಅಭಿವ್ಯಕ್ತಿ_LOCATION (ref, loc);

	  check_counted_by_attribute (loc, ref);

	  ಆದರೆ (ವೃಕ್ಷ_READONLY (subdatum)
	      || (use_datum_quals && ವೃಕ್ಷ_READONLY (datum)))
	    ವೃಕ್ಷ_READONLY (ref) = 1;
	  ಆದರೆ (ವೃಕ್ಷ_THIS_VOLATILE (subdatum)
	      || (use_datum_quals && ವೃಕ್ಷ_THIS_VOLATILE (datum)))
	    ವೃಕ್ಷ_THIS_VOLATILE (ref) = 1;

	  ಆದರೆ (ವೃಕ್ಷ_UNAVAILABLE (subdatum))
	    error_unavailable_use (subdatum, NULL_ವೃಕ್ಷ);
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ವೃಕ್ಷ_DEPRECATED (subdatum))
	    warn_deprecated_use (subdatum, NULL_ವೃಕ್ಷ);

	  datum = ref;

	  ಕ್ಷೇತ್ರ_2 = ವೃಕ್ಷ_CHAIN (ಕ್ಷೇತ್ರ_2);
	}
      ಆಗ (ಕ್ಷೇತ್ರ_2);

      ಹಿಂತಿರುಗಿ ref;
    }
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (should_suggest_deref_p (type))
    {
      /* Special-case the error message for "ptr.field" for the case
	 where the user has confused "." vs "->".  */
      rich_location richloc (ಸಾಲು_ಕೋಷ್ಟಕ, loc);
      ಆದರೆ (ಪರೋಕ್ಷ_REF_P (datum) && arrow_loc != UNKNOWN_LOCATION)
	{
	  richloc.ಕೂಡಿಸು_fixit_ಸೇರಿಸು_before (arrow_loc, "(*");
	  richloc.ಕೂಡಿಸು_fixit_ಸೇರಿಸು_after (arrow_loc, ")");
	  error_at (&richloc,
		    "%qE is a pointer to pointer; did you mean to dereference "
		    "it before applying %<->%> to it?",
		    ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (datum, 0));
	}
      ಇಲ್ಲದಿದ್ದರೆ
	{
	  /* "loc" should be the "." token.  */
	  richloc.ಕೂಡಿಸು_fixit_replace ("->");
	  error_at (&richloc,
		    "%qE is a pointer; did you mean to use %<->%>?",
		    datum);
	}
      ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
    }
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ಸಂಕೇತ_2 != ERROR_MARK)
    error_at (loc,
	      "request for member %qE in something not a structure or union",
	      component);

  ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
}

/* Given an expression PTR for a pointer, return an expression
   for the value pointed to.
   ERRORSTRING is the name of the operator to appear in error messages.

   LOC is the location to use for the generated tree.  */

ವೃಕ್ಷ
build_ಪರೋಕ್ಷ_ref (location_t loc, ವೃಕ್ಷ ptr, ref_operator errstring)
{
  ವೃಕ್ಷ ಸೂಚಕ = default_conversion (ptr);
  ವೃಕ್ಷ type = ವೃಕ್ಷ_TYPE (ಸೂಚಕ);
  ವೃಕ್ಷ ref;

  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (type) == ಸೂಚಕ_TYPE)
    {
      ಆದರೆ (CONVERT_ಅಭಿವ್ಯಕ್ತಿ_P (ಸೂಚಕ)
          || ವೃಕ್ಷ_ಸಂಕೇತ (ಸೂಚಕ) == VIEW_CONVERT_ಅಭಿವ್ಯಕ್ತಿ)
	{
	  /* If a warning is issued, mark it to avoid duplicates from
	     the backend.  This only needs to be done at
	     warn_strict_aliasing > 2.  */
	  ಆದರೆ (warn_strict_aliasing > 2)
	    ಆದರೆ (strict_aliasing_warning (ಅಭಿವ್ಯಕ್ತಿ_LOCATION (ಸೂಚಕ),
					 type, ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (ಸೂಚಕ, 0)))
	      suppress_warning (ಸೂಚಕ, OPT_Wstrict_aliasing_);
	}

      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ಸೂಚಕ) == ADDR_ಅಭಿವ್ಯಕ್ತಿ
	  && (ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (ಸೂಚಕ, 0))
	      == ವೃಕ್ಷ_TYPE (type)))
	{
	  ref = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (ಸೂಚಕ, 0);
	  protected_ಗಣ_ಅಭಿವ್ಯಕ್ತಿ_location (ref, loc);
	  ಹಿಂತಿರುಗಿ ref;
	}
      ಇಲ್ಲದಿದ್ದರೆ
	{
	  ವೃಕ್ಷ t = ವೃಕ್ಷ_TYPE (type);

	  ref = build1 (ಪರೋಕ್ಷ_REF, t, ಸೂಚಕ);

	  ಆದರೆ (VOID_TYPE_P (t) && c_inhibit_evaluation_warnings == 0)
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
	    = TYPE_VOLATILE (t) || ವೃಕ್ಷ_SIDE_EFFECTS (ಸೂಚಕ);
	  ವೃಕ್ಷ_THIS_VOLATILE (ref) = TYPE_VOLATILE (t);
	  protected_ಗಣ_ಅಭಿವ್ಯಕ್ತಿ_location (ref, loc);
	  ಹಿಂತಿರುಗಿ ref;
	}
    }
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ಸೂಚಕ) != ERROR_MARK)
    invalid_indirection_error (loc, type, errstring);

  ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
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
build_array_ref (location_t loc, ವೃಕ್ಷ array, ವೃಕ್ಷ ಸೂಚ್ಯಂಕ)
{
  ವೃಕ್ಷ ret;
  ತಾರ್ಕಿಕ swapped = ಸುಳ್ಳು;
  ಆದರೆ (ವೃಕ್ಷ_TYPE (array) == error_mark_ಗಂಟು
      || ವೃಕ್ಷ_TYPE (ಸೂಚ್ಯಂಕ) == error_mark_ಗಂಟು)
    ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;

  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (array)) != ARRAY_TYPE
      && ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (array)) != ಸೂಚಕ_TYPE
      /* Allow vector[index] but not index[vector].  */
      && !gnu_ಸದಿಶ_type_p (ವೃಕ್ಷ_TYPE (array)))
    {
      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (ಸೂಚ್ಯಂಕ)) != ARRAY_TYPE
	  && ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (ಸೂಚ್ಯಂಕ)) != ಸೂಚಕ_TYPE)
	{
          error_at (loc,
            "subscripted value is neither array nor pointer nor vector");

	  ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
	}
      std::ಅದಲುಬದಲು (array, ಸೂಚ್ಯಂಕ);
      swapped = ನಿಜ;
    }

  ಆದರೆ (!INTEGRAL_TYPE_P (ವೃಕ್ಷ_TYPE (ಸೂಚ್ಯಂಕ)))
    {
      error_at (loc, "array subscript is not an integer");
      ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
    }

  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_TYPE (array))) == FUNCTION_TYPE)
    {
      error_at (loc, "subscripted value is pointer to function");
      ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
    }

  /* ??? Existing practice has been to warn only when the char
     index is syntactically the index, not for char[array].  */
  ಆದರೆ (!swapped)
     warn_array_subscript_with_type_char (loc, ಸೂಚ್ಯಂಕ);

  /* Apply default promotions *after* noticing character types.  */
  ಸೂಚ್ಯಂಕ = default_conversion (ಸೂಚ್ಯಂಕ);
  ಆದರೆ (ಸೂಚ್ಯಂಕ == error_mark_ಗಂಟು)
    ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;

  gcc_assert (ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (ಸೂಚ್ಯಂಕ)) == INTEGER_TYPE
	      || ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (ಸೂಚ್ಯಂಕ)) == BITINT_TYPE);

  ತಾರ್ಕಿಕ was_ಸದಿಶ = ಸದಿಶ_TYPE_P (ವೃಕ್ಷ_TYPE (array));
  ತಾರ್ಕಿಕ non_lvalue = convert_ಸದಿಶ_ಗಮ್ಯ_array_for_subscript (loc, &array, ಸೂಚ್ಯಂಕ);

  /* We only generate a call to .ACCESS_WITH_SIZE when it is a read.  */
  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (array) == COMPONENT_REF
      && handle_counted_by_p (array))
    array = handle_counted_by_for_component_ref (loc, array);

  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (array)) == ARRAY_TYPE)
    {
      ವೃಕ್ಷ rval, type;

      /* An array that is indexed by a non-constant
	 cannot be stored in a register; we must be able to do
	 address arithmetic on its address.
	 Likewise an array of elements of variable size.  */
      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ಸೂಚ್ಯಂಕ) != INTEGER_CST
	  || (COMPLETE_TYPE_P (ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_TYPE (array)))
	      && ವೃಕ್ಷ_ಸಂಕೇತ (TYPE_ಗಾತ್ರ (ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_TYPE (array)))) != INTEGER_CST))
	{
	  ಆದರೆ (!c_mark_addressable (array, ನಿಜ, ನಿಜ))
	    ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
	}
      /* An array that is indexed by a constant value which is not within
	 the array bounds cannot be stored in a register either; because we
	 would get a crash in store_bit_field/extract_bit_field when trying
	 to access a non-existent part of the register.  */
      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ಸೂಚ್ಯಂಕ) == INTEGER_CST
	  && TYPE_DOMAIN (ವೃಕ್ಷ_TYPE (array))
	  && !int_ಹೊಂದುತ್ತದೆ_type_p (ಸೂಚ್ಯಂಕ, TYPE_DOMAIN (ವೃಕ್ಷ_TYPE (array))))
	{
	  ಆದರೆ (!c_mark_addressable (array, ಸುಳ್ಳು, ನಿಜ))
	    ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
	  /* ISO C2Y disallows a negative integer constant expression index
	     when array subscripting has an operand of array type.  */
	  ಆದರೆ (flag_isoc2y
	      && !ವೃಕ್ಷ_ಅತಿಪ್ರವಾಹ (ಸೂಚ್ಯಂಕ)
	      && ವೃಕ್ಷ_int_cst_sgn (ಸೂಚ್ಯಂಕ) < 0)
	    error_at (loc, "array subscript is negative");
	}

      ಆದರೆ ((pedantic || warn_c90_c99_compat || warn_c23_c2y_compat)
	  && ! was_ಸದಿಶ)
	{
	  ವೃಕ್ಷ foo = array;
	  ಆಗ (ವೃಕ್ಷ_ಸಂಕೇತ (foo) == COMPONENT_REF)
	    foo = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (foo, 0);
	  ಆದರೆ ((VAR_P (foo) && C_DECL_ರಿಜಿಸ್ಟರ್ (foo))
	      || (ವೃಕ್ಷ_ಸಂಕೇತ (foo) == COMPOUND_LITERAL_ಅಭಿವ್ಯಕ್ತಿ
		  && C_DECL_ರಿಜಿಸ್ಟರ್ (COMPOUND_LITERAL_ಅಭಿವ್ಯಕ್ತಿ_DECL (foo))))
	    pedwarn_c23 (loc, OPT_Wpedantic,
			 "ISO C forbids subscripting %<register%> array "
			 "before C2Y");
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!lvalue_p (foo))
	    pedwarn_c90 (loc, OPT_Wpedantic,
			 "ISO C90 forbids subscripting non-lvalue "
			 "array");
	}

      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (ಸೂಚ್ಯಂಕ)) == BITINT_TYPE
	  && TYPE_PRECISION (ವೃಕ್ಷ_TYPE (ಸೂಚ್ಯಂಕ)) > TYPE_PRECISION (sizetype))
	ಸೂಚ್ಯಂಕ = fold_convert (sizetype, ಸೂಚ್ಯಂಕ);

      type = ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_TYPE (array));
      rval = build4 (ARRAY_REF, type, array, ಸೂಚ್ಯಂಕ, NULL_ವೃಕ್ಷ, NULL_ವೃಕ್ಷ);
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
      protected_ಗಣ_ಅಭಿವ್ಯಕ್ತಿ_location (ret, loc);
      ಆದರೆ (non_lvalue)
	ret = non_lvalue_loc (loc, ret);
      ಹಿಂತಿರುಗಿ ret;
    }
  ಇಲ್ಲದಿದ್ದರೆ
    {
      ವೃಕ್ಷ ar = default_conversion (array);

      ಆದರೆ (ar == error_mark_ಗಂಟು)
	ಹಿಂತಿರುಗಿ ar;

      gcc_assert (ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (ar)) == ಸೂಚಕ_TYPE);
      gcc_assert (ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_TYPE (ar))) != FUNCTION_TYPE);

      ret = build_ಪರೋಕ್ಷ_ref (loc, build_ದ್ವಿಮಾನ_op (loc, PLUS_ಅಭಿವ್ಯಕ್ತಿ, ar,
						      ಸೂಚ್ಯಂಕ, ಸುಳ್ಳು),
				RO_ARRAY_INDEXING);
      ಆದರೆ (non_lvalue)
	ret = non_lvalue_loc (loc, ret);
      ಹಿಂತಿರುಗಿ ret;
    }
}

/* Build an OpenMP array section reference, creating an exact type for the
   resulting expression based on the element type and bounds if possible.  If
   we have variable bounds, create an incomplete array type for the result
   instead.  */

ವೃಕ್ಷ
build_omp_array_section (location_t loc, ವೃಕ್ಷ array, ವೃಕ್ಷ ಸೂಚ್ಯಂಕ, ವೃಕ್ಷ ಉದ್ದಳತೆ)
{
  ವೃಕ್ಷ type = ವೃಕ್ಷ_TYPE (array);
  gcc_assert (type);

  ವೃಕ್ಷ sectype, eltype = ವೃಕ್ಷ_TYPE (type);

  /* It's not an array or pointer type.  Just reuse the type of the original
     expression as the type of the array section (an error will be raised
     anyway, later).  */
  ಆದರೆ (eltype == NULL_ವೃಕ್ಷ || error_ಕಾರ್ಯಾಂಶ_p (eltype))
    sectype = ವೃಕ್ಷ_TYPE (array);
  ಇಲ್ಲದಿದ್ದರೆ
    {
      ವೃಕ್ಷ idxtype = NULL_ವೃಕ್ಷ;

      ಆದರೆ (ಸೂಚ್ಯಂಕ != NULL_ವೃಕ್ಷ
	  && ಉದ್ದಳತೆ != NULL_ವೃಕ್ಷ
	  && INTEGRAL_TYPE_P (ವೃಕ್ಷ_TYPE (ಸೂಚ್ಯಂಕ))
	  && INTEGRAL_TYPE_P (ವೃಕ್ಷ_TYPE (ಉದ್ದಳತೆ)))
	{
	  ವೃಕ್ಷ ಕೆಳಗಿನ = fold_convert (sizetype, ಸೂಚ್ಯಂಕ);
	  ವೃಕ್ಷ ಮೇಲಿನ = fold_convert (sizetype, ಉದ್ದಳತೆ);
	  ಮೇಲಿನ = ಗಾತ್ರ_binop (PLUS_ಅಭಿವ್ಯಕ್ತಿ, ಕೆಳಗಿನ, ಮೇಲಿನ);
	  ಮೇಲಿನ = ಗಾತ್ರ_binop (MINUS_ಅಭಿವ್ಯಕ್ತಿ, ಮೇಲಿನ, ಗಾತ್ರ_one_ಗಂಟು);
	  idxtype = build_range_type (sizetype, ಕೆಳಗಿನ, ಮೇಲಿನ);
	}
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ ((ಸೂಚ್ಯಂಕ == NULL_ವೃಕ್ಷ || integer_zerop (ಸೂಚ್ಯಂಕ))
	       && ಉದ್ದಳತೆ != NULL_ವೃಕ್ಷ
	       && INTEGRAL_TYPE_P (ವೃಕ್ಷ_TYPE (ಉದ್ದಳತೆ)))
	idxtype = build_ಸೂಚ್ಯಂಕ_type (ಉದ್ದಳತೆ);

      gcc_assert (!error_ಕಾರ್ಯಾಂಶ_p (idxtype));

      sectype = c_build_array_type (eltype, idxtype);
    }

  ಹಿಂತಿರುಗಿ build3_loc (loc, OMP_ARRAY_SECTION, sectype, array, ಸೂಚ್ಯಂಕ, ಉದ್ದಳತೆ);
}


/* Record that REF is used.  This is relevant for undeclared static
   function and declarations referenced from a non-local context.
   ADDRESS indicates whether the address is taken.  */

ಶೂನ್ಯ
mark_decl_ಬಳಸಿದ (ವೃಕ್ಷ ref, ತಾರ್ಕಿಕ ವಿಳಾಸ)
{
  ಆದರೆ (!ref || !DECL_P (ref) || ಒಳ_alignof)
    ಹಿಂತಿರುಗಿ;

  /* Non-file-scope and non-local reference in nested function.  */
  ತಾರ್ಕಿಕ nonloc_p = current_function_decl && DECL_CONTEXT (ref)
		  && DECL_CONTEXT (current_function_decl)
		  && DECL_CONTEXT (ref) != current_function_decl;

  /* An undeclared static function.  */
  ತಾರ್ಕಿಕ static_p = ವೃಕ್ಷ_ಸಂಕೇತ (ref) == FUNCTION_DECL
		  && DECL_INITIAL (ref) == NULL_ವೃಕ್ಷ
		  && DECL_EXTERNAL (ref)
		  && !ವೃಕ್ಷ_ಬಹಿರಂಗ (ref);

  ಆದರೆ (!static_p && !nonloc_p)
    ಹಿಂತಿರುಗಿ;

  /* If we may be in an unevaluated context, delay the decision.  */
  ಆದರೆ (ಒಳ_sizeof || ಒಳ_typeof || ಒಳ_countof || ಒಳ_generic)
    ಹಿಂತಿರುಗಿ ದಾಖಲೆ_maybe_ಬಳಸಿದ_decl (ref, ವಿಳಾಸ);

  ಆದರೆ (static_p)
    C_DECL_ಬಳಸಿದ (ref) = 1;

  ಆದರೆ (nonloc_p && (VAR_OR_FUNCTION_DECL_P (ref)
		   || ವೃಕ್ಷ_ಸಂಕೇತ (ref) == PARM_DECL))
    DECL_NONLOCAL (ref) = 1;

  /* Nothing to do anymore.  */
  ಆದರೆ (!nonloc_p || C_FUNC_NONLOCAL_CONTEXT (current_function_decl))
    ಹಿಂತಿರುಗಿ;

  /* Filter out the cases where referencing a non-local variable does not
     require a non-local context passed via the static chain.  */
  ಆದರೆ (!c_type_variably_modified_p (ವೃಕ್ಷ_TYPE (ref)))
    ಆಯ್ಕೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ref))
      {
      ಸ್ಥಿತಿ FUNCTION_DECL:
	/* Use of another local function that requires no context is ok.  */
	ಆದರೆ (!C_FUNC_NONLOCAL_CONTEXT (ref) && DECL_INITIAL (ref))
	  ಹಿಂತಿರುಗಿ;
	ನಿಲ್ಲಿಸು;
      ಸ್ಥಿತಿ VAR_DECL:
	/* Static variables and constexpr are ok, but for the later only
	   when the address is not taken.  */
	ಆದರೆ (ವೃಕ್ಷ_STATIC (ref) || (C_DECL_DECLARED_CONSTEXPR (ref) && !ವಿಳಾಸ))
	  ಹಿಂತಿರುಗಿ;
	ನಿಲ್ಲಿಸು;
      ಸ್ಥಿತಿ TYPE_DECL:
	/* A typedef is ok when not for a variably-modified type. */
	ಹಿಂತಿರುಗಿ;
      ಸ್ಥಿತಿ CONST_DECL:
	/* An enumeration constant is ok. */
	ಹಿಂತಿರುಗಿ;
      ಸ್ಥಿತಿ PARM_DECL:
	ನಿಲ್ಲಿಸು;
      ಸ್ಥಿತಿ LABEL_DECL:
	ನಿಲ್ಲಿಸು;
      ಪೂರ್ವನಿಯೋಜಿತ:
	gcc_unreachable ();
    }

  /* Mark all parent functions up to the nesting level of the variable as
     as needing the non-local context.  */
  ಗಾಗಿ (ವೃಕ್ಷ cont = current_function_decl; cont; cont = DECL_CONTEXT (cont))
    {
      ಆದರೆ (cont == DECL_CONTEXT (ref))
	ನಿಲ್ಲಿಸು;

      /* There should not be any other type of context used for function
	 except TRANSLATION_UNIT_DECL which we should be able to reach.  */
      gcc_checking_assert (ವೃಕ್ಷ_ಸಂಕೇತ (cont) == FUNCTION_DECL);

      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (cont) == FUNCTION_DECL)
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

  *type = ಖಾಲಿ;
  ಆದರೆ (decl && decl != error_mark_ಗಂಟು)
    {
      ref = decl;
      *type = ವೃಕ್ಷ_TYPE (ref);
      ಆದರೆ (DECL_P (decl) && C_DECL_UNDERSPECIFIED (decl))
	error_at (loc, "underspecified %qD referenced in its initializer",
		  decl);
    }
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (fun)
    /* Implicit function declaration.  */
    ref = implicitly_declare (loc, id);
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (decl == error_mark_ಗಂಟು)
    /* Don't complain about something that's already been
       complained about.  */
    ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
  ಇಲ್ಲದಿದ್ದರೆ
    {
      undeclared_variable (loc, id);
      ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
    }

  /* For an OpenMP map clause, we can get better diagnostics for decls with
     unmappable types if we return the decl with an error_mark_node type,
     rather than returning error_mark_node for the decl itself.  */
  ಆದರೆ (ವೃಕ್ಷ_TYPE (ref) == error_mark_ಗಂಟು
      && !c_omp_array_section_p)
    ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;

  ಆದರೆ (ವೃಕ್ಷ_UNAVAILABLE (ref))
    error_unavailable_use (ref, NULL_ವೃಕ್ಷ);
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ವೃಕ್ಷ_DEPRECATED (ref))
    warn_deprecated_use (ref, NULL_ವೃಕ್ಷ);

  /* Recursive call does not count as usage.  */
  ಆದರೆ (ref != current_function_decl)
    {
      ವೃಕ್ಷ_ಬಳಸಿದ (ref) = 1;
    }

  mark_decl_ಬಳಸಿದ (ref, ಸುಳ್ಳು);

  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ref) == CONST_DECL)
    {
      ಬಳಸಿದ_types_ಸೇರಿಸು (ವೃಕ್ಷ_TYPE (ref));

      ಆದರೆ (warn_cxx_compat
	  && ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (ref)) == ENUMERAL_TYPE
	  && C_TYPE_DEFINED_ಒಳ_STRUCT (ವೃಕ್ಷ_TYPE (ref)))
	{
	  warning_at (loc, OPT_Wc___compat,
		      "enum constant defined in struct or union "
		      "is not visible in C++");
	  inform (DECL_ಮೂಲ_LOCATION (ref), "enum constant defined here");
	}

      ref = DECL_INITIAL (ref);
      ವೃಕ್ಷ_CONSTANT (ref) = 1;
    }
  /* C99 6.7.4p3: An inline definition of a function with external
     linkage ... shall not contain a reference to an identifier with
     internal linkage.  */
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (current_function_decl != NULL_ವೃಕ್ಷ
	   && DECL_DECLARED_INLINE_P (current_function_decl)
	   && DECL_EXTERNAL (current_function_decl)
	   && VAR_OR_FUNCTION_DECL_P (ref)
	   && (!VAR_P (ref) || ವೃಕ್ಷ_STATIC (ref))
	   && ! ವೃಕ್ಷ_ಬಹಿರಂಗ (ref)
	   && DECL_CONTEXT (ref) != current_function_decl)
    ದಾಖಲೆ_inline_static (loc, current_function_decl, ref,
			  csi_ಆಂತರಿಕ);

  ಹಿಂತಿರುಗಿ ref;
}

ಸ್ಥಿರ ರಚನೆ maybe_ಬಳಸಿದ_decl *maybe_ಬಳಸಿದ_decls;

/* Record that DECL, a reference seen inside sizeof or typeof or _Countof or
   _Generic, might be used if the operand of sizeof is a VLA type or the
   operand of typeof is a variably modified type or the operand of _Countof has
   a variable number of elements or the operand of _Generic is the one selected
   as the result.  */

ಸ್ಥಿರ ಶೂನ್ಯ
ದಾಖಲೆ_maybe_ಬಳಸಿದ_decl (ವೃಕ್ಷ decl, ತಾರ್ಕಿಕ ವಿಳಾಸ)
{
  ರಚನೆ maybe_ಬಳಸಿದ_decl *t = XOBNEW (&parser_obstack, ರಚನೆ maybe_ಬಳಸಿದ_decl);
  t->decl = decl;
  t->level = ಒಳ_sizeof + ಒಳ_typeof + ಒಳ_countof + ಒಳ_generic;
  t->ವಿಳಾಸ = ವಿಳಾಸ;
  t->ಮುಂದಿನ = maybe_ಬಳಸಿದ_decls;
  maybe_ಬಳಸಿದ_decls = t;
}

/* Pop the stack of decls possibly used inside sizeof or typeof or _Countof or
   _Generic.  If USED is false, just discard them.  If it is true, mark them
   used (if no longer inside sizeof or typeof or _Countof or _Generic) or move
   them to the next level up (if still inside sizeof or typeof or _Countof or
   _Generic).  */

ಶೂನ್ಯ
ತೆಗೆ_maybe_ಬಳಸಿದ (ತಾರ್ಕಿಕ ಬಳಸಿದ)
{
  ರಚನೆ maybe_ಬಳಸಿದ_decl *p = maybe_ಬಳಸಿದ_decls;
  ಪೂರ್ಣಾಂಕ cur_level = ಒಳ_sizeof + ಒಳ_typeof + ಒಳ_countof + ಒಳ_generic;
  ಆಗ (p && p->level > cur_level)
    {
      ಆದರೆ (ಬಳಸಿದ)
	{
	  ಆದರೆ (cur_level == 0)
	    mark_decl_ಬಳಸಿದ (p->decl, p->ವಿಳಾಸ);
	  ಇಲ್ಲದಿದ್ದರೆ
	    p->level = cur_level;
	}
      p = p->ಮುಂದಿನ;
    }
  ಆದರೆ (!ಬಳಸಿದ || cur_level == 0)
    maybe_ಬಳಸಿದ_decls = p;
}

/* Pop the stack of decls possibly used inside sizeof or typeof or _Countof or
   _Generic, without acting on them, and return the pointer to the previous top
   of the stack.  This for use at the end of a default generic association when
   it is not yet known whether the expression is used.  If it later turns out
   the expression is used (or treated as used before C23), restore_maybe_used
   should be called on the return value followed by pop_maybe_used (true);
   otherwise, the return value can be discarded.  */

ರಚನೆ maybe_ಬಳಸಿದ_decl *
save_maybe_ಬಳಸಿದ ()
{
  ರಚನೆ maybe_ಬಳಸಿದ_decl *p = maybe_ಬಳಸಿದ_decls, *orig = p;
  ಪೂರ್ಣಾಂಕ cur_level = ಒಳ_sizeof + ಒಳ_typeof + ಒಳ_countof + ಒಳ_generic;
  ಆಗ (p && p->level > cur_level)
    p = p->ಮುಂದಿನ;
  maybe_ಬಳಸಿದ_decls = p;
  ಹಿಂತಿರುಗಿ orig;
}

/* Restore the stack of decls possibly used inside sizeof or typeof or _Countof
   or _Generic returned by save_maybe_used.  It is required that the stack is
   at exactly the point where it was left by save_maybe_used.  */

ಶೂನ್ಯ
restore_maybe_ಬಳಸಿದ (ರಚನೆ maybe_ಬಳಸಿದ_decl *ರಾಶಿ)
{
  maybe_ಬಳಸಿದ_decls = ರಾಶಿ;
}

/* Return the result of sizeof applied to EXPR.  */

ರಚನೆ c_ಅಭಿವ್ಯಕ್ತಿ
c_ಅಭಿವ್ಯಕ್ತಿ_sizeof_ಅಭಿವ್ಯಕ್ತಿ (location_t loc, ರಚನೆ c_ಅಭಿವ್ಯಕ್ತಿ ಅಭಿವ್ಯಕ್ತಿ)
{
  ರಚನೆ c_ಅಭಿವ್ಯಕ್ತಿ ret;
  ಆದರೆ (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ == error_mark_ಗಂಟು)
    {
      ret.ಮೌಲ್ಯ = error_mark_ಗಂಟು;
      ret.original_ಸಂಕೇತ = ERROR_MARK;
      ret.original_type = ಖಾಲಿ;
      ret.m_decimal = 0;
      ತೆಗೆ_maybe_ಬಳಸಿದ (ಸುಳ್ಳು);
    }
  ಇಲ್ಲದಿದ್ದರೆ
    {
      ತಾರ್ಕಿಕ ಅಭಿವ್ಯಕ್ತಿ_const_operands = ನಿಜ;

      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ) == PARM_DECL
	  && C_ARRAY_PARAMETER (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ))
	{
	  auto_diagnostic_ಗುಂಪು d;
	  ಆದರೆ (warning_at (loc, OPT_Wsizeof_array_ವಾದ,
			  "%<sizeof%> on array function parameter %qE will "
			  "return size of %qT", ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ,
			  ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ)))
	    inform (DECL_ಮೂಲ_LOCATION (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ), "declared here");
	}
      ವೃಕ್ಷ folded_ಅಭಿವ್ಯಕ್ತಿ = c_fully_fold (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ, require_constant_ಮೌಲ್ಯ,
				       &ಅಭಿವ್ಯಕ್ತಿ_const_operands);
      ret.ಮೌಲ್ಯ = c_sizeof (loc, ವೃಕ್ಷ_TYPE (folded_ಅಭಿವ್ಯಕ್ತಿ));
      c_ಕೊನೆಯ_sizeof_arg = ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ;
      c_ಕೊನೆಯ_sizeof_loc = loc;
      ret.original_ಸಂಕೇತ = SIZEOF_ಅಭಿವ್ಯಕ್ತಿ;
      ret.original_type = ಖಾಲಿ;
      ret.m_decimal = 0;
      ಆದರೆ (C_TYPE_VARIABLE_ಗಾತ್ರ (ವೃಕ್ಷ_TYPE (folded_ಅಭಿವ್ಯಕ್ತಿ)))
	{
	  /* sizeof is evaluated when given a vla (C99 6.5.3.4p2).  */
	  ret.ಮೌಲ್ಯ = build2 (C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (ret.ಮೌಲ್ಯ),
			      folded_ಅಭಿವ್ಯಕ್ತಿ, ret.ಮೌಲ್ಯ);
	  C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ_NON_CONST (ret.ಮೌಲ್ಯ) = !ಅಭಿವ್ಯಕ್ತಿ_const_operands;
	  ಗಣ_ಅಭಿವ್ಯಕ್ತಿ_LOCATION (ret.ಮೌಲ್ಯ, loc);
	}
      ತೆಗೆ_maybe_ಬಳಸಿದ (C_TYPE_VARIABLE_ಗಾತ್ರ (ವೃಕ್ಷ_TYPE (folded_ಅಭಿವ್ಯಕ್ತಿ)));
    }
  ಹಿಂತಿರುಗಿ ret;
}

/* Return the result of sizeof applied to T, a structure for the type
   name passed to sizeof (rather than the type itself).  LOC is the
   location of the original expression.  */

ರಚನೆ c_ಅಭಿವ್ಯಕ್ತಿ
c_ಅಭಿವ್ಯಕ್ತಿ_sizeof_type (location_t loc, ರಚನೆ c_type_name *t)
{
  ವೃಕ್ಷ type;
  ರಚನೆ c_ಅಭಿವ್ಯಕ್ತಿ ret;
  ವೃಕ್ಷ type_ಅಭಿವ್ಯಕ್ತಿ = NULL_ವೃಕ್ಷ;
  ತಾರ್ಕಿಕ type_ಅಭಿವ್ಯಕ್ತಿ_const = ನಿಜ;
  type = groktypename (t, &type_ಅಭಿವ್ಯಕ್ತಿ, &type_ಅಭಿವ್ಯಕ್ತಿ_const);
  ret.ಮೌಲ್ಯ = c_sizeof (loc, type);
  c_ಕೊನೆಯ_sizeof_arg = type;
  c_ಕೊನೆಯ_sizeof_loc = loc;
  ret.original_ಸಂಕೇತ = SIZEOF_ಅಭಿವ್ಯಕ್ತಿ;
  ret.original_type = ಖಾಲಿ;
  ret.m_decimal = 0;
  ಆದರೆ (type == error_mark_ಗಂಟು)
    {
      ret.ಮೌಲ್ಯ = error_mark_ಗಂಟು;
      ret.original_ಸಂಕೇತ = ERROR_MARK;
    }
  ಇಲ್ಲದಿದ್ದರೆ
  ಆದರೆ ((type_ಅಭಿವ್ಯಕ್ತಿ || ವೃಕ್ಷ_ಸಂಕೇತ (ret.ಮೌಲ್ಯ) == INTEGER_CST)
      && C_TYPE_VARIABLE_ಗಾತ್ರ (type))
    {
      /* If the type is a [*] array, it is a VLA but is represented as
	 having a size of zero.  In such a case we must ensure that
	 the result of sizeof does not get folded to a constant by
	 c_fully_fold, because if the size is evaluated the result is
	 not constant and so constraints on zero or negative size
	 arrays must not be applied when this sizeof call is inside
	 another array declarator.  */
      ಆದರೆ (!type_ಅಭಿವ್ಯಕ್ತಿ)
	type_ಅಭಿವ್ಯಕ್ತಿ = integer_zero_ಗಂಟು;
      ret.ಮೌಲ್ಯ = build2 (C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (ret.ಮೌಲ್ಯ),
			  type_ಅಭಿವ್ಯಕ್ತಿ, ret.ಮೌಲ್ಯ);
      C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ_NON_CONST (ret.ಮೌಲ್ಯ) = !type_ಅಭಿವ್ಯಕ್ತಿ_const;
    }
  ತೆಗೆ_maybe_ಬಳಸಿದ (type != error_mark_ಗಂಟು
		  ? C_TYPE_VARIABLE_ಗಾತ್ರ (type) : ಸುಳ್ಳು);
  ಹಿಂತಿರುಗಿ ret;
}

ಸ್ಥಿರ ತಾರ್ಕಿಕ
ತುದಿ_array_vla_p (const_ವೃಕ್ಷ type)
{
  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (type) != ARRAY_TYPE)
    ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;

  ವೃಕ್ಷ d = TYPE_DOMAIN (type);

  ಆದರೆ (!d)
    ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
  ಆದರೆ (!TYPE_MAX_ಮೌಲ್ಯ (d))
    ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;

  ಹಿಂತಿರುಗಿ ವೃಕ್ಷ_ಸಂಕೇತ (TYPE_MAX_ಮೌಲ್ಯ (d)) != INTEGER_CST
	 || ವೃಕ್ಷ_ಸಂಕೇತ (TYPE_MIN_ಮೌಲ್ಯ (d)) != INTEGER_CST;
}

/* Return the result of countof applied to EXPR.  */

ರಚನೆ c_ಅಭಿವ್ಯಕ್ತಿ
c_ಅಭಿವ್ಯಕ್ತಿ_countof_ಅಭಿವ್ಯಕ್ತಿ (location_t loc, ರಚನೆ c_ಅಭಿವ್ಯಕ್ತಿ ಅಭಿವ್ಯಕ್ತಿ)
{
  ರಚನೆ c_ಅಭಿವ್ಯಕ್ತಿ ret;
  ಆದರೆ (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ == error_mark_ಗಂಟು)
    {
      ret.ಮೌಲ್ಯ = error_mark_ಗಂಟು;
      ret.original_ಸಂಕೇತ = ERROR_MARK;
      ret.original_type = ಖಾಲಿ;
      ret.m_decimal = 0;
      ತೆಗೆ_maybe_ಬಳಸಿದ (ಸುಳ್ಳು);
    }
  ಇಲ್ಲದಿದ್ದರೆ
    {
      ತಾರ್ಕಿಕ ಅಭಿವ್ಯಕ್ತಿ_const_operands = ನಿಜ;

      ವೃಕ್ಷ folded_ಅಭಿವ್ಯಕ್ತಿ = c_fully_fold (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ, require_constant_ಮೌಲ್ಯ,
				       &ಅಭಿವ್ಯಕ್ತಿ_const_operands);
      ret.ಮೌಲ್ಯ = c_countof_type (loc, ವೃಕ್ಷ_TYPE (folded_ಅಭಿವ್ಯಕ್ತಿ));
      c_ಕೊನೆಯ_sizeof_arg = ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ;
      c_ಕೊನೆಯ_sizeof_loc = loc;
      ret.original_ಸಂಕೇತ = COUNTOF_ಅಭಿವ್ಯಕ್ತಿ;
      ret.original_type = ಖಾಲಿ;
      ret.m_decimal = 0;
      ಆದರೆ (ತುದಿ_array_vla_p (ವೃಕ್ಷ_TYPE (folded_ಅಭಿವ್ಯಕ್ತಿ)))
	{
	  /* countof is evaluated when given a vla.  */
	  ret.ಮೌಲ್ಯ = build2 (C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (ret.ಮೌಲ್ಯ),
			      folded_ಅಭಿವ್ಯಕ್ತಿ, ret.ಮೌಲ್ಯ);
	  C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ_NON_CONST (ret.ಮೌಲ್ಯ) = !ಅಭಿವ್ಯಕ್ತಿ_const_operands;
	  ಗಣ_ಅಭಿವ್ಯಕ್ತಿ_LOCATION (ret.ಮೌಲ್ಯ, loc);
	}
      ತೆಗೆ_maybe_ಬಳಸಿದ (ತುದಿ_array_vla_p (ವೃಕ್ಷ_TYPE (folded_ಅಭಿವ್ಯಕ್ತಿ)));
    }
  ಹಿಂತಿರುಗಿ ret;
}

/* Return the result of countof applied to T, a structure for the type
   name passed to countof (rather than the type itself).  LOC is the
   location of the original expression.  */

ರಚನೆ c_ಅಭಿವ್ಯಕ್ತಿ
c_ಅಭಿವ್ಯಕ್ತಿ_countof_type (location_t loc, ರಚನೆ c_type_name *t)
{
  ವೃಕ್ಷ type;
  ರಚನೆ c_ಅಭಿವ್ಯಕ್ತಿ ret;
  ವೃಕ್ಷ type_ಅಭಿವ್ಯಕ್ತಿ = NULL_ವೃಕ್ಷ;
  ತಾರ್ಕಿಕ type_ಅಭಿವ್ಯಕ್ತಿ_const = ನಿಜ;
  type = groktypename (t, &type_ಅಭಿವ್ಯಕ್ತಿ, &type_ಅಭಿವ್ಯಕ್ತಿ_const);
  ret.ಮೌಲ್ಯ = c_countof_type (loc, type);
  c_ಕೊನೆಯ_sizeof_arg = type;
  c_ಕೊನೆಯ_sizeof_loc = loc;
  ret.original_ಸಂಕೇತ = COUNTOF_ಅಭಿವ್ಯಕ್ತಿ;
  ret.original_type = ಖಾಲಿ;
  ret.m_decimal = 0;
  ಆದರೆ (type == error_mark_ಗಂಟು)
    {
      ret.ಮೌಲ್ಯ = error_mark_ಗಂಟು;
      ret.original_ಸಂಕೇತ = ERROR_MARK;
    }
  ಇಲ್ಲದಿದ್ದರೆ
  ಆದರೆ ((type_ಅಭಿವ್ಯಕ್ತಿ || ವೃಕ್ಷ_ಸಂಕೇತ (ret.ಮೌಲ್ಯ) == INTEGER_CST)
      && ತುದಿ_array_vla_p (type))
    {
      /* If the type is a [*] array, it is a VLA but is represented as
	 having a size of zero.  In such a case we must ensure that
	 the result of countof does not get folded to a constant by
	 c_fully_fold, because if the number of elements is evaluated
	 the result is not constant and so
	 constraints on zero or negative size arrays must not be applied
	 when this countof call is inside another array declarator.  */
      ಆದರೆ (!type_ಅಭಿವ್ಯಕ್ತಿ)
	type_ಅಭಿವ್ಯಕ್ತಿ = integer_zero_ಗಂಟು;
      ret.ಮೌಲ್ಯ = build2 (C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (ret.ಮೌಲ್ಯ),
			  type_ಅಭಿವ್ಯಕ್ತಿ, ret.ಮೌಲ್ಯ);
      C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ_NON_CONST (ret.ಮೌಲ್ಯ) = !type_ಅಭಿವ್ಯಕ್ತಿ_const;
    }
  ತೆಗೆ_maybe_ಬಳಸಿದ (type != error_mark_ಗಂಟು ? ತುದಿ_array_vla_p (type) : ಸುಳ್ಳು);
  ಹಿಂತಿರುಗಿ ret;
}

/* Return the result of maxof applied to T, a structure for the type
   name passed to maxof (rather than the type itself).  LOC is the
   location of the original expression.  */

ರಚನೆ c_ಅಭಿವ್ಯಕ್ತಿ
c_ಅಭಿವ್ಯಕ್ತಿ_maxof_type (location_t loc, ರಚನೆ c_type_name *t)
{
  ವೃಕ್ಷ type;
  ರಚನೆ c_ಅಭಿವ್ಯಕ್ತಿ ret;
  ವೃಕ್ಷ type_ಅಭಿವ್ಯಕ್ತಿ = NULL_ವೃಕ್ಷ;
  ತಾರ್ಕಿಕ type_ಅಭಿವ್ಯಕ್ತಿ_const = ನಿಜ;
  type = groktypename (t, &type_ಅಭಿವ್ಯಕ್ತಿ, &type_ಅಭಿವ್ಯಕ್ತಿ_const);
  ret.ಮೌಲ್ಯ = c_maxof_type (loc, type);
  c_ಕೊನೆಯ_sizeof_arg = type;
  c_ಕೊನೆಯ_sizeof_loc = loc;
  ret.original_ಸಂಕೇತ = MAXOF_ಅಭಿವ್ಯಕ್ತಿ;
  ret.original_type = ಖಾಲಿ;
  ret.m_decimal = 0;
  ಆದರೆ (type == error_mark_ಗಂಟು)
    {
      ret.ಮೌಲ್ಯ = error_mark_ಗಂಟು;
      ret.original_ಸಂಕೇತ = ERROR_MARK;
    }
  ತೆಗೆ_maybe_ಬಳಸಿದ (type != error_mark_ಗಂಟು);
  ಹಿಂತಿರುಗಿ ret;
}

/* Return the result of minof applied to T, a structure for the type
   name passed to minof (rather than the type itself).  LOC is the
   location of the original expression.  */

ರಚನೆ c_ಅಭಿವ್ಯಕ್ತಿ
c_ಅಭಿವ್ಯಕ್ತಿ_minof_type (location_t loc, ರಚನೆ c_type_name *t)
{
  ವೃಕ್ಷ type;
  ರಚನೆ c_ಅಭಿವ್ಯಕ್ತಿ ret;
  ವೃಕ್ಷ type_ಅಭಿವ್ಯಕ್ತಿ = NULL_ವೃಕ್ಷ;
  ತಾರ್ಕಿಕ type_ಅಭಿವ್ಯಕ್ತಿ_const = ನಿಜ;
  type = groktypename (t, &type_ಅಭಿವ್ಯಕ್ತಿ, &type_ಅಭಿವ್ಯಕ್ತಿ_const);
  ret.ಮೌಲ್ಯ = c_minof_type (loc, type);
  c_ಕೊನೆಯ_sizeof_arg = type;
  c_ಕೊನೆಯ_sizeof_loc = loc;
  ret.original_ಸಂಕೇತ = MINOF_ಅಭಿವ್ಯಕ್ತಿ;
  ret.original_type = ಖಾಲಿ;
  ret.m_decimal = 0;
  ಆದರೆ (type == error_mark_ಗಂಟು)
    {
      ret.ಮೌಲ್ಯ = error_mark_ಗಂಟು;
      ret.original_ಸಂಕೇತ = ERROR_MARK;
    }
  ತೆಗೆ_maybe_ಬಳಸಿದ (type != error_mark_ಗಂಟು);
  ಹಿಂತಿರುಗಿ ret;
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

  vec_alloc (v, list_ಉದ್ದಳತೆ (params));
  ಗಾಗಿ (; params; params = ವೃಕ್ಷ_CHAIN (params))
    v->ಶೀಘ್ರ_ತಳ್ಳು (ವೃಕ್ಷ_ಮೌಲ್ಯ (params));
  ret = c_build_function_call_vec (loc, vNULL, function, v, ಖಾಲಿ);
  vec_free (v);
  ಹಿಂತಿರುಗಿ ret;
}

/* Give a note about the location of the declaration of DECL,
   or, failing that, a pertinent declaration for FUNCTION_EXPR.  */

ಸ್ಥಿರ ಶೂನ್ಯ
inform_declaration (ವೃಕ್ಷ decl, ವೃಕ್ಷ function_ಅಭಿವ್ಯಕ್ತಿ)
{
  ಆದರೆ (decl && (ವೃಕ್ಷ_ಸಂಕೇತ (decl) != FUNCTION_DECL
	       || !DECL_IS_UNDECLARED_BUILTIN (decl)))
    inform (DECL_ಮೂಲ_LOCATION (decl), "declared here");
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (function_ಅಭಿವ್ಯಕ್ತಿ)
    ಆಯ್ಕೆ (ವೃಕ್ಷ_ಸಂಕೇತ (function_ಅಭಿವ್ಯಕ್ತಿ))
      {
      ಪೂರ್ವನಿಯೋಜಿತ:
	ನಿಲ್ಲಿಸು;
      ಸ್ಥಿತಿ COMPONENT_REF:
	/* Show the decl of the pertinent field (e.g. for callback
	   fields in a struct.  */
	{
	  ವೃಕ್ಷ ಕ್ಷೇತ್ರ_decl = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (function_ಅಭಿವ್ಯಕ್ತಿ, 1);
	  ಆದರೆ (location_t loc = DECL_ಮೂಲ_LOCATION (ಕ್ಷೇತ್ರ_decl))
	    inform (loc, "declared here");
	}
	ನಿಲ್ಲಿಸು;
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
  ವೃಕ್ಷ name = NULL_ವೃಕ್ಷ, ಫಲಿತಾಂಶ;
  ವೃಕ್ಷ tem;
  ಪೂರ್ಣಾಂಕ nargs;
  ವೃಕ್ಷ *argarray;


  /* Strip NON_LVALUE_EXPRs, etc., since we aren't using as an lvalue.  */
  STRIP_TYPE_NOPS (function);

  /* Convert anything with function type to a pointer-to-function.  */
  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (function) == FUNCTION_DECL)
    {
      name = DECL_NAME (function);

      ಆದರೆ (flag_tm)
	tm_malloc_replacement (function);
      fundecl = function;
      ಆದರೆ (!orig_fundecl)
	orig_fundecl = fundecl;
      /* Atomic functions have type checking/casting already done.  They are
	 often rewritten and don't match the original parameter list.  */
      ಆದರೆ (name && startswith (IDENTIFIER_ಸೂಚಕ (name), "__atomic_"))
        origtypes = ಖಾಲಿ;
    }
  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (function)) == FUNCTION_TYPE)
    function = function_ಗಮ್ಯ_ಸೂಚಕ_conversion (loc, function);

  /* For Objective-C, convert any calls via a cast to OBJC_TYPE_REF
     expressions, like those used for ObjC messenger dispatches.  */
  ಆದರೆ (params && !params->is_ಖಾಲಿಗಳು ())
    function = objc_rewrite_function_call (function, (*params)[0]);

  function = c_fully_fold (function, ಸುಳ್ಳು, ಖಾಲಿ);

  fntype = ವೃಕ್ಷ_TYPE (function);

  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (fntype) == ERROR_MARK)
    ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;

  ಆದರೆ (!(ವೃಕ್ಷ_ಸಂಕೇತ (fntype) == ಸೂಚಕ_TYPE
	&& ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (fntype)) == FUNCTION_TYPE))
    {
      ಆದರೆ (!flag_diagnostics_show_caret && !STATEMENT_CLASS_P (function))
	error_at (loc,
		  "called object %qE is not a function or function pointer",
		  function);
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (DECL_P (function))
	{
	  auto_diagnostic_ಗುಂಪು d;
	  error_at (loc,
		    "called object %qD is not a function or function pointer",
		    function);
	  inform_declaration (function, NULL_ವೃಕ್ಷ);
	}
      ಇಲ್ಲದಿದ್ದರೆ
	error_at (loc,
		  "called object is not a function or function pointer");
      ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
    }

  ಆದರೆ (fundecl && ವೃಕ್ಷ_THIS_VOLATILE (fundecl))
    current_function_returns_abnormally = 1;

  /* fntype now gets the type of function pointed to.  */
  fntype = ವೃಕ್ಷ_TYPE (fntype);
  ವೃಕ್ಷ return_type = ವೃಕ್ಷ_TYPE (fntype);

  /* Convert the parameters to the types declared in the
     function prototype, or apply default promotions.  */

  nargs = convert_arguments (loc, arg_loc, fntype, params,
			     origtypes, function, fundecl);
  ಆದರೆ (nargs < 0)
    ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;

  /* Check that the function is called through a compatible prototype.
     If it is not, warn.  */
  ಆದರೆ (CONVERT_ಅಭಿವ್ಯಕ್ತಿ_P (function)
      && ವೃಕ್ಷ_ಸಂಕೇತ (tem = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (function, 0)) == ADDR_ಅಭಿವ್ಯಕ್ತಿ
      && ವೃಕ್ಷ_ಸಂಕೇತ (tem = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (tem, 0)) == FUNCTION_DECL
      && !comptypes (fntype, ವೃಕ್ಷ_TYPE (tem)))
    {
      /* This situation leads to run-time undefined behavior.  We can't,
	 therefore, simply error unless we can prove that all possible
	 executions of the program must execute the code.  */
      warning_at (loc, 0, "function called through a non-compatible type");

      ಆದರೆ (VOID_TYPE_P (return_type)
	  && TYPE_QUALS (return_type) != TYPE_UNQUALIFIED)
	pedwarn (loc, 0,
		 "function with qualified void return type called");
     }

  argarray = vec_ಸುರಕ್ಷಿತ_ವಿಳಾಸ (params);

  /* Check that arguments to builtin functions match the expectations.  */
  ಆದರೆ (fundecl
      && fndecl_built_ಒಳ_p (fundecl)
      && !check_builtin_function_arguments (loc, arg_loc, fundecl,
					    orig_fundecl, nargs, argarray))
    ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;

  /* Check that the arguments to the function are valid.  */
  ತಾರ್ಕಿಕ warned_p = check_function_arguments (loc, fundecl, fntype,
					    nargs, argarray, &arg_loc,
					    comptypes);

  ಆದರೆ (TYPE_QUALS (return_type) != TYPE_UNQUALIFIED
      && !VOID_TYPE_P (return_type))
    return_type = c_build_qualified_type (return_type, TYPE_UNQUALIFIED);
  ಆದರೆ (name != NULL_ವೃಕ್ಷ
      && startswith (IDENTIFIER_ಸೂಚಕ (name), "__builtin_"))
    {
      ಆದರೆ (require_constant_ಮೌಲ್ಯ)
	ಫಲಿತಾಂಶ
	  = fold_build_call_array_initializer_loc (loc, return_type,
						   function, nargs, argarray);
      ಇಲ್ಲದಿದ್ದರೆ
	ಫಲಿತಾಂಶ = fold_build_call_array_loc (loc, return_type,
					    function, nargs, argarray);
      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ಫಲಿತಾಂಶ) == NOP_ಅಭಿವ್ಯಕ್ತಿ
	  && ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (ಫಲಿತಾಂಶ, 0)) == INTEGER_CST)
	STRIP_TYPE_NOPS (ಫಲಿತಾಂಶ);
    }
  ಇಲ್ಲದಿದ್ದರೆ
    ಫಲಿತಾಂಶ = build_call_array_loc (loc, return_type,
				   function, nargs, argarray);
  /* If -Wnonnull warning has been diagnosed, avoid diagnosing it again
     later.  */
  ಆದರೆ (warned_p && ವೃಕ್ಷ_ಸಂಕೇತ (ಫಲಿತಾಂಶ) == CALL_ಅಭಿವ್ಯಕ್ತಿ)
    suppress_warning (ಫಲಿತಾಂಶ, OPT_Wnonnull);

  /* In this improbable scenario, a nested function returns a VM type.
     Create a TARGET_EXPR so that the call always has a LHS, much as
     what the C++ FE does for functions returning non-PODs.  */
  ಆದರೆ (c_type_variably_modified_p (ವೃಕ್ಷ_TYPE (fntype)))
    {
      ವೃಕ್ಷ tmp = create_tmp_var_raw (ವೃಕ್ಷ_TYPE (fntype));
      ಫಲಿತಾಂಶ = build4 (ಗುರಿ_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (fntype), tmp, ಫಲಿತಾಂಶ,
		       NULL_ವೃಕ್ಷ, NULL_ವೃಕ್ಷ);
    }

  ಆದರೆ (VOID_TYPE_P (ವೃಕ್ಷ_TYPE (ಫಲಿತಾಂಶ)))
    {
      ಆದರೆ (TYPE_QUALS (ವೃಕ್ಷ_TYPE (ಫಲಿತಾಂಶ)) != TYPE_UNQUALIFIED)
	pedwarn (loc, 0,
		 "function with qualified void return type called");
      ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
    }
  ಹಿಂತಿರುಗಿ require_complete_type (loc, ಫಲಿತಾಂಶ);
}

/* Like build_function_call_vec, but call also resolve_overloaded_builtin.  */

ವೃಕ್ಷ
c_build_function_call_vec (location_t loc, ಸ್ಥಿರಾಂಕ vec<location_t> &arg_loc,
			   ವೃಕ್ಷ function, vec<ವೃಕ್ಷ, va_gc> *params,
			   vec<ವೃಕ್ಷ, va_gc> *origtypes)
{
  /* Strip NON_LVALUE_EXPRs, etc., since we aren't using as an lvalue.  */
  STRIP_TYPE_NOPS (function);

  /* Convert anything with function type to a pointer-to-function.  */
  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (function) == FUNCTION_DECL)
    {
      /* Implement type-directed function overloading for builtins.
	 resolve_overloaded_builtin and targetm.resolve_overloaded_builtin
	 handle all the type checking.  The result is a complete expression
	 that implements this function call.  */
      ವೃಕ್ಷ tem = resolve_overloaded_builtin (loc, function, params);
      ಆದರೆ (tem)
	ಹಿಂತಿರುಗಿ tem;
    }
  ಹಿಂತಿರುಗಿ build_function_call_vec (loc, arg_loc, function, params, origtypes);
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
convert_ವಾದ (location_t ploc, ವೃಕ್ಷ function, ವೃಕ್ಷ fundecl,
		  ವೃಕ್ಷ type, ವೃಕ್ಷ origtype, ವೃಕ್ಷ val, ವೃಕ್ಷ valtype,
		  ತಾರ್ಕಿಕ npc, ವೃಕ್ಷ rname, ಪೂರ್ಣಾಂಕ parmnum, ಪೂರ್ಣಾಂಕ argnum,
		  ತಾರ್ಕಿಕ excess_precision, ಪೂರ್ಣಾಂಕ warnopt)
{
  /* Formal parm type is specified by a function prototype.  */

  ಆದರೆ (type == error_mark_ಗಂಟು || !COMPLETE_TYPE_P (type))
    {
      error_at (ploc, "type of formal parameter %d is incomplete",
		parmnum + 1);
      ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
    }

  /* Optionally warn about conversions that differ from the default
     conversions.  */
  ಆದರೆ (warn_traditional_conversion || warn_traditional)
    {
      ಆದರೆ (INTEGRAL_TYPE_P (type)
	  && SCALAR_FLOAT_TYPE_P (valtype))
	warning_at (ploc, OPT_Wtraditional_conversion,
		    "passing argument %d of %qE as integer rather "
		    "than floating due to prototype",
		    argnum, rname);
      ಆದರೆ (INTEGRAL_TYPE_P (type)
	  && ವೃಕ್ಷ_ಸಂಕೇತ (valtype) == COMPLEX_TYPE)
	warning_at (ploc, OPT_Wtraditional_conversion,
		    "passing argument %d of %qE as integer rather "
		    "than complex due to prototype",
		    argnum, rname);
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (type) == COMPLEX_TYPE
	       && SCALAR_FLOAT_TYPE_P (valtype))
	warning_at (ploc, OPT_Wtraditional_conversion,
		    "passing argument %d of %qE as complex rather "
		    "than floating due to prototype",
		    argnum, rname);
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SCALAR_FLOAT_TYPE_P (type)
	       && INTEGRAL_TYPE_P (valtype))
	warning_at (ploc, OPT_Wtraditional_conversion,
		    "passing argument %d of %qE as floating rather "
		    "than integer due to prototype",
		    argnum, rname);
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (type) == COMPLEX_TYPE
	       && INTEGRAL_TYPE_P (valtype))
	warning_at (ploc, OPT_Wtraditional_conversion,
		    "passing argument %d of %qE as complex rather "
		    "than integer due to prototype",
		    argnum, rname);
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SCALAR_FLOAT_TYPE_P (type)
	       && ವೃಕ್ಷ_ಸಂಕೇತ (valtype) == COMPLEX_TYPE)
	warning_at (ploc, OPT_Wtraditional_conversion,
		    "passing argument %d of %qE as floating rather "
		    "than complex due to prototype",
		    argnum, rname);
      /* ??? At some point, messages should be written about
	 conversions between complex types, but that's too messy
	 to do now.  */
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SCALAR_FLOAT_TYPE_P (type)
	       && SCALAR_FLOAT_TYPE_P (valtype))
	{
	  ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ formal_prec = TYPE_PRECISION (type);

	  /* Warn if any argument is passed as `float',
	     since without a prototype it would be `double'.  */
	  ಆದರೆ (formal_prec == TYPE_PRECISION (float_type_ಗಂಟು)
	      && type != dfloat32_type_ಗಂಟು)
	    warning_at (ploc, 0,
			"passing argument %d of %qE as %<float%> "
			"rather than %<double%> due to prototype",
			argnum, rname);

	  /* Warn if mismatch between argument and prototype
	     for decimal float types.  Warn of conversions with
	     binary float types and of precision narrowing due to
	     prototype.  */
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (type != valtype
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
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (warn_traditional_conversion
	       && INTEGRAL_TYPE_P (type)
	       && INTEGRAL_TYPE_P (valtype))
	{
	  ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ formal_prec = TYPE_PRECISION (type);
	  ವೃಕ್ಷ would_have_been = default_conversion (val);
	  ವೃಕ್ಷ type1 = ವೃಕ್ಷ_TYPE (would_have_been);

	  ಆದರೆ (val == error_mark_ಗಂಟು)
	    /* VAL could have been of incomplete type.  */;
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (type) == ENUMERAL_TYPE
		   && (TYPE_MAIN_VARIANT (type)
		       == TYPE_MAIN_VARIANT (valtype)))
	    /* No warning if function asks for enum
	       and the actual arg is that enum type.  */
	    ;
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (formal_prec != TYPE_PRECISION (type1))
	    warning_at (ploc, OPT_Wtraditional_conversion,
			"passing argument %d of %qE "
			"with different width due to prototype",
			argnum, rname);
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (TYPE_UNSIGNED (type) == TYPE_UNSIGNED (type1))
	    ;
	  /* Don't complain if the formal parameter type
	     is an enum, because we can't tell now whether
	     the value was an enum--even the same enum.  */
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (type) == ENUMERAL_TYPE)
	    ;
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (val) == INTEGER_CST
		   && int_ಹೊಂದುತ್ತದೆ_type_p (val, type))
	    /* Change in signedness doesn't matter
	       if a constant value is unaffected.  */
	    ;
	  /* If the value is extended from a narrower
	     unsigned type, it doesn't matter whether we
	     pass it as signed or unsigned; the value
	     certainly is the same either way.  */
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (TYPE_PRECISION (valtype) < TYPE_PRECISION (type)
		   && TYPE_UNSIGNED (valtype))
	    ;
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (TYPE_UNSIGNED (type))
	    warning_at (ploc, OPT_Wtraditional_conversion,
			"passing argument %d of %qE "
			"as unsigned due to prototype",
			argnum, rname);
	  ಇಲ್ಲದಿದ್ದರೆ
	    warning_at (ploc, OPT_Wtraditional_conversion,
			"passing argument %d of %qE "
			"as signed due to prototype",
			argnum, rname);
	}
    }

  /* Possibly restore an EXCESS_PRECISION_EXPR for the
     sake of better warnings from convert_and_check.  */
  ಆದರೆ (excess_precision)
    val = build1 (EXCESS_PRECISION_ಅಭಿವ್ಯಕ್ತಿ, valtype, val);

  ವೃಕ್ಷ parmval = convert_for_assignment (ploc, ploc, type,
					 val, origtype, ic_argpass,
					 npc, fundecl, function,
					 parmnum + 1, warnopt);
  ಹಿಂತಿರುಗಿ parmval;
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

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ
convert_arguments (location_t loc, vec<location_t> arg_loc, ವೃಕ್ಷ fntype,
		   vec<ವೃಕ್ಷ, va_gc> *ಮೌಲ್ಯಗಳು, vec<ವೃಕ್ಷ, va_gc> *origtypes,
		   ವೃಕ್ಷ function, ವೃಕ್ಷ fundecl)
{
  ವೃಕ್ಷ typelist = TYPE_ARG_TYPES (fntype);
  ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ parmnum;
  ತಾರ್ಕಿಕ error_ವಾದಗಳು = ಸುಳ್ಳು;
  ಸ್ಥಿರಾಂಕ ತಾರ್ಕಿಕ type_generic = fundecl
    && lookup_attribute ("type generic", TYPE_ಗುಣಲಕ್ಷಣಗಳು (ವೃಕ್ಷ_TYPE (fundecl)));
  ತಾರ್ಕಿಕ type_generic_remove_excess_precision = ಸುಳ್ಳು;
  ತಾರ್ಕಿಕ type_generic_ಅತಿಪ್ರವಾಹ_p = ಸುಳ್ಳು;
  ತಾರ್ಕಿಕ type_generic_ಬಿಟ್_query = ಸುಳ್ಳು;
  ವೃಕ್ಷ selector;

  /* Change pointer to function to the function itself for
     diagnostics.  */
  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (function) == ADDR_ಅಭಿವ್ಯಕ್ತಿ
      && ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (function, 0)) == FUNCTION_DECL)
    function = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (function, 0);

  /* Handle an ObjC selector specially for diagnostics.  */
  selector = objc_ಸಂದೇಶ_selector ();

  /* For a call to a built-in function declared without a prototype,
     set to the built-in function's argument list.  */
  ವೃಕ್ಷ builtin_typelist = NULL_ವೃಕ್ಷ;

  /* For type-generic built-in functions, determine whether excess
     precision should be removed (classification) or not
     (comparison).  */
  ಆದರೆ (fundecl
      && fndecl_built_ಒಳ_p (fundecl, BUILT_ಒಳ_ಸಾಮಾನ್ಯ))
    {
      built_ಒಳ_function ಸಂಕೇತ_2 = DECL_FUNCTION_ಸಂಕೇತ (fundecl);
      ಆದರೆ (C_DECL_BUILTIN_PROTOTYPE (fundecl))
	{
	  /* For a call to a built-in function declared without a prototype
	     use the types of the parameters of the internal built-in to
	     match those of the arguments to.  */
	  ಆದರೆ (ವೃಕ್ಷ bdecl = builtin_decl_explicit (ಸಂಕೇತ_2))
	    builtin_typelist = TYPE_ARG_TYPES (ವೃಕ್ಷ_TYPE (bdecl));
	}

      /* For type-generic built-in functions, determine whether excess
	 precision should be removed (classification) or not
	 (comparison).  */
      ಆದರೆ (type_generic)
	ಆಯ್ಕೆ (ಸಂಕೇತ_2)
	  {
	  ಸ್ಥಿತಿ BUILT_ಒಳ_ISFINITE:
	  ಸ್ಥಿತಿ BUILT_ಒಳ_ISINF:
	  ಸ್ಥಿತಿ BUILT_ಒಳ_ISINF_SIGN:
	  ಸ್ಥಿತಿ BUILT_ಒಳ_ISNAN:
	  ಸ್ಥಿತಿ BUILT_ಒಳ_ISNORMAL:
	  ಸ್ಥಿತಿ BUILT_ಒಳ_ISSIGNALING:
	  ಸ್ಥಿತಿ BUILT_ಒಳ_FPCLASSIFY:
	    type_generic_remove_excess_precision = ನಿಜ;
	    ನಿಲ್ಲಿಸು;

	  ಸ್ಥಿತಿ BUILT_ಒಳ_ಕೂಡಿಸು_ಅತಿಪ್ರವಾಹ_P:
	  ಸ್ಥಿತಿ BUILT_ಒಳ_SUB_ಅತಿಪ್ರವಾಹ_P:
	  ಸ್ಥಿತಿ BUILT_ಒಳ_MUL_ಅತಿಪ್ರವಾಹ_P:
	    /* The last argument of these type-generic builtins
	       should not be promoted.  */
	    type_generic_ಅತಿಪ್ರವಾಹ_p = ನಿಜ;
	    ನಿಲ್ಲಿಸು;

	  ಸ್ಥಿತಿ BUILT_ಒಳ_CLZG:
	  ಸ್ಥಿತಿ BUILT_ಒಳ_CTZG:
	  ಸ್ಥಿತಿ BUILT_ಒಳ_CLRSBG:
	  ಸ್ಥಿತಿ BUILT_ಒಳ_FFSG:
	  ಸ್ಥಿತಿ BUILT_ಒಳ_PARITYG:
	  ಸ್ಥಿತಿ BUILT_ಒಳ_POPCOUNTG:
	    /* The first argument of these type-generic builtins
	       should not be promoted.  */
	    type_generic_ಬಿಟ್_query = ನಿಜ;
	    ನಿಲ್ಲಿಸು;

	  ಪೂರ್ವನಿಯೋಜಿತ:
	    ನಿಲ್ಲಿಸು;
	  }
    }

  /* Scan the given expressions (VALUES) and types (TYPELIST), producing
     individual converted arguments.  */

  ವೃಕ್ಷ typetail, builtin_typetail, val;
  ಗಾಗಿ (typetail = typelist,
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
      ಪೂರ್ಣಾಂಕ argnum = parmnum + 1;
      ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *invalid_func_diag;
      /* Set for EXCESS_PRECISION_EXPR arguments.  */
      ತಾರ್ಕಿಕ excess_precision = ಸುಳ್ಳು;
      /* The value of the argument after conversion to the type
	 of the function parameter it is passed to.  */
      ವೃಕ್ಷ parmval;
      /* Some __atomic_* builtins have additional hidden argument at
	 position 0.  */
      location_t ploc
	= !arg_loc.is_ಖಾಲಿಗಳು () && ಮೌಲ್ಯಗಳು->ಉದ್ದಳತೆ () == arg_loc.ಉದ್ದಳತೆ ()
	  ? expansion_ಬಿಂದು_location_if_ಒಳ_system_ಶೀರ್ಷಿಕೆ (arg_loc[parmnum])
	  : ಒಳಹರಿವು_location;

      ಆದರೆ (type == void_type_ಗಂಟು)
	{
	  auto_diagnostic_ಗುಂಪು d;
	  ಪೂರ್ಣಾಂಕ ಅಂಕೆ_expected = parmnum;
	  ಪೂರ್ಣಾಂಕ ಅಂಕೆ_actual = ಮೌಲ್ಯಗಳು->ಉದ್ದಳತೆ ();
	  gcc_rich_location rich_loc (loc);
	  ಆದರೆ (ploc != ಒಳಹರಿವು_location)
	    rich_loc.ಕೂಡಿಸು_range (ploc);
	  ಆದರೆ (selector)
	    error_at (&rich_loc,
		      "too many arguments to method %qE; expected %i, have %i",
		      selector, ಅಂಕೆ_expected, ಅಂಕೆ_actual);
	  ಇಲ್ಲದಿದ್ದರೆ
	    error_at (&rich_loc,
		      "too many arguments to function %qE; expected %i, have %i",
		      function, ಅಂಕೆ_expected, ಅಂಕೆ_actual);
	  inform_declaration (fundecl, function);
	  ಹಿಂತಿರುಗಿ error_ವಾದಗಳು ? -1 : (ಪೂರ್ಣಾಂಕ) parmnum;
	}

      ಆದರೆ (builtin_type == void_type_ಗಂಟು)
	{
	  auto_diagnostic_ಗುಂಪು d;
	  ಆದರೆ (warning_at (loc, OPT_Wbuiltin_declaration_mismatch,
			  "too many arguments to built-in function %qE "
			  "expecting %d", function, parmnum))
	    inform_declaration (fundecl, function);
	  builtin_typetail = NULL_ವೃಕ್ಷ;
	}

      ಆದರೆ (!typetail && parmnum == 0 && !TYPE_NO_NAMED_ವಾದಗಳು_STDARG_P (fntype)
	  && !(fundecl && fndecl_built_ಒಳ_p (fundecl)))
	{
	  auto_diagnostic_ಗುಂಪು d;
	  ತಾರ್ಕಿಕ warned;
	  ಆದರೆ (selector)
	    warned = warning_at (loc, OPT_Wdeprecated_non_prototype,
				 "ISO C23 does not allow arguments"
				 " for method %qE declared without parameters",
				 function);
	  ಇಲ್ಲದಿದ್ದರೆ
	    warned = warning_at (loc, OPT_Wdeprecated_non_prototype,
				 "ISO C23 does not allow arguments"
				 " for function %qE declared without parameters",
				 function);
	  ಆದರೆ (warned)
	    inform_declaration (fundecl, function);
	}

      ಆದರೆ (selector && argnum > 2)
	{
	  rname = selector;
	  argnum -= 2;
	}

      /* Determine if VAL is a null pointer constant before folding it.  */
      ತಾರ್ಕಿಕ npc = null_ಸೂಚಕ_constant_p (val);

      /* If there is excess precision and a prototype, convert once to
	 the required type rather than converting via the semantic
	 type.  Likewise without a prototype a float value represented
	 as long double should be converted once to double.  But for
	 type-generic classification functions excess precision must
	 be removed here.  */
      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (val) == EXCESS_PRECISION_ಅಭಿವ್ಯಕ್ತಿ
	  && (type || !type_generic || !type_generic_remove_excess_precision))
	{
	  val = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (val, 0);
	  excess_precision = ನಿಜ;
	}
      val = c_fully_fold (val, ಸುಳ್ಳು, ಖಾಲಿ);
      STRIP_TYPE_NOPS (val);

      val = require_complete_type (ploc, val);

      /* Some floating-point arguments must be promoted to double when
	 no type is specified by a prototype.  This applies to
	 arguments of type float, and to architecture-specific types
	 (ARM __fp16), but not to _FloatN or _FloatNx types.  */
      ತಾರ್ಕಿಕ promote_float_arg = ಸುಳ್ಳು;
      ಆದರೆ (type == NULL_ವೃಕ್ಷ
	  && ವೃಕ್ಷ_ಸಂಕೇತ (valtype) == REAL_TYPE
	  && (TYPE_PRECISION (valtype)
	      <= TYPE_PRECISION (double_type_ಗಂಟು))
	  && TYPE_MAIN_VARIANT (valtype) != double_type_ಗಂಟು
	  && TYPE_MAIN_VARIANT (valtype) != long_double_type_ಗಂಟು
	  && !DECIMAL_FLOAT_ಬಹುಲಕ_P (TYPE_ಬಹುಲಕ (valtype)))
	{
	  /* Promote this argument, unless it has a _FloatN or
	     _FloatNx type.  */
	  promote_float_arg = ನಿಜ;
	  ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < ಅಂಕೆ_FLOATN_NX_TYPES; i++)
	    ಆದರೆ (TYPE_MAIN_VARIANT (valtype) == FLOATN_NX_TYPE_ಗಂಟು (i))
	      {
		promote_float_arg = ಸುಳ್ಳು;
		ನಿಲ್ಲಿಸು;
	      }
	  /* Don't promote __bf16 either.  */
	  ಆದರೆ (TYPE_MAIN_VARIANT (valtype) == bfloat16_type_ಗಂಟು)
	    promote_float_arg = ಸುಳ್ಳು;
	}

      ಆದರೆ (type != NULL_ವೃಕ್ಷ)
	{
	  ವೃಕ್ಷ origtype = (!origtypes) ? NULL_ವೃಕ್ಷ : (*origtypes)[parmnum];
	  parmval = convert_ವಾದ (ploc, function, fundecl, type, origtype,
				      val, valtype, npc, rname, parmnum, argnum,
				      excess_precision, 0);
	}
      /* A NULLPTR type is just a nullptr always.  */
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (val)) == NULLPTR_TYPE)
	parmval = omit_one_ಕಾರ್ಯಾಂಶ_loc (ploc, ವೃಕ್ಷ_TYPE (val), nullptr_ಗಂಟು, val);
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (promote_float_arg)
        {
	  ಆದರೆ (type_generic)
	    parmval = val;
	  ಇಲ್ಲದಿದ್ದರೆ
	    {
	      /* Convert `float' to `double'.  */
	      ಆದರೆ (warn_double_promotion && !c_inhibit_evaluation_warnings)
		warning_at (ploc, OPT_Wdouble_promotion,
			    "implicit conversion from %qT to %qT when passing "
			    "argument to function",
			    valtype, double_type_ಗಂಟು);
	      parmval = convert (double_type_ಗಂಟು, val);
	    }
	}
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ ((excess_precision && !type_generic)
	       || (type_generic_ಅತಿಪ್ರವಾಹ_p && parmnum == 2)
	       || (type_generic_ಬಿಟ್_query && parmnum == 0))
	/* A "double" argument with excess precision being passed
	   without a prototype or in variable arguments.
	   The last argument of __builtin_*_overflow_p should not be
	   promoted, similarly the first argument of
	   __builtin_{clz,ctz,clrsb,ffs,parity,popcount}g.  */
	parmval = convert (valtype, val);
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ ((invalid_func_diag =
		targetm.calls.invalid_arg_for_unprototyped_fn (typelist, fundecl, val)))
	{
	  error (invalid_func_diag);
	  ಹಿಂತಿರುಗಿ -1;
	}
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (val) == ADDR_ಅಭಿವ್ಯಕ್ತಿ && reject_gcc_builtin (val))
	{
	  ಹಿಂತಿರುಗಿ -1;
	}
      ಇಲ್ಲದಿದ್ದರೆ
	/* Convert `short' and `char' to full-size `int'.  */
	parmval = default_conversion (val);

      (*ಮೌಲ್ಯಗಳು)[parmnum] = parmval;
      ಆದರೆ (parmval == error_mark_ಗಂಟು)
	error_ವಾದಗಳು = ನಿಜ;

      ಆದರೆ (!type && builtin_type && ವೃಕ್ಷ_ಸಂಕೇತ (builtin_type) != VOID_TYPE)
	{
	  /* For a call to a built-in function declared without a prototype,
	     perform the conversions from the argument to the expected type
	     but issue warnings rather than errors for any mismatches.
	     Ignore the converted argument and use the PARMVAL obtained
	     above by applying default conversions instead.  */
	  ವೃಕ್ಷ origtype = (!origtypes) ? NULL_ವೃಕ್ಷ : (*origtypes)[parmnum];
	  convert_ವಾದ (ploc, function, fundecl, builtin_type, origtype,
			    val, valtype, npc, rname, parmnum, argnum,
			    excess_precision,
			    OPT_Wbuiltin_declaration_mismatch);
	}

      ಆದರೆ (typetail)
	typetail = ವೃಕ್ಷ_CHAIN (typetail);

      ಆದರೆ (builtin_typetail)
	builtin_typetail = ವೃಕ್ಷ_CHAIN (builtin_typetail);
    }

  gcc_assert (parmnum == vec_ಸುರಕ್ಷಿತ_ಉದ್ದಳತೆ (ಮೌಲ್ಯಗಳು));

  ಆದರೆ (typetail != NULL_ವೃಕ್ಷ && ವೃಕ್ಷ_ಮೌಲ್ಯ (typetail) != void_type_ಗಂಟು)
    {
      /* Not enough args.
	 Determine minimum number of arguments required.  */
      ಪೂರ್ಣಾಂಕ min_expected_ಅಂಕೆ = 0;
      ತಾರ್ಕಿಕ at_ಕನಿಷ್ಠ_p = ಸುಳ್ಳು;
      ವೃಕ್ಷ iter = typelist;
      ಆಗ (ನಿಜ)
	{
	  ಆದರೆ (!iter)
	    {
	      /* Variadic arguments; stop iterating.  */
	      at_ಕನಿಷ್ಠ_p = ನಿಜ;
	      ನಿಲ್ಲಿಸು;
	    }
	  ಆದರೆ (iter == void_list_ಗಂಟು)
	    /* End of arguments; stop iterating.  */
	    ನಿಲ್ಲಿಸು;
	  ++min_expected_ಅಂಕೆ;
	  iter = ವೃಕ್ಷ_CHAIN (iter);
	}
      auto_diagnostic_ಗುಂಪು d;
      ಪೂರ್ಣಾಂಕ actual_ಅಂಕೆ = vec_ಸುರಕ್ಷಿತ_ಉದ್ದಳತೆ (ಮೌಲ್ಯಗಳು);
      error_at (loc,
		at_ಕನಿಷ್ಠ_p
		? G_("too few arguments to function %qE; expected at least %i, have %i")
		: G_("too few arguments to function %qE; expected %i, have %i"),
		function, min_expected_ಅಂಕೆ, actual_ಅಂಕೆ);
      inform_declaration (fundecl, function);
      ಹಿಂತಿರುಗಿ -1;
    }

  ಆದರೆ (builtin_typetail && ವೃಕ್ಷ_ಮೌಲ್ಯ (builtin_typetail) != void_type_ಗಂಟು)
    {
      ಚಿಹ್ನೆರಹಿತ nargs = parmnum;
      ಗಾಗಿ (ವೃಕ್ಷ t = builtin_typetail; t; t = ವೃಕ್ಷ_CHAIN (t))
	++nargs;

      auto_diagnostic_ಗುಂಪು d;
      ಆದರೆ (warning_at (loc, OPT_Wbuiltin_declaration_mismatch,
		      "too few arguments to built-in function %qE "
		      "expecting %u", function, nargs - 1))
	inform_declaration (fundecl, function);
    }

  ಹಿಂತಿರುಗಿ error_ವಾದಗಳು ? -1 : (ಪೂರ್ಣಾಂಕ) parmnum;
}

/* This is the entry point used by the parser to build unary operators
   in the input.  CODE, a tree_code, specifies the unary operator, and
   ARG is the operand.  For unary plus, the C parser currently uses
   CONVERT_EXPR for code.

   LOC is the location to use for the tree generated.
*/

ರಚನೆ c_ಅಭಿವ್ಯಕ್ತಿ
parser_build_unary_op (location_t loc, ಎಣಿಕೆ ವೃಕ್ಷ_ಸಂಕೇತ_2 ಸಂಕೇತ_2, ರಚನೆ c_ಅಭಿವ್ಯಕ್ತಿ arg)
{
  ರಚನೆ c_ಅಭಿವ್ಯಕ್ತಿ ಫಲಿತಾಂಶ;

  ಫಲಿತಾಂಶ.original_ಸಂಕೇತ = ಸಂಕೇತ_2;
  ಫಲಿತಾಂಶ.original_type = ಖಾಲಿ;
  ಫಲಿತಾಂಶ.m_decimal = 0;

  ಆದರೆ (reject_gcc_builtin (arg.ಮೌಲ್ಯ))
    {
      ಫಲಿತಾಂಶ.ಮೌಲ್ಯ = error_mark_ಗಂಟು;
    }
  ಇಲ್ಲದಿದ್ದರೆ
    {
      ಫಲಿತಾಂಶ.ಮೌಲ್ಯ = build_unary_op (loc, ಸಂಕೇತ_2, arg.ಮೌಲ್ಯ, ಸುಳ್ಳು);

      ಆದರೆ (ವೃಕ್ಷ_ಅತಿಪ್ರವಾಹ_P (ಫಲಿತಾಂಶ.ಮೌಲ್ಯ) && !ವೃಕ್ಷ_ಅತಿಪ್ರವಾಹ_P (arg.ಮೌಲ್ಯ))
	ಅತಿಪ್ರವಾಹ_warning (loc, ಫಲಿತಾಂಶ.ಮೌಲ್ಯ, arg.ಮೌಲ್ಯ);
    }

  /* We are typically called when parsing a prefix token at LOC acting on
     ARG.  Reflect this by updating the source range of the result to
     start at LOC and end at the end of ARG.  */
  ಗಣ_c_ಅಭಿವ್ಯಕ್ತಿ_ಮೂಲ_range (&ಫಲಿತಾಂಶ,
			   loc, arg.get_ಮುಕ್ತಾಯ ());

  ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
}

/* Returns true if TYPE is a character type, *not* including wchar_t.  */

ತಾರ್ಕಿಕ
char_type_p (ವೃಕ್ಷ type)
{
  ಹಿಂತಿರುಗಿ (type == char_type_ಗಂಟು
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

ರಚನೆ c_ಅಭಿವ್ಯಕ್ತಿ
parser_build_ದ್ವಿಮಾನ_op (location_t location, ಎಣಿಕೆ ವೃಕ್ಷ_ಸಂಕೇತ_2 ಸಂಕೇತ_2,
			ರಚನೆ c_ಅಭಿವ್ಯಕ್ತಿ arg1, ರಚನೆ c_ಅಭಿವ್ಯಕ್ತಿ arg2, ವೃಕ್ಷ orig_arg1)
{
  ರಚನೆ c_ಅಭಿವ್ಯಕ್ತಿ ಫಲಿತಾಂಶ;
  ಫಲಿತಾಂಶ.m_decimal = 0;

  ಎಣಿಕೆ ವೃಕ್ಷ_ಸಂಕೇತ_2 code1 = arg1.original_ಸಂಕೇತ;
  ಎಣಿಕೆ ವೃಕ್ಷ_ಸಂಕೇತ_2 code2 = arg2.original_ಸಂಕೇತ;
  ವೃಕ್ಷ type1 = (arg1.original_type
                ? arg1.original_type
                : ವೃಕ್ಷ_TYPE (arg1.ಮೌಲ್ಯ));
  ವೃಕ್ಷ type2 = (arg2.original_type
                ? arg2.original_type
                : ವೃಕ್ಷ_TYPE (arg2.ಮೌಲ್ಯ));

  ಫಲಿತಾಂಶ.ಮೌಲ್ಯ = build_ದ್ವಿಮಾನ_op (location, ಸಂಕೇತ_2,
				  arg1.ಮೌಲ್ಯ, arg2.ಮೌಲ್ಯ, ನಿಜ);
  ಫಲಿತಾಂಶ.original_ಸಂಕೇತ = ಸಂಕೇತ_2;
  ಫಲಿತಾಂಶ.original_type = ಖಾಲಿ;
  ಫಲಿತಾಂಶ.m_decimal = 0;

  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ಫಲಿತಾಂಶ.ಮೌಲ್ಯ) == ERROR_MARK)
    {
      ಗಣ_c_ಅಭಿವ್ಯಕ್ತಿ_ಮೂಲ_range (&ಫಲಿತಾಂಶ,
			       arg1.get_ಆರಂಭ (),
			       arg2.get_ಮುಕ್ತಾಯ ());
      ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
    }

  ಆದರೆ (location != UNKNOWN_LOCATION)
    protected_ಗಣ_ಅಭಿವ್ಯಕ್ತಿ_location (ಫಲಿತಾಂಶ.ಮೌಲ್ಯ, location);

  ಗಣ_c_ಅಭಿವ್ಯಕ್ತಿ_ಮೂಲ_range (&ಫಲಿತಾಂಶ,
			   arg1.get_ಆರಂಭ (),
			   arg2.get_ಮುಕ್ತಾಯ ());

  /* Check for cases such as x+y<<z which users are likely
     to misinterpret.  */
  ಆದರೆ (warn_parentheses)
    warn_about_parentheses (location, ಸಂಕೇತ_2, code1, arg1.ಮೌಲ್ಯ, code2,
			    arg2.ಮೌಲ್ಯ);

  ಆದರೆ (warn_logical_op)
    warn_logical_operator (location, ಸಂಕೇತ_2, ವೃಕ್ಷ_TYPE (ಫಲಿತಾಂಶ.ಮೌಲ್ಯ),
			   code1, arg1.ಮೌಲ್ಯ, code2, arg2.ಮೌಲ್ಯ);

  ಆದರೆ (warn_constant_logical_ಕಾರ್ಯಾಂಶ
      && (ಸಂಕೇತ_2 == TRUTH_ANDIF_ಅಭಿವ್ಯಕ್ತಿ || ಸಂಕೇತ_2 == TRUTH_ORIF_ಅಭಿವ್ಯಕ್ತಿ)
      && INTEGRAL_NB_TYPE_P (type1)
      && INTEGRAL_NB_TYPE_P (type2))
    {
      ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name = ಸಂಕೇತ_2 == TRUTH_ANDIF_ಅಭಿವ್ಯಕ್ತಿ ? "&&" : "||";
      ಆದರೆ (orig_arg1 == NULL_ವೃಕ್ಷ)
	orig_arg1 = arg1.ಮೌಲ್ಯ;
      ಸ್ವಯಂಚಾಲಿತ enum_other_than_0_1 = [] (ವೃಕ್ಷ type) {
	ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (type) != ENUMERAL_TYPE)
	  ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
	ಗಾಗಿ (ವೃಕ್ಷ l = TYPE_ಮೌಲ್ಯಗಳು (type); l; l = ವೃಕ್ಷ_CHAIN (l))
	  {
	    ವೃಕ್ಷ v = DECL_INITIAL (ವೃಕ್ಷ_ಮೌಲ್ಯ (l));
	    ಆದರೆ (!integer_zerop (v) && !integer_onep (v))
	      ಹಿಂತಿರುಗಿ ನಿಜ;
	  }
	ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
      };
      ಸ್ವಯಂಚಾಲಿತ diagnose_constant_logical_ಕಾರ್ಯಾಂಶ = [=] (ವೃಕ್ಷ val, ವೃಕ್ಷ type) {
	ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (val) != INTEGER_CST || integer_zerop (val))
	  ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
	ಆದರೆ (integer_onep (val) && !enum_other_than_0_1 (type))
	  ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
	gcc_rich_location richloc (location);
	richloc.ಕೂಡಿಸು_fixit_replace (name + 1);
	auto_diagnostic_ಗುಂಪು d;
	ಆದರೆ (warning_at (location, OPT_Wconstant_logical_ಕಾರ್ಯಾಂಶ,
			"use of logical %qs with constant operand %qE",
			name, val))
	  inform (&richloc, "use %qs for bitwise operation", name + 1);
	ಹಿಂತಿರುಗಿ ನಿಜ;
      };
      ಆದರೆ (!diagnose_constant_logical_ಕಾರ್ಯಾಂಶ (arg2.ಮೌಲ್ಯ, type2))
	diagnose_constant_logical_ಕಾರ್ಯಾಂಶ (orig_arg1, type1);
    }

  ಆದರೆ (warn_tautological_compare)
    {
      ವೃಕ್ಷ lhs = arg1.ಮೌಲ್ಯ;
      ವೃಕ್ಷ rhs = arg2.ಮೌಲ್ಯ;
      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (lhs) == C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ)
	{
	  ಆದರೆ (C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ_PRE (lhs) != NULL_ವೃಕ್ಷ
	      && ವೃಕ್ಷ_SIDE_EFFECTS (C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ_PRE (lhs)))
	    lhs = NULL_ವೃಕ್ಷ;
	  ಇಲ್ಲದಿದ್ದರೆ
	    lhs = C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ_ಅಭಿವ್ಯಕ್ತಿ (lhs);
	}
      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (rhs) == C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ)
	{
	  ಆದರೆ (C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ_PRE (rhs) != NULL_ವೃಕ್ಷ
	      && ವೃಕ್ಷ_SIDE_EFFECTS (C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ_PRE (rhs)))
	    rhs = NULL_ವೃಕ್ಷ;
	  ಇಲ್ಲದಿದ್ದರೆ
	    rhs = C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ_ಅಭಿವ್ಯಕ್ತಿ (rhs);
	}
      ಆದರೆ (lhs != NULL_ವೃಕ್ಷ && rhs != NULL_ವೃಕ್ಷ)
	warn_tautological_cmp (location, ಸಂಕೇತ_2, lhs, rhs);
    }

  ಆದರೆ (warn_logical_not_paren
      && ವೃಕ್ಷ_ಸಂಕೇತ_CLASS (ಸಂಕೇತ_2) == tcc_comparison
      && code1 == TRUTH_NOT_ಅಭಿವ್ಯಕ್ತಿ
      && code2 != TRUTH_NOT_ಅಭಿವ್ಯಕ್ತಿ
      /* Avoid warning for !!x == y.  */
      && (ವೃಕ್ಷ_ಸಂಕೇತ (arg1.ಮೌಲ್ಯ) != NE_ಅಭಿವ್ಯಕ್ತಿ
	  || !integer_zerop (ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (arg1.ಮೌಲ್ಯ, 1))))
    {
      /* Avoid warning for !b == y where b has _Bool type.  */
      ವೃಕ್ಷ t = integer_zero_ಗಂಟು;
      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (arg1.ಮೌಲ್ಯ) == EQ_ಅಭಿವ್ಯಕ್ತಿ
	  && integer_zerop (ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (arg1.ಮೌಲ್ಯ, 1))
	  && ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (arg1.ಮೌಲ್ಯ, 0)) == integer_type_ಗಂಟು)
	{
	  t = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (arg1.ಮೌಲ್ಯ, 0);
	  ಮಾಡು
	    {
	      ಆದರೆ (ವೃಕ್ಷ_TYPE (t) != integer_type_ಗಂಟು)
		ನಿಲ್ಲಿಸು;
	      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (t) == C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ)
		t = C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ_ಅಭಿವ್ಯಕ್ತಿ (t);
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (CONVERT_ಅಭಿವ್ಯಕ್ತಿ_P (t))
		t = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (t, 0);
	      ಇಲ್ಲದಿದ್ದರೆ
		ನಿಲ್ಲಿಸು;
	    }
	  ಆಗ (1);
	}
      ಆದರೆ (!C_BOOLEAN_TYPE_P (ವೃಕ್ಷ_TYPE (t)))
	warn_logical_not_parentheses (location, ಸಂಕೇತ_2, arg1.ಮೌಲ್ಯ, arg2.ಮೌಲ್ಯ);
    }

  /* Warn about comparisons against string literals, with the exception
     of testing for equality or inequality of a string literal with NULL.  */
  ಆದರೆ (ಸಂಕೇತ_2 == EQ_ಅಭಿವ್ಯಕ್ತಿ || ಸಂಕೇತ_2 == NE_ಅಭಿವ್ಯಕ್ತಿ)
    {
      ಆದರೆ ((code1 == STRING_CST
	   && !integer_zerop (ವೃಕ್ಷ_strip_nop_conversions (arg2.ಮೌಲ್ಯ)))
	  || (code2 == STRING_CST
	      && !integer_zerop (ವೃಕ್ಷ_strip_nop_conversions (arg1.ಮೌಲ್ಯ))))
	warning_at (location, OPT_Waddress,
		    "comparison with string literal results in unspecified behavior");
      /* Warn for ptr == '\0', it's likely that it should've been ptr[0].  */
      ಆದರೆ (ಸೂಚಕ_TYPE_P (type1)
	  && null_ಸೂಚಕ_constant_p (arg2.ಮೌಲ್ಯ)
	  && char_type_p (type2))
	{
	  auto_diagnostic_ಗುಂಪು d;
	  ಆದರೆ (warning_at (location, OPT_Wpointer_compare,
			    "comparison between pointer and zero character "
			    "constant"))
	    inform (arg1.get_ಆರಂಭ (),
		      "did you mean to dereference the pointer?");
	}
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ಸೂಚಕ_TYPE_P (type2)
	       && null_ಸೂಚಕ_constant_p (arg1.ಮೌಲ್ಯ)
	       && char_type_p (type1))
	{
	  auto_diagnostic_ಗುಂಪು d;
	  ಆದರೆ (warning_at (location, OPT_Wpointer_compare,
			    "comparison between pointer and zero character "
			    "constant"))
	    inform (arg2.get_ಆರಂಭ (),
		      "did you mean to dereference the pointer?");
	}
    }
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ_CLASS (ಸಂಕೇತ_2) == tcc_comparison
	   && (code1 == STRING_CST || code2 == STRING_CST))
    warning_at (location, OPT_Waddress,
		"comparison with string literal results in unspecified "
		"behavior");

  ಆದರೆ (warn_zero_as_null_ಸೂಚಕ_constant
      && c_inhibit_evaluation_warnings == 0
      && ವೃಕ್ಷ_ಸಂಕೇತ_CLASS (ಸಂಕೇತ_2) == tcc_comparison)
    {
      ಆದರೆ ((ವೃಕ್ಷ_ಸಂಕೇತ (type1) == ಸೂಚಕ_TYPE
	   || ವೃಕ್ಷ_ಸಂಕೇತ (type1) == NULLPTR_TYPE)
	  && INTEGRAL_TYPE_P (type2)
	  && null_ಸೂಚಕ_constant_p (arg2.ಮೌಲ್ಯ))
	warning_at (arg2.get_location(), OPT_Wzero_as_null_ಸೂಚಕ_constant,
		    "zero as null pointer constant");

      ಆದರೆ ((ವೃಕ್ಷ_ಸಂಕೇತ (type2) == ಸೂಚಕ_TYPE
	   || ವೃಕ್ಷ_ಸಂಕೇತ (type2) == NULLPTR_TYPE)
	  && INTEGRAL_TYPE_P (type1)
	  && null_ಸೂಚಕ_constant_p (arg1.ಮೌಲ್ಯ))
	warning_at (arg1.get_location(), OPT_Wzero_as_null_ಸೂಚಕ_constant,
		    "zero as null pointer constant");
    }

  ಆದರೆ (warn_array_compare
      && ವೃಕ್ಷ_ಸಂಕೇತ_CLASS (ಸಂಕೇತ_2) == tcc_comparison
      && ವೃಕ್ಷ_ಸಂಕೇತ (type1) == ARRAY_TYPE
      && ವೃಕ್ಷ_ಸಂಕೇತ (type2) == ARRAY_TYPE)
    do_warn_array_compare (location, ಸಂಕೇತ_2, arg1.ಮೌಲ್ಯ, arg2.ಮೌಲ್ಯ);

  ಆದರೆ (ವೃಕ್ಷ_ಅತಿಪ್ರವಾಹ_P (ಫಲಿತಾಂಶ.ಮೌಲ್ಯ)
      && !ವೃಕ್ಷ_ಅತಿಪ್ರವಾಹ_P (arg1.ಮೌಲ್ಯ)
      && !ವೃಕ್ಷ_ಅತಿಪ್ರವಾಹ_P (arg2.ಮೌಲ್ಯ))
    ಅತಿಪ್ರವಾಹ_warning (location, ಫಲಿತಾಂಶ.ಮೌಲ್ಯ);

  /* Warn about comparisons of different enum types.  */
  ಆದರೆ (warn_enum_compare
      && ವೃಕ್ಷ_ಸಂಕೇತ_CLASS (ಸಂಕೇತ_2) == tcc_comparison
      && ವೃಕ್ಷ_ಸಂಕೇತ (type1) == ENUMERAL_TYPE
      && ವೃಕ್ಷ_ಸಂಕೇತ (type2) == ENUMERAL_TYPE
      && TYPE_MAIN_VARIANT (type1) != TYPE_MAIN_VARIANT (type2))
    warning_at (location, OPT_Wenum_compare,
		"comparison between %qT and %qT",
		type1, type2);

  ಆದರೆ (warn_xor_ಬಳಸಿದ_as_pow
      && ಸಂಕೇತ_2 == ಬಿಟ್_XOR_ಅಭಿವ್ಯಕ್ತಿ
      && arg1.m_decimal
      && arg2.m_decimal)
    check_for_xor_ಬಳಸಿದ_as_pow (arg1.get_location (), arg1.ಮೌಲ್ಯ,
			       location,
			       arg2.get_location (), arg2.ಮೌಲ್ಯ);

  ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
}

/* Return a tree for the difference of pointers OP0 and OP1.
   The resulting tree has type ptrdiff_t.  If POINTER_SUBTRACT sanitization is
   enabled, assign to INSTRUMENT_EXPR call to libsanitizer.  */

ಸ್ಥಿರ ವೃಕ್ಷ
ಸೂಚಕ_diff (location_t loc, ವೃಕ್ಷ op0, ವೃಕ್ಷ op1, ವೃಕ್ಷ *instrument_ಅಭಿವ್ಯಕ್ತಿ)
{
  ವೃಕ್ಷ restype = ptrdiff_type_ಗಂಟು;
  ವೃಕ್ಷ ಫಲಿತಾಂಶ, inttype;

  addr_space_t as0 = TYPE_ADDR_SPACE (ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_TYPE (op0)));
  addr_space_t as1 = TYPE_ADDR_SPACE (ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_TYPE (op1)));
  ವೃಕ್ಷ ಗುರಿ_type = ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_TYPE (op0));
  ವೃಕ್ಷ orig_op0 = op0;
  ವೃಕ್ಷ orig_op1 = op1;

  /* If the operands point into different address spaces, we need to
     explicitly convert them to pointers into the common address space
     before we can subtract the numerical address values.  */
  ಆದರೆ (as0 != as1)
    {
      addr_space_t as_common;
      ವೃಕ್ಷ common_type;

      /* Determine the common superset address space.  This is guaranteed
	 to exist because the caller verified that comp_target_types
	 returned non-zero.  */
      ಆದರೆ (!addr_space_superset (as0, as1, &as_common))
	gcc_unreachable ();

      common_type = common_ಸೂಚಕ_type (ವೃಕ್ಷ_TYPE (op0), ವೃಕ್ಷ_TYPE (op1), NULL_ವೃಕ್ಷ);
      op0 = convert (common_type, op0);
      op1 = convert (common_type, op1);
    }

  /* Determine integer type result of the subtraction.  This will usually
     be the same as the result type (ptrdiff_t), but may need to be a wider
     type if pointers for the address space are wider than ptrdiff_t.  */
  ಆದರೆ (TYPE_PRECISION (restype) < TYPE_PRECISION (ವೃಕ್ಷ_TYPE (op0)))
    inttype = c_common_type_for_ಗಾತ್ರ (TYPE_PRECISION (ವೃಕ್ಷ_TYPE (op0)), 0);
  ಇಲ್ಲದಿದ್ದರೆ
    inttype = restype;

  ಆದರೆ (VOID_TYPE_P (ಗುರಿ_type))
    pedwarn (loc, OPT_Wpointer_arith,
	     "pointer of type %<void *%> used in subtraction");
  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ಗುರಿ_type) == FUNCTION_TYPE)
    pedwarn (loc, OPT_Wpointer_arith,
	     "pointer to a function used in subtraction");

  ಆದರೆ (current_function_decl != NULL_ವೃಕ್ಷ
      && sanitize_flags_p (SANITIZE_ಸೂಚಕ_ಕಳೆ))
    {
      op0 = save_ಅಭಿವ್ಯಕ್ತಿ (c_fully_fold (op0, ಸುಳ್ಳು, ಖಾಲಿ));
      op1 = save_ಅಭಿವ್ಯಕ್ತಿ (c_fully_fold (op1, ಸುಳ್ಳು, ಖಾಲಿ));

      ವೃಕ್ಷ tt = builtin_decl_explicit (BUILT_ಒಳ_ASAN_ಸೂಚಕ_ಕಳೆ);
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
  ಆದರೆ (TYPE_PRECISION (inttype) > TYPE_PRECISION (ವೃಕ್ಷ_TYPE (op0)))
    op0 = build_ದ್ವಿಮಾನ_op (loc, MINUS_ಅಭಿವ್ಯಕ್ತಿ, convert (inttype, op0),
			   convert (inttype, op1), ಸುಳ್ಳು);
  ಇಲ್ಲದಿದ್ದರೆ
    {
      /* Cast away qualifiers.  */
      op0 = convert (c_common_type (ವೃಕ್ಷ_TYPE (op0), ವೃಕ್ಷ_TYPE (op0)), op0);
      op1 = convert (c_common_type (ವೃಕ್ಷ_TYPE (op1), ವೃಕ್ಷ_TYPE (op1)), op1);
      op0 = build2_loc (loc, ಸೂಚಕ_DIFF_ಅಭಿವ್ಯಕ್ತಿ, inttype, op0, op1);
    }

  /* This generates an error if op1 is pointer to incomplete type.  */
  ಆದರೆ (!COMPLETE_OR_VOID_TYPE_P (ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_TYPE (orig_op1))))
    error_at (loc, "arithmetic on pointer to an incomplete type");
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (verify_type_context (loc, TCTX_ಸೂಚಕ_ARITH,
				ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_TYPE (orig_op0))))
    verify_type_context (loc, TCTX_ಸೂಚಕ_ARITH,
			 ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_TYPE (orig_op1)));

  op1 = c_ಗಾತ್ರ_ಒಳ_ಬೈಟುಗಳು (ಗುರಿ_type);

  ಆದರೆ (ಸೂಚಕ_ಗಮ್ಯ_zero_sized_aggr_p (ವೃಕ್ಷ_TYPE (orig_op1)))
    error_at (loc, "arithmetic on pointer to an empty aggregate");

  /* Divide by the size, in easiest possible way.  */
  ಫಲಿತಾಂಶ = fold_build2_loc (loc, EXACT_DIV_ಅಭಿವ್ಯಕ್ತಿ, inttype,
			    op0, convert (inttype, op1));

  /* Convert to final result type if necessary.  */
  ಹಿಂತಿರುಗಿ convert (restype, ಫಲಿತಾಂಶ);
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
build_atomic_ನಿಯೋಜಿಸು (location_t loc, ವೃಕ್ಷ lhs, ಎಣಿಕೆ ವೃಕ್ಷ_ಸಂಕೇತ_2 modifycode,
		     ವೃಕ್ಷ rhs, ತಾರ್ಕಿಕ return_old_p)
{
  ವೃಕ್ಷ fndecl, func_call;
  vec<ವೃಕ್ಷ, va_gc> *params;
  ವೃಕ್ಷ val, nonatomic_lhs_type, nonatomic_rhs_type, newval, newval_addr;
  ವೃಕ್ಷ old, old_addr;
  ವೃಕ್ಷ compound_stmt = NULL_ವೃಕ್ಷ;
  ವೃಕ್ಷ stmt, goto_stmt;
  ವೃಕ್ಷ loop_label, loop_decl, ಮುಗಿದ_label, ಮುಗಿದ_decl;

  ವೃಕ್ಷ lhs_type = ವೃಕ್ಷ_TYPE (lhs);
  ವೃಕ್ಷ lhs_addr = build_unary_op (loc, ADDR_ಅಭಿವ್ಯಕ್ತಿ, lhs, ಸುಳ್ಳು);
  ವೃಕ್ಷ seq_cst = build_int_cst (integer_type_ಗಂಟು, MEMMODEL_SEQ_CST);
  ವೃಕ್ಷ rhs_semantic_type = ವೃಕ್ಷ_TYPE (rhs);
  ವೃಕ್ಷ nonatomic_rhs_semantic_type;
  ವೃಕ್ಷ rhs_type;

  gcc_assert (TYPE_ATOMIC (lhs_type));

  ಆದರೆ (return_old_p)
    gcc_assert (modifycode == PLUS_ಅಭಿವ್ಯಕ್ತಿ || modifycode == MINUS_ಅಭಿವ್ಯಕ್ತಿ);

  /* Allocate enough vector items for a compare_exchange.  */
  vec_alloc (params, 6);

  /* Create a compound statement to hold the sequence of statements
     with a loop.  */
  ಆದರೆ (modifycode != NOP_ಅಭಿವ್ಯಕ್ತಿ)
    {
      compound_stmt = c_begin_compound_stmt (ಸುಳ್ಳು);

      /* For consistency with build_modify_expr on non-_Atomic,
	 mark the lhs as read.  Also, it would be very hard to match
	 such expressions in mark_exp_read.  */
      mark_exp_read (lhs);
    }

  /* Remove any excess precision (which is only present here in the
     case of compound assignments).  */
  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (rhs) == EXCESS_PRECISION_ಅಭಿವ್ಯಕ್ತಿ)
    {
      gcc_assert (modifycode != NOP_ಅಭಿವ್ಯಕ್ತಿ);
      rhs = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (rhs, 0);
    }
  rhs_type = ವೃಕ್ಷ_TYPE (rhs);

  /* Fold the RHS if it hasn't already been folded.  */
  ಆದರೆ (modifycode != NOP_ಅಭಿವ್ಯಕ್ತಿ)
    rhs = c_fully_fold (rhs, ಸುಳ್ಳು, ಖಾಲಿ);

  /* Remove the qualifiers for the rest of the expressions and create
     the VAL temp variable to hold the RHS.  */
  nonatomic_lhs_type = build_qualified_type (lhs_type, TYPE_UNQUALIFIED);
  nonatomic_rhs_type = build_qualified_type (rhs_type, TYPE_UNQUALIFIED);
  nonatomic_rhs_semantic_type = build_qualified_type (rhs_semantic_type,
						      TYPE_UNQUALIFIED);
  val = create_tmp_var_raw (nonatomic_rhs_type);
  ವೃಕ್ಷ_ADDRESSABLE (val) = 1;
  suppress_warning (val);
  rhs = build4 (ಗುರಿ_ಅಭಿವ್ಯಕ್ತಿ, nonatomic_rhs_type, val, rhs, NULL_ವೃಕ್ಷ,
		NULL_ವೃಕ್ಷ);
  ವೃಕ್ಷ_SIDE_EFFECTS (rhs) = 1;
  ಗಣ_ಅಭಿವ್ಯಕ್ತಿ_LOCATION (rhs, loc);
  ಆದರೆ (modifycode != NOP_ಅಭಿವ್ಯಕ್ತಿ)
    ಕೂಡಿಸು_stmt (rhs);

  /* NOP_EXPR indicates it's a straight store of the RHS. Simply issue
     an atomic_store.  */
  ಆದರೆ (modifycode == NOP_ಅಭಿವ್ಯಕ್ತಿ)
    {
      compound_stmt = rhs;
      /* Build __atomic_store (&lhs, &val, SEQ_CST)  */
      rhs = build_unary_op (loc, ADDR_ಅಭಿವ್ಯಕ್ತಿ, val, ಸುಳ್ಳು);
      fndecl = builtin_decl_explicit (BUILT_ಒಳ_ATOMIC_STORE);
      params->ಶೀಘ್ರ_ತಳ್ಳು (lhs_addr);
      params->ಶೀಘ್ರ_ತಳ್ಳು (rhs);
      params->ಶೀಘ್ರ_ತಳ್ಳು (seq_cst);
      func_call = c_build_function_call_vec (loc, vNULL, fndecl, params, ಖಾಲಿ);

      compound_stmt = build2 (COMPOUND_ಅಭಿವ್ಯಕ್ತಿ, void_type_ಗಂಟು,
			      compound_stmt, func_call);

      /* VAL is the value which was stored, return a COMPOUND_STMT of
	 the statement and that value.  */
      ಹಿಂತಿರುಗಿ build2 (COMPOUND_ಅಭಿವ್ಯಕ್ತಿ, nonatomic_lhs_type, compound_stmt, val);
    }

  /* Attempt to implement the atomic operation as an __atomic_fetch_* or
     __atomic_*_fetch built-in rather than a CAS loop.  atomic_bool type
     isn't applicable for such builtins.  ??? Do we want to handle enums?  */
  ಆದರೆ ((ವೃಕ್ಷ_ಸಂಕೇತ (lhs_type) == INTEGER_TYPE || ಸೂಚಕ_TYPE_P (lhs_type))
      && ವೃಕ್ಷ_ಸಂಕೇತ (rhs_type) == INTEGER_TYPE)
    {
      built_ಒಳ_function fncode;
      ಆಯ್ಕೆ (modifycode)
	{
	ಸ್ಥಿತಿ PLUS_ಅಭಿವ್ಯಕ್ತಿ:
	ಸ್ಥಿತಿ ಸೂಚಕ_PLUS_ಅಭಿವ್ಯಕ್ತಿ:
	  fncode = (return_old_p
		    ? BUILT_ಒಳ_ATOMIC_FETCH_ಕೂಡಿಸು_N
		    : BUILT_ಒಳ_ATOMIC_ಕೂಡಿಸು_FETCH_N);
	  ನಿಲ್ಲಿಸು;
	ಸ್ಥಿತಿ MINUS_ಅಭಿವ್ಯಕ್ತಿ:
	  fncode = (return_old_p
		    ? BUILT_ಒಳ_ATOMIC_FETCH_SUB_N
		    : BUILT_ಒಳ_ATOMIC_SUB_FETCH_N);
	  ನಿಲ್ಲಿಸು;
	ಸ್ಥಿತಿ ಬಿಟ್_AND_ಅಭಿವ್ಯಕ್ತಿ:
	  fncode = (return_old_p
		    ? BUILT_ಒಳ_ATOMIC_FETCH_AND_N
		    : BUILT_ಒಳ_ATOMIC_AND_FETCH_N);
	  ನಿಲ್ಲಿಸು;
	ಸ್ಥಿತಿ ಬಿಟ್_IOR_ಅಭಿವ್ಯಕ್ತಿ:
	  fncode = (return_old_p
		    ? BUILT_ಒಳ_ATOMIC_FETCH_OR_N
		    : BUILT_ಒಳ_ATOMIC_OR_FETCH_N);
	  ನಿಲ್ಲಿಸು;
	ಸ್ಥಿತಿ ಬಿಟ್_XOR_ಅಭಿವ್ಯಕ್ತಿ:
	  fncode = (return_old_p
		    ? BUILT_ಒಳ_ATOMIC_FETCH_XOR_N
		    : BUILT_ಒಳ_ATOMIC_XOR_FETCH_N);
	  ನಿಲ್ಲಿಸು;
	ಪೂರ್ವನಿಯೋಜಿತ:
	  ಹೋಗು cas_loop;
	}

      /* We can only use "_1" through "_16" variants of the atomic fetch
	 built-ins.  */
      ಚಿಹ್ನೆರಹಿತ HOST_WIDE_INT ಗಾತ್ರ_2 = ವೃಕ್ಷ_ಗಮ್ಯ_uhwi (TYPE_ಗಾತ್ರ_UNIT (lhs_type));
      ಆದರೆ (ಗಾತ್ರ_2 != 1 && ಗಾತ್ರ_2 != 2 && ಗಾತ್ರ_2 != 4 && ಗಾತ್ರ_2 != 8 && ಗಾತ್ರ_2 != 16)
	ಹೋಗು cas_loop;

      /* If this is a pointer type, we need to multiply by the size of
	 the pointer target type.  */
      ಆದರೆ (ಸೂಚಕ_TYPE_P (lhs_type))
	{
	  ಆದರೆ (!COMPLETE_TYPE_P (ವೃಕ್ಷ_TYPE (lhs_type))
	      /* ??? This would introduce -Wdiscarded-qualifiers
		 warning: __atomic_fetch_* expect volatile void *
		 type as the first argument.  (Assignments between
		 atomic and non-atomic objects are OK.) */
	      || TYPE_RESTRICT (lhs_type))
	    ಹೋಗು cas_loop;
	  ವೃಕ್ಷ sz = TYPE_ಗಾತ್ರ_UNIT (ವೃಕ್ಷ_TYPE (lhs_type));
	  rhs = fold_build2_loc (loc, MULT_ಅಭಿವ್ಯಕ್ತಿ, ptrdiff_type_ಗಂಟು,
				 convert (ptrdiff_type_ಗಂಟು, rhs),
				 convert (ptrdiff_type_ಗಂಟು, sz));
	}

      /* Build __atomic_fetch_* (&lhs, &val, SEQ_CST), or
	 __atomic_*_fetch (&lhs, &val, SEQ_CST).  */
      fndecl = builtin_decl_explicit (fncode);
      params->ಶೀಘ್ರ_ತಳ್ಳು (lhs_addr);
      params->ಶೀಘ್ರ_ತಳ್ಳು (rhs);
      params->ಶೀಘ್ರ_ತಳ್ಳು (seq_cst);
      func_call = c_build_function_call_vec (loc, vNULL, fndecl, params, ಖಾಲಿ);

      newval = create_tmp_var_raw (nonatomic_lhs_type);
      ವೃಕ್ಷ_ADDRESSABLE (newval) = 1;
      suppress_warning (newval);
      rhs = build4 (ಗುರಿ_ಅಭಿವ್ಯಕ್ತಿ, nonatomic_lhs_type, newval, func_call,
		    NULL_ವೃಕ್ಷ, NULL_ವೃಕ್ಷ);
      ಗಣ_ಅಭಿವ್ಯಕ್ತಿ_LOCATION (rhs, loc);
      ಕೂಡಿಸು_stmt (rhs);

      /* Finish the compound statement.  */
      compound_stmt = c_ಕೊನೆ_compound_stmt (loc, compound_stmt, ಸುಳ್ಳು);

      /* NEWVAL is the value which was stored, return a COMPOUND_STMT of
	 the statement and that value.  */
      ಹಿಂತಿರುಗಿ build2 (COMPOUND_ಅಭಿವ್ಯಕ್ತಿ, nonatomic_lhs_type, compound_stmt, newval);
    }

cas_loop:
  /* Create the variables and labels required for the op= form.  */
  old = create_tmp_var_raw (nonatomic_lhs_type);
  old_addr = build_unary_op (loc, ADDR_ಅಭಿವ್ಯಕ್ತಿ, old, ಸುಳ್ಳು);
  ವೃಕ್ಷ_ADDRESSABLE (old) = 1;
  suppress_warning (old);

  newval = create_tmp_var_raw (nonatomic_lhs_type);
  newval_addr = build_unary_op (loc, ADDR_ಅಭಿವ್ಯಕ್ತಿ, newval, ಸುಳ್ಳು);
  ವೃಕ್ಷ_ADDRESSABLE (newval) = 1;
  suppress_warning (newval);

  loop_decl = create_artificial_label (loc);
  loop_label = build1 (LABEL_ಅಭಿವ್ಯಕ್ತಿ, void_type_ಗಂಟು, loop_decl);

  ಮುಗಿದ_decl = create_artificial_label (loc);
  ಮುಗಿದ_label = build1 (LABEL_ಅಭಿವ್ಯಕ್ತಿ, void_type_ಗಂಟು, ಮುಗಿದ_decl);

  /* __atomic_load (addr, &old, SEQ_CST).  */
  fndecl = builtin_decl_explicit (BUILT_ಒಳ_ATOMIC_ತುಂಬು);
  params->ಶೀಘ್ರ_ತಳ್ಳು (lhs_addr);
  params->ಶೀಘ್ರ_ತಳ್ಳು (old_addr);
  params->ಶೀಘ್ರ_ತಳ್ಳು (seq_cst);
  func_call = c_build_function_call_vec (loc, vNULL, fndecl, params, ಖಾಲಿ);
  old = build4 (ಗುರಿ_ಅಭಿವ್ಯಕ್ತಿ, nonatomic_lhs_type, old, func_call, NULL_ವೃಕ್ಷ,
		NULL_ವೃಕ್ಷ);
  ಕೂಡಿಸು_stmt (old);
  params->truncate (0);

  /* Create the expressions for floating-point environment
     manipulation, if required.  */
  ತಾರ್ಕಿಕ need_fenv = (flag_trapping_math
		    && (FLOAT_TYPE_P (lhs_type) || FLOAT_TYPE_P (rhs_type)));
  ವೃಕ್ಷ hold_call = NULL_ವೃಕ್ಷ, clear_call = NULL_ವೃಕ್ಷ, update_call = NULL_ವೃಕ್ಷ;
  ಆದರೆ (need_fenv)
    targetm.atomic_ನಿಯೋಜಿಸು_expand_fenv (&hold_call, &clear_call, &update_call);

  ಆದರೆ (hold_call)
    ಕೂಡಿಸು_stmt (hold_call);

  /* loop:  */
  ಕೂಡಿಸು_stmt (loop_label);

  /* newval = old + val;  */
  ಆದರೆ (rhs_type != rhs_semantic_type)
    val = build1 (EXCESS_PRECISION_ಅಭಿವ್ಯಕ್ತಿ, nonatomic_rhs_semantic_type, val);
  rhs = build_ದ್ವಿಮಾನ_op (loc, modifycode,
			 convert_lvalue_ಗಮ್ಯ_rvalue (loc, old, ನಿಜ, ನಿಜ),
			 val, ನಿಜ);
  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (rhs) == EXCESS_PRECISION_ಅಭಿವ್ಯಕ್ತಿ)
    {
      ವೃಕ್ಷ eptype = ವೃಕ್ಷ_TYPE (rhs);
      rhs = c_fully_fold (ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (rhs, 0), ಸುಳ್ಳು, ಖಾಲಿ);
      rhs = build1 (EXCESS_PRECISION_ಅಭಿವ್ಯಕ್ತಿ, eptype, rhs);
    }
  ಇಲ್ಲದಿದ್ದರೆ
    rhs = c_fully_fold (rhs, ಸುಳ್ಳು, ಖಾಲಿ);
  rhs = convert_for_assignment (loc, UNKNOWN_LOCATION, nonatomic_lhs_type,
				rhs, NULL_ವೃಕ್ಷ, ic_ನಿಯೋಜಿಸು, ಸುಳ್ಳು, NULL_ವೃಕ್ಷ,
				NULL_ವೃಕ್ಷ, 0);
  /* The temporary variable for NEWVAL is only gimplified correctly (in
     particular, given a DECL_CONTEXT) if used in a TARGET_EXPR.  To avoid
     subsequent ICEs in nested function processing after an error, ensure such
     a TARGET_EXPR is built even after an error.  */
  ಆದರೆ (rhs == error_mark_ಗಂಟು)
    rhs = old;
  rhs = build4 (ಗುರಿ_ಅಭಿವ್ಯಕ್ತಿ, nonatomic_lhs_type, newval, rhs, NULL_ವೃಕ್ಷ,
		NULL_ವೃಕ್ಷ);
  ಗಣ_ಅಭಿವ್ಯಕ್ತಿ_LOCATION (rhs, loc);
  ಕೂಡಿಸು_stmt (rhs);

  /* if (__atomic_compare_exchange (addr, &old, &new, false, SEQ_CST, SEQ_CST))
       goto done;  */
  fndecl = builtin_decl_explicit (BUILT_ಒಳ_ATOMIC_COMPARE_EXCHANGE);
  params->ಶೀಘ್ರ_ತಳ್ಳು (lhs_addr);
  params->ಶೀಘ್ರ_ತಳ್ಳು (old_addr);
  params->ಶೀಘ್ರ_ತಳ್ಳು (newval_addr);
  params->ಶೀಘ್ರ_ತಳ್ಳು (integer_zero_ಗಂಟು);
  params->ಶೀಘ್ರ_ತಳ್ಳು (seq_cst);
  params->ಶೀಘ್ರ_ತಳ್ಳು (seq_cst);
  func_call = c_build_function_call_vec (loc, vNULL, fndecl, params, ಖಾಲಿ);

  goto_stmt = build1 (GOTO_ಅಭಿವ್ಯಕ್ತಿ, void_type_ಗಂಟು, ಮುಗಿದ_decl);
  ಗಣ_ಅಭಿವ್ಯಕ್ತಿ_LOCATION (goto_stmt, loc);

  stmt = build3 (COND_ಅಭಿವ್ಯಕ್ತಿ, void_type_ಗಂಟು, func_call, goto_stmt, NULL_ವೃಕ್ಷ);
  ಗಣ_ಅಭಿವ್ಯಕ್ತಿ_LOCATION (stmt, loc);
  ಕೂಡಿಸು_stmt (stmt);

  ಆದರೆ (clear_call)
    ಕೂಡಿಸು_stmt (clear_call);

  /* goto loop;  */
  goto_stmt  = build1 (GOTO_ಅಭಿವ್ಯಕ್ತಿ, void_type_ಗಂಟು, loop_decl);
  ಗಣ_ಅಭಿವ್ಯಕ್ತಿ_LOCATION (goto_stmt, loc);
  ಕೂಡಿಸು_stmt (goto_stmt);

  /* done:  */
  ಕೂಡಿಸು_stmt (ಮುಗಿದ_label);

  ಆದರೆ (update_call)
    ಕೂಡಿಸು_stmt (update_call);

  /* Finish the compound statement.  */
  compound_stmt = c_ಕೊನೆ_compound_stmt (loc, compound_stmt, ಸುಳ್ಳು);

  /* NEWVAL is the value that was successfully stored, return a
     COMPOUND_EXPR of the statement and the appropriate value.  */
  ಹಿಂತಿರುಗಿ build2 (COMPOUND_ಅಭಿವ್ಯಕ್ತಿ, nonatomic_lhs_type, compound_stmt,
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
build_unary_op (location_t location, ಎಣಿಕೆ ವೃಕ್ಷ_ಸಂಕೇತ_2 ಸಂಕೇತ_2, ವೃಕ್ಷ xarg,
		ತಾರ್ಕಿಕ noconvert)
{
  /* No default_conversion here.  It causes trouble for ADDR_EXPR.  */
  ವೃಕ್ಷ arg = xarg;
  ವೃಕ್ಷ argtype = NULL_ವೃಕ್ಷ;
  ಎಣಿಕೆ ವೃಕ್ಷ_ಸಂಕೇತ_2 typecode;
  ವೃಕ್ಷ val;
  ವೃಕ್ಷ ret = error_mark_ಗಂಟು;
  ವೃಕ್ಷ eptype = NULL_ವೃಕ್ಷ;
  ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *invalid_op_diag;

  /* If ARG is wrapped in a call to .ACCESS_WITH_SIZE — created when the
     C parser rvalue-converts a counted_by-annotated member access (see
     PR123569) — unwrap it here.  Unary operators that consume an rvalue
     (!, -, +) read the value itself rather than dereferencing into the
     pointed-to data, so the bounds-checking wrapper is unnecessary and
     would otherwise reach build_unary_op while it is not equipped to
     handle the wrapped form.  PR123569 fixed the ++/-- side of this by
     suppressing wrapper creation in the parser; the rvalue-consuming
     ops still receive the wrapper and need to strip it here.  */
  ಆದರೆ (is_access_with_ಗಾತ್ರ_p (arg))
    xarg = arg = get_ref_from_access_with_ಗಾತ್ರ (arg);

  gcc_checking_assert (!is_access_with_ಗಾತ್ರ_p (arg));

  ತಾರ್ಕಿಕ int_operands = ಅಭಿವ್ಯಕ್ತಿ_INT_CONST_OPERANDS (xarg);
  ಆದರೆ (int_operands)
    arg = remove_c_maybe_const_ಅಭಿವ್ಯಕ್ತಿ (arg);

  ಆದರೆ (ಸಂಕೇತ_2 != ADDR_ಅಭಿವ್ಯಕ್ತಿ)
    arg = require_complete_type (location, arg);

  typecode = ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (arg));
  ಆದರೆ (typecode == ERROR_MARK)
    ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
  ಆದರೆ (typecode == ENUMERAL_TYPE || typecode == BOOLEAN_TYPE)
    typecode = INTEGER_TYPE;

  ಆದರೆ ((invalid_op_diag
       = targetm.invalid_unary_op (ಸಂಕೇತ_2, ವೃಕ್ಷ_TYPE (xarg))))
    {
      error_at (location, invalid_op_diag);
      ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
    }

  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (arg) == EXCESS_PRECISION_ಅಭಿವ್ಯಕ್ತಿ)
    {
      eptype = ವೃಕ್ಷ_TYPE (arg);
      arg = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (arg, 0);
    }

  ಆಯ್ಕೆ (ಸಂಕೇತ_2)
    {
    ಸ್ಥಿತಿ CONVERT_ಅಭಿವ್ಯಕ್ತಿ:
      /* This is used for unary plus, because a CONVERT_EXPR
	 is enough to prevent anybody from looking inside for
	 associativity, but won't generate any code.  */
      ಆದರೆ (!(typecode == INTEGER_TYPE || typecode == REAL_TYPE
	    || typecode == FIXED_ಬಿಂದು_TYPE || typecode == COMPLEX_TYPE
	    || typecode == BITINT_TYPE
	    || gnu_ಸದಿಶ_type_p (ವೃಕ್ಷ_TYPE (arg))))
	{
	  error_at (location, "wrong type argument to unary plus");
	  ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
	}
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!noconvert)
	arg = default_conversion (arg);
      arg = non_lvalue_loc (location, arg);
      ನಿಲ್ಲಿಸು;

    ಸ್ಥಿತಿ NEGATE_ಅಭಿವ್ಯಕ್ತಿ:
      ಆದರೆ (!(typecode == INTEGER_TYPE || typecode == REAL_TYPE
	    || typecode == FIXED_ಬಿಂದು_TYPE || typecode == COMPLEX_TYPE
	    || typecode == BITINT_TYPE
	    || gnu_ಸದಿಶ_type_p (ವೃಕ್ಷ_TYPE (arg))))
	{
	  error_at (location, "wrong type argument to unary minus");
	  ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
	}
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!noconvert)
	arg = default_conversion (arg);
      ನಿಲ್ಲಿಸು;

    ಸ್ಥಿತಿ ಬಿಟ್_NOT_ಅಭಿವ್ಯಕ್ತಿ:
      /* ~ works on integer types and non float vectors. */
      ಆದರೆ (typecode == INTEGER_TYPE
	  || typecode == BITINT_TYPE
	  || (gnu_ಸದಿಶ_type_p (ವೃಕ್ಷ_TYPE (arg))
	      && !ಸದಿಶ_FLOAT_TYPE_P (ವೃಕ್ಷ_TYPE (arg))))
	{
	  ವೃಕ್ಷ e = arg;

	  /* Warn if the expression has boolean value.  */
	  ಆಗ (ವೃಕ್ಷ_ಸಂಕೇತ (e) == COMPOUND_ಅಭಿವ್ಯಕ್ತಿ)
	    e = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (e, 1);

	  ಆದರೆ ((C_BOOLEAN_TYPE_P (ವೃಕ್ಷ_TYPE (arg))
	       || truth_ಮೌಲ್ಯ_p (ವೃಕ್ಷ_ಸಂಕೇತ (e))))
	    {
	      auto_diagnostic_ಗುಂಪು d;
	      ಆದರೆ (warning_at (location, OPT_Wbool_operation,
				"%<~%> on a boolean expression"))
		{
		  gcc_rich_location richloc (location);
		  richloc.ಕೂಡಿಸು_fixit_ಸೇರಿಸು_before (location, "!");
		  inform (&richloc, "did you mean to use logical not?");
		}
	    }
	  ಆದರೆ (!noconvert)
	    arg = default_conversion (arg);
	}
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (typecode == COMPLEX_TYPE)
	{
	  ಸಂಕೇತ_2 = CONJ_ಅಭಿವ್ಯಕ್ತಿ;
	  pedwarn (location, OPT_Wpedantic,
		   "ISO C does not support %<~%> for complex conjugation");
	  ಆದರೆ (!noconvert)
	    arg = default_conversion (arg);
	}
      ಇಲ್ಲದಿದ್ದರೆ
	{
	  error_at (location, "wrong type argument to bit-complement");
	  ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
	}
      ನಿಲ್ಲಿಸು;

    ಸ್ಥಿತಿ ABS_ಅಭಿವ್ಯಕ್ತಿ:
      ಆದರೆ (!(typecode == INTEGER_TYPE || typecode == REAL_TYPE))
	{
	  error_at (location, "wrong type argument to abs");
	  ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
	}
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!noconvert)
	arg = default_conversion (arg);
      ನಿಲ್ಲಿಸು;

    ಸ್ಥಿತಿ ABSU_ಅಭಿವ್ಯಕ್ತಿ:
      ಆದರೆ (!(typecode == INTEGER_TYPE))
	{
	  error_at (location, "wrong type argument to absu");
	  ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
	}
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!noconvert)
	arg = default_conversion (arg);
      ನಿಲ್ಲಿಸು;

    ಸ್ಥಿತಿ CONJ_ಅಭಿವ್ಯಕ್ತಿ:
      /* Conjugating a real value is a no-op, but allow it anyway.  */
      ಆದರೆ (!(typecode == INTEGER_TYPE || typecode == REAL_TYPE
	    || typecode == COMPLEX_TYPE))
	{
	  error_at (location, "wrong type argument to conjugation");
	  ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
	}
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!noconvert)
	arg = default_conversion (arg);
      ನಿಲ್ಲಿಸು;

    ಸ್ಥಿತಿ TRUTH_NOT_ಅಭಿವ್ಯಕ್ತಿ:
      ಆದರೆ (typecode != INTEGER_TYPE && typecode != FIXED_ಬಿಂದು_TYPE
	  && typecode != REAL_TYPE && typecode != ಸೂಚಕ_TYPE
	  && typecode != COMPLEX_TYPE && typecode != NULLPTR_TYPE
	  && typecode != BITINT_TYPE)
	{
	  error_at (location,
		    "wrong type argument to unary exclamation mark");
	  ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
	}
      ಆದರೆ (int_operands)
	{
	  arg = c_objc_common_truthvalue_conversion (location, xarg);
	  arg = remove_c_maybe_const_ಅಭಿವ್ಯಕ್ತಿ (arg);
	}
      ಇಲ್ಲದಿದ್ದರೆ
	arg = c_objc_common_truthvalue_conversion (location, arg);
      ret = invert_truthvalue_loc (location, arg);
      eptype = NULL_ವೃಕ್ಷ;
      /* If the TRUTH_NOT_EXPR has been folded, reset the location.  */
      ಆದರೆ (ಅಭಿವ್ಯಕ್ತಿ_P (ret) && ಅಭಿವ್ಯಕ್ತಿ_HAS_LOCATION (ret))
	location = ಅಭಿವ್ಯಕ್ತಿ_LOCATION (ret);
      ಹೋಗು return_build_unary_op;

    ಸ್ಥಿತಿ REALPART_ಅಭಿವ್ಯಕ್ತಿ:
    ಸ್ಥಿತಿ IMAGPART_ಅಭಿವ್ಯಕ್ತಿ:
      ret = build_real_imag_ಅಭಿವ್ಯಕ್ತಿ (location, ಸಂಕೇತ_2, arg);
      ಆದರೆ (ret == error_mark_ಗಂಟು)
	ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
      ಆದರೆ (eptype && ವೃಕ್ಷ_ಸಂಕೇತ (eptype) == COMPLEX_TYPE)
	eptype = ವೃಕ್ಷ_TYPE (eptype);
      ಹೋಗು return_build_unary_op;

    ಸ್ಥಿತಿ PREINCREMENT_ಅಭಿವ್ಯಕ್ತಿ:
    ಸ್ಥಿತಿ POSTINCREMENT_ಅಭಿವ್ಯಕ್ತಿ:
    ಸ್ಥಿತಿ PREDECREMENT_ಅಭಿವ್ಯಕ್ತಿ:
    ಸ್ಥಿತಿ POSTDECREMENT_ಅಭಿವ್ಯಕ್ತಿ:

      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (arg) == C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ)
	{
	  ವೃಕ್ಷ inner = build_unary_op (location, ಸಂಕೇತ_2,
				       C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ_ಅಭಿವ್ಯಕ್ತಿ (arg),
				       noconvert);
	  ಆದರೆ (inner == error_mark_ಗಂಟು)
	    ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
	  ret = build2 (C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (inner),
			C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ_PRE (arg), inner);
	  gcc_assert (!C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ_INT_OPERANDS (arg));
	  C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ_NON_CONST (ret) = 1;
	  ಹೋಗು return_build_unary_op;
	}

      /* Complain about anything that is not a true lvalue.  In
	 Objective-C, skip this check for property_refs.  */
      ಆದರೆ (!objc_is_property_ref (arg)
	  && !lvalue_or_else (location,
			      arg, ((ಸಂಕೇತ_2 == PREINCREMENT_ಅಭಿವ್ಯಕ್ತಿ
				     || ಸಂಕೇತ_2 == POSTINCREMENT_ಅಭಿವ್ಯಕ್ತಿ)
				    ? lv_increment
				    : lv_decrement)))
	ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;

      ಆದರೆ (warn_cxx_compat && ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (arg)) == ENUMERAL_TYPE)
	{
	  ಆದರೆ (ಸಂಕೇತ_2 == PREINCREMENT_ಅಭಿವ್ಯಕ್ತಿ || ಸಂಕೇತ_2 == POSTINCREMENT_ಅಭಿವ್ಯಕ್ತಿ)
	    warning_at (location, OPT_Wc___compat,
			"increment of enumeration value is invalid in C++");
	  ಇಲ್ಲದಿದ್ದರೆ
	    warning_at (location, OPT_Wc___compat,
			"decrement of enumeration value is invalid in C++");
	}

      ಆದರೆ (C_BOOLEAN_TYPE_P (ವೃಕ್ಷ_TYPE (arg)))
	{
	  ಆದರೆ (ಸಂಕೇತ_2 == PREINCREMENT_ಅಭಿವ್ಯಕ್ತಿ || ಸಂಕೇತ_2 == POSTINCREMENT_ಅಭಿವ್ಯಕ್ತಿ)
	    warning_at (location, OPT_Wbool_operation,
			"increment of a boolean expression");
	  ಇಲ್ಲದಿದ್ದರೆ
	    warning_at (location, OPT_Wbool_operation,
			"decrement of a boolean expression");
	}

      /* Ensure the argument is fully folded inside any SAVE_EXPR.  */
      arg = c_fully_fold (arg, ಸುಳ್ಳು, ಖಾಲಿ, ನಿಜ);

      ತಾರ್ಕಿಕ atomic_op;
      atomic_op = really_atomic_lvalue (arg);

      /* Increment or decrement the real part of the value,
	 and don't change the imaginary part.  */
      ಆದರೆ (typecode == COMPLEX_TYPE)
	{
	  ವೃಕ್ಷ real, imag;

	  pedwarn_c23 (location, OPT_Wpedantic,
		       "ISO C does not support %<++%> and %<--%> on complex "
		       "types before C2Y");

	  ಆದರೆ (!atomic_op)
	    {
	      arg = stabilize_reference (arg);
	      real = build_unary_op (ಅಭಿವ್ಯಕ್ತಿ_LOCATION (arg), REALPART_ಅಭಿವ್ಯಕ್ತಿ, arg,
				     ನಿಜ);
	      imag = build_unary_op (ಅಭಿವ್ಯಕ್ತಿ_LOCATION (arg), IMAGPART_ಅಭಿವ್ಯಕ್ತಿ, arg,
				     ನಿಜ);
	      real = build_unary_op (ಅಭಿವ್ಯಕ್ತಿ_LOCATION (arg), ಸಂಕೇತ_2, real, ನಿಜ);
	      ಆದರೆ (real == error_mark_ಗಂಟು || imag == error_mark_ಗಂಟು)
		ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
	      ret = build2 (COMPLEX_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (arg),
			    real, imag);
	      ಹೋಗು return_build_unary_op;
	    }
	}

      /* Report invalid types.  */

      ಆದರೆ (typecode != ಸೂಚಕ_TYPE && typecode != FIXED_ಬಿಂದು_TYPE
	  && typecode != INTEGER_TYPE && typecode != REAL_TYPE
	  && typecode != COMPLEX_TYPE && typecode != BITINT_TYPE
	  && !gnu_ಸದಿಶ_type_p (ವೃಕ್ಷ_TYPE (arg)))
	{
	  ಆದರೆ (ಸಂಕೇತ_2 == PREINCREMENT_ಅಭಿವ್ಯಕ್ತಿ || ಸಂಕೇತ_2 == POSTINCREMENT_ಅಭಿವ್ಯಕ್ತಿ)
	    error_at (location, "wrong type argument to increment");
	  ಇಲ್ಲದಿದ್ದರೆ
	    error_at (location, "wrong type argument to decrement");

	  ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
	}

      {
	ವೃಕ್ಷ inc;

	argtype = ವೃಕ್ಷ_TYPE (arg);

	/* Compute the increment.  */

	ಆದರೆ (typecode == ಸೂಚಕ_TYPE)
	  {
	    /* If pointer target is an incomplete type,
	       we just cannot know how to do the arithmetic.  */
	    ಆದರೆ (!COMPLETE_OR_VOID_TYPE_P (ವೃಕ್ಷ_TYPE (argtype)))
	      {
		ಆದರೆ (ಸಂಕೇತ_2 == PREINCREMENT_ಅಭಿವ್ಯಕ್ತಿ || ಸಂಕೇತ_2 == POSTINCREMENT_ಅಭಿವ್ಯಕ್ತಿ)
		  error_at (location,
			    "increment of pointer to an incomplete type %qT",
			    ವೃಕ್ಷ_TYPE (argtype));
		ಇಲ್ಲದಿದ್ದರೆ
		  error_at (location,
			    "decrement of pointer to an incomplete type %qT",
			    ವೃಕ್ಷ_TYPE (argtype));
	      }
	    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (argtype)) == FUNCTION_TYPE
		     || VOID_TYPE_P (ವೃಕ್ಷ_TYPE (argtype)))
	      {
		ಆದರೆ (ಸಂಕೇತ_2 == PREINCREMENT_ಅಭಿವ್ಯಕ್ತಿ || ಸಂಕೇತ_2 == POSTINCREMENT_ಅಭಿವ್ಯಕ್ತಿ)
		  pedwarn (location, OPT_Wpointer_arith,
			   "wrong type argument to increment");
		ಇಲ್ಲದಿದ್ದರೆ
		  pedwarn (location, OPT_Wpointer_arith,
			   "wrong type argument to decrement");
	      }
	    ಇಲ್ಲದಿದ್ದರೆ
	      verify_type_context (location, TCTX_ಸೂಚಕ_ARITH,
				   ವೃಕ್ಷ_TYPE (argtype));

	    inc = c_ಗಾತ್ರ_ಒಳ_ಬೈಟುಗಳು (ವೃಕ್ಷ_TYPE (argtype));
	    inc = convert_ಗಮ್ಯ_ptrofftype_loc (location, inc);
	  }
	ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (FRACT_ಬಹುಲಕ_P (TYPE_ಬಹುಲಕ (argtype)))
	  {
	    /* For signed fract types, we invert ++ to -- or
	       -- to ++, and change inc from 1 to -1, because
	       it is not possible to represent 1 in signed fract constants.
	       For unsigned fract types, the result always overflows and
	       we get an undefined (original) or the maximum value.  */
	    ಆದರೆ (ಸಂಕೇತ_2 == PREINCREMENT_ಅಭಿವ್ಯಕ್ತಿ)
	      ಸಂಕೇತ_2 = PREDECREMENT_ಅಭಿವ್ಯಕ್ತಿ;
	    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ಸಂಕೇತ_2 == PREDECREMENT_ಅಭಿವ್ಯಕ್ತಿ)
	      ಸಂಕೇತ_2 = PREINCREMENT_ಅಭಿವ್ಯಕ್ತಿ;
	    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ಸಂಕೇತ_2 == POSTINCREMENT_ಅಭಿವ್ಯಕ್ತಿ)
	      ಸಂಕೇತ_2 = POSTDECREMENT_ಅಭಿವ್ಯಕ್ತಿ;
	    ಇಲ್ಲದಿದ್ದರೆ /* code == POSTDECREMENT_EXPR  */
	      ಸಂಕೇತ_2 = POSTINCREMENT_ಅಭಿವ್ಯಕ್ತಿ;

	    inc = integer_minus_one_ಗಂಟು;
	    inc = convert (argtype, inc);
	  }
	ಇಲ್ಲದಿದ್ದರೆ
	  {
	    inc = ಸದಿಶ_TYPE_P (argtype)
	      ? build_one_cst (argtype)
	      : integer_one_ಗಂಟು;
	    inc = convert (argtype, inc);
	  }

	/* If 'arg' is an Objective-C PROPERTY_REF expression, then we
	   need to ask Objective-C to build the increment or decrement
	   expression for it.  */
	ಆದರೆ (objc_is_property_ref (arg))
	  ಹಿಂತಿರುಗಿ objc_build_incr_ಅಭಿವ್ಯಕ್ತಿ_for_property_ref (location, ಸಂಕೇತ_2,
							arg, inc);

	/* Report a read-only lvalue.  */
	ಆದರೆ (TYPE_READONLY (argtype))
	  {
	    readonly_error (location, arg,
			    ((ಸಂಕೇತ_2 == PREINCREMENT_ಅಭಿವ್ಯಕ್ತಿ
			      || ಸಂಕೇತ_2 == POSTINCREMENT_ಅಭಿವ್ಯಕ್ತಿ)
			     ? lv_increment : lv_decrement));
	    ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
	  }
	ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ವೃಕ್ಷ_READONLY (arg))
	  readonly_warning (arg,
			    ((ಸಂಕೇತ_2 == PREINCREMENT_ಅಭಿವ್ಯಕ್ತಿ
			      || ಸಂಕೇತ_2 == POSTINCREMENT_ಅಭಿವ್ಯಕ್ತಿ)
			     ? lv_increment : lv_decrement));

	/* If the argument is atomic, use the special code sequences for
	   atomic compound assignment.  */
	ಆದರೆ (atomic_op)
	  {
	    arg = stabilize_reference (arg);
	    ret = build_atomic_ನಿಯೋಜಿಸು (location, arg,
				       ((ಸಂಕೇತ_2 == PREINCREMENT_ಅಭಿವ್ಯಕ್ತಿ
					 || ಸಂಕೇತ_2 == POSTINCREMENT_ಅಭಿವ್ಯಕ್ತಿ)
					? PLUS_ಅಭಿವ್ಯಕ್ತಿ
					: MINUS_ಅಭಿವ್ಯಕ್ತಿ),
				       (FRACT_ಬಹುಲಕ_P (TYPE_ಬಹುಲಕ (argtype))
					? inc
					: integer_one_ಗಂಟು),
				       (ಸಂಕೇತ_2 == POSTINCREMENT_ಅಭಿವ್ಯಕ್ತಿ
					|| ಸಂಕೇತ_2 == POSTDECREMENT_ಅಭಿವ್ಯಕ್ತಿ));
	    ಹೋಗು return_build_unary_op;
	  }

	ವೃಕ್ಷ true_res;
	ಆದರೆ (c_hardbool_type_attr (ವೃಕ್ಷ_TYPE (arg), ಖಾಲಿ, &true_res))
	  {
	    ವೃಕ್ಷ larg = stabilize_reference (arg);
	    ವೃಕ್ಷ sarg = save_ಅಭಿವ್ಯಕ್ತಿ (larg);
	    ಆಯ್ಕೆ (ಸಂಕೇತ_2)
	      {
	      ಸ್ಥಿತಿ PREINCREMENT_ಅಭಿವ್ಯಕ್ತಿ:
		val = build2 (MODIFY_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (larg), larg, true_res);
		val = build2 (COMPOUND_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (larg), sarg, val);
		ನಿಲ್ಲಿಸು;
	      ಸ್ಥಿತಿ POSTINCREMENT_ಅಭಿವ್ಯಕ್ತಿ:
		val = build2 (MODIFY_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (larg), larg, true_res);
		val = build2 (COMPOUND_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (larg), val, sarg);
		val = build2 (COMPOUND_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (larg), sarg, val);
		ನಿಲ್ಲಿಸು;
	      ಸ್ಥಿತಿ PREDECREMENT_ಅಭಿವ್ಯಕ್ತಿ:
		{
		  ವೃಕ್ಷ rarg = convert_lvalue_ಗಮ್ಯ_rvalue (location, sarg,
							ನಿಜ, ನಿಜ);
		  rarg = invert_truthvalue_loc (location, rarg);
		  rarg = convert (ವೃಕ್ಷ_TYPE (sarg), rarg);
		  val = build2 (MODIFY_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (larg), larg, rarg);
		}
		ನಿಲ್ಲಿಸು;
	      ಸ್ಥಿತಿ POSTDECREMENT_ಅಭಿವ್ಯಕ್ತಿ:
		{
		  ವೃಕ್ಷ rarg = convert_lvalue_ಗಮ್ಯ_rvalue (location, sarg,
							ನಿಜ, ನಿಜ);
		  rarg = invert_truthvalue_loc (location, rarg);
		  ವೃಕ್ಷ iarg = convert (ವೃಕ್ಷ_TYPE (larg), rarg);
		  val = build2 (MODIFY_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (larg), larg, iarg);
		  val = build2 (COMPOUND_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (larg), val, sarg);
		  val = build2 (COMPOUND_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (larg), sarg, val);
		}
		ನಿಲ್ಲಿಸು;
	      ಪೂರ್ವನಿಯೋಜಿತ:
		gcc_unreachable ();
	      }
	    ವೃಕ್ಷ_SIDE_EFFECTS (val) = 1;
	  }
	ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (C_BOOLEAN_TYPE_P (ವೃಕ್ಷ_TYPE (arg)))
	  val = boolean_increment (ಸಂಕೇತ_2, arg);
	ಇಲ್ಲದಿದ್ದರೆ
	  val = build2 (ಸಂಕೇತ_2, ವೃಕ್ಷ_TYPE (arg), arg, inc);
	ವೃಕ್ಷ_SIDE_EFFECTS (val) = 1;
	ಆದರೆ (TYPE_QUALS (ವೃಕ್ಷ_TYPE (val)) != TYPE_UNQUALIFIED)
	  ವೃಕ್ಷ_TYPE (val) = c_build_qualified_type (ವೃಕ್ಷ_TYPE (val),
						    TYPE_UNQUALIFIED);
	ret = val;
	ಹೋಗು return_build_unary_op;
      }

    ಸ್ಥಿತಿ ADDR_ಅಭಿವ್ಯಕ್ತಿ:
      /* Note that this operation never does default_conversion.  */

      /* The operand of unary '&' must be an lvalue (which excludes
	 expressions of type void), or, in C99, the result of a [] or
	 unary '*' operator.  */
      ಆದರೆ (VOID_TYPE_P (ವೃಕ್ಷ_TYPE (arg))
	  && TYPE_QUALS (ವೃಕ್ಷ_TYPE (arg)) == TYPE_UNQUALIFIED
	  && (!ಪರೋಕ್ಷ_REF_P (arg) || !flag_isoc99))
	pedwarn (location, 0, "taking address of expression of type %<void%>");

      /* Let &* cancel out to simplify resulting code.  */
      ಆದರೆ (ಪರೋಕ್ಷ_REF_P (arg))
	{
	  /* Don't let this be an lvalue.  */
	  ಆದರೆ (lvalue_p (ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (arg, 0)))
	    ಹಿಂತಿರುಗಿ non_lvalue_loc (location, ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (arg, 0));
	  ret = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (arg, 0);
	  ಹೋಗು return_build_unary_op;
	}

      /* Anything not already handled and not a true memory reference
	 or a non-lvalue array is an error.  */
      ಆದರೆ (typecode != FUNCTION_TYPE && !noconvert
	  && !lvalue_or_else (location, arg, lv_addressof))
	ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;

      /* Move address operations inside C_MAYBE_CONST_EXPR to simplify
	 folding later.  */
      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (arg) == C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ)
	{
	  ವೃಕ್ಷ inner = build_unary_op (location, ಸಂಕೇತ_2,
				       C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ_ಅಭಿವ್ಯಕ್ತಿ (arg),
				       noconvert);
	  ret = build2 (C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (inner),
			C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ_PRE (arg), inner);
	  gcc_assert (!C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ_INT_OPERANDS (arg));
	  C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ_NON_CONST (ret)
	    = C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ_NON_CONST (arg);
	  ಹೋಗು return_build_unary_op;
	}

      /* Ordinary case; arg is a COMPONENT_REF or a decl.  */

      argtype = ವೃಕ್ಷ_TYPE (arg);

      /* If the lvalue is const or volatile, merge that into the type
	 to which the address will point.  This is only needed
	 for function types.  */
      ಆದರೆ ((DECL_P (arg) || REFERENCE_CLASS_P (arg))
	  && (ವೃಕ್ಷ_READONLY (arg) || ವೃಕ್ಷ_THIS_VOLATILE (arg))
	  && ವೃಕ್ಷ_ಸಂಕೇತ (argtype) == FUNCTION_TYPE)
	{
	  ಪೂರ್ಣಾಂಕ orig_quals = TYPE_QUALS (strip_array_types (argtype));
	  ಪೂರ್ಣಾಂಕ quals = orig_quals;

	  ಆದರೆ (ವೃಕ್ಷ_READONLY (arg))
	    quals |= TYPE_QUAL_CONST;
	  ಆದರೆ (ವೃಕ್ಷ_THIS_VOLATILE (arg))
	    quals |= TYPE_QUAL_VOLATILE;

	  argtype = c_build_qualified_type (argtype, quals);
	}

      ಆಯ್ಕೆ (ವೃಕ್ಷ_ಸಂಕೇತ (arg))
	{
	ಸ್ಥಿತಿ COMPONENT_REF:
	  ಆದರೆ (DECL_C_ಬಿಟ್_ಕ್ಷೇತ್ರ (ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (arg, 1)))
	    {
	      error_at (location, "cannot take address of bit-field %qD",
			ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (arg, 1));
	      ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
	    }

	  /* fall through */

	ಸ್ಥಿತಿ ARRAY_REF:
	  ಆದರೆ (TYPE_ಹಿಮ್ಮುಖ_STORAGE_ಕ್ರಮ (ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (arg, 0))))
	    {
	      ಆದರೆ (!AGGREGATE_TYPE_P (ವೃಕ್ಷ_TYPE (arg))
		  && !ಸೂಚಕ_TYPE_P (ವೃಕ್ಷ_TYPE (arg))
		  && !ಸದಿಶ_TYPE_P (ವೃಕ್ಷ_TYPE (arg)))
		{
		  error_at (location, "cannot take address of scalar with "
			    "reverse storage order");
		  ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
		}

	      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (arg)) == ARRAY_TYPE
		  && TYPE_ಹಿಮ್ಮುಖ_STORAGE_ಕ್ರಮ (ವೃಕ್ಷ_TYPE (arg)))
		warning_at (location, OPT_Wscalar_storage_ಕ್ರಮ,
			    "address of array with reverse scalar storage "
			    "order requested");
	    }

	ಪೂರ್ವನಿಯೋಜಿತ:
	  ನಿಲ್ಲಿಸು;
	}

      ಆದರೆ (!c_mark_addressable (arg))
	ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;

      gcc_assert (ವೃಕ್ಷ_ಸಂಕೇತ (arg) != COMPONENT_REF
		  || !DECL_C_ಬಿಟ್_ಕ್ಷೇತ್ರ (ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (arg, 1)));

      argtype = c_build_ಸೂಚಕ_type (argtype);

      /* ??? Cope with user tricks that amount to offsetof.  Delete this
	 when we have proper support for integer constant expressions.  */
      val = get_ತಳ_ವಿಳಾಸ (arg);
      ಆದರೆ (val && ಪರೋಕ್ಷ_REF_P (val)
          && ವೃಕ್ಷ_CONSTANT (ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (val, 0)))
	{
	  ret = fold_offsetof (arg, argtype);
	  ಹೋಗು return_build_unary_op;
	}

      val = build1 (ADDR_ಅಭಿವ್ಯಕ್ತಿ, argtype, arg);

      ret = val;
      ಹೋಗು return_build_unary_op;

    ಸ್ಥಿತಿ PAREN_ಅಭಿವ್ಯಕ್ತಿ:
      ret = build1 (ಸಂಕೇತ_2, ವೃಕ್ಷ_TYPE (arg), arg);
      ಹೋಗು return_build_unary_op;

    ಪೂರ್ವನಿಯೋಜಿತ:
      gcc_unreachable ();
    }

  ಆದರೆ (argtype == NULL_ವೃಕ್ಷ)
    argtype = ವೃಕ್ಷ_TYPE (arg);
  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (arg) == INTEGER_CST)
    ret = (require_constant_ಮೌಲ್ಯ
	   ? fold_build1_initializer_loc (location, ಸಂಕೇತ_2, argtype, arg)
	   : fold_build1_loc (location, ಸಂಕೇತ_2, argtype, arg));
  ಇಲ್ಲದಿದ್ದರೆ
    ret = build1 (ಸಂಕೇತ_2, argtype, arg);
 return_build_unary_op:
  gcc_assert (ret != error_mark_ಗಂಟು);
  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ret) == INTEGER_CST && !ವೃಕ್ಷ_ಅತಿಪ್ರವಾಹ (ret)
      && !(ವೃಕ್ಷ_ಸಂಕೇತ (xarg) == INTEGER_CST && !ವೃಕ್ಷ_ಅತಿಪ್ರವಾಹ (xarg)))
    ret = build1 (NOP_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (ret), ret);
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ret) != INTEGER_CST && int_operands)
    ret = note_integer_operands (ret);
  ಆದರೆ (eptype)
    ret = build1 (EXCESS_PRECISION_ಅಭಿವ್ಯಕ್ತಿ, eptype, ret);
  protected_ಗಣ_ಅಭಿವ್ಯಕ್ತಿ_location (ret, location);
  ಹಿಂತಿರುಗಿ ret;
}

/* Return nonzero if REF is an lvalue valid for this language.
   Lvalues can be assigned, unless their type has TYPE_READONLY.
   Lvalues can have their address taken, unless they have C_DECL_REGISTER.  */

ತಾರ್ಕಿಕ
lvalue_p (const_ವೃಕ್ಷ ref)
{
  ಸ್ಥಿರಾಂಕ ಎಣಿಕೆ ವೃಕ್ಷ_ಸಂಕೇತ_2 ಸಂಕೇತ_2 = ವೃಕ್ಷ_ಸಂಕೇತ (ref);

  ಆಯ್ಕೆ (ಸಂಕೇತ_2)
    {
    ಸ್ಥಿತಿ REALPART_ಅಭಿವ್ಯಕ್ತಿ:
    ಸ್ಥಿತಿ IMAGPART_ಅಭಿವ್ಯಕ್ತಿ:
    ಸ್ಥಿತಿ COMPONENT_REF:
      ಹಿಂತಿರುಗಿ lvalue_p (ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (ref, 0));

    ಸ್ಥಿತಿ C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ:
      ಹಿಂತಿರುಗಿ lvalue_p (ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (ref, 1));

    ಸ್ಥಿತಿ COMPOUND_LITERAL_ಅಭಿವ್ಯಕ್ತಿ:
    ಸ್ಥಿತಿ STRING_CST:
      ಹಿಂತಿರುಗಿ ನಿಜ;

    ಸ್ಥಿತಿ MEM_REF:
    ಸ್ಥಿತಿ ಗುರಿ_MEM_REF:
      /* MEM_REFs can appear from -fgimple parsing or folding, so allow them
	 here as well.  */
    ಸ್ಥಿತಿ ಪರೋಕ್ಷ_REF:
    ಸ್ಥಿತಿ ARRAY_REF:
    ಸ್ಥಿತಿ VAR_DECL:
    ಸ್ಥಿತಿ PARM_DECL:
    ಸ್ಥಿತಿ ಫಲಿತಾಂಶ_DECL:
    ಸ್ಥಿತಿ ERROR_MARK:
      ಹಿಂತಿರುಗಿ (ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (ref)) != FUNCTION_TYPE
	      && ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (ref)) != ವಿಧಾನ_TYPE);

    ಸ್ಥಿತಿ BIND_ಅಭಿವ್ಯಕ್ತಿ:
      ಹಿಂತಿರುಗಿ ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (ref)) == ARRAY_TYPE;

    ಸ್ಥಿತಿ CALL_ಅಭಿವ್ಯಕ್ತಿ:
      ಹಿಂತಿರುಗಿ is_access_with_ಗಾತ್ರ_p (ref);

    ಪೂರ್ವನಿಯೋಜಿತ:
      ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
    }
}

/* Give a warning for storing in something that is read-only in GCC
   terms but not const in ISO C terms.  */

ಸ್ಥಿರ ಶೂನ್ಯ
readonly_warning (ವೃಕ್ಷ arg, ಎಣಿಕೆ lvalue_use use)
{
  ಆಯ್ಕೆ (use)
    {
    ಸ್ಥಿತಿ lv_ನಿಯೋಜಿಸು:
      warning (0, "assignment of read-only location %qE", arg);
      ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ lv_increment:
      warning (0, "increment of read-only location %qE", arg);
      ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ lv_decrement:
      warning (0, "decrement of read-only location %qE", arg);
      ನಿಲ್ಲಿಸು;
    ಪೂರ್ವನಿಯೋಜಿತ:
      gcc_unreachable ();
    }
  ಹಿಂತಿರುಗಿ;
}


/* Return nonzero if REF is an lvalue valid for this language;
   otherwise, print an error message and return zero.  USE says
   how the lvalue is being used and so selects the error message.
   LOCATION is the location at which any error should be reported.  */

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ
lvalue_or_else (location_t loc, const_ವೃಕ್ಷ ref, ಎಣಿಕೆ lvalue_use use)
{
  ಪೂರ್ಣಾಂಕ win = lvalue_p (ref);

  ಆದರೆ (!win)
    lvalue_error (loc, use);

  ಹಿಂತಿರುಗಿ win;
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
c_mark_addressable (ವೃಕ್ಷ ಘಾತಾಂಕ, ತಾರ್ಕಿಕ array_ref_p, ತಾರ್ಕಿಕ override_ರಿಜಿಸ್ಟರ್)
{
  ವೃಕ್ಷ x = ಘಾತಾಂಕ;

  ಆಗ (1)
    ಆಯ್ಕೆ (ವೃಕ್ಷ_ಸಂಕೇತ (x))
      {
      ಸ್ಥಿತಿ VIEW_CONVERT_ಅಭಿವ್ಯಕ್ತಿ:
	ಆದರೆ (array_ref_p
	    && ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (x)) == ARRAY_TYPE
	    && ಸದಿಶ_TYPE_P (ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (x, 0))))
	  ಹಿಂತಿರುಗಿ ನಿಜ;
	x = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (x, 0);
	ನಿಲ್ಲಿಸು;

      ಸ್ಥಿತಿ COMPONENT_REF:
	ಆದರೆ (DECL_C_ಬಿಟ್_ಕ್ಷೇತ್ರ (ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (x, 1)))
	  {
	    error ("cannot take address of bit-field %qD",
		   ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (x, 1));
	    ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
	  }
	/* FALLTHRU */
      ಸ್ಥಿತಿ ADDR_ಅಭಿವ್ಯಕ್ತಿ:
      ಸ್ಥಿತಿ ARRAY_REF:
      ಸ್ಥಿತಿ REALPART_ಅಭಿವ್ಯಕ್ತಿ:
      ಸ್ಥಿತಿ IMAGPART_ಅಭಿವ್ಯಕ್ತಿ:
	x = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (x, 0);
	ನಿಲ್ಲಿಸು;

      ಸ್ಥಿತಿ COMPOUND_LITERAL_ಅಭಿವ್ಯಕ್ತಿ:
	ಆದರೆ (C_DECL_ರಿಜಿಸ್ಟರ್ (COMPOUND_LITERAL_ಅಭಿವ್ಯಕ್ತಿ_DECL (x)))
	  {
	    ಆದರೆ (override_ರಿಜಿಸ್ಟರ್)
	      DECL_ರಿಜಿಸ್ಟರ್ (COMPOUND_LITERAL_ಅಭಿವ್ಯಕ್ತಿ_DECL (x)) = 0;
	    ಇಲ್ಲದಿದ್ದರೆ
	      {
		error ("address of register compound literal requested");
		ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
	      }
	  }
	ವೃಕ್ಷ_ADDRESSABLE (x) = 1;
	ವೃಕ್ಷ_ADDRESSABLE (COMPOUND_LITERAL_ಅಭಿವ್ಯಕ್ತಿ_DECL (x)) = 1;
	ಹಿಂತಿರುಗಿ ನಿಜ;

      ಸ್ಥಿತಿ CONSTRUCTOR:
	ವೃಕ್ಷ_ADDRESSABLE (x) = 1;
	ಹಿಂತಿರುಗಿ ನಿಜ;

      ಸ್ಥಿತಿ VAR_DECL:
      ಸ್ಥಿತಿ CONST_DECL:
      ಸ್ಥಿತಿ PARM_DECL:
      ಸ್ಥಿತಿ ಫಲಿತಾಂಶ_DECL:
	ಆದರೆ (C_DECL_ರಿಜಿಸ್ಟರ್ (x)
	    && DECL_NONLOCAL (x))
	  {
	    ಆದರೆ (ವೃಕ್ಷ_ಬಹಿರಂಗ (x) || is_global_var (x))
	      {
		error
		  ("global register variable %qD used in nested function", x);
		ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
	      }
	    pedwarn (ಒಳಹರಿವು_location, 0, "register variable %qD used in nested function", x);
	  }
	ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (C_DECL_ರಿಜಿಸ್ಟರ್ (x))
	  {
	    ಆದರೆ (ವೃಕ್ಷ_ಬಹಿರಂಗ (x) || is_global_var (x))
	      error ("address of global register variable %qD requested", x);
	    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (override_ರಿಜಿಸ್ಟರ್ && !DECL_HARD_ರಿಜಿಸ್ಟರ್ (x))
	      {
		DECL_ರಿಜಿಸ್ಟರ್ (x) = 0;
		ವೃಕ್ಷ_ADDRESSABLE (x) = 1;
		mark_decl_ಬಳಸಿದ (x, ನಿಜ);
		ಹಿಂತಿರುಗಿ ನಿಜ;
	      }
	    ಇಲ್ಲದಿದ್ದರೆ
	      error ("address of register variable %qD requested", x);
	    ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
	  }

	/* FALLTHRU */
      ಸ್ಥಿತಿ FUNCTION_DECL:
	ವೃಕ್ಷ_ADDRESSABLE (x) = 1;
	mark_decl_ಬಳಸಿದ (x, ನಿಜ);
	/* FALLTHRU */
      ಪೂರ್ವನಿಯೋಜಿತ:
	ಹಿಂತಿರುಗಿ ನಿಜ;
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
  ಆದರೆ (ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ) == type)
    ಹಿಂತಿರುಗಿ ಅಭಿವ್ಯಕ್ತಿ;

  /* For C11, integer conversions may have results with excess
     precision.  */
  ಆದರೆ (flag_isoc11 || !semantic_type)
    ಹಿಂತಿರುಗಿ convert_and_check (loc, type, ಅಭಿವ್ಯಕ್ತಿ);

  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ)) == INTEGER_TYPE
      && ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ) != semantic_type)
    {
      /* For integers, we need to check the real conversion, not
	 the conversion to the excess precision type.  */
      ಅಭಿವ್ಯಕ್ತಿ = convert_and_check (loc, semantic_type, ಅಭಿವ್ಯಕ್ತಿ);
    }
  /* Result type is the excess precision type, which should be
     large enough, so do not check.  */
  ಹಿಂತಿರುಗಿ convert (type, ಅಭಿವ್ಯಕ್ತಿ);
}

/* If EXPR refers to a built-in declared without a prototype returns
   the actual type of the built-in and, if non-null, set *BLTIN to
   a pointer to the built-in.  Otherwise return the type of EXPR
   and clear *BLTIN if non-null.  */

ಸ್ಥಿರ ವೃಕ್ಷ
type_or_builtin_type (ವೃಕ್ಷ ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ *bltin = ಖಾಲಿ)
{
  ವೃಕ್ಷ dummy;
  ಆದರೆ (!bltin)
    bltin = &dummy;

  *bltin = NULL_ವೃಕ್ಷ;

  ವೃಕ್ಷ type = ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ);
  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ಅಭಿವ್ಯಕ್ತಿ) != ADDR_ಅಭಿವ್ಯಕ್ತಿ)
    ಹಿಂತಿರುಗಿ type;

  ವೃಕ್ಷ oper = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (ಅಭಿವ್ಯಕ್ತಿ, 0);
  ಆದರೆ (!DECL_P (oper)
      || ವೃಕ್ಷ_ಸಂಕೇತ (oper) != FUNCTION_DECL
      || !fndecl_built_ಒಳ_p (oper, BUILT_ಒಳ_ಸಾಮಾನ್ಯ))
    ಹಿಂತಿರುಗಿ type;

  built_ಒಳ_function ಸಂಕೇತ_2 = DECL_FUNCTION_ಸಂಕೇತ (oper);
  ಆದರೆ (!C_DECL_BUILTIN_PROTOTYPE (oper))
    ಹಿಂತಿರುಗಿ type;

  ಆದರೆ ((*bltin = builtin_decl_implicit (ಸಂಕೇತ_2)))
    type = c_build_ಸೂಚಕ_type (ವೃಕ್ಷ_TYPE (*bltin));

  ಹಿಂತಿರುಗಿ type;
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
  ವೃಕ್ಷ ಫಲಿತಾಂಶ_type = ಖಾಲಿ;
  ವೃಕ್ಷ semantic_ಫಲಿತಾಂಶ_type = ಖಾಲಿ;
  ವೃಕ್ಷ orig_op1 = op1, orig_op2 = op2;
  ತಾರ್ಕಿಕ int_const, op1_int_operands, op2_int_operands, int_operands;
  ತಾರ್ಕಿಕ ifexp_int_operands;
  ವೃಕ್ಷ ret;

  op1_int_operands = ಅಭಿವ್ಯಕ್ತಿ_INT_CONST_OPERANDS (orig_op1);
  ಆದರೆ (op1_int_operands)
    op1 = remove_c_maybe_const_ಅಭಿವ್ಯಕ್ತಿ (op1);
  op2_int_operands = ಅಭಿವ್ಯಕ್ತಿ_INT_CONST_OPERANDS (orig_op2);
  ಆದರೆ (op2_int_operands)
    op2 = remove_c_maybe_const_ಅಭಿವ್ಯಕ್ತಿ (op2);
  ifexp_int_operands = ಅಭಿವ್ಯಕ್ತಿ_INT_CONST_OPERANDS (ifexp);
  ಆದರೆ (ifexp_int_operands)
    ifexp = remove_c_maybe_const_ಅಭಿವ್ಯಕ್ತಿ (ifexp);

  /* Promote both alternatives.  */

  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (op1)) != VOID_TYPE)
    op1 = default_conversion (op1);
  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (op2)) != VOID_TYPE)
    op2 = default_conversion (op2);

  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ifexp) == ERROR_MARK
      || ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (op1)) == ERROR_MARK
      || ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (op2)) == ERROR_MARK)
    ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;

  ವೃಕ್ಷ bltin1 = NULL_ವೃಕ್ಷ;
  ವೃಕ್ಷ bltin2 = NULL_ವೃಕ್ಷ;
  type1 = type_or_builtin_type (op1, &bltin1);
  ಸ್ಥಿರಾಂಕ ಎಣಿಕೆ ವೃಕ್ಷ_ಸಂಕೇತ_2 code1 = ವೃಕ್ಷ_ಸಂಕೇತ (type1);
  type2 = type_or_builtin_type (op2, &bltin2);
  ಸ್ಥಿರಾಂಕ ಎಣಿಕೆ ವೃಕ್ಷ_ಸಂಕೇತ_2 code2 = ವೃಕ್ಷ_ಸಂಕೇತ (type2);

  ಆದರೆ (code1 == ಸೂಚಕ_TYPE && reject_gcc_builtin (op1))
    ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;

  ಆದರೆ (code2 == ಸೂಚಕ_TYPE && reject_gcc_builtin (op2))
    ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;

  /* C90 does not permit non-lvalue arrays in conditional expressions.
     In C99 they will be pointers by now.  */
  ಆದರೆ (code1 == ARRAY_TYPE || code2 == ARRAY_TYPE)
    {
      error_at (colon_loc, "non-lvalue array in conditional expression");
      ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
    }

  ಆದರೆ ((ವೃಕ್ಷ_ಸಂಕೇತ (op1) == EXCESS_PRECISION_ಅಭಿವ್ಯಕ್ತಿ
       || ವೃಕ್ಷ_ಸಂಕೇತ (op2) == EXCESS_PRECISION_ಅಭಿವ್ಯಕ್ತಿ)
      && (code1 == INTEGER_TYPE || code1 == REAL_TYPE
	  || code1 == COMPLEX_TYPE || code1 == BITINT_TYPE)
      && (code2 == INTEGER_TYPE || code2 == REAL_TYPE
	  || code2 == COMPLEX_TYPE || code2 == BITINT_TYPE))
    {
      semantic_ಫಲಿತಾಂಶ_type = c_common_type (type1, type2);
      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (op1) == EXCESS_PRECISION_ಅಭಿವ್ಯಕ್ತಿ)
	{
	  op1 = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (op1, 0);
	  type1 = ವೃಕ್ಷ_TYPE (op1);
	  gcc_assert (ವೃಕ್ಷ_ಸಂಕೇತ (type1) == code1);
	}
      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (op2) == EXCESS_PRECISION_ಅಭಿವ್ಯಕ್ತಿ)
	{
	  op2 = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (op2, 0);
	  type2 = ವೃಕ್ಷ_TYPE (op2);
	  gcc_assert (ವೃಕ್ಷ_ಸಂಕೇತ (type2) == code2);
	}
    }

  ಆದರೆ (warn_cxx_compat)
    {
      ವೃಕ್ಷ t1 = op1_original_type ? op1_original_type : ವೃಕ್ಷ_TYPE (orig_op1);
      ವೃಕ್ಷ t2 = op2_original_type ? op2_original_type : ವೃಕ್ಷ_TYPE (orig_op2);

      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (t1) == ENUMERAL_TYPE
	  && ವೃಕ್ಷ_ಸಂಕೇತ (t2) == ENUMERAL_TYPE
	  && TYPE_MAIN_VARIANT (t1) != TYPE_MAIN_VARIANT (t2))
	warning_at (colon_loc, OPT_Wc___compat,
		    "different enum types in conditional is "
		    "invalid in C++: %qT vs %qT", t1, t2);
    }

  ಆದರೆ (warn_zero_as_null_ಸೂಚಕ_constant
      && c_inhibit_evaluation_warnings == 0)
    {
      ಆದರೆ ((code1 == ಸೂಚಕ_TYPE || code1 == NULLPTR_TYPE)
	  && INTEGRAL_TYPE_P (type2) && null_ಸೂಚಕ_constant_p (orig_op2))
	warning_at (op2_loc, OPT_Wzero_as_null_ಸೂಚಕ_constant,
		    "zero as null pointer constant");

      ಆದರೆ ((code2 == ಸೂಚಕ_TYPE || code2 == NULLPTR_TYPE)
	  && INTEGRAL_TYPE_P (type1) && null_ಸೂಚಕ_constant_p (orig_op1))
	warning_at (op1_loc, OPT_Wzero_as_null_ಸೂಚಕ_constant,
		    "zero as null pointer constant");
    }

  /* Quickly detect the usual case where op1 and op2 have the same type
     after promotion.  */
  ಆದರೆ (TYPE_MAIN_VARIANT (type1) == TYPE_MAIN_VARIANT (type2))
    {
      ಆದರೆ (type1 == type2)
	ಫಲಿತಾಂಶ_type = type1;
      ಇಲ್ಲದಿದ್ದರೆ
	ಫಲಿತಾಂಶ_type = TYPE_MAIN_VARIANT (type1);
    }
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ ((code1 == INTEGER_TYPE || code1 == REAL_TYPE
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
      ಆದರೆ (flag_isoc11)
	{
	  ವೃಕ್ಷ eptype;
	  ಆದರೆ (ANY_INTEGRAL_TYPE_P (type1)
	      && (eptype = excess_precision_type (type2)) != NULL_ವೃಕ್ಷ)
	    {
	      eptype2 = eptype;
	      ಆದರೆ (!semantic_ಫಲಿತಾಂಶ_type)
		semantic_ಫಲಿತಾಂಶ_type = c_common_type (type1, type2);
	    }
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ANY_INTEGRAL_TYPE_P (type2)
		   && (eptype = excess_precision_type (type1)) != NULL_ವೃಕ್ಷ)
	    {
	      eptype1 = eptype;
	      ಆದರೆ (!semantic_ಫಲಿತಾಂಶ_type)
		semantic_ಫಲಿತಾಂಶ_type = c_common_type (type1, type2);
	    }
	}
      ಫಲಿತಾಂಶ_type = c_common_type (eptype1, eptype2);
      ಆದರೆ (ಫಲಿತಾಂಶ_type == error_mark_ಗಂಟು)
	ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
      do_warn_double_promotion (ಫಲಿತಾಂಶ_type, type1, type2,
				"implicit conversion from %qT to %qT to "
				"match other result of conditional",
				colon_loc);

      /* If -Wsign-compare, warn here if type1 and type2 have
	 different signedness.  We'll promote the signed to unsigned
	 and later code won't know it used to be different.
	 Do this check on the original types, so that explicit casts
	 will be considered, but default promotions won't.  */
      ಆದರೆ (c_inhibit_evaluation_warnings == 0)
	{
	  ಪೂರ್ಣಾಂಕ unsigned_op1 = TYPE_UNSIGNED (ವೃಕ್ಷ_TYPE (orig_op1));
	  ಪೂರ್ಣಾಂಕ unsigned_op2 = TYPE_UNSIGNED (ವೃಕ್ಷ_TYPE (orig_op2));

	  ಆದರೆ (unsigned_op1 ^ unsigned_op2)
	    {
	      /* Do not warn if the result type is signed, since the
		 signed type will only be chosen if it can represent
		 all the values of the unsigned type.  */
	      ಆದರೆ (!TYPE_UNSIGNED (ಫಲಿತಾಂಶ_type))
		/* OK */;
	      ಇಲ್ಲದಿದ್ದರೆ
		{
		  ತಾರ್ಕಿಕ op1_maybe_const = ನಿಜ;
		  ತಾರ್ಕಿಕ op2_maybe_const = ನಿಜ;

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

		  ಆದರೆ (warn_sign_compare)
		    {
		      ಆದರೆ ((unsigned_op2
			   && ವೃಕ್ಷ_ಅಭಿವ್ಯಕ್ತಿ_nonnegative_p (op1))
			  || (unsigned_op1
			      && ವೃಕ್ಷ_ಅಭಿವ್ಯಕ್ತಿ_nonnegative_p (op2)))
			/* OK */;
		      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (unsigned_op2)
			warning_at (op1_loc, OPT_Wsign_compare,
				    "operand of %<?:%> changes signedness from "
				    "%qT to %qT due to unsignedness of other "
				    "operand", ವೃಕ್ಷ_TYPE (orig_op1),
				    ವೃಕ್ಷ_TYPE (orig_op2));
		      ಇಲ್ಲದಿದ್ದರೆ
			warning_at (op2_loc, OPT_Wsign_compare,
				    "operand of %<?:%> changes signedness from "
				    "%qT to %qT due to unsignedness of other "
				    "operand", ವೃಕ್ಷ_TYPE (orig_op2),
				    ವೃಕ್ಷ_TYPE (orig_op1));
		    }
		  ಆದರೆ (!op1_maybe_const || ವೃಕ್ಷ_ಸಂಕೇತ (op1) != INTEGER_CST)
		    op1 = c_wrap_maybe_const (op1, !op1_maybe_const);
		  ಆದರೆ (!op2_maybe_const || ವೃಕ್ಷ_ಸಂಕೇತ (op2) != INTEGER_CST)
		    op2 = c_wrap_maybe_const (op2, !op2_maybe_const);
		}
	    }
	}
    }
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (code1 == VOID_TYPE || code2 == VOID_TYPE)
    {
      ಆದರೆ (code1 != VOID_TYPE || code2 != VOID_TYPE)
	pedwarn (colon_loc, OPT_Wpedantic,
		 "ISO C forbids conditional expr with only one void side");
      ಫಲಿತಾಂಶ_type = void_type_ಗಂಟು;
    }
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (code1 == ಸೂಚಕ_TYPE && code2 == ಸೂಚಕ_TYPE)
    {
      addr_space_t as1 = TYPE_ADDR_SPACE (ವೃಕ್ಷ_TYPE (type1));
      addr_space_t as2 = TYPE_ADDR_SPACE (ವೃಕ್ಷ_TYPE (type2));
      addr_space_t as_common;

      ಆದರೆ (comp_ಗುರಿ_types (colon_loc, type1, type2))
	{
	  ifexp = save_ಅಭಿವ್ಯಕ್ತಿ (ifexp);
	  ಫಲಿತಾಂಶ_type = common_ಸೂಚಕ_type (type1, type2, ifexp);
	}
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (null_ಸೂಚಕ_constant_p (orig_op1))
	ಫಲಿತಾಂಶ_type = type2;
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (null_ಸೂಚಕ_constant_p (orig_op2))
	ಫಲಿತಾಂಶ_type = type1;
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!addr_space_superset (as1, as2, &as_common))
	{
	  error_at (colon_loc, "pointers to disjoint address spaces "
		    "used in conditional expression");
	  ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
	}
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ ((VOID_TYPE_P (ವೃಕ್ಷ_TYPE (type1))
		&& !TYPE_ATOMIC (ವೃಕ್ಷ_TYPE (type1)))
	       || (VOID_TYPE_P (ವೃಕ್ಷ_TYPE (type2))
		   && !TYPE_ATOMIC (ವೃಕ್ಷ_TYPE (type2))))
	{
	  ವೃಕ್ಷ t1 = ವೃಕ್ಷ_TYPE (type1);
	  ವೃಕ್ಷ t2 = ವೃಕ್ಷ_TYPE (type2);
	  ಆದರೆ (!(VOID_TYPE_P (t1)
		&& !TYPE_ATOMIC (t1)))
	   {
	     /* roles are swapped */
	     t1 = t2;
	     t2 = ವೃಕ್ಷ_TYPE (type1);
	   }
	  ವೃಕ್ಷ t2_stripped = strip_array_types (t2);
	  ಆದರೆ ((ವೃಕ್ಷ_ಸಂಕೇತ (t2) == ARRAY_TYPE)
	      && (TYPE_QUALS (t2_stripped) & ~TYPE_QUALS (t1)))
	    {
	      ಆದರೆ (!flag_isoc23)
		warning_at (colon_loc, OPT_Wdiscarded_array_qualifiers,
			    "pointer to array loses qualifier "
			    "in conditional expression");
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (warn_c11_c23_compat > 0)
		warning_at (colon_loc, OPT_Wc11_c23_compat,
			    "pointer to array loses qualifier "
			    "in conditional expression in ISO C before C23");
	    }
	  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (t2) == FUNCTION_TYPE)
	    pedwarn (colon_loc, OPT_Wpedantic,
		     "ISO C forbids conditional expr between "
		     "%<void *%> and function pointer");
	  /* for array, use qualifiers of element type */
	  ಆದರೆ (flag_isoc23)
	    t2 = t2_stripped;
	  ಫಲಿತಾಂಶ_type = c_build_ಸೂಚಕ_type (qualify_type (t1, t2));
	}
      /* Objective-C pointer comparisons are a bit more lenient.  */
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (objc_have_common_type (type1, type2, -3, NULL_ವೃಕ್ಷ))
	ಫಲಿತಾಂಶ_type = objc_common_type (type1, type2);
      ಇಲ್ಲದಿದ್ದರೆ
	{
	  ಪೂರ್ಣಾಂಕ qual = ENCODE_QUAL_ADDR_SPACE (as_common);
	  ಎಣಿಕೆ diagnostics::ಬಗೆ ಬಗೆ = diagnostics::ಬಗೆ::permerror;
	  ಆದರೆ (!flag_isoc99)
	    /* This downgrade to a warning ensures that -std=gnu89
	       -pedantic-errors does not flag these mismatches between
	       builtins as errors (as diagnostics::kind::permerror would)
	       ISO C99 and later do not have implicit function declarations,
	       so the mismatch cannot occur naturally there.  */
	    ಬಗೆ = (bltin1 && bltin2
		    ? diagnostics::ಬಗೆ::warning
		    : diagnostics::ಬಗೆ::pedwarn);
	  ಆದರೆ (emit_diagnostic (ಬಗೆ, colon_loc, OPT_Wincompatible_ಸೂಚಕ_types,
			       "pointer type mismatch "
			       "in conditional expression"))
	    {
	      inform (op1_loc, "first expression has type %qT", type1);
	      inform (op2_loc, "second expression has type %qT", type2);
	    }
	  ಫಲಿತಾಂಶ_type = c_build_ಸೂಚಕ_type
			  (c_build_qualified_type (void_type_ಗಂಟು, qual));
	}
    }
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (code1 == ಸೂಚಕ_TYPE
	   && (code2 == INTEGER_TYPE || code2 == BITINT_TYPE))
    {
      ಆದರೆ (!null_ಸೂಚಕ_constant_p (orig_op2))
	permerror_opt (colon_loc, OPT_Wint_conversion,
		       "pointer/integer type mismatch "
		       "in conditional expression");
      ಇಲ್ಲದಿದ್ದರೆ
	{
	  op2 = null_ಸೂಚಕ_ಗಂಟು;
	}
      ಫಲಿತಾಂಶ_type = type1;
    }
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (code2 == ಸೂಚಕ_TYPE
	   && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
    {
      ಆದರೆ (!null_ಸೂಚಕ_constant_p (orig_op1))
	permerror_opt (colon_loc, OPT_Wint_conversion,
		       "pointer/integer type mismatch "
		       "in conditional expression");
      ಇಲ್ಲದಿದ್ದರೆ
	{
	  op1 = null_ಸೂಚಕ_ಗಂಟು;
	}
      ಫಲಿತಾಂಶ_type = type2;
    }
  /* 6.5.15: "if one is a null pointer constant (other than a pointer) or has
     type nullptr_t and the other is a pointer, the result type is the pointer
     type."  */
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (code1 == NULLPTR_TYPE && code2 == ಸೂಚಕ_TYPE)
    ಫಲಿತಾಂಶ_type = type2;
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (code1 == ಸೂಚಕ_TYPE && code2 == NULLPTR_TYPE)
    ಫಲಿತಾಂಶ_type = type1;
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ದಾಖಲೆ_OR_UNION_TYPE_P (type1) && ದಾಖಲೆ_OR_UNION_TYPE_P (type2)
	   && comptypes (TYPE_MAIN_VARIANT (type1),
			 TYPE_MAIN_VARIANT (type2)))
    ಫಲಿತಾಂಶ_type = ಸಂಯುಕ್ತ_type (TYPE_MAIN_VARIANT (type1),
				  TYPE_MAIN_VARIANT (type2));

  ಆದರೆ (!ಫಲಿತಾಂಶ_type)
    {
      ಆದರೆ (flag_cond_mismatch)
	ಫಲಿತಾಂಶ_type = void_type_ಗಂಟು;
      ಇಲ್ಲದಿದ್ದರೆ
	{
	  error_at (colon_loc, "type mismatch in conditional expression");
	  ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
	}
    }

  /* Merge const and volatile flags of the incoming types.  */
  ಫಲಿತಾಂಶ_type
    = build_type_variant (ಫಲಿತಾಂಶ_type,
			  TYPE_READONLY (type1) || TYPE_READONLY (type2),
			  TYPE_VOLATILE (type1) || TYPE_VOLATILE (type2));

  op1 = ep_convert_and_check (colon_loc, ಫಲಿತಾಂಶ_type, op1,
			      semantic_ಫಲಿತಾಂಶ_type);
  op2 = ep_convert_and_check (colon_loc, ಫಲಿತಾಂಶ_type, op2,
			      semantic_ಫಲಿತಾಂಶ_type);

  ಆದರೆ (ifexp_bcp && ifexp == truthvalue_true_ಗಂಟು)
    {
      op2_int_operands = ನಿಜ;
      op1 = c_fully_fold (op1, require_constant_ಮೌಲ್ಯ, ಖಾಲಿ);
    }
  ಆದರೆ (ifexp_bcp && ifexp == truthvalue_false_ಗಂಟು)
    {
      op1_int_operands = ನಿಜ;
      op2 = c_fully_fold (op2, require_constant_ಮೌಲ್ಯ, ಖಾಲಿ);
    }
  int_const = int_operands = (ifexp_int_operands
			      && op1_int_operands
			      && op2_int_operands);
  ಆದರೆ (int_operands)
    {
      int_const = ((ifexp == truthvalue_true_ಗಂಟು
		    && ವೃಕ್ಷ_ಸಂಕೇತ (orig_op1) == INTEGER_CST
		    && !ವೃಕ್ಷ_ಅತಿಪ್ರವಾಹ (orig_op1))
		   || (ifexp == truthvalue_false_ಗಂಟು
		       && ವೃಕ್ಷ_ಸಂಕೇತ (orig_op2) == INTEGER_CST
		       && !ವೃಕ್ಷ_ಅತಿಪ್ರವಾಹ (orig_op2)));
    }

  /* Need to convert condition operand into a vector mask.  */
  ಆದರೆ (ಸದಿಶ_TYPE_P (ವೃಕ್ಷ_TYPE (ifexp)))
    {
      ವೃಕ್ಷ vectype = ವೃಕ್ಷ_TYPE (ifexp);
      ವೃಕ್ಷ elem_type = ವೃಕ್ಷ_TYPE (vectype);
      ವೃಕ್ಷ zero = build_int_cst (elem_type, 0);
      ವೃಕ್ಷ zero_vec = build_ಸದಿಶ_from_val (vectype, zero);
      ವೃಕ್ಷ cmp_type = truth_type_for (vectype);
      ifexp = build2 (NE_ಅಭಿವ್ಯಕ್ತಿ, cmp_type, ifexp, zero_vec);
    }

  ಆದರೆ (int_const || (ifexp_bcp && ವೃಕ್ಷ_ಸಂಕೇತ (ifexp) == INTEGER_CST))
    ret = fold_build3_loc (colon_loc, COND_ಅಭಿವ್ಯಕ್ತಿ, ಫಲಿತಾಂಶ_type, ifexp, op1, op2);
  ಇಲ್ಲದಿದ್ದರೆ
    {
      ಆದರೆ (int_operands)
	{
	  /* Use c_fully_fold here, since C_MAYBE_CONST_EXPR might be
	     nested inside of the expression.  */
	  op1 = c_fully_fold (op1, ಸುಳ್ಳು, ಖಾಲಿ);
	  op2 = c_fully_fold (op2, ಸುಳ್ಳು, ಖಾಲಿ);
	}
      ret = build3 (COND_ಅಭಿವ್ಯಕ್ತಿ, ಫಲಿತಾಂಶ_type, ifexp, op1, op2);
      ಆದರೆ (int_operands)
	ret = note_integer_operands (ret);
    }
  ಆದರೆ (semantic_ಫಲಿತಾಂಶ_type)
    ret = build1 (EXCESS_PRECISION_ಅಭಿವ್ಯಕ್ತಿ, semantic_ಫಲಿತಾಂಶ_type, ret);

  protected_ಗಣ_ಅಭಿವ್ಯಕ್ತಿ_location (ret, colon_loc);

  /* If the OP1 and OP2 are the same and don't have side-effects,
     warn here, because the COND_EXPR will be turned into OP1.  */
  ಆದರೆ (warn_duplicated_branches
      && ವೃಕ್ಷ_ಸಂಕೇತ (ret) == COND_ಅಭಿವ್ಯಕ್ತಿ
      && (op1 == op2 || ಕಾರ್ಯಾಂಶ_equal_p (op1, op2, OEP_ವಿಳಾಸ_ದ_SAME_ಕ್ಷೇತ್ರ)))
    warning_at (ಅಭಿವ್ಯಕ್ತಿ_LOCATION (ret), OPT_Wduplicated_branches,
		"this condition has identical branches");

  ಹಿಂತಿರುಗಿ ret;
}

/* EXPR is an expression, location LOC, whose result is discarded.
   Warn if it is a call to a nodiscard function (or a COMPOUND_EXPR
   whose right-hand operand is such a call, possibly recursively).  */

ಸ್ಥಿರ ಶೂನ್ಯ
maybe_warn_nodiscard (location_t loc, ವೃಕ್ಷ ಅಭಿವ್ಯಕ್ತಿ)
{
  ಆದರೆ (VOID_TYPE_P (ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ)))
    ಹಿಂತಿರುಗಿ;
  ಆಗ (ವೃಕ್ಷ_ಸಂಕೇತ (ಅಭಿವ್ಯಕ್ತಿ) == COMPOUND_ಅಭಿವ್ಯಕ್ತಿ)
    {
      ಅಭಿವ್ಯಕ್ತಿ = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (ಅಭಿವ್ಯಕ್ತಿ, 1);
      ಆದರೆ (ಅಭಿವ್ಯಕ್ತಿ_HAS_LOCATION (ಅಭಿವ್ಯಕ್ತಿ))
	loc = ಅಭಿವ್ಯಕ್ತಿ_LOCATION (ಅಭಿವ್ಯಕ್ತಿ);
    }
  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ಅಭಿವ್ಯಕ್ತಿ) != CALL_ಅಭಿವ್ಯಕ್ತಿ)
    ಹಿಂತಿರುಗಿ;
  ವೃಕ್ಷ fn = CALL_ಅಭಿವ್ಯಕ್ತಿ_FN (ಅಭಿವ್ಯಕ್ತಿ);
  ಆದರೆ (!fn)
    ಹಿಂತಿರುಗಿ;
  ವೃಕ್ಷ attr;
  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (fn) == ADDR_ಅಭಿವ್ಯಕ್ತಿ
      && ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (fn, 0)) == FUNCTION_DECL
      && (attr = lookup_attribute ("nodiscard",
				   DECL_ಗುಣಲಕ್ಷಣಗಳು (ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (fn, 0)))))
    {
      fn = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (fn, 0);
      ವೃಕ್ಷ ವಾದಗಳು = ವೃಕ್ಷ_ಮೌಲ್ಯ (attr);
      ಆದರೆ (ವಾದಗಳು)
	ವಾದಗಳು = ವೃಕ್ಷ_ಮೌಲ್ಯ (ವಾದಗಳು);
      auto_diagnostic_ಗುಂಪು d;
      auto_urlify_ಗುಣಲಕ್ಷಣಗಳು sentinel;
      ಪೂರ್ಣಾಂಕ warned;
      ಆದರೆ (ವಾದಗಳು)
	warned = warning_at (loc, OPT_Wunused_ಫಲಿತಾಂಶ,
			     "ignoring return value of %qD, declared with "
			     "attribute %<nodiscard%>: %E", fn, ವಾದಗಳು);
      ಇಲ್ಲದಿದ್ದರೆ
	warned = warning_at (loc, OPT_Wunused_ಫಲಿತಾಂಶ,
			     "ignoring return value of %qD, declared with "
			     "attribute %<nodiscard%>", fn);
      ಆದರೆ (warned)
	inform (DECL_ಮೂಲ_LOCATION (fn), "declared here");
    }
  ಇಲ್ಲದಿದ್ದರೆ
    {
      ವೃಕ್ಷ rettype = ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_TYPE (fn)));
      attr = lookup_attribute ("nodiscard", TYPE_ಗುಣಲಕ್ಷಣಗಳು (rettype));
      ಆದರೆ (!attr)
	ಹಿಂತಿರುಗಿ;
      ವೃಕ್ಷ ವಾದಗಳು = ವೃಕ್ಷ_ಮೌಲ್ಯ (attr);
      ಆದರೆ (ವಾದಗಳು)
	ವಾದಗಳು = ವೃಕ್ಷ_ಮೌಲ್ಯ (ವಾದಗಳು);
      auto_diagnostic_ಗುಂಪು d;
      auto_urlify_ಗುಣಲಕ್ಷಣಗಳು sentinel;
      ಪೂರ್ಣಾಂಕ warned;
      ಆದರೆ (ವಾದಗಳು)
	warned = warning_at (loc, OPT_Wunused_ಫಲಿತಾಂಶ,
			     "ignoring return value of type %qT, declared "
			     "with attribute %<nodiscard%>: %E",
			     rettype, ವಾದಗಳು);
      ಇಲ್ಲದಿದ್ದರೆ
	warned = warning_at (loc, OPT_Wunused_ಫಲಿತಾಂಶ,
			     "ignoring return value of type %qT, declared "
			     "with attribute %<nodiscard%>", rettype);
      ಆದರೆ (warned)
	{
	  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (fn) == ADDR_ಅಭಿವ್ಯಕ್ತಿ)
	    {
	      fn = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (fn, 0);
	      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (fn) == FUNCTION_DECL)
		inform (DECL_ಮೂಲ_LOCATION (fn),
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
  ಆದರೆ (expr1_int_operands)
    expr1 = remove_c_maybe_const_ಅಭಿವ್ಯಕ್ತಿ (expr1);
  expr2_int_operands = ಅಭಿವ್ಯಕ್ತಿ_INT_CONST_OPERANDS (expr2);
  ಆದರೆ (expr2_int_operands)
    expr2 = remove_c_maybe_const_ಅಭಿವ್ಯಕ್ತಿ (expr2);

  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (expr1) == EXCESS_PRECISION_ಅಭಿವ್ಯಕ್ತಿ)
    expr1 = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (expr1, 0);
  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (expr2) == EXCESS_PRECISION_ಅಭಿವ್ಯಕ್ತಿ)
    {
      eptype = ವೃಕ್ಷ_TYPE (expr2);
      expr2 = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (expr2, 0);
    }

  ಆದರೆ (!ವೃಕ್ಷ_SIDE_EFFECTS (expr1))
    {
      /* The left-hand operand of a comma expression is like an expression
	 statement: with -Wunused, we should warn if it doesn't have
	 any side-effects, unless it was explicitly cast to (void).  */
      ಆದರೆ (warn_ಬಳಸದ_ಮೌಲ್ಯ)
	{
	  ಆದರೆ (VOID_TYPE_P (ವೃಕ್ಷ_TYPE (expr1))
	      && CONVERT_ಅಭಿವ್ಯಕ್ತಿ_P (expr1))
	    ; /* (void) a, b */
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (VOID_TYPE_P (ವೃಕ್ಷ_TYPE (expr1))
		   && ವೃಕ್ಷ_ಸಂಕೇತ (expr1) == COMPOUND_ಅಭಿವ್ಯಕ್ತಿ
		   && CONVERT_ಅಭಿವ್ಯಕ್ತಿ_P (ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (expr1, 1)))
	    ; /* (void) a, (void) b, c */
	  ಇಲ್ಲದಿದ್ದರೆ
	    warning_at (loc, OPT_Wunused_ಮೌಲ್ಯ,
			"left-hand operand of comma expression has no effect");
	}
    }
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (expr1) == COMPOUND_ಅಭಿವ್ಯಕ್ತಿ
	   && warn_ಬಳಸದ_ಮೌಲ್ಯ)
    {
      ವೃಕ್ಷ r = expr1;
      location_t cloc = loc;
      ಆಗ (ವೃಕ್ಷ_ಸಂಕೇತ (r) == COMPOUND_ಅಭಿವ್ಯಕ್ತಿ)
        {
	  ಆದರೆ (ಅಭಿವ್ಯಕ್ತಿ_HAS_LOCATION (r))
	    cloc = ಅಭಿವ್ಯಕ್ತಿ_LOCATION (r);
	  r = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (r, 1);
	}
      ಆದರೆ (!ವೃಕ್ಷ_SIDE_EFFECTS (r)
	  && !VOID_TYPE_P (ವೃಕ್ಷ_TYPE (r))
	  && !CONVERT_ಅಭಿವ್ಯಕ್ತಿ_P (r))
	warning_at (cloc, OPT_Wunused_ಮೌಲ್ಯ,
	            "right-hand operand of comma expression has no effect");
    }

  /* With -Wunused, we should also warn if the left-hand operand does have
     side-effects, but computes a value which is not used.  For example, in
     `foo() + bar(), baz()' the result of the `+' operator is not used,
     so we should issue a warning.  */
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (warn_ಬಳಸದ_ಮೌಲ್ಯ)
    warn_if_ಬಳಸದ_ಮೌಲ್ಯ (expr1, loc);

  maybe_warn_nodiscard (loc, expr1);

  ಆದರೆ (expr2 == error_mark_ಗಂಟು)
    ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;

  ret = build2 (COMPOUND_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (expr2), expr1, expr2);

  ಆದರೆ (flag_isoc99
      && expr1_int_operands
      && expr2_int_operands)
    ret = note_integer_operands (ret);

  ಆದರೆ (eptype)
    ret = build1 (EXCESS_PRECISION_ಅಭಿವ್ಯಕ್ತಿ, eptype, ret);

  protected_ಗಣ_ಅಭಿವ್ಯಕ್ತಿ_location (ret, loc);
  ಹಿಂತಿರುಗಿ ret;
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
  ವೃಕ್ಷ ಒಳ_type = type;
  ವೃಕ್ಷ ಒಳ_otype = otype;
  ಪೂರ್ಣಾಂಕ added = 0;
  ಪೂರ್ಣಾಂಕ discarded = 0;
  ತಾರ್ಕಿಕ is_const;

  /* Check that the qualifiers on IN_TYPE are a superset of the
     qualifiers of IN_OTYPE.  The outermost level of POINTER_TYPE
     nodes is uninteresting and we stop as soon as we hit a
     non-POINTER_TYPE node on either type.  */
  ಮಾಡು
    {
      ಒಳ_otype = ವೃಕ್ಷ_TYPE (ಒಳ_otype);
      ಒಳ_type = ವೃಕ್ಷ_TYPE (ಒಳ_type);

      /* GNU C allows cv-qualified function types.  'const' means the
	 function is very pure, 'volatile' means it can't return.  We
	 need to warn when such qualifiers are added, not when they're
	 taken away.  */
      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ಒಳ_otype) == FUNCTION_TYPE
	  && ವೃಕ್ಷ_ಸಂಕೇತ (ಒಳ_type) == FUNCTION_TYPE)
	added |= (TYPE_QUALS_NO_ADDR_SPACE (ಒಳ_type)
		  & ~TYPE_QUALS_NO_ADDR_SPACE (ಒಳ_otype));
      ಇಲ್ಲದಿದ್ದರೆ
	discarded |= (TYPE_QUALS_NO_ADDR_SPACE (ಒಳ_otype)
		      & ~TYPE_QUALS_NO_ADDR_SPACE (ಒಳ_type));
    }
  ಆಗ (ವೃಕ್ಷ_ಸಂಕೇತ (ಒಳ_type) == ಸೂಚಕ_TYPE
	 && ವೃಕ್ಷ_ಸಂಕೇತ (ಒಳ_otype) == ಸೂಚಕ_TYPE);

  ಆದರೆ (added)
    warning_at (loc, OPT_Wcast_qual,
		"cast adds %q#v qualifier to function type", added);

  ಆದರೆ (discarded)
    /* There are qualifiers present in IN_OTYPE that are not present
       in IN_TYPE.  */
    warning_at (loc, OPT_Wcast_qual,
		"cast discards %qv qualifier from pointer target type",
		discarded);

  ಆದರೆ (added || discarded)
    ಹಿಂತಿರುಗಿ;

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

  ಆದರೆ (TYPE_MAIN_VARIANT (ಒಳ_type) != TYPE_MAIN_VARIANT (ಒಳ_otype))
    ಹಿಂತಿರುಗಿ;
  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (type)) != ಸೂಚಕ_TYPE)
    ಹಿಂತಿರುಗಿ;

  ಒಳ_type = type;
  ಒಳ_otype = otype;
  is_const = TYPE_READONLY (ವೃಕ್ಷ_TYPE (ಒಳ_type));
  ಮಾಡು
    {
      ಒಳ_type = ವೃಕ್ಷ_TYPE (ಒಳ_type);
      ಒಳ_otype = ವೃಕ್ಷ_TYPE (ಒಳ_otype);
      ಆದರೆ ((TYPE_QUALS (ಒಳ_type) &~ TYPE_QUALS (ಒಳ_otype)) != 0
	  && !is_const)
	{
	  warning_at (loc, OPT_Wcast_qual,
		      "to be safe all intermediate pointers in cast from "
                      "%qT to %qT must be %<const%> qualified",
		      otype, type);
	  ನಿಲ್ಲಿಸು;
	}
      ಆದರೆ (is_const)
	is_const = TYPE_READONLY (ಒಳ_type);
    }
  ಆಗ (ವೃಕ್ಷ_ಸಂಕೇತ (ಒಳ_type) == ಸೂಚಕ_TYPE);
}

/* Heuristic check if two parameter types can be considered ABI-equivalent.  */

ಸ್ಥಿರ ತಾರ್ಕಿಕ
c_ಸುರಕ್ಷಿತ_arg_type_equiv_p (ವೃಕ್ಷ t1, ವೃಕ್ಷ t2)
{
  ಆದರೆ (error_ಕಾರ್ಯಾಂಶ_p (t1) || error_ಕಾರ್ಯಾಂಶ_p (t2))
    ಹಿಂತಿರುಗಿ ನಿಜ;

  t1 = TYPE_MAIN_VARIANT (t1);
  t2 = TYPE_MAIN_VARIANT (t2);

  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (t1) == ಸೂಚಕ_TYPE
      && ವೃಕ್ಷ_ಸಂಕೇತ (t2) == ಸೂಚಕ_TYPE)
    ಹಿಂತಿರುಗಿ ನಿಜ;

  /* Only the precision of the parameter matters.  This check should
     make sure that the callee does not see undefined values in argument
     registers.  */
  ಆದರೆ (INTEGRAL_TYPE_P (t1)
      && INTEGRAL_TYPE_P (t2)
      && TYPE_PRECISION (t1) == TYPE_PRECISION (t2))
    ಹಿಂತಿರುಗಿ ನಿಜ;

  ಹಿಂತಿರುಗಿ comptypes (t1, t2);
}

/* Check if a type cast between two function types can be considered safe.  */

ಸ್ಥಿರ ತಾರ್ಕಿಕ
c_ಸುರಕ್ಷಿತ_function_type_cast_p (ವೃಕ್ಷ t1, ವೃಕ್ಷ t2)
{
  ಆದರೆ (ವೃಕ್ಷ_TYPE (t1) == void_type_ಗಂಟು &&
      TYPE_ARG_TYPES (t1) == void_list_ಗಂಟು)
    ಹಿಂತಿರುಗಿ ನಿಜ;

  ಆದರೆ (ವೃಕ್ಷ_TYPE (t2) == void_type_ಗಂಟು &&
      TYPE_ARG_TYPES (t2) == void_list_ಗಂಟು)
    ಹಿಂತಿರುಗಿ ನಿಜ;

  ಆದರೆ (!c_ಸುರಕ್ಷಿತ_arg_type_equiv_p (ವೃಕ್ಷ_TYPE (t1), ವೃಕ್ಷ_TYPE (t2)))
    ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;

  ಗಾಗಿ (t1 = TYPE_ARG_TYPES (t1), t2 = TYPE_ARG_TYPES (t2);
       t1 && t2;
       t1 = ವೃಕ್ಷ_CHAIN (t1), t2 = ವೃಕ್ಷ_CHAIN (t2))
    ಆದರೆ (!c_ಸುರಕ್ಷಿತ_arg_type_equiv_p (ವೃಕ್ಷ_ಮೌಲ್ಯ (t1), ವೃಕ್ಷ_ಮೌಲ್ಯ (t2)))
      ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;

  ಹಿಂತಿರುಗಿ ನಿಜ;
}

/* Build an expression representing a cast to type TYPE of expression EXPR.
   LOC is the location of the cast-- typically the open paren of the cast.  */

ವೃಕ್ಷ
build_c_cast (location_t loc, ವೃಕ್ಷ type, ವೃಕ್ಷ ಅಭಿವ್ಯಕ್ತಿ)
{
  ವೃಕ್ಷ ಮೌಲ್ಯ;

  ತಾರ್ಕಿಕ int_operands = ಅಭಿವ್ಯಕ್ತಿ_INT_CONST_OPERANDS (ಅಭಿವ್ಯಕ್ತಿ);

  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ಅಭಿವ್ಯಕ್ತಿ) == EXCESS_PRECISION_ಅಭಿವ್ಯಕ್ತಿ)
    ಅಭಿವ್ಯಕ್ತಿ = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (ಅಭಿವ್ಯಕ್ತಿ, 0);

  ಮೌಲ್ಯ = ಅಭಿವ್ಯಕ್ತಿ;
  ಆದರೆ (int_operands)
    ಮೌಲ್ಯ = remove_c_maybe_const_ಅಭಿವ್ಯಕ್ತಿ (ಮೌಲ್ಯ);

  ಆದರೆ (type == error_mark_ಗಂಟು || ಅಭಿವ್ಯಕ್ತಿ == error_mark_ಗಂಟು)
    ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;

  /* The ObjC front-end uses TYPE_MAIN_VARIANT to tie together types differing
     only in <protocol> qualifications.  But when constructing cast expressions,
     the protocols do matter and must be kept around.  */
  ಆದರೆ (objc_is_object_ptr (type) && objc_is_object_ptr (ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ)))
    ಹಿಂತಿರುಗಿ build1 (NOP_ಅಭಿವ್ಯಕ್ತಿ, type, ಅಭಿವ್ಯಕ್ತಿ);

  type = TYPE_MAIN_VARIANT (type);

  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (type) == ARRAY_TYPE)
    {
      error_at (loc, "cast specifies array type");
      ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
    }

  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (type) == FUNCTION_TYPE)
    {
      error_at (loc, "cast specifies function type");
      ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
    }

  ಆದರೆ (!VOID_TYPE_P (type))
    {
      ಮೌಲ್ಯ = require_complete_type (loc, ಮೌಲ್ಯ);
      ಆದರೆ (ಮೌಲ್ಯ == error_mark_ಗಂಟು)
	ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
    }

  ಆದರೆ (type == TYPE_MAIN_VARIANT (ವೃಕ್ಷ_TYPE (ಮೌಲ್ಯ)))
    {
      ಆದರೆ (ದಾಖಲೆ_OR_UNION_TYPE_P (type)
	  && pedwarn (loc, OPT_Wpedantic,
		      "ISO C forbids casting nonscalar to the same type"))
	      ;
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (warn_useless_cast && c_inhibit_evaluation_warnings == 0)
	warning_at (loc, OPT_Wuseless_cast,
		    "useless cast to type %qT", type);

      /* Convert to remove any qualifiers from VALUE's type.  */
      ಮೌಲ್ಯ = convert (type, ಮೌಲ್ಯ);
    }
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (type) == UNION_TYPE)
    {
      ವೃಕ್ಷ ಕ್ಷೇತ್ರ_2;

      ಗಾಗಿ (ಕ್ಷೇತ್ರ_2 = TYPE_FIELDS (type); ಕ್ಷೇತ್ರ_2; ಕ್ಷೇತ್ರ_2 = DECL_CHAIN (ಕ್ಷೇತ್ರ_2))
	ಆದರೆ (ವೃಕ್ಷ_TYPE (ಕ್ಷೇತ್ರ_2) != error_mark_ಗಂಟು
	    && comptypes (TYPE_MAIN_VARIANT (ವೃಕ್ಷ_TYPE (ಕ್ಷೇತ್ರ_2)),
			  TYPE_MAIN_VARIANT (ವೃಕ್ಷ_TYPE (ಮೌಲ್ಯ))))
	  ನಿಲ್ಲಿಸು;

      ಆದರೆ (ಕ್ಷೇತ್ರ_2)
	{
	  ವೃಕ್ಷ t;
	  ತಾರ್ಕಿಕ maybe_const = ನಿಜ;

	  pedwarn (loc, OPT_Wpedantic, "ISO C forbids casts to union type");
	  t = c_fully_fold (ಮೌಲ್ಯ, ಸುಳ್ಳು, &maybe_const);
	  t = build_constructor_single (type, ಕ್ಷೇತ್ರ_2, t);
	  ಆದರೆ (!maybe_const)
	    t = c_wrap_maybe_const (t, ನಿಜ);
	  t = digest_init (loc, ಕ್ಷೇತ್ರ_2, type, t,
			   NULL_ವೃಕ್ಷ, ಸುಳ್ಳು, ಸುಳ್ಳು, ಸುಳ್ಳು, ನಿಜ, ಸುಳ್ಳು, ಸುಳ್ಳು);
	  ವೃಕ್ಷ_CONSTANT (t) = ವೃಕ್ಷ_CONSTANT (ಮೌಲ್ಯ);
	  ಹಿಂತಿರುಗಿ t;
	}
      error_at (loc, "cast to union type from type not present in union");
      ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
    }
  ಇಲ್ಲದಿದ್ದರೆ
    {
      ವೃಕ್ಷ otype, ovalue;

      ಆದರೆ (type == void_type_ಗಂಟು)
	{
	  ವೃಕ್ಷ t = build1 (CONVERT_ಅಭಿವ್ಯಕ್ತಿ, type, ಮೌಲ್ಯ);
	  ಗಣ_ಅಭಿವ್ಯಕ್ತಿ_LOCATION (t, loc);
	  ಹಿಂತಿರುಗಿ t;
	}

      otype = ವೃಕ್ಷ_TYPE (ಮೌಲ್ಯ);

      /* Optionally warn about potentially worrisome casts.  */
      ಆದರೆ (warn_cast_qual
	  && ವೃಕ್ಷ_ಸಂಕೇತ (type) == ಸೂಚಕ_TYPE
	  && ವೃಕ್ಷ_ಸಂಕೇತ (otype) == ಸೂಚಕ_TYPE)
	handle_warn_cast_qual (loc, type, otype);

      /* Warn about conversions between pointers to disjoint
	 address spaces.  */
      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (type) == ಸೂಚಕ_TYPE
	  && ವೃಕ್ಷ_ಸಂಕೇತ (otype) == ಸೂಚಕ_TYPE
	  && !null_ಸೂಚಕ_constant_p (ಮೌಲ್ಯ))
	{
	  addr_space_t as_ಗಮ್ಯ = TYPE_ADDR_SPACE (ವೃಕ್ಷ_TYPE (type));
	  addr_space_t as_from = TYPE_ADDR_SPACE (ವೃಕ್ಷ_TYPE (otype));
	  addr_space_t as_common;

	  ಆದರೆ (!addr_space_superset (as_ಗಮ್ಯ, as_from, &as_common))
	    {
	      ಆದರೆ (ADDR_SPACE_GENERIC_P (as_from))
		warning_at (loc, 0, "cast to %qs address space pointer "
			    "from disjoint generic address space pointer",
			    c_addr_space_name (as_ಗಮ್ಯ));

	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ADDR_SPACE_GENERIC_P (as_ಗಮ್ಯ))
		warning_at (loc, 0, "cast to generic address space pointer "
			    "from disjoint %qs address space pointer",
			    c_addr_space_name (as_from));

	      ಇಲ್ಲದಿದ್ದರೆ
		warning_at (loc, 0, "cast to %qs address space pointer "
			    "from disjoint %qs address space pointer",
			    c_addr_space_name (as_ಗಮ್ಯ),
			    c_addr_space_name (as_from));
	    }

	  /* Warn of new allocations that are not big enough for the target
	     type.  */
	  ಆದರೆ (warn_alloc_ಗಾತ್ರ && ವೃಕ್ಷ_ಸಂಕೇತ (ಮೌಲ್ಯ) == CALL_ಅಭಿವ್ಯಕ್ತಿ)
	    ಆದರೆ (ವೃಕ್ಷ fndecl = get_callee_fndecl (ಮೌಲ್ಯ))
	      ಆದರೆ (DECL_IS_MALLOC (fndecl))
		{
		  ವೃಕ್ಷ attrs = TYPE_ಗುಣಲಕ್ಷಣಗಳು (ವೃಕ್ಷ_TYPE (fndecl));
		  ವೃಕ್ಷ alloc_ಗಾತ್ರ = lookup_attribute ("alloc_size", attrs);
		  ಆದರೆ (alloc_ಗಾತ್ರ)
		    warn_for_alloc_ಗಾತ್ರ (loc, ವೃಕ್ಷ_TYPE (type), ಮೌಲ್ಯ,
					 alloc_ಗಾತ್ರ);
		}
	}

      /* Warn about possible alignment problems.  */
      ಆದರೆ ((STRICT_ALIGNMENT || warn_cast_align == 2)
	  && ವೃಕ್ಷ_ಸಂಕೇತ (type) == ಸೂಚಕ_TYPE
	  && ವೃಕ್ಷ_ಸಂಕೇತ (otype) == ಸೂಚಕ_TYPE
	  && ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (otype)) != VOID_TYPE
	  && ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (otype)) != FUNCTION_TYPE
	  /* Don't warn about opaque types, where the actual alignment
	     restriction is unknown.  */
	  && !(ದಾಖಲೆ_OR_UNION_TYPE_P (ವೃಕ್ಷ_TYPE (otype))
	       && TYPE_ಬಹುಲಕ (ವೃಕ್ಷ_TYPE (otype)) == VOIDmode)
	  && min_align_ದ_type (ವೃಕ್ಷ_TYPE (type))
	     > min_align_ದ_type (ವೃಕ್ಷ_TYPE (otype)))
	warning_at (loc, OPT_Wcast_align,
		    "cast increases required alignment of target type");

      ಆದರೆ ((ವೃಕ್ಷ_ಸಂಕೇತ (type) == INTEGER_TYPE
	   || ವೃಕ್ಷ_ಸಂಕೇತ (type) == BITINT_TYPE)
	  && ವೃಕ್ಷ_ಸಂಕೇತ (otype) == ಸೂಚಕ_TYPE
	  && TYPE_PRECISION (type) != TYPE_PRECISION (otype))
      /* Unlike conversion of integers to pointers, where the
         warning is disabled for converting constants because
         of cases such as SIG_*, warn about converting constant
         pointers to integers. In some cases it may cause unwanted
         sign extension, and a warning is appropriate.  */
	warning_at (loc, OPT_Wpointer_ಗಮ್ಯ_int_cast,
		    "cast from pointer to integer of different size");

      ಆದರೆ ((ವೃಕ್ಷ_ಸಂಕೇತ (ಮೌಲ್ಯ) == CALL_ಅಭಿವ್ಯಕ್ತಿ
	   && !is_access_with_ಗಾತ್ರ_p (ಮೌಲ್ಯ))
	  && ವೃಕ್ಷ_ಸಂಕೇತ (type) != ವೃಕ್ಷ_ಸಂಕೇತ (otype))
	warning_at (loc, OPT_Wbad_function_cast,
		    "cast from function call of type %qT "
		    "to non-matching type %qT", otype, type);

      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (type) == ಸೂಚಕ_TYPE
	  && (ವೃಕ್ಷ_ಸಂಕೇತ (otype) == INTEGER_TYPE
	      || ವೃಕ್ಷ_ಸಂಕೇತ (otype) == BITINT_TYPE)
	  && TYPE_PRECISION (type) != TYPE_PRECISION (otype)
	  /* Don't warn about converting any constant.  */
	  && !ವೃಕ್ಷ_CONSTANT (ಮೌಲ್ಯ))
	warning_at (loc,
		    OPT_Wint_ಗಮ್ಯ_ಸೂಚಕ_cast, "cast to pointer from integer "
		    "of different size");

      ಆದರೆ (warn_strict_aliasing <= 2)
        strict_aliasing_warning (ಅಭಿವ್ಯಕ್ತಿ_LOCATION (ಮೌಲ್ಯ), type, ಅಭಿವ್ಯಕ್ತಿ);

      /* If pedantic, warn for conversions between function and object
	 pointer types, except for converting a null pointer constant
	 to function pointer type.  */
      ಆದರೆ (pedantic
	  && ವೃಕ್ಷ_ಸಂಕೇತ (type) == ಸೂಚಕ_TYPE
	  && ವೃಕ್ಷ_ಸಂಕೇತ (otype) == ಸೂಚಕ_TYPE
	  && ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (otype)) == FUNCTION_TYPE
	  && ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (type)) != FUNCTION_TYPE)
	pedwarn (loc, OPT_Wpedantic, "ISO C forbids "
		 "conversion of function pointer to object pointer type");

      ಆದರೆ (pedantic
	  && ವೃಕ್ಷ_ಸಂಕೇತ (type) == ಸೂಚಕ_TYPE
	  && ವೃಕ್ಷ_ಸಂಕೇತ (otype) == ಸೂಚಕ_TYPE
	  && ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (type)) == FUNCTION_TYPE
	  && ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (otype)) != FUNCTION_TYPE
	  && !null_ಸೂಚಕ_constant_p (ಮೌಲ್ಯ))
	pedwarn (loc, OPT_Wpedantic, "ISO C forbids "
		 "conversion of object pointer to function pointer type");

      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (type) == ಸೂಚಕ_TYPE
	  && ವೃಕ್ಷ_ಸಂಕೇತ (otype) == ಸೂಚಕ_TYPE
	  && ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (type)) == FUNCTION_TYPE
	  && ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (otype)) == FUNCTION_TYPE
	  && !c_ಸುರಕ್ಷಿತ_function_type_cast_p (ವೃಕ್ಷ_TYPE (type),
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
      ಆದರೆ (int_operands
	  && ವೃಕ್ಷ_ಸಂಕೇತ (ಮೌಲ್ಯ) != INTEGER_CST
	  && (ವೃಕ್ಷ_ಸಂಕೇತ (type) == BOOLEAN_TYPE
	      || (ವೃಕ್ಷ_ಸಂಕೇತ (type) == ENUMERAL_TYPE
		  && ENUM_UNDERLYING_TYPE (type) != NULL_ವೃಕ್ಷ
		  && ವೃಕ್ಷ_ಸಂಕೇತ (ENUM_UNDERLYING_TYPE (type)) == BOOLEAN_TYPE)))
	ಮೌಲ್ಯ = note_integer_operands (ಮೌಲ್ಯ);
      ಮೌಲ್ಯ = convert (type, ಮೌಲ್ಯ);

      /* Ignore any integer overflow caused by the cast.  */
      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ಮೌಲ್ಯ) == INTEGER_CST && !FLOAT_TYPE_P (otype))
	{
	  ಆದರೆ (ವೃಕ್ಷ_ಅತಿಪ್ರವಾಹ_P (ovalue))
	    {
	      ಆದರೆ (!ವೃಕ್ಷ_ಅತಿಪ್ರವಾಹ (ಮೌಲ್ಯ))
		{
		  /* Avoid clobbering a shared constant.  */
		  ಮೌಲ್ಯ = copy_ಗಂಟು (ಮೌಲ್ಯ);
		  ವೃಕ್ಷ_ಅತಿಪ್ರವಾಹ (ಮೌಲ್ಯ) = ವೃಕ್ಷ_ಅತಿಪ್ರವಾಹ (ovalue);
		}
	    }
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ವೃಕ್ಷ_ಅತಿಪ್ರವಾಹ (ಮೌಲ್ಯ))
	    /* Reset VALUE's overflow flags, ensuring constant sharing.  */
	    ಮೌಲ್ಯ = wide_int_ಗಮ್ಯ_ವೃಕ್ಷ (ವೃಕ್ಷ_TYPE (ಮೌಲ್ಯ), wi::ಗಮ್ಯ_wide (ಮೌಲ್ಯ));
	}
    }

  /* Don't let a cast be an lvalue.  */
  ಆದರೆ (lvalue_p (ಮೌಲ್ಯ)
      /* Also, don't let a cast be a bit-field of a bit-precise integer type,
	 otherwise it could be incorrectly subject of integer promotions.  */
      || (ವೃಕ್ಷ_ಸಂಕೇತ (ಮೌಲ್ಯ) == COMPONENT_REF
	  && DECL_C_ಬಿಟ್_ಕ್ಷೇತ್ರ (ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (ಮೌಲ್ಯ, 1))
	  && BITINT_TYPE_P (DECL_ಬಿಟ್_ಕ್ಷೇತ್ರ_TYPE (ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (ಮೌಲ್ಯ, 1)))))
    ಮೌಲ್ಯ = non_lvalue_loc (loc, ಮೌಲ್ಯ);

  /* Don't allow the results of casting to floating-point or complex
     types be confused with actual constants, or casts involving
     integer and pointer types other than direct integer-to-integer
     and integer-to-pointer be confused with integer constant
     expressions and null pointer constants.  */
  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ಮೌಲ್ಯ) == REAL_CST
      || ವೃಕ್ಷ_ಸಂಕೇತ (ಮೌಲ್ಯ) == COMPLEX_CST
      || (ವೃಕ್ಷ_ಸಂಕೇತ (ಮೌಲ್ಯ) == INTEGER_CST
	  && !((ವೃಕ್ಷ_ಸಂಕೇತ (ಅಭಿವ್ಯಕ್ತಿ) == INTEGER_CST
		&& INTEGRAL_TYPE_P (ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ)))
	       || ವೃಕ್ಷ_ಸಂಕೇತ (ಅಭಿವ್ಯಕ್ತಿ) == REAL_CST
	       || ವೃಕ್ಷ_ಸಂಕೇತ (ಅಭಿವ್ಯಕ್ತಿ) == COMPLEX_CST)))
      ಮೌಲ್ಯ = build1 (NOP_ಅಭಿವ್ಯಕ್ತಿ, type, ಮೌಲ್ಯ);

  /* If the expression has integer operands and so can occur in an
     unevaluated part of an integer constant expression, ensure the
     return value reflects this.  */
  ಆದರೆ (int_operands
      && INTEGRAL_TYPE_P (type)
      && ಮೌಲ್ಯ != error_mark_ಗಂಟು
      && !ಅಭಿವ್ಯಕ್ತಿ_INT_CONST_OPERANDS (ಮೌಲ್ಯ))
    ಮೌಲ್ಯ = note_integer_operands (ಮೌಲ್ಯ);

  protected_ಗಣ_ಅಭಿವ್ಯಕ್ತಿ_location (ಮೌಲ್ಯ, loc);
  ಹಿಂತಿರುಗಿ ಮೌಲ್ಯ;
}

/* Interpret a cast of expression EXPR to type TYPE.  LOC is the
   location of the open paren of the cast, or the position of the cast
   expr.  */
ವೃಕ್ಷ
c_cast_ಅಭಿವ್ಯಕ್ತಿ (location_t loc, ರಚನೆ c_type_name *type_name, ವೃಕ್ಷ ಅಭಿವ್ಯಕ್ತಿ)
{
  ವೃಕ್ಷ type;
  ವೃಕ್ಷ type_ಅಭಿವ್ಯಕ್ತಿ = NULL_ವೃಕ್ಷ;
  ತಾರ್ಕಿಕ type_ಅಭಿವ್ಯಕ್ತಿ_const = ನಿಜ;
  ವೃಕ್ಷ ret;
  ಪೂರ್ಣಾಂಕ saved_wsp = warn_strict_prototypes;

  /* This avoids warnings about unprototyped casts on
     integers.  E.g. "#define SIG_DFL (void(*)())0".  */
  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ಅಭಿವ್ಯಕ್ತಿ) == INTEGER_CST)
    warn_strict_prototypes = 0;
  type = groktypename (type_name, &type_ಅಭಿವ್ಯಕ್ತಿ, &type_ಅಭಿವ್ಯಕ್ತಿ_const);
  warn_strict_prototypes = saved_wsp;

  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ಅಭಿವ್ಯಕ್ತಿ) == ADDR_ಅಭಿವ್ಯಕ್ತಿ && !VOID_TYPE_P (type)
      && reject_gcc_builtin (ಅಭಿವ್ಯಕ್ತಿ))
    ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;

  ret = build_c_cast (loc, type, ಅಭಿವ್ಯಕ್ತಿ);
  ಆದರೆ (ret == error_mark_ಗಂಟು)
    ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;

  ಆದರೆ (type_ಅಭಿವ್ಯಕ್ತಿ)
    {
      ತಾರ್ಕಿಕ inner_ಅಭಿವ್ಯಕ್ತಿ_const = ನಿಜ;
      ret = c_fully_fold (ret, require_constant_ಮೌಲ್ಯ, &inner_ಅಭಿವ್ಯಕ್ತಿ_const);
      ret = build2 (C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (ret), type_ಅಭಿವ್ಯಕ್ತಿ, ret);
      C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ_NON_CONST (ret) = !(type_ಅಭಿವ್ಯಕ್ತಿ_const
					     && inner_ಅಭಿವ್ಯಕ್ತಿ_const);
      ಗಣ_ಅಭಿವ್ಯಕ್ತಿ_LOCATION (ret, loc);
    }

  ಆದರೆ (!ಅಭಿವ್ಯಕ್ತಿ_HAS_LOCATION (ret))
    protected_ಗಣ_ಅಭಿವ್ಯಕ್ತಿ_location (ret, loc);

  /* C++ does not permits types to be defined in a cast, but it
     allows references to incomplete types.  */
  ಆದರೆ (warn_cxx_compat && type_name->specs->typespec_ಬಗೆ == ctsk_tagdef)
    warning_at (loc, OPT_Wc___compat,
		"defining a type in a cast is invalid in C++");

  ಹಿಂತಿರುಗಿ ret;
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
		   ಎಣಿಕೆ ವೃಕ್ಷ_ಸಂಕೇತ_2 modifycode,
		   location_t rhs_loc, ವೃಕ್ಷ rhs, ವೃಕ್ಷ rhs_origtype)
{
  ವೃಕ್ಷ ಫಲಿತಾಂಶ;
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
  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (lhs) == ERROR_MARK || ವೃಕ್ಷ_ಸಂಕೇತ (rhs) == ERROR_MARK)
    ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;

  /* Ensure an error for assigning a non-lvalue array to an array in
     C90.  */
  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (lhstype) == ARRAY_TYPE)
    {
      error_at (location, "assignment to expression with array type");
      ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
    }

  /* For ObjC properties, defer this check.  */
  ಆದರೆ (!objc_is_property_ref (lhs) && !lvalue_or_else (location, lhs, lv_ನಿಯೋಜಿಸು))
    ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;

  is_atomic_op = really_atomic_lvalue (lhs);

  newrhs = rhs;

  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (lhs) == C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ)
    {
      ವೃಕ್ಷ inner = build_modify_ಅಭಿವ್ಯಕ್ತಿ (location, C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ_ಅಭಿವ್ಯಕ್ತಿ (lhs),
				      lhs_origtype, modifycode, rhs_loc, rhs,
				      rhs_origtype);
      ಆದರೆ (inner == error_mark_ಗಂಟು)
	ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
      ಫಲಿತಾಂಶ = build2 (C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (inner),
		       C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ_PRE (lhs), inner);
      gcc_assert (!C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ_INT_OPERANDS (lhs));
      C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ_NON_CONST (ಫಲಿತಾಂಶ) = 1;
      protected_ಗಣ_ಅಭಿವ್ಯಕ್ತಿ_location (ಫಲಿತಾಂಶ, location);
      ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
    }

  /* If a binary op has been requested, combine the old LHS value with the RHS
     producing the value we should actually store into the LHS.  */

  ಆದರೆ (modifycode != NOP_ಅಭಿವ್ಯಕ್ತಿ)
    {
      lhs = c_fully_fold (lhs, ಸುಳ್ಳು, ಖಾಲಿ, ನಿಜ);
      lhs = stabilize_reference (lhs);

      /* Construct the RHS for any non-atomic compound assignment. */
      ಆದರೆ (!is_atomic_op)
        {
	  /* If in LHS op= RHS the RHS has side-effects, ensure they
	     are preevaluated before the rest of the assignment expression's
	     side-effects, because RHS could contain e.g. function calls
	     that modify LHS.  */
	  ಆದರೆ (ವೃಕ್ಷ_SIDE_EFFECTS (rhs))
	    {
	      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (rhs) == EXCESS_PRECISION_ಅಭಿವ್ಯಕ್ತಿ)
		newrhs = save_ಅಭಿವ್ಯಕ್ತಿ (ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (rhs, 0));
	      ಇಲ್ಲದಿದ್ದರೆ
		newrhs = save_ಅಭಿವ್ಯಕ್ತಿ (rhs);
	      rhseval = newrhs;
	      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (rhs) == EXCESS_PRECISION_ಅಭಿವ್ಯಕ್ತಿ)
		newrhs = build1 (EXCESS_PRECISION_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (rhs),
				 newrhs);
	    }
	  ತಾರ್ಕಿಕ clear_decl_read = ಸುಳ್ಳು;
	  ಆದರೆ ((VAR_P (lhs) || ವೃಕ್ಷ_ಸಂಕೇತ (lhs) == PARM_DECL)
	      && !DECL_READ_P (lhs)
	      && (VAR_P (lhs) ? warn_ಬಳಸದ_but_ಗಣ_variable
			      : warn_ಬಳಸದ_but_ಗಣ_parameter) > 2)
	    {
	      mark_exp_read (newrhs);
	      ಆದರೆ (!DECL_READ_P (lhs))
		clear_decl_read = ನಿಜ;
	    }

	  newrhs = build_ದ್ವಿಮಾನ_op (location, modifycode,
				    convert_lvalue_ಗಮ್ಯ_rvalue (location, lhs,
							      ನಿಜ, ನಿಜ),
				    newrhs, ನಿಜ);
	  ಆದರೆ (clear_decl_read)
	    DECL_READ_P (lhs) = 0;

	  /* The original type of the right hand side is no longer
	     meaningful.  */
	  rhs_origtype = NULL_ವೃಕ್ಷ;
	}
    }

  ಆದರೆ (c_dialect_objc ())
    {
      /* Check if we are modifying an Objective-C property reference;
	 if so, we need to generate setter calls.  */
      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (newrhs) == EXCESS_PRECISION_ಅಭಿವ್ಯಕ್ತಿ)
	ಫಲಿತಾಂಶ = objc_maybe_build_modify_ಅಭಿವ್ಯಕ್ತಿ (lhs, ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (newrhs, 0));
      ಇಲ್ಲದಿದ್ದರೆ
	ಫಲಿತಾಂಶ = objc_maybe_build_modify_ಅಭಿವ್ಯಕ್ತಿ (lhs, newrhs);
      ಆದರೆ (ಫಲಿತಾಂಶ)
	ಹೋಗು return_ಫಲಿತಾಂಶ;

      /* Else, do the check that we postponed for Objective-C.  */
      ಆದರೆ (!lvalue_or_else (location, lhs, lv_ನಿಯೋಜಿಸು))
	ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
    }

  /* Give an error for storing in something that is 'const'.  */

  ಆದರೆ (TYPE_READONLY (lhstype)
      || (ದಾಖಲೆ_OR_UNION_TYPE_P (lhstype)
	  && C_TYPE_FIELDS_READONLY (lhstype)))
    {
      readonly_error (location, lhs, lv_ನಿಯೋಜಿಸು);
      ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
    }
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ವೃಕ್ಷ_READONLY (lhs))
    readonly_warning (lhs, lv_ನಿಯೋಜಿಸು);

  /* If storing into a structure or union member,
     it has probably been given type `int'.
     Compute the type that would go with
     the actual amount of storage the member occupies.  */

  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (lhs) == COMPONENT_REF
      && (ವೃಕ್ಷ_ಸಂಕೇತ (lhstype) == INTEGER_TYPE
	  || ವೃಕ್ಷ_ಸಂಕೇತ (lhstype) == BOOLEAN_TYPE
	  || SCALAR_FLOAT_TYPE_P (lhstype)
	  || ವೃಕ್ಷ_ಸಂಕೇತ (lhstype) == ENUMERAL_TYPE))
    lhstype = ವೃಕ್ಷ_TYPE (get_unwidened (lhs, 0));

  /* If storing in a field that is in actuality a short or narrower than one,
     we must store in the field in its actual type.  */

  ಆದರೆ (lhstype != ವೃಕ್ಷ_TYPE (lhs))
    {
      lhs = copy_ಗಂಟು (lhs);
      ವೃಕ್ಷ_TYPE (lhs) = lhstype;
    }

  /* Issue -Wc++-compat warnings about an assignment to an enum type
     when LHS does not have its original type.  This happens for,
     e.g., an enum bitfield in a struct.  */
  ಆದರೆ (warn_cxx_compat
      && lhs_origtype != NULL_ವೃಕ್ಷ
      && lhs_origtype != lhstype
      && ವೃಕ್ಷ_ಸಂಕೇತ (lhs_origtype) == ENUMERAL_TYPE)
    {
      ವೃಕ್ಷ checktype = (rhs_origtype != NULL_ವೃಕ್ಷ
			? rhs_origtype
			: ವೃಕ್ಷ_TYPE (rhs));
      ಆದರೆ (checktype != error_mark_ಗಂಟು
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

  ಆದರೆ (!(is_atomic_op && modifycode != NOP_ಅಭಿವ್ಯಕ್ತಿ))
    {
      ವೃಕ್ಷ rhs_semantic_type = NULL_ವೃಕ್ಷ;
      ಆದರೆ (!c_ಒಳ_omp_for)
	{
	  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (newrhs) == EXCESS_PRECISION_ಅಭಿವ್ಯಕ್ತಿ)
	    {
	      rhs_semantic_type = ವೃಕ್ಷ_TYPE (newrhs);
	      newrhs = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (newrhs, 0);
	    }
	  npc = null_ಸೂಚಕ_constant_p (newrhs);
	  newrhs = c_fully_fold (newrhs, ಸುಳ್ಳು, ಖಾಲಿ);
	  ಆದರೆ (rhs_semantic_type)
	    newrhs = build1 (EXCESS_PRECISION_ಅಭಿವ್ಯಕ್ತಿ, rhs_semantic_type, newrhs);
	}
      ಇಲ್ಲದಿದ್ದರೆ
	npc = null_ಸೂಚಕ_constant_p (newrhs);
      newrhs = convert_for_assignment (location, rhs_loc, lhstype, newrhs,
				       rhs_origtype, ic_ನಿಯೋಜಿಸು, npc,
				       NULL_ವೃಕ್ಷ, NULL_ವೃಕ್ಷ, 0);
      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (newrhs) == ERROR_MARK)
	ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
    }

  /* Emit ObjC write barrier, if necessary.  */
  ಆದರೆ (c_dialect_objc () && flag_objc_gc)
    {
      ಫಲಿತಾಂಶ = objc_generate_write_barrier (lhs, modifycode, newrhs);
      ಆದರೆ (ಫಲಿತಾಂಶ)
	{
	  protected_ಗಣ_ಅಭಿವ್ಯಕ್ತಿ_location (ಫಲಿತಾಂಶ, location);
	  ಹೋಗು return_ಫಲಿತಾಂಶ;
	}
    }

  /* Scan operands.  */

  ಆದರೆ (is_atomic_op)
    ಫಲಿತಾಂಶ = build_atomic_ನಿಯೋಜಿಸು (location, lhs, modifycode, newrhs, ಸುಳ್ಳು);
  ಇಲ್ಲದಿದ್ದರೆ
    {
      ಫಲಿತಾಂಶ = build2 (MODIFY_ಅಭಿವ್ಯಕ್ತಿ, lhstype, lhs, newrhs);
      ವೃಕ್ಷ_SIDE_EFFECTS (ಫಲಿತಾಂಶ) = 1;
      protected_ಗಣ_ಅಭಿವ್ಯಕ್ತಿ_location (ಫಲಿತಾಂಶ, location);
    }

  /* If we got the LHS in a different type for storing in,
     convert the result back to the nominal type of LHS
     so that the value we return always has the same type
     as the LHS argument.  */

  ಆದರೆ (olhstype == ವೃಕ್ಷ_TYPE (ಫಲಿತಾಂಶ))
    ಹೋಗು return_ಫಲಿತಾಂಶ;

  ಫಲಿತಾಂಶ = convert_for_assignment (location, rhs_loc, olhstype, ಫಲಿತಾಂಶ,
				   rhs_origtype, ic_ನಿಯೋಜಿಸು, ಸುಳ್ಳು, NULL_ವೃಕ್ಷ,
				   NULL_ವೃಕ್ಷ, 0);
  protected_ಗಣ_ಅಭಿವ್ಯಕ್ತಿ_location (ಫಲಿತಾಂಶ, location);

return_ಫಲಿತಾಂಶ:
  ಆದರೆ (rhseval)
    ಫಲಿತಾಂಶ = build2 (COMPOUND_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (ಫಲಿತಾಂಶ), rhseval, ಫಲಿತಾಂಶ);
  ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
}

/* Return whether STRUCT_TYPE has an anonymous field with type TYPE.
   This is used to implement -fplan9-extensions.  */

ಸ್ಥಿರ ತಾರ್ಕಿಕ
ಕಂಡುಹಿಡಿ_anonymous_ಕ್ಷೇತ್ರ_with_type (ವೃಕ್ಷ struct_type, ವೃಕ್ಷ type)
{
  ವೃಕ್ಷ ಕ್ಷೇತ್ರ_2;
  ತಾರ್ಕಿಕ ಸಿಕ್ಕಿತು;

  gcc_assert (ದಾಖಲೆ_OR_UNION_TYPE_P (struct_type));
  ಸಿಕ್ಕಿತು = ಸುಳ್ಳು;
  ಗಾಗಿ (ಕ್ಷೇತ್ರ_2 = TYPE_FIELDS (struct_type);
       ಕ್ಷೇತ್ರ_2 != NULL_ವೃಕ್ಷ;
       ಕ್ಷೇತ್ರ_2 = ವೃಕ್ಷ_CHAIN (ಕ್ಷೇತ್ರ_2))
    {
      ವೃಕ್ಷ fieldtype = remove_qualifiers (ವೃಕ್ಷ_TYPE (ಕ್ಷೇತ್ರ_2));
      ಆದರೆ (DECL_NAME (ಕ್ಷೇತ್ರ_2) == ಖಾಲಿ
	  && comptypes (type, fieldtype))
	{
	  ಆದರೆ (ಸಿಕ್ಕಿತು)
	    ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
	  ಸಿಕ್ಕಿತು = ನಿಜ;
	}
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (DECL_NAME (ಕ್ಷೇತ್ರ_2) == ಖಾಲಿ
	       && ದಾಖಲೆ_OR_UNION_TYPE_P (ವೃಕ್ಷ_TYPE (ಕ್ಷೇತ್ರ_2))
	       && ಕಂಡುಹಿಡಿ_anonymous_ಕ್ಷೇತ್ರ_with_type (ವೃಕ್ಷ_TYPE (ಕ್ಷೇತ್ರ_2), type))
	{
	  ಆದರೆ (ಸಿಕ್ಕಿತು)
	    ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
	  ಸಿಕ್ಕಿತು = ನಿಜ;
	}
    }
  ಹಿಂತಿರುಗಿ ಸಿಕ್ಕಿತು;
}

/* RHS is an expression whose type is pointer to struct.  If there is
   an anonymous field in RHS with type TYPE, then return a pointer to
   that field in RHS.  This is used with -fplan9-extensions.  This
   returns NULL if no conversion could be found.  */

ಸ್ಥಿರ ವೃಕ್ಷ
convert_ಗಮ್ಯ_anonymous_ಕ್ಷೇತ್ರ (location_t location, ವೃಕ್ಷ type, ವೃಕ್ಷ rhs)
{
  ವೃಕ್ಷ rhs_struct_type, lhs_main_type;
  ವೃಕ್ಷ ಕ್ಷೇತ್ರ_2, ಸಿಕ್ಕಿತು_ಕ್ಷೇತ್ರ;
  ತಾರ್ಕಿಕ ಸಿಕ್ಕಿತು_sub_ಕ್ಷೇತ್ರ;
  ವೃಕ್ಷ ret;

  gcc_assert (ಸೂಚಕ_TYPE_P (ವೃಕ್ಷ_TYPE (rhs)));
  rhs_struct_type = ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_TYPE (rhs));
  gcc_assert (ದಾಖಲೆ_OR_UNION_TYPE_P (rhs_struct_type));

  gcc_assert (ಸೂಚಕ_TYPE_P (type));
  lhs_main_type = remove_qualifiers (ವೃಕ್ಷ_TYPE (type));

  ಸಿಕ್ಕಿತು_ಕ್ಷೇತ್ರ = NULL_ವೃಕ್ಷ;
  ಸಿಕ್ಕಿತು_sub_ಕ್ಷೇತ್ರ = ಸುಳ್ಳು;
  ಗಾಗಿ (ಕ್ಷೇತ್ರ_2 = TYPE_FIELDS (rhs_struct_type);
       ಕ್ಷೇತ್ರ_2 != NULL_ವೃಕ್ಷ;
       ಕ್ಷೇತ್ರ_2 = ವೃಕ್ಷ_CHAIN (ಕ್ಷೇತ್ರ_2))
    {
      ಆದರೆ (DECL_NAME (ಕ್ಷೇತ್ರ_2) != NULL_ವೃಕ್ಷ
	  || !ದಾಖಲೆ_OR_UNION_TYPE_P (ವೃಕ್ಷ_TYPE (ಕ್ಷೇತ್ರ_2)))
	ಮುಂದುವರಿ;
      ವೃಕ್ಷ fieldtype = remove_qualifiers (ವೃಕ್ಷ_TYPE (ಕ್ಷೇತ್ರ_2));
      ಆದರೆ (comptypes (lhs_main_type, fieldtype))
	{
	  ಆದರೆ (ಸಿಕ್ಕಿತು_ಕ್ಷೇತ್ರ != NULL_ವೃಕ್ಷ)
	    ಹಿಂತಿರುಗಿ NULL_ವೃಕ್ಷ;
	  ಸಿಕ್ಕಿತು_ಕ್ಷೇತ್ರ = ಕ್ಷೇತ್ರ_2;
	}
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ಕಂಡುಹಿಡಿ_anonymous_ಕ್ಷೇತ್ರ_with_type (ವೃಕ್ಷ_TYPE (ಕ್ಷೇತ್ರ_2),
					       lhs_main_type))
	{
	  ಆದರೆ (ಸಿಕ್ಕಿತು_ಕ್ಷೇತ್ರ != NULL_ವೃಕ್ಷ)
	    ಹಿಂತಿರುಗಿ NULL_ವೃಕ್ಷ;
	  ಸಿಕ್ಕಿತು_ಕ್ಷೇತ್ರ = ಕ್ಷೇತ್ರ_2;
	  ಸಿಕ್ಕಿತು_sub_ಕ್ಷೇತ್ರ = ನಿಜ;
	}
    }

  ಆದರೆ (ಸಿಕ್ಕಿತು_ಕ್ಷೇತ್ರ == NULL_ವೃಕ್ಷ)
    ಹಿಂತಿರುಗಿ NULL_ವೃಕ್ಷ;

  ret = fold_build3_loc (location, COMPONENT_REF, ವೃಕ್ಷ_TYPE (ಸಿಕ್ಕಿತು_ಕ್ಷೇತ್ರ),
			 build_fold_ಪರೋಕ್ಷ_ref (rhs), ಸಿಕ್ಕಿತು_ಕ್ಷೇತ್ರ,
			 NULL_ವೃಕ್ಷ);
  ret = build_fold_addr_ಅಭಿವ್ಯಕ್ತಿ_loc (location, ret);

  ಆದರೆ (ಸಿಕ್ಕಿತು_sub_ಕ್ಷೇತ್ರ)
    {
      ret = convert_ಗಮ್ಯ_anonymous_ಕ್ಷೇತ್ರ (location, type, ret);
      gcc_assert (ret != NULL_ವೃಕ್ಷ);
    }

  ಹಿಂತಿರುಗಿ ret;
}

/* Issue an error message for a bad initializer component.
   GMSGID identifies the message.
   The component name is taken from the spelling stack.  */

ಸ್ಥಿರ ಶೂನ್ಯ ATTRIBUTE_GCC_DIAG (2,0)
error_init (location_t loc, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *gmsgid, ...)
{
  ಅಕ್ಷರ *ofwhat;

  auto_diagnostic_ಗುಂಪು d;

  /* The gmsgid may be a format string with %< and %>. */
  va_list ap;
  va_ಆರಂಭ (ap, gmsgid);
  ತಾರ್ಕಿಕ warned = emit_diagnostic_valist (diagnostics::ಬಗೆ::error,
					loc, -1, gmsgid, &ap);
  va_ಕೊನೆ (ap);

  ofwhat = print_spelling ((ಅಕ್ಷರ *) alloca (spelling_ಉದ್ದಳತೆ () + 1));
  ಆದರೆ (*ofwhat && warned)
    inform (loc, "(near initialization for %qs)", ofwhat);
}

/* Used to implement pedwarn_init and permerror_init.  */

ಸ್ಥಿರ ತಾರ್ಕಿಕ ATTRIBUTE_GCC_DIAG (3,0)
pedwarn_permerror_init (location_t loc, ಪೂರ್ಣಾಂಕ opt, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *gmsgid,
			va_list *ap, ಎಣಿಕೆ diagnostics::ಬಗೆ ಬಗೆ)
{
  /* Use the location where a macro was expanded rather than where
     it was defined to make sure macros defined in system headers
     but used incorrectly elsewhere are diagnosed.  */
  location_t exploc = expansion_ಬಿಂದು_location_if_ಒಳ_system_ಶೀರ್ಷಿಕೆ (loc);
  auto_diagnostic_ಗುಂಪು d;
  ತಾರ್ಕಿಕ warned = emit_diagnostic_valist (ಬಗೆ, exploc, opt, gmsgid, ap);
  ಆದರೆ (warned)
    {
      ಅಕ್ಷರ *ofwhat = print_spelling ((ಅಕ್ಷರ *) alloca (spelling_ಉದ್ದಳತೆ () + 1));
      ಆದರೆ (*ofwhat)
	inform (exploc, "(near initialization for %qs)", ofwhat);
    }
  ಹಿಂತಿರುಗಿ warned;
}

/* Issue a pedantic warning for a bad initializer component.  OPT is
   the option OPT_* (from options.h) controlling this warning or 0 if
   it is unconditionally given.  GMSGID identifies the message.  The
   component name is taken from the spelling stack.  */

ಸ್ಥಿರ ತಾರ್ಕಿಕ ATTRIBUTE_GCC_DIAG (3,0)
pedwarn_init (location_t loc, ಪೂರ್ಣಾಂಕ opt, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *gmsgid, ...)
{
  va_list ap;
  va_ಆರಂಭ (ap, gmsgid);
  ತಾರ್ಕಿಕ warned = pedwarn_permerror_init (loc, opt, gmsgid, &ap,
					diagnostics::ಬಗೆ::pedwarn);
  va_ಕೊನೆ (ap);
  ಹಿಂತಿರುಗಿ warned;
}

/* Like pedwarn_init, but issue a permerror.  */

ಸ್ಥಿರ ತಾರ್ಕಿಕ ATTRIBUTE_GCC_DIAG (3,0)
permerror_init (location_t loc, ಪೂರ್ಣಾಂಕ opt, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *gmsgid, ...)
{
  va_list ap;
  va_ಆರಂಭ (ap, gmsgid);
  ತಾರ್ಕಿಕ warned = pedwarn_permerror_init (loc, opt, gmsgid, &ap,
					diagnostics::ಬಗೆ::permerror);
  va_ಕೊನೆ (ap);
  ಹಿಂತಿರುಗಿ warned;
}

/* Issue a warning for a bad initializer component.

   OPT is the OPT_W* value corresponding to the warning option that
   controls this warning.  GMSGID identifies the message.  The
   component name is taken from the spelling stack.  */

ಸ್ಥಿರ ಶೂನ್ಯ
warning_init (location_t loc, ಪೂರ್ಣಾಂಕ opt, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *gmsgid)
{
  ಅಕ್ಷರ *ofwhat;
  ತಾರ್ಕಿಕ warned;

  auto_diagnostic_ಗುಂಪು d;

  /* Use the location where a macro was expanded rather than where
     it was defined to make sure macros defined in system headers
     but used incorrectly elsewhere are diagnosed.  */
  location_t exploc = expansion_ಬಿಂದು_location_if_ಒಳ_system_ಶೀರ್ಷಿಕೆ (loc);

  /* The gmsgid may be a format string with %< and %>. */
  warned = warning_at (exploc, opt, gmsgid);
  ಆದರೆ (warned)
    {
      ofwhat = print_spelling ((ಅಕ್ಷರ *) alloca (spelling_ಉದ್ದಳತೆ () + 1));
      ಆದರೆ (*ofwhat)
	inform (exploc, "(near initialization for %qs)", ofwhat);
    }
}

/* If TYPE is an array type and EXPR is a parenthesized string
   constant, warn if pedantic that EXPR is being used to initialize an
   object of type TYPE.  */

ಶೂನ್ಯ
maybe_warn_string_init (location_t loc, ವೃಕ್ಷ type, ರಚನೆ c_ಅಭಿವ್ಯಕ್ತಿ ಅಭಿವ್ಯಕ್ತಿ)
{
  ಆದರೆ (pedantic
      && ವೃಕ್ಷ_ಸಂಕೇತ (type) == ARRAY_TYPE
      && ವೃಕ್ಷ_ಸಂಕೇತ (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ) == STRING_CST
      && ಅಭಿವ್ಯಕ್ತಿ.original_ಸಂಕೇತ != STRING_CST)
    pedwarn_init (loc, OPT_Wpedantic,
		  "array initialized from parenthesized string constant");
}

/* Attempt to locate the parameter with the given index within FNDECL,
   returning DECL_SOURCE_LOCATION (FNDECL) if it can't be found.  */

ಸ್ಥಿರ location_t
get_fndecl_ವಾದ_location (ವೃಕ್ಷ fndecl, ಪೂರ್ಣಾಂಕ argnum)
{
  ಪೂರ್ಣಾಂಕ i;
  ವೃಕ್ಷ param;

  /* Locate param by index within DECL_ARGUMENTS (fndecl).  */
  ಗಾಗಿ (i = 0, param = DECL_ARGUMENTS (fndecl);
       i < argnum && param;
       i++, param = ವೃಕ್ಷ_CHAIN (param))
    ;

  /* If something went wrong (e.g. if we have a builtin and thus no arguments),
     return DECL_SOURCE_LOCATION (FNDECL).  */
  ಆದರೆ (param == ಖಾಲಿ)
    ಹಿಂತಿರುಗಿ DECL_ಮೂಲ_LOCATION (fndecl);

  ಹಿಂತಿರುಗಿ DECL_ಮೂಲ_LOCATION (param);
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
inform_for_arg (ವೃಕ್ಷ fundecl, location_t ploc, ಪೂರ್ಣಾಂಕ parmnum,
		ವೃಕ್ಷ expected_type, ವೃಕ್ಷ actual_type)
{
  location_t loc;
  ಆದರೆ (fundecl && !DECL_IS_UNDECLARED_BUILTIN (fundecl))
    loc = get_fndecl_ವಾದ_location (fundecl, parmnum - 1);
  ಇಲ್ಲದಿದ್ದರೆ
    loc = ploc;

  gcc_rich_location richloc (loc, ಶೂನ್ಯಸೂಚಕ, highlight_colors::expected);

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
maybe_warn_builtin_no_proto_arg (location_t loc, ವೃಕ್ಷ fundecl, ಪೂರ್ಣಾಂಕ parmnum,
				 ವೃಕ್ಷ parmtype, ವೃಕ್ಷ argtype)
{
  ವೃಕ್ಷ_ಸಂಕೇತ_2 parmcode = ವೃಕ್ಷ_ಸಂಕೇತ (parmtype);
  ವೃಕ್ಷ_ಸಂಕೇತ_2 argcode = ವೃಕ್ಷ_ಸಂಕೇತ (argtype);
  ವೃಕ್ಷ promoted = c_type_promotes_ಗಮ್ಯ (argtype);

  /* Avoid warning for enum arguments that promote to an integer type
     of the same size/mode.  */
  ಆದರೆ (parmcode == INTEGER_TYPE
      && argcode == ENUMERAL_TYPE
      && TYPE_ಬಹುಲಕ (parmtype) == TYPE_ಬಹುಲಕ (argtype))
    ಹಿಂತಿರುಗಿ;

  ಆದರೆ ((parmcode == argcode
       || (parmcode == INTEGER_TYPE
	   && argcode == ENUMERAL_TYPE))
      && TYPE_MAIN_VARIANT (parmtype) == TYPE_MAIN_VARIANT (promoted))
    ಹಿಂತಿರುಗಿ;

  /* This diagnoses even signed/unsigned mismatches.  Those might be
     safe in many cases but GCC may emit suboptimal code for them so
     warning on those cases drives efficiency improvements.  */
  ಆದರೆ (warning_at (loc, OPT_Wbuiltin_declaration_mismatch,
		  TYPE_MAIN_VARIANT (promoted) == argtype
		  ? G_("%qD argument %d type is %qT where %qT is expected "
		       "in a call to built-in function declared without "
		       "prototype")
		  : G_("%qD argument %d promotes to %qT where %qT is expected "
		       "in a call to built-in function declared without "
		       "prototype"),
		  fundecl, parmnum, promoted, parmtype))
    inform (DECL_ಮೂಲ_LOCATION (fundecl),
	    "built-in %qD declared here",
	    fundecl);
}

/* Print a declaration in quotes, with the given highlight_color.
   Analogous to handler for %qD, but with a specific highlight color.  */

ವರ್ಗ pp_element_quoted_decl : ಸಾರ್ವಜನಿಕ pp_element
{
ಸಾರ್ವಜನಿಕ:
  pp_element_quoted_decl (ವೃಕ್ಷ decl, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *highlight_color)
  : m_decl (decl),
    m_highlight_color (highlight_color)
  {
  }

  ಶೂನ್ಯ ಕೂಡಿಸು_ಗಮ್ಯ_phase_2 (pp_markup::context &ctxt) override
  {
    ctxt.begin_quote ();
    ctxt.begin_highlight_color (m_highlight_color);

    print_decl (ctxt);

    ctxt.ಕೊನೆ_highlight_color ();
    ctxt.ಕೊನೆ_quote ();
  }

  ಶೂನ್ಯ print_decl (pp_markup::context &ctxt)
  {
    pretty_printer *ಸ್ಥಿರಾಂಕ pp = &ctxt.m_pp;
    pp->ಗಣ_padding (pp_none);
    ಆದರೆ (DECL_NAME (m_decl))
      pp_identifier (pp, lang_hooks.decl_printable_name (m_decl, 2));
    ಇಲ್ಲದಿದ್ದರೆ
      pp_string (pp, _("({anonymous})"));
  }

ಖಾಸಗಿ:
  ವೃಕ್ಷ m_decl;
  ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *m_highlight_color;
};

/* If TYPE is from a typedef, issue a note showing the location
   to the user.
   Use HIGHLIGHT_COLOR as the highlight color.  */

ಸ್ಥಿರ ಶೂನ್ಯ
maybe_inform_typedef_location (ವೃಕ್ಷ type, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *highlight_color)
{
  ಆದರೆ (!typedef_variant_p (type))
    ಹಿಂತಿರುಗಿ;

  ವೃಕ್ಷ typedef_decl = TYPE_NAME (type);
  gcc_assert (ವೃಕ್ಷ_ಸಂಕೇತ (typedef_decl) == TYPE_DECL);
  gcc_rich_location richloc (DECL_ಮೂಲ_LOCATION (typedef_decl),
			     ಶೂನ್ಯಸೂಚಕ, highlight_color);
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
			ವೃಕ್ಷ rhs, ವೃಕ್ಷ origtype, ಎಣಿಕೆ impl_conv errtype,
			ತಾರ್ಕಿಕ null_ಸೂಚಕ_constant, ವೃಕ್ಷ fundecl,
			ವೃಕ್ಷ function, ಪೂರ್ಣಾಂಕ parmnum, ಪೂರ್ಣಾಂಕ warnopt /* = 0 */)
{
  ಎಣಿಕೆ ವೃಕ್ಷ_ಸಂಕೇತ_2 codel = ವೃಕ್ಷ_ಸಂಕೇತ (type);
  ವೃಕ್ಷ orig_rhs = rhs;
  ವೃಕ್ಷ rhstype;
  ಎಣಿಕೆ ವೃಕ್ಷ_ಸಂಕೇತ_2 coder;
  ವೃಕ್ಷ rname = NULL_ವೃಕ್ಷ;
  ತಾರ್ಕಿಕ objc_ok = ಸುಳ್ಳು;

  /* Use the expansion point location to handle cases such as user's
     function returning a wrong-type macro defined in a system header.  */
  location = expansion_ಬಿಂದು_location_if_ಒಳ_system_ಶೀರ್ಷಿಕೆ (location);

  ಆದರೆ (errtype == ic_argpass)
    {
      ವೃಕ್ಷ selector;
      /* Change pointer to function to the function itself for
	 diagnostics.  */
      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (function) == ADDR_ಅಭಿವ್ಯಕ್ತಿ
	  && ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (function, 0)) == FUNCTION_DECL)
	function = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (function, 0);

      /* Handle an ObjC selector specially for diagnostics.  */
      selector = objc_ಸಂದೇಶ_selector ();
      rname = function;
      ಆದರೆ (selector && parmnum > 2)
	{
	  rname = selector;
	  parmnum -= 2;
	}
    }

  /* This macro is used to emit diagnostics to ensure that all format
     strings are complete sentences, visible to gettext and checked at
     compile time.  */
#ವ್ಯಾಖ್ಯಾನಿಸು PEDWARN_FOR_ASSIGNMENT(LOCATION, PLOC, OPT, AR, AS, ಒಳ, RE)	 \
  ಮಾಡು {                                                                   \
    ಆಯ್ಕೆ (errtype)                                                     \
      {                                                                  \
      ಸ್ಥಿತಿ ic_argpass:                                                   \
	{								\
	  auto_diagnostic_ಗುಂಪು d;						\
	  ಆದರೆ (pedwarn (PLOC, OPT, AR, parmnum, rname))		\
	    inform_for_arg (fundecl, (PLOC), parmnum, type, rhstype); \
	}								\
        ನಿಲ್ಲಿಸು;                                                           \
      ಸ್ಥಿತಿ ic_ನಿಯೋಜಿಸು:                                                    \
        pedwarn (LOCATION, OPT, AS);                                     \
        ನಿಲ್ಲಿಸು;                                                           \
      ಸ್ಥಿತಿ ic_init:                                                      \
      ಸ್ಥಿತಿ ic_init_const:                                                \
        pedwarn_init (LOCATION, OPT, ಒಳ);                                \
        ನಿಲ್ಲಿಸು;                                                           \
      ಸ್ಥಿತಿ ic_return:                                                    \
        pedwarn (LOCATION, OPT, RE);					 \
        ನಿಲ್ಲಿಸು;                                                           \
      ಪೂರ್ವನಿಯೋಜಿತ:                                                           \
        gcc_unreachable ();                                              \
      }                                                                  \
  } ಆಗ (0)

  /* This macro is used to emit diagnostics to ensure that all format
     strings are complete sentences, visible to gettext and checked at
     compile time.  It can be called with 'pedwarn' or 'warning_at'.  */
#ವ್ಯಾಖ್ಯಾನಿಸು WARNING_FOR_QUALIFIERS(PEDWARN, LOCATION, PLOC, OPT, AR, AS, ಒಳ, RE, QUALS) \
  ಮಾಡು {                                                                   \
    ಆಯ್ಕೆ (errtype)                                                     \
      {                                                                  \
      ಸ್ಥಿತಿ ic_argpass:                                                   \
	{								 \
	  auto_diagnostic_ಗುಂಪು d;					 \
	  ಆದರೆ (PEDWARN) {						 \
	    ಆದರೆ (pedwarn (PLOC, OPT, AR, parmnum, rname, QUALS))          \
	      inform_for_arg (fundecl, (PLOC), parmnum, type, rhstype);  \
	  } ಇಲ್ಲದಿದ್ದರೆ {							 \
	    ಆದರೆ (warning_at (PLOC, OPT, AR, parmnum, rname, QUALS))	 \
	      inform_for_arg (fundecl, (PLOC), parmnum, type, rhstype);  \
	  }								 \
	}								 \
        ನಿಲ್ಲಿಸು;                                                           \
      ಸ್ಥಿತಿ ic_ನಿಯೋಜಿಸು:                                                    \
	ಆದರೆ (PEDWARN)							 \
	  pedwarn (LOCATION, OPT, AS, QUALS);                            \
	ಇಲ್ಲದಿದ್ದರೆ								 \
	  warning_at (LOCATION, OPT, AS, QUALS);                         \
        ನಿಲ್ಲಿಸು;                                                           \
      ಸ್ಥಿತಿ ic_init:                                                      \
      ಸ್ಥಿತಿ ic_init_const:                                                \
	ಆದರೆ (PEDWARN)							 \
	  pedwarn (LOCATION, OPT, ಒಳ, QUALS);                            \
	ಇಲ್ಲದಿದ್ದರೆ								 \
	  warning_at (LOCATION, OPT, ಒಳ, QUALS);                         \
        ನಿಲ್ಲಿಸು;                                                           \
      ಸ್ಥಿತಿ ic_return:                                                    \
	ಆದರೆ (PEDWARN)							 \
	  pedwarn (LOCATION, OPT, RE, QUALS);                            \
	ಇಲ್ಲದಿದ್ದರೆ								 \
	  warning_at (LOCATION, OPT, RE, QUALS);                         \
        ನಿಲ್ಲಿಸು;                                                           \
      ಪೂರ್ವನಿಯೋಜಿತ:                                                           \
        gcc_unreachable ();                                              \
      }                                                                  \
  } ಆಗ (0)

  /* This macro is used to emit diagnostics to ensure that all format
     strings are complete sentences, visible to gettext and checked at
     compile time.  It is the same as PEDWARN_FOR_ASSIGNMENT but with an
     extra parameter to enumerate qualifiers.  */
#ವ್ಯಾಖ್ಯಾನಿಸು PEDWARN_FOR_QUALIFIERS(LOCATION, PLOC, OPT, AR, AS, ಒಳ, RE, QUALS) \
   WARNING_FOR_QUALIFIERS (ನಿಜ, LOCATION, PLOC, OPT, AR, AS, ಒಳ, RE, QUALS)


  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (rhs) == EXCESS_PRECISION_ಅಭಿವ್ಯಕ್ತಿ)
    rhs = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (rhs, 0);

  rhstype = ವೃಕ್ಷ_TYPE (rhs);
  coder = ವೃಕ್ಷ_ಸಂಕೇತ (rhstype);

  ಆದರೆ (coder == ERROR_MARK)
    ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;

  ಆದರೆ (c_dialect_objc ())
    {
      ಪೂರ್ಣಾಂಕ parmno;

      ಆಯ್ಕೆ (errtype)
	{
	ಸ್ಥಿತಿ ic_return:
	  parmno = 0;
	  ನಿಲ್ಲಿಸು;

	ಸ್ಥಿತಿ ic_ನಿಯೋಜಿಸು:
	  parmno = -1;
	  ನಿಲ್ಲಿಸು;

	ಸ್ಥಿತಿ ic_init:
	ಸ್ಥಿತಿ ic_init_const:
	  parmno = -2;
	  ನಿಲ್ಲಿಸು;

	ಪೂರ್ವನಿಯೋಜಿತ:
	  parmno = parmnum;
	  ನಿಲ್ಲಿಸು;
	}

      objc_ok = objc_compare_types (type, rhstype, parmno, rname);
    }

  ಆದರೆ (warn_cxx_compat)
    {
      ವೃಕ್ಷ checktype = origtype != NULL_ವೃಕ್ಷ ? origtype : rhstype;
      ಆದರೆ (checktype != error_mark_ಗಂಟು
	  && ವೃಕ್ಷ_ಸಂಕೇತ (type) == ENUMERAL_TYPE
	  && TYPE_MAIN_VARIANT (checktype) != TYPE_MAIN_VARIANT (type))
	ಆಯ್ಕೆ (errtype)
	  {
	  ಸ್ಥಿತಿ ic_argpass:
	    ಆದರೆ (pedwarn (ಅಭಿವ್ಯಕ್ತಿ_loc, OPT_Wc___compat, "enum conversion when "
			 "passing argument %d of %qE is invalid in C++",
			 parmnum, rname))
	      inform ((fundecl && !DECL_IS_UNDECLARED_BUILTIN (fundecl))
		      ? DECL_ಮೂಲ_LOCATION (fundecl) : ಅಭಿವ್ಯಕ್ತಿ_loc,
		      "expected %qT but argument is of type %qT",
		      type, rhstype);
	    ನಿಲ್ಲಿಸು;
	  ಸ್ಥಿತಿ ic_ನಿಯೋಜಿಸು:
	    pedwarn (location, OPT_Wc___compat, "enum conversion from %qT to "
		     "%qT in assignment is invalid in C++", rhstype, type);
	    ನಿಲ್ಲಿಸು;
	  ಸ್ಥಿತಿ ic_init:
	  ಸ್ಥಿತಿ ic_init_const:
	    pedwarn_init (location, OPT_Wc___compat, "enum conversion from "
			  "%qT to %qT in initialization is invalid in C++",
			  rhstype, type);
	    ನಿಲ್ಲಿಸು;
	  ಸ್ಥಿತಿ ic_return:
	    pedwarn (location, OPT_Wc___compat, "enum conversion from %qT to "
		     "%qT in return is invalid in C++", rhstype, type);
	    ನಿಲ್ಲಿಸು;
	  ಪೂರ್ವನಿಯೋಜಿತ:
	    gcc_unreachable ();
	  }
    }

  ಆದರೆ (warn_enum_conversion)
    {
      ವೃಕ್ಷ checktype = origtype != NULL_ವೃಕ್ಷ ? origtype : rhstype;
      ಆದರೆ (checktype != error_mark_ಗಂಟು
	  && ವೃಕ್ಷ_ಸಂಕೇತ (checktype) == ENUMERAL_TYPE
	  && ವೃಕ್ಷ_ಸಂಕೇತ (type) == ENUMERAL_TYPE
	  && !comptypes (TYPE_MAIN_VARIANT (checktype), TYPE_MAIN_VARIANT (type)))
       {
	  gcc_rich_location loc (location);
	  warning_at (&loc, OPT_Wenum_conversion,
		      "implicit conversion from %qT to %qT",
		      checktype, type);
       }
    }

  ಆದರೆ (TYPE_MAIN_VARIANT (type) == TYPE_MAIN_VARIANT (rhstype))
    {
      warn_for_ವಿಳಾಸ_ದ_packed_member (type, orig_rhs);
      ಆದರೆ (type != rhstype)
	/* Convert RHS to TYPE in order to not lose TYPE in diagnostics.  */
	rhs = convert (type, rhs);
      ಹಿಂತಿರುಗಿ rhs;
    }

  ಆದರೆ (coder == VOID_TYPE)
    {
      /* Except for passing an argument to an unprototyped function,
	 this is a constraint violation.  When passing an argument to
	 an unprototyped function, it is compile-time undefined;
	 making it a constraint in that case was rejected in
	 DR#252.  */
      ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ ಸಂದೇಶ_2[] = "void value not ignored as it ought to be";
      ಆದರೆ (warnopt)
	warning_at (location, warnopt, ಸಂದೇಶ_2);
      ಇಲ್ಲದಿದ್ದರೆ
	error_at (location, ಸಂದೇಶ_2);
      ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
    }
  rhs = require_complete_type (location, rhs);
  ಆದರೆ (rhs == error_mark_ಗಂಟು)
    ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;

  ಆದರೆ (coder == ಸೂಚಕ_TYPE && reject_gcc_builtin (rhs))
    ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;

  /* A non-reference type can convert to a reference.  This handles
     va_start, va_copy and possibly port built-ins.  */
  ಆದರೆ (codel == REFERENCE_TYPE && coder != REFERENCE_TYPE)
    {
      ಆದರೆ (!lvalue_p (rhs))
	{
	  ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ ಸಂದೇಶ_2[] = "cannot pass rvalue to reference parameter";
	  ಆದರೆ (warnopt)
	    warning_at (location, warnopt, ಸಂದೇಶ_2);
	  ಇಲ್ಲದಿದ್ದರೆ
	    error_at (location, ಸಂದೇಶ_2);
	  ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
	}
      ಆದರೆ (!c_mark_addressable (rhs))
	ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
      rhs = build1 (ADDR_ಅಭಿವ್ಯಕ್ತಿ, c_build_ಸೂಚಕ_type (ವೃಕ್ಷ_TYPE (rhs)), rhs);
      ಗಣ_ಅಭಿವ್ಯಕ್ತಿ_LOCATION (rhs, location);

      rhs = convert_for_assignment (location, ಅಭಿವ್ಯಕ್ತಿ_loc,
				    c_build_ಸೂಚಕ_type (ವೃಕ್ಷ_TYPE (type)),
				    rhs, origtype, errtype,
				    null_ಸೂಚಕ_constant, fundecl, function,
				    parmnum, warnopt);
      ಆದರೆ (rhs == error_mark_ಗಂಟು)
	ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;

      rhs = build1 (NOP_ಅಭಿವ್ಯಕ್ತಿ, type, rhs);
      ಗಣ_ಅಭಿವ್ಯಕ್ತಿ_LOCATION (rhs, location);
      ಹಿಂತಿರುಗಿ rhs;
    }
  /* Some types can interconvert without explicit casts.  */
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (codel == ಸದಿಶ_TYPE && coder == ಸದಿಶ_TYPE
	   && ಸದಿಶ_types_convertible_p (type, ವೃಕ್ಷ_TYPE (rhs), ನಿಜ))
    ಹಿಂತಿರುಗಿ convert (type, rhs);
  /* Arithmetic types all interconvert, and enum is treated like int.  */
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ ((codel == INTEGER_TYPE || codel == REAL_TYPE
	    || codel == FIXED_ಬಿಂದು_TYPE
	    || codel == ENUMERAL_TYPE || codel == COMPLEX_TYPE
	    || codel == BOOLEAN_TYPE || codel == BITINT_TYPE)
	   && (coder == INTEGER_TYPE || coder == REAL_TYPE
	       || coder == FIXED_ಬಿಂದು_TYPE
	       || coder == ENUMERAL_TYPE || coder == COMPLEX_TYPE
	       || coder == BOOLEAN_TYPE || coder == BITINT_TYPE))
    {
      ಆದರೆ (warnopt && errtype == ic_argpass)
	maybe_warn_builtin_no_proto_arg (ಅಭಿವ್ಯಕ್ತಿ_loc, fundecl, parmnum, type,
					 rhstype);

      ತಾರ್ಕಿಕ save = ಒಳ_late_ದ್ವಿಮಾನ_op;
      ಆದರೆ (C_BOOLEAN_TYPE_P (type) || codel == COMPLEX_TYPE
	  || (coder == REAL_TYPE
	      && (codel == INTEGER_TYPE || codel == ENUMERAL_TYPE)
	      && sanitize_flags_p (SANITIZE_FLOAT_CAST)))
	ಒಳ_late_ದ್ವಿಮಾನ_op = ನಿಜ;
      ವೃಕ್ಷ ret = convert_and_check (ಅಭಿವ್ಯಕ್ತಿ_loc != UNKNOWN_LOCATION
				    ? ಅಭಿವ್ಯಕ್ತಿ_loc : location, type, orig_rhs,
				    errtype == ic_init_const);
      ಒಳ_late_ದ್ವಿಮಾನ_op = save;
      ಹಿಂತಿರುಗಿ ret;
    }

  /* Aggregates in different TUs might need conversion.  */
  ಆದರೆ ((codel == ದಾಖಲೆ_TYPE || codel == UNION_TYPE)
      && codel == coder
      && comptypes (TYPE_MAIN_VARIANT (type), TYPE_MAIN_VARIANT (rhstype)))
    ಹಿಂತಿರುಗಿ convert_and_check (ಅಭಿವ್ಯಕ್ತಿ_loc != UNKNOWN_LOCATION
			      ? ಅಭಿವ್ಯಕ್ತಿ_loc : location, type, rhs);

  /* Conversion to a transparent union or record from its member types.
     This applies only to function arguments.  */
  ಆದರೆ (((codel == UNION_TYPE || codel == ದಾಖಲೆ_TYPE)
      && TYPE_TRANSPARENT_AGGR (type))
      && errtype == ic_argpass)
    {
      ವೃಕ್ಷ memb, marginal_memb = NULL_ವೃಕ್ಷ;

      ಗಾಗಿ (memb = TYPE_FIELDS (type); memb ; memb = DECL_CHAIN (memb))
	{
	  ವೃಕ್ಷ memb_type = ವೃಕ್ಷ_TYPE (memb);

	  ಆದರೆ (comptypes (TYPE_MAIN_VARIANT (memb_type),
			 TYPE_MAIN_VARIANT (rhstype)))
	    ನಿಲ್ಲಿಸು;

	  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (memb_type) != ಸೂಚಕ_TYPE)
	    ಮುಂದುವರಿ;

	  ಆದರೆ (coder == ಸೂಚಕ_TYPE)
	    {
	      ವೃಕ್ಷ ttl = ವೃಕ್ಷ_TYPE (memb_type);
	      ವೃಕ್ಷ ttr = ವೃಕ್ಷ_TYPE (rhstype);

	      /* Any non-function converts to a [const][volatile] void *
		 and vice versa; otherwise, targets must be the same.
		 Meanwhile, the lhs target must have all the qualifiers of
		 the rhs.  */
	      ಆದರೆ ((VOID_TYPE_P (ttl) && !TYPE_ATOMIC (ttl))
		  || (VOID_TYPE_P (ttr) && !TYPE_ATOMIC (ttr))
		  || comp_ಗುರಿ_types (location, memb_type, rhstype))
		{
		  ಪೂರ್ಣಾಂಕ lquals = TYPE_QUALS (ttl) & ~TYPE_QUAL_ATOMIC;
		  ಪೂರ್ಣಾಂಕ rquals = TYPE_QUALS (ttr) & ~TYPE_QUAL_ATOMIC;
		  /* If this type won't generate any warnings, use it.  */
		  ಆದರೆ (lquals == rquals
		      || ((ವೃಕ್ಷ_ಸಂಕೇತ (ttr) == FUNCTION_TYPE
			   && ವೃಕ್ಷ_ಸಂಕೇತ (ttl) == FUNCTION_TYPE)
			  ? ((lquals | rquals) == rquals)
			  : ((lquals | rquals) == lquals)))
		    ನಿಲ್ಲಿಸು;

		  /* Keep looking for a better type, but remember this one.  */
		  ಆದರೆ (!marginal_memb)
		    marginal_memb = memb;
		}
	    }

	  /* Can convert integer zero to any pointer type.  */
	  ಆದರೆ (null_ಸೂಚಕ_constant)
	    {
	      rhs = null_ಸೂಚಕ_ಗಂಟು;
	      ನಿಲ್ಲಿಸು;
	    }
	}

      ಆದರೆ (memb || marginal_memb)
	{
	  ಆದರೆ (!memb)
	    {
	      /* We have only a marginally acceptable member type;
		 it needs a warning.  */
	      ವೃಕ್ಷ ttl = ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_TYPE (marginal_memb));
	      ವೃಕ್ಷ ttr = ವೃಕ್ಷ_TYPE (rhstype);

	      /* Const and volatile mean something different for function
		 types, so the usual warnings are not appropriate.  */
	      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ttr) == FUNCTION_TYPE
		  && ವೃಕ್ಷ_ಸಂಕೇತ (ttl) == FUNCTION_TYPE)
		{
		  /* Because const and volatile on functions are
		     restrictions that say the function will not do
		     certain things, it is okay to use a const or volatile
		     function where an ordinary one is wanted, but not
		     vice-versa.  */
		  ಆದರೆ (TYPE_QUALS_NO_ADDR_SPACE (ttl)
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
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (TYPE_QUALS_NO_ADDR_SPACE (ttr)
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

	  ಆದರೆ (!fundecl || !DECL_ಒಳ_SYSTEM_ಶೀರ್ಷಿಕೆ (fundecl))
	    pedwarn (location, OPT_Wpedantic,
		     "ISO C prohibits argument conversion to union type");

	  rhs = fold_convert_loc (location, ವೃಕ್ಷ_TYPE (memb), rhs);
	  ಹಿಂತಿರುಗಿ build_constructor_single (type, memb, rhs);
	}
    }

  /* Conversions among pointers */
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ ((codel == ಸೂಚಕ_TYPE || codel == REFERENCE_TYPE)
	   && (coder == codel))
    {
      /* If RHS refers to a built-in declared without a prototype
	 BLTIN is the declaration of the built-in with a prototype
	 and RHSTYPE is set to the actual type of the built-in.  */
      ವೃಕ್ಷ bltin;
      rhstype = type_or_builtin_type (rhs, &bltin);

      ವೃಕ್ಷ ttl = ವೃಕ್ಷ_TYPE (type);
      ವೃಕ್ಷ ttr = ವೃಕ್ಷ_TYPE (rhstype);
      ತಾರ್ಕಿಕ is_opaque_ಸೂಚಕ;
      ತಾರ್ಕಿಕ ಗುರಿ_cmp = ಸುಳ್ಳು;   /* Cache comp_target_types () result.  */
      addr_space_t asl;
      addr_space_t asr;

      ವೃಕ್ಷ mvl = remove_qualifiers (ttl);
      ವೃಕ್ಷ mvr = remove_qualifiers (ttr);

      /* Opaque pointers are treated like void pointers.  */
      is_opaque_ಸೂಚಕ = ಸದಿಶ_targets_convertible_p (ttl, ttr);

      /* The Plan 9 compiler permits a pointer to a struct to be
	 automatically converted into a pointer to an anonymous field
	 within the struct.  */
      ಆದರೆ (flag_plan9_extensions
	  && ದಾಖಲೆ_OR_UNION_TYPE_P (mvl)
	  && ದಾಖಲೆ_OR_UNION_TYPE_P (mvr)
	  && mvl != mvr)
	{
	  ವೃಕ್ಷ new_rhs = convert_ಗಮ್ಯ_anonymous_ಕ್ಷೇತ್ರ (location, type, rhs);
	  ಆದರೆ (new_rhs != NULL_ವೃಕ್ಷ)
	    {
	      rhs = new_rhs;
	      rhstype = ವೃಕ್ಷ_TYPE (rhs);
	      coder = ವೃಕ್ಷ_ಸಂಕೇತ (rhstype);
	      ttr = ವೃಕ್ಷ_TYPE (rhstype);
	      mvr = TYPE_MAIN_VARIANT (ttr);
	    }
	}

      /* C++ does not allow the implicit conversion void* -> T*.  However,
	 for the purpose of reducing the number of false positives, we
	 tolerate the special case of

		int *p = NULL;

	 where NULL is typically defined in C to be '(void *) 0'.  */
      ಆದರೆ (VOID_TYPE_P (ttr) && rhs != null_ಸೂಚಕ_ಗಂಟು && !VOID_TYPE_P (ttl))
	warning_at (errtype == ic_argpass ? ಅಭಿವ್ಯಕ್ತಿ_loc : location,
		    OPT_Wc___compat,
		    "request for implicit conversion "
		    "from %qT to %qT not permitted in C++", rhstype, type);

      /* Warn of new allocations that are not big enough for the target
	 type.  */
      ಆದರೆ (warn_alloc_ಗಾತ್ರ && ವೃಕ್ಷ_ಸಂಕೇತ (rhs) == CALL_ಅಭಿವ್ಯಕ್ತಿ)
	ಆದರೆ (ವೃಕ್ಷ fndecl = get_callee_fndecl (rhs))
	  ಆದರೆ (DECL_IS_MALLOC (fndecl))
	    {
	      ವೃಕ್ಷ attrs = TYPE_ಗುಣಲಕ್ಷಣಗಳು (ವೃಕ್ಷ_TYPE (fndecl));
	      ವೃಕ್ಷ alloc_ಗಾತ್ರ = lookup_attribute ("alloc_size", attrs);
	      ಆದರೆ (alloc_ಗಾತ್ರ)
		warn_for_alloc_ಗಾತ್ರ (location, ttl, rhs, alloc_ಗಾತ್ರ);
	    }

      /* See if the pointers point to incompatible address spaces.  */
      asl = TYPE_ADDR_SPACE (ttl);
      asr = TYPE_ADDR_SPACE (ttr);
      ಆದರೆ (!null_ಸೂಚಕ_constant_p (rhs)
	  && asr != asl && !targetm.addr_space.subset_p (asr, asl))
	{
	  auto_diagnostic_ಗುಂಪು d;
	  ತಾರ್ಕಿಕ diagnosed = ನಿಜ;
	  ಆಯ್ಕೆ (errtype)
	    {
	    ಸ್ಥಿತಿ ic_argpass:
	      {
		ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ ಸಂದೇಶ_2[] = G_("passing argument %d of %qE from "
				      "pointer to non-enclosed address space");
		ಆದರೆ (warnopt)
		  diagnosed
		    = warning_at (ಅಭಿವ್ಯಕ್ತಿ_loc, warnopt, ಸಂದೇಶ_2, parmnum, rname);
		ಇಲ್ಲದಿದ್ದರೆ
		  error_at (ಅಭಿವ್ಯಕ್ತಿ_loc, ಸಂದೇಶ_2, parmnum, rname);
	      ನಿಲ್ಲಿಸು;
	      }
	    ಸ್ಥಿತಿ ic_ನಿಯೋಜಿಸು:
	      {
		ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ ಸಂದೇಶ_2[] = G_("assignment from pointer to "
				      "non-enclosed address space");
		ಆದರೆ (warnopt)
		  diagnosed = warning_at (location, warnopt, ಸಂದೇಶ_2);
		ಇಲ್ಲದಿದ್ದರೆ
		  error_at (location, ಸಂದೇಶ_2);
		ನಿಲ್ಲಿಸು;
	      }
	    ಸ್ಥಿತಿ ic_init:
	    ಸ್ಥಿತಿ ic_init_const:
	      {
		ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ ಸಂದೇಶ_2[] = G_("initialization from pointer to "
				      "non-enclosed address space");
		ಆದರೆ (warnopt)
		  diagnosed = warning_at (location, warnopt, ಸಂದೇಶ_2);
		ಇಲ್ಲದಿದ್ದರೆ
		  error_at (location, ಸಂದೇಶ_2);
		ನಿಲ್ಲಿಸು;
	      }
	    ಸ್ಥಿತಿ ic_return:
	      {
		ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ ಸಂದೇಶ_2[] = G_("return from pointer to "
				      "non-enclosed address space");
		ಆದರೆ (warnopt)
		  diagnosed = warning_at (location, warnopt, ಸಂದೇಶ_2);
		ಇಲ್ಲದಿದ್ದರೆ
		  error_at (location, ಸಂದೇಶ_2);
		ನಿಲ್ಲಿಸು;
	      }
	    ಪೂರ್ವನಿಯೋಜಿತ:
	      gcc_unreachable ();
	    }
	  ಆದರೆ (diagnosed)
	    {
	      ಆದರೆ (errtype == ic_argpass)
		inform_for_arg (fundecl, ಅಭಿವ್ಯಕ್ತಿ_loc, parmnum, type, rhstype);
	      ಇಲ್ಲದಿದ್ದರೆ
		inform (location, "expected %qT but pointer is of type %qT",
			type, rhstype);
	    }
	  ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
	}

      /* Check if the right-hand side has a format attribute but the
	 left-hand side doesn't.  */
      ಆದರೆ (warn_suggest_attribute_format
	  && check_missing_format_attribute (type, rhstype))
	{
	  ಆಯ್ಕೆ (errtype)
	  {
	  ಸ್ಥಿತಿ ic_argpass:
	    warning_at (ಅಭಿವ್ಯಕ್ತಿ_loc, OPT_Wsuggest_attribute_format,
			"argument %d of %qE might be "
			"a candidate for a format attribute",
			parmnum, rname);
	    ನಿಲ್ಲಿಸು;
	  ಸ್ಥಿತಿ ic_ನಿಯೋಜಿಸು:
	    warning_at (location, OPT_Wsuggest_attribute_format,
			"assignment left-hand side might be "
			"a candidate for a format attribute");
	    ನಿಲ್ಲಿಸು;
	  ಸ್ಥಿತಿ ic_init:
	  ಸ್ಥಿತಿ ic_init_const:
	    warning_at (location, OPT_Wsuggest_attribute_format,
			"initialization left-hand side might be "
			"a candidate for a format attribute");
	    ನಿಲ್ಲಿಸು;
	  ಸ್ಥಿತಿ ic_return:
	    warning_at (location, OPT_Wsuggest_attribute_format,
			"return type might be "
			"a candidate for a format attribute");
	    ನಿಲ್ಲಿಸು;
	  ಪೂರ್ವನಿಯೋಜಿತ:
	    gcc_unreachable ();
	  }
	}

      /* See if the pointers point to incompatible scalar storage orders.  */
      ಆದರೆ (warn_scalar_storage_ಕ್ರಮ
	  && !null_ಸೂಚಕ_constant_p (rhs)
	  && (AGGREGATE_TYPE_P (ttl) && TYPE_ಹಿಮ್ಮುಖ_STORAGE_ಕ್ರಮ (ttl))
	     != (AGGREGATE_TYPE_P (ttr) && TYPE_ಹಿಮ್ಮುಖ_STORAGE_ಕ್ರಮ (ttr)))
	{
	  ವೃಕ್ಷ t;

	  ಆಯ್ಕೆ (errtype)
	  {
	  ಸ್ಥಿತಿ ic_argpass:
	    /* Do not warn for built-in functions, for example memcpy, since we
	       control how they behave and they can be useful in this area.  */
	    ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (rname) != FUNCTION_DECL
		|| !fndecl_built_ಒಳ_p (rname))
	      warning_at (location, OPT_Wscalar_storage_ಕ್ರಮ,
			  "passing argument %d of %qE from incompatible "
			  "scalar storage order", parmnum, rname);
	    ನಿಲ್ಲಿಸು;
	  ಸ್ಥಿತಿ ic_ನಿಯೋಜಿಸು:
	    /* Do not warn if the RHS is a call to a function that returns a
	       pointer that is not an alias.  */
	    ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (rhs) != CALL_ಅಭಿವ್ಯಕ್ತಿ
		|| (t = get_callee_fndecl (rhs)) == NULL_ವೃಕ್ಷ
		|| !DECL_IS_MALLOC (t))
	      warning_at (location, OPT_Wscalar_storage_ಕ್ರಮ,
			  "assignment to %qT from pointer type %qT with "
			  "incompatible scalar storage order", type, rhstype);
	    ನಿಲ್ಲಿಸು;
	  ಸ್ಥಿತಿ ic_init:
	  ಸ್ಥಿತಿ ic_init_const:
	    /* Likewise.  */
	    ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (rhs) != CALL_ಅಭಿವ್ಯಕ್ತಿ
		|| (t = get_callee_fndecl (rhs)) == NULL_ವೃಕ್ಷ
		|| !DECL_IS_MALLOC (t))
	      warning_at (location, OPT_Wscalar_storage_ಕ್ರಮ,
			  "initialization of %qT from pointer type %qT with "
			  "incompatible scalar storage order", type, rhstype);
	    ನಿಲ್ಲಿಸು;
	  ಸ್ಥಿತಿ ic_return:
	    warning_at (location, OPT_Wscalar_storage_ಕ್ರಮ,
			"returning %qT from pointer type with incompatible "
			"scalar storage order %qT", rhstype, type);
	    ನಿಲ್ಲಿಸು;
	  ಪೂರ್ವನಿಯೋಜಿತ:
	    gcc_unreachable ();
	  }
	}

      /* Any non-function converts to a [const][volatile] void *
	 and vice versa; otherwise, targets must be the same.
	 Meanwhile, the lhs target must have all the qualifiers of the rhs.  */
      ಆದರೆ ((VOID_TYPE_P (ttl) && !TYPE_ATOMIC (ttl))
	  || (VOID_TYPE_P (ttr) && !TYPE_ATOMIC (ttr))
	  || (ಗುರಿ_cmp = comp_ಗುರಿ_types (location, type, rhstype))
	  || is_opaque_ಸೂಚಕ
	  || ((c_common_unsigned_type (mvl)
	       == c_common_unsigned_type (mvr))
	      && (c_common_signed_type (mvl)
		  == c_common_signed_type (mvr))
	      && TYPE_ATOMIC (mvl) == TYPE_ATOMIC (mvr)))
	{
	  /* Warn about loss of qualifers from pointers to arrays with
	     qualifiers on the element type. */
	  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ttr) == ARRAY_TYPE)
	    {
	      ttr = strip_array_types (ttr);
	      ttl = strip_array_types (ttl);

	      ಆದರೆ (TYPE_QUALS_NO_ADDR_SPACE_NO_ATOMIC (ttr)
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
          ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (pedantic
	      && ((VOID_TYPE_P (ttl) && ವೃಕ್ಷ_ಸಂಕೇತ (ttr) == FUNCTION_TYPE)
		  ||
		  (VOID_TYPE_P (ttr)
		   && !null_ಸೂಚಕ_constant
		   && ವೃಕ್ಷ_ಸಂಕೇತ (ttl) == FUNCTION_TYPE)))
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
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ttr) != FUNCTION_TYPE
		   && ವೃಕ್ಷ_ಸಂಕೇತ (ttl) != FUNCTION_TYPE)
	    {
	       /* Assignments between atomic and non-atomic objects are OK.  */
	       ತಾರ್ಕಿಕ warn_quals_ped = TYPE_QUALS_NO_ADDR_SPACE_NO_ATOMIC (ttr)
				     & ~TYPE_QUALS_NO_ADDR_SPACE_NO_ATOMIC (ttl);
	       ತಾರ್ಕಿಕ warn_quals = TYPE_QUALS_NO_ADDR_SPACE_NO_ATOMIC (ttr)
				 & ~TYPE_QUALS_NO_ADDR_SPACE_NO_ATOMIC (strip_array_types (ttl));

	      /* Don't warn about loss of qualifier for conversions from
		 qualified void* to pointers to arrays with corresponding
		 qualifier on the element type (except for pedantic before C23). */
	      ಆದರೆ (warn_quals || (warn_quals_ped && pedantic && !flag_isoc23))
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
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (warn_quals_ped)
		pedwarn_c11 (location, OPT_Wc11_c23_compat,
			     "array with qualifier on the element is not qualified before C23");

	      /* If this is not a case of ignoring a mismatch in signedness,
		 no warning.  */
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (VOID_TYPE_P (ttl) || VOID_TYPE_P (ttr)
		       || ಗುರಿ_cmp)
		;
	      /* If there is a mismatch, do warn.  */
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (warn_ಸೂಚಕ_sign)
		ಆಯ್ಕೆ (errtype)
		  {
		  ಸ್ಥಿತಿ ic_argpass:
		    {
		      auto_diagnostic_ಗುಂಪು d;
		      range_label_for_type_mismatch rhs_label (rhstype, type);
		      gcc_rich_location richloc (ಅಭಿವ್ಯಕ್ತಿ_loc, &rhs_label,
						 highlight_colors::actual);
		      ಆದರೆ (pedwarn (&richloc, OPT_Wpointer_sign,
				   "pointer targets in passing argument %d of "
				   "%qE differ in signedness", parmnum, rname))
			inform_for_arg (fundecl, ಅಭಿವ್ಯಕ್ತಿ_loc, parmnum, type,
					rhstype);
		    }
		    ನಿಲ್ಲಿಸು;
		  ಸ್ಥಿತಿ ic_ನಿಯೋಜಿಸು:
		    pedwarn (location, OPT_Wpointer_sign,
			     "pointer targets in assignment from %qT to %qT "
			     "differ in signedness", rhstype, type);
		    ನಿಲ್ಲಿಸು;
		  ಸ್ಥಿತಿ ic_init:
		  ಸ್ಥಿತಿ ic_init_const:
		    pedwarn_init (location, OPT_Wpointer_sign,
				  "pointer targets in initialization of %qT "
				  "from %qT differ in signedness", type,
				  rhstype);
		    ನಿಲ್ಲಿಸು;
		  ಸ್ಥಿತಿ ic_return:
		    pedwarn (location, OPT_Wpointer_sign, "pointer targets in "
			     "returning %qT from a function with return type "
			     "%qT differ in signedness", rhstype, type);
		    ನಿಲ್ಲಿಸು;
		  ಪೂರ್ವನಿಯೋಜಿತ:
		    gcc_unreachable ();
		  }
	    }
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ttl) == FUNCTION_TYPE
		   && ವೃಕ್ಷ_ಸಂಕೇತ (ttr) == FUNCTION_TYPE)
	    {
	      /* Because const and volatile on functions are restrictions
		 that say the function will not do certain things,
		 it is okay to use a const or volatile function
		 where an ordinary one is wanted, but not vice-versa.  */
	      ಆದರೆ (TYPE_QUALS_NO_ADDR_SPACE (ttl)
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
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!objc_ok)
	{
	  auto_diagnostic_ಗುಂಪು d;
	  ತಾರ್ಕಿಕ warned = ಸುಳ್ಳು;
	  pp_markup::element_expected_type e_type (type);
	  pp_markup::element_actual_type e_rhstype (rhstype);
	  ಆಯ್ಕೆ (errtype)
	    {
	    ಸ್ಥಿತಿ ic_argpass:
	      {
		range_label_for_type_mismatch rhs_label (rhstype, type);
		gcc_rich_location richloc (ಅಭಿವ್ಯಕ್ತಿ_loc, &rhs_label,
					   highlight_colors::actual);
		warned
		  = permerror_opt (&richloc, OPT_Wincompatible_ಸೂಚಕ_types,
				   "passing argument %d of %qE from "
				   "incompatible pointer type",
				   parmnum, rname);
		ಆದರೆ (warned)
		  inform_for_arg (fundecl, ಅಭಿವ್ಯಕ್ತಿ_loc, parmnum, type, rhstype);
	      }
	      ನಿಲ್ಲಿಸು;
	    ಸ್ಥಿತಿ ic_ನಿಯೋಜಿಸು:
	      ಆದರೆ (bltin)
		warned
		  = permerror_opt (location, OPT_Wincompatible_ಸೂಚಕ_types,
				   "assignment to %e from pointer to "
				   "%qD with incompatible type %e",
				   &e_type, bltin, &e_rhstype);
	      ಇಲ್ಲದಿದ್ದರೆ
		warned
		  = permerror_opt (location, OPT_Wincompatible_ಸೂಚಕ_types,
				   "assignment to %e from incompatible "
				   "pointer type %e",
				   &e_type, &e_rhstype);
	      ನಿಲ್ಲಿಸು;
	    ಸ್ಥಿತಿ ic_init:
	    ಸ್ಥಿತಿ ic_init_const:
	      ಆದರೆ (bltin)
		warned
		  = permerror_init (location, OPT_Wincompatible_ಸೂಚಕ_types,
				    "initialization of %e from pointer to "
				    "%qD with incompatible type %e",
				    &e_type, bltin, &e_rhstype);
	      ಇಲ್ಲದಿದ್ದರೆ
		warned
		  = permerror_init (location, OPT_Wincompatible_ಸೂಚಕ_types,
				    "initialization of %e from incompatible "
				    "pointer type %e",
				    &e_type, &e_rhstype);
	      ನಿಲ್ಲಿಸು;
	    ಸ್ಥಿತಿ ic_return:
	      ಆದರೆ (bltin)
		warned
		  = permerror_opt (location, OPT_Wincompatible_ಸೂಚಕ_types,
				   "returning pointer to %qD of type %e from "
				   "a function with incompatible type %e",
				   bltin, &e_rhstype, &e_type);
	      ಇಲ್ಲದಿದ್ದರೆ
		warned
		  = permerror_opt (location, OPT_Wincompatible_ಸೂಚಕ_types,
				   "returning %e from a function with "
				   "incompatible return type %e",
				   &e_rhstype, &e_type);
	      ನಿಲ್ಲಿಸು;
	    ಪೂರ್ವನಿಯೋಜಿತ:
	      gcc_unreachable ();
	    }
	  ಆದರೆ (warned)
	    {
	      /* If the mismatching function type is a pointer to a function,
		 try to show the decl of the function.  */
	      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (rhs) == ADDR_ಅಭಿವ್ಯಕ್ತಿ
		  && ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (rhs, 0)) == FUNCTION_DECL)
		{
		  ವೃಕ್ಷ rhs_fndecl = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (rhs, 0);
		  ಆದರೆ (!DECL_IS_UNDECLARED_BUILTIN (rhs_fndecl))
		    {
		      gcc_rich_location richloc
			(DECL_ಮೂಲ_LOCATION (rhs_fndecl), ಶೂನ್ಯಸೂಚಕ,
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
      warn_for_ವಿಳಾಸ_ದ_packed_member (type, orig_rhs);

      ಹಿಂತಿರುಗಿ convert (type, rhs);
    }
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (codel == ಸೂಚಕ_TYPE && coder == ARRAY_TYPE)
    {
      /* ??? This should not be an error when inlining calls to
	 unprototyped functions.  */
      ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ ಸಂದೇಶ_2[] = "invalid use of non-lvalue array";
      ಆದರೆ (warnopt)
	warning_at (location, warnopt, ಸಂದೇಶ_2);
      ಇಲ್ಲದಿದ್ದರೆ
	error_at (location, ಸಂದೇಶ_2);
      ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
    }
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (codel == ಸೂಚಕ_TYPE
	   && (coder == INTEGER_TYPE
	       || coder == ENUMERAL_TYPE
	       || coder == BOOLEAN_TYPE
	       || coder == NULLPTR_TYPE
	       || coder == BITINT_TYPE))
    {
      ಆದರೆ (null_ಸೂಚಕ_constant && c_inhibit_evaluation_warnings == 0
	  && coder != NULLPTR_TYPE)
	warning_at (location, OPT_Wzero_as_null_ಸೂಚಕ_constant,
		    "zero as null pointer constant");
      /* A NULLPTR type is just a nullptr always.  */
      ಆದರೆ (coder == NULLPTR_TYPE)
	ಹಿಂತಿರುಗಿ omit_one_ಕಾರ್ಯಾಂಶ_loc (ಅಭಿವ್ಯಕ್ತಿ_loc, type, nullptr_ಗಂಟು, rhs);
      /* An explicit constant 0 or type nullptr_t can convert to a pointer,
	 or one that results from arithmetic, even including a cast to
	 integer type.  */
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!null_ಸೂಚಕ_constant)
	ಆಯ್ಕೆ (errtype)
	  {
	  ಸ್ಥಿತಿ ic_argpass:
	    {
	      auto_diagnostic_ಗುಂಪು d;
	      range_label_for_type_mismatch rhs_label (rhstype, type);
	      gcc_rich_location richloc (ಅಭಿವ್ಯಕ್ತಿ_loc, &rhs_label,
					 highlight_colors::actual);
	      ಆದರೆ (permerror_opt (&richloc, OPT_Wint_conversion,
				 "passing argument %d of %qE makes pointer "
				 "from integer without a cast", parmnum, rname))
		{
		  maybe_emit_indirection_note (ಅಭಿವ್ಯಕ್ತಿ_loc, rhs, type);
		  inform_for_arg (fundecl, ಅಭಿವ್ಯಕ್ತಿ_loc, parmnum, type, rhstype);
		}
	    }
	    ನಿಲ್ಲಿಸು;
	  ಸ್ಥಿತಿ ic_ನಿಯೋಜಿಸು:
	    permerror_opt (location, OPT_Wint_conversion,
			   "assignment to %qT from %qT makes pointer from "
			   "integer without a cast", type, rhstype);
	    ನಿಲ್ಲಿಸು;
	  ಸ್ಥಿತಿ ic_init:
	  ಸ್ಥಿತಿ ic_init_const:
	    permerror_init (location, OPT_Wint_conversion,
			    "initialization of %qT from %qT makes pointer "
			    "from integer without a cast", type, rhstype);
	    ನಿಲ್ಲಿಸು;
	  ಸ್ಥಿತಿ ic_return:
	    permerror_init (location, OPT_Wint_conversion,
			    "returning %qT from a function with return type "
			    "%qT makes pointer from integer without a cast",
			    rhstype, type);
	    ನಿಲ್ಲಿಸು;
	  ಪೂರ್ವನಿಯೋಜಿತ:
	    gcc_unreachable ();
	  }

      ಹಿಂತಿರುಗಿ convert (type, rhs);
    }
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ ((codel == INTEGER_TYPE || codel == BITINT_TYPE)
	   && coder == ಸೂಚಕ_TYPE)
    {
      ಆಯ್ಕೆ (errtype)
	{
	ಸ್ಥಿತಿ ic_argpass:
	  {
	    auto_diagnostic_ಗುಂಪು d;
	    range_label_for_type_mismatch rhs_label (rhstype, type);
	    gcc_rich_location richloc (ಅಭಿವ್ಯಕ್ತಿ_loc, &rhs_label,
				       highlight_colors::actual);
	    ಆದರೆ (permerror_opt (&richloc, OPT_Wint_conversion,
			       "passing argument %d of %qE makes integer from "
			       "pointer without a cast", parmnum, rname))
	      {
		maybe_emit_indirection_note (ಅಭಿವ್ಯಕ್ತಿ_loc, rhs, type);
		inform_for_arg (fundecl, ಅಭಿವ್ಯಕ್ತಿ_loc, parmnum, type, rhstype);
	      }
	  }
	  ನಿಲ್ಲಿಸು;
	ಸ್ಥಿತಿ ic_ನಿಯೋಜಿಸು:
	  permerror_opt (location, OPT_Wint_conversion,
			 "assignment to %qT from %qT makes integer from "
			 "pointer without a cast", type, rhstype);
	  ನಿಲ್ಲಿಸು;
	ಸ್ಥಿತಿ ic_init:
	ಸ್ಥಿತಿ ic_init_const:
	  permerror_init (location, OPT_Wint_conversion,
			  "initialization of %qT from %qT makes integer "
			  "from pointer without a cast", type, rhstype);
	  ನಿಲ್ಲಿಸು;
	ಸ್ಥಿತಿ ic_return:
	  permerror_opt (location, OPT_Wint_conversion, "returning %qT from a "
			 "function with return type %qT makes integer from "
			 "pointer without a cast", rhstype, type);
	  ನಿಲ್ಲಿಸು;
	ಪೂರ್ವನಿಯೋಜಿತ:
	  gcc_unreachable ();
	}

      ಹಿಂತಿರುಗಿ convert (type, rhs);
    }
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (C_BOOLEAN_TYPE_P (type)
	   /* The type nullptr_t may be converted to bool.  The
	      result is false.  */
	   && (coder == ಸೂಚಕ_TYPE || coder == NULLPTR_TYPE))
    {
      ವೃಕ್ಷ ret;
      ತಾರ್ಕಿಕ save = ಒಳ_late_ದ್ವಿಮಾನ_op;
      ಒಳ_late_ದ್ವಿಮಾನ_op = ನಿಜ;
      ret = convert (type, rhs);
      ಒಳ_late_ದ್ವಿಮಾನ_op = save;
      ಹಿಂತಿರುಗಿ ret;
    }
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (codel == NULLPTR_TYPE && null_ಸೂಚಕ_constant)
    ಹಿಂತಿರುಗಿ convert (type, rhs);

  ಆಯ್ಕೆ (errtype)
    {
    ಸ್ಥಿತಿ ic_argpass:
      {
	auto_diagnostic_ಗುಂಪು d;
	range_label_for_type_mismatch rhs_label (rhstype, type);
	gcc_rich_location richloc (ಅಭಿವ್ಯಕ್ತಿ_loc, &rhs_label,
				   highlight_colors::actual);
	ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ ಸಂದೇಶ_2[] = G_("incompatible type for argument %d of %qE");
	ಆದರೆ (warnopt)
	  warning_at (ಅಭಿವ್ಯಕ್ತಿ_loc, warnopt, ಸಂದೇಶ_2, parmnum, rname);
	ಇಲ್ಲದಿದ್ದರೆ
	  error_at (&richloc, ಸಂದೇಶ_2, parmnum, rname);
	inform_for_arg (fundecl, ಅಭಿವ್ಯಕ್ತಿ_loc, parmnum, type, rhstype);
      }
      ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ ic_ನಿಯೋಜಿಸು:
      {
	ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ ಸಂದೇಶ_2[]
	  = G_("incompatible types when assigning to type %qT from type %qT");
	ಆದರೆ (warnopt)
	  warning_at (ಅಭಿವ್ಯಕ್ತಿ_loc, 0, ಸಂದೇಶ_2, type, rhstype);
	ಇಲ್ಲದಿದ್ದರೆ
	  error_at (ಅಭಿವ್ಯಕ್ತಿ_loc, ಸಂದೇಶ_2, type, rhstype);
	ನಿಲ್ಲಿಸು;
      }
    ಸ್ಥಿತಿ ic_init:
    ಸ್ಥಿತಿ ic_init_const:
      {
	ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ ಸಂದೇಶ_2[]
	  = G_("incompatible types when initializing type %qT using type %qT");
	ಆದರೆ (warnopt)
	  warning_at (location, 0, ಸಂದೇಶ_2, type, rhstype);
	ಇಲ್ಲದಿದ್ದರೆ
	  error_at (location, ಸಂದೇಶ_2, type, rhstype);
	ನಿಲ್ಲಿಸು;
      }
    ಸ್ಥಿತಿ ic_return:
      {
	ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ ಸಂದೇಶ_2[]
	  = G_("incompatible types when returning type %qT but %qT was expected");
	ಆದರೆ (warnopt)
	  warning_at (location, 0, ಸಂದೇಶ_2, rhstype, type);
	ಇಲ್ಲದಿದ್ದರೆ
	  error_at (location, ಸಂದೇಶ_2, rhstype, type);
	ನಿಲ್ಲಿಸು;
      }
    ಪೂರ್ವನಿಯೋಜಿತ:
      gcc_unreachable ();
    }

  ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
}

/* If VALUE is a compound expr all of whose expressions are constant, then
   return its value.  Otherwise, return error_mark_node.

   This is for handling COMPOUND_EXPRs as initializer elements
   which is allowed with a warning when -pedantic is specified.  */

ಸ್ಥಿರ ವೃಕ್ಷ
valid_compound_ಅಭಿವ್ಯಕ್ತಿ_initializer (ವೃಕ್ಷ ಮೌಲ್ಯ, ವೃಕ್ಷ endtype)
{
  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ಮೌಲ್ಯ) == COMPOUND_ಅಭಿವ್ಯಕ್ತಿ)
    {
      ಆದರೆ (valid_compound_ಅಭಿವ್ಯಕ್ತಿ_initializer (ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (ಮೌಲ್ಯ, 0), endtype)
	  == error_mark_ಗಂಟು)
	ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
      ಹಿಂತಿರುಗಿ valid_compound_ಅಭಿವ್ಯಕ್ತಿ_initializer (ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (ಮೌಲ್ಯ, 1),
					      endtype);
    }
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!initializer_constant_valid_p (ಮೌಲ್ಯ, endtype))
    ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
  ಇಲ್ಲದಿದ್ದರೆ
    ಹಿಂತಿರುಗಿ ಮೌಲ್ಯ;
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
  ತಾರ್ಕಿಕ npc = ಸುಳ್ಳು;
  ತಾರ್ಕಿಕ int_const_ಅಭಿವ್ಯಕ್ತಿ = ಸುಳ್ಳು;
  ತಾರ್ಕಿಕ arith_const_ಅಭಿವ್ಯಕ್ತಿ = ಸುಳ್ಳು;

  /* If variable's type was invalidly declared, just ignore it.  */

  type = ವೃಕ್ಷ_TYPE (decl);
  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (type) == ERROR_MARK)
    ಹಿಂತಿರುಗಿ;

  /* Digest the specified initializer into an expression.  */

  ಆದರೆ (init)
    {
      npc = null_ಸೂಚಕ_constant_p (init);
      int_const_ಅಭಿವ್ಯಕ್ತಿ = (ವೃಕ್ಷ_ಸಂಕೇತ (init) == INTEGER_CST
			&& !ವೃಕ್ಷ_ಅತಿಪ್ರವಾಹ (init)
			&& INTEGRAL_TYPE_P (ವೃಕ್ಷ_TYPE (init)));
      /* Not fully determined before folding.  */
      arith_const_ಅಭಿವ್ಯಕ್ತಿ = ನಿಜ;
    }
  ತಾರ್ಕಿಕ constexpr_p = (VAR_P (decl)
		      && C_DECL_DECLARED_CONSTEXPR (decl));
  ಮೌಲ್ಯ = digest_init (init_loc, decl, type, init, origtype, npc,
		       int_const_ಅಭಿವ್ಯಕ್ತಿ, arith_const_ಅಭಿವ್ಯಕ್ತಿ, ನಿಜ,
		       ವೃಕ್ಷ_STATIC (decl) || constexpr_p, constexpr_p);

  /* Store the expression if valid; else report error.  */

  ಆದರೆ (!ಒಳ_system_ಶೀರ್ಷಿಕೆ_at (ಒಳಹರಿವು_location)
      && AGGREGATE_TYPE_P (ವೃಕ್ಷ_TYPE (decl)) && !ವೃಕ್ಷ_STATIC (decl))
    warning (OPT_Wtraditional, "traditional C rejects automatic "
	     "aggregate initialization");

  ಆದರೆ (ಮೌಲ್ಯ != error_mark_ಗಂಟು || ವೃಕ್ಷ_ಸಂಕೇತ (decl) != FUNCTION_DECL)
    DECL_INITIAL (decl) = ಮೌಲ್ಯ;

  /* ANSI wants warnings about out-of-range constant initializers.  */
  STRIP_TYPE_NOPS (ಮೌಲ್ಯ);
  ಆದರೆ (ವೃಕ್ಷ_STATIC (decl))
    constant_ಅಭಿವ್ಯಕ್ತಿ_warning (ಮೌಲ್ಯ);

  /* Check if we need to set array size from compound literal size.  */
  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (type) == ARRAY_TYPE
      && TYPE_DOMAIN (type) == NULL_ವೃಕ್ಷ
      && ಮೌಲ್ಯ != error_mark_ಗಂಟು)
    {
      ವೃಕ್ಷ inside_init = init;

      STRIP_TYPE_NOPS (inside_init);
      inside_init = fold (inside_init);

      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (inside_init) == COMPOUND_LITERAL_ಅಭಿವ್ಯಕ್ತಿ)
	{
	  ವೃಕ್ಷ cldecl = COMPOUND_LITERAL_ಅಭಿವ್ಯಕ್ತಿ_DECL (inside_init);

	  ಆದರೆ (TYPE_DOMAIN (ವೃಕ್ಷ_TYPE (cldecl)))
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

ರಚನೆ spelling
{
  ಪೂರ್ಣಾಂಕ ಬಗೆ;
  ಒಕ್ಕೂಟ
    {
      ಚಿಹ್ನೆರಹಿತ HOST_WIDE_INT i;
      ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *s;
    } u;
};

#ವ್ಯಾಖ್ಯಾನಿಸು SPELLING_STRING 1
#ವ್ಯಾಖ್ಯಾನಿಸು SPELLING_MEMBER 2
#ವ್ಯಾಖ್ಯಾನಿಸು SPELLING_BOUNDS 3

ಸ್ಥಿರ ರಚನೆ spelling *spelling;	/* Next stack element (unused).  */
ಸ್ಥಿರ ರಚನೆ spelling *spelling_ತಳ;	/* Spelling stack base.  */
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ spelling_ಗಾತ್ರ;		/* Size of the spelling stack.  */

/* Macros to save and restore the spelling stack around push_... functions.
   Alternative to SAVE_SPELLING_STACK.  */

#ವ್ಯಾಖ್ಯಾನಿಸು SPELLING_ಆಳ() (spelling - spelling_ತಳ)
#ವ್ಯಾಖ್ಯಾನಿಸು RESTORE_SPELLING_ಆಳ(ಆಳ_2) (spelling = spelling_ತಳ + (ಆಳ_2))

/* Push an element on the spelling stack with type KIND and assign VALUE
   to MEMBER.  */

#ವ್ಯಾಖ್ಯಾನಿಸು ತಳ್ಳು_SPELLING(ಬಗೆ_2, ಮೌಲ್ಯ_2, MEMBER)				\
{									\
  ಪೂರ್ಣಾಂಕ ಆಳ = SPELLING_ಆಳ ();					\
									\
  ಆದರೆ (ಆಳ >= spelling_ಗಾತ್ರ)						\
    {									\
      spelling_ಗಾತ್ರ += 10;						\
      spelling_ತಳ = XRESIZEVEC (ರಚನೆ spelling, spelling_ತಳ,	\
				  spelling_ಗಾತ್ರ);			\
      RESTORE_SPELLING_ಆಳ (ಆಳ);					\
    }									\
									\
  spelling->ಬಗೆ = (ಬಗೆ_2);						\
  spelling->MEMBER = (ಮೌಲ್ಯ_2);						\
  spelling++;								\
}

/* Push STRING on the stack.  Printed literally.  */

ಸ್ಥಿರ ಶೂನ್ಯ
ತಳ್ಳು_string (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *string)
{
  ತಳ್ಳು_SPELLING (SPELLING_STRING, string, u.s);
}

/* Push a member name on the stack.  Printed as '.' STRING.  */

ಸ್ಥಿರ ಶೂನ್ಯ
ತಳ್ಳು_member_name (ವೃಕ್ಷ decl)
{
  ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಸ್ಥಿರಾಂಕ string
    = (DECL_NAME (decl)
       ? identifier_ಗಮ್ಯ_locale (IDENTIFIER_ಸೂಚಕ (DECL_NAME (decl)))
       : _("<anonymous>"));
  ತಳ್ಳು_SPELLING (SPELLING_MEMBER, string, u.s);
}

/* Push an array bounds on the stack.  Printed as [BOUNDS].  */

ಸ್ಥಿರ ಶೂನ್ಯ
ತಳ್ಳು_array_bounds (ಚಿಹ್ನೆರಹಿತ HOST_WIDE_INT bounds)
{
  ತಳ್ಳು_SPELLING (SPELLING_BOUNDS, bounds, u.i);
}

/* Compute the maximum size in bytes of the printed spelling.  */

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ
spelling_ಉದ್ದಳತೆ (ಶೂನ್ಯ)
{
  ಪೂರ್ಣಾಂಕ ಗಾತ್ರ_2 = 0;
  ರಚನೆ spelling *p;

  ಗಾಗಿ (p = spelling_ತಳ; p < spelling; p++)
    {
      ಆದರೆ (p->ಬಗೆ == SPELLING_BOUNDS)
	ಗಾತ್ರ_2 += 25;
      ಇಲ್ಲದಿದ್ದರೆ
	ಗಾತ್ರ_2 += ಅಕ್ಷರಸರಣಿ_ಉದ್ದ (p->u.s) + 1;
    }

  ಹಿಂತಿರುಗಿ ಗಾತ್ರ_2;
}

/* Print the spelling to BUFFER and return it.  */

ಸ್ಥಿರ ಅಕ್ಷರ *
print_spelling (ಅಕ್ಷರ *ಬಫರ್)
{
  ಅಕ್ಷರ *d = ಬಫರ್;
  ರಚನೆ spelling *p;

  ಗಾಗಿ (p = spelling_ತಳ; p < spelling; p++)
    ಆದರೆ (p->ಬಗೆ == SPELLING_BOUNDS)
      {
	sprintf (d, "[" HOST_WIDE_INT_PRINT_UNSIGNED "]", p->u.i);
	d += ಅಕ್ಷರಸರಣಿ_ಉದ್ದ (d);
      }
    ಇಲ್ಲದಿದ್ದರೆ
      {
	ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *s;
	ಆದರೆ (p->ಬಗೆ == SPELLING_MEMBER)
	  *d++ = '.';
	ಗಾಗಿ (s = p->u.s; (*d = *s++); d++)
	  ;
      }
  *d++ = '\0';
  ಹಿಂತಿರುಗಿ ಬಫರ್;
}

/* Check whether INIT, a floating or integer constant, is
   representable in TYPE, a real floating type with the same radix or
   a decimal floating type initialized with a binary floating
   constant.  Return true if OK, false if not.  */
ಸ್ಥಿರ ತಾರ್ಕಿಕ
constexpr_init_ಹೊಂದುತ್ತದೆ_real_type (ವೃಕ್ಷ type, ವೃಕ್ಷ init)
{
  gcc_assert (SCALAR_FLOAT_TYPE_P (type));
  gcc_assert (ವೃಕ್ಷ_ಸಂಕೇತ (init) == INTEGER_CST || ವೃಕ್ಷ_ಸಂಕೇತ (init) == REAL_CST);
  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (init) == REAL_CST
      && TYPE_ಬಹುಲಕ (ವೃಕ್ಷ_TYPE (init)) == TYPE_ಬಹುಲಕ (type))
    {
      /* Same mode, no conversion required except for the case of
	 signaling NaNs if the types are incompatible (e.g. double and
	 long double with the same mode).  */
      ಆದರೆ (REAL_ಮೌಲ್ಯ_ISSIGNALING_NAN (ವೃಕ್ಷ_REAL_CST (init))
	  && !comptypes (TYPE_MAIN_VARIANT (type),
			 TYPE_MAIN_VARIANT (ವೃಕ್ಷ_TYPE (init))))
	ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
      ಹಿಂತಿರುಗಿ ನಿಜ;
    }
  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (init) == INTEGER_CST)
    {
      ವೃಕ್ಷ converted = build_real_from_int_cst (type, init);
      ತಾರ್ಕಿಕ fail = ಸುಳ್ಳು;
      wide_int w = real_ಗಮ್ಯ_integer (&ವೃಕ್ಷ_REAL_CST (converted), &fail,
				    TYPE_PRECISION (ವೃಕ್ಷ_TYPE (init)));
      ಹಿಂತಿರುಗಿ !fail && wi::eq_p (w, wi::ಗಮ್ಯ_wide (init));
    }
  ಆದರೆ (REAL_ಮೌಲ್ಯ_ISSIGNALING_NAN (ವೃಕ್ಷ_REAL_CST (init)))
    ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
  ಆದರೆ ((REAL_ಮೌಲ್ಯ_ISINF (ವೃಕ್ಷ_REAL_CST (init))
       && ಬಹುಲಕ_HAS_INFINITIES (TYPE_ಬಹುಲಕ (type)))
      || (REAL_ಮೌಲ್ಯ_ISNAN (ವೃಕ್ಷ_REAL_CST (init))
	  && ಬಹುಲಕ_HAS_NANS (TYPE_ಬಹುಲಕ (type))))
    ಹಿಂತಿರುಗಿ ನಿಜ;
  ಆದರೆ (DECIMAL_FLOAT_TYPE_P (type)
      && !DECIMAL_FLOAT_TYPE_P (ವೃಕ್ಷ_TYPE (init)))
    {
      /* This is valid if the real number represented by the
	 initializer can be exactly represented in the decimal
	 type.  Compare the values using MPFR.  */
      REAL_ಮೌಲ್ಯ_TYPE t;
      real_convert (&t, TYPE_ಬಹುಲಕ (type), &ವೃಕ್ಷ_REAL_CST (init));
      mpfr_t bin_val, dec_val;
      mpfr_init2 (bin_val, REAL_ಬಹುಲಕ_FORMAT (TYPE_ಬಹುಲಕ (ವೃಕ್ಷ_TYPE (init)))->p);
      mpfr_init2 (dec_val, REAL_ಬಹುಲಕ_FORMAT (TYPE_ಬಹುಲಕ (ವೃಕ್ಷ_TYPE (init)))->p);
      mpfr_from_real (bin_val, &ವೃಕ್ಷ_REAL_CST (init), MPFR_RNDN);
      ಅಕ್ಷರ string[256];
      real_ಗಮ್ಯ_decimal (string, &t, ಗಾತ್ರ string, 0, 1);
      ತಾರ್ಕಿಕ res = (mpfr_strtofr (dec_val, string, ಖಾಲಿ, 10, MPFR_RNDN) == 0
		  && mpfr_equal_p (bin_val, dec_val));
      mpfr_clear (bin_val);
      mpfr_clear (dec_val);
      ಹಿಂತಿರುಗಿ res;
    }
  /* exact_real_truncate is not quite right here, since it doesn't
     allow even an exact conversion to subnormal values.  */
  REAL_ಮೌಲ್ಯ_TYPE t;
  real_convert (&t, TYPE_ಬಹುಲಕ (type), &ವೃಕ್ಷ_REAL_CST (init));
  ಹಿಂತಿರುಗಿ real_identical (&t, &ವೃಕ್ಷ_REAL_CST (init));
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
  ಆದರೆ (ಸೂಚಕ_TYPE_P (type))
    {
      /* The initializer must be null.  */
      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (init) != INTEGER_CST || !integer_zerop (init))
	error_at (loc, "%<constexpr%> pointer initializer is not null");
      ಹಿಂತಿರುಗಿ;
    }
  ಆದರೆ (INTEGRAL_TYPE_P (type))
    {
      /* The initializer must be an integer constant expression,
	 representable in the target type.  */
      ಆದರೆ (!int_const_ಅಭಿವ್ಯಕ್ತಿ)
	{
	  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (init) == RAW_ದತ್ತಾಂಶ_CST
	      && TYPE_PRECISION (type) == CHAR_ಬಿಟ್)
	    {
	      ಆದರೆ (!TYPE_UNSIGNED (type))
		ಗಾಗಿ (ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ i = 0;
		     i < (ಚಿಹ್ನೆರಹಿತ) RAW_ದತ್ತಾಂಶ_ಉದ್ದಳತೆ (init); ++i)
		  ಆದರೆ (RAW_ದತ್ತಾಂಶ_SCHAR_ELT (init, i) < 0)
		    {
		      error_at (loc, "%<constexpr%> initializer not "
				"representable in type of object");
		      ನಿಲ್ಲಿಸು;
		    }
	    }
	  ಇಲ್ಲದಿದ್ದರೆ
	    error_at (loc, "%<constexpr%> integer initializer is not an "
		      "integer constant expression");
	}
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!int_ಹೊಂದುತ್ತದೆ_type_p (init, type))
	error_at (loc, "%<constexpr%> initializer not representable in "
		  "type of object");
      ಹಿಂತಿರುಗಿ;
    }
  /* We don't apply any extra checks to extension types such as vector
     or fixed-point types.  */
  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (type) != REAL_TYPE && ವೃಕ್ಷ_ಸಂಕೇತ (type) != COMPLEX_TYPE)
    ಹಿಂತಿರುಗಿ;
  ಆದರೆ (!arith_const_ಅಭಿವ್ಯಕ್ತಿ)
    {
      error_at (loc, "%<constexpr%> initializer is not an arithmetic "
		"constant expression");
      ಹಿಂತಿರುಗಿ;
    }
  /* We don't apply any extra checks to complex integers.  */
  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (type) == COMPLEX_TYPE
      && ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (type)) != REAL_TYPE)
    ಹಿಂತಿರುಗಿ;
  /* Following N3082, a real type cannot be initialized from a complex
     type and a binary type cannot be initialized from a decimal type
     (but initializing a decimal type from a binary type is OK).
     Signaling NaN initializers are OK only if the types are
     compatible (not just the same mode); all quiet NaN and infinity
     initializations are considered to preserve the value.  */
  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (init)) == COMPLEX_TYPE
      && SCALAR_FLOAT_TYPE_P (type))
    {
      error_at (loc, "%<constexpr%> initializer for a real type is of "
		"complex type");
      ಹಿಂತಿರುಗಿ;
    }
  ಆದರೆ (SCALAR_FLOAT_TYPE_P (type)
      && SCALAR_FLOAT_TYPE_P (ವೃಕ್ಷ_TYPE (init))
      && DECIMAL_FLOAT_TYPE_P (ವೃಕ್ಷ_TYPE (init))
      && !DECIMAL_FLOAT_TYPE_P (type))
    {
      error_at (loc, "%<constexpr%> initializer for a binary "
		"floating-point type is of decimal type");
      ಹಿಂತಿರುಗಿ;
    }
  ತಾರ್ಕಿಕ ಹೊಂದುತ್ತದೆ;
  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (type) == COMPLEX_TYPE)
    {
      ಆಯ್ಕೆ (ವೃಕ್ಷ_ಸಂಕೇತ (init))
	{
	ಸ್ಥಿತಿ INTEGER_CST:
	ಸ್ಥಿತಿ REAL_CST:
	  ಹೊಂದುತ್ತದೆ = constexpr_init_ಹೊಂದುತ್ತದೆ_real_type (ವೃಕ್ಷ_TYPE (type), init);
	  ನಿಲ್ಲಿಸು;
	ಸ್ಥಿತಿ COMPLEX_CST:
	  ಹೊಂದುತ್ತದೆ = (constexpr_init_ಹೊಂದುತ್ತದೆ_real_type (ವೃಕ್ಷ_TYPE (type),
						 ವೃಕ್ಷ_REALPART (init))
		  && constexpr_init_ಹೊಂದುತ್ತದೆ_real_type (ವೃಕ್ಷ_TYPE (type),
						    ವೃಕ್ಷ_IMAGPART (init)));
	  ನಿಲ್ಲಿಸು;
	ಪೂರ್ವನಿಯೋಜಿತ:
	  gcc_unreachable ();
	}
    }
  ಇಲ್ಲದಿದ್ದರೆ
    ಹೊಂದುತ್ತದೆ = constexpr_init_ಹೊಂದುತ್ತದೆ_real_type (type, init);
  ಆದರೆ (!ಹೊಂದುತ್ತದೆ)
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
	     ವೃಕ್ಷ origtype, ತಾರ್ಕಿಕ null_ಸೂಚಕ_constant, ತಾರ್ಕಿಕ int_const_ಅಭಿವ್ಯಕ್ತಿ,
	     ತಾರ್ಕಿಕ arith_const_ಅಭಿವ್ಯಕ್ತಿ, ತಾರ್ಕಿಕ strict_string,
	     ತಾರ್ಕಿಕ require_constant, ತಾರ್ಕಿಕ require_constexpr)
{
  ಎಣಿಕೆ ವೃಕ್ಷ_ಸಂಕೇತ_2 ಸಂಕೇತ_2 = ವೃಕ್ಷ_ಸಂಕೇತ (type);
  ವೃಕ್ಷ inside_init = init;
  ವೃಕ್ಷ semantic_type = NULL_ವೃಕ್ಷ;
  ತಾರ್ಕಿಕ maybe_const = ನಿಜ;

  ಆದರೆ (type == error_mark_ಗಂಟು
      || !init
      || error_ಕಾರ್ಯಾಂಶ_p (init))
    ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;

  STRIP_TYPE_NOPS (inside_init);

  /* If require_constant is TRUE,  when the initializer is a call to
     .ACCESS_WITH_SIZE, use the first argument as the initializer.
     For example:
     y = (char *) .ACCESS_WITH_SIZE ((char *) &static_annotated.c,...)
     will be converted to
     y = &static_annotated.c.  */

  ಆದರೆ (require_constant
      && ವೃಕ್ಷ_ಸಂಕೇತ (inside_init) == NOP_ಅಭಿವ್ಯಕ್ತಿ
      && ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (inside_init, 0)) == CALL_ಅಭಿವ್ಯಕ್ತಿ
      && is_access_with_ಗಾತ್ರ_p (ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (inside_init, 0)))
    inside_init
      = get_ref_from_access_with_ಗಾತ್ರ (ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (inside_init, 0));

  ಆದರೆ (!c_ಒಳ_omp_for)
    {
      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (inside_init) == EXCESS_PRECISION_ಅಭಿವ್ಯಕ್ತಿ)
	{
	  semantic_type = ವೃಕ್ಷ_TYPE (inside_init);
	  inside_init = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (inside_init, 0);
	}
      inside_init = c_fully_fold (inside_init, require_constant, &maybe_const);
    }
  /* TODO: this may not detect all cases of expressions folding to
     constants that are not arithmetic constant expressions.  */
  ಆದರೆ (!maybe_const)
    arith_const_ಅಭಿವ್ಯಕ್ತಿ = ಸುಳ್ಳು;
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!INTEGRAL_TYPE_P (ವೃಕ್ಷ_TYPE (inside_init))
	   && ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (inside_init)) != REAL_TYPE
	   && ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (inside_init)) != COMPLEX_TYPE)
    arith_const_ಅಭಿವ್ಯಕ್ತಿ = ಸುಳ್ಳು;
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (inside_init) != INTEGER_CST
	   && ವೃಕ್ಷ_ಸಂಕೇತ (inside_init) != REAL_CST
	   && ವೃಕ್ಷ_ಸಂಕೇತ (inside_init) != COMPLEX_CST
	   && ವೃಕ್ಷ_ಸಂಕೇತ (inside_init) != RAW_ದತ್ತಾಂಶ_CST)
    arith_const_ಅಭಿವ್ಯಕ್ತಿ = ಸುಳ್ಳು;
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ವೃಕ್ಷ_ಅತಿಪ್ರವಾಹ (inside_init))
    arith_const_ಅಭಿವ್ಯಕ್ತಿ = ಸುಳ್ಳು;

  /* Initialization of an array of chars from a string constant
     optionally enclosed in braces.  */

  ಆದರೆ (ಸಂಕೇತ_2 == ARRAY_TYPE && inside_init
      && ವೃಕ್ಷ_ಸಂಕೇತ (inside_init) == STRING_CST)
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

      ಆದರೆ (char_array || wchar_array || char16_array || char32_array)
	{
	  ರಚನೆ c_ಅಭಿವ್ಯಕ್ತಿ ಅಭಿವ್ಯಕ್ತಿ;
	  ವೃಕ್ಷ typ2 = TYPE_MAIN_VARIANT (ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_TYPE (inside_init)));
	  ತಾರ್ಕಿಕ incompat_string_cst = ಸುಳ್ಳು;
	  ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ = inside_init;
	  ಅಭಿವ್ಯಕ್ತಿ.original_ಸಂಕೇತ = (strict_string ? STRING_CST : ERROR_MARK);
	  ಅಭಿವ್ಯಕ್ತಿ.original_type = ಖಾಲಿ;
	  ಅಭಿವ್ಯಕ್ತಿ.m_decimal = 0;
	  maybe_warn_string_init (init_loc, type, ಅಭಿವ್ಯಕ್ತಿ);

	  ಆದರೆ (flexible_array_member_type_p (type))
	    pedwarn_init (init_loc, OPT_Wpedantic,
			  "initialization of a flexible array member");

	  ಆದರೆ (comptypes (TYPE_MAIN_VARIANT (ವೃಕ್ಷ_TYPE (inside_init)),
			 TYPE_MAIN_VARIANT (type)))
	    ಹಿಂತಿರುಗಿ inside_init;

	  ಆದರೆ (char_array)
	    {
	      ಆದರೆ (typ2 != char_type_ಗಂಟು && typ2 != char8_type_ಗಂಟು)
		incompat_string_cst = ನಿಜ;
	    }
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!comptypes (typ1, typ2))
	    incompat_string_cst = ನಿಜ;

          ಆದರೆ (incompat_string_cst)
            {
	      error_init (init_loc, "cannot initialize array of %qT from "
			  "a string literal with type array of %qT",
			  typ1, typ2);
	      ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
            }

	  ಆದರೆ (require_constexpr
	      && TYPE_UNSIGNED (typ1) != TYPE_UNSIGNED (typ2))
	    {
	      /* Check if all characters of the string can be
		 represented in the type of the constexpr object being
		 initialized.  */
	      ಚಿಹ್ನೆರಹಿತ HOST_WIDE_INT len = ವೃಕ್ಷ_STRING_ಉದ್ದಳತೆ (inside_init);
	      ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *p =
		(ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *) ವೃಕ್ಷ_STRING_ಸೂಚಕ (inside_init);
	      gcc_assert (CHAR_TYPE_ಗಾತ್ರ == 8 && CHAR_ಬಿಟ್ == 8);
	      ಗಾಗಿ (ಚಿಹ್ನೆರಹಿತ i = 0; i < len; i++)
		ಆದರೆ (p[i] > 127)
		  {
		    error_init (init_loc, "%<constexpr%> initializer not "
				"representable in type of object");
		    ನಿಲ್ಲಿಸು;
		  }
	    }

	  ಆದರೆ (TYPE_DOMAIN (type) != NULL_ವೃಕ್ಷ
	      && TYPE_ಗಾತ್ರ (type) != NULL_ವೃಕ್ಷ
	      && ವೃಕ್ಷ_ಸಂಕೇತ (TYPE_ಗಾತ್ರ (type)) == INTEGER_CST)
	    {
	      ಚಿಹ್ನೆರಹಿತ HOST_WIDE_INT len = ವೃಕ್ಷ_STRING_ಉದ್ದಳತೆ (inside_init);

	      ಆದರೆ (compare_ವೃಕ್ಷ_int (TYPE_ಗಾತ್ರ_UNIT (type), len) < 0)
		{
		  ಚಿಹ್ನೆರಹಿತ HOST_WIDE_INT avail
		    = ವೃಕ್ಷ_ಗಮ್ಯ_uhwi (TYPE_ಗಾತ್ರ_UNIT (type));
		  ಚಿಹ್ನೆರಹಿತ unit = TYPE_PRECISION (typ1) / ಬಿಟ್ಟುಗಳು_ಪ್ರತಿ_UNIT;
		  ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *p = ವೃಕ್ಷ_STRING_ಸೂಚಕ (inside_init);

		  /* Construct truncated string.  */
		  inside_init = build_string (avail, p);

		  /* Subtract the size of a single (possibly wide) character
		     because it may be ok to ignore the terminating NUL char
		     that is counted in the length of the constant.  */
		  ಆದರೆ (len - unit > avail)
		    pedwarn_init (init_loc, 0,
				  "initializer-string for array of %qT "
				  "is too long (%wu chars into %wu "
				  "available)", typ1, len, avail);
		  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (warn_cxx_compat)
		    warning_at (init_loc, OPT_Wc___compat,
				"initializer-string for array of %qT "
				"is too long for C++ (%wu chars into %wu "
				"available)", typ1, len, avail);
		  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (warn_unterminated_string_initialization
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
	  ಹಿಂತಿರುಗಿ inside_init;
	}
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (INTEGRAL_TYPE_P (typ1))
	{
	  error_init (init_loc, "array of inappropriate type initialized "
		      "from string constant");
	  ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
	}
    }

  /* Build a VECTOR_CST from a *constant* vector constructor.  If the
     vector constructor is not constant (e.g. {1,2,3,foo()}) then punt
     below and handle as a constructor.  */
  ಆದರೆ (ಸಂಕೇತ_2 == ಸದಿಶ_TYPE
      && ಸದಿಶ_TYPE_P (ವೃಕ್ಷ_TYPE (inside_init))
      && ಸದಿಶ_types_convertible_p (ವೃಕ್ಷ_TYPE (inside_init), type, ನಿಜ)
      && ವೃಕ್ಷ_CONSTANT (inside_init))
    {
      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (inside_init) == ಸದಿಶ_CST
	  && comptypes (TYPE_MAIN_VARIANT (ವೃಕ್ಷ_TYPE (inside_init)),
			TYPE_MAIN_VARIANT (type)))
	ಹಿಂತಿರುಗಿ inside_init;

      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (inside_init) == CONSTRUCTOR)
	{
	  ಚಿಹ್ನೆರಹಿತ HOST_WIDE_INT ix;
	  ವೃಕ್ಷ ಮೌಲ್ಯ;
	  ತಾರ್ಕಿಕ constant_p = ನಿಜ;

	  /* Iterate through elements and check if all constructor
	     elements are *_CSTs.  */
	  FOR_EACH_CONSTRUCTOR_ಮೌಲ್ಯ (CONSTRUCTOR_ELTS (inside_init), ix, ಮೌಲ್ಯ)
	    ಆದರೆ (!CONSTANT_CLASS_P (ಮೌಲ್ಯ))
	      {
		constant_p = ಸುಳ್ಳು;
		ನಿಲ್ಲಿಸು;
	      }

	  ಆದರೆ (constant_p)
	    ಹಿಂತಿರುಗಿ build_ಸದಿಶ_from_ctor (type,
					   CONSTRUCTOR_ELTS (inside_init));
	}
    }

  ಆದರೆ (warn_sequence_ಬಿಂದು)
    verify_sequence_points (inside_init);

  /* Any type can be initialized
     from an expression of the same type, optionally with braces.  */

  ಆದರೆ (inside_init && ವೃಕ್ಷ_TYPE (inside_init) != NULL_ವೃಕ್ಷ
      && (comptypes (TYPE_MAIN_VARIANT (ವೃಕ್ಷ_TYPE (inside_init)),
		     TYPE_MAIN_VARIANT (type))
	  || (ಸಂಕೇತ_2 == ARRAY_TYPE
	      && comptypes (ವೃಕ್ಷ_TYPE (inside_init), type))
	  || (gnu_ಸದಿಶ_type_p (type)
	      && comptypes (ವೃಕ್ಷ_TYPE (inside_init), type))
	  || (ಸಂಕೇತ_2 == ಸೂಚಕ_TYPE
	      && ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (inside_init)) == ARRAY_TYPE
	      && comptypes (ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_TYPE (inside_init)),
			    ವೃಕ್ಷ_TYPE (type)))))
    {
      ಆದರೆ (ಸಂಕೇತ_2 == ಸೂಚಕ_TYPE)
	{
	  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (inside_init)) == ARRAY_TYPE)
	    {
	      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (inside_init) == STRING_CST
		  || ವೃಕ್ಷ_ಸಂಕೇತ (inside_init) == COMPOUND_LITERAL_ಅಭಿವ್ಯಕ್ತಿ)
		inside_init = array_ಗಮ್ಯ_ಸೂಚಕ_conversion
		  (init_loc, inside_init);
	      ಇಲ್ಲದಿದ್ದರೆ
		{
		  error_init (init_loc, "invalid use of non-lvalue array");
		  ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
		}
	    }
	}

      ಆದರೆ (ಸಂಕೇತ_2 == ಸದಿಶ_TYPE || c_hardbool_type_attr (type))
	/* Although the types are compatible, we may require a
	   conversion.  */
	inside_init = convert (type, inside_init);

      ಆದರೆ ((ಸಂಕೇತ_2 == ದಾಖಲೆ_TYPE || ಸಂಕೇತ_2 == UNION_TYPE)
	  && !comptypes (TYPE_MAIN_VARIANT (type), TYPE_MAIN_VARIANT (ವೃಕ್ಷ_TYPE (inside_init))))
	{
	  error_init (init_loc, "invalid initializer");
	  ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
	}

      ಆದರೆ (require_constant
	  && ವೃಕ್ಷ_ಸಂಕೇತ (inside_init) == COMPOUND_LITERAL_ಅಭಿವ್ಯಕ್ತಿ)
	{
	  /* As an extension, allow initializing objects with static storage
	     duration with compound literals (which are then treated just as
	     the brace enclosed list they contain).  Also allow this for
	     vectors, as we can only assign them with compound literals.  */
	  ಆದರೆ (flag_isoc99 && ಸಂಕೇತ_2 != ಸದಿಶ_TYPE)
	    pedwarn_init (init_loc, OPT_Wpedantic, "initializer element "
			  "is not constant");
	  ವೃಕ್ಷ decl = COMPOUND_LITERAL_ಅಭಿವ್ಯಕ್ತಿ_DECL (inside_init);
	  inside_init = DECL_INITIAL (decl);
	}

      ಆದರೆ (ಸಂಕೇತ_2 == ARRAY_TYPE && ವೃಕ್ಷ_ಸಂಕೇತ (inside_init) != STRING_CST
	  && ವೃಕ್ಷ_ಸಂಕೇತ (inside_init) != CONSTRUCTOR)
	{
	  error_init (init_loc, "array initialized from non-constant array "
		      "expression");
	  ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
	}

      /* Compound expressions can only occur here if -Wpedantic or
	 -pedantic-errors is specified.  In the later case, we always want
	 an error.  In the former case, we simply want a warning.  */
      ಆದರೆ (require_constant && pedantic
	  && ವೃಕ್ಷ_ಸಂಕೇತ (inside_init) == COMPOUND_ಅಭಿವ್ಯಕ್ತಿ)
	{
	  inside_init
	    = valid_compound_ಅಭಿವ್ಯಕ್ತಿ_initializer (inside_init,
					       ವೃಕ್ಷ_TYPE (inside_init));
	  ಆದರೆ (inside_init == error_mark_ಗಂಟು)
	    error_init (init_loc, "initializer element is not constant");
	  ಇಲ್ಲದಿದ್ದರೆ
	    pedwarn_init (init_loc, OPT_Wpedantic,
			  "initializer element is not constant");
	  ಆದರೆ (flag_pedantic_errors)
	    inside_init = error_mark_ಗಂಟು;
	}
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (require_constant
	       && !initializer_constant_valid_p (inside_init,
						 ವೃಕ್ಷ_TYPE (inside_init)))
	{
	  error_init (init_loc, "initializer element is not constant");
	  inside_init = error_mark_ಗಂಟು;
	}
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (require_constant && !maybe_const)
	pedwarn_init (init_loc, OPT_Wpedantic,
		      "initializer element is not a constant expression");
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (require_constexpr)
	check_constexpr_init (init_loc, type, inside_init,
			      int_const_ಅಭಿವ್ಯಕ್ತಿ, arith_const_ಅಭಿವ್ಯಕ್ತಿ);

      /* Added to enable additional -Wsuggest-attribute=format warnings.  */
      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (inside_init)) == ಸೂಚಕ_TYPE)
	inside_init = convert_for_assignment (init_loc, UNKNOWN_LOCATION,
					      type, inside_init, origtype,
					      (require_constant
					       ? ic_init_const
					       : ic_init), null_ಸೂಚಕ_constant,
					      NULL_ವೃಕ್ಷ, NULL_ವೃಕ್ಷ, 0);
      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (inside_init) == RAW_ದತ್ತಾಂಶ_CST
	  && c_inhibit_evaluation_warnings == 0
	  && warn_conversion
	  && !TYPE_UNSIGNED (type)
	  && TYPE_PRECISION (type) == CHAR_ಬಿಟ್)
	ಗಾಗಿ (ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ i = 0;
	     i < (ಚಿಹ್ನೆರಹಿತ) RAW_ದತ್ತಾಂಶ_ಉದ್ದಳತೆ (inside_init); ++i)
	  ಆದರೆ (RAW_ದತ್ತಾಂಶ_SCHAR_ELT (inside_init, i) < 0)
	    warning_at (init_loc, OPT_Wconversion,
			"conversion from %qT to %qT changes value from "
			"%qd to %qd",
			integer_type_ಗಂಟು, type,
			RAW_ದತ್ತಾಂಶ_UCHAR_ELT (inside_init, i),
			RAW_ದತ್ತಾಂಶ_SCHAR_ELT (inside_init, i));
      ಹಿಂತಿರುಗಿ inside_init;
    }

  /* Handle scalar types, including conversions.  */

  ಆದರೆ (ಸಂಕೇತ_2 == INTEGER_TYPE || ಸಂಕೇತ_2 == REAL_TYPE || ಸಂಕೇತ_2 == FIXED_ಬಿಂದು_TYPE
      || ಸಂಕೇತ_2 == ಸೂಚಕ_TYPE || ಸಂಕೇತ_2 == ENUMERAL_TYPE || ಸಂಕೇತ_2 == BOOLEAN_TYPE
      || ಸಂಕೇತ_2 == COMPLEX_TYPE || ಸಂಕೇತ_2 == ಸದಿಶ_TYPE || ಸಂಕೇತ_2 == NULLPTR_TYPE
      || ಸಂಕೇತ_2 == BITINT_TYPE)
    {
      ವೃಕ್ಷ unconverted_init = inside_init;
      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (init)) == ARRAY_TYPE
	  && (ವೃಕ್ಷ_ಸಂಕೇತ (init) == STRING_CST
	      || ವೃಕ್ಷ_ಸಂಕೇತ (init) == COMPOUND_LITERAL_ಅಭಿವ್ಯಕ್ತಿ))
	inside_init = init = array_ಗಮ್ಯ_ಸೂಚಕ_conversion (init_loc, init);
      ಆದರೆ (semantic_type)
	inside_init = build1 (EXCESS_PRECISION_ಅಭಿವ್ಯಕ್ತಿ, semantic_type,
			      inside_init);
      inside_init
	= convert_for_assignment (init_loc, UNKNOWN_LOCATION, type,
				  inside_init, origtype,
				  require_constant ? ic_init_const : ic_init,
				  null_ಸೂಚಕ_constant, NULL_ವೃಕ್ಷ, NULL_ವೃಕ್ಷ,
				  0);

      /* Check to see if we have already given an error message.  */
      ಆದರೆ (inside_init == error_mark_ಗಂಟು)
	;
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (require_constant && !ವೃಕ್ಷ_CONSTANT (inside_init))
	{
	  error_init (init_loc, "initializer element is not constant");
	  inside_init = error_mark_ಗಂಟು;
	}
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (require_constant
	       && !initializer_constant_valid_p (inside_init,
						 ವೃಕ್ಷ_TYPE (inside_init)))
	{
	  error_init (init_loc, "initializer element is not computable at "
		      "load time");
	  inside_init = error_mark_ಗಂಟು;
	}
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (require_constant && !maybe_const)
	pedwarn_init (init_loc, OPT_Wpedantic,
		      "initializer element is not a constant expression");
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (require_constexpr)
	check_constexpr_init (init_loc, type, unconverted_init,
			      int_const_ಅಭಿವ್ಯಕ್ತಿ, arith_const_ಅಭಿವ್ಯಕ್ತಿ);

      ಹಿಂತಿರುಗಿ inside_init;
    }

  /* Come here only for records and arrays.  */

  ಆದರೆ (COMPLETE_TYPE_P (type) && ವೃಕ್ಷ_ಸಂಕೇತ (TYPE_ಗಾತ್ರ (type)) != INTEGER_CST)
    {
      error_init (init_loc,
		  "variable-sized object may not be initialized except "
		  "with an empty initializer");
      ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
    }

  error_init (init_loc, "invalid initializer");
  ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
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
ಸ್ಥಿರ ವೃಕ್ಷ constructor_ಸೂಚ್ಯಂಕ;

/* For an ARRAY_TYPE, this is the maximum index.  */
ಸ್ಥಿರ ವೃಕ್ಷ constructor_max_ಸೂಚ್ಯಂಕ;

/* For a RECORD_TYPE, this is the first field not yet written out.  */
ಸ್ಥಿರ ವೃಕ್ಷ constructor_unfilled_fields;

/* For an ARRAY_TYPE, this is the index of the first element
   not yet written out.  */
ಸ್ಥಿರ ವೃಕ್ಷ constructor_unfilled_ಸೂಚ್ಯಂಕ;

/* In a RECORD_TYPE, the byte index of the next consecutive field.
   This is so we can generate gaps between fields, when appropriate.  */
ಸ್ಥಿರ ವೃಕ್ಷ constructor_ಬಿಟ್_ಸೂಚ್ಯಂಕ;

/* If we are saving up the elements rather than allocating them,
   this is the list of elements so far (in reverse order,
   most recent first).  */
ಸ್ಥಿರ vec<constructor_elt, va_gc> *constructor_elements;

/* 1 if constructor should be incrementally stored into a constructor chain,
   0 if all the elements should be kept in AVL tree.  */
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ constructor_incremental;

/* 1 if so far this constructor's elements are all compile-time constants.  */
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ constructor_constant;

/* 1 if so far this constructor's elements are all valid address constants.  */
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ constructor_simple;

/* 1 if this constructor has an element that cannot be part of a
   constant expression.  */
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ constructor_nonconst;

/* 1 if this constructor is erroneous so far.  */
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ constructor_erroneous;

/* 1 if this constructor is the universal zero initializer { 0 }.  */
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ constructor_zeroinit;

/* 1 if this constructor should have padding bits zeroed (C23 {}.  */
ಸ್ಥಿರ ತಾರ್ಕಿಕ constructor_zero_padding_ಬಿಟ್ಟುಗಳು;

/* 1 if this constructor is a braced scalar initializer (further nested levels
   of braces are an error).  */
ಸ್ಥಿರ ತಾರ್ಕಿಕ constructor_braced_scalar;

/* Structure for managing pending initializer elements, organized as an
   AVL tree.  */

ರಚನೆ init_ಗಂಟು
{
  ರಚನೆ init_ಗಂಟು *ಎಡ, *ಬಲ;
  ರಚನೆ init_ಗಂಟು *ಪೋಷಕ;
  ಪೂರ್ಣಾಂಕ balance;
  ವೃಕ್ಷ purpose;
  ವೃಕ್ಷ ಮೌಲ್ಯ;
  ವೃಕ್ಷ origtype;
};

/* Tree of pending elements at this constructor level.
   These are elements encountered out of order
   which belong at places we haven't reached yet in actually
   writing the output.
   Will never hold tree nodes across GC runs.  */
ಸ್ಥಿರ ರಚನೆ init_ಗಂಟು *constructor_pending_elts;

/* The SPELLING_DEPTH of this constructor.  */
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ constructor_ಆಳ;

/* DECL node for which an initializer is being read.
   0 means we are reading a constructor expression
   such as (struct foo) {...}.  */
ಸ್ಥಿರ ವೃಕ್ಷ constructor_decl;

/* Nonzero if there were any member designators in this initializer.  */
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ constructor_designated;

/* Nesting depth of designator list.  */
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ designator_ಆಳ;

/* Nonzero if there were diagnosed errors in this designator list.  */
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ designator_erroneous;


/* This stack has a level for each implicit or explicit level of
   structuring in the initializer, including the outermost one.  It
   saves the values of most of the variables above.  */

ರಚನೆ constructor_range_ರಾಶಿ;

ರಚನೆ constructor_ರಾಶಿ
{
  ರಚನೆ constructor_ರಾಶಿ *ಮುಂದಿನ;
  ವೃಕ್ಷ type;
  ವೃಕ್ಷ fields;
  ವೃಕ್ಷ ಸೂಚ್ಯಂಕ;
  ವೃಕ್ಷ max_ಸೂಚ್ಯಂಕ;
  ವೃಕ್ಷ unfilled_ಸೂಚ್ಯಂಕ;
  ವೃಕ್ಷ unfilled_fields;
  ವೃಕ್ಷ ಬಿಟ್_ಸೂಚ್ಯಂಕ;
  vec<constructor_elt, va_gc> *elements;
  ರಚನೆ init_ಗಂಟು *pending_elts;
  ಪೂರ್ಣಾಂಕ ಸ್ಥಾನಾಂತರ;
  ಪೂರ್ಣಾಂಕ ಆಳ;
  /* If value nonzero, this value should replace the entire
     constructor at this level.  */
  ರಚನೆ c_ಅಭಿವ್ಯಕ್ತಿ replacement_ಮೌಲ್ಯ;
  ರಚನೆ constructor_range_ರಾಶಿ *range_ರಾಶಿ;
  ಅಕ್ಷರ constant;
  ಅಕ್ಷರ simple;
  ಅಕ್ಷರ nonconst;
  ಅಕ್ಷರ implicit;
  ಅಕ್ಷರ erroneous;
  ಅಕ್ಷರ outer;
  ಅಕ್ಷರ incremental;
  ಅಕ್ಷರ designated;
  ತಾರ್ಕಿಕ zero_padding_ಬಿಟ್ಟುಗಳು;
  ತಾರ್ಕಿಕ braced_scalar;
  ಪೂರ್ಣಾಂಕ designator_ಆಳ;
};

ಸ್ಥಿರ ರಚನೆ constructor_ರಾಶಿ *constructor_ರಾಶಿ;

/* This stack represents designators from some range designator up to
   the last designator in the list.  */

ರಚನೆ constructor_range_ರಾಶಿ
{
  ರಚನೆ constructor_range_ರಾಶಿ *ಮುಂದಿನ, *prev;
  ರಚನೆ constructor_ರಾಶಿ *ರಾಶಿ;
  ವೃಕ್ಷ range_ಆರಂಭ;
  ವೃಕ್ಷ ಸೂಚ್ಯಂಕ;
  ವೃಕ್ಷ range_ಕೊನೆ;
  ವೃಕ್ಷ fields;
};

ಸ್ಥಿರ ರಚನೆ constructor_range_ರಾಶಿ *constructor_range_ರಾಶಿ;

/* This stack records separate initializers that are nested.
   Nested initializers can't happen in ANSI C, but GNU C allows them
   in cases like { ... (struct foo) { ... } ... }.  */

ರಚನೆ initializer_ರಾಶಿ
{
  ರಚನೆ initializer_ರಾಶಿ *ಮುಂದಿನ;
  ವೃಕ್ಷ decl;
  ರಚನೆ constructor_ರಾಶಿ *constructor_ರಾಶಿ;
  ರಚನೆ constructor_range_ರಾಶಿ *constructor_range_ರಾಶಿ;
  vec<constructor_elt, va_gc> *elements;
  ರಚನೆ spelling *spelling;
  ರಚನೆ spelling *spelling_ತಳ;
  ಪೂರ್ಣಾಂಕ spelling_ಗಾತ್ರ;
  ಅಕ್ಷರ require_constant_ಮೌಲ್ಯ;
  ಅಕ್ಷರ require_constant_elements;
  ಅಕ್ಷರ require_constexpr_ಮೌಲ್ಯ;
  ಅಕ್ಷರ designated;
  rich_location *missing_brace_richloc;
};

ಸ್ಥಿರ ರಚನೆ initializer_ರಾಶಿ *initializer_ರಾಶಿ;

/* Prepare to parse and output the initializer for variable DECL.  */

ಶೂನ್ಯ
ಆರಂಭ_init (ವೃಕ್ಷ decl, ವೃಕ್ಷ asmspec_ವೃಕ್ಷ ATTRIBUTE_ಬಳಸದ,
	    ತಾರ್ಕಿಕ init_require_constant, ತಾರ್ಕಿಕ init_require_constexpr,
	    rich_location *richloc)
{
  ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *locus;
  ರಚನೆ initializer_ರಾಶಿ *p = XNEW (ರಚನೆ initializer_ರಾಶಿ);

  p->decl = constructor_decl;
  p->require_constant_ಮೌಲ್ಯ = require_constant_ಮೌಲ್ಯ;
  p->require_constant_elements = require_constant_elements;
  p->require_constexpr_ಮೌಲ್ಯ = require_constexpr_ಮೌಲ್ಯ;
  p->constructor_ರಾಶಿ = constructor_ರಾಶಿ;
  p->constructor_range_ರಾಶಿ = constructor_range_ರಾಶಿ;
  p->elements = constructor_elements;
  p->spelling = spelling;
  p->spelling_ತಳ = spelling_ತಳ;
  p->spelling_ಗಾತ್ರ = spelling_ಗಾತ್ರ;
  p->ಮುಂದಿನ = initializer_ರಾಶಿ;
  p->missing_brace_richloc = richloc;
  p->designated = constructor_designated;
  initializer_ರಾಶಿ = p;

  constructor_decl = decl;
  constructor_designated = 0;

  require_constant_ಮೌಲ್ಯ = init_require_constant;
  require_constexpr_ಮೌಲ್ಯ = init_require_constexpr;
  ಆದರೆ (decl != NULL_ವೃಕ್ಷ && decl != error_mark_ಗಂಟು)
    {
      require_constant_elements
	= ((init_require_constant || (pedantic && !flag_isoc99))
	   /* For a scalar, you can always use any value to initialize,
	      even within braces.  */
	   && AGGREGATE_TYPE_P (ವೃಕ್ಷ_TYPE (decl)));
      locus = identifier_ಗಮ್ಯ_locale (IDENTIFIER_ಸೂಚಕ (DECL_NAME (decl)));
    }
  ಇಲ್ಲದಿದ್ದರೆ
    {
      require_constant_elements = ಸುಳ್ಳು;
      locus = _("(anonymous)");
    }

  constructor_ರಾಶಿ = 0;
  constructor_range_ರಾಶಿ = 0;

  ಸಿಕ್ಕಿತು_missing_braces = 0;

  spelling_ತಳ = 0;
  spelling_ಗಾತ್ರ = 0;
  RESTORE_SPELLING_ಆಳ (0);

  ಆದರೆ (locus)
    ತಳ್ಳು_string (locus);
}

ಶೂನ್ಯ
ಮುಕ್ತಾಯ_init (ಶೂನ್ಯ)
{
  ರಚನೆ initializer_ರಾಶಿ *p = initializer_ರಾಶಿ;

  /* Free the whole constructor stack of this initializer.  */
  ಆಗ (constructor_ರಾಶಿ)
    {
      ರಚನೆ constructor_ರಾಶಿ *q = constructor_ರಾಶಿ;
      constructor_ರಾಶಿ = q->ಮುಂದಿನ;
      XDELETE (q);
    }

  gcc_assert (!constructor_range_ರಾಶಿ);

  /* Pop back to the data of the outer initializer (if any).  */
  XDELETE (spelling_ತಳ);

  constructor_decl = p->decl;
  require_constant_ಮೌಲ್ಯ = p->require_constant_ಮೌಲ್ಯ;
  require_constant_elements = p->require_constant_elements;
  require_constexpr_ಮೌಲ್ಯ = p->require_constexpr_ಮೌಲ್ಯ;
  constructor_ರಾಶಿ = p->constructor_ರಾಶಿ;
  constructor_designated = p->designated;
  constructor_range_ರಾಶಿ = p->constructor_range_ರಾಶಿ;
  constructor_elements = p->elements;
  spelling = p->spelling;
  spelling_ತಳ = p->spelling_ತಳ;
  spelling_ಗಾತ್ರ = p->spelling_ಗಾತ್ರ;
  initializer_ರಾಶಿ = p->ಮುಂದಿನ;
  XDELETE (p);
}

/* Call here when we see the initializer is surrounded by braces.
   This is instead of a call to push_init_level;
   it is matched by a call to pop_init_level.

   TYPE is the type to initialize, for a constructor expression.
   For an initializer for a decl, TYPE is zero.  */

ಶೂನ್ಯ
really_ಆರಂಭ_incremental_init (ವೃಕ್ಷ type)
{
  ರಚನೆ constructor_ರಾಶಿ *p = XNEW (ರಚನೆ constructor_ರಾಶಿ);

  ಆದರೆ (type == NULL_ವೃಕ್ಷ)
    type = ವೃಕ್ಷ_TYPE (constructor_decl);

  ಆದರೆ (ಸದಿಶ_TYPE_P (type)
      && TYPE_ಸದಿಶ_OPAQUE (type))
    error ("opaque vector types cannot be initialized");

  p->type = constructor_type;
  p->fields = constructor_fields;
  p->ಸೂಚ್ಯಂಕ = constructor_ಸೂಚ್ಯಂಕ;
  p->max_ಸೂಚ್ಯಂಕ = constructor_max_ಸೂಚ್ಯಂಕ;
  p->unfilled_ಸೂಚ್ಯಂಕ = constructor_unfilled_ಸೂಚ್ಯಂಕ;
  p->unfilled_fields = constructor_unfilled_fields;
  p->ಬಿಟ್_ಸೂಚ್ಯಂಕ = constructor_ಬಿಟ್_ಸೂಚ್ಯಂಕ;
  p->elements = constructor_elements;
  p->constant = constructor_constant;
  p->simple = constructor_simple;
  p->nonconst = constructor_nonconst;
  p->erroneous = constructor_erroneous;
  p->pending_elts = constructor_pending_elts;
  p->ಆಳ = constructor_ಆಳ;
  p->replacement_ಮೌಲ್ಯ.ಮೌಲ್ಯ = 0;
  p->replacement_ಮೌಲ್ಯ.original_ಸಂಕೇತ = ERROR_MARK;
  p->replacement_ಮೌಲ್ಯ.original_type = ಖಾಲಿ;
  p->implicit = 0;
  p->range_ರಾಶಿ = 0;
  p->outer = 0;
  p->incremental = constructor_incremental;
  p->designated = constructor_designated;
  p->zero_padding_ಬಿಟ್ಟುಗಳು = constructor_zero_padding_ಬಿಟ್ಟುಗಳು;
  p->braced_scalar = constructor_braced_scalar;
  p->designator_ಆಳ = designator_ಆಳ;
  p->ಮುಂದಿನ = 0;
  constructor_ರಾಶಿ = p;

  constructor_constant = 1;
  constructor_simple = 1;
  constructor_nonconst = 0;
  constructor_ಆಳ = SPELLING_ಆಳ ();
  constructor_elements = ಖಾಲಿ;
  constructor_pending_elts = 0;
  constructor_type = type;
  constructor_incremental = 1;
  constructor_designated = 0;
  constructor_zero_padding_ಬಿಟ್ಟುಗಳು = ಸುಳ್ಳು;
  constructor_zeroinit = 1;
  constructor_braced_scalar = ಸುಳ್ಳು;
  designator_ಆಳ = 0;
  designator_erroneous = 0;

  ಆದರೆ (ದಾಖಲೆ_OR_UNION_TYPE_P (constructor_type))
    {
      constructor_fields = TYPE_FIELDS (constructor_type);
      /* Skip any nameless bit fields at the beginning.  */
      ಆಗ (constructor_fields != NULL_ವೃಕ್ಷ
	     && DECL_UNNAMED_ಬಿಟ್_ಕ್ಷೇತ್ರ (constructor_fields))
	constructor_fields = DECL_CHAIN (constructor_fields);

      constructor_unfilled_fields = constructor_fields;
      constructor_ಬಿಟ್_ಸೂಚ್ಯಂಕ = bitsize_zero_ಗಂಟು;
    }
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (constructor_type) == ARRAY_TYPE)
    {
      ಆದರೆ (TYPE_DOMAIN (constructor_type))
	{
	  constructor_max_ಸೂಚ್ಯಂಕ
	    = TYPE_MAX_ಮೌಲ್ಯ (TYPE_DOMAIN (constructor_type));

	  /* Detect non-empty initializations of zero-length arrays.  */
	  ಆದರೆ (constructor_max_ಸೂಚ್ಯಂಕ == NULL_ವೃಕ್ಷ
	      && TYPE_ಗಾತ್ರ (constructor_type))
	    constructor_max_ಸೂಚ್ಯಂಕ = integer_minus_one_ಗಂಟು;

	  /* constructor_max_index needs to be an INTEGER_CST.  Attempts
	     to initialize VLAs with a nonempty initializer will cause a
	     proper error; avoid tree checking errors as well by setting a
	     safe value.  */
	  ಆದರೆ (constructor_max_ಸೂಚ್ಯಂಕ
	      && ವೃಕ್ಷ_ಸಂಕೇತ (constructor_max_ಸೂಚ್ಯಂಕ) != INTEGER_CST)
	    constructor_max_ಸೂಚ್ಯಂಕ = integer_minus_one_ಗಂಟು;

	  constructor_ಸೂಚ್ಯಂಕ
	    = convert (bitsizetype,
		       TYPE_MIN_ಮೌಲ್ಯ (TYPE_DOMAIN (constructor_type)));
	}
      ಇಲ್ಲದಿದ್ದರೆ
	{
	  constructor_ಸೂಚ್ಯಂಕ = bitsize_zero_ಗಂಟು;
	  constructor_max_ಸೂಚ್ಯಂಕ = NULL_ವೃಕ್ಷ;
	}

      constructor_unfilled_ಸೂಚ್ಯಂಕ = constructor_ಸೂಚ್ಯಂಕ;
    }
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (gnu_ಸದಿಶ_type_p (constructor_type))
    {
      /* Vectors are like simple fixed-size arrays.  */
      constructor_max_ಸೂಚ್ಯಂಕ =
	bitsize_int (TYPE_ಸದಿಶ_SUBPARTS (constructor_type) - 1);
      constructor_ಸೂಚ್ಯಂಕ = bitsize_zero_ಗಂಟು;
      constructor_unfilled_ಸೂಚ್ಯಂಕ = constructor_ಸೂಚ್ಯಂಕ;
    }
  ಇಲ್ಲದಿದ್ದರೆ
    {
      /* Handle the case of int x = {5}; */
      constructor_fields = constructor_type;
      constructor_unfilled_fields = constructor_type;
      constructor_braced_scalar = ನಿಜ;
    }
}

ಬಾಹ್ಯ location_t ಕೊನೆಯ_init_list_comma;

/* Called when we see an open brace for a nested initializer.  Finish
   off any pending levels with implicit braces.  */
ಶೂನ್ಯ
ಮುಕ್ತಾಯ_implicit_inits (location_t loc, ರಚನೆ obstack *braced_init_obstack)
{
  ಆಗ (constructor_ರಾಶಿ->implicit)
    {
      ಆದರೆ (ದಾಖಲೆ_OR_UNION_TYPE_P (constructor_type)
	  && constructor_fields == NULL_ವೃಕ್ಷ)
	process_init_element (ಒಳಹರಿವು_location,
			      ತೆಗೆ_init_level (loc, 1, braced_init_obstack,
					      ಕೊನೆಯ_init_list_comma),
			      ನಿಜ, braced_init_obstack);
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (constructor_type) == ARRAY_TYPE
	       && constructor_max_ಸೂಚ್ಯಂಕ
	       && ವೃಕ್ಷ_int_cst_lt (constructor_max_ಸೂಚ್ಯಂಕ,
				   constructor_ಸೂಚ್ಯಂಕ))
	process_init_element (ಒಳಹರಿವು_location,
			      ತೆಗೆ_init_level (loc, 1, braced_init_obstack,
					      ಕೊನೆಯ_init_list_comma),
			      ನಿಜ, braced_init_obstack);
      ಇಲ್ಲದಿದ್ದರೆ
	ನಿಲ್ಲಿಸು;
    }
}

/* Push down into a subobject, for initialization.
   If this is for an explicit set of braces, IMPLICIT is 0.
   If it is because the next element belongs at a lower level,
   IMPLICIT is 1 (or 2 if the push is because of designator list).  */

ಶೂನ್ಯ
ತಳ್ಳು_init_level (location_t loc, ಪೂರ್ಣಾಂಕ implicit,
		 ರಚನೆ obstack *braced_init_obstack)
{
  ರಚನೆ constructor_ರಾಶಿ *p;
  ವೃಕ್ಷ ಮೌಲ್ಯ = NULL_ವೃಕ್ಷ;

  /* Unless this is an explicit brace, we need to preserve previous
     content if any.  */
  ಆದರೆ (implicit)
    {
      ಆದರೆ (ದಾಖಲೆ_OR_UNION_TYPE_P (constructor_type) && constructor_fields)
	ಮೌಲ್ಯ = ಕಂಡುಹಿಡಿ_init_member (constructor_fields, braced_init_obstack);
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (constructor_type) == ARRAY_TYPE)
	ಮೌಲ್ಯ = ಕಂಡುಹಿಡಿ_init_member (constructor_ಸೂಚ್ಯಂಕ, braced_init_obstack);
    }

  p = XNEW (ರಚನೆ constructor_ರಾಶಿ);
  p->type = constructor_type;
  p->fields = constructor_fields;
  p->ಸೂಚ್ಯಂಕ = constructor_ಸೂಚ್ಯಂಕ;
  p->max_ಸೂಚ್ಯಂಕ = constructor_max_ಸೂಚ್ಯಂಕ;
  p->unfilled_ಸೂಚ್ಯಂಕ = constructor_unfilled_ಸೂಚ್ಯಂಕ;
  p->unfilled_fields = constructor_unfilled_fields;
  p->ಬಿಟ್_ಸೂಚ್ಯಂಕ = constructor_ಬಿಟ್_ಸೂಚ್ಯಂಕ;
  p->elements = constructor_elements;
  p->constant = constructor_constant;
  p->simple = constructor_simple;
  p->nonconst = constructor_nonconst;
  p->erroneous = constructor_erroneous;
  p->pending_elts = constructor_pending_elts;
  p->ಆಳ = constructor_ಆಳ;
  p->replacement_ಮೌಲ್ಯ.ಮೌಲ್ಯ = NULL_ವೃಕ್ಷ;
  p->replacement_ಮೌಲ್ಯ.original_ಸಂಕೇತ = ERROR_MARK;
  p->replacement_ಮೌಲ್ಯ.original_type = ಖಾಲಿ;
  p->implicit = implicit;
  p->outer = 0;
  p->incremental = constructor_incremental;
  p->designated = constructor_designated;
  p->zero_padding_ಬಿಟ್ಟುಗಳು = constructor_zero_padding_ಬಿಟ್ಟುಗಳು;
  p->braced_scalar = constructor_braced_scalar;
  p->designator_ಆಳ = designator_ಆಳ;
  p->ಮುಂದಿನ = constructor_ರಾಶಿ;
  p->range_ರಾಶಿ = 0;
  constructor_ರಾಶಿ = p;

  constructor_constant = 1;
  constructor_simple = 1;
  constructor_nonconst = 0;
  constructor_ಆಳ = SPELLING_ಆಳ ();
  constructor_elements = ಖಾಲಿ;
  constructor_incremental = 1;
  /* If the upper initializer is designated, then mark this as
     designated too to prevent bogus warnings.  */
  constructor_designated = p->designated;
  /* If the upper initializer has padding bits zeroed, that includes
     all nested initializers as well.  */
  constructor_zero_padding_ಬಿಟ್ಟುಗಳು = p->zero_padding_ಬಿಟ್ಟುಗಳು;
  constructor_braced_scalar = ಸುಳ್ಳು;
  constructor_pending_elts = 0;
  ಆದರೆ (!implicit)
    {
      p->range_ರಾಶಿ = constructor_range_ರಾಶಿ;
      constructor_range_ರಾಶಿ = 0;
      designator_ಆಳ = 0;
      designator_erroneous = 0;
    }

  /* Don't die if an entire brace-pair level is superfluous
     in the containing level.  */
  ಆದರೆ (constructor_type == NULL_ವೃಕ್ಷ)
    ;
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ದಾಖಲೆ_OR_UNION_TYPE_P (constructor_type))
    {
      /* Don't die if there are extra init elts at the end.  */
      ಆದರೆ (constructor_fields == NULL_ವೃಕ್ಷ)
	constructor_type = NULL_ವೃಕ್ಷ;
      ಇಲ್ಲದಿದ್ದರೆ
	{
	  constructor_type = ವೃಕ್ಷ_TYPE (constructor_fields);
	  ತಳ್ಳು_member_name (constructor_fields);
	  constructor_ಆಳ++;
	}
    }
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (constructor_type) == ARRAY_TYPE)
    {
      constructor_type = ವೃಕ್ಷ_TYPE (constructor_type);
      ತಳ್ಳು_array_bounds (ವೃಕ್ಷ_ಗಮ್ಯ_uhwi (constructor_ಸೂಚ್ಯಂಕ));
      constructor_ಆಳ++;
    }

  ಆದರೆ (constructor_type == NULL_ವೃಕ್ಷ)
    {
      error_init (loc, "extra brace group at end of initializer");
      constructor_fields = NULL_ವೃಕ್ಷ;
      constructor_unfilled_fields = NULL_ವೃಕ್ಷ;
      ಹಿಂತಿರುಗಿ;
    }

  ಆದರೆ (ಮೌಲ್ಯ && ವೃಕ್ಷ_ಸಂಕೇತ (ಮೌಲ್ಯ) == CONSTRUCTOR)
    {
      constructor_constant = ವೃಕ್ಷ_CONSTANT (ಮೌಲ್ಯ);
      constructor_simple = ವೃಕ್ಷ_STATIC (ಮೌಲ್ಯ);
      constructor_nonconst = CONSTRUCTOR_NON_CONST (ಮೌಲ್ಯ);
      constructor_elements = CONSTRUCTOR_ELTS (ಮೌಲ್ಯ);
      constructor_zero_padding_ಬಿಟ್ಟುಗಳು |= CONSTRUCTOR_ZERO_PADDING_ಬಿಟ್ಟುಗಳು (ಮೌಲ್ಯ);
      ಆದರೆ (!vec_ಸುರಕ್ಷಿತ_is_ಖಾಲಿಗಳು (constructor_elements)
	  && (ವೃಕ್ಷ_ಸಂಕೇತ (constructor_type) == ದಾಖಲೆ_TYPE
	      || ವೃಕ್ಷ_ಸಂಕೇತ (constructor_type) == ARRAY_TYPE))
	ಗಣ_nonincremental_init (braced_init_obstack);
    }

  ಆದರೆ (implicit == 1)
    {
      ಸಿಕ್ಕಿತು_missing_braces = 1;
      ಆದರೆ (initializer_ರಾಶಿ->missing_brace_richloc)
	initializer_ರಾಶಿ->missing_brace_richloc->ಕೂಡಿಸು_fixit_ಸೇರಿಸು_before
	  (loc, "{");
    }

  ಆದರೆ (ದಾಖಲೆ_OR_UNION_TYPE_P (constructor_type))
    {
      constructor_fields = TYPE_FIELDS (constructor_type);
      /* Skip any nameless bit fields at the beginning.  */
      ಆಗ (constructor_fields != NULL_ವೃಕ್ಷ
	     && DECL_UNNAMED_ಬಿಟ್_ಕ್ಷೇತ್ರ (constructor_fields))
	constructor_fields = DECL_CHAIN (constructor_fields);

      constructor_unfilled_fields = constructor_fields;
      constructor_ಬಿಟ್_ಸೂಚ್ಯಂಕ = bitsize_zero_ಗಂಟು;
    }
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (gnu_ಸದಿಶ_type_p (constructor_type))
    {
      /* Vectors are like simple fixed-size arrays.  */
      constructor_max_ಸೂಚ್ಯಂಕ =
	bitsize_int (TYPE_ಸದಿಶ_SUBPARTS (constructor_type) - 1);
      constructor_ಸೂಚ್ಯಂಕ = bitsize_int (0);
      constructor_unfilled_ಸೂಚ್ಯಂಕ = constructor_ಸೂಚ್ಯಂಕ;
    }
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (constructor_type) == ARRAY_TYPE)
    {
      ಆದರೆ (TYPE_DOMAIN (constructor_type))
	{
	  constructor_max_ಸೂಚ್ಯಂಕ
	    = TYPE_MAX_ಮೌಲ್ಯ (TYPE_DOMAIN (constructor_type));

	  /* Detect non-empty initializations of zero-length arrays.  */
	  ಆದರೆ (constructor_max_ಸೂಚ್ಯಂಕ == NULL_ವೃಕ್ಷ
	      && TYPE_ಗಾತ್ರ (constructor_type))
	    constructor_max_ಸೂಚ್ಯಂಕ = integer_minus_one_ಗಂಟು;

	  /* constructor_max_index needs to be an INTEGER_CST.  Attempts
	     to initialize VLAs will cause a proper error; avoid tree
	     checking errors as well by setting a safe value.  */
	  ಆದರೆ (constructor_max_ಸೂಚ್ಯಂಕ
	      && ವೃಕ್ಷ_ಸಂಕೇತ (constructor_max_ಸೂಚ್ಯಂಕ) != INTEGER_CST)
	    constructor_max_ಸೂಚ್ಯಂಕ = integer_minus_one_ಗಂಟು;

	  constructor_ಸೂಚ್ಯಂಕ
	    = convert (bitsizetype,
		       TYPE_MIN_ಮೌಲ್ಯ (TYPE_DOMAIN (constructor_type)));
	}
      ಇಲ್ಲದಿದ್ದರೆ
	constructor_ಸೂಚ್ಯಂಕ = bitsize_zero_ಗಂಟು;

      constructor_unfilled_ಸೂಚ್ಯಂಕ = constructor_ಸೂಚ್ಯಂಕ;
      ಆದರೆ (ಮೌಲ್ಯ && ವೃಕ್ಷ_ಸಂಕೇತ (ಮೌಲ್ಯ) == STRING_CST)
	{
	  /* We need to split the char/wchar array into individual
	     characters, so that we don't have to special case it
	     everywhere.  */
	  ಗಣ_nonincremental_init_from_string (ಮೌಲ್ಯ, braced_init_obstack);
	}
    }
  ಇಲ್ಲದಿದ್ದರೆ
    {
      ಆದರೆ (constructor_type != error_mark_ಗಂಟು)
	{
	  ಆದರೆ (p->braced_scalar)
	    permerror_init (ಒಳಹರಿವು_location, 0,
			    "braces around scalar initializer");
	  ಇಲ್ಲದಿದ್ದರೆ
	    warning_init (ಒಳಹರಿವು_location, 0,
			  "braces around scalar initializer");
	  constructor_braced_scalar = ನಿಜ;
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

ರಚನೆ c_ಅಭಿವ್ಯಕ್ತಿ
ತೆಗೆ_init_level (location_t loc, ಪೂರ್ಣಾಂಕ implicit,
		ರಚನೆ obstack *braced_init_obstack,
		location_t ಸೇರಿಸು_before)
{
  ರಚನೆ constructor_ರಾಶಿ *p;
  ರಚನೆ c_ಅಭಿವ್ಯಕ್ತಿ ret;
  ret.ಮೌಲ್ಯ = NULL_ವೃಕ್ಷ;
  ret.original_ಸಂಕೇತ = ERROR_MARK;
  ret.original_type = ಖಾಲಿ;
  ret.m_decimal = 0;

  ಆದರೆ (implicit == 0)
    {
      /* When we come to an explicit close brace,
	 pop any inner levels that didn't have explicit braces.  */
      ಆಗ (constructor_ರಾಶಿ->implicit)
	process_init_element (ಒಳಹರಿವು_location,
			      ತೆಗೆ_init_level (loc, 1, braced_init_obstack,
					      ಸೇರಿಸು_before),
			      ನಿಜ, braced_init_obstack);
      gcc_assert (!constructor_range_ರಾಶಿ);
    }
  ಇಲ್ಲದಿದ್ದರೆ
    ಆದರೆ (initializer_ರಾಶಿ->missing_brace_richloc)
      initializer_ರಾಶಿ->missing_brace_richloc->ಕೂಡಿಸು_fixit_ಸೇರಿಸು_before
	(ಸೇರಿಸು_before, "}");

  /* Now output all pending elements.  */
  constructor_incremental = 1;
  output_pending_init_elements (1, braced_init_obstack);

  p = constructor_ರಾಶಿ;

  /* Error for initializing a flexible array member.  */
  ಆದರೆ (constructor_type && constructor_fields
      && flexible_array_member_type_p (constructor_type))
    {
      /* Silently discard empty initializations.  The parser will
	 already have pedwarned for empty brackets for C17 and earlier.  */
      ಆದರೆ (integer_zerop (constructor_unfilled_ಸೂಚ್ಯಂಕ))
	constructor_type = NULL_ವೃಕ್ಷ;
      ಆದರೆ (constructor_type || flag_isoc23)
	{
	  gcc_assert (!constructor_type || !TYPE_ಗಾತ್ರ (constructor_type));

	  ಆದರೆ (constructor_ಆಳ <= 2)
	    pedwarn_init (loc, OPT_Wpedantic,
			  "initialization of a flexible array member");
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (constructor_type)
	    error_init (loc, "initialization of flexible array member "
			     "in a nested context");
	  ಇಲ್ಲದಿದ್ದರೆ
	    pedwarn_init (loc, OPT_Wpedantic,
			  "initialization of flexible array member "
			  "in a nested context");

	  /* We have already issued an error message for the existence
	     of a flexible array member not at the end of the structure.
	     Discard the initializer so that we do not die later.  */
	  ಆದರೆ (constructor_type
	      && DECL_CHAIN (constructor_fields) != NULL_ವೃಕ್ಷ
	      && (!p->type || ವೃಕ್ಷ_ಸಂಕೇತ (p->type) != UNION_TYPE))
	    constructor_type = NULL_ವೃಕ್ಷ;
	}
    }

  ಆಯ್ಕೆ (vec_ಸುರಕ್ಷಿತ_ಉದ್ದಳತೆ (constructor_elements))
    {
    ಸ್ಥಿತಿ 0:
      /* Initialization with { } counts as zeroinit.  */
      constructor_zeroinit = 1;
      ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ 1:
      /* This might be zeroinit as well.  */
      ಆದರೆ (integer_zerop ((*constructor_elements)[0].ಮೌಲ್ಯ))
	constructor_zeroinit = 1;
      ನಿಲ್ಲಿಸು;
    ಪೂರ್ವನಿಯೋಜಿತ:
      /* If the constructor has more than one element, it can't be { 0 }.  */
      constructor_zeroinit = 0;
      ನಿಲ್ಲಿಸು;
    }

  /* Warn when some structs are initialized with direct aggregation.  */
  ಆದರೆ (!implicit && ಸಿಕ್ಕಿತು_missing_braces && warn_missing_braces
      && !constructor_zeroinit)
    {
      gcc_assert (initializer_ರಾಶಿ->missing_brace_richloc);
      warning_at (initializer_ರಾಶಿ->missing_brace_richloc,
		  OPT_Wmissing_braces,
		  "missing braces around initializer");
    }

  /* Warn when some struct elements are implicitly initialized to zero.  */
  ಆದರೆ (warn_missing_ಕ್ಷೇತ್ರ_initializers
      && constructor_type
      && ವೃಕ್ಷ_ಸಂಕೇತ (constructor_type) == ದಾಖಲೆ_TYPE
      && constructor_unfilled_fields)
    {
	/* Do not warn for flexible array members or zero-length arrays.  */
	ಆಗ (constructor_unfilled_fields
	       && (!DECL_ಗಾತ್ರ (constructor_unfilled_fields)
		   || integer_zerop (DECL_ಗಾತ್ರ (constructor_unfilled_fields))))
	  constructor_unfilled_fields = DECL_CHAIN (constructor_unfilled_fields);

	ಆದರೆ (constructor_unfilled_fields
	    /* Do not warn if this level of the initializer uses member
	       designators; it is likely to be deliberate.  */
	    && !constructor_designated
	    /* Do not warn about initializing with { 0 } or with { }.  */
	    && !constructor_zeroinit)
	  {
	    ಆದರೆ (warning_at (ಒಳಹರಿವು_location, OPT_Wmissing_ಕ್ಷೇತ್ರ_initializers,
			    "missing initializer for field %qD of %qT",
			    constructor_unfilled_fields,
			    constructor_type))
	      inform (DECL_ಮೂಲ_LOCATION (constructor_unfilled_fields),
		      "%qD declared here", constructor_unfilled_fields);
	  }
    }

  /* Pad out the end of the structure.  */
  ಆದರೆ (p->replacement_ಮೌಲ್ಯ.ಮೌಲ್ಯ)
    /* If this closes a superfluous brace pair,
       just pass out the element between them.  */
    ret = p->replacement_ಮೌಲ್ಯ;
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (constructor_type == NULL_ವೃಕ್ಷ)
    ;
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!ದಾಖಲೆ_OR_UNION_TYPE_P (constructor_type)
	   && ವೃಕ್ಷ_ಸಂಕೇತ (constructor_type) != ARRAY_TYPE
	   && !gnu_ಸದಿಶ_type_p (constructor_type))
    {
      /* A nonincremental scalar initializer--just return
	 the element, after verifying there is just one.
         Empty scalar initializers are supported in C23.  */
      ಆದರೆ (vec_ಸುರಕ್ಷಿತ_is_ಖಾಲಿಗಳು (constructor_elements))
	{
	  ಆದರೆ (constructor_erroneous || constructor_type == error_mark_ಗಂಟು)
	    ret.ಮೌಲ್ಯ = error_mark_ಗಂಟು;
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (constructor_type) == FUNCTION_TYPE)
	    {
	      error_init (loc, "invalid initializer");
	      ret.ಮೌಲ್ಯ = error_mark_ಗಂಟು;
	    }
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (constructor_type) == ಸೂಚಕ_TYPE)
	    /* Ensure this is a null pointer constant in the case of a
	       'constexpr' object initialized with {}.  */
	    ret.ಮೌಲ್ಯ = build_zero_cst (ptr_type_ಗಂಟು);
	  ಇಲ್ಲದಿದ್ದರೆ
	    ret.ಮೌಲ್ಯ = build_zero_cst (constructor_type);
	}
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (vec_ಸುರಕ್ಷಿತ_ಉದ್ದಳತೆ (constructor_elements) != 1)
	{
	  error_init (loc, "extra elements in scalar initializer");
	  ret.ಮೌಲ್ಯ = (*constructor_elements)[0].ಮೌಲ್ಯ;
	}
      ಇಲ್ಲದಿದ್ದರೆ
	ret.ಮೌಲ್ಯ = (*constructor_elements)[0].ಮೌಲ್ಯ;
    }
  ಇಲ್ಲದಿದ್ದರೆ
    {
      ಆದರೆ (constructor_erroneous)
	ret.ಮೌಲ್ಯ = error_mark_ಗಂಟು;
      ಇಲ್ಲದಿದ್ದರೆ
	{
	  ret.ಮೌಲ್ಯ = build_constructor (constructor_type,
					 constructor_elements);
	  ಆದರೆ (constructor_constant)
	    ವೃಕ್ಷ_CONSTANT (ret.ಮೌಲ್ಯ) = 1;
	  ಆದರೆ (constructor_constant && constructor_simple)
	    ವೃಕ್ಷ_STATIC (ret.ಮೌಲ್ಯ) = 1;
	  ಆದರೆ (constructor_nonconst)
	    CONSTRUCTOR_NON_CONST (ret.ಮೌಲ್ಯ) = 1;
	  ಆದರೆ (constructor_zero_padding_ಬಿಟ್ಟುಗಳು)
	    CONSTRUCTOR_ZERO_PADDING_ಬಿಟ್ಟುಗಳು (ret.ಮೌಲ್ಯ) = 1;
	}
    }

  ಆದರೆ (ret.ಮೌಲ್ಯ && ವೃಕ್ಷ_ಸಂಕೇತ (ret.ಮೌಲ್ಯ) != CONSTRUCTOR)
    {
      ಆದರೆ (constructor_nonconst)
	ret.original_ಸಂಕೇತ = C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ;
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ret.original_ಸಂಕೇತ == C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ)
	ret.original_ಸಂಕೇತ = ERROR_MARK;
    }

  constructor_type = p->type;
  constructor_fields = p->fields;
  constructor_ಸೂಚ್ಯಂಕ = p->ಸೂಚ್ಯಂಕ;
  constructor_max_ಸೂಚ್ಯಂಕ = p->max_ಸೂಚ್ಯಂಕ;
  constructor_unfilled_ಸೂಚ್ಯಂಕ = p->unfilled_ಸೂಚ್ಯಂಕ;
  constructor_unfilled_fields = p->unfilled_fields;
  constructor_ಬಿಟ್_ಸೂಚ್ಯಂಕ = p->ಬಿಟ್_ಸೂಚ್ಯಂಕ;
  constructor_elements = p->elements;
  constructor_constant = p->constant;
  constructor_simple = p->simple;
  constructor_nonconst = p->nonconst;
  constructor_erroneous = p->erroneous;
  constructor_incremental = p->incremental;
  constructor_designated = p->designated;
  constructor_zero_padding_ಬಿಟ್ಟುಗಳು = p->zero_padding_ಬಿಟ್ಟುಗಳು;
  constructor_braced_scalar = p->braced_scalar;
  designator_ಆಳ = p->designator_ಆಳ;
  constructor_pending_elts = p->pending_elts;
  constructor_ಆಳ = p->ಆಳ;
  ಆದರೆ (!p->implicit)
    constructor_range_ರಾಶಿ = p->range_ರಾಶಿ;
  RESTORE_SPELLING_ಆಳ (constructor_ಆಳ);

  constructor_ರಾಶಿ = p->ಮುಂದಿನ;
  XDELETE (p);

  ಆದರೆ (ret.ಮೌಲ್ಯ == NULL_ವೃಕ್ಷ && constructor_ರಾಶಿ == 0)
    ret.ಮೌಲ್ಯ = error_mark_ಗಂಟು;
  ಹಿಂತಿರುಗಿ ret;
}

/* Common handling for both array range and field name designators.
   ARRAY argument is nonzero for array ranges.  Returns false for success.  */

ಸ್ಥಿರ ತಾರ್ಕಿಕ
ಗಣ_designator (location_t loc, ತಾರ್ಕಿಕ array,
		ರಚನೆ obstack *braced_init_obstack)
{
  ವೃಕ್ಷ subtype;
  ಎಣಿಕೆ ವೃಕ್ಷ_ಸಂಕೇತ_2 subcode;

  /* Don't die if an entire brace-pair level is superfluous
     in the containing level, or for an erroneous type.  */
  ಆದರೆ (constructor_type == NULL_ವೃಕ್ಷ || constructor_type == error_mark_ಗಂಟು)
    ಹಿಂತಿರುಗಿ ನಿಜ;

  /* If there were errors in this designator list already, bail out
     silently.  */
  ಆದರೆ (designator_erroneous)
    ಹಿಂತಿರುಗಿ ನಿಜ;

  /* Likewise for an initializer for a variable-size type.  Those are
     diagnosed in the parser, except for empty initializer braces.  */
  ಆದರೆ (COMPLETE_TYPE_P (constructor_type)
      && ವೃಕ್ಷ_ಸಂಕೇತ (TYPE_ಗಾತ್ರ (constructor_type)) != INTEGER_CST)
    ಹಿಂತಿರುಗಿ ನಿಜ;

  ಆದರೆ (!designator_ಆಳ)
    {
      gcc_assert (!constructor_range_ರಾಶಿ);

      /* Designator list starts at the level of closest explicit
	 braces.  */
      ಆಗ (constructor_ರಾಶಿ->implicit)
	process_init_element (ಒಳಹರಿವು_location,
			      ತೆಗೆ_init_level (loc, 1, braced_init_obstack,
					      ಕೊನೆಯ_init_list_comma),
			      ನಿಜ, braced_init_obstack);
      constructor_designated = 1;
      ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
    }

  ಆಯ್ಕೆ (ವೃಕ್ಷ_ಸಂಕೇತ (constructor_type))
    {
    ಸ್ಥಿತಿ  ದಾಖಲೆ_TYPE:
    ಸ್ಥಿತಿ  UNION_TYPE:
      subtype = ವೃಕ್ಷ_TYPE (constructor_fields);
      ಆದರೆ (subtype != error_mark_ಗಂಟು)
	subtype = TYPE_MAIN_VARIANT (subtype);
      ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ ARRAY_TYPE:
      subtype = TYPE_MAIN_VARIANT (ವೃಕ್ಷ_TYPE (constructor_type));
      ನಿಲ್ಲಿಸು;
    ಪೂರ್ವನಿಯೋಜಿತ:
      gcc_unreachable ();
    }

  subcode = ವೃಕ್ಷ_ಸಂಕೇತ (subtype);
  ಆದರೆ (array && subcode != ARRAY_TYPE)
    {
      error_init (loc, "array index in non-array initializer");
      ಹಿಂತಿರುಗಿ ನಿಜ;
    }
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!array && subcode != ದಾಖಲೆ_TYPE && subcode != UNION_TYPE)
    {
      error_init (loc, "field name not in record or union initializer");
      ಹಿಂತಿರುಗಿ ನಿಜ;
    }

  constructor_designated = 1;
  ಮುಕ್ತಾಯ_implicit_inits (loc, braced_init_obstack);
  ತಳ್ಳು_init_level (loc, 2, braced_init_obstack);
  ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
}

/* If there are range designators in designator list, push a new designator
   to constructor_range_stack.  RANGE_END is end of such stack range or
   NULL_TREE if there is no range designator at this level.  */

ಸ್ಥಿರ ಶೂನ್ಯ
ತಳ್ಳು_range_ರಾಶಿ (ವೃಕ್ಷ range_ಕೊನೆ, ರಚನೆ obstack * braced_init_obstack)
{
  ರಚನೆ constructor_range_ರಾಶಿ *p;

  p = (ರಚನೆ constructor_range_ರಾಶಿ *)
    obstack_alloc (braced_init_obstack,
		   ಗಾತ್ರ (ರಚನೆ constructor_range_ರಾಶಿ));
  p->prev = constructor_range_ರಾಶಿ;
  p->ಮುಂದಿನ = 0;
  p->fields = constructor_fields;
  p->range_ಆರಂಭ = constructor_ಸೂಚ್ಯಂಕ;
  p->ಸೂಚ್ಯಂಕ = constructor_ಸೂಚ್ಯಂಕ;
  p->ರಾಶಿ = constructor_ರಾಶಿ;
  p->range_ಕೊನೆ = range_ಕೊನೆ;
  ಆದರೆ (constructor_range_ರಾಶಿ)
    constructor_range_ರಾಶಿ->ಮುಂದಿನ = p;
  constructor_range_ರಾಶಿ = p;
}

/* Within an array initializer, specify the next index to be initialized.
   FIRST is that index.  If LAST is nonzero, then initialize a range
   of indices, running from FIRST through LAST.  */

ಶೂನ್ಯ
ಗಣ_init_ಸೂಚ್ಯಂಕ (location_t loc, ವೃಕ್ಷ ಮೊದಲ, ವೃಕ್ಷ ಕೊನೆಯ,
		ರಚನೆ obstack *braced_init_obstack)
{
  ಆದರೆ (ಗಣ_designator (loc, ನಿಜ, braced_init_obstack))
    ಹಿಂತಿರುಗಿ;

  designator_erroneous = 1;

  ಆದರೆ (!INTEGRAL_TYPE_P (ವೃಕ್ಷ_TYPE (ಮೊದಲ))
      || (ಕೊನೆಯ && !INTEGRAL_TYPE_P (ವೃಕ್ಷ_TYPE (ಕೊನೆಯ))))
    {
      error_init (loc, "array index in initializer not of integer type");
      ಹಿಂತಿರುಗಿ;
    }

  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ಮೊದಲ) != INTEGER_CST)
    {
      ಮೊದಲ = c_fully_fold (ಮೊದಲ, ಸುಳ್ಳು, ಖಾಲಿ);
      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ಮೊದಲ) == INTEGER_CST)
	pedwarn_init (loc, OPT_Wpedantic,
		      "array index in initializer is not "
		      "an integer constant expression");
    }

  ಆದರೆ (ಕೊನೆಯ && ವೃಕ್ಷ_ಸಂಕೇತ (ಕೊನೆಯ) != INTEGER_CST)
    {
      ಕೊನೆಯ = c_fully_fold (ಕೊನೆಯ, ಸುಳ್ಳು, ಖಾಲಿ);
      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ಕೊನೆಯ) == INTEGER_CST)
	pedwarn_init (loc, OPT_Wpedantic,
		      "array index in initializer is not "
		      "an integer constant expression");
    }

  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ಮೊದಲ) != INTEGER_CST)
    error_init (loc, "nonconstant array index in initializer");
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ಕೊನೆಯ != NULL_ವೃಕ್ಷ && ವೃಕ್ಷ_ಸಂಕೇತ (ಕೊನೆಯ) != INTEGER_CST)
    error_init (loc, "nonconstant array index in initializer");
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (constructor_type) != ARRAY_TYPE)
    error_init (loc, "array index in non-array initializer");
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ವೃಕ್ಷ_int_cst_sgn (ಮೊದಲ) == -1)
    error_init (loc, "array index in initializer exceeds array bounds");
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (constructor_max_ಸೂಚ್ಯಂಕ
	   && ವೃಕ್ಷ_int_cst_lt (constructor_max_ಸೂಚ್ಯಂಕ, ಮೊದಲ))
    error_init (loc, "array index in initializer exceeds array bounds");
  ಇಲ್ಲದಿದ್ದರೆ
    {
      constant_ಅಭಿವ್ಯಕ್ತಿ_warning (ಮೊದಲ);
      ಆದರೆ (ಕೊನೆಯ)
	constant_ಅಭಿವ್ಯಕ್ತಿ_warning (ಕೊನೆಯ);
      constructor_ಸೂಚ್ಯಂಕ = convert (bitsizetype, ಮೊದಲ);
      ಆದರೆ (ವೃಕ್ಷ_int_cst_lt (constructor_ಸೂಚ್ಯಂಕ, ಮೊದಲ))
	{
	  constructor_ಸೂಚ್ಯಂಕ = copy_ಗಂಟು (constructor_ಸೂಚ್ಯಂಕ);
	  ವೃಕ್ಷ_ಅತಿಪ್ರವಾಹ (constructor_ಸೂಚ್ಯಂಕ) = 1;
	}

      ಆದರೆ (ಕೊನೆಯ)
	{
	  ಆದರೆ (ವೃಕ್ಷ_int_cst_equal (ಮೊದಲ, ಕೊನೆಯ))
	    ಕೊನೆಯ = NULL_ವೃಕ್ಷ;
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ವೃಕ್ಷ_int_cst_lt (ಕೊನೆಯ, ಮೊದಲ))
	    {
	      error_init (loc, "empty index range in initializer");
	      ಕೊನೆಯ = NULL_ವೃಕ್ಷ;
	    }
	  ಇಲ್ಲದಿದ್ದರೆ
	    {
	      ಕೊನೆಯ = convert (bitsizetype, ಕೊನೆಯ);
	      ಆದರೆ (constructor_max_ಸೂಚ್ಯಂಕ != NULL_ವೃಕ್ಷ
		  && ವೃಕ್ಷ_int_cst_lt (constructor_max_ಸೂಚ್ಯಂಕ, ಕೊನೆಯ))
		{
		  error_init (loc, "array index range in initializer exceeds "
			      "array bounds");
		  ಕೊನೆಯ = NULL_ವೃಕ್ಷ;
		}
	    }
	}

      designator_ಆಳ++;
      designator_erroneous = 0;
      ಆದರೆ (constructor_range_ರಾಶಿ || ಕೊನೆಯ)
	ತಳ್ಳು_range_ರಾಶಿ (ಕೊನೆಯ, braced_init_obstack);
    }
}

/* Within a struct initializer, specify the next field to be initialized.  */

ಶೂನ್ಯ
ಗಣ_init_label (location_t loc, ವೃಕ್ಷ fieldname, location_t fieldname_loc,
		ರಚನೆ obstack *braced_init_obstack)
{
  ವೃಕ್ಷ ಕ್ಷೇತ್ರ_2;

  ಆದರೆ (ಗಣ_designator (loc, ಸುಳ್ಳು, braced_init_obstack))
    ಹಿಂತಿರುಗಿ;

  designator_erroneous = 1;

  ಆದರೆ (!ದಾಖಲೆ_OR_UNION_TYPE_P (constructor_type))
    {
      error_init (loc, "field name not in record or union initializer");
      ಹಿಂತಿರುಗಿ;
    }

  ಕ್ಷೇತ್ರ_2 = lookup_ಕ್ಷೇತ್ರ (constructor_type, fieldname);

  ಆದರೆ (ಕ್ಷೇತ್ರ_2 == NULL_ವೃಕ್ಷ)
    {
      ವೃಕ್ಷ guessed_id = lookup_ಕ್ಷೇತ್ರ_fuzzy (constructor_type, fieldname);
      ಆದರೆ (guessed_id)
	{
	  gcc_rich_location rich_loc (fieldname_loc);
	  rich_loc.ಕೂಡಿಸು_fixit_misspelled_id (fieldname_loc, guessed_id);
	  error_at (&rich_loc,
		    "%qT has no member named %qE; did you mean %qE?",
		    constructor_type, fieldname, guessed_id);
	}
      ಇಲ್ಲದಿದ್ದರೆ
	error_at (fieldname_loc, "%qT has no member named %qE",
		  constructor_type, fieldname);
    }
  ಇಲ್ಲದಿದ್ದರೆ
    ಮಾಡು
      {
	constructor_fields = ವೃಕ್ಷ_ಮೌಲ್ಯ (ಕ್ಷೇತ್ರ_2);
	designator_ಆಳ++;
	designator_erroneous = 0;
	ಆದರೆ (constructor_range_ರಾಶಿ)
	  ತಳ್ಳು_range_ರಾಶಿ (NULL_ವೃಕ್ಷ, braced_init_obstack);
	ಕ್ಷೇತ್ರ_2 = ವೃಕ್ಷ_CHAIN (ಕ್ಷೇತ್ರ_2);
	ಆದರೆ (ಕ್ಷೇತ್ರ_2)
	  {
	    ಆದರೆ (ಗಣ_designator (loc, ಸುಳ್ಳು, braced_init_obstack))
	      ಹಿಂತಿರುಗಿ;
	  }
      }
    ಆಗ (ಕ್ಷೇತ್ರ_2 != NULL_ವೃಕ್ಷ);
}

/* Helper function for add_pending_init.  Find inorder successor of P
   in AVL tree.  */
ಸ್ಥಿರ ರಚನೆ init_ಗಂಟು *
init_ಗಂಟು_successor (ರಚನೆ init_ಗಂಟು *p)
{
  ರಚನೆ init_ಗಂಟು *r;
  ಆದರೆ (p->ಬಲ)
    {
      r = p->ಬಲ;
      ಆಗ (r->ಎಡ)
	r = r->ಎಡ;
      ಹಿಂತಿರುಗಿ r;
    }
  r = p->ಪೋಷಕ;
  ಆಗ (r && p == r->ಬಲ)
    {
      p = r;
      r = r->ಪೋಷಕ;
    }
  ಹಿಂತಿರುಗಿ r;
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
ಕೂಡಿಸು_pending_init (location_t loc, ವೃಕ್ಷ purpose, ವೃಕ್ಷ ಮೌಲ್ಯ, ವೃಕ್ಷ origtype,
		  ತಾರ್ಕಿಕ implicit, ರಚನೆ obstack *braced_init_obstack)
{
  ರಚನೆ init_ಗಂಟು *p, **q, *r;

  q = &constructor_pending_elts;
  p = 0;

  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (constructor_type) == ARRAY_TYPE)
    {
      ಆಗ (*q != 0)
	{
	  p = *q;
	  ಆದರೆ (ವೃಕ್ಷ_int_cst_lt (purpose, p->purpose))
	    q = &p->ಎಡ;
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ವೃಕ್ಷ_int_cst_lt (p->purpose, purpose))
	    {
	      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (p->ಮೌಲ್ಯ) != RAW_ದತ್ತಾಂಶ_CST
		  || (p->ಬಲ
		      && ವೃಕ್ಷ_int_cst_le (p->ಬಲ->purpose, purpose)))
		q = &p->ಬಲ;
	      ಇಲ್ಲದಿದ್ದರೆ
		{
		  widest_int pp = wi::ಗಮ್ಯ_widest (p->purpose);
		  widest_int pw = wi::ಗಮ್ಯ_widest (purpose);
		  ಆದರೆ (pp + RAW_ದತ್ತಾಂಶ_ಉದ್ದಳತೆ (p->ಮೌಲ್ಯ) <= pw)
		    q = &p->ಬಲ;
		  ಇಲ್ಲದಿದ್ದರೆ
		    {
		      /* Override which should split the old RAW_DATA_CST
			 into 2 or 3 pieces.  */
		      ಆದರೆ (!implicit && warn_override_init)
			warning_init (loc, OPT_Woverride_init,
				      "initialized field overwritten");
		      ಚಿಹ್ನೆರಹಿತ HOST_WIDE_INT ಆರಂಭ = (pw - pp).ಗಮ್ಯ_uhwi ();
		      ಚಿಹ್ನೆರಹಿತ HOST_WIDE_INT len = 1;
		      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ಮೌಲ್ಯ) == RAW_ದತ್ತಾಂಶ_CST)
			len = RAW_ದತ್ತಾಂಶ_ಉದ್ದಳತೆ (ಮೌಲ್ಯ);
		      ಚಿಹ್ನೆರಹಿತ HOST_WIDE_INT ಕೊನೆ = 0;
		      ಚಿಹ್ನೆರಹಿತ plen = RAW_ದತ್ತಾಂಶ_ಉದ್ದಳತೆ (p->ಮೌಲ್ಯ);
		      gcc_checking_assert (ಆರಂಭ < plen && ಆರಂಭ);
		      ಆದರೆ (plen - ಆರಂಭ > len)
			ಕೊನೆ = plen - ಆರಂಭ - len;
		      ವೃಕ್ಷ v = p->ಮೌಲ್ಯ;
		      ವೃಕ್ಷ origtype = p->origtype;
		      ಆದರೆ (ಆರಂಭ == 1)
			p->ಮೌಲ್ಯ = build_int_cst (ವೃಕ್ಷ_TYPE (v),
						  RAW_ದತ್ತಾಂಶ_UCHAR_ELT (v, 0));
		      ಇಲ್ಲದಿದ್ದರೆ
			{
			  p->ಮೌಲ್ಯ = v;
			  ಆದರೆ (ಕೊನೆ > 1)
			    v = copy_ಗಂಟು (v);
			  RAW_ದತ್ತಾಂಶ_ಉದ್ದಳತೆ (p->ಮೌಲ್ಯ) = ಆರಂಭ;
			}
		      ಆದರೆ (ಕೊನೆ)
			{
			  ವೃಕ್ಷ epurpose
			    = ಗಾತ್ರ_binop (PLUS_ಅಭಿವ್ಯಕ್ತಿ, purpose,
					  bitsize_int (len));
			  ಆದರೆ (ಕೊನೆ > 1)
			    {
			      RAW_ದತ್ತಾಂಶ_ಉದ್ದಳತೆ (v) -= plen - ಕೊನೆ;
			      RAW_ದತ್ತಾಂಶ_ಸೂಚಕ (v) += plen - ಕೊನೆ;
			    }
			  ಇಲ್ಲದಿದ್ದರೆ
			    v = build_int_cst (ವೃಕ್ಷ_TYPE (v),
					       RAW_ದತ್ತಾಂಶ_UCHAR_ELT (v, plen
								      - ಕೊನೆ));
			  ಕೂಡಿಸು_pending_init (loc, epurpose, v, origtype,
					    implicit, braced_init_obstack);
			}
		      q = &constructor_pending_elts;
		      ಮುಂದುವರಿ;
		    }
		}
	    }
	  ಇಲ್ಲದಿದ್ದರೆ
	    {
	      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (p->ಮೌಲ್ಯ) == RAW_ದತ್ತಾಂಶ_CST
		  && (RAW_ದತ್ತಾಂಶ_ಉದ್ದಳತೆ (p->ಮೌಲ್ಯ)
		      > (ವೃಕ್ಷ_ಸಂಕೇತ (ಮೌಲ್ಯ) == RAW_ದತ್ತಾಂಶ_CST
			 ? RAW_ದತ್ತಾಂಶ_ಉದ್ದಳತೆ (ಮೌಲ್ಯ) : 1)))
		{
		  /* Override which should split the old RAW_DATA_CST
		     into 2 pieces.  */
		  ಆದರೆ (!implicit && warn_override_init)
		    warning_init (loc, OPT_Woverride_init,
				  "initialized field overwritten");
		  ಚಿಹ್ನೆರಹಿತ HOST_WIDE_INT len = 1;
		  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ಮೌಲ್ಯ) == RAW_ದತ್ತಾಂಶ_CST)
		    len = RAW_ದತ್ತಾಂಶ_ಉದ್ದಳತೆ (ಮೌಲ್ಯ);
		  ಆದರೆ ((ಚಿಹ್ನೆರಹಿತ) RAW_ದತ್ತಾಂಶ_ಉದ್ದಳತೆ (p->ಮೌಲ್ಯ) > len + 1)
		    {
		      RAW_ದತ್ತಾಂಶ_ಉದ್ದಳತೆ (p->ಮೌಲ್ಯ) -= len;
		      RAW_ದತ್ತಾಂಶ_ಸೂಚಕ (p->ಮೌಲ್ಯ) += len;
		    }
		  ಇಲ್ಲದಿದ್ದರೆ
		    {
		      ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ l = RAW_ದತ್ತಾಂಶ_ಉದ್ದಳತೆ (p->ಮೌಲ್ಯ) - 1;
		      p->ಮೌಲ್ಯ
			= build_int_cst (ವೃಕ್ಷ_TYPE (p->ಮೌಲ್ಯ),
					 RAW_ದತ್ತಾಂಶ_UCHAR_ELT (p->ಮೌಲ್ಯ, l));
		    }
		  p->purpose = ಗಾತ್ರ_binop (PLUS_ಅಭಿವ್ಯಕ್ತಿ, p->purpose,
					   bitsize_int (len));
		  ಮುಂದುವರಿ;
		}
	      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ಮೌಲ್ಯ) == RAW_ದತ್ತಾಂಶ_CST)
		{
		handle_raw_ದತ್ತಾಂಶ:
		  /* RAW_DATA_CST value might overlap various further
		     prior initval entries.  Find out how many.  */
		  ಚಿಹ್ನೆರಹಿತ cnt = 0;
		  widest_int w
		    = wi::ಗಮ್ಯ_widest (purpose) + RAW_ದತ್ತಾಂಶ_ಉದ್ದಳತೆ (ಮೌಲ್ಯ);
		  ರಚನೆ init_ಗಂಟು *r = p, *ಕೊನೆಯ = ಖಾಲಿ;
		  ತಾರ್ಕಿಕ override_init = warn_override_init;
		  ಆಗ ((r = init_ಗಂಟು_successor (r))
			 && wi::ಗಮ್ಯ_widest (r->purpose) < w)
		    {
		      ++cnt;
		      ಆದರೆ (ವೃಕ್ಷ_SIDE_EFFECTS (r->ಮೌಲ್ಯ))
			warning_init (loc, OPT_Woverride_init_side_effects,
				      "initialized field with side-effects "
				      "overwritten");
		      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (override_init)
			{
			  warning_init (loc, OPT_Woverride_init,
					"initialized field overwritten");
			  override_init = ಸುಳ್ಳು;
			}
		      ಕೊನೆಯ = r;
		    }
		  ಆದರೆ (cnt)
		    {
		      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ಕೊನೆಯ->ಮೌಲ್ಯ) == RAW_ದತ್ತಾಂಶ_CST
			  && (wi::ಗಮ್ಯ_widest (ಕೊನೆಯ->purpose)
			      + RAW_ದತ್ತಾಂಶ_ಉದ್ದಳತೆ (ಕೊನೆಯ->ಮೌಲ್ಯ) > w))
			{
			  /* The last overlapping prior initval overlaps
			     only partially.  Shrink it and decrease cnt.  */
			  ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ l = (wi::ಗಮ್ಯ_widest (ಕೊನೆಯ->purpose)
					    + RAW_ದತ್ತಾಂಶ_ಉದ್ದಳತೆ (ಕೊನೆಯ->ಮೌಲ್ಯ)
					    - w).ಗಮ್ಯ_uhwi ();
			  --cnt;
			  RAW_ದತ್ತಾಂಶ_ಉದ್ದಳತೆ (ಕೊನೆಯ->ಮೌಲ್ಯ) -= l;
			  RAW_ದತ್ತಾಂಶ_ಸೂಚಕ (ಕೊನೆಯ->ಮೌಲ್ಯ) += l;
			  ಆದರೆ (RAW_ದತ್ತಾಂಶ_ಉದ್ದಳತೆ (ಕೊನೆಯ->ಮೌಲ್ಯ) == 1)
			    ಕೊನೆಯ->ಮೌಲ್ಯ
			      = build_int_cst (ವೃಕ್ಷ_TYPE (ಕೊನೆಯ->ಮೌಲ್ಯ),
					       RAW_ದತ್ತಾಂಶ_UCHAR_ELT (ಕೊನೆಯ->ಮೌಲ್ಯ,
								   0));
			  ಕೊನೆಯ->purpose
			    = ಗಾತ್ರ_binop (PLUS_ಅಭಿವ್ಯಕ್ತಿ, ಕೊನೆಯ->purpose,
					  bitsize_int (l));
			}
		      /* Instead of deleting cnt nodes from the AVL tree
			 and rebalancing, peel of last cnt bytes from the
			 RAW_DATA_CST.  Overriding thousands of previously
			 initialized array elements with #embed needs to work,
			 but doesn't need to be super efficient.  */
		      gcc_checking_assert ((ಚಿಹ್ನೆರಹಿತ) RAW_ದತ್ತಾಂಶ_ಉದ್ದಳತೆ (ಮೌಲ್ಯ)
					   > cnt);
		      RAW_ದತ್ತಾಂಶ_ಉದ್ದಳತೆ (ಮೌಲ್ಯ) -= cnt;
		      ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *s
			= &RAW_ದತ್ತಾಂಶ_UCHAR_ELT (ಮೌಲ್ಯ, RAW_ದತ್ತಾಂಶ_ಉದ್ದಳತೆ (ಮೌಲ್ಯ));
		      ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ o = RAW_ದತ್ತಾಂಶ_ಉದ್ದಳತೆ (ಮೌಲ್ಯ);
		      ಗಾಗಿ (r = p; cnt--; ++o, ++s)
			{
			  r = init_ಗಂಟು_successor (r);
			  r->purpose = ಗಾತ್ರ_binop (PLUS_ಅಭಿವ್ಯಕ್ತಿ, purpose,
						   bitsize_int (o));
			  r->ಮೌಲ್ಯ = build_int_cst (ವೃಕ್ಷ_TYPE (ಮೌಲ್ಯ), *s);
			  r->origtype = origtype;
			}
		      ಆದರೆ (RAW_ದತ್ತಾಂಶ_ಉದ್ದಳತೆ (ಮೌಲ್ಯ) == 1)
			ಮೌಲ್ಯ = build_int_cst (ವೃಕ್ಷ_TYPE (ಮೌಲ್ಯ),
					       RAW_ದತ್ತಾಂಶ_UCHAR_ELT (ಮೌಲ್ಯ, 0));
		    }
		}
	      ಆದರೆ (!implicit)
		{
		  ಆದರೆ (ವೃಕ್ಷ_SIDE_EFFECTS (p->ಮೌಲ್ಯ))
		    warning_init (loc, OPT_Woverride_init_side_effects,
				  "initialized field with side-effects "
				  "overwritten");
		  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (warn_override_init)
		    warning_init (loc, OPT_Woverride_init,
				  "initialized field overwritten");
		}
	      p->ಮೌಲ್ಯ = ಮೌಲ್ಯ;
	      p->origtype = origtype;
	      ಹಿಂತಿರುಗಿ;
	    }
	}
      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ಮೌಲ್ಯ) == RAW_ದತ್ತಾಂಶ_CST && p)
	{
	  ರಚನೆ init_ಗಂಟು *r;
	  ಆದರೆ (q == &p->ಎಡ)
	    r = p;
	  ಇಲ್ಲದಿದ್ದರೆ
	    r = init_ಗಂಟು_successor (p);
	  ಆದರೆ (r && wi::ಗಮ್ಯ_widest (r->purpose) < (wi::ಗಮ್ಯ_widest (purpose)
						 + RAW_ದತ್ತಾಂಶ_ಉದ್ದಳತೆ (ಮೌಲ್ಯ)))
	    {
	      /* Overlap with at least one prior initval in the range but
		 not at the start.  */
	      p = r;
	      p->purpose = purpose;
	      ಹೋಗು handle_raw_ದತ್ತಾಂಶ;
	    }
	}
    }
  ಇಲ್ಲದಿದ್ದರೆ
    {
      ವೃಕ್ಷ bitpos;

      bitpos = ಬಿಟ್_position (purpose);
      ಆಗ (*q != ಖಾಲಿ)
	{
	  p = *q;
	  ಆದರೆ (ವೃಕ್ಷ_int_cst_lt (bitpos, ಬಿಟ್_position (p->purpose)))
	    q = &p->ಎಡ;
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (p->purpose != purpose)
	    q = &p->ಬಲ;
	  ಇಲ್ಲದಿದ್ದರೆ
	    {
	      ಆದರೆ (!implicit)
		{
		  ಆದರೆ (ವೃಕ್ಷ_SIDE_EFFECTS (p->ಮೌಲ್ಯ))
		    warning_init (loc, OPT_Woverride_init_side_effects,
				  "initialized field with side-effects "
				  "overwritten");
		  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (warn_override_init)
		    warning_init (loc, OPT_Woverride_init,
				  "initialized field overwritten");
		}
	      p->ಮೌಲ್ಯ = ಮೌಲ್ಯ;
	      p->origtype = origtype;
	      ಹಿಂತಿರುಗಿ;
	    }
	}
    }

  r = (ರಚನೆ init_ಗಂಟು *) obstack_alloc (braced_init_obstack,
					  ಗಾತ್ರ (ರಚನೆ init_ಗಂಟು));
  r->purpose = purpose;
  r->ಮೌಲ್ಯ = ಮೌಲ್ಯ;
  r->origtype = origtype;

  *q = r;
  r->ಪೋಷಕ = p;
  r->ಎಡ = 0;
  r->ಬಲ = 0;
  r->balance = 0;

  ಆಗ (p)
    {
      ರಚನೆ init_ಗಂಟು *s;

      ಆದರೆ (r == p->ಎಡ)
	{
	  ಆದರೆ (p->balance == 0)
	    p->balance = -1;
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (p->balance < 0)
	    {
	      ಆದರೆ (r->balance < 0)
		{
		  /* L rotation.  */
		  p->ಎಡ = r->ಬಲ;
		  ಆದರೆ (p->ಎಡ)
		    p->ಎಡ->ಪೋಷಕ = p;
		  r->ಬಲ = p;

		  p->balance = 0;
		  r->balance = 0;

		  s = p->ಪೋಷಕ;
		  p->ಪೋಷಕ = r;
		  r->ಪೋಷಕ = s;
		  ಆದರೆ (s)
		    {
		      ಆದರೆ (s->ಎಡ == p)
			s->ಎಡ = r;
		      ಇಲ್ಲದಿದ್ದರೆ
			s->ಬಲ = r;
		    }
		  ಇಲ್ಲದಿದ್ದರೆ
		    constructor_pending_elts = r;
		}
	      ಇಲ್ಲದಿದ್ದರೆ
		{
		  /* LR rotation.  */
		  ರಚನೆ init_ಗಂಟು *t = r->ಬಲ;

		  r->ಬಲ = t->ಎಡ;
		  ಆದರೆ (r->ಬಲ)
		    r->ಬಲ->ಪೋಷಕ = r;
		  t->ಎಡ = r;

		  p->ಎಡ = t->ಬಲ;
		  ಆದರೆ (p->ಎಡ)
		    p->ಎಡ->ಪೋಷಕ = p;
		  t->ಬಲ = p;

		  p->balance = t->balance < 0;
		  r->balance = -(t->balance > 0);
		  t->balance = 0;

		  s = p->ಪೋಷಕ;
		  p->ಪೋಷಕ = t;
		  r->ಪೋಷಕ = t;
		  t->ಪೋಷಕ = s;
		  ಆದರೆ (s)
		    {
		      ಆದರೆ (s->ಎಡ == p)
			s->ಎಡ = t;
		      ಇಲ್ಲದಿದ್ದರೆ
			s->ಬಲ = t;
		    }
		  ಇಲ್ಲದಿದ್ದರೆ
		    constructor_pending_elts = t;
		}
	      ನಿಲ್ಲಿಸು;
	    }
	  ಇಲ್ಲದಿದ್ದರೆ
	    {
	      /* p->balance == +1; growth of left side balances the node.  */
	      p->balance = 0;
	      ನಿಲ್ಲಿಸು;
	    }
	}
      ಇಲ್ಲದಿದ್ದರೆ /* r == p->right */
	{
	  ಆದರೆ (p->balance == 0)
	    /* Growth propagation from right side.  */
	    p->balance++;
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (p->balance > 0)
	    {
	      ಆದರೆ (r->balance > 0)
		{
		  /* R rotation.  */
		  p->ಬಲ = r->ಎಡ;
		  ಆದರೆ (p->ಬಲ)
		    p->ಬಲ->ಪೋಷಕ = p;
		  r->ಎಡ = p;

		  p->balance = 0;
		  r->balance = 0;

		  s = p->ಪೋಷಕ;
		  p->ಪೋಷಕ = r;
		  r->ಪೋಷಕ = s;
		  ಆದರೆ (s)
		    {
		      ಆದರೆ (s->ಎಡ == p)
			s->ಎಡ = r;
		      ಇಲ್ಲದಿದ್ದರೆ
			s->ಬಲ = r;
		    }
		  ಇಲ್ಲದಿದ್ದರೆ
		    constructor_pending_elts = r;
		}
	      ಇಲ್ಲದಿದ್ದರೆ /* r->balance == -1 */
		{
		  /* RL rotation */
		  ರಚನೆ init_ಗಂಟು *t = r->ಎಡ;

		  r->ಎಡ = t->ಬಲ;
		  ಆದರೆ (r->ಎಡ)
		    r->ಎಡ->ಪೋಷಕ = r;
		  t->ಬಲ = r;

		  p->ಬಲ = t->ಎಡ;
		  ಆದರೆ (p->ಬಲ)
		    p->ಬಲ->ಪೋಷಕ = p;
		  t->ಎಡ = p;

		  r->balance = (t->balance < 0);
		  p->balance = -(t->balance > 0);
		  t->balance = 0;

		  s = p->ಪೋಷಕ;
		  p->ಪೋಷಕ = t;
		  r->ಪೋಷಕ = t;
		  t->ಪೋಷಕ = s;
		  ಆದರೆ (s)
		    {
		      ಆದರೆ (s->ಎಡ == p)
			s->ಎಡ = t;
		      ಇಲ್ಲದಿದ್ದರೆ
			s->ಬಲ = t;
		    }
		  ಇಲ್ಲದಿದ್ದರೆ
		    constructor_pending_elts = t;
		}
	      ನಿಲ್ಲಿಸು;
	    }
	  ಇಲ್ಲದಿದ್ದರೆ
	    {
	      /* p->balance == -1; growth of right side balances the node.  */
	      p->balance = 0;
	      ನಿಲ್ಲಿಸು;
	    }
	}

      r = p;
      p = p->ಪೋಷಕ;
    }
}

/* Build AVL tree from a sorted chain.  */

ಸ್ಥಿರ ಶೂನ್ಯ
ಗಣ_nonincremental_init (ರಚನೆ obstack * braced_init_obstack)
{
  ಚಿಹ್ನೆರಹಿತ HOST_WIDE_INT ix;
  ವೃಕ್ಷ ಸೂಚ್ಯಂಕ, ಮೌಲ್ಯ;

  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (constructor_type) != ದಾಖಲೆ_TYPE
      && ವೃಕ್ಷ_ಸಂಕೇತ (constructor_type) != ARRAY_TYPE)
    ಹಿಂತಿರುಗಿ;

  FOR_EACH_CONSTRUCTOR_ELT (constructor_elements, ix, ಸೂಚ್ಯಂಕ, ಮೌಲ್ಯ)
    ಕೂಡಿಸು_pending_init (ಒಳಹರಿವು_location, ಸೂಚ್ಯಂಕ, ಮೌಲ್ಯ, NULL_ವೃಕ್ಷ, ನಿಜ,
		      braced_init_obstack);
  constructor_elements = ಖಾಲಿ;
  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (constructor_type) == ದಾಖಲೆ_TYPE)
    {
      constructor_unfilled_fields = TYPE_FIELDS (constructor_type);
      /* Skip any nameless bit fields at the beginning.  */
      ಆಗ (constructor_unfilled_fields != NULL_ವೃಕ್ಷ
	     && DECL_UNNAMED_ಬಿಟ್_ಕ್ಷೇತ್ರ (constructor_unfilled_fields))
	constructor_unfilled_fields = ವೃಕ್ಷ_CHAIN (constructor_unfilled_fields);

    }
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (constructor_type) == ARRAY_TYPE)
    {
      ಆದರೆ (TYPE_DOMAIN (constructor_type))
	constructor_unfilled_ಸೂಚ್ಯಂಕ
	  = convert (bitsizetype,
		     TYPE_MIN_ಮೌಲ್ಯ (TYPE_DOMAIN (constructor_type)));
      ಇಲ್ಲದಿದ್ದರೆ
	constructor_unfilled_ಸೂಚ್ಯಂಕ = bitsize_zero_ಗಂಟು;
    }
  constructor_incremental = 0;
}

/* Build AVL tree from a string constant.  */

ಸ್ಥಿರ ಶೂನ್ಯ
ಗಣ_nonincremental_init_from_string (ವೃಕ್ಷ str,
				     ರಚನೆ obstack * braced_init_obstack)
{
  ವೃಕ್ಷ ಮೌಲ್ಯ, purpose, type;
  HOST_WIDE_INT val[2];
  ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *p, *ಕೊನೆ;
  ಪೂರ್ಣಾಂಕ byte, wchar_ಬೈಟುಗಳು, charwidth, bitpos;

  gcc_assert (ವೃಕ್ಷ_ಸಂಕೇತ (constructor_type) == ARRAY_TYPE);

  wchar_ಬೈಟುಗಳು = TYPE_PRECISION (ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_TYPE (str))) / ಬಿಟ್ಟುಗಳು_ಪ್ರತಿ_UNIT;
  charwidth = TYPE_PRECISION (char_type_ಗಂಟು);
  gcc_assert ((ಗಾತ್ರ_t) wchar_ಬೈಟುಗಳು * charwidth
	      <= ARRAY_ಗಾತ್ರ (val) * HOST_ಬಿಟ್ಟುಗಳು_ಪ್ರತಿ_WIDE_INT);
  type = ವೃಕ್ಷ_TYPE (constructor_type);
  p = ವೃಕ್ಷ_STRING_ಸೂಚಕ (str);
  ಕೊನೆ = p + ವೃಕ್ಷ_STRING_ಉದ್ದಳತೆ (str);

  ಗಾಗಿ (purpose = bitsize_zero_ಗಂಟು;
       p < ಕೊನೆ
       && !(constructor_max_ಸೂಚ್ಯಂಕ
	    && ವೃಕ್ಷ_int_cst_lt (constructor_max_ಸೂಚ್ಯಂಕ, purpose));
       purpose = ಗಾತ್ರ_binop (PLUS_ಅಭಿವ್ಯಕ್ತಿ, purpose, bitsize_one_ಗಂಟು))
    {
      ಆದರೆ (wchar_ಬೈಟುಗಳು == 1)
	{
	  val[0] = (ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ) *p++;
	  val[1] = 0;
	}
      ಇಲ್ಲದಿದ್ದರೆ
	{
	  val[1] = 0;
	  val[0] = 0;
	  ಗಾಗಿ (byte = 0; byte < wchar_ಬೈಟುಗಳು; byte++)
	    {
	      ಆದರೆ (ಬೈಟುಗಳು_BIG_ENDIAN)
		bitpos = (wchar_ಬೈಟುಗಳು - byte - 1) * charwidth;
	      ಇಲ್ಲದಿದ್ದರೆ
		bitpos = byte * charwidth;
	      val[bitpos / HOST_ಬಿಟ್ಟುಗಳು_ಪ್ರತಿ_WIDE_INT]
		|= ((ಚಿಹ್ನೆರಹಿತ HOST_WIDE_INT) ((ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ) *p++))
		   << (bitpos % HOST_ಬಿಟ್ಟುಗಳು_ಪ್ರತಿ_WIDE_INT);
	    }
	}

      ಆದರೆ (!TYPE_UNSIGNED (type))
	{
	  bitpos = ((wchar_ಬೈಟುಗಳು - 1) * charwidth) + HOST_ಬಿಟ್ಟುಗಳು_ಪ್ರತಿ_CHAR;
	  ಆದರೆ (bitpos < HOST_ಬಿಟ್ಟುಗಳು_ಪ್ರತಿ_WIDE_INT)
	    {
	      ಆದರೆ (val[0] & (HOST_WIDE_INT_1 << (bitpos - 1)))
		{
		  val[0] |= HOST_WIDE_INT_M1U << bitpos;
		  val[1] = -1;
		}
	    }
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (bitpos == HOST_ಬಿಟ್ಟುಗಳು_ಪ್ರತಿ_WIDE_INT)
	    {
	      ಆದರೆ (val[0] < 0)
		val[1] = -1;
	    }
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (val[1] & (HOST_WIDE_INT_1
			     << (bitpos - 1 - HOST_ಬಿಟ್ಟುಗಳು_ಪ್ರತಿ_WIDE_INT)))
	    val[1] |= HOST_WIDE_INT_M1U << (bitpos - HOST_ಬಿಟ್ಟುಗಳು_ಪ್ರತಿ_WIDE_INT);
	}

      ಮೌಲ್ಯ = wide_int_ಗಮ್ಯ_ವೃಕ್ಷ (type,
				wide_int::from_array (val, 2,
						      HOST_ಬಿಟ್ಟುಗಳು_ಪ್ರತಿ_WIDE_INT * 2));
      ಕೂಡಿಸು_pending_init (ಒಳಹರಿವು_location, purpose, ಮೌಲ್ಯ, NULL_ವೃಕ್ಷ, ನಿಜ,
                        braced_init_obstack);
    }

  constructor_incremental = 0;
}

/* Return value of FIELD in pending initializer or NULL_TREE if the field was
   not initialized yet.  */

ಸ್ಥಿರ ವೃಕ್ಷ
ಕಂಡುಹಿಡಿ_init_member (ವೃಕ್ಷ ಕ್ಷೇತ್ರ_2, ರಚನೆ obstack * braced_init_obstack)
{
  ರಚನೆ init_ಗಂಟು *p;

  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (constructor_type) == ARRAY_TYPE)
    {
      ಆದರೆ (constructor_incremental
	  && ವೃಕ್ಷ_int_cst_lt (ಕ್ಷೇತ್ರ_2, constructor_unfilled_ಸೂಚ್ಯಂಕ))
	ಗಣ_nonincremental_init (braced_init_obstack);

      p = constructor_pending_elts;
      ಆಗ (p)
	{
	  ಆದರೆ (ವೃಕ್ಷ_int_cst_lt (ಕ್ಷೇತ್ರ_2, p->purpose))
	    p = p->ಎಡ;
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ವೃಕ್ಷ_int_cst_lt (p->purpose, ಕ್ಷೇತ್ರ_2))
	    p = p->ಬಲ;
	  ಇಲ್ಲದಿದ್ದರೆ
	    ಹಿಂತಿರುಗಿ p->ಮೌಲ್ಯ;
	}
    }
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (constructor_type) == ದಾಖಲೆ_TYPE)
    {
      ವೃಕ್ಷ bitpos = ಬಿಟ್_position (ಕ್ಷೇತ್ರ_2);

      ಆದರೆ (constructor_incremental
	  && (!constructor_unfilled_fields
	      || ವೃಕ್ಷ_int_cst_lt (bitpos,
				  ಬಿಟ್_position (constructor_unfilled_fields))))
	ಗಣ_nonincremental_init (braced_init_obstack);

      p = constructor_pending_elts;
      ಆಗ (p)
	{
	  ಆದರೆ (ಕ್ಷೇತ್ರ_2 == p->purpose)
	    ಹಿಂತಿರುಗಿ p->ಮೌಲ್ಯ;
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ವೃಕ್ಷ_int_cst_lt (bitpos, ಬಿಟ್_position (p->purpose)))
	    p = p->ಎಡ;
	  ಇಲ್ಲದಿದ್ದರೆ
	    p = p->ಬಲ;
	}
    }
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (constructor_type) == UNION_TYPE)
    {
      ಆದರೆ (!vec_ಸುರಕ್ಷಿತ_is_ಖಾಲಿಗಳು (constructor_elements)
	  && (constructor_elements->ಕೊನೆಯ ().ಸೂಚ್ಯಂಕ == ಕ್ಷೇತ್ರ_2))
	ಹಿಂತಿರುಗಿ constructor_elements->ಕೊನೆಯ ().ಮೌಲ್ಯ;
    }
  ಹಿಂತಿರುಗಿ NULL_ವೃಕ್ಷ;
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
		     ತಾರ್ಕಿಕ strict_string, ವೃಕ್ಷ type, ವೃಕ್ಷ ಕ್ಷೇತ್ರ_2, ತಾರ್ಕಿಕ pending,
		     ತಾರ್ಕಿಕ implicit, ರಚನೆ obstack * braced_init_obstack)
{
  ವೃಕ್ಷ semantic_type = NULL_ವೃಕ್ಷ;
  ತಾರ್ಕಿಕ maybe_const = ನಿಜ;
  ತಾರ್ಕಿಕ npc, int_const_ಅಭಿವ್ಯಕ್ತಿ, arith_const_ಅಭಿವ್ಯಕ್ತಿ;

  ಆದರೆ (type == error_mark_ಗಂಟು || ಮೌಲ್ಯ == error_mark_ಗಂಟು)
    {
      constructor_erroneous = 1;
      ಹಿಂತಿರುಗಿ;
    }
  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (ಮೌಲ್ಯ)) == ARRAY_TYPE
      && (ವೃಕ್ಷ_ಸಂಕೇತ (ಮೌಲ್ಯ) == STRING_CST
	  || ವೃಕ್ಷ_ಸಂಕೇತ (ಮೌಲ್ಯ) == COMPOUND_LITERAL_ಅಭಿವ್ಯಕ್ತಿ)
      && !(ವೃಕ್ಷ_ಸಂಕೇತ (ಮೌಲ್ಯ) == STRING_CST
	   && ವೃಕ್ಷ_ಸಂಕೇತ (type) == ARRAY_TYPE
	   && INTEGRAL_TYPE_P (ವೃಕ್ಷ_TYPE (type)))
      && !comptypes (TYPE_MAIN_VARIANT (ವೃಕ್ಷ_TYPE (ಮೌಲ್ಯ)),
		     TYPE_MAIN_VARIANT (type)))
    ಮೌಲ್ಯ = array_ಗಮ್ಯ_ಸೂಚಕ_conversion (ಒಳಹರಿವು_location, ಮೌಲ್ಯ);

  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ಮೌಲ್ಯ) == COMPOUND_LITERAL_ಅಭಿವ್ಯಕ್ತಿ
      && require_constant_ಮೌಲ್ಯ && pending)
    {
      /* As an extension, allow initializing objects with static storage
	 duration with compound literals (which are then treated just as
	 the brace enclosed list they contain).  */
      ಆದರೆ (flag_isoc99)
	pedwarn_init (loc, OPT_Wpedantic, "initializer element is not "
		      "constant");
      ವೃಕ್ಷ decl = COMPOUND_LITERAL_ಅಭಿವ್ಯಕ್ತಿ_DECL (ಮೌಲ್ಯ);
      ಮೌಲ್ಯ = DECL_INITIAL (decl);
    }

  npc = null_ಸೂಚಕ_constant_p (ಮೌಲ್ಯ);
  int_const_ಅಭಿವ್ಯಕ್ತಿ = (ವೃಕ್ಷ_ಸಂಕೇತ (ಮೌಲ್ಯ) == INTEGER_CST
		    && !ವೃಕ್ಷ_ಅತಿಪ್ರವಾಹ (ಮೌಲ್ಯ)
		    && INTEGRAL_TYPE_P (ವೃಕ್ಷ_TYPE (ಮೌಲ್ಯ)));
  /* Not fully determined before folding.  */
  arith_const_ಅಭಿವ್ಯಕ್ತಿ = ನಿಜ;
  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ಮೌಲ್ಯ) == EXCESS_PRECISION_ಅಭಿವ್ಯಕ್ತಿ)
    {
      semantic_type = ವೃಕ್ಷ_TYPE (ಮೌಲ್ಯ);
      ಮೌಲ್ಯ = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (ಮೌಲ್ಯ, 0);
    }
  ಮೌಲ್ಯ = c_fully_fold (ಮೌಲ್ಯ, require_constant_ಮೌಲ್ಯ, &maybe_const);
  /* TODO: this may not detect all cases of expressions folding to
     constants that are not arithmetic constant expressions.  */
  ಆದರೆ (!maybe_const)
    arith_const_ಅಭಿವ್ಯಕ್ತಿ = ಸುಳ್ಳು;
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!INTEGRAL_TYPE_P (ವೃಕ್ಷ_TYPE (ಮೌಲ್ಯ))
	   && ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (ಮೌಲ್ಯ)) != REAL_TYPE
	   && ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (ಮೌಲ್ಯ)) != COMPLEX_TYPE)
    arith_const_ಅಭಿವ್ಯಕ್ತಿ = ಸುಳ್ಳು;
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ಮೌಲ್ಯ) != INTEGER_CST
	   && ವೃಕ್ಷ_ಸಂಕೇತ (ಮೌಲ್ಯ) != REAL_CST
	   && ವೃಕ್ಷ_ಸಂಕೇತ (ಮೌಲ್ಯ) != COMPLEX_CST
	   && ವೃಕ್ಷ_ಸಂಕೇತ (ಮೌಲ್ಯ) != RAW_ದತ್ತಾಂಶ_CST)
    arith_const_ಅಭಿವ್ಯಕ್ತಿ = ಸುಳ್ಳು;
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ವೃಕ್ಷ_ಅತಿಪ್ರವಾಹ (ಮೌಲ್ಯ))
    arith_const_ಅಭಿವ್ಯಕ್ತಿ = ಸುಳ್ಳು;

  ಆದರೆ (ಮೌಲ್ಯ == error_mark_ಗಂಟು)
    constructor_erroneous = 1;
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!ವೃಕ್ಷ_CONSTANT (ಮೌಲ್ಯ))
    constructor_constant = 0;
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!initializer_constant_valid_p (ಮೌಲ್ಯ,
					  ವೃಕ್ಷ_TYPE (ಮೌಲ್ಯ),
					  AGGREGATE_TYPE_P (constructor_type)
					  && TYPE_ಹಿಮ್ಮುಖ_STORAGE_ಕ್ರಮ
					     (constructor_type))
	   || (ದಾಖಲೆ_OR_UNION_TYPE_P (constructor_type)
	       && DECL_C_ಬಿಟ್_ಕ್ಷೇತ್ರ (ಕ್ಷೇತ್ರ_2)
	       && ವೃಕ್ಷ_ಸಂಕೇತ (ಮೌಲ್ಯ) != INTEGER_CST))
    constructor_simple = 0;
  ಆದರೆ (!maybe_const)
    constructor_nonconst = 1;

  /* Digest the initializer and issue any errors about incompatible
     types before issuing errors about non-constant initializers.  */
  ವೃಕ್ಷ new_ಮೌಲ್ಯ = ಮೌಲ್ಯ;
  ಆದರೆ (semantic_type)
    new_ಮೌಲ್ಯ = build1 (EXCESS_PRECISION_ಅಭಿವ್ಯಕ್ತಿ, semantic_type, ಮೌಲ್ಯ);
  /* In the case of braces around a scalar initializer, the result of
     this initializer processing goes through digest_init again at the
     outer level.  In the case of a constexpr initializer for a
     pointer, avoid converting a null pointer constant to something
     that is not a null pointer constant to avoid a spurious error
     from that second processing.  */
  ಆದರೆ (!require_constexpr_ಮೌಲ್ಯ
      || !npc
      || ವೃಕ್ಷ_ಸಂಕೇತ (constructor_type) != ಸೂಚಕ_TYPE)
    new_ಮೌಲ್ಯ = digest_init (loc,
			     ದಾಖಲೆ_OR_UNION_TYPE_P (constructor_type)
			     ? ಕ್ಷೇತ್ರ_2 : constructor_fields
			     ? constructor_fields : constructor_decl,
			     type, new_ಮೌಲ್ಯ, origtype, npc,
			     int_const_ಅಭಿವ್ಯಕ್ತಿ, arith_const_ಅಭಿವ್ಯಕ್ತಿ, strict_string,
			     require_constant_ಮೌಲ್ಯ, require_constexpr_ಮೌಲ್ಯ);
  ಆದರೆ (new_ಮೌಲ್ಯ == error_mark_ಗಂಟು)
    {
      constructor_erroneous = 1;
      ಹಿಂತಿರುಗಿ;
    }
  ಆದರೆ (require_constant_ಮೌಲ್ಯ || require_constant_elements)
    constant_ಅಭಿವ್ಯಕ್ತಿ_warning (new_ಮೌಲ್ಯ);

  /* Proceed to check the constness of the original initializer.  */
  ಆದರೆ (!initializer_constant_valid_p (ಮೌಲ್ಯ, ವೃಕ್ಷ_TYPE (ಮೌಲ್ಯ)))
    {
      ಆದರೆ (require_constant_ಮೌಲ್ಯ)
	{
	  error_init (loc, "initializer element is not constant");
	  ಮೌಲ್ಯ = error_mark_ಗಂಟು;
	}
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (require_constant_elements)
	pedwarn (loc, OPT_Wpedantic,
		 "initializer element is not computable at load time");
    }
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!maybe_const
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
  ಆದರೆ (warn_cxx_compat
      && ಕ್ಷೇತ್ರ_2 != NULL_ವೃಕ್ಷ
      && ವೃಕ್ಷ_ಸಂಕೇತ (ಕ್ಷೇತ್ರ_2) == ಕ್ಷೇತ್ರ_DECL
      && DECL_ಬಿಟ್_ಕ್ಷೇತ್ರ_TYPE (ಕ್ಷೇತ್ರ_2) != NULL_ವೃಕ್ಷ
      && (TYPE_MAIN_VARIANT (DECL_ಬಿಟ್_ಕ್ಷೇತ್ರ_TYPE (ಕ್ಷೇತ್ರ_2))
	  != TYPE_MAIN_VARIANT (type))
      && ವೃಕ್ಷ_ಸಂಕೇತ (DECL_ಬಿಟ್_ಕ್ಷೇತ್ರ_TYPE (ಕ್ಷೇತ್ರ_2)) == ENUMERAL_TYPE)
    {
      ವೃಕ್ಷ checktype = origtype != NULL_ವೃಕ್ಷ ? origtype : ವೃಕ್ಷ_TYPE (ಮೌಲ್ಯ);
      ಆದರೆ (checktype != error_mark_ಗಂಟು
	  && (TYPE_MAIN_VARIANT (checktype)
	      != TYPE_MAIN_VARIANT (DECL_ಬಿಟ್_ಕ್ಷೇತ್ರ_TYPE (ಕ್ಷೇತ್ರ_2))))
	warning_init (loc, OPT_Wc___compat,
		      "enum conversion in initialization is invalid in C++");
    }

  /* If this field is empty and does not have side effects (and is not at
     the end of structure), don't do anything other than checking the
     initializer.  */
  ಆದರೆ (ಕ್ಷೇತ್ರ_2
      && (ವೃಕ್ಷ_TYPE (ಕ್ಷೇತ್ರ_2) == error_mark_ಗಂಟು
	  || (COMPLETE_TYPE_P (ವೃಕ್ಷ_TYPE (ಕ್ಷೇತ್ರ_2))
	      && integer_zerop (TYPE_ಗಾತ್ರ (ವೃಕ್ಷ_TYPE (ಕ್ಷೇತ್ರ_2)))
	      && !ವೃಕ್ಷ_SIDE_EFFECTS (new_ಮೌಲ್ಯ)
	      && (ವೃಕ್ಷ_ಸಂಕೇತ (constructor_type) == ARRAY_TYPE
		  || DECL_CHAIN (ಕ್ಷೇತ್ರ_2)))))
    ಹಿಂತಿರುಗಿ;

  /* Finally, set VALUE to the initializer value digested above.  */
  ಮೌಲ್ಯ = new_ಮೌಲ್ಯ;

  /* If this element doesn't come next in sequence,
     put it on constructor_pending_elts.  */
  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (constructor_type) == ARRAY_TYPE
      && (!constructor_incremental
	  || !ವೃಕ್ಷ_int_cst_equal (ಕ್ಷೇತ್ರ_2, constructor_unfilled_ಸೂಚ್ಯಂಕ)
	  || (ವೃಕ್ಷ_ಸಂಕೇತ (ಮೌಲ್ಯ) == RAW_ದತ್ತಾಂಶ_CST
	      && constructor_pending_elts
	      && pending)))
    {
      ಆದರೆ (constructor_incremental
	  && (ವೃಕ್ಷ_int_cst_lt (ಕ್ಷೇತ್ರ_2, constructor_unfilled_ಸೂಚ್ಯಂಕ)
	      || (ವೃಕ್ಷ_ಸಂಕೇತ (ಮೌಲ್ಯ) == RAW_ದತ್ತಾಂಶ_CST
		  && constructor_pending_elts
		  && pending)))
	ಗಣ_nonincremental_init (braced_init_obstack);

      ಕೂಡಿಸು_pending_init (loc, ಕ್ಷೇತ್ರ_2, ಮೌಲ್ಯ, origtype, implicit,
			braced_init_obstack);
      ಹಿಂತಿರುಗಿ;
    }
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (constructor_type) == ದಾಖಲೆ_TYPE
	   && (!constructor_incremental
	       || ಕ್ಷೇತ್ರ_2 != constructor_unfilled_fields))
    {
      /* We do this for records but not for unions.  In a union,
	 no matter which field is specified, it can be initialized
	 right away since it starts at the beginning of the union.  */
      ಆದರೆ (constructor_incremental)
	{
	  ಆದರೆ (!constructor_unfilled_fields)
	    ಗಣ_nonincremental_init (braced_init_obstack);
	  ಇಲ್ಲದಿದ್ದರೆ
	    {
	      ವೃಕ್ಷ bitpos, unfillpos;

	      bitpos = ಬಿಟ್_position (ಕ್ಷೇತ್ರ_2);
	      unfillpos = ಬಿಟ್_position (constructor_unfilled_fields);

	      ಆದರೆ (ವೃಕ್ಷ_int_cst_lt (bitpos, unfillpos))
		ಗಣ_nonincremental_init (braced_init_obstack);
	    }
	}

      ಕೂಡಿಸು_pending_init (loc, ಕ್ಷೇತ್ರ_2, ಮೌಲ್ಯ, origtype, implicit,
			braced_init_obstack);
      ಹಿಂತಿರುಗಿ;
    }
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (constructor_type) == UNION_TYPE
	   && !vec_ಸುರಕ್ಷಿತ_is_ಖಾಲಿಗಳು (constructor_elements))
    {
      ಆದರೆ (!implicit)
	{
	  ಆದರೆ (ವೃಕ್ಷ_SIDE_EFFECTS (constructor_elements->ಕೊನೆಯ ().ಮೌಲ್ಯ))
	    warning_init (loc, OPT_Woverride_init_side_effects,
			  "initialized field with side-effects overwritten");
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (warn_override_init)
	    warning_init (loc, OPT_Woverride_init,
			  "initialized field overwritten");
	}

      /* We can have just one union field set.  */
      constructor_elements = ಖಾಲಿ;
    }

  /* Otherwise, output this element either to
     constructor_elements or to the assembler file.  */

  constructor_elt celt = {ಕ್ಷೇತ್ರ_2, ಮೌಲ್ಯ};
  vec_ಸುರಕ್ಷಿತ_ತಳ್ಳು (constructor_elements, celt);

  /* Advance the variable that indicates sequential elements output.  */
  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (constructor_type) == ARRAY_TYPE)
    {
      ವೃಕ್ಷ inc = bitsize_one_ಗಂಟು;
      ಆದರೆ (ಮೌಲ್ಯ && ವೃಕ್ಷ_ಸಂಕೇತ (ಮೌಲ್ಯ) == RAW_ದತ್ತಾಂಶ_CST)
	inc = bitsize_int (RAW_ದತ್ತಾಂಶ_ಉದ್ದಳತೆ (ಮೌಲ್ಯ));
      constructor_unfilled_ಸೂಚ್ಯಂಕ
	= ಗಾತ್ರ_binop_loc (ಒಳಹರಿವು_location, PLUS_ಅಭಿವ್ಯಕ್ತಿ,
			  constructor_unfilled_ಸೂಚ್ಯಂಕ, inc);
    }
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (constructor_type) == ದಾಖಲೆ_TYPE)
    {
      constructor_unfilled_fields
	= DECL_CHAIN (constructor_unfilled_fields);

      /* Skip any nameless bit fields.  */
      ಆಗ (constructor_unfilled_fields != NULL_ವೃಕ್ಷ
	     && DECL_UNNAMED_ಬಿಟ್_ಕ್ಷೇತ್ರ (constructor_unfilled_fields))
	constructor_unfilled_fields
	  = DECL_CHAIN (constructor_unfilled_fields);
    }
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (constructor_type) == UNION_TYPE)
    constructor_unfilled_fields = NULL_ವೃಕ್ಷ;

  /* Now output any pending elements which have become next.  */
  ಆದರೆ (pending)
    output_pending_init_elements (0, braced_init_obstack);
}

/* For two FIELD_DECLs in the same chain, return -1 if field1
   comes before field2, 1 if field1 comes after field2 and
   0 if field1 == field2.  */

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ
init_ಕ್ಷೇತ್ರ_decl_cmp (ವೃಕ್ಷ field1, ವೃಕ್ಷ field2)
{
  ಆದರೆ (field1 == field2)
    ಹಿಂತಿರುಗಿ 0;

  ವೃಕ್ಷ bitpos1 = ಬಿಟ್_position (field1);
  ವೃಕ್ಷ bitpos2 = ಬಿಟ್_position (field2);
  ಆದರೆ (ವೃಕ್ಷ_int_cst_equal (bitpos1, bitpos2))
    {
      /* If one of the fields has non-zero bitsize, then that
	 field must be the last one in a sequence of zero
	 sized fields, fields after it will have bigger
	 bit_position.  */
      ಆದರೆ (ವೃಕ್ಷ_TYPE (field1) != error_mark_ಗಂಟು
	  && COMPLETE_TYPE_P (ವೃಕ್ಷ_TYPE (field1))
	  && integer_nonzerop (ವೃಕ್ಷ_TYPE (field1)))
	ಹಿಂತಿರುಗಿ 1;
      ಆದರೆ (ವೃಕ್ಷ_TYPE (field2) != error_mark_ಗಂಟು
	  && COMPLETE_TYPE_P (ವೃಕ್ಷ_TYPE (field2))
	  && integer_nonzerop (ವೃಕ್ಷ_TYPE (field2)))
	ಹಿಂತಿರುಗಿ -1;
      /* Otherwise, fallback to DECL_CHAIN walk to find out
	 which field comes earlier.  Walk chains of both
	 fields, so that if field1 and field2 are close to each
	 other in either order, it is found soon even for large
	 sequences of zero sized fields.  */
      ವೃಕ್ಷ f1 = field1, f2 = field2;
      ಆಗ (1)
	{
	  f1 = DECL_CHAIN (f1);
	  f2 = DECL_CHAIN (f2);
	  ಆದರೆ (f1 == NULL_ವೃಕ್ಷ)
	    {
	      gcc_assert (f2);
	      ಹಿಂತಿರುಗಿ 1;
	    }
	  ಆದರೆ (f2 == NULL_ವೃಕ್ಷ)
	    ಹಿಂತಿರುಗಿ -1;
	  ಆದರೆ (f1 == field2)
	    ಹಿಂತಿರುಗಿ -1;
	  ಆದರೆ (f2 == field1)
	    ಹಿಂತಿರುಗಿ 1;
	  ಆದರೆ (!ವೃಕ್ಷ_int_cst_equal (ಬಿಟ್_position (f1), bitpos1))
	    ಹಿಂತಿರುಗಿ 1;
	  ಆದರೆ (!ವೃಕ್ಷ_int_cst_equal (ಬಿಟ್_position (f2), bitpos1))
	    ಹಿಂತಿರುಗಿ -1;
	}
    }
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ವೃಕ್ಷ_int_cst_lt (bitpos1, bitpos2))
    ಹಿಂತಿರುಗಿ -1;
  ಇಲ್ಲದಿದ್ದರೆ
    ಹಿಂತಿರುಗಿ 1;
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
output_pending_init_elements (ಪೂರ್ಣಾಂಕ all, ರಚನೆ obstack * braced_init_obstack)
{
  ರಚನೆ init_ಗಂಟು *elt = constructor_pending_elts;
  ವೃಕ್ಷ ಮುಂದಿನ;

 retry:

  /* Look through the whole pending tree.
     If we find an element that should be output now,
     output it.  Otherwise, set NEXT to the element
     that comes first among those still pending.  */

  ಮುಂದಿನ = NULL_ವೃಕ್ಷ;
  ಆಗ (elt)
    {
      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (constructor_type) == ARRAY_TYPE)
	{
	  ಆದರೆ (ವೃಕ್ಷ_int_cst_equal (elt->purpose,
				  constructor_unfilled_ಸೂಚ್ಯಂಕ))
	    output_init_element (ಒಳಹರಿವು_location, elt->ಮೌಲ್ಯ, elt->origtype,
				 ನಿಜ, ವೃಕ್ಷ_TYPE (constructor_type),
				 constructor_unfilled_ಸೂಚ್ಯಂಕ, ಸುಳ್ಳು, ಸುಳ್ಳು,
				 braced_init_obstack);
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ವೃಕ್ಷ_int_cst_lt (constructor_unfilled_ಸೂಚ್ಯಂಕ,
				    elt->purpose))
	    {
	      /* Advance to the next smaller node.  */
	      ಆದರೆ (elt->ಎಡ)
		elt = elt->ಎಡ;
	      ಇಲ್ಲದಿದ್ದರೆ
		{
		  /* We have reached the smallest node bigger than the
		     current unfilled index.  Fill the space first.  */
		  ಮುಂದಿನ = elt->purpose;
		  ನಿಲ್ಲಿಸು;
		}
	    }
	  ಇಲ್ಲದಿದ್ದರೆ
	    {
	      /* Advance to the next bigger node.  */
	      ಆದರೆ (elt->ಬಲ)
		elt = elt->ಬಲ;
	      ಇಲ್ಲದಿದ್ದರೆ
		{
		  /* We have reached the biggest node in a subtree.  Find
		     the parent of it, which is the next bigger node.  */
		  ಆಗ (elt->ಪೋಷಕ && elt->ಪೋಷಕ->ಬಲ == elt)
		    elt = elt->ಪೋಷಕ;
		  elt = elt->ಪೋಷಕ;
		  ಆದರೆ (elt && ವೃಕ್ಷ_int_cst_lt (constructor_unfilled_ಸೂಚ್ಯಂಕ,
					      elt->purpose))
		    {
		      ಮುಂದಿನ = elt->purpose;
		      ನಿಲ್ಲಿಸು;
		    }
		}
	    }
	}
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ದಾಖಲೆ_OR_UNION_TYPE_P (constructor_type))
	{
	  /* If the current record is complete we are done.  */
	  ಆದರೆ (constructor_unfilled_fields == NULL_ವೃಕ್ಷ)
	    ನಿಲ್ಲಿಸು;

	  ಪೂರ್ಣಾಂಕ cmp = init_ಕ್ಷೇತ್ರ_decl_cmp (constructor_unfilled_fields,
					 elt->purpose);
	  ಆದರೆ (cmp == 0)
	    output_init_element (ಒಳಹರಿವು_location, elt->ಮೌಲ್ಯ, elt->origtype,
				 ನಿಜ, ವೃಕ್ಷ_TYPE (elt->purpose),
				 elt->purpose, ಸುಳ್ಳು, ಸುಳ್ಳು,
				 braced_init_obstack);
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (cmp < 0)
	    {
	      /* Advance to the next smaller node.  */
	      ಆದರೆ (elt->ಎಡ)
		elt = elt->ಎಡ;
	      ಇಲ್ಲದಿದ್ದರೆ
		{
		  /* We have reached the smallest node bigger than the
		     current unfilled field.  Fill the space first.  */
		  ಮುಂದಿನ = elt->purpose;
		  ನಿಲ್ಲಿಸು;
		}
	    }
	  ಇಲ್ಲದಿದ್ದರೆ
	    {
	      /* Advance to the next bigger node.  */
	      ಆದರೆ (elt->ಬಲ)
		elt = elt->ಬಲ;
	      ಇಲ್ಲದಿದ್ದರೆ
		{
		  /* We have reached the biggest node in a subtree.  Find
		     the parent of it, which is the next bigger node.  */
		  ಆಗ (elt->ಪೋಷಕ && elt->ಪೋಷಕ->ಬಲ == elt)
		    elt = elt->ಪೋಷಕ;
		  elt = elt->ಪೋಷಕ;
		  ಆದರೆ (elt
		      && init_ಕ್ಷೇತ್ರ_decl_cmp (constructor_unfilled_fields,
					      elt->purpose) < 0)
		    {
		      ಮುಂದಿನ = elt->purpose;
		      ನಿಲ್ಲಿಸು;
		    }
		}
	    }
	}
    }

  /* Ordinarily return, but not if we want to output all
     and there are elements left.  */
  ಆದರೆ (!(all && ಮುಂದಿನ != NULL_ವೃಕ್ಷ))
    ಹಿಂತಿರುಗಿ;

  /* If it's not incremental, just skip over the gap, so that after
     jumping to retry we will output the next successive element.  */
  ಆದರೆ (ದಾಖಲೆ_OR_UNION_TYPE_P (constructor_type))
    constructor_unfilled_fields = ಮುಂದಿನ;
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (constructor_type) == ARRAY_TYPE)
    constructor_unfilled_ಸೂಚ್ಯಂಕ = ಮುಂದಿನ;

  /* ELT now points to the node in the pending tree with the next
     initializer to output.  */
  ಹೋಗು retry;
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
  ಆದರೆ (type == error_mark_ಗಂಟು || ಮೌಲ್ಯ == error_mark_ಗಂಟು)
    ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;

  gcc_checking_assert (TYPE_MAIN_VARIANT (type) == type);

  ವೃಕ್ಷ ಮೌಲ್ಯ_type = ವೃಕ್ಷ_TYPE (ಮೌಲ್ಯ);
  ಆದರೆ (ಮೌಲ್ಯ_type == error_mark_ಗಂಟು)
    ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;

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
  ಆದರೆ (gnu_ಸದಿಶ_type_p (type))
    ಹಿಂತಿರುಗಿ !ಸದಿಶ_TYPE_P (ಮೌಲ್ಯ_type);

  ಆದರೆ (AGGREGATE_TYPE_P (type))
    ಹಿಂತಿರುಗಿ !comptypes (type, TYPE_MAIN_VARIANT (ಮೌಲ್ಯ_type));

  ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
}

/* Helper function for process_init_element.  Split first element of
   RAW_DATA_CST and save the rest to *RAW_DATA.  */

ಸ್ಥಿರ ಸಾಲೊಳಗೆ ವೃಕ್ಷ
maybe_ವಿಭಜಿಸು_raw_ದತ್ತಾಂಶ (ವೃಕ್ಷ ಮೌಲ್ಯ, ವೃಕ್ಷ *raw_ದತ್ತಾಂಶ)
{
  ಆದರೆ (ಮೌಲ್ಯ == NULL_ವೃಕ್ಷ || ವೃಕ್ಷ_ಸಂಕೇತ (ಮೌಲ್ಯ) != RAW_ದತ್ತಾಂಶ_CST)
    ಹಿಂತಿರುಗಿ ಮೌಲ್ಯ;
  *raw_ದತ್ತಾಂಶ = ಮೌಲ್ಯ;
  ಮೌಲ್ಯ = build_int_cst (integer_type_ಗಂಟು,
			 RAW_ದತ್ತಾಂಶ_UCHAR_ELT (*raw_ದತ್ತಾಂಶ, 0));
  ++RAW_ದತ್ತಾಂಶ_ಸೂಚಕ (*raw_ದತ್ತಾಂಶ);
  --RAW_ದತ್ತಾಂಶ_ಉದ್ದಳತೆ (*raw_ದತ್ತಾಂಶ);
  ಹಿಂತಿರುಗಿ ಮೌಲ್ಯ;
}

/* Return non-zero if c_parser_initval should attempt to optimize
   large initializers into RAW_DATA_CST.  In that case return how
   many elements to optimize at most.  */

ಚಿಹ್ನೆರಹಿತ
c_maybe_optimize_large_byte_initializer (ಶೂನ್ಯ)
{
  ಆದರೆ (!constructor_type
      || ವೃಕ್ಷ_ಸಂಕೇತ (constructor_type) != ARRAY_TYPE
      || constructor_ರಾಶಿ->implicit)
    ಹಿಂತಿರುಗಿ 0;
  ವೃಕ್ಷ elttype = TYPE_MAIN_VARIANT (ವೃಕ್ಷ_TYPE (constructor_type));
  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (elttype) != INTEGER_TYPE
      && ವೃಕ್ಷ_ಸಂಕೇತ (elttype) != BITINT_TYPE)
    ಹಿಂತಿರುಗಿ 0;
  ಆದರೆ (TYPE_PRECISION (elttype) != CHAR_ಬಿಟ್
      || constructor_ರಾಶಿ->replacement_ಮೌಲ್ಯ.ಮೌಲ್ಯ
      || (COMPLETE_TYPE_P (constructor_type)
	  && !poly_int_ವೃಕ್ಷ_p (TYPE_ಗಾತ್ರ (constructor_type)))
      || constructor_range_ರಾಶಿ)
    ಹಿಂತಿರುಗಿ 0;
  ಆದರೆ (constructor_max_ಸೂಚ್ಯಂಕ == NULL_ವೃಕ್ಷ)
    ಹಿಂತಿರುಗಿ ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ;
  ಆದರೆ (ವೃಕ್ಷ_int_cst_le (constructor_max_ಸೂಚ್ಯಂಕ, constructor_ಸೂಚ್ಯಂಕ)
      || integer_all_onesp (constructor_max_ಸೂಚ್ಯಂಕ))
    ಹಿಂತಿರುಗಿ 0;
  widest_int w = wi::ಗಮ್ಯ_widest (constructor_max_ಸೂಚ್ಯಂಕ);
  w -= wi::ಗಮ್ಯ_widest (constructor_ಸೂಚ್ಯಂಕ);
  w += 1;
  ಆದರೆ (w < 64)
    ಹಿಂತಿರುಗಿ 0;
  ಆದರೆ (w > ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ)
    ಹಿಂತಿರುಗಿ ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ;
  ಹಿಂತಿರುಗಿ w.ಗಮ್ಯ_uhwi ();
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
process_init_element (location_t loc, ರಚನೆ c_ಅಭಿವ್ಯಕ್ತಿ ಮೌಲ್ಯ, ತಾರ್ಕಿಕ implicit,
		      ರಚನೆ obstack * braced_init_obstack)
{
  ವೃಕ್ಷ orig_ಮೌಲ್ಯ = ಮೌಲ್ಯ.ಮೌಲ್ಯ;
  ಪೂರ್ಣಾಂಕ string_flag
    = (orig_ಮೌಲ್ಯ != NULL_ವೃಕ್ಷ && ವೃಕ್ಷ_ಸಂಕೇತ (orig_ಮೌಲ್ಯ) == STRING_CST);
  ತಾರ್ಕಿಕ strict_string = ಮೌಲ್ಯ.original_ಸಂಕೇತ == STRING_CST;
  ತಾರ್ಕಿಕ was_designated = designator_ಆಳ != 0;
  ವೃಕ್ಷ raw_ದತ್ತಾಂಶ = NULL_ವೃಕ್ಷ;

retry:
  designator_ಆಳ = 0;
  designator_erroneous = 0;

  ಆದರೆ (!implicit && ಮೌಲ್ಯ.ಮೌಲ್ಯ && !integer_zerop (ಮೌಲ್ಯ.ಮೌಲ್ಯ))
    constructor_zeroinit = 0;

  /* Handle superfluous braces around string cst as in
     char x[] = {"foo"}; */
  ಆದರೆ (constructor_type
      && !was_designated
      && ವೃಕ್ಷ_ಸಂಕೇತ (constructor_type) == ARRAY_TYPE
      && INTEGRAL_TYPE_P (ವೃಕ್ಷ_TYPE (constructor_type))
      && integer_zerop (constructor_unfilled_ಸೂಚ್ಯಂಕ))
    {
      ಆದರೆ (constructor_ರಾಶಿ->replacement_ಮೌಲ್ಯ.ಮೌಲ್ಯ)
	{
	  error_init (loc, "excess elements in %qT initializer", constructor_type);
	  ಹಿಂತಿರುಗಿ;
	}
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (string_flag)
	{
	  constructor_ರಾಶಿ->replacement_ಮೌಲ್ಯ = ಮೌಲ್ಯ;
	  ಹಿಂತಿರುಗಿ;
	}
    }

  ಆದರೆ (constructor_ರಾಶಿ->replacement_ಮೌಲ್ಯ.ಮೌಲ್ಯ != NULL_ವೃಕ್ಷ)
    {
      error_init (loc, "excess elements in struct initializer");
      ಹಿಂತಿರುಗಿ;
    }

  /* Ignore elements of a brace group if it is entirely superfluous
     and has already been diagnosed, or if the type is erroneous.  */
  ಆದರೆ (constructor_type == NULL_ವೃಕ್ಷ || constructor_type == error_mark_ಗಂಟು)
    ಹಿಂತಿರುಗಿ;

  /* Ignore elements of an initializer for a variable-size type.
     Those are diagnosed in the parser (empty initializer braces are OK).  */
  ಆದರೆ (COMPLETE_TYPE_P (constructor_type)
      && !poly_int_ವೃಕ್ಷ_p (TYPE_ಗಾತ್ರ (constructor_type)))
    ಹಿಂತಿರುಗಿ;

  ಆದರೆ (!implicit && warn_designated_init && !was_designated
      && ವೃಕ್ಷ_ಸಂಕೇತ (constructor_type) == ದಾಖಲೆ_TYPE
      && lookup_attribute ("designated_init",
			   TYPE_ಗುಣಲಕ್ಷಣಗಳು (constructor_type)))
    warning_init (loc,
		  OPT_Wdesignated_init,
		  "positional initialization of field "
		  "in %<struct%> declared with %<designated_init%> attribute");

  /* If we've exhausted any levels that didn't have braces,
     pop them now.  */
  ಆಗ (constructor_ರಾಶಿ->implicit)
    {
      ಆದರೆ (ದಾಖಲೆ_OR_UNION_TYPE_P (constructor_type)
	  && constructor_fields == NULL_ವೃಕ್ಷ)
	process_init_element (loc,
			      ತೆಗೆ_init_level (loc, 1, braced_init_obstack,
					      ಕೊನೆಯ_init_list_comma),
			      ನಿಜ, braced_init_obstack);
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ ((ವೃಕ್ಷ_ಸಂಕೇತ (constructor_type) == ARRAY_TYPE
		|| gnu_ಸದಿಶ_type_p (constructor_type))
	       && constructor_max_ಸೂಚ್ಯಂಕ
	       && ವೃಕ್ಷ_int_cst_lt (constructor_max_ಸೂಚ್ಯಂಕ,
				   constructor_ಸೂಚ್ಯಂಕ))
	process_init_element (loc,
			      ತೆಗೆ_init_level (loc, 1, braced_init_obstack,
					      ಕೊನೆಯ_init_list_comma),
			      ನಿಜ, braced_init_obstack);
      ಇಲ್ಲದಿದ್ದರೆ
	ನಿಲ್ಲಿಸು;
    }

  /* In the case of [LO ... HI] = VALUE, only evaluate VALUE once.  */
  ಆದರೆ (constructor_range_ರಾಶಿ)
    {
      /* If value is a compound literal and we'll be just using its
	 content, don't put it into a SAVE_EXPR.  */
      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ಮೌಲ್ಯ.ಮೌಲ್ಯ) != COMPOUND_LITERAL_ಅಭಿವ್ಯಕ್ತಿ
	  || !require_constant_ಮೌಲ್ಯ)
	{
	  ವೃಕ್ಷ semantic_type = NULL_ವೃಕ್ಷ;
	  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ಮೌಲ್ಯ.ಮೌಲ್ಯ) == EXCESS_PRECISION_ಅಭಿವ್ಯಕ್ತಿ)
	    {
	      semantic_type = ವೃಕ್ಷ_TYPE (ಮೌಲ್ಯ.ಮೌಲ್ಯ);
	      ಮೌಲ್ಯ.ಮೌಲ್ಯ = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (ಮೌಲ್ಯ.ಮೌಲ್ಯ, 0);
	    }
	  ಮೌಲ್ಯ.ಮೌಲ್ಯ = save_ಅಭಿವ್ಯಕ್ತಿ (ಮೌಲ್ಯ.ಮೌಲ್ಯ);
	  ಆದರೆ (semantic_type)
	    ಮೌಲ್ಯ.ಮೌಲ್ಯ = build1 (EXCESS_PRECISION_ಅಭಿವ್ಯಕ್ತಿ, semantic_type,
				  ಮೌಲ್ಯ.ಮೌಲ್ಯ);
	}
    }

  ಆಗ (1)
    {
      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (constructor_type) == ದಾಖಲೆ_TYPE)
	{
	  ವೃಕ್ಷ fieldtype;
	  ಎಣಿಕೆ ವೃಕ್ಷ_ಸಂಕೇತ_2 fieldcode;

	  ಆದರೆ (constructor_fields == NULL_ವೃಕ್ಷ)
	    {
	      pedwarn_init (loc, 0, "excess elements in struct initializer");
	      ನಿಲ್ಲಿಸು;
	    }

	  fieldtype = ವೃಕ್ಷ_TYPE (constructor_fields);
	  ಆದರೆ (fieldtype != error_mark_ಗಂಟು)
	    fieldtype = TYPE_MAIN_VARIANT (fieldtype);
	  fieldcode = ವೃಕ್ಷ_ಸಂಕೇತ (fieldtype);

	  /* Error for non-static initialization of a flexible array member.  */
	  ಆದರೆ (fieldcode == ARRAY_TYPE
	      && !require_constant_ಮೌಲ್ಯ
	      && TYPE_ಗಾತ್ರ (fieldtype) == NULL_ವೃಕ್ಷ
	      && DECL_CHAIN (constructor_fields) == NULL_ವೃಕ್ಷ)
	    {
	      error_init (loc, "non-static initialization of a flexible "
			  "array member");
	      ನಿಲ್ಲಿಸು;
	    }

	  /* Error for initialization of a flexible array member with
	     a string constant if the structure is in an array.  E.g.:
	     struct S { int x; char y[]; };
	     struct S s[] = { { 1, "foo" } };
	     is invalid.  */
	  ಆದರೆ (string_flag
	      && fieldcode == ARRAY_TYPE
	      && constructor_ಆಳ > 1
	      && TYPE_ಗಾತ್ರ (fieldtype) == NULL_ವೃಕ್ಷ
	      && DECL_CHAIN (constructor_fields) == NULL_ವೃಕ್ಷ)
	    {
	      ತಾರ್ಕಿಕ ಒಳ_array_p = ಸುಳ್ಳು;
	      ಗಾಗಿ (ರಚನೆ constructor_ರಾಶಿ *p = constructor_ರಾಶಿ;
		   p && p->type; p = p->ಮುಂದಿನ)
		ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (p->type) == ARRAY_TYPE)
		  {
		    ಒಳ_array_p = ನಿಜ;
		    ನಿಲ್ಲಿಸು;
		  }
	      ಆದರೆ (ಒಳ_array_p)
		{
		  error_init (loc, "initialization of flexible array "
			      "member in a nested context");
		  ನಿಲ್ಲಿಸು;
		}
	    }

	  /* Accept a string constant to initialize a subarray.  */
	  ಆದರೆ (ಮೌಲ್ಯ.ಮೌಲ್ಯ != NULL_ವೃಕ್ಷ
	      && fieldcode == ARRAY_TYPE
	      && INTEGRAL_TYPE_P (ವೃಕ್ಷ_TYPE (fieldtype))
	      && string_flag)
	    ಮೌಲ್ಯ.ಮೌಲ್ಯ = orig_ಮೌಲ್ಯ;
	  /* Otherwise, if we have come to a subaggregate,
	     and we don't have an element of its type, push into it.  */
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ಮೌಲ್ಯ.ಮೌಲ್ಯ != NULL_ವೃಕ್ಷ
		   && initialize_elementwise_p (fieldtype, ಮೌಲ್ಯ.ಮೌಲ್ಯ))
	    {
	      ತಳ್ಳು_init_level (loc, 1, braced_init_obstack);
	      ಮುಂದುವರಿ;
	    }

	  ಮೌಲ್ಯ.ಮೌಲ್ಯ = maybe_ವಿಭಜಿಸು_raw_ದತ್ತಾಂಶ (ಮೌಲ್ಯ.ಮೌಲ್ಯ, &raw_ದತ್ತಾಂಶ);
	  ಆದರೆ (ಮೌಲ್ಯ.ಮೌಲ್ಯ)
	    {
	      ತಳ್ಳು_member_name (constructor_fields);
	      output_init_element (loc, ಮೌಲ್ಯ.ಮೌಲ್ಯ, ಮೌಲ್ಯ.original_type,
				   strict_string, fieldtype,
				   constructor_fields, ನಿಜ, implicit,
				   braced_init_obstack);
	      RESTORE_SPELLING_ಆಳ (constructor_ಆಳ);
	    }
	  ಇಲ್ಲದಿದ್ದರೆ
	    /* Do the bookkeeping for an element that was
	       directly output as a constructor.  */
	    {
	      /* For a record, keep track of end position of last field.  */
	      ಆದರೆ (DECL_ಗಾತ್ರ (constructor_fields))
		constructor_ಬಿಟ್_ಸೂಚ್ಯಂಕ
		  = ಗಾತ್ರ_binop_loc (ಒಳಹರಿವು_location, PLUS_ಅಭಿವ್ಯಕ್ತಿ,
				    ಬಿಟ್_position (constructor_fields),
				    DECL_ಗಾತ್ರ (constructor_fields));

	      /* If the current field was the first one not yet written out,
		 it isn't now, so update.  */
	      ಆದರೆ (constructor_unfilled_fields == constructor_fields)
		{
		  constructor_unfilled_fields = DECL_CHAIN (constructor_fields);
		  /* Skip any nameless bit fields.  */
		  ಆಗ (constructor_unfilled_fields != 0
			 && (DECL_UNNAMED_ಬಿಟ್_ಕ್ಷೇತ್ರ
			     (constructor_unfilled_fields)))
		    constructor_unfilled_fields =
		      DECL_CHAIN (constructor_unfilled_fields);
		}
	    }

	  constructor_fields = DECL_CHAIN (constructor_fields);
	  /* Skip any nameless bit fields at the beginning.  */
	  ಆಗ (constructor_fields != NULL_ವೃಕ್ಷ
		 && DECL_UNNAMED_ಬಿಟ್_ಕ್ಷೇತ್ರ (constructor_fields))
	    constructor_fields = DECL_CHAIN (constructor_fields);
	}
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (constructor_type) == UNION_TYPE)
	{
	  ವೃಕ್ಷ fieldtype;
	  ಎಣಿಕೆ ವೃಕ್ಷ_ಸಂಕೇತ_2 fieldcode;

	  ಆದರೆ (constructor_fields == NULL_ವೃಕ್ಷ)
	    {
	      pedwarn_init (loc, 0,
			    "excess elements in union initializer");
	      ನಿಲ್ಲಿಸು;
	    }

	  fieldtype = ವೃಕ್ಷ_TYPE (constructor_fields);
	  ಆದರೆ (fieldtype != error_mark_ಗಂಟು)
	    fieldtype = TYPE_MAIN_VARIANT (fieldtype);
	  fieldcode = ವೃಕ್ಷ_ಸಂಕೇತ (fieldtype);

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
	  ಆದರೆ (!ಒಳ_system_ಶೀರ್ಷಿಕೆ_at (ಒಳಹರಿವು_location) && !constructor_designated
	      && !(ಮೌಲ್ಯ.ಮೌಲ್ಯ && (integer_zerop (ಮೌಲ್ಯ.ಮೌಲ್ಯ)
				   || real_zerop (ಮೌಲ್ಯ.ಮೌಲ್ಯ))))
	    warning (OPT_Wtraditional, "traditional C rejects initialization "
		     "of unions");

	  /* Error for non-static initialization of a flexible array member.  */
	  ಆದರೆ (fieldcode == ARRAY_TYPE
	      && !require_constant_ಮೌಲ್ಯ
	      && TYPE_ಗಾತ್ರ (fieldtype) == NULL_ವೃಕ್ಷ)
	    {
	      error_init (loc, "non-static initialization of a flexible "
			  "array member");
	      ನಿಲ್ಲಿಸು;
	    }

	  /* Error for initialization of a flexible array member with
	     a string constant if the structure is in an array.  E.g.:
	     union U { int x; char y[]; };
	     union U s[] = { { 1, "foo" } };
	     is invalid.  */
	  ಆದರೆ (string_flag
	      && fieldcode == ARRAY_TYPE
	      && constructor_ಆಳ > 1
	      && TYPE_ಗಾತ್ರ (fieldtype) == NULL_ವೃಕ್ಷ)
	    {
	      ತಾರ್ಕಿಕ ಒಳ_array_p = ಸುಳ್ಳು;
	      ಗಾಗಿ (ರಚನೆ constructor_ರಾಶಿ *p = constructor_ರಾಶಿ;
		   p && p->type; p = p->ಮುಂದಿನ)
		ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (p->type) == ARRAY_TYPE)
		  {
		    ಒಳ_array_p = ನಿಜ;
		    ನಿಲ್ಲಿಸು;
		  }
	      ಆದರೆ (ಒಳ_array_p)
		{
		  error_init (loc, "initialization of flexible array "
			      "member in a nested context");
		  ನಿಲ್ಲಿಸು;
		}
	    }

	  /* Accept a string constant to initialize a subarray.  */
	  ಆದರೆ (ಮೌಲ್ಯ.ಮೌಲ್ಯ != NULL_ವೃಕ್ಷ
	      && fieldcode == ARRAY_TYPE
	      && INTEGRAL_TYPE_P (ವೃಕ್ಷ_TYPE (fieldtype))
	      && string_flag)
	    ಮೌಲ್ಯ.ಮೌಲ್ಯ = orig_ಮೌಲ್ಯ;
	  /* Otherwise, if we have come to a subaggregate,
	     and we don't have an element of its type, push into it.  */
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ಮೌಲ್ಯ.ಮೌಲ್ಯ != NULL_ವೃಕ್ಷ
		   && initialize_elementwise_p (fieldtype, ಮೌಲ್ಯ.ಮೌಲ್ಯ))
	    {
	      ತಳ್ಳು_init_level (loc, 1, braced_init_obstack);
	      ಮುಂದುವರಿ;
	    }

	  ಮೌಲ್ಯ.ಮೌಲ್ಯ = maybe_ವಿಭಜಿಸು_raw_ದತ್ತಾಂಶ (ಮೌಲ್ಯ.ಮೌಲ್ಯ, &raw_ದತ್ತಾಂಶ);
	  ಆದರೆ (ಮೌಲ್ಯ.ಮೌಲ್ಯ)
	    {
	      ತಳ್ಳು_member_name (constructor_fields);
	      output_init_element (loc, ಮೌಲ್ಯ.ಮೌಲ್ಯ, ಮೌಲ್ಯ.original_type,
				   strict_string, fieldtype,
				   constructor_fields, ನಿಜ, implicit,
				   braced_init_obstack);
	      RESTORE_SPELLING_ಆಳ (constructor_ಆಳ);
	    }
	  ಇಲ್ಲದಿದ್ದರೆ
	    /* Do the bookkeeping for an element that was
	       directly output as a constructor.  */
	    {
	      constructor_ಬಿಟ್_ಸೂಚ್ಯಂಕ = DECL_ಗಾತ್ರ (constructor_fields);
	      constructor_unfilled_fields = DECL_CHAIN (constructor_fields);
	    }

	  constructor_fields = NULL_ವೃಕ್ಷ;
	}
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (constructor_type) == ARRAY_TYPE)
	{
	  ವೃಕ್ಷ elttype = TYPE_MAIN_VARIANT (ವೃಕ್ಷ_TYPE (constructor_type));
	  ಎಣಿಕೆ ವೃಕ್ಷ_ಸಂಕೇತ_2 eltcode = ವೃಕ್ಷ_ಸಂಕೇತ (elttype);

	  /* Accept a string constant to initialize a subarray.  */
	  ಆದರೆ (ಮೌಲ್ಯ.ಮೌಲ್ಯ != NULL_ವೃಕ್ಷ
	      && eltcode == ARRAY_TYPE
	      && INTEGRAL_TYPE_P (ವೃಕ್ಷ_TYPE (elttype))
	      && string_flag)
	    ಮೌಲ್ಯ.ಮೌಲ್ಯ = orig_ಮೌಲ್ಯ;
	  /* Otherwise, if we have come to a subaggregate,
	     and we don't have an element of its type, push into it.  */
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ಮೌಲ್ಯ.ಮೌಲ್ಯ != NULL_ವೃಕ್ಷ
		   && initialize_elementwise_p (elttype, ಮೌಲ್ಯ.ಮೌಲ್ಯ))
	    {
	      ತಳ್ಳು_init_level (loc, 1, braced_init_obstack);
	      ಮುಂದುವರಿ;
	    }

	  ಆದರೆ (constructor_max_ಸೂಚ್ಯಂಕ != NULL_ವೃಕ್ಷ
	      && (ವೃಕ್ಷ_int_cst_lt (constructor_max_ಸೂಚ್ಯಂಕ, constructor_ಸೂಚ್ಯಂಕ)
		  || integer_all_onesp (constructor_max_ಸೂಚ್ಯಂಕ))
	      /* For VLA we got an error already.  */
	      && !C_TYPE_VARIABLE_ಗಾತ್ರ (constructor_type))
	    {
	      pedwarn_init (loc, 0,
			    "excess elements in array initializer");
	      ನಿಲ್ಲಿಸು;
	    }

	  ಆದರೆ (ಮೌಲ್ಯ.ಮೌಲ್ಯ
	      && ವೃಕ್ಷ_ಸಂಕೇತ (ಮೌಲ್ಯ.ಮೌಲ್ಯ) == RAW_ದತ್ತಾಂಶ_CST
	      && RAW_ದತ್ತಾಂಶ_ಉದ್ದಳತೆ (ಮೌಲ್ಯ.ಮೌಲ್ಯ) > 1
	      && (ವೃಕ್ಷ_ಸಂಕೇತ (elttype) == INTEGER_TYPE
		  || ವೃಕ್ಷ_ಸಂಕೇತ (elttype) == BITINT_TYPE)
	      && TYPE_PRECISION (elttype) == CHAR_ಬಿಟ್
	      && (constructor_max_ಸೂಚ್ಯಂಕ == NULL_ವೃಕ್ಷ
		  || ವೃಕ್ಷ_int_cst_lt (constructor_ಸೂಚ್ಯಂಕ,
				      constructor_max_ಸೂಚ್ಯಂಕ)))
	    {
	      ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ len = RAW_ದತ್ತಾಂಶ_ಉದ್ದಳತೆ (ಮೌಲ್ಯ.ಮೌಲ್ಯ);
	      ಆದರೆ (constructor_max_ಸೂಚ್ಯಂಕ)
		{
		  widest_int w = wi::ಗಮ್ಯ_widest (constructor_max_ಸೂಚ್ಯಂಕ);
		  w -= wi::ಗಮ್ಯ_widest (constructor_ಸೂಚ್ಯಂಕ);
		  w += 1;
		  ಆದರೆ (w < len)
		    len = w.ಗಮ್ಯ_uhwi ();
		}
	      ಆದರೆ (len < (ಚಿಹ್ನೆರಹಿತ) RAW_ದತ್ತಾಂಶ_ಉದ್ದಳತೆ (ಮೌಲ್ಯ.ಮೌಲ್ಯ))
		{
		  raw_ದತ್ತಾಂಶ = copy_ಗಂಟು (ಮೌಲ್ಯ.ಮೌಲ್ಯ);
		  RAW_ದತ್ತಾಂಶ_ಉದ್ದಳತೆ (raw_ದತ್ತಾಂಶ) -= len;
		  RAW_ದತ್ತಾಂಶ_ಸೂಚಕ (raw_ದತ್ತಾಂಶ) += len;
		  RAW_ದತ್ತಾಂಶ_ಉದ್ದಳತೆ (ಮೌಲ್ಯ.ಮೌಲ್ಯ) = len;
		}
	      ವೃಕ್ಷ_TYPE (ಮೌಲ್ಯ.ಮೌಲ್ಯ) = elttype;
	      ತಳ್ಳು_array_bounds (ವೃಕ್ಷ_ಗಮ್ಯ_uhwi (constructor_ಸೂಚ್ಯಂಕ));
	      output_init_element (loc, ಮೌಲ್ಯ.ಮೌಲ್ಯ, ಮೌಲ್ಯ.original_type,
				   ಸುಳ್ಳು, elttype, constructor_ಸೂಚ್ಯಂಕ, ನಿಜ,
				   implicit, braced_init_obstack);
	      RESTORE_SPELLING_ಆಳ (constructor_ಆಳ);
	      constructor_ಸೂಚ್ಯಂಕ
		= ಗಾತ್ರ_binop_loc (ಒಳಹರಿವು_location, PLUS_ಅಭಿವ್ಯಕ್ತಿ,
				  constructor_ಸೂಚ್ಯಂಕ, bitsize_int (len));
	    }
	  ಇಲ್ಲದಿದ್ದರೆ
	    {
	      ಮೌಲ್ಯ.ಮೌಲ್ಯ = maybe_ವಿಭಜಿಸು_raw_ದತ್ತಾಂಶ (ಮೌಲ್ಯ.ಮೌಲ್ಯ, &raw_ದತ್ತಾಂಶ);
	      /* Now output the actual element.  */
	      ಆದರೆ (ಮೌಲ್ಯ.ಮೌಲ್ಯ)
		{
		  ತಳ್ಳು_array_bounds (ವೃಕ್ಷ_ಗಮ್ಯ_uhwi (constructor_ಸೂಚ್ಯಂಕ));
		  output_init_element (loc, ಮೌಲ್ಯ.ಮೌಲ್ಯ, ಮೌಲ್ಯ.original_type,
				       strict_string, elttype,
				       constructor_ಸೂಚ್ಯಂಕ, ನಿಜ, implicit,
				       braced_init_obstack);
		  RESTORE_SPELLING_ಆಳ (constructor_ಆಳ);
		}

	      constructor_ಸೂಚ್ಯಂಕ
		= ಗಾತ್ರ_binop_loc (ಒಳಹರಿವು_location, PLUS_ಅಭಿವ್ಯಕ್ತಿ,
				  constructor_ಸೂಚ್ಯಂಕ, bitsize_one_ಗಂಟು);

	      ಆದರೆ (!ಮೌಲ್ಯ.ಮೌಲ್ಯ)
		/* If we are doing the bookkeeping for an element that was
		   directly output as a constructor, we must update
		   constructor_unfilled_index.  */
		constructor_unfilled_ಸೂಚ್ಯಂಕ = constructor_ಸೂಚ್ಯಂಕ;
	    }
	}
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (gnu_ಸದಿಶ_type_p (constructor_type))
	{
	  ವೃಕ್ಷ elttype = TYPE_MAIN_VARIANT (ವೃಕ್ಷ_TYPE (constructor_type));

	  /* Do a basic check of initializer size.  Note that vectors
	     may not always have a fixed size derived from their type.  */
	  ಆದರೆ (maybe_lt (ವೃಕ್ಷ_ಗಮ್ಯ_poly_uint64 (constructor_max_ಸೂಚ್ಯಂಕ),
			ವೃಕ್ಷ_ಗಮ್ಯ_poly_uint64 (constructor_ಸೂಚ್ಯಂಕ)))
	    {
	      /* Diagose VLA out-of-bounds as errors.  */
	      ಆದರೆ (ವೃಕ್ಷ_ಗಮ್ಯ_poly_uint64 (constructor_max_ಸೂಚ್ಯಂಕ).is_constant())
		pedwarn_init (loc, 0,
			      "excess elements in vector initializer");
	      ಇಲ್ಲದಿದ್ದರೆ
		error_init (loc, "excess elements in vector initializer");

	      ನಿಲ್ಲಿಸು;
	    }

	  ಮೌಲ್ಯ.ಮೌಲ್ಯ = maybe_ವಿಭಜಿಸು_raw_ದತ್ತಾಂಶ (ಮೌಲ್ಯ.ಮೌಲ್ಯ, &raw_ದತ್ತಾಂಶ);
	  /* Now output the actual element.  */
	  ಆದರೆ (ಮೌಲ್ಯ.ಮೌಲ್ಯ)
	    {
	      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ಮೌಲ್ಯ.ಮೌಲ್ಯ) == ಸದಿಶ_CST)
		elttype = TYPE_MAIN_VARIANT (constructor_type);
	      output_init_element (loc, ಮೌಲ್ಯ.ಮೌಲ್ಯ, ಮೌಲ್ಯ.original_type,
				   strict_string, elttype,
				   constructor_ಸೂಚ್ಯಂಕ, ನಿಜ, implicit,
				   braced_init_obstack);
	    }

	  constructor_ಸೂಚ್ಯಂಕ
	    = ಗಾತ್ರ_binop_loc (ಒಳಹರಿವು_location,
			      PLUS_ಅಭಿವ್ಯಕ್ತಿ, constructor_ಸೂಚ್ಯಂಕ, bitsize_one_ಗಂಟು);

	  ಆದರೆ (!ಮೌಲ್ಯ.ಮೌಲ್ಯ)
	    /* If we are doing the bookkeeping for an element that was
	       directly output as a constructor, we must update
	       constructor_unfilled_index.  */
	    constructor_unfilled_ಸೂಚ್ಯಂಕ = constructor_ಸೂಚ್ಯಂಕ;
	}

      /* Handle the sole element allowed in a braced initializer
	 for a scalar variable.  */
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (constructor_type != error_mark_ಗಂಟು
	       && constructor_fields == NULL_ವೃಕ್ಷ)
	{
	  pedwarn_init (loc, 0,
			"excess elements in scalar initializer");
	  ನಿಲ್ಲಿಸು;
	}
      ಇಲ್ಲದಿದ್ದರೆ
	{
	  ಮೌಲ್ಯ.ಮೌಲ್ಯ = maybe_ವಿಭಜಿಸು_raw_ದತ್ತಾಂಶ (ಮೌಲ್ಯ.ಮೌಲ್ಯ, &raw_ದತ್ತಾಂಶ);
	  ಆದರೆ (ಮೌಲ್ಯ.ಮೌಲ್ಯ)
	    output_init_element (loc, ಮೌಲ್ಯ.ಮೌಲ್ಯ, ಮೌಲ್ಯ.original_type,
				 strict_string, constructor_type,
				 NULL_ವೃಕ್ಷ, ನಿಜ, implicit,
				 braced_init_obstack);
	  constructor_fields = NULL_ವೃಕ್ಷ;
	}

      /* Handle range initializers either at this level or anywhere higher
	 in the designator stack.  */
      ಆದರೆ (constructor_range_ರಾಶಿ)
	{
	  ರಚನೆ constructor_range_ರಾಶಿ *p, *range_ರಾಶಿ;
	  ಪೂರ್ಣಾಂಕ ಮುಕ್ತಾಯ = 0;

	  range_ರಾಶಿ = constructor_range_ರಾಶಿ;
	  constructor_range_ರಾಶಿ = 0;
	  ಆಗ (constructor_ರಾಶಿ != range_ರಾಶಿ->ರಾಶಿ)
	    {
	      gcc_assert (constructor_ರಾಶಿ->implicit);
	      process_init_element (loc,
				    ತೆಗೆ_init_level (loc, 1,
						    braced_init_obstack,
						    ಕೊನೆಯ_init_list_comma),
				    ನಿಜ, braced_init_obstack);
	    }
	  ಗಾಗಿ (p = range_ರಾಶಿ;
	       !p->range_ಕೊನೆ || ವೃಕ್ಷ_int_cst_equal (p->ಸೂಚ್ಯಂಕ, p->range_ಕೊನೆ);
	       p = p->prev)
	    {
	      gcc_assert (constructor_ರಾಶಿ->implicit);
	      process_init_element (loc,
				    ತೆಗೆ_init_level (loc, 1,
						    braced_init_obstack,
						    ಕೊನೆಯ_init_list_comma),
				    ನಿಜ, braced_init_obstack);
	    }

	  p->ಸೂಚ್ಯಂಕ = ಗಾತ್ರ_binop_loc (ಒಳಹರಿವು_location,
				     PLUS_ಅಭಿವ್ಯಕ್ತಿ, p->ಸೂಚ್ಯಂಕ, bitsize_one_ಗಂಟು);
	  ಆದರೆ (ವೃಕ್ಷ_int_cst_equal (p->ಸೂಚ್ಯಂಕ, p->range_ಕೊನೆ) && !p->prev)
	    ಮುಕ್ತಾಯ = 1;

	  ಆಗ (1)
	    {
	      constructor_ಸೂಚ್ಯಂಕ = p->ಸೂಚ್ಯಂಕ;
	      constructor_fields = p->fields;
	      ಆದರೆ (ಮುಕ್ತಾಯ && p->range_ಕೊನೆ && p->ಸೂಚ್ಯಂಕ == p->range_ಆರಂಭ)
		{
		  ಮುಕ್ತಾಯ = 0;
		  p->prev = 0;
		}
	      p = p->ಮುಂದಿನ;
	      ಆದರೆ (!p)
		ನಿಲ್ಲಿಸು;
	      ಮುಕ್ತಾಯ_implicit_inits (loc, braced_init_obstack);
	      ತಳ್ಳು_init_level (loc, 2, braced_init_obstack);
	      p->ರಾಶಿ = constructor_ರಾಶಿ;
	      ಆದರೆ (p->range_ಕೊನೆ && ವೃಕ್ಷ_int_cst_equal (p->ಸೂಚ್ಯಂಕ, p->range_ಕೊನೆ))
		p->ಸೂಚ್ಯಂಕ = p->range_ಆರಂಭ;
	    }

	  ಆದರೆ (!ಮುಕ್ತಾಯ)
	    constructor_range_ರಾಶಿ = range_ರಾಶಿ;
	  ಮುಂದುವರಿ;
	}

      ನಿಲ್ಲಿಸು;
    }

  constructor_range_ರಾಶಿ = 0;

  ಆದರೆ (raw_ದತ್ತಾಂಶ && RAW_ದತ್ತಾಂಶ_ಉದ್ದಳತೆ (raw_ದತ್ತಾಂಶ))
    {
      gcc_assert (!string_flag && !was_designated);
      ಮೌಲ್ಯ.ಮೌಲ್ಯ = raw_ದತ್ತಾಂಶ;
      raw_ದತ್ತಾಂಶ = NULL_ವೃಕ್ಷ;
      ಹೋಗು retry;
    }
}

/* Build a complete asm-statement, whose components are a CV_QUALIFIER
   (guaranteed to be 'volatile' or null) and ARGS (represented using
   an ASM_EXPR node).  */
ವೃಕ್ಷ
build_asm_stmt (ತಾರ್ಕಿಕ is_volatile, ವೃಕ್ಷ ವಾದಗಳು)
{
  ಆದರೆ (is_volatile)
    ASM_VOLATILE_P (ವಾದಗಳು) = 1;
  ಹಿಂತಿರುಗಿ ಕೂಡಿಸು_stmt (ವಾದಗಳು);
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
  ವೃಕ್ಷ ಬಾಲ;
  ವೃಕ್ಷ ವಾದಗಳು;
  ಪೂರ್ಣಾಂಕ i;
  ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *constraint;
  ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ **oconstraints;
  ತಾರ್ಕಿಕ allows_mem, allows_reg, is_inout;
  ಪೂರ್ಣಾಂಕ ninputs, noutputs;

  ninputs = list_ಉದ್ದಳತೆ (inputs);
  noutputs = list_ಉದ್ದಳತೆ (outputs);
  oconstraints = (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ **) alloca (noutputs * ಗಾತ್ರ (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *));

  string = resolve_asm_ಕಾರ್ಯಾಂಶ_ಹೆಸರುಗಳು (string, outputs, inputs, labels);

  /* Remove output conversions that change the type but not the mode.  */
  ಗಾಗಿ (i = 0, ಬಾಲ = outputs; ಬಾಲ; ++i, ಬಾಲ = ವೃಕ್ಷ_CHAIN (ಬಾಲ))
    {
      ವೃಕ್ಷ output = ವೃಕ್ಷ_ಮೌಲ್ಯ (ಬಾಲ);

      output = c_fully_fold (output, ಸುಳ್ಳು, ಖಾಲಿ, ನಿಜ);

      /* ??? Really, this should not be here.  Users should be using a
	 proper lvalue, dammit.  But there's a long history of using casts
	 in the output operands.  In cases like longlong.h, this becomes a
	 primitive form of typechecking -- if the cast can be removed, then
	 the output operand had a type of the proper width; otherwise we'll
	 get an error.  Gross, but ...  */
      STRIP_NOPS (output);

      ಆದರೆ (!lvalue_or_else (loc, output, lv_asm))
	output = error_mark_ಗಂಟು;

      ಆದರೆ (output != error_mark_ಗಂಟು
	  && (ವೃಕ್ಷ_READONLY (output)
	      || TYPE_READONLY (ವೃಕ್ಷ_TYPE (output))
	      || (ದಾಖಲೆ_OR_UNION_TYPE_P (ವೃಕ್ಷ_TYPE (output))
		  && C_TYPE_FIELDS_READONLY (ವೃಕ್ಷ_TYPE (output)))))
	readonly_error (loc, output, lv_asm);

      constraint = ವೃಕ್ಷ_STRING_ಸೂಚಕ (ವೃಕ್ಷ_ಮೌಲ್ಯ (ವೃಕ್ಷ_PURPOSE (ಬಾಲ)));
      oconstraints[i] = constraint;

      ಆದರೆ (parse_output_constraint (&constraint, i, ninputs, noutputs,
				   &allows_mem, &allows_reg, &is_inout,
				   ಶೂನ್ಯಸೂಚಕ))
	{
	  /* If the operand is going to end up in memory,
	     mark it addressable.  */
	  ಆದರೆ (!allows_reg && !c_mark_addressable (output))
	    output = error_mark_ಗಂಟು;
	  ಆದರೆ (!(!allows_reg && allows_mem)
	      && output != error_mark_ಗಂಟು
	      && VOID_TYPE_P (ವೃಕ್ಷ_TYPE (output)))
	    {
	      error_at (loc, "invalid use of void expression");
	      output = error_mark_ಗಂಟು;
	    }
	  ಆದರೆ (allows_reg && current_function_decl == NULL_ವೃಕ್ಷ)
	    {
	      error_at (loc, "constraint allows registers outside of "
			     "a function");
	      output = error_mark_ಗಂಟು;
	    }
	}
      ಇಲ್ಲದಿದ್ದರೆ
	output = error_mark_ಗಂಟು;

      ಆದರೆ (current_function_decl == NULL_ವೃಕ್ಷ && output != error_mark_ಗಂಟು)
	{
	  ಆದರೆ (ವೃಕ್ಷ_SIDE_EFFECTS (output))
	    {
	      error_at (loc, "side-effects in output operand outside "
			     "of a function");
	      output = error_mark_ಗಂಟು;
	    }
	  ಇಲ್ಲದಿದ್ದರೆ
	    {
	      ವೃಕ್ಷ addr = build_unary_op (loc, ADDR_ಅಭಿವ್ಯಕ್ತಿ, output, ಸುಳ್ಳು);
	      ಆದರೆ (addr == error_mark_ಗಂಟು)
		output = error_mark_ಗಂಟು;
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!initializer_constant_valid_p (addr, ವೃಕ್ಷ_TYPE (addr)))
		{
		  error_at (loc, "output operand outside of a function is not "
				 "constant");
		  output = error_mark_ಗಂಟು;
		}
	    }
	}
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (output != error_mark_ಗಂಟು && ಅಕ್ಷರಸರಣಿ_ಹುಡುಕು (constraint, "-"))
	{
	  error_at (loc, "%<-%> modifier used inside of a function");
	  output = error_mark_ಗಂಟು;
	}

      ವೃಕ್ಷ_ಮೌಲ್ಯ (ಬಾಲ) = output;
    }

  ಗಾಗಿ (i = 0, ಬಾಲ = inputs; ಬಾಲ; ++i, ಬಾಲ = ವೃಕ್ಷ_CHAIN (ಬಾಲ))
    {
      ವೃಕ್ಷ ಒಳಹರಿವು;

      constraint = ವೃಕ್ಷ_STRING_ಸೂಚಕ (ವೃಕ್ಷ_ಮೌಲ್ಯ (ವೃಕ್ಷ_PURPOSE (ಬಾಲ)));
      ಒಳಹರಿವು = ವೃಕ್ಷ_ಮೌಲ್ಯ (ಬಾಲ);

      ಆದರೆ (parse_ಒಳಹರಿವು_constraint (&constraint, i, ninputs, noutputs, 0,
				  oconstraints, &allows_mem, &allows_reg,
				  ಶೂನ್ಯಸೂಚಕ))
	{
	  /* If the operand is going to end up in memory,
	     mark it addressable.  */
	  ಆದರೆ (!allows_reg && allows_mem)
	    {
	      ಒಳಹರಿವು = c_fully_fold (ಒಳಹರಿವು, ಸುಳ್ಳು, ಖಾಲಿ, ನಿಜ);

	      /* Strip the nops as we allow this case.  FIXME, this really
		 should be rejected or made deprecated.  */
	      STRIP_NOPS (ಒಳಹರಿವು);
	      ಆದರೆ (!c_mark_addressable (ಒಳಹರಿವು))
		ಒಳಹರಿವು = error_mark_ಗಂಟು;
	    }
	  ಇಲ್ಲದಿದ್ದರೆ
	    {
	      ಒಳಹರಿವು = c_fully_fold (convert_lvalue_ಗಮ್ಯ_rvalue (loc, ಒಳಹರಿವು,
							      ನಿಜ, ಸುಳ್ಳು),
				    ಸುಳ್ಳು, ಖಾಲಿ);

	      ಆದರೆ (ಒಳಹರಿವು != error_mark_ಗಂಟು && VOID_TYPE_P (ವೃಕ್ಷ_TYPE (ಒಳಹರಿವು)))
		{
		  error_at (loc, "invalid use of void expression");
		  ಒಳಹರಿವು = error_mark_ಗಂಟು;
		}
	    }
	  ಆದರೆ (allows_reg && current_function_decl == NULL_ವೃಕ್ಷ)
	    {
	      error_at (loc, "constraint allows registers outside of "
			     "a function");
	      ಒಳಹರಿವು = error_mark_ಗಂಟು;
	    }
	  ಆದರೆ (constraint[0] == ':' && ಒಳಹರಿವು != error_mark_ಗಂಟು)
	    {
	      ವೃಕ್ಷ t = ಒಳಹರಿವು;
	      STRIP_NOPS (t);
	      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (t) != ADDR_ಅಭಿವ್ಯಕ್ತಿ
		  || !(ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (t, 0)) == FUNCTION_DECL
		       || (VAR_P (ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (t, 0))
			   && is_global_var (ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (t, 0)))))
		{
		  error_at (loc, "%<:%> constraint operand is not address "
				 "of a function or non-automatic variable");
		  ಒಳಹರಿವು = error_mark_ಗಂಟು;
		}
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (t, 0)) == FUNCTION_DECL)
		suppress_warning (ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (t, 0), OPT_Wunused);
	    }
	}
      ಇಲ್ಲದಿದ್ದರೆ
	ಒಳಹರಿವು = error_mark_ಗಂಟು;

      ಆದರೆ (current_function_decl == NULL_ವೃಕ್ಷ && ಒಳಹರಿವು != error_mark_ಗಂಟು)
	{
	  ಆದರೆ (ವೃಕ್ಷ_SIDE_EFFECTS (ಒಳಹರಿವು))
	    {
	      error_at (loc, "side-effects in input operand outside "
			     "of a function");
	      ಒಳಹರಿವು = error_mark_ಗಂಟು;
	    }
	  ಇಲ್ಲದಿದ್ದರೆ
	    {
	      ವೃಕ್ಷ tem = ಒಳಹರಿವು;
	      ಆದರೆ (allows_mem && lvalue_p (ಒಳಹರಿವು))
		tem = build_unary_op (loc, ADDR_ಅಭಿವ್ಯಕ್ತಿ, ಒಳಹರಿವು, ಸುಳ್ಳು);
	      ಆದರೆ (!initializer_constant_valid_p (tem, ವೃಕ್ಷ_TYPE (tem)))
		{
		  error_at (loc, "input operand outside of a function is not "
				 "constant");
		  ಒಳಹರಿವು = error_mark_ಗಂಟು;
		}
	    }
	}
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ಒಳಹರಿವು != error_mark_ಗಂಟು && ಅಕ್ಷರಸರಣಿ_ಹುಡುಕು (constraint, "-"))
	{
	  error_at (loc, "%<-%> modifier used inside of a function");
	  ಒಳಹರಿವು = error_mark_ಗಂಟು;
	}

      ವೃಕ್ಷ_ಮೌಲ್ಯ (ಬಾಲ) = ಒಳಹರಿವು;
    }

  ವಾದಗಳು = build_stmt (loc, ASM_ಅಭಿವ್ಯಕ್ತಿ, string, outputs, inputs, clobbers, labels);

  /* asm statements without outputs, including simple ones, are treated
     as volatile.  */
  ASM_BASIC_P (ವಾದಗಳು) = simple;
  ASM_VOLATILE_P (ವಾದಗಳು) = (noutputs == 0);
  ASM_INLINE_P (ವಾದಗಳು) = is_inline;

  ಹಿಂತಿರುಗಿ ವಾದಗಳು;
}

/* Generate a goto statement to LABEL.  LOC is the location of the
   GOTO.  */

ವೃಕ್ಷ
c_ಮುಕ್ತಾಯ_goto_label (location_t loc, ವೃಕ್ಷ label)
{
  ವೃಕ್ಷ decl = lookup_label_for_goto (loc, label);
  ಆದರೆ (!decl)
    ಹಿಂತಿರುಗಿ NULL_ವೃಕ್ಷ;
  ವೃಕ್ಷ_ಬಳಸಿದ (decl) = 1;
  mark_decl_ಬಳಸಿದ (decl, ಸುಳ್ಳು);
  {
    ಕೂಡಿಸು_stmt (build_predict_ಅಭಿವ್ಯಕ್ತಿ (PRED_GOTO, NOT_ತೆಗೆದುಕೊಂಡ));
    ವೃಕ್ಷ t = build1 (GOTO_ಅಭಿವ್ಯಕ್ತಿ, void_type_ಗಂಟು, decl);
    ಗಣ_ಅಭಿವ್ಯಕ್ತಿ_LOCATION (t, loc);
    ಹಿಂತಿರುಗಿ ಕೂಡಿಸು_stmt (t);
  }
}

/* Generate a computed goto statement to EXPR.  LOC is the location of
   the GOTO.  */

ವೃಕ್ಷ
c_ಮುಕ್ತಾಯ_goto_ptr (location_t loc, c_ಅಭಿವ್ಯಕ್ತಿ val)
{
  ವೃಕ್ಷ ಅಭಿವ್ಯಕ್ತಿ = val.ಮೌಲ್ಯ;
  ವೃಕ್ಷ t;
  pedwarn (loc, OPT_Wpedantic, "ISO C forbids %<goto *expr;%>");
  ಆದರೆ (ಅಭಿವ್ಯಕ್ತಿ != error_mark_ಗಂಟು
      && !ಸೂಚಕ_TYPE_P (ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ))
      && !null_ಸೂಚಕ_constant_p (ಅಭಿವ್ಯಕ್ತಿ))
    {
      error_at (val.get_location (),
		"computed goto must be pointer type");
      ಅಭಿವ್ಯಕ್ತಿ = build_zero_cst (ptr_type_ಗಂಟು);
    }
  ಅಭಿವ್ಯಕ್ತಿ = c_fully_fold (ಅಭಿವ್ಯಕ್ತಿ, ಸುಳ್ಳು, ಖಾಲಿ);
  ಅಭಿವ್ಯಕ್ತಿ = convert (ptr_type_ಗಂಟು, ಅಭಿವ್ಯಕ್ತಿ);
  t = build1 (GOTO_ಅಭಿವ್ಯಕ್ತಿ, void_type_ಗಂಟು, ಅಭಿವ್ಯಕ್ತಿ);
  ಗಣ_ಅಭಿವ್ಯಕ್ತಿ_LOCATION (t, loc);
  ಹಿಂತಿರುಗಿ ಕೂಡಿಸು_stmt (t);
}

/* Generate a C `return' statement.  RETVAL is the expression for what
   to return, or a null pointer for `return;' with no value.  LOC is
   the location of the return statement, or the location of the expression,
   if the statement has any.  If ORIGTYPE is not NULL_TREE, it
   is the original type of RETVAL.  MUSTTAIL_P indicates a musttail
   attribute.  */

ವೃಕ್ಷ
c_ಮುಕ್ತಾಯ_return (location_t loc, ವೃಕ್ಷ retval, ವೃಕ್ಷ origtype, ತಾರ್ಕಿಕ musttail_p)
{
  ವೃಕ್ಷ valtype = ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_TYPE (current_function_decl)), ret_stmt;
  ತಾರ್ಕಿಕ no_warning = ಸುಳ್ಳು;
  ತಾರ್ಕಿಕ npc = ಸುಳ್ಳು;

  /* Use the expansion point to handle cases such as returning NULL
     in a function returning void.  */
  location_t xloc = expansion_ಬಿಂದು_location_if_ಒಳ_system_ಶೀರ್ಷಿಕೆ (loc);

  ಆದರೆ (ವೃಕ್ಷ_THIS_VOLATILE (current_function_decl))
    warning_at (xloc, 0,
		"function declared %<noreturn%> has a %<return%> statement");

  ಗಣ_musttail_on_return (retval, xloc, musttail_p);

  ಆದರೆ (retval)
    {
      ವೃಕ್ಷ semantic_type = NULL_ವೃಕ್ಷ;
      npc = null_ಸೂಚಕ_constant_p (retval);
      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (retval) == EXCESS_PRECISION_ಅಭಿವ್ಯಕ್ತಿ)
	{
	  semantic_type = ವೃಕ್ಷ_TYPE (retval);
	  retval = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (retval, 0);
	}
      retval = c_fully_fold (retval, ಸುಳ್ಳು, ಖಾಲಿ);
      ಆದರೆ (semantic_type
	  && valtype != NULL_ವೃಕ್ಷ
	  && ವೃಕ್ಷ_ಸಂಕೇತ (valtype) != VOID_TYPE)
	retval = build1 (EXCESS_PRECISION_ಅಭಿವ್ಯಕ್ತಿ, semantic_type, retval);
    }

  ಆದರೆ (!retval)
    {
      current_function_returns_null = 1;
      ಆದರೆ ((warn_return_type >= 0 || flag_isoc99)
	  && valtype != NULL_ವೃಕ್ಷ && ವೃಕ್ಷ_ಸಂಕೇತ (valtype) != VOID_TYPE)
	{
	  no_warning = ನಿಜ;
	  ಆದರೆ (emit_diagnostic (flag_isoc99
			       ? diagnostics::ಬಗೆ::permerror
			       : diagnostics::ಬಗೆ::warning,
			       loc, OPT_Wreturn_mismatch,
			       "%<return%> with no value,"
			       " in function returning non-void"))
	    inform (DECL_ಮೂಲ_LOCATION (current_function_decl),
		    "declared here");
	}
    }
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (valtype == NULL_ವೃಕ್ಷ || VOID_TYPE_P (valtype))
    {
      current_function_returns_null = 1;
      ತಾರ್ಕಿಕ warned_ಇಲ್ಲಿ;
      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (retval)) != VOID_TYPE)
	warned_ಇಲ್ಲಿ = permerror_opt
	  (xloc, OPT_Wreturn_mismatch,
	   "%<return%> with a value, in function returning void");
      ಇಲ್ಲದಿದ್ದರೆ
	warned_ಇಲ್ಲಿ = pedwarn
	  (xloc, OPT_Wpedantic, "ISO C forbids "
	   "%<return%> with expression, in function returning void");
      ಆದರೆ (warned_ಇಲ್ಲಿ)
	inform (DECL_ಮೂಲ_LOCATION (current_function_decl),
		"declared here");
    }
  ಇಲ್ಲದಿದ್ದರೆ
    {
      ವೃಕ್ಷ t = convert_for_assignment (loc, UNKNOWN_LOCATION, valtype,
				       retval, origtype, ic_return,
				       npc, NULL_ವೃಕ್ಷ, NULL_ವೃಕ್ಷ, 0);
      ವೃಕ್ಷ res = DECL_ಫಲಿತಾಂಶ (current_function_decl);
      ವೃಕ್ಷ inner;
      ತಾರ್ಕಿಕ save;

      current_function_returns_ಮೌಲ್ಯ = 1;
      ಆದರೆ (t == error_mark_ಗಂಟು)
	{
	  /* Suppress -Wreturn-type for this function.  */
	  ಆದರೆ (warn_return_type)
	    suppress_warning (current_function_decl, OPT_Wreturn_type);
	  ಹಿಂತಿರುಗಿ NULL_ವೃಕ್ಷ;
	}

      save = ಒಳ_late_ದ್ವಿಮಾನ_op;
      ಆದರೆ (C_BOOLEAN_TYPE_P (ವೃಕ್ಷ_TYPE (res))
	  || ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (res)) == COMPLEX_TYPE
	  || (SCALAR_FLOAT_TYPE_P (ವೃಕ್ಷ_TYPE (t))
	      && (ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (res)) == INTEGER_TYPE
		  || ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (res)) == ENUMERAL_TYPE)
	      && sanitize_flags_p (SANITIZE_FLOAT_CAST)))
        ಒಳ_late_ದ್ವಿಮಾನ_op = ನಿಜ;
      inner = t = convert (ವೃಕ್ಷ_TYPE (res), t);
      ಒಳ_late_ದ್ವಿಮಾನ_op = save;

      /* Strip any conversions, additions, and subtractions, and see if
	 we are returning the address of a local variable.  Warn if so.  */
      ಆಗ (1)
	{
	  ಆಯ್ಕೆ (ವೃಕ್ಷ_ಸಂಕೇತ (inner))
	    {
	    CASE_CONVERT:
	    ಸ್ಥಿತಿ NON_LVALUE_ಅಭಿವ್ಯಕ್ತಿ:
	    ಸ್ಥಿತಿ PLUS_ಅಭಿವ್ಯಕ್ತಿ:
	    ಸ್ಥಿತಿ ಸೂಚಕ_PLUS_ಅಭಿವ್ಯಕ್ತಿ:
	      inner = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (inner, 0);
	      ಮುಂದುವರಿ;

	    ಸ್ಥಿತಿ MINUS_ಅಭಿವ್ಯಕ್ತಿ:
	      /* If the second operand of the MINUS_EXPR has a pointer
		 type (or is converted from it), this may be valid, so
		 don't give a warning.  */
	      {
		ವೃಕ್ಷ op1 = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (inner, 1);

		ಆಗ (!ಸೂಚಕ_TYPE_P (ವೃಕ್ಷ_TYPE (op1))
		       && (CONVERT_ಅಭಿವ್ಯಕ್ತಿ_P (op1)
			   || ವೃಕ್ಷ_ಸಂಕೇತ (op1) == NON_LVALUE_ಅಭಿವ್ಯಕ್ತಿ))
		  op1 = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (op1, 0);

		ಆದರೆ (ಸೂಚಕ_TYPE_P (ವೃಕ್ಷ_TYPE (op1)))
		  ನಿಲ್ಲಿಸು;

		inner = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (inner, 0);
		ಮುಂದುವರಿ;
	      }

	    ಸ್ಥಿತಿ ADDR_ಅಭಿವ್ಯಕ್ತಿ:
	      inner = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (inner, 0);

	      ಆಗ (REFERENCE_CLASS_P (inner)
		     && !ಪರೋಕ್ಷ_REF_P (inner))
		inner = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (inner, 0);

	      ಆದರೆ (DECL_P (inner)
		  && !DECL_EXTERNAL (inner)
		  && DECL_CONTEXT (inner) == current_function_decl
		  && ಸೂಚಕ_TYPE_P (ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_TYPE (current_function_decl))))
		{
		  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (inner) == LABEL_DECL)
		    warning_at (loc, OPT_Wreturn_local_addr,
				"function returns address of label");
		  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (inner) == FUNCTION_DECL
			   && (C_FUNC_NONLOCAL_CONTEXT (inner)
			       || !DECL_INITIAL (inner)))
		    warning_at (loc, OPT_Wreturn_local_addr,
				"function returns address of nested function "
				"referencing local context");
		  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (inner) != FUNCTION_DECL
			   && !ವೃಕ್ಷ_STATIC (inner))
		    {
		      warning_at (loc, OPT_Wreturn_local_addr,
				  "function returns address of local variable");
		      ವೃಕ್ಷ zero = build_zero_cst (ವೃಕ್ಷ_TYPE (res));
		      t = build2 (COMPOUND_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (res), t, zero);
		    }
		}
	      ನಿಲ್ಲಿಸು;

	    ಪೂರ್ವನಿಯೋಜಿತ:
	      ನಿಲ್ಲಿಸು;
	    }

	  ನಿಲ್ಲಿಸು;
	}

      retval = build2 (MODIFY_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (res), res, t);
      ಗಣ_ಅಭಿವ್ಯಕ್ತಿ_LOCATION (retval, loc);

      ಆದರೆ (warn_sequence_ಬಿಂದು)
	verify_sequence_points (retval);
    }

  ret_stmt = build_stmt (loc, RETURN_ಅಭಿವ್ಯಕ್ತಿ, retval);
  ಆದರೆ (no_warning)
    suppress_warning (ret_stmt, OPT_Wreturn_type);
  ಹಿಂತಿರುಗಿ ಕೂಡಿಸು_stmt (ret_stmt);
}

ರಚನೆ c_switch {
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
  ರಚನೆ c_spot_bindings *bindings;

  /* Whether the switch includes any break statements.  */
  ತಾರ್ಕಿಕ break_stmt_ನೋಡಿದ_p;

  /* The next node on the stack.  */
  ರಚನೆ c_switch *ಮುಂದಿನ;

  /* Remember whether the controlling expression had boolean type
     before integer promotions for the sake of -Wswitch-bool.  */
  ತಾರ್ಕಿಕ bool_cond_p;
};

/* A stack of the currently active switch statements.  The innermost
   switch statement is on the top of the stack.  There is no need to
   mark the stack for garbage collection because it is only active
   during the processing of the body of a function, and we never
   collect at that point.  */

ರಚನೆ c_switch *c_switch_ರಾಶಿ;

/* Start a C switch statement, testing expression EXP.  Return the new
   SWITCH_STMT.  SWITCH_LOC is the location of the `switch'.
   SWITCH_COND_LOC is the location of the switch's condition.
   EXPLICIT_CAST_P is true if the expression EXP has an explicit cast.  */

ವೃಕ್ಷ
c_ಆರಂಭ_switch (location_t switch_loc,
		location_t switch_cond_loc,
		ವೃಕ್ಷ ಘಾತಾಂಕ, ತಾರ್ಕಿಕ explicit_cast_p, ವೃಕ್ಷ switch_name)
{
  ವೃಕ್ಷ orig_type = error_mark_ಗಂಟು;
  ತಾರ್ಕಿಕ bool_cond_p = ಸುಳ್ಳು;
  ರಚನೆ c_switch *cs;

  ಆದರೆ (ಘಾತಾಂಕ != error_mark_ಗಂಟು)
    {
      orig_type = ವೃಕ್ಷ_TYPE (ಘಾತಾಂಕ);

      ಆದರೆ (!INTEGRAL_TYPE_P (orig_type))
	{
	  ಆದರೆ (orig_type != error_mark_ಗಂಟು)
	    {
	      error_at (switch_cond_loc, "switch quantity not an integer");
	      orig_type = error_mark_ಗಂಟು;
	    }
	  ಘಾತಾಂಕ = integer_zero_ಗಂಟು;
	}
      ಇಲ್ಲದಿದ್ದರೆ
	{
	  ವೃಕ್ಷ type = TYPE_MAIN_VARIANT (orig_type);
	  ವೃಕ್ಷ e = ಘಾತಾಂಕ;

	  /* Warn if the condition has boolean value.  */
	  ಆಗ (ವೃಕ್ಷ_ಸಂಕೇತ (e) == COMPOUND_ಅಭಿವ್ಯಕ್ತಿ)
	    e = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (e, 1);

	  ಆದರೆ ((C_BOOLEAN_TYPE_P (type)
	       || truth_ಮೌಲ್ಯ_p (ವೃಕ್ಷ_ಸಂಕೇತ (e)))
	      /* Explicit cast to int suppresses this warning.  */
	      && !(ವೃಕ್ಷ_ಸಂಕೇತ (type) == INTEGER_TYPE
		   && explicit_cast_p))
	    bool_cond_p = ನಿಜ;

	  ಆದರೆ (!ಒಳ_system_ಶೀರ್ಷಿಕೆ_at (ಒಳಹರಿವು_location)
	      && (type == long_integer_type_ಗಂಟು
		  || type == long_unsigned_type_ಗಂಟು))
	    warning_at (switch_cond_loc,
			OPT_Wtraditional, "%<long%> switch expression not "
			"converted to %<int%> in ISO C");

	  ಘಾತಾಂಕ = c_fully_fold (ಘಾತಾಂಕ, ಸುಳ್ಳು, ಖಾಲಿ);
	  ಘಾತಾಂಕ = default_conversion (ಘಾತಾಂಕ);

	  ಆದರೆ (warn_sequence_ಬಿಂದು)
	    verify_sequence_points (ಘಾತಾಂಕ);
	}
    }

  /* Add this new SWITCH_STMT to the stack.  */
  cs = XNEW (ರಚನೆ c_switch);
  cs->switch_stmt = build_stmt (switch_loc, SWITCH_STMT, ಘಾತಾಂಕ,
				NULL_ವೃಕ್ಷ, orig_type, NULL_ವೃಕ್ಷ, switch_name);
  cs->orig_type = orig_type;
  cs->cases = splay_ವೃಕ್ಷ_new (case_compare, ಖಾಲಿ, ಖಾಲಿ);
  cs->bindings = c_get_switch_bindings ();
  cs->break_stmt_ನೋಡಿದ_p = ಸುಳ್ಳು;
  cs->bool_cond_p = bool_cond_p;
  cs->ಮುಂದಿನ = c_switch_ರಾಶಿ;
  c_switch_ರಾಶಿ = cs;

  ಹಿಂತಿರುಗಿ ಕೂಡಿಸು_stmt (cs->switch_stmt);
}

/* Process a case label at location LOC, with attributes ATTRS.  */

ವೃಕ್ಷ
do_case (location_t loc, ವೃಕ್ಷ ಕೆಳಗಿನ_ಮೌಲ್ಯ, ವೃಕ್ಷ ಮೇಲಿನ_ಮೌಲ್ಯ, ವೃಕ್ಷ attrs)
{
  ವೃಕ್ಷ label = NULL_ವೃಕ್ಷ;

  ಆದರೆ (ಕೆಳಗಿನ_ಮೌಲ್ಯ && ವೃಕ್ಷ_ಸಂಕೇತ (ಕೆಳಗಿನ_ಮೌಲ್ಯ) != INTEGER_CST)
    {
      ಕೆಳಗಿನ_ಮೌಲ್ಯ = c_fully_fold (ಕೆಳಗಿನ_ಮೌಲ್ಯ, ಸುಳ್ಳು, ಖಾಲಿ);
      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ಕೆಳಗಿನ_ಮೌಲ್ಯ) == INTEGER_CST)
	pedwarn (loc, OPT_Wpedantic,
		 "case label is not an integer constant expression");
    }

  ಆದರೆ (ಮೇಲಿನ_ಮೌಲ್ಯ && ವೃಕ್ಷ_ಸಂಕೇತ (ಮೇಲಿನ_ಮೌಲ್ಯ) != INTEGER_CST)
    {
      ಮೇಲಿನ_ಮೌಲ್ಯ = c_fully_fold (ಮೇಲಿನ_ಮೌಲ್ಯ, ಸುಳ್ಳು, ಖಾಲಿ);
      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ಮೇಲಿನ_ಮೌಲ್ಯ) == INTEGER_CST)
	pedwarn (ಒಳಹರಿವು_location, OPT_Wpedantic,
		 "case label is not an integer constant expression");
    }

  ಆದರೆ (c_switch_ರಾಶಿ == ಖಾಲಿ)
    {
      ಆದರೆ (ಕೆಳಗಿನ_ಮೌಲ್ಯ)
	error_at (loc, "case label not within a switch statement");
      ಇಲ್ಲದಿದ್ದರೆ
	error_at (loc, "%<default%> label not within a switch statement");
      ಹಿಂತಿರುಗಿ NULL_ವೃಕ್ಷ;
    }

  ಆದರೆ (c_check_switch_jump_warnings (c_switch_ರಾಶಿ->bindings,
				    ಅಭಿವ್ಯಕ್ತಿ_LOCATION (c_switch_ರಾಶಿ->switch_stmt),
				    loc))
    ಹಿಂತಿರುಗಿ NULL_ವೃಕ್ಷ;

  label = c_ಕೂಡಿಸು_case_label (loc, c_switch_ರಾಶಿ->cases,
			    SWITCH_STMT_COND (c_switch_ರಾಶಿ->switch_stmt),
			    ಕೆಳಗಿನ_ಮೌಲ್ಯ, ಮೇಲಿನ_ಮೌಲ್ಯ, attrs);
  ಆದರೆ (label == error_mark_ಗಂಟು)
    label = NULL_ವೃಕ್ಷ;
  ಹಿಂತಿರುಗಿ label;
}

/* Finish the switch statement.  TYPE is the original type of the
   controlling expression of the switch, or NULL_TREE.  */

ಶೂನ್ಯ
c_ಮುಕ್ತಾಯ_switch (ವೃಕ್ಷ body, ವೃಕ್ಷ type)
{
  ರಚನೆ c_switch *cs = c_switch_ರಾಶಿ;
  location_t switch_location;

  SWITCH_STMT_BODY (cs->switch_stmt) = body;

  /* Emit warnings as needed.  */
  switch_location = ಅಭಿವ್ಯಕ್ತಿ_LOCATION (cs->switch_stmt);
  c_do_switch_warnings (cs->cases, switch_location,
			type ? type : SWITCH_STMT_TYPE (cs->switch_stmt),
			SWITCH_STMT_COND (cs->switch_stmt), cs->bool_cond_p);
  ಆದರೆ (c_switch_covers_all_cases_p (cs->cases,
				   SWITCH_STMT_TYPE (cs->switch_stmt)))
    SWITCH_STMT_ALL_CASES_P (cs->switch_stmt) = 1;
  SWITCH_STMT_NO_BREAK_P (cs->switch_stmt) = !cs->break_stmt_ನೋಡಿದ_p;

  /* Pop the stack.  */
  c_switch_ರಾಶಿ = cs->ಮುಂದಿನ;
  splay_ವೃಕ್ಷ_delete (cs->cases);
  c_release_switch_bindings (cs->bindings);
  XDELETE (cs);
}

/* Emit an if statement.  IF_LOCUS is the location of the 'if'.  COND,
   THEN_BLOCK and ELSE_BLOCK are expressions to be used; ELSE_BLOCK
   may be null.  */

ಶೂನ್ಯ
c_ಮುಕ್ತಾಯ_if_stmt (location_t if_locus, ವೃಕ್ಷ cond, ವೃಕ್ಷ then_ಖಂಡ,
		  ವೃಕ್ಷ else_ಖಂಡ)
{
  ವೃಕ್ಷ stmt;

  stmt = build3 (COND_ಅಭಿವ್ಯಕ್ತಿ, void_type_ಗಂಟು, cond, then_ಖಂಡ, else_ಖಂಡ);
  ಗಣ_ಅಭಿವ್ಯಕ್ತಿ_LOCATION (stmt, if_locus);
  ಕೂಡಿಸು_stmt (stmt);
}

ವೃಕ್ಷ
c_ಮುಕ್ತಾಯ_bc_stmt (location_t loc, ವೃಕ್ಷ label, ತಾರ್ಕಿಕ is_break, ವೃಕ್ಷ name)
{
  /* In switch statements break is sometimes stylistically used after
     a return statement.  This can lead to spurious warnings about
     control reaching the end of a non-void function when it is
     inlined.  Note that we are calling block_may_fallthru with
     language specific tree nodes; this works because
     block_may_fallthru returns true when given something it does not
     understand.  */
  ತಾರ್ಕಿಕ skip = !ಖಂಡ_may_fallthru (cur_stmt_list);

  ಆದರೆ (is_break)
    ಆಯ್ಕೆ (ಒಳ_statement & ~ಒಳ_NAMED_STMT)
      {
      ಸ್ಥಿತಿ 0:
	error_at (loc, "break statement not within loop or switch");
	ಹಿಂತಿರುಗಿ NULL_ವೃಕ್ಷ;
      ಸ್ಥಿತಿ ಒಳ_OMP_ಖಂಡ:
	error_at (loc, "invalid exit from OpenMP structured block");
	ಹಿಂತಿರುಗಿ NULL_ವೃಕ್ಷ;
      ಸ್ಥಿತಿ ಒಳ_OMP_FOR:
	error_at (loc, "break statement used with OpenMP for loop");
	ಹಿಂತಿರುಗಿ NULL_ವೃಕ್ಷ;
      ಸ್ಥಿತಿ ಒಳ_ITERATION_STMT:
      ಸ್ಥಿತಿ ಒಳ_OBJC_FOREACH:
	ನಿಲ್ಲಿಸು;
      ಪೂರ್ವನಿಯೋಜಿತ:
	gcc_assert (ಒಳ_statement & ಒಳ_SWITCH_STMT);
	c_switch_ರಾಶಿ->break_stmt_ನೋಡಿದ_p = ನಿಜ;
	ನಿಲ್ಲಿಸು;
      }
  ಇಲ್ಲದಿದ್ದರೆ
    ಆಯ್ಕೆ (ಒಳ_statement & ~(ಒಳ_SWITCH_STMT | ಒಳ_NAMED_STMT))
      {
      ಸ್ಥಿತಿ 0:
	error_at (loc, "continue statement not within a loop");
	ಹಿಂತಿರುಗಿ NULL_ವೃಕ್ಷ;
      ಸ್ಥಿತಿ ಒಳ_OMP_ಖಂಡ:
	error_at (loc, "invalid exit from OpenMP structured block");
	ಹಿಂತಿರುಗಿ NULL_ವೃಕ್ಷ;
      ಸ್ಥಿತಿ ಒಳ_ITERATION_STMT:
      ಸ್ಥಿತಿ ಒಳ_OMP_FOR:
      ಸ್ಥಿತಿ ಒಳ_OBJC_FOREACH:
	ನಿಲ್ಲಿಸು;
      ಪೂರ್ವನಿಯೋಜಿತ:
	gcc_unreachable ();
      }

  ಆದರೆ (skip)
    ಹಿಂತಿರುಗಿ NULL_ವೃಕ್ಷ;
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ ((ಒಳ_statement & ಒಳ_OBJC_FOREACH)
	   && !(is_break && (ಒಳ_statement & ಒಳ_SWITCH_STMT))
	   && name == NULL_ವೃಕ್ಷ)
    {
      /* The foreach expander produces low-level code using gotos instead
	 of a structured loop construct.  */
      gcc_assert (label);
      ಹಿಂತಿರುಗಿ ಕೂಡಿಸು_stmt (build_stmt (loc, GOTO_ಅಭಿವ್ಯಕ್ತಿ, label));
    }
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (name && C_DECL_LOOP_NAME (name) && C_DECL_SWITCH_NAME (name))
    {
      label = DECL_CHAIN (name);
      ಆದರೆ (!is_break)
	label = DECL_CHAIN (label);
      /* Foreach expander from some outer level.  */
      ಹಿಂತಿರುಗಿ ಕೂಡಿಸು_stmt (build_stmt (loc, GOTO_ಅಭಿವ್ಯಕ್ತಿ, label));
    }
  ಹಿಂತಿರುಗಿ ಕೂಡಿಸು_stmt (build_stmt (loc, is_break ? BREAK_STMT : CONTINUE_STMT,
			       name));
}

/* A helper routine for c_process_expr_stmt and c_finish_stmt_expr.  */

ಸ್ಥಿರ ಶೂನ್ಯ
emit_side_effect_warnings (location_t loc, ವೃಕ್ಷ ಅಭಿವ್ಯಕ್ತಿ)
{
  maybe_warn_nodiscard (loc, ಅಭಿವ್ಯಕ್ತಿ);
  ಆದರೆ (!warn_ಬಳಸದ_ಮೌಲ್ಯ)
    ಹಿಂತಿರುಗಿ;
  ಆದರೆ (ಅಭಿವ್ಯಕ್ತಿ == error_mark_ಗಂಟು)
    ;
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!ವೃಕ್ಷ_SIDE_EFFECTS (ಅಭಿವ್ಯಕ್ತಿ))
    {
      ಆದರೆ (!VOID_TYPE_P (ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ))
	  && !warning_suppressed_p (ಅಭಿವ್ಯಕ್ತಿ, OPT_Wunused_ಮೌಲ್ಯ))
	warning_at (loc, OPT_Wunused_ಮೌಲ್ಯ, "statement with no effect");
    }
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ಅಭಿವ್ಯಕ್ತಿ) == COMPOUND_ಅಭಿವ್ಯಕ್ತಿ)
    {
      ವೃಕ್ಷ r = ಅಭಿವ್ಯಕ್ತಿ;
      location_t cloc = loc;
      ಆಗ (ವೃಕ್ಷ_ಸಂಕೇತ (r) == COMPOUND_ಅಭಿವ್ಯಕ್ತಿ)
	{
	  ಆದರೆ (ಅಭಿವ್ಯಕ್ತಿ_HAS_LOCATION (r))
	    cloc = ಅಭಿವ್ಯಕ್ತಿ_LOCATION (r);
	  r = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (r, 1);
	}
      ಆದರೆ (!ವೃಕ್ಷ_SIDE_EFFECTS (r)
	  && !VOID_TYPE_P (ವೃಕ್ಷ_TYPE (r))
	  && !CONVERT_ಅಭಿವ್ಯಕ್ತಿ_P (r)
	  && !warning_suppressed_p (r, OPT_Wunused_ಮೌಲ್ಯ)
	  && !warning_suppressed_p (ಅಭಿವ್ಯಕ್ತಿ, OPT_Wunused_ಮೌಲ್ಯ))
	warning_at (cloc, OPT_Wunused_ಮೌಲ್ಯ,
		    "right-hand operand of comma expression has no effect");
    }
  ಇಲ್ಲದಿದ್ದರೆ
    warn_if_ಬಳಸದ_ಮೌಲ್ಯ (ಅಭಿವ್ಯಕ್ತಿ, loc);
}

/* Process an expression as if it were a complete statement.  Emit
   diagnostics, but do not call ADD_STMT.  LOC is the location of the
   statement.  */

ವೃಕ್ಷ
c_process_ಅಭಿವ್ಯಕ್ತಿ_stmt (location_t loc, ವೃಕ್ಷ ಅಭಿವ್ಯಕ್ತಿ)
{
  ವೃಕ್ಷ exprv;

  ಆದರೆ (!ಅಭಿವ್ಯಕ್ತಿ)
    ಹಿಂತಿರುಗಿ NULL_ವೃಕ್ಷ;

  ಅಭಿವ್ಯಕ್ತಿ = c_fully_fold (ಅಭಿವ್ಯಕ್ತಿ, ಸುಳ್ಳು, ಖಾಲಿ);

  ಆದರೆ (warn_sequence_ಬಿಂದು)
    verify_sequence_points (ಅಭಿವ್ಯಕ್ತಿ);

  ಆದರೆ (ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ) != error_mark_ಗಂಟು
      && !COMPLETE_OR_VOID_TYPE_P (ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ))
      && ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ)) != ARRAY_TYPE)
    error_at (loc, "expression statement has incomplete type");

  /* If we're not processing a statement expression, warn about unused values.
     Warnings for statement expressions will be emitted later, once we figure
     out which is the result.  */
  ಆದರೆ (!STATEMENT_LIST_STMT_ಅಭಿವ್ಯಕ್ತಿ (cur_stmt_list)
      && (warn_ಬಳಸದ_ಮೌಲ್ಯ || warn_ಬಳಸದ_ಫಲಿತಾಂಶ))
    emit_side_effect_warnings (ಅಭಿವ್ಯಕ್ತಿ_LOC_OR_LOC (ಅಭಿವ್ಯಕ್ತಿ, loc), ಅಭಿವ್ಯಕ್ತಿ);

  exprv = ಅಭಿವ್ಯಕ್ತಿ;
  ಆಗ (ವೃಕ್ಷ_ಸಂಕೇತ (exprv) == COMPOUND_ಅಭಿವ್ಯಕ್ತಿ)
    exprv = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (exprv, 1);
  ಆಗ (CONVERT_ಅಭಿವ್ಯಕ್ತಿ_P (exprv))
    exprv = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (exprv, 0);
  ಆದರೆ (DECL_P (exprv)
      || handled_component_p (exprv)
      || ವೃಕ್ಷ_ಸಂಕೇತ (exprv) == ADDR_ಅಭಿವ್ಯಕ್ತಿ)
    mark_exp_read (exprv);

  /* If the expression is not of a type to which we cannot assign a line
     number, wrap the thing in a no-op NOP_EXPR.  */
  ಆದರೆ (DECL_P (ಅಭಿವ್ಯಕ್ತಿ) || CONSTANT_CLASS_P (ಅಭಿವ್ಯಕ್ತಿ))
    {
      ಅಭಿವ್ಯಕ್ತಿ = build1 (NOP_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ), ಅಭಿವ್ಯಕ್ತಿ);
      ಗಣ_ಅಭಿವ್ಯಕ್ತಿ_LOCATION (ಅಭಿವ್ಯಕ್ತಿ, loc);
    }

  ಹಿಂತಿರುಗಿ ಅಭಿವ್ಯಕ್ತಿ;
}

/* Emit an expression as a statement.  LOC is the location of the
   expression.  */

ವೃಕ್ಷ
c_ಮುಕ್ತಾಯ_ಅಭಿವ್ಯಕ್ತಿ_stmt (location_t loc, ವೃಕ್ಷ ಅಭಿವ್ಯಕ್ತಿ)
{
  ಆದರೆ (ಅಭಿವ್ಯಕ್ತಿ)
    ಹಿಂತಿರುಗಿ ಕೂಡಿಸು_stmt (c_process_ಅಭಿವ್ಯಕ್ತಿ_stmt (loc, ಅಭಿವ್ಯಕ್ತಿ));
  ಇಲ್ಲದಿದ್ದರೆ
    ಹಿಂತಿರುಗಿ ಖಾಲಿ;
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
  keep_ಮುಂದಿನ_level ();
  ret = c_begin_compound_stmt (ನಿಜ);

  c_bindings_ಆರಂಭ_stmt_ಅಭಿವ್ಯಕ್ತಿ (c_switch_ರಾಶಿ == ಖಾಲಿ
			      ? ಖಾಲಿ
			      : c_switch_ರಾಶಿ->bindings);

  /* Mark the current statement list as belonging to a statement list.  */
  STATEMENT_LIST_STMT_ಅಭಿವ್ಯಕ್ತಿ (ret) = 1;

  ಹಿಂತಿರುಗಿ ret;
}

/* LOC is the location of the compound statement to which this body
   belongs.  */

ವೃಕ್ಷ
c_ಮುಕ್ತಾಯ_stmt_ಅಭಿವ್ಯಕ್ತಿ (location_t loc, ವೃಕ್ಷ body)
{
  ವೃಕ್ಷ ಕೊನೆಯ, type, tmp, val;
  ವೃಕ್ಷ *ಕೊನೆಯ_p;

  body = c_ಕೊನೆ_compound_stmt (loc, body, ನಿಜ);

  c_bindings_ಕೊನೆ_stmt_ಅಭಿವ್ಯಕ್ತಿ (c_switch_ರಾಶಿ == ಖಾಲಿ
			    ? ಖಾಲಿ
			    : c_switch_ರಾಶಿ->bindings);

  /* Locate the last statement in BODY.  See c_end_compound_stmt
     about always returning a BIND_EXPR.  */
  ಕೊನೆಯ_p = &BIND_ಅಭಿವ್ಯಕ್ತಿ_BODY (body);
  ಕೊನೆಯ = BIND_ಅಭಿವ್ಯಕ್ತಿ_BODY (body);

 continue_searching:
  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ಕೊನೆಯ) == STATEMENT_LIST)
    {
      ವೃಕ್ಷ_stmt_iterator l = tsi_ಕೊನೆಯ (ಕೊನೆಯ);

      ಆಗ (!tsi_ಕೊನೆ_p (l) && ವೃಕ್ಷ_ಸಂಕೇತ (tsi_stmt (l)) == DEBUG_BEGIN_STMT)
	tsi_prev (&l);

      /* This can happen with degenerate cases like ({ }).  No value.  */
      ಆದರೆ (tsi_ಕೊನೆ_p (l))
	ಹಿಂತಿರುಗಿ body;

      /* If we're supposed to generate side effects warnings, process
	 all of the statements except the last.  */
      ಆದರೆ (warn_ಬಳಸದ_ಮೌಲ್ಯ || warn_ಬಳಸದ_ಫಲಿತಾಂಶ)
	{
	  ಗಾಗಿ (ವೃಕ್ಷ_stmt_iterator i = tsi_ಆರಂಭ (ಕೊನೆಯ);
	       tsi_stmt (i) != tsi_stmt (l); tsi_ಮುಂದಿನ (&i))
	    {
	      location_t tloc;
	      ವೃಕ್ಷ t = tsi_stmt (i);

	      tloc = ಅಭಿವ್ಯಕ್ತಿ_HAS_LOCATION (t) ? ಅಭಿವ್ಯಕ್ತಿ_LOCATION (t) : loc;
	      emit_side_effect_warnings (tloc, t);
	    }
	}
      ಕೊನೆಯ_p = tsi_stmt_ptr (l);
      ಕೊನೆಯ = *ಕೊನೆಯ_p;
    }

  /* If the end of the list is exception related, then the list was split
     by a call to push_cleanup.  Continue searching.  */
  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ಕೊನೆಯ) == TRY_FINALLY_ಅಭಿವ್ಯಕ್ತಿ
      || ವೃಕ್ಷ_ಸಂಕೇತ (ಕೊನೆಯ) == TRY_CATCH_ಅಭಿವ್ಯಕ್ತಿ)
    {
      ಕೊನೆಯ_p = &ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (ಕೊನೆಯ, 0);
      ಕೊನೆಯ = *ಕೊನೆಯ_p;
      ಹೋಗು continue_searching;
    }

  ಆದರೆ (ಕೊನೆಯ == error_mark_ಗಂಟು)
    ಹಿಂತಿರುಗಿ ಕೊನೆಯ;

  /* In the case that the BIND_EXPR is not necessary, return the
     expression out from inside it.  */
  ಆದರೆ ((ಕೊನೆಯ == BIND_ಅಭಿವ್ಯಕ್ತಿ_BODY (body)
       /* Skip nested debug stmts.  */
       || ಕೊನೆಯ == ಅಭಿವ್ಯಕ್ತಿ_ಮೊದಲ (BIND_ಅಭಿವ್ಯಕ್ತಿ_BODY (body)))
      && BIND_ಅಭಿವ್ಯಕ್ತಿ_VARS (body) == ಖಾಲಿ)
    {
      /* Even if this looks constant, do not allow it in a constant
	 expression.  */
      ಕೊನೆಯ = c_wrap_maybe_const (ಕೊನೆಯ, ನಿಜ);
      /* Do not warn if the return value of a statement expression is
	 unused.  */
      suppress_warning (ಕೊನೆಯ, OPT_Wunused);
      ಹಿಂತಿರುಗಿ ಕೊನೆಯ;
    }

  /* Extract the type of said expression.  */
  type = ವೃಕ್ಷ_TYPE (ಕೊನೆಯ);

  /* If we're not returning a value at all, then the BIND_EXPR that
     we already have is a fine expression to return.  */
  ಆದರೆ (!type || VOID_TYPE_P (type))
    ಹಿಂತಿರುಗಿ body;

  /* Now that we've located the expression containing the value, it seems
     silly to make voidify_wrapper_expr repeat the process.  Create a
     temporary of the appropriate type and stick it in a TARGET_EXPR.  */
  tmp = create_tmp_var_raw (type);

  /* Unwrap a no-op NOP_EXPR as added by c_finish_expr_stmt.  This avoids
     tree_expr_nonnegative_p giving up immediately.  */
  val = ಕೊನೆಯ;
  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (val) == NOP_ಅಭಿವ್ಯಕ್ತಿ
      && ವೃಕ್ಷ_TYPE (val) == ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (val, 0)))
    val = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (val, 0);

  *ಕೊನೆಯ_p = build2 (MODIFY_ಅಭಿವ್ಯಕ್ತಿ, void_type_ಗಂಟು, tmp, val);
  ಗಣ_ಅಭಿವ್ಯಕ್ತಿ_LOCATION (*ಕೊನೆಯ_p, ಅಭಿವ್ಯಕ್ತಿ_LOCATION (ಕೊನೆಯ));

  {
    ವೃಕ್ಷ t = build4 (ಗುರಿ_ಅಭಿವ್ಯಕ್ತಿ, type, tmp, body, NULL_ವೃಕ್ಷ, NULL_ವೃಕ್ಷ);
    ಗಣ_ಅಭಿವ್ಯಕ್ತಿ_LOCATION (t, loc);
    ಹಿಂತಿರುಗಿ t;
  }
}

/* Begin and end compound statements.  This is as simple as pushing
   and popping new statement lists from the tree.  */

ವೃಕ್ಷ
c_begin_compound_stmt (ತಾರ್ಕಿಕ do_scope)
{
  ವೃಕ್ಷ stmt = ತಳ್ಳು_stmt_list ();
  ಆದರೆ (do_scope)
    ತಳ್ಳು_scope ();
  ಹಿಂತಿರುಗಿ stmt;
}

/* End a compound statement.  STMT is the statement.  LOC is the
   location of the compound statement-- this is usually the location
   of the opening brace.  */

ವೃಕ್ಷ
c_ಕೊನೆ_compound_stmt (location_t loc, ವೃಕ್ಷ stmt, ತಾರ್ಕಿಕ do_scope)
{
  ವೃಕ್ಷ ಖಂಡ = ಖಾಲಿ;

  ಆದರೆ (do_scope)
    {
      ಆದರೆ (c_dialect_objc ())
	objc_clear_super_receiver ();
      ಖಂಡ = ತೆಗೆ_scope ();
    }

  stmt = ತೆಗೆ_stmt_list (stmt);
  stmt = c_build_bind_ಅಭಿವ್ಯಕ್ತಿ (loc, ಖಂಡ, stmt);

  /* If this compound statement is nested immediately inside a statement
     expression, then force a BIND_EXPR to be created.  Otherwise we'll
     do the wrong thing for ({ { 1; } }) or ({ 1; { } }).  In particular,
     STATEMENT_LISTs merge, and thus we can lose track of what statement
     was really last.  */
  ಆದರೆ (building_stmt_list_p ()
      && STATEMENT_LIST_STMT_ಅಭಿವ್ಯಕ್ತಿ (cur_stmt_list)
      && ವೃಕ್ಷ_ಸಂಕೇತ (stmt) != BIND_ಅಭಿವ್ಯಕ್ತಿ)
    {
      stmt = build3 (BIND_ಅಭಿವ್ಯಕ್ತಿ, void_type_ಗಂಟು, ಖಾಲಿ, stmt, ಖಾಲಿ);
      ವೃಕ್ಷ_SIDE_EFFECTS (stmt) = 1;
      ಗಣ_ಅಭಿವ್ಯಕ್ತಿ_LOCATION (stmt, loc);
    }

  ಹಿಂತಿರುಗಿ stmt;
}

/* Queue a cleanup.  CLEANUP is an expression/statement to be executed
   when the current scope is exited.  EH_ONLY is true when this is not
   meant to apply to normal control flow transfer.  */

ಶೂನ್ಯ
ತಳ್ಳು_cleanup (ವೃಕ್ಷ decl, ವೃಕ್ಷ cleanup, ತಾರ್ಕಿಕ eh_only)
{
  ಎಣಿಕೆ ವೃಕ್ಷ_ಸಂಕೇತ_2 ಸಂಕೇತ_2;
  ವೃಕ್ಷ stmt, list;
  ತಾರ್ಕಿಕ stmt_ಅಭಿವ್ಯಕ್ತಿ;

  ಸಂಕೇತ_2 = eh_only ? TRY_CATCH_ಅಭಿವ್ಯಕ್ತಿ : TRY_FINALLY_ಅಭಿವ್ಯಕ್ತಿ;
  stmt = build_stmt (DECL_ಮೂಲ_LOCATION (decl), ಸಂಕೇತ_2, ಖಾಲಿ, cleanup);
  ಕೂಡಿಸು_stmt (stmt);
  stmt_ಅಭಿವ್ಯಕ್ತಿ = STATEMENT_LIST_STMT_ಅಭಿವ್ಯಕ್ತಿ (cur_stmt_list);
  list = ತಳ್ಳು_stmt_list ();
  ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (stmt, 0) = list;
  STATEMENT_LIST_STMT_ಅಭಿವ್ಯಕ್ತಿ (list) = stmt_ಅಭಿವ್ಯಕ್ತಿ;
}

/* Build a vector comparison of ARG0 and ARG1 using CODE opcode
   into a value of TYPE type.  Comparison is done via VEC_COND_EXPR.  */

ಸ್ಥಿರ ವೃಕ್ಷ
build_vec_cmp (ವೃಕ್ಷ_ಸಂಕೇತ_2 ಸಂಕೇತ_2, ವೃಕ್ಷ type,
	       ವೃಕ್ಷ arg0, ವೃಕ್ಷ arg1)
{
  ವೃಕ್ಷ zero_vec = build_zero_cst (type);
  ವೃಕ್ಷ minus_one_vec = build_minus_one_cst (type);
  ವೃಕ್ಷ cmp_type = truth_type_for (ವೃಕ್ಷ_TYPE (arg0));
  ವೃಕ್ಷ cmp = build2 (ಸಂಕೇತ_2, cmp_type, arg0, arg1);
  ಹಿಂತಿರುಗಿ build3 (VEC_COND_ಅಭಿವ್ಯಕ್ತಿ, type, cmp, minus_one_vec, zero_vec);
}

/* Possibly warn about an address of OP never being NULL in a comparison
   operation CODE involving null.  */

ಸ್ಥಿರ ಶೂನ್ಯ
maybe_warn_for_null_ವಿಳಾಸ (location_t loc, ವೃಕ್ಷ op, ವೃಕ್ಷ_ಸಂಕೇತ_2 ಸಂಕೇತ_2)
{
  /* Prevent warnings issued for macro expansion.  */
  ಆದರೆ (!warn_ವಿಳಾಸ
      || warning_suppressed_p (op, OPT_Waddress)
      || from_macro_expansion_at (loc))
    ಹಿಂತಿರುಗಿ;

  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (op) == NOP_ಅಭಿವ್ಯಕ್ತಿ)
    {
      /* Allow casts to intptr_t to suppress the warning.  */
      ವೃಕ್ಷ type = ವೃಕ್ಷ_TYPE (op);
      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (type) == INTEGER_TYPE)
	ಹಿಂತಿರುಗಿ;
      op = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (op, 0);
    }

  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (op) == ಸೂಚಕ_PLUS_ಅಭಿವ್ಯಕ್ತಿ)
    {
      /* Allow a cast to void* to suppress the warning.  */
      ವೃಕ್ಷ type = ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_TYPE (op));
      ಆದರೆ (VOID_TYPE_P (type))
	ಹಿಂತಿರುಗಿ;

      /* Adding any value to a null pointer, including zero, is undefined
	 in C.  This includes the expression &p[0] where p is the null
	 pointer, although &p[0] will have been folded to p by this point
	 and so not diagnosed.  */
      ಆದರೆ (ಸಂಕೇತ_2 == EQ_ಅಭಿವ್ಯಕ್ತಿ)
	warning_at (loc, OPT_Waddress,
		    "the comparison will always evaluate as %<false%> "
		    "for the pointer operand in %qE must not be NULL",
		    op);
      ಇಲ್ಲದಿದ್ದರೆ
	warning_at (loc, OPT_Waddress,
		    "the comparison will always evaluate as %<true%> "
		    "for the pointer operand in %qE must not be NULL",
		    op);

      ಹಿಂತಿರುಗಿ;
    }

  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (op) != ADDR_ಅಭಿವ್ಯಕ್ತಿ)
    ಹಿಂತಿರುಗಿ;

  op = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (op, 0);

  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (op) == IMAGPART_ಅಭಿವ್ಯಕ್ತಿ
      || ವೃಕ್ಷ_ಸಂಕೇತ (op) == REALPART_ಅಭಿವ್ಯಕ್ತಿ)
    {
      /* The address of either complex part may not be null.  */
      ಆದರೆ (ಸಂಕೇತ_2 == EQ_ಅಭಿವ್ಯಕ್ತಿ)
	warning_at (loc, OPT_Waddress,
		    "the comparison will always evaluate as %<false%> "
		    "for the address of %qE will never be NULL",
		    op);
      ಇಲ್ಲದಿದ್ದರೆ
	warning_at (loc, OPT_Waddress,
		    "the comparison will always evaluate as %<true%> "
		    "for the address of %qE will never be NULL",
		    op);
      ಹಿಂತಿರುಗಿ;
    }

  /* Set to true in the loop below if OP dereferences is operand.
     In such a case the ultimate target need not be a decl for
     the null [in]equality test to be constant.  */
  ತಾರ್ಕಿಕ deref = ಸುಳ್ಳು;

  /* Get the outermost array or object, or member.  */
  ಆಗ (handled_component_p (op))
    {
      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (op) == COMPONENT_REF)
	{
	  /* Get the member (its address is never null).  */
	  op = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (op, 1);
	  ನಿಲ್ಲಿಸು;
	}

      /* Get the outer array/object to refer to in the warning.  */
      op = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (op, 0);
      deref = ನಿಜ;
    }

  ಆದರೆ ((!deref && !decl_with_nonnull_addr_p (op))
      || from_macro_expansion_at (loc))
    ಹಿಂತಿರುಗಿ;

  ತಾರ್ಕಿಕ w;
  ಆದರೆ (ಸಂಕೇತ_2 == EQ_ಅಭಿವ್ಯಕ್ತಿ)
    w = warning_at (loc, OPT_Waddress,
		    "the comparison will always evaluate as %<false%> "
		    "for the address of %qE will never be NULL",
		    op);
  ಇಲ್ಲದಿದ್ದರೆ
    w = warning_at (loc, OPT_Waddress,
		    "the comparison will always evaluate as %<true%> "
		    "for the address of %qE will never be NULL",
		    op);

  ಆದರೆ (w && DECL_P (op))
    inform (DECL_ಮೂಲ_LOCATION (op), "%qD declared here", op);
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
build_ದ್ವಿಮಾನ_op (location_t location, ಎಣಿಕೆ ವೃಕ್ಷ_ಸಂಕೇತ_2 ಸಂಕೇತ_2,
		 ವೃಕ್ಷ orig_op0, ವೃಕ್ಷ orig_op1, ತಾರ್ಕಿಕ convert_p)
{
  ವೃಕ್ಷ type0, type1, orig_type0, orig_type1;
  ವೃಕ್ಷ eptype;
  ಎಣಿಕೆ ವೃಕ್ಷ_ಸಂಕೇತ_2 code0, code1;
  ವೃಕ್ಷ op0, op1;
  ವೃಕ್ಷ ret = error_mark_ಗಂಟು;
  ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *invalid_op_diag;
  ತಾರ್ಕಿಕ op0_int_operands, op1_int_operands;
  ತಾರ್ಕಿಕ int_const, int_const_or_ಅತಿಪ್ರವಾಹ, int_operands;

  /* Expression code to give to the expression when it is built.
     Normally this is CODE, which is what the caller asked for,
     but in some special cases we change it.  */
  ಎಣಿಕೆ ವೃಕ್ಷ_ಸಂಕೇತ_2 resultcode = ಸಂಕೇತ_2;

  /* Data type in which the computation is to be performed.
     In the simplest cases this is the common type of the arguments.  */
  ವೃಕ್ಷ ಫಲಿತಾಂಶ_type = ಖಾಲಿ;

  /* When the computation is in excess precision, the type of the
     final EXCESS_PRECISION_EXPR.  */
  ವೃಕ್ಷ semantic_ಫಲಿತಾಂಶ_type = ಖಾಲಿ;

  /* Nonzero means operands have already been type-converted
     in whatever way is necessary.
     Zero means they need to be converted to RESULT_TYPE.  */
  ಪೂರ್ಣಾಂಕ converted = 0;

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
  ಪೂರ್ಣಾಂಕ shorten = 0;

  /* Nonzero if this is a comparison operation;
     if both args are promoted shorts, compare the original shorts.
     Also implies COMMON.  */
  ಪೂರ್ಣಾಂಕ short_compare = 0;

  /* Nonzero if this is a right-shift operation, which can be computed on the
     original short and then promoted if the operand is a promoted short.  */
  ಪೂರ್ಣಾಂಕ short_ಸರಿಸು = 0;

  /* Nonzero means set RESULT_TYPE to the common type of the args.  */
  ಪೂರ್ಣಾಂಕ common = 0;

  /* True means types are compatible as far as ObjC is concerned.  */
  ತಾರ್ಕಿಕ objc_ok;

  /* True means this is an arithmetic operation that may need excess
     precision.  */
  ತಾರ್ಕಿಕ may_need_excess_precision;

  /* True means this is a boolean operation that converts both its
     operands to truth-values.  */
  ತಾರ್ಕಿಕ boolean_op = ಸುಳ್ಳು;

  /* Remember whether we're doing / or %.  */
  ತಾರ್ಕಿಕ doing_div_or_mod = ಸುಳ್ಳು;

  /* Remember whether we're doing << or >>.  */
  ತಾರ್ಕಿಕ doing_ಸರಿಸು = ಸುಳ್ಳು;

  /* Tree holding instrumentation expression.  */
  ವೃಕ್ಷ instrument_ಅಭಿವ್ಯಕ್ತಿ = ಖಾಲಿ;

  ಆದರೆ (location == UNKNOWN_LOCATION)
    location = ಒಳಹರಿವು_location;

  op0 = orig_op0;
  op1 = orig_op1;

  op0_int_operands = ಅಭಿವ್ಯಕ್ತಿ_INT_CONST_OPERANDS (orig_op0);
  ಆದರೆ (op0_int_operands)
    op0 = remove_c_maybe_const_ಅಭಿವ್ಯಕ್ತಿ (op0);
  op1_int_operands = ಅಭಿವ್ಯಕ್ತಿ_INT_CONST_OPERANDS (orig_op1);
  ಆದರೆ (op1_int_operands)
    op1 = remove_c_maybe_const_ಅಭಿವ್ಯಕ್ತಿ (op1);
  int_operands = (op0_int_operands && op1_int_operands);
  ಆದರೆ (int_operands)
    {
      int_const_or_ಅತಿಪ್ರವಾಹ = (ವೃಕ್ಷ_ಸಂಕೇತ (orig_op0) == INTEGER_CST
			       && ವೃಕ್ಷ_ಸಂಕೇತ (orig_op1) == INTEGER_CST);
      int_const = (int_const_or_ಅತಿಪ್ರವಾಹ
		   && !ವೃಕ್ಷ_ಅತಿಪ್ರವಾಹ (orig_op0)
		   && !ವೃಕ್ಷ_ಅತಿಪ್ರವಾಹ (orig_op1));
    }
  ಇಲ್ಲದಿದ್ದರೆ
    int_const = int_const_or_ಅತಿಪ್ರವಾಹ = ಸುಳ್ಳು;

  /* Do not apply default conversion in mixed vector/scalar expression.  */
  ಆದರೆ (convert_p
      && ಸದಿಶ_TYPE_P (ವೃಕ್ಷ_TYPE (op0)) == ಸದಿಶ_TYPE_P (ವೃಕ್ಷ_TYPE (op1)))
    {
      op0 = default_conversion (op0);
      op1 = default_conversion (op1);
    }

  orig_type0 = type0 = ವೃಕ್ಷ_TYPE (op0);

  orig_type1 = type1 = ವೃಕ್ಷ_TYPE (op1);

  /* The expression codes of the data types of the arguments tell us
     whether the arguments are integers, floating, pointers, etc.  */
  code0 = ವೃಕ್ಷ_ಸಂಕೇತ (type0);
  code1 = ವೃಕ್ಷ_ಸಂಕೇತ (type1);

  /* Strip NON_LVALUE_EXPRs, etc., since we aren't using as an lvalue.  */
  STRIP_TYPE_NOPS (op0);
  STRIP_TYPE_NOPS (op1);

  /* If an error was already reported for one of the arguments,
     avoid reporting another error.  */

  ಆದರೆ (code0 == ERROR_MARK || code1 == ERROR_MARK)
    ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;

  ಆದರೆ (code0 == ಸೂಚಕ_TYPE
      && reject_gcc_builtin (op0, ಅಭಿವ್ಯಕ್ತಿ_LOCATION (orig_op0)))
    ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;

  ಆದರೆ (code1 == ಸೂಚಕ_TYPE
      && reject_gcc_builtin (op1, ಅಭಿವ್ಯಕ್ತಿ_LOCATION (orig_op1)))
    ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;

  ಆದರೆ ((invalid_op_diag
       = targetm.invalid_ದ್ವಿಮಾನ_op (ಸಂಕೇತ_2, type0, type1)))
    {
      error_at (location, invalid_op_diag);
      ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
    }

  ಆಯ್ಕೆ (ಸಂಕೇತ_2)
    {
    ಸ್ಥಿತಿ PLUS_ಅಭಿವ್ಯಕ್ತಿ:
    ಸ್ಥಿತಿ MINUS_ಅಭಿವ್ಯಕ್ತಿ:
    ಸ್ಥಿತಿ MULT_ಅಭಿವ್ಯಕ್ತಿ:
    ಸ್ಥಿತಿ TRUNC_DIV_ಅಭಿವ್ಯಕ್ತಿ:
    ಸ್ಥಿತಿ CEIL_DIV_ಅಭಿವ್ಯಕ್ತಿ:
    ಸ್ಥಿತಿ FLOOR_DIV_ಅಭಿವ್ಯಕ್ತಿ:
    ಸ್ಥಿತಿ ಸುತ್ತು_DIV_ಅಭಿವ್ಯಕ್ತಿ:
    ಸ್ಥಿತಿ EXACT_DIV_ಅಭಿವ್ಯಕ್ತಿ:
      may_need_excess_precision = ನಿಜ;
      ನಿಲ್ಲಿಸು;

    ಸ್ಥಿತಿ EQ_ಅಭಿವ್ಯಕ್ತಿ:
    ಸ್ಥಿತಿ NE_ಅಭಿವ್ಯಕ್ತಿ:
    ಸ್ಥಿತಿ LE_ಅಭಿವ್ಯಕ್ತಿ:
    ಸ್ಥಿತಿ GE_ಅಭಿವ್ಯಕ್ತಿ:
    ಸ್ಥಿತಿ LT_ಅಭಿವ್ಯಕ್ತಿ:
    ಸ್ಥಿತಿ GT_ಅಭಿವ್ಯಕ್ತಿ:
      /* Excess precision for implicit conversions of integers to
	 floating point in C11 and later.  */
      may_need_excess_precision = (flag_isoc11
				   && (ANY_INTEGRAL_TYPE_P (type0)
				       || ANY_INTEGRAL_TYPE_P (type1)));
      ನಿಲ್ಲಿಸು;

    ಪೂರ್ವನಿಯೋಜಿತ:
      may_need_excess_precision = ಸುಳ್ಳು;
      ನಿಲ್ಲಿಸು;
    }
  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (op0) == EXCESS_PRECISION_ಅಭಿವ್ಯಕ್ತಿ)
    {
      op0 = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (op0, 0);
      type0 = ವೃಕ್ಷ_TYPE (op0);
    }
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (may_need_excess_precision
	   && (eptype = excess_precision_type (type0)) != NULL_ವೃಕ್ಷ)
    {
      type0 = eptype;
      op0 = convert (eptype, op0);
    }
  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (op1) == EXCESS_PRECISION_ಅಭಿವ್ಯಕ್ತಿ)
    {
      op1 = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (op1, 0);
      type1 = ವೃಕ್ಷ_TYPE (op1);
    }
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (may_need_excess_precision
	   && (eptype = excess_precision_type (type1)) != NULL_ವೃಕ್ಷ)
    {
      type1 = eptype;
      op1 = convert (eptype, op1);
    }

  objc_ok = objc_compare_types (type0, type1, -3, NULL_ವೃಕ್ಷ);

  /* In case when one of the operands of the binary operation is
     a vector and another is a scalar -- convert scalar to vector.  */
  ಆದರೆ ((gnu_ಸದಿಶ_type_p (type0) && code1 != ಸದಿಶ_TYPE)
      || (gnu_ಸದಿಶ_type_p (type1) && code0 != ಸದಿಶ_TYPE))
    {
      ಎಣಿಕೆ stv_conv convert_flag = scalar_ಗಮ್ಯ_ಸದಿಶ (location, ಸಂಕೇತ_2, orig_op0,
						     orig_op1, ನಿಜ);

      ಆಯ್ಕೆ (convert_flag)
	{
	  ಸ್ಥಿತಿ stv_error:
	    ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
	  ಸ್ಥಿತಿ stv_firstarg:
	    {
              ತಾರ್ಕಿಕ maybe_const = ನಿಜ;
              ವೃಕ್ಷ sc;
              sc = c_fully_fold (op0, ಸುಳ್ಳು, &maybe_const);
              sc = save_ಅಭಿವ್ಯಕ್ತಿ (sc);
              sc = convert (ವೃಕ್ಷ_TYPE (type1), sc);
              op0 = build_ಸದಿಶ_from_val (type1, sc);
              ಆದರೆ (!maybe_const)
                op0 = c_wrap_maybe_const (op0, ನಿಜ);
              orig_type0 = type0 = ವೃಕ್ಷ_TYPE (op0);
              code0 = ವೃಕ್ಷ_ಸಂಕೇತ (type0);
              converted = 1;
              ನಿಲ್ಲಿಸು;
	    }
	  ಸ್ಥಿತಿ stv_secondarg:
	    {
	      ತಾರ್ಕಿಕ maybe_const = ನಿಜ;
	      ವೃಕ್ಷ sc;
	      sc = c_fully_fold (op1, ಸುಳ್ಳು, &maybe_const);
	      sc = save_ಅಭಿವ್ಯಕ್ತಿ (sc);
	      sc = convert (ವೃಕ್ಷ_TYPE (type0), sc);
	      op1 = build_ಸದಿಶ_from_val (type0, sc);
	      ಆದರೆ (!maybe_const)
		op1 = c_wrap_maybe_const (op1, ನಿಜ);
	      orig_type1 = type1 = ವೃಕ್ಷ_TYPE (op1);
	      code1 = ವೃಕ್ಷ_ಸಂಕೇತ (type1);
	      converted = 1;
	      ನಿಲ್ಲಿಸು;
	    }
	  ಪೂರ್ವನಿಯೋಜಿತ:
	    ನಿಲ್ಲಿಸು;
	}
    }

  ಆಯ್ಕೆ (ಸಂಕೇತ_2)
    {
    ಸ್ಥಿತಿ PLUS_ಅಭಿವ್ಯಕ್ತಿ:
      /* Handle the pointer + int case.  */
      ಆದರೆ (code0 == ಸೂಚಕ_TYPE
	  && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  ret = ಸೂಚಕ_int_ಮೊತ್ತ (location, PLUS_ಅಭಿವ್ಯಕ್ತಿ, op0, op1);
	  ಹೋಗು return_build_ದ್ವಿಮಾನ_op;
	}
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (code1 == ಸೂಚಕ_TYPE
	       && (code0 == INTEGER_TYPE || code0 == BITINT_TYPE))
	{
	  ret = ಸೂಚಕ_int_ಮೊತ್ತ (location, PLUS_ಅಭಿವ್ಯಕ್ತಿ, op1, op0);
	  ಹೋಗು return_build_ದ್ವಿಮಾನ_op;
	}
      ಇಲ್ಲದಿದ್ದರೆ
	common = 1;
      ನಿಲ್ಲಿಸು;

    ಸ್ಥಿತಿ MINUS_ಅಭಿವ್ಯಕ್ತಿ:
      /* Subtraction of two similar pointers.
	 We must subtract them as integers, then divide by object size.  */
      ಆದರೆ (code0 == ಸೂಚಕ_TYPE && code1 == ಸೂಚಕ_TYPE
	  && comp_ಗುರಿ_types (location, type0, type1))
	{
	  ret = ಸೂಚಕ_diff (location, op0, op1, &instrument_ಅಭಿವ್ಯಕ್ತಿ);
	  ಹೋಗು return_build_ದ್ವಿಮಾನ_op;
	}
      /* Handle pointer minus int.  Just like pointer plus int.  */
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (code0 == ಸೂಚಕ_TYPE
	       && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  ret = ಸೂಚಕ_int_ಮೊತ್ತ (location, MINUS_ಅಭಿವ್ಯಕ್ತಿ, op0, op1);
	  ಹೋಗು return_build_ದ್ವಿಮಾನ_op;
	}
      ಇಲ್ಲದಿದ್ದರೆ
	common = 1;
      ನಿಲ್ಲಿಸು;

    ಸ್ಥಿತಿ MULT_ಅಭಿವ್ಯಕ್ತಿ:
      common = 1;
      ನಿಲ್ಲಿಸು;

    ಸ್ಥಿತಿ TRUNC_DIV_ಅಭಿವ್ಯಕ್ತಿ:
    ಸ್ಥಿತಿ CEIL_DIV_ಅಭಿವ್ಯಕ್ತಿ:
    ಸ್ಥಿತಿ FLOOR_DIV_ಅಭಿವ್ಯಕ್ತಿ:
    ಸ್ಥಿತಿ ಸುತ್ತು_DIV_ಅಭಿವ್ಯಕ್ತಿ:
    ಸ್ಥಿತಿ EXACT_DIV_ಅಭಿವ್ಯಕ್ತಿ:
      doing_div_or_mod = ನಿಜ;
      warn_for_div_by_zero (location, op1);

      ಆದರೆ ((code0 == INTEGER_TYPE || code0 == REAL_TYPE
	   || code0 == FIXED_ಬಿಂದು_TYPE || code0 == BITINT_TYPE
	   || code0 == COMPLEX_TYPE
	   || gnu_ಸದಿಶ_type_p (type0))
	  && (code1 == INTEGER_TYPE || code1 == REAL_TYPE
	      || code1 == FIXED_ಬಿಂದು_TYPE || code1 == BITINT_TYPE
	      || code1 == COMPLEX_TYPE
	      || gnu_ಸದಿಶ_type_p (type1)))
	{
	  ಎಣಿಕೆ ವೃಕ್ಷ_ಸಂಕೇತ_2 tcode0 = code0, tcode1 = code1;

	  ಆದರೆ (code0 == COMPLEX_TYPE || code0 == ಸದಿಶ_TYPE)
	    tcode0 = ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_TYPE (op0)));
	  ಆದರೆ (code1 == COMPLEX_TYPE || code1 == ಸದಿಶ_TYPE)
	    tcode1 = ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_TYPE (op1)));

	  ಆದರೆ (!(((tcode0 == INTEGER_TYPE || tcode0 == BITINT_TYPE
		  || (tcode0 == ENUMERAL_TYPE && code0 == ಸದಿಶ_TYPE))
		 && (tcode1 == INTEGER_TYPE || tcode1 == BITINT_TYPE
		     || (tcode1 == ENUMERAL_TYPE && code1 == ಸದಿಶ_TYPE)))
		|| (tcode0 == FIXED_ಬಿಂದು_TYPE && tcode1 == FIXED_ಬಿಂದು_TYPE)))
	    resultcode = RDIV_ಅಭಿವ್ಯಕ್ತಿ;
	  ಇಲ್ಲದಿದ್ದರೆ
	    /* Although it would be tempting to shorten always here, that
	       loses on some targets, since the modulo instruction is
	       undefined if the quotient can't be represented in the
	       computation mode.  We shorten only if unsigned or if
	       dividing by something we know != -1.  */
	    shorten = may_shorten_divmod (op0, op1);
	  common = 1;
	}
      ನಿಲ್ಲಿಸು;

    ಸ್ಥಿತಿ ಬಿಟ್_AND_ಅಭಿವ್ಯಕ್ತಿ:
    ಸ್ಥಿತಿ ಬಿಟ್_IOR_ಅಭಿವ್ಯಕ್ತಿ:
    ಸ್ಥಿತಿ ಬಿಟ್_XOR_ಅಭಿವ್ಯಕ್ತಿ:
      ಆದರೆ ((code0 == INTEGER_TYPE || code0 == BITINT_TYPE)
	  && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	shorten = -1;
      /* Allow vector types which are not floating point types.   */
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (gnu_ಸದಿಶ_type_p (type0)
	       && gnu_ಸದಿಶ_type_p (type1)
	       && !ಸದಿಶ_FLOAT_TYPE_P (type0)
	       && !ಸದಿಶ_FLOAT_TYPE_P (type1))
	common = 1;
      ನಿಲ್ಲಿಸು;

    ಸ್ಥಿತಿ TRUNC_MOD_ಅಭಿವ್ಯಕ್ತಿ:
    ಸ್ಥಿತಿ FLOOR_MOD_ಅಭಿವ್ಯಕ್ತಿ:
      doing_div_or_mod = ನಿಜ;
      warn_for_div_by_zero (location, op1);

      ಆದರೆ (gnu_ಸದಿಶ_type_p (type0)
	  && gnu_ಸದಿಶ_type_p (type1)
	  && ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (type0)) == INTEGER_TYPE
	  && ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (type1)) == INTEGER_TYPE)
	common = 1;
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ ((code0 == INTEGER_TYPE || code0 == BITINT_TYPE)
	       && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  /* Although it would be tempting to shorten always here, that loses
	     on some targets, since the modulo instruction is undefined if the
	     quotient can't be represented in the computation mode.  We shorten
	     only if unsigned or if dividing by something we know != -1.  */
	  shorten = may_shorten_divmod (op0, op1);
	  common = 1;
	}
      ನಿಲ್ಲಿಸು;

    ಸ್ಥಿತಿ TRUTH_ANDIF_ಅಭಿವ್ಯಕ್ತಿ:
    ಸ್ಥಿತಿ TRUTH_ORIF_ಅಭಿವ್ಯಕ್ತಿ:
    ಸ್ಥಿತಿ TRUTH_AND_ಅಭಿವ್ಯಕ್ತಿ:
    ಸ್ಥಿತಿ TRUTH_OR_ಅಭಿವ್ಯಕ್ತಿ:
    ಸ್ಥಿತಿ TRUTH_XOR_ಅಭಿವ್ಯಕ್ತಿ:
      ಆದರೆ ((code0 == INTEGER_TYPE || code0 == ಸೂಚಕ_TYPE
	   || code0 == REAL_TYPE || code0 == COMPLEX_TYPE
	   || code0 == FIXED_ಬಿಂದು_TYPE || code0 == NULLPTR_TYPE
	   || code0 == BITINT_TYPE)
	  && (code1 == INTEGER_TYPE || code1 == ಸೂಚಕ_TYPE
	      || code1 == REAL_TYPE || code1 == COMPLEX_TYPE
	      || code1 == FIXED_ಬಿಂದು_TYPE || code1 == NULLPTR_TYPE
	      || code1 == BITINT_TYPE))
	{
	  /* Result of these operations is always an int,
	     but that does not mean the operands should be
	     converted to ints!  */
	  ಫಲಿತಾಂಶ_type = integer_type_ಗಂಟು;
	  ಆದರೆ (op0_int_operands)
	    {
	      op0 = c_objc_common_truthvalue_conversion (location, orig_op0);
	      op0 = remove_c_maybe_const_ಅಭಿವ್ಯಕ್ತಿ (op0);
	    }
	  ಇಲ್ಲದಿದ್ದರೆ
	    op0 = c_objc_common_truthvalue_conversion (location, op0);
	  ಆದರೆ (op1_int_operands)
	    {
	      op1 = c_objc_common_truthvalue_conversion (location, orig_op1);
	      op1 = remove_c_maybe_const_ಅಭಿವ್ಯಕ್ತಿ (op1);
	    }
	  ಇಲ್ಲದಿದ್ದರೆ
	    op1 = c_objc_common_truthvalue_conversion (location, op1);
	  converted = 1;
	  boolean_op = ನಿಜ;
	}
      ಆದರೆ (ಸಂಕೇತ_2 == TRUTH_ANDIF_ಅಭಿವ್ಯಕ್ತಿ)
	{
	  int_const_or_ಅತಿಪ್ರವಾಹ = (int_operands
				   && ವೃಕ್ಷ_ಸಂಕೇತ (orig_op0) == INTEGER_CST
				   && (op0 == truthvalue_false_ಗಂಟು
				       || ವೃಕ್ಷ_ಸಂಕೇತ (orig_op1) == INTEGER_CST));
	  int_const = (int_const_or_ಅತಿಪ್ರವಾಹ
		       && !ವೃಕ್ಷ_ಅತಿಪ್ರವಾಹ (orig_op0)
		       && (op0 == truthvalue_false_ಗಂಟು
			   || !ವೃಕ್ಷ_ಅತಿಪ್ರವಾಹ (orig_op1)));
	}
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ಸಂಕೇತ_2 == TRUTH_ORIF_ಅಭಿವ್ಯಕ್ತಿ)
	{
	  int_const_or_ಅತಿಪ್ರವಾಹ = (int_operands
				   && ವೃಕ್ಷ_ಸಂಕೇತ (orig_op0) == INTEGER_CST
				   && (op0 == truthvalue_true_ಗಂಟು
				       || ವೃಕ್ಷ_ಸಂಕೇತ (orig_op1) == INTEGER_CST));
	  int_const = (int_const_or_ಅತಿಪ್ರವಾಹ
		       && !ವೃಕ್ಷ_ಅತಿಪ್ರವಾಹ (orig_op0)
		       && (op0 == truthvalue_true_ಗಂಟು
			   || !ವೃಕ್ಷ_ಅತಿಪ್ರವಾಹ (orig_op1)));
	}
      ನಿಲ್ಲಿಸು;

      /* Shift operations: result has same type as first operand;
	 always convert second operand to int.
	 Also set SHORT_SHIFT if shifting rightward.  */

    ಸ್ಥಿತಿ RSHIFT_ಅಭಿವ್ಯಕ್ತಿ:
      ಆದರೆ (gnu_ಸದಿಶ_type_p (type0)
	  && gnu_ಸದಿಶ_type_p (type1)
	  && ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (type0)) == INTEGER_TYPE
	  && ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (type1)) == INTEGER_TYPE
	  && ತಿಳಿದ_eq (TYPE_ಸದಿಶ_SUBPARTS (type0),
		       TYPE_ಸದಿಶ_SUBPARTS (type1)))
	{
	  ಫಲಿತಾಂಶ_type = type0;
	  converted = 1;
	}
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ ((code0 == INTEGER_TYPE || code0 == FIXED_ಬಿಂದು_TYPE
		|| code0 == BITINT_TYPE
		|| (gnu_ಸದಿಶ_type_p (type0)
		    && ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (type0)) == INTEGER_TYPE))
	       && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  doing_ಸರಿಸು = ನಿಜ;
	  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (op1) == INTEGER_CST)
	    {
	      ಆದರೆ (ವೃಕ್ಷ_int_cst_sgn (op1) < 0)
		{
		  int_const = ಸುಳ್ಳು;
		  ಆದರೆ (c_inhibit_evaluation_warnings == 0)
		    warning_at (location, OPT_Wshift_ಎಣಿಕೆ_negative,
				"right shift count is negative");
		}
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (code0 == ಸದಿಶ_TYPE)
		{
		  ಆದರೆ (compare_ವೃಕ್ಷ_int (op1,
					TYPE_PRECISION (ವೃಕ್ಷ_TYPE (type0)))
		      >= 0)
		    {
		      int_const = ಸುಳ್ಳು;
		      ಆದರೆ (c_inhibit_evaluation_warnings == 0)
			warning_at (location, OPT_Wshift_ಎಣಿಕೆ_ಅತಿಪ್ರವಾಹ,
				    "right shift count >= width of vector element");
		    }
		}
	      ಇಲ್ಲದಿದ್ದರೆ
		{
		  ಆದರೆ (!integer_zerop (op1))
		    short_ಸರಿಸು = 1;

		  ಆದರೆ (compare_ವೃಕ್ಷ_int (op1, TYPE_PRECISION (type0)) >= 0)
		    {
		      int_const = ಸುಳ್ಳು;
		      ಆದರೆ (c_inhibit_evaluation_warnings == 0)
			warning_at (location, OPT_Wshift_ಎಣಿಕೆ_ಅತಿಪ್ರವಾಹ,
				    "right shift count >= width of type");
		    }
		}
	    }

	  /* Use the type of the value to be shifted.  */
	  ಫಲಿತಾಂಶ_type = type0;
	  /* Avoid converting op1 to result_type later.  */
	  converted = 1;
	}
      ನಿಲ್ಲಿಸು;

    ಸ್ಥಿತಿ LSHIFT_ಅಭಿವ್ಯಕ್ತಿ:
      ಆದರೆ (gnu_ಸದಿಶ_type_p (type0)
	  && gnu_ಸದಿಶ_type_p (type1)
	  && ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (type0)) == INTEGER_TYPE
	  && ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (type1)) == INTEGER_TYPE
	  && ತಿಳಿದ_eq (TYPE_ಸದಿಶ_SUBPARTS (type0),
		       TYPE_ಸದಿಶ_SUBPARTS (type1)))
	{
	  ಫಲಿತಾಂಶ_type = type0;
	  converted = 1;
	}
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ ((code0 == INTEGER_TYPE || code0 == FIXED_ಬಿಂದು_TYPE
		|| code0 == BITINT_TYPE
		|| (gnu_ಸದಿಶ_type_p (type0)
		    && ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (type0)) == INTEGER_TYPE))
	       && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  doing_ಸರಿಸು = ನಿಜ;
	  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (op0) == INTEGER_CST
	      && ವೃಕ್ಷ_int_cst_sgn (op0) < 0
	      && !TYPE_ಅತಿಪ್ರವಾಹ_WRAPS (type0))
	    {
	      /* Don't reject a left shift of a negative value in a context
		 where a constant expression is needed in C90.  */
	      ಆದರೆ (flag_isoc99)
		int_const = ಸುಳ್ಳು;
	      ಆದರೆ (c_inhibit_evaluation_warnings == 0)
		warning_at (location, OPT_Wshift_negative_ಮೌಲ್ಯ,
			    "left shift of negative value");
	    }
	  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (op1) == INTEGER_CST)
	    {
	      ಆದರೆ (ವೃಕ್ಷ_int_cst_sgn (op1) < 0)
		{
		  int_const = ಸುಳ್ಳು;
		  ಆದರೆ (c_inhibit_evaluation_warnings == 0)
		    warning_at (location, OPT_Wshift_ಎಣಿಕೆ_negative,
				"left shift count is negative");
		}
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (code0 == ಸದಿಶ_TYPE)
		{
		  ಆದರೆ (compare_ವೃಕ್ಷ_int (op1,
					TYPE_PRECISION (ವೃಕ್ಷ_TYPE (type0)))
		      >= 0)
		    {
		      int_const = ಸುಳ್ಳು;
		      ಆದರೆ (c_inhibit_evaluation_warnings == 0)
			warning_at (location, OPT_Wshift_ಎಣಿಕೆ_ಅತಿಪ್ರವಾಹ,
				    "left shift count >= width of vector element");
		    }
		}
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (compare_ವೃಕ್ಷ_int (op1, TYPE_PRECISION (type0)) >= 0)
		{
		  int_const = ಸುಳ್ಳು;
		  ಆದರೆ (c_inhibit_evaluation_warnings == 0)
		    warning_at (location, OPT_Wshift_ಎಣಿಕೆ_ಅತಿಪ್ರವಾಹ,
				"left shift count >= width of type");
		}
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (op0) == INTEGER_CST
		       && maybe_warn_ಸರಿಸು_ಅತಿಪ್ರವಾಹ (location, op0, op1)
		       && flag_isoc99)
		int_const = ಸುಳ್ಳು;
	    }

	  /* Use the type of the value to be shifted.  */
	  ಫಲಿತಾಂಶ_type = type0;
	  /* Avoid converting op1 to result_type later.  */
	  converted = 1;
	}
      ನಿಲ್ಲಿಸು;

    ಸ್ಥಿತಿ EQ_ಅಭಿವ್ಯಕ್ತಿ:
    ಸ್ಥಿತಿ NE_ಅಭಿವ್ಯಕ್ತಿ:
      ಆದರೆ (gnu_ಸದಿಶ_type_p (type0) && gnu_ಸದಿಶ_type_p (type1))
        {
          ವೃಕ್ಷ intt;
	  ಆದರೆ (!ಸದಿಶ_types_compatible_elements_p (type0, type1))
            {
              error_at (location, "comparing vectors with different "
                                  "element types");
              ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
            }

	  ಆದರೆ (maybe_ne (TYPE_ಸದಿಶ_SUBPARTS (type0),
			TYPE_ಸದಿಶ_SUBPARTS (type1)))
            {
              error_at (location, "comparing vectors with different "
                                  "number of elements");
              ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
            }

	  /* It's not precisely specified how the usual arithmetic
	     conversions apply to the vector types.  Here, we use
	     the unsigned type if one of the operands is signed and
	     the other one is unsigned.  */
	  ಆದರೆ (TYPE_UNSIGNED (type0) != TYPE_UNSIGNED (type1))
	    {
	      ಆದರೆ (!TYPE_UNSIGNED (type0))
		op0 = build1 (VIEW_CONVERT_ಅಭಿವ್ಯಕ್ತಿ, type1, op0);
	      ಇಲ್ಲದಿದ್ದರೆ
		op1 = build1 (VIEW_CONVERT_ಅಭಿವ್ಯಕ್ತಿ, type0, op1);
	      warning_at (location, OPT_Wsign_compare, "comparison between "
			  "types %qT and %qT", type0, type1);
	    }

          /* Always construct signed integer vector type.  */
	  ಆದರೆ (ಸದಿಶ_BOOLEAN_TYPE_P (type0) && ಸದಿಶ_BOOLEAN_TYPE_P (type1))
	    ಫಲಿತಾಂಶ_type = type0;
	  ಇಲ್ಲದಿದ್ದರೆ
	    {
	      ಸ್ವಯಂಚಾಲಿತ nelts = TYPE_ಸದಿಶ_SUBPARTS (type0);

	      intt = c_common_type_for_ಗಾತ್ರ (GET_ಬಹುಲಕ_BITSIZE
					     (SCALAR_TYPE_ಬಹುಲಕ
						(ವೃಕ್ಷ_TYPE (type0))), 0);
	      ಆದರೆ (!intt)
		{
		  error_at (location, "could not find an integer type "
				      "of the same size as %qT",
			    ವೃಕ್ಷ_TYPE (type0));
		  ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
		}
	      ಫಲಿತಾಂಶ_type = build_opaque_ಸದಿಶ_type (intt, nelts);
	    }
          converted = 1;
	  ret = build_vec_cmp (resultcode, ಫಲಿತಾಂಶ_type, op0, op1);
	  ಹೋಗು return_build_ದ್ವಿಮಾನ_op;
        }
      ಆದರೆ (FLOAT_TYPE_P (type0) || FLOAT_TYPE_P (type1))
	warning_at (location,
		    OPT_Wfloat_equal,
		    "comparing floating-point with %<==%> or %<!=%> is unsafe");
      /* Result of comparison is always int,
	 but don't convert the args to int!  */
      build_type = integer_type_ಗಂಟು;
      ಆದರೆ ((code0 == INTEGER_TYPE || code0 == REAL_TYPE || code0 == BITINT_TYPE
	   || code0 == FIXED_ಬಿಂದು_TYPE || code0 == COMPLEX_TYPE)
	  && (code1 == INTEGER_TYPE || code1 == REAL_TYPE
	      || code1 == BITINT_TYPE
	      || code1 == FIXED_ಬಿಂದು_TYPE || code1 == COMPLEX_TYPE))
	short_compare = 1;
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (code0 == ಸೂಚಕ_TYPE
	       && (code1 == NULLPTR_TYPE
		   || null_ಸೂಚಕ_constant_p (orig_op1)))
	{
	  maybe_warn_for_null_ವಿಳಾಸ (location, op0, ಸಂಕೇತ_2);
	  ಫಲಿತಾಂಶ_type = type0;
	}
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (code1 == ಸೂಚಕ_TYPE
	       && (code0 == NULLPTR_TYPE
		   || null_ಸೂಚಕ_constant_p (orig_op0)))
	{
	  maybe_warn_for_null_ವಿಳಾಸ (location, op1, ಸಂಕೇತ_2);
	  ಫಲಿತಾಂಶ_type = type1;
	}
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (code0 == ಸೂಚಕ_TYPE && code1 == ಸೂಚಕ_TYPE)
	{
	  ವೃಕ್ಷ tt0 = ವೃಕ್ಷ_TYPE (type0);
	  ವೃಕ್ಷ tt1 = ವೃಕ್ಷ_TYPE (type1);
	  addr_space_t as0 = TYPE_ADDR_SPACE (tt0);
	  addr_space_t as1 = TYPE_ADDR_SPACE (tt1);
	  addr_space_t as_common = ADDR_SPACE_GENERIC;

	  /* Anything compares with void *.  void * compares with anything.
	     Otherwise, the targets must be compatible
	     and both must be object or both incomplete.  */
	  ಆದರೆ (comp_ಗುರಿ_types (location, type0, type1))
	    ಫಲಿತಾಂಶ_type = common_ಸೂಚಕ_type (type0, type1, NULL_ವೃಕ್ಷ);
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!addr_space_superset (as0, as1, &as_common))
	    {
	      error_at (location, "comparison of pointers to "
			"disjoint address spaces");
	      ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
	    }
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (VOID_TYPE_P (tt0) && !TYPE_ATOMIC (tt0))
	    {
	      ಆದರೆ (pedantic && ವೃಕ್ಷ_ಸಂಕೇತ (tt1) == FUNCTION_TYPE)
		pedwarn (location, OPT_Wpedantic, "ISO C forbids "
			 "comparison of %<void *%> with function pointer");
	    }
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (VOID_TYPE_P (tt1) && !TYPE_ATOMIC (tt1))
	    {
	      ಆದರೆ (pedantic && ವೃಕ್ಷ_ಸಂಕೇತ (tt0) == FUNCTION_TYPE)
		pedwarn (location, OPT_Wpedantic, "ISO C forbids "
			 "comparison of %<void *%> with function pointer");
	    }
	  ಇಲ್ಲದಿದ್ದರೆ
	    /* Avoid warning about the volatile ObjC EH puts on decls.  */
	    ಆದರೆ (!objc_ok)
	      pedwarn (location, OPT_Wcompare_distinct_ಸೂಚಕ_types,
		       "comparison of distinct pointer types lacks a cast");

	  ಆದರೆ (ಫಲಿತಾಂಶ_type == NULL_ವೃಕ್ಷ)
	    {
	      ಪೂರ್ಣಾಂಕ qual = ENCODE_QUAL_ADDR_SPACE (as_common);
	      ಫಲಿತಾಂಶ_type = c_build_ಸೂಚಕ_type
			      (c_build_qualified_type (void_type_ಗಂಟು, qual));
	    }
	}
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (code0 == ಸೂಚಕ_TYPE
	       && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  ಫಲಿತಾಂಶ_type = type0;
	  pedwarn (location, 0, "comparison between pointer and integer");
	}
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ ((code0 == INTEGER_TYPE || code0 == BITINT_TYPE)
	       && code1 == ಸೂಚಕ_TYPE)
	{
	  ಫಲಿತಾಂಶ_type = type1;
	  pedwarn (location, 0, "comparison between pointer and integer");
	}
      /* 6.5.9: One of the following shall hold:
	 -- both operands have type nullptr_t;  */
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (code0 == NULLPTR_TYPE && code1 == NULLPTR_TYPE)
	{
	  ಫಲಿತಾಂಶ_type = nullptr_type_ಗಂಟು;
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
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (code0 == NULLPTR_TYPE && null_ಸೂಚಕ_constant_p (orig_op1))
	ಫಲಿತಾಂಶ_type = (INTEGRAL_TYPE_P (type1)
		       ? c_build_ಸೂಚಕ_type (type1) : type1);
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (code1 == NULLPTR_TYPE && null_ಸೂಚಕ_constant_p (orig_op0))
	ಫಲಿತಾಂಶ_type = (INTEGRAL_TYPE_P (type0)
		       ? c_build_ಸೂಚಕ_type (type0) : type0);
      ಆದರೆ ((C_BOOLEAN_TYPE_P (ವೃಕ್ಷ_TYPE (orig_op0))
	   || truth_ಮೌಲ್ಯ_p (ವೃಕ್ಷ_ಸಂಕೇತ (orig_op0)))
	  ^ (C_BOOLEAN_TYPE_P (ವೃಕ್ಷ_TYPE (orig_op1))
	     || truth_ಮೌಲ್ಯ_p (ವೃಕ್ಷ_ಸಂಕೇತ (orig_op1))))
	maybe_warn_bool_compare (location, ಸಂಕೇತ_2, orig_op0, orig_op1);
      ನಿಲ್ಲಿಸು;

    ಸ್ಥಿತಿ LE_ಅಭಿವ್ಯಕ್ತಿ:
    ಸ್ಥಿತಿ GE_ಅಭಿವ್ಯಕ್ತಿ:
    ಸ್ಥಿತಿ LT_ಅಭಿವ್ಯಕ್ತಿ:
    ಸ್ಥಿತಿ GT_ಅಭಿವ್ಯಕ್ತಿ:
      ಆದರೆ (gnu_ಸದಿಶ_type_p (type0) && gnu_ಸದಿಶ_type_p (type1))
        {
          ವೃಕ್ಷ intt;
	  ಆದರೆ (!ಸದಿಶ_types_compatible_elements_p (type0, type1))
            {
              error_at (location, "comparing vectors with different "
                                  "element types");
              ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
            }

	  ಆದರೆ (maybe_ne (TYPE_ಸದಿಶ_SUBPARTS (type0),
			TYPE_ಸದಿಶ_SUBPARTS (type1)))
            {
              error_at (location, "comparing vectors with different "
                                  "number of elements");
              ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
            }

	  /* It's not precisely specified how the usual arithmetic
	     conversions apply to the vector types.  Here, we use
	     the unsigned type if one of the operands is signed and
	     the other one is unsigned.  */
	  ಆದರೆ (TYPE_UNSIGNED (type0) != TYPE_UNSIGNED (type1))
	    {
	      ಆದರೆ (!TYPE_UNSIGNED (type0))
		op0 = build1 (VIEW_CONVERT_ಅಭಿವ್ಯಕ್ತಿ, type1, op0);
	      ಇಲ್ಲದಿದ್ದರೆ
		op1 = build1 (VIEW_CONVERT_ಅಭಿವ್ಯಕ್ತಿ, type0, op1);
	      warning_at (location, OPT_Wsign_compare, "comparison between "
			  "types %qT and %qT", type0, type1);
	    }

          /* Always construct signed integer vector type.  */
          intt = c_common_type_for_ಗಾತ್ರ (GET_ಬಹುಲಕ_BITSIZE
					 (SCALAR_TYPE_ಬಹುಲಕ
					  (ವೃಕ್ಷ_TYPE (type0))), 0);
	  ಆದರೆ (!intt)
	    {
	      error_at (location, "could not find an integer type "
				  "of the same size as %qT",
			ವೃಕ್ಷ_TYPE (type0));
	      ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
	    }
          ಫಲಿತಾಂಶ_type = build_opaque_ಸದಿಶ_type (intt,
						  TYPE_ಸದಿಶ_SUBPARTS (type0));
          converted = 1;
	  ret = build_vec_cmp (resultcode, ಫಲಿತಾಂಶ_type, op0, op1);
	  ಹೋಗು return_build_ದ್ವಿಮಾನ_op;
        }
      build_type = integer_type_ಗಂಟು;
      ಆದರೆ ((code0 == INTEGER_TYPE || code0 == REAL_TYPE
	   || code0 == BITINT_TYPE || code0 == FIXED_ಬಿಂದು_TYPE)
	  && (code1 == INTEGER_TYPE || code1 == REAL_TYPE
	      || code1 == BITINT_TYPE || code1 == FIXED_ಬಿಂದು_TYPE))
	short_compare = 1;
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (code0 == ಸೂಚಕ_TYPE && code1 == ಸೂಚಕ_TYPE)
	{
	  addr_space_t as0 = TYPE_ADDR_SPACE (ವೃಕ್ಷ_TYPE (type0));
	  addr_space_t as1 = TYPE_ADDR_SPACE (ವೃಕ್ಷ_TYPE (type1));
	  addr_space_t as_common;

	  ಆದರೆ (comp_ಗುರಿ_types (location, type0, type1))
	    {
	      ಫಲಿತಾಂಶ_type = common_ಸೂಚಕ_type (type0, type1, NULL_ವೃಕ್ಷ);
	      ಆದರೆ (!COMPLETE_TYPE_P (ವೃಕ್ಷ_TYPE (type0))
		  != !COMPLETE_TYPE_P (ವೃಕ್ಷ_TYPE (type1)))
		pedwarn_c99 (location, OPT_Wpedantic,
			     "comparison of complete and incomplete pointers");
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (type0)) == FUNCTION_TYPE)
		pedwarn (location, OPT_Wpedantic, "ISO C forbids "
			 "ordered comparisons of pointers to functions");
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (null_ಸೂಚಕ_constant_p (orig_op0)
		       || null_ಸೂಚಕ_constant_p (orig_op1))
		warning_at (location, OPT_Wextra,
			    "ordered comparison of pointer with null pointer");

	    }
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!addr_space_superset (as0, as1, &as_common))
	    {
	      error_at (location, "comparison of pointers to "
			"disjoint address spaces");
	      ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
	    }
	  ಇಲ್ಲದಿದ್ದರೆ
	    {
	      ಪೂರ್ಣಾಂಕ qual = ENCODE_QUAL_ADDR_SPACE (as_common);
	      ಫಲಿತಾಂಶ_type = c_build_ಸೂಚಕ_type
			      (c_build_qualified_type (void_type_ಗಂಟು, qual));
              pedwarn (location, OPT_Wcompare_distinct_ಸೂಚಕ_types,
                       "comparison of distinct pointer types lacks a cast");
	    }
	}
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (code0 == ಸೂಚಕ_TYPE && null_ಸೂಚಕ_constant_p (orig_op1))
	{
	  ಫಲಿತಾಂಶ_type = type0;
	  ಆದರೆ (pedantic)
	    pedwarn (location, OPT_Wpedantic,
		     "ordered comparison of pointer with integer zero");
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (extra_warnings)
	    warning_at (location, OPT_Wextra,
			"ordered comparison of pointer with integer zero");
	}
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (code1 == ಸೂಚಕ_TYPE && null_ಸೂಚಕ_constant_p (orig_op0))
	{
	  ಫಲಿತಾಂಶ_type = type1;
	  ಆದರೆ (pedantic)
	    pedwarn (location, OPT_Wpedantic,
		     "ordered comparison of pointer with integer zero");
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (extra_warnings)
	    warning_at (location, OPT_Wextra,
			"ordered comparison of pointer with integer zero");
	}
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (code0 == ಸೂಚಕ_TYPE
	       && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  ಫಲಿತಾಂಶ_type = type0;
	  pedwarn (location, 0, "comparison between pointer and integer");
	}
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ ((code0 == INTEGER_TYPE || code0 == BITINT_TYPE)
	       && code1 == ಸೂಚಕ_TYPE)
	{
	  ಫಲಿತಾಂಶ_type = type1;
	  pedwarn (location, 0, "comparison between pointer and integer");
	}

      ಆದರೆ ((code0 == ಸೂಚಕ_TYPE || code1 == ಸೂಚಕ_TYPE)
	  && current_function_decl != NULL_ವೃಕ್ಷ
	  && sanitize_flags_p (SANITIZE_ಸೂಚಕ_COMPARE))
	{
	  op0 = save_ಅಭಿವ್ಯಕ್ತಿ (c_fully_fold (op0, ಸುಳ್ಳು, ಖಾಲಿ));
	  op1 = save_ಅಭಿವ್ಯಕ್ತಿ (c_fully_fold (op1, ಸುಳ್ಳು, ಖಾಲಿ));

	  ವೃಕ್ಷ tt = builtin_decl_explicit (BUILT_ಒಳ_ASAN_ಸೂಚಕ_COMPARE);
	  instrument_ಅಭಿವ್ಯಕ್ತಿ = build_call_ಅಭಿವ್ಯಕ್ತಿ_loc (location, tt, 2, op0, op1);
	}

      ಆದರೆ ((C_BOOLEAN_TYPE_P (ವೃಕ್ಷ_TYPE (orig_op0))
	   || truth_ಮೌಲ್ಯ_p (ವೃಕ್ಷ_ಸಂಕೇತ (orig_op0)))
	  ^ (C_BOOLEAN_TYPE_P (ವೃಕ್ಷ_TYPE (orig_op1))
	     || truth_ಮೌಲ್ಯ_p (ವೃಕ್ಷ_ಸಂಕೇತ (orig_op1))))
	maybe_warn_bool_compare (location, ಸಂಕೇತ_2, orig_op0, orig_op1);
      ನಿಲ್ಲಿಸು;

    ಸ್ಥಿತಿ MIN_ಅಭಿವ್ಯಕ್ತಿ:
    ಸ್ಥಿತಿ MAX_ಅಭಿವ್ಯಕ್ತಿ:
      /* Used for OpenMP atomics.  */
      gcc_assert (flag_openmp);
      common = 1;
      ನಿಲ್ಲಿಸು;

    ಪೂರ್ವನಿಯೋಜಿತ:
      gcc_unreachable ();
    }

  ಆದರೆ (code0 == ERROR_MARK || code1 == ERROR_MARK)
    ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;

  ಆದರೆ (gnu_ಸದಿಶ_type_p (type0)
      && gnu_ಸದಿಶ_type_p (type1)
      && (!ವೃಕ್ಷ_int_cst_equal (TYPE_ಗಾತ್ರ (type0), TYPE_ಗಾತ್ರ (type1))
	  || !ಸದಿಶ_types_compatible_elements_p (type0, type1)))
    {
      gcc_rich_location richloc (location);
      maybe_range_label_for_ವೃಕ್ಷ_type_mismatch
	label_for_op0 (orig_op0, orig_op1),
	label_for_op1 (orig_op1, orig_op0);
      richloc.maybe_ಕೂಡಿಸು_ಅಭಿವ್ಯಕ್ತಿ (orig_op0, &label_for_op0, highlight_colors::lhs);
      richloc.maybe_ಕೂಡಿಸು_ಅಭಿವ್ಯಕ್ತಿ (orig_op1, &label_for_op1, highlight_colors::rhs);
      ದ್ವಿಮಾನ_op_error (&richloc, ಸಂಕೇತ_2, type0, type1);
      ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
    }

  ಆದರೆ ((code0 == INTEGER_TYPE || code0 == REAL_TYPE || code0 == COMPLEX_TYPE
       || code0 == FIXED_ಬಿಂದು_TYPE || code0 == BITINT_TYPE
       || gnu_ಸದಿಶ_type_p (type0))
      && (code1 == INTEGER_TYPE || code1 == REAL_TYPE || code1 == COMPLEX_TYPE
	  || code1 == FIXED_ಬಿಂದು_TYPE || code1 == BITINT_TYPE
	  || gnu_ಸದಿಶ_type_p (type1)))
    {
      ತಾರ್ಕಿಕ ಮೊದಲ_complex = (code0 == COMPLEX_TYPE);
      ತಾರ್ಕಿಕ ಎರಡನೇ_complex = (code1 == COMPLEX_TYPE);
      ಪೂರ್ಣಾಂಕ none_complex = (!ಮೊದಲ_complex && !ಎರಡನೇ_complex);

      ಆದರೆ (shorten || common || short_compare)
	{
	  ಫಲಿತಾಂಶ_type = c_common_type (type0, type1);
	  do_warn_double_promotion (ಫಲಿತಾಂಶ_type, type0, type1,
				    "implicit conversion from %qT to %qT "
				    "to match other operand of binary "
				    "expression",
				    location);
	  ಆದರೆ (ಫಲಿತಾಂಶ_type == error_mark_ಗಂಟು)
	    ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
	}

      ಆದರೆ (ಮೊದಲ_complex != ಎರಡನೇ_complex
	  && (ಸಂಕೇತ_2 == PLUS_ಅಭಿವ್ಯಕ್ತಿ
	      || ಸಂಕೇತ_2 == MINUS_ಅಭಿವ್ಯಕ್ತಿ
	      || ಸಂಕೇತ_2 == MULT_ಅಭಿವ್ಯಕ್ತಿ
	      || (ಸಂಕೇತ_2 == TRUNC_DIV_ಅಭಿವ್ಯಕ್ತಿ && ಮೊದಲ_complex))
	  && ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (ಫಲಿತಾಂಶ_type)) == REAL_TYPE
	  && flag_signed_zeros)
	{
	  /* An operation on mixed real/complex operands must be
	     handled specially, but the language-independent code can
	     more easily optimize the plain complex arithmetic if
	     -fno-signed-zeros.  */
	  ವೃಕ್ಷ real_type = ವೃಕ್ಷ_TYPE (ಫಲಿತಾಂಶ_type);
	  ವೃಕ್ಷ real, imag;
	  ಆದರೆ (type0 != orig_type0 || type1 != orig_type1)
	    {
	      gcc_assert (may_need_excess_precision && common);
	      semantic_ಫಲಿತಾಂಶ_type = c_common_type (orig_type0, orig_type1);
	    }
	  ಆದರೆ (ಮೊದಲ_complex)
	    {
	      ಆದರೆ (ವೃಕ್ಷ_TYPE (op0) != ಫಲಿತಾಂಶ_type)
		op0 = convert_and_check (location, ಫಲಿತಾಂಶ_type, op0);
	      ಆದರೆ (ವೃಕ್ಷ_TYPE (op1) != real_type)
		op1 = convert_and_check (location, real_type, op1);
	    }
	  ಇಲ್ಲದಿದ್ದರೆ
	    {
	      ಆದರೆ (ವೃಕ್ಷ_TYPE (op0) != real_type)
		op0 = convert_and_check (location, real_type, op0);
	      ಆದರೆ (ವೃಕ್ಷ_TYPE (op1) != ಫಲಿತಾಂಶ_type)
		op1 = convert_and_check (location, ಫಲಿತಾಂಶ_type, op1);
	    }
	  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (op0) == ERROR_MARK || ವೃಕ್ಷ_ಸಂಕೇತ (op1) == ERROR_MARK)
	    ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
	  ಆದರೆ (ಮೊದಲ_complex)
	    {
	      op0 = save_ಅಭಿವ್ಯಕ್ತಿ (op0);
	      real = build_unary_op (ಅಭಿವ್ಯಕ್ತಿ_LOCATION (orig_op0), REALPART_ಅಭಿವ್ಯಕ್ತಿ,
				     op0, ನಿಜ);
	      imag = build_unary_op (ಅಭಿವ್ಯಕ್ತಿ_LOCATION (orig_op0), IMAGPART_ಅಭಿವ್ಯಕ್ತಿ,
				     op0, ನಿಜ);
	      ಆಯ್ಕೆ (ಸಂಕೇತ_2)
		{
		ಸ್ಥಿತಿ MULT_ಅಭಿವ್ಯಕ್ತಿ:
		ಸ್ಥಿತಿ TRUNC_DIV_ಅಭಿವ್ಯಕ್ತಿ:
		  op1 = save_ಅಭಿವ್ಯಕ್ತಿ (op1);
		  imag = build2 (resultcode, real_type, imag, op1);
		  /* Fall through.  */
		ಸ್ಥಿತಿ PLUS_ಅಭಿವ್ಯಕ್ತಿ:
		ಸ್ಥಿತಿ MINUS_ಅಭಿವ್ಯಕ್ತಿ:
		  real = build2 (resultcode, real_type, real, op1);
		  ನಿಲ್ಲಿಸು;
		ಪೂರ್ವನಿಯೋಜಿತ:
		  gcc_unreachable();
		}
	    }
	  ಇಲ್ಲದಿದ್ದರೆ
	    {
	      op1 = save_ಅಭಿವ್ಯಕ್ತಿ (op1);
	      real = build_unary_op (ಅಭಿವ್ಯಕ್ತಿ_LOCATION (orig_op1), REALPART_ಅಭಿವ್ಯಕ್ತಿ,
				     op1, ನಿಜ);
	      imag = build_unary_op (ಅಭಿವ್ಯಕ್ತಿ_LOCATION (orig_op1), IMAGPART_ಅಭಿವ್ಯಕ್ತಿ,
				     op1, ನಿಜ);
	      ಆಯ್ಕೆ (ಸಂಕೇತ_2)
		{
		ಸ್ಥಿತಿ MULT_ಅಭಿವ್ಯಕ್ತಿ:
		  op0 = save_ಅಭಿವ್ಯಕ್ತಿ (op0);
		  imag = build2 (resultcode, real_type, op0, imag);
		  /* Fall through.  */
		ಸ್ಥಿತಿ PLUS_ಅಭಿವ್ಯಕ್ತಿ:
		  real = build2 (resultcode, real_type, op0, real);
		  ನಿಲ್ಲಿಸು;
		ಸ್ಥಿತಿ MINUS_ಅಭಿವ್ಯಕ್ತಿ:
		  real = build2 (resultcode, real_type, op0, real);
		  imag = build1 (NEGATE_ಅಭಿವ್ಯಕ್ತಿ, real_type, imag);
		  ನಿಲ್ಲಿಸು;
		ಪೂರ್ವನಿಯೋಜಿತ:
		  gcc_unreachable();
		}
	    }
	  ret = build2 (COMPLEX_ಅಭಿವ್ಯಕ್ತಿ, ಫಲಿತಾಂಶ_type, real, imag);
	  ಹೋಗು return_build_ದ್ವಿಮಾನ_op;
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

      ಆದರೆ (shorten && none_complex)
	{
	  final_type = ಫಲಿತಾಂಶ_type;
	  ಫಲಿತಾಂಶ_type = shorten_ದ್ವಿಮಾನ_op (ಫಲಿತಾಂಶ_type, op0, op1,
					   shorten == -1);
	}

      /* Shifts can be shortened if shifting right.  */

      ಆದರೆ (short_ಸರಿಸು)
	{
	  ಪೂರ್ಣಾಂಕ unsigned_arg;
	  ವೃಕ್ಷ arg0 = get_narrower (op0, &unsigned_arg);

	  final_type = ಫಲಿತಾಂಶ_type;

	  ಆದರೆ (arg0 == op0 && final_type == ವೃಕ್ಷ_TYPE (op0))
	    unsigned_arg = TYPE_UNSIGNED (ವೃಕ್ಷ_TYPE (op0));

	  ಆದರೆ (TYPE_PRECISION (ವೃಕ್ಷ_TYPE (arg0)) < TYPE_PRECISION (ಫಲಿತಾಂಶ_type)
	      && ವೃಕ್ಷ_int_cst_sgn (op1) > 0
	      /* We can shorten only if the shift count is less than the
		 number of bits in the smaller type size.  */
	      && compare_ವೃಕ್ಷ_int (op1, TYPE_PRECISION (ವೃಕ್ಷ_TYPE (arg0))) < 0
	      /* We cannot drop an unsigned shift after sign-extension.  */
	      && (!TYPE_UNSIGNED (final_type) || unsigned_arg))
	    {
	      /* Do an unsigned shift if the operand was zero-extended.  */
	      ಫಲಿತಾಂಶ_type
		= c_common_signed_or_unsigned_type (unsigned_arg,
						    ವೃಕ್ಷ_TYPE (arg0));
	      /* Convert value-to-be-shifted to that type.  */
	      ಆದರೆ (ವೃಕ್ಷ_TYPE (op0) != ಫಲಿತಾಂಶ_type)
		op0 = convert (ಫಲಿತಾಂಶ_type, op0);
	      converted = 1;
	    }
	}

      /* Comparison operations are shortened too but differently.
	 They identify themselves by setting short_compare = 1.  */

      ಆದರೆ (short_compare)
	{
	  /* Don't write &op0, etc., because that would prevent op0
	     from being kept in a register.
	     Instead, make copies of the our local variables and
	     pass the copies by reference, then copy them back afterward.  */
	  ವೃಕ್ಷ xop0 = op0, xop1 = op1, xresult_type = ಫಲಿತಾಂಶ_type;
	  ಎಣಿಕೆ ವೃಕ್ಷ_ಸಂಕೇತ_2 xresultcode = resultcode;
	  ವೃಕ್ಷ val
	    = shorten_compare (location, &xop0, &xop1, &xresult_type,
			       &xresultcode);

	  ಆದರೆ (val != NULL_ವೃಕ್ಷ)
	    {
	      ret = val;
	      ಹೋಗು return_build_ದ್ವಿಮಾನ_op;
	    }

	  op0 = xop0, op1 = xop1;
	  converted = 1;
	  resultcode = xresultcode;

	  ಆದರೆ (c_inhibit_evaluation_warnings == 0 && !c_ಒಳ_omp_for)
	    {
	      ತಾರ್ಕಿಕ op0_maybe_const = ನಿಜ;
	      ತಾರ್ಕಿಕ op1_maybe_const = ನಿಜ;
	      ವೃಕ್ಷ orig_op0_folded, orig_op1_folded;

	      ಆದರೆ (ಒಳ_late_ದ್ವಿಮಾನ_op)
		{
		  orig_op0_folded = orig_op0;
		  orig_op1_folded = orig_op1;
		}
	      ಇಲ್ಲದಿದ್ದರೆ
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
						  ಖಾಲಿ);
		  orig_op1_folded = c_fully_fold (orig_op1,
						  require_constant_ಮೌಲ್ಯ,
						  ಖಾಲಿ);
		}

	      ಆದರೆ (warn_sign_compare)
		warn_for_sign_compare (location, orig_op0_folded,
				       orig_op1_folded, op0, op1,
				       ಫಲಿತಾಂಶ_type, resultcode);
	      ಆದರೆ (!ಒಳ_late_ದ್ವಿಮಾನ_op && !int_operands)
		{
		  ಆದರೆ (!op0_maybe_const || ವೃಕ್ಷ_ಸಂಕೇತ (op0) != INTEGER_CST)
		    op0 = c_wrap_maybe_const (op0, !op0_maybe_const);
		  ಆದರೆ (!op1_maybe_const || ವೃಕ್ಷ_ಸಂಕೇತ (op1) != INTEGER_CST)
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

  ಆದರೆ (!ಫಲಿತಾಂಶ_type)
    {
      /* Favor showing any expression locations that are available. */
      op_location_t oploc (location, UNKNOWN_LOCATION);
      ದ್ವಿಮಾನ_op_rich_location richloc (oploc, orig_op0, orig_op1, ನಿಜ);
      ದ್ವಿಮಾನ_op_error (&richloc, ಸಂಕೇತ_2, ವೃಕ್ಷ_TYPE (op0), ವೃಕ್ಷ_TYPE (op1));
      ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
    }

  ಆದರೆ (build_type == NULL_ವೃಕ್ಷ)
    {
      build_type = ಫಲಿತಾಂಶ_type;
      ಆದರೆ ((type0 != orig_type0 || type1 != orig_type1)
	  && !boolean_op)
	{
	  gcc_assert (may_need_excess_precision && common);
	  semantic_ಫಲಿತಾಂಶ_type = c_common_type (orig_type0, orig_type1);
	}
    }

  ಆದರೆ (!converted)
    {
      op0 = ep_convert_and_check (location, ಫಲಿತಾಂಶ_type, op0,
				  semantic_ಫಲಿತಾಂಶ_type);
      op1 = ep_convert_and_check (location, ಫಲಿತಾಂಶ_type, op1,
				  semantic_ಫಲಿತಾಂಶ_type);

      /* This can happen if one operand has a vector type, and the other
	 has a different type.  */
      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (op0) == ERROR_MARK || ವೃಕ್ಷ_ಸಂಕೇತ (op1) == ERROR_MARK)
	ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
    }

  ಆದರೆ (sanitize_flags_p ((SANITIZE_ಸರಿಸು
			 | SANITIZE_DIVIDE
			 | SANITIZE_FLOAT_DIVIDE
			 | SANITIZE_SI_ಅತಿಪ್ರವಾಹ))
      && current_function_decl != NULL_ವೃಕ್ಷ
      && (doing_div_or_mod || doing_ಸರಿಸು)
      && !require_constant_ಮೌಲ್ಯ)
    {
      /* OP0 and/or OP1 might have side-effects.  */
      op0 = save_ಅಭಿವ್ಯಕ್ತಿ (op0);
      op1 = save_ಅಭಿವ್ಯಕ್ತಿ (op1);
      op0 = c_fully_fold (op0, ಸುಳ್ಳು, ಖಾಲಿ);
      op1 = c_fully_fold (op1, ಸುಳ್ಳು, ಖಾಲಿ);
      ಆದರೆ (doing_div_or_mod && (sanitize_flags_p ((SANITIZE_DIVIDE
						  | SANITIZE_FLOAT_DIVIDE
						  | SANITIZE_SI_ಅತಿಪ್ರವಾಹ))))
	instrument_ಅಭಿವ್ಯಕ್ತಿ = ubsan_instrument_division (location, op0, op1);
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (doing_ಸರಿಸು && sanitize_flags_p (SANITIZE_ಸರಿಸು))
	instrument_ಅಭಿವ್ಯಕ್ತಿ = ubsan_instrument_ಸರಿಸು (location, ಸಂಕೇತ_2, op0, op1);
    }

  /* Treat expressions in initializers specially as they can't trap.  */
  ಆದರೆ (int_const_or_ಅತಿಪ್ರವಾಹ)
    ret = (require_constant_ಮೌಲ್ಯ
	   ? fold_build2_initializer_loc (location, resultcode, build_type,
					  op0, op1)
	   : fold_build2_loc (location, resultcode, build_type, op0, op1));
  ಇಲ್ಲದಿದ್ದರೆ
    ret = build2 (resultcode, build_type, op0, op1);
  ಆದರೆ (final_type != NULL_ವೃಕ್ಷ)
    ret = convert (final_type, ret);

 return_build_ದ್ವಿಮಾನ_op:
  gcc_assert (ret != error_mark_ಗಂಟು);
  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ret) == INTEGER_CST && !ವೃಕ್ಷ_ಅತಿಪ್ರವಾಹ (ret) && !int_const)
    ret = (int_operands
	   ? note_integer_operands (ret)
	   : build1 (NOP_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (ret), ret));
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ret) != INTEGER_CST && int_operands
	   && !ಒಳ_late_ದ್ವಿಮಾನ_op)
    ret = note_integer_operands (ret);
  protected_ಗಣ_ಅಭಿವ್ಯಕ್ತಿ_location (ret, location);

  ಆದರೆ (instrument_ಅಭಿವ್ಯಕ್ತಿ != ಖಾಲಿ)
    ret = fold_build2 (COMPOUND_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (ret),
		       instrument_ಅಭಿವ್ಯಕ್ತಿ, ret);

  ಆದರೆ (semantic_ಫಲಿತಾಂಶ_type)
    ret = build1_loc (location, EXCESS_PRECISION_ಅಭಿವ್ಯಕ್ತಿ,
		      semantic_ಫಲಿತಾಂಶ_type, ret);

  ಹಿಂತಿರುಗಿ ret;
}


/* Convert EXPR to be a truth-value (type TYPE), validating its type for this
   purpose.  LOCATION is the source location for the expression.  */

ವೃಕ್ಷ
c_objc_common_truthvalue_conversion (location_t location, ವೃಕ್ಷ ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ type)
{
  ತಾರ್ಕಿಕ int_const, int_operands;

  ಆಯ್ಕೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ)))
    {
    ಸ್ಥಿತಿ ARRAY_TYPE:
      error_at (location, "used array that cannot be converted to pointer where scalar is required");
      ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;

    ಸ್ಥಿತಿ ದಾಖಲೆ_TYPE:
      error_at (location, "used struct type value where scalar is required");
      ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;

    ಸ್ಥಿತಿ UNION_TYPE:
      error_at (location, "used union type value where scalar is required");
      ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;

    ಸ್ಥಿತಿ VOID_TYPE:
      error_at (location, "void value not ignored as it ought to be");
      ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;

    ಸ್ಥಿತಿ ಸೂಚಕ_TYPE:
      ಆದರೆ (reject_gcc_builtin (ಅಭಿವ್ಯಕ್ತಿ))
	ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
      ನಿಲ್ಲಿಸು;

    ಸ್ಥಿತಿ FUNCTION_TYPE:
      gcc_unreachable ();

    ಸ್ಥಿತಿ ಸದಿಶ_TYPE:
      error_at (location, "used vector type where scalar is required");
      ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;

    ಪೂರ್ವನಿಯೋಜಿತ:
      ನಿಲ್ಲಿಸು;
    }

  /* Conversion of a floating constant to boolean goes through here
     and yields an integer constant expression.  Otherwise, the result
     is only an integer constant expression if the argument is.  */
  int_const = ((ವೃಕ್ಷ_ಸಂಕೇತ (ಅಭಿವ್ಯಕ್ತಿ) == INTEGER_CST && !ವೃಕ್ಷ_ಅತಿಪ್ರವಾಹ (ಅಭಿವ್ಯಕ್ತಿ))
	       || ((ವೃಕ್ಷ_ಸಂಕೇತ (ಅಭಿವ್ಯಕ್ತಿ) == REAL_CST
		    || ವೃಕ್ಷ_ಸಂಕೇತ (ಅಭಿವ್ಯಕ್ತಿ) == COMPLEX_CST)
		   && (ವೃಕ್ಷ_ಸಂಕೇತ (type) == BOOLEAN_TYPE
		       || (ವೃಕ್ಷ_ಸಂಕೇತ (type) == ENUMERAL_TYPE
			   && ENUM_UNDERLYING_TYPE (type) != NULL_ವೃಕ್ಷ
			   && (ವೃಕ್ಷ_ಸಂಕೇತ (ENUM_UNDERLYING_TYPE (type))
			       == BOOLEAN_TYPE)))));
  int_operands = ಅಭಿವ್ಯಕ್ತಿ_INT_CONST_OPERANDS (ಅಭಿವ್ಯಕ್ತಿ);
  ಆದರೆ (int_operands && ವೃಕ್ಷ_ಸಂಕೇತ (ಅಭಿವ್ಯಕ್ತಿ) != INTEGER_CST)
    {
      ಅಭಿವ್ಯಕ್ತಿ = remove_c_maybe_const_ಅಭಿವ್ಯಕ್ತಿ (ಅಭಿವ್ಯಕ್ತಿ);
      ಅಭಿವ್ಯಕ್ತಿ = build2 (NE_ಅಭಿವ್ಯಕ್ತಿ, type, ಅಭಿವ್ಯಕ್ತಿ,
		     convert (ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ), integer_zero_ಗಂಟು));
      ಅಭಿವ್ಯಕ್ತಿ = note_integer_operands (ಅಭಿವ್ಯಕ್ತಿ);
    }
  ಇಲ್ಲದಿದ್ದರೆ
    {
      /* ??? Should we also give an error for vectors rather than leaving
	 those to give errors later?  */
      ಅಭಿವ್ಯಕ್ತಿ = c_common_truthvalue_conversion (location, ಅಭಿವ್ಯಕ್ತಿ);
      ಅಭಿವ್ಯಕ್ತಿ = fold_convert_loc (location, type, ಅಭಿವ್ಯಕ್ತಿ);
    }

  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ಅಭಿವ್ಯಕ್ತಿ) == INTEGER_CST && int_operands && !int_const)
    {
      ಆದರೆ (ವೃಕ್ಷ_ಅತಿಪ್ರವಾಹ (ಅಭಿವ್ಯಕ್ತಿ))
	ಹಿಂತಿರುಗಿ ಅಭಿವ್ಯಕ್ತಿ;
      ಇಲ್ಲದಿದ್ದರೆ
	ಹಿಂತಿರುಗಿ note_integer_operands (ಅಭಿವ್ಯಕ್ತಿ);
    }
  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ಅಭಿವ್ಯಕ್ತಿ) == INTEGER_CST && !int_const)
    ಹಿಂತಿರುಗಿ build1 (NOP_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ), ಅಭಿವ್ಯಕ್ತಿ);
  ಹಿಂತಿರುಗಿ ಅಭಿವ್ಯಕ್ತಿ;
}


/* Convert EXPR to a contained DECL, updating *TC, *TI and *SE as
   required.  */

ವೃಕ್ಷ
c_ಅಭಿವ್ಯಕ್ತಿ_ಗಮ್ಯ_decl (ವೃಕ್ಷ ಅಭಿವ್ಯಕ್ತಿ, ತಾರ್ಕಿಕ *tc ATTRIBUTE_ಬಳಸದ, ತಾರ್ಕಿಕ *se)
{
  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ಅಭಿವ್ಯಕ್ತಿ) == COMPOUND_LITERAL_ಅಭಿವ್ಯಕ್ತಿ)
    {
      ವೃಕ್ಷ decl = COMPOUND_LITERAL_ಅಭಿವ್ಯಕ್ತಿ_DECL (ಅಭಿವ್ಯಕ್ತಿ);
      /* Executing a compound literal inside a function reinitializes
	 it.  */
      ಆದರೆ (!ವೃಕ್ಷ_STATIC (decl))
	*se = ನಿಜ;
      ಹಿಂತಿರುಗಿ decl;
    }
  ಇಲ್ಲದಿದ್ದರೆ
    ಹಿಂತಿರುಗಿ ಅಭಿವ್ಯಕ್ತಿ;
}

/* Generate OMP construct CODE, with BODY and CLAUSES as its compound
   statement.  LOC is the location of the construct.  */

ವೃಕ್ಷ
c_ಮುಕ್ತಾಯ_omp_construct (location_t loc, ಎಣಿಕೆ ವೃಕ್ಷ_ಸಂಕೇತ_2 ಸಂಕೇತ_2, ವೃಕ್ಷ body,
			ವೃಕ್ಷ clauses)
{
  body = c_ಕೊನೆ_compound_stmt (loc, body, ನಿಜ);

  ವೃಕ್ಷ stmt = make_ಗಂಟು (ಸಂಕೇತ_2);
  ವೃಕ್ಷ_TYPE (stmt) = void_type_ಗಂಟು;
  OMP_BODY (stmt) = body;
  OMP_CLAUSES (stmt) = clauses;
  ಗಣ_ಅಭಿವ್ಯಕ್ತಿ_LOCATION (stmt, loc);

  ಹಿಂತಿರುಗಿ ಕೂಡಿಸು_stmt (stmt);
}

/* Generate OACC_DATA, with CLAUSES and BLOCK as its compound
   statement.  LOC is the location of the OACC_DATA.  */

ವೃಕ್ಷ
c_ಮುಕ್ತಾಯ_oacc_ದತ್ತಾಂಶ (location_t loc, ವೃಕ್ಷ clauses, ವೃಕ್ಷ ಖಂಡ)
{
  ವೃಕ್ಷ stmt;

  ಖಂಡ = c_ಕೊನೆ_compound_stmt (loc, ಖಂಡ, ನಿಜ);

  stmt = make_ಗಂಟು (OACC_ದತ್ತಾಂಶ);
  ವೃಕ್ಷ_TYPE (stmt) = void_type_ಗಂಟು;
  OACC_ದತ್ತಾಂಶ_CLAUSES (stmt) = clauses;
  OACC_ದತ್ತಾಂಶ_BODY (stmt) = ಖಂಡ;
  ಗಣ_ಅಭಿವ್ಯಕ್ತಿ_LOCATION (stmt, loc);

  ಹಿಂತಿರುಗಿ ಕೂಡಿಸು_stmt (stmt);
}

/* Generate OACC_HOST_DATA, with CLAUSES and BLOCK as its compound
   statement.  LOC is the location of the OACC_HOST_DATA.  */

ವೃಕ್ಷ
c_ಮುಕ್ತಾಯ_oacc_host_ದತ್ತಾಂಶ (location_t loc, ವೃಕ್ಷ clauses, ವೃಕ್ಷ ಖಂಡ)
{
  ವೃಕ್ಷ stmt;

  ಖಂಡ = c_ಕೊನೆ_compound_stmt (loc, ಖಂಡ, ನಿಜ);

  stmt = make_ಗಂಟು (OACC_HOST_ದತ್ತಾಂಶ);
  ವೃಕ್ಷ_TYPE (stmt) = void_type_ಗಂಟು;
  OACC_HOST_ದತ್ತಾಂಶ_CLAUSES (stmt) = clauses;
  OACC_HOST_ದತ್ತಾಂಶ_BODY (stmt) = ಖಂಡ;
  ಗಣ_ಅಭಿವ್ಯಕ್ತಿ_LOCATION (stmt, loc);

  ಹಿಂತಿರುಗಿ ಕೂಡಿಸು_stmt (stmt);
}

/* Like c_begin_compound_stmt, except force the retention of the BLOCK.  */

ವೃಕ್ಷ
c_begin_omp_parallel (ಶೂನ್ಯ)
{
  ವೃಕ್ಷ ಖಂಡ;

  keep_ಮುಂದಿನ_level ();
  ಖಂಡ = c_begin_compound_stmt (ನಿಜ);

  ಹಿಂತಿರುಗಿ ಖಂಡ;
}

/* Generate OMP_PARALLEL, with CLAUSES and BLOCK as its compound
   statement.  LOC is the location of the OMP_PARALLEL.  */

ವೃಕ್ಷ
c_ಮುಕ್ತಾಯ_omp_parallel (location_t loc, ವೃಕ್ಷ clauses, ವೃಕ್ಷ ಖಂಡ)
{
  ವೃಕ್ಷ stmt;

  ಖಂಡ = c_ಕೊನೆ_compound_stmt (loc, ಖಂಡ, ನಿಜ);

  stmt = make_ಗಂಟು (OMP_PARALLEL);
  ವೃಕ್ಷ_TYPE (stmt) = void_type_ಗಂಟು;
  OMP_PARALLEL_CLAUSES (stmt) = clauses;
  OMP_PARALLEL_BODY (stmt) = ಖಂಡ;
  ಗಣ_ಅಭಿವ್ಯಕ್ತಿ_LOCATION (stmt, loc);

  ಹಿಂತಿರುಗಿ ಕೂಡಿಸು_stmt (stmt);
}

/* Like c_begin_compound_stmt, except force the retention of the BLOCK.  */

ವೃಕ್ಷ
c_begin_omp_task (ಶೂನ್ಯ)
{
  ವೃಕ್ಷ ಖಂಡ;

  keep_ಮುಂದಿನ_level ();
  ಖಂಡ = c_begin_compound_stmt (ನಿಜ);

  ಹಿಂತಿರುಗಿ ಖಂಡ;
}

/* Generate OMP_TASK, with CLAUSES and BLOCK as its compound
   statement.  LOC is the location of the #pragma.  */

ವೃಕ್ಷ
c_ಮುಕ್ತಾಯ_omp_task (location_t loc, ವೃಕ್ಷ clauses, ವೃಕ್ಷ ಖಂಡ)
{
  ವೃಕ್ಷ stmt;

  ಖಂಡ = c_ಕೊನೆ_compound_stmt (loc, ಖಂಡ, ನಿಜ);

  stmt = make_ಗಂಟು (OMP_TASK);
  ವೃಕ್ಷ_TYPE (stmt) = void_type_ಗಂಟು;
  OMP_TASK_CLAUSES (stmt) = clauses;
  OMP_TASK_BODY (stmt) = ಖಂಡ;
  ಗಣ_ಅಭಿವ್ಯಕ್ತಿ_LOCATION (stmt, loc);

  ಹಿಂತಿರುಗಿ ಕೂಡಿಸು_stmt (stmt);
}

/* Generate GOMP_cancel call for #pragma omp cancel.  */

ಶೂನ್ಯ
c_ಮುಕ್ತಾಯ_omp_cancel (location_t loc, ವೃಕ್ಷ clauses)
{
  ವೃಕ್ಷ fn = builtin_decl_explicit (BUILT_ಒಳ_GOMP_CANCEL);
  ಪೂರ್ಣಾಂಕ ಮುಖವಾಡ = 0;
  ಆದರೆ (omp_ಕಂಡುಹಿಡಿ_clause (clauses, OMP_CLAUSE_PARALLEL))
    ಮುಖವಾಡ = 1;
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (omp_ಕಂಡುಹಿಡಿ_clause (clauses, OMP_CLAUSE_FOR))
    ಮುಖವಾಡ = 2;
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (omp_ಕಂಡುಹಿಡಿ_clause (clauses, OMP_CLAUSE_SECTIONS))
    ಮುಖವಾಡ = 4;
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (omp_ಕಂಡುಹಿಡಿ_clause (clauses, OMP_CLAUSE_TASKGROUP))
    ಮುಖವಾಡ = 8;
  ಇಲ್ಲದಿದ್ದರೆ
    {
      error_at (loc, "%<#pragma omp cancel%> must specify one of "
		     "%<parallel%>, %<for%>, %<sections%> or %<taskgroup%> "
		     "clauses");
      ಹಿಂತಿರುಗಿ;
    }
  ವೃಕ್ಷ ifc = omp_ಕಂಡುಹಿಡಿ_clause (clauses, OMP_CLAUSE_IF);
  ಆದರೆ (ifc != NULL_ವೃಕ್ಷ)
    {
      ಆದರೆ (OMP_CLAUSE_IF_MODIFIER (ifc) != ERROR_MARK
	  && OMP_CLAUSE_IF_MODIFIER (ifc) != VOID_CST)
	error_at (OMP_CLAUSE_LOCATION (ifc),
		  "expected %<cancel%> %<if%> clause modifier");
      ಇಲ್ಲದಿದ್ದರೆ
	{
	  ವೃಕ್ಷ ifc2 = omp_ಕಂಡುಹಿಡಿ_clause (OMP_CLAUSE_CHAIN (ifc), OMP_CLAUSE_IF);
	  ಆದರೆ (ifc2 != NULL_ವೃಕ್ಷ)
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
  ಇಲ್ಲದಿದ್ದರೆ
    ifc = boolean_true_ಗಂಟು;
  ವೃಕ್ಷ stmt = build_call_ಅಭಿವ್ಯಕ್ತಿ_loc (loc, fn, 2,
				   build_int_cst (integer_type_ಗಂಟು, ಮುಖವಾಡ),
				   ifc);
  ಕೂಡಿಸು_stmt (stmt);
}

/* Generate GOMP_cancellation_point call for
   #pragma omp cancellation point.  */

ಶೂನ್ಯ
c_ಮುಕ್ತಾಯ_omp_cancellation_ಬಿಂದು (location_t loc, ವೃಕ್ಷ clauses)
{
  ವೃಕ್ಷ fn = builtin_decl_explicit (BUILT_ಒಳ_GOMP_CANCELLATION_ಬಿಂದು);
  ಪೂರ್ಣಾಂಕ ಮುಖವಾಡ = 0;
  ಆದರೆ (omp_ಕಂಡುಹಿಡಿ_clause (clauses, OMP_CLAUSE_PARALLEL))
    ಮುಖವಾಡ = 1;
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (omp_ಕಂಡುಹಿಡಿ_clause (clauses, OMP_CLAUSE_FOR))
    ಮುಖವಾಡ = 2;
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (omp_ಕಂಡುಹಿಡಿ_clause (clauses, OMP_CLAUSE_SECTIONS))
    ಮುಖವಾಡ = 4;
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (omp_ಕಂಡುಹಿಡಿ_clause (clauses, OMP_CLAUSE_TASKGROUP))
    ಮುಖವಾಡ = 8;
  ಇಲ್ಲದಿದ್ದರೆ
    {
      error_at (loc, "%<#pragma omp cancellation point%> must specify one of "
		     "%<parallel%>, %<for%>, %<sections%> or %<taskgroup%> "
		     "clauses");
      ಹಿಂತಿರುಗಿ;
    }
  ವೃಕ್ಷ stmt = build_call_ಅಭಿವ್ಯಕ್ತಿ_loc (loc, fn, 1,
				   build_int_cst (integer_type_ಗಂಟು, ಮುಖವಾಡ));
  ಕೂಡಿಸು_stmt (stmt);
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
			     ತಾರ್ಕಿಕ &maybe_zero_len, ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ &ಮೊದಲ_non_one,
			     ಎಣಿಕೆ c_omp_region_type ort)
{
  ವೃಕ್ಷ ret, ಕೆಳಗಿನ_bound, ಉದ್ದಳತೆ, type;
  ತಾರ್ಕಿಕ openacc = (ort & C_ORT_ACC) != 0;
  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (t) != OMP_ARRAY_SECTION)
    {
      ಆದರೆ (error_ಕಾರ್ಯಾಂಶ_p (t))
	ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
      c_omp_ವಿಳಾಸ_inspector ai (OMP_CLAUSE_LOCATION (c), t);
      ret = t;
      ಆದರೆ (OMP_CLAUSE_ಸಂಕೇತ (c) != OMP_CLAUSE_AFFINITY
	  && OMP_CLAUSE_ಸಂಕೇತ (c) != OMP_CLAUSE_DEPEND
	  && TYPE_ATOMIC (strip_array_types (ವೃಕ್ಷ_TYPE (t))))
	{
	  error_at (OMP_CLAUSE_LOCATION (c), "%<_Atomic%> %qE in %qs clause",
		    t, omp_clause_ಸಂಕೇತ_name[OMP_CLAUSE_ಸಂಕೇತ (c)]);
	  ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
	}
      ಆದರೆ (!ai.check_clause (c))
	ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ai.component_access_p ()
	       && (OMP_CLAUSE_ಸಂಕೇತ (c) == OMP_CLAUSE_MAP
		   || OMP_CLAUSE_ಸಂಕೇತ (c) == OMP_CLAUSE_ಗಮ್ಯ
		   || OMP_CLAUSE_ಸಂಕೇತ (c) == OMP_CLAUSE_FROM))
	t = ai.get_ಬೇರು_ಪದ (ನಿಜ);
      ಇಲ್ಲದಿದ್ದರೆ
	t = ai.unconverted_ref_origin ();
      ಆದರೆ (t == error_mark_ಗಂಟು)
	ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
      ಆದರೆ (!VAR_P (t)
	  && (ort == C_ORT_ACC || !ಅಭಿವ್ಯಕ್ತಿ_P (t))
	  && ವೃಕ್ಷ_ಸಂಕೇತ (t) != PARM_DECL)
	{
	  ಆದರೆ (DECL_P (t))
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%qD is not a variable in %qs clause", t,
		      omp_clause_ಸಂಕೇತ_name[OMP_CLAUSE_ಸಂಕೇತ (c)]);
	  ಇಲ್ಲದಿದ್ದರೆ
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%qE is not a variable in %qs clause", t,
		      omp_clause_ಸಂಕೇತ_name[OMP_CLAUSE_ಸಂಕೇತ (c)]);
	  ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
	}
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (OMP_CLAUSE_ಸಂಕೇತ (c) != OMP_CLAUSE_AFFINITY
	       && OMP_CLAUSE_ಸಂಕೇತ (c) != OMP_CLAUSE_DEPEND
	       && TYPE_ATOMIC (ವೃಕ್ಷ_TYPE (t)))
	{
	  error_at (OMP_CLAUSE_LOCATION (c), "%<_Atomic%> %qD in %qs clause",
		    t, omp_clause_ಸಂಕೇತ_name[OMP_CLAUSE_ಸಂಕೇತ (c)]);
	  ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
	}
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (OMP_CLAUSE_ಸಂಕೇತ (c) != OMP_CLAUSE_AFFINITY
	       && OMP_CLAUSE_ಸಂಕೇತ (c) != OMP_CLAUSE_DEPEND
	       && VAR_P (t)
	       && DECL_THREAD_LOCAL_P (t))
	{
	  error_at (OMP_CLAUSE_LOCATION (c),
		    "%qD is threadprivate variable in %qs clause", t,
		    omp_clause_ಸಂಕೇತ_name[OMP_CLAUSE_ಸಂಕೇತ (c)]);
	  ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
	}
      ಆದರೆ ((OMP_CLAUSE_ಸಂಕೇತ (c) == OMP_CLAUSE_AFFINITY
	   || OMP_CLAUSE_ಸಂಕೇತ (c) == OMP_CLAUSE_DEPEND)
	  && TYPE_ATOMIC (ವೃಕ್ಷ_TYPE (t))
	  && ಸೂಚಕ_TYPE_P (ವೃಕ್ಷ_TYPE (t)))
	{
	  /* If the array section is pointer based and the pointer
	     itself is _Atomic qualified, we need to atomically load
	     the pointer.  */
	  ret = convert_lvalue_ಗಮ್ಯ_rvalue (OMP_CLAUSE_LOCATION (c),
					  ret, ಸುಳ್ಳು, ಸುಳ್ಳು);
	}
      ಹಿಂತಿರುಗಿ ret;
    }

  ret = handle_omp_array_sections_1 (c, ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (t, 0), types,
				     maybe_zero_len, ಮೊದಲ_non_one, ort);
  ಆದರೆ (ret == error_mark_ಗಂಟು || ret == NULL_ವೃಕ್ಷ)
    ಹಿಂತಿರುಗಿ ret;

  type = ವೃಕ್ಷ_TYPE (ret);
  ಕೆಳಗಿನ_bound = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (t, 1);
  ಉದ್ದಳತೆ = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (t, 2);

  ಆದರೆ (ಕೆಳಗಿನ_bound == error_mark_ಗಂಟು || ಉದ್ದಳತೆ == error_mark_ಗಂಟು)
    ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;

  ಆದರೆ (ಕೆಳಗಿನ_bound && !INTEGRAL_TYPE_P (ವೃಕ್ಷ_TYPE (ಕೆಳಗಿನ_bound)))
    {
      error_at (OMP_CLAUSE_LOCATION (c),
		"low bound %qE of array section does not have integral type",
		ಕೆಳಗಿನ_bound);
      ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
    }
  ಆದರೆ (ಉದ್ದಳತೆ && !INTEGRAL_TYPE_P (ವೃಕ್ಷ_TYPE (ಉದ್ದಳತೆ)))
    {
      error_at (OMP_CLAUSE_LOCATION (c),
		"length %qE of array section does not have integral type",
		ಉದ್ದಳತೆ);
      ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
    }
  ಆದರೆ (ಕೆಳಗಿನ_bound
      && ವೃಕ್ಷ_ಸಂಕೇತ (ಕೆಳಗಿನ_bound) == INTEGER_CST
      && TYPE_PRECISION (ವೃಕ್ಷ_TYPE (ಕೆಳಗಿನ_bound))
	 > TYPE_PRECISION (sizetype))
    ಕೆಳಗಿನ_bound = fold_convert (sizetype, ಕೆಳಗಿನ_bound);
  ಆದರೆ (ಉದ್ದಳತೆ
      && ವೃಕ್ಷ_ಸಂಕೇತ (ಉದ್ದಳತೆ) == INTEGER_CST
      && TYPE_PRECISION (ವೃಕ್ಷ_TYPE (ಉದ್ದಳತೆ))
	 > TYPE_PRECISION (sizetype))
    ಉದ್ದಳತೆ = fold_convert (sizetype, ಉದ್ದಳತೆ);
  ಆದರೆ (ಕೆಳಗಿನ_bound == NULL_ವೃಕ್ಷ)
    ಕೆಳಗಿನ_bound = integer_zero_ಗಂಟು;
  ಆದರೆ (OMP_CLAUSE_ಸಂಕೇತ (c) == OMP_CLAUSE_MAP
      && (OMP_CLAUSE_MAP_ಬಗೆ (c) == GOMP_MAP_ATTACH
	  || OMP_CLAUSE_MAP_ಬಗೆ (c) == GOMP_MAP_DETACH))
    {
      ಆದರೆ (ಉದ್ದಳತೆ != integer_one_ಗಂಟು)
	{
	  error_at (OMP_CLAUSE_LOCATION (c),
		    "expected single pointer in %qs clause",
		    user_omp_clause_ಸಂಕೇತ_name (c, openacc));
	  ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
	}
    }
  ಆದರೆ (ಉದ್ದಳತೆ != NULL_ವೃಕ್ಷ)
    {
      ಆದರೆ (!integer_nonzerop (ಉದ್ದಳತೆ))
	{
	  ಆದರೆ (OMP_CLAUSE_ಸಂಕೇತ (c) == OMP_CLAUSE_AFFINITY
	      || OMP_CLAUSE_ಸಂಕೇತ (c) == OMP_CLAUSE_DEPEND
	      || OMP_CLAUSE_ಸಂಕೇತ (c) == OMP_CLAUSE_REDUCTION
	      || OMP_CLAUSE_ಸಂಕೇತ (c) == OMP_CLAUSE_ಒಳ_REDUCTION
	      || OMP_CLAUSE_ಸಂಕೇತ (c) == OMP_CLAUSE_TASK_REDUCTION)
	    {
	      ಆದರೆ (integer_zerop (ಉದ್ದಳತೆ))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "zero length array section in %qs clause",
			    omp_clause_ಸಂಕೇತ_name[OMP_CLAUSE_ಸಂಕೇತ (c)]);
		  ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
		}
	    }
	  ಇಲ್ಲದಿದ್ದರೆ
	    maybe_zero_len = ನಿಜ;
	}
      ಆದರೆ (ಮೊದಲ_non_one == types.ಉದ್ದಳತೆ ()
	  && (ವೃಕ್ಷ_ಸಂಕೇತ (ಉದ್ದಳತೆ) != INTEGER_CST || integer_onep (ಉದ್ದಳತೆ)))
	ಮೊದಲ_non_one++;
    }
  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (type) == ARRAY_TYPE)
    {
      ಆದರೆ (ಉದ್ದಳತೆ == NULL_ವೃಕ್ಷ
	  && (TYPE_DOMAIN (type) == NULL_ವೃಕ್ಷ
	      || TYPE_MAX_ಮೌಲ್ಯ (TYPE_DOMAIN (type)) == NULL_ವೃಕ್ಷ))
	{
	  error_at (OMP_CLAUSE_LOCATION (c),
		    "for unknown bound array type length expression must "
		    "be specified");
	  ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
	}
      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ಕೆಳಗಿನ_bound) == INTEGER_CST
	  && ವೃಕ್ಷ_int_cst_sgn (ಕೆಳಗಿನ_bound) == -1)
	{
	  error_at (OMP_CLAUSE_LOCATION (c),
		    "negative low bound in array section in %qs clause",
		    omp_clause_ಸಂಕೇತ_name[OMP_CLAUSE_ಸಂಕೇತ (c)]);
	  ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
	}
      ಆದರೆ (ಉದ್ದಳತೆ != NULL_ವೃಕ್ಷ
	  && ವೃಕ್ಷ_ಸಂಕೇತ (ಉದ್ದಳತೆ) == INTEGER_CST
	  && ವೃಕ್ಷ_int_cst_sgn (ಉದ್ದಳತೆ) == -1)
	{
	  error_at (OMP_CLAUSE_LOCATION (c),
		    "negative length in array section in %qs clause",
		    omp_clause_ಸಂಕೇತ_name[OMP_CLAUSE_ಸಂಕೇತ (c)]);
	  ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
	}
      ಆದರೆ (TYPE_DOMAIN (type)
	  && TYPE_MAX_ಮೌಲ್ಯ (TYPE_DOMAIN (type))
	  && ವೃಕ್ಷ_ಸಂಕೇತ (TYPE_MAX_ಮೌಲ್ಯ (TYPE_DOMAIN (type)))
			== INTEGER_CST)
	{
	  ವೃಕ್ಷ ಗಾತ್ರ_2
	    = fold_convert (sizetype, TYPE_MAX_ಮೌಲ್ಯ (TYPE_DOMAIN (type)));
	  ಗಾತ್ರ_2 = ಗಾತ್ರ_binop (PLUS_ಅಭಿವ್ಯಕ್ತಿ, ಗಾತ್ರ_2, ಗಾತ್ರ_one_ಗಂಟು);
	  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ಕೆಳಗಿನ_bound) == INTEGER_CST)
	    {
	      ಆದರೆ (ವೃಕ್ಷ_int_cst_lt (ಗಾತ್ರ_2, ಕೆಳಗಿನ_bound))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "low bound %qE above array section size "
			    "in %qs clause", ಕೆಳಗಿನ_bound,
			    omp_clause_ಸಂಕೇತ_name[OMP_CLAUSE_ಸಂಕೇತ (c)]);
		  ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
		}
	      ಆದರೆ (ವೃಕ್ಷ_int_cst_equal (ಗಾತ್ರ_2, ಕೆಳಗಿನ_bound))
		{
		  ಆದರೆ (OMP_CLAUSE_ಸಂಕೇತ (c) == OMP_CLAUSE_AFFINITY
		      || OMP_CLAUSE_ಸಂಕೇತ (c) == OMP_CLAUSE_DEPEND
		      || OMP_CLAUSE_ಸಂಕೇತ (c) == OMP_CLAUSE_REDUCTION
		      || OMP_CLAUSE_ಸಂಕೇತ (c) == OMP_CLAUSE_ಒಳ_REDUCTION
		      || OMP_CLAUSE_ಸಂಕೇತ (c) == OMP_CLAUSE_TASK_REDUCTION)
		    {
		      error_at (OMP_CLAUSE_LOCATION (c),
				"zero length array section in %qs clause",
				omp_clause_ಸಂಕೇತ_name[OMP_CLAUSE_ಸಂಕೇತ (c)]);
		      ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
		    }
		  maybe_zero_len = ನಿಜ;
		}
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ಉದ್ದಳತೆ == NULL_ವೃಕ್ಷ
		       && ಮೊದಲ_non_one == types.ಉದ್ದಳತೆ ()
		       && ವೃಕ್ಷ_int_cst_equal
			    (TYPE_MAX_ಮೌಲ್ಯ (TYPE_DOMAIN (type)),
			     ಕೆಳಗಿನ_bound))
		ಮೊದಲ_non_one++;
	    }
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ಉದ್ದಳತೆ == NULL_ವೃಕ್ಷ)
	    {
	      ಆದರೆ (OMP_CLAUSE_ಸಂಕೇತ (c) != OMP_CLAUSE_AFFINITY
		  && OMP_CLAUSE_ಸಂಕೇತ (c) != OMP_CLAUSE_DEPEND
		  && OMP_CLAUSE_ಸಂಕೇತ (c) != OMP_CLAUSE_REDUCTION
		  && OMP_CLAUSE_ಸಂಕೇತ (c) != OMP_CLAUSE_ಒಳ_REDUCTION
		  && OMP_CLAUSE_ಸಂಕೇತ (c) != OMP_CLAUSE_TASK_REDUCTION)
		maybe_zero_len = ನಿಜ;
	      ಆದರೆ (ಮೊದಲ_non_one == types.ಉದ್ದಳತೆ ())
		ಮೊದಲ_non_one++;
	    }
	  ಆದರೆ (ಉದ್ದಳತೆ && ವೃಕ್ಷ_ಸಂಕೇತ (ಉದ್ದಳತೆ) == INTEGER_CST)
	    {
	      ಆದರೆ (ವೃಕ್ಷ_int_cst_lt (ಗಾತ್ರ_2, ಉದ್ದಳತೆ))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "length %qE above array section size "
			    "in %qs clause", ಉದ್ದಳತೆ,
			    omp_clause_ಸಂಕೇತ_name[OMP_CLAUSE_ಸಂಕೇತ (c)]);
		  ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
		}
	      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ಕೆಳಗಿನ_bound) == INTEGER_CST)
		{
		  ವೃಕ್ಷ lbpluslen
		    = ಗಾತ್ರ_binop (PLUS_ಅಭಿವ್ಯಕ್ತಿ,
				  fold_convert (sizetype, ಕೆಳಗಿನ_bound),
				  fold_convert (sizetype, ಉದ್ದಳತೆ));
		  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (lbpluslen) == INTEGER_CST
		      && ವೃಕ್ಷ_int_cst_lt (ಗಾತ್ರ_2, lbpluslen))
		    {
		      error_at (OMP_CLAUSE_LOCATION (c),
				"high bound %qE above array section size "
				"in %qs clause", lbpluslen,
				omp_clause_ಸಂಕೇತ_name[OMP_CLAUSE_ಸಂಕೇತ (c)]);
		      ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
		    }
		}
	    }
	}
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ಉದ್ದಳತೆ == NULL_ವೃಕ್ಷ)
	{
	  ಆದರೆ (OMP_CLAUSE_ಸಂಕೇತ (c) != OMP_CLAUSE_AFFINITY
	      && OMP_CLAUSE_ಸಂಕೇತ (c) != OMP_CLAUSE_DEPEND
	      && OMP_CLAUSE_ಸಂಕೇತ (c) != OMP_CLAUSE_REDUCTION
	      && OMP_CLAUSE_ಸಂಕೇತ (c) != OMP_CLAUSE_ಒಳ_REDUCTION
	      && OMP_CLAUSE_ಸಂಕೇತ (c) != OMP_CLAUSE_TASK_REDUCTION)
	    maybe_zero_len = ನಿಜ;
	  ಆದರೆ (ಮೊದಲ_non_one == types.ಉದ್ದಳತೆ ())
	    ಮೊದಲ_non_one++;
	}

      /* For [lb:] we will need to evaluate lb more than once.  */
      ಆದರೆ (ಉದ್ದಳತೆ == NULL_ವೃಕ್ಷ && OMP_CLAUSE_ಸಂಕೇತ (c) != OMP_CLAUSE_DEPEND)
	{
	  ವೃಕ್ಷ lb = save_ಅಭಿವ್ಯಕ್ತಿ (ಕೆಳಗಿನ_bound);
	  ಆದರೆ (lb != ಕೆಳಗಿನ_bound)
	    {
	      ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (t, 1) = lb;
	      ಕೆಳಗಿನ_bound = lb;
	    }
	}
    }
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (type) == ಸೂಚಕ_TYPE)
    {
      ಆದರೆ (ಉದ್ದಳತೆ == NULL_ವೃಕ್ಷ)
	{
	  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ret) == PARM_DECL && C_ARRAY_PARAMETER (ret))
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "for array function parameter length expression "
		      "must be specified");
	  ಇಲ್ಲದಿದ್ದರೆ
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "for pointer type length expression must be specified");
	  ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
	}
      ಆದರೆ (ಉದ್ದಳತೆ != NULL_ವೃಕ್ಷ
	  && ವೃಕ್ಷ_ಸಂಕೇತ (ಉದ್ದಳತೆ) == INTEGER_CST
	  && ವೃಕ್ಷ_int_cst_sgn (ಉದ್ದಳತೆ) == -1)
	{
	  error_at (OMP_CLAUSE_LOCATION (c),
		    "negative length in array section in %qs clause",
		    omp_clause_ಸಂಕೇತ_name[OMP_CLAUSE_ಸಂಕೇತ (c)]);
	  ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
	}
      /* If there is a pointer type anywhere but in the very first
	 array-section-subscript, the array section could be non-contiguous.  */
      ಆದರೆ (OMP_CLAUSE_ಸಂಕೇತ (c) != OMP_CLAUSE_DEPEND
	  && OMP_CLAUSE_ಸಂಕೇತ (c) != OMP_CLAUSE_AFFINITY
	  && ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (t, 0)) == OMP_ARRAY_SECTION)
	{
	  /* If any prior dimension has a non-one length, then deem this
	     array section as non-contiguous.  */
	  ಗಾಗಿ (ವೃಕ್ಷ d = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (t, 0);
	       ವೃಕ್ಷ_ಸಂಕೇತ (d) == OMP_ARRAY_SECTION;
	       d = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (d, 0))
	    {
	      ವೃಕ್ಷ d_ಉದ್ದಳತೆ = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (d, 2);
	      ಆದರೆ (d_ಉದ್ದಳತೆ == NULL_ವೃಕ್ಷ || !integer_onep (d_ಉದ್ದಳತೆ))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "array section is not contiguous in %qs clause",
			    omp_clause_ಸಂಕೇತ_name[OMP_CLAUSE_ಸಂಕೇತ (c)]);
		  ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
		}
	    }
	}
    }
  ಇಲ್ಲದಿದ್ದರೆ
    {
      error_at (OMP_CLAUSE_LOCATION (c),
		"%qE does not have pointer or array type", ret);
      ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
    }
  ಆದರೆ (OMP_CLAUSE_ಸಂಕೇತ (c) != OMP_CLAUSE_DEPEND)
    types.ಸುರಕ್ಷಿತ_ತಳ್ಳು (ವೃಕ್ಷ_TYPE (ret));
  /* We will need to evaluate lb more than once.  */
  ವೃಕ್ಷ lb = save_ಅಭಿವ್ಯಕ್ತಿ (ಕೆಳಗಿನ_bound);
  ಆದರೆ (lb != ಕೆಳಗಿನ_bound)
    {
      ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (t, 1) = lb;
      ಕೆಳಗಿನ_bound = lb;
    }
  ret = build_array_ref (OMP_CLAUSE_LOCATION (c), ret, ಕೆಳಗಿನ_bound);
  ಹಿಂತಿರುಗಿ ret;
}

/* Handle array sections for clause C.  */

ಸ್ಥಿರ ತಾರ್ಕಿಕ
handle_omp_array_sections (ವೃಕ್ಷ &c, ಎಣಿಕೆ c_omp_region_type ort)
{
  ತಾರ್ಕಿಕ maybe_zero_len = ಸುಳ್ಳು;
  ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ ಮೊದಲ_non_one = 0;
  auto_vec<ವೃಕ್ಷ, 10> types;
  ವೃಕ್ಷ *tp = &OMP_CLAUSE_DECL (c);
  ಆದರೆ ((OMP_CLAUSE_ಸಂಕೇತ (c) == OMP_CLAUSE_DEPEND
       || OMP_CLAUSE_ಸಂಕೇತ (c) == OMP_CLAUSE_AFFINITY)
      && OMP_ITERATOR_DECL_P (*tp))
    tp = &ವೃಕ್ಷ_ಮೌಲ್ಯ (*tp);
  ವೃಕ್ಷ ಮೊದಲ = handle_omp_array_sections_1 (c, *tp, types,
					    maybe_zero_len, ಮೊದಲ_non_one,
					    ort);
  ಆದರೆ (ಮೊದಲ == error_mark_ಗಂಟು)
    ಹಿಂತಿರುಗಿ ನಿಜ;
  ಆದರೆ (ಮೊದಲ == NULL_ವೃಕ್ಷ)
    ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
  ಆದರೆ (OMP_CLAUSE_ಸಂಕೇತ (c) == OMP_CLAUSE_DEPEND
      || OMP_CLAUSE_ಸಂಕೇತ (c) == OMP_CLAUSE_AFFINITY)
    {
      ವೃಕ್ಷ t = *tp;
      ವೃಕ್ಷ tem = NULL_ವೃಕ್ಷ;
      /* Need to evaluate side effects in the length expressions
	 if any.  */
      ಆಗ (ವೃಕ್ಷ_ಸಂಕೇತ (t) == ವೃಕ್ಷ_LIST)
	{
	  ಆದರೆ (ವೃಕ್ಷ_ಮೌಲ್ಯ (t) && ವೃಕ್ಷ_SIDE_EFFECTS (ವೃಕ್ಷ_ಮೌಲ್ಯ (t)))
	    {
	      ಆದರೆ (tem == NULL_ವೃಕ್ಷ)
		tem = ವೃಕ್ಷ_ಮೌಲ್ಯ (t);
	      ಇಲ್ಲದಿದ್ದರೆ
		tem = build2 (COMPOUND_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (tem),
			      ವೃಕ್ಷ_ಮೌಲ್ಯ (t), tem);
	    }
	  t = ವೃಕ್ಷ_CHAIN (t);
	}
      ಆದರೆ (tem)
	ಮೊದಲ = build2 (COMPOUND_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (ಮೊದಲ), tem, ಮೊದಲ);
      ಮೊದಲ = c_fully_fold (ಮೊದಲ, ಸುಳ್ಳು, ಖಾಲಿ, ನಿಜ);
      *tp = ಮೊದಲ;
    }
  ಇಲ್ಲದಿದ್ದರೆ
    {
      ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ ಅಂಕೆ = types.ಉದ್ದಳತೆ (), i;
      ವೃಕ್ಷ t, side_effects = NULL_ವೃಕ್ಷ, ಗಾತ್ರ_2 = NULL_ವೃಕ್ಷ;
      ವೃಕ್ಷ condition = NULL_ವೃಕ್ಷ;

      ಆದರೆ (int_ಗಾತ್ರ_ಒಳ_ಬೈಟುಗಳು (ವೃಕ್ಷ_TYPE (ಮೊದಲ)) <= 0)
	maybe_zero_len = ನಿಜ;

      ಗಾಗಿ (i = ಅಂಕೆ, t = OMP_CLAUSE_DECL (c); i > 0;
	   t = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (t, 0))
	{
	  ವೃಕ್ಷ ಕೆಳಗಿನ_bound = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (t, 1);
	  ವೃಕ್ಷ ಉದ್ದಳತೆ = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (t, 2);

	  i--;
	  ಆದರೆ (ಕೆಳಗಿನ_bound
	      && ವೃಕ್ಷ_ಸಂಕೇತ (ಕೆಳಗಿನ_bound) == INTEGER_CST
	      && TYPE_PRECISION (ವೃಕ್ಷ_TYPE (ಕೆಳಗಿನ_bound))
		 > TYPE_PRECISION (sizetype))
	    ಕೆಳಗಿನ_bound = fold_convert (sizetype, ಕೆಳಗಿನ_bound);
	  ಆದರೆ (ಉದ್ದಳತೆ
	      && ವೃಕ್ಷ_ಸಂಕೇತ (ಉದ್ದಳತೆ) == INTEGER_CST
	      && TYPE_PRECISION (ವೃಕ್ಷ_TYPE (ಉದ್ದಳತೆ))
		 > TYPE_PRECISION (sizetype))
	    ಉದ್ದಳತೆ = fold_convert (sizetype, ಉದ್ದಳತೆ);
	  ಆದರೆ (ಕೆಳಗಿನ_bound == NULL_ವೃಕ್ಷ)
	    ಕೆಳಗಿನ_bound = integer_zero_ಗಂಟು;
	  ಆದರೆ (!maybe_zero_len && i > ಮೊದಲ_non_one)
	    {
	      ಆದರೆ (integer_nonzerop (ಕೆಳಗಿನ_bound))
		ಹೋಗು do_warn_noncontiguous;
	      ಆದರೆ (ಉದ್ದಳತೆ != NULL_ವೃಕ್ಷ
		  && ವೃಕ್ಷ_ಸಂಕೇತ (ಉದ್ದಳತೆ) == INTEGER_CST
		  && TYPE_DOMAIN (types[i])
		  && TYPE_MAX_ಮೌಲ್ಯ (TYPE_DOMAIN (types[i]))
		  && ವೃಕ್ಷ_ಸಂಕೇತ (TYPE_MAX_ಮೌಲ್ಯ (TYPE_DOMAIN (types[i])))
		     == INTEGER_CST)
		{
		  ವೃಕ್ಷ ಗಾತ್ರ_2;
		  ಗಾತ್ರ_2 = ಗಾತ್ರ_binop (PLUS_ಅಭಿವ್ಯಕ್ತಿ,
				     TYPE_MAX_ಮೌಲ್ಯ (TYPE_DOMAIN (types[i])),
				     ಗಾತ್ರ_one_ಗಂಟು);
		  ಆದರೆ (!ವೃಕ್ಷ_int_cst_equal (ಉದ್ದಳತೆ, ಗಾತ್ರ_2))
		    {
		     do_warn_noncontiguous:
		      error_at (OMP_CLAUSE_LOCATION (c),
				"array section is not contiguous in %qs "
				"clause",
				omp_clause_ಸಂಕೇತ_name[OMP_CLAUSE_ಸಂಕೇತ (c)]);
		      ಹಿಂತಿರುಗಿ ನಿಜ;
		    }
		}
	      ಆದರೆ (ಉದ್ದಳತೆ != NULL_ವೃಕ್ಷ
		  && ವೃಕ್ಷ_SIDE_EFFECTS (ಉದ್ದಳತೆ))
		{
		  ಆದರೆ (side_effects == NULL_ವೃಕ್ಷ)
		    side_effects = ಉದ್ದಳತೆ;
		  ಇಲ್ಲದಿದ್ದರೆ
		    side_effects = build2 (COMPOUND_ಅಭಿವ್ಯಕ್ತಿ,
					   ವೃಕ್ಷ_TYPE (side_effects),
					   ಉದ್ದಳತೆ, side_effects);
		}
	    }
	  ಇಲ್ಲದಿದ್ದರೆ
	    {
	      ವೃಕ್ಷ l;

	      ಆದರೆ (i > ಮೊದಲ_non_one
		  && ((ಉದ್ದಳತೆ && integer_nonzerop (ಉದ್ದಳತೆ))
		      || OMP_CLAUSE_ಸಂಕೇತ (c) == OMP_CLAUSE_REDUCTION
		      || OMP_CLAUSE_ಸಂಕೇತ (c) == OMP_CLAUSE_ಒಳ_REDUCTION
		      || OMP_CLAUSE_ಸಂಕೇತ (c) == OMP_CLAUSE_TASK_REDUCTION))
		ಮುಂದುವರಿ;
	      ಆದರೆ (ಉದ್ದಳತೆ)
		l = fold_convert (sizetype, ಉದ್ದಳತೆ);
	      ಇಲ್ಲದಿದ್ದರೆ
		{
		  l = ಗಾತ್ರ_binop (PLUS_ಅಭಿವ್ಯಕ್ತಿ,
				  TYPE_MAX_ಮೌಲ್ಯ (TYPE_DOMAIN (types[i])),
				  ಗಾತ್ರ_one_ಗಂಟು);
		  l = ಗಾತ್ರ_binop (MINUS_ಅಭಿವ್ಯಕ್ತಿ, l,
				  fold_convert (sizetype, ಕೆಳಗಿನ_bound));
		}
	      ಆದರೆ (i > ಮೊದಲ_non_one)
		{
		  l = fold_build2 (NE_ಅಭಿವ್ಯಕ್ತಿ, boolean_type_ಗಂಟು, l,
				   ಗಾತ್ರ_zero_ಗಂಟು);
		  ಆದರೆ (condition == NULL_ವೃಕ್ಷ)
		    condition = l;
		  ಇಲ್ಲದಿದ್ದರೆ
		    condition = fold_build2 (ಬಿಟ್_AND_ಅಭಿವ್ಯಕ್ತಿ, boolean_type_ಗಂಟು,
					     l, condition);
		}
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ಗಾತ್ರ_2 == NULL_ವೃಕ್ಷ)
		{
		  ಗಾತ್ರ_2 = ಗಾತ್ರ_ಒಳ_ಬೈಟುಗಳು (ವೃಕ್ಷ_TYPE (types[i]));
		  ವೃಕ್ಷ eltype = ವೃಕ್ಷ_TYPE (types[ಅಂಕೆ - 1]);
		  ಆಗ (ವೃಕ್ಷ_ಸಂಕೇತ (eltype) == ARRAY_TYPE)
		    eltype = ವೃಕ್ಷ_TYPE (eltype);
		  ಆದರೆ (OMP_CLAUSE_ಸಂಕೇತ (c) == OMP_CLAUSE_REDUCTION
		      || OMP_CLAUSE_ಸಂಕೇತ (c) == OMP_CLAUSE_ಒಳ_REDUCTION
		      || OMP_CLAUSE_ಸಂಕೇತ (c) == OMP_CLAUSE_TASK_REDUCTION)
		    {
		      ಆದರೆ (integer_zerop (ಗಾತ್ರ_2)
			  || integer_zerop (ಗಾತ್ರ_ಒಳ_ಬೈಟುಗಳು (eltype)))
			{
			  error_at (OMP_CLAUSE_LOCATION (c),
				    "zero length array section in %qs clause",
				    omp_clause_ಸಂಕೇತ_name[OMP_CLAUSE_ಸಂಕೇತ (c)]);
			  ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
			}
		      ಗಾತ್ರ_2 = ಗಾತ್ರ_binop (EXACT_DIV_ಅಭಿವ್ಯಕ್ತಿ, ಗಾತ್ರ_2,
					 ಗಾತ್ರ_ಒಳ_ಬೈಟುಗಳು (eltype));
		    }
		  ಗಾತ್ರ_2 = ಗಾತ್ರ_binop (MULT_ಅಭಿವ್ಯಕ್ತಿ, ಗಾತ್ರ_2, l);
		  ಆದರೆ (condition)
		    ಗಾತ್ರ_2 = fold_build3 (COND_ಅಭಿವ್ಯಕ್ತಿ, sizetype, condition,
					ಗಾತ್ರ_2, ಗಾತ್ರ_zero_ಗಂಟು);
		}
	      ಇಲ್ಲದಿದ್ದರೆ
		ಗಾತ್ರ_2 = ಗಾತ್ರ_binop (MULT_ಅಭಿವ್ಯಕ್ತಿ, ಗಾತ್ರ_2, l);
	    }
	}
      ಆದರೆ (side_effects)
	ಗಾತ್ರ_2 = build2 (COMPOUND_ಅಭಿವ್ಯಕ್ತಿ, sizetype, side_effects, ಗಾತ್ರ_2);
      ಆದರೆ (OMP_CLAUSE_ಸಂಕೇತ (c) == OMP_CLAUSE_REDUCTION
	  || OMP_CLAUSE_ಸಂಕೇತ (c) == OMP_CLAUSE_ಒಳ_REDUCTION
	  || OMP_CLAUSE_ಸಂಕೇತ (c) == OMP_CLAUSE_TASK_REDUCTION)
	{
	  ಗಾತ್ರ_2 = ಗಾತ್ರ_binop (MINUS_ಅಭಿವ್ಯಕ್ತಿ, ಗಾತ್ರ_2, ಗಾತ್ರ_one_ಗಂಟು);
	  ಗಾತ್ರ_2 = c_fully_fold (ಗಾತ್ರ_2, ಸುಳ್ಳು, ಖಾಲಿ);
	  ಗಾತ್ರ_2 = save_ಅಭಿವ್ಯಕ್ತಿ (ಗಾತ್ರ_2);
	  ವೃಕ್ಷ ಸೂಚ್ಯಂಕ_type = build_ಸೂಚ್ಯಂಕ_type (ಗಾತ್ರ_2);
	  ವೃಕ್ಷ eltype = ವೃಕ್ಷ_TYPE (ಮೊದಲ);
	  ಆಗ (ವೃಕ್ಷ_ಸಂಕೇತ (eltype) == ARRAY_TYPE)
	    eltype = ವೃಕ್ಷ_TYPE (eltype);
	  ವೃಕ್ಷ type = c_build_array_type (eltype, ಸೂಚ್ಯಂಕ_type);
	  ವೃಕ್ಷ ptype = c_build_ಸೂಚಕ_type (eltype);
	  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (t)) == ARRAY_TYPE)
	    t = build_fold_addr_ಅಭಿವ್ಯಕ್ತಿ (t);
	  ವೃಕ್ಷ t2 = build_fold_addr_ಅಭಿವ್ಯಕ್ತಿ (ಮೊದಲ);
	  t2 = fold_convert_loc (OMP_CLAUSE_LOCATION (c),
				 ptrdiff_type_ಗಂಟು, t2);
	  t2 = fold_build2_loc (OMP_CLAUSE_LOCATION (c), MINUS_ಅಭಿವ್ಯಕ್ತಿ,
				ptrdiff_type_ಗಂಟು, t2,
				fold_convert_loc (OMP_CLAUSE_LOCATION (c),
						  ptrdiff_type_ಗಂಟು, t));
	  t2 = c_fully_fold (t2, ಸುಳ್ಳು, ಖಾಲಿ);
	  ಆದರೆ (ವೃಕ್ಷ_ಹೊಂದುತ್ತದೆ_shwi_p (t2))
	    t = build2 (MEM_REF, type, t,
			build_int_cst (ptype, ವೃಕ್ಷ_ಗಮ್ಯ_shwi (t2)));
	  ಇಲ್ಲದಿದ್ದರೆ
	    {
	      t2 = fold_convert_loc (OMP_CLAUSE_LOCATION (c), sizetype, t2);
	      t = build2_loc (OMP_CLAUSE_LOCATION (c), ಸೂಚಕ_PLUS_ಅಭಿವ್ಯಕ್ತಿ,
			      ವೃಕ್ಷ_TYPE (t), t, t2);
	      t = build2 (MEM_REF, type, t, build_int_cst (ptype, 0));
	    }
	  OMP_CLAUSE_DECL (c) = t;
	  ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
	}
      ಮೊದಲ = c_fully_fold (ಮೊದಲ, ಸುಳ್ಳು, ಖಾಲಿ);
      OMP_CLAUSE_DECL (c) = ಮೊದಲ;
      ಆದರೆ (OMP_CLAUSE_ಸಂಕೇತ (c) == OMP_CLAUSE_HAS_DEVICE_ADDR)
	ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
      /* Don't set OMP_CLAUSE_SIZE for bare attach/detach clauses.  */
      ಆದರೆ (OMP_CLAUSE_ಸಂಕೇತ (c) != OMP_CLAUSE_MAP
	  || (OMP_CLAUSE_MAP_ಬಗೆ (c) != GOMP_MAP_ATTACH
	      && OMP_CLAUSE_MAP_ಬಗೆ (c) != GOMP_MAP_DETACH
	      && OMP_CLAUSE_MAP_ಬಗೆ (c) != GOMP_MAP_FORCE_DETACH))
	{
	  ಆದರೆ (ಗಾತ್ರ_2)
	    ಗಾತ್ರ_2 = c_fully_fold (ಗಾತ್ರ_2, ಸುಳ್ಳು, ಖಾಲಿ);
	  OMP_CLAUSE_ಗಾತ್ರ (c) = ಗಾತ್ರ_2;
	}

      ಆದರೆ (OMP_CLAUSE_ಸಂಕೇತ (c) != OMP_CLAUSE_MAP)
	ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;

      auto_vec<omp_addr_token *, 10> addr_ಟೋಕನುಗಳು;

      ಆದರೆ (!omp_parse_ಅಭಿವ್ಯಕ್ತಿ (addr_ಟೋಕನುಗಳು, ಮೊದಲ))
	ಹಿಂತಿರುಗಿ ನಿಜ;

      c_omp_ವಿಳಾಸ_inspector ai (OMP_CLAUSE_LOCATION (c), t);

      ವೃಕ್ಷ nc = ai.expand_map_clause (c, ಮೊದಲ, addr_ಟೋಕನುಗಳು, ort);
      ಆದರೆ (nc != error_mark_ಗಂಟು)
	{
	  ಬಳಸಿ ನಾಮಾಕಾಶ omp_addr_tokenizer;

	  ಆದರೆ (ai.maybe_zero_ಉದ್ದಳತೆ_array_section (c))
	    OMP_CLAUSE_MAP_MAYBE_ZERO_ಉದ್ದಳತೆ_ARRAY_SECTION (c) = 1;

	  /* !!! If we're accessing a base decl via chained access
	     methods (e.g. multiple indirections), duplicate clause
	     detection won't work properly.  Skip it in that case.  */
	  ಆದರೆ ((addr_ಟೋಕನುಗಳು[0]->type == STRUCTURE_ತಳ
	       || addr_ಟೋಕನುಗಳು[0]->type == ARRAY_ತಳ)
	      && addr_ಟೋಕನುಗಳು[0]->u.structure_ತಳ_ಬಗೆ == ತಳ_DECL
	      && addr_ಟೋಕನುಗಳು[1]->type == ACCESS_ವಿಧಾನ
	      && omp_access_chain_p (addr_ಟೋಕನುಗಳು, 1))
	    c = nc;

	  ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
	}
    }
  ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
}

/* Helper function of finish_omp_clauses.  Clone STMT as if we were making
   an inline call.  But, remap
   the OMP_DECL1 VAR_DECL (omp_out resp. omp_orig) to PLACEHOLDER
   and OMP_DECL2 VAR_DECL (omp_in resp. omp_priv) to DECL.  */

ಸ್ಥಿರ ವೃಕ್ಷ
c_clone_omp_udr (ವೃಕ್ಷ stmt, ವೃಕ್ಷ omp_decl1, ವೃಕ್ಷ omp_decl2,
		 ವೃಕ್ಷ decl, ವೃಕ್ಷ placeholder)
{
  copy_body_ದತ್ತಾಂಶ id;
  hash_map<ವೃಕ್ಷ, ವೃಕ್ಷ> decl_map;

  decl_map.put (omp_decl1, placeholder);
  decl_map.put (omp_decl2, decl);
  memset (&id, 0, ಗಾತ್ರ (id));
  id.src_fn = DECL_CONTEXT (omp_decl1);
  id.dst_fn = current_function_decl;
  id.src_cfun = DECL_STRUCT_FUNCTION (id.src_fn);
  id.decl_map = &decl_map;

  id.copy_decl = copy_decl_no_change;
  id.transform_call_ನಕ್ಷೆ_ಅಂಚುಗಳು = CB_CGE_DUPLICATE;
  id.transform_new_cfg = ನಿಜ;
  id.transform_return_ಗಮ್ಯ_modify = ಸುಳ್ಳು;
  id.eh_lp_nr = 0;
  walk_ವೃಕ್ಷ (&stmt, copy_ವೃಕ್ಷ_body_r, &id, ಖಾಲಿ);
  ಹಿಂತಿರುಗಿ stmt;
}

/* Helper function of c_finish_omp_clauses, called via walk_tree.
   Find OMP_CLAUSE_PLACEHOLDER (passed in DATA) in *TP.  */

ಸ್ಥಿರ ವೃಕ್ಷ
c_ಕಂಡುಹಿಡಿ_omp_placeholder_r (ವೃಕ್ಷ *tp, ಪೂರ್ಣಾಂಕ *, ಶೂನ್ಯ *ದತ್ತಾಂಶ)
{
  ಆದರೆ (*tp == (ವೃಕ್ಷ) ದತ್ತಾಂಶ)
    ಹಿಂತಿರುಗಿ *tp;
  ಹಿಂತಿರುಗಿ NULL_ವೃಕ್ಷ;
}

/* Similarly, but also walk aggregate fields.  */

ರಚನೆ c_ಕಂಡುಹಿಡಿ_omp_var_s { ವೃಕ್ಷ var; hash_ಗಣ<ವೃಕ್ಷ> *pset; };

ಸ್ಥಿರ ವೃಕ್ಷ
c_ಕಂಡುಹಿಡಿ_omp_var_r (ವೃಕ್ಷ *tp, ಪೂರ್ಣಾಂಕ *, ಶೂನ್ಯ *ದತ್ತಾಂಶ)
{
  ಆದರೆ (*tp == ((ರಚನೆ c_ಕಂಡುಹಿಡಿ_omp_var_s *) ದತ್ತಾಂಶ)->var)
    ಹಿಂತಿರುಗಿ *tp;
  ಆದರೆ (ದಾಖಲೆ_OR_UNION_TYPE_P (*tp))
    {
      ವೃಕ್ಷ ಕ್ಷೇತ್ರ_2;
      hash_ಗಣ<ವೃಕ್ಷ> *pset = ((ರಚನೆ c_ಕಂಡುಹಿಡಿ_omp_var_s *) ದತ್ತಾಂಶ)->pset;

      ಗಾಗಿ (ಕ್ಷೇತ್ರ_2 = TYPE_FIELDS (*tp); ಕ್ಷೇತ್ರ_2;
	   ಕ್ಷೇತ್ರ_2 = DECL_CHAIN (ಕ್ಷೇತ್ರ_2))
	ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ಕ್ಷೇತ್ರ_2) == ಕ್ಷೇತ್ರ_DECL)
	  {
	    ವೃಕ್ಷ ret = walk_ವೃಕ್ಷ (&DECL_ಕ್ಷೇತ್ರ_ಸ್ಥಾನಾಂತರ (ಕ್ಷೇತ್ರ_2),
				  c_ಕಂಡುಹಿಡಿ_omp_var_r, ದತ್ತಾಂಶ, pset);
	    ಆದರೆ (ret)
	      ಹಿಂತಿರುಗಿ ret;
	    ret = walk_ವೃಕ್ಷ (&DECL_ಗಾತ್ರ (ಕ್ಷೇತ್ರ_2), c_ಕಂಡುಹಿಡಿ_omp_var_r, ದತ್ತಾಂಶ, pset);
	    ಆದರೆ (ret)
	      ಹಿಂತಿರುಗಿ ret;
	    ret = walk_ವೃಕ್ಷ (&DECL_ಗಾತ್ರ_UNIT (ಕ್ಷೇತ್ರ_2), c_ಕಂಡುಹಿಡಿ_omp_var_r, ದತ್ತಾಂಶ,
			     pset);
	    ಆದರೆ (ret)
	      ಹಿಂತಿರುಗಿ ret;
	    ret = walk_ವೃಕ್ಷ (&ವೃಕ್ಷ_TYPE (ಕ್ಷೇತ್ರ_2), c_ಕಂಡುಹಿಡಿ_omp_var_r, ದತ್ತಾಂಶ, pset);
	    ಆದರೆ (ret)
	      ಹಿಂತಿರುಗಿ ret;
	  }
    }
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (INTEGRAL_TYPE_P (*tp))
    ಹಿಂತಿರುಗಿ walk_ವೃಕ್ಷ (&TYPE_MAX_ಮೌಲ್ಯ (*tp), c_ಕಂಡುಹಿಡಿ_omp_var_r, ದತ್ತಾಂಶ,
		      ((ರಚನೆ c_ಕಂಡುಹಿಡಿ_omp_var_s *) ದತ್ತಾಂಶ)->pset);
  ಹಿಂತಿರುಗಿ NULL_ವೃಕ್ಷ;
}

/* Finish OpenMP iterators ITER.  Return true if they are erroneous
   and clauses containing them should be removed.  */

ಸ್ಥಿರ ತಾರ್ಕಿಕ
c_omp_ಮುಕ್ತಾಯ_iterators (ವೃಕ್ಷ iter)
{
  ತಾರ್ಕಿಕ ret = ಸುಳ್ಳು;
  ಗಾಗಿ (ವೃಕ್ಷ it = iter; it; it = ವೃಕ್ಷ_CHAIN (it))
    {
      ವೃಕ್ಷ var = OMP_ITERATOR_VAR (it);
      ವೃಕ್ಷ begin = OMP_ITERATOR_BEGIN (it);
      ವೃಕ್ಷ ಕೊನೆ = OMP_ITERATOR_ಕೊನೆ (it);
      ವೃಕ್ಷ ಹೆಜ್ಜೆ = OMP_ITERATOR_ಹೆಜ್ಜೆ (it);
      ವೃಕ್ಷ orig_ಹೆಜ್ಜೆ;
      ವೃಕ್ಷ type = ವೃಕ್ಷ_TYPE (var);
      location_t loc = DECL_ಮೂಲ_LOCATION (var);
      ಆದರೆ (type == error_mark_ಗಂಟು)
	{
	  ret = ನಿಜ;
	  ಮುಂದುವರಿ;
	}
      ಆದರೆ (!INTEGRAL_TYPE_P (type) && !ಸೂಚಕ_TYPE_P (type))
	{
	  error_at (loc, "iterator %qD has neither integral nor pointer type",
		    var);
	  ret = ನಿಜ;
	  ಮುಂದುವರಿ;
	}
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (TYPE_ATOMIC (type))
	{
	  error_at (loc, "iterator %qD has %<_Atomic%> qualified type", var);
	  ret = ನಿಜ;
	  ಮುಂದುವರಿ;
	}
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (TYPE_READONLY (type))
	{
	  error_at (loc, "iterator %qD has const qualified type", var);
	  ret = ನಿಜ;
	  ಮುಂದುವರಿ;
	}
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ಹೆಜ್ಜೆ == error_mark_ಗಂಟು
	       || ವೃಕ್ಷ_TYPE (ಹೆಜ್ಜೆ) == error_mark_ಗಂಟು)
	{
	  ret = ನಿಜ;
	  ಮುಂದುವರಿ;
	}
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!INTEGRAL_TYPE_P (ವೃಕ್ಷ_TYPE (ಹೆಜ್ಜೆ)))
	{
	  error_at (ಅಭಿವ್ಯಕ್ತಿ_LOC_OR_LOC (ಹೆಜ್ಜೆ, loc),
		    "iterator step with non-integral type");
	  ret = ನಿಜ;
	  ಮುಂದುವರಿ;
	}
      begin = c_fully_fold (build_c_cast (loc, type, begin), ಸುಳ್ಳು, ಖಾಲಿ);
      ಕೊನೆ = c_fully_fold (build_c_cast (loc, type, ಕೊನೆ), ಸುಳ್ಳು, ಖಾಲಿ);
      orig_ಹೆಜ್ಜೆ = save_ಅಭಿವ್ಯಕ್ತಿ (c_fully_fold (ಹೆಜ್ಜೆ, ಸುಳ್ಳು, ಖಾಲಿ));
      ವೃಕ್ಷ stype = ಸೂಚಕ_TYPE_P (type) ? sizetype : type;
      ಹೆಜ್ಜೆ = c_fully_fold (build_c_cast (loc, stype, orig_ಹೆಜ್ಜೆ), ಸುಳ್ಳು, ಖಾಲಿ);
      ಆದರೆ (ಸೂಚಕ_TYPE_P (type))
	{
	  begin = save_ಅಭಿವ್ಯಕ್ತಿ (begin);
	  ಹೆಜ್ಜೆ = ಸೂಚಕ_int_ಮೊತ್ತ (loc, PLUS_ಅಭಿವ್ಯಕ್ತಿ, begin, ಹೆಜ್ಜೆ);
	  ಹೆಜ್ಜೆ = fold_build2_loc (loc, MINUS_ಅಭಿವ್ಯಕ್ತಿ, sizetype,
				  fold_convert (sizetype, ಹೆಜ್ಜೆ),
				  fold_convert (sizetype, begin));
	  ಹೆಜ್ಜೆ = fold_convert (ssizetype, ಹೆಜ್ಜೆ);
	}
      ಆದರೆ (integer_zerop (ಹೆಜ್ಜೆ))
	{
	  error_at (loc, "iterator %qD has zero step", var);
	  ret = ನಿಜ;
	  ಮುಂದುವರಿ;
	}

      ಆದರೆ (begin == error_mark_ಗಂಟು
	  || ಕೊನೆ == error_mark_ಗಂಟು
	  || ಹೆಜ್ಜೆ == error_mark_ಗಂಟು
	  || orig_ಹೆಜ್ಜೆ == error_mark_ಗಂಟು)
	{
	  ret = ನಿಜ;
	  ಮುಂದುವರಿ;
	}
      hash_ಗಣ<ವೃಕ್ಷ> pset;
      ವೃಕ್ಷ it2;
      ಗಾಗಿ (it2 = ವೃಕ್ಷ_CHAIN (it); it2; it2 = ವೃಕ್ಷ_CHAIN (it2))
	{
	  ವೃಕ್ಷ var2 = OMP_ITERATOR_VAR (it2);
	  ವೃಕ್ಷ begin2 = OMP_ITERATOR_BEGIN (it2);
	  ವೃಕ್ಷ end2 = OMP_ITERATOR_ಕೊನೆ (it2);
	  ವೃಕ್ಷ step2 = OMP_ITERATOR_ಹೆಜ್ಜೆ (it2);
	  ವೃಕ್ಷ type2 = ವೃಕ್ಷ_TYPE (var2);
	  location_t loc2 = DECL_ಮೂಲ_LOCATION (var2);
	  ರಚನೆ c_ಕಂಡುಹಿಡಿ_omp_var_s ದತ್ತಾಂಶ = { var, &pset };
	  ಆದರೆ (walk_ವೃಕ್ಷ (&type2, c_ಕಂಡುಹಿಡಿ_omp_var_r, &ದತ್ತಾಂಶ, &pset))
	    {
	      error_at (loc2,
			"type of iterator %qD refers to outer iterator %qD",
			var2, var);
	      ನಿಲ್ಲಿಸು;
	    }
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (walk_ವೃಕ್ಷ (&begin2, c_ಕಂಡುಹಿಡಿ_omp_var_r, &ದತ್ತಾಂಶ, &pset))
	    {
	      error_at (ಅಭಿವ್ಯಕ್ತಿ_LOC_OR_LOC (begin2, loc2),
			"begin expression refers to outer iterator %qD", var);
	      ನಿಲ್ಲಿಸು;
	    }
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (walk_ವೃಕ್ಷ (&end2, c_ಕಂಡುಹಿಡಿ_omp_var_r, &ದತ್ತಾಂಶ, &pset))
	    {
	      error_at (ಅಭಿವ್ಯಕ್ತಿ_LOC_OR_LOC (end2, loc2),
			"end expression refers to outer iterator %qD", var);
	      ನಿಲ್ಲಿಸು;
	    }
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (walk_ವೃಕ್ಷ (&step2, c_ಕಂಡುಹಿಡಿ_omp_var_r, &ದತ್ತಾಂಶ, &pset))
	    {
	      error_at (ಅಭಿವ್ಯಕ್ತಿ_LOC_OR_LOC (step2, loc2),
			"step expression refers to outer iterator %qD", var);
	      ನಿಲ್ಲಿಸು;
	    }
	}
      ಆದರೆ (it2)
	{
	  ret = ನಿಜ;
	  ಮುಂದುವರಿ;
	}
      OMP_ITERATOR_BEGIN (it) = begin;
      OMP_ITERATOR_ಕೊನೆ (it) = ಕೊನೆ;
      OMP_ITERATOR_ಹೆಜ್ಜೆ (it) = ಹೆಜ್ಜೆ;
      OMP_ITERATOR_ORIG_ಹೆಜ್ಜೆ (it) = orig_ಹೆಜ್ಜೆ;
    }
  ಹಿಂತಿರುಗಿ ret;
}

/* Ensure that pointers are used in OpenACC attach and detach clauses.
   Return true if an error has been detected.  */

ಸ್ಥಿರ ತಾರ್ಕಿಕ
c_oacc_check_attachments (ವೃಕ್ಷ c)
{
  ಆದರೆ (OMP_CLAUSE_ಸಂಕೇತ (c) != OMP_CLAUSE_MAP)
    ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;

  /* OpenACC attach / detach clauses must be pointers.  */
  ಆದರೆ (OMP_CLAUSE_MAP_ಬಗೆ (c) == GOMP_MAP_ATTACH
      || OMP_CLAUSE_MAP_ಬಗೆ (c) == GOMP_MAP_DETACH)
    {
      ವೃಕ್ಷ t = OMP_CLAUSE_DECL (c);

      ಆಗ (ವೃಕ್ಷ_ಸಂಕೇತ (t) == OMP_ARRAY_SECTION)
	t = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (t, 0);

      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (t)) != ಸೂಚಕ_TYPE)
	{
	  error_at (OMP_CLAUSE_LOCATION (c), "expected pointer in %qs clause",
		    user_omp_clause_ಸಂಕೇತ_name (c, ನಿಜ));
	  ಹಿಂತಿರುಗಿ ನಿಜ;
	}
    }

  ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
}

/* For all elements of CLAUSES, validate them against their constraints.
   Remove any elements from the list that are invalid.  */

ವೃಕ್ಷ
c_ಮುಕ್ತಾಯ_omp_clauses (ವೃಕ್ಷ clauses, ಎಣಿಕೆ c_omp_region_type ort)
{
  bitmap_ತಲೆ generic_ತಲೆ, firstprivate_ತಲೆ, lastprivate_ತಲೆ;
  bitmap_ತಲೆ aligned_ತಲೆ, map_ತಲೆ, map_ಕ್ಷೇತ್ರ_ತಲೆ, map_firstprivate_ತಲೆ;
  bitmap_ತಲೆ oacc_reduction_ತಲೆ, is_on_device_ತಲೆ;
  ವೃಕ್ಷ c, t, type, *pc;
  ವೃಕ್ಷ simdlen = NULL_ವೃಕ್ಷ, safelen = NULL_ವೃಕ್ಷ;
  ತಾರ್ಕಿಕ branch_ನೋಡಿದ = ಸುಳ್ಳು;
  ತಾರ್ಕಿಕ copyprivate_ನೋಡಿದ = ಸುಳ್ಳು;
  ತಾರ್ಕಿಕ mergeable_ನೋಡಿದ = ಸುಳ್ಳು;
  ವೃಕ್ಷ *detach_ನೋಡಿದ = ಖಾಲಿ;
  ತಾರ್ಕಿಕ ರೇಖೀಯ_variable_ಹೆಜ್ಜೆ_check = ಸುಳ್ಳು;
  ವೃಕ್ಷ *nowait_clause = ಖಾಲಿ;
  ವೃಕ್ಷ *grainsize_ನೋಡಿದ = ಖಾಲಿ;
  ತಾರ್ಕಿಕ ಅಂಕೆ_tasks_ನೋಡಿದ = ಸುಳ್ಳು;
  ವೃಕ್ಷ ordered_clause = NULL_ವೃಕ್ಷ;
  ವೃಕ್ಷ ವೇಳಾಪಟ್ಟಿ_clause = NULL_ವೃಕ್ಷ;
  ತಾರ್ಕಿಕ oacc_async = ಸುಳ್ಳು;
  ವೃಕ್ಷ ಕೊನೆಯ_iterators = NULL_ವೃಕ್ಷ;
  ತಾರ್ಕಿಕ ಕೊನೆಯ_iterators_remove = ಸುಳ್ಳು;
  ವೃಕ್ಷ *nogroup_ನೋಡಿದ = ಖಾಲಿ;
  ವೃಕ್ಷ *ಕ್ರಮ_clause = ಖಾಲಿ;
  /* 1 if normal/task reduction has been seen, -1 if inscan reduction
     has been seen, -2 if mixed inscan/normal reduction diagnosed.  */
  ಪೂರ್ಣಾಂಕ reduction_ನೋಡಿದ = 0;
  ತಾರ್ಕಿಕ allocate_ನೋಡಿದ = ಸುಳ್ಳು;
  ತಾರ್ಕಿಕ implicit_moved = ಸುಳ್ಳು;
  ತಾರ್ಕಿಕ ಗುರಿ_ಒಳ_reduction_ನೋಡಿದ = ಸುಳ್ಳು;
  ವೃಕ್ಷ *ತುಂಬಿದ_ನೋಡಿದ = ಖಾಲಿ;
  ತಾರ್ಕಿಕ partial_ನೋಡಿದ = ಸುಳ್ಳು;
  ತಾರ್ಕಿಕ openacc = (ort & C_ORT_ACC) != 0;
  ತಾರ್ಕಿಕ init_ನೋಡಿದ = ಸುಳ್ಳು;
  ತಾರ್ಕಿಕ init_use_destroy_ನೋಡಿದ = ಸುಳ್ಳು;
  ವೃಕ್ಷ init_no_targetsync_clause = NULL_ವೃಕ್ಷ;
  ವೃಕ್ಷ depend_clause = NULL_ವೃಕ್ಷ;

  ಆದರೆ (!openacc)
    clauses = omp_remove_duplicate_maps (clauses, ನಿಜ);

  bitmap_obstack_initialize (ಖಾಲಿ);
  bitmap_initialize (&generic_ತಲೆ, &bitmap_default_obstack);
  bitmap_initialize (&firstprivate_ತಲೆ, &bitmap_default_obstack);
  bitmap_initialize (&lastprivate_ತಲೆ, &bitmap_default_obstack);
  bitmap_initialize (&aligned_ತಲೆ, &bitmap_default_obstack);
  /* If ort == C_ORT_OMP_DECLARE_SIMD used as uniform_head instead.  */
  bitmap_initialize (&map_ತಲೆ, &bitmap_default_obstack);
  bitmap_initialize (&map_ಕ್ಷೇತ್ರ_ತಲೆ, &bitmap_default_obstack);
  bitmap_initialize (&map_firstprivate_ತಲೆ, &bitmap_default_obstack);
  /* If ort == C_ORT_OMP used as nontemporal_head or use_device_xxx_head
     instead and for ort == C_ORT_OMP_TARGET used as in_reduction_head.  */
  bitmap_initialize (&oacc_reduction_ತಲೆ, &bitmap_default_obstack);
  bitmap_initialize (&is_on_device_ತಲೆ, &bitmap_default_obstack);

  ಆದರೆ (openacc)
    ಗಾಗಿ (c = clauses; c; c = OMP_CLAUSE_CHAIN (c))
      ಆದರೆ (OMP_CLAUSE_ಸಂಕೇತ (c) == OMP_CLAUSE_ASYNC)
	{
	  oacc_async = ನಿಜ;
	  ನಿಲ್ಲಿಸು;
	}

  ವೃಕ್ಷ *grp_ಆರಂಭ_p = ಖಾಲಿ, grp_sentinel = NULL_ವೃಕ್ಷ;

  ಗಾಗಿ (pc = &clauses, c = clauses; c ; c = *pc)
    {
      ತಾರ್ಕಿಕ remove = ಸುಳ್ಳು;
      ತಾರ್ಕಿಕ need_complete = ಸುಳ್ಳು;
      ತಾರ್ಕಿಕ need_implicitly_determined = ಸುಳ್ಳು;

      /* We've reached the end of a list of expanded nodes.  Reset the group
	 start pointer.  */
      ಆದರೆ (c == grp_sentinel)
	{
	  ಆದರೆ (grp_ಆರಂಭ_p
	      && OMP_CLAUSE_HAS_ITERATORS (*grp_ಆರಂಭ_p))
	    ಗಾಗಿ (ವೃಕ್ಷ gc = *grp_ಆರಂಭ_p; gc != grp_sentinel;
		 gc = OMP_CLAUSE_CHAIN (gc))
	      OMP_CLAUSE_ITERATORS (gc) = OMP_CLAUSE_ITERATORS (*grp_ಆರಂಭ_p);
	  grp_ಆರಂಭ_p = ಖಾಲಿ;
	}

      ಆಯ್ಕೆ (OMP_CLAUSE_ಸಂಕೇತ (c))
	{
	ಸ್ಥಿತಿ OMP_CLAUSE_SHARED:
	  need_implicitly_determined = ನಿಜ;
	  ಹೋಗು check_dup_generic;

	ಸ್ಥಿತಿ OMP_CLAUSE_ಖಾಸಗಿ:
	  need_complete = ನಿಜ;
	  need_implicitly_determined = ನಿಜ;
	  ಹೋಗು check_dup_generic;

	ಸ್ಥಿತಿ OMP_CLAUSE_REDUCTION:
	  ಆದರೆ (reduction_ನೋಡಿದ == 0)
	    reduction_ನೋಡಿದ = OMP_CLAUSE_REDUCTION_INSCAN (c) ? -1 : 1;
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (reduction_ನೋಡಿದ != -2
		   && reduction_ನೋಡಿದ != (OMP_CLAUSE_REDUCTION_INSCAN (c)
					 ? -1 : 1))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<inscan%> and non-%<inscan%> %<reduction%> clauses "
			"on the same construct");
	      reduction_ನೋಡಿದ = -2;
	    }
	  /* FALLTHRU */
	ಸ್ಥಿತಿ OMP_CLAUSE_ಒಳ_REDUCTION:
	ಸ್ಥಿತಿ OMP_CLAUSE_TASK_REDUCTION:
	  need_implicitly_determined = ನಿಜ;
	  t = OMP_CLAUSE_DECL (c);
	  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (t) == OMP_ARRAY_SECTION)
	    {
	      ಆದರೆ (handle_omp_array_sections (c, ort))
		{
		  remove = ನಿಜ;
		  ನಿಲ್ಲಿಸು;
		}

	      t = OMP_CLAUSE_DECL (c);
	      ಆದರೆ (OMP_CLAUSE_ಸಂಕೇತ (c) == OMP_CLAUSE_REDUCTION
		  && OMP_CLAUSE_REDUCTION_INSCAN (c))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%<inscan%> %<reduction%> clause with array "
			    "section");
		  remove = ನಿಜ;
		  ನಿಲ್ಲಿಸು;
		}
	    }
	  t = require_complete_type (OMP_CLAUSE_LOCATION (c), t);
	  ಆದರೆ (t == error_mark_ಗಂಟು)
	    {
	      remove = ನಿಜ;
	      ನಿಲ್ಲಿಸು;
	    }
	  ಆದರೆ (oacc_async)
	    c_mark_addressable (t);
	  type = ವೃಕ್ಷ_TYPE (t);
	  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (t) == MEM_REF)
	    type = ವೃಕ್ಷ_TYPE (type);
	  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (type) == ARRAY_TYPE)
	    {
	      ವೃಕ್ಷ oatype = type;
	      gcc_assert (ವೃಕ್ಷ_ಸಂಕೇತ (t) != MEM_REF);
	      ಆಗ (ವೃಕ್ಷ_ಸಂಕೇತ (type) == ARRAY_TYPE)
		type = ವೃಕ್ಷ_TYPE (type);
	      ಆದರೆ (integer_zerop (TYPE_ಗಾತ್ರ_UNIT (type)))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD in %<reduction%> clause is a zero size array",
			    t);
		  remove = ನಿಜ;
		  ನಿಲ್ಲಿಸು;
		}
	      ವೃಕ್ಷ ಗಾತ್ರ_2 = ಗಾತ್ರ_binop (EXACT_DIV_ಅಭಿವ್ಯಕ್ತಿ, TYPE_ಗಾತ್ರ_UNIT (oatype),
				      TYPE_ಗಾತ್ರ_UNIT (type));
	      ಆದರೆ (integer_zerop (ಗಾತ್ರ_2))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD in %<reduction%> clause is a zero size array",
			    t);
		  remove = ನಿಜ;
		  ನಿಲ್ಲಿಸು;
		}
	      ಗಾತ್ರ_2 = ಗಾತ್ರ_binop (MINUS_ಅಭಿವ್ಯಕ್ತಿ, ಗಾತ್ರ_2, ಗಾತ್ರ_one_ಗಂಟು);
	      ಗಾತ್ರ_2 = save_ಅಭಿವ್ಯಕ್ತಿ (ಗಾತ್ರ_2);
	      ವೃಕ್ಷ ಸೂಚ್ಯಂಕ_type = build_ಸೂಚ್ಯಂಕ_type (ಗಾತ್ರ_2);
	      ವೃಕ್ಷ atype = c_build_array_type (TYPE_MAIN_VARIANT (type),
					       ಸೂಚ್ಯಂಕ_type);
	      atype = c_build_qualified_type (atype, TYPE_QUALS (type));
	      ವೃಕ್ಷ ptype = c_build_ಸೂಚಕ_type (type);
	      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (t)) == ARRAY_TYPE)
		t = build_fold_addr_ಅಭಿವ್ಯಕ್ತಿ (t);
	      t = build2 (MEM_REF, atype, t, build_int_cst (ptype, 0));
	      OMP_CLAUSE_DECL (c) = t;
	    }
	  ಆದರೆ (TYPE_ATOMIC (type))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<_Atomic%> %qE in %<reduction%> clause", t);
	      remove = ನಿಜ;
	      ನಿಲ್ಲಿಸು;
	    }
	  ಆದರೆ (OMP_CLAUSE_ಸಂಕೇತ (c) != OMP_CLAUSE_REDUCTION
	      || OMP_CLAUSE_REDUCTION_TASK (c))
	    {
	      /* Disallow zero sized or potentially zero sized task
		 reductions.  */
	      ಆದರೆ (integer_zerop (TYPE_ಗಾತ್ರ_UNIT (type)))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "zero sized type %qT in %qs clause", type,
			    omp_clause_ಸಂಕೇತ_name[OMP_CLAUSE_ಸಂಕೇತ (c)]);
		  remove = ನಿಜ;
		  ನಿಲ್ಲಿಸು;
		}
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (TYPE_ಗಾತ್ರ_UNIT (type)) != INTEGER_CST)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "variable sized type %qT in %qs clause", type,
			    omp_clause_ಸಂಕೇತ_name[OMP_CLAUSE_ಸಂಕೇತ (c)]);
		  remove = ನಿಜ;
		  ನಿಲ್ಲಿಸು;
		}
	    }
	  ಆದರೆ (OMP_CLAUSE_REDUCTION_PLACEHOLDER (c) == NULL_ವೃಕ್ಷ
	      && (FLOAT_TYPE_P (type)
		  || ವೃಕ್ಷ_ಸಂಕೇತ (type) == COMPLEX_TYPE))
	    {
	      ಎಣಿಕೆ ವೃಕ್ಷ_ಸಂಕೇತ_2 r_ಸಂಕೇತ = OMP_CLAUSE_REDUCTION_ಸಂಕೇತ (c);
	      ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *r_name = ಖಾಲಿ;

	      ಆಯ್ಕೆ (r_ಸಂಕೇತ)
		{
		ಸ್ಥಿತಿ PLUS_ಅಭಿವ್ಯಕ್ತಿ:
		ಸ್ಥಿತಿ MULT_ಅಭಿವ್ಯಕ್ತಿ:
		ಸ್ಥಿತಿ MINUS_ಅಭಿವ್ಯಕ್ತಿ:
		ಸ್ಥಿತಿ TRUTH_ANDIF_ಅಭಿವ್ಯಕ್ತಿ:
		ಸ್ಥಿತಿ TRUTH_ORIF_ಅಭಿವ್ಯಕ್ತಿ:
		  ನಿಲ್ಲಿಸು;
		ಸ್ಥಿತಿ MIN_ಅಭಿವ್ಯಕ್ತಿ:
		  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (type) == COMPLEX_TYPE)
		    r_name = "min";
		  ನಿಲ್ಲಿಸು;
		ಸ್ಥಿತಿ MAX_ಅಭಿವ್ಯಕ್ತಿ:
		  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (type) == COMPLEX_TYPE)
		    r_name = "max";
		  ನಿಲ್ಲಿಸು;
		ಸ್ಥಿತಿ ಬಿಟ್_AND_ಅಭಿವ್ಯಕ್ತಿ:
		  r_name = "&";
		  ನಿಲ್ಲಿಸು;
		ಸ್ಥಿತಿ ಬಿಟ್_XOR_ಅಭಿವ್ಯಕ್ತಿ:
		  r_name = "^";
		  ನಿಲ್ಲಿಸು;
		ಸ್ಥಿತಿ ಬಿಟ್_IOR_ಅಭಿವ್ಯಕ್ತಿ:
		  r_name = "|";
		  ನಿಲ್ಲಿಸು;
		ಪೂರ್ವನಿಯೋಜಿತ:
		  gcc_unreachable ();
		}
	      ಆದರೆ (r_name)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qE has invalid type for %<reduction(%s)%>",
			    t, r_name);
		  remove = ನಿಜ;
		  ನಿಲ್ಲಿಸು;
		}
	    }
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (OMP_CLAUSE_REDUCTION_PLACEHOLDER (c) == error_mark_ಗಂಟು)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"user defined reduction not found for %qE", t);
	      remove = ನಿಜ;
	      ನಿಲ್ಲಿಸು;
	    }
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (OMP_CLAUSE_REDUCTION_PLACEHOLDER (c))
	    {
	      ವೃಕ್ಷ list = OMP_CLAUSE_REDUCTION_PLACEHOLDER (c);
	      type = TYPE_MAIN_VARIANT (type);
	      ವೃಕ್ಷ placeholder = build_decl (OMP_CLAUSE_LOCATION (c),
					     VAR_DECL, NULL_ವೃಕ್ಷ, type);
	      ವೃಕ್ಷ decl_placeholder = NULL_ವೃಕ್ಷ;
	      OMP_CLAUSE_REDUCTION_PLACEHOLDER (c) = placeholder;
	      DECL_ARTIFICIAL (placeholder) = 1;
	      DECL_IGNORED_P (placeholder) = 1;
	      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (t) == MEM_REF)
		{
		  decl_placeholder = build_decl (OMP_CLAUSE_LOCATION (c),
						 VAR_DECL, NULL_ವೃಕ್ಷ, type);
		  OMP_CLAUSE_REDUCTION_DECL_PLACEHOLDER (c) = decl_placeholder;
		  DECL_ARTIFICIAL (decl_placeholder) = 1;
		  DECL_IGNORED_P (decl_placeholder) = 1;
		}
	      ಆದರೆ (ವೃಕ್ಷ_ADDRESSABLE (ವೃಕ್ಷ_VEC_ELT (list, 0)))
		c_mark_addressable (placeholder);
	      ಆದರೆ (ವೃಕ್ಷ_ADDRESSABLE (ವೃಕ್ಷ_VEC_ELT (list, 1)))
		c_mark_addressable (decl_placeholder ? decl_placeholder
				    : OMP_CLAUSE_DECL (c));
	      OMP_CLAUSE_REDUCTION_ವಿಲೀನ (c)
		= c_clone_omp_udr (ವೃಕ್ಷ_VEC_ELT (list, 2),
				   ವೃಕ್ಷ_VEC_ELT (list, 0),
				   ವೃಕ್ಷ_VEC_ELT (list, 1),
				   decl_placeholder ? decl_placeholder
				   : OMP_CLAUSE_DECL (c), placeholder);
	      OMP_CLAUSE_REDUCTION_ವಿಲೀನ (c)
		= build3_loc (OMP_CLAUSE_LOCATION (c), BIND_ಅಭಿವ್ಯಕ್ತಿ,
			      void_type_ಗಂಟು, NULL_ವೃಕ್ಷ,
			      OMP_CLAUSE_REDUCTION_ವಿಲೀನ (c), NULL_ವೃಕ್ಷ);
	      ವೃಕ್ಷ_SIDE_EFFECTS (OMP_CLAUSE_REDUCTION_ವಿಲೀನ (c)) = 1;
	      ಆದರೆ (ವೃಕ್ಷ_VEC_ಉದ್ದಳತೆ (list) == 6)
		{
		  ಆದರೆ (ವೃಕ್ಷ_ADDRESSABLE (ವೃಕ್ಷ_VEC_ELT (list, 3)))
		    c_mark_addressable (decl_placeholder ? decl_placeholder
					: OMP_CLAUSE_DECL (c));
		  ಆದರೆ (ವೃಕ್ಷ_ADDRESSABLE (ವೃಕ್ಷ_VEC_ELT (list, 4)))
		    c_mark_addressable (placeholder);
		  ವೃಕ್ಷ init = ವೃಕ್ಷ_VEC_ELT (list, 5);
		  ಆದರೆ (init == error_mark_ಗಂಟು)
		    init = DECL_INITIAL (ವೃಕ್ಷ_VEC_ELT (list, 3));
		  OMP_CLAUSE_REDUCTION_INIT (c)
		    = c_clone_omp_udr (init, ವೃಕ್ಷ_VEC_ELT (list, 4),
				       ವೃಕ್ಷ_VEC_ELT (list, 3),
				       decl_placeholder ? decl_placeholder
				       : OMP_CLAUSE_DECL (c), placeholder);
		  ಆದರೆ (ವೃಕ್ಷ_VEC_ELT (list, 5) == error_mark_ಗಂಟು)
		    {
		      ವೃಕ್ಷ v = decl_placeholder ? decl_placeholder : t;
		      OMP_CLAUSE_REDUCTION_INIT (c)
			= build2 (INIT_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (v), v,
				  OMP_CLAUSE_REDUCTION_INIT (c));
		    }
		  ಆದರೆ (walk_ವೃಕ್ಷ (&OMP_CLAUSE_REDUCTION_INIT (c),
				 c_ಕಂಡುಹಿಡಿ_omp_placeholder_r,
				 placeholder, ಖಾಲಿ))
		    OMP_CLAUSE_REDUCTION_OMP_ORIG_REF (c) = 1;
		}
	      ಇಲ್ಲದಿದ್ದರೆ
		{
		  ವೃಕ್ಷ init;
		  ವೃಕ್ಷ v = decl_placeholder ? decl_placeholder : t;
		  ಆದರೆ (AGGREGATE_TYPE_P (ವೃಕ್ಷ_TYPE (v)))
		    init = build_constructor (ವೃಕ್ಷ_TYPE (v), ಖಾಲಿ);
		  ಇಲ್ಲದಿದ್ದರೆ
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
	  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (t) == MEM_REF)
	    {
	      ಆದರೆ (TYPE_ಗಾತ್ರ_UNIT (ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_TYPE (t))) == NULL_ವೃಕ್ಷ
		  || ವೃಕ್ಷ_ಸಂಕೇತ (TYPE_ಗಾತ್ರ_UNIT (ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_TYPE (t))))
		     != INTEGER_CST)
		{
		  sorry ("variable length element type in array "
			 "%<reduction%> clause");
		  remove = ನಿಜ;
		  ನಿಲ್ಲಿಸು;
		}
	      t = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (t, 0);
	      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (t) == ಸೂಚಕ_PLUS_ಅಭಿವ್ಯಕ್ತಿ)
		t = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (t, 0);
	      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (t) == ADDR_ಅಭಿವ್ಯಕ್ತಿ)
		t = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (t, 0);
	    }
	  ಹೋಗು check_dup_generic_t;

	ಸ್ಥಿತಿ OMP_CLAUSE_COPYPRIVATE:
	  copyprivate_ನೋಡಿದ = ನಿಜ;
	  ಆದರೆ (nowait_clause)
	    {
	      error_at (OMP_CLAUSE_LOCATION (*nowait_clause),
			"%<nowait%> clause must not be used together "
			"with %<copyprivate%> clause");
	      *nowait_clause = OMP_CLAUSE_CHAIN (*nowait_clause);
	      nowait_clause = ಖಾಲಿ;
	    }
	  ಹೋಗು check_dup_generic;

	ಸ್ಥಿತಿ OMP_CLAUSE_COPYIN:
	  t = OMP_CLAUSE_DECL (c);
	  ಆದರೆ (!VAR_P (t) || !DECL_THREAD_LOCAL_P (t))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE must be %<threadprivate%> for %<copyin%>", t);
	      remove = ನಿಜ;
	      ನಿಲ್ಲಿಸು;
	    }
	  ಹೋಗು check_dup_generic;

	ಸ್ಥಿತಿ OMP_CLAUSE_ರೇಖೀಯ:
	  ಆದರೆ (ort != C_ORT_OMP_DECLARE_SIMD)
	    need_implicitly_determined = ನಿಜ;
	  t = OMP_CLAUSE_DECL (c);
	  ಆದರೆ (ort != C_ORT_OMP_DECLARE_SIMD
	      && OMP_CLAUSE_ರೇಖೀಯ_ಬಗೆ (c) != OMP_CLAUSE_ರೇಖೀಯ_DEFAULT
	      && OMP_CLAUSE_ರೇಖೀಯ_OLD_ರೇಖೀಯ_MODIFIER (c))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"modifier should not be specified in %<linear%> "
			"clause on %<simd%> or %<for%> constructs when not "
			"using OpenMP 5.2 modifiers");
	      OMP_CLAUSE_ರೇಖೀಯ_ಬಗೆ (c) = OMP_CLAUSE_ರೇಖೀಯ_DEFAULT;
	    }
	  ಆದರೆ (!INTEGRAL_TYPE_P (ವೃಕ್ಷ_TYPE (t))
	      && ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (t)) != ಸೂಚಕ_TYPE)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"linear clause applied to non-integral non-pointer "
			"variable with type %qT", ವೃಕ್ಷ_TYPE (t));
	      remove = ನಿಜ;
	      ನಿಲ್ಲಿಸು;
	    }
	  ಆದರೆ (TYPE_ATOMIC (ವೃಕ್ಷ_TYPE (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<_Atomic%> %qD in %<linear%> clause", t);
	      remove = ನಿಜ;
	      ನಿಲ್ಲಿಸು;
	    }
	  ಆದರೆ (ort == C_ORT_OMP_DECLARE_SIMD)
	    {
	      ವೃಕ್ಷ s = OMP_CLAUSE_ರೇಖೀಯ_ಹೆಜ್ಜೆ (c);
	      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (s) == PARM_DECL)
		{
		  OMP_CLAUSE_ರೇಖೀಯ_VARIABLE_STRIDE (c) = 1;
		  /* map_head bitmap is used as uniform_head if
		     declare_simd.  */
		  ಆದರೆ (!bitmap_ಬಿಟ್_p (&map_ತಲೆ, DECL_UID (s)))
		    ರೇಖೀಯ_variable_ಹೆಜ್ಜೆ_check = ನಿಜ;
		  ಹೋಗು check_dup_generic;
		}
	      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (s) != INTEGER_CST)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%<linear%> clause step %qE is neither constant "
			    "nor a parameter", s);
		  remove = ನಿಜ;
		  ನಿಲ್ಲಿಸು;
		}
	    }
	  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (OMP_CLAUSE_DECL (c))) == ಸೂಚಕ_TYPE)
	    {
	      ವೃಕ್ಷ s = OMP_CLAUSE_ರೇಖೀಯ_ಹೆಜ್ಜೆ (c);
	      s = ಸೂಚಕ_int_ಮೊತ್ತ (OMP_CLAUSE_LOCATION (c), PLUS_ಅಭಿವ್ಯಕ್ತಿ,
				   OMP_CLAUSE_DECL (c), s);
	      s = fold_build2_loc (OMP_CLAUSE_LOCATION (c), MINUS_ಅಭಿವ್ಯಕ್ತಿ,
				   sizetype, fold_convert (sizetype, s),
				   fold_convert
				     (sizetype, OMP_CLAUSE_DECL (c)));
	      ಆದರೆ (s == error_mark_ಗಂಟು)
		s = ಗಾತ್ರ_one_ಗಂಟು;
	      OMP_CLAUSE_ರೇಖೀಯ_ಹೆಜ್ಜೆ (c) = s;
	    }
	  ಇಲ್ಲದಿದ್ದರೆ
	    OMP_CLAUSE_ರೇಖೀಯ_ಹೆಜ್ಜೆ (c)
	      = fold_convert (ವೃಕ್ಷ_TYPE (t), OMP_CLAUSE_ರೇಖೀಯ_ಹೆಜ್ಜೆ (c));
	  ಹೋಗು check_dup_generic;

	check_dup_generic:
	  t = OMP_CLAUSE_DECL (c);
	check_dup_generic_t:
	  ಆದರೆ (!VAR_P (t) && ವೃಕ್ಷ_ಸಂಕೇತ (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in clause %qs", t,
			omp_clause_ಸಂಕೇತ_name[OMP_CLAUSE_ಸಂಕೇತ (c)]);
	      remove = ನಿಜ;
	    }
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ ((openacc && OMP_CLAUSE_ಸಂಕೇತ (c) == OMP_CLAUSE_REDUCTION)
		   || (ort == C_ORT_OMP
		       && (OMP_CLAUSE_ಸಂಕೇತ (c) == OMP_CLAUSE_USE_DEVICE_PTR
			   || (OMP_CLAUSE_ಸಂಕೇತ (c)
			       == OMP_CLAUSE_USE_DEVICE_ADDR)))
		   || (ort == C_ORT_OMP_ಗುರಿ
		       && OMP_CLAUSE_ಸಂಕೇತ (c) == OMP_CLAUSE_ಒಳ_REDUCTION))
	    {
	      ಆದರೆ (OMP_CLAUSE_ಸಂಕೇತ (c) == OMP_CLAUSE_ಒಳ_REDUCTION
		  && (bitmap_ಬಿಟ್_p (&generic_ತಲೆ, DECL_UID (t))
		      || bitmap_ಬಿಟ್_p (&firstprivate_ತಲೆ, DECL_UID (t))))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD appears more than once in data-sharing "
			    "clauses", t);
		  remove = ನಿಜ;
		  ನಿಲ್ಲಿಸು;
		}
	      ಆದರೆ (OMP_CLAUSE_ಸಂಕೇತ (c) == OMP_CLAUSE_ಒಳ_REDUCTION)
		ಗುರಿ_ಒಳ_reduction_ನೋಡಿದ = ನಿಜ;
	      ಆದರೆ (bitmap_ಬಿಟ್_p (&oacc_reduction_ತಲೆ, DECL_UID (t)))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    openacc
			    ? "%qD appears more than once in reduction clauses"
			    : "%qD appears more than once in data clauses",
			    t);
		  remove = ನಿಜ;
		}
	      ಇಲ್ಲದಿದ್ದರೆ
		bitmap_ಗಣ_ಬಿಟ್ (&oacc_reduction_ತಲೆ, DECL_UID (t));
	    }
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (bitmap_ಬಿಟ್_p (&generic_ತಲೆ, DECL_UID (t))
		   || bitmap_ಬಿಟ್_p (&firstprivate_ತಲೆ, DECL_UID (t))
		   || bitmap_ಬಿಟ್_p (&lastprivate_ತಲೆ, DECL_UID (t))
		   || bitmap_ಬಿಟ್_p (&map_firstprivate_ತಲೆ, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE appears more than once in data clauses", t);
	      remove = ನಿಜ;
	    }
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ ((OMP_CLAUSE_ಸಂಕೇತ (c) == OMP_CLAUSE_ಖಾಸಗಿ
		    || OMP_CLAUSE_ಸಂಕೇತ (c) == OMP_CLAUSE_HAS_DEVICE_ADDR
		    || OMP_CLAUSE_ಸಂಕೇತ (c) == OMP_CLAUSE_IS_DEVICE_PTR)
		   && bitmap_ಬಿಟ್_p (&map_ತಲೆ, DECL_UID (t)))
	    {
	      ಆದರೆ (openacc)
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD appears more than once in data clauses", t);
	      ಇಲ್ಲದಿದ್ದರೆ
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD appears both in data and map clauses", t);
	      remove = ನಿಜ;
	    }
	  ಇಲ್ಲದಿದ್ದರೆ
	    bitmap_ಗಣ_ಬಿಟ್ (&generic_ತಲೆ, DECL_UID (t));
	  ನಿಲ್ಲಿಸು;

	ಸ್ಥಿತಿ OMP_CLAUSE_FIRSTPRIVATE:
	  ಆದರೆ (OMP_CLAUSE_FIRSTPRIVATE_IMPLICIT (c) && !implicit_moved)
	    {
	    move_implicit:
	      implicit_moved = ನಿಜ;
	      /* Move firstprivate and map clauses with
		 OMP_CLAUSE_{FIRSTPRIVATE,MAP}_IMPLICIT set to the end of
		 clauses chain.  */
	      ವೃಕ್ಷ cl1 = NULL_ವೃಕ್ಷ, cl2 = NULL_ವೃಕ್ಷ;
	      ವೃಕ್ಷ *pc1 = pc, *pc2 = &cl1, *pc3 = &cl2;
	      ಆಗ (*pc1)
		ಆದರೆ (OMP_CLAUSE_ಸಂಕೇತ (*pc1) == OMP_CLAUSE_FIRSTPRIVATE
		    && OMP_CLAUSE_FIRSTPRIVATE_IMPLICIT (*pc1))
		  {
		    *pc3 = *pc1;
		    pc3 = &OMP_CLAUSE_CHAIN (*pc3);
		    *pc1 = OMP_CLAUSE_CHAIN (*pc1);
		  }
		ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (OMP_CLAUSE_ಸಂಕೇತ (*pc1) == OMP_CLAUSE_MAP
			 && OMP_CLAUSE_MAP_IMPLICIT (*pc1))
		  {
		    *pc2 = *pc1;
		    pc2 = &OMP_CLAUSE_CHAIN (*pc2);
		    *pc1 = OMP_CLAUSE_CHAIN (*pc1);
		  }
		ಇಲ್ಲದಿದ್ದರೆ
		  pc1 = &OMP_CLAUSE_CHAIN (*pc1);
	      *pc3 = ಖಾಲಿ;
	      *pc2 = cl2;
	      *pc1 = cl1;
	      ಮುಂದುವರಿ;
	    }
	  t = OMP_CLAUSE_DECL (c);
	  need_complete = ನಿಜ;
	  need_implicitly_determined = ನಿಜ;
	  ಆದರೆ (!VAR_P (t) && ವೃಕ್ಷ_ಸಂಕೇತ (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in clause %<firstprivate%>", t);
	      remove = ನಿಜ;
	    }
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (OMP_CLAUSE_FIRSTPRIVATE_IMPLICIT (c)
		   && !OMP_CLAUSE_FIRSTPRIVATE_IMPLICIT_ಗುರಿ (c)
		   && bitmap_ಬಿಟ್_p (&map_firstprivate_ತಲೆ, DECL_UID (t)))
	    remove = ನಿಜ;
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (bitmap_ಬಿಟ್_p (&generic_ತಲೆ, DECL_UID (t))
		   || bitmap_ಬಿಟ್_p (&firstprivate_ತಲೆ, DECL_UID (t))
		   || bitmap_ಬಿಟ್_p (&map_firstprivate_ತಲೆ, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE appears more than once in data clauses", t);
	      remove = ನಿಜ;
	    }
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (bitmap_ಬಿಟ್_p (&map_ತಲೆ, DECL_UID (t))
		   || bitmap_ಬಿಟ್_p (&map_ಕ್ಷೇತ್ರ_ತಲೆ, DECL_UID (t)))
	    {
	      ಆದರೆ (openacc)
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD appears more than once in data clauses", t);
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (OMP_CLAUSE_FIRSTPRIVATE_IMPLICIT (c)
		       && !OMP_CLAUSE_FIRSTPRIVATE_IMPLICIT_ಗುರಿ (c))
		/* Silently drop the clause.  */;
	      ಇಲ್ಲದಿದ್ದರೆ
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD appears both in data and map clauses", t);
	      remove = ನಿಜ;
	    }
	  ಇಲ್ಲದಿದ್ದರೆ
	    bitmap_ಗಣ_ಬಿಟ್ (&firstprivate_ತಲೆ, DECL_UID (t));
	  ನಿಲ್ಲಿಸು;

	ಸ್ಥಿತಿ OMP_CLAUSE_LASTPRIVATE:
	  t = OMP_CLAUSE_DECL (c);
	  need_complete = ನಿಜ;
	  need_implicitly_determined = ನಿಜ;
	  ಆದರೆ (!VAR_P (t) && ವೃಕ್ಷ_ಸಂಕೇತ (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in clause %<lastprivate%>", t);
	      remove = ನಿಜ;
	    }
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (bitmap_ಬಿಟ್_p (&generic_ತಲೆ, DECL_UID (t))
		   || bitmap_ಬಿಟ್_p (&lastprivate_ತಲೆ, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
		     "%qE appears more than once in data clauses", t);
	      remove = ನಿಜ;
	    }
	  ಇಲ್ಲದಿದ್ದರೆ
	    bitmap_ಗಣ_ಬಿಟ್ (&lastprivate_ತಲೆ, DECL_UID (t));
	  ನಿಲ್ಲಿಸು;

	ಸ್ಥಿತಿ OMP_CLAUSE_ALIGNED:
	  t = OMP_CLAUSE_DECL (c);
	  ಆದರೆ (!VAR_P (t) && ವೃಕ್ಷ_ಸಂಕೇತ (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in %<aligned%> clause", t);
	      remove = ನಿಜ;
	    }
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!ಸೂಚಕ_TYPE_P (ವೃಕ್ಷ_TYPE (t))
		   && ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (t)) != ARRAY_TYPE)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE in %<aligned%> clause is neither a pointer nor "
			"an array", t);
	      remove = ನಿಜ;
	    }
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (TYPE_ATOMIC (ವೃಕ್ಷ_TYPE (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<_Atomic%> %qD in %<aligned%> clause", t);
	      remove = ನಿಜ;
	      ನಿಲ್ಲಿಸು;
	    }
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (bitmap_ಬಿಟ್_p (&aligned_ತಲೆ, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE appears more than once in %<aligned%> clauses",
			t);
	      remove = ನಿಜ;
	    }
	  ಇಲ್ಲದಿದ್ದರೆ
	    bitmap_ಗಣ_ಬಿಟ್ (&aligned_ತಲೆ, DECL_UID (t));
	  ನಿಲ್ಲಿಸು;

	ಸ್ಥಿತಿ OMP_CLAUSE_NONTEMPORAL:
	  t = OMP_CLAUSE_DECL (c);
	  ಆದರೆ (!VAR_P (t) && ವೃಕ್ಷ_ಸಂಕೇತ (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in %<nontemporal%> clause", t);
	      remove = ನಿಜ;
	    }
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (bitmap_ಬಿಟ್_p (&oacc_reduction_ತಲೆ, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE appears more than once in %<nontemporal%> "
			"clauses", t);
	      remove = ನಿಜ;
	    }
	  ಇಲ್ಲದಿದ್ದರೆ
	    bitmap_ಗಣ_ಬಿಟ್ (&oacc_reduction_ತಲೆ, DECL_UID (t));
	  ನಿಲ್ಲಿಸು;

	ಸ್ಥಿತಿ OMP_CLAUSE_ALLOCATE:
	  t = OMP_CLAUSE_DECL (c);
	  ಆದರೆ (!VAR_P (t) && ವೃಕ್ಷ_ಸಂಕೇತ (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in %<allocate%> clause", t);
	      remove = ನಿಜ;
	    }
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (bitmap_ಬಿಟ್_p (&aligned_ತಲೆ, DECL_UID (t)))
	    {
	      warning_at (OMP_CLAUSE_LOCATION (c), OPT_Wopenmp,
			  "%qE appears more than once in %<allocate%> clauses",
			  t);
	      remove = ನಿಜ;
	    }
	  ಇಲ್ಲದಿದ್ದರೆ
	    {
	      bitmap_ಗಣ_ಬಿಟ್ (&aligned_ತಲೆ, DECL_UID (t));
	      ಆದರೆ (!OMP_CLAUSE_ALLOCATE_COMBINED (c))
		allocate_ನೋಡಿದ = ನಿಜ;
	    }
	  ನಿಲ್ಲಿಸು;

	ಸ್ಥಿತಿ OMP_CLAUSE_DOACROSS:
	  t = OMP_CLAUSE_DECL (c);
	  ಆದರೆ (t == NULL_ವೃಕ್ಷ)
	    ನಿಲ್ಲಿಸು;
	  ಆದರೆ (OMP_CLAUSE_DOACROSS_ಬಗೆ (c) == OMP_CLAUSE_DOACROSS_SINK)
	    {
	      gcc_assert (ವೃಕ್ಷ_ಸಂಕೇತ (t) == ವೃಕ್ಷ_LIST);
	      ಗಾಗಿ (; t; t = ವೃಕ್ಷ_CHAIN (t))
		{
		  ವೃಕ್ಷ decl = ವೃಕ್ಷ_ಮೌಲ್ಯ (t);
		  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (decl)) == ಸೂಚಕ_TYPE)
		    {
		      ವೃಕ್ಷ ಸ್ಥಾನಾಂತರ = ವೃಕ್ಷ_PURPOSE (t);
		      ತಾರ್ಕಿಕ neg = wi::neg_p (wi::ಗಮ್ಯ_wide (ಸ್ಥಾನಾಂತರ));
		      ಸ್ಥಾನಾಂತರ = fold_unary (ABS_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (ಸ್ಥಾನಾಂತರ), ಸ್ಥಾನಾಂತರ);
		      ವೃಕ್ಷ t2 = ಸೂಚಕ_int_ಮೊತ್ತ (OMP_CLAUSE_LOCATION (c),
						 neg ? MINUS_ಅಭಿವ್ಯಕ್ತಿ : PLUS_ಅಭಿವ್ಯಕ್ತಿ,
						 decl, ಸ್ಥಾನಾಂತರ);
		      t2 = fold_build2_loc (OMP_CLAUSE_LOCATION (c), MINUS_ಅಭಿವ್ಯಕ್ತಿ,
					    sizetype,
					    fold_convert (sizetype, t2),
					    fold_convert (sizetype, decl));
		      ಆದರೆ (t2 == error_mark_ಗಂಟು)
			{
			  remove = ನಿಜ;
			  ನಿಲ್ಲಿಸು;
			}
		      ವೃಕ್ಷ_PURPOSE (t) = t2;
		    }
		}
	      ನಿಲ್ಲಿಸು;
	    }
	  gcc_unreachable ();

	ಸ್ಥಿತಿ OMP_CLAUSE_ಬಳಸುತ್ತದೆ_ALLOCATORS:
	  t = OMP_CLAUSE_ಬಳಸುತ್ತದೆ_ALLOCATORS_ALLOCATOR (c);
	  ಆದರೆ (t == error_mark_ಗಂಟು)
	    {
	      remove = ನಿಜ;
	      ನಿಲ್ಲಿಸು;
	    }
	  ಆದರೆ ((VAR_P (t) || ವೃಕ್ಷ_ಸಂಕೇತ (t) == PARM_DECL)
	      && (bitmap_ಬಿಟ್_p (&generic_ತಲೆ, DECL_UID (t))
		  || bitmap_ಬಿಟ್_p (&map_ತಲೆ, DECL_UID (t))
		  || bitmap_ಬಿಟ್_p (&firstprivate_ತಲೆ, DECL_UID (t))
		  || bitmap_ಬಿಟ್_p (&lastprivate_ತಲೆ, DECL_UID (t))))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE appears more than once in data clauses", t);
	      remove = ನಿಜ;
	      ನಿಲ್ಲಿಸು;
	    }
	  ಇಲ್ಲದಿದ್ದರೆ
	    bitmap_ಗಣ_ಬಿಟ್ (&generic_ತಲೆ, DECL_UID (t));
	  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (t)) != ENUMERAL_TYPE
	      || strcmp (IDENTIFIER_ಸೂಚಕ (TYPE_IDENTIFIER (ವೃಕ್ಷ_TYPE (t))),
			 "omp_allocator_handle_t") != 0)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"allocator %qE must be of %<omp_allocator_handle_t%> "
			"type", t);
	      remove = ನಿಜ;
	      ನಿಲ್ಲಿಸು;
	    }
	  ವೃಕ್ಷ init;
	  ಆದರೆ (!DECL_P (t)
	      || (ವೃಕ್ಷ_ಸಂಕೇತ (t) == CONST_DECL
		  && ((init = DECL_INITIAL(t)) == ಶೂನ್ಯಸೂಚಕ
		      || ವೃಕ್ಷ_ಸಂಕೇತ (init) != INTEGER_CST
		      || ((wi::ಗಮ್ಯ_widest (init) < 0
			   || wi::ಗಮ್ಯ_widest (init) > GOMP_OMP_PREDEF_ALLOC_MAX)
			  && (wi::ಗಮ್ಯ_widest (init) < GOMP_OMPX_PREDEF_ALLOC_MIN
			      || (wi::ಗಮ್ಯ_widest (init)
				  > GOMP_OMPX_PREDEF_ALLOC_MAX))))))
	    {
	      remove = ನಿಜ;
	      error_at (OMP_CLAUSE_LOCATION (c),
			"allocator %qE must be either a variable or a "
			"predefined allocator", t);
	      ನಿಲ್ಲಿಸು;
	    }
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (t) == CONST_DECL)
	    {
	      /* omp_null_allocator is ignored and for predefined allocators,
		 no special handling is required; thus, mark them removed. */
	      remove = ನಿಜ;

	      ಆದರೆ (OMP_CLAUSE_ಬಳಸುತ್ತದೆ_ALLOCATORS_MEMSPACE (c)
		  || OMP_CLAUSE_ಬಳಸುತ್ತದೆ_ALLOCATORS_TRAITS (c))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "modifiers cannot be used with predefined "
			    "allocator %qE", t);
		  ನಿಲ್ಲಿಸು;
		}
	    }
	  t = OMP_CLAUSE_ಬಳಸುತ್ತದೆ_ALLOCATORS_MEMSPACE (c);
	  ಆದರೆ (t == error_mark_ಗಂಟು)
	    {
	      remove = ನಿಜ;
	      ನಿಲ್ಲಿಸು;
	    }
	  ಆದರೆ (t != NULL_ವೃಕ್ಷ
	      && ((ವೃಕ್ಷ_ಸಂಕೇತ (t) != CONST_DECL && ವೃಕ್ಷ_ಸಂಕೇತ (t) != INTEGER_CST)
		  || ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (t)) != ENUMERAL_TYPE
		  || strcmp (IDENTIFIER_ಸೂಚಕ (TYPE_IDENTIFIER (ವೃಕ್ಷ_TYPE (t))),
			     "omp_memspace_handle_t") != 0))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c), "memspace modifier %qE must be"
			" constant enum of %<omp_memspace_handle_t%> type", t);
	      remove = ನಿಜ;
	      ನಿಲ್ಲಿಸು;
	    }
	  t = OMP_CLAUSE_ಬಳಸುತ್ತದೆ_ALLOCATORS_TRAITS (c);
	  ಆದರೆ (t == error_mark_ಗಂಟು)
	    {
	      remove = ನಿಜ;
	      ನಿಲ್ಲಿಸು;
	    }
	  ಆದರೆ (t != NULL_ವೃಕ್ಷ
	      && t != error_mark_ಗಂಟು
	      && (DECL_EXTERNAL (t)
		  || ವೃಕ್ಷ_ಸಂಕೇತ (t) == PARM_DECL))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c), "traits array %qE must be "
			"defined in same scope as the construct on which the "
			"clause appears", t);
	      remove = ನಿಜ;
	    }
	  ಆದರೆ (t != NULL_ವೃಕ್ಷ)
	    {
	      ತಾರ್ಕಿಕ type_err = ಸುಳ್ಳು;

	      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (t)) != ARRAY_TYPE
		  || DECL_ಗಾತ್ರ (t) == NULL_ವೃಕ್ಷ
		  || !COMPLETE_TYPE_P (ವೃಕ್ಷ_TYPE (t)))
		type_err = ನಿಜ;
	      ಇಲ್ಲದಿದ್ದರೆ
		{
		  ವೃಕ್ಷ elem_t = ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_TYPE (t));
		  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (elem_t) != ದಾಖಲೆ_TYPE
		      || strcmp (IDENTIFIER_ಸೂಚಕ (TYPE_IDENTIFIER (elem_t)),
				 "omp_alloctrait_t") != 0
		      || !TYPE_READONLY (elem_t))
		    type_err = ನಿಜ;
		}
	      ಆದರೆ (type_err)
		{
		  ಆದರೆ (t != error_mark_ಗಂಟು)
		    error_at (OMP_CLAUSE_LOCATION (c), "traits array %qE must "
			      "be of %<const omp_alloctrait_t []%> type", t);
		  ಇಲ್ಲದಿದ್ದರೆ
		    error_at (OMP_CLAUSE_LOCATION (c), "traits array must "
			      "be of %<const omp_alloctrait_t []%> type");
		  remove = ನಿಜ;
		}
	      ಇಲ್ಲದಿದ್ದರೆ
		{
		  ವೃಕ್ಷ cst_val = decl_constant_ಮೌಲ್ಯ_1 (t, ನಿಜ);
		  ಆದರೆ (cst_val == t)
		    {
		      error_at (OMP_CLAUSE_LOCATION (c), "traits array must be "
				"initialized with constants");

		      remove = ನಿಜ;
		    }
		}
	    }
	  ಆದರೆ (remove)
	    ನಿಲ್ಲಿಸು;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  ಮುಂದುವರಿ;
	ಸ್ಥಿತಿ OMP_CLAUSE_DEPEND:
	  depend_clause = c;
	  /* FALLTHRU */
	ಸ್ಥಿತಿ OMP_CLAUSE_AFFINITY:
	  t = OMP_CLAUSE_DECL (c);
	  ಆದರೆ (OMP_ITERATOR_DECL_P (t))
	    {
	      ಆದರೆ (ವೃಕ್ಷ_PURPOSE (t) != ಕೊನೆಯ_iterators)
		ಕೊನೆಯ_iterators_remove
		  = c_omp_ಮುಕ್ತಾಯ_iterators (ವೃಕ್ಷ_PURPOSE (t));
	      ಕೊನೆಯ_iterators = ವೃಕ್ಷ_PURPOSE (t);
	      t = ವೃಕ್ಷ_ಮೌಲ್ಯ (t);
	      ಆದರೆ (ಕೊನೆಯ_iterators_remove)
		t = error_mark_ಗಂಟು;
	    }
	  ಇಲ್ಲದಿದ್ದರೆ
	    ಕೊನೆಯ_iterators = NULL_ವೃಕ್ಷ;
	  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (t) == OMP_ARRAY_SECTION)
	    {
	      ಆದರೆ (handle_omp_array_sections (c, ort))
		remove = ನಿಜ;
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (OMP_CLAUSE_ಸಂಕೇತ (c) == OMP_CLAUSE_DEPEND
		       && OMP_CLAUSE_DEPEND_ಬಗೆ (c) == OMP_CLAUSE_DEPEND_DEPOBJ)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%<depend%> clause with %<depobj%> dependence "
			    "type on array section");
		  remove = ನಿಜ;
		}
	      ನಿಲ್ಲಿಸು;
	    }
	  ಆದರೆ (t == error_mark_ಗಂಟು)
	    remove = ನಿಜ;
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (OMP_CLAUSE_ಸಂಕೇತ (c) == OMP_CLAUSE_DEPEND
		   && t == ridpointers[RID_OMP_ALL_ಸ್ಮರಣೆ])
	    {
	      ಆದರೆ (OMP_CLAUSE_DEPEND_ಬಗೆ (c) != OMP_CLAUSE_DEPEND_ಹೊರಹೋಗು
		  && OMP_CLAUSE_DEPEND_ಬಗೆ (c) != OMP_CLAUSE_DEPEND_INOUT)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%<omp_all_memory%> used with %<depend%> kind "
			    "other than %<out%> or %<inout%>");
		  remove = ನಿಜ;
		}
	    }
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!lvalue_p (t))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not lvalue expression nor array section in "
			"%qs clause", t,
			omp_clause_ಸಂಕೇತ_name[OMP_CLAUSE_ಸಂಕೇತ (c)]);
	      remove = ನಿಜ;
	    }
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (t) == COMPONENT_REF
		   && DECL_C_ಬಿಟ್_ಕ್ಷೇತ್ರ (ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (t, 1)))
	    {
	      gcc_assert (OMP_CLAUSE_ಸಂಕೇತ (c) == OMP_CLAUSE_DEPEND
			  || OMP_CLAUSE_ಸಂಕೇತ (c) == OMP_CLAUSE_AFFINITY);
	      error_at (OMP_CLAUSE_LOCATION (c),
			"bit-field %qE in %qs clause", t,
			omp_clause_ಸಂಕೇತ_name[OMP_CLAUSE_ಸಂಕೇತ (c)]);
	      remove = ನಿಜ;
	    }
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (OMP_CLAUSE_ಸಂಕೇತ (c) == OMP_CLAUSE_DEPEND
		   && OMP_CLAUSE_DEPEND_ಬಗೆ (c) == OMP_CLAUSE_DEPEND_DEPOBJ)
	    {
	      ಆದರೆ (!c_omp_depend_t_p (ವೃಕ್ಷ_TYPE (t)))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qE does not have %<omp_depend_t%> type in "
			    "%<depend%> clause with %<depobj%> dependence "
			    "type", t);
		  remove = ನಿಜ;
		}
	    }
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (OMP_CLAUSE_ಸಂಕೇತ (c) == OMP_CLAUSE_DEPEND
		   && c_omp_depend_t_p (ವೃಕ್ಷ_TYPE (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE should not have %<omp_depend_t%> type in "
			"%<depend%> clause with dependence type other than "
			"%<depobj%>", t);
	      remove = ನಿಜ;
	    }
	  ಆದರೆ (!remove)
	    {
	      ಆದರೆ (t == ridpointers[RID_OMP_ALL_ಸ್ಮರಣೆ])
		t = null_ಸೂಚಕ_ಗಂಟು;
	      ಇಲ್ಲದಿದ್ದರೆ
		{
		  ವೃಕ್ಷ addr = build_unary_op (OMP_CLAUSE_LOCATION (c),
					      ADDR_ಅಭಿವ್ಯಕ್ತಿ, t, ಸುಳ್ಳು);
		  ಆದರೆ (addr == error_mark_ಗಂಟು)
		    {
		      remove = ನಿಜ;
		      ನಿಲ್ಲಿಸು;
		    }
		  t = build_ಪರೋಕ್ಷ_ref (OMP_CLAUSE_LOCATION (c), addr,
					  RO_UNARY_ನಕ್ಷತ್ರ);
		  ಆದರೆ (t == error_mark_ಗಂಟು)
		    {
		      remove = ನಿಜ;
		      ನಿಲ್ಲಿಸು;
		    }
		}
	      ಆದರೆ (OMP_ITERATOR_DECL_P (OMP_CLAUSE_DECL (c)))
		ವೃಕ್ಷ_ಮೌಲ್ಯ (OMP_CLAUSE_DECL (c)) = t;
	      ಇಲ್ಲದಿದ್ದರೆ
		OMP_CLAUSE_DECL (c) = t;
	    }
	  ನಿಲ್ಲಿಸು;

	ಸ್ಥಿತಿ OMP_CLAUSE_MAP:
	  ಆದರೆ (OMP_CLAUSE_MAP_IMPLICIT (c) && !implicit_moved)
	    ಹೋಗು move_implicit;
	  ಆದರೆ (OMP_CLAUSE_MAP_ಬಗೆ (c) == GOMP_MAP_ತಳ್ಳು_MAPPER_NAME
	      || OMP_CLAUSE_MAP_ಬಗೆ (c) == GOMP_MAP_ತೆಗೆ_MAPPER_NAME)
	    {
	      remove = ನಿಜ;
	      ನಿಲ್ಲಿಸು;
	    }
	  /* FALLTHRU */
	ಸ್ಥಿತಿ OMP_CLAUSE_ಗಮ್ಯ:
	ಸ್ಥಿತಿ OMP_CLAUSE_FROM:
	  ಆದರೆ (OMP_CLAUSE_ITERATORS (c)
	      && c_omp_ಮುಕ್ತಾಯ_iterators (OMP_CLAUSE_ITERATORS (c)))
	    {
	      t = error_mark_ಗಂಟು;
	      ನಿಲ್ಲಿಸು;
	    }
	  /* FALLTHRU */
	ಸ್ಥಿತಿ OMP_CLAUSE__CACHE_:
	  {
	    ಬಳಸಿ ನಾಮಾಕಾಶ omp_addr_tokenizer;
	    auto_vec<omp_addr_token *, 10> addr_ಟೋಕನುಗಳು;

	    t = OMP_CLAUSE_DECL (c);
	    ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (t) == OMP_ARRAY_SECTION)
	      {
		grp_ಆರಂಭ_p = pc;
		grp_sentinel = OMP_CLAUSE_CHAIN (c);

		ಆದರೆ (handle_omp_array_sections (c, ort))
		  remove = ನಿಜ;
		ಇಲ್ಲದಿದ್ದರೆ
		  {
		    t = OMP_CLAUSE_DECL (c);
		    ಆದರೆ (!omp_mappable_type (ವೃಕ್ಷ_TYPE (t)))
		      {
			error_at (OMP_CLAUSE_LOCATION (c),
				  "array section does not have mappable type "
				  "in %qs clause",
				  omp_clause_ಸಂಕೇತ_name[OMP_CLAUSE_ಸಂಕೇತ (c)]);
			remove = ನಿಜ;
		      }
		    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (TYPE_ATOMIC (ವೃಕ್ಷ_TYPE (t)))
		      {
			error_at (OMP_CLAUSE_LOCATION (c),
				  "%<_Atomic%> %qE in %qs clause", t,
				  omp_clause_ಸಂಕೇತ_name[OMP_CLAUSE_ಸಂಕೇತ (c)]);
			remove = ನಿಜ;
		      }
		    ಆಗ (ವೃಕ್ಷ_ಸಂಕೇತ (t) == ARRAY_REF)
		      t = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (t, 0);

		    c_omp_ವಿಳಾಸ_inspector ai (OMP_CLAUSE_LOCATION (c), t);

		    ಆದರೆ (!omp_parse_ಅಭಿವ್ಯಕ್ತಿ (addr_ಟೋಕನುಗಳು, t))
		      {
			sorry_at (OMP_CLAUSE_LOCATION (c),
				  "unsupported map expression %qE",
				  OMP_CLAUSE_DECL (c));
			remove = ನಿಜ;
			ನಿಲ್ಲಿಸು;
		      }

		    /* This check is to determine if this will be the only map
		       node created for this clause.  Otherwise, we'll check
		       the following FIRSTPRIVATE_POINTER or ATTACH_DETACH
		       node on the next iteration(s) of the loop.   */
		    ಆದರೆ (addr_ಟೋಕನುಗಳು.ಉದ್ದಳತೆ () >= 4
			&& addr_ಟೋಕನುಗಳು[0]->type == STRUCTURE_ತಳ
			&& addr_ಟೋಕನುಗಳು[0]->u.structure_ತಳ_ಬಗೆ == ತಳ_DECL
			&& addr_ಟೋಕನುಗಳು[1]->type == ACCESS_ವಿಧಾನ
			&& addr_ಟೋಕನುಗಳು[2]->type == COMPONENT_SELECTOR
			&& addr_ಟೋಕನುಗಳು[3]->type == ACCESS_ವಿಧಾನ
			&& (addr_ಟೋಕನುಗಳು[3]->u.access_ಬಗೆ == ACCESS_ನೇರ
			    || (addr_ಟೋಕನುಗಳು[3]->u.access_ಬಗೆ
				== ACCESS_ಸೂಚ್ಯಂಕಿತ_ARRAY)))
		      {
			ವೃಕ್ಷ rt = addr_ಟೋಕನುಗಳು[1]->ಅಭಿವ್ಯಕ್ತಿ;

			gcc_assert (DECL_P (rt));

			ಆದರೆ (OMP_CLAUSE_ಸಂಕೇತ (c) == OMP_CLAUSE_MAP
			    && OMP_CLAUSE_MAP_IMPLICIT (c)
			    && (bitmap_ಬಿಟ್_p (&map_ತಲೆ, DECL_UID (rt))
				|| bitmap_ಬಿಟ್_p (&map_ಕ್ಷೇತ್ರ_ತಲೆ, DECL_UID (rt))
				|| bitmap_ಬಿಟ್_p (&map_firstprivate_ತಲೆ,
						 DECL_UID (rt))))
			  {
			    remove = ನಿಜ;
			    ನಿಲ್ಲಿಸು;
			  }
			ಆದರೆ (bitmap_ಬಿಟ್_p (&map_ಕ್ಷೇತ್ರ_ತಲೆ, DECL_UID (rt)))
			  ನಿಲ್ಲಿಸು;
			ಆದರೆ (bitmap_ಬಿಟ್_p (&map_ತಲೆ, DECL_UID (rt)))
			  {
			    ಆದರೆ (OMP_CLAUSE_ಸಂಕೇತ (c) != OMP_CLAUSE_MAP)
			      error_at (OMP_CLAUSE_LOCATION (c),
					"%qD appears more than once in motion "
					"clauses", rt);
			    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (openacc)
			      error_at (OMP_CLAUSE_LOCATION (c),
					"%qD appears more than once in data "
					"clauses", rt);
			    ಇಲ್ಲದಿದ್ದರೆ
			      error_at (OMP_CLAUSE_LOCATION (c),
					"%qD appears more than once in map "
					"clauses", rt);
			    remove = ನಿಜ;
			  }
			ಇಲ್ಲದಿದ್ದರೆ
			  {
			    bitmap_ಗಣ_ಬಿಟ್ (&map_ತಲೆ, DECL_UID (rt));
			    bitmap_ಗಣ_ಬಿಟ್ (&map_ಕ್ಷೇತ್ರ_ತಲೆ, DECL_UID (rt));
			  }
		      }
		  }
		ಆದರೆ (c_oacc_check_attachments (c))
		  remove = ನಿಜ;
		ಆದರೆ (OMP_CLAUSE_ಸಂಕೇತ (c) == OMP_CLAUSE_MAP
		    && (OMP_CLAUSE_MAP_ಬಗೆ (c) == GOMP_MAP_ATTACH
			|| OMP_CLAUSE_MAP_ಬಗೆ (c) == GOMP_MAP_DETACH)
		    && !OMP_CLAUSE_ಗಾತ್ರ (c))
		  /* In this case, we have a single array element which is a
		     pointer, and we already set OMP_CLAUSE_SIZE in
		     handle_omp_array_sections above.  For attach/detach
		     clauses, reset the OMP_CLAUSE_SIZE (representing a bias)
		     to zero here.  */
		  OMP_CLAUSE_ಗಾತ್ರ (c) = ಗಾತ್ರ_zero_ಗಂಟು;
		ನಿಲ್ಲಿಸು;
	      }
	    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!omp_parse_ಅಭಿವ್ಯಕ್ತಿ (addr_ಟೋಕನುಗಳು, t))
	      {
		sorry_at (OMP_CLAUSE_LOCATION (c),
			  "unsupported map expression %qE",
			  OMP_CLAUSE_DECL (c));
		remove = ನಿಜ;
		ನಿಲ್ಲಿಸು;
	      }
	    ಆದರೆ (t == error_mark_ಗಂಟು)
	      {
		remove = ನಿಜ;
		ನಿಲ್ಲಿಸು;
	      }

	    ವೃಕ್ಷ attr;
	    ಆದರೆ (DECL_P (t)
		&& OMP_CLAUSE_ಸಂಕೇತ (c) == OMP_CLAUSE_MAP
		&& (attr = lookup_attribute ("omp declare target",
					     DECL_ಗುಣಲಕ್ಷಣಗಳು (t)))
		&& ಮೌಲ್ಯ_member (get_identifier ("local"),
				 ವೃಕ್ಷ_ಮೌಲ್ಯ (attr)))
	      {
		error_at (OMP_CLAUSE_LOCATION (c),
			  "device-local variable %qD cannot appear "
			  "in map clause", t);
		remove = ನಿಜ;
		ನಿಲ್ಲಿಸು;
	      }

	    /* OpenACC attach / detach clauses must be pointers.  */
	    ಆದರೆ (c_oacc_check_attachments (c))
	      {
		remove = ನಿಜ;
		ನಿಲ್ಲಿಸು;
	      }
	    ಆದರೆ (OMP_CLAUSE_ಸಂಕೇತ (c) == OMP_CLAUSE_MAP
		&& (OMP_CLAUSE_MAP_ಬಗೆ (c) == GOMP_MAP_ATTACH
		    || OMP_CLAUSE_MAP_ಬಗೆ (c) == GOMP_MAP_DETACH)
		&& !OMP_CLAUSE_ಗಾತ್ರ (c))
	      /* For attach/detach clauses, set OMP_CLAUSE_SIZE (representing a
		 bias) to zero here, so it is not set erroneously to the pointer
		 size later on in gimplify.cc.  */
	      OMP_CLAUSE_ಗಾತ್ರ (c) = ಗಾತ್ರ_zero_ಗಂಟು;

	    c_omp_ವಿಳಾಸ_inspector ai (OMP_CLAUSE_LOCATION (c), t);

	    ಆದರೆ (!ai.check_clause (c))
	      {
		remove = ನಿಜ;
		ನಿಲ್ಲಿಸು;
	      }

	    ಆದರೆ (!ai.map_supported_p ())
	      {
		sorry_at (OMP_CLAUSE_LOCATION (c),
			  "unsupported map expression %qE",
			  OMP_CLAUSE_DECL (c));
		remove = ನಿಜ;
		ನಿಲ್ಲಿಸು;
	      }

	    gcc_assert ((addr_ಟೋಕನುಗಳು[0]->type == ARRAY_ತಳ
			 || addr_ಟೋಕನುಗಳು[0]->type == STRUCTURE_ತಳ)
			&& addr_ಟೋಕನುಗಳು[1]->type == ACCESS_ವಿಧಾನ);

	    t = addr_ಟೋಕನುಗಳು[1]->ಅಭಿವ್ಯಕ್ತಿ;

	    ಆದರೆ (addr_ಟೋಕನುಗಳು[0]->u.structure_ತಳ_ಬಗೆ != ತಳ_DECL)
	      ಹೋಗು skip_decl_checks;

	    /* For OpenMP, we can access a struct "t" and "t.d" on the same
	       mapping.  OpenACC allows multiple fields of the same structure
	       to be written.  */
	    ಆದರೆ (addr_ಟೋಕನುಗಳು[0]->type == STRUCTURE_ತಳ
		&& (bitmap_ಬಿಟ್_p (&map_ಕ್ಷೇತ್ರ_ತಲೆ, DECL_UID (t))
		    || (!openacc && bitmap_ಬಿಟ್_p (&map_ತಲೆ, DECL_UID (t)))))
	      ಹೋಗು skip_decl_checks;

	    ಆದರೆ (!VAR_P (t) && ವೃಕ್ಷ_ಸಂಕೇತ (t) != PARM_DECL)
	      {
		ಆದರೆ (ort != C_ORT_ACC && ಅಭಿವ್ಯಕ್ತಿ_P (t))
		  ನಿಲ್ಲಿಸು;

		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qE is not a variable in %qs clause", t,
			  omp_clause_ಸಂಕೇತ_name[OMP_CLAUSE_ಸಂಕೇತ (c)]);
		remove = ನಿಜ;
	      }
	    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (VAR_P (t) && DECL_THREAD_LOCAL_P (t))
	      {
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD is threadprivate variable in %qs clause", t,
			  omp_clause_ಸಂಕೇತ_name[OMP_CLAUSE_ಸಂಕೇತ (c)]);
		remove = ನಿಜ;
	      }
	    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ ((OMP_CLAUSE_ಸಂಕೇತ (c) != OMP_CLAUSE_MAP
		      || (OMP_CLAUSE_MAP_ಬಗೆ (c)
			  != GOMP_MAP_FIRSTPRIVATE_ಸೂಚಕ))
		     && !c_mark_addressable (t))
	      remove = ನಿಜ;
	    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!(OMP_CLAUSE_ಸಂಕೇತ (c) == OMP_CLAUSE_MAP
		       && (OMP_CLAUSE_MAP_ಬಗೆ (c) == GOMP_MAP_ಸೂಚಕ
			   || (OMP_CLAUSE_MAP_ಬಗೆ (c)
			       == GOMP_MAP_FIRSTPRIVATE_ಸೂಚಕ)
			   || (OMP_CLAUSE_MAP_ಬಗೆ (c)
			       == GOMP_MAP_FORCE_DEVICEPTR)))
		     && t == OMP_CLAUSE_DECL (c)
		     && !omp_mappable_type (ವೃಕ್ಷ_TYPE (t)))
	      {
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD does not have a mappable type in %qs clause", t,
			  omp_clause_ಸಂಕೇತ_name[OMP_CLAUSE_ಸಂಕೇತ (c)]);
		remove = ನಿಜ;
	      }
	    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ವೃಕ್ಷ_TYPE (t) == error_mark_ಗಂಟು)
	      remove = ನಿಜ;
	    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (TYPE_ATOMIC (strip_array_types (ವೃಕ್ಷ_TYPE (t))))
	      {
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%<_Atomic%> %qE in %qs clause", t,
			  omp_clause_ಸಂಕೇತ_name[OMP_CLAUSE_ಸಂಕೇತ (c)]);
		remove = ನಿಜ;
	      }
	    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (OMP_CLAUSE_ಸಂಕೇತ (c) == OMP_CLAUSE_MAP
		     && OMP_CLAUSE_MAP_IMPLICIT (c)
		     && (bitmap_ಬಿಟ್_p (&map_ತಲೆ, DECL_UID (t))
			 || bitmap_ಬಿಟ್_p (&map_ಕ್ಷೇತ್ರ_ತಲೆ, DECL_UID (t))
			 || bitmap_ಬಿಟ್_p (&map_firstprivate_ತಲೆ,
					  DECL_UID (t))))
	      remove = ನಿಜ;
	    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (OMP_CLAUSE_ಸಂಕೇತ (c) == OMP_CLAUSE_MAP
		     && (OMP_CLAUSE_MAP_ಬಗೆ (c)
			 == GOMP_MAP_FIRSTPRIVATE_ಸೂಚಕ))
	      {
		ಆದರೆ (bitmap_ಬಿಟ್_p (&generic_ತಲೆ, DECL_UID (t))
		    || bitmap_ಬಿಟ್_p (&firstprivate_ತಲೆ, DECL_UID (t))
		    || bitmap_ಬಿಟ್_p (&map_firstprivate_ತಲೆ, DECL_UID (t)))
		  {
		    error_at (OMP_CLAUSE_LOCATION (c),
			      "%qD appears more than once in data clauses", t);
		    remove = ನಿಜ;
		  }
		ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (bitmap_ಬಿಟ್_p (&map_ತಲೆ, DECL_UID (t))
			 && !bitmap_ಬಿಟ್_p (&map_ಕ್ಷೇತ್ರ_ತಲೆ, DECL_UID (t))
			 && openacc)
		  {
		    error_at (OMP_CLAUSE_LOCATION (c),
			      "%qD appears more than once in data clauses", t);
		    remove = ನಿಜ;
		  }
		ಇಲ್ಲದಿದ್ದರೆ
		  bitmap_ಗಣ_ಬಿಟ್ (&map_firstprivate_ತಲೆ, DECL_UID (t));
	      }
	    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (bitmap_ಬಿಟ್_p (&map_ತಲೆ, DECL_UID (t))
		     && !bitmap_ಬಿಟ್_p (&map_ಕ್ಷೇತ್ರ_ತಲೆ, DECL_UID (t))
		     && ort != C_ORT_OMP
		     && ort != C_ORT_OMP_ಗುರಿ
		     && ort != C_ORT_OMP_EXIT_ದತ್ತಾಂಶ)
	      {
		ಆದರೆ (OMP_CLAUSE_ಸಂಕೇತ (c) != OMP_CLAUSE_MAP)
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD appears more than once in motion clauses", t);
		ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (openacc)
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD appears more than once in data clauses", t);
		ಇಲ್ಲದಿದ್ದರೆ
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD appears more than once in map clauses", t);
		remove = ನಿಜ;
	      }
	    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (openacc && bitmap_ಬಿಟ್_p (&generic_ತಲೆ, DECL_UID (t)))
	      {
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD appears more than once in data clauses", t);
		remove = ನಿಜ;
	      }
	    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (bitmap_ಬಿಟ್_p (&firstprivate_ತಲೆ, DECL_UID (t))
		     || bitmap_ಬಿಟ್_p (&is_on_device_ತಲೆ, DECL_UID (t)))
	      {
		ಆದರೆ (openacc)
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD appears more than once in data clauses", t);
		ಇಲ್ಲದಿದ್ದರೆ
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD appears both in data and map clauses", t);
		remove = ನಿಜ;
	      }
	    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!omp_access_chain_p (addr_ಟೋಕನುಗಳು, 1))
	      {
		bitmap_ಗಣ_ಬಿಟ್ (&map_ತಲೆ, DECL_UID (t));
		ಆದರೆ (t != OMP_CLAUSE_DECL (c)
		    && ವೃಕ್ಷ_ಸಂಕೇತ (OMP_CLAUSE_DECL (c)) == COMPONENT_REF)
		  bitmap_ಗಣ_ಬಿಟ್ (&map_ಕ್ಷೇತ್ರ_ತಲೆ, DECL_UID (t));
	      }

	  skip_decl_checks:
	    /* If we call omp_expand_map_clause in handle_omp_array_sections,
	       the containing loop (here) iterates through the new nodes
	       created by that expansion.  Avoid expanding those again (just
	       by checking the node type).  */
	    ಆದರೆ (!remove
		&& ort != C_ORT_DECLARE_SIMD
		&& (OMP_CLAUSE_ಸಂಕೇತ (c) != OMP_CLAUSE_MAP
		    || (OMP_CLAUSE_MAP_ಬಗೆ (c) != GOMP_MAP_FIRSTPRIVATE_ಸೂಚಕ
			&& (OMP_CLAUSE_MAP_ಬಗೆ (c)
			    != GOMP_MAP_FIRSTPRIVATE_REFERENCE)
			&& OMP_CLAUSE_MAP_ಬಗೆ (c) != GOMP_MAP_ALWAYS_ಸೂಚಕ
			&& OMP_CLAUSE_MAP_ಬಗೆ (c) != GOMP_MAP_ATTACH_DETACH
			&& OMP_CLAUSE_MAP_ಬಗೆ (c) != GOMP_MAP_ATTACH
			&& OMP_CLAUSE_MAP_ಬಗೆ (c) != GOMP_MAP_DETACH)))
	      {
		grp_ಆರಂಭ_p = pc;
		grp_sentinel = OMP_CLAUSE_CHAIN (c);
		ವೃಕ್ಷ nc = ai.expand_map_clause (c, OMP_CLAUSE_DECL (c),
						addr_ಟೋಕನುಗಳು, ort);
		ಆದರೆ (nc != error_mark_ಗಂಟು)
		  c = nc;
	      }
	  }
	  ನಿಲ್ಲಿಸು;

	ಸ್ಥಿತಿ OMP_CLAUSE_ENTER:
	ಸ್ಥಿತಿ OMP_CLAUSE_LINK:
	ಸ್ಥಿತಿ OMP_CLAUSE_LOCAL:
	  t = OMP_CLAUSE_DECL (c);
	  ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *cname;
	  cname = omp_clause_ಸಂಕೇತ_name[OMP_CLAUSE_ಸಂಕೇತ (c)];
	  ಆದರೆ (OMP_CLAUSE_ಸಂಕೇತ (c) == OMP_CLAUSE_ENTER
	      && OMP_CLAUSE_ENTER_ಗಮ್ಯ (c))
	    cname = "to";
	  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (t) == FUNCTION_DECL
	      && OMP_CLAUSE_ಸಂಕೇತ (c) == OMP_CLAUSE_ENTER)
	    ;
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!VAR_P (t))
	    {
	      ಆದರೆ (OMP_CLAUSE_ಸಂಕೇತ (c) == OMP_CLAUSE_ENTER)
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qE is neither a variable nor a function name in "
			  "clause %qs", t, cname);
	      ಇಲ್ಲದಿದ್ದರೆ
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qE is not a variable in clause %qs", t, cname);
	      remove = ನಿಜ;
	    }
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (DECL_THREAD_LOCAL_P (t))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qD is threadprivate variable in %qs clause", t,
			cname);
	      remove = ನಿಜ;
	    }
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!omp_mappable_type (ವೃಕ್ಷ_TYPE (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qD does not have a mappable type in %qs clause", t,
			cname);
	      remove = ನಿಜ;
	    }
	  ಆದರೆ (remove)
	    ನಿಲ್ಲಿಸು;
	  ಆದರೆ (bitmap_ಬಿಟ್_p (&generic_ತಲೆ, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE appears more than once on the same "
			"%<declare target%> directive", t);
	      remove = ನಿಜ;
	    }
	  ಇಲ್ಲದಿದ್ದರೆ
	    bitmap_ಗಣ_ಬಿಟ್ (&generic_ತಲೆ, DECL_UID (t));
	  ನಿಲ್ಲಿಸು;

	ಸ್ಥಿತಿ OMP_CLAUSE_ಏಕರೂಪ:
	  t = OMP_CLAUSE_DECL (c);
	  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (t) != PARM_DECL)
	    {
	      ಆದರೆ (DECL_P (t))
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD is not an argument in %<uniform%> clause", t);
	      ಇಲ್ಲದಿದ್ದರೆ
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qE is not an argument in %<uniform%> clause", t);
	      remove = ನಿಜ;
	      ನಿಲ್ಲಿಸು;
	    }
	  /* map_head bitmap is used as uniform_head if declare_simd.  */
	  bitmap_ಗಣ_ಬಿಟ್ (&map_ತಲೆ, DECL_UID (t));
	  ಹೋಗು check_dup_generic;

	ಸ್ಥಿತಿ OMP_CLAUSE_IS_DEVICE_PTR:
	ಸ್ಥಿತಿ OMP_CLAUSE_USE_DEVICE_PTR:
	  t = OMP_CLAUSE_DECL (c);
	  ಆದರೆ (OMP_CLAUSE_ಸಂಕೇತ (c) == OMP_CLAUSE_IS_DEVICE_PTR)
	    bitmap_ಗಣ_ಬಿಟ್ (&is_on_device_ತಲೆ, DECL_UID (t));
	  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (t)) != ಸೂಚಕ_TYPE)
	    {
	      ಆದರೆ (OMP_CLAUSE_ಸಂಕೇತ (c) == OMP_CLAUSE_USE_DEVICE_PTR
		  && !openacc)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qs variable is not a pointer",
			    omp_clause_ಸಂಕೇತ_name[OMP_CLAUSE_ಸಂಕೇತ (c)]);
		  remove = ನಿಜ;
		}
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (t)) != ARRAY_TYPE)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qs variable is neither a pointer nor an array",
			    omp_clause_ಸಂಕೇತ_name[OMP_CLAUSE_ಸಂಕೇತ (c)]);
		  remove = ನಿಜ;
		}
	    }
	  ಹೋಗು check_dup_generic;

	ಸ್ಥಿತಿ OMP_CLAUSE_HAS_DEVICE_ADDR:
	  t = OMP_CLAUSE_DECL (c);
	  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (t) == OMP_ARRAY_SECTION)
	    {
	      ಆದರೆ (handle_omp_array_sections (c, ort))
		remove = ನಿಜ;
	      ಇಲ್ಲದಿದ್ದರೆ
		{
		  t = OMP_CLAUSE_DECL (c);
		  ಆಗ (ವೃಕ್ಷ_ಸಂಕೇತ (t) == ARRAY_REF)
		    t = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (t, 0);
		}
	    }
	  bitmap_ಗಣ_ಬಿಟ್ (&is_on_device_ತಲೆ, DECL_UID (t));
	  ಆದರೆ (VAR_P (t) || ವೃಕ್ಷ_ಸಂಕೇತ (t) == PARM_DECL)
	    c_mark_addressable (t);
	  ಹೋಗು check_dup_generic_t;

	ಸ್ಥಿತಿ OMP_CLAUSE_USE_DEVICE_ADDR:
	  t = OMP_CLAUSE_DECL (c);
	  ಆದರೆ (VAR_P (t) || ವೃಕ್ಷ_ಸಂಕೇತ (t) == PARM_DECL)
	    c_mark_addressable (t);
	  ಹೋಗು check_dup_generic;

	ಸ್ಥಿತಿ OMP_CLAUSE_NOWAIT:
	  ಆದರೆ (copyprivate_ನೋಡಿದ)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<nowait%> clause must not be used together "
			"with %<copyprivate%> clause");
	      remove = ನಿಜ;
	      ನಿಲ್ಲಿಸು;
	    }
	  nowait_clause = pc;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  ಮುಂದುವರಿ;

	ಸ್ಥಿತಿ OMP_CLAUSE_ಕ್ರಮ:
	  ಆದರೆ (ordered_clause)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<order%> clause must not be used together "
			"with %<ordered%> clause");
	      remove = ನಿಜ;
	      ನಿಲ್ಲಿಸು;
	    }
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ಕ್ರಮ_clause)
	    {
	      /* Silently remove duplicates.  */
	      remove = ನಿಜ;
	      ನಿಲ್ಲಿಸು;
	    }
	  ಕ್ರಮ_clause = pc;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  ಮುಂದುವರಿ;

	ಸ್ಥಿತಿ OMP_CLAUSE_DETACH:
	  t = OMP_CLAUSE_DECL (c);
	  ಆದರೆ (detach_ನೋಡಿದ)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"too many %qs clauses on a task construct",
			"detach");
	      remove = ನಿಜ;
	      ನಿಲ್ಲಿಸು;
	    }
	  detach_ನೋಡಿದ = pc;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  c_mark_addressable (t);
	  ಮುಂದುವರಿ;

	ಸ್ಥಿತಿ OMP_CLAUSE_IF:
	ಸ್ಥಿತಿ OMP_CLAUSE_SELF:
	ಸ್ಥಿತಿ OMP_CLAUSE_ಅಂಕೆ_ಎಳೆಗಳು:
	ಸ್ಥಿತಿ OMP_CLAUSE_ಅಂಕೆ_TEAMS:
	ಸ್ಥಿತಿ OMP_CLAUSE_THREAD_ಎಲ್ಲೆ:
	ಸ್ಥಿತಿ OMP_CLAUSE_DEFAULT:
	ಸ್ಥಿತಿ OMP_CLAUSE_UNTIED:
	ಸ್ಥಿತಿ OMP_CLAUSE_COLLAPSE:
	ಸ್ಥಿತಿ OMP_CLAUSE_FINAL:
	ಸ್ಥಿತಿ OMP_CLAUSE_DEVICE:
	ಸ್ಥಿತಿ OMP_CLAUSE_DIST_ವೇಳಾಪಟ್ಟಿ:
	ಸ್ಥಿತಿ OMP_CLAUSE_DYN_GROUPPRIVATE:
	ಸ್ಥಿತಿ OMP_CLAUSE_PARALLEL:
	ಸ್ಥಿತಿ OMP_CLAUSE_FOR:
	ಸ್ಥಿತಿ OMP_CLAUSE_SECTIONS:
	ಸ್ಥಿತಿ OMP_CLAUSE_TASKGROUP:
	ಸ್ಥಿತಿ OMP_CLAUSE_PROC_BIND:
	ಸ್ಥಿತಿ OMP_CLAUSE_DEVICE_TYPE:
	ಸ್ಥಿತಿ OMP_CLAUSE_ಆದ್ಯತೆ:
	ಸ್ಥಿತಿ OMP_CLAUSE_ಎಳೆಗಳು:
	ಸ್ಥಿತಿ OMP_CLAUSE_SIMD:
	ಸ್ಥಿತಿ OMP_CLAUSE_HINT:
	ಸ್ಥಿತಿ OMP_CLAUSE_FILTER:
	ಸ್ಥಿತಿ OMP_CLAUSE_DEFAULTMAP:
	ಸ್ಥಿತಿ OMP_CLAUSE_BIND:
	ಸ್ಥಿತಿ OMP_CLAUSE_ಅಂಕೆ_GANGS:
	ಸ್ಥಿತಿ OMP_CLAUSE_ಅಂಕೆ_WORKERS:
	ಸ್ಥಿತಿ OMP_CLAUSE_ಸದಿಶ_ಉದ್ದಳತೆ:
	ಸ್ಥಿತಿ OMP_CLAUSE_ASYNC:
	ಸ್ಥಿತಿ OMP_CLAUSE_WAIT:
	ಸ್ಥಿತಿ OMP_CLAUSE_AUTO:
	ಸ್ಥಿತಿ OMP_CLAUSE_INDEPENDENT:
	ಸ್ಥಿತಿ OMP_CLAUSE_SEQ:
	ಸ್ಥಿತಿ OMP_CLAUSE_GANG:
	ಸ್ಥಿತಿ OMP_CLAUSE_ಕೆಲಸಗಾರ:
	ಸ್ಥಿತಿ OMP_CLAUSE_ಸದಿಶ:
	ಸ್ಥಿತಿ OMP_CLAUSE_TILE:
	ಸ್ಥಿತಿ OMP_CLAUSE_IF_PRESENT:
	ಸ್ಥಿತಿ OMP_CLAUSE_FINALIZE:
	ಸ್ಥಿತಿ OMP_CLAUSE_NOHOST:
	ಸ್ಥಿತಿ OMP_CLAUSE_ಪರೋಕ್ಷ:
	ಸ್ಥಿತಿ OMP_CLAUSE_NOVARIANTS:
	ಸ್ಥಿತಿ OMP_CLAUSE_NOCONTEXT:
	  pc = &OMP_CLAUSE_CHAIN (c);
	  ಮುಂದುವರಿ;

	ಸ್ಥಿತಿ OMP_CLAUSE_GRAINSIZE:
	  grainsize_ನೋಡಿದ = pc;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  ಮುಂದುವರಿ;

	ಸ್ಥಿತಿ OMP_CLAUSE_ಅಂಕೆ_TASKS:
	  ಅಂಕೆ_tasks_ನೋಡಿದ = ನಿಜ;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  ಮುಂದುವರಿ;

	ಸ್ಥಿತಿ OMP_CLAUSE_MERGEABLE:
	  mergeable_ನೋಡಿದ = ನಿಜ;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  ಮುಂದುವರಿ;

	ಸ್ಥಿತಿ OMP_CLAUSE_NOGROUP:
	  nogroup_ನೋಡಿದ = pc;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  ಮುಂದುವರಿ;

	ಸ್ಥಿತಿ OMP_CLAUSE_ವೇಳಾಪಟ್ಟಿ:
	  ವೇಳಾಪಟ್ಟಿ_clause = c;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  ಮುಂದುವರಿ;

	ಸ್ಥಿತಿ OMP_CLAUSE_ORDERED:
	  ordered_clause = c;
	  ಆದರೆ (ಕ್ರಮ_clause)
	    {
	      error_at (OMP_CLAUSE_LOCATION (*ಕ್ರಮ_clause),
			"%<order%> clause must not be used together "
			"with %<ordered%> clause");
	      *ಕ್ರಮ_clause = OMP_CLAUSE_CHAIN (*ಕ್ರಮ_clause);
	      ಕ್ರಮ_clause = ಖಾಲಿ;
	    }
	  pc = &OMP_CLAUSE_CHAIN (c);
	  ಮುಂದುವರಿ;

	ಸ್ಥಿತಿ OMP_CLAUSE_SAFELEN:
	  safelen = c;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  ಮುಂದುವರಿ;
	ಸ್ಥಿತಿ OMP_CLAUSE_SIMDLEN:
	  simdlen = c;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  ಮುಂದುವರಿ;

	ಸ್ಥಿತಿ OMP_CLAUSE_ತುಂಬಿದ:
	  ತುಂಬಿದ_ನೋಡಿದ = pc;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  ಮುಂದುವರಿ;

	ಸ್ಥಿತಿ OMP_CLAUSE_PARTIAL:
	  partial_ನೋಡಿದ = ನಿಜ;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  ಮುಂದುವರಿ;

	ಸ್ಥಿತಿ OMP_CLAUSE_SIZES:
	  pc = &OMP_CLAUSE_CHAIN (c);
	  ಮುಂದುವರಿ;

	ಸ್ಥಿತಿ OMP_CLAUSE_INBRANCH:
	ಸ್ಥಿತಿ OMP_CLAUSE_NOTINBRANCH:
	  ಆದರೆ (branch_ನೋಡಿದ)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<inbranch%> clause is incompatible with "
			"%<notinbranch%>");
	      remove = ನಿಜ;
	      ನಿಲ್ಲಿಸು;
	    }
	  branch_ನೋಡಿದ = ನಿಜ;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  ಮುಂದುವರಿ;

	ಸ್ಥಿತಿ OMP_CLAUSE_INCLUSIVE:
	ಸ್ಥಿತಿ OMP_CLAUSE_EXCLUSIVE:
	  need_complete = ನಿಜ;
	  need_implicitly_determined = ನಿಜ;
	  t = OMP_CLAUSE_DECL (c);
	  ಆದರೆ (!VAR_P (t) && ವೃಕ್ಷ_ಸಂಕೇತ (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in clause %qs", t,
			omp_clause_ಸಂಕೇತ_name[OMP_CLAUSE_ಸಂಕೇತ (c)]);
	      remove = ನಿಜ;
	    }
	  ನಿಲ್ಲಿಸು;

	ಸ್ಥಿತಿ OMP_CLAUSE_INIT:
	  init_ನೋಡಿದ = ನಿಜ;
	  ಆದರೆ (!OMP_CLAUSE_INIT_TARGETSYNC (c))
	    init_no_targetsync_clause = c;
	  /* FALLTHRU */
	ಸ್ಥಿತಿ OMP_CLAUSE_DESTROY:
	ಸ್ಥಿತಿ OMP_CLAUSE_USE:
	  init_use_destroy_ನೋಡಿದ = ನಿಜ;
	  t = OMP_CLAUSE_DECL (c);
	  ಆದರೆ (bitmap_ಬಿಟ್_p (&generic_ತಲೆ, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qD appears more than once in action clauses", t);
	      remove = ನಿಜ;
	      ನಿಲ್ಲಿಸು;
	    }
	  bitmap_ಗಣ_ಬಿಟ್ (&generic_ತಲೆ, DECL_UID (t));
	  /* FALLTHRU */
	ಸ್ಥಿತಿ OMP_CLAUSE_INTEROP:
	  ಆದರೆ (/* ort == C_ORT_OMP_INTEROP [uncomment for depobj init]  */
		   !c_omp_interop_t_p (ವೃಕ್ಷ_TYPE (OMP_CLAUSE_DECL (c))))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qD must be of %<omp_interop_t%>",
			OMP_CLAUSE_DECL (c));
	      remove = ನಿಜ;
	    }
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ ((OMP_CLAUSE_ಸಂಕೇತ (c) == OMP_CLAUSE_INIT
		    || OMP_CLAUSE_ಸಂಕೇತ (c) == OMP_CLAUSE_DESTROY)
		   && ವೃಕ್ಷ_READONLY (OMP_CLAUSE_DECL (c)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
		      "%qD shall not be const", OMP_CLAUSE_DECL (c));
	      remove = ನಿಜ;
	    }
	  pc = &OMP_CLAUSE_CHAIN (c);
	  ನಿಲ್ಲಿಸು;
	ಪೂರ್ವನಿಯೋಜಿತ:
	  gcc_unreachable ();
	}

      ಆದರೆ (!remove)
	{
	  t = OMP_CLAUSE_DECL (c);

	  ಆದರೆ (need_complete)
	    {
	      t = require_complete_type (OMP_CLAUSE_LOCATION (c), t);
	      ಆದರೆ (t == error_mark_ಗಂಟು)
		remove = ನಿಜ;
	    }

	  ಆದರೆ (need_implicitly_determined)
	    {
	      ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *share_name = ಖಾಲಿ;

	      ಆದರೆ (VAR_P (t) && DECL_THREAD_LOCAL_P (t))
		share_name = "threadprivate";
	      ಇಲ್ಲದಿದ್ದರೆ ಆಯ್ಕೆ (c_omp_predetermined_sharing (t))
		{
		ಸ್ಥಿತಿ OMP_CLAUSE_DEFAULT_UNSPECIFIED:
		  ನಿಲ್ಲಿಸು;
		ಸ್ಥಿತಿ OMP_CLAUSE_DEFAULT_SHARED:
		  ಆದರೆ ((OMP_CLAUSE_ಸಂಕೇತ (c) == OMP_CLAUSE_SHARED
		       || OMP_CLAUSE_ಸಂಕೇತ (c) == OMP_CLAUSE_FIRSTPRIVATE)
		      && c_omp_predefined_variable (t))
		    /* The __func__ variable and similar function-local
		       predefined variables may be listed in a shared or
		       firstprivate clause.  */
		    ನಿಲ್ಲಿಸು;
		  share_name = "shared";
		  ನಿಲ್ಲಿಸು;
		ಸ್ಥಿತಿ OMP_CLAUSE_DEFAULT_ಖಾಸಗಿ:
		  share_name = "private";
		  ನಿಲ್ಲಿಸು;
		ಪೂರ್ವನಿಯೋಜಿತ:
		  gcc_unreachable ();
		}
	      ಆದರೆ (share_name)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qE is predetermined %qs for %qs",
			    t, share_name,
			    omp_clause_ಸಂಕೇತ_name[OMP_CLAUSE_ಸಂಕೇತ (c)]);
		  remove = ನಿಜ;
		}
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ವೃಕ್ಷ_READONLY (t)
		       && OMP_CLAUSE_ಸಂಕೇತ (c) != OMP_CLAUSE_SHARED
		       && OMP_CLAUSE_ಸಂಕೇತ (c) != OMP_CLAUSE_FIRSTPRIVATE)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%<const%> qualified %qE may appear only in "
			    "%<shared%> or %<firstprivate%> clauses", t);
		  remove = ನಿಜ;
		}
	    }
	}

      ಆದರೆ (remove)
	{
	  ಆದರೆ (grp_ಆರಂಭ_p)
	    {
	      /* If we found a clause to remove, we want to remove the whole
		 expanded group, otherwise gimplify
		 (omp_resolve_clause_dependencies) can get confused.  */
	      *grp_ಆರಂಭ_p = grp_sentinel;
	      pc = grp_ಆರಂಭ_p;
	      grp_ಆರಂಭ_p = ಖಾಲಿ;
	    }
	  ಇಲ್ಲದಿದ್ದರೆ
	    *pc = OMP_CLAUSE_CHAIN (c);
	}
      ಇಲ್ಲದಿದ್ದರೆ
	pc = &OMP_CLAUSE_CHAIN (c);
    }

  ಆದರೆ (grp_ಆರಂಭ_p
      && OMP_CLAUSE_HAS_ITERATORS (*grp_ಆರಂಭ_p))
    ಗಾಗಿ (ವೃಕ್ಷ gc = *grp_ಆರಂಭ_p; gc; gc = OMP_CLAUSE_CHAIN (gc))
      OMP_CLAUSE_ITERATORS (gc) = OMP_CLAUSE_ITERATORS (*grp_ಆರಂಭ_p);

  ಆದರೆ (simdlen
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

  ಆದರೆ (ordered_clause
      && ವೇಳಾಪಟ್ಟಿ_clause
      && (OMP_CLAUSE_ವೇಳಾಪಟ್ಟಿ_ಬಗೆ (ವೇಳಾಪಟ್ಟಿ_clause)
	  & OMP_CLAUSE_ವೇಳಾಪಟ್ಟಿ_NONMONOTONIC))
    {
      error_at (OMP_CLAUSE_LOCATION (ವೇಳಾಪಟ್ಟಿ_clause),
		"%<nonmonotonic%> schedule modifier specified together "
		"with %<ordered%> clause");
      OMP_CLAUSE_ವೇಳಾಪಟ್ಟಿ_ಬಗೆ (ವೇಳಾಪಟ್ಟಿ_clause)
	= (ಎಣಿಕೆ omp_clause_ವೇಳಾಪಟ್ಟಿ_ಬಗೆ)
	  (OMP_CLAUSE_ವೇಳಾಪಟ್ಟಿ_ಬಗೆ (ವೇಳಾಪಟ್ಟಿ_clause)
	   & ~OMP_CLAUSE_ವೇಳಾಪಟ್ಟಿ_NONMONOTONIC);
    }

  ಆದರೆ (reduction_ನೋಡಿದ < 0 && ordered_clause)
    {
      error_at (OMP_CLAUSE_LOCATION (ordered_clause),
		"%qs clause specified together with %<inscan%> "
		"%<reduction%> clause", "ordered");
      reduction_ನೋಡಿದ = -2;
    }

  ಆದರೆ (reduction_ನೋಡಿದ < 0 && ವೇಳಾಪಟ್ಟಿ_clause)
    {
      error_at (OMP_CLAUSE_LOCATION (ವೇಳಾಪಟ್ಟಿ_clause),
		"%qs clause specified together with %<inscan%> "
		"%<reduction%> clause", "schedule");
      reduction_ನೋಡಿದ = -2;
    }

  ಆದರೆ (ರೇಖೀಯ_variable_ಹೆಜ್ಜೆ_check
      || reduction_ನೋಡಿದ == -2
      || allocate_ನೋಡಿದ
      || ಗುರಿ_ಒಳ_reduction_ನೋಡಿದ)
    ಗಾಗಿ (pc = &clauses, c = clauses; c ; c = *pc)
      {
	ತಾರ್ಕಿಕ remove = ಸುಳ್ಳು;
	ಆದರೆ (allocate_ನೋಡಿದ)
	  ಆಯ್ಕೆ (OMP_CLAUSE_ಸಂಕೇತ (c))
	    {
	    ಸ್ಥಿತಿ OMP_CLAUSE_REDUCTION:
	    ಸ್ಥಿತಿ OMP_CLAUSE_ಒಳ_REDUCTION:
	    ಸ್ಥಿತಿ OMP_CLAUSE_TASK_REDUCTION:
	      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (OMP_CLAUSE_DECL (c)) == MEM_REF)
		{
		  t = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (OMP_CLAUSE_DECL (c), 0);
		  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (t) == ಸೂಚಕ_PLUS_ಅಭಿವ್ಯಕ್ತಿ)
		    t = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (t, 0);
		  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (t) == ADDR_ಅಭಿವ್ಯಕ್ತಿ
		      || ಪರೋಕ್ಷ_REF_P (t))
		    t = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (t, 0);
		  ಆದರೆ (DECL_P (t))
		    bitmap_clear_ಬಿಟ್ (&aligned_ತಲೆ, DECL_UID (t));
		  ನಿಲ್ಲಿಸು;
		}
	      /* FALLTHRU */
	    ಸ್ಥಿತಿ OMP_CLAUSE_ಖಾಸಗಿ:
	    ಸ್ಥಿತಿ OMP_CLAUSE_FIRSTPRIVATE:
	    ಸ್ಥಿತಿ OMP_CLAUSE_LASTPRIVATE:
	    ಸ್ಥಿತಿ OMP_CLAUSE_ರೇಖೀಯ:
	      ಆದರೆ (DECL_P (OMP_CLAUSE_DECL (c)))
		bitmap_clear_ಬಿಟ್ (&aligned_ತಲೆ,
				  DECL_UID (OMP_CLAUSE_DECL (c)));
	      ನಿಲ್ಲಿಸು;
	    ಪೂರ್ವನಿಯೋಜಿತ:
	      ನಿಲ್ಲಿಸು;
	    }
	ಆದರೆ (OMP_CLAUSE_ಸಂಕೇತ (c) == OMP_CLAUSE_ರೇಖೀಯ
	    && OMP_CLAUSE_ರೇಖೀಯ_VARIABLE_STRIDE (c)
	    && !bitmap_ಬಿಟ್_p (&map_ತಲೆ,
			      DECL_UID (OMP_CLAUSE_ರೇಖೀಯ_ಹೆಜ್ಜೆ (c))))
	  {
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%<linear%> clause step is a parameter %qD not "
		      "specified in %<uniform%> clause",
		      OMP_CLAUSE_ರೇಖೀಯ_ಹೆಜ್ಜೆ (c));
	    remove = ನಿಜ;
	  }
	ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (OMP_CLAUSE_ಸಂಕೇತ (c) == OMP_CLAUSE_REDUCTION
		 && reduction_ನೋಡಿದ == -2)
	  OMP_CLAUSE_REDUCTION_INSCAN (c) = 0;
	ಆದರೆ (ಗುರಿ_ಒಳ_reduction_ನೋಡಿದ
	    && OMP_CLAUSE_ಸಂಕೇತ (c) == OMP_CLAUSE_MAP)
	  {
	    ವೃಕ್ಷ t = OMP_CLAUSE_DECL (c);
	    ಆಗ (handled_component_p (t)
		   || ಪರೋಕ್ಷ_REF_P (t)
		   || ವೃಕ್ಷ_ಸಂಕೇತ (t) == ADDR_ಅಭಿವ್ಯಕ್ತಿ
		   || ವೃಕ್ಷ_ಸಂಕೇತ (t) == MEM_REF
		   || ವೃಕ್ಷ_ಸಂಕೇತ (t) == NON_LVALUE_ಅಭಿವ್ಯಕ್ತಿ)
	      t = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (t, 0);
	    ಆದರೆ (DECL_P (t)
		&& bitmap_ಬಿಟ್_p (&oacc_reduction_ತಲೆ, DECL_UID (t)))
	      OMP_CLAUSE_MAP_ಒಳ_REDUCTION (c) = 1;
	  }

	ಆದರೆ (remove)
	  *pc = OMP_CLAUSE_CHAIN (c);
	ಇಲ್ಲದಿದ್ದರೆ
	  pc = &OMP_CLAUSE_CHAIN (c);
      }

  ಆದರೆ (allocate_ನೋಡಿದ)
    ಗಾಗಿ (pc = &clauses, c = clauses; c ; c = *pc)
      {
	ತಾರ್ಕಿಕ remove = ಸುಳ್ಳು;
	ಆದರೆ (OMP_CLAUSE_ಸಂಕೇತ (c) == OMP_CLAUSE_ALLOCATE
	    && !OMP_CLAUSE_ALLOCATE_COMBINED (c)
	    && bitmap_ಬಿಟ್_p (&aligned_ತಲೆ, DECL_UID (OMP_CLAUSE_DECL (c))))
	  {
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%qD specified in %<allocate%> clause but not in "
		      "an explicit privatization clause", OMP_CLAUSE_DECL (c));
	    remove = ನಿಜ;
	  }
	ಆದರೆ (remove)
	  *pc = OMP_CLAUSE_CHAIN (c);
	ಇಲ್ಲದಿದ್ದರೆ
	  pc = &OMP_CLAUSE_CHAIN (c);
      }

  ಆದರೆ (nogroup_ನೋಡಿದ && reduction_ನೋಡಿದ)
    {
      error_at (OMP_CLAUSE_LOCATION (*nogroup_ನೋಡಿದ),
		"%<nogroup%> clause must not be used together with "
		"%<reduction%> clause");
      *nogroup_ನೋಡಿದ = OMP_CLAUSE_CHAIN (*nogroup_ನೋಡಿದ);
    }

  ಆದರೆ (grainsize_ನೋಡಿದ && ಅಂಕೆ_tasks_ನೋಡಿದ)
    {
      error_at (OMP_CLAUSE_LOCATION (*grainsize_ನೋಡಿದ),
		"%<grainsize%> clause must not be used together with "
		"%<num_tasks%> clause");
      *grainsize_ನೋಡಿದ = OMP_CLAUSE_CHAIN (*grainsize_ನೋಡಿದ);
    }

  ಆದರೆ (ತುಂಬಿದ_ನೋಡಿದ && partial_ನೋಡಿದ)
    {
      error_at (OMP_CLAUSE_LOCATION (*ತುಂಬಿದ_ನೋಡಿದ),
		"%<full%> clause must not be used together with "
		"%<partial%> clause");
      *ತುಂಬಿದ_ನೋಡಿದ = OMP_CLAUSE_CHAIN (*ತುಂಬಿದ_ನೋಡಿದ);
    }

  ಆದರೆ (detach_ನೋಡಿದ)
    {
      ಆದರೆ (mergeable_ನೋಡಿದ)
	{
	  error_at (OMP_CLAUSE_LOCATION (*detach_ನೋಡಿದ),
		    "%<detach%> clause must not be used together with "
		    "%<mergeable%> clause");
	  *detach_ನೋಡಿದ = OMP_CLAUSE_CHAIN (*detach_ನೋಡಿದ);
	}
      ಇಲ್ಲದಿದ್ದರೆ
	{
	  ವೃಕ್ಷ detach_decl = OMP_CLAUSE_DECL (*detach_ನೋಡಿದ);

	  ಗಾಗಿ (pc = &clauses, c = clauses; c ; c = *pc)
	    {
	      ತಾರ್ಕಿಕ remove = ಸುಳ್ಳು;
	      ಆದರೆ ((OMP_CLAUSE_ಸಂಕೇತ (c) == OMP_CLAUSE_SHARED
		   || OMP_CLAUSE_ಸಂಕೇತ (c) == OMP_CLAUSE_ಖಾಸಗಿ
		   || OMP_CLAUSE_ಸಂಕೇತ (c) == OMP_CLAUSE_FIRSTPRIVATE
		   || OMP_CLAUSE_ಸಂಕೇತ (c) == OMP_CLAUSE_LASTPRIVATE)
		  && OMP_CLAUSE_DECL (c) == detach_decl)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "the event handle of a %<detach%> clause "
			    "should not be in a data-sharing clause");
		  remove = ನಿಜ;
		}
	      ಆದರೆ (remove)
		*pc = OMP_CLAUSE_CHAIN (c);
	      ಇಲ್ಲದಿದ್ದರೆ
		pc = &OMP_CLAUSE_CHAIN (c);
	    }
	}
    }

  ಆದರೆ (ort == C_ORT_OMP_INTEROP
      && depend_clause
      && (!init_use_destroy_ನೋಡಿದ
	  || (init_ನೋಡಿದ && init_no_targetsync_clause)))
    {
      error_at (OMP_CLAUSE_LOCATION (depend_clause),
		"%<depend%> clause requires action clauses with "
		"%<targetsync%> interop-type");
      ಆದರೆ (init_no_targetsync_clause)
	inform (OMP_CLAUSE_LOCATION (init_no_targetsync_clause),
		"%<init%> clause lacks the %<targetsync%> modifier");
    }

  bitmap_obstack_release (ಖಾಲಿ);
  ಹಿಂತಿರುಗಿ clauses;
}

/* Do processing necessary to make CLAUSES well-formed, where CLAUSES result
   from implicit instantiation of user-defined mappers (in gimplify.cc).  */

ವೃಕ್ಷ
c_omp_ಮುಕ್ತಾಯ_mapper_clauses (ವೃಕ್ಷ clauses)
{
  ಹಿಂತಿರುಗಿ c_ಮುಕ್ತಾಯ_omp_clauses (clauses, C_ORT_OMP);
}

/* Return code to initialize DST with a copy constructor from SRC.
   C doesn't have copy constructors nor assignment operators, only for
   _Atomic vars we need to perform __atomic_load from src into a temporary
   followed by __atomic_store of the temporary to dst.  */

ವೃಕ್ಷ
c_omp_clause_copy_ctor (ವೃಕ್ಷ clause, ವೃಕ್ಷ dst, ವೃಕ್ಷ src)
{
  ಆದರೆ (!really_atomic_lvalue (dst) && !really_atomic_lvalue (src))
    ಹಿಂತಿರುಗಿ build2 (MODIFY_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (dst), dst, src);

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
  ವೃಕ್ಷ fndecl = builtin_decl_explicit (BUILT_ಒಳ_ATOMIC_ತುಂಬು);
  params->ಶೀಘ್ರ_ತಳ್ಳು (src_addr);
  params->ಶೀಘ್ರ_ತಳ್ಳು (tmp_addr);
  params->ಶೀಘ್ರ_ತಳ್ಳು (seq_cst);
  ವೃಕ್ಷ ತುಂಬು = c_build_function_call_vec (loc, vNULL, fndecl, params, ಖಾಲಿ);

  vec_alloc (params, 4);

  /* Build __atomic_store (&dst, &tmp, SEQ_CST);  */
  fndecl = builtin_decl_explicit (BUILT_ಒಳ_ATOMIC_STORE);
  params->ಶೀಘ್ರ_ತಳ್ಳು (dst_addr);
  params->ಶೀಘ್ರ_ತಳ್ಳು (tmp_addr);
  params->ಶೀಘ್ರ_ತಳ್ಳು (seq_cst);
  ವೃಕ್ಷ store = c_build_function_call_vec (loc, vNULL, fndecl, params, ಖಾಲಿ);
  ಹಿಂತಿರುಗಿ build2 (COMPOUND_ಅಭಿವ್ಯಕ್ತಿ, void_type_ಗಂಟು, ತುಂಬು, store);
}

/* Create a transaction node.  */

ವೃಕ್ಷ
c_ಮುಕ್ತಾಯ_transaction (location_t loc, ವೃಕ್ಷ ಖಂಡ, ಪೂರ್ಣಾಂಕ flags)
{
  ವೃಕ್ಷ stmt = build_stmt (loc, TRANSACTION_ಅಭಿವ್ಯಕ್ತಿ, ಖಂಡ);
  ಆದರೆ (flags & TM_STMT_ATTR_OUTER)
    TRANSACTION_ಅಭಿವ್ಯಕ್ತಿ_OUTER (stmt) = 1;
  ಆದರೆ (flags & TM_STMT_ATTR_RELAXED)
    TRANSACTION_ಅಭಿವ್ಯಕ್ತಿ_RELAXED (stmt) = 1;
  ಹಿಂತಿರುಗಿ ಕೂಡಿಸು_stmt (stmt);
}

/* Make a variant type in the proper way for C/C++, propagating qualifiers
   down to the element type of an array.  If ORIG_QUAL_TYPE is not
   NULL, then it should be used as the qualified type
   ORIG_QUAL_INDIRECT levels down in array type derivation (to
   preserve information about the typedef name from which an array
   type was derived).  */

ವೃಕ್ಷ
c_build_qualified_type (ವೃಕ್ಷ type, ಪೂರ್ಣಾಂಕ type_quals, ವೃಕ್ಷ orig_qual_type,
			ಗಾತ್ರ_t orig_qual_ಪರೋಕ್ಷ)
{
  ಆದರೆ (type == error_mark_ಗಂಟು)
    ಹಿಂತಿರುಗಿ type;

  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (type) == ARRAY_TYPE)
    {
      ವೃಕ್ಷ t;
      ವೃಕ್ಷ element_type = c_build_qualified_type (ವೃಕ್ಷ_TYPE (type),
						  type_quals, orig_qual_type,
						  orig_qual_ಪರೋಕ್ಷ - 1);

      /* See if we already have an identically qualified type.  */
      ಆದರೆ (orig_qual_type && orig_qual_ಪರೋಕ್ಷ == 0)
	t = orig_qual_type;
      ಇಲ್ಲದಿದ್ದರೆ
	ಗಾಗಿ (t = TYPE_MAIN_VARIANT (type); t; t = TYPE_ಮುಂದಿನ_VARIANT (t))
	  {
	    ಆದರೆ (TYPE_QUALS (strip_array_types (t)) == type_quals
		&& TYPE_NAME (t) == TYPE_NAME (type)
		&& TYPE_CONTEXT (t) == TYPE_CONTEXT (type)
		&& attribute_list_equal (TYPE_ಗುಣಲಕ್ಷಣಗಳು (t),
					 TYPE_ಗುಣಲಕ್ಷಣಗಳು (type)))
	      ನಿಲ್ಲಿಸು;
	  }
      ಆದರೆ (!t)
	{
          ವೃಕ್ಷ domain = TYPE_DOMAIN (type);

	  t = build_variant_type_copy (type);
	  ವೃಕ್ಷ_TYPE (t) = element_type;
	  TYPE_ADDR_SPACE (t) = TYPE_ADDR_SPACE (element_type);

          ಆದರೆ (TYPE_STRUCTURAL_EQUALITY_P (element_type)
              || (domain && TYPE_STRUCTURAL_EQUALITY_P (domain)))
            ಗಣ_TYPE_STRUCTURAL_EQUALITY (t);
          ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (TYPE_CANONICAL (element_type) != element_type
                   || (domain && TYPE_CANONICAL (domain) != domain))
            {
              ವೃಕ್ಷ unqualified_canon
		= c_build_array_type (TYPE_CANONICAL (element_type),
				      domain ? TYPE_CANONICAL (domain)
					     : NULL_ವೃಕ್ಷ);
              ಆದರೆ (TYPE_ಹಿಮ್ಮುಖ_STORAGE_ಕ್ರಮ (type))
                {
                  unqualified_canon
		    = build_distinct_type_copy (unqualified_canon);
                  TYPE_ಹಿಮ್ಮುಖ_STORAGE_ಕ್ರಮ (unqualified_canon) = 1;
                }
              TYPE_CANONICAL (t)
		= c_build_qualified_type (unqualified_canon, type_quals);
            }
          ಇಲ್ಲದಿದ್ದರೆ
            TYPE_CANONICAL (t) = t;
	}
      ಹಿಂತಿರುಗಿ t;
    }

  /* A restrict-qualified pointer type must be a pointer to object or
     incomplete type.  Note that the use of POINTER_TYPE_P also allows
     REFERENCE_TYPEs, which is appropriate for C++.  */
  ಆದರೆ ((type_quals & TYPE_QUAL_RESTRICT)
      && (!ಸೂಚಕ_TYPE_P (type)
	  || !C_TYPE_OBJECT_OR_INCOMPLETE_P (ವೃಕ್ಷ_TYPE (type))))
    {
      error ("invalid use of %<restrict%>");
      type_quals &= ~TYPE_QUAL_RESTRICT;
    }

  ವೃಕ್ಷ var_type = (orig_qual_type && orig_qual_ಪರೋಕ್ಷ == 0
		   ? orig_qual_type
		   : build_qualified_type (type, type_quals));

  gcc_checking_assert (C_TYPE_VARIABLE_ಗಾತ್ರ (var_type)
		       == C_TYPE_VARIABLE_ಗಾತ್ರ (type));
  gcc_checking_assert (c_type_variably_modified_p (var_type)
		       == c_type_variably_modified_p (type));

  /* A variant type does not inherit the list of incomplete vars from the
     type main variant.  */
  ಆದರೆ ((ದಾಖಲೆ_OR_UNION_TYPE_P (var_type)
       || ವೃಕ್ಷ_ಸಂಕೇತ (var_type) == ENUMERAL_TYPE)
      && TYPE_MAIN_VARIANT (var_type) != var_type)
    C_TYPE_INCOMPLETE_VARS (var_type) = 0;
  ಹಿಂತಿರುಗಿ var_type;
}

/* Build a VA_ARG_EXPR for the C parser.  */

ವೃಕ್ಷ
c_build_va_arg (location_t loc1, ವೃಕ್ಷ ಅಭಿವ್ಯಕ್ತಿ, location_t loc2, ವೃಕ್ಷ type,
		ವೃಕ್ಷ type_ಅಭಿವ್ಯಕ್ತಿ)
{
  ಆದರೆ (error_ಕಾರ್ಯಾಂಶ_p (type))
    ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
  /* VA_ARG_EXPR cannot be used for a scalar va_list with reverse storage
     order because it takes the address of the expression.  */
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (handled_component_p (ಅಭಿವ್ಯಕ್ತಿ)
	   && ಹಿಮ್ಮುಖ_storage_ಕ್ರಮ_for_component_p (ಅಭಿವ್ಯಕ್ತಿ))
    {
      error_at (loc1, "cannot use %<va_arg%> with reverse storage order");
      ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
    }
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!COMPLETE_TYPE_P (type))
    {
      error_at (loc2, "second argument to %<va_arg%> is of incomplete "
		"type %qT", type);
      ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
    }
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (type) == FUNCTION_TYPE)
    {
      error_at (loc2, "second argument to %<va_arg%> is a function type %qT",
		type);
      ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
    }
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (type) == ARRAY_TYPE && C_TYPE_VARIABLE_ಗಾತ್ರ (type)
	   && !flag_isoc99)
    {
      error_at (loc2, "second argument to %<va_arg%> is an array type %qT",
		type);
      ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
    }
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (warn_cxx_compat && ವೃಕ್ಷ_ಸಂಕೇತ (type) == ENUMERAL_TYPE)
    warning_at (loc2, OPT_Wc___compat,
		"C++ requires promoted type, not enum type, in %<va_arg%>");

  ಆದರೆ (flag_isoc99 && ವೃಕ್ಷ_ಸಂಕೇತ (type) == ARRAY_TYPE)
    {
      warning_at (loc2, 0, "second argument to %<va_arg%> is an array type %qT",
		  type);
      /* We create a trap but evaluate side effects first.  */
      ವೃಕ್ಷ trapfn = builtin_decl_explicit (BUILT_ಒಳ_TRAP);
      trapfn = build_call_ಅಭಿವ್ಯಕ್ತಿ_loc (loc2, trapfn, 0);
      ವೃಕ್ಷ e2 = build2 (COMPOUND_ಅಭಿವ್ಯಕ್ತಿ, void_type_ಗಂಟು, ಅಭಿವ್ಯಕ್ತಿ, trapfn);
      /* Return a compound literal of the right type.  */
      ವೃಕ್ಷ e1 = build_compound_literal (loc2, type, ಖಾಲಿ, ನಿಜ, 0, ಖಾಲಿ);
      ಅಭಿವ್ಯಕ್ತಿ = build2 (COMPOUND_ಅಭಿವ್ಯಕ್ತಿ, type, e2, e1);
    }
  ಇಲ್ಲದಿದ್ದರೆ
    ಅಭಿವ್ಯಕ್ತಿ = build_va_arg (loc2, ಅಭಿವ್ಯಕ್ತಿ, type);

  ಆದರೆ (type_ಅಭಿವ್ಯಕ್ತಿ)
    ಅಭಿವ್ಯಕ್ತಿ = build2 (COMPOUND_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ), type_ಅಭಿವ್ಯಕ್ತಿ, ಅಭಿವ್ಯಕ್ತಿ);

  ಹಿಂತಿರುಗಿ ಅಭಿವ್ಯಕ್ತಿ;
}

/* Return truthvalue of whether T1 is the same tree structure as T2.
   Return 1 if they are the same. Return false if they are different.  */

ತಾರ್ಕಿಕ
c_ವೃಕ್ಷ_equal (ವೃಕ್ಷ t1, ವೃಕ್ಷ t2)
{
  ಎಣಿಕೆ ವೃಕ್ಷ_ಸಂಕೇತ_2 code1, code2;

  ಆದರೆ (t1 == t2)
    ಹಿಂತಿರುಗಿ ನಿಜ;
  ಆದರೆ (!t1 || !t2)
    ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;

  ಗಾಗಿ (code1 = ವೃಕ್ಷ_ಸಂಕೇತ (t1); code1 == NON_LVALUE_ಅಭಿವ್ಯಕ್ತಿ;
       code1 = ವೃಕ್ಷ_ಸಂಕೇತ (t1))
    t1 = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (t1, 0);
  ಗಾಗಿ (code2 = ವೃಕ್ಷ_ಸಂಕೇತ (t2); code2 == NON_LVALUE_ಅಭಿವ್ಯಕ್ತಿ;
       code2 = ವೃಕ್ಷ_ಸಂಕೇತ (t2))
    t2 = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (t2, 0);

  /* They might have become equal now.  */
  ಆದರೆ (t1 == t2)
    ಹಿಂತಿರುಗಿ ನಿಜ;

  ಆದರೆ (code1 != code2)
    ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;

  ಆದರೆ (CONSTANT_CLASS_P (t1) && !comptypes (ವೃಕ್ಷ_TYPE (t1), ವೃಕ್ಷ_TYPE (t2)))
    ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;

  ಆಯ್ಕೆ (code1)
    {
    ಸ್ಥಿತಿ INTEGER_CST:
      ಹಿಂತಿರುಗಿ wi::ಗಮ್ಯ_wide (t1) == wi::ಗಮ್ಯ_wide (t2);

    ಸ್ಥಿತಿ REAL_CST:
      ಹಿಂತಿರುಗಿ real_equal (&ವೃಕ್ಷ_REAL_CST (t1), &ವೃಕ್ಷ_REAL_CST (t2));

    ಸ್ಥಿತಿ STRING_CST:
      ಹಿಂತಿರುಗಿ ವೃಕ್ಷ_STRING_ಉದ್ದಳತೆ (t1) == ವೃಕ್ಷ_STRING_ಉದ್ದಳತೆ (t2)
	&& !memcmp (ವೃಕ್ಷ_STRING_ಸೂಚಕ (t1), ವೃಕ್ಷ_STRING_ಸೂಚಕ (t2),
		    ವೃಕ್ಷ_STRING_ಉದ್ದಳತೆ (t1));

    ಸ್ಥಿತಿ FIXED_CST:
      ಹಿಂತಿರುಗಿ FIXED_ಮೌಲ್ಯಗಳು_IDENTICAL (ವೃಕ್ಷ_FIXED_CST (t1),
				     ವೃಕ್ಷ_FIXED_CST (t2));

    ಸ್ಥಿತಿ COMPLEX_CST:
      ಹಿಂತಿರುಗಿ c_ವೃಕ್ಷ_equal (ವೃಕ್ಷ_REALPART (t1), ವೃಕ್ಷ_REALPART (t2))
	     && c_ವೃಕ್ಷ_equal (ವೃಕ್ಷ_IMAGPART (t1), ವೃಕ್ಷ_IMAGPART (t2));

    ಸ್ಥಿತಿ ಸದಿಶ_CST:
      ಹಿಂತಿರುಗಿ ಕಾರ್ಯಾಂಶ_equal_p (t1, t2, OEP_ONLY_CONST);

    ಸ್ಥಿತಿ CONSTRUCTOR:
      /* We need to do this when determining whether or not two
	 non-type pointer to member function template arguments
	 are the same.  */
      ಆದರೆ (!comptypes (ವೃಕ್ಷ_TYPE (t1), ವೃಕ್ಷ_TYPE (t2))
	  || CONSTRUCTOR_NELTS (t1) != CONSTRUCTOR_NELTS (t2))
	ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
      {
	ವೃಕ್ಷ ಕ್ಷೇತ್ರ_2, ಮೌಲ್ಯ;
	ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ i;
	FOR_EACH_CONSTRUCTOR_ELT (CONSTRUCTOR_ELTS (t1), i, ಕ್ಷೇತ್ರ_2, ಮೌಲ್ಯ)
	  {
	    constructor_elt *elt2 = CONSTRUCTOR_ELT (t2, i);
	    ಆದರೆ (!c_ವೃಕ್ಷ_equal (ಕ್ಷೇತ್ರ_2, elt2->ಸೂಚ್ಯಂಕ)
		|| !c_ವೃಕ್ಷ_equal (ಮೌಲ್ಯ, elt2->ಮೌಲ್ಯ))
	      ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
	  }
      }
      ಹಿಂತಿರುಗಿ ನಿಜ;

    ಸ್ಥಿತಿ ವೃಕ್ಷ_LIST:
      ಆದರೆ (!c_ವೃಕ್ಷ_equal (ವೃಕ್ಷ_PURPOSE (t1), ವೃಕ್ಷ_PURPOSE (t2)))
	ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
      ಆದರೆ (!c_ವೃಕ್ಷ_equal (ವೃಕ್ಷ_ಮೌಲ್ಯ (t1), ವೃಕ್ಷ_ಮೌಲ್ಯ (t2)))
	ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
      ಹಿಂತಿರುಗಿ c_ವೃಕ್ಷ_equal (ವೃಕ್ಷ_CHAIN (t1), ವೃಕ್ಷ_CHAIN (t2));

    ಸ್ಥಿತಿ SAVE_ಅಭಿವ್ಯಕ್ತಿ:
      ಹಿಂತಿರುಗಿ c_ವೃಕ್ಷ_equal (ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (t1, 0), ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (t2, 0));

    ಸ್ಥಿತಿ CALL_ಅಭಿವ್ಯಕ್ತಿ:
      {
	ವೃಕ್ಷ arg1, arg2;
	call_ಅಭಿವ್ಯಕ್ತಿ_arg_iterator iter1, iter2;
	ಆದರೆ (!c_ವೃಕ್ಷ_equal (CALL_ಅಭಿವ್ಯಕ್ತಿ_FN (t1), CALL_ಅಭಿವ್ಯಕ್ತಿ_FN (t2)))
	  ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
	ಗಾಗಿ (arg1 = ಮೊದಲ_call_ಅಭಿವ್ಯಕ್ತಿ_arg (t1, &iter1),
	       arg2 = ಮೊದಲ_call_ಅಭಿವ್ಯಕ್ತಿ_arg (t2, &iter2);
	     arg1 && arg2;
	     arg1 = ಮುಂದಿನ_call_ಅಭಿವ್ಯಕ್ತಿ_arg (&iter1),
	       arg2 = ಮುಂದಿನ_call_ಅಭಿವ್ಯಕ್ತಿ_arg (&iter2))
	  ಆದರೆ (!c_ವೃಕ್ಷ_equal (arg1, arg2))
	    ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
	ಆದರೆ (arg1 || arg2)
	  ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
	ಹಿಂತಿರುಗಿ ನಿಜ;
      }

    ಸ್ಥಿತಿ ಗುರಿ_ಅಭಿವ್ಯಕ್ತಿ:
      {
	ವೃಕ್ಷ o1 = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (t1, 0);
	ವೃಕ್ಷ o2 = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (t2, 0);

	/* Special case: if either target is an unallocated VAR_DECL,
	   it means that it's going to be unified with whatever the
	   TARGET_EXPR is really supposed to initialize, so treat it
	   as being equivalent to anything.  */
	ಆದರೆ (VAR_P (o1) && DECL_NAME (o1) == NULL_ವೃಕ್ಷ
	    && !DECL_RTL_ಗಣ_P (o1))
	  /*Nop*/;
	ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (VAR_P (o2) && DECL_NAME (o2) == NULL_ವೃಕ್ಷ
		 && !DECL_RTL_ಗಣ_P (o2))
	  /*Nop*/;
	ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!c_ವೃಕ್ಷ_equal (o1, o2))
	  ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;

	ಹಿಂತಿರುಗಿ c_ವೃಕ್ಷ_equal (ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (t1, 1), ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (t2, 1));
      }

    ಸ್ಥಿತಿ COMPONENT_REF:
      ಆದರೆ (ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (t1, 1) != ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (t2, 1))
	ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
      ಹಿಂತಿರುಗಿ c_ವೃಕ್ಷ_equal (ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (t1, 0), ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (t2, 0));

    ಸ್ಥಿತಿ PARM_DECL:
    ಸ್ಥಿತಿ VAR_DECL:
    ಸ್ಥಿತಿ CONST_DECL:
    ಸ್ಥಿತಿ ಕ್ಷೇತ್ರ_DECL:
    ಸ್ಥಿತಿ FUNCTION_DECL:
    ಸ್ಥಿತಿ IDENTIFIER_ಗಂಟು:
    ಸ್ಥಿತಿ SSA_NAME:
      ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;

    ಸ್ಥಿತಿ ವೃಕ್ಷ_VEC:
      {
	ಚಿಹ್ನೆರಹಿತ ix;
	ಆದರೆ (ವೃಕ್ಷ_VEC_ಉದ್ದಳತೆ (t1) != ವೃಕ್ಷ_VEC_ಉದ್ದಳತೆ (t2))
	  ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
	ಗಾಗಿ (ix = ವೃಕ್ಷ_VEC_ಉದ್ದಳತೆ (t1); ix--;)
	  ಆದರೆ (!c_ವೃಕ್ಷ_equal (ವೃಕ್ಷ_VEC_ELT (t1, ix),
			     ವೃಕ್ಷ_VEC_ELT (t2, ix)))
	    ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
	ಹಿಂತಿರುಗಿ ನಿಜ;
      }

    CASE_CONVERT:
      ಆದರೆ (!comptypes (ವೃಕ್ಷ_TYPE (t1), ವೃಕ್ಷ_TYPE (t2)))
	ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
      ನಿಲ್ಲಿಸು;

    ಪೂರ್ವನಿಯೋಜಿತ:
      ನಿಲ್ಲಿಸು;
    }

  ಆಯ್ಕೆ (ವೃಕ್ಷ_ಸಂಕೇತ_CLASS (code1))
    {
    ಸ್ಥಿತಿ tcc_unary:
    ಸ್ಥಿತಿ tcc_ದ್ವಿಮಾನ:
    ಸ್ಥಿತಿ tcc_comparison:
    ಸ್ಥಿತಿ tcc_ಅಭಿವ್ಯಕ್ತಿ:
    ಸ್ಥಿತಿ tcc_vl_exp:
    ಸ್ಥಿತಿ tcc_reference:
    ಸ್ಥಿತಿ tcc_statement:
      {
	ಪೂರ್ಣಾಂಕ i, n = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ_ಉದ್ದಳತೆ (t1);

	ಆಯ್ಕೆ (code1)
	  {
	  ಸ್ಥಿತಿ PREINCREMENT_ಅಭಿವ್ಯಕ್ತಿ:
	  ಸ್ಥಿತಿ PREDECREMENT_ಅಭಿವ್ಯಕ್ತಿ:
	  ಸ್ಥಿತಿ POSTINCREMENT_ಅಭಿವ್ಯಕ್ತಿ:
	  ಸ್ಥಿತಿ POSTDECREMENT_ಅಭಿವ್ಯಕ್ತಿ:
	    n = 1;
	    ನಿಲ್ಲಿಸು;
	  ಸ್ಥಿತಿ ARRAY_REF:
	    n = 2;
	    ನಿಲ್ಲಿಸು;
	  ಪೂರ್ವನಿಯೋಜಿತ:
	    ನಿಲ್ಲಿಸು;
	  }

	ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ_CLASS (code1) == tcc_vl_exp
	    && n != ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ_ಉದ್ದಳತೆ (t2))
	  ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;

	ಗಾಗಿ (i = 0; i < n; ++i)
	  ಆದರೆ (!c_ವೃಕ್ಷ_equal (ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (t1, i), ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (t2, i)))
	    ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;

	ಹಿಂತಿರುಗಿ ನಿಜ;
      }

    ಸ್ಥಿತಿ tcc_type:
      ಹಿಂತಿರುಗಿ comptypes (t1, t2);
    ಪೂರ್ವನಿಯೋಜಿತ:
      gcc_unreachable ();
    }
}

/* Returns true when the function declaration FNDECL is implicit,
   introduced as a result of a call to an otherwise undeclared
   function, and false otherwise.  */

ತಾರ್ಕಿಕ
c_decl_implicit (const_ವೃಕ್ಷ fndecl)
{
  ಹಿಂತಿರುಗಿ C_DECL_IMPLICIT (fndecl);
}
