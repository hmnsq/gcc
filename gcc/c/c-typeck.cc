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

#ਅਨ੍ਤਰ੍ਭਾਵ "config.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "system.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "coretypes.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "memmodel.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "target.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "function.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "bitmap.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "c-tree.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "gimple-expr.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "predict.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "stor-layout.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "trans-mem.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "varasm.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "stmt.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "langhooks.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "c-lang.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "intl.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "tree-iterator.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "gimplify.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "tree-inline.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "omp-general.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "c-family/c-objc.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "c-family/c-ubsan.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "gomp-constants.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "spellcheck-tree.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "c-family/c-type-mismatch.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "stringpool.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "attribs.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "asan.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "realmpfr.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "tree-pretty-print-markup.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "gcc-urlifier.h"

/* Possible cases of implicit conversions.  Used to select diagnostic messages
   and control folding initializers in convert_for_assignment.  */
ਗਿਣਤੀ impl_conv {
  ic_argpass,
  ic_ਸੌਂਪੋ,
  ic_init,
  ic_init_const,
  ic_return
};

/* The level of nesting inside "__alignof__".  */
ਪੂਰਨ ਵਿੱਚ_alignof;

/* The level of nesting inside "sizeof".  */
ਪੂਰਨ ਵਿੱਚ_sizeof;

/* The level of nesting inside "countof".  */
ਪੂਰਨ ਵਿੱਚ_countof;

/* The level of nesting inside "typeof".  */
ਪੂਰਨ ਵਿੱਚ_typeof;

/* The level of nesting inside "_Generic".  */
ਪੂਰਨ ਵਿੱਚ_generic;

/* True when parsing OpenMP loop expressions.  */
ਤਾਰਕਿਕ c_ਵਿੱਚ_omp_for;

/* True when parsing OpenMP map clause.  */
ਤਾਰਕਿਕ c_omp_array_section_p;

/* The argument of last parsed sizeof expression, only to be tested
   if expr.original_code == SIZEOF_EXPR.  */
ਰੁੱਖ c_ਆਖਰੀ_sizeof_arg;
location_t c_ਆਖਰੀ_sizeof_loc;

/* Nonzero if we might need to print a "missing braces around
   initializer" message within this initializer.  */
ਸਥਿਰ ਪੂਰਨ ਮਿਲਿਆ_missing_braces;

ਸਥਿਰ ਤਾਰਕਿਕ require_constant_ਮੁੱਲ;
ਸਥਿਰ ਤਾਰਕਿਕ require_constant_elements;
ਸਥਿਰ ਤਾਰਕਿਕ require_constexpr_ਮੁੱਲ;

ਸਥਿਰ ਰੁੱਖ qualify_type (ਰੁੱਖ, ਰੁੱਖ);
ਬਣਤਰ comptypes_ਅੰਕੜੇ;
ਸਥਿਰ ਤਾਰਕਿਕ tagged_types_tu_compatible_p (const_ਰੁੱਖ, const_ਰੁੱਖ,
					  ਬਣਤਰ comptypes_ਅੰਕੜੇ *);
ਸਥਿਰ ਤਾਰਕਿਕ comp_ਨਿਸ਼ਾਨਾ_types (location_t, ਰੁੱਖ, ਰੁੱਖ);
ਸਥਿਰ ਤਾਰਕਿਕ function_types_compatible_p (const_ਰੁੱਖ, const_ਰੁੱਖ,
					 ਬਣਤਰ comptypes_ਅੰਕੜੇ *);
ਸਥਿਰ ਤਾਰਕਿਕ type_lists_compatible_p (const_ਰੁੱਖ, const_ਰੁੱਖ,
				     ਬਣਤਰ comptypes_ਅੰਕੜੇ *);
ਸਥਿਰ ਪੂਰਨ convert_arguments (location_t, vec<location_t>, ਰੁੱਖ,
			      vec<ਰੁੱਖ, va_gc> *, vec<ਰੁੱਖ, va_gc> *, ਰੁੱਖ,
			      ਰੁੱਖ);
ਸਥਿਰ ਰੁੱਖ ਸੂਚਕ_diff (location_t, ਰੁੱਖ, ਰੁੱਖ, ਰੁੱਖ *);
ਸਥਿਰ ਰੁੱਖ convert_for_assignment (location_t, location_t, ਰੁੱਖ, ਰੁੱਖ, ਰੁੱਖ,
				    ਗਿਣਤੀ impl_conv, ਤਾਰਕਿਕ, ਰੁੱਖ, ਰੁੱਖ, ਪੂਰਨ,
				    ਪੂਰਨ = 0);
ਸਥਿਰ ਰੁੱਖ valid_compound_ਵਿਅੰਜਕ_initializer (ਰੁੱਖ, ਰੁੱਖ);
ਸਥਿਰ ਖਾਲੀ ਧੱਕੋ_string (ਅਚਲ ਅੱਖਰ *);
ਸਥਿਰ ਖਾਲੀ ਧੱਕੋ_member_name (ਰੁੱਖ);
ਸਥਿਰ ਪੂਰਨ spelling_ਲੰਮਾਈ (ਖਾਲੀ);
ਸਥਿਰ ਅੱਖਰ *print_spelling (ਅੱਖਰ *);
ਸਥਿਰ ਖਾਲੀ warning_init (location_t, ਪੂਰਨ, ਅਚਲ ਅੱਖਰ *);
ਸਥਿਰ ਰੁੱਖ digest_init (location_t, ਰੁੱਖ, ਰੁੱਖ, ਰੁੱਖ, ਰੁੱਖ, ਤਾਰਕਿਕ, ਤਾਰਕਿਕ, ਤਾਰਕਿਕ,
			 ਤਾਰਕਿਕ, ਤਾਰਕਿਕ, ਤਾਰਕਿਕ);
ਸਥਿਰ ਖਾਲੀ output_init_element (location_t, ਰੁੱਖ, ਰੁੱਖ, ਤਾਰਕਿਕ, ਰੁੱਖ, ਰੁੱਖ, ਤਾਰਕਿਕ,
				 ਤਾਰਕਿਕ, ਬਣਤਰ obstack *);
ਸਥਿਰ ਖਾਲੀ output_pending_init_elements (ਪੂਰਨ, ਬਣਤਰ obstack *);
ਸਥਿਰ ਤਾਰਕਿਕ ਸੈੱਟ_designator (location_t, ਤਾਰਕਿਕ, ਬਣਤਰ obstack *);
ਸਥਿਰ ਖਾਲੀ ਧੱਕੋ_range_ਢੇਰ (ਰੁੱਖ, ਬਣਤਰ obstack *);
ਸਥਿਰ ਖਾਲੀ ਜੋੜੋ_pending_init (location_t, ਰੁੱਖ, ਰੁੱਖ, ਰੁੱਖ, ਤਾਰਕਿਕ,
			      ਬਣਤਰ obstack *);
ਸਥਿਰ ਖਾਲੀ ਸੈੱਟ_nonincremental_init (ਬਣਤਰ obstack *);
ਸਥਿਰ ਖਾਲੀ ਸੈੱਟ_nonincremental_init_from_string (ਰੁੱਖ, ਬਣਤਰ obstack *);
ਸਥਿਰ ਰੁੱਖ ਲੱਭੋ_init_member (ਰੁੱਖ, ਬਣਤਰ obstack *);
ਸਥਿਰ ਖਾਲੀ readonly_warning (ਰੁੱਖ, ਗਿਣਤੀ lvalue_use);
ਸਥਿਰ ਪੂਰਨ lvalue_or_else (location_t, const_ਰੁੱਖ, ਗਿਣਤੀ lvalue_use);
ਸਥਿਰ ਖਾਲੀ ਰਿਕਾਰਡ_maybe_ਵਰਤਿਆ_decl (ਰੁੱਖ, ਤਾਰਕਿਕ ਪਤਾ);
ਸਥਿਰ ਤਾਰਕਿਕ comptypes_ਅੰਦਰੂਨੀ (const_ਰੁੱਖ, const_ਰੁੱਖ,
				ਬਣਤਰ comptypes_ਅੰਕੜੇ *ਅੰਕੜੇ);
ਸਥਿਰ ਤਾਰਕਿਕ comptypes_check_for_ਸੰਯੁਕਤ (ਰੁੱਖ t1, ਰੁੱਖ t2);
ਸਥਿਰ ਤਾਰਕਿਕ handle_counted_by_p (ਰੁੱਖ);
ਸਥਿਰ ਤਾਰਕਿਕ ਸਿਖਰ_array_vla_p (const_ਰੁੱਖ type);


/* Return true if EXP is a null pointer constant, false otherwise.  */

ਤਾਰਕਿਕ
null_ਸੂਚਕ_constant_p (const_ਰੁੱਖ ਵਿਅੰਜਕ)
{
  /* This should really operate on c_expr structures, but they aren't
     yet available everywhere required.  */
  ਰੁੱਖ type = ਰੁੱਖ_TYPE (ਵਿਅੰਜਕ);

  /* An integer constant expression with the value 0, such an expression
     cast to type void*, or the predefined constant nullptr, are a null
     pointer constant.  */
  ਜੇ (ਵਿਅੰਜਕ == nullptr_ਗੰਢ)
    ਵਾਪਸ ਸੱਚ;

  ਵਾਪਸ (ਰੁੱਖ_ਕੋਡ (ਵਿਅੰਜਕ) == INTEGER_CST
	  && !ਰੁੱਖ_ਉਛਾਲ (ਵਿਅੰਜਕ)
	  && integer_zerop (ਵਿਅੰਜਕ)
	  && (INTEGRAL_TYPE_P (type)
	      || (ਰੁੱਖ_ਕੋਡ (type) == ਸੂਚਕ_TYPE
		  && VOID_TYPE_P (ਰੁੱਖ_TYPE (type))
		  && TYPE_QUALS (ਰੁੱਖ_TYPE (type)) == TYPE_UNQUALIFIED)));
}

/* EXPR may appear in an unevaluated part of an integer constant
   expression, but not in an evaluated part.  Wrap it in a
   C_MAYBE_CONST_EXPR, or mark it with TREE_OVERFLOW if it is just an
   INTEGER_CST and we cannot create a C_MAYBE_CONST_EXPR.  */

ਸਥਿਰ ਰੁੱਖ
note_integer_operands (ਰੁੱਖ ਵਿਅੰਜਕ)
{
  ਰੁੱਖ ret;
  ਜੇ (ਰੁੱਖ_ਕੋਡ (ਵਿਅੰਜਕ) == INTEGER_CST && ਵਿੱਚ_late_ਦੁਆਧਾਰੀ_op)
    {
      ret = copy_ਗੰਢ (ਵਿਅੰਜਕ);
      ਰੁੱਖ_ਉਛਾਲ (ret) = 1;
    }
  ਨਹੀਂਤਾਂ
    {
      ret = build2 (C_MAYBE_CONST_ਵਿਅੰਜਕ, ਰੁੱਖ_TYPE (ਵਿਅੰਜਕ), NULL_ਰੁੱਖ, ਵਿਅੰਜਕ);
      C_MAYBE_CONST_ਵਿਅੰਜਕ_INT_OPERANDS (ret) = 1;
    }
  ਵਾਪਸ ret;
}

/* Having checked whether EXPR may appear in an unevaluated part of an
   integer constant expression and found that it may, remove any
   C_MAYBE_CONST_EXPR noting this fact and return the resulting
   expression.  */

ਸਥਿਰ ਸਤਰਅੰਦਰ ਰੁੱਖ
remove_c_maybe_const_ਵਿਅੰਜਕ (ਰੁੱਖ ਵਿਅੰਜਕ)
{
  ਜੇ (ਰੁੱਖ_ਕੋਡ (ਵਿਅੰਜਕ) == C_MAYBE_CONST_ਵਿਅੰਜਕ)
    ਵਾਪਸ C_MAYBE_CONST_ਵਿਅੰਜਕ_ਵਿਅੰਜਕ (ਵਿਅੰਜਕ);
  ਨਹੀਂਤਾਂ
    ਵਾਪਸ ਵਿਅੰਜਕ;
}

/* This is a cache to hold if two types are seen.  */

ਬਣਤਰ tagged_tu_ਵੇਖਿਆ_cache {
  ਅਚਲ ਬਣਤਰ tagged_tu_ਵੇਖਿਆ_cache * ਅਗਲਾ;
  const_ਰੁੱਖ t1;
  const_ਰੁੱਖ t2;
};

/* Do `exp = require_complete_type (loc, exp);' to make sure exp
   does not have an incomplete type.  (That includes void types.)
   LOC is the location of the use.  */

ਰੁੱਖ
require_complete_type (location_t loc, ਰੁੱਖ ਮੁੱਲ)
{
  ਰੁੱਖ type = ਰੁੱਖ_TYPE (ਮੁੱਲ);

  ਜੇ (error_ਸੰਕਾਰਜ_p (ਮੁੱਲ))
    ਵਾਪਸ error_mark_ਗੰਢ;

  /* First, detect a valid value with a complete type.  */
  ਜੇ (COMPLETE_TYPE_P (type))
    ਵਾਪਸ ਮੁੱਲ;

  c_incomplete_type_error (loc, ਮੁੱਲ, type);
  ਵਾਪਸ error_mark_ਗੰਢ;
}

/* Print an error message for invalid use of an incomplete type.
   VALUE is the expression that was used (or 0 if that isn't known)
   and TYPE is the type that was invalid.  LOC is the location for
   the error.  */

ਖਾਲੀ
c_incomplete_type_error (location_t loc, const_ਰੁੱਖ ਮੁੱਲ, const_ਰੁੱਖ type)
{
  /* Avoid duplicate error message.  */
  ਜੇ (ਰੁੱਖ_ਕੋਡ (type) == ERROR_MARK)
    ਵਾਪਸ;

  ਜੇ (ਮੁੱਲ != NULL_ਰੁੱਖ && (VAR_P (ਮੁੱਲ) || ਰੁੱਖ_ਕੋਡ (ਮੁੱਲ) == PARM_DECL))
    error_at (loc, "%qD has an incomplete type %qT", ਮੁੱਲ, type);
  ਨਹੀਂਤਾਂ
    {
    retry:
      /* We must print an error message.  Be clever about what it says.  */

      ਚੋਣ (ਰੁੱਖ_ਕੋਡ (type))
	{
	ਹਾਲਤ ਰਿਕਾਰਡ_TYPE:
	ਹਾਲਤ UNION_TYPE:
	ਹਾਲਤ ENUMERAL_TYPE:
	  ਰੋਕੋ;

	ਹਾਲਤ VOID_TYPE:
	  error_at (loc, "invalid use of void expression");
	  ਵਾਪਸ;

	ਹਾਲਤ ARRAY_TYPE:
	  ਜੇ (TYPE_DOMAIN (type))
	    {
	      ਜੇ (flexible_array_member_type_p (type))
		{
		  error_at (loc, "invalid use of flexible array member");
		  ਵਾਪਸ;
		}
	      type = ਰੁੱਖ_TYPE (type);
	      ਜਾਓ retry;
	    }
	  error_at (loc, "invalid use of array with unspecified bounds");
	  ਵਾਪਸ;

	ਮੂਲ:
	  gcc_unreachable ();
	}

      ਜੇ (ਰੁੱਖ_ਕੋਡ (TYPE_NAME (type)) == IDENTIFIER_ਗੰਢ)
	error_at (loc, "invalid use of undefined type %qT", type);
      ਨਹੀਂਤਾਂ
	/* If this type has a typedef-name, the TYPE_NAME is a TYPE_DECL.  */
	error_at (loc, "invalid use of incomplete typedef %qT", type);
    }
}

/* Given a type, apply default promotions wrt unnamed function
   arguments and return the new type.  */

ਰੁੱਖ
c_type_promotes_ਮੰਜ਼ਿਲ (ਰੁੱਖ type)
{
  ਰੁੱਖ ret = NULL_ਰੁੱਖ;

  ਜੇ (TYPE_MAIN_VARIANT (type) == float_type_ਗੰਢ)
    ret = double_type_ਗੰਢ;
  ਨਹੀਂਤਾਂ ਜੇ (c_promoting_integer_type_p (type))
    {
      /* Preserve unsignedness if not really getting any wider.  */
      ਜੇ (TYPE_UNSIGNED (type)
	  && (TYPE_PRECISION (type) == TYPE_PRECISION (integer_type_ਗੰਢ)))
	ret = unsigned_type_ਗੰਢ;
      ਨਹੀਂਤਾਂ
	ret = integer_type_ਗੰਢ;
    }

  ਜੇ (ret != NULL_ਰੁੱਖ)
    ਵਾਪਸ (TYPE_ATOMIC (type)
	    ? c_build_qualified_type (ret, TYPE_QUAL_ATOMIC)
	    : ret);

  ਵਾਪਸ type;
}

/* Return true if between two named address spaces, whether there is a superset
   named address space that encompasses both address spaces.  If there is a
   superset, return which address space is the superset.  */

ਸਥਿਰ ਤਾਰਕਿਕ
addr_space_superset (addr_space_t as1, addr_space_t as2, addr_space_t *common)
{
  ਜੇ (as1 == as2)
    {
      *common = as1;
      ਵਾਪਸ ਸੱਚ;
    }
  ਨਹੀਂਤਾਂ ਜੇ (targetm.addr_space.subset_p (as1, as2))
    {
      *common = as2;
      ਵਾਪਸ ਸੱਚ;
    }
  ਨਹੀਂਤਾਂ ਜੇ (targetm.addr_space.subset_p (as2, as1))
    {
      *common = as1;
      ਵਾਪਸ ਸੱਚ;
    }
  ਨਹੀਂਤਾਂ
    ਵਾਪਸ ਝੂਠ;
}

/* Return a variant of TYPE which has all the type qualifiers of LIKE
   as well as those of TYPE.  */

ਸਥਿਰ ਰੁੱਖ
qualify_type (ਰੁੱਖ type, ਰੁੱਖ like)
{
  addr_space_t as_type = TYPE_ADDR_SPACE (type);
  addr_space_t as_like = TYPE_ADDR_SPACE (like);
  addr_space_t as_common;

  /* If the two named address spaces are different, determine the common
     superset address space.  If there isn't one, raise an error.  */
  ਜੇ (!addr_space_superset (as_type, as_like, &as_common))
    {
      as_common = as_type;
      error ("%qT and %qT are in disjoint named address spaces",
	     type, like);
    }

  ਵਾਪਸ c_build_qualified_type (type,
				 TYPE_QUALS_NO_ADDR_SPACE (type)
				 | TYPE_QUALS_NO_ADDR_SPACE_NO_ATOMIC (like)
				 | ENCODE_QUAL_ADDR_SPACE (as_common));
}


/* Check consistency of type TYPE.  For derived types, we test that
   C_TYPE_VARIABLE_SIZE and C_TYPE_VARIABLY_MODIFIED are consistent with
   the requirements of the base type.  We also check that arrays with a
   non-constant length are marked with C_TYPE_VARIABLE_SIZE. If any
   inconsistency is detected false is returned and true otherwise.  */

ਸਥਿਰ ਤਾਰਕਿਕ
c_verify_type (ਰੁੱਖ type)
{
  ਚੋਣ (ਰੁੱਖ_ਕੋਡ (type))
    {
    ਹਾਲਤ ਸੂਚਕ_TYPE:
    ਹਾਲਤ FUNCTION_TYPE:
    ਹਾਲਤ ARRAY_TYPE:
      /* Pointer, array, functions are variably modified if and only if the
	 target, element, return type is variably modified.  */
      ਜੇ (!TYPE_STRUCTURAL_EQUALITY_P (type)
	  && (C_TYPE_VARIABLY_MODIFIED (type)
	      != C_TYPE_VARIABLY_MODIFIED (ਰੁੱਖ_TYPE (type))))
	ਵਾਪਸ ਝੂਠ;
      /* If the target type is structural equality, the type should also. */
      ਜੇ (!TYPE_STRUCTURAL_EQUALITY_P (type)
	  && TYPE_STRUCTURAL_EQUALITY_P (ਰੁੱਖ_TYPE (type)))
	ਵਾਪਸ ਝੂਠ;
    ਮੂਲ:
       ਰੋਕੋ;
    }

  ਚੋਣ (ਰੁੱਖ_ਕੋਡ (type))
    {
    ਹਾਲਤ ਸੂਚਕ_TYPE:
    ਹਾਲਤ FUNCTION_TYPE:
      /* Pointer and functions can not have variable size.  */
      ਜੇ (C_TYPE_VARIABLE_ਮਾਪ (type))
	ਵਾਪਸ ਝੂਠ;
      ਰੋਕੋ;
    ਹਾਲਤ ARRAY_TYPE:
      /* An array has variable size if and only if it has a non-constant
	 dimensions or its element type has variable size.  */
      ਜੇ ((C_TYPE_VARIABLE_ਮਾਪ (ਰੁੱਖ_TYPE (type))
	   || ਸਿਖਰ_array_vla_p (type))
	  != C_TYPE_VARIABLE_ਮਾਪ (type))
	ਵਾਪਸ ਝੂਠ;
      /* If the element type or the array has variable size, then the
	 array has variable size and is variably modified.  */
      ਜੇ (C_TYPE_VARIABLE_ਮਾਪ (ਰੁੱਖ_TYPE (type))
	  || C_TYPE_VARIABLE_ਮਾਪ (type))
	{
	  ਜੇ (!C_TYPE_VARIABLE_ਮਾਪ (type))
	    ਵਾਪਸ ਝੂਠ;
	  ਜੇ (!C_TYPE_VARIABLY_MODIFIED (type))
	    ਵਾਪਸ ਝੂਠ;
	}

      /* va_list violates this, accept such types here.  */
      ਜੇ (!COMPLETE_TYPE_P (ਰੁੱਖ_TYPE (type)))
	ਵਾਪਸ ਸੱਚ;

      ਜੇ (COMPLETE_TYPE_P (type))
	{
	  /* If the size is unknown, it can not be complete.  */
	  ਜੇ (NULL_ਰੁੱਖ == TYPE_DOMAIN (type))
	    ਵਾਪਸ ਝੂਠ;

	  /* Zero-length arrays must have size zero.  */
	  ਜੇ (zero_ਲੰਮਾਈ_array_type_p (type)
	      && !integer_zerop (TYPE_ਮਾਪ (type)))
	    ਵਾਪਸ ਝੂਠ;
	}
      ਨਹੀਂਤਾਂ
	{
	  /* If not complete but has a domain, it must be a FAM.  */
	  ਜੇ (NULL_ਰੁੱਖ != TYPE_DOMAIN (type)
	      && !flexible_array_member_type_p (type))
	    ਵਾਪਸ ਝੂਠ;
	}
    ਮੂਲ:
      ਰੋਕੋ;
    }
  ਵਾਪਸ ਸੱਚ;
}

/* Propagate C_TYPE_VARIABLY_MODIFIED and C_TYPE_VARIABLE_SIZE
   from a base type to a newly built derived or qualified type.  */

ਸਥਿਰ ਰੁੱਖ
c_ਸੈੱਟ_type_ਬਿੱਟ (ਰੁੱਖ new_type, ਰੁੱਖ old_type)
{
  gcc_checking_assert (c_verify_type (old_type));

  ਜੇ (c_type_variably_modified_p (old_type))
    C_TYPE_VARIABLY_MODIFIED (new_type) = ਸੱਚ;

  ਜੇ (ਰੁੱਖ_ਕੋਡ (new_type) == ARRAY_TYPE && C_TYPE_VARIABLE_ਮਾਪ (old_type))
    {
      C_TYPE_VARIABLY_MODIFIED (new_type) = ਸੱਚ;
      C_TYPE_VARIABLE_ਮਾਪ (new_type) = ਸੱਚ;
    }
  ਵਾਪਸ new_type;
}

/* Build a pointer type using the default pointer mode.  */

ਰੁੱਖ
c_build_ਸੂਚਕ_type (ਰੁੱਖ ਮੰਜ਼ਿਲ_type)
{
  addr_space_t as = ਮੰਜ਼ਿਲ_type == error_mark_ਗੰਢ ? ADDR_SPACE_GENERIC
					       : TYPE_ADDR_SPACE (ਮੰਜ਼ਿਲ_type);
  machine_ਬਹੁਲਕ ਸੂਚਕ_ਬਹੁਲਕ;

  ਜੇ (as != ADDR_SPACE_GENERIC || c_default_ਸੂਚਕ_ਬਹੁਲਕ == VOIDmode)
    ਸੂਚਕ_ਬਹੁਲਕ = targetm.addr_space.ਸੂਚਕ_ਬਹੁਲਕ (as);
  ਨਹੀਂਤਾਂ
    ਸੂਚਕ_ਬਹੁਲਕ = c_default_ਸੂਚਕ_ਬਹੁਲਕ;

  ਵਾਪਸ c_build_ਸੂਚਕ_type_for_ਬਹੁਲਕ (ਮੰਜ਼ਿਲ_type, ਸੂਚਕ_ਬਹੁਲਕ, ਝੂਠ);
}

/* Build a pointer type using the given mode.  */

ਰੁੱਖ
c_build_ਸੂਚਕ_type_for_ਬਹੁਲਕ (ਰੁੱਖ type, machine_ਬਹੁਲਕ ਬਹੁਲਕ, ਤਾਰਕਿਕ m)
{
  ਰੁੱਖ ret = build_ਸੂਚਕ_type_for_ਬਹੁਲਕ (type, ਬਹੁਲਕ, m);
  ਵਾਪਸ c_ਸੈੱਟ_type_ਬਿੱਟ (ret, type);
}

/* Build a function type.  */

ਰੁੱਖ
c_build_function_type (ਰੁੱਖ type, ਰੁੱਖ ਦਲੀਲਾਂ, ਤਾਰਕਿਕ no)
{
  ਰੁੱਖ ret = build_function_type (type, ਦਲੀਲਾਂ, no);
  ਵਾਪਸ c_ਸੈੱਟ_type_ਬਿੱਟ (ret, type);
}

/* Build an array type.  This sets typeless storage as required
   by C2Y and C_TYPE_VARIABLY_MODIFIED and C_TYPE_VARIABLE_SIZE
   based on the element type and domain.  */

ਰੁੱਖ
c_build_array_type (ਰੁੱਖ type, ਰੁੱਖ domain)
{
  ਪੂਰਨ type_quals = TYPE_QUALS (type);

  /* Identify typeless storage as introduced in C2Y
     and supported also in earlier language modes.  */
  ਤਾਰਕਿਕ typeless = (char_type_p (type) && !(type_quals & TYPE_QUAL_ATOMIC))
		  || (AGGREGATE_TYPE_P (type) && TYPE_TYPELESS_STORAGE (type));

  ਰੁੱਖ ret = build_array_type (type, domain, typeless);

  ਜੇ (ਸਿਖਰ_array_vla_p (ret))
    {
      C_TYPE_VARIABLE_ਮਾਪ (ret) = 1;
      C_TYPE_VARIABLY_MODIFIED (ret) = 1;
    }

  ਵਾਪਸ c_ਸੈੱਟ_type_ਬਿੱਟ (ret, type);
}

/* Build an array type of unspecified size.  */
ਰੁੱਖ
c_build_array_type_unspecified (ਰੁੱਖ type)
{
  ਰੁੱਖ ਉੱਤਲਾ = build2 (COMPOUND_ਵਿਅੰਜਕ, ਰੁੱਖ_TYPE (ਮਾਪ_zero_ਗੰਢ),
		       integer_zero_ਗੰਢ, ਮਾਪ_zero_ਗੰਢ);
  ਵਾਪਸ c_build_array_type (type, build_ਸੂਚਕਾਂਕ_type (ਉੱਤਲਾ));
}

/* Build an array type of zero size.  */
ਰੁੱਖ
c_build_array_type_zero_ਮਾਪ (ਰੁੱਖ type)
{
  /* The GCC extension for zero-length arrays differs from
     ISO flexible array members in that sizeof yields
     zero.  */
  type = c_build_array_type (type, build_ਸੂਚਕਾਂਕ_type (NULL_ਰੁੱਖ));
  type = build_distinct_type_copy (TYPE_MAIN_VARIANT (type));
  TYPE_ਮਾਪ (type) = bitsize_zero_ਗੰਢ;
  TYPE_ਮਾਪ_UNIT (type) = ਮਾਪ_zero_ਗੰਢ;
  ਸੈੱਟ_TYPE_STRUCTURAL_EQUALITY (type);
  ਵਾਪਸ type;
}

ਰੁੱਖ
c_build_type_attribute_qual_variant (ਰੁੱਖ type, ਰੁੱਖ attrs, ਪੂਰਨ quals)
{
  ਰੁੱਖ ret = build_type_attribute_qual_variant (type, attrs, quals);
  ਵਾਪਸ c_ਸੈੱਟ_type_ਬਿੱਟ (ret, type);
}

ਰੁੱਖ
c_build_type_attribute_variant (ਰੁੱਖ type, ਰੁੱਖ attrs)
{
  ਵਾਪਸ c_build_type_attribute_qual_variant (type, attrs, TYPE_QUALS (type));
}

/* Reconstruct a complex derived type.  This is used to re-construct types
   with the vector attribute.  It is called via a langhook.  */

ਰੁੱਖ
c_reconstruct_complex_type (ਰੁੱਖ type, ਰੁੱਖ bottom)
{
  ਰੁੱਖ inner, outer;

  ਜੇ (ਰੁੱਖ_ਕੋਡ (type) == ਸੂਚਕ_TYPE)
    {
      inner = c_reconstruct_complex_type (ਰੁੱਖ_TYPE (type), bottom);
      outer = c_build_ਸੂਚਕ_type_for_ਬਹੁਲਕ (inner, TYPE_ਬਹੁਲਕ (type),
					     TYPE_REF_CAN_ALIAS_ALL (type));
    }
  ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਕੋਡ (type) == ARRAY_TYPE)
    {
      ਤਾਰਕਿਕ rso = TYPE_ਉਲਟ_STORAGE_ਕ੍ਰਮ (type);
      inner = c_reconstruct_complex_type (ਰੁੱਖ_TYPE (type), bottom);
      outer = c_build_array_type (inner, TYPE_DOMAIN (type));
      ਜੇ (rso)
	{
	  outer = build_distinct_type_copy (outer);
	  TYPE_ਉਲਟ_STORAGE_ਕ੍ਰਮ (outer) = 1;
	}

      gcc_checking_assert (C_TYPE_VARIABLE_ਮਾਪ (type)
			   == C_TYPE_VARIABLE_ਮਾਪ (outer));
    }
  ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਕੋਡ (type) == FUNCTION_TYPE)
    {
      inner = c_reconstruct_complex_type (ਰੁੱਖ_TYPE (type), bottom);
      outer = c_build_function_type (inner, TYPE_ARG_TYPES (type),
				     TYPE_NO_NAMED_ਦਲੀਲਾਂ_STDARG_P (type));
    }
  ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਕੋਡ (type) == REFERENCE_TYPE
	   || ਰੁੱਖ_ਕੋਡ (type) == ਵਿੱਥ_TYPE)
    gcc_unreachable ();
  ਨਹੀਂਤਾਂ
    ਵਾਪਸ bottom;

  ਵਾਪਸ c_build_type_attribute_qual_variant (outer, TYPE_ਗੁਣ (type),
					      TYPE_QUALS (type));
}


/* Helper function for c_canonical_type.  Check whether FIELD
   contains a pointer to a structure or union with tag,
   possibly nested in other type derivations, and return the
   type of this nested structure or union.  */
ਸਥਿਰ ਰੁੱਖ
ptr_ਮੰਜ਼ਿਲ_tagged_member (ਰੁੱਖ ਖੇਤਰ_2)
{
  gcc_assert (ਖੇਤਰ_DECL == ਰੁੱਖ_ਕੋਡ (ਖੇਤਰ_2));
  ਰੁੱਖ type = ਰੁੱਖ_TYPE (ਖੇਤਰ_2);
  ਤਾਰਕਿਕ ptr_ਵੇਖਿਆ = ਝੂਠ;
  ਜਦੋਂ (ਰੁੱਖ_ਕੋਡ (type) == ARRAY_TYPE
	 || ਰੁੱਖ_ਕੋਡ (type) == FUNCTION_TYPE
	 || ਰੁੱਖ_ਕੋਡ (type) == ਸੂਚਕ_TYPE)
    {
      ਜੇ (ਰੁੱਖ_ਕੋਡ (type) == ਸੂਚਕ_TYPE)
	ptr_ਵੇਖਿਆ = ਸੱਚ;
      type = ਰੁੱਖ_TYPE (type);
    }

  ਜੇ (ptr_ਵੇਖਿਆ
      && ਰਿਕਾਰਡ_OR_UNION_TYPE_P (type)
      && NULL_ਰੁੱਖ != c_type_ਟੈਗ (type))
    ਵਾਪਸ type;

  ਵਾਪਸ NULL_ਰੁੱਖ;
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
ਰੁੱਖ
c_type_canonical (ਰੁੱਖ type)
{
  gcc_assert (ਰਿਕਾਰਡ_OR_UNION_TYPE_P (type));

  ਤਾਰਕਿਕ needs_mod = ਝੂਠ;
  ਲਈ (ਰੁੱਖ x = TYPE_FIELDS (type); x; x = DECL_CHAIN (x))
    {
      ਜੇ (!ptr_ਮੰਜ਼ਿਲ_tagged_member (x))
	ਜਾਰੀ;
      needs_mod = ਸੱਚ;
      ਰੋਕੋ;
    }
  ਜੇ (!needs_mod)
    ਵਾਪਸ type;

  /* Construct new version with such members replaced.  */
  ਰੁੱਖ n = build_distinct_type_copy (type);
  ਰੁੱਖ *fields = &TYPE_FIELDS (n);
  ਲਈ (ਰੁੱਖ x = TYPE_FIELDS (type); x; x = DECL_CHAIN (x))
    {
      ਰੁੱਖ f = copy_ਗੰਢ (x);
      ਜੇ (ਰੁੱਖ m = ptr_ਮੰਜ਼ਿਲ_tagged_member (x))
	{
	  ਰੁੱਖ new_ਗੰਢ = make_ਗੰਢ (ਰੁੱਖ_ਕੋਡ (m));
	  TYPE_NAME (new_ਗੰਢ) = TYPE_NAME (m);
	  ਸੈੱਟ_TYPE_STRUCTURAL_EQUALITY (new_ਗੰਢ);
	  new_ਗੰਢ = qualify_type (new_ਗੰਢ, m);
	  ਰੁੱਖ_TYPE (f) = c_reconstruct_complex_type (ਰੁੱਖ_TYPE (x),
						      new_ਗੰਢ);
	}
      *fields = f;
      fields = &DECL_CHAIN (f);
    }
  TYPE_CANONICAL (n) = n;
  ਵਾਪਸ n;
}


/* If NTYPE is a type of a non-variadic function with a prototype
   and OTYPE is a type of a function without a prototype and ATTRS
   contains attribute format, diagnosess and removes it from ATTRS.
   Returns the result of build_type_attribute_variant of NTYPE and
   the (possibly) modified ATTRS.  */

ਸਥਿਰ ਰੁੱਖ
c_build_functype_attribute_variant (ਰੁੱਖ ntype, ਰੁੱਖ otype, ਰੁੱਖ attrs)
{
  ਜੇ (!prototype_p (otype)
      && prototype_p (ntype)
      && lookup_attribute ("format", attrs))
    {
      warning_at (ਨਿਵੇਸ਼_location, OPT_Wattributes,
		  "%qs attribute can only be applied to variadic functions",
		  "format");
      attrs = remove_attribute ("format", attrs);
    }
  ਵਾਪਸ c_build_type_attribute_variant (ntype, attrs);

}

/* Given a type which could be a typedef name, make sure to return the
   original type.  See set_underlying_type. */
ਸਥਿਰ const_ਰੁੱਖ
c_type_original (const_ਰੁੱਖ t)
{
  /* It may even be a typedef of a typedef...
     In the case of compiler-created builtin structs the TYPE_DECL
     may be a dummy, with no DECL_ORIGINAL_TYPE.  Don't fault.  */
  ਜਦੋਂ (TYPE_NAME (t)
	 && ਰੁੱਖ_ਕੋਡ (TYPE_NAME (t)) == TYPE_DECL
	 && DECL_ORIGINAL_TYPE (TYPE_NAME (t)))
    t = DECL_ORIGINAL_TYPE (TYPE_NAME (t));
  ਵਾਪਸ t;
}

/* Return the tag for a tagged type.  */
ਰੁੱਖ
c_type_ਟੈਗ (const_ਰੁੱਖ t)
{
  gcc_assert (ਰਿਕਾਰਡ_OR_UNION_TYPE_P (t) || ਰੁੱਖ_ਕੋਡ (t) == ENUMERAL_TYPE);
  const_ਰੁੱਖ orig = c_type_original (t);
  ਰੁੱਖ name = TYPE_NAME (orig);
  ਜੇ (!name)
    ਵਾਪਸ NULL_ਰੁੱਖ;
  ਜੇ (ਰੁੱਖ_ਕੋਡ (name) == TYPE_DECL)
    {
      ਜੇ (!DECL_NAME (name))
	ਵਾਪਸ NULL_ਰੁੱਖ;
      name = DECL_NAME (name);
    }
  gcc_checking_assert (ਰੁੱਖ_ਕੋਡ (name) == IDENTIFIER_ਗੰਢ);
  ਵਾਪਸ name;
}

/* Remove qualifiers but not atomic.  For arrays remove qualifiers
   on the element type but also do not remove atomic.  */
ਸਥਿਰ ਰੁੱਖ
remove_qualifiers (ਰੁੱਖ t)
{
  ਜੇ (!t || t == error_mark_ਗੰਢ)
    ਵਾਪਸ t;
  ਵਾਪਸ TYPE_ATOMIC (strip_array_types (t))
	 ? c_build_qualified_type (TYPE_MAIN_VARIANT (t), TYPE_QUAL_ATOMIC)
	 : TYPE_MAIN_VARIANT (t);
}


/* Helper function for composite_type_internal.  Find a compatible type
   in a (transparent) union U compatible to T.  If found, return the
   type of the corresponding member.  Otherwise, return the union type U.  */
ਸਥਿਰ ਰੁੱਖ
transparent_union_replacement (ਰੁੱਖ u, ਰੁੱਖ t)
{
  ਜੇ (u == error_mark_ਗੰਢ || t == error_mark_ਗੰਢ
      || ਰੁੱਖ_ਕੋਡ (u) != UNION_TYPE
      || !(TYPE_TRANSPARENT_AGGR (u) || TYPE_NAME (u) == NULL_ਰੁੱਖ)
      || comptypes (u, t))
    ਵਾਪਸ u;

  ਲਈ (ਰੁੱਖ memb = TYPE_FIELDS (u); memb; memb = DECL_CHAIN (memb))
    {
      ਰੁੱਖ m = remove_qualifiers (ਰੁੱਖ_TYPE (memb));
      ਜੇ (comptypes (m, t))
	{
	  pedwarn (ਨਿਵੇਸ਼_location, OPT_Wpedantic,
		    "function types not truly compatible in ISO C");
	  ਵਾਪਸ m;
	}
    }

  ਵਾਪਸ u;
}



/* Return the composite type of two compatible types.

   We assume that comptypes has already been done and returned
   nonzero; if that isn't so, this may crash.  In particular, we
   assume that qualifiers match.  */

ਬਣਤਰ ਸੰਯੁਕਤ_cache {
  ਰੁੱਖ t1;
  ਰੁੱਖ t2;
  ਰੁੱਖ ਸੰਯੁਕਤ;
  ਬਣਤਰ ਸੰਯੁਕਤ_cache* ਅਗਲਾ;
};

ਰੁੱਖ
ਸੰਯੁਕਤ_type_ਅੰਦਰੂਨੀ (ਰੁੱਖ t1, ਰੁੱਖ t2, ਰੁੱਖ cond,
			 ਬਣਤਰ ਸੰਯੁਕਤ_cache* cache)
{
  ਗਿਣਤੀ ਰੁੱਖ_ਕੋਡ_2 code1;
  ਗਿਣਤੀ ਰੁੱਖ_ਕੋਡ_2 code2;
  ਰੁੱਖ ਗੁਣ;

  /* Save time if the two types are the same.  */

  ਜੇ (t1 == t2) ਵਾਪਸ t1;

  /* If one type is nonsense, use the other.  */
  ਜੇ (t1 == error_mark_ਗੰਢ)
    ਵਾਪਸ t2;
  ਜੇ (t2 == error_mark_ਗੰਢ)
    ਵਾਪਸ t1;

  code1 = ਰੁੱਖ_ਕੋਡ (t1);
  code2 = ਰੁੱਖ_ਕੋਡ (t2);

  /* Merge the attributes.  */
  ਗੁਣ = targetm.ਮਿਲਾਓ_type_ਗੁਣ (t1, t2);

  /* If one is an enumerated type and the other is the compatible
     integer type, the composite type might be either of the two
     (DR#013 question 3).  For consistency, use the enumerated type as
     the composite type.  */

  ਜੇ (code1 == ENUMERAL_TYPE
      && (code2 == INTEGER_TYPE
	  || code2 == BOOLEAN_TYPE))
    ਵਾਪਸ t1;
  ਜੇ (code2 == ENUMERAL_TYPE
      && (code1 == INTEGER_TYPE
	  || code1 == BOOLEAN_TYPE))
    ਵਾਪਸ t2;

  gcc_assert (code1 == code2);

  ਚੋਣ (code1)
    {
    ਹਾਲਤ ਸੂਚਕ_TYPE:
      /* For two pointers, do this recursively on the target type.  */
      {
	gcc_checking_assert (TYPE_QUALS (t1) == TYPE_QUALS (t2));
	ਰੁੱਖ ਨਿਸ਼ਾਨਾ = ਸੰਯੁਕਤ_type_ਅੰਦਰੂਨੀ (ਰੁੱਖ_TYPE (t1), ਰੁੱਖ_TYPE (t2),
					       cond, cache);
	ਰੁੱਖ n = c_build_ਸੂਚਕ_type_for_ਬਹੁਲਕ (ਨਿਸ਼ਾਨਾ, TYPE_ਬਹੁਲਕ (t1), ਝੂਠ);
	ਵਾਪਸ c_build_type_attribute_qual_variant (n, ਗੁਣ,
						    TYPE_QUALS (t2));
      }

    ਹਾਲਤ ARRAY_TYPE:
      {
	ਰੁੱਖ d1 = TYPE_DOMAIN (t1);
	ਰੁੱਖ d2 = TYPE_DOMAIN (t2);

	/* We should not have any type quals on arrays at all.  */
	gcc_assert (!TYPE_QUALS_NO_ADDR_SPACE (t1)
		    && !TYPE_QUALS_NO_ADDR_SPACE (t2));

	ਤਾਰਕਿਕ d1_zero = zero_ਲੰਮਾਈ_array_type_p (t1)
		       || flexible_array_member_type_p (t1);
	ਤਾਰਕਿਕ d2_zero = zero_ਲੰਮਾਈ_array_type_p (t2)
		       || flexible_array_member_type_p (t2);

	ਤਾਰਕਿਕ d1_variable = ਸਿਖਰ_array_vla_p (t1);
	ਤਾਰਕਿਕ d2_variable = ਸਿਖਰ_array_vla_p (t2);

	ਤਾਰਕਿਕ use1 = d1 && (d2_variable || !d2 || d2_zero || !d1_variable);
	ਤਾਰਕਿਕ use2 = d2 && (d1_variable || !d1 || d1_zero || !d2_variable);

	/* If the first is an unspecified size pick the other one.  */
	ਜੇ (d2_variable && c_type_unspecified_p (t1))
	  {
	    gcc_assert (use1 && use2);
	    use1 = ਝੂਠ;
	  }

	/* If both are VLAs but not unspecified and we are in the
	   conditional operator, we create a conditional to select
	   the size of the active branch.  */
	ਤਾਰਕਿਕ use0 = cond && d1_variable && !c_type_unspecified_p (t1)
			 && d2_variable && !c_type_unspecified_p (t2);

	ਰੁੱਖ td;
	ਰੁੱਖ elt = ਸੰਯੁਕਤ_type_ਅੰਦਰੂਨੀ (ਰੁੱਖ_TYPE (t1), ਰੁੱਖ_TYPE (t2),
					    cond, cache);

	ਜੇ (!use0)
	  {
	    /* Save space: see if the result is identical to one of the args.  */
	    ਜੇ (elt == ਰੁੱਖ_TYPE (t1) && use1)
	      ਵਾਪਸ c_build_type_attribute_variant (t1, ਗੁਣ);
	    ਜੇ (elt == ਰੁੱਖ_TYPE (t2) && use2)
	      ਵਾਪਸ c_build_type_attribute_variant (t2, ਗੁਣ);

	    ਜੇ (elt == ਰੁੱਖ_TYPE (t1) && !TYPE_DOMAIN (t2) && !TYPE_DOMAIN (t1))
	      ਵਾਪਸ c_build_type_attribute_variant (t1, ਗੁਣ);
	    ਜੇ (elt == ਰੁੱਖ_TYPE (t2) && !TYPE_DOMAIN (t2) && !TYPE_DOMAIN (t1))
	      ਵਾਪਸ c_build_type_attribute_variant (t2, ਗੁਣ);

	    td = TYPE_DOMAIN (use1 ? t1 : t2);
	  }
	ਨਹੀਂਤਾਂ
	  {
	    /* Not used in C.  */
	    gcc_assert (ਮਾਪ_zero_ਗੰਢ == TYPE_MIN_ਮੁੱਲ (d1));
	    gcc_assert (ਮਾਪ_zero_ਗੰਢ == TYPE_MIN_ਮੁੱਲ (d2));

	    ਰੁੱਖ d = fold_build3_loc (UNKNOWN_LOCATION, COND_ਵਿਅੰਜਕ, sizetype,
				      cond, TYPE_MAX_ਮੁੱਲ (d1),
				      TYPE_MAX_ਮੁੱਲ (d2));

	    td = build_ਸੂਚਕਾਂਕ_type (d);
	  }

	/* Merge the element types, and have a size if either arg has
	   one.  We may have qualifiers on the element types.  To set
	   up TYPE_MAIN_VARIANT correctly, we need to form the
	   composite of the unqualified types and add the qualifiers
	   back at the end.  */
	ਪੂਰਨ quals = TYPE_QUALS (strip_array_types (elt));
	ਰੁੱਖ unqual_elt = c_build_qualified_type (elt, TYPE_UNQUALIFIED);

	ਜੇ ((!d1 || d1_zero) && (!d2 || d2_zero) && (d1 || d2))
	  t1 = c_build_array_type_zero_ਮਾਪ (unqual_elt);
	ਨਹੀਂਤਾਂ
	  t1 = c_build_array_type (unqual_elt, td);

	/* Check that a type which has a varying outermost dimension
	   got marked as having a variable size.  */
	ਤਾਰਕਿਕ varsize = (d1_variable && d2_variable)
		       || (d1_variable && !d2)
		       || (d2_variable && !d1);
	gcc_checking_assert (!varsize || C_TYPE_VARIABLE_ਮਾਪ (t1));

	t1 = c_build_qualified_type (t1, quals);
	ਵਾਪਸ c_build_type_attribute_variant (t1, ਗੁਣ);
      }

    ਹਾਲਤ ਰਿਕਾਰਡ_TYPE:
    ਹਾਲਤ UNION_TYPE:
      ਜੇ (flag_isoc23 && !comptypes_same_p (t1, t2))
	{
	  /* Go to the original type to get the right tag.  */
	  ਰੁੱਖ ਟੈਗ = c_type_ਟੈਗ (t1);

	  gcc_checking_assert (COMPLETE_TYPE_P (t1) && COMPLETE_TYPE_P (t2));
	  gcc_checking_assert (!ਟੈਗ || comptypes (t1, t2));

	  /* If a composite type for these two types is already under
	     construction, return it.  */

	  ਲਈ (ਬਣਤਰ ਸੰਯੁਕਤ_cache *c = cache; c != ਨਿਰਾ; c = c->ਅਗਲਾ)
	    ਜੇ ((c->t1 == t1 && c->t2 == t2) || (c->t1 == t2 && c->t2 == t1))
	       ਵਾਪਸ c->ਸੰਯੁਕਤ;

	  /* Otherwise, create a new type node and link it into the cache.  */

	  ਰੁੱਖ n = make_ਗੰਢ (code1);
	  ਸੈੱਟ_TYPE_STRUCTURAL_EQUALITY (n);
	  TYPE_NAME (n) = ਟੈਗ;

	  ਬਣਤਰ ਸੰਯੁਕਤ_cache cache2 = { t1, t2, n, cache };
	  cache = &cache2;

	  ਰੁੱਖ f1 = TYPE_FIELDS (t1);
	  ਰੁੱਖ f2 = TYPE_FIELDS (t2);
	  ਰੁੱਖ fields = NULL_ਰੁੱਖ;

	  ਲਈ (ਰੁੱਖ a = f1, b = f2; a && b;
	       a = DECL_CHAIN (a), b = DECL_CHAIN (b))
	    {
	      ਰੁੱਖ ta = ਰੁੱਖ_TYPE (a);
	      ਰੁੱਖ tb = ਰੁੱਖ_TYPE (b);

	      ਜੇ (DECL_C_ਦੋਆਧਾਰੀ_ਅੰਕ_ਖੇਤਰ (a))
		{
		  ta = DECL_ਦੋਆਧਾਰੀ_ਅੰਕ_ਖੇਤਰ_TYPE (a);
		  tb = DECL_ਦੋਆਧਾਰੀ_ਅੰਕ_ਖੇਤਰ_TYPE (b);
		}

	      gcc_assert (DECL_NAME (a) == DECL_NAME (b));
	      gcc_checking_assert (!DECL_NAME (a) || comptypes (ta, tb));

	      ਰੁੱਖ t = ਸੰਯੁਕਤ_type_ਅੰਦਰੂਨੀ (ta, tb, cond, cache);
	      ਰੁੱਖ f = build_decl (ਨਿਵੇਸ਼_location, ਖੇਤਰ_DECL, DECL_NAME (a), t);

	      DECL_PACKED (f) = DECL_PACKED (a);
	      ਸੈੱਟ_DECL_ALIGN (f, DECL_ALIGN (a));
	      DECL_ਗੁਣ (f) = DECL_ਗੁਣ (a);
	      C_DECL_VARIABLE_ਮਾਪ (f) = C_TYPE_VARIABLE_ਮਾਪ (t);

	      decl_ਗੁਣ (&f, DECL_ਗੁਣ (f), 0);

	      ਅੰਤ_decl (f, ਨਿਵੇਸ਼_location, ਨਿਰਾ, ਨਿਰਾ, ਨਿਰਾ);

	      ਜੇ (DECL_C_ਦੋਆਧਾਰੀ_ਅੰਕ_ਖੇਤਰ (a))
		{
		  /* This will be processed by finish_struct.  */
		  ਸੈੱਟ_DECL_C_ਦੋਆਧਾਰੀ_ਅੰਕ_ਖੇਤਰ (f);
		  DECL_INITIAL (f) = build_int_cst (integer_type_ਗੰਢ,
						    ਰੁੱਖ_ਮੰਜ਼ਿਲ_uhwi (DECL_ਮਾਪ (a)));
		  DECL_NONADDRESSABLE_P (f) = ਸੱਚ;
		  DECL_PADDING_P (f) = !DECL_NAME (a);
		}

	      DECL_CHAIN (f) = fields;
	      fields = f;
	    }

	  fields = nreverse (fields);

	  /* Setup the struct/union type.  Because we inherit all variably
	     modified components, we can ignore the size expression.  */
	  ਰੁੱਖ ਵਿਅੰਜਕ = NULL_ਰੁੱਖ;

	  /* Set TYPE_STUB_DECL for debugging symbols.  */
	  TYPE_STUB_DECL (n) = pushdecl (build_decl (ਨਿਵੇਸ਼_location, TYPE_DECL,
						     NULL_ਰੁੱਖ, n));

	  n = ਅੰਤ_struct (ਨਿਵੇਸ਼_location, n, fields, ਗੁਣ, ਨਿਰਾ,
			     &ਵਿਅੰਜਕ);

	  ਵਾਪਸ qualify_type (n, t1);
	}
      /* FALLTHRU */
    ਹਾਲਤ ENUMERAL_TYPE:
      ਜੇ (ਗੁਣ != ਨਿਰਾ)
	{
	  /* Try harder not to create a new aggregate type.  */
	  ਜੇ (attribute_list_equal (TYPE_ਗੁਣ (t1), ਗੁਣ))
	    ਵਾਪਸ t1;
	  ਜੇ (attribute_list_equal (TYPE_ਗੁਣ (t2), ਗੁਣ))
	    ਵਾਪਸ t2;
	}
      ਵਾਪਸ c_build_type_attribute_variant (t1, ਗੁਣ);

    ਹਾਲਤ FUNCTION_TYPE:
      /* Function types: prefer the one that specified arg types.
	 If both do, merge the arg types.  Also merge the return types.  */
      {
	ਰੁੱਖ valtype = ਸੰਯੁਕਤ_type_ਅੰਦਰੂਨੀ (ਰੁੱਖ_TYPE (t1), ਰੁੱਖ_TYPE (t2),
						cond, cache);
	ਰੁੱਖ p1 = TYPE_ARG_TYPES (t1);
	ਰੁੱਖ p2 = TYPE_ARG_TYPES (t2);

	/* Save space: see if the result is identical to one of the args.  */
	ਜੇ (valtype == ਰੁੱਖ_TYPE (t1) && !TYPE_ARG_TYPES (t2))
	  ਵਾਪਸ c_build_functype_attribute_variant (t1, t2, ਗੁਣ);
	ਜੇ (valtype == ਰੁੱਖ_TYPE (t2) && !TYPE_ARG_TYPES (t1))
	  ਵਾਪਸ c_build_functype_attribute_variant (t2, t1, ਗੁਣ);

	/* Simple way if one arg fails to specify argument types.  */
	ਜੇ (TYPE_ARG_TYPES (t1) == NULL_ਰੁੱਖ)
	  {
	    t1 = c_build_function_type (valtype, TYPE_ARG_TYPES (t2),
					TYPE_NO_NAMED_ਦਲੀਲਾਂ_STDARG_P (t2));
	    t1 = c_build_type_attribute_variant (t1, ਗੁਣ);
	    ਵਾਪਸ qualify_type (t1, t2);
	 }
	ਜੇ (TYPE_ARG_TYPES (t2) == NULL_ਰੁੱਖ)
	  {
	    t1 = c_build_function_type (valtype, TYPE_ARG_TYPES (t1),
					TYPE_NO_NAMED_ਦਲੀਲਾਂ_STDARG_P (t1));
	    t1 = c_build_type_attribute_variant (t1, ਗੁਣ);
	    ਵਾਪਸ qualify_type (t1, t2);
	  }

	/* If both args specify argument types, we must merge the two
	   lists, argument by argument.  */
	ਰੁੱਖ newargs = NULL_ਰੁੱਖ;
	ਰੁੱਖ *endp = &newargs;

	ਲਈ (; p1; p1 = ਰੁੱਖ_CHAIN (p1), p2 = ਰੁੱਖ_CHAIN (p2))
	  {
	    ਜੇ (p1 == void_list_ਗੰਢ)
	      {
		*endp = void_list_ਗੰਢ;
		ਰੋਕੋ;
	      }
	    ਰੁੱਖ mv1 = remove_qualifiers (ਰੁੱਖ_ਮੁੱਲ (p1));
	    ਰੁੱਖ mv2 = remove_qualifiers (ਰੁੱਖ_ਮੁੱਲ (p2));

	    gcc_assert (mv1);
	    gcc_assert (mv2);

	    mv1 = transparent_union_replacement (mv1, mv2);
	    mv2 = transparent_union_replacement (mv2, mv1);

	    *endp = ਰੁੱਖ_cons (NULL_ਰੁੱਖ,
			       ਸੰਯੁਕਤ_type_ਅੰਦਰੂਨੀ (mv1, mv2, cond, cache),
			       NULL_ਰੁੱਖ);

	    endp = &ਰੁੱਖ_CHAIN (*endp);
	  }

	t1 = c_build_function_type (valtype, newargs);
	t1 = qualify_type (t1, t2);
      }
      /* FALLTHRU */

    ਮੂਲ:
      ਵਾਪਸ c_build_type_attribute_variant (t1, ਗੁਣ);
    }
}

ਰੁੱਖ
ਸੰਯੁਕਤ_type_cond (ਰੁੱਖ t1, ਰੁੱਖ t2, ਰੁੱਖ cond)
{
  gcc_checking_assert (comptypes_check_for_ਸੰਯੁਕਤ (t1, t2));

  ਬਣਤਰ ਸੰਯੁਕਤ_cache cache = { };
  ਰੁੱਖ n = ਸੰਯੁਕਤ_type_ਅੰਦਰੂਨੀ (t1, t2, cond, &cache);

  gcc_checking_assert (comptypes_check_for_ਸੰਯੁਕਤ (n, t1));
  gcc_checking_assert (comptypes_check_for_ਸੰਯੁਕਤ (n, t2));
  ਵਾਪਸ n;
}


ਰੁੱਖ
ਸੰਯੁਕਤ_type (ਰੁੱਖ t1, ਰੁੱਖ t2)
{
  ਵਾਪਸ ਸੰਯੁਕਤ_type_cond (t1, t2, NULL_ਰੁੱਖ);
}

/* Return the type of a conditional expression between pointers to
   possibly differently qualified versions of compatible types.

   We assume that comp_target_types has already been done and returned
   true; if that isn't so, this may crash.  */

ਸਥਿਰ ਰੁੱਖ
common_ਸੂਚਕ_type (ਰੁੱਖ t1, ਰੁੱਖ t2, ਰੁੱਖ cond)
{
  ਰੁੱਖ ਗੁਣ;
  ਬਿਨਾਨਿਸ਼ਾਨੀ ਨਿਸ਼ਾਨਾ_quals;
  addr_space_t as1, as2, as_common;
  ਪੂਰਨ quals1, quals2;

  /* Save time if the two types are the same.  */

  ਜੇ (t1 == t2) ਵਾਪਸ t1;

  /* If one type is nonsense, use the other.  */
  ਜੇ (t1 == error_mark_ਗੰਢ)
    ਵਾਪਸ t2;
  ਜੇ (t2 == error_mark_ਗੰਢ)
    ਵਾਪਸ t1;

  gcc_assert (ਰੁੱਖ_ਕੋਡ (t1) == ਸੂਚਕ_TYPE
	      && ਰੁੱਖ_ਕੋਡ (t2) == ਸੂਚਕ_TYPE);

  /* Merge the attributes.  */
  ਗੁਣ = targetm.ਮਿਲਾਓ_type_ਗੁਣ (t1, t2);

  /* Find the composite type of the target types, and combine the
     qualifiers of the two types' targets.  */
  ਰੁੱਖ pointed_ਮੰਜ਼ਿਲ_1 = ਰੁੱਖ_TYPE (t1);
  ਰੁੱਖ pointed_ਮੰਜ਼ਿਲ_2 = ਰੁੱਖ_TYPE (t2);
  ਰੁੱਖ ਨਿਸ਼ਾਨਾ = ਸੰਯੁਕਤ_type_cond (TYPE_MAIN_VARIANT (pointed_ਮੰਜ਼ਿਲ_1),
				     TYPE_MAIN_VARIANT (pointed_ਮੰਜ਼ਿਲ_2), cond);

  /* Strip array types to get correct qualifier for pointers to arrays */
  quals1 = TYPE_QUALS_NO_ADDR_SPACE (strip_array_types (pointed_ਮੰਜ਼ਿਲ_1));
  quals2 = TYPE_QUALS_NO_ADDR_SPACE (strip_array_types (pointed_ਮੰਜ਼ਿਲ_2));

  /* For function types do not merge const qualifiers, but drop them
     if used inconsistently.  The middle-end uses these to mark const
     and noreturn functions.  */
  ਜੇ (ਰੁੱਖ_ਕੋਡ (pointed_ਮੰਜ਼ਿਲ_1) == FUNCTION_TYPE)
    ਨਿਸ਼ਾਨਾ_quals = (quals1 & quals2);
  ਨਹੀਂਤਾਂ
    ਨਿਸ਼ਾਨਾ_quals = (quals1 | quals2);

  /* If the two named address spaces are different, determine the common
     superset address space.  This is guaranteed to exist due to the
     assumption that comp_target_type returned true.  */
  as1 = TYPE_ADDR_SPACE (pointed_ਮੰਜ਼ਿਲ_1);
  as2 = TYPE_ADDR_SPACE (pointed_ਮੰਜ਼ਿਲ_2);
  ਜੇ (!addr_space_superset (as1, as2, &as_common))
    gcc_unreachable ();

  ਨਿਸ਼ਾਨਾ_quals |= ENCODE_QUAL_ADDR_SPACE (as_common);

  t1 = c_build_ਸੂਚਕ_type (c_build_qualified_type (ਨਿਸ਼ਾਨਾ, ਨਿਸ਼ਾਨਾ_quals));
  ਵਾਪਸ c_build_type_attribute_variant (t1, ਗੁਣ);
}

/* Return the common type for two arithmetic types under the usual
   arithmetic conversions.  The default conversions have already been
   applied, and enumerated types converted to their compatible integer
   types.  The resulting type is unqualified and has no attributes.

   This is the type for the result of most arithmetic operations
   if the operands have the given two types.  */

ਸਥਿਰ ਰੁੱਖ
c_common_type (ਰੁੱਖ t1, ਰੁੱਖ t2)
{
  ਗਿਣਤੀ ਰੁੱਖ_ਕੋਡ_2 code1;
  ਗਿਣਤੀ ਰੁੱਖ_ਕੋਡ_2 code2;

  /* If one type is nonsense, use the other.  */
  ਜੇ (t1 == error_mark_ਗੰਢ)
    ਵਾਪਸ t2;
  ਜੇ (t2 == error_mark_ਗੰਢ)
    ਵਾਪਸ t1;

  ਜੇ (TYPE_QUALS (t1) != TYPE_UNQUALIFIED)
    t1 = TYPE_MAIN_VARIANT (t1);

  ਜੇ (TYPE_QUALS (t2) != TYPE_UNQUALIFIED)
    t2 = TYPE_MAIN_VARIANT (t2);

  ਜੇ (TYPE_ਗੁਣ (t1) != NULL_ਰੁੱਖ)
    {
      ਰੁੱਖ attrs = affects_type_ਪਛਾਣ_ਤੱਤ_ਗੁਣ (TYPE_ਗੁਣ (t1));
      t1 = c_build_type_attribute_variant (t1, attrs);
    }

  ਜੇ (TYPE_ਗੁਣ (t2) != NULL_ਰੁੱਖ)
    {
      ਰੁੱਖ attrs = affects_type_ਪਛਾਣ_ਤੱਤ_ਗੁਣ (TYPE_ਗੁਣ (t2));
      t2 = c_build_type_attribute_variant (t2, attrs);
    }

  /* Save time if the two types are the same.  */

  ਜੇ (t1 == t2) ਵਾਪਸ t1;

  code1 = ਰੁੱਖ_ਕੋਡ (t1);
  code2 = ਰੁੱਖ_ਕੋਡ (t2);

  gcc_assert (code1 == ਸਦਿਸ਼_TYPE || code1 == COMPLEX_TYPE
	      || code1 == FIXED_ਬਿੰਦੂ_TYPE || code1 == REAL_TYPE
	      || code1 == INTEGER_TYPE || code1 == BITINT_TYPE);
  gcc_assert (code2 == ਸਦਿਸ਼_TYPE || code2 == COMPLEX_TYPE
	      || code2 == FIXED_ਬਿੰਦੂ_TYPE || code2 == REAL_TYPE
	      || code2 == INTEGER_TYPE || code2 == BITINT_TYPE);

  /* When one operand is a decimal float type, the other operand cannot be
     a generic float type or a complex type.  We also disallow vector types
     here.  */
  ਜੇ ((DECIMAL_FLOAT_TYPE_P (t1) || DECIMAL_FLOAT_TYPE_P (t2))
      && !(DECIMAL_FLOAT_TYPE_P (t1) && DECIMAL_FLOAT_TYPE_P (t2)))
    {
      ਜੇ (code1 == ਸਦਿਸ਼_TYPE || code2 == ਸਦਿਸ਼_TYPE)
	{
	  error ("cannot mix operands of decimal floating and vector types");
	  ਵਾਪਸ error_mark_ਗੰਢ;
	}
      ਜੇ (code1 == COMPLEX_TYPE || code2 == COMPLEX_TYPE)
	{
	  error ("cannot mix operands of decimal floating and complex types");
	  ਵਾਪਸ error_mark_ਗੰਢ;
	}
      ਜੇ (code1 == REAL_TYPE && code2 == REAL_TYPE)
	{
	  error ("cannot mix operands of decimal floating "
		 "and other floating types");
	  ਵਾਪਸ error_mark_ਗੰਢ;
	}
    }

  /* If one type is a vector type, return that type.  (How the usual
     arithmetic conversions apply to the vector types extension is not
     precisely specified.)  */
  ਜੇ (code1 == ਸਦਿਸ਼_TYPE)
    ਵਾਪਸ t1;

  ਜੇ (code2 == ਸਦਿਸ਼_TYPE)
    ਵਾਪਸ t2;

  /* If one type is complex, form the common type of the non-complex
     components, then make that complex.  Use T1 or T2 if it is the
     required type.  */
  ਜੇ (code1 == COMPLEX_TYPE || code2 == COMPLEX_TYPE)
    {
      ਰੁੱਖ subtype1 = code1 == COMPLEX_TYPE ? ਰੁੱਖ_TYPE (t1) : t1;
      ਰੁੱਖ subtype2 = code2 == COMPLEX_TYPE ? ਰੁੱਖ_TYPE (t2) : t2;
      ਰੁੱਖ subtype = c_common_type (subtype1, subtype2);

      ਜੇ (code1 == COMPLEX_TYPE && ਰੁੱਖ_TYPE (t1) == subtype)
	ਵਾਪਸ t1;
      ਨਹੀਂਤਾਂ ਜੇ (code2 == COMPLEX_TYPE && ਰੁੱਖ_TYPE (t2) == subtype)
	ਵਾਪਸ t2;
      ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਕੋਡ (subtype) == BITINT_TYPE)
	{
	  sorry ("%<_Complex _BitInt(%d)%> unsupported",
		 TYPE_PRECISION (subtype));
	  ਵਾਪਸ code1 == COMPLEX_TYPE ? t1 : t2;
	}
      ਨਹੀਂਤਾਂ
	ਵਾਪਸ build_complex_type (subtype);
    }

  /* If only one is real, use it as the result.  */

  ਜੇ (code1 == REAL_TYPE && code2 != REAL_TYPE)
    ਵਾਪਸ t1;

  ਜੇ (code2 == REAL_TYPE && code1 != REAL_TYPE)
    ਵਾਪਸ t2;

  /* If both are real and either are decimal floating point types, use
     the decimal floating point type with the greater precision. */

  ਜੇ (code1 == REAL_TYPE && code2 == REAL_TYPE)
    {
      ਜੇ (TYPE_MAIN_VARIANT (t1) == dfloat128_type_ਗੰਢ
	  || TYPE_MAIN_VARIANT (t2) == dfloat128_type_ਗੰਢ)
	ਵਾਪਸ dfloat128_type_ਗੰਢ;
      /* And prefer _Decimal128 over _Decimal64x which has in GCC's
	 implementation the same mode.  */
      ਨਹੀਂਤਾਂ ਜੇ (TYPE_MAIN_VARIANT (t1) == dfloat64x_type_ਗੰਢ
	       || TYPE_MAIN_VARIANT (t2) == dfloat64x_type_ਗੰਢ)
	ਵਾਪਸ dfloat64x_type_ਗੰਢ;
      ਨਹੀਂਤਾਂ ਜੇ (TYPE_MAIN_VARIANT (t1) == dfloat64_type_ਗੰਢ
	       || TYPE_MAIN_VARIANT (t2) == dfloat64_type_ਗੰਢ)
	ਵਾਪਸ dfloat64_type_ਗੰਢ;
      ਨਹੀਂਤਾਂ ਜੇ (TYPE_MAIN_VARIANT (t1) == dfloat32_type_ਗੰਢ
	       || TYPE_MAIN_VARIANT (t2) == dfloat32_type_ਗੰਢ)
	ਵਾਪਸ dfloat32_type_ਗੰਢ;
    }

  /* Deal with fixed-point types.  */
  ਜੇ (code1 == FIXED_ਬਿੰਦੂ_TYPE || code2 == FIXED_ਬਿੰਦੂ_TYPE)
    {
      ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ unsignedp = 0, satp = 0;
      scalar_ਬਹੁਲਕ m1, m2;
      ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ fbit1, ibit1, fbit2, ibit2, max_fbit, max_ibit;

      m1 = SCALAR_TYPE_ਬਹੁਲਕ (t1);
      m2 = SCALAR_TYPE_ਬਹੁਲਕ (t2);

      /* If one input type is saturating, the result type is saturating.  */
      ਜੇ (TYPE_SATURATING (t1) || TYPE_SATURATING (t2))
	satp = 1;

      /* If both fixed-point types are unsigned, the result type is unsigned.
	 When mixing fixed-point and integer types, follow the sign of the
	 fixed-point type.
	 Otherwise, the result type is signed.  */
      ਜੇ ((TYPE_UNSIGNED (t1) && TYPE_UNSIGNED (t2)
	   && code1 == FIXED_ਬਿੰਦੂ_TYPE && code2 == FIXED_ਬਿੰਦੂ_TYPE)
	  || (code1 == FIXED_ਬਿੰਦੂ_TYPE && code2 != FIXED_ਬਿੰਦੂ_TYPE
	      && TYPE_UNSIGNED (t1))
	  || (code1 != FIXED_ਬਿੰਦੂ_TYPE && code2 == FIXED_ਬਿੰਦੂ_TYPE
	      && TYPE_UNSIGNED (t2)))
	unsignedp = 1;

      /* The result type is signed.  */
      ਜੇ (unsignedp == 0)
	{
	  /* If the input type is unsigned, we need to convert to the
	     signed type.  */
	  ਜੇ (code1 == FIXED_ਬਿੰਦੂ_TYPE && TYPE_UNSIGNED (t1))
	    {
	      ਗਿਣਤੀ ਬਹੁਲਕ_class mclass = (ਗਿਣਤੀ ਬਹੁਲਕ_class) 0;
	      ਜੇ (GET_ਬਹੁਲਕ_CLASS (m1) == ਬਹੁਲਕ_UFRACT)
		mclass = ਬਹੁਲਕ_FRACT;
	      ਨਹੀਂਤਾਂ ਜੇ (GET_ਬਹੁਲਕ_CLASS (m1) == ਬਹੁਲਕ_UACCUM)
		mclass = ਬਹੁਲਕ_ACCUM;
	      ਨਹੀਂਤਾਂ
		gcc_unreachable ();
	      m1 = as_a <scalar_ਬਹੁਲਕ>
		(ਬਹੁਲਕ_for_ਮਾਪ (GET_ਬਹੁਲਕ_PRECISION (m1), mclass, 0));
	    }
	  ਜੇ (code2 == FIXED_ਬਿੰਦੂ_TYPE && TYPE_UNSIGNED (t2))
	    {
	      ਗਿਣਤੀ ਬਹੁਲਕ_class mclass = (ਗਿਣਤੀ ਬਹੁਲਕ_class) 0;
	      ਜੇ (GET_ਬਹੁਲਕ_CLASS (m2) == ਬਹੁਲਕ_UFRACT)
		mclass = ਬਹੁਲਕ_FRACT;
	      ਨਹੀਂਤਾਂ ਜੇ (GET_ਬਹੁਲਕ_CLASS (m2) == ਬਹੁਲਕ_UACCUM)
		mclass = ਬਹੁਲਕ_ACCUM;
	      ਨਹੀਂਤਾਂ
		gcc_unreachable ();
	      m2 = as_a <scalar_ਬਹੁਲਕ>
		(ਬਹੁਲਕ_for_ਮਾਪ (GET_ਬਹੁਲਕ_PRECISION (m2), mclass, 0));
	    }
	}

      ਜੇ (code1 == FIXED_ਬਿੰਦੂ_TYPE)
	{
	  fbit1 = GET_ਬਹੁਲਕ_FBIT (m1);
	  ibit1 = GET_ਬਹੁਲਕ_IBIT (m1);
	}
      ਨਹੀਂਤਾਂ
	{
	  fbit1 = 0;
	  /* Signed integers need to subtract one sign bit.  */
	  ibit1 = TYPE_PRECISION (t1) - (!TYPE_UNSIGNED (t1));
	}

      ਜੇ (code2 == FIXED_ਬਿੰਦੂ_TYPE)
	{
	  fbit2 = GET_ਬਹੁਲਕ_FBIT (m2);
	  ibit2 = GET_ਬਹੁਲਕ_IBIT (m2);
	}
      ਨਹੀਂਤਾਂ
	{
	  fbit2 = 0;
	  /* Signed integers need to subtract one sign bit.  */
	  ibit2 = TYPE_PRECISION (t2) - (!TYPE_UNSIGNED (t2));
	}

      max_ibit = ibit1 >= ibit2 ?  ibit1 : ibit2;
      max_fbit = fbit1 >= fbit2 ?  fbit1 : fbit2;
      ਵਾਪਸ c_common_fixed_ਬਿੰਦੂ_type_for_ਮਾਪ (max_ibit, max_fbit, unsignedp,
						 satp);
    }

  /* Both real or both integers; use the one with greater precision.  */

  ਜੇ (TYPE_PRECISION (t1) > TYPE_PRECISION (t2))
    ਵਾਪਸ t1;
  ਨਹੀਂਤਾਂ ਜੇ (TYPE_PRECISION (t2) > TYPE_PRECISION (t1))
    ਵਾਪਸ t2;

  /* Same precision.  Prefer long longs to longs to ints when the
     same precision, following the C99 rules on integer type rank
     (which are equivalent to the C90 rules for C90 types).  */

  ਜੇ (TYPE_MAIN_VARIANT (t1) == long_long_unsigned_type_ਗੰਢ
      || TYPE_MAIN_VARIANT (t2) == long_long_unsigned_type_ਗੰਢ)
    ਵਾਪਸ long_long_unsigned_type_ਗੰਢ;

  ਜੇ (TYPE_MAIN_VARIANT (t1) == long_long_integer_type_ਗੰਢ
      || TYPE_MAIN_VARIANT (t2) == long_long_integer_type_ਗੰਢ)
    {
      ਜੇ (TYPE_UNSIGNED (t1) || TYPE_UNSIGNED (t2))
	ਵਾਪਸ long_long_unsigned_type_ਗੰਢ;
      ਨਹੀਂਤਾਂ
	ਵਾਪਸ long_long_integer_type_ਗੰਢ;
    }

  ਜੇ (TYPE_MAIN_VARIANT (t1) == long_unsigned_type_ਗੰਢ
      || TYPE_MAIN_VARIANT (t2) == long_unsigned_type_ਗੰਢ)
    ਵਾਪਸ long_unsigned_type_ਗੰਢ;

  ਜੇ (TYPE_MAIN_VARIANT (t1) == long_integer_type_ਗੰਢ
      || TYPE_MAIN_VARIANT (t2) == long_integer_type_ਗੰਢ)
    {
      /* But preserve unsignedness from the other type,
	 since long cannot hold all the values of an unsigned int.  */
      ਜੇ (TYPE_UNSIGNED (t1) || TYPE_UNSIGNED (t2))
	ਵਾਪਸ long_unsigned_type_ਗੰਢ;
      ਨਹੀਂਤਾਂ
	ਵਾਪਸ long_integer_type_ਗੰਢ;
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
  ਰੁੱਖ mv1 = TYPE_MAIN_VARIANT (t1);
  ਰੁੱਖ mv2 = TYPE_MAIN_VARIANT (t2);

  ਲਈ (ਪੂਰਨ i = ਅੰਕ_FLOATN_TYPES - 1; i >= 0; i--)
    ਜੇ (mv1 == FLOATN_TYPE_ਗੰਢ (i) || mv2 == FLOATN_TYPE_ਗੰਢ (i))
      ਵਾਪਸ FLOATN_TYPE_ਗੰਢ (i);

  /* Likewise, prefer long double to double even if same size.  */
  ਜੇ (mv1 == long_double_type_ਗੰਢ || mv2 == long_double_type_ਗੰਢ)
    ਵਾਪਸ long_double_type_ਗੰਢ;

  /* Likewise, prefer double to float even if same size.
     We got a couple of embedded targets with 32 bit doubles, and the
     pdp11 might have 64 bit floats.  */
  ਜੇ (mv1 == double_type_ਗੰਢ || mv2 == double_type_ਗੰਢ)
    ਵਾਪਸ double_type_ਗੰਢ;

  ਜੇ (mv1 == float_type_ਗੰਢ || mv2 == float_type_ਗੰਢ)
    ਵਾਪਸ float_type_ਗੰਢ;

  ਲਈ (ਪੂਰਨ i = ਅੰਕ_FLOATNX_TYPES - 1; i >= 0; i--)
    ਜੇ (mv1 == FLOATNX_TYPE_ਗੰਢ (i) || mv2 == FLOATNX_TYPE_ਗੰਢ (i))
      ਵਾਪਸ FLOATNX_TYPE_ਗੰਢ (i);

  ਜੇ ((code1 == BITINT_TYPE || code2 == BITINT_TYPE) && code1 != code2)
    {
      /* Prefer any other integral types over bit-precise integer types.  */
      ਜੇ (TYPE_UNSIGNED (t1) == TYPE_UNSIGNED (t2))
	ਵਾਪਸ code1 == BITINT_TYPE ? t2 : t1;
      /* If BITINT_TYPE is unsigned and the other type is signed
	 non-BITINT_TYPE with the same precision, the latter has higher rank.
	 In that case:
	 Otherwise, both operands are converted to the unsigned integer type
	 corresponding to the type of the operand with signed integer type.  */
      ਜੇ (TYPE_UNSIGNED (code1 == BITINT_TYPE ? t1 : t2))
	ਵਾਪਸ c_common_unsigned_type (code1 == BITINT_TYPE ? t2 : t1);
    }

  /* Otherwise prefer the unsigned one.  */

  ਜੇ (TYPE_UNSIGNED (t1))
    ਵਾਪਸ t1;
  ਨਹੀਂਤਾਂ
    ਵਾਪਸ t2;
}

/* Wrapper around c_common_type that is used by c-common.cc and other
   front end optimizations that remove promotions.  ENUMERAL_TYPEs
   are allowed here and are converted to their compatible integer types.
   BOOLEAN_TYPEs are allowed here and return either boolean_type_node or
   preferably a non-Boolean type as the common type.  */
ਰੁੱਖ
common_type (ਰੁੱਖ t1, ਰੁੱਖ t2)
{
  ਜੇ (ਰੁੱਖ_ਕੋਡ (t1) == ENUMERAL_TYPE)
    t1 = ENUM_UNDERLYING_TYPE (t1);
  ਜੇ (ਰੁੱਖ_ਕੋਡ (t2) == ENUMERAL_TYPE)
    t2 = ENUM_UNDERLYING_TYPE (t2);

  /* If both types are BOOLEAN_TYPE, then return boolean_type_node.  */
  ਜੇ (ਰੁੱਖ_ਕੋਡ (t1) == BOOLEAN_TYPE
      && ਰੁੱਖ_ਕੋਡ (t2) == BOOLEAN_TYPE)
    ਵਾਪਸ boolean_type_ਗੰਢ;

  /* If either type is BOOLEAN_TYPE, then return the other.  */
  ਜੇ (ਰੁੱਖ_ਕੋਡ (t1) == BOOLEAN_TYPE)
    ਵਾਪਸ t2;
  ਜੇ (ਰੁੱਖ_ਕੋਡ (t2) == BOOLEAN_TYPE)
    ਵਾਪਸ t1;

  ਵਾਪਸ c_common_type (t1, t2);
}



/* Helper function for comptypes.  For two compatible types, return 1
   if they pass consistency checks.  In particular we test that
   TYPE_CANONICAL is set correctly, i.e. the two types can alias.  */

ਸਥਿਰ ਤਾਰਕਿਕ
comptypes_verify (ਰੁੱਖ type1, ਰੁੱਖ type2)
{
  ਜੇ (type1 == type2 || !type1 || !type2
      || ਰੁੱਖ_ਕੋਡ (type1) == ERROR_MARK || ਰੁੱਖ_ਕੋਡ (type2) == ERROR_MARK)
    ਵਾਪਸ ਸੱਚ;

  gcc_checking_assert (c_verify_type (type1));
  gcc_checking_assert (c_verify_type (type2));

  ਜੇ (TYPE_CANONICAL (type1) != TYPE_CANONICAL (type2)
      && !TYPE_STRUCTURAL_EQUALITY_P (type1)
      && !TYPE_STRUCTURAL_EQUALITY_P (type2))
    {
      /* FIXME: check other types. */
      ਜੇ (ਰਿਕਾਰਡ_OR_UNION_TYPE_P (type1)
	  || ਰੁੱਖ_ਕੋਡ (type1) == ENUMERAL_TYPE
	  || ਰੁੱਖ_ਕੋਡ (type2) == ENUMERAL_TYPE)
	ਵਾਪਸ ਝੂਠ;
    }
  ਵਾਪਸ ਸੱਚ;
}

ਬਣਤਰ comptypes_ਅੰਕੜੇ {

  /* output */
  ਤਾਰਕਿਕ enum_and_int_p;
  ਤਾਰਕਿਕ different_types_p;
  ਤਾਰਕਿਕ warning_needed;

  /* context */
  ਤਾਰਕਿਕ anon_ਖੇਤਰ;
  ਤਾਰਕਿਕ pointedto;

  /* configuration */
  ਤਾਰਕਿਕ equiv;
  ਤਾਰਕਿਕ ignore_promoting_ਦਲੀਲਾਂ;

  ਅਚਲ ਬਣਤਰ tagged_tu_ਵੇਖਿਆ_cache* cache;
};


/* Helper function for composite_type.  This function ignores when the
   function type of an old-style declaration is incompatible with a type
   of a declaration with prototype because some are arguments are not
   self-promoting.  This is ignored only for function types but not
   ignored in a nested context.  */

ਸਥਿਰ ਤਾਰਕਿਕ
comptypes_check_for_ਸੰਯੁਕਤ (ਰੁੱਖ t1, ਰੁੱਖ t2)
{
  ਬਣਤਰ comptypes_ਅੰਕੜੇ ਅੰਕੜੇ = { };
  ਅੰਕੜੇ.ignore_promoting_ਦਲੀਲਾਂ = FUNCTION_TYPE == ਰੁੱਖ_ਕੋਡ (t1);
  ਵਾਪਸ comptypes_ਅੰਦਰੂਨੀ (t1, t2, &ਅੰਕੜੇ);
}


/* C implementation of compatible_types_for_indirection_note_p.  */

ਤਾਰਕਿਕ
compatible_types_for_indirection_note_p (ਰੁੱਖ type1, ਰੁੱਖ type2)
{
  ਵਾਪਸ comptypes (type1, type2);
}

/* Return true if TYPE1 and TYPE2 are compatible types for assignment
   or various other operations.  */

ਤਾਰਕਿਕ
comptypes (ਰੁੱਖ type1, ਰੁੱਖ type2)
{
  ਬਣਤਰ comptypes_ਅੰਕੜੇ ਅੰਕੜੇ = { };
  ਤਾਰਕਿਕ ret = comptypes_ਅੰਦਰੂਨੀ (type1, type2, &ਅੰਕੜੇ);

  gcc_checking_assert (!ret || comptypes_verify (type1, type2));

  ਵਾਪਸ ret;
}


/* Like comptypes, but it returns non-zero only for identical
   types.  */

ਤਾਰਕਿਕ
comptypes_same_p (ਰੁੱਖ type1, ਰੁੱਖ type2)
{
  ਬਣਤਰ comptypes_ਅੰਕੜੇ ਅੰਕੜੇ = { };
  ਤਾਰਕਿਕ ret = comptypes_ਅੰਦਰੂਨੀ (type1, type2, &ਅੰਕੜੇ);

  gcc_checking_assert (!ret || comptypes_verify (type1, type2));

  ਜੇ (ਅੰਕੜੇ.different_types_p)
    ਵਾਪਸ ਝੂਠ;

  ਵਾਪਸ ret;
}


/* Like comptypes, but if it returns true because enum and int are
   compatible, it sets *ENUM_AND_INT_P to true.  */

ਤਾਰਕਿਕ
comptypes_check_enum_int (ਰੁੱਖ type1, ਰੁੱਖ type2, ਤਾਰਕਿਕ *enum_and_int_p)
{
  ਬਣਤਰ comptypes_ਅੰਕੜੇ ਅੰਕੜੇ = { };
  ਤਾਰਕਿਕ ret = comptypes_ਅੰਦਰੂਨੀ (type1, type2, &ਅੰਕੜੇ);
  *enum_and_int_p = ਅੰਕੜੇ.enum_and_int_p;

  gcc_checking_assert (!ret || comptypes_verify (type1, type2));

  ਵਾਪਸ ret;
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

ਤਾਰਕਿਕ
comptypes_equiv_p (ਰੁੱਖ type1, ਰੁੱਖ type2)
{
  ਬਣਤਰ comptypes_ਅੰਕੜੇ ਅੰਕੜੇ = { };
  ਅੰਕੜੇ.equiv = ਸੱਚ;
  ਤਾਰਕਿਕ ret = comptypes_ਅੰਦਰੂਨੀ (type1, type2, &ਅੰਕੜੇ);

  /* check that different equivance classes are assigned only
     to types that are not compatible.  */
  gcc_checking_assert (ret || !comptypes (type1, type2));

  ਵਾਪਸ ret;
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

ਸਥਿਰ ਤਾਰਕਿਕ
comptypes_ਅੰਦਰੂਨੀ (const_ਰੁੱਖ type1, const_ਰੁੱਖ type2,
		    ਬਣਤਰ comptypes_ਅੰਕੜੇ *ਅੰਕੜੇ)
{
  const_ਰੁੱਖ t1 = type1;
  const_ਰੁੱਖ t2 = type2;

  /* Suppress errors caused by previously reported errors.  */

  ਜੇ (t1 == t2 || !t1 || !t2
      || ਰੁੱਖ_ਕੋਡ (t1) == ERROR_MARK || ਰੁੱਖ_ਕੋਡ (t2) == ERROR_MARK)
    ਵਾਪਸ ਸੱਚ;

  /* Qualifiers must match. C99 6.7.3p9 */

  ਜੇ (TYPE_QUALS (t1) != TYPE_QUALS (t2))
    ਵਾਪਸ ਝੂਠ;

  /* Enumerated types are compatible with integer types, but this is
     not transitive: two enumerated types in the same translation unit
     are compatible with each other only if they are the same type.  */

  ਜੇ (ਰੁੱਖ_ਕੋਡ (t1) == ENUMERAL_TYPE
      && COMPLETE_TYPE_P (t1)
      && ਰੁੱਖ_ਕੋਡ (t2) != ENUMERAL_TYPE)
    {
      t1 = ENUM_UNDERLYING_TYPE (t1);
      ਜੇ (ਰੁੱਖ_ਕੋਡ (t2) != VOID_TYPE)
	{
	  ਅੰਕੜੇ->enum_and_int_p = ਸੱਚ;
	  ਅੰਕੜੇ->different_types_p = ਸੱਚ;
	}
    }
  ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਕੋਡ (t2) == ENUMERAL_TYPE
	   && COMPLETE_TYPE_P (t2)
	   && ਰੁੱਖ_ਕੋਡ (t1) != ENUMERAL_TYPE)
    {
      t2 = ENUM_UNDERLYING_TYPE (t2);
      ਜੇ (ਰੁੱਖ_ਕੋਡ (t1) != VOID_TYPE)
	{
	  ਅੰਕੜੇ->enum_and_int_p = ਸੱਚ;
	  ਅੰਕੜੇ->different_types_p = ਸੱਚ;
	}
    }

  ਜੇ (t1 == t2)
    ਵਾਪਸ ਸੱਚ;

  /* Different classes of types can't be compatible.  */

  ਜੇ (ਰੁੱਖ_ਕੋਡ (t1) != ਰੁੱਖ_ਕੋਡ (t2))
    ਵਾਪਸ ਝੂਠ;

  /* Allow for two different type nodes which have essentially the same
     definition.  Note that we already checked for equality of the type
     qualifiers (just above).  */

  ਜੇ (ਰੁੱਖ_ਕੋਡ (t1) != ARRAY_TYPE
      && TYPE_MAIN_VARIANT (t1) == TYPE_MAIN_VARIANT (t2))
    ਵਾਪਸ ਸੱਚ;

  ਪੂਰਨ attrval;

  /* 1 if no need for warning yet, 2 if warning cause has been seen.  */
  ਜੇ (!(attrval = comp_type_ਗੁਣ (t1, t2)))
    ਵਾਪਸ ਝੂਠ;

  ਜੇ (2 == attrval)
    ਅੰਕੜੇ->warning_needed = ਸੱਚ;

  ਚੋਣ (ਰੁੱਖ_ਕੋਡ (t1))
    {
    ਹਾਲਤ INTEGER_TYPE:
    ਹਾਲਤ FIXED_ਬਿੰਦੂ_TYPE:
    ਹਾਲਤ REAL_TYPE:
    ਹਾਲਤ BITINT_TYPE:
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
      ਵਾਪਸ TYPE_CANONICAL (t1) == TYPE_CANONICAL (t2);

    ਹਾਲਤ ਸੂਚਕ_TYPE:
      /* Do not remove mode information.  */
      ਜੇ (TYPE_ਬਹੁਲਕ (t1) != TYPE_ਬਹੁਲਕ (t2))
	ਵਾਪਸ ਝੂਠ;
      ਅੰਕੜੇ->pointedto = ਸੱਚ;
      ਵਾਪਸ comptypes_ਅੰਦਰੂਨੀ (ਰੁੱਖ_TYPE (t1), ਰੁੱਖ_TYPE (t2), ਅੰਕੜੇ);

    ਹਾਲਤ FUNCTION_TYPE:
      ਵਾਪਸ function_types_compatible_p (t1, t2, ਅੰਕੜੇ);

    ਹਾਲਤ ARRAY_TYPE:
      {
	ਰੁੱਖ d1 = TYPE_DOMAIN (t1);
	ਰੁੱਖ d2 = TYPE_DOMAIN (t2);

	/* Target types must match incl. qualifiers.  */
	ਜੇ (!comptypes_ਅੰਦਰੂਨੀ (ਰੁੱਖ_TYPE (t1), ਰੁੱਖ_TYPE (t2), ਅੰਕੜੇ))
	  ਵਾਪਸ ਝੂਠ;

	ਜੇ ((d1 == NULL_ਰੁੱਖ) != (d2 == NULL_ਰੁੱਖ))
	  ਅੰਕੜੇ->different_types_p = ਸੱਚ;
	/* Ignore size mismatches when forming equivalence classes.  */
	ਜੇ (ਅੰਕੜੇ->equiv)
	  ਵਾਪਸ ਸੱਚ;
	/* Sizes must match unless one is missing or variable.  */
	ਜੇ (d1 == NULL_ਰੁੱਖ || d2 == NULL_ਰੁੱਖ || d1 == d2)
	  ਵਾਪਸ ਸੱਚ;

	ਤਾਰਕਿਕ d1_variable = ਸਿਖਰ_array_vla_p (t1);
	ਤਾਰਕਿਕ d2_variable = ਸਿਖਰ_array_vla_p (t2);

	ਜੇ (d1_variable != d2_variable)
	  ਅੰਕੜੇ->different_types_p = ਸੱਚ;
	ਜੇ (d1_variable || d2_variable)
	  ਵਾਪਸ ਸੱਚ;

	ਤਾਰਕਿਕ d1_zero = zero_ਲੰਮਾਈ_array_type_p (t1)
		       || flexible_array_member_type_p (t1);

	ਤਾਰਕਿਕ d2_zero = zero_ਲੰਮਾਈ_array_type_p (t2)
		       || flexible_array_member_type_p (t2);

	ਜੇ (d1_zero && d2_zero)
	  ਵਾਪਸ ਸੱਚ;
	ਜੇ (d1_zero || d2_zero)
	  ਵਾਪਸ ਝੂਠ;

	ਜੇ (!ਰੁੱਖ_int_cst_equal (TYPE_MIN_ਮੁੱਲ (d1), TYPE_MIN_ਮੁੱਲ (d2))
	    || !ਰੁੱਖ_int_cst_equal (TYPE_MAX_ਮੁੱਲ (d1), TYPE_MAX_ਮੁੱਲ (d2)))
	  ਵਾਪਸ ਝੂਠ;

	ਵਾਪਸ ਸੱਚ;
      }

    ਹਾਲਤ ENUMERAL_TYPE:
    ਹਾਲਤ ਰਿਕਾਰਡ_TYPE:
    ਹਾਲਤ UNION_TYPE:

      ਜੇ (!flag_isoc23)
	ਵਾਪਸ ਝੂਠ;

      ਵਾਪਸ tagged_types_tu_compatible_p (t1, t2, ਅੰਕੜੇ);

    ਹਾਲਤ ਸਦਿਸ਼_TYPE:
      ਵਾਪਸ ਗਿਆਤ_eq (TYPE_ਸਦਿਸ਼_SUBPARTS (t1), TYPE_ਸਦਿਸ਼_SUBPARTS (t2))
	     && comptypes_ਅੰਦਰੂਨੀ (ਰੁੱਖ_TYPE (t1), ਰੁੱਖ_TYPE (t2), ਅੰਕੜੇ);

    ਮੂਲ:
      ਵਾਪਸ ਝੂਠ;
    }
  gcc_unreachable ();
}

/* Return true if TTL and TTR are pointers to types that are equivalent, ignoring
   their qualifiers, except for named address spaces.  If the pointers point to
   different named addresses, then we must determine if one address space is a
   subset of the other.  */

ਸਥਿਰ ਤਾਰਕਿਕ
comp_ਨਿਸ਼ਾਨਾ_types (location_t location, ਰੁੱਖ ttl, ਰੁੱਖ ttr)
{
  ਰੁੱਖ mvl = ਰੁੱਖ_TYPE (ttl);
  ਰੁੱਖ mvr = ਰੁੱਖ_TYPE (ttr);
  addr_space_t asl = TYPE_ADDR_SPACE (mvl);
  addr_space_t asr = TYPE_ADDR_SPACE (mvr);
  addr_space_t as_common;

  /* Fail if pointers point to incompatible address spaces.  */
  ਜੇ (!addr_space_superset (asl, asr, &as_common))
    ਵਾਪਸ 0;

  /* Qualifiers on element types of array types that are
     pointer targets are also removed.  */
  ਬਣਤਰ comptypes_ਅੰਕੜੇ ਅੰਕੜੇ = { };
  ਜੇ (!comptypes_ਅੰਦਰੂਨੀ (remove_qualifiers (mvl),
			   remove_qualifiers (mvr), &ਅੰਕੜੇ))
    ਵਾਪਸ ਝੂਠ;

  /* For pedantic use comptypes on arrays before removing
     qualifiers on the element type. */
  ਜੇ (ਰੁੱਖ_ਕੋਡ (mvl) == ARRAY_TYPE
      && ਰੁੱਖ_ਕੋਡ (mvr) == ARRAY_TYPE
      && !comptypes (mvl, mvr))
    pedwarn_c11 (location, OPT_Wpedantic, "invalid use of pointers to arrays "
					  "with different qualifiers in ISO C "
					  "before C23");

  ਜੇ (ਅੰਕੜੇ.warning_needed)
    pedwarn (location, OPT_Wpedantic, "types are not quite compatible");

  ਜੇ (ਅੰਕੜੇ.enum_and_int_p && warn_cxx_compat)
    warning_at (location, OPT_Wc___compat,
		"pointer target types incompatible in C++");

  ਵਾਪਸ ਸੱਚ;
}

/* Subroutines of `comptypes'.  */

/* Return true if two 'struct', 'union', or 'enum' types T1 and T2 are
   compatible.  The two types are not the same (which has been
   checked earlier in comptypes_internal).  */

ਸਥਿਰ ਤਾਰਕਿਕ
tagged_types_tu_compatible_p (const_ਰੁੱਖ t1, const_ਰੁੱਖ t2,
			      ਬਣਤਰ comptypes_ਅੰਕੜੇ *ਅੰਕੜੇ)
{
  ਰੁੱਖ s1, s2;

  ਜੇ (c_type_ਟੈਗ (t1) != c_type_ਟੈਗ (t2))
    ਵਾਪਸ ਝੂਠ;

  /* When forming equivalence classes for TYPE_CANONICAL in C23, we treat
     structs with the same tag as equivalent, but only when they are targets
     of pointers inside other structs.  */
  ਜੇ (ਅੰਕੜੇ->equiv && ਅੰਕੜੇ->pointedto && NULL_ਰੁੱਖ != c_type_ਟੈਗ (t1))
    ਵਾਪਸ ਸੱਚ;

  /* Different types without tag are incompatible except as an anonymous
     field or when forming equivalence classes for TYPE_CANONICAL.  */
  ਜੇ (!ਅੰਕੜੇ->anon_ਖੇਤਰ && !ਅੰਕੜੇ->equiv && NULL_ਰੁੱਖ == c_type_ਟੈਗ (t1))
    ਵਾਪਸ ਝੂਠ;

  ਜੇ (!ਅੰਕੜੇ->anon_ਖੇਤਰ && TYPE_STUB_DECL (t1) != TYPE_STUB_DECL (t2))
    ਅੰਕੜੇ->different_types_p = ਸੱਚ;

  /* Incomplete types are incompatible inside a TU.  */
  ਜੇ (TYPE_ਮਾਪ (t1) == ਨਿਰਾ || TYPE_ਮਾਪ (t2) == ਨਿਰਾ)
    ਵਾਪਸ ਝੂਠ;

  ਜੇ (ENUMERAL_TYPE != ਰੁੱਖ_ਕੋਡ (t1)
      && (TYPE_ਉਲਟ_STORAGE_ਕ੍ਰਮ (t1)
	  != TYPE_ਉਲਟ_STORAGE_ਕ੍ਰਮ (t2)))
    ਵਾਪਸ ਝੂਠ;

  ਜੇ (TYPE_USER_ALIGN (t1) != TYPE_USER_ALIGN (t2))
    ਅੰਕੜੇ->different_types_p = ਸੱਚ;

  /* For types already being looked at in some active
     invocation of this function, assume compatibility.
     The cache is built as a linked list on the stack
     with the head of the list passed downwards.  */
  ਲਈ (ਅਚਲ ਬਣਤਰ tagged_tu_ਵੇਖਿਆ_cache *t = ਅੰਕੜੇ->cache;
       t != ਨਿਰਾ; t = t->ਅਗਲਾ)
    ਜੇ (t->t1 == t1 && t->t2 == t2)
      ਵਾਪਸ ਸੱਚ;

  ਅਚਲ ਬਣਤਰ tagged_tu_ਵੇਖਿਆ_cache ਇੰਦਰਾਜ = { ਅੰਕੜੇ->cache, t1, t2 };

  ਚੋਣ (ਰੁੱਖ_ਕੋਡ (t1))
    {
    ਹਾਲਤ ENUMERAL_TYPE:
      {
	ਜੇ (!comptypes (ENUM_UNDERLYING_TYPE (t1), ENUM_UNDERLYING_TYPE (t2)))
	  ਵਾਪਸ ਝੂਠ;

	/* Speed up the case where the type values are in the same order.  */
	ਰੁੱਖ tv1 = TYPE_ਮੁੱਲਾਂ (t1);
	ਰੁੱਖ tv2 = TYPE_ਮੁੱਲਾਂ (t2);

	ਜੇ (tv1 == tv2)
	  ਵਾਪਸ ਸੱਚ;

	ਲਈ (;tv1 && tv2; tv1 = ਰੁੱਖ_CHAIN (tv1), tv2 = ਰੁੱਖ_CHAIN (tv2))
	  {
	    ਜੇ (ਰੁੱਖ_PURPOSE (tv1) != ਰੁੱਖ_PURPOSE (tv2))
	      ਰੋਕੋ;

	    ਜੇ (simple_cst_equal (DECL_INITIAL (ਰੁੱਖ_ਮੁੱਲ (tv1)),
				  DECL_INITIAL (ਰੁੱਖ_ਮੁੱਲ (tv2))) != 1)
	      ਰੋਕੋ;
	  }

	ਜੇ (tv1 == NULL_ਰੁੱਖ && tv2 == NULL_ਰੁੱਖ)
	  ਵਾਪਸ ਸੱਚ;

	ਜੇ (tv1 == NULL_ਰੁੱਖ || tv2 == NULL_ਰੁੱਖ)
	  ਵਾਪਸ ਝੂਠ;

	ਜੇ (list_ਲੰਮਾਈ (TYPE_ਮੁੱਲਾਂ (t1)) != list_ਲੰਮਾਈ (TYPE_ਮੁੱਲਾਂ (t2)))
	  ਵਾਪਸ ਝੂਠ;

	ਲਈ (s1 = TYPE_ਮੁੱਲਾਂ (t1); s1; s1 = ਰੁੱਖ_CHAIN (s1))
	  {
	    s2 = purpose_member (ਰੁੱਖ_PURPOSE (s1), TYPE_ਮੁੱਲਾਂ (t2));

	    ਜੇ (s2 == ਨਿਰਾ
		|| simple_cst_equal (DECL_INITIAL (ਰੁੱਖ_ਮੁੱਲ (s1)),
				     DECL_INITIAL (ਰੁੱਖ_ਮੁੱਲ (s2))) != 1)
	      ਵਾਪਸ ਝੂਠ;
	  }

	ਵਾਪਸ ਸੱਚ;
      }

    ਹਾਲਤ UNION_TYPE:
    ਹਾਲਤ ਰਿਕਾਰਡ_TYPE:

	ਜੇ (list_ਲੰਮਾਈ (TYPE_FIELDS (t1)) != list_ਲੰਮਾਈ (TYPE_FIELDS (t2)))
	  ਵਾਪਸ ਝੂਠ;

	ਲਈ (s1 = TYPE_FIELDS (t1), s2 = TYPE_FIELDS (t2);
	     s1 && s2;
	     s1 = DECL_CHAIN (s1), s2 = DECL_CHAIN (s2))
	  {
	    gcc_assert (ਰੁੱਖ_ਕੋਡ (s1) == ਖੇਤਰ_DECL);
	    gcc_assert (ਰੁੱਖ_ਕੋਡ (s2) == ਖੇਤਰ_DECL);

	    ਰੁੱਖ ft1 = ਰੁੱਖ_TYPE (s1);
	    ਰੁੱਖ ft2 = ਰੁੱਖ_TYPE (s2);

	    ਜੇ (DECL_NAME (s1) != DECL_NAME (s2))
	      ਵਾਪਸ ਝੂਠ;

	    ਜੇ (DECL_ALIGN (s1) != DECL_ALIGN (s2))
	      ਵਾਪਸ ਝੂਠ;

	    ਜੇ (DECL_C_ਦੋਆਧਾਰੀ_ਅੰਕ_ਖੇਤਰ (s1) != DECL_C_ਦੋਆਧਾਰੀ_ਅੰਕ_ਖੇਤਰ (s2))
	       ਵਾਪਸ ਝੂਠ;

	    ਜੇ (DECL_C_ਦੋਆਧਾਰੀ_ਅੰਕ_ਖੇਤਰ (s1))
	      {
		ਜੇ (!ਰੁੱਖ_int_cst_equal (DECL_ਮਾਪ (s1), DECL_ਮਾਪ (s2)))
		  ਵਾਪਸ ਝੂਠ;

		ft1 = DECL_ਦੋਆਧਾਰੀ_ਅੰਕ_ਖੇਤਰ_TYPE (s1);
		ft2 = DECL_ਦੋਆਧਾਰੀ_ਅੰਕ_ਖੇਤਰ_TYPE (s2);
	      }

	    ਜੇ (!ft1 || !ft2)
	      ਵਾਪਸ ਝੂਠ;

	    ਜੇ (ਰੁੱਖ_ਕੋਡ (ft1) == ERROR_MARK || ਰੁੱਖ_ਕੋਡ (ft2) == ERROR_MARK)
	      ਵਾਪਸ ਝੂਠ;

	    ਅੰਕੜੇ->anon_ਖੇਤਰ = !DECL_NAME (s1);
	    ਅੰਕੜੇ->pointedto = ਝੂਠ;

	    ਅਚਲ ਬਣਤਰ tagged_tu_ਵੇਖਿਆ_cache *cache = ਅੰਕੜੇ->cache;
	    ਅੰਕੜੇ->cache = &ਇੰਦਰਾਜ;
	    ਤਾਰਕਿਕ ret = comptypes_ਅੰਦਰੂਨੀ (ft1, ft2, ਅੰਕੜੇ);
	    ਅੰਕੜੇ->cache = cache;
	    ਜੇ (!ret)
	      ਵਾਪਸ ਝੂਠ;

	    ਰੁੱਖ st1 = TYPE_ਮਾਪ (ਰੁੱਖ_TYPE (s1));
	    ਰੁੱਖ st2 = TYPE_ਮਾਪ (ਰੁੱਖ_TYPE (s2));

	    ਜੇ (ਅੰਕੜੇ->equiv
		&& st1 && ਰੁੱਖ_ਕੋਡ (st1) == INTEGER_CST
		&& st2 && ਰੁੱਖ_ਕੋਡ (st2) == INTEGER_CST
		&& !ਰੁੱਖ_int_cst_equal (st1, st2))
	     ਵਾਪਸ ਝੂਠ;

	    ਰੁੱਖ counted_by1 = lookup_attribute ("counted_by",
						 DECL_ਗੁਣ (s1));
	    ਰੁੱਖ counted_by2 = lookup_attribute ("counted_by",
						 DECL_ਗੁਣ (s2));
	    /* If there is no counted_by attribute for both fields.  */
	    ਜੇ (!counted_by1 && !counted_by2)
	      ਜਾਰੀ;

	    /* If only one field has counted_by attribute.  */
	    ਜੇ ((counted_by1 && !counted_by2)
		|| (!counted_by1 && counted_by2))
	      ਵਾਪਸ ਝੂਠ;

	    /* Now both s1 and s2 have counted_by attributes, check
	       whether they are the same.  */

	    ਰੁੱਖ counted_by_field1
	      = lookup_ਖੇਤਰ (t1, ਰੁੱਖ_ਮੁੱਲ (ਰੁੱਖ_ਮੁੱਲ (counted_by1)));
	    ਰੁੱਖ counted_by_field2
	      = lookup_ਖੇਤਰ (t2, ਰੁੱਖ_ਮੁੱਲ (ਰੁੱਖ_ਮੁੱਲ (counted_by2)));

	    gcc_assert (counted_by_field1 && counted_by_field2);

	    ਜਦੋਂ (ਰੁੱਖ_CHAIN (counted_by_field1))
	      counted_by_field1 = ਰੁੱਖ_CHAIN (counted_by_field1);
	    ਜਦੋਂ (ਰੁੱਖ_CHAIN (counted_by_field2))
	      counted_by_field2 = ਰੁੱਖ_CHAIN (counted_by_field2);

	    ਜੇ (DECL_NAME (ਰੁੱਖ_ਮੁੱਲ (counted_by_field1))
		!= DECL_NAME (ਰੁੱਖ_ਮੁੱਲ (counted_by_field2)))
	      ਵਾਪਸ ਝੂਠ;
	  }
	ਵਾਪਸ ਸੱਚ;

    ਮੂਲ:
      gcc_unreachable ();
    }
}

/* Return true if two function types F1 and F2 are compatible.
   If either type specifies no argument types,
   the other must specify a fixed number of self-promoting arg types.
   Otherwise, if one type specifies only the number of arguments,
   the other must specify that number of self-promoting arg types.
   Otherwise, the argument types must match.  */

ਸਥਿਰ ਤਾਰਕਿਕ
function_types_compatible_p (const_ਰੁੱਖ f1, const_ਰੁੱਖ f2,
			     ਬਣਤਰ comptypes_ਅੰਕੜੇ *ਅੰਕੜੇ)
{
  ਰੁੱਖ ret1 = ਰੁੱਖ_TYPE (f1);
  ਰੁੱਖ ret2 = ਰੁੱਖ_TYPE (f2);

  /* 'volatile' qualifiers on a function's return type used to mean
     the function is noreturn.  */
  ਜੇ (TYPE_VOLATILE (ret1) != TYPE_VOLATILE (ret2))
    pedwarn (ਨਿਵੇਸ਼_location, 0, "function return types not compatible due to %<volatile%>");
  ਜੇ (TYPE_VOLATILE (ret1))
    ret1 = build_qualified_type (TYPE_MAIN_VARIANT (ret1),
				 TYPE_QUALS (ret1) & ~TYPE_QUAL_VOLATILE);
  ਜੇ (TYPE_VOLATILE (ret2))
    ret2 = build_qualified_type (TYPE_MAIN_VARIANT (ret2),
				 TYPE_QUALS (ret2) & ~TYPE_QUAL_VOLATILE);

  ਤਾਰਕਿਕ ignore_pargs = ਅੰਕੜੇ->ignore_promoting_ਦਲੀਲਾਂ;
  ਅੰਕੜੇ->ignore_promoting_ਦਲੀਲਾਂ = ਝੂਠ;

  ਜੇ (!comptypes_ਅੰਦਰੂਨੀ (ret1, ret2, ਅੰਕੜੇ))
    ਵਾਪਸ ਝੂਠ;

  ਅੰਕੜੇ->ignore_promoting_ਦਲੀਲਾਂ = ignore_pargs;

  ਰੁੱਖ args1 = TYPE_ARG_TYPES (f1);
  ਰੁੱਖ args2 = TYPE_ARG_TYPES (f2);

  ਜੇ ((args1 == NULL_ਰੁੱਖ) != (args2 == NULL_ਰੁੱਖ))
    ਅੰਕੜੇ->different_types_p = ਸੱਚ;

  /* An unspecified parmlist matches any specified parmlist
     whose argument types don't need default promotions.  */

  ਜੇ (args1 == NULL_ਰੁੱਖ)
    {
      ਜੇ (TYPE_NO_NAMED_ਦਲੀਲਾਂ_STDARG_P (f1) != TYPE_NO_NAMED_ਦਲੀਲਾਂ_STDARG_P (f2))
	ਵਾਪਸ ਝੂਠ;
      ਜੇ (!(ਅੰਕੜੇ->ignore_promoting_ਦਲੀਲਾਂ || self_promoting_ਦਲੀਲਾਂ_p (args2)))
	ਵਾਪਸ ਝੂਠ;
      ਅੰਕੜੇ->ignore_promoting_ਦਲੀਲਾਂ = ਝੂਠ;
      /* If one of these types comes from a non-prototype fn definition,
	 compare that with the other type's arglist.
	 If they don't match, ask for a warning (but no error).  */
      ਜੇ (TYPE_ACTUAL_ARG_TYPES (f1)
	  && !type_lists_compatible_p (args2, TYPE_ACTUAL_ARG_TYPES (f1), ਅੰਕੜੇ))
	 ਅੰਕੜੇ->warning_needed = ਸੱਚ;
      ਵਾਪਸ ਸੱਚ;
    }
  ਜੇ (args2 == NULL_ਰੁੱਖ)
    {
      ਜੇ (TYPE_NO_NAMED_ਦਲੀਲਾਂ_STDARG_P (f1) != TYPE_NO_NAMED_ਦਲੀਲਾਂ_STDARG_P (f2))
	ਵਾਪਸ ਝੂਠ;
      ਜੇ (!(ਅੰਕੜੇ->ignore_promoting_ਦਲੀਲਾਂ || self_promoting_ਦਲੀਲਾਂ_p (args1)))
	ਵਾਪਸ ਝੂਠ;
      ਅੰਕੜੇ->ignore_promoting_ਦਲੀਲਾਂ = ਝੂਠ;
      ਜੇ (TYPE_ACTUAL_ARG_TYPES (f2)
	  && !type_lists_compatible_p (args1, TYPE_ACTUAL_ARG_TYPES (f2), ਅੰਕੜੇ))
	ਅੰਕੜੇ->warning_needed = ਸੱਚ;
      ਵਾਪਸ ਸੱਚ;
    }

  /* Both types have argument lists: compare them and propagate results.  */
  ਵਾਪਸ type_lists_compatible_p (args1, args2, ਅੰਕੜੇ);
}

/* Check two lists of types for compatibility, returning false for
   incompatible, true for compatible.  */

ਸਥਿਰ ਤਾਰਕਿਕ
type_lists_compatible_p (const_ਰੁੱਖ args1, const_ਰੁੱਖ args2,
			 ਬਣਤਰ comptypes_ਅੰਕੜੇ *ਅੰਕੜੇ)
{
  ਜਦੋਂ (1)
    {
      ਜੇ (args1 == NULL_ਰੁੱਖ && args2 == NULL_ਰੁੱਖ)
	ਵਾਪਸ ਸੱਚ;
      /* If one list is shorter than the other,
	 they fail to match.  */
      ਜੇ (args1 == NULL_ਰੁੱਖ || args2 == NULL_ਰੁੱਖ)
	ਵਾਪਸ ਝੂਠ;
      ਰੁੱਖ a1 = ਰੁੱਖ_ਮੁੱਲ (args1);
      ਰੁੱਖ a2 = ਰੁੱਖ_ਮੁੱਲ (args2);
      ਰੁੱਖ mv1 = remove_qualifiers (a1);
      ਰੁੱਖ mv2 = remove_qualifiers (a2);

      gcc_assert (mv2);
      gcc_assert (mv2);

      /* If one of the lists has an error marker, ignore this arg.  */
      ਜੇ (ਰੁੱਖ_ਕੋਡ (a1) == ERROR_MARK
	       || ਰੁੱਖ_ਕੋਡ (a2) == ERROR_MARK)
	;
      ਨਹੀਂਤਾਂ ਜੇ (!comptypes_ਅੰਦਰੂਨੀ (mv1, mv2, ਅੰਕੜੇ))
	{
	  ਅੰਕੜੇ->different_types_p = ਸੱਚ;
	  /* Allow  wait (union {union wait *u; int *i} *)
	     and  wait (union wait *)  to be compatible.  */
	  ਜੇ (ਰੁੱਖ_ਕੋਡ (a1) == UNION_TYPE
	      && (TYPE_NAME (a1) == NULL_ਰੁੱਖ
		  || TYPE_TRANSPARENT_AGGR (a1))
	      && ਰੁੱਖ_ਕੋਡ (TYPE_ਮਾਪ (a1)) == INTEGER_CST
	      && ਰੁੱਖ_int_cst_equal (TYPE_ਮਾਪ (a1),
				     TYPE_ਮਾਪ (a2)))
	    {
	      ਰੁੱਖ memb;
	      ਲਈ (memb = TYPE_FIELDS (a1);
		   memb; memb = DECL_CHAIN (memb))
		{
		  ਰੁੱਖ mv3 = remove_qualifiers (ਰੁੱਖ_TYPE (memb));
		  ਜੇ (comptypes_ਅੰਦਰੂਨੀ (mv3, mv2, ਅੰਕੜੇ))
		    ਰੋਕੋ;
		}
	      ਜੇ (memb == NULL_ਰੁੱਖ)
		ਵਾਪਸ ਝੂਠ;
	    }
	  ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਕੋਡ (a2) == UNION_TYPE
		   && (TYPE_NAME (a2) == NULL_ਰੁੱਖ
		       || TYPE_TRANSPARENT_AGGR (a2))
		   && ਰੁੱਖ_ਕੋਡ (TYPE_ਮਾਪ (a2)) == INTEGER_CST
		   && ਰੁੱਖ_int_cst_equal (TYPE_ਮਾਪ (a2),
					  TYPE_ਮਾਪ (a1)))
	    {
	      ਰੁੱਖ memb;
	      ਲਈ (memb = TYPE_FIELDS (a2);
		   memb; memb = DECL_CHAIN (memb))
		{
		  ਰੁੱਖ mv3 = remove_qualifiers (ਰੁੱਖ_TYPE (memb));
		  ਜੇ (comptypes_ਅੰਦਰੂਨੀ (mv3, mv1, ਅੰਕੜੇ))
		    ਰੋਕੋ;
		}
	      ਜੇ (memb == NULL_ਰੁੱਖ)
		ਵਾਪਸ ਝੂਠ;
	    }
	  ਨਹੀਂਤਾਂ
	    ਵਾਪਸ ਝੂਠ;
	}

      args1 = ਰੁੱਖ_CHAIN (args1);
      args2 = ਰੁੱਖ_CHAIN (args2);
    }
}

/* Compute the size to increment a pointer by.  When a function type or void
   type or incomplete type is passed, size_one_node is returned.
   This function does not emit any diagnostics; the caller is responsible
   for that.  */

ਸਥਿਰ ਰੁੱਖ
c_ਮਾਪ_ਵਿੱਚ_ਬਾਈਟਾਂ (const_ਰੁੱਖ type)
{
  ਗਿਣਤੀ ਰੁੱਖ_ਕੋਡ_2 ਕੋਡ = ਰੁੱਖ_ਕੋਡ (type);

  ਜੇ (ਕੋਡ == FUNCTION_TYPE || ਕੋਡ == VOID_TYPE || ਕੋਡ == ERROR_MARK
      || !COMPLETE_TYPE_P (type))
    ਵਾਪਸ ਮਾਪ_one_ਗੰਢ;

  /* Convert in case a char is more than one unit.  */
  ਵਾਪਸ ਮਾਪ_binop_loc (ਨਿਵੇਸ਼_location, CEIL_DIV_ਵਿਅੰਜਕ, TYPE_ਮਾਪ_UNIT (type),
			 ਮਾਪ_int (TYPE_PRECISION (char_type_ਗੰਢ)
				   / ਬਿੱਟ_ਪ੍ਰਤੀ_UNIT));
}

/* Return either DECL or its known constant value (if it has one).  */

ਰੁੱਖ
decl_constant_ਮੁੱਲ_1 (ਰੁੱਖ decl, ਤਾਰਕਿਕ ਵਿੱਚ_init)
{
  ਜੇ (/* Note that DECL_INITIAL isn't valid for a PARM_DECL.  */
      ਰੁੱਖ_ਕੋਡ (decl) != PARM_DECL
      && !ਰੁੱਖ_THIS_VOLATILE (decl)
      && ਰੁੱਖ_READONLY (decl)
      && DECL_INITIAL (decl) != NULL_ਰੁੱਖ
      && !error_ਸੰਕਾਰਜ_p (DECL_INITIAL (decl))
      /* This is invalid if initial value is not constant.
	 If it has either a function call, a memory reference,
	 or a variable, then re-evaluating it could give different results.  */
      && ਰੁੱਖ_CONSTANT (DECL_INITIAL (decl))
      /* Check for cases where this is sub-optimal, even though valid.  */
      && (ਵਿੱਚ_init || ਰੁੱਖ_ਕੋਡ (DECL_INITIAL (decl)) != CONSTRUCTOR))
    ਵਾਪਸ DECL_INITIAL (decl);
  ਵਾਪਸ decl;
}

/* Return either DECL or its known constant value (if it has one).
   Like the above, but always return decl outside of functions.  */

ਰੁੱਖ
decl_constant_ਮੁੱਲ (ਰੁੱਖ decl)
{
  /* Don't change a variable array bound or initial value to a constant
     in a place where a variable is invalid.  */
  ਵਾਪਸ current_function_decl ? decl_constant_ਮੁੱਲ_1 (decl, ਝੂਠ) : decl;
}

/* Convert the array expression EXP to a pointer.  */
ਸਥਿਰ ਰੁੱਖ
array_ਮੰਜ਼ਿਲ_ਸੂਚਕ_conversion (location_t loc, ਰੁੱਖ ਘਾਤਾਂਕ)
{
  ਰੁੱਖ orig_exp = ਘਾਤਾਂਕ;
  ਰੁੱਖ type = ਰੁੱਖ_TYPE (ਘਾਤਾਂਕ);
  ਰੁੱਖ adr;
  ਰੁੱਖ restype = ਰੁੱਖ_TYPE (type);
  ਰੁੱਖ ptrtype;

  gcc_assert (ਰੁੱਖ_ਕੋਡ (type) == ARRAY_TYPE);

  STRIP_TYPE_NOPS (ਘਾਤਾਂਕ);

  copy_warning (ਘਾਤਾਂਕ, orig_exp);

  ptrtype = c_build_ਸੂਚਕ_type (restype);

  ਜੇ (ਅਸਿੱਧਾ_REF_P (ਘਾਤਾਂਕ))
    ਵਾਪਸ convert (ptrtype, ਰੁੱਖ_ਸੰਕਾਰਜ (ਘਾਤਾਂਕ, 0));

  /* In C++ array compound literals are temporary objects unless they are
     const or appear in namespace scope, so they are destroyed too soon
     to use them for much of anything  (c++/53220).  */
  ਜੇ (warn_cxx_compat && ਰੁੱਖ_ਕੋਡ (ਘਾਤਾਂਕ) == COMPOUND_LITERAL_ਵਿਅੰਜਕ)
    {
      ਰੁੱਖ decl = ਰੁੱਖ_ਸੰਕਾਰਜ (ਰੁੱਖ_ਸੰਕਾਰਜ (ਘਾਤਾਂਕ, 0), 0);
      ਜੇ (!ਰੁੱਖ_READONLY (decl) && !ਰੁੱਖ_STATIC (decl))
	warning_at (DECL_ਸਰੋਤ_LOCATION (decl), OPT_Wc___compat,
		    "converting an array compound literal to a pointer "
		    "leads to a dangling pointer in C++");
    }

  adr = build_unary_op (loc, ADDR_ਵਿਅੰਜਕ, ਘਾਤਾਂਕ, ਸੱਚ);
  ਵਾਪਸ convert (ptrtype, adr);
}

/* Convert the function expression EXP to a pointer.  */
ਸਥਿਰ ਰੁੱਖ
function_ਮੰਜ਼ਿਲ_ਸੂਚਕ_conversion (location_t loc, ਰੁੱਖ ਘਾਤਾਂਕ)
{
  ਰੁੱਖ orig_exp = ਘਾਤਾਂਕ;

  gcc_assert (ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (ਘਾਤਾਂਕ)) == FUNCTION_TYPE);

  STRIP_TYPE_NOPS (ਘਾਤਾਂਕ);

  copy_warning (ਘਾਤਾਂਕ, orig_exp);

  ਰੁੱਖ exp2 = build_unary_op (loc, ADDR_ਵਿਅੰਜਕ, ਘਾਤਾਂਕ, ਝੂਠ);

  /* If the function is defined and known to not require a non-local
     context, make sure no trampoline is generated.  */
  ਜੇ (ਰੁੱਖ_ਕੋਡ (ਘਾਤਾਂਕ) == FUNCTION_DECL
      && DECL_INITIAL (ਘਾਤਾਂਕ) && !C_FUNC_NONLOCAL_CONTEXT (ਘਾਤਾਂਕ))
   ਰੁੱਖ_NO_TRAMPOLINE (exp2) = 1;

  ਵਾਪਸ exp2;
}

/* Mark EXP as read, not just set, for set but not used -Wunused
   warning purposes.  */

ਖਾਲੀ
mark_exp_read (ਰੁੱਖ ਘਾਤਾਂਕ)
{
  ਚੋਣ (ਰੁੱਖ_ਕੋਡ (ਘਾਤਾਂਕ))
    {
    ਹਾਲਤ VAR_DECL:
    ਹਾਲਤ PARM_DECL:
      DECL_READ_P (ਘਾਤਾਂਕ) = 1;
      ਰੋਕੋ;
    CASE_CONVERT:
      ਜੇ (VOID_TYPE_P (ਰੁੱਖ_TYPE (ਘਾਤਾਂਕ)))
	ਚੋਣ (ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_ਸੰਕਾਰਜ (ਘਾਤਾਂਕ, 0)))
	  {
	  ਹਾਲਤ PREINCREMENT_ਵਿਅੰਜਕ:
	  ਹਾਲਤ PREDECREMENT_ਵਿਅੰਜਕ:
	  ਹਾਲਤ POSTINCREMENT_ਵਿਅੰਜਕ:
	  ਹਾਲਤ POSTDECREMENT_ਵਿਅੰਜਕ:
	    ਵਾਪਸ;
	  ਮੂਲ:
	    ਰੋਕੋ;
	  }
      /* FALLTHRU */
    ਹਾਲਤ ARRAY_REF:
    ਹਾਲਤ COMPONENT_REF:
    ਹਾਲਤ MODIFY_ਵਿਅੰਜਕ:
    ਹਾਲਤ REALPART_ਵਿਅੰਜਕ:
    ਹਾਲਤ IMAGPART_ਵਿਅੰਜਕ:
    ਹਾਲਤ ADDR_ਵਿਅੰਜਕ:
    ਹਾਲਤ VIEW_CONVERT_ਵਿਅੰਜਕ:
    ਹਾਲਤ PREINCREMENT_ਵਿਅੰਜਕ:
    ਹਾਲਤ PREDECREMENT_ਵਿਅੰਜਕ:
    ਹਾਲਤ POSTINCREMENT_ਵਿਅੰਜਕ:
    ਹਾਲਤ POSTDECREMENT_ਵਿਅੰਜਕ:
      mark_exp_read (ਰੁੱਖ_ਸੰਕਾਰਜ (ਘਾਤਾਂਕ, 0));
      ਰੋਕੋ;
    ਹਾਲਤ COMPOUND_ਵਿਅੰਜਕ:
      /* Pattern match what build_atomic_assign produces with modifycode
	 NOP_EXPR.  */
      ਜੇ (VAR_P (ਰੁੱਖ_ਸੰਕਾਰਜ (ਘਾਤਾਂਕ, 1))
	  && DECL_ARTIFICIAL (ਰੁੱਖ_ਸੰਕਾਰਜ (ਘਾਤਾਂਕ, 1))
	  && ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_ਸੰਕਾਰਜ (ਘਾਤਾਂਕ, 0)) == COMPOUND_ਵਿਅੰਜਕ)
	{
	  ਰੁੱਖ t1 = ਰੁੱਖ_ਸੰਕਾਰਜ (ਰੁੱਖ_ਸੰਕਾਰਜ (ਘਾਤਾਂਕ, 0), 0);
	  ਰੁੱਖ t2 = ਰੁੱਖ_ਸੰਕਾਰਜ (ਰੁੱਖ_ਸੰਕਾਰਜ (ਘਾਤਾਂਕ, 0), 1);
	  ਜੇ (ਰੁੱਖ_ਕੋਡ (t1) == ਨਿਸ਼ਾਨਾ_ਵਿਅੰਜਕ
	      && ਨਿਸ਼ਾਨਾ_ਵਿਅੰਜਕ_ਥਾਂ (t1) == ਰੁੱਖ_ਸੰਕਾਰਜ (ਘਾਤਾਂਕ, 1)
	      && ਰੁੱਖ_ਕੋਡ (t2) == CALL_ਵਿਅੰਜਕ)
	    {
	      ਰੁੱਖ fndecl = get_callee_fndecl (t2);
	      ਰੁੱਖ arg = NULL_ਰੁੱਖ;
	      ਜੇ (fndecl
		  && ਰੁੱਖ_ਕੋਡ (fndecl) == FUNCTION_DECL
		  && fndecl_built_ਵਿੱਚ_p (fndecl, BUILT_ਵਿੱਚ_ਸਾਧਾਰਨ)
		  && call_ਵਿਅੰਜਕ_nargs (t2) >= 2)
		ਚੋਣ (DECL_FUNCTION_ਕੋਡ (fndecl))
		  {
		  ਹਾਲਤ BUILT_ਵਿੱਚ_ATOMIC_STORE:
		    arg = CALL_ਵਿਅੰਜਕ_ARG (t2, 1);
		    ਰੋਕੋ;
		  ਹਾਲਤ BUILT_ਵਿੱਚ_ATOMIC_STORE_1:
		  ਹਾਲਤ BUILT_ਵਿੱਚ_ATOMIC_STORE_2:
		  ਹਾਲਤ BUILT_ਵਿੱਚ_ATOMIC_STORE_4:
		  ਹਾਲਤ BUILT_ਵਿੱਚ_ATOMIC_STORE_8:
		  ਹਾਲਤ BUILT_ਵਿੱਚ_ATOMIC_STORE_16:
		    arg = CALL_ਵਿਅੰਜਕ_ARG (t2, 0);
		    ਰੋਕੋ;
		  ਮੂਲ:
		    ਰੋਕੋ;
		  }
	      ਜੇ (arg)
		{
		  STRIP_NOPS (arg);
		  ਜੇ (ਰੁੱਖ_ਕੋਡ (arg) == ADDR_ਵਿਅੰਜਕ
		      && DECL_P (ਰੁੱਖ_ਸੰਕਾਰਜ (arg, 0))
		      && TYPE_ATOMIC (ਰੁੱਖ_TYPE (ਰੁੱਖ_ਸੰਕਾਰਜ (arg, 0))))
		    mark_exp_read (ਰੁੱਖ_ਸੰਕਾਰਜ (arg, 0));
		}
	    }
	}
      /* FALLTHRU */
    ਹਾਲਤ C_MAYBE_CONST_ਵਿਅੰਜਕ:
      mark_exp_read (ਰੁੱਖ_ਸੰਕਾਰਜ (ਘਾਤਾਂਕ, 1));
      ਰੋਕੋ;
    ਹਾਲਤ OMP_ARRAY_SECTION:
      mark_exp_read (ਰੁੱਖ_ਸੰਕਾਰਜ (ਘਾਤਾਂਕ, 0));
      ਜੇ (ਰੁੱਖ_ਸੰਕਾਰਜ (ਘਾਤਾਂਕ, 1))
	mark_exp_read (ਰੁੱਖ_ਸੰਕਾਰਜ (ਘਾਤਾਂਕ, 1));
      ਜੇ (ਰੁੱਖ_ਸੰਕਾਰਜ (ਘਾਤਾਂਕ, 2))
	mark_exp_read (ਰੁੱਖ_ਸੰਕਾਰਜ (ਘਾਤਾਂਕ, 2));
      ਰੋਕੋ;
    ਮੂਲ:
      ਰੋਕੋ;
    }
}

/* Perform the default conversion of arrays and functions to pointers.
   Return the result of converting EXP.  For any other expression, just
   return EXP.

   LOC is the location of the expression.  */

ਬਣਤਰ c_ਵਿਅੰਜਕ
default_function_array_conversion (location_t loc, ਬਣਤਰ c_ਵਿਅੰਜਕ ਘਾਤਾਂਕ)
{
  ਰੁੱਖ orig_exp = ਘਾਤਾਂਕ.ਮੁੱਲ;
  ਰੁੱਖ type = ਰੁੱਖ_TYPE (ਘਾਤਾਂਕ.ਮੁੱਲ);
  ਗਿਣਤੀ ਰੁੱਖ_ਕੋਡ_2 ਕੋਡ = ਰੁੱਖ_ਕੋਡ (type);

  ਚੋਣ (ਕੋਡ)
    {
    ਹਾਲਤ ARRAY_TYPE:
      {
	ਤਾਰਕਿਕ not_lvalue = ਝੂਠ;
	ਤਾਰਕਿਕ lvalue_array_p;

	ਜਦੋਂ ((ਰੁੱਖ_ਕੋਡ (ਘਾਤਾਂਕ.ਮੁੱਲ) == NON_LVALUE_ਵਿਅੰਜਕ
		|| CONVERT_ਵਿਅੰਜਕ_P (ਘਾਤਾਂਕ.ਮੁੱਲ))
	       && ਰੁੱਖ_TYPE (ਰੁੱਖ_ਸੰਕਾਰਜ (ਘਾਤਾਂਕ.ਮੁੱਲ, 0)) == type)
	  {
	    ਜੇ (ਰੁੱਖ_ਕੋਡ (ਘਾਤਾਂਕ.ਮੁੱਲ) == NON_LVALUE_ਵਿਅੰਜਕ)
	      not_lvalue = ਸੱਚ;
	    ਘਾਤਾਂਕ.ਮੁੱਲ = ਰੁੱਖ_ਸੰਕਾਰਜ (ਘਾਤਾਂਕ.ਮੁੱਲ, 0);
	  }

	copy_warning (ਘਾਤਾਂਕ.ਮੁੱਲ, orig_exp);

	lvalue_array_p = !not_lvalue && lvalue_p (ਘਾਤਾਂਕ.ਮੁੱਲ);
	ਜੇ (!flag_isoc99 && !lvalue_array_p)
	  {
	    /* Before C99, non-lvalue arrays do not decay to pointers.
	       Normally, using such an array would be invalid; but it can
	       be used correctly inside sizeof or as a statement expression.
	       Thus, do not give an error here; an error will result later.  */
	    ਵਾਪਸ ਘਾਤਾਂਕ;
	  }

	ਘਾਤਾਂਕ.ਮੁੱਲ = array_ਮੰਜ਼ਿਲ_ਸੂਚਕ_conversion (loc, ਘਾਤਾਂਕ.ਮੁੱਲ);
      }
      ਰੋਕੋ;
    ਹਾਲਤ FUNCTION_TYPE:
      ਘਾਤਾਂਕ.ਮੁੱਲ = function_ਮੰਜ਼ਿਲ_ਸੂਚਕ_conversion (loc, ਘਾਤਾਂਕ.ਮੁੱਲ);
      ਰੋਕੋ;
    ਮੂਲ:
      ਰੋਕੋ;
    }

  ਵਾਪਸ ਘਾਤਾਂਕ;
}

ਬਣਤਰ c_ਵਿਅੰਜਕ
default_function_array_read_conversion (location_t loc, ਬਣਤਰ c_ਵਿਅੰਜਕ ਘਾਤਾਂਕ)
{
  mark_exp_read (ਘਾਤਾਂਕ.ਮੁੱਲ);
  /* We only generate a call to .ACCESS_WITH_SIZE when it is a read.  */
  ਜੇ (ਰੁੱਖ_ਕੋਡ (ਘਾਤਾਂਕ.ਮੁੱਲ) == COMPONENT_REF
      && handle_counted_by_p (ਘਾਤਾਂਕ.ਮੁੱਲ))
    ਘਾਤਾਂਕ.ਮੁੱਲ = handle_counted_by_for_component_ref (loc, ਘਾਤਾਂਕ.ਮੁੱਲ);
  ਵਾਪਸ default_function_array_conversion (loc, ਘਾਤਾਂਕ);
}

/* Return whether EXPR should be treated as an atomic lvalue for the
   purposes of load and store handling.  */

ਸਥਿਰ ਤਾਰਕਿਕ
really_atomic_lvalue (ਰੁੱਖ ਵਿਅੰਜਕ)
{
  ਜੇ (error_ਸੰਕਾਰਜ_p (ਵਿਅੰਜਕ))
    ਵਾਪਸ ਝੂਠ;
  ਜੇ (!TYPE_ATOMIC (ਰੁੱਖ_TYPE (ਵਿਅੰਜਕ)))
    ਵਾਪਸ ਝੂਠ;
  ਜੇ (!COMPLETE_TYPE_P (ਰੁੱਖ_TYPE (ਵਿਅੰਜਕ)))
    ਵਾਪਸ ਝੂਠ;
  ਜੇ (!lvalue_p (ਵਿਅੰਜਕ))
    ਵਾਪਸ ਝੂਠ;

  /* Ignore _Atomic on register variables, since their addresses can't
     be taken so (a) atomicity is irrelevant and (b) the normal atomic
     sequences wouldn't work.  Ignore _Atomic on structures containing
     bit-fields, since accessing elements of atomic structures or
     unions is undefined behavior (C11 6.5.2.3#5), but it's unclear if
     it's undefined at translation time or execution time, and the
     normal atomic sequences again wouldn't work.  */
  ਜਦੋਂ (handled_component_p (ਵਿਅੰਜਕ))
    {
      ਜੇ (ਰੁੱਖ_ਕੋਡ (ਵਿਅੰਜਕ) == COMPONENT_REF
	  && DECL_C_ਦੋਆਧਾਰੀ_ਅੰਕ_ਖੇਤਰ (ਰੁੱਖ_ਸੰਕਾਰਜ (ਵਿਅੰਜਕ, 1)))
	ਵਾਪਸ ਝੂਠ;
      ਵਿਅੰਜਕ = ਰੁੱਖ_ਸੰਕਾਰਜ (ਵਿਅੰਜਕ, 0);
    }
  ਜੇ (ਰੁੱਖ_ਕੋਡ (ਵਿਅੰਜਕ) == COMPOUND_LITERAL_ਵਿਅੰਜਕ)
    ਵਿਅੰਜਕ = COMPOUND_LITERAL_ਵਿਅੰਜਕ_DECL (ਵਿਅੰਜਕ);
  ਜੇ (DECL_P (ਵਿਅੰਜਕ) && C_DECL_ਰਜਿਸਟਰ (ਵਿਅੰਜਕ))
    ਵਾਪਸ ਝੂਠ;
  ਵਾਪਸ ਸੱਚ;
}

/* If EXPR is a named constant (C23) derived from a constexpr variable
   - that is, a reference to such a variable, or a member extracted by
   a sequence of structure and union (but not array) member accesses
   (where union member accesses must access the same member as
   initialized) - then return the corresponding initializer;
   otherwise, return NULL_TREE.  */

ਸਥਿਰ ਰੁੱਖ
maybe_get_constexpr_init (ਰੁੱਖ ਵਿਅੰਜਕ)
{
  ਰੁੱਖ decl = NULL_ਰੁੱਖ;
  ਜੇ (ਰੁੱਖ_ਕੋਡ (ਵਿਅੰਜਕ) == VAR_DECL)
    decl = ਵਿਅੰਜਕ;
  ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਕੋਡ (ਵਿਅੰਜਕ) == COMPOUND_LITERAL_ਵਿਅੰਜਕ)
    decl = COMPOUND_LITERAL_ਵਿਅੰਜਕ_DECL (ਵਿਅੰਜਕ);
  ਜੇ (decl
      && C_DECL_DECLARED_CONSTEXPR (decl)
      && DECL_INITIAL (decl) != NULL_ਰੁੱਖ
      && !error_ਸੰਕਾਰਜ_p (DECL_INITIAL (decl)))
    ਵਾਪਸ DECL_INITIAL (decl);
  ਜੇ (ਰੁੱਖ_ਕੋਡ (ਵਿਅੰਜਕ) != COMPONENT_REF)
    ਵਾਪਸ NULL_ਰੁੱਖ;
  ਰੁੱਖ inner = maybe_get_constexpr_init (ਰੁੱਖ_ਸੰਕਾਰਜ (ਵਿਅੰਜਕ, 0));
  ਜੇ (inner == NULL_ਰੁੱਖ)
    ਵਾਪਸ NULL_ਰੁੱਖ;
  ਜਦੋਂ ((CONVERT_ਵਿਅੰਜਕ_P (inner) || ਰੁੱਖ_ਕੋਡ (inner) == NON_LVALUE_ਵਿਅੰਜਕ)
	 && !error_ਸੰਕਾਰਜ_p (inner)
	 && (TYPE_MAIN_VARIANT (ਰੁੱਖ_TYPE (inner))
	     == TYPE_MAIN_VARIANT (ਰੁੱਖ_TYPE (ਰੁੱਖ_ਸੰਕਾਰਜ (inner, 0)))))
    inner = ਰੁੱਖ_ਸੰਕਾਰਜ (inner, 0);
  ਜੇ (ਰੁੱਖ_ਕੋਡ (inner) != CONSTRUCTOR)
    ਵਾਪਸ NULL_ਰੁੱਖ;
  ਰੁੱਖ ਖੇਤਰ_2 = ਰੁੱਖ_ਸੰਕਾਰਜ (ਵਿਅੰਜਕ, 1);
  ਬਿਨਾਨਿਸ਼ਾਨੀ HOST_WIDE_INT cidx;
  ਰੁੱਖ cfield, cvalue;
  ਤਾਰਕਿਕ have_other_init = ਝੂਠ;
  FOR_EACH_CONSTRUCTOR_ELT (CONSTRUCTOR_ELTS (inner), cidx, cfield, cvalue)
    {
      ਜੇ (cfield == ਖੇਤਰ_2)
	ਵਾਪਸ cvalue;
      have_other_init = ਸੱਚ;
    }
  ਜੇ (ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (inner)) == UNION_TYPE
      && (have_other_init || ਖੇਤਰ_2 != TYPE_FIELDS (ਰੁੱਖ_TYPE (inner))))
    ਵਾਪਸ NULL_ਰੁੱਖ;
  /* Return a default initializer.  */
  ਜੇ (ਰਿਕਾਰਡ_OR_UNION_TYPE_P (ਰੁੱਖ_TYPE (ਵਿਅੰਜਕ)))
    ਵਾਪਸ build_constructor (ਰੁੱਖ_TYPE (ਵਿਅੰਜਕ), ਨਿਰਾ);
  ਵਾਪਸ build_zero_cst (ਰੁੱਖ_TYPE (ਵਿਅੰਜਕ));
}

/* Helper function for convert_lvalue_to_rvalue called via
   walk_tree_without_duplicates.  Find DATA inside of the expression.  */

ਸਥਿਰ ਰੁੱਖ
c_ਲੱਭੋ_var_r (ਰੁੱਖ *tp, ਪੂਰਨ *walk_subtrees, ਖਾਲੀ *ਅੰਕੜੇ)
{
  ਜੇ (TYPE_P (*tp))
    *walk_subtrees = 0;
  ਨਹੀਂਤਾਂ ਜੇ (*tp == (ਰੁੱਖ) ਅੰਕੜੇ)
    ਵਾਪਸ *tp;
  ਵਾਪਸ NULL_ਰੁੱਖ;
}

/* Convert expression EXP (location LOC) from lvalue to rvalue,
   including converting functions and arrays to pointers if CONVERT_P.
   If READ_P, also mark the expression as having been read.  If
   FOR_INIT, constexpr expressions of structure and union type should
   be replaced by the corresponding CONSTRUCTOR; otherwise, only
   constexpr scalars (including elements of structures and unions) are
   replaced by their initializers.  */

ਬਣਤਰ c_ਵਿਅੰਜਕ
convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (location_t loc, ਬਣਤਰ c_ਵਿਅੰਜਕ ਘਾਤਾਂਕ,
			  ਤਾਰਕਿਕ convert_p, ਤਾਰਕਿਕ read_p, ਤਾਰਕਿਕ for_init)
{
  ਤਾਰਕਿਕ force_non_npc = ਝੂਠ;
  ਜੇ (read_p)
    mark_exp_read (ਘਾਤਾਂਕ.ਮੁੱਲ);
  /* We only generate a call to .ACCESS_WITH_SIZE when it is a read.  */
  ਜੇ (read_p && ਰੁੱਖ_ਕੋਡ (ਘਾਤਾਂਕ.ਮੁੱਲ) == COMPONENT_REF
      && handle_counted_by_p (ਘਾਤਾਂਕ.ਮੁੱਲ))
    ਘਾਤਾਂਕ.ਮੁੱਲ = handle_counted_by_for_component_ref (loc, ਘਾਤਾਂਕ.ਮੁੱਲ);

  ਜੇ (convert_p)
    ਘਾਤਾਂਕ = default_function_array_conversion (loc, ਘਾਤਾਂਕ);
  ਜੇ (!VOID_TYPE_P (ਰੁੱਖ_TYPE (ਘਾਤਾਂਕ.ਮੁੱਲ))
      || (flag_isoc2y
	  && TYPE_QUALS (ਰੁੱਖ_TYPE (ਘਾਤਾਂਕ.ਮੁੱਲ)) != TYPE_UNQUALIFIED))
    ਘਾਤਾਂਕ.ਮੁੱਲ = require_complete_type (loc, ਘਾਤਾਂਕ.ਮੁੱਲ);
  ਜੇ (for_init || !ਰਿਕਾਰਡ_OR_UNION_TYPE_P (ਰੁੱਖ_TYPE (ਘਾਤਾਂਕ.ਮੁੱਲ)))
    {
      ਰੁੱਖ init = maybe_get_constexpr_init (ਘਾਤਾਂਕ.ਮੁੱਲ);
      ਜੇ (init != NULL_ਰੁੱਖ)
	{
	  /* A named constant of pointer type or type nullptr_t is not
	     a null pointer constant even if the initializer is
	     one.  */
	  ਜੇ (ਰੁੱਖ_ਕੋਡ (init) == INTEGER_CST
	      && !INTEGRAL_TYPE_P (ਰੁੱਖ_TYPE (init))
	      && integer_zerop (init))
	    force_non_npc = ਸੱਚ;
	  ਘਾਤਾਂਕ.ਮੁੱਲ = init;
	}
    }
  ਜੇ (really_atomic_lvalue (ਘਾਤਾਂਕ.ਮੁੱਲ))
    {
      vec<ਰੁੱਖ, va_gc> *params;
      ਰੁੱਖ nonatomic_type, tmp, tmp_addr, fndecl, func_call;
      ਰੁੱਖ ਵਿਅੰਜਕ_type = ਰੁੱਖ_TYPE (ਘਾਤਾਂਕ.ਮੁੱਲ);
      ਰੁੱਖ ਵਿਅੰਜਕ_addr = build_unary_op (loc, ADDR_ਵਿਅੰਜਕ, ਘਾਤਾਂਕ.ਮੁੱਲ, ਝੂਠ);
      ਰੁੱਖ seq_cst = build_int_cst (integer_type_ਗੰਢ, MEMMODEL_SEQ_CST);

      gcc_assert (TYPE_ATOMIC (ਵਿਅੰਜਕ_type));

      /* Expansion of a generic atomic load may require an addition
	 element, so allocate enough to prevent a resize.  */
      vec_alloc (params, 4);

      /* Remove the qualifiers for the rest of the expressions and
	 create the VAL temp variable to hold the RHS.  */
      nonatomic_type = build_qualified_type (ਵਿਅੰਜਕ_type, TYPE_UNQUALIFIED);
      tmp = create_tmp_var_raw (nonatomic_type);
      tmp_addr = build_unary_op (loc, ADDR_ਵਿਅੰਜਕ, tmp, ਝੂਠ);
      ਰੁੱਖ_ADDRESSABLE (tmp) = 1;
      /* Do not disable warnings for TMP even though it's artificial.
	 -Winvalid-memory-model depends on it.  */

      /* Issue __atomic_load (&expr, &tmp, SEQ_CST);  */
      fndecl = builtin_decl_explicit (BUILT_ਵਿੱਚ_ATOMIC_ਲੱਦੋ);
      params->ਤੇਜ਼_ਧੱਕੋ (ਵਿਅੰਜਕ_addr);
      params->ਤੇਜ਼_ਧੱਕੋ (tmp_addr);
      params->ਤੇਜ਼_ਧੱਕੋ (seq_cst);
      func_call = c_build_function_call_vec (loc, vNULL, fndecl, params, ਨਿਰਾ);

      /* EXPR is always read.  */
      mark_exp_read (ਘਾਤਾਂਕ.ਮੁੱਲ);

      /* Optimize the common case where c_build_function_call_vec
	 immediately folds __atomic_load (&expr, &tmp, SEQ_CST); into
	 tmp = __atomic_load_<N> (&expr, SEQ_CST);
	 In that case tmp is not addressable and can be initialized
	 fully by the rhs of the MODIFY_EXPR.  */
      ਰੁੱਖ tem = func_call;
      ਜੇ (CONVERT_ਵਿਅੰਜਕ_P (tem) && VOID_TYPE_P (ਰੁੱਖ_TYPE (tem)))
	{
	  tem = ਰੁੱਖ_ਸੰਕਾਰਜ (tem, 0);
	  ਜੇ (ਰੁੱਖ_ਕੋਡ (tem) == MODIFY_ਵਿਅੰਜਕ
	      && ਰੁੱਖ_ਸੰਕਾਰਜ (tem, 0) == tmp
	      && !walk_ਰੁੱਖ_without_duplicates (&ਰੁੱਖ_ਸੰਕਾਰਜ (tem, 1),
						c_ਲੱਭੋ_var_r, tmp))
	    {
	      ਰੁੱਖ_ADDRESSABLE (tmp) = 0;
	      func_call = ਰੁੱਖ_ਸੰਕਾਰਜ (tem, 1);
	    }
	}

      /* Return tmp which contains the value loaded.  */
      ਘਾਤਾਂਕ.ਮੁੱਲ = build4 (ਨਿਸ਼ਾਨਾ_ਵਿਅੰਜਕ, nonatomic_type, tmp, func_call,
			  NULL_ਰੁੱਖ, NULL_ਰੁੱਖ);
    }
  ਜੇ (convert_p && !error_ਸੰਕਾਰਜ_p (ਘਾਤਾਂਕ.ਮੁੱਲ)
      && (ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (ਘਾਤਾਂਕ.ਮੁੱਲ)) != ARRAY_TYPE))
    ਘਾਤਾਂਕ.ਮੁੱਲ = convert (build_qualified_type (ਰੁੱਖ_TYPE (ਘਾਤਾਂਕ.ਮੁੱਲ), TYPE_UNQUALIFIED), ਘਾਤਾਂਕ.ਮੁੱਲ);
  ਜੇ (force_non_npc)
    ਘਾਤਾਂਕ.ਮੁੱਲ = build1 (NOP_ਵਿਅੰਜਕ, ਰੁੱਖ_TYPE (ਘਾਤਾਂਕ.ਮੁੱਲ), ਘਾਤਾਂਕ.ਮੁੱਲ);

  {
    ਰੁੱਖ false_ਮੁੱਲ, true_ਮੁੱਲ;
    ਜੇ (convert_p && !error_ਸੰਕਾਰਜ_p (ਘਾਤਾਂਕ.ਮੁੱਲ)
	&& c_hardbool_type_attr (ਰੁੱਖ_TYPE (ਘਾਤਾਂਕ.ਮੁੱਲ),
				 &false_ਮੁੱਲ, &true_ਮੁੱਲ))
      {
	ਰੁੱਖ t = save_ਵਿਅੰਜਕ (ਘਾਤਾਂਕ.ਮੁੱਲ);

	mark_exp_read (ਘਾਤਾਂਕ.ਮੁੱਲ);

	ਰੁੱਖ trapfn = builtin_decl_explicit (BUILT_ਵਿੱਚ_TRAP);
	ਰੁੱਖ ਵਿਅੰਜਕ = build_call_ਵਿਅੰਜਕ_loc (loc, trapfn, 0);
	ਵਿਅੰਜਕ = build_compound_ਵਿਅੰਜਕ (loc, ਵਿਅੰਜਕ, boolean_true_ਗੰਢ);
	ਵਿਅੰਜਕ = fold_build3_loc (loc, COND_ਵਿਅੰਜਕ, boolean_type_ਗੰਢ,
				fold_build2_loc (loc, NE_ਵਿਅੰਜਕ,
						 boolean_type_ਗੰਢ,
						 t, true_ਮੁੱਲ),
				ਵਿਅੰਜਕ, boolean_true_ਗੰਢ);
	ਵਿਅੰਜਕ = fold_build3_loc (loc, COND_ਵਿਅੰਜਕ, boolean_type_ਗੰਢ,
				fold_build2_loc (loc, NE_ਵਿਅੰਜਕ,
						 boolean_type_ਗੰਢ,
						 t, false_ਮੁੱਲ),
				ਵਿਅੰਜਕ, boolean_false_ਗੰਢ);

	ਘਾਤਾਂਕ.ਮੁੱਲ = ਵਿਅੰਜਕ;
      }
  }

  ਵਾਪਸ ਘਾਤਾਂਕ;
}

/* Wrapper for the overload above, same arguments but for tree rather than
   c_expr.  This is important for hardbools to decay to bools.  */

ਸਥਿਰ ਸਤਰਅੰਦਰ ਰੁੱਖ
convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (location_t loc, ਰੁੱਖ val,
			  ਤਾਰਕਿਕ convert_p, ਤਾਰਕਿਕ read_p, ਤਾਰਕਿਕ for_init = ਝੂਠ)
{
  ਬਣਤਰ c_ਵਿਅੰਜਕ ਵਿਅੰਜਕ;
  memset (&ਵਿਅੰਜਕ, 0, ਆਕਾਰ (ਵਿਅੰਜਕ));
  ਵਿਅੰਜਕ.ਮੁੱਲ = val;
  ਵਿਅੰਜਕ = convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (loc, ਵਿਅੰਜਕ, convert_p, read_p, for_init);
  ਵਾਪਸ ਵਿਅੰਜਕ.ਮੁੱਲ;
}

/* EXP is an expression of integer type.  Apply the integer promotions
   to it and return the promoted value.  */

ਰੁੱਖ
perform_integral_promotions (ਰੁੱਖ ਘਾਤਾਂਕ)
{
  ਰੁੱਖ type = ਰੁੱਖ_TYPE (ਘਾਤਾਂਕ);
  ਗਿਣਤੀ ਰੁੱਖ_ਕੋਡ_2 ਕੋਡ = ਰੁੱਖ_ਕੋਡ (type);

  gcc_assert (INTEGRAL_TYPE_P (type));

  /* Convert enums to the result of applying the integer promotions to
     their underlying type.  */
  ਜੇ (ਕੋਡ == ENUMERAL_TYPE)
    {
      type = ENUM_UNDERLYING_TYPE (type);
      ਜੇ (c_promoting_integer_type_p (type))
	{
	  ਜੇ (TYPE_UNSIGNED (type)
	      && TYPE_PRECISION (type) == TYPE_PRECISION (integer_type_ਗੰਢ))
	    type = unsigned_type_ਗੰਢ;
	  ਨਹੀਂਤਾਂ
	    type = integer_type_ਗੰਢ;
	}

      ਵਾਪਸ convert (type, ਘਾਤਾਂਕ);
    }

  /* ??? This should no longer be needed now bit-fields have their
     proper types.  */
  ਜੇ (ਰੁੱਖ_ਕੋਡ (ਘਾਤਾਂਕ) == COMPONENT_REF
      && DECL_C_ਦੋਆਧਾਰੀ_ਅੰਕ_ਖੇਤਰ (ਰੁੱਖ_ਸੰਕਾਰਜ (ਘਾਤਾਂਕ, 1)))
    {
      ਜੇ (BITINT_TYPE_P (DECL_ਦੋਆਧਾਰੀ_ਅੰਕ_ਖੇਤਰ_TYPE (ਰੁੱਖ_ਸੰਕਾਰਜ (ਘਾਤਾਂਕ, 1))))
	{
	  ਰੁੱਖ btype = DECL_ਦੋਆਧਾਰੀ_ਅੰਕ_ਖੇਤਰ_TYPE (ਰੁੱਖ_ਸੰਕਾਰਜ (ਘਾਤਾਂਕ, 1));
	  ਜੇ (ਰੁੱਖ_ਕੋਡ (btype) == BITINT_TYPE)
	    ਵਾਪਸ convert (btype, ਘਾਤਾਂਕ);
	  ਨਹੀਂਤਾਂ
	    ਵਾਪਸ convert (ENUM_UNDERLYING_TYPE (btype), ਘਾਤਾਂਕ);
	}
      /* If it's thinner than an int, promote it like a
	 c_promoting_integer_type_p, otherwise leave it alone.  */
      ਜੇ (compare_ਰੁੱਖ_int (DECL_ਮਾਪ (ਰੁੱਖ_ਸੰਕਾਰਜ (ਘਾਤਾਂਕ, 1)),
			    TYPE_PRECISION (integer_type_ਗੰਢ)) < 0)
	ਵਾਪਸ convert (integer_type_ਗੰਢ, ਘਾਤਾਂਕ);
    }

  ਜੇ (c_promoting_integer_type_p (type))
    {
      /* Preserve unsignedness if not really getting any wider.  */
      ਜੇ (TYPE_UNSIGNED (type)
	  && TYPE_PRECISION (type) == TYPE_PRECISION (integer_type_ਗੰਢ))
	ਵਾਪਸ convert (unsigned_type_ਗੰਢ, ਘਾਤਾਂਕ);

      ਵਾਪਸ convert (integer_type_ਗੰਢ, ਘਾਤਾਂਕ);
    }

  ਵਾਪਸ ਘਾਤਾਂਕ;
}


/* Perform default promotions for C data used in expressions.
   Enumeral types or short or char are converted to int.
   In addition, manifest constants symbols are replaced by their values.  */

ਰੁੱਖ
default_conversion (ਰੁੱਖ ਘਾਤਾਂਕ)
{
  ਰੁੱਖ orig_exp;
  ਰੁੱਖ type = ਰੁੱਖ_TYPE (ਘਾਤਾਂਕ);
  ਗਿਣਤੀ ਰੁੱਖ_ਕੋਡ_2 ਕੋਡ = ਰੁੱਖ_ਕੋਡ (type);
  ਰੁੱਖ promoted_type;

  mark_exp_read (ਘਾਤਾਂਕ);
  /* We only generate a call to .ACCESS_WITH_SIZE when it is a read.  */
  ਜੇ (ਰੁੱਖ_ਕੋਡ (ਘਾਤਾਂਕ) == COMPONENT_REF
      && handle_counted_by_p (ਘਾਤਾਂਕ))
    ਘਾਤਾਂਕ = handle_counted_by_for_component_ref (ਵਿਅੰਜਕ_LOCATION (ਘਾਤਾਂਕ), ਘਾਤਾਂਕ);

  /* Functions and arrays have been converted during parsing.  */
  gcc_assert (ਕੋਡ != FUNCTION_TYPE);
  ਜੇ (ਕੋਡ == ARRAY_TYPE)
    ਵਾਪਸ ਘਾਤਾਂਕ;

  /* Constants can be used directly unless they're not loadable.  */
  ਜੇ (ਰੁੱਖ_ਕੋਡ (ਘਾਤਾਂਕ) == CONST_DECL)
    ਘਾਤਾਂਕ = DECL_INITIAL (ਘਾਤਾਂਕ);

  /* Strip no-op conversions.  */
  orig_exp = ਘਾਤਾਂਕ;
  STRIP_TYPE_NOPS (ਘਾਤਾਂਕ);

  copy_warning (ਘਾਤਾਂਕ, orig_exp);

  ਜੇ (ਕੋਡ == VOID_TYPE)
    {
      error_at (ਵਿਅੰਜਕ_LOC_OR_LOC (ਘਾਤਾਂਕ, ਨਿਵੇਸ਼_location),
		"void value not ignored as it ought to be");
      ਵਾਪਸ error_mark_ਗੰਢ;
    }

  ਘਾਤਾਂਕ = require_complete_type (ਵਿਅੰਜਕ_LOC_OR_LOC (ਘਾਤਾਂਕ, ਨਿਵੇਸ਼_location), ਘਾਤਾਂਕ);
  ਜੇ (ਘਾਤਾਂਕ == error_mark_ਗੰਢ)
    ਵਾਪਸ error_mark_ਗੰਢ;

  promoted_type = targetm.promoted_type (type);
  ਜੇ (promoted_type)
    ਵਾਪਸ convert (promoted_type, ਘਾਤਾਂਕ);

  ਜੇ (INTEGRAL_TYPE_P (type))
    {
      /* Avoid performing integral promotion of bit-precise integer
	 type bit-field to its corresponding bit-precise integer if
	 orig_exp is a cast to it to its underlying type.  */
      ਜੇ (orig_exp != ਘਾਤਾਂਕ
	  && ਰੁੱਖ_ਕੋਡ (ਘਾਤਾਂਕ) == COMPONENT_REF
	  && DECL_C_ਦੋਆਧਾਰੀ_ਅੰਕ_ਖੇਤਰ (ਰੁੱਖ_ਸੰਕਾਰਜ (ਘਾਤਾਂਕ, 1))
	  && BITINT_TYPE_P (DECL_ਦੋਆਧਾਰੀ_ਅੰਕ_ਖੇਤਰ_TYPE (ਰੁੱਖ_ਸੰਕਾਰਜ (ਘਾਤਾਂਕ, 1))))
	ਵਾਪਸ perform_integral_promotions (orig_exp);
      ਵਾਪਸ perform_integral_promotions (ਘਾਤਾਂਕ);
    }

  ਵਾਪਸ ਘਾਤਾਂਕ;
}

/* Look up COMPONENT in a structure or union TYPE.

   If the component name is not found, returns NULL_TREE.  Otherwise,
   the return value is a TREE_LIST, with each TREE_VALUE a FIELD_DECL
   stepping down the chain to the component, which is in the last
   TREE_VALUE of the list.  Normally the list is of length one, but if
   the component is embedded within (nested) anonymous structures or
   unions, the list steps down the chain to the component.  */

ਰੁੱਖ
lookup_ਖੇਤਰ (const_ਰੁੱਖ type, ਰੁੱਖ component)
{
  ਰੁੱਖ ਖੇਤਰ_2;

  /* If TYPE_LANG_SPECIFIC is set, then it is a sorted array of pointers
     to the field elements.  Use a binary search on this array to quickly
     find the element.  Otherwise, do a linear search.  TYPE_LANG_SPECIFIC
     will always be set for structures which have many elements.

     Duplicate field checking replaces duplicates with NULL_TREE so
     TYPE_LANG_SPECIFIC arrays are potentially no longer sorted.  In that
     case just iterate using DECL_CHAIN.  */

  ਜੇ (TYPE_LANG_SPECIFIC (type) && TYPE_LANG_SPECIFIC (type)->s
      && !ਵੇਖਿਆ_error ())
    {
      ਪੂਰਨ bot, ਸਿਖਰ, half;
      ਰੁੱਖ *ਖੇਤਰ_array = &TYPE_LANG_SPECIFIC (type)->s->elts[0];

      ਖੇਤਰ_2 = TYPE_FIELDS (type);
      bot = 0;
      ਸਿਖਰ = TYPE_LANG_SPECIFIC (type)->s->len;
      ਜਦੋਂ (ਸਿਖਰ - bot > 1)
	{
	  half = (ਸਿਖਰ - bot + 1) >> 1;
	  ਖੇਤਰ_2 = ਖੇਤਰ_array[bot+half];

	  ਜੇ (DECL_NAME (ਖੇਤਰ_2) == NULL_ਰੁੱਖ)
	    {
	      /* Step through all anon unions in linear fashion.  */
	      ਜਦੋਂ (DECL_NAME (ਖੇਤਰ_array[bot]) == NULL_ਰੁੱਖ)
		{
		  ਖੇਤਰ_2 = ਖੇਤਰ_array[bot++];
		  ਜੇ (ਰਿਕਾਰਡ_OR_UNION_TYPE_P (ਰੁੱਖ_TYPE (ਖੇਤਰ_2)))
		    {
		      ਰੁੱਖ anon = lookup_ਖੇਤਰ (ਰੁੱਖ_TYPE (ਖੇਤਰ_2), component);

		      ਜੇ (anon)
			ਵਾਪਸ ਰੁੱਖ_cons (NULL_ਰੁੱਖ, ਖੇਤਰ_2, anon);

		      /* The Plan 9 compiler permits referring
			 directly to an anonymous struct/union field
			 using a typedef name.  */
		      ਜੇ (flag_plan9_extensions
			  && TYPE_NAME (ਰੁੱਖ_TYPE (ਖੇਤਰ_2)) != NULL_ਰੁੱਖ
			  && (ਰੁੱਖ_ਕੋਡ (TYPE_NAME (ਰੁੱਖ_TYPE (ਖੇਤਰ_2)))
			      == TYPE_DECL)
			  && (DECL_NAME (TYPE_NAME (ਰੁੱਖ_TYPE (ਖੇਤਰ_2)))
			      == component))
			ਰੋਕੋ;
		    }
		}

	      /* Entire record is only anon unions.  */
	      ਜੇ (bot > ਸਿਖਰ)
		ਵਾਪਸ NULL_ਰੁੱਖ;

	      /* Restart the binary search, with new lower bound.  */
	      ਜਾਰੀ;
	    }

	  ਜੇ (DECL_NAME (ਖੇਤਰ_2) == component)
	    ਰੋਕੋ;
	  ਜੇ (DECL_NAME (ਖੇਤਰ_2) < component)
	    bot += half;
	  ਨਹੀਂਤਾਂ
	    ਸਿਖਰ = bot + half;
	}

      ਜੇ (DECL_NAME (ਖੇਤਰ_array[bot]) == component)
	ਖੇਤਰ_2 = ਖੇਤਰ_array[bot];
      ਨਹੀਂਤਾਂ ਜੇ (DECL_NAME (ਖੇਤਰ_2) != component)
	ਵਾਪਸ NULL_ਰੁੱਖ;
    }
  ਨਹੀਂਤਾਂ
    {
      ਲਈ (ਖੇਤਰ_2 = TYPE_FIELDS (type); ਖੇਤਰ_2; ਖੇਤਰ_2 = DECL_CHAIN (ਖੇਤਰ_2))
	{
	  ਜੇ (DECL_NAME (ਖੇਤਰ_2) == NULL_ਰੁੱਖ
	      && ਰਿਕਾਰਡ_OR_UNION_TYPE_P (ਰੁੱਖ_TYPE (ਖੇਤਰ_2)))
	    {
	      ਰੁੱਖ anon = lookup_ਖੇਤਰ (ਰੁੱਖ_TYPE (ਖੇਤਰ_2), component);

	      ਜੇ (anon)
		ਵਾਪਸ ਰੁੱਖ_cons (NULL_ਰੁੱਖ, ਖੇਤਰ_2, anon);

	      /* The Plan 9 compiler permits referring directly to an
		 anonymous struct/union field using a typedef
		 name.  */
	      ਜੇ (flag_plan9_extensions
		  && TYPE_NAME (ਰੁੱਖ_TYPE (ਖੇਤਰ_2)) != NULL_ਰੁੱਖ
		  && ਰੁੱਖ_ਕੋਡ (TYPE_NAME (ਰੁੱਖ_TYPE (ਖੇਤਰ_2))) == TYPE_DECL
		  && (DECL_NAME (TYPE_NAME (ਰੁੱਖ_TYPE (ਖੇਤਰ_2)))
		      == component))
		ਰੋਕੋ;
	    }

	  ਜੇ (DECL_NAME (ਖੇਤਰ_2) == component)
	    ਰੋਕੋ;
	}

      ਜੇ (ਖੇਤਰ_2 == NULL_ਰੁੱਖ)
	ਵਾਪਸ NULL_ਰੁੱਖ;
    }

  ਵਾਪਸ ਰੁੱਖ_cons (NULL_ਰੁੱਖ, ਖੇਤਰ_2, NULL_ਰੁੱਖ);
}

/* Recursively append candidate IDENTIFIER_NODEs to CANDIDATES.  */

ਸਥਿਰ ਖਾਲੀ
lookup_ਖੇਤਰ_fuzzy_ਲੱਭੋ_candidates (ਰੁੱਖ type, ਰੁੱਖ component,
				    vec<ਰੁੱਖ> *candidates)
{
  ਰੁੱਖ ਖੇਤਰ_2;
  ਲਈ (ਖੇਤਰ_2 = TYPE_FIELDS (type); ਖੇਤਰ_2; ਖੇਤਰ_2 = DECL_CHAIN (ਖੇਤਰ_2))
    {
      ਜੇ (DECL_NAME (ਖੇਤਰ_2) == NULL_ਰੁੱਖ
	  && ਰਿਕਾਰਡ_OR_UNION_TYPE_P (ਰੁੱਖ_TYPE (ਖੇਤਰ_2)))
	lookup_ਖੇਤਰ_fuzzy_ਲੱਭੋ_candidates (ਰੁੱਖ_TYPE (ਖੇਤਰ_2), component,
					    candidates);

      ਜੇ (DECL_NAME (ਖੇਤਰ_2))
	candidates->ਸੁਰੱਖਿਅਤ_ਧੱਕੋ (DECL_NAME (ਖੇਤਰ_2));
    }
}

/* Like "lookup_field", but find the closest matching IDENTIFIER_NODE,
   rather than returning a TREE_LIST for an exact match.  */

ਸਥਿਰ ਰੁੱਖ
lookup_ਖੇਤਰ_fuzzy (ਰੁੱਖ type, ਰੁੱਖ component)
{
  gcc_assert (ਰੁੱਖ_ਕੋਡ (component) == IDENTIFIER_ਗੰਢ);

  /* First, gather a list of candidates.  */
  auto_vec <ਰੁੱਖ> candidates;

  lookup_ਖੇਤਰ_fuzzy_ਲੱਭੋ_candidates (type, component,
				      &candidates);

  ਵਾਪਸ ਲੱਭੋ_closest_identifier (component, &candidates);
}

/* Support function for build_component_ref's error-handling.

   Given DATUM_TYPE, and "DATUM.COMPONENT", where DATUM is *not* a
   struct or union, should we suggest "DATUM->COMPONENT" as a hint?  */

ਸਥਿਰ ਤਾਰਕਿਕ
should_suggest_deref_p (ਰੁੱਖ datum_type)
{
  /* We don't do it for Objective-C, since Objective-C 2.0 dot-syntax
     allows "." for ptrs; we could be handling a failed attempt
     to access a property.  */
  ਜੇ (c_dialect_objc ())
    ਵਾਪਸ ਝੂਠ;

  /* Only suggest it for pointers...  */
  ਜੇ (ਰੁੱਖ_ਕੋਡ (datum_type) != ਸੂਚਕ_TYPE)
    ਵਾਪਸ ਝੂਠ;

  /* ...to structs/unions.  */
  ਰੁੱਖ underlying_type = ਰੁੱਖ_TYPE (datum_type);
  ਗਿਣਤੀ ਰੁੱਖ_ਕੋਡ_2 ਕੋਡ = ਰੁੱਖ_ਕੋਡ (underlying_type);
  ਜੇ (ਕੋਡ == ਰਿਕਾਰਡ_TYPE || ਕੋਡ == UNION_TYPE)
    ਵਾਪਸ ਸੱਚ;
  ਨਹੀਂਤਾਂ
    ਵਾਪਸ ਝੂਠ;
}

/* Give a component ref REF, decide whether we should handle its counted_by
   attribute based on its context:
   Do not handle counted_by when in offsetof, typeof and alignof operator.  */

ਸਥਿਰ ਤਾਰਕਿਕ
handle_counted_by_p (ਰੁੱਖ ref)
{
  gcc_assert (ਰੁੱਖ_ਕੋਡ (ref) == COMPONENT_REF);
  ਰੁੱਖ datum = ਰੁੱਖ_ਸੰਕਾਰਜ (ref, 0);
  /* If the component_ref is build for a offsetof, i.e., the datum
     of the component_ref is a indirect_ref of null_pointer_node,
     we should not generate call to .ACCESS_WITH_SIZE.  */
  ਜੇ (ਰੁੱਖ_ਕੋਡ (datum) == ਅਸਿੱਧਾ_REF
      && ਰੁੱਖ_ਸੰਕਾਰਜ (datum, 0) == null_ਸੂਚਕ_ਗੰਢ)
    ਵਾਪਸ ਝੂਠ;
  ਜੇ (ਵਿੱਚ_typeof || ਵਿੱਚ_alignof)
    ਵਾਪਸ ਝੂਠ;
  ਵਾਪਸ ਸੱਚ;
}

/* Given a component ref REF, if there is a counted_by attribute attached,
   issue error when the element_type is a structure or union including a
   flexible array member.  */

ਸਥਿਰ ਖਾਲੀ
check_counted_by_attribute (location_t loc, ਰੁੱਖ ref)
{
  ਰੁੱਖ subdatum = ਰੁੱਖ_ਸੰਕਾਰਜ (ref, 1);
  ਰੁੱਖ sub_type = ਰੁੱਖ_TYPE (subdatum);

  ਜੇ (!flexible_array_member_type_p (sub_type)
      && ਰੁੱਖ_ਕੋਡ (sub_type) != ਸੂਚਕ_TYPE)
    ਵਾਪਸ;

  ਰੁੱਖ element_type = ਰੁੱਖ_TYPE (sub_type);

  ਰੁੱਖ attr_counted_by = lookup_attribute ("counted_by",
					   DECL_ਗੁਣ (subdatum));
  ਜੇ (attr_counted_by)
    {
      /* Issue error when the element_type is a structure or
	union including a flexible array member.  */
      ਜੇ (ਰਿਕਾਰਡ_OR_UNION_TYPE_P (element_type)
	  && TYPE_INCLUDES_FLEXARRAY (element_type))
	{
	  error_at (loc,
		    "%<counted_by%> attribute is not allowed for a pointer to"
		    " structure or union with flexible array member");
	  ਵਾਪਸ;
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

ਸਥਿਰ ਰੁੱਖ
build_counted_by_ref (ਰੁੱਖ datum, ਰੁੱਖ subdatum,
		      ਰੁੱਖ *counted_by_type)
{
  ਰੁੱਖ sub_type = ਰੁੱਖ_TYPE (subdatum);
  ਜੇ (!flexible_array_member_type_p (sub_type)
      && ਰੁੱਖ_ਕੋਡ (sub_type) != ਸੂਚਕ_TYPE)
    ਵਾਪਸ NULL_ਰੁੱਖ;

  ਰੁੱਖ attr_counted_by = lookup_attribute ("counted_by",
					   DECL_ਗੁਣ (subdatum));
  ਜੇ (!attr_counted_by)
    ਵਾਪਸ NULL_ਰੁੱਖ;

  ਰੁੱਖ counted_by_ref = NULL_ਰੁੱਖ;
  *counted_by_type = NULL_ਰੁੱਖ;

  ਰੁੱਖ type = ਰੁੱਖ_TYPE (datum);

  /* If the type of the containing structure is an anonymous struct/union,
     and this anonymous struct/union is not a root type, get the first
     outer named structure/union type.  */
  ਜਦੋਂ (ਰੁੱਖ_ਕੋਡ (datum) == COMPONENT_REF
	 && c_type_ਟੈਗ (type) == NULL_ਰੁੱਖ
	 && DECL_NAME (ਰੁੱਖ_ਸੰਕਾਰਜ (datum, 1)) == NULL_ਰੁੱਖ)
    {
      datum = ਰੁੱਖ_ਸੰਕਾਰਜ (datum, 0);
      type = ਰੁੱਖ_TYPE (datum);
    }

  ਰੁੱਖ ਖੇਤਰ_id = ਰੁੱਖ_ਮੁੱਲ (ਰੁੱਖ_ਮੁੱਲ (attr_counted_by));
  ਰੁੱਖ counted_by_ਖੇਤਰ = lookup_ਖੇਤਰ (type, ਖੇਤਰ_id);
  gcc_assert (counted_by_ਖੇਤਰ);

  ਰੁੱਖ counted_by_subdatum;
  ਕਰੋ
    {
      counted_by_subdatum = ਰੁੱਖ_ਮੁੱਲ (counted_by_ਖੇਤਰ);
      /* Get the TYPE of the counted_by field.  */
      *counted_by_type = ਰੁੱਖ_TYPE (counted_by_subdatum);

      counted_by_ref
	= build3 (COMPONENT_REF, ਰੁੱਖ_TYPE (counted_by_subdatum),
		  datum, counted_by_subdatum, NULL_ਰੁੱਖ);

      datum = counted_by_ref;
      counted_by_ਖੇਤਰ = ਰੁੱਖ_CHAIN (counted_by_ਖੇਤਰ);
    }
  ਜਦੋਂ (counted_by_ਖੇਤਰ);

  counted_by_ref = build_fold_addr_ਵਿਅੰਜਕ (counted_by_ref);
  ਵਾਪਸ counted_by_ref;
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
ਸਥਿਰ ਰੁੱਖ
build_access_with_ਮਾਪ_for_counted_by (location_t loc, ਰੁੱਖ ref,
				       ਰੁੱਖ counted_by_ref,
				       ਰੁੱਖ counted_by_type)
{
  gcc_assert (flexible_array_member_type_p (ਰੁੱਖ_TYPE (ref))
	      || ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (ref)) == ਸੂਚਕ_TYPE);

  ਤਾਰਕਿਕ is_fam = flexible_array_member_type_p (ਰੁੱਖ_TYPE (ref));

  /* The result type of the call is a pointer to the flexible array type;
     or is the original pointer type to the pointer field with counted_by.  */
  ਰੁੱਖ ਨਤੀਜਾ_type = is_fam ? c_build_ਸੂਚਕ_type (ਰੁੱਖ_TYPE (ref))
		     : ਰੁੱਖ_TYPE (ref);

  ਰੁੱਖ element_type = ਰੁੱਖ_TYPE (ਰੁੱਖ_TYPE (ref));
  ਰੁੱਖ element_ਮਾਪ = VOID_TYPE_P (element_type)
		      ? ਮਾਪ_one_ਗੰਢ
		      : TYPE_ਮਾਪ_UNIT (element_type);
  ਜੇ (element_ਮਾਪ == NULL_ਰੁੱਖ)
    ਵਾਪਸ ref;

  ਰੁੱਖ ਪਹਿਲਾ_param = is_fam
		     ? c_fully_fold (array_ਮੰਜ਼ਿਲ_ਸੂਚਕ_conversion (loc, ref),
				     ਝੂਠ, ਨਿਰਾ)
		     : c_fully_fold (ref, ਝੂਠ, ਨਿਰਾ);
  ਰੁੱਖ ਦੂਜਾ_param
    = c_fully_fold (counted_by_ref, ਝੂਠ, ਨਿਰਾ);
  ਰੁੱਖ ਤੀਜਾ_param = build_int_cst (c_build_ਸੂਚਕ_type (counted_by_type), 0);

  ਰੁੱਖ call
    = build_call_ਵਿਅੰਜਕ_ਅੰਦਰੂਨੀ_loc (loc, IFN_ACCESS_WITH_ਮਾਪ,
				    ਨਤੀਜਾ_type, 4,
				    ਪਹਿਲਾ_param,
				    ਦੂਜਾ_param,
				    ਤੀਜਾ_param,
				    element_ਮਾਪ);

  /* Wrap the call with an INDIRECT_REF with the flexible array type.  */
  ਜੇ (is_fam)
    call = build1 (ਅਸਿੱਧਾ_REF, ਰੁੱਖ_TYPE (ref), call);
  ਸੈੱਟ_ਵਿਅੰਜਕ_LOCATION (call, loc);
  ਵਾਪਸ call;
}

/* For the COMPONENT_REF ref, check whether it has a counted_by attribute,
   if so, wrap this COMPONENT_REF with the corresponding CALL to the
   function .ACCESS_WITH_SIZE.
   Otherwise, return the ref itself.  */

ਰੁੱਖ
handle_counted_by_for_component_ref (location_t loc, ਰੁੱਖ ref)
{
  gcc_assert (ਰੁੱਖ_ਕੋਡ (ref) == COMPONENT_REF);
  ਰੁੱਖ datum = ਰੁੱਖ_ਸੰਕਾਰਜ (ref, 0);
  ਰੁੱਖ subdatum = ਰੁੱਖ_ਸੰਕਾਰਜ (ref, 1);
  ਰੁੱਖ counted_by_type = NULL_ਰੁੱਖ;

  ਜੇ (!(flexible_array_member_type_p (ਰੁੱਖ_TYPE (ref))
	|| ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (ref)) == ਸੂਚਕ_TYPE))
    ਵਾਪਸ ref;

  ਰੁੱਖ counted_by_ref = build_counted_by_ref (datum, subdatum,
					      &counted_by_type);
  ਜੇ (counted_by_ref)
    ref = build_access_with_ਮਾਪ_for_counted_by (loc, ref,
						 counted_by_ref,
						 counted_by_type);
  ਵਾਪਸ ref;
}

/* Make an expression to refer to the COMPONENT field of structure or
   union value DATUM.  COMPONENT is an IDENTIFIER_NODE.  LOC is the
   location of the COMPONENT_REF.  COMPONENT_LOC is the location
   of COMPONENT.  ARROW_LOC is the location of the first -> operand if
   it is from -> operator.
   If HANDLE_COUNTED_BY is true, check the counted_by attribute and generate
   a call to .ACCESS_WITH_SIZE.  Otherwise, ignore the attribute.  */

ਰੁੱਖ
build_component_ref (location_t loc, ਰੁੱਖ datum, ਰੁੱਖ component,
		     location_t component_loc, location_t arrow_loc)
{
  ਰੁੱਖ type = ਰੁੱਖ_TYPE (datum);
  ਗਿਣਤੀ ਰੁੱਖ_ਕੋਡ_2 ਕੋਡ = ਰੁੱਖ_ਕੋਡ (type);
  ਰੁੱਖ ਖੇਤਰ_2 = ਨਿਰਾ;
  ਰੁੱਖ ref;
  ਤਾਰਕਿਕ datum_lvalue = lvalue_p (datum);

  ਜੇ (!objc_is_ਜਨਤਕ (datum, component))
    ਵਾਪਸ error_mark_ਗੰਢ;

  /* Detect Objective-C property syntax object.property.  */
  ਜੇ (c_dialect_objc ()
      && (ref = objc_maybe_build_component_ref (datum, component)))
    ਵਾਪਸ ref;

  /* See if there is a field or component with name COMPONENT.  */

  ਜੇ (ਕੋਡ == ਰਿਕਾਰਡ_TYPE || ਕੋਡ == UNION_TYPE)
    {
      ਜੇ (!COMPLETE_TYPE_P (type))
	{
	  c_incomplete_type_error (loc, NULL_ਰੁੱਖ, type);
	  ਵਾਪਸ error_mark_ਗੰਢ;
	}

      ਖੇਤਰ_2 = lookup_ਖੇਤਰ (type, component);

      ਜੇ (!ਖੇਤਰ_2)
	{
	  ਰੁੱਖ guessed_id = lookup_ਖੇਤਰ_fuzzy (type, component);
	  ਜੇ (guessed_id)
	    {
	      /* Attempt to provide a fixit replacement hint, if
		 we have a valid range for the component.  */
	      location_t reported_loc
		= (component_loc != UNKNOWN_LOCATION) ? component_loc : loc;
	      gcc_rich_location rich_loc (reported_loc);
	      ਜੇ (component_loc != UNKNOWN_LOCATION)
		rich_loc.ਜੋੜੋ_fixit_misspelled_id (component_loc, guessed_id);
	      error_at (&rich_loc,
			"%qT has no member named %qE; did you mean %qE?",
			type, component, guessed_id);
	    }
	  ਨਹੀਂਤਾਂ
	    error_at (loc, "%qT has no member named %qE", type, component);
	  ਵਾਪਸ error_mark_ਗੰਢ;
	}

      /* Accessing elements of atomic structures or unions is undefined
	 behavior (C11 6.5.2.3#5).  */
      ਜੇ (TYPE_ATOMIC (type) && c_inhibit_evaluation_warnings == 0)
	{
	  ਜੇ (ਕੋਡ == ਰਿਕਾਰਡ_TYPE)
	    warning_at (loc, 0, "accessing a member %qE of an atomic "
			"structure %qE", component, datum);
	  ਨਹੀਂਤਾਂ
	    warning_at (loc, 0, "accessing a member %qE of an atomic "
			"union %qE", component, datum);
	}

      /* Chain the COMPONENT_REFs if necessary down to the FIELD.
	 This might be better solved in future the way the C++ front
	 end does it - by giving the anonymous entities each a
	 separate name and type, and then have build_component_ref
	 recursively call itself.  We can't do that here.  */
      ਕਰੋ
	{
	  ਰੁੱਖ subdatum = ਰੁੱਖ_ਮੁੱਲ (ਖੇਤਰ_2);
	  ਪੂਰਨ quals;
	  ਰੁੱਖ subtype;
	  ਤਾਰਕਿਕ use_datum_quals;

	  ਜੇ (ਰੁੱਖ_TYPE (subdatum) == error_mark_ਗੰਢ)
	    ਵਾਪਸ error_mark_ਗੰਢ;

	  /* If this is an rvalue, it does not have qualifiers in C
	     standard terms and we must avoid propagating such
	     qualifiers down to a non-lvalue array that is then
	     converted to a pointer.  */
	  use_datum_quals = (datum_lvalue
			     || ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (subdatum)) != ARRAY_TYPE);

	  quals = TYPE_QUALS (strip_array_types (ਰੁੱਖ_TYPE (subdatum)));
	  ਜੇ (use_datum_quals)
	    quals |= TYPE_QUALS (ਰੁੱਖ_TYPE (datum));
	  subtype = c_build_qualified_type (ਰੁੱਖ_TYPE (subdatum), quals);

	  ref = build3 (COMPONENT_REF, subtype, datum, subdatum,
			NULL_ਰੁੱਖ);
	  ਸੈੱਟ_ਵਿਅੰਜਕ_LOCATION (ref, loc);

	  check_counted_by_attribute (loc, ref);

	  ਜੇ (ਰੁੱਖ_READONLY (subdatum)
	      || (use_datum_quals && ਰੁੱਖ_READONLY (datum)))
	    ਰੁੱਖ_READONLY (ref) = 1;
	  ਜੇ (ਰੁੱਖ_THIS_VOLATILE (subdatum)
	      || (use_datum_quals && ਰੁੱਖ_THIS_VOLATILE (datum)))
	    ਰੁੱਖ_THIS_VOLATILE (ref) = 1;

	  ਜੇ (ਰੁੱਖ_UNAVAILABLE (subdatum))
	    error_unavailable_use (subdatum, NULL_ਰੁੱਖ);
	  ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_DEPRECATED (subdatum))
	    warn_deprecated_use (subdatum, NULL_ਰੁੱਖ);

	  datum = ref;

	  ਖੇਤਰ_2 = ਰੁੱਖ_CHAIN (ਖੇਤਰ_2);
	}
      ਜਦੋਂ (ਖੇਤਰ_2);

      ਵਾਪਸ ref;
    }
  ਨਹੀਂਤਾਂ ਜੇ (should_suggest_deref_p (type))
    {
      /* Special-case the error message for "ptr.field" for the case
	 where the user has confused "." vs "->".  */
      rich_location richloc (ਸਤਰ_ਸਾਰਣੀ, loc);
      ਜੇ (ਅਸਿੱਧਾ_REF_P (datum) && arrow_loc != UNKNOWN_LOCATION)
	{
	  richloc.ਜੋੜੋ_fixit_ਪਾਓ_before (arrow_loc, "(*");
	  richloc.ਜੋੜੋ_fixit_ਪਾਓ_after (arrow_loc, ")");
	  error_at (&richloc,
		    "%qE is a pointer to pointer; did you mean to dereference "
		    "it before applying %<->%> to it?",
		    ਰੁੱਖ_ਸੰਕਾਰਜ (datum, 0));
	}
      ਨਹੀਂਤਾਂ
	{
	  /* "loc" should be the "." token.  */
	  richloc.ਜੋੜੋ_fixit_replace ("->");
	  error_at (&richloc,
		    "%qE is a pointer; did you mean to use %<->%>?",
		    datum);
	}
      ਵਾਪਸ error_mark_ਗੰਢ;
    }
  ਨਹੀਂਤਾਂ ਜੇ (ਕੋਡ != ERROR_MARK)
    error_at (loc,
	      "request for member %qE in something not a structure or union",
	      component);

  ਵਾਪਸ error_mark_ਗੰਢ;
}

/* Given an expression PTR for a pointer, return an expression
   for the value pointed to.
   ERRORSTRING is the name of the operator to appear in error messages.

   LOC is the location to use for the generated tree.  */

ਰੁੱਖ
build_ਅਸਿੱਧਾ_ref (location_t loc, ਰੁੱਖ ptr, ref_operator errstring)
{
  ਰੁੱਖ ਸੂਚਕ = default_conversion (ptr);
  ਰੁੱਖ type = ਰੁੱਖ_TYPE (ਸੂਚਕ);
  ਰੁੱਖ ref;

  ਜੇ (ਰੁੱਖ_ਕੋਡ (type) == ਸੂਚਕ_TYPE)
    {
      ਜੇ (CONVERT_ਵਿਅੰਜਕ_P (ਸੂਚਕ)
          || ਰੁੱਖ_ਕੋਡ (ਸੂਚਕ) == VIEW_CONVERT_ਵਿਅੰਜਕ)
	{
	  /* If a warning is issued, mark it to avoid duplicates from
	     the backend.  This only needs to be done at
	     warn_strict_aliasing > 2.  */
	  ਜੇ (warn_strict_aliasing > 2)
	    ਜੇ (strict_aliasing_warning (ਵਿਅੰਜਕ_LOCATION (ਸੂਚਕ),
					 type, ਰੁੱਖ_ਸੰਕਾਰਜ (ਸੂਚਕ, 0)))
	      suppress_warning (ਸੂਚਕ, OPT_Wstrict_aliasing_);
	}

      ਜੇ (ਰੁੱਖ_ਕੋਡ (ਸੂਚਕ) == ADDR_ਵਿਅੰਜਕ
	  && (ਰੁੱਖ_TYPE (ਰੁੱਖ_ਸੰਕਾਰਜ (ਸੂਚਕ, 0))
	      == ਰੁੱਖ_TYPE (type)))
	{
	  ref = ਰੁੱਖ_ਸੰਕਾਰਜ (ਸੂਚਕ, 0);
	  protected_ਸੈੱਟ_ਵਿਅੰਜਕ_location (ref, loc);
	  ਵਾਪਸ ref;
	}
      ਨਹੀਂਤਾਂ
	{
	  ਰੁੱਖ t = ਰੁੱਖ_TYPE (type);

	  ref = build1 (ਅਸਿੱਧਾ_REF, t, ਸੂਚਕ);

	  ਜੇ (VOID_TYPE_P (t) && c_inhibit_evaluation_warnings == 0)
	    warning_at (loc, 0, "dereferencing %<void *%> pointer");

	  /* We *must* set TREE_READONLY when dereferencing a pointer to const,
	     so that we get the proper error message if the result is used
	     to assign to.  Also, &* is supposed to be a no-op.
	     And ANSI C seems to specify that the type of the result
	     should be the const type.  */
	  /* A de-reference of a pointer to const is not a const.  It is valid
	     to change it via some other pointer.  */
	  ਰੁੱਖ_READONLY (ref) = TYPE_READONLY (t);
	  ਰੁੱਖ_SIDE_EFFECTS (ref)
	    = TYPE_VOLATILE (t) || ਰੁੱਖ_SIDE_EFFECTS (ਸੂਚਕ);
	  ਰੁੱਖ_THIS_VOLATILE (ref) = TYPE_VOLATILE (t);
	  protected_ਸੈੱਟ_ਵਿਅੰਜਕ_location (ref, loc);
	  ਵਾਪਸ ref;
	}
    }
  ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਕੋਡ (ਸੂਚਕ) != ERROR_MARK)
    invalid_indirection_error (loc, type, errstring);

  ਵਾਪਸ error_mark_ਗੰਢ;
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

ਰੁੱਖ
build_array_ref (location_t loc, ਰੁੱਖ array, ਰੁੱਖ ਸੂਚਕਾਂਕ)
{
  ਰੁੱਖ ret;
  ਤਾਰਕਿਕ swapped = ਝੂਠ;
  ਜੇ (ਰੁੱਖ_TYPE (array) == error_mark_ਗੰਢ
      || ਰੁੱਖ_TYPE (ਸੂਚਕਾਂਕ) == error_mark_ਗੰਢ)
    ਵਾਪਸ error_mark_ਗੰਢ;

  ਜੇ (ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (array)) != ARRAY_TYPE
      && ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (array)) != ਸੂਚਕ_TYPE
      /* Allow vector[index] but not index[vector].  */
      && !gnu_ਸਦਿਸ਼_type_p (ਰੁੱਖ_TYPE (array)))
    {
      ਜੇ (ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (ਸੂਚਕਾਂਕ)) != ARRAY_TYPE
	  && ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (ਸੂਚਕਾਂਕ)) != ਸੂਚਕ_TYPE)
	{
          error_at (loc,
            "subscripted value is neither array nor pointer nor vector");

	  ਵਾਪਸ error_mark_ਗੰਢ;
	}
      std::ਅਦਲਾ_ਬਦਲੀ (array, ਸੂਚਕਾਂਕ);
      swapped = ਸੱਚ;
    }

  ਜੇ (!INTEGRAL_TYPE_P (ਰੁੱਖ_TYPE (ਸੂਚਕਾਂਕ)))
    {
      error_at (loc, "array subscript is not an integer");
      ਵਾਪਸ error_mark_ਗੰਢ;
    }

  ਜੇ (ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (ਰੁੱਖ_TYPE (array))) == FUNCTION_TYPE)
    {
      error_at (loc, "subscripted value is pointer to function");
      ਵਾਪਸ error_mark_ਗੰਢ;
    }

  /* ??? Existing practice has been to warn only when the char
     index is syntactically the index, not for char[array].  */
  ਜੇ (!swapped)
     warn_array_subscript_with_type_char (loc, ਸੂਚਕਾਂਕ);

  /* Apply default promotions *after* noticing character types.  */
  ਸੂਚਕਾਂਕ = default_conversion (ਸੂਚਕਾਂਕ);
  ਜੇ (ਸੂਚਕਾਂਕ == error_mark_ਗੰਢ)
    ਵਾਪਸ error_mark_ਗੰਢ;

  gcc_assert (ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (ਸੂਚਕਾਂਕ)) == INTEGER_TYPE
	      || ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (ਸੂਚਕਾਂਕ)) == BITINT_TYPE);

  ਤਾਰਕਿਕ was_ਸਦਿਸ਼ = ਸਦਿਸ਼_TYPE_P (ਰੁੱਖ_TYPE (array));
  ਤਾਰਕਿਕ non_lvalue = convert_ਸਦਿਸ਼_ਮੰਜ਼ਿਲ_array_for_subscript (loc, &array, ਸੂਚਕਾਂਕ);

  /* We only generate a call to .ACCESS_WITH_SIZE when it is a read.  */
  ਜੇ (ਰੁੱਖ_ਕੋਡ (array) == COMPONENT_REF
      && handle_counted_by_p (array))
    array = handle_counted_by_for_component_ref (loc, array);

  ਜੇ (ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (array)) == ARRAY_TYPE)
    {
      ਰੁੱਖ rval, type;

      /* An array that is indexed by a non-constant
	 cannot be stored in a register; we must be able to do
	 address arithmetic on its address.
	 Likewise an array of elements of variable size.  */
      ਜੇ (ਰੁੱਖ_ਕੋਡ (ਸੂਚਕਾਂਕ) != INTEGER_CST
	  || (COMPLETE_TYPE_P (ਰੁੱਖ_TYPE (ਰੁੱਖ_TYPE (array)))
	      && ਰੁੱਖ_ਕੋਡ (TYPE_ਮਾਪ (ਰੁੱਖ_TYPE (ਰੁੱਖ_TYPE (array)))) != INTEGER_CST))
	{
	  ਜੇ (!c_mark_addressable (array, ਸੱਚ, ਸੱਚ))
	    ਵਾਪਸ error_mark_ਗੰਢ;
	}
      /* An array that is indexed by a constant value which is not within
	 the array bounds cannot be stored in a register either; because we
	 would get a crash in store_bit_field/extract_bit_field when trying
	 to access a non-existent part of the register.  */
      ਜੇ (ਰੁੱਖ_ਕੋਡ (ਸੂਚਕਾਂਕ) == INTEGER_CST
	  && TYPE_DOMAIN (ਰੁੱਖ_TYPE (array))
	  && !int_ਸਮਾਉਂਦਾ_type_p (ਸੂਚਕਾਂਕ, TYPE_DOMAIN (ਰੁੱਖ_TYPE (array))))
	{
	  ਜੇ (!c_mark_addressable (array, ਝੂਠ, ਸੱਚ))
	    ਵਾਪਸ error_mark_ਗੰਢ;
	  /* ISO C2Y disallows a negative integer constant expression index
	     when array subscripting has an operand of array type.  */
	  ਜੇ (flag_isoc2y
	      && !ਰੁੱਖ_ਉਛਾਲ (ਸੂਚਕਾਂਕ)
	      && ਰੁੱਖ_int_cst_sgn (ਸੂਚਕਾਂਕ) < 0)
	    error_at (loc, "array subscript is negative");
	}

      ਜੇ ((pedantic || warn_c90_c99_compat || warn_c23_c2y_compat)
	  && ! was_ਸਦਿਸ਼)
	{
	  ਰੁੱਖ foo = array;
	  ਜਦੋਂ (ਰੁੱਖ_ਕੋਡ (foo) == COMPONENT_REF)
	    foo = ਰੁੱਖ_ਸੰਕਾਰਜ (foo, 0);
	  ਜੇ ((VAR_P (foo) && C_DECL_ਰਜਿਸਟਰ (foo))
	      || (ਰੁੱਖ_ਕੋਡ (foo) == COMPOUND_LITERAL_ਵਿਅੰਜਕ
		  && C_DECL_ਰਜਿਸਟਰ (COMPOUND_LITERAL_ਵਿਅੰਜਕ_DECL (foo))))
	    pedwarn_c23 (loc, OPT_Wpedantic,
			 "ISO C forbids subscripting %<register%> array "
			 "before C2Y");
	  ਨਹੀਂਤਾਂ ਜੇ (!lvalue_p (foo))
	    pedwarn_c90 (loc, OPT_Wpedantic,
			 "ISO C90 forbids subscripting non-lvalue "
			 "array");
	}

      ਜੇ (ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (ਸੂਚਕਾਂਕ)) == BITINT_TYPE
	  && TYPE_PRECISION (ਰੁੱਖ_TYPE (ਸੂਚਕਾਂਕ)) > TYPE_PRECISION (sizetype))
	ਸੂਚਕਾਂਕ = fold_convert (sizetype, ਸੂਚਕਾਂਕ);

      type = ਰੁੱਖ_TYPE (ਰੁੱਖ_TYPE (array));
      rval = build4 (ARRAY_REF, type, array, ਸੂਚਕਾਂਕ, NULL_ਰੁੱਖ, NULL_ਰੁੱਖ);
      /* Array ref is const/volatile if the array elements are
	 or if the array is.  */
      ਰੁੱਖ_READONLY (rval)
	|= (TYPE_READONLY (ਰੁੱਖ_TYPE (ਰੁੱਖ_TYPE (array)))
	    | ਰੁੱਖ_READONLY (array));
      ਰੁੱਖ_SIDE_EFFECTS (rval)
	|= (TYPE_VOLATILE (ਰੁੱਖ_TYPE (ਰੁੱਖ_TYPE (array)))
	    | ਰੁੱਖ_SIDE_EFFECTS (array));
      ਰੁੱਖ_THIS_VOLATILE (rval)
	|= (TYPE_VOLATILE (ਰੁੱਖ_TYPE (ਰੁੱਖ_TYPE (array)))
	    /* This was added by rms on 16 Nov 91.
	       It fixes  vol struct foo *a;  a->elts[1]
	       in an inline function.
	       Hope it doesn't break something else.  */
	    | ਰੁੱਖ_THIS_VOLATILE (array));
      ret = require_complete_type (loc, rval);
      protected_ਸੈੱਟ_ਵਿਅੰਜਕ_location (ret, loc);
      ਜੇ (non_lvalue)
	ret = non_lvalue_loc (loc, ret);
      ਵਾਪਸ ret;
    }
  ਨਹੀਂਤਾਂ
    {
      ਰੁੱਖ ar = default_conversion (array);

      ਜੇ (ar == error_mark_ਗੰਢ)
	ਵਾਪਸ ar;

      gcc_assert (ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (ar)) == ਸੂਚਕ_TYPE);
      gcc_assert (ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (ਰੁੱਖ_TYPE (ar))) != FUNCTION_TYPE);

      ret = build_ਅਸਿੱਧਾ_ref (loc, build_ਦੁਆਧਾਰੀ_op (loc, PLUS_ਵਿਅੰਜਕ, ar,
						      ਸੂਚਕਾਂਕ, ਝੂਠ),
				RO_ARRAY_INDEXING);
      ਜੇ (non_lvalue)
	ret = non_lvalue_loc (loc, ret);
      ਵਾਪਸ ret;
    }
}

/* Build an OpenMP array section reference, creating an exact type for the
   resulting expression based on the element type and bounds if possible.  If
   we have variable bounds, create an incomplete array type for the result
   instead.  */

ਰੁੱਖ
build_omp_array_section (location_t loc, ਰੁੱਖ array, ਰੁੱਖ ਸੂਚਕਾਂਕ, ਰੁੱਖ ਲੰਮਾਈ)
{
  ਰੁੱਖ type = ਰੁੱਖ_TYPE (array);
  gcc_assert (type);

  ਰੁੱਖ sectype, eltype = ਰੁੱਖ_TYPE (type);

  /* It's not an array or pointer type.  Just reuse the type of the original
     expression as the type of the array section (an error will be raised
     anyway, later).  */
  ਜੇ (eltype == NULL_ਰੁੱਖ || error_ਸੰਕਾਰਜ_p (eltype))
    sectype = ਰੁੱਖ_TYPE (array);
  ਨਹੀਂਤਾਂ
    {
      ਰੁੱਖ idxtype = NULL_ਰੁੱਖ;

      ਜੇ (ਸੂਚਕਾਂਕ != NULL_ਰੁੱਖ
	  && ਲੰਮਾਈ != NULL_ਰੁੱਖ
	  && INTEGRAL_TYPE_P (ਰੁੱਖ_TYPE (ਸੂਚਕਾਂਕ))
	  && INTEGRAL_TYPE_P (ਰੁੱਖ_TYPE (ਲੰਮਾਈ)))
	{
	  ਰੁੱਖ ਨੀਵਾਂ = fold_convert (sizetype, ਸੂਚਕਾਂਕ);
	  ਰੁੱਖ ਉੱਚਾ = fold_convert (sizetype, ਲੰਮਾਈ);
	  ਉੱਚਾ = ਮਾਪ_binop (PLUS_ਵਿਅੰਜਕ, ਨੀਵਾਂ, ਉੱਚਾ);
	  ਉੱਚਾ = ਮਾਪ_binop (MINUS_ਵਿਅੰਜਕ, ਉੱਚਾ, ਮਾਪ_one_ਗੰਢ);
	  idxtype = build_range_type (sizetype, ਨੀਵਾਂ, ਉੱਚਾ);
	}
      ਨਹੀਂਤਾਂ ਜੇ ((ਸੂਚਕਾਂਕ == NULL_ਰੁੱਖ || integer_zerop (ਸੂਚਕਾਂਕ))
	       && ਲੰਮਾਈ != NULL_ਰੁੱਖ
	       && INTEGRAL_TYPE_P (ਰੁੱਖ_TYPE (ਲੰਮਾਈ)))
	idxtype = build_ਸੂਚਕਾਂਕ_type (ਲੰਮਾਈ);

      gcc_assert (!error_ਸੰਕਾਰਜ_p (idxtype));

      sectype = c_build_array_type (eltype, idxtype);
    }

  ਵਾਪਸ build3_loc (loc, OMP_ARRAY_SECTION, sectype, array, ਸੂਚਕਾਂਕ, ਲੰਮਾਈ);
}


/* Record that REF is used.  This is relevant for undeclared static
   function and declarations referenced from a non-local context.
   ADDRESS indicates whether the address is taken.  */

ਖਾਲੀ
mark_decl_ਵਰਤਿਆ (ਰੁੱਖ ref, ਤਾਰਕਿਕ ਪਤਾ)
{
  ਜੇ (!ref || !DECL_P (ref) || ਵਿੱਚ_alignof)
    ਵਾਪਸ;

  /* Non-file-scope and non-local reference in nested function.  */
  ਤਾਰਕਿਕ nonloc_p = current_function_decl && DECL_CONTEXT (ref)
		  && DECL_CONTEXT (current_function_decl)
		  && DECL_CONTEXT (ref) != current_function_decl;

  /* An undeclared static function.  */
  ਤਾਰਕਿਕ static_p = ਰੁੱਖ_ਕੋਡ (ref) == FUNCTION_DECL
		  && DECL_INITIAL (ref) == NULL_ਰੁੱਖ
		  && DECL_EXTERNAL (ref)
		  && !ਰੁੱਖ_ਜਨਤਕ (ref);

  ਜੇ (!static_p && !nonloc_p)
    ਵਾਪਸ;

  /* If we may be in an unevaluated context, delay the decision.  */
  ਜੇ (ਵਿੱਚ_sizeof || ਵਿੱਚ_typeof || ਵਿੱਚ_countof || ਵਿੱਚ_generic)
    ਵਾਪਸ ਰਿਕਾਰਡ_maybe_ਵਰਤਿਆ_decl (ref, ਪਤਾ);

  ਜੇ (static_p)
    C_DECL_ਵਰਤਿਆ (ref) = 1;

  ਜੇ (nonloc_p && (VAR_OR_FUNCTION_DECL_P (ref)
		   || ਰੁੱਖ_ਕੋਡ (ref) == PARM_DECL))
    DECL_NONLOCAL (ref) = 1;

  /* Nothing to do anymore.  */
  ਜੇ (!nonloc_p || C_FUNC_NONLOCAL_CONTEXT (current_function_decl))
    ਵਾਪਸ;

  /* Filter out the cases where referencing a non-local variable does not
     require a non-local context passed via the static chain.  */
  ਜੇ (!c_type_variably_modified_p (ਰੁੱਖ_TYPE (ref)))
    ਚੋਣ (ਰੁੱਖ_ਕੋਡ (ref))
      {
      ਹਾਲਤ FUNCTION_DECL:
	/* Use of another local function that requires no context is ok.  */
	ਜੇ (!C_FUNC_NONLOCAL_CONTEXT (ref) && DECL_INITIAL (ref))
	  ਵਾਪਸ;
	ਰੋਕੋ;
      ਹਾਲਤ VAR_DECL:
	/* Static variables and constexpr are ok, but for the later only
	   when the address is not taken.  */
	ਜੇ (ਰੁੱਖ_STATIC (ref) || (C_DECL_DECLARED_CONSTEXPR (ref) && !ਪਤਾ))
	  ਵਾਪਸ;
	ਰੋਕੋ;
      ਹਾਲਤ TYPE_DECL:
	/* A typedef is ok when not for a variably-modified type. */
	ਵਾਪਸ;
      ਹਾਲਤ CONST_DECL:
	/* An enumeration constant is ok. */
	ਵਾਪਸ;
      ਹਾਲਤ PARM_DECL:
	ਰੋਕੋ;
      ਹਾਲਤ LABEL_DECL:
	ਰੋਕੋ;
      ਮੂਲ:
	gcc_unreachable ();
    }

  /* Mark all parent functions up to the nesting level of the variable as
     as needing the non-local context.  */
  ਲਈ (ਰੁੱਖ cont = current_function_decl; cont; cont = DECL_CONTEXT (cont))
    {
      ਜੇ (cont == DECL_CONTEXT (ref))
	ਰੋਕੋ;

      /* There should not be any other type of context used for function
	 except TRANSLATION_UNIT_DECL which we should be able to reach.  */
      gcc_checking_assert (ਰੁੱਖ_ਕੋਡ (cont) == FUNCTION_DECL);

      ਜੇ (ਰੁੱਖ_ਕੋਡ (cont) == FUNCTION_DECL)
	C_FUNC_NONLOCAL_CONTEXT (cont) = 1;
    }
}


/* Build an external reference to identifier ID.  FUN indicates
   whether this will be used for a function call.  LOC is the source
   location of the identifier.  This sets *TYPE to the type of the
   identifier, which is not the same as the type of the returned value
   for CONST_DECLs defined as enum constants.  If the type of the
   identifier is not available, *TYPE is set to NULL.  */
ਰੁੱਖ
build_external_ref (location_t loc, ਰੁੱਖ id, ਤਾਰਕਿਕ fun, ਰੁੱਖ *type)
{
  ਰੁੱਖ ref;
  ਰੁੱਖ decl = lookup_name (id);

  /* In Objective-C, an instance variable (ivar) may be preferred to
     whatever lookup_name() found.  */
  decl = objc_lookup_ivar (decl, id);

  *type = ਨਿਰਾ;
  ਜੇ (decl && decl != error_mark_ਗੰਢ)
    {
      ref = decl;
      *type = ਰੁੱਖ_TYPE (ref);
      ਜੇ (DECL_P (decl) && C_DECL_UNDERSPECIFIED (decl))
	error_at (loc, "underspecified %qD referenced in its initializer",
		  decl);
    }
  ਨਹੀਂਤਾਂ ਜੇ (fun)
    /* Implicit function declaration.  */
    ref = implicitly_declare (loc, id);
  ਨਹੀਂਤਾਂ ਜੇ (decl == error_mark_ਗੰਢ)
    /* Don't complain about something that's already been
       complained about.  */
    ਵਾਪਸ error_mark_ਗੰਢ;
  ਨਹੀਂਤਾਂ
    {
      undeclared_variable (loc, id);
      ਵਾਪਸ error_mark_ਗੰਢ;
    }

  /* For an OpenMP map clause, we can get better diagnostics for decls with
     unmappable types if we return the decl with an error_mark_node type,
     rather than returning error_mark_node for the decl itself.  */
  ਜੇ (ਰੁੱਖ_TYPE (ref) == error_mark_ਗੰਢ
      && !c_omp_array_section_p)
    ਵਾਪਸ error_mark_ਗੰਢ;

  ਜੇ (ਰੁੱਖ_UNAVAILABLE (ref))
    error_unavailable_use (ref, NULL_ਰੁੱਖ);
  ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_DEPRECATED (ref))
    warn_deprecated_use (ref, NULL_ਰੁੱਖ);

  /* Recursive call does not count as usage.  */
  ਜੇ (ref != current_function_decl)
    {
      ਰੁੱਖ_ਵਰਤਿਆ (ref) = 1;
    }

  mark_decl_ਵਰਤਿਆ (ref, ਝੂਠ);

  ਜੇ (ਰੁੱਖ_ਕੋਡ (ref) == CONST_DECL)
    {
      ਵਰਤਿਆ_types_ਪਾਓ (ਰੁੱਖ_TYPE (ref));

      ਜੇ (warn_cxx_compat
	  && ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (ref)) == ENUMERAL_TYPE
	  && C_TYPE_DEFINED_ਵਿੱਚ_STRUCT (ਰੁੱਖ_TYPE (ref)))
	{
	  warning_at (loc, OPT_Wc___compat,
		      "enum constant defined in struct or union "
		      "is not visible in C++");
	  inform (DECL_ਸਰੋਤ_LOCATION (ref), "enum constant defined here");
	}

      ref = DECL_INITIAL (ref);
      ਰੁੱਖ_CONSTANT (ref) = 1;
    }
  /* C99 6.7.4p3: An inline definition of a function with external
     linkage ... shall not contain a reference to an identifier with
     internal linkage.  */
  ਨਹੀਂਤਾਂ ਜੇ (current_function_decl != NULL_ਰੁੱਖ
	   && DECL_DECLARED_INLINE_P (current_function_decl)
	   && DECL_EXTERNAL (current_function_decl)
	   && VAR_OR_FUNCTION_DECL_P (ref)
	   && (!VAR_P (ref) || ਰੁੱਖ_STATIC (ref))
	   && ! ਰੁੱਖ_ਜਨਤਕ (ref)
	   && DECL_CONTEXT (ref) != current_function_decl)
    ਰਿਕਾਰਡ_inline_static (loc, current_function_decl, ref,
			  csi_ਅੰਦਰੂਨੀ);

  ਵਾਪਸ ref;
}

ਸਥਿਰ ਬਣਤਰ maybe_ਵਰਤਿਆ_decl *maybe_ਵਰਤਿਆ_decls;

/* Record that DECL, a reference seen inside sizeof or typeof or _Countof or
   _Generic, might be used if the operand of sizeof is a VLA type or the
   operand of typeof is a variably modified type or the operand of _Countof has
   a variable number of elements or the operand of _Generic is the one selected
   as the result.  */

ਸਥਿਰ ਖਾਲੀ
ਰਿਕਾਰਡ_maybe_ਵਰਤਿਆ_decl (ਰੁੱਖ decl, ਤਾਰਕਿਕ ਪਤਾ)
{
  ਬਣਤਰ maybe_ਵਰਤਿਆ_decl *t = XOBNEW (&parser_obstack, ਬਣਤਰ maybe_ਵਰਤਿਆ_decl);
  t->decl = decl;
  t->level = ਵਿੱਚ_sizeof + ਵਿੱਚ_typeof + ਵਿੱਚ_countof + ਵਿੱਚ_generic;
  t->ਪਤਾ = ਪਤਾ;
  t->ਅਗਲਾ = maybe_ਵਰਤਿਆ_decls;
  maybe_ਵਰਤਿਆ_decls = t;
}

/* Pop the stack of decls possibly used inside sizeof or typeof or _Countof or
   _Generic.  If USED is false, just discard them.  If it is true, mark them
   used (if no longer inside sizeof or typeof or _Countof or _Generic) or move
   them to the next level up (if still inside sizeof or typeof or _Countof or
   _Generic).  */

ਖਾਲੀ
ਕੱਢੋ_maybe_ਵਰਤਿਆ (ਤਾਰਕਿਕ ਵਰਤਿਆ)
{
  ਬਣਤਰ maybe_ਵਰਤਿਆ_decl *p = maybe_ਵਰਤਿਆ_decls;
  ਪੂਰਨ cur_level = ਵਿੱਚ_sizeof + ਵਿੱਚ_typeof + ਵਿੱਚ_countof + ਵਿੱਚ_generic;
  ਜਦੋਂ (p && p->level > cur_level)
    {
      ਜੇ (ਵਰਤਿਆ)
	{
	  ਜੇ (cur_level == 0)
	    mark_decl_ਵਰਤਿਆ (p->decl, p->ਪਤਾ);
	  ਨਹੀਂਤਾਂ
	    p->level = cur_level;
	}
      p = p->ਅਗਲਾ;
    }
  ਜੇ (!ਵਰਤਿਆ || cur_level == 0)
    maybe_ਵਰਤਿਆ_decls = p;
}

/* Pop the stack of decls possibly used inside sizeof or typeof or _Countof or
   _Generic, without acting on them, and return the pointer to the previous top
   of the stack.  This for use at the end of a default generic association when
   it is not yet known whether the expression is used.  If it later turns out
   the expression is used (or treated as used before C23), restore_maybe_used
   should be called on the return value followed by pop_maybe_used (true);
   otherwise, the return value can be discarded.  */

ਬਣਤਰ maybe_ਵਰਤਿਆ_decl *
save_maybe_ਵਰਤਿਆ ()
{
  ਬਣਤਰ maybe_ਵਰਤਿਆ_decl *p = maybe_ਵਰਤਿਆ_decls, *orig = p;
  ਪੂਰਨ cur_level = ਵਿੱਚ_sizeof + ਵਿੱਚ_typeof + ਵਿੱਚ_countof + ਵਿੱਚ_generic;
  ਜਦੋਂ (p && p->level > cur_level)
    p = p->ਅਗਲਾ;
  maybe_ਵਰਤਿਆ_decls = p;
  ਵਾਪਸ orig;
}

/* Restore the stack of decls possibly used inside sizeof or typeof or _Countof
   or _Generic returned by save_maybe_used.  It is required that the stack is
   at exactly the point where it was left by save_maybe_used.  */

ਖਾਲੀ
restore_maybe_ਵਰਤਿਆ (ਬਣਤਰ maybe_ਵਰਤਿਆ_decl *ਢੇਰ)
{
  maybe_ਵਰਤਿਆ_decls = ਢੇਰ;
}

/* Return the result of sizeof applied to EXPR.  */

ਬਣਤਰ c_ਵਿਅੰਜਕ
c_ਵਿਅੰਜਕ_sizeof_ਵਿਅੰਜਕ (location_t loc, ਬਣਤਰ c_ਵਿਅੰਜਕ ਵਿਅੰਜਕ)
{
  ਬਣਤਰ c_ਵਿਅੰਜਕ ret;
  ਜੇ (ਵਿਅੰਜਕ.ਮੁੱਲ == error_mark_ਗੰਢ)
    {
      ret.ਮੁੱਲ = error_mark_ਗੰਢ;
      ret.original_ਕੋਡ = ERROR_MARK;
      ret.original_type = ਨਿਰਾ;
      ret.m_decimal = 0;
      ਕੱਢੋ_maybe_ਵਰਤਿਆ (ਝੂਠ);
    }
  ਨਹੀਂਤਾਂ
    {
      ਤਾਰਕਿਕ ਵਿਅੰਜਕ_const_operands = ਸੱਚ;

      ਜੇ (ਰੁੱਖ_ਕੋਡ (ਵਿਅੰਜਕ.ਮੁੱਲ) == PARM_DECL
	  && C_ARRAY_PARAMETER (ਵਿਅੰਜਕ.ਮੁੱਲ))
	{
	  auto_diagnostic_ਸਮੂਹ d;
	  ਜੇ (warning_at (loc, OPT_Wsizeof_array_ਦਲੀਲ,
			  "%<sizeof%> on array function parameter %qE will "
			  "return size of %qT", ਵਿਅੰਜਕ.ਮੁੱਲ,
			  ਰੁੱਖ_TYPE (ਵਿਅੰਜਕ.ਮੁੱਲ)))
	    inform (DECL_ਸਰੋਤ_LOCATION (ਵਿਅੰਜਕ.ਮੁੱਲ), "declared here");
	}
      ਰੁੱਖ folded_ਵਿਅੰਜਕ = c_fully_fold (ਵਿਅੰਜਕ.ਮੁੱਲ, require_constant_ਮੁੱਲ,
				       &ਵਿਅੰਜਕ_const_operands);
      ret.ਮੁੱਲ = c_sizeof (loc, ਰੁੱਖ_TYPE (folded_ਵਿਅੰਜਕ));
      c_ਆਖਰੀ_sizeof_arg = ਵਿਅੰਜਕ.ਮੁੱਲ;
      c_ਆਖਰੀ_sizeof_loc = loc;
      ret.original_ਕੋਡ = SIZEOF_ਵਿਅੰਜਕ;
      ret.original_type = ਨਿਰਾ;
      ret.m_decimal = 0;
      ਜੇ (C_TYPE_VARIABLE_ਮਾਪ (ਰੁੱਖ_TYPE (folded_ਵਿਅੰਜਕ)))
	{
	  /* sizeof is evaluated when given a vla (C99 6.5.3.4p2).  */
	  ret.ਮੁੱਲ = build2 (C_MAYBE_CONST_ਵਿਅੰਜਕ, ਰੁੱਖ_TYPE (ret.ਮੁੱਲ),
			      folded_ਵਿਅੰਜਕ, ret.ਮੁੱਲ);
	  C_MAYBE_CONST_ਵਿਅੰਜਕ_NON_CONST (ret.ਮੁੱਲ) = !ਵਿਅੰਜਕ_const_operands;
	  ਸੈੱਟ_ਵਿਅੰਜਕ_LOCATION (ret.ਮੁੱਲ, loc);
	}
      ਕੱਢੋ_maybe_ਵਰਤਿਆ (C_TYPE_VARIABLE_ਮਾਪ (ਰੁੱਖ_TYPE (folded_ਵਿਅੰਜਕ)));
    }
  ਵਾਪਸ ret;
}

/* Return the result of sizeof applied to T, a structure for the type
   name passed to sizeof (rather than the type itself).  LOC is the
   location of the original expression.  */

ਬਣਤਰ c_ਵਿਅੰਜਕ
c_ਵਿਅੰਜਕ_sizeof_type (location_t loc, ਬਣਤਰ c_type_name *t)
{
  ਰੁੱਖ type;
  ਬਣਤਰ c_ਵਿਅੰਜਕ ret;
  ਰੁੱਖ type_ਵਿਅੰਜਕ = NULL_ਰੁੱਖ;
  ਤਾਰਕਿਕ type_ਵਿਅੰਜਕ_const = ਸੱਚ;
  type = groktypename (t, &type_ਵਿਅੰਜਕ, &type_ਵਿਅੰਜਕ_const);
  ret.ਮੁੱਲ = c_sizeof (loc, type);
  c_ਆਖਰੀ_sizeof_arg = type;
  c_ਆਖਰੀ_sizeof_loc = loc;
  ret.original_ਕੋਡ = SIZEOF_ਵਿਅੰਜਕ;
  ret.original_type = ਨਿਰਾ;
  ret.m_decimal = 0;
  ਜੇ (type == error_mark_ਗੰਢ)
    {
      ret.ਮੁੱਲ = error_mark_ਗੰਢ;
      ret.original_ਕੋਡ = ERROR_MARK;
    }
  ਨਹੀਂਤਾਂ
  ਜੇ ((type_ਵਿਅੰਜਕ || ਰੁੱਖ_ਕੋਡ (ret.ਮੁੱਲ) == INTEGER_CST)
      && C_TYPE_VARIABLE_ਮਾਪ (type))
    {
      /* If the type is a [*] array, it is a VLA but is represented as
	 having a size of zero.  In such a case we must ensure that
	 the result of sizeof does not get folded to a constant by
	 c_fully_fold, because if the size is evaluated the result is
	 not constant and so constraints on zero or negative size
	 arrays must not be applied when this sizeof call is inside
	 another array declarator.  */
      ਜੇ (!type_ਵਿਅੰਜਕ)
	type_ਵਿਅੰਜਕ = integer_zero_ਗੰਢ;
      ret.ਮੁੱਲ = build2 (C_MAYBE_CONST_ਵਿਅੰਜਕ, ਰੁੱਖ_TYPE (ret.ਮੁੱਲ),
			  type_ਵਿਅੰਜਕ, ret.ਮੁੱਲ);
      C_MAYBE_CONST_ਵਿਅੰਜਕ_NON_CONST (ret.ਮੁੱਲ) = !type_ਵਿਅੰਜਕ_const;
    }
  ਕੱਢੋ_maybe_ਵਰਤਿਆ (type != error_mark_ਗੰਢ
		  ? C_TYPE_VARIABLE_ਮਾਪ (type) : ਝੂਠ);
  ਵਾਪਸ ret;
}

ਸਥਿਰ ਤਾਰਕਿਕ
ਸਿਖਰ_array_vla_p (const_ਰੁੱਖ type)
{
  ਜੇ (ਰੁੱਖ_ਕੋਡ (type) != ARRAY_TYPE)
    ਵਾਪਸ ਝੂਠ;

  ਰੁੱਖ d = TYPE_DOMAIN (type);

  ਜੇ (!d)
    ਵਾਪਸ ਝੂਠ;
  ਜੇ (!TYPE_MAX_ਮੁੱਲ (d))
    ਵਾਪਸ ਝੂਠ;

  ਵਾਪਸ ਰੁੱਖ_ਕੋਡ (TYPE_MAX_ਮੁੱਲ (d)) != INTEGER_CST
	 || ਰੁੱਖ_ਕੋਡ (TYPE_MIN_ਮੁੱਲ (d)) != INTEGER_CST;
}

/* Return the result of countof applied to EXPR.  */

ਬਣਤਰ c_ਵਿਅੰਜਕ
c_ਵਿਅੰਜਕ_countof_ਵਿਅੰਜਕ (location_t loc, ਬਣਤਰ c_ਵਿਅੰਜਕ ਵਿਅੰਜਕ)
{
  ਬਣਤਰ c_ਵਿਅੰਜਕ ret;
  ਜੇ (ਵਿਅੰਜਕ.ਮੁੱਲ == error_mark_ਗੰਢ)
    {
      ret.ਮੁੱਲ = error_mark_ਗੰਢ;
      ret.original_ਕੋਡ = ERROR_MARK;
      ret.original_type = ਨਿਰਾ;
      ret.m_decimal = 0;
      ਕੱਢੋ_maybe_ਵਰਤਿਆ (ਝੂਠ);
    }
  ਨਹੀਂਤਾਂ
    {
      ਤਾਰਕਿਕ ਵਿਅੰਜਕ_const_operands = ਸੱਚ;

      ਰੁੱਖ folded_ਵਿਅੰਜਕ = c_fully_fold (ਵਿਅੰਜਕ.ਮੁੱਲ, require_constant_ਮੁੱਲ,
				       &ਵਿਅੰਜਕ_const_operands);
      ret.ਮੁੱਲ = c_countof_type (loc, ਰੁੱਖ_TYPE (folded_ਵਿਅੰਜਕ));
      c_ਆਖਰੀ_sizeof_arg = ਵਿਅੰਜਕ.ਮੁੱਲ;
      c_ਆਖਰੀ_sizeof_loc = loc;
      ret.original_ਕੋਡ = COUNTOF_ਵਿਅੰਜਕ;
      ret.original_type = ਨਿਰਾ;
      ret.m_decimal = 0;
      ਜੇ (ਸਿਖਰ_array_vla_p (ਰੁੱਖ_TYPE (folded_ਵਿਅੰਜਕ)))
	{
	  /* countof is evaluated when given a vla.  */
	  ret.ਮੁੱਲ = build2 (C_MAYBE_CONST_ਵਿਅੰਜਕ, ਰੁੱਖ_TYPE (ret.ਮੁੱਲ),
			      folded_ਵਿਅੰਜਕ, ret.ਮੁੱਲ);
	  C_MAYBE_CONST_ਵਿਅੰਜਕ_NON_CONST (ret.ਮੁੱਲ) = !ਵਿਅੰਜਕ_const_operands;
	  ਸੈੱਟ_ਵਿਅੰਜਕ_LOCATION (ret.ਮੁੱਲ, loc);
	}
      ਕੱਢੋ_maybe_ਵਰਤਿਆ (ਸਿਖਰ_array_vla_p (ਰੁੱਖ_TYPE (folded_ਵਿਅੰਜਕ)));
    }
  ਵਾਪਸ ret;
}

/* Return the result of countof applied to T, a structure for the type
   name passed to countof (rather than the type itself).  LOC is the
   location of the original expression.  */

ਬਣਤਰ c_ਵਿਅੰਜਕ
c_ਵਿਅੰਜਕ_countof_type (location_t loc, ਬਣਤਰ c_type_name *t)
{
  ਰੁੱਖ type;
  ਬਣਤਰ c_ਵਿਅੰਜਕ ret;
  ਰੁੱਖ type_ਵਿਅੰਜਕ = NULL_ਰੁੱਖ;
  ਤਾਰਕਿਕ type_ਵਿਅੰਜਕ_const = ਸੱਚ;
  type = groktypename (t, &type_ਵਿਅੰਜਕ, &type_ਵਿਅੰਜਕ_const);
  ret.ਮੁੱਲ = c_countof_type (loc, type);
  c_ਆਖਰੀ_sizeof_arg = type;
  c_ਆਖਰੀ_sizeof_loc = loc;
  ret.original_ਕੋਡ = COUNTOF_ਵਿਅੰਜਕ;
  ret.original_type = ਨਿਰਾ;
  ret.m_decimal = 0;
  ਜੇ (type == error_mark_ਗੰਢ)
    {
      ret.ਮੁੱਲ = error_mark_ਗੰਢ;
      ret.original_ਕੋਡ = ERROR_MARK;
    }
  ਨਹੀਂਤਾਂ
  ਜੇ ((type_ਵਿਅੰਜਕ || ਰੁੱਖ_ਕੋਡ (ret.ਮੁੱਲ) == INTEGER_CST)
      && ਸਿਖਰ_array_vla_p (type))
    {
      /* If the type is a [*] array, it is a VLA but is represented as
	 having a size of zero.  In such a case we must ensure that
	 the result of countof does not get folded to a constant by
	 c_fully_fold, because if the number of elements is evaluated
	 the result is not constant and so
	 constraints on zero or negative size arrays must not be applied
	 when this countof call is inside another array declarator.  */
      ਜੇ (!type_ਵਿਅੰਜਕ)
	type_ਵਿਅੰਜਕ = integer_zero_ਗੰਢ;
      ret.ਮੁੱਲ = build2 (C_MAYBE_CONST_ਵਿਅੰਜਕ, ਰੁੱਖ_TYPE (ret.ਮੁੱਲ),
			  type_ਵਿਅੰਜਕ, ret.ਮੁੱਲ);
      C_MAYBE_CONST_ਵਿਅੰਜਕ_NON_CONST (ret.ਮੁੱਲ) = !type_ਵਿਅੰਜਕ_const;
    }
  ਕੱਢੋ_maybe_ਵਰਤਿਆ (type != error_mark_ਗੰਢ ? ਸਿਖਰ_array_vla_p (type) : ਝੂਠ);
  ਵਾਪਸ ret;
}

/* Return the result of maxof applied to T, a structure for the type
   name passed to maxof (rather than the type itself).  LOC is the
   location of the original expression.  */

ਬਣਤਰ c_ਵਿਅੰਜਕ
c_ਵਿਅੰਜਕ_maxof_type (location_t loc, ਬਣਤਰ c_type_name *t)
{
  ਰੁੱਖ type;
  ਬਣਤਰ c_ਵਿਅੰਜਕ ret;
  ਰੁੱਖ type_ਵਿਅੰਜਕ = NULL_ਰੁੱਖ;
  ਤਾਰਕਿਕ type_ਵਿਅੰਜਕ_const = ਸੱਚ;
  type = groktypename (t, &type_ਵਿਅੰਜਕ, &type_ਵਿਅੰਜਕ_const);
  ret.ਮੁੱਲ = c_maxof_type (loc, type);
  c_ਆਖਰੀ_sizeof_arg = type;
  c_ਆਖਰੀ_sizeof_loc = loc;
  ret.original_ਕੋਡ = MAXOF_ਵਿਅੰਜਕ;
  ret.original_type = ਨਿਰਾ;
  ret.m_decimal = 0;
  ਜੇ (type == error_mark_ਗੰਢ)
    {
      ret.ਮੁੱਲ = error_mark_ਗੰਢ;
      ret.original_ਕੋਡ = ERROR_MARK;
    }
  ਕੱਢੋ_maybe_ਵਰਤਿਆ (type != error_mark_ਗੰਢ);
  ਵਾਪਸ ret;
}

/* Return the result of minof applied to T, a structure for the type
   name passed to minof (rather than the type itself).  LOC is the
   location of the original expression.  */

ਬਣਤਰ c_ਵਿਅੰਜਕ
c_ਵਿਅੰਜਕ_minof_type (location_t loc, ਬਣਤਰ c_type_name *t)
{
  ਰੁੱਖ type;
  ਬਣਤਰ c_ਵਿਅੰਜਕ ret;
  ਰੁੱਖ type_ਵਿਅੰਜਕ = NULL_ਰੁੱਖ;
  ਤਾਰਕਿਕ type_ਵਿਅੰਜਕ_const = ਸੱਚ;
  type = groktypename (t, &type_ਵਿਅੰਜਕ, &type_ਵਿਅੰਜਕ_const);
  ret.ਮੁੱਲ = c_minof_type (loc, type);
  c_ਆਖਰੀ_sizeof_arg = type;
  c_ਆਖਰੀ_sizeof_loc = loc;
  ret.original_ਕੋਡ = MINOF_ਵਿਅੰਜਕ;
  ret.original_type = ਨਿਰਾ;
  ret.m_decimal = 0;
  ਜੇ (type == error_mark_ਗੰਢ)
    {
      ret.ਮੁੱਲ = error_mark_ਗੰਢ;
      ret.original_ਕੋਡ = ERROR_MARK;
    }
  ਕੱਢੋ_maybe_ਵਰਤਿਆ (type != error_mark_ਗੰਢ);
  ਵਾਪਸ ret;
}

/* Build a function call to function FUNCTION with parameters PARAMS.
   The function call is at LOC.
   PARAMS is a list--a chain of TREE_LIST nodes--in which the
   TREE_VALUE of each node is a parameter-expression.
   FUNCTION's data type may be a function type or a pointer-to-function.  */

ਰੁੱਖ
build_function_call (location_t loc, ਰੁੱਖ function, ਰੁੱਖ params)
{
  vec<ਰੁੱਖ, va_gc> *v;
  ਰੁੱਖ ret;

  vec_alloc (v, list_ਲੰਮਾਈ (params));
  ਲਈ (; params; params = ਰੁੱਖ_CHAIN (params))
    v->ਤੇਜ਼_ਧੱਕੋ (ਰੁੱਖ_ਮੁੱਲ (params));
  ret = c_build_function_call_vec (loc, vNULL, function, v, ਨਿਰਾ);
  vec_free (v);
  ਵਾਪਸ ret;
}

/* Give a note about the location of the declaration of DECL,
   or, failing that, a pertinent declaration for FUNCTION_EXPR.  */

ਸਥਿਰ ਖਾਲੀ
inform_declaration (ਰੁੱਖ decl, ਰੁੱਖ function_ਵਿਅੰਜਕ)
{
  ਜੇ (decl && (ਰੁੱਖ_ਕੋਡ (decl) != FUNCTION_DECL
	       || !DECL_IS_UNDECLARED_BUILTIN (decl)))
    inform (DECL_ਸਰੋਤ_LOCATION (decl), "declared here");
  ਨਹੀਂਤਾਂ ਜੇ (function_ਵਿਅੰਜਕ)
    ਚੋਣ (ਰੁੱਖ_ਕੋਡ (function_ਵਿਅੰਜਕ))
      {
      ਮੂਲ:
	ਰੋਕੋ;
      ਹਾਲਤ COMPONENT_REF:
	/* Show the decl of the pertinent field (e.g. for callback
	   fields in a struct.  */
	{
	  ਰੁੱਖ ਖੇਤਰ_decl = ਰੁੱਖ_ਸੰਕਾਰਜ (function_ਵਿਅੰਜਕ, 1);
	  ਜੇ (location_t loc = DECL_ਸਰੋਤ_LOCATION (ਖੇਤਰ_decl))
	    inform (loc, "declared here");
	}
	ਰੋਕੋ;
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

ਰੁੱਖ
build_function_call_vec (location_t loc, vec<location_t> arg_loc,
			 ਰੁੱਖ function, vec<ਰੁੱਖ, va_gc> *params,
			 vec<ਰੁੱਖ, va_gc> *origtypes, ਰੁੱਖ orig_fundecl)
{
  ਰੁੱਖ fntype, fundecl = NULL_ਰੁੱਖ;
  ਰੁੱਖ name = NULL_ਰੁੱਖ, ਨਤੀਜਾ;
  ਰੁੱਖ tem;
  ਪੂਰਨ nargs;
  ਰੁੱਖ *argarray;


  /* Strip NON_LVALUE_EXPRs, etc., since we aren't using as an lvalue.  */
  STRIP_TYPE_NOPS (function);

  /* Convert anything with function type to a pointer-to-function.  */
  ਜੇ (ਰੁੱਖ_ਕੋਡ (function) == FUNCTION_DECL)
    {
      name = DECL_NAME (function);

      ਜੇ (flag_tm)
	tm_malloc_replacement (function);
      fundecl = function;
      ਜੇ (!orig_fundecl)
	orig_fundecl = fundecl;
      /* Atomic functions have type checking/casting already done.  They are
	 often rewritten and don't match the original parameter list.  */
      ਜੇ (name && startswith (IDENTIFIER_ਸੂਚਕ (name), "__atomic_"))
        origtypes = ਨਿਰਾ;
    }
  ਜੇ (ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (function)) == FUNCTION_TYPE)
    function = function_ਮੰਜ਼ਿਲ_ਸੂਚਕ_conversion (loc, function);

  /* For Objective-C, convert any calls via a cast to OBJC_TYPE_REF
     expressions, like those used for ObjC messenger dispatches.  */
  ਜੇ (params && !params->is_ਖਾਲੀ_ਥਾਵਾਂ ())
    function = objc_rewrite_function_call (function, (*params)[0]);

  function = c_fully_fold (function, ਝੂਠ, ਨਿਰਾ);

  fntype = ਰੁੱਖ_TYPE (function);

  ਜੇ (ਰੁੱਖ_ਕੋਡ (fntype) == ERROR_MARK)
    ਵਾਪਸ error_mark_ਗੰਢ;

  ਜੇ (!(ਰੁੱਖ_ਕੋਡ (fntype) == ਸੂਚਕ_TYPE
	&& ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (fntype)) == FUNCTION_TYPE))
    {
      ਜੇ (!flag_diagnostics_show_caret && !STATEMENT_CLASS_P (function))
	error_at (loc,
		  "called object %qE is not a function or function pointer",
		  function);
      ਨਹੀਂਤਾਂ ਜੇ (DECL_P (function))
	{
	  auto_diagnostic_ਸਮੂਹ d;
	  error_at (loc,
		    "called object %qD is not a function or function pointer",
		    function);
	  inform_declaration (function, NULL_ਰੁੱਖ);
	}
      ਨਹੀਂਤਾਂ
	error_at (loc,
		  "called object is not a function or function pointer");
      ਵਾਪਸ error_mark_ਗੰਢ;
    }

  ਜੇ (fundecl && ਰੁੱਖ_THIS_VOLATILE (fundecl))
    current_function_returns_abnormally = 1;

  /* fntype now gets the type of function pointed to.  */
  fntype = ਰੁੱਖ_TYPE (fntype);
  ਰੁੱਖ return_type = ਰੁੱਖ_TYPE (fntype);

  /* Convert the parameters to the types declared in the
     function prototype, or apply default promotions.  */

  nargs = convert_arguments (loc, arg_loc, fntype, params,
			     origtypes, function, fundecl);
  ਜੇ (nargs < 0)
    ਵਾਪਸ error_mark_ਗੰਢ;

  /* Check that the function is called through a compatible prototype.
     If it is not, warn.  */
  ਜੇ (CONVERT_ਵਿਅੰਜਕ_P (function)
      && ਰੁੱਖ_ਕੋਡ (tem = ਰੁੱਖ_ਸੰਕਾਰਜ (function, 0)) == ADDR_ਵਿਅੰਜਕ
      && ਰੁੱਖ_ਕੋਡ (tem = ਰੁੱਖ_ਸੰਕਾਰਜ (tem, 0)) == FUNCTION_DECL
      && !comptypes (fntype, ਰੁੱਖ_TYPE (tem)))
    {
      /* This situation leads to run-time undefined behavior.  We can't,
	 therefore, simply error unless we can prove that all possible
	 executions of the program must execute the code.  */
      warning_at (loc, 0, "function called through a non-compatible type");

      ਜੇ (VOID_TYPE_P (return_type)
	  && TYPE_QUALS (return_type) != TYPE_UNQUALIFIED)
	pedwarn (loc, 0,
		 "function with qualified void return type called");
     }

  argarray = vec_ਸੁਰੱਖਿਅਤ_ਪਤਾ (params);

  /* Check that arguments to builtin functions match the expectations.  */
  ਜੇ (fundecl
      && fndecl_built_ਵਿੱਚ_p (fundecl)
      && !check_builtin_function_arguments (loc, arg_loc, fundecl,
					    orig_fundecl, nargs, argarray))
    ਵਾਪਸ error_mark_ਗੰਢ;

  /* Check that the arguments to the function are valid.  */
  ਤਾਰਕਿਕ warned_p = check_function_arguments (loc, fundecl, fntype,
					    nargs, argarray, &arg_loc,
					    comptypes);

  ਜੇ (TYPE_QUALS (return_type) != TYPE_UNQUALIFIED
      && !VOID_TYPE_P (return_type))
    return_type = c_build_qualified_type (return_type, TYPE_UNQUALIFIED);
  ਜੇ (name != NULL_ਰੁੱਖ
      && startswith (IDENTIFIER_ਸੂਚਕ (name), "__builtin_"))
    {
      ਜੇ (require_constant_ਮੁੱਲ)
	ਨਤੀਜਾ
	  = fold_build_call_array_initializer_loc (loc, return_type,
						   function, nargs, argarray);
      ਨਹੀਂਤਾਂ
	ਨਤੀਜਾ = fold_build_call_array_loc (loc, return_type,
					    function, nargs, argarray);
      ਜੇ (ਰੁੱਖ_ਕੋਡ (ਨਤੀਜਾ) == NOP_ਵਿਅੰਜਕ
	  && ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_ਸੰਕਾਰਜ (ਨਤੀਜਾ, 0)) == INTEGER_CST)
	STRIP_TYPE_NOPS (ਨਤੀਜਾ);
    }
  ਨਹੀਂਤਾਂ
    ਨਤੀਜਾ = build_call_array_loc (loc, return_type,
				   function, nargs, argarray);
  /* If -Wnonnull warning has been diagnosed, avoid diagnosing it again
     later.  */
  ਜੇ (warned_p && ਰੁੱਖ_ਕੋਡ (ਨਤੀਜਾ) == CALL_ਵਿਅੰਜਕ)
    suppress_warning (ਨਤੀਜਾ, OPT_Wnonnull);

  /* In this improbable scenario, a nested function returns a VM type.
     Create a TARGET_EXPR so that the call always has a LHS, much as
     what the C++ FE does for functions returning non-PODs.  */
  ਜੇ (c_type_variably_modified_p (ਰੁੱਖ_TYPE (fntype)))
    {
      ਰੁੱਖ tmp = create_tmp_var_raw (ਰੁੱਖ_TYPE (fntype));
      ਨਤੀਜਾ = build4 (ਨਿਸ਼ਾਨਾ_ਵਿਅੰਜਕ, ਰੁੱਖ_TYPE (fntype), tmp, ਨਤੀਜਾ,
		       NULL_ਰੁੱਖ, NULL_ਰੁੱਖ);
    }

  ਜੇ (VOID_TYPE_P (ਰੁੱਖ_TYPE (ਨਤੀਜਾ)))
    {
      ਜੇ (TYPE_QUALS (ਰੁੱਖ_TYPE (ਨਤੀਜਾ)) != TYPE_UNQUALIFIED)
	pedwarn (loc, 0,
		 "function with qualified void return type called");
      ਵਾਪਸ ਨਤੀਜਾ;
    }
  ਵਾਪਸ require_complete_type (loc, ਨਤੀਜਾ);
}

/* Like build_function_call_vec, but call also resolve_overloaded_builtin.  */

ਰੁੱਖ
c_build_function_call_vec (location_t loc, ਅਚਲ vec<location_t> &arg_loc,
			   ਰੁੱਖ function, vec<ਰੁੱਖ, va_gc> *params,
			   vec<ਰੁੱਖ, va_gc> *origtypes)
{
  /* Strip NON_LVALUE_EXPRs, etc., since we aren't using as an lvalue.  */
  STRIP_TYPE_NOPS (function);

  /* Convert anything with function type to a pointer-to-function.  */
  ਜੇ (ਰੁੱਖ_ਕੋਡ (function) == FUNCTION_DECL)
    {
      /* Implement type-directed function overloading for builtins.
	 resolve_overloaded_builtin and targetm.resolve_overloaded_builtin
	 handle all the type checking.  The result is a complete expression
	 that implements this function call.  */
      ਰੁੱਖ tem = resolve_overloaded_builtin (loc, function, params);
      ਜੇ (tem)
	ਵਾਪਸ tem;
    }
  ਵਾਪਸ build_function_call_vec (loc, arg_loc, function, params, origtypes);
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

ਸਥਿਰ ਰੁੱਖ
convert_ਦਲੀਲ (location_t ploc, ਰੁੱਖ function, ਰੁੱਖ fundecl,
		  ਰੁੱਖ type, ਰੁੱਖ origtype, ਰੁੱਖ val, ਰੁੱਖ valtype,
		  ਤਾਰਕਿਕ npc, ਰੁੱਖ rname, ਪੂਰਨ parmnum, ਪੂਰਨ argnum,
		  ਤਾਰਕਿਕ excess_precision, ਪੂਰਨ warnopt)
{
  /* Formal parm type is specified by a function prototype.  */

  ਜੇ (type == error_mark_ਗੰਢ || !COMPLETE_TYPE_P (type))
    {
      error_at (ploc, "type of formal parameter %d is incomplete",
		parmnum + 1);
      ਵਾਪਸ error_mark_ਗੰਢ;
    }

  /* Optionally warn about conversions that differ from the default
     conversions.  */
  ਜੇ (warn_traditional_conversion || warn_traditional)
    {
      ਜੇ (INTEGRAL_TYPE_P (type)
	  && SCALAR_FLOAT_TYPE_P (valtype))
	warning_at (ploc, OPT_Wtraditional_conversion,
		    "passing argument %d of %qE as integer rather "
		    "than floating due to prototype",
		    argnum, rname);
      ਜੇ (INTEGRAL_TYPE_P (type)
	  && ਰੁੱਖ_ਕੋਡ (valtype) == COMPLEX_TYPE)
	warning_at (ploc, OPT_Wtraditional_conversion,
		    "passing argument %d of %qE as integer rather "
		    "than complex due to prototype",
		    argnum, rname);
      ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਕੋਡ (type) == COMPLEX_TYPE
	       && SCALAR_FLOAT_TYPE_P (valtype))
	warning_at (ploc, OPT_Wtraditional_conversion,
		    "passing argument %d of %qE as complex rather "
		    "than floating due to prototype",
		    argnum, rname);
      ਨਹੀਂਤਾਂ ਜੇ (SCALAR_FLOAT_TYPE_P (type)
	       && INTEGRAL_TYPE_P (valtype))
	warning_at (ploc, OPT_Wtraditional_conversion,
		    "passing argument %d of %qE as floating rather "
		    "than integer due to prototype",
		    argnum, rname);
      ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਕੋਡ (type) == COMPLEX_TYPE
	       && INTEGRAL_TYPE_P (valtype))
	warning_at (ploc, OPT_Wtraditional_conversion,
		    "passing argument %d of %qE as complex rather "
		    "than integer due to prototype",
		    argnum, rname);
      ਨਹੀਂਤਾਂ ਜੇ (SCALAR_FLOAT_TYPE_P (type)
	       && ਰੁੱਖ_ਕੋਡ (valtype) == COMPLEX_TYPE)
	warning_at (ploc, OPT_Wtraditional_conversion,
		    "passing argument %d of %qE as floating rather "
		    "than complex due to prototype",
		    argnum, rname);
      /* ??? At some point, messages should be written about
	 conversions between complex types, but that's too messy
	 to do now.  */
      ਨਹੀਂਤਾਂ ਜੇ (SCALAR_FLOAT_TYPE_P (type)
	       && SCALAR_FLOAT_TYPE_P (valtype))
	{
	  ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ formal_prec = TYPE_PRECISION (type);

	  /* Warn if any argument is passed as `float',
	     since without a prototype it would be `double'.  */
	  ਜੇ (formal_prec == TYPE_PRECISION (float_type_ਗੰਢ)
	      && type != dfloat32_type_ਗੰਢ)
	    warning_at (ploc, 0,
			"passing argument %d of %qE as %<float%> "
			"rather than %<double%> due to prototype",
			argnum, rname);

	  /* Warn if mismatch between argument and prototype
	     for decimal float types.  Warn of conversions with
	     binary float types and of precision narrowing due to
	     prototype.  */
	  ਨਹੀਂਤਾਂ ਜੇ (type != valtype
		   && (type == dfloat32_type_ਗੰਢ
		       || type == dfloat64_type_ਗੰਢ
		       || type == dfloat128_type_ਗੰਢ
		       || valtype == dfloat32_type_ਗੰਢ
		       || valtype == dfloat64_type_ਗੰਢ
		       || valtype == dfloat128_type_ਗੰਢ)
		   && (formal_prec
		       <= TYPE_PRECISION (valtype)
		       || (type == dfloat128_type_ਗੰਢ
			   && (valtype
			       != dfloat64_type_ਗੰਢ
			       && (valtype
				   != dfloat32_type_ਗੰਢ)))
		       || (type == dfloat64_type_ਗੰਢ
			   && (valtype
			       != dfloat32_type_ਗੰਢ))))
	    warning_at (ploc, 0,
			"passing argument %d of %qE as %qT "
			"rather than %qT due to prototype",
			argnum, rname, type, valtype);

	}
      /* Detect integer changing in width or signedness.
	 These warnings are only activated with
	 -Wtraditional-conversion, not with -Wtraditional.  */
      ਨਹੀਂਤਾਂ ਜੇ (warn_traditional_conversion
	       && INTEGRAL_TYPE_P (type)
	       && INTEGRAL_TYPE_P (valtype))
	{
	  ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ formal_prec = TYPE_PRECISION (type);
	  ਰੁੱਖ would_have_been = default_conversion (val);
	  ਰੁੱਖ type1 = ਰੁੱਖ_TYPE (would_have_been);

	  ਜੇ (val == error_mark_ਗੰਢ)
	    /* VAL could have been of incomplete type.  */;
	  ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਕੋਡ (type) == ENUMERAL_TYPE
		   && (TYPE_MAIN_VARIANT (type)
		       == TYPE_MAIN_VARIANT (valtype)))
	    /* No warning if function asks for enum
	       and the actual arg is that enum type.  */
	    ;
	  ਨਹੀਂਤਾਂ ਜੇ (formal_prec != TYPE_PRECISION (type1))
	    warning_at (ploc, OPT_Wtraditional_conversion,
			"passing argument %d of %qE "
			"with different width due to prototype",
			argnum, rname);
	  ਨਹੀਂਤਾਂ ਜੇ (TYPE_UNSIGNED (type) == TYPE_UNSIGNED (type1))
	    ;
	  /* Don't complain if the formal parameter type
	     is an enum, because we can't tell now whether
	     the value was an enum--even the same enum.  */
	  ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਕੋਡ (type) == ENUMERAL_TYPE)
	    ;
	  ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਕੋਡ (val) == INTEGER_CST
		   && int_ਸਮਾਉਂਦਾ_type_p (val, type))
	    /* Change in signedness doesn't matter
	       if a constant value is unaffected.  */
	    ;
	  /* If the value is extended from a narrower
	     unsigned type, it doesn't matter whether we
	     pass it as signed or unsigned; the value
	     certainly is the same either way.  */
	  ਨਹੀਂਤਾਂ ਜੇ (TYPE_PRECISION (valtype) < TYPE_PRECISION (type)
		   && TYPE_UNSIGNED (valtype))
	    ;
	  ਨਹੀਂਤਾਂ ਜੇ (TYPE_UNSIGNED (type))
	    warning_at (ploc, OPT_Wtraditional_conversion,
			"passing argument %d of %qE "
			"as unsigned due to prototype",
			argnum, rname);
	  ਨਹੀਂਤਾਂ
	    warning_at (ploc, OPT_Wtraditional_conversion,
			"passing argument %d of %qE "
			"as signed due to prototype",
			argnum, rname);
	}
    }

  /* Possibly restore an EXCESS_PRECISION_EXPR for the
     sake of better warnings from convert_and_check.  */
  ਜੇ (excess_precision)
    val = build1 (EXCESS_PRECISION_ਵਿਅੰਜਕ, valtype, val);

  ਰੁੱਖ parmval = convert_for_assignment (ploc, ploc, type,
					 val, origtype, ic_argpass,
					 npc, fundecl, function,
					 parmnum + 1, warnopt);
  ਵਾਪਸ parmval;
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

ਸਥਿਰ ਪੂਰਨ
convert_arguments (location_t loc, vec<location_t> arg_loc, ਰੁੱਖ fntype,
		   vec<ਰੁੱਖ, va_gc> *ਮੁੱਲਾਂ, vec<ਰੁੱਖ, va_gc> *origtypes,
		   ਰੁੱਖ function, ਰੁੱਖ fundecl)
{
  ਰੁੱਖ typelist = TYPE_ARG_TYPES (fntype);
  ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ parmnum;
  ਤਾਰਕਿਕ error_ਦਲੀਲਾਂ = ਝੂਠ;
  ਅਚਲ ਤਾਰਕਿਕ type_generic = fundecl
    && lookup_attribute ("type generic", TYPE_ਗੁਣ (ਰੁੱਖ_TYPE (fundecl)));
  ਤਾਰਕਿਕ type_generic_remove_excess_precision = ਝੂਠ;
  ਤਾਰਕਿਕ type_generic_ਉਛਾਲ_p = ਝੂਠ;
  ਤਾਰਕਿਕ type_generic_ਦੋਆਧਾਰੀ_ਅੰਕ_query = ਝੂਠ;
  ਰੁੱਖ selector;

  /* Change pointer to function to the function itself for
     diagnostics.  */
  ਜੇ (ਰੁੱਖ_ਕੋਡ (function) == ADDR_ਵਿਅੰਜਕ
      && ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_ਸੰਕਾਰਜ (function, 0)) == FUNCTION_DECL)
    function = ਰੁੱਖ_ਸੰਕਾਰਜ (function, 0);

  /* Handle an ObjC selector specially for diagnostics.  */
  selector = objc_ਸੁਨੇਹਾ_selector ();

  /* For a call to a built-in function declared without a prototype,
     set to the built-in function's argument list.  */
  ਰੁੱਖ builtin_typelist = NULL_ਰੁੱਖ;

  /* For type-generic built-in functions, determine whether excess
     precision should be removed (classification) or not
     (comparison).  */
  ਜੇ (fundecl
      && fndecl_built_ਵਿੱਚ_p (fundecl, BUILT_ਵਿੱਚ_ਸਾਧਾਰਨ))
    {
      built_ਵਿੱਚ_function ਕੋਡ = DECL_FUNCTION_ਕੋਡ (fundecl);
      ਜੇ (C_DECL_BUILTIN_PROTOTYPE (fundecl))
	{
	  /* For a call to a built-in function declared without a prototype
	     use the types of the parameters of the internal built-in to
	     match those of the arguments to.  */
	  ਜੇ (ਰੁੱਖ bdecl = builtin_decl_explicit (ਕੋਡ))
	    builtin_typelist = TYPE_ARG_TYPES (ਰੁੱਖ_TYPE (bdecl));
	}

      /* For type-generic built-in functions, determine whether excess
	 precision should be removed (classification) or not
	 (comparison).  */
      ਜੇ (type_generic)
	ਚੋਣ (ਕੋਡ)
	  {
	  ਹਾਲਤ BUILT_ਵਿੱਚ_ISFINITE:
	  ਹਾਲਤ BUILT_ਵਿੱਚ_ISINF:
	  ਹਾਲਤ BUILT_ਵਿੱਚ_ISINF_SIGN:
	  ਹਾਲਤ BUILT_ਵਿੱਚ_ISNAN:
	  ਹਾਲਤ BUILT_ਵਿੱਚ_ISNORMAL:
	  ਹਾਲਤ BUILT_ਵਿੱਚ_ISSIGNALING:
	  ਹਾਲਤ BUILT_ਵਿੱਚ_FPCLASSIFY:
	    type_generic_remove_excess_precision = ਸੱਚ;
	    ਰੋਕੋ;

	  ਹਾਲਤ BUILT_ਵਿੱਚ_ਜੋੜੋ_ਉਛਾਲ_P:
	  ਹਾਲਤ BUILT_ਵਿੱਚ_SUB_ਉਛਾਲ_P:
	  ਹਾਲਤ BUILT_ਵਿੱਚ_MUL_ਉਛਾਲ_P:
	    /* The last argument of these type-generic builtins
	       should not be promoted.  */
	    type_generic_ਉਛਾਲ_p = ਸੱਚ;
	    ਰੋਕੋ;

	  ਹਾਲਤ BUILT_ਵਿੱਚ_CLZG:
	  ਹਾਲਤ BUILT_ਵਿੱਚ_CTZG:
	  ਹਾਲਤ BUILT_ਵਿੱਚ_CLRSBG:
	  ਹਾਲਤ BUILT_ਵਿੱਚ_FFSG:
	  ਹਾਲਤ BUILT_ਵਿੱਚ_PARITYG:
	  ਹਾਲਤ BUILT_ਵਿੱਚ_POPCOUNTG:
	    /* The first argument of these type-generic builtins
	       should not be promoted.  */
	    type_generic_ਦੋਆਧਾਰੀ_ਅੰਕ_query = ਸੱਚ;
	    ਰੋਕੋ;

	  ਮੂਲ:
	    ਰੋਕੋ;
	  }
    }

  /* Scan the given expressions (VALUES) and types (TYPELIST), producing
     individual converted arguments.  */

  ਰੁੱਖ typetail, builtin_typetail, val;
  ਲਈ (typetail = typelist,
	 builtin_typetail = builtin_typelist,
	 parmnum = 0;
       ਮੁੱਲਾਂ && ਮੁੱਲਾਂ->iterate (parmnum, &val);
       ++parmnum)
    {
      /* The type of the function parameter (if it was declared with one).  */
      ਰੁੱਖ type = typetail ? ਰੁੱਖ_ਮੁੱਲ (typetail) : NULL_ਰੁੱਖ;
      /* The type of the built-in function parameter (if the function
	 is a built-in).  Used to detect type incompatibilities in
	 calls to built-ins declared without a prototype.  */
      ਰੁੱਖ builtin_type = (builtin_typetail
			   ? ਰੁੱਖ_ਮੁੱਲ (builtin_typetail) : NULL_ਰੁੱਖ);
      /* The original type of the argument being passed to the function.  */
      ਰੁੱਖ valtype = ਰੁੱਖ_TYPE (val);
      /* The called function (or function selector in Objective C).  */
      ਰੁੱਖ rname = function;
      ਪੂਰਨ argnum = parmnum + 1;
      ਅਚਲ ਅੱਖਰ *invalid_func_diag;
      /* Set for EXCESS_PRECISION_EXPR arguments.  */
      ਤਾਰਕਿਕ excess_precision = ਝੂਠ;
      /* The value of the argument after conversion to the type
	 of the function parameter it is passed to.  */
      ਰੁੱਖ parmval;
      /* Some __atomic_* builtins have additional hidden argument at
	 position 0.  */
      location_t ploc
	= !arg_loc.is_ਖਾਲੀ_ਥਾਵਾਂ () && ਮੁੱਲਾਂ->ਲੰਮਾਈ () == arg_loc.ਲੰਮਾਈ ()
	  ? expansion_ਬਿੰਦੂ_location_if_ਵਿੱਚ_system_ਸਿਰਲੇਖ (arg_loc[parmnum])
	  : ਨਿਵੇਸ਼_location;

      ਜੇ (type == void_type_ਗੰਢ)
	{
	  auto_diagnostic_ਸਮੂਹ d;
	  ਪੂਰਨ ਅੰਕ_expected = parmnum;
	  ਪੂਰਨ ਅੰਕ_actual = ਮੁੱਲਾਂ->ਲੰਮਾਈ ();
	  gcc_rich_location rich_loc (loc);
	  ਜੇ (ploc != ਨਿਵੇਸ਼_location)
	    rich_loc.ਜੋੜੋ_range (ploc);
	  ਜੇ (selector)
	    error_at (&rich_loc,
		      "too many arguments to method %qE; expected %i, have %i",
		      selector, ਅੰਕ_expected, ਅੰਕ_actual);
	  ਨਹੀਂਤਾਂ
	    error_at (&rich_loc,
		      "too many arguments to function %qE; expected %i, have %i",
		      function, ਅੰਕ_expected, ਅੰਕ_actual);
	  inform_declaration (fundecl, function);
	  ਵਾਪਸ error_ਦਲੀਲਾਂ ? -1 : (ਪੂਰਨ) parmnum;
	}

      ਜੇ (builtin_type == void_type_ਗੰਢ)
	{
	  auto_diagnostic_ਸਮੂਹ d;
	  ਜੇ (warning_at (loc, OPT_Wbuiltin_declaration_mismatch,
			  "too many arguments to built-in function %qE "
			  "expecting %d", function, parmnum))
	    inform_declaration (fundecl, function);
	  builtin_typetail = NULL_ਰੁੱਖ;
	}

      ਜੇ (!typetail && parmnum == 0 && !TYPE_NO_NAMED_ਦਲੀਲਾਂ_STDARG_P (fntype)
	  && !(fundecl && fndecl_built_ਵਿੱਚ_p (fundecl)))
	{
	  auto_diagnostic_ਸਮੂਹ d;
	  ਤਾਰਕਿਕ warned;
	  ਜੇ (selector)
	    warned = warning_at (loc, OPT_Wdeprecated_non_prototype,
				 "ISO C23 does not allow arguments"
				 " for method %qE declared without parameters",
				 function);
	  ਨਹੀਂਤਾਂ
	    warned = warning_at (loc, OPT_Wdeprecated_non_prototype,
				 "ISO C23 does not allow arguments"
				 " for function %qE declared without parameters",
				 function);
	  ਜੇ (warned)
	    inform_declaration (fundecl, function);
	}

      ਜੇ (selector && argnum > 2)
	{
	  rname = selector;
	  argnum -= 2;
	}

      /* Determine if VAL is a null pointer constant before folding it.  */
      ਤਾਰਕਿਕ npc = null_ਸੂਚਕ_constant_p (val);

      /* If there is excess precision and a prototype, convert once to
	 the required type rather than converting via the semantic
	 type.  Likewise without a prototype a float value represented
	 as long double should be converted once to double.  But for
	 type-generic classification functions excess precision must
	 be removed here.  */
      ਜੇ (ਰੁੱਖ_ਕੋਡ (val) == EXCESS_PRECISION_ਵਿਅੰਜਕ
	  && (type || !type_generic || !type_generic_remove_excess_precision))
	{
	  val = ਰੁੱਖ_ਸੰਕਾਰਜ (val, 0);
	  excess_precision = ਸੱਚ;
	}
      val = c_fully_fold (val, ਝੂਠ, ਨਿਰਾ);
      STRIP_TYPE_NOPS (val);

      val = require_complete_type (ploc, val);

      /* Some floating-point arguments must be promoted to double when
	 no type is specified by a prototype.  This applies to
	 arguments of type float, and to architecture-specific types
	 (ARM __fp16), but not to _FloatN or _FloatNx types.  */
      ਤਾਰਕਿਕ promote_float_arg = ਝੂਠ;
      ਜੇ (type == NULL_ਰੁੱਖ
	  && ਰੁੱਖ_ਕੋਡ (valtype) == REAL_TYPE
	  && (TYPE_PRECISION (valtype)
	      <= TYPE_PRECISION (double_type_ਗੰਢ))
	  && TYPE_MAIN_VARIANT (valtype) != double_type_ਗੰਢ
	  && TYPE_MAIN_VARIANT (valtype) != long_double_type_ਗੰਢ
	  && !DECIMAL_FLOAT_ਬਹੁਲਕ_P (TYPE_ਬਹੁਲਕ (valtype)))
	{
	  /* Promote this argument, unless it has a _FloatN or
	     _FloatNx type.  */
	  promote_float_arg = ਸੱਚ;
	  ਲਈ (ਪੂਰਨ i = 0; i < ਅੰਕ_FLOATN_NX_TYPES; i++)
	    ਜੇ (TYPE_MAIN_VARIANT (valtype) == FLOATN_NX_TYPE_ਗੰਢ (i))
	      {
		promote_float_arg = ਝੂਠ;
		ਰੋਕੋ;
	      }
	  /* Don't promote __bf16 either.  */
	  ਜੇ (TYPE_MAIN_VARIANT (valtype) == bfloat16_type_ਗੰਢ)
	    promote_float_arg = ਝੂਠ;
	}

      ਜੇ (type != NULL_ਰੁੱਖ)
	{
	  ਰੁੱਖ origtype = (!origtypes) ? NULL_ਰੁੱਖ : (*origtypes)[parmnum];
	  parmval = convert_ਦਲੀਲ (ploc, function, fundecl, type, origtype,
				      val, valtype, npc, rname, parmnum, argnum,
				      excess_precision, 0);
	}
      /* A NULLPTR type is just a nullptr always.  */
      ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (val)) == NULLPTR_TYPE)
	parmval = omit_one_ਸੰਕਾਰਜ_loc (ploc, ਰੁੱਖ_TYPE (val), nullptr_ਗੰਢ, val);
      ਨਹੀਂਤਾਂ ਜੇ (promote_float_arg)
        {
	  ਜੇ (type_generic)
	    parmval = val;
	  ਨਹੀਂਤਾਂ
	    {
	      /* Convert `float' to `double'.  */
	      ਜੇ (warn_double_promotion && !c_inhibit_evaluation_warnings)
		warning_at (ploc, OPT_Wdouble_promotion,
			    "implicit conversion from %qT to %qT when passing "
			    "argument to function",
			    valtype, double_type_ਗੰਢ);
	      parmval = convert (double_type_ਗੰਢ, val);
	    }
	}
      ਨਹੀਂਤਾਂ ਜੇ ((excess_precision && !type_generic)
	       || (type_generic_ਉਛਾਲ_p && parmnum == 2)
	       || (type_generic_ਦੋਆਧਾਰੀ_ਅੰਕ_query && parmnum == 0))
	/* A "double" argument with excess precision being passed
	   without a prototype or in variable arguments.
	   The last argument of __builtin_*_overflow_p should not be
	   promoted, similarly the first argument of
	   __builtin_{clz,ctz,clrsb,ffs,parity,popcount}g.  */
	parmval = convert (valtype, val);
      ਨਹੀਂਤਾਂ ਜੇ ((invalid_func_diag =
		targetm.calls.invalid_arg_for_unprototyped_fn (typelist, fundecl, val)))
	{
	  error (invalid_func_diag);
	  ਵਾਪਸ -1;
	}
      ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਕੋਡ (val) == ADDR_ਵਿਅੰਜਕ && reject_gcc_builtin (val))
	{
	  ਵਾਪਸ -1;
	}
      ਨਹੀਂਤਾਂ
	/* Convert `short' and `char' to full-size `int'.  */
	parmval = default_conversion (val);

      (*ਮੁੱਲਾਂ)[parmnum] = parmval;
      ਜੇ (parmval == error_mark_ਗੰਢ)
	error_ਦਲੀਲਾਂ = ਸੱਚ;

      ਜੇ (!type && builtin_type && ਰੁੱਖ_ਕੋਡ (builtin_type) != VOID_TYPE)
	{
	  /* For a call to a built-in function declared without a prototype,
	     perform the conversions from the argument to the expected type
	     but issue warnings rather than errors for any mismatches.
	     Ignore the converted argument and use the PARMVAL obtained
	     above by applying default conversions instead.  */
	  ਰੁੱਖ origtype = (!origtypes) ? NULL_ਰੁੱਖ : (*origtypes)[parmnum];
	  convert_ਦਲੀਲ (ploc, function, fundecl, builtin_type, origtype,
			    val, valtype, npc, rname, parmnum, argnum,
			    excess_precision,
			    OPT_Wbuiltin_declaration_mismatch);
	}

      ਜੇ (typetail)
	typetail = ਰੁੱਖ_CHAIN (typetail);

      ਜੇ (builtin_typetail)
	builtin_typetail = ਰੁੱਖ_CHAIN (builtin_typetail);
    }

  gcc_assert (parmnum == vec_ਸੁਰੱਖਿਅਤ_ਲੰਮਾਈ (ਮੁੱਲਾਂ));

  ਜੇ (typetail != NULL_ਰੁੱਖ && ਰੁੱਖ_ਮੁੱਲ (typetail) != void_type_ਗੰਢ)
    {
      /* Not enough args.
	 Determine minimum number of arguments required.  */
      ਪੂਰਨ min_expected_ਅੰਕ = 0;
      ਤਾਰਕਿਕ at_ਘੱਟ_ਤੋਂ_ਘੱਟ_p = ਝੂਠ;
      ਰੁੱਖ iter = typelist;
      ਜਦੋਂ (ਸੱਚ)
	{
	  ਜੇ (!iter)
	    {
	      /* Variadic arguments; stop iterating.  */
	      at_ਘੱਟ_ਤੋਂ_ਘੱਟ_p = ਸੱਚ;
	      ਰੋਕੋ;
	    }
	  ਜੇ (iter == void_list_ਗੰਢ)
	    /* End of arguments; stop iterating.  */
	    ਰੋਕੋ;
	  ++min_expected_ਅੰਕ;
	  iter = ਰੁੱਖ_CHAIN (iter);
	}
      auto_diagnostic_ਸਮੂਹ d;
      ਪੂਰਨ actual_ਅੰਕ = vec_ਸੁਰੱਖਿਅਤ_ਲੰਮਾਈ (ਮੁੱਲਾਂ);
      error_at (loc,
		at_ਘੱਟ_ਤੋਂ_ਘੱਟ_p
		? G_("too few arguments to function %qE; expected at least %i, have %i")
		: G_("too few arguments to function %qE; expected %i, have %i"),
		function, min_expected_ਅੰਕ, actual_ਅੰਕ);
      inform_declaration (fundecl, function);
      ਵਾਪਸ -1;
    }

  ਜੇ (builtin_typetail && ਰੁੱਖ_ਮੁੱਲ (builtin_typetail) != void_type_ਗੰਢ)
    {
      ਬਿਨਾਨਿਸ਼ਾਨੀ nargs = parmnum;
      ਲਈ (ਰੁੱਖ t = builtin_typetail; t; t = ਰੁੱਖ_CHAIN (t))
	++nargs;

      auto_diagnostic_ਸਮੂਹ d;
      ਜੇ (warning_at (loc, OPT_Wbuiltin_declaration_mismatch,
		      "too few arguments to built-in function %qE "
		      "expecting %u", function, nargs - 1))
	inform_declaration (fundecl, function);
    }

  ਵਾਪਸ error_ਦਲੀਲਾਂ ? -1 : (ਪੂਰਨ) parmnum;
}

/* This is the entry point used by the parser to build unary operators
   in the input.  CODE, a tree_code, specifies the unary operator, and
   ARG is the operand.  For unary plus, the C parser currently uses
   CONVERT_EXPR for code.

   LOC is the location to use for the tree generated.
*/

ਬਣਤਰ c_ਵਿਅੰਜਕ
parser_build_unary_op (location_t loc, ਗਿਣਤੀ ਰੁੱਖ_ਕੋਡ_2 ਕੋਡ, ਬਣਤਰ c_ਵਿਅੰਜਕ arg)
{
  ਬਣਤਰ c_ਵਿਅੰਜਕ ਨਤੀਜਾ;

  ਨਤੀਜਾ.original_ਕੋਡ = ਕੋਡ;
  ਨਤੀਜਾ.original_type = ਨਿਰਾ;
  ਨਤੀਜਾ.m_decimal = 0;

  ਜੇ (reject_gcc_builtin (arg.ਮੁੱਲ))
    {
      ਨਤੀਜਾ.ਮੁੱਲ = error_mark_ਗੰਢ;
    }
  ਨਹੀਂਤਾਂ
    {
      ਨਤੀਜਾ.ਮੁੱਲ = build_unary_op (loc, ਕੋਡ, arg.ਮੁੱਲ, ਝੂਠ);

      ਜੇ (ਰੁੱਖ_ਉਛਾਲ_P (ਨਤੀਜਾ.ਮੁੱਲ) && !ਰੁੱਖ_ਉਛਾਲ_P (arg.ਮੁੱਲ))
	ਉਛਾਲ_warning (loc, ਨਤੀਜਾ.ਮੁੱਲ, arg.ਮੁੱਲ);
    }

  /* We are typically called when parsing a prefix token at LOC acting on
     ARG.  Reflect this by updating the source range of the result to
     start at LOC and end at the end of ARG.  */
  ਸੈੱਟ_c_ਵਿਅੰਜਕ_ਸਰੋਤ_range (&ਨਤੀਜਾ,
			   loc, arg.get_ਅੰਤ ());

  ਵਾਪਸ ਨਤੀਜਾ;
}

/* Returns true if TYPE is a character type, *not* including wchar_t.  */

ਤਾਰਕਿਕ
char_type_p (ਰੁੱਖ type)
{
  ਵਾਪਸ (type == char_type_ਗੰਢ
	  || type == unsigned_char_type_ਗੰਢ
	  || type == signed_char_type_ਗੰਢ
	  || type == char16_type_ਗੰਢ
	  || type == char32_type_ਗੰਢ);
}

/* This is the entry point used by the parser to build binary operators
   in the input.  CODE, a tree_code, specifies the binary operator, and
   ARG1 and ARG2 are the operands.  In addition to constructing the
   expression, we check for operands that were written with other binary
   operators in a way that is likely to confuse the user.  ORIG_ARG1 is
   the original first operand for TRUTH_{AND,OR}IF_EXPR before it is
   converted to truth value, otherwise NULL_TREE.

   LOCATION is the location of the binary operator.  */

ਬਣਤਰ c_ਵਿਅੰਜਕ
parser_build_ਦੁਆਧਾਰੀ_op (location_t location, ਗਿਣਤੀ ਰੁੱਖ_ਕੋਡ_2 ਕੋਡ,
			ਬਣਤਰ c_ਵਿਅੰਜਕ arg1, ਬਣਤਰ c_ਵਿਅੰਜਕ arg2, ਰੁੱਖ orig_arg1)
{
  ਬਣਤਰ c_ਵਿਅੰਜਕ ਨਤੀਜਾ;
  ਨਤੀਜਾ.m_decimal = 0;

  ਗਿਣਤੀ ਰੁੱਖ_ਕੋਡ_2 code1 = arg1.original_ਕੋਡ;
  ਗਿਣਤੀ ਰੁੱਖ_ਕੋਡ_2 code2 = arg2.original_ਕੋਡ;
  ਰੁੱਖ type1 = (arg1.original_type
                ? arg1.original_type
                : ਰੁੱਖ_TYPE (arg1.ਮੁੱਲ));
  ਰੁੱਖ type2 = (arg2.original_type
                ? arg2.original_type
                : ਰੁੱਖ_TYPE (arg2.ਮੁੱਲ));

  ਨਤੀਜਾ.ਮੁੱਲ = build_ਦੁਆਧਾਰੀ_op (location, ਕੋਡ,
				  arg1.ਮੁੱਲ, arg2.ਮੁੱਲ, ਸੱਚ);
  ਨਤੀਜਾ.original_ਕੋਡ = ਕੋਡ;
  ਨਤੀਜਾ.original_type = ਨਿਰਾ;
  ਨਤੀਜਾ.m_decimal = 0;

  ਜੇ (ਰੁੱਖ_ਕੋਡ (ਨਤੀਜਾ.ਮੁੱਲ) == ERROR_MARK)
    {
      ਸੈੱਟ_c_ਵਿਅੰਜਕ_ਸਰੋਤ_range (&ਨਤੀਜਾ,
			       arg1.get_ਸ਼ੁਰੂ (),
			       arg2.get_ਅੰਤ ());
      ਵਾਪਸ ਨਤੀਜਾ;
    }

  ਜੇ (location != UNKNOWN_LOCATION)
    protected_ਸੈੱਟ_ਵਿਅੰਜਕ_location (ਨਤੀਜਾ.ਮੁੱਲ, location);

  ਸੈੱਟ_c_ਵਿਅੰਜਕ_ਸਰੋਤ_range (&ਨਤੀਜਾ,
			   arg1.get_ਸ਼ੁਰੂ (),
			   arg2.get_ਅੰਤ ());

  /* Check for cases such as x+y<<z which users are likely
     to misinterpret.  */
  ਜੇ (warn_parentheses)
    warn_about_parentheses (location, ਕੋਡ, code1, arg1.ਮੁੱਲ, code2,
			    arg2.ਮੁੱਲ);

  ਜੇ (warn_logical_op)
    warn_logical_operator (location, ਕੋਡ, ਰੁੱਖ_TYPE (ਨਤੀਜਾ.ਮੁੱਲ),
			   code1, arg1.ਮੁੱਲ, code2, arg2.ਮੁੱਲ);

  ਜੇ (warn_constant_logical_ਸੰਕਾਰਜ
      && (ਕੋਡ == TRUTH_ANDIF_ਵਿਅੰਜਕ || ਕੋਡ == TRUTH_ORIF_ਵਿਅੰਜਕ)
      && INTEGRAL_NB_TYPE_P (type1)
      && INTEGRAL_NB_TYPE_P (type2))
    {
      ਅਚਲ ਅੱਖਰ *name = ਕੋਡ == TRUTH_ANDIF_ਵਿਅੰਜਕ ? "&&" : "||";
      ਜੇ (orig_arg1 == NULL_ਰੁੱਖ)
	orig_arg1 = arg1.ਮੁੱਲ;
      ਸਵੈਚਾਲਿਤ enum_other_than_0_1 = [] (ਰੁੱਖ type) {
	ਜੇ (ਰੁੱਖ_ਕੋਡ (type) != ENUMERAL_TYPE)
	  ਵਾਪਸ ਝੂਠ;
	ਲਈ (ਰੁੱਖ l = TYPE_ਮੁੱਲਾਂ (type); l; l = ਰੁੱਖ_CHAIN (l))
	  {
	    ਰੁੱਖ v = DECL_INITIAL (ਰੁੱਖ_ਮੁੱਲ (l));
	    ਜੇ (!integer_zerop (v) && !integer_onep (v))
	      ਵਾਪਸ ਸੱਚ;
	  }
	ਵਾਪਸ ਝੂਠ;
      };
      ਸਵੈਚਾਲਿਤ diagnose_constant_logical_ਸੰਕਾਰਜ = [=] (ਰੁੱਖ val, ਰੁੱਖ type) {
	ਜੇ (ਰੁੱਖ_ਕੋਡ (val) != INTEGER_CST || integer_zerop (val))
	  ਵਾਪਸ ਝੂਠ;
	ਜੇ (integer_onep (val) && !enum_other_than_0_1 (type))
	  ਵਾਪਸ ਝੂਠ;
	gcc_rich_location richloc (location);
	richloc.ਜੋੜੋ_fixit_replace (name + 1);
	auto_diagnostic_ਸਮੂਹ d;
	ਜੇ (warning_at (location, OPT_Wconstant_logical_ਸੰਕਾਰਜ,
			"use of logical %qs with constant operand %qE",
			name, val))
	  inform (&richloc, "use %qs for bitwise operation", name + 1);
	ਵਾਪਸ ਸੱਚ;
      };
      ਜੇ (!diagnose_constant_logical_ਸੰਕਾਰਜ (arg2.ਮੁੱਲ, type2))
	diagnose_constant_logical_ਸੰਕਾਰਜ (orig_arg1, type1);
    }

  ਜੇ (warn_tautological_compare)
    {
      ਰੁੱਖ lhs = arg1.ਮੁੱਲ;
      ਰੁੱਖ rhs = arg2.ਮੁੱਲ;
      ਜੇ (ਰੁੱਖ_ਕੋਡ (lhs) == C_MAYBE_CONST_ਵਿਅੰਜਕ)
	{
	  ਜੇ (C_MAYBE_CONST_ਵਿਅੰਜਕ_PRE (lhs) != NULL_ਰੁੱਖ
	      && ਰੁੱਖ_SIDE_EFFECTS (C_MAYBE_CONST_ਵਿਅੰਜਕ_PRE (lhs)))
	    lhs = NULL_ਰੁੱਖ;
	  ਨਹੀਂਤਾਂ
	    lhs = C_MAYBE_CONST_ਵਿਅੰਜਕ_ਵਿਅੰਜਕ (lhs);
	}
      ਜੇ (ਰੁੱਖ_ਕੋਡ (rhs) == C_MAYBE_CONST_ਵਿਅੰਜਕ)
	{
	  ਜੇ (C_MAYBE_CONST_ਵਿਅੰਜਕ_PRE (rhs) != NULL_ਰੁੱਖ
	      && ਰੁੱਖ_SIDE_EFFECTS (C_MAYBE_CONST_ਵਿਅੰਜਕ_PRE (rhs)))
	    rhs = NULL_ਰੁੱਖ;
	  ਨਹੀਂਤਾਂ
	    rhs = C_MAYBE_CONST_ਵਿਅੰਜਕ_ਵਿਅੰਜਕ (rhs);
	}
      ਜੇ (lhs != NULL_ਰੁੱਖ && rhs != NULL_ਰੁੱਖ)
	warn_tautological_cmp (location, ਕੋਡ, lhs, rhs);
    }

  ਜੇ (warn_logical_not_paren
      && ਰੁੱਖ_ਕੋਡ_CLASS (ਕੋਡ) == tcc_comparison
      && code1 == TRUTH_NOT_ਵਿਅੰਜਕ
      && code2 != TRUTH_NOT_ਵਿਅੰਜਕ
      /* Avoid warning for !!x == y.  */
      && (ਰੁੱਖ_ਕੋਡ (arg1.ਮੁੱਲ) != NE_ਵਿਅੰਜਕ
	  || !integer_zerop (ਰੁੱਖ_ਸੰਕਾਰਜ (arg1.ਮੁੱਲ, 1))))
    {
      /* Avoid warning for !b == y where b has _Bool type.  */
      ਰੁੱਖ t = integer_zero_ਗੰਢ;
      ਜੇ (ਰੁੱਖ_ਕੋਡ (arg1.ਮੁੱਲ) == EQ_ਵਿਅੰਜਕ
	  && integer_zerop (ਰੁੱਖ_ਸੰਕਾਰਜ (arg1.ਮੁੱਲ, 1))
	  && ਰੁੱਖ_TYPE (ਰੁੱਖ_ਸੰਕਾਰਜ (arg1.ਮੁੱਲ, 0)) == integer_type_ਗੰਢ)
	{
	  t = ਰੁੱਖ_ਸੰਕਾਰਜ (arg1.ਮੁੱਲ, 0);
	  ਕਰੋ
	    {
	      ਜੇ (ਰੁੱਖ_TYPE (t) != integer_type_ਗੰਢ)
		ਰੋਕੋ;
	      ਜੇ (ਰੁੱਖ_ਕੋਡ (t) == C_MAYBE_CONST_ਵਿਅੰਜਕ)
		t = C_MAYBE_CONST_ਵਿਅੰਜਕ_ਵਿਅੰਜਕ (t);
	      ਨਹੀਂਤਾਂ ਜੇ (CONVERT_ਵਿਅੰਜਕ_P (t))
		t = ਰੁੱਖ_ਸੰਕਾਰਜ (t, 0);
	      ਨਹੀਂਤਾਂ
		ਰੋਕੋ;
	    }
	  ਜਦੋਂ (1);
	}
      ਜੇ (!C_BOOLEAN_TYPE_P (ਰੁੱਖ_TYPE (t)))
	warn_logical_not_parentheses (location, ਕੋਡ, arg1.ਮੁੱਲ, arg2.ਮੁੱਲ);
    }

  /* Warn about comparisons against string literals, with the exception
     of testing for equality or inequality of a string literal with NULL.  */
  ਜੇ (ਕੋਡ == EQ_ਵਿਅੰਜਕ || ਕੋਡ == NE_ਵਿਅੰਜਕ)
    {
      ਜੇ ((code1 == STRING_CST
	   && !integer_zerop (ਰੁੱਖ_strip_nop_conversions (arg2.ਮੁੱਲ)))
	  || (code2 == STRING_CST
	      && !integer_zerop (ਰੁੱਖ_strip_nop_conversions (arg1.ਮੁੱਲ))))
	warning_at (location, OPT_Waddress,
		    "comparison with string literal results in unspecified behavior");
      /* Warn for ptr == '\0', it's likely that it should've been ptr[0].  */
      ਜੇ (ਸੂਚਕ_TYPE_P (type1)
	  && null_ਸੂਚਕ_constant_p (arg2.ਮੁੱਲ)
	  && char_type_p (type2))
	{
	  auto_diagnostic_ਸਮੂਹ d;
	  ਜੇ (warning_at (location, OPT_Wpointer_compare,
			    "comparison between pointer and zero character "
			    "constant"))
	    inform (arg1.get_ਸ਼ੁਰੂ (),
		      "did you mean to dereference the pointer?");
	}
      ਨਹੀਂਤਾਂ ਜੇ (ਸੂਚਕ_TYPE_P (type2)
	       && null_ਸੂਚਕ_constant_p (arg1.ਮੁੱਲ)
	       && char_type_p (type1))
	{
	  auto_diagnostic_ਸਮੂਹ d;
	  ਜੇ (warning_at (location, OPT_Wpointer_compare,
			    "comparison between pointer and zero character "
			    "constant"))
	    inform (arg2.get_ਸ਼ੁਰੂ (),
		      "did you mean to dereference the pointer?");
	}
    }
  ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਕੋਡ_CLASS (ਕੋਡ) == tcc_comparison
	   && (code1 == STRING_CST || code2 == STRING_CST))
    warning_at (location, OPT_Waddress,
		"comparison with string literal results in unspecified "
		"behavior");

  ਜੇ (warn_zero_as_null_ਸੂਚਕ_constant
      && c_inhibit_evaluation_warnings == 0
      && ਰੁੱਖ_ਕੋਡ_CLASS (ਕੋਡ) == tcc_comparison)
    {
      ਜੇ ((ਰੁੱਖ_ਕੋਡ (type1) == ਸੂਚਕ_TYPE
	   || ਰੁੱਖ_ਕੋਡ (type1) == NULLPTR_TYPE)
	  && INTEGRAL_TYPE_P (type2)
	  && null_ਸੂਚਕ_constant_p (arg2.ਮੁੱਲ))
	warning_at (arg2.get_location(), OPT_Wzero_as_null_ਸੂਚਕ_constant,
		    "zero as null pointer constant");

      ਜੇ ((ਰੁੱਖ_ਕੋਡ (type2) == ਸੂਚਕ_TYPE
	   || ਰੁੱਖ_ਕੋਡ (type2) == NULLPTR_TYPE)
	  && INTEGRAL_TYPE_P (type1)
	  && null_ਸੂਚਕ_constant_p (arg1.ਮੁੱਲ))
	warning_at (arg1.get_location(), OPT_Wzero_as_null_ਸੂਚਕ_constant,
		    "zero as null pointer constant");
    }

  ਜੇ (warn_array_compare
      && ਰੁੱਖ_ਕੋਡ_CLASS (ਕੋਡ) == tcc_comparison
      && ਰੁੱਖ_ਕੋਡ (type1) == ARRAY_TYPE
      && ਰੁੱਖ_ਕੋਡ (type2) == ARRAY_TYPE)
    do_warn_array_compare (location, ਕੋਡ, arg1.ਮੁੱਲ, arg2.ਮੁੱਲ);

  ਜੇ (ਰੁੱਖ_ਉਛਾਲ_P (ਨਤੀਜਾ.ਮੁੱਲ)
      && !ਰੁੱਖ_ਉਛਾਲ_P (arg1.ਮੁੱਲ)
      && !ਰੁੱਖ_ਉਛਾਲ_P (arg2.ਮੁੱਲ))
    ਉਛਾਲ_warning (location, ਨਤੀਜਾ.ਮੁੱਲ);

  /* Warn about comparisons of different enum types.  */
  ਜੇ (warn_enum_compare
      && ਰੁੱਖ_ਕੋਡ_CLASS (ਕੋਡ) == tcc_comparison
      && ਰੁੱਖ_ਕੋਡ (type1) == ENUMERAL_TYPE
      && ਰੁੱਖ_ਕੋਡ (type2) == ENUMERAL_TYPE
      && TYPE_MAIN_VARIANT (type1) != TYPE_MAIN_VARIANT (type2))
    warning_at (location, OPT_Wenum_compare,
		"comparison between %qT and %qT",
		type1, type2);

  ਜੇ (warn_xor_ਵਰਤਿਆ_as_pow
      && ਕੋਡ == ਦੋਆਧਾਰੀ_ਅੰਕ_XOR_ਵਿਅੰਜਕ
      && arg1.m_decimal
      && arg2.m_decimal)
    check_for_xor_ਵਰਤਿਆ_as_pow (arg1.get_location (), arg1.ਮੁੱਲ,
			       location,
			       arg2.get_location (), arg2.ਮੁੱਲ);

  ਵਾਪਸ ਨਤੀਜਾ;
}

/* Return a tree for the difference of pointers OP0 and OP1.
   The resulting tree has type ptrdiff_t.  If POINTER_SUBTRACT sanitization is
   enabled, assign to INSTRUMENT_EXPR call to libsanitizer.  */

ਸਥਿਰ ਰੁੱਖ
ਸੂਚਕ_diff (location_t loc, ਰੁੱਖ op0, ਰੁੱਖ op1, ਰੁੱਖ *instrument_ਵਿਅੰਜਕ)
{
  ਰੁੱਖ restype = ptrdiff_type_ਗੰਢ;
  ਰੁੱਖ ਨਤੀਜਾ, inttype;

  addr_space_t as0 = TYPE_ADDR_SPACE (ਰੁੱਖ_TYPE (ਰੁੱਖ_TYPE (op0)));
  addr_space_t as1 = TYPE_ADDR_SPACE (ਰੁੱਖ_TYPE (ਰੁੱਖ_TYPE (op1)));
  ਰੁੱਖ ਨਿਸ਼ਾਨਾ_type = ਰੁੱਖ_TYPE (ਰੁੱਖ_TYPE (op0));
  ਰੁੱਖ orig_op0 = op0;
  ਰੁੱਖ orig_op1 = op1;

  /* If the operands point into different address spaces, we need to
     explicitly convert them to pointers into the common address space
     before we can subtract the numerical address values.  */
  ਜੇ (as0 != as1)
    {
      addr_space_t as_common;
      ਰੁੱਖ common_type;

      /* Determine the common superset address space.  This is guaranteed
	 to exist because the caller verified that comp_target_types
	 returned non-zero.  */
      ਜੇ (!addr_space_superset (as0, as1, &as_common))
	gcc_unreachable ();

      common_type = common_ਸੂਚਕ_type (ਰੁੱਖ_TYPE (op0), ਰੁੱਖ_TYPE (op1), NULL_ਰੁੱਖ);
      op0 = convert (common_type, op0);
      op1 = convert (common_type, op1);
    }

  /* Determine integer type result of the subtraction.  This will usually
     be the same as the result type (ptrdiff_t), but may need to be a wider
     type if pointers for the address space are wider than ptrdiff_t.  */
  ਜੇ (TYPE_PRECISION (restype) < TYPE_PRECISION (ਰੁੱਖ_TYPE (op0)))
    inttype = c_common_type_for_ਮਾਪ (TYPE_PRECISION (ਰੁੱਖ_TYPE (op0)), 0);
  ਨਹੀਂਤਾਂ
    inttype = restype;

  ਜੇ (VOID_TYPE_P (ਨਿਸ਼ਾਨਾ_type))
    pedwarn (loc, OPT_Wpointer_arith,
	     "pointer of type %<void *%> used in subtraction");
  ਜੇ (ਰੁੱਖ_ਕੋਡ (ਨਿਸ਼ਾਨਾ_type) == FUNCTION_TYPE)
    pedwarn (loc, OPT_Wpointer_arith,
	     "pointer to a function used in subtraction");

  ਜੇ (current_function_decl != NULL_ਰੁੱਖ
      && sanitize_flags_p (SANITIZE_ਸੂਚਕ_ਘਟਾਓ))
    {
      op0 = save_ਵਿਅੰਜਕ (c_fully_fold (op0, ਝੂਠ, ਨਿਰਾ));
      op1 = save_ਵਿਅੰਜਕ (c_fully_fold (op1, ਝੂਠ, ਨਿਰਾ));

      ਰੁੱਖ tt = builtin_decl_explicit (BUILT_ਵਿੱਚ_ASAN_ਸੂਚਕ_ਘਟਾਓ);
      *instrument_ਵਿਅੰਜਕ = build_call_ਵਿਅੰਜਕ_loc (loc, tt, 2, op0, op1);
    }

  /* First do the subtraction, then build the divide operator
     and only convert at the very end.
     Do not do default conversions in case restype is a short type.  */

  /* POINTER_DIFF_EXPR requires a signed integer type of the same size as
     pointers.  If some platform cannot provide that, or has a larger
     ptrdiff_type to support differences larger than half the address
     space, cast the pointers to some larger integer type and do the
     computations in that type.  */
  ਜੇ (TYPE_PRECISION (inttype) > TYPE_PRECISION (ਰੁੱਖ_TYPE (op0)))
    op0 = build_ਦੁਆਧਾਰੀ_op (loc, MINUS_ਵਿਅੰਜਕ, convert (inttype, op0),
			   convert (inttype, op1), ਝੂਠ);
  ਨਹੀਂਤਾਂ
    {
      /* Cast away qualifiers.  */
      op0 = convert (c_common_type (ਰੁੱਖ_TYPE (op0), ਰੁੱਖ_TYPE (op0)), op0);
      op1 = convert (c_common_type (ਰੁੱਖ_TYPE (op1), ਰੁੱਖ_TYPE (op1)), op1);
      op0 = build2_loc (loc, ਸੂਚਕ_DIFF_ਵਿਅੰਜਕ, inttype, op0, op1);
    }

  /* This generates an error if op1 is pointer to incomplete type.  */
  ਜੇ (!COMPLETE_OR_VOID_TYPE_P (ਰੁੱਖ_TYPE (ਰੁੱਖ_TYPE (orig_op1))))
    error_at (loc, "arithmetic on pointer to an incomplete type");
  ਨਹੀਂਤਾਂ ਜੇ (verify_type_context (loc, TCTX_ਸੂਚਕ_ARITH,
				ਰੁੱਖ_TYPE (ਰੁੱਖ_TYPE (orig_op0))))
    verify_type_context (loc, TCTX_ਸੂਚਕ_ARITH,
			 ਰੁੱਖ_TYPE (ਰੁੱਖ_TYPE (orig_op1)));

  op1 = c_ਮਾਪ_ਵਿੱਚ_ਬਾਈਟਾਂ (ਨਿਸ਼ਾਨਾ_type);

  ਜੇ (ਸੂਚਕ_ਮੰਜ਼ਿਲ_zero_sized_aggr_p (ਰੁੱਖ_TYPE (orig_op1)))
    error_at (loc, "arithmetic on pointer to an empty aggregate");

  /* Divide by the size, in easiest possible way.  */
  ਨਤੀਜਾ = fold_build2_loc (loc, EXACT_DIV_ਵਿਅੰਜਕ, inttype,
			    op0, convert (inttype, op1));

  /* Convert to final result type if necessary.  */
  ਵਾਪਸ convert (restype, ਨਤੀਜਾ);
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

ਸਥਿਰ ਰੁੱਖ
build_atomic_ਸੌਂਪੋ (location_t loc, ਰੁੱਖ lhs, ਗਿਣਤੀ ਰੁੱਖ_ਕੋਡ_2 modifycode,
		     ਰੁੱਖ rhs, ਤਾਰਕਿਕ return_old_p)
{
  ਰੁੱਖ fndecl, func_call;
  vec<ਰੁੱਖ, va_gc> *params;
  ਰੁੱਖ val, nonatomic_lhs_type, nonatomic_rhs_type, newval, newval_addr;
  ਰੁੱਖ old, old_addr;
  ਰੁੱਖ compound_stmt = NULL_ਰੁੱਖ;
  ਰੁੱਖ stmt, goto_stmt;
  ਰੁੱਖ loop_label, loop_decl, ਪੂਰਾ_label, ਪੂਰਾ_decl;

  ਰੁੱਖ lhs_type = ਰੁੱਖ_TYPE (lhs);
  ਰੁੱਖ lhs_addr = build_unary_op (loc, ADDR_ਵਿਅੰਜਕ, lhs, ਝੂਠ);
  ਰੁੱਖ seq_cst = build_int_cst (integer_type_ਗੰਢ, MEMMODEL_SEQ_CST);
  ਰੁੱਖ rhs_semantic_type = ਰੁੱਖ_TYPE (rhs);
  ਰੁੱਖ nonatomic_rhs_semantic_type;
  ਰੁੱਖ rhs_type;

  gcc_assert (TYPE_ATOMIC (lhs_type));

  ਜੇ (return_old_p)
    gcc_assert (modifycode == PLUS_ਵਿਅੰਜਕ || modifycode == MINUS_ਵਿਅੰਜਕ);

  /* Allocate enough vector items for a compare_exchange.  */
  vec_alloc (params, 6);

  /* Create a compound statement to hold the sequence of statements
     with a loop.  */
  ਜੇ (modifycode != NOP_ਵਿਅੰਜਕ)
    {
      compound_stmt = c_begin_compound_stmt (ਝੂਠ);

      /* For consistency with build_modify_expr on non-_Atomic,
	 mark the lhs as read.  Also, it would be very hard to match
	 such expressions in mark_exp_read.  */
      mark_exp_read (lhs);
    }

  /* Remove any excess precision (which is only present here in the
     case of compound assignments).  */
  ਜੇ (ਰੁੱਖ_ਕੋਡ (rhs) == EXCESS_PRECISION_ਵਿਅੰਜਕ)
    {
      gcc_assert (modifycode != NOP_ਵਿਅੰਜਕ);
      rhs = ਰੁੱਖ_ਸੰਕਾਰਜ (rhs, 0);
    }
  rhs_type = ਰੁੱਖ_TYPE (rhs);

  /* Fold the RHS if it hasn't already been folded.  */
  ਜੇ (modifycode != NOP_ਵਿਅੰਜਕ)
    rhs = c_fully_fold (rhs, ਝੂਠ, ਨਿਰਾ);

  /* Remove the qualifiers for the rest of the expressions and create
     the VAL temp variable to hold the RHS.  */
  nonatomic_lhs_type = build_qualified_type (lhs_type, TYPE_UNQUALIFIED);
  nonatomic_rhs_type = build_qualified_type (rhs_type, TYPE_UNQUALIFIED);
  nonatomic_rhs_semantic_type = build_qualified_type (rhs_semantic_type,
						      TYPE_UNQUALIFIED);
  val = create_tmp_var_raw (nonatomic_rhs_type);
  ਰੁੱਖ_ADDRESSABLE (val) = 1;
  suppress_warning (val);
  rhs = build4 (ਨਿਸ਼ਾਨਾ_ਵਿਅੰਜਕ, nonatomic_rhs_type, val, rhs, NULL_ਰੁੱਖ,
		NULL_ਰੁੱਖ);
  ਰੁੱਖ_SIDE_EFFECTS (rhs) = 1;
  ਸੈੱਟ_ਵਿਅੰਜਕ_LOCATION (rhs, loc);
  ਜੇ (modifycode != NOP_ਵਿਅੰਜਕ)
    ਜੋੜੋ_stmt (rhs);

  /* NOP_EXPR indicates it's a straight store of the RHS. Simply issue
     an atomic_store.  */
  ਜੇ (modifycode == NOP_ਵਿਅੰਜਕ)
    {
      compound_stmt = rhs;
      /* Build __atomic_store (&lhs, &val, SEQ_CST)  */
      rhs = build_unary_op (loc, ADDR_ਵਿਅੰਜਕ, val, ਝੂਠ);
      fndecl = builtin_decl_explicit (BUILT_ਵਿੱਚ_ATOMIC_STORE);
      params->ਤੇਜ਼_ਧੱਕੋ (lhs_addr);
      params->ਤੇਜ਼_ਧੱਕੋ (rhs);
      params->ਤੇਜ਼_ਧੱਕੋ (seq_cst);
      func_call = c_build_function_call_vec (loc, vNULL, fndecl, params, ਨਿਰਾ);

      compound_stmt = build2 (COMPOUND_ਵਿਅੰਜਕ, void_type_ਗੰਢ,
			      compound_stmt, func_call);

      /* VAL is the value which was stored, return a COMPOUND_STMT of
	 the statement and that value.  */
      ਵਾਪਸ build2 (COMPOUND_ਵਿਅੰਜਕ, nonatomic_lhs_type, compound_stmt, val);
    }

  /* Attempt to implement the atomic operation as an __atomic_fetch_* or
     __atomic_*_fetch built-in rather than a CAS loop.  atomic_bool type
     isn't applicable for such builtins.  ??? Do we want to handle enums?  */
  ਜੇ ((ਰੁੱਖ_ਕੋਡ (lhs_type) == INTEGER_TYPE || ਸੂਚਕ_TYPE_P (lhs_type))
      && ਰੁੱਖ_ਕੋਡ (rhs_type) == INTEGER_TYPE)
    {
      built_ਵਿੱਚ_function fncode;
      ਚੋਣ (modifycode)
	{
	ਹਾਲਤ PLUS_ਵਿਅੰਜਕ:
	ਹਾਲਤ ਸੂਚਕ_PLUS_ਵਿਅੰਜਕ:
	  fncode = (return_old_p
		    ? BUILT_ਵਿੱਚ_ATOMIC_FETCH_ਜੋੜੋ_N
		    : BUILT_ਵਿੱਚ_ATOMIC_ਜੋੜੋ_FETCH_N);
	  ਰੋਕੋ;
	ਹਾਲਤ MINUS_ਵਿਅੰਜਕ:
	  fncode = (return_old_p
		    ? BUILT_ਵਿੱਚ_ATOMIC_FETCH_SUB_N
		    : BUILT_ਵਿੱਚ_ATOMIC_SUB_FETCH_N);
	  ਰੋਕੋ;
	ਹਾਲਤ ਦੋਆਧਾਰੀ_ਅੰਕ_AND_ਵਿਅੰਜਕ:
	  fncode = (return_old_p
		    ? BUILT_ਵਿੱਚ_ATOMIC_FETCH_AND_N
		    : BUILT_ਵਿੱਚ_ATOMIC_AND_FETCH_N);
	  ਰੋਕੋ;
	ਹਾਲਤ ਦੋਆਧਾਰੀ_ਅੰਕ_IOR_ਵਿਅੰਜਕ:
	  fncode = (return_old_p
		    ? BUILT_ਵਿੱਚ_ATOMIC_FETCH_OR_N
		    : BUILT_ਵਿੱਚ_ATOMIC_OR_FETCH_N);
	  ਰੋਕੋ;
	ਹਾਲਤ ਦੋਆਧਾਰੀ_ਅੰਕ_XOR_ਵਿਅੰਜਕ:
	  fncode = (return_old_p
		    ? BUILT_ਵਿੱਚ_ATOMIC_FETCH_XOR_N
		    : BUILT_ਵਿੱਚ_ATOMIC_XOR_FETCH_N);
	  ਰੋਕੋ;
	ਮੂਲ:
	  ਜਾਓ cas_loop;
	}

      /* We can only use "_1" through "_16" variants of the atomic fetch
	 built-ins.  */
      ਬਿਨਾਨਿਸ਼ਾਨੀ HOST_WIDE_INT ਮਾਪ = ਰੁੱਖ_ਮੰਜ਼ਿਲ_uhwi (TYPE_ਮਾਪ_UNIT (lhs_type));
      ਜੇ (ਮਾਪ != 1 && ਮਾਪ != 2 && ਮਾਪ != 4 && ਮਾਪ != 8 && ਮਾਪ != 16)
	ਜਾਓ cas_loop;

      /* If this is a pointer type, we need to multiply by the size of
	 the pointer target type.  */
      ਜੇ (ਸੂਚਕ_TYPE_P (lhs_type))
	{
	  ਜੇ (!COMPLETE_TYPE_P (ਰੁੱਖ_TYPE (lhs_type))
	      /* ??? This would introduce -Wdiscarded-qualifiers
		 warning: __atomic_fetch_* expect volatile void *
		 type as the first argument.  (Assignments between
		 atomic and non-atomic objects are OK.) */
	      || TYPE_RESTRICT (lhs_type))
	    ਜਾਓ cas_loop;
	  ਰੁੱਖ sz = TYPE_ਮਾਪ_UNIT (ਰੁੱਖ_TYPE (lhs_type));
	  rhs = fold_build2_loc (loc, MULT_ਵਿਅੰਜਕ, ptrdiff_type_ਗੰਢ,
				 convert (ptrdiff_type_ਗੰਢ, rhs),
				 convert (ptrdiff_type_ਗੰਢ, sz));
	}

      /* Build __atomic_fetch_* (&lhs, &val, SEQ_CST), or
	 __atomic_*_fetch (&lhs, &val, SEQ_CST).  */
      fndecl = builtin_decl_explicit (fncode);
      params->ਤੇਜ਼_ਧੱਕੋ (lhs_addr);
      params->ਤੇਜ਼_ਧੱਕੋ (rhs);
      params->ਤੇਜ਼_ਧੱਕੋ (seq_cst);
      func_call = c_build_function_call_vec (loc, vNULL, fndecl, params, ਨਿਰਾ);

      newval = create_tmp_var_raw (nonatomic_lhs_type);
      ਰੁੱਖ_ADDRESSABLE (newval) = 1;
      suppress_warning (newval);
      rhs = build4 (ਨਿਸ਼ਾਨਾ_ਵਿਅੰਜਕ, nonatomic_lhs_type, newval, func_call,
		    NULL_ਰੁੱਖ, NULL_ਰੁੱਖ);
      ਸੈੱਟ_ਵਿਅੰਜਕ_LOCATION (rhs, loc);
      ਜੋੜੋ_stmt (rhs);

      /* Finish the compound statement.  */
      compound_stmt = c_ਸਿਰਾ_compound_stmt (loc, compound_stmt, ਝੂਠ);

      /* NEWVAL is the value which was stored, return a COMPOUND_STMT of
	 the statement and that value.  */
      ਵਾਪਸ build2 (COMPOUND_ਵਿਅੰਜਕ, nonatomic_lhs_type, compound_stmt, newval);
    }

cas_loop:
  /* Create the variables and labels required for the op= form.  */
  old = create_tmp_var_raw (nonatomic_lhs_type);
  old_addr = build_unary_op (loc, ADDR_ਵਿਅੰਜਕ, old, ਝੂਠ);
  ਰੁੱਖ_ADDRESSABLE (old) = 1;
  suppress_warning (old);

  newval = create_tmp_var_raw (nonatomic_lhs_type);
  newval_addr = build_unary_op (loc, ADDR_ਵਿਅੰਜਕ, newval, ਝੂਠ);
  ਰੁੱਖ_ADDRESSABLE (newval) = 1;
  suppress_warning (newval);

  loop_decl = create_artificial_label (loc);
  loop_label = build1 (LABEL_ਵਿਅੰਜਕ, void_type_ਗੰਢ, loop_decl);

  ਪੂਰਾ_decl = create_artificial_label (loc);
  ਪੂਰਾ_label = build1 (LABEL_ਵਿਅੰਜਕ, void_type_ਗੰਢ, ਪੂਰਾ_decl);

  /* __atomic_load (addr, &old, SEQ_CST).  */
  fndecl = builtin_decl_explicit (BUILT_ਵਿੱਚ_ATOMIC_ਲੱਦੋ);
  params->ਤੇਜ਼_ਧੱਕੋ (lhs_addr);
  params->ਤੇਜ਼_ਧੱਕੋ (old_addr);
  params->ਤੇਜ਼_ਧੱਕੋ (seq_cst);
  func_call = c_build_function_call_vec (loc, vNULL, fndecl, params, ਨਿਰਾ);
  old = build4 (ਨਿਸ਼ਾਨਾ_ਵਿਅੰਜਕ, nonatomic_lhs_type, old, func_call, NULL_ਰੁੱਖ,
		NULL_ਰੁੱਖ);
  ਜੋੜੋ_stmt (old);
  params->truncate (0);

  /* Create the expressions for floating-point environment
     manipulation, if required.  */
  ਤਾਰਕਿਕ need_fenv = (flag_trapping_math
		    && (FLOAT_TYPE_P (lhs_type) || FLOAT_TYPE_P (rhs_type)));
  ਰੁੱਖ hold_call = NULL_ਰੁੱਖ, clear_call = NULL_ਰੁੱਖ, update_call = NULL_ਰੁੱਖ;
  ਜੇ (need_fenv)
    targetm.atomic_ਸੌਂਪੋ_expand_fenv (&hold_call, &clear_call, &update_call);

  ਜੇ (hold_call)
    ਜੋੜੋ_stmt (hold_call);

  /* loop:  */
  ਜੋੜੋ_stmt (loop_label);

  /* newval = old + val;  */
  ਜੇ (rhs_type != rhs_semantic_type)
    val = build1 (EXCESS_PRECISION_ਵਿਅੰਜਕ, nonatomic_rhs_semantic_type, val);
  rhs = build_ਦੁਆਧਾਰੀ_op (loc, modifycode,
			 convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (loc, old, ਸੱਚ, ਸੱਚ),
			 val, ਸੱਚ);
  ਜੇ (ਰੁੱਖ_ਕੋਡ (rhs) == EXCESS_PRECISION_ਵਿਅੰਜਕ)
    {
      ਰੁੱਖ eptype = ਰੁੱਖ_TYPE (rhs);
      rhs = c_fully_fold (ਰੁੱਖ_ਸੰਕਾਰਜ (rhs, 0), ਝੂਠ, ਨਿਰਾ);
      rhs = build1 (EXCESS_PRECISION_ਵਿਅੰਜਕ, eptype, rhs);
    }
  ਨਹੀਂਤਾਂ
    rhs = c_fully_fold (rhs, ਝੂਠ, ਨਿਰਾ);
  rhs = convert_for_assignment (loc, UNKNOWN_LOCATION, nonatomic_lhs_type,
				rhs, NULL_ਰੁੱਖ, ic_ਸੌਂਪੋ, ਝੂਠ, NULL_ਰੁੱਖ,
				NULL_ਰੁੱਖ, 0);
  /* The temporary variable for NEWVAL is only gimplified correctly (in
     particular, given a DECL_CONTEXT) if used in a TARGET_EXPR.  To avoid
     subsequent ICEs in nested function processing after an error, ensure such
     a TARGET_EXPR is built even after an error.  */
  ਜੇ (rhs == error_mark_ਗੰਢ)
    rhs = old;
  rhs = build4 (ਨਿਸ਼ਾਨਾ_ਵਿਅੰਜਕ, nonatomic_lhs_type, newval, rhs, NULL_ਰੁੱਖ,
		NULL_ਰੁੱਖ);
  ਸੈੱਟ_ਵਿਅੰਜਕ_LOCATION (rhs, loc);
  ਜੋੜੋ_stmt (rhs);

  /* if (__atomic_compare_exchange (addr, &old, &new, false, SEQ_CST, SEQ_CST))
       goto done;  */
  fndecl = builtin_decl_explicit (BUILT_ਵਿੱਚ_ATOMIC_COMPARE_EXCHANGE);
  params->ਤੇਜ਼_ਧੱਕੋ (lhs_addr);
  params->ਤੇਜ਼_ਧੱਕੋ (old_addr);
  params->ਤੇਜ਼_ਧੱਕੋ (newval_addr);
  params->ਤੇਜ਼_ਧੱਕੋ (integer_zero_ਗੰਢ);
  params->ਤੇਜ਼_ਧੱਕੋ (seq_cst);
  params->ਤੇਜ਼_ਧੱਕੋ (seq_cst);
  func_call = c_build_function_call_vec (loc, vNULL, fndecl, params, ਨਿਰਾ);

  goto_stmt = build1 (GOTO_ਵਿਅੰਜਕ, void_type_ਗੰਢ, ਪੂਰਾ_decl);
  ਸੈੱਟ_ਵਿਅੰਜਕ_LOCATION (goto_stmt, loc);

  stmt = build3 (COND_ਵਿਅੰਜਕ, void_type_ਗੰਢ, func_call, goto_stmt, NULL_ਰੁੱਖ);
  ਸੈੱਟ_ਵਿਅੰਜਕ_LOCATION (stmt, loc);
  ਜੋੜੋ_stmt (stmt);

  ਜੇ (clear_call)
    ਜੋੜੋ_stmt (clear_call);

  /* goto loop;  */
  goto_stmt  = build1 (GOTO_ਵਿਅੰਜਕ, void_type_ਗੰਢ, loop_decl);
  ਸੈੱਟ_ਵਿਅੰਜਕ_LOCATION (goto_stmt, loc);
  ਜੋੜੋ_stmt (goto_stmt);

  /* done:  */
  ਜੋੜੋ_stmt (ਪੂਰਾ_label);

  ਜੇ (update_call)
    ਜੋੜੋ_stmt (update_call);

  /* Finish the compound statement.  */
  compound_stmt = c_ਸਿਰਾ_compound_stmt (loc, compound_stmt, ਝੂਠ);

  /* NEWVAL is the value that was successfully stored, return a
     COMPOUND_EXPR of the statement and the appropriate value.  */
  ਵਾਪਸ build2 (COMPOUND_ਵਿਅੰਜਕ, nonatomic_lhs_type, compound_stmt,
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

ਰੁੱਖ
build_unary_op (location_t location, ਗਿਣਤੀ ਰੁੱਖ_ਕੋਡ_2 ਕੋਡ, ਰੁੱਖ xarg,
		ਤਾਰਕਿਕ noconvert)
{
  /* No default_conversion here.  It causes trouble for ADDR_EXPR.  */
  ਰੁੱਖ arg = xarg;
  ਰੁੱਖ argtype = NULL_ਰੁੱਖ;
  ਗਿਣਤੀ ਰੁੱਖ_ਕੋਡ_2 typecode;
  ਰੁੱਖ val;
  ਰੁੱਖ ret = error_mark_ਗੰਢ;
  ਰੁੱਖ eptype = NULL_ਰੁੱਖ;
  ਅਚਲ ਅੱਖਰ *invalid_op_diag;

  /* If ARG is wrapped in a call to .ACCESS_WITH_SIZE — created when the
     C parser rvalue-converts a counted_by-annotated member access (see
     PR123569) — unwrap it here.  Unary operators that consume an rvalue
     (!, -, +) read the value itself rather than dereferencing into the
     pointed-to data, so the bounds-checking wrapper is unnecessary and
     would otherwise reach build_unary_op while it is not equipped to
     handle the wrapped form.  PR123569 fixed the ++/-- side of this by
     suppressing wrapper creation in the parser; the rvalue-consuming
     ops still receive the wrapper and need to strip it here.  */
  ਜੇ (is_access_with_ਮਾਪ_p (arg))
    xarg = arg = get_ref_from_access_with_ਮਾਪ (arg);

  gcc_checking_assert (!is_access_with_ਮਾਪ_p (arg));

  ਤਾਰਕਿਕ int_operands = ਵਿਅੰਜਕ_INT_CONST_OPERANDS (xarg);
  ਜੇ (int_operands)
    arg = remove_c_maybe_const_ਵਿਅੰਜਕ (arg);

  ਜੇ (ਕੋਡ != ADDR_ਵਿਅੰਜਕ)
    arg = require_complete_type (location, arg);

  typecode = ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (arg));
  ਜੇ (typecode == ERROR_MARK)
    ਵਾਪਸ error_mark_ਗੰਢ;
  ਜੇ (typecode == ENUMERAL_TYPE || typecode == BOOLEAN_TYPE)
    typecode = INTEGER_TYPE;

  ਜੇ ((invalid_op_diag
       = targetm.invalid_unary_op (ਕੋਡ, ਰੁੱਖ_TYPE (xarg))))
    {
      error_at (location, invalid_op_diag);
      ਵਾਪਸ error_mark_ਗੰਢ;
    }

  ਜੇ (ਰੁੱਖ_ਕੋਡ (arg) == EXCESS_PRECISION_ਵਿਅੰਜਕ)
    {
      eptype = ਰੁੱਖ_TYPE (arg);
      arg = ਰੁੱਖ_ਸੰਕਾਰਜ (arg, 0);
    }

  ਚੋਣ (ਕੋਡ)
    {
    ਹਾਲਤ CONVERT_ਵਿਅੰਜਕ:
      /* This is used for unary plus, because a CONVERT_EXPR
	 is enough to prevent anybody from looking inside for
	 associativity, but won't generate any code.  */
      ਜੇ (!(typecode == INTEGER_TYPE || typecode == REAL_TYPE
	    || typecode == FIXED_ਬਿੰਦੂ_TYPE || typecode == COMPLEX_TYPE
	    || typecode == BITINT_TYPE
	    || gnu_ਸਦਿਸ਼_type_p (ਰੁੱਖ_TYPE (arg))))
	{
	  error_at (location, "wrong type argument to unary plus");
	  ਵਾਪਸ error_mark_ਗੰਢ;
	}
      ਨਹੀਂਤਾਂ ਜੇ (!noconvert)
	arg = default_conversion (arg);
      arg = non_lvalue_loc (location, arg);
      ਰੋਕੋ;

    ਹਾਲਤ NEGATE_ਵਿਅੰਜਕ:
      ਜੇ (!(typecode == INTEGER_TYPE || typecode == REAL_TYPE
	    || typecode == FIXED_ਬਿੰਦੂ_TYPE || typecode == COMPLEX_TYPE
	    || typecode == BITINT_TYPE
	    || gnu_ਸਦਿਸ਼_type_p (ਰੁੱਖ_TYPE (arg))))
	{
	  error_at (location, "wrong type argument to unary minus");
	  ਵਾਪਸ error_mark_ਗੰਢ;
	}
      ਨਹੀਂਤਾਂ ਜੇ (!noconvert)
	arg = default_conversion (arg);
      ਰੋਕੋ;

    ਹਾਲਤ ਦੋਆਧਾਰੀ_ਅੰਕ_NOT_ਵਿਅੰਜਕ:
      /* ~ works on integer types and non float vectors. */
      ਜੇ (typecode == INTEGER_TYPE
	  || typecode == BITINT_TYPE
	  || (gnu_ਸਦਿਸ਼_type_p (ਰੁੱਖ_TYPE (arg))
	      && !ਸਦਿਸ਼_FLOAT_TYPE_P (ਰੁੱਖ_TYPE (arg))))
	{
	  ਰੁੱਖ e = arg;

	  /* Warn if the expression has boolean value.  */
	  ਜਦੋਂ (ਰੁੱਖ_ਕੋਡ (e) == COMPOUND_ਵਿਅੰਜਕ)
	    e = ਰੁੱਖ_ਸੰਕਾਰਜ (e, 1);

	  ਜੇ ((C_BOOLEAN_TYPE_P (ਰੁੱਖ_TYPE (arg))
	       || truth_ਮੁੱਲ_p (ਰੁੱਖ_ਕੋਡ (e))))
	    {
	      auto_diagnostic_ਸਮੂਹ d;
	      ਜੇ (warning_at (location, OPT_Wbool_operation,
				"%<~%> on a boolean expression"))
		{
		  gcc_rich_location richloc (location);
		  richloc.ਜੋੜੋ_fixit_ਪਾਓ_before (location, "!");
		  inform (&richloc, "did you mean to use logical not?");
		}
	    }
	  ਜੇ (!noconvert)
	    arg = default_conversion (arg);
	}
      ਨਹੀਂਤਾਂ ਜੇ (typecode == COMPLEX_TYPE)
	{
	  ਕੋਡ = CONJ_ਵਿਅੰਜਕ;
	  pedwarn (location, OPT_Wpedantic,
		   "ISO C does not support %<~%> for complex conjugation");
	  ਜੇ (!noconvert)
	    arg = default_conversion (arg);
	}
      ਨਹੀਂਤਾਂ
	{
	  error_at (location, "wrong type argument to bit-complement");
	  ਵਾਪਸ error_mark_ਗੰਢ;
	}
      ਰੋਕੋ;

    ਹਾਲਤ ABS_ਵਿਅੰਜਕ:
      ਜੇ (!(typecode == INTEGER_TYPE || typecode == REAL_TYPE))
	{
	  error_at (location, "wrong type argument to abs");
	  ਵਾਪਸ error_mark_ਗੰਢ;
	}
      ਨਹੀਂਤਾਂ ਜੇ (!noconvert)
	arg = default_conversion (arg);
      ਰੋਕੋ;

    ਹਾਲਤ ABSU_ਵਿਅੰਜਕ:
      ਜੇ (!(typecode == INTEGER_TYPE))
	{
	  error_at (location, "wrong type argument to absu");
	  ਵਾਪਸ error_mark_ਗੰਢ;
	}
      ਨਹੀਂਤਾਂ ਜੇ (!noconvert)
	arg = default_conversion (arg);
      ਰੋਕੋ;

    ਹਾਲਤ CONJ_ਵਿਅੰਜਕ:
      /* Conjugating a real value is a no-op, but allow it anyway.  */
      ਜੇ (!(typecode == INTEGER_TYPE || typecode == REAL_TYPE
	    || typecode == COMPLEX_TYPE))
	{
	  error_at (location, "wrong type argument to conjugation");
	  ਵਾਪਸ error_mark_ਗੰਢ;
	}
      ਨਹੀਂਤਾਂ ਜੇ (!noconvert)
	arg = default_conversion (arg);
      ਰੋਕੋ;

    ਹਾਲਤ TRUTH_NOT_ਵਿਅੰਜਕ:
      ਜੇ (typecode != INTEGER_TYPE && typecode != FIXED_ਬਿੰਦੂ_TYPE
	  && typecode != REAL_TYPE && typecode != ਸੂਚਕ_TYPE
	  && typecode != COMPLEX_TYPE && typecode != NULLPTR_TYPE
	  && typecode != BITINT_TYPE)
	{
	  error_at (location,
		    "wrong type argument to unary exclamation mark");
	  ਵਾਪਸ error_mark_ਗੰਢ;
	}
      ਜੇ (int_operands)
	{
	  arg = c_objc_common_truthvalue_conversion (location, xarg);
	  arg = remove_c_maybe_const_ਵਿਅੰਜਕ (arg);
	}
      ਨਹੀਂਤਾਂ
	arg = c_objc_common_truthvalue_conversion (location, arg);
      ret = invert_truthvalue_loc (location, arg);
      eptype = NULL_ਰੁੱਖ;
      /* If the TRUTH_NOT_EXPR has been folded, reset the location.  */
      ਜੇ (ਵਿਅੰਜਕ_P (ret) && ਵਿਅੰਜਕ_HAS_LOCATION (ret))
	location = ਵਿਅੰਜਕ_LOCATION (ret);
      ਜਾਓ return_build_unary_op;

    ਹਾਲਤ REALPART_ਵਿਅੰਜਕ:
    ਹਾਲਤ IMAGPART_ਵਿਅੰਜਕ:
      ret = build_real_imag_ਵਿਅੰਜਕ (location, ਕੋਡ, arg);
      ਜੇ (ret == error_mark_ਗੰਢ)
	ਵਾਪਸ error_mark_ਗੰਢ;
      ਜੇ (eptype && ਰੁੱਖ_ਕੋਡ (eptype) == COMPLEX_TYPE)
	eptype = ਰੁੱਖ_TYPE (eptype);
      ਜਾਓ return_build_unary_op;

    ਹਾਲਤ PREINCREMENT_ਵਿਅੰਜਕ:
    ਹਾਲਤ POSTINCREMENT_ਵਿਅੰਜਕ:
    ਹਾਲਤ PREDECREMENT_ਵਿਅੰਜਕ:
    ਹਾਲਤ POSTDECREMENT_ਵਿਅੰਜਕ:

      ਜੇ (ਰੁੱਖ_ਕੋਡ (arg) == C_MAYBE_CONST_ਵਿਅੰਜਕ)
	{
	  ਰੁੱਖ inner = build_unary_op (location, ਕੋਡ,
				       C_MAYBE_CONST_ਵਿਅੰਜਕ_ਵਿਅੰਜਕ (arg),
				       noconvert);
	  ਜੇ (inner == error_mark_ਗੰਢ)
	    ਵਾਪਸ error_mark_ਗੰਢ;
	  ret = build2 (C_MAYBE_CONST_ਵਿਅੰਜਕ, ਰੁੱਖ_TYPE (inner),
			C_MAYBE_CONST_ਵਿਅੰਜਕ_PRE (arg), inner);
	  gcc_assert (!C_MAYBE_CONST_ਵਿਅੰਜਕ_INT_OPERANDS (arg));
	  C_MAYBE_CONST_ਵਿਅੰਜਕ_NON_CONST (ret) = 1;
	  ਜਾਓ return_build_unary_op;
	}

      /* Complain about anything that is not a true lvalue.  In
	 Objective-C, skip this check for property_refs.  */
      ਜੇ (!objc_is_property_ref (arg)
	  && !lvalue_or_else (location,
			      arg, ((ਕੋਡ == PREINCREMENT_ਵਿਅੰਜਕ
				     || ਕੋਡ == POSTINCREMENT_ਵਿਅੰਜਕ)
				    ? lv_increment
				    : lv_decrement)))
	ਵਾਪਸ error_mark_ਗੰਢ;

      ਜੇ (warn_cxx_compat && ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (arg)) == ENUMERAL_TYPE)
	{
	  ਜੇ (ਕੋਡ == PREINCREMENT_ਵਿਅੰਜਕ || ਕੋਡ == POSTINCREMENT_ਵਿਅੰਜਕ)
	    warning_at (location, OPT_Wc___compat,
			"increment of enumeration value is invalid in C++");
	  ਨਹੀਂਤਾਂ
	    warning_at (location, OPT_Wc___compat,
			"decrement of enumeration value is invalid in C++");
	}

      ਜੇ (C_BOOLEAN_TYPE_P (ਰੁੱਖ_TYPE (arg)))
	{
	  ਜੇ (ਕੋਡ == PREINCREMENT_ਵਿਅੰਜਕ || ਕੋਡ == POSTINCREMENT_ਵਿਅੰਜਕ)
	    warning_at (location, OPT_Wbool_operation,
			"increment of a boolean expression");
	  ਨਹੀਂਤਾਂ
	    warning_at (location, OPT_Wbool_operation,
			"decrement of a boolean expression");
	}

      /* Ensure the argument is fully folded inside any SAVE_EXPR.  */
      arg = c_fully_fold (arg, ਝੂਠ, ਨਿਰਾ, ਸੱਚ);

      ਤਾਰਕਿਕ atomic_op;
      atomic_op = really_atomic_lvalue (arg);

      /* Increment or decrement the real part of the value,
	 and don't change the imaginary part.  */
      ਜੇ (typecode == COMPLEX_TYPE)
	{
	  ਰੁੱਖ real, imag;

	  pedwarn_c23 (location, OPT_Wpedantic,
		       "ISO C does not support %<++%> and %<--%> on complex "
		       "types before C2Y");

	  ਜੇ (!atomic_op)
	    {
	      arg = stabilize_reference (arg);
	      real = build_unary_op (ਵਿਅੰਜਕ_LOCATION (arg), REALPART_ਵਿਅੰਜਕ, arg,
				     ਸੱਚ);
	      imag = build_unary_op (ਵਿਅੰਜਕ_LOCATION (arg), IMAGPART_ਵਿਅੰਜਕ, arg,
				     ਸੱਚ);
	      real = build_unary_op (ਵਿਅੰਜਕ_LOCATION (arg), ਕੋਡ, real, ਸੱਚ);
	      ਜੇ (real == error_mark_ਗੰਢ || imag == error_mark_ਗੰਢ)
		ਵਾਪਸ error_mark_ਗੰਢ;
	      ret = build2 (COMPLEX_ਵਿਅੰਜਕ, ਰੁੱਖ_TYPE (arg),
			    real, imag);
	      ਜਾਓ return_build_unary_op;
	    }
	}

      /* Report invalid types.  */

      ਜੇ (typecode != ਸੂਚਕ_TYPE && typecode != FIXED_ਬਿੰਦੂ_TYPE
	  && typecode != INTEGER_TYPE && typecode != REAL_TYPE
	  && typecode != COMPLEX_TYPE && typecode != BITINT_TYPE
	  && !gnu_ਸਦਿਸ਼_type_p (ਰੁੱਖ_TYPE (arg)))
	{
	  ਜੇ (ਕੋਡ == PREINCREMENT_ਵਿਅੰਜਕ || ਕੋਡ == POSTINCREMENT_ਵਿਅੰਜਕ)
	    error_at (location, "wrong type argument to increment");
	  ਨਹੀਂਤਾਂ
	    error_at (location, "wrong type argument to decrement");

	  ਵਾਪਸ error_mark_ਗੰਢ;
	}

      {
	ਰੁੱਖ inc;

	argtype = ਰੁੱਖ_TYPE (arg);

	/* Compute the increment.  */

	ਜੇ (typecode == ਸੂਚਕ_TYPE)
	  {
	    /* If pointer target is an incomplete type,
	       we just cannot know how to do the arithmetic.  */
	    ਜੇ (!COMPLETE_OR_VOID_TYPE_P (ਰੁੱਖ_TYPE (argtype)))
	      {
		ਜੇ (ਕੋਡ == PREINCREMENT_ਵਿਅੰਜਕ || ਕੋਡ == POSTINCREMENT_ਵਿਅੰਜਕ)
		  error_at (location,
			    "increment of pointer to an incomplete type %qT",
			    ਰੁੱਖ_TYPE (argtype));
		ਨਹੀਂਤਾਂ
		  error_at (location,
			    "decrement of pointer to an incomplete type %qT",
			    ਰੁੱਖ_TYPE (argtype));
	      }
	    ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (argtype)) == FUNCTION_TYPE
		     || VOID_TYPE_P (ਰੁੱਖ_TYPE (argtype)))
	      {
		ਜੇ (ਕੋਡ == PREINCREMENT_ਵਿਅੰਜਕ || ਕੋਡ == POSTINCREMENT_ਵਿਅੰਜਕ)
		  pedwarn (location, OPT_Wpointer_arith,
			   "wrong type argument to increment");
		ਨਹੀਂਤਾਂ
		  pedwarn (location, OPT_Wpointer_arith,
			   "wrong type argument to decrement");
	      }
	    ਨਹੀਂਤਾਂ
	      verify_type_context (location, TCTX_ਸੂਚਕ_ARITH,
				   ਰੁੱਖ_TYPE (argtype));

	    inc = c_ਮਾਪ_ਵਿੱਚ_ਬਾਈਟਾਂ (ਰੁੱਖ_TYPE (argtype));
	    inc = convert_ਮੰਜ਼ਿਲ_ptrofftype_loc (location, inc);
	  }
	ਨਹੀਂਤਾਂ ਜੇ (FRACT_ਬਹੁਲਕ_P (TYPE_ਬਹੁਲਕ (argtype)))
	  {
	    /* For signed fract types, we invert ++ to -- or
	       -- to ++, and change inc from 1 to -1, because
	       it is not possible to represent 1 in signed fract constants.
	       For unsigned fract types, the result always overflows and
	       we get an undefined (original) or the maximum value.  */
	    ਜੇ (ਕੋਡ == PREINCREMENT_ਵਿਅੰਜਕ)
	      ਕੋਡ = PREDECREMENT_ਵਿਅੰਜਕ;
	    ਨਹੀਂਤਾਂ ਜੇ (ਕੋਡ == PREDECREMENT_ਵਿਅੰਜਕ)
	      ਕੋਡ = PREINCREMENT_ਵਿਅੰਜਕ;
	    ਨਹੀਂਤਾਂ ਜੇ (ਕੋਡ == POSTINCREMENT_ਵਿਅੰਜਕ)
	      ਕੋਡ = POSTDECREMENT_ਵਿਅੰਜਕ;
	    ਨਹੀਂਤਾਂ /* code == POSTDECREMENT_EXPR  */
	      ਕੋਡ = POSTINCREMENT_ਵਿਅੰਜਕ;

	    inc = integer_minus_one_ਗੰਢ;
	    inc = convert (argtype, inc);
	  }
	ਨਹੀਂਤਾਂ
	  {
	    inc = ਸਦਿਸ਼_TYPE_P (argtype)
	      ? build_one_cst (argtype)
	      : integer_one_ਗੰਢ;
	    inc = convert (argtype, inc);
	  }

	/* If 'arg' is an Objective-C PROPERTY_REF expression, then we
	   need to ask Objective-C to build the increment or decrement
	   expression for it.  */
	ਜੇ (objc_is_property_ref (arg))
	  ਵਾਪਸ objc_build_incr_ਵਿਅੰਜਕ_for_property_ref (location, ਕੋਡ,
							arg, inc);

	/* Report a read-only lvalue.  */
	ਜੇ (TYPE_READONLY (argtype))
	  {
	    readonly_error (location, arg,
			    ((ਕੋਡ == PREINCREMENT_ਵਿਅੰਜਕ
			      || ਕੋਡ == POSTINCREMENT_ਵਿਅੰਜਕ)
			     ? lv_increment : lv_decrement));
	    ਵਾਪਸ error_mark_ਗੰਢ;
	  }
	ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_READONLY (arg))
	  readonly_warning (arg,
			    ((ਕੋਡ == PREINCREMENT_ਵਿਅੰਜਕ
			      || ਕੋਡ == POSTINCREMENT_ਵਿਅੰਜਕ)
			     ? lv_increment : lv_decrement));

	/* If the argument is atomic, use the special code sequences for
	   atomic compound assignment.  */
	ਜੇ (atomic_op)
	  {
	    arg = stabilize_reference (arg);
	    ret = build_atomic_ਸੌਂਪੋ (location, arg,
				       ((ਕੋਡ == PREINCREMENT_ਵਿਅੰਜਕ
					 || ਕੋਡ == POSTINCREMENT_ਵਿਅੰਜਕ)
					? PLUS_ਵਿਅੰਜਕ
					: MINUS_ਵਿਅੰਜਕ),
				       (FRACT_ਬਹੁਲਕ_P (TYPE_ਬਹੁਲਕ (argtype))
					? inc
					: integer_one_ਗੰਢ),
				       (ਕੋਡ == POSTINCREMENT_ਵਿਅੰਜਕ
					|| ਕੋਡ == POSTDECREMENT_ਵਿਅੰਜਕ));
	    ਜਾਓ return_build_unary_op;
	  }

	ਰੁੱਖ true_res;
	ਜੇ (c_hardbool_type_attr (ਰੁੱਖ_TYPE (arg), ਨਿਰਾ, &true_res))
	  {
	    ਰੁੱਖ larg = stabilize_reference (arg);
	    ਰੁੱਖ sarg = save_ਵਿਅੰਜਕ (larg);
	    ਚੋਣ (ਕੋਡ)
	      {
	      ਹਾਲਤ PREINCREMENT_ਵਿਅੰਜਕ:
		val = build2 (MODIFY_ਵਿਅੰਜਕ, ਰੁੱਖ_TYPE (larg), larg, true_res);
		val = build2 (COMPOUND_ਵਿਅੰਜਕ, ਰੁੱਖ_TYPE (larg), sarg, val);
		ਰੋਕੋ;
	      ਹਾਲਤ POSTINCREMENT_ਵਿਅੰਜਕ:
		val = build2 (MODIFY_ਵਿਅੰਜਕ, ਰੁੱਖ_TYPE (larg), larg, true_res);
		val = build2 (COMPOUND_ਵਿਅੰਜਕ, ਰੁੱਖ_TYPE (larg), val, sarg);
		val = build2 (COMPOUND_ਵਿਅੰਜਕ, ਰੁੱਖ_TYPE (larg), sarg, val);
		ਰੋਕੋ;
	      ਹਾਲਤ PREDECREMENT_ਵਿਅੰਜਕ:
		{
		  ਰੁੱਖ rarg = convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (location, sarg,
							ਸੱਚ, ਸੱਚ);
		  rarg = invert_truthvalue_loc (location, rarg);
		  rarg = convert (ਰੁੱਖ_TYPE (sarg), rarg);
		  val = build2 (MODIFY_ਵਿਅੰਜਕ, ਰੁੱਖ_TYPE (larg), larg, rarg);
		}
		ਰੋਕੋ;
	      ਹਾਲਤ POSTDECREMENT_ਵਿਅੰਜਕ:
		{
		  ਰੁੱਖ rarg = convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (location, sarg,
							ਸੱਚ, ਸੱਚ);
		  rarg = invert_truthvalue_loc (location, rarg);
		  ਰੁੱਖ iarg = convert (ਰੁੱਖ_TYPE (larg), rarg);
		  val = build2 (MODIFY_ਵਿਅੰਜਕ, ਰੁੱਖ_TYPE (larg), larg, iarg);
		  val = build2 (COMPOUND_ਵਿਅੰਜਕ, ਰੁੱਖ_TYPE (larg), val, sarg);
		  val = build2 (COMPOUND_ਵਿਅੰਜਕ, ਰੁੱਖ_TYPE (larg), sarg, val);
		}
		ਰੋਕੋ;
	      ਮੂਲ:
		gcc_unreachable ();
	      }
	    ਰੁੱਖ_SIDE_EFFECTS (val) = 1;
	  }
	ਨਹੀਂਤਾਂ ਜੇ (C_BOOLEAN_TYPE_P (ਰੁੱਖ_TYPE (arg)))
	  val = boolean_increment (ਕੋਡ, arg);
	ਨਹੀਂਤਾਂ
	  val = build2 (ਕੋਡ, ਰੁੱਖ_TYPE (arg), arg, inc);
	ਰੁੱਖ_SIDE_EFFECTS (val) = 1;
	ਜੇ (TYPE_QUALS (ਰੁੱਖ_TYPE (val)) != TYPE_UNQUALIFIED)
	  ਰੁੱਖ_TYPE (val) = c_build_qualified_type (ਰੁੱਖ_TYPE (val),
						    TYPE_UNQUALIFIED);
	ret = val;
	ਜਾਓ return_build_unary_op;
      }

    ਹਾਲਤ ADDR_ਵਿਅੰਜਕ:
      /* Note that this operation never does default_conversion.  */

      /* The operand of unary '&' must be an lvalue (which excludes
	 expressions of type void), or, in C99, the result of a [] or
	 unary '*' operator.  */
      ਜੇ (VOID_TYPE_P (ਰੁੱਖ_TYPE (arg))
	  && TYPE_QUALS (ਰੁੱਖ_TYPE (arg)) == TYPE_UNQUALIFIED
	  && (!ਅਸਿੱਧਾ_REF_P (arg) || !flag_isoc99))
	pedwarn (location, 0, "taking address of expression of type %<void%>");

      /* Let &* cancel out to simplify resulting code.  */
      ਜੇ (ਅਸਿੱਧਾ_REF_P (arg))
	{
	  /* Don't let this be an lvalue.  */
	  ਜੇ (lvalue_p (ਰੁੱਖ_ਸੰਕਾਰਜ (arg, 0)))
	    ਵਾਪਸ non_lvalue_loc (location, ਰੁੱਖ_ਸੰਕਾਰਜ (arg, 0));
	  ret = ਰੁੱਖ_ਸੰਕਾਰਜ (arg, 0);
	  ਜਾਓ return_build_unary_op;
	}

      /* Anything not already handled and not a true memory reference
	 or a non-lvalue array is an error.  */
      ਜੇ (typecode != FUNCTION_TYPE && !noconvert
	  && !lvalue_or_else (location, arg, lv_addressof))
	ਵਾਪਸ error_mark_ਗੰਢ;

      /* Move address operations inside C_MAYBE_CONST_EXPR to simplify
	 folding later.  */
      ਜੇ (ਰੁੱਖ_ਕੋਡ (arg) == C_MAYBE_CONST_ਵਿਅੰਜਕ)
	{
	  ਰੁੱਖ inner = build_unary_op (location, ਕੋਡ,
				       C_MAYBE_CONST_ਵਿਅੰਜਕ_ਵਿਅੰਜਕ (arg),
				       noconvert);
	  ret = build2 (C_MAYBE_CONST_ਵਿਅੰਜਕ, ਰੁੱਖ_TYPE (inner),
			C_MAYBE_CONST_ਵਿਅੰਜਕ_PRE (arg), inner);
	  gcc_assert (!C_MAYBE_CONST_ਵਿਅੰਜਕ_INT_OPERANDS (arg));
	  C_MAYBE_CONST_ਵਿਅੰਜਕ_NON_CONST (ret)
	    = C_MAYBE_CONST_ਵਿਅੰਜਕ_NON_CONST (arg);
	  ਜਾਓ return_build_unary_op;
	}

      /* Ordinary case; arg is a COMPONENT_REF or a decl.  */

      argtype = ਰੁੱਖ_TYPE (arg);

      /* If the lvalue is const or volatile, merge that into the type
	 to which the address will point.  This is only needed
	 for function types.  */
      ਜੇ ((DECL_P (arg) || REFERENCE_CLASS_P (arg))
	  && (ਰੁੱਖ_READONLY (arg) || ਰੁੱਖ_THIS_VOLATILE (arg))
	  && ਰੁੱਖ_ਕੋਡ (argtype) == FUNCTION_TYPE)
	{
	  ਪੂਰਨ orig_quals = TYPE_QUALS (strip_array_types (argtype));
	  ਪੂਰਨ quals = orig_quals;

	  ਜੇ (ਰੁੱਖ_READONLY (arg))
	    quals |= TYPE_QUAL_CONST;
	  ਜੇ (ਰੁੱਖ_THIS_VOLATILE (arg))
	    quals |= TYPE_QUAL_VOLATILE;

	  argtype = c_build_qualified_type (argtype, quals);
	}

      ਚੋਣ (ਰੁੱਖ_ਕੋਡ (arg))
	{
	ਹਾਲਤ COMPONENT_REF:
	  ਜੇ (DECL_C_ਦੋਆਧਾਰੀ_ਅੰਕ_ਖੇਤਰ (ਰੁੱਖ_ਸੰਕਾਰਜ (arg, 1)))
	    {
	      error_at (location, "cannot take address of bit-field %qD",
			ਰੁੱਖ_ਸੰਕਾਰਜ (arg, 1));
	      ਵਾਪਸ error_mark_ਗੰਢ;
	    }

	  /* fall through */

	ਹਾਲਤ ARRAY_REF:
	  ਜੇ (TYPE_ਉਲਟ_STORAGE_ਕ੍ਰਮ (ਰੁੱਖ_TYPE (ਰੁੱਖ_ਸੰਕਾਰਜ (arg, 0))))
	    {
	      ਜੇ (!AGGREGATE_TYPE_P (ਰੁੱਖ_TYPE (arg))
		  && !ਸੂਚਕ_TYPE_P (ਰੁੱਖ_TYPE (arg))
		  && !ਸਦਿਸ਼_TYPE_P (ਰੁੱਖ_TYPE (arg)))
		{
		  error_at (location, "cannot take address of scalar with "
			    "reverse storage order");
		  ਵਾਪਸ error_mark_ਗੰਢ;
		}

	      ਜੇ (ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (arg)) == ARRAY_TYPE
		  && TYPE_ਉਲਟ_STORAGE_ਕ੍ਰਮ (ਰੁੱਖ_TYPE (arg)))
		warning_at (location, OPT_Wscalar_storage_ਕ੍ਰਮ,
			    "address of array with reverse scalar storage "
			    "order requested");
	    }

	ਮੂਲ:
	  ਰੋਕੋ;
	}

      ਜੇ (!c_mark_addressable (arg))
	ਵਾਪਸ error_mark_ਗੰਢ;

      gcc_assert (ਰੁੱਖ_ਕੋਡ (arg) != COMPONENT_REF
		  || !DECL_C_ਦੋਆਧਾਰੀ_ਅੰਕ_ਖੇਤਰ (ਰੁੱਖ_ਸੰਕਾਰਜ (arg, 1)));

      argtype = c_build_ਸੂਚਕ_type (argtype);

      /* ??? Cope with user tricks that amount to offsetof.  Delete this
	 when we have proper support for integer constant expressions.  */
      val = get_ਅਧਾਰ_ਪਤਾ (arg);
      ਜੇ (val && ਅਸਿੱਧਾ_REF_P (val)
          && ਰੁੱਖ_CONSTANT (ਰੁੱਖ_ਸੰਕਾਰਜ (val, 0)))
	{
	  ret = fold_offsetof (arg, argtype);
	  ਜਾਓ return_build_unary_op;
	}

      val = build1 (ADDR_ਵਿਅੰਜਕ, argtype, arg);

      ret = val;
      ਜਾਓ return_build_unary_op;

    ਹਾਲਤ PAREN_ਵਿਅੰਜਕ:
      ret = build1 (ਕੋਡ, ਰੁੱਖ_TYPE (arg), arg);
      ਜਾਓ return_build_unary_op;

    ਮੂਲ:
      gcc_unreachable ();
    }

  ਜੇ (argtype == NULL_ਰੁੱਖ)
    argtype = ਰੁੱਖ_TYPE (arg);
  ਜੇ (ਰੁੱਖ_ਕੋਡ (arg) == INTEGER_CST)
    ret = (require_constant_ਮੁੱਲ
	   ? fold_build1_initializer_loc (location, ਕੋਡ, argtype, arg)
	   : fold_build1_loc (location, ਕੋਡ, argtype, arg));
  ਨਹੀਂਤਾਂ
    ret = build1 (ਕੋਡ, argtype, arg);
 return_build_unary_op:
  gcc_assert (ret != error_mark_ਗੰਢ);
  ਜੇ (ਰੁੱਖ_ਕੋਡ (ret) == INTEGER_CST && !ਰੁੱਖ_ਉਛਾਲ (ret)
      && !(ਰੁੱਖ_ਕੋਡ (xarg) == INTEGER_CST && !ਰੁੱਖ_ਉਛਾਲ (xarg)))
    ret = build1 (NOP_ਵਿਅੰਜਕ, ਰੁੱਖ_TYPE (ret), ret);
  ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਕੋਡ (ret) != INTEGER_CST && int_operands)
    ret = note_integer_operands (ret);
  ਜੇ (eptype)
    ret = build1 (EXCESS_PRECISION_ਵਿਅੰਜਕ, eptype, ret);
  protected_ਸੈੱਟ_ਵਿਅੰਜਕ_location (ret, location);
  ਵਾਪਸ ret;
}

/* Return nonzero if REF is an lvalue valid for this language.
   Lvalues can be assigned, unless their type has TYPE_READONLY.
   Lvalues can have their address taken, unless they have C_DECL_REGISTER.  */

ਤਾਰਕਿਕ
lvalue_p (const_ਰੁੱਖ ref)
{
  ਅਚਲ ਗਿਣਤੀ ਰੁੱਖ_ਕੋਡ_2 ਕੋਡ = ਰੁੱਖ_ਕੋਡ (ref);

  ਚੋਣ (ਕੋਡ)
    {
    ਹਾਲਤ REALPART_ਵਿਅੰਜਕ:
    ਹਾਲਤ IMAGPART_ਵਿਅੰਜਕ:
    ਹਾਲਤ COMPONENT_REF:
      ਵਾਪਸ lvalue_p (ਰੁੱਖ_ਸੰਕਾਰਜ (ref, 0));

    ਹਾਲਤ C_MAYBE_CONST_ਵਿਅੰਜਕ:
      ਵਾਪਸ lvalue_p (ਰੁੱਖ_ਸੰਕਾਰਜ (ref, 1));

    ਹਾਲਤ COMPOUND_LITERAL_ਵਿਅੰਜਕ:
    ਹਾਲਤ STRING_CST:
      ਵਾਪਸ ਸੱਚ;

    ਹਾਲਤ MEM_REF:
    ਹਾਲਤ ਨਿਸ਼ਾਨਾ_MEM_REF:
      /* MEM_REFs can appear from -fgimple parsing or folding, so allow them
	 here as well.  */
    ਹਾਲਤ ਅਸਿੱਧਾ_REF:
    ਹਾਲਤ ARRAY_REF:
    ਹਾਲਤ VAR_DECL:
    ਹਾਲਤ PARM_DECL:
    ਹਾਲਤ ਨਤੀਜਾ_DECL:
    ਹਾਲਤ ERROR_MARK:
      ਵਾਪਸ (ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (ref)) != FUNCTION_TYPE
	      && ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (ref)) != ਵਿਧੀ_TYPE);

    ਹਾਲਤ BIND_ਵਿਅੰਜਕ:
      ਵਾਪਸ ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (ref)) == ARRAY_TYPE;

    ਹਾਲਤ CALL_ਵਿਅੰਜਕ:
      ਵਾਪਸ is_access_with_ਮਾਪ_p (ref);

    ਮੂਲ:
      ਵਾਪਸ ਝੂਠ;
    }
}

/* Give a warning for storing in something that is read-only in GCC
   terms but not const in ISO C terms.  */

ਸਥਿਰ ਖਾਲੀ
readonly_warning (ਰੁੱਖ arg, ਗਿਣਤੀ lvalue_use use)
{
  ਚੋਣ (use)
    {
    ਹਾਲਤ lv_ਸੌਂਪੋ:
      warning (0, "assignment of read-only location %qE", arg);
      ਰੋਕੋ;
    ਹਾਲਤ lv_increment:
      warning (0, "increment of read-only location %qE", arg);
      ਰੋਕੋ;
    ਹਾਲਤ lv_decrement:
      warning (0, "decrement of read-only location %qE", arg);
      ਰੋਕੋ;
    ਮੂਲ:
      gcc_unreachable ();
    }
  ਵਾਪਸ;
}


/* Return nonzero if REF is an lvalue valid for this language;
   otherwise, print an error message and return zero.  USE says
   how the lvalue is being used and so selects the error message.
   LOCATION is the location at which any error should be reported.  */

ਸਥਿਰ ਪੂਰਨ
lvalue_or_else (location_t loc, const_ਰੁੱਖ ref, ਗਿਣਤੀ lvalue_use use)
{
  ਪੂਰਨ win = lvalue_p (ref);

  ਜੇ (!win)
    lvalue_error (loc, use);

  ਵਾਪਸ win;
}

/* Mark EXP saying that we need to be able to take the
   address of it; it should not be allocated in a register.
   Returns true if successful.  ARRAY_REF_P is true if this
   is for ARRAY_REF construction - in that case we don't want
   to look through VIEW_CONVERT_EXPR from VECTOR_TYPE to ARRAY_TYPE,
   it is fine to use ARRAY_REFs for vector subscripts on vector
   register variables.  If OVERRIDE_REGISTER, clear DECL_REGISTER rather
   than producing an error for taking the address of a register.  */

ਤਾਰਕਿਕ
c_mark_addressable (ਰੁੱਖ ਘਾਤਾਂਕ, ਤਾਰਕਿਕ array_ref_p, ਤਾਰਕਿਕ override_ਰਜਿਸਟਰ)
{
  ਰੁੱਖ x = ਘਾਤਾਂਕ;

  ਜਦੋਂ (1)
    ਚੋਣ (ਰੁੱਖ_ਕੋਡ (x))
      {
      ਹਾਲਤ VIEW_CONVERT_ਵਿਅੰਜਕ:
	ਜੇ (array_ref_p
	    && ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (x)) == ARRAY_TYPE
	    && ਸਦਿਸ਼_TYPE_P (ਰੁੱਖ_TYPE (ਰੁੱਖ_ਸੰਕਾਰਜ (x, 0))))
	  ਵਾਪਸ ਸੱਚ;
	x = ਰੁੱਖ_ਸੰਕਾਰਜ (x, 0);
	ਰੋਕੋ;

      ਹਾਲਤ COMPONENT_REF:
	ਜੇ (DECL_C_ਦੋਆਧਾਰੀ_ਅੰਕ_ਖੇਤਰ (ਰੁੱਖ_ਸੰਕਾਰਜ (x, 1)))
	  {
	    error ("cannot take address of bit-field %qD",
		   ਰੁੱਖ_ਸੰਕਾਰਜ (x, 1));
	    ਵਾਪਸ ਝੂਠ;
	  }
	/* FALLTHRU */
      ਹਾਲਤ ADDR_ਵਿਅੰਜਕ:
      ਹਾਲਤ ARRAY_REF:
      ਹਾਲਤ REALPART_ਵਿਅੰਜਕ:
      ਹਾਲਤ IMAGPART_ਵਿਅੰਜਕ:
	x = ਰੁੱਖ_ਸੰਕਾਰਜ (x, 0);
	ਰੋਕੋ;

      ਹਾਲਤ COMPOUND_LITERAL_ਵਿਅੰਜਕ:
	ਜੇ (C_DECL_ਰਜਿਸਟਰ (COMPOUND_LITERAL_ਵਿਅੰਜਕ_DECL (x)))
	  {
	    ਜੇ (override_ਰਜਿਸਟਰ)
	      DECL_ਰਜਿਸਟਰ (COMPOUND_LITERAL_ਵਿਅੰਜਕ_DECL (x)) = 0;
	    ਨਹੀਂਤਾਂ
	      {
		error ("address of register compound literal requested");
		ਵਾਪਸ ਝੂਠ;
	      }
	  }
	ਰੁੱਖ_ADDRESSABLE (x) = 1;
	ਰੁੱਖ_ADDRESSABLE (COMPOUND_LITERAL_ਵਿਅੰਜਕ_DECL (x)) = 1;
	ਵਾਪਸ ਸੱਚ;

      ਹਾਲਤ CONSTRUCTOR:
	ਰੁੱਖ_ADDRESSABLE (x) = 1;
	ਵਾਪਸ ਸੱਚ;

      ਹਾਲਤ VAR_DECL:
      ਹਾਲਤ CONST_DECL:
      ਹਾਲਤ PARM_DECL:
      ਹਾਲਤ ਨਤੀਜਾ_DECL:
	ਜੇ (C_DECL_ਰਜਿਸਟਰ (x)
	    && DECL_NONLOCAL (x))
	  {
	    ਜੇ (ਰੁੱਖ_ਜਨਤਕ (x) || is_global_var (x))
	      {
		error
		  ("global register variable %qD used in nested function", x);
		ਵਾਪਸ ਝੂਠ;
	      }
	    pedwarn (ਨਿਵੇਸ਼_location, 0, "register variable %qD used in nested function", x);
	  }
	ਨਹੀਂਤਾਂ ਜੇ (C_DECL_ਰਜਿਸਟਰ (x))
	  {
	    ਜੇ (ਰੁੱਖ_ਜਨਤਕ (x) || is_global_var (x))
	      error ("address of global register variable %qD requested", x);
	    ਨਹੀਂਤਾਂ ਜੇ (override_ਰਜਿਸਟਰ && !DECL_HARD_ਰਜਿਸਟਰ (x))
	      {
		DECL_ਰਜਿਸਟਰ (x) = 0;
		ਰੁੱਖ_ADDRESSABLE (x) = 1;
		mark_decl_ਵਰਤਿਆ (x, ਸੱਚ);
		ਵਾਪਸ ਸੱਚ;
	      }
	    ਨਹੀਂਤਾਂ
	      error ("address of register variable %qD requested", x);
	    ਵਾਪਸ ਝੂਠ;
	  }

	/* FALLTHRU */
      ਹਾਲਤ FUNCTION_DECL:
	ਰੁੱਖ_ADDRESSABLE (x) = 1;
	mark_decl_ਵਰਤਿਆ (x, ਸੱਚ);
	/* FALLTHRU */
      ਮੂਲ:
	ਵਾਪਸ ਸੱਚ;
    }
}

/* Convert EXPR to TYPE, warning about conversion problems with
   constants.  SEMANTIC_TYPE is the type this conversion would use
   without excess precision. If SEMANTIC_TYPE is NULL, this function
   is equivalent to convert_and_check. This function is a wrapper that
   handles conversions that may be different than
   the usual ones because of excess precision.  */

ਸਥਿਰ ਰੁੱਖ
ep_convert_and_check (location_t loc, ਰੁੱਖ type, ਰੁੱਖ ਵਿਅੰਜਕ,
		      ਰੁੱਖ semantic_type)
{
  ਜੇ (ਰੁੱਖ_TYPE (ਵਿਅੰਜਕ) == type)
    ਵਾਪਸ ਵਿਅੰਜਕ;

  /* For C11, integer conversions may have results with excess
     precision.  */
  ਜੇ (flag_isoc11 || !semantic_type)
    ਵਾਪਸ convert_and_check (loc, type, ਵਿਅੰਜਕ);

  ਜੇ (ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (ਵਿਅੰਜਕ)) == INTEGER_TYPE
      && ਰੁੱਖ_TYPE (ਵਿਅੰਜਕ) != semantic_type)
    {
      /* For integers, we need to check the real conversion, not
	 the conversion to the excess precision type.  */
      ਵਿਅੰਜਕ = convert_and_check (loc, semantic_type, ਵਿਅੰਜਕ);
    }
  /* Result type is the excess precision type, which should be
     large enough, so do not check.  */
  ਵਾਪਸ convert (type, ਵਿਅੰਜਕ);
}

/* If EXPR refers to a built-in declared without a prototype returns
   the actual type of the built-in and, if non-null, set *BLTIN to
   a pointer to the built-in.  Otherwise return the type of EXPR
   and clear *BLTIN if non-null.  */

ਸਥਿਰ ਰੁੱਖ
type_or_builtin_type (ਰੁੱਖ ਵਿਅੰਜਕ, ਰੁੱਖ *bltin = ਨਿਰਾ)
{
  ਰੁੱਖ dummy;
  ਜੇ (!bltin)
    bltin = &dummy;

  *bltin = NULL_ਰੁੱਖ;

  ਰੁੱਖ type = ਰੁੱਖ_TYPE (ਵਿਅੰਜਕ);
  ਜੇ (ਰੁੱਖ_ਕੋਡ (ਵਿਅੰਜਕ) != ADDR_ਵਿਅੰਜਕ)
    ਵਾਪਸ type;

  ਰੁੱਖ oper = ਰੁੱਖ_ਸੰਕਾਰਜ (ਵਿਅੰਜਕ, 0);
  ਜੇ (!DECL_P (oper)
      || ਰੁੱਖ_ਕੋਡ (oper) != FUNCTION_DECL
      || !fndecl_built_ਵਿੱਚ_p (oper, BUILT_ਵਿੱਚ_ਸਾਧਾਰਨ))
    ਵਾਪਸ type;

  built_ਵਿੱਚ_function ਕੋਡ = DECL_FUNCTION_ਕੋਡ (oper);
  ਜੇ (!C_DECL_BUILTIN_PROTOTYPE (oper))
    ਵਾਪਸ type;

  ਜੇ ((*bltin = builtin_decl_implicit (ਕੋਡ)))
    type = c_build_ਸੂਚਕ_type (ਰੁੱਖ_TYPE (*bltin));

  ਵਾਪਸ type;
}

/* Build and return a conditional expression IFEXP ? OP1 : OP2.  If
   IFEXP_BCP then the condition is a call to __builtin_constant_p, and
   if folded to an integer constant then the unselected half may
   contain arbitrary operations not normally permitted in constant
   expressions.  Set the location of the expression to LOC.  */

ਰੁੱਖ
build_conditional_ਵਿਅੰਜਕ (location_t colon_loc, ਰੁੱਖ ifexp, ਤਾਰਕਿਕ ifexp_bcp,
			ਰੁੱਖ op1, ਰੁੱਖ op1_original_type, location_t op1_loc,
			ਰੁੱਖ op2, ਰੁੱਖ op2_original_type, location_t op2_loc)
{
  ਰੁੱਖ type1;
  ਰੁੱਖ type2;
  ਰੁੱਖ ਨਤੀਜਾ_type = ਨਿਰਾ;
  ਰੁੱਖ semantic_ਨਤੀਜਾ_type = ਨਿਰਾ;
  ਰੁੱਖ orig_op1 = op1, orig_op2 = op2;
  ਤਾਰਕਿਕ int_const, op1_int_operands, op2_int_operands, int_operands;
  ਤਾਰਕਿਕ ifexp_int_operands;
  ਰੁੱਖ ret;

  op1_int_operands = ਵਿਅੰਜਕ_INT_CONST_OPERANDS (orig_op1);
  ਜੇ (op1_int_operands)
    op1 = remove_c_maybe_const_ਵਿਅੰਜਕ (op1);
  op2_int_operands = ਵਿਅੰਜਕ_INT_CONST_OPERANDS (orig_op2);
  ਜੇ (op2_int_operands)
    op2 = remove_c_maybe_const_ਵਿਅੰਜਕ (op2);
  ifexp_int_operands = ਵਿਅੰਜਕ_INT_CONST_OPERANDS (ifexp);
  ਜੇ (ifexp_int_operands)
    ifexp = remove_c_maybe_const_ਵਿਅੰਜਕ (ifexp);

  /* Promote both alternatives.  */

  ਜੇ (ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (op1)) != VOID_TYPE)
    op1 = default_conversion (op1);
  ਜੇ (ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (op2)) != VOID_TYPE)
    op2 = default_conversion (op2);

  ਜੇ (ਰੁੱਖ_ਕੋਡ (ifexp) == ERROR_MARK
      || ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (op1)) == ERROR_MARK
      || ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (op2)) == ERROR_MARK)
    ਵਾਪਸ error_mark_ਗੰਢ;

  ਰੁੱਖ bltin1 = NULL_ਰੁੱਖ;
  ਰੁੱਖ bltin2 = NULL_ਰੁੱਖ;
  type1 = type_or_builtin_type (op1, &bltin1);
  ਅਚਲ ਗਿਣਤੀ ਰੁੱਖ_ਕੋਡ_2 code1 = ਰੁੱਖ_ਕੋਡ (type1);
  type2 = type_or_builtin_type (op2, &bltin2);
  ਅਚਲ ਗਿਣਤੀ ਰੁੱਖ_ਕੋਡ_2 code2 = ਰੁੱਖ_ਕੋਡ (type2);

  ਜੇ (code1 == ਸੂਚਕ_TYPE && reject_gcc_builtin (op1))
    ਵਾਪਸ error_mark_ਗੰਢ;

  ਜੇ (code2 == ਸੂਚਕ_TYPE && reject_gcc_builtin (op2))
    ਵਾਪਸ error_mark_ਗੰਢ;

  /* C90 does not permit non-lvalue arrays in conditional expressions.
     In C99 they will be pointers by now.  */
  ਜੇ (code1 == ARRAY_TYPE || code2 == ARRAY_TYPE)
    {
      error_at (colon_loc, "non-lvalue array in conditional expression");
      ਵਾਪਸ error_mark_ਗੰਢ;
    }

  ਜੇ ((ਰੁੱਖ_ਕੋਡ (op1) == EXCESS_PRECISION_ਵਿਅੰਜਕ
       || ਰੁੱਖ_ਕੋਡ (op2) == EXCESS_PRECISION_ਵਿਅੰਜਕ)
      && (code1 == INTEGER_TYPE || code1 == REAL_TYPE
	  || code1 == COMPLEX_TYPE || code1 == BITINT_TYPE)
      && (code2 == INTEGER_TYPE || code2 == REAL_TYPE
	  || code2 == COMPLEX_TYPE || code2 == BITINT_TYPE))
    {
      semantic_ਨਤੀਜਾ_type = c_common_type (type1, type2);
      ਜੇ (ਰੁੱਖ_ਕੋਡ (op1) == EXCESS_PRECISION_ਵਿਅੰਜਕ)
	{
	  op1 = ਰੁੱਖ_ਸੰਕਾਰਜ (op1, 0);
	  type1 = ਰੁੱਖ_TYPE (op1);
	  gcc_assert (ਰੁੱਖ_ਕੋਡ (type1) == code1);
	}
      ਜੇ (ਰੁੱਖ_ਕੋਡ (op2) == EXCESS_PRECISION_ਵਿਅੰਜਕ)
	{
	  op2 = ਰੁੱਖ_ਸੰਕਾਰਜ (op2, 0);
	  type2 = ਰੁੱਖ_TYPE (op2);
	  gcc_assert (ਰੁੱਖ_ਕੋਡ (type2) == code2);
	}
    }

  ਜੇ (warn_cxx_compat)
    {
      ਰੁੱਖ t1 = op1_original_type ? op1_original_type : ਰੁੱਖ_TYPE (orig_op1);
      ਰੁੱਖ t2 = op2_original_type ? op2_original_type : ਰੁੱਖ_TYPE (orig_op2);

      ਜੇ (ਰੁੱਖ_ਕੋਡ (t1) == ENUMERAL_TYPE
	  && ਰੁੱਖ_ਕੋਡ (t2) == ENUMERAL_TYPE
	  && TYPE_MAIN_VARIANT (t1) != TYPE_MAIN_VARIANT (t2))
	warning_at (colon_loc, OPT_Wc___compat,
		    "different enum types in conditional is "
		    "invalid in C++: %qT vs %qT", t1, t2);
    }

  ਜੇ (warn_zero_as_null_ਸੂਚਕ_constant
      && c_inhibit_evaluation_warnings == 0)
    {
      ਜੇ ((code1 == ਸੂਚਕ_TYPE || code1 == NULLPTR_TYPE)
	  && INTEGRAL_TYPE_P (type2) && null_ਸੂਚਕ_constant_p (orig_op2))
	warning_at (op2_loc, OPT_Wzero_as_null_ਸੂਚਕ_constant,
		    "zero as null pointer constant");

      ਜੇ ((code2 == ਸੂਚਕ_TYPE || code2 == NULLPTR_TYPE)
	  && INTEGRAL_TYPE_P (type1) && null_ਸੂਚਕ_constant_p (orig_op1))
	warning_at (op1_loc, OPT_Wzero_as_null_ਸੂਚਕ_constant,
		    "zero as null pointer constant");
    }

  /* Quickly detect the usual case where op1 and op2 have the same type
     after promotion.  */
  ਜੇ (TYPE_MAIN_VARIANT (type1) == TYPE_MAIN_VARIANT (type2))
    {
      ਜੇ (type1 == type2)
	ਨਤੀਜਾ_type = type1;
      ਨਹੀਂਤਾਂ
	ਨਤੀਜਾ_type = TYPE_MAIN_VARIANT (type1);
    }
  ਨਹੀਂਤਾਂ ਜੇ ((code1 == INTEGER_TYPE || code1 == REAL_TYPE
	    || code1 == COMPLEX_TYPE || code1 == BITINT_TYPE)
	   && (code2 == INTEGER_TYPE || code2 == REAL_TYPE
	       || code2 == COMPLEX_TYPE || code2 == BITINT_TYPE))
    {
      /* In C11, a conditional expression between a floating-point
	 type and an integer type should convert the integer type to
	 the evaluation format of the floating-point type, with
	 possible excess precision.  */
      ਰੁੱਖ eptype1 = type1;
      ਰੁੱਖ eptype2 = type2;
      ਜੇ (flag_isoc11)
	{
	  ਰੁੱਖ eptype;
	  ਜੇ (ANY_INTEGRAL_TYPE_P (type1)
	      && (eptype = excess_precision_type (type2)) != NULL_ਰੁੱਖ)
	    {
	      eptype2 = eptype;
	      ਜੇ (!semantic_ਨਤੀਜਾ_type)
		semantic_ਨਤੀਜਾ_type = c_common_type (type1, type2);
	    }
	  ਨਹੀਂਤਾਂ ਜੇ (ANY_INTEGRAL_TYPE_P (type2)
		   && (eptype = excess_precision_type (type1)) != NULL_ਰੁੱਖ)
	    {
	      eptype1 = eptype;
	      ਜੇ (!semantic_ਨਤੀਜਾ_type)
		semantic_ਨਤੀਜਾ_type = c_common_type (type1, type2);
	    }
	}
      ਨਤੀਜਾ_type = c_common_type (eptype1, eptype2);
      ਜੇ (ਨਤੀਜਾ_type == error_mark_ਗੰਢ)
	ਵਾਪਸ error_mark_ਗੰਢ;
      do_warn_double_promotion (ਨਤੀਜਾ_type, type1, type2,
				"implicit conversion from %qT to %qT to "
				"match other result of conditional",
				colon_loc);

      /* If -Wsign-compare, warn here if type1 and type2 have
	 different signedness.  We'll promote the signed to unsigned
	 and later code won't know it used to be different.
	 Do this check on the original types, so that explicit casts
	 will be considered, but default promotions won't.  */
      ਜੇ (c_inhibit_evaluation_warnings == 0)
	{
	  ਪੂਰਨ unsigned_op1 = TYPE_UNSIGNED (ਰੁੱਖ_TYPE (orig_op1));
	  ਪੂਰਨ unsigned_op2 = TYPE_UNSIGNED (ਰੁੱਖ_TYPE (orig_op2));

	  ਜੇ (unsigned_op1 ^ unsigned_op2)
	    {
	      /* Do not warn if the result type is signed, since the
		 signed type will only be chosen if it can represent
		 all the values of the unsigned type.  */
	      ਜੇ (!TYPE_UNSIGNED (ਨਤੀਜਾ_type))
		/* OK */;
	      ਨਹੀਂਤਾਂ
		{
		  ਤਾਰਕਿਕ op1_maybe_const = ਸੱਚ;
		  ਤਾਰਕਿਕ op2_maybe_const = ਸੱਚ;

		  /* Do not warn if the signed quantity is an
		     unsuffixed integer literal (or some static
		     constant expression involving such literals) and
		     it is non-negative.  This warning requires the
		     operands to be folded for best results, so do
		     that folding in this case even without
		     warn_sign_compare to avoid warning options
		     possibly affecting code generation.  */
		  c_inhibit_evaluation_warnings
		    += (ifexp == truthvalue_false_ਗੰਢ);
		  op1 = c_fully_fold (op1, require_constant_ਮੁੱਲ,
				      &op1_maybe_const);
		  c_inhibit_evaluation_warnings
		    -= (ifexp == truthvalue_false_ਗੰਢ);

		  c_inhibit_evaluation_warnings
		    += (ifexp == truthvalue_true_ਗੰਢ);
		  op2 = c_fully_fold (op2, require_constant_ਮੁੱਲ,
				      &op2_maybe_const);
		  c_inhibit_evaluation_warnings
		    -= (ifexp == truthvalue_true_ਗੰਢ);

		  ਜੇ (warn_sign_compare)
		    {
		      ਜੇ ((unsigned_op2
			   && ਰੁੱਖ_ਵਿਅੰਜਕ_nonnegative_p (op1))
			  || (unsigned_op1
			      && ਰੁੱਖ_ਵਿਅੰਜਕ_nonnegative_p (op2)))
			/* OK */;
		      ਨਹੀਂਤਾਂ ਜੇ (unsigned_op2)
			warning_at (op1_loc, OPT_Wsign_compare,
				    "operand of %<?:%> changes signedness from "
				    "%qT to %qT due to unsignedness of other "
				    "operand", ਰੁੱਖ_TYPE (orig_op1),
				    ਰੁੱਖ_TYPE (orig_op2));
		      ਨਹੀਂਤਾਂ
			warning_at (op2_loc, OPT_Wsign_compare,
				    "operand of %<?:%> changes signedness from "
				    "%qT to %qT due to unsignedness of other "
				    "operand", ਰੁੱਖ_TYPE (orig_op2),
				    ਰੁੱਖ_TYPE (orig_op1));
		    }
		  ਜੇ (!op1_maybe_const || ਰੁੱਖ_ਕੋਡ (op1) != INTEGER_CST)
		    op1 = c_wrap_maybe_const (op1, !op1_maybe_const);
		  ਜੇ (!op2_maybe_const || ਰੁੱਖ_ਕੋਡ (op2) != INTEGER_CST)
		    op2 = c_wrap_maybe_const (op2, !op2_maybe_const);
		}
	    }
	}
    }
  ਨਹੀਂਤਾਂ ਜੇ (code1 == VOID_TYPE || code2 == VOID_TYPE)
    {
      ਜੇ (code1 != VOID_TYPE || code2 != VOID_TYPE)
	pedwarn (colon_loc, OPT_Wpedantic,
		 "ISO C forbids conditional expr with only one void side");
      ਨਤੀਜਾ_type = void_type_ਗੰਢ;
    }
  ਨਹੀਂਤਾਂ ਜੇ (code1 == ਸੂਚਕ_TYPE && code2 == ਸੂਚਕ_TYPE)
    {
      addr_space_t as1 = TYPE_ADDR_SPACE (ਰੁੱਖ_TYPE (type1));
      addr_space_t as2 = TYPE_ADDR_SPACE (ਰੁੱਖ_TYPE (type2));
      addr_space_t as_common;

      ਜੇ (comp_ਨਿਸ਼ਾਨਾ_types (colon_loc, type1, type2))
	{
	  ifexp = save_ਵਿਅੰਜਕ (ifexp);
	  ਨਤੀਜਾ_type = common_ਸੂਚਕ_type (type1, type2, ifexp);
	}
      ਨਹੀਂਤਾਂ ਜੇ (null_ਸੂਚਕ_constant_p (orig_op1))
	ਨਤੀਜਾ_type = type2;
      ਨਹੀਂਤਾਂ ਜੇ (null_ਸੂਚਕ_constant_p (orig_op2))
	ਨਤੀਜਾ_type = type1;
      ਨਹੀਂਤਾਂ ਜੇ (!addr_space_superset (as1, as2, &as_common))
	{
	  error_at (colon_loc, "pointers to disjoint address spaces "
		    "used in conditional expression");
	  ਵਾਪਸ error_mark_ਗੰਢ;
	}
      ਨਹੀਂਤਾਂ ਜੇ ((VOID_TYPE_P (ਰੁੱਖ_TYPE (type1))
		&& !TYPE_ATOMIC (ਰੁੱਖ_TYPE (type1)))
	       || (VOID_TYPE_P (ਰੁੱਖ_TYPE (type2))
		   && !TYPE_ATOMIC (ਰੁੱਖ_TYPE (type2))))
	{
	  ਰੁੱਖ t1 = ਰੁੱਖ_TYPE (type1);
	  ਰੁੱਖ t2 = ਰੁੱਖ_TYPE (type2);
	  ਜੇ (!(VOID_TYPE_P (t1)
		&& !TYPE_ATOMIC (t1)))
	   {
	     /* roles are swapped */
	     t1 = t2;
	     t2 = ਰੁੱਖ_TYPE (type1);
	   }
	  ਰੁੱਖ t2_stripped = strip_array_types (t2);
	  ਜੇ ((ਰੁੱਖ_ਕੋਡ (t2) == ARRAY_TYPE)
	      && (TYPE_QUALS (t2_stripped) & ~TYPE_QUALS (t1)))
	    {
	      ਜੇ (!flag_isoc23)
		warning_at (colon_loc, OPT_Wdiscarded_array_qualifiers,
			    "pointer to array loses qualifier "
			    "in conditional expression");
	      ਨਹੀਂਤਾਂ ਜੇ (warn_c11_c23_compat > 0)
		warning_at (colon_loc, OPT_Wc11_c23_compat,
			    "pointer to array loses qualifier "
			    "in conditional expression in ISO C before C23");
	    }
	  ਜੇ (ਰੁੱਖ_ਕੋਡ (t2) == FUNCTION_TYPE)
	    pedwarn (colon_loc, OPT_Wpedantic,
		     "ISO C forbids conditional expr between "
		     "%<void *%> and function pointer");
	  /* for array, use qualifiers of element type */
	  ਜੇ (flag_isoc23)
	    t2 = t2_stripped;
	  ਨਤੀਜਾ_type = c_build_ਸੂਚਕ_type (qualify_type (t1, t2));
	}
      /* Objective-C pointer comparisons are a bit more lenient.  */
      ਨਹੀਂਤਾਂ ਜੇ (objc_have_common_type (type1, type2, -3, NULL_ਰੁੱਖ))
	ਨਤੀਜਾ_type = objc_common_type (type1, type2);
      ਨਹੀਂਤਾਂ
	{
	  ਪੂਰਨ qual = ENCODE_QUAL_ADDR_SPACE (as_common);
	  ਗਿਣਤੀ diagnostics::ਕਿਸਮ ਕਿਸਮ = diagnostics::ਕਿਸਮ::permerror;
	  ਜੇ (!flag_isoc99)
	    /* This downgrade to a warning ensures that -std=gnu89
	       -pedantic-errors does not flag these mismatches between
	       builtins as errors (as diagnostics::kind::permerror would)
	       ISO C99 and later do not have implicit function declarations,
	       so the mismatch cannot occur naturally there.  */
	    ਕਿਸਮ = (bltin1 && bltin2
		    ? diagnostics::ਕਿਸਮ::warning
		    : diagnostics::ਕਿਸਮ::pedwarn);
	  ਜੇ (emit_diagnostic (ਕਿਸਮ, colon_loc, OPT_Wincompatible_ਸੂਚਕ_types,
			       "pointer type mismatch "
			       "in conditional expression"))
	    {
	      inform (op1_loc, "first expression has type %qT", type1);
	      inform (op2_loc, "second expression has type %qT", type2);
	    }
	  ਨਤੀਜਾ_type = c_build_ਸੂਚਕ_type
			  (c_build_qualified_type (void_type_ਗੰਢ, qual));
	}
    }
  ਨਹੀਂਤਾਂ ਜੇ (code1 == ਸੂਚਕ_TYPE
	   && (code2 == INTEGER_TYPE || code2 == BITINT_TYPE))
    {
      ਜੇ (!null_ਸੂਚਕ_constant_p (orig_op2))
	permerror_opt (colon_loc, OPT_Wint_conversion,
		       "pointer/integer type mismatch "
		       "in conditional expression");
      ਨਹੀਂਤਾਂ
	{
	  op2 = null_ਸੂਚਕ_ਗੰਢ;
	}
      ਨਤੀਜਾ_type = type1;
    }
  ਨਹੀਂਤਾਂ ਜੇ (code2 == ਸੂਚਕ_TYPE
	   && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
    {
      ਜੇ (!null_ਸੂਚਕ_constant_p (orig_op1))
	permerror_opt (colon_loc, OPT_Wint_conversion,
		       "pointer/integer type mismatch "
		       "in conditional expression");
      ਨਹੀਂਤਾਂ
	{
	  op1 = null_ਸੂਚਕ_ਗੰਢ;
	}
      ਨਤੀਜਾ_type = type2;
    }
  /* 6.5.15: "if one is a null pointer constant (other than a pointer) or has
     type nullptr_t and the other is a pointer, the result type is the pointer
     type."  */
  ਨਹੀਂਤਾਂ ਜੇ (code1 == NULLPTR_TYPE && code2 == ਸੂਚਕ_TYPE)
    ਨਤੀਜਾ_type = type2;
  ਨਹੀਂਤਾਂ ਜੇ (code1 == ਸੂਚਕ_TYPE && code2 == NULLPTR_TYPE)
    ਨਤੀਜਾ_type = type1;
  ਨਹੀਂਤਾਂ ਜੇ (ਰਿਕਾਰਡ_OR_UNION_TYPE_P (type1) && ਰਿਕਾਰਡ_OR_UNION_TYPE_P (type2)
	   && comptypes (TYPE_MAIN_VARIANT (type1),
			 TYPE_MAIN_VARIANT (type2)))
    ਨਤੀਜਾ_type = ਸੰਯੁਕਤ_type (TYPE_MAIN_VARIANT (type1),
				  TYPE_MAIN_VARIANT (type2));

  ਜੇ (!ਨਤੀਜਾ_type)
    {
      ਜੇ (flag_cond_mismatch)
	ਨਤੀਜਾ_type = void_type_ਗੰਢ;
      ਨਹੀਂਤਾਂ
	{
	  error_at (colon_loc, "type mismatch in conditional expression");
	  ਵਾਪਸ error_mark_ਗੰਢ;
	}
    }

  /* Merge const and volatile flags of the incoming types.  */
  ਨਤੀਜਾ_type
    = build_type_variant (ਨਤੀਜਾ_type,
			  TYPE_READONLY (type1) || TYPE_READONLY (type2),
			  TYPE_VOLATILE (type1) || TYPE_VOLATILE (type2));

  op1 = ep_convert_and_check (colon_loc, ਨਤੀਜਾ_type, op1,
			      semantic_ਨਤੀਜਾ_type);
  op2 = ep_convert_and_check (colon_loc, ਨਤੀਜਾ_type, op2,
			      semantic_ਨਤੀਜਾ_type);

  ਜੇ (ifexp_bcp && ifexp == truthvalue_true_ਗੰਢ)
    {
      op2_int_operands = ਸੱਚ;
      op1 = c_fully_fold (op1, require_constant_ਮੁੱਲ, ਨਿਰਾ);
    }
  ਜੇ (ifexp_bcp && ifexp == truthvalue_false_ਗੰਢ)
    {
      op1_int_operands = ਸੱਚ;
      op2 = c_fully_fold (op2, require_constant_ਮੁੱਲ, ਨਿਰਾ);
    }
  int_const = int_operands = (ifexp_int_operands
			      && op1_int_operands
			      && op2_int_operands);
  ਜੇ (int_operands)
    {
      int_const = ((ifexp == truthvalue_true_ਗੰਢ
		    && ਰੁੱਖ_ਕੋਡ (orig_op1) == INTEGER_CST
		    && !ਰੁੱਖ_ਉਛਾਲ (orig_op1))
		   || (ifexp == truthvalue_false_ਗੰਢ
		       && ਰੁੱਖ_ਕੋਡ (orig_op2) == INTEGER_CST
		       && !ਰੁੱਖ_ਉਛਾਲ (orig_op2)));
    }

  /* Need to convert condition operand into a vector mask.  */
  ਜੇ (ਸਦਿਸ਼_TYPE_P (ਰੁੱਖ_TYPE (ifexp)))
    {
      ਰੁੱਖ vectype = ਰੁੱਖ_TYPE (ifexp);
      ਰੁੱਖ elem_type = ਰੁੱਖ_TYPE (vectype);
      ਰੁੱਖ zero = build_int_cst (elem_type, 0);
      ਰੁੱਖ zero_vec = build_ਸਦਿਸ਼_from_val (vectype, zero);
      ਰੁੱਖ cmp_type = truth_type_for (vectype);
      ifexp = build2 (NE_ਵਿਅੰਜਕ, cmp_type, ifexp, zero_vec);
    }

  ਜੇ (int_const || (ifexp_bcp && ਰੁੱਖ_ਕੋਡ (ifexp) == INTEGER_CST))
    ret = fold_build3_loc (colon_loc, COND_ਵਿਅੰਜਕ, ਨਤੀਜਾ_type, ifexp, op1, op2);
  ਨਹੀਂਤਾਂ
    {
      ਜੇ (int_operands)
	{
	  /* Use c_fully_fold here, since C_MAYBE_CONST_EXPR might be
	     nested inside of the expression.  */
	  op1 = c_fully_fold (op1, ਝੂਠ, ਨਿਰਾ);
	  op2 = c_fully_fold (op2, ਝੂਠ, ਨਿਰਾ);
	}
      ret = build3 (COND_ਵਿਅੰਜਕ, ਨਤੀਜਾ_type, ifexp, op1, op2);
      ਜੇ (int_operands)
	ret = note_integer_operands (ret);
    }
  ਜੇ (semantic_ਨਤੀਜਾ_type)
    ret = build1 (EXCESS_PRECISION_ਵਿਅੰਜਕ, semantic_ਨਤੀਜਾ_type, ret);

  protected_ਸੈੱਟ_ਵਿਅੰਜਕ_location (ret, colon_loc);

  /* If the OP1 and OP2 are the same and don't have side-effects,
     warn here, because the COND_EXPR will be turned into OP1.  */
  ਜੇ (warn_duplicated_branches
      && ਰੁੱਖ_ਕੋਡ (ret) == COND_ਵਿਅੰਜਕ
      && (op1 == op2 || ਸੰਕਾਰਜ_equal_p (op1, op2, OEP_ਪਤਾ_ਦਾ_SAME_ਖੇਤਰ)))
    warning_at (ਵਿਅੰਜਕ_LOCATION (ret), OPT_Wduplicated_branches,
		"this condition has identical branches");

  ਵਾਪਸ ret;
}

/* EXPR is an expression, location LOC, whose result is discarded.
   Warn if it is a call to a nodiscard function (or a COMPOUND_EXPR
   whose right-hand operand is such a call, possibly recursively).  */

ਸਥਿਰ ਖਾਲੀ
maybe_warn_nodiscard (location_t loc, ਰੁੱਖ ਵਿਅੰਜਕ)
{
  ਜੇ (VOID_TYPE_P (ਰੁੱਖ_TYPE (ਵਿਅੰਜਕ)))
    ਵਾਪਸ;
  ਜਦੋਂ (ਰੁੱਖ_ਕੋਡ (ਵਿਅੰਜਕ) == COMPOUND_ਵਿਅੰਜਕ)
    {
      ਵਿਅੰਜਕ = ਰੁੱਖ_ਸੰਕਾਰਜ (ਵਿਅੰਜਕ, 1);
      ਜੇ (ਵਿਅੰਜਕ_HAS_LOCATION (ਵਿਅੰਜਕ))
	loc = ਵਿਅੰਜਕ_LOCATION (ਵਿਅੰਜਕ);
    }
  ਜੇ (ਰੁੱਖ_ਕੋਡ (ਵਿਅੰਜਕ) != CALL_ਵਿਅੰਜਕ)
    ਵਾਪਸ;
  ਰੁੱਖ fn = CALL_ਵਿਅੰਜਕ_FN (ਵਿਅੰਜਕ);
  ਜੇ (!fn)
    ਵਾਪਸ;
  ਰੁੱਖ attr;
  ਜੇ (ਰੁੱਖ_ਕੋਡ (fn) == ADDR_ਵਿਅੰਜਕ
      && ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_ਸੰਕਾਰਜ (fn, 0)) == FUNCTION_DECL
      && (attr = lookup_attribute ("nodiscard",
				   DECL_ਗੁਣ (ਰੁੱਖ_ਸੰਕਾਰਜ (fn, 0)))))
    {
      fn = ਰੁੱਖ_ਸੰਕਾਰਜ (fn, 0);
      ਰੁੱਖ ਦਲੀਲਾਂ = ਰੁੱਖ_ਮੁੱਲ (attr);
      ਜੇ (ਦਲੀਲਾਂ)
	ਦਲੀਲਾਂ = ਰੁੱਖ_ਮੁੱਲ (ਦਲੀਲਾਂ);
      auto_diagnostic_ਸਮੂਹ d;
      auto_urlify_ਗੁਣ sentinel;
      ਪੂਰਨ warned;
      ਜੇ (ਦਲੀਲਾਂ)
	warned = warning_at (loc, OPT_Wunused_ਨਤੀਜਾ,
			     "ignoring return value of %qD, declared with "
			     "attribute %<nodiscard%>: %E", fn, ਦਲੀਲਾਂ);
      ਨਹੀਂਤਾਂ
	warned = warning_at (loc, OPT_Wunused_ਨਤੀਜਾ,
			     "ignoring return value of %qD, declared with "
			     "attribute %<nodiscard%>", fn);
      ਜੇ (warned)
	inform (DECL_ਸਰੋਤ_LOCATION (fn), "declared here");
    }
  ਨਹੀਂਤਾਂ
    {
      ਰੁੱਖ rettype = ਰੁੱਖ_TYPE (ਰੁੱਖ_TYPE (ਰੁੱਖ_TYPE (fn)));
      attr = lookup_attribute ("nodiscard", TYPE_ਗੁਣ (rettype));
      ਜੇ (!attr)
	ਵਾਪਸ;
      ਰੁੱਖ ਦਲੀਲਾਂ = ਰੁੱਖ_ਮੁੱਲ (attr);
      ਜੇ (ਦਲੀਲਾਂ)
	ਦਲੀਲਾਂ = ਰੁੱਖ_ਮੁੱਲ (ਦਲੀਲਾਂ);
      auto_diagnostic_ਸਮੂਹ d;
      auto_urlify_ਗੁਣ sentinel;
      ਪੂਰਨ warned;
      ਜੇ (ਦਲੀਲਾਂ)
	warned = warning_at (loc, OPT_Wunused_ਨਤੀਜਾ,
			     "ignoring return value of type %qT, declared "
			     "with attribute %<nodiscard%>: %E",
			     rettype, ਦਲੀਲਾਂ);
      ਨਹੀਂਤਾਂ
	warned = warning_at (loc, OPT_Wunused_ਨਤੀਜਾ,
			     "ignoring return value of type %qT, declared "
			     "with attribute %<nodiscard%>", rettype);
      ਜੇ (warned)
	{
	  ਜੇ (ਰੁੱਖ_ਕੋਡ (fn) == ADDR_ਵਿਅੰਜਕ)
	    {
	      fn = ਰੁੱਖ_ਸੰਕਾਰਜ (fn, 0);
	      ਜੇ (ਰੁੱਖ_ਕੋਡ (fn) == FUNCTION_DECL)
		inform (DECL_ਸਰੋਤ_LOCATION (fn),
			"in call to %qD, declared here", fn);
	    }
	}
    }
}

/* Return a compound expression that performs two expressions and
   returns the value of the second of them.

   LOC is the location of the COMPOUND_EXPR.  */

ਰੁੱਖ
build_compound_ਵਿਅੰਜਕ (location_t loc, ਰੁੱਖ expr1, ਰੁੱਖ expr2)
{
  ਤਾਰਕਿਕ expr1_int_operands, expr2_int_operands;
  ਰੁੱਖ eptype = NULL_ਰੁੱਖ;
  ਰੁੱਖ ret;

  expr1_int_operands = ਵਿਅੰਜਕ_INT_CONST_OPERANDS (expr1);
  ਜੇ (expr1_int_operands)
    expr1 = remove_c_maybe_const_ਵਿਅੰਜਕ (expr1);
  expr2_int_operands = ਵਿਅੰਜਕ_INT_CONST_OPERANDS (expr2);
  ਜੇ (expr2_int_operands)
    expr2 = remove_c_maybe_const_ਵਿਅੰਜਕ (expr2);

  ਜੇ (ਰੁੱਖ_ਕੋਡ (expr1) == EXCESS_PRECISION_ਵਿਅੰਜਕ)
    expr1 = ਰੁੱਖ_ਸੰਕਾਰਜ (expr1, 0);
  ਜੇ (ਰੁੱਖ_ਕੋਡ (expr2) == EXCESS_PRECISION_ਵਿਅੰਜਕ)
    {
      eptype = ਰੁੱਖ_TYPE (expr2);
      expr2 = ਰੁੱਖ_ਸੰਕਾਰਜ (expr2, 0);
    }

  ਜੇ (!ਰੁੱਖ_SIDE_EFFECTS (expr1))
    {
      /* The left-hand operand of a comma expression is like an expression
	 statement: with -Wunused, we should warn if it doesn't have
	 any side-effects, unless it was explicitly cast to (void).  */
      ਜੇ (warn_ਅਣਵਰਤਿਆ_ਮੁੱਲ)
	{
	  ਜੇ (VOID_TYPE_P (ਰੁੱਖ_TYPE (expr1))
	      && CONVERT_ਵਿਅੰਜਕ_P (expr1))
	    ; /* (void) a, b */
	  ਨਹੀਂਤਾਂ ਜੇ (VOID_TYPE_P (ਰੁੱਖ_TYPE (expr1))
		   && ਰੁੱਖ_ਕੋਡ (expr1) == COMPOUND_ਵਿਅੰਜਕ
		   && CONVERT_ਵਿਅੰਜਕ_P (ਰੁੱਖ_ਸੰਕਾਰਜ (expr1, 1)))
	    ; /* (void) a, (void) b, c */
	  ਨਹੀਂਤਾਂ
	    warning_at (loc, OPT_Wunused_ਮੁੱਲ,
			"left-hand operand of comma expression has no effect");
	}
    }
  ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਕੋਡ (expr1) == COMPOUND_ਵਿਅੰਜਕ
	   && warn_ਅਣਵਰਤਿਆ_ਮੁੱਲ)
    {
      ਰੁੱਖ r = expr1;
      location_t cloc = loc;
      ਜਦੋਂ (ਰੁੱਖ_ਕੋਡ (r) == COMPOUND_ਵਿਅੰਜਕ)
        {
	  ਜੇ (ਵਿਅੰਜਕ_HAS_LOCATION (r))
	    cloc = ਵਿਅੰਜਕ_LOCATION (r);
	  r = ਰੁੱਖ_ਸੰਕਾਰਜ (r, 1);
	}
      ਜੇ (!ਰੁੱਖ_SIDE_EFFECTS (r)
	  && !VOID_TYPE_P (ਰੁੱਖ_TYPE (r))
	  && !CONVERT_ਵਿਅੰਜਕ_P (r))
	warning_at (cloc, OPT_Wunused_ਮੁੱਲ,
	            "right-hand operand of comma expression has no effect");
    }

  /* With -Wunused, we should also warn if the left-hand operand does have
     side-effects, but computes a value which is not used.  For example, in
     `foo() + bar(), baz()' the result of the `+' operator is not used,
     so we should issue a warning.  */
  ਨਹੀਂਤਾਂ ਜੇ (warn_ਅਣਵਰਤਿਆ_ਮੁੱਲ)
    warn_if_ਅਣਵਰਤਿਆ_ਮੁੱਲ (expr1, loc);

  maybe_warn_nodiscard (loc, expr1);

  ਜੇ (expr2 == error_mark_ਗੰਢ)
    ਵਾਪਸ error_mark_ਗੰਢ;

  ret = build2 (COMPOUND_ਵਿਅੰਜਕ, ਰੁੱਖ_TYPE (expr2), expr1, expr2);

  ਜੇ (flag_isoc99
      && expr1_int_operands
      && expr2_int_operands)
    ret = note_integer_operands (ret);

  ਜੇ (eptype)
    ret = build1 (EXCESS_PRECISION_ਵਿਅੰਜਕ, eptype, ret);

  protected_ਸੈੱਟ_ਵਿਅੰਜਕ_location (ret, loc);
  ਵਾਪਸ ret;
}

/* Issue -Wcast-qual warnings when appropriate.  TYPE is the type to
   which we are casting.  OTYPE is the type of the expression being
   cast.  Both TYPE and OTYPE are pointer types.  LOC is the location
   of the cast.  -Wcast-qual appeared on the command line.  Named
   address space qualifiers are not handled here, because they result
   in different warnings.  */

ਸਥਿਰ ਖਾਲੀ
handle_warn_cast_qual (location_t loc, ਰੁੱਖ type, ਰੁੱਖ otype)
{
  ਰੁੱਖ ਵਿੱਚ_type = type;
  ਰੁੱਖ ਵਿੱਚ_otype = otype;
  ਪੂਰਨ added = 0;
  ਪੂਰਨ discarded = 0;
  ਤਾਰਕਿਕ is_const;

  /* Check that the qualifiers on IN_TYPE are a superset of the
     qualifiers of IN_OTYPE.  The outermost level of POINTER_TYPE
     nodes is uninteresting and we stop as soon as we hit a
     non-POINTER_TYPE node on either type.  */
  ਕਰੋ
    {
      ਵਿੱਚ_otype = ਰੁੱਖ_TYPE (ਵਿੱਚ_otype);
      ਵਿੱਚ_type = ਰੁੱਖ_TYPE (ਵਿੱਚ_type);

      /* GNU C allows cv-qualified function types.  'const' means the
	 function is very pure, 'volatile' means it can't return.  We
	 need to warn when such qualifiers are added, not when they're
	 taken away.  */
      ਜੇ (ਰੁੱਖ_ਕੋਡ (ਵਿੱਚ_otype) == FUNCTION_TYPE
	  && ਰੁੱਖ_ਕੋਡ (ਵਿੱਚ_type) == FUNCTION_TYPE)
	added |= (TYPE_QUALS_NO_ADDR_SPACE (ਵਿੱਚ_type)
		  & ~TYPE_QUALS_NO_ADDR_SPACE (ਵਿੱਚ_otype));
      ਨਹੀਂਤਾਂ
	discarded |= (TYPE_QUALS_NO_ADDR_SPACE (ਵਿੱਚ_otype)
		      & ~TYPE_QUALS_NO_ADDR_SPACE (ਵਿੱਚ_type));
    }
  ਜਦੋਂ (ਰੁੱਖ_ਕੋਡ (ਵਿੱਚ_type) == ਸੂਚਕ_TYPE
	 && ਰੁੱਖ_ਕੋਡ (ਵਿੱਚ_otype) == ਸੂਚਕ_TYPE);

  ਜੇ (added)
    warning_at (loc, OPT_Wcast_qual,
		"cast adds %q#v qualifier to function type", added);

  ਜੇ (discarded)
    /* There are qualifiers present in IN_OTYPE that are not present
       in IN_TYPE.  */
    warning_at (loc, OPT_Wcast_qual,
		"cast discards %qv qualifier from pointer target type",
		discarded);

  ਜੇ (added || discarded)
    ਵਾਪਸ;

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

  ਜੇ (TYPE_MAIN_VARIANT (ਵਿੱਚ_type) != TYPE_MAIN_VARIANT (ਵਿੱਚ_otype))
    ਵਾਪਸ;
  ਜੇ (ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (type)) != ਸੂਚਕ_TYPE)
    ਵਾਪਸ;

  ਵਿੱਚ_type = type;
  ਵਿੱਚ_otype = otype;
  is_const = TYPE_READONLY (ਰੁੱਖ_TYPE (ਵਿੱਚ_type));
  ਕਰੋ
    {
      ਵਿੱਚ_type = ਰੁੱਖ_TYPE (ਵਿੱਚ_type);
      ਵਿੱਚ_otype = ਰੁੱਖ_TYPE (ਵਿੱਚ_otype);
      ਜੇ ((TYPE_QUALS (ਵਿੱਚ_type) &~ TYPE_QUALS (ਵਿੱਚ_otype)) != 0
	  && !is_const)
	{
	  warning_at (loc, OPT_Wcast_qual,
		      "to be safe all intermediate pointers in cast from "
                      "%qT to %qT must be %<const%> qualified",
		      otype, type);
	  ਰੋਕੋ;
	}
      ਜੇ (is_const)
	is_const = TYPE_READONLY (ਵਿੱਚ_type);
    }
  ਜਦੋਂ (ਰੁੱਖ_ਕੋਡ (ਵਿੱਚ_type) == ਸੂਚਕ_TYPE);
}

/* Heuristic check if two parameter types can be considered ABI-equivalent.  */

ਸਥਿਰ ਤਾਰਕਿਕ
c_ਸੁਰੱਖਿਅਤ_arg_type_equiv_p (ਰੁੱਖ t1, ਰੁੱਖ t2)
{
  ਜੇ (error_ਸੰਕਾਰਜ_p (t1) || error_ਸੰਕਾਰਜ_p (t2))
    ਵਾਪਸ ਸੱਚ;

  t1 = TYPE_MAIN_VARIANT (t1);
  t2 = TYPE_MAIN_VARIANT (t2);

  ਜੇ (ਰੁੱਖ_ਕੋਡ (t1) == ਸੂਚਕ_TYPE
      && ਰੁੱਖ_ਕੋਡ (t2) == ਸੂਚਕ_TYPE)
    ਵਾਪਸ ਸੱਚ;

  /* Only the precision of the parameter matters.  This check should
     make sure that the callee does not see undefined values in argument
     registers.  */
  ਜੇ (INTEGRAL_TYPE_P (t1)
      && INTEGRAL_TYPE_P (t2)
      && TYPE_PRECISION (t1) == TYPE_PRECISION (t2))
    ਵਾਪਸ ਸੱਚ;

  ਵਾਪਸ comptypes (t1, t2);
}

/* Check if a type cast between two function types can be considered safe.  */

ਸਥਿਰ ਤਾਰਕਿਕ
c_ਸੁਰੱਖਿਅਤ_function_type_cast_p (ਰੁੱਖ t1, ਰੁੱਖ t2)
{
  ਜੇ (ਰੁੱਖ_TYPE (t1) == void_type_ਗੰਢ &&
      TYPE_ARG_TYPES (t1) == void_list_ਗੰਢ)
    ਵਾਪਸ ਸੱਚ;

  ਜੇ (ਰੁੱਖ_TYPE (t2) == void_type_ਗੰਢ &&
      TYPE_ARG_TYPES (t2) == void_list_ਗੰਢ)
    ਵਾਪਸ ਸੱਚ;

  ਜੇ (!c_ਸੁਰੱਖਿਅਤ_arg_type_equiv_p (ਰੁੱਖ_TYPE (t1), ਰੁੱਖ_TYPE (t2)))
    ਵਾਪਸ ਝੂਠ;

  ਲਈ (t1 = TYPE_ARG_TYPES (t1), t2 = TYPE_ARG_TYPES (t2);
       t1 && t2;
       t1 = ਰੁੱਖ_CHAIN (t1), t2 = ਰੁੱਖ_CHAIN (t2))
    ਜੇ (!c_ਸੁਰੱਖਿਅਤ_arg_type_equiv_p (ਰੁੱਖ_ਮੁੱਲ (t1), ਰੁੱਖ_ਮੁੱਲ (t2)))
      ਵਾਪਸ ਝੂਠ;

  ਵਾਪਸ ਸੱਚ;
}

/* Build an expression representing a cast to type TYPE of expression EXPR.
   LOC is the location of the cast-- typically the open paren of the cast.  */

ਰੁੱਖ
build_c_cast (location_t loc, ਰੁੱਖ type, ਰੁੱਖ ਵਿਅੰਜਕ)
{
  ਰੁੱਖ ਮੁੱਲ;

  ਤਾਰਕਿਕ int_operands = ਵਿਅੰਜਕ_INT_CONST_OPERANDS (ਵਿਅੰਜਕ);

  ਜੇ (ਰੁੱਖ_ਕੋਡ (ਵਿਅੰਜਕ) == EXCESS_PRECISION_ਵਿਅੰਜਕ)
    ਵਿਅੰਜਕ = ਰੁੱਖ_ਸੰਕਾਰਜ (ਵਿਅੰਜਕ, 0);

  ਮੁੱਲ = ਵਿਅੰਜਕ;
  ਜੇ (int_operands)
    ਮੁੱਲ = remove_c_maybe_const_ਵਿਅੰਜਕ (ਮੁੱਲ);

  ਜੇ (type == error_mark_ਗੰਢ || ਵਿਅੰਜਕ == error_mark_ਗੰਢ)
    ਵਾਪਸ error_mark_ਗੰਢ;

  /* The ObjC front-end uses TYPE_MAIN_VARIANT to tie together types differing
     only in <protocol> qualifications.  But when constructing cast expressions,
     the protocols do matter and must be kept around.  */
  ਜੇ (objc_is_object_ptr (type) && objc_is_object_ptr (ਰੁੱਖ_TYPE (ਵਿਅੰਜਕ)))
    ਵਾਪਸ build1 (NOP_ਵਿਅੰਜਕ, type, ਵਿਅੰਜਕ);

  type = TYPE_MAIN_VARIANT (type);

  ਜੇ (ਰੁੱਖ_ਕੋਡ (type) == ARRAY_TYPE)
    {
      error_at (loc, "cast specifies array type");
      ਵਾਪਸ error_mark_ਗੰਢ;
    }

  ਜੇ (ਰੁੱਖ_ਕੋਡ (type) == FUNCTION_TYPE)
    {
      error_at (loc, "cast specifies function type");
      ਵਾਪਸ error_mark_ਗੰਢ;
    }

  ਜੇ (!VOID_TYPE_P (type))
    {
      ਮੁੱਲ = require_complete_type (loc, ਮੁੱਲ);
      ਜੇ (ਮੁੱਲ == error_mark_ਗੰਢ)
	ਵਾਪਸ error_mark_ਗੰਢ;
    }

  ਜੇ (type == TYPE_MAIN_VARIANT (ਰੁੱਖ_TYPE (ਮੁੱਲ)))
    {
      ਜੇ (ਰਿਕਾਰਡ_OR_UNION_TYPE_P (type)
	  && pedwarn (loc, OPT_Wpedantic,
		      "ISO C forbids casting nonscalar to the same type"))
	      ;
      ਨਹੀਂਤਾਂ ਜੇ (warn_useless_cast && c_inhibit_evaluation_warnings == 0)
	warning_at (loc, OPT_Wuseless_cast,
		    "useless cast to type %qT", type);

      /* Convert to remove any qualifiers from VALUE's type.  */
      ਮੁੱਲ = convert (type, ਮੁੱਲ);
    }
  ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਕੋਡ (type) == UNION_TYPE)
    {
      ਰੁੱਖ ਖੇਤਰ_2;

      ਲਈ (ਖੇਤਰ_2 = TYPE_FIELDS (type); ਖੇਤਰ_2; ਖੇਤਰ_2 = DECL_CHAIN (ਖੇਤਰ_2))
	ਜੇ (ਰੁੱਖ_TYPE (ਖੇਤਰ_2) != error_mark_ਗੰਢ
	    && comptypes (TYPE_MAIN_VARIANT (ਰੁੱਖ_TYPE (ਖੇਤਰ_2)),
			  TYPE_MAIN_VARIANT (ਰੁੱਖ_TYPE (ਮੁੱਲ))))
	  ਰੋਕੋ;

      ਜੇ (ਖੇਤਰ_2)
	{
	  ਰੁੱਖ t;
	  ਤਾਰਕਿਕ maybe_const = ਸੱਚ;

	  pedwarn (loc, OPT_Wpedantic, "ISO C forbids casts to union type");
	  t = c_fully_fold (ਮੁੱਲ, ਝੂਠ, &maybe_const);
	  t = build_constructor_single (type, ਖੇਤਰ_2, t);
	  ਜੇ (!maybe_const)
	    t = c_wrap_maybe_const (t, ਸੱਚ);
	  t = digest_init (loc, ਖੇਤਰ_2, type, t,
			   NULL_ਰੁੱਖ, ਝੂਠ, ਝੂਠ, ਝੂਠ, ਸੱਚ, ਝੂਠ, ਝੂਠ);
	  ਰੁੱਖ_CONSTANT (t) = ਰੁੱਖ_CONSTANT (ਮੁੱਲ);
	  ਵਾਪਸ t;
	}
      error_at (loc, "cast to union type from type not present in union");
      ਵਾਪਸ error_mark_ਗੰਢ;
    }
  ਨਹੀਂਤਾਂ
    {
      ਰੁੱਖ otype, ovalue;

      ਜੇ (type == void_type_ਗੰਢ)
	{
	  ਰੁੱਖ t = build1 (CONVERT_ਵਿਅੰਜਕ, type, ਮੁੱਲ);
	  ਸੈੱਟ_ਵਿਅੰਜਕ_LOCATION (t, loc);
	  ਵਾਪਸ t;
	}

      otype = ਰੁੱਖ_TYPE (ਮੁੱਲ);

      /* Optionally warn about potentially worrisome casts.  */
      ਜੇ (warn_cast_qual
	  && ਰੁੱਖ_ਕੋਡ (type) == ਸੂਚਕ_TYPE
	  && ਰੁੱਖ_ਕੋਡ (otype) == ਸੂਚਕ_TYPE)
	handle_warn_cast_qual (loc, type, otype);

      /* Warn about conversions between pointers to disjoint
	 address spaces.  */
      ਜੇ (ਰੁੱਖ_ਕੋਡ (type) == ਸੂਚਕ_TYPE
	  && ਰੁੱਖ_ਕੋਡ (otype) == ਸੂਚਕ_TYPE
	  && !null_ਸੂਚਕ_constant_p (ਮੁੱਲ))
	{
	  addr_space_t as_ਮੰਜ਼ਿਲ = TYPE_ADDR_SPACE (ਰੁੱਖ_TYPE (type));
	  addr_space_t as_from = TYPE_ADDR_SPACE (ਰੁੱਖ_TYPE (otype));
	  addr_space_t as_common;

	  ਜੇ (!addr_space_superset (as_ਮੰਜ਼ਿਲ, as_from, &as_common))
	    {
	      ਜੇ (ADDR_SPACE_GENERIC_P (as_from))
		warning_at (loc, 0, "cast to %qs address space pointer "
			    "from disjoint generic address space pointer",
			    c_addr_space_name (as_ਮੰਜ਼ਿਲ));

	      ਨਹੀਂਤਾਂ ਜੇ (ADDR_SPACE_GENERIC_P (as_ਮੰਜ਼ਿਲ))
		warning_at (loc, 0, "cast to generic address space pointer "
			    "from disjoint %qs address space pointer",
			    c_addr_space_name (as_from));

	      ਨਹੀਂਤਾਂ
		warning_at (loc, 0, "cast to %qs address space pointer "
			    "from disjoint %qs address space pointer",
			    c_addr_space_name (as_ਮੰਜ਼ਿਲ),
			    c_addr_space_name (as_from));
	    }

	  /* Warn of new allocations that are not big enough for the target
	     type.  */
	  ਜੇ (warn_alloc_ਮਾਪ && ਰੁੱਖ_ਕੋਡ (ਮੁੱਲ) == CALL_ਵਿਅੰਜਕ)
	    ਜੇ (ਰੁੱਖ fndecl = get_callee_fndecl (ਮੁੱਲ))
	      ਜੇ (DECL_IS_MALLOC (fndecl))
		{
		  ਰੁੱਖ attrs = TYPE_ਗੁਣ (ਰੁੱਖ_TYPE (fndecl));
		  ਰੁੱਖ alloc_ਮਾਪ = lookup_attribute ("alloc_size", attrs);
		  ਜੇ (alloc_ਮਾਪ)
		    warn_for_alloc_ਮਾਪ (loc, ਰੁੱਖ_TYPE (type), ਮੁੱਲ,
					 alloc_ਮਾਪ);
		}
	}

      /* Warn about possible alignment problems.  */
      ਜੇ ((STRICT_ALIGNMENT || warn_cast_align == 2)
	  && ਰੁੱਖ_ਕੋਡ (type) == ਸੂਚਕ_TYPE
	  && ਰੁੱਖ_ਕੋਡ (otype) == ਸੂਚਕ_TYPE
	  && ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (otype)) != VOID_TYPE
	  && ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (otype)) != FUNCTION_TYPE
	  /* Don't warn about opaque types, where the actual alignment
	     restriction is unknown.  */
	  && !(ਰਿਕਾਰਡ_OR_UNION_TYPE_P (ਰੁੱਖ_TYPE (otype))
	       && TYPE_ਬਹੁਲਕ (ਰੁੱਖ_TYPE (otype)) == VOIDmode)
	  && min_align_ਦਾ_type (ਰੁੱਖ_TYPE (type))
	     > min_align_ਦਾ_type (ਰੁੱਖ_TYPE (otype)))
	warning_at (loc, OPT_Wcast_align,
		    "cast increases required alignment of target type");

      ਜੇ ((ਰੁੱਖ_ਕੋਡ (type) == INTEGER_TYPE
	   || ਰੁੱਖ_ਕੋਡ (type) == BITINT_TYPE)
	  && ਰੁੱਖ_ਕੋਡ (otype) == ਸੂਚਕ_TYPE
	  && TYPE_PRECISION (type) != TYPE_PRECISION (otype))
      /* Unlike conversion of integers to pointers, where the
         warning is disabled for converting constants because
         of cases such as SIG_*, warn about converting constant
         pointers to integers. In some cases it may cause unwanted
         sign extension, and a warning is appropriate.  */
	warning_at (loc, OPT_Wpointer_ਮੰਜ਼ਿਲ_int_cast,
		    "cast from pointer to integer of different size");

      ਜੇ ((ਰੁੱਖ_ਕੋਡ (ਮੁੱਲ) == CALL_ਵਿਅੰਜਕ
	   && !is_access_with_ਮਾਪ_p (ਮੁੱਲ))
	  && ਰੁੱਖ_ਕੋਡ (type) != ਰੁੱਖ_ਕੋਡ (otype))
	warning_at (loc, OPT_Wbad_function_cast,
		    "cast from function call of type %qT "
		    "to non-matching type %qT", otype, type);

      ਜੇ (ਰੁੱਖ_ਕੋਡ (type) == ਸੂਚਕ_TYPE
	  && (ਰੁੱਖ_ਕੋਡ (otype) == INTEGER_TYPE
	      || ਰੁੱਖ_ਕੋਡ (otype) == BITINT_TYPE)
	  && TYPE_PRECISION (type) != TYPE_PRECISION (otype)
	  /* Don't warn about converting any constant.  */
	  && !ਰੁੱਖ_CONSTANT (ਮੁੱਲ))
	warning_at (loc,
		    OPT_Wint_ਮੰਜ਼ਿਲ_ਸੂਚਕ_cast, "cast to pointer from integer "
		    "of different size");

      ਜੇ (warn_strict_aliasing <= 2)
        strict_aliasing_warning (ਵਿਅੰਜਕ_LOCATION (ਮੁੱਲ), type, ਵਿਅੰਜਕ);

      /* If pedantic, warn for conversions between function and object
	 pointer types, except for converting a null pointer constant
	 to function pointer type.  */
      ਜੇ (pedantic
	  && ਰੁੱਖ_ਕੋਡ (type) == ਸੂਚਕ_TYPE
	  && ਰੁੱਖ_ਕੋਡ (otype) == ਸੂਚਕ_TYPE
	  && ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (otype)) == FUNCTION_TYPE
	  && ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (type)) != FUNCTION_TYPE)
	pedwarn (loc, OPT_Wpedantic, "ISO C forbids "
		 "conversion of function pointer to object pointer type");

      ਜੇ (pedantic
	  && ਰੁੱਖ_ਕੋਡ (type) == ਸੂਚਕ_TYPE
	  && ਰੁੱਖ_ਕੋਡ (otype) == ਸੂਚਕ_TYPE
	  && ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (type)) == FUNCTION_TYPE
	  && ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (otype)) != FUNCTION_TYPE
	  && !null_ਸੂਚਕ_constant_p (ਮੁੱਲ))
	pedwarn (loc, OPT_Wpedantic, "ISO C forbids "
		 "conversion of object pointer to function pointer type");

      ਜੇ (ਰੁੱਖ_ਕੋਡ (type) == ਸੂਚਕ_TYPE
	  && ਰੁੱਖ_ਕੋਡ (otype) == ਸੂਚਕ_TYPE
	  && ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (type)) == FUNCTION_TYPE
	  && ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (otype)) == FUNCTION_TYPE
	  && !c_ਸੁਰੱਖਿਅਤ_function_type_cast_p (ਰੁੱਖ_TYPE (type),
					   ਰੁੱਖ_TYPE (otype)))
	warning_at (loc, OPT_Wcast_function_type,
		    "cast between incompatible function types"
		    " from %qT to %qT", otype, type);

      ovalue = ਮੁੱਲ;
      /* If converting to boolean a value with integer operands that
	 is not itself represented as an INTEGER_CST, the call below
	 to note_integer_operands may insert a C_MAYBE_CONST_EXPR, but
	 build_binary_op as called by c_common_truthvalue_conversion
	 may also insert a C_MAYBE_CONST_EXPR to indicate that a
	 subexpression has been fully folded.  To avoid nested
	 C_MAYBE_CONST_EXPR, ensure that
	 c_objc_common_truthvalue_conversion receives an argument
	 properly marked as having integer operands in that case.  */
      ਜੇ (int_operands
	  && ਰੁੱਖ_ਕੋਡ (ਮੁੱਲ) != INTEGER_CST
	  && (ਰੁੱਖ_ਕੋਡ (type) == BOOLEAN_TYPE
	      || (ਰੁੱਖ_ਕੋਡ (type) == ENUMERAL_TYPE
		  && ENUM_UNDERLYING_TYPE (type) != NULL_ਰੁੱਖ
		  && ਰੁੱਖ_ਕੋਡ (ENUM_UNDERLYING_TYPE (type)) == BOOLEAN_TYPE)))
	ਮੁੱਲ = note_integer_operands (ਮੁੱਲ);
      ਮੁੱਲ = convert (type, ਮੁੱਲ);

      /* Ignore any integer overflow caused by the cast.  */
      ਜੇ (ਰੁੱਖ_ਕੋਡ (ਮੁੱਲ) == INTEGER_CST && !FLOAT_TYPE_P (otype))
	{
	  ਜੇ (ਰੁੱਖ_ਉਛਾਲ_P (ovalue))
	    {
	      ਜੇ (!ਰੁੱਖ_ਉਛਾਲ (ਮੁੱਲ))
		{
		  /* Avoid clobbering a shared constant.  */
		  ਮੁੱਲ = copy_ਗੰਢ (ਮੁੱਲ);
		  ਰੁੱਖ_ਉਛਾਲ (ਮੁੱਲ) = ਰੁੱਖ_ਉਛਾਲ (ovalue);
		}
	    }
	  ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਉਛਾਲ (ਮੁੱਲ))
	    /* Reset VALUE's overflow flags, ensuring constant sharing.  */
	    ਮੁੱਲ = wide_int_ਮੰਜ਼ਿਲ_ਰੁੱਖ (ਰੁੱਖ_TYPE (ਮੁੱਲ), wi::ਮੰਜ਼ਿਲ_wide (ਮੁੱਲ));
	}
    }

  /* Don't let a cast be an lvalue.  */
  ਜੇ (lvalue_p (ਮੁੱਲ)
      /* Also, don't let a cast be a bit-field of a bit-precise integer type,
	 otherwise it could be incorrectly subject of integer promotions.  */
      || (ਰੁੱਖ_ਕੋਡ (ਮੁੱਲ) == COMPONENT_REF
	  && DECL_C_ਦੋਆਧਾਰੀ_ਅੰਕ_ਖੇਤਰ (ਰੁੱਖ_ਸੰਕਾਰਜ (ਮੁੱਲ, 1))
	  && BITINT_TYPE_P (DECL_ਦੋਆਧਾਰੀ_ਅੰਕ_ਖੇਤਰ_TYPE (ਰੁੱਖ_ਸੰਕਾਰਜ (ਮੁੱਲ, 1)))))
    ਮੁੱਲ = non_lvalue_loc (loc, ਮੁੱਲ);

  /* Don't allow the results of casting to floating-point or complex
     types be confused with actual constants, or casts involving
     integer and pointer types other than direct integer-to-integer
     and integer-to-pointer be confused with integer constant
     expressions and null pointer constants.  */
  ਜੇ (ਰੁੱਖ_ਕੋਡ (ਮੁੱਲ) == REAL_CST
      || ਰੁੱਖ_ਕੋਡ (ਮੁੱਲ) == COMPLEX_CST
      || (ਰੁੱਖ_ਕੋਡ (ਮੁੱਲ) == INTEGER_CST
	  && !((ਰੁੱਖ_ਕੋਡ (ਵਿਅੰਜਕ) == INTEGER_CST
		&& INTEGRAL_TYPE_P (ਰੁੱਖ_TYPE (ਵਿਅੰਜਕ)))
	       || ਰੁੱਖ_ਕੋਡ (ਵਿਅੰਜਕ) == REAL_CST
	       || ਰੁੱਖ_ਕੋਡ (ਵਿਅੰਜਕ) == COMPLEX_CST)))
      ਮੁੱਲ = build1 (NOP_ਵਿਅੰਜਕ, type, ਮੁੱਲ);

  /* If the expression has integer operands and so can occur in an
     unevaluated part of an integer constant expression, ensure the
     return value reflects this.  */
  ਜੇ (int_operands
      && INTEGRAL_TYPE_P (type)
      && ਮੁੱਲ != error_mark_ਗੰਢ
      && !ਵਿਅੰਜਕ_INT_CONST_OPERANDS (ਮੁੱਲ))
    ਮੁੱਲ = note_integer_operands (ਮੁੱਲ);

  protected_ਸੈੱਟ_ਵਿਅੰਜਕ_location (ਮੁੱਲ, loc);
  ਵਾਪਸ ਮੁੱਲ;
}

/* Interpret a cast of expression EXPR to type TYPE.  LOC is the
   location of the open paren of the cast, or the position of the cast
   expr.  */
ਰੁੱਖ
c_cast_ਵਿਅੰਜਕ (location_t loc, ਬਣਤਰ c_type_name *type_name, ਰੁੱਖ ਵਿਅੰਜਕ)
{
  ਰੁੱਖ type;
  ਰੁੱਖ type_ਵਿਅੰਜਕ = NULL_ਰੁੱਖ;
  ਤਾਰਕਿਕ type_ਵਿਅੰਜਕ_const = ਸੱਚ;
  ਰੁੱਖ ret;
  ਪੂਰਨ saved_wsp = warn_strict_prototypes;

  /* This avoids warnings about unprototyped casts on
     integers.  E.g. "#define SIG_DFL (void(*)())0".  */
  ਜੇ (ਰੁੱਖ_ਕੋਡ (ਵਿਅੰਜਕ) == INTEGER_CST)
    warn_strict_prototypes = 0;
  type = groktypename (type_name, &type_ਵਿਅੰਜਕ, &type_ਵਿਅੰਜਕ_const);
  warn_strict_prototypes = saved_wsp;

  ਜੇ (ਰੁੱਖ_ਕੋਡ (ਵਿਅੰਜਕ) == ADDR_ਵਿਅੰਜਕ && !VOID_TYPE_P (type)
      && reject_gcc_builtin (ਵਿਅੰਜਕ))
    ਵਾਪਸ error_mark_ਗੰਢ;

  ret = build_c_cast (loc, type, ਵਿਅੰਜਕ);
  ਜੇ (ret == error_mark_ਗੰਢ)
    ਵਾਪਸ error_mark_ਗੰਢ;

  ਜੇ (type_ਵਿਅੰਜਕ)
    {
      ਤਾਰਕਿਕ inner_ਵਿਅੰਜਕ_const = ਸੱਚ;
      ret = c_fully_fold (ret, require_constant_ਮੁੱਲ, &inner_ਵਿਅੰਜਕ_const);
      ret = build2 (C_MAYBE_CONST_ਵਿਅੰਜਕ, ਰੁੱਖ_TYPE (ret), type_ਵਿਅੰਜਕ, ret);
      C_MAYBE_CONST_ਵਿਅੰਜਕ_NON_CONST (ret) = !(type_ਵਿਅੰਜਕ_const
					     && inner_ਵਿਅੰਜਕ_const);
      ਸੈੱਟ_ਵਿਅੰਜਕ_LOCATION (ret, loc);
    }

  ਜੇ (!ਵਿਅੰਜਕ_HAS_LOCATION (ret))
    protected_ਸੈੱਟ_ਵਿਅੰਜਕ_location (ret, loc);

  /* C++ does not permits types to be defined in a cast, but it
     allows references to incomplete types.  */
  ਜੇ (warn_cxx_compat && type_name->specs->typespec_ਕਿਸਮ == ctsk_tagdef)
    warning_at (loc, OPT_Wc___compat,
		"defining a type in a cast is invalid in C++");

  ਵਾਪਸ ret;
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

ਰੁੱਖ
build_modify_ਵਿਅੰਜਕ (location_t location, ਰੁੱਖ lhs, ਰੁੱਖ lhs_origtype,
		   ਗਿਣਤੀ ਰੁੱਖ_ਕੋਡ_2 modifycode,
		   location_t rhs_loc, ਰੁੱਖ rhs, ਰੁੱਖ rhs_origtype)
{
  ਰੁੱਖ ਨਤੀਜਾ;
  ਰੁੱਖ newrhs;
  ਰੁੱਖ rhseval = NULL_ਰੁੱਖ;
  ਰੁੱਖ lhstype = ਰੁੱਖ_TYPE (lhs);
  ਰੁੱਖ olhstype = lhstype;
  ਤਾਰਕਿਕ npc;
  ਤਾਰਕਿਕ is_atomic_op;

  /* Types that aren't fully specified cannot be used in assignments.  */
  lhs = require_complete_type (location, lhs);
  rhs = require_complete_type (location, rhs);

  /* Avoid duplicate error messages from operands that had errors.  */
  ਜੇ (ਰੁੱਖ_ਕੋਡ (lhs) == ERROR_MARK || ਰੁੱਖ_ਕੋਡ (rhs) == ERROR_MARK)
    ਵਾਪਸ error_mark_ਗੰਢ;

  /* Ensure an error for assigning a non-lvalue array to an array in
     C90.  */
  ਜੇ (ਰੁੱਖ_ਕੋਡ (lhstype) == ARRAY_TYPE)
    {
      error_at (location, "assignment to expression with array type");
      ਵਾਪਸ error_mark_ਗੰਢ;
    }

  /* For ObjC properties, defer this check.  */
  ਜੇ (!objc_is_property_ref (lhs) && !lvalue_or_else (location, lhs, lv_ਸੌਂਪੋ))
    ਵਾਪਸ error_mark_ਗੰਢ;

  is_atomic_op = really_atomic_lvalue (lhs);

  newrhs = rhs;

  ਜੇ (ਰੁੱਖ_ਕੋਡ (lhs) == C_MAYBE_CONST_ਵਿਅੰਜਕ)
    {
      ਰੁੱਖ inner = build_modify_ਵਿਅੰਜਕ (location, C_MAYBE_CONST_ਵਿਅੰਜਕ_ਵਿਅੰਜਕ (lhs),
				      lhs_origtype, modifycode, rhs_loc, rhs,
				      rhs_origtype);
      ਜੇ (inner == error_mark_ਗੰਢ)
	ਵਾਪਸ error_mark_ਗੰਢ;
      ਨਤੀਜਾ = build2 (C_MAYBE_CONST_ਵਿਅੰਜਕ, ਰੁੱਖ_TYPE (inner),
		       C_MAYBE_CONST_ਵਿਅੰਜਕ_PRE (lhs), inner);
      gcc_assert (!C_MAYBE_CONST_ਵਿਅੰਜਕ_INT_OPERANDS (lhs));
      C_MAYBE_CONST_ਵਿਅੰਜਕ_NON_CONST (ਨਤੀਜਾ) = 1;
      protected_ਸੈੱਟ_ਵਿਅੰਜਕ_location (ਨਤੀਜਾ, location);
      ਵਾਪਸ ਨਤੀਜਾ;
    }

  /* If a binary op has been requested, combine the old LHS value with the RHS
     producing the value we should actually store into the LHS.  */

  ਜੇ (modifycode != NOP_ਵਿਅੰਜਕ)
    {
      lhs = c_fully_fold (lhs, ਝੂਠ, ਨਿਰਾ, ਸੱਚ);
      lhs = stabilize_reference (lhs);

      /* Construct the RHS for any non-atomic compound assignment. */
      ਜੇ (!is_atomic_op)
        {
	  /* If in LHS op= RHS the RHS has side-effects, ensure they
	     are preevaluated before the rest of the assignment expression's
	     side-effects, because RHS could contain e.g. function calls
	     that modify LHS.  */
	  ਜੇ (ਰੁੱਖ_SIDE_EFFECTS (rhs))
	    {
	      ਜੇ (ਰੁੱਖ_ਕੋਡ (rhs) == EXCESS_PRECISION_ਵਿਅੰਜਕ)
		newrhs = save_ਵਿਅੰਜਕ (ਰੁੱਖ_ਸੰਕਾਰਜ (rhs, 0));
	      ਨਹੀਂਤਾਂ
		newrhs = save_ਵਿਅੰਜਕ (rhs);
	      rhseval = newrhs;
	      ਜੇ (ਰੁੱਖ_ਕੋਡ (rhs) == EXCESS_PRECISION_ਵਿਅੰਜਕ)
		newrhs = build1 (EXCESS_PRECISION_ਵਿਅੰਜਕ, ਰੁੱਖ_TYPE (rhs),
				 newrhs);
	    }
	  ਤਾਰਕਿਕ clear_decl_read = ਝੂਠ;
	  ਜੇ ((VAR_P (lhs) || ਰੁੱਖ_ਕੋਡ (lhs) == PARM_DECL)
	      && !DECL_READ_P (lhs)
	      && (VAR_P (lhs) ? warn_ਅਣਵਰਤਿਆ_but_ਸੈੱਟ_variable
			      : warn_ਅਣਵਰਤਿਆ_but_ਸੈੱਟ_parameter) > 2)
	    {
	      mark_exp_read (newrhs);
	      ਜੇ (!DECL_READ_P (lhs))
		clear_decl_read = ਸੱਚ;
	    }

	  newrhs = build_ਦੁਆਧਾਰੀ_op (location, modifycode,
				    convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (location, lhs,
							      ਸੱਚ, ਸੱਚ),
				    newrhs, ਸੱਚ);
	  ਜੇ (clear_decl_read)
	    DECL_READ_P (lhs) = 0;

	  /* The original type of the right hand side is no longer
	     meaningful.  */
	  rhs_origtype = NULL_ਰੁੱਖ;
	}
    }

  ਜੇ (c_dialect_objc ())
    {
      /* Check if we are modifying an Objective-C property reference;
	 if so, we need to generate setter calls.  */
      ਜੇ (ਰੁੱਖ_ਕੋਡ (newrhs) == EXCESS_PRECISION_ਵਿਅੰਜਕ)
	ਨਤੀਜਾ = objc_maybe_build_modify_ਵਿਅੰਜਕ (lhs, ਰੁੱਖ_ਸੰਕਾਰਜ (newrhs, 0));
      ਨਹੀਂਤਾਂ
	ਨਤੀਜਾ = objc_maybe_build_modify_ਵਿਅੰਜਕ (lhs, newrhs);
      ਜੇ (ਨਤੀਜਾ)
	ਜਾਓ return_ਨਤੀਜਾ;

      /* Else, do the check that we postponed for Objective-C.  */
      ਜੇ (!lvalue_or_else (location, lhs, lv_ਸੌਂਪੋ))
	ਵਾਪਸ error_mark_ਗੰਢ;
    }

  /* Give an error for storing in something that is 'const'.  */

  ਜੇ (TYPE_READONLY (lhstype)
      || (ਰਿਕਾਰਡ_OR_UNION_TYPE_P (lhstype)
	  && C_TYPE_FIELDS_READONLY (lhstype)))
    {
      readonly_error (location, lhs, lv_ਸੌਂਪੋ);
      ਵਾਪਸ error_mark_ਗੰਢ;
    }
  ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_READONLY (lhs))
    readonly_warning (lhs, lv_ਸੌਂਪੋ);

  /* If storing into a structure or union member,
     it has probably been given type `int'.
     Compute the type that would go with
     the actual amount of storage the member occupies.  */

  ਜੇ (ਰੁੱਖ_ਕੋਡ (lhs) == COMPONENT_REF
      && (ਰੁੱਖ_ਕੋਡ (lhstype) == INTEGER_TYPE
	  || ਰੁੱਖ_ਕੋਡ (lhstype) == BOOLEAN_TYPE
	  || SCALAR_FLOAT_TYPE_P (lhstype)
	  || ਰੁੱਖ_ਕੋਡ (lhstype) == ENUMERAL_TYPE))
    lhstype = ਰੁੱਖ_TYPE (get_unwidened (lhs, 0));

  /* If storing in a field that is in actuality a short or narrower than one,
     we must store in the field in its actual type.  */

  ਜੇ (lhstype != ਰੁੱਖ_TYPE (lhs))
    {
      lhs = copy_ਗੰਢ (lhs);
      ਰੁੱਖ_TYPE (lhs) = lhstype;
    }

  /* Issue -Wc++-compat warnings about an assignment to an enum type
     when LHS does not have its original type.  This happens for,
     e.g., an enum bitfield in a struct.  */
  ਜੇ (warn_cxx_compat
      && lhs_origtype != NULL_ਰੁੱਖ
      && lhs_origtype != lhstype
      && ਰੁੱਖ_ਕੋਡ (lhs_origtype) == ENUMERAL_TYPE)
    {
      ਰੁੱਖ checktype = (rhs_origtype != NULL_ਰੁੱਖ
			? rhs_origtype
			: ਰੁੱਖ_TYPE (rhs));
      ਜੇ (checktype != error_mark_ਗੰਢ
	  && (TYPE_MAIN_VARIANT (checktype) != TYPE_MAIN_VARIANT (lhs_origtype)
	      || (is_atomic_op && modifycode != NOP_ਵਿਅੰਜਕ)))
	warning_at (location, OPT_Wc___compat,
		    "enum conversion in assignment is invalid in C++");
    }

  /* Remove qualifiers.  */
  lhstype = c_build_qualified_type (lhstype, TYPE_UNQUALIFIED);
  olhstype = c_build_qualified_type (olhstype, TYPE_UNQUALIFIED);

  /* Convert new value to destination type.  Fold it first, then
     restore any excess precision information, for the sake of
     conversion warnings.  */

  ਜੇ (!(is_atomic_op && modifycode != NOP_ਵਿਅੰਜਕ))
    {
      ਰੁੱਖ rhs_semantic_type = NULL_ਰੁੱਖ;
      ਜੇ (!c_ਵਿੱਚ_omp_for)
	{
	  ਜੇ (ਰੁੱਖ_ਕੋਡ (newrhs) == EXCESS_PRECISION_ਵਿਅੰਜਕ)
	    {
	      rhs_semantic_type = ਰੁੱਖ_TYPE (newrhs);
	      newrhs = ਰੁੱਖ_ਸੰਕਾਰਜ (newrhs, 0);
	    }
	  npc = null_ਸੂਚਕ_constant_p (newrhs);
	  newrhs = c_fully_fold (newrhs, ਝੂਠ, ਨਿਰਾ);
	  ਜੇ (rhs_semantic_type)
	    newrhs = build1 (EXCESS_PRECISION_ਵਿਅੰਜਕ, rhs_semantic_type, newrhs);
	}
      ਨਹੀਂਤਾਂ
	npc = null_ਸੂਚਕ_constant_p (newrhs);
      newrhs = convert_for_assignment (location, rhs_loc, lhstype, newrhs,
				       rhs_origtype, ic_ਸੌਂਪੋ, npc,
				       NULL_ਰੁੱਖ, NULL_ਰੁੱਖ, 0);
      ਜੇ (ਰੁੱਖ_ਕੋਡ (newrhs) == ERROR_MARK)
	ਵਾਪਸ error_mark_ਗੰਢ;
    }

  /* Emit ObjC write barrier, if necessary.  */
  ਜੇ (c_dialect_objc () && flag_objc_gc)
    {
      ਨਤੀਜਾ = objc_generate_write_barrier (lhs, modifycode, newrhs);
      ਜੇ (ਨਤੀਜਾ)
	{
	  protected_ਸੈੱਟ_ਵਿਅੰਜਕ_location (ਨਤੀਜਾ, location);
	  ਜਾਓ return_ਨਤੀਜਾ;
	}
    }

  /* Scan operands.  */

  ਜੇ (is_atomic_op)
    ਨਤੀਜਾ = build_atomic_ਸੌਂਪੋ (location, lhs, modifycode, newrhs, ਝੂਠ);
  ਨਹੀਂਤਾਂ
    {
      ਨਤੀਜਾ = build2 (MODIFY_ਵਿਅੰਜਕ, lhstype, lhs, newrhs);
      ਰੁੱਖ_SIDE_EFFECTS (ਨਤੀਜਾ) = 1;
      protected_ਸੈੱਟ_ਵਿਅੰਜਕ_location (ਨਤੀਜਾ, location);
    }

  /* If we got the LHS in a different type for storing in,
     convert the result back to the nominal type of LHS
     so that the value we return always has the same type
     as the LHS argument.  */

  ਜੇ (olhstype == ਰੁੱਖ_TYPE (ਨਤੀਜਾ))
    ਜਾਓ return_ਨਤੀਜਾ;

  ਨਤੀਜਾ = convert_for_assignment (location, rhs_loc, olhstype, ਨਤੀਜਾ,
				   rhs_origtype, ic_ਸੌਂਪੋ, ਝੂਠ, NULL_ਰੁੱਖ,
				   NULL_ਰੁੱਖ, 0);
  protected_ਸੈੱਟ_ਵਿਅੰਜਕ_location (ਨਤੀਜਾ, location);

return_ਨਤੀਜਾ:
  ਜੇ (rhseval)
    ਨਤੀਜਾ = build2 (COMPOUND_ਵਿਅੰਜਕ, ਰੁੱਖ_TYPE (ਨਤੀਜਾ), rhseval, ਨਤੀਜਾ);
  ਵਾਪਸ ਨਤੀਜਾ;
}

/* Return whether STRUCT_TYPE has an anonymous field with type TYPE.
   This is used to implement -fplan9-extensions.  */

ਸਥਿਰ ਤਾਰਕਿਕ
ਲੱਭੋ_anonymous_ਖੇਤਰ_with_type (ਰੁੱਖ struct_type, ਰੁੱਖ type)
{
  ਰੁੱਖ ਖੇਤਰ_2;
  ਤਾਰਕਿਕ ਮਿਲਿਆ;

  gcc_assert (ਰਿਕਾਰਡ_OR_UNION_TYPE_P (struct_type));
  ਮਿਲਿਆ = ਝੂਠ;
  ਲਈ (ਖੇਤਰ_2 = TYPE_FIELDS (struct_type);
       ਖੇਤਰ_2 != NULL_ਰੁੱਖ;
       ਖੇਤਰ_2 = ਰੁੱਖ_CHAIN (ਖੇਤਰ_2))
    {
      ਰੁੱਖ fieldtype = remove_qualifiers (ਰੁੱਖ_TYPE (ਖੇਤਰ_2));
      ਜੇ (DECL_NAME (ਖੇਤਰ_2) == ਨਿਰਾ
	  && comptypes (type, fieldtype))
	{
	  ਜੇ (ਮਿਲਿਆ)
	    ਵਾਪਸ ਝੂਠ;
	  ਮਿਲਿਆ = ਸੱਚ;
	}
      ਨਹੀਂਤਾਂ ਜੇ (DECL_NAME (ਖੇਤਰ_2) == ਨਿਰਾ
	       && ਰਿਕਾਰਡ_OR_UNION_TYPE_P (ਰੁੱਖ_TYPE (ਖੇਤਰ_2))
	       && ਲੱਭੋ_anonymous_ਖੇਤਰ_with_type (ਰੁੱਖ_TYPE (ਖੇਤਰ_2), type))
	{
	  ਜੇ (ਮਿਲਿਆ)
	    ਵਾਪਸ ਝੂਠ;
	  ਮਿਲਿਆ = ਸੱਚ;
	}
    }
  ਵਾਪਸ ਮਿਲਿਆ;
}

/* RHS is an expression whose type is pointer to struct.  If there is
   an anonymous field in RHS with type TYPE, then return a pointer to
   that field in RHS.  This is used with -fplan9-extensions.  This
   returns NULL if no conversion could be found.  */

ਸਥਿਰ ਰੁੱਖ
convert_ਮੰਜ਼ਿਲ_anonymous_ਖੇਤਰ (location_t location, ਰੁੱਖ type, ਰੁੱਖ rhs)
{
  ਰੁੱਖ rhs_struct_type, lhs_main_type;
  ਰੁੱਖ ਖੇਤਰ_2, ਮਿਲਿਆ_ਖੇਤਰ;
  ਤਾਰਕਿਕ ਮਿਲਿਆ_sub_ਖੇਤਰ;
  ਰੁੱਖ ret;

  gcc_assert (ਸੂਚਕ_TYPE_P (ਰੁੱਖ_TYPE (rhs)));
  rhs_struct_type = ਰੁੱਖ_TYPE (ਰੁੱਖ_TYPE (rhs));
  gcc_assert (ਰਿਕਾਰਡ_OR_UNION_TYPE_P (rhs_struct_type));

  gcc_assert (ਸੂਚਕ_TYPE_P (type));
  lhs_main_type = remove_qualifiers (ਰੁੱਖ_TYPE (type));

  ਮਿਲਿਆ_ਖੇਤਰ = NULL_ਰੁੱਖ;
  ਮਿਲਿਆ_sub_ਖੇਤਰ = ਝੂਠ;
  ਲਈ (ਖੇਤਰ_2 = TYPE_FIELDS (rhs_struct_type);
       ਖੇਤਰ_2 != NULL_ਰੁੱਖ;
       ਖੇਤਰ_2 = ਰੁੱਖ_CHAIN (ਖੇਤਰ_2))
    {
      ਜੇ (DECL_NAME (ਖੇਤਰ_2) != NULL_ਰੁੱਖ
	  || !ਰਿਕਾਰਡ_OR_UNION_TYPE_P (ਰੁੱਖ_TYPE (ਖੇਤਰ_2)))
	ਜਾਰੀ;
      ਰੁੱਖ fieldtype = remove_qualifiers (ਰੁੱਖ_TYPE (ਖੇਤਰ_2));
      ਜੇ (comptypes (lhs_main_type, fieldtype))
	{
	  ਜੇ (ਮਿਲਿਆ_ਖੇਤਰ != NULL_ਰੁੱਖ)
	    ਵਾਪਸ NULL_ਰੁੱਖ;
	  ਮਿਲਿਆ_ਖੇਤਰ = ਖੇਤਰ_2;
	}
      ਨਹੀਂਤਾਂ ਜੇ (ਲੱਭੋ_anonymous_ਖੇਤਰ_with_type (ਰੁੱਖ_TYPE (ਖੇਤਰ_2),
					       lhs_main_type))
	{
	  ਜੇ (ਮਿਲਿਆ_ਖੇਤਰ != NULL_ਰੁੱਖ)
	    ਵਾਪਸ NULL_ਰੁੱਖ;
	  ਮਿਲਿਆ_ਖੇਤਰ = ਖੇਤਰ_2;
	  ਮਿਲਿਆ_sub_ਖੇਤਰ = ਸੱਚ;
	}
    }

  ਜੇ (ਮਿਲਿਆ_ਖੇਤਰ == NULL_ਰੁੱਖ)
    ਵਾਪਸ NULL_ਰੁੱਖ;

  ret = fold_build3_loc (location, COMPONENT_REF, ਰੁੱਖ_TYPE (ਮਿਲਿਆ_ਖੇਤਰ),
			 build_fold_ਅਸਿੱਧਾ_ref (rhs), ਮਿਲਿਆ_ਖੇਤਰ,
			 NULL_ਰੁੱਖ);
  ret = build_fold_addr_ਵਿਅੰਜਕ_loc (location, ret);

  ਜੇ (ਮਿਲਿਆ_sub_ਖੇਤਰ)
    {
      ret = convert_ਮੰਜ਼ਿਲ_anonymous_ਖੇਤਰ (location, type, ret);
      gcc_assert (ret != NULL_ਰੁੱਖ);
    }

  ਵਾਪਸ ret;
}

/* Issue an error message for a bad initializer component.
   GMSGID identifies the message.
   The component name is taken from the spelling stack.  */

ਸਥਿਰ ਖਾਲੀ ATTRIBUTE_GCC_DIAG (2,0)
error_init (location_t loc, ਅਚਲ ਅੱਖਰ *gmsgid, ...)
{
  ਅੱਖਰ *ofwhat;

  auto_diagnostic_ਸਮੂਹ d;

  /* The gmsgid may be a format string with %< and %>. */
  va_list ap;
  va_ਸ਼ੁਰੂ (ap, gmsgid);
  ਤਾਰਕਿਕ warned = emit_diagnostic_valist (diagnostics::ਕਿਸਮ::error,
					loc, -1, gmsgid, &ap);
  va_ਸਿਰਾ (ap);

  ofwhat = print_spelling ((ਅੱਖਰ *) alloca (spelling_ਲੰਮਾਈ () + 1));
  ਜੇ (*ofwhat && warned)
    inform (loc, "(near initialization for %qs)", ofwhat);
}

/* Used to implement pedwarn_init and permerror_init.  */

ਸਥਿਰ ਤਾਰਕਿਕ ATTRIBUTE_GCC_DIAG (3,0)
pedwarn_permerror_init (location_t loc, ਪੂਰਨ opt, ਅਚਲ ਅੱਖਰ *gmsgid,
			va_list *ap, ਗਿਣਤੀ diagnostics::ਕਿਸਮ ਕਿਸਮ)
{
  /* Use the location where a macro was expanded rather than where
     it was defined to make sure macros defined in system headers
     but used incorrectly elsewhere are diagnosed.  */
  location_t exploc = expansion_ਬਿੰਦੂ_location_if_ਵਿੱਚ_system_ਸਿਰਲੇਖ (loc);
  auto_diagnostic_ਸਮੂਹ d;
  ਤਾਰਕਿਕ warned = emit_diagnostic_valist (ਕਿਸਮ, exploc, opt, gmsgid, ap);
  ਜੇ (warned)
    {
      ਅੱਖਰ *ofwhat = print_spelling ((ਅੱਖਰ *) alloca (spelling_ਲੰਮਾਈ () + 1));
      ਜੇ (*ofwhat)
	inform (exploc, "(near initialization for %qs)", ofwhat);
    }
  ਵਾਪਸ warned;
}

/* Issue a pedantic warning for a bad initializer component.  OPT is
   the option OPT_* (from options.h) controlling this warning or 0 if
   it is unconditionally given.  GMSGID identifies the message.  The
   component name is taken from the spelling stack.  */

ਸਥਿਰ ਤਾਰਕਿਕ ATTRIBUTE_GCC_DIAG (3,0)
pedwarn_init (location_t loc, ਪੂਰਨ opt, ਅਚਲ ਅੱਖਰ *gmsgid, ...)
{
  va_list ap;
  va_ਸ਼ੁਰੂ (ap, gmsgid);
  ਤਾਰਕਿਕ warned = pedwarn_permerror_init (loc, opt, gmsgid, &ap,
					diagnostics::ਕਿਸਮ::pedwarn);
  va_ਸਿਰਾ (ap);
  ਵਾਪਸ warned;
}

/* Like pedwarn_init, but issue a permerror.  */

ਸਥਿਰ ਤਾਰਕਿਕ ATTRIBUTE_GCC_DIAG (3,0)
permerror_init (location_t loc, ਪੂਰਨ opt, ਅਚਲ ਅੱਖਰ *gmsgid, ...)
{
  va_list ap;
  va_ਸ਼ੁਰੂ (ap, gmsgid);
  ਤਾਰਕਿਕ warned = pedwarn_permerror_init (loc, opt, gmsgid, &ap,
					diagnostics::ਕਿਸਮ::permerror);
  va_ਸਿਰਾ (ap);
  ਵਾਪਸ warned;
}

/* Issue a warning for a bad initializer component.

   OPT is the OPT_W* value corresponding to the warning option that
   controls this warning.  GMSGID identifies the message.  The
   component name is taken from the spelling stack.  */

ਸਥਿਰ ਖਾਲੀ
warning_init (location_t loc, ਪੂਰਨ opt, ਅਚਲ ਅੱਖਰ *gmsgid)
{
  ਅੱਖਰ *ofwhat;
  ਤਾਰਕਿਕ warned;

  auto_diagnostic_ਸਮੂਹ d;

  /* Use the location where a macro was expanded rather than where
     it was defined to make sure macros defined in system headers
     but used incorrectly elsewhere are diagnosed.  */
  location_t exploc = expansion_ਬਿੰਦੂ_location_if_ਵਿੱਚ_system_ਸਿਰਲੇਖ (loc);

  /* The gmsgid may be a format string with %< and %>. */
  warned = warning_at (exploc, opt, gmsgid);
  ਜੇ (warned)
    {
      ofwhat = print_spelling ((ਅੱਖਰ *) alloca (spelling_ਲੰਮਾਈ () + 1));
      ਜੇ (*ofwhat)
	inform (exploc, "(near initialization for %qs)", ofwhat);
    }
}

/* If TYPE is an array type and EXPR is a parenthesized string
   constant, warn if pedantic that EXPR is being used to initialize an
   object of type TYPE.  */

ਖਾਲੀ
maybe_warn_string_init (location_t loc, ਰੁੱਖ type, ਬਣਤਰ c_ਵਿਅੰਜਕ ਵਿਅੰਜਕ)
{
  ਜੇ (pedantic
      && ਰੁੱਖ_ਕੋਡ (type) == ARRAY_TYPE
      && ਰੁੱਖ_ਕੋਡ (ਵਿਅੰਜਕ.ਮੁੱਲ) == STRING_CST
      && ਵਿਅੰਜਕ.original_ਕੋਡ != STRING_CST)
    pedwarn_init (loc, OPT_Wpedantic,
		  "array initialized from parenthesized string constant");
}

/* Attempt to locate the parameter with the given index within FNDECL,
   returning DECL_SOURCE_LOCATION (FNDECL) if it can't be found.  */

ਸਥਿਰ location_t
get_fndecl_ਦਲੀਲ_location (ਰੁੱਖ fndecl, ਪੂਰਨ argnum)
{
  ਪੂਰਨ i;
  ਰੁੱਖ param;

  /* Locate param by index within DECL_ARGUMENTS (fndecl).  */
  ਲਈ (i = 0, param = DECL_ARGUMENTS (fndecl);
       i < argnum && param;
       i++, param = ਰੁੱਖ_CHAIN (param))
    ;

  /* If something went wrong (e.g. if we have a builtin and thus no arguments),
     return DECL_SOURCE_LOCATION (FNDECL).  */
  ਜੇ (param == ਨਿਰਾ)
    ਵਾਪਸ DECL_ਸਰੋਤ_LOCATION (fndecl);

  ਵਾਪਸ DECL_ਸਰੋਤ_LOCATION (param);
}

/* Issue a note about a mismatching argument for parameter PARMNUM
   to FUNDECL, for types EXPECTED_TYPE and ACTUAL_TYPE.
   Attempt to issue the note at the pertinent parameter of the decl;
   failing that issue it at the location of FUNDECL; failing that
   issue it at PLOC.
   Use highlight_colors::actual for the ACTUAL_TYPE
   and highlight_colors::expected for EXPECTED_TYPE and the
   parameter of FUNDECL*/

ਸਥਿਰ ਖਾਲੀ
inform_for_arg (ਰੁੱਖ fundecl, location_t ploc, ਪੂਰਨ parmnum,
		ਰੁੱਖ expected_type, ਰੁੱਖ actual_type)
{
  location_t loc;
  ਜੇ (fundecl && !DECL_IS_UNDECLARED_BUILTIN (fundecl))
    loc = get_fndecl_ਦਲੀਲ_location (fundecl, parmnum - 1);
  ਨਹੀਂਤਾਂ
    loc = ploc;

  gcc_rich_location richloc (loc, ਖਾਲੀ_ਸੂਚਕ, highlight_colors::expected);

  pp_markup::element_expected_type elem_expected_type (expected_type);
  pp_markup::element_actual_type elem_actual_type (actual_type);
  inform (&richloc,
	  "expected %e but argument is of type %e",
	  &elem_expected_type, &elem_actual_type);
}

/* Issue a warning when an argument of ARGTYPE is passed to a built-in
   function FUNDECL declared without prototype to parameter PARMNUM of
   PARMTYPE when ARGTYPE does not promote to PARMTYPE.  */

ਸਥਿਰ ਖਾਲੀ
maybe_warn_builtin_no_proto_arg (location_t loc, ਰੁੱਖ fundecl, ਪੂਰਨ parmnum,
				 ਰੁੱਖ parmtype, ਰੁੱਖ argtype)
{
  ਰੁੱਖ_ਕੋਡ_2 parmcode = ਰੁੱਖ_ਕੋਡ (parmtype);
  ਰੁੱਖ_ਕੋਡ_2 argcode = ਰੁੱਖ_ਕੋਡ (argtype);
  ਰੁੱਖ promoted = c_type_promotes_ਮੰਜ਼ਿਲ (argtype);

  /* Avoid warning for enum arguments that promote to an integer type
     of the same size/mode.  */
  ਜੇ (parmcode == INTEGER_TYPE
      && argcode == ENUMERAL_TYPE
      && TYPE_ਬਹੁਲਕ (parmtype) == TYPE_ਬਹੁਲਕ (argtype))
    ਵਾਪਸ;

  ਜੇ ((parmcode == argcode
       || (parmcode == INTEGER_TYPE
	   && argcode == ENUMERAL_TYPE))
      && TYPE_MAIN_VARIANT (parmtype) == TYPE_MAIN_VARIANT (promoted))
    ਵਾਪਸ;

  /* This diagnoses even signed/unsigned mismatches.  Those might be
     safe in many cases but GCC may emit suboptimal code for them so
     warning on those cases drives efficiency improvements.  */
  ਜੇ (warning_at (loc, OPT_Wbuiltin_declaration_mismatch,
		  TYPE_MAIN_VARIANT (promoted) == argtype
		  ? G_("%qD argument %d type is %qT where %qT is expected "
		       "in a call to built-in function declared without "
		       "prototype")
		  : G_("%qD argument %d promotes to %qT where %qT is expected "
		       "in a call to built-in function declared without "
		       "prototype"),
		  fundecl, parmnum, promoted, parmtype))
    inform (DECL_ਸਰੋਤ_LOCATION (fundecl),
	    "built-in %qD declared here",
	    fundecl);
}

/* Print a declaration in quotes, with the given highlight_color.
   Analogous to handler for %qD, but with a specific highlight color.  */

ਵਰਗ pp_element_quoted_decl : ਜਨਤਕ pp_element
{
ਜਨਤਕ:
  pp_element_quoted_decl (ਰੁੱਖ decl, ਅਚਲ ਅੱਖਰ *highlight_color)
  : m_decl (decl),
    m_highlight_color (highlight_color)
  {
  }

  ਖਾਲੀ ਜੋੜੋ_ਮੰਜ਼ਿਲ_phase_2 (pp_markup::context &ctxt) override
  {
    ctxt.begin_quote ();
    ctxt.begin_highlight_color (m_highlight_color);

    print_decl (ctxt);

    ctxt.ਸਿਰਾ_highlight_color ();
    ctxt.ਸਿਰਾ_quote ();
  }

  ਖਾਲੀ print_decl (pp_markup::context &ctxt)
  {
    pretty_printer *ਅਚਲ pp = &ctxt.m_pp;
    pp->ਸੈੱਟ_padding (pp_none);
    ਜੇ (DECL_NAME (m_decl))
      pp_identifier (pp, lang_hooks.decl_printable_name (m_decl, 2));
    ਨਹੀਂਤਾਂ
      pp_string (pp, _("({anonymous})"));
  }

ਨਿਜੀ:
  ਰੁੱਖ m_decl;
  ਅਚਲ ਅੱਖਰ *m_highlight_color;
};

/* If TYPE is from a typedef, issue a note showing the location
   to the user.
   Use HIGHLIGHT_COLOR as the highlight color.  */

ਸਥਿਰ ਖਾਲੀ
maybe_inform_typedef_location (ਰੁੱਖ type, ਅਚਲ ਅੱਖਰ *highlight_color)
{
  ਜੇ (!typedef_variant_p (type))
    ਵਾਪਸ;

  ਰੁੱਖ typedef_decl = TYPE_NAME (type);
  gcc_assert (ਰੁੱਖ_ਕੋਡ (typedef_decl) == TYPE_DECL);
  gcc_rich_location richloc (DECL_ਸਰੋਤ_LOCATION (typedef_decl),
			     ਖਾਲੀ_ਸੂਚਕ, highlight_color);
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

ਸਥਿਰ ਰੁੱਖ
convert_for_assignment (location_t location, location_t ਵਿਅੰਜਕ_loc, ਰੁੱਖ type,
			ਰੁੱਖ rhs, ਰੁੱਖ origtype, ਗਿਣਤੀ impl_conv errtype,
			ਤਾਰਕਿਕ null_ਸੂਚਕ_constant, ਰੁੱਖ fundecl,
			ਰੁੱਖ function, ਪੂਰਨ parmnum, ਪੂਰਨ warnopt /* = 0 */)
{
  ਗਿਣਤੀ ਰੁੱਖ_ਕੋਡ_2 codel = ਰੁੱਖ_ਕੋਡ (type);
  ਰੁੱਖ orig_rhs = rhs;
  ਰੁੱਖ rhstype;
  ਗਿਣਤੀ ਰੁੱਖ_ਕੋਡ_2 coder;
  ਰੁੱਖ rname = NULL_ਰੁੱਖ;
  ਤਾਰਕਿਕ objc_ok = ਝੂਠ;

  /* Use the expansion point location to handle cases such as user's
     function returning a wrong-type macro defined in a system header.  */
  location = expansion_ਬਿੰਦੂ_location_if_ਵਿੱਚ_system_ਸਿਰਲੇਖ (location);

  ਜੇ (errtype == ic_argpass)
    {
      ਰੁੱਖ selector;
      /* Change pointer to function to the function itself for
	 diagnostics.  */
      ਜੇ (ਰੁੱਖ_ਕੋਡ (function) == ADDR_ਵਿਅੰਜਕ
	  && ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_ਸੰਕਾਰਜ (function, 0)) == FUNCTION_DECL)
	function = ਰੁੱਖ_ਸੰਕਾਰਜ (function, 0);

      /* Handle an ObjC selector specially for diagnostics.  */
      selector = objc_ਸੁਨੇਹਾ_selector ();
      rname = function;
      ਜੇ (selector && parmnum > 2)
	{
	  rname = selector;
	  parmnum -= 2;
	}
    }

  /* This macro is used to emit diagnostics to ensure that all format
     strings are complete sentences, visible to gettext and checked at
     compile time.  */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PEDWARN_FOR_ASSIGNMENT(LOCATION, PLOC, OPT, AR, AS, ਵਿੱਚ, RE)	 \
  ਕਰੋ {                                                                   \
    ਚੋਣ (errtype)                                                     \
      {                                                                  \
      ਹਾਲਤ ic_argpass:                                                   \
	{								\
	  auto_diagnostic_ਸਮੂਹ d;						\
	  ਜੇ (pedwarn (PLOC, OPT, AR, parmnum, rname))		\
	    inform_for_arg (fundecl, (PLOC), parmnum, type, rhstype); \
	}								\
        ਰੋਕੋ;                                                           \
      ਹਾਲਤ ic_ਸੌਂਪੋ:                                                    \
        pedwarn (LOCATION, OPT, AS);                                     \
        ਰੋਕੋ;                                                           \
      ਹਾਲਤ ic_init:                                                      \
      ਹਾਲਤ ic_init_const:                                                \
        pedwarn_init (LOCATION, OPT, ਵਿੱਚ);                                \
        ਰੋਕੋ;                                                           \
      ਹਾਲਤ ic_return:                                                    \
        pedwarn (LOCATION, OPT, RE);					 \
        ਰੋਕੋ;                                                           \
      ਮੂਲ:                                                           \
        gcc_unreachable ();                                              \
      }                                                                  \
  } ਜਦੋਂ (0)

  /* This macro is used to emit diagnostics to ensure that all format
     strings are complete sentences, visible to gettext and checked at
     compile time.  It can be called with 'pedwarn' or 'warning_at'.  */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WARNING_FOR_QUALIFIERS(PEDWARN, LOCATION, PLOC, OPT, AR, AS, ਵਿੱਚ, RE, QUALS) \
  ਕਰੋ {                                                                   \
    ਚੋਣ (errtype)                                                     \
      {                                                                  \
      ਹਾਲਤ ic_argpass:                                                   \
	{								 \
	  auto_diagnostic_ਸਮੂਹ d;					 \
	  ਜੇ (PEDWARN) {						 \
	    ਜੇ (pedwarn (PLOC, OPT, AR, parmnum, rname, QUALS))          \
	      inform_for_arg (fundecl, (PLOC), parmnum, type, rhstype);  \
	  } ਨਹੀਂਤਾਂ {							 \
	    ਜੇ (warning_at (PLOC, OPT, AR, parmnum, rname, QUALS))	 \
	      inform_for_arg (fundecl, (PLOC), parmnum, type, rhstype);  \
	  }								 \
	}								 \
        ਰੋਕੋ;                                                           \
      ਹਾਲਤ ic_ਸੌਂਪੋ:                                                    \
	ਜੇ (PEDWARN)							 \
	  pedwarn (LOCATION, OPT, AS, QUALS);                            \
	ਨਹੀਂਤਾਂ								 \
	  warning_at (LOCATION, OPT, AS, QUALS);                         \
        ਰੋਕੋ;                                                           \
      ਹਾਲਤ ic_init:                                                      \
      ਹਾਲਤ ic_init_const:                                                \
	ਜੇ (PEDWARN)							 \
	  pedwarn (LOCATION, OPT, ਵਿੱਚ, QUALS);                            \
	ਨਹੀਂਤਾਂ								 \
	  warning_at (LOCATION, OPT, ਵਿੱਚ, QUALS);                         \
        ਰੋਕੋ;                                                           \
      ਹਾਲਤ ic_return:                                                    \
	ਜੇ (PEDWARN)							 \
	  pedwarn (LOCATION, OPT, RE, QUALS);                            \
	ਨਹੀਂਤਾਂ								 \
	  warning_at (LOCATION, OPT, RE, QUALS);                         \
        ਰੋਕੋ;                                                           \
      ਮੂਲ:                                                           \
        gcc_unreachable ();                                              \
      }                                                                  \
  } ਜਦੋਂ (0)

  /* This macro is used to emit diagnostics to ensure that all format
     strings are complete sentences, visible to gettext and checked at
     compile time.  It is the same as PEDWARN_FOR_ASSIGNMENT but with an
     extra parameter to enumerate qualifiers.  */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PEDWARN_FOR_QUALIFIERS(LOCATION, PLOC, OPT, AR, AS, ਵਿੱਚ, RE, QUALS) \
   WARNING_FOR_QUALIFIERS (ਸੱਚ, LOCATION, PLOC, OPT, AR, AS, ਵਿੱਚ, RE, QUALS)


  ਜੇ (ਰੁੱਖ_ਕੋਡ (rhs) == EXCESS_PRECISION_ਵਿਅੰਜਕ)
    rhs = ਰੁੱਖ_ਸੰਕਾਰਜ (rhs, 0);

  rhstype = ਰੁੱਖ_TYPE (rhs);
  coder = ਰੁੱਖ_ਕੋਡ (rhstype);

  ਜੇ (coder == ERROR_MARK)
    ਵਾਪਸ error_mark_ਗੰਢ;

  ਜੇ (c_dialect_objc ())
    {
      ਪੂਰਨ parmno;

      ਚੋਣ (errtype)
	{
	ਹਾਲਤ ic_return:
	  parmno = 0;
	  ਰੋਕੋ;

	ਹਾਲਤ ic_ਸੌਂਪੋ:
	  parmno = -1;
	  ਰੋਕੋ;

	ਹਾਲਤ ic_init:
	ਹਾਲਤ ic_init_const:
	  parmno = -2;
	  ਰੋਕੋ;

	ਮੂਲ:
	  parmno = parmnum;
	  ਰੋਕੋ;
	}

      objc_ok = objc_compare_types (type, rhstype, parmno, rname);
    }

  ਜੇ (warn_cxx_compat)
    {
      ਰੁੱਖ checktype = origtype != NULL_ਰੁੱਖ ? origtype : rhstype;
      ਜੇ (checktype != error_mark_ਗੰਢ
	  && ਰੁੱਖ_ਕੋਡ (type) == ENUMERAL_TYPE
	  && TYPE_MAIN_VARIANT (checktype) != TYPE_MAIN_VARIANT (type))
	ਚੋਣ (errtype)
	  {
	  ਹਾਲਤ ic_argpass:
	    ਜੇ (pedwarn (ਵਿਅੰਜਕ_loc, OPT_Wc___compat, "enum conversion when "
			 "passing argument %d of %qE is invalid in C++",
			 parmnum, rname))
	      inform ((fundecl && !DECL_IS_UNDECLARED_BUILTIN (fundecl))
		      ? DECL_ਸਰੋਤ_LOCATION (fundecl) : ਵਿਅੰਜਕ_loc,
		      "expected %qT but argument is of type %qT",
		      type, rhstype);
	    ਰੋਕੋ;
	  ਹਾਲਤ ic_ਸੌਂਪੋ:
	    pedwarn (location, OPT_Wc___compat, "enum conversion from %qT to "
		     "%qT in assignment is invalid in C++", rhstype, type);
	    ਰੋਕੋ;
	  ਹਾਲਤ ic_init:
	  ਹਾਲਤ ic_init_const:
	    pedwarn_init (location, OPT_Wc___compat, "enum conversion from "
			  "%qT to %qT in initialization is invalid in C++",
			  rhstype, type);
	    ਰੋਕੋ;
	  ਹਾਲਤ ic_return:
	    pedwarn (location, OPT_Wc___compat, "enum conversion from %qT to "
		     "%qT in return is invalid in C++", rhstype, type);
	    ਰੋਕੋ;
	  ਮੂਲ:
	    gcc_unreachable ();
	  }
    }

  ਜੇ (warn_enum_conversion)
    {
      ਰੁੱਖ checktype = origtype != NULL_ਰੁੱਖ ? origtype : rhstype;
      ਜੇ (checktype != error_mark_ਗੰਢ
	  && ਰੁੱਖ_ਕੋਡ (checktype) == ENUMERAL_TYPE
	  && ਰੁੱਖ_ਕੋਡ (type) == ENUMERAL_TYPE
	  && !comptypes (TYPE_MAIN_VARIANT (checktype), TYPE_MAIN_VARIANT (type)))
       {
	  gcc_rich_location loc (location);
	  warning_at (&loc, OPT_Wenum_conversion,
		      "implicit conversion from %qT to %qT",
		      checktype, type);
       }
    }

  ਜੇ (TYPE_MAIN_VARIANT (type) == TYPE_MAIN_VARIANT (rhstype))
    {
      warn_for_ਪਤਾ_ਦਾ_packed_member (type, orig_rhs);
      ਜੇ (type != rhstype)
	/* Convert RHS to TYPE in order to not lose TYPE in diagnostics.  */
	rhs = convert (type, rhs);
      ਵਾਪਸ rhs;
    }

  ਜੇ (coder == VOID_TYPE)
    {
      /* Except for passing an argument to an unprototyped function,
	 this is a constraint violation.  When passing an argument to
	 an unprototyped function, it is compile-time undefined;
	 making it a constraint in that case was rejected in
	 DR#252.  */
      ਅਚਲ ਅੱਖਰ ਸੁਨੇਹਾ_2[] = "void value not ignored as it ought to be";
      ਜੇ (warnopt)
	warning_at (location, warnopt, ਸੁਨੇਹਾ_2);
      ਨਹੀਂਤਾਂ
	error_at (location, ਸੁਨੇਹਾ_2);
      ਵਾਪਸ error_mark_ਗੰਢ;
    }
  rhs = require_complete_type (location, rhs);
  ਜੇ (rhs == error_mark_ਗੰਢ)
    ਵਾਪਸ error_mark_ਗੰਢ;

  ਜੇ (coder == ਸੂਚਕ_TYPE && reject_gcc_builtin (rhs))
    ਵਾਪਸ error_mark_ਗੰਢ;

  /* A non-reference type can convert to a reference.  This handles
     va_start, va_copy and possibly port built-ins.  */
  ਜੇ (codel == REFERENCE_TYPE && coder != REFERENCE_TYPE)
    {
      ਜੇ (!lvalue_p (rhs))
	{
	  ਅਚਲ ਅੱਖਰ ਸੁਨੇਹਾ_2[] = "cannot pass rvalue to reference parameter";
	  ਜੇ (warnopt)
	    warning_at (location, warnopt, ਸੁਨੇਹਾ_2);
	  ਨਹੀਂਤਾਂ
	    error_at (location, ਸੁਨੇਹਾ_2);
	  ਵਾਪਸ error_mark_ਗੰਢ;
	}
      ਜੇ (!c_mark_addressable (rhs))
	ਵਾਪਸ error_mark_ਗੰਢ;
      rhs = build1 (ADDR_ਵਿਅੰਜਕ, c_build_ਸੂਚਕ_type (ਰੁੱਖ_TYPE (rhs)), rhs);
      ਸੈੱਟ_ਵਿਅੰਜਕ_LOCATION (rhs, location);

      rhs = convert_for_assignment (location, ਵਿਅੰਜਕ_loc,
				    c_build_ਸੂਚਕ_type (ਰੁੱਖ_TYPE (type)),
				    rhs, origtype, errtype,
				    null_ਸੂਚਕ_constant, fundecl, function,
				    parmnum, warnopt);
      ਜੇ (rhs == error_mark_ਗੰਢ)
	ਵਾਪਸ error_mark_ਗੰਢ;

      rhs = build1 (NOP_ਵਿਅੰਜਕ, type, rhs);
      ਸੈੱਟ_ਵਿਅੰਜਕ_LOCATION (rhs, location);
      ਵਾਪਸ rhs;
    }
  /* Some types can interconvert without explicit casts.  */
  ਨਹੀਂਤਾਂ ਜੇ (codel == ਸਦਿਸ਼_TYPE && coder == ਸਦਿਸ਼_TYPE
	   && ਸਦਿਸ਼_types_convertible_p (type, ਰੁੱਖ_TYPE (rhs), ਸੱਚ))
    ਵਾਪਸ convert (type, rhs);
  /* Arithmetic types all interconvert, and enum is treated like int.  */
  ਨਹੀਂਤਾਂ ਜੇ ((codel == INTEGER_TYPE || codel == REAL_TYPE
	    || codel == FIXED_ਬਿੰਦੂ_TYPE
	    || codel == ENUMERAL_TYPE || codel == COMPLEX_TYPE
	    || codel == BOOLEAN_TYPE || codel == BITINT_TYPE)
	   && (coder == INTEGER_TYPE || coder == REAL_TYPE
	       || coder == FIXED_ਬਿੰਦੂ_TYPE
	       || coder == ENUMERAL_TYPE || coder == COMPLEX_TYPE
	       || coder == BOOLEAN_TYPE || coder == BITINT_TYPE))
    {
      ਜੇ (warnopt && errtype == ic_argpass)
	maybe_warn_builtin_no_proto_arg (ਵਿਅੰਜਕ_loc, fundecl, parmnum, type,
					 rhstype);

      ਤਾਰਕਿਕ save = ਵਿੱਚ_late_ਦੁਆਧਾਰੀ_op;
      ਜੇ (C_BOOLEAN_TYPE_P (type) || codel == COMPLEX_TYPE
	  || (coder == REAL_TYPE
	      && (codel == INTEGER_TYPE || codel == ENUMERAL_TYPE)
	      && sanitize_flags_p (SANITIZE_FLOAT_CAST)))
	ਵਿੱਚ_late_ਦੁਆਧਾਰੀ_op = ਸੱਚ;
      ਰੁੱਖ ret = convert_and_check (ਵਿਅੰਜਕ_loc != UNKNOWN_LOCATION
				    ? ਵਿਅੰਜਕ_loc : location, type, orig_rhs,
				    errtype == ic_init_const);
      ਵਿੱਚ_late_ਦੁਆਧਾਰੀ_op = save;
      ਵਾਪਸ ret;
    }

  /* Aggregates in different TUs might need conversion.  */
  ਜੇ ((codel == ਰਿਕਾਰਡ_TYPE || codel == UNION_TYPE)
      && codel == coder
      && comptypes (TYPE_MAIN_VARIANT (type), TYPE_MAIN_VARIANT (rhstype)))
    ਵਾਪਸ convert_and_check (ਵਿਅੰਜਕ_loc != UNKNOWN_LOCATION
			      ? ਵਿਅੰਜਕ_loc : location, type, rhs);

  /* Conversion to a transparent union or record from its member types.
     This applies only to function arguments.  */
  ਜੇ (((codel == UNION_TYPE || codel == ਰਿਕਾਰਡ_TYPE)
      && TYPE_TRANSPARENT_AGGR (type))
      && errtype == ic_argpass)
    {
      ਰੁੱਖ memb, marginal_memb = NULL_ਰੁੱਖ;

      ਲਈ (memb = TYPE_FIELDS (type); memb ; memb = DECL_CHAIN (memb))
	{
	  ਰੁੱਖ memb_type = ਰੁੱਖ_TYPE (memb);

	  ਜੇ (comptypes (TYPE_MAIN_VARIANT (memb_type),
			 TYPE_MAIN_VARIANT (rhstype)))
	    ਰੋਕੋ;

	  ਜੇ (ਰੁੱਖ_ਕੋਡ (memb_type) != ਸੂਚਕ_TYPE)
	    ਜਾਰੀ;

	  ਜੇ (coder == ਸੂਚਕ_TYPE)
	    {
	      ਰੁੱਖ ttl = ਰੁੱਖ_TYPE (memb_type);
	      ਰੁੱਖ ttr = ਰੁੱਖ_TYPE (rhstype);

	      /* Any non-function converts to a [const][volatile] void *
		 and vice versa; otherwise, targets must be the same.
		 Meanwhile, the lhs target must have all the qualifiers of
		 the rhs.  */
	      ਜੇ ((VOID_TYPE_P (ttl) && !TYPE_ATOMIC (ttl))
		  || (VOID_TYPE_P (ttr) && !TYPE_ATOMIC (ttr))
		  || comp_ਨਿਸ਼ਾਨਾ_types (location, memb_type, rhstype))
		{
		  ਪੂਰਨ lquals = TYPE_QUALS (ttl) & ~TYPE_QUAL_ATOMIC;
		  ਪੂਰਨ rquals = TYPE_QUALS (ttr) & ~TYPE_QUAL_ATOMIC;
		  /* If this type won't generate any warnings, use it.  */
		  ਜੇ (lquals == rquals
		      || ((ਰੁੱਖ_ਕੋਡ (ttr) == FUNCTION_TYPE
			   && ਰੁੱਖ_ਕੋਡ (ttl) == FUNCTION_TYPE)
			  ? ((lquals | rquals) == rquals)
			  : ((lquals | rquals) == lquals)))
		    ਰੋਕੋ;

		  /* Keep looking for a better type, but remember this one.  */
		  ਜੇ (!marginal_memb)
		    marginal_memb = memb;
		}
	    }

	  /* Can convert integer zero to any pointer type.  */
	  ਜੇ (null_ਸੂਚਕ_constant)
	    {
	      rhs = null_ਸੂਚਕ_ਗੰਢ;
	      ਰੋਕੋ;
	    }
	}

      ਜੇ (memb || marginal_memb)
	{
	  ਜੇ (!memb)
	    {
	      /* We have only a marginally acceptable member type;
		 it needs a warning.  */
	      ਰੁੱਖ ttl = ਰੁੱਖ_TYPE (ਰੁੱਖ_TYPE (marginal_memb));
	      ਰੁੱਖ ttr = ਰੁੱਖ_TYPE (rhstype);

	      /* Const and volatile mean something different for function
		 types, so the usual warnings are not appropriate.  */
	      ਜੇ (ਰੁੱਖ_ਕੋਡ (ttr) == FUNCTION_TYPE
		  && ਰੁੱਖ_ਕੋਡ (ttl) == FUNCTION_TYPE)
		{
		  /* Because const and volatile on functions are
		     restrictions that say the function will not do
		     certain things, it is okay to use a const or volatile
		     function where an ordinary one is wanted, but not
		     vice-versa.  */
		  ਜੇ (TYPE_QUALS_NO_ADDR_SPACE (ttl)
		      & ~TYPE_QUALS_NO_ADDR_SPACE (ttr))
		    PEDWARN_FOR_QUALIFIERS (location, ਵਿਅੰਜਕ_loc,
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
	      ਨਹੀਂਤਾਂ ਜੇ (TYPE_QUALS_NO_ADDR_SPACE (ttr)
		       & ~TYPE_QUALS_NO_ADDR_SPACE (ttl))
		PEDWARN_FOR_QUALIFIERS (location, ਵਿਅੰਜਕ_loc,
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

	  ਜੇ (!fundecl || !DECL_ਵਿੱਚ_SYSTEM_ਸਿਰਲੇਖ (fundecl))
	    pedwarn (location, OPT_Wpedantic,
		     "ISO C prohibits argument conversion to union type");

	  rhs = fold_convert_loc (location, ਰੁੱਖ_TYPE (memb), rhs);
	  ਵਾਪਸ build_constructor_single (type, memb, rhs);
	}
    }

  /* Conversions among pointers */
  ਨਹੀਂਤਾਂ ਜੇ ((codel == ਸੂਚਕ_TYPE || codel == REFERENCE_TYPE)
	   && (coder == codel))
    {
      /* If RHS refers to a built-in declared without a prototype
	 BLTIN is the declaration of the built-in with a prototype
	 and RHSTYPE is set to the actual type of the built-in.  */
      ਰੁੱਖ bltin;
      rhstype = type_or_builtin_type (rhs, &bltin);

      ਰੁੱਖ ttl = ਰੁੱਖ_TYPE (type);
      ਰੁੱਖ ttr = ਰੁੱਖ_TYPE (rhstype);
      ਤਾਰਕਿਕ is_opaque_ਸੂਚਕ;
      ਤਾਰਕਿਕ ਨਿਸ਼ਾਨਾ_cmp = ਝੂਠ;   /* Cache comp_target_types () result.  */
      addr_space_t asl;
      addr_space_t asr;

      ਰੁੱਖ mvl = remove_qualifiers (ttl);
      ਰੁੱਖ mvr = remove_qualifiers (ttr);

      /* Opaque pointers are treated like void pointers.  */
      is_opaque_ਸੂਚਕ = ਸਦਿਸ਼_targets_convertible_p (ttl, ttr);

      /* The Plan 9 compiler permits a pointer to a struct to be
	 automatically converted into a pointer to an anonymous field
	 within the struct.  */
      ਜੇ (flag_plan9_extensions
	  && ਰਿਕਾਰਡ_OR_UNION_TYPE_P (mvl)
	  && ਰਿਕਾਰਡ_OR_UNION_TYPE_P (mvr)
	  && mvl != mvr)
	{
	  ਰੁੱਖ new_rhs = convert_ਮੰਜ਼ਿਲ_anonymous_ਖੇਤਰ (location, type, rhs);
	  ਜੇ (new_rhs != NULL_ਰੁੱਖ)
	    {
	      rhs = new_rhs;
	      rhstype = ਰੁੱਖ_TYPE (rhs);
	      coder = ਰੁੱਖ_ਕੋਡ (rhstype);
	      ttr = ਰੁੱਖ_TYPE (rhstype);
	      mvr = TYPE_MAIN_VARIANT (ttr);
	    }
	}

      /* C++ does not allow the implicit conversion void* -> T*.  However,
	 for the purpose of reducing the number of false positives, we
	 tolerate the special case of

		int *p = NULL;

	 where NULL is typically defined in C to be '(void *) 0'.  */
      ਜੇ (VOID_TYPE_P (ttr) && rhs != null_ਸੂਚਕ_ਗੰਢ && !VOID_TYPE_P (ttl))
	warning_at (errtype == ic_argpass ? ਵਿਅੰਜਕ_loc : location,
		    OPT_Wc___compat,
		    "request for implicit conversion "
		    "from %qT to %qT not permitted in C++", rhstype, type);

      /* Warn of new allocations that are not big enough for the target
	 type.  */
      ਜੇ (warn_alloc_ਮਾਪ && ਰੁੱਖ_ਕੋਡ (rhs) == CALL_ਵਿਅੰਜਕ)
	ਜੇ (ਰੁੱਖ fndecl = get_callee_fndecl (rhs))
	  ਜੇ (DECL_IS_MALLOC (fndecl))
	    {
	      ਰੁੱਖ attrs = TYPE_ਗੁਣ (ਰੁੱਖ_TYPE (fndecl));
	      ਰੁੱਖ alloc_ਮਾਪ = lookup_attribute ("alloc_size", attrs);
	      ਜੇ (alloc_ਮਾਪ)
		warn_for_alloc_ਮਾਪ (location, ttl, rhs, alloc_ਮਾਪ);
	    }

      /* See if the pointers point to incompatible address spaces.  */
      asl = TYPE_ADDR_SPACE (ttl);
      asr = TYPE_ADDR_SPACE (ttr);
      ਜੇ (!null_ਸੂਚਕ_constant_p (rhs)
	  && asr != asl && !targetm.addr_space.subset_p (asr, asl))
	{
	  auto_diagnostic_ਸਮੂਹ d;
	  ਤਾਰਕਿਕ diagnosed = ਸੱਚ;
	  ਚੋਣ (errtype)
	    {
	    ਹਾਲਤ ic_argpass:
	      {
		ਅਚਲ ਅੱਖਰ ਸੁਨੇਹਾ_2[] = G_("passing argument %d of %qE from "
				      "pointer to non-enclosed address space");
		ਜੇ (warnopt)
		  diagnosed
		    = warning_at (ਵਿਅੰਜਕ_loc, warnopt, ਸੁਨੇਹਾ_2, parmnum, rname);
		ਨਹੀਂਤਾਂ
		  error_at (ਵਿਅੰਜਕ_loc, ਸੁਨੇਹਾ_2, parmnum, rname);
	      ਰੋਕੋ;
	      }
	    ਹਾਲਤ ic_ਸੌਂਪੋ:
	      {
		ਅਚਲ ਅੱਖਰ ਸੁਨੇਹਾ_2[] = G_("assignment from pointer to "
				      "non-enclosed address space");
		ਜੇ (warnopt)
		  diagnosed = warning_at (location, warnopt, ਸੁਨੇਹਾ_2);
		ਨਹੀਂਤਾਂ
		  error_at (location, ਸੁਨੇਹਾ_2);
		ਰੋਕੋ;
	      }
	    ਹਾਲਤ ic_init:
	    ਹਾਲਤ ic_init_const:
	      {
		ਅਚਲ ਅੱਖਰ ਸੁਨੇਹਾ_2[] = G_("initialization from pointer to "
				      "non-enclosed address space");
		ਜੇ (warnopt)
		  diagnosed = warning_at (location, warnopt, ਸੁਨੇਹਾ_2);
		ਨਹੀਂਤਾਂ
		  error_at (location, ਸੁਨੇਹਾ_2);
		ਰੋਕੋ;
	      }
	    ਹਾਲਤ ic_return:
	      {
		ਅਚਲ ਅੱਖਰ ਸੁਨੇਹਾ_2[] = G_("return from pointer to "
				      "non-enclosed address space");
		ਜੇ (warnopt)
		  diagnosed = warning_at (location, warnopt, ਸੁਨੇਹਾ_2);
		ਨਹੀਂਤਾਂ
		  error_at (location, ਸੁਨੇਹਾ_2);
		ਰੋਕੋ;
	      }
	    ਮੂਲ:
	      gcc_unreachable ();
	    }
	  ਜੇ (diagnosed)
	    {
	      ਜੇ (errtype == ic_argpass)
		inform_for_arg (fundecl, ਵਿਅੰਜਕ_loc, parmnum, type, rhstype);
	      ਨਹੀਂਤਾਂ
		inform (location, "expected %qT but pointer is of type %qT",
			type, rhstype);
	    }
	  ਵਾਪਸ error_mark_ਗੰਢ;
	}

      /* Check if the right-hand side has a format attribute but the
	 left-hand side doesn't.  */
      ਜੇ (warn_suggest_attribute_format
	  && check_missing_format_attribute (type, rhstype))
	{
	  ਚੋਣ (errtype)
	  {
	  ਹਾਲਤ ic_argpass:
	    warning_at (ਵਿਅੰਜਕ_loc, OPT_Wsuggest_attribute_format,
			"argument %d of %qE might be "
			"a candidate for a format attribute",
			parmnum, rname);
	    ਰੋਕੋ;
	  ਹਾਲਤ ic_ਸੌਂਪੋ:
	    warning_at (location, OPT_Wsuggest_attribute_format,
			"assignment left-hand side might be "
			"a candidate for a format attribute");
	    ਰੋਕੋ;
	  ਹਾਲਤ ic_init:
	  ਹਾਲਤ ic_init_const:
	    warning_at (location, OPT_Wsuggest_attribute_format,
			"initialization left-hand side might be "
			"a candidate for a format attribute");
	    ਰੋਕੋ;
	  ਹਾਲਤ ic_return:
	    warning_at (location, OPT_Wsuggest_attribute_format,
			"return type might be "
			"a candidate for a format attribute");
	    ਰੋਕੋ;
	  ਮੂਲ:
	    gcc_unreachable ();
	  }
	}

      /* See if the pointers point to incompatible scalar storage orders.  */
      ਜੇ (warn_scalar_storage_ਕ੍ਰਮ
	  && !null_ਸੂਚਕ_constant_p (rhs)
	  && (AGGREGATE_TYPE_P (ttl) && TYPE_ਉਲਟ_STORAGE_ਕ੍ਰਮ (ttl))
	     != (AGGREGATE_TYPE_P (ttr) && TYPE_ਉਲਟ_STORAGE_ਕ੍ਰਮ (ttr)))
	{
	  ਰੁੱਖ t;

	  ਚੋਣ (errtype)
	  {
	  ਹਾਲਤ ic_argpass:
	    /* Do not warn for built-in functions, for example memcpy, since we
	       control how they behave and they can be useful in this area.  */
	    ਜੇ (ਰੁੱਖ_ਕੋਡ (rname) != FUNCTION_DECL
		|| !fndecl_built_ਵਿੱਚ_p (rname))
	      warning_at (location, OPT_Wscalar_storage_ਕ੍ਰਮ,
			  "passing argument %d of %qE from incompatible "
			  "scalar storage order", parmnum, rname);
	    ਰੋਕੋ;
	  ਹਾਲਤ ic_ਸੌਂਪੋ:
	    /* Do not warn if the RHS is a call to a function that returns a
	       pointer that is not an alias.  */
	    ਜੇ (ਰੁੱਖ_ਕੋਡ (rhs) != CALL_ਵਿਅੰਜਕ
		|| (t = get_callee_fndecl (rhs)) == NULL_ਰੁੱਖ
		|| !DECL_IS_MALLOC (t))
	      warning_at (location, OPT_Wscalar_storage_ਕ੍ਰਮ,
			  "assignment to %qT from pointer type %qT with "
			  "incompatible scalar storage order", type, rhstype);
	    ਰੋਕੋ;
	  ਹਾਲਤ ic_init:
	  ਹਾਲਤ ic_init_const:
	    /* Likewise.  */
	    ਜੇ (ਰੁੱਖ_ਕੋਡ (rhs) != CALL_ਵਿਅੰਜਕ
		|| (t = get_callee_fndecl (rhs)) == NULL_ਰੁੱਖ
		|| !DECL_IS_MALLOC (t))
	      warning_at (location, OPT_Wscalar_storage_ਕ੍ਰਮ,
			  "initialization of %qT from pointer type %qT with "
			  "incompatible scalar storage order", type, rhstype);
	    ਰੋਕੋ;
	  ਹਾਲਤ ic_return:
	    warning_at (location, OPT_Wscalar_storage_ਕ੍ਰਮ,
			"returning %qT from pointer type with incompatible "
			"scalar storage order %qT", rhstype, type);
	    ਰੋਕੋ;
	  ਮੂਲ:
	    gcc_unreachable ();
	  }
	}

      /* Any non-function converts to a [const][volatile] void *
	 and vice versa; otherwise, targets must be the same.
	 Meanwhile, the lhs target must have all the qualifiers of the rhs.  */
      ਜੇ ((VOID_TYPE_P (ttl) && !TYPE_ATOMIC (ttl))
	  || (VOID_TYPE_P (ttr) && !TYPE_ATOMIC (ttr))
	  || (ਨਿਸ਼ਾਨਾ_cmp = comp_ਨਿਸ਼ਾਨਾ_types (location, type, rhstype))
	  || is_opaque_ਸੂਚਕ
	  || ((c_common_unsigned_type (mvl)
	       == c_common_unsigned_type (mvr))
	      && (c_common_signed_type (mvl)
		  == c_common_signed_type (mvr))
	      && TYPE_ATOMIC (mvl) == TYPE_ATOMIC (mvr)))
	{
	  /* Warn about loss of qualifers from pointers to arrays with
	     qualifiers on the element type. */
	  ਜੇ (ਰੁੱਖ_ਕੋਡ (ttr) == ARRAY_TYPE)
	    {
	      ttr = strip_array_types (ttr);
	      ttl = strip_array_types (ttl);

	      ਜੇ (TYPE_QUALS_NO_ADDR_SPACE_NO_ATOMIC (ttr)
		  & ~TYPE_QUALS_NO_ADDR_SPACE_NO_ATOMIC (ttl))
		WARNING_FOR_QUALIFIERS (flag_isoc23,
					location, ਵਿਅੰਜਕ_loc,
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
          ਨਹੀਂਤਾਂ ਜੇ (pedantic
	      && ((VOID_TYPE_P (ttl) && ਰੁੱਖ_ਕੋਡ (ttr) == FUNCTION_TYPE)
		  ||
		  (VOID_TYPE_P (ttr)
		   && !null_ਸੂਚਕ_constant
		   && ਰੁੱਖ_ਕੋਡ (ttl) == FUNCTION_TYPE)))
	    PEDWARN_FOR_ASSIGNMENT (location, ਵਿਅੰਜਕ_loc, OPT_Wpedantic,
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
	  ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਕੋਡ (ttr) != FUNCTION_TYPE
		   && ਰੁੱਖ_ਕੋਡ (ttl) != FUNCTION_TYPE)
	    {
	       /* Assignments between atomic and non-atomic objects are OK.  */
	       ਤਾਰਕਿਕ warn_quals_ped = TYPE_QUALS_NO_ADDR_SPACE_NO_ATOMIC (ttr)
				     & ~TYPE_QUALS_NO_ADDR_SPACE_NO_ATOMIC (ttl);
	       ਤਾਰਕਿਕ warn_quals = TYPE_QUALS_NO_ADDR_SPACE_NO_ATOMIC (ttr)
				 & ~TYPE_QUALS_NO_ADDR_SPACE_NO_ATOMIC (strip_array_types (ttl));

	      /* Don't warn about loss of qualifier for conversions from
		 qualified void* to pointers to arrays with corresponding
		 qualifier on the element type (except for pedantic before C23). */
	      ਜੇ (warn_quals || (warn_quals_ped && pedantic && !flag_isoc23))
		PEDWARN_FOR_QUALIFIERS (location, ਵਿਅੰਜਕ_loc,
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
	      ਨਹੀਂਤਾਂ ਜੇ (warn_quals_ped)
		pedwarn_c11 (location, OPT_Wc11_c23_compat,
			     "array with qualifier on the element is not qualified before C23");

	      /* If this is not a case of ignoring a mismatch in signedness,
		 no warning.  */
	      ਨਹੀਂਤਾਂ ਜੇ (VOID_TYPE_P (ttl) || VOID_TYPE_P (ttr)
		       || ਨਿਸ਼ਾਨਾ_cmp)
		;
	      /* If there is a mismatch, do warn.  */
	      ਨਹੀਂਤਾਂ ਜੇ (warn_ਸੂਚਕ_sign)
		ਚੋਣ (errtype)
		  {
		  ਹਾਲਤ ic_argpass:
		    {
		      auto_diagnostic_ਸਮੂਹ d;
		      range_label_for_type_mismatch rhs_label (rhstype, type);
		      gcc_rich_location richloc (ਵਿਅੰਜਕ_loc, &rhs_label,
						 highlight_colors::actual);
		      ਜੇ (pedwarn (&richloc, OPT_Wpointer_sign,
				   "pointer targets in passing argument %d of "
				   "%qE differ in signedness", parmnum, rname))
			inform_for_arg (fundecl, ਵਿਅੰਜਕ_loc, parmnum, type,
					rhstype);
		    }
		    ਰੋਕੋ;
		  ਹਾਲਤ ic_ਸੌਂਪੋ:
		    pedwarn (location, OPT_Wpointer_sign,
			     "pointer targets in assignment from %qT to %qT "
			     "differ in signedness", rhstype, type);
		    ਰੋਕੋ;
		  ਹਾਲਤ ic_init:
		  ਹਾਲਤ ic_init_const:
		    pedwarn_init (location, OPT_Wpointer_sign,
				  "pointer targets in initialization of %qT "
				  "from %qT differ in signedness", type,
				  rhstype);
		    ਰੋਕੋ;
		  ਹਾਲਤ ic_return:
		    pedwarn (location, OPT_Wpointer_sign, "pointer targets in "
			     "returning %qT from a function with return type "
			     "%qT differ in signedness", rhstype, type);
		    ਰੋਕੋ;
		  ਮੂਲ:
		    gcc_unreachable ();
		  }
	    }
	  ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਕੋਡ (ttl) == FUNCTION_TYPE
		   && ਰੁੱਖ_ਕੋਡ (ttr) == FUNCTION_TYPE)
	    {
	      /* Because const and volatile on functions are restrictions
		 that say the function will not do certain things,
		 it is okay to use a const or volatile function
		 where an ordinary one is wanted, but not vice-versa.  */
	      ਜੇ (TYPE_QUALS_NO_ADDR_SPACE (ttl)
		  & ~TYPE_QUALS_NO_ADDR_SPACE (ttr))
		PEDWARN_FOR_QUALIFIERS (location, ਵਿਅੰਜਕ_loc,
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
      ਨਹੀਂਤਾਂ ਜੇ (!objc_ok)
	{
	  auto_diagnostic_ਸਮੂਹ d;
	  ਤਾਰਕਿਕ warned = ਝੂਠ;
	  pp_markup::element_expected_type e_type (type);
	  pp_markup::element_actual_type e_rhstype (rhstype);
	  ਚੋਣ (errtype)
	    {
	    ਹਾਲਤ ic_argpass:
	      {
		range_label_for_type_mismatch rhs_label (rhstype, type);
		gcc_rich_location richloc (ਵਿਅੰਜਕ_loc, &rhs_label,
					   highlight_colors::actual);
		warned
		  = permerror_opt (&richloc, OPT_Wincompatible_ਸੂਚਕ_types,
				   "passing argument %d of %qE from "
				   "incompatible pointer type",
				   parmnum, rname);
		ਜੇ (warned)
		  inform_for_arg (fundecl, ਵਿਅੰਜਕ_loc, parmnum, type, rhstype);
	      }
	      ਰੋਕੋ;
	    ਹਾਲਤ ic_ਸੌਂਪੋ:
	      ਜੇ (bltin)
		warned
		  = permerror_opt (location, OPT_Wincompatible_ਸੂਚਕ_types,
				   "assignment to %e from pointer to "
				   "%qD with incompatible type %e",
				   &e_type, bltin, &e_rhstype);
	      ਨਹੀਂਤਾਂ
		warned
		  = permerror_opt (location, OPT_Wincompatible_ਸੂਚਕ_types,
				   "assignment to %e from incompatible "
				   "pointer type %e",
				   &e_type, &e_rhstype);
	      ਰੋਕੋ;
	    ਹਾਲਤ ic_init:
	    ਹਾਲਤ ic_init_const:
	      ਜੇ (bltin)
		warned
		  = permerror_init (location, OPT_Wincompatible_ਸੂਚਕ_types,
				    "initialization of %e from pointer to "
				    "%qD with incompatible type %e",
				    &e_type, bltin, &e_rhstype);
	      ਨਹੀਂਤਾਂ
		warned
		  = permerror_init (location, OPT_Wincompatible_ਸੂਚਕ_types,
				    "initialization of %e from incompatible "
				    "pointer type %e",
				    &e_type, &e_rhstype);
	      ਰੋਕੋ;
	    ਹਾਲਤ ic_return:
	      ਜੇ (bltin)
		warned
		  = permerror_opt (location, OPT_Wincompatible_ਸੂਚਕ_types,
				   "returning pointer to %qD of type %e from "
				   "a function with incompatible type %e",
				   bltin, &e_rhstype, &e_type);
	      ਨਹੀਂਤਾਂ
		warned
		  = permerror_opt (location, OPT_Wincompatible_ਸੂਚਕ_types,
				   "returning %e from a function with "
				   "incompatible return type %e",
				   &e_rhstype, &e_type);
	      ਰੋਕੋ;
	    ਮੂਲ:
	      gcc_unreachable ();
	    }
	  ਜੇ (warned)
	    {
	      /* If the mismatching function type is a pointer to a function,
		 try to show the decl of the function.  */
	      ਜੇ (ਰੁੱਖ_ਕੋਡ (rhs) == ADDR_ਵਿਅੰਜਕ
		  && ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_ਸੰਕਾਰਜ (rhs, 0)) == FUNCTION_DECL)
		{
		  ਰੁੱਖ rhs_fndecl = ਰੁੱਖ_ਸੰਕਾਰਜ (rhs, 0);
		  ਜੇ (!DECL_IS_UNDECLARED_BUILTIN (rhs_fndecl))
		    {
		      gcc_rich_location richloc
			(DECL_ਸਰੋਤ_LOCATION (rhs_fndecl), ਖਾਲੀ_ਸੂਚਕ,
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
      warn_for_ਪਤਾ_ਦਾ_packed_member (type, orig_rhs);

      ਵਾਪਸ convert (type, rhs);
    }
  ਨਹੀਂਤਾਂ ਜੇ (codel == ਸੂਚਕ_TYPE && coder == ARRAY_TYPE)
    {
      /* ??? This should not be an error when inlining calls to
	 unprototyped functions.  */
      ਅਚਲ ਅੱਖਰ ਸੁਨੇਹਾ_2[] = "invalid use of non-lvalue array";
      ਜੇ (warnopt)
	warning_at (location, warnopt, ਸੁਨੇਹਾ_2);
      ਨਹੀਂਤਾਂ
	error_at (location, ਸੁਨੇਹਾ_2);
      ਵਾਪਸ error_mark_ਗੰਢ;
    }
  ਨਹੀਂਤਾਂ ਜੇ (codel == ਸੂਚਕ_TYPE
	   && (coder == INTEGER_TYPE
	       || coder == ENUMERAL_TYPE
	       || coder == BOOLEAN_TYPE
	       || coder == NULLPTR_TYPE
	       || coder == BITINT_TYPE))
    {
      ਜੇ (null_ਸੂਚਕ_constant && c_inhibit_evaluation_warnings == 0
	  && coder != NULLPTR_TYPE)
	warning_at (location, OPT_Wzero_as_null_ਸੂਚਕ_constant,
		    "zero as null pointer constant");
      /* A NULLPTR type is just a nullptr always.  */
      ਜੇ (coder == NULLPTR_TYPE)
	ਵਾਪਸ omit_one_ਸੰਕਾਰਜ_loc (ਵਿਅੰਜਕ_loc, type, nullptr_ਗੰਢ, rhs);
      /* An explicit constant 0 or type nullptr_t can convert to a pointer,
	 or one that results from arithmetic, even including a cast to
	 integer type.  */
      ਨਹੀਂਤਾਂ ਜੇ (!null_ਸੂਚਕ_constant)
	ਚੋਣ (errtype)
	  {
	  ਹਾਲਤ ic_argpass:
	    {
	      auto_diagnostic_ਸਮੂਹ d;
	      range_label_for_type_mismatch rhs_label (rhstype, type);
	      gcc_rich_location richloc (ਵਿਅੰਜਕ_loc, &rhs_label,
					 highlight_colors::actual);
	      ਜੇ (permerror_opt (&richloc, OPT_Wint_conversion,
				 "passing argument %d of %qE makes pointer "
				 "from integer without a cast", parmnum, rname))
		{
		  maybe_emit_indirection_note (ਵਿਅੰਜਕ_loc, rhs, type);
		  inform_for_arg (fundecl, ਵਿਅੰਜਕ_loc, parmnum, type, rhstype);
		}
	    }
	    ਰੋਕੋ;
	  ਹਾਲਤ ic_ਸੌਂਪੋ:
	    permerror_opt (location, OPT_Wint_conversion,
			   "assignment to %qT from %qT makes pointer from "
			   "integer without a cast", type, rhstype);
	    ਰੋਕੋ;
	  ਹਾਲਤ ic_init:
	  ਹਾਲਤ ic_init_const:
	    permerror_init (location, OPT_Wint_conversion,
			    "initialization of %qT from %qT makes pointer "
			    "from integer without a cast", type, rhstype);
	    ਰੋਕੋ;
	  ਹਾਲਤ ic_return:
	    permerror_init (location, OPT_Wint_conversion,
			    "returning %qT from a function with return type "
			    "%qT makes pointer from integer without a cast",
			    rhstype, type);
	    ਰੋਕੋ;
	  ਮੂਲ:
	    gcc_unreachable ();
	  }

      ਵਾਪਸ convert (type, rhs);
    }
  ਨਹੀਂਤਾਂ ਜੇ ((codel == INTEGER_TYPE || codel == BITINT_TYPE)
	   && coder == ਸੂਚਕ_TYPE)
    {
      ਚੋਣ (errtype)
	{
	ਹਾਲਤ ic_argpass:
	  {
	    auto_diagnostic_ਸਮੂਹ d;
	    range_label_for_type_mismatch rhs_label (rhstype, type);
	    gcc_rich_location richloc (ਵਿਅੰਜਕ_loc, &rhs_label,
				       highlight_colors::actual);
	    ਜੇ (permerror_opt (&richloc, OPT_Wint_conversion,
			       "passing argument %d of %qE makes integer from "
			       "pointer without a cast", parmnum, rname))
	      {
		maybe_emit_indirection_note (ਵਿਅੰਜਕ_loc, rhs, type);
		inform_for_arg (fundecl, ਵਿਅੰਜਕ_loc, parmnum, type, rhstype);
	      }
	  }
	  ਰੋਕੋ;
	ਹਾਲਤ ic_ਸੌਂਪੋ:
	  permerror_opt (location, OPT_Wint_conversion,
			 "assignment to %qT from %qT makes integer from "
			 "pointer without a cast", type, rhstype);
	  ਰੋਕੋ;
	ਹਾਲਤ ic_init:
	ਹਾਲਤ ic_init_const:
	  permerror_init (location, OPT_Wint_conversion,
			  "initialization of %qT from %qT makes integer "
			  "from pointer without a cast", type, rhstype);
	  ਰੋਕੋ;
	ਹਾਲਤ ic_return:
	  permerror_opt (location, OPT_Wint_conversion, "returning %qT from a "
			 "function with return type %qT makes integer from "
			 "pointer without a cast", rhstype, type);
	  ਰੋਕੋ;
	ਮੂਲ:
	  gcc_unreachable ();
	}

      ਵਾਪਸ convert (type, rhs);
    }
  ਨਹੀਂਤਾਂ ਜੇ (C_BOOLEAN_TYPE_P (type)
	   /* The type nullptr_t may be converted to bool.  The
	      result is false.  */
	   && (coder == ਸੂਚਕ_TYPE || coder == NULLPTR_TYPE))
    {
      ਰੁੱਖ ret;
      ਤਾਰਕਿਕ save = ਵਿੱਚ_late_ਦੁਆਧਾਰੀ_op;
      ਵਿੱਚ_late_ਦੁਆਧਾਰੀ_op = ਸੱਚ;
      ret = convert (type, rhs);
      ਵਿੱਚ_late_ਦੁਆਧਾਰੀ_op = save;
      ਵਾਪਸ ret;
    }
  ਨਹੀਂਤਾਂ ਜੇ (codel == NULLPTR_TYPE && null_ਸੂਚਕ_constant)
    ਵਾਪਸ convert (type, rhs);

  ਚੋਣ (errtype)
    {
    ਹਾਲਤ ic_argpass:
      {
	auto_diagnostic_ਸਮੂਹ d;
	range_label_for_type_mismatch rhs_label (rhstype, type);
	gcc_rich_location richloc (ਵਿਅੰਜਕ_loc, &rhs_label,
				   highlight_colors::actual);
	ਅਚਲ ਅੱਖਰ ਸੁਨੇਹਾ_2[] = G_("incompatible type for argument %d of %qE");
	ਜੇ (warnopt)
	  warning_at (ਵਿਅੰਜਕ_loc, warnopt, ਸੁਨੇਹਾ_2, parmnum, rname);
	ਨਹੀਂਤਾਂ
	  error_at (&richloc, ਸੁਨੇਹਾ_2, parmnum, rname);
	inform_for_arg (fundecl, ਵਿਅੰਜਕ_loc, parmnum, type, rhstype);
      }
      ਰੋਕੋ;
    ਹਾਲਤ ic_ਸੌਂਪੋ:
      {
	ਅਚਲ ਅੱਖਰ ਸੁਨੇਹਾ_2[]
	  = G_("incompatible types when assigning to type %qT from type %qT");
	ਜੇ (warnopt)
	  warning_at (ਵਿਅੰਜਕ_loc, 0, ਸੁਨੇਹਾ_2, type, rhstype);
	ਨਹੀਂਤਾਂ
	  error_at (ਵਿਅੰਜਕ_loc, ਸੁਨੇਹਾ_2, type, rhstype);
	ਰੋਕੋ;
      }
    ਹਾਲਤ ic_init:
    ਹਾਲਤ ic_init_const:
      {
	ਅਚਲ ਅੱਖਰ ਸੁਨੇਹਾ_2[]
	  = G_("incompatible types when initializing type %qT using type %qT");
	ਜੇ (warnopt)
	  warning_at (location, 0, ਸੁਨੇਹਾ_2, type, rhstype);
	ਨਹੀਂਤਾਂ
	  error_at (location, ਸੁਨੇਹਾ_2, type, rhstype);
	ਰੋਕੋ;
      }
    ਹਾਲਤ ic_return:
      {
	ਅਚਲ ਅੱਖਰ ਸੁਨੇਹਾ_2[]
	  = G_("incompatible types when returning type %qT but %qT was expected");
	ਜੇ (warnopt)
	  warning_at (location, 0, ਸੁਨੇਹਾ_2, rhstype, type);
	ਨਹੀਂਤਾਂ
	  error_at (location, ਸੁਨੇਹਾ_2, rhstype, type);
	ਰੋਕੋ;
      }
    ਮੂਲ:
      gcc_unreachable ();
    }

  ਵਾਪਸ error_mark_ਗੰਢ;
}

/* If VALUE is a compound expr all of whose expressions are constant, then
   return its value.  Otherwise, return error_mark_node.

   This is for handling COMPOUND_EXPRs as initializer elements
   which is allowed with a warning when -pedantic is specified.  */

ਸਥਿਰ ਰੁੱਖ
valid_compound_ਵਿਅੰਜਕ_initializer (ਰੁੱਖ ਮੁੱਲ, ਰੁੱਖ endtype)
{
  ਜੇ (ਰੁੱਖ_ਕੋਡ (ਮੁੱਲ) == COMPOUND_ਵਿਅੰਜਕ)
    {
      ਜੇ (valid_compound_ਵਿਅੰਜਕ_initializer (ਰੁੱਖ_ਸੰਕਾਰਜ (ਮੁੱਲ, 0), endtype)
	  == error_mark_ਗੰਢ)
	ਵਾਪਸ error_mark_ਗੰਢ;
      ਵਾਪਸ valid_compound_ਵਿਅੰਜਕ_initializer (ਰੁੱਖ_ਸੰਕਾਰਜ (ਮੁੱਲ, 1),
					      endtype);
    }
  ਨਹੀਂਤਾਂ ਜੇ (!initializer_constant_valid_p (ਮੁੱਲ, endtype))
    ਵਾਪਸ error_mark_ਗੰਢ;
  ਨਹੀਂਤਾਂ
    ਵਾਪਸ ਮੁੱਲ;
}

/* Perform appropriate conversions on the initial value of a variable,
   store it in the declaration DECL,
   and print any error messages that are appropriate.
   If ORIGTYPE is not NULL_TREE, it is the original type of INIT.
   If the init is invalid, store an ERROR_MARK.

   INIT_LOC is the location of the initial value.  */

ਖਾਲੀ
store_init_ਮੁੱਲ (location_t init_loc, ਰੁੱਖ decl, ਰੁੱਖ init, ਰੁੱਖ origtype)
{
  ਰੁੱਖ ਮੁੱਲ, type;
  ਤਾਰਕਿਕ npc = ਝੂਠ;
  ਤਾਰਕਿਕ int_const_ਵਿਅੰਜਕ = ਝੂਠ;
  ਤਾਰਕਿਕ arith_const_ਵਿਅੰਜਕ = ਝੂਠ;

  /* If variable's type was invalidly declared, just ignore it.  */

  type = ਰੁੱਖ_TYPE (decl);
  ਜੇ (ਰੁੱਖ_ਕੋਡ (type) == ERROR_MARK)
    ਵਾਪਸ;

  /* Digest the specified initializer into an expression.  */

  ਜੇ (init)
    {
      npc = null_ਸੂਚਕ_constant_p (init);
      int_const_ਵਿਅੰਜਕ = (ਰੁੱਖ_ਕੋਡ (init) == INTEGER_CST
			&& !ਰੁੱਖ_ਉਛਾਲ (init)
			&& INTEGRAL_TYPE_P (ਰੁੱਖ_TYPE (init)));
      /* Not fully determined before folding.  */
      arith_const_ਵਿਅੰਜਕ = ਸੱਚ;
    }
  ਤਾਰਕਿਕ constexpr_p = (VAR_P (decl)
		      && C_DECL_DECLARED_CONSTEXPR (decl));
  ਮੁੱਲ = digest_init (init_loc, decl, type, init, origtype, npc,
		       int_const_ਵਿਅੰਜਕ, arith_const_ਵਿਅੰਜਕ, ਸੱਚ,
		       ਰੁੱਖ_STATIC (decl) || constexpr_p, constexpr_p);

  /* Store the expression if valid; else report error.  */

  ਜੇ (!ਵਿੱਚ_system_ਸਿਰਲੇਖ_at (ਨਿਵੇਸ਼_location)
      && AGGREGATE_TYPE_P (ਰੁੱਖ_TYPE (decl)) && !ਰੁੱਖ_STATIC (decl))
    warning (OPT_Wtraditional, "traditional C rejects automatic "
	     "aggregate initialization");

  ਜੇ (ਮੁੱਲ != error_mark_ਗੰਢ || ਰੁੱਖ_ਕੋਡ (decl) != FUNCTION_DECL)
    DECL_INITIAL (decl) = ਮੁੱਲ;

  /* ANSI wants warnings about out-of-range constant initializers.  */
  STRIP_TYPE_NOPS (ਮੁੱਲ);
  ਜੇ (ਰੁੱਖ_STATIC (decl))
    constant_ਵਿਅੰਜਕ_warning (ਮੁੱਲ);

  /* Check if we need to set array size from compound literal size.  */
  ਜੇ (ਰੁੱਖ_ਕੋਡ (type) == ARRAY_TYPE
      && TYPE_DOMAIN (type) == NULL_ਰੁੱਖ
      && ਮੁੱਲ != error_mark_ਗੰਢ)
    {
      ਰੁੱਖ inside_init = init;

      STRIP_TYPE_NOPS (inside_init);
      inside_init = fold (inside_init);

      ਜੇ (ਰੁੱਖ_ਕੋਡ (inside_init) == COMPOUND_LITERAL_ਵਿਅੰਜਕ)
	{
	  ਰੁੱਖ cldecl = COMPOUND_LITERAL_ਵਿਅੰਜਕ_DECL (inside_init);

	  ਜੇ (TYPE_DOMAIN (ਰੁੱਖ_TYPE (cldecl)))
	    {
	      /* For int foo[] = (int [3]){1}; we need to set array size
		 now since later on array initializer will be just the
		 brace enclosed list of the compound literal.  */
	      ਰੁੱਖ etype = strip_array_types (ਰੁੱਖ_TYPE (decl));
	      type = build_distinct_type_copy (TYPE_MAIN_VARIANT (type));
	      TYPE_DOMAIN (type) = TYPE_DOMAIN (ਰੁੱਖ_TYPE (cldecl));
	      layout_type (type);
	      layout_decl (cldecl, 0);
	      ਰੁੱਖ_TYPE (decl)
		= c_build_qualified_type (type, TYPE_QUALS (etype));
	    }
	}
    }
}

/* Methods for storing and printing names for error messages.  */

/* Implement a spelling stack that allows components of a name to be pushed
   and popped.  Each element on the stack is this structure.  */

ਬਣਤਰ spelling
{
  ਪੂਰਨ ਕਿਸਮ;
  ਸੰਘ
    {
      ਬਿਨਾਨਿਸ਼ਾਨੀ HOST_WIDE_INT i;
      ਅਚਲ ਅੱਖਰ *s;
    } u;
};

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SPELLING_STRING 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SPELLING_MEMBER 2
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SPELLING_BOUNDS 3

ਸਥਿਰ ਬਣਤਰ spelling *spelling;	/* Next stack element (unused).  */
ਸਥਿਰ ਬਣਤਰ spelling *spelling_ਅਧਾਰ;	/* Spelling stack base.  */
ਸਥਿਰ ਪੂਰਨ spelling_ਮਾਪ;		/* Size of the spelling stack.  */

/* Macros to save and restore the spelling stack around push_... functions.
   Alternative to SAVE_SPELLING_STACK.  */

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SPELLING_ਡੂੰਘਾਈ() (spelling - spelling_ਅਧਾਰ)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ RESTORE_SPELLING_ਡੂੰਘਾਈ(ਡੂੰਘਾਈ_2) (spelling = spelling_ਅਧਾਰ + (ਡੂੰਘਾਈ_2))

/* Push an element on the spelling stack with type KIND and assign VALUE
   to MEMBER.  */

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਧੱਕੋ_SPELLING(ਕਿਸਮ_2, ਮੁੱਲ_2, MEMBER)				\
{									\
  ਪੂਰਨ ਡੂੰਘਾਈ = SPELLING_ਡੂੰਘਾਈ ();					\
									\
  ਜੇ (ਡੂੰਘਾਈ >= spelling_ਮਾਪ)						\
    {									\
      spelling_ਮਾਪ += 10;						\
      spelling_ਅਧਾਰ = XRESIZEVEC (ਬਣਤਰ spelling, spelling_ਅਧਾਰ,	\
				  spelling_ਮਾਪ);			\
      RESTORE_SPELLING_ਡੂੰਘਾਈ (ਡੂੰਘਾਈ);					\
    }									\
									\
  spelling->ਕਿਸਮ = (ਕਿਸਮ_2);						\
  spelling->MEMBER = (ਮੁੱਲ_2);						\
  spelling++;								\
}

/* Push STRING on the stack.  Printed literally.  */

ਸਥਿਰ ਖਾਲੀ
ਧੱਕੋ_string (ਅਚਲ ਅੱਖਰ *string)
{
  ਧੱਕੋ_SPELLING (SPELLING_STRING, string, u.s);
}

/* Push a member name on the stack.  Printed as '.' STRING.  */

ਸਥਿਰ ਖਾਲੀ
ਧੱਕੋ_member_name (ਰੁੱਖ decl)
{
  ਅਚਲ ਅੱਖਰ *ਅਚਲ string
    = (DECL_NAME (decl)
       ? identifier_ਮੰਜ਼ਿਲ_locale (IDENTIFIER_ਸੂਚਕ (DECL_NAME (decl)))
       : _("<anonymous>"));
  ਧੱਕੋ_SPELLING (SPELLING_MEMBER, string, u.s);
}

/* Push an array bounds on the stack.  Printed as [BOUNDS].  */

ਸਥਿਰ ਖਾਲੀ
ਧੱਕੋ_array_bounds (ਬਿਨਾਨਿਸ਼ਾਨੀ HOST_WIDE_INT bounds)
{
  ਧੱਕੋ_SPELLING (SPELLING_BOUNDS, bounds, u.i);
}

/* Compute the maximum size in bytes of the printed spelling.  */

ਸਥਿਰ ਪੂਰਨ
spelling_ਲੰਮਾਈ (ਖਾਲੀ)
{
  ਪੂਰਨ ਮਾਪ = 0;
  ਬਣਤਰ spelling *p;

  ਲਈ (p = spelling_ਅਧਾਰ; p < spelling; p++)
    {
      ਜੇ (p->ਕਿਸਮ == SPELLING_BOUNDS)
	ਮਾਪ += 25;
      ਨਹੀਂਤਾਂ
	ਮਾਪ += ਲੜੀ_ਲੰਬਾਈ (p->u.s) + 1;
    }

  ਵਾਪਸ ਮਾਪ;
}

/* Print the spelling to BUFFER and return it.  */

ਸਥਿਰ ਅੱਖਰ *
print_spelling (ਅੱਖਰ *ਬਫਰ)
{
  ਅੱਖਰ *d = ਬਫਰ;
  ਬਣਤਰ spelling *p;

  ਲਈ (p = spelling_ਅਧਾਰ; p < spelling; p++)
    ਜੇ (p->ਕਿਸਮ == SPELLING_BOUNDS)
      {
	sprintf (d, "[" HOST_WIDE_INT_PRINT_UNSIGNED "]", p->u.i);
	d += ਲੜੀ_ਲੰਬਾਈ (d);
      }
    ਨਹੀਂਤਾਂ
      {
	ਅਚਲ ਅੱਖਰ *s;
	ਜੇ (p->ਕਿਸਮ == SPELLING_MEMBER)
	  *d++ = '.';
	ਲਈ (s = p->u.s; (*d = *s++); d++)
	  ;
      }
  *d++ = '\0';
  ਵਾਪਸ ਬਫਰ;
}

/* Check whether INIT, a floating or integer constant, is
   representable in TYPE, a real floating type with the same radix or
   a decimal floating type initialized with a binary floating
   constant.  Return true if OK, false if not.  */
ਸਥਿਰ ਤਾਰਕਿਕ
constexpr_init_ਸਮਾਉਂਦਾ_real_type (ਰੁੱਖ type, ਰੁੱਖ init)
{
  gcc_assert (SCALAR_FLOAT_TYPE_P (type));
  gcc_assert (ਰੁੱਖ_ਕੋਡ (init) == INTEGER_CST || ਰੁੱਖ_ਕੋਡ (init) == REAL_CST);
  ਜੇ (ਰੁੱਖ_ਕੋਡ (init) == REAL_CST
      && TYPE_ਬਹੁਲਕ (ਰੁੱਖ_TYPE (init)) == TYPE_ਬਹੁਲਕ (type))
    {
      /* Same mode, no conversion required except for the case of
	 signaling NaNs if the types are incompatible (e.g. double and
	 long double with the same mode).  */
      ਜੇ (REAL_ਮੁੱਲ_ISSIGNALING_NAN (ਰੁੱਖ_REAL_CST (init))
	  && !comptypes (TYPE_MAIN_VARIANT (type),
			 TYPE_MAIN_VARIANT (ਰੁੱਖ_TYPE (init))))
	ਵਾਪਸ ਝੂਠ;
      ਵਾਪਸ ਸੱਚ;
    }
  ਜੇ (ਰੁੱਖ_ਕੋਡ (init) == INTEGER_CST)
    {
      ਰੁੱਖ converted = build_real_from_int_cst (type, init);
      ਤਾਰਕਿਕ fail = ਝੂਠ;
      wide_int w = real_ਮੰਜ਼ਿਲ_integer (&ਰੁੱਖ_REAL_CST (converted), &fail,
				    TYPE_PRECISION (ਰੁੱਖ_TYPE (init)));
      ਵਾਪਸ !fail && wi::eq_p (w, wi::ਮੰਜ਼ਿਲ_wide (init));
    }
  ਜੇ (REAL_ਮੁੱਲ_ISSIGNALING_NAN (ਰੁੱਖ_REAL_CST (init)))
    ਵਾਪਸ ਝੂਠ;
  ਜੇ ((REAL_ਮੁੱਲ_ISINF (ਰੁੱਖ_REAL_CST (init))
       && ਬਹੁਲਕ_HAS_INFINITIES (TYPE_ਬਹੁਲਕ (type)))
      || (REAL_ਮੁੱਲ_ISNAN (ਰੁੱਖ_REAL_CST (init))
	  && ਬਹੁਲਕ_HAS_NANS (TYPE_ਬਹੁਲਕ (type))))
    ਵਾਪਸ ਸੱਚ;
  ਜੇ (DECIMAL_FLOAT_TYPE_P (type)
      && !DECIMAL_FLOAT_TYPE_P (ਰੁੱਖ_TYPE (init)))
    {
      /* This is valid if the real number represented by the
	 initializer can be exactly represented in the decimal
	 type.  Compare the values using MPFR.  */
      REAL_ਮੁੱਲ_TYPE t;
      real_convert (&t, TYPE_ਬਹੁਲਕ (type), &ਰੁੱਖ_REAL_CST (init));
      mpfr_t bin_val, dec_val;
      mpfr_init2 (bin_val, REAL_ਬਹੁਲਕ_FORMAT (TYPE_ਬਹੁਲਕ (ਰੁੱਖ_TYPE (init)))->p);
      mpfr_init2 (dec_val, REAL_ਬਹੁਲਕ_FORMAT (TYPE_ਬਹੁਲਕ (ਰੁੱਖ_TYPE (init)))->p);
      mpfr_from_real (bin_val, &ਰੁੱਖ_REAL_CST (init), MPFR_RNDN);
      ਅੱਖਰ string[256];
      real_ਮੰਜ਼ਿਲ_decimal (string, &t, ਆਕਾਰ string, 0, 1);
      ਤਾਰਕਿਕ res = (mpfr_strtofr (dec_val, string, ਨਿਰਾ, 10, MPFR_RNDN) == 0
		  && mpfr_equal_p (bin_val, dec_val));
      mpfr_clear (bin_val);
      mpfr_clear (dec_val);
      ਵਾਪਸ res;
    }
  /* exact_real_truncate is not quite right here, since it doesn't
     allow even an exact conversion to subnormal values.  */
  REAL_ਮੁੱਲ_TYPE t;
  real_convert (&t, TYPE_ਬਹੁਲਕ (type), &ਰੁੱਖ_REAL_CST (init));
  ਵਾਪਸ real_identical (&t, &ਰੁੱਖ_REAL_CST (init));
}

/* Check whether INIT (location LOC) is valid as a 'constexpr'
   initializer for type TYPE, and give an error if not.  INIT has
   already been folded and verified to be constant.  INT_CONST_EXPR
   and ARITH_CONST_EXPR say whether it is an integer constant
   expression or arithmetic constant expression, respectively.  If
   TYPE is not a scalar type, this function does nothing.  */

ਸਥਿਰ ਖਾਲੀ
check_constexpr_init (location_t loc, ਰੁੱਖ type, ਰੁੱਖ init,
		      ਤਾਰਕਿਕ int_const_ਵਿਅੰਜਕ, ਤਾਰਕਿਕ arith_const_ਵਿਅੰਜਕ)
{
  ਜੇ (ਸੂਚਕ_TYPE_P (type))
    {
      /* The initializer must be null.  */
      ਜੇ (ਰੁੱਖ_ਕੋਡ (init) != INTEGER_CST || !integer_zerop (init))
	error_at (loc, "%<constexpr%> pointer initializer is not null");
      ਵਾਪਸ;
    }
  ਜੇ (INTEGRAL_TYPE_P (type))
    {
      /* The initializer must be an integer constant expression,
	 representable in the target type.  */
      ਜੇ (!int_const_ਵਿਅੰਜਕ)
	{
	  ਜੇ (ਰੁੱਖ_ਕੋਡ (init) == RAW_ਅੰਕੜੇ_CST
	      && TYPE_PRECISION (type) == CHAR_ਦੋਆਧਾਰੀ_ਅੰਕ)
	    {
	      ਜੇ (!TYPE_UNSIGNED (type))
		ਲਈ (ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ i = 0;
		     i < (ਬਿਨਾਨਿਸ਼ਾਨੀ) RAW_ਅੰਕੜੇ_ਲੰਮਾਈ (init); ++i)
		  ਜੇ (RAW_ਅੰਕੜੇ_SCHAR_ELT (init, i) < 0)
		    {
		      error_at (loc, "%<constexpr%> initializer not "
				"representable in type of object");
		      ਰੋਕੋ;
		    }
	    }
	  ਨਹੀਂਤਾਂ
	    error_at (loc, "%<constexpr%> integer initializer is not an "
		      "integer constant expression");
	}
      ਨਹੀਂਤਾਂ ਜੇ (!int_ਸਮਾਉਂਦਾ_type_p (init, type))
	error_at (loc, "%<constexpr%> initializer not representable in "
		  "type of object");
      ਵਾਪਸ;
    }
  /* We don't apply any extra checks to extension types such as vector
     or fixed-point types.  */
  ਜੇ (ਰੁੱਖ_ਕੋਡ (type) != REAL_TYPE && ਰੁੱਖ_ਕੋਡ (type) != COMPLEX_TYPE)
    ਵਾਪਸ;
  ਜੇ (!arith_const_ਵਿਅੰਜਕ)
    {
      error_at (loc, "%<constexpr%> initializer is not an arithmetic "
		"constant expression");
      ਵਾਪਸ;
    }
  /* We don't apply any extra checks to complex integers.  */
  ਜੇ (ਰੁੱਖ_ਕੋਡ (type) == COMPLEX_TYPE
      && ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (type)) != REAL_TYPE)
    ਵਾਪਸ;
  /* Following N3082, a real type cannot be initialized from a complex
     type and a binary type cannot be initialized from a decimal type
     (but initializing a decimal type from a binary type is OK).
     Signaling NaN initializers are OK only if the types are
     compatible (not just the same mode); all quiet NaN and infinity
     initializations are considered to preserve the value.  */
  ਜੇ (ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (init)) == COMPLEX_TYPE
      && SCALAR_FLOAT_TYPE_P (type))
    {
      error_at (loc, "%<constexpr%> initializer for a real type is of "
		"complex type");
      ਵਾਪਸ;
    }
  ਜੇ (SCALAR_FLOAT_TYPE_P (type)
      && SCALAR_FLOAT_TYPE_P (ਰੁੱਖ_TYPE (init))
      && DECIMAL_FLOAT_TYPE_P (ਰੁੱਖ_TYPE (init))
      && !DECIMAL_FLOAT_TYPE_P (type))
    {
      error_at (loc, "%<constexpr%> initializer for a binary "
		"floating-point type is of decimal type");
      ਵਾਪਸ;
    }
  ਤਾਰਕਿਕ ਸਮਾਉਂਦਾ;
  ਜੇ (ਰੁੱਖ_ਕੋਡ (type) == COMPLEX_TYPE)
    {
      ਚੋਣ (ਰੁੱਖ_ਕੋਡ (init))
	{
	ਹਾਲਤ INTEGER_CST:
	ਹਾਲਤ REAL_CST:
	  ਸਮਾਉਂਦਾ = constexpr_init_ਸਮਾਉਂਦਾ_real_type (ਰੁੱਖ_TYPE (type), init);
	  ਰੋਕੋ;
	ਹਾਲਤ COMPLEX_CST:
	  ਸਮਾਉਂਦਾ = (constexpr_init_ਸਮਾਉਂਦਾ_real_type (ਰੁੱਖ_TYPE (type),
						 ਰੁੱਖ_REALPART (init))
		  && constexpr_init_ਸਮਾਉਂਦਾ_real_type (ਰੁੱਖ_TYPE (type),
						    ਰੁੱਖ_IMAGPART (init)));
	  ਰੋਕੋ;
	ਮੂਲ:
	  gcc_unreachable ();
	}
    }
  ਨਹੀਂਤਾਂ
    ਸਮਾਉਂਦਾ = constexpr_init_ਸਮਾਉਂਦਾ_real_type (type, init);
  ਜੇ (!ਸਮਾਉਂਦਾ)
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

ਸਥਿਰ ਰੁੱਖ
digest_init (location_t init_loc, ਰੁੱਖ decl, ਰੁੱਖ type, ਰੁੱਖ init,
	     ਰੁੱਖ origtype, ਤਾਰਕਿਕ null_ਸੂਚਕ_constant, ਤਾਰਕਿਕ int_const_ਵਿਅੰਜਕ,
	     ਤਾਰਕਿਕ arith_const_ਵਿਅੰਜਕ, ਤਾਰਕਿਕ strict_string,
	     ਤਾਰਕਿਕ require_constant, ਤਾਰਕਿਕ require_constexpr)
{
  ਗਿਣਤੀ ਰੁੱਖ_ਕੋਡ_2 ਕੋਡ = ਰੁੱਖ_ਕੋਡ (type);
  ਰੁੱਖ inside_init = init;
  ਰੁੱਖ semantic_type = NULL_ਰੁੱਖ;
  ਤਾਰਕਿਕ maybe_const = ਸੱਚ;

  ਜੇ (type == error_mark_ਗੰਢ
      || !init
      || error_ਸੰਕਾਰਜ_p (init))
    ਵਾਪਸ error_mark_ਗੰਢ;

  STRIP_TYPE_NOPS (inside_init);

  /* If require_constant is TRUE,  when the initializer is a call to
     .ACCESS_WITH_SIZE, use the first argument as the initializer.
     For example:
     y = (char *) .ACCESS_WITH_SIZE ((char *) &static_annotated.c,...)
     will be converted to
     y = &static_annotated.c.  */

  ਜੇ (require_constant
      && ਰੁੱਖ_ਕੋਡ (inside_init) == NOP_ਵਿਅੰਜਕ
      && ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_ਸੰਕਾਰਜ (inside_init, 0)) == CALL_ਵਿਅੰਜਕ
      && is_access_with_ਮਾਪ_p (ਰੁੱਖ_ਸੰਕਾਰਜ (inside_init, 0)))
    inside_init
      = get_ref_from_access_with_ਮਾਪ (ਰੁੱਖ_ਸੰਕਾਰਜ (inside_init, 0));

  ਜੇ (!c_ਵਿੱਚ_omp_for)
    {
      ਜੇ (ਰੁੱਖ_ਕੋਡ (inside_init) == EXCESS_PRECISION_ਵਿਅੰਜਕ)
	{
	  semantic_type = ਰੁੱਖ_TYPE (inside_init);
	  inside_init = ਰੁੱਖ_ਸੰਕਾਰਜ (inside_init, 0);
	}
      inside_init = c_fully_fold (inside_init, require_constant, &maybe_const);
    }
  /* TODO: this may not detect all cases of expressions folding to
     constants that are not arithmetic constant expressions.  */
  ਜੇ (!maybe_const)
    arith_const_ਵਿਅੰਜਕ = ਝੂਠ;
  ਨਹੀਂਤਾਂ ਜੇ (!INTEGRAL_TYPE_P (ਰੁੱਖ_TYPE (inside_init))
	   && ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (inside_init)) != REAL_TYPE
	   && ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (inside_init)) != COMPLEX_TYPE)
    arith_const_ਵਿਅੰਜਕ = ਝੂਠ;
  ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਕੋਡ (inside_init) != INTEGER_CST
	   && ਰੁੱਖ_ਕੋਡ (inside_init) != REAL_CST
	   && ਰੁੱਖ_ਕੋਡ (inside_init) != COMPLEX_CST
	   && ਰੁੱਖ_ਕੋਡ (inside_init) != RAW_ਅੰਕੜੇ_CST)
    arith_const_ਵਿਅੰਜਕ = ਝੂਠ;
  ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਉਛਾਲ (inside_init))
    arith_const_ਵਿਅੰਜਕ = ਝੂਠ;

  /* Initialization of an array of chars from a string constant
     optionally enclosed in braces.  */

  ਜੇ (ਕੋਡ == ARRAY_TYPE && inside_init
      && ਰੁੱਖ_ਕੋਡ (inside_init) == STRING_CST)
    {
      ਰੁੱਖ typ1
	= (TYPE_ATOMIC (ਰੁੱਖ_TYPE (type))
	   ? c_build_qualified_type (TYPE_MAIN_VARIANT (ਰੁੱਖ_TYPE (type)),
				     TYPE_QUAL_ATOMIC)
	   : TYPE_MAIN_VARIANT (ਰੁੱਖ_TYPE (type)));
      /* Note that an array could be both an array of character type
	 and an array of wchar_t if wchar_t is signed char or unsigned
	 char.  */
      ਤਾਰਕਿਕ char_array = (typ1 == char_type_ਗੰਢ
			 || typ1 == signed_char_type_ਗੰਢ
			 || typ1 == unsigned_char_type_ਗੰਢ);
      ਤਾਰਕਿਕ wchar_array = comptypes (typ1, wchar_type_ਗੰਢ);
      ਤਾਰਕਿਕ char16_array = comptypes (typ1, char16_type_ਗੰਢ);
      ਤਾਰਕਿਕ char32_array = comptypes (typ1, char32_type_ਗੰਢ);

      ਜੇ (char_array || wchar_array || char16_array || char32_array)
	{
	  ਬਣਤਰ c_ਵਿਅੰਜਕ ਵਿਅੰਜਕ;
	  ਰੁੱਖ typ2 = TYPE_MAIN_VARIANT (ਰੁੱਖ_TYPE (ਰੁੱਖ_TYPE (inside_init)));
	  ਤਾਰਕਿਕ incompat_string_cst = ਝੂਠ;
	  ਵਿਅੰਜਕ.ਮੁੱਲ = inside_init;
	  ਵਿਅੰਜਕ.original_ਕੋਡ = (strict_string ? STRING_CST : ERROR_MARK);
	  ਵਿਅੰਜਕ.original_type = ਨਿਰਾ;
	  ਵਿਅੰਜਕ.m_decimal = 0;
	  maybe_warn_string_init (init_loc, type, ਵਿਅੰਜਕ);

	  ਜੇ (flexible_array_member_type_p (type))
	    pedwarn_init (init_loc, OPT_Wpedantic,
			  "initialization of a flexible array member");

	  ਜੇ (comptypes (TYPE_MAIN_VARIANT (ਰੁੱਖ_TYPE (inside_init)),
			 TYPE_MAIN_VARIANT (type)))
	    ਵਾਪਸ inside_init;

	  ਜੇ (char_array)
	    {
	      ਜੇ (typ2 != char_type_ਗੰਢ && typ2 != char8_type_ਗੰਢ)
		incompat_string_cst = ਸੱਚ;
	    }
	  ਨਹੀਂਤਾਂ ਜੇ (!comptypes (typ1, typ2))
	    incompat_string_cst = ਸੱਚ;

          ਜੇ (incompat_string_cst)
            {
	      error_init (init_loc, "cannot initialize array of %qT from "
			  "a string literal with type array of %qT",
			  typ1, typ2);
	      ਵਾਪਸ error_mark_ਗੰਢ;
            }

	  ਜੇ (require_constexpr
	      && TYPE_UNSIGNED (typ1) != TYPE_UNSIGNED (typ2))
	    {
	      /* Check if all characters of the string can be
		 represented in the type of the constexpr object being
		 initialized.  */
	      ਬਿਨਾਨਿਸ਼ਾਨੀ HOST_WIDE_INT len = ਰੁੱਖ_STRING_ਲੰਮਾਈ (inside_init);
	      ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *p =
		(ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *) ਰੁੱਖ_STRING_ਸੂਚਕ (inside_init);
	      gcc_assert (CHAR_TYPE_ਮਾਪ == 8 && CHAR_ਦੋਆਧਾਰੀ_ਅੰਕ == 8);
	      ਲਈ (ਬਿਨਾਨਿਸ਼ਾਨੀ i = 0; i < len; i++)
		ਜੇ (p[i] > 127)
		  {
		    error_init (init_loc, "%<constexpr%> initializer not "
				"representable in type of object");
		    ਰੋਕੋ;
		  }
	    }

	  ਜੇ (TYPE_DOMAIN (type) != NULL_ਰੁੱਖ
	      && TYPE_ਮਾਪ (type) != NULL_ਰੁੱਖ
	      && ਰੁੱਖ_ਕੋਡ (TYPE_ਮਾਪ (type)) == INTEGER_CST)
	    {
	      ਬਿਨਾਨਿਸ਼ਾਨੀ HOST_WIDE_INT len = ਰੁੱਖ_STRING_ਲੰਮਾਈ (inside_init);

	      ਜੇ (compare_ਰੁੱਖ_int (TYPE_ਮਾਪ_UNIT (type), len) < 0)
		{
		  ਬਿਨਾਨਿਸ਼ਾਨੀ HOST_WIDE_INT avail
		    = ਰੁੱਖ_ਮੰਜ਼ਿਲ_uhwi (TYPE_ਮਾਪ_UNIT (type));
		  ਬਿਨਾਨਿਸ਼ਾਨੀ unit = TYPE_PRECISION (typ1) / ਬਿੱਟ_ਪ੍ਰਤੀ_UNIT;
		  ਅਚਲ ਅੱਖਰ *p = ਰੁੱਖ_STRING_ਸੂਚਕ (inside_init);

		  /* Construct truncated string.  */
		  inside_init = build_string (avail, p);

		  /* Subtract the size of a single (possibly wide) character
		     because it may be ok to ignore the terminating NUL char
		     that is counted in the length of the constant.  */
		  ਜੇ (len - unit > avail)
		    pedwarn_init (init_loc, 0,
				  "initializer-string for array of %qT "
				  "is too long (%wu chars into %wu "
				  "available)", typ1, len, avail);
		  ਨਹੀਂਤਾਂ ਜੇ (warn_cxx_compat)
		    warning_at (init_loc, OPT_Wc___compat,
				"initializer-string for array of %qT "
				"is too long for C++ (%wu chars into %wu "
				"available)", typ1, len, avail);
		  ਨਹੀਂਤਾਂ ਜੇ (warn_unterminated_string_initialization
			   && get_attr_nonstring_decl (decl) == NULL_ਰੁੱਖ)
		    warning_at (init_loc,
				OPT_Wunterminated_string_initialization,
				"initializer-string for array of %qT "
				"truncates NUL terminator but destination "
				"lacks %qs attribute (%wu chars into %wu "
				"available)", typ1, "nonstring", len, avail);
		}
	    }

	  ਰੁੱਖ_TYPE (inside_init) = type;
	  ਵਾਪਸ inside_init;
	}
      ਨਹੀਂਤਾਂ ਜੇ (INTEGRAL_TYPE_P (typ1))
	{
	  error_init (init_loc, "array of inappropriate type initialized "
		      "from string constant");
	  ਵਾਪਸ error_mark_ਗੰਢ;
	}
    }

  /* Build a VECTOR_CST from a *constant* vector constructor.  If the
     vector constructor is not constant (e.g. {1,2,3,foo()}) then punt
     below and handle as a constructor.  */
  ਜੇ (ਕੋਡ == ਸਦਿਸ਼_TYPE
      && ਸਦਿਸ਼_TYPE_P (ਰੁੱਖ_TYPE (inside_init))
      && ਸਦਿਸ਼_types_convertible_p (ਰੁੱਖ_TYPE (inside_init), type, ਸੱਚ)
      && ਰੁੱਖ_CONSTANT (inside_init))
    {
      ਜੇ (ਰੁੱਖ_ਕੋਡ (inside_init) == ਸਦਿਸ਼_CST
	  && comptypes (TYPE_MAIN_VARIANT (ਰੁੱਖ_TYPE (inside_init)),
			TYPE_MAIN_VARIANT (type)))
	ਵਾਪਸ inside_init;

      ਜੇ (ਰੁੱਖ_ਕੋਡ (inside_init) == CONSTRUCTOR)
	{
	  ਬਿਨਾਨਿਸ਼ਾਨੀ HOST_WIDE_INT ix;
	  ਰੁੱਖ ਮੁੱਲ;
	  ਤਾਰਕਿਕ constant_p = ਸੱਚ;

	  /* Iterate through elements and check if all constructor
	     elements are *_CSTs.  */
	  FOR_EACH_CONSTRUCTOR_ਮੁੱਲ (CONSTRUCTOR_ELTS (inside_init), ix, ਮੁੱਲ)
	    ਜੇ (!CONSTANT_CLASS_P (ਮੁੱਲ))
	      {
		constant_p = ਝੂਠ;
		ਰੋਕੋ;
	      }

	  ਜੇ (constant_p)
	    ਵਾਪਸ build_ਸਦਿਸ਼_from_ctor (type,
					   CONSTRUCTOR_ELTS (inside_init));
	}
    }

  ਜੇ (warn_sequence_ਬਿੰਦੂ)
    verify_sequence_points (inside_init);

  /* Any type can be initialized
     from an expression of the same type, optionally with braces.  */

  ਜੇ (inside_init && ਰੁੱਖ_TYPE (inside_init) != NULL_ਰੁੱਖ
      && (comptypes (TYPE_MAIN_VARIANT (ਰੁੱਖ_TYPE (inside_init)),
		     TYPE_MAIN_VARIANT (type))
	  || (ਕੋਡ == ARRAY_TYPE
	      && comptypes (ਰੁੱਖ_TYPE (inside_init), type))
	  || (gnu_ਸਦਿਸ਼_type_p (type)
	      && comptypes (ਰੁੱਖ_TYPE (inside_init), type))
	  || (ਕੋਡ == ਸੂਚਕ_TYPE
	      && ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (inside_init)) == ARRAY_TYPE
	      && comptypes (ਰੁੱਖ_TYPE (ਰੁੱਖ_TYPE (inside_init)),
			    ਰੁੱਖ_TYPE (type)))))
    {
      ਜੇ (ਕੋਡ == ਸੂਚਕ_TYPE)
	{
	  ਜੇ (ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (inside_init)) == ARRAY_TYPE)
	    {
	      ਜੇ (ਰੁੱਖ_ਕੋਡ (inside_init) == STRING_CST
		  || ਰੁੱਖ_ਕੋਡ (inside_init) == COMPOUND_LITERAL_ਵਿਅੰਜਕ)
		inside_init = array_ਮੰਜ਼ਿਲ_ਸੂਚਕ_conversion
		  (init_loc, inside_init);
	      ਨਹੀਂਤਾਂ
		{
		  error_init (init_loc, "invalid use of non-lvalue array");
		  ਵਾਪਸ error_mark_ਗੰਢ;
		}
	    }
	}

      ਜੇ (ਕੋਡ == ਸਦਿਸ਼_TYPE || c_hardbool_type_attr (type))
	/* Although the types are compatible, we may require a
	   conversion.  */
	inside_init = convert (type, inside_init);

      ਜੇ ((ਕੋਡ == ਰਿਕਾਰਡ_TYPE || ਕੋਡ == UNION_TYPE)
	  && !comptypes (TYPE_MAIN_VARIANT (type), TYPE_MAIN_VARIANT (ਰੁੱਖ_TYPE (inside_init))))
	{
	  error_init (init_loc, "invalid initializer");
	  ਵਾਪਸ error_mark_ਗੰਢ;
	}

      ਜੇ (require_constant
	  && ਰੁੱਖ_ਕੋਡ (inside_init) == COMPOUND_LITERAL_ਵਿਅੰਜਕ)
	{
	  /* As an extension, allow initializing objects with static storage
	     duration with compound literals (which are then treated just as
	     the brace enclosed list they contain).  Also allow this for
	     vectors, as we can only assign them with compound literals.  */
	  ਜੇ (flag_isoc99 && ਕੋਡ != ਸਦਿਸ਼_TYPE)
	    pedwarn_init (init_loc, OPT_Wpedantic, "initializer element "
			  "is not constant");
	  ਰੁੱਖ decl = COMPOUND_LITERAL_ਵਿਅੰਜਕ_DECL (inside_init);
	  inside_init = DECL_INITIAL (decl);
	}

      ਜੇ (ਕੋਡ == ARRAY_TYPE && ਰੁੱਖ_ਕੋਡ (inside_init) != STRING_CST
	  && ਰੁੱਖ_ਕੋਡ (inside_init) != CONSTRUCTOR)
	{
	  error_init (init_loc, "array initialized from non-constant array "
		      "expression");
	  ਵਾਪਸ error_mark_ਗੰਢ;
	}

      /* Compound expressions can only occur here if -Wpedantic or
	 -pedantic-errors is specified.  In the later case, we always want
	 an error.  In the former case, we simply want a warning.  */
      ਜੇ (require_constant && pedantic
	  && ਰੁੱਖ_ਕੋਡ (inside_init) == COMPOUND_ਵਿਅੰਜਕ)
	{
	  inside_init
	    = valid_compound_ਵਿਅੰਜਕ_initializer (inside_init,
					       ਰੁੱਖ_TYPE (inside_init));
	  ਜੇ (inside_init == error_mark_ਗੰਢ)
	    error_init (init_loc, "initializer element is not constant");
	  ਨਹੀਂਤਾਂ
	    pedwarn_init (init_loc, OPT_Wpedantic,
			  "initializer element is not constant");
	  ਜੇ (flag_pedantic_errors)
	    inside_init = error_mark_ਗੰਢ;
	}
      ਨਹੀਂਤਾਂ ਜੇ (require_constant
	       && !initializer_constant_valid_p (inside_init,
						 ਰੁੱਖ_TYPE (inside_init)))
	{
	  error_init (init_loc, "initializer element is not constant");
	  inside_init = error_mark_ਗੰਢ;
	}
      ਨਹੀਂਤਾਂ ਜੇ (require_constant && !maybe_const)
	pedwarn_init (init_loc, OPT_Wpedantic,
		      "initializer element is not a constant expression");
      ਨਹੀਂਤਾਂ ਜੇ (require_constexpr)
	check_constexpr_init (init_loc, type, inside_init,
			      int_const_ਵਿਅੰਜਕ, arith_const_ਵਿਅੰਜਕ);

      /* Added to enable additional -Wsuggest-attribute=format warnings.  */
      ਜੇ (ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (inside_init)) == ਸੂਚਕ_TYPE)
	inside_init = convert_for_assignment (init_loc, UNKNOWN_LOCATION,
					      type, inside_init, origtype,
					      (require_constant
					       ? ic_init_const
					       : ic_init), null_ਸੂਚਕ_constant,
					      NULL_ਰੁੱਖ, NULL_ਰੁੱਖ, 0);
      ਜੇ (ਰੁੱਖ_ਕੋਡ (inside_init) == RAW_ਅੰਕੜੇ_CST
	  && c_inhibit_evaluation_warnings == 0
	  && warn_conversion
	  && !TYPE_UNSIGNED (type)
	  && TYPE_PRECISION (type) == CHAR_ਦੋਆਧਾਰੀ_ਅੰਕ)
	ਲਈ (ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ i = 0;
	     i < (ਬਿਨਾਨਿਸ਼ਾਨੀ) RAW_ਅੰਕੜੇ_ਲੰਮਾਈ (inside_init); ++i)
	  ਜੇ (RAW_ਅੰਕੜੇ_SCHAR_ELT (inside_init, i) < 0)
	    warning_at (init_loc, OPT_Wconversion,
			"conversion from %qT to %qT changes value from "
			"%qd to %qd",
			integer_type_ਗੰਢ, type,
			RAW_ਅੰਕੜੇ_UCHAR_ELT (inside_init, i),
			RAW_ਅੰਕੜੇ_SCHAR_ELT (inside_init, i));
      ਵਾਪਸ inside_init;
    }

  /* Handle scalar types, including conversions.  */

  ਜੇ (ਕੋਡ == INTEGER_TYPE || ਕੋਡ == REAL_TYPE || ਕੋਡ == FIXED_ਬਿੰਦੂ_TYPE
      || ਕੋਡ == ਸੂਚਕ_TYPE || ਕੋਡ == ENUMERAL_TYPE || ਕੋਡ == BOOLEAN_TYPE
      || ਕੋਡ == COMPLEX_TYPE || ਕੋਡ == ਸਦਿਸ਼_TYPE || ਕੋਡ == NULLPTR_TYPE
      || ਕੋਡ == BITINT_TYPE)
    {
      ਰੁੱਖ unconverted_init = inside_init;
      ਜੇ (ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (init)) == ARRAY_TYPE
	  && (ਰੁੱਖ_ਕੋਡ (init) == STRING_CST
	      || ਰੁੱਖ_ਕੋਡ (init) == COMPOUND_LITERAL_ਵਿਅੰਜਕ))
	inside_init = init = array_ਮੰਜ਼ਿਲ_ਸੂਚਕ_conversion (init_loc, init);
      ਜੇ (semantic_type)
	inside_init = build1 (EXCESS_PRECISION_ਵਿਅੰਜਕ, semantic_type,
			      inside_init);
      inside_init
	= convert_for_assignment (init_loc, UNKNOWN_LOCATION, type,
				  inside_init, origtype,
				  require_constant ? ic_init_const : ic_init,
				  null_ਸੂਚਕ_constant, NULL_ਰੁੱਖ, NULL_ਰੁੱਖ,
				  0);

      /* Check to see if we have already given an error message.  */
      ਜੇ (inside_init == error_mark_ਗੰਢ)
	;
      ਨਹੀਂਤਾਂ ਜੇ (require_constant && !ਰੁੱਖ_CONSTANT (inside_init))
	{
	  error_init (init_loc, "initializer element is not constant");
	  inside_init = error_mark_ਗੰਢ;
	}
      ਨਹੀਂਤਾਂ ਜੇ (require_constant
	       && !initializer_constant_valid_p (inside_init,
						 ਰੁੱਖ_TYPE (inside_init)))
	{
	  error_init (init_loc, "initializer element is not computable at "
		      "load time");
	  inside_init = error_mark_ਗੰਢ;
	}
      ਨਹੀਂਤਾਂ ਜੇ (require_constant && !maybe_const)
	pedwarn_init (init_loc, OPT_Wpedantic,
		      "initializer element is not a constant expression");
      ਨਹੀਂਤਾਂ ਜੇ (require_constexpr)
	check_constexpr_init (init_loc, type, unconverted_init,
			      int_const_ਵਿਅੰਜਕ, arith_const_ਵਿਅੰਜਕ);

      ਵਾਪਸ inside_init;
    }

  /* Come here only for records and arrays.  */

  ਜੇ (COMPLETE_TYPE_P (type) && ਰੁੱਖ_ਕੋਡ (TYPE_ਮਾਪ (type)) != INTEGER_CST)
    {
      error_init (init_loc,
		  "variable-sized object may not be initialized except "
		  "with an empty initializer");
      ਵਾਪਸ error_mark_ਗੰਢ;
    }

  error_init (init_loc, "invalid initializer");
  ਵਾਪਸ error_mark_ਗੰਢ;
}

/* Handle initializers that use braces.  */

/* Type of object we are accumulating a constructor for.
   This type is always a RECORD_TYPE, UNION_TYPE or ARRAY_TYPE.  */
ਸਥਿਰ ਰੁੱਖ constructor_type;

/* For a RECORD_TYPE or UNION_TYPE, this is the chain of fields
   left to fill.  */
ਸਥਿਰ ਰੁੱਖ constructor_fields;

/* For an ARRAY_TYPE, this is the specified index
   at which to store the next element we get.  */
ਸਥਿਰ ਰੁੱਖ constructor_ਸੂਚਕਾਂਕ;

/* For an ARRAY_TYPE, this is the maximum index.  */
ਸਥਿਰ ਰੁੱਖ constructor_max_ਸੂਚਕਾਂਕ;

/* For a RECORD_TYPE, this is the first field not yet written out.  */
ਸਥਿਰ ਰੁੱਖ constructor_unfilled_fields;

/* For an ARRAY_TYPE, this is the index of the first element
   not yet written out.  */
ਸਥਿਰ ਰੁੱਖ constructor_unfilled_ਸੂਚਕਾਂਕ;

/* In a RECORD_TYPE, the byte index of the next consecutive field.
   This is so we can generate gaps between fields, when appropriate.  */
ਸਥਿਰ ਰੁੱਖ constructor_ਦੋਆਧਾਰੀ_ਅੰਕ_ਸੂਚਕਾਂਕ;

/* If we are saving up the elements rather than allocating them,
   this is the list of elements so far (in reverse order,
   most recent first).  */
ਸਥਿਰ vec<constructor_elt, va_gc> *constructor_elements;

/* 1 if constructor should be incrementally stored into a constructor chain,
   0 if all the elements should be kept in AVL tree.  */
ਸਥਿਰ ਪੂਰਨ constructor_incremental;

/* 1 if so far this constructor's elements are all compile-time constants.  */
ਸਥਿਰ ਪੂਰਨ constructor_constant;

/* 1 if so far this constructor's elements are all valid address constants.  */
ਸਥਿਰ ਪੂਰਨ constructor_simple;

/* 1 if this constructor has an element that cannot be part of a
   constant expression.  */
ਸਥਿਰ ਪੂਰਨ constructor_nonconst;

/* 1 if this constructor is erroneous so far.  */
ਸਥਿਰ ਪੂਰਨ constructor_erroneous;

/* 1 if this constructor is the universal zero initializer { 0 }.  */
ਸਥਿਰ ਪੂਰਨ constructor_zeroinit;

/* 1 if this constructor should have padding bits zeroed (C23 {}.  */
ਸਥਿਰ ਤਾਰਕਿਕ constructor_zero_padding_ਬਿੱਟ;

/* 1 if this constructor is a braced scalar initializer (further nested levels
   of braces are an error).  */
ਸਥਿਰ ਤਾਰਕਿਕ constructor_braced_scalar;

/* Structure for managing pending initializer elements, organized as an
   AVL tree.  */

ਬਣਤਰ init_ਗੰਢ
{
  ਬਣਤਰ init_ਗੰਢ *ਖੱਬੇ, *ਸੱਜੇ;
  ਬਣਤਰ init_ਗੰਢ *ਮਾਪਾ;
  ਪੂਰਨ balance;
  ਰੁੱਖ purpose;
  ਰੁੱਖ ਮੁੱਲ;
  ਰੁੱਖ origtype;
};

/* Tree of pending elements at this constructor level.
   These are elements encountered out of order
   which belong at places we haven't reached yet in actually
   writing the output.
   Will never hold tree nodes across GC runs.  */
ਸਥਿਰ ਬਣਤਰ init_ਗੰਢ *constructor_pending_elts;

/* The SPELLING_DEPTH of this constructor.  */
ਸਥਿਰ ਪੂਰਨ constructor_ਡੂੰਘਾਈ;

/* DECL node for which an initializer is being read.
   0 means we are reading a constructor expression
   such as (struct foo) {...}.  */
ਸਥਿਰ ਰੁੱਖ constructor_decl;

/* Nonzero if there were any member designators in this initializer.  */
ਸਥਿਰ ਪੂਰਨ constructor_designated;

/* Nesting depth of designator list.  */
ਸਥਿਰ ਪੂਰਨ designator_ਡੂੰਘਾਈ;

/* Nonzero if there were diagnosed errors in this designator list.  */
ਸਥਿਰ ਪੂਰਨ designator_erroneous;


/* This stack has a level for each implicit or explicit level of
   structuring in the initializer, including the outermost one.  It
   saves the values of most of the variables above.  */

ਬਣਤਰ constructor_range_ਢੇਰ;

ਬਣਤਰ constructor_ਢੇਰ
{
  ਬਣਤਰ constructor_ਢੇਰ *ਅਗਲਾ;
  ਰੁੱਖ type;
  ਰੁੱਖ fields;
  ਰੁੱਖ ਸੂਚਕਾਂਕ;
  ਰੁੱਖ max_ਸੂਚਕਾਂਕ;
  ਰੁੱਖ unfilled_ਸੂਚਕਾਂਕ;
  ਰੁੱਖ unfilled_fields;
  ਰੁੱਖ ਦੋਆਧਾਰੀ_ਅੰਕ_ਸੂਚਕਾਂਕ;
  vec<constructor_elt, va_gc> *elements;
  ਬਣਤਰ init_ਗੰਢ *pending_elts;
  ਪੂਰਨ ਵਿੱਥ;
  ਪੂਰਨ ਡੂੰਘਾਈ;
  /* If value nonzero, this value should replace the entire
     constructor at this level.  */
  ਬਣਤਰ c_ਵਿਅੰਜਕ replacement_ਮੁੱਲ;
  ਬਣਤਰ constructor_range_ਢੇਰ *range_ਢੇਰ;
  ਅੱਖਰ constant;
  ਅੱਖਰ simple;
  ਅੱਖਰ nonconst;
  ਅੱਖਰ implicit;
  ਅੱਖਰ erroneous;
  ਅੱਖਰ outer;
  ਅੱਖਰ incremental;
  ਅੱਖਰ designated;
  ਤਾਰਕਿਕ zero_padding_ਬਿੱਟ;
  ਤਾਰਕਿਕ braced_scalar;
  ਪੂਰਨ designator_ਡੂੰਘਾਈ;
};

ਸਥਿਰ ਬਣਤਰ constructor_ਢੇਰ *constructor_ਢੇਰ;

/* This stack represents designators from some range designator up to
   the last designator in the list.  */

ਬਣਤਰ constructor_range_ਢੇਰ
{
  ਬਣਤਰ constructor_range_ਢੇਰ *ਅਗਲਾ, *prev;
  ਬਣਤਰ constructor_ਢੇਰ *ਢੇਰ;
  ਰੁੱਖ range_ਸ਼ੁਰੂ;
  ਰੁੱਖ ਸੂਚਕਾਂਕ;
  ਰੁੱਖ range_ਸਿਰਾ;
  ਰੁੱਖ fields;
};

ਸਥਿਰ ਬਣਤਰ constructor_range_ਢੇਰ *constructor_range_ਢੇਰ;

/* This stack records separate initializers that are nested.
   Nested initializers can't happen in ANSI C, but GNU C allows them
   in cases like { ... (struct foo) { ... } ... }.  */

ਬਣਤਰ initializer_ਢੇਰ
{
  ਬਣਤਰ initializer_ਢੇਰ *ਅਗਲਾ;
  ਰੁੱਖ decl;
  ਬਣਤਰ constructor_ਢੇਰ *constructor_ਢੇਰ;
  ਬਣਤਰ constructor_range_ਢੇਰ *constructor_range_ਢੇਰ;
  vec<constructor_elt, va_gc> *elements;
  ਬਣਤਰ spelling *spelling;
  ਬਣਤਰ spelling *spelling_ਅਧਾਰ;
  ਪੂਰਨ spelling_ਮਾਪ;
  ਅੱਖਰ require_constant_ਮੁੱਲ;
  ਅੱਖਰ require_constant_elements;
  ਅੱਖਰ require_constexpr_ਮੁੱਲ;
  ਅੱਖਰ designated;
  rich_location *missing_brace_richloc;
};

ਸਥਿਰ ਬਣਤਰ initializer_ਢੇਰ *initializer_ਢੇਰ;

/* Prepare to parse and output the initializer for variable DECL.  */

ਖਾਲੀ
ਸ਼ੁਰੂ_init (ਰੁੱਖ decl, ਰੁੱਖ asmspec_ਰੁੱਖ ATTRIBUTE_ਅਣਵਰਤਿਆ,
	    ਤਾਰਕਿਕ init_require_constant, ਤਾਰਕਿਕ init_require_constexpr,
	    rich_location *richloc)
{
  ਅਚਲ ਅੱਖਰ *locus;
  ਬਣਤਰ initializer_ਢੇਰ *p = XNEW (ਬਣਤਰ initializer_ਢੇਰ);

  p->decl = constructor_decl;
  p->require_constant_ਮੁੱਲ = require_constant_ਮੁੱਲ;
  p->require_constant_elements = require_constant_elements;
  p->require_constexpr_ਮੁੱਲ = require_constexpr_ਮੁੱਲ;
  p->constructor_ਢੇਰ = constructor_ਢੇਰ;
  p->constructor_range_ਢੇਰ = constructor_range_ਢੇਰ;
  p->elements = constructor_elements;
  p->spelling = spelling;
  p->spelling_ਅਧਾਰ = spelling_ਅਧਾਰ;
  p->spelling_ਮਾਪ = spelling_ਮਾਪ;
  p->ਅਗਲਾ = initializer_ਢੇਰ;
  p->missing_brace_richloc = richloc;
  p->designated = constructor_designated;
  initializer_ਢੇਰ = p;

  constructor_decl = decl;
  constructor_designated = 0;

  require_constant_ਮੁੱਲ = init_require_constant;
  require_constexpr_ਮੁੱਲ = init_require_constexpr;
  ਜੇ (decl != NULL_ਰੁੱਖ && decl != error_mark_ਗੰਢ)
    {
      require_constant_elements
	= ((init_require_constant || (pedantic && !flag_isoc99))
	   /* For a scalar, you can always use any value to initialize,
	      even within braces.  */
	   && AGGREGATE_TYPE_P (ਰੁੱਖ_TYPE (decl)));
      locus = identifier_ਮੰਜ਼ਿਲ_locale (IDENTIFIER_ਸੂਚਕ (DECL_NAME (decl)));
    }
  ਨਹੀਂਤਾਂ
    {
      require_constant_elements = ਝੂਠ;
      locus = _("(anonymous)");
    }

  constructor_ਢੇਰ = 0;
  constructor_range_ਢੇਰ = 0;

  ਮਿਲਿਆ_missing_braces = 0;

  spelling_ਅਧਾਰ = 0;
  spelling_ਮਾਪ = 0;
  RESTORE_SPELLING_ਡੂੰਘਾਈ (0);

  ਜੇ (locus)
    ਧੱਕੋ_string (locus);
}

ਖਾਲੀ
ਅੰਤ_init (ਖਾਲੀ)
{
  ਬਣਤਰ initializer_ਢੇਰ *p = initializer_ਢੇਰ;

  /* Free the whole constructor stack of this initializer.  */
  ਜਦੋਂ (constructor_ਢੇਰ)
    {
      ਬਣਤਰ constructor_ਢੇਰ *q = constructor_ਢੇਰ;
      constructor_ਢੇਰ = q->ਅਗਲਾ;
      XDELETE (q);
    }

  gcc_assert (!constructor_range_ਢੇਰ);

  /* Pop back to the data of the outer initializer (if any).  */
  XDELETE (spelling_ਅਧਾਰ);

  constructor_decl = p->decl;
  require_constant_ਮੁੱਲ = p->require_constant_ਮੁੱਲ;
  require_constant_elements = p->require_constant_elements;
  require_constexpr_ਮੁੱਲ = p->require_constexpr_ਮੁੱਲ;
  constructor_ਢੇਰ = p->constructor_ਢੇਰ;
  constructor_designated = p->designated;
  constructor_range_ਢੇਰ = p->constructor_range_ਢੇਰ;
  constructor_elements = p->elements;
  spelling = p->spelling;
  spelling_ਅਧਾਰ = p->spelling_ਅਧਾਰ;
  spelling_ਮਾਪ = p->spelling_ਮਾਪ;
  initializer_ਢੇਰ = p->ਅਗਲਾ;
  XDELETE (p);
}

/* Call here when we see the initializer is surrounded by braces.
   This is instead of a call to push_init_level;
   it is matched by a call to pop_init_level.

   TYPE is the type to initialize, for a constructor expression.
   For an initializer for a decl, TYPE is zero.  */

ਖਾਲੀ
really_ਸ਼ੁਰੂ_incremental_init (ਰੁੱਖ type)
{
  ਬਣਤਰ constructor_ਢੇਰ *p = XNEW (ਬਣਤਰ constructor_ਢੇਰ);

  ਜੇ (type == NULL_ਰੁੱਖ)
    type = ਰੁੱਖ_TYPE (constructor_decl);

  ਜੇ (ਸਦਿਸ਼_TYPE_P (type)
      && TYPE_ਸਦਿਸ਼_OPAQUE (type))
    error ("opaque vector types cannot be initialized");

  p->type = constructor_type;
  p->fields = constructor_fields;
  p->ਸੂਚਕਾਂਕ = constructor_ਸੂਚਕਾਂਕ;
  p->max_ਸੂਚਕਾਂਕ = constructor_max_ਸੂਚਕਾਂਕ;
  p->unfilled_ਸੂਚਕਾਂਕ = constructor_unfilled_ਸੂਚਕਾਂਕ;
  p->unfilled_fields = constructor_unfilled_fields;
  p->ਦੋਆਧਾਰੀ_ਅੰਕ_ਸੂਚਕਾਂਕ = constructor_ਦੋਆਧਾਰੀ_ਅੰਕ_ਸੂਚਕਾਂਕ;
  p->elements = constructor_elements;
  p->constant = constructor_constant;
  p->simple = constructor_simple;
  p->nonconst = constructor_nonconst;
  p->erroneous = constructor_erroneous;
  p->pending_elts = constructor_pending_elts;
  p->ਡੂੰਘਾਈ = constructor_ਡੂੰਘਾਈ;
  p->replacement_ਮੁੱਲ.ਮੁੱਲ = 0;
  p->replacement_ਮੁੱਲ.original_ਕੋਡ = ERROR_MARK;
  p->replacement_ਮੁੱਲ.original_type = ਨਿਰਾ;
  p->implicit = 0;
  p->range_ਢੇਰ = 0;
  p->outer = 0;
  p->incremental = constructor_incremental;
  p->designated = constructor_designated;
  p->zero_padding_ਬਿੱਟ = constructor_zero_padding_ਬਿੱਟ;
  p->braced_scalar = constructor_braced_scalar;
  p->designator_ਡੂੰਘਾਈ = designator_ਡੂੰਘਾਈ;
  p->ਅਗਲਾ = 0;
  constructor_ਢੇਰ = p;

  constructor_constant = 1;
  constructor_simple = 1;
  constructor_nonconst = 0;
  constructor_ਡੂੰਘਾਈ = SPELLING_ਡੂੰਘਾਈ ();
  constructor_elements = ਨਿਰਾ;
  constructor_pending_elts = 0;
  constructor_type = type;
  constructor_incremental = 1;
  constructor_designated = 0;
  constructor_zero_padding_ਬਿੱਟ = ਝੂਠ;
  constructor_zeroinit = 1;
  constructor_braced_scalar = ਝੂਠ;
  designator_ਡੂੰਘਾਈ = 0;
  designator_erroneous = 0;

  ਜੇ (ਰਿਕਾਰਡ_OR_UNION_TYPE_P (constructor_type))
    {
      constructor_fields = TYPE_FIELDS (constructor_type);
      /* Skip any nameless bit fields at the beginning.  */
      ਜਦੋਂ (constructor_fields != NULL_ਰੁੱਖ
	     && DECL_UNNAMED_ਦੋਆਧਾਰੀ_ਅੰਕ_ਖੇਤਰ (constructor_fields))
	constructor_fields = DECL_CHAIN (constructor_fields);

      constructor_unfilled_fields = constructor_fields;
      constructor_ਦੋਆਧਾਰੀ_ਅੰਕ_ਸੂਚਕਾਂਕ = bitsize_zero_ਗੰਢ;
    }
  ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਕੋਡ (constructor_type) == ARRAY_TYPE)
    {
      ਜੇ (TYPE_DOMAIN (constructor_type))
	{
	  constructor_max_ਸੂਚਕਾਂਕ
	    = TYPE_MAX_ਮੁੱਲ (TYPE_DOMAIN (constructor_type));

	  /* Detect non-empty initializations of zero-length arrays.  */
	  ਜੇ (constructor_max_ਸੂਚਕਾਂਕ == NULL_ਰੁੱਖ
	      && TYPE_ਮਾਪ (constructor_type))
	    constructor_max_ਸੂਚਕਾਂਕ = integer_minus_one_ਗੰਢ;

	  /* constructor_max_index needs to be an INTEGER_CST.  Attempts
	     to initialize VLAs with a nonempty initializer will cause a
	     proper error; avoid tree checking errors as well by setting a
	     safe value.  */
	  ਜੇ (constructor_max_ਸੂਚਕਾਂਕ
	      && ਰੁੱਖ_ਕੋਡ (constructor_max_ਸੂਚਕਾਂਕ) != INTEGER_CST)
	    constructor_max_ਸੂਚਕਾਂਕ = integer_minus_one_ਗੰਢ;

	  constructor_ਸੂਚਕਾਂਕ
	    = convert (bitsizetype,
		       TYPE_MIN_ਮੁੱਲ (TYPE_DOMAIN (constructor_type)));
	}
      ਨਹੀਂਤਾਂ
	{
	  constructor_ਸੂਚਕਾਂਕ = bitsize_zero_ਗੰਢ;
	  constructor_max_ਸੂਚਕਾਂਕ = NULL_ਰੁੱਖ;
	}

      constructor_unfilled_ਸੂਚਕਾਂਕ = constructor_ਸੂਚਕਾਂਕ;
    }
  ਨਹੀਂਤਾਂ ਜੇ (gnu_ਸਦਿਸ਼_type_p (constructor_type))
    {
      /* Vectors are like simple fixed-size arrays.  */
      constructor_max_ਸੂਚਕਾਂਕ =
	bitsize_int (TYPE_ਸਦਿਸ਼_SUBPARTS (constructor_type) - 1);
      constructor_ਸੂਚਕਾਂਕ = bitsize_zero_ਗੰਢ;
      constructor_unfilled_ਸੂਚਕਾਂਕ = constructor_ਸੂਚਕਾਂਕ;
    }
  ਨਹੀਂਤਾਂ
    {
      /* Handle the case of int x = {5}; */
      constructor_fields = constructor_type;
      constructor_unfilled_fields = constructor_type;
      constructor_braced_scalar = ਸੱਚ;
    }
}

ਬਾਹਰੀ location_t ਆਖਰੀ_init_list_comma;

/* Called when we see an open brace for a nested initializer.  Finish
   off any pending levels with implicit braces.  */
ਖਾਲੀ
ਅੰਤ_implicit_inits (location_t loc, ਬਣਤਰ obstack *braced_init_obstack)
{
  ਜਦੋਂ (constructor_ਢੇਰ->implicit)
    {
      ਜੇ (ਰਿਕਾਰਡ_OR_UNION_TYPE_P (constructor_type)
	  && constructor_fields == NULL_ਰੁੱਖ)
	process_init_element (ਨਿਵੇਸ਼_location,
			      ਕੱਢੋ_init_level (loc, 1, braced_init_obstack,
					      ਆਖਰੀ_init_list_comma),
			      ਸੱਚ, braced_init_obstack);
      ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਕੋਡ (constructor_type) == ARRAY_TYPE
	       && constructor_max_ਸੂਚਕਾਂਕ
	       && ਰੁੱਖ_int_cst_lt (constructor_max_ਸੂਚਕਾਂਕ,
				   constructor_ਸੂਚਕਾਂਕ))
	process_init_element (ਨਿਵੇਸ਼_location,
			      ਕੱਢੋ_init_level (loc, 1, braced_init_obstack,
					      ਆਖਰੀ_init_list_comma),
			      ਸੱਚ, braced_init_obstack);
      ਨਹੀਂਤਾਂ
	ਰੋਕੋ;
    }
}

/* Push down into a subobject, for initialization.
   If this is for an explicit set of braces, IMPLICIT is 0.
   If it is because the next element belongs at a lower level,
   IMPLICIT is 1 (or 2 if the push is because of designator list).  */

ਖਾਲੀ
ਧੱਕੋ_init_level (location_t loc, ਪੂਰਨ implicit,
		 ਬਣਤਰ obstack *braced_init_obstack)
{
  ਬਣਤਰ constructor_ਢੇਰ *p;
  ਰੁੱਖ ਮੁੱਲ = NULL_ਰੁੱਖ;

  /* Unless this is an explicit brace, we need to preserve previous
     content if any.  */
  ਜੇ (implicit)
    {
      ਜੇ (ਰਿਕਾਰਡ_OR_UNION_TYPE_P (constructor_type) && constructor_fields)
	ਮੁੱਲ = ਲੱਭੋ_init_member (constructor_fields, braced_init_obstack);
      ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਕੋਡ (constructor_type) == ARRAY_TYPE)
	ਮੁੱਲ = ਲੱਭੋ_init_member (constructor_ਸੂਚਕਾਂਕ, braced_init_obstack);
    }

  p = XNEW (ਬਣਤਰ constructor_ਢੇਰ);
  p->type = constructor_type;
  p->fields = constructor_fields;
  p->ਸੂਚਕਾਂਕ = constructor_ਸੂਚਕਾਂਕ;
  p->max_ਸੂਚਕਾਂਕ = constructor_max_ਸੂਚਕਾਂਕ;
  p->unfilled_ਸੂਚਕਾਂਕ = constructor_unfilled_ਸੂਚਕਾਂਕ;
  p->unfilled_fields = constructor_unfilled_fields;
  p->ਦੋਆਧਾਰੀ_ਅੰਕ_ਸੂਚਕਾਂਕ = constructor_ਦੋਆਧਾਰੀ_ਅੰਕ_ਸੂਚਕਾਂਕ;
  p->elements = constructor_elements;
  p->constant = constructor_constant;
  p->simple = constructor_simple;
  p->nonconst = constructor_nonconst;
  p->erroneous = constructor_erroneous;
  p->pending_elts = constructor_pending_elts;
  p->ਡੂੰਘਾਈ = constructor_ਡੂੰਘਾਈ;
  p->replacement_ਮੁੱਲ.ਮੁੱਲ = NULL_ਰੁੱਖ;
  p->replacement_ਮੁੱਲ.original_ਕੋਡ = ERROR_MARK;
  p->replacement_ਮੁੱਲ.original_type = ਨਿਰਾ;
  p->implicit = implicit;
  p->outer = 0;
  p->incremental = constructor_incremental;
  p->designated = constructor_designated;
  p->zero_padding_ਬਿੱਟ = constructor_zero_padding_ਬਿੱਟ;
  p->braced_scalar = constructor_braced_scalar;
  p->designator_ਡੂੰਘਾਈ = designator_ਡੂੰਘਾਈ;
  p->ਅਗਲਾ = constructor_ਢੇਰ;
  p->range_ਢੇਰ = 0;
  constructor_ਢੇਰ = p;

  constructor_constant = 1;
  constructor_simple = 1;
  constructor_nonconst = 0;
  constructor_ਡੂੰਘਾਈ = SPELLING_ਡੂੰਘਾਈ ();
  constructor_elements = ਨਿਰਾ;
  constructor_incremental = 1;
  /* If the upper initializer is designated, then mark this as
     designated too to prevent bogus warnings.  */
  constructor_designated = p->designated;
  /* If the upper initializer has padding bits zeroed, that includes
     all nested initializers as well.  */
  constructor_zero_padding_ਬਿੱਟ = p->zero_padding_ਬਿੱਟ;
  constructor_braced_scalar = ਝੂਠ;
  constructor_pending_elts = 0;
  ਜੇ (!implicit)
    {
      p->range_ਢੇਰ = constructor_range_ਢੇਰ;
      constructor_range_ਢੇਰ = 0;
      designator_ਡੂੰਘਾਈ = 0;
      designator_erroneous = 0;
    }

  /* Don't die if an entire brace-pair level is superfluous
     in the containing level.  */
  ਜੇ (constructor_type == NULL_ਰੁੱਖ)
    ;
  ਨਹੀਂਤਾਂ ਜੇ (ਰਿਕਾਰਡ_OR_UNION_TYPE_P (constructor_type))
    {
      /* Don't die if there are extra init elts at the end.  */
      ਜੇ (constructor_fields == NULL_ਰੁੱਖ)
	constructor_type = NULL_ਰੁੱਖ;
      ਨਹੀਂਤਾਂ
	{
	  constructor_type = ਰੁੱਖ_TYPE (constructor_fields);
	  ਧੱਕੋ_member_name (constructor_fields);
	  constructor_ਡੂੰਘਾਈ++;
	}
    }
  ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਕੋਡ (constructor_type) == ARRAY_TYPE)
    {
      constructor_type = ਰੁੱਖ_TYPE (constructor_type);
      ਧੱਕੋ_array_bounds (ਰੁੱਖ_ਮੰਜ਼ਿਲ_uhwi (constructor_ਸੂਚਕਾਂਕ));
      constructor_ਡੂੰਘਾਈ++;
    }

  ਜੇ (constructor_type == NULL_ਰੁੱਖ)
    {
      error_init (loc, "extra brace group at end of initializer");
      constructor_fields = NULL_ਰੁੱਖ;
      constructor_unfilled_fields = NULL_ਰੁੱਖ;
      ਵਾਪਸ;
    }

  ਜੇ (ਮੁੱਲ && ਰੁੱਖ_ਕੋਡ (ਮੁੱਲ) == CONSTRUCTOR)
    {
      constructor_constant = ਰੁੱਖ_CONSTANT (ਮੁੱਲ);
      constructor_simple = ਰੁੱਖ_STATIC (ਮੁੱਲ);
      constructor_nonconst = CONSTRUCTOR_NON_CONST (ਮੁੱਲ);
      constructor_elements = CONSTRUCTOR_ELTS (ਮੁੱਲ);
      constructor_zero_padding_ਬਿੱਟ |= CONSTRUCTOR_ZERO_PADDING_ਬਿੱਟ (ਮੁੱਲ);
      ਜੇ (!vec_ਸੁਰੱਖਿਅਤ_is_ਖਾਲੀ_ਥਾਵਾਂ (constructor_elements)
	  && (ਰੁੱਖ_ਕੋਡ (constructor_type) == ਰਿਕਾਰਡ_TYPE
	      || ਰੁੱਖ_ਕੋਡ (constructor_type) == ARRAY_TYPE))
	ਸੈੱਟ_nonincremental_init (braced_init_obstack);
    }

  ਜੇ (implicit == 1)
    {
      ਮਿਲਿਆ_missing_braces = 1;
      ਜੇ (initializer_ਢੇਰ->missing_brace_richloc)
	initializer_ਢੇਰ->missing_brace_richloc->ਜੋੜੋ_fixit_ਪਾਓ_before
	  (loc, "{");
    }

  ਜੇ (ਰਿਕਾਰਡ_OR_UNION_TYPE_P (constructor_type))
    {
      constructor_fields = TYPE_FIELDS (constructor_type);
      /* Skip any nameless bit fields at the beginning.  */
      ਜਦੋਂ (constructor_fields != NULL_ਰੁੱਖ
	     && DECL_UNNAMED_ਦੋਆਧਾਰੀ_ਅੰਕ_ਖੇਤਰ (constructor_fields))
	constructor_fields = DECL_CHAIN (constructor_fields);

      constructor_unfilled_fields = constructor_fields;
      constructor_ਦੋਆਧਾਰੀ_ਅੰਕ_ਸੂਚਕਾਂਕ = bitsize_zero_ਗੰਢ;
    }
  ਨਹੀਂਤਾਂ ਜੇ (gnu_ਸਦਿਸ਼_type_p (constructor_type))
    {
      /* Vectors are like simple fixed-size arrays.  */
      constructor_max_ਸੂਚਕਾਂਕ =
	bitsize_int (TYPE_ਸਦਿਸ਼_SUBPARTS (constructor_type) - 1);
      constructor_ਸੂਚਕਾਂਕ = bitsize_int (0);
      constructor_unfilled_ਸੂਚਕਾਂਕ = constructor_ਸੂਚਕਾਂਕ;
    }
  ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਕੋਡ (constructor_type) == ARRAY_TYPE)
    {
      ਜੇ (TYPE_DOMAIN (constructor_type))
	{
	  constructor_max_ਸੂਚਕਾਂਕ
	    = TYPE_MAX_ਮੁੱਲ (TYPE_DOMAIN (constructor_type));

	  /* Detect non-empty initializations of zero-length arrays.  */
	  ਜੇ (constructor_max_ਸੂਚਕਾਂਕ == NULL_ਰੁੱਖ
	      && TYPE_ਮਾਪ (constructor_type))
	    constructor_max_ਸੂਚਕਾਂਕ = integer_minus_one_ਗੰਢ;

	  /* constructor_max_index needs to be an INTEGER_CST.  Attempts
	     to initialize VLAs will cause a proper error; avoid tree
	     checking errors as well by setting a safe value.  */
	  ਜੇ (constructor_max_ਸੂਚਕਾਂਕ
	      && ਰੁੱਖ_ਕੋਡ (constructor_max_ਸੂਚਕਾਂਕ) != INTEGER_CST)
	    constructor_max_ਸੂਚਕਾਂਕ = integer_minus_one_ਗੰਢ;

	  constructor_ਸੂਚਕਾਂਕ
	    = convert (bitsizetype,
		       TYPE_MIN_ਮੁੱਲ (TYPE_DOMAIN (constructor_type)));
	}
      ਨਹੀਂਤਾਂ
	constructor_ਸੂਚਕਾਂਕ = bitsize_zero_ਗੰਢ;

      constructor_unfilled_ਸੂਚਕਾਂਕ = constructor_ਸੂਚਕਾਂਕ;
      ਜੇ (ਮੁੱਲ && ਰੁੱਖ_ਕੋਡ (ਮੁੱਲ) == STRING_CST)
	{
	  /* We need to split the char/wchar array into individual
	     characters, so that we don't have to special case it
	     everywhere.  */
	  ਸੈੱਟ_nonincremental_init_from_string (ਮੁੱਲ, braced_init_obstack);
	}
    }
  ਨਹੀਂਤਾਂ
    {
      ਜੇ (constructor_type != error_mark_ਗੰਢ)
	{
	  ਜੇ (p->braced_scalar)
	    permerror_init (ਨਿਵੇਸ਼_location, 0,
			    "braces around scalar initializer");
	  ਨਹੀਂਤਾਂ
	    warning_init (ਨਿਵੇਸ਼_location, 0,
			  "braces around scalar initializer");
	  constructor_braced_scalar = ਸੱਚ;
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

ਬਣਤਰ c_ਵਿਅੰਜਕ
ਕੱਢੋ_init_level (location_t loc, ਪੂਰਨ implicit,
		ਬਣਤਰ obstack *braced_init_obstack,
		location_t ਪਾਓ_before)
{
  ਬਣਤਰ constructor_ਢੇਰ *p;
  ਬਣਤਰ c_ਵਿਅੰਜਕ ret;
  ret.ਮੁੱਲ = NULL_ਰੁੱਖ;
  ret.original_ਕੋਡ = ERROR_MARK;
  ret.original_type = ਨਿਰਾ;
  ret.m_decimal = 0;

  ਜੇ (implicit == 0)
    {
      /* When we come to an explicit close brace,
	 pop any inner levels that didn't have explicit braces.  */
      ਜਦੋਂ (constructor_ਢੇਰ->implicit)
	process_init_element (ਨਿਵੇਸ਼_location,
			      ਕੱਢੋ_init_level (loc, 1, braced_init_obstack,
					      ਪਾਓ_before),
			      ਸੱਚ, braced_init_obstack);
      gcc_assert (!constructor_range_ਢੇਰ);
    }
  ਨਹੀਂਤਾਂ
    ਜੇ (initializer_ਢੇਰ->missing_brace_richloc)
      initializer_ਢੇਰ->missing_brace_richloc->ਜੋੜੋ_fixit_ਪਾਓ_before
	(ਪਾਓ_before, "}");

  /* Now output all pending elements.  */
  constructor_incremental = 1;
  output_pending_init_elements (1, braced_init_obstack);

  p = constructor_ਢੇਰ;

  /* Error for initializing a flexible array member.  */
  ਜੇ (constructor_type && constructor_fields
      && flexible_array_member_type_p (constructor_type))
    {
      /* Silently discard empty initializations.  The parser will
	 already have pedwarned for empty brackets for C17 and earlier.  */
      ਜੇ (integer_zerop (constructor_unfilled_ਸੂਚਕਾਂਕ))
	constructor_type = NULL_ਰੁੱਖ;
      ਜੇ (constructor_type || flag_isoc23)
	{
	  gcc_assert (!constructor_type || !TYPE_ਮਾਪ (constructor_type));

	  ਜੇ (constructor_ਡੂੰਘਾਈ <= 2)
	    pedwarn_init (loc, OPT_Wpedantic,
			  "initialization of a flexible array member");
	  ਨਹੀਂਤਾਂ ਜੇ (constructor_type)
	    error_init (loc, "initialization of flexible array member "
			     "in a nested context");
	  ਨਹੀਂਤਾਂ
	    pedwarn_init (loc, OPT_Wpedantic,
			  "initialization of flexible array member "
			  "in a nested context");

	  /* We have already issued an error message for the existence
	     of a flexible array member not at the end of the structure.
	     Discard the initializer so that we do not die later.  */
	  ਜੇ (constructor_type
	      && DECL_CHAIN (constructor_fields) != NULL_ਰੁੱਖ
	      && (!p->type || ਰੁੱਖ_ਕੋਡ (p->type) != UNION_TYPE))
	    constructor_type = NULL_ਰੁੱਖ;
	}
    }

  ਚੋਣ (vec_ਸੁਰੱਖਿਅਤ_ਲੰਮਾਈ (constructor_elements))
    {
    ਹਾਲਤ 0:
      /* Initialization with { } counts as zeroinit.  */
      constructor_zeroinit = 1;
      ਰੋਕੋ;
    ਹਾਲਤ 1:
      /* This might be zeroinit as well.  */
      ਜੇ (integer_zerop ((*constructor_elements)[0].ਮੁੱਲ))
	constructor_zeroinit = 1;
      ਰੋਕੋ;
    ਮੂਲ:
      /* If the constructor has more than one element, it can't be { 0 }.  */
      constructor_zeroinit = 0;
      ਰੋਕੋ;
    }

  /* Warn when some structs are initialized with direct aggregation.  */
  ਜੇ (!implicit && ਮਿਲਿਆ_missing_braces && warn_missing_braces
      && !constructor_zeroinit)
    {
      gcc_assert (initializer_ਢੇਰ->missing_brace_richloc);
      warning_at (initializer_ਢੇਰ->missing_brace_richloc,
		  OPT_Wmissing_braces,
		  "missing braces around initializer");
    }

  /* Warn when some struct elements are implicitly initialized to zero.  */
  ਜੇ (warn_missing_ਖੇਤਰ_initializers
      && constructor_type
      && ਰੁੱਖ_ਕੋਡ (constructor_type) == ਰਿਕਾਰਡ_TYPE
      && constructor_unfilled_fields)
    {
	/* Do not warn for flexible array members or zero-length arrays.  */
	ਜਦੋਂ (constructor_unfilled_fields
	       && (!DECL_ਮਾਪ (constructor_unfilled_fields)
		   || integer_zerop (DECL_ਮਾਪ (constructor_unfilled_fields))))
	  constructor_unfilled_fields = DECL_CHAIN (constructor_unfilled_fields);

	ਜੇ (constructor_unfilled_fields
	    /* Do not warn if this level of the initializer uses member
	       designators; it is likely to be deliberate.  */
	    && !constructor_designated
	    /* Do not warn about initializing with { 0 } or with { }.  */
	    && !constructor_zeroinit)
	  {
	    ਜੇ (warning_at (ਨਿਵੇਸ਼_location, OPT_Wmissing_ਖੇਤਰ_initializers,
			    "missing initializer for field %qD of %qT",
			    constructor_unfilled_fields,
			    constructor_type))
	      inform (DECL_ਸਰੋਤ_LOCATION (constructor_unfilled_fields),
		      "%qD declared here", constructor_unfilled_fields);
	  }
    }

  /* Pad out the end of the structure.  */
  ਜੇ (p->replacement_ਮੁੱਲ.ਮੁੱਲ)
    /* If this closes a superfluous brace pair,
       just pass out the element between them.  */
    ret = p->replacement_ਮੁੱਲ;
  ਨਹੀਂਤਾਂ ਜੇ (constructor_type == NULL_ਰੁੱਖ)
    ;
  ਨਹੀਂਤਾਂ ਜੇ (!ਰਿਕਾਰਡ_OR_UNION_TYPE_P (constructor_type)
	   && ਰੁੱਖ_ਕੋਡ (constructor_type) != ARRAY_TYPE
	   && !gnu_ਸਦਿਸ਼_type_p (constructor_type))
    {
      /* A nonincremental scalar initializer--just return
	 the element, after verifying there is just one.
         Empty scalar initializers are supported in C23.  */
      ਜੇ (vec_ਸੁਰੱਖਿਅਤ_is_ਖਾਲੀ_ਥਾਵਾਂ (constructor_elements))
	{
	  ਜੇ (constructor_erroneous || constructor_type == error_mark_ਗੰਢ)
	    ret.ਮੁੱਲ = error_mark_ਗੰਢ;
	  ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਕੋਡ (constructor_type) == FUNCTION_TYPE)
	    {
	      error_init (loc, "invalid initializer");
	      ret.ਮੁੱਲ = error_mark_ਗੰਢ;
	    }
	  ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਕੋਡ (constructor_type) == ਸੂਚਕ_TYPE)
	    /* Ensure this is a null pointer constant in the case of a
	       'constexpr' object initialized with {}.  */
	    ret.ਮੁੱਲ = build_zero_cst (ptr_type_ਗੰਢ);
	  ਨਹੀਂਤਾਂ
	    ret.ਮੁੱਲ = build_zero_cst (constructor_type);
	}
      ਨਹੀਂਤਾਂ ਜੇ (vec_ਸੁਰੱਖਿਅਤ_ਲੰਮਾਈ (constructor_elements) != 1)
	{
	  error_init (loc, "extra elements in scalar initializer");
	  ret.ਮੁੱਲ = (*constructor_elements)[0].ਮੁੱਲ;
	}
      ਨਹੀਂਤਾਂ
	ret.ਮੁੱਲ = (*constructor_elements)[0].ਮੁੱਲ;
    }
  ਨਹੀਂਤਾਂ
    {
      ਜੇ (constructor_erroneous)
	ret.ਮੁੱਲ = error_mark_ਗੰਢ;
      ਨਹੀਂਤਾਂ
	{
	  ret.ਮੁੱਲ = build_constructor (constructor_type,
					 constructor_elements);
	  ਜੇ (constructor_constant)
	    ਰੁੱਖ_CONSTANT (ret.ਮੁੱਲ) = 1;
	  ਜੇ (constructor_constant && constructor_simple)
	    ਰੁੱਖ_STATIC (ret.ਮੁੱਲ) = 1;
	  ਜੇ (constructor_nonconst)
	    CONSTRUCTOR_NON_CONST (ret.ਮੁੱਲ) = 1;
	  ਜੇ (constructor_zero_padding_ਬਿੱਟ)
	    CONSTRUCTOR_ZERO_PADDING_ਬਿੱਟ (ret.ਮੁੱਲ) = 1;
	}
    }

  ਜੇ (ret.ਮੁੱਲ && ਰੁੱਖ_ਕੋਡ (ret.ਮੁੱਲ) != CONSTRUCTOR)
    {
      ਜੇ (constructor_nonconst)
	ret.original_ਕੋਡ = C_MAYBE_CONST_ਵਿਅੰਜਕ;
      ਨਹੀਂਤਾਂ ਜੇ (ret.original_ਕੋਡ == C_MAYBE_CONST_ਵਿਅੰਜਕ)
	ret.original_ਕੋਡ = ERROR_MARK;
    }

  constructor_type = p->type;
  constructor_fields = p->fields;
  constructor_ਸੂਚਕਾਂਕ = p->ਸੂਚਕਾਂਕ;
  constructor_max_ਸੂਚਕਾਂਕ = p->max_ਸੂਚਕਾਂਕ;
  constructor_unfilled_ਸੂਚਕਾਂਕ = p->unfilled_ਸੂਚਕਾਂਕ;
  constructor_unfilled_fields = p->unfilled_fields;
  constructor_ਦੋਆਧਾਰੀ_ਅੰਕ_ਸੂਚਕਾਂਕ = p->ਦੋਆਧਾਰੀ_ਅੰਕ_ਸੂਚਕਾਂਕ;
  constructor_elements = p->elements;
  constructor_constant = p->constant;
  constructor_simple = p->simple;
  constructor_nonconst = p->nonconst;
  constructor_erroneous = p->erroneous;
  constructor_incremental = p->incremental;
  constructor_designated = p->designated;
  constructor_zero_padding_ਬਿੱਟ = p->zero_padding_ਬਿੱਟ;
  constructor_braced_scalar = p->braced_scalar;
  designator_ਡੂੰਘਾਈ = p->designator_ਡੂੰਘਾਈ;
  constructor_pending_elts = p->pending_elts;
  constructor_ਡੂੰਘਾਈ = p->ਡੂੰਘਾਈ;
  ਜੇ (!p->implicit)
    constructor_range_ਢੇਰ = p->range_ਢੇਰ;
  RESTORE_SPELLING_ਡੂੰਘਾਈ (constructor_ਡੂੰਘਾਈ);

  constructor_ਢੇਰ = p->ਅਗਲਾ;
  XDELETE (p);

  ਜੇ (ret.ਮੁੱਲ == NULL_ਰੁੱਖ && constructor_ਢੇਰ == 0)
    ret.ਮੁੱਲ = error_mark_ਗੰਢ;
  ਵਾਪਸ ret;
}

/* Common handling for both array range and field name designators.
   ARRAY argument is nonzero for array ranges.  Returns false for success.  */

ਸਥਿਰ ਤਾਰਕਿਕ
ਸੈੱਟ_designator (location_t loc, ਤਾਰਕਿਕ array,
		ਬਣਤਰ obstack *braced_init_obstack)
{
  ਰੁੱਖ subtype;
  ਗਿਣਤੀ ਰੁੱਖ_ਕੋਡ_2 subcode;

  /* Don't die if an entire brace-pair level is superfluous
     in the containing level, or for an erroneous type.  */
  ਜੇ (constructor_type == NULL_ਰੁੱਖ || constructor_type == error_mark_ਗੰਢ)
    ਵਾਪਸ ਸੱਚ;

  /* If there were errors in this designator list already, bail out
     silently.  */
  ਜੇ (designator_erroneous)
    ਵਾਪਸ ਸੱਚ;

  /* Likewise for an initializer for a variable-size type.  Those are
     diagnosed in the parser, except for empty initializer braces.  */
  ਜੇ (COMPLETE_TYPE_P (constructor_type)
      && ਰੁੱਖ_ਕੋਡ (TYPE_ਮਾਪ (constructor_type)) != INTEGER_CST)
    ਵਾਪਸ ਸੱਚ;

  ਜੇ (!designator_ਡੂੰਘਾਈ)
    {
      gcc_assert (!constructor_range_ਢੇਰ);

      /* Designator list starts at the level of closest explicit
	 braces.  */
      ਜਦੋਂ (constructor_ਢੇਰ->implicit)
	process_init_element (ਨਿਵੇਸ਼_location,
			      ਕੱਢੋ_init_level (loc, 1, braced_init_obstack,
					      ਆਖਰੀ_init_list_comma),
			      ਸੱਚ, braced_init_obstack);
      constructor_designated = 1;
      ਵਾਪਸ ਝੂਠ;
    }

  ਚੋਣ (ਰੁੱਖ_ਕੋਡ (constructor_type))
    {
    ਹਾਲਤ  ਰਿਕਾਰਡ_TYPE:
    ਹਾਲਤ  UNION_TYPE:
      subtype = ਰੁੱਖ_TYPE (constructor_fields);
      ਜੇ (subtype != error_mark_ਗੰਢ)
	subtype = TYPE_MAIN_VARIANT (subtype);
      ਰੋਕੋ;
    ਹਾਲਤ ARRAY_TYPE:
      subtype = TYPE_MAIN_VARIANT (ਰੁੱਖ_TYPE (constructor_type));
      ਰੋਕੋ;
    ਮੂਲ:
      gcc_unreachable ();
    }

  subcode = ਰੁੱਖ_ਕੋਡ (subtype);
  ਜੇ (array && subcode != ARRAY_TYPE)
    {
      error_init (loc, "array index in non-array initializer");
      ਵਾਪਸ ਸੱਚ;
    }
  ਨਹੀਂਤਾਂ ਜੇ (!array && subcode != ਰਿਕਾਰਡ_TYPE && subcode != UNION_TYPE)
    {
      error_init (loc, "field name not in record or union initializer");
      ਵਾਪਸ ਸੱਚ;
    }

  constructor_designated = 1;
  ਅੰਤ_implicit_inits (loc, braced_init_obstack);
  ਧੱਕੋ_init_level (loc, 2, braced_init_obstack);
  ਵਾਪਸ ਝੂਠ;
}

/* If there are range designators in designator list, push a new designator
   to constructor_range_stack.  RANGE_END is end of such stack range or
   NULL_TREE if there is no range designator at this level.  */

ਸਥਿਰ ਖਾਲੀ
ਧੱਕੋ_range_ਢੇਰ (ਰੁੱਖ range_ਸਿਰਾ, ਬਣਤਰ obstack * braced_init_obstack)
{
  ਬਣਤਰ constructor_range_ਢੇਰ *p;

  p = (ਬਣਤਰ constructor_range_ਢੇਰ *)
    obstack_alloc (braced_init_obstack,
		   ਆਕਾਰ (ਬਣਤਰ constructor_range_ਢੇਰ));
  p->prev = constructor_range_ਢੇਰ;
  p->ਅਗਲਾ = 0;
  p->fields = constructor_fields;
  p->range_ਸ਼ੁਰੂ = constructor_ਸੂਚਕਾਂਕ;
  p->ਸੂਚਕਾਂਕ = constructor_ਸੂਚਕਾਂਕ;
  p->ਢੇਰ = constructor_ਢੇਰ;
  p->range_ਸਿਰਾ = range_ਸਿਰਾ;
  ਜੇ (constructor_range_ਢੇਰ)
    constructor_range_ਢੇਰ->ਅਗਲਾ = p;
  constructor_range_ਢੇਰ = p;
}

/* Within an array initializer, specify the next index to be initialized.
   FIRST is that index.  If LAST is nonzero, then initialize a range
   of indices, running from FIRST through LAST.  */

ਖਾਲੀ
ਸੈੱਟ_init_ਸੂਚਕਾਂਕ (location_t loc, ਰੁੱਖ ਪਹਿਲਾ, ਰੁੱਖ ਆਖਰੀ,
		ਬਣਤਰ obstack *braced_init_obstack)
{
  ਜੇ (ਸੈੱਟ_designator (loc, ਸੱਚ, braced_init_obstack))
    ਵਾਪਸ;

  designator_erroneous = 1;

  ਜੇ (!INTEGRAL_TYPE_P (ਰੁੱਖ_TYPE (ਪਹਿਲਾ))
      || (ਆਖਰੀ && !INTEGRAL_TYPE_P (ਰੁੱਖ_TYPE (ਆਖਰੀ))))
    {
      error_init (loc, "array index in initializer not of integer type");
      ਵਾਪਸ;
    }

  ਜੇ (ਰੁੱਖ_ਕੋਡ (ਪਹਿਲਾ) != INTEGER_CST)
    {
      ਪਹਿਲਾ = c_fully_fold (ਪਹਿਲਾ, ਝੂਠ, ਨਿਰਾ);
      ਜੇ (ਰੁੱਖ_ਕੋਡ (ਪਹਿਲਾ) == INTEGER_CST)
	pedwarn_init (loc, OPT_Wpedantic,
		      "array index in initializer is not "
		      "an integer constant expression");
    }

  ਜੇ (ਆਖਰੀ && ਰੁੱਖ_ਕੋਡ (ਆਖਰੀ) != INTEGER_CST)
    {
      ਆਖਰੀ = c_fully_fold (ਆਖਰੀ, ਝੂਠ, ਨਿਰਾ);
      ਜੇ (ਰੁੱਖ_ਕੋਡ (ਆਖਰੀ) == INTEGER_CST)
	pedwarn_init (loc, OPT_Wpedantic,
		      "array index in initializer is not "
		      "an integer constant expression");
    }

  ਜੇ (ਰੁੱਖ_ਕੋਡ (ਪਹਿਲਾ) != INTEGER_CST)
    error_init (loc, "nonconstant array index in initializer");
  ਨਹੀਂਤਾਂ ਜੇ (ਆਖਰੀ != NULL_ਰੁੱਖ && ਰੁੱਖ_ਕੋਡ (ਆਖਰੀ) != INTEGER_CST)
    error_init (loc, "nonconstant array index in initializer");
  ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਕੋਡ (constructor_type) != ARRAY_TYPE)
    error_init (loc, "array index in non-array initializer");
  ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_int_cst_sgn (ਪਹਿਲਾ) == -1)
    error_init (loc, "array index in initializer exceeds array bounds");
  ਨਹੀਂਤਾਂ ਜੇ (constructor_max_ਸੂਚਕਾਂਕ
	   && ਰੁੱਖ_int_cst_lt (constructor_max_ਸੂਚਕਾਂਕ, ਪਹਿਲਾ))
    error_init (loc, "array index in initializer exceeds array bounds");
  ਨਹੀਂਤਾਂ
    {
      constant_ਵਿਅੰਜਕ_warning (ਪਹਿਲਾ);
      ਜੇ (ਆਖਰੀ)
	constant_ਵਿਅੰਜਕ_warning (ਆਖਰੀ);
      constructor_ਸੂਚਕਾਂਕ = convert (bitsizetype, ਪਹਿਲਾ);
      ਜੇ (ਰੁੱਖ_int_cst_lt (constructor_ਸੂਚਕਾਂਕ, ਪਹਿਲਾ))
	{
	  constructor_ਸੂਚਕਾਂਕ = copy_ਗੰਢ (constructor_ਸੂਚਕਾਂਕ);
	  ਰੁੱਖ_ਉਛਾਲ (constructor_ਸੂਚਕਾਂਕ) = 1;
	}

      ਜੇ (ਆਖਰੀ)
	{
	  ਜੇ (ਰੁੱਖ_int_cst_equal (ਪਹਿਲਾ, ਆਖਰੀ))
	    ਆਖਰੀ = NULL_ਰੁੱਖ;
	  ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_int_cst_lt (ਆਖਰੀ, ਪਹਿਲਾ))
	    {
	      error_init (loc, "empty index range in initializer");
	      ਆਖਰੀ = NULL_ਰੁੱਖ;
	    }
	  ਨਹੀਂਤਾਂ
	    {
	      ਆਖਰੀ = convert (bitsizetype, ਆਖਰੀ);
	      ਜੇ (constructor_max_ਸੂਚਕਾਂਕ != NULL_ਰੁੱਖ
		  && ਰੁੱਖ_int_cst_lt (constructor_max_ਸੂਚਕਾਂਕ, ਆਖਰੀ))
		{
		  error_init (loc, "array index range in initializer exceeds "
			      "array bounds");
		  ਆਖਰੀ = NULL_ਰੁੱਖ;
		}
	    }
	}

      designator_ਡੂੰਘਾਈ++;
      designator_erroneous = 0;
      ਜੇ (constructor_range_ਢੇਰ || ਆਖਰੀ)
	ਧੱਕੋ_range_ਢੇਰ (ਆਖਰੀ, braced_init_obstack);
    }
}

/* Within a struct initializer, specify the next field to be initialized.  */

ਖਾਲੀ
ਸੈੱਟ_init_label (location_t loc, ਰੁੱਖ fieldname, location_t fieldname_loc,
		ਬਣਤਰ obstack *braced_init_obstack)
{
  ਰੁੱਖ ਖੇਤਰ_2;

  ਜੇ (ਸੈੱਟ_designator (loc, ਝੂਠ, braced_init_obstack))
    ਵਾਪਸ;

  designator_erroneous = 1;

  ਜੇ (!ਰਿਕਾਰਡ_OR_UNION_TYPE_P (constructor_type))
    {
      error_init (loc, "field name not in record or union initializer");
      ਵਾਪਸ;
    }

  ਖੇਤਰ_2 = lookup_ਖੇਤਰ (constructor_type, fieldname);

  ਜੇ (ਖੇਤਰ_2 == NULL_ਰੁੱਖ)
    {
      ਰੁੱਖ guessed_id = lookup_ਖੇਤਰ_fuzzy (constructor_type, fieldname);
      ਜੇ (guessed_id)
	{
	  gcc_rich_location rich_loc (fieldname_loc);
	  rich_loc.ਜੋੜੋ_fixit_misspelled_id (fieldname_loc, guessed_id);
	  error_at (&rich_loc,
		    "%qT has no member named %qE; did you mean %qE?",
		    constructor_type, fieldname, guessed_id);
	}
      ਨਹੀਂਤਾਂ
	error_at (fieldname_loc, "%qT has no member named %qE",
		  constructor_type, fieldname);
    }
  ਨਹੀਂਤਾਂ
    ਕਰੋ
      {
	constructor_fields = ਰੁੱਖ_ਮੁੱਲ (ਖੇਤਰ_2);
	designator_ਡੂੰਘਾਈ++;
	designator_erroneous = 0;
	ਜੇ (constructor_range_ਢੇਰ)
	  ਧੱਕੋ_range_ਢੇਰ (NULL_ਰੁੱਖ, braced_init_obstack);
	ਖੇਤਰ_2 = ਰੁੱਖ_CHAIN (ਖੇਤਰ_2);
	ਜੇ (ਖੇਤਰ_2)
	  {
	    ਜੇ (ਸੈੱਟ_designator (loc, ਝੂਠ, braced_init_obstack))
	      ਵਾਪਸ;
	  }
      }
    ਜਦੋਂ (ਖੇਤਰ_2 != NULL_ਰੁੱਖ);
}

/* Helper function for add_pending_init.  Find inorder successor of P
   in AVL tree.  */
ਸਥਿਰ ਬਣਤਰ init_ਗੰਢ *
init_ਗੰਢ_successor (ਬਣਤਰ init_ਗੰਢ *p)
{
  ਬਣਤਰ init_ਗੰਢ *r;
  ਜੇ (p->ਸੱਜੇ)
    {
      r = p->ਸੱਜੇ;
      ਜਦੋਂ (r->ਖੱਬੇ)
	r = r->ਖੱਬੇ;
      ਵਾਪਸ r;
    }
  r = p->ਮਾਪਾ;
  ਜਦੋਂ (r && p == r->ਸੱਜੇ)
    {
      p = r;
      r = r->ਮਾਪਾ;
    }
  ਵਾਪਸ r;
}

/* Add a new initializer to the tree of pending initializers.  PURPOSE
   identifies the initializer, either array index or field in a structure.
   VALUE is the value of that index or field.  If ORIGTYPE is not
   NULL_TREE, it is the original type of VALUE.

   IMPLICIT is true if value comes from pop_init_level (1),
   the new initializer has been merged with the existing one
   and thus no warnings should be emitted about overriding an
   existing initializer.  */

ਸਥਿਰ ਖਾਲੀ
ਜੋੜੋ_pending_init (location_t loc, ਰੁੱਖ purpose, ਰੁੱਖ ਮੁੱਲ, ਰੁੱਖ origtype,
		  ਤਾਰਕਿਕ implicit, ਬਣਤਰ obstack *braced_init_obstack)
{
  ਬਣਤਰ init_ਗੰਢ *p, **q, *r;

  q = &constructor_pending_elts;
  p = 0;

  ਜੇ (ਰੁੱਖ_ਕੋਡ (constructor_type) == ARRAY_TYPE)
    {
      ਜਦੋਂ (*q != 0)
	{
	  p = *q;
	  ਜੇ (ਰੁੱਖ_int_cst_lt (purpose, p->purpose))
	    q = &p->ਖੱਬੇ;
	  ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_int_cst_lt (p->purpose, purpose))
	    {
	      ਜੇ (ਰੁੱਖ_ਕੋਡ (p->ਮੁੱਲ) != RAW_ਅੰਕੜੇ_CST
		  || (p->ਸੱਜੇ
		      && ਰੁੱਖ_int_cst_le (p->ਸੱਜੇ->purpose, purpose)))
		q = &p->ਸੱਜੇ;
	      ਨਹੀਂਤਾਂ
		{
		  widest_int pp = wi::ਮੰਜ਼ਿਲ_widest (p->purpose);
		  widest_int pw = wi::ਮੰਜ਼ਿਲ_widest (purpose);
		  ਜੇ (pp + RAW_ਅੰਕੜੇ_ਲੰਮਾਈ (p->ਮੁੱਲ) <= pw)
		    q = &p->ਸੱਜੇ;
		  ਨਹੀਂਤਾਂ
		    {
		      /* Override which should split the old RAW_DATA_CST
			 into 2 or 3 pieces.  */
		      ਜੇ (!implicit && warn_override_init)
			warning_init (loc, OPT_Woverride_init,
				      "initialized field overwritten");
		      ਬਿਨਾਨਿਸ਼ਾਨੀ HOST_WIDE_INT ਸ਼ੁਰੂ = (pw - pp).ਮੰਜ਼ਿਲ_uhwi ();
		      ਬਿਨਾਨਿਸ਼ਾਨੀ HOST_WIDE_INT len = 1;
		      ਜੇ (ਰੁੱਖ_ਕੋਡ (ਮੁੱਲ) == RAW_ਅੰਕੜੇ_CST)
			len = RAW_ਅੰਕੜੇ_ਲੰਮਾਈ (ਮੁੱਲ);
		      ਬਿਨਾਨਿਸ਼ਾਨੀ HOST_WIDE_INT ਸਿਰਾ = 0;
		      ਬਿਨਾਨਿਸ਼ਾਨੀ plen = RAW_ਅੰਕੜੇ_ਲੰਮਾਈ (p->ਮੁੱਲ);
		      gcc_checking_assert (ਸ਼ੁਰੂ < plen && ਸ਼ੁਰੂ);
		      ਜੇ (plen - ਸ਼ੁਰੂ > len)
			ਸਿਰਾ = plen - ਸ਼ੁਰੂ - len;
		      ਰੁੱਖ v = p->ਮੁੱਲ;
		      ਰੁੱਖ origtype = p->origtype;
		      ਜੇ (ਸ਼ੁਰੂ == 1)
			p->ਮੁੱਲ = build_int_cst (ਰੁੱਖ_TYPE (v),
						  RAW_ਅੰਕੜੇ_UCHAR_ELT (v, 0));
		      ਨਹੀਂਤਾਂ
			{
			  p->ਮੁੱਲ = v;
			  ਜੇ (ਸਿਰਾ > 1)
			    v = copy_ਗੰਢ (v);
			  RAW_ਅੰਕੜੇ_ਲੰਮਾਈ (p->ਮੁੱਲ) = ਸ਼ੁਰੂ;
			}
		      ਜੇ (ਸਿਰਾ)
			{
			  ਰੁੱਖ epurpose
			    = ਮਾਪ_binop (PLUS_ਵਿਅੰਜਕ, purpose,
					  bitsize_int (len));
			  ਜੇ (ਸਿਰਾ > 1)
			    {
			      RAW_ਅੰਕੜੇ_ਲੰਮਾਈ (v) -= plen - ਸਿਰਾ;
			      RAW_ਅੰਕੜੇ_ਸੂਚਕ (v) += plen - ਸਿਰਾ;
			    }
			  ਨਹੀਂਤਾਂ
			    v = build_int_cst (ਰੁੱਖ_TYPE (v),
					       RAW_ਅੰਕੜੇ_UCHAR_ELT (v, plen
								      - ਸਿਰਾ));
			  ਜੋੜੋ_pending_init (loc, epurpose, v, origtype,
					    implicit, braced_init_obstack);
			}
		      q = &constructor_pending_elts;
		      ਜਾਰੀ;
		    }
		}
	    }
	  ਨਹੀਂਤਾਂ
	    {
	      ਜੇ (ਰੁੱਖ_ਕੋਡ (p->ਮੁੱਲ) == RAW_ਅੰਕੜੇ_CST
		  && (RAW_ਅੰਕੜੇ_ਲੰਮਾਈ (p->ਮੁੱਲ)
		      > (ਰੁੱਖ_ਕੋਡ (ਮੁੱਲ) == RAW_ਅੰਕੜੇ_CST
			 ? RAW_ਅੰਕੜੇ_ਲੰਮਾਈ (ਮੁੱਲ) : 1)))
		{
		  /* Override which should split the old RAW_DATA_CST
		     into 2 pieces.  */
		  ਜੇ (!implicit && warn_override_init)
		    warning_init (loc, OPT_Woverride_init,
				  "initialized field overwritten");
		  ਬਿਨਾਨਿਸ਼ਾਨੀ HOST_WIDE_INT len = 1;
		  ਜੇ (ਰੁੱਖ_ਕੋਡ (ਮੁੱਲ) == RAW_ਅੰਕੜੇ_CST)
		    len = RAW_ਅੰਕੜੇ_ਲੰਮਾਈ (ਮੁੱਲ);
		  ਜੇ ((ਬਿਨਾਨਿਸ਼ਾਨੀ) RAW_ਅੰਕੜੇ_ਲੰਮਾਈ (p->ਮੁੱਲ) > len + 1)
		    {
		      RAW_ਅੰਕੜੇ_ਲੰਮਾਈ (p->ਮੁੱਲ) -= len;
		      RAW_ਅੰਕੜੇ_ਸੂਚਕ (p->ਮੁੱਲ) += len;
		    }
		  ਨਹੀਂਤਾਂ
		    {
		      ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ l = RAW_ਅੰਕੜੇ_ਲੰਮਾਈ (p->ਮੁੱਲ) - 1;
		      p->ਮੁੱਲ
			= build_int_cst (ਰੁੱਖ_TYPE (p->ਮੁੱਲ),
					 RAW_ਅੰਕੜੇ_UCHAR_ELT (p->ਮੁੱਲ, l));
		    }
		  p->purpose = ਮਾਪ_binop (PLUS_ਵਿਅੰਜਕ, p->purpose,
					   bitsize_int (len));
		  ਜਾਰੀ;
		}
	      ਜੇ (ਰੁੱਖ_ਕੋਡ (ਮੁੱਲ) == RAW_ਅੰਕੜੇ_CST)
		{
		handle_raw_ਅੰਕੜੇ:
		  /* RAW_DATA_CST value might overlap various further
		     prior initval entries.  Find out how many.  */
		  ਬਿਨਾਨਿਸ਼ਾਨੀ cnt = 0;
		  widest_int w
		    = wi::ਮੰਜ਼ਿਲ_widest (purpose) + RAW_ਅੰਕੜੇ_ਲੰਮਾਈ (ਮੁੱਲ);
		  ਬਣਤਰ init_ਗੰਢ *r = p, *ਆਖਰੀ = ਨਿਰਾ;
		  ਤਾਰਕਿਕ override_init = warn_override_init;
		  ਜਦੋਂ ((r = init_ਗੰਢ_successor (r))
			 && wi::ਮੰਜ਼ਿਲ_widest (r->purpose) < w)
		    {
		      ++cnt;
		      ਜੇ (ਰੁੱਖ_SIDE_EFFECTS (r->ਮੁੱਲ))
			warning_init (loc, OPT_Woverride_init_side_effects,
				      "initialized field with side-effects "
				      "overwritten");
		      ਨਹੀਂਤਾਂ ਜੇ (override_init)
			{
			  warning_init (loc, OPT_Woverride_init,
					"initialized field overwritten");
			  override_init = ਝੂਠ;
			}
		      ਆਖਰੀ = r;
		    }
		  ਜੇ (cnt)
		    {
		      ਜੇ (ਰੁੱਖ_ਕੋਡ (ਆਖਰੀ->ਮੁੱਲ) == RAW_ਅੰਕੜੇ_CST
			  && (wi::ਮੰਜ਼ਿਲ_widest (ਆਖਰੀ->purpose)
			      + RAW_ਅੰਕੜੇ_ਲੰਮਾਈ (ਆਖਰੀ->ਮੁੱਲ) > w))
			{
			  /* The last overlapping prior initval overlaps
			     only partially.  Shrink it and decrease cnt.  */
			  ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ l = (wi::ਮੰਜ਼ਿਲ_widest (ਆਖਰੀ->purpose)
					    + RAW_ਅੰਕੜੇ_ਲੰਮਾਈ (ਆਖਰੀ->ਮੁੱਲ)
					    - w).ਮੰਜ਼ਿਲ_uhwi ();
			  --cnt;
			  RAW_ਅੰਕੜੇ_ਲੰਮਾਈ (ਆਖਰੀ->ਮੁੱਲ) -= l;
			  RAW_ਅੰਕੜੇ_ਸੂਚਕ (ਆਖਰੀ->ਮੁੱਲ) += l;
			  ਜੇ (RAW_ਅੰਕੜੇ_ਲੰਮਾਈ (ਆਖਰੀ->ਮੁੱਲ) == 1)
			    ਆਖਰੀ->ਮੁੱਲ
			      = build_int_cst (ਰੁੱਖ_TYPE (ਆਖਰੀ->ਮੁੱਲ),
					       RAW_ਅੰਕੜੇ_UCHAR_ELT (ਆਖਰੀ->ਮੁੱਲ,
								   0));
			  ਆਖਰੀ->purpose
			    = ਮਾਪ_binop (PLUS_ਵਿਅੰਜਕ, ਆਖਰੀ->purpose,
					  bitsize_int (l));
			}
		      /* Instead of deleting cnt nodes from the AVL tree
			 and rebalancing, peel of last cnt bytes from the
			 RAW_DATA_CST.  Overriding thousands of previously
			 initialized array elements with #embed needs to work,
			 but doesn't need to be super efficient.  */
		      gcc_checking_assert ((ਬਿਨਾਨਿਸ਼ਾਨੀ) RAW_ਅੰਕੜੇ_ਲੰਮਾਈ (ਮੁੱਲ)
					   > cnt);
		      RAW_ਅੰਕੜੇ_ਲੰਮਾਈ (ਮੁੱਲ) -= cnt;
		      ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *s
			= &RAW_ਅੰਕੜੇ_UCHAR_ELT (ਮੁੱਲ, RAW_ਅੰਕੜੇ_ਲੰਮਾਈ (ਮੁੱਲ));
		      ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ o = RAW_ਅੰਕੜੇ_ਲੰਮਾਈ (ਮੁੱਲ);
		      ਲਈ (r = p; cnt--; ++o, ++s)
			{
			  r = init_ਗੰਢ_successor (r);
			  r->purpose = ਮਾਪ_binop (PLUS_ਵਿਅੰਜਕ, purpose,
						   bitsize_int (o));
			  r->ਮੁੱਲ = build_int_cst (ਰੁੱਖ_TYPE (ਮੁੱਲ), *s);
			  r->origtype = origtype;
			}
		      ਜੇ (RAW_ਅੰਕੜੇ_ਲੰਮਾਈ (ਮੁੱਲ) == 1)
			ਮੁੱਲ = build_int_cst (ਰੁੱਖ_TYPE (ਮੁੱਲ),
					       RAW_ਅੰਕੜੇ_UCHAR_ELT (ਮੁੱਲ, 0));
		    }
		}
	      ਜੇ (!implicit)
		{
		  ਜੇ (ਰੁੱਖ_SIDE_EFFECTS (p->ਮੁੱਲ))
		    warning_init (loc, OPT_Woverride_init_side_effects,
				  "initialized field with side-effects "
				  "overwritten");
		  ਨਹੀਂਤਾਂ ਜੇ (warn_override_init)
		    warning_init (loc, OPT_Woverride_init,
				  "initialized field overwritten");
		}
	      p->ਮੁੱਲ = ਮੁੱਲ;
	      p->origtype = origtype;
	      ਵਾਪਸ;
	    }
	}
      ਜੇ (ਰੁੱਖ_ਕੋਡ (ਮੁੱਲ) == RAW_ਅੰਕੜੇ_CST && p)
	{
	  ਬਣਤਰ init_ਗੰਢ *r;
	  ਜੇ (q == &p->ਖੱਬੇ)
	    r = p;
	  ਨਹੀਂਤਾਂ
	    r = init_ਗੰਢ_successor (p);
	  ਜੇ (r && wi::ਮੰਜ਼ਿਲ_widest (r->purpose) < (wi::ਮੰਜ਼ਿਲ_widest (purpose)
						 + RAW_ਅੰਕੜੇ_ਲੰਮਾਈ (ਮੁੱਲ)))
	    {
	      /* Overlap with at least one prior initval in the range but
		 not at the start.  */
	      p = r;
	      p->purpose = purpose;
	      ਜਾਓ handle_raw_ਅੰਕੜੇ;
	    }
	}
    }
  ਨਹੀਂਤਾਂ
    {
      ਰੁੱਖ bitpos;

      bitpos = ਦੋਆਧਾਰੀ_ਅੰਕ_position (purpose);
      ਜਦੋਂ (*q != ਨਿਰਾ)
	{
	  p = *q;
	  ਜੇ (ਰੁੱਖ_int_cst_lt (bitpos, ਦੋਆਧਾਰੀ_ਅੰਕ_position (p->purpose)))
	    q = &p->ਖੱਬੇ;
	  ਨਹੀਂਤਾਂ ਜੇ (p->purpose != purpose)
	    q = &p->ਸੱਜੇ;
	  ਨਹੀਂਤਾਂ
	    {
	      ਜੇ (!implicit)
		{
		  ਜੇ (ਰੁੱਖ_SIDE_EFFECTS (p->ਮੁੱਲ))
		    warning_init (loc, OPT_Woverride_init_side_effects,
				  "initialized field with side-effects "
				  "overwritten");
		  ਨਹੀਂਤਾਂ ਜੇ (warn_override_init)
		    warning_init (loc, OPT_Woverride_init,
				  "initialized field overwritten");
		}
	      p->ਮੁੱਲ = ਮੁੱਲ;
	      p->origtype = origtype;
	      ਵਾਪਸ;
	    }
	}
    }

  r = (ਬਣਤਰ init_ਗੰਢ *) obstack_alloc (braced_init_obstack,
					  ਆਕਾਰ (ਬਣਤਰ init_ਗੰਢ));
  r->purpose = purpose;
  r->ਮੁੱਲ = ਮੁੱਲ;
  r->origtype = origtype;

  *q = r;
  r->ਮਾਪਾ = p;
  r->ਖੱਬੇ = 0;
  r->ਸੱਜੇ = 0;
  r->balance = 0;

  ਜਦੋਂ (p)
    {
      ਬਣਤਰ init_ਗੰਢ *s;

      ਜੇ (r == p->ਖੱਬੇ)
	{
	  ਜੇ (p->balance == 0)
	    p->balance = -1;
	  ਨਹੀਂਤਾਂ ਜੇ (p->balance < 0)
	    {
	      ਜੇ (r->balance < 0)
		{
		  /* L rotation.  */
		  p->ਖੱਬੇ = r->ਸੱਜੇ;
		  ਜੇ (p->ਖੱਬੇ)
		    p->ਖੱਬੇ->ਮਾਪਾ = p;
		  r->ਸੱਜੇ = p;

		  p->balance = 0;
		  r->balance = 0;

		  s = p->ਮਾਪਾ;
		  p->ਮਾਪਾ = r;
		  r->ਮਾਪਾ = s;
		  ਜੇ (s)
		    {
		      ਜੇ (s->ਖੱਬੇ == p)
			s->ਖੱਬੇ = r;
		      ਨਹੀਂਤਾਂ
			s->ਸੱਜੇ = r;
		    }
		  ਨਹੀਂਤਾਂ
		    constructor_pending_elts = r;
		}
	      ਨਹੀਂਤਾਂ
		{
		  /* LR rotation.  */
		  ਬਣਤਰ init_ਗੰਢ *t = r->ਸੱਜੇ;

		  r->ਸੱਜੇ = t->ਖੱਬੇ;
		  ਜੇ (r->ਸੱਜੇ)
		    r->ਸੱਜੇ->ਮਾਪਾ = r;
		  t->ਖੱਬੇ = r;

		  p->ਖੱਬੇ = t->ਸੱਜੇ;
		  ਜੇ (p->ਖੱਬੇ)
		    p->ਖੱਬੇ->ਮਾਪਾ = p;
		  t->ਸੱਜੇ = p;

		  p->balance = t->balance < 0;
		  r->balance = -(t->balance > 0);
		  t->balance = 0;

		  s = p->ਮਾਪਾ;
		  p->ਮਾਪਾ = t;
		  r->ਮਾਪਾ = t;
		  t->ਮਾਪਾ = s;
		  ਜੇ (s)
		    {
		      ਜੇ (s->ਖੱਬੇ == p)
			s->ਖੱਬੇ = t;
		      ਨਹੀਂਤਾਂ
			s->ਸੱਜੇ = t;
		    }
		  ਨਹੀਂਤਾਂ
		    constructor_pending_elts = t;
		}
	      ਰੋਕੋ;
	    }
	  ਨਹੀਂਤਾਂ
	    {
	      /* p->balance == +1; growth of left side balances the node.  */
	      p->balance = 0;
	      ਰੋਕੋ;
	    }
	}
      ਨਹੀਂਤਾਂ /* r == p->right */
	{
	  ਜੇ (p->balance == 0)
	    /* Growth propagation from right side.  */
	    p->balance++;
	  ਨਹੀਂਤਾਂ ਜੇ (p->balance > 0)
	    {
	      ਜੇ (r->balance > 0)
		{
		  /* R rotation.  */
		  p->ਸੱਜੇ = r->ਖੱਬੇ;
		  ਜੇ (p->ਸੱਜੇ)
		    p->ਸੱਜੇ->ਮਾਪਾ = p;
		  r->ਖੱਬੇ = p;

		  p->balance = 0;
		  r->balance = 0;

		  s = p->ਮਾਪਾ;
		  p->ਮਾਪਾ = r;
		  r->ਮਾਪਾ = s;
		  ਜੇ (s)
		    {
		      ਜੇ (s->ਖੱਬੇ == p)
			s->ਖੱਬੇ = r;
		      ਨਹੀਂਤਾਂ
			s->ਸੱਜੇ = r;
		    }
		  ਨਹੀਂਤਾਂ
		    constructor_pending_elts = r;
		}
	      ਨਹੀਂਤਾਂ /* r->balance == -1 */
		{
		  /* RL rotation */
		  ਬਣਤਰ init_ਗੰਢ *t = r->ਖੱਬੇ;

		  r->ਖੱਬੇ = t->ਸੱਜੇ;
		  ਜੇ (r->ਖੱਬੇ)
		    r->ਖੱਬੇ->ਮਾਪਾ = r;
		  t->ਸੱਜੇ = r;

		  p->ਸੱਜੇ = t->ਖੱਬੇ;
		  ਜੇ (p->ਸੱਜੇ)
		    p->ਸੱਜੇ->ਮਾਪਾ = p;
		  t->ਖੱਬੇ = p;

		  r->balance = (t->balance < 0);
		  p->balance = -(t->balance > 0);
		  t->balance = 0;

		  s = p->ਮਾਪਾ;
		  p->ਮਾਪਾ = t;
		  r->ਮਾਪਾ = t;
		  t->ਮਾਪਾ = s;
		  ਜੇ (s)
		    {
		      ਜੇ (s->ਖੱਬੇ == p)
			s->ਖੱਬੇ = t;
		      ਨਹੀਂਤਾਂ
			s->ਸੱਜੇ = t;
		    }
		  ਨਹੀਂਤਾਂ
		    constructor_pending_elts = t;
		}
	      ਰੋਕੋ;
	    }
	  ਨਹੀਂਤਾਂ
	    {
	      /* p->balance == -1; growth of right side balances the node.  */
	      p->balance = 0;
	      ਰੋਕੋ;
	    }
	}

      r = p;
      p = p->ਮਾਪਾ;
    }
}

/* Build AVL tree from a sorted chain.  */

ਸਥਿਰ ਖਾਲੀ
ਸੈੱਟ_nonincremental_init (ਬਣਤਰ obstack * braced_init_obstack)
{
  ਬਿਨਾਨਿਸ਼ਾਨੀ HOST_WIDE_INT ix;
  ਰੁੱਖ ਸੂਚਕਾਂਕ, ਮੁੱਲ;

  ਜੇ (ਰੁੱਖ_ਕੋਡ (constructor_type) != ਰਿਕਾਰਡ_TYPE
      && ਰੁੱਖ_ਕੋਡ (constructor_type) != ARRAY_TYPE)
    ਵਾਪਸ;

  FOR_EACH_CONSTRUCTOR_ELT (constructor_elements, ix, ਸੂਚਕਾਂਕ, ਮੁੱਲ)
    ਜੋੜੋ_pending_init (ਨਿਵੇਸ਼_location, ਸੂਚਕਾਂਕ, ਮੁੱਲ, NULL_ਰੁੱਖ, ਸੱਚ,
		      braced_init_obstack);
  constructor_elements = ਨਿਰਾ;
  ਜੇ (ਰੁੱਖ_ਕੋਡ (constructor_type) == ਰਿਕਾਰਡ_TYPE)
    {
      constructor_unfilled_fields = TYPE_FIELDS (constructor_type);
      /* Skip any nameless bit fields at the beginning.  */
      ਜਦੋਂ (constructor_unfilled_fields != NULL_ਰੁੱਖ
	     && DECL_UNNAMED_ਦੋਆਧਾਰੀ_ਅੰਕ_ਖੇਤਰ (constructor_unfilled_fields))
	constructor_unfilled_fields = ਰੁੱਖ_CHAIN (constructor_unfilled_fields);

    }
  ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਕੋਡ (constructor_type) == ARRAY_TYPE)
    {
      ਜੇ (TYPE_DOMAIN (constructor_type))
	constructor_unfilled_ਸੂਚਕਾਂਕ
	  = convert (bitsizetype,
		     TYPE_MIN_ਮੁੱਲ (TYPE_DOMAIN (constructor_type)));
      ਨਹੀਂਤਾਂ
	constructor_unfilled_ਸੂਚਕਾਂਕ = bitsize_zero_ਗੰਢ;
    }
  constructor_incremental = 0;
}

/* Build AVL tree from a string constant.  */

ਸਥਿਰ ਖਾਲੀ
ਸੈੱਟ_nonincremental_init_from_string (ਰੁੱਖ str,
				     ਬਣਤਰ obstack * braced_init_obstack)
{
  ਰੁੱਖ ਮੁੱਲ, purpose, type;
  HOST_WIDE_INT val[2];
  ਅਚਲ ਅੱਖਰ *p, *ਸਿਰਾ;
  ਪੂਰਨ byte, wchar_ਬਾਈਟਾਂ, charwidth, bitpos;

  gcc_assert (ਰੁੱਖ_ਕੋਡ (constructor_type) == ARRAY_TYPE);

  wchar_ਬਾਈਟਾਂ = TYPE_PRECISION (ਰੁੱਖ_TYPE (ਰੁੱਖ_TYPE (str))) / ਬਿੱਟ_ਪ੍ਰਤੀ_UNIT;
  charwidth = TYPE_PRECISION (char_type_ਗੰਢ);
  gcc_assert ((ਮਾਪ_t) wchar_ਬਾਈਟਾਂ * charwidth
	      <= ARRAY_ਮਾਪ (val) * HOST_ਬਿੱਟ_ਪ੍ਰਤੀ_WIDE_INT);
  type = ਰੁੱਖ_TYPE (constructor_type);
  p = ਰੁੱਖ_STRING_ਸੂਚਕ (str);
  ਸਿਰਾ = p + ਰੁੱਖ_STRING_ਲੰਮਾਈ (str);

  ਲਈ (purpose = bitsize_zero_ਗੰਢ;
       p < ਸਿਰਾ
       && !(constructor_max_ਸੂਚਕਾਂਕ
	    && ਰੁੱਖ_int_cst_lt (constructor_max_ਸੂਚਕਾਂਕ, purpose));
       purpose = ਮਾਪ_binop (PLUS_ਵਿਅੰਜਕ, purpose, bitsize_one_ਗੰਢ))
    {
      ਜੇ (wchar_ਬਾਈਟਾਂ == 1)
	{
	  val[0] = (ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ) *p++;
	  val[1] = 0;
	}
      ਨਹੀਂਤਾਂ
	{
	  val[1] = 0;
	  val[0] = 0;
	  ਲਈ (byte = 0; byte < wchar_ਬਾਈਟਾਂ; byte++)
	    {
	      ਜੇ (ਬਾਈਟਾਂ_BIG_ENDIAN)
		bitpos = (wchar_ਬਾਈਟਾਂ - byte - 1) * charwidth;
	      ਨਹੀਂਤਾਂ
		bitpos = byte * charwidth;
	      val[bitpos / HOST_ਬਿੱਟ_ਪ੍ਰਤੀ_WIDE_INT]
		|= ((ਬਿਨਾਨਿਸ਼ਾਨੀ HOST_WIDE_INT) ((ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ) *p++))
		   << (bitpos % HOST_ਬਿੱਟ_ਪ੍ਰਤੀ_WIDE_INT);
	    }
	}

      ਜੇ (!TYPE_UNSIGNED (type))
	{
	  bitpos = ((wchar_ਬਾਈਟਾਂ - 1) * charwidth) + HOST_ਬਿੱਟ_ਪ੍ਰਤੀ_CHAR;
	  ਜੇ (bitpos < HOST_ਬਿੱਟ_ਪ੍ਰਤੀ_WIDE_INT)
	    {
	      ਜੇ (val[0] & (HOST_WIDE_INT_1 << (bitpos - 1)))
		{
		  val[0] |= HOST_WIDE_INT_M1U << bitpos;
		  val[1] = -1;
		}
	    }
	  ਨਹੀਂਤਾਂ ਜੇ (bitpos == HOST_ਬਿੱਟ_ਪ੍ਰਤੀ_WIDE_INT)
	    {
	      ਜੇ (val[0] < 0)
		val[1] = -1;
	    }
	  ਨਹੀਂਤਾਂ ਜੇ (val[1] & (HOST_WIDE_INT_1
			     << (bitpos - 1 - HOST_ਬਿੱਟ_ਪ੍ਰਤੀ_WIDE_INT)))
	    val[1] |= HOST_WIDE_INT_M1U << (bitpos - HOST_ਬਿੱਟ_ਪ੍ਰਤੀ_WIDE_INT);
	}

      ਮੁੱਲ = wide_int_ਮੰਜ਼ਿਲ_ਰੁੱਖ (type,
				wide_int::from_array (val, 2,
						      HOST_ਬਿੱਟ_ਪ੍ਰਤੀ_WIDE_INT * 2));
      ਜੋੜੋ_pending_init (ਨਿਵੇਸ਼_location, purpose, ਮੁੱਲ, NULL_ਰੁੱਖ, ਸੱਚ,
                        braced_init_obstack);
    }

  constructor_incremental = 0;
}

/* Return value of FIELD in pending initializer or NULL_TREE if the field was
   not initialized yet.  */

ਸਥਿਰ ਰੁੱਖ
ਲੱਭੋ_init_member (ਰੁੱਖ ਖੇਤਰ_2, ਬਣਤਰ obstack * braced_init_obstack)
{
  ਬਣਤਰ init_ਗੰਢ *p;

  ਜੇ (ਰੁੱਖ_ਕੋਡ (constructor_type) == ARRAY_TYPE)
    {
      ਜੇ (constructor_incremental
	  && ਰੁੱਖ_int_cst_lt (ਖੇਤਰ_2, constructor_unfilled_ਸੂਚਕਾਂਕ))
	ਸੈੱਟ_nonincremental_init (braced_init_obstack);

      p = constructor_pending_elts;
      ਜਦੋਂ (p)
	{
	  ਜੇ (ਰੁੱਖ_int_cst_lt (ਖੇਤਰ_2, p->purpose))
	    p = p->ਖੱਬੇ;
	  ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_int_cst_lt (p->purpose, ਖੇਤਰ_2))
	    p = p->ਸੱਜੇ;
	  ਨਹੀਂਤਾਂ
	    ਵਾਪਸ p->ਮੁੱਲ;
	}
    }
  ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਕੋਡ (constructor_type) == ਰਿਕਾਰਡ_TYPE)
    {
      ਰੁੱਖ bitpos = ਦੋਆਧਾਰੀ_ਅੰਕ_position (ਖੇਤਰ_2);

      ਜੇ (constructor_incremental
	  && (!constructor_unfilled_fields
	      || ਰੁੱਖ_int_cst_lt (bitpos,
				  ਦੋਆਧਾਰੀ_ਅੰਕ_position (constructor_unfilled_fields))))
	ਸੈੱਟ_nonincremental_init (braced_init_obstack);

      p = constructor_pending_elts;
      ਜਦੋਂ (p)
	{
	  ਜੇ (ਖੇਤਰ_2 == p->purpose)
	    ਵਾਪਸ p->ਮੁੱਲ;
	  ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_int_cst_lt (bitpos, ਦੋਆਧਾਰੀ_ਅੰਕ_position (p->purpose)))
	    p = p->ਖੱਬੇ;
	  ਨਹੀਂਤਾਂ
	    p = p->ਸੱਜੇ;
	}
    }
  ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਕੋਡ (constructor_type) == UNION_TYPE)
    {
      ਜੇ (!vec_ਸੁਰੱਖਿਅਤ_is_ਖਾਲੀ_ਥਾਵਾਂ (constructor_elements)
	  && (constructor_elements->ਆਖਰੀ ().ਸੂਚਕਾਂਕ == ਖੇਤਰ_2))
	ਵਾਪਸ constructor_elements->ਆਖਰੀ ().ਮੁੱਲ;
    }
  ਵਾਪਸ NULL_ਰੁੱਖ;
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

ਸਥਿਰ ਖਾਲੀ
output_init_element (location_t loc, ਰੁੱਖ ਮੁੱਲ, ਰੁੱਖ origtype,
		     ਤਾਰਕਿਕ strict_string, ਰੁੱਖ type, ਰੁੱਖ ਖੇਤਰ_2, ਤਾਰਕਿਕ pending,
		     ਤਾਰਕਿਕ implicit, ਬਣਤਰ obstack * braced_init_obstack)
{
  ਰੁੱਖ semantic_type = NULL_ਰੁੱਖ;
  ਤਾਰਕਿਕ maybe_const = ਸੱਚ;
  ਤਾਰਕਿਕ npc, int_const_ਵਿਅੰਜਕ, arith_const_ਵਿਅੰਜਕ;

  ਜੇ (type == error_mark_ਗੰਢ || ਮੁੱਲ == error_mark_ਗੰਢ)
    {
      constructor_erroneous = 1;
      ਵਾਪਸ;
    }
  ਜੇ (ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (ਮੁੱਲ)) == ARRAY_TYPE
      && (ਰੁੱਖ_ਕੋਡ (ਮੁੱਲ) == STRING_CST
	  || ਰੁੱਖ_ਕੋਡ (ਮੁੱਲ) == COMPOUND_LITERAL_ਵਿਅੰਜਕ)
      && !(ਰੁੱਖ_ਕੋਡ (ਮੁੱਲ) == STRING_CST
	   && ਰੁੱਖ_ਕੋਡ (type) == ARRAY_TYPE
	   && INTEGRAL_TYPE_P (ਰੁੱਖ_TYPE (type)))
      && !comptypes (TYPE_MAIN_VARIANT (ਰੁੱਖ_TYPE (ਮੁੱਲ)),
		     TYPE_MAIN_VARIANT (type)))
    ਮੁੱਲ = array_ਮੰਜ਼ਿਲ_ਸੂਚਕ_conversion (ਨਿਵੇਸ਼_location, ਮੁੱਲ);

  ਜੇ (ਰੁੱਖ_ਕੋਡ (ਮੁੱਲ) == COMPOUND_LITERAL_ਵਿਅੰਜਕ
      && require_constant_ਮੁੱਲ && pending)
    {
      /* As an extension, allow initializing objects with static storage
	 duration with compound literals (which are then treated just as
	 the brace enclosed list they contain).  */
      ਜੇ (flag_isoc99)
	pedwarn_init (loc, OPT_Wpedantic, "initializer element is not "
		      "constant");
      ਰੁੱਖ decl = COMPOUND_LITERAL_ਵਿਅੰਜਕ_DECL (ਮੁੱਲ);
      ਮੁੱਲ = DECL_INITIAL (decl);
    }

  npc = null_ਸੂਚਕ_constant_p (ਮੁੱਲ);
  int_const_ਵਿਅੰਜਕ = (ਰੁੱਖ_ਕੋਡ (ਮੁੱਲ) == INTEGER_CST
		    && !ਰੁੱਖ_ਉਛਾਲ (ਮੁੱਲ)
		    && INTEGRAL_TYPE_P (ਰੁੱਖ_TYPE (ਮੁੱਲ)));
  /* Not fully determined before folding.  */
  arith_const_ਵਿਅੰਜਕ = ਸੱਚ;
  ਜੇ (ਰੁੱਖ_ਕੋਡ (ਮੁੱਲ) == EXCESS_PRECISION_ਵਿਅੰਜਕ)
    {
      semantic_type = ਰੁੱਖ_TYPE (ਮੁੱਲ);
      ਮੁੱਲ = ਰੁੱਖ_ਸੰਕਾਰਜ (ਮੁੱਲ, 0);
    }
  ਮੁੱਲ = c_fully_fold (ਮੁੱਲ, require_constant_ਮੁੱਲ, &maybe_const);
  /* TODO: this may not detect all cases of expressions folding to
     constants that are not arithmetic constant expressions.  */
  ਜੇ (!maybe_const)
    arith_const_ਵਿਅੰਜਕ = ਝੂਠ;
  ਨਹੀਂਤਾਂ ਜੇ (!INTEGRAL_TYPE_P (ਰੁੱਖ_TYPE (ਮੁੱਲ))
	   && ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (ਮੁੱਲ)) != REAL_TYPE
	   && ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (ਮੁੱਲ)) != COMPLEX_TYPE)
    arith_const_ਵਿਅੰਜਕ = ਝੂਠ;
  ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਕੋਡ (ਮੁੱਲ) != INTEGER_CST
	   && ਰੁੱਖ_ਕੋਡ (ਮੁੱਲ) != REAL_CST
	   && ਰੁੱਖ_ਕੋਡ (ਮੁੱਲ) != COMPLEX_CST
	   && ਰੁੱਖ_ਕੋਡ (ਮੁੱਲ) != RAW_ਅੰਕੜੇ_CST)
    arith_const_ਵਿਅੰਜਕ = ਝੂਠ;
  ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਉਛਾਲ (ਮੁੱਲ))
    arith_const_ਵਿਅੰਜਕ = ਝੂਠ;

  ਜੇ (ਮੁੱਲ == error_mark_ਗੰਢ)
    constructor_erroneous = 1;
  ਨਹੀਂਤਾਂ ਜੇ (!ਰੁੱਖ_CONSTANT (ਮੁੱਲ))
    constructor_constant = 0;
  ਨਹੀਂਤਾਂ ਜੇ (!initializer_constant_valid_p (ਮੁੱਲ,
					  ਰੁੱਖ_TYPE (ਮੁੱਲ),
					  AGGREGATE_TYPE_P (constructor_type)
					  && TYPE_ਉਲਟ_STORAGE_ਕ੍ਰਮ
					     (constructor_type))
	   || (ਰਿਕਾਰਡ_OR_UNION_TYPE_P (constructor_type)
	       && DECL_C_ਦੋਆਧਾਰੀ_ਅੰਕ_ਖੇਤਰ (ਖੇਤਰ_2)
	       && ਰੁੱਖ_ਕੋਡ (ਮੁੱਲ) != INTEGER_CST))
    constructor_simple = 0;
  ਜੇ (!maybe_const)
    constructor_nonconst = 1;

  /* Digest the initializer and issue any errors about incompatible
     types before issuing errors about non-constant initializers.  */
  ਰੁੱਖ new_ਮੁੱਲ = ਮੁੱਲ;
  ਜੇ (semantic_type)
    new_ਮੁੱਲ = build1 (EXCESS_PRECISION_ਵਿਅੰਜਕ, semantic_type, ਮੁੱਲ);
  /* In the case of braces around a scalar initializer, the result of
     this initializer processing goes through digest_init again at the
     outer level.  In the case of a constexpr initializer for a
     pointer, avoid converting a null pointer constant to something
     that is not a null pointer constant to avoid a spurious error
     from that second processing.  */
  ਜੇ (!require_constexpr_ਮੁੱਲ
      || !npc
      || ਰੁੱਖ_ਕੋਡ (constructor_type) != ਸੂਚਕ_TYPE)
    new_ਮੁੱਲ = digest_init (loc,
			     ਰਿਕਾਰਡ_OR_UNION_TYPE_P (constructor_type)
			     ? ਖੇਤਰ_2 : constructor_fields
			     ? constructor_fields : constructor_decl,
			     type, new_ਮੁੱਲ, origtype, npc,
			     int_const_ਵਿਅੰਜਕ, arith_const_ਵਿਅੰਜਕ, strict_string,
			     require_constant_ਮੁੱਲ, require_constexpr_ਮੁੱਲ);
  ਜੇ (new_ਮੁੱਲ == error_mark_ਗੰਢ)
    {
      constructor_erroneous = 1;
      ਵਾਪਸ;
    }
  ਜੇ (require_constant_ਮੁੱਲ || require_constant_elements)
    constant_ਵਿਅੰਜਕ_warning (new_ਮੁੱਲ);

  /* Proceed to check the constness of the original initializer.  */
  ਜੇ (!initializer_constant_valid_p (ਮੁੱਲ, ਰੁੱਖ_TYPE (ਮੁੱਲ)))
    {
      ਜੇ (require_constant_ਮੁੱਲ)
	{
	  error_init (loc, "initializer element is not constant");
	  ਮੁੱਲ = error_mark_ਗੰਢ;
	}
      ਨਹੀਂਤਾਂ ਜੇ (require_constant_elements)
	pedwarn (loc, OPT_Wpedantic,
		 "initializer element is not computable at load time");
    }
  ਨਹੀਂਤਾਂ ਜੇ (!maybe_const
	   && (require_constant_ਮੁੱਲ || require_constant_elements))
    pedwarn_init (loc, OPT_Wpedantic,
		  "initializer element is not a constant expression");
  /* digest_init has already carried out the additional checks
     required for 'constexpr' initializers (using the information
     passed to it about whether the original initializer was certain
     kinds of constant expression), so that check does not need to be
     repeated here.  */

  /* Issue -Wc++-compat warnings about initializing a bitfield with
     enum type.  */
  ਜੇ (warn_cxx_compat
      && ਖੇਤਰ_2 != NULL_ਰੁੱਖ
      && ਰੁੱਖ_ਕੋਡ (ਖੇਤਰ_2) == ਖੇਤਰ_DECL
      && DECL_ਦੋਆਧਾਰੀ_ਅੰਕ_ਖੇਤਰ_TYPE (ਖੇਤਰ_2) != NULL_ਰੁੱਖ
      && (TYPE_MAIN_VARIANT (DECL_ਦੋਆਧਾਰੀ_ਅੰਕ_ਖੇਤਰ_TYPE (ਖੇਤਰ_2))
	  != TYPE_MAIN_VARIANT (type))
      && ਰੁੱਖ_ਕੋਡ (DECL_ਦੋਆਧਾਰੀ_ਅੰਕ_ਖੇਤਰ_TYPE (ਖੇਤਰ_2)) == ENUMERAL_TYPE)
    {
      ਰੁੱਖ checktype = origtype != NULL_ਰੁੱਖ ? origtype : ਰੁੱਖ_TYPE (ਮੁੱਲ);
      ਜੇ (checktype != error_mark_ਗੰਢ
	  && (TYPE_MAIN_VARIANT (checktype)
	      != TYPE_MAIN_VARIANT (DECL_ਦੋਆਧਾਰੀ_ਅੰਕ_ਖੇਤਰ_TYPE (ਖੇਤਰ_2))))
	warning_init (loc, OPT_Wc___compat,
		      "enum conversion in initialization is invalid in C++");
    }

  /* If this field is empty and does not have side effects (and is not at
     the end of structure), don't do anything other than checking the
     initializer.  */
  ਜੇ (ਖੇਤਰ_2
      && (ਰੁੱਖ_TYPE (ਖੇਤਰ_2) == error_mark_ਗੰਢ
	  || (COMPLETE_TYPE_P (ਰੁੱਖ_TYPE (ਖੇਤਰ_2))
	      && integer_zerop (TYPE_ਮਾਪ (ਰੁੱਖ_TYPE (ਖੇਤਰ_2)))
	      && !ਰੁੱਖ_SIDE_EFFECTS (new_ਮੁੱਲ)
	      && (ਰੁੱਖ_ਕੋਡ (constructor_type) == ARRAY_TYPE
		  || DECL_CHAIN (ਖੇਤਰ_2)))))
    ਵਾਪਸ;

  /* Finally, set VALUE to the initializer value digested above.  */
  ਮੁੱਲ = new_ਮੁੱਲ;

  /* If this element doesn't come next in sequence,
     put it on constructor_pending_elts.  */
  ਜੇ (ਰੁੱਖ_ਕੋਡ (constructor_type) == ARRAY_TYPE
      && (!constructor_incremental
	  || !ਰੁੱਖ_int_cst_equal (ਖੇਤਰ_2, constructor_unfilled_ਸੂਚਕਾਂਕ)
	  || (ਰੁੱਖ_ਕੋਡ (ਮੁੱਲ) == RAW_ਅੰਕੜੇ_CST
	      && constructor_pending_elts
	      && pending)))
    {
      ਜੇ (constructor_incremental
	  && (ਰੁੱਖ_int_cst_lt (ਖੇਤਰ_2, constructor_unfilled_ਸੂਚਕਾਂਕ)
	      || (ਰੁੱਖ_ਕੋਡ (ਮੁੱਲ) == RAW_ਅੰਕੜੇ_CST
		  && constructor_pending_elts
		  && pending)))
	ਸੈੱਟ_nonincremental_init (braced_init_obstack);

      ਜੋੜੋ_pending_init (loc, ਖੇਤਰ_2, ਮੁੱਲ, origtype, implicit,
			braced_init_obstack);
      ਵਾਪਸ;
    }
  ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਕੋਡ (constructor_type) == ਰਿਕਾਰਡ_TYPE
	   && (!constructor_incremental
	       || ਖੇਤਰ_2 != constructor_unfilled_fields))
    {
      /* We do this for records but not for unions.  In a union,
	 no matter which field is specified, it can be initialized
	 right away since it starts at the beginning of the union.  */
      ਜੇ (constructor_incremental)
	{
	  ਜੇ (!constructor_unfilled_fields)
	    ਸੈੱਟ_nonincremental_init (braced_init_obstack);
	  ਨਹੀਂਤਾਂ
	    {
	      ਰੁੱਖ bitpos, unfillpos;

	      bitpos = ਦੋਆਧਾਰੀ_ਅੰਕ_position (ਖੇਤਰ_2);
	      unfillpos = ਦੋਆਧਾਰੀ_ਅੰਕ_position (constructor_unfilled_fields);

	      ਜੇ (ਰੁੱਖ_int_cst_lt (bitpos, unfillpos))
		ਸੈੱਟ_nonincremental_init (braced_init_obstack);
	    }
	}

      ਜੋੜੋ_pending_init (loc, ਖੇਤਰ_2, ਮੁੱਲ, origtype, implicit,
			braced_init_obstack);
      ਵਾਪਸ;
    }
  ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਕੋਡ (constructor_type) == UNION_TYPE
	   && !vec_ਸੁਰੱਖਿਅਤ_is_ਖਾਲੀ_ਥਾਵਾਂ (constructor_elements))
    {
      ਜੇ (!implicit)
	{
	  ਜੇ (ਰੁੱਖ_SIDE_EFFECTS (constructor_elements->ਆਖਰੀ ().ਮੁੱਲ))
	    warning_init (loc, OPT_Woverride_init_side_effects,
			  "initialized field with side-effects overwritten");
	  ਨਹੀਂਤਾਂ ਜੇ (warn_override_init)
	    warning_init (loc, OPT_Woverride_init,
			  "initialized field overwritten");
	}

      /* We can have just one union field set.  */
      constructor_elements = ਨਿਰਾ;
    }

  /* Otherwise, output this element either to
     constructor_elements or to the assembler file.  */

  constructor_elt celt = {ਖੇਤਰ_2, ਮੁੱਲ};
  vec_ਸੁਰੱਖਿਅਤ_ਧੱਕੋ (constructor_elements, celt);

  /* Advance the variable that indicates sequential elements output.  */
  ਜੇ (ਰੁੱਖ_ਕੋਡ (constructor_type) == ARRAY_TYPE)
    {
      ਰੁੱਖ inc = bitsize_one_ਗੰਢ;
      ਜੇ (ਮੁੱਲ && ਰੁੱਖ_ਕੋਡ (ਮੁੱਲ) == RAW_ਅੰਕੜੇ_CST)
	inc = bitsize_int (RAW_ਅੰਕੜੇ_ਲੰਮਾਈ (ਮੁੱਲ));
      constructor_unfilled_ਸੂਚਕਾਂਕ
	= ਮਾਪ_binop_loc (ਨਿਵੇਸ਼_location, PLUS_ਵਿਅੰਜਕ,
			  constructor_unfilled_ਸੂਚਕਾਂਕ, inc);
    }
  ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਕੋਡ (constructor_type) == ਰਿਕਾਰਡ_TYPE)
    {
      constructor_unfilled_fields
	= DECL_CHAIN (constructor_unfilled_fields);

      /* Skip any nameless bit fields.  */
      ਜਦੋਂ (constructor_unfilled_fields != NULL_ਰੁੱਖ
	     && DECL_UNNAMED_ਦੋਆਧਾਰੀ_ਅੰਕ_ਖੇਤਰ (constructor_unfilled_fields))
	constructor_unfilled_fields
	  = DECL_CHAIN (constructor_unfilled_fields);
    }
  ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਕੋਡ (constructor_type) == UNION_TYPE)
    constructor_unfilled_fields = NULL_ਰੁੱਖ;

  /* Now output any pending elements which have become next.  */
  ਜੇ (pending)
    output_pending_init_elements (0, braced_init_obstack);
}

/* For two FIELD_DECLs in the same chain, return -1 if field1
   comes before field2, 1 if field1 comes after field2 and
   0 if field1 == field2.  */

ਸਥਿਰ ਪੂਰਨ
init_ਖੇਤਰ_decl_cmp (ਰੁੱਖ field1, ਰੁੱਖ field2)
{
  ਜੇ (field1 == field2)
    ਵਾਪਸ 0;

  ਰੁੱਖ bitpos1 = ਦੋਆਧਾਰੀ_ਅੰਕ_position (field1);
  ਰੁੱਖ bitpos2 = ਦੋਆਧਾਰੀ_ਅੰਕ_position (field2);
  ਜੇ (ਰੁੱਖ_int_cst_equal (bitpos1, bitpos2))
    {
      /* If one of the fields has non-zero bitsize, then that
	 field must be the last one in a sequence of zero
	 sized fields, fields after it will have bigger
	 bit_position.  */
      ਜੇ (ਰੁੱਖ_TYPE (field1) != error_mark_ਗੰਢ
	  && COMPLETE_TYPE_P (ਰੁੱਖ_TYPE (field1))
	  && integer_nonzerop (ਰੁੱਖ_TYPE (field1)))
	ਵਾਪਸ 1;
      ਜੇ (ਰੁੱਖ_TYPE (field2) != error_mark_ਗੰਢ
	  && COMPLETE_TYPE_P (ਰੁੱਖ_TYPE (field2))
	  && integer_nonzerop (ਰੁੱਖ_TYPE (field2)))
	ਵਾਪਸ -1;
      /* Otherwise, fallback to DECL_CHAIN walk to find out
	 which field comes earlier.  Walk chains of both
	 fields, so that if field1 and field2 are close to each
	 other in either order, it is found soon even for large
	 sequences of zero sized fields.  */
      ਰੁੱਖ f1 = field1, f2 = field2;
      ਜਦੋਂ (1)
	{
	  f1 = DECL_CHAIN (f1);
	  f2 = DECL_CHAIN (f2);
	  ਜੇ (f1 == NULL_ਰੁੱਖ)
	    {
	      gcc_assert (f2);
	      ਵਾਪਸ 1;
	    }
	  ਜੇ (f2 == NULL_ਰੁੱਖ)
	    ਵਾਪਸ -1;
	  ਜੇ (f1 == field2)
	    ਵਾਪਸ -1;
	  ਜੇ (f2 == field1)
	    ਵਾਪਸ 1;
	  ਜੇ (!ਰੁੱਖ_int_cst_equal (ਦੋਆਧਾਰੀ_ਅੰਕ_position (f1), bitpos1))
	    ਵਾਪਸ 1;
	  ਜੇ (!ਰੁੱਖ_int_cst_equal (ਦੋਆਧਾਰੀ_ਅੰਕ_position (f2), bitpos1))
	    ਵਾਪਸ -1;
	}
    }
  ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_int_cst_lt (bitpos1, bitpos2))
    ਵਾਪਸ -1;
  ਨਹੀਂਤਾਂ
    ਵਾਪਸ 1;
}

/* Output any pending elements which have become next.
   As we output elements, constructor_unfilled_{fields,index}
   advances, which may cause other elements to become next;
   if so, they too are output.

   If ALL is 0, we return when there are
   no more pending elements to output now.

   If ALL is 1, we output space as necessary so that
   we can output all the pending elements.  */
ਸਥਿਰ ਖਾਲੀ
output_pending_init_elements (ਪੂਰਨ all, ਬਣਤਰ obstack * braced_init_obstack)
{
  ਬਣਤਰ init_ਗੰਢ *elt = constructor_pending_elts;
  ਰੁੱਖ ਅਗਲਾ;

 retry:

  /* Look through the whole pending tree.
     If we find an element that should be output now,
     output it.  Otherwise, set NEXT to the element
     that comes first among those still pending.  */

  ਅਗਲਾ = NULL_ਰੁੱਖ;
  ਜਦੋਂ (elt)
    {
      ਜੇ (ਰੁੱਖ_ਕੋਡ (constructor_type) == ARRAY_TYPE)
	{
	  ਜੇ (ਰੁੱਖ_int_cst_equal (elt->purpose,
				  constructor_unfilled_ਸੂਚਕਾਂਕ))
	    output_init_element (ਨਿਵੇਸ਼_location, elt->ਮੁੱਲ, elt->origtype,
				 ਸੱਚ, ਰੁੱਖ_TYPE (constructor_type),
				 constructor_unfilled_ਸੂਚਕਾਂਕ, ਝੂਠ, ਝੂਠ,
				 braced_init_obstack);
	  ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_int_cst_lt (constructor_unfilled_ਸੂਚਕਾਂਕ,
				    elt->purpose))
	    {
	      /* Advance to the next smaller node.  */
	      ਜੇ (elt->ਖੱਬੇ)
		elt = elt->ਖੱਬੇ;
	      ਨਹੀਂਤਾਂ
		{
		  /* We have reached the smallest node bigger than the
		     current unfilled index.  Fill the space first.  */
		  ਅਗਲਾ = elt->purpose;
		  ਰੋਕੋ;
		}
	    }
	  ਨਹੀਂਤਾਂ
	    {
	      /* Advance to the next bigger node.  */
	      ਜੇ (elt->ਸੱਜੇ)
		elt = elt->ਸੱਜੇ;
	      ਨਹੀਂਤਾਂ
		{
		  /* We have reached the biggest node in a subtree.  Find
		     the parent of it, which is the next bigger node.  */
		  ਜਦੋਂ (elt->ਮਾਪਾ && elt->ਮਾਪਾ->ਸੱਜੇ == elt)
		    elt = elt->ਮਾਪਾ;
		  elt = elt->ਮਾਪਾ;
		  ਜੇ (elt && ਰੁੱਖ_int_cst_lt (constructor_unfilled_ਸੂਚਕਾਂਕ,
					      elt->purpose))
		    {
		      ਅਗਲਾ = elt->purpose;
		      ਰੋਕੋ;
		    }
		}
	    }
	}
      ਨਹੀਂਤਾਂ ਜੇ (ਰਿਕਾਰਡ_OR_UNION_TYPE_P (constructor_type))
	{
	  /* If the current record is complete we are done.  */
	  ਜੇ (constructor_unfilled_fields == NULL_ਰੁੱਖ)
	    ਰੋਕੋ;

	  ਪੂਰਨ cmp = init_ਖੇਤਰ_decl_cmp (constructor_unfilled_fields,
					 elt->purpose);
	  ਜੇ (cmp == 0)
	    output_init_element (ਨਿਵੇਸ਼_location, elt->ਮੁੱਲ, elt->origtype,
				 ਸੱਚ, ਰੁੱਖ_TYPE (elt->purpose),
				 elt->purpose, ਝੂਠ, ਝੂਠ,
				 braced_init_obstack);
	  ਨਹੀਂਤਾਂ ਜੇ (cmp < 0)
	    {
	      /* Advance to the next smaller node.  */
	      ਜੇ (elt->ਖੱਬੇ)
		elt = elt->ਖੱਬੇ;
	      ਨਹੀਂਤਾਂ
		{
		  /* We have reached the smallest node bigger than the
		     current unfilled field.  Fill the space first.  */
		  ਅਗਲਾ = elt->purpose;
		  ਰੋਕੋ;
		}
	    }
	  ਨਹੀਂਤਾਂ
	    {
	      /* Advance to the next bigger node.  */
	      ਜੇ (elt->ਸੱਜੇ)
		elt = elt->ਸੱਜੇ;
	      ਨਹੀਂਤਾਂ
		{
		  /* We have reached the biggest node in a subtree.  Find
		     the parent of it, which is the next bigger node.  */
		  ਜਦੋਂ (elt->ਮਾਪਾ && elt->ਮਾਪਾ->ਸੱਜੇ == elt)
		    elt = elt->ਮਾਪਾ;
		  elt = elt->ਮਾਪਾ;
		  ਜੇ (elt
		      && init_ਖੇਤਰ_decl_cmp (constructor_unfilled_fields,
					      elt->purpose) < 0)
		    {
		      ਅਗਲਾ = elt->purpose;
		      ਰੋਕੋ;
		    }
		}
	    }
	}
    }

  /* Ordinarily return, but not if we want to output all
     and there are elements left.  */
  ਜੇ (!(all && ਅਗਲਾ != NULL_ਰੁੱਖ))
    ਵਾਪਸ;

  /* If it's not incremental, just skip over the gap, so that after
     jumping to retry we will output the next successive element.  */
  ਜੇ (ਰਿਕਾਰਡ_OR_UNION_TYPE_P (constructor_type))
    constructor_unfilled_fields = ਅਗਲਾ;
  ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਕੋਡ (constructor_type) == ARRAY_TYPE)
    constructor_unfilled_ਸੂਚਕਾਂਕ = ਅਗਲਾ;

  /* ELT now points to the node in the pending tree with the next
     initializer to output.  */
  ਜਾਓ retry;
}

/* Expression VALUE coincides with the start of type TYPE in a braced
   initializer.  Return true if we should treat VALUE as initializing
   the first element of TYPE, false if we should treat it as initializing
   TYPE as a whole.

   If the initializer is clearly invalid, the question becomes:
   which choice gives the best error message?  */

ਸਥਿਰ ਤਾਰਕਿਕ
initialize_elementwise_p (ਰੁੱਖ type, ਰੁੱਖ ਮੁੱਲ)
{
  ਜੇ (type == error_mark_ਗੰਢ || ਮੁੱਲ == error_mark_ਗੰਢ)
    ਵਾਪਸ ਝੂਠ;

  gcc_checking_assert (TYPE_MAIN_VARIANT (type) == type);

  ਰੁੱਖ ਮੁੱਲ_type = ਰੁੱਖ_TYPE (ਮੁੱਲ);
  ਜੇ (ਮੁੱਲ_type == error_mark_ਗੰਢ)
    ਵਾਪਸ ਝੂਠ;

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
  ਜੇ (gnu_ਸਦਿਸ਼_type_p (type))
    ਵਾਪਸ !ਸਦਿਸ਼_TYPE_P (ਮੁੱਲ_type);

  ਜੇ (AGGREGATE_TYPE_P (type))
    ਵਾਪਸ !comptypes (type, TYPE_MAIN_VARIANT (ਮੁੱਲ_type));

  ਵਾਪਸ ਝੂਠ;
}

/* Helper function for process_init_element.  Split first element of
   RAW_DATA_CST and save the rest to *RAW_DATA.  */

ਸਥਿਰ ਸਤਰਅੰਦਰ ਰੁੱਖ
maybe_ਵੰਡੋ_raw_ਅੰਕੜੇ (ਰੁੱਖ ਮੁੱਲ, ਰੁੱਖ *raw_ਅੰਕੜੇ)
{
  ਜੇ (ਮੁੱਲ == NULL_ਰੁੱਖ || ਰੁੱਖ_ਕੋਡ (ਮੁੱਲ) != RAW_ਅੰਕੜੇ_CST)
    ਵਾਪਸ ਮੁੱਲ;
  *raw_ਅੰਕੜੇ = ਮੁੱਲ;
  ਮੁੱਲ = build_int_cst (integer_type_ਗੰਢ,
			 RAW_ਅੰਕੜੇ_UCHAR_ELT (*raw_ਅੰਕੜੇ, 0));
  ++RAW_ਅੰਕੜੇ_ਸੂਚਕ (*raw_ਅੰਕੜੇ);
  --RAW_ਅੰਕੜੇ_ਲੰਮਾਈ (*raw_ਅੰਕੜੇ);
  ਵਾਪਸ ਮੁੱਲ;
}

/* Return non-zero if c_parser_initval should attempt to optimize
   large initializers into RAW_DATA_CST.  In that case return how
   many elements to optimize at most.  */

ਬਿਨਾਨਿਸ਼ਾਨੀ
c_maybe_optimize_large_byte_initializer (ਖਾਲੀ)
{
  ਜੇ (!constructor_type
      || ਰੁੱਖ_ਕੋਡ (constructor_type) != ARRAY_TYPE
      || constructor_ਢੇਰ->implicit)
    ਵਾਪਸ 0;
  ਰੁੱਖ elttype = TYPE_MAIN_VARIANT (ਰੁੱਖ_TYPE (constructor_type));
  ਜੇ (ਰੁੱਖ_ਕੋਡ (elttype) != INTEGER_TYPE
      && ਰੁੱਖ_ਕੋਡ (elttype) != BITINT_TYPE)
    ਵਾਪਸ 0;
  ਜੇ (TYPE_PRECISION (elttype) != CHAR_ਦੋਆਧਾਰੀ_ਅੰਕ
      || constructor_ਢੇਰ->replacement_ਮੁੱਲ.ਮੁੱਲ
      || (COMPLETE_TYPE_P (constructor_type)
	  && !poly_int_ਰੁੱਖ_p (TYPE_ਮਾਪ (constructor_type)))
      || constructor_range_ਢੇਰ)
    ਵਾਪਸ 0;
  ਜੇ (constructor_max_ਸੂਚਕਾਂਕ == NULL_ਰੁੱਖ)
    ਵਾਪਸ ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ;
  ਜੇ (ਰੁੱਖ_int_cst_le (constructor_max_ਸੂਚਕਾਂਕ, constructor_ਸੂਚਕਾਂਕ)
      || integer_all_onesp (constructor_max_ਸੂਚਕਾਂਕ))
    ਵਾਪਸ 0;
  widest_int w = wi::ਮੰਜ਼ਿਲ_widest (constructor_max_ਸੂਚਕਾਂਕ);
  w -= wi::ਮੰਜ਼ਿਲ_widest (constructor_ਸੂਚਕਾਂਕ);
  w += 1;
  ਜੇ (w < 64)
    ਵਾਪਸ 0;
  ਜੇ (w > ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ)
    ਵਾਪਸ ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ;
  ਵਾਪਸ w.ਮੰਜ਼ਿਲ_uhwi ();
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

ਖਾਲੀ
process_init_element (location_t loc, ਬਣਤਰ c_ਵਿਅੰਜਕ ਮੁੱਲ, ਤਾਰਕਿਕ implicit,
		      ਬਣਤਰ obstack * braced_init_obstack)
{
  ਰੁੱਖ orig_ਮੁੱਲ = ਮੁੱਲ.ਮੁੱਲ;
  ਪੂਰਨ string_flag
    = (orig_ਮੁੱਲ != NULL_ਰੁੱਖ && ਰੁੱਖ_ਕੋਡ (orig_ਮੁੱਲ) == STRING_CST);
  ਤਾਰਕਿਕ strict_string = ਮੁੱਲ.original_ਕੋਡ == STRING_CST;
  ਤਾਰਕਿਕ was_designated = designator_ਡੂੰਘਾਈ != 0;
  ਰੁੱਖ raw_ਅੰਕੜੇ = NULL_ਰੁੱਖ;

retry:
  designator_ਡੂੰਘਾਈ = 0;
  designator_erroneous = 0;

  ਜੇ (!implicit && ਮੁੱਲ.ਮੁੱਲ && !integer_zerop (ਮੁੱਲ.ਮੁੱਲ))
    constructor_zeroinit = 0;

  /* Handle superfluous braces around string cst as in
     char x[] = {"foo"}; */
  ਜੇ (constructor_type
      && !was_designated
      && ਰੁੱਖ_ਕੋਡ (constructor_type) == ARRAY_TYPE
      && INTEGRAL_TYPE_P (ਰੁੱਖ_TYPE (constructor_type))
      && integer_zerop (constructor_unfilled_ਸੂਚਕਾਂਕ))
    {
      ਜੇ (constructor_ਢੇਰ->replacement_ਮੁੱਲ.ਮੁੱਲ)
	{
	  error_init (loc, "excess elements in %qT initializer", constructor_type);
	  ਵਾਪਸ;
	}
      ਨਹੀਂਤਾਂ ਜੇ (string_flag)
	{
	  constructor_ਢੇਰ->replacement_ਮੁੱਲ = ਮੁੱਲ;
	  ਵਾਪਸ;
	}
    }

  ਜੇ (constructor_ਢੇਰ->replacement_ਮੁੱਲ.ਮੁੱਲ != NULL_ਰੁੱਖ)
    {
      error_init (loc, "excess elements in struct initializer");
      ਵਾਪਸ;
    }

  /* Ignore elements of a brace group if it is entirely superfluous
     and has already been diagnosed, or if the type is erroneous.  */
  ਜੇ (constructor_type == NULL_ਰੁੱਖ || constructor_type == error_mark_ਗੰਢ)
    ਵਾਪਸ;

  /* Ignore elements of an initializer for a variable-size type.
     Those are diagnosed in the parser (empty initializer braces are OK).  */
  ਜੇ (COMPLETE_TYPE_P (constructor_type)
      && !poly_int_ਰੁੱਖ_p (TYPE_ਮਾਪ (constructor_type)))
    ਵਾਪਸ;

  ਜੇ (!implicit && warn_designated_init && !was_designated
      && ਰੁੱਖ_ਕੋਡ (constructor_type) == ਰਿਕਾਰਡ_TYPE
      && lookup_attribute ("designated_init",
			   TYPE_ਗੁਣ (constructor_type)))
    warning_init (loc,
		  OPT_Wdesignated_init,
		  "positional initialization of field "
		  "in %<struct%> declared with %<designated_init%> attribute");

  /* If we've exhausted any levels that didn't have braces,
     pop them now.  */
  ਜਦੋਂ (constructor_ਢੇਰ->implicit)
    {
      ਜੇ (ਰਿਕਾਰਡ_OR_UNION_TYPE_P (constructor_type)
	  && constructor_fields == NULL_ਰੁੱਖ)
	process_init_element (loc,
			      ਕੱਢੋ_init_level (loc, 1, braced_init_obstack,
					      ਆਖਰੀ_init_list_comma),
			      ਸੱਚ, braced_init_obstack);
      ਨਹੀਂਤਾਂ ਜੇ ((ਰੁੱਖ_ਕੋਡ (constructor_type) == ARRAY_TYPE
		|| gnu_ਸਦਿਸ਼_type_p (constructor_type))
	       && constructor_max_ਸੂਚਕਾਂਕ
	       && ਰੁੱਖ_int_cst_lt (constructor_max_ਸੂਚਕਾਂਕ,
				   constructor_ਸੂਚਕਾਂਕ))
	process_init_element (loc,
			      ਕੱਢੋ_init_level (loc, 1, braced_init_obstack,
					      ਆਖਰੀ_init_list_comma),
			      ਸੱਚ, braced_init_obstack);
      ਨਹੀਂਤਾਂ
	ਰੋਕੋ;
    }

  /* In the case of [LO ... HI] = VALUE, only evaluate VALUE once.  */
  ਜੇ (constructor_range_ਢੇਰ)
    {
      /* If value is a compound literal and we'll be just using its
	 content, don't put it into a SAVE_EXPR.  */
      ਜੇ (ਰੁੱਖ_ਕੋਡ (ਮੁੱਲ.ਮੁੱਲ) != COMPOUND_LITERAL_ਵਿਅੰਜਕ
	  || !require_constant_ਮੁੱਲ)
	{
	  ਰੁੱਖ semantic_type = NULL_ਰੁੱਖ;
	  ਜੇ (ਰੁੱਖ_ਕੋਡ (ਮੁੱਲ.ਮੁੱਲ) == EXCESS_PRECISION_ਵਿਅੰਜਕ)
	    {
	      semantic_type = ਰੁੱਖ_TYPE (ਮੁੱਲ.ਮੁੱਲ);
	      ਮੁੱਲ.ਮੁੱਲ = ਰੁੱਖ_ਸੰਕਾਰਜ (ਮੁੱਲ.ਮੁੱਲ, 0);
	    }
	  ਮੁੱਲ.ਮੁੱਲ = save_ਵਿਅੰਜਕ (ਮੁੱਲ.ਮੁੱਲ);
	  ਜੇ (semantic_type)
	    ਮੁੱਲ.ਮੁੱਲ = build1 (EXCESS_PRECISION_ਵਿਅੰਜਕ, semantic_type,
				  ਮੁੱਲ.ਮੁੱਲ);
	}
    }

  ਜਦੋਂ (1)
    {
      ਜੇ (ਰੁੱਖ_ਕੋਡ (constructor_type) == ਰਿਕਾਰਡ_TYPE)
	{
	  ਰੁੱਖ fieldtype;
	  ਗਿਣਤੀ ਰੁੱਖ_ਕੋਡ_2 fieldcode;

	  ਜੇ (constructor_fields == NULL_ਰੁੱਖ)
	    {
	      pedwarn_init (loc, 0, "excess elements in struct initializer");
	      ਰੋਕੋ;
	    }

	  fieldtype = ਰੁੱਖ_TYPE (constructor_fields);
	  ਜੇ (fieldtype != error_mark_ਗੰਢ)
	    fieldtype = TYPE_MAIN_VARIANT (fieldtype);
	  fieldcode = ਰੁੱਖ_ਕੋਡ (fieldtype);

	  /* Error for non-static initialization of a flexible array member.  */
	  ਜੇ (fieldcode == ARRAY_TYPE
	      && !require_constant_ਮੁੱਲ
	      && TYPE_ਮਾਪ (fieldtype) == NULL_ਰੁੱਖ
	      && DECL_CHAIN (constructor_fields) == NULL_ਰੁੱਖ)
	    {
	      error_init (loc, "non-static initialization of a flexible "
			  "array member");
	      ਰੋਕੋ;
	    }

	  /* Error for initialization of a flexible array member with
	     a string constant if the structure is in an array.  E.g.:
	     struct S { int x; char y[]; };
	     struct S s[] = { { 1, "foo" } };
	     is invalid.  */
	  ਜੇ (string_flag
	      && fieldcode == ARRAY_TYPE
	      && constructor_ਡੂੰਘਾਈ > 1
	      && TYPE_ਮਾਪ (fieldtype) == NULL_ਰੁੱਖ
	      && DECL_CHAIN (constructor_fields) == NULL_ਰੁੱਖ)
	    {
	      ਤਾਰਕਿਕ ਵਿੱਚ_array_p = ਝੂਠ;
	      ਲਈ (ਬਣਤਰ constructor_ਢੇਰ *p = constructor_ਢੇਰ;
		   p && p->type; p = p->ਅਗਲਾ)
		ਜੇ (ਰੁੱਖ_ਕੋਡ (p->type) == ARRAY_TYPE)
		  {
		    ਵਿੱਚ_array_p = ਸੱਚ;
		    ਰੋਕੋ;
		  }
	      ਜੇ (ਵਿੱਚ_array_p)
		{
		  error_init (loc, "initialization of flexible array "
			      "member in a nested context");
		  ਰੋਕੋ;
		}
	    }

	  /* Accept a string constant to initialize a subarray.  */
	  ਜੇ (ਮੁੱਲ.ਮੁੱਲ != NULL_ਰੁੱਖ
	      && fieldcode == ARRAY_TYPE
	      && INTEGRAL_TYPE_P (ਰੁੱਖ_TYPE (fieldtype))
	      && string_flag)
	    ਮੁੱਲ.ਮੁੱਲ = orig_ਮੁੱਲ;
	  /* Otherwise, if we have come to a subaggregate,
	     and we don't have an element of its type, push into it.  */
	  ਨਹੀਂਤਾਂ ਜੇ (ਮੁੱਲ.ਮੁੱਲ != NULL_ਰੁੱਖ
		   && initialize_elementwise_p (fieldtype, ਮੁੱਲ.ਮੁੱਲ))
	    {
	      ਧੱਕੋ_init_level (loc, 1, braced_init_obstack);
	      ਜਾਰੀ;
	    }

	  ਮੁੱਲ.ਮੁੱਲ = maybe_ਵੰਡੋ_raw_ਅੰਕੜੇ (ਮੁੱਲ.ਮੁੱਲ, &raw_ਅੰਕੜੇ);
	  ਜੇ (ਮੁੱਲ.ਮੁੱਲ)
	    {
	      ਧੱਕੋ_member_name (constructor_fields);
	      output_init_element (loc, ਮੁੱਲ.ਮੁੱਲ, ਮੁੱਲ.original_type,
				   strict_string, fieldtype,
				   constructor_fields, ਸੱਚ, implicit,
				   braced_init_obstack);
	      RESTORE_SPELLING_ਡੂੰਘਾਈ (constructor_ਡੂੰਘਾਈ);
	    }
	  ਨਹੀਂਤਾਂ
	    /* Do the bookkeeping for an element that was
	       directly output as a constructor.  */
	    {
	      /* For a record, keep track of end position of last field.  */
	      ਜੇ (DECL_ਮਾਪ (constructor_fields))
		constructor_ਦੋਆਧਾਰੀ_ਅੰਕ_ਸੂਚਕਾਂਕ
		  = ਮਾਪ_binop_loc (ਨਿਵੇਸ਼_location, PLUS_ਵਿਅੰਜਕ,
				    ਦੋਆਧਾਰੀ_ਅੰਕ_position (constructor_fields),
				    DECL_ਮਾਪ (constructor_fields));

	      /* If the current field was the first one not yet written out,
		 it isn't now, so update.  */
	      ਜੇ (constructor_unfilled_fields == constructor_fields)
		{
		  constructor_unfilled_fields = DECL_CHAIN (constructor_fields);
		  /* Skip any nameless bit fields.  */
		  ਜਦੋਂ (constructor_unfilled_fields != 0
			 && (DECL_UNNAMED_ਦੋਆਧਾਰੀ_ਅੰਕ_ਖੇਤਰ
			     (constructor_unfilled_fields)))
		    constructor_unfilled_fields =
		      DECL_CHAIN (constructor_unfilled_fields);
		}
	    }

	  constructor_fields = DECL_CHAIN (constructor_fields);
	  /* Skip any nameless bit fields at the beginning.  */
	  ਜਦੋਂ (constructor_fields != NULL_ਰੁੱਖ
		 && DECL_UNNAMED_ਦੋਆਧਾਰੀ_ਅੰਕ_ਖੇਤਰ (constructor_fields))
	    constructor_fields = DECL_CHAIN (constructor_fields);
	}
      ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਕੋਡ (constructor_type) == UNION_TYPE)
	{
	  ਰੁੱਖ fieldtype;
	  ਗਿਣਤੀ ਰੁੱਖ_ਕੋਡ_2 fieldcode;

	  ਜੇ (constructor_fields == NULL_ਰੁੱਖ)
	    {
	      pedwarn_init (loc, 0,
			    "excess elements in union initializer");
	      ਰੋਕੋ;
	    }

	  fieldtype = ਰੁੱਖ_TYPE (constructor_fields);
	  ਜੇ (fieldtype != error_mark_ਗੰਢ)
	    fieldtype = TYPE_MAIN_VARIANT (fieldtype);
	  fieldcode = ਰੁੱਖ_ਕੋਡ (fieldtype);

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
	  ਜੇ (!ਵਿੱਚ_system_ਸਿਰਲੇਖ_at (ਨਿਵੇਸ਼_location) && !constructor_designated
	      && !(ਮੁੱਲ.ਮੁੱਲ && (integer_zerop (ਮੁੱਲ.ਮੁੱਲ)
				   || real_zerop (ਮੁੱਲ.ਮੁੱਲ))))
	    warning (OPT_Wtraditional, "traditional C rejects initialization "
		     "of unions");

	  /* Error for non-static initialization of a flexible array member.  */
	  ਜੇ (fieldcode == ARRAY_TYPE
	      && !require_constant_ਮੁੱਲ
	      && TYPE_ਮਾਪ (fieldtype) == NULL_ਰੁੱਖ)
	    {
	      error_init (loc, "non-static initialization of a flexible "
			  "array member");
	      ਰੋਕੋ;
	    }

	  /* Error for initialization of a flexible array member with
	     a string constant if the structure is in an array.  E.g.:
	     union U { int x; char y[]; };
	     union U s[] = { { 1, "foo" } };
	     is invalid.  */
	  ਜੇ (string_flag
	      && fieldcode == ARRAY_TYPE
	      && constructor_ਡੂੰਘਾਈ > 1
	      && TYPE_ਮਾਪ (fieldtype) == NULL_ਰੁੱਖ)
	    {
	      ਤਾਰਕਿਕ ਵਿੱਚ_array_p = ਝੂਠ;
	      ਲਈ (ਬਣਤਰ constructor_ਢੇਰ *p = constructor_ਢੇਰ;
		   p && p->type; p = p->ਅਗਲਾ)
		ਜੇ (ਰੁੱਖ_ਕੋਡ (p->type) == ARRAY_TYPE)
		  {
		    ਵਿੱਚ_array_p = ਸੱਚ;
		    ਰੋਕੋ;
		  }
	      ਜੇ (ਵਿੱਚ_array_p)
		{
		  error_init (loc, "initialization of flexible array "
			      "member in a nested context");
		  ਰੋਕੋ;
		}
	    }

	  /* Accept a string constant to initialize a subarray.  */
	  ਜੇ (ਮੁੱਲ.ਮੁੱਲ != NULL_ਰੁੱਖ
	      && fieldcode == ARRAY_TYPE
	      && INTEGRAL_TYPE_P (ਰੁੱਖ_TYPE (fieldtype))
	      && string_flag)
	    ਮੁੱਲ.ਮੁੱਲ = orig_ਮੁੱਲ;
	  /* Otherwise, if we have come to a subaggregate,
	     and we don't have an element of its type, push into it.  */
	  ਨਹੀਂਤਾਂ ਜੇ (ਮੁੱਲ.ਮੁੱਲ != NULL_ਰੁੱਖ
		   && initialize_elementwise_p (fieldtype, ਮੁੱਲ.ਮੁੱਲ))
	    {
	      ਧੱਕੋ_init_level (loc, 1, braced_init_obstack);
	      ਜਾਰੀ;
	    }

	  ਮੁੱਲ.ਮੁੱਲ = maybe_ਵੰਡੋ_raw_ਅੰਕੜੇ (ਮੁੱਲ.ਮੁੱਲ, &raw_ਅੰਕੜੇ);
	  ਜੇ (ਮੁੱਲ.ਮੁੱਲ)
	    {
	      ਧੱਕੋ_member_name (constructor_fields);
	      output_init_element (loc, ਮੁੱਲ.ਮੁੱਲ, ਮੁੱਲ.original_type,
				   strict_string, fieldtype,
				   constructor_fields, ਸੱਚ, implicit,
				   braced_init_obstack);
	      RESTORE_SPELLING_ਡੂੰਘਾਈ (constructor_ਡੂੰਘਾਈ);
	    }
	  ਨਹੀਂਤਾਂ
	    /* Do the bookkeeping for an element that was
	       directly output as a constructor.  */
	    {
	      constructor_ਦੋਆਧਾਰੀ_ਅੰਕ_ਸੂਚਕਾਂਕ = DECL_ਮਾਪ (constructor_fields);
	      constructor_unfilled_fields = DECL_CHAIN (constructor_fields);
	    }

	  constructor_fields = NULL_ਰੁੱਖ;
	}
      ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਕੋਡ (constructor_type) == ARRAY_TYPE)
	{
	  ਰੁੱਖ elttype = TYPE_MAIN_VARIANT (ਰੁੱਖ_TYPE (constructor_type));
	  ਗਿਣਤੀ ਰੁੱਖ_ਕੋਡ_2 eltcode = ਰੁੱਖ_ਕੋਡ (elttype);

	  /* Accept a string constant to initialize a subarray.  */
	  ਜੇ (ਮੁੱਲ.ਮੁੱਲ != NULL_ਰੁੱਖ
	      && eltcode == ARRAY_TYPE
	      && INTEGRAL_TYPE_P (ਰੁੱਖ_TYPE (elttype))
	      && string_flag)
	    ਮੁੱਲ.ਮੁੱਲ = orig_ਮੁੱਲ;
	  /* Otherwise, if we have come to a subaggregate,
	     and we don't have an element of its type, push into it.  */
	  ਨਹੀਂਤਾਂ ਜੇ (ਮੁੱਲ.ਮੁੱਲ != NULL_ਰੁੱਖ
		   && initialize_elementwise_p (elttype, ਮੁੱਲ.ਮੁੱਲ))
	    {
	      ਧੱਕੋ_init_level (loc, 1, braced_init_obstack);
	      ਜਾਰੀ;
	    }

	  ਜੇ (constructor_max_ਸੂਚਕਾਂਕ != NULL_ਰੁੱਖ
	      && (ਰੁੱਖ_int_cst_lt (constructor_max_ਸੂਚਕਾਂਕ, constructor_ਸੂਚਕਾਂਕ)
		  || integer_all_onesp (constructor_max_ਸੂਚਕਾਂਕ))
	      /* For VLA we got an error already.  */
	      && !C_TYPE_VARIABLE_ਮਾਪ (constructor_type))
	    {
	      pedwarn_init (loc, 0,
			    "excess elements in array initializer");
	      ਰੋਕੋ;
	    }

	  ਜੇ (ਮੁੱਲ.ਮੁੱਲ
	      && ਰੁੱਖ_ਕੋਡ (ਮੁੱਲ.ਮੁੱਲ) == RAW_ਅੰਕੜੇ_CST
	      && RAW_ਅੰਕੜੇ_ਲੰਮਾਈ (ਮੁੱਲ.ਮੁੱਲ) > 1
	      && (ਰੁੱਖ_ਕੋਡ (elttype) == INTEGER_TYPE
		  || ਰੁੱਖ_ਕੋਡ (elttype) == BITINT_TYPE)
	      && TYPE_PRECISION (elttype) == CHAR_ਦੋਆਧਾਰੀ_ਅੰਕ
	      && (constructor_max_ਸੂਚਕਾਂਕ == NULL_ਰੁੱਖ
		  || ਰੁੱਖ_int_cst_lt (constructor_ਸੂਚਕਾਂਕ,
				      constructor_max_ਸੂਚਕਾਂਕ)))
	    {
	      ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ len = RAW_ਅੰਕੜੇ_ਲੰਮਾਈ (ਮੁੱਲ.ਮੁੱਲ);
	      ਜੇ (constructor_max_ਸੂਚਕਾਂਕ)
		{
		  widest_int w = wi::ਮੰਜ਼ਿਲ_widest (constructor_max_ਸੂਚਕਾਂਕ);
		  w -= wi::ਮੰਜ਼ਿਲ_widest (constructor_ਸੂਚਕਾਂਕ);
		  w += 1;
		  ਜੇ (w < len)
		    len = w.ਮੰਜ਼ਿਲ_uhwi ();
		}
	      ਜੇ (len < (ਬਿਨਾਨਿਸ਼ਾਨੀ) RAW_ਅੰਕੜੇ_ਲੰਮਾਈ (ਮੁੱਲ.ਮੁੱਲ))
		{
		  raw_ਅੰਕੜੇ = copy_ਗੰਢ (ਮੁੱਲ.ਮੁੱਲ);
		  RAW_ਅੰਕੜੇ_ਲੰਮਾਈ (raw_ਅੰਕੜੇ) -= len;
		  RAW_ਅੰਕੜੇ_ਸੂਚਕ (raw_ਅੰਕੜੇ) += len;
		  RAW_ਅੰਕੜੇ_ਲੰਮਾਈ (ਮੁੱਲ.ਮੁੱਲ) = len;
		}
	      ਰੁੱਖ_TYPE (ਮੁੱਲ.ਮੁੱਲ) = elttype;
	      ਧੱਕੋ_array_bounds (ਰੁੱਖ_ਮੰਜ਼ਿਲ_uhwi (constructor_ਸੂਚਕਾਂਕ));
	      output_init_element (loc, ਮੁੱਲ.ਮੁੱਲ, ਮੁੱਲ.original_type,
				   ਝੂਠ, elttype, constructor_ਸੂਚਕਾਂਕ, ਸੱਚ,
				   implicit, braced_init_obstack);
	      RESTORE_SPELLING_ਡੂੰਘਾਈ (constructor_ਡੂੰਘਾਈ);
	      constructor_ਸੂਚਕਾਂਕ
		= ਮਾਪ_binop_loc (ਨਿਵੇਸ਼_location, PLUS_ਵਿਅੰਜਕ,
				  constructor_ਸੂਚਕਾਂਕ, bitsize_int (len));
	    }
	  ਨਹੀਂਤਾਂ
	    {
	      ਮੁੱਲ.ਮੁੱਲ = maybe_ਵੰਡੋ_raw_ਅੰਕੜੇ (ਮੁੱਲ.ਮੁੱਲ, &raw_ਅੰਕੜੇ);
	      /* Now output the actual element.  */
	      ਜੇ (ਮੁੱਲ.ਮੁੱਲ)
		{
		  ਧੱਕੋ_array_bounds (ਰੁੱਖ_ਮੰਜ਼ਿਲ_uhwi (constructor_ਸੂਚਕਾਂਕ));
		  output_init_element (loc, ਮੁੱਲ.ਮੁੱਲ, ਮੁੱਲ.original_type,
				       strict_string, elttype,
				       constructor_ਸੂਚਕਾਂਕ, ਸੱਚ, implicit,
				       braced_init_obstack);
		  RESTORE_SPELLING_ਡੂੰਘਾਈ (constructor_ਡੂੰਘਾਈ);
		}

	      constructor_ਸੂਚਕਾਂਕ
		= ਮਾਪ_binop_loc (ਨਿਵੇਸ਼_location, PLUS_ਵਿਅੰਜਕ,
				  constructor_ਸੂਚਕਾਂਕ, bitsize_one_ਗੰਢ);

	      ਜੇ (!ਮੁੱਲ.ਮੁੱਲ)
		/* If we are doing the bookkeeping for an element that was
		   directly output as a constructor, we must update
		   constructor_unfilled_index.  */
		constructor_unfilled_ਸੂਚਕਾਂਕ = constructor_ਸੂਚਕਾਂਕ;
	    }
	}
      ਨਹੀਂਤਾਂ ਜੇ (gnu_ਸਦਿਸ਼_type_p (constructor_type))
	{
	  ਰੁੱਖ elttype = TYPE_MAIN_VARIANT (ਰੁੱਖ_TYPE (constructor_type));

	  /* Do a basic check of initializer size.  Note that vectors
	     may not always have a fixed size derived from their type.  */
	  ਜੇ (maybe_lt (ਰੁੱਖ_ਮੰਜ਼ਿਲ_poly_uint64 (constructor_max_ਸੂਚਕਾਂਕ),
			ਰੁੱਖ_ਮੰਜ਼ਿਲ_poly_uint64 (constructor_ਸੂਚਕਾਂਕ)))
	    {
	      /* Diagose VLA out-of-bounds as errors.  */
	      ਜੇ (ਰੁੱਖ_ਮੰਜ਼ਿਲ_poly_uint64 (constructor_max_ਸੂਚਕਾਂਕ).is_constant())
		pedwarn_init (loc, 0,
			      "excess elements in vector initializer");
	      ਨਹੀਂਤਾਂ
		error_init (loc, "excess elements in vector initializer");

	      ਰੋਕੋ;
	    }

	  ਮੁੱਲ.ਮੁੱਲ = maybe_ਵੰਡੋ_raw_ਅੰਕੜੇ (ਮੁੱਲ.ਮੁੱਲ, &raw_ਅੰਕੜੇ);
	  /* Now output the actual element.  */
	  ਜੇ (ਮੁੱਲ.ਮੁੱਲ)
	    {
	      ਜੇ (ਰੁੱਖ_ਕੋਡ (ਮੁੱਲ.ਮੁੱਲ) == ਸਦਿਸ਼_CST)
		elttype = TYPE_MAIN_VARIANT (constructor_type);
	      output_init_element (loc, ਮੁੱਲ.ਮੁੱਲ, ਮੁੱਲ.original_type,
				   strict_string, elttype,
				   constructor_ਸੂਚਕਾਂਕ, ਸੱਚ, implicit,
				   braced_init_obstack);
	    }

	  constructor_ਸੂਚਕਾਂਕ
	    = ਮਾਪ_binop_loc (ਨਿਵੇਸ਼_location,
			      PLUS_ਵਿਅੰਜਕ, constructor_ਸੂਚਕਾਂਕ, bitsize_one_ਗੰਢ);

	  ਜੇ (!ਮੁੱਲ.ਮੁੱਲ)
	    /* If we are doing the bookkeeping for an element that was
	       directly output as a constructor, we must update
	       constructor_unfilled_index.  */
	    constructor_unfilled_ਸੂਚਕਾਂਕ = constructor_ਸੂਚਕਾਂਕ;
	}

      /* Handle the sole element allowed in a braced initializer
	 for a scalar variable.  */
      ਨਹੀਂਤਾਂ ਜੇ (constructor_type != error_mark_ਗੰਢ
	       && constructor_fields == NULL_ਰੁੱਖ)
	{
	  pedwarn_init (loc, 0,
			"excess elements in scalar initializer");
	  ਰੋਕੋ;
	}
      ਨਹੀਂਤਾਂ
	{
	  ਮੁੱਲ.ਮੁੱਲ = maybe_ਵੰਡੋ_raw_ਅੰਕੜੇ (ਮੁੱਲ.ਮੁੱਲ, &raw_ਅੰਕੜੇ);
	  ਜੇ (ਮੁੱਲ.ਮੁੱਲ)
	    output_init_element (loc, ਮੁੱਲ.ਮੁੱਲ, ਮੁੱਲ.original_type,
				 strict_string, constructor_type,
				 NULL_ਰੁੱਖ, ਸੱਚ, implicit,
				 braced_init_obstack);
	  constructor_fields = NULL_ਰੁੱਖ;
	}

      /* Handle range initializers either at this level or anywhere higher
	 in the designator stack.  */
      ਜੇ (constructor_range_ਢੇਰ)
	{
	  ਬਣਤਰ constructor_range_ਢੇਰ *p, *range_ਢੇਰ;
	  ਪੂਰਨ ਅੰਤ = 0;

	  range_ਢੇਰ = constructor_range_ਢੇਰ;
	  constructor_range_ਢੇਰ = 0;
	  ਜਦੋਂ (constructor_ਢੇਰ != range_ਢੇਰ->ਢੇਰ)
	    {
	      gcc_assert (constructor_ਢੇਰ->implicit);
	      process_init_element (loc,
				    ਕੱਢੋ_init_level (loc, 1,
						    braced_init_obstack,
						    ਆਖਰੀ_init_list_comma),
				    ਸੱਚ, braced_init_obstack);
	    }
	  ਲਈ (p = range_ਢੇਰ;
	       !p->range_ਸਿਰਾ || ਰੁੱਖ_int_cst_equal (p->ਸੂਚਕਾਂਕ, p->range_ਸਿਰਾ);
	       p = p->prev)
	    {
	      gcc_assert (constructor_ਢੇਰ->implicit);
	      process_init_element (loc,
				    ਕੱਢੋ_init_level (loc, 1,
						    braced_init_obstack,
						    ਆਖਰੀ_init_list_comma),
				    ਸੱਚ, braced_init_obstack);
	    }

	  p->ਸੂਚਕਾਂਕ = ਮਾਪ_binop_loc (ਨਿਵੇਸ਼_location,
				     PLUS_ਵਿਅੰਜਕ, p->ਸੂਚਕਾਂਕ, bitsize_one_ਗੰਢ);
	  ਜੇ (ਰੁੱਖ_int_cst_equal (p->ਸੂਚਕਾਂਕ, p->range_ਸਿਰਾ) && !p->prev)
	    ਅੰਤ = 1;

	  ਜਦੋਂ (1)
	    {
	      constructor_ਸੂਚਕਾਂਕ = p->ਸੂਚਕਾਂਕ;
	      constructor_fields = p->fields;
	      ਜੇ (ਅੰਤ && p->range_ਸਿਰਾ && p->ਸੂਚਕਾਂਕ == p->range_ਸ਼ੁਰੂ)
		{
		  ਅੰਤ = 0;
		  p->prev = 0;
		}
	      p = p->ਅਗਲਾ;
	      ਜੇ (!p)
		ਰੋਕੋ;
	      ਅੰਤ_implicit_inits (loc, braced_init_obstack);
	      ਧੱਕੋ_init_level (loc, 2, braced_init_obstack);
	      p->ਢੇਰ = constructor_ਢੇਰ;
	      ਜੇ (p->range_ਸਿਰਾ && ਰੁੱਖ_int_cst_equal (p->ਸੂਚਕਾਂਕ, p->range_ਸਿਰਾ))
		p->ਸੂਚਕਾਂਕ = p->range_ਸ਼ੁਰੂ;
	    }

	  ਜੇ (!ਅੰਤ)
	    constructor_range_ਢੇਰ = range_ਢੇਰ;
	  ਜਾਰੀ;
	}

      ਰੋਕੋ;
    }

  constructor_range_ਢੇਰ = 0;

  ਜੇ (raw_ਅੰਕੜੇ && RAW_ਅੰਕੜੇ_ਲੰਮਾਈ (raw_ਅੰਕੜੇ))
    {
      gcc_assert (!string_flag && !was_designated);
      ਮੁੱਲ.ਮੁੱਲ = raw_ਅੰਕੜੇ;
      raw_ਅੰਕੜੇ = NULL_ਰੁੱਖ;
      ਜਾਓ retry;
    }
}

/* Build a complete asm-statement, whose components are a CV_QUALIFIER
   (guaranteed to be 'volatile' or null) and ARGS (represented using
   an ASM_EXPR node).  */
ਰੁੱਖ
build_asm_stmt (ਤਾਰਕਿਕ is_volatile, ਰੁੱਖ ਦਲੀਲਾਂ)
{
  ਜੇ (is_volatile)
    ASM_VOLATILE_P (ਦਲੀਲਾਂ) = 1;
  ਵਾਪਸ ਜੋੜੋ_stmt (ਦਲੀਲਾਂ);
}

/* Build an asm-expr, whose components are a STRING, some OUTPUTS,
   some INPUTS, and some CLOBBERS.  The latter three may be NULL.
   SIMPLE indicates whether there was anything at all after the
   string in the asm expression -- asm("blah") and asm("blah" : )
   are subtly different.  We use a ASM_EXPR node to represent this.
   LOC is the location of the asm, and IS_INLINE says whether this
   is asm inline.  */
ਰੁੱਖ
build_asm_ਵਿਅੰਜਕ (location_t loc, ਰੁੱਖ string, ਰੁੱਖ outputs, ਰੁੱਖ inputs,
		ਰੁੱਖ clobbers, ਰੁੱਖ labels, ਤਾਰਕਿਕ simple, ਤਾਰਕਿਕ is_inline)
{
  ਰੁੱਖ ਪੂਛ;
  ਰੁੱਖ ਦਲੀਲਾਂ;
  ਪੂਰਨ i;
  ਅਚਲ ਅੱਖਰ *constraint;
  ਅਚਲ ਅੱਖਰ **oconstraints;
  ਤਾਰਕਿਕ allows_mem, allows_reg, is_inout;
  ਪੂਰਨ ninputs, noutputs;

  ninputs = list_ਲੰਮਾਈ (inputs);
  noutputs = list_ਲੰਮਾਈ (outputs);
  oconstraints = (ਅਚਲ ਅੱਖਰ **) alloca (noutputs * ਆਕਾਰ (ਅਚਲ ਅੱਖਰ *));

  string = resolve_asm_ਸੰਕਾਰਜ_ਨਾਂ (string, outputs, inputs, labels);

  /* Remove output conversions that change the type but not the mode.  */
  ਲਈ (i = 0, ਪੂਛ = outputs; ਪੂਛ; ++i, ਪੂਛ = ਰੁੱਖ_CHAIN (ਪੂਛ))
    {
      ਰੁੱਖ output = ਰੁੱਖ_ਮੁੱਲ (ਪੂਛ);

      output = c_fully_fold (output, ਝੂਠ, ਨਿਰਾ, ਸੱਚ);

      /* ??? Really, this should not be here.  Users should be using a
	 proper lvalue, dammit.  But there's a long history of using casts
	 in the output operands.  In cases like longlong.h, this becomes a
	 primitive form of typechecking -- if the cast can be removed, then
	 the output operand had a type of the proper width; otherwise we'll
	 get an error.  Gross, but ...  */
      STRIP_NOPS (output);

      ਜੇ (!lvalue_or_else (loc, output, lv_asm))
	output = error_mark_ਗੰਢ;

      ਜੇ (output != error_mark_ਗੰਢ
	  && (ਰੁੱਖ_READONLY (output)
	      || TYPE_READONLY (ਰੁੱਖ_TYPE (output))
	      || (ਰਿਕਾਰਡ_OR_UNION_TYPE_P (ਰੁੱਖ_TYPE (output))
		  && C_TYPE_FIELDS_READONLY (ਰੁੱਖ_TYPE (output)))))
	readonly_error (loc, output, lv_asm);

      constraint = ਰੁੱਖ_STRING_ਸੂਚਕ (ਰੁੱਖ_ਮੁੱਲ (ਰੁੱਖ_PURPOSE (ਪੂਛ)));
      oconstraints[i] = constraint;

      ਜੇ (parse_output_constraint (&constraint, i, ninputs, noutputs,
				   &allows_mem, &allows_reg, &is_inout,
				   ਖਾਲੀ_ਸੂਚਕ))
	{
	  /* If the operand is going to end up in memory,
	     mark it addressable.  */
	  ਜੇ (!allows_reg && !c_mark_addressable (output))
	    output = error_mark_ਗੰਢ;
	  ਜੇ (!(!allows_reg && allows_mem)
	      && output != error_mark_ਗੰਢ
	      && VOID_TYPE_P (ਰੁੱਖ_TYPE (output)))
	    {
	      error_at (loc, "invalid use of void expression");
	      output = error_mark_ਗੰਢ;
	    }
	  ਜੇ (allows_reg && current_function_decl == NULL_ਰੁੱਖ)
	    {
	      error_at (loc, "constraint allows registers outside of "
			     "a function");
	      output = error_mark_ਗੰਢ;
	    }
	}
      ਨਹੀਂਤਾਂ
	output = error_mark_ਗੰਢ;

      ਜੇ (current_function_decl == NULL_ਰੁੱਖ && output != error_mark_ਗੰਢ)
	{
	  ਜੇ (ਰੁੱਖ_SIDE_EFFECTS (output))
	    {
	      error_at (loc, "side-effects in output operand outside "
			     "of a function");
	      output = error_mark_ਗੰਢ;
	    }
	  ਨਹੀਂਤਾਂ
	    {
	      ਰੁੱਖ addr = build_unary_op (loc, ADDR_ਵਿਅੰਜਕ, output, ਝੂਠ);
	      ਜੇ (addr == error_mark_ਗੰਢ)
		output = error_mark_ਗੰਢ;
	      ਨਹੀਂਤਾਂ ਜੇ (!initializer_constant_valid_p (addr, ਰੁੱਖ_TYPE (addr)))
		{
		  error_at (loc, "output operand outside of a function is not "
				 "constant");
		  output = error_mark_ਗੰਢ;
		}
	    }
	}
      ਨਹੀਂਤਾਂ ਜੇ (output != error_mark_ਗੰਢ && ਲੜੀ_ਖੋਜ (constraint, "-"))
	{
	  error_at (loc, "%<-%> modifier used inside of a function");
	  output = error_mark_ਗੰਢ;
	}

      ਰੁੱਖ_ਮੁੱਲ (ਪੂਛ) = output;
    }

  ਲਈ (i = 0, ਪੂਛ = inputs; ਪੂਛ; ++i, ਪੂਛ = ਰੁੱਖ_CHAIN (ਪੂਛ))
    {
      ਰੁੱਖ ਨਿਵੇਸ਼;

      constraint = ਰੁੱਖ_STRING_ਸੂਚਕ (ਰੁੱਖ_ਮੁੱਲ (ਰੁੱਖ_PURPOSE (ਪੂਛ)));
      ਨਿਵੇਸ਼ = ਰੁੱਖ_ਮੁੱਲ (ਪੂਛ);

      ਜੇ (parse_ਨਿਵੇਸ਼_constraint (&constraint, i, ninputs, noutputs, 0,
				  oconstraints, &allows_mem, &allows_reg,
				  ਖਾਲੀ_ਸੂਚਕ))
	{
	  /* If the operand is going to end up in memory,
	     mark it addressable.  */
	  ਜੇ (!allows_reg && allows_mem)
	    {
	      ਨਿਵੇਸ਼ = c_fully_fold (ਨਿਵੇਸ਼, ਝੂਠ, ਨਿਰਾ, ਸੱਚ);

	      /* Strip the nops as we allow this case.  FIXME, this really
		 should be rejected or made deprecated.  */
	      STRIP_NOPS (ਨਿਵੇਸ਼);
	      ਜੇ (!c_mark_addressable (ਨਿਵੇਸ਼))
		ਨਿਵੇਸ਼ = error_mark_ਗੰਢ;
	    }
	  ਨਹੀਂਤਾਂ
	    {
	      ਨਿਵੇਸ਼ = c_fully_fold (convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (loc, ਨਿਵੇਸ਼,
							      ਸੱਚ, ਝੂਠ),
				    ਝੂਠ, ਨਿਰਾ);

	      ਜੇ (ਨਿਵੇਸ਼ != error_mark_ਗੰਢ && VOID_TYPE_P (ਰੁੱਖ_TYPE (ਨਿਵੇਸ਼)))
		{
		  error_at (loc, "invalid use of void expression");
		  ਨਿਵੇਸ਼ = error_mark_ਗੰਢ;
		}
	    }
	  ਜੇ (allows_reg && current_function_decl == NULL_ਰੁੱਖ)
	    {
	      error_at (loc, "constraint allows registers outside of "
			     "a function");
	      ਨਿਵੇਸ਼ = error_mark_ਗੰਢ;
	    }
	  ਜੇ (constraint[0] == ':' && ਨਿਵੇਸ਼ != error_mark_ਗੰਢ)
	    {
	      ਰੁੱਖ t = ਨਿਵੇਸ਼;
	      STRIP_NOPS (t);
	      ਜੇ (ਰੁੱਖ_ਕੋਡ (t) != ADDR_ਵਿਅੰਜਕ
		  || !(ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_ਸੰਕਾਰਜ (t, 0)) == FUNCTION_DECL
		       || (VAR_P (ਰੁੱਖ_ਸੰਕਾਰਜ (t, 0))
			   && is_global_var (ਰੁੱਖ_ਸੰਕਾਰਜ (t, 0)))))
		{
		  error_at (loc, "%<:%> constraint operand is not address "
				 "of a function or non-automatic variable");
		  ਨਿਵੇਸ਼ = error_mark_ਗੰਢ;
		}
	      ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_ਸੰਕਾਰਜ (t, 0)) == FUNCTION_DECL)
		suppress_warning (ਰੁੱਖ_ਸੰਕਾਰਜ (t, 0), OPT_Wunused);
	    }
	}
      ਨਹੀਂਤਾਂ
	ਨਿਵੇਸ਼ = error_mark_ਗੰਢ;

      ਜੇ (current_function_decl == NULL_ਰੁੱਖ && ਨਿਵੇਸ਼ != error_mark_ਗੰਢ)
	{
	  ਜੇ (ਰੁੱਖ_SIDE_EFFECTS (ਨਿਵੇਸ਼))
	    {
	      error_at (loc, "side-effects in input operand outside "
			     "of a function");
	      ਨਿਵੇਸ਼ = error_mark_ਗੰਢ;
	    }
	  ਨਹੀਂਤਾਂ
	    {
	      ਰੁੱਖ tem = ਨਿਵੇਸ਼;
	      ਜੇ (allows_mem && lvalue_p (ਨਿਵੇਸ਼))
		tem = build_unary_op (loc, ADDR_ਵਿਅੰਜਕ, ਨਿਵੇਸ਼, ਝੂਠ);
	      ਜੇ (!initializer_constant_valid_p (tem, ਰੁੱਖ_TYPE (tem)))
		{
		  error_at (loc, "input operand outside of a function is not "
				 "constant");
		  ਨਿਵੇਸ਼ = error_mark_ਗੰਢ;
		}
	    }
	}
      ਨਹੀਂਤਾਂ ਜੇ (ਨਿਵੇਸ਼ != error_mark_ਗੰਢ && ਲੜੀ_ਖੋਜ (constraint, "-"))
	{
	  error_at (loc, "%<-%> modifier used inside of a function");
	  ਨਿਵੇਸ਼ = error_mark_ਗੰਢ;
	}

      ਰੁੱਖ_ਮੁੱਲ (ਪੂਛ) = ਨਿਵੇਸ਼;
    }

  ਦਲੀਲਾਂ = build_stmt (loc, ASM_ਵਿਅੰਜਕ, string, outputs, inputs, clobbers, labels);

  /* asm statements without outputs, including simple ones, are treated
     as volatile.  */
  ASM_BASIC_P (ਦਲੀਲਾਂ) = simple;
  ASM_VOLATILE_P (ਦਲੀਲਾਂ) = (noutputs == 0);
  ASM_INLINE_P (ਦਲੀਲਾਂ) = is_inline;

  ਵਾਪਸ ਦਲੀਲਾਂ;
}

/* Generate a goto statement to LABEL.  LOC is the location of the
   GOTO.  */

ਰੁੱਖ
c_ਅੰਤ_goto_label (location_t loc, ਰੁੱਖ label)
{
  ਰੁੱਖ decl = lookup_label_for_goto (loc, label);
  ਜੇ (!decl)
    ਵਾਪਸ NULL_ਰੁੱਖ;
  ਰੁੱਖ_ਵਰਤਿਆ (decl) = 1;
  mark_decl_ਵਰਤਿਆ (decl, ਝੂਠ);
  {
    ਜੋੜੋ_stmt (build_predict_ਵਿਅੰਜਕ (PRED_GOTO, NOT_ਲਿਆ));
    ਰੁੱਖ t = build1 (GOTO_ਵਿਅੰਜਕ, void_type_ਗੰਢ, decl);
    ਸੈੱਟ_ਵਿਅੰਜਕ_LOCATION (t, loc);
    ਵਾਪਸ ਜੋੜੋ_stmt (t);
  }
}

/* Generate a computed goto statement to EXPR.  LOC is the location of
   the GOTO.  */

ਰੁੱਖ
c_ਅੰਤ_goto_ptr (location_t loc, c_ਵਿਅੰਜਕ val)
{
  ਰੁੱਖ ਵਿਅੰਜਕ = val.ਮੁੱਲ;
  ਰੁੱਖ t;
  pedwarn (loc, OPT_Wpedantic, "ISO C forbids %<goto *expr;%>");
  ਜੇ (ਵਿਅੰਜਕ != error_mark_ਗੰਢ
      && !ਸੂਚਕ_TYPE_P (ਰੁੱਖ_TYPE (ਵਿਅੰਜਕ))
      && !null_ਸੂਚਕ_constant_p (ਵਿਅੰਜਕ))
    {
      error_at (val.get_location (),
		"computed goto must be pointer type");
      ਵਿਅੰਜਕ = build_zero_cst (ptr_type_ਗੰਢ);
    }
  ਵਿਅੰਜਕ = c_fully_fold (ਵਿਅੰਜਕ, ਝੂਠ, ਨਿਰਾ);
  ਵਿਅੰਜਕ = convert (ptr_type_ਗੰਢ, ਵਿਅੰਜਕ);
  t = build1 (GOTO_ਵਿਅੰਜਕ, void_type_ਗੰਢ, ਵਿਅੰਜਕ);
  ਸੈੱਟ_ਵਿਅੰਜਕ_LOCATION (t, loc);
  ਵਾਪਸ ਜੋੜੋ_stmt (t);
}

/* Generate a C `return' statement.  RETVAL is the expression for what
   to return, or a null pointer for `return;' with no value.  LOC is
   the location of the return statement, or the location of the expression,
   if the statement has any.  If ORIGTYPE is not NULL_TREE, it
   is the original type of RETVAL.  MUSTTAIL_P indicates a musttail
   attribute.  */

ਰੁੱਖ
c_ਅੰਤ_return (location_t loc, ਰੁੱਖ retval, ਰੁੱਖ origtype, ਤਾਰਕਿਕ musttail_p)
{
  ਰੁੱਖ valtype = ਰੁੱਖ_TYPE (ਰੁੱਖ_TYPE (current_function_decl)), ret_stmt;
  ਤਾਰਕਿਕ no_warning = ਝੂਠ;
  ਤਾਰਕਿਕ npc = ਝੂਠ;

  /* Use the expansion point to handle cases such as returning NULL
     in a function returning void.  */
  location_t xloc = expansion_ਬਿੰਦੂ_location_if_ਵਿੱਚ_system_ਸਿਰਲੇਖ (loc);

  ਜੇ (ਰੁੱਖ_THIS_VOLATILE (current_function_decl))
    warning_at (xloc, 0,
		"function declared %<noreturn%> has a %<return%> statement");

  ਸੈੱਟ_musttail_on_return (retval, xloc, musttail_p);

  ਜੇ (retval)
    {
      ਰੁੱਖ semantic_type = NULL_ਰੁੱਖ;
      npc = null_ਸੂਚਕ_constant_p (retval);
      ਜੇ (ਰੁੱਖ_ਕੋਡ (retval) == EXCESS_PRECISION_ਵਿਅੰਜਕ)
	{
	  semantic_type = ਰੁੱਖ_TYPE (retval);
	  retval = ਰੁੱਖ_ਸੰਕਾਰਜ (retval, 0);
	}
      retval = c_fully_fold (retval, ਝੂਠ, ਨਿਰਾ);
      ਜੇ (semantic_type
	  && valtype != NULL_ਰੁੱਖ
	  && ਰੁੱਖ_ਕੋਡ (valtype) != VOID_TYPE)
	retval = build1 (EXCESS_PRECISION_ਵਿਅੰਜਕ, semantic_type, retval);
    }

  ਜੇ (!retval)
    {
      current_function_returns_null = 1;
      ਜੇ ((warn_return_type >= 0 || flag_isoc99)
	  && valtype != NULL_ਰੁੱਖ && ਰੁੱਖ_ਕੋਡ (valtype) != VOID_TYPE)
	{
	  no_warning = ਸੱਚ;
	  ਜੇ (emit_diagnostic (flag_isoc99
			       ? diagnostics::ਕਿਸਮ::permerror
			       : diagnostics::ਕਿਸਮ::warning,
			       loc, OPT_Wreturn_mismatch,
			       "%<return%> with no value,"
			       " in function returning non-void"))
	    inform (DECL_ਸਰੋਤ_LOCATION (current_function_decl),
		    "declared here");
	}
    }
  ਨਹੀਂਤਾਂ ਜੇ (valtype == NULL_ਰੁੱਖ || VOID_TYPE_P (valtype))
    {
      current_function_returns_null = 1;
      ਤਾਰਕਿਕ warned_ਇੱਥੇ;
      ਜੇ (ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (retval)) != VOID_TYPE)
	warned_ਇੱਥੇ = permerror_opt
	  (xloc, OPT_Wreturn_mismatch,
	   "%<return%> with a value, in function returning void");
      ਨਹੀਂਤਾਂ
	warned_ਇੱਥੇ = pedwarn
	  (xloc, OPT_Wpedantic, "ISO C forbids "
	   "%<return%> with expression, in function returning void");
      ਜੇ (warned_ਇੱਥੇ)
	inform (DECL_ਸਰੋਤ_LOCATION (current_function_decl),
		"declared here");
    }
  ਨਹੀਂਤਾਂ
    {
      ਰੁੱਖ t = convert_for_assignment (loc, UNKNOWN_LOCATION, valtype,
				       retval, origtype, ic_return,
				       npc, NULL_ਰੁੱਖ, NULL_ਰੁੱਖ, 0);
      ਰੁੱਖ res = DECL_ਨਤੀਜਾ (current_function_decl);
      ਰੁੱਖ inner;
      ਤਾਰਕਿਕ save;

      current_function_returns_ਮੁੱਲ = 1;
      ਜੇ (t == error_mark_ਗੰਢ)
	{
	  /* Suppress -Wreturn-type for this function.  */
	  ਜੇ (warn_return_type)
	    suppress_warning (current_function_decl, OPT_Wreturn_type);
	  ਵਾਪਸ NULL_ਰੁੱਖ;
	}

      save = ਵਿੱਚ_late_ਦੁਆਧਾਰੀ_op;
      ਜੇ (C_BOOLEAN_TYPE_P (ਰੁੱਖ_TYPE (res))
	  || ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (res)) == COMPLEX_TYPE
	  || (SCALAR_FLOAT_TYPE_P (ਰੁੱਖ_TYPE (t))
	      && (ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (res)) == INTEGER_TYPE
		  || ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (res)) == ENUMERAL_TYPE)
	      && sanitize_flags_p (SANITIZE_FLOAT_CAST)))
        ਵਿੱਚ_late_ਦੁਆਧਾਰੀ_op = ਸੱਚ;
      inner = t = convert (ਰੁੱਖ_TYPE (res), t);
      ਵਿੱਚ_late_ਦੁਆਧਾਰੀ_op = save;

      /* Strip any conversions, additions, and subtractions, and see if
	 we are returning the address of a local variable.  Warn if so.  */
      ਜਦੋਂ (1)
	{
	  ਚੋਣ (ਰੁੱਖ_ਕੋਡ (inner))
	    {
	    CASE_CONVERT:
	    ਹਾਲਤ NON_LVALUE_ਵਿਅੰਜਕ:
	    ਹਾਲਤ PLUS_ਵਿਅੰਜਕ:
	    ਹਾਲਤ ਸੂਚਕ_PLUS_ਵਿਅੰਜਕ:
	      inner = ਰੁੱਖ_ਸੰਕਾਰਜ (inner, 0);
	      ਜਾਰੀ;

	    ਹਾਲਤ MINUS_ਵਿਅੰਜਕ:
	      /* If the second operand of the MINUS_EXPR has a pointer
		 type (or is converted from it), this may be valid, so
		 don't give a warning.  */
	      {
		ਰੁੱਖ op1 = ਰੁੱਖ_ਸੰਕਾਰਜ (inner, 1);

		ਜਦੋਂ (!ਸੂਚਕ_TYPE_P (ਰੁੱਖ_TYPE (op1))
		       && (CONVERT_ਵਿਅੰਜਕ_P (op1)
			   || ਰੁੱਖ_ਕੋਡ (op1) == NON_LVALUE_ਵਿਅੰਜਕ))
		  op1 = ਰੁੱਖ_ਸੰਕਾਰਜ (op1, 0);

		ਜੇ (ਸੂਚਕ_TYPE_P (ਰੁੱਖ_TYPE (op1)))
		  ਰੋਕੋ;

		inner = ਰੁੱਖ_ਸੰਕਾਰਜ (inner, 0);
		ਜਾਰੀ;
	      }

	    ਹਾਲਤ ADDR_ਵਿਅੰਜਕ:
	      inner = ਰੁੱਖ_ਸੰਕਾਰਜ (inner, 0);

	      ਜਦੋਂ (REFERENCE_CLASS_P (inner)
		     && !ਅਸਿੱਧਾ_REF_P (inner))
		inner = ਰੁੱਖ_ਸੰਕਾਰਜ (inner, 0);

	      ਜੇ (DECL_P (inner)
		  && !DECL_EXTERNAL (inner)
		  && DECL_CONTEXT (inner) == current_function_decl
		  && ਸੂਚਕ_TYPE_P (ਰੁੱਖ_TYPE (ਰੁੱਖ_TYPE (current_function_decl))))
		{
		  ਜੇ (ਰੁੱਖ_ਕੋਡ (inner) == LABEL_DECL)
		    warning_at (loc, OPT_Wreturn_local_addr,
				"function returns address of label");
		  ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਕੋਡ (inner) == FUNCTION_DECL
			   && (C_FUNC_NONLOCAL_CONTEXT (inner)
			       || !DECL_INITIAL (inner)))
		    warning_at (loc, OPT_Wreturn_local_addr,
				"function returns address of nested function "
				"referencing local context");
		  ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਕੋਡ (inner) != FUNCTION_DECL
			   && !ਰੁੱਖ_STATIC (inner))
		    {
		      warning_at (loc, OPT_Wreturn_local_addr,
				  "function returns address of local variable");
		      ਰੁੱਖ zero = build_zero_cst (ਰੁੱਖ_TYPE (res));
		      t = build2 (COMPOUND_ਵਿਅੰਜਕ, ਰੁੱਖ_TYPE (res), t, zero);
		    }
		}
	      ਰੋਕੋ;

	    ਮੂਲ:
	      ਰੋਕੋ;
	    }

	  ਰੋਕੋ;
	}

      retval = build2 (MODIFY_ਵਿਅੰਜਕ, ਰੁੱਖ_TYPE (res), res, t);
      ਸੈੱਟ_ਵਿਅੰਜਕ_LOCATION (retval, loc);

      ਜੇ (warn_sequence_ਬਿੰਦੂ)
	verify_sequence_points (retval);
    }

  ret_stmt = build_stmt (loc, RETURN_ਵਿਅੰਜਕ, retval);
  ਜੇ (no_warning)
    suppress_warning (ret_stmt, OPT_Wreturn_type);
  ਵਾਪਸ ਜੋੜੋ_stmt (ret_stmt);
}

ਬਣਤਰ c_switch {
  /* The SWITCH_STMT being built.  */
  ਰੁੱਖ switch_stmt;

  /* The original type of the testing expression, i.e. before the
     default conversion is applied.  */
  ਰੁੱਖ orig_type;

  /* A splay-tree mapping the low element of a case range to the high
     element, or NULL_TREE if there is no high element.  Used to
     determine whether or not a new case label duplicates an old case
     label.  We need a tree, rather than simply a hash table, because
     of the GNU case range extension.  */
  splay_ਰੁੱਖ cases;

  /* The bindings at the point of the switch.  This is used for
     warnings crossing decls when branching to a case label.  */
  ਬਣਤਰ c_spot_bindings *bindings;

  /* Whether the switch includes any break statements.  */
  ਤਾਰਕਿਕ break_stmt_ਵੇਖਿਆ_p;

  /* The next node on the stack.  */
  ਬਣਤਰ c_switch *ਅਗਲਾ;

  /* Remember whether the controlling expression had boolean type
     before integer promotions for the sake of -Wswitch-bool.  */
  ਤਾਰਕਿਕ bool_cond_p;
};

/* A stack of the currently active switch statements.  The innermost
   switch statement is on the top of the stack.  There is no need to
   mark the stack for garbage collection because it is only active
   during the processing of the body of a function, and we never
   collect at that point.  */

ਬਣਤਰ c_switch *c_switch_ਢੇਰ;

/* Start a C switch statement, testing expression EXP.  Return the new
   SWITCH_STMT.  SWITCH_LOC is the location of the `switch'.
   SWITCH_COND_LOC is the location of the switch's condition.
   EXPLICIT_CAST_P is true if the expression EXP has an explicit cast.  */

ਰੁੱਖ
c_ਸ਼ੁਰੂ_switch (location_t switch_loc,
		location_t switch_cond_loc,
		ਰੁੱਖ ਘਾਤਾਂਕ, ਤਾਰਕਿਕ explicit_cast_p, ਰੁੱਖ switch_name)
{
  ਰੁੱਖ orig_type = error_mark_ਗੰਢ;
  ਤਾਰਕਿਕ bool_cond_p = ਝੂਠ;
  ਬਣਤਰ c_switch *cs;

  ਜੇ (ਘਾਤਾਂਕ != error_mark_ਗੰਢ)
    {
      orig_type = ਰੁੱਖ_TYPE (ਘਾਤਾਂਕ);

      ਜੇ (!INTEGRAL_TYPE_P (orig_type))
	{
	  ਜੇ (orig_type != error_mark_ਗੰਢ)
	    {
	      error_at (switch_cond_loc, "switch quantity not an integer");
	      orig_type = error_mark_ਗੰਢ;
	    }
	  ਘਾਤਾਂਕ = integer_zero_ਗੰਢ;
	}
      ਨਹੀਂਤਾਂ
	{
	  ਰੁੱਖ type = TYPE_MAIN_VARIANT (orig_type);
	  ਰੁੱਖ e = ਘਾਤਾਂਕ;

	  /* Warn if the condition has boolean value.  */
	  ਜਦੋਂ (ਰੁੱਖ_ਕੋਡ (e) == COMPOUND_ਵਿਅੰਜਕ)
	    e = ਰੁੱਖ_ਸੰਕਾਰਜ (e, 1);

	  ਜੇ ((C_BOOLEAN_TYPE_P (type)
	       || truth_ਮੁੱਲ_p (ਰੁੱਖ_ਕੋਡ (e)))
	      /* Explicit cast to int suppresses this warning.  */
	      && !(ਰੁੱਖ_ਕੋਡ (type) == INTEGER_TYPE
		   && explicit_cast_p))
	    bool_cond_p = ਸੱਚ;

	  ਜੇ (!ਵਿੱਚ_system_ਸਿਰਲੇਖ_at (ਨਿਵੇਸ਼_location)
	      && (type == long_integer_type_ਗੰਢ
		  || type == long_unsigned_type_ਗੰਢ))
	    warning_at (switch_cond_loc,
			OPT_Wtraditional, "%<long%> switch expression not "
			"converted to %<int%> in ISO C");

	  ਘਾਤਾਂਕ = c_fully_fold (ਘਾਤਾਂਕ, ਝੂਠ, ਨਿਰਾ);
	  ਘਾਤਾਂਕ = default_conversion (ਘਾਤਾਂਕ);

	  ਜੇ (warn_sequence_ਬਿੰਦੂ)
	    verify_sequence_points (ਘਾਤਾਂਕ);
	}
    }

  /* Add this new SWITCH_STMT to the stack.  */
  cs = XNEW (ਬਣਤਰ c_switch);
  cs->switch_stmt = build_stmt (switch_loc, SWITCH_STMT, ਘਾਤਾਂਕ,
				NULL_ਰੁੱਖ, orig_type, NULL_ਰੁੱਖ, switch_name);
  cs->orig_type = orig_type;
  cs->cases = splay_ਰੁੱਖ_new (case_compare, ਨਿਰਾ, ਨਿਰਾ);
  cs->bindings = c_get_switch_bindings ();
  cs->break_stmt_ਵੇਖਿਆ_p = ਝੂਠ;
  cs->bool_cond_p = bool_cond_p;
  cs->ਅਗਲਾ = c_switch_ਢੇਰ;
  c_switch_ਢੇਰ = cs;

  ਵਾਪਸ ਜੋੜੋ_stmt (cs->switch_stmt);
}

/* Process a case label at location LOC, with attributes ATTRS.  */

ਰੁੱਖ
do_case (location_t loc, ਰੁੱਖ ਨੀਵਾਂ_ਮੁੱਲ, ਰੁੱਖ ਉੱਚਾ_ਮੁੱਲ, ਰੁੱਖ attrs)
{
  ਰੁੱਖ label = NULL_ਰੁੱਖ;

  ਜੇ (ਨੀਵਾਂ_ਮੁੱਲ && ਰੁੱਖ_ਕੋਡ (ਨੀਵਾਂ_ਮੁੱਲ) != INTEGER_CST)
    {
      ਨੀਵਾਂ_ਮੁੱਲ = c_fully_fold (ਨੀਵਾਂ_ਮੁੱਲ, ਝੂਠ, ਨਿਰਾ);
      ਜੇ (ਰੁੱਖ_ਕੋਡ (ਨੀਵਾਂ_ਮੁੱਲ) == INTEGER_CST)
	pedwarn (loc, OPT_Wpedantic,
		 "case label is not an integer constant expression");
    }

  ਜੇ (ਉੱਚਾ_ਮੁੱਲ && ਰੁੱਖ_ਕੋਡ (ਉੱਚਾ_ਮੁੱਲ) != INTEGER_CST)
    {
      ਉੱਚਾ_ਮੁੱਲ = c_fully_fold (ਉੱਚਾ_ਮੁੱਲ, ਝੂਠ, ਨਿਰਾ);
      ਜੇ (ਰੁੱਖ_ਕੋਡ (ਉੱਚਾ_ਮੁੱਲ) == INTEGER_CST)
	pedwarn (ਨਿਵੇਸ਼_location, OPT_Wpedantic,
		 "case label is not an integer constant expression");
    }

  ਜੇ (c_switch_ਢੇਰ == ਨਿਰਾ)
    {
      ਜੇ (ਨੀਵਾਂ_ਮੁੱਲ)
	error_at (loc, "case label not within a switch statement");
      ਨਹੀਂਤਾਂ
	error_at (loc, "%<default%> label not within a switch statement");
      ਵਾਪਸ NULL_ਰੁੱਖ;
    }

  ਜੇ (c_check_switch_jump_warnings (c_switch_ਢੇਰ->bindings,
				    ਵਿਅੰਜਕ_LOCATION (c_switch_ਢੇਰ->switch_stmt),
				    loc))
    ਵਾਪਸ NULL_ਰੁੱਖ;

  label = c_ਜੋੜੋ_case_label (loc, c_switch_ਢੇਰ->cases,
			    SWITCH_STMT_COND (c_switch_ਢੇਰ->switch_stmt),
			    ਨੀਵਾਂ_ਮੁੱਲ, ਉੱਚਾ_ਮੁੱਲ, attrs);
  ਜੇ (label == error_mark_ਗੰਢ)
    label = NULL_ਰੁੱਖ;
  ਵਾਪਸ label;
}

/* Finish the switch statement.  TYPE is the original type of the
   controlling expression of the switch, or NULL_TREE.  */

ਖਾਲੀ
c_ਅੰਤ_switch (ਰੁੱਖ body, ਰੁੱਖ type)
{
  ਬਣਤਰ c_switch *cs = c_switch_ਢੇਰ;
  location_t switch_location;

  SWITCH_STMT_BODY (cs->switch_stmt) = body;

  /* Emit warnings as needed.  */
  switch_location = ਵਿਅੰਜਕ_LOCATION (cs->switch_stmt);
  c_do_switch_warnings (cs->cases, switch_location,
			type ? type : SWITCH_STMT_TYPE (cs->switch_stmt),
			SWITCH_STMT_COND (cs->switch_stmt), cs->bool_cond_p);
  ਜੇ (c_switch_covers_all_cases_p (cs->cases,
				   SWITCH_STMT_TYPE (cs->switch_stmt)))
    SWITCH_STMT_ALL_CASES_P (cs->switch_stmt) = 1;
  SWITCH_STMT_NO_BREAK_P (cs->switch_stmt) = !cs->break_stmt_ਵੇਖਿਆ_p;

  /* Pop the stack.  */
  c_switch_ਢੇਰ = cs->ਅਗਲਾ;
  splay_ਰੁੱਖ_delete (cs->cases);
  c_release_switch_bindings (cs->bindings);
  XDELETE (cs);
}

/* Emit an if statement.  IF_LOCUS is the location of the 'if'.  COND,
   THEN_BLOCK and ELSE_BLOCK are expressions to be used; ELSE_BLOCK
   may be null.  */

ਖਾਲੀ
c_ਅੰਤ_if_stmt (location_t if_locus, ਰੁੱਖ cond, ਰੁੱਖ then_ਖੰਡ,
		  ਰੁੱਖ else_ਖੰਡ)
{
  ਰੁੱਖ stmt;

  stmt = build3 (COND_ਵਿਅੰਜਕ, void_type_ਗੰਢ, cond, then_ਖੰਡ, else_ਖੰਡ);
  ਸੈੱਟ_ਵਿਅੰਜਕ_LOCATION (stmt, if_locus);
  ਜੋੜੋ_stmt (stmt);
}

ਰੁੱਖ
c_ਅੰਤ_bc_stmt (location_t loc, ਰੁੱਖ label, ਤਾਰਕਿਕ is_break, ਰੁੱਖ name)
{
  /* In switch statements break is sometimes stylistically used after
     a return statement.  This can lead to spurious warnings about
     control reaching the end of a non-void function when it is
     inlined.  Note that we are calling block_may_fallthru with
     language specific tree nodes; this works because
     block_may_fallthru returns true when given something it does not
     understand.  */
  ਤਾਰਕਿਕ skip = !ਖੰਡ_may_fallthru (cur_stmt_list);

  ਜੇ (is_break)
    ਚੋਣ (ਵਿੱਚ_statement & ~ਵਿੱਚ_NAMED_STMT)
      {
      ਹਾਲਤ 0:
	error_at (loc, "break statement not within loop or switch");
	ਵਾਪਸ NULL_ਰੁੱਖ;
      ਹਾਲਤ ਵਿੱਚ_OMP_ਖੰਡ:
	error_at (loc, "invalid exit from OpenMP structured block");
	ਵਾਪਸ NULL_ਰੁੱਖ;
      ਹਾਲਤ ਵਿੱਚ_OMP_FOR:
	error_at (loc, "break statement used with OpenMP for loop");
	ਵਾਪਸ NULL_ਰੁੱਖ;
      ਹਾਲਤ ਵਿੱਚ_ITERATION_STMT:
      ਹਾਲਤ ਵਿੱਚ_OBJC_FOREACH:
	ਰੋਕੋ;
      ਮੂਲ:
	gcc_assert (ਵਿੱਚ_statement & ਵਿੱਚ_SWITCH_STMT);
	c_switch_ਢੇਰ->break_stmt_ਵੇਖਿਆ_p = ਸੱਚ;
	ਰੋਕੋ;
      }
  ਨਹੀਂਤਾਂ
    ਚੋਣ (ਵਿੱਚ_statement & ~(ਵਿੱਚ_SWITCH_STMT | ਵਿੱਚ_NAMED_STMT))
      {
      ਹਾਲਤ 0:
	error_at (loc, "continue statement not within a loop");
	ਵਾਪਸ NULL_ਰੁੱਖ;
      ਹਾਲਤ ਵਿੱਚ_OMP_ਖੰਡ:
	error_at (loc, "invalid exit from OpenMP structured block");
	ਵਾਪਸ NULL_ਰੁੱਖ;
      ਹਾਲਤ ਵਿੱਚ_ITERATION_STMT:
      ਹਾਲਤ ਵਿੱਚ_OMP_FOR:
      ਹਾਲਤ ਵਿੱਚ_OBJC_FOREACH:
	ਰੋਕੋ;
      ਮੂਲ:
	gcc_unreachable ();
      }

  ਜੇ (skip)
    ਵਾਪਸ NULL_ਰੁੱਖ;
  ਨਹੀਂਤਾਂ ਜੇ ((ਵਿੱਚ_statement & ਵਿੱਚ_OBJC_FOREACH)
	   && !(is_break && (ਵਿੱਚ_statement & ਵਿੱਚ_SWITCH_STMT))
	   && name == NULL_ਰੁੱਖ)
    {
      /* The foreach expander produces low-level code using gotos instead
	 of a structured loop construct.  */
      gcc_assert (label);
      ਵਾਪਸ ਜੋੜੋ_stmt (build_stmt (loc, GOTO_ਵਿਅੰਜਕ, label));
    }
  ਨਹੀਂਤਾਂ ਜੇ (name && C_DECL_LOOP_NAME (name) && C_DECL_SWITCH_NAME (name))
    {
      label = DECL_CHAIN (name);
      ਜੇ (!is_break)
	label = DECL_CHAIN (label);
      /* Foreach expander from some outer level.  */
      ਵਾਪਸ ਜੋੜੋ_stmt (build_stmt (loc, GOTO_ਵਿਅੰਜਕ, label));
    }
  ਵਾਪਸ ਜੋੜੋ_stmt (build_stmt (loc, is_break ? BREAK_STMT : CONTINUE_STMT,
			       name));
}

/* A helper routine for c_process_expr_stmt and c_finish_stmt_expr.  */

ਸਥਿਰ ਖਾਲੀ
emit_side_effect_warnings (location_t loc, ਰੁੱਖ ਵਿਅੰਜਕ)
{
  maybe_warn_nodiscard (loc, ਵਿਅੰਜਕ);
  ਜੇ (!warn_ਅਣਵਰਤਿਆ_ਮੁੱਲ)
    ਵਾਪਸ;
  ਜੇ (ਵਿਅੰਜਕ == error_mark_ਗੰਢ)
    ;
  ਨਹੀਂਤਾਂ ਜੇ (!ਰੁੱਖ_SIDE_EFFECTS (ਵਿਅੰਜਕ))
    {
      ਜੇ (!VOID_TYPE_P (ਰੁੱਖ_TYPE (ਵਿਅੰਜਕ))
	  && !warning_suppressed_p (ਵਿਅੰਜਕ, OPT_Wunused_ਮੁੱਲ))
	warning_at (loc, OPT_Wunused_ਮੁੱਲ, "statement with no effect");
    }
  ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਕੋਡ (ਵਿਅੰਜਕ) == COMPOUND_ਵਿਅੰਜਕ)
    {
      ਰੁੱਖ r = ਵਿਅੰਜਕ;
      location_t cloc = loc;
      ਜਦੋਂ (ਰੁੱਖ_ਕੋਡ (r) == COMPOUND_ਵਿਅੰਜਕ)
	{
	  ਜੇ (ਵਿਅੰਜਕ_HAS_LOCATION (r))
	    cloc = ਵਿਅੰਜਕ_LOCATION (r);
	  r = ਰੁੱਖ_ਸੰਕਾਰਜ (r, 1);
	}
      ਜੇ (!ਰੁੱਖ_SIDE_EFFECTS (r)
	  && !VOID_TYPE_P (ਰੁੱਖ_TYPE (r))
	  && !CONVERT_ਵਿਅੰਜਕ_P (r)
	  && !warning_suppressed_p (r, OPT_Wunused_ਮੁੱਲ)
	  && !warning_suppressed_p (ਵਿਅੰਜਕ, OPT_Wunused_ਮੁੱਲ))
	warning_at (cloc, OPT_Wunused_ਮੁੱਲ,
		    "right-hand operand of comma expression has no effect");
    }
  ਨਹੀਂਤਾਂ
    warn_if_ਅਣਵਰਤਿਆ_ਮੁੱਲ (ਵਿਅੰਜਕ, loc);
}

/* Process an expression as if it were a complete statement.  Emit
   diagnostics, but do not call ADD_STMT.  LOC is the location of the
   statement.  */

ਰੁੱਖ
c_process_ਵਿਅੰਜਕ_stmt (location_t loc, ਰੁੱਖ ਵਿਅੰਜਕ)
{
  ਰੁੱਖ exprv;

  ਜੇ (!ਵਿਅੰਜਕ)
    ਵਾਪਸ NULL_ਰੁੱਖ;

  ਵਿਅੰਜਕ = c_fully_fold (ਵਿਅੰਜਕ, ਝੂਠ, ਨਿਰਾ);

  ਜੇ (warn_sequence_ਬਿੰਦੂ)
    verify_sequence_points (ਵਿਅੰਜਕ);

  ਜੇ (ਰੁੱਖ_TYPE (ਵਿਅੰਜਕ) != error_mark_ਗੰਢ
      && !COMPLETE_OR_VOID_TYPE_P (ਰੁੱਖ_TYPE (ਵਿਅੰਜਕ))
      && ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (ਵਿਅੰਜਕ)) != ARRAY_TYPE)
    error_at (loc, "expression statement has incomplete type");

  /* If we're not processing a statement expression, warn about unused values.
     Warnings for statement expressions will be emitted later, once we figure
     out which is the result.  */
  ਜੇ (!STATEMENT_LIST_STMT_ਵਿਅੰਜਕ (cur_stmt_list)
      && (warn_ਅਣਵਰਤਿਆ_ਮੁੱਲ || warn_ਅਣਵਰਤਿਆ_ਨਤੀਜਾ))
    emit_side_effect_warnings (ਵਿਅੰਜਕ_LOC_OR_LOC (ਵਿਅੰਜਕ, loc), ਵਿਅੰਜਕ);

  exprv = ਵਿਅੰਜਕ;
  ਜਦੋਂ (ਰੁੱਖ_ਕੋਡ (exprv) == COMPOUND_ਵਿਅੰਜਕ)
    exprv = ਰੁੱਖ_ਸੰਕਾਰਜ (exprv, 1);
  ਜਦੋਂ (CONVERT_ਵਿਅੰਜਕ_P (exprv))
    exprv = ਰੁੱਖ_ਸੰਕਾਰਜ (exprv, 0);
  ਜੇ (DECL_P (exprv)
      || handled_component_p (exprv)
      || ਰੁੱਖ_ਕੋਡ (exprv) == ADDR_ਵਿਅੰਜਕ)
    mark_exp_read (exprv);

  /* If the expression is not of a type to which we cannot assign a line
     number, wrap the thing in a no-op NOP_EXPR.  */
  ਜੇ (DECL_P (ਵਿਅੰਜਕ) || CONSTANT_CLASS_P (ਵਿਅੰਜਕ))
    {
      ਵਿਅੰਜਕ = build1 (NOP_ਵਿਅੰਜਕ, ਰੁੱਖ_TYPE (ਵਿਅੰਜਕ), ਵਿਅੰਜਕ);
      ਸੈੱਟ_ਵਿਅੰਜਕ_LOCATION (ਵਿਅੰਜਕ, loc);
    }

  ਵਾਪਸ ਵਿਅੰਜਕ;
}

/* Emit an expression as a statement.  LOC is the location of the
   expression.  */

ਰੁੱਖ
c_ਅੰਤ_ਵਿਅੰਜਕ_stmt (location_t loc, ਰੁੱਖ ਵਿਅੰਜਕ)
{
  ਜੇ (ਵਿਅੰਜਕ)
    ਵਾਪਸ ਜੋੜੋ_stmt (c_process_ਵਿਅੰਜਕ_stmt (loc, ਵਿਅੰਜਕ));
  ਨਹੀਂਤਾਂ
    ਵਾਪਸ ਨਿਰਾ;
}

/* Do the opposite and emit a statement as an expression.  To begin,
   create a new binding level and return it.  */

ਰੁੱਖ
c_begin_stmt_ਵਿਅੰਜਕ (ਖਾਲੀ)
{
  ਰੁੱਖ ret;

  /* We must force a BLOCK for this level so that, if it is not expanded
     later, there is a way to turn off the entire subtree of blocks that
     are contained in it.  */
  keep_ਅਗਲਾ_level ();
  ret = c_begin_compound_stmt (ਸੱਚ);

  c_bindings_ਸ਼ੁਰੂ_stmt_ਵਿਅੰਜਕ (c_switch_ਢੇਰ == ਨਿਰਾ
			      ? ਨਿਰਾ
			      : c_switch_ਢੇਰ->bindings);

  /* Mark the current statement list as belonging to a statement list.  */
  STATEMENT_LIST_STMT_ਵਿਅੰਜਕ (ret) = 1;

  ਵਾਪਸ ret;
}

/* LOC is the location of the compound statement to which this body
   belongs.  */

ਰੁੱਖ
c_ਅੰਤ_stmt_ਵਿਅੰਜਕ (location_t loc, ਰੁੱਖ body)
{
  ਰੁੱਖ ਆਖਰੀ, type, tmp, val;
  ਰੁੱਖ *ਆਖਰੀ_p;

  body = c_ਸਿਰਾ_compound_stmt (loc, body, ਸੱਚ);

  c_bindings_ਸਿਰਾ_stmt_ਵਿਅੰਜਕ (c_switch_ਢੇਰ == ਨਿਰਾ
			    ? ਨਿਰਾ
			    : c_switch_ਢੇਰ->bindings);

  /* Locate the last statement in BODY.  See c_end_compound_stmt
     about always returning a BIND_EXPR.  */
  ਆਖਰੀ_p = &BIND_ਵਿਅੰਜਕ_BODY (body);
  ਆਖਰੀ = BIND_ਵਿਅੰਜਕ_BODY (body);

 continue_searching:
  ਜੇ (ਰੁੱਖ_ਕੋਡ (ਆਖਰੀ) == STATEMENT_LIST)
    {
      ਰੁੱਖ_stmt_iterator l = tsi_ਆਖਰੀ (ਆਖਰੀ);

      ਜਦੋਂ (!tsi_ਸਿਰਾ_p (l) && ਰੁੱਖ_ਕੋਡ (tsi_stmt (l)) == DEBUG_BEGIN_STMT)
	tsi_prev (&l);

      /* This can happen with degenerate cases like ({ }).  No value.  */
      ਜੇ (tsi_ਸਿਰਾ_p (l))
	ਵਾਪਸ body;

      /* If we're supposed to generate side effects warnings, process
	 all of the statements except the last.  */
      ਜੇ (warn_ਅਣਵਰਤਿਆ_ਮੁੱਲ || warn_ਅਣਵਰਤਿਆ_ਨਤੀਜਾ)
	{
	  ਲਈ (ਰੁੱਖ_stmt_iterator i = tsi_ਸ਼ੁਰੂ (ਆਖਰੀ);
	       tsi_stmt (i) != tsi_stmt (l); tsi_ਅਗਲਾ (&i))
	    {
	      location_t tloc;
	      ਰੁੱਖ t = tsi_stmt (i);

	      tloc = ਵਿਅੰਜਕ_HAS_LOCATION (t) ? ਵਿਅੰਜਕ_LOCATION (t) : loc;
	      emit_side_effect_warnings (tloc, t);
	    }
	}
      ਆਖਰੀ_p = tsi_stmt_ptr (l);
      ਆਖਰੀ = *ਆਖਰੀ_p;
    }

  /* If the end of the list is exception related, then the list was split
     by a call to push_cleanup.  Continue searching.  */
  ਜੇ (ਰੁੱਖ_ਕੋਡ (ਆਖਰੀ) == TRY_FINALLY_ਵਿਅੰਜਕ
      || ਰੁੱਖ_ਕੋਡ (ਆਖਰੀ) == TRY_CATCH_ਵਿਅੰਜਕ)
    {
      ਆਖਰੀ_p = &ਰੁੱਖ_ਸੰਕਾਰਜ (ਆਖਰੀ, 0);
      ਆਖਰੀ = *ਆਖਰੀ_p;
      ਜਾਓ continue_searching;
    }

  ਜੇ (ਆਖਰੀ == error_mark_ਗੰਢ)
    ਵਾਪਸ ਆਖਰੀ;

  /* In the case that the BIND_EXPR is not necessary, return the
     expression out from inside it.  */
  ਜੇ ((ਆਖਰੀ == BIND_ਵਿਅੰਜਕ_BODY (body)
       /* Skip nested debug stmts.  */
       || ਆਖਰੀ == ਵਿਅੰਜਕ_ਪਹਿਲਾ (BIND_ਵਿਅੰਜਕ_BODY (body)))
      && BIND_ਵਿਅੰਜਕ_VARS (body) == ਨਿਰਾ)
    {
      /* Even if this looks constant, do not allow it in a constant
	 expression.  */
      ਆਖਰੀ = c_wrap_maybe_const (ਆਖਰੀ, ਸੱਚ);
      /* Do not warn if the return value of a statement expression is
	 unused.  */
      suppress_warning (ਆਖਰੀ, OPT_Wunused);
      ਵਾਪਸ ਆਖਰੀ;
    }

  /* Extract the type of said expression.  */
  type = ਰੁੱਖ_TYPE (ਆਖਰੀ);

  /* If we're not returning a value at all, then the BIND_EXPR that
     we already have is a fine expression to return.  */
  ਜੇ (!type || VOID_TYPE_P (type))
    ਵਾਪਸ body;

  /* Now that we've located the expression containing the value, it seems
     silly to make voidify_wrapper_expr repeat the process.  Create a
     temporary of the appropriate type and stick it in a TARGET_EXPR.  */
  tmp = create_tmp_var_raw (type);

  /* Unwrap a no-op NOP_EXPR as added by c_finish_expr_stmt.  This avoids
     tree_expr_nonnegative_p giving up immediately.  */
  val = ਆਖਰੀ;
  ਜੇ (ਰੁੱਖ_ਕੋਡ (val) == NOP_ਵਿਅੰਜਕ
      && ਰੁੱਖ_TYPE (val) == ਰੁੱਖ_TYPE (ਰੁੱਖ_ਸੰਕਾਰਜ (val, 0)))
    val = ਰੁੱਖ_ਸੰਕਾਰਜ (val, 0);

  *ਆਖਰੀ_p = build2 (MODIFY_ਵਿਅੰਜਕ, void_type_ਗੰਢ, tmp, val);
  ਸੈੱਟ_ਵਿਅੰਜਕ_LOCATION (*ਆਖਰੀ_p, ਵਿਅੰਜਕ_LOCATION (ਆਖਰੀ));

  {
    ਰੁੱਖ t = build4 (ਨਿਸ਼ਾਨਾ_ਵਿਅੰਜਕ, type, tmp, body, NULL_ਰੁੱਖ, NULL_ਰੁੱਖ);
    ਸੈੱਟ_ਵਿਅੰਜਕ_LOCATION (t, loc);
    ਵਾਪਸ t;
  }
}

/* Begin and end compound statements.  This is as simple as pushing
   and popping new statement lists from the tree.  */

ਰੁੱਖ
c_begin_compound_stmt (ਤਾਰਕਿਕ do_scope)
{
  ਰੁੱਖ stmt = ਧੱਕੋ_stmt_list ();
  ਜੇ (do_scope)
    ਧੱਕੋ_scope ();
  ਵਾਪਸ stmt;
}

/* End a compound statement.  STMT is the statement.  LOC is the
   location of the compound statement-- this is usually the location
   of the opening brace.  */

ਰੁੱਖ
c_ਸਿਰਾ_compound_stmt (location_t loc, ਰੁੱਖ stmt, ਤਾਰਕਿਕ do_scope)
{
  ਰੁੱਖ ਖੰਡ = ਨਿਰਾ;

  ਜੇ (do_scope)
    {
      ਜੇ (c_dialect_objc ())
	objc_clear_super_receiver ();
      ਖੰਡ = ਕੱਢੋ_scope ();
    }

  stmt = ਕੱਢੋ_stmt_list (stmt);
  stmt = c_build_bind_ਵਿਅੰਜਕ (loc, ਖੰਡ, stmt);

  /* If this compound statement is nested immediately inside a statement
     expression, then force a BIND_EXPR to be created.  Otherwise we'll
     do the wrong thing for ({ { 1; } }) or ({ 1; { } }).  In particular,
     STATEMENT_LISTs merge, and thus we can lose track of what statement
     was really last.  */
  ਜੇ (building_stmt_list_p ()
      && STATEMENT_LIST_STMT_ਵਿਅੰਜਕ (cur_stmt_list)
      && ਰੁੱਖ_ਕੋਡ (stmt) != BIND_ਵਿਅੰਜਕ)
    {
      stmt = build3 (BIND_ਵਿਅੰਜਕ, void_type_ਗੰਢ, ਨਿਰਾ, stmt, ਨਿਰਾ);
      ਰੁੱਖ_SIDE_EFFECTS (stmt) = 1;
      ਸੈੱਟ_ਵਿਅੰਜਕ_LOCATION (stmt, loc);
    }

  ਵਾਪਸ stmt;
}

/* Queue a cleanup.  CLEANUP is an expression/statement to be executed
   when the current scope is exited.  EH_ONLY is true when this is not
   meant to apply to normal control flow transfer.  */

ਖਾਲੀ
ਧੱਕੋ_cleanup (ਰੁੱਖ decl, ਰੁੱਖ cleanup, ਤਾਰਕਿਕ eh_only)
{
  ਗਿਣਤੀ ਰੁੱਖ_ਕੋਡ_2 ਕੋਡ;
  ਰੁੱਖ stmt, list;
  ਤਾਰਕਿਕ stmt_ਵਿਅੰਜਕ;

  ਕੋਡ = eh_only ? TRY_CATCH_ਵਿਅੰਜਕ : TRY_FINALLY_ਵਿਅੰਜਕ;
  stmt = build_stmt (DECL_ਸਰੋਤ_LOCATION (decl), ਕੋਡ, ਨਿਰਾ, cleanup);
  ਜੋੜੋ_stmt (stmt);
  stmt_ਵਿਅੰਜਕ = STATEMENT_LIST_STMT_ਵਿਅੰਜਕ (cur_stmt_list);
  list = ਧੱਕੋ_stmt_list ();
  ਰੁੱਖ_ਸੰਕਾਰਜ (stmt, 0) = list;
  STATEMENT_LIST_STMT_ਵਿਅੰਜਕ (list) = stmt_ਵਿਅੰਜਕ;
}

/* Build a vector comparison of ARG0 and ARG1 using CODE opcode
   into a value of TYPE type.  Comparison is done via VEC_COND_EXPR.  */

ਸਥਿਰ ਰੁੱਖ
build_vec_cmp (ਰੁੱਖ_ਕੋਡ_2 ਕੋਡ, ਰੁੱਖ type,
	       ਰੁੱਖ arg0, ਰੁੱਖ arg1)
{
  ਰੁੱਖ zero_vec = build_zero_cst (type);
  ਰੁੱਖ minus_one_vec = build_minus_one_cst (type);
  ਰੁੱਖ cmp_type = truth_type_for (ਰੁੱਖ_TYPE (arg0));
  ਰੁੱਖ cmp = build2 (ਕੋਡ, cmp_type, arg0, arg1);
  ਵਾਪਸ build3 (VEC_COND_ਵਿਅੰਜਕ, type, cmp, minus_one_vec, zero_vec);
}

/* Possibly warn about an address of OP never being NULL in a comparison
   operation CODE involving null.  */

ਸਥਿਰ ਖਾਲੀ
maybe_warn_for_null_ਪਤਾ (location_t loc, ਰੁੱਖ op, ਰੁੱਖ_ਕੋਡ_2 ਕੋਡ)
{
  /* Prevent warnings issued for macro expansion.  */
  ਜੇ (!warn_ਪਤਾ
      || warning_suppressed_p (op, OPT_Waddress)
      || from_macro_expansion_at (loc))
    ਵਾਪਸ;

  ਜੇ (ਰੁੱਖ_ਕੋਡ (op) == NOP_ਵਿਅੰਜਕ)
    {
      /* Allow casts to intptr_t to suppress the warning.  */
      ਰੁੱਖ type = ਰੁੱਖ_TYPE (op);
      ਜੇ (ਰੁੱਖ_ਕੋਡ (type) == INTEGER_TYPE)
	ਵਾਪਸ;
      op = ਰੁੱਖ_ਸੰਕਾਰਜ (op, 0);
    }

  ਜੇ (ਰੁੱਖ_ਕੋਡ (op) == ਸੂਚਕ_PLUS_ਵਿਅੰਜਕ)
    {
      /* Allow a cast to void* to suppress the warning.  */
      ਰੁੱਖ type = ਰੁੱਖ_TYPE (ਰੁੱਖ_TYPE (op));
      ਜੇ (VOID_TYPE_P (type))
	ਵਾਪਸ;

      /* Adding any value to a null pointer, including zero, is undefined
	 in C.  This includes the expression &p[0] where p is the null
	 pointer, although &p[0] will have been folded to p by this point
	 and so not diagnosed.  */
      ਜੇ (ਕੋਡ == EQ_ਵਿਅੰਜਕ)
	warning_at (loc, OPT_Waddress,
		    "the comparison will always evaluate as %<false%> "
		    "for the pointer operand in %qE must not be NULL",
		    op);
      ਨਹੀਂਤਾਂ
	warning_at (loc, OPT_Waddress,
		    "the comparison will always evaluate as %<true%> "
		    "for the pointer operand in %qE must not be NULL",
		    op);

      ਵਾਪਸ;
    }

  ਜੇ (ਰੁੱਖ_ਕੋਡ (op) != ADDR_ਵਿਅੰਜਕ)
    ਵਾਪਸ;

  op = ਰੁੱਖ_ਸੰਕਾਰਜ (op, 0);

  ਜੇ (ਰੁੱਖ_ਕੋਡ (op) == IMAGPART_ਵਿਅੰਜਕ
      || ਰੁੱਖ_ਕੋਡ (op) == REALPART_ਵਿਅੰਜਕ)
    {
      /* The address of either complex part may not be null.  */
      ਜੇ (ਕੋਡ == EQ_ਵਿਅੰਜਕ)
	warning_at (loc, OPT_Waddress,
		    "the comparison will always evaluate as %<false%> "
		    "for the address of %qE will never be NULL",
		    op);
      ਨਹੀਂਤਾਂ
	warning_at (loc, OPT_Waddress,
		    "the comparison will always evaluate as %<true%> "
		    "for the address of %qE will never be NULL",
		    op);
      ਵਾਪਸ;
    }

  /* Set to true in the loop below if OP dereferences is operand.
     In such a case the ultimate target need not be a decl for
     the null [in]equality test to be constant.  */
  ਤਾਰਕਿਕ deref = ਝੂਠ;

  /* Get the outermost array or object, or member.  */
  ਜਦੋਂ (handled_component_p (op))
    {
      ਜੇ (ਰੁੱਖ_ਕੋਡ (op) == COMPONENT_REF)
	{
	  /* Get the member (its address is never null).  */
	  op = ਰੁੱਖ_ਸੰਕਾਰਜ (op, 1);
	  ਰੋਕੋ;
	}

      /* Get the outer array/object to refer to in the warning.  */
      op = ਰੁੱਖ_ਸੰਕਾਰਜ (op, 0);
      deref = ਸੱਚ;
    }

  ਜੇ ((!deref && !decl_with_nonnull_addr_p (op))
      || from_macro_expansion_at (loc))
    ਵਾਪਸ;

  ਤਾਰਕਿਕ w;
  ਜੇ (ਕੋਡ == EQ_ਵਿਅੰਜਕ)
    w = warning_at (loc, OPT_Waddress,
		    "the comparison will always evaluate as %<false%> "
		    "for the address of %qE will never be NULL",
		    op);
  ਨਹੀਂਤਾਂ
    w = warning_at (loc, OPT_Waddress,
		    "the comparison will always evaluate as %<true%> "
		    "for the address of %qE will never be NULL",
		    op);

  ਜੇ (w && DECL_P (op))
    inform (DECL_ਸਰੋਤ_LOCATION (op), "%qD declared here", op);
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

ਰੁੱਖ
build_ਦੁਆਧਾਰੀ_op (location_t location, ਗਿਣਤੀ ਰੁੱਖ_ਕੋਡ_2 ਕੋਡ,
		 ਰੁੱਖ orig_op0, ਰੁੱਖ orig_op1, ਤਾਰਕਿਕ convert_p)
{
  ਰੁੱਖ type0, type1, orig_type0, orig_type1;
  ਰੁੱਖ eptype;
  ਗਿਣਤੀ ਰੁੱਖ_ਕੋਡ_2 code0, code1;
  ਰੁੱਖ op0, op1;
  ਰੁੱਖ ret = error_mark_ਗੰਢ;
  ਅਚਲ ਅੱਖਰ *invalid_op_diag;
  ਤਾਰਕਿਕ op0_int_operands, op1_int_operands;
  ਤਾਰਕਿਕ int_const, int_const_or_ਉਛਾਲ, int_operands;

  /* Expression code to give to the expression when it is built.
     Normally this is CODE, which is what the caller asked for,
     but in some special cases we change it.  */
  ਗਿਣਤੀ ਰੁੱਖ_ਕੋਡ_2 resultcode = ਕੋਡ;

  /* Data type in which the computation is to be performed.
     In the simplest cases this is the common type of the arguments.  */
  ਰੁੱਖ ਨਤੀਜਾ_type = ਨਿਰਾ;

  /* When the computation is in excess precision, the type of the
     final EXCESS_PRECISION_EXPR.  */
  ਰੁੱਖ semantic_ਨਤੀਜਾ_type = ਨਿਰਾ;

  /* Nonzero means operands have already been type-converted
     in whatever way is necessary.
     Zero means they need to be converted to RESULT_TYPE.  */
  ਪੂਰਨ converted = 0;

  /* Nonzero means create the expression with this type, rather than
     RESULT_TYPE.  */
  ਰੁੱਖ build_type = NULL_ਰੁੱਖ;

  /* Nonzero means after finally constructing the expression
     convert it to this type.  */
  ਰੁੱਖ final_type = NULL_ਰੁੱਖ;

  /* Nonzero if this is an operation like MIN or MAX which can
     safely be computed in short if both args are promoted shorts.
     Also implies COMMON.
     -1 indicates a bitwise operation; this makes a difference
     in the exact conditions for when it is safe to do the operation
     in a narrower mode.  */
  ਪੂਰਨ shorten = 0;

  /* Nonzero if this is a comparison operation;
     if both args are promoted shorts, compare the original shorts.
     Also implies COMMON.  */
  ਪੂਰਨ short_compare = 0;

  /* Nonzero if this is a right-shift operation, which can be computed on the
     original short and then promoted if the operand is a promoted short.  */
  ਪੂਰਨ short_ਖਿਸਕਾਓ = 0;

  /* Nonzero means set RESULT_TYPE to the common type of the args.  */
  ਪੂਰਨ common = 0;

  /* True means types are compatible as far as ObjC is concerned.  */
  ਤਾਰਕਿਕ objc_ok;

  /* True means this is an arithmetic operation that may need excess
     precision.  */
  ਤਾਰਕਿਕ may_need_excess_precision;

  /* True means this is a boolean operation that converts both its
     operands to truth-values.  */
  ਤਾਰਕਿਕ boolean_op = ਝੂਠ;

  /* Remember whether we're doing / or %.  */
  ਤਾਰਕਿਕ doing_div_or_mod = ਝੂਠ;

  /* Remember whether we're doing << or >>.  */
  ਤਾਰਕਿਕ doing_ਖਿਸਕਾਓ = ਝੂਠ;

  /* Tree holding instrumentation expression.  */
  ਰੁੱਖ instrument_ਵਿਅੰਜਕ = ਨਿਰਾ;

  ਜੇ (location == UNKNOWN_LOCATION)
    location = ਨਿਵੇਸ਼_location;

  op0 = orig_op0;
  op1 = orig_op1;

  op0_int_operands = ਵਿਅੰਜਕ_INT_CONST_OPERANDS (orig_op0);
  ਜੇ (op0_int_operands)
    op0 = remove_c_maybe_const_ਵਿਅੰਜਕ (op0);
  op1_int_operands = ਵਿਅੰਜਕ_INT_CONST_OPERANDS (orig_op1);
  ਜੇ (op1_int_operands)
    op1 = remove_c_maybe_const_ਵਿਅੰਜਕ (op1);
  int_operands = (op0_int_operands && op1_int_operands);
  ਜੇ (int_operands)
    {
      int_const_or_ਉਛਾਲ = (ਰੁੱਖ_ਕੋਡ (orig_op0) == INTEGER_CST
			       && ਰੁੱਖ_ਕੋਡ (orig_op1) == INTEGER_CST);
      int_const = (int_const_or_ਉਛਾਲ
		   && !ਰੁੱਖ_ਉਛਾਲ (orig_op0)
		   && !ਰੁੱਖ_ਉਛਾਲ (orig_op1));
    }
  ਨਹੀਂਤਾਂ
    int_const = int_const_or_ਉਛਾਲ = ਝੂਠ;

  /* Do not apply default conversion in mixed vector/scalar expression.  */
  ਜੇ (convert_p
      && ਸਦਿਸ਼_TYPE_P (ਰੁੱਖ_TYPE (op0)) == ਸਦਿਸ਼_TYPE_P (ਰੁੱਖ_TYPE (op1)))
    {
      op0 = default_conversion (op0);
      op1 = default_conversion (op1);
    }

  orig_type0 = type0 = ਰੁੱਖ_TYPE (op0);

  orig_type1 = type1 = ਰੁੱਖ_TYPE (op1);

  /* The expression codes of the data types of the arguments tell us
     whether the arguments are integers, floating, pointers, etc.  */
  code0 = ਰੁੱਖ_ਕੋਡ (type0);
  code1 = ਰੁੱਖ_ਕੋਡ (type1);

  /* Strip NON_LVALUE_EXPRs, etc., since we aren't using as an lvalue.  */
  STRIP_TYPE_NOPS (op0);
  STRIP_TYPE_NOPS (op1);

  /* If an error was already reported for one of the arguments,
     avoid reporting another error.  */

  ਜੇ (code0 == ERROR_MARK || code1 == ERROR_MARK)
    ਵਾਪਸ error_mark_ਗੰਢ;

  ਜੇ (code0 == ਸੂਚਕ_TYPE
      && reject_gcc_builtin (op0, ਵਿਅੰਜਕ_LOCATION (orig_op0)))
    ਵਾਪਸ error_mark_ਗੰਢ;

  ਜੇ (code1 == ਸੂਚਕ_TYPE
      && reject_gcc_builtin (op1, ਵਿਅੰਜਕ_LOCATION (orig_op1)))
    ਵਾਪਸ error_mark_ਗੰਢ;

  ਜੇ ((invalid_op_diag
       = targetm.invalid_ਦੁਆਧਾਰੀ_op (ਕੋਡ, type0, type1)))
    {
      error_at (location, invalid_op_diag);
      ਵਾਪਸ error_mark_ਗੰਢ;
    }

  ਚੋਣ (ਕੋਡ)
    {
    ਹਾਲਤ PLUS_ਵਿਅੰਜਕ:
    ਹਾਲਤ MINUS_ਵਿਅੰਜਕ:
    ਹਾਲਤ MULT_ਵਿਅੰਜਕ:
    ਹਾਲਤ TRUNC_DIV_ਵਿਅੰਜਕ:
    ਹਾਲਤ CEIL_DIV_ਵਿਅੰਜਕ:
    ਹਾਲਤ FLOOR_DIV_ਵਿਅੰਜਕ:
    ਹਾਲਤ ਗੇੜਾ_DIV_ਵਿਅੰਜਕ:
    ਹਾਲਤ EXACT_DIV_ਵਿਅੰਜਕ:
      may_need_excess_precision = ਸੱਚ;
      ਰੋਕੋ;

    ਹਾਲਤ EQ_ਵਿਅੰਜਕ:
    ਹਾਲਤ NE_ਵਿਅੰਜਕ:
    ਹਾਲਤ LE_ਵਿਅੰਜਕ:
    ਹਾਲਤ GE_ਵਿਅੰਜਕ:
    ਹਾਲਤ LT_ਵਿਅੰਜਕ:
    ਹਾਲਤ GT_ਵਿਅੰਜਕ:
      /* Excess precision for implicit conversions of integers to
	 floating point in C11 and later.  */
      may_need_excess_precision = (flag_isoc11
				   && (ANY_INTEGRAL_TYPE_P (type0)
				       || ANY_INTEGRAL_TYPE_P (type1)));
      ਰੋਕੋ;

    ਮੂਲ:
      may_need_excess_precision = ਝੂਠ;
      ਰੋਕੋ;
    }
  ਜੇ (ਰੁੱਖ_ਕੋਡ (op0) == EXCESS_PRECISION_ਵਿਅੰਜਕ)
    {
      op0 = ਰੁੱਖ_ਸੰਕਾਰਜ (op0, 0);
      type0 = ਰੁੱਖ_TYPE (op0);
    }
  ਨਹੀਂਤਾਂ ਜੇ (may_need_excess_precision
	   && (eptype = excess_precision_type (type0)) != NULL_ਰੁੱਖ)
    {
      type0 = eptype;
      op0 = convert (eptype, op0);
    }
  ਜੇ (ਰੁੱਖ_ਕੋਡ (op1) == EXCESS_PRECISION_ਵਿਅੰਜਕ)
    {
      op1 = ਰੁੱਖ_ਸੰਕਾਰਜ (op1, 0);
      type1 = ਰੁੱਖ_TYPE (op1);
    }
  ਨਹੀਂਤਾਂ ਜੇ (may_need_excess_precision
	   && (eptype = excess_precision_type (type1)) != NULL_ਰੁੱਖ)
    {
      type1 = eptype;
      op1 = convert (eptype, op1);
    }

  objc_ok = objc_compare_types (type0, type1, -3, NULL_ਰੁੱਖ);

  /* In case when one of the operands of the binary operation is
     a vector and another is a scalar -- convert scalar to vector.  */
  ਜੇ ((gnu_ਸਦਿਸ਼_type_p (type0) && code1 != ਸਦਿਸ਼_TYPE)
      || (gnu_ਸਦਿਸ਼_type_p (type1) && code0 != ਸਦਿਸ਼_TYPE))
    {
      ਗਿਣਤੀ stv_conv convert_flag = scalar_ਮੰਜ਼ਿਲ_ਸਦਿਸ਼ (location, ਕੋਡ, orig_op0,
						     orig_op1, ਸੱਚ);

      ਚੋਣ (convert_flag)
	{
	  ਹਾਲਤ stv_error:
	    ਵਾਪਸ error_mark_ਗੰਢ;
	  ਹਾਲਤ stv_firstarg:
	    {
              ਤਾਰਕਿਕ maybe_const = ਸੱਚ;
              ਰੁੱਖ sc;
              sc = c_fully_fold (op0, ਝੂਠ, &maybe_const);
              sc = save_ਵਿਅੰਜਕ (sc);
              sc = convert (ਰੁੱਖ_TYPE (type1), sc);
              op0 = build_ਸਦਿਸ਼_from_val (type1, sc);
              ਜੇ (!maybe_const)
                op0 = c_wrap_maybe_const (op0, ਸੱਚ);
              orig_type0 = type0 = ਰੁੱਖ_TYPE (op0);
              code0 = ਰੁੱਖ_ਕੋਡ (type0);
              converted = 1;
              ਰੋਕੋ;
	    }
	  ਹਾਲਤ stv_secondarg:
	    {
	      ਤਾਰਕਿਕ maybe_const = ਸੱਚ;
	      ਰੁੱਖ sc;
	      sc = c_fully_fold (op1, ਝੂਠ, &maybe_const);
	      sc = save_ਵਿਅੰਜਕ (sc);
	      sc = convert (ਰੁੱਖ_TYPE (type0), sc);
	      op1 = build_ਸਦਿਸ਼_from_val (type0, sc);
	      ਜੇ (!maybe_const)
		op1 = c_wrap_maybe_const (op1, ਸੱਚ);
	      orig_type1 = type1 = ਰੁੱਖ_TYPE (op1);
	      code1 = ਰੁੱਖ_ਕੋਡ (type1);
	      converted = 1;
	      ਰੋਕੋ;
	    }
	  ਮੂਲ:
	    ਰੋਕੋ;
	}
    }

  ਚੋਣ (ਕੋਡ)
    {
    ਹਾਲਤ PLUS_ਵਿਅੰਜਕ:
      /* Handle the pointer + int case.  */
      ਜੇ (code0 == ਸੂਚਕ_TYPE
	  && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  ret = ਸੂਚਕ_int_ਜੋੜ (location, PLUS_ਵਿਅੰਜਕ, op0, op1);
	  ਜਾਓ return_build_ਦੁਆਧਾਰੀ_op;
	}
      ਨਹੀਂਤਾਂ ਜੇ (code1 == ਸੂਚਕ_TYPE
	       && (code0 == INTEGER_TYPE || code0 == BITINT_TYPE))
	{
	  ret = ਸੂਚਕ_int_ਜੋੜ (location, PLUS_ਵਿਅੰਜਕ, op1, op0);
	  ਜਾਓ return_build_ਦੁਆਧਾਰੀ_op;
	}
      ਨਹੀਂਤਾਂ
	common = 1;
      ਰੋਕੋ;

    ਹਾਲਤ MINUS_ਵਿਅੰਜਕ:
      /* Subtraction of two similar pointers.
	 We must subtract them as integers, then divide by object size.  */
      ਜੇ (code0 == ਸੂਚਕ_TYPE && code1 == ਸੂਚਕ_TYPE
	  && comp_ਨਿਸ਼ਾਨਾ_types (location, type0, type1))
	{
	  ret = ਸੂਚਕ_diff (location, op0, op1, &instrument_ਵਿਅੰਜਕ);
	  ਜਾਓ return_build_ਦੁਆਧਾਰੀ_op;
	}
      /* Handle pointer minus int.  Just like pointer plus int.  */
      ਨਹੀਂਤਾਂ ਜੇ (code0 == ਸੂਚਕ_TYPE
	       && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  ret = ਸੂਚਕ_int_ਜੋੜ (location, MINUS_ਵਿਅੰਜਕ, op0, op1);
	  ਜਾਓ return_build_ਦੁਆਧਾਰੀ_op;
	}
      ਨਹੀਂਤਾਂ
	common = 1;
      ਰੋਕੋ;

    ਹਾਲਤ MULT_ਵਿਅੰਜਕ:
      common = 1;
      ਰੋਕੋ;

    ਹਾਲਤ TRUNC_DIV_ਵਿਅੰਜਕ:
    ਹਾਲਤ CEIL_DIV_ਵਿਅੰਜਕ:
    ਹਾਲਤ FLOOR_DIV_ਵਿਅੰਜਕ:
    ਹਾਲਤ ਗੇੜਾ_DIV_ਵਿਅੰਜਕ:
    ਹਾਲਤ EXACT_DIV_ਵਿਅੰਜਕ:
      doing_div_or_mod = ਸੱਚ;
      warn_for_div_by_zero (location, op1);

      ਜੇ ((code0 == INTEGER_TYPE || code0 == REAL_TYPE
	   || code0 == FIXED_ਬਿੰਦੂ_TYPE || code0 == BITINT_TYPE
	   || code0 == COMPLEX_TYPE
	   || gnu_ਸਦਿਸ਼_type_p (type0))
	  && (code1 == INTEGER_TYPE || code1 == REAL_TYPE
	      || code1 == FIXED_ਬਿੰਦੂ_TYPE || code1 == BITINT_TYPE
	      || code1 == COMPLEX_TYPE
	      || gnu_ਸਦਿਸ਼_type_p (type1)))
	{
	  ਗਿਣਤੀ ਰੁੱਖ_ਕੋਡ_2 tcode0 = code0, tcode1 = code1;

	  ਜੇ (code0 == COMPLEX_TYPE || code0 == ਸਦਿਸ਼_TYPE)
	    tcode0 = ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (ਰੁੱਖ_TYPE (op0)));
	  ਜੇ (code1 == COMPLEX_TYPE || code1 == ਸਦਿਸ਼_TYPE)
	    tcode1 = ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (ਰੁੱਖ_TYPE (op1)));

	  ਜੇ (!(((tcode0 == INTEGER_TYPE || tcode0 == BITINT_TYPE
		  || (tcode0 == ENUMERAL_TYPE && code0 == ਸਦਿਸ਼_TYPE))
		 && (tcode1 == INTEGER_TYPE || tcode1 == BITINT_TYPE
		     || (tcode1 == ENUMERAL_TYPE && code1 == ਸਦਿਸ਼_TYPE)))
		|| (tcode0 == FIXED_ਬਿੰਦੂ_TYPE && tcode1 == FIXED_ਬਿੰਦੂ_TYPE)))
	    resultcode = RDIV_ਵਿਅੰਜਕ;
	  ਨਹੀਂਤਾਂ
	    /* Although it would be tempting to shorten always here, that
	       loses on some targets, since the modulo instruction is
	       undefined if the quotient can't be represented in the
	       computation mode.  We shorten only if unsigned or if
	       dividing by something we know != -1.  */
	    shorten = may_shorten_divmod (op0, op1);
	  common = 1;
	}
      ਰੋਕੋ;

    ਹਾਲਤ ਦੋਆਧਾਰੀ_ਅੰਕ_AND_ਵਿਅੰਜਕ:
    ਹਾਲਤ ਦੋਆਧਾਰੀ_ਅੰਕ_IOR_ਵਿਅੰਜਕ:
    ਹਾਲਤ ਦੋਆਧਾਰੀ_ਅੰਕ_XOR_ਵਿਅੰਜਕ:
      ਜੇ ((code0 == INTEGER_TYPE || code0 == BITINT_TYPE)
	  && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	shorten = -1;
      /* Allow vector types which are not floating point types.   */
      ਨਹੀਂਤਾਂ ਜੇ (gnu_ਸਦਿਸ਼_type_p (type0)
	       && gnu_ਸਦਿਸ਼_type_p (type1)
	       && !ਸਦਿਸ਼_FLOAT_TYPE_P (type0)
	       && !ਸਦਿਸ਼_FLOAT_TYPE_P (type1))
	common = 1;
      ਰੋਕੋ;

    ਹਾਲਤ TRUNC_MOD_ਵਿਅੰਜਕ:
    ਹਾਲਤ FLOOR_MOD_ਵਿਅੰਜਕ:
      doing_div_or_mod = ਸੱਚ;
      warn_for_div_by_zero (location, op1);

      ਜੇ (gnu_ਸਦਿਸ਼_type_p (type0)
	  && gnu_ਸਦਿਸ਼_type_p (type1)
	  && ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (type0)) == INTEGER_TYPE
	  && ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (type1)) == INTEGER_TYPE)
	common = 1;
      ਨਹੀਂਤਾਂ ਜੇ ((code0 == INTEGER_TYPE || code0 == BITINT_TYPE)
	       && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  /* Although it would be tempting to shorten always here, that loses
	     on some targets, since the modulo instruction is undefined if the
	     quotient can't be represented in the computation mode.  We shorten
	     only if unsigned or if dividing by something we know != -1.  */
	  shorten = may_shorten_divmod (op0, op1);
	  common = 1;
	}
      ਰੋਕੋ;

    ਹਾਲਤ TRUTH_ANDIF_ਵਿਅੰਜਕ:
    ਹਾਲਤ TRUTH_ORIF_ਵਿਅੰਜਕ:
    ਹਾਲਤ TRUTH_AND_ਵਿਅੰਜਕ:
    ਹਾਲਤ TRUTH_OR_ਵਿਅੰਜਕ:
    ਹਾਲਤ TRUTH_XOR_ਵਿਅੰਜਕ:
      ਜੇ ((code0 == INTEGER_TYPE || code0 == ਸੂਚਕ_TYPE
	   || code0 == REAL_TYPE || code0 == COMPLEX_TYPE
	   || code0 == FIXED_ਬਿੰਦੂ_TYPE || code0 == NULLPTR_TYPE
	   || code0 == BITINT_TYPE)
	  && (code1 == INTEGER_TYPE || code1 == ਸੂਚਕ_TYPE
	      || code1 == REAL_TYPE || code1 == COMPLEX_TYPE
	      || code1 == FIXED_ਬਿੰਦੂ_TYPE || code1 == NULLPTR_TYPE
	      || code1 == BITINT_TYPE))
	{
	  /* Result of these operations is always an int,
	     but that does not mean the operands should be
	     converted to ints!  */
	  ਨਤੀਜਾ_type = integer_type_ਗੰਢ;
	  ਜੇ (op0_int_operands)
	    {
	      op0 = c_objc_common_truthvalue_conversion (location, orig_op0);
	      op0 = remove_c_maybe_const_ਵਿਅੰਜਕ (op0);
	    }
	  ਨਹੀਂਤਾਂ
	    op0 = c_objc_common_truthvalue_conversion (location, op0);
	  ਜੇ (op1_int_operands)
	    {
	      op1 = c_objc_common_truthvalue_conversion (location, orig_op1);
	      op1 = remove_c_maybe_const_ਵਿਅੰਜਕ (op1);
	    }
	  ਨਹੀਂਤਾਂ
	    op1 = c_objc_common_truthvalue_conversion (location, op1);
	  converted = 1;
	  boolean_op = ਸੱਚ;
	}
      ਜੇ (ਕੋਡ == TRUTH_ANDIF_ਵਿਅੰਜਕ)
	{
	  int_const_or_ਉਛਾਲ = (int_operands
				   && ਰੁੱਖ_ਕੋਡ (orig_op0) == INTEGER_CST
				   && (op0 == truthvalue_false_ਗੰਢ
				       || ਰੁੱਖ_ਕੋਡ (orig_op1) == INTEGER_CST));
	  int_const = (int_const_or_ਉਛਾਲ
		       && !ਰੁੱਖ_ਉਛਾਲ (orig_op0)
		       && (op0 == truthvalue_false_ਗੰਢ
			   || !ਰੁੱਖ_ਉਛਾਲ (orig_op1)));
	}
      ਨਹੀਂਤਾਂ ਜੇ (ਕੋਡ == TRUTH_ORIF_ਵਿਅੰਜਕ)
	{
	  int_const_or_ਉਛਾਲ = (int_operands
				   && ਰੁੱਖ_ਕੋਡ (orig_op0) == INTEGER_CST
				   && (op0 == truthvalue_true_ਗੰਢ
				       || ਰੁੱਖ_ਕੋਡ (orig_op1) == INTEGER_CST));
	  int_const = (int_const_or_ਉਛਾਲ
		       && !ਰੁੱਖ_ਉਛਾਲ (orig_op0)
		       && (op0 == truthvalue_true_ਗੰਢ
			   || !ਰੁੱਖ_ਉਛਾਲ (orig_op1)));
	}
      ਰੋਕੋ;

      /* Shift operations: result has same type as first operand;
	 always convert second operand to int.
	 Also set SHORT_SHIFT if shifting rightward.  */

    ਹਾਲਤ RSHIFT_ਵਿਅੰਜਕ:
      ਜੇ (gnu_ਸਦਿਸ਼_type_p (type0)
	  && gnu_ਸਦਿਸ਼_type_p (type1)
	  && ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (type0)) == INTEGER_TYPE
	  && ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (type1)) == INTEGER_TYPE
	  && ਗਿਆਤ_eq (TYPE_ਸਦਿਸ਼_SUBPARTS (type0),
		       TYPE_ਸਦਿਸ਼_SUBPARTS (type1)))
	{
	  ਨਤੀਜਾ_type = type0;
	  converted = 1;
	}
      ਨਹੀਂਤਾਂ ਜੇ ((code0 == INTEGER_TYPE || code0 == FIXED_ਬਿੰਦੂ_TYPE
		|| code0 == BITINT_TYPE
		|| (gnu_ਸਦਿਸ਼_type_p (type0)
		    && ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (type0)) == INTEGER_TYPE))
	       && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  doing_ਖਿਸਕਾਓ = ਸੱਚ;
	  ਜੇ (ਰੁੱਖ_ਕੋਡ (op1) == INTEGER_CST)
	    {
	      ਜੇ (ਰੁੱਖ_int_cst_sgn (op1) < 0)
		{
		  int_const = ਝੂਠ;
		  ਜੇ (c_inhibit_evaluation_warnings == 0)
		    warning_at (location, OPT_Wshift_ਗਿਣਤੀ_negative,
				"right shift count is negative");
		}
	      ਨਹੀਂਤਾਂ ਜੇ (code0 == ਸਦਿਸ਼_TYPE)
		{
		  ਜੇ (compare_ਰੁੱਖ_int (op1,
					TYPE_PRECISION (ਰੁੱਖ_TYPE (type0)))
		      >= 0)
		    {
		      int_const = ਝੂਠ;
		      ਜੇ (c_inhibit_evaluation_warnings == 0)
			warning_at (location, OPT_Wshift_ਗਿਣਤੀ_ਉਛਾਲ,
				    "right shift count >= width of vector element");
		    }
		}
	      ਨਹੀਂਤਾਂ
		{
		  ਜੇ (!integer_zerop (op1))
		    short_ਖਿਸਕਾਓ = 1;

		  ਜੇ (compare_ਰੁੱਖ_int (op1, TYPE_PRECISION (type0)) >= 0)
		    {
		      int_const = ਝੂਠ;
		      ਜੇ (c_inhibit_evaluation_warnings == 0)
			warning_at (location, OPT_Wshift_ਗਿਣਤੀ_ਉਛਾਲ,
				    "right shift count >= width of type");
		    }
		}
	    }

	  /* Use the type of the value to be shifted.  */
	  ਨਤੀਜਾ_type = type0;
	  /* Avoid converting op1 to result_type later.  */
	  converted = 1;
	}
      ਰੋਕੋ;

    ਹਾਲਤ LSHIFT_ਵਿਅੰਜਕ:
      ਜੇ (gnu_ਸਦਿਸ਼_type_p (type0)
	  && gnu_ਸਦਿਸ਼_type_p (type1)
	  && ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (type0)) == INTEGER_TYPE
	  && ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (type1)) == INTEGER_TYPE
	  && ਗਿਆਤ_eq (TYPE_ਸਦਿਸ਼_SUBPARTS (type0),
		       TYPE_ਸਦਿਸ਼_SUBPARTS (type1)))
	{
	  ਨਤੀਜਾ_type = type0;
	  converted = 1;
	}
      ਨਹੀਂਤਾਂ ਜੇ ((code0 == INTEGER_TYPE || code0 == FIXED_ਬਿੰਦੂ_TYPE
		|| code0 == BITINT_TYPE
		|| (gnu_ਸਦਿਸ਼_type_p (type0)
		    && ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (type0)) == INTEGER_TYPE))
	       && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  doing_ਖਿਸਕਾਓ = ਸੱਚ;
	  ਜੇ (ਰੁੱਖ_ਕੋਡ (op0) == INTEGER_CST
	      && ਰੁੱਖ_int_cst_sgn (op0) < 0
	      && !TYPE_ਉਛਾਲ_WRAPS (type0))
	    {
	      /* Don't reject a left shift of a negative value in a context
		 where a constant expression is needed in C90.  */
	      ਜੇ (flag_isoc99)
		int_const = ਝੂਠ;
	      ਜੇ (c_inhibit_evaluation_warnings == 0)
		warning_at (location, OPT_Wshift_negative_ਮੁੱਲ,
			    "left shift of negative value");
	    }
	  ਜੇ (ਰੁੱਖ_ਕੋਡ (op1) == INTEGER_CST)
	    {
	      ਜੇ (ਰੁੱਖ_int_cst_sgn (op1) < 0)
		{
		  int_const = ਝੂਠ;
		  ਜੇ (c_inhibit_evaluation_warnings == 0)
		    warning_at (location, OPT_Wshift_ਗਿਣਤੀ_negative,
				"left shift count is negative");
		}
	      ਨਹੀਂਤਾਂ ਜੇ (code0 == ਸਦਿਸ਼_TYPE)
		{
		  ਜੇ (compare_ਰੁੱਖ_int (op1,
					TYPE_PRECISION (ਰੁੱਖ_TYPE (type0)))
		      >= 0)
		    {
		      int_const = ਝੂਠ;
		      ਜੇ (c_inhibit_evaluation_warnings == 0)
			warning_at (location, OPT_Wshift_ਗਿਣਤੀ_ਉਛਾਲ,
				    "left shift count >= width of vector element");
		    }
		}
	      ਨਹੀਂਤਾਂ ਜੇ (compare_ਰੁੱਖ_int (op1, TYPE_PRECISION (type0)) >= 0)
		{
		  int_const = ਝੂਠ;
		  ਜੇ (c_inhibit_evaluation_warnings == 0)
		    warning_at (location, OPT_Wshift_ਗਿਣਤੀ_ਉਛਾਲ,
				"left shift count >= width of type");
		}
	      ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਕੋਡ (op0) == INTEGER_CST
		       && maybe_warn_ਖਿਸਕਾਓ_ਉਛਾਲ (location, op0, op1)
		       && flag_isoc99)
		int_const = ਝੂਠ;
	    }

	  /* Use the type of the value to be shifted.  */
	  ਨਤੀਜਾ_type = type0;
	  /* Avoid converting op1 to result_type later.  */
	  converted = 1;
	}
      ਰੋਕੋ;

    ਹਾਲਤ EQ_ਵਿਅੰਜਕ:
    ਹਾਲਤ NE_ਵਿਅੰਜਕ:
      ਜੇ (gnu_ਸਦਿਸ਼_type_p (type0) && gnu_ਸਦਿਸ਼_type_p (type1))
        {
          ਰੁੱਖ intt;
	  ਜੇ (!ਸਦਿਸ਼_types_compatible_elements_p (type0, type1))
            {
              error_at (location, "comparing vectors with different "
                                  "element types");
              ਵਾਪਸ error_mark_ਗੰਢ;
            }

	  ਜੇ (maybe_ne (TYPE_ਸਦਿਸ਼_SUBPARTS (type0),
			TYPE_ਸਦਿਸ਼_SUBPARTS (type1)))
            {
              error_at (location, "comparing vectors with different "
                                  "number of elements");
              ਵਾਪਸ error_mark_ਗੰਢ;
            }

	  /* It's not precisely specified how the usual arithmetic
	     conversions apply to the vector types.  Here, we use
	     the unsigned type if one of the operands is signed and
	     the other one is unsigned.  */
	  ਜੇ (TYPE_UNSIGNED (type0) != TYPE_UNSIGNED (type1))
	    {
	      ਜੇ (!TYPE_UNSIGNED (type0))
		op0 = build1 (VIEW_CONVERT_ਵਿਅੰਜਕ, type1, op0);
	      ਨਹੀਂਤਾਂ
		op1 = build1 (VIEW_CONVERT_ਵਿਅੰਜਕ, type0, op1);
	      warning_at (location, OPT_Wsign_compare, "comparison between "
			  "types %qT and %qT", type0, type1);
	    }

          /* Always construct signed integer vector type.  */
	  ਜੇ (ਸਦਿਸ਼_BOOLEAN_TYPE_P (type0) && ਸਦਿਸ਼_BOOLEAN_TYPE_P (type1))
	    ਨਤੀਜਾ_type = type0;
	  ਨਹੀਂਤਾਂ
	    {
	      ਸਵੈਚਾਲਿਤ nelts = TYPE_ਸਦਿਸ਼_SUBPARTS (type0);

	      intt = c_common_type_for_ਮਾਪ (GET_ਬਹੁਲਕ_BITSIZE
					     (SCALAR_TYPE_ਬਹੁਲਕ
						(ਰੁੱਖ_TYPE (type0))), 0);
	      ਜੇ (!intt)
		{
		  error_at (location, "could not find an integer type "
				      "of the same size as %qT",
			    ਰੁੱਖ_TYPE (type0));
		  ਵਾਪਸ error_mark_ਗੰਢ;
		}
	      ਨਤੀਜਾ_type = build_opaque_ਸਦਿਸ਼_type (intt, nelts);
	    }
          converted = 1;
	  ret = build_vec_cmp (resultcode, ਨਤੀਜਾ_type, op0, op1);
	  ਜਾਓ return_build_ਦੁਆਧਾਰੀ_op;
        }
      ਜੇ (FLOAT_TYPE_P (type0) || FLOAT_TYPE_P (type1))
	warning_at (location,
		    OPT_Wfloat_equal,
		    "comparing floating-point with %<==%> or %<!=%> is unsafe");
      /* Result of comparison is always int,
	 but don't convert the args to int!  */
      build_type = integer_type_ਗੰਢ;
      ਜੇ ((code0 == INTEGER_TYPE || code0 == REAL_TYPE || code0 == BITINT_TYPE
	   || code0 == FIXED_ਬਿੰਦੂ_TYPE || code0 == COMPLEX_TYPE)
	  && (code1 == INTEGER_TYPE || code1 == REAL_TYPE
	      || code1 == BITINT_TYPE
	      || code1 == FIXED_ਬਿੰਦੂ_TYPE || code1 == COMPLEX_TYPE))
	short_compare = 1;
      ਨਹੀਂਤਾਂ ਜੇ (code0 == ਸੂਚਕ_TYPE
	       && (code1 == NULLPTR_TYPE
		   || null_ਸੂਚਕ_constant_p (orig_op1)))
	{
	  maybe_warn_for_null_ਪਤਾ (location, op0, ਕੋਡ);
	  ਨਤੀਜਾ_type = type0;
	}
      ਨਹੀਂਤਾਂ ਜੇ (code1 == ਸੂਚਕ_TYPE
	       && (code0 == NULLPTR_TYPE
		   || null_ਸੂਚਕ_constant_p (orig_op0)))
	{
	  maybe_warn_for_null_ਪਤਾ (location, op1, ਕੋਡ);
	  ਨਤੀਜਾ_type = type1;
	}
      ਨਹੀਂਤਾਂ ਜੇ (code0 == ਸੂਚਕ_TYPE && code1 == ਸੂਚਕ_TYPE)
	{
	  ਰੁੱਖ tt0 = ਰੁੱਖ_TYPE (type0);
	  ਰੁੱਖ tt1 = ਰੁੱਖ_TYPE (type1);
	  addr_space_t as0 = TYPE_ADDR_SPACE (tt0);
	  addr_space_t as1 = TYPE_ADDR_SPACE (tt1);
	  addr_space_t as_common = ADDR_SPACE_GENERIC;

	  /* Anything compares with void *.  void * compares with anything.
	     Otherwise, the targets must be compatible
	     and both must be object or both incomplete.  */
	  ਜੇ (comp_ਨਿਸ਼ਾਨਾ_types (location, type0, type1))
	    ਨਤੀਜਾ_type = common_ਸੂਚਕ_type (type0, type1, NULL_ਰੁੱਖ);
	  ਨਹੀਂਤਾਂ ਜੇ (!addr_space_superset (as0, as1, &as_common))
	    {
	      error_at (location, "comparison of pointers to "
			"disjoint address spaces");
	      ਵਾਪਸ error_mark_ਗੰਢ;
	    }
	  ਨਹੀਂਤਾਂ ਜੇ (VOID_TYPE_P (tt0) && !TYPE_ATOMIC (tt0))
	    {
	      ਜੇ (pedantic && ਰੁੱਖ_ਕੋਡ (tt1) == FUNCTION_TYPE)
		pedwarn (location, OPT_Wpedantic, "ISO C forbids "
			 "comparison of %<void *%> with function pointer");
	    }
	  ਨਹੀਂਤਾਂ ਜੇ (VOID_TYPE_P (tt1) && !TYPE_ATOMIC (tt1))
	    {
	      ਜੇ (pedantic && ਰੁੱਖ_ਕੋਡ (tt0) == FUNCTION_TYPE)
		pedwarn (location, OPT_Wpedantic, "ISO C forbids "
			 "comparison of %<void *%> with function pointer");
	    }
	  ਨਹੀਂਤਾਂ
	    /* Avoid warning about the volatile ObjC EH puts on decls.  */
	    ਜੇ (!objc_ok)
	      pedwarn (location, OPT_Wcompare_distinct_ਸੂਚਕ_types,
		       "comparison of distinct pointer types lacks a cast");

	  ਜੇ (ਨਤੀਜਾ_type == NULL_ਰੁੱਖ)
	    {
	      ਪੂਰਨ qual = ENCODE_QUAL_ADDR_SPACE (as_common);
	      ਨਤੀਜਾ_type = c_build_ਸੂਚਕ_type
			      (c_build_qualified_type (void_type_ਗੰਢ, qual));
	    }
	}
      ਨਹੀਂਤਾਂ ਜੇ (code0 == ਸੂਚਕ_TYPE
	       && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  ਨਤੀਜਾ_type = type0;
	  pedwarn (location, 0, "comparison between pointer and integer");
	}
      ਨਹੀਂਤਾਂ ਜੇ ((code0 == INTEGER_TYPE || code0 == BITINT_TYPE)
	       && code1 == ਸੂਚਕ_TYPE)
	{
	  ਨਤੀਜਾ_type = type1;
	  pedwarn (location, 0, "comparison between pointer and integer");
	}
      /* 6.5.9: One of the following shall hold:
	 -- both operands have type nullptr_t;  */
      ਨਹੀਂਤਾਂ ਜੇ (code0 == NULLPTR_TYPE && code1 == NULLPTR_TYPE)
	{
	  ਨਤੀਜਾ_type = nullptr_type_ਗੰਢ;
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
      ਨਹੀਂਤਾਂ ਜੇ (code0 == NULLPTR_TYPE && null_ਸੂਚਕ_constant_p (orig_op1))
	ਨਤੀਜਾ_type = (INTEGRAL_TYPE_P (type1)
		       ? c_build_ਸੂਚਕ_type (type1) : type1);
      ਨਹੀਂਤਾਂ ਜੇ (code1 == NULLPTR_TYPE && null_ਸੂਚਕ_constant_p (orig_op0))
	ਨਤੀਜਾ_type = (INTEGRAL_TYPE_P (type0)
		       ? c_build_ਸੂਚਕ_type (type0) : type0);
      ਜੇ ((C_BOOLEAN_TYPE_P (ਰੁੱਖ_TYPE (orig_op0))
	   || truth_ਮੁੱਲ_p (ਰੁੱਖ_ਕੋਡ (orig_op0)))
	  ^ (C_BOOLEAN_TYPE_P (ਰੁੱਖ_TYPE (orig_op1))
	     || truth_ਮੁੱਲ_p (ਰੁੱਖ_ਕੋਡ (orig_op1))))
	maybe_warn_bool_compare (location, ਕੋਡ, orig_op0, orig_op1);
      ਰੋਕੋ;

    ਹਾਲਤ LE_ਵਿਅੰਜਕ:
    ਹਾਲਤ GE_ਵਿਅੰਜਕ:
    ਹਾਲਤ LT_ਵਿਅੰਜਕ:
    ਹਾਲਤ GT_ਵਿਅੰਜਕ:
      ਜੇ (gnu_ਸਦਿਸ਼_type_p (type0) && gnu_ਸਦਿਸ਼_type_p (type1))
        {
          ਰੁੱਖ intt;
	  ਜੇ (!ਸਦਿਸ਼_types_compatible_elements_p (type0, type1))
            {
              error_at (location, "comparing vectors with different "
                                  "element types");
              ਵਾਪਸ error_mark_ਗੰਢ;
            }

	  ਜੇ (maybe_ne (TYPE_ਸਦਿਸ਼_SUBPARTS (type0),
			TYPE_ਸਦਿਸ਼_SUBPARTS (type1)))
            {
              error_at (location, "comparing vectors with different "
                                  "number of elements");
              ਵਾਪਸ error_mark_ਗੰਢ;
            }

	  /* It's not precisely specified how the usual arithmetic
	     conversions apply to the vector types.  Here, we use
	     the unsigned type if one of the operands is signed and
	     the other one is unsigned.  */
	  ਜੇ (TYPE_UNSIGNED (type0) != TYPE_UNSIGNED (type1))
	    {
	      ਜੇ (!TYPE_UNSIGNED (type0))
		op0 = build1 (VIEW_CONVERT_ਵਿਅੰਜਕ, type1, op0);
	      ਨਹੀਂਤਾਂ
		op1 = build1 (VIEW_CONVERT_ਵਿਅੰਜਕ, type0, op1);
	      warning_at (location, OPT_Wsign_compare, "comparison between "
			  "types %qT and %qT", type0, type1);
	    }

          /* Always construct signed integer vector type.  */
          intt = c_common_type_for_ਮਾਪ (GET_ਬਹੁਲਕ_BITSIZE
					 (SCALAR_TYPE_ਬਹੁਲਕ
					  (ਰੁੱਖ_TYPE (type0))), 0);
	  ਜੇ (!intt)
	    {
	      error_at (location, "could not find an integer type "
				  "of the same size as %qT",
			ਰੁੱਖ_TYPE (type0));
	      ਵਾਪਸ error_mark_ਗੰਢ;
	    }
          ਨਤੀਜਾ_type = build_opaque_ਸਦਿਸ਼_type (intt,
						  TYPE_ਸਦਿਸ਼_SUBPARTS (type0));
          converted = 1;
	  ret = build_vec_cmp (resultcode, ਨਤੀਜਾ_type, op0, op1);
	  ਜਾਓ return_build_ਦੁਆਧਾਰੀ_op;
        }
      build_type = integer_type_ਗੰਢ;
      ਜੇ ((code0 == INTEGER_TYPE || code0 == REAL_TYPE
	   || code0 == BITINT_TYPE || code0 == FIXED_ਬਿੰਦੂ_TYPE)
	  && (code1 == INTEGER_TYPE || code1 == REAL_TYPE
	      || code1 == BITINT_TYPE || code1 == FIXED_ਬਿੰਦੂ_TYPE))
	short_compare = 1;
      ਨਹੀਂਤਾਂ ਜੇ (code0 == ਸੂਚਕ_TYPE && code1 == ਸੂਚਕ_TYPE)
	{
	  addr_space_t as0 = TYPE_ADDR_SPACE (ਰੁੱਖ_TYPE (type0));
	  addr_space_t as1 = TYPE_ADDR_SPACE (ਰੁੱਖ_TYPE (type1));
	  addr_space_t as_common;

	  ਜੇ (comp_ਨਿਸ਼ਾਨਾ_types (location, type0, type1))
	    {
	      ਨਤੀਜਾ_type = common_ਸੂਚਕ_type (type0, type1, NULL_ਰੁੱਖ);
	      ਜੇ (!COMPLETE_TYPE_P (ਰੁੱਖ_TYPE (type0))
		  != !COMPLETE_TYPE_P (ਰੁੱਖ_TYPE (type1)))
		pedwarn_c99 (location, OPT_Wpedantic,
			     "comparison of complete and incomplete pointers");
	      ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (type0)) == FUNCTION_TYPE)
		pedwarn (location, OPT_Wpedantic, "ISO C forbids "
			 "ordered comparisons of pointers to functions");
	      ਨਹੀਂਤਾਂ ਜੇ (null_ਸੂਚਕ_constant_p (orig_op0)
		       || null_ਸੂਚਕ_constant_p (orig_op1))
		warning_at (location, OPT_Wextra,
			    "ordered comparison of pointer with null pointer");

	    }
	  ਨਹੀਂਤਾਂ ਜੇ (!addr_space_superset (as0, as1, &as_common))
	    {
	      error_at (location, "comparison of pointers to "
			"disjoint address spaces");
	      ਵਾਪਸ error_mark_ਗੰਢ;
	    }
	  ਨਹੀਂਤਾਂ
	    {
	      ਪੂਰਨ qual = ENCODE_QUAL_ADDR_SPACE (as_common);
	      ਨਤੀਜਾ_type = c_build_ਸੂਚਕ_type
			      (c_build_qualified_type (void_type_ਗੰਢ, qual));
              pedwarn (location, OPT_Wcompare_distinct_ਸੂਚਕ_types,
                       "comparison of distinct pointer types lacks a cast");
	    }
	}
      ਨਹੀਂਤਾਂ ਜੇ (code0 == ਸੂਚਕ_TYPE && null_ਸੂਚਕ_constant_p (orig_op1))
	{
	  ਨਤੀਜਾ_type = type0;
	  ਜੇ (pedantic)
	    pedwarn (location, OPT_Wpedantic,
		     "ordered comparison of pointer with integer zero");
	  ਨਹੀਂਤਾਂ ਜੇ (extra_warnings)
	    warning_at (location, OPT_Wextra,
			"ordered comparison of pointer with integer zero");
	}
      ਨਹੀਂਤਾਂ ਜੇ (code1 == ਸੂਚਕ_TYPE && null_ਸੂਚਕ_constant_p (orig_op0))
	{
	  ਨਤੀਜਾ_type = type1;
	  ਜੇ (pedantic)
	    pedwarn (location, OPT_Wpedantic,
		     "ordered comparison of pointer with integer zero");
	  ਨਹੀਂਤਾਂ ਜੇ (extra_warnings)
	    warning_at (location, OPT_Wextra,
			"ordered comparison of pointer with integer zero");
	}
      ਨਹੀਂਤਾਂ ਜੇ (code0 == ਸੂਚਕ_TYPE
	       && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  ਨਤੀਜਾ_type = type0;
	  pedwarn (location, 0, "comparison between pointer and integer");
	}
      ਨਹੀਂਤਾਂ ਜੇ ((code0 == INTEGER_TYPE || code0 == BITINT_TYPE)
	       && code1 == ਸੂਚਕ_TYPE)
	{
	  ਨਤੀਜਾ_type = type1;
	  pedwarn (location, 0, "comparison between pointer and integer");
	}

      ਜੇ ((code0 == ਸੂਚਕ_TYPE || code1 == ਸੂਚਕ_TYPE)
	  && current_function_decl != NULL_ਰੁੱਖ
	  && sanitize_flags_p (SANITIZE_ਸੂਚਕ_COMPARE))
	{
	  op0 = save_ਵਿਅੰਜਕ (c_fully_fold (op0, ਝੂਠ, ਨਿਰਾ));
	  op1 = save_ਵਿਅੰਜਕ (c_fully_fold (op1, ਝੂਠ, ਨਿਰਾ));

	  ਰੁੱਖ tt = builtin_decl_explicit (BUILT_ਵਿੱਚ_ASAN_ਸੂਚਕ_COMPARE);
	  instrument_ਵਿਅੰਜਕ = build_call_ਵਿਅੰਜਕ_loc (location, tt, 2, op0, op1);
	}

      ਜੇ ((C_BOOLEAN_TYPE_P (ਰੁੱਖ_TYPE (orig_op0))
	   || truth_ਮੁੱਲ_p (ਰੁੱਖ_ਕੋਡ (orig_op0)))
	  ^ (C_BOOLEAN_TYPE_P (ਰੁੱਖ_TYPE (orig_op1))
	     || truth_ਮੁੱਲ_p (ਰੁੱਖ_ਕੋਡ (orig_op1))))
	maybe_warn_bool_compare (location, ਕੋਡ, orig_op0, orig_op1);
      ਰੋਕੋ;

    ਹਾਲਤ MIN_ਵਿਅੰਜਕ:
    ਹਾਲਤ MAX_ਵਿਅੰਜਕ:
      /* Used for OpenMP atomics.  */
      gcc_assert (flag_openmp);
      common = 1;
      ਰੋਕੋ;

    ਮੂਲ:
      gcc_unreachable ();
    }

  ਜੇ (code0 == ERROR_MARK || code1 == ERROR_MARK)
    ਵਾਪਸ error_mark_ਗੰਢ;

  ਜੇ (gnu_ਸਦਿਸ਼_type_p (type0)
      && gnu_ਸਦਿਸ਼_type_p (type1)
      && (!ਰੁੱਖ_int_cst_equal (TYPE_ਮਾਪ (type0), TYPE_ਮਾਪ (type1))
	  || !ਸਦਿਸ਼_types_compatible_elements_p (type0, type1)))
    {
      gcc_rich_location richloc (location);
      maybe_range_label_for_ਰੁੱਖ_type_mismatch
	label_for_op0 (orig_op0, orig_op1),
	label_for_op1 (orig_op1, orig_op0);
      richloc.maybe_ਜੋੜੋ_ਵਿਅੰਜਕ (orig_op0, &label_for_op0, highlight_colors::lhs);
      richloc.maybe_ਜੋੜੋ_ਵਿਅੰਜਕ (orig_op1, &label_for_op1, highlight_colors::rhs);
      ਦੁਆਧਾਰੀ_op_error (&richloc, ਕੋਡ, type0, type1);
      ਵਾਪਸ error_mark_ਗੰਢ;
    }

  ਜੇ ((code0 == INTEGER_TYPE || code0 == REAL_TYPE || code0 == COMPLEX_TYPE
       || code0 == FIXED_ਬਿੰਦੂ_TYPE || code0 == BITINT_TYPE
       || gnu_ਸਦਿਸ਼_type_p (type0))
      && (code1 == INTEGER_TYPE || code1 == REAL_TYPE || code1 == COMPLEX_TYPE
	  || code1 == FIXED_ਬਿੰਦੂ_TYPE || code1 == BITINT_TYPE
	  || gnu_ਸਦਿਸ਼_type_p (type1)))
    {
      ਤਾਰਕਿਕ ਪਹਿਲਾ_complex = (code0 == COMPLEX_TYPE);
      ਤਾਰਕਿਕ ਦੂਜਾ_complex = (code1 == COMPLEX_TYPE);
      ਪੂਰਨ none_complex = (!ਪਹਿਲਾ_complex && !ਦੂਜਾ_complex);

      ਜੇ (shorten || common || short_compare)
	{
	  ਨਤੀਜਾ_type = c_common_type (type0, type1);
	  do_warn_double_promotion (ਨਤੀਜਾ_type, type0, type1,
				    "implicit conversion from %qT to %qT "
				    "to match other operand of binary "
				    "expression",
				    location);
	  ਜੇ (ਨਤੀਜਾ_type == error_mark_ਗੰਢ)
	    ਵਾਪਸ error_mark_ਗੰਢ;
	}

      ਜੇ (ਪਹਿਲਾ_complex != ਦੂਜਾ_complex
	  && (ਕੋਡ == PLUS_ਵਿਅੰਜਕ
	      || ਕੋਡ == MINUS_ਵਿਅੰਜਕ
	      || ਕੋਡ == MULT_ਵਿਅੰਜਕ
	      || (ਕੋਡ == TRUNC_DIV_ਵਿਅੰਜਕ && ਪਹਿਲਾ_complex))
	  && ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (ਨਤੀਜਾ_type)) == REAL_TYPE
	  && flag_signed_zeros)
	{
	  /* An operation on mixed real/complex operands must be
	     handled specially, but the language-independent code can
	     more easily optimize the plain complex arithmetic if
	     -fno-signed-zeros.  */
	  ਰੁੱਖ real_type = ਰੁੱਖ_TYPE (ਨਤੀਜਾ_type);
	  ਰੁੱਖ real, imag;
	  ਜੇ (type0 != orig_type0 || type1 != orig_type1)
	    {
	      gcc_assert (may_need_excess_precision && common);
	      semantic_ਨਤੀਜਾ_type = c_common_type (orig_type0, orig_type1);
	    }
	  ਜੇ (ਪਹਿਲਾ_complex)
	    {
	      ਜੇ (ਰੁੱਖ_TYPE (op0) != ਨਤੀਜਾ_type)
		op0 = convert_and_check (location, ਨਤੀਜਾ_type, op0);
	      ਜੇ (ਰੁੱਖ_TYPE (op1) != real_type)
		op1 = convert_and_check (location, real_type, op1);
	    }
	  ਨਹੀਂਤਾਂ
	    {
	      ਜੇ (ਰੁੱਖ_TYPE (op0) != real_type)
		op0 = convert_and_check (location, real_type, op0);
	      ਜੇ (ਰੁੱਖ_TYPE (op1) != ਨਤੀਜਾ_type)
		op1 = convert_and_check (location, ਨਤੀਜਾ_type, op1);
	    }
	  ਜੇ (ਰੁੱਖ_ਕੋਡ (op0) == ERROR_MARK || ਰੁੱਖ_ਕੋਡ (op1) == ERROR_MARK)
	    ਵਾਪਸ error_mark_ਗੰਢ;
	  ਜੇ (ਪਹਿਲਾ_complex)
	    {
	      op0 = save_ਵਿਅੰਜਕ (op0);
	      real = build_unary_op (ਵਿਅੰਜਕ_LOCATION (orig_op0), REALPART_ਵਿਅੰਜਕ,
				     op0, ਸੱਚ);
	      imag = build_unary_op (ਵਿਅੰਜਕ_LOCATION (orig_op0), IMAGPART_ਵਿਅੰਜਕ,
				     op0, ਸੱਚ);
	      ਚੋਣ (ਕੋਡ)
		{
		ਹਾਲਤ MULT_ਵਿਅੰਜਕ:
		ਹਾਲਤ TRUNC_DIV_ਵਿਅੰਜਕ:
		  op1 = save_ਵਿਅੰਜਕ (op1);
		  imag = build2 (resultcode, real_type, imag, op1);
		  /* Fall through.  */
		ਹਾਲਤ PLUS_ਵਿਅੰਜਕ:
		ਹਾਲਤ MINUS_ਵਿਅੰਜਕ:
		  real = build2 (resultcode, real_type, real, op1);
		  ਰੋਕੋ;
		ਮੂਲ:
		  gcc_unreachable();
		}
	    }
	  ਨਹੀਂਤਾਂ
	    {
	      op1 = save_ਵਿਅੰਜਕ (op1);
	      real = build_unary_op (ਵਿਅੰਜਕ_LOCATION (orig_op1), REALPART_ਵਿਅੰਜਕ,
				     op1, ਸੱਚ);
	      imag = build_unary_op (ਵਿਅੰਜਕ_LOCATION (orig_op1), IMAGPART_ਵਿਅੰਜਕ,
				     op1, ਸੱਚ);
	      ਚੋਣ (ਕੋਡ)
		{
		ਹਾਲਤ MULT_ਵਿਅੰਜਕ:
		  op0 = save_ਵਿਅੰਜਕ (op0);
		  imag = build2 (resultcode, real_type, op0, imag);
		  /* Fall through.  */
		ਹਾਲਤ PLUS_ਵਿਅੰਜਕ:
		  real = build2 (resultcode, real_type, op0, real);
		  ਰੋਕੋ;
		ਹਾਲਤ MINUS_ਵਿਅੰਜਕ:
		  real = build2 (resultcode, real_type, op0, real);
		  imag = build1 (NEGATE_ਵਿਅੰਜਕ, real_type, imag);
		  ਰੋਕੋ;
		ਮੂਲ:
		  gcc_unreachable();
		}
	    }
	  ret = build2 (COMPLEX_ਵਿਅੰਜਕ, ਨਤੀਜਾ_type, real, imag);
	  ਜਾਓ return_build_ਦੁਆਧਾਰੀ_op;
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

      ਜੇ (shorten && none_complex)
	{
	  final_type = ਨਤੀਜਾ_type;
	  ਨਤੀਜਾ_type = shorten_ਦੁਆਧਾਰੀ_op (ਨਤੀਜਾ_type, op0, op1,
					   shorten == -1);
	}

      /* Shifts can be shortened if shifting right.  */

      ਜੇ (short_ਖਿਸਕਾਓ)
	{
	  ਪੂਰਨ unsigned_arg;
	  ਰੁੱਖ arg0 = get_narrower (op0, &unsigned_arg);

	  final_type = ਨਤੀਜਾ_type;

	  ਜੇ (arg0 == op0 && final_type == ਰੁੱਖ_TYPE (op0))
	    unsigned_arg = TYPE_UNSIGNED (ਰੁੱਖ_TYPE (op0));

	  ਜੇ (TYPE_PRECISION (ਰੁੱਖ_TYPE (arg0)) < TYPE_PRECISION (ਨਤੀਜਾ_type)
	      && ਰੁੱਖ_int_cst_sgn (op1) > 0
	      /* We can shorten only if the shift count is less than the
		 number of bits in the smaller type size.  */
	      && compare_ਰੁੱਖ_int (op1, TYPE_PRECISION (ਰੁੱਖ_TYPE (arg0))) < 0
	      /* We cannot drop an unsigned shift after sign-extension.  */
	      && (!TYPE_UNSIGNED (final_type) || unsigned_arg))
	    {
	      /* Do an unsigned shift if the operand was zero-extended.  */
	      ਨਤੀਜਾ_type
		= c_common_signed_or_unsigned_type (unsigned_arg,
						    ਰੁੱਖ_TYPE (arg0));
	      /* Convert value-to-be-shifted to that type.  */
	      ਜੇ (ਰੁੱਖ_TYPE (op0) != ਨਤੀਜਾ_type)
		op0 = convert (ਨਤੀਜਾ_type, op0);
	      converted = 1;
	    }
	}

      /* Comparison operations are shortened too but differently.
	 They identify themselves by setting short_compare = 1.  */

      ਜੇ (short_compare)
	{
	  /* Don't write &op0, etc., because that would prevent op0
	     from being kept in a register.
	     Instead, make copies of the our local variables and
	     pass the copies by reference, then copy them back afterward.  */
	  ਰੁੱਖ xop0 = op0, xop1 = op1, xresult_type = ਨਤੀਜਾ_type;
	  ਗਿਣਤੀ ਰੁੱਖ_ਕੋਡ_2 xresultcode = resultcode;
	  ਰੁੱਖ val
	    = shorten_compare (location, &xop0, &xop1, &xresult_type,
			       &xresultcode);

	  ਜੇ (val != NULL_ਰੁੱਖ)
	    {
	      ret = val;
	      ਜਾਓ return_build_ਦੁਆਧਾਰੀ_op;
	    }

	  op0 = xop0, op1 = xop1;
	  converted = 1;
	  resultcode = xresultcode;

	  ਜੇ (c_inhibit_evaluation_warnings == 0 && !c_ਵਿੱਚ_omp_for)
	    {
	      ਤਾਰਕਿਕ op0_maybe_const = ਸੱਚ;
	      ਤਾਰਕਿਕ op1_maybe_const = ਸੱਚ;
	      ਰੁੱਖ orig_op0_folded, orig_op1_folded;

	      ਜੇ (ਵਿੱਚ_late_ਦੁਆਧਾਰੀ_op)
		{
		  orig_op0_folded = orig_op0;
		  orig_op1_folded = orig_op1;
		}
	      ਨਹੀਂਤਾਂ
		{
		  /* Fold for the sake of possible warnings, as in
		     build_conditional_expr.  This requires the
		     "original" values to be folded, not just op0 and
		     op1.  */
		  c_inhibit_evaluation_warnings++;
		  op0 = c_fully_fold (op0, require_constant_ਮੁੱਲ,
				      &op0_maybe_const);
		  op1 = c_fully_fold (op1, require_constant_ਮੁੱਲ,
				      &op1_maybe_const);
		  c_inhibit_evaluation_warnings--;
		  orig_op0_folded = c_fully_fold (orig_op0,
						  require_constant_ਮੁੱਲ,
						  ਨਿਰਾ);
		  orig_op1_folded = c_fully_fold (orig_op1,
						  require_constant_ਮੁੱਲ,
						  ਨਿਰਾ);
		}

	      ਜੇ (warn_sign_compare)
		warn_for_sign_compare (location, orig_op0_folded,
				       orig_op1_folded, op0, op1,
				       ਨਤੀਜਾ_type, resultcode);
	      ਜੇ (!ਵਿੱਚ_late_ਦੁਆਧਾਰੀ_op && !int_operands)
		{
		  ਜੇ (!op0_maybe_const || ਰੁੱਖ_ਕੋਡ (op0) != INTEGER_CST)
		    op0 = c_wrap_maybe_const (op0, !op0_maybe_const);
		  ਜੇ (!op1_maybe_const || ਰੁੱਖ_ਕੋਡ (op1) != INTEGER_CST)
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

  ਜੇ (!ਨਤੀਜਾ_type)
    {
      /* Favor showing any expression locations that are available. */
      op_location_t oploc (location, UNKNOWN_LOCATION);
      ਦੁਆਧਾਰੀ_op_rich_location richloc (oploc, orig_op0, orig_op1, ਸੱਚ);
      ਦੁਆਧਾਰੀ_op_error (&richloc, ਕੋਡ, ਰੁੱਖ_TYPE (op0), ਰੁੱਖ_TYPE (op1));
      ਵਾਪਸ error_mark_ਗੰਢ;
    }

  ਜੇ (build_type == NULL_ਰੁੱਖ)
    {
      build_type = ਨਤੀਜਾ_type;
      ਜੇ ((type0 != orig_type0 || type1 != orig_type1)
	  && !boolean_op)
	{
	  gcc_assert (may_need_excess_precision && common);
	  semantic_ਨਤੀਜਾ_type = c_common_type (orig_type0, orig_type1);
	}
    }

  ਜੇ (!converted)
    {
      op0 = ep_convert_and_check (location, ਨਤੀਜਾ_type, op0,
				  semantic_ਨਤੀਜਾ_type);
      op1 = ep_convert_and_check (location, ਨਤੀਜਾ_type, op1,
				  semantic_ਨਤੀਜਾ_type);

      /* This can happen if one operand has a vector type, and the other
	 has a different type.  */
      ਜੇ (ਰੁੱਖ_ਕੋਡ (op0) == ERROR_MARK || ਰੁੱਖ_ਕੋਡ (op1) == ERROR_MARK)
	ਵਾਪਸ error_mark_ਗੰਢ;
    }

  ਜੇ (sanitize_flags_p ((SANITIZE_ਖਿਸਕਾਓ
			 | SANITIZE_DIVIDE
			 | SANITIZE_FLOAT_DIVIDE
			 | SANITIZE_SI_ਉਛਾਲ))
      && current_function_decl != NULL_ਰੁੱਖ
      && (doing_div_or_mod || doing_ਖਿਸਕਾਓ)
      && !require_constant_ਮੁੱਲ)
    {
      /* OP0 and/or OP1 might have side-effects.  */
      op0 = save_ਵਿਅੰਜਕ (op0);
      op1 = save_ਵਿਅੰਜਕ (op1);
      op0 = c_fully_fold (op0, ਝੂਠ, ਨਿਰਾ);
      op1 = c_fully_fold (op1, ਝੂਠ, ਨਿਰਾ);
      ਜੇ (doing_div_or_mod && (sanitize_flags_p ((SANITIZE_DIVIDE
						  | SANITIZE_FLOAT_DIVIDE
						  | SANITIZE_SI_ਉਛਾਲ))))
	instrument_ਵਿਅੰਜਕ = ubsan_instrument_division (location, op0, op1);
      ਨਹੀਂਤਾਂ ਜੇ (doing_ਖਿਸਕਾਓ && sanitize_flags_p (SANITIZE_ਖਿਸਕਾਓ))
	instrument_ਵਿਅੰਜਕ = ubsan_instrument_ਖਿਸਕਾਓ (location, ਕੋਡ, op0, op1);
    }

  /* Treat expressions in initializers specially as they can't trap.  */
  ਜੇ (int_const_or_ਉਛਾਲ)
    ret = (require_constant_ਮੁੱਲ
	   ? fold_build2_initializer_loc (location, resultcode, build_type,
					  op0, op1)
	   : fold_build2_loc (location, resultcode, build_type, op0, op1));
  ਨਹੀਂਤਾਂ
    ret = build2 (resultcode, build_type, op0, op1);
  ਜੇ (final_type != NULL_ਰੁੱਖ)
    ret = convert (final_type, ret);

 return_build_ਦੁਆਧਾਰੀ_op:
  gcc_assert (ret != error_mark_ਗੰਢ);
  ਜੇ (ਰੁੱਖ_ਕੋਡ (ret) == INTEGER_CST && !ਰੁੱਖ_ਉਛਾਲ (ret) && !int_const)
    ret = (int_operands
	   ? note_integer_operands (ret)
	   : build1 (NOP_ਵਿਅੰਜਕ, ਰੁੱਖ_TYPE (ret), ret));
  ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਕੋਡ (ret) != INTEGER_CST && int_operands
	   && !ਵਿੱਚ_late_ਦੁਆਧਾਰੀ_op)
    ret = note_integer_operands (ret);
  protected_ਸੈੱਟ_ਵਿਅੰਜਕ_location (ret, location);

  ਜੇ (instrument_ਵਿਅੰਜਕ != ਨਿਰਾ)
    ret = fold_build2 (COMPOUND_ਵਿਅੰਜਕ, ਰੁੱਖ_TYPE (ret),
		       instrument_ਵਿਅੰਜਕ, ret);

  ਜੇ (semantic_ਨਤੀਜਾ_type)
    ret = build1_loc (location, EXCESS_PRECISION_ਵਿਅੰਜਕ,
		      semantic_ਨਤੀਜਾ_type, ret);

  ਵਾਪਸ ret;
}


/* Convert EXPR to be a truth-value (type TYPE), validating its type for this
   purpose.  LOCATION is the source location for the expression.  */

ਰੁੱਖ
c_objc_common_truthvalue_conversion (location_t location, ਰੁੱਖ ਵਿਅੰਜਕ, ਰੁੱਖ type)
{
  ਤਾਰਕਿਕ int_const, int_operands;

  ਚੋਣ (ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (ਵਿਅੰਜਕ)))
    {
    ਹਾਲਤ ARRAY_TYPE:
      error_at (location, "used array that cannot be converted to pointer where scalar is required");
      ਵਾਪਸ error_mark_ਗੰਢ;

    ਹਾਲਤ ਰਿਕਾਰਡ_TYPE:
      error_at (location, "used struct type value where scalar is required");
      ਵਾਪਸ error_mark_ਗੰਢ;

    ਹਾਲਤ UNION_TYPE:
      error_at (location, "used union type value where scalar is required");
      ਵਾਪਸ error_mark_ਗੰਢ;

    ਹਾਲਤ VOID_TYPE:
      error_at (location, "void value not ignored as it ought to be");
      ਵਾਪਸ error_mark_ਗੰਢ;

    ਹਾਲਤ ਸੂਚਕ_TYPE:
      ਜੇ (reject_gcc_builtin (ਵਿਅੰਜਕ))
	ਵਾਪਸ error_mark_ਗੰਢ;
      ਰੋਕੋ;

    ਹਾਲਤ FUNCTION_TYPE:
      gcc_unreachable ();

    ਹਾਲਤ ਸਦਿਸ਼_TYPE:
      error_at (location, "used vector type where scalar is required");
      ਵਾਪਸ error_mark_ਗੰਢ;

    ਮੂਲ:
      ਰੋਕੋ;
    }

  /* Conversion of a floating constant to boolean goes through here
     and yields an integer constant expression.  Otherwise, the result
     is only an integer constant expression if the argument is.  */
  int_const = ((ਰੁੱਖ_ਕੋਡ (ਵਿਅੰਜਕ) == INTEGER_CST && !ਰੁੱਖ_ਉਛਾਲ (ਵਿਅੰਜਕ))
	       || ((ਰੁੱਖ_ਕੋਡ (ਵਿਅੰਜਕ) == REAL_CST
		    || ਰੁੱਖ_ਕੋਡ (ਵਿਅੰਜਕ) == COMPLEX_CST)
		   && (ਰੁੱਖ_ਕੋਡ (type) == BOOLEAN_TYPE
		       || (ਰੁੱਖ_ਕੋਡ (type) == ENUMERAL_TYPE
			   && ENUM_UNDERLYING_TYPE (type) != NULL_ਰੁੱਖ
			   && (ਰੁੱਖ_ਕੋਡ (ENUM_UNDERLYING_TYPE (type))
			       == BOOLEAN_TYPE)))));
  int_operands = ਵਿਅੰਜਕ_INT_CONST_OPERANDS (ਵਿਅੰਜਕ);
  ਜੇ (int_operands && ਰੁੱਖ_ਕੋਡ (ਵਿਅੰਜਕ) != INTEGER_CST)
    {
      ਵਿਅੰਜਕ = remove_c_maybe_const_ਵਿਅੰਜਕ (ਵਿਅੰਜਕ);
      ਵਿਅੰਜਕ = build2 (NE_ਵਿਅੰਜਕ, type, ਵਿਅੰਜਕ,
		     convert (ਰੁੱਖ_TYPE (ਵਿਅੰਜਕ), integer_zero_ਗੰਢ));
      ਵਿਅੰਜਕ = note_integer_operands (ਵਿਅੰਜਕ);
    }
  ਨਹੀਂਤਾਂ
    {
      /* ??? Should we also give an error for vectors rather than leaving
	 those to give errors later?  */
      ਵਿਅੰਜਕ = c_common_truthvalue_conversion (location, ਵਿਅੰਜਕ);
      ਵਿਅੰਜਕ = fold_convert_loc (location, type, ਵਿਅੰਜਕ);
    }

  ਜੇ (ਰੁੱਖ_ਕੋਡ (ਵਿਅੰਜਕ) == INTEGER_CST && int_operands && !int_const)
    {
      ਜੇ (ਰੁੱਖ_ਉਛਾਲ (ਵਿਅੰਜਕ))
	ਵਾਪਸ ਵਿਅੰਜਕ;
      ਨਹੀਂਤਾਂ
	ਵਾਪਸ note_integer_operands (ਵਿਅੰਜਕ);
    }
  ਜੇ (ਰੁੱਖ_ਕੋਡ (ਵਿਅੰਜਕ) == INTEGER_CST && !int_const)
    ਵਾਪਸ build1 (NOP_ਵਿਅੰਜਕ, ਰੁੱਖ_TYPE (ਵਿਅੰਜਕ), ਵਿਅੰਜਕ);
  ਵਾਪਸ ਵਿਅੰਜਕ;
}


/* Convert EXPR to a contained DECL, updating *TC, *TI and *SE as
   required.  */

ਰੁੱਖ
c_ਵਿਅੰਜਕ_ਮੰਜ਼ਿਲ_decl (ਰੁੱਖ ਵਿਅੰਜਕ, ਤਾਰਕਿਕ *tc ATTRIBUTE_ਅਣਵਰਤਿਆ, ਤਾਰਕਿਕ *se)
{
  ਜੇ (ਰੁੱਖ_ਕੋਡ (ਵਿਅੰਜਕ) == COMPOUND_LITERAL_ਵਿਅੰਜਕ)
    {
      ਰੁੱਖ decl = COMPOUND_LITERAL_ਵਿਅੰਜਕ_DECL (ਵਿਅੰਜਕ);
      /* Executing a compound literal inside a function reinitializes
	 it.  */
      ਜੇ (!ਰੁੱਖ_STATIC (decl))
	*se = ਸੱਚ;
      ਵਾਪਸ decl;
    }
  ਨਹੀਂਤਾਂ
    ਵਾਪਸ ਵਿਅੰਜਕ;
}

/* Generate OMP construct CODE, with BODY and CLAUSES as its compound
   statement.  LOC is the location of the construct.  */

ਰੁੱਖ
c_ਅੰਤ_omp_construct (location_t loc, ਗਿਣਤੀ ਰੁੱਖ_ਕੋਡ_2 ਕੋਡ, ਰੁੱਖ body,
			ਰੁੱਖ clauses)
{
  body = c_ਸਿਰਾ_compound_stmt (loc, body, ਸੱਚ);

  ਰੁੱਖ stmt = make_ਗੰਢ (ਕੋਡ);
  ਰੁੱਖ_TYPE (stmt) = void_type_ਗੰਢ;
  OMP_BODY (stmt) = body;
  OMP_CLAUSES (stmt) = clauses;
  ਸੈੱਟ_ਵਿਅੰਜਕ_LOCATION (stmt, loc);

  ਵਾਪਸ ਜੋੜੋ_stmt (stmt);
}

/* Generate OACC_DATA, with CLAUSES and BLOCK as its compound
   statement.  LOC is the location of the OACC_DATA.  */

ਰੁੱਖ
c_ਅੰਤ_oacc_ਅੰਕੜੇ (location_t loc, ਰੁੱਖ clauses, ਰੁੱਖ ਖੰਡ)
{
  ਰੁੱਖ stmt;

  ਖੰਡ = c_ਸਿਰਾ_compound_stmt (loc, ਖੰਡ, ਸੱਚ);

  stmt = make_ਗੰਢ (OACC_ਅੰਕੜੇ);
  ਰੁੱਖ_TYPE (stmt) = void_type_ਗੰਢ;
  OACC_ਅੰਕੜੇ_CLAUSES (stmt) = clauses;
  OACC_ਅੰਕੜੇ_BODY (stmt) = ਖੰਡ;
  ਸੈੱਟ_ਵਿਅੰਜਕ_LOCATION (stmt, loc);

  ਵਾਪਸ ਜੋੜੋ_stmt (stmt);
}

/* Generate OACC_HOST_DATA, with CLAUSES and BLOCK as its compound
   statement.  LOC is the location of the OACC_HOST_DATA.  */

ਰੁੱਖ
c_ਅੰਤ_oacc_host_ਅੰਕੜੇ (location_t loc, ਰੁੱਖ clauses, ਰੁੱਖ ਖੰਡ)
{
  ਰੁੱਖ stmt;

  ਖੰਡ = c_ਸਿਰਾ_compound_stmt (loc, ਖੰਡ, ਸੱਚ);

  stmt = make_ਗੰਢ (OACC_HOST_ਅੰਕੜੇ);
  ਰੁੱਖ_TYPE (stmt) = void_type_ਗੰਢ;
  OACC_HOST_ਅੰਕੜੇ_CLAUSES (stmt) = clauses;
  OACC_HOST_ਅੰਕੜੇ_BODY (stmt) = ਖੰਡ;
  ਸੈੱਟ_ਵਿਅੰਜਕ_LOCATION (stmt, loc);

  ਵਾਪਸ ਜੋੜੋ_stmt (stmt);
}

/* Like c_begin_compound_stmt, except force the retention of the BLOCK.  */

ਰੁੱਖ
c_begin_omp_parallel (ਖਾਲੀ)
{
  ਰੁੱਖ ਖੰਡ;

  keep_ਅਗਲਾ_level ();
  ਖੰਡ = c_begin_compound_stmt (ਸੱਚ);

  ਵਾਪਸ ਖੰਡ;
}

/* Generate OMP_PARALLEL, with CLAUSES and BLOCK as its compound
   statement.  LOC is the location of the OMP_PARALLEL.  */

ਰੁੱਖ
c_ਅੰਤ_omp_parallel (location_t loc, ਰੁੱਖ clauses, ਰੁੱਖ ਖੰਡ)
{
  ਰੁੱਖ stmt;

  ਖੰਡ = c_ਸਿਰਾ_compound_stmt (loc, ਖੰਡ, ਸੱਚ);

  stmt = make_ਗੰਢ (OMP_PARALLEL);
  ਰੁੱਖ_TYPE (stmt) = void_type_ਗੰਢ;
  OMP_PARALLEL_CLAUSES (stmt) = clauses;
  OMP_PARALLEL_BODY (stmt) = ਖੰਡ;
  ਸੈੱਟ_ਵਿਅੰਜਕ_LOCATION (stmt, loc);

  ਵਾਪਸ ਜੋੜੋ_stmt (stmt);
}

/* Like c_begin_compound_stmt, except force the retention of the BLOCK.  */

ਰੁੱਖ
c_begin_omp_task (ਖਾਲੀ)
{
  ਰੁੱਖ ਖੰਡ;

  keep_ਅਗਲਾ_level ();
  ਖੰਡ = c_begin_compound_stmt (ਸੱਚ);

  ਵਾਪਸ ਖੰਡ;
}

/* Generate OMP_TASK, with CLAUSES and BLOCK as its compound
   statement.  LOC is the location of the #pragma.  */

ਰੁੱਖ
c_ਅੰਤ_omp_task (location_t loc, ਰੁੱਖ clauses, ਰੁੱਖ ਖੰਡ)
{
  ਰੁੱਖ stmt;

  ਖੰਡ = c_ਸਿਰਾ_compound_stmt (loc, ਖੰਡ, ਸੱਚ);

  stmt = make_ਗੰਢ (OMP_TASK);
  ਰੁੱਖ_TYPE (stmt) = void_type_ਗੰਢ;
  OMP_TASK_CLAUSES (stmt) = clauses;
  OMP_TASK_BODY (stmt) = ਖੰਡ;
  ਸੈੱਟ_ਵਿਅੰਜਕ_LOCATION (stmt, loc);

  ਵਾਪਸ ਜੋੜੋ_stmt (stmt);
}

/* Generate GOMP_cancel call for #pragma omp cancel.  */

ਖਾਲੀ
c_ਅੰਤ_omp_cancel (location_t loc, ਰੁੱਖ clauses)
{
  ਰੁੱਖ fn = builtin_decl_explicit (BUILT_ਵਿੱਚ_GOMP_CANCEL);
  ਪੂਰਨ ਨਕਾਬ = 0;
  ਜੇ (omp_ਲੱਭੋ_clause (clauses, OMP_CLAUSE_PARALLEL))
    ਨਕਾਬ = 1;
  ਨਹੀਂਤਾਂ ਜੇ (omp_ਲੱਭੋ_clause (clauses, OMP_CLAUSE_FOR))
    ਨਕਾਬ = 2;
  ਨਹੀਂਤਾਂ ਜੇ (omp_ਲੱਭੋ_clause (clauses, OMP_CLAUSE_SECTIONS))
    ਨਕਾਬ = 4;
  ਨਹੀਂਤਾਂ ਜੇ (omp_ਲੱਭੋ_clause (clauses, OMP_CLAUSE_TASKGROUP))
    ਨਕਾਬ = 8;
  ਨਹੀਂਤਾਂ
    {
      error_at (loc, "%<#pragma omp cancel%> must specify one of "
		     "%<parallel%>, %<for%>, %<sections%> or %<taskgroup%> "
		     "clauses");
      ਵਾਪਸ;
    }
  ਰੁੱਖ ifc = omp_ਲੱਭੋ_clause (clauses, OMP_CLAUSE_IF);
  ਜੇ (ifc != NULL_ਰੁੱਖ)
    {
      ਜੇ (OMP_CLAUSE_IF_MODIFIER (ifc) != ERROR_MARK
	  && OMP_CLAUSE_IF_MODIFIER (ifc) != VOID_CST)
	error_at (OMP_CLAUSE_LOCATION (ifc),
		  "expected %<cancel%> %<if%> clause modifier");
      ਨਹੀਂਤਾਂ
	{
	  ਰੁੱਖ ifc2 = omp_ਲੱਭੋ_clause (OMP_CLAUSE_CHAIN (ifc), OMP_CLAUSE_IF);
	  ਜੇ (ifc2 != NULL_ਰੁੱਖ)
	    {
	      gcc_assert (OMP_CLAUSE_IF_MODIFIER (ifc) == VOID_CST
			  && OMP_CLAUSE_IF_MODIFIER (ifc2) != ERROR_MARK
			  && OMP_CLAUSE_IF_MODIFIER (ifc2) != VOID_CST);
	      error_at (OMP_CLAUSE_LOCATION (ifc2),
			"expected %<cancel%> %<if%> clause modifier");
	    }
	}

      ਰੁੱਖ type = ਰੁੱਖ_TYPE (OMP_CLAUSE_IF_ਵਿਅੰਜਕ (ifc));
      ifc = fold_build2_loc (OMP_CLAUSE_LOCATION (ifc), NE_ਵਿਅੰਜਕ,
			     boolean_type_ਗੰਢ, OMP_CLAUSE_IF_ਵਿਅੰਜਕ (ifc),
			     build_zero_cst (type));
    }
  ਨਹੀਂਤਾਂ
    ifc = boolean_true_ਗੰਢ;
  ਰੁੱਖ stmt = build_call_ਵਿਅੰਜਕ_loc (loc, fn, 2,
				   build_int_cst (integer_type_ਗੰਢ, ਨਕਾਬ),
				   ifc);
  ਜੋੜੋ_stmt (stmt);
}

/* Generate GOMP_cancellation_point call for
   #pragma omp cancellation point.  */

ਖਾਲੀ
c_ਅੰਤ_omp_cancellation_ਬਿੰਦੂ (location_t loc, ਰੁੱਖ clauses)
{
  ਰੁੱਖ fn = builtin_decl_explicit (BUILT_ਵਿੱਚ_GOMP_CANCELLATION_ਬਿੰਦੂ);
  ਪੂਰਨ ਨਕਾਬ = 0;
  ਜੇ (omp_ਲੱਭੋ_clause (clauses, OMP_CLAUSE_PARALLEL))
    ਨਕਾਬ = 1;
  ਨਹੀਂਤਾਂ ਜੇ (omp_ਲੱਭੋ_clause (clauses, OMP_CLAUSE_FOR))
    ਨਕਾਬ = 2;
  ਨਹੀਂਤਾਂ ਜੇ (omp_ਲੱਭੋ_clause (clauses, OMP_CLAUSE_SECTIONS))
    ਨਕਾਬ = 4;
  ਨਹੀਂਤਾਂ ਜੇ (omp_ਲੱਭੋ_clause (clauses, OMP_CLAUSE_TASKGROUP))
    ਨਕਾਬ = 8;
  ਨਹੀਂਤਾਂ
    {
      error_at (loc, "%<#pragma omp cancellation point%> must specify one of "
		     "%<parallel%>, %<for%>, %<sections%> or %<taskgroup%> "
		     "clauses");
      ਵਾਪਸ;
    }
  ਰੁੱਖ stmt = build_call_ਵਿਅੰਜਕ_loc (loc, fn, 1,
				   build_int_cst (integer_type_ਗੰਢ, ਨਕਾਬ));
  ਜੋੜੋ_stmt (stmt);
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

ਸਥਿਰ ਰੁੱਖ
handle_omp_array_sections_1 (ਰੁੱਖ c, ਰੁੱਖ t, vec<ਰੁੱਖ> &types,
			     ਤਾਰਕਿਕ &maybe_zero_len, ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ &ਪਹਿਲਾ_non_one,
			     ਗਿਣਤੀ c_omp_region_type ort)
{
  ਰੁੱਖ ret, ਨੀਵਾਂ_bound, ਲੰਮਾਈ, type;
  ਤਾਰਕਿਕ openacc = (ort & C_ORT_ACC) != 0;
  ਜੇ (ਰੁੱਖ_ਕੋਡ (t) != OMP_ARRAY_SECTION)
    {
      ਜੇ (error_ਸੰਕਾਰਜ_p (t))
	ਵਾਪਸ error_mark_ਗੰਢ;
      c_omp_ਪਤਾ_inspector ai (OMP_CLAUSE_LOCATION (c), t);
      ret = t;
      ਜੇ (OMP_CLAUSE_ਕੋਡ (c) != OMP_CLAUSE_AFFINITY
	  && OMP_CLAUSE_ਕੋਡ (c) != OMP_CLAUSE_DEPEND
	  && TYPE_ATOMIC (strip_array_types (ਰੁੱਖ_TYPE (t))))
	{
	  error_at (OMP_CLAUSE_LOCATION (c), "%<_Atomic%> %qE in %qs clause",
		    t, omp_clause_ਕੋਡ_name[OMP_CLAUSE_ਕੋਡ (c)]);
	  ਵਾਪਸ error_mark_ਗੰਢ;
	}
      ਜੇ (!ai.check_clause (c))
	ਵਾਪਸ error_mark_ਗੰਢ;
      ਨਹੀਂਤਾਂ ਜੇ (ai.component_access_p ()
	       && (OMP_CLAUSE_ਕੋਡ (c) == OMP_CLAUSE_MAP
		   || OMP_CLAUSE_ਕੋਡ (c) == OMP_CLAUSE_ਮੰਜ਼ਿਲ
		   || OMP_CLAUSE_ਕੋਡ (c) == OMP_CLAUSE_FROM))
	t = ai.get_ਜੜ੍ਹ_ਪਦ (ਸੱਚ);
      ਨਹੀਂਤਾਂ
	t = ai.unconverted_ref_origin ();
      ਜੇ (t == error_mark_ਗੰਢ)
	ਵਾਪਸ error_mark_ਗੰਢ;
      ਜੇ (!VAR_P (t)
	  && (ort == C_ORT_ACC || !ਵਿਅੰਜਕ_P (t))
	  && ਰੁੱਖ_ਕੋਡ (t) != PARM_DECL)
	{
	  ਜੇ (DECL_P (t))
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%qD is not a variable in %qs clause", t,
		      omp_clause_ਕੋਡ_name[OMP_CLAUSE_ਕੋਡ (c)]);
	  ਨਹੀਂਤਾਂ
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%qE is not a variable in %qs clause", t,
		      omp_clause_ਕੋਡ_name[OMP_CLAUSE_ਕੋਡ (c)]);
	  ਵਾਪਸ error_mark_ਗੰਢ;
	}
      ਨਹੀਂਤਾਂ ਜੇ (OMP_CLAUSE_ਕੋਡ (c) != OMP_CLAUSE_AFFINITY
	       && OMP_CLAUSE_ਕੋਡ (c) != OMP_CLAUSE_DEPEND
	       && TYPE_ATOMIC (ਰੁੱਖ_TYPE (t)))
	{
	  error_at (OMP_CLAUSE_LOCATION (c), "%<_Atomic%> %qD in %qs clause",
		    t, omp_clause_ਕੋਡ_name[OMP_CLAUSE_ਕੋਡ (c)]);
	  ਵਾਪਸ error_mark_ਗੰਢ;
	}
      ਨਹੀਂਤਾਂ ਜੇ (OMP_CLAUSE_ਕੋਡ (c) != OMP_CLAUSE_AFFINITY
	       && OMP_CLAUSE_ਕੋਡ (c) != OMP_CLAUSE_DEPEND
	       && VAR_P (t)
	       && DECL_THREAD_LOCAL_P (t))
	{
	  error_at (OMP_CLAUSE_LOCATION (c),
		    "%qD is threadprivate variable in %qs clause", t,
		    omp_clause_ਕੋਡ_name[OMP_CLAUSE_ਕੋਡ (c)]);
	  ਵਾਪਸ error_mark_ਗੰਢ;
	}
      ਜੇ ((OMP_CLAUSE_ਕੋਡ (c) == OMP_CLAUSE_AFFINITY
	   || OMP_CLAUSE_ਕੋਡ (c) == OMP_CLAUSE_DEPEND)
	  && TYPE_ATOMIC (ਰੁੱਖ_TYPE (t))
	  && ਸੂਚਕ_TYPE_P (ਰੁੱਖ_TYPE (t)))
	{
	  /* If the array section is pointer based and the pointer
	     itself is _Atomic qualified, we need to atomically load
	     the pointer.  */
	  ret = convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (OMP_CLAUSE_LOCATION (c),
					  ret, ਝੂਠ, ਝੂਠ);
	}
      ਵਾਪਸ ret;
    }

  ret = handle_omp_array_sections_1 (c, ਰੁੱਖ_ਸੰਕਾਰਜ (t, 0), types,
				     maybe_zero_len, ਪਹਿਲਾ_non_one, ort);
  ਜੇ (ret == error_mark_ਗੰਢ || ret == NULL_ਰੁੱਖ)
    ਵਾਪਸ ret;

  type = ਰੁੱਖ_TYPE (ret);
  ਨੀਵਾਂ_bound = ਰੁੱਖ_ਸੰਕਾਰਜ (t, 1);
  ਲੰਮਾਈ = ਰੁੱਖ_ਸੰਕਾਰਜ (t, 2);

  ਜੇ (ਨੀਵਾਂ_bound == error_mark_ਗੰਢ || ਲੰਮਾਈ == error_mark_ਗੰਢ)
    ਵਾਪਸ error_mark_ਗੰਢ;

  ਜੇ (ਨੀਵਾਂ_bound && !INTEGRAL_TYPE_P (ਰੁੱਖ_TYPE (ਨੀਵਾਂ_bound)))
    {
      error_at (OMP_CLAUSE_LOCATION (c),
		"low bound %qE of array section does not have integral type",
		ਨੀਵਾਂ_bound);
      ਵਾਪਸ error_mark_ਗੰਢ;
    }
  ਜੇ (ਲੰਮਾਈ && !INTEGRAL_TYPE_P (ਰੁੱਖ_TYPE (ਲੰਮਾਈ)))
    {
      error_at (OMP_CLAUSE_LOCATION (c),
		"length %qE of array section does not have integral type",
		ਲੰਮਾਈ);
      ਵਾਪਸ error_mark_ਗੰਢ;
    }
  ਜੇ (ਨੀਵਾਂ_bound
      && ਰੁੱਖ_ਕੋਡ (ਨੀਵਾਂ_bound) == INTEGER_CST
      && TYPE_PRECISION (ਰੁੱਖ_TYPE (ਨੀਵਾਂ_bound))
	 > TYPE_PRECISION (sizetype))
    ਨੀਵਾਂ_bound = fold_convert (sizetype, ਨੀਵਾਂ_bound);
  ਜੇ (ਲੰਮਾਈ
      && ਰੁੱਖ_ਕੋਡ (ਲੰਮਾਈ) == INTEGER_CST
      && TYPE_PRECISION (ਰੁੱਖ_TYPE (ਲੰਮਾਈ))
	 > TYPE_PRECISION (sizetype))
    ਲੰਮਾਈ = fold_convert (sizetype, ਲੰਮਾਈ);
  ਜੇ (ਨੀਵਾਂ_bound == NULL_ਰੁੱਖ)
    ਨੀਵਾਂ_bound = integer_zero_ਗੰਢ;
  ਜੇ (OMP_CLAUSE_ਕੋਡ (c) == OMP_CLAUSE_MAP
      && (OMP_CLAUSE_MAP_ਕਿਸਮ (c) == GOMP_MAP_ATTACH
	  || OMP_CLAUSE_MAP_ਕਿਸਮ (c) == GOMP_MAP_DETACH))
    {
      ਜੇ (ਲੰਮਾਈ != integer_one_ਗੰਢ)
	{
	  error_at (OMP_CLAUSE_LOCATION (c),
		    "expected single pointer in %qs clause",
		    user_omp_clause_ਕੋਡ_name (c, openacc));
	  ਵਾਪਸ error_mark_ਗੰਢ;
	}
    }
  ਜੇ (ਲੰਮਾਈ != NULL_ਰੁੱਖ)
    {
      ਜੇ (!integer_nonzerop (ਲੰਮਾਈ))
	{
	  ਜੇ (OMP_CLAUSE_ਕੋਡ (c) == OMP_CLAUSE_AFFINITY
	      || OMP_CLAUSE_ਕੋਡ (c) == OMP_CLAUSE_DEPEND
	      || OMP_CLAUSE_ਕੋਡ (c) == OMP_CLAUSE_REDUCTION
	      || OMP_CLAUSE_ਕੋਡ (c) == OMP_CLAUSE_ਵਿੱਚ_REDUCTION
	      || OMP_CLAUSE_ਕੋਡ (c) == OMP_CLAUSE_TASK_REDUCTION)
	    {
	      ਜੇ (integer_zerop (ਲੰਮਾਈ))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "zero length array section in %qs clause",
			    omp_clause_ਕੋਡ_name[OMP_CLAUSE_ਕੋਡ (c)]);
		  ਵਾਪਸ error_mark_ਗੰਢ;
		}
	    }
	  ਨਹੀਂਤਾਂ
	    maybe_zero_len = ਸੱਚ;
	}
      ਜੇ (ਪਹਿਲਾ_non_one == types.ਲੰਮਾਈ ()
	  && (ਰੁੱਖ_ਕੋਡ (ਲੰਮਾਈ) != INTEGER_CST || integer_onep (ਲੰਮਾਈ)))
	ਪਹਿਲਾ_non_one++;
    }
  ਜੇ (ਰੁੱਖ_ਕੋਡ (type) == ARRAY_TYPE)
    {
      ਜੇ (ਲੰਮਾਈ == NULL_ਰੁੱਖ
	  && (TYPE_DOMAIN (type) == NULL_ਰੁੱਖ
	      || TYPE_MAX_ਮੁੱਲ (TYPE_DOMAIN (type)) == NULL_ਰੁੱਖ))
	{
	  error_at (OMP_CLAUSE_LOCATION (c),
		    "for unknown bound array type length expression must "
		    "be specified");
	  ਵਾਪਸ error_mark_ਗੰਢ;
	}
      ਜੇ (ਰੁੱਖ_ਕੋਡ (ਨੀਵਾਂ_bound) == INTEGER_CST
	  && ਰੁੱਖ_int_cst_sgn (ਨੀਵਾਂ_bound) == -1)
	{
	  error_at (OMP_CLAUSE_LOCATION (c),
		    "negative low bound in array section in %qs clause",
		    omp_clause_ਕੋਡ_name[OMP_CLAUSE_ਕੋਡ (c)]);
	  ਵਾਪਸ error_mark_ਗੰਢ;
	}
      ਜੇ (ਲੰਮਾਈ != NULL_ਰੁੱਖ
	  && ਰੁੱਖ_ਕੋਡ (ਲੰਮਾਈ) == INTEGER_CST
	  && ਰੁੱਖ_int_cst_sgn (ਲੰਮਾਈ) == -1)
	{
	  error_at (OMP_CLAUSE_LOCATION (c),
		    "negative length in array section in %qs clause",
		    omp_clause_ਕੋਡ_name[OMP_CLAUSE_ਕੋਡ (c)]);
	  ਵਾਪਸ error_mark_ਗੰਢ;
	}
      ਜੇ (TYPE_DOMAIN (type)
	  && TYPE_MAX_ਮੁੱਲ (TYPE_DOMAIN (type))
	  && ਰੁੱਖ_ਕੋਡ (TYPE_MAX_ਮੁੱਲ (TYPE_DOMAIN (type)))
			== INTEGER_CST)
	{
	  ਰੁੱਖ ਮਾਪ
	    = fold_convert (sizetype, TYPE_MAX_ਮੁੱਲ (TYPE_DOMAIN (type)));
	  ਮਾਪ = ਮਾਪ_binop (PLUS_ਵਿਅੰਜਕ, ਮਾਪ, ਮਾਪ_one_ਗੰਢ);
	  ਜੇ (ਰੁੱਖ_ਕੋਡ (ਨੀਵਾਂ_bound) == INTEGER_CST)
	    {
	      ਜੇ (ਰੁੱਖ_int_cst_lt (ਮਾਪ, ਨੀਵਾਂ_bound))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "low bound %qE above array section size "
			    "in %qs clause", ਨੀਵਾਂ_bound,
			    omp_clause_ਕੋਡ_name[OMP_CLAUSE_ਕੋਡ (c)]);
		  ਵਾਪਸ error_mark_ਗੰਢ;
		}
	      ਜੇ (ਰੁੱਖ_int_cst_equal (ਮਾਪ, ਨੀਵਾਂ_bound))
		{
		  ਜੇ (OMP_CLAUSE_ਕੋਡ (c) == OMP_CLAUSE_AFFINITY
		      || OMP_CLAUSE_ਕੋਡ (c) == OMP_CLAUSE_DEPEND
		      || OMP_CLAUSE_ਕੋਡ (c) == OMP_CLAUSE_REDUCTION
		      || OMP_CLAUSE_ਕੋਡ (c) == OMP_CLAUSE_ਵਿੱਚ_REDUCTION
		      || OMP_CLAUSE_ਕੋਡ (c) == OMP_CLAUSE_TASK_REDUCTION)
		    {
		      error_at (OMP_CLAUSE_LOCATION (c),
				"zero length array section in %qs clause",
				omp_clause_ਕੋਡ_name[OMP_CLAUSE_ਕੋਡ (c)]);
		      ਵਾਪਸ error_mark_ਗੰਢ;
		    }
		  maybe_zero_len = ਸੱਚ;
		}
	      ਨਹੀਂਤਾਂ ਜੇ (ਲੰਮਾਈ == NULL_ਰੁੱਖ
		       && ਪਹਿਲਾ_non_one == types.ਲੰਮਾਈ ()
		       && ਰੁੱਖ_int_cst_equal
			    (TYPE_MAX_ਮੁੱਲ (TYPE_DOMAIN (type)),
			     ਨੀਵਾਂ_bound))
		ਪਹਿਲਾ_non_one++;
	    }
	  ਨਹੀਂਤਾਂ ਜੇ (ਲੰਮਾਈ == NULL_ਰੁੱਖ)
	    {
	      ਜੇ (OMP_CLAUSE_ਕੋਡ (c) != OMP_CLAUSE_AFFINITY
		  && OMP_CLAUSE_ਕੋਡ (c) != OMP_CLAUSE_DEPEND
		  && OMP_CLAUSE_ਕੋਡ (c) != OMP_CLAUSE_REDUCTION
		  && OMP_CLAUSE_ਕੋਡ (c) != OMP_CLAUSE_ਵਿੱਚ_REDUCTION
		  && OMP_CLAUSE_ਕੋਡ (c) != OMP_CLAUSE_TASK_REDUCTION)
		maybe_zero_len = ਸੱਚ;
	      ਜੇ (ਪਹਿਲਾ_non_one == types.ਲੰਮਾਈ ())
		ਪਹਿਲਾ_non_one++;
	    }
	  ਜੇ (ਲੰਮਾਈ && ਰੁੱਖ_ਕੋਡ (ਲੰਮਾਈ) == INTEGER_CST)
	    {
	      ਜੇ (ਰੁੱਖ_int_cst_lt (ਮਾਪ, ਲੰਮਾਈ))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "length %qE above array section size "
			    "in %qs clause", ਲੰਮਾਈ,
			    omp_clause_ਕੋਡ_name[OMP_CLAUSE_ਕੋਡ (c)]);
		  ਵਾਪਸ error_mark_ਗੰਢ;
		}
	      ਜੇ (ਰੁੱਖ_ਕੋਡ (ਨੀਵਾਂ_bound) == INTEGER_CST)
		{
		  ਰੁੱਖ lbpluslen
		    = ਮਾਪ_binop (PLUS_ਵਿਅੰਜਕ,
				  fold_convert (sizetype, ਨੀਵਾਂ_bound),
				  fold_convert (sizetype, ਲੰਮਾਈ));
		  ਜੇ (ਰੁੱਖ_ਕੋਡ (lbpluslen) == INTEGER_CST
		      && ਰੁੱਖ_int_cst_lt (ਮਾਪ, lbpluslen))
		    {
		      error_at (OMP_CLAUSE_LOCATION (c),
				"high bound %qE above array section size "
				"in %qs clause", lbpluslen,
				omp_clause_ਕੋਡ_name[OMP_CLAUSE_ਕੋਡ (c)]);
		      ਵਾਪਸ error_mark_ਗੰਢ;
		    }
		}
	    }
	}
      ਨਹੀਂਤਾਂ ਜੇ (ਲੰਮਾਈ == NULL_ਰੁੱਖ)
	{
	  ਜੇ (OMP_CLAUSE_ਕੋਡ (c) != OMP_CLAUSE_AFFINITY
	      && OMP_CLAUSE_ਕੋਡ (c) != OMP_CLAUSE_DEPEND
	      && OMP_CLAUSE_ਕੋਡ (c) != OMP_CLAUSE_REDUCTION
	      && OMP_CLAUSE_ਕੋਡ (c) != OMP_CLAUSE_ਵਿੱਚ_REDUCTION
	      && OMP_CLAUSE_ਕੋਡ (c) != OMP_CLAUSE_TASK_REDUCTION)
	    maybe_zero_len = ਸੱਚ;
	  ਜੇ (ਪਹਿਲਾ_non_one == types.ਲੰਮਾਈ ())
	    ਪਹਿਲਾ_non_one++;
	}

      /* For [lb:] we will need to evaluate lb more than once.  */
      ਜੇ (ਲੰਮਾਈ == NULL_ਰੁੱਖ && OMP_CLAUSE_ਕੋਡ (c) != OMP_CLAUSE_DEPEND)
	{
	  ਰੁੱਖ lb = save_ਵਿਅੰਜਕ (ਨੀਵਾਂ_bound);
	  ਜੇ (lb != ਨੀਵਾਂ_bound)
	    {
	      ਰੁੱਖ_ਸੰਕਾਰਜ (t, 1) = lb;
	      ਨੀਵਾਂ_bound = lb;
	    }
	}
    }
  ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਕੋਡ (type) == ਸੂਚਕ_TYPE)
    {
      ਜੇ (ਲੰਮਾਈ == NULL_ਰੁੱਖ)
	{
	  ਜੇ (ਰੁੱਖ_ਕੋਡ (ret) == PARM_DECL && C_ARRAY_PARAMETER (ret))
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "for array function parameter length expression "
		      "must be specified");
	  ਨਹੀਂਤਾਂ
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "for pointer type length expression must be specified");
	  ਵਾਪਸ error_mark_ਗੰਢ;
	}
      ਜੇ (ਲੰਮਾਈ != NULL_ਰੁੱਖ
	  && ਰੁੱਖ_ਕੋਡ (ਲੰਮਾਈ) == INTEGER_CST
	  && ਰੁੱਖ_int_cst_sgn (ਲੰਮਾਈ) == -1)
	{
	  error_at (OMP_CLAUSE_LOCATION (c),
		    "negative length in array section in %qs clause",
		    omp_clause_ਕੋਡ_name[OMP_CLAUSE_ਕੋਡ (c)]);
	  ਵਾਪਸ error_mark_ਗੰਢ;
	}
      /* If there is a pointer type anywhere but in the very first
	 array-section-subscript, the array section could be non-contiguous.  */
      ਜੇ (OMP_CLAUSE_ਕੋਡ (c) != OMP_CLAUSE_DEPEND
	  && OMP_CLAUSE_ਕੋਡ (c) != OMP_CLAUSE_AFFINITY
	  && ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_ਸੰਕਾਰਜ (t, 0)) == OMP_ARRAY_SECTION)
	{
	  /* If any prior dimension has a non-one length, then deem this
	     array section as non-contiguous.  */
	  ਲਈ (ਰੁੱਖ d = ਰੁੱਖ_ਸੰਕਾਰਜ (t, 0);
	       ਰੁੱਖ_ਕੋਡ (d) == OMP_ARRAY_SECTION;
	       d = ਰੁੱਖ_ਸੰਕਾਰਜ (d, 0))
	    {
	      ਰੁੱਖ d_ਲੰਮਾਈ = ਰੁੱਖ_ਸੰਕਾਰਜ (d, 2);
	      ਜੇ (d_ਲੰਮਾਈ == NULL_ਰੁੱਖ || !integer_onep (d_ਲੰਮਾਈ))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "array section is not contiguous in %qs clause",
			    omp_clause_ਕੋਡ_name[OMP_CLAUSE_ਕੋਡ (c)]);
		  ਵਾਪਸ error_mark_ਗੰਢ;
		}
	    }
	}
    }
  ਨਹੀਂਤਾਂ
    {
      error_at (OMP_CLAUSE_LOCATION (c),
		"%qE does not have pointer or array type", ret);
      ਵਾਪਸ error_mark_ਗੰਢ;
    }
  ਜੇ (OMP_CLAUSE_ਕੋਡ (c) != OMP_CLAUSE_DEPEND)
    types.ਸੁਰੱਖਿਅਤ_ਧੱਕੋ (ਰੁੱਖ_TYPE (ret));
  /* We will need to evaluate lb more than once.  */
  ਰੁੱਖ lb = save_ਵਿਅੰਜਕ (ਨੀਵਾਂ_bound);
  ਜੇ (lb != ਨੀਵਾਂ_bound)
    {
      ਰੁੱਖ_ਸੰਕਾਰਜ (t, 1) = lb;
      ਨੀਵਾਂ_bound = lb;
    }
  ret = build_array_ref (OMP_CLAUSE_LOCATION (c), ret, ਨੀਵਾਂ_bound);
  ਵਾਪਸ ret;
}

/* Handle array sections for clause C.  */

ਸਥਿਰ ਤਾਰਕਿਕ
handle_omp_array_sections (ਰੁੱਖ &c, ਗਿਣਤੀ c_omp_region_type ort)
{
  ਤਾਰਕਿਕ maybe_zero_len = ਝੂਠ;
  ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ਪਹਿਲਾ_non_one = 0;
  auto_vec<ਰੁੱਖ, 10> types;
  ਰੁੱਖ *tp = &OMP_CLAUSE_DECL (c);
  ਜੇ ((OMP_CLAUSE_ਕੋਡ (c) == OMP_CLAUSE_DEPEND
       || OMP_CLAUSE_ਕੋਡ (c) == OMP_CLAUSE_AFFINITY)
      && OMP_ITERATOR_DECL_P (*tp))
    tp = &ਰੁੱਖ_ਮੁੱਲ (*tp);
  ਰੁੱਖ ਪਹਿਲਾ = handle_omp_array_sections_1 (c, *tp, types,
					    maybe_zero_len, ਪਹਿਲਾ_non_one,
					    ort);
  ਜੇ (ਪਹਿਲਾ == error_mark_ਗੰਢ)
    ਵਾਪਸ ਸੱਚ;
  ਜੇ (ਪਹਿਲਾ == NULL_ਰੁੱਖ)
    ਵਾਪਸ ਝੂਠ;
  ਜੇ (OMP_CLAUSE_ਕੋਡ (c) == OMP_CLAUSE_DEPEND
      || OMP_CLAUSE_ਕੋਡ (c) == OMP_CLAUSE_AFFINITY)
    {
      ਰੁੱਖ t = *tp;
      ਰੁੱਖ tem = NULL_ਰੁੱਖ;
      /* Need to evaluate side effects in the length expressions
	 if any.  */
      ਜਦੋਂ (ਰੁੱਖ_ਕੋਡ (t) == ਰੁੱਖ_LIST)
	{
	  ਜੇ (ਰੁੱਖ_ਮੁੱਲ (t) && ਰੁੱਖ_SIDE_EFFECTS (ਰੁੱਖ_ਮੁੱਲ (t)))
	    {
	      ਜੇ (tem == NULL_ਰੁੱਖ)
		tem = ਰੁੱਖ_ਮੁੱਲ (t);
	      ਨਹੀਂਤਾਂ
		tem = build2 (COMPOUND_ਵਿਅੰਜਕ, ਰੁੱਖ_TYPE (tem),
			      ਰੁੱਖ_ਮੁੱਲ (t), tem);
	    }
	  t = ਰੁੱਖ_CHAIN (t);
	}
      ਜੇ (tem)
	ਪਹਿਲਾ = build2 (COMPOUND_ਵਿਅੰਜਕ, ਰੁੱਖ_TYPE (ਪਹਿਲਾ), tem, ਪਹਿਲਾ);
      ਪਹਿਲਾ = c_fully_fold (ਪਹਿਲਾ, ਝੂਠ, ਨਿਰਾ, ਸੱਚ);
      *tp = ਪਹਿਲਾ;
    }
  ਨਹੀਂਤਾਂ
    {
      ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ਅੰਕ = types.ਲੰਮਾਈ (), i;
      ਰੁੱਖ t, side_effects = NULL_ਰੁੱਖ, ਮਾਪ = NULL_ਰੁੱਖ;
      ਰੁੱਖ condition = NULL_ਰੁੱਖ;

      ਜੇ (int_ਮਾਪ_ਵਿੱਚ_ਬਾਈਟਾਂ (ਰੁੱਖ_TYPE (ਪਹਿਲਾ)) <= 0)
	maybe_zero_len = ਸੱਚ;

      ਲਈ (i = ਅੰਕ, t = OMP_CLAUSE_DECL (c); i > 0;
	   t = ਰੁੱਖ_ਸੰਕਾਰਜ (t, 0))
	{
	  ਰੁੱਖ ਨੀਵਾਂ_bound = ਰੁੱਖ_ਸੰਕਾਰਜ (t, 1);
	  ਰੁੱਖ ਲੰਮਾਈ = ਰੁੱਖ_ਸੰਕਾਰਜ (t, 2);

	  i--;
	  ਜੇ (ਨੀਵਾਂ_bound
	      && ਰੁੱਖ_ਕੋਡ (ਨੀਵਾਂ_bound) == INTEGER_CST
	      && TYPE_PRECISION (ਰੁੱਖ_TYPE (ਨੀਵਾਂ_bound))
		 > TYPE_PRECISION (sizetype))
	    ਨੀਵਾਂ_bound = fold_convert (sizetype, ਨੀਵਾਂ_bound);
	  ਜੇ (ਲੰਮਾਈ
	      && ਰੁੱਖ_ਕੋਡ (ਲੰਮਾਈ) == INTEGER_CST
	      && TYPE_PRECISION (ਰੁੱਖ_TYPE (ਲੰਮਾਈ))
		 > TYPE_PRECISION (sizetype))
	    ਲੰਮਾਈ = fold_convert (sizetype, ਲੰਮਾਈ);
	  ਜੇ (ਨੀਵਾਂ_bound == NULL_ਰੁੱਖ)
	    ਨੀਵਾਂ_bound = integer_zero_ਗੰਢ;
	  ਜੇ (!maybe_zero_len && i > ਪਹਿਲਾ_non_one)
	    {
	      ਜੇ (integer_nonzerop (ਨੀਵਾਂ_bound))
		ਜਾਓ do_warn_noncontiguous;
	      ਜੇ (ਲੰਮਾਈ != NULL_ਰੁੱਖ
		  && ਰੁੱਖ_ਕੋਡ (ਲੰਮਾਈ) == INTEGER_CST
		  && TYPE_DOMAIN (types[i])
		  && TYPE_MAX_ਮੁੱਲ (TYPE_DOMAIN (types[i]))
		  && ਰੁੱਖ_ਕੋਡ (TYPE_MAX_ਮੁੱਲ (TYPE_DOMAIN (types[i])))
		     == INTEGER_CST)
		{
		  ਰੁੱਖ ਮਾਪ;
		  ਮਾਪ = ਮਾਪ_binop (PLUS_ਵਿਅੰਜਕ,
				     TYPE_MAX_ਮੁੱਲ (TYPE_DOMAIN (types[i])),
				     ਮਾਪ_one_ਗੰਢ);
		  ਜੇ (!ਰੁੱਖ_int_cst_equal (ਲੰਮਾਈ, ਮਾਪ))
		    {
		     do_warn_noncontiguous:
		      error_at (OMP_CLAUSE_LOCATION (c),
				"array section is not contiguous in %qs "
				"clause",
				omp_clause_ਕੋਡ_name[OMP_CLAUSE_ਕੋਡ (c)]);
		      ਵਾਪਸ ਸੱਚ;
		    }
		}
	      ਜੇ (ਲੰਮਾਈ != NULL_ਰੁੱਖ
		  && ਰੁੱਖ_SIDE_EFFECTS (ਲੰਮਾਈ))
		{
		  ਜੇ (side_effects == NULL_ਰੁੱਖ)
		    side_effects = ਲੰਮਾਈ;
		  ਨਹੀਂਤਾਂ
		    side_effects = build2 (COMPOUND_ਵਿਅੰਜਕ,
					   ਰੁੱਖ_TYPE (side_effects),
					   ਲੰਮਾਈ, side_effects);
		}
	    }
	  ਨਹੀਂਤਾਂ
	    {
	      ਰੁੱਖ l;

	      ਜੇ (i > ਪਹਿਲਾ_non_one
		  && ((ਲੰਮਾਈ && integer_nonzerop (ਲੰਮਾਈ))
		      || OMP_CLAUSE_ਕੋਡ (c) == OMP_CLAUSE_REDUCTION
		      || OMP_CLAUSE_ਕੋਡ (c) == OMP_CLAUSE_ਵਿੱਚ_REDUCTION
		      || OMP_CLAUSE_ਕੋਡ (c) == OMP_CLAUSE_TASK_REDUCTION))
		ਜਾਰੀ;
	      ਜੇ (ਲੰਮਾਈ)
		l = fold_convert (sizetype, ਲੰਮਾਈ);
	      ਨਹੀਂਤਾਂ
		{
		  l = ਮਾਪ_binop (PLUS_ਵਿਅੰਜਕ,
				  TYPE_MAX_ਮੁੱਲ (TYPE_DOMAIN (types[i])),
				  ਮਾਪ_one_ਗੰਢ);
		  l = ਮਾਪ_binop (MINUS_ਵਿਅੰਜਕ, l,
				  fold_convert (sizetype, ਨੀਵਾਂ_bound));
		}
	      ਜੇ (i > ਪਹਿਲਾ_non_one)
		{
		  l = fold_build2 (NE_ਵਿਅੰਜਕ, boolean_type_ਗੰਢ, l,
				   ਮਾਪ_zero_ਗੰਢ);
		  ਜੇ (condition == NULL_ਰੁੱਖ)
		    condition = l;
		  ਨਹੀਂਤਾਂ
		    condition = fold_build2 (ਦੋਆਧਾਰੀ_ਅੰਕ_AND_ਵਿਅੰਜਕ, boolean_type_ਗੰਢ,
					     l, condition);
		}
	      ਨਹੀਂਤਾਂ ਜੇ (ਮਾਪ == NULL_ਰੁੱਖ)
		{
		  ਮਾਪ = ਮਾਪ_ਵਿੱਚ_ਬਾਈਟਾਂ (ਰੁੱਖ_TYPE (types[i]));
		  ਰੁੱਖ eltype = ਰੁੱਖ_TYPE (types[ਅੰਕ - 1]);
		  ਜਦੋਂ (ਰੁੱਖ_ਕੋਡ (eltype) == ARRAY_TYPE)
		    eltype = ਰੁੱਖ_TYPE (eltype);
		  ਜੇ (OMP_CLAUSE_ਕੋਡ (c) == OMP_CLAUSE_REDUCTION
		      || OMP_CLAUSE_ਕੋਡ (c) == OMP_CLAUSE_ਵਿੱਚ_REDUCTION
		      || OMP_CLAUSE_ਕੋਡ (c) == OMP_CLAUSE_TASK_REDUCTION)
		    {
		      ਜੇ (integer_zerop (ਮਾਪ)
			  || integer_zerop (ਮਾਪ_ਵਿੱਚ_ਬਾਈਟਾਂ (eltype)))
			{
			  error_at (OMP_CLAUSE_LOCATION (c),
				    "zero length array section in %qs clause",
				    omp_clause_ਕੋਡ_name[OMP_CLAUSE_ਕੋਡ (c)]);
			  ਵਾਪਸ error_mark_ਗੰਢ;
			}
		      ਮਾਪ = ਮਾਪ_binop (EXACT_DIV_ਵਿਅੰਜਕ, ਮਾਪ,
					 ਮਾਪ_ਵਿੱਚ_ਬਾਈਟਾਂ (eltype));
		    }
		  ਮਾਪ = ਮਾਪ_binop (MULT_ਵਿਅੰਜਕ, ਮਾਪ, l);
		  ਜੇ (condition)
		    ਮਾਪ = fold_build3 (COND_ਵਿਅੰਜਕ, sizetype, condition,
					ਮਾਪ, ਮਾਪ_zero_ਗੰਢ);
		}
	      ਨਹੀਂਤਾਂ
		ਮਾਪ = ਮਾਪ_binop (MULT_ਵਿਅੰਜਕ, ਮਾਪ, l);
	    }
	}
      ਜੇ (side_effects)
	ਮਾਪ = build2 (COMPOUND_ਵਿਅੰਜਕ, sizetype, side_effects, ਮਾਪ);
      ਜੇ (OMP_CLAUSE_ਕੋਡ (c) == OMP_CLAUSE_REDUCTION
	  || OMP_CLAUSE_ਕੋਡ (c) == OMP_CLAUSE_ਵਿੱਚ_REDUCTION
	  || OMP_CLAUSE_ਕੋਡ (c) == OMP_CLAUSE_TASK_REDUCTION)
	{
	  ਮਾਪ = ਮਾਪ_binop (MINUS_ਵਿਅੰਜਕ, ਮਾਪ, ਮਾਪ_one_ਗੰਢ);
	  ਮਾਪ = c_fully_fold (ਮਾਪ, ਝੂਠ, ਨਿਰਾ);
	  ਮਾਪ = save_ਵਿਅੰਜਕ (ਮਾਪ);
	  ਰੁੱਖ ਸੂਚਕਾਂਕ_type = build_ਸੂਚਕਾਂਕ_type (ਮਾਪ);
	  ਰੁੱਖ eltype = ਰੁੱਖ_TYPE (ਪਹਿਲਾ);
	  ਜਦੋਂ (ਰੁੱਖ_ਕੋਡ (eltype) == ARRAY_TYPE)
	    eltype = ਰੁੱਖ_TYPE (eltype);
	  ਰੁੱਖ type = c_build_array_type (eltype, ਸੂਚਕਾਂਕ_type);
	  ਰੁੱਖ ptype = c_build_ਸੂਚਕ_type (eltype);
	  ਜੇ (ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (t)) == ARRAY_TYPE)
	    t = build_fold_addr_ਵਿਅੰਜਕ (t);
	  ਰੁੱਖ t2 = build_fold_addr_ਵਿਅੰਜਕ (ਪਹਿਲਾ);
	  t2 = fold_convert_loc (OMP_CLAUSE_LOCATION (c),
				 ptrdiff_type_ਗੰਢ, t2);
	  t2 = fold_build2_loc (OMP_CLAUSE_LOCATION (c), MINUS_ਵਿਅੰਜਕ,
				ptrdiff_type_ਗੰਢ, t2,
				fold_convert_loc (OMP_CLAUSE_LOCATION (c),
						  ptrdiff_type_ਗੰਢ, t));
	  t2 = c_fully_fold (t2, ਝੂਠ, ਨਿਰਾ);
	  ਜੇ (ਰੁੱਖ_ਸਮਾਉਂਦਾ_shwi_p (t2))
	    t = build2 (MEM_REF, type, t,
			build_int_cst (ptype, ਰੁੱਖ_ਮੰਜ਼ਿਲ_shwi (t2)));
	  ਨਹੀਂਤਾਂ
	    {
	      t2 = fold_convert_loc (OMP_CLAUSE_LOCATION (c), sizetype, t2);
	      t = build2_loc (OMP_CLAUSE_LOCATION (c), ਸੂਚਕ_PLUS_ਵਿਅੰਜਕ,
			      ਰੁੱਖ_TYPE (t), t, t2);
	      t = build2 (MEM_REF, type, t, build_int_cst (ptype, 0));
	    }
	  OMP_CLAUSE_DECL (c) = t;
	  ਵਾਪਸ ਝੂਠ;
	}
      ਪਹਿਲਾ = c_fully_fold (ਪਹਿਲਾ, ਝੂਠ, ਨਿਰਾ);
      OMP_CLAUSE_DECL (c) = ਪਹਿਲਾ;
      ਜੇ (OMP_CLAUSE_ਕੋਡ (c) == OMP_CLAUSE_HAS_DEVICE_ADDR)
	ਵਾਪਸ ਝੂਠ;
      /* Don't set OMP_CLAUSE_SIZE for bare attach/detach clauses.  */
      ਜੇ (OMP_CLAUSE_ਕੋਡ (c) != OMP_CLAUSE_MAP
	  || (OMP_CLAUSE_MAP_ਕਿਸਮ (c) != GOMP_MAP_ATTACH
	      && OMP_CLAUSE_MAP_ਕਿਸਮ (c) != GOMP_MAP_DETACH
	      && OMP_CLAUSE_MAP_ਕਿਸਮ (c) != GOMP_MAP_FORCE_DETACH))
	{
	  ਜੇ (ਮਾਪ)
	    ਮਾਪ = c_fully_fold (ਮਾਪ, ਝੂਠ, ਨਿਰਾ);
	  OMP_CLAUSE_ਮਾਪ (c) = ਮਾਪ;
	}

      ਜੇ (OMP_CLAUSE_ਕੋਡ (c) != OMP_CLAUSE_MAP)
	ਵਾਪਸ ਝੂਠ;

      auto_vec<omp_addr_token *, 10> addr_ਟੋਕਨ;

      ਜੇ (!omp_parse_ਵਿਅੰਜਕ (addr_ਟੋਕਨ, ਪਹਿਲਾ))
	ਵਾਪਸ ਸੱਚ;

      c_omp_ਪਤਾ_inspector ai (OMP_CLAUSE_LOCATION (c), t);

      ਰੁੱਖ nc = ai.expand_map_clause (c, ਪਹਿਲਾ, addr_ਟੋਕਨ, ort);
      ਜੇ (nc != error_mark_ਗੰਢ)
	{
	  ਵਰਤੋਂ ਨਾਮਾਕਾਸ਼ omp_addr_tokenizer;

	  ਜੇ (ai.maybe_zero_ਲੰਮਾਈ_array_section (c))
	    OMP_CLAUSE_MAP_MAYBE_ZERO_ਲੰਮਾਈ_ARRAY_SECTION (c) = 1;

	  /* !!! If we're accessing a base decl via chained access
	     methods (e.g. multiple indirections), duplicate clause
	     detection won't work properly.  Skip it in that case.  */
	  ਜੇ ((addr_ਟੋਕਨ[0]->type == STRUCTURE_ਅਧਾਰ
	       || addr_ਟੋਕਨ[0]->type == ARRAY_ਅਧਾਰ)
	      && addr_ਟੋਕਨ[0]->u.structure_ਅਧਾਰ_ਕਿਸਮ == ਅਧਾਰ_DECL
	      && addr_ਟੋਕਨ[1]->type == ACCESS_ਵਿਧੀ
	      && omp_access_chain_p (addr_ਟੋਕਨ, 1))
	    c = nc;

	  ਵਾਪਸ ਝੂਠ;
	}
    }
  ਵਾਪਸ ਝੂਠ;
}

/* Helper function of finish_omp_clauses.  Clone STMT as if we were making
   an inline call.  But, remap
   the OMP_DECL1 VAR_DECL (omp_out resp. omp_orig) to PLACEHOLDER
   and OMP_DECL2 VAR_DECL (omp_in resp. omp_priv) to DECL.  */

ਸਥਿਰ ਰੁੱਖ
c_clone_omp_udr (ਰੁੱਖ stmt, ਰੁੱਖ omp_decl1, ਰੁੱਖ omp_decl2,
		 ਰੁੱਖ decl, ਰੁੱਖ placeholder)
{
  copy_body_ਅੰਕੜੇ id;
  hash_map<ਰੁੱਖ, ਰੁੱਖ> decl_map;

  decl_map.put (omp_decl1, placeholder);
  decl_map.put (omp_decl2, decl);
  memset (&id, 0, ਆਕਾਰ (id));
  id.src_fn = DECL_CONTEXT (omp_decl1);
  id.dst_fn = current_function_decl;
  id.src_cfun = DECL_STRUCT_FUNCTION (id.src_fn);
  id.decl_map = &decl_map;

  id.copy_decl = copy_decl_no_change;
  id.transform_call_ਗ੍ਰਾਫ_ਕਿਨਾਰੇ = CB_CGE_DUPLICATE;
  id.transform_new_cfg = ਸੱਚ;
  id.transform_return_ਮੰਜ਼ਿਲ_modify = ਝੂਠ;
  id.eh_lp_nr = 0;
  walk_ਰੁੱਖ (&stmt, copy_ਰੁੱਖ_body_r, &id, ਨਿਰਾ);
  ਵਾਪਸ stmt;
}

/* Helper function of c_finish_omp_clauses, called via walk_tree.
   Find OMP_CLAUSE_PLACEHOLDER (passed in DATA) in *TP.  */

ਸਥਿਰ ਰੁੱਖ
c_ਲੱਭੋ_omp_placeholder_r (ਰੁੱਖ *tp, ਪੂਰਨ *, ਖਾਲੀ *ਅੰਕੜੇ)
{
  ਜੇ (*tp == (ਰੁੱਖ) ਅੰਕੜੇ)
    ਵਾਪਸ *tp;
  ਵਾਪਸ NULL_ਰੁੱਖ;
}

/* Similarly, but also walk aggregate fields.  */

ਬਣਤਰ c_ਲੱਭੋ_omp_var_s { ਰੁੱਖ var; hash_ਸੈੱਟ<ਰੁੱਖ> *pset; };

ਸਥਿਰ ਰੁੱਖ
c_ਲੱਭੋ_omp_var_r (ਰੁੱਖ *tp, ਪੂਰਨ *, ਖਾਲੀ *ਅੰਕੜੇ)
{
  ਜੇ (*tp == ((ਬਣਤਰ c_ਲੱਭੋ_omp_var_s *) ਅੰਕੜੇ)->var)
    ਵਾਪਸ *tp;
  ਜੇ (ਰਿਕਾਰਡ_OR_UNION_TYPE_P (*tp))
    {
      ਰੁੱਖ ਖੇਤਰ_2;
      hash_ਸੈੱਟ<ਰੁੱਖ> *pset = ((ਬਣਤਰ c_ਲੱਭੋ_omp_var_s *) ਅੰਕੜੇ)->pset;

      ਲਈ (ਖੇਤਰ_2 = TYPE_FIELDS (*tp); ਖੇਤਰ_2;
	   ਖੇਤਰ_2 = DECL_CHAIN (ਖੇਤਰ_2))
	ਜੇ (ਰੁੱਖ_ਕੋਡ (ਖੇਤਰ_2) == ਖੇਤਰ_DECL)
	  {
	    ਰੁੱਖ ret = walk_ਰੁੱਖ (&DECL_ਖੇਤਰ_ਵਿੱਥ (ਖੇਤਰ_2),
				  c_ਲੱਭੋ_omp_var_r, ਅੰਕੜੇ, pset);
	    ਜੇ (ret)
	      ਵਾਪਸ ret;
	    ret = walk_ਰੁੱਖ (&DECL_ਮਾਪ (ਖੇਤਰ_2), c_ਲੱਭੋ_omp_var_r, ਅੰਕੜੇ, pset);
	    ਜੇ (ret)
	      ਵਾਪਸ ret;
	    ret = walk_ਰੁੱਖ (&DECL_ਮਾਪ_UNIT (ਖੇਤਰ_2), c_ਲੱਭੋ_omp_var_r, ਅੰਕੜੇ,
			     pset);
	    ਜੇ (ret)
	      ਵਾਪਸ ret;
	    ret = walk_ਰੁੱਖ (&ਰੁੱਖ_TYPE (ਖੇਤਰ_2), c_ਲੱਭੋ_omp_var_r, ਅੰਕੜੇ, pset);
	    ਜੇ (ret)
	      ਵਾਪਸ ret;
	  }
    }
  ਨਹੀਂਤਾਂ ਜੇ (INTEGRAL_TYPE_P (*tp))
    ਵਾਪਸ walk_ਰੁੱਖ (&TYPE_MAX_ਮੁੱਲ (*tp), c_ਲੱਭੋ_omp_var_r, ਅੰਕੜੇ,
		      ((ਬਣਤਰ c_ਲੱਭੋ_omp_var_s *) ਅੰਕੜੇ)->pset);
  ਵਾਪਸ NULL_ਰੁੱਖ;
}

/* Finish OpenMP iterators ITER.  Return true if they are erroneous
   and clauses containing them should be removed.  */

ਸਥਿਰ ਤਾਰਕਿਕ
c_omp_ਅੰਤ_iterators (ਰੁੱਖ iter)
{
  ਤਾਰਕਿਕ ret = ਝੂਠ;
  ਲਈ (ਰੁੱਖ it = iter; it; it = ਰੁੱਖ_CHAIN (it))
    {
      ਰੁੱਖ var = OMP_ITERATOR_VAR (it);
      ਰੁੱਖ begin = OMP_ITERATOR_BEGIN (it);
      ਰੁੱਖ ਸਿਰਾ = OMP_ITERATOR_ਸਿਰਾ (it);
      ਰੁੱਖ ਕਦਮ = OMP_ITERATOR_ਕਦਮ (it);
      ਰੁੱਖ orig_ਕਦਮ;
      ਰੁੱਖ type = ਰੁੱਖ_TYPE (var);
      location_t loc = DECL_ਸਰੋਤ_LOCATION (var);
      ਜੇ (type == error_mark_ਗੰਢ)
	{
	  ret = ਸੱਚ;
	  ਜਾਰੀ;
	}
      ਜੇ (!INTEGRAL_TYPE_P (type) && !ਸੂਚਕ_TYPE_P (type))
	{
	  error_at (loc, "iterator %qD has neither integral nor pointer type",
		    var);
	  ret = ਸੱਚ;
	  ਜਾਰੀ;
	}
      ਨਹੀਂਤਾਂ ਜੇ (TYPE_ATOMIC (type))
	{
	  error_at (loc, "iterator %qD has %<_Atomic%> qualified type", var);
	  ret = ਸੱਚ;
	  ਜਾਰੀ;
	}
      ਨਹੀਂਤਾਂ ਜੇ (TYPE_READONLY (type))
	{
	  error_at (loc, "iterator %qD has const qualified type", var);
	  ret = ਸੱਚ;
	  ਜਾਰੀ;
	}
      ਨਹੀਂਤਾਂ ਜੇ (ਕਦਮ == error_mark_ਗੰਢ
	       || ਰੁੱਖ_TYPE (ਕਦਮ) == error_mark_ਗੰਢ)
	{
	  ret = ਸੱਚ;
	  ਜਾਰੀ;
	}
      ਨਹੀਂਤਾਂ ਜੇ (!INTEGRAL_TYPE_P (ਰੁੱਖ_TYPE (ਕਦਮ)))
	{
	  error_at (ਵਿਅੰਜਕ_LOC_OR_LOC (ਕਦਮ, loc),
		    "iterator step with non-integral type");
	  ret = ਸੱਚ;
	  ਜਾਰੀ;
	}
      begin = c_fully_fold (build_c_cast (loc, type, begin), ਝੂਠ, ਨਿਰਾ);
      ਸਿਰਾ = c_fully_fold (build_c_cast (loc, type, ਸਿਰਾ), ਝੂਠ, ਨਿਰਾ);
      orig_ਕਦਮ = save_ਵਿਅੰਜਕ (c_fully_fold (ਕਦਮ, ਝੂਠ, ਨਿਰਾ));
      ਰੁੱਖ stype = ਸੂਚਕ_TYPE_P (type) ? sizetype : type;
      ਕਦਮ = c_fully_fold (build_c_cast (loc, stype, orig_ਕਦਮ), ਝੂਠ, ਨਿਰਾ);
      ਜੇ (ਸੂਚਕ_TYPE_P (type))
	{
	  begin = save_ਵਿਅੰਜਕ (begin);
	  ਕਦਮ = ਸੂਚਕ_int_ਜੋੜ (loc, PLUS_ਵਿਅੰਜਕ, begin, ਕਦਮ);
	  ਕਦਮ = fold_build2_loc (loc, MINUS_ਵਿਅੰਜਕ, sizetype,
				  fold_convert (sizetype, ਕਦਮ),
				  fold_convert (sizetype, begin));
	  ਕਦਮ = fold_convert (ssizetype, ਕਦਮ);
	}
      ਜੇ (integer_zerop (ਕਦਮ))
	{
	  error_at (loc, "iterator %qD has zero step", var);
	  ret = ਸੱਚ;
	  ਜਾਰੀ;
	}

      ਜੇ (begin == error_mark_ਗੰਢ
	  || ਸਿਰਾ == error_mark_ਗੰਢ
	  || ਕਦਮ == error_mark_ਗੰਢ
	  || orig_ਕਦਮ == error_mark_ਗੰਢ)
	{
	  ret = ਸੱਚ;
	  ਜਾਰੀ;
	}
      hash_ਸੈੱਟ<ਰੁੱਖ> pset;
      ਰੁੱਖ it2;
      ਲਈ (it2 = ਰੁੱਖ_CHAIN (it); it2; it2 = ਰੁੱਖ_CHAIN (it2))
	{
	  ਰੁੱਖ var2 = OMP_ITERATOR_VAR (it2);
	  ਰੁੱਖ begin2 = OMP_ITERATOR_BEGIN (it2);
	  ਰੁੱਖ end2 = OMP_ITERATOR_ਸਿਰਾ (it2);
	  ਰੁੱਖ step2 = OMP_ITERATOR_ਕਦਮ (it2);
	  ਰੁੱਖ type2 = ਰੁੱਖ_TYPE (var2);
	  location_t loc2 = DECL_ਸਰੋਤ_LOCATION (var2);
	  ਬਣਤਰ c_ਲੱਭੋ_omp_var_s ਅੰਕੜੇ = { var, &pset };
	  ਜੇ (walk_ਰੁੱਖ (&type2, c_ਲੱਭੋ_omp_var_r, &ਅੰਕੜੇ, &pset))
	    {
	      error_at (loc2,
			"type of iterator %qD refers to outer iterator %qD",
			var2, var);
	      ਰੋਕੋ;
	    }
	  ਨਹੀਂਤਾਂ ਜੇ (walk_ਰੁੱਖ (&begin2, c_ਲੱਭੋ_omp_var_r, &ਅੰਕੜੇ, &pset))
	    {
	      error_at (ਵਿਅੰਜਕ_LOC_OR_LOC (begin2, loc2),
			"begin expression refers to outer iterator %qD", var);
	      ਰੋਕੋ;
	    }
	  ਨਹੀਂਤਾਂ ਜੇ (walk_ਰੁੱਖ (&end2, c_ਲੱਭੋ_omp_var_r, &ਅੰਕੜੇ, &pset))
	    {
	      error_at (ਵਿਅੰਜਕ_LOC_OR_LOC (end2, loc2),
			"end expression refers to outer iterator %qD", var);
	      ਰੋਕੋ;
	    }
	  ਨਹੀਂਤਾਂ ਜੇ (walk_ਰੁੱਖ (&step2, c_ਲੱਭੋ_omp_var_r, &ਅੰਕੜੇ, &pset))
	    {
	      error_at (ਵਿਅੰਜਕ_LOC_OR_LOC (step2, loc2),
			"step expression refers to outer iterator %qD", var);
	      ਰੋਕੋ;
	    }
	}
      ਜੇ (it2)
	{
	  ret = ਸੱਚ;
	  ਜਾਰੀ;
	}
      OMP_ITERATOR_BEGIN (it) = begin;
      OMP_ITERATOR_ਸਿਰਾ (it) = ਸਿਰਾ;
      OMP_ITERATOR_ਕਦਮ (it) = ਕਦਮ;
      OMP_ITERATOR_ORIG_ਕਦਮ (it) = orig_ਕਦਮ;
    }
  ਵਾਪਸ ret;
}

/* Ensure that pointers are used in OpenACC attach and detach clauses.
   Return true if an error has been detected.  */

ਸਥਿਰ ਤਾਰਕਿਕ
c_oacc_check_attachments (ਰੁੱਖ c)
{
  ਜੇ (OMP_CLAUSE_ਕੋਡ (c) != OMP_CLAUSE_MAP)
    ਵਾਪਸ ਝੂਠ;

  /* OpenACC attach / detach clauses must be pointers.  */
  ਜੇ (OMP_CLAUSE_MAP_ਕਿਸਮ (c) == GOMP_MAP_ATTACH
      || OMP_CLAUSE_MAP_ਕਿਸਮ (c) == GOMP_MAP_DETACH)
    {
      ਰੁੱਖ t = OMP_CLAUSE_DECL (c);

      ਜਦੋਂ (ਰੁੱਖ_ਕੋਡ (t) == OMP_ARRAY_SECTION)
	t = ਰੁੱਖ_ਸੰਕਾਰਜ (t, 0);

      ਜੇ (ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (t)) != ਸੂਚਕ_TYPE)
	{
	  error_at (OMP_CLAUSE_LOCATION (c), "expected pointer in %qs clause",
		    user_omp_clause_ਕੋਡ_name (c, ਸੱਚ));
	  ਵਾਪਸ ਸੱਚ;
	}
    }

  ਵਾਪਸ ਝੂਠ;
}

/* For all elements of CLAUSES, validate them against their constraints.
   Remove any elements from the list that are invalid.  */

ਰੁੱਖ
c_ਅੰਤ_omp_clauses (ਰੁੱਖ clauses, ਗਿਣਤੀ c_omp_region_type ort)
{
  bitmap_ਸਿਰ generic_ਸਿਰ, firstprivate_ਸਿਰ, lastprivate_ਸਿਰ;
  bitmap_ਸਿਰ aligned_ਸਿਰ, map_ਸਿਰ, map_ਖੇਤਰ_ਸਿਰ, map_firstprivate_ਸਿਰ;
  bitmap_ਸਿਰ oacc_reduction_ਸਿਰ, is_on_device_ਸਿਰ;
  ਰੁੱਖ c, t, type, *pc;
  ਰੁੱਖ simdlen = NULL_ਰੁੱਖ, safelen = NULL_ਰੁੱਖ;
  ਤਾਰਕਿਕ branch_ਵੇਖਿਆ = ਝੂਠ;
  ਤਾਰਕਿਕ copyprivate_ਵੇਖਿਆ = ਝੂਠ;
  ਤਾਰਕਿਕ mergeable_ਵੇਖਿਆ = ਝੂਠ;
  ਰੁੱਖ *detach_ਵੇਖਿਆ = ਨਿਰਾ;
  ਤਾਰਕਿਕ ਰੇਖਿਕ_variable_ਕਦਮ_check = ਝੂਠ;
  ਰੁੱਖ *nowait_clause = ਨਿਰਾ;
  ਰੁੱਖ *grainsize_ਵੇਖਿਆ = ਨਿਰਾ;
  ਤਾਰਕਿਕ ਅੰਕ_tasks_ਵੇਖਿਆ = ਝੂਠ;
  ਰੁੱਖ ordered_clause = NULL_ਰੁੱਖ;
  ਰੁੱਖ ਸਮਾਂ_ਸਾਰਣੀ_clause = NULL_ਰੁੱਖ;
  ਤਾਰਕਿਕ oacc_async = ਝੂਠ;
  ਰੁੱਖ ਆਖਰੀ_iterators = NULL_ਰੁੱਖ;
  ਤਾਰਕਿਕ ਆਖਰੀ_iterators_remove = ਝੂਠ;
  ਰੁੱਖ *nogroup_ਵੇਖਿਆ = ਨਿਰਾ;
  ਰੁੱਖ *ਕ੍ਰਮ_clause = ਨਿਰਾ;
  /* 1 if normal/task reduction has been seen, -1 if inscan reduction
     has been seen, -2 if mixed inscan/normal reduction diagnosed.  */
  ਪੂਰਨ reduction_ਵੇਖਿਆ = 0;
  ਤਾਰਕਿਕ allocate_ਵੇਖਿਆ = ਝੂਠ;
  ਤਾਰਕਿਕ implicit_moved = ਝੂਠ;
  ਤਾਰਕਿਕ ਨਿਸ਼ਾਨਾ_ਵਿੱਚ_reduction_ਵੇਖਿਆ = ਝੂਠ;
  ਰੁੱਖ *ਭਰਿਆ_ਵੇਖਿਆ = ਨਿਰਾ;
  ਤਾਰਕਿਕ partial_ਵੇਖਿਆ = ਝੂਠ;
  ਤਾਰਕਿਕ openacc = (ort & C_ORT_ACC) != 0;
  ਤਾਰਕਿਕ init_ਵੇਖਿਆ = ਝੂਠ;
  ਤਾਰਕਿਕ init_use_destroy_ਵੇਖਿਆ = ਝੂਠ;
  ਰੁੱਖ init_no_targetsync_clause = NULL_ਰੁੱਖ;
  ਰੁੱਖ depend_clause = NULL_ਰੁੱਖ;

  ਜੇ (!openacc)
    clauses = omp_remove_duplicate_maps (clauses, ਸੱਚ);

  bitmap_obstack_initialize (ਨਿਰਾ);
  bitmap_initialize (&generic_ਸਿਰ, &bitmap_default_obstack);
  bitmap_initialize (&firstprivate_ਸਿਰ, &bitmap_default_obstack);
  bitmap_initialize (&lastprivate_ਸਿਰ, &bitmap_default_obstack);
  bitmap_initialize (&aligned_ਸਿਰ, &bitmap_default_obstack);
  /* If ort == C_ORT_OMP_DECLARE_SIMD used as uniform_head instead.  */
  bitmap_initialize (&map_ਸਿਰ, &bitmap_default_obstack);
  bitmap_initialize (&map_ਖੇਤਰ_ਸਿਰ, &bitmap_default_obstack);
  bitmap_initialize (&map_firstprivate_ਸਿਰ, &bitmap_default_obstack);
  /* If ort == C_ORT_OMP used as nontemporal_head or use_device_xxx_head
     instead and for ort == C_ORT_OMP_TARGET used as in_reduction_head.  */
  bitmap_initialize (&oacc_reduction_ਸਿਰ, &bitmap_default_obstack);
  bitmap_initialize (&is_on_device_ਸਿਰ, &bitmap_default_obstack);

  ਜੇ (openacc)
    ਲਈ (c = clauses; c; c = OMP_CLAUSE_CHAIN (c))
      ਜੇ (OMP_CLAUSE_ਕੋਡ (c) == OMP_CLAUSE_ASYNC)
	{
	  oacc_async = ਸੱਚ;
	  ਰੋਕੋ;
	}

  ਰੁੱਖ *grp_ਸ਼ੁਰੂ_p = ਨਿਰਾ, grp_sentinel = NULL_ਰੁੱਖ;

  ਲਈ (pc = &clauses, c = clauses; c ; c = *pc)
    {
      ਤਾਰਕਿਕ remove = ਝੂਠ;
      ਤਾਰਕਿਕ need_complete = ਝੂਠ;
      ਤਾਰਕਿਕ need_implicitly_determined = ਝੂਠ;

      /* We've reached the end of a list of expanded nodes.  Reset the group
	 start pointer.  */
      ਜੇ (c == grp_sentinel)
	{
	  ਜੇ (grp_ਸ਼ੁਰੂ_p
	      && OMP_CLAUSE_HAS_ITERATORS (*grp_ਸ਼ੁਰੂ_p))
	    ਲਈ (ਰੁੱਖ gc = *grp_ਸ਼ੁਰੂ_p; gc != grp_sentinel;
		 gc = OMP_CLAUSE_CHAIN (gc))
	      OMP_CLAUSE_ITERATORS (gc) = OMP_CLAUSE_ITERATORS (*grp_ਸ਼ੁਰੂ_p);
	  grp_ਸ਼ੁਰੂ_p = ਨਿਰਾ;
	}

      ਚੋਣ (OMP_CLAUSE_ਕੋਡ (c))
	{
	ਹਾਲਤ OMP_CLAUSE_SHARED:
	  need_implicitly_determined = ਸੱਚ;
	  ਜਾਓ check_dup_generic;

	ਹਾਲਤ OMP_CLAUSE_ਨਿੱਜੀ:
	  need_complete = ਸੱਚ;
	  need_implicitly_determined = ਸੱਚ;
	  ਜਾਓ check_dup_generic;

	ਹਾਲਤ OMP_CLAUSE_REDUCTION:
	  ਜੇ (reduction_ਵੇਖਿਆ == 0)
	    reduction_ਵੇਖਿਆ = OMP_CLAUSE_REDUCTION_INSCAN (c) ? -1 : 1;
	  ਨਹੀਂਤਾਂ ਜੇ (reduction_ਵੇਖਿਆ != -2
		   && reduction_ਵੇਖਿਆ != (OMP_CLAUSE_REDUCTION_INSCAN (c)
					 ? -1 : 1))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<inscan%> and non-%<inscan%> %<reduction%> clauses "
			"on the same construct");
	      reduction_ਵੇਖਿਆ = -2;
	    }
	  /* FALLTHRU */
	ਹਾਲਤ OMP_CLAUSE_ਵਿੱਚ_REDUCTION:
	ਹਾਲਤ OMP_CLAUSE_TASK_REDUCTION:
	  need_implicitly_determined = ਸੱਚ;
	  t = OMP_CLAUSE_DECL (c);
	  ਜੇ (ਰੁੱਖ_ਕੋਡ (t) == OMP_ARRAY_SECTION)
	    {
	      ਜੇ (handle_omp_array_sections (c, ort))
		{
		  remove = ਸੱਚ;
		  ਰੋਕੋ;
		}

	      t = OMP_CLAUSE_DECL (c);
	      ਜੇ (OMP_CLAUSE_ਕੋਡ (c) == OMP_CLAUSE_REDUCTION
		  && OMP_CLAUSE_REDUCTION_INSCAN (c))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%<inscan%> %<reduction%> clause with array "
			    "section");
		  remove = ਸੱਚ;
		  ਰੋਕੋ;
		}
	    }
	  t = require_complete_type (OMP_CLAUSE_LOCATION (c), t);
	  ਜੇ (t == error_mark_ਗੰਢ)
	    {
	      remove = ਸੱਚ;
	      ਰੋਕੋ;
	    }
	  ਜੇ (oacc_async)
	    c_mark_addressable (t);
	  type = ਰੁੱਖ_TYPE (t);
	  ਜੇ (ਰੁੱਖ_ਕੋਡ (t) == MEM_REF)
	    type = ਰੁੱਖ_TYPE (type);
	  ਜੇ (ਰੁੱਖ_ਕੋਡ (type) == ARRAY_TYPE)
	    {
	      ਰੁੱਖ oatype = type;
	      gcc_assert (ਰੁੱਖ_ਕੋਡ (t) != MEM_REF);
	      ਜਦੋਂ (ਰੁੱਖ_ਕੋਡ (type) == ARRAY_TYPE)
		type = ਰੁੱਖ_TYPE (type);
	      ਜੇ (integer_zerop (TYPE_ਮਾਪ_UNIT (type)))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD in %<reduction%> clause is a zero size array",
			    t);
		  remove = ਸੱਚ;
		  ਰੋਕੋ;
		}
	      ਰੁੱਖ ਮਾਪ = ਮਾਪ_binop (EXACT_DIV_ਵਿਅੰਜਕ, TYPE_ਮਾਪ_UNIT (oatype),
				      TYPE_ਮਾਪ_UNIT (type));
	      ਜੇ (integer_zerop (ਮਾਪ))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD in %<reduction%> clause is a zero size array",
			    t);
		  remove = ਸੱਚ;
		  ਰੋਕੋ;
		}
	      ਮਾਪ = ਮਾਪ_binop (MINUS_ਵਿਅੰਜਕ, ਮਾਪ, ਮਾਪ_one_ਗੰਢ);
	      ਮਾਪ = save_ਵਿਅੰਜਕ (ਮਾਪ);
	      ਰੁੱਖ ਸੂਚਕਾਂਕ_type = build_ਸੂਚਕਾਂਕ_type (ਮਾਪ);
	      ਰੁੱਖ atype = c_build_array_type (TYPE_MAIN_VARIANT (type),
					       ਸੂਚਕਾਂਕ_type);
	      atype = c_build_qualified_type (atype, TYPE_QUALS (type));
	      ਰੁੱਖ ptype = c_build_ਸੂਚਕ_type (type);
	      ਜੇ (ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (t)) == ARRAY_TYPE)
		t = build_fold_addr_ਵਿਅੰਜਕ (t);
	      t = build2 (MEM_REF, atype, t, build_int_cst (ptype, 0));
	      OMP_CLAUSE_DECL (c) = t;
	    }
	  ਜੇ (TYPE_ATOMIC (type))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<_Atomic%> %qE in %<reduction%> clause", t);
	      remove = ਸੱਚ;
	      ਰੋਕੋ;
	    }
	  ਜੇ (OMP_CLAUSE_ਕੋਡ (c) != OMP_CLAUSE_REDUCTION
	      || OMP_CLAUSE_REDUCTION_TASK (c))
	    {
	      /* Disallow zero sized or potentially zero sized task
		 reductions.  */
	      ਜੇ (integer_zerop (TYPE_ਮਾਪ_UNIT (type)))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "zero sized type %qT in %qs clause", type,
			    omp_clause_ਕੋਡ_name[OMP_CLAUSE_ਕੋਡ (c)]);
		  remove = ਸੱਚ;
		  ਰੋਕੋ;
		}
	      ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਕੋਡ (TYPE_ਮਾਪ_UNIT (type)) != INTEGER_CST)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "variable sized type %qT in %qs clause", type,
			    omp_clause_ਕੋਡ_name[OMP_CLAUSE_ਕੋਡ (c)]);
		  remove = ਸੱਚ;
		  ਰੋਕੋ;
		}
	    }
	  ਜੇ (OMP_CLAUSE_REDUCTION_PLACEHOLDER (c) == NULL_ਰੁੱਖ
	      && (FLOAT_TYPE_P (type)
		  || ਰੁੱਖ_ਕੋਡ (type) == COMPLEX_TYPE))
	    {
	      ਗਿਣਤੀ ਰੁੱਖ_ਕੋਡ_2 r_ਕੋਡ = OMP_CLAUSE_REDUCTION_ਕੋਡ (c);
	      ਅਚਲ ਅੱਖਰ *r_name = ਨਿਰਾ;

	      ਚੋਣ (r_ਕੋਡ)
		{
		ਹਾਲਤ PLUS_ਵਿਅੰਜਕ:
		ਹਾਲਤ MULT_ਵਿਅੰਜਕ:
		ਹਾਲਤ MINUS_ਵਿਅੰਜਕ:
		ਹਾਲਤ TRUTH_ANDIF_ਵਿਅੰਜਕ:
		ਹਾਲਤ TRUTH_ORIF_ਵਿਅੰਜਕ:
		  ਰੋਕੋ;
		ਹਾਲਤ MIN_ਵਿਅੰਜਕ:
		  ਜੇ (ਰੁੱਖ_ਕੋਡ (type) == COMPLEX_TYPE)
		    r_name = "min";
		  ਰੋਕੋ;
		ਹਾਲਤ MAX_ਵਿਅੰਜਕ:
		  ਜੇ (ਰੁੱਖ_ਕੋਡ (type) == COMPLEX_TYPE)
		    r_name = "max";
		  ਰੋਕੋ;
		ਹਾਲਤ ਦੋਆਧਾਰੀ_ਅੰਕ_AND_ਵਿਅੰਜਕ:
		  r_name = "&";
		  ਰੋਕੋ;
		ਹਾਲਤ ਦੋਆਧਾਰੀ_ਅੰਕ_XOR_ਵਿਅੰਜਕ:
		  r_name = "^";
		  ਰੋਕੋ;
		ਹਾਲਤ ਦੋਆਧਾਰੀ_ਅੰਕ_IOR_ਵਿਅੰਜਕ:
		  r_name = "|";
		  ਰੋਕੋ;
		ਮੂਲ:
		  gcc_unreachable ();
		}
	      ਜੇ (r_name)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qE has invalid type for %<reduction(%s)%>",
			    t, r_name);
		  remove = ਸੱਚ;
		  ਰੋਕੋ;
		}
	    }
	  ਨਹੀਂਤਾਂ ਜੇ (OMP_CLAUSE_REDUCTION_PLACEHOLDER (c) == error_mark_ਗੰਢ)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"user defined reduction not found for %qE", t);
	      remove = ਸੱਚ;
	      ਰੋਕੋ;
	    }
	  ਨਹੀਂਤਾਂ ਜੇ (OMP_CLAUSE_REDUCTION_PLACEHOLDER (c))
	    {
	      ਰੁੱਖ list = OMP_CLAUSE_REDUCTION_PLACEHOLDER (c);
	      type = TYPE_MAIN_VARIANT (type);
	      ਰੁੱਖ placeholder = build_decl (OMP_CLAUSE_LOCATION (c),
					     VAR_DECL, NULL_ਰੁੱਖ, type);
	      ਰੁੱਖ decl_placeholder = NULL_ਰੁੱਖ;
	      OMP_CLAUSE_REDUCTION_PLACEHOLDER (c) = placeholder;
	      DECL_ARTIFICIAL (placeholder) = 1;
	      DECL_IGNORED_P (placeholder) = 1;
	      ਜੇ (ਰੁੱਖ_ਕੋਡ (t) == MEM_REF)
		{
		  decl_placeholder = build_decl (OMP_CLAUSE_LOCATION (c),
						 VAR_DECL, NULL_ਰੁੱਖ, type);
		  OMP_CLAUSE_REDUCTION_DECL_PLACEHOLDER (c) = decl_placeholder;
		  DECL_ARTIFICIAL (decl_placeholder) = 1;
		  DECL_IGNORED_P (decl_placeholder) = 1;
		}
	      ਜੇ (ਰੁੱਖ_ADDRESSABLE (ਰੁੱਖ_VEC_ELT (list, 0)))
		c_mark_addressable (placeholder);
	      ਜੇ (ਰੁੱਖ_ADDRESSABLE (ਰੁੱਖ_VEC_ELT (list, 1)))
		c_mark_addressable (decl_placeholder ? decl_placeholder
				    : OMP_CLAUSE_DECL (c));
	      OMP_CLAUSE_REDUCTION_ਮਿਲਾਓ (c)
		= c_clone_omp_udr (ਰੁੱਖ_VEC_ELT (list, 2),
				   ਰੁੱਖ_VEC_ELT (list, 0),
				   ਰੁੱਖ_VEC_ELT (list, 1),
				   decl_placeholder ? decl_placeholder
				   : OMP_CLAUSE_DECL (c), placeholder);
	      OMP_CLAUSE_REDUCTION_ਮਿਲਾਓ (c)
		= build3_loc (OMP_CLAUSE_LOCATION (c), BIND_ਵਿਅੰਜਕ,
			      void_type_ਗੰਢ, NULL_ਰੁੱਖ,
			      OMP_CLAUSE_REDUCTION_ਮਿਲਾਓ (c), NULL_ਰੁੱਖ);
	      ਰੁੱਖ_SIDE_EFFECTS (OMP_CLAUSE_REDUCTION_ਮਿਲਾਓ (c)) = 1;
	      ਜੇ (ਰੁੱਖ_VEC_ਲੰਮਾਈ (list) == 6)
		{
		  ਜੇ (ਰੁੱਖ_ADDRESSABLE (ਰੁੱਖ_VEC_ELT (list, 3)))
		    c_mark_addressable (decl_placeholder ? decl_placeholder
					: OMP_CLAUSE_DECL (c));
		  ਜੇ (ਰੁੱਖ_ADDRESSABLE (ਰੁੱਖ_VEC_ELT (list, 4)))
		    c_mark_addressable (placeholder);
		  ਰੁੱਖ init = ਰੁੱਖ_VEC_ELT (list, 5);
		  ਜੇ (init == error_mark_ਗੰਢ)
		    init = DECL_INITIAL (ਰੁੱਖ_VEC_ELT (list, 3));
		  OMP_CLAUSE_REDUCTION_INIT (c)
		    = c_clone_omp_udr (init, ਰੁੱਖ_VEC_ELT (list, 4),
				       ਰੁੱਖ_VEC_ELT (list, 3),
				       decl_placeholder ? decl_placeholder
				       : OMP_CLAUSE_DECL (c), placeholder);
		  ਜੇ (ਰੁੱਖ_VEC_ELT (list, 5) == error_mark_ਗੰਢ)
		    {
		      ਰੁੱਖ v = decl_placeholder ? decl_placeholder : t;
		      OMP_CLAUSE_REDUCTION_INIT (c)
			= build2 (INIT_ਵਿਅੰਜਕ, ਰੁੱਖ_TYPE (v), v,
				  OMP_CLAUSE_REDUCTION_INIT (c));
		    }
		  ਜੇ (walk_ਰੁੱਖ (&OMP_CLAUSE_REDUCTION_INIT (c),
				 c_ਲੱਭੋ_omp_placeholder_r,
				 placeholder, ਨਿਰਾ))
		    OMP_CLAUSE_REDUCTION_OMP_ORIG_REF (c) = 1;
		}
	      ਨਹੀਂਤਾਂ
		{
		  ਰੁੱਖ init;
		  ਰੁੱਖ v = decl_placeholder ? decl_placeholder : t;
		  ਜੇ (AGGREGATE_TYPE_P (ਰੁੱਖ_TYPE (v)))
		    init = build_constructor (ਰੁੱਖ_TYPE (v), ਨਿਰਾ);
		  ਨਹੀਂਤਾਂ
		    init = fold_convert (ਰੁੱਖ_TYPE (v), integer_zero_ਗੰਢ);
		  OMP_CLAUSE_REDUCTION_INIT (c)
		    = build2 (INIT_ਵਿਅੰਜਕ, ਰੁੱਖ_TYPE (v), v, init);
		}
	      OMP_CLAUSE_REDUCTION_INIT (c)
		= build3_loc (OMP_CLAUSE_LOCATION (c), BIND_ਵਿਅੰਜਕ,
			      void_type_ਗੰਢ, NULL_ਰੁੱਖ,
			       OMP_CLAUSE_REDUCTION_INIT (c), NULL_ਰੁੱਖ);
	      ਰੁੱਖ_SIDE_EFFECTS (OMP_CLAUSE_REDUCTION_INIT (c)) = 1;
	    }
	  ਜੇ (ਰੁੱਖ_ਕੋਡ (t) == MEM_REF)
	    {
	      ਜੇ (TYPE_ਮਾਪ_UNIT (ਰੁੱਖ_TYPE (ਰੁੱਖ_TYPE (t))) == NULL_ਰੁੱਖ
		  || ਰੁੱਖ_ਕੋਡ (TYPE_ਮਾਪ_UNIT (ਰੁੱਖ_TYPE (ਰੁੱਖ_TYPE (t))))
		     != INTEGER_CST)
		{
		  sorry ("variable length element type in array "
			 "%<reduction%> clause");
		  remove = ਸੱਚ;
		  ਰੋਕੋ;
		}
	      t = ਰੁੱਖ_ਸੰਕਾਰਜ (t, 0);
	      ਜੇ (ਰੁੱਖ_ਕੋਡ (t) == ਸੂਚਕ_PLUS_ਵਿਅੰਜਕ)
		t = ਰੁੱਖ_ਸੰਕਾਰਜ (t, 0);
	      ਜੇ (ਰੁੱਖ_ਕੋਡ (t) == ADDR_ਵਿਅੰਜਕ)
		t = ਰੁੱਖ_ਸੰਕਾਰਜ (t, 0);
	    }
	  ਜਾਓ check_dup_generic_t;

	ਹਾਲਤ OMP_CLAUSE_COPYPRIVATE:
	  copyprivate_ਵੇਖਿਆ = ਸੱਚ;
	  ਜੇ (nowait_clause)
	    {
	      error_at (OMP_CLAUSE_LOCATION (*nowait_clause),
			"%<nowait%> clause must not be used together "
			"with %<copyprivate%> clause");
	      *nowait_clause = OMP_CLAUSE_CHAIN (*nowait_clause);
	      nowait_clause = ਨਿਰਾ;
	    }
	  ਜਾਓ check_dup_generic;

	ਹਾਲਤ OMP_CLAUSE_COPYIN:
	  t = OMP_CLAUSE_DECL (c);
	  ਜੇ (!VAR_P (t) || !DECL_THREAD_LOCAL_P (t))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE must be %<threadprivate%> for %<copyin%>", t);
	      remove = ਸੱਚ;
	      ਰੋਕੋ;
	    }
	  ਜਾਓ check_dup_generic;

	ਹਾਲਤ OMP_CLAUSE_ਰੇਖਿਕ:
	  ਜੇ (ort != C_ORT_OMP_DECLARE_SIMD)
	    need_implicitly_determined = ਸੱਚ;
	  t = OMP_CLAUSE_DECL (c);
	  ਜੇ (ort != C_ORT_OMP_DECLARE_SIMD
	      && OMP_CLAUSE_ਰੇਖਿਕ_ਕਿਸਮ (c) != OMP_CLAUSE_ਰੇਖਿਕ_DEFAULT
	      && OMP_CLAUSE_ਰੇਖਿਕ_OLD_ਰੇਖਿਕ_MODIFIER (c))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"modifier should not be specified in %<linear%> "
			"clause on %<simd%> or %<for%> constructs when not "
			"using OpenMP 5.2 modifiers");
	      OMP_CLAUSE_ਰੇਖਿਕ_ਕਿਸਮ (c) = OMP_CLAUSE_ਰੇਖਿਕ_DEFAULT;
	    }
	  ਜੇ (!INTEGRAL_TYPE_P (ਰੁੱਖ_TYPE (t))
	      && ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (t)) != ਸੂਚਕ_TYPE)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"linear clause applied to non-integral non-pointer "
			"variable with type %qT", ਰੁੱਖ_TYPE (t));
	      remove = ਸੱਚ;
	      ਰੋਕੋ;
	    }
	  ਜੇ (TYPE_ATOMIC (ਰੁੱਖ_TYPE (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<_Atomic%> %qD in %<linear%> clause", t);
	      remove = ਸੱਚ;
	      ਰੋਕੋ;
	    }
	  ਜੇ (ort == C_ORT_OMP_DECLARE_SIMD)
	    {
	      ਰੁੱਖ s = OMP_CLAUSE_ਰੇਖਿਕ_ਕਦਮ (c);
	      ਜੇ (ਰੁੱਖ_ਕੋਡ (s) == PARM_DECL)
		{
		  OMP_CLAUSE_ਰੇਖਿਕ_VARIABLE_STRIDE (c) = 1;
		  /* map_head bitmap is used as uniform_head if
		     declare_simd.  */
		  ਜੇ (!bitmap_ਦੋਆਧਾਰੀ_ਅੰਕ_p (&map_ਸਿਰ, DECL_UID (s)))
		    ਰੇਖਿਕ_variable_ਕਦਮ_check = ਸੱਚ;
		  ਜਾਓ check_dup_generic;
		}
	      ਜੇ (ਰੁੱਖ_ਕੋਡ (s) != INTEGER_CST)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%<linear%> clause step %qE is neither constant "
			    "nor a parameter", s);
		  remove = ਸੱਚ;
		  ਰੋਕੋ;
		}
	    }
	  ਜੇ (ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (OMP_CLAUSE_DECL (c))) == ਸੂਚਕ_TYPE)
	    {
	      ਰੁੱਖ s = OMP_CLAUSE_ਰੇਖਿਕ_ਕਦਮ (c);
	      s = ਸੂਚਕ_int_ਜੋੜ (OMP_CLAUSE_LOCATION (c), PLUS_ਵਿਅੰਜਕ,
				   OMP_CLAUSE_DECL (c), s);
	      s = fold_build2_loc (OMP_CLAUSE_LOCATION (c), MINUS_ਵਿਅੰਜਕ,
				   sizetype, fold_convert (sizetype, s),
				   fold_convert
				     (sizetype, OMP_CLAUSE_DECL (c)));
	      ਜੇ (s == error_mark_ਗੰਢ)
		s = ਮਾਪ_one_ਗੰਢ;
	      OMP_CLAUSE_ਰੇਖਿਕ_ਕਦਮ (c) = s;
	    }
	  ਨਹੀਂਤਾਂ
	    OMP_CLAUSE_ਰੇਖਿਕ_ਕਦਮ (c)
	      = fold_convert (ਰੁੱਖ_TYPE (t), OMP_CLAUSE_ਰੇਖਿਕ_ਕਦਮ (c));
	  ਜਾਓ check_dup_generic;

	check_dup_generic:
	  t = OMP_CLAUSE_DECL (c);
	check_dup_generic_t:
	  ਜੇ (!VAR_P (t) && ਰੁੱਖ_ਕੋਡ (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in clause %qs", t,
			omp_clause_ਕੋਡ_name[OMP_CLAUSE_ਕੋਡ (c)]);
	      remove = ਸੱਚ;
	    }
	  ਨਹੀਂਤਾਂ ਜੇ ((openacc && OMP_CLAUSE_ਕੋਡ (c) == OMP_CLAUSE_REDUCTION)
		   || (ort == C_ORT_OMP
		       && (OMP_CLAUSE_ਕੋਡ (c) == OMP_CLAUSE_USE_DEVICE_PTR
			   || (OMP_CLAUSE_ਕੋਡ (c)
			       == OMP_CLAUSE_USE_DEVICE_ADDR)))
		   || (ort == C_ORT_OMP_ਨਿਸ਼ਾਨਾ
		       && OMP_CLAUSE_ਕੋਡ (c) == OMP_CLAUSE_ਵਿੱਚ_REDUCTION))
	    {
	      ਜੇ (OMP_CLAUSE_ਕੋਡ (c) == OMP_CLAUSE_ਵਿੱਚ_REDUCTION
		  && (bitmap_ਦੋਆਧਾਰੀ_ਅੰਕ_p (&generic_ਸਿਰ, DECL_UID (t))
		      || bitmap_ਦੋਆਧਾਰੀ_ਅੰਕ_p (&firstprivate_ਸਿਰ, DECL_UID (t))))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD appears more than once in data-sharing "
			    "clauses", t);
		  remove = ਸੱਚ;
		  ਰੋਕੋ;
		}
	      ਜੇ (OMP_CLAUSE_ਕੋਡ (c) == OMP_CLAUSE_ਵਿੱਚ_REDUCTION)
		ਨਿਸ਼ਾਨਾ_ਵਿੱਚ_reduction_ਵੇਖਿਆ = ਸੱਚ;
	      ਜੇ (bitmap_ਦੋਆਧਾਰੀ_ਅੰਕ_p (&oacc_reduction_ਸਿਰ, DECL_UID (t)))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    openacc
			    ? "%qD appears more than once in reduction clauses"
			    : "%qD appears more than once in data clauses",
			    t);
		  remove = ਸੱਚ;
		}
	      ਨਹੀਂਤਾਂ
		bitmap_ਸੈੱਟ_ਦੋਆਧਾਰੀ_ਅੰਕ (&oacc_reduction_ਸਿਰ, DECL_UID (t));
	    }
	  ਨਹੀਂਤਾਂ ਜੇ (bitmap_ਦੋਆਧਾਰੀ_ਅੰਕ_p (&generic_ਸਿਰ, DECL_UID (t))
		   || bitmap_ਦੋਆਧਾਰੀ_ਅੰਕ_p (&firstprivate_ਸਿਰ, DECL_UID (t))
		   || bitmap_ਦੋਆਧਾਰੀ_ਅੰਕ_p (&lastprivate_ਸਿਰ, DECL_UID (t))
		   || bitmap_ਦੋਆਧਾਰੀ_ਅੰਕ_p (&map_firstprivate_ਸਿਰ, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE appears more than once in data clauses", t);
	      remove = ਸੱਚ;
	    }
	  ਨਹੀਂਤਾਂ ਜੇ ((OMP_CLAUSE_ਕੋਡ (c) == OMP_CLAUSE_ਨਿੱਜੀ
		    || OMP_CLAUSE_ਕੋਡ (c) == OMP_CLAUSE_HAS_DEVICE_ADDR
		    || OMP_CLAUSE_ਕੋਡ (c) == OMP_CLAUSE_IS_DEVICE_PTR)
		   && bitmap_ਦੋਆਧਾਰੀ_ਅੰਕ_p (&map_ਸਿਰ, DECL_UID (t)))
	    {
	      ਜੇ (openacc)
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD appears more than once in data clauses", t);
	      ਨਹੀਂਤਾਂ
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD appears both in data and map clauses", t);
	      remove = ਸੱਚ;
	    }
	  ਨਹੀਂਤਾਂ
	    bitmap_ਸੈੱਟ_ਦੋਆਧਾਰੀ_ਅੰਕ (&generic_ਸਿਰ, DECL_UID (t));
	  ਰੋਕੋ;

	ਹਾਲਤ OMP_CLAUSE_FIRSTPRIVATE:
	  ਜੇ (OMP_CLAUSE_FIRSTPRIVATE_IMPLICIT (c) && !implicit_moved)
	    {
	    move_implicit:
	      implicit_moved = ਸੱਚ;
	      /* Move firstprivate and map clauses with
		 OMP_CLAUSE_{FIRSTPRIVATE,MAP}_IMPLICIT set to the end of
		 clauses chain.  */
	      ਰੁੱਖ cl1 = NULL_ਰੁੱਖ, cl2 = NULL_ਰੁੱਖ;
	      ਰੁੱਖ *pc1 = pc, *pc2 = &cl1, *pc3 = &cl2;
	      ਜਦੋਂ (*pc1)
		ਜੇ (OMP_CLAUSE_ਕੋਡ (*pc1) == OMP_CLAUSE_FIRSTPRIVATE
		    && OMP_CLAUSE_FIRSTPRIVATE_IMPLICIT (*pc1))
		  {
		    *pc3 = *pc1;
		    pc3 = &OMP_CLAUSE_CHAIN (*pc3);
		    *pc1 = OMP_CLAUSE_CHAIN (*pc1);
		  }
		ਨਹੀਂਤਾਂ ਜੇ (OMP_CLAUSE_ਕੋਡ (*pc1) == OMP_CLAUSE_MAP
			 && OMP_CLAUSE_MAP_IMPLICIT (*pc1))
		  {
		    *pc2 = *pc1;
		    pc2 = &OMP_CLAUSE_CHAIN (*pc2);
		    *pc1 = OMP_CLAUSE_CHAIN (*pc1);
		  }
		ਨਹੀਂਤਾਂ
		  pc1 = &OMP_CLAUSE_CHAIN (*pc1);
	      *pc3 = ਨਿਰਾ;
	      *pc2 = cl2;
	      *pc1 = cl1;
	      ਜਾਰੀ;
	    }
	  t = OMP_CLAUSE_DECL (c);
	  need_complete = ਸੱਚ;
	  need_implicitly_determined = ਸੱਚ;
	  ਜੇ (!VAR_P (t) && ਰੁੱਖ_ਕੋਡ (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in clause %<firstprivate%>", t);
	      remove = ਸੱਚ;
	    }
	  ਨਹੀਂਤਾਂ ਜੇ (OMP_CLAUSE_FIRSTPRIVATE_IMPLICIT (c)
		   && !OMP_CLAUSE_FIRSTPRIVATE_IMPLICIT_ਨਿਸ਼ਾਨਾ (c)
		   && bitmap_ਦੋਆਧਾਰੀ_ਅੰਕ_p (&map_firstprivate_ਸਿਰ, DECL_UID (t)))
	    remove = ਸੱਚ;
	  ਨਹੀਂਤਾਂ ਜੇ (bitmap_ਦੋਆਧਾਰੀ_ਅੰਕ_p (&generic_ਸਿਰ, DECL_UID (t))
		   || bitmap_ਦੋਆਧਾਰੀ_ਅੰਕ_p (&firstprivate_ਸਿਰ, DECL_UID (t))
		   || bitmap_ਦੋਆਧਾਰੀ_ਅੰਕ_p (&map_firstprivate_ਸਿਰ, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE appears more than once in data clauses", t);
	      remove = ਸੱਚ;
	    }
	  ਨਹੀਂਤਾਂ ਜੇ (bitmap_ਦੋਆਧਾਰੀ_ਅੰਕ_p (&map_ਸਿਰ, DECL_UID (t))
		   || bitmap_ਦੋਆਧਾਰੀ_ਅੰਕ_p (&map_ਖੇਤਰ_ਸਿਰ, DECL_UID (t)))
	    {
	      ਜੇ (openacc)
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD appears more than once in data clauses", t);
	      ਨਹੀਂਤਾਂ ਜੇ (OMP_CLAUSE_FIRSTPRIVATE_IMPLICIT (c)
		       && !OMP_CLAUSE_FIRSTPRIVATE_IMPLICIT_ਨਿਸ਼ਾਨਾ (c))
		/* Silently drop the clause.  */;
	      ਨਹੀਂਤਾਂ
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD appears both in data and map clauses", t);
	      remove = ਸੱਚ;
	    }
	  ਨਹੀਂਤਾਂ
	    bitmap_ਸੈੱਟ_ਦੋਆਧਾਰੀ_ਅੰਕ (&firstprivate_ਸਿਰ, DECL_UID (t));
	  ਰੋਕੋ;

	ਹਾਲਤ OMP_CLAUSE_LASTPRIVATE:
	  t = OMP_CLAUSE_DECL (c);
	  need_complete = ਸੱਚ;
	  need_implicitly_determined = ਸੱਚ;
	  ਜੇ (!VAR_P (t) && ਰੁੱਖ_ਕੋਡ (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in clause %<lastprivate%>", t);
	      remove = ਸੱਚ;
	    }
	  ਨਹੀਂਤਾਂ ਜੇ (bitmap_ਦੋਆਧਾਰੀ_ਅੰਕ_p (&generic_ਸਿਰ, DECL_UID (t))
		   || bitmap_ਦੋਆਧਾਰੀ_ਅੰਕ_p (&lastprivate_ਸਿਰ, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
		     "%qE appears more than once in data clauses", t);
	      remove = ਸੱਚ;
	    }
	  ਨਹੀਂਤਾਂ
	    bitmap_ਸੈੱਟ_ਦੋਆਧਾਰੀ_ਅੰਕ (&lastprivate_ਸਿਰ, DECL_UID (t));
	  ਰੋਕੋ;

	ਹਾਲਤ OMP_CLAUSE_ALIGNED:
	  t = OMP_CLAUSE_DECL (c);
	  ਜੇ (!VAR_P (t) && ਰੁੱਖ_ਕੋਡ (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in %<aligned%> clause", t);
	      remove = ਸੱਚ;
	    }
	  ਨਹੀਂਤਾਂ ਜੇ (!ਸੂਚਕ_TYPE_P (ਰੁੱਖ_TYPE (t))
		   && ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (t)) != ARRAY_TYPE)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE in %<aligned%> clause is neither a pointer nor "
			"an array", t);
	      remove = ਸੱਚ;
	    }
	  ਨਹੀਂਤਾਂ ਜੇ (TYPE_ATOMIC (ਰੁੱਖ_TYPE (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<_Atomic%> %qD in %<aligned%> clause", t);
	      remove = ਸੱਚ;
	      ਰੋਕੋ;
	    }
	  ਨਹੀਂਤਾਂ ਜੇ (bitmap_ਦੋਆਧਾਰੀ_ਅੰਕ_p (&aligned_ਸਿਰ, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE appears more than once in %<aligned%> clauses",
			t);
	      remove = ਸੱਚ;
	    }
	  ਨਹੀਂਤਾਂ
	    bitmap_ਸੈੱਟ_ਦੋਆਧਾਰੀ_ਅੰਕ (&aligned_ਸਿਰ, DECL_UID (t));
	  ਰੋਕੋ;

	ਹਾਲਤ OMP_CLAUSE_NONTEMPORAL:
	  t = OMP_CLAUSE_DECL (c);
	  ਜੇ (!VAR_P (t) && ਰੁੱਖ_ਕੋਡ (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in %<nontemporal%> clause", t);
	      remove = ਸੱਚ;
	    }
	  ਨਹੀਂਤਾਂ ਜੇ (bitmap_ਦੋਆਧਾਰੀ_ਅੰਕ_p (&oacc_reduction_ਸਿਰ, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE appears more than once in %<nontemporal%> "
			"clauses", t);
	      remove = ਸੱਚ;
	    }
	  ਨਹੀਂਤਾਂ
	    bitmap_ਸੈੱਟ_ਦੋਆਧਾਰੀ_ਅੰਕ (&oacc_reduction_ਸਿਰ, DECL_UID (t));
	  ਰੋਕੋ;

	ਹਾਲਤ OMP_CLAUSE_ALLOCATE:
	  t = OMP_CLAUSE_DECL (c);
	  ਜੇ (!VAR_P (t) && ਰੁੱਖ_ਕੋਡ (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in %<allocate%> clause", t);
	      remove = ਸੱਚ;
	    }
	  ਨਹੀਂਤਾਂ ਜੇ (bitmap_ਦੋਆਧਾਰੀ_ਅੰਕ_p (&aligned_ਸਿਰ, DECL_UID (t)))
	    {
	      warning_at (OMP_CLAUSE_LOCATION (c), OPT_Wopenmp,
			  "%qE appears more than once in %<allocate%> clauses",
			  t);
	      remove = ਸੱਚ;
	    }
	  ਨਹੀਂਤਾਂ
	    {
	      bitmap_ਸੈੱਟ_ਦੋਆਧਾਰੀ_ਅੰਕ (&aligned_ਸਿਰ, DECL_UID (t));
	      ਜੇ (!OMP_CLAUSE_ALLOCATE_COMBINED (c))
		allocate_ਵੇਖਿਆ = ਸੱਚ;
	    }
	  ਰੋਕੋ;

	ਹਾਲਤ OMP_CLAUSE_DOACROSS:
	  t = OMP_CLAUSE_DECL (c);
	  ਜੇ (t == NULL_ਰੁੱਖ)
	    ਰੋਕੋ;
	  ਜੇ (OMP_CLAUSE_DOACROSS_ਕਿਸਮ (c) == OMP_CLAUSE_DOACROSS_SINK)
	    {
	      gcc_assert (ਰੁੱਖ_ਕੋਡ (t) == ਰੁੱਖ_LIST);
	      ਲਈ (; t; t = ਰੁੱਖ_CHAIN (t))
		{
		  ਰੁੱਖ decl = ਰੁੱਖ_ਮੁੱਲ (t);
		  ਜੇ (ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (decl)) == ਸੂਚਕ_TYPE)
		    {
		      ਰੁੱਖ ਵਿੱਥ = ਰੁੱਖ_PURPOSE (t);
		      ਤਾਰਕਿਕ neg = wi::neg_p (wi::ਮੰਜ਼ਿਲ_wide (ਵਿੱਥ));
		      ਵਿੱਥ = fold_unary (ABS_ਵਿਅੰਜਕ, ਰੁੱਖ_TYPE (ਵਿੱਥ), ਵਿੱਥ);
		      ਰੁੱਖ t2 = ਸੂਚਕ_int_ਜੋੜ (OMP_CLAUSE_LOCATION (c),
						 neg ? MINUS_ਵਿਅੰਜਕ : PLUS_ਵਿਅੰਜਕ,
						 decl, ਵਿੱਥ);
		      t2 = fold_build2_loc (OMP_CLAUSE_LOCATION (c), MINUS_ਵਿਅੰਜਕ,
					    sizetype,
					    fold_convert (sizetype, t2),
					    fold_convert (sizetype, decl));
		      ਜੇ (t2 == error_mark_ਗੰਢ)
			{
			  remove = ਸੱਚ;
			  ਰੋਕੋ;
			}
		      ਰੁੱਖ_PURPOSE (t) = t2;
		    }
		}
	      ਰੋਕੋ;
	    }
	  gcc_unreachable ();

	ਹਾਲਤ OMP_CLAUSE_ਵਰਤਦਾ_ALLOCATORS:
	  t = OMP_CLAUSE_ਵਰਤਦਾ_ALLOCATORS_ALLOCATOR (c);
	  ਜੇ (t == error_mark_ਗੰਢ)
	    {
	      remove = ਸੱਚ;
	      ਰੋਕੋ;
	    }
	  ਜੇ ((VAR_P (t) || ਰੁੱਖ_ਕੋਡ (t) == PARM_DECL)
	      && (bitmap_ਦੋਆਧਾਰੀ_ਅੰਕ_p (&generic_ਸਿਰ, DECL_UID (t))
		  || bitmap_ਦੋਆਧਾਰੀ_ਅੰਕ_p (&map_ਸਿਰ, DECL_UID (t))
		  || bitmap_ਦੋਆਧਾਰੀ_ਅੰਕ_p (&firstprivate_ਸਿਰ, DECL_UID (t))
		  || bitmap_ਦੋਆਧਾਰੀ_ਅੰਕ_p (&lastprivate_ਸਿਰ, DECL_UID (t))))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE appears more than once in data clauses", t);
	      remove = ਸੱਚ;
	      ਰੋਕੋ;
	    }
	  ਨਹੀਂਤਾਂ
	    bitmap_ਸੈੱਟ_ਦੋਆਧਾਰੀ_ਅੰਕ (&generic_ਸਿਰ, DECL_UID (t));
	  ਜੇ (ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (t)) != ENUMERAL_TYPE
	      || strcmp (IDENTIFIER_ਸੂਚਕ (TYPE_IDENTIFIER (ਰੁੱਖ_TYPE (t))),
			 "omp_allocator_handle_t") != 0)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"allocator %qE must be of %<omp_allocator_handle_t%> "
			"type", t);
	      remove = ਸੱਚ;
	      ਰੋਕੋ;
	    }
	  ਰੁੱਖ init;
	  ਜੇ (!DECL_P (t)
	      || (ਰੁੱਖ_ਕੋਡ (t) == CONST_DECL
		  && ((init = DECL_INITIAL(t)) == ਖਾਲੀ_ਸੂਚਕ
		      || ਰੁੱਖ_ਕੋਡ (init) != INTEGER_CST
		      || ((wi::ਮੰਜ਼ਿਲ_widest (init) < 0
			   || wi::ਮੰਜ਼ਿਲ_widest (init) > GOMP_OMP_PREDEF_ALLOC_MAX)
			  && (wi::ਮੰਜ਼ਿਲ_widest (init) < GOMP_OMPX_PREDEF_ALLOC_MIN
			      || (wi::ਮੰਜ਼ਿਲ_widest (init)
				  > GOMP_OMPX_PREDEF_ALLOC_MAX))))))
	    {
	      remove = ਸੱਚ;
	      error_at (OMP_CLAUSE_LOCATION (c),
			"allocator %qE must be either a variable or a "
			"predefined allocator", t);
	      ਰੋਕੋ;
	    }
	  ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਕੋਡ (t) == CONST_DECL)
	    {
	      /* omp_null_allocator is ignored and for predefined allocators,
		 no special handling is required; thus, mark them removed. */
	      remove = ਸੱਚ;

	      ਜੇ (OMP_CLAUSE_ਵਰਤਦਾ_ALLOCATORS_MEMSPACE (c)
		  || OMP_CLAUSE_ਵਰਤਦਾ_ALLOCATORS_TRAITS (c))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "modifiers cannot be used with predefined "
			    "allocator %qE", t);
		  ਰੋਕੋ;
		}
	    }
	  t = OMP_CLAUSE_ਵਰਤਦਾ_ALLOCATORS_MEMSPACE (c);
	  ਜੇ (t == error_mark_ਗੰਢ)
	    {
	      remove = ਸੱਚ;
	      ਰੋਕੋ;
	    }
	  ਜੇ (t != NULL_ਰੁੱਖ
	      && ((ਰੁੱਖ_ਕੋਡ (t) != CONST_DECL && ਰੁੱਖ_ਕੋਡ (t) != INTEGER_CST)
		  || ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (t)) != ENUMERAL_TYPE
		  || strcmp (IDENTIFIER_ਸੂਚਕ (TYPE_IDENTIFIER (ਰੁੱਖ_TYPE (t))),
			     "omp_memspace_handle_t") != 0))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c), "memspace modifier %qE must be"
			" constant enum of %<omp_memspace_handle_t%> type", t);
	      remove = ਸੱਚ;
	      ਰੋਕੋ;
	    }
	  t = OMP_CLAUSE_ਵਰਤਦਾ_ALLOCATORS_TRAITS (c);
	  ਜੇ (t == error_mark_ਗੰਢ)
	    {
	      remove = ਸੱਚ;
	      ਰੋਕੋ;
	    }
	  ਜੇ (t != NULL_ਰੁੱਖ
	      && t != error_mark_ਗੰਢ
	      && (DECL_EXTERNAL (t)
		  || ਰੁੱਖ_ਕੋਡ (t) == PARM_DECL))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c), "traits array %qE must be "
			"defined in same scope as the construct on which the "
			"clause appears", t);
	      remove = ਸੱਚ;
	    }
	  ਜੇ (t != NULL_ਰੁੱਖ)
	    {
	      ਤਾਰਕਿਕ type_err = ਝੂਠ;

	      ਜੇ (ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (t)) != ARRAY_TYPE
		  || DECL_ਮਾਪ (t) == NULL_ਰੁੱਖ
		  || !COMPLETE_TYPE_P (ਰੁੱਖ_TYPE (t)))
		type_err = ਸੱਚ;
	      ਨਹੀਂਤਾਂ
		{
		  ਰੁੱਖ elem_t = ਰੁੱਖ_TYPE (ਰੁੱਖ_TYPE (t));
		  ਜੇ (ਰੁੱਖ_ਕੋਡ (elem_t) != ਰਿਕਾਰਡ_TYPE
		      || strcmp (IDENTIFIER_ਸੂਚਕ (TYPE_IDENTIFIER (elem_t)),
				 "omp_alloctrait_t") != 0
		      || !TYPE_READONLY (elem_t))
		    type_err = ਸੱਚ;
		}
	      ਜੇ (type_err)
		{
		  ਜੇ (t != error_mark_ਗੰਢ)
		    error_at (OMP_CLAUSE_LOCATION (c), "traits array %qE must "
			      "be of %<const omp_alloctrait_t []%> type", t);
		  ਨਹੀਂਤਾਂ
		    error_at (OMP_CLAUSE_LOCATION (c), "traits array must "
			      "be of %<const omp_alloctrait_t []%> type");
		  remove = ਸੱਚ;
		}
	      ਨਹੀਂਤਾਂ
		{
		  ਰੁੱਖ cst_val = decl_constant_ਮੁੱਲ_1 (t, ਸੱਚ);
		  ਜੇ (cst_val == t)
		    {
		      error_at (OMP_CLAUSE_LOCATION (c), "traits array must be "
				"initialized with constants");

		      remove = ਸੱਚ;
		    }
		}
	    }
	  ਜੇ (remove)
	    ਰੋਕੋ;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  ਜਾਰੀ;
	ਹਾਲਤ OMP_CLAUSE_DEPEND:
	  depend_clause = c;
	  /* FALLTHRU */
	ਹਾਲਤ OMP_CLAUSE_AFFINITY:
	  t = OMP_CLAUSE_DECL (c);
	  ਜੇ (OMP_ITERATOR_DECL_P (t))
	    {
	      ਜੇ (ਰੁੱਖ_PURPOSE (t) != ਆਖਰੀ_iterators)
		ਆਖਰੀ_iterators_remove
		  = c_omp_ਅੰਤ_iterators (ਰੁੱਖ_PURPOSE (t));
	      ਆਖਰੀ_iterators = ਰੁੱਖ_PURPOSE (t);
	      t = ਰੁੱਖ_ਮੁੱਲ (t);
	      ਜੇ (ਆਖਰੀ_iterators_remove)
		t = error_mark_ਗੰਢ;
	    }
	  ਨਹੀਂਤਾਂ
	    ਆਖਰੀ_iterators = NULL_ਰੁੱਖ;
	  ਜੇ (ਰੁੱਖ_ਕੋਡ (t) == OMP_ARRAY_SECTION)
	    {
	      ਜੇ (handle_omp_array_sections (c, ort))
		remove = ਸੱਚ;
	      ਨਹੀਂਤਾਂ ਜੇ (OMP_CLAUSE_ਕੋਡ (c) == OMP_CLAUSE_DEPEND
		       && OMP_CLAUSE_DEPEND_ਕਿਸਮ (c) == OMP_CLAUSE_DEPEND_DEPOBJ)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%<depend%> clause with %<depobj%> dependence "
			    "type on array section");
		  remove = ਸੱਚ;
		}
	      ਰੋਕੋ;
	    }
	  ਜੇ (t == error_mark_ਗੰਢ)
	    remove = ਸੱਚ;
	  ਨਹੀਂਤਾਂ ਜੇ (OMP_CLAUSE_ਕੋਡ (c) == OMP_CLAUSE_DEPEND
		   && t == ridpointers[RID_OMP_ALL_ਸਮ੍ਰਿਤੀ])
	    {
	      ਜੇ (OMP_CLAUSE_DEPEND_ਕਿਸਮ (c) != OMP_CLAUSE_DEPEND_ਬਾਹਰਲਾ
		  && OMP_CLAUSE_DEPEND_ਕਿਸਮ (c) != OMP_CLAUSE_DEPEND_INOUT)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%<omp_all_memory%> used with %<depend%> kind "
			    "other than %<out%> or %<inout%>");
		  remove = ਸੱਚ;
		}
	    }
	  ਨਹੀਂਤਾਂ ਜੇ (!lvalue_p (t))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not lvalue expression nor array section in "
			"%qs clause", t,
			omp_clause_ਕੋਡ_name[OMP_CLAUSE_ਕੋਡ (c)]);
	      remove = ਸੱਚ;
	    }
	  ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਕੋਡ (t) == COMPONENT_REF
		   && DECL_C_ਦੋਆਧਾਰੀ_ਅੰਕ_ਖੇਤਰ (ਰੁੱਖ_ਸੰਕਾਰਜ (t, 1)))
	    {
	      gcc_assert (OMP_CLAUSE_ਕੋਡ (c) == OMP_CLAUSE_DEPEND
			  || OMP_CLAUSE_ਕੋਡ (c) == OMP_CLAUSE_AFFINITY);
	      error_at (OMP_CLAUSE_LOCATION (c),
			"bit-field %qE in %qs clause", t,
			omp_clause_ਕੋਡ_name[OMP_CLAUSE_ਕੋਡ (c)]);
	      remove = ਸੱਚ;
	    }
	  ਨਹੀਂਤਾਂ ਜੇ (OMP_CLAUSE_ਕੋਡ (c) == OMP_CLAUSE_DEPEND
		   && OMP_CLAUSE_DEPEND_ਕਿਸਮ (c) == OMP_CLAUSE_DEPEND_DEPOBJ)
	    {
	      ਜੇ (!c_omp_depend_t_p (ਰੁੱਖ_TYPE (t)))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qE does not have %<omp_depend_t%> type in "
			    "%<depend%> clause with %<depobj%> dependence "
			    "type", t);
		  remove = ਸੱਚ;
		}
	    }
	  ਨਹੀਂਤਾਂ ਜੇ (OMP_CLAUSE_ਕੋਡ (c) == OMP_CLAUSE_DEPEND
		   && c_omp_depend_t_p (ਰੁੱਖ_TYPE (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE should not have %<omp_depend_t%> type in "
			"%<depend%> clause with dependence type other than "
			"%<depobj%>", t);
	      remove = ਸੱਚ;
	    }
	  ਜੇ (!remove)
	    {
	      ਜੇ (t == ridpointers[RID_OMP_ALL_ਸਮ੍ਰਿਤੀ])
		t = null_ਸੂਚਕ_ਗੰਢ;
	      ਨਹੀਂਤਾਂ
		{
		  ਰੁੱਖ addr = build_unary_op (OMP_CLAUSE_LOCATION (c),
					      ADDR_ਵਿਅੰਜਕ, t, ਝੂਠ);
		  ਜੇ (addr == error_mark_ਗੰਢ)
		    {
		      remove = ਸੱਚ;
		      ਰੋਕੋ;
		    }
		  t = build_ਅਸਿੱਧਾ_ref (OMP_CLAUSE_LOCATION (c), addr,
					  RO_UNARY_ਤਾਰਾ);
		  ਜੇ (t == error_mark_ਗੰਢ)
		    {
		      remove = ਸੱਚ;
		      ਰੋਕੋ;
		    }
		}
	      ਜੇ (OMP_ITERATOR_DECL_P (OMP_CLAUSE_DECL (c)))
		ਰੁੱਖ_ਮੁੱਲ (OMP_CLAUSE_DECL (c)) = t;
	      ਨਹੀਂਤਾਂ
		OMP_CLAUSE_DECL (c) = t;
	    }
	  ਰੋਕੋ;

	ਹਾਲਤ OMP_CLAUSE_MAP:
	  ਜੇ (OMP_CLAUSE_MAP_IMPLICIT (c) && !implicit_moved)
	    ਜਾਓ move_implicit;
	  ਜੇ (OMP_CLAUSE_MAP_ਕਿਸਮ (c) == GOMP_MAP_ਧੱਕੋ_MAPPER_NAME
	      || OMP_CLAUSE_MAP_ਕਿਸਮ (c) == GOMP_MAP_ਕੱਢੋ_MAPPER_NAME)
	    {
	      remove = ਸੱਚ;
	      ਰੋਕੋ;
	    }
	  /* FALLTHRU */
	ਹਾਲਤ OMP_CLAUSE_ਮੰਜ਼ਿਲ:
	ਹਾਲਤ OMP_CLAUSE_FROM:
	  ਜੇ (OMP_CLAUSE_ITERATORS (c)
	      && c_omp_ਅੰਤ_iterators (OMP_CLAUSE_ITERATORS (c)))
	    {
	      t = error_mark_ਗੰਢ;
	      ਰੋਕੋ;
	    }
	  /* FALLTHRU */
	ਹਾਲਤ OMP_CLAUSE__CACHE_:
	  {
	    ਵਰਤੋਂ ਨਾਮਾਕਾਸ਼ omp_addr_tokenizer;
	    auto_vec<omp_addr_token *, 10> addr_ਟੋਕਨ;

	    t = OMP_CLAUSE_DECL (c);
	    ਜੇ (ਰੁੱਖ_ਕੋਡ (t) == OMP_ARRAY_SECTION)
	      {
		grp_ਸ਼ੁਰੂ_p = pc;
		grp_sentinel = OMP_CLAUSE_CHAIN (c);

		ਜੇ (handle_omp_array_sections (c, ort))
		  remove = ਸੱਚ;
		ਨਹੀਂਤਾਂ
		  {
		    t = OMP_CLAUSE_DECL (c);
		    ਜੇ (!omp_mappable_type (ਰੁੱਖ_TYPE (t)))
		      {
			error_at (OMP_CLAUSE_LOCATION (c),
				  "array section does not have mappable type "
				  "in %qs clause",
				  omp_clause_ਕੋਡ_name[OMP_CLAUSE_ਕੋਡ (c)]);
			remove = ਸੱਚ;
		      }
		    ਨਹੀਂਤਾਂ ਜੇ (TYPE_ATOMIC (ਰੁੱਖ_TYPE (t)))
		      {
			error_at (OMP_CLAUSE_LOCATION (c),
				  "%<_Atomic%> %qE in %qs clause", t,
				  omp_clause_ਕੋਡ_name[OMP_CLAUSE_ਕੋਡ (c)]);
			remove = ਸੱਚ;
		      }
		    ਜਦੋਂ (ਰੁੱਖ_ਕੋਡ (t) == ARRAY_REF)
		      t = ਰੁੱਖ_ਸੰਕਾਰਜ (t, 0);

		    c_omp_ਪਤਾ_inspector ai (OMP_CLAUSE_LOCATION (c), t);

		    ਜੇ (!omp_parse_ਵਿਅੰਜਕ (addr_ਟੋਕਨ, t))
		      {
			sorry_at (OMP_CLAUSE_LOCATION (c),
				  "unsupported map expression %qE",
				  OMP_CLAUSE_DECL (c));
			remove = ਸੱਚ;
			ਰੋਕੋ;
		      }

		    /* This check is to determine if this will be the only map
		       node created for this clause.  Otherwise, we'll check
		       the following FIRSTPRIVATE_POINTER or ATTACH_DETACH
		       node on the next iteration(s) of the loop.   */
		    ਜੇ (addr_ਟੋਕਨ.ਲੰਮਾਈ () >= 4
			&& addr_ਟੋਕਨ[0]->type == STRUCTURE_ਅਧਾਰ
			&& addr_ਟੋਕਨ[0]->u.structure_ਅਧਾਰ_ਕਿਸਮ == ਅਧਾਰ_DECL
			&& addr_ਟੋਕਨ[1]->type == ACCESS_ਵਿਧੀ
			&& addr_ਟੋਕਨ[2]->type == COMPONENT_SELECTOR
			&& addr_ਟੋਕਨ[3]->type == ACCESS_ਵਿਧੀ
			&& (addr_ਟੋਕਨ[3]->u.access_ਕਿਸਮ == ACCESS_ਸਿੱਧਾ
			    || (addr_ਟੋਕਨ[3]->u.access_ਕਿਸਮ
				== ACCESS_ਸੂਚਕਾਂਕਿਤ_ARRAY)))
		      {
			ਰੁੱਖ rt = addr_ਟੋਕਨ[1]->ਵਿਅੰਜਕ;

			gcc_assert (DECL_P (rt));

			ਜੇ (OMP_CLAUSE_ਕੋਡ (c) == OMP_CLAUSE_MAP
			    && OMP_CLAUSE_MAP_IMPLICIT (c)
			    && (bitmap_ਦੋਆਧਾਰੀ_ਅੰਕ_p (&map_ਸਿਰ, DECL_UID (rt))
				|| bitmap_ਦੋਆਧਾਰੀ_ਅੰਕ_p (&map_ਖੇਤਰ_ਸਿਰ, DECL_UID (rt))
				|| bitmap_ਦੋਆਧਾਰੀ_ਅੰਕ_p (&map_firstprivate_ਸਿਰ,
						 DECL_UID (rt))))
			  {
			    remove = ਸੱਚ;
			    ਰੋਕੋ;
			  }
			ਜੇ (bitmap_ਦੋਆਧਾਰੀ_ਅੰਕ_p (&map_ਖੇਤਰ_ਸਿਰ, DECL_UID (rt)))
			  ਰੋਕੋ;
			ਜੇ (bitmap_ਦੋਆਧਾਰੀ_ਅੰਕ_p (&map_ਸਿਰ, DECL_UID (rt)))
			  {
			    ਜੇ (OMP_CLAUSE_ਕੋਡ (c) != OMP_CLAUSE_MAP)
			      error_at (OMP_CLAUSE_LOCATION (c),
					"%qD appears more than once in motion "
					"clauses", rt);
			    ਨਹੀਂਤਾਂ ਜੇ (openacc)
			      error_at (OMP_CLAUSE_LOCATION (c),
					"%qD appears more than once in data "
					"clauses", rt);
			    ਨਹੀਂਤਾਂ
			      error_at (OMP_CLAUSE_LOCATION (c),
					"%qD appears more than once in map "
					"clauses", rt);
			    remove = ਸੱਚ;
			  }
			ਨਹੀਂਤਾਂ
			  {
			    bitmap_ਸੈੱਟ_ਦੋਆਧਾਰੀ_ਅੰਕ (&map_ਸਿਰ, DECL_UID (rt));
			    bitmap_ਸੈੱਟ_ਦੋਆਧਾਰੀ_ਅੰਕ (&map_ਖੇਤਰ_ਸਿਰ, DECL_UID (rt));
			  }
		      }
		  }
		ਜੇ (c_oacc_check_attachments (c))
		  remove = ਸੱਚ;
		ਜੇ (OMP_CLAUSE_ਕੋਡ (c) == OMP_CLAUSE_MAP
		    && (OMP_CLAUSE_MAP_ਕਿਸਮ (c) == GOMP_MAP_ATTACH
			|| OMP_CLAUSE_MAP_ਕਿਸਮ (c) == GOMP_MAP_DETACH)
		    && !OMP_CLAUSE_ਮਾਪ (c))
		  /* In this case, we have a single array element which is a
		     pointer, and we already set OMP_CLAUSE_SIZE in
		     handle_omp_array_sections above.  For attach/detach
		     clauses, reset the OMP_CLAUSE_SIZE (representing a bias)
		     to zero here.  */
		  OMP_CLAUSE_ਮਾਪ (c) = ਮਾਪ_zero_ਗੰਢ;
		ਰੋਕੋ;
	      }
	    ਨਹੀਂਤਾਂ ਜੇ (!omp_parse_ਵਿਅੰਜਕ (addr_ਟੋਕਨ, t))
	      {
		sorry_at (OMP_CLAUSE_LOCATION (c),
			  "unsupported map expression %qE",
			  OMP_CLAUSE_DECL (c));
		remove = ਸੱਚ;
		ਰੋਕੋ;
	      }
	    ਜੇ (t == error_mark_ਗੰਢ)
	      {
		remove = ਸੱਚ;
		ਰੋਕੋ;
	      }

	    ਰੁੱਖ attr;
	    ਜੇ (DECL_P (t)
		&& OMP_CLAUSE_ਕੋਡ (c) == OMP_CLAUSE_MAP
		&& (attr = lookup_attribute ("omp declare target",
					     DECL_ਗੁਣ (t)))
		&& ਮੁੱਲ_member (get_identifier ("local"),
				 ਰੁੱਖ_ਮੁੱਲ (attr)))
	      {
		error_at (OMP_CLAUSE_LOCATION (c),
			  "device-local variable %qD cannot appear "
			  "in map clause", t);
		remove = ਸੱਚ;
		ਰੋਕੋ;
	      }

	    /* OpenACC attach / detach clauses must be pointers.  */
	    ਜੇ (c_oacc_check_attachments (c))
	      {
		remove = ਸੱਚ;
		ਰੋਕੋ;
	      }
	    ਜੇ (OMP_CLAUSE_ਕੋਡ (c) == OMP_CLAUSE_MAP
		&& (OMP_CLAUSE_MAP_ਕਿਸਮ (c) == GOMP_MAP_ATTACH
		    || OMP_CLAUSE_MAP_ਕਿਸਮ (c) == GOMP_MAP_DETACH)
		&& !OMP_CLAUSE_ਮਾਪ (c))
	      /* For attach/detach clauses, set OMP_CLAUSE_SIZE (representing a
		 bias) to zero here, so it is not set erroneously to the pointer
		 size later on in gimplify.cc.  */
	      OMP_CLAUSE_ਮਾਪ (c) = ਮਾਪ_zero_ਗੰਢ;

	    c_omp_ਪਤਾ_inspector ai (OMP_CLAUSE_LOCATION (c), t);

	    ਜੇ (!ai.check_clause (c))
	      {
		remove = ਸੱਚ;
		ਰੋਕੋ;
	      }

	    ਜੇ (!ai.map_supported_p ())
	      {
		sorry_at (OMP_CLAUSE_LOCATION (c),
			  "unsupported map expression %qE",
			  OMP_CLAUSE_DECL (c));
		remove = ਸੱਚ;
		ਰੋਕੋ;
	      }

	    gcc_assert ((addr_ਟੋਕਨ[0]->type == ARRAY_ਅਧਾਰ
			 || addr_ਟੋਕਨ[0]->type == STRUCTURE_ਅਧਾਰ)
			&& addr_ਟੋਕਨ[1]->type == ACCESS_ਵਿਧੀ);

	    t = addr_ਟੋਕਨ[1]->ਵਿਅੰਜਕ;

	    ਜੇ (addr_ਟੋਕਨ[0]->u.structure_ਅਧਾਰ_ਕਿਸਮ != ਅਧਾਰ_DECL)
	      ਜਾਓ skip_decl_checks;

	    /* For OpenMP, we can access a struct "t" and "t.d" on the same
	       mapping.  OpenACC allows multiple fields of the same structure
	       to be written.  */
	    ਜੇ (addr_ਟੋਕਨ[0]->type == STRUCTURE_ਅਧਾਰ
		&& (bitmap_ਦੋਆਧਾਰੀ_ਅੰਕ_p (&map_ਖੇਤਰ_ਸਿਰ, DECL_UID (t))
		    || (!openacc && bitmap_ਦੋਆਧਾਰੀ_ਅੰਕ_p (&map_ਸਿਰ, DECL_UID (t)))))
	      ਜਾਓ skip_decl_checks;

	    ਜੇ (!VAR_P (t) && ਰੁੱਖ_ਕੋਡ (t) != PARM_DECL)
	      {
		ਜੇ (ort != C_ORT_ACC && ਵਿਅੰਜਕ_P (t))
		  ਰੋਕੋ;

		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qE is not a variable in %qs clause", t,
			  omp_clause_ਕੋਡ_name[OMP_CLAUSE_ਕੋਡ (c)]);
		remove = ਸੱਚ;
	      }
	    ਨਹੀਂਤਾਂ ਜੇ (VAR_P (t) && DECL_THREAD_LOCAL_P (t))
	      {
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD is threadprivate variable in %qs clause", t,
			  omp_clause_ਕੋਡ_name[OMP_CLAUSE_ਕੋਡ (c)]);
		remove = ਸੱਚ;
	      }
	    ਨਹੀਂਤਾਂ ਜੇ ((OMP_CLAUSE_ਕੋਡ (c) != OMP_CLAUSE_MAP
		      || (OMP_CLAUSE_MAP_ਕਿਸਮ (c)
			  != GOMP_MAP_FIRSTPRIVATE_ਸੂਚਕ))
		     && !c_mark_addressable (t))
	      remove = ਸੱਚ;
	    ਨਹੀਂਤਾਂ ਜੇ (!(OMP_CLAUSE_ਕੋਡ (c) == OMP_CLAUSE_MAP
		       && (OMP_CLAUSE_MAP_ਕਿਸਮ (c) == GOMP_MAP_ਸੂਚਕ
			   || (OMP_CLAUSE_MAP_ਕਿਸਮ (c)
			       == GOMP_MAP_FIRSTPRIVATE_ਸੂਚਕ)
			   || (OMP_CLAUSE_MAP_ਕਿਸਮ (c)
			       == GOMP_MAP_FORCE_DEVICEPTR)))
		     && t == OMP_CLAUSE_DECL (c)
		     && !omp_mappable_type (ਰੁੱਖ_TYPE (t)))
	      {
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD does not have a mappable type in %qs clause", t,
			  omp_clause_ਕੋਡ_name[OMP_CLAUSE_ਕੋਡ (c)]);
		remove = ਸੱਚ;
	      }
	    ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_TYPE (t) == error_mark_ਗੰਢ)
	      remove = ਸੱਚ;
	    ਨਹੀਂਤਾਂ ਜੇ (TYPE_ATOMIC (strip_array_types (ਰੁੱਖ_TYPE (t))))
	      {
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%<_Atomic%> %qE in %qs clause", t,
			  omp_clause_ਕੋਡ_name[OMP_CLAUSE_ਕੋਡ (c)]);
		remove = ਸੱਚ;
	      }
	    ਨਹੀਂਤਾਂ ਜੇ (OMP_CLAUSE_ਕੋਡ (c) == OMP_CLAUSE_MAP
		     && OMP_CLAUSE_MAP_IMPLICIT (c)
		     && (bitmap_ਦੋਆਧਾਰੀ_ਅੰਕ_p (&map_ਸਿਰ, DECL_UID (t))
			 || bitmap_ਦੋਆਧਾਰੀ_ਅੰਕ_p (&map_ਖੇਤਰ_ਸਿਰ, DECL_UID (t))
			 || bitmap_ਦੋਆਧਾਰੀ_ਅੰਕ_p (&map_firstprivate_ਸਿਰ,
					  DECL_UID (t))))
	      remove = ਸੱਚ;
	    ਨਹੀਂਤਾਂ ਜੇ (OMP_CLAUSE_ਕੋਡ (c) == OMP_CLAUSE_MAP
		     && (OMP_CLAUSE_MAP_ਕਿਸਮ (c)
			 == GOMP_MAP_FIRSTPRIVATE_ਸੂਚਕ))
	      {
		ਜੇ (bitmap_ਦੋਆਧਾਰੀ_ਅੰਕ_p (&generic_ਸਿਰ, DECL_UID (t))
		    || bitmap_ਦੋਆਧਾਰੀ_ਅੰਕ_p (&firstprivate_ਸਿਰ, DECL_UID (t))
		    || bitmap_ਦੋਆਧਾਰੀ_ਅੰਕ_p (&map_firstprivate_ਸਿਰ, DECL_UID (t)))
		  {
		    error_at (OMP_CLAUSE_LOCATION (c),
			      "%qD appears more than once in data clauses", t);
		    remove = ਸੱਚ;
		  }
		ਨਹੀਂਤਾਂ ਜੇ (bitmap_ਦੋਆਧਾਰੀ_ਅੰਕ_p (&map_ਸਿਰ, DECL_UID (t))
			 && !bitmap_ਦੋਆਧਾਰੀ_ਅੰਕ_p (&map_ਖੇਤਰ_ਸਿਰ, DECL_UID (t))
			 && openacc)
		  {
		    error_at (OMP_CLAUSE_LOCATION (c),
			      "%qD appears more than once in data clauses", t);
		    remove = ਸੱਚ;
		  }
		ਨਹੀਂਤਾਂ
		  bitmap_ਸੈੱਟ_ਦੋਆਧਾਰੀ_ਅੰਕ (&map_firstprivate_ਸਿਰ, DECL_UID (t));
	      }
	    ਨਹੀਂਤਾਂ ਜੇ (bitmap_ਦੋਆਧਾਰੀ_ਅੰਕ_p (&map_ਸਿਰ, DECL_UID (t))
		     && !bitmap_ਦੋਆਧਾਰੀ_ਅੰਕ_p (&map_ਖੇਤਰ_ਸਿਰ, DECL_UID (t))
		     && ort != C_ORT_OMP
		     && ort != C_ORT_OMP_ਨਿਸ਼ਾਨਾ
		     && ort != C_ORT_OMP_EXIT_ਅੰਕੜੇ)
	      {
		ਜੇ (OMP_CLAUSE_ਕੋਡ (c) != OMP_CLAUSE_MAP)
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD appears more than once in motion clauses", t);
		ਨਹੀਂਤਾਂ ਜੇ (openacc)
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD appears more than once in data clauses", t);
		ਨਹੀਂਤਾਂ
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD appears more than once in map clauses", t);
		remove = ਸੱਚ;
	      }
	    ਨਹੀਂਤਾਂ ਜੇ (openacc && bitmap_ਦੋਆਧਾਰੀ_ਅੰਕ_p (&generic_ਸਿਰ, DECL_UID (t)))
	      {
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD appears more than once in data clauses", t);
		remove = ਸੱਚ;
	      }
	    ਨਹੀਂਤਾਂ ਜੇ (bitmap_ਦੋਆਧਾਰੀ_ਅੰਕ_p (&firstprivate_ਸਿਰ, DECL_UID (t))
		     || bitmap_ਦੋਆਧਾਰੀ_ਅੰਕ_p (&is_on_device_ਸਿਰ, DECL_UID (t)))
	      {
		ਜੇ (openacc)
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD appears more than once in data clauses", t);
		ਨਹੀਂਤਾਂ
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD appears both in data and map clauses", t);
		remove = ਸੱਚ;
	      }
	    ਨਹੀਂਤਾਂ ਜੇ (!omp_access_chain_p (addr_ਟੋਕਨ, 1))
	      {
		bitmap_ਸੈੱਟ_ਦੋਆਧਾਰੀ_ਅੰਕ (&map_ਸਿਰ, DECL_UID (t));
		ਜੇ (t != OMP_CLAUSE_DECL (c)
		    && ਰੁੱਖ_ਕੋਡ (OMP_CLAUSE_DECL (c)) == COMPONENT_REF)
		  bitmap_ਸੈੱਟ_ਦੋਆਧਾਰੀ_ਅੰਕ (&map_ਖੇਤਰ_ਸਿਰ, DECL_UID (t));
	      }

	  skip_decl_checks:
	    /* If we call omp_expand_map_clause in handle_omp_array_sections,
	       the containing loop (here) iterates through the new nodes
	       created by that expansion.  Avoid expanding those again (just
	       by checking the node type).  */
	    ਜੇ (!remove
		&& ort != C_ORT_DECLARE_SIMD
		&& (OMP_CLAUSE_ਕੋਡ (c) != OMP_CLAUSE_MAP
		    || (OMP_CLAUSE_MAP_ਕਿਸਮ (c) != GOMP_MAP_FIRSTPRIVATE_ਸੂਚਕ
			&& (OMP_CLAUSE_MAP_ਕਿਸਮ (c)
			    != GOMP_MAP_FIRSTPRIVATE_REFERENCE)
			&& OMP_CLAUSE_MAP_ਕਿਸਮ (c) != GOMP_MAP_ALWAYS_ਸੂਚਕ
			&& OMP_CLAUSE_MAP_ਕਿਸਮ (c) != GOMP_MAP_ATTACH_DETACH
			&& OMP_CLAUSE_MAP_ਕਿਸਮ (c) != GOMP_MAP_ATTACH
			&& OMP_CLAUSE_MAP_ਕਿਸਮ (c) != GOMP_MAP_DETACH)))
	      {
		grp_ਸ਼ੁਰੂ_p = pc;
		grp_sentinel = OMP_CLAUSE_CHAIN (c);
		ਰੁੱਖ nc = ai.expand_map_clause (c, OMP_CLAUSE_DECL (c),
						addr_ਟੋਕਨ, ort);
		ਜੇ (nc != error_mark_ਗੰਢ)
		  c = nc;
	      }
	  }
	  ਰੋਕੋ;

	ਹਾਲਤ OMP_CLAUSE_ENTER:
	ਹਾਲਤ OMP_CLAUSE_LINK:
	ਹਾਲਤ OMP_CLAUSE_LOCAL:
	  t = OMP_CLAUSE_DECL (c);
	  ਅਚਲ ਅੱਖਰ *cname;
	  cname = omp_clause_ਕੋਡ_name[OMP_CLAUSE_ਕੋਡ (c)];
	  ਜੇ (OMP_CLAUSE_ਕੋਡ (c) == OMP_CLAUSE_ENTER
	      && OMP_CLAUSE_ENTER_ਮੰਜ਼ਿਲ (c))
	    cname = "to";
	  ਜੇ (ਰੁੱਖ_ਕੋਡ (t) == FUNCTION_DECL
	      && OMP_CLAUSE_ਕੋਡ (c) == OMP_CLAUSE_ENTER)
	    ;
	  ਨਹੀਂਤਾਂ ਜੇ (!VAR_P (t))
	    {
	      ਜੇ (OMP_CLAUSE_ਕੋਡ (c) == OMP_CLAUSE_ENTER)
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qE is neither a variable nor a function name in "
			  "clause %qs", t, cname);
	      ਨਹੀਂਤਾਂ
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qE is not a variable in clause %qs", t, cname);
	      remove = ਸੱਚ;
	    }
	  ਨਹੀਂਤਾਂ ਜੇ (DECL_THREAD_LOCAL_P (t))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qD is threadprivate variable in %qs clause", t,
			cname);
	      remove = ਸੱਚ;
	    }
	  ਨਹੀਂਤਾਂ ਜੇ (!omp_mappable_type (ਰੁੱਖ_TYPE (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qD does not have a mappable type in %qs clause", t,
			cname);
	      remove = ਸੱਚ;
	    }
	  ਜੇ (remove)
	    ਰੋਕੋ;
	  ਜੇ (bitmap_ਦੋਆਧਾਰੀ_ਅੰਕ_p (&generic_ਸਿਰ, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE appears more than once on the same "
			"%<declare target%> directive", t);
	      remove = ਸੱਚ;
	    }
	  ਨਹੀਂਤਾਂ
	    bitmap_ਸੈੱਟ_ਦੋਆਧਾਰੀ_ਅੰਕ (&generic_ਸਿਰ, DECL_UID (t));
	  ਰੋਕੋ;

	ਹਾਲਤ OMP_CLAUSE_ਇਕਸਾਰ:
	  t = OMP_CLAUSE_DECL (c);
	  ਜੇ (ਰੁੱਖ_ਕੋਡ (t) != PARM_DECL)
	    {
	      ਜੇ (DECL_P (t))
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD is not an argument in %<uniform%> clause", t);
	      ਨਹੀਂਤਾਂ
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qE is not an argument in %<uniform%> clause", t);
	      remove = ਸੱਚ;
	      ਰੋਕੋ;
	    }
	  /* map_head bitmap is used as uniform_head if declare_simd.  */
	  bitmap_ਸੈੱਟ_ਦੋਆਧਾਰੀ_ਅੰਕ (&map_ਸਿਰ, DECL_UID (t));
	  ਜਾਓ check_dup_generic;

	ਹਾਲਤ OMP_CLAUSE_IS_DEVICE_PTR:
	ਹਾਲਤ OMP_CLAUSE_USE_DEVICE_PTR:
	  t = OMP_CLAUSE_DECL (c);
	  ਜੇ (OMP_CLAUSE_ਕੋਡ (c) == OMP_CLAUSE_IS_DEVICE_PTR)
	    bitmap_ਸੈੱਟ_ਦੋਆਧਾਰੀ_ਅੰਕ (&is_on_device_ਸਿਰ, DECL_UID (t));
	  ਜੇ (ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (t)) != ਸੂਚਕ_TYPE)
	    {
	      ਜੇ (OMP_CLAUSE_ਕੋਡ (c) == OMP_CLAUSE_USE_DEVICE_PTR
		  && !openacc)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qs variable is not a pointer",
			    omp_clause_ਕੋਡ_name[OMP_CLAUSE_ਕੋਡ (c)]);
		  remove = ਸੱਚ;
		}
	      ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (t)) != ARRAY_TYPE)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qs variable is neither a pointer nor an array",
			    omp_clause_ਕੋਡ_name[OMP_CLAUSE_ਕੋਡ (c)]);
		  remove = ਸੱਚ;
		}
	    }
	  ਜਾਓ check_dup_generic;

	ਹਾਲਤ OMP_CLAUSE_HAS_DEVICE_ADDR:
	  t = OMP_CLAUSE_DECL (c);
	  ਜੇ (ਰੁੱਖ_ਕੋਡ (t) == OMP_ARRAY_SECTION)
	    {
	      ਜੇ (handle_omp_array_sections (c, ort))
		remove = ਸੱਚ;
	      ਨਹੀਂਤਾਂ
		{
		  t = OMP_CLAUSE_DECL (c);
		  ਜਦੋਂ (ਰੁੱਖ_ਕੋਡ (t) == ARRAY_REF)
		    t = ਰੁੱਖ_ਸੰਕਾਰਜ (t, 0);
		}
	    }
	  bitmap_ਸੈੱਟ_ਦੋਆਧਾਰੀ_ਅੰਕ (&is_on_device_ਸਿਰ, DECL_UID (t));
	  ਜੇ (VAR_P (t) || ਰੁੱਖ_ਕੋਡ (t) == PARM_DECL)
	    c_mark_addressable (t);
	  ਜਾਓ check_dup_generic_t;

	ਹਾਲਤ OMP_CLAUSE_USE_DEVICE_ADDR:
	  t = OMP_CLAUSE_DECL (c);
	  ਜੇ (VAR_P (t) || ਰੁੱਖ_ਕੋਡ (t) == PARM_DECL)
	    c_mark_addressable (t);
	  ਜਾਓ check_dup_generic;

	ਹਾਲਤ OMP_CLAUSE_NOWAIT:
	  ਜੇ (copyprivate_ਵੇਖਿਆ)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<nowait%> clause must not be used together "
			"with %<copyprivate%> clause");
	      remove = ਸੱਚ;
	      ਰੋਕੋ;
	    }
	  nowait_clause = pc;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  ਜਾਰੀ;

	ਹਾਲਤ OMP_CLAUSE_ਕ੍ਰਮ:
	  ਜੇ (ordered_clause)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<order%> clause must not be used together "
			"with %<ordered%> clause");
	      remove = ਸੱਚ;
	      ਰੋਕੋ;
	    }
	  ਨਹੀਂਤਾਂ ਜੇ (ਕ੍ਰਮ_clause)
	    {
	      /* Silently remove duplicates.  */
	      remove = ਸੱਚ;
	      ਰੋਕੋ;
	    }
	  ਕ੍ਰਮ_clause = pc;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  ਜਾਰੀ;

	ਹਾਲਤ OMP_CLAUSE_DETACH:
	  t = OMP_CLAUSE_DECL (c);
	  ਜੇ (detach_ਵੇਖਿਆ)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"too many %qs clauses on a task construct",
			"detach");
	      remove = ਸੱਚ;
	      ਰੋਕੋ;
	    }
	  detach_ਵੇਖਿਆ = pc;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  c_mark_addressable (t);
	  ਜਾਰੀ;

	ਹਾਲਤ OMP_CLAUSE_IF:
	ਹਾਲਤ OMP_CLAUSE_SELF:
	ਹਾਲਤ OMP_CLAUSE_ਅੰਕ_ਧਾਗੇ:
	ਹਾਲਤ OMP_CLAUSE_ਅੰਕ_TEAMS:
	ਹਾਲਤ OMP_CLAUSE_THREAD_ਹੱਦਬੰਦੀ:
	ਹਾਲਤ OMP_CLAUSE_DEFAULT:
	ਹਾਲਤ OMP_CLAUSE_UNTIED:
	ਹਾਲਤ OMP_CLAUSE_COLLAPSE:
	ਹਾਲਤ OMP_CLAUSE_FINAL:
	ਹਾਲਤ OMP_CLAUSE_DEVICE:
	ਹਾਲਤ OMP_CLAUSE_DIST_ਸਮਾਂ_ਸਾਰਣੀ:
	ਹਾਲਤ OMP_CLAUSE_DYN_GROUPPRIVATE:
	ਹਾਲਤ OMP_CLAUSE_PARALLEL:
	ਹਾਲਤ OMP_CLAUSE_FOR:
	ਹਾਲਤ OMP_CLAUSE_SECTIONS:
	ਹਾਲਤ OMP_CLAUSE_TASKGROUP:
	ਹਾਲਤ OMP_CLAUSE_PROC_BIND:
	ਹਾਲਤ OMP_CLAUSE_DEVICE_TYPE:
	ਹਾਲਤ OMP_CLAUSE_ਤਰਜੀਹ:
	ਹਾਲਤ OMP_CLAUSE_ਧਾਗੇ:
	ਹਾਲਤ OMP_CLAUSE_SIMD:
	ਹਾਲਤ OMP_CLAUSE_HINT:
	ਹਾਲਤ OMP_CLAUSE_FILTER:
	ਹਾਲਤ OMP_CLAUSE_DEFAULTMAP:
	ਹਾਲਤ OMP_CLAUSE_BIND:
	ਹਾਲਤ OMP_CLAUSE_ਅੰਕ_GANGS:
	ਹਾਲਤ OMP_CLAUSE_ਅੰਕ_WORKERS:
	ਹਾਲਤ OMP_CLAUSE_ਸਦਿਸ਼_ਲੰਮਾਈ:
	ਹਾਲਤ OMP_CLAUSE_ASYNC:
	ਹਾਲਤ OMP_CLAUSE_WAIT:
	ਹਾਲਤ OMP_CLAUSE_AUTO:
	ਹਾਲਤ OMP_CLAUSE_INDEPENDENT:
	ਹਾਲਤ OMP_CLAUSE_SEQ:
	ਹਾਲਤ OMP_CLAUSE_GANG:
	ਹਾਲਤ OMP_CLAUSE_ਕਾਮਾ:
	ਹਾਲਤ OMP_CLAUSE_ਸਦਿਸ਼:
	ਹਾਲਤ OMP_CLAUSE_TILE:
	ਹਾਲਤ OMP_CLAUSE_IF_PRESENT:
	ਹਾਲਤ OMP_CLAUSE_FINALIZE:
	ਹਾਲਤ OMP_CLAUSE_NOHOST:
	ਹਾਲਤ OMP_CLAUSE_ਅਸਿੱਧਾ:
	ਹਾਲਤ OMP_CLAUSE_NOVARIANTS:
	ਹਾਲਤ OMP_CLAUSE_NOCONTEXT:
	  pc = &OMP_CLAUSE_CHAIN (c);
	  ਜਾਰੀ;

	ਹਾਲਤ OMP_CLAUSE_GRAINSIZE:
	  grainsize_ਵੇਖਿਆ = pc;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  ਜਾਰੀ;

	ਹਾਲਤ OMP_CLAUSE_ਅੰਕ_TASKS:
	  ਅੰਕ_tasks_ਵੇਖਿਆ = ਸੱਚ;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  ਜਾਰੀ;

	ਹਾਲਤ OMP_CLAUSE_MERGEABLE:
	  mergeable_ਵੇਖਿਆ = ਸੱਚ;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  ਜਾਰੀ;

	ਹਾਲਤ OMP_CLAUSE_NOGROUP:
	  nogroup_ਵੇਖਿਆ = pc;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  ਜਾਰੀ;

	ਹਾਲਤ OMP_CLAUSE_ਸਮਾਂ_ਸਾਰਣੀ:
	  ਸਮਾਂ_ਸਾਰਣੀ_clause = c;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  ਜਾਰੀ;

	ਹਾਲਤ OMP_CLAUSE_ORDERED:
	  ordered_clause = c;
	  ਜੇ (ਕ੍ਰਮ_clause)
	    {
	      error_at (OMP_CLAUSE_LOCATION (*ਕ੍ਰਮ_clause),
			"%<order%> clause must not be used together "
			"with %<ordered%> clause");
	      *ਕ੍ਰਮ_clause = OMP_CLAUSE_CHAIN (*ਕ੍ਰਮ_clause);
	      ਕ੍ਰਮ_clause = ਨਿਰਾ;
	    }
	  pc = &OMP_CLAUSE_CHAIN (c);
	  ਜਾਰੀ;

	ਹਾਲਤ OMP_CLAUSE_SAFELEN:
	  safelen = c;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  ਜਾਰੀ;
	ਹਾਲਤ OMP_CLAUSE_SIMDLEN:
	  simdlen = c;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  ਜਾਰੀ;

	ਹਾਲਤ OMP_CLAUSE_ਭਰਿਆ:
	  ਭਰਿਆ_ਵੇਖਿਆ = pc;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  ਜਾਰੀ;

	ਹਾਲਤ OMP_CLAUSE_PARTIAL:
	  partial_ਵੇਖਿਆ = ਸੱਚ;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  ਜਾਰੀ;

	ਹਾਲਤ OMP_CLAUSE_SIZES:
	  pc = &OMP_CLAUSE_CHAIN (c);
	  ਜਾਰੀ;

	ਹਾਲਤ OMP_CLAUSE_INBRANCH:
	ਹਾਲਤ OMP_CLAUSE_NOTINBRANCH:
	  ਜੇ (branch_ਵੇਖਿਆ)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<inbranch%> clause is incompatible with "
			"%<notinbranch%>");
	      remove = ਸੱਚ;
	      ਰੋਕੋ;
	    }
	  branch_ਵੇਖਿਆ = ਸੱਚ;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  ਜਾਰੀ;

	ਹਾਲਤ OMP_CLAUSE_INCLUSIVE:
	ਹਾਲਤ OMP_CLAUSE_EXCLUSIVE:
	  need_complete = ਸੱਚ;
	  need_implicitly_determined = ਸੱਚ;
	  t = OMP_CLAUSE_DECL (c);
	  ਜੇ (!VAR_P (t) && ਰੁੱਖ_ਕੋਡ (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in clause %qs", t,
			omp_clause_ਕੋਡ_name[OMP_CLAUSE_ਕੋਡ (c)]);
	      remove = ਸੱਚ;
	    }
	  ਰੋਕੋ;

	ਹਾਲਤ OMP_CLAUSE_INIT:
	  init_ਵੇਖਿਆ = ਸੱਚ;
	  ਜੇ (!OMP_CLAUSE_INIT_TARGETSYNC (c))
	    init_no_targetsync_clause = c;
	  /* FALLTHRU */
	ਹਾਲਤ OMP_CLAUSE_DESTROY:
	ਹਾਲਤ OMP_CLAUSE_USE:
	  init_use_destroy_ਵੇਖਿਆ = ਸੱਚ;
	  t = OMP_CLAUSE_DECL (c);
	  ਜੇ (bitmap_ਦੋਆਧਾਰੀ_ਅੰਕ_p (&generic_ਸਿਰ, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qD appears more than once in action clauses", t);
	      remove = ਸੱਚ;
	      ਰੋਕੋ;
	    }
	  bitmap_ਸੈੱਟ_ਦੋਆਧਾਰੀ_ਅੰਕ (&generic_ਸਿਰ, DECL_UID (t));
	  /* FALLTHRU */
	ਹਾਲਤ OMP_CLAUSE_INTEROP:
	  ਜੇ (/* ort == C_ORT_OMP_INTEROP [uncomment for depobj init]  */
		   !c_omp_interop_t_p (ਰੁੱਖ_TYPE (OMP_CLAUSE_DECL (c))))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qD must be of %<omp_interop_t%>",
			OMP_CLAUSE_DECL (c));
	      remove = ਸੱਚ;
	    }
	  ਨਹੀਂਤਾਂ ਜੇ ((OMP_CLAUSE_ਕੋਡ (c) == OMP_CLAUSE_INIT
		    || OMP_CLAUSE_ਕੋਡ (c) == OMP_CLAUSE_DESTROY)
		   && ਰੁੱਖ_READONLY (OMP_CLAUSE_DECL (c)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
		      "%qD shall not be const", OMP_CLAUSE_DECL (c));
	      remove = ਸੱਚ;
	    }
	  pc = &OMP_CLAUSE_CHAIN (c);
	  ਰੋਕੋ;
	ਮੂਲ:
	  gcc_unreachable ();
	}

      ਜੇ (!remove)
	{
	  t = OMP_CLAUSE_DECL (c);

	  ਜੇ (need_complete)
	    {
	      t = require_complete_type (OMP_CLAUSE_LOCATION (c), t);
	      ਜੇ (t == error_mark_ਗੰਢ)
		remove = ਸੱਚ;
	    }

	  ਜੇ (need_implicitly_determined)
	    {
	      ਅਚਲ ਅੱਖਰ *share_name = ਨਿਰਾ;

	      ਜੇ (VAR_P (t) && DECL_THREAD_LOCAL_P (t))
		share_name = "threadprivate";
	      ਨਹੀਂਤਾਂ ਚੋਣ (c_omp_predetermined_sharing (t))
		{
		ਹਾਲਤ OMP_CLAUSE_DEFAULT_UNSPECIFIED:
		  ਰੋਕੋ;
		ਹਾਲਤ OMP_CLAUSE_DEFAULT_SHARED:
		  ਜੇ ((OMP_CLAUSE_ਕੋਡ (c) == OMP_CLAUSE_SHARED
		       || OMP_CLAUSE_ਕੋਡ (c) == OMP_CLAUSE_FIRSTPRIVATE)
		      && c_omp_predefined_variable (t))
		    /* The __func__ variable and similar function-local
		       predefined variables may be listed in a shared or
		       firstprivate clause.  */
		    ਰੋਕੋ;
		  share_name = "shared";
		  ਰੋਕੋ;
		ਹਾਲਤ OMP_CLAUSE_DEFAULT_ਨਿੱਜੀ:
		  share_name = "private";
		  ਰੋਕੋ;
		ਮੂਲ:
		  gcc_unreachable ();
		}
	      ਜੇ (share_name)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qE is predetermined %qs for %qs",
			    t, share_name,
			    omp_clause_ਕੋਡ_name[OMP_CLAUSE_ਕੋਡ (c)]);
		  remove = ਸੱਚ;
		}
	      ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_READONLY (t)
		       && OMP_CLAUSE_ਕੋਡ (c) != OMP_CLAUSE_SHARED
		       && OMP_CLAUSE_ਕੋਡ (c) != OMP_CLAUSE_FIRSTPRIVATE)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%<const%> qualified %qE may appear only in "
			    "%<shared%> or %<firstprivate%> clauses", t);
		  remove = ਸੱਚ;
		}
	    }
	}

      ਜੇ (remove)
	{
	  ਜੇ (grp_ਸ਼ੁਰੂ_p)
	    {
	      /* If we found a clause to remove, we want to remove the whole
		 expanded group, otherwise gimplify
		 (omp_resolve_clause_dependencies) can get confused.  */
	      *grp_ਸ਼ੁਰੂ_p = grp_sentinel;
	      pc = grp_ਸ਼ੁਰੂ_p;
	      grp_ਸ਼ੁਰੂ_p = ਨਿਰਾ;
	    }
	  ਨਹੀਂਤਾਂ
	    *pc = OMP_CLAUSE_CHAIN (c);
	}
      ਨਹੀਂਤਾਂ
	pc = &OMP_CLAUSE_CHAIN (c);
    }

  ਜੇ (grp_ਸ਼ੁਰੂ_p
      && OMP_CLAUSE_HAS_ITERATORS (*grp_ਸ਼ੁਰੂ_p))
    ਲਈ (ਰੁੱਖ gc = *grp_ਸ਼ੁਰੂ_p; gc; gc = OMP_CLAUSE_CHAIN (gc))
      OMP_CLAUSE_ITERATORS (gc) = OMP_CLAUSE_ITERATORS (*grp_ਸ਼ੁਰੂ_p);

  ਜੇ (simdlen
      && safelen
      && ਰੁੱਖ_int_cst_lt (OMP_CLAUSE_SAFELEN_ਵਿਅੰਜਕ (safelen),
			  OMP_CLAUSE_SIMDLEN_ਵਿਅੰਜਕ (simdlen)))
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
      OMP_CLAUSE_SIMDLEN_ਵਿਅੰਜਕ (simdlen)
	= OMP_CLAUSE_SAFELEN_ਵਿਅੰਜਕ (safelen);
    }

  ਜੇ (ordered_clause
      && ਸਮਾਂ_ਸਾਰਣੀ_clause
      && (OMP_CLAUSE_ਸਮਾਂ_ਸਾਰਣੀ_ਕਿਸਮ (ਸਮਾਂ_ਸਾਰਣੀ_clause)
	  & OMP_CLAUSE_ਸਮਾਂ_ਸਾਰਣੀ_NONMONOTONIC))
    {
      error_at (OMP_CLAUSE_LOCATION (ਸਮਾਂ_ਸਾਰਣੀ_clause),
		"%<nonmonotonic%> schedule modifier specified together "
		"with %<ordered%> clause");
      OMP_CLAUSE_ਸਮਾਂ_ਸਾਰਣੀ_ਕਿਸਮ (ਸਮਾਂ_ਸਾਰਣੀ_clause)
	= (ਗਿਣਤੀ omp_clause_ਸਮਾਂ_ਸਾਰਣੀ_ਕਿਸਮ)
	  (OMP_CLAUSE_ਸਮਾਂ_ਸਾਰਣੀ_ਕਿਸਮ (ਸਮਾਂ_ਸਾਰਣੀ_clause)
	   & ~OMP_CLAUSE_ਸਮਾਂ_ਸਾਰਣੀ_NONMONOTONIC);
    }

  ਜੇ (reduction_ਵੇਖਿਆ < 0 && ordered_clause)
    {
      error_at (OMP_CLAUSE_LOCATION (ordered_clause),
		"%qs clause specified together with %<inscan%> "
		"%<reduction%> clause", "ordered");
      reduction_ਵੇਖਿਆ = -2;
    }

  ਜੇ (reduction_ਵੇਖਿਆ < 0 && ਸਮਾਂ_ਸਾਰਣੀ_clause)
    {
      error_at (OMP_CLAUSE_LOCATION (ਸਮਾਂ_ਸਾਰਣੀ_clause),
		"%qs clause specified together with %<inscan%> "
		"%<reduction%> clause", "schedule");
      reduction_ਵੇਖਿਆ = -2;
    }

  ਜੇ (ਰੇਖਿਕ_variable_ਕਦਮ_check
      || reduction_ਵੇਖਿਆ == -2
      || allocate_ਵੇਖਿਆ
      || ਨਿਸ਼ਾਨਾ_ਵਿੱਚ_reduction_ਵੇਖਿਆ)
    ਲਈ (pc = &clauses, c = clauses; c ; c = *pc)
      {
	ਤਾਰਕਿਕ remove = ਝੂਠ;
	ਜੇ (allocate_ਵੇਖਿਆ)
	  ਚੋਣ (OMP_CLAUSE_ਕੋਡ (c))
	    {
	    ਹਾਲਤ OMP_CLAUSE_REDUCTION:
	    ਹਾਲਤ OMP_CLAUSE_ਵਿੱਚ_REDUCTION:
	    ਹਾਲਤ OMP_CLAUSE_TASK_REDUCTION:
	      ਜੇ (ਰੁੱਖ_ਕੋਡ (OMP_CLAUSE_DECL (c)) == MEM_REF)
		{
		  t = ਰੁੱਖ_ਸੰਕਾਰਜ (OMP_CLAUSE_DECL (c), 0);
		  ਜੇ (ਰੁੱਖ_ਕੋਡ (t) == ਸੂਚਕ_PLUS_ਵਿਅੰਜਕ)
		    t = ਰੁੱਖ_ਸੰਕਾਰਜ (t, 0);
		  ਜੇ (ਰੁੱਖ_ਕੋਡ (t) == ADDR_ਵਿਅੰਜਕ
		      || ਅਸਿੱਧਾ_REF_P (t))
		    t = ਰੁੱਖ_ਸੰਕਾਰਜ (t, 0);
		  ਜੇ (DECL_P (t))
		    bitmap_clear_ਦੋਆਧਾਰੀ_ਅੰਕ (&aligned_ਸਿਰ, DECL_UID (t));
		  ਰੋਕੋ;
		}
	      /* FALLTHRU */
	    ਹਾਲਤ OMP_CLAUSE_ਨਿੱਜੀ:
	    ਹਾਲਤ OMP_CLAUSE_FIRSTPRIVATE:
	    ਹਾਲਤ OMP_CLAUSE_LASTPRIVATE:
	    ਹਾਲਤ OMP_CLAUSE_ਰੇਖਿਕ:
	      ਜੇ (DECL_P (OMP_CLAUSE_DECL (c)))
		bitmap_clear_ਦੋਆਧਾਰੀ_ਅੰਕ (&aligned_ਸਿਰ,
				  DECL_UID (OMP_CLAUSE_DECL (c)));
	      ਰੋਕੋ;
	    ਮੂਲ:
	      ਰੋਕੋ;
	    }
	ਜੇ (OMP_CLAUSE_ਕੋਡ (c) == OMP_CLAUSE_ਰੇਖਿਕ
	    && OMP_CLAUSE_ਰੇਖਿਕ_VARIABLE_STRIDE (c)
	    && !bitmap_ਦੋਆਧਾਰੀ_ਅੰਕ_p (&map_ਸਿਰ,
			      DECL_UID (OMP_CLAUSE_ਰੇਖਿਕ_ਕਦਮ (c))))
	  {
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%<linear%> clause step is a parameter %qD not "
		      "specified in %<uniform%> clause",
		      OMP_CLAUSE_ਰੇਖਿਕ_ਕਦਮ (c));
	    remove = ਸੱਚ;
	  }
	ਨਹੀਂਤਾਂ ਜੇ (OMP_CLAUSE_ਕੋਡ (c) == OMP_CLAUSE_REDUCTION
		 && reduction_ਵੇਖਿਆ == -2)
	  OMP_CLAUSE_REDUCTION_INSCAN (c) = 0;
	ਜੇ (ਨਿਸ਼ਾਨਾ_ਵਿੱਚ_reduction_ਵੇਖਿਆ
	    && OMP_CLAUSE_ਕੋਡ (c) == OMP_CLAUSE_MAP)
	  {
	    ਰੁੱਖ t = OMP_CLAUSE_DECL (c);
	    ਜਦੋਂ (handled_component_p (t)
		   || ਅਸਿੱਧਾ_REF_P (t)
		   || ਰੁੱਖ_ਕੋਡ (t) == ADDR_ਵਿਅੰਜਕ
		   || ਰੁੱਖ_ਕੋਡ (t) == MEM_REF
		   || ਰੁੱਖ_ਕੋਡ (t) == NON_LVALUE_ਵਿਅੰਜਕ)
	      t = ਰੁੱਖ_ਸੰਕਾਰਜ (t, 0);
	    ਜੇ (DECL_P (t)
		&& bitmap_ਦੋਆਧਾਰੀ_ਅੰਕ_p (&oacc_reduction_ਸਿਰ, DECL_UID (t)))
	      OMP_CLAUSE_MAP_ਵਿੱਚ_REDUCTION (c) = 1;
	  }

	ਜੇ (remove)
	  *pc = OMP_CLAUSE_CHAIN (c);
	ਨਹੀਂਤਾਂ
	  pc = &OMP_CLAUSE_CHAIN (c);
      }

  ਜੇ (allocate_ਵੇਖਿਆ)
    ਲਈ (pc = &clauses, c = clauses; c ; c = *pc)
      {
	ਤਾਰਕਿਕ remove = ਝੂਠ;
	ਜੇ (OMP_CLAUSE_ਕੋਡ (c) == OMP_CLAUSE_ALLOCATE
	    && !OMP_CLAUSE_ALLOCATE_COMBINED (c)
	    && bitmap_ਦੋਆਧਾਰੀ_ਅੰਕ_p (&aligned_ਸਿਰ, DECL_UID (OMP_CLAUSE_DECL (c))))
	  {
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%qD specified in %<allocate%> clause but not in "
		      "an explicit privatization clause", OMP_CLAUSE_DECL (c));
	    remove = ਸੱਚ;
	  }
	ਜੇ (remove)
	  *pc = OMP_CLAUSE_CHAIN (c);
	ਨਹੀਂਤਾਂ
	  pc = &OMP_CLAUSE_CHAIN (c);
      }

  ਜੇ (nogroup_ਵੇਖਿਆ && reduction_ਵੇਖਿਆ)
    {
      error_at (OMP_CLAUSE_LOCATION (*nogroup_ਵੇਖਿਆ),
		"%<nogroup%> clause must not be used together with "
		"%<reduction%> clause");
      *nogroup_ਵੇਖਿਆ = OMP_CLAUSE_CHAIN (*nogroup_ਵੇਖਿਆ);
    }

  ਜੇ (grainsize_ਵੇਖਿਆ && ਅੰਕ_tasks_ਵੇਖਿਆ)
    {
      error_at (OMP_CLAUSE_LOCATION (*grainsize_ਵੇਖਿਆ),
		"%<grainsize%> clause must not be used together with "
		"%<num_tasks%> clause");
      *grainsize_ਵੇਖਿਆ = OMP_CLAUSE_CHAIN (*grainsize_ਵੇਖਿਆ);
    }

  ਜੇ (ਭਰਿਆ_ਵੇਖਿਆ && partial_ਵੇਖਿਆ)
    {
      error_at (OMP_CLAUSE_LOCATION (*ਭਰਿਆ_ਵੇਖਿਆ),
		"%<full%> clause must not be used together with "
		"%<partial%> clause");
      *ਭਰਿਆ_ਵੇਖਿਆ = OMP_CLAUSE_CHAIN (*ਭਰਿਆ_ਵੇਖਿਆ);
    }

  ਜੇ (detach_ਵੇਖਿਆ)
    {
      ਜੇ (mergeable_ਵੇਖਿਆ)
	{
	  error_at (OMP_CLAUSE_LOCATION (*detach_ਵੇਖਿਆ),
		    "%<detach%> clause must not be used together with "
		    "%<mergeable%> clause");
	  *detach_ਵੇਖਿਆ = OMP_CLAUSE_CHAIN (*detach_ਵੇਖਿਆ);
	}
      ਨਹੀਂਤਾਂ
	{
	  ਰੁੱਖ detach_decl = OMP_CLAUSE_DECL (*detach_ਵੇਖਿਆ);

	  ਲਈ (pc = &clauses, c = clauses; c ; c = *pc)
	    {
	      ਤਾਰਕਿਕ remove = ਝੂਠ;
	      ਜੇ ((OMP_CLAUSE_ਕੋਡ (c) == OMP_CLAUSE_SHARED
		   || OMP_CLAUSE_ਕੋਡ (c) == OMP_CLAUSE_ਨਿੱਜੀ
		   || OMP_CLAUSE_ਕੋਡ (c) == OMP_CLAUSE_FIRSTPRIVATE
		   || OMP_CLAUSE_ਕੋਡ (c) == OMP_CLAUSE_LASTPRIVATE)
		  && OMP_CLAUSE_DECL (c) == detach_decl)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "the event handle of a %<detach%> clause "
			    "should not be in a data-sharing clause");
		  remove = ਸੱਚ;
		}
	      ਜੇ (remove)
		*pc = OMP_CLAUSE_CHAIN (c);
	      ਨਹੀਂਤਾਂ
		pc = &OMP_CLAUSE_CHAIN (c);
	    }
	}
    }

  ਜੇ (ort == C_ORT_OMP_INTEROP
      && depend_clause
      && (!init_use_destroy_ਵੇਖਿਆ
	  || (init_ਵੇਖਿਆ && init_no_targetsync_clause)))
    {
      error_at (OMP_CLAUSE_LOCATION (depend_clause),
		"%<depend%> clause requires action clauses with "
		"%<targetsync%> interop-type");
      ਜੇ (init_no_targetsync_clause)
	inform (OMP_CLAUSE_LOCATION (init_no_targetsync_clause),
		"%<init%> clause lacks the %<targetsync%> modifier");
    }

  bitmap_obstack_release (ਨਿਰਾ);
  ਵਾਪਸ clauses;
}

/* Do processing necessary to make CLAUSES well-formed, where CLAUSES result
   from implicit instantiation of user-defined mappers (in gimplify.cc).  */

ਰੁੱਖ
c_omp_ਅੰਤ_mapper_clauses (ਰੁੱਖ clauses)
{
  ਵਾਪਸ c_ਅੰਤ_omp_clauses (clauses, C_ORT_OMP);
}

/* Return code to initialize DST with a copy constructor from SRC.
   C doesn't have copy constructors nor assignment operators, only for
   _Atomic vars we need to perform __atomic_load from src into a temporary
   followed by __atomic_store of the temporary to dst.  */

ਰੁੱਖ
c_omp_clause_copy_ctor (ਰੁੱਖ clause, ਰੁੱਖ dst, ਰੁੱਖ src)
{
  ਜੇ (!really_atomic_lvalue (dst) && !really_atomic_lvalue (src))
    ਵਾਪਸ build2 (MODIFY_ਵਿਅੰਜਕ, ਰੁੱਖ_TYPE (dst), dst, src);

  location_t loc = OMP_CLAUSE_LOCATION (clause);
  ਰੁੱਖ type = ਰੁੱਖ_TYPE (dst);
  ਰੁੱਖ nonatomic_type = build_qualified_type (type, TYPE_UNQUALIFIED);
  ਰੁੱਖ tmp = create_tmp_var (nonatomic_type);
  ਰੁੱਖ tmp_addr = build_fold_addr_ਵਿਅੰਜਕ (tmp);
  ਰੁੱਖ_ADDRESSABLE (tmp) = 1;
  suppress_warning (tmp);
  ਰੁੱਖ src_addr = build_fold_addr_ਵਿਅੰਜਕ (src);
  ਰੁੱਖ dst_addr = build_fold_addr_ਵਿਅੰਜਕ (dst);
  ਰੁੱਖ seq_cst = build_int_cst (integer_type_ਗੰਢ, MEMMODEL_SEQ_CST);
  vec<ਰੁੱਖ, va_gc> *params;
  /* Expansion of a generic atomic load may require an addition
     element, so allocate enough to prevent a resize.  */
  vec_alloc (params, 4);

  /* Build __atomic_load (&src, &tmp, SEQ_CST);  */
  ਰੁੱਖ fndecl = builtin_decl_explicit (BUILT_ਵਿੱਚ_ATOMIC_ਲੱਦੋ);
  params->ਤੇਜ਼_ਧੱਕੋ (src_addr);
  params->ਤੇਜ਼_ਧੱਕੋ (tmp_addr);
  params->ਤੇਜ਼_ਧੱਕੋ (seq_cst);
  ਰੁੱਖ ਲੱਦੋ = c_build_function_call_vec (loc, vNULL, fndecl, params, ਨਿਰਾ);

  vec_alloc (params, 4);

  /* Build __atomic_store (&dst, &tmp, SEQ_CST);  */
  fndecl = builtin_decl_explicit (BUILT_ਵਿੱਚ_ATOMIC_STORE);
  params->ਤੇਜ਼_ਧੱਕੋ (dst_addr);
  params->ਤੇਜ਼_ਧੱਕੋ (tmp_addr);
  params->ਤੇਜ਼_ਧੱਕੋ (seq_cst);
  ਰੁੱਖ store = c_build_function_call_vec (loc, vNULL, fndecl, params, ਨਿਰਾ);
  ਵਾਪਸ build2 (COMPOUND_ਵਿਅੰਜਕ, void_type_ਗੰਢ, ਲੱਦੋ, store);
}

/* Create a transaction node.  */

ਰੁੱਖ
c_ਅੰਤ_transaction (location_t loc, ਰੁੱਖ ਖੰਡ, ਪੂਰਨ flags)
{
  ਰੁੱਖ stmt = build_stmt (loc, TRANSACTION_ਵਿਅੰਜਕ, ਖੰਡ);
  ਜੇ (flags & TM_STMT_ATTR_OUTER)
    TRANSACTION_ਵਿਅੰਜਕ_OUTER (stmt) = 1;
  ਜੇ (flags & TM_STMT_ATTR_RELAXED)
    TRANSACTION_ਵਿਅੰਜਕ_RELAXED (stmt) = 1;
  ਵਾਪਸ ਜੋੜੋ_stmt (stmt);
}

/* Make a variant type in the proper way for C/C++, propagating qualifiers
   down to the element type of an array.  If ORIG_QUAL_TYPE is not
   NULL, then it should be used as the qualified type
   ORIG_QUAL_INDIRECT levels down in array type derivation (to
   preserve information about the typedef name from which an array
   type was derived).  */

ਰੁੱਖ
c_build_qualified_type (ਰੁੱਖ type, ਪੂਰਨ type_quals, ਰੁੱਖ orig_qual_type,
			ਮਾਪ_t orig_qual_ਅਸਿੱਧਾ)
{
  ਜੇ (type == error_mark_ਗੰਢ)
    ਵਾਪਸ type;

  ਜੇ (ਰੁੱਖ_ਕੋਡ (type) == ARRAY_TYPE)
    {
      ਰੁੱਖ t;
      ਰੁੱਖ element_type = c_build_qualified_type (ਰੁੱਖ_TYPE (type),
						  type_quals, orig_qual_type,
						  orig_qual_ਅਸਿੱਧਾ - 1);

      /* See if we already have an identically qualified type.  */
      ਜੇ (orig_qual_type && orig_qual_ਅਸਿੱਧਾ == 0)
	t = orig_qual_type;
      ਨਹੀਂਤਾਂ
	ਲਈ (t = TYPE_MAIN_VARIANT (type); t; t = TYPE_ਅਗਲਾ_VARIANT (t))
	  {
	    ਜੇ (TYPE_QUALS (strip_array_types (t)) == type_quals
		&& TYPE_NAME (t) == TYPE_NAME (type)
		&& TYPE_CONTEXT (t) == TYPE_CONTEXT (type)
		&& attribute_list_equal (TYPE_ਗੁਣ (t),
					 TYPE_ਗੁਣ (type)))
	      ਰੋਕੋ;
	  }
      ਜੇ (!t)
	{
          ਰੁੱਖ domain = TYPE_DOMAIN (type);

	  t = build_variant_type_copy (type);
	  ਰੁੱਖ_TYPE (t) = element_type;
	  TYPE_ADDR_SPACE (t) = TYPE_ADDR_SPACE (element_type);

          ਜੇ (TYPE_STRUCTURAL_EQUALITY_P (element_type)
              || (domain && TYPE_STRUCTURAL_EQUALITY_P (domain)))
            ਸੈੱਟ_TYPE_STRUCTURAL_EQUALITY (t);
          ਨਹੀਂਤਾਂ ਜੇ (TYPE_CANONICAL (element_type) != element_type
                   || (domain && TYPE_CANONICAL (domain) != domain))
            {
              ਰੁੱਖ unqualified_canon
		= c_build_array_type (TYPE_CANONICAL (element_type),
				      domain ? TYPE_CANONICAL (domain)
					     : NULL_ਰੁੱਖ);
              ਜੇ (TYPE_ਉਲਟ_STORAGE_ਕ੍ਰਮ (type))
                {
                  unqualified_canon
		    = build_distinct_type_copy (unqualified_canon);
                  TYPE_ਉਲਟ_STORAGE_ਕ੍ਰਮ (unqualified_canon) = 1;
                }
              TYPE_CANONICAL (t)
		= c_build_qualified_type (unqualified_canon, type_quals);
            }
          ਨਹੀਂਤਾਂ
            TYPE_CANONICAL (t) = t;
	}
      ਵਾਪਸ t;
    }

  /* A restrict-qualified pointer type must be a pointer to object or
     incomplete type.  Note that the use of POINTER_TYPE_P also allows
     REFERENCE_TYPEs, which is appropriate for C++.  */
  ਜੇ ((type_quals & TYPE_QUAL_RESTRICT)
      && (!ਸੂਚਕ_TYPE_P (type)
	  || !C_TYPE_OBJECT_OR_INCOMPLETE_P (ਰੁੱਖ_TYPE (type))))
    {
      error ("invalid use of %<restrict%>");
      type_quals &= ~TYPE_QUAL_RESTRICT;
    }

  ਰੁੱਖ var_type = (orig_qual_type && orig_qual_ਅਸਿੱਧਾ == 0
		   ? orig_qual_type
		   : build_qualified_type (type, type_quals));

  gcc_checking_assert (C_TYPE_VARIABLE_ਮਾਪ (var_type)
		       == C_TYPE_VARIABLE_ਮਾਪ (type));
  gcc_checking_assert (c_type_variably_modified_p (var_type)
		       == c_type_variably_modified_p (type));

  /* A variant type does not inherit the list of incomplete vars from the
     type main variant.  */
  ਜੇ ((ਰਿਕਾਰਡ_OR_UNION_TYPE_P (var_type)
       || ਰੁੱਖ_ਕੋਡ (var_type) == ENUMERAL_TYPE)
      && TYPE_MAIN_VARIANT (var_type) != var_type)
    C_TYPE_INCOMPLETE_VARS (var_type) = 0;
  ਵਾਪਸ var_type;
}

/* Build a VA_ARG_EXPR for the C parser.  */

ਰੁੱਖ
c_build_va_arg (location_t loc1, ਰੁੱਖ ਵਿਅੰਜਕ, location_t loc2, ਰੁੱਖ type,
		ਰੁੱਖ type_ਵਿਅੰਜਕ)
{
  ਜੇ (error_ਸੰਕਾਰਜ_p (type))
    ਵਾਪਸ error_mark_ਗੰਢ;
  /* VA_ARG_EXPR cannot be used for a scalar va_list with reverse storage
     order because it takes the address of the expression.  */
  ਨਹੀਂਤਾਂ ਜੇ (handled_component_p (ਵਿਅੰਜਕ)
	   && ਉਲਟ_storage_ਕ੍ਰਮ_for_component_p (ਵਿਅੰਜਕ))
    {
      error_at (loc1, "cannot use %<va_arg%> with reverse storage order");
      ਵਾਪਸ error_mark_ਗੰਢ;
    }
  ਨਹੀਂਤਾਂ ਜੇ (!COMPLETE_TYPE_P (type))
    {
      error_at (loc2, "second argument to %<va_arg%> is of incomplete "
		"type %qT", type);
      ਵਾਪਸ error_mark_ਗੰਢ;
    }
  ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਕੋਡ (type) == FUNCTION_TYPE)
    {
      error_at (loc2, "second argument to %<va_arg%> is a function type %qT",
		type);
      ਵਾਪਸ error_mark_ਗੰਢ;
    }
  ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਕੋਡ (type) == ARRAY_TYPE && C_TYPE_VARIABLE_ਮਾਪ (type)
	   && !flag_isoc99)
    {
      error_at (loc2, "second argument to %<va_arg%> is an array type %qT",
		type);
      ਵਾਪਸ error_mark_ਗੰਢ;
    }
  ਨਹੀਂਤਾਂ ਜੇ (warn_cxx_compat && ਰੁੱਖ_ਕੋਡ (type) == ENUMERAL_TYPE)
    warning_at (loc2, OPT_Wc___compat,
		"C++ requires promoted type, not enum type, in %<va_arg%>");

  ਜੇ (flag_isoc99 && ਰੁੱਖ_ਕੋਡ (type) == ARRAY_TYPE)
    {
      warning_at (loc2, 0, "second argument to %<va_arg%> is an array type %qT",
		  type);
      /* We create a trap but evaluate side effects first.  */
      ਰੁੱਖ trapfn = builtin_decl_explicit (BUILT_ਵਿੱਚ_TRAP);
      trapfn = build_call_ਵਿਅੰਜਕ_loc (loc2, trapfn, 0);
      ਰੁੱਖ e2 = build2 (COMPOUND_ਵਿਅੰਜਕ, void_type_ਗੰਢ, ਵਿਅੰਜਕ, trapfn);
      /* Return a compound literal of the right type.  */
      ਰੁੱਖ e1 = build_compound_literal (loc2, type, ਨਿਰਾ, ਸੱਚ, 0, ਨਿਰਾ);
      ਵਿਅੰਜਕ = build2 (COMPOUND_ਵਿਅੰਜਕ, type, e2, e1);
    }
  ਨਹੀਂਤਾਂ
    ਵਿਅੰਜਕ = build_va_arg (loc2, ਵਿਅੰਜਕ, type);

  ਜੇ (type_ਵਿਅੰਜਕ)
    ਵਿਅੰਜਕ = build2 (COMPOUND_ਵਿਅੰਜਕ, ਰੁੱਖ_TYPE (ਵਿਅੰਜਕ), type_ਵਿਅੰਜਕ, ਵਿਅੰਜਕ);

  ਵਾਪਸ ਵਿਅੰਜਕ;
}

/* Return truthvalue of whether T1 is the same tree structure as T2.
   Return 1 if they are the same. Return false if they are different.  */

ਤਾਰਕਿਕ
c_ਰੁੱਖ_equal (ਰੁੱਖ t1, ਰੁੱਖ t2)
{
  ਗਿਣਤੀ ਰੁੱਖ_ਕੋਡ_2 code1, code2;

  ਜੇ (t1 == t2)
    ਵਾਪਸ ਸੱਚ;
  ਜੇ (!t1 || !t2)
    ਵਾਪਸ ਝੂਠ;

  ਲਈ (code1 = ਰੁੱਖ_ਕੋਡ (t1); code1 == NON_LVALUE_ਵਿਅੰਜਕ;
       code1 = ਰੁੱਖ_ਕੋਡ (t1))
    t1 = ਰੁੱਖ_ਸੰਕਾਰਜ (t1, 0);
  ਲਈ (code2 = ਰੁੱਖ_ਕੋਡ (t2); code2 == NON_LVALUE_ਵਿਅੰਜਕ;
       code2 = ਰੁੱਖ_ਕੋਡ (t2))
    t2 = ਰੁੱਖ_ਸੰਕਾਰਜ (t2, 0);

  /* They might have become equal now.  */
  ਜੇ (t1 == t2)
    ਵਾਪਸ ਸੱਚ;

  ਜੇ (code1 != code2)
    ਵਾਪਸ ਝੂਠ;

  ਜੇ (CONSTANT_CLASS_P (t1) && !comptypes (ਰੁੱਖ_TYPE (t1), ਰੁੱਖ_TYPE (t2)))
    ਵਾਪਸ ਝੂਠ;

  ਚੋਣ (code1)
    {
    ਹਾਲਤ INTEGER_CST:
      ਵਾਪਸ wi::ਮੰਜ਼ਿਲ_wide (t1) == wi::ਮੰਜ਼ਿਲ_wide (t2);

    ਹਾਲਤ REAL_CST:
      ਵਾਪਸ real_equal (&ਰੁੱਖ_REAL_CST (t1), &ਰੁੱਖ_REAL_CST (t2));

    ਹਾਲਤ STRING_CST:
      ਵਾਪਸ ਰੁੱਖ_STRING_ਲੰਮਾਈ (t1) == ਰੁੱਖ_STRING_ਲੰਮਾਈ (t2)
	&& !memcmp (ਰੁੱਖ_STRING_ਸੂਚਕ (t1), ਰੁੱਖ_STRING_ਸੂਚਕ (t2),
		    ਰੁੱਖ_STRING_ਲੰਮਾਈ (t1));

    ਹਾਲਤ FIXED_CST:
      ਵਾਪਸ FIXED_ਮੁੱਲਾਂ_IDENTICAL (ਰੁੱਖ_FIXED_CST (t1),
				     ਰੁੱਖ_FIXED_CST (t2));

    ਹਾਲਤ COMPLEX_CST:
      ਵਾਪਸ c_ਰੁੱਖ_equal (ਰੁੱਖ_REALPART (t1), ਰੁੱਖ_REALPART (t2))
	     && c_ਰੁੱਖ_equal (ਰੁੱਖ_IMAGPART (t1), ਰੁੱਖ_IMAGPART (t2));

    ਹਾਲਤ ਸਦਿਸ਼_CST:
      ਵਾਪਸ ਸੰਕਾਰਜ_equal_p (t1, t2, OEP_ONLY_CONST);

    ਹਾਲਤ CONSTRUCTOR:
      /* We need to do this when determining whether or not two
	 non-type pointer to member function template arguments
	 are the same.  */
      ਜੇ (!comptypes (ਰੁੱਖ_TYPE (t1), ਰੁੱਖ_TYPE (t2))
	  || CONSTRUCTOR_NELTS (t1) != CONSTRUCTOR_NELTS (t2))
	ਵਾਪਸ ਝੂਠ;
      {
	ਰੁੱਖ ਖੇਤਰ_2, ਮੁੱਲ;
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ i;
	FOR_EACH_CONSTRUCTOR_ELT (CONSTRUCTOR_ELTS (t1), i, ਖੇਤਰ_2, ਮੁੱਲ)
	  {
	    constructor_elt *elt2 = CONSTRUCTOR_ELT (t2, i);
	    ਜੇ (!c_ਰੁੱਖ_equal (ਖੇਤਰ_2, elt2->ਸੂਚਕਾਂਕ)
		|| !c_ਰੁੱਖ_equal (ਮੁੱਲ, elt2->ਮੁੱਲ))
	      ਵਾਪਸ ਝੂਠ;
	  }
      }
      ਵਾਪਸ ਸੱਚ;

    ਹਾਲਤ ਰੁੱਖ_LIST:
      ਜੇ (!c_ਰੁੱਖ_equal (ਰੁੱਖ_PURPOSE (t1), ਰੁੱਖ_PURPOSE (t2)))
	ਵਾਪਸ ਝੂਠ;
      ਜੇ (!c_ਰੁੱਖ_equal (ਰੁੱਖ_ਮੁੱਲ (t1), ਰੁੱਖ_ਮੁੱਲ (t2)))
	ਵਾਪਸ ਝੂਠ;
      ਵਾਪਸ c_ਰੁੱਖ_equal (ਰੁੱਖ_CHAIN (t1), ਰੁੱਖ_CHAIN (t2));

    ਹਾਲਤ SAVE_ਵਿਅੰਜਕ:
      ਵਾਪਸ c_ਰੁੱਖ_equal (ਰੁੱਖ_ਸੰਕਾਰਜ (t1, 0), ਰੁੱਖ_ਸੰਕਾਰਜ (t2, 0));

    ਹਾਲਤ CALL_ਵਿਅੰਜਕ:
      {
	ਰੁੱਖ arg1, arg2;
	call_ਵਿਅੰਜਕ_arg_iterator iter1, iter2;
	ਜੇ (!c_ਰੁੱਖ_equal (CALL_ਵਿਅੰਜਕ_FN (t1), CALL_ਵਿਅੰਜਕ_FN (t2)))
	  ਵਾਪਸ ਝੂਠ;
	ਲਈ (arg1 = ਪਹਿਲਾ_call_ਵਿਅੰਜਕ_arg (t1, &iter1),
	       arg2 = ਪਹਿਲਾ_call_ਵਿਅੰਜਕ_arg (t2, &iter2);
	     arg1 && arg2;
	     arg1 = ਅਗਲਾ_call_ਵਿਅੰਜਕ_arg (&iter1),
	       arg2 = ਅਗਲਾ_call_ਵਿਅੰਜਕ_arg (&iter2))
	  ਜੇ (!c_ਰੁੱਖ_equal (arg1, arg2))
	    ਵਾਪਸ ਝੂਠ;
	ਜੇ (arg1 || arg2)
	  ਵਾਪਸ ਝੂਠ;
	ਵਾਪਸ ਸੱਚ;
      }

    ਹਾਲਤ ਨਿਸ਼ਾਨਾ_ਵਿਅੰਜਕ:
      {
	ਰੁੱਖ o1 = ਰੁੱਖ_ਸੰਕਾਰਜ (t1, 0);
	ਰੁੱਖ o2 = ਰੁੱਖ_ਸੰਕਾਰਜ (t2, 0);

	/* Special case: if either target is an unallocated VAR_DECL,
	   it means that it's going to be unified with whatever the
	   TARGET_EXPR is really supposed to initialize, so treat it
	   as being equivalent to anything.  */
	ਜੇ (VAR_P (o1) && DECL_NAME (o1) == NULL_ਰੁੱਖ
	    && !DECL_RTL_ਸੈੱਟ_P (o1))
	  /*Nop*/;
	ਨਹੀਂਤਾਂ ਜੇ (VAR_P (o2) && DECL_NAME (o2) == NULL_ਰੁੱਖ
		 && !DECL_RTL_ਸੈੱਟ_P (o2))
	  /*Nop*/;
	ਨਹੀਂਤਾਂ ਜੇ (!c_ਰੁੱਖ_equal (o1, o2))
	  ਵਾਪਸ ਝੂਠ;

	ਵਾਪਸ c_ਰੁੱਖ_equal (ਰੁੱਖ_ਸੰਕਾਰਜ (t1, 1), ਰੁੱਖ_ਸੰਕਾਰਜ (t2, 1));
      }

    ਹਾਲਤ COMPONENT_REF:
      ਜੇ (ਰੁੱਖ_ਸੰਕਾਰਜ (t1, 1) != ਰੁੱਖ_ਸੰਕਾਰਜ (t2, 1))
	ਵਾਪਸ ਝੂਠ;
      ਵਾਪਸ c_ਰੁੱਖ_equal (ਰੁੱਖ_ਸੰਕਾਰਜ (t1, 0), ਰੁੱਖ_ਸੰਕਾਰਜ (t2, 0));

    ਹਾਲਤ PARM_DECL:
    ਹਾਲਤ VAR_DECL:
    ਹਾਲਤ CONST_DECL:
    ਹਾਲਤ ਖੇਤਰ_DECL:
    ਹਾਲਤ FUNCTION_DECL:
    ਹਾਲਤ IDENTIFIER_ਗੰਢ:
    ਹਾਲਤ SSA_NAME:
      ਵਾਪਸ ਝੂਠ;

    ਹਾਲਤ ਰੁੱਖ_VEC:
      {
	ਬਿਨਾਨਿਸ਼ਾਨੀ ix;
	ਜੇ (ਰੁੱਖ_VEC_ਲੰਮਾਈ (t1) != ਰੁੱਖ_VEC_ਲੰਮਾਈ (t2))
	  ਵਾਪਸ ਝੂਠ;
	ਲਈ (ix = ਰੁੱਖ_VEC_ਲੰਮਾਈ (t1); ix--;)
	  ਜੇ (!c_ਰੁੱਖ_equal (ਰੁੱਖ_VEC_ELT (t1, ix),
			     ਰੁੱਖ_VEC_ELT (t2, ix)))
	    ਵਾਪਸ ਝੂਠ;
	ਵਾਪਸ ਸੱਚ;
      }

    CASE_CONVERT:
      ਜੇ (!comptypes (ਰੁੱਖ_TYPE (t1), ਰੁੱਖ_TYPE (t2)))
	ਵਾਪਸ ਝੂਠ;
      ਰੋਕੋ;

    ਮੂਲ:
      ਰੋਕੋ;
    }

  ਚੋਣ (ਰੁੱਖ_ਕੋਡ_CLASS (code1))
    {
    ਹਾਲਤ tcc_unary:
    ਹਾਲਤ tcc_ਦੁਆਧਾਰੀ:
    ਹਾਲਤ tcc_comparison:
    ਹਾਲਤ tcc_ਵਿਅੰਜਕ:
    ਹਾਲਤ tcc_vl_exp:
    ਹਾਲਤ tcc_reference:
    ਹਾਲਤ tcc_statement:
      {
	ਪੂਰਨ i, n = ਰੁੱਖ_ਸੰਕਾਰਜ_ਲੰਮਾਈ (t1);

	ਚੋਣ (code1)
	  {
	  ਹਾਲਤ PREINCREMENT_ਵਿਅੰਜਕ:
	  ਹਾਲਤ PREDECREMENT_ਵਿਅੰਜਕ:
	  ਹਾਲਤ POSTINCREMENT_ਵਿਅੰਜਕ:
	  ਹਾਲਤ POSTDECREMENT_ਵਿਅੰਜਕ:
	    n = 1;
	    ਰੋਕੋ;
	  ਹਾਲਤ ARRAY_REF:
	    n = 2;
	    ਰੋਕੋ;
	  ਮੂਲ:
	    ਰੋਕੋ;
	  }

	ਜੇ (ਰੁੱਖ_ਕੋਡ_CLASS (code1) == tcc_vl_exp
	    && n != ਰੁੱਖ_ਸੰਕਾਰਜ_ਲੰਮਾਈ (t2))
	  ਵਾਪਸ ਝੂਠ;

	ਲਈ (i = 0; i < n; ++i)
	  ਜੇ (!c_ਰੁੱਖ_equal (ਰੁੱਖ_ਸੰਕਾਰਜ (t1, i), ਰੁੱਖ_ਸੰਕਾਰਜ (t2, i)))
	    ਵਾਪਸ ਝੂਠ;

	ਵਾਪਸ ਸੱਚ;
      }

    ਹਾਲਤ tcc_type:
      ਵਾਪਸ comptypes (t1, t2);
    ਮੂਲ:
      gcc_unreachable ();
    }
}

/* Returns true when the function declaration FNDECL is implicit,
   introduced as a result of a call to an otherwise undeclared
   function, and false otherwise.  */

ਤਾਰਕਿਕ
c_decl_implicit (const_ਰੁੱਖ fndecl)
{
  ਵਾਪਸ C_DECL_IMPLICIT (fndecl);
}
