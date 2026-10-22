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

#ଅନ୍ତର୍ଭାଵ "config.h"
#ଅନ୍ତର୍ଭାଵ "system.h"
#ଅନ୍ତର୍ଭାଵ "coretypes.h"
#ଅନ୍ତର୍ଭାଵ "memmodel.h"
#ଅନ୍ତର୍ଭାଵ "target.h"
#ଅନ୍ତର୍ଭାଵ "function.h"
#ଅନ୍ତର୍ଭାଵ "bitmap.h"
#ଅନ୍ତର୍ଭାଵ "c-tree.h"
#ଅନ୍ତର୍ଭାଵ "gimple-expr.h"
#ଅନ୍ତର୍ଭାଵ "predict.h"
#ଅନ୍ତର୍ଭାଵ "stor-layout.h"
#ଅନ୍ତର୍ଭାଵ "trans-mem.h"
#ଅନ୍ତର୍ଭାଵ "varasm.h"
#ଅନ୍ତର୍ଭାଵ "stmt.h"
#ଅନ୍ତର୍ଭାଵ "langhooks.h"
#ଅନ୍ତର୍ଭାଵ "c-lang.h"
#ଅନ୍ତର୍ଭାଵ "intl.h"
#ଅନ୍ତର୍ଭାଵ "tree-iterator.h"
#ଅନ୍ତର୍ଭାଵ "gimplify.h"
#ଅନ୍ତର୍ଭାଵ "tree-inline.h"
#ଅନ୍ତର୍ଭାଵ "omp-general.h"
#ଅନ୍ତର୍ଭାଵ "c-family/c-objc.h"
#ଅନ୍ତର୍ଭାଵ "c-family/c-ubsan.h"
#ଅନ୍ତର୍ଭାଵ "gomp-constants.h"
#ଅନ୍ତର୍ଭାଵ "spellcheck-tree.h"
#ଅନ୍ତର୍ଭାଵ "c-family/c-type-mismatch.h"
#ଅନ୍ତର୍ଭାଵ "stringpool.h"
#ଅନ୍ତର୍ଭାଵ "attribs.h"
#ଅନ୍ତର୍ଭାଵ "asan.h"
#ଅନ୍ତର୍ଭାଵ "realmpfr.h"
#ଅନ୍ତର୍ଭାଵ "tree-pretty-print-markup.h"
#ଅନ୍ତର୍ଭାଵ "gcc-urlifier.h"

/* Possible cases of implicit conversions.  Used to select diagnostic messages
   and control folding initializers in convert_for_assignment.  */
ଗଣନା impl_conv {
  ic_argpass,
  ic_assign,
  ic_init,
  ic_init_const,
  ic_return
};

/* The level of nesting inside "__alignof__".  */
ପୂର୍ଣ୍ଣସଂଖ୍ୟା in_alignof;

/* The level of nesting inside "sizeof".  */
ପୂର୍ଣ୍ଣସଂଖ୍ୟା in_sizeof;

/* The level of nesting inside "countof".  */
ପୂର୍ଣ୍ଣସଂଖ୍ୟା in_countof;

/* The level of nesting inside "typeof".  */
ପୂର୍ଣ୍ଣସଂଖ୍ୟା in_typeof;

/* The level of nesting inside "_Generic".  */
ପୂର୍ଣ୍ଣସଂଖ୍ୟା in_generic;

/* True when parsing OpenMP loop expressions.  */
ତାର୍କିକ c_in_omp_for;

/* True when parsing OpenMP map clause.  */
ତାର୍କିକ c_omp_array_section_p;

/* The argument of last parsed sizeof expression, only to be tested
   if expr.original_code == SIZEOF_EXPR.  */
ବୃକ୍ଷ c_last_sizeof_arg;
location_t c_last_sizeof_loc;

/* Nonzero if we might need to print a "missing braces around
   initializer" message within this initializer.  */
ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା found_missing_braces;

ସ୍ଥିର ତାର୍କିକ require_constant_ମୂଲ୍ୟ;
ସ୍ଥିର ତାର୍କିକ require_constant_elements;
ସ୍ଥିର ତାର୍କିକ require_constexpr_ମୂଲ୍ୟ;

ସ୍ଥିର ବୃକ୍ଷ qualify_type (ବୃକ୍ଷ, ବୃକ୍ଷ);
ସଂରଚନା comptypes_data;
ସ୍ଥିର ତାର୍କିକ tagged_types_tu_compatible_p (const_ବୃକ୍ଷ, const_ବୃକ୍ଷ,
					  ସଂରଚନା comptypes_data *);
ସ୍ଥିର ତାର୍କିକ comp_target_types (location_t, ବୃକ୍ଷ, ବୃକ୍ଷ);
ସ୍ଥିର ତାର୍କିକ function_types_compatible_p (const_ବୃକ୍ଷ, const_ବୃକ୍ଷ,
					 ସଂରଚନା comptypes_data *);
ସ୍ଥିର ତାର୍କିକ type_lists_compatible_p (const_ବୃକ୍ଷ, const_ବୃକ୍ଷ,
				     ସଂରଚନା comptypes_data *);
ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା convert_arguments (location_t, vec<location_t>, ବୃକ୍ଷ,
			      vec<ବୃକ୍ଷ, va_gc> *, vec<ବୃକ୍ଷ, va_gc> *, ବୃକ୍ଷ,
			      ବୃକ୍ଷ);
ସ୍ଥିର ବୃକ୍ଷ pointer_diff (location_t, ବୃକ୍ଷ, ବୃକ୍ଷ, ବୃକ୍ଷ *);
ସ୍ଥିର ବୃକ୍ଷ convert_for_assignment (location_t, location_t, ବୃକ୍ଷ, ବୃକ୍ଷ, ବୃକ୍ଷ,
				    ଗଣନା impl_conv, ତାର୍କିକ, ବୃକ୍ଷ, ବୃକ୍ଷ, ପୂର୍ଣ୍ଣସଂଖ୍ୟା,
				    ପୂର୍ଣ୍ଣସଂଖ୍ୟା = 0);
ସ୍ଥିର ବୃକ୍ଷ valid_compound_ପଦସମଷ୍ଟି_initializer (ବୃକ୍ଷ, ବୃକ୍ଷ);
ସ୍ଥିର ଶୂନ୍ୟ ଠେଲ_string (ଅଚଳ ଅକ୍ଷର *);
ସ୍ଥିର ଶୂନ୍ୟ ଠେଲ_member_name (ବୃକ୍ଷ);
ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା spelling_length (ଶୂନ୍ୟ);
ସ୍ଥିର ଅକ୍ଷର *print_spelling (ଅକ୍ଷର *);
ସ୍ଥିର ଶୂନ୍ୟ warning_init (location_t, ପୂର୍ଣ୍ଣସଂଖ୍ୟା, ଅଚଳ ଅକ୍ଷର *);
ସ୍ଥିର ବୃକ୍ଷ digest_init (location_t, ବୃକ୍ଷ, ବୃକ୍ଷ, ବୃକ୍ଷ, ବୃକ୍ଷ, ତାର୍କିକ, ତାର୍କିକ, ତାର୍କିକ,
			 ତାର୍କିକ, ତାର୍କିକ, ତାର୍କିକ);
ସ୍ଥିର ଶୂନ୍ୟ output_init_element (location_t, ବୃକ୍ଷ, ବୃକ୍ଷ, ତାର୍କିକ, ବୃକ୍ଷ, ବୃକ୍ଷ, ତାର୍କିକ,
				 ତାର୍କିକ, ସଂରଚନା obstack *);
ସ୍ଥିର ଶୂନ୍ୟ output_pending_init_elements (ପୂର୍ଣ୍ଣସଂଖ୍ୟା, ସଂରଚନା obstack *);
ସ୍ଥିର ତାର୍କିକ set_designator (location_t, ତାର୍କିକ, ସଂରଚନା obstack *);
ସ୍ଥିର ଶୂନ୍ୟ ଠେଲ_range_ଗଦା (ବୃକ୍ଷ, ସଂରଚନା obstack *);
ସ୍ଥିର ଶୂନ୍ୟ add_pending_init (location_t, ବୃକ୍ଷ, ବୃକ୍ଷ, ବୃକ୍ଷ, ତାର୍କିକ,
			      ସଂରଚନା obstack *);
ସ୍ଥିର ଶୂନ୍ୟ set_nonincremental_init (ସଂରଚନା obstack *);
ସ୍ଥିର ଶୂନ୍ୟ set_nonincremental_init_from_string (ବୃକ୍ଷ, ସଂରଚନା obstack *);
ସ୍ଥିର ବୃକ୍ଷ find_init_member (ବୃକ୍ଷ, ସଂରଚନା obstack *);
ସ୍ଥିର ଶୂନ୍ୟ readonly_warning (ବୃକ୍ଷ, ଗଣନା lvalue_use);
ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା lvalue_or_else (location_t, const_ବୃକ୍ଷ, ଗଣନା lvalue_use);
ସ୍ଥିର ଶୂନ୍ୟ record_maybe_used_decl (ବୃକ୍ଷ, ତାର୍କିକ address);
ସ୍ଥିର ତାର୍କିକ comptypes_internal (const_ବୃକ୍ଷ, const_ବୃକ୍ଷ,
				ସଂରଚନା comptypes_data *data);
ସ୍ଥିର ତାର୍କିକ comptypes_check_for_composite (ବୃକ୍ଷ t1, ବୃକ୍ଷ t2);
ସ୍ଥିର ତାର୍କିକ handle_counted_by_p (ବୃକ୍ଷ);
ସ୍ଥିର ତାର୍କିକ ଶୀର୍ଷ_array_vla_p (const_ବୃକ୍ଷ type);


/* Return true if EXP is a null pointer constant, false otherwise.  */

ତାର୍କିକ
null_pointer_constant_p (const_ବୃକ୍ଷ ପଦସମଷ୍ଟି)
{
  /* This should really operate on c_expr structures, but they aren't
     yet available everywhere required.  */
  ବୃକ୍ଷ type = ବୃକ୍ଷ_TYPE (ପଦସମଷ୍ଟି);

  /* An integer constant expression with the value 0, such an expression
     cast to type void*, or the predefined constant nullptr, are a null
     pointer constant.  */
  ଯଦି (ପଦସମଷ୍ଟି == nullptr_ଗଣ୍ଠି)
    ଫେରନ୍ତୁ ସତ୍ୟ;

  ଫେରନ୍ତୁ (ବୃକ୍ଷ_CODE (ପଦସମଷ୍ଟି) == INTEGER_CST
	  && !ବୃକ୍ଷ_OVERFLOW (ପଦସମଷ୍ଟି)
	  && integer_zerop (ପଦସମଷ୍ଟି)
	  && (INTEGRAL_TYPE_P (type)
	      || (ବୃକ୍ଷ_CODE (type) == POINTER_TYPE
		  && VOID_TYPE_P (ବୃକ୍ଷ_TYPE (type))
		  && TYPE_QUALS (ବୃକ୍ଷ_TYPE (type)) == TYPE_UNQUALIFIED)));
}

/* EXPR may appear in an unevaluated part of an integer constant
   expression, but not in an evaluated part.  Wrap it in a
   C_MAYBE_CONST_EXPR, or mark it with TREE_OVERFLOW if it is just an
   INTEGER_CST and we cannot create a C_MAYBE_CONST_EXPR.  */

ସ୍ଥିର ବୃକ୍ଷ
note_integer_operands (ବୃକ୍ଷ ପଦସମଷ୍ଟି)
{
  ବୃକ୍ଷ ret;
  ଯଦି (ବୃକ୍ଷ_CODE (ପଦସମଷ୍ଟି) == INTEGER_CST && in_late_ଦ୍ୱିମିକ_op)
    {
      ret = copy_ଗଣ୍ଠି (ପଦସମଷ୍ଟି);
      ବୃକ୍ଷ_OVERFLOW (ret) = 1;
    }
  ଅନ୍ୟଥା
    {
      ret = build2 (C_MAYBE_CONST_ପଦସମଷ୍ଟି, ବୃକ୍ଷ_TYPE (ପଦସମଷ୍ଟି), NULL_ବୃକ୍ଷ, ପଦସମଷ୍ଟି);
      C_MAYBE_CONST_ପଦସମଷ୍ଟି_INT_OPERANDS (ret) = 1;
    }
  ଫେରନ୍ତୁ ret;
}

/* Having checked whether EXPR may appear in an unevaluated part of an
   integer constant expression and found that it may, remove any
   C_MAYBE_CONST_EXPR noting this fact and return the resulting
   expression.  */

ସ୍ଥିର ଧାଡ଼ିଭିତରେ ବୃକ୍ଷ
remove_c_maybe_const_ପଦସମଷ୍ଟି (ବୃକ୍ଷ ପଦସମଷ୍ଟି)
{
  ଯଦି (ବୃକ୍ଷ_CODE (ପଦସମଷ୍ଟି) == C_MAYBE_CONST_ପଦସମଷ୍ଟି)
    ଫେରନ୍ତୁ C_MAYBE_CONST_ପଦସମଷ୍ଟି_ପଦସମଷ୍ଟି (ପଦସମଷ୍ଟି);
  ଅନ୍ୟଥା
    ଫେରନ୍ତୁ ପଦସମଷ୍ଟି;
}

/* This is a cache to hold if two types are seen.  */

ସଂରଚନା tagged_tu_seen_cache {
  ଅଚଳ ସଂରଚନା tagged_tu_seen_cache * next;
  const_ବୃକ୍ଷ t1;
  const_ବୃକ୍ଷ t2;
};

/* Do `exp = require_complete_type (loc, exp);' to make sure exp
   does not have an incomplete type.  (That includes void types.)
   LOC is the location of the use.  */

ବୃକ୍ଷ
require_complete_type (location_t loc, ବୃକ୍ଷ ମୂଲ୍ୟ)
{
  ବୃକ୍ଷ type = ବୃକ୍ଷ_TYPE (ମୂଲ୍ୟ);

  ଯଦି (error_operand_p (ମୂଲ୍ୟ))
    ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;

  /* First, detect a valid value with a complete type.  */
  ଯଦି (COMPLETE_TYPE_P (type))
    ଫେରନ୍ତୁ ମୂଲ୍ୟ;

  c_incomplete_type_error (loc, ମୂଲ୍ୟ, type);
  ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
}

/* Print an error message for invalid use of an incomplete type.
   VALUE is the expression that was used (or 0 if that isn't known)
   and TYPE is the type that was invalid.  LOC is the location for
   the error.  */

ଶୂନ୍ୟ
c_incomplete_type_error (location_t loc, const_ବୃକ୍ଷ ମୂଲ୍ୟ, const_ବୃକ୍ଷ type)
{
  /* Avoid duplicate error message.  */
  ଯଦି (ବୃକ୍ଷ_CODE (type) == ERROR_MARK)
    ଫେରନ୍ତୁ;

  ଯଦି (ମୂଲ୍ୟ != NULL_ବୃକ୍ଷ && (VAR_P (ମୂଲ୍ୟ) || ବୃକ୍ଷ_CODE (ମୂଲ୍ୟ) == PARM_DECL))
    error_at (loc, "%qD has an incomplete type %qT", ମୂଲ୍ୟ, type);
  ଅନ୍ୟଥା
    {
    retry:
      /* We must print an error message.  Be clever about what it says.  */

      ବାଛ (ବୃକ୍ଷ_CODE (type))
	{
	ସ୍ଥିତି RECORD_TYPE:
	ସ୍ଥିତି UNION_TYPE:
	ସ୍ଥିତି ENUMERAL_TYPE:
	  ଭାଙ୍ଗ;

	ସ୍ଥିତି VOID_TYPE:
	  error_at (loc, "invalid use of void expression");
	  ଫେରନ୍ତୁ;

	ସ୍ଥିତି ARRAY_TYPE:
	  ଯଦି (TYPE_DOMAIN (type))
	    {
	      ଯଦି (flexible_array_member_type_p (type))
		{
		  error_at (loc, "invalid use of flexible array member");
		  ଫେରନ୍ତୁ;
		}
	      type = ବୃକ୍ଷ_TYPE (type);
	      ଯାଅ retry;
	    }
	  error_at (loc, "invalid use of array with unspecified bounds");
	  ଫେରନ୍ତୁ;

	ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
	  gcc_unreachable ();
	}

      ଯଦି (ବୃକ୍ଷ_CODE (TYPE_NAME (type)) == IDENTIFIER_ଗଣ୍ଠି)
	error_at (loc, "invalid use of undefined type %qT", type);
      ଅନ୍ୟଥା
	/* If this type has a typedef-name, the TYPE_NAME is a TYPE_DECL.  */
	error_at (loc, "invalid use of incomplete typedef %qT", type);
    }
}

/* Given a type, apply default promotions wrt unnamed function
   arguments and return the new type.  */

ବୃକ୍ଷ
c_type_promotes_to (ବୃକ୍ଷ type)
{
  ବୃକ୍ଷ ret = NULL_ବୃକ୍ଷ;

  ଯଦି (TYPE_MAIN_VARIANT (type) == float_type_ଗଣ୍ଠି)
    ret = double_type_ଗଣ୍ଠି;
  ଅନ୍ୟଥା ଯଦି (c_promoting_integer_type_p (type))
    {
      /* Preserve unsignedness if not really getting any wider.  */
      ଯଦି (TYPE_UNSIGNED (type)
	  && (TYPE_PRECISION (type) == TYPE_PRECISION (integer_type_ଗଣ୍ଠି)))
	ret = unsigned_type_ଗଣ୍ଠି;
      ଅନ୍ୟଥା
	ret = integer_type_ଗଣ୍ଠି;
    }

  ଯଦି (ret != NULL_ବୃକ୍ଷ)
    ଫେରନ୍ତୁ (TYPE_ATOMIC (type)
	    ? c_build_qualified_type (ret, TYPE_QUAL_ATOMIC)
	    : ret);

  ଫେରନ୍ତୁ type;
}

/* Return true if between two named address spaces, whether there is a superset
   named address space that encompasses both address spaces.  If there is a
   superset, return which address space is the superset.  */

ସ୍ଥିର ତାର୍କିକ
addr_space_superset (addr_space_t as1, addr_space_t as2, addr_space_t *common)
{
  ଯଦି (as1 == as2)
    {
      *common = as1;
      ଫେରନ୍ତୁ ସତ୍ୟ;
    }
  ଅନ୍ୟଥା ଯଦି (targetm.addr_space.subset_p (as1, as2))
    {
      *common = as2;
      ଫେରନ୍ତୁ ସତ୍ୟ;
    }
  ଅନ୍ୟଥା ଯଦି (targetm.addr_space.subset_p (as2, as1))
    {
      *common = as1;
      ଫେରନ୍ତୁ ସତ୍ୟ;
    }
  ଅନ୍ୟଥା
    ଫେରନ୍ତୁ ମିଥ୍ୟା;
}

/* Return a variant of TYPE which has all the type qualifiers of LIKE
   as well as those of TYPE.  */

ସ୍ଥିର ବୃକ୍ଷ
qualify_type (ବୃକ୍ଷ type, ବୃକ୍ଷ like)
{
  addr_space_t as_type = TYPE_ADDR_SPACE (type);
  addr_space_t as_like = TYPE_ADDR_SPACE (like);
  addr_space_t as_common;

  /* If the two named address spaces are different, determine the common
     superset address space.  If there isn't one, raise an error.  */
  ଯଦି (!addr_space_superset (as_type, as_like, &as_common))
    {
      as_common = as_type;
      error ("%qT and %qT are in disjoint named address spaces",
	     type, like);
    }

  ଫେରନ୍ତୁ c_build_qualified_type (type,
				 TYPE_QUALS_NO_ADDR_SPACE (type)
				 | TYPE_QUALS_NO_ADDR_SPACE_NO_ATOMIC (like)
				 | ENCODE_QUAL_ADDR_SPACE (as_common));
}


/* Check consistency of type TYPE.  For derived types, we test that
   C_TYPE_VARIABLE_SIZE and C_TYPE_VARIABLY_MODIFIED are consistent with
   the requirements of the base type.  We also check that arrays with a
   non-constant length are marked with C_TYPE_VARIABLE_SIZE. If any
   inconsistency is detected false is returned and true otherwise.  */

ସ୍ଥିର ତାର୍କିକ
c_verify_type (ବୃକ୍ଷ type)
{
  ବାଛ (ବୃକ୍ଷ_CODE (type))
    {
    ସ୍ଥିତି POINTER_TYPE:
    ସ୍ଥିତି FUNCTION_TYPE:
    ସ୍ଥିତି ARRAY_TYPE:
      /* Pointer, array, functions are variably modified if and only if the
	 target, element, return type is variably modified.  */
      ଯଦି (!TYPE_STRUCTURAL_EQUALITY_P (type)
	  && (C_TYPE_VARIABLY_MODIFIED (type)
	      != C_TYPE_VARIABLY_MODIFIED (ବୃକ୍ଷ_TYPE (type))))
	ଫେରନ୍ତୁ ମିଥ୍ୟା;
      /* If the target type is structural equality, the type should also. */
      ଯଦି (!TYPE_STRUCTURAL_EQUALITY_P (type)
	  && TYPE_STRUCTURAL_EQUALITY_P (ବୃକ୍ଷ_TYPE (type)))
	ଫେରନ୍ତୁ ମିଥ୍ୟା;
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
       ଭାଙ୍ଗ;
    }

  ବାଛ (ବୃକ୍ଷ_CODE (type))
    {
    ସ୍ଥିତି POINTER_TYPE:
    ସ୍ଥିତି FUNCTION_TYPE:
      /* Pointer and functions can not have variable size.  */
      ଯଦି (C_TYPE_VARIABLE_SIZE (type))
	ଫେରନ୍ତୁ ମିଥ୍ୟା;
      ଭାଙ୍ଗ;
    ସ୍ଥିତି ARRAY_TYPE:
      /* An array has variable size if and only if it has a non-constant
	 dimensions or its element type has variable size.  */
      ଯଦି ((C_TYPE_VARIABLE_SIZE (ବୃକ୍ଷ_TYPE (type))
	   || ଶୀର୍ଷ_array_vla_p (type))
	  != C_TYPE_VARIABLE_SIZE (type))
	ଫେରନ୍ତୁ ମିଥ୍ୟା;
      /* If the element type or the array has variable size, then the
	 array has variable size and is variably modified.  */
      ଯଦି (C_TYPE_VARIABLE_SIZE (ବୃକ୍ଷ_TYPE (type))
	  || C_TYPE_VARIABLE_SIZE (type))
	{
	  ଯଦି (!C_TYPE_VARIABLE_SIZE (type))
	    ଫେରନ୍ତୁ ମିଥ୍ୟା;
	  ଯଦି (!C_TYPE_VARIABLY_MODIFIED (type))
	    ଫେରନ୍ତୁ ମିଥ୍ୟା;
	}

      /* va_list violates this, accept such types here.  */
      ଯଦି (!COMPLETE_TYPE_P (ବୃକ୍ଷ_TYPE (type)))
	ଫେରନ୍ତୁ ସତ୍ୟ;

      ଯଦି (COMPLETE_TYPE_P (type))
	{
	  /* If the size is unknown, it can not be complete.  */
	  ଯଦି (NULL_ବୃକ୍ଷ == TYPE_DOMAIN (type))
	    ଫେରନ୍ତୁ ମିଥ୍ୟା;

	  /* Zero-length arrays must have size zero.  */
	  ଯଦି (zero_length_array_type_p (type)
	      && !integer_zerop (TYPE_SIZE (type)))
	    ଫେରନ୍ତୁ ମିଥ୍ୟା;
	}
      ଅନ୍ୟଥା
	{
	  /* If not complete but has a domain, it must be a FAM.  */
	  ଯଦି (NULL_ବୃକ୍ଷ != TYPE_DOMAIN (type)
	      && !flexible_array_member_type_p (type))
	    ଫେରନ୍ତୁ ମିଥ୍ୟା;
	}
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
      ଭାଙ୍ଗ;
    }
  ଫେରନ୍ତୁ ସତ୍ୟ;
}

/* Propagate C_TYPE_VARIABLY_MODIFIED and C_TYPE_VARIABLE_SIZE
   from a base type to a newly built derived or qualified type.  */

ସ୍ଥିର ବୃକ୍ଷ
c_set_type_bits (ବୃକ୍ଷ new_type, ବୃକ୍ଷ old_type)
{
  gcc_checking_assert (c_verify_type (old_type));

  ଯଦି (c_type_variably_modified_p (old_type))
    C_TYPE_VARIABLY_MODIFIED (new_type) = ସତ୍ୟ;

  ଯଦି (ବୃକ୍ଷ_CODE (new_type) == ARRAY_TYPE && C_TYPE_VARIABLE_SIZE (old_type))
    {
      C_TYPE_VARIABLY_MODIFIED (new_type) = ସତ୍ୟ;
      C_TYPE_VARIABLE_SIZE (new_type) = ସତ୍ୟ;
    }
  ଫେରନ୍ତୁ new_type;
}

/* Build a pointer type using the default pointer mode.  */

ବୃକ୍ଷ
c_build_pointer_type (ବୃକ୍ଷ to_type)
{
  addr_space_t as = to_type == error_mark_ଗଣ୍ଠି ? ADDR_SPACE_GENERIC
					       : TYPE_ADDR_SPACE (to_type);
  machine_mode pointer_mode;

  ଯଦି (as != ADDR_SPACE_GENERIC || c_default_pointer_mode == VOIDmode)
    pointer_mode = targetm.addr_space.pointer_mode (as);
  ଅନ୍ୟଥା
    pointer_mode = c_default_pointer_mode;

  ଫେରନ୍ତୁ c_build_pointer_type_for_mode (to_type, pointer_mode, ମିଥ୍ୟା);
}

/* Build a pointer type using the given mode.  */

ବୃକ୍ଷ
c_build_pointer_type_for_mode (ବୃକ୍ଷ type, machine_mode mode, ତାର୍କିକ m)
{
  ବୃକ୍ଷ ret = build_pointer_type_for_mode (type, mode, m);
  ଫେରନ୍ତୁ c_set_type_bits (ret, type);
}

/* Build a function type.  */

ବୃକ୍ଷ
c_build_function_type (ବୃକ୍ଷ type, ବୃକ୍ଷ args, ତାର୍କିକ no)
{
  ବୃକ୍ଷ ret = build_function_type (type, args, no);
  ଫେରନ୍ତୁ c_set_type_bits (ret, type);
}

/* Build an array type.  This sets typeless storage as required
   by C2Y and C_TYPE_VARIABLY_MODIFIED and C_TYPE_VARIABLE_SIZE
   based on the element type and domain.  */

ବୃକ୍ଷ
c_build_array_type (ବୃକ୍ଷ type, ବୃକ୍ଷ domain)
{
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା type_quals = TYPE_QUALS (type);

  /* Identify typeless storage as introduced in C2Y
     and supported also in earlier language modes.  */
  ତାର୍କିକ typeless = (char_type_p (type) && !(type_quals & TYPE_QUAL_ATOMIC))
		  || (AGGREGATE_TYPE_P (type) && TYPE_TYPELESS_STORAGE (type));

  ବୃକ୍ଷ ret = build_array_type (type, domain, typeless);

  ଯଦି (ଶୀର୍ଷ_array_vla_p (ret))
    {
      C_TYPE_VARIABLE_SIZE (ret) = 1;
      C_TYPE_VARIABLY_MODIFIED (ret) = 1;
    }

  ଫେରନ୍ତୁ c_set_type_bits (ret, type);
}

/* Build an array type of unspecified size.  */
ବୃକ୍ଷ
c_build_array_type_unspecified (ବୃକ୍ଷ type)
{
  ବୃକ୍ଷ upper = build2 (COMPOUND_ପଦସମଷ୍ଟି, ବୃକ୍ଷ_TYPE (size_zero_ଗଣ୍ଠି),
		       integer_zero_ଗଣ୍ଠି, size_zero_ଗଣ୍ଠି);
  ଫେରନ୍ତୁ c_build_array_type (type, build_index_type (upper));
}

/* Build an array type of zero size.  */
ବୃକ୍ଷ
c_build_array_type_zero_size (ବୃକ୍ଷ type)
{
  /* The GCC extension for zero-length arrays differs from
     ISO flexible array members in that sizeof yields
     zero.  */
  type = c_build_array_type (type, build_index_type (NULL_ବୃକ୍ଷ));
  type = build_distinct_type_copy (TYPE_MAIN_VARIANT (type));
  TYPE_SIZE (type) = bitsize_zero_ଗଣ୍ଠି;
  TYPE_SIZE_UNIT (type) = size_zero_ଗଣ୍ଠି;
  SET_TYPE_STRUCTURAL_EQUALITY (type);
  ଫେରନ୍ତୁ type;
}

ବୃକ୍ଷ
c_build_type_attribute_qual_variant (ବୃକ୍ଷ type, ବୃକ୍ଷ attrs, ପୂର୍ଣ୍ଣସଂଖ୍ୟା quals)
{
  ବୃକ୍ଷ ret = build_type_attribute_qual_variant (type, attrs, quals);
  ଫେରନ୍ତୁ c_set_type_bits (ret, type);
}

ବୃକ୍ଷ
c_build_type_attribute_variant (ବୃକ୍ଷ type, ବୃକ୍ଷ attrs)
{
  ଫେରନ୍ତୁ c_build_type_attribute_qual_variant (type, attrs, TYPE_QUALS (type));
}

/* Reconstruct a complex derived type.  This is used to re-construct types
   with the vector attribute.  It is called via a langhook.  */

ବୃକ୍ଷ
c_reconstruct_complex_type (ବୃକ୍ଷ type, ବୃକ୍ଷ bottom)
{
  ବୃକ୍ଷ inner, outer;

  ଯଦି (ବୃକ୍ଷ_CODE (type) == POINTER_TYPE)
    {
      inner = c_reconstruct_complex_type (ବୃକ୍ଷ_TYPE (type), bottom);
      outer = c_build_pointer_type_for_mode (inner, TYPE_MODE (type),
					     TYPE_REF_CAN_ALIAS_ALL (type));
    }
  ଅନ୍ୟଥା ଯଦି (ବୃକ୍ଷ_CODE (type) == ARRAY_TYPE)
    {
      ତାର୍କିକ rso = TYPE_REVERSE_STORAGE_ORDER (type);
      inner = c_reconstruct_complex_type (ବୃକ୍ଷ_TYPE (type), bottom);
      outer = c_build_array_type (inner, TYPE_DOMAIN (type));
      ଯଦି (rso)
	{
	  outer = build_distinct_type_copy (outer);
	  TYPE_REVERSE_STORAGE_ORDER (outer) = 1;
	}

      gcc_checking_assert (C_TYPE_VARIABLE_SIZE (type)
			   == C_TYPE_VARIABLE_SIZE (outer));
    }
  ଅନ୍ୟଥା ଯଦି (ବୃକ୍ଷ_CODE (type) == FUNCTION_TYPE)
    {
      inner = c_reconstruct_complex_type (ବୃକ୍ଷ_TYPE (type), bottom);
      outer = c_build_function_type (inner, TYPE_ARG_TYPES (type),
				     TYPE_NO_NAMED_ARGS_STDARG_P (type));
    }
  ଅନ୍ୟଥା ଯଦି (ବୃକ୍ଷ_CODE (type) == REFERENCE_TYPE
	   || ବୃକ୍ଷ_CODE (type) == OFFSET_TYPE)
    gcc_unreachable ();
  ଅନ୍ୟଥା
    ଫେରନ୍ତୁ bottom;

  ଫେରନ୍ତୁ c_build_type_attribute_qual_variant (outer, TYPE_ATTRIBUTES (type),
					      TYPE_QUALS (type));
}


/* Helper function for c_canonical_type.  Check whether FIELD
   contains a pointer to a structure or union with tag,
   possibly nested in other type derivations, and return the
   type of this nested structure or union.  */
ସ୍ଥିର ବୃକ୍ଷ
ptr_to_tagged_member (ବୃକ୍ଷ field)
{
  gcc_assert (FIELD_DECL == ବୃକ୍ଷ_CODE (field));
  ବୃକ୍ଷ type = ବୃକ୍ଷ_TYPE (field);
  ତାର୍କିକ ptr_seen = ମିଥ୍ୟା;
  ଯେତେବେଳେ (ବୃକ୍ଷ_CODE (type) == ARRAY_TYPE
	 || ବୃକ୍ଷ_CODE (type) == FUNCTION_TYPE
	 || ବୃକ୍ଷ_CODE (type) == POINTER_TYPE)
    {
      ଯଦି (ବୃକ୍ଷ_CODE (type) == POINTER_TYPE)
	ptr_seen = ସତ୍ୟ;
      type = ବୃକ୍ଷ_TYPE (type);
    }

  ଯଦି (ptr_seen
      && RECORD_OR_UNION_TYPE_P (type)
      && NULL_ବୃକ୍ଷ != c_type_tag (type))
    ଫେରନ୍ତୁ type;

  ଫେରନ୍ତୁ NULL_ବୃକ୍ଷ;
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
ବୃକ୍ଷ
c_type_canonical (ବୃକ୍ଷ type)
{
  gcc_assert (RECORD_OR_UNION_TYPE_P (type));

  ତାର୍କିକ needs_mod = ମିଥ୍ୟା;
  ପାଇଁ (ବୃକ୍ଷ x = TYPE_FIELDS (type); x; x = DECL_CHAIN (x))
    {
      ଯଦି (!ptr_to_tagged_member (x))
	ଜାରି;
      needs_mod = ସତ୍ୟ;
      ଭାଙ୍ଗ;
    }
  ଯଦି (!needs_mod)
    ଫେରନ୍ତୁ type;

  /* Construct new version with such members replaced.  */
  ବୃକ୍ଷ n = build_distinct_type_copy (type);
  ବୃକ୍ଷ *fields = &TYPE_FIELDS (n);
  ପାଇଁ (ବୃକ୍ଷ x = TYPE_FIELDS (type); x; x = DECL_CHAIN (x))
    {
      ବୃକ୍ଷ f = copy_ଗଣ୍ଠି (x);
      ଯଦି (ବୃକ୍ଷ m = ptr_to_tagged_member (x))
	{
	  ବୃକ୍ଷ new_ଗଣ୍ଠି = make_ଗଣ୍ଠି (ବୃକ୍ଷ_CODE (m));
	  TYPE_NAME (new_ଗଣ୍ଠି) = TYPE_NAME (m);
	  SET_TYPE_STRUCTURAL_EQUALITY (new_ଗଣ୍ଠି);
	  new_ଗଣ୍ଠି = qualify_type (new_ଗଣ୍ଠି, m);
	  ବୃକ୍ଷ_TYPE (f) = c_reconstruct_complex_type (ବୃକ୍ଷ_TYPE (x),
						      new_ଗଣ୍ଠି);
	}
      *fields = f;
      fields = &DECL_CHAIN (f);
    }
  TYPE_CANONICAL (n) = n;
  ଫେରନ୍ତୁ n;
}


/* If NTYPE is a type of a non-variadic function with a prototype
   and OTYPE is a type of a function without a prototype and ATTRS
   contains attribute format, diagnosess and removes it from ATTRS.
   Returns the result of build_type_attribute_variant of NTYPE and
   the (possibly) modified ATTRS.  */

ସ୍ଥିର ବୃକ୍ଷ
c_build_functype_attribute_variant (ବୃକ୍ଷ ntype, ବୃକ୍ଷ otype, ବୃକ୍ଷ attrs)
{
  ଯଦି (!prototype_p (otype)
      && prototype_p (ntype)
      && lookup_attribute ("format", attrs))
    {
      warning_at (ନିବେଶ_location, OPT_Wattributes,
		  "%qs attribute can only be applied to variadic functions",
		  "format");
      attrs = remove_attribute ("format", attrs);
    }
  ଫେରନ୍ତୁ c_build_type_attribute_variant (ntype, attrs);

}

/* Given a type which could be a typedef name, make sure to return the
   original type.  See set_underlying_type. */
ସ୍ଥିର const_ବୃକ୍ଷ
c_type_original (const_ବୃକ୍ଷ t)
{
  /* It may even be a typedef of a typedef...
     In the case of compiler-created builtin structs the TYPE_DECL
     may be a dummy, with no DECL_ORIGINAL_TYPE.  Don't fault.  */
  ଯେତେବେଳେ (TYPE_NAME (t)
	 && ବୃକ୍ଷ_CODE (TYPE_NAME (t)) == TYPE_DECL
	 && DECL_ORIGINAL_TYPE (TYPE_NAME (t)))
    t = DECL_ORIGINAL_TYPE (TYPE_NAME (t));
  ଫେରନ୍ତୁ t;
}

/* Return the tag for a tagged type.  */
ବୃକ୍ଷ
c_type_tag (const_ବୃକ୍ଷ t)
{
  gcc_assert (RECORD_OR_UNION_TYPE_P (t) || ବୃକ୍ଷ_CODE (t) == ENUMERAL_TYPE);
  const_ବୃକ୍ଷ orig = c_type_original (t);
  ବୃକ୍ଷ name = TYPE_NAME (orig);
  ଯଦି (!name)
    ଫେରନ୍ତୁ NULL_ବୃକ୍ଷ;
  ଯଦି (ବୃକ୍ଷ_CODE (name) == TYPE_DECL)
    {
      ଯଦି (!DECL_NAME (name))
	ଫେରନ୍ତୁ NULL_ବୃକ୍ଷ;
      name = DECL_NAME (name);
    }
  gcc_checking_assert (ବୃକ୍ଷ_CODE (name) == IDENTIFIER_ଗଣ୍ଠି);
  ଫେରନ୍ତୁ name;
}

/* Remove qualifiers but not atomic.  For arrays remove qualifiers
   on the element type but also do not remove atomic.  */
ସ୍ଥିର ବୃକ୍ଷ
remove_qualifiers (ବୃକ୍ଷ t)
{
  ଯଦି (!t || t == error_mark_ଗଣ୍ଠି)
    ଫେରନ୍ତୁ t;
  ଫେରନ୍ତୁ TYPE_ATOMIC (strip_array_types (t))
	 ? c_build_qualified_type (TYPE_MAIN_VARIANT (t), TYPE_QUAL_ATOMIC)
	 : TYPE_MAIN_VARIANT (t);
}


/* Helper function for composite_type_internal.  Find a compatible type
   in a (transparent) union U compatible to T.  If found, return the
   type of the corresponding member.  Otherwise, return the union type U.  */
ସ୍ଥିର ବୃକ୍ଷ
transparent_union_replacement (ବୃକ୍ଷ u, ବୃକ୍ଷ t)
{
  ଯଦି (u == error_mark_ଗଣ୍ଠି || t == error_mark_ଗଣ୍ଠି
      || ବୃକ୍ଷ_CODE (u) != UNION_TYPE
      || !(TYPE_TRANSPARENT_AGGR (u) || TYPE_NAME (u) == NULL_ବୃକ୍ଷ)
      || comptypes (u, t))
    ଫେରନ୍ତୁ u;

  ପାଇଁ (ବୃକ୍ଷ memb = TYPE_FIELDS (u); memb; memb = DECL_CHAIN (memb))
    {
      ବୃକ୍ଷ m = remove_qualifiers (ବୃକ୍ଷ_TYPE (memb));
      ଯଦି (comptypes (m, t))
	{
	  pedwarn (ନିବେଶ_location, OPT_Wpedantic,
		    "function types not truly compatible in ISO C");
	  ଫେରନ୍ତୁ m;
	}
    }

  ଫେରନ୍ତୁ u;
}



/* Return the composite type of two compatible types.

   We assume that comptypes has already been done and returned
   nonzero; if that isn't so, this may crash.  In particular, we
   assume that qualifiers match.  */

ସଂରଚନା composite_cache {
  ବୃକ୍ଷ t1;
  ବୃକ୍ଷ t2;
  ବୃକ୍ଷ composite;
  ସଂରଚନା composite_cache* next;
};

ବୃକ୍ଷ
composite_type_internal (ବୃକ୍ଷ t1, ବୃକ୍ଷ t2, ବୃକ୍ଷ cond,
			 ସଂରଚନା composite_cache* cache)
{
  ଗଣନା ବୃକ୍ଷ_code code1;
  ଗଣନା ବୃକ୍ଷ_code code2;
  ବୃକ୍ଷ attributes;

  /* Save time if the two types are the same.  */

  ଯଦି (t1 == t2) ଫେରନ୍ତୁ t1;

  /* If one type is nonsense, use the other.  */
  ଯଦି (t1 == error_mark_ଗଣ୍ଠି)
    ଫେରନ୍ତୁ t2;
  ଯଦି (t2 == error_mark_ଗଣ୍ଠି)
    ଫେରନ୍ତୁ t1;

  code1 = ବୃକ୍ଷ_CODE (t1);
  code2 = ବୃକ୍ଷ_CODE (t2);

  /* Merge the attributes.  */
  attributes = targetm.merge_type_attributes (t1, t2);

  /* If one is an enumerated type and the other is the compatible
     integer type, the composite type might be either of the two
     (DR#013 question 3).  For consistency, use the enumerated type as
     the composite type.  */

  ଯଦି (code1 == ENUMERAL_TYPE
      && (code2 == INTEGER_TYPE
	  || code2 == BOOLEAN_TYPE))
    ଫେରନ୍ତୁ t1;
  ଯଦି (code2 == ENUMERAL_TYPE
      && (code1 == INTEGER_TYPE
	  || code1 == BOOLEAN_TYPE))
    ଫେରନ୍ତୁ t2;

  gcc_assert (code1 == code2);

  ବାଛ (code1)
    {
    ସ୍ଥିତି POINTER_TYPE:
      /* For two pointers, do this recursively on the target type.  */
      {
	gcc_checking_assert (TYPE_QUALS (t1) == TYPE_QUALS (t2));
	ବୃକ୍ଷ target = composite_type_internal (ବୃକ୍ଷ_TYPE (t1), ବୃକ୍ଷ_TYPE (t2),
					       cond, cache);
	ବୃକ୍ଷ n = c_build_pointer_type_for_mode (target, TYPE_MODE (t1), ମିଥ୍ୟା);
	ଫେରନ୍ତୁ c_build_type_attribute_qual_variant (n, attributes,
						    TYPE_QUALS (t2));
      }

    ସ୍ଥିତି ARRAY_TYPE:
      {
	ବୃକ୍ଷ d1 = TYPE_DOMAIN (t1);
	ବୃକ୍ଷ d2 = TYPE_DOMAIN (t2);

	/* We should not have any type quals on arrays at all.  */
	gcc_assert (!TYPE_QUALS_NO_ADDR_SPACE (t1)
		    && !TYPE_QUALS_NO_ADDR_SPACE (t2));

	ତାର୍କିକ d1_zero = zero_length_array_type_p (t1)
		       || flexible_array_member_type_p (t1);
	ତାର୍କିକ d2_zero = zero_length_array_type_p (t2)
		       || flexible_array_member_type_p (t2);

	ତାର୍କିକ d1_variable = ଶୀର୍ଷ_array_vla_p (t1);
	ତାର୍କିକ d2_variable = ଶୀର୍ଷ_array_vla_p (t2);

	ତାର୍କିକ use1 = d1 && (d2_variable || !d2 || d2_zero || !d1_variable);
	ତାର୍କିକ use2 = d2 && (d1_variable || !d1 || d1_zero || !d2_variable);

	/* If the first is an unspecified size pick the other one.  */
	ଯଦି (d2_variable && c_type_unspecified_p (t1))
	  {
	    gcc_assert (use1 && use2);
	    use1 = ମିଥ୍ୟା;
	  }

	/* If both are VLAs but not unspecified and we are in the
	   conditional operator, we create a conditional to select
	   the size of the active branch.  */
	ତାର୍କିକ use0 = cond && d1_variable && !c_type_unspecified_p (t1)
			 && d2_variable && !c_type_unspecified_p (t2);

	ବୃକ୍ଷ td;
	ବୃକ୍ଷ elt = composite_type_internal (ବୃକ୍ଷ_TYPE (t1), ବୃକ୍ଷ_TYPE (t2),
					    cond, cache);

	ଯଦି (!use0)
	  {
	    /* Save space: see if the result is identical to one of the args.  */
	    ଯଦି (elt == ବୃକ୍ଷ_TYPE (t1) && use1)
	      ଫେରନ୍ତୁ c_build_type_attribute_variant (t1, attributes);
	    ଯଦି (elt == ବୃକ୍ଷ_TYPE (t2) && use2)
	      ଫେରନ୍ତୁ c_build_type_attribute_variant (t2, attributes);

	    ଯଦି (elt == ବୃକ୍ଷ_TYPE (t1) && !TYPE_DOMAIN (t2) && !TYPE_DOMAIN (t1))
	      ଫେରନ୍ତୁ c_build_type_attribute_variant (t1, attributes);
	    ଯଦି (elt == ବୃକ୍ଷ_TYPE (t2) && !TYPE_DOMAIN (t2) && !TYPE_DOMAIN (t1))
	      ଫେରନ୍ତୁ c_build_type_attribute_variant (t2, attributes);

	    td = TYPE_DOMAIN (use1 ? t1 : t2);
	  }
	ଅନ୍ୟଥା
	  {
	    /* Not used in C.  */
	    gcc_assert (size_zero_ଗଣ୍ଠି == TYPE_MIN_ମୂଲ୍ୟ (d1));
	    gcc_assert (size_zero_ଗଣ୍ଠି == TYPE_MIN_ମୂଲ୍ୟ (d2));

	    ବୃକ୍ଷ d = fold_build3_loc (UNKNOWN_LOCATION, COND_ପଦସମଷ୍ଟି, sizetype,
				      cond, TYPE_MAX_ମୂଲ୍ୟ (d1),
				      TYPE_MAX_ମୂଲ୍ୟ (d2));

	    td = build_index_type (d);
	  }

	/* Merge the element types, and have a size if either arg has
	   one.  We may have qualifiers on the element types.  To set
	   up TYPE_MAIN_VARIANT correctly, we need to form the
	   composite of the unqualified types and add the qualifiers
	   back at the end.  */
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା quals = TYPE_QUALS (strip_array_types (elt));
	ବୃକ୍ଷ unqual_elt = c_build_qualified_type (elt, TYPE_UNQUALIFIED);

	ଯଦି ((!d1 || d1_zero) && (!d2 || d2_zero) && (d1 || d2))
	  t1 = c_build_array_type_zero_size (unqual_elt);
	ଅନ୍ୟଥା
	  t1 = c_build_array_type (unqual_elt, td);

	/* Check that a type which has a varying outermost dimension
	   got marked as having a variable size.  */
	ତାର୍କିକ varsize = (d1_variable && d2_variable)
		       || (d1_variable && !d2)
		       || (d2_variable && !d1);
	gcc_checking_assert (!varsize || C_TYPE_VARIABLE_SIZE (t1));

	t1 = c_build_qualified_type (t1, quals);
	ଫେରନ୍ତୁ c_build_type_attribute_variant (t1, attributes);
      }

    ସ୍ଥିତି RECORD_TYPE:
    ସ୍ଥିତି UNION_TYPE:
      ଯଦି (flag_isoc23 && !comptypes_same_p (t1, t2))
	{
	  /* Go to the original type to get the right tag.  */
	  ବୃକ୍ଷ tag = c_type_tag (t1);

	  gcc_checking_assert (COMPLETE_TYPE_P (t1) && COMPLETE_TYPE_P (t2));
	  gcc_checking_assert (!tag || comptypes (t1, t2));

	  /* If a composite type for these two types is already under
	     construction, return it.  */

	  ପାଇଁ (ସଂରଚନା composite_cache *c = cache; c != ଖାଲି; c = c->next)
	    ଯଦି ((c->t1 == t1 && c->t2 == t2) || (c->t1 == t2 && c->t2 == t1))
	       ଫେରନ୍ତୁ c->composite;

	  /* Otherwise, create a new type node and link it into the cache.  */

	  ବୃକ୍ଷ n = make_ଗଣ୍ଠି (code1);
	  SET_TYPE_STRUCTURAL_EQUALITY (n);
	  TYPE_NAME (n) = tag;

	  ସଂରଚନା composite_cache cache2 = { t1, t2, n, cache };
	  cache = &cache2;

	  ବୃକ୍ଷ f1 = TYPE_FIELDS (t1);
	  ବୃକ୍ଷ f2 = TYPE_FIELDS (t2);
	  ବୃକ୍ଷ fields = NULL_ବୃକ୍ଷ;

	  ପାଇଁ (ବୃକ୍ଷ a = f1, b = f2; a && b;
	       a = DECL_CHAIN (a), b = DECL_CHAIN (b))
	    {
	      ବୃକ୍ଷ ta = ବୃକ୍ଷ_TYPE (a);
	      ବୃକ୍ଷ tb = ବୃକ୍ଷ_TYPE (b);

	      ଯଦି (DECL_C_BIT_FIELD (a))
		{
		  ta = DECL_BIT_FIELD_TYPE (a);
		  tb = DECL_BIT_FIELD_TYPE (b);
		}

	      gcc_assert (DECL_NAME (a) == DECL_NAME (b));
	      gcc_checking_assert (!DECL_NAME (a) || comptypes (ta, tb));

	      ବୃକ୍ଷ t = composite_type_internal (ta, tb, cond, cache);
	      ବୃକ୍ଷ f = build_decl (ନିବେଶ_location, FIELD_DECL, DECL_NAME (a), t);

	      DECL_PACKED (f) = DECL_PACKED (a);
	      SET_DECL_ALIGN (f, DECL_ALIGN (a));
	      DECL_ATTRIBUTES (f) = DECL_ATTRIBUTES (a);
	      C_DECL_VARIABLE_SIZE (f) = C_TYPE_VARIABLE_SIZE (t);

	      decl_attributes (&f, DECL_ATTRIBUTES (f), 0);

	      finish_decl (f, ନିବେଶ_location, ଖାଲି, ଖାଲି, ଖାଲି);

	      ଯଦି (DECL_C_BIT_FIELD (a))
		{
		  /* This will be processed by finish_struct.  */
		  SET_DECL_C_BIT_FIELD (f);
		  DECL_INITIAL (f) = build_int_cst (integer_type_ଗଣ୍ଠି,
						    ବୃକ୍ଷ_to_uhwi (DECL_SIZE (a)));
		  DECL_NONADDRESSABLE_P (f) = ସତ୍ୟ;
		  DECL_PADDING_P (f) = !DECL_NAME (a);
		}

	      DECL_CHAIN (f) = fields;
	      fields = f;
	    }

	  fields = nreverse (fields);

	  /* Setup the struct/union type.  Because we inherit all variably
	     modified components, we can ignore the size expression.  */
	  ବୃକ୍ଷ ପଦସମଷ୍ଟି = NULL_ବୃକ୍ଷ;

	  /* Set TYPE_STUB_DECL for debugging symbols.  */
	  TYPE_STUB_DECL (n) = pushdecl (build_decl (ନିବେଶ_location, TYPE_DECL,
						     NULL_ବୃକ୍ଷ, n));

	  n = finish_struct (ନିବେଶ_location, n, fields, attributes, ଖାଲି,
			     &ପଦସମଷ୍ଟି);

	  ଫେରନ୍ତୁ qualify_type (n, t1);
	}
      /* FALLTHRU */
    ସ୍ଥିତି ENUMERAL_TYPE:
      ଯଦି (attributes != ଖାଲି)
	{
	  /* Try harder not to create a new aggregate type.  */
	  ଯଦି (attribute_list_equal (TYPE_ATTRIBUTES (t1), attributes))
	    ଫେରନ୍ତୁ t1;
	  ଯଦି (attribute_list_equal (TYPE_ATTRIBUTES (t2), attributes))
	    ଫେରନ୍ତୁ t2;
	}
      ଫେରନ୍ତୁ c_build_type_attribute_variant (t1, attributes);

    ସ୍ଥିତି FUNCTION_TYPE:
      /* Function types: prefer the one that specified arg types.
	 If both do, merge the arg types.  Also merge the return types.  */
      {
	ବୃକ୍ଷ valtype = composite_type_internal (ବୃକ୍ଷ_TYPE (t1), ବୃକ୍ଷ_TYPE (t2),
						cond, cache);
	ବୃକ୍ଷ p1 = TYPE_ARG_TYPES (t1);
	ବୃକ୍ଷ p2 = TYPE_ARG_TYPES (t2);

	/* Save space: see if the result is identical to one of the args.  */
	ଯଦି (valtype == ବୃକ୍ଷ_TYPE (t1) && !TYPE_ARG_TYPES (t2))
	  ଫେରନ୍ତୁ c_build_functype_attribute_variant (t1, t2, attributes);
	ଯଦି (valtype == ବୃକ୍ଷ_TYPE (t2) && !TYPE_ARG_TYPES (t1))
	  ଫେରନ୍ତୁ c_build_functype_attribute_variant (t2, t1, attributes);

	/* Simple way if one arg fails to specify argument types.  */
	ଯଦି (TYPE_ARG_TYPES (t1) == NULL_ବୃକ୍ଷ)
	  {
	    t1 = c_build_function_type (valtype, TYPE_ARG_TYPES (t2),
					TYPE_NO_NAMED_ARGS_STDARG_P (t2));
	    t1 = c_build_type_attribute_variant (t1, attributes);
	    ଫେରନ୍ତୁ qualify_type (t1, t2);
	 }
	ଯଦି (TYPE_ARG_TYPES (t2) == NULL_ବୃକ୍ଷ)
	  {
	    t1 = c_build_function_type (valtype, TYPE_ARG_TYPES (t1),
					TYPE_NO_NAMED_ARGS_STDARG_P (t1));
	    t1 = c_build_type_attribute_variant (t1, attributes);
	    ଫେରନ୍ତୁ qualify_type (t1, t2);
	  }

	/* If both args specify argument types, we must merge the two
	   lists, argument by argument.  */
	ବୃକ୍ଷ newargs = NULL_ବୃକ୍ଷ;
	ବୃକ୍ଷ *endp = &newargs;

	ପାଇଁ (; p1; p1 = ବୃକ୍ଷ_CHAIN (p1), p2 = ବୃକ୍ଷ_CHAIN (p2))
	  {
	    ଯଦି (p1 == void_list_ଗଣ୍ଠି)
	      {
		*endp = void_list_ଗଣ୍ଠି;
		ଭାଙ୍ଗ;
	      }
	    ବୃକ୍ଷ mv1 = remove_qualifiers (ବୃକ୍ଷ_ମୂଲ୍ୟ (p1));
	    ବୃକ୍ଷ mv2 = remove_qualifiers (ବୃକ୍ଷ_ମୂଲ୍ୟ (p2));

	    gcc_assert (mv1);
	    gcc_assert (mv2);

	    mv1 = transparent_union_replacement (mv1, mv2);
	    mv2 = transparent_union_replacement (mv2, mv1);

	    *endp = ବୃକ୍ଷ_cons (NULL_ବୃକ୍ଷ,
			       composite_type_internal (mv1, mv2, cond, cache),
			       NULL_ବୃକ୍ଷ);

	    endp = &ବୃକ୍ଷ_CHAIN (*endp);
	  }

	t1 = c_build_function_type (valtype, newargs);
	t1 = qualify_type (t1, t2);
      }
      /* FALLTHRU */

    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
      ଫେରନ୍ତୁ c_build_type_attribute_variant (t1, attributes);
    }
}

ବୃକ୍ଷ
composite_type_cond (ବୃକ୍ଷ t1, ବୃକ୍ଷ t2, ବୃକ୍ଷ cond)
{
  gcc_checking_assert (comptypes_check_for_composite (t1, t2));

  ସଂରଚନା composite_cache cache = { };
  ବୃକ୍ଷ n = composite_type_internal (t1, t2, cond, &cache);

  gcc_checking_assert (comptypes_check_for_composite (n, t1));
  gcc_checking_assert (comptypes_check_for_composite (n, t2));
  ଫେରନ୍ତୁ n;
}


ବୃକ୍ଷ
composite_type (ବୃକ୍ଷ t1, ବୃକ୍ଷ t2)
{
  ଫେରନ୍ତୁ composite_type_cond (t1, t2, NULL_ବୃକ୍ଷ);
}

/* Return the type of a conditional expression between pointers to
   possibly differently qualified versions of compatible types.

   We assume that comp_target_types has already been done and returned
   true; if that isn't so, this may crash.  */

ସ୍ଥିର ବୃକ୍ଷ
common_pointer_type (ବୃକ୍ଷ t1, ବୃକ୍ଷ t2, ବୃକ୍ଷ cond)
{
  ବୃକ୍ଷ attributes;
  unsigned target_quals;
  addr_space_t as1, as2, as_common;
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା quals1, quals2;

  /* Save time if the two types are the same.  */

  ଯଦି (t1 == t2) ଫେରନ୍ତୁ t1;

  /* If one type is nonsense, use the other.  */
  ଯଦି (t1 == error_mark_ଗଣ୍ଠି)
    ଫେରନ୍ତୁ t2;
  ଯଦି (t2 == error_mark_ଗଣ୍ଠି)
    ଫେରନ୍ତୁ t1;

  gcc_assert (ବୃକ୍ଷ_CODE (t1) == POINTER_TYPE
	      && ବୃକ୍ଷ_CODE (t2) == POINTER_TYPE);

  /* Merge the attributes.  */
  attributes = targetm.merge_type_attributes (t1, t2);

  /* Find the composite type of the target types, and combine the
     qualifiers of the two types' targets.  */
  ବୃକ୍ଷ pointed_to_1 = ବୃକ୍ଷ_TYPE (t1);
  ବୃକ୍ଷ pointed_to_2 = ବୃକ୍ଷ_TYPE (t2);
  ବୃକ୍ଷ target = composite_type_cond (TYPE_MAIN_VARIANT (pointed_to_1),
				     TYPE_MAIN_VARIANT (pointed_to_2), cond);

  /* Strip array types to get correct qualifier for pointers to arrays */
  quals1 = TYPE_QUALS_NO_ADDR_SPACE (strip_array_types (pointed_to_1));
  quals2 = TYPE_QUALS_NO_ADDR_SPACE (strip_array_types (pointed_to_2));

  /* For function types do not merge const qualifiers, but drop them
     if used inconsistently.  The middle-end uses these to mark const
     and noreturn functions.  */
  ଯଦି (ବୃକ୍ଷ_CODE (pointed_to_1) == FUNCTION_TYPE)
    target_quals = (quals1 & quals2);
  ଅନ୍ୟଥା
    target_quals = (quals1 | quals2);

  /* If the two named address spaces are different, determine the common
     superset address space.  This is guaranteed to exist due to the
     assumption that comp_target_type returned true.  */
  as1 = TYPE_ADDR_SPACE (pointed_to_1);
  as2 = TYPE_ADDR_SPACE (pointed_to_2);
  ଯଦି (!addr_space_superset (as1, as2, &as_common))
    gcc_unreachable ();

  target_quals |= ENCODE_QUAL_ADDR_SPACE (as_common);

  t1 = c_build_pointer_type (c_build_qualified_type (target, target_quals));
  ଫେରନ୍ତୁ c_build_type_attribute_variant (t1, attributes);
}

/* Return the common type for two arithmetic types under the usual
   arithmetic conversions.  The default conversions have already been
   applied, and enumerated types converted to their compatible integer
   types.  The resulting type is unqualified and has no attributes.

   This is the type for the result of most arithmetic operations
   if the operands have the given two types.  */

ସ୍ଥିର ବୃକ୍ଷ
c_common_type (ବୃକ୍ଷ t1, ବୃକ୍ଷ t2)
{
  ଗଣନା ବୃକ୍ଷ_code code1;
  ଗଣନା ବୃକ୍ଷ_code code2;

  /* If one type is nonsense, use the other.  */
  ଯଦି (t1 == error_mark_ଗଣ୍ଠି)
    ଫେରନ୍ତୁ t2;
  ଯଦି (t2 == error_mark_ଗଣ୍ଠି)
    ଫେରନ୍ତୁ t1;

  ଯଦି (TYPE_QUALS (t1) != TYPE_UNQUALIFIED)
    t1 = TYPE_MAIN_VARIANT (t1);

  ଯଦି (TYPE_QUALS (t2) != TYPE_UNQUALIFIED)
    t2 = TYPE_MAIN_VARIANT (t2);

  ଯଦି (TYPE_ATTRIBUTES (t1) != NULL_ବୃକ୍ଷ)
    {
      ବୃକ୍ଷ attrs = affects_type_identity_attributes (TYPE_ATTRIBUTES (t1));
      t1 = c_build_type_attribute_variant (t1, attrs);
    }

  ଯଦି (TYPE_ATTRIBUTES (t2) != NULL_ବୃକ୍ଷ)
    {
      ବୃକ୍ଷ attrs = affects_type_identity_attributes (TYPE_ATTRIBUTES (t2));
      t2 = c_build_type_attribute_variant (t2, attrs);
    }

  /* Save time if the two types are the same.  */

  ଯଦି (t1 == t2) ଫେରନ୍ତୁ t1;

  code1 = ବୃକ୍ଷ_CODE (t1);
  code2 = ବୃକ୍ଷ_CODE (t2);

  gcc_assert (code1 == VECTOR_TYPE || code1 == COMPLEX_TYPE
	      || code1 == FIXED_POINT_TYPE || code1 == REAL_TYPE
	      || code1 == INTEGER_TYPE || code1 == BITINT_TYPE);
  gcc_assert (code2 == VECTOR_TYPE || code2 == COMPLEX_TYPE
	      || code2 == FIXED_POINT_TYPE || code2 == REAL_TYPE
	      || code2 == INTEGER_TYPE || code2 == BITINT_TYPE);

  /* When one operand is a decimal float type, the other operand cannot be
     a generic float type or a complex type.  We also disallow vector types
     here.  */
  ଯଦି ((DECIMAL_FLOAT_TYPE_P (t1) || DECIMAL_FLOAT_TYPE_P (t2))
      && !(DECIMAL_FLOAT_TYPE_P (t1) && DECIMAL_FLOAT_TYPE_P (t2)))
    {
      ଯଦି (code1 == VECTOR_TYPE || code2 == VECTOR_TYPE)
	{
	  error ("cannot mix operands of decimal floating and vector types");
	  ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
	}
      ଯଦି (code1 == COMPLEX_TYPE || code2 == COMPLEX_TYPE)
	{
	  error ("cannot mix operands of decimal floating and complex types");
	  ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
	}
      ଯଦି (code1 == REAL_TYPE && code2 == REAL_TYPE)
	{
	  error ("cannot mix operands of decimal floating "
		 "and other floating types");
	  ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
	}
    }

  /* If one type is a vector type, return that type.  (How the usual
     arithmetic conversions apply to the vector types extension is not
     precisely specified.)  */
  ଯଦି (code1 == VECTOR_TYPE)
    ଫେରନ୍ତୁ t1;

  ଯଦି (code2 == VECTOR_TYPE)
    ଫେରନ୍ତୁ t2;

  /* If one type is complex, form the common type of the non-complex
     components, then make that complex.  Use T1 or T2 if it is the
     required type.  */
  ଯଦି (code1 == COMPLEX_TYPE || code2 == COMPLEX_TYPE)
    {
      ବୃକ୍ଷ subtype1 = code1 == COMPLEX_TYPE ? ବୃକ୍ଷ_TYPE (t1) : t1;
      ବୃକ୍ଷ subtype2 = code2 == COMPLEX_TYPE ? ବୃକ୍ଷ_TYPE (t2) : t2;
      ବୃକ୍ଷ subtype = c_common_type (subtype1, subtype2);

      ଯଦି (code1 == COMPLEX_TYPE && ବୃକ୍ଷ_TYPE (t1) == subtype)
	ଫେରନ୍ତୁ t1;
      ଅନ୍ୟଥା ଯଦି (code2 == COMPLEX_TYPE && ବୃକ୍ଷ_TYPE (t2) == subtype)
	ଫେରନ୍ତୁ t2;
      ଅନ୍ୟଥା ଯଦି (ବୃକ୍ଷ_CODE (subtype) == BITINT_TYPE)
	{
	  sorry ("%<_Complex _BitInt(%d)%> unsupported",
		 TYPE_PRECISION (subtype));
	  ଫେରନ୍ତୁ code1 == COMPLEX_TYPE ? t1 : t2;
	}
      ଅନ୍ୟଥା
	ଫେରନ୍ତୁ build_complex_type (subtype);
    }

  /* If only one is real, use it as the result.  */

  ଯଦି (code1 == REAL_TYPE && code2 != REAL_TYPE)
    ଫେରନ୍ତୁ t1;

  ଯଦି (code2 == REAL_TYPE && code1 != REAL_TYPE)
    ଫେରନ୍ତୁ t2;

  /* If both are real and either are decimal floating point types, use
     the decimal floating point type with the greater precision. */

  ଯଦି (code1 == REAL_TYPE && code2 == REAL_TYPE)
    {
      ଯଦି (TYPE_MAIN_VARIANT (t1) == dfloat128_type_ଗଣ୍ଠି
	  || TYPE_MAIN_VARIANT (t2) == dfloat128_type_ଗଣ୍ଠି)
	ଫେରନ୍ତୁ dfloat128_type_ଗଣ୍ଠି;
      /* And prefer _Decimal128 over _Decimal64x which has in GCC's
	 implementation the same mode.  */
      ଅନ୍ୟଥା ଯଦି (TYPE_MAIN_VARIANT (t1) == dfloat64x_type_ଗଣ୍ଠି
	       || TYPE_MAIN_VARIANT (t2) == dfloat64x_type_ଗଣ୍ଠି)
	ଫେରନ୍ତୁ dfloat64x_type_ଗଣ୍ଠି;
      ଅନ୍ୟଥା ଯଦି (TYPE_MAIN_VARIANT (t1) == dfloat64_type_ଗଣ୍ଠି
	       || TYPE_MAIN_VARIANT (t2) == dfloat64_type_ଗଣ୍ଠି)
	ଫେରନ୍ତୁ dfloat64_type_ଗଣ୍ଠି;
      ଅନ୍ୟଥା ଯଦି (TYPE_MAIN_VARIANT (t1) == dfloat32_type_ଗଣ୍ଠି
	       || TYPE_MAIN_VARIANT (t2) == dfloat32_type_ଗଣ୍ଠି)
	ଫେରନ୍ତୁ dfloat32_type_ଗଣ୍ଠି;
    }

  /* Deal with fixed-point types.  */
  ଯଦି (code1 == FIXED_POINT_TYPE || code2 == FIXED_POINT_TYPE)
    {
      unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା unsignedp = 0, satp = 0;
      scalar_mode m1, m2;
      unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା fbit1, ibit1, fbit2, ibit2, max_fbit, max_ibit;

      m1 = SCALAR_TYPE_MODE (t1);
      m2 = SCALAR_TYPE_MODE (t2);

      /* If one input type is saturating, the result type is saturating.  */
      ଯଦି (TYPE_SATURATING (t1) || TYPE_SATURATING (t2))
	satp = 1;

      /* If both fixed-point types are unsigned, the result type is unsigned.
	 When mixing fixed-point and integer types, follow the sign of the
	 fixed-point type.
	 Otherwise, the result type is signed.  */
      ଯଦି ((TYPE_UNSIGNED (t1) && TYPE_UNSIGNED (t2)
	   && code1 == FIXED_POINT_TYPE && code2 == FIXED_POINT_TYPE)
	  || (code1 == FIXED_POINT_TYPE && code2 != FIXED_POINT_TYPE
	      && TYPE_UNSIGNED (t1))
	  || (code1 != FIXED_POINT_TYPE && code2 == FIXED_POINT_TYPE
	      && TYPE_UNSIGNED (t2)))
	unsignedp = 1;

      /* The result type is signed.  */
      ଯଦି (unsignedp == 0)
	{
	  /* If the input type is unsigned, we need to convert to the
	     signed type.  */
	  ଯଦି (code1 == FIXED_POINT_TYPE && TYPE_UNSIGNED (t1))
	    {
	      ଗଣନା mode_class mclass = (ଗଣନା mode_class) 0;
	      ଯଦି (GET_MODE_CLASS (m1) == MODE_UFRACT)
		mclass = MODE_FRACT;
	      ଅନ୍ୟଥା ଯଦି (GET_MODE_CLASS (m1) == MODE_UACCUM)
		mclass = MODE_ACCUM;
	      ଅନ୍ୟଥା
		gcc_unreachable ();
	      m1 = as_a <scalar_mode>
		(mode_for_size (GET_MODE_PRECISION (m1), mclass, 0));
	    }
	  ଯଦି (code2 == FIXED_POINT_TYPE && TYPE_UNSIGNED (t2))
	    {
	      ଗଣନା mode_class mclass = (ଗଣନା mode_class) 0;
	      ଯଦି (GET_MODE_CLASS (m2) == MODE_UFRACT)
		mclass = MODE_FRACT;
	      ଅନ୍ୟଥା ଯଦି (GET_MODE_CLASS (m2) == MODE_UACCUM)
		mclass = MODE_ACCUM;
	      ଅନ୍ୟଥା
		gcc_unreachable ();
	      m2 = as_a <scalar_mode>
		(mode_for_size (GET_MODE_PRECISION (m2), mclass, 0));
	    }
	}

      ଯଦି (code1 == FIXED_POINT_TYPE)
	{
	  fbit1 = GET_MODE_FBIT (m1);
	  ibit1 = GET_MODE_IBIT (m1);
	}
      ଅନ୍ୟଥା
	{
	  fbit1 = 0;
	  /* Signed integers need to subtract one sign bit.  */
	  ibit1 = TYPE_PRECISION (t1) - (!TYPE_UNSIGNED (t1));
	}

      ଯଦି (code2 == FIXED_POINT_TYPE)
	{
	  fbit2 = GET_MODE_FBIT (m2);
	  ibit2 = GET_MODE_IBIT (m2);
	}
      ଅନ୍ୟଥା
	{
	  fbit2 = 0;
	  /* Signed integers need to subtract one sign bit.  */
	  ibit2 = TYPE_PRECISION (t2) - (!TYPE_UNSIGNED (t2));
	}

      max_ibit = ibit1 >= ibit2 ?  ibit1 : ibit2;
      max_fbit = fbit1 >= fbit2 ?  fbit1 : fbit2;
      ଫେରନ୍ତୁ c_common_fixed_point_type_for_size (max_ibit, max_fbit, unsignedp,
						 satp);
    }

  /* Both real or both integers; use the one with greater precision.  */

  ଯଦି (TYPE_PRECISION (t1) > TYPE_PRECISION (t2))
    ଫେରନ୍ତୁ t1;
  ଅନ୍ୟଥା ଯଦି (TYPE_PRECISION (t2) > TYPE_PRECISION (t1))
    ଫେରନ୍ତୁ t2;

  /* Same precision.  Prefer long longs to longs to ints when the
     same precision, following the C99 rules on integer type rank
     (which are equivalent to the C90 rules for C90 types).  */

  ଯଦି (TYPE_MAIN_VARIANT (t1) == long_long_unsigned_type_ଗଣ୍ଠି
      || TYPE_MAIN_VARIANT (t2) == long_long_unsigned_type_ଗଣ୍ଠି)
    ଫେରନ୍ତୁ long_long_unsigned_type_ଗଣ୍ଠି;

  ଯଦି (TYPE_MAIN_VARIANT (t1) == long_long_integer_type_ଗଣ୍ଠି
      || TYPE_MAIN_VARIANT (t2) == long_long_integer_type_ଗଣ୍ଠି)
    {
      ଯଦି (TYPE_UNSIGNED (t1) || TYPE_UNSIGNED (t2))
	ଫେରନ୍ତୁ long_long_unsigned_type_ଗଣ୍ଠି;
      ଅନ୍ୟଥା
	ଫେରନ୍ତୁ long_long_integer_type_ଗଣ୍ଠି;
    }

  ଯଦି (TYPE_MAIN_VARIANT (t1) == long_unsigned_type_ଗଣ୍ଠି
      || TYPE_MAIN_VARIANT (t2) == long_unsigned_type_ଗଣ୍ଠି)
    ଫେରନ୍ତୁ long_unsigned_type_ଗଣ୍ଠି;

  ଯଦି (TYPE_MAIN_VARIANT (t1) == long_integer_type_ଗଣ୍ଠି
      || TYPE_MAIN_VARIANT (t2) == long_integer_type_ଗଣ୍ଠି)
    {
      /* But preserve unsignedness from the other type,
	 since long cannot hold all the values of an unsigned int.  */
      ଯଦି (TYPE_UNSIGNED (t1) || TYPE_UNSIGNED (t2))
	ଫେରନ୍ତୁ long_unsigned_type_ଗଣ୍ଠି;
      ଅନ୍ୟଥା
	ଫେରନ୍ତୁ long_integer_type_ଗଣ୍ଠି;
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
  ବୃକ୍ଷ mv1 = TYPE_MAIN_VARIANT (t1);
  ବୃକ୍ଷ mv2 = TYPE_MAIN_VARIANT (t2);

  ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = ଅଙ୍କ_FLOATN_TYPES - 1; i >= 0; i--)
    ଯଦି (mv1 == FLOATN_TYPE_ଗଣ୍ଠି (i) || mv2 == FLOATN_TYPE_ଗଣ୍ଠି (i))
      ଫେରନ୍ତୁ FLOATN_TYPE_ଗଣ୍ଠି (i);

  /* Likewise, prefer long double to double even if same size.  */
  ଯଦି (mv1 == long_double_type_ଗଣ୍ଠି || mv2 == long_double_type_ଗଣ୍ଠି)
    ଫେରନ୍ତୁ long_double_type_ଗଣ୍ଠି;

  /* Likewise, prefer double to float even if same size.
     We got a couple of embedded targets with 32 bit doubles, and the
     pdp11 might have 64 bit floats.  */
  ଯଦି (mv1 == double_type_ଗଣ୍ଠି || mv2 == double_type_ଗଣ୍ଠି)
    ଫେରନ୍ତୁ double_type_ଗଣ୍ଠି;

  ଯଦି (mv1 == float_type_ଗଣ୍ଠି || mv2 == float_type_ଗଣ୍ଠି)
    ଫେରନ୍ତୁ float_type_ଗଣ୍ଠି;

  ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = ଅଙ୍କ_FLOATNX_TYPES - 1; i >= 0; i--)
    ଯଦି (mv1 == FLOATNX_TYPE_ଗଣ୍ଠି (i) || mv2 == FLOATNX_TYPE_ଗଣ୍ଠି (i))
      ଫେରନ୍ତୁ FLOATNX_TYPE_ଗଣ୍ଠି (i);

  ଯଦି ((code1 == BITINT_TYPE || code2 == BITINT_TYPE) && code1 != code2)
    {
      /* Prefer any other integral types over bit-precise integer types.  */
      ଯଦି (TYPE_UNSIGNED (t1) == TYPE_UNSIGNED (t2))
	ଫେରନ୍ତୁ code1 == BITINT_TYPE ? t2 : t1;
      /* If BITINT_TYPE is unsigned and the other type is signed
	 non-BITINT_TYPE with the same precision, the latter has higher rank.
	 In that case:
	 Otherwise, both operands are converted to the unsigned integer type
	 corresponding to the type of the operand with signed integer type.  */
      ଯଦି (TYPE_UNSIGNED (code1 == BITINT_TYPE ? t1 : t2))
	ଫେରନ୍ତୁ c_common_unsigned_type (code1 == BITINT_TYPE ? t2 : t1);
    }

  /* Otherwise prefer the unsigned one.  */

  ଯଦି (TYPE_UNSIGNED (t1))
    ଫେରନ୍ତୁ t1;
  ଅନ୍ୟଥା
    ଫେରନ୍ତୁ t2;
}

/* Wrapper around c_common_type that is used by c-common.cc and other
   front end optimizations that remove promotions.  ENUMERAL_TYPEs
   are allowed here and are converted to their compatible integer types.
   BOOLEAN_TYPEs are allowed here and return either boolean_type_node or
   preferably a non-Boolean type as the common type.  */
ବୃକ୍ଷ
common_type (ବୃକ୍ଷ t1, ବୃକ୍ଷ t2)
{
  ଯଦି (ବୃକ୍ଷ_CODE (t1) == ENUMERAL_TYPE)
    t1 = ENUM_UNDERLYING_TYPE (t1);
  ଯଦି (ବୃକ୍ଷ_CODE (t2) == ENUMERAL_TYPE)
    t2 = ENUM_UNDERLYING_TYPE (t2);

  /* If both types are BOOLEAN_TYPE, then return boolean_type_node.  */
  ଯଦି (ବୃକ୍ଷ_CODE (t1) == BOOLEAN_TYPE
      && ବୃକ୍ଷ_CODE (t2) == BOOLEAN_TYPE)
    ଫେରନ୍ତୁ boolean_type_ଗଣ୍ଠି;

  /* If either type is BOOLEAN_TYPE, then return the other.  */
  ଯଦି (ବୃକ୍ଷ_CODE (t1) == BOOLEAN_TYPE)
    ଫେରନ୍ତୁ t2;
  ଯଦି (ବୃକ୍ଷ_CODE (t2) == BOOLEAN_TYPE)
    ଫେରନ୍ତୁ t1;

  ଫେରନ୍ତୁ c_common_type (t1, t2);
}



/* Helper function for comptypes.  For two compatible types, return 1
   if they pass consistency checks.  In particular we test that
   TYPE_CANONICAL is set correctly, i.e. the two types can alias.  */

ସ୍ଥିର ତାର୍କିକ
comptypes_verify (ବୃକ୍ଷ type1, ବୃକ୍ଷ type2)
{
  ଯଦି (type1 == type2 || !type1 || !type2
      || ବୃକ୍ଷ_CODE (type1) == ERROR_MARK || ବୃକ୍ଷ_CODE (type2) == ERROR_MARK)
    ଫେରନ୍ତୁ ସତ୍ୟ;

  gcc_checking_assert (c_verify_type (type1));
  gcc_checking_assert (c_verify_type (type2));

  ଯଦି (TYPE_CANONICAL (type1) != TYPE_CANONICAL (type2)
      && !TYPE_STRUCTURAL_EQUALITY_P (type1)
      && !TYPE_STRUCTURAL_EQUALITY_P (type2))
    {
      /* FIXME: check other types. */
      ଯଦି (RECORD_OR_UNION_TYPE_P (type1)
	  || ବୃକ୍ଷ_CODE (type1) == ENUMERAL_TYPE
	  || ବୃକ୍ଷ_CODE (type2) == ENUMERAL_TYPE)
	ଫେରନ୍ତୁ ମିଥ୍ୟା;
    }
  ଫେରନ୍ତୁ ସତ୍ୟ;
}

ସଂରଚନା comptypes_data {

  /* output */
  ତାର୍କିକ enum_and_int_p;
  ତାର୍କିକ different_types_p;
  ତାର୍କିକ warning_needed;

  /* context */
  ତାର୍କିକ anon_field;
  ତାର୍କିକ pointedto;

  /* configuration */
  ତାର୍କିକ equiv;
  ତାର୍କିକ ignore_promoting_args;

  ଅଚଳ ସଂରଚନା tagged_tu_seen_cache* cache;
};


/* Helper function for composite_type.  This function ignores when the
   function type of an old-style declaration is incompatible with a type
   of a declaration with prototype because some are arguments are not
   self-promoting.  This is ignored only for function types but not
   ignored in a nested context.  */

ସ୍ଥିର ତାର୍କିକ
comptypes_check_for_composite (ବୃକ୍ଷ t1, ବୃକ୍ଷ t2)
{
  ସଂରଚନା comptypes_data data = { };
  data.ignore_promoting_args = FUNCTION_TYPE == ବୃକ୍ଷ_CODE (t1);
  ଫେରନ୍ତୁ comptypes_internal (t1, t2, &data);
}


/* C implementation of compatible_types_for_indirection_note_p.  */

ତାର୍କିକ
compatible_types_for_indirection_note_p (ବୃକ୍ଷ type1, ବୃକ୍ଷ type2)
{
  ଫେରନ୍ତୁ comptypes (type1, type2);
}

/* Return true if TYPE1 and TYPE2 are compatible types for assignment
   or various other operations.  */

ତାର୍କିକ
comptypes (ବୃକ୍ଷ type1, ବୃକ୍ଷ type2)
{
  ସଂରଚନା comptypes_data data = { };
  ତାର୍କିକ ret = comptypes_internal (type1, type2, &data);

  gcc_checking_assert (!ret || comptypes_verify (type1, type2));

  ଫେରନ୍ତୁ ret;
}


/* Like comptypes, but it returns non-zero only for identical
   types.  */

ତାର୍କିକ
comptypes_same_p (ବୃକ୍ଷ type1, ବୃକ୍ଷ type2)
{
  ସଂରଚନା comptypes_data data = { };
  ତାର୍କିକ ret = comptypes_internal (type1, type2, &data);

  gcc_checking_assert (!ret || comptypes_verify (type1, type2));

  ଯଦି (data.different_types_p)
    ଫେରନ୍ତୁ ମିଥ୍ୟା;

  ଫେରନ୍ତୁ ret;
}


/* Like comptypes, but if it returns true because enum and int are
   compatible, it sets *ENUM_AND_INT_P to true.  */

ତାର୍କିକ
comptypes_check_enum_int (ବୃକ୍ଷ type1, ବୃକ୍ଷ type2, ତାର୍କିକ *enum_and_int_p)
{
  ସଂରଚନା comptypes_data data = { };
  ତାର୍କିକ ret = comptypes_internal (type1, type2, &data);
  *enum_and_int_p = data.enum_and_int_p;

  gcc_checking_assert (!ret || comptypes_verify (type1, type2));

  ଫେରନ୍ତୁ ret;
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

ତାର୍କିକ
comptypes_equiv_p (ବୃକ୍ଷ type1, ବୃକ୍ଷ type2)
{
  ସଂରଚନା comptypes_data data = { };
  data.equiv = ସତ୍ୟ;
  ତାର୍କିକ ret = comptypes_internal (type1, type2, &data);

  /* check that different equivance classes are assigned only
     to types that are not compatible.  */
  gcc_checking_assert (ret || !comptypes (type1, type2));

  ଫେରନ୍ତୁ ret;
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

ସ୍ଥିର ତାର୍କିକ
comptypes_internal (const_ବୃକ୍ଷ type1, const_ବୃକ୍ଷ type2,
		    ସଂରଚନା comptypes_data *data)
{
  const_ବୃକ୍ଷ t1 = type1;
  const_ବୃକ୍ଷ t2 = type2;

  /* Suppress errors caused by previously reported errors.  */

  ଯଦି (t1 == t2 || !t1 || !t2
      || ବୃକ୍ଷ_CODE (t1) == ERROR_MARK || ବୃକ୍ଷ_CODE (t2) == ERROR_MARK)
    ଫେରନ୍ତୁ ସତ୍ୟ;

  /* Qualifiers must match. C99 6.7.3p9 */

  ଯଦି (TYPE_QUALS (t1) != TYPE_QUALS (t2))
    ଫେରନ୍ତୁ ମିଥ୍ୟା;

  /* Enumerated types are compatible with integer types, but this is
     not transitive: two enumerated types in the same translation unit
     are compatible with each other only if they are the same type.  */

  ଯଦି (ବୃକ୍ଷ_CODE (t1) == ENUMERAL_TYPE
      && COMPLETE_TYPE_P (t1)
      && ବୃକ୍ଷ_CODE (t2) != ENUMERAL_TYPE)
    {
      t1 = ENUM_UNDERLYING_TYPE (t1);
      ଯଦି (ବୃକ୍ଷ_CODE (t2) != VOID_TYPE)
	{
	  data->enum_and_int_p = ସତ୍ୟ;
	  data->different_types_p = ସତ୍ୟ;
	}
    }
  ଅନ୍ୟଥା ଯଦି (ବୃକ୍ଷ_CODE (t2) == ENUMERAL_TYPE
	   && COMPLETE_TYPE_P (t2)
	   && ବୃକ୍ଷ_CODE (t1) != ENUMERAL_TYPE)
    {
      t2 = ENUM_UNDERLYING_TYPE (t2);
      ଯଦି (ବୃକ୍ଷ_CODE (t1) != VOID_TYPE)
	{
	  data->enum_and_int_p = ସତ୍ୟ;
	  data->different_types_p = ସତ୍ୟ;
	}
    }

  ଯଦି (t1 == t2)
    ଫେରନ୍ତୁ ସତ୍ୟ;

  /* Different classes of types can't be compatible.  */

  ଯଦି (ବୃକ୍ଷ_CODE (t1) != ବୃକ୍ଷ_CODE (t2))
    ଫେରନ୍ତୁ ମିଥ୍ୟା;

  /* Allow for two different type nodes which have essentially the same
     definition.  Note that we already checked for equality of the type
     qualifiers (just above).  */

  ଯଦି (ବୃକ୍ଷ_CODE (t1) != ARRAY_TYPE
      && TYPE_MAIN_VARIANT (t1) == TYPE_MAIN_VARIANT (t2))
    ଫେରନ୍ତୁ ସତ୍ୟ;

  ପୂର୍ଣ୍ଣସଂଖ୍ୟା attrval;

  /* 1 if no need for warning yet, 2 if warning cause has been seen.  */
  ଯଦି (!(attrval = comp_type_attributes (t1, t2)))
    ଫେରନ୍ତୁ ମିଥ୍ୟା;

  ଯଦି (2 == attrval)
    data->warning_needed = ସତ୍ୟ;

  ବାଛ (ବୃକ୍ଷ_CODE (t1))
    {
    ସ୍ଥିତି INTEGER_TYPE:
    ସ୍ଥିତି FIXED_POINT_TYPE:
    ସ୍ଥିତି REAL_TYPE:
    ସ୍ଥିତି BITINT_TYPE:
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
      ଫେରନ୍ତୁ TYPE_CANONICAL (t1) == TYPE_CANONICAL (t2);

    ସ୍ଥିତି POINTER_TYPE:
      /* Do not remove mode information.  */
      ଯଦି (TYPE_MODE (t1) != TYPE_MODE (t2))
	ଫେରନ୍ତୁ ମିଥ୍ୟା;
      data->pointedto = ସତ୍ୟ;
      ଫେରନ୍ତୁ comptypes_internal (ବୃକ୍ଷ_TYPE (t1), ବୃକ୍ଷ_TYPE (t2), data);

    ସ୍ଥିତି FUNCTION_TYPE:
      ଫେରନ୍ତୁ function_types_compatible_p (t1, t2, data);

    ସ୍ଥିତି ARRAY_TYPE:
      {
	ବୃକ୍ଷ d1 = TYPE_DOMAIN (t1);
	ବୃକ୍ଷ d2 = TYPE_DOMAIN (t2);

	/* Target types must match incl. qualifiers.  */
	ଯଦି (!comptypes_internal (ବୃକ୍ଷ_TYPE (t1), ବୃକ୍ଷ_TYPE (t2), data))
	  ଫେରନ୍ତୁ ମିଥ୍ୟା;

	ଯଦି ((d1 == NULL_ବୃକ୍ଷ) != (d2 == NULL_ବୃକ୍ଷ))
	  data->different_types_p = ସତ୍ୟ;
	/* Ignore size mismatches when forming equivalence classes.  */
	ଯଦି (data->equiv)
	  ଫେରନ୍ତୁ ସତ୍ୟ;
	/* Sizes must match unless one is missing or variable.  */
	ଯଦି (d1 == NULL_ବୃକ୍ଷ || d2 == NULL_ବୃକ୍ଷ || d1 == d2)
	  ଫେରନ୍ତୁ ସତ୍ୟ;

	ତାର୍କିକ d1_variable = ଶୀର୍ଷ_array_vla_p (t1);
	ତାର୍କିକ d2_variable = ଶୀର୍ଷ_array_vla_p (t2);

	ଯଦି (d1_variable != d2_variable)
	  data->different_types_p = ସତ୍ୟ;
	ଯଦି (d1_variable || d2_variable)
	  ଫେରନ୍ତୁ ସତ୍ୟ;

	ତାର୍କିକ d1_zero = zero_length_array_type_p (t1)
		       || flexible_array_member_type_p (t1);

	ତାର୍କିକ d2_zero = zero_length_array_type_p (t2)
		       || flexible_array_member_type_p (t2);

	ଯଦି (d1_zero && d2_zero)
	  ଫେରନ୍ତୁ ସତ୍ୟ;
	ଯଦି (d1_zero || d2_zero)
	  ଫେରନ୍ତୁ ମିଥ୍ୟା;

	ଯଦି (!ବୃକ୍ଷ_int_cst_equal (TYPE_MIN_ମୂଲ୍ୟ (d1), TYPE_MIN_ମୂଲ୍ୟ (d2))
	    || !ବୃକ୍ଷ_int_cst_equal (TYPE_MAX_ମୂଲ୍ୟ (d1), TYPE_MAX_ମୂଲ୍ୟ (d2)))
	  ଫେରନ୍ତୁ ମିଥ୍ୟା;

	ଫେରନ୍ତୁ ସତ୍ୟ;
      }

    ସ୍ଥିତି ENUMERAL_TYPE:
    ସ୍ଥିତି RECORD_TYPE:
    ସ୍ଥିତି UNION_TYPE:

      ଯଦି (!flag_isoc23)
	ଫେରନ୍ତୁ ମିଥ୍ୟା;

      ଫେରନ୍ତୁ tagged_types_tu_compatible_p (t1, t2, data);

    ସ୍ଥିତି VECTOR_TYPE:
      ଫେରନ୍ତୁ known_eq (TYPE_VECTOR_SUBPARTS (t1), TYPE_VECTOR_SUBPARTS (t2))
	     && comptypes_internal (ବୃକ୍ଷ_TYPE (t1), ବୃକ୍ଷ_TYPE (t2), data);

    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
      ଫେରନ୍ତୁ ମିଥ୍ୟା;
    }
  gcc_unreachable ();
}

/* Return true if TTL and TTR are pointers to types that are equivalent, ignoring
   their qualifiers, except for named address spaces.  If the pointers point to
   different named addresses, then we must determine if one address space is a
   subset of the other.  */

ସ୍ଥିର ତାର୍କିକ
comp_target_types (location_t location, ବୃକ୍ଷ ttl, ବୃକ୍ଷ ttr)
{
  ବୃକ୍ଷ mvl = ବୃକ୍ଷ_TYPE (ttl);
  ବୃକ୍ଷ mvr = ବୃକ୍ଷ_TYPE (ttr);
  addr_space_t asl = TYPE_ADDR_SPACE (mvl);
  addr_space_t asr = TYPE_ADDR_SPACE (mvr);
  addr_space_t as_common;

  /* Fail if pointers point to incompatible address spaces.  */
  ଯଦି (!addr_space_superset (asl, asr, &as_common))
    ଫେରନ୍ତୁ 0;

  /* Qualifiers on element types of array types that are
     pointer targets are also removed.  */
  ସଂରଚନା comptypes_data data = { };
  ଯଦି (!comptypes_internal (remove_qualifiers (mvl),
			   remove_qualifiers (mvr), &data))
    ଫେରନ୍ତୁ ମିଥ୍ୟା;

  /* For pedantic use comptypes on arrays before removing
     qualifiers on the element type. */
  ଯଦି (ବୃକ୍ଷ_CODE (mvl) == ARRAY_TYPE
      && ବୃକ୍ଷ_CODE (mvr) == ARRAY_TYPE
      && !comptypes (mvl, mvr))
    pedwarn_c11 (location, OPT_Wpedantic, "invalid use of pointers to arrays "
					  "with different qualifiers in ISO C "
					  "before C23");

  ଯଦି (data.warning_needed)
    pedwarn (location, OPT_Wpedantic, "types are not quite compatible");

  ଯଦି (data.enum_and_int_p && warn_cxx_compat)
    warning_at (location, OPT_Wc___compat,
		"pointer target types incompatible in C++");

  ଫେରନ୍ତୁ ସତ୍ୟ;
}

/* Subroutines of `comptypes'.  */

/* Return true if two 'struct', 'union', or 'enum' types T1 and T2 are
   compatible.  The two types are not the same (which has been
   checked earlier in comptypes_internal).  */

ସ୍ଥିର ତାର୍କିକ
tagged_types_tu_compatible_p (const_ବୃକ୍ଷ t1, const_ବୃକ୍ଷ t2,
			      ସଂରଚନା comptypes_data *data)
{
  ବୃକ୍ଷ s1, s2;

  ଯଦି (c_type_tag (t1) != c_type_tag (t2))
    ଫେରନ୍ତୁ ମିଥ୍ୟା;

  /* When forming equivalence classes for TYPE_CANONICAL in C23, we treat
     structs with the same tag as equivalent, but only when they are targets
     of pointers inside other structs.  */
  ଯଦି (data->equiv && data->pointedto && NULL_ବୃକ୍ଷ != c_type_tag (t1))
    ଫେରନ୍ତୁ ସତ୍ୟ;

  /* Different types without tag are incompatible except as an anonymous
     field or when forming equivalence classes for TYPE_CANONICAL.  */
  ଯଦି (!data->anon_field && !data->equiv && NULL_ବୃକ୍ଷ == c_type_tag (t1))
    ଫେରନ୍ତୁ ମିଥ୍ୟା;

  ଯଦି (!data->anon_field && TYPE_STUB_DECL (t1) != TYPE_STUB_DECL (t2))
    data->different_types_p = ସତ୍ୟ;

  /* Incomplete types are incompatible inside a TU.  */
  ଯଦି (TYPE_SIZE (t1) == ଖାଲି || TYPE_SIZE (t2) == ଖାଲି)
    ଫେରନ୍ତୁ ମିଥ୍ୟା;

  ଯଦି (ENUMERAL_TYPE != ବୃକ୍ଷ_CODE (t1)
      && (TYPE_REVERSE_STORAGE_ORDER (t1)
	  != TYPE_REVERSE_STORAGE_ORDER (t2)))
    ଫେରନ୍ତୁ ମିଥ୍ୟା;

  ଯଦି (TYPE_USER_ALIGN (t1) != TYPE_USER_ALIGN (t2))
    data->different_types_p = ସତ୍ୟ;

  /* For types already being looked at in some active
     invocation of this function, assume compatibility.
     The cache is built as a linked list on the stack
     with the head of the list passed downwards.  */
  ପାଇଁ (ଅଚଳ ସଂରଚନା tagged_tu_seen_cache *t = data->cache;
       t != ଖାଲି; t = t->next)
    ଯଦି (t->t1 == t1 && t->t2 == t2)
      ଫେରନ୍ତୁ ସତ୍ୟ;

  ଅଚଳ ସଂରଚନା tagged_tu_seen_cache entry = { data->cache, t1, t2 };

  ବାଛ (ବୃକ୍ଷ_CODE (t1))
    {
    ସ୍ଥିତି ENUMERAL_TYPE:
      {
	ଯଦି (!comptypes (ENUM_UNDERLYING_TYPE (t1), ENUM_UNDERLYING_TYPE (t2)))
	  ଫେରନ୍ତୁ ମିଥ୍ୟା;

	/* Speed up the case where the type values are in the same order.  */
	ବୃକ୍ଷ tv1 = TYPE_ମୂଲ୍ୟଗୁଡ଼ିକ (t1);
	ବୃକ୍ଷ tv2 = TYPE_ମୂଲ୍ୟଗୁଡ଼ିକ (t2);

	ଯଦି (tv1 == tv2)
	  ଫେରନ୍ତୁ ସତ୍ୟ;

	ପାଇଁ (;tv1 && tv2; tv1 = ବୃକ୍ଷ_CHAIN (tv1), tv2 = ବୃକ୍ଷ_CHAIN (tv2))
	  {
	    ଯଦି (ବୃକ୍ଷ_PURPOSE (tv1) != ବୃକ୍ଷ_PURPOSE (tv2))
	      ଭାଙ୍ଗ;

	    ଯଦି (simple_cst_equal (DECL_INITIAL (ବୃକ୍ଷ_ମୂଲ୍ୟ (tv1)),
				  DECL_INITIAL (ବୃକ୍ଷ_ମୂଲ୍ୟ (tv2))) != 1)
	      ଭାଙ୍ଗ;
	  }

	ଯଦି (tv1 == NULL_ବୃକ୍ଷ && tv2 == NULL_ବୃକ୍ଷ)
	  ଫେରନ୍ତୁ ସତ୍ୟ;

	ଯଦି (tv1 == NULL_ବୃକ୍ଷ || tv2 == NULL_ବୃକ୍ଷ)
	  ଫେରନ୍ତୁ ମିଥ୍ୟା;

	ଯଦି (list_length (TYPE_ମୂଲ୍ୟଗୁଡ଼ିକ (t1)) != list_length (TYPE_ମୂଲ୍ୟଗୁଡ଼ିକ (t2)))
	  ଫେରନ୍ତୁ ମିଥ୍ୟା;

	ପାଇଁ (s1 = TYPE_ମୂଲ୍ୟଗୁଡ଼ିକ (t1); s1; s1 = ବୃକ୍ଷ_CHAIN (s1))
	  {
	    s2 = purpose_member (ବୃକ୍ଷ_PURPOSE (s1), TYPE_ମୂଲ୍ୟଗୁଡ଼ିକ (t2));

	    ଯଦି (s2 == ଖାଲି
		|| simple_cst_equal (DECL_INITIAL (ବୃକ୍ଷ_ମୂଲ୍ୟ (s1)),
				     DECL_INITIAL (ବୃକ୍ଷ_ମୂଲ୍ୟ (s2))) != 1)
	      ଫେରନ୍ତୁ ମିଥ୍ୟା;
	  }

	ଫେରନ୍ତୁ ସତ୍ୟ;
      }

    ସ୍ଥିତି UNION_TYPE:
    ସ୍ଥିତି RECORD_TYPE:

	ଯଦି (list_length (TYPE_FIELDS (t1)) != list_length (TYPE_FIELDS (t2)))
	  ଫେରନ୍ତୁ ମିଥ୍ୟା;

	ପାଇଁ (s1 = TYPE_FIELDS (t1), s2 = TYPE_FIELDS (t2);
	     s1 && s2;
	     s1 = DECL_CHAIN (s1), s2 = DECL_CHAIN (s2))
	  {
	    gcc_assert (ବୃକ୍ଷ_CODE (s1) == FIELD_DECL);
	    gcc_assert (ବୃକ୍ଷ_CODE (s2) == FIELD_DECL);

	    ବୃକ୍ଷ ft1 = ବୃକ୍ଷ_TYPE (s1);
	    ବୃକ୍ଷ ft2 = ବୃକ୍ଷ_TYPE (s2);

	    ଯଦି (DECL_NAME (s1) != DECL_NAME (s2))
	      ଫେରନ୍ତୁ ମିଥ୍ୟା;

	    ଯଦି (DECL_ALIGN (s1) != DECL_ALIGN (s2))
	      ଫେରନ୍ତୁ ମିଥ୍ୟା;

	    ଯଦି (DECL_C_BIT_FIELD (s1) != DECL_C_BIT_FIELD (s2))
	       ଫେରନ୍ତୁ ମିଥ୍ୟା;

	    ଯଦି (DECL_C_BIT_FIELD (s1))
	      {
		ଯଦି (!ବୃକ୍ଷ_int_cst_equal (DECL_SIZE (s1), DECL_SIZE (s2)))
		  ଫେରନ୍ତୁ ମିଥ୍ୟା;

		ft1 = DECL_BIT_FIELD_TYPE (s1);
		ft2 = DECL_BIT_FIELD_TYPE (s2);
	      }

	    ଯଦି (!ft1 || !ft2)
	      ଫେରନ୍ତୁ ମିଥ୍ୟା;

	    ଯଦି (ବୃକ୍ଷ_CODE (ft1) == ERROR_MARK || ବୃକ୍ଷ_CODE (ft2) == ERROR_MARK)
	      ଫେରନ୍ତୁ ମିଥ୍ୟା;

	    data->anon_field = !DECL_NAME (s1);
	    data->pointedto = ମିଥ୍ୟା;

	    ଅଚଳ ସଂରଚନା tagged_tu_seen_cache *cache = data->cache;
	    data->cache = &entry;
	    ତାର୍କିକ ret = comptypes_internal (ft1, ft2, data);
	    data->cache = cache;
	    ଯଦି (!ret)
	      ଫେରନ୍ତୁ ମିଥ୍ୟା;

	    ବୃକ୍ଷ st1 = TYPE_SIZE (ବୃକ୍ଷ_TYPE (s1));
	    ବୃକ୍ଷ st2 = TYPE_SIZE (ବୃକ୍ଷ_TYPE (s2));

	    ଯଦି (data->equiv
		&& st1 && ବୃକ୍ଷ_CODE (st1) == INTEGER_CST
		&& st2 && ବୃକ୍ଷ_CODE (st2) == INTEGER_CST
		&& !ବୃକ୍ଷ_int_cst_equal (st1, st2))
	     ଫେରନ୍ତୁ ମିଥ୍ୟା;

	    ବୃକ୍ଷ counted_by1 = lookup_attribute ("counted_by",
						 DECL_ATTRIBUTES (s1));
	    ବୃକ୍ଷ counted_by2 = lookup_attribute ("counted_by",
						 DECL_ATTRIBUTES (s2));
	    /* If there is no counted_by attribute for both fields.  */
	    ଯଦି (!counted_by1 && !counted_by2)
	      ଜାରି;

	    /* If only one field has counted_by attribute.  */
	    ଯଦି ((counted_by1 && !counted_by2)
		|| (!counted_by1 && counted_by2))
	      ଫେରନ୍ତୁ ମିଥ୍ୟା;

	    /* Now both s1 and s2 have counted_by attributes, check
	       whether they are the same.  */

	    ବୃକ୍ଷ counted_by_field1
	      = lookup_field (t1, ବୃକ୍ଷ_ମୂଲ୍ୟ (ବୃକ୍ଷ_ମୂଲ୍ୟ (counted_by1)));
	    ବୃକ୍ଷ counted_by_field2
	      = lookup_field (t2, ବୃକ୍ଷ_ମୂଲ୍ୟ (ବୃକ୍ଷ_ମୂଲ୍ୟ (counted_by2)));

	    gcc_assert (counted_by_field1 && counted_by_field2);

	    ଯେତେବେଳେ (ବୃକ୍ଷ_CHAIN (counted_by_field1))
	      counted_by_field1 = ବୃକ୍ଷ_CHAIN (counted_by_field1);
	    ଯେତେବେଳେ (ବୃକ୍ଷ_CHAIN (counted_by_field2))
	      counted_by_field2 = ବୃକ୍ଷ_CHAIN (counted_by_field2);

	    ଯଦି (DECL_NAME (ବୃକ୍ଷ_ମୂଲ୍ୟ (counted_by_field1))
		!= DECL_NAME (ବୃକ୍ଷ_ମୂଲ୍ୟ (counted_by_field2)))
	      ଫେରନ୍ତୁ ମିଥ୍ୟା;
	  }
	ଫେରନ୍ତୁ ସତ୍ୟ;

    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
      gcc_unreachable ();
    }
}

/* Return true if two function types F1 and F2 are compatible.
   If either type specifies no argument types,
   the other must specify a fixed number of self-promoting arg types.
   Otherwise, if one type specifies only the number of arguments,
   the other must specify that number of self-promoting arg types.
   Otherwise, the argument types must match.  */

ସ୍ଥିର ତାର୍କିକ
function_types_compatible_p (const_ବୃକ୍ଷ f1, const_ବୃକ୍ଷ f2,
			     ସଂରଚନା comptypes_data *data)
{
  ବୃକ୍ଷ ret1 = ବୃକ୍ଷ_TYPE (f1);
  ବୃକ୍ଷ ret2 = ବୃକ୍ଷ_TYPE (f2);

  /* 'volatile' qualifiers on a function's return type used to mean
     the function is noreturn.  */
  ଯଦି (TYPE_VOLATILE (ret1) != TYPE_VOLATILE (ret2))
    pedwarn (ନିବେଶ_location, 0, "function return types not compatible due to %<volatile%>");
  ଯଦି (TYPE_VOLATILE (ret1))
    ret1 = build_qualified_type (TYPE_MAIN_VARIANT (ret1),
				 TYPE_QUALS (ret1) & ~TYPE_QUAL_VOLATILE);
  ଯଦି (TYPE_VOLATILE (ret2))
    ret2 = build_qualified_type (TYPE_MAIN_VARIANT (ret2),
				 TYPE_QUALS (ret2) & ~TYPE_QUAL_VOLATILE);

  ତାର୍କିକ ignore_pargs = data->ignore_promoting_args;
  data->ignore_promoting_args = ମିଥ୍ୟା;

  ଯଦି (!comptypes_internal (ret1, ret2, data))
    ଫେରନ୍ତୁ ମିଥ୍ୟା;

  data->ignore_promoting_args = ignore_pargs;

  ବୃକ୍ଷ args1 = TYPE_ARG_TYPES (f1);
  ବୃକ୍ଷ args2 = TYPE_ARG_TYPES (f2);

  ଯଦି ((args1 == NULL_ବୃକ୍ଷ) != (args2 == NULL_ବୃକ୍ଷ))
    data->different_types_p = ସତ୍ୟ;

  /* An unspecified parmlist matches any specified parmlist
     whose argument types don't need default promotions.  */

  ଯଦି (args1 == NULL_ବୃକ୍ଷ)
    {
      ଯଦି (TYPE_NO_NAMED_ARGS_STDARG_P (f1) != TYPE_NO_NAMED_ARGS_STDARG_P (f2))
	ଫେରନ୍ତୁ ମିଥ୍ୟା;
      ଯଦି (!(data->ignore_promoting_args || self_promoting_args_p (args2)))
	ଫେରନ୍ତୁ ମିଥ୍ୟା;
      data->ignore_promoting_args = ମିଥ୍ୟା;
      /* If one of these types comes from a non-prototype fn definition,
	 compare that with the other type's arglist.
	 If they don't match, ask for a warning (but no error).  */
      ଯଦି (TYPE_ACTUAL_ARG_TYPES (f1)
	  && !type_lists_compatible_p (args2, TYPE_ACTUAL_ARG_TYPES (f1), data))
	 data->warning_needed = ସତ୍ୟ;
      ଫେରନ୍ତୁ ସତ୍ୟ;
    }
  ଯଦି (args2 == NULL_ବୃକ୍ଷ)
    {
      ଯଦି (TYPE_NO_NAMED_ARGS_STDARG_P (f1) != TYPE_NO_NAMED_ARGS_STDARG_P (f2))
	ଫେରନ୍ତୁ ମିଥ୍ୟା;
      ଯଦି (!(data->ignore_promoting_args || self_promoting_args_p (args1)))
	ଫେରନ୍ତୁ ମିଥ୍ୟା;
      data->ignore_promoting_args = ମିଥ୍ୟା;
      ଯଦି (TYPE_ACTUAL_ARG_TYPES (f2)
	  && !type_lists_compatible_p (args1, TYPE_ACTUAL_ARG_TYPES (f2), data))
	data->warning_needed = ସତ୍ୟ;
      ଫେରନ୍ତୁ ସତ୍ୟ;
    }

  /* Both types have argument lists: compare them and propagate results.  */
  ଫେରନ୍ତୁ type_lists_compatible_p (args1, args2, data);
}

/* Check two lists of types for compatibility, returning false for
   incompatible, true for compatible.  */

ସ୍ଥିର ତାର୍କିକ
type_lists_compatible_p (const_ବୃକ୍ଷ args1, const_ବୃକ୍ଷ args2,
			 ସଂରଚନା comptypes_data *data)
{
  ଯେତେବେଳେ (1)
    {
      ଯଦି (args1 == NULL_ବୃକ୍ଷ && args2 == NULL_ବୃକ୍ଷ)
	ଫେରନ୍ତୁ ସତ୍ୟ;
      /* If one list is shorter than the other,
	 they fail to match.  */
      ଯଦି (args1 == NULL_ବୃକ୍ଷ || args2 == NULL_ବୃକ୍ଷ)
	ଫେରନ୍ତୁ ମିଥ୍ୟା;
      ବୃକ୍ଷ a1 = ବୃକ୍ଷ_ମୂଲ୍ୟ (args1);
      ବୃକ୍ଷ a2 = ବୃକ୍ଷ_ମୂଲ୍ୟ (args2);
      ବୃକ୍ଷ mv1 = remove_qualifiers (a1);
      ବୃକ୍ଷ mv2 = remove_qualifiers (a2);

      gcc_assert (mv2);
      gcc_assert (mv2);

      /* If one of the lists has an error marker, ignore this arg.  */
      ଯଦି (ବୃକ୍ଷ_CODE (a1) == ERROR_MARK
	       || ବୃକ୍ଷ_CODE (a2) == ERROR_MARK)
	;
      ଅନ୍ୟଥା ଯଦି (!comptypes_internal (mv1, mv2, data))
	{
	  data->different_types_p = ସତ୍ୟ;
	  /* Allow  wait (union {union wait *u; int *i} *)
	     and  wait (union wait *)  to be compatible.  */
	  ଯଦି (ବୃକ୍ଷ_CODE (a1) == UNION_TYPE
	      && (TYPE_NAME (a1) == NULL_ବୃକ୍ଷ
		  || TYPE_TRANSPARENT_AGGR (a1))
	      && ବୃକ୍ଷ_CODE (TYPE_SIZE (a1)) == INTEGER_CST
	      && ବୃକ୍ଷ_int_cst_equal (TYPE_SIZE (a1),
				     TYPE_SIZE (a2)))
	    {
	      ବୃକ୍ଷ memb;
	      ପାଇଁ (memb = TYPE_FIELDS (a1);
		   memb; memb = DECL_CHAIN (memb))
		{
		  ବୃକ୍ଷ mv3 = remove_qualifiers (ବୃକ୍ଷ_TYPE (memb));
		  ଯଦି (comptypes_internal (mv3, mv2, data))
		    ଭାଙ୍ଗ;
		}
	      ଯଦି (memb == NULL_ବୃକ୍ଷ)
		ଫେରନ୍ତୁ ମିଥ୍ୟା;
	    }
	  ଅନ୍ୟଥା ଯଦି (ବୃକ୍ଷ_CODE (a2) == UNION_TYPE
		   && (TYPE_NAME (a2) == NULL_ବୃକ୍ଷ
		       || TYPE_TRANSPARENT_AGGR (a2))
		   && ବୃକ୍ଷ_CODE (TYPE_SIZE (a2)) == INTEGER_CST
		   && ବୃକ୍ଷ_int_cst_equal (TYPE_SIZE (a2),
					  TYPE_SIZE (a1)))
	    {
	      ବୃକ୍ଷ memb;
	      ପାଇଁ (memb = TYPE_FIELDS (a2);
		   memb; memb = DECL_CHAIN (memb))
		{
		  ବୃକ୍ଷ mv3 = remove_qualifiers (ବୃକ୍ଷ_TYPE (memb));
		  ଯଦି (comptypes_internal (mv3, mv1, data))
		    ଭାଙ୍ଗ;
		}
	      ଯଦି (memb == NULL_ବୃକ୍ଷ)
		ଫେରନ୍ତୁ ମିଥ୍ୟା;
	    }
	  ଅନ୍ୟଥା
	    ଫେରନ୍ତୁ ମିଥ୍ୟା;
	}

      args1 = ବୃକ୍ଷ_CHAIN (args1);
      args2 = ବୃକ୍ଷ_CHAIN (args2);
    }
}

/* Compute the size to increment a pointer by.  When a function type or void
   type or incomplete type is passed, size_one_node is returned.
   This function does not emit any diagnostics; the caller is responsible
   for that.  */

ସ୍ଥିର ବୃକ୍ଷ
c_size_in_bytes (const_ବୃକ୍ଷ type)
{
  ଗଣନା ବୃକ୍ଷ_code code = ବୃକ୍ଷ_CODE (type);

  ଯଦି (code == FUNCTION_TYPE || code == VOID_TYPE || code == ERROR_MARK
      || !COMPLETE_TYPE_P (type))
    ଫେରନ୍ତୁ size_one_ଗଣ୍ଠି;

  /* Convert in case a char is more than one unit.  */
  ଫେରନ୍ତୁ size_binop_loc (ନିବେଶ_location, CEIL_DIV_ପଦସମଷ୍ଟି, TYPE_SIZE_UNIT (type),
			 size_int (TYPE_PRECISION (char_type_ଗଣ୍ଠି)
				   / BITS_PER_UNIT));
}

/* Return either DECL or its known constant value (if it has one).  */

ବୃକ୍ଷ
decl_constant_ମୂଲ୍ୟ_1 (ବୃକ୍ଷ decl, ତାର୍କିକ in_init)
{
  ଯଦି (/* Note that DECL_INITIAL isn't valid for a PARM_DECL.  */
      ବୃକ୍ଷ_CODE (decl) != PARM_DECL
      && !ବୃକ୍ଷ_THIS_VOLATILE (decl)
      && ବୃକ୍ଷ_READONLY (decl)
      && DECL_INITIAL (decl) != NULL_ବୃକ୍ଷ
      && !error_operand_p (DECL_INITIAL (decl))
      /* This is invalid if initial value is not constant.
	 If it has either a function call, a memory reference,
	 or a variable, then re-evaluating it could give different results.  */
      && ବୃକ୍ଷ_CONSTANT (DECL_INITIAL (decl))
      /* Check for cases where this is sub-optimal, even though valid.  */
      && (in_init || ବୃକ୍ଷ_CODE (DECL_INITIAL (decl)) != CONSTRUCTOR))
    ଫେରନ୍ତୁ DECL_INITIAL (decl);
  ଫେରନ୍ତୁ decl;
}

/* Return either DECL or its known constant value (if it has one).
   Like the above, but always return decl outside of functions.  */

ବୃକ୍ଷ
decl_constant_ମୂଲ୍ୟ (ବୃକ୍ଷ decl)
{
  /* Don't change a variable array bound or initial value to a constant
     in a place where a variable is invalid.  */
  ଫେରନ୍ତୁ current_function_decl ? decl_constant_ମୂଲ୍ୟ_1 (decl, ମିଥ୍ୟା) : decl;
}

/* Convert the array expression EXP to a pointer.  */
ସ୍ଥିର ବୃକ୍ଷ
array_to_pointer_conversion (location_t loc, ବୃକ୍ଷ exp)
{
  ବୃକ୍ଷ orig_exp = exp;
  ବୃକ୍ଷ type = ବୃକ୍ଷ_TYPE (exp);
  ବୃକ୍ଷ adr;
  ବୃକ୍ଷ restype = ବୃକ୍ଷ_TYPE (type);
  ବୃକ୍ଷ ptrtype;

  gcc_assert (ବୃକ୍ଷ_CODE (type) == ARRAY_TYPE);

  STRIP_TYPE_NOPS (exp);

  copy_warning (exp, orig_exp);

  ptrtype = c_build_pointer_type (restype);

  ଯଦି (INDIRECT_REF_P (exp))
    ଫେରନ୍ତୁ convert (ptrtype, ବୃକ୍ଷ_OPERAND (exp, 0));

  /* In C++ array compound literals are temporary objects unless they are
     const or appear in namespace scope, so they are destroyed too soon
     to use them for much of anything  (c++/53220).  */
  ଯଦି (warn_cxx_compat && ବୃକ୍ଷ_CODE (exp) == COMPOUND_LITERAL_ପଦସମଷ୍ଟି)
    {
      ବୃକ୍ଷ decl = ବୃକ୍ଷ_OPERAND (ବୃକ୍ଷ_OPERAND (exp, 0), 0);
      ଯଦି (!ବୃକ୍ଷ_READONLY (decl) && !ବୃକ୍ଷ_STATIC (decl))
	warning_at (DECL_SOURCE_LOCATION (decl), OPT_Wc___compat,
		    "converting an array compound literal to a pointer "
		    "leads to a dangling pointer in C++");
    }

  adr = build_unary_op (loc, ADDR_ପଦସମଷ୍ଟି, exp, ସତ୍ୟ);
  ଫେରନ୍ତୁ convert (ptrtype, adr);
}

/* Convert the function expression EXP to a pointer.  */
ସ୍ଥିର ବୃକ୍ଷ
function_to_pointer_conversion (location_t loc, ବୃକ୍ଷ exp)
{
  ବୃକ୍ଷ orig_exp = exp;

  gcc_assert (ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (exp)) == FUNCTION_TYPE);

  STRIP_TYPE_NOPS (exp);

  copy_warning (exp, orig_exp);

  ବୃକ୍ଷ exp2 = build_unary_op (loc, ADDR_ପଦସମଷ୍ଟି, exp, ମିଥ୍ୟା);

  /* If the function is defined and known to not require a non-local
     context, make sure no trampoline is generated.  */
  ଯଦି (ବୃକ୍ଷ_CODE (exp) == FUNCTION_DECL
      && DECL_INITIAL (exp) && !C_FUNC_NONLOCAL_CONTEXT (exp))
   ବୃକ୍ଷ_NO_TRAMPOLINE (exp2) = 1;

  ଫେରନ୍ତୁ exp2;
}

/* Mark EXP as read, not just set, for set but not used -Wunused
   warning purposes.  */

ଶୂନ୍ୟ
mark_exp_read (ବୃକ୍ଷ exp)
{
  ବାଛ (ବୃକ୍ଷ_CODE (exp))
    {
    ସ୍ଥିତି VAR_DECL:
    ସ୍ଥିତି PARM_DECL:
      DECL_READ_P (exp) = 1;
      ଭାଙ୍ଗ;
    CASE_CONVERT:
      ଯଦି (VOID_TYPE_P (ବୃକ୍ଷ_TYPE (exp)))
	ବାଛ (ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_OPERAND (exp, 0)))
	  {
	  ସ୍ଥିତି PREINCREMENT_ପଦସମଷ୍ଟି:
	  ସ୍ଥିତି PREDECREMENT_ପଦସମଷ୍ଟି:
	  ସ୍ଥିତି POSTINCREMENT_ପଦସମଷ୍ଟି:
	  ସ୍ଥିତି POSTDECREMENT_ପଦସମଷ୍ଟି:
	    ଫେରନ୍ତୁ;
	  ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
	    ଭାଙ୍ଗ;
	  }
      /* FALLTHRU */
    ସ୍ଥିତି ARRAY_REF:
    ସ୍ଥିତି COMPONENT_REF:
    ସ୍ଥିତି MODIFY_ପଦସମଷ୍ଟି:
    ସ୍ଥିତି REALPART_ପଦସମଷ୍ଟି:
    ସ୍ଥିତି IMAGPART_ପଦସମଷ୍ଟି:
    ସ୍ଥିତି ADDR_ପଦସମଷ୍ଟି:
    ସ୍ଥିତି VIEW_CONVERT_ପଦସମଷ୍ଟି:
    ସ୍ଥିତି PREINCREMENT_ପଦସମଷ୍ଟି:
    ସ୍ଥିତି PREDECREMENT_ପଦସମଷ୍ଟି:
    ସ୍ଥିତି POSTINCREMENT_ପଦସମଷ୍ଟି:
    ସ୍ଥିତି POSTDECREMENT_ପଦସମଷ୍ଟି:
      mark_exp_read (ବୃକ୍ଷ_OPERAND (exp, 0));
      ଭାଙ୍ଗ;
    ସ୍ଥିତି COMPOUND_ପଦସମଷ୍ଟି:
      /* Pattern match what build_atomic_assign produces with modifycode
	 NOP_EXPR.  */
      ଯଦି (VAR_P (ବୃକ୍ଷ_OPERAND (exp, 1))
	  && DECL_ARTIFICIAL (ବୃକ୍ଷ_OPERAND (exp, 1))
	  && ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_OPERAND (exp, 0)) == COMPOUND_ପଦସମଷ୍ଟି)
	{
	  ବୃକ୍ଷ t1 = ବୃକ୍ଷ_OPERAND (ବୃକ୍ଷ_OPERAND (exp, 0), 0);
	  ବୃକ୍ଷ t2 = ବୃକ୍ଷ_OPERAND (ବୃକ୍ଷ_OPERAND (exp, 0), 1);
	  ଯଦି (ବୃକ୍ଷ_CODE (t1) == TARGET_ପଦସମଷ୍ଟି
	      && TARGET_ପଦସମଷ୍ଟି_SLOT (t1) == ବୃକ୍ଷ_OPERAND (exp, 1)
	      && ବୃକ୍ଷ_CODE (t2) == CALL_ପଦସମଷ୍ଟି)
	    {
	      ବୃକ୍ଷ fndecl = get_callee_fndecl (t2);
	      ବୃକ୍ଷ arg = NULL_ବୃକ୍ଷ;
	      ଯଦି (fndecl
		  && ବୃକ୍ଷ_CODE (fndecl) == FUNCTION_DECL
		  && fndecl_built_in_p (fndecl, BUILT_IN_NORMAL)
		  && call_ପଦସମଷ୍ଟି_nargs (t2) >= 2)
		ବାଛ (DECL_FUNCTION_CODE (fndecl))
		  {
		  ସ୍ଥିତି BUILT_IN_ATOMIC_STORE:
		    arg = CALL_ପଦସମଷ୍ଟି_ARG (t2, 1);
		    ଭାଙ୍ଗ;
		  ସ୍ଥିତି BUILT_IN_ATOMIC_STORE_1:
		  ସ୍ଥିତି BUILT_IN_ATOMIC_STORE_2:
		  ସ୍ଥିତି BUILT_IN_ATOMIC_STORE_4:
		  ସ୍ଥିତି BUILT_IN_ATOMIC_STORE_8:
		  ସ୍ଥିତି BUILT_IN_ATOMIC_STORE_16:
		    arg = CALL_ପଦସମଷ୍ଟି_ARG (t2, 0);
		    ଭାଙ୍ଗ;
		  ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
		    ଭାଙ୍ଗ;
		  }
	      ଯଦି (arg)
		{
		  STRIP_NOPS (arg);
		  ଯଦି (ବୃକ୍ଷ_CODE (arg) == ADDR_ପଦସମଷ୍ଟି
		      && DECL_P (ବୃକ୍ଷ_OPERAND (arg, 0))
		      && TYPE_ATOMIC (ବୃକ୍ଷ_TYPE (ବୃକ୍ଷ_OPERAND (arg, 0))))
		    mark_exp_read (ବୃକ୍ଷ_OPERAND (arg, 0));
		}
	    }
	}
      /* FALLTHRU */
    ସ୍ଥିତି C_MAYBE_CONST_ପଦସମଷ୍ଟି:
      mark_exp_read (ବୃକ୍ଷ_OPERAND (exp, 1));
      ଭାଙ୍ଗ;
    ସ୍ଥିତି OMP_ARRAY_SECTION:
      mark_exp_read (ବୃକ୍ଷ_OPERAND (exp, 0));
      ଯଦି (ବୃକ୍ଷ_OPERAND (exp, 1))
	mark_exp_read (ବୃକ୍ଷ_OPERAND (exp, 1));
      ଯଦି (ବୃକ୍ଷ_OPERAND (exp, 2))
	mark_exp_read (ବୃକ୍ଷ_OPERAND (exp, 2));
      ଭାଙ୍ଗ;
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
      ଭାଙ୍ଗ;
    }
}

/* Perform the default conversion of arrays and functions to pointers.
   Return the result of converting EXP.  For any other expression, just
   return EXP.

   LOC is the location of the expression.  */

ସଂରଚନା c_ପଦସମଷ୍ଟି
default_function_array_conversion (location_t loc, ସଂରଚନା c_ପଦସମଷ୍ଟି exp)
{
  ବୃକ୍ଷ orig_exp = exp.ମୂଲ୍ୟ;
  ବୃକ୍ଷ type = ବୃକ୍ଷ_TYPE (exp.ମୂଲ୍ୟ);
  ଗଣନା ବୃକ୍ଷ_code code = ବୃକ୍ଷ_CODE (type);

  ବାଛ (code)
    {
    ସ୍ଥିତି ARRAY_TYPE:
      {
	ତାର୍କିକ not_lvalue = ମିଥ୍ୟା;
	ତାର୍କିକ lvalue_array_p;

	ଯେତେବେଳେ ((ବୃକ୍ଷ_CODE (exp.ମୂଲ୍ୟ) == NON_LVALUE_ପଦସମଷ୍ଟି
		|| CONVERT_ପଦସମଷ୍ଟି_P (exp.ମୂଲ୍ୟ))
	       && ବୃକ୍ଷ_TYPE (ବୃକ୍ଷ_OPERAND (exp.ମୂଲ୍ୟ, 0)) == type)
	  {
	    ଯଦି (ବୃକ୍ଷ_CODE (exp.ମୂଲ୍ୟ) == NON_LVALUE_ପଦସମଷ୍ଟି)
	      not_lvalue = ସତ୍ୟ;
	    exp.ମୂଲ୍ୟ = ବୃକ୍ଷ_OPERAND (exp.ମୂଲ୍ୟ, 0);
	  }

	copy_warning (exp.ମୂଲ୍ୟ, orig_exp);

	lvalue_array_p = !not_lvalue && lvalue_p (exp.ମୂଲ୍ୟ);
	ଯଦି (!flag_isoc99 && !lvalue_array_p)
	  {
	    /* Before C99, non-lvalue arrays do not decay to pointers.
	       Normally, using such an array would be invalid; but it can
	       be used correctly inside sizeof or as a statement expression.
	       Thus, do not give an error here; an error will result later.  */
	    ଫେରନ୍ତୁ exp;
	  }

	exp.ମୂଲ୍ୟ = array_to_pointer_conversion (loc, exp.ମୂଲ୍ୟ);
      }
      ଭାଙ୍ଗ;
    ସ୍ଥିତି FUNCTION_TYPE:
      exp.ମୂଲ୍ୟ = function_to_pointer_conversion (loc, exp.ମୂଲ୍ୟ);
      ଭାଙ୍ଗ;
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
      ଭାଙ୍ଗ;
    }

  ଫେରନ୍ତୁ exp;
}

ସଂରଚନା c_ପଦସମଷ୍ଟି
default_function_array_read_conversion (location_t loc, ସଂରଚନା c_ପଦସମଷ୍ଟି exp)
{
  mark_exp_read (exp.ମୂଲ୍ୟ);
  /* We only generate a call to .ACCESS_WITH_SIZE when it is a read.  */
  ଯଦି (ବୃକ୍ଷ_CODE (exp.ମୂଲ୍ୟ) == COMPONENT_REF
      && handle_counted_by_p (exp.ମୂଲ୍ୟ))
    exp.ମୂଲ୍ୟ = handle_counted_by_for_component_ref (loc, exp.ମୂଲ୍ୟ);
  ଫେରନ୍ତୁ default_function_array_conversion (loc, exp);
}

/* Return whether EXPR should be treated as an atomic lvalue for the
   purposes of load and store handling.  */

ସ୍ଥିର ତାର୍କିକ
really_atomic_lvalue (ବୃକ୍ଷ ପଦସମଷ୍ଟି)
{
  ଯଦି (error_operand_p (ପଦସମଷ୍ଟି))
    ଫେରନ୍ତୁ ମିଥ୍ୟା;
  ଯଦି (!TYPE_ATOMIC (ବୃକ୍ଷ_TYPE (ପଦସମଷ୍ଟି)))
    ଫେରନ୍ତୁ ମିଥ୍ୟା;
  ଯଦି (!COMPLETE_TYPE_P (ବୃକ୍ଷ_TYPE (ପଦସମଷ୍ଟି)))
    ଫେରନ୍ତୁ ମିଥ୍ୟା;
  ଯଦି (!lvalue_p (ପଦସମଷ୍ଟି))
    ଫେରନ୍ତୁ ମିଥ୍ୟା;

  /* Ignore _Atomic on register variables, since their addresses can't
     be taken so (a) atomicity is irrelevant and (b) the normal atomic
     sequences wouldn't work.  Ignore _Atomic on structures containing
     bit-fields, since accessing elements of atomic structures or
     unions is undefined behavior (C11 6.5.2.3#5), but it's unclear if
     it's undefined at translation time or execution time, and the
     normal atomic sequences again wouldn't work.  */
  ଯେତେବେଳେ (handled_component_p (ପଦସମଷ୍ଟି))
    {
      ଯଦି (ବୃକ୍ଷ_CODE (ପଦସମଷ୍ଟି) == COMPONENT_REF
	  && DECL_C_BIT_FIELD (ବୃକ୍ଷ_OPERAND (ପଦସମଷ୍ଟି, 1)))
	ଫେରନ୍ତୁ ମିଥ୍ୟା;
      ପଦସମଷ୍ଟି = ବୃକ୍ଷ_OPERAND (ପଦସମଷ୍ଟି, 0);
    }
  ଯଦି (ବୃକ୍ଷ_CODE (ପଦସମଷ୍ଟି) == COMPOUND_LITERAL_ପଦସମଷ୍ଟି)
    ପଦସମଷ୍ଟି = COMPOUND_LITERAL_ପଦସମଷ୍ଟି_DECL (ପଦସମଷ୍ଟି);
  ଯଦି (DECL_P (ପଦସମଷ୍ଟି) && C_DECL_REGISTER (ପଦସମଷ୍ଟି))
    ଫେରନ୍ତୁ ମିଥ୍ୟା;
  ଫେରନ୍ତୁ ସତ୍ୟ;
}

/* If EXPR is a named constant (C23) derived from a constexpr variable
   - that is, a reference to such a variable, or a member extracted by
   a sequence of structure and union (but not array) member accesses
   (where union member accesses must access the same member as
   initialized) - then return the corresponding initializer;
   otherwise, return NULL_TREE.  */

ସ୍ଥିର ବୃକ୍ଷ
maybe_get_constexpr_init (ବୃକ୍ଷ ପଦସମଷ୍ଟି)
{
  ବୃକ୍ଷ decl = NULL_ବୃକ୍ଷ;
  ଯଦି (ବୃକ୍ଷ_CODE (ପଦସମଷ୍ଟି) == VAR_DECL)
    decl = ପଦସମଷ୍ଟି;
  ଅନ୍ୟଥା ଯଦି (ବୃକ୍ଷ_CODE (ପଦସମଷ୍ଟି) == COMPOUND_LITERAL_ପଦସମଷ୍ଟି)
    decl = COMPOUND_LITERAL_ପଦସମଷ୍ଟି_DECL (ପଦସମଷ୍ଟି);
  ଯଦି (decl
      && C_DECL_DECLARED_CONSTEXPR (decl)
      && DECL_INITIAL (decl) != NULL_ବୃକ୍ଷ
      && !error_operand_p (DECL_INITIAL (decl)))
    ଫେରନ୍ତୁ DECL_INITIAL (decl);
  ଯଦି (ବୃକ୍ଷ_CODE (ପଦସମଷ୍ଟି) != COMPONENT_REF)
    ଫେରନ୍ତୁ NULL_ବୃକ୍ଷ;
  ବୃକ୍ଷ inner = maybe_get_constexpr_init (ବୃକ୍ଷ_OPERAND (ପଦସମଷ୍ଟି, 0));
  ଯଦି (inner == NULL_ବୃକ୍ଷ)
    ଫେରନ୍ତୁ NULL_ବୃକ୍ଷ;
  ଯେତେବେଳେ ((CONVERT_ପଦସମଷ୍ଟି_P (inner) || ବୃକ୍ଷ_CODE (inner) == NON_LVALUE_ପଦସମଷ୍ଟି)
	 && !error_operand_p (inner)
	 && (TYPE_MAIN_VARIANT (ବୃକ୍ଷ_TYPE (inner))
	     == TYPE_MAIN_VARIANT (ବୃକ୍ଷ_TYPE (ବୃକ୍ଷ_OPERAND (inner, 0)))))
    inner = ବୃକ୍ଷ_OPERAND (inner, 0);
  ଯଦି (ବୃକ୍ଷ_CODE (inner) != CONSTRUCTOR)
    ଫେରନ୍ତୁ NULL_ବୃକ୍ଷ;
  ବୃକ୍ଷ field = ବୃକ୍ଷ_OPERAND (ପଦସମଷ୍ଟି, 1);
  unsigned HOST_WIDE_INT cidx;
  ବୃକ୍ଷ cfield, cvalue;
  ତାର୍କିକ have_other_init = ମିଥ୍ୟା;
  FOR_EACH_CONSTRUCTOR_ELT (CONSTRUCTOR_ELTS (inner), cidx, cfield, cvalue)
    {
      ଯଦି (cfield == field)
	ଫେରନ୍ତୁ cvalue;
      have_other_init = ସତ୍ୟ;
    }
  ଯଦି (ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (inner)) == UNION_TYPE
      && (have_other_init || field != TYPE_FIELDS (ବୃକ୍ଷ_TYPE (inner))))
    ଫେରନ୍ତୁ NULL_ବୃକ୍ଷ;
  /* Return a default initializer.  */
  ଯଦି (RECORD_OR_UNION_TYPE_P (ବୃକ୍ଷ_TYPE (ପଦସମଷ୍ଟି)))
    ଫେରନ୍ତୁ build_constructor (ବୃକ୍ଷ_TYPE (ପଦସମଷ୍ଟି), ଖାଲି);
  ଫେରନ୍ତୁ build_zero_cst (ବୃକ୍ଷ_TYPE (ପଦସମଷ୍ଟି));
}

/* Helper function for convert_lvalue_to_rvalue called via
   walk_tree_without_duplicates.  Find DATA inside of the expression.  */

ସ୍ଥିର ବୃକ୍ଷ
c_find_var_r (ବୃକ୍ଷ *tp, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *walk_subtrees, ଶୂନ୍ୟ *data)
{
  ଯଦି (TYPE_P (*tp))
    *walk_subtrees = 0;
  ଅନ୍ୟଥା ଯଦି (*tp == (ବୃକ୍ଷ) data)
    ଫେରନ୍ତୁ *tp;
  ଫେରନ୍ତୁ NULL_ବୃକ୍ଷ;
}

/* Convert expression EXP (location LOC) from lvalue to rvalue,
   including converting functions and arrays to pointers if CONVERT_P.
   If READ_P, also mark the expression as having been read.  If
   FOR_INIT, constexpr expressions of structure and union type should
   be replaced by the corresponding CONSTRUCTOR; otherwise, only
   constexpr scalars (including elements of structures and unions) are
   replaced by their initializers.  */

ସଂରଚନା c_ପଦସମଷ୍ଟି
convert_lvalue_to_rvalue (location_t loc, ସଂରଚନା c_ପଦସମଷ୍ଟି exp,
			  ତାର୍କିକ convert_p, ତାର୍କିକ read_p, ତାର୍କିକ for_init)
{
  ତାର୍କିକ force_non_npc = ମିଥ୍ୟା;
  ଯଦି (read_p)
    mark_exp_read (exp.ମୂଲ୍ୟ);
  /* We only generate a call to .ACCESS_WITH_SIZE when it is a read.  */
  ଯଦି (read_p && ବୃକ୍ଷ_CODE (exp.ମୂଲ୍ୟ) == COMPONENT_REF
      && handle_counted_by_p (exp.ମୂଲ୍ୟ))
    exp.ମୂଲ୍ୟ = handle_counted_by_for_component_ref (loc, exp.ମୂଲ୍ୟ);

  ଯଦି (convert_p)
    exp = default_function_array_conversion (loc, exp);
  ଯଦି (!VOID_TYPE_P (ବୃକ୍ଷ_TYPE (exp.ମୂଲ୍ୟ))
      || (flag_isoc2y
	  && TYPE_QUALS (ବୃକ୍ଷ_TYPE (exp.ମୂଲ୍ୟ)) != TYPE_UNQUALIFIED))
    exp.ମୂଲ୍ୟ = require_complete_type (loc, exp.ମୂଲ୍ୟ);
  ଯଦି (for_init || !RECORD_OR_UNION_TYPE_P (ବୃକ୍ଷ_TYPE (exp.ମୂଲ୍ୟ)))
    {
      ବୃକ୍ଷ init = maybe_get_constexpr_init (exp.ମୂଲ୍ୟ);
      ଯଦି (init != NULL_ବୃକ୍ଷ)
	{
	  /* A named constant of pointer type or type nullptr_t is not
	     a null pointer constant even if the initializer is
	     one.  */
	  ଯଦି (ବୃକ୍ଷ_CODE (init) == INTEGER_CST
	      && !INTEGRAL_TYPE_P (ବୃକ୍ଷ_TYPE (init))
	      && integer_zerop (init))
	    force_non_npc = ସତ୍ୟ;
	  exp.ମୂଲ୍ୟ = init;
	}
    }
  ଯଦି (really_atomic_lvalue (exp.ମୂଲ୍ୟ))
    {
      vec<ବୃକ୍ଷ, va_gc> *params;
      ବୃକ୍ଷ nonatomic_type, tmp, tmp_addr, fndecl, func_call;
      ବୃକ୍ଷ ପଦସମଷ୍ଟି_type = ବୃକ୍ଷ_TYPE (exp.ମୂଲ୍ୟ);
      ବୃକ୍ଷ ପଦସମଷ୍ଟି_addr = build_unary_op (loc, ADDR_ପଦସମଷ୍ଟି, exp.ମୂଲ୍ୟ, ମିଥ୍ୟା);
      ବୃକ୍ଷ seq_cst = build_int_cst (integer_type_ଗଣ୍ଠି, MEMMODEL_SEQ_CST);

      gcc_assert (TYPE_ATOMIC (ପଦସମଷ୍ଟି_type));

      /* Expansion of a generic atomic load may require an addition
	 element, so allocate enough to prevent a resize.  */
      vec_alloc (params, 4);

      /* Remove the qualifiers for the rest of the expressions and
	 create the VAL temp variable to hold the RHS.  */
      nonatomic_type = build_qualified_type (ପଦସମଷ୍ଟି_type, TYPE_UNQUALIFIED);
      tmp = create_tmp_var_raw (nonatomic_type);
      tmp_addr = build_unary_op (loc, ADDR_ପଦସମଷ୍ଟି, tmp, ମିଥ୍ୟା);
      ବୃକ୍ଷ_ADDRESSABLE (tmp) = 1;
      /* Do not disable warnings for TMP even though it's artificial.
	 -Winvalid-memory-model depends on it.  */

      /* Issue __atomic_load (&expr, &tmp, SEQ_CST);  */
      fndecl = builtin_decl_explicit (BUILT_IN_ATOMIC_LOAD);
      params->quick_ଠେଲ (ପଦସମଷ୍ଟି_addr);
      params->quick_ଠେଲ (tmp_addr);
      params->quick_ଠେଲ (seq_cst);
      func_call = c_build_function_call_vec (loc, vNULL, fndecl, params, ଖାଲି);

      /* EXPR is always read.  */
      mark_exp_read (exp.ମୂଲ୍ୟ);

      /* Optimize the common case where c_build_function_call_vec
	 immediately folds __atomic_load (&expr, &tmp, SEQ_CST); into
	 tmp = __atomic_load_<N> (&expr, SEQ_CST);
	 In that case tmp is not addressable and can be initialized
	 fully by the rhs of the MODIFY_EXPR.  */
      ବୃକ୍ଷ tem = func_call;
      ଯଦି (CONVERT_ପଦସମଷ୍ଟି_P (tem) && VOID_TYPE_P (ବୃକ୍ଷ_TYPE (tem)))
	{
	  tem = ବୃକ୍ଷ_OPERAND (tem, 0);
	  ଯଦି (ବୃକ୍ଷ_CODE (tem) == MODIFY_ପଦସମଷ୍ଟି
	      && ବୃକ୍ଷ_OPERAND (tem, 0) == tmp
	      && !walk_ବୃକ୍ଷ_without_duplicates (&ବୃକ୍ଷ_OPERAND (tem, 1),
						c_find_var_r, tmp))
	    {
	      ବୃକ୍ଷ_ADDRESSABLE (tmp) = 0;
	      func_call = ବୃକ୍ଷ_OPERAND (tem, 1);
	    }
	}

      /* Return tmp which contains the value loaded.  */
      exp.ମୂଲ୍ୟ = build4 (TARGET_ପଦସମଷ୍ଟି, nonatomic_type, tmp, func_call,
			  NULL_ବୃକ୍ଷ, NULL_ବୃକ୍ଷ);
    }
  ଯଦି (convert_p && !error_operand_p (exp.ମୂଲ୍ୟ)
      && (ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (exp.ମୂଲ୍ୟ)) != ARRAY_TYPE))
    exp.ମୂଲ୍ୟ = convert (build_qualified_type (ବୃକ୍ଷ_TYPE (exp.ମୂଲ୍ୟ), TYPE_UNQUALIFIED), exp.ମୂଲ୍ୟ);
  ଯଦି (force_non_npc)
    exp.ମୂଲ୍ୟ = build1 (NOP_ପଦସମଷ୍ଟି, ବୃକ୍ଷ_TYPE (exp.ମୂଲ୍ୟ), exp.ମୂଲ୍ୟ);

  {
    ବୃକ୍ଷ false_ମୂଲ୍ୟ, true_ମୂଲ୍ୟ;
    ଯଦି (convert_p && !error_operand_p (exp.ମୂଲ୍ୟ)
	&& c_hardbool_type_attr (ବୃକ୍ଷ_TYPE (exp.ମୂଲ୍ୟ),
				 &false_ମୂଲ୍ୟ, &true_ମୂଲ୍ୟ))
      {
	ବୃକ୍ଷ t = save_ପଦସମଷ୍ଟି (exp.ମୂଲ୍ୟ);

	mark_exp_read (exp.ମୂଲ୍ୟ);

	ବୃକ୍ଷ trapfn = builtin_decl_explicit (BUILT_IN_TRAP);
	ବୃକ୍ଷ ପଦସମଷ୍ଟି = build_call_ପଦସମଷ୍ଟି_loc (loc, trapfn, 0);
	ପଦସମଷ୍ଟି = build_compound_ପଦସମଷ୍ଟି (loc, ପଦସମଷ୍ଟି, boolean_true_ଗଣ୍ଠି);
	ପଦସମଷ୍ଟି = fold_build3_loc (loc, COND_ପଦସମଷ୍ଟି, boolean_type_ଗଣ୍ଠି,
				fold_build2_loc (loc, NE_ପଦସମଷ୍ଟି,
						 boolean_type_ଗଣ୍ଠି,
						 t, true_ମୂଲ୍ୟ),
				ପଦସମଷ୍ଟି, boolean_true_ଗଣ୍ଠି);
	ପଦସମଷ୍ଟି = fold_build3_loc (loc, COND_ପଦସମଷ୍ଟି, boolean_type_ଗଣ୍ଠି,
				fold_build2_loc (loc, NE_ପଦସମଷ୍ଟି,
						 boolean_type_ଗଣ୍ଠି,
						 t, false_ମୂଲ୍ୟ),
				ପଦସମଷ୍ଟି, boolean_false_ଗଣ୍ଠି);

	exp.ମୂଲ୍ୟ = ପଦସମଷ୍ଟି;
      }
  }

  ଫେରନ୍ତୁ exp;
}

/* Wrapper for the overload above, same arguments but for tree rather than
   c_expr.  This is important for hardbools to decay to bools.  */

ସ୍ଥିର ଧାଡ଼ିଭିତରେ ବୃକ୍ଷ
convert_lvalue_to_rvalue (location_t loc, ବୃକ୍ଷ val,
			  ତାର୍କିକ convert_p, ତାର୍କିକ read_p, ତାର୍କିକ for_init = ମିଥ୍ୟା)
{
  ସଂରଚନା c_ପଦସମଷ୍ଟି ପଦସମଷ୍ଟି;
  memset (&ପଦସମଷ୍ଟି, 0, ଆକାର (ପଦସମଷ୍ଟି));
  ପଦସମଷ୍ଟି.ମୂଲ୍ୟ = val;
  ପଦସମଷ୍ଟି = convert_lvalue_to_rvalue (loc, ପଦସମଷ୍ଟି, convert_p, read_p, for_init);
  ଫେରନ୍ତୁ ପଦସମଷ୍ଟି.ମୂଲ୍ୟ;
}

/* EXP is an expression of integer type.  Apply the integer promotions
   to it and return the promoted value.  */

ବୃକ୍ଷ
perform_integral_promotions (ବୃକ୍ଷ exp)
{
  ବୃକ୍ଷ type = ବୃକ୍ଷ_TYPE (exp);
  ଗଣନା ବୃକ୍ଷ_code code = ବୃକ୍ଷ_CODE (type);

  gcc_assert (INTEGRAL_TYPE_P (type));

  /* Convert enums to the result of applying the integer promotions to
     their underlying type.  */
  ଯଦି (code == ENUMERAL_TYPE)
    {
      type = ENUM_UNDERLYING_TYPE (type);
      ଯଦି (c_promoting_integer_type_p (type))
	{
	  ଯଦି (TYPE_UNSIGNED (type)
	      && TYPE_PRECISION (type) == TYPE_PRECISION (integer_type_ଗଣ୍ଠି))
	    type = unsigned_type_ଗଣ୍ଠି;
	  ଅନ୍ୟଥା
	    type = integer_type_ଗଣ୍ଠି;
	}

      ଫେରନ୍ତୁ convert (type, exp);
    }

  /* ??? This should no longer be needed now bit-fields have their
     proper types.  */
  ଯଦି (ବୃକ୍ଷ_CODE (exp) == COMPONENT_REF
      && DECL_C_BIT_FIELD (ବୃକ୍ଷ_OPERAND (exp, 1)))
    {
      ଯଦି (BITINT_TYPE_P (DECL_BIT_FIELD_TYPE (ବୃକ୍ଷ_OPERAND (exp, 1))))
	{
	  ବୃକ୍ଷ btype = DECL_BIT_FIELD_TYPE (ବୃକ୍ଷ_OPERAND (exp, 1));
	  ଯଦି (ବୃକ୍ଷ_CODE (btype) == BITINT_TYPE)
	    ଫେରନ୍ତୁ convert (btype, exp);
	  ଅନ୍ୟଥା
	    ଫେରନ୍ତୁ convert (ENUM_UNDERLYING_TYPE (btype), exp);
	}
      /* If it's thinner than an int, promote it like a
	 c_promoting_integer_type_p, otherwise leave it alone.  */
      ଯଦି (compare_ବୃକ୍ଷ_int (DECL_SIZE (ବୃକ୍ଷ_OPERAND (exp, 1)),
			    TYPE_PRECISION (integer_type_ଗଣ୍ଠି)) < 0)
	ଫେରନ୍ତୁ convert (integer_type_ଗଣ୍ଠି, exp);
    }

  ଯଦି (c_promoting_integer_type_p (type))
    {
      /* Preserve unsignedness if not really getting any wider.  */
      ଯଦି (TYPE_UNSIGNED (type)
	  && TYPE_PRECISION (type) == TYPE_PRECISION (integer_type_ଗଣ୍ଠି))
	ଫେରନ୍ତୁ convert (unsigned_type_ଗଣ୍ଠି, exp);

      ଫେରନ୍ତୁ convert (integer_type_ଗଣ୍ଠି, exp);
    }

  ଫେରନ୍ତୁ exp;
}


/* Perform default promotions for C data used in expressions.
   Enumeral types or short or char are converted to int.
   In addition, manifest constants symbols are replaced by their values.  */

ବୃକ୍ଷ
default_conversion (ବୃକ୍ଷ exp)
{
  ବୃକ୍ଷ orig_exp;
  ବୃକ୍ଷ type = ବୃକ୍ଷ_TYPE (exp);
  ଗଣନା ବୃକ୍ଷ_code code = ବୃକ୍ଷ_CODE (type);
  ବୃକ୍ଷ promoted_type;

  mark_exp_read (exp);
  /* We only generate a call to .ACCESS_WITH_SIZE when it is a read.  */
  ଯଦି (ବୃକ୍ଷ_CODE (exp) == COMPONENT_REF
      && handle_counted_by_p (exp))
    exp = handle_counted_by_for_component_ref (ପଦସମଷ୍ଟି_LOCATION (exp), exp);

  /* Functions and arrays have been converted during parsing.  */
  gcc_assert (code != FUNCTION_TYPE);
  ଯଦି (code == ARRAY_TYPE)
    ଫେରନ୍ତୁ exp;

  /* Constants can be used directly unless they're not loadable.  */
  ଯଦି (ବୃକ୍ଷ_CODE (exp) == CONST_DECL)
    exp = DECL_INITIAL (exp);

  /* Strip no-op conversions.  */
  orig_exp = exp;
  STRIP_TYPE_NOPS (exp);

  copy_warning (exp, orig_exp);

  ଯଦି (code == VOID_TYPE)
    {
      error_at (ପଦସମଷ୍ଟି_LOC_OR_LOC (exp, ନିବେଶ_location),
		"void value not ignored as it ought to be");
      ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
    }

  exp = require_complete_type (ପଦସମଷ୍ଟି_LOC_OR_LOC (exp, ନିବେଶ_location), exp);
  ଯଦି (exp == error_mark_ଗଣ୍ଠି)
    ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;

  promoted_type = targetm.promoted_type (type);
  ଯଦି (promoted_type)
    ଫେରନ୍ତୁ convert (promoted_type, exp);

  ଯଦି (INTEGRAL_TYPE_P (type))
    {
      /* Avoid performing integral promotion of bit-precise integer
	 type bit-field to its corresponding bit-precise integer if
	 orig_exp is a cast to it to its underlying type.  */
      ଯଦି (orig_exp != exp
	  && ବୃକ୍ଷ_CODE (exp) == COMPONENT_REF
	  && DECL_C_BIT_FIELD (ବୃକ୍ଷ_OPERAND (exp, 1))
	  && BITINT_TYPE_P (DECL_BIT_FIELD_TYPE (ବୃକ୍ଷ_OPERAND (exp, 1))))
	ଫେରନ୍ତୁ perform_integral_promotions (orig_exp);
      ଫେରନ୍ତୁ perform_integral_promotions (exp);
    }

  ଫେରନ୍ତୁ exp;
}

/* Look up COMPONENT in a structure or union TYPE.

   If the component name is not found, returns NULL_TREE.  Otherwise,
   the return value is a TREE_LIST, with each TREE_VALUE a FIELD_DECL
   stepping down the chain to the component, which is in the last
   TREE_VALUE of the list.  Normally the list is of length one, but if
   the component is embedded within (nested) anonymous structures or
   unions, the list steps down the chain to the component.  */

ବୃକ୍ଷ
lookup_field (const_ବୃକ୍ଷ type, ବୃକ୍ଷ component)
{
  ବୃକ୍ଷ field;

  /* If TYPE_LANG_SPECIFIC is set, then it is a sorted array of pointers
     to the field elements.  Use a binary search on this array to quickly
     find the element.  Otherwise, do a linear search.  TYPE_LANG_SPECIFIC
     will always be set for structures which have many elements.

     Duplicate field checking replaces duplicates with NULL_TREE so
     TYPE_LANG_SPECIFIC arrays are potentially no longer sorted.  In that
     case just iterate using DECL_CHAIN.  */

  ଯଦି (TYPE_LANG_SPECIFIC (type) && TYPE_LANG_SPECIFIC (type)->s
      && !seen_error ())
    {
      ପୂର୍ଣ୍ଣସଂଖ୍ୟା bot, ଶୀର୍ଷ, half;
      ବୃକ୍ଷ *field_array = &TYPE_LANG_SPECIFIC (type)->s->elts[0];

      field = TYPE_FIELDS (type);
      bot = 0;
      ଶୀର୍ଷ = TYPE_LANG_SPECIFIC (type)->s->len;
      ଯେତେବେଳେ (ଶୀର୍ଷ - bot > 1)
	{
	  half = (ଶୀର୍ଷ - bot + 1) >> 1;
	  field = field_array[bot+half];

	  ଯଦି (DECL_NAME (field) == NULL_ବୃକ୍ଷ)
	    {
	      /* Step through all anon unions in linear fashion.  */
	      ଯେତେବେଳେ (DECL_NAME (field_array[bot]) == NULL_ବୃକ୍ଷ)
		{
		  field = field_array[bot++];
		  ଯଦି (RECORD_OR_UNION_TYPE_P (ବୃକ୍ଷ_TYPE (field)))
		    {
		      ବୃକ୍ଷ anon = lookup_field (ବୃକ୍ଷ_TYPE (field), component);

		      ଯଦି (anon)
			ଫେରନ୍ତୁ ବୃକ୍ଷ_cons (NULL_ବୃକ୍ଷ, field, anon);

		      /* The Plan 9 compiler permits referring
			 directly to an anonymous struct/union field
			 using a typedef name.  */
		      ଯଦି (flag_plan9_extensions
			  && TYPE_NAME (ବୃକ୍ଷ_TYPE (field)) != NULL_ବୃକ୍ଷ
			  && (ବୃକ୍ଷ_CODE (TYPE_NAME (ବୃକ୍ଷ_TYPE (field)))
			      == TYPE_DECL)
			  && (DECL_NAME (TYPE_NAME (ବୃକ୍ଷ_TYPE (field)))
			      == component))
			ଭାଙ୍ଗ;
		    }
		}

	      /* Entire record is only anon unions.  */
	      ଯଦି (bot > ଶୀର୍ଷ)
		ଫେରନ୍ତୁ NULL_ବୃକ୍ଷ;

	      /* Restart the binary search, with new lower bound.  */
	      ଜାରି;
	    }

	  ଯଦି (DECL_NAME (field) == component)
	    ଭାଙ୍ଗ;
	  ଯଦି (DECL_NAME (field) < component)
	    bot += half;
	  ଅନ୍ୟଥା
	    ଶୀର୍ଷ = bot + half;
	}

      ଯଦି (DECL_NAME (field_array[bot]) == component)
	field = field_array[bot];
      ଅନ୍ୟଥା ଯଦି (DECL_NAME (field) != component)
	ଫେରନ୍ତୁ NULL_ବୃକ୍ଷ;
    }
  ଅନ୍ୟଥା
    {
      ପାଇଁ (field = TYPE_FIELDS (type); field; field = DECL_CHAIN (field))
	{
	  ଯଦି (DECL_NAME (field) == NULL_ବୃକ୍ଷ
	      && RECORD_OR_UNION_TYPE_P (ବୃକ୍ଷ_TYPE (field)))
	    {
	      ବୃକ୍ଷ anon = lookup_field (ବୃକ୍ଷ_TYPE (field), component);

	      ଯଦି (anon)
		ଫେରନ୍ତୁ ବୃକ୍ଷ_cons (NULL_ବୃକ୍ଷ, field, anon);

	      /* The Plan 9 compiler permits referring directly to an
		 anonymous struct/union field using a typedef
		 name.  */
	      ଯଦି (flag_plan9_extensions
		  && TYPE_NAME (ବୃକ୍ଷ_TYPE (field)) != NULL_ବୃକ୍ଷ
		  && ବୃକ୍ଷ_CODE (TYPE_NAME (ବୃକ୍ଷ_TYPE (field))) == TYPE_DECL
		  && (DECL_NAME (TYPE_NAME (ବୃକ୍ଷ_TYPE (field)))
		      == component))
		ଭାଙ୍ଗ;
	    }

	  ଯଦି (DECL_NAME (field) == component)
	    ଭାଙ୍ଗ;
	}

      ଯଦି (field == NULL_ବୃକ୍ଷ)
	ଫେରନ୍ତୁ NULL_ବୃକ୍ଷ;
    }

  ଫେରନ୍ତୁ ବୃକ୍ଷ_cons (NULL_ବୃକ୍ଷ, field, NULL_ବୃକ୍ଷ);
}

/* Recursively append candidate IDENTIFIER_NODEs to CANDIDATES.  */

ସ୍ଥିର ଶୂନ୍ୟ
lookup_field_fuzzy_find_candidates (ବୃକ୍ଷ type, ବୃକ୍ଷ component,
				    vec<ବୃକ୍ଷ> *candidates)
{
  ବୃକ୍ଷ field;
  ପାଇଁ (field = TYPE_FIELDS (type); field; field = DECL_CHAIN (field))
    {
      ଯଦି (DECL_NAME (field) == NULL_ବୃକ୍ଷ
	  && RECORD_OR_UNION_TYPE_P (ବୃକ୍ଷ_TYPE (field)))
	lookup_field_fuzzy_find_candidates (ବୃକ୍ଷ_TYPE (field), component,
					    candidates);

      ଯଦି (DECL_NAME (field))
	candidates->safe_ଠେଲ (DECL_NAME (field));
    }
}

/* Like "lookup_field", but find the closest matching IDENTIFIER_NODE,
   rather than returning a TREE_LIST for an exact match.  */

ସ୍ଥିର ବୃକ୍ଷ
lookup_field_fuzzy (ବୃକ୍ଷ type, ବୃକ୍ଷ component)
{
  gcc_assert (ବୃକ୍ଷ_CODE (component) == IDENTIFIER_ଗଣ୍ଠି);

  /* First, gather a list of candidates.  */
  auto_vec <ବୃକ୍ଷ> candidates;

  lookup_field_fuzzy_find_candidates (type, component,
				      &candidates);

  ଫେରନ୍ତୁ find_closest_identifier (component, &candidates);
}

/* Support function for build_component_ref's error-handling.

   Given DATUM_TYPE, and "DATUM.COMPONENT", where DATUM is *not* a
   struct or union, should we suggest "DATUM->COMPONENT" as a hint?  */

ସ୍ଥିର ତାର୍କିକ
should_suggest_deref_p (ବୃକ୍ଷ datum_type)
{
  /* We don't do it for Objective-C, since Objective-C 2.0 dot-syntax
     allows "." for ptrs; we could be handling a failed attempt
     to access a property.  */
  ଯଦି (c_dialect_objc ())
    ଫେରନ୍ତୁ ମିଥ୍ୟା;

  /* Only suggest it for pointers...  */
  ଯଦି (ବୃକ୍ଷ_CODE (datum_type) != POINTER_TYPE)
    ଫେରନ୍ତୁ ମିଥ୍ୟା;

  /* ...to structs/unions.  */
  ବୃକ୍ଷ underlying_type = ବୃକ୍ଷ_TYPE (datum_type);
  ଗଣନା ବୃକ୍ଷ_code code = ବୃକ୍ଷ_CODE (underlying_type);
  ଯଦି (code == RECORD_TYPE || code == UNION_TYPE)
    ଫେରନ୍ତୁ ସତ୍ୟ;
  ଅନ୍ୟଥା
    ଫେରନ୍ତୁ ମିଥ୍ୟା;
}

/* Give a component ref REF, decide whether we should handle its counted_by
   attribute based on its context:
   Do not handle counted_by when in offsetof, typeof and alignof operator.  */

ସ୍ଥିର ତାର୍କିକ
handle_counted_by_p (ବୃକ୍ଷ ref)
{
  gcc_assert (ବୃକ୍ଷ_CODE (ref) == COMPONENT_REF);
  ବୃକ୍ଷ datum = ବୃକ୍ଷ_OPERAND (ref, 0);
  /* If the component_ref is build for a offsetof, i.e., the datum
     of the component_ref is a indirect_ref of null_pointer_node,
     we should not generate call to .ACCESS_WITH_SIZE.  */
  ଯଦି (ବୃକ୍ଷ_CODE (datum) == INDIRECT_REF
      && ବୃକ୍ଷ_OPERAND (datum, 0) == null_pointer_ଗଣ୍ଠି)
    ଫେରନ୍ତୁ ମିଥ୍ୟା;
  ଯଦି (in_typeof || in_alignof)
    ଫେରନ୍ତୁ ମିଥ୍ୟା;
  ଫେରନ୍ତୁ ସତ୍ୟ;
}

/* Given a component ref REF, if there is a counted_by attribute attached,
   issue error when the element_type is a structure or union including a
   flexible array member.  */

ସ୍ଥିର ଶୂନ୍ୟ
check_counted_by_attribute (location_t loc, ବୃକ୍ଷ ref)
{
  ବୃକ୍ଷ subdatum = ବୃକ୍ଷ_OPERAND (ref, 1);
  ବୃକ୍ଷ sub_type = ବୃକ୍ଷ_TYPE (subdatum);

  ଯଦି (!flexible_array_member_type_p (sub_type)
      && ବୃକ୍ଷ_CODE (sub_type) != POINTER_TYPE)
    ଫେରନ୍ତୁ;

  ବୃକ୍ଷ element_type = ବୃକ୍ଷ_TYPE (sub_type);

  ବୃକ୍ଷ attr_counted_by = lookup_attribute ("counted_by",
					   DECL_ATTRIBUTES (subdatum));
  ଯଦି (attr_counted_by)
    {
      /* Issue error when the element_type is a structure or
	union including a flexible array member.  */
      ଯଦି (RECORD_OR_UNION_TYPE_P (element_type)
	  && TYPE_INCLUDES_FLEXARRAY (element_type))
	{
	  error_at (loc,
		    "%<counted_by%> attribute is not allowed for a pointer to"
		    " structure or union with flexible array member");
	  ଫେରନ୍ତୁ;
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

ସ୍ଥିର ବୃକ୍ଷ
build_counted_by_ref (ବୃକ୍ଷ datum, ବୃକ୍ଷ subdatum,
		      ବୃକ୍ଷ *counted_by_type)
{
  ବୃକ୍ଷ sub_type = ବୃକ୍ଷ_TYPE (subdatum);
  ଯଦି (!flexible_array_member_type_p (sub_type)
      && ବୃକ୍ଷ_CODE (sub_type) != POINTER_TYPE)
    ଫେରନ୍ତୁ NULL_ବୃକ୍ଷ;

  ବୃକ୍ଷ attr_counted_by = lookup_attribute ("counted_by",
					   DECL_ATTRIBUTES (subdatum));
  ଯଦି (!attr_counted_by)
    ଫେରନ୍ତୁ NULL_ବୃକ୍ଷ;

  ବୃକ୍ଷ counted_by_ref = NULL_ବୃକ୍ଷ;
  *counted_by_type = NULL_ବୃକ୍ଷ;

  ବୃକ୍ଷ type = ବୃକ୍ଷ_TYPE (datum);

  /* If the type of the containing structure is an anonymous struct/union,
     and this anonymous struct/union is not a root type, get the first
     outer named structure/union type.  */
  ଯେତେବେଳେ (ବୃକ୍ଷ_CODE (datum) == COMPONENT_REF
	 && c_type_tag (type) == NULL_ବୃକ୍ଷ
	 && DECL_NAME (ବୃକ୍ଷ_OPERAND (datum, 1)) == NULL_ବୃକ୍ଷ)
    {
      datum = ବୃକ୍ଷ_OPERAND (datum, 0);
      type = ବୃକ୍ଷ_TYPE (datum);
    }

  ବୃକ୍ଷ field_id = ବୃକ୍ଷ_ମୂଲ୍ୟ (ବୃକ୍ଷ_ମୂଲ୍ୟ (attr_counted_by));
  ବୃକ୍ଷ counted_by_field = lookup_field (type, field_id);
  gcc_assert (counted_by_field);

  ବୃକ୍ଷ counted_by_subdatum;
  କର
    {
      counted_by_subdatum = ବୃକ୍ଷ_ମୂଲ୍ୟ (counted_by_field);
      /* Get the TYPE of the counted_by field.  */
      *counted_by_type = ବୃକ୍ଷ_TYPE (counted_by_subdatum);

      counted_by_ref
	= build3 (COMPONENT_REF, ବୃକ୍ଷ_TYPE (counted_by_subdatum),
		  datum, counted_by_subdatum, NULL_ବୃକ୍ଷ);

      datum = counted_by_ref;
      counted_by_field = ବୃକ୍ଷ_CHAIN (counted_by_field);
    }
  ଯେତେବେଳେ (counted_by_field);

  counted_by_ref = build_fold_addr_ପଦସମଷ୍ଟି (counted_by_ref);
  ଫେରନ୍ତୁ counted_by_ref;
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
ସ୍ଥିର ବୃକ୍ଷ
build_access_with_size_for_counted_by (location_t loc, ବୃକ୍ଷ ref,
				       ବୃକ୍ଷ counted_by_ref,
				       ବୃକ୍ଷ counted_by_type)
{
  gcc_assert (flexible_array_member_type_p (ବୃକ୍ଷ_TYPE (ref))
	      || ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (ref)) == POINTER_TYPE);

  ତାର୍କିକ is_fam = flexible_array_member_type_p (ବୃକ୍ଷ_TYPE (ref));

  /* The result type of the call is a pointer to the flexible array type;
     or is the original pointer type to the pointer field with counted_by.  */
  ବୃକ୍ଷ result_type = is_fam ? c_build_pointer_type (ବୃକ୍ଷ_TYPE (ref))
		     : ବୃକ୍ଷ_TYPE (ref);

  ବୃକ୍ଷ element_type = ବୃକ୍ଷ_TYPE (ବୃକ୍ଷ_TYPE (ref));
  ବୃକ୍ଷ element_size = VOID_TYPE_P (element_type)
		      ? size_one_ଗଣ୍ଠି
		      : TYPE_SIZE_UNIT (element_type);
  ଯଦି (element_size == NULL_ବୃକ୍ଷ)
    ଫେରନ୍ତୁ ref;

  ବୃକ୍ଷ first_param = is_fam
		     ? c_fully_fold (array_to_pointer_conversion (loc, ref),
				     ମିଥ୍ୟା, ଖାଲି)
		     : c_fully_fold (ref, ମିଥ୍ୟା, ଖାଲି);
  ବୃକ୍ଷ second_param
    = c_fully_fold (counted_by_ref, ମିଥ୍ୟା, ଖାଲି);
  ବୃକ୍ଷ third_param = build_int_cst (c_build_pointer_type (counted_by_type), 0);

  ବୃକ୍ଷ call
    = build_call_ପଦସମଷ୍ଟି_internal_loc (loc, IFN_ACCESS_WITH_SIZE,
				    result_type, 4,
				    first_param,
				    second_param,
				    third_param,
				    element_size);

  /* Wrap the call with an INDIRECT_REF with the flexible array type.  */
  ଯଦି (is_fam)
    call = build1 (INDIRECT_REF, ବୃକ୍ଷ_TYPE (ref), call);
  SET_ପଦସମଷ୍ଟି_LOCATION (call, loc);
  ଫେରନ୍ତୁ call;
}

/* For the COMPONENT_REF ref, check whether it has a counted_by attribute,
   if so, wrap this COMPONENT_REF with the corresponding CALL to the
   function .ACCESS_WITH_SIZE.
   Otherwise, return the ref itself.  */

ବୃକ୍ଷ
handle_counted_by_for_component_ref (location_t loc, ବୃକ୍ଷ ref)
{
  gcc_assert (ବୃକ୍ଷ_CODE (ref) == COMPONENT_REF);
  ବୃକ୍ଷ datum = ବୃକ୍ଷ_OPERAND (ref, 0);
  ବୃକ୍ଷ subdatum = ବୃକ୍ଷ_OPERAND (ref, 1);
  ବୃକ୍ଷ counted_by_type = NULL_ବୃକ୍ଷ;

  ଯଦି (!(flexible_array_member_type_p (ବୃକ୍ଷ_TYPE (ref))
	|| ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (ref)) == POINTER_TYPE))
    ଫେରନ୍ତୁ ref;

  ବୃକ୍ଷ counted_by_ref = build_counted_by_ref (datum, subdatum,
					      &counted_by_type);
  ଯଦି (counted_by_ref)
    ref = build_access_with_size_for_counted_by (loc, ref,
						 counted_by_ref,
						 counted_by_type);
  ଫେରନ୍ତୁ ref;
}

/* Make an expression to refer to the COMPONENT field of structure or
   union value DATUM.  COMPONENT is an IDENTIFIER_NODE.  LOC is the
   location of the COMPONENT_REF.  COMPONENT_LOC is the location
   of COMPONENT.  ARROW_LOC is the location of the first -> operand if
   it is from -> operator.
   If HANDLE_COUNTED_BY is true, check the counted_by attribute and generate
   a call to .ACCESS_WITH_SIZE.  Otherwise, ignore the attribute.  */

ବୃକ୍ଷ
build_component_ref (location_t loc, ବୃକ୍ଷ datum, ବୃକ୍ଷ component,
		     location_t component_loc, location_t arrow_loc)
{
  ବୃକ୍ଷ type = ବୃକ୍ଷ_TYPE (datum);
  ଗଣନା ବୃକ୍ଷ_code code = ବୃକ୍ଷ_CODE (type);
  ବୃକ୍ଷ field = ଖାଲି;
  ବୃକ୍ଷ ref;
  ତାର୍କିକ datum_lvalue = lvalue_p (datum);

  ଯଦି (!objc_is_public (datum, component))
    ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;

  /* Detect Objective-C property syntax object.property.  */
  ଯଦି (c_dialect_objc ()
      && (ref = objc_maybe_build_component_ref (datum, component)))
    ଫେରନ୍ତୁ ref;

  /* See if there is a field or component with name COMPONENT.  */

  ଯଦି (code == RECORD_TYPE || code == UNION_TYPE)
    {
      ଯଦି (!COMPLETE_TYPE_P (type))
	{
	  c_incomplete_type_error (loc, NULL_ବୃକ୍ଷ, type);
	  ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
	}

      field = lookup_field (type, component);

      ଯଦି (!field)
	{
	  ବୃକ୍ଷ guessed_id = lookup_field_fuzzy (type, component);
	  ଯଦି (guessed_id)
	    {
	      /* Attempt to provide a fixit replacement hint, if
		 we have a valid range for the component.  */
	      location_t reported_loc
		= (component_loc != UNKNOWN_LOCATION) ? component_loc : loc;
	      gcc_rich_location rich_loc (reported_loc);
	      ଯଦି (component_loc != UNKNOWN_LOCATION)
		rich_loc.add_fixit_misspelled_id (component_loc, guessed_id);
	      error_at (&rich_loc,
			"%qT has no member named %qE; did you mean %qE?",
			type, component, guessed_id);
	    }
	  ଅନ୍ୟଥା
	    error_at (loc, "%qT has no member named %qE", type, component);
	  ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
	}

      /* Accessing elements of atomic structures or unions is undefined
	 behavior (C11 6.5.2.3#5).  */
      ଯଦି (TYPE_ATOMIC (type) && c_inhibit_evaluation_warnings == 0)
	{
	  ଯଦି (code == RECORD_TYPE)
	    warning_at (loc, 0, "accessing a member %qE of an atomic "
			"structure %qE", component, datum);
	  ଅନ୍ୟଥା
	    warning_at (loc, 0, "accessing a member %qE of an atomic "
			"union %qE", component, datum);
	}

      /* Chain the COMPONENT_REFs if necessary down to the FIELD.
	 This might be better solved in future the way the C++ front
	 end does it - by giving the anonymous entities each a
	 separate name and type, and then have build_component_ref
	 recursively call itself.  We can't do that here.  */
      କର
	{
	  ବୃକ୍ଷ subdatum = ବୃକ୍ଷ_ମୂଲ୍ୟ (field);
	  ପୂର୍ଣ୍ଣସଂଖ୍ୟା quals;
	  ବୃକ୍ଷ subtype;
	  ତାର୍କିକ use_datum_quals;

	  ଯଦି (ବୃକ୍ଷ_TYPE (subdatum) == error_mark_ଗଣ୍ଠି)
	    ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;

	  /* If this is an rvalue, it does not have qualifiers in C
	     standard terms and we must avoid propagating such
	     qualifiers down to a non-lvalue array that is then
	     converted to a pointer.  */
	  use_datum_quals = (datum_lvalue
			     || ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (subdatum)) != ARRAY_TYPE);

	  quals = TYPE_QUALS (strip_array_types (ବୃକ୍ଷ_TYPE (subdatum)));
	  ଯଦି (use_datum_quals)
	    quals |= TYPE_QUALS (ବୃକ୍ଷ_TYPE (datum));
	  subtype = c_build_qualified_type (ବୃକ୍ଷ_TYPE (subdatum), quals);

	  ref = build3 (COMPONENT_REF, subtype, datum, subdatum,
			NULL_ବୃକ୍ଷ);
	  SET_ପଦସମଷ୍ଟି_LOCATION (ref, loc);

	  check_counted_by_attribute (loc, ref);

	  ଯଦି (ବୃକ୍ଷ_READONLY (subdatum)
	      || (use_datum_quals && ବୃକ୍ଷ_READONLY (datum)))
	    ବୃକ୍ଷ_READONLY (ref) = 1;
	  ଯଦି (ବୃକ୍ଷ_THIS_VOLATILE (subdatum)
	      || (use_datum_quals && ବୃକ୍ଷ_THIS_VOLATILE (datum)))
	    ବୃକ୍ଷ_THIS_VOLATILE (ref) = 1;

	  ଯଦି (ବୃକ୍ଷ_UNAVAILABLE (subdatum))
	    error_unavailable_use (subdatum, NULL_ବୃକ୍ଷ);
	  ଅନ୍ୟଥା ଯଦି (ବୃକ୍ଷ_DEPRECATED (subdatum))
	    warn_deprecated_use (subdatum, NULL_ବୃକ୍ଷ);

	  datum = ref;

	  field = ବୃକ୍ଷ_CHAIN (field);
	}
      ଯେତେବେଳେ (field);

      ଫେରନ୍ତୁ ref;
    }
  ଅନ୍ୟଥା ଯଦି (should_suggest_deref_p (type))
    {
      /* Special-case the error message for "ptr.field" for the case
	 where the user has confused "." vs "->".  */
      rich_location richloc (ଧାଡ଼ି_table, loc);
      ଯଦି (INDIRECT_REF_P (datum) && arrow_loc != UNKNOWN_LOCATION)
	{
	  richloc.add_fixit_ଭର୍ତ୍ତି_before (arrow_loc, "(*");
	  richloc.add_fixit_ଭର୍ତ୍ତି_after (arrow_loc, ")");
	  error_at (&richloc,
		    "%qE is a pointer to pointer; did you mean to dereference "
		    "it before applying %<->%> to it?",
		    ବୃକ୍ଷ_OPERAND (datum, 0));
	}
      ଅନ୍ୟଥା
	{
	  /* "loc" should be the "." token.  */
	  richloc.add_fixit_replace ("->");
	  error_at (&richloc,
		    "%qE is a pointer; did you mean to use %<->%>?",
		    datum);
	}
      ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
    }
  ଅନ୍ୟଥା ଯଦି (code != ERROR_MARK)
    error_at (loc,
	      "request for member %qE in something not a structure or union",
	      component);

  ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
}

/* Given an expression PTR for a pointer, return an expression
   for the value pointed to.
   ERRORSTRING is the name of the operator to appear in error messages.

   LOC is the location to use for the generated tree.  */

ବୃକ୍ଷ
build_indirect_ref (location_t loc, ବୃକ୍ଷ ptr, ref_operator errstring)
{
  ବୃକ୍ଷ pointer = default_conversion (ptr);
  ବୃକ୍ଷ type = ବୃକ୍ଷ_TYPE (pointer);
  ବୃକ୍ଷ ref;

  ଯଦି (ବୃକ୍ଷ_CODE (type) == POINTER_TYPE)
    {
      ଯଦି (CONVERT_ପଦସମଷ୍ଟି_P (pointer)
          || ବୃକ୍ଷ_CODE (pointer) == VIEW_CONVERT_ପଦସମଷ୍ଟି)
	{
	  /* If a warning is issued, mark it to avoid duplicates from
	     the backend.  This only needs to be done at
	     warn_strict_aliasing > 2.  */
	  ଯଦି (warn_strict_aliasing > 2)
	    ଯଦି (strict_aliasing_warning (ପଦସମଷ୍ଟି_LOCATION (pointer),
					 type, ବୃକ୍ଷ_OPERAND (pointer, 0)))
	      suppress_warning (pointer, OPT_Wstrict_aliasing_);
	}

      ଯଦି (ବୃକ୍ଷ_CODE (pointer) == ADDR_ପଦସମଷ୍ଟି
	  && (ବୃକ୍ଷ_TYPE (ବୃକ୍ଷ_OPERAND (pointer, 0))
	      == ବୃକ୍ଷ_TYPE (type)))
	{
	  ref = ବୃକ୍ଷ_OPERAND (pointer, 0);
	  protected_set_ପଦସମଷ୍ଟି_location (ref, loc);
	  ଫେରନ୍ତୁ ref;
	}
      ଅନ୍ୟଥା
	{
	  ବୃକ୍ଷ t = ବୃକ୍ଷ_TYPE (type);

	  ref = build1 (INDIRECT_REF, t, pointer);

	  ଯଦି (VOID_TYPE_P (t) && c_inhibit_evaluation_warnings == 0)
	    warning_at (loc, 0, "dereferencing %<void *%> pointer");

	  /* We *must* set TREE_READONLY when dereferencing a pointer to const,
	     so that we get the proper error message if the result is used
	     to assign to.  Also, &* is supposed to be a no-op.
	     And ANSI C seems to specify that the type of the result
	     should be the const type.  */
	  /* A de-reference of a pointer to const is not a const.  It is valid
	     to change it via some other pointer.  */
	  ବୃକ୍ଷ_READONLY (ref) = TYPE_READONLY (t);
	  ବୃକ୍ଷ_SIDE_EFFECTS (ref)
	    = TYPE_VOLATILE (t) || ବୃକ୍ଷ_SIDE_EFFECTS (pointer);
	  ବୃକ୍ଷ_THIS_VOLATILE (ref) = TYPE_VOLATILE (t);
	  protected_set_ପଦସମଷ୍ଟି_location (ref, loc);
	  ଫେରନ୍ତୁ ref;
	}
    }
  ଅନ୍ୟଥା ଯଦି (ବୃକ୍ଷ_CODE (pointer) != ERROR_MARK)
    invalid_indirection_error (loc, type, errstring);

  ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
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

ବୃକ୍ଷ
build_array_ref (location_t loc, ବୃକ୍ଷ array, ବୃକ୍ଷ index)
{
  ବୃକ୍ଷ ret;
  ତାର୍କିକ swapped = ମିଥ୍ୟା;
  ଯଦି (ବୃକ୍ଷ_TYPE (array) == error_mark_ଗଣ୍ଠି
      || ବୃକ୍ଷ_TYPE (index) == error_mark_ଗଣ୍ଠି)
    ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;

  ଯଦି (ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (array)) != ARRAY_TYPE
      && ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (array)) != POINTER_TYPE
      /* Allow vector[index] but not index[vector].  */
      && !gnu_vector_type_p (ବୃକ୍ଷ_TYPE (array)))
    {
      ଯଦି (ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (index)) != ARRAY_TYPE
	  && ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (index)) != POINTER_TYPE)
	{
          error_at (loc,
            "subscripted value is neither array nor pointer nor vector");

	  ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
	}
      std::swap (array, index);
      swapped = ସତ୍ୟ;
    }

  ଯଦି (!INTEGRAL_TYPE_P (ବୃକ୍ଷ_TYPE (index)))
    {
      error_at (loc, "array subscript is not an integer");
      ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
    }

  ଯଦି (ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (ବୃକ୍ଷ_TYPE (array))) == FUNCTION_TYPE)
    {
      error_at (loc, "subscripted value is pointer to function");
      ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
    }

  /* ??? Existing practice has been to warn only when the char
     index is syntactically the index, not for char[array].  */
  ଯଦି (!swapped)
     warn_array_subscript_with_type_char (loc, index);

  /* Apply default promotions *after* noticing character types.  */
  index = default_conversion (index);
  ଯଦି (index == error_mark_ଗଣ୍ଠି)
    ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;

  gcc_assert (ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (index)) == INTEGER_TYPE
	      || ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (index)) == BITINT_TYPE);

  ତାର୍କିକ was_vector = VECTOR_TYPE_P (ବୃକ୍ଷ_TYPE (array));
  ତାର୍କିକ non_lvalue = convert_vector_to_array_for_subscript (loc, &array, index);

  /* We only generate a call to .ACCESS_WITH_SIZE when it is a read.  */
  ଯଦି (ବୃକ୍ଷ_CODE (array) == COMPONENT_REF
      && handle_counted_by_p (array))
    array = handle_counted_by_for_component_ref (loc, array);

  ଯଦି (ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (array)) == ARRAY_TYPE)
    {
      ବୃକ୍ଷ rval, type;

      /* An array that is indexed by a non-constant
	 cannot be stored in a register; we must be able to do
	 address arithmetic on its address.
	 Likewise an array of elements of variable size.  */
      ଯଦି (ବୃକ୍ଷ_CODE (index) != INTEGER_CST
	  || (COMPLETE_TYPE_P (ବୃକ୍ଷ_TYPE (ବୃକ୍ଷ_TYPE (array)))
	      && ବୃକ୍ଷ_CODE (TYPE_SIZE (ବୃକ୍ଷ_TYPE (ବୃକ୍ଷ_TYPE (array)))) != INTEGER_CST))
	{
	  ଯଦି (!c_mark_addressable (array, ସତ୍ୟ, ସତ୍ୟ))
	    ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
	}
      /* An array that is indexed by a constant value which is not within
	 the array bounds cannot be stored in a register either; because we
	 would get a crash in store_bit_field/extract_bit_field when trying
	 to access a non-existent part of the register.  */
      ଯଦି (ବୃକ୍ଷ_CODE (index) == INTEGER_CST
	  && TYPE_DOMAIN (ବୃକ୍ଷ_TYPE (array))
	  && !int_fits_type_p (index, TYPE_DOMAIN (ବୃକ୍ଷ_TYPE (array))))
	{
	  ଯଦି (!c_mark_addressable (array, ମିଥ୍ୟା, ସତ୍ୟ))
	    ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
	  /* ISO C2Y disallows a negative integer constant expression index
	     when array subscripting has an operand of array type.  */
	  ଯଦି (flag_isoc2y
	      && !ବୃକ୍ଷ_OVERFLOW (index)
	      && ବୃକ୍ଷ_int_cst_sgn (index) < 0)
	    error_at (loc, "array subscript is negative");
	}

      ଯଦି ((pedantic || warn_c90_c99_compat || warn_c23_c2y_compat)
	  && ! was_vector)
	{
	  ବୃକ୍ଷ foo = array;
	  ଯେତେବେଳେ (ବୃକ୍ଷ_CODE (foo) == COMPONENT_REF)
	    foo = ବୃକ୍ଷ_OPERAND (foo, 0);
	  ଯଦି ((VAR_P (foo) && C_DECL_REGISTER (foo))
	      || (ବୃକ୍ଷ_CODE (foo) == COMPOUND_LITERAL_ପଦସମଷ୍ଟି
		  && C_DECL_REGISTER (COMPOUND_LITERAL_ପଦସମଷ୍ଟି_DECL (foo))))
	    pedwarn_c23 (loc, OPT_Wpedantic,
			 "ISO C forbids subscripting %<register%> array "
			 "before C2Y");
	  ଅନ୍ୟଥା ଯଦି (!lvalue_p (foo))
	    pedwarn_c90 (loc, OPT_Wpedantic,
			 "ISO C90 forbids subscripting non-lvalue "
			 "array");
	}

      ଯଦି (ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (index)) == BITINT_TYPE
	  && TYPE_PRECISION (ବୃକ୍ଷ_TYPE (index)) > TYPE_PRECISION (sizetype))
	index = fold_convert (sizetype, index);

      type = ବୃକ୍ଷ_TYPE (ବୃକ୍ଷ_TYPE (array));
      rval = build4 (ARRAY_REF, type, array, index, NULL_ବୃକ୍ଷ, NULL_ବୃକ୍ଷ);
      /* Array ref is const/volatile if the array elements are
	 or if the array is.  */
      ବୃକ୍ଷ_READONLY (rval)
	|= (TYPE_READONLY (ବୃକ୍ଷ_TYPE (ବୃକ୍ଷ_TYPE (array)))
	    | ବୃକ୍ଷ_READONLY (array));
      ବୃକ୍ଷ_SIDE_EFFECTS (rval)
	|= (TYPE_VOLATILE (ବୃକ୍ଷ_TYPE (ବୃକ୍ଷ_TYPE (array)))
	    | ବୃକ୍ଷ_SIDE_EFFECTS (array));
      ବୃକ୍ଷ_THIS_VOLATILE (rval)
	|= (TYPE_VOLATILE (ବୃକ୍ଷ_TYPE (ବୃକ୍ଷ_TYPE (array)))
	    /* This was added by rms on 16 Nov 91.
	       It fixes  vol struct foo *a;  a->elts[1]
	       in an inline function.
	       Hope it doesn't break something else.  */
	    | ବୃକ୍ଷ_THIS_VOLATILE (array));
      ret = require_complete_type (loc, rval);
      protected_set_ପଦସମଷ୍ଟି_location (ret, loc);
      ଯଦି (non_lvalue)
	ret = non_lvalue_loc (loc, ret);
      ଫେରନ୍ତୁ ret;
    }
  ଅନ୍ୟଥା
    {
      ବୃକ୍ଷ ar = default_conversion (array);

      ଯଦି (ar == error_mark_ଗଣ୍ଠି)
	ଫେରନ୍ତୁ ar;

      gcc_assert (ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (ar)) == POINTER_TYPE);
      gcc_assert (ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (ବୃକ୍ଷ_TYPE (ar))) != FUNCTION_TYPE);

      ret = build_indirect_ref (loc, build_ଦ୍ୱିମିକ_op (loc, PLUS_ପଦସମଷ୍ଟି, ar,
						      index, ମିଥ୍ୟା),
				RO_ARRAY_INDEXING);
      ଯଦି (non_lvalue)
	ret = non_lvalue_loc (loc, ret);
      ଫେରନ୍ତୁ ret;
    }
}

/* Build an OpenMP array section reference, creating an exact type for the
   resulting expression based on the element type and bounds if possible.  If
   we have variable bounds, create an incomplete array type for the result
   instead.  */

ବୃକ୍ଷ
build_omp_array_section (location_t loc, ବୃକ୍ଷ array, ବୃକ୍ଷ index, ବୃକ୍ଷ length)
{
  ବୃକ୍ଷ type = ବୃକ୍ଷ_TYPE (array);
  gcc_assert (type);

  ବୃକ୍ଷ sectype, eltype = ବୃକ୍ଷ_TYPE (type);

  /* It's not an array or pointer type.  Just reuse the type of the original
     expression as the type of the array section (an error will be raised
     anyway, later).  */
  ଯଦି (eltype == NULL_ବୃକ୍ଷ || error_operand_p (eltype))
    sectype = ବୃକ୍ଷ_TYPE (array);
  ଅନ୍ୟଥା
    {
      ବୃକ୍ଷ idxtype = NULL_ବୃକ୍ଷ;

      ଯଦି (index != NULL_ବୃକ୍ଷ
	  && length != NULL_ବୃକ୍ଷ
	  && INTEGRAL_TYPE_P (ବୃକ୍ଷ_TYPE (index))
	  && INTEGRAL_TYPE_P (ବୃକ୍ଷ_TYPE (length)))
	{
	  ବୃକ୍ଷ ତଳ = fold_convert (sizetype, index);
	  ବୃକ୍ଷ ଉପର = fold_convert (sizetype, length);
	  ଉପର = size_binop (PLUS_ପଦସମଷ୍ଟି, ତଳ, ଉପର);
	  ଉପର = size_binop (MINUS_ପଦସମଷ୍ଟି, ଉପର, size_one_ଗଣ୍ଠି);
	  idxtype = build_range_type (sizetype, ତଳ, ଉପର);
	}
      ଅନ୍ୟଥା ଯଦି ((index == NULL_ବୃକ୍ଷ || integer_zerop (index))
	       && length != NULL_ବୃକ୍ଷ
	       && INTEGRAL_TYPE_P (ବୃକ୍ଷ_TYPE (length)))
	idxtype = build_index_type (length);

      gcc_assert (!error_operand_p (idxtype));

      sectype = c_build_array_type (eltype, idxtype);
    }

  ଫେରନ୍ତୁ build3_loc (loc, OMP_ARRAY_SECTION, sectype, array, index, length);
}


/* Record that REF is used.  This is relevant for undeclared static
   function and declarations referenced from a non-local context.
   ADDRESS indicates whether the address is taken.  */

ଶୂନ୍ୟ
mark_decl_used (ବୃକ୍ଷ ref, ତାର୍କିକ address)
{
  ଯଦି (!ref || !DECL_P (ref) || in_alignof)
    ଫେରନ୍ତୁ;

  /* Non-file-scope and non-local reference in nested function.  */
  ତାର୍କିକ nonloc_p = current_function_decl && DECL_CONTEXT (ref)
		  && DECL_CONTEXT (current_function_decl)
		  && DECL_CONTEXT (ref) != current_function_decl;

  /* An undeclared static function.  */
  ତାର୍କିକ static_p = ବୃକ୍ଷ_CODE (ref) == FUNCTION_DECL
		  && DECL_INITIAL (ref) == NULL_ବୃକ୍ଷ
		  && DECL_EXTERNAL (ref)
		  && !ବୃକ୍ଷ_PUBLIC (ref);

  ଯଦି (!static_p && !nonloc_p)
    ଫେରନ୍ତୁ;

  /* If we may be in an unevaluated context, delay the decision.  */
  ଯଦି (in_sizeof || in_typeof || in_countof || in_generic)
    ଫେରନ୍ତୁ record_maybe_used_decl (ref, address);

  ଯଦି (static_p)
    C_DECL_USED (ref) = 1;

  ଯଦି (nonloc_p && (VAR_OR_FUNCTION_DECL_P (ref)
		   || ବୃକ୍ଷ_CODE (ref) == PARM_DECL))
    DECL_NONLOCAL (ref) = 1;

  /* Nothing to do anymore.  */
  ଯଦି (!nonloc_p || C_FUNC_NONLOCAL_CONTEXT (current_function_decl))
    ଫେରନ୍ତୁ;

  /* Filter out the cases where referencing a non-local variable does not
     require a non-local context passed via the static chain.  */
  ଯଦି (!c_type_variably_modified_p (ବୃକ୍ଷ_TYPE (ref)))
    ବାଛ (ବୃକ୍ଷ_CODE (ref))
      {
      ସ୍ଥିତି FUNCTION_DECL:
	/* Use of another local function that requires no context is ok.  */
	ଯଦି (!C_FUNC_NONLOCAL_CONTEXT (ref) && DECL_INITIAL (ref))
	  ଫେରନ୍ତୁ;
	ଭାଙ୍ଗ;
      ସ୍ଥିତି VAR_DECL:
	/* Static variables and constexpr are ok, but for the later only
	   when the address is not taken.  */
	ଯଦି (ବୃକ୍ଷ_STATIC (ref) || (C_DECL_DECLARED_CONSTEXPR (ref) && !address))
	  ଫେରନ୍ତୁ;
	ଭାଙ୍ଗ;
      ସ୍ଥିତି TYPE_DECL:
	/* A typedef is ok when not for a variably-modified type. */
	ଫେରନ୍ତୁ;
      ସ୍ଥିତି CONST_DECL:
	/* An enumeration constant is ok. */
	ଫେରନ୍ତୁ;
      ସ୍ଥିତି PARM_DECL:
	ଭାଙ୍ଗ;
      ସ୍ଥିତି LABEL_DECL:
	ଭାଙ୍ଗ;
      ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
	gcc_unreachable ();
    }

  /* Mark all parent functions up to the nesting level of the variable as
     as needing the non-local context.  */
  ପାଇଁ (ବୃକ୍ଷ cont = current_function_decl; cont; cont = DECL_CONTEXT (cont))
    {
      ଯଦି (cont == DECL_CONTEXT (ref))
	ଭାଙ୍ଗ;

      /* There should not be any other type of context used for function
	 except TRANSLATION_UNIT_DECL which we should be able to reach.  */
      gcc_checking_assert (ବୃକ୍ଷ_CODE (cont) == FUNCTION_DECL);

      ଯଦି (ବୃକ୍ଷ_CODE (cont) == FUNCTION_DECL)
	C_FUNC_NONLOCAL_CONTEXT (cont) = 1;
    }
}


/* Build an external reference to identifier ID.  FUN indicates
   whether this will be used for a function call.  LOC is the source
   location of the identifier.  This sets *TYPE to the type of the
   identifier, which is not the same as the type of the returned value
   for CONST_DECLs defined as enum constants.  If the type of the
   identifier is not available, *TYPE is set to NULL.  */
ବୃକ୍ଷ
build_external_ref (location_t loc, ବୃକ୍ଷ id, ତାର୍କିକ fun, ବୃକ୍ଷ *type)
{
  ବୃକ୍ଷ ref;
  ବୃକ୍ଷ decl = lookup_name (id);

  /* In Objective-C, an instance variable (ivar) may be preferred to
     whatever lookup_name() found.  */
  decl = objc_lookup_ivar (decl, id);

  *type = ଖାଲି;
  ଯଦି (decl && decl != error_mark_ଗଣ୍ଠି)
    {
      ref = decl;
      *type = ବୃକ୍ଷ_TYPE (ref);
      ଯଦି (DECL_P (decl) && C_DECL_UNDERSPECIFIED (decl))
	error_at (loc, "underspecified %qD referenced in its initializer",
		  decl);
    }
  ଅନ୍ୟଥା ଯଦି (fun)
    /* Implicit function declaration.  */
    ref = implicitly_declare (loc, id);
  ଅନ୍ୟଥା ଯଦି (decl == error_mark_ଗଣ୍ଠି)
    /* Don't complain about something that's already been
       complained about.  */
    ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
  ଅନ୍ୟଥା
    {
      undeclared_variable (loc, id);
      ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
    }

  /* For an OpenMP map clause, we can get better diagnostics for decls with
     unmappable types if we return the decl with an error_mark_node type,
     rather than returning error_mark_node for the decl itself.  */
  ଯଦି (ବୃକ୍ଷ_TYPE (ref) == error_mark_ଗଣ୍ଠି
      && !c_omp_array_section_p)
    ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;

  ଯଦି (ବୃକ୍ଷ_UNAVAILABLE (ref))
    error_unavailable_use (ref, NULL_ବୃକ୍ଷ);
  ଅନ୍ୟଥା ଯଦି (ବୃକ୍ଷ_DEPRECATED (ref))
    warn_deprecated_use (ref, NULL_ବୃକ୍ଷ);

  /* Recursive call does not count as usage.  */
  ଯଦି (ref != current_function_decl)
    {
      ବୃକ୍ଷ_USED (ref) = 1;
    }

  mark_decl_used (ref, ମିଥ୍ୟା);

  ଯଦି (ବୃକ୍ଷ_CODE (ref) == CONST_DECL)
    {
      used_types_ଭର୍ତ୍ତି (ବୃକ୍ଷ_TYPE (ref));

      ଯଦି (warn_cxx_compat
	  && ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (ref)) == ENUMERAL_TYPE
	  && C_TYPE_DEFINED_IN_STRUCT (ବୃକ୍ଷ_TYPE (ref)))
	{
	  warning_at (loc, OPT_Wc___compat,
		      "enum constant defined in struct or union "
		      "is not visible in C++");
	  inform (DECL_SOURCE_LOCATION (ref), "enum constant defined here");
	}

      ref = DECL_INITIAL (ref);
      ବୃକ୍ଷ_CONSTANT (ref) = 1;
    }
  /* C99 6.7.4p3: An inline definition of a function with external
     linkage ... shall not contain a reference to an identifier with
     internal linkage.  */
  ଅନ୍ୟଥା ଯଦି (current_function_decl != NULL_ବୃକ୍ଷ
	   && DECL_DECLARED_INLINE_P (current_function_decl)
	   && DECL_EXTERNAL (current_function_decl)
	   && VAR_OR_FUNCTION_DECL_P (ref)
	   && (!VAR_P (ref) || ବୃକ୍ଷ_STATIC (ref))
	   && ! ବୃକ୍ଷ_PUBLIC (ref)
	   && DECL_CONTEXT (ref) != current_function_decl)
    record_inline_static (loc, current_function_decl, ref,
			  csi_internal);

  ଫେରନ୍ତୁ ref;
}

ସ୍ଥିର ସଂରଚନା maybe_used_decl *maybe_used_decls;

/* Record that DECL, a reference seen inside sizeof or typeof or _Countof or
   _Generic, might be used if the operand of sizeof is a VLA type or the
   operand of typeof is a variably modified type or the operand of _Countof has
   a variable number of elements or the operand of _Generic is the one selected
   as the result.  */

ସ୍ଥିର ଶୂନ୍ୟ
record_maybe_used_decl (ବୃକ୍ଷ decl, ତାର୍କିକ address)
{
  ସଂରଚନା maybe_used_decl *t = XOBNEW (&parser_obstack, ସଂରଚନା maybe_used_decl);
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

ଶୂନ୍ୟ
କାଢ଼_maybe_used (ତାର୍କିକ used)
{
  ସଂରଚନା maybe_used_decl *p = maybe_used_decls;
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା cur_level = in_sizeof + in_typeof + in_countof + in_generic;
  ଯେତେବେଳେ (p && p->level > cur_level)
    {
      ଯଦି (used)
	{
	  ଯଦି (cur_level == 0)
	    mark_decl_used (p->decl, p->address);
	  ଅନ୍ୟଥା
	    p->level = cur_level;
	}
      p = p->next;
    }
  ଯଦି (!used || cur_level == 0)
    maybe_used_decls = p;
}

/* Pop the stack of decls possibly used inside sizeof or typeof or _Countof or
   _Generic, without acting on them, and return the pointer to the previous top
   of the stack.  This for use at the end of a default generic association when
   it is not yet known whether the expression is used.  If it later turns out
   the expression is used (or treated as used before C23), restore_maybe_used
   should be called on the return value followed by pop_maybe_used (true);
   otherwise, the return value can be discarded.  */

ସଂରଚନା maybe_used_decl *
save_maybe_used ()
{
  ସଂରଚନା maybe_used_decl *p = maybe_used_decls, *orig = p;
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା cur_level = in_sizeof + in_typeof + in_countof + in_generic;
  ଯେତେବେଳେ (p && p->level > cur_level)
    p = p->next;
  maybe_used_decls = p;
  ଫେରନ୍ତୁ orig;
}

/* Restore the stack of decls possibly used inside sizeof or typeof or _Countof
   or _Generic returned by save_maybe_used.  It is required that the stack is
   at exactly the point where it was left by save_maybe_used.  */

ଶୂନ୍ୟ
restore_maybe_used (ସଂରଚନା maybe_used_decl *ଗଦା)
{
  maybe_used_decls = ଗଦା;
}

/* Return the result of sizeof applied to EXPR.  */

ସଂରଚନା c_ପଦସମଷ୍ଟି
c_ପଦସମଷ୍ଟି_sizeof_ପଦସମଷ୍ଟି (location_t loc, ସଂରଚନା c_ପଦସମଷ୍ଟି ପଦସମଷ୍ଟି)
{
  ସଂରଚନା c_ପଦସମଷ୍ଟି ret;
  ଯଦି (ପଦସମଷ୍ଟି.ମୂଲ୍ୟ == error_mark_ଗଣ୍ଠି)
    {
      ret.ମୂଲ୍ୟ = error_mark_ଗଣ୍ଠି;
      ret.original_code = ERROR_MARK;
      ret.original_type = ଖାଲି;
      ret.m_decimal = 0;
      କାଢ଼_maybe_used (ମିଥ୍ୟା);
    }
  ଅନ୍ୟଥା
    {
      ତାର୍କିକ ପଦସମଷ୍ଟି_const_operands = ସତ୍ୟ;

      ଯଦି (ବୃକ୍ଷ_CODE (ପଦସମଷ୍ଟି.ମୂଲ୍ୟ) == PARM_DECL
	  && C_ARRAY_PARAMETER (ପଦସମଷ୍ଟି.ମୂଲ୍ୟ))
	{
	  auto_diagnostic_group d;
	  ଯଦି (warning_at (loc, OPT_Wsizeof_array_argument,
			  "%<sizeof%> on array function parameter %qE will "
			  "return size of %qT", ପଦସମଷ୍ଟି.ମୂଲ୍ୟ,
			  ବୃକ୍ଷ_TYPE (ପଦସମଷ୍ଟି.ମୂଲ୍ୟ)))
	    inform (DECL_SOURCE_LOCATION (ପଦସମଷ୍ଟି.ମୂଲ୍ୟ), "declared here");
	}
      ବୃକ୍ଷ folded_ପଦସମଷ୍ଟି = c_fully_fold (ପଦସମଷ୍ଟି.ମୂଲ୍ୟ, require_constant_ମୂଲ୍ୟ,
				       &ପଦସମଷ୍ଟି_const_operands);
      ret.ମୂଲ୍ୟ = c_sizeof (loc, ବୃକ୍ଷ_TYPE (folded_ପଦସମଷ୍ଟି));
      c_last_sizeof_arg = ପଦସମଷ୍ଟି.ମୂଲ୍ୟ;
      c_last_sizeof_loc = loc;
      ret.original_code = SIZEOF_ପଦସମଷ୍ଟି;
      ret.original_type = ଖାଲି;
      ret.m_decimal = 0;
      ଯଦି (C_TYPE_VARIABLE_SIZE (ବୃକ୍ଷ_TYPE (folded_ପଦସମଷ୍ଟି)))
	{
	  /* sizeof is evaluated when given a vla (C99 6.5.3.4p2).  */
	  ret.ମୂଲ୍ୟ = build2 (C_MAYBE_CONST_ପଦସମଷ୍ଟି, ବୃକ୍ଷ_TYPE (ret.ମୂଲ୍ୟ),
			      folded_ପଦସମଷ୍ଟି, ret.ମୂଲ୍ୟ);
	  C_MAYBE_CONST_ପଦସମଷ୍ଟି_NON_CONST (ret.ମୂଲ୍ୟ) = !ପଦସମଷ୍ଟି_const_operands;
	  SET_ପଦସମଷ୍ଟି_LOCATION (ret.ମୂଲ୍ୟ, loc);
	}
      କାଢ଼_maybe_used (C_TYPE_VARIABLE_SIZE (ବୃକ୍ଷ_TYPE (folded_ପଦସମଷ୍ଟି)));
    }
  ଫେରନ୍ତୁ ret;
}

/* Return the result of sizeof applied to T, a structure for the type
   name passed to sizeof (rather than the type itself).  LOC is the
   location of the original expression.  */

ସଂରଚନା c_ପଦସମଷ୍ଟି
c_ପଦସମଷ୍ଟି_sizeof_type (location_t loc, ସଂରଚନା c_type_name *t)
{
  ବୃକ୍ଷ type;
  ସଂରଚନା c_ପଦସମଷ୍ଟି ret;
  ବୃକ୍ଷ type_ପଦସମଷ୍ଟି = NULL_ବୃକ୍ଷ;
  ତାର୍କିକ type_ପଦସମଷ୍ଟି_const = ସତ୍ୟ;
  type = groktypename (t, &type_ପଦସମଷ୍ଟି, &type_ପଦସମଷ୍ଟି_const);
  ret.ମୂଲ୍ୟ = c_sizeof (loc, type);
  c_last_sizeof_arg = type;
  c_last_sizeof_loc = loc;
  ret.original_code = SIZEOF_ପଦସମଷ୍ଟି;
  ret.original_type = ଖାଲି;
  ret.m_decimal = 0;
  ଯଦି (type == error_mark_ଗଣ୍ଠି)
    {
      ret.ମୂଲ୍ୟ = error_mark_ଗଣ୍ଠି;
      ret.original_code = ERROR_MARK;
    }
  ଅନ୍ୟଥା
  ଯଦି ((type_ପଦସମଷ୍ଟି || ବୃକ୍ଷ_CODE (ret.ମୂଲ୍ୟ) == INTEGER_CST)
      && C_TYPE_VARIABLE_SIZE (type))
    {
      /* If the type is a [*] array, it is a VLA but is represented as
	 having a size of zero.  In such a case we must ensure that
	 the result of sizeof does not get folded to a constant by
	 c_fully_fold, because if the size is evaluated the result is
	 not constant and so constraints on zero or negative size
	 arrays must not be applied when this sizeof call is inside
	 another array declarator.  */
      ଯଦି (!type_ପଦସମଷ୍ଟି)
	type_ପଦସମଷ୍ଟି = integer_zero_ଗଣ୍ଠି;
      ret.ମୂଲ୍ୟ = build2 (C_MAYBE_CONST_ପଦସମଷ୍ଟି, ବୃକ୍ଷ_TYPE (ret.ମୂଲ୍ୟ),
			  type_ପଦସମଷ୍ଟି, ret.ମୂଲ୍ୟ);
      C_MAYBE_CONST_ପଦସମଷ୍ଟି_NON_CONST (ret.ମୂଲ୍ୟ) = !type_ପଦସମଷ୍ଟି_const;
    }
  କାଢ଼_maybe_used (type != error_mark_ଗଣ୍ଠି
		  ? C_TYPE_VARIABLE_SIZE (type) : ମିଥ୍ୟା);
  ଫେରନ୍ତୁ ret;
}

ସ୍ଥିର ତାର୍କିକ
ଶୀର୍ଷ_array_vla_p (const_ବୃକ୍ଷ type)
{
  ଯଦି (ବୃକ୍ଷ_CODE (type) != ARRAY_TYPE)
    ଫେରନ୍ତୁ ମିଥ୍ୟା;

  ବୃକ୍ଷ d = TYPE_DOMAIN (type);

  ଯଦି (!d)
    ଫେରନ୍ତୁ ମିଥ୍ୟା;
  ଯଦି (!TYPE_MAX_ମୂଲ୍ୟ (d))
    ଫେରନ୍ତୁ ମିଥ୍ୟା;

  ଫେରନ୍ତୁ ବୃକ୍ଷ_CODE (TYPE_MAX_ମୂଲ୍ୟ (d)) != INTEGER_CST
	 || ବୃକ୍ଷ_CODE (TYPE_MIN_ମୂଲ୍ୟ (d)) != INTEGER_CST;
}

/* Return the result of countof applied to EXPR.  */

ସଂରଚନା c_ପଦସମଷ୍ଟି
c_ପଦସମଷ୍ଟି_countof_ପଦସମଷ୍ଟି (location_t loc, ସଂରଚନା c_ପଦସମଷ୍ଟି ପଦସମଷ୍ଟି)
{
  ସଂରଚନା c_ପଦସମଷ୍ଟି ret;
  ଯଦି (ପଦସମଷ୍ଟି.ମୂଲ୍ୟ == error_mark_ଗଣ୍ଠି)
    {
      ret.ମୂଲ୍ୟ = error_mark_ଗଣ୍ଠି;
      ret.original_code = ERROR_MARK;
      ret.original_type = ଖାଲି;
      ret.m_decimal = 0;
      କାଢ଼_maybe_used (ମିଥ୍ୟା);
    }
  ଅନ୍ୟଥା
    {
      ତାର୍କିକ ପଦସମଷ୍ଟି_const_operands = ସତ୍ୟ;

      ବୃକ୍ଷ folded_ପଦସମଷ୍ଟି = c_fully_fold (ପଦସମଷ୍ଟି.ମୂଲ୍ୟ, require_constant_ମୂଲ୍ୟ,
				       &ପଦସମଷ୍ଟି_const_operands);
      ret.ମୂଲ୍ୟ = c_countof_type (loc, ବୃକ୍ଷ_TYPE (folded_ପଦସମଷ୍ଟି));
      c_last_sizeof_arg = ପଦସମଷ୍ଟି.ମୂଲ୍ୟ;
      c_last_sizeof_loc = loc;
      ret.original_code = COUNTOF_ପଦସମଷ୍ଟି;
      ret.original_type = ଖାଲି;
      ret.m_decimal = 0;
      ଯଦି (ଶୀର୍ଷ_array_vla_p (ବୃକ୍ଷ_TYPE (folded_ପଦସମଷ୍ଟି)))
	{
	  /* countof is evaluated when given a vla.  */
	  ret.ମୂଲ୍ୟ = build2 (C_MAYBE_CONST_ପଦସମଷ୍ଟି, ବୃକ୍ଷ_TYPE (ret.ମୂଲ୍ୟ),
			      folded_ପଦସମଷ୍ଟି, ret.ମୂଲ୍ୟ);
	  C_MAYBE_CONST_ପଦସମଷ୍ଟି_NON_CONST (ret.ମୂଲ୍ୟ) = !ପଦସମଷ୍ଟି_const_operands;
	  SET_ପଦସମଷ୍ଟି_LOCATION (ret.ମୂଲ୍ୟ, loc);
	}
      କାଢ଼_maybe_used (ଶୀର୍ଷ_array_vla_p (ବୃକ୍ଷ_TYPE (folded_ପଦସମଷ୍ଟି)));
    }
  ଫେରନ୍ତୁ ret;
}

/* Return the result of countof applied to T, a structure for the type
   name passed to countof (rather than the type itself).  LOC is the
   location of the original expression.  */

ସଂରଚନା c_ପଦସମଷ୍ଟି
c_ପଦସମଷ୍ଟି_countof_type (location_t loc, ସଂରଚନା c_type_name *t)
{
  ବୃକ୍ଷ type;
  ସଂରଚନା c_ପଦସମଷ୍ଟି ret;
  ବୃକ୍ଷ type_ପଦସମଷ୍ଟି = NULL_ବୃକ୍ଷ;
  ତାର୍କିକ type_ପଦସମଷ୍ଟି_const = ସତ୍ୟ;
  type = groktypename (t, &type_ପଦସମଷ୍ଟି, &type_ପଦସମଷ୍ଟି_const);
  ret.ମୂଲ୍ୟ = c_countof_type (loc, type);
  c_last_sizeof_arg = type;
  c_last_sizeof_loc = loc;
  ret.original_code = COUNTOF_ପଦସମଷ୍ଟି;
  ret.original_type = ଖାଲି;
  ret.m_decimal = 0;
  ଯଦି (type == error_mark_ଗଣ୍ଠି)
    {
      ret.ମୂଲ୍ୟ = error_mark_ଗଣ୍ଠି;
      ret.original_code = ERROR_MARK;
    }
  ଅନ୍ୟଥା
  ଯଦି ((type_ପଦସମଷ୍ଟି || ବୃକ୍ଷ_CODE (ret.ମୂଲ୍ୟ) == INTEGER_CST)
      && ଶୀର୍ଷ_array_vla_p (type))
    {
      /* If the type is a [*] array, it is a VLA but is represented as
	 having a size of zero.  In such a case we must ensure that
	 the result of countof does not get folded to a constant by
	 c_fully_fold, because if the number of elements is evaluated
	 the result is not constant and so
	 constraints on zero or negative size arrays must not be applied
	 when this countof call is inside another array declarator.  */
      ଯଦି (!type_ପଦସମଷ୍ଟି)
	type_ପଦସମଷ୍ଟି = integer_zero_ଗଣ୍ଠି;
      ret.ମୂଲ୍ୟ = build2 (C_MAYBE_CONST_ପଦସମଷ୍ଟି, ବୃକ୍ଷ_TYPE (ret.ମୂଲ୍ୟ),
			  type_ପଦସମଷ୍ଟି, ret.ମୂଲ୍ୟ);
      C_MAYBE_CONST_ପଦସମଷ୍ଟି_NON_CONST (ret.ମୂଲ୍ୟ) = !type_ପଦସମଷ୍ଟି_const;
    }
  କାଢ଼_maybe_used (type != error_mark_ଗଣ୍ଠି ? ଶୀର୍ଷ_array_vla_p (type) : ମିଥ୍ୟା);
  ଫେରନ୍ତୁ ret;
}

/* Return the result of maxof applied to T, a structure for the type
   name passed to maxof (rather than the type itself).  LOC is the
   location of the original expression.  */

ସଂରଚନା c_ପଦସମଷ୍ଟି
c_ପଦସମଷ୍ଟି_maxof_type (location_t loc, ସଂରଚନା c_type_name *t)
{
  ବୃକ୍ଷ type;
  ସଂରଚନା c_ପଦସମଷ୍ଟି ret;
  ବୃକ୍ଷ type_ପଦସମଷ୍ଟି = NULL_ବୃକ୍ଷ;
  ତାର୍କିକ type_ପଦସମଷ୍ଟି_const = ସତ୍ୟ;
  type = groktypename (t, &type_ପଦସମଷ୍ଟି, &type_ପଦସମଷ୍ଟି_const);
  ret.ମୂଲ୍ୟ = c_maxof_type (loc, type);
  c_last_sizeof_arg = type;
  c_last_sizeof_loc = loc;
  ret.original_code = MAXOF_ପଦସମଷ୍ଟି;
  ret.original_type = ଖାଲି;
  ret.m_decimal = 0;
  ଯଦି (type == error_mark_ଗଣ୍ଠି)
    {
      ret.ମୂଲ୍ୟ = error_mark_ଗଣ୍ଠି;
      ret.original_code = ERROR_MARK;
    }
  କାଢ଼_maybe_used (type != error_mark_ଗଣ୍ଠି);
  ଫେରନ୍ତୁ ret;
}

/* Return the result of minof applied to T, a structure for the type
   name passed to minof (rather than the type itself).  LOC is the
   location of the original expression.  */

ସଂରଚନା c_ପଦସମଷ୍ଟି
c_ପଦସମଷ୍ଟି_minof_type (location_t loc, ସଂରଚନା c_type_name *t)
{
  ବୃକ୍ଷ type;
  ସଂରଚନା c_ପଦସମଷ୍ଟି ret;
  ବୃକ୍ଷ type_ପଦସମଷ୍ଟି = NULL_ବୃକ୍ଷ;
  ତାର୍କିକ type_ପଦସମଷ୍ଟି_const = ସତ୍ୟ;
  type = groktypename (t, &type_ପଦସମଷ୍ଟି, &type_ପଦସମଷ୍ଟି_const);
  ret.ମୂଲ୍ୟ = c_minof_type (loc, type);
  c_last_sizeof_arg = type;
  c_last_sizeof_loc = loc;
  ret.original_code = MINOF_ପଦସମଷ୍ଟି;
  ret.original_type = ଖାଲି;
  ret.m_decimal = 0;
  ଯଦି (type == error_mark_ଗଣ୍ଠି)
    {
      ret.ମୂଲ୍ୟ = error_mark_ଗଣ୍ଠି;
      ret.original_code = ERROR_MARK;
    }
  କାଢ଼_maybe_used (type != error_mark_ଗଣ୍ଠି);
  ଫେରନ୍ତୁ ret;
}

/* Build a function call to function FUNCTION with parameters PARAMS.
   The function call is at LOC.
   PARAMS is a list--a chain of TREE_LIST nodes--in which the
   TREE_VALUE of each node is a parameter-expression.
   FUNCTION's data type may be a function type or a pointer-to-function.  */

ବୃକ୍ଷ
build_function_call (location_t loc, ବୃକ୍ଷ function, ବୃକ୍ଷ params)
{
  vec<ବୃକ୍ଷ, va_gc> *v;
  ବୃକ୍ଷ ret;

  vec_alloc (v, list_length (params));
  ପାଇଁ (; params; params = ବୃକ୍ଷ_CHAIN (params))
    v->quick_ଠେଲ (ବୃକ୍ଷ_ମୂଲ୍ୟ (params));
  ret = c_build_function_call_vec (loc, vNULL, function, v, ଖାଲି);
  vec_free (v);
  ଫେରନ୍ତୁ ret;
}

/* Give a note about the location of the declaration of DECL,
   or, failing that, a pertinent declaration for FUNCTION_EXPR.  */

ସ୍ଥିର ଶୂନ୍ୟ
inform_declaration (ବୃକ୍ଷ decl, ବୃକ୍ଷ function_ପଦସମଷ୍ଟି)
{
  ଯଦି (decl && (ବୃକ୍ଷ_CODE (decl) != FUNCTION_DECL
	       || !DECL_IS_UNDECLARED_BUILTIN (decl)))
    inform (DECL_SOURCE_LOCATION (decl), "declared here");
  ଅନ୍ୟଥା ଯଦି (function_ପଦସମଷ୍ଟି)
    ବାଛ (ବୃକ୍ଷ_CODE (function_ପଦସମଷ୍ଟି))
      {
      ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
	ଭାଙ୍ଗ;
      ସ୍ଥିତି COMPONENT_REF:
	/* Show the decl of the pertinent field (e.g. for callback
	   fields in a struct.  */
	{
	  ବୃକ୍ଷ field_decl = ବୃକ୍ଷ_OPERAND (function_ପଦସମଷ୍ଟି, 1);
	  ଯଦି (location_t loc = DECL_SOURCE_LOCATION (field_decl))
	    inform (loc, "declared here");
	}
	ଭାଙ୍ଗ;
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

ବୃକ୍ଷ
build_function_call_vec (location_t loc, vec<location_t> arg_loc,
			 ବୃକ୍ଷ function, vec<ବୃକ୍ଷ, va_gc> *params,
			 vec<ବୃକ୍ଷ, va_gc> *origtypes, ବୃକ୍ଷ orig_fundecl)
{
  ବୃକ୍ଷ fntype, fundecl = NULL_ବୃକ୍ଷ;
  ବୃକ୍ଷ name = NULL_ବୃକ୍ଷ, result;
  ବୃକ୍ଷ tem;
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା nargs;
  ବୃକ୍ଷ *argarray;


  /* Strip NON_LVALUE_EXPRs, etc., since we aren't using as an lvalue.  */
  STRIP_TYPE_NOPS (function);

  /* Convert anything with function type to a pointer-to-function.  */
  ଯଦି (ବୃକ୍ଷ_CODE (function) == FUNCTION_DECL)
    {
      name = DECL_NAME (function);

      ଯଦି (flag_tm)
	tm_malloc_replacement (function);
      fundecl = function;
      ଯଦି (!orig_fundecl)
	orig_fundecl = fundecl;
      /* Atomic functions have type checking/casting already done.  They are
	 often rewritten and don't match the original parameter list.  */
      ଯଦି (name && startswith (IDENTIFIER_POINTER (name), "__atomic_"))
        origtypes = ଖାଲି;
    }
  ଯଦି (ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (function)) == FUNCTION_TYPE)
    function = function_to_pointer_conversion (loc, function);

  /* For Objective-C, convert any calls via a cast to OBJC_TYPE_REF
     expressions, like those used for ObjC messenger dispatches.  */
  ଯଦି (params && !params->is_empty ())
    function = objc_rewrite_function_call (function, (*params)[0]);

  function = c_fully_fold (function, ମିଥ୍ୟା, ଖାଲି);

  fntype = ବୃକ୍ଷ_TYPE (function);

  ଯଦି (ବୃକ୍ଷ_CODE (fntype) == ERROR_MARK)
    ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;

  ଯଦି (!(ବୃକ୍ଷ_CODE (fntype) == POINTER_TYPE
	&& ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (fntype)) == FUNCTION_TYPE))
    {
      ଯଦି (!flag_diagnostics_show_caret && !STATEMENT_CLASS_P (function))
	error_at (loc,
		  "called object %qE is not a function or function pointer",
		  function);
      ଅନ୍ୟଥା ଯଦି (DECL_P (function))
	{
	  auto_diagnostic_group d;
	  error_at (loc,
		    "called object %qD is not a function or function pointer",
		    function);
	  inform_declaration (function, NULL_ବୃକ୍ଷ);
	}
      ଅନ୍ୟଥା
	error_at (loc,
		  "called object is not a function or function pointer");
      ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
    }

  ଯଦି (fundecl && ବୃକ୍ଷ_THIS_VOLATILE (fundecl))
    current_function_returns_abnormally = 1;

  /* fntype now gets the type of function pointed to.  */
  fntype = ବୃକ୍ଷ_TYPE (fntype);
  ବୃକ୍ଷ return_type = ବୃକ୍ଷ_TYPE (fntype);

  /* Convert the parameters to the types declared in the
     function prototype, or apply default promotions.  */

  nargs = convert_arguments (loc, arg_loc, fntype, params,
			     origtypes, function, fundecl);
  ଯଦି (nargs < 0)
    ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;

  /* Check that the function is called through a compatible prototype.
     If it is not, warn.  */
  ଯଦି (CONVERT_ପଦସମଷ୍ଟି_P (function)
      && ବୃକ୍ଷ_CODE (tem = ବୃକ୍ଷ_OPERAND (function, 0)) == ADDR_ପଦସମଷ୍ଟି
      && ବୃକ୍ଷ_CODE (tem = ବୃକ୍ଷ_OPERAND (tem, 0)) == FUNCTION_DECL
      && !comptypes (fntype, ବୃକ୍ଷ_TYPE (tem)))
    {
      /* This situation leads to run-time undefined behavior.  We can't,
	 therefore, simply error unless we can prove that all possible
	 executions of the program must execute the code.  */
      warning_at (loc, 0, "function called through a non-compatible type");

      ଯଦି (VOID_TYPE_P (return_type)
	  && TYPE_QUALS (return_type) != TYPE_UNQUALIFIED)
	pedwarn (loc, 0,
		 "function with qualified void return type called");
     }

  argarray = vec_safe_address (params);

  /* Check that arguments to builtin functions match the expectations.  */
  ଯଦି (fundecl
      && fndecl_built_in_p (fundecl)
      && !check_builtin_function_arguments (loc, arg_loc, fundecl,
					    orig_fundecl, nargs, argarray))
    ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;

  /* Check that the arguments to the function are valid.  */
  ତାର୍କିକ warned_p = check_function_arguments (loc, fundecl, fntype,
					    nargs, argarray, &arg_loc,
					    comptypes);

  ଯଦି (TYPE_QUALS (return_type) != TYPE_UNQUALIFIED
      && !VOID_TYPE_P (return_type))
    return_type = c_build_qualified_type (return_type, TYPE_UNQUALIFIED);
  ଯଦି (name != NULL_ବୃକ୍ଷ
      && startswith (IDENTIFIER_POINTER (name), "__builtin_"))
    {
      ଯଦି (require_constant_ମୂଲ୍ୟ)
	result
	  = fold_build_call_array_initializer_loc (loc, return_type,
						   function, nargs, argarray);
      ଅନ୍ୟଥା
	result = fold_build_call_array_loc (loc, return_type,
					    function, nargs, argarray);
      ଯଦି (ବୃକ୍ଷ_CODE (result) == NOP_ପଦସମଷ୍ଟି
	  && ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_OPERAND (result, 0)) == INTEGER_CST)
	STRIP_TYPE_NOPS (result);
    }
  ଅନ୍ୟଥା
    result = build_call_array_loc (loc, return_type,
				   function, nargs, argarray);
  /* If -Wnonnull warning has been diagnosed, avoid diagnosing it again
     later.  */
  ଯଦି (warned_p && ବୃକ୍ଷ_CODE (result) == CALL_ପଦସମଷ୍ଟି)
    suppress_warning (result, OPT_Wnonnull);

  /* In this improbable scenario, a nested function returns a VM type.
     Create a TARGET_EXPR so that the call always has a LHS, much as
     what the C++ FE does for functions returning non-PODs.  */
  ଯଦି (c_type_variably_modified_p (ବୃକ୍ଷ_TYPE (fntype)))
    {
      ବୃକ୍ଷ tmp = create_tmp_var_raw (ବୃକ୍ଷ_TYPE (fntype));
      result = build4 (TARGET_ପଦସମଷ୍ଟି, ବୃକ୍ଷ_TYPE (fntype), tmp, result,
		       NULL_ବୃକ୍ଷ, NULL_ବୃକ୍ଷ);
    }

  ଯଦି (VOID_TYPE_P (ବୃକ୍ଷ_TYPE (result)))
    {
      ଯଦି (TYPE_QUALS (ବୃକ୍ଷ_TYPE (result)) != TYPE_UNQUALIFIED)
	pedwarn (loc, 0,
		 "function with qualified void return type called");
      ଫେରନ୍ତୁ result;
    }
  ଫେରନ୍ତୁ require_complete_type (loc, result);
}

/* Like build_function_call_vec, but call also resolve_overloaded_builtin.  */

ବୃକ୍ଷ
c_build_function_call_vec (location_t loc, ଅଚଳ vec<location_t> &arg_loc,
			   ବୃକ୍ଷ function, vec<ବୃକ୍ଷ, va_gc> *params,
			   vec<ବୃକ୍ଷ, va_gc> *origtypes)
{
  /* Strip NON_LVALUE_EXPRs, etc., since we aren't using as an lvalue.  */
  STRIP_TYPE_NOPS (function);

  /* Convert anything with function type to a pointer-to-function.  */
  ଯଦି (ବୃକ୍ଷ_CODE (function) == FUNCTION_DECL)
    {
      /* Implement type-directed function overloading for builtins.
	 resolve_overloaded_builtin and targetm.resolve_overloaded_builtin
	 handle all the type checking.  The result is a complete expression
	 that implements this function call.  */
      ବୃକ୍ଷ tem = resolve_overloaded_builtin (loc, function, params);
      ଯଦି (tem)
	ଫେରନ୍ତୁ tem;
    }
  ଫେରନ୍ତୁ build_function_call_vec (loc, arg_loc, function, params, origtypes);
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

ସ୍ଥିର ବୃକ୍ଷ
convert_argument (location_t ploc, ବୃକ୍ଷ function, ବୃକ୍ଷ fundecl,
		  ବୃକ୍ଷ type, ବୃକ୍ଷ origtype, ବୃକ୍ଷ val, ବୃକ୍ଷ valtype,
		  ତାର୍କିକ npc, ବୃକ୍ଷ rname, ପୂର୍ଣ୍ଣସଂଖ୍ୟା parmnum, ପୂର୍ଣ୍ଣସଂଖ୍ୟା argnum,
		  ତାର୍କିକ excess_precision, ପୂର୍ଣ୍ଣସଂଖ୍ୟା warnopt)
{
  /* Formal parm type is specified by a function prototype.  */

  ଯଦି (type == error_mark_ଗଣ୍ଠି || !COMPLETE_TYPE_P (type))
    {
      error_at (ploc, "type of formal parameter %d is incomplete",
		parmnum + 1);
      ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
    }

  /* Optionally warn about conversions that differ from the default
     conversions.  */
  ଯଦି (warn_traditional_conversion || warn_traditional)
    {
      ଯଦି (INTEGRAL_TYPE_P (type)
	  && SCALAR_FLOAT_TYPE_P (valtype))
	warning_at (ploc, OPT_Wtraditional_conversion,
		    "passing argument %d of %qE as integer rather "
		    "than floating due to prototype",
		    argnum, rname);
      ଯଦି (INTEGRAL_TYPE_P (type)
	  && ବୃକ୍ଷ_CODE (valtype) == COMPLEX_TYPE)
	warning_at (ploc, OPT_Wtraditional_conversion,
		    "passing argument %d of %qE as integer rather "
		    "than complex due to prototype",
		    argnum, rname);
      ଅନ୍ୟଥା ଯଦି (ବୃକ୍ଷ_CODE (type) == COMPLEX_TYPE
	       && SCALAR_FLOAT_TYPE_P (valtype))
	warning_at (ploc, OPT_Wtraditional_conversion,
		    "passing argument %d of %qE as complex rather "
		    "than floating due to prototype",
		    argnum, rname);
      ଅନ୍ୟଥା ଯଦି (SCALAR_FLOAT_TYPE_P (type)
	       && INTEGRAL_TYPE_P (valtype))
	warning_at (ploc, OPT_Wtraditional_conversion,
		    "passing argument %d of %qE as floating rather "
		    "than integer due to prototype",
		    argnum, rname);
      ଅନ୍ୟଥା ଯଦି (ବୃକ୍ଷ_CODE (type) == COMPLEX_TYPE
	       && INTEGRAL_TYPE_P (valtype))
	warning_at (ploc, OPT_Wtraditional_conversion,
		    "passing argument %d of %qE as complex rather "
		    "than integer due to prototype",
		    argnum, rname);
      ଅନ୍ୟଥା ଯଦି (SCALAR_FLOAT_TYPE_P (type)
	       && ବୃକ୍ଷ_CODE (valtype) == COMPLEX_TYPE)
	warning_at (ploc, OPT_Wtraditional_conversion,
		    "passing argument %d of %qE as floating rather "
		    "than complex due to prototype",
		    argnum, rname);
      /* ??? At some point, messages should be written about
	 conversions between complex types, but that's too messy
	 to do now.  */
      ଅନ୍ୟଥା ଯଦି (SCALAR_FLOAT_TYPE_P (type)
	       && SCALAR_FLOAT_TYPE_P (valtype))
	{
	  unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା formal_prec = TYPE_PRECISION (type);

	  /* Warn if any argument is passed as `float',
	     since without a prototype it would be `double'.  */
	  ଯଦି (formal_prec == TYPE_PRECISION (float_type_ଗଣ୍ଠି)
	      && type != dfloat32_type_ଗଣ୍ଠି)
	    warning_at (ploc, 0,
			"passing argument %d of %qE as %<float%> "
			"rather than %<double%> due to prototype",
			argnum, rname);

	  /* Warn if mismatch between argument and prototype
	     for decimal float types.  Warn of conversions with
	     binary float types and of precision narrowing due to
	     prototype.  */
	  ଅନ୍ୟଥା ଯଦି (type != valtype
		   && (type == dfloat32_type_ଗଣ୍ଠି
		       || type == dfloat64_type_ଗଣ୍ଠି
		       || type == dfloat128_type_ଗଣ୍ଠି
		       || valtype == dfloat32_type_ଗଣ୍ଠି
		       || valtype == dfloat64_type_ଗଣ୍ଠି
		       || valtype == dfloat128_type_ଗଣ୍ଠି)
		   && (formal_prec
		       <= TYPE_PRECISION (valtype)
		       || (type == dfloat128_type_ଗଣ୍ଠି
			   && (valtype
			       != dfloat64_type_ଗଣ୍ଠି
			       && (valtype
				   != dfloat32_type_ଗଣ୍ଠି)))
		       || (type == dfloat64_type_ଗଣ୍ଠି
			   && (valtype
			       != dfloat32_type_ଗଣ୍ଠି))))
	    warning_at (ploc, 0,
			"passing argument %d of %qE as %qT "
			"rather than %qT due to prototype",
			argnum, rname, type, valtype);

	}
      /* Detect integer changing in width or signedness.
	 These warnings are only activated with
	 -Wtraditional-conversion, not with -Wtraditional.  */
      ଅନ୍ୟଥା ଯଦି (warn_traditional_conversion
	       && INTEGRAL_TYPE_P (type)
	       && INTEGRAL_TYPE_P (valtype))
	{
	  unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା formal_prec = TYPE_PRECISION (type);
	  ବୃକ୍ଷ would_have_been = default_conversion (val);
	  ବୃକ୍ଷ type1 = ବୃକ୍ଷ_TYPE (would_have_been);

	  ଯଦି (val == error_mark_ଗଣ୍ଠି)
	    /* VAL could have been of incomplete type.  */;
	  ଅନ୍ୟଥା ଯଦି (ବୃକ୍ଷ_CODE (type) == ENUMERAL_TYPE
		   && (TYPE_MAIN_VARIANT (type)
		       == TYPE_MAIN_VARIANT (valtype)))
	    /* No warning if function asks for enum
	       and the actual arg is that enum type.  */
	    ;
	  ଅନ୍ୟଥା ଯଦି (formal_prec != TYPE_PRECISION (type1))
	    warning_at (ploc, OPT_Wtraditional_conversion,
			"passing argument %d of %qE "
			"with different width due to prototype",
			argnum, rname);
	  ଅନ୍ୟଥା ଯଦି (TYPE_UNSIGNED (type) == TYPE_UNSIGNED (type1))
	    ;
	  /* Don't complain if the formal parameter type
	     is an enum, because we can't tell now whether
	     the value was an enum--even the same enum.  */
	  ଅନ୍ୟଥା ଯଦି (ବୃକ୍ଷ_CODE (type) == ENUMERAL_TYPE)
	    ;
	  ଅନ୍ୟଥା ଯଦି (ବୃକ୍ଷ_CODE (val) == INTEGER_CST
		   && int_fits_type_p (val, type))
	    /* Change in signedness doesn't matter
	       if a constant value is unaffected.  */
	    ;
	  /* If the value is extended from a narrower
	     unsigned type, it doesn't matter whether we
	     pass it as signed or unsigned; the value
	     certainly is the same either way.  */
	  ଅନ୍ୟଥା ଯଦି (TYPE_PRECISION (valtype) < TYPE_PRECISION (type)
		   && TYPE_UNSIGNED (valtype))
	    ;
	  ଅନ୍ୟଥା ଯଦି (TYPE_UNSIGNED (type))
	    warning_at (ploc, OPT_Wtraditional_conversion,
			"passing argument %d of %qE "
			"as unsigned due to prototype",
			argnum, rname);
	  ଅନ୍ୟଥା
	    warning_at (ploc, OPT_Wtraditional_conversion,
			"passing argument %d of %qE "
			"as signed due to prototype",
			argnum, rname);
	}
    }

  /* Possibly restore an EXCESS_PRECISION_EXPR for the
     sake of better warnings from convert_and_check.  */
  ଯଦି (excess_precision)
    val = build1 (EXCESS_PRECISION_ପଦସମଷ୍ଟି, valtype, val);

  ବୃକ୍ଷ parmval = convert_for_assignment (ploc, ploc, type,
					 val, origtype, ic_argpass,
					 npc, fundecl, function,
					 parmnum + 1, warnopt);
  ଫେରନ୍ତୁ parmval;
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

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା
convert_arguments (location_t loc, vec<location_t> arg_loc, ବୃକ୍ଷ fntype,
		   vec<ବୃକ୍ଷ, va_gc> *ମୂଲ୍ୟଗୁଡ଼ିକ, vec<ବୃକ୍ଷ, va_gc> *origtypes,
		   ବୃକ୍ଷ function, ବୃକ୍ଷ fundecl)
{
  ବୃକ୍ଷ typelist = TYPE_ARG_TYPES (fntype);
  unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା parmnum;
  ତାର୍କିକ error_args = ମିଥ୍ୟା;
  ଅଚଳ ତାର୍କିକ type_generic = fundecl
    && lookup_attribute ("type generic", TYPE_ATTRIBUTES (ବୃକ୍ଷ_TYPE (fundecl)));
  ତାର୍କିକ type_generic_remove_excess_precision = ମିଥ୍ୟା;
  ତାର୍କିକ type_generic_overflow_p = ମିଥ୍ୟା;
  ତାର୍କିକ type_generic_bit_query = ମିଥ୍ୟା;
  ବୃକ୍ଷ selector;

  /* Change pointer to function to the function itself for
     diagnostics.  */
  ଯଦି (ବୃକ୍ଷ_CODE (function) == ADDR_ପଦସମଷ୍ଟି
      && ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_OPERAND (function, 0)) == FUNCTION_DECL)
    function = ବୃକ୍ଷ_OPERAND (function, 0);

  /* Handle an ObjC selector specially for diagnostics.  */
  selector = objc_message_selector ();

  /* For a call to a built-in function declared without a prototype,
     set to the built-in function's argument list.  */
  ବୃକ୍ଷ builtin_typelist = NULL_ବୃକ୍ଷ;

  /* For type-generic built-in functions, determine whether excess
     precision should be removed (classification) or not
     (comparison).  */
  ଯଦି (fundecl
      && fndecl_built_in_p (fundecl, BUILT_IN_NORMAL))
    {
      built_in_function code = DECL_FUNCTION_CODE (fundecl);
      ଯଦି (C_DECL_BUILTIN_PROTOTYPE (fundecl))
	{
	  /* For a call to a built-in function declared without a prototype
	     use the types of the parameters of the internal built-in to
	     match those of the arguments to.  */
	  ଯଦି (ବୃକ୍ଷ bdecl = builtin_decl_explicit (code))
	    builtin_typelist = TYPE_ARG_TYPES (ବୃକ୍ଷ_TYPE (bdecl));
	}

      /* For type-generic built-in functions, determine whether excess
	 precision should be removed (classification) or not
	 (comparison).  */
      ଯଦି (type_generic)
	ବାଛ (code)
	  {
	  ସ୍ଥିତି BUILT_IN_ISFINITE:
	  ସ୍ଥିତି BUILT_IN_ISINF:
	  ସ୍ଥିତି BUILT_IN_ISINF_SIGN:
	  ସ୍ଥିତି BUILT_IN_ISNAN:
	  ସ୍ଥିତି BUILT_IN_ISNORMAL:
	  ସ୍ଥିତି BUILT_IN_ISSIGNALING:
	  ସ୍ଥିତି BUILT_IN_FPCLASSIFY:
	    type_generic_remove_excess_precision = ସତ୍ୟ;
	    ଭାଙ୍ଗ;

	  ସ୍ଥିତି BUILT_IN_ADD_OVERFLOW_P:
	  ସ୍ଥିତି BUILT_IN_SUB_OVERFLOW_P:
	  ସ୍ଥିତି BUILT_IN_MUL_OVERFLOW_P:
	    /* The last argument of these type-generic builtins
	       should not be promoted.  */
	    type_generic_overflow_p = ସତ୍ୟ;
	    ଭାଙ୍ଗ;

	  ସ୍ଥିତି BUILT_IN_CLZG:
	  ସ୍ଥିତି BUILT_IN_CTZG:
	  ସ୍ଥିତି BUILT_IN_CLRSBG:
	  ସ୍ଥିତି BUILT_IN_FFSG:
	  ସ୍ଥିତି BUILT_IN_PARITYG:
	  ସ୍ଥିତି BUILT_IN_POPCOUNTG:
	    /* The first argument of these type-generic builtins
	       should not be promoted.  */
	    type_generic_bit_query = ସତ୍ୟ;
	    ଭାଙ୍ଗ;

	  ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
	    ଭାଙ୍ଗ;
	  }
    }

  /* Scan the given expressions (VALUES) and types (TYPELIST), producing
     individual converted arguments.  */

  ବୃକ୍ଷ typetail, builtin_typetail, val;
  ପାଇଁ (typetail = typelist,
	 builtin_typetail = builtin_typelist,
	 parmnum = 0;
       ମୂଲ୍ୟଗୁଡ଼ିକ && ମୂଲ୍ୟଗୁଡ଼ିକ->iterate (parmnum, &val);
       ++parmnum)
    {
      /* The type of the function parameter (if it was declared with one).  */
      ବୃକ୍ଷ type = typetail ? ବୃକ୍ଷ_ମୂଲ୍ୟ (typetail) : NULL_ବୃକ୍ଷ;
      /* The type of the built-in function parameter (if the function
	 is a built-in).  Used to detect type incompatibilities in
	 calls to built-ins declared without a prototype.  */
      ବୃକ୍ଷ builtin_type = (builtin_typetail
			   ? ବୃକ୍ଷ_ମୂଲ୍ୟ (builtin_typetail) : NULL_ବୃକ୍ଷ);
      /* The original type of the argument being passed to the function.  */
      ବୃକ୍ଷ valtype = ବୃକ୍ଷ_TYPE (val);
      /* The called function (or function selector in Objective C).  */
      ବୃକ୍ଷ rname = function;
      ପୂର୍ଣ୍ଣସଂଖ୍ୟା argnum = parmnum + 1;
      ଅଚଳ ଅକ୍ଷର *invalid_func_diag;
      /* Set for EXCESS_PRECISION_EXPR arguments.  */
      ତାର୍କିକ excess_precision = ମିଥ୍ୟା;
      /* The value of the argument after conversion to the type
	 of the function parameter it is passed to.  */
      ବୃକ୍ଷ parmval;
      /* Some __atomic_* builtins have additional hidden argument at
	 position 0.  */
      location_t ploc
	= !arg_loc.is_empty () && ମୂଲ୍ୟଗୁଡ଼ିକ->length () == arg_loc.length ()
	  ? expansion_point_location_if_in_system_header (arg_loc[parmnum])
	  : ନିବେଶ_location;

      ଯଦି (type == void_type_ଗଣ୍ଠି)
	{
	  auto_diagnostic_group d;
	  ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଅଙ୍କ_expected = parmnum;
	  ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଅଙ୍କ_actual = ମୂଲ୍ୟଗୁଡ଼ିକ->length ();
	  gcc_rich_location rich_loc (loc);
	  ଯଦି (ploc != ନିବେଶ_location)
	    rich_loc.add_range (ploc);
	  ଯଦି (selector)
	    error_at (&rich_loc,
		      "too many arguments to method %qE; expected %i, have %i",
		      selector, ଅଙ୍କ_expected, ଅଙ୍କ_actual);
	  ଅନ୍ୟଥା
	    error_at (&rich_loc,
		      "too many arguments to function %qE; expected %i, have %i",
		      function, ଅଙ୍କ_expected, ଅଙ୍କ_actual);
	  inform_declaration (fundecl, function);
	  ଫେରନ୍ତୁ error_args ? -1 : (ପୂର୍ଣ୍ଣସଂଖ୍ୟା) parmnum;
	}

      ଯଦି (builtin_type == void_type_ଗଣ୍ଠି)
	{
	  auto_diagnostic_group d;
	  ଯଦି (warning_at (loc, OPT_Wbuiltin_declaration_mismatch,
			  "too many arguments to built-in function %qE "
			  "expecting %d", function, parmnum))
	    inform_declaration (fundecl, function);
	  builtin_typetail = NULL_ବୃକ୍ଷ;
	}

      ଯଦି (!typetail && parmnum == 0 && !TYPE_NO_NAMED_ARGS_STDARG_P (fntype)
	  && !(fundecl && fndecl_built_in_p (fundecl)))
	{
	  auto_diagnostic_group d;
	  ତାର୍କିକ warned;
	  ଯଦି (selector)
	    warned = warning_at (loc, OPT_Wdeprecated_non_prototype,
				 "ISO C23 does not allow arguments"
				 " for method %qE declared without parameters",
				 function);
	  ଅନ୍ୟଥା
	    warned = warning_at (loc, OPT_Wdeprecated_non_prototype,
				 "ISO C23 does not allow arguments"
				 " for function %qE declared without parameters",
				 function);
	  ଯଦି (warned)
	    inform_declaration (fundecl, function);
	}

      ଯଦି (selector && argnum > 2)
	{
	  rname = selector;
	  argnum -= 2;
	}

      /* Determine if VAL is a null pointer constant before folding it.  */
      ତାର୍କିକ npc = null_pointer_constant_p (val);

      /* If there is excess precision and a prototype, convert once to
	 the required type rather than converting via the semantic
	 type.  Likewise without a prototype a float value represented
	 as long double should be converted once to double.  But for
	 type-generic classification functions excess precision must
	 be removed here.  */
      ଯଦି (ବୃକ୍ଷ_CODE (val) == EXCESS_PRECISION_ପଦସମଷ୍ଟି
	  && (type || !type_generic || !type_generic_remove_excess_precision))
	{
	  val = ବୃକ୍ଷ_OPERAND (val, 0);
	  excess_precision = ସତ୍ୟ;
	}
      val = c_fully_fold (val, ମିଥ୍ୟା, ଖାଲି);
      STRIP_TYPE_NOPS (val);

      val = require_complete_type (ploc, val);

      /* Some floating-point arguments must be promoted to double when
	 no type is specified by a prototype.  This applies to
	 arguments of type float, and to architecture-specific types
	 (ARM __fp16), but not to _FloatN or _FloatNx types.  */
      ତାର୍କିକ promote_float_arg = ମିଥ୍ୟା;
      ଯଦି (type == NULL_ବୃକ୍ଷ
	  && ବୃକ୍ଷ_CODE (valtype) == REAL_TYPE
	  && (TYPE_PRECISION (valtype)
	      <= TYPE_PRECISION (double_type_ଗଣ୍ଠି))
	  && TYPE_MAIN_VARIANT (valtype) != double_type_ଗଣ୍ଠି
	  && TYPE_MAIN_VARIANT (valtype) != long_double_type_ଗଣ୍ଠି
	  && !DECIMAL_FLOAT_MODE_P (TYPE_MODE (valtype)))
	{
	  /* Promote this argument, unless it has a _FloatN or
	     _FloatNx type.  */
	  promote_float_arg = ସତ୍ୟ;
	  ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < ଅଙ୍କ_FLOATN_NX_TYPES; i++)
	    ଯଦି (TYPE_MAIN_VARIANT (valtype) == FLOATN_NX_TYPE_ଗଣ୍ଠି (i))
	      {
		promote_float_arg = ମିଥ୍ୟା;
		ଭାଙ୍ଗ;
	      }
	  /* Don't promote __bf16 either.  */
	  ଯଦି (TYPE_MAIN_VARIANT (valtype) == bfloat16_type_ଗଣ୍ଠି)
	    promote_float_arg = ମିଥ୍ୟା;
	}

      ଯଦି (type != NULL_ବୃକ୍ଷ)
	{
	  ବୃକ୍ଷ origtype = (!origtypes) ? NULL_ବୃକ୍ଷ : (*origtypes)[parmnum];
	  parmval = convert_argument (ploc, function, fundecl, type, origtype,
				      val, valtype, npc, rname, parmnum, argnum,
				      excess_precision, 0);
	}
      /* A NULLPTR type is just a nullptr always.  */
      ଅନ୍ୟଥା ଯଦି (ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (val)) == NULLPTR_TYPE)
	parmval = omit_one_operand_loc (ploc, ବୃକ୍ଷ_TYPE (val), nullptr_ଗଣ୍ଠି, val);
      ଅନ୍ୟଥା ଯଦି (promote_float_arg)
        {
	  ଯଦି (type_generic)
	    parmval = val;
	  ଅନ୍ୟଥା
	    {
	      /* Convert `float' to `double'.  */
	      ଯଦି (warn_double_promotion && !c_inhibit_evaluation_warnings)
		warning_at (ploc, OPT_Wdouble_promotion,
			    "implicit conversion from %qT to %qT when passing "
			    "argument to function",
			    valtype, double_type_ଗଣ୍ଠି);
	      parmval = convert (double_type_ଗଣ୍ଠି, val);
	    }
	}
      ଅନ୍ୟଥା ଯଦି ((excess_precision && !type_generic)
	       || (type_generic_overflow_p && parmnum == 2)
	       || (type_generic_bit_query && parmnum == 0))
	/* A "double" argument with excess precision being passed
	   without a prototype or in variable arguments.
	   The last argument of __builtin_*_overflow_p should not be
	   promoted, similarly the first argument of
	   __builtin_{clz,ctz,clrsb,ffs,parity,popcount}g.  */
	parmval = convert (valtype, val);
      ଅନ୍ୟଥା ଯଦି ((invalid_func_diag =
		targetm.calls.invalid_arg_for_unprototyped_fn (typelist, fundecl, val)))
	{
	  error (invalid_func_diag);
	  ଫେରନ୍ତୁ -1;
	}
      ଅନ୍ୟଥା ଯଦି (ବୃକ୍ଷ_CODE (val) == ADDR_ପଦସମଷ୍ଟି && reject_gcc_builtin (val))
	{
	  ଫେରନ୍ତୁ -1;
	}
      ଅନ୍ୟଥା
	/* Convert `short' and `char' to full-size `int'.  */
	parmval = default_conversion (val);

      (*ମୂଲ୍ୟଗୁଡ଼ିକ)[parmnum] = parmval;
      ଯଦି (parmval == error_mark_ଗଣ୍ଠି)
	error_args = ସତ୍ୟ;

      ଯଦି (!type && builtin_type && ବୃକ୍ଷ_CODE (builtin_type) != VOID_TYPE)
	{
	  /* For a call to a built-in function declared without a prototype,
	     perform the conversions from the argument to the expected type
	     but issue warnings rather than errors for any mismatches.
	     Ignore the converted argument and use the PARMVAL obtained
	     above by applying default conversions instead.  */
	  ବୃକ୍ଷ origtype = (!origtypes) ? NULL_ବୃକ୍ଷ : (*origtypes)[parmnum];
	  convert_argument (ploc, function, fundecl, builtin_type, origtype,
			    val, valtype, npc, rname, parmnum, argnum,
			    excess_precision,
			    OPT_Wbuiltin_declaration_mismatch);
	}

      ଯଦି (typetail)
	typetail = ବୃକ୍ଷ_CHAIN (typetail);

      ଯଦି (builtin_typetail)
	builtin_typetail = ବୃକ୍ଷ_CHAIN (builtin_typetail);
    }

  gcc_assert (parmnum == vec_safe_length (ମୂଲ୍ୟଗୁଡ଼ିକ));

  ଯଦି (typetail != NULL_ବୃକ୍ଷ && ବୃକ୍ଷ_ମୂଲ୍ୟ (typetail) != void_type_ଗଣ୍ଠି)
    {
      /* Not enough args.
	 Determine minimum number of arguments required.  */
      ପୂର୍ଣ୍ଣସଂଖ୍ୟା min_expected_ଅଙ୍କ = 0;
      ତାର୍କିକ at_least_p = ମିଥ୍ୟା;
      ବୃକ୍ଷ iter = typelist;
      ଯେତେବେଳେ (ସତ୍ୟ)
	{
	  ଯଦି (!iter)
	    {
	      /* Variadic arguments; stop iterating.  */
	      at_least_p = ସତ୍ୟ;
	      ଭାଙ୍ଗ;
	    }
	  ଯଦି (iter == void_list_ଗଣ୍ଠି)
	    /* End of arguments; stop iterating.  */
	    ଭାଙ୍ଗ;
	  ++min_expected_ଅଙ୍କ;
	  iter = ବୃକ୍ଷ_CHAIN (iter);
	}
      auto_diagnostic_group d;
      ପୂର୍ଣ୍ଣସଂଖ୍ୟା actual_ଅଙ୍କ = vec_safe_length (ମୂଲ୍ୟଗୁଡ଼ିକ);
      error_at (loc,
		at_least_p
		? G_("too few arguments to function %qE; expected at least %i, have %i")
		: G_("too few arguments to function %qE; expected %i, have %i"),
		function, min_expected_ଅଙ୍କ, actual_ଅଙ୍କ);
      inform_declaration (fundecl, function);
      ଫେରନ୍ତୁ -1;
    }

  ଯଦି (builtin_typetail && ବୃକ୍ଷ_ମୂଲ୍ୟ (builtin_typetail) != void_type_ଗଣ୍ଠି)
    {
      unsigned nargs = parmnum;
      ପାଇଁ (ବୃକ୍ଷ t = builtin_typetail; t; t = ବୃକ୍ଷ_CHAIN (t))
	++nargs;

      auto_diagnostic_group d;
      ଯଦି (warning_at (loc, OPT_Wbuiltin_declaration_mismatch,
		      "too few arguments to built-in function %qE "
		      "expecting %u", function, nargs - 1))
	inform_declaration (fundecl, function);
    }

  ଫେରନ୍ତୁ error_args ? -1 : (ପୂର୍ଣ୍ଣସଂଖ୍ୟା) parmnum;
}

/* This is the entry point used by the parser to build unary operators
   in the input.  CODE, a tree_code, specifies the unary operator, and
   ARG is the operand.  For unary plus, the C parser currently uses
   CONVERT_EXPR for code.

   LOC is the location to use for the tree generated.
*/

ସଂରଚନା c_ପଦସମଷ୍ଟି
parser_build_unary_op (location_t loc, ଗଣନା ବୃକ୍ଷ_code code, ସଂରଚନା c_ପଦସମଷ୍ଟି arg)
{
  ସଂରଚନା c_ପଦସମଷ୍ଟି result;

  result.original_code = code;
  result.original_type = ଖାଲି;
  result.m_decimal = 0;

  ଯଦି (reject_gcc_builtin (arg.ମୂଲ୍ୟ))
    {
      result.ମୂଲ୍ୟ = error_mark_ଗଣ୍ଠି;
    }
  ଅନ୍ୟଥା
    {
      result.ମୂଲ୍ୟ = build_unary_op (loc, code, arg.ମୂଲ୍ୟ, ମିଥ୍ୟା);

      ଯଦି (ବୃକ୍ଷ_OVERFLOW_P (result.ମୂଲ୍ୟ) && !ବୃକ୍ଷ_OVERFLOW_P (arg.ମୂଲ୍ୟ))
	overflow_warning (loc, result.ମୂଲ୍ୟ, arg.ମୂଲ୍ୟ);
    }

  /* We are typically called when parsing a prefix token at LOC acting on
     ARG.  Reflect this by updating the source range of the result to
     start at LOC and end at the end of ARG.  */
  set_c_ପଦସମଷ୍ଟି_source_range (&result,
			   loc, arg.get_finish ());

  ଫେରନ୍ତୁ result;
}

/* Returns true if TYPE is a character type, *not* including wchar_t.  */

ତାର୍କିକ
char_type_p (ବୃକ୍ଷ type)
{
  ଫେରନ୍ତୁ (type == char_type_ଗଣ୍ଠି
	  || type == unsigned_char_type_ଗଣ୍ଠି
	  || type == signed_char_type_ଗଣ୍ଠି
	  || type == char16_type_ଗଣ୍ଠି
	  || type == char32_type_ଗଣ୍ଠି);
}

/* This is the entry point used by the parser to build binary operators
   in the input.  CODE, a tree_code, specifies the binary operator, and
   ARG1 and ARG2 are the operands.  In addition to constructing the
   expression, we check for operands that were written with other binary
   operators in a way that is likely to confuse the user.  ORIG_ARG1 is
   the original first operand for TRUTH_{AND,OR}IF_EXPR before it is
   converted to truth value, otherwise NULL_TREE.

   LOCATION is the location of the binary operator.  */

ସଂରଚନା c_ପଦସମଷ୍ଟି
parser_build_ଦ୍ୱିମିକ_op (location_t location, ଗଣନା ବୃକ୍ଷ_code code,
			ସଂରଚନା c_ପଦସମଷ୍ଟି arg1, ସଂରଚନା c_ପଦସମଷ୍ଟି arg2, ବୃକ୍ଷ orig_arg1)
{
  ସଂରଚନା c_ପଦସମଷ୍ଟି result;
  result.m_decimal = 0;

  ଗଣନା ବୃକ୍ଷ_code code1 = arg1.original_code;
  ଗଣନା ବୃକ୍ଷ_code code2 = arg2.original_code;
  ବୃକ୍ଷ type1 = (arg1.original_type
                ? arg1.original_type
                : ବୃକ୍ଷ_TYPE (arg1.ମୂଲ୍ୟ));
  ବୃକ୍ଷ type2 = (arg2.original_type
                ? arg2.original_type
                : ବୃକ୍ଷ_TYPE (arg2.ମୂଲ୍ୟ));

  result.ମୂଲ୍ୟ = build_ଦ୍ୱିମିକ_op (location, code,
				  arg1.ମୂଲ୍ୟ, arg2.ମୂଲ୍ୟ, ସତ୍ୟ);
  result.original_code = code;
  result.original_type = ଖାଲି;
  result.m_decimal = 0;

  ଯଦି (ବୃକ୍ଷ_CODE (result.ମୂଲ୍ୟ) == ERROR_MARK)
    {
      set_c_ପଦସମଷ୍ଟି_source_range (&result,
			       arg1.get_start (),
			       arg2.get_finish ());
      ଫେରନ୍ତୁ result;
    }

  ଯଦି (location != UNKNOWN_LOCATION)
    protected_set_ପଦସମଷ୍ଟି_location (result.ମୂଲ୍ୟ, location);

  set_c_ପଦସମଷ୍ଟି_source_range (&result,
			   arg1.get_start (),
			   arg2.get_finish ());

  /* Check for cases such as x+y<<z which users are likely
     to misinterpret.  */
  ଯଦି (warn_parentheses)
    warn_about_parentheses (location, code, code1, arg1.ମୂଲ୍ୟ, code2,
			    arg2.ମୂଲ୍ୟ);

  ଯଦି (warn_logical_op)
    warn_logical_operator (location, code, ବୃକ୍ଷ_TYPE (result.ମୂଲ୍ୟ),
			   code1, arg1.ମୂଲ୍ୟ, code2, arg2.ମୂଲ୍ୟ);

  ଯଦି (warn_constant_logical_operand
      && (code == TRUTH_ANDIF_ପଦସମଷ୍ଟି || code == TRUTH_ORIF_ପଦସମଷ୍ଟି)
      && INTEGRAL_NB_TYPE_P (type1)
      && INTEGRAL_NB_TYPE_P (type2))
    {
      ଅଚଳ ଅକ୍ଷର *name = code == TRUTH_ANDIF_ପଦସମଷ୍ଟି ? "&&" : "||";
      ଯଦି (orig_arg1 == NULL_ବୃକ୍ଷ)
	orig_arg1 = arg1.ମୂଲ୍ୟ;
      auto enum_other_than_0_1 = [] (ବୃକ୍ଷ type) {
	ଯଦି (ବୃକ୍ଷ_CODE (type) != ENUMERAL_TYPE)
	  ଫେରନ୍ତୁ ମିଥ୍ୟା;
	ପାଇଁ (ବୃକ୍ଷ l = TYPE_ମୂଲ୍ୟଗୁଡ଼ିକ (type); l; l = ବୃକ୍ଷ_CHAIN (l))
	  {
	    ବୃକ୍ଷ v = DECL_INITIAL (ବୃକ୍ଷ_ମୂଲ୍ୟ (l));
	    ଯଦି (!integer_zerop (v) && !integer_onep (v))
	      ଫେରନ୍ତୁ ସତ୍ୟ;
	  }
	ଫେରନ୍ତୁ ମିଥ୍ୟା;
      };
      auto diagnose_constant_logical_operand = [=] (ବୃକ୍ଷ val, ବୃକ୍ଷ type) {
	ଯଦି (ବୃକ୍ଷ_CODE (val) != INTEGER_CST || integer_zerop (val))
	  ଫେରନ୍ତୁ ମିଥ୍ୟା;
	ଯଦି (integer_onep (val) && !enum_other_than_0_1 (type))
	  ଫେରନ୍ତୁ ମିଥ୍ୟା;
	gcc_rich_location richloc (location);
	richloc.add_fixit_replace (name + 1);
	auto_diagnostic_group d;
	ଯଦି (warning_at (location, OPT_Wconstant_logical_operand,
			"use of logical %qs with constant operand %qE",
			name, val))
	  inform (&richloc, "use %qs for bitwise operation", name + 1);
	ଫେରନ୍ତୁ ସତ୍ୟ;
      };
      ଯଦି (!diagnose_constant_logical_operand (arg2.ମୂଲ୍ୟ, type2))
	diagnose_constant_logical_operand (orig_arg1, type1);
    }

  ଯଦି (warn_tautological_compare)
    {
      ବୃକ୍ଷ lhs = arg1.ମୂଲ୍ୟ;
      ବୃକ୍ଷ rhs = arg2.ମୂଲ୍ୟ;
      ଯଦି (ବୃକ୍ଷ_CODE (lhs) == C_MAYBE_CONST_ପଦସମଷ୍ଟି)
	{
	  ଯଦି (C_MAYBE_CONST_ପଦସମଷ୍ଟି_PRE (lhs) != NULL_ବୃକ୍ଷ
	      && ବୃକ୍ଷ_SIDE_EFFECTS (C_MAYBE_CONST_ପଦସମଷ୍ଟି_PRE (lhs)))
	    lhs = NULL_ବୃକ୍ଷ;
	  ଅନ୍ୟଥା
	    lhs = C_MAYBE_CONST_ପଦସମଷ୍ଟି_ପଦସମଷ୍ଟି (lhs);
	}
      ଯଦି (ବୃକ୍ଷ_CODE (rhs) == C_MAYBE_CONST_ପଦସମଷ୍ଟି)
	{
	  ଯଦି (C_MAYBE_CONST_ପଦସମଷ୍ଟି_PRE (rhs) != NULL_ବୃକ୍ଷ
	      && ବୃକ୍ଷ_SIDE_EFFECTS (C_MAYBE_CONST_ପଦସମଷ୍ଟି_PRE (rhs)))
	    rhs = NULL_ବୃକ୍ଷ;
	  ଅନ୍ୟଥା
	    rhs = C_MAYBE_CONST_ପଦସମଷ୍ଟି_ପଦସମଷ୍ଟି (rhs);
	}
      ଯଦି (lhs != NULL_ବୃକ୍ଷ && rhs != NULL_ବୃକ୍ଷ)
	warn_tautological_cmp (location, code, lhs, rhs);
    }

  ଯଦି (warn_logical_not_paren
      && ବୃକ୍ଷ_CODE_CLASS (code) == tcc_comparison
      && code1 == TRUTH_NOT_ପଦସମଷ୍ଟି
      && code2 != TRUTH_NOT_ପଦସମଷ୍ଟି
      /* Avoid warning for !!x == y.  */
      && (ବୃକ୍ଷ_CODE (arg1.ମୂଲ୍ୟ) != NE_ପଦସମଷ୍ଟି
	  || !integer_zerop (ବୃକ୍ଷ_OPERAND (arg1.ମୂଲ୍ୟ, 1))))
    {
      /* Avoid warning for !b == y where b has _Bool type.  */
      ବୃକ୍ଷ t = integer_zero_ଗଣ୍ଠି;
      ଯଦି (ବୃକ୍ଷ_CODE (arg1.ମୂଲ୍ୟ) == EQ_ପଦସମଷ୍ଟି
	  && integer_zerop (ବୃକ୍ଷ_OPERAND (arg1.ମୂଲ୍ୟ, 1))
	  && ବୃକ୍ଷ_TYPE (ବୃକ୍ଷ_OPERAND (arg1.ମୂଲ୍ୟ, 0)) == integer_type_ଗଣ୍ଠି)
	{
	  t = ବୃକ୍ଷ_OPERAND (arg1.ମୂଲ୍ୟ, 0);
	  କର
	    {
	      ଯଦି (ବୃକ୍ଷ_TYPE (t) != integer_type_ଗଣ୍ଠି)
		ଭାଙ୍ଗ;
	      ଯଦି (ବୃକ୍ଷ_CODE (t) == C_MAYBE_CONST_ପଦସମଷ୍ଟି)
		t = C_MAYBE_CONST_ପଦସମଷ୍ଟି_ପଦସମଷ୍ଟି (t);
	      ଅନ୍ୟଥା ଯଦି (CONVERT_ପଦସମଷ୍ଟି_P (t))
		t = ବୃକ୍ଷ_OPERAND (t, 0);
	      ଅନ୍ୟଥା
		ଭାଙ୍ଗ;
	    }
	  ଯେତେବେଳେ (1);
	}
      ଯଦି (!C_BOOLEAN_TYPE_P (ବୃକ୍ଷ_TYPE (t)))
	warn_logical_not_parentheses (location, code, arg1.ମୂଲ୍ୟ, arg2.ମୂଲ୍ୟ);
    }

  /* Warn about comparisons against string literals, with the exception
     of testing for equality or inequality of a string literal with NULL.  */
  ଯଦି (code == EQ_ପଦସମଷ୍ଟି || code == NE_ପଦସମଷ୍ଟି)
    {
      ଯଦି ((code1 == STRING_CST
	   && !integer_zerop (ବୃକ୍ଷ_strip_nop_conversions (arg2.ମୂଲ୍ୟ)))
	  || (code2 == STRING_CST
	      && !integer_zerop (ବୃକ୍ଷ_strip_nop_conversions (arg1.ମୂଲ୍ୟ))))
	warning_at (location, OPT_Waddress,
		    "comparison with string literal results in unspecified behavior");
      /* Warn for ptr == '\0', it's likely that it should've been ptr[0].  */
      ଯଦି (POINTER_TYPE_P (type1)
	  && null_pointer_constant_p (arg2.ମୂଲ୍ୟ)
	  && char_type_p (type2))
	{
	  auto_diagnostic_group d;
	  ଯଦି (warning_at (location, OPT_Wpointer_compare,
			    "comparison between pointer and zero character "
			    "constant"))
	    inform (arg1.get_start (),
		      "did you mean to dereference the pointer?");
	}
      ଅନ୍ୟଥା ଯଦି (POINTER_TYPE_P (type2)
	       && null_pointer_constant_p (arg1.ମୂଲ୍ୟ)
	       && char_type_p (type1))
	{
	  auto_diagnostic_group d;
	  ଯଦି (warning_at (location, OPT_Wpointer_compare,
			    "comparison between pointer and zero character "
			    "constant"))
	    inform (arg2.get_start (),
		      "did you mean to dereference the pointer?");
	}
    }
  ଅନ୍ୟଥା ଯଦି (ବୃକ୍ଷ_CODE_CLASS (code) == tcc_comparison
	   && (code1 == STRING_CST || code2 == STRING_CST))
    warning_at (location, OPT_Waddress,
		"comparison with string literal results in unspecified "
		"behavior");

  ଯଦି (warn_zero_as_null_pointer_constant
      && c_inhibit_evaluation_warnings == 0
      && ବୃକ୍ଷ_CODE_CLASS (code) == tcc_comparison)
    {
      ଯଦି ((ବୃକ୍ଷ_CODE (type1) == POINTER_TYPE
	   || ବୃକ୍ଷ_CODE (type1) == NULLPTR_TYPE)
	  && INTEGRAL_TYPE_P (type2)
	  && null_pointer_constant_p (arg2.ମୂଲ୍ୟ))
	warning_at (arg2.get_location(), OPT_Wzero_as_null_pointer_constant,
		    "zero as null pointer constant");

      ଯଦି ((ବୃକ୍ଷ_CODE (type2) == POINTER_TYPE
	   || ବୃକ୍ଷ_CODE (type2) == NULLPTR_TYPE)
	  && INTEGRAL_TYPE_P (type1)
	  && null_pointer_constant_p (arg1.ମୂଲ୍ୟ))
	warning_at (arg1.get_location(), OPT_Wzero_as_null_pointer_constant,
		    "zero as null pointer constant");
    }

  ଯଦି (warn_array_compare
      && ବୃକ୍ଷ_CODE_CLASS (code) == tcc_comparison
      && ବୃକ୍ଷ_CODE (type1) == ARRAY_TYPE
      && ବୃକ୍ଷ_CODE (type2) == ARRAY_TYPE)
    do_warn_array_compare (location, code, arg1.ମୂଲ୍ୟ, arg2.ମୂଲ୍ୟ);

  ଯଦି (ବୃକ୍ଷ_OVERFLOW_P (result.ମୂଲ୍ୟ)
      && !ବୃକ୍ଷ_OVERFLOW_P (arg1.ମୂଲ୍ୟ)
      && !ବୃକ୍ଷ_OVERFLOW_P (arg2.ମୂଲ୍ୟ))
    overflow_warning (location, result.ମୂଲ୍ୟ);

  /* Warn about comparisons of different enum types.  */
  ଯଦି (warn_enum_compare
      && ବୃକ୍ଷ_CODE_CLASS (code) == tcc_comparison
      && ବୃକ୍ଷ_CODE (type1) == ENUMERAL_TYPE
      && ବୃକ୍ଷ_CODE (type2) == ENUMERAL_TYPE
      && TYPE_MAIN_VARIANT (type1) != TYPE_MAIN_VARIANT (type2))
    warning_at (location, OPT_Wenum_compare,
		"comparison between %qT and %qT",
		type1, type2);

  ଯଦି (warn_xor_used_as_pow
      && code == BIT_XOR_ପଦସମଷ୍ଟି
      && arg1.m_decimal
      && arg2.m_decimal)
    check_for_xor_used_as_pow (arg1.get_location (), arg1.ମୂଲ୍ୟ,
			       location,
			       arg2.get_location (), arg2.ମୂଲ୍ୟ);

  ଫେରନ୍ତୁ result;
}

/* Return a tree for the difference of pointers OP0 and OP1.
   The resulting tree has type ptrdiff_t.  If POINTER_SUBTRACT sanitization is
   enabled, assign to INSTRUMENT_EXPR call to libsanitizer.  */

ସ୍ଥିର ବୃକ୍ଷ
pointer_diff (location_t loc, ବୃକ୍ଷ op0, ବୃକ୍ଷ op1, ବୃକ୍ଷ *instrument_ପଦସମଷ୍ଟି)
{
  ବୃକ୍ଷ restype = ptrdiff_type_ଗଣ୍ଠି;
  ବୃକ୍ଷ result, inttype;

  addr_space_t as0 = TYPE_ADDR_SPACE (ବୃକ୍ଷ_TYPE (ବୃକ୍ଷ_TYPE (op0)));
  addr_space_t as1 = TYPE_ADDR_SPACE (ବୃକ୍ଷ_TYPE (ବୃକ୍ଷ_TYPE (op1)));
  ବୃକ୍ଷ target_type = ବୃକ୍ଷ_TYPE (ବୃକ୍ଷ_TYPE (op0));
  ବୃକ୍ଷ orig_op0 = op0;
  ବୃକ୍ଷ orig_op1 = op1;

  /* If the operands point into different address spaces, we need to
     explicitly convert them to pointers into the common address space
     before we can subtract the numerical address values.  */
  ଯଦି (as0 != as1)
    {
      addr_space_t as_common;
      ବୃକ୍ଷ common_type;

      /* Determine the common superset address space.  This is guaranteed
	 to exist because the caller verified that comp_target_types
	 returned non-zero.  */
      ଯଦି (!addr_space_superset (as0, as1, &as_common))
	gcc_unreachable ();

      common_type = common_pointer_type (ବୃକ୍ଷ_TYPE (op0), ବୃକ୍ଷ_TYPE (op1), NULL_ବୃକ୍ଷ);
      op0 = convert (common_type, op0);
      op1 = convert (common_type, op1);
    }

  /* Determine integer type result of the subtraction.  This will usually
     be the same as the result type (ptrdiff_t), but may need to be a wider
     type if pointers for the address space are wider than ptrdiff_t.  */
  ଯଦି (TYPE_PRECISION (restype) < TYPE_PRECISION (ବୃକ୍ଷ_TYPE (op0)))
    inttype = c_common_type_for_size (TYPE_PRECISION (ବୃକ୍ଷ_TYPE (op0)), 0);
  ଅନ୍ୟଥା
    inttype = restype;

  ଯଦି (VOID_TYPE_P (target_type))
    pedwarn (loc, OPT_Wpointer_arith,
	     "pointer of type %<void *%> used in subtraction");
  ଯଦି (ବୃକ୍ଷ_CODE (target_type) == FUNCTION_TYPE)
    pedwarn (loc, OPT_Wpointer_arith,
	     "pointer to a function used in subtraction");

  ଯଦି (current_function_decl != NULL_ବୃକ୍ଷ
      && sanitize_flags_p (SANITIZE_POINTER_SUBTRACT))
    {
      op0 = save_ପଦସମଷ୍ଟି (c_fully_fold (op0, ମିଥ୍ୟା, ଖାଲି));
      op1 = save_ପଦସମଷ୍ଟି (c_fully_fold (op1, ମିଥ୍ୟା, ଖାଲି));

      ବୃକ୍ଷ tt = builtin_decl_explicit (BUILT_IN_ASAN_POINTER_SUBTRACT);
      *instrument_ପଦସମଷ୍ଟି = build_call_ପଦସମଷ୍ଟି_loc (loc, tt, 2, op0, op1);
    }

  /* First do the subtraction, then build the divide operator
     and only convert at the very end.
     Do not do default conversions in case restype is a short type.  */

  /* POINTER_DIFF_EXPR requires a signed integer type of the same size as
     pointers.  If some platform cannot provide that, or has a larger
     ptrdiff_type to support differences larger than half the address
     space, cast the pointers to some larger integer type and do the
     computations in that type.  */
  ଯଦି (TYPE_PRECISION (inttype) > TYPE_PRECISION (ବୃକ୍ଷ_TYPE (op0)))
    op0 = build_ଦ୍ୱିମିକ_op (loc, MINUS_ପଦସମଷ୍ଟି, convert (inttype, op0),
			   convert (inttype, op1), ମିଥ୍ୟା);
  ଅନ୍ୟଥା
    {
      /* Cast away qualifiers.  */
      op0 = convert (c_common_type (ବୃକ୍ଷ_TYPE (op0), ବୃକ୍ଷ_TYPE (op0)), op0);
      op1 = convert (c_common_type (ବୃକ୍ଷ_TYPE (op1), ବୃକ୍ଷ_TYPE (op1)), op1);
      op0 = build2_loc (loc, POINTER_DIFF_ପଦସମଷ୍ଟି, inttype, op0, op1);
    }

  /* This generates an error if op1 is pointer to incomplete type.  */
  ଯଦି (!COMPLETE_OR_VOID_TYPE_P (ବୃକ୍ଷ_TYPE (ବୃକ୍ଷ_TYPE (orig_op1))))
    error_at (loc, "arithmetic on pointer to an incomplete type");
  ଅନ୍ୟଥା ଯଦି (verify_type_context (loc, TCTX_POINTER_ARITH,
				ବୃକ୍ଷ_TYPE (ବୃକ୍ଷ_TYPE (orig_op0))))
    verify_type_context (loc, TCTX_POINTER_ARITH,
			 ବୃକ୍ଷ_TYPE (ବୃକ୍ଷ_TYPE (orig_op1)));

  op1 = c_size_in_bytes (target_type);

  ଯଦି (pointer_to_zero_sized_aggr_p (ବୃକ୍ଷ_TYPE (orig_op1)))
    error_at (loc, "arithmetic on pointer to an empty aggregate");

  /* Divide by the size, in easiest possible way.  */
  result = fold_build2_loc (loc, EXACT_DIV_ପଦସମଷ୍ଟି, inttype,
			    op0, convert (inttype, op1));

  /* Convert to final result type if necessary.  */
  ଫେରନ୍ତୁ convert (restype, result);
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

ସ୍ଥିର ବୃକ୍ଷ
build_atomic_assign (location_t loc, ବୃକ୍ଷ lhs, ଗଣନା ବୃକ୍ଷ_code modifycode,
		     ବୃକ୍ଷ rhs, ତାର୍କିକ return_old_p)
{
  ବୃକ୍ଷ fndecl, func_call;
  vec<ବୃକ୍ଷ, va_gc> *params;
  ବୃକ୍ଷ val, nonatomic_lhs_type, nonatomic_rhs_type, newval, newval_addr;
  ବୃକ୍ଷ old, old_addr;
  ବୃକ୍ଷ compound_stmt = NULL_ବୃକ୍ଷ;
  ବୃକ୍ଷ stmt, goto_stmt;
  ବୃକ୍ଷ loop_label, loop_decl, done_label, done_decl;

  ବୃକ୍ଷ lhs_type = ବୃକ୍ଷ_TYPE (lhs);
  ବୃକ୍ଷ lhs_addr = build_unary_op (loc, ADDR_ପଦସମଷ୍ଟି, lhs, ମିଥ୍ୟା);
  ବୃକ୍ଷ seq_cst = build_int_cst (integer_type_ଗଣ୍ଠି, MEMMODEL_SEQ_CST);
  ବୃକ୍ଷ rhs_semantic_type = ବୃକ୍ଷ_TYPE (rhs);
  ବୃକ୍ଷ nonatomic_rhs_semantic_type;
  ବୃକ୍ଷ rhs_type;

  gcc_assert (TYPE_ATOMIC (lhs_type));

  ଯଦି (return_old_p)
    gcc_assert (modifycode == PLUS_ପଦସମଷ୍ଟି || modifycode == MINUS_ପଦସମଷ୍ଟି);

  /* Allocate enough vector items for a compare_exchange.  */
  vec_alloc (params, 6);

  /* Create a compound statement to hold the sequence of statements
     with a loop.  */
  ଯଦି (modifycode != NOP_ପଦସମଷ୍ଟି)
    {
      compound_stmt = c_begin_compound_stmt (ମିଥ୍ୟା);

      /* For consistency with build_modify_expr on non-_Atomic,
	 mark the lhs as read.  Also, it would be very hard to match
	 such expressions in mark_exp_read.  */
      mark_exp_read (lhs);
    }

  /* Remove any excess precision (which is only present here in the
     case of compound assignments).  */
  ଯଦି (ବୃକ୍ଷ_CODE (rhs) == EXCESS_PRECISION_ପଦସମଷ୍ଟି)
    {
      gcc_assert (modifycode != NOP_ପଦସମଷ୍ଟି);
      rhs = ବୃକ୍ଷ_OPERAND (rhs, 0);
    }
  rhs_type = ବୃକ୍ଷ_TYPE (rhs);

  /* Fold the RHS if it hasn't already been folded.  */
  ଯଦି (modifycode != NOP_ପଦସମଷ୍ଟି)
    rhs = c_fully_fold (rhs, ମିଥ୍ୟା, ଖାଲି);

  /* Remove the qualifiers for the rest of the expressions and create
     the VAL temp variable to hold the RHS.  */
  nonatomic_lhs_type = build_qualified_type (lhs_type, TYPE_UNQUALIFIED);
  nonatomic_rhs_type = build_qualified_type (rhs_type, TYPE_UNQUALIFIED);
  nonatomic_rhs_semantic_type = build_qualified_type (rhs_semantic_type,
						      TYPE_UNQUALIFIED);
  val = create_tmp_var_raw (nonatomic_rhs_type);
  ବୃକ୍ଷ_ADDRESSABLE (val) = 1;
  suppress_warning (val);
  rhs = build4 (TARGET_ପଦସମଷ୍ଟି, nonatomic_rhs_type, val, rhs, NULL_ବୃକ୍ଷ,
		NULL_ବୃକ୍ଷ);
  ବୃକ୍ଷ_SIDE_EFFECTS (rhs) = 1;
  SET_ପଦସମଷ୍ଟି_LOCATION (rhs, loc);
  ଯଦି (modifycode != NOP_ପଦସମଷ୍ଟି)
    add_stmt (rhs);

  /* NOP_EXPR indicates it's a straight store of the RHS. Simply issue
     an atomic_store.  */
  ଯଦି (modifycode == NOP_ପଦସମଷ୍ଟି)
    {
      compound_stmt = rhs;
      /* Build __atomic_store (&lhs, &val, SEQ_CST)  */
      rhs = build_unary_op (loc, ADDR_ପଦସମଷ୍ଟି, val, ମିଥ୍ୟା);
      fndecl = builtin_decl_explicit (BUILT_IN_ATOMIC_STORE);
      params->quick_ଠେଲ (lhs_addr);
      params->quick_ଠେଲ (rhs);
      params->quick_ଠେଲ (seq_cst);
      func_call = c_build_function_call_vec (loc, vNULL, fndecl, params, ଖାଲି);

      compound_stmt = build2 (COMPOUND_ପଦସମଷ୍ଟି, void_type_ଗଣ୍ଠି,
			      compound_stmt, func_call);

      /* VAL is the value which was stored, return a COMPOUND_STMT of
	 the statement and that value.  */
      ଫେରନ୍ତୁ build2 (COMPOUND_ପଦସମଷ୍ଟି, nonatomic_lhs_type, compound_stmt, val);
    }

  /* Attempt to implement the atomic operation as an __atomic_fetch_* or
     __atomic_*_fetch built-in rather than a CAS loop.  atomic_bool type
     isn't applicable for such builtins.  ??? Do we want to handle enums?  */
  ଯଦି ((ବୃକ୍ଷ_CODE (lhs_type) == INTEGER_TYPE || POINTER_TYPE_P (lhs_type))
      && ବୃକ୍ଷ_CODE (rhs_type) == INTEGER_TYPE)
    {
      built_in_function fncode;
      ବାଛ (modifycode)
	{
	ସ୍ଥିତି PLUS_ପଦସମଷ୍ଟି:
	ସ୍ଥିତି POINTER_PLUS_ପଦସମଷ୍ଟି:
	  fncode = (return_old_p
		    ? BUILT_IN_ATOMIC_FETCH_ADD_N
		    : BUILT_IN_ATOMIC_ADD_FETCH_N);
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି MINUS_ପଦସମଷ୍ଟି:
	  fncode = (return_old_p
		    ? BUILT_IN_ATOMIC_FETCH_SUB_N
		    : BUILT_IN_ATOMIC_SUB_FETCH_N);
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି BIT_AND_ପଦସମଷ୍ଟି:
	  fncode = (return_old_p
		    ? BUILT_IN_ATOMIC_FETCH_AND_N
		    : BUILT_IN_ATOMIC_AND_FETCH_N);
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି BIT_IOR_ପଦସମଷ୍ଟି:
	  fncode = (return_old_p
		    ? BUILT_IN_ATOMIC_FETCH_OR_N
		    : BUILT_IN_ATOMIC_OR_FETCH_N);
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି BIT_XOR_ପଦସମଷ୍ଟି:
	  fncode = (return_old_p
		    ? BUILT_IN_ATOMIC_FETCH_XOR_N
		    : BUILT_IN_ATOMIC_XOR_FETCH_N);
	  ଭାଙ୍ଗ;
	ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
	  ଯାଅ cas_loop;
	}

      /* We can only use "_1" through "_16" variants of the atomic fetch
	 built-ins.  */
      unsigned HOST_WIDE_INT size = ବୃକ୍ଷ_to_uhwi (TYPE_SIZE_UNIT (lhs_type));
      ଯଦି (size != 1 && size != 2 && size != 4 && size != 8 && size != 16)
	ଯାଅ cas_loop;

      /* If this is a pointer type, we need to multiply by the size of
	 the pointer target type.  */
      ଯଦି (POINTER_TYPE_P (lhs_type))
	{
	  ଯଦି (!COMPLETE_TYPE_P (ବୃକ୍ଷ_TYPE (lhs_type))
	      /* ??? This would introduce -Wdiscarded-qualifiers
		 warning: __atomic_fetch_* expect volatile void *
		 type as the first argument.  (Assignments between
		 atomic and non-atomic objects are OK.) */
	      || TYPE_RESTRICT (lhs_type))
	    ଯାଅ cas_loop;
	  ବୃକ୍ଷ sz = TYPE_SIZE_UNIT (ବୃକ୍ଷ_TYPE (lhs_type));
	  rhs = fold_build2_loc (loc, MULT_ପଦସମଷ୍ଟି, ptrdiff_type_ଗଣ୍ଠି,
				 convert (ptrdiff_type_ଗଣ୍ଠି, rhs),
				 convert (ptrdiff_type_ଗଣ୍ଠି, sz));
	}

      /* Build __atomic_fetch_* (&lhs, &val, SEQ_CST), or
	 __atomic_*_fetch (&lhs, &val, SEQ_CST).  */
      fndecl = builtin_decl_explicit (fncode);
      params->quick_ଠେଲ (lhs_addr);
      params->quick_ଠେଲ (rhs);
      params->quick_ଠେଲ (seq_cst);
      func_call = c_build_function_call_vec (loc, vNULL, fndecl, params, ଖାଲି);

      newval = create_tmp_var_raw (nonatomic_lhs_type);
      ବୃକ୍ଷ_ADDRESSABLE (newval) = 1;
      suppress_warning (newval);
      rhs = build4 (TARGET_ପଦସମଷ୍ଟି, nonatomic_lhs_type, newval, func_call,
		    NULL_ବୃକ୍ଷ, NULL_ବୃକ୍ଷ);
      SET_ପଦସମଷ୍ଟି_LOCATION (rhs, loc);
      add_stmt (rhs);

      /* Finish the compound statement.  */
      compound_stmt = c_end_compound_stmt (loc, compound_stmt, ମିଥ୍ୟା);

      /* NEWVAL is the value which was stored, return a COMPOUND_STMT of
	 the statement and that value.  */
      ଫେରନ୍ତୁ build2 (COMPOUND_ପଦସମଷ୍ଟି, nonatomic_lhs_type, compound_stmt, newval);
    }

cas_loop:
  /* Create the variables and labels required for the op= form.  */
  old = create_tmp_var_raw (nonatomic_lhs_type);
  old_addr = build_unary_op (loc, ADDR_ପଦସମଷ୍ଟି, old, ମିଥ୍ୟା);
  ବୃକ୍ଷ_ADDRESSABLE (old) = 1;
  suppress_warning (old);

  newval = create_tmp_var_raw (nonatomic_lhs_type);
  newval_addr = build_unary_op (loc, ADDR_ପଦସମଷ୍ଟି, newval, ମିଥ୍ୟା);
  ବୃକ୍ଷ_ADDRESSABLE (newval) = 1;
  suppress_warning (newval);

  loop_decl = create_artificial_label (loc);
  loop_label = build1 (LABEL_ପଦସମଷ୍ଟି, void_type_ଗଣ୍ଠି, loop_decl);

  done_decl = create_artificial_label (loc);
  done_label = build1 (LABEL_ପଦସମଷ୍ଟି, void_type_ଗଣ୍ଠି, done_decl);

  /* __atomic_load (addr, &old, SEQ_CST).  */
  fndecl = builtin_decl_explicit (BUILT_IN_ATOMIC_LOAD);
  params->quick_ଠେଲ (lhs_addr);
  params->quick_ଠେଲ (old_addr);
  params->quick_ଠେଲ (seq_cst);
  func_call = c_build_function_call_vec (loc, vNULL, fndecl, params, ଖାଲି);
  old = build4 (TARGET_ପଦସମଷ୍ଟି, nonatomic_lhs_type, old, func_call, NULL_ବୃକ୍ଷ,
		NULL_ବୃକ୍ଷ);
  add_stmt (old);
  params->truncate (0);

  /* Create the expressions for floating-point environment
     manipulation, if required.  */
  ତାର୍କିକ need_fenv = (flag_trapping_math
		    && (FLOAT_TYPE_P (lhs_type) || FLOAT_TYPE_P (rhs_type)));
  ବୃକ୍ଷ hold_call = NULL_ବୃକ୍ଷ, clear_call = NULL_ବୃକ୍ଷ, update_call = NULL_ବୃକ୍ଷ;
  ଯଦି (need_fenv)
    targetm.atomic_assign_expand_fenv (&hold_call, &clear_call, &update_call);

  ଯଦି (hold_call)
    add_stmt (hold_call);

  /* loop:  */
  add_stmt (loop_label);

  /* newval = old + val;  */
  ଯଦି (rhs_type != rhs_semantic_type)
    val = build1 (EXCESS_PRECISION_ପଦସମଷ୍ଟି, nonatomic_rhs_semantic_type, val);
  rhs = build_ଦ୍ୱିମିକ_op (loc, modifycode,
			 convert_lvalue_to_rvalue (loc, old, ସତ୍ୟ, ସତ୍ୟ),
			 val, ସତ୍ୟ);
  ଯଦି (ବୃକ୍ଷ_CODE (rhs) == EXCESS_PRECISION_ପଦସମଷ୍ଟି)
    {
      ବୃକ୍ଷ eptype = ବୃକ୍ଷ_TYPE (rhs);
      rhs = c_fully_fold (ବୃକ୍ଷ_OPERAND (rhs, 0), ମିଥ୍ୟା, ଖାଲି);
      rhs = build1 (EXCESS_PRECISION_ପଦସମଷ୍ଟି, eptype, rhs);
    }
  ଅନ୍ୟଥା
    rhs = c_fully_fold (rhs, ମିଥ୍ୟା, ଖାଲି);
  rhs = convert_for_assignment (loc, UNKNOWN_LOCATION, nonatomic_lhs_type,
				rhs, NULL_ବୃକ୍ଷ, ic_assign, ମିଥ୍ୟା, NULL_ବୃକ୍ଷ,
				NULL_ବୃକ୍ଷ, 0);
  /* The temporary variable for NEWVAL is only gimplified correctly (in
     particular, given a DECL_CONTEXT) if used in a TARGET_EXPR.  To avoid
     subsequent ICEs in nested function processing after an error, ensure such
     a TARGET_EXPR is built even after an error.  */
  ଯଦି (rhs == error_mark_ଗଣ୍ଠି)
    rhs = old;
  rhs = build4 (TARGET_ପଦସମଷ୍ଟି, nonatomic_lhs_type, newval, rhs, NULL_ବୃକ୍ଷ,
		NULL_ବୃକ୍ଷ);
  SET_ପଦସମଷ୍ଟି_LOCATION (rhs, loc);
  add_stmt (rhs);

  /* if (__atomic_compare_exchange (addr, &old, &new, false, SEQ_CST, SEQ_CST))
       goto done;  */
  fndecl = builtin_decl_explicit (BUILT_IN_ATOMIC_COMPARE_EXCHANGE);
  params->quick_ଠେଲ (lhs_addr);
  params->quick_ଠେଲ (old_addr);
  params->quick_ଠେଲ (newval_addr);
  params->quick_ଠେଲ (integer_zero_ଗଣ୍ଠି);
  params->quick_ଠେଲ (seq_cst);
  params->quick_ଠେଲ (seq_cst);
  func_call = c_build_function_call_vec (loc, vNULL, fndecl, params, ଖାଲି);

  goto_stmt = build1 (GOTO_ପଦସମଷ୍ଟି, void_type_ଗଣ୍ଠି, done_decl);
  SET_ପଦସମଷ୍ଟି_LOCATION (goto_stmt, loc);

  stmt = build3 (COND_ପଦସମଷ୍ଟି, void_type_ଗଣ୍ଠି, func_call, goto_stmt, NULL_ବୃକ୍ଷ);
  SET_ପଦସମଷ୍ଟି_LOCATION (stmt, loc);
  add_stmt (stmt);

  ଯଦି (clear_call)
    add_stmt (clear_call);

  /* goto loop;  */
  goto_stmt  = build1 (GOTO_ପଦସମଷ୍ଟି, void_type_ଗଣ୍ଠି, loop_decl);
  SET_ପଦସମଷ୍ଟି_LOCATION (goto_stmt, loc);
  add_stmt (goto_stmt);

  /* done:  */
  add_stmt (done_label);

  ଯଦି (update_call)
    add_stmt (update_call);

  /* Finish the compound statement.  */
  compound_stmt = c_end_compound_stmt (loc, compound_stmt, ମିଥ୍ୟା);

  /* NEWVAL is the value that was successfully stored, return a
     COMPOUND_EXPR of the statement and the appropriate value.  */
  ଫେରନ୍ତୁ build2 (COMPOUND_ପଦସମଷ୍ଟି, nonatomic_lhs_type, compound_stmt,
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

ବୃକ୍ଷ
build_unary_op (location_t location, ଗଣନା ବୃକ୍ଷ_code code, ବୃକ୍ଷ xarg,
		ତାର୍କିକ noconvert)
{
  /* No default_conversion here.  It causes trouble for ADDR_EXPR.  */
  ବୃକ୍ଷ arg = xarg;
  ବୃକ୍ଷ argtype = NULL_ବୃକ୍ଷ;
  ଗଣନା ବୃକ୍ଷ_code typecode;
  ବୃକ୍ଷ val;
  ବୃକ୍ଷ ret = error_mark_ଗଣ୍ଠି;
  ବୃକ୍ଷ eptype = NULL_ବୃକ୍ଷ;
  ଅଚଳ ଅକ୍ଷର *invalid_op_diag;

  /* If ARG is wrapped in a call to .ACCESS_WITH_SIZE — created when the
     C parser rvalue-converts a counted_by-annotated member access (see
     PR123569) — unwrap it here.  Unary operators that consume an rvalue
     (!, -, +) read the value itself rather than dereferencing into the
     pointed-to data, so the bounds-checking wrapper is unnecessary and
     would otherwise reach build_unary_op while it is not equipped to
     handle the wrapped form.  PR123569 fixed the ++/-- side of this by
     suppressing wrapper creation in the parser; the rvalue-consuming
     ops still receive the wrapper and need to strip it here.  */
  ଯଦି (is_access_with_size_p (arg))
    xarg = arg = get_ref_from_access_with_size (arg);

  gcc_checking_assert (!is_access_with_size_p (arg));

  ତାର୍କିକ int_operands = ପଦସମଷ୍ଟି_INT_CONST_OPERANDS (xarg);
  ଯଦି (int_operands)
    arg = remove_c_maybe_const_ପଦସମଷ୍ଟି (arg);

  ଯଦି (code != ADDR_ପଦସମଷ୍ଟି)
    arg = require_complete_type (location, arg);

  typecode = ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (arg));
  ଯଦି (typecode == ERROR_MARK)
    ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
  ଯଦି (typecode == ENUMERAL_TYPE || typecode == BOOLEAN_TYPE)
    typecode = INTEGER_TYPE;

  ଯଦି ((invalid_op_diag
       = targetm.invalid_unary_op (code, ବୃକ୍ଷ_TYPE (xarg))))
    {
      error_at (location, invalid_op_diag);
      ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
    }

  ଯଦି (ବୃକ୍ଷ_CODE (arg) == EXCESS_PRECISION_ପଦସମଷ୍ଟି)
    {
      eptype = ବୃକ୍ଷ_TYPE (arg);
      arg = ବୃକ୍ଷ_OPERAND (arg, 0);
    }

  ବାଛ (code)
    {
    ସ୍ଥିତି CONVERT_ପଦସମଷ୍ଟି:
      /* This is used for unary plus, because a CONVERT_EXPR
	 is enough to prevent anybody from looking inside for
	 associativity, but won't generate any code.  */
      ଯଦି (!(typecode == INTEGER_TYPE || typecode == REAL_TYPE
	    || typecode == FIXED_POINT_TYPE || typecode == COMPLEX_TYPE
	    || typecode == BITINT_TYPE
	    || gnu_vector_type_p (ବୃକ୍ଷ_TYPE (arg))))
	{
	  error_at (location, "wrong type argument to unary plus");
	  ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
	}
      ଅନ୍ୟଥା ଯଦି (!noconvert)
	arg = default_conversion (arg);
      arg = non_lvalue_loc (location, arg);
      ଭାଙ୍ଗ;

    ସ୍ଥିତି NEGATE_ପଦସମଷ୍ଟି:
      ଯଦି (!(typecode == INTEGER_TYPE || typecode == REAL_TYPE
	    || typecode == FIXED_POINT_TYPE || typecode == COMPLEX_TYPE
	    || typecode == BITINT_TYPE
	    || gnu_vector_type_p (ବୃକ୍ଷ_TYPE (arg))))
	{
	  error_at (location, "wrong type argument to unary minus");
	  ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
	}
      ଅନ୍ୟଥା ଯଦି (!noconvert)
	arg = default_conversion (arg);
      ଭାଙ୍ଗ;

    ସ୍ଥିତି BIT_NOT_ପଦସମଷ୍ଟି:
      /* ~ works on integer types and non float vectors. */
      ଯଦି (typecode == INTEGER_TYPE
	  || typecode == BITINT_TYPE
	  || (gnu_vector_type_p (ବୃକ୍ଷ_TYPE (arg))
	      && !VECTOR_FLOAT_TYPE_P (ବୃକ୍ଷ_TYPE (arg))))
	{
	  ବୃକ୍ଷ e = arg;

	  /* Warn if the expression has boolean value.  */
	  ଯେତେବେଳେ (ବୃକ୍ଷ_CODE (e) == COMPOUND_ପଦସମଷ୍ଟି)
	    e = ବୃକ୍ଷ_OPERAND (e, 1);

	  ଯଦି ((C_BOOLEAN_TYPE_P (ବୃକ୍ଷ_TYPE (arg))
	       || truth_ମୂଲ୍ୟ_p (ବୃକ୍ଷ_CODE (e))))
	    {
	      auto_diagnostic_group d;
	      ଯଦି (warning_at (location, OPT_Wbool_operation,
				"%<~%> on a boolean expression"))
		{
		  gcc_rich_location richloc (location);
		  richloc.add_fixit_ଭର୍ତ୍ତି_before (location, "!");
		  inform (&richloc, "did you mean to use logical not?");
		}
	    }
	  ଯଦି (!noconvert)
	    arg = default_conversion (arg);
	}
      ଅନ୍ୟଥା ଯଦି (typecode == COMPLEX_TYPE)
	{
	  code = CONJ_ପଦସମଷ୍ଟି;
	  pedwarn (location, OPT_Wpedantic,
		   "ISO C does not support %<~%> for complex conjugation");
	  ଯଦି (!noconvert)
	    arg = default_conversion (arg);
	}
      ଅନ୍ୟଥା
	{
	  error_at (location, "wrong type argument to bit-complement");
	  ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
	}
      ଭାଙ୍ଗ;

    ସ୍ଥିତି ABS_ପଦସମଷ୍ଟି:
      ଯଦି (!(typecode == INTEGER_TYPE || typecode == REAL_TYPE))
	{
	  error_at (location, "wrong type argument to abs");
	  ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
	}
      ଅନ୍ୟଥା ଯଦି (!noconvert)
	arg = default_conversion (arg);
      ଭାଙ୍ଗ;

    ସ୍ଥିତି ABSU_ପଦସମଷ୍ଟି:
      ଯଦି (!(typecode == INTEGER_TYPE))
	{
	  error_at (location, "wrong type argument to absu");
	  ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
	}
      ଅନ୍ୟଥା ଯଦି (!noconvert)
	arg = default_conversion (arg);
      ଭାଙ୍ଗ;

    ସ୍ଥିତି CONJ_ପଦସମଷ୍ଟି:
      /* Conjugating a real value is a no-op, but allow it anyway.  */
      ଯଦି (!(typecode == INTEGER_TYPE || typecode == REAL_TYPE
	    || typecode == COMPLEX_TYPE))
	{
	  error_at (location, "wrong type argument to conjugation");
	  ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
	}
      ଅନ୍ୟଥା ଯଦି (!noconvert)
	arg = default_conversion (arg);
      ଭାଙ୍ଗ;

    ସ୍ଥିତି TRUTH_NOT_ପଦସମଷ୍ଟି:
      ଯଦି (typecode != INTEGER_TYPE && typecode != FIXED_POINT_TYPE
	  && typecode != REAL_TYPE && typecode != POINTER_TYPE
	  && typecode != COMPLEX_TYPE && typecode != NULLPTR_TYPE
	  && typecode != BITINT_TYPE)
	{
	  error_at (location,
		    "wrong type argument to unary exclamation mark");
	  ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
	}
      ଯଦି (int_operands)
	{
	  arg = c_objc_common_truthvalue_conversion (location, xarg);
	  arg = remove_c_maybe_const_ପଦସମଷ୍ଟି (arg);
	}
      ଅନ୍ୟଥା
	arg = c_objc_common_truthvalue_conversion (location, arg);
      ret = invert_truthvalue_loc (location, arg);
      eptype = NULL_ବୃକ୍ଷ;
      /* If the TRUTH_NOT_EXPR has been folded, reset the location.  */
      ଯଦି (ପଦସମଷ୍ଟି_P (ret) && ପଦସମଷ୍ଟି_HAS_LOCATION (ret))
	location = ପଦସମଷ୍ଟି_LOCATION (ret);
      ଯାଅ return_build_unary_op;

    ସ୍ଥିତି REALPART_ପଦସମଷ୍ଟି:
    ସ୍ଥିତି IMAGPART_ପଦସମଷ୍ଟି:
      ret = build_real_imag_ପଦସମଷ୍ଟି (location, code, arg);
      ଯଦି (ret == error_mark_ଗଣ୍ଠି)
	ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
      ଯଦି (eptype && ବୃକ୍ଷ_CODE (eptype) == COMPLEX_TYPE)
	eptype = ବୃକ୍ଷ_TYPE (eptype);
      ଯାଅ return_build_unary_op;

    ସ୍ଥିତି PREINCREMENT_ପଦସମଷ୍ଟି:
    ସ୍ଥିତି POSTINCREMENT_ପଦସମଷ୍ଟି:
    ସ୍ଥିତି PREDECREMENT_ପଦସମଷ୍ଟି:
    ସ୍ଥିତି POSTDECREMENT_ପଦସମଷ୍ଟି:

      ଯଦି (ବୃକ୍ଷ_CODE (arg) == C_MAYBE_CONST_ପଦସମଷ୍ଟି)
	{
	  ବୃକ୍ଷ inner = build_unary_op (location, code,
				       C_MAYBE_CONST_ପଦସମଷ୍ଟି_ପଦସମଷ୍ଟି (arg),
				       noconvert);
	  ଯଦି (inner == error_mark_ଗଣ୍ଠି)
	    ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
	  ret = build2 (C_MAYBE_CONST_ପଦସମଷ୍ଟି, ବୃକ୍ଷ_TYPE (inner),
			C_MAYBE_CONST_ପଦସମଷ୍ଟି_PRE (arg), inner);
	  gcc_assert (!C_MAYBE_CONST_ପଦସମଷ୍ଟି_INT_OPERANDS (arg));
	  C_MAYBE_CONST_ପଦସମଷ୍ଟି_NON_CONST (ret) = 1;
	  ଯାଅ return_build_unary_op;
	}

      /* Complain about anything that is not a true lvalue.  In
	 Objective-C, skip this check for property_refs.  */
      ଯଦି (!objc_is_property_ref (arg)
	  && !lvalue_or_else (location,
			      arg, ((code == PREINCREMENT_ପଦସମଷ୍ଟି
				     || code == POSTINCREMENT_ପଦସମଷ୍ଟି)
				    ? lv_increment
				    : lv_decrement)))
	ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;

      ଯଦି (warn_cxx_compat && ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (arg)) == ENUMERAL_TYPE)
	{
	  ଯଦି (code == PREINCREMENT_ପଦସମଷ୍ଟି || code == POSTINCREMENT_ପଦସମଷ୍ଟି)
	    warning_at (location, OPT_Wc___compat,
			"increment of enumeration value is invalid in C++");
	  ଅନ୍ୟଥା
	    warning_at (location, OPT_Wc___compat,
			"decrement of enumeration value is invalid in C++");
	}

      ଯଦି (C_BOOLEAN_TYPE_P (ବୃକ୍ଷ_TYPE (arg)))
	{
	  ଯଦି (code == PREINCREMENT_ପଦସମଷ୍ଟି || code == POSTINCREMENT_ପଦସମଷ୍ଟି)
	    warning_at (location, OPT_Wbool_operation,
			"increment of a boolean expression");
	  ଅନ୍ୟଥା
	    warning_at (location, OPT_Wbool_operation,
			"decrement of a boolean expression");
	}

      /* Ensure the argument is fully folded inside any SAVE_EXPR.  */
      arg = c_fully_fold (arg, ମିଥ୍ୟା, ଖାଲି, ସତ୍ୟ);

      ତାର୍କିକ atomic_op;
      atomic_op = really_atomic_lvalue (arg);

      /* Increment or decrement the real part of the value,
	 and don't change the imaginary part.  */
      ଯଦି (typecode == COMPLEX_TYPE)
	{
	  ବୃକ୍ଷ real, imag;

	  pedwarn_c23 (location, OPT_Wpedantic,
		       "ISO C does not support %<++%> and %<--%> on complex "
		       "types before C2Y");

	  ଯଦି (!atomic_op)
	    {
	      arg = stabilize_reference (arg);
	      real = build_unary_op (ପଦସମଷ୍ଟି_LOCATION (arg), REALPART_ପଦସମଷ୍ଟି, arg,
				     ସତ୍ୟ);
	      imag = build_unary_op (ପଦସମଷ୍ଟି_LOCATION (arg), IMAGPART_ପଦସମଷ୍ଟି, arg,
				     ସତ୍ୟ);
	      real = build_unary_op (ପଦସମଷ୍ଟି_LOCATION (arg), code, real, ସତ୍ୟ);
	      ଯଦି (real == error_mark_ଗଣ୍ଠି || imag == error_mark_ଗଣ୍ଠି)
		ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
	      ret = build2 (COMPLEX_ପଦସମଷ୍ଟି, ବୃକ୍ଷ_TYPE (arg),
			    real, imag);
	      ଯାଅ return_build_unary_op;
	    }
	}

      /* Report invalid types.  */

      ଯଦି (typecode != POINTER_TYPE && typecode != FIXED_POINT_TYPE
	  && typecode != INTEGER_TYPE && typecode != REAL_TYPE
	  && typecode != COMPLEX_TYPE && typecode != BITINT_TYPE
	  && !gnu_vector_type_p (ବୃକ୍ଷ_TYPE (arg)))
	{
	  ଯଦି (code == PREINCREMENT_ପଦସମଷ୍ଟି || code == POSTINCREMENT_ପଦସମଷ୍ଟି)
	    error_at (location, "wrong type argument to increment");
	  ଅନ୍ୟଥା
	    error_at (location, "wrong type argument to decrement");

	  ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
	}

      {
	ବୃକ୍ଷ inc;

	argtype = ବୃକ୍ଷ_TYPE (arg);

	/* Compute the increment.  */

	ଯଦି (typecode == POINTER_TYPE)
	  {
	    /* If pointer target is an incomplete type,
	       we just cannot know how to do the arithmetic.  */
	    ଯଦି (!COMPLETE_OR_VOID_TYPE_P (ବୃକ୍ଷ_TYPE (argtype)))
	      {
		ଯଦି (code == PREINCREMENT_ପଦସମଷ୍ଟି || code == POSTINCREMENT_ପଦସମଷ୍ଟି)
		  error_at (location,
			    "increment of pointer to an incomplete type %qT",
			    ବୃକ୍ଷ_TYPE (argtype));
		ଅନ୍ୟଥା
		  error_at (location,
			    "decrement of pointer to an incomplete type %qT",
			    ବୃକ୍ଷ_TYPE (argtype));
	      }
	    ଅନ୍ୟଥା ଯଦି (ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (argtype)) == FUNCTION_TYPE
		     || VOID_TYPE_P (ବୃକ୍ଷ_TYPE (argtype)))
	      {
		ଯଦି (code == PREINCREMENT_ପଦସମଷ୍ଟି || code == POSTINCREMENT_ପଦସମଷ୍ଟି)
		  pedwarn (location, OPT_Wpointer_arith,
			   "wrong type argument to increment");
		ଅନ୍ୟଥା
		  pedwarn (location, OPT_Wpointer_arith,
			   "wrong type argument to decrement");
	      }
	    ଅନ୍ୟଥା
	      verify_type_context (location, TCTX_POINTER_ARITH,
				   ବୃକ୍ଷ_TYPE (argtype));

	    inc = c_size_in_bytes (ବୃକ୍ଷ_TYPE (argtype));
	    inc = convert_to_ptrofftype_loc (location, inc);
	  }
	ଅନ୍ୟଥା ଯଦି (FRACT_MODE_P (TYPE_MODE (argtype)))
	  {
	    /* For signed fract types, we invert ++ to -- or
	       -- to ++, and change inc from 1 to -1, because
	       it is not possible to represent 1 in signed fract constants.
	       For unsigned fract types, the result always overflows and
	       we get an undefined (original) or the maximum value.  */
	    ଯଦି (code == PREINCREMENT_ପଦସମଷ୍ଟି)
	      code = PREDECREMENT_ପଦସମଷ୍ଟି;
	    ଅନ୍ୟଥା ଯଦି (code == PREDECREMENT_ପଦସମଷ୍ଟି)
	      code = PREINCREMENT_ପଦସମଷ୍ଟି;
	    ଅନ୍ୟଥା ଯଦି (code == POSTINCREMENT_ପଦସମଷ୍ଟି)
	      code = POSTDECREMENT_ପଦସମଷ୍ଟି;
	    ଅନ୍ୟଥା /* code == POSTDECREMENT_EXPR  */
	      code = POSTINCREMENT_ପଦସମଷ୍ଟି;

	    inc = integer_minus_one_ଗଣ୍ଠି;
	    inc = convert (argtype, inc);
	  }
	ଅନ୍ୟଥା
	  {
	    inc = VECTOR_TYPE_P (argtype)
	      ? build_one_cst (argtype)
	      : integer_one_ଗଣ୍ଠି;
	    inc = convert (argtype, inc);
	  }

	/* If 'arg' is an Objective-C PROPERTY_REF expression, then we
	   need to ask Objective-C to build the increment or decrement
	   expression for it.  */
	ଯଦି (objc_is_property_ref (arg))
	  ଫେରନ୍ତୁ objc_build_incr_ପଦସମଷ୍ଟି_for_property_ref (location, code,
							arg, inc);

	/* Report a read-only lvalue.  */
	ଯଦି (TYPE_READONLY (argtype))
	  {
	    readonly_error (location, arg,
			    ((code == PREINCREMENT_ପଦସମଷ୍ଟି
			      || code == POSTINCREMENT_ପଦସମଷ୍ଟି)
			     ? lv_increment : lv_decrement));
	    ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
	  }
	ଅନ୍ୟଥା ଯଦି (ବୃକ୍ଷ_READONLY (arg))
	  readonly_warning (arg,
			    ((code == PREINCREMENT_ପଦସମଷ୍ଟି
			      || code == POSTINCREMENT_ପଦସମଷ୍ଟି)
			     ? lv_increment : lv_decrement));

	/* If the argument is atomic, use the special code sequences for
	   atomic compound assignment.  */
	ଯଦି (atomic_op)
	  {
	    arg = stabilize_reference (arg);
	    ret = build_atomic_assign (location, arg,
				       ((code == PREINCREMENT_ପଦସମଷ୍ଟି
					 || code == POSTINCREMENT_ପଦସମଷ୍ଟି)
					? PLUS_ପଦସମଷ୍ଟି
					: MINUS_ପଦସମଷ୍ଟି),
				       (FRACT_MODE_P (TYPE_MODE (argtype))
					? inc
					: integer_one_ଗଣ୍ଠି),
				       (code == POSTINCREMENT_ପଦସମଷ୍ଟି
					|| code == POSTDECREMENT_ପଦସମଷ୍ଟି));
	    ଯାଅ return_build_unary_op;
	  }

	ବୃକ୍ଷ true_res;
	ଯଦି (c_hardbool_type_attr (ବୃକ୍ଷ_TYPE (arg), ଖାଲି, &true_res))
	  {
	    ବୃକ୍ଷ larg = stabilize_reference (arg);
	    ବୃକ୍ଷ sarg = save_ପଦସମଷ୍ଟି (larg);
	    ବାଛ (code)
	      {
	      ସ୍ଥିତି PREINCREMENT_ପଦସମଷ୍ଟି:
		val = build2 (MODIFY_ପଦସମଷ୍ଟି, ବୃକ୍ଷ_TYPE (larg), larg, true_res);
		val = build2 (COMPOUND_ପଦସମଷ୍ଟି, ବୃକ୍ଷ_TYPE (larg), sarg, val);
		ଭାଙ୍ଗ;
	      ସ୍ଥିତି POSTINCREMENT_ପଦସମଷ୍ଟି:
		val = build2 (MODIFY_ପଦସମଷ୍ଟି, ବୃକ୍ଷ_TYPE (larg), larg, true_res);
		val = build2 (COMPOUND_ପଦସମଷ୍ଟି, ବୃକ୍ଷ_TYPE (larg), val, sarg);
		val = build2 (COMPOUND_ପଦସମଷ୍ଟି, ବୃକ୍ଷ_TYPE (larg), sarg, val);
		ଭାଙ୍ଗ;
	      ସ୍ଥିତି PREDECREMENT_ପଦସମଷ୍ଟି:
		{
		  ବୃକ୍ଷ rarg = convert_lvalue_to_rvalue (location, sarg,
							ସତ୍ୟ, ସତ୍ୟ);
		  rarg = invert_truthvalue_loc (location, rarg);
		  rarg = convert (ବୃକ୍ଷ_TYPE (sarg), rarg);
		  val = build2 (MODIFY_ପଦସମଷ୍ଟି, ବୃକ୍ଷ_TYPE (larg), larg, rarg);
		}
		ଭାଙ୍ଗ;
	      ସ୍ଥିତି POSTDECREMENT_ପଦସମଷ୍ଟି:
		{
		  ବୃକ୍ଷ rarg = convert_lvalue_to_rvalue (location, sarg,
							ସତ୍ୟ, ସତ୍ୟ);
		  rarg = invert_truthvalue_loc (location, rarg);
		  ବୃକ୍ଷ iarg = convert (ବୃକ୍ଷ_TYPE (larg), rarg);
		  val = build2 (MODIFY_ପଦସମଷ୍ଟି, ବୃକ୍ଷ_TYPE (larg), larg, iarg);
		  val = build2 (COMPOUND_ପଦସମଷ୍ଟି, ବୃକ୍ଷ_TYPE (larg), val, sarg);
		  val = build2 (COMPOUND_ପଦସମଷ୍ଟି, ବୃକ୍ଷ_TYPE (larg), sarg, val);
		}
		ଭାଙ୍ଗ;
	      ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
		gcc_unreachable ();
	      }
	    ବୃକ୍ଷ_SIDE_EFFECTS (val) = 1;
	  }
	ଅନ୍ୟଥା ଯଦି (C_BOOLEAN_TYPE_P (ବୃକ୍ଷ_TYPE (arg)))
	  val = boolean_increment (code, arg);
	ଅନ୍ୟଥା
	  val = build2 (code, ବୃକ୍ଷ_TYPE (arg), arg, inc);
	ବୃକ୍ଷ_SIDE_EFFECTS (val) = 1;
	ଯଦି (TYPE_QUALS (ବୃକ୍ଷ_TYPE (val)) != TYPE_UNQUALIFIED)
	  ବୃକ୍ଷ_TYPE (val) = c_build_qualified_type (ବୃକ୍ଷ_TYPE (val),
						    TYPE_UNQUALIFIED);
	ret = val;
	ଯାଅ return_build_unary_op;
      }

    ସ୍ଥିତି ADDR_ପଦସମଷ୍ଟି:
      /* Note that this operation never does default_conversion.  */

      /* The operand of unary '&' must be an lvalue (which excludes
	 expressions of type void), or, in C99, the result of a [] or
	 unary '*' operator.  */
      ଯଦି (VOID_TYPE_P (ବୃକ୍ଷ_TYPE (arg))
	  && TYPE_QUALS (ବୃକ୍ଷ_TYPE (arg)) == TYPE_UNQUALIFIED
	  && (!INDIRECT_REF_P (arg) || !flag_isoc99))
	pedwarn (location, 0, "taking address of expression of type %<void%>");

      /* Let &* cancel out to simplify resulting code.  */
      ଯଦି (INDIRECT_REF_P (arg))
	{
	  /* Don't let this be an lvalue.  */
	  ଯଦି (lvalue_p (ବୃକ୍ଷ_OPERAND (arg, 0)))
	    ଫେରନ୍ତୁ non_lvalue_loc (location, ବୃକ୍ଷ_OPERAND (arg, 0));
	  ret = ବୃକ୍ଷ_OPERAND (arg, 0);
	  ଯାଅ return_build_unary_op;
	}

      /* Anything not already handled and not a true memory reference
	 or a non-lvalue array is an error.  */
      ଯଦି (typecode != FUNCTION_TYPE && !noconvert
	  && !lvalue_or_else (location, arg, lv_addressof))
	ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;

      /* Move address operations inside C_MAYBE_CONST_EXPR to simplify
	 folding later.  */
      ଯଦି (ବୃକ୍ଷ_CODE (arg) == C_MAYBE_CONST_ପଦସମଷ୍ଟି)
	{
	  ବୃକ୍ଷ inner = build_unary_op (location, code,
				       C_MAYBE_CONST_ପଦସମଷ୍ଟି_ପଦସମଷ୍ଟି (arg),
				       noconvert);
	  ret = build2 (C_MAYBE_CONST_ପଦସମଷ୍ଟି, ବୃକ୍ଷ_TYPE (inner),
			C_MAYBE_CONST_ପଦସମଷ୍ଟି_PRE (arg), inner);
	  gcc_assert (!C_MAYBE_CONST_ପଦସମଷ୍ଟି_INT_OPERANDS (arg));
	  C_MAYBE_CONST_ପଦସମଷ୍ଟି_NON_CONST (ret)
	    = C_MAYBE_CONST_ପଦସମଷ୍ଟି_NON_CONST (arg);
	  ଯାଅ return_build_unary_op;
	}

      /* Ordinary case; arg is a COMPONENT_REF or a decl.  */

      argtype = ବୃକ୍ଷ_TYPE (arg);

      /* If the lvalue is const or volatile, merge that into the type
	 to which the address will point.  This is only needed
	 for function types.  */
      ଯଦି ((DECL_P (arg) || REFERENCE_CLASS_P (arg))
	  && (ବୃକ୍ଷ_READONLY (arg) || ବୃକ୍ଷ_THIS_VOLATILE (arg))
	  && ବୃକ୍ଷ_CODE (argtype) == FUNCTION_TYPE)
	{
	  ପୂର୍ଣ୍ଣସଂଖ୍ୟା orig_quals = TYPE_QUALS (strip_array_types (argtype));
	  ପୂର୍ଣ୍ଣସଂଖ୍ୟା quals = orig_quals;

	  ଯଦି (ବୃକ୍ଷ_READONLY (arg))
	    quals |= TYPE_QUAL_CONST;
	  ଯଦି (ବୃକ୍ଷ_THIS_VOLATILE (arg))
	    quals |= TYPE_QUAL_VOLATILE;

	  argtype = c_build_qualified_type (argtype, quals);
	}

      ବାଛ (ବୃକ୍ଷ_CODE (arg))
	{
	ସ୍ଥିତି COMPONENT_REF:
	  ଯଦି (DECL_C_BIT_FIELD (ବୃକ୍ଷ_OPERAND (arg, 1)))
	    {
	      error_at (location, "cannot take address of bit-field %qD",
			ବୃକ୍ଷ_OPERAND (arg, 1));
	      ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
	    }

	  /* fall through */

	ସ୍ଥିତି ARRAY_REF:
	  ଯଦି (TYPE_REVERSE_STORAGE_ORDER (ବୃକ୍ଷ_TYPE (ବୃକ୍ଷ_OPERAND (arg, 0))))
	    {
	      ଯଦି (!AGGREGATE_TYPE_P (ବୃକ୍ଷ_TYPE (arg))
		  && !POINTER_TYPE_P (ବୃକ୍ଷ_TYPE (arg))
		  && !VECTOR_TYPE_P (ବୃକ୍ଷ_TYPE (arg)))
		{
		  error_at (location, "cannot take address of scalar with "
			    "reverse storage order");
		  ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
		}

	      ଯଦି (ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (arg)) == ARRAY_TYPE
		  && TYPE_REVERSE_STORAGE_ORDER (ବୃକ୍ଷ_TYPE (arg)))
		warning_at (location, OPT_Wscalar_storage_order,
			    "address of array with reverse scalar storage "
			    "order requested");
	    }

	ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
	  ଭାଙ୍ଗ;
	}

      ଯଦି (!c_mark_addressable (arg))
	ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;

      gcc_assert (ବୃକ୍ଷ_CODE (arg) != COMPONENT_REF
		  || !DECL_C_BIT_FIELD (ବୃକ୍ଷ_OPERAND (arg, 1)));

      argtype = c_build_pointer_type (argtype);

      /* ??? Cope with user tricks that amount to offsetof.  Delete this
	 when we have proper support for integer constant expressions.  */
      val = get_base_address (arg);
      ଯଦି (val && INDIRECT_REF_P (val)
          && ବୃକ୍ଷ_CONSTANT (ବୃକ୍ଷ_OPERAND (val, 0)))
	{
	  ret = fold_offsetof (arg, argtype);
	  ଯାଅ return_build_unary_op;
	}

      val = build1 (ADDR_ପଦସମଷ୍ଟି, argtype, arg);

      ret = val;
      ଯାଅ return_build_unary_op;

    ସ୍ଥିତି PAREN_ପଦସମଷ୍ଟି:
      ret = build1 (code, ବୃକ୍ଷ_TYPE (arg), arg);
      ଯାଅ return_build_unary_op;

    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
      gcc_unreachable ();
    }

  ଯଦି (argtype == NULL_ବୃକ୍ଷ)
    argtype = ବୃକ୍ଷ_TYPE (arg);
  ଯଦି (ବୃକ୍ଷ_CODE (arg) == INTEGER_CST)
    ret = (require_constant_ମୂଲ୍ୟ
	   ? fold_build1_initializer_loc (location, code, argtype, arg)
	   : fold_build1_loc (location, code, argtype, arg));
  ଅନ୍ୟଥା
    ret = build1 (code, argtype, arg);
 return_build_unary_op:
  gcc_assert (ret != error_mark_ଗଣ୍ଠି);
  ଯଦି (ବୃକ୍ଷ_CODE (ret) == INTEGER_CST && !ବୃକ୍ଷ_OVERFLOW (ret)
      && !(ବୃକ୍ଷ_CODE (xarg) == INTEGER_CST && !ବୃକ୍ଷ_OVERFLOW (xarg)))
    ret = build1 (NOP_ପଦସମଷ୍ଟି, ବୃକ୍ଷ_TYPE (ret), ret);
  ଅନ୍ୟଥା ଯଦି (ବୃକ୍ଷ_CODE (ret) != INTEGER_CST && int_operands)
    ret = note_integer_operands (ret);
  ଯଦି (eptype)
    ret = build1 (EXCESS_PRECISION_ପଦସମଷ୍ଟି, eptype, ret);
  protected_set_ପଦସମଷ୍ଟି_location (ret, location);
  ଫେରନ୍ତୁ ret;
}

/* Return nonzero if REF is an lvalue valid for this language.
   Lvalues can be assigned, unless their type has TYPE_READONLY.
   Lvalues can have their address taken, unless they have C_DECL_REGISTER.  */

ତାର୍କିକ
lvalue_p (const_ବୃକ୍ଷ ref)
{
  ଅଚଳ ଗଣନା ବୃକ୍ଷ_code code = ବୃକ୍ଷ_CODE (ref);

  ବାଛ (code)
    {
    ସ୍ଥିତି REALPART_ପଦସମଷ୍ଟି:
    ସ୍ଥିତି IMAGPART_ପଦସମଷ୍ଟି:
    ସ୍ଥିତି COMPONENT_REF:
      ଫେରନ୍ତୁ lvalue_p (ବୃକ୍ଷ_OPERAND (ref, 0));

    ସ୍ଥିତି C_MAYBE_CONST_ପଦସମଷ୍ଟି:
      ଫେରନ୍ତୁ lvalue_p (ବୃକ୍ଷ_OPERAND (ref, 1));

    ସ୍ଥିତି COMPOUND_LITERAL_ପଦସମଷ୍ଟି:
    ସ୍ଥିତି STRING_CST:
      ଫେରନ୍ତୁ ସତ୍ୟ;

    ସ୍ଥିତି MEM_REF:
    ସ୍ଥିତି TARGET_MEM_REF:
      /* MEM_REFs can appear from -fgimple parsing or folding, so allow them
	 here as well.  */
    ସ୍ଥିତି INDIRECT_REF:
    ସ୍ଥିତି ARRAY_REF:
    ସ୍ଥିତି VAR_DECL:
    ସ୍ଥିତି PARM_DECL:
    ସ୍ଥିତି RESULT_DECL:
    ସ୍ଥିତି ERROR_MARK:
      ଫେରନ୍ତୁ (ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (ref)) != FUNCTION_TYPE
	      && ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (ref)) != METHOD_TYPE);

    ସ୍ଥିତି BIND_ପଦସମଷ୍ଟି:
      ଫେରନ୍ତୁ ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (ref)) == ARRAY_TYPE;

    ସ୍ଥିତି CALL_ପଦସମଷ୍ଟି:
      ଫେରନ୍ତୁ is_access_with_size_p (ref);

    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
      ଫେରନ୍ତୁ ମିଥ୍ୟା;
    }
}

/* Give a warning for storing in something that is read-only in GCC
   terms but not const in ISO C terms.  */

ସ୍ଥିର ଶୂନ୍ୟ
readonly_warning (ବୃକ୍ଷ arg, ଗଣନା lvalue_use use)
{
  ବାଛ (use)
    {
    ସ୍ଥିତି lv_assign:
      warning (0, "assignment of read-only location %qE", arg);
      ଭାଙ୍ଗ;
    ସ୍ଥିତି lv_increment:
      warning (0, "increment of read-only location %qE", arg);
      ଭାଙ୍ଗ;
    ସ୍ଥିତି lv_decrement:
      warning (0, "decrement of read-only location %qE", arg);
      ଭାଙ୍ଗ;
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
      gcc_unreachable ();
    }
  ଫେରନ୍ତୁ;
}


/* Return nonzero if REF is an lvalue valid for this language;
   otherwise, print an error message and return zero.  USE says
   how the lvalue is being used and so selects the error message.
   LOCATION is the location at which any error should be reported.  */

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା
lvalue_or_else (location_t loc, const_ବୃକ୍ଷ ref, ଗଣନା lvalue_use use)
{
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା win = lvalue_p (ref);

  ଯଦି (!win)
    lvalue_error (loc, use);

  ଫେରନ୍ତୁ win;
}

/* Mark EXP saying that we need to be able to take the
   address of it; it should not be allocated in a register.
   Returns true if successful.  ARRAY_REF_P is true if this
   is for ARRAY_REF construction - in that case we don't want
   to look through VIEW_CONVERT_EXPR from VECTOR_TYPE to ARRAY_TYPE,
   it is fine to use ARRAY_REFs for vector subscripts on vector
   register variables.  If OVERRIDE_REGISTER, clear DECL_REGISTER rather
   than producing an error for taking the address of a register.  */

ତାର୍କିକ
c_mark_addressable (ବୃକ୍ଷ exp, ତାର୍କିକ array_ref_p, ତାର୍କିକ override_register)
{
  ବୃକ୍ଷ x = exp;

  ଯେତେବେଳେ (1)
    ବାଛ (ବୃକ୍ଷ_CODE (x))
      {
      ସ୍ଥିତି VIEW_CONVERT_ପଦସମଷ୍ଟି:
	ଯଦି (array_ref_p
	    && ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (x)) == ARRAY_TYPE
	    && VECTOR_TYPE_P (ବୃକ୍ଷ_TYPE (ବୃକ୍ଷ_OPERAND (x, 0))))
	  ଫେରନ୍ତୁ ସତ୍ୟ;
	x = ବୃକ୍ଷ_OPERAND (x, 0);
	ଭାଙ୍ଗ;

      ସ୍ଥିତି COMPONENT_REF:
	ଯଦି (DECL_C_BIT_FIELD (ବୃକ୍ଷ_OPERAND (x, 1)))
	  {
	    error ("cannot take address of bit-field %qD",
		   ବୃକ୍ଷ_OPERAND (x, 1));
	    ଫେରନ୍ତୁ ମିଥ୍ୟା;
	  }
	/* FALLTHRU */
      ସ୍ଥିତି ADDR_ପଦସମଷ୍ଟି:
      ସ୍ଥିତି ARRAY_REF:
      ସ୍ଥିତି REALPART_ପଦସମଷ୍ଟି:
      ସ୍ଥିତି IMAGPART_ପଦସମଷ୍ଟି:
	x = ବୃକ୍ଷ_OPERAND (x, 0);
	ଭାଙ୍ଗ;

      ସ୍ଥିତି COMPOUND_LITERAL_ପଦସମଷ୍ଟି:
	ଯଦି (C_DECL_REGISTER (COMPOUND_LITERAL_ପଦସମଷ୍ଟି_DECL (x)))
	  {
	    ଯଦି (override_register)
	      DECL_REGISTER (COMPOUND_LITERAL_ପଦସମଷ୍ଟି_DECL (x)) = 0;
	    ଅନ୍ୟଥା
	      {
		error ("address of register compound literal requested");
		ଫେରନ୍ତୁ ମିଥ୍ୟା;
	      }
	  }
	ବୃକ୍ଷ_ADDRESSABLE (x) = 1;
	ବୃକ୍ଷ_ADDRESSABLE (COMPOUND_LITERAL_ପଦସମଷ୍ଟି_DECL (x)) = 1;
	ଫେରନ୍ତୁ ସତ୍ୟ;

      ସ୍ଥିତି CONSTRUCTOR:
	ବୃକ୍ଷ_ADDRESSABLE (x) = 1;
	ଫେରନ୍ତୁ ସତ୍ୟ;

      ସ୍ଥିତି VAR_DECL:
      ସ୍ଥିତି CONST_DECL:
      ସ୍ଥିତି PARM_DECL:
      ସ୍ଥିତି RESULT_DECL:
	ଯଦି (C_DECL_REGISTER (x)
	    && DECL_NONLOCAL (x))
	  {
	    ଯଦି (ବୃକ୍ଷ_PUBLIC (x) || is_global_var (x))
	      {
		error
		  ("global register variable %qD used in nested function", x);
		ଫେରନ୍ତୁ ମିଥ୍ୟା;
	      }
	    pedwarn (ନିବେଶ_location, 0, "register variable %qD used in nested function", x);
	  }
	ଅନ୍ୟଥା ଯଦି (C_DECL_REGISTER (x))
	  {
	    ଯଦି (ବୃକ୍ଷ_PUBLIC (x) || is_global_var (x))
	      error ("address of global register variable %qD requested", x);
	    ଅନ୍ୟଥା ଯଦି (override_register && !DECL_HARD_REGISTER (x))
	      {
		DECL_REGISTER (x) = 0;
		ବୃକ୍ଷ_ADDRESSABLE (x) = 1;
		mark_decl_used (x, ସତ୍ୟ);
		ଫେରନ୍ତୁ ସତ୍ୟ;
	      }
	    ଅନ୍ୟଥା
	      error ("address of register variable %qD requested", x);
	    ଫେରନ୍ତୁ ମିଥ୍ୟା;
	  }

	/* FALLTHRU */
      ସ୍ଥିତି FUNCTION_DECL:
	ବୃକ୍ଷ_ADDRESSABLE (x) = 1;
	mark_decl_used (x, ସତ୍ୟ);
	/* FALLTHRU */
      ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
	ଫେରନ୍ତୁ ସତ୍ୟ;
    }
}

/* Convert EXPR to TYPE, warning about conversion problems with
   constants.  SEMANTIC_TYPE is the type this conversion would use
   without excess precision. If SEMANTIC_TYPE is NULL, this function
   is equivalent to convert_and_check. This function is a wrapper that
   handles conversions that may be different than
   the usual ones because of excess precision.  */

ସ୍ଥିର ବୃକ୍ଷ
ep_convert_and_check (location_t loc, ବୃକ୍ଷ type, ବୃକ୍ଷ ପଦସମଷ୍ଟି,
		      ବୃକ୍ଷ semantic_type)
{
  ଯଦି (ବୃକ୍ଷ_TYPE (ପଦସମଷ୍ଟି) == type)
    ଫେରନ୍ତୁ ପଦସମଷ୍ଟି;

  /* For C11, integer conversions may have results with excess
     precision.  */
  ଯଦି (flag_isoc11 || !semantic_type)
    ଫେରନ୍ତୁ convert_and_check (loc, type, ପଦସମଷ୍ଟି);

  ଯଦି (ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (ପଦସମଷ୍ଟି)) == INTEGER_TYPE
      && ବୃକ୍ଷ_TYPE (ପଦସମଷ୍ଟି) != semantic_type)
    {
      /* For integers, we need to check the real conversion, not
	 the conversion to the excess precision type.  */
      ପଦସମଷ୍ଟି = convert_and_check (loc, semantic_type, ପଦସମଷ୍ଟି);
    }
  /* Result type is the excess precision type, which should be
     large enough, so do not check.  */
  ଫେରନ୍ତୁ convert (type, ପଦସମଷ୍ଟି);
}

/* If EXPR refers to a built-in declared without a prototype returns
   the actual type of the built-in and, if non-null, set *BLTIN to
   a pointer to the built-in.  Otherwise return the type of EXPR
   and clear *BLTIN if non-null.  */

ସ୍ଥିର ବୃକ୍ଷ
type_or_builtin_type (ବୃକ୍ଷ ପଦସମଷ୍ଟି, ବୃକ୍ଷ *bltin = ଖାଲି)
{
  ବୃକ୍ଷ dummy;
  ଯଦି (!bltin)
    bltin = &dummy;

  *bltin = NULL_ବୃକ୍ଷ;

  ବୃକ୍ଷ type = ବୃକ୍ଷ_TYPE (ପଦସମଷ୍ଟି);
  ଯଦି (ବୃକ୍ଷ_CODE (ପଦସମଷ୍ଟି) != ADDR_ପଦସମଷ୍ଟି)
    ଫେରନ୍ତୁ type;

  ବୃକ୍ଷ oper = ବୃକ୍ଷ_OPERAND (ପଦସମଷ୍ଟି, 0);
  ଯଦି (!DECL_P (oper)
      || ବୃକ୍ଷ_CODE (oper) != FUNCTION_DECL
      || !fndecl_built_in_p (oper, BUILT_IN_NORMAL))
    ଫେରନ୍ତୁ type;

  built_in_function code = DECL_FUNCTION_CODE (oper);
  ଯଦି (!C_DECL_BUILTIN_PROTOTYPE (oper))
    ଫେରନ୍ତୁ type;

  ଯଦି ((*bltin = builtin_decl_implicit (code)))
    type = c_build_pointer_type (ବୃକ୍ଷ_TYPE (*bltin));

  ଫେରନ୍ତୁ type;
}

/* Build and return a conditional expression IFEXP ? OP1 : OP2.  If
   IFEXP_BCP then the condition is a call to __builtin_constant_p, and
   if folded to an integer constant then the unselected half may
   contain arbitrary operations not normally permitted in constant
   expressions.  Set the location of the expression to LOC.  */

ବୃକ୍ଷ
build_conditional_ପଦସମଷ୍ଟି (location_t colon_loc, ବୃକ୍ଷ ifexp, ତାର୍କିକ ifexp_bcp,
			ବୃକ୍ଷ op1, ବୃକ୍ଷ op1_original_type, location_t op1_loc,
			ବୃକ୍ଷ op2, ବୃକ୍ଷ op2_original_type, location_t op2_loc)
{
  ବୃକ୍ଷ type1;
  ବୃକ୍ଷ type2;
  ବୃକ୍ଷ result_type = ଖାଲି;
  ବୃକ୍ଷ semantic_result_type = ଖାଲି;
  ବୃକ୍ଷ orig_op1 = op1, orig_op2 = op2;
  ତାର୍କିକ int_const, op1_int_operands, op2_int_operands, int_operands;
  ତାର୍କିକ ifexp_int_operands;
  ବୃକ୍ଷ ret;

  op1_int_operands = ପଦସମଷ୍ଟି_INT_CONST_OPERANDS (orig_op1);
  ଯଦି (op1_int_operands)
    op1 = remove_c_maybe_const_ପଦସମଷ୍ଟି (op1);
  op2_int_operands = ପଦସମଷ୍ଟି_INT_CONST_OPERANDS (orig_op2);
  ଯଦି (op2_int_operands)
    op2 = remove_c_maybe_const_ପଦସମଷ୍ଟି (op2);
  ifexp_int_operands = ପଦସମଷ୍ଟି_INT_CONST_OPERANDS (ifexp);
  ଯଦି (ifexp_int_operands)
    ifexp = remove_c_maybe_const_ପଦସମଷ୍ଟି (ifexp);

  /* Promote both alternatives.  */

  ଯଦି (ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (op1)) != VOID_TYPE)
    op1 = default_conversion (op1);
  ଯଦି (ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (op2)) != VOID_TYPE)
    op2 = default_conversion (op2);

  ଯଦି (ବୃକ୍ଷ_CODE (ifexp) == ERROR_MARK
      || ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (op1)) == ERROR_MARK
      || ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (op2)) == ERROR_MARK)
    ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;

  ବୃକ୍ଷ bltin1 = NULL_ବୃକ୍ଷ;
  ବୃକ୍ଷ bltin2 = NULL_ବୃକ୍ଷ;
  type1 = type_or_builtin_type (op1, &bltin1);
  ଅଚଳ ଗଣନା ବୃକ୍ଷ_code code1 = ବୃକ୍ଷ_CODE (type1);
  type2 = type_or_builtin_type (op2, &bltin2);
  ଅଚଳ ଗଣନା ବୃକ୍ଷ_code code2 = ବୃକ୍ଷ_CODE (type2);

  ଯଦି (code1 == POINTER_TYPE && reject_gcc_builtin (op1))
    ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;

  ଯଦି (code2 == POINTER_TYPE && reject_gcc_builtin (op2))
    ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;

  /* C90 does not permit non-lvalue arrays in conditional expressions.
     In C99 they will be pointers by now.  */
  ଯଦି (code1 == ARRAY_TYPE || code2 == ARRAY_TYPE)
    {
      error_at (colon_loc, "non-lvalue array in conditional expression");
      ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
    }

  ଯଦି ((ବୃକ୍ଷ_CODE (op1) == EXCESS_PRECISION_ପଦସମଷ୍ଟି
       || ବୃକ୍ଷ_CODE (op2) == EXCESS_PRECISION_ପଦସମଷ୍ଟି)
      && (code1 == INTEGER_TYPE || code1 == REAL_TYPE
	  || code1 == COMPLEX_TYPE || code1 == BITINT_TYPE)
      && (code2 == INTEGER_TYPE || code2 == REAL_TYPE
	  || code2 == COMPLEX_TYPE || code2 == BITINT_TYPE))
    {
      semantic_result_type = c_common_type (type1, type2);
      ଯଦି (ବୃକ୍ଷ_CODE (op1) == EXCESS_PRECISION_ପଦସମଷ୍ଟି)
	{
	  op1 = ବୃକ୍ଷ_OPERAND (op1, 0);
	  type1 = ବୃକ୍ଷ_TYPE (op1);
	  gcc_assert (ବୃକ୍ଷ_CODE (type1) == code1);
	}
      ଯଦି (ବୃକ୍ଷ_CODE (op2) == EXCESS_PRECISION_ପଦସମଷ୍ଟି)
	{
	  op2 = ବୃକ୍ଷ_OPERAND (op2, 0);
	  type2 = ବୃକ୍ଷ_TYPE (op2);
	  gcc_assert (ବୃକ୍ଷ_CODE (type2) == code2);
	}
    }

  ଯଦି (warn_cxx_compat)
    {
      ବୃକ୍ଷ t1 = op1_original_type ? op1_original_type : ବୃକ୍ଷ_TYPE (orig_op1);
      ବୃକ୍ଷ t2 = op2_original_type ? op2_original_type : ବୃକ୍ଷ_TYPE (orig_op2);

      ଯଦି (ବୃକ୍ଷ_CODE (t1) == ENUMERAL_TYPE
	  && ବୃକ୍ଷ_CODE (t2) == ENUMERAL_TYPE
	  && TYPE_MAIN_VARIANT (t1) != TYPE_MAIN_VARIANT (t2))
	warning_at (colon_loc, OPT_Wc___compat,
		    "different enum types in conditional is "
		    "invalid in C++: %qT vs %qT", t1, t2);
    }

  ଯଦି (warn_zero_as_null_pointer_constant
      && c_inhibit_evaluation_warnings == 0)
    {
      ଯଦି ((code1 == POINTER_TYPE || code1 == NULLPTR_TYPE)
	  && INTEGRAL_TYPE_P (type2) && null_pointer_constant_p (orig_op2))
	warning_at (op2_loc, OPT_Wzero_as_null_pointer_constant,
		    "zero as null pointer constant");

      ଯଦି ((code2 == POINTER_TYPE || code2 == NULLPTR_TYPE)
	  && INTEGRAL_TYPE_P (type1) && null_pointer_constant_p (orig_op1))
	warning_at (op1_loc, OPT_Wzero_as_null_pointer_constant,
		    "zero as null pointer constant");
    }

  /* Quickly detect the usual case where op1 and op2 have the same type
     after promotion.  */
  ଯଦି (TYPE_MAIN_VARIANT (type1) == TYPE_MAIN_VARIANT (type2))
    {
      ଯଦି (type1 == type2)
	result_type = type1;
      ଅନ୍ୟଥା
	result_type = TYPE_MAIN_VARIANT (type1);
    }
  ଅନ୍ୟଥା ଯଦି ((code1 == INTEGER_TYPE || code1 == REAL_TYPE
	    || code1 == COMPLEX_TYPE || code1 == BITINT_TYPE)
	   && (code2 == INTEGER_TYPE || code2 == REAL_TYPE
	       || code2 == COMPLEX_TYPE || code2 == BITINT_TYPE))
    {
      /* In C11, a conditional expression between a floating-point
	 type and an integer type should convert the integer type to
	 the evaluation format of the floating-point type, with
	 possible excess precision.  */
      ବୃକ୍ଷ eptype1 = type1;
      ବୃକ୍ଷ eptype2 = type2;
      ଯଦି (flag_isoc11)
	{
	  ବୃକ୍ଷ eptype;
	  ଯଦି (ANY_INTEGRAL_TYPE_P (type1)
	      && (eptype = excess_precision_type (type2)) != NULL_ବୃକ୍ଷ)
	    {
	      eptype2 = eptype;
	      ଯଦି (!semantic_result_type)
		semantic_result_type = c_common_type (type1, type2);
	    }
	  ଅନ୍ୟଥା ଯଦି (ANY_INTEGRAL_TYPE_P (type2)
		   && (eptype = excess_precision_type (type1)) != NULL_ବୃକ୍ଷ)
	    {
	      eptype1 = eptype;
	      ଯଦି (!semantic_result_type)
		semantic_result_type = c_common_type (type1, type2);
	    }
	}
      result_type = c_common_type (eptype1, eptype2);
      ଯଦି (result_type == error_mark_ଗଣ୍ଠି)
	ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
      do_warn_double_promotion (result_type, type1, type2,
				"implicit conversion from %qT to %qT to "
				"match other result of conditional",
				colon_loc);

      /* If -Wsign-compare, warn here if type1 and type2 have
	 different signedness.  We'll promote the signed to unsigned
	 and later code won't know it used to be different.
	 Do this check on the original types, so that explicit casts
	 will be considered, but default promotions won't.  */
      ଯଦି (c_inhibit_evaluation_warnings == 0)
	{
	  ପୂର୍ଣ୍ଣସଂଖ୍ୟା unsigned_op1 = TYPE_UNSIGNED (ବୃକ୍ଷ_TYPE (orig_op1));
	  ପୂର୍ଣ୍ଣସଂଖ୍ୟା unsigned_op2 = TYPE_UNSIGNED (ବୃକ୍ଷ_TYPE (orig_op2));

	  ଯଦି (unsigned_op1 ^ unsigned_op2)
	    {
	      /* Do not warn if the result type is signed, since the
		 signed type will only be chosen if it can represent
		 all the values of the unsigned type.  */
	      ଯଦି (!TYPE_UNSIGNED (result_type))
		/* OK */;
	      ଅନ୍ୟଥା
		{
		  ତାର୍କିକ op1_maybe_const = ସତ୍ୟ;
		  ତାର୍କିକ op2_maybe_const = ସତ୍ୟ;

		  /* Do not warn if the signed quantity is an
		     unsuffixed integer literal (or some static
		     constant expression involving such literals) and
		     it is non-negative.  This warning requires the
		     operands to be folded for best results, so do
		     that folding in this case even without
		     warn_sign_compare to avoid warning options
		     possibly affecting code generation.  */
		  c_inhibit_evaluation_warnings
		    += (ifexp == truthvalue_false_ଗଣ୍ଠି);
		  op1 = c_fully_fold (op1, require_constant_ମୂଲ୍ୟ,
				      &op1_maybe_const);
		  c_inhibit_evaluation_warnings
		    -= (ifexp == truthvalue_false_ଗଣ୍ଠି);

		  c_inhibit_evaluation_warnings
		    += (ifexp == truthvalue_true_ଗଣ୍ଠି);
		  op2 = c_fully_fold (op2, require_constant_ମୂଲ୍ୟ,
				      &op2_maybe_const);
		  c_inhibit_evaluation_warnings
		    -= (ifexp == truthvalue_true_ଗଣ୍ଠି);

		  ଯଦି (warn_sign_compare)
		    {
		      ଯଦି ((unsigned_op2
			   && ବୃକ୍ଷ_ପଦସମଷ୍ଟି_nonnegative_p (op1))
			  || (unsigned_op1
			      && ବୃକ୍ଷ_ପଦସମଷ୍ଟି_nonnegative_p (op2)))
			/* OK */;
		      ଅନ୍ୟଥା ଯଦି (unsigned_op2)
			warning_at (op1_loc, OPT_Wsign_compare,
				    "operand of %<?:%> changes signedness from "
				    "%qT to %qT due to unsignedness of other "
				    "operand", ବୃକ୍ଷ_TYPE (orig_op1),
				    ବୃକ୍ଷ_TYPE (orig_op2));
		      ଅନ୍ୟଥା
			warning_at (op2_loc, OPT_Wsign_compare,
				    "operand of %<?:%> changes signedness from "
				    "%qT to %qT due to unsignedness of other "
				    "operand", ବୃକ୍ଷ_TYPE (orig_op2),
				    ବୃକ୍ଷ_TYPE (orig_op1));
		    }
		  ଯଦି (!op1_maybe_const || ବୃକ୍ଷ_CODE (op1) != INTEGER_CST)
		    op1 = c_wrap_maybe_const (op1, !op1_maybe_const);
		  ଯଦି (!op2_maybe_const || ବୃକ୍ଷ_CODE (op2) != INTEGER_CST)
		    op2 = c_wrap_maybe_const (op2, !op2_maybe_const);
		}
	    }
	}
    }
  ଅନ୍ୟଥା ଯଦି (code1 == VOID_TYPE || code2 == VOID_TYPE)
    {
      ଯଦି (code1 != VOID_TYPE || code2 != VOID_TYPE)
	pedwarn (colon_loc, OPT_Wpedantic,
		 "ISO C forbids conditional expr with only one void side");
      result_type = void_type_ଗଣ୍ଠି;
    }
  ଅନ୍ୟଥା ଯଦି (code1 == POINTER_TYPE && code2 == POINTER_TYPE)
    {
      addr_space_t as1 = TYPE_ADDR_SPACE (ବୃକ୍ଷ_TYPE (type1));
      addr_space_t as2 = TYPE_ADDR_SPACE (ବୃକ୍ଷ_TYPE (type2));
      addr_space_t as_common;

      ଯଦି (comp_target_types (colon_loc, type1, type2))
	{
	  ifexp = save_ପଦସମଷ୍ଟି (ifexp);
	  result_type = common_pointer_type (type1, type2, ifexp);
	}
      ଅନ୍ୟଥା ଯଦି (null_pointer_constant_p (orig_op1))
	result_type = type2;
      ଅନ୍ୟଥା ଯଦି (null_pointer_constant_p (orig_op2))
	result_type = type1;
      ଅନ୍ୟଥା ଯଦି (!addr_space_superset (as1, as2, &as_common))
	{
	  error_at (colon_loc, "pointers to disjoint address spaces "
		    "used in conditional expression");
	  ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
	}
      ଅନ୍ୟଥା ଯଦି ((VOID_TYPE_P (ବୃକ୍ଷ_TYPE (type1))
		&& !TYPE_ATOMIC (ବୃକ୍ଷ_TYPE (type1)))
	       || (VOID_TYPE_P (ବୃକ୍ଷ_TYPE (type2))
		   && !TYPE_ATOMIC (ବୃକ୍ଷ_TYPE (type2))))
	{
	  ବୃକ୍ଷ t1 = ବୃକ୍ଷ_TYPE (type1);
	  ବୃକ୍ଷ t2 = ବୃକ୍ଷ_TYPE (type2);
	  ଯଦି (!(VOID_TYPE_P (t1)
		&& !TYPE_ATOMIC (t1)))
	   {
	     /* roles are swapped */
	     t1 = t2;
	     t2 = ବୃକ୍ଷ_TYPE (type1);
	   }
	  ବୃକ୍ଷ t2_stripped = strip_array_types (t2);
	  ଯଦି ((ବୃକ୍ଷ_CODE (t2) == ARRAY_TYPE)
	      && (TYPE_QUALS (t2_stripped) & ~TYPE_QUALS (t1)))
	    {
	      ଯଦି (!flag_isoc23)
		warning_at (colon_loc, OPT_Wdiscarded_array_qualifiers,
			    "pointer to array loses qualifier "
			    "in conditional expression");
	      ଅନ୍ୟଥା ଯଦି (warn_c11_c23_compat > 0)
		warning_at (colon_loc, OPT_Wc11_c23_compat,
			    "pointer to array loses qualifier "
			    "in conditional expression in ISO C before C23");
	    }
	  ଯଦି (ବୃକ୍ଷ_CODE (t2) == FUNCTION_TYPE)
	    pedwarn (colon_loc, OPT_Wpedantic,
		     "ISO C forbids conditional expr between "
		     "%<void *%> and function pointer");
	  /* for array, use qualifiers of element type */
	  ଯଦି (flag_isoc23)
	    t2 = t2_stripped;
	  result_type = c_build_pointer_type (qualify_type (t1, t2));
	}
      /* Objective-C pointer comparisons are a bit more lenient.  */
      ଅନ୍ୟଥା ଯଦି (objc_have_common_type (type1, type2, -3, NULL_ବୃକ୍ଷ))
	result_type = objc_common_type (type1, type2);
      ଅନ୍ୟଥା
	{
	  ପୂର୍ଣ୍ଣସଂଖ୍ୟା qual = ENCODE_QUAL_ADDR_SPACE (as_common);
	  ଗଣନା diagnostics::kind kind = diagnostics::kind::permerror;
	  ଯଦି (!flag_isoc99)
	    /* This downgrade to a warning ensures that -std=gnu89
	       -pedantic-errors does not flag these mismatches between
	       builtins as errors (as diagnostics::kind::permerror would)
	       ISO C99 and later do not have implicit function declarations,
	       so the mismatch cannot occur naturally there.  */
	    kind = (bltin1 && bltin2
		    ? diagnostics::kind::warning
		    : diagnostics::kind::pedwarn);
	  ଯଦି (emit_diagnostic (kind, colon_loc, OPT_Wincompatible_pointer_types,
			       "pointer type mismatch "
			       "in conditional expression"))
	    {
	      inform (op1_loc, "first expression has type %qT", type1);
	      inform (op2_loc, "second expression has type %qT", type2);
	    }
	  result_type = c_build_pointer_type
			  (c_build_qualified_type (void_type_ଗଣ୍ଠି, qual));
	}
    }
  ଅନ୍ୟଥା ଯଦି (code1 == POINTER_TYPE
	   && (code2 == INTEGER_TYPE || code2 == BITINT_TYPE))
    {
      ଯଦି (!null_pointer_constant_p (orig_op2))
	permerror_opt (colon_loc, OPT_Wint_conversion,
		       "pointer/integer type mismatch "
		       "in conditional expression");
      ଅନ୍ୟଥା
	{
	  op2 = null_pointer_ଗଣ୍ଠି;
	}
      result_type = type1;
    }
  ଅନ୍ୟଥା ଯଦି (code2 == POINTER_TYPE
	   && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
    {
      ଯଦି (!null_pointer_constant_p (orig_op1))
	permerror_opt (colon_loc, OPT_Wint_conversion,
		       "pointer/integer type mismatch "
		       "in conditional expression");
      ଅନ୍ୟଥା
	{
	  op1 = null_pointer_ଗଣ୍ଠି;
	}
      result_type = type2;
    }
  /* 6.5.15: "if one is a null pointer constant (other than a pointer) or has
     type nullptr_t and the other is a pointer, the result type is the pointer
     type."  */
  ଅନ୍ୟଥା ଯଦି (code1 == NULLPTR_TYPE && code2 == POINTER_TYPE)
    result_type = type2;
  ଅନ୍ୟଥା ଯଦି (code1 == POINTER_TYPE && code2 == NULLPTR_TYPE)
    result_type = type1;
  ଅନ୍ୟଥା ଯଦି (RECORD_OR_UNION_TYPE_P (type1) && RECORD_OR_UNION_TYPE_P (type2)
	   && comptypes (TYPE_MAIN_VARIANT (type1),
			 TYPE_MAIN_VARIANT (type2)))
    result_type = composite_type (TYPE_MAIN_VARIANT (type1),
				  TYPE_MAIN_VARIANT (type2));

  ଯଦି (!result_type)
    {
      ଯଦି (flag_cond_mismatch)
	result_type = void_type_ଗଣ୍ଠି;
      ଅନ୍ୟଥା
	{
	  error_at (colon_loc, "type mismatch in conditional expression");
	  ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
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

  ଯଦି (ifexp_bcp && ifexp == truthvalue_true_ଗଣ୍ଠି)
    {
      op2_int_operands = ସତ୍ୟ;
      op1 = c_fully_fold (op1, require_constant_ମୂଲ୍ୟ, ଖାଲି);
    }
  ଯଦି (ifexp_bcp && ifexp == truthvalue_false_ଗଣ୍ଠି)
    {
      op1_int_operands = ସତ୍ୟ;
      op2 = c_fully_fold (op2, require_constant_ମୂଲ୍ୟ, ଖାଲି);
    }
  int_const = int_operands = (ifexp_int_operands
			      && op1_int_operands
			      && op2_int_operands);
  ଯଦି (int_operands)
    {
      int_const = ((ifexp == truthvalue_true_ଗଣ୍ଠି
		    && ବୃକ୍ଷ_CODE (orig_op1) == INTEGER_CST
		    && !ବୃକ୍ଷ_OVERFLOW (orig_op1))
		   || (ifexp == truthvalue_false_ଗଣ୍ଠି
		       && ବୃକ୍ଷ_CODE (orig_op2) == INTEGER_CST
		       && !ବୃକ୍ଷ_OVERFLOW (orig_op2)));
    }

  /* Need to convert condition operand into a vector mask.  */
  ଯଦି (VECTOR_TYPE_P (ବୃକ୍ଷ_TYPE (ifexp)))
    {
      ବୃକ୍ଷ vectype = ବୃକ୍ଷ_TYPE (ifexp);
      ବୃକ୍ଷ elem_type = ବୃକ୍ଷ_TYPE (vectype);
      ବୃକ୍ଷ zero = build_int_cst (elem_type, 0);
      ବୃକ୍ଷ zero_vec = build_vector_from_val (vectype, zero);
      ବୃକ୍ଷ cmp_type = truth_type_for (vectype);
      ifexp = build2 (NE_ପଦସମଷ୍ଟି, cmp_type, ifexp, zero_vec);
    }

  ଯଦି (int_const || (ifexp_bcp && ବୃକ୍ଷ_CODE (ifexp) == INTEGER_CST))
    ret = fold_build3_loc (colon_loc, COND_ପଦସମଷ୍ଟି, result_type, ifexp, op1, op2);
  ଅନ୍ୟଥା
    {
      ଯଦି (int_operands)
	{
	  /* Use c_fully_fold here, since C_MAYBE_CONST_EXPR might be
	     nested inside of the expression.  */
	  op1 = c_fully_fold (op1, ମିଥ୍ୟା, ଖାଲି);
	  op2 = c_fully_fold (op2, ମିଥ୍ୟା, ଖାଲି);
	}
      ret = build3 (COND_ପଦସମଷ୍ଟି, result_type, ifexp, op1, op2);
      ଯଦି (int_operands)
	ret = note_integer_operands (ret);
    }
  ଯଦି (semantic_result_type)
    ret = build1 (EXCESS_PRECISION_ପଦସମଷ୍ଟି, semantic_result_type, ret);

  protected_set_ପଦସମଷ୍ଟି_location (ret, colon_loc);

  /* If the OP1 and OP2 are the same and don't have side-effects,
     warn here, because the COND_EXPR will be turned into OP1.  */
  ଯଦି (warn_duplicated_branches
      && ବୃକ୍ଷ_CODE (ret) == COND_ପଦସମଷ୍ଟି
      && (op1 == op2 || operand_equal_p (op1, op2, OEP_ADDRESS_OF_SAME_FIELD)))
    warning_at (ପଦସମଷ୍ଟି_LOCATION (ret), OPT_Wduplicated_branches,
		"this condition has identical branches");

  ଫେରନ୍ତୁ ret;
}

/* EXPR is an expression, location LOC, whose result is discarded.
   Warn if it is a call to a nodiscard function (or a COMPOUND_EXPR
   whose right-hand operand is such a call, possibly recursively).  */

ସ୍ଥିର ଶୂନ୍ୟ
maybe_warn_nodiscard (location_t loc, ବୃକ୍ଷ ପଦସମଷ୍ଟି)
{
  ଯଦି (VOID_TYPE_P (ବୃକ୍ଷ_TYPE (ପଦସମଷ୍ଟି)))
    ଫେରନ୍ତୁ;
  ଯେତେବେଳେ (ବୃକ୍ଷ_CODE (ପଦସମଷ୍ଟି) == COMPOUND_ପଦସମଷ୍ଟି)
    {
      ପଦସମଷ୍ଟି = ବୃକ୍ଷ_OPERAND (ପଦସମଷ୍ଟି, 1);
      ଯଦି (ପଦସମଷ୍ଟି_HAS_LOCATION (ପଦସମଷ୍ଟି))
	loc = ପଦସମଷ୍ଟି_LOCATION (ପଦସମଷ୍ଟି);
    }
  ଯଦି (ବୃକ୍ଷ_CODE (ପଦସମଷ୍ଟି) != CALL_ପଦସମଷ୍ଟି)
    ଫେରନ୍ତୁ;
  ବୃକ୍ଷ fn = CALL_ପଦସମଷ୍ଟି_FN (ପଦସମଷ୍ଟି);
  ଯଦି (!fn)
    ଫେରନ୍ତୁ;
  ବୃକ୍ଷ attr;
  ଯଦି (ବୃକ୍ଷ_CODE (fn) == ADDR_ପଦସମଷ୍ଟି
      && ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_OPERAND (fn, 0)) == FUNCTION_DECL
      && (attr = lookup_attribute ("nodiscard",
				   DECL_ATTRIBUTES (ବୃକ୍ଷ_OPERAND (fn, 0)))))
    {
      fn = ବୃକ୍ଷ_OPERAND (fn, 0);
      ବୃକ୍ଷ args = ବୃକ୍ଷ_ମୂଲ୍ୟ (attr);
      ଯଦି (args)
	args = ବୃକ୍ଷ_ମୂଲ୍ୟ (args);
      auto_diagnostic_group d;
      auto_urlify_attributes sentinel;
      ପୂର୍ଣ୍ଣସଂଖ୍ୟା warned;
      ଯଦି (args)
	warned = warning_at (loc, OPT_Wunused_result,
			     "ignoring return value of %qD, declared with "
			     "attribute %<nodiscard%>: %E", fn, args);
      ଅନ୍ୟଥା
	warned = warning_at (loc, OPT_Wunused_result,
			     "ignoring return value of %qD, declared with "
			     "attribute %<nodiscard%>", fn);
      ଯଦି (warned)
	inform (DECL_SOURCE_LOCATION (fn), "declared here");
    }
  ଅନ୍ୟଥା
    {
      ବୃକ୍ଷ rettype = ବୃକ୍ଷ_TYPE (ବୃକ୍ଷ_TYPE (ବୃକ୍ଷ_TYPE (fn)));
      attr = lookup_attribute ("nodiscard", TYPE_ATTRIBUTES (rettype));
      ଯଦି (!attr)
	ଫେରନ୍ତୁ;
      ବୃକ୍ଷ args = ବୃକ୍ଷ_ମୂଲ୍ୟ (attr);
      ଯଦି (args)
	args = ବୃକ୍ଷ_ମୂଲ୍ୟ (args);
      auto_diagnostic_group d;
      auto_urlify_attributes sentinel;
      ପୂର୍ଣ୍ଣସଂଖ୍ୟା warned;
      ଯଦି (args)
	warned = warning_at (loc, OPT_Wunused_result,
			     "ignoring return value of type %qT, declared "
			     "with attribute %<nodiscard%>: %E",
			     rettype, args);
      ଅନ୍ୟଥା
	warned = warning_at (loc, OPT_Wunused_result,
			     "ignoring return value of type %qT, declared "
			     "with attribute %<nodiscard%>", rettype);
      ଯଦି (warned)
	{
	  ଯଦି (ବୃକ୍ଷ_CODE (fn) == ADDR_ପଦସମଷ୍ଟି)
	    {
	      fn = ବୃକ୍ଷ_OPERAND (fn, 0);
	      ଯଦି (ବୃକ୍ଷ_CODE (fn) == FUNCTION_DECL)
		inform (DECL_SOURCE_LOCATION (fn),
			"in call to %qD, declared here", fn);
	    }
	}
    }
}

/* Return a compound expression that performs two expressions and
   returns the value of the second of them.

   LOC is the location of the COMPOUND_EXPR.  */

ବୃକ୍ଷ
build_compound_ପଦସମଷ୍ଟି (location_t loc, ବୃକ୍ଷ expr1, ବୃକ୍ଷ expr2)
{
  ତାର୍କିକ expr1_int_operands, expr2_int_operands;
  ବୃକ୍ଷ eptype = NULL_ବୃକ୍ଷ;
  ବୃକ୍ଷ ret;

  expr1_int_operands = ପଦସମଷ୍ଟି_INT_CONST_OPERANDS (expr1);
  ଯଦି (expr1_int_operands)
    expr1 = remove_c_maybe_const_ପଦସମଷ୍ଟି (expr1);
  expr2_int_operands = ପଦସମଷ୍ଟି_INT_CONST_OPERANDS (expr2);
  ଯଦି (expr2_int_operands)
    expr2 = remove_c_maybe_const_ପଦସମଷ୍ଟି (expr2);

  ଯଦି (ବୃକ୍ଷ_CODE (expr1) == EXCESS_PRECISION_ପଦସମଷ୍ଟି)
    expr1 = ବୃକ୍ଷ_OPERAND (expr1, 0);
  ଯଦି (ବୃକ୍ଷ_CODE (expr2) == EXCESS_PRECISION_ପଦସମଷ୍ଟି)
    {
      eptype = ବୃକ୍ଷ_TYPE (expr2);
      expr2 = ବୃକ୍ଷ_OPERAND (expr2, 0);
    }

  ଯଦି (!ବୃକ୍ଷ_SIDE_EFFECTS (expr1))
    {
      /* The left-hand operand of a comma expression is like an expression
	 statement: with -Wunused, we should warn if it doesn't have
	 any side-effects, unless it was explicitly cast to (void).  */
      ଯଦି (warn_unused_ମୂଲ୍ୟ)
	{
	  ଯଦି (VOID_TYPE_P (ବୃକ୍ଷ_TYPE (expr1))
	      && CONVERT_ପଦସମଷ୍ଟି_P (expr1))
	    ; /* (void) a, b */
	  ଅନ୍ୟଥା ଯଦି (VOID_TYPE_P (ବୃକ୍ଷ_TYPE (expr1))
		   && ବୃକ୍ଷ_CODE (expr1) == COMPOUND_ପଦସମଷ୍ଟି
		   && CONVERT_ପଦସମଷ୍ଟି_P (ବୃକ୍ଷ_OPERAND (expr1, 1)))
	    ; /* (void) a, (void) b, c */
	  ଅନ୍ୟଥା
	    warning_at (loc, OPT_Wunused_ମୂଲ୍ୟ,
			"left-hand operand of comma expression has no effect");
	}
    }
  ଅନ୍ୟଥା ଯଦି (ବୃକ୍ଷ_CODE (expr1) == COMPOUND_ପଦସମଷ୍ଟି
	   && warn_unused_ମୂଲ୍ୟ)
    {
      ବୃକ୍ଷ r = expr1;
      location_t cloc = loc;
      ଯେତେବେଳେ (ବୃକ୍ଷ_CODE (r) == COMPOUND_ପଦସମଷ୍ଟି)
        {
	  ଯଦି (ପଦସମଷ୍ଟି_HAS_LOCATION (r))
	    cloc = ପଦସମଷ୍ଟି_LOCATION (r);
	  r = ବୃକ୍ଷ_OPERAND (r, 1);
	}
      ଯଦି (!ବୃକ୍ଷ_SIDE_EFFECTS (r)
	  && !VOID_TYPE_P (ବୃକ୍ଷ_TYPE (r))
	  && !CONVERT_ପଦସମଷ୍ଟି_P (r))
	warning_at (cloc, OPT_Wunused_ମୂଲ୍ୟ,
	            "right-hand operand of comma expression has no effect");
    }

  /* With -Wunused, we should also warn if the left-hand operand does have
     side-effects, but computes a value which is not used.  For example, in
     `foo() + bar(), baz()' the result of the `+' operator is not used,
     so we should issue a warning.  */
  ଅନ୍ୟଥା ଯଦି (warn_unused_ମୂଲ୍ୟ)
    warn_if_unused_ମୂଲ୍ୟ (expr1, loc);

  maybe_warn_nodiscard (loc, expr1);

  ଯଦି (expr2 == error_mark_ଗଣ୍ଠି)
    ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;

  ret = build2 (COMPOUND_ପଦସମଷ୍ଟି, ବୃକ୍ଷ_TYPE (expr2), expr1, expr2);

  ଯଦି (flag_isoc99
      && expr1_int_operands
      && expr2_int_operands)
    ret = note_integer_operands (ret);

  ଯଦି (eptype)
    ret = build1 (EXCESS_PRECISION_ପଦସମଷ୍ଟି, eptype, ret);

  protected_set_ପଦସମଷ୍ଟି_location (ret, loc);
  ଫେରନ୍ତୁ ret;
}

/* Issue -Wcast-qual warnings when appropriate.  TYPE is the type to
   which we are casting.  OTYPE is the type of the expression being
   cast.  Both TYPE and OTYPE are pointer types.  LOC is the location
   of the cast.  -Wcast-qual appeared on the command line.  Named
   address space qualifiers are not handled here, because they result
   in different warnings.  */

ସ୍ଥିର ଶୂନ୍ୟ
handle_warn_cast_qual (location_t loc, ବୃକ୍ଷ type, ବୃକ୍ଷ otype)
{
  ବୃକ୍ଷ in_type = type;
  ବୃକ୍ଷ in_otype = otype;
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା added = 0;
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା discarded = 0;
  ତାର୍କିକ is_const;

  /* Check that the qualifiers on IN_TYPE are a superset of the
     qualifiers of IN_OTYPE.  The outermost level of POINTER_TYPE
     nodes is uninteresting and we stop as soon as we hit a
     non-POINTER_TYPE node on either type.  */
  କର
    {
      in_otype = ବୃକ୍ଷ_TYPE (in_otype);
      in_type = ବୃକ୍ଷ_TYPE (in_type);

      /* GNU C allows cv-qualified function types.  'const' means the
	 function is very pure, 'volatile' means it can't return.  We
	 need to warn when such qualifiers are added, not when they're
	 taken away.  */
      ଯଦି (ବୃକ୍ଷ_CODE (in_otype) == FUNCTION_TYPE
	  && ବୃକ୍ଷ_CODE (in_type) == FUNCTION_TYPE)
	added |= (TYPE_QUALS_NO_ADDR_SPACE (in_type)
		  & ~TYPE_QUALS_NO_ADDR_SPACE (in_otype));
      ଅନ୍ୟଥା
	discarded |= (TYPE_QUALS_NO_ADDR_SPACE (in_otype)
		      & ~TYPE_QUALS_NO_ADDR_SPACE (in_type));
    }
  ଯେତେବେଳେ (ବୃକ୍ଷ_CODE (in_type) == POINTER_TYPE
	 && ବୃକ୍ଷ_CODE (in_otype) == POINTER_TYPE);

  ଯଦି (added)
    warning_at (loc, OPT_Wcast_qual,
		"cast adds %q#v qualifier to function type", added);

  ଯଦି (discarded)
    /* There are qualifiers present in IN_OTYPE that are not present
       in IN_TYPE.  */
    warning_at (loc, OPT_Wcast_qual,
		"cast discards %qv qualifier from pointer target type",
		discarded);

  ଯଦି (added || discarded)
    ଫେରନ୍ତୁ;

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

  ଯଦି (TYPE_MAIN_VARIANT (in_type) != TYPE_MAIN_VARIANT (in_otype))
    ଫେରନ୍ତୁ;
  ଯଦି (ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (type)) != POINTER_TYPE)
    ଫେରନ୍ତୁ;

  in_type = type;
  in_otype = otype;
  is_const = TYPE_READONLY (ବୃକ୍ଷ_TYPE (in_type));
  କର
    {
      in_type = ବୃକ୍ଷ_TYPE (in_type);
      in_otype = ବୃକ୍ଷ_TYPE (in_otype);
      ଯଦି ((TYPE_QUALS (in_type) &~ TYPE_QUALS (in_otype)) != 0
	  && !is_const)
	{
	  warning_at (loc, OPT_Wcast_qual,
		      "to be safe all intermediate pointers in cast from "
                      "%qT to %qT must be %<const%> qualified",
		      otype, type);
	  ଭାଙ୍ଗ;
	}
      ଯଦି (is_const)
	is_const = TYPE_READONLY (in_type);
    }
  ଯେତେବେଳେ (ବୃକ୍ଷ_CODE (in_type) == POINTER_TYPE);
}

/* Heuristic check if two parameter types can be considered ABI-equivalent.  */

ସ୍ଥିର ତାର୍କିକ
c_safe_arg_type_equiv_p (ବୃକ୍ଷ t1, ବୃକ୍ଷ t2)
{
  ଯଦି (error_operand_p (t1) || error_operand_p (t2))
    ଫେରନ୍ତୁ ସତ୍ୟ;

  t1 = TYPE_MAIN_VARIANT (t1);
  t2 = TYPE_MAIN_VARIANT (t2);

  ଯଦି (ବୃକ୍ଷ_CODE (t1) == POINTER_TYPE
      && ବୃକ୍ଷ_CODE (t2) == POINTER_TYPE)
    ଫେରନ୍ତୁ ସତ୍ୟ;

  /* Only the precision of the parameter matters.  This check should
     make sure that the callee does not see undefined values in argument
     registers.  */
  ଯଦି (INTEGRAL_TYPE_P (t1)
      && INTEGRAL_TYPE_P (t2)
      && TYPE_PRECISION (t1) == TYPE_PRECISION (t2))
    ଫେରନ୍ତୁ ସତ୍ୟ;

  ଫେରନ୍ତୁ comptypes (t1, t2);
}

/* Check if a type cast between two function types can be considered safe.  */

ସ୍ଥିର ତାର୍କିକ
c_safe_function_type_cast_p (ବୃକ୍ଷ t1, ବୃକ୍ଷ t2)
{
  ଯଦି (ବୃକ୍ଷ_TYPE (t1) == void_type_ଗଣ୍ଠି &&
      TYPE_ARG_TYPES (t1) == void_list_ଗଣ୍ଠି)
    ଫେରନ୍ତୁ ସତ୍ୟ;

  ଯଦି (ବୃକ୍ଷ_TYPE (t2) == void_type_ଗଣ୍ଠି &&
      TYPE_ARG_TYPES (t2) == void_list_ଗଣ୍ଠି)
    ଫେରନ୍ତୁ ସତ୍ୟ;

  ଯଦି (!c_safe_arg_type_equiv_p (ବୃକ୍ଷ_TYPE (t1), ବୃକ୍ଷ_TYPE (t2)))
    ଫେରନ୍ତୁ ମିଥ୍ୟା;

  ପାଇଁ (t1 = TYPE_ARG_TYPES (t1), t2 = TYPE_ARG_TYPES (t2);
       t1 && t2;
       t1 = ବୃକ୍ଷ_CHAIN (t1), t2 = ବୃକ୍ଷ_CHAIN (t2))
    ଯଦି (!c_safe_arg_type_equiv_p (ବୃକ୍ଷ_ମୂଲ୍ୟ (t1), ବୃକ୍ଷ_ମୂଲ୍ୟ (t2)))
      ଫେରନ୍ତୁ ମିଥ୍ୟା;

  ଫେରନ୍ତୁ ସତ୍ୟ;
}

/* Build an expression representing a cast to type TYPE of expression EXPR.
   LOC is the location of the cast-- typically the open paren of the cast.  */

ବୃକ୍ଷ
build_c_cast (location_t loc, ବୃକ୍ଷ type, ବୃକ୍ଷ ପଦସମଷ୍ଟି)
{
  ବୃକ୍ଷ ମୂଲ୍ୟ;

  ତାର୍କିକ int_operands = ପଦସମଷ୍ଟି_INT_CONST_OPERANDS (ପଦସମଷ୍ଟି);

  ଯଦି (ବୃକ୍ଷ_CODE (ପଦସମଷ୍ଟି) == EXCESS_PRECISION_ପଦସମଷ୍ଟି)
    ପଦସମଷ୍ଟି = ବୃକ୍ଷ_OPERAND (ପଦସମଷ୍ଟି, 0);

  ମୂଲ୍ୟ = ପଦସମଷ୍ଟି;
  ଯଦି (int_operands)
    ମୂଲ୍ୟ = remove_c_maybe_const_ପଦସମଷ୍ଟି (ମୂଲ୍ୟ);

  ଯଦି (type == error_mark_ଗଣ୍ଠି || ପଦସମଷ୍ଟି == error_mark_ଗଣ୍ଠି)
    ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;

  /* The ObjC front-end uses TYPE_MAIN_VARIANT to tie together types differing
     only in <protocol> qualifications.  But when constructing cast expressions,
     the protocols do matter and must be kept around.  */
  ଯଦି (objc_is_object_ptr (type) && objc_is_object_ptr (ବୃକ୍ଷ_TYPE (ପଦସମଷ୍ଟି)))
    ଫେରନ୍ତୁ build1 (NOP_ପଦସମଷ୍ଟି, type, ପଦସମଷ୍ଟି);

  type = TYPE_MAIN_VARIANT (type);

  ଯଦି (ବୃକ୍ଷ_CODE (type) == ARRAY_TYPE)
    {
      error_at (loc, "cast specifies array type");
      ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
    }

  ଯଦି (ବୃକ୍ଷ_CODE (type) == FUNCTION_TYPE)
    {
      error_at (loc, "cast specifies function type");
      ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
    }

  ଯଦି (!VOID_TYPE_P (type))
    {
      ମୂଲ୍ୟ = require_complete_type (loc, ମୂଲ୍ୟ);
      ଯଦି (ମୂଲ୍ୟ == error_mark_ଗଣ୍ଠି)
	ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
    }

  ଯଦି (type == TYPE_MAIN_VARIANT (ବୃକ୍ଷ_TYPE (ମୂଲ୍ୟ)))
    {
      ଯଦି (RECORD_OR_UNION_TYPE_P (type)
	  && pedwarn (loc, OPT_Wpedantic,
		      "ISO C forbids casting nonscalar to the same type"))
	      ;
      ଅନ୍ୟଥା ଯଦି (warn_useless_cast && c_inhibit_evaluation_warnings == 0)
	warning_at (loc, OPT_Wuseless_cast,
		    "useless cast to type %qT", type);

      /* Convert to remove any qualifiers from VALUE's type.  */
      ମୂଲ୍ୟ = convert (type, ମୂଲ୍ୟ);
    }
  ଅନ୍ୟଥା ଯଦି (ବୃକ୍ଷ_CODE (type) == UNION_TYPE)
    {
      ବୃକ୍ଷ field;

      ପାଇଁ (field = TYPE_FIELDS (type); field; field = DECL_CHAIN (field))
	ଯଦି (ବୃକ୍ଷ_TYPE (field) != error_mark_ଗଣ୍ଠି
	    && comptypes (TYPE_MAIN_VARIANT (ବୃକ୍ଷ_TYPE (field)),
			  TYPE_MAIN_VARIANT (ବୃକ୍ଷ_TYPE (ମୂଲ୍ୟ))))
	  ଭାଙ୍ଗ;

      ଯଦି (field)
	{
	  ବୃକ୍ଷ t;
	  ତାର୍କିକ maybe_const = ସତ୍ୟ;

	  pedwarn (loc, OPT_Wpedantic, "ISO C forbids casts to union type");
	  t = c_fully_fold (ମୂଲ୍ୟ, ମିଥ୍ୟା, &maybe_const);
	  t = build_constructor_single (type, field, t);
	  ଯଦି (!maybe_const)
	    t = c_wrap_maybe_const (t, ସତ୍ୟ);
	  t = digest_init (loc, field, type, t,
			   NULL_ବୃକ୍ଷ, ମିଥ୍ୟା, ମିଥ୍ୟା, ମିଥ୍ୟା, ସତ୍ୟ, ମିଥ୍ୟା, ମିଥ୍ୟା);
	  ବୃକ୍ଷ_CONSTANT (t) = ବୃକ୍ଷ_CONSTANT (ମୂଲ୍ୟ);
	  ଫେରନ୍ତୁ t;
	}
      error_at (loc, "cast to union type from type not present in union");
      ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
    }
  ଅନ୍ୟଥା
    {
      ବୃକ୍ଷ otype, ovalue;

      ଯଦି (type == void_type_ଗଣ୍ଠି)
	{
	  ବୃକ୍ଷ t = build1 (CONVERT_ପଦସମଷ୍ଟି, type, ମୂଲ୍ୟ);
	  SET_ପଦସମଷ୍ଟି_LOCATION (t, loc);
	  ଫେରନ୍ତୁ t;
	}

      otype = ବୃକ୍ଷ_TYPE (ମୂଲ୍ୟ);

      /* Optionally warn about potentially worrisome casts.  */
      ଯଦି (warn_cast_qual
	  && ବୃକ୍ଷ_CODE (type) == POINTER_TYPE
	  && ବୃକ୍ଷ_CODE (otype) == POINTER_TYPE)
	handle_warn_cast_qual (loc, type, otype);

      /* Warn about conversions between pointers to disjoint
	 address spaces.  */
      ଯଦି (ବୃକ୍ଷ_CODE (type) == POINTER_TYPE
	  && ବୃକ୍ଷ_CODE (otype) == POINTER_TYPE
	  && !null_pointer_constant_p (ମୂଲ୍ୟ))
	{
	  addr_space_t as_to = TYPE_ADDR_SPACE (ବୃକ୍ଷ_TYPE (type));
	  addr_space_t as_from = TYPE_ADDR_SPACE (ବୃକ୍ଷ_TYPE (otype));
	  addr_space_t as_common;

	  ଯଦି (!addr_space_superset (as_to, as_from, &as_common))
	    {
	      ଯଦି (ADDR_SPACE_GENERIC_P (as_from))
		warning_at (loc, 0, "cast to %qs address space pointer "
			    "from disjoint generic address space pointer",
			    c_addr_space_name (as_to));

	      ଅନ୍ୟଥା ଯଦି (ADDR_SPACE_GENERIC_P (as_to))
		warning_at (loc, 0, "cast to generic address space pointer "
			    "from disjoint %qs address space pointer",
			    c_addr_space_name (as_from));

	      ଅନ୍ୟଥା
		warning_at (loc, 0, "cast to %qs address space pointer "
			    "from disjoint %qs address space pointer",
			    c_addr_space_name (as_to),
			    c_addr_space_name (as_from));
	    }

	  /* Warn of new allocations that are not big enough for the target
	     type.  */
	  ଯଦି (warn_alloc_size && ବୃକ୍ଷ_CODE (ମୂଲ୍ୟ) == CALL_ପଦସମଷ୍ଟି)
	    ଯଦି (ବୃକ୍ଷ fndecl = get_callee_fndecl (ମୂଲ୍ୟ))
	      ଯଦି (DECL_IS_MALLOC (fndecl))
		{
		  ବୃକ୍ଷ attrs = TYPE_ATTRIBUTES (ବୃକ୍ଷ_TYPE (fndecl));
		  ବୃକ୍ଷ alloc_size = lookup_attribute ("alloc_size", attrs);
		  ଯଦି (alloc_size)
		    warn_for_alloc_size (loc, ବୃକ୍ଷ_TYPE (type), ମୂଲ୍ୟ,
					 alloc_size);
		}
	}

      /* Warn about possible alignment problems.  */
      ଯଦି ((STRICT_ALIGNMENT || warn_cast_align == 2)
	  && ବୃକ୍ଷ_CODE (type) == POINTER_TYPE
	  && ବୃକ୍ଷ_CODE (otype) == POINTER_TYPE
	  && ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (otype)) != VOID_TYPE
	  && ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (otype)) != FUNCTION_TYPE
	  /* Don't warn about opaque types, where the actual alignment
	     restriction is unknown.  */
	  && !(RECORD_OR_UNION_TYPE_P (ବୃକ୍ଷ_TYPE (otype))
	       && TYPE_MODE (ବୃକ୍ଷ_TYPE (otype)) == VOIDmode)
	  && min_align_of_type (ବୃକ୍ଷ_TYPE (type))
	     > min_align_of_type (ବୃକ୍ଷ_TYPE (otype)))
	warning_at (loc, OPT_Wcast_align,
		    "cast increases required alignment of target type");

      ଯଦି ((ବୃକ୍ଷ_CODE (type) == INTEGER_TYPE
	   || ବୃକ୍ଷ_CODE (type) == BITINT_TYPE)
	  && ବୃକ୍ଷ_CODE (otype) == POINTER_TYPE
	  && TYPE_PRECISION (type) != TYPE_PRECISION (otype))
      /* Unlike conversion of integers to pointers, where the
         warning is disabled for converting constants because
         of cases such as SIG_*, warn about converting constant
         pointers to integers. In some cases it may cause unwanted
         sign extension, and a warning is appropriate.  */
	warning_at (loc, OPT_Wpointer_to_int_cast,
		    "cast from pointer to integer of different size");

      ଯଦି ((ବୃକ୍ଷ_CODE (ମୂଲ୍ୟ) == CALL_ପଦସମଷ୍ଟି
	   && !is_access_with_size_p (ମୂଲ୍ୟ))
	  && ବୃକ୍ଷ_CODE (type) != ବୃକ୍ଷ_CODE (otype))
	warning_at (loc, OPT_Wbad_function_cast,
		    "cast from function call of type %qT "
		    "to non-matching type %qT", otype, type);

      ଯଦି (ବୃକ୍ଷ_CODE (type) == POINTER_TYPE
	  && (ବୃକ୍ଷ_CODE (otype) == INTEGER_TYPE
	      || ବୃକ୍ଷ_CODE (otype) == BITINT_TYPE)
	  && TYPE_PRECISION (type) != TYPE_PRECISION (otype)
	  /* Don't warn about converting any constant.  */
	  && !ବୃକ୍ଷ_CONSTANT (ମୂଲ୍ୟ))
	warning_at (loc,
		    OPT_Wint_to_pointer_cast, "cast to pointer from integer "
		    "of different size");

      ଯଦି (warn_strict_aliasing <= 2)
        strict_aliasing_warning (ପଦସମଷ୍ଟି_LOCATION (ମୂଲ୍ୟ), type, ପଦସମଷ୍ଟି);

      /* If pedantic, warn for conversions between function and object
	 pointer types, except for converting a null pointer constant
	 to function pointer type.  */
      ଯଦି (pedantic
	  && ବୃକ୍ଷ_CODE (type) == POINTER_TYPE
	  && ବୃକ୍ଷ_CODE (otype) == POINTER_TYPE
	  && ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (otype)) == FUNCTION_TYPE
	  && ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (type)) != FUNCTION_TYPE)
	pedwarn (loc, OPT_Wpedantic, "ISO C forbids "
		 "conversion of function pointer to object pointer type");

      ଯଦି (pedantic
	  && ବୃକ୍ଷ_CODE (type) == POINTER_TYPE
	  && ବୃକ୍ଷ_CODE (otype) == POINTER_TYPE
	  && ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (type)) == FUNCTION_TYPE
	  && ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (otype)) != FUNCTION_TYPE
	  && !null_pointer_constant_p (ମୂଲ୍ୟ))
	pedwarn (loc, OPT_Wpedantic, "ISO C forbids "
		 "conversion of object pointer to function pointer type");

      ଯଦି (ବୃକ୍ଷ_CODE (type) == POINTER_TYPE
	  && ବୃକ୍ଷ_CODE (otype) == POINTER_TYPE
	  && ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (type)) == FUNCTION_TYPE
	  && ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (otype)) == FUNCTION_TYPE
	  && !c_safe_function_type_cast_p (ବୃକ୍ଷ_TYPE (type),
					   ବୃକ୍ଷ_TYPE (otype)))
	warning_at (loc, OPT_Wcast_function_type,
		    "cast between incompatible function types"
		    " from %qT to %qT", otype, type);

      ovalue = ମୂଲ୍ୟ;
      /* If converting to boolean a value with integer operands that
	 is not itself represented as an INTEGER_CST, the call below
	 to note_integer_operands may insert a C_MAYBE_CONST_EXPR, but
	 build_binary_op as called by c_common_truthvalue_conversion
	 may also insert a C_MAYBE_CONST_EXPR to indicate that a
	 subexpression has been fully folded.  To avoid nested
	 C_MAYBE_CONST_EXPR, ensure that
	 c_objc_common_truthvalue_conversion receives an argument
	 properly marked as having integer operands in that case.  */
      ଯଦି (int_operands
	  && ବୃକ୍ଷ_CODE (ମୂଲ୍ୟ) != INTEGER_CST
	  && (ବୃକ୍ଷ_CODE (type) == BOOLEAN_TYPE
	      || (ବୃକ୍ଷ_CODE (type) == ENUMERAL_TYPE
		  && ENUM_UNDERLYING_TYPE (type) != NULL_ବୃକ୍ଷ
		  && ବୃକ୍ଷ_CODE (ENUM_UNDERLYING_TYPE (type)) == BOOLEAN_TYPE)))
	ମୂଲ୍ୟ = note_integer_operands (ମୂଲ୍ୟ);
      ମୂଲ୍ୟ = convert (type, ମୂଲ୍ୟ);

      /* Ignore any integer overflow caused by the cast.  */
      ଯଦି (ବୃକ୍ଷ_CODE (ମୂଲ୍ୟ) == INTEGER_CST && !FLOAT_TYPE_P (otype))
	{
	  ଯଦି (ବୃକ୍ଷ_OVERFLOW_P (ovalue))
	    {
	      ଯଦି (!ବୃକ୍ଷ_OVERFLOW (ମୂଲ୍ୟ))
		{
		  /* Avoid clobbering a shared constant.  */
		  ମୂଲ୍ୟ = copy_ଗଣ୍ଠି (ମୂଲ୍ୟ);
		  ବୃକ୍ଷ_OVERFLOW (ମୂଲ୍ୟ) = ବୃକ୍ଷ_OVERFLOW (ovalue);
		}
	    }
	  ଅନ୍ୟଥା ଯଦି (ବୃକ୍ଷ_OVERFLOW (ମୂଲ୍ୟ))
	    /* Reset VALUE's overflow flags, ensuring constant sharing.  */
	    ମୂଲ୍ୟ = wide_int_to_ବୃକ୍ଷ (ବୃକ୍ଷ_TYPE (ମୂଲ୍ୟ), wi::to_wide (ମୂଲ୍ୟ));
	}
    }

  /* Don't let a cast be an lvalue.  */
  ଯଦି (lvalue_p (ମୂଲ୍ୟ)
      /* Also, don't let a cast be a bit-field of a bit-precise integer type,
	 otherwise it could be incorrectly subject of integer promotions.  */
      || (ବୃକ୍ଷ_CODE (ମୂଲ୍ୟ) == COMPONENT_REF
	  && DECL_C_BIT_FIELD (ବୃକ୍ଷ_OPERAND (ମୂଲ୍ୟ, 1))
	  && BITINT_TYPE_P (DECL_BIT_FIELD_TYPE (ବୃକ୍ଷ_OPERAND (ମୂଲ୍ୟ, 1)))))
    ମୂଲ୍ୟ = non_lvalue_loc (loc, ମୂଲ୍ୟ);

  /* Don't allow the results of casting to floating-point or complex
     types be confused with actual constants, or casts involving
     integer and pointer types other than direct integer-to-integer
     and integer-to-pointer be confused with integer constant
     expressions and null pointer constants.  */
  ଯଦି (ବୃକ୍ଷ_CODE (ମୂଲ୍ୟ) == REAL_CST
      || ବୃକ୍ଷ_CODE (ମୂଲ୍ୟ) == COMPLEX_CST
      || (ବୃକ୍ଷ_CODE (ମୂଲ୍ୟ) == INTEGER_CST
	  && !((ବୃକ୍ଷ_CODE (ପଦସମଷ୍ଟି) == INTEGER_CST
		&& INTEGRAL_TYPE_P (ବୃକ୍ଷ_TYPE (ପଦସମଷ୍ଟି)))
	       || ବୃକ୍ଷ_CODE (ପଦସମଷ୍ଟି) == REAL_CST
	       || ବୃକ୍ଷ_CODE (ପଦସମଷ୍ଟି) == COMPLEX_CST)))
      ମୂଲ୍ୟ = build1 (NOP_ପଦସମଷ୍ଟି, type, ମୂଲ୍ୟ);

  /* If the expression has integer operands and so can occur in an
     unevaluated part of an integer constant expression, ensure the
     return value reflects this.  */
  ଯଦି (int_operands
      && INTEGRAL_TYPE_P (type)
      && ମୂଲ୍ୟ != error_mark_ଗଣ୍ଠି
      && !ପଦସମଷ୍ଟି_INT_CONST_OPERANDS (ମୂଲ୍ୟ))
    ମୂଲ୍ୟ = note_integer_operands (ମୂଲ୍ୟ);

  protected_set_ପଦସମଷ୍ଟି_location (ମୂଲ୍ୟ, loc);
  ଫେରନ୍ତୁ ମୂଲ୍ୟ;
}

/* Interpret a cast of expression EXPR to type TYPE.  LOC is the
   location of the open paren of the cast, or the position of the cast
   expr.  */
ବୃକ୍ଷ
c_cast_ପଦସମଷ୍ଟି (location_t loc, ସଂରଚନା c_type_name *type_name, ବୃକ୍ଷ ପଦସମଷ୍ଟି)
{
  ବୃକ୍ଷ type;
  ବୃକ୍ଷ type_ପଦସମଷ୍ଟି = NULL_ବୃକ୍ଷ;
  ତାର୍କିକ type_ପଦସମଷ୍ଟି_const = ସତ୍ୟ;
  ବୃକ୍ଷ ret;
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା saved_wsp = warn_strict_prototypes;

  /* This avoids warnings about unprototyped casts on
     integers.  E.g. "#define SIG_DFL (void(*)())0".  */
  ଯଦି (ବୃକ୍ଷ_CODE (ପଦସମଷ୍ଟି) == INTEGER_CST)
    warn_strict_prototypes = 0;
  type = groktypename (type_name, &type_ପଦସମଷ୍ଟି, &type_ପଦସମଷ୍ଟି_const);
  warn_strict_prototypes = saved_wsp;

  ଯଦି (ବୃକ୍ଷ_CODE (ପଦସମଷ୍ଟି) == ADDR_ପଦସମଷ୍ଟି && !VOID_TYPE_P (type)
      && reject_gcc_builtin (ପଦସମଷ୍ଟି))
    ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;

  ret = build_c_cast (loc, type, ପଦସମଷ୍ଟି);
  ଯଦି (ret == error_mark_ଗଣ୍ଠି)
    ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;

  ଯଦି (type_ପଦସମଷ୍ଟି)
    {
      ତାର୍କିକ inner_ପଦସମଷ୍ଟି_const = ସତ୍ୟ;
      ret = c_fully_fold (ret, require_constant_ମୂଲ୍ୟ, &inner_ପଦସମଷ୍ଟି_const);
      ret = build2 (C_MAYBE_CONST_ପଦସମଷ୍ଟି, ବୃକ୍ଷ_TYPE (ret), type_ପଦସମଷ୍ଟି, ret);
      C_MAYBE_CONST_ପଦସମଷ୍ଟି_NON_CONST (ret) = !(type_ପଦସମଷ୍ଟି_const
					     && inner_ପଦସମଷ୍ଟି_const);
      SET_ପଦସମଷ୍ଟି_LOCATION (ret, loc);
    }

  ଯଦି (!ପଦସମଷ୍ଟି_HAS_LOCATION (ret))
    protected_set_ପଦସମଷ୍ଟି_location (ret, loc);

  /* C++ does not permits types to be defined in a cast, but it
     allows references to incomplete types.  */
  ଯଦି (warn_cxx_compat && type_name->specs->typespec_kind == ctsk_tagdef)
    warning_at (loc, OPT_Wc___compat,
		"defining a type in a cast is invalid in C++");

  ଫେରନ୍ତୁ ret;
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

ବୃକ୍ଷ
build_modify_ପଦସମଷ୍ଟି (location_t location, ବୃକ୍ଷ lhs, ବୃକ୍ଷ lhs_origtype,
		   ଗଣନା ବୃକ୍ଷ_code modifycode,
		   location_t rhs_loc, ବୃକ୍ଷ rhs, ବୃକ୍ଷ rhs_origtype)
{
  ବୃକ୍ଷ result;
  ବୃକ୍ଷ newrhs;
  ବୃକ୍ଷ rhseval = NULL_ବୃକ୍ଷ;
  ବୃକ୍ଷ lhstype = ବୃକ୍ଷ_TYPE (lhs);
  ବୃକ୍ଷ olhstype = lhstype;
  ତାର୍କିକ npc;
  ତାର୍କିକ is_atomic_op;

  /* Types that aren't fully specified cannot be used in assignments.  */
  lhs = require_complete_type (location, lhs);
  rhs = require_complete_type (location, rhs);

  /* Avoid duplicate error messages from operands that had errors.  */
  ଯଦି (ବୃକ୍ଷ_CODE (lhs) == ERROR_MARK || ବୃକ୍ଷ_CODE (rhs) == ERROR_MARK)
    ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;

  /* Ensure an error for assigning a non-lvalue array to an array in
     C90.  */
  ଯଦି (ବୃକ୍ଷ_CODE (lhstype) == ARRAY_TYPE)
    {
      error_at (location, "assignment to expression with array type");
      ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
    }

  /* For ObjC properties, defer this check.  */
  ଯଦି (!objc_is_property_ref (lhs) && !lvalue_or_else (location, lhs, lv_assign))
    ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;

  is_atomic_op = really_atomic_lvalue (lhs);

  newrhs = rhs;

  ଯଦି (ବୃକ୍ଷ_CODE (lhs) == C_MAYBE_CONST_ପଦସମଷ୍ଟି)
    {
      ବୃକ୍ଷ inner = build_modify_ପଦସମଷ୍ଟି (location, C_MAYBE_CONST_ପଦସମଷ୍ଟି_ପଦସମଷ୍ଟି (lhs),
				      lhs_origtype, modifycode, rhs_loc, rhs,
				      rhs_origtype);
      ଯଦି (inner == error_mark_ଗଣ୍ଠି)
	ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
      result = build2 (C_MAYBE_CONST_ପଦସମଷ୍ଟି, ବୃକ୍ଷ_TYPE (inner),
		       C_MAYBE_CONST_ପଦସମଷ୍ଟି_PRE (lhs), inner);
      gcc_assert (!C_MAYBE_CONST_ପଦସମଷ୍ଟି_INT_OPERANDS (lhs));
      C_MAYBE_CONST_ପଦସମଷ୍ଟି_NON_CONST (result) = 1;
      protected_set_ପଦସମଷ୍ଟି_location (result, location);
      ଫେରନ୍ତୁ result;
    }

  /* If a binary op has been requested, combine the old LHS value with the RHS
     producing the value we should actually store into the LHS.  */

  ଯଦି (modifycode != NOP_ପଦସମଷ୍ଟି)
    {
      lhs = c_fully_fold (lhs, ମିଥ୍ୟା, ଖାଲି, ସତ୍ୟ);
      lhs = stabilize_reference (lhs);

      /* Construct the RHS for any non-atomic compound assignment. */
      ଯଦି (!is_atomic_op)
        {
	  /* If in LHS op= RHS the RHS has side-effects, ensure they
	     are preevaluated before the rest of the assignment expression's
	     side-effects, because RHS could contain e.g. function calls
	     that modify LHS.  */
	  ଯଦି (ବୃକ୍ଷ_SIDE_EFFECTS (rhs))
	    {
	      ଯଦି (ବୃକ୍ଷ_CODE (rhs) == EXCESS_PRECISION_ପଦସମଷ୍ଟି)
		newrhs = save_ପଦସମଷ୍ଟି (ବୃକ୍ଷ_OPERAND (rhs, 0));
	      ଅନ୍ୟଥା
		newrhs = save_ପଦସମଷ୍ଟି (rhs);
	      rhseval = newrhs;
	      ଯଦି (ବୃକ୍ଷ_CODE (rhs) == EXCESS_PRECISION_ପଦସମଷ୍ଟି)
		newrhs = build1 (EXCESS_PRECISION_ପଦସମଷ୍ଟି, ବୃକ୍ଷ_TYPE (rhs),
				 newrhs);
	    }
	  ତାର୍କିକ clear_decl_read = ମିଥ୍ୟା;
	  ଯଦି ((VAR_P (lhs) || ବୃକ୍ଷ_CODE (lhs) == PARM_DECL)
	      && !DECL_READ_P (lhs)
	      && (VAR_P (lhs) ? warn_unused_but_set_variable
			      : warn_unused_but_set_parameter) > 2)
	    {
	      mark_exp_read (newrhs);
	      ଯଦି (!DECL_READ_P (lhs))
		clear_decl_read = ସତ୍ୟ;
	    }

	  newrhs = build_ଦ୍ୱିମିକ_op (location, modifycode,
				    convert_lvalue_to_rvalue (location, lhs,
							      ସତ୍ୟ, ସତ୍ୟ),
				    newrhs, ସତ୍ୟ);
	  ଯଦି (clear_decl_read)
	    DECL_READ_P (lhs) = 0;

	  /* The original type of the right hand side is no longer
	     meaningful.  */
	  rhs_origtype = NULL_ବୃକ୍ଷ;
	}
    }

  ଯଦି (c_dialect_objc ())
    {
      /* Check if we are modifying an Objective-C property reference;
	 if so, we need to generate setter calls.  */
      ଯଦି (ବୃକ୍ଷ_CODE (newrhs) == EXCESS_PRECISION_ପଦସମଷ୍ଟି)
	result = objc_maybe_build_modify_ପଦସମଷ୍ଟି (lhs, ବୃକ୍ଷ_OPERAND (newrhs, 0));
      ଅନ୍ୟଥା
	result = objc_maybe_build_modify_ପଦସମଷ୍ଟି (lhs, newrhs);
      ଯଦି (result)
	ଯାଅ return_result;

      /* Else, do the check that we postponed for Objective-C.  */
      ଯଦି (!lvalue_or_else (location, lhs, lv_assign))
	ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
    }

  /* Give an error for storing in something that is 'const'.  */

  ଯଦି (TYPE_READONLY (lhstype)
      || (RECORD_OR_UNION_TYPE_P (lhstype)
	  && C_TYPE_FIELDS_READONLY (lhstype)))
    {
      readonly_error (location, lhs, lv_assign);
      ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
    }
  ଅନ୍ୟଥା ଯଦି (ବୃକ୍ଷ_READONLY (lhs))
    readonly_warning (lhs, lv_assign);

  /* If storing into a structure or union member,
     it has probably been given type `int'.
     Compute the type that would go with
     the actual amount of storage the member occupies.  */

  ଯଦି (ବୃକ୍ଷ_CODE (lhs) == COMPONENT_REF
      && (ବୃକ୍ଷ_CODE (lhstype) == INTEGER_TYPE
	  || ବୃକ୍ଷ_CODE (lhstype) == BOOLEAN_TYPE
	  || SCALAR_FLOAT_TYPE_P (lhstype)
	  || ବୃକ୍ଷ_CODE (lhstype) == ENUMERAL_TYPE))
    lhstype = ବୃକ୍ଷ_TYPE (get_unwidened (lhs, 0));

  /* If storing in a field that is in actuality a short or narrower than one,
     we must store in the field in its actual type.  */

  ଯଦି (lhstype != ବୃକ୍ଷ_TYPE (lhs))
    {
      lhs = copy_ଗଣ୍ଠି (lhs);
      ବୃକ୍ଷ_TYPE (lhs) = lhstype;
    }

  /* Issue -Wc++-compat warnings about an assignment to an enum type
     when LHS does not have its original type.  This happens for,
     e.g., an enum bitfield in a struct.  */
  ଯଦି (warn_cxx_compat
      && lhs_origtype != NULL_ବୃକ୍ଷ
      && lhs_origtype != lhstype
      && ବୃକ୍ଷ_CODE (lhs_origtype) == ENUMERAL_TYPE)
    {
      ବୃକ୍ଷ checktype = (rhs_origtype != NULL_ବୃକ୍ଷ
			? rhs_origtype
			: ବୃକ୍ଷ_TYPE (rhs));
      ଯଦି (checktype != error_mark_ଗଣ୍ଠି
	  && (TYPE_MAIN_VARIANT (checktype) != TYPE_MAIN_VARIANT (lhs_origtype)
	      || (is_atomic_op && modifycode != NOP_ପଦସମଷ୍ଟି)))
	warning_at (location, OPT_Wc___compat,
		    "enum conversion in assignment is invalid in C++");
    }

  /* Remove qualifiers.  */
  lhstype = c_build_qualified_type (lhstype, TYPE_UNQUALIFIED);
  olhstype = c_build_qualified_type (olhstype, TYPE_UNQUALIFIED);

  /* Convert new value to destination type.  Fold it first, then
     restore any excess precision information, for the sake of
     conversion warnings.  */

  ଯଦି (!(is_atomic_op && modifycode != NOP_ପଦସମଷ୍ଟି))
    {
      ବୃକ୍ଷ rhs_semantic_type = NULL_ବୃକ୍ଷ;
      ଯଦି (!c_in_omp_for)
	{
	  ଯଦି (ବୃକ୍ଷ_CODE (newrhs) == EXCESS_PRECISION_ପଦସମଷ୍ଟି)
	    {
	      rhs_semantic_type = ବୃକ୍ଷ_TYPE (newrhs);
	      newrhs = ବୃକ୍ଷ_OPERAND (newrhs, 0);
	    }
	  npc = null_pointer_constant_p (newrhs);
	  newrhs = c_fully_fold (newrhs, ମିଥ୍ୟା, ଖାଲି);
	  ଯଦି (rhs_semantic_type)
	    newrhs = build1 (EXCESS_PRECISION_ପଦସମଷ୍ଟି, rhs_semantic_type, newrhs);
	}
      ଅନ୍ୟଥା
	npc = null_pointer_constant_p (newrhs);
      newrhs = convert_for_assignment (location, rhs_loc, lhstype, newrhs,
				       rhs_origtype, ic_assign, npc,
				       NULL_ବୃକ୍ଷ, NULL_ବୃକ୍ଷ, 0);
      ଯଦି (ବୃକ୍ଷ_CODE (newrhs) == ERROR_MARK)
	ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
    }

  /* Emit ObjC write barrier, if necessary.  */
  ଯଦି (c_dialect_objc () && flag_objc_gc)
    {
      result = objc_generate_write_barrier (lhs, modifycode, newrhs);
      ଯଦି (result)
	{
	  protected_set_ପଦସମଷ୍ଟି_location (result, location);
	  ଯାଅ return_result;
	}
    }

  /* Scan operands.  */

  ଯଦି (is_atomic_op)
    result = build_atomic_assign (location, lhs, modifycode, newrhs, ମିଥ୍ୟା);
  ଅନ୍ୟଥା
    {
      result = build2 (MODIFY_ପଦସମଷ୍ଟି, lhstype, lhs, newrhs);
      ବୃକ୍ଷ_SIDE_EFFECTS (result) = 1;
      protected_set_ପଦସମଷ୍ଟି_location (result, location);
    }

  /* If we got the LHS in a different type for storing in,
     convert the result back to the nominal type of LHS
     so that the value we return always has the same type
     as the LHS argument.  */

  ଯଦି (olhstype == ବୃକ୍ଷ_TYPE (result))
    ଯାଅ return_result;

  result = convert_for_assignment (location, rhs_loc, olhstype, result,
				   rhs_origtype, ic_assign, ମିଥ୍ୟା, NULL_ବୃକ୍ଷ,
				   NULL_ବୃକ୍ଷ, 0);
  protected_set_ପଦସମଷ୍ଟି_location (result, location);

return_result:
  ଯଦି (rhseval)
    result = build2 (COMPOUND_ପଦସମଷ୍ଟି, ବୃକ୍ଷ_TYPE (result), rhseval, result);
  ଫେରନ୍ତୁ result;
}

/* Return whether STRUCT_TYPE has an anonymous field with type TYPE.
   This is used to implement -fplan9-extensions.  */

ସ୍ଥିର ତାର୍କିକ
find_anonymous_field_with_type (ବୃକ୍ଷ struct_type, ବୃକ୍ଷ type)
{
  ବୃକ୍ଷ field;
  ତାର୍କିକ found;

  gcc_assert (RECORD_OR_UNION_TYPE_P (struct_type));
  found = ମିଥ୍ୟା;
  ପାଇଁ (field = TYPE_FIELDS (struct_type);
       field != NULL_ବୃକ୍ଷ;
       field = ବୃକ୍ଷ_CHAIN (field))
    {
      ବୃକ୍ଷ fieldtype = remove_qualifiers (ବୃକ୍ଷ_TYPE (field));
      ଯଦି (DECL_NAME (field) == ଖାଲି
	  && comptypes (type, fieldtype))
	{
	  ଯଦି (found)
	    ଫେରନ୍ତୁ ମିଥ୍ୟା;
	  found = ସତ୍ୟ;
	}
      ଅନ୍ୟଥା ଯଦି (DECL_NAME (field) == ଖାଲି
	       && RECORD_OR_UNION_TYPE_P (ବୃକ୍ଷ_TYPE (field))
	       && find_anonymous_field_with_type (ବୃକ୍ଷ_TYPE (field), type))
	{
	  ଯଦି (found)
	    ଫେରନ୍ତୁ ମିଥ୍ୟା;
	  found = ସତ୍ୟ;
	}
    }
  ଫେରନ୍ତୁ found;
}

/* RHS is an expression whose type is pointer to struct.  If there is
   an anonymous field in RHS with type TYPE, then return a pointer to
   that field in RHS.  This is used with -fplan9-extensions.  This
   returns NULL if no conversion could be found.  */

ସ୍ଥିର ବୃକ୍ଷ
convert_to_anonymous_field (location_t location, ବୃକ୍ଷ type, ବୃକ୍ଷ rhs)
{
  ବୃକ୍ଷ rhs_struct_type, lhs_main_type;
  ବୃକ୍ଷ field, found_field;
  ତାର୍କିକ found_sub_field;
  ବୃକ୍ଷ ret;

  gcc_assert (POINTER_TYPE_P (ବୃକ୍ଷ_TYPE (rhs)));
  rhs_struct_type = ବୃକ୍ଷ_TYPE (ବୃକ୍ଷ_TYPE (rhs));
  gcc_assert (RECORD_OR_UNION_TYPE_P (rhs_struct_type));

  gcc_assert (POINTER_TYPE_P (type));
  lhs_main_type = remove_qualifiers (ବୃକ୍ଷ_TYPE (type));

  found_field = NULL_ବୃକ୍ଷ;
  found_sub_field = ମିଥ୍ୟା;
  ପାଇଁ (field = TYPE_FIELDS (rhs_struct_type);
       field != NULL_ବୃକ୍ଷ;
       field = ବୃକ୍ଷ_CHAIN (field))
    {
      ଯଦି (DECL_NAME (field) != NULL_ବୃକ୍ଷ
	  || !RECORD_OR_UNION_TYPE_P (ବୃକ୍ଷ_TYPE (field)))
	ଜାରି;
      ବୃକ୍ଷ fieldtype = remove_qualifiers (ବୃକ୍ଷ_TYPE (field));
      ଯଦି (comptypes (lhs_main_type, fieldtype))
	{
	  ଯଦି (found_field != NULL_ବୃକ୍ଷ)
	    ଫେରନ୍ତୁ NULL_ବୃକ୍ଷ;
	  found_field = field;
	}
      ଅନ୍ୟଥା ଯଦି (find_anonymous_field_with_type (ବୃକ୍ଷ_TYPE (field),
					       lhs_main_type))
	{
	  ଯଦି (found_field != NULL_ବୃକ୍ଷ)
	    ଫେରନ୍ତୁ NULL_ବୃକ୍ଷ;
	  found_field = field;
	  found_sub_field = ସତ୍ୟ;
	}
    }

  ଯଦି (found_field == NULL_ବୃକ୍ଷ)
    ଫେରନ୍ତୁ NULL_ବୃକ୍ଷ;

  ret = fold_build3_loc (location, COMPONENT_REF, ବୃକ୍ଷ_TYPE (found_field),
			 build_fold_indirect_ref (rhs), found_field,
			 NULL_ବୃକ୍ଷ);
  ret = build_fold_addr_ପଦସମଷ୍ଟି_loc (location, ret);

  ଯଦି (found_sub_field)
    {
      ret = convert_to_anonymous_field (location, type, ret);
      gcc_assert (ret != NULL_ବୃକ୍ଷ);
    }

  ଫେରନ୍ତୁ ret;
}

/* Issue an error message for a bad initializer component.
   GMSGID identifies the message.
   The component name is taken from the spelling stack.  */

ସ୍ଥିର ଶୂନ୍ୟ ATTRIBUTE_GCC_DIAG (2,0)
error_init (location_t loc, ଅଚଳ ଅକ୍ଷର *gmsgid, ...)
{
  ଅକ୍ଷର *ofwhat;

  auto_diagnostic_group d;

  /* The gmsgid may be a format string with %< and %>. */
  va_list ap;
  va_start (ap, gmsgid);
  ତାର୍କିକ warned = emit_diagnostic_valist (diagnostics::kind::error,
					loc, -1, gmsgid, &ap);
  va_end (ap);

  ofwhat = print_spelling ((ଅକ୍ଷର *) alloca (spelling_length () + 1));
  ଯଦି (*ofwhat && warned)
    inform (loc, "(near initialization for %qs)", ofwhat);
}

/* Used to implement pedwarn_init and permerror_init.  */

ସ୍ଥିର ତାର୍କିକ ATTRIBUTE_GCC_DIAG (3,0)
pedwarn_permerror_init (location_t loc, ପୂର୍ଣ୍ଣସଂଖ୍ୟା opt, ଅଚଳ ଅକ୍ଷର *gmsgid,
			va_list *ap, ଗଣନା diagnostics::kind kind)
{
  /* Use the location where a macro was expanded rather than where
     it was defined to make sure macros defined in system headers
     but used incorrectly elsewhere are diagnosed.  */
  location_t exploc = expansion_point_location_if_in_system_header (loc);
  auto_diagnostic_group d;
  ତାର୍କିକ warned = emit_diagnostic_valist (kind, exploc, opt, gmsgid, ap);
  ଯଦି (warned)
    {
      ଅକ୍ଷର *ofwhat = print_spelling ((ଅକ୍ଷର *) alloca (spelling_length () + 1));
      ଯଦି (*ofwhat)
	inform (exploc, "(near initialization for %qs)", ofwhat);
    }
  ଫେରନ୍ତୁ warned;
}

/* Issue a pedantic warning for a bad initializer component.  OPT is
   the option OPT_* (from options.h) controlling this warning or 0 if
   it is unconditionally given.  GMSGID identifies the message.  The
   component name is taken from the spelling stack.  */

ସ୍ଥିର ତାର୍କିକ ATTRIBUTE_GCC_DIAG (3,0)
pedwarn_init (location_t loc, ପୂର୍ଣ୍ଣସଂଖ୍ୟା opt, ଅଚଳ ଅକ୍ଷର *gmsgid, ...)
{
  va_list ap;
  va_start (ap, gmsgid);
  ତାର୍କିକ warned = pedwarn_permerror_init (loc, opt, gmsgid, &ap,
					diagnostics::kind::pedwarn);
  va_end (ap);
  ଫେରନ୍ତୁ warned;
}

/* Like pedwarn_init, but issue a permerror.  */

ସ୍ଥିର ତାର୍କିକ ATTRIBUTE_GCC_DIAG (3,0)
permerror_init (location_t loc, ପୂର୍ଣ୍ଣସଂଖ୍ୟା opt, ଅଚଳ ଅକ୍ଷର *gmsgid, ...)
{
  va_list ap;
  va_start (ap, gmsgid);
  ତାର୍କିକ warned = pedwarn_permerror_init (loc, opt, gmsgid, &ap,
					diagnostics::kind::permerror);
  va_end (ap);
  ଫେରନ୍ତୁ warned;
}

/* Issue a warning for a bad initializer component.

   OPT is the OPT_W* value corresponding to the warning option that
   controls this warning.  GMSGID identifies the message.  The
   component name is taken from the spelling stack.  */

ସ୍ଥିର ଶୂନ୍ୟ
warning_init (location_t loc, ପୂର୍ଣ୍ଣସଂଖ୍ୟା opt, ଅଚଳ ଅକ୍ଷର *gmsgid)
{
  ଅକ୍ଷର *ofwhat;
  ତାର୍କିକ warned;

  auto_diagnostic_group d;

  /* Use the location where a macro was expanded rather than where
     it was defined to make sure macros defined in system headers
     but used incorrectly elsewhere are diagnosed.  */
  location_t exploc = expansion_point_location_if_in_system_header (loc);

  /* The gmsgid may be a format string with %< and %>. */
  warned = warning_at (exploc, opt, gmsgid);
  ଯଦି (warned)
    {
      ofwhat = print_spelling ((ଅକ୍ଷର *) alloca (spelling_length () + 1));
      ଯଦି (*ofwhat)
	inform (exploc, "(near initialization for %qs)", ofwhat);
    }
}

/* If TYPE is an array type and EXPR is a parenthesized string
   constant, warn if pedantic that EXPR is being used to initialize an
   object of type TYPE.  */

ଶୂନ୍ୟ
maybe_warn_string_init (location_t loc, ବୃକ୍ଷ type, ସଂରଚନା c_ପଦସମଷ୍ଟି ପଦସମଷ୍ଟି)
{
  ଯଦି (pedantic
      && ବୃକ୍ଷ_CODE (type) == ARRAY_TYPE
      && ବୃକ୍ଷ_CODE (ପଦସମଷ୍ଟି.ମୂଲ୍ୟ) == STRING_CST
      && ପଦସମଷ୍ଟି.original_code != STRING_CST)
    pedwarn_init (loc, OPT_Wpedantic,
		  "array initialized from parenthesized string constant");
}

/* Attempt to locate the parameter with the given index within FNDECL,
   returning DECL_SOURCE_LOCATION (FNDECL) if it can't be found.  */

ସ୍ଥିର location_t
get_fndecl_argument_location (ବୃକ୍ଷ fndecl, ପୂର୍ଣ୍ଣସଂଖ୍ୟା argnum)
{
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;
  ବୃକ୍ଷ param;

  /* Locate param by index within DECL_ARGUMENTS (fndecl).  */
  ପାଇଁ (i = 0, param = DECL_ARGUMENTS (fndecl);
       i < argnum && param;
       i++, param = ବୃକ୍ଷ_CHAIN (param))
    ;

  /* If something went wrong (e.g. if we have a builtin and thus no arguments),
     return DECL_SOURCE_LOCATION (FNDECL).  */
  ଯଦି (param == ଖାଲି)
    ଫେରନ୍ତୁ DECL_SOURCE_LOCATION (fndecl);

  ଫେରନ୍ତୁ DECL_SOURCE_LOCATION (param);
}

/* Issue a note about a mismatching argument for parameter PARMNUM
   to FUNDECL, for types EXPECTED_TYPE and ACTUAL_TYPE.
   Attempt to issue the note at the pertinent parameter of the decl;
   failing that issue it at the location of FUNDECL; failing that
   issue it at PLOC.
   Use highlight_colors::actual for the ACTUAL_TYPE
   and highlight_colors::expected for EXPECTED_TYPE and the
   parameter of FUNDECL*/

ସ୍ଥିର ଶୂନ୍ୟ
inform_for_arg (ବୃକ୍ଷ fundecl, location_t ploc, ପୂର୍ଣ୍ଣସଂଖ୍ୟା parmnum,
		ବୃକ୍ଷ expected_type, ବୃକ୍ଷ actual_type)
{
  location_t loc;
  ଯଦି (fundecl && !DECL_IS_UNDECLARED_BUILTIN (fundecl))
    loc = get_fndecl_argument_location (fundecl, parmnum - 1);
  ଅନ୍ୟଥା
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

ସ୍ଥିର ଶୂନ୍ୟ
maybe_warn_builtin_no_proto_arg (location_t loc, ବୃକ୍ଷ fundecl, ପୂର୍ଣ୍ଣସଂଖ୍ୟା parmnum,
				 ବୃକ୍ଷ parmtype, ବୃକ୍ଷ argtype)
{
  ବୃକ୍ଷ_code parmcode = ବୃକ୍ଷ_CODE (parmtype);
  ବୃକ୍ଷ_code argcode = ବୃକ୍ଷ_CODE (argtype);
  ବୃକ୍ଷ promoted = c_type_promotes_to (argtype);

  /* Avoid warning for enum arguments that promote to an integer type
     of the same size/mode.  */
  ଯଦି (parmcode == INTEGER_TYPE
      && argcode == ENUMERAL_TYPE
      && TYPE_MODE (parmtype) == TYPE_MODE (argtype))
    ଫେରନ୍ତୁ;

  ଯଦି ((parmcode == argcode
       || (parmcode == INTEGER_TYPE
	   && argcode == ENUMERAL_TYPE))
      && TYPE_MAIN_VARIANT (parmtype) == TYPE_MAIN_VARIANT (promoted))
    ଫେରନ୍ତୁ;

  /* This diagnoses even signed/unsigned mismatches.  Those might be
     safe in many cases but GCC may emit suboptimal code for them so
     warning on those cases drives efficiency improvements.  */
  ଯଦି (warning_at (loc, OPT_Wbuiltin_declaration_mismatch,
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

ଶ୍ରେଣୀ pp_element_quoted_decl : ସର୍ବସାଧାରଣ pp_element
{
ସର୍ବସାଧାରଣ:
  pp_element_quoted_decl (ବୃକ୍ଷ decl, ଅଚଳ ଅକ୍ଷର *highlight_color)
  : m_decl (decl),
    m_highlight_color (highlight_color)
  {
  }

  ଶୂନ୍ୟ add_to_phase_2 (pp_markup::context &ctxt) override
  {
    ctxt.begin_quote ();
    ctxt.begin_highlight_color (m_highlight_color);

    print_decl (ctxt);

    ctxt.end_highlight_color ();
    ctxt.end_quote ();
  }

  ଶୂନ୍ୟ print_decl (pp_markup::context &ctxt)
  {
    pretty_printer *ଅଚଳ pp = &ctxt.m_pp;
    pp->set_padding (pp_none);
    ଯଦି (DECL_NAME (m_decl))
      pp_identifier (pp, lang_hooks.decl_printable_name (m_decl, 2));
    ଅନ୍ୟଥା
      pp_string (pp, _("({anonymous})"));
  }

ବ୍ୟକ୍ତିଗତ:
  ବୃକ୍ଷ m_decl;
  ଅଚଳ ଅକ୍ଷର *m_highlight_color;
};

/* If TYPE is from a typedef, issue a note showing the location
   to the user.
   Use HIGHLIGHT_COLOR as the highlight color.  */

ସ୍ଥିର ଶୂନ୍ୟ
maybe_inform_typedef_location (ବୃକ୍ଷ type, ଅଚଳ ଅକ୍ଷର *highlight_color)
{
  ଯଦି (!typedef_variant_p (type))
    ଫେରନ୍ତୁ;

  ବୃକ୍ଷ typedef_decl = TYPE_NAME (type);
  gcc_assert (ବୃକ୍ଷ_CODE (typedef_decl) == TYPE_DECL);
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

ସ୍ଥିର ବୃକ୍ଷ
convert_for_assignment (location_t location, location_t ପଦସମଷ୍ଟି_loc, ବୃକ୍ଷ type,
			ବୃକ୍ଷ rhs, ବୃକ୍ଷ origtype, ଗଣନା impl_conv errtype,
			ତାର୍କିକ null_pointer_constant, ବୃକ୍ଷ fundecl,
			ବୃକ୍ଷ function, ପୂର୍ଣ୍ଣସଂଖ୍ୟା parmnum, ପୂର୍ଣ୍ଣସଂଖ୍ୟା warnopt /* = 0 */)
{
  ଗଣନା ବୃକ୍ଷ_code codel = ବୃକ୍ଷ_CODE (type);
  ବୃକ୍ଷ orig_rhs = rhs;
  ବୃକ୍ଷ rhstype;
  ଗଣନା ବୃକ୍ଷ_code coder;
  ବୃକ୍ଷ rname = NULL_ବୃକ୍ଷ;
  ତାର୍କିକ objc_ok = ମିଥ୍ୟା;

  /* Use the expansion point location to handle cases such as user's
     function returning a wrong-type macro defined in a system header.  */
  location = expansion_point_location_if_in_system_header (location);

  ଯଦି (errtype == ic_argpass)
    {
      ବୃକ୍ଷ selector;
      /* Change pointer to function to the function itself for
	 diagnostics.  */
      ଯଦି (ବୃକ୍ଷ_CODE (function) == ADDR_ପଦସମଷ୍ଟି
	  && ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_OPERAND (function, 0)) == FUNCTION_DECL)
	function = ବୃକ୍ଷ_OPERAND (function, 0);

      /* Handle an ObjC selector specially for diagnostics.  */
      selector = objc_message_selector ();
      rname = function;
      ଯଦି (selector && parmnum > 2)
	{
	  rname = selector;
	  parmnum -= 2;
	}
    }

  /* This macro is used to emit diagnostics to ensure that all format
     strings are complete sentences, visible to gettext and checked at
     compile time.  */
#define PEDWARN_FOR_ASSIGNMENT(LOCATION, PLOC, OPT, AR, AS, IN, RE)	 \
  କର {                                                                   \
    ବାଛ (errtype)                                                     \
      {                                                                  \
      ସ୍ଥିତି ic_argpass:                                                   \
	{								\
	  auto_diagnostic_group d;						\
	  ଯଦି (pedwarn (PLOC, OPT, AR, parmnum, rname))		\
	    inform_for_arg (fundecl, (PLOC), parmnum, type, rhstype); \
	}								\
        ଭାଙ୍ଗ;                                                           \
      ସ୍ଥିତି ic_assign:                                                    \
        pedwarn (LOCATION, OPT, AS);                                     \
        ଭାଙ୍ଗ;                                                           \
      ସ୍ଥିତି ic_init:                                                      \
      ସ୍ଥିତି ic_init_const:                                                \
        pedwarn_init (LOCATION, OPT, IN);                                \
        ଭାଙ୍ଗ;                                                           \
      ସ୍ଥିତି ic_return:                                                    \
        pedwarn (LOCATION, OPT, RE);					 \
        ଭାଙ୍ଗ;                                                           \
      ପୂର୍ବନିର୍ଦ୍ଧାରିତ:                                                           \
        gcc_unreachable ();                                              \
      }                                                                  \
  } ଯେତେବେଳେ (0)

  /* This macro is used to emit diagnostics to ensure that all format
     strings are complete sentences, visible to gettext and checked at
     compile time.  It can be called with 'pedwarn' or 'warning_at'.  */
#define WARNING_FOR_QUALIFIERS(PEDWARN, LOCATION, PLOC, OPT, AR, AS, IN, RE, QUALS) \
  କର {                                                                   \
    ବାଛ (errtype)                                                     \
      {                                                                  \
      ସ୍ଥିତି ic_argpass:                                                   \
	{								 \
	  auto_diagnostic_group d;					 \
	  ଯଦି (PEDWARN) {						 \
	    ଯଦି (pedwarn (PLOC, OPT, AR, parmnum, rname, QUALS))          \
	      inform_for_arg (fundecl, (PLOC), parmnum, type, rhstype);  \
	  } ଅନ୍ୟଥା {							 \
	    ଯଦି (warning_at (PLOC, OPT, AR, parmnum, rname, QUALS))	 \
	      inform_for_arg (fundecl, (PLOC), parmnum, type, rhstype);  \
	  }								 \
	}								 \
        ଭାଙ୍ଗ;                                                           \
      ସ୍ଥିତି ic_assign:                                                    \
	ଯଦି (PEDWARN)							 \
	  pedwarn (LOCATION, OPT, AS, QUALS);                            \
	ଅନ୍ୟଥା								 \
	  warning_at (LOCATION, OPT, AS, QUALS);                         \
        ଭାଙ୍ଗ;                                                           \
      ସ୍ଥିତି ic_init:                                                      \
      ସ୍ଥିତି ic_init_const:                                                \
	ଯଦି (PEDWARN)							 \
	  pedwarn (LOCATION, OPT, IN, QUALS);                            \
	ଅନ୍ୟଥା								 \
	  warning_at (LOCATION, OPT, IN, QUALS);                         \
        ଭାଙ୍ଗ;                                                           \
      ସ୍ଥିତି ic_return:                                                    \
	ଯଦି (PEDWARN)							 \
	  pedwarn (LOCATION, OPT, RE, QUALS);                            \
	ଅନ୍ୟଥା								 \
	  warning_at (LOCATION, OPT, RE, QUALS);                         \
        ଭାଙ୍ଗ;                                                           \
      ପୂର୍ବନିର୍ଦ୍ଧାରିତ:                                                           \
        gcc_unreachable ();                                              \
      }                                                                  \
  } ଯେତେବେଳେ (0)

  /* This macro is used to emit diagnostics to ensure that all format
     strings are complete sentences, visible to gettext and checked at
     compile time.  It is the same as PEDWARN_FOR_ASSIGNMENT but with an
     extra parameter to enumerate qualifiers.  */
#define PEDWARN_FOR_QUALIFIERS(LOCATION, PLOC, OPT, AR, AS, IN, RE, QUALS) \
   WARNING_FOR_QUALIFIERS (ସତ୍ୟ, LOCATION, PLOC, OPT, AR, AS, IN, RE, QUALS)


  ଯଦି (ବୃକ୍ଷ_CODE (rhs) == EXCESS_PRECISION_ପଦସମଷ୍ଟି)
    rhs = ବୃକ୍ଷ_OPERAND (rhs, 0);

  rhstype = ବୃକ୍ଷ_TYPE (rhs);
  coder = ବୃକ୍ଷ_CODE (rhstype);

  ଯଦି (coder == ERROR_MARK)
    ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;

  ଯଦି (c_dialect_objc ())
    {
      ପୂର୍ଣ୍ଣସଂଖ୍ୟା parmno;

      ବାଛ (errtype)
	{
	ସ୍ଥିତି ic_return:
	  parmno = 0;
	  ଭାଙ୍ଗ;

	ସ୍ଥିତି ic_assign:
	  parmno = -1;
	  ଭାଙ୍ଗ;

	ସ୍ଥିତି ic_init:
	ସ୍ଥିତି ic_init_const:
	  parmno = -2;
	  ଭାଙ୍ଗ;

	ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
	  parmno = parmnum;
	  ଭାଙ୍ଗ;
	}

      objc_ok = objc_compare_types (type, rhstype, parmno, rname);
    }

  ଯଦି (warn_cxx_compat)
    {
      ବୃକ୍ଷ checktype = origtype != NULL_ବୃକ୍ଷ ? origtype : rhstype;
      ଯଦି (checktype != error_mark_ଗଣ୍ଠି
	  && ବୃକ୍ଷ_CODE (type) == ENUMERAL_TYPE
	  && TYPE_MAIN_VARIANT (checktype) != TYPE_MAIN_VARIANT (type))
	ବାଛ (errtype)
	  {
	  ସ୍ଥିତି ic_argpass:
	    ଯଦି (pedwarn (ପଦସମଷ୍ଟି_loc, OPT_Wc___compat, "enum conversion when "
			 "passing argument %d of %qE is invalid in C++",
			 parmnum, rname))
	      inform ((fundecl && !DECL_IS_UNDECLARED_BUILTIN (fundecl))
		      ? DECL_SOURCE_LOCATION (fundecl) : ପଦସମଷ୍ଟି_loc,
		      "expected %qT but argument is of type %qT",
		      type, rhstype);
	    ଭାଙ୍ଗ;
	  ସ୍ଥିତି ic_assign:
	    pedwarn (location, OPT_Wc___compat, "enum conversion from %qT to "
		     "%qT in assignment is invalid in C++", rhstype, type);
	    ଭାଙ୍ଗ;
	  ସ୍ଥିତି ic_init:
	  ସ୍ଥିତି ic_init_const:
	    pedwarn_init (location, OPT_Wc___compat, "enum conversion from "
			  "%qT to %qT in initialization is invalid in C++",
			  rhstype, type);
	    ଭାଙ୍ଗ;
	  ସ୍ଥିତି ic_return:
	    pedwarn (location, OPT_Wc___compat, "enum conversion from %qT to "
		     "%qT in return is invalid in C++", rhstype, type);
	    ଭାଙ୍ଗ;
	  ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
	    gcc_unreachable ();
	  }
    }

  ଯଦି (warn_enum_conversion)
    {
      ବୃକ୍ଷ checktype = origtype != NULL_ବୃକ୍ଷ ? origtype : rhstype;
      ଯଦି (checktype != error_mark_ଗଣ୍ଠି
	  && ବୃକ୍ଷ_CODE (checktype) == ENUMERAL_TYPE
	  && ବୃକ୍ଷ_CODE (type) == ENUMERAL_TYPE
	  && !comptypes (TYPE_MAIN_VARIANT (checktype), TYPE_MAIN_VARIANT (type)))
       {
	  gcc_rich_location loc (location);
	  warning_at (&loc, OPT_Wenum_conversion,
		      "implicit conversion from %qT to %qT",
		      checktype, type);
       }
    }

  ଯଦି (TYPE_MAIN_VARIANT (type) == TYPE_MAIN_VARIANT (rhstype))
    {
      warn_for_address_of_packed_member (type, orig_rhs);
      ଯଦି (type != rhstype)
	/* Convert RHS to TYPE in order to not lose TYPE in diagnostics.  */
	rhs = convert (type, rhs);
      ଫେରନ୍ତୁ rhs;
    }

  ଯଦି (coder == VOID_TYPE)
    {
      /* Except for passing an argument to an unprototyped function,
	 this is a constraint violation.  When passing an argument to
	 an unprototyped function, it is compile-time undefined;
	 making it a constraint in that case was rejected in
	 DR#252.  */
      ଅଚଳ ଅକ୍ଷର ସନ୍ଦେଶ[] = "void value not ignored as it ought to be";
      ଯଦି (warnopt)
	warning_at (location, warnopt, ସନ୍ଦେଶ);
      ଅନ୍ୟଥା
	error_at (location, ସନ୍ଦେଶ);
      ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
    }
  rhs = require_complete_type (location, rhs);
  ଯଦି (rhs == error_mark_ଗଣ୍ଠି)
    ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;

  ଯଦି (coder == POINTER_TYPE && reject_gcc_builtin (rhs))
    ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;

  /* A non-reference type can convert to a reference.  This handles
     va_start, va_copy and possibly port built-ins.  */
  ଯଦି (codel == REFERENCE_TYPE && coder != REFERENCE_TYPE)
    {
      ଯଦି (!lvalue_p (rhs))
	{
	  ଅଚଳ ଅକ୍ଷର ସନ୍ଦେଶ[] = "cannot pass rvalue to reference parameter";
	  ଯଦି (warnopt)
	    warning_at (location, warnopt, ସନ୍ଦେଶ);
	  ଅନ୍ୟଥା
	    error_at (location, ସନ୍ଦେଶ);
	  ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
	}
      ଯଦି (!c_mark_addressable (rhs))
	ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
      rhs = build1 (ADDR_ପଦସମଷ୍ଟି, c_build_pointer_type (ବୃକ୍ଷ_TYPE (rhs)), rhs);
      SET_ପଦସମଷ୍ଟି_LOCATION (rhs, location);

      rhs = convert_for_assignment (location, ପଦସମଷ୍ଟି_loc,
				    c_build_pointer_type (ବୃକ୍ଷ_TYPE (type)),
				    rhs, origtype, errtype,
				    null_pointer_constant, fundecl, function,
				    parmnum, warnopt);
      ଯଦି (rhs == error_mark_ଗଣ୍ଠି)
	ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;

      rhs = build1 (NOP_ପଦସମଷ୍ଟି, type, rhs);
      SET_ପଦସମଷ୍ଟି_LOCATION (rhs, location);
      ଫେରନ୍ତୁ rhs;
    }
  /* Some types can interconvert without explicit casts.  */
  ଅନ୍ୟଥା ଯଦି (codel == VECTOR_TYPE && coder == VECTOR_TYPE
	   && vector_types_convertible_p (type, ବୃକ୍ଷ_TYPE (rhs), ସତ୍ୟ))
    ଫେରନ୍ତୁ convert (type, rhs);
  /* Arithmetic types all interconvert, and enum is treated like int.  */
  ଅନ୍ୟଥା ଯଦି ((codel == INTEGER_TYPE || codel == REAL_TYPE
	    || codel == FIXED_POINT_TYPE
	    || codel == ENUMERAL_TYPE || codel == COMPLEX_TYPE
	    || codel == BOOLEAN_TYPE || codel == BITINT_TYPE)
	   && (coder == INTEGER_TYPE || coder == REAL_TYPE
	       || coder == FIXED_POINT_TYPE
	       || coder == ENUMERAL_TYPE || coder == COMPLEX_TYPE
	       || coder == BOOLEAN_TYPE || coder == BITINT_TYPE))
    {
      ଯଦି (warnopt && errtype == ic_argpass)
	maybe_warn_builtin_no_proto_arg (ପଦସମଷ୍ଟି_loc, fundecl, parmnum, type,
					 rhstype);

      ତାର୍କିକ save = in_late_ଦ୍ୱିମିକ_op;
      ଯଦି (C_BOOLEAN_TYPE_P (type) || codel == COMPLEX_TYPE
	  || (coder == REAL_TYPE
	      && (codel == INTEGER_TYPE || codel == ENUMERAL_TYPE)
	      && sanitize_flags_p (SANITIZE_FLOAT_CAST)))
	in_late_ଦ୍ୱିମିକ_op = ସତ୍ୟ;
      ବୃକ୍ଷ ret = convert_and_check (ପଦସମଷ୍ଟି_loc != UNKNOWN_LOCATION
				    ? ପଦସମଷ୍ଟି_loc : location, type, orig_rhs,
				    errtype == ic_init_const);
      in_late_ଦ୍ୱିମିକ_op = save;
      ଫେରନ୍ତୁ ret;
    }

  /* Aggregates in different TUs might need conversion.  */
  ଯଦି ((codel == RECORD_TYPE || codel == UNION_TYPE)
      && codel == coder
      && comptypes (TYPE_MAIN_VARIANT (type), TYPE_MAIN_VARIANT (rhstype)))
    ଫେରନ୍ତୁ convert_and_check (ପଦସମଷ୍ଟି_loc != UNKNOWN_LOCATION
			      ? ପଦସମଷ୍ଟି_loc : location, type, rhs);

  /* Conversion to a transparent union or record from its member types.
     This applies only to function arguments.  */
  ଯଦି (((codel == UNION_TYPE || codel == RECORD_TYPE)
      && TYPE_TRANSPARENT_AGGR (type))
      && errtype == ic_argpass)
    {
      ବୃକ୍ଷ memb, marginal_memb = NULL_ବୃକ୍ଷ;

      ପାଇଁ (memb = TYPE_FIELDS (type); memb ; memb = DECL_CHAIN (memb))
	{
	  ବୃକ୍ଷ memb_type = ବୃକ୍ଷ_TYPE (memb);

	  ଯଦି (comptypes (TYPE_MAIN_VARIANT (memb_type),
			 TYPE_MAIN_VARIANT (rhstype)))
	    ଭାଙ୍ଗ;

	  ଯଦି (ବୃକ୍ଷ_CODE (memb_type) != POINTER_TYPE)
	    ଜାରି;

	  ଯଦି (coder == POINTER_TYPE)
	    {
	      ବୃକ୍ଷ ttl = ବୃକ୍ଷ_TYPE (memb_type);
	      ବୃକ୍ଷ ttr = ବୃକ୍ଷ_TYPE (rhstype);

	      /* Any non-function converts to a [const][volatile] void *
		 and vice versa; otherwise, targets must be the same.
		 Meanwhile, the lhs target must have all the qualifiers of
		 the rhs.  */
	      ଯଦି ((VOID_TYPE_P (ttl) && !TYPE_ATOMIC (ttl))
		  || (VOID_TYPE_P (ttr) && !TYPE_ATOMIC (ttr))
		  || comp_target_types (location, memb_type, rhstype))
		{
		  ପୂର୍ଣ୍ଣସଂଖ୍ୟା lquals = TYPE_QUALS (ttl) & ~TYPE_QUAL_ATOMIC;
		  ପୂର୍ଣ୍ଣସଂଖ୍ୟା rquals = TYPE_QUALS (ttr) & ~TYPE_QUAL_ATOMIC;
		  /* If this type won't generate any warnings, use it.  */
		  ଯଦି (lquals == rquals
		      || ((ବୃକ୍ଷ_CODE (ttr) == FUNCTION_TYPE
			   && ବୃକ୍ଷ_CODE (ttl) == FUNCTION_TYPE)
			  ? ((lquals | rquals) == rquals)
			  : ((lquals | rquals) == lquals)))
		    ଭାଙ୍ଗ;

		  /* Keep looking for a better type, but remember this one.  */
		  ଯଦି (!marginal_memb)
		    marginal_memb = memb;
		}
	    }

	  /* Can convert integer zero to any pointer type.  */
	  ଯଦି (null_pointer_constant)
	    {
	      rhs = null_pointer_ଗଣ୍ଠି;
	      ଭାଙ୍ଗ;
	    }
	}

      ଯଦି (memb || marginal_memb)
	{
	  ଯଦି (!memb)
	    {
	      /* We have only a marginally acceptable member type;
		 it needs a warning.  */
	      ବୃକ୍ଷ ttl = ବୃକ୍ଷ_TYPE (ବୃକ୍ଷ_TYPE (marginal_memb));
	      ବୃକ୍ଷ ttr = ବୃକ୍ଷ_TYPE (rhstype);

	      /* Const and volatile mean something different for function
		 types, so the usual warnings are not appropriate.  */
	      ଯଦି (ବୃକ୍ଷ_CODE (ttr) == FUNCTION_TYPE
		  && ବୃକ୍ଷ_CODE (ttl) == FUNCTION_TYPE)
		{
		  /* Because const and volatile on functions are
		     restrictions that say the function will not do
		     certain things, it is okay to use a const or volatile
		     function where an ordinary one is wanted, but not
		     vice-versa.  */
		  ଯଦି (TYPE_QUALS_NO_ADDR_SPACE (ttl)
		      & ~TYPE_QUALS_NO_ADDR_SPACE (ttr))
		    PEDWARN_FOR_QUALIFIERS (location, ପଦସମଷ୍ଟି_loc,
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
	      ଅନ୍ୟଥା ଯଦି (TYPE_QUALS_NO_ADDR_SPACE (ttr)
		       & ~TYPE_QUALS_NO_ADDR_SPACE (ttl))
		PEDWARN_FOR_QUALIFIERS (location, ପଦସମଷ୍ଟି_loc,
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

	  ଯଦି (!fundecl || !DECL_IN_SYSTEM_HEADER (fundecl))
	    pedwarn (location, OPT_Wpedantic,
		     "ISO C prohibits argument conversion to union type");

	  rhs = fold_convert_loc (location, ବୃକ୍ଷ_TYPE (memb), rhs);
	  ଫେରନ୍ତୁ build_constructor_single (type, memb, rhs);
	}
    }

  /* Conversions among pointers */
  ଅନ୍ୟଥା ଯଦି ((codel == POINTER_TYPE || codel == REFERENCE_TYPE)
	   && (coder == codel))
    {
      /* If RHS refers to a built-in declared without a prototype
	 BLTIN is the declaration of the built-in with a prototype
	 and RHSTYPE is set to the actual type of the built-in.  */
      ବୃକ୍ଷ bltin;
      rhstype = type_or_builtin_type (rhs, &bltin);

      ବୃକ୍ଷ ttl = ବୃକ୍ଷ_TYPE (type);
      ବୃକ୍ଷ ttr = ବୃକ୍ଷ_TYPE (rhstype);
      ତାର୍କିକ is_opaque_pointer;
      ତାର୍କିକ target_cmp = ମିଥ୍ୟା;   /* Cache comp_target_types () result.  */
      addr_space_t asl;
      addr_space_t asr;

      ବୃକ୍ଷ mvl = remove_qualifiers (ttl);
      ବୃକ୍ଷ mvr = remove_qualifiers (ttr);

      /* Opaque pointers are treated like void pointers.  */
      is_opaque_pointer = vector_targets_convertible_p (ttl, ttr);

      /* The Plan 9 compiler permits a pointer to a struct to be
	 automatically converted into a pointer to an anonymous field
	 within the struct.  */
      ଯଦି (flag_plan9_extensions
	  && RECORD_OR_UNION_TYPE_P (mvl)
	  && RECORD_OR_UNION_TYPE_P (mvr)
	  && mvl != mvr)
	{
	  ବୃକ୍ଷ new_rhs = convert_to_anonymous_field (location, type, rhs);
	  ଯଦି (new_rhs != NULL_ବୃକ୍ଷ)
	    {
	      rhs = new_rhs;
	      rhstype = ବୃକ୍ଷ_TYPE (rhs);
	      coder = ବୃକ୍ଷ_CODE (rhstype);
	      ttr = ବୃକ୍ଷ_TYPE (rhstype);
	      mvr = TYPE_MAIN_VARIANT (ttr);
	    }
	}

      /* C++ does not allow the implicit conversion void* -> T*.  However,
	 for the purpose of reducing the number of false positives, we
	 tolerate the special case of

		int *p = NULL;

	 where NULL is typically defined in C to be '(void *) 0'.  */
      ଯଦି (VOID_TYPE_P (ttr) && rhs != null_pointer_ଗଣ୍ଠି && !VOID_TYPE_P (ttl))
	warning_at (errtype == ic_argpass ? ପଦସମଷ୍ଟି_loc : location,
		    OPT_Wc___compat,
		    "request for implicit conversion "
		    "from %qT to %qT not permitted in C++", rhstype, type);

      /* Warn of new allocations that are not big enough for the target
	 type.  */
      ଯଦି (warn_alloc_size && ବୃକ୍ଷ_CODE (rhs) == CALL_ପଦସମଷ୍ଟି)
	ଯଦି (ବୃକ୍ଷ fndecl = get_callee_fndecl (rhs))
	  ଯଦି (DECL_IS_MALLOC (fndecl))
	    {
	      ବୃକ୍ଷ attrs = TYPE_ATTRIBUTES (ବୃକ୍ଷ_TYPE (fndecl));
	      ବୃକ୍ଷ alloc_size = lookup_attribute ("alloc_size", attrs);
	      ଯଦି (alloc_size)
		warn_for_alloc_size (location, ttl, rhs, alloc_size);
	    }

      /* See if the pointers point to incompatible address spaces.  */
      asl = TYPE_ADDR_SPACE (ttl);
      asr = TYPE_ADDR_SPACE (ttr);
      ଯଦି (!null_pointer_constant_p (rhs)
	  && asr != asl && !targetm.addr_space.subset_p (asr, asl))
	{
	  auto_diagnostic_group d;
	  ତାର୍କିକ diagnosed = ସତ୍ୟ;
	  ବାଛ (errtype)
	    {
	    ସ୍ଥିତି ic_argpass:
	      {
		ଅଚଳ ଅକ୍ଷର ସନ୍ଦେଶ[] = G_("passing argument %d of %qE from "
				      "pointer to non-enclosed address space");
		ଯଦି (warnopt)
		  diagnosed
		    = warning_at (ପଦସମଷ୍ଟି_loc, warnopt, ସନ୍ଦେଶ, parmnum, rname);
		ଅନ୍ୟଥା
		  error_at (ପଦସମଷ୍ଟି_loc, ସନ୍ଦେଶ, parmnum, rname);
	      ଭାଙ୍ଗ;
	      }
	    ସ୍ଥିତି ic_assign:
	      {
		ଅଚଳ ଅକ୍ଷର ସନ୍ଦେଶ[] = G_("assignment from pointer to "
				      "non-enclosed address space");
		ଯଦି (warnopt)
		  diagnosed = warning_at (location, warnopt, ସନ୍ଦେଶ);
		ଅନ୍ୟଥା
		  error_at (location, ସନ୍ଦେଶ);
		ଭାଙ୍ଗ;
	      }
	    ସ୍ଥିତି ic_init:
	    ସ୍ଥିତି ic_init_const:
	      {
		ଅଚଳ ଅକ୍ଷର ସନ୍ଦେଶ[] = G_("initialization from pointer to "
				      "non-enclosed address space");
		ଯଦି (warnopt)
		  diagnosed = warning_at (location, warnopt, ସନ୍ଦେଶ);
		ଅନ୍ୟଥା
		  error_at (location, ସନ୍ଦେଶ);
		ଭାଙ୍ଗ;
	      }
	    ସ୍ଥିତି ic_return:
	      {
		ଅଚଳ ଅକ୍ଷର ସନ୍ଦେଶ[] = G_("return from pointer to "
				      "non-enclosed address space");
		ଯଦି (warnopt)
		  diagnosed = warning_at (location, warnopt, ସନ୍ଦେଶ);
		ଅନ୍ୟଥା
		  error_at (location, ସନ୍ଦେଶ);
		ଭାଙ୍ଗ;
	      }
	    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
	      gcc_unreachable ();
	    }
	  ଯଦି (diagnosed)
	    {
	      ଯଦି (errtype == ic_argpass)
		inform_for_arg (fundecl, ପଦସମଷ୍ଟି_loc, parmnum, type, rhstype);
	      ଅନ୍ୟଥା
		inform (location, "expected %qT but pointer is of type %qT",
			type, rhstype);
	    }
	  ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
	}

      /* Check if the right-hand side has a format attribute but the
	 left-hand side doesn't.  */
      ଯଦି (warn_suggest_attribute_format
	  && check_missing_format_attribute (type, rhstype))
	{
	  ବାଛ (errtype)
	  {
	  ସ୍ଥିତି ic_argpass:
	    warning_at (ପଦସମଷ୍ଟି_loc, OPT_Wsuggest_attribute_format,
			"argument %d of %qE might be "
			"a candidate for a format attribute",
			parmnum, rname);
	    ଭାଙ୍ଗ;
	  ସ୍ଥିତି ic_assign:
	    warning_at (location, OPT_Wsuggest_attribute_format,
			"assignment left-hand side might be "
			"a candidate for a format attribute");
	    ଭାଙ୍ଗ;
	  ସ୍ଥିତି ic_init:
	  ସ୍ଥିତି ic_init_const:
	    warning_at (location, OPT_Wsuggest_attribute_format,
			"initialization left-hand side might be "
			"a candidate for a format attribute");
	    ଭାଙ୍ଗ;
	  ସ୍ଥିତି ic_return:
	    warning_at (location, OPT_Wsuggest_attribute_format,
			"return type might be "
			"a candidate for a format attribute");
	    ଭାଙ୍ଗ;
	  ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
	    gcc_unreachable ();
	  }
	}

      /* See if the pointers point to incompatible scalar storage orders.  */
      ଯଦି (warn_scalar_storage_order
	  && !null_pointer_constant_p (rhs)
	  && (AGGREGATE_TYPE_P (ttl) && TYPE_REVERSE_STORAGE_ORDER (ttl))
	     != (AGGREGATE_TYPE_P (ttr) && TYPE_REVERSE_STORAGE_ORDER (ttr)))
	{
	  ବୃକ୍ଷ t;

	  ବାଛ (errtype)
	  {
	  ସ୍ଥିତି ic_argpass:
	    /* Do not warn for built-in functions, for example memcpy, since we
	       control how they behave and they can be useful in this area.  */
	    ଯଦି (ବୃକ୍ଷ_CODE (rname) != FUNCTION_DECL
		|| !fndecl_built_in_p (rname))
	      warning_at (location, OPT_Wscalar_storage_order,
			  "passing argument %d of %qE from incompatible "
			  "scalar storage order", parmnum, rname);
	    ଭାଙ୍ଗ;
	  ସ୍ଥିତି ic_assign:
	    /* Do not warn if the RHS is a call to a function that returns a
	       pointer that is not an alias.  */
	    ଯଦି (ବୃକ୍ଷ_CODE (rhs) != CALL_ପଦସମଷ୍ଟି
		|| (t = get_callee_fndecl (rhs)) == NULL_ବୃକ୍ଷ
		|| !DECL_IS_MALLOC (t))
	      warning_at (location, OPT_Wscalar_storage_order,
			  "assignment to %qT from pointer type %qT with "
			  "incompatible scalar storage order", type, rhstype);
	    ଭାଙ୍ଗ;
	  ସ୍ଥିତି ic_init:
	  ସ୍ଥିତି ic_init_const:
	    /* Likewise.  */
	    ଯଦି (ବୃକ୍ଷ_CODE (rhs) != CALL_ପଦସମଷ୍ଟି
		|| (t = get_callee_fndecl (rhs)) == NULL_ବୃକ୍ଷ
		|| !DECL_IS_MALLOC (t))
	      warning_at (location, OPT_Wscalar_storage_order,
			  "initialization of %qT from pointer type %qT with "
			  "incompatible scalar storage order", type, rhstype);
	    ଭାଙ୍ଗ;
	  ସ୍ଥିତି ic_return:
	    warning_at (location, OPT_Wscalar_storage_order,
			"returning %qT from pointer type with incompatible "
			"scalar storage order %qT", rhstype, type);
	    ଭାଙ୍ଗ;
	  ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
	    gcc_unreachable ();
	  }
	}

      /* Any non-function converts to a [const][volatile] void *
	 and vice versa; otherwise, targets must be the same.
	 Meanwhile, the lhs target must have all the qualifiers of the rhs.  */
      ଯଦି ((VOID_TYPE_P (ttl) && !TYPE_ATOMIC (ttl))
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
	  ଯଦି (ବୃକ୍ଷ_CODE (ttr) == ARRAY_TYPE)
	    {
	      ttr = strip_array_types (ttr);
	      ttl = strip_array_types (ttl);

	      ଯଦି (TYPE_QUALS_NO_ADDR_SPACE_NO_ATOMIC (ttr)
		  & ~TYPE_QUALS_NO_ADDR_SPACE_NO_ATOMIC (ttl))
		WARNING_FOR_QUALIFIERS (flag_isoc23,
					location, ପଦସମଷ୍ଟି_loc,
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
          ଅନ୍ୟଥା ଯଦି (pedantic
	      && ((VOID_TYPE_P (ttl) && ବୃକ୍ଷ_CODE (ttr) == FUNCTION_TYPE)
		  ||
		  (VOID_TYPE_P (ttr)
		   && !null_pointer_constant
		   && ବୃକ୍ଷ_CODE (ttl) == FUNCTION_TYPE)))
	    PEDWARN_FOR_ASSIGNMENT (location, ପଦସମଷ୍ଟି_loc, OPT_Wpedantic,
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
	  ଅନ୍ୟଥା ଯଦି (ବୃକ୍ଷ_CODE (ttr) != FUNCTION_TYPE
		   && ବୃକ୍ଷ_CODE (ttl) != FUNCTION_TYPE)
	    {
	       /* Assignments between atomic and non-atomic objects are OK.  */
	       ତାର୍କିକ warn_quals_ped = TYPE_QUALS_NO_ADDR_SPACE_NO_ATOMIC (ttr)
				     & ~TYPE_QUALS_NO_ADDR_SPACE_NO_ATOMIC (ttl);
	       ତାର୍କିକ warn_quals = TYPE_QUALS_NO_ADDR_SPACE_NO_ATOMIC (ttr)
				 & ~TYPE_QUALS_NO_ADDR_SPACE_NO_ATOMIC (strip_array_types (ttl));

	      /* Don't warn about loss of qualifier for conversions from
		 qualified void* to pointers to arrays with corresponding
		 qualifier on the element type (except for pedantic before C23). */
	      ଯଦି (warn_quals || (warn_quals_ped && pedantic && !flag_isoc23))
		PEDWARN_FOR_QUALIFIERS (location, ପଦସମଷ୍ଟି_loc,
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
	      ଅନ୍ୟଥା ଯଦି (warn_quals_ped)
		pedwarn_c11 (location, OPT_Wc11_c23_compat,
			     "array with qualifier on the element is not qualified before C23");

	      /* If this is not a case of ignoring a mismatch in signedness,
		 no warning.  */
	      ଅନ୍ୟଥା ଯଦି (VOID_TYPE_P (ttl) || VOID_TYPE_P (ttr)
		       || target_cmp)
		;
	      /* If there is a mismatch, do warn.  */
	      ଅନ୍ୟଥା ଯଦି (warn_pointer_sign)
		ବାଛ (errtype)
		  {
		  ସ୍ଥିତି ic_argpass:
		    {
		      auto_diagnostic_group d;
		      range_label_for_type_mismatch rhs_label (rhstype, type);
		      gcc_rich_location richloc (ପଦସମଷ୍ଟି_loc, &rhs_label,
						 highlight_colors::actual);
		      ଯଦି (pedwarn (&richloc, OPT_Wpointer_sign,
				   "pointer targets in passing argument %d of "
				   "%qE differ in signedness", parmnum, rname))
			inform_for_arg (fundecl, ପଦସମଷ୍ଟି_loc, parmnum, type,
					rhstype);
		    }
		    ଭାଙ୍ଗ;
		  ସ୍ଥିତି ic_assign:
		    pedwarn (location, OPT_Wpointer_sign,
			     "pointer targets in assignment from %qT to %qT "
			     "differ in signedness", rhstype, type);
		    ଭାଙ୍ଗ;
		  ସ୍ଥିତି ic_init:
		  ସ୍ଥିତି ic_init_const:
		    pedwarn_init (location, OPT_Wpointer_sign,
				  "pointer targets in initialization of %qT "
				  "from %qT differ in signedness", type,
				  rhstype);
		    ଭାଙ୍ଗ;
		  ସ୍ଥିତି ic_return:
		    pedwarn (location, OPT_Wpointer_sign, "pointer targets in "
			     "returning %qT from a function with return type "
			     "%qT differ in signedness", rhstype, type);
		    ଭାଙ୍ଗ;
		  ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
		    gcc_unreachable ();
		  }
	    }
	  ଅନ୍ୟଥା ଯଦି (ବୃକ୍ଷ_CODE (ttl) == FUNCTION_TYPE
		   && ବୃକ୍ଷ_CODE (ttr) == FUNCTION_TYPE)
	    {
	      /* Because const and volatile on functions are restrictions
		 that say the function will not do certain things,
		 it is okay to use a const or volatile function
		 where an ordinary one is wanted, but not vice-versa.  */
	      ଯଦି (TYPE_QUALS_NO_ADDR_SPACE (ttl)
		  & ~TYPE_QUALS_NO_ADDR_SPACE (ttr))
		PEDWARN_FOR_QUALIFIERS (location, ପଦସମଷ୍ଟି_loc,
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
      ଅନ୍ୟଥା ଯଦି (!objc_ok)
	{
	  auto_diagnostic_group d;
	  ତାର୍କିକ warned = ମିଥ୍ୟା;
	  pp_markup::element_expected_type e_type (type);
	  pp_markup::element_actual_type e_rhstype (rhstype);
	  ବାଛ (errtype)
	    {
	    ସ୍ଥିତି ic_argpass:
	      {
		range_label_for_type_mismatch rhs_label (rhstype, type);
		gcc_rich_location richloc (ପଦସମଷ୍ଟି_loc, &rhs_label,
					   highlight_colors::actual);
		warned
		  = permerror_opt (&richloc, OPT_Wincompatible_pointer_types,
				   "passing argument %d of %qE from "
				   "incompatible pointer type",
				   parmnum, rname);
		ଯଦି (warned)
		  inform_for_arg (fundecl, ପଦସମଷ୍ଟି_loc, parmnum, type, rhstype);
	      }
	      ଭାଙ୍ଗ;
	    ସ୍ଥିତି ic_assign:
	      ଯଦି (bltin)
		warned
		  = permerror_opt (location, OPT_Wincompatible_pointer_types,
				   "assignment to %e from pointer to "
				   "%qD with incompatible type %e",
				   &e_type, bltin, &e_rhstype);
	      ଅନ୍ୟଥା
		warned
		  = permerror_opt (location, OPT_Wincompatible_pointer_types,
				   "assignment to %e from incompatible "
				   "pointer type %e",
				   &e_type, &e_rhstype);
	      ଭାଙ୍ଗ;
	    ସ୍ଥିତି ic_init:
	    ସ୍ଥିତି ic_init_const:
	      ଯଦି (bltin)
		warned
		  = permerror_init (location, OPT_Wincompatible_pointer_types,
				    "initialization of %e from pointer to "
				    "%qD with incompatible type %e",
				    &e_type, bltin, &e_rhstype);
	      ଅନ୍ୟଥା
		warned
		  = permerror_init (location, OPT_Wincompatible_pointer_types,
				    "initialization of %e from incompatible "
				    "pointer type %e",
				    &e_type, &e_rhstype);
	      ଭାଙ୍ଗ;
	    ସ୍ଥିତି ic_return:
	      ଯଦି (bltin)
		warned
		  = permerror_opt (location, OPT_Wincompatible_pointer_types,
				   "returning pointer to %qD of type %e from "
				   "a function with incompatible type %e",
				   bltin, &e_rhstype, &e_type);
	      ଅନ୍ୟଥା
		warned
		  = permerror_opt (location, OPT_Wincompatible_pointer_types,
				   "returning %e from a function with "
				   "incompatible return type %e",
				   &e_rhstype, &e_type);
	      ଭାଙ୍ଗ;
	    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
	      gcc_unreachable ();
	    }
	  ଯଦି (warned)
	    {
	      /* If the mismatching function type is a pointer to a function,
		 try to show the decl of the function.  */
	      ଯଦି (ବୃକ୍ଷ_CODE (rhs) == ADDR_ପଦସମଷ୍ଟି
		  && ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_OPERAND (rhs, 0)) == FUNCTION_DECL)
		{
		  ବୃକ୍ଷ rhs_fndecl = ବୃକ୍ଷ_OPERAND (rhs, 0);
		  ଯଦି (!DECL_IS_UNDECLARED_BUILTIN (rhs_fndecl))
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

      ଫେରନ୍ତୁ convert (type, rhs);
    }
  ଅନ୍ୟଥା ଯଦି (codel == POINTER_TYPE && coder == ARRAY_TYPE)
    {
      /* ??? This should not be an error when inlining calls to
	 unprototyped functions.  */
      ଅଚଳ ଅକ୍ଷର ସନ୍ଦେଶ[] = "invalid use of non-lvalue array";
      ଯଦି (warnopt)
	warning_at (location, warnopt, ସନ୍ଦେଶ);
      ଅନ୍ୟଥା
	error_at (location, ସନ୍ଦେଶ);
      ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
    }
  ଅନ୍ୟଥା ଯଦି (codel == POINTER_TYPE
	   && (coder == INTEGER_TYPE
	       || coder == ENUMERAL_TYPE
	       || coder == BOOLEAN_TYPE
	       || coder == NULLPTR_TYPE
	       || coder == BITINT_TYPE))
    {
      ଯଦି (null_pointer_constant && c_inhibit_evaluation_warnings == 0
	  && coder != NULLPTR_TYPE)
	warning_at (location, OPT_Wzero_as_null_pointer_constant,
		    "zero as null pointer constant");
      /* A NULLPTR type is just a nullptr always.  */
      ଯଦି (coder == NULLPTR_TYPE)
	ଫେରନ୍ତୁ omit_one_operand_loc (ପଦସମଷ୍ଟି_loc, type, nullptr_ଗଣ୍ଠି, rhs);
      /* An explicit constant 0 or type nullptr_t can convert to a pointer,
	 or one that results from arithmetic, even including a cast to
	 integer type.  */
      ଅନ୍ୟଥା ଯଦି (!null_pointer_constant)
	ବାଛ (errtype)
	  {
	  ସ୍ଥିତି ic_argpass:
	    {
	      auto_diagnostic_group d;
	      range_label_for_type_mismatch rhs_label (rhstype, type);
	      gcc_rich_location richloc (ପଦସମଷ୍ଟି_loc, &rhs_label,
					 highlight_colors::actual);
	      ଯଦି (permerror_opt (&richloc, OPT_Wint_conversion,
				 "passing argument %d of %qE makes pointer "
				 "from integer without a cast", parmnum, rname))
		{
		  maybe_emit_indirection_note (ପଦସମଷ୍ଟି_loc, rhs, type);
		  inform_for_arg (fundecl, ପଦସମଷ୍ଟି_loc, parmnum, type, rhstype);
		}
	    }
	    ଭାଙ୍ଗ;
	  ସ୍ଥିତି ic_assign:
	    permerror_opt (location, OPT_Wint_conversion,
			   "assignment to %qT from %qT makes pointer from "
			   "integer without a cast", type, rhstype);
	    ଭାଙ୍ଗ;
	  ସ୍ଥିତି ic_init:
	  ସ୍ଥିତି ic_init_const:
	    permerror_init (location, OPT_Wint_conversion,
			    "initialization of %qT from %qT makes pointer "
			    "from integer without a cast", type, rhstype);
	    ଭାଙ୍ଗ;
	  ସ୍ଥିତି ic_return:
	    permerror_init (location, OPT_Wint_conversion,
			    "returning %qT from a function with return type "
			    "%qT makes pointer from integer without a cast",
			    rhstype, type);
	    ଭାଙ୍ଗ;
	  ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
	    gcc_unreachable ();
	  }

      ଫେରନ୍ତୁ convert (type, rhs);
    }
  ଅନ୍ୟଥା ଯଦି ((codel == INTEGER_TYPE || codel == BITINT_TYPE)
	   && coder == POINTER_TYPE)
    {
      ବାଛ (errtype)
	{
	ସ୍ଥିତି ic_argpass:
	  {
	    auto_diagnostic_group d;
	    range_label_for_type_mismatch rhs_label (rhstype, type);
	    gcc_rich_location richloc (ପଦସମଷ୍ଟି_loc, &rhs_label,
				       highlight_colors::actual);
	    ଯଦି (permerror_opt (&richloc, OPT_Wint_conversion,
			       "passing argument %d of %qE makes integer from "
			       "pointer without a cast", parmnum, rname))
	      {
		maybe_emit_indirection_note (ପଦସମଷ୍ଟି_loc, rhs, type);
		inform_for_arg (fundecl, ପଦସମଷ୍ଟି_loc, parmnum, type, rhstype);
	      }
	  }
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି ic_assign:
	  permerror_opt (location, OPT_Wint_conversion,
			 "assignment to %qT from %qT makes integer from "
			 "pointer without a cast", type, rhstype);
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି ic_init:
	ସ୍ଥିତି ic_init_const:
	  permerror_init (location, OPT_Wint_conversion,
			  "initialization of %qT from %qT makes integer "
			  "from pointer without a cast", type, rhstype);
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି ic_return:
	  permerror_opt (location, OPT_Wint_conversion, "returning %qT from a "
			 "function with return type %qT makes integer from "
			 "pointer without a cast", rhstype, type);
	  ଭାଙ୍ଗ;
	ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
	  gcc_unreachable ();
	}

      ଫେରନ୍ତୁ convert (type, rhs);
    }
  ଅନ୍ୟଥା ଯଦି (C_BOOLEAN_TYPE_P (type)
	   /* The type nullptr_t may be converted to bool.  The
	      result is false.  */
	   && (coder == POINTER_TYPE || coder == NULLPTR_TYPE))
    {
      ବୃକ୍ଷ ret;
      ତାର୍କିକ save = in_late_ଦ୍ୱିମିକ_op;
      in_late_ଦ୍ୱିମିକ_op = ସତ୍ୟ;
      ret = convert (type, rhs);
      in_late_ଦ୍ୱିମିକ_op = save;
      ଫେରନ୍ତୁ ret;
    }
  ଅନ୍ୟଥା ଯଦି (codel == NULLPTR_TYPE && null_pointer_constant)
    ଫେରନ୍ତୁ convert (type, rhs);

  ବାଛ (errtype)
    {
    ସ୍ଥିତି ic_argpass:
      {
	auto_diagnostic_group d;
	range_label_for_type_mismatch rhs_label (rhstype, type);
	gcc_rich_location richloc (ପଦସମଷ୍ଟି_loc, &rhs_label,
				   highlight_colors::actual);
	ଅଚଳ ଅକ୍ଷର ସନ୍ଦେଶ[] = G_("incompatible type for argument %d of %qE");
	ଯଦି (warnopt)
	  warning_at (ପଦସମଷ୍ଟି_loc, warnopt, ସନ୍ଦେଶ, parmnum, rname);
	ଅନ୍ୟଥା
	  error_at (&richloc, ସନ୍ଦେଶ, parmnum, rname);
	inform_for_arg (fundecl, ପଦସମଷ୍ଟି_loc, parmnum, type, rhstype);
      }
      ଭାଙ୍ଗ;
    ସ୍ଥିତି ic_assign:
      {
	ଅଚଳ ଅକ୍ଷର ସନ୍ଦେଶ[]
	  = G_("incompatible types when assigning to type %qT from type %qT");
	ଯଦି (warnopt)
	  warning_at (ପଦସମଷ୍ଟି_loc, 0, ସନ୍ଦେଶ, type, rhstype);
	ଅନ୍ୟଥା
	  error_at (ପଦସମଷ୍ଟି_loc, ସନ୍ଦେଶ, type, rhstype);
	ଭାଙ୍ଗ;
      }
    ସ୍ଥିତି ic_init:
    ସ୍ଥିତି ic_init_const:
      {
	ଅଚଳ ଅକ୍ଷର ସନ୍ଦେଶ[]
	  = G_("incompatible types when initializing type %qT using type %qT");
	ଯଦି (warnopt)
	  warning_at (location, 0, ସନ୍ଦେଶ, type, rhstype);
	ଅନ୍ୟଥା
	  error_at (location, ସନ୍ଦେଶ, type, rhstype);
	ଭାଙ୍ଗ;
      }
    ସ୍ଥିତି ic_return:
      {
	ଅଚଳ ଅକ୍ଷର ସନ୍ଦେଶ[]
	  = G_("incompatible types when returning type %qT but %qT was expected");
	ଯଦି (warnopt)
	  warning_at (location, 0, ସନ୍ଦେଶ, rhstype, type);
	ଅନ୍ୟଥା
	  error_at (location, ସନ୍ଦେଶ, rhstype, type);
	ଭାଙ୍ଗ;
      }
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
      gcc_unreachable ();
    }

  ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
}

/* If VALUE is a compound expr all of whose expressions are constant, then
   return its value.  Otherwise, return error_mark_node.

   This is for handling COMPOUND_EXPRs as initializer elements
   which is allowed with a warning when -pedantic is specified.  */

ସ୍ଥିର ବୃକ୍ଷ
valid_compound_ପଦସମଷ୍ଟି_initializer (ବୃକ୍ଷ ମୂଲ୍ୟ, ବୃକ୍ଷ endtype)
{
  ଯଦି (ବୃକ୍ଷ_CODE (ମୂଲ୍ୟ) == COMPOUND_ପଦସମଷ୍ଟି)
    {
      ଯଦି (valid_compound_ପଦସମଷ୍ଟି_initializer (ବୃକ୍ଷ_OPERAND (ମୂଲ୍ୟ, 0), endtype)
	  == error_mark_ଗଣ୍ଠି)
	ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
      ଫେରନ୍ତୁ valid_compound_ପଦସମଷ୍ଟି_initializer (ବୃକ୍ଷ_OPERAND (ମୂଲ୍ୟ, 1),
					      endtype);
    }
  ଅନ୍ୟଥା ଯଦି (!initializer_constant_valid_p (ମୂଲ୍ୟ, endtype))
    ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
  ଅନ୍ୟଥା
    ଫେରନ୍ତୁ ମୂଲ୍ୟ;
}

/* Perform appropriate conversions on the initial value of a variable,
   store it in the declaration DECL,
   and print any error messages that are appropriate.
   If ORIGTYPE is not NULL_TREE, it is the original type of INIT.
   If the init is invalid, store an ERROR_MARK.

   INIT_LOC is the location of the initial value.  */

ଶୂନ୍ୟ
store_init_ମୂଲ୍ୟ (location_t init_loc, ବୃକ୍ଷ decl, ବୃକ୍ଷ init, ବୃକ୍ଷ origtype)
{
  ବୃକ୍ଷ ମୂଲ୍ୟ, type;
  ତାର୍କିକ npc = ମିଥ୍ୟା;
  ତାର୍କିକ int_const_ପଦସମଷ୍ଟି = ମିଥ୍ୟା;
  ତାର୍କିକ arith_const_ପଦସମଷ୍ଟି = ମିଥ୍ୟା;

  /* If variable's type was invalidly declared, just ignore it.  */

  type = ବୃକ୍ଷ_TYPE (decl);
  ଯଦି (ବୃକ୍ଷ_CODE (type) == ERROR_MARK)
    ଫେରନ୍ତୁ;

  /* Digest the specified initializer into an expression.  */

  ଯଦି (init)
    {
      npc = null_pointer_constant_p (init);
      int_const_ପଦସମଷ୍ଟି = (ବୃକ୍ଷ_CODE (init) == INTEGER_CST
			&& !ବୃକ୍ଷ_OVERFLOW (init)
			&& INTEGRAL_TYPE_P (ବୃକ୍ଷ_TYPE (init)));
      /* Not fully determined before folding.  */
      arith_const_ପଦସମଷ୍ଟି = ସତ୍ୟ;
    }
  ତାର୍କିକ constexpr_p = (VAR_P (decl)
		      && C_DECL_DECLARED_CONSTEXPR (decl));
  ମୂଲ୍ୟ = digest_init (init_loc, decl, type, init, origtype, npc,
		       int_const_ପଦସମଷ୍ଟି, arith_const_ପଦସମଷ୍ଟି, ସତ୍ୟ,
		       ବୃକ୍ଷ_STATIC (decl) || constexpr_p, constexpr_p);

  /* Store the expression if valid; else report error.  */

  ଯଦି (!in_system_header_at (ନିବେଶ_location)
      && AGGREGATE_TYPE_P (ବୃକ୍ଷ_TYPE (decl)) && !ବୃକ୍ଷ_STATIC (decl))
    warning (OPT_Wtraditional, "traditional C rejects automatic "
	     "aggregate initialization");

  ଯଦି (ମୂଲ୍ୟ != error_mark_ଗଣ୍ଠି || ବୃକ୍ଷ_CODE (decl) != FUNCTION_DECL)
    DECL_INITIAL (decl) = ମୂଲ୍ୟ;

  /* ANSI wants warnings about out-of-range constant initializers.  */
  STRIP_TYPE_NOPS (ମୂଲ୍ୟ);
  ଯଦି (ବୃକ୍ଷ_STATIC (decl))
    constant_expression_warning (ମୂଲ୍ୟ);

  /* Check if we need to set array size from compound literal size.  */
  ଯଦି (ବୃକ୍ଷ_CODE (type) == ARRAY_TYPE
      && TYPE_DOMAIN (type) == NULL_ବୃକ୍ଷ
      && ମୂଲ୍ୟ != error_mark_ଗଣ୍ଠି)
    {
      ବୃକ୍ଷ inside_init = init;

      STRIP_TYPE_NOPS (inside_init);
      inside_init = fold (inside_init);

      ଯଦି (ବୃକ୍ଷ_CODE (inside_init) == COMPOUND_LITERAL_ପଦସମଷ୍ଟି)
	{
	  ବୃକ୍ଷ cldecl = COMPOUND_LITERAL_ପଦସମଷ୍ଟି_DECL (inside_init);

	  ଯଦି (TYPE_DOMAIN (ବୃକ୍ଷ_TYPE (cldecl)))
	    {
	      /* For int foo[] = (int [3]){1}; we need to set array size
		 now since later on array initializer will be just the
		 brace enclosed list of the compound literal.  */
	      ବୃକ୍ଷ etype = strip_array_types (ବୃକ୍ଷ_TYPE (decl));
	      type = build_distinct_type_copy (TYPE_MAIN_VARIANT (type));
	      TYPE_DOMAIN (type) = TYPE_DOMAIN (ବୃକ୍ଷ_TYPE (cldecl));
	      layout_type (type);
	      layout_decl (cldecl, 0);
	      ବୃକ୍ଷ_TYPE (decl)
		= c_build_qualified_type (type, TYPE_QUALS (etype));
	    }
	}
    }
}

/* Methods for storing and printing names for error messages.  */

/* Implement a spelling stack that allows components of a name to be pushed
   and popped.  Each element on the stack is this structure.  */

ସଂରଚନା spelling
{
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା kind;
  ସଂଘ
    {
      unsigned HOST_WIDE_INT i;
      ଅଚଳ ଅକ୍ଷର *s;
    } u;
};

#define SPELLING_STRING 1
#define SPELLING_MEMBER 2
#define SPELLING_BOUNDS 3

ସ୍ଥିର ସଂରଚନା spelling *spelling;	/* Next stack element (unused).  */
ସ୍ଥିର ସଂରଚନା spelling *spelling_base;	/* Spelling stack base.  */
ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା spelling_size;		/* Size of the spelling stack.  */

/* Macros to save and restore the spelling stack around push_... functions.
   Alternative to SAVE_SPELLING_STACK.  */

#define SPELLING_DEPTH() (spelling - spelling_base)
#define RESTORE_SPELLING_DEPTH(DEPTH) (spelling = spelling_base + (DEPTH))

/* Push an element on the spelling stack with type KIND and assign VALUE
   to MEMBER.  */

#define ଠେଲ_SPELLING(KIND, ମୂଲ୍ୟ_2, MEMBER)				\
{									\
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା depth = SPELLING_DEPTH ();					\
									\
  ଯଦି (depth >= spelling_size)						\
    {									\
      spelling_size += 10;						\
      spelling_base = XRESIZEVEC (ସଂରଚନା spelling, spelling_base,	\
				  spelling_size);			\
      RESTORE_SPELLING_DEPTH (depth);					\
    }									\
									\
  spelling->kind = (KIND);						\
  spelling->MEMBER = (ମୂଲ୍ୟ_2);						\
  spelling++;								\
}

/* Push STRING on the stack.  Printed literally.  */

ସ୍ଥିର ଶୂନ୍ୟ
ଠେଲ_string (ଅଚଳ ଅକ୍ଷର *string)
{
  ଠେଲ_SPELLING (SPELLING_STRING, string, u.s);
}

/* Push a member name on the stack.  Printed as '.' STRING.  */

ସ୍ଥିର ଶୂନ୍ୟ
ଠେଲ_member_name (ବୃକ୍ଷ decl)
{
  ଅଚଳ ଅକ୍ଷର *ଅଚଳ string
    = (DECL_NAME (decl)
       ? identifier_to_locale (IDENTIFIER_POINTER (DECL_NAME (decl)))
       : _("<anonymous>"));
  ଠେଲ_SPELLING (SPELLING_MEMBER, string, u.s);
}

/* Push an array bounds on the stack.  Printed as [BOUNDS].  */

ସ୍ଥିର ଶୂନ୍ୟ
ଠେଲ_array_bounds (unsigned HOST_WIDE_INT bounds)
{
  ଠେଲ_SPELLING (SPELLING_BOUNDS, bounds, u.i);
}

/* Compute the maximum size in bytes of the printed spelling.  */

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା
spelling_length (ଶୂନ୍ୟ)
{
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା size = 0;
  ସଂରଚନା spelling *p;

  ପାଇଁ (p = spelling_base; p < spelling; p++)
    {
      ଯଦି (p->kind == SPELLING_BOUNDS)
	size += 25;
      ଅନ୍ୟଥା
	size += strlen (p->u.s) + 1;
    }

  ଫେରନ୍ତୁ size;
}

/* Print the spelling to BUFFER and return it.  */

ସ୍ଥିର ଅକ୍ଷର *
print_spelling (ଅକ୍ଷର *buffer)
{
  ଅକ୍ଷର *d = buffer;
  ସଂରଚନା spelling *p;

  ପାଇଁ (p = spelling_base; p < spelling; p++)
    ଯଦି (p->kind == SPELLING_BOUNDS)
      {
	sprintf (d, "[" HOST_WIDE_INT_PRINT_UNSIGNED "]", p->u.i);
	d += strlen (d);
      }
    ଅନ୍ୟଥା
      {
	ଅଚଳ ଅକ୍ଷର *s;
	ଯଦି (p->kind == SPELLING_MEMBER)
	  *d++ = '.';
	ପାଇଁ (s = p->u.s; (*d = *s++); d++)
	  ;
      }
  *d++ = '\0';
  ଫେରନ୍ତୁ buffer;
}

/* Check whether INIT, a floating or integer constant, is
   representable in TYPE, a real floating type with the same radix or
   a decimal floating type initialized with a binary floating
   constant.  Return true if OK, false if not.  */
ସ୍ଥିର ତାର୍କିକ
constexpr_init_fits_real_type (ବୃକ୍ଷ type, ବୃକ୍ଷ init)
{
  gcc_assert (SCALAR_FLOAT_TYPE_P (type));
  gcc_assert (ବୃକ୍ଷ_CODE (init) == INTEGER_CST || ବୃକ୍ଷ_CODE (init) == REAL_CST);
  ଯଦି (ବୃକ୍ଷ_CODE (init) == REAL_CST
      && TYPE_MODE (ବୃକ୍ଷ_TYPE (init)) == TYPE_MODE (type))
    {
      /* Same mode, no conversion required except for the case of
	 signaling NaNs if the types are incompatible (e.g. double and
	 long double with the same mode).  */
      ଯଦି (REAL_ମୂଲ୍ୟ_ISSIGNALING_NAN (ବୃକ୍ଷ_REAL_CST (init))
	  && !comptypes (TYPE_MAIN_VARIANT (type),
			 TYPE_MAIN_VARIANT (ବୃକ୍ଷ_TYPE (init))))
	ଫେରନ୍ତୁ ମିଥ୍ୟା;
      ଫେରନ୍ତୁ ସତ୍ୟ;
    }
  ଯଦି (ବୃକ୍ଷ_CODE (init) == INTEGER_CST)
    {
      ବୃକ୍ଷ converted = build_real_from_int_cst (type, init);
      ତାର୍କିକ fail = ମିଥ୍ୟା;
      wide_int w = real_to_integer (&ବୃକ୍ଷ_REAL_CST (converted), &fail,
				    TYPE_PRECISION (ବୃକ୍ଷ_TYPE (init)));
      ଫେରନ୍ତୁ !fail && wi::eq_p (w, wi::to_wide (init));
    }
  ଯଦି (REAL_ମୂଲ୍ୟ_ISSIGNALING_NAN (ବୃକ୍ଷ_REAL_CST (init)))
    ଫେରନ୍ତୁ ମିଥ୍ୟା;
  ଯଦି ((REAL_ମୂଲ୍ୟ_ISINF (ବୃକ୍ଷ_REAL_CST (init))
       && MODE_HAS_INFINITIES (TYPE_MODE (type)))
      || (REAL_ମୂଲ୍ୟ_ISNAN (ବୃକ୍ଷ_REAL_CST (init))
	  && MODE_HAS_NANS (TYPE_MODE (type))))
    ଫେରନ୍ତୁ ସତ୍ୟ;
  ଯଦି (DECIMAL_FLOAT_TYPE_P (type)
      && !DECIMAL_FLOAT_TYPE_P (ବୃକ୍ଷ_TYPE (init)))
    {
      /* This is valid if the real number represented by the
	 initializer can be exactly represented in the decimal
	 type.  Compare the values using MPFR.  */
      REAL_ମୂଲ୍ୟ_TYPE t;
      real_convert (&t, TYPE_MODE (type), &ବୃକ୍ଷ_REAL_CST (init));
      mpfr_t bin_val, dec_val;
      mpfr_init2 (bin_val, REAL_MODE_FORMAT (TYPE_MODE (ବୃକ୍ଷ_TYPE (init)))->p);
      mpfr_init2 (dec_val, REAL_MODE_FORMAT (TYPE_MODE (ବୃକ୍ଷ_TYPE (init)))->p);
      mpfr_from_real (bin_val, &ବୃକ୍ଷ_REAL_CST (init), MPFR_RNDN);
      ଅକ୍ଷର string[256];
      real_to_decimal (string, &t, ଆକାର string, 0, 1);
      ତାର୍କିକ res = (mpfr_strtofr (dec_val, string, ଖାଲି, 10, MPFR_RNDN) == 0
		  && mpfr_equal_p (bin_val, dec_val));
      mpfr_clear (bin_val);
      mpfr_clear (dec_val);
      ଫେରନ୍ତୁ res;
    }
  /* exact_real_truncate is not quite right here, since it doesn't
     allow even an exact conversion to subnormal values.  */
  REAL_ମୂଲ୍ୟ_TYPE t;
  real_convert (&t, TYPE_MODE (type), &ବୃକ୍ଷ_REAL_CST (init));
  ଫେରନ୍ତୁ real_identical (&t, &ବୃକ୍ଷ_REAL_CST (init));
}

/* Check whether INIT (location LOC) is valid as a 'constexpr'
   initializer for type TYPE, and give an error if not.  INIT has
   already been folded and verified to be constant.  INT_CONST_EXPR
   and ARITH_CONST_EXPR say whether it is an integer constant
   expression or arithmetic constant expression, respectively.  If
   TYPE is not a scalar type, this function does nothing.  */

ସ୍ଥିର ଶୂନ୍ୟ
check_constexpr_init (location_t loc, ବୃକ୍ଷ type, ବୃକ୍ଷ init,
		      ତାର୍କିକ int_const_ପଦସମଷ୍ଟି, ତାର୍କିକ arith_const_ପଦସମଷ୍ଟି)
{
  ଯଦି (POINTER_TYPE_P (type))
    {
      /* The initializer must be null.  */
      ଯଦି (ବୃକ୍ଷ_CODE (init) != INTEGER_CST || !integer_zerop (init))
	error_at (loc, "%<constexpr%> pointer initializer is not null");
      ଫେରନ୍ତୁ;
    }
  ଯଦି (INTEGRAL_TYPE_P (type))
    {
      /* The initializer must be an integer constant expression,
	 representable in the target type.  */
      ଯଦି (!int_const_ପଦସମଷ୍ଟି)
	{
	  ଯଦି (ବୃକ୍ଷ_CODE (init) == RAW_DATA_CST
	      && TYPE_PRECISION (type) == CHAR_BIT)
	    {
	      ଯଦି (!TYPE_UNSIGNED (type))
		ପାଇଁ (unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0;
		     i < (unsigned) RAW_DATA_LENGTH (init); ++i)
		  ଯଦି (RAW_DATA_SCHAR_ELT (init, i) < 0)
		    {
		      error_at (loc, "%<constexpr%> initializer not "
				"representable in type of object");
		      ଭାଙ୍ଗ;
		    }
	    }
	  ଅନ୍ୟଥା
	    error_at (loc, "%<constexpr%> integer initializer is not an "
		      "integer constant expression");
	}
      ଅନ୍ୟଥା ଯଦି (!int_fits_type_p (init, type))
	error_at (loc, "%<constexpr%> initializer not representable in "
		  "type of object");
      ଫେରନ୍ତୁ;
    }
  /* We don't apply any extra checks to extension types such as vector
     or fixed-point types.  */
  ଯଦି (ବୃକ୍ଷ_CODE (type) != REAL_TYPE && ବୃକ୍ଷ_CODE (type) != COMPLEX_TYPE)
    ଫେରନ୍ତୁ;
  ଯଦି (!arith_const_ପଦସମଷ୍ଟି)
    {
      error_at (loc, "%<constexpr%> initializer is not an arithmetic "
		"constant expression");
      ଫେରନ୍ତୁ;
    }
  /* We don't apply any extra checks to complex integers.  */
  ଯଦି (ବୃକ୍ଷ_CODE (type) == COMPLEX_TYPE
      && ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (type)) != REAL_TYPE)
    ଫେରନ୍ତୁ;
  /* Following N3082, a real type cannot be initialized from a complex
     type and a binary type cannot be initialized from a decimal type
     (but initializing a decimal type from a binary type is OK).
     Signaling NaN initializers are OK only if the types are
     compatible (not just the same mode); all quiet NaN and infinity
     initializations are considered to preserve the value.  */
  ଯଦି (ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (init)) == COMPLEX_TYPE
      && SCALAR_FLOAT_TYPE_P (type))
    {
      error_at (loc, "%<constexpr%> initializer for a real type is of "
		"complex type");
      ଫେରନ୍ତୁ;
    }
  ଯଦି (SCALAR_FLOAT_TYPE_P (type)
      && SCALAR_FLOAT_TYPE_P (ବୃକ୍ଷ_TYPE (init))
      && DECIMAL_FLOAT_TYPE_P (ବୃକ୍ଷ_TYPE (init))
      && !DECIMAL_FLOAT_TYPE_P (type))
    {
      error_at (loc, "%<constexpr%> initializer for a binary "
		"floating-point type is of decimal type");
      ଫେରନ୍ତୁ;
    }
  ତାର୍କିକ fits;
  ଯଦି (ବୃକ୍ଷ_CODE (type) == COMPLEX_TYPE)
    {
      ବାଛ (ବୃକ୍ଷ_CODE (init))
	{
	ସ୍ଥିତି INTEGER_CST:
	ସ୍ଥିତି REAL_CST:
	  fits = constexpr_init_fits_real_type (ବୃକ୍ଷ_TYPE (type), init);
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି COMPLEX_CST:
	  fits = (constexpr_init_fits_real_type (ବୃକ୍ଷ_TYPE (type),
						 ବୃକ୍ଷ_REALPART (init))
		  && constexpr_init_fits_real_type (ବୃକ୍ଷ_TYPE (type),
						    ବୃକ୍ଷ_IMAGPART (init)));
	  ଭାଙ୍ଗ;
	ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
	  gcc_unreachable ();
	}
    }
  ଅନ୍ୟଥା
    fits = constexpr_init_fits_real_type (type, init);
  ଯଦି (!fits)
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

ସ୍ଥିର ବୃକ୍ଷ
digest_init (location_t init_loc, ବୃକ୍ଷ decl, ବୃକ୍ଷ type, ବୃକ୍ଷ init,
	     ବୃକ୍ଷ origtype, ତାର୍କିକ null_pointer_constant, ତାର୍କିକ int_const_ପଦସମଷ୍ଟି,
	     ତାର୍କିକ arith_const_ପଦସମଷ୍ଟି, ତାର୍କିକ strict_string,
	     ତାର୍କିକ require_constant, ତାର୍କିକ require_constexpr)
{
  ଗଣନା ବୃକ୍ଷ_code code = ବୃକ୍ଷ_CODE (type);
  ବୃକ୍ଷ inside_init = init;
  ବୃକ୍ଷ semantic_type = NULL_ବୃକ୍ଷ;
  ତାର୍କିକ maybe_const = ସତ୍ୟ;

  ଯଦି (type == error_mark_ଗଣ୍ଠି
      || !init
      || error_operand_p (init))
    ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;

  STRIP_TYPE_NOPS (inside_init);

  /* If require_constant is TRUE,  when the initializer is a call to
     .ACCESS_WITH_SIZE, use the first argument as the initializer.
     For example:
     y = (char *) .ACCESS_WITH_SIZE ((char *) &static_annotated.c,...)
     will be converted to
     y = &static_annotated.c.  */

  ଯଦି (require_constant
      && ବୃକ୍ଷ_CODE (inside_init) == NOP_ପଦସମଷ୍ଟି
      && ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_OPERAND (inside_init, 0)) == CALL_ପଦସମଷ୍ଟି
      && is_access_with_size_p (ବୃକ୍ଷ_OPERAND (inside_init, 0)))
    inside_init
      = get_ref_from_access_with_size (ବୃକ୍ଷ_OPERAND (inside_init, 0));

  ଯଦି (!c_in_omp_for)
    {
      ଯଦି (ବୃକ୍ଷ_CODE (inside_init) == EXCESS_PRECISION_ପଦସମଷ୍ଟି)
	{
	  semantic_type = ବୃକ୍ଷ_TYPE (inside_init);
	  inside_init = ବୃକ୍ଷ_OPERAND (inside_init, 0);
	}
      inside_init = c_fully_fold (inside_init, require_constant, &maybe_const);
    }
  /* TODO: this may not detect all cases of expressions folding to
     constants that are not arithmetic constant expressions.  */
  ଯଦି (!maybe_const)
    arith_const_ପଦସମଷ୍ଟି = ମିଥ୍ୟା;
  ଅନ୍ୟଥା ଯଦି (!INTEGRAL_TYPE_P (ବୃକ୍ଷ_TYPE (inside_init))
	   && ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (inside_init)) != REAL_TYPE
	   && ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (inside_init)) != COMPLEX_TYPE)
    arith_const_ପଦସମଷ୍ଟି = ମିଥ୍ୟା;
  ଅନ୍ୟଥା ଯଦି (ବୃକ୍ଷ_CODE (inside_init) != INTEGER_CST
	   && ବୃକ୍ଷ_CODE (inside_init) != REAL_CST
	   && ବୃକ୍ଷ_CODE (inside_init) != COMPLEX_CST
	   && ବୃକ୍ଷ_CODE (inside_init) != RAW_DATA_CST)
    arith_const_ପଦସମଷ୍ଟି = ମିଥ୍ୟା;
  ଅନ୍ୟଥା ଯଦି (ବୃକ୍ଷ_OVERFLOW (inside_init))
    arith_const_ପଦସମଷ୍ଟି = ମିଥ୍ୟା;

  /* Initialization of an array of chars from a string constant
     optionally enclosed in braces.  */

  ଯଦି (code == ARRAY_TYPE && inside_init
      && ବୃକ୍ଷ_CODE (inside_init) == STRING_CST)
    {
      ବୃକ୍ଷ typ1
	= (TYPE_ATOMIC (ବୃକ୍ଷ_TYPE (type))
	   ? c_build_qualified_type (TYPE_MAIN_VARIANT (ବୃକ୍ଷ_TYPE (type)),
				     TYPE_QUAL_ATOMIC)
	   : TYPE_MAIN_VARIANT (ବୃକ୍ଷ_TYPE (type)));
      /* Note that an array could be both an array of character type
	 and an array of wchar_t if wchar_t is signed char or unsigned
	 char.  */
      ତାର୍କିକ char_array = (typ1 == char_type_ଗଣ୍ଠି
			 || typ1 == signed_char_type_ଗଣ୍ଠି
			 || typ1 == unsigned_char_type_ଗଣ୍ଠି);
      ତାର୍କିକ wchar_array = comptypes (typ1, wchar_type_ଗଣ୍ଠି);
      ତାର୍କିକ char16_array = comptypes (typ1, char16_type_ଗଣ୍ଠି);
      ତାର୍କିକ char32_array = comptypes (typ1, char32_type_ଗଣ୍ଠି);

      ଯଦି (char_array || wchar_array || char16_array || char32_array)
	{
	  ସଂରଚନା c_ପଦସମଷ୍ଟି ପଦସମଷ୍ଟି;
	  ବୃକ୍ଷ typ2 = TYPE_MAIN_VARIANT (ବୃକ୍ଷ_TYPE (ବୃକ୍ଷ_TYPE (inside_init)));
	  ତାର୍କିକ incompat_string_cst = ମିଥ୍ୟା;
	  ପଦସମଷ୍ଟି.ମୂଲ୍ୟ = inside_init;
	  ପଦସମଷ୍ଟି.original_code = (strict_string ? STRING_CST : ERROR_MARK);
	  ପଦସମଷ୍ଟି.original_type = ଖାଲି;
	  ପଦସମଷ୍ଟି.m_decimal = 0;
	  maybe_warn_string_init (init_loc, type, ପଦସମଷ୍ଟି);

	  ଯଦି (flexible_array_member_type_p (type))
	    pedwarn_init (init_loc, OPT_Wpedantic,
			  "initialization of a flexible array member");

	  ଯଦି (comptypes (TYPE_MAIN_VARIANT (ବୃକ୍ଷ_TYPE (inside_init)),
			 TYPE_MAIN_VARIANT (type)))
	    ଫେରନ୍ତୁ inside_init;

	  ଯଦି (char_array)
	    {
	      ଯଦି (typ2 != char_type_ଗଣ୍ଠି && typ2 != char8_type_ଗଣ୍ଠି)
		incompat_string_cst = ସତ୍ୟ;
	    }
	  ଅନ୍ୟଥା ଯଦି (!comptypes (typ1, typ2))
	    incompat_string_cst = ସତ୍ୟ;

          ଯଦି (incompat_string_cst)
            {
	      error_init (init_loc, "cannot initialize array of %qT from "
			  "a string literal with type array of %qT",
			  typ1, typ2);
	      ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
            }

	  ଯଦି (require_constexpr
	      && TYPE_UNSIGNED (typ1) != TYPE_UNSIGNED (typ2))
	    {
	      /* Check if all characters of the string can be
		 represented in the type of the constexpr object being
		 initialized.  */
	      unsigned HOST_WIDE_INT len = ବୃକ୍ଷ_STRING_LENGTH (inside_init);
	      ଅଚଳ unsigned ଅକ୍ଷର *p =
		(ଅଚଳ unsigned ଅକ୍ଷର *) ବୃକ୍ଷ_STRING_POINTER (inside_init);
	      gcc_assert (CHAR_TYPE_SIZE == 8 && CHAR_BIT == 8);
	      ପାଇଁ (unsigned i = 0; i < len; i++)
		ଯଦି (p[i] > 127)
		  {
		    error_init (init_loc, "%<constexpr%> initializer not "
				"representable in type of object");
		    ଭାଙ୍ଗ;
		  }
	    }

	  ଯଦି (TYPE_DOMAIN (type) != NULL_ବୃକ୍ଷ
	      && TYPE_SIZE (type) != NULL_ବୃକ୍ଷ
	      && ବୃକ୍ଷ_CODE (TYPE_SIZE (type)) == INTEGER_CST)
	    {
	      unsigned HOST_WIDE_INT len = ବୃକ୍ଷ_STRING_LENGTH (inside_init);

	      ଯଦି (compare_ବୃକ୍ଷ_int (TYPE_SIZE_UNIT (type), len) < 0)
		{
		  unsigned HOST_WIDE_INT avail
		    = ବୃକ୍ଷ_to_uhwi (TYPE_SIZE_UNIT (type));
		  unsigned unit = TYPE_PRECISION (typ1) / BITS_PER_UNIT;
		  ଅଚଳ ଅକ୍ଷର *p = ବୃକ୍ଷ_STRING_POINTER (inside_init);

		  /* Construct truncated string.  */
		  inside_init = build_string (avail, p);

		  /* Subtract the size of a single (possibly wide) character
		     because it may be ok to ignore the terminating NUL char
		     that is counted in the length of the constant.  */
		  ଯଦି (len - unit > avail)
		    pedwarn_init (init_loc, 0,
				  "initializer-string for array of %qT "
				  "is too long (%wu chars into %wu "
				  "available)", typ1, len, avail);
		  ଅନ୍ୟଥା ଯଦି (warn_cxx_compat)
		    warning_at (init_loc, OPT_Wc___compat,
				"initializer-string for array of %qT "
				"is too long for C++ (%wu chars into %wu "
				"available)", typ1, len, avail);
		  ଅନ୍ୟଥା ଯଦି (warn_unterminated_string_initialization
			   && get_attr_nonstring_decl (decl) == NULL_ବୃକ୍ଷ)
		    warning_at (init_loc,
				OPT_Wunterminated_string_initialization,
				"initializer-string for array of %qT "
				"truncates NUL terminator but destination "
				"lacks %qs attribute (%wu chars into %wu "
				"available)", typ1, "nonstring", len, avail);
		}
	    }

	  ବୃକ୍ଷ_TYPE (inside_init) = type;
	  ଫେରନ୍ତୁ inside_init;
	}
      ଅନ୍ୟଥା ଯଦି (INTEGRAL_TYPE_P (typ1))
	{
	  error_init (init_loc, "array of inappropriate type initialized "
		      "from string constant");
	  ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
	}
    }

  /* Build a VECTOR_CST from a *constant* vector constructor.  If the
     vector constructor is not constant (e.g. {1,2,3,foo()}) then punt
     below and handle as a constructor.  */
  ଯଦି (code == VECTOR_TYPE
      && VECTOR_TYPE_P (ବୃକ୍ଷ_TYPE (inside_init))
      && vector_types_convertible_p (ବୃକ୍ଷ_TYPE (inside_init), type, ସତ୍ୟ)
      && ବୃକ୍ଷ_CONSTANT (inside_init))
    {
      ଯଦି (ବୃକ୍ଷ_CODE (inside_init) == VECTOR_CST
	  && comptypes (TYPE_MAIN_VARIANT (ବୃକ୍ଷ_TYPE (inside_init)),
			TYPE_MAIN_VARIANT (type)))
	ଫେରନ୍ତୁ inside_init;

      ଯଦି (ବୃକ୍ଷ_CODE (inside_init) == CONSTRUCTOR)
	{
	  unsigned HOST_WIDE_INT ix;
	  ବୃକ୍ଷ ମୂଲ୍ୟ;
	  ତାର୍କିକ constant_p = ସତ୍ୟ;

	  /* Iterate through elements and check if all constructor
	     elements are *_CSTs.  */
	  FOR_EACH_CONSTRUCTOR_ମୂଲ୍ୟ (CONSTRUCTOR_ELTS (inside_init), ix, ମୂଲ୍ୟ)
	    ଯଦି (!CONSTANT_CLASS_P (ମୂଲ୍ୟ))
	      {
		constant_p = ମିଥ୍ୟା;
		ଭାଙ୍ଗ;
	      }

	  ଯଦି (constant_p)
	    ଫେରନ୍ତୁ build_vector_from_ctor (type,
					   CONSTRUCTOR_ELTS (inside_init));
	}
    }

  ଯଦି (warn_sequence_point)
    verify_sequence_points (inside_init);

  /* Any type can be initialized
     from an expression of the same type, optionally with braces.  */

  ଯଦି (inside_init && ବୃକ୍ଷ_TYPE (inside_init) != NULL_ବୃକ୍ଷ
      && (comptypes (TYPE_MAIN_VARIANT (ବୃକ୍ଷ_TYPE (inside_init)),
		     TYPE_MAIN_VARIANT (type))
	  || (code == ARRAY_TYPE
	      && comptypes (ବୃକ୍ଷ_TYPE (inside_init), type))
	  || (gnu_vector_type_p (type)
	      && comptypes (ବୃକ୍ଷ_TYPE (inside_init), type))
	  || (code == POINTER_TYPE
	      && ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (inside_init)) == ARRAY_TYPE
	      && comptypes (ବୃକ୍ଷ_TYPE (ବୃକ୍ଷ_TYPE (inside_init)),
			    ବୃକ୍ଷ_TYPE (type)))))
    {
      ଯଦି (code == POINTER_TYPE)
	{
	  ଯଦି (ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (inside_init)) == ARRAY_TYPE)
	    {
	      ଯଦି (ବୃକ୍ଷ_CODE (inside_init) == STRING_CST
		  || ବୃକ୍ଷ_CODE (inside_init) == COMPOUND_LITERAL_ପଦସମଷ୍ଟି)
		inside_init = array_to_pointer_conversion
		  (init_loc, inside_init);
	      ଅନ୍ୟଥା
		{
		  error_init (init_loc, "invalid use of non-lvalue array");
		  ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
		}
	    }
	}

      ଯଦି (code == VECTOR_TYPE || c_hardbool_type_attr (type))
	/* Although the types are compatible, we may require a
	   conversion.  */
	inside_init = convert (type, inside_init);

      ଯଦି ((code == RECORD_TYPE || code == UNION_TYPE)
	  && !comptypes (TYPE_MAIN_VARIANT (type), TYPE_MAIN_VARIANT (ବୃକ୍ଷ_TYPE (inside_init))))
	{
	  error_init (init_loc, "invalid initializer");
	  ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
	}

      ଯଦି (require_constant
	  && ବୃକ୍ଷ_CODE (inside_init) == COMPOUND_LITERAL_ପଦସମଷ୍ଟି)
	{
	  /* As an extension, allow initializing objects with static storage
	     duration with compound literals (which are then treated just as
	     the brace enclosed list they contain).  Also allow this for
	     vectors, as we can only assign them with compound literals.  */
	  ଯଦି (flag_isoc99 && code != VECTOR_TYPE)
	    pedwarn_init (init_loc, OPT_Wpedantic, "initializer element "
			  "is not constant");
	  ବୃକ୍ଷ decl = COMPOUND_LITERAL_ପଦସମଷ୍ଟି_DECL (inside_init);
	  inside_init = DECL_INITIAL (decl);
	}

      ଯଦି (code == ARRAY_TYPE && ବୃକ୍ଷ_CODE (inside_init) != STRING_CST
	  && ବୃକ୍ଷ_CODE (inside_init) != CONSTRUCTOR)
	{
	  error_init (init_loc, "array initialized from non-constant array "
		      "expression");
	  ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
	}

      /* Compound expressions can only occur here if -Wpedantic or
	 -pedantic-errors is specified.  In the later case, we always want
	 an error.  In the former case, we simply want a warning.  */
      ଯଦି (require_constant && pedantic
	  && ବୃକ୍ଷ_CODE (inside_init) == COMPOUND_ପଦସମଷ୍ଟି)
	{
	  inside_init
	    = valid_compound_ପଦସମଷ୍ଟି_initializer (inside_init,
					       ବୃକ୍ଷ_TYPE (inside_init));
	  ଯଦି (inside_init == error_mark_ଗଣ୍ଠି)
	    error_init (init_loc, "initializer element is not constant");
	  ଅନ୍ୟଥା
	    pedwarn_init (init_loc, OPT_Wpedantic,
			  "initializer element is not constant");
	  ଯଦି (flag_pedantic_errors)
	    inside_init = error_mark_ଗଣ୍ଠି;
	}
      ଅନ୍ୟଥା ଯଦି (require_constant
	       && !initializer_constant_valid_p (inside_init,
						 ବୃକ୍ଷ_TYPE (inside_init)))
	{
	  error_init (init_loc, "initializer element is not constant");
	  inside_init = error_mark_ଗଣ୍ଠି;
	}
      ଅନ୍ୟଥା ଯଦି (require_constant && !maybe_const)
	pedwarn_init (init_loc, OPT_Wpedantic,
		      "initializer element is not a constant expression");
      ଅନ୍ୟଥା ଯଦି (require_constexpr)
	check_constexpr_init (init_loc, type, inside_init,
			      int_const_ପଦସମଷ୍ଟି, arith_const_ପଦସମଷ୍ଟି);

      /* Added to enable additional -Wsuggest-attribute=format warnings.  */
      ଯଦି (ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (inside_init)) == POINTER_TYPE)
	inside_init = convert_for_assignment (init_loc, UNKNOWN_LOCATION,
					      type, inside_init, origtype,
					      (require_constant
					       ? ic_init_const
					       : ic_init), null_pointer_constant,
					      NULL_ବୃକ୍ଷ, NULL_ବୃକ୍ଷ, 0);
      ଯଦି (ବୃକ୍ଷ_CODE (inside_init) == RAW_DATA_CST
	  && c_inhibit_evaluation_warnings == 0
	  && warn_conversion
	  && !TYPE_UNSIGNED (type)
	  && TYPE_PRECISION (type) == CHAR_BIT)
	ପାଇଁ (unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0;
	     i < (unsigned) RAW_DATA_LENGTH (inside_init); ++i)
	  ଯଦି (RAW_DATA_SCHAR_ELT (inside_init, i) < 0)
	    warning_at (init_loc, OPT_Wconversion,
			"conversion from %qT to %qT changes value from "
			"%qd to %qd",
			integer_type_ଗଣ୍ଠି, type,
			RAW_DATA_UCHAR_ELT (inside_init, i),
			RAW_DATA_SCHAR_ELT (inside_init, i));
      ଫେରନ୍ତୁ inside_init;
    }

  /* Handle scalar types, including conversions.  */

  ଯଦି (code == INTEGER_TYPE || code == REAL_TYPE || code == FIXED_POINT_TYPE
      || code == POINTER_TYPE || code == ENUMERAL_TYPE || code == BOOLEAN_TYPE
      || code == COMPLEX_TYPE || code == VECTOR_TYPE || code == NULLPTR_TYPE
      || code == BITINT_TYPE)
    {
      ବୃକ୍ଷ unconverted_init = inside_init;
      ଯଦି (ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (init)) == ARRAY_TYPE
	  && (ବୃକ୍ଷ_CODE (init) == STRING_CST
	      || ବୃକ୍ଷ_CODE (init) == COMPOUND_LITERAL_ପଦସମଷ୍ଟି))
	inside_init = init = array_to_pointer_conversion (init_loc, init);
      ଯଦି (semantic_type)
	inside_init = build1 (EXCESS_PRECISION_ପଦସମଷ୍ଟି, semantic_type,
			      inside_init);
      inside_init
	= convert_for_assignment (init_loc, UNKNOWN_LOCATION, type,
				  inside_init, origtype,
				  require_constant ? ic_init_const : ic_init,
				  null_pointer_constant, NULL_ବୃକ୍ଷ, NULL_ବୃକ୍ଷ,
				  0);

      /* Check to see if we have already given an error message.  */
      ଯଦି (inside_init == error_mark_ଗଣ୍ଠି)
	;
      ଅନ୍ୟଥା ଯଦି (require_constant && !ବୃକ୍ଷ_CONSTANT (inside_init))
	{
	  error_init (init_loc, "initializer element is not constant");
	  inside_init = error_mark_ଗଣ୍ଠି;
	}
      ଅନ୍ୟଥା ଯଦି (require_constant
	       && !initializer_constant_valid_p (inside_init,
						 ବୃକ୍ଷ_TYPE (inside_init)))
	{
	  error_init (init_loc, "initializer element is not computable at "
		      "load time");
	  inside_init = error_mark_ଗଣ୍ଠି;
	}
      ଅନ୍ୟଥା ଯଦି (require_constant && !maybe_const)
	pedwarn_init (init_loc, OPT_Wpedantic,
		      "initializer element is not a constant expression");
      ଅନ୍ୟଥା ଯଦି (require_constexpr)
	check_constexpr_init (init_loc, type, unconverted_init,
			      int_const_ପଦସମଷ୍ଟି, arith_const_ପଦସମଷ୍ଟି);

      ଫେରନ୍ତୁ inside_init;
    }

  /* Come here only for records and arrays.  */

  ଯଦି (COMPLETE_TYPE_P (type) && ବୃକ୍ଷ_CODE (TYPE_SIZE (type)) != INTEGER_CST)
    {
      error_init (init_loc,
		  "variable-sized object may not be initialized except "
		  "with an empty initializer");
      ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
    }

  error_init (init_loc, "invalid initializer");
  ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
}

/* Handle initializers that use braces.  */

/* Type of object we are accumulating a constructor for.
   This type is always a RECORD_TYPE, UNION_TYPE or ARRAY_TYPE.  */
ସ୍ଥିର ବୃକ୍ଷ constructor_type;

/* For a RECORD_TYPE or UNION_TYPE, this is the chain of fields
   left to fill.  */
ସ୍ଥିର ବୃକ୍ଷ constructor_fields;

/* For an ARRAY_TYPE, this is the specified index
   at which to store the next element we get.  */
ସ୍ଥିର ବୃକ୍ଷ constructor_index;

/* For an ARRAY_TYPE, this is the maximum index.  */
ସ୍ଥିର ବୃକ୍ଷ constructor_max_index;

/* For a RECORD_TYPE, this is the first field not yet written out.  */
ସ୍ଥିର ବୃକ୍ଷ constructor_unfilled_fields;

/* For an ARRAY_TYPE, this is the index of the first element
   not yet written out.  */
ସ୍ଥିର ବୃକ୍ଷ constructor_unfilled_index;

/* In a RECORD_TYPE, the byte index of the next consecutive field.
   This is so we can generate gaps between fields, when appropriate.  */
ସ୍ଥିର ବୃକ୍ଷ constructor_bit_index;

/* If we are saving up the elements rather than allocating them,
   this is the list of elements so far (in reverse order,
   most recent first).  */
ସ୍ଥିର vec<constructor_elt, va_gc> *constructor_elements;

/* 1 if constructor should be incrementally stored into a constructor chain,
   0 if all the elements should be kept in AVL tree.  */
ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା constructor_incremental;

/* 1 if so far this constructor's elements are all compile-time constants.  */
ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା constructor_constant;

/* 1 if so far this constructor's elements are all valid address constants.  */
ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା constructor_simple;

/* 1 if this constructor has an element that cannot be part of a
   constant expression.  */
ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା constructor_nonconst;

/* 1 if this constructor is erroneous so far.  */
ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା constructor_erroneous;

/* 1 if this constructor is the universal zero initializer { 0 }.  */
ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା constructor_zeroinit;

/* 1 if this constructor should have padding bits zeroed (C23 {}.  */
ସ୍ଥିର ତାର୍କିକ constructor_zero_padding_bits;

/* 1 if this constructor is a braced scalar initializer (further nested levels
   of braces are an error).  */
ସ୍ଥିର ତାର୍କିକ constructor_braced_scalar;

/* Structure for managing pending initializer elements, organized as an
   AVL tree.  */

ସଂରଚନା init_ଗଣ୍ଠି
{
  ସଂରଚନା init_ଗଣ୍ଠି *ବାମ, *ଡାହାଣ;
  ସଂରଚନା init_ଗଣ୍ଠି *parent;
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା balance;
  ବୃକ୍ଷ purpose;
  ବୃକ୍ଷ ମୂଲ୍ୟ;
  ବୃକ୍ଷ origtype;
};

/* Tree of pending elements at this constructor level.
   These are elements encountered out of order
   which belong at places we haven't reached yet in actually
   writing the output.
   Will never hold tree nodes across GC runs.  */
ସ୍ଥିର ସଂରଚନା init_ଗଣ୍ଠି *constructor_pending_elts;

/* The SPELLING_DEPTH of this constructor.  */
ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା constructor_depth;

/* DECL node for which an initializer is being read.
   0 means we are reading a constructor expression
   such as (struct foo) {...}.  */
ସ୍ଥିର ବୃକ୍ଷ constructor_decl;

/* Nonzero if there were any member designators in this initializer.  */
ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା constructor_designated;

/* Nesting depth of designator list.  */
ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା designator_depth;

/* Nonzero if there were diagnosed errors in this designator list.  */
ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା designator_erroneous;


/* This stack has a level for each implicit or explicit level of
   structuring in the initializer, including the outermost one.  It
   saves the values of most of the variables above.  */

ସଂରଚନା constructor_range_ଗଦା;

ସଂରଚନା constructor_ଗଦା
{
  ସଂରଚନା constructor_ଗଦା *next;
  ବୃକ୍ଷ type;
  ବୃକ୍ଷ fields;
  ବୃକ୍ଷ index;
  ବୃକ୍ଷ max_index;
  ବୃକ୍ଷ unfilled_index;
  ବୃକ୍ଷ unfilled_fields;
  ବୃକ୍ଷ bit_index;
  vec<constructor_elt, va_gc> *elements;
  ସଂରଚନା init_ଗଣ୍ଠି *pending_elts;
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା offset;
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା depth;
  /* If value nonzero, this value should replace the entire
     constructor at this level.  */
  ସଂରଚନା c_ପଦସମଷ୍ଟି replacement_ମୂଲ୍ୟ;
  ସଂରଚନା constructor_range_ଗଦା *range_ଗଦା;
  ଅକ୍ଷର constant;
  ଅକ୍ଷର simple;
  ଅକ୍ଷର nonconst;
  ଅକ୍ଷର implicit;
  ଅକ୍ଷର erroneous;
  ଅକ୍ଷର outer;
  ଅକ୍ଷର incremental;
  ଅକ୍ଷର designated;
  ତାର୍କିକ zero_padding_bits;
  ତାର୍କିକ braced_scalar;
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା designator_depth;
};

ସ୍ଥିର ସଂରଚନା constructor_ଗଦା *constructor_ଗଦା;

/* This stack represents designators from some range designator up to
   the last designator in the list.  */

ସଂରଚନା constructor_range_ଗଦା
{
  ସଂରଚନା constructor_range_ଗଦା *next, *prev;
  ସଂରଚନା constructor_ଗଦା *ଗଦା;
  ବୃକ୍ଷ range_start;
  ବୃକ୍ଷ index;
  ବୃକ୍ଷ range_end;
  ବୃକ୍ଷ fields;
};

ସ୍ଥିର ସଂରଚନା constructor_range_ଗଦା *constructor_range_ଗଦା;

/* This stack records separate initializers that are nested.
   Nested initializers can't happen in ANSI C, but GNU C allows them
   in cases like { ... (struct foo) { ... } ... }.  */

ସଂରଚନା initializer_ଗଦା
{
  ସଂରଚନା initializer_ଗଦା *next;
  ବୃକ୍ଷ decl;
  ସଂରଚନା constructor_ଗଦା *constructor_ଗଦା;
  ସଂରଚନା constructor_range_ଗଦା *constructor_range_ଗଦା;
  vec<constructor_elt, va_gc> *elements;
  ସଂରଚନା spelling *spelling;
  ସଂରଚନା spelling *spelling_base;
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା spelling_size;
  ଅକ୍ଷର require_constant_ମୂଲ୍ୟ;
  ଅକ୍ଷର require_constant_elements;
  ଅକ୍ଷର require_constexpr_ମୂଲ୍ୟ;
  ଅକ୍ଷର designated;
  rich_location *missing_brace_richloc;
};

ସ୍ଥିର ସଂରଚନା initializer_ଗଦା *initializer_ଗଦା;

/* Prepare to parse and output the initializer for variable DECL.  */

ଶୂନ୍ୟ
start_init (ବୃକ୍ଷ decl, ବୃକ୍ଷ asmspec_ବୃକ୍ଷ ATTRIBUTE_UNUSED,
	    ତାର୍କିକ init_require_constant, ତାର୍କିକ init_require_constexpr,
	    rich_location *richloc)
{
  ଅଚଳ ଅକ୍ଷର *locus;
  ସଂରଚନା initializer_ଗଦା *p = XNEW (ସଂରଚନା initializer_ଗଦା);

  p->decl = constructor_decl;
  p->require_constant_ମୂଲ୍ୟ = require_constant_ମୂଲ୍ୟ;
  p->require_constant_elements = require_constant_elements;
  p->require_constexpr_ମୂଲ୍ୟ = require_constexpr_ମୂଲ୍ୟ;
  p->constructor_ଗଦା = constructor_ଗଦା;
  p->constructor_range_ଗଦା = constructor_range_ଗଦା;
  p->elements = constructor_elements;
  p->spelling = spelling;
  p->spelling_base = spelling_base;
  p->spelling_size = spelling_size;
  p->next = initializer_ଗଦା;
  p->missing_brace_richloc = richloc;
  p->designated = constructor_designated;
  initializer_ଗଦା = p;

  constructor_decl = decl;
  constructor_designated = 0;

  require_constant_ମୂଲ୍ୟ = init_require_constant;
  require_constexpr_ମୂଲ୍ୟ = init_require_constexpr;
  ଯଦି (decl != NULL_ବୃକ୍ଷ && decl != error_mark_ଗଣ୍ଠି)
    {
      require_constant_elements
	= ((init_require_constant || (pedantic && !flag_isoc99))
	   /* For a scalar, you can always use any value to initialize,
	      even within braces.  */
	   && AGGREGATE_TYPE_P (ବୃକ୍ଷ_TYPE (decl)));
      locus = identifier_to_locale (IDENTIFIER_POINTER (DECL_NAME (decl)));
    }
  ଅନ୍ୟଥା
    {
      require_constant_elements = ମିଥ୍ୟା;
      locus = _("(anonymous)");
    }

  constructor_ଗଦା = 0;
  constructor_range_ଗଦା = 0;

  found_missing_braces = 0;

  spelling_base = 0;
  spelling_size = 0;
  RESTORE_SPELLING_DEPTH (0);

  ଯଦି (locus)
    ଠେଲ_string (locus);
}

ଶୂନ୍ୟ
finish_init (ଶୂନ୍ୟ)
{
  ସଂରଚନା initializer_ଗଦା *p = initializer_ଗଦା;

  /* Free the whole constructor stack of this initializer.  */
  ଯେତେବେଳେ (constructor_ଗଦା)
    {
      ସଂରଚନା constructor_ଗଦା *q = constructor_ଗଦା;
      constructor_ଗଦା = q->next;
      XDELETE (q);
    }

  gcc_assert (!constructor_range_ଗଦା);

  /* Pop back to the data of the outer initializer (if any).  */
  XDELETE (spelling_base);

  constructor_decl = p->decl;
  require_constant_ମୂଲ୍ୟ = p->require_constant_ମୂଲ୍ୟ;
  require_constant_elements = p->require_constant_elements;
  require_constexpr_ମୂଲ୍ୟ = p->require_constexpr_ମୂଲ୍ୟ;
  constructor_ଗଦା = p->constructor_ଗଦା;
  constructor_designated = p->designated;
  constructor_range_ଗଦା = p->constructor_range_ଗଦା;
  constructor_elements = p->elements;
  spelling = p->spelling;
  spelling_base = p->spelling_base;
  spelling_size = p->spelling_size;
  initializer_ଗଦା = p->next;
  XDELETE (p);
}

/* Call here when we see the initializer is surrounded by braces.
   This is instead of a call to push_init_level;
   it is matched by a call to pop_init_level.

   TYPE is the type to initialize, for a constructor expression.
   For an initializer for a decl, TYPE is zero.  */

ଶୂନ୍ୟ
really_start_incremental_init (ବୃକ୍ଷ type)
{
  ସଂରଚନା constructor_ଗଦା *p = XNEW (ସଂରଚନା constructor_ଗଦା);

  ଯଦି (type == NULL_ବୃକ୍ଷ)
    type = ବୃକ୍ଷ_TYPE (constructor_decl);

  ଯଦି (VECTOR_TYPE_P (type)
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
  p->replacement_ମୂଲ୍ୟ.ମୂଲ୍ୟ = 0;
  p->replacement_ମୂଲ୍ୟ.original_code = ERROR_MARK;
  p->replacement_ମୂଲ୍ୟ.original_type = ଖାଲି;
  p->implicit = 0;
  p->range_ଗଦା = 0;
  p->outer = 0;
  p->incremental = constructor_incremental;
  p->designated = constructor_designated;
  p->zero_padding_bits = constructor_zero_padding_bits;
  p->braced_scalar = constructor_braced_scalar;
  p->designator_depth = designator_depth;
  p->next = 0;
  constructor_ଗଦା = p;

  constructor_constant = 1;
  constructor_simple = 1;
  constructor_nonconst = 0;
  constructor_depth = SPELLING_DEPTH ();
  constructor_elements = ଖାଲି;
  constructor_pending_elts = 0;
  constructor_type = type;
  constructor_incremental = 1;
  constructor_designated = 0;
  constructor_zero_padding_bits = ମିଥ୍ୟା;
  constructor_zeroinit = 1;
  constructor_braced_scalar = ମିଥ୍ୟା;
  designator_depth = 0;
  designator_erroneous = 0;

  ଯଦି (RECORD_OR_UNION_TYPE_P (constructor_type))
    {
      constructor_fields = TYPE_FIELDS (constructor_type);
      /* Skip any nameless bit fields at the beginning.  */
      ଯେତେବେଳେ (constructor_fields != NULL_ବୃକ୍ଷ
	     && DECL_UNNAMED_BIT_FIELD (constructor_fields))
	constructor_fields = DECL_CHAIN (constructor_fields);

      constructor_unfilled_fields = constructor_fields;
      constructor_bit_index = bitsize_zero_ଗଣ୍ଠି;
    }
  ଅନ୍ୟଥା ଯଦି (ବୃକ୍ଷ_CODE (constructor_type) == ARRAY_TYPE)
    {
      ଯଦି (TYPE_DOMAIN (constructor_type))
	{
	  constructor_max_index
	    = TYPE_MAX_ମୂଲ୍ୟ (TYPE_DOMAIN (constructor_type));

	  /* Detect non-empty initializations of zero-length arrays.  */
	  ଯଦି (constructor_max_index == NULL_ବୃକ୍ଷ
	      && TYPE_SIZE (constructor_type))
	    constructor_max_index = integer_minus_one_ଗଣ୍ଠି;

	  /* constructor_max_index needs to be an INTEGER_CST.  Attempts
	     to initialize VLAs with a nonempty initializer will cause a
	     proper error; avoid tree checking errors as well by setting a
	     safe value.  */
	  ଯଦି (constructor_max_index
	      && ବୃକ୍ଷ_CODE (constructor_max_index) != INTEGER_CST)
	    constructor_max_index = integer_minus_one_ଗଣ୍ଠି;

	  constructor_index
	    = convert (bitsizetype,
		       TYPE_MIN_ମୂଲ୍ୟ (TYPE_DOMAIN (constructor_type)));
	}
      ଅନ୍ୟଥା
	{
	  constructor_index = bitsize_zero_ଗଣ୍ଠି;
	  constructor_max_index = NULL_ବୃକ୍ଷ;
	}

      constructor_unfilled_index = constructor_index;
    }
  ଅନ୍ୟଥା ଯଦି (gnu_vector_type_p (constructor_type))
    {
      /* Vectors are like simple fixed-size arrays.  */
      constructor_max_index =
	bitsize_int (TYPE_VECTOR_SUBPARTS (constructor_type) - 1);
      constructor_index = bitsize_zero_ଗଣ୍ଠି;
      constructor_unfilled_index = constructor_index;
    }
  ଅନ୍ୟଥା
    {
      /* Handle the case of int x = {5}; */
      constructor_fields = constructor_type;
      constructor_unfilled_fields = constructor_type;
      constructor_braced_scalar = ସତ୍ୟ;
    }
}

ବାହ୍ୟ location_t last_init_list_comma;

/* Called when we see an open brace for a nested initializer.  Finish
   off any pending levels with implicit braces.  */
ଶୂନ୍ୟ
finish_implicit_inits (location_t loc, ସଂରଚନା obstack *braced_init_obstack)
{
  ଯେତେବେଳେ (constructor_ଗଦା->implicit)
    {
      ଯଦି (RECORD_OR_UNION_TYPE_P (constructor_type)
	  && constructor_fields == NULL_ବୃକ୍ଷ)
	process_init_element (ନିବେଶ_location,
			      କାଢ଼_init_level (loc, 1, braced_init_obstack,
					      last_init_list_comma),
			      ସତ୍ୟ, braced_init_obstack);
      ଅନ୍ୟଥା ଯଦି (ବୃକ୍ଷ_CODE (constructor_type) == ARRAY_TYPE
	       && constructor_max_index
	       && ବୃକ୍ଷ_int_cst_lt (constructor_max_index,
				   constructor_index))
	process_init_element (ନିବେଶ_location,
			      କାଢ଼_init_level (loc, 1, braced_init_obstack,
					      last_init_list_comma),
			      ସତ୍ୟ, braced_init_obstack);
      ଅନ୍ୟଥା
	ଭାଙ୍ଗ;
    }
}

/* Push down into a subobject, for initialization.
   If this is for an explicit set of braces, IMPLICIT is 0.
   If it is because the next element belongs at a lower level,
   IMPLICIT is 1 (or 2 if the push is because of designator list).  */

ଶୂନ୍ୟ
ଠେଲ_init_level (location_t loc, ପୂର୍ଣ୍ଣସଂଖ୍ୟା implicit,
		 ସଂରଚନା obstack *braced_init_obstack)
{
  ସଂରଚନା constructor_ଗଦା *p;
  ବୃକ୍ଷ ମୂଲ୍ୟ = NULL_ବୃକ୍ଷ;

  /* Unless this is an explicit brace, we need to preserve previous
     content if any.  */
  ଯଦି (implicit)
    {
      ଯଦି (RECORD_OR_UNION_TYPE_P (constructor_type) && constructor_fields)
	ମୂଲ୍ୟ = find_init_member (constructor_fields, braced_init_obstack);
      ଅନ୍ୟଥା ଯଦି (ବୃକ୍ଷ_CODE (constructor_type) == ARRAY_TYPE)
	ମୂଲ୍ୟ = find_init_member (constructor_index, braced_init_obstack);
    }

  p = XNEW (ସଂରଚନା constructor_ଗଦା);
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
  p->replacement_ମୂଲ୍ୟ.ମୂଲ୍ୟ = NULL_ବୃକ୍ଷ;
  p->replacement_ମୂଲ୍ୟ.original_code = ERROR_MARK;
  p->replacement_ମୂଲ୍ୟ.original_type = ଖାଲି;
  p->implicit = implicit;
  p->outer = 0;
  p->incremental = constructor_incremental;
  p->designated = constructor_designated;
  p->zero_padding_bits = constructor_zero_padding_bits;
  p->braced_scalar = constructor_braced_scalar;
  p->designator_depth = designator_depth;
  p->next = constructor_ଗଦା;
  p->range_ଗଦା = 0;
  constructor_ଗଦା = p;

  constructor_constant = 1;
  constructor_simple = 1;
  constructor_nonconst = 0;
  constructor_depth = SPELLING_DEPTH ();
  constructor_elements = ଖାଲି;
  constructor_incremental = 1;
  /* If the upper initializer is designated, then mark this as
     designated too to prevent bogus warnings.  */
  constructor_designated = p->designated;
  /* If the upper initializer has padding bits zeroed, that includes
     all nested initializers as well.  */
  constructor_zero_padding_bits = p->zero_padding_bits;
  constructor_braced_scalar = ମିଥ୍ୟା;
  constructor_pending_elts = 0;
  ଯଦି (!implicit)
    {
      p->range_ଗଦା = constructor_range_ଗଦା;
      constructor_range_ଗଦା = 0;
      designator_depth = 0;
      designator_erroneous = 0;
    }

  /* Don't die if an entire brace-pair level is superfluous
     in the containing level.  */
  ଯଦି (constructor_type == NULL_ବୃକ୍ଷ)
    ;
  ଅନ୍ୟଥା ଯଦି (RECORD_OR_UNION_TYPE_P (constructor_type))
    {
      /* Don't die if there are extra init elts at the end.  */
      ଯଦି (constructor_fields == NULL_ବୃକ୍ଷ)
	constructor_type = NULL_ବୃକ୍ଷ;
      ଅନ୍ୟଥା
	{
	  constructor_type = ବୃକ୍ଷ_TYPE (constructor_fields);
	  ଠେଲ_member_name (constructor_fields);
	  constructor_depth++;
	}
    }
  ଅନ୍ୟଥା ଯଦି (ବୃକ୍ଷ_CODE (constructor_type) == ARRAY_TYPE)
    {
      constructor_type = ବୃକ୍ଷ_TYPE (constructor_type);
      ଠେଲ_array_bounds (ବୃକ୍ଷ_to_uhwi (constructor_index));
      constructor_depth++;
    }

  ଯଦି (constructor_type == NULL_ବୃକ୍ଷ)
    {
      error_init (loc, "extra brace group at end of initializer");
      constructor_fields = NULL_ବୃକ୍ଷ;
      constructor_unfilled_fields = NULL_ବୃକ୍ଷ;
      ଫେରନ୍ତୁ;
    }

  ଯଦି (ମୂଲ୍ୟ && ବୃକ୍ଷ_CODE (ମୂଲ୍ୟ) == CONSTRUCTOR)
    {
      constructor_constant = ବୃକ୍ଷ_CONSTANT (ମୂଲ୍ୟ);
      constructor_simple = ବୃକ୍ଷ_STATIC (ମୂଲ୍ୟ);
      constructor_nonconst = CONSTRUCTOR_NON_CONST (ମୂଲ୍ୟ);
      constructor_elements = CONSTRUCTOR_ELTS (ମୂଲ୍ୟ);
      constructor_zero_padding_bits |= CONSTRUCTOR_ZERO_PADDING_BITS (ମୂଲ୍ୟ);
      ଯଦି (!vec_safe_is_empty (constructor_elements)
	  && (ବୃକ୍ଷ_CODE (constructor_type) == RECORD_TYPE
	      || ବୃକ୍ଷ_CODE (constructor_type) == ARRAY_TYPE))
	set_nonincremental_init (braced_init_obstack);
    }

  ଯଦି (implicit == 1)
    {
      found_missing_braces = 1;
      ଯଦି (initializer_ଗଦା->missing_brace_richloc)
	initializer_ଗଦା->missing_brace_richloc->add_fixit_ଭର୍ତ୍ତି_before
	  (loc, "{");
    }

  ଯଦି (RECORD_OR_UNION_TYPE_P (constructor_type))
    {
      constructor_fields = TYPE_FIELDS (constructor_type);
      /* Skip any nameless bit fields at the beginning.  */
      ଯେତେବେଳେ (constructor_fields != NULL_ବୃକ୍ଷ
	     && DECL_UNNAMED_BIT_FIELD (constructor_fields))
	constructor_fields = DECL_CHAIN (constructor_fields);

      constructor_unfilled_fields = constructor_fields;
      constructor_bit_index = bitsize_zero_ଗଣ୍ଠି;
    }
  ଅନ୍ୟଥା ଯଦି (gnu_vector_type_p (constructor_type))
    {
      /* Vectors are like simple fixed-size arrays.  */
      constructor_max_index =
	bitsize_int (TYPE_VECTOR_SUBPARTS (constructor_type) - 1);
      constructor_index = bitsize_int (0);
      constructor_unfilled_index = constructor_index;
    }
  ଅନ୍ୟଥା ଯଦି (ବୃକ୍ଷ_CODE (constructor_type) == ARRAY_TYPE)
    {
      ଯଦି (TYPE_DOMAIN (constructor_type))
	{
	  constructor_max_index
	    = TYPE_MAX_ମୂଲ୍ୟ (TYPE_DOMAIN (constructor_type));

	  /* Detect non-empty initializations of zero-length arrays.  */
	  ଯଦି (constructor_max_index == NULL_ବୃକ୍ଷ
	      && TYPE_SIZE (constructor_type))
	    constructor_max_index = integer_minus_one_ଗଣ୍ଠି;

	  /* constructor_max_index needs to be an INTEGER_CST.  Attempts
	     to initialize VLAs will cause a proper error; avoid tree
	     checking errors as well by setting a safe value.  */
	  ଯଦି (constructor_max_index
	      && ବୃକ୍ଷ_CODE (constructor_max_index) != INTEGER_CST)
	    constructor_max_index = integer_minus_one_ଗଣ୍ଠି;

	  constructor_index
	    = convert (bitsizetype,
		       TYPE_MIN_ମୂଲ୍ୟ (TYPE_DOMAIN (constructor_type)));
	}
      ଅନ୍ୟଥା
	constructor_index = bitsize_zero_ଗଣ୍ଠି;

      constructor_unfilled_index = constructor_index;
      ଯଦି (ମୂଲ୍ୟ && ବୃକ୍ଷ_CODE (ମୂଲ୍ୟ) == STRING_CST)
	{
	  /* We need to split the char/wchar array into individual
	     characters, so that we don't have to special case it
	     everywhere.  */
	  set_nonincremental_init_from_string (ମୂଲ୍ୟ, braced_init_obstack);
	}
    }
  ଅନ୍ୟଥା
    {
      ଯଦି (constructor_type != error_mark_ଗଣ୍ଠି)
	{
	  ଯଦି (p->braced_scalar)
	    permerror_init (ନିବେଶ_location, 0,
			    "braces around scalar initializer");
	  ଅନ୍ୟଥା
	    warning_init (ନିବେଶ_location, 0,
			  "braces around scalar initializer");
	  constructor_braced_scalar = ସତ୍ୟ;
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

ସଂରଚନା c_ପଦସମଷ୍ଟି
କାଢ଼_init_level (location_t loc, ପୂର୍ଣ୍ଣସଂଖ୍ୟା implicit,
		ସଂରଚନା obstack *braced_init_obstack,
		location_t ଭର୍ତ୍ତି_before)
{
  ସଂରଚନା constructor_ଗଦା *p;
  ସଂରଚନା c_ପଦସମଷ୍ଟି ret;
  ret.ମୂଲ୍ୟ = NULL_ବୃକ୍ଷ;
  ret.original_code = ERROR_MARK;
  ret.original_type = ଖାଲି;
  ret.m_decimal = 0;

  ଯଦି (implicit == 0)
    {
      /* When we come to an explicit close brace,
	 pop any inner levels that didn't have explicit braces.  */
      ଯେତେବେଳେ (constructor_ଗଦା->implicit)
	process_init_element (ନିବେଶ_location,
			      କାଢ଼_init_level (loc, 1, braced_init_obstack,
					      ଭର୍ତ୍ତି_before),
			      ସତ୍ୟ, braced_init_obstack);
      gcc_assert (!constructor_range_ଗଦା);
    }
  ଅନ୍ୟଥା
    ଯଦି (initializer_ଗଦା->missing_brace_richloc)
      initializer_ଗଦା->missing_brace_richloc->add_fixit_ଭର୍ତ୍ତି_before
	(ଭର୍ତ୍ତି_before, "}");

  /* Now output all pending elements.  */
  constructor_incremental = 1;
  output_pending_init_elements (1, braced_init_obstack);

  p = constructor_ଗଦା;

  /* Error for initializing a flexible array member.  */
  ଯଦି (constructor_type && constructor_fields
      && flexible_array_member_type_p (constructor_type))
    {
      /* Silently discard empty initializations.  The parser will
	 already have pedwarned for empty brackets for C17 and earlier.  */
      ଯଦି (integer_zerop (constructor_unfilled_index))
	constructor_type = NULL_ବୃକ୍ଷ;
      ଯଦି (constructor_type || flag_isoc23)
	{
	  gcc_assert (!constructor_type || !TYPE_SIZE (constructor_type));

	  ଯଦି (constructor_depth <= 2)
	    pedwarn_init (loc, OPT_Wpedantic,
			  "initialization of a flexible array member");
	  ଅନ୍ୟଥା ଯଦି (constructor_type)
	    error_init (loc, "initialization of flexible array member "
			     "in a nested context");
	  ଅନ୍ୟଥା
	    pedwarn_init (loc, OPT_Wpedantic,
			  "initialization of flexible array member "
			  "in a nested context");

	  /* We have already issued an error message for the existence
	     of a flexible array member not at the end of the structure.
	     Discard the initializer so that we do not die later.  */
	  ଯଦି (constructor_type
	      && DECL_CHAIN (constructor_fields) != NULL_ବୃକ୍ଷ
	      && (!p->type || ବୃକ୍ଷ_CODE (p->type) != UNION_TYPE))
	    constructor_type = NULL_ବୃକ୍ଷ;
	}
    }

  ବାଛ (vec_safe_length (constructor_elements))
    {
    ସ୍ଥିତି 0:
      /* Initialization with { } counts as zeroinit.  */
      constructor_zeroinit = 1;
      ଭାଙ୍ଗ;
    ସ୍ଥିତି 1:
      /* This might be zeroinit as well.  */
      ଯଦି (integer_zerop ((*constructor_elements)[0].ମୂଲ୍ୟ))
	constructor_zeroinit = 1;
      ଭାଙ୍ଗ;
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
      /* If the constructor has more than one element, it can't be { 0 }.  */
      constructor_zeroinit = 0;
      ଭାଙ୍ଗ;
    }

  /* Warn when some structs are initialized with direct aggregation.  */
  ଯଦି (!implicit && found_missing_braces && warn_missing_braces
      && !constructor_zeroinit)
    {
      gcc_assert (initializer_ଗଦା->missing_brace_richloc);
      warning_at (initializer_ଗଦା->missing_brace_richloc,
		  OPT_Wmissing_braces,
		  "missing braces around initializer");
    }

  /* Warn when some struct elements are implicitly initialized to zero.  */
  ଯଦି (warn_missing_field_initializers
      && constructor_type
      && ବୃକ୍ଷ_CODE (constructor_type) == RECORD_TYPE
      && constructor_unfilled_fields)
    {
	/* Do not warn for flexible array members or zero-length arrays.  */
	ଯେତେବେଳେ (constructor_unfilled_fields
	       && (!DECL_SIZE (constructor_unfilled_fields)
		   || integer_zerop (DECL_SIZE (constructor_unfilled_fields))))
	  constructor_unfilled_fields = DECL_CHAIN (constructor_unfilled_fields);

	ଯଦି (constructor_unfilled_fields
	    /* Do not warn if this level of the initializer uses member
	       designators; it is likely to be deliberate.  */
	    && !constructor_designated
	    /* Do not warn about initializing with { 0 } or with { }.  */
	    && !constructor_zeroinit)
	  {
	    ଯଦି (warning_at (ନିବେଶ_location, OPT_Wmissing_field_initializers,
			    "missing initializer for field %qD of %qT",
			    constructor_unfilled_fields,
			    constructor_type))
	      inform (DECL_SOURCE_LOCATION (constructor_unfilled_fields),
		      "%qD declared here", constructor_unfilled_fields);
	  }
    }

  /* Pad out the end of the structure.  */
  ଯଦି (p->replacement_ମୂଲ୍ୟ.ମୂଲ୍ୟ)
    /* If this closes a superfluous brace pair,
       just pass out the element between them.  */
    ret = p->replacement_ମୂଲ୍ୟ;
  ଅନ୍ୟଥା ଯଦି (constructor_type == NULL_ବୃକ୍ଷ)
    ;
  ଅନ୍ୟଥା ଯଦି (!RECORD_OR_UNION_TYPE_P (constructor_type)
	   && ବୃକ୍ଷ_CODE (constructor_type) != ARRAY_TYPE
	   && !gnu_vector_type_p (constructor_type))
    {
      /* A nonincremental scalar initializer--just return
	 the element, after verifying there is just one.
         Empty scalar initializers are supported in C23.  */
      ଯଦି (vec_safe_is_empty (constructor_elements))
	{
	  ଯଦି (constructor_erroneous || constructor_type == error_mark_ଗଣ୍ଠି)
	    ret.ମୂଲ୍ୟ = error_mark_ଗଣ୍ଠି;
	  ଅନ୍ୟଥା ଯଦି (ବୃକ୍ଷ_CODE (constructor_type) == FUNCTION_TYPE)
	    {
	      error_init (loc, "invalid initializer");
	      ret.ମୂଲ୍ୟ = error_mark_ଗଣ୍ଠି;
	    }
	  ଅନ୍ୟଥା ଯଦି (ବୃକ୍ଷ_CODE (constructor_type) == POINTER_TYPE)
	    /* Ensure this is a null pointer constant in the case of a
	       'constexpr' object initialized with {}.  */
	    ret.ମୂଲ୍ୟ = build_zero_cst (ptr_type_ଗଣ୍ଠି);
	  ଅନ୍ୟଥା
	    ret.ମୂଲ୍ୟ = build_zero_cst (constructor_type);
	}
      ଅନ୍ୟଥା ଯଦି (vec_safe_length (constructor_elements) != 1)
	{
	  error_init (loc, "extra elements in scalar initializer");
	  ret.ମୂଲ୍ୟ = (*constructor_elements)[0].ମୂଲ୍ୟ;
	}
      ଅନ୍ୟଥା
	ret.ମୂଲ୍ୟ = (*constructor_elements)[0].ମୂଲ୍ୟ;
    }
  ଅନ୍ୟଥା
    {
      ଯଦି (constructor_erroneous)
	ret.ମୂଲ୍ୟ = error_mark_ଗଣ୍ଠି;
      ଅନ୍ୟଥା
	{
	  ret.ମୂଲ୍ୟ = build_constructor (constructor_type,
					 constructor_elements);
	  ଯଦି (constructor_constant)
	    ବୃକ୍ଷ_CONSTANT (ret.ମୂଲ୍ୟ) = 1;
	  ଯଦି (constructor_constant && constructor_simple)
	    ବୃକ୍ଷ_STATIC (ret.ମୂଲ୍ୟ) = 1;
	  ଯଦି (constructor_nonconst)
	    CONSTRUCTOR_NON_CONST (ret.ମୂଲ୍ୟ) = 1;
	  ଯଦି (constructor_zero_padding_bits)
	    CONSTRUCTOR_ZERO_PADDING_BITS (ret.ମୂଲ୍ୟ) = 1;
	}
    }

  ଯଦି (ret.ମୂଲ୍ୟ && ବୃକ୍ଷ_CODE (ret.ମୂଲ୍ୟ) != CONSTRUCTOR)
    {
      ଯଦି (constructor_nonconst)
	ret.original_code = C_MAYBE_CONST_ପଦସମଷ୍ଟି;
      ଅନ୍ୟଥା ଯଦି (ret.original_code == C_MAYBE_CONST_ପଦସମଷ୍ଟି)
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
  ଯଦି (!p->implicit)
    constructor_range_ଗଦା = p->range_ଗଦା;
  RESTORE_SPELLING_DEPTH (constructor_depth);

  constructor_ଗଦା = p->next;
  XDELETE (p);

  ଯଦି (ret.ମୂଲ୍ୟ == NULL_ବୃକ୍ଷ && constructor_ଗଦା == 0)
    ret.ମୂଲ୍ୟ = error_mark_ଗଣ୍ଠି;
  ଫେରନ୍ତୁ ret;
}

/* Common handling for both array range and field name designators.
   ARRAY argument is nonzero for array ranges.  Returns false for success.  */

ସ୍ଥିର ତାର୍କିକ
set_designator (location_t loc, ତାର୍କିକ array,
		ସଂରଚନା obstack *braced_init_obstack)
{
  ବୃକ୍ଷ subtype;
  ଗଣନା ବୃକ୍ଷ_code subcode;

  /* Don't die if an entire brace-pair level is superfluous
     in the containing level, or for an erroneous type.  */
  ଯଦି (constructor_type == NULL_ବୃକ୍ଷ || constructor_type == error_mark_ଗଣ୍ଠି)
    ଫେରନ୍ତୁ ସତ୍ୟ;

  /* If there were errors in this designator list already, bail out
     silently.  */
  ଯଦି (designator_erroneous)
    ଫେରନ୍ତୁ ସତ୍ୟ;

  /* Likewise for an initializer for a variable-size type.  Those are
     diagnosed in the parser, except for empty initializer braces.  */
  ଯଦି (COMPLETE_TYPE_P (constructor_type)
      && ବୃକ୍ଷ_CODE (TYPE_SIZE (constructor_type)) != INTEGER_CST)
    ଫେରନ୍ତୁ ସତ୍ୟ;

  ଯଦି (!designator_depth)
    {
      gcc_assert (!constructor_range_ଗଦା);

      /* Designator list starts at the level of closest explicit
	 braces.  */
      ଯେତେବେଳେ (constructor_ଗଦା->implicit)
	process_init_element (ନିବେଶ_location,
			      କାଢ଼_init_level (loc, 1, braced_init_obstack,
					      last_init_list_comma),
			      ସତ୍ୟ, braced_init_obstack);
      constructor_designated = 1;
      ଫେରନ୍ତୁ ମିଥ୍ୟା;
    }

  ବାଛ (ବୃକ୍ଷ_CODE (constructor_type))
    {
    ସ୍ଥିତି  RECORD_TYPE:
    ସ୍ଥିତି  UNION_TYPE:
      subtype = ବୃକ୍ଷ_TYPE (constructor_fields);
      ଯଦି (subtype != error_mark_ଗଣ୍ଠି)
	subtype = TYPE_MAIN_VARIANT (subtype);
      ଭାଙ୍ଗ;
    ସ୍ଥିତି ARRAY_TYPE:
      subtype = TYPE_MAIN_VARIANT (ବୃକ୍ଷ_TYPE (constructor_type));
      ଭାଙ୍ଗ;
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
      gcc_unreachable ();
    }

  subcode = ବୃକ୍ଷ_CODE (subtype);
  ଯଦି (array && subcode != ARRAY_TYPE)
    {
      error_init (loc, "array index in non-array initializer");
      ଫେରନ୍ତୁ ସତ୍ୟ;
    }
  ଅନ୍ୟଥା ଯଦି (!array && subcode != RECORD_TYPE && subcode != UNION_TYPE)
    {
      error_init (loc, "field name not in record or union initializer");
      ଫେରନ୍ତୁ ସତ୍ୟ;
    }

  constructor_designated = 1;
  finish_implicit_inits (loc, braced_init_obstack);
  ଠେଲ_init_level (loc, 2, braced_init_obstack);
  ଫେରନ୍ତୁ ମିଥ୍ୟା;
}

/* If there are range designators in designator list, push a new designator
   to constructor_range_stack.  RANGE_END is end of such stack range or
   NULL_TREE if there is no range designator at this level.  */

ସ୍ଥିର ଶୂନ୍ୟ
ଠେଲ_range_ଗଦା (ବୃକ୍ଷ range_end, ସଂରଚନା obstack * braced_init_obstack)
{
  ସଂରଚନା constructor_range_ଗଦା *p;

  p = (ସଂରଚନା constructor_range_ଗଦା *)
    obstack_alloc (braced_init_obstack,
		   ଆକାର (ସଂରଚନା constructor_range_ଗଦା));
  p->prev = constructor_range_ଗଦା;
  p->next = 0;
  p->fields = constructor_fields;
  p->range_start = constructor_index;
  p->index = constructor_index;
  p->ଗଦା = constructor_ଗଦା;
  p->range_end = range_end;
  ଯଦି (constructor_range_ଗଦା)
    constructor_range_ଗଦା->next = p;
  constructor_range_ଗଦା = p;
}

/* Within an array initializer, specify the next index to be initialized.
   FIRST is that index.  If LAST is nonzero, then initialize a range
   of indices, running from FIRST through LAST.  */

ଶୂନ୍ୟ
set_init_index (location_t loc, ବୃକ୍ଷ first, ବୃକ୍ଷ last,
		ସଂରଚନା obstack *braced_init_obstack)
{
  ଯଦି (set_designator (loc, ସତ୍ୟ, braced_init_obstack))
    ଫେରନ୍ତୁ;

  designator_erroneous = 1;

  ଯଦି (!INTEGRAL_TYPE_P (ବୃକ୍ଷ_TYPE (first))
      || (last && !INTEGRAL_TYPE_P (ବୃକ୍ଷ_TYPE (last))))
    {
      error_init (loc, "array index in initializer not of integer type");
      ଫେରନ୍ତୁ;
    }

  ଯଦି (ବୃକ୍ଷ_CODE (first) != INTEGER_CST)
    {
      first = c_fully_fold (first, ମିଥ୍ୟା, ଖାଲି);
      ଯଦି (ବୃକ୍ଷ_CODE (first) == INTEGER_CST)
	pedwarn_init (loc, OPT_Wpedantic,
		      "array index in initializer is not "
		      "an integer constant expression");
    }

  ଯଦି (last && ବୃକ୍ଷ_CODE (last) != INTEGER_CST)
    {
      last = c_fully_fold (last, ମିଥ୍ୟା, ଖାଲି);
      ଯଦି (ବୃକ୍ଷ_CODE (last) == INTEGER_CST)
	pedwarn_init (loc, OPT_Wpedantic,
		      "array index in initializer is not "
		      "an integer constant expression");
    }

  ଯଦି (ବୃକ୍ଷ_CODE (first) != INTEGER_CST)
    error_init (loc, "nonconstant array index in initializer");
  ଅନ୍ୟଥା ଯଦି (last != NULL_ବୃକ୍ଷ && ବୃକ୍ଷ_CODE (last) != INTEGER_CST)
    error_init (loc, "nonconstant array index in initializer");
  ଅନ୍ୟଥା ଯଦି (ବୃକ୍ଷ_CODE (constructor_type) != ARRAY_TYPE)
    error_init (loc, "array index in non-array initializer");
  ଅନ୍ୟଥା ଯଦି (ବୃକ୍ଷ_int_cst_sgn (first) == -1)
    error_init (loc, "array index in initializer exceeds array bounds");
  ଅନ୍ୟଥା ଯଦି (constructor_max_index
	   && ବୃକ୍ଷ_int_cst_lt (constructor_max_index, first))
    error_init (loc, "array index in initializer exceeds array bounds");
  ଅନ୍ୟଥା
    {
      constant_expression_warning (first);
      ଯଦି (last)
	constant_expression_warning (last);
      constructor_index = convert (bitsizetype, first);
      ଯଦି (ବୃକ୍ଷ_int_cst_lt (constructor_index, first))
	{
	  constructor_index = copy_ଗଣ୍ଠି (constructor_index);
	  ବୃକ୍ଷ_OVERFLOW (constructor_index) = 1;
	}

      ଯଦି (last)
	{
	  ଯଦି (ବୃକ୍ଷ_int_cst_equal (first, last))
	    last = NULL_ବୃକ୍ଷ;
	  ଅନ୍ୟଥା ଯଦି (ବୃକ୍ଷ_int_cst_lt (last, first))
	    {
	      error_init (loc, "empty index range in initializer");
	      last = NULL_ବୃକ୍ଷ;
	    }
	  ଅନ୍ୟଥା
	    {
	      last = convert (bitsizetype, last);
	      ଯଦି (constructor_max_index != NULL_ବୃକ୍ଷ
		  && ବୃକ୍ଷ_int_cst_lt (constructor_max_index, last))
		{
		  error_init (loc, "array index range in initializer exceeds "
			      "array bounds");
		  last = NULL_ବୃକ୍ଷ;
		}
	    }
	}

      designator_depth++;
      designator_erroneous = 0;
      ଯଦି (constructor_range_ଗଦା || last)
	ଠେଲ_range_ଗଦା (last, braced_init_obstack);
    }
}

/* Within a struct initializer, specify the next field to be initialized.  */

ଶୂନ୍ୟ
set_init_label (location_t loc, ବୃକ୍ଷ fieldname, location_t fieldname_loc,
		ସଂରଚନା obstack *braced_init_obstack)
{
  ବୃକ୍ଷ field;

  ଯଦି (set_designator (loc, ମିଥ୍ୟା, braced_init_obstack))
    ଫେରନ୍ତୁ;

  designator_erroneous = 1;

  ଯଦି (!RECORD_OR_UNION_TYPE_P (constructor_type))
    {
      error_init (loc, "field name not in record or union initializer");
      ଫେରନ୍ତୁ;
    }

  field = lookup_field (constructor_type, fieldname);

  ଯଦି (field == NULL_ବୃକ୍ଷ)
    {
      ବୃକ୍ଷ guessed_id = lookup_field_fuzzy (constructor_type, fieldname);
      ଯଦି (guessed_id)
	{
	  gcc_rich_location rich_loc (fieldname_loc);
	  rich_loc.add_fixit_misspelled_id (fieldname_loc, guessed_id);
	  error_at (&rich_loc,
		    "%qT has no member named %qE; did you mean %qE?",
		    constructor_type, fieldname, guessed_id);
	}
      ଅନ୍ୟଥା
	error_at (fieldname_loc, "%qT has no member named %qE",
		  constructor_type, fieldname);
    }
  ଅନ୍ୟଥା
    କର
      {
	constructor_fields = ବୃକ୍ଷ_ମୂଲ୍ୟ (field);
	designator_depth++;
	designator_erroneous = 0;
	ଯଦି (constructor_range_ଗଦା)
	  ଠେଲ_range_ଗଦା (NULL_ବୃକ୍ଷ, braced_init_obstack);
	field = ବୃକ୍ଷ_CHAIN (field);
	ଯଦି (field)
	  {
	    ଯଦି (set_designator (loc, ମିଥ୍ୟା, braced_init_obstack))
	      ଫେରନ୍ତୁ;
	  }
      }
    ଯେତେବେଳେ (field != NULL_ବୃକ୍ଷ);
}

/* Helper function for add_pending_init.  Find inorder successor of P
   in AVL tree.  */
ସ୍ଥିର ସଂରଚନା init_ଗଣ୍ଠି *
init_ଗଣ୍ଠି_successor (ସଂରଚନା init_ଗଣ୍ଠି *p)
{
  ସଂରଚନା init_ଗଣ୍ଠି *r;
  ଯଦି (p->ଡାହାଣ)
    {
      r = p->ଡାହାଣ;
      ଯେତେବେଳେ (r->ବାମ)
	r = r->ବାମ;
      ଫେରନ୍ତୁ r;
    }
  r = p->parent;
  ଯେତେବେଳେ (r && p == r->ଡାହାଣ)
    {
      p = r;
      r = r->parent;
    }
  ଫେରନ୍ତୁ r;
}

/* Add a new initializer to the tree of pending initializers.  PURPOSE
   identifies the initializer, either array index or field in a structure.
   VALUE is the value of that index or field.  If ORIGTYPE is not
   NULL_TREE, it is the original type of VALUE.

   IMPLICIT is true if value comes from pop_init_level (1),
   the new initializer has been merged with the existing one
   and thus no warnings should be emitted about overriding an
   existing initializer.  */

ସ୍ଥିର ଶୂନ୍ୟ
add_pending_init (location_t loc, ବୃକ୍ଷ purpose, ବୃକ୍ଷ ମୂଲ୍ୟ, ବୃକ୍ଷ origtype,
		  ତାର୍କିକ implicit, ସଂରଚନା obstack *braced_init_obstack)
{
  ସଂରଚନା init_ଗଣ୍ଠି *p, **q, *r;

  q = &constructor_pending_elts;
  p = 0;

  ଯଦି (ବୃକ୍ଷ_CODE (constructor_type) == ARRAY_TYPE)
    {
      ଯେତେବେଳେ (*q != 0)
	{
	  p = *q;
	  ଯଦି (ବୃକ୍ଷ_int_cst_lt (purpose, p->purpose))
	    q = &p->ବାମ;
	  ଅନ୍ୟଥା ଯଦି (ବୃକ୍ଷ_int_cst_lt (p->purpose, purpose))
	    {
	      ଯଦି (ବୃକ୍ଷ_CODE (p->ମୂଲ୍ୟ) != RAW_DATA_CST
		  || (p->ଡାହାଣ
		      && ବୃକ୍ଷ_int_cst_le (p->ଡାହାଣ->purpose, purpose)))
		q = &p->ଡାହାଣ;
	      ଅନ୍ୟଥା
		{
		  widest_int pp = wi::to_widest (p->purpose);
		  widest_int pw = wi::to_widest (purpose);
		  ଯଦି (pp + RAW_DATA_LENGTH (p->ମୂଲ୍ୟ) <= pw)
		    q = &p->ଡାହାଣ;
		  ଅନ୍ୟଥା
		    {
		      /* Override which should split the old RAW_DATA_CST
			 into 2 or 3 pieces.  */
		      ଯଦି (!implicit && warn_override_init)
			warning_init (loc, OPT_Woverride_init,
				      "initialized field overwritten");
		      unsigned HOST_WIDE_INT start = (pw - pp).to_uhwi ();
		      unsigned HOST_WIDE_INT len = 1;
		      ଯଦି (ବୃକ୍ଷ_CODE (ମୂଲ୍ୟ) == RAW_DATA_CST)
			len = RAW_DATA_LENGTH (ମୂଲ୍ୟ);
		      unsigned HOST_WIDE_INT end = 0;
		      unsigned plen = RAW_DATA_LENGTH (p->ମୂଲ୍ୟ);
		      gcc_checking_assert (start < plen && start);
		      ଯଦି (plen - start > len)
			end = plen - start - len;
		      ବୃକ୍ଷ v = p->ମୂଲ୍ୟ;
		      ବୃକ୍ଷ origtype = p->origtype;
		      ଯଦି (start == 1)
			p->ମୂଲ୍ୟ = build_int_cst (ବୃକ୍ଷ_TYPE (v),
						  RAW_DATA_UCHAR_ELT (v, 0));
		      ଅନ୍ୟଥା
			{
			  p->ମୂଲ୍ୟ = v;
			  ଯଦି (end > 1)
			    v = copy_ଗଣ୍ଠି (v);
			  RAW_DATA_LENGTH (p->ମୂଲ୍ୟ) = start;
			}
		      ଯଦି (end)
			{
			  ବୃକ୍ଷ epurpose
			    = size_binop (PLUS_ପଦସମଷ୍ଟି, purpose,
					  bitsize_int (len));
			  ଯଦି (end > 1)
			    {
			      RAW_DATA_LENGTH (v) -= plen - end;
			      RAW_DATA_POINTER (v) += plen - end;
			    }
			  ଅନ୍ୟଥା
			    v = build_int_cst (ବୃକ୍ଷ_TYPE (v),
					       RAW_DATA_UCHAR_ELT (v, plen
								      - end));
			  add_pending_init (loc, epurpose, v, origtype,
					    implicit, braced_init_obstack);
			}
		      q = &constructor_pending_elts;
		      ଜାରି;
		    }
		}
	    }
	  ଅନ୍ୟଥା
	    {
	      ଯଦି (ବୃକ୍ଷ_CODE (p->ମୂଲ୍ୟ) == RAW_DATA_CST
		  && (RAW_DATA_LENGTH (p->ମୂଲ୍ୟ)
		      > (ବୃକ୍ଷ_CODE (ମୂଲ୍ୟ) == RAW_DATA_CST
			 ? RAW_DATA_LENGTH (ମୂଲ୍ୟ) : 1)))
		{
		  /* Override which should split the old RAW_DATA_CST
		     into 2 pieces.  */
		  ଯଦି (!implicit && warn_override_init)
		    warning_init (loc, OPT_Woverride_init,
				  "initialized field overwritten");
		  unsigned HOST_WIDE_INT len = 1;
		  ଯଦି (ବୃକ୍ଷ_CODE (ମୂଲ୍ୟ) == RAW_DATA_CST)
		    len = RAW_DATA_LENGTH (ମୂଲ୍ୟ);
		  ଯଦି ((unsigned) RAW_DATA_LENGTH (p->ମୂଲ୍ୟ) > len + 1)
		    {
		      RAW_DATA_LENGTH (p->ମୂଲ୍ୟ) -= len;
		      RAW_DATA_POINTER (p->ମୂଲ୍ୟ) += len;
		    }
		  ଅନ୍ୟଥା
		    {
		      unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା l = RAW_DATA_LENGTH (p->ମୂଲ୍ୟ) - 1;
		      p->ମୂଲ୍ୟ
			= build_int_cst (ବୃକ୍ଷ_TYPE (p->ମୂଲ୍ୟ),
					 RAW_DATA_UCHAR_ELT (p->ମୂଲ୍ୟ, l));
		    }
		  p->purpose = size_binop (PLUS_ପଦସମଷ୍ଟି, p->purpose,
					   bitsize_int (len));
		  ଜାରି;
		}
	      ଯଦି (ବୃକ୍ଷ_CODE (ମୂଲ୍ୟ) == RAW_DATA_CST)
		{
		handle_raw_data:
		  /* RAW_DATA_CST value might overlap various further
		     prior initval entries.  Find out how many.  */
		  unsigned cnt = 0;
		  widest_int w
		    = wi::to_widest (purpose) + RAW_DATA_LENGTH (ମୂଲ୍ୟ);
		  ସଂରଚନା init_ଗଣ୍ଠି *r = p, *last = ଖାଲି;
		  ତାର୍କିକ override_init = warn_override_init;
		  ଯେତେବେଳେ ((r = init_ଗଣ୍ଠି_successor (r))
			 && wi::to_widest (r->purpose) < w)
		    {
		      ++cnt;
		      ଯଦି (ବୃକ୍ଷ_SIDE_EFFECTS (r->ମୂଲ୍ୟ))
			warning_init (loc, OPT_Woverride_init_side_effects,
				      "initialized field with side-effects "
				      "overwritten");
		      ଅନ୍ୟଥା ଯଦି (override_init)
			{
			  warning_init (loc, OPT_Woverride_init,
					"initialized field overwritten");
			  override_init = ମିଥ୍ୟା;
			}
		      last = r;
		    }
		  ଯଦି (cnt)
		    {
		      ଯଦି (ବୃକ୍ଷ_CODE (last->ମୂଲ୍ୟ) == RAW_DATA_CST
			  && (wi::to_widest (last->purpose)
			      + RAW_DATA_LENGTH (last->ମୂଲ୍ୟ) > w))
			{
			  /* The last overlapping prior initval overlaps
			     only partially.  Shrink it and decrease cnt.  */
			  unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା l = (wi::to_widest (last->purpose)
					    + RAW_DATA_LENGTH (last->ମୂଲ୍ୟ)
					    - w).to_uhwi ();
			  --cnt;
			  RAW_DATA_LENGTH (last->ମୂଲ୍ୟ) -= l;
			  RAW_DATA_POINTER (last->ମୂଲ୍ୟ) += l;
			  ଯଦି (RAW_DATA_LENGTH (last->ମୂଲ୍ୟ) == 1)
			    last->ମୂଲ୍ୟ
			      = build_int_cst (ବୃକ୍ଷ_TYPE (last->ମୂଲ୍ୟ),
					       RAW_DATA_UCHAR_ELT (last->ମୂଲ୍ୟ,
								   0));
			  last->purpose
			    = size_binop (PLUS_ପଦସମଷ୍ଟି, last->purpose,
					  bitsize_int (l));
			}
		      /* Instead of deleting cnt nodes from the AVL tree
			 and rebalancing, peel of last cnt bytes from the
			 RAW_DATA_CST.  Overriding thousands of previously
			 initialized array elements with #embed needs to work,
			 but doesn't need to be super efficient.  */
		      gcc_checking_assert ((unsigned) RAW_DATA_LENGTH (ମୂଲ୍ୟ)
					   > cnt);
		      RAW_DATA_LENGTH (ମୂଲ୍ୟ) -= cnt;
		      ଅଚଳ unsigned ଅକ୍ଷର *s
			= &RAW_DATA_UCHAR_ELT (ମୂଲ୍ୟ, RAW_DATA_LENGTH (ମୂଲ୍ୟ));
		      unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା o = RAW_DATA_LENGTH (ମୂଲ୍ୟ);
		      ପାଇଁ (r = p; cnt--; ++o, ++s)
			{
			  r = init_ଗଣ୍ଠି_successor (r);
			  r->purpose = size_binop (PLUS_ପଦସମଷ୍ଟି, purpose,
						   bitsize_int (o));
			  r->ମୂଲ୍ୟ = build_int_cst (ବୃକ୍ଷ_TYPE (ମୂଲ୍ୟ), *s);
			  r->origtype = origtype;
			}
		      ଯଦି (RAW_DATA_LENGTH (ମୂଲ୍ୟ) == 1)
			ମୂଲ୍ୟ = build_int_cst (ବୃକ୍ଷ_TYPE (ମୂଲ୍ୟ),
					       RAW_DATA_UCHAR_ELT (ମୂଲ୍ୟ, 0));
		    }
		}
	      ଯଦି (!implicit)
		{
		  ଯଦି (ବୃକ୍ଷ_SIDE_EFFECTS (p->ମୂଲ୍ୟ))
		    warning_init (loc, OPT_Woverride_init_side_effects,
				  "initialized field with side-effects "
				  "overwritten");
		  ଅନ୍ୟଥା ଯଦି (warn_override_init)
		    warning_init (loc, OPT_Woverride_init,
				  "initialized field overwritten");
		}
	      p->ମୂଲ୍ୟ = ମୂଲ୍ୟ;
	      p->origtype = origtype;
	      ଫେରନ୍ତୁ;
	    }
	}
      ଯଦି (ବୃକ୍ଷ_CODE (ମୂଲ୍ୟ) == RAW_DATA_CST && p)
	{
	  ସଂରଚନା init_ଗଣ୍ଠି *r;
	  ଯଦି (q == &p->ବାମ)
	    r = p;
	  ଅନ୍ୟଥା
	    r = init_ଗଣ୍ଠି_successor (p);
	  ଯଦି (r && wi::to_widest (r->purpose) < (wi::to_widest (purpose)
						 + RAW_DATA_LENGTH (ମୂଲ୍ୟ)))
	    {
	      /* Overlap with at least one prior initval in the range but
		 not at the start.  */
	      p = r;
	      p->purpose = purpose;
	      ଯାଅ handle_raw_data;
	    }
	}
    }
  ଅନ୍ୟଥା
    {
      ବୃକ୍ଷ bitpos;

      bitpos = bit_position (purpose);
      ଯେତେବେଳେ (*q != ଖାଲି)
	{
	  p = *q;
	  ଯଦି (ବୃକ୍ଷ_int_cst_lt (bitpos, bit_position (p->purpose)))
	    q = &p->ବାମ;
	  ଅନ୍ୟଥା ଯଦି (p->purpose != purpose)
	    q = &p->ଡାହାଣ;
	  ଅନ୍ୟଥା
	    {
	      ଯଦି (!implicit)
		{
		  ଯଦି (ବୃକ୍ଷ_SIDE_EFFECTS (p->ମୂଲ୍ୟ))
		    warning_init (loc, OPT_Woverride_init_side_effects,
				  "initialized field with side-effects "
				  "overwritten");
		  ଅନ୍ୟଥା ଯଦି (warn_override_init)
		    warning_init (loc, OPT_Woverride_init,
				  "initialized field overwritten");
		}
	      p->ମୂଲ୍ୟ = ମୂଲ୍ୟ;
	      p->origtype = origtype;
	      ଫେରନ୍ତୁ;
	    }
	}
    }

  r = (ସଂରଚନା init_ଗଣ୍ଠି *) obstack_alloc (braced_init_obstack,
					  ଆକାର (ସଂରଚନା init_ଗଣ୍ଠି));
  r->purpose = purpose;
  r->ମୂଲ୍ୟ = ମୂଲ୍ୟ;
  r->origtype = origtype;

  *q = r;
  r->parent = p;
  r->ବାମ = 0;
  r->ଡାହାଣ = 0;
  r->balance = 0;

  ଯେତେବେଳେ (p)
    {
      ସଂରଚନା init_ଗଣ୍ଠି *s;

      ଯଦି (r == p->ବାମ)
	{
	  ଯଦି (p->balance == 0)
	    p->balance = -1;
	  ଅନ୍ୟଥା ଯଦି (p->balance < 0)
	    {
	      ଯଦି (r->balance < 0)
		{
		  /* L rotation.  */
		  p->ବାମ = r->ଡାହାଣ;
		  ଯଦି (p->ବାମ)
		    p->ବାମ->parent = p;
		  r->ଡାହାଣ = p;

		  p->balance = 0;
		  r->balance = 0;

		  s = p->parent;
		  p->parent = r;
		  r->parent = s;
		  ଯଦି (s)
		    {
		      ଯଦି (s->ବାମ == p)
			s->ବାମ = r;
		      ଅନ୍ୟଥା
			s->ଡାହାଣ = r;
		    }
		  ଅନ୍ୟଥା
		    constructor_pending_elts = r;
		}
	      ଅନ୍ୟଥା
		{
		  /* LR rotation.  */
		  ସଂରଚନା init_ଗଣ୍ଠି *t = r->ଡାହାଣ;

		  r->ଡାହାଣ = t->ବାମ;
		  ଯଦି (r->ଡାହାଣ)
		    r->ଡାହାଣ->parent = r;
		  t->ବାମ = r;

		  p->ବାମ = t->ଡାହାଣ;
		  ଯଦି (p->ବାମ)
		    p->ବାମ->parent = p;
		  t->ଡାହାଣ = p;

		  p->balance = t->balance < 0;
		  r->balance = -(t->balance > 0);
		  t->balance = 0;

		  s = p->parent;
		  p->parent = t;
		  r->parent = t;
		  t->parent = s;
		  ଯଦି (s)
		    {
		      ଯଦି (s->ବାମ == p)
			s->ବାମ = t;
		      ଅନ୍ୟଥା
			s->ଡାହାଣ = t;
		    }
		  ଅନ୍ୟଥା
		    constructor_pending_elts = t;
		}
	      ଭାଙ୍ଗ;
	    }
	  ଅନ୍ୟଥା
	    {
	      /* p->balance == +1; growth of left side balances the node.  */
	      p->balance = 0;
	      ଭାଙ୍ଗ;
	    }
	}
      ଅନ୍ୟଥା /* r == p->right */
	{
	  ଯଦି (p->balance == 0)
	    /* Growth propagation from right side.  */
	    p->balance++;
	  ଅନ୍ୟଥା ଯଦି (p->balance > 0)
	    {
	      ଯଦି (r->balance > 0)
		{
		  /* R rotation.  */
		  p->ଡାହାଣ = r->ବାମ;
		  ଯଦି (p->ଡାହାଣ)
		    p->ଡାହାଣ->parent = p;
		  r->ବାମ = p;

		  p->balance = 0;
		  r->balance = 0;

		  s = p->parent;
		  p->parent = r;
		  r->parent = s;
		  ଯଦି (s)
		    {
		      ଯଦି (s->ବାମ == p)
			s->ବାମ = r;
		      ଅନ୍ୟଥା
			s->ଡାହାଣ = r;
		    }
		  ଅନ୍ୟଥା
		    constructor_pending_elts = r;
		}
	      ଅନ୍ୟଥା /* r->balance == -1 */
		{
		  /* RL rotation */
		  ସଂରଚନା init_ଗଣ୍ଠି *t = r->ବାମ;

		  r->ବାମ = t->ଡାହାଣ;
		  ଯଦି (r->ବାମ)
		    r->ବାମ->parent = r;
		  t->ଡାହାଣ = r;

		  p->ଡାହାଣ = t->ବାମ;
		  ଯଦି (p->ଡାହାଣ)
		    p->ଡାହାଣ->parent = p;
		  t->ବାମ = p;

		  r->balance = (t->balance < 0);
		  p->balance = -(t->balance > 0);
		  t->balance = 0;

		  s = p->parent;
		  p->parent = t;
		  r->parent = t;
		  t->parent = s;
		  ଯଦି (s)
		    {
		      ଯଦି (s->ବାମ == p)
			s->ବାମ = t;
		      ଅନ୍ୟଥା
			s->ଡାହାଣ = t;
		    }
		  ଅନ୍ୟଥା
		    constructor_pending_elts = t;
		}
	      ଭାଙ୍ଗ;
	    }
	  ଅନ୍ୟଥା
	    {
	      /* p->balance == -1; growth of right side balances the node.  */
	      p->balance = 0;
	      ଭାଙ୍ଗ;
	    }
	}

      r = p;
      p = p->parent;
    }
}

/* Build AVL tree from a sorted chain.  */

ସ୍ଥିର ଶୂନ୍ୟ
set_nonincremental_init (ସଂରଚନା obstack * braced_init_obstack)
{
  unsigned HOST_WIDE_INT ix;
  ବୃକ୍ଷ index, ମୂଲ୍ୟ;

  ଯଦି (ବୃକ୍ଷ_CODE (constructor_type) != RECORD_TYPE
      && ବୃକ୍ଷ_CODE (constructor_type) != ARRAY_TYPE)
    ଫେରନ୍ତୁ;

  FOR_EACH_CONSTRUCTOR_ELT (constructor_elements, ix, index, ମୂଲ୍ୟ)
    add_pending_init (ନିବେଶ_location, index, ମୂଲ୍ୟ, NULL_ବୃକ୍ଷ, ସତ୍ୟ,
		      braced_init_obstack);
  constructor_elements = ଖାଲି;
  ଯଦି (ବୃକ୍ଷ_CODE (constructor_type) == RECORD_TYPE)
    {
      constructor_unfilled_fields = TYPE_FIELDS (constructor_type);
      /* Skip any nameless bit fields at the beginning.  */
      ଯେତେବେଳେ (constructor_unfilled_fields != NULL_ବୃକ୍ଷ
	     && DECL_UNNAMED_BIT_FIELD (constructor_unfilled_fields))
	constructor_unfilled_fields = ବୃକ୍ଷ_CHAIN (constructor_unfilled_fields);

    }
  ଅନ୍ୟଥା ଯଦି (ବୃକ୍ଷ_CODE (constructor_type) == ARRAY_TYPE)
    {
      ଯଦି (TYPE_DOMAIN (constructor_type))
	constructor_unfilled_index
	  = convert (bitsizetype,
		     TYPE_MIN_ମୂଲ୍ୟ (TYPE_DOMAIN (constructor_type)));
      ଅନ୍ୟଥା
	constructor_unfilled_index = bitsize_zero_ଗଣ୍ଠି;
    }
  constructor_incremental = 0;
}

/* Build AVL tree from a string constant.  */

ସ୍ଥିର ଶୂନ୍ୟ
set_nonincremental_init_from_string (ବୃକ୍ଷ str,
				     ସଂରଚନା obstack * braced_init_obstack)
{
  ବୃକ୍ଷ ମୂଲ୍ୟ, purpose, type;
  HOST_WIDE_INT val[2];
  ଅଚଳ ଅକ୍ଷର *p, *end;
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା byte, wchar_bytes, charwidth, bitpos;

  gcc_assert (ବୃକ୍ଷ_CODE (constructor_type) == ARRAY_TYPE);

  wchar_bytes = TYPE_PRECISION (ବୃକ୍ଷ_TYPE (ବୃକ୍ଷ_TYPE (str))) / BITS_PER_UNIT;
  charwidth = TYPE_PRECISION (char_type_ଗଣ୍ଠି);
  gcc_assert ((size_t) wchar_bytes * charwidth
	      <= ARRAY_SIZE (val) * HOST_BITS_PER_WIDE_INT);
  type = ବୃକ୍ଷ_TYPE (constructor_type);
  p = ବୃକ୍ଷ_STRING_POINTER (str);
  end = p + ବୃକ୍ଷ_STRING_LENGTH (str);

  ପାଇଁ (purpose = bitsize_zero_ଗଣ୍ଠି;
       p < end
       && !(constructor_max_index
	    && ବୃକ୍ଷ_int_cst_lt (constructor_max_index, purpose));
       purpose = size_binop (PLUS_ପଦସମଷ୍ଟି, purpose, bitsize_one_ଗଣ୍ଠି))
    {
      ଯଦି (wchar_bytes == 1)
	{
	  val[0] = (unsigned ଅକ୍ଷର) *p++;
	  val[1] = 0;
	}
      ଅନ୍ୟଥା
	{
	  val[1] = 0;
	  val[0] = 0;
	  ପାଇଁ (byte = 0; byte < wchar_bytes; byte++)
	    {
	      ଯଦି (BYTES_BIG_ENDIAN)
		bitpos = (wchar_bytes - byte - 1) * charwidth;
	      ଅନ୍ୟଥା
		bitpos = byte * charwidth;
	      val[bitpos / HOST_BITS_PER_WIDE_INT]
		|= ((unsigned HOST_WIDE_INT) ((unsigned ଅକ୍ଷର) *p++))
		   << (bitpos % HOST_BITS_PER_WIDE_INT);
	    }
	}

      ଯଦି (!TYPE_UNSIGNED (type))
	{
	  bitpos = ((wchar_bytes - 1) * charwidth) + HOST_BITS_PER_CHAR;
	  ଯଦି (bitpos < HOST_BITS_PER_WIDE_INT)
	    {
	      ଯଦି (val[0] & (HOST_WIDE_INT_1 << (bitpos - 1)))
		{
		  val[0] |= HOST_WIDE_INT_M1U << bitpos;
		  val[1] = -1;
		}
	    }
	  ଅନ୍ୟଥା ଯଦି (bitpos == HOST_BITS_PER_WIDE_INT)
	    {
	      ଯଦି (val[0] < 0)
		val[1] = -1;
	    }
	  ଅନ୍ୟଥା ଯଦି (val[1] & (HOST_WIDE_INT_1
			     << (bitpos - 1 - HOST_BITS_PER_WIDE_INT)))
	    val[1] |= HOST_WIDE_INT_M1U << (bitpos - HOST_BITS_PER_WIDE_INT);
	}

      ମୂଲ୍ୟ = wide_int_to_ବୃକ୍ଷ (type,
				wide_int::from_array (val, 2,
						      HOST_BITS_PER_WIDE_INT * 2));
      add_pending_init (ନିବେଶ_location, purpose, ମୂଲ୍ୟ, NULL_ବୃକ୍ଷ, ସତ୍ୟ,
                        braced_init_obstack);
    }

  constructor_incremental = 0;
}

/* Return value of FIELD in pending initializer or NULL_TREE if the field was
   not initialized yet.  */

ସ୍ଥିର ବୃକ୍ଷ
find_init_member (ବୃକ୍ଷ field, ସଂରଚନା obstack * braced_init_obstack)
{
  ସଂରଚନା init_ଗଣ୍ଠି *p;

  ଯଦି (ବୃକ୍ଷ_CODE (constructor_type) == ARRAY_TYPE)
    {
      ଯଦି (constructor_incremental
	  && ବୃକ୍ଷ_int_cst_lt (field, constructor_unfilled_index))
	set_nonincremental_init (braced_init_obstack);

      p = constructor_pending_elts;
      ଯେତେବେଳେ (p)
	{
	  ଯଦି (ବୃକ୍ଷ_int_cst_lt (field, p->purpose))
	    p = p->ବାମ;
	  ଅନ୍ୟଥା ଯଦି (ବୃକ୍ଷ_int_cst_lt (p->purpose, field))
	    p = p->ଡାହାଣ;
	  ଅନ୍ୟଥା
	    ଫେରନ୍ତୁ p->ମୂଲ୍ୟ;
	}
    }
  ଅନ୍ୟଥା ଯଦି (ବୃକ୍ଷ_CODE (constructor_type) == RECORD_TYPE)
    {
      ବୃକ୍ଷ bitpos = bit_position (field);

      ଯଦି (constructor_incremental
	  && (!constructor_unfilled_fields
	      || ବୃକ୍ଷ_int_cst_lt (bitpos,
				  bit_position (constructor_unfilled_fields))))
	set_nonincremental_init (braced_init_obstack);

      p = constructor_pending_elts;
      ଯେତେବେଳେ (p)
	{
	  ଯଦି (field == p->purpose)
	    ଫେରନ୍ତୁ p->ମୂଲ୍ୟ;
	  ଅନ୍ୟଥା ଯଦି (ବୃକ୍ଷ_int_cst_lt (bitpos, bit_position (p->purpose)))
	    p = p->ବାମ;
	  ଅନ୍ୟଥା
	    p = p->ଡାହାଣ;
	}
    }
  ଅନ୍ୟଥା ଯଦି (ବୃକ୍ଷ_CODE (constructor_type) == UNION_TYPE)
    {
      ଯଦି (!vec_safe_is_empty (constructor_elements)
	  && (constructor_elements->last ().index == field))
	ଫେରନ୍ତୁ constructor_elements->last ().ମୂଲ୍ୟ;
    }
  ଫେରନ୍ତୁ NULL_ବୃକ୍ଷ;
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

ସ୍ଥିର ଶୂନ୍ୟ
output_init_element (location_t loc, ବୃକ୍ଷ ମୂଲ୍ୟ, ବୃକ୍ଷ origtype,
		     ତାର୍କିକ strict_string, ବୃକ୍ଷ type, ବୃକ୍ଷ field, ତାର୍କିକ pending,
		     ତାର୍କିକ implicit, ସଂରଚନା obstack * braced_init_obstack)
{
  ବୃକ୍ଷ semantic_type = NULL_ବୃକ୍ଷ;
  ତାର୍କିକ maybe_const = ସତ୍ୟ;
  ତାର୍କିକ npc, int_const_ପଦସମଷ୍ଟି, arith_const_ପଦସମଷ୍ଟି;

  ଯଦି (type == error_mark_ଗଣ୍ଠି || ମୂଲ୍ୟ == error_mark_ଗଣ୍ଠି)
    {
      constructor_erroneous = 1;
      ଫେରନ୍ତୁ;
    }
  ଯଦି (ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (ମୂଲ୍ୟ)) == ARRAY_TYPE
      && (ବୃକ୍ଷ_CODE (ମୂଲ୍ୟ) == STRING_CST
	  || ବୃକ୍ଷ_CODE (ମୂଲ୍ୟ) == COMPOUND_LITERAL_ପଦସମଷ୍ଟି)
      && !(ବୃକ୍ଷ_CODE (ମୂଲ୍ୟ) == STRING_CST
	   && ବୃକ୍ଷ_CODE (type) == ARRAY_TYPE
	   && INTEGRAL_TYPE_P (ବୃକ୍ଷ_TYPE (type)))
      && !comptypes (TYPE_MAIN_VARIANT (ବୃକ୍ଷ_TYPE (ମୂଲ୍ୟ)),
		     TYPE_MAIN_VARIANT (type)))
    ମୂଲ୍ୟ = array_to_pointer_conversion (ନିବେଶ_location, ମୂଲ୍ୟ);

  ଯଦି (ବୃକ୍ଷ_CODE (ମୂଲ୍ୟ) == COMPOUND_LITERAL_ପଦସମଷ୍ଟି
      && require_constant_ମୂଲ୍ୟ && pending)
    {
      /* As an extension, allow initializing objects with static storage
	 duration with compound literals (which are then treated just as
	 the brace enclosed list they contain).  */
      ଯଦି (flag_isoc99)
	pedwarn_init (loc, OPT_Wpedantic, "initializer element is not "
		      "constant");
      ବୃକ୍ଷ decl = COMPOUND_LITERAL_ପଦସମଷ୍ଟି_DECL (ମୂଲ୍ୟ);
      ମୂଲ୍ୟ = DECL_INITIAL (decl);
    }

  npc = null_pointer_constant_p (ମୂଲ୍ୟ);
  int_const_ପଦସମଷ୍ଟି = (ବୃକ୍ଷ_CODE (ମୂଲ୍ୟ) == INTEGER_CST
		    && !ବୃକ୍ଷ_OVERFLOW (ମୂଲ୍ୟ)
		    && INTEGRAL_TYPE_P (ବୃକ୍ଷ_TYPE (ମୂଲ୍ୟ)));
  /* Not fully determined before folding.  */
  arith_const_ପଦସମଷ୍ଟି = ସତ୍ୟ;
  ଯଦି (ବୃକ୍ଷ_CODE (ମୂଲ୍ୟ) == EXCESS_PRECISION_ପଦସମଷ୍ଟି)
    {
      semantic_type = ବୃକ୍ଷ_TYPE (ମୂଲ୍ୟ);
      ମୂଲ୍ୟ = ବୃକ୍ଷ_OPERAND (ମୂଲ୍ୟ, 0);
    }
  ମୂଲ୍ୟ = c_fully_fold (ମୂଲ୍ୟ, require_constant_ମୂଲ୍ୟ, &maybe_const);
  /* TODO: this may not detect all cases of expressions folding to
     constants that are not arithmetic constant expressions.  */
  ଯଦି (!maybe_const)
    arith_const_ପଦସମଷ୍ଟି = ମିଥ୍ୟା;
  ଅନ୍ୟଥା ଯଦି (!INTEGRAL_TYPE_P (ବୃକ୍ଷ_TYPE (ମୂଲ୍ୟ))
	   && ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (ମୂଲ୍ୟ)) != REAL_TYPE
	   && ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (ମୂଲ୍ୟ)) != COMPLEX_TYPE)
    arith_const_ପଦସମଷ୍ଟି = ମିଥ୍ୟା;
  ଅନ୍ୟଥା ଯଦି (ବୃକ୍ଷ_CODE (ମୂଲ୍ୟ) != INTEGER_CST
	   && ବୃକ୍ଷ_CODE (ମୂଲ୍ୟ) != REAL_CST
	   && ବୃକ୍ଷ_CODE (ମୂଲ୍ୟ) != COMPLEX_CST
	   && ବୃକ୍ଷ_CODE (ମୂଲ୍ୟ) != RAW_DATA_CST)
    arith_const_ପଦସମଷ୍ଟି = ମିଥ୍ୟା;
  ଅନ୍ୟଥା ଯଦି (ବୃକ୍ଷ_OVERFLOW (ମୂଲ୍ୟ))
    arith_const_ପଦସମଷ୍ଟି = ମିଥ୍ୟା;

  ଯଦି (ମୂଲ୍ୟ == error_mark_ଗଣ୍ଠି)
    constructor_erroneous = 1;
  ଅନ୍ୟଥା ଯଦି (!ବୃକ୍ଷ_CONSTANT (ମୂଲ୍ୟ))
    constructor_constant = 0;
  ଅନ୍ୟଥା ଯଦି (!initializer_constant_valid_p (ମୂଲ୍ୟ,
					  ବୃକ୍ଷ_TYPE (ମୂଲ୍ୟ),
					  AGGREGATE_TYPE_P (constructor_type)
					  && TYPE_REVERSE_STORAGE_ORDER
					     (constructor_type))
	   || (RECORD_OR_UNION_TYPE_P (constructor_type)
	       && DECL_C_BIT_FIELD (field)
	       && ବୃକ୍ଷ_CODE (ମୂଲ୍ୟ) != INTEGER_CST))
    constructor_simple = 0;
  ଯଦି (!maybe_const)
    constructor_nonconst = 1;

  /* Digest the initializer and issue any errors about incompatible
     types before issuing errors about non-constant initializers.  */
  ବୃକ୍ଷ new_ମୂଲ୍ୟ = ମୂଲ୍ୟ;
  ଯଦି (semantic_type)
    new_ମୂଲ୍ୟ = build1 (EXCESS_PRECISION_ପଦସମଷ୍ଟି, semantic_type, ମୂଲ୍ୟ);
  /* In the case of braces around a scalar initializer, the result of
     this initializer processing goes through digest_init again at the
     outer level.  In the case of a constexpr initializer for a
     pointer, avoid converting a null pointer constant to something
     that is not a null pointer constant to avoid a spurious error
     from that second processing.  */
  ଯଦି (!require_constexpr_ମୂଲ୍ୟ
      || !npc
      || ବୃକ୍ଷ_CODE (constructor_type) != POINTER_TYPE)
    new_ମୂଲ୍ୟ = digest_init (loc,
			     RECORD_OR_UNION_TYPE_P (constructor_type)
			     ? field : constructor_fields
			     ? constructor_fields : constructor_decl,
			     type, new_ମୂଲ୍ୟ, origtype, npc,
			     int_const_ପଦସମଷ୍ଟି, arith_const_ପଦସମଷ୍ଟି, strict_string,
			     require_constant_ମୂଲ୍ୟ, require_constexpr_ମୂଲ୍ୟ);
  ଯଦି (new_ମୂଲ୍ୟ == error_mark_ଗଣ୍ଠି)
    {
      constructor_erroneous = 1;
      ଫେରନ୍ତୁ;
    }
  ଯଦି (require_constant_ମୂଲ୍ୟ || require_constant_elements)
    constant_expression_warning (new_ମୂଲ୍ୟ);

  /* Proceed to check the constness of the original initializer.  */
  ଯଦି (!initializer_constant_valid_p (ମୂଲ୍ୟ, ବୃକ୍ଷ_TYPE (ମୂଲ୍ୟ)))
    {
      ଯଦି (require_constant_ମୂଲ୍ୟ)
	{
	  error_init (loc, "initializer element is not constant");
	  ମୂଲ୍ୟ = error_mark_ଗଣ୍ଠି;
	}
      ଅନ୍ୟଥା ଯଦି (require_constant_elements)
	pedwarn (loc, OPT_Wpedantic,
		 "initializer element is not computable at load time");
    }
  ଅନ୍ୟଥା ଯଦି (!maybe_const
	   && (require_constant_ମୂଲ୍ୟ || require_constant_elements))
    pedwarn_init (loc, OPT_Wpedantic,
		  "initializer element is not a constant expression");
  /* digest_init has already carried out the additional checks
     required for 'constexpr' initializers (using the information
     passed to it about whether the original initializer was certain
     kinds of constant expression), so that check does not need to be
     repeated here.  */

  /* Issue -Wc++-compat warnings about initializing a bitfield with
     enum type.  */
  ଯଦି (warn_cxx_compat
      && field != NULL_ବୃକ୍ଷ
      && ବୃକ୍ଷ_CODE (field) == FIELD_DECL
      && DECL_BIT_FIELD_TYPE (field) != NULL_ବୃକ୍ଷ
      && (TYPE_MAIN_VARIANT (DECL_BIT_FIELD_TYPE (field))
	  != TYPE_MAIN_VARIANT (type))
      && ବୃକ୍ଷ_CODE (DECL_BIT_FIELD_TYPE (field)) == ENUMERAL_TYPE)
    {
      ବୃକ୍ଷ checktype = origtype != NULL_ବୃକ୍ଷ ? origtype : ବୃକ୍ଷ_TYPE (ମୂଲ୍ୟ);
      ଯଦି (checktype != error_mark_ଗଣ୍ଠି
	  && (TYPE_MAIN_VARIANT (checktype)
	      != TYPE_MAIN_VARIANT (DECL_BIT_FIELD_TYPE (field))))
	warning_init (loc, OPT_Wc___compat,
		      "enum conversion in initialization is invalid in C++");
    }

  /* If this field is empty and does not have side effects (and is not at
     the end of structure), don't do anything other than checking the
     initializer.  */
  ଯଦି (field
      && (ବୃକ୍ଷ_TYPE (field) == error_mark_ଗଣ୍ଠି
	  || (COMPLETE_TYPE_P (ବୃକ୍ଷ_TYPE (field))
	      && integer_zerop (TYPE_SIZE (ବୃକ୍ଷ_TYPE (field)))
	      && !ବୃକ୍ଷ_SIDE_EFFECTS (new_ମୂଲ୍ୟ)
	      && (ବୃକ୍ଷ_CODE (constructor_type) == ARRAY_TYPE
		  || DECL_CHAIN (field)))))
    ଫେରନ୍ତୁ;

  /* Finally, set VALUE to the initializer value digested above.  */
  ମୂଲ୍ୟ = new_ମୂଲ୍ୟ;

  /* If this element doesn't come next in sequence,
     put it on constructor_pending_elts.  */
  ଯଦି (ବୃକ୍ଷ_CODE (constructor_type) == ARRAY_TYPE
      && (!constructor_incremental
	  || !ବୃକ୍ଷ_int_cst_equal (field, constructor_unfilled_index)
	  || (ବୃକ୍ଷ_CODE (ମୂଲ୍ୟ) == RAW_DATA_CST
	      && constructor_pending_elts
	      && pending)))
    {
      ଯଦି (constructor_incremental
	  && (ବୃକ୍ଷ_int_cst_lt (field, constructor_unfilled_index)
	      || (ବୃକ୍ଷ_CODE (ମୂଲ୍ୟ) == RAW_DATA_CST
		  && constructor_pending_elts
		  && pending)))
	set_nonincremental_init (braced_init_obstack);

      add_pending_init (loc, field, ମୂଲ୍ୟ, origtype, implicit,
			braced_init_obstack);
      ଫେରନ୍ତୁ;
    }
  ଅନ୍ୟଥା ଯଦି (ବୃକ୍ଷ_CODE (constructor_type) == RECORD_TYPE
	   && (!constructor_incremental
	       || field != constructor_unfilled_fields))
    {
      /* We do this for records but not for unions.  In a union,
	 no matter which field is specified, it can be initialized
	 right away since it starts at the beginning of the union.  */
      ଯଦି (constructor_incremental)
	{
	  ଯଦି (!constructor_unfilled_fields)
	    set_nonincremental_init (braced_init_obstack);
	  ଅନ୍ୟଥା
	    {
	      ବୃକ୍ଷ bitpos, unfillpos;

	      bitpos = bit_position (field);
	      unfillpos = bit_position (constructor_unfilled_fields);

	      ଯଦି (ବୃକ୍ଷ_int_cst_lt (bitpos, unfillpos))
		set_nonincremental_init (braced_init_obstack);
	    }
	}

      add_pending_init (loc, field, ମୂଲ୍ୟ, origtype, implicit,
			braced_init_obstack);
      ଫେରନ୍ତୁ;
    }
  ଅନ୍ୟଥା ଯଦି (ବୃକ୍ଷ_CODE (constructor_type) == UNION_TYPE
	   && !vec_safe_is_empty (constructor_elements))
    {
      ଯଦି (!implicit)
	{
	  ଯଦି (ବୃକ୍ଷ_SIDE_EFFECTS (constructor_elements->last ().ମୂଲ୍ୟ))
	    warning_init (loc, OPT_Woverride_init_side_effects,
			  "initialized field with side-effects overwritten");
	  ଅନ୍ୟଥା ଯଦି (warn_override_init)
	    warning_init (loc, OPT_Woverride_init,
			  "initialized field overwritten");
	}

      /* We can have just one union field set.  */
      constructor_elements = ଖାଲି;
    }

  /* Otherwise, output this element either to
     constructor_elements or to the assembler file.  */

  constructor_elt celt = {field, ମୂଲ୍ୟ};
  vec_safe_ଠେଲ (constructor_elements, celt);

  /* Advance the variable that indicates sequential elements output.  */
  ଯଦି (ବୃକ୍ଷ_CODE (constructor_type) == ARRAY_TYPE)
    {
      ବୃକ୍ଷ inc = bitsize_one_ଗଣ୍ଠି;
      ଯଦି (ମୂଲ୍ୟ && ବୃକ୍ଷ_CODE (ମୂଲ୍ୟ) == RAW_DATA_CST)
	inc = bitsize_int (RAW_DATA_LENGTH (ମୂଲ୍ୟ));
      constructor_unfilled_index
	= size_binop_loc (ନିବେଶ_location, PLUS_ପଦସମଷ୍ଟି,
			  constructor_unfilled_index, inc);
    }
  ଅନ୍ୟଥା ଯଦି (ବୃକ୍ଷ_CODE (constructor_type) == RECORD_TYPE)
    {
      constructor_unfilled_fields
	= DECL_CHAIN (constructor_unfilled_fields);

      /* Skip any nameless bit fields.  */
      ଯେତେବେଳେ (constructor_unfilled_fields != NULL_ବୃକ୍ଷ
	     && DECL_UNNAMED_BIT_FIELD (constructor_unfilled_fields))
	constructor_unfilled_fields
	  = DECL_CHAIN (constructor_unfilled_fields);
    }
  ଅନ୍ୟଥା ଯଦି (ବୃକ୍ଷ_CODE (constructor_type) == UNION_TYPE)
    constructor_unfilled_fields = NULL_ବୃକ୍ଷ;

  /* Now output any pending elements which have become next.  */
  ଯଦି (pending)
    output_pending_init_elements (0, braced_init_obstack);
}

/* For two FIELD_DECLs in the same chain, return -1 if field1
   comes before field2, 1 if field1 comes after field2 and
   0 if field1 == field2.  */

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା
init_field_decl_cmp (ବୃକ୍ଷ field1, ବୃକ୍ଷ field2)
{
  ଯଦି (field1 == field2)
    ଫେରନ୍ତୁ 0;

  ବୃକ୍ଷ bitpos1 = bit_position (field1);
  ବୃକ୍ଷ bitpos2 = bit_position (field2);
  ଯଦି (ବୃକ୍ଷ_int_cst_equal (bitpos1, bitpos2))
    {
      /* If one of the fields has non-zero bitsize, then that
	 field must be the last one in a sequence of zero
	 sized fields, fields after it will have bigger
	 bit_position.  */
      ଯଦି (ବୃକ୍ଷ_TYPE (field1) != error_mark_ଗଣ୍ଠି
	  && COMPLETE_TYPE_P (ବୃକ୍ଷ_TYPE (field1))
	  && integer_nonzerop (ବୃକ୍ଷ_TYPE (field1)))
	ଫେରନ୍ତୁ 1;
      ଯଦି (ବୃକ୍ଷ_TYPE (field2) != error_mark_ଗଣ୍ଠି
	  && COMPLETE_TYPE_P (ବୃକ୍ଷ_TYPE (field2))
	  && integer_nonzerop (ବୃକ୍ଷ_TYPE (field2)))
	ଫେରନ୍ତୁ -1;
      /* Otherwise, fallback to DECL_CHAIN walk to find out
	 which field comes earlier.  Walk chains of both
	 fields, so that if field1 and field2 are close to each
	 other in either order, it is found soon even for large
	 sequences of zero sized fields.  */
      ବୃକ୍ଷ f1 = field1, f2 = field2;
      ଯେତେବେଳେ (1)
	{
	  f1 = DECL_CHAIN (f1);
	  f2 = DECL_CHAIN (f2);
	  ଯଦି (f1 == NULL_ବୃକ୍ଷ)
	    {
	      gcc_assert (f2);
	      ଫେରନ୍ତୁ 1;
	    }
	  ଯଦି (f2 == NULL_ବୃକ୍ଷ)
	    ଫେରନ୍ତୁ -1;
	  ଯଦି (f1 == field2)
	    ଫେରନ୍ତୁ -1;
	  ଯଦି (f2 == field1)
	    ଫେରନ୍ତୁ 1;
	  ଯଦି (!ବୃକ୍ଷ_int_cst_equal (bit_position (f1), bitpos1))
	    ଫେରନ୍ତୁ 1;
	  ଯଦି (!ବୃକ୍ଷ_int_cst_equal (bit_position (f2), bitpos1))
	    ଫେରନ୍ତୁ -1;
	}
    }
  ଅନ୍ୟଥା ଯଦି (ବୃକ୍ଷ_int_cst_lt (bitpos1, bitpos2))
    ଫେରନ୍ତୁ -1;
  ଅନ୍ୟଥା
    ଫେରନ୍ତୁ 1;
}

/* Output any pending elements which have become next.
   As we output elements, constructor_unfilled_{fields,index}
   advances, which may cause other elements to become next;
   if so, they too are output.

   If ALL is 0, we return when there are
   no more pending elements to output now.

   If ALL is 1, we output space as necessary so that
   we can output all the pending elements.  */
ସ୍ଥିର ଶୂନ୍ୟ
output_pending_init_elements (ପୂର୍ଣ୍ଣସଂଖ୍ୟା all, ସଂରଚନା obstack * braced_init_obstack)
{
  ସଂରଚନା init_ଗଣ୍ଠି *elt = constructor_pending_elts;
  ବୃକ୍ଷ next;

 retry:

  /* Look through the whole pending tree.
     If we find an element that should be output now,
     output it.  Otherwise, set NEXT to the element
     that comes first among those still pending.  */

  next = NULL_ବୃକ୍ଷ;
  ଯେତେବେଳେ (elt)
    {
      ଯଦି (ବୃକ୍ଷ_CODE (constructor_type) == ARRAY_TYPE)
	{
	  ଯଦି (ବୃକ୍ଷ_int_cst_equal (elt->purpose,
				  constructor_unfilled_index))
	    output_init_element (ନିବେଶ_location, elt->ମୂଲ୍ୟ, elt->origtype,
				 ସତ୍ୟ, ବୃକ୍ଷ_TYPE (constructor_type),
				 constructor_unfilled_index, ମିଥ୍ୟା, ମିଥ୍ୟା,
				 braced_init_obstack);
	  ଅନ୍ୟଥା ଯଦି (ବୃକ୍ଷ_int_cst_lt (constructor_unfilled_index,
				    elt->purpose))
	    {
	      /* Advance to the next smaller node.  */
	      ଯଦି (elt->ବାମ)
		elt = elt->ବାମ;
	      ଅନ୍ୟଥା
		{
		  /* We have reached the smallest node bigger than the
		     current unfilled index.  Fill the space first.  */
		  next = elt->purpose;
		  ଭାଙ୍ଗ;
		}
	    }
	  ଅନ୍ୟଥା
	    {
	      /* Advance to the next bigger node.  */
	      ଯଦି (elt->ଡାହାଣ)
		elt = elt->ଡାହାଣ;
	      ଅନ୍ୟଥା
		{
		  /* We have reached the biggest node in a subtree.  Find
		     the parent of it, which is the next bigger node.  */
		  ଯେତେବେଳେ (elt->parent && elt->parent->ଡାହାଣ == elt)
		    elt = elt->parent;
		  elt = elt->parent;
		  ଯଦି (elt && ବୃକ୍ଷ_int_cst_lt (constructor_unfilled_index,
					      elt->purpose))
		    {
		      next = elt->purpose;
		      ଭାଙ୍ଗ;
		    }
		}
	    }
	}
      ଅନ୍ୟଥା ଯଦି (RECORD_OR_UNION_TYPE_P (constructor_type))
	{
	  /* If the current record is complete we are done.  */
	  ଯଦି (constructor_unfilled_fields == NULL_ବୃକ୍ଷ)
	    ଭାଙ୍ଗ;

	  ପୂର୍ଣ୍ଣସଂଖ୍ୟା cmp = init_field_decl_cmp (constructor_unfilled_fields,
					 elt->purpose);
	  ଯଦି (cmp == 0)
	    output_init_element (ନିବେଶ_location, elt->ମୂଲ୍ୟ, elt->origtype,
				 ସତ୍ୟ, ବୃକ୍ଷ_TYPE (elt->purpose),
				 elt->purpose, ମିଥ୍ୟା, ମିଥ୍ୟା,
				 braced_init_obstack);
	  ଅନ୍ୟଥା ଯଦି (cmp < 0)
	    {
	      /* Advance to the next smaller node.  */
	      ଯଦି (elt->ବାମ)
		elt = elt->ବାମ;
	      ଅନ୍ୟଥା
		{
		  /* We have reached the smallest node bigger than the
		     current unfilled field.  Fill the space first.  */
		  next = elt->purpose;
		  ଭାଙ୍ଗ;
		}
	    }
	  ଅନ୍ୟଥା
	    {
	      /* Advance to the next bigger node.  */
	      ଯଦି (elt->ଡାହାଣ)
		elt = elt->ଡାହାଣ;
	      ଅନ୍ୟଥା
		{
		  /* We have reached the biggest node in a subtree.  Find
		     the parent of it, which is the next bigger node.  */
		  ଯେତେବେଳେ (elt->parent && elt->parent->ଡାହାଣ == elt)
		    elt = elt->parent;
		  elt = elt->parent;
		  ଯଦି (elt
		      && init_field_decl_cmp (constructor_unfilled_fields,
					      elt->purpose) < 0)
		    {
		      next = elt->purpose;
		      ଭାଙ୍ଗ;
		    }
		}
	    }
	}
    }

  /* Ordinarily return, but not if we want to output all
     and there are elements left.  */
  ଯଦି (!(all && next != NULL_ବୃକ୍ଷ))
    ଫେରନ୍ତୁ;

  /* If it's not incremental, just skip over the gap, so that after
     jumping to retry we will output the next successive element.  */
  ଯଦି (RECORD_OR_UNION_TYPE_P (constructor_type))
    constructor_unfilled_fields = next;
  ଅନ୍ୟଥା ଯଦି (ବୃକ୍ଷ_CODE (constructor_type) == ARRAY_TYPE)
    constructor_unfilled_index = next;

  /* ELT now points to the node in the pending tree with the next
     initializer to output.  */
  ଯାଅ retry;
}

/* Expression VALUE coincides with the start of type TYPE in a braced
   initializer.  Return true if we should treat VALUE as initializing
   the first element of TYPE, false if we should treat it as initializing
   TYPE as a whole.

   If the initializer is clearly invalid, the question becomes:
   which choice gives the best error message?  */

ସ୍ଥିର ତାର୍କିକ
initialize_elementwise_p (ବୃକ୍ଷ type, ବୃକ୍ଷ ମୂଲ୍ୟ)
{
  ଯଦି (type == error_mark_ଗଣ୍ଠି || ମୂଲ୍ୟ == error_mark_ଗଣ୍ଠି)
    ଫେରନ୍ତୁ ମିଥ୍ୟା;

  gcc_checking_assert (TYPE_MAIN_VARIANT (type) == type);

  ବୃକ୍ଷ ମୂଲ୍ୟ_type = ବୃକ୍ଷ_TYPE (ମୂଲ୍ୟ);
  ଯଦି (ମୂଲ୍ୟ_type == error_mark_ଗଣ୍ଠି)
    ଫେରନ୍ତୁ ମିଥ୍ୟା;

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
  ଯଦି (gnu_vector_type_p (type))
    ଫେରନ୍ତୁ !VECTOR_TYPE_P (ମୂଲ୍ୟ_type);

  ଯଦି (AGGREGATE_TYPE_P (type))
    ଫେରନ୍ତୁ !comptypes (type, TYPE_MAIN_VARIANT (ମୂଲ୍ୟ_type));

  ଫେରନ୍ତୁ ମିଥ୍ୟା;
}

/* Helper function for process_init_element.  Split first element of
   RAW_DATA_CST and save the rest to *RAW_DATA.  */

ସ୍ଥିର ଧାଡ଼ିଭିତରେ ବୃକ୍ଷ
maybe_split_raw_data (ବୃକ୍ଷ ମୂଲ୍ୟ, ବୃକ୍ଷ *raw_data)
{
  ଯଦି (ମୂଲ୍ୟ == NULL_ବୃକ୍ଷ || ବୃକ୍ଷ_CODE (ମୂଲ୍ୟ) != RAW_DATA_CST)
    ଫେରନ୍ତୁ ମୂଲ୍ୟ;
  *raw_data = ମୂଲ୍ୟ;
  ମୂଲ୍ୟ = build_int_cst (integer_type_ଗଣ୍ଠି,
			 RAW_DATA_UCHAR_ELT (*raw_data, 0));
  ++RAW_DATA_POINTER (*raw_data);
  --RAW_DATA_LENGTH (*raw_data);
  ଫେରନ୍ତୁ ମୂଲ୍ୟ;
}

/* Return non-zero if c_parser_initval should attempt to optimize
   large initializers into RAW_DATA_CST.  In that case return how
   many elements to optimize at most.  */

unsigned
c_maybe_optimize_large_byte_initializer (ଶୂନ୍ୟ)
{
  ଯଦି (!constructor_type
      || ବୃକ୍ଷ_CODE (constructor_type) != ARRAY_TYPE
      || constructor_ଗଦା->implicit)
    ଫେରନ୍ତୁ 0;
  ବୃକ୍ଷ elttype = TYPE_MAIN_VARIANT (ବୃକ୍ଷ_TYPE (constructor_type));
  ଯଦି (ବୃକ୍ଷ_CODE (elttype) != INTEGER_TYPE
      && ବୃକ୍ଷ_CODE (elttype) != BITINT_TYPE)
    ଫେରନ୍ତୁ 0;
  ଯଦି (TYPE_PRECISION (elttype) != CHAR_BIT
      || constructor_ଗଦା->replacement_ମୂଲ୍ୟ.ମୂଲ୍ୟ
      || (COMPLETE_TYPE_P (constructor_type)
	  && !poly_int_ବୃକ୍ଷ_p (TYPE_SIZE (constructor_type)))
      || constructor_range_ଗଦା)
    ଫେରନ୍ତୁ 0;
  ଯଦି (constructor_max_index == NULL_ବୃକ୍ଷ)
    ଫେରନ୍ତୁ INT_MAX;
  ଯଦି (ବୃକ୍ଷ_int_cst_le (constructor_max_index, constructor_index)
      || integer_all_onesp (constructor_max_index))
    ଫେରନ୍ତୁ 0;
  widest_int w = wi::to_widest (constructor_max_index);
  w -= wi::to_widest (constructor_index);
  w += 1;
  ଯଦି (w < 64)
    ଫେରନ୍ତୁ 0;
  ଯଦି (w > INT_MAX)
    ଫେରନ୍ତୁ INT_MAX;
  ଫେରନ୍ତୁ w.to_uhwi ();
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

ଶୂନ୍ୟ
process_init_element (location_t loc, ସଂରଚନା c_ପଦସମଷ୍ଟି ମୂଲ୍ୟ, ତାର୍କିକ implicit,
		      ସଂରଚନା obstack * braced_init_obstack)
{
  ବୃକ୍ଷ orig_ମୂଲ୍ୟ = ମୂଲ୍ୟ.ମୂଲ୍ୟ;
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା string_flag
    = (orig_ମୂଲ୍ୟ != NULL_ବୃକ୍ଷ && ବୃକ୍ଷ_CODE (orig_ମୂଲ୍ୟ) == STRING_CST);
  ତାର୍କିକ strict_string = ମୂଲ୍ୟ.original_code == STRING_CST;
  ତାର୍କିକ was_designated = designator_depth != 0;
  ବୃକ୍ଷ raw_data = NULL_ବୃକ୍ଷ;

retry:
  designator_depth = 0;
  designator_erroneous = 0;

  ଯଦି (!implicit && ମୂଲ୍ୟ.ମୂଲ୍ୟ && !integer_zerop (ମୂଲ୍ୟ.ମୂଲ୍ୟ))
    constructor_zeroinit = 0;

  /* Handle superfluous braces around string cst as in
     char x[] = {"foo"}; */
  ଯଦି (constructor_type
      && !was_designated
      && ବୃକ୍ଷ_CODE (constructor_type) == ARRAY_TYPE
      && INTEGRAL_TYPE_P (ବୃକ୍ଷ_TYPE (constructor_type))
      && integer_zerop (constructor_unfilled_index))
    {
      ଯଦି (constructor_ଗଦା->replacement_ମୂଲ୍ୟ.ମୂଲ୍ୟ)
	{
	  error_init (loc, "excess elements in %qT initializer", constructor_type);
	  ଫେରନ୍ତୁ;
	}
      ଅନ୍ୟଥା ଯଦି (string_flag)
	{
	  constructor_ଗଦା->replacement_ମୂଲ୍ୟ = ମୂଲ୍ୟ;
	  ଫେରନ୍ତୁ;
	}
    }

  ଯଦି (constructor_ଗଦା->replacement_ମୂଲ୍ୟ.ମୂଲ୍ୟ != NULL_ବୃକ୍ଷ)
    {
      error_init (loc, "excess elements in struct initializer");
      ଫେରନ୍ତୁ;
    }

  /* Ignore elements of a brace group if it is entirely superfluous
     and has already been diagnosed, or if the type is erroneous.  */
  ଯଦି (constructor_type == NULL_ବୃକ୍ଷ || constructor_type == error_mark_ଗଣ୍ଠି)
    ଫେରନ୍ତୁ;

  /* Ignore elements of an initializer for a variable-size type.
     Those are diagnosed in the parser (empty initializer braces are OK).  */
  ଯଦି (COMPLETE_TYPE_P (constructor_type)
      && !poly_int_ବୃକ୍ଷ_p (TYPE_SIZE (constructor_type)))
    ଫେରନ୍ତୁ;

  ଯଦି (!implicit && warn_designated_init && !was_designated
      && ବୃକ୍ଷ_CODE (constructor_type) == RECORD_TYPE
      && lookup_attribute ("designated_init",
			   TYPE_ATTRIBUTES (constructor_type)))
    warning_init (loc,
		  OPT_Wdesignated_init,
		  "positional initialization of field "
		  "in %<struct%> declared with %<designated_init%> attribute");

  /* If we've exhausted any levels that didn't have braces,
     pop them now.  */
  ଯେତେବେଳେ (constructor_ଗଦା->implicit)
    {
      ଯଦି (RECORD_OR_UNION_TYPE_P (constructor_type)
	  && constructor_fields == NULL_ବୃକ୍ଷ)
	process_init_element (loc,
			      କାଢ଼_init_level (loc, 1, braced_init_obstack,
					      last_init_list_comma),
			      ସତ୍ୟ, braced_init_obstack);
      ଅନ୍ୟଥା ଯଦି ((ବୃକ୍ଷ_CODE (constructor_type) == ARRAY_TYPE
		|| gnu_vector_type_p (constructor_type))
	       && constructor_max_index
	       && ବୃକ୍ଷ_int_cst_lt (constructor_max_index,
				   constructor_index))
	process_init_element (loc,
			      କାଢ଼_init_level (loc, 1, braced_init_obstack,
					      last_init_list_comma),
			      ସତ୍ୟ, braced_init_obstack);
      ଅନ୍ୟଥା
	ଭାଙ୍ଗ;
    }

  /* In the case of [LO ... HI] = VALUE, only evaluate VALUE once.  */
  ଯଦି (constructor_range_ଗଦା)
    {
      /* If value is a compound literal and we'll be just using its
	 content, don't put it into a SAVE_EXPR.  */
      ଯଦି (ବୃକ୍ଷ_CODE (ମୂଲ୍ୟ.ମୂଲ୍ୟ) != COMPOUND_LITERAL_ପଦସମଷ୍ଟି
	  || !require_constant_ମୂଲ୍ୟ)
	{
	  ବୃକ୍ଷ semantic_type = NULL_ବୃକ୍ଷ;
	  ଯଦି (ବୃକ୍ଷ_CODE (ମୂଲ୍ୟ.ମୂଲ୍ୟ) == EXCESS_PRECISION_ପଦସମଷ୍ଟି)
	    {
	      semantic_type = ବୃକ୍ଷ_TYPE (ମୂଲ୍ୟ.ମୂଲ୍ୟ);
	      ମୂଲ୍ୟ.ମୂଲ୍ୟ = ବୃକ୍ଷ_OPERAND (ମୂଲ୍ୟ.ମୂଲ୍ୟ, 0);
	    }
	  ମୂଲ୍ୟ.ମୂଲ୍ୟ = save_ପଦସମଷ୍ଟି (ମୂଲ୍ୟ.ମୂଲ୍ୟ);
	  ଯଦି (semantic_type)
	    ମୂଲ୍ୟ.ମୂଲ୍ୟ = build1 (EXCESS_PRECISION_ପଦସମଷ୍ଟି, semantic_type,
				  ମୂଲ୍ୟ.ମୂଲ୍ୟ);
	}
    }

  ଯେତେବେଳେ (1)
    {
      ଯଦି (ବୃକ୍ଷ_CODE (constructor_type) == RECORD_TYPE)
	{
	  ବୃକ୍ଷ fieldtype;
	  ଗଣନା ବୃକ୍ଷ_code fieldcode;

	  ଯଦି (constructor_fields == NULL_ବୃକ୍ଷ)
	    {
	      pedwarn_init (loc, 0, "excess elements in struct initializer");
	      ଭାଙ୍ଗ;
	    }

	  fieldtype = ବୃକ୍ଷ_TYPE (constructor_fields);
	  ଯଦି (fieldtype != error_mark_ଗଣ୍ଠି)
	    fieldtype = TYPE_MAIN_VARIANT (fieldtype);
	  fieldcode = ବୃକ୍ଷ_CODE (fieldtype);

	  /* Error for non-static initialization of a flexible array member.  */
	  ଯଦି (fieldcode == ARRAY_TYPE
	      && !require_constant_ମୂଲ୍ୟ
	      && TYPE_SIZE (fieldtype) == NULL_ବୃକ୍ଷ
	      && DECL_CHAIN (constructor_fields) == NULL_ବୃକ୍ଷ)
	    {
	      error_init (loc, "non-static initialization of a flexible "
			  "array member");
	      ଭାଙ୍ଗ;
	    }

	  /* Error for initialization of a flexible array member with
	     a string constant if the structure is in an array.  E.g.:
	     struct S { int x; char y[]; };
	     struct S s[] = { { 1, "foo" } };
	     is invalid.  */
	  ଯଦି (string_flag
	      && fieldcode == ARRAY_TYPE
	      && constructor_depth > 1
	      && TYPE_SIZE (fieldtype) == NULL_ବୃକ୍ଷ
	      && DECL_CHAIN (constructor_fields) == NULL_ବୃକ୍ଷ)
	    {
	      ତାର୍କିକ in_array_p = ମିଥ୍ୟା;
	      ପାଇଁ (ସଂରଚନା constructor_ଗଦା *p = constructor_ଗଦା;
		   p && p->type; p = p->next)
		ଯଦି (ବୃକ୍ଷ_CODE (p->type) == ARRAY_TYPE)
		  {
		    in_array_p = ସତ୍ୟ;
		    ଭାଙ୍ଗ;
		  }
	      ଯଦି (in_array_p)
		{
		  error_init (loc, "initialization of flexible array "
			      "member in a nested context");
		  ଭାଙ୍ଗ;
		}
	    }

	  /* Accept a string constant to initialize a subarray.  */
	  ଯଦି (ମୂଲ୍ୟ.ମୂଲ୍ୟ != NULL_ବୃକ୍ଷ
	      && fieldcode == ARRAY_TYPE
	      && INTEGRAL_TYPE_P (ବୃକ୍ଷ_TYPE (fieldtype))
	      && string_flag)
	    ମୂଲ୍ୟ.ମୂଲ୍ୟ = orig_ମୂଲ୍ୟ;
	  /* Otherwise, if we have come to a subaggregate,
	     and we don't have an element of its type, push into it.  */
	  ଅନ୍ୟଥା ଯଦି (ମୂଲ୍ୟ.ମୂଲ୍ୟ != NULL_ବୃକ୍ଷ
		   && initialize_elementwise_p (fieldtype, ମୂଲ୍ୟ.ମୂଲ୍ୟ))
	    {
	      ଠେଲ_init_level (loc, 1, braced_init_obstack);
	      ଜାରି;
	    }

	  ମୂଲ୍ୟ.ମୂଲ୍ୟ = maybe_split_raw_data (ମୂଲ୍ୟ.ମୂଲ୍ୟ, &raw_data);
	  ଯଦି (ମୂଲ୍ୟ.ମୂଲ୍ୟ)
	    {
	      ଠେଲ_member_name (constructor_fields);
	      output_init_element (loc, ମୂଲ୍ୟ.ମୂଲ୍ୟ, ମୂଲ୍ୟ.original_type,
				   strict_string, fieldtype,
				   constructor_fields, ସତ୍ୟ, implicit,
				   braced_init_obstack);
	      RESTORE_SPELLING_DEPTH (constructor_depth);
	    }
	  ଅନ୍ୟଥା
	    /* Do the bookkeeping for an element that was
	       directly output as a constructor.  */
	    {
	      /* For a record, keep track of end position of last field.  */
	      ଯଦି (DECL_SIZE (constructor_fields))
		constructor_bit_index
		  = size_binop_loc (ନିବେଶ_location, PLUS_ପଦସମଷ୍ଟି,
				    bit_position (constructor_fields),
				    DECL_SIZE (constructor_fields));

	      /* If the current field was the first one not yet written out,
		 it isn't now, so update.  */
	      ଯଦି (constructor_unfilled_fields == constructor_fields)
		{
		  constructor_unfilled_fields = DECL_CHAIN (constructor_fields);
		  /* Skip any nameless bit fields.  */
		  ଯେତେବେଳେ (constructor_unfilled_fields != 0
			 && (DECL_UNNAMED_BIT_FIELD
			     (constructor_unfilled_fields)))
		    constructor_unfilled_fields =
		      DECL_CHAIN (constructor_unfilled_fields);
		}
	    }

	  constructor_fields = DECL_CHAIN (constructor_fields);
	  /* Skip any nameless bit fields at the beginning.  */
	  ଯେତେବେଳେ (constructor_fields != NULL_ବୃକ୍ଷ
		 && DECL_UNNAMED_BIT_FIELD (constructor_fields))
	    constructor_fields = DECL_CHAIN (constructor_fields);
	}
      ଅନ୍ୟଥା ଯଦି (ବୃକ୍ଷ_CODE (constructor_type) == UNION_TYPE)
	{
	  ବୃକ୍ଷ fieldtype;
	  ଗଣନା ବୃକ୍ଷ_code fieldcode;

	  ଯଦି (constructor_fields == NULL_ବୃକ୍ଷ)
	    {
	      pedwarn_init (loc, 0,
			    "excess elements in union initializer");
	      ଭାଙ୍ଗ;
	    }

	  fieldtype = ବୃକ୍ଷ_TYPE (constructor_fields);
	  ଯଦି (fieldtype != error_mark_ଗଣ୍ଠି)
	    fieldtype = TYPE_MAIN_VARIANT (fieldtype);
	  fieldcode = ବୃକ୍ଷ_CODE (fieldtype);

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
	  ଯଦି (!in_system_header_at (ନିବେଶ_location) && !constructor_designated
	      && !(ମୂଲ୍ୟ.ମୂଲ୍ୟ && (integer_zerop (ମୂଲ୍ୟ.ମୂଲ୍ୟ)
				   || real_zerop (ମୂଲ୍ୟ.ମୂଲ୍ୟ))))
	    warning (OPT_Wtraditional, "traditional C rejects initialization "
		     "of unions");

	  /* Error for non-static initialization of a flexible array member.  */
	  ଯଦି (fieldcode == ARRAY_TYPE
	      && !require_constant_ମୂଲ୍ୟ
	      && TYPE_SIZE (fieldtype) == NULL_ବୃକ୍ଷ)
	    {
	      error_init (loc, "non-static initialization of a flexible "
			  "array member");
	      ଭାଙ୍ଗ;
	    }

	  /* Error for initialization of a flexible array member with
	     a string constant if the structure is in an array.  E.g.:
	     union U { int x; char y[]; };
	     union U s[] = { { 1, "foo" } };
	     is invalid.  */
	  ଯଦି (string_flag
	      && fieldcode == ARRAY_TYPE
	      && constructor_depth > 1
	      && TYPE_SIZE (fieldtype) == NULL_ବୃକ୍ଷ)
	    {
	      ତାର୍କିକ in_array_p = ମିଥ୍ୟା;
	      ପାଇଁ (ସଂରଚନା constructor_ଗଦା *p = constructor_ଗଦା;
		   p && p->type; p = p->next)
		ଯଦି (ବୃକ୍ଷ_CODE (p->type) == ARRAY_TYPE)
		  {
		    in_array_p = ସତ୍ୟ;
		    ଭାଙ୍ଗ;
		  }
	      ଯଦି (in_array_p)
		{
		  error_init (loc, "initialization of flexible array "
			      "member in a nested context");
		  ଭାଙ୍ଗ;
		}
	    }

	  /* Accept a string constant to initialize a subarray.  */
	  ଯଦି (ମୂଲ୍ୟ.ମୂଲ୍ୟ != NULL_ବୃକ୍ଷ
	      && fieldcode == ARRAY_TYPE
	      && INTEGRAL_TYPE_P (ବୃକ୍ଷ_TYPE (fieldtype))
	      && string_flag)
	    ମୂଲ୍ୟ.ମୂଲ୍ୟ = orig_ମୂଲ୍ୟ;
	  /* Otherwise, if we have come to a subaggregate,
	     and we don't have an element of its type, push into it.  */
	  ଅନ୍ୟଥା ଯଦି (ମୂଲ୍ୟ.ମୂଲ୍ୟ != NULL_ବୃକ୍ଷ
		   && initialize_elementwise_p (fieldtype, ମୂଲ୍ୟ.ମୂଲ୍ୟ))
	    {
	      ଠେଲ_init_level (loc, 1, braced_init_obstack);
	      ଜାରି;
	    }

	  ମୂଲ୍ୟ.ମୂଲ୍ୟ = maybe_split_raw_data (ମୂଲ୍ୟ.ମୂଲ୍ୟ, &raw_data);
	  ଯଦି (ମୂଲ୍ୟ.ମୂଲ୍ୟ)
	    {
	      ଠେଲ_member_name (constructor_fields);
	      output_init_element (loc, ମୂଲ୍ୟ.ମୂଲ୍ୟ, ମୂଲ୍ୟ.original_type,
				   strict_string, fieldtype,
				   constructor_fields, ସତ୍ୟ, implicit,
				   braced_init_obstack);
	      RESTORE_SPELLING_DEPTH (constructor_depth);
	    }
	  ଅନ୍ୟଥା
	    /* Do the bookkeeping for an element that was
	       directly output as a constructor.  */
	    {
	      constructor_bit_index = DECL_SIZE (constructor_fields);
	      constructor_unfilled_fields = DECL_CHAIN (constructor_fields);
	    }

	  constructor_fields = NULL_ବୃକ୍ଷ;
	}
      ଅନ୍ୟଥା ଯଦି (ବୃକ୍ଷ_CODE (constructor_type) == ARRAY_TYPE)
	{
	  ବୃକ୍ଷ elttype = TYPE_MAIN_VARIANT (ବୃକ୍ଷ_TYPE (constructor_type));
	  ଗଣନା ବୃକ୍ଷ_code eltcode = ବୃକ୍ଷ_CODE (elttype);

	  /* Accept a string constant to initialize a subarray.  */
	  ଯଦି (ମୂଲ୍ୟ.ମୂଲ୍ୟ != NULL_ବୃକ୍ଷ
	      && eltcode == ARRAY_TYPE
	      && INTEGRAL_TYPE_P (ବୃକ୍ଷ_TYPE (elttype))
	      && string_flag)
	    ମୂଲ୍ୟ.ମୂଲ୍ୟ = orig_ମୂଲ୍ୟ;
	  /* Otherwise, if we have come to a subaggregate,
	     and we don't have an element of its type, push into it.  */
	  ଅନ୍ୟଥା ଯଦି (ମୂଲ୍ୟ.ମୂଲ୍ୟ != NULL_ବୃକ୍ଷ
		   && initialize_elementwise_p (elttype, ମୂଲ୍ୟ.ମୂଲ୍ୟ))
	    {
	      ଠେଲ_init_level (loc, 1, braced_init_obstack);
	      ଜାରି;
	    }

	  ଯଦି (constructor_max_index != NULL_ବୃକ୍ଷ
	      && (ବୃକ୍ଷ_int_cst_lt (constructor_max_index, constructor_index)
		  || integer_all_onesp (constructor_max_index))
	      /* For VLA we got an error already.  */
	      && !C_TYPE_VARIABLE_SIZE (constructor_type))
	    {
	      pedwarn_init (loc, 0,
			    "excess elements in array initializer");
	      ଭାଙ୍ଗ;
	    }

	  ଯଦି (ମୂଲ୍ୟ.ମୂଲ୍ୟ
	      && ବୃକ୍ଷ_CODE (ମୂଲ୍ୟ.ମୂଲ୍ୟ) == RAW_DATA_CST
	      && RAW_DATA_LENGTH (ମୂଲ୍ୟ.ମୂଲ୍ୟ) > 1
	      && (ବୃକ୍ଷ_CODE (elttype) == INTEGER_TYPE
		  || ବୃକ୍ଷ_CODE (elttype) == BITINT_TYPE)
	      && TYPE_PRECISION (elttype) == CHAR_BIT
	      && (constructor_max_index == NULL_ବୃକ୍ଷ
		  || ବୃକ୍ଷ_int_cst_lt (constructor_index,
				      constructor_max_index)))
	    {
	      unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା len = RAW_DATA_LENGTH (ମୂଲ୍ୟ.ମୂଲ୍ୟ);
	      ଯଦି (constructor_max_index)
		{
		  widest_int w = wi::to_widest (constructor_max_index);
		  w -= wi::to_widest (constructor_index);
		  w += 1;
		  ଯଦି (w < len)
		    len = w.to_uhwi ();
		}
	      ଯଦି (len < (unsigned) RAW_DATA_LENGTH (ମୂଲ୍ୟ.ମୂଲ୍ୟ))
		{
		  raw_data = copy_ଗଣ୍ଠି (ମୂଲ୍ୟ.ମୂଲ୍ୟ);
		  RAW_DATA_LENGTH (raw_data) -= len;
		  RAW_DATA_POINTER (raw_data) += len;
		  RAW_DATA_LENGTH (ମୂଲ୍ୟ.ମୂଲ୍ୟ) = len;
		}
	      ବୃକ୍ଷ_TYPE (ମୂଲ୍ୟ.ମୂଲ୍ୟ) = elttype;
	      ଠେଲ_array_bounds (ବୃକ୍ଷ_to_uhwi (constructor_index));
	      output_init_element (loc, ମୂଲ୍ୟ.ମୂଲ୍ୟ, ମୂଲ୍ୟ.original_type,
				   ମିଥ୍ୟା, elttype, constructor_index, ସତ୍ୟ,
				   implicit, braced_init_obstack);
	      RESTORE_SPELLING_DEPTH (constructor_depth);
	      constructor_index
		= size_binop_loc (ନିବେଶ_location, PLUS_ପଦସମଷ୍ଟି,
				  constructor_index, bitsize_int (len));
	    }
	  ଅନ୍ୟଥା
	    {
	      ମୂଲ୍ୟ.ମୂଲ୍ୟ = maybe_split_raw_data (ମୂଲ୍ୟ.ମୂଲ୍ୟ, &raw_data);
	      /* Now output the actual element.  */
	      ଯଦି (ମୂଲ୍ୟ.ମୂଲ୍ୟ)
		{
		  ଠେଲ_array_bounds (ବୃକ୍ଷ_to_uhwi (constructor_index));
		  output_init_element (loc, ମୂଲ୍ୟ.ମୂଲ୍ୟ, ମୂଲ୍ୟ.original_type,
				       strict_string, elttype,
				       constructor_index, ସତ୍ୟ, implicit,
				       braced_init_obstack);
		  RESTORE_SPELLING_DEPTH (constructor_depth);
		}

	      constructor_index
		= size_binop_loc (ନିବେଶ_location, PLUS_ପଦସମଷ୍ଟି,
				  constructor_index, bitsize_one_ଗଣ୍ଠି);

	      ଯଦି (!ମୂଲ୍ୟ.ମୂଲ୍ୟ)
		/* If we are doing the bookkeeping for an element that was
		   directly output as a constructor, we must update
		   constructor_unfilled_index.  */
		constructor_unfilled_index = constructor_index;
	    }
	}
      ଅନ୍ୟଥା ଯଦି (gnu_vector_type_p (constructor_type))
	{
	  ବୃକ୍ଷ elttype = TYPE_MAIN_VARIANT (ବୃକ୍ଷ_TYPE (constructor_type));

	  /* Do a basic check of initializer size.  Note that vectors
	     may not always have a fixed size derived from their type.  */
	  ଯଦି (maybe_lt (ବୃକ୍ଷ_to_poly_uint64 (constructor_max_index),
			ବୃକ୍ଷ_to_poly_uint64 (constructor_index)))
	    {
	      /* Diagose VLA out-of-bounds as errors.  */
	      ଯଦି (ବୃକ୍ଷ_to_poly_uint64 (constructor_max_index).is_constant())
		pedwarn_init (loc, 0,
			      "excess elements in vector initializer");
	      ଅନ୍ୟଥା
		error_init (loc, "excess elements in vector initializer");

	      ଭାଙ୍ଗ;
	    }

	  ମୂଲ୍ୟ.ମୂଲ୍ୟ = maybe_split_raw_data (ମୂଲ୍ୟ.ମୂଲ୍ୟ, &raw_data);
	  /* Now output the actual element.  */
	  ଯଦି (ମୂଲ୍ୟ.ମୂଲ୍ୟ)
	    {
	      ଯଦି (ବୃକ୍ଷ_CODE (ମୂଲ୍ୟ.ମୂଲ୍ୟ) == VECTOR_CST)
		elttype = TYPE_MAIN_VARIANT (constructor_type);
	      output_init_element (loc, ମୂଲ୍ୟ.ମୂଲ୍ୟ, ମୂଲ୍ୟ.original_type,
				   strict_string, elttype,
				   constructor_index, ସତ୍ୟ, implicit,
				   braced_init_obstack);
	    }

	  constructor_index
	    = size_binop_loc (ନିବେଶ_location,
			      PLUS_ପଦସମଷ୍ଟି, constructor_index, bitsize_one_ଗଣ୍ଠି);

	  ଯଦି (!ମୂଲ୍ୟ.ମୂଲ୍ୟ)
	    /* If we are doing the bookkeeping for an element that was
	       directly output as a constructor, we must update
	       constructor_unfilled_index.  */
	    constructor_unfilled_index = constructor_index;
	}

      /* Handle the sole element allowed in a braced initializer
	 for a scalar variable.  */
      ଅନ୍ୟଥା ଯଦି (constructor_type != error_mark_ଗଣ୍ଠି
	       && constructor_fields == NULL_ବୃକ୍ଷ)
	{
	  pedwarn_init (loc, 0,
			"excess elements in scalar initializer");
	  ଭାଙ୍ଗ;
	}
      ଅନ୍ୟଥା
	{
	  ମୂଲ୍ୟ.ମୂଲ୍ୟ = maybe_split_raw_data (ମୂଲ୍ୟ.ମୂଲ୍ୟ, &raw_data);
	  ଯଦି (ମୂଲ୍ୟ.ମୂଲ୍ୟ)
	    output_init_element (loc, ମୂଲ୍ୟ.ମୂଲ୍ୟ, ମୂଲ୍ୟ.original_type,
				 strict_string, constructor_type,
				 NULL_ବୃକ୍ଷ, ସତ୍ୟ, implicit,
				 braced_init_obstack);
	  constructor_fields = NULL_ବୃକ୍ଷ;
	}

      /* Handle range initializers either at this level or anywhere higher
	 in the designator stack.  */
      ଯଦି (constructor_range_ଗଦା)
	{
	  ସଂରଚନା constructor_range_ଗଦା *p, *range_ଗଦା;
	  ପୂର୍ଣ୍ଣସଂଖ୍ୟା finish = 0;

	  range_ଗଦା = constructor_range_ଗଦା;
	  constructor_range_ଗଦା = 0;
	  ଯେତେବେଳେ (constructor_ଗଦା != range_ଗଦା->ଗଦା)
	    {
	      gcc_assert (constructor_ଗଦା->implicit);
	      process_init_element (loc,
				    କାଢ଼_init_level (loc, 1,
						    braced_init_obstack,
						    last_init_list_comma),
				    ସତ୍ୟ, braced_init_obstack);
	    }
	  ପାଇଁ (p = range_ଗଦା;
	       !p->range_end || ବୃକ୍ଷ_int_cst_equal (p->index, p->range_end);
	       p = p->prev)
	    {
	      gcc_assert (constructor_ଗଦା->implicit);
	      process_init_element (loc,
				    କାଢ଼_init_level (loc, 1,
						    braced_init_obstack,
						    last_init_list_comma),
				    ସତ୍ୟ, braced_init_obstack);
	    }

	  p->index = size_binop_loc (ନିବେଶ_location,
				     PLUS_ପଦସମଷ୍ଟି, p->index, bitsize_one_ଗଣ୍ଠି);
	  ଯଦି (ବୃକ୍ଷ_int_cst_equal (p->index, p->range_end) && !p->prev)
	    finish = 1;

	  ଯେତେବେଳେ (1)
	    {
	      constructor_index = p->index;
	      constructor_fields = p->fields;
	      ଯଦି (finish && p->range_end && p->index == p->range_start)
		{
		  finish = 0;
		  p->prev = 0;
		}
	      p = p->next;
	      ଯଦି (!p)
		ଭାଙ୍ଗ;
	      finish_implicit_inits (loc, braced_init_obstack);
	      ଠେଲ_init_level (loc, 2, braced_init_obstack);
	      p->ଗଦା = constructor_ଗଦା;
	      ଯଦି (p->range_end && ବୃକ୍ଷ_int_cst_equal (p->index, p->range_end))
		p->index = p->range_start;
	    }

	  ଯଦି (!finish)
	    constructor_range_ଗଦା = range_ଗଦା;
	  ଜାରି;
	}

      ଭାଙ୍ଗ;
    }

  constructor_range_ଗଦା = 0;

  ଯଦି (raw_data && RAW_DATA_LENGTH (raw_data))
    {
      gcc_assert (!string_flag && !was_designated);
      ମୂଲ୍ୟ.ମୂଲ୍ୟ = raw_data;
      raw_data = NULL_ବୃକ୍ଷ;
      ଯାଅ retry;
    }
}

/* Build a complete asm-statement, whose components are a CV_QUALIFIER
   (guaranteed to be 'volatile' or null) and ARGS (represented using
   an ASM_EXPR node).  */
ବୃକ୍ଷ
build_asm_stmt (ତାର୍କିକ is_volatile, ବୃକ୍ଷ args)
{
  ଯଦି (is_volatile)
    ASM_VOLATILE_P (args) = 1;
  ଫେରନ୍ତୁ add_stmt (args);
}

/* Build an asm-expr, whose components are a STRING, some OUTPUTS,
   some INPUTS, and some CLOBBERS.  The latter three may be NULL.
   SIMPLE indicates whether there was anything at all after the
   string in the asm expression -- asm("blah") and asm("blah" : )
   are subtly different.  We use a ASM_EXPR node to represent this.
   LOC is the location of the asm, and IS_INLINE says whether this
   is asm inline.  */
ବୃକ୍ଷ
build_asm_ପଦସମଷ୍ଟି (location_t loc, ବୃକ୍ଷ string, ବୃକ୍ଷ outputs, ବୃକ୍ଷ inputs,
		ବୃକ୍ଷ clobbers, ବୃକ୍ଷ labels, ତାର୍କିକ simple, ତାର୍କିକ is_inline)
{
  ବୃକ୍ଷ tail;
  ବୃକ୍ଷ args;
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;
  ଅଚଳ ଅକ୍ଷର *constraint;
  ଅଚଳ ଅକ୍ଷର **oconstraints;
  ତାର୍କିକ allows_mem, allows_reg, is_inout;
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା ninputs, noutputs;

  ninputs = list_length (inputs);
  noutputs = list_length (outputs);
  oconstraints = (ଅଚଳ ଅକ୍ଷର **) alloca (noutputs * ଆକାର (ଅଚଳ ଅକ୍ଷର *));

  string = resolve_asm_operand_names (string, outputs, inputs, labels);

  /* Remove output conversions that change the type but not the mode.  */
  ପାଇଁ (i = 0, tail = outputs; tail; ++i, tail = ବୃକ୍ଷ_CHAIN (tail))
    {
      ବୃକ୍ଷ output = ବୃକ୍ଷ_ମୂଲ୍ୟ (tail);

      output = c_fully_fold (output, ମିଥ୍ୟା, ଖାଲି, ସତ୍ୟ);

      /* ??? Really, this should not be here.  Users should be using a
	 proper lvalue, dammit.  But there's a long history of using casts
	 in the output operands.  In cases like longlong.h, this becomes a
	 primitive form of typechecking -- if the cast can be removed, then
	 the output operand had a type of the proper width; otherwise we'll
	 get an error.  Gross, but ...  */
      STRIP_NOPS (output);

      ଯଦି (!lvalue_or_else (loc, output, lv_asm))
	output = error_mark_ଗଣ୍ଠି;

      ଯଦି (output != error_mark_ଗଣ୍ଠି
	  && (ବୃକ୍ଷ_READONLY (output)
	      || TYPE_READONLY (ବୃକ୍ଷ_TYPE (output))
	      || (RECORD_OR_UNION_TYPE_P (ବୃକ୍ଷ_TYPE (output))
		  && C_TYPE_FIELDS_READONLY (ବୃକ୍ଷ_TYPE (output)))))
	readonly_error (loc, output, lv_asm);

      constraint = ବୃକ୍ଷ_STRING_POINTER (ବୃକ୍ଷ_ମୂଲ୍ୟ (ବୃକ୍ଷ_PURPOSE (tail)));
      oconstraints[i] = constraint;

      ଯଦି (parse_output_constraint (&constraint, i, ninputs, noutputs,
				   &allows_mem, &allows_reg, &is_inout,
				   nullptr))
	{
	  /* If the operand is going to end up in memory,
	     mark it addressable.  */
	  ଯଦି (!allows_reg && !c_mark_addressable (output))
	    output = error_mark_ଗଣ୍ଠି;
	  ଯଦି (!(!allows_reg && allows_mem)
	      && output != error_mark_ଗଣ୍ଠି
	      && VOID_TYPE_P (ବୃକ୍ଷ_TYPE (output)))
	    {
	      error_at (loc, "invalid use of void expression");
	      output = error_mark_ଗଣ୍ଠି;
	    }
	  ଯଦି (allows_reg && current_function_decl == NULL_ବୃକ୍ଷ)
	    {
	      error_at (loc, "constraint allows registers outside of "
			     "a function");
	      output = error_mark_ଗଣ୍ଠି;
	    }
	}
      ଅନ୍ୟଥା
	output = error_mark_ଗଣ୍ଠି;

      ଯଦି (current_function_decl == NULL_ବୃକ୍ଷ && output != error_mark_ଗଣ୍ଠି)
	{
	  ଯଦି (ବୃକ୍ଷ_SIDE_EFFECTS (output))
	    {
	      error_at (loc, "side-effects in output operand outside "
			     "of a function");
	      output = error_mark_ଗଣ୍ଠି;
	    }
	  ଅନ୍ୟଥା
	    {
	      ବୃକ୍ଷ addr = build_unary_op (loc, ADDR_ପଦସମଷ୍ଟି, output, ମିଥ୍ୟା);
	      ଯଦି (addr == error_mark_ଗଣ୍ଠି)
		output = error_mark_ଗଣ୍ଠି;
	      ଅନ୍ୟଥା ଯଦି (!initializer_constant_valid_p (addr, ବୃକ୍ଷ_TYPE (addr)))
		{
		  error_at (loc, "output operand outside of a function is not "
				 "constant");
		  output = error_mark_ଗଣ୍ଠି;
		}
	    }
	}
      ଅନ୍ୟଥା ଯଦି (output != error_mark_ଗଣ୍ଠି && strstr (constraint, "-"))
	{
	  error_at (loc, "%<-%> modifier used inside of a function");
	  output = error_mark_ଗଣ୍ଠି;
	}

      ବୃକ୍ଷ_ମୂଲ୍ୟ (tail) = output;
    }

  ପାଇଁ (i = 0, tail = inputs; tail; ++i, tail = ବୃକ୍ଷ_CHAIN (tail))
    {
      ବୃକ୍ଷ ନିବେଶ;

      constraint = ବୃକ୍ଷ_STRING_POINTER (ବୃକ୍ଷ_ମୂଲ୍ୟ (ବୃକ୍ଷ_PURPOSE (tail)));
      ନିବେଶ = ବୃକ୍ଷ_ମୂଲ୍ୟ (tail);

      ଯଦି (parse_ନିବେଶ_constraint (&constraint, i, ninputs, noutputs, 0,
				  oconstraints, &allows_mem, &allows_reg,
				  nullptr))
	{
	  /* If the operand is going to end up in memory,
	     mark it addressable.  */
	  ଯଦି (!allows_reg && allows_mem)
	    {
	      ନିବେଶ = c_fully_fold (ନିବେଶ, ମିଥ୍ୟା, ଖାଲି, ସତ୍ୟ);

	      /* Strip the nops as we allow this case.  FIXME, this really
		 should be rejected or made deprecated.  */
	      STRIP_NOPS (ନିବେଶ);
	      ଯଦି (!c_mark_addressable (ନିବେଶ))
		ନିବେଶ = error_mark_ଗଣ୍ଠି;
	    }
	  ଅନ୍ୟଥା
	    {
	      ନିବେଶ = c_fully_fold (convert_lvalue_to_rvalue (loc, ନିବେଶ,
							      ସତ୍ୟ, ମିଥ୍ୟା),
				    ମିଥ୍ୟା, ଖାଲି);

	      ଯଦି (ନିବେଶ != error_mark_ଗଣ୍ଠି && VOID_TYPE_P (ବୃକ୍ଷ_TYPE (ନିବେଶ)))
		{
		  error_at (loc, "invalid use of void expression");
		  ନିବେଶ = error_mark_ଗଣ୍ଠି;
		}
	    }
	  ଯଦି (allows_reg && current_function_decl == NULL_ବୃକ୍ଷ)
	    {
	      error_at (loc, "constraint allows registers outside of "
			     "a function");
	      ନିବେଶ = error_mark_ଗଣ୍ଠି;
	    }
	  ଯଦି (constraint[0] == ':' && ନିବେଶ != error_mark_ଗଣ୍ଠି)
	    {
	      ବୃକ୍ଷ t = ନିବେଶ;
	      STRIP_NOPS (t);
	      ଯଦି (ବୃକ୍ଷ_CODE (t) != ADDR_ପଦସମଷ୍ଟି
		  || !(ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_OPERAND (t, 0)) == FUNCTION_DECL
		       || (VAR_P (ବୃକ୍ଷ_OPERAND (t, 0))
			   && is_global_var (ବୃକ୍ଷ_OPERAND (t, 0)))))
		{
		  error_at (loc, "%<:%> constraint operand is not address "
				 "of a function or non-automatic variable");
		  ନିବେଶ = error_mark_ଗଣ୍ଠି;
		}
	      ଅନ୍ୟଥା ଯଦି (ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_OPERAND (t, 0)) == FUNCTION_DECL)
		suppress_warning (ବୃକ୍ଷ_OPERAND (t, 0), OPT_Wunused);
	    }
	}
      ଅନ୍ୟଥା
	ନିବେଶ = error_mark_ଗଣ୍ଠି;

      ଯଦି (current_function_decl == NULL_ବୃକ୍ଷ && ନିବେଶ != error_mark_ଗଣ୍ଠି)
	{
	  ଯଦି (ବୃକ୍ଷ_SIDE_EFFECTS (ନିବେଶ))
	    {
	      error_at (loc, "side-effects in input operand outside "
			     "of a function");
	      ନିବେଶ = error_mark_ଗଣ୍ଠି;
	    }
	  ଅନ୍ୟଥା
	    {
	      ବୃକ୍ଷ tem = ନିବେଶ;
	      ଯଦି (allows_mem && lvalue_p (ନିବେଶ))
		tem = build_unary_op (loc, ADDR_ପଦସମଷ୍ଟି, ନିବେଶ, ମିଥ୍ୟା);
	      ଯଦି (!initializer_constant_valid_p (tem, ବୃକ୍ଷ_TYPE (tem)))
		{
		  error_at (loc, "input operand outside of a function is not "
				 "constant");
		  ନିବେଶ = error_mark_ଗଣ୍ଠି;
		}
	    }
	}
      ଅନ୍ୟଥା ଯଦି (ନିବେଶ != error_mark_ଗଣ୍ଠି && strstr (constraint, "-"))
	{
	  error_at (loc, "%<-%> modifier used inside of a function");
	  ନିବେଶ = error_mark_ଗଣ୍ଠି;
	}

      ବୃକ୍ଷ_ମୂଲ୍ୟ (tail) = ନିବେଶ;
    }

  args = build_stmt (loc, ASM_ପଦସମଷ୍ଟି, string, outputs, inputs, clobbers, labels);

  /* asm statements without outputs, including simple ones, are treated
     as volatile.  */
  ASM_BASIC_P (args) = simple;
  ASM_VOLATILE_P (args) = (noutputs == 0);
  ASM_INLINE_P (args) = is_inline;

  ଫେରନ୍ତୁ args;
}

/* Generate a goto statement to LABEL.  LOC is the location of the
   GOTO.  */

ବୃକ୍ଷ
c_finish_goto_label (location_t loc, ବୃକ୍ଷ label)
{
  ବୃକ୍ଷ decl = lookup_label_for_goto (loc, label);
  ଯଦି (!decl)
    ଫେରନ୍ତୁ NULL_ବୃକ୍ଷ;
  ବୃକ୍ଷ_USED (decl) = 1;
  mark_decl_used (decl, ମିଥ୍ୟା);
  {
    add_stmt (build_predict_ପଦସମଷ୍ଟି (PRED_GOTO, NOT_TAKEN));
    ବୃକ୍ଷ t = build1 (GOTO_ପଦସମଷ୍ଟି, void_type_ଗଣ୍ଠି, decl);
    SET_ପଦସମଷ୍ଟି_LOCATION (t, loc);
    ଫେରନ୍ତୁ add_stmt (t);
  }
}

/* Generate a computed goto statement to EXPR.  LOC is the location of
   the GOTO.  */

ବୃକ୍ଷ
c_finish_goto_ptr (location_t loc, c_ପଦସମଷ୍ଟି val)
{
  ବୃକ୍ଷ ପଦସମଷ୍ଟି = val.ମୂଲ୍ୟ;
  ବୃକ୍ଷ t;
  pedwarn (loc, OPT_Wpedantic, "ISO C forbids %<goto *expr;%>");
  ଯଦି (ପଦସମଷ୍ଟି != error_mark_ଗଣ୍ଠି
      && !POINTER_TYPE_P (ବୃକ୍ଷ_TYPE (ପଦସମଷ୍ଟି))
      && !null_pointer_constant_p (ପଦସମଷ୍ଟି))
    {
      error_at (val.get_location (),
		"computed goto must be pointer type");
      ପଦସମଷ୍ଟି = build_zero_cst (ptr_type_ଗଣ୍ଠି);
    }
  ପଦସମଷ୍ଟି = c_fully_fold (ପଦସମଷ୍ଟି, ମିଥ୍ୟା, ଖାଲି);
  ପଦସମଷ୍ଟି = convert (ptr_type_ଗଣ୍ଠି, ପଦସମଷ୍ଟି);
  t = build1 (GOTO_ପଦସମଷ୍ଟି, void_type_ଗଣ୍ଠି, ପଦସମଷ୍ଟି);
  SET_ପଦସମଷ୍ଟି_LOCATION (t, loc);
  ଫେରନ୍ତୁ add_stmt (t);
}

/* Generate a C `return' statement.  RETVAL is the expression for what
   to return, or a null pointer for `return;' with no value.  LOC is
   the location of the return statement, or the location of the expression,
   if the statement has any.  If ORIGTYPE is not NULL_TREE, it
   is the original type of RETVAL.  MUSTTAIL_P indicates a musttail
   attribute.  */

ବୃକ୍ଷ
c_finish_return (location_t loc, ବୃକ୍ଷ retval, ବୃକ୍ଷ origtype, ତାର୍କିକ musttail_p)
{
  ବୃକ୍ଷ valtype = ବୃକ୍ଷ_TYPE (ବୃକ୍ଷ_TYPE (current_function_decl)), ret_stmt;
  ତାର୍କିକ no_warning = ମିଥ୍ୟା;
  ତାର୍କିକ npc = ମିଥ୍ୟା;

  /* Use the expansion point to handle cases such as returning NULL
     in a function returning void.  */
  location_t xloc = expansion_point_location_if_in_system_header (loc);

  ଯଦି (ବୃକ୍ଷ_THIS_VOLATILE (current_function_decl))
    warning_at (xloc, 0,
		"function declared %<noreturn%> has a %<return%> statement");

  set_musttail_on_return (retval, xloc, musttail_p);

  ଯଦି (retval)
    {
      ବୃକ୍ଷ semantic_type = NULL_ବୃକ୍ଷ;
      npc = null_pointer_constant_p (retval);
      ଯଦି (ବୃକ୍ଷ_CODE (retval) == EXCESS_PRECISION_ପଦସମଷ୍ଟି)
	{
	  semantic_type = ବୃକ୍ଷ_TYPE (retval);
	  retval = ବୃକ୍ଷ_OPERAND (retval, 0);
	}
      retval = c_fully_fold (retval, ମିଥ୍ୟା, ଖାଲି);
      ଯଦି (semantic_type
	  && valtype != NULL_ବୃକ୍ଷ
	  && ବୃକ୍ଷ_CODE (valtype) != VOID_TYPE)
	retval = build1 (EXCESS_PRECISION_ପଦସମଷ୍ଟି, semantic_type, retval);
    }

  ଯଦି (!retval)
    {
      current_function_returns_null = 1;
      ଯଦି ((warn_return_type >= 0 || flag_isoc99)
	  && valtype != NULL_ବୃକ୍ଷ && ବୃକ୍ଷ_CODE (valtype) != VOID_TYPE)
	{
	  no_warning = ସତ୍ୟ;
	  ଯଦି (emit_diagnostic (flag_isoc99
			       ? diagnostics::kind::permerror
			       : diagnostics::kind::warning,
			       loc, OPT_Wreturn_mismatch,
			       "%<return%> with no value,"
			       " in function returning non-void"))
	    inform (DECL_SOURCE_LOCATION (current_function_decl),
		    "declared here");
	}
    }
  ଅନ୍ୟଥା ଯଦି (valtype == NULL_ବୃକ୍ଷ || VOID_TYPE_P (valtype))
    {
      current_function_returns_null = 1;
      ତାର୍କିକ warned_here;
      ଯଦି (ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (retval)) != VOID_TYPE)
	warned_here = permerror_opt
	  (xloc, OPT_Wreturn_mismatch,
	   "%<return%> with a value, in function returning void");
      ଅନ୍ୟଥା
	warned_here = pedwarn
	  (xloc, OPT_Wpedantic, "ISO C forbids "
	   "%<return%> with expression, in function returning void");
      ଯଦି (warned_here)
	inform (DECL_SOURCE_LOCATION (current_function_decl),
		"declared here");
    }
  ଅନ୍ୟଥା
    {
      ବୃକ୍ଷ t = convert_for_assignment (loc, UNKNOWN_LOCATION, valtype,
				       retval, origtype, ic_return,
				       npc, NULL_ବୃକ୍ଷ, NULL_ବୃକ୍ଷ, 0);
      ବୃକ୍ଷ res = DECL_RESULT (current_function_decl);
      ବୃକ୍ଷ inner;
      ତାର୍କିକ save;

      current_function_returns_ମୂଲ୍ୟ = 1;
      ଯଦି (t == error_mark_ଗଣ୍ଠି)
	{
	  /* Suppress -Wreturn-type for this function.  */
	  ଯଦି (warn_return_type)
	    suppress_warning (current_function_decl, OPT_Wreturn_type);
	  ଫେରନ୍ତୁ NULL_ବୃକ୍ଷ;
	}

      save = in_late_ଦ୍ୱିମିକ_op;
      ଯଦି (C_BOOLEAN_TYPE_P (ବୃକ୍ଷ_TYPE (res))
	  || ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (res)) == COMPLEX_TYPE
	  || (SCALAR_FLOAT_TYPE_P (ବୃକ୍ଷ_TYPE (t))
	      && (ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (res)) == INTEGER_TYPE
		  || ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (res)) == ENUMERAL_TYPE)
	      && sanitize_flags_p (SANITIZE_FLOAT_CAST)))
        in_late_ଦ୍ୱିମିକ_op = ସତ୍ୟ;
      inner = t = convert (ବୃକ୍ଷ_TYPE (res), t);
      in_late_ଦ୍ୱିମିକ_op = save;

      /* Strip any conversions, additions, and subtractions, and see if
	 we are returning the address of a local variable.  Warn if so.  */
      ଯେତେବେଳେ (1)
	{
	  ବାଛ (ବୃକ୍ଷ_CODE (inner))
	    {
	    CASE_CONVERT:
	    ସ୍ଥିତି NON_LVALUE_ପଦସମଷ୍ଟି:
	    ସ୍ଥିତି PLUS_ପଦସମଷ୍ଟି:
	    ସ୍ଥିତି POINTER_PLUS_ପଦସମଷ୍ଟି:
	      inner = ବୃକ୍ଷ_OPERAND (inner, 0);
	      ଜାରି;

	    ସ୍ଥିତି MINUS_ପଦସମଷ୍ଟି:
	      /* If the second operand of the MINUS_EXPR has a pointer
		 type (or is converted from it), this may be valid, so
		 don't give a warning.  */
	      {
		ବୃକ୍ଷ op1 = ବୃକ୍ଷ_OPERAND (inner, 1);

		ଯେତେବେଳେ (!POINTER_TYPE_P (ବୃକ୍ଷ_TYPE (op1))
		       && (CONVERT_ପଦସମଷ୍ଟି_P (op1)
			   || ବୃକ୍ଷ_CODE (op1) == NON_LVALUE_ପଦସମଷ୍ଟି))
		  op1 = ବୃକ୍ଷ_OPERAND (op1, 0);

		ଯଦି (POINTER_TYPE_P (ବୃକ୍ଷ_TYPE (op1)))
		  ଭାଙ୍ଗ;

		inner = ବୃକ୍ଷ_OPERAND (inner, 0);
		ଜାରି;
	      }

	    ସ୍ଥିତି ADDR_ପଦସମଷ୍ଟି:
	      inner = ବୃକ୍ଷ_OPERAND (inner, 0);

	      ଯେତେବେଳେ (REFERENCE_CLASS_P (inner)
		     && !INDIRECT_REF_P (inner))
		inner = ବୃକ୍ଷ_OPERAND (inner, 0);

	      ଯଦି (DECL_P (inner)
		  && !DECL_EXTERNAL (inner)
		  && DECL_CONTEXT (inner) == current_function_decl
		  && POINTER_TYPE_P (ବୃକ୍ଷ_TYPE (ବୃକ୍ଷ_TYPE (current_function_decl))))
		{
		  ଯଦି (ବୃକ୍ଷ_CODE (inner) == LABEL_DECL)
		    warning_at (loc, OPT_Wreturn_local_addr,
				"function returns address of label");
		  ଅନ୍ୟଥା ଯଦି (ବୃକ୍ଷ_CODE (inner) == FUNCTION_DECL
			   && (C_FUNC_NONLOCAL_CONTEXT (inner)
			       || !DECL_INITIAL (inner)))
		    warning_at (loc, OPT_Wreturn_local_addr,
				"function returns address of nested function "
				"referencing local context");
		  ଅନ୍ୟଥା ଯଦି (ବୃକ୍ଷ_CODE (inner) != FUNCTION_DECL
			   && !ବୃକ୍ଷ_STATIC (inner))
		    {
		      warning_at (loc, OPT_Wreturn_local_addr,
				  "function returns address of local variable");
		      ବୃକ୍ଷ zero = build_zero_cst (ବୃକ୍ଷ_TYPE (res));
		      t = build2 (COMPOUND_ପଦସମଷ୍ଟି, ବୃକ୍ଷ_TYPE (res), t, zero);
		    }
		}
	      ଭାଙ୍ଗ;

	    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
	      ଭାଙ୍ଗ;
	    }

	  ଭାଙ୍ଗ;
	}

      retval = build2 (MODIFY_ପଦସମଷ୍ଟି, ବୃକ୍ଷ_TYPE (res), res, t);
      SET_ପଦସମଷ୍ଟି_LOCATION (retval, loc);

      ଯଦି (warn_sequence_point)
	verify_sequence_points (retval);
    }

  ret_stmt = build_stmt (loc, RETURN_ପଦସମଷ୍ଟି, retval);
  ଯଦି (no_warning)
    suppress_warning (ret_stmt, OPT_Wreturn_type);
  ଫେରନ୍ତୁ add_stmt (ret_stmt);
}

ସଂରଚନା c_switch {
  /* The SWITCH_STMT being built.  */
  ବୃକ୍ଷ switch_stmt;

  /* The original type of the testing expression, i.e. before the
     default conversion is applied.  */
  ବୃକ୍ଷ orig_type;

  /* A splay-tree mapping the low element of a case range to the high
     element, or NULL_TREE if there is no high element.  Used to
     determine whether or not a new case label duplicates an old case
     label.  We need a tree, rather than simply a hash table, because
     of the GNU case range extension.  */
  splay_ବୃକ୍ଷ cases;

  /* The bindings at the point of the switch.  This is used for
     warnings crossing decls when branching to a case label.  */
  ସଂରଚନା c_spot_bindings *bindings;

  /* Whether the switch includes any break statements.  */
  ତାର୍କିକ break_stmt_seen_p;

  /* The next node on the stack.  */
  ସଂରଚନା c_switch *next;

  /* Remember whether the controlling expression had boolean type
     before integer promotions for the sake of -Wswitch-bool.  */
  ତାର୍କିକ bool_cond_p;
};

/* A stack of the currently active switch statements.  The innermost
   switch statement is on the top of the stack.  There is no need to
   mark the stack for garbage collection because it is only active
   during the processing of the body of a function, and we never
   collect at that point.  */

ସଂରଚନା c_switch *c_switch_ଗଦା;

/* Start a C switch statement, testing expression EXP.  Return the new
   SWITCH_STMT.  SWITCH_LOC is the location of the `switch'.
   SWITCH_COND_LOC is the location of the switch's condition.
   EXPLICIT_CAST_P is true if the expression EXP has an explicit cast.  */

ବୃକ୍ଷ
c_start_switch (location_t switch_loc,
		location_t switch_cond_loc,
		ବୃକ୍ଷ exp, ତାର୍କିକ explicit_cast_p, ବୃକ୍ଷ switch_name)
{
  ବୃକ୍ଷ orig_type = error_mark_ଗଣ୍ଠି;
  ତାର୍କିକ bool_cond_p = ମିଥ୍ୟା;
  ସଂରଚନା c_switch *cs;

  ଯଦି (exp != error_mark_ଗଣ୍ଠି)
    {
      orig_type = ବୃକ୍ଷ_TYPE (exp);

      ଯଦି (!INTEGRAL_TYPE_P (orig_type))
	{
	  ଯଦି (orig_type != error_mark_ଗଣ୍ଠି)
	    {
	      error_at (switch_cond_loc, "switch quantity not an integer");
	      orig_type = error_mark_ଗଣ୍ଠି;
	    }
	  exp = integer_zero_ଗଣ୍ଠି;
	}
      ଅନ୍ୟଥା
	{
	  ବୃକ୍ଷ type = TYPE_MAIN_VARIANT (orig_type);
	  ବୃକ୍ଷ e = exp;

	  /* Warn if the condition has boolean value.  */
	  ଯେତେବେଳେ (ବୃକ୍ଷ_CODE (e) == COMPOUND_ପଦସମଷ୍ଟି)
	    e = ବୃକ୍ଷ_OPERAND (e, 1);

	  ଯଦି ((C_BOOLEAN_TYPE_P (type)
	       || truth_ମୂଲ୍ୟ_p (ବୃକ୍ଷ_CODE (e)))
	      /* Explicit cast to int suppresses this warning.  */
	      && !(ବୃକ୍ଷ_CODE (type) == INTEGER_TYPE
		   && explicit_cast_p))
	    bool_cond_p = ସତ୍ୟ;

	  ଯଦି (!in_system_header_at (ନିବେଶ_location)
	      && (type == long_integer_type_ଗଣ୍ଠି
		  || type == long_unsigned_type_ଗଣ୍ଠି))
	    warning_at (switch_cond_loc,
			OPT_Wtraditional, "%<long%> switch expression not "
			"converted to %<int%> in ISO C");

	  exp = c_fully_fold (exp, ମିଥ୍ୟା, ଖାଲି);
	  exp = default_conversion (exp);

	  ଯଦି (warn_sequence_point)
	    verify_sequence_points (exp);
	}
    }

  /* Add this new SWITCH_STMT to the stack.  */
  cs = XNEW (ସଂରଚନା c_switch);
  cs->switch_stmt = build_stmt (switch_loc, SWITCH_STMT, exp,
				NULL_ବୃକ୍ଷ, orig_type, NULL_ବୃକ୍ଷ, switch_name);
  cs->orig_type = orig_type;
  cs->cases = splay_ବୃକ୍ଷ_new (case_compare, ଖାଲି, ଖାଲି);
  cs->bindings = c_get_switch_bindings ();
  cs->break_stmt_seen_p = ମିଥ୍ୟା;
  cs->bool_cond_p = bool_cond_p;
  cs->next = c_switch_ଗଦା;
  c_switch_ଗଦା = cs;

  ଫେରନ୍ତୁ add_stmt (cs->switch_stmt);
}

/* Process a case label at location LOC, with attributes ATTRS.  */

ବୃକ୍ଷ
do_case (location_t loc, ବୃକ୍ଷ ତଳ_ମୂଲ୍ୟ, ବୃକ୍ଷ ଉପର_ମୂଲ୍ୟ, ବୃକ୍ଷ attrs)
{
  ବୃକ୍ଷ label = NULL_ବୃକ୍ଷ;

  ଯଦି (ତଳ_ମୂଲ୍ୟ && ବୃକ୍ଷ_CODE (ତଳ_ମୂଲ୍ୟ) != INTEGER_CST)
    {
      ତଳ_ମୂଲ୍ୟ = c_fully_fold (ତଳ_ମୂଲ୍ୟ, ମିଥ୍ୟା, ଖାଲି);
      ଯଦି (ବୃକ୍ଷ_CODE (ତଳ_ମୂଲ୍ୟ) == INTEGER_CST)
	pedwarn (loc, OPT_Wpedantic,
		 "case label is not an integer constant expression");
    }

  ଯଦି (ଉପର_ମୂଲ୍ୟ && ବୃକ୍ଷ_CODE (ଉପର_ମୂଲ୍ୟ) != INTEGER_CST)
    {
      ଉପର_ମୂଲ୍ୟ = c_fully_fold (ଉପର_ମୂଲ୍ୟ, ମିଥ୍ୟା, ଖାଲି);
      ଯଦି (ବୃକ୍ଷ_CODE (ଉପର_ମୂଲ୍ୟ) == INTEGER_CST)
	pedwarn (ନିବେଶ_location, OPT_Wpedantic,
		 "case label is not an integer constant expression");
    }

  ଯଦି (c_switch_ଗଦା == ଖାଲି)
    {
      ଯଦି (ତଳ_ମୂଲ୍ୟ)
	error_at (loc, "case label not within a switch statement");
      ଅନ୍ୟଥା
	error_at (loc, "%<default%> label not within a switch statement");
      ଫେରନ୍ତୁ NULL_ବୃକ୍ଷ;
    }

  ଯଦି (c_check_switch_jump_warnings (c_switch_ଗଦା->bindings,
				    ପଦସମଷ୍ଟି_LOCATION (c_switch_ଗଦା->switch_stmt),
				    loc))
    ଫେରନ୍ତୁ NULL_ବୃକ୍ଷ;

  label = c_add_case_label (loc, c_switch_ଗଦା->cases,
			    SWITCH_STMT_COND (c_switch_ଗଦା->switch_stmt),
			    ତଳ_ମୂଲ୍ୟ, ଉପର_ମୂଲ୍ୟ, attrs);
  ଯଦି (label == error_mark_ଗଣ୍ଠି)
    label = NULL_ବୃକ୍ଷ;
  ଫେରନ୍ତୁ label;
}

/* Finish the switch statement.  TYPE is the original type of the
   controlling expression of the switch, or NULL_TREE.  */

ଶୂନ୍ୟ
c_finish_switch (ବୃକ୍ଷ body, ବୃକ୍ଷ type)
{
  ସଂରଚନା c_switch *cs = c_switch_ଗଦା;
  location_t switch_location;

  SWITCH_STMT_BODY (cs->switch_stmt) = body;

  /* Emit warnings as needed.  */
  switch_location = ପଦସମଷ୍ଟି_LOCATION (cs->switch_stmt);
  c_do_switch_warnings (cs->cases, switch_location,
			type ? type : SWITCH_STMT_TYPE (cs->switch_stmt),
			SWITCH_STMT_COND (cs->switch_stmt), cs->bool_cond_p);
  ଯଦି (c_switch_covers_all_cases_p (cs->cases,
				   SWITCH_STMT_TYPE (cs->switch_stmt)))
    SWITCH_STMT_ALL_CASES_P (cs->switch_stmt) = 1;
  SWITCH_STMT_NO_BREAK_P (cs->switch_stmt) = !cs->break_stmt_seen_p;

  /* Pop the stack.  */
  c_switch_ଗଦା = cs->next;
  splay_ବୃକ୍ଷ_delete (cs->cases);
  c_release_switch_bindings (cs->bindings);
  XDELETE (cs);
}

/* Emit an if statement.  IF_LOCUS is the location of the 'if'.  COND,
   THEN_BLOCK and ELSE_BLOCK are expressions to be used; ELSE_BLOCK
   may be null.  */

ଶୂନ୍ୟ
c_finish_if_stmt (location_t if_locus, ବୃକ୍ଷ cond, ବୃକ୍ଷ then_block,
		  ବୃକ୍ଷ else_block)
{
  ବୃକ୍ଷ stmt;

  stmt = build3 (COND_ପଦସମଷ୍ଟି, void_type_ଗଣ୍ଠି, cond, then_block, else_block);
  SET_ପଦସମଷ୍ଟି_LOCATION (stmt, if_locus);
  add_stmt (stmt);
}

ବୃକ୍ଷ
c_finish_bc_stmt (location_t loc, ବୃକ୍ଷ label, ତାର୍କିକ is_break, ବୃକ୍ଷ name)
{
  /* In switch statements break is sometimes stylistically used after
     a return statement.  This can lead to spurious warnings about
     control reaching the end of a non-void function when it is
     inlined.  Note that we are calling block_may_fallthru with
     language specific tree nodes; this works because
     block_may_fallthru returns true when given something it does not
     understand.  */
  ତାର୍କିକ skip = !block_may_fallthru (cur_stmt_list);

  ଯଦି (is_break)
    ବାଛ (in_statement & ~IN_NAMED_STMT)
      {
      ସ୍ଥିତି 0:
	error_at (loc, "break statement not within loop or switch");
	ଫେରନ୍ତୁ NULL_ବୃକ୍ଷ;
      ସ୍ଥିତି IN_OMP_BLOCK:
	error_at (loc, "invalid exit from OpenMP structured block");
	ଫେରନ୍ତୁ NULL_ବୃକ୍ଷ;
      ସ୍ଥିତି IN_OMP_FOR:
	error_at (loc, "break statement used with OpenMP for loop");
	ଫେରନ୍ତୁ NULL_ବୃକ୍ଷ;
      ସ୍ଥିତି IN_ITERATION_STMT:
      ସ୍ଥିତି IN_OBJC_FOREACH:
	ଭାଙ୍ଗ;
      ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
	gcc_assert (in_statement & IN_SWITCH_STMT);
	c_switch_ଗଦା->break_stmt_seen_p = ସତ୍ୟ;
	ଭାଙ୍ଗ;
      }
  ଅନ୍ୟଥା
    ବାଛ (in_statement & ~(IN_SWITCH_STMT | IN_NAMED_STMT))
      {
      ସ୍ଥିତି 0:
	error_at (loc, "continue statement not within a loop");
	ଫେରନ୍ତୁ NULL_ବୃକ୍ଷ;
      ସ୍ଥିତି IN_OMP_BLOCK:
	error_at (loc, "invalid exit from OpenMP structured block");
	ଫେରନ୍ତୁ NULL_ବୃକ୍ଷ;
      ସ୍ଥିତି IN_ITERATION_STMT:
      ସ୍ଥିତି IN_OMP_FOR:
      ସ୍ଥିତି IN_OBJC_FOREACH:
	ଭାଙ୍ଗ;
      ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
	gcc_unreachable ();
      }

  ଯଦି (skip)
    ଫେରନ୍ତୁ NULL_ବୃକ୍ଷ;
  ଅନ୍ୟଥା ଯଦି ((in_statement & IN_OBJC_FOREACH)
	   && !(is_break && (in_statement & IN_SWITCH_STMT))
	   && name == NULL_ବୃକ୍ଷ)
    {
      /* The foreach expander produces low-level code using gotos instead
	 of a structured loop construct.  */
      gcc_assert (label);
      ଫେରନ୍ତୁ add_stmt (build_stmt (loc, GOTO_ପଦସମଷ୍ଟି, label));
    }
  ଅନ୍ୟଥା ଯଦି (name && C_DECL_LOOP_NAME (name) && C_DECL_SWITCH_NAME (name))
    {
      label = DECL_CHAIN (name);
      ଯଦି (!is_break)
	label = DECL_CHAIN (label);
      /* Foreach expander from some outer level.  */
      ଫେରନ୍ତୁ add_stmt (build_stmt (loc, GOTO_ପଦସମଷ୍ଟି, label));
    }
  ଫେରନ୍ତୁ add_stmt (build_stmt (loc, is_break ? BREAK_STMT : CONTINUE_STMT,
			       name));
}

/* A helper routine for c_process_expr_stmt and c_finish_stmt_expr.  */

ସ୍ଥିର ଶୂନ୍ୟ
emit_side_effect_warnings (location_t loc, ବୃକ୍ଷ ପଦସମଷ୍ଟି)
{
  maybe_warn_nodiscard (loc, ପଦସମଷ୍ଟି);
  ଯଦି (!warn_unused_ମୂଲ୍ୟ)
    ଫେରନ୍ତୁ;
  ଯଦି (ପଦସମଷ୍ଟି == error_mark_ଗଣ୍ଠି)
    ;
  ଅନ୍ୟଥା ଯଦି (!ବୃକ୍ଷ_SIDE_EFFECTS (ପଦସମଷ୍ଟି))
    {
      ଯଦି (!VOID_TYPE_P (ବୃକ୍ଷ_TYPE (ପଦସମଷ୍ଟି))
	  && !warning_suppressed_p (ପଦସମଷ୍ଟି, OPT_Wunused_ମୂଲ୍ୟ))
	warning_at (loc, OPT_Wunused_ମୂଲ୍ୟ, "statement with no effect");
    }
  ଅନ୍ୟଥା ଯଦି (ବୃକ୍ଷ_CODE (ପଦସମଷ୍ଟି) == COMPOUND_ପଦସମଷ୍ଟି)
    {
      ବୃକ୍ଷ r = ପଦସମଷ୍ଟି;
      location_t cloc = loc;
      ଯେତେବେଳେ (ବୃକ୍ଷ_CODE (r) == COMPOUND_ପଦସମଷ୍ଟି)
	{
	  ଯଦି (ପଦସମଷ୍ଟି_HAS_LOCATION (r))
	    cloc = ପଦସମଷ୍ଟି_LOCATION (r);
	  r = ବୃକ୍ଷ_OPERAND (r, 1);
	}
      ଯଦି (!ବୃକ୍ଷ_SIDE_EFFECTS (r)
	  && !VOID_TYPE_P (ବୃକ୍ଷ_TYPE (r))
	  && !CONVERT_ପଦସମଷ୍ଟି_P (r)
	  && !warning_suppressed_p (r, OPT_Wunused_ମୂଲ୍ୟ)
	  && !warning_suppressed_p (ପଦସମଷ୍ଟି, OPT_Wunused_ମୂଲ୍ୟ))
	warning_at (cloc, OPT_Wunused_ମୂଲ୍ୟ,
		    "right-hand operand of comma expression has no effect");
    }
  ଅନ୍ୟଥା
    warn_if_unused_ମୂଲ୍ୟ (ପଦସମଷ୍ଟି, loc);
}

/* Process an expression as if it were a complete statement.  Emit
   diagnostics, but do not call ADD_STMT.  LOC is the location of the
   statement.  */

ବୃକ୍ଷ
c_process_ପଦସମଷ୍ଟି_stmt (location_t loc, ବୃକ୍ଷ ପଦସମଷ୍ଟି)
{
  ବୃକ୍ଷ exprv;

  ଯଦି (!ପଦସମଷ୍ଟି)
    ଫେରନ୍ତୁ NULL_ବୃକ୍ଷ;

  ପଦସମଷ୍ଟି = c_fully_fold (ପଦସମଷ୍ଟି, ମିଥ୍ୟା, ଖାଲି);

  ଯଦି (warn_sequence_point)
    verify_sequence_points (ପଦସମଷ୍ଟି);

  ଯଦି (ବୃକ୍ଷ_TYPE (ପଦସମଷ୍ଟି) != error_mark_ଗଣ୍ଠି
      && !COMPLETE_OR_VOID_TYPE_P (ବୃକ୍ଷ_TYPE (ପଦସମଷ୍ଟି))
      && ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (ପଦସମଷ୍ଟି)) != ARRAY_TYPE)
    error_at (loc, "expression statement has incomplete type");

  /* If we're not processing a statement expression, warn about unused values.
     Warnings for statement expressions will be emitted later, once we figure
     out which is the result.  */
  ଯଦି (!STATEMENT_LIST_STMT_ପଦସମଷ୍ଟି (cur_stmt_list)
      && (warn_unused_ମୂଲ୍ୟ || warn_unused_result))
    emit_side_effect_warnings (ପଦସମଷ୍ଟି_LOC_OR_LOC (ପଦସମଷ୍ଟି, loc), ପଦସମଷ୍ଟି);

  exprv = ପଦସମଷ୍ଟି;
  ଯେତେବେଳେ (ବୃକ୍ଷ_CODE (exprv) == COMPOUND_ପଦସମଷ୍ଟି)
    exprv = ବୃକ୍ଷ_OPERAND (exprv, 1);
  ଯେତେବେଳେ (CONVERT_ପଦସମଷ୍ଟି_P (exprv))
    exprv = ବୃକ୍ଷ_OPERAND (exprv, 0);
  ଯଦି (DECL_P (exprv)
      || handled_component_p (exprv)
      || ବୃକ୍ଷ_CODE (exprv) == ADDR_ପଦସମଷ୍ଟି)
    mark_exp_read (exprv);

  /* If the expression is not of a type to which we cannot assign a line
     number, wrap the thing in a no-op NOP_EXPR.  */
  ଯଦି (DECL_P (ପଦସମଷ୍ଟି) || CONSTANT_CLASS_P (ପଦସମଷ୍ଟି))
    {
      ପଦସମଷ୍ଟି = build1 (NOP_ପଦସମଷ୍ଟି, ବୃକ୍ଷ_TYPE (ପଦସମଷ୍ଟି), ପଦସମଷ୍ଟି);
      SET_ପଦସମଷ୍ଟି_LOCATION (ପଦସମଷ୍ଟି, loc);
    }

  ଫେରନ୍ତୁ ପଦସମଷ୍ଟି;
}

/* Emit an expression as a statement.  LOC is the location of the
   expression.  */

ବୃକ୍ଷ
c_finish_ପଦସମଷ୍ଟି_stmt (location_t loc, ବୃକ୍ଷ ପଦସମଷ୍ଟି)
{
  ଯଦି (ପଦସମଷ୍ଟି)
    ଫେରନ୍ତୁ add_stmt (c_process_ପଦସମଷ୍ଟି_stmt (loc, ପଦସମଷ୍ଟି));
  ଅନ୍ୟଥା
    ଫେରନ୍ତୁ ଖାଲି;
}

/* Do the opposite and emit a statement as an expression.  To begin,
   create a new binding level and return it.  */

ବୃକ୍ଷ
c_begin_stmt_ପଦସମଷ୍ଟି (ଶୂନ୍ୟ)
{
  ବୃକ୍ଷ ret;

  /* We must force a BLOCK for this level so that, if it is not expanded
     later, there is a way to turn off the entire subtree of blocks that
     are contained in it.  */
  keep_next_level ();
  ret = c_begin_compound_stmt (ସତ୍ୟ);

  c_bindings_start_stmt_ପଦସମଷ୍ଟି (c_switch_ଗଦା == ଖାଲି
			      ? ଖାଲି
			      : c_switch_ଗଦା->bindings);

  /* Mark the current statement list as belonging to a statement list.  */
  STATEMENT_LIST_STMT_ପଦସମଷ୍ଟି (ret) = 1;

  ଫେରନ୍ତୁ ret;
}

/* LOC is the location of the compound statement to which this body
   belongs.  */

ବୃକ୍ଷ
c_finish_stmt_ପଦସମଷ୍ଟି (location_t loc, ବୃକ୍ଷ body)
{
  ବୃକ୍ଷ last, type, tmp, val;
  ବୃକ୍ଷ *last_p;

  body = c_end_compound_stmt (loc, body, ସତ୍ୟ);

  c_bindings_end_stmt_ପଦସମଷ୍ଟି (c_switch_ଗଦା == ଖାଲି
			    ? ଖାଲି
			    : c_switch_ଗଦା->bindings);

  /* Locate the last statement in BODY.  See c_end_compound_stmt
     about always returning a BIND_EXPR.  */
  last_p = &BIND_ପଦସମଷ୍ଟି_BODY (body);
  last = BIND_ପଦସମଷ୍ଟି_BODY (body);

 continue_searching:
  ଯଦି (ବୃକ୍ଷ_CODE (last) == STATEMENT_LIST)
    {
      ବୃକ୍ଷ_stmt_iterator l = tsi_last (last);

      ଯେତେବେଳେ (!tsi_end_p (l) && ବୃକ୍ଷ_CODE (tsi_stmt (l)) == DEBUG_BEGIN_STMT)
	tsi_prev (&l);

      /* This can happen with degenerate cases like ({ }).  No value.  */
      ଯଦି (tsi_end_p (l))
	ଫେରନ୍ତୁ body;

      /* If we're supposed to generate side effects warnings, process
	 all of the statements except the last.  */
      ଯଦି (warn_unused_ମୂଲ୍ୟ || warn_unused_result)
	{
	  ପାଇଁ (ବୃକ୍ଷ_stmt_iterator i = tsi_start (last);
	       tsi_stmt (i) != tsi_stmt (l); tsi_next (&i))
	    {
	      location_t tloc;
	      ବୃକ୍ଷ t = tsi_stmt (i);

	      tloc = ପଦସମଷ୍ଟି_HAS_LOCATION (t) ? ପଦସମଷ୍ଟି_LOCATION (t) : loc;
	      emit_side_effect_warnings (tloc, t);
	    }
	}
      last_p = tsi_stmt_ptr (l);
      last = *last_p;
    }

  /* If the end of the list is exception related, then the list was split
     by a call to push_cleanup.  Continue searching.  */
  ଯଦି (ବୃକ୍ଷ_CODE (last) == TRY_FINALLY_ପଦସମଷ୍ଟି
      || ବୃକ୍ଷ_CODE (last) == TRY_CATCH_ପଦସମଷ୍ଟି)
    {
      last_p = &ବୃକ୍ଷ_OPERAND (last, 0);
      last = *last_p;
      ଯାଅ continue_searching;
    }

  ଯଦି (last == error_mark_ଗଣ୍ଠି)
    ଫେରନ୍ତୁ last;

  /* In the case that the BIND_EXPR is not necessary, return the
     expression out from inside it.  */
  ଯଦି ((last == BIND_ପଦସମଷ୍ଟି_BODY (body)
       /* Skip nested debug stmts.  */
       || last == ପଦସମଷ୍ଟି_first (BIND_ପଦସମଷ୍ଟି_BODY (body)))
      && BIND_ପଦସମଷ୍ଟି_VARS (body) == ଖାଲି)
    {
      /* Even if this looks constant, do not allow it in a constant
	 expression.  */
      last = c_wrap_maybe_const (last, ସତ୍ୟ);
      /* Do not warn if the return value of a statement expression is
	 unused.  */
      suppress_warning (last, OPT_Wunused);
      ଫେରନ୍ତୁ last;
    }

  /* Extract the type of said expression.  */
  type = ବୃକ୍ଷ_TYPE (last);

  /* If we're not returning a value at all, then the BIND_EXPR that
     we already have is a fine expression to return.  */
  ଯଦି (!type || VOID_TYPE_P (type))
    ଫେରନ୍ତୁ body;

  /* Now that we've located the expression containing the value, it seems
     silly to make voidify_wrapper_expr repeat the process.  Create a
     temporary of the appropriate type and stick it in a TARGET_EXPR.  */
  tmp = create_tmp_var_raw (type);

  /* Unwrap a no-op NOP_EXPR as added by c_finish_expr_stmt.  This avoids
     tree_expr_nonnegative_p giving up immediately.  */
  val = last;
  ଯଦି (ବୃକ୍ଷ_CODE (val) == NOP_ପଦସମଷ୍ଟି
      && ବୃକ୍ଷ_TYPE (val) == ବୃକ୍ଷ_TYPE (ବୃକ୍ଷ_OPERAND (val, 0)))
    val = ବୃକ୍ଷ_OPERAND (val, 0);

  *last_p = build2 (MODIFY_ପଦସମଷ୍ଟି, void_type_ଗଣ୍ଠି, tmp, val);
  SET_ପଦସମଷ୍ଟି_LOCATION (*last_p, ପଦସମଷ୍ଟି_LOCATION (last));

  {
    ବୃକ୍ଷ t = build4 (TARGET_ପଦସମଷ୍ଟି, type, tmp, body, NULL_ବୃକ୍ଷ, NULL_ବୃକ୍ଷ);
    SET_ପଦସମଷ୍ଟି_LOCATION (t, loc);
    ଫେରନ୍ତୁ t;
  }
}

/* Begin and end compound statements.  This is as simple as pushing
   and popping new statement lists from the tree.  */

ବୃକ୍ଷ
c_begin_compound_stmt (ତାର୍କିକ do_scope)
{
  ବୃକ୍ଷ stmt = ଠେଲ_stmt_list ();
  ଯଦି (do_scope)
    ଠେଲ_scope ();
  ଫେରନ୍ତୁ stmt;
}

/* End a compound statement.  STMT is the statement.  LOC is the
   location of the compound statement-- this is usually the location
   of the opening brace.  */

ବୃକ୍ଷ
c_end_compound_stmt (location_t loc, ବୃକ୍ଷ stmt, ତାର୍କିକ do_scope)
{
  ବୃକ୍ଷ block = ଖାଲି;

  ଯଦି (do_scope)
    {
      ଯଦି (c_dialect_objc ())
	objc_clear_super_receiver ();
      block = କାଢ଼_scope ();
    }

  stmt = କାଢ଼_stmt_list (stmt);
  stmt = c_build_bind_ପଦସମଷ୍ଟି (loc, block, stmt);

  /* If this compound statement is nested immediately inside a statement
     expression, then force a BIND_EXPR to be created.  Otherwise we'll
     do the wrong thing for ({ { 1; } }) or ({ 1; { } }).  In particular,
     STATEMENT_LISTs merge, and thus we can lose track of what statement
     was really last.  */
  ଯଦି (building_stmt_list_p ()
      && STATEMENT_LIST_STMT_ପଦସମଷ୍ଟି (cur_stmt_list)
      && ବୃକ୍ଷ_CODE (stmt) != BIND_ପଦସମଷ୍ଟି)
    {
      stmt = build3 (BIND_ପଦସମଷ୍ଟି, void_type_ଗଣ୍ଠି, ଖାଲି, stmt, ଖାଲି);
      ବୃକ୍ଷ_SIDE_EFFECTS (stmt) = 1;
      SET_ପଦସମଷ୍ଟି_LOCATION (stmt, loc);
    }

  ଫେରନ୍ତୁ stmt;
}

/* Queue a cleanup.  CLEANUP is an expression/statement to be executed
   when the current scope is exited.  EH_ONLY is true when this is not
   meant to apply to normal control flow transfer.  */

ଶୂନ୍ୟ
ଠେଲ_cleanup (ବୃକ୍ଷ decl, ବୃକ୍ଷ cleanup, ତାର୍କିକ eh_only)
{
  ଗଣନା ବୃକ୍ଷ_code code;
  ବୃକ୍ଷ stmt, list;
  ତାର୍କିକ stmt_ପଦସମଷ୍ଟି;

  code = eh_only ? TRY_CATCH_ପଦସମଷ୍ଟି : TRY_FINALLY_ପଦସମଷ୍ଟି;
  stmt = build_stmt (DECL_SOURCE_LOCATION (decl), code, ଖାଲି, cleanup);
  add_stmt (stmt);
  stmt_ପଦସମଷ୍ଟି = STATEMENT_LIST_STMT_ପଦସମଷ୍ଟି (cur_stmt_list);
  list = ଠେଲ_stmt_list ();
  ବୃକ୍ଷ_OPERAND (stmt, 0) = list;
  STATEMENT_LIST_STMT_ପଦସମଷ୍ଟି (list) = stmt_ପଦସମଷ୍ଟି;
}

/* Build a vector comparison of ARG0 and ARG1 using CODE opcode
   into a value of TYPE type.  Comparison is done via VEC_COND_EXPR.  */

ସ୍ଥିର ବୃକ୍ଷ
build_vec_cmp (ବୃକ୍ଷ_code code, ବୃକ୍ଷ type,
	       ବୃକ୍ଷ arg0, ବୃକ୍ଷ arg1)
{
  ବୃକ୍ଷ zero_vec = build_zero_cst (type);
  ବୃକ୍ଷ minus_one_vec = build_minus_one_cst (type);
  ବୃକ୍ଷ cmp_type = truth_type_for (ବୃକ୍ଷ_TYPE (arg0));
  ବୃକ୍ଷ cmp = build2 (code, cmp_type, arg0, arg1);
  ଫେରନ୍ତୁ build3 (VEC_COND_ପଦସମଷ୍ଟି, type, cmp, minus_one_vec, zero_vec);
}

/* Possibly warn about an address of OP never being NULL in a comparison
   operation CODE involving null.  */

ସ୍ଥିର ଶୂନ୍ୟ
maybe_warn_for_null_address (location_t loc, ବୃକ୍ଷ op, ବୃକ୍ଷ_code code)
{
  /* Prevent warnings issued for macro expansion.  */
  ଯଦି (!warn_address
      || warning_suppressed_p (op, OPT_Waddress)
      || from_macro_expansion_at (loc))
    ଫେରନ୍ତୁ;

  ଯଦି (ବୃକ୍ଷ_CODE (op) == NOP_ପଦସମଷ୍ଟି)
    {
      /* Allow casts to intptr_t to suppress the warning.  */
      ବୃକ୍ଷ type = ବୃକ୍ଷ_TYPE (op);
      ଯଦି (ବୃକ୍ଷ_CODE (type) == INTEGER_TYPE)
	ଫେରନ୍ତୁ;
      op = ବୃକ୍ଷ_OPERAND (op, 0);
    }

  ଯଦି (ବୃକ୍ଷ_CODE (op) == POINTER_PLUS_ପଦସମଷ୍ଟି)
    {
      /* Allow a cast to void* to suppress the warning.  */
      ବୃକ୍ଷ type = ବୃକ୍ଷ_TYPE (ବୃକ୍ଷ_TYPE (op));
      ଯଦି (VOID_TYPE_P (type))
	ଫେରନ୍ତୁ;

      /* Adding any value to a null pointer, including zero, is undefined
	 in C.  This includes the expression &p[0] where p is the null
	 pointer, although &p[0] will have been folded to p by this point
	 and so not diagnosed.  */
      ଯଦି (code == EQ_ପଦସମଷ୍ଟି)
	warning_at (loc, OPT_Waddress,
		    "the comparison will always evaluate as %<false%> "
		    "for the pointer operand in %qE must not be NULL",
		    op);
      ଅନ୍ୟଥା
	warning_at (loc, OPT_Waddress,
		    "the comparison will always evaluate as %<true%> "
		    "for the pointer operand in %qE must not be NULL",
		    op);

      ଫେରନ୍ତୁ;
    }

  ଯଦି (ବୃକ୍ଷ_CODE (op) != ADDR_ପଦସମଷ୍ଟି)
    ଫେରନ୍ତୁ;

  op = ବୃକ୍ଷ_OPERAND (op, 0);

  ଯଦି (ବୃକ୍ଷ_CODE (op) == IMAGPART_ପଦସମଷ୍ଟି
      || ବୃକ୍ଷ_CODE (op) == REALPART_ପଦସମଷ୍ଟି)
    {
      /* The address of either complex part may not be null.  */
      ଯଦି (code == EQ_ପଦସମଷ୍ଟି)
	warning_at (loc, OPT_Waddress,
		    "the comparison will always evaluate as %<false%> "
		    "for the address of %qE will never be NULL",
		    op);
      ଅନ୍ୟଥା
	warning_at (loc, OPT_Waddress,
		    "the comparison will always evaluate as %<true%> "
		    "for the address of %qE will never be NULL",
		    op);
      ଫେରନ୍ତୁ;
    }

  /* Set to true in the loop below if OP dereferences is operand.
     In such a case the ultimate target need not be a decl for
     the null [in]equality test to be constant.  */
  ତାର୍କିକ deref = ମିଥ୍ୟା;

  /* Get the outermost array or object, or member.  */
  ଯେତେବେଳେ (handled_component_p (op))
    {
      ଯଦି (ବୃକ୍ଷ_CODE (op) == COMPONENT_REF)
	{
	  /* Get the member (its address is never null).  */
	  op = ବୃକ୍ଷ_OPERAND (op, 1);
	  ଭାଙ୍ଗ;
	}

      /* Get the outer array/object to refer to in the warning.  */
      op = ବୃକ୍ଷ_OPERAND (op, 0);
      deref = ସତ୍ୟ;
    }

  ଯଦି ((!deref && !decl_with_nonnull_addr_p (op))
      || from_macro_expansion_at (loc))
    ଫେରନ୍ତୁ;

  ତାର୍କିକ w;
  ଯଦି (code == EQ_ପଦସମଷ୍ଟି)
    w = warning_at (loc, OPT_Waddress,
		    "the comparison will always evaluate as %<false%> "
		    "for the address of %qE will never be NULL",
		    op);
  ଅନ୍ୟଥା
    w = warning_at (loc, OPT_Waddress,
		    "the comparison will always evaluate as %<true%> "
		    "for the address of %qE will never be NULL",
		    op);

  ଯଦି (w && DECL_P (op))
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

ବୃକ୍ଷ
build_ଦ୍ୱିମିକ_op (location_t location, ଗଣନା ବୃକ୍ଷ_code code,
		 ବୃକ୍ଷ orig_op0, ବୃକ୍ଷ orig_op1, ତାର୍କିକ convert_p)
{
  ବୃକ୍ଷ type0, type1, orig_type0, orig_type1;
  ବୃକ୍ଷ eptype;
  ଗଣନା ବୃକ୍ଷ_code code0, code1;
  ବୃକ୍ଷ op0, op1;
  ବୃକ୍ଷ ret = error_mark_ଗଣ୍ଠି;
  ଅଚଳ ଅକ୍ଷର *invalid_op_diag;
  ତାର୍କିକ op0_int_operands, op1_int_operands;
  ତାର୍କିକ int_const, int_const_or_overflow, int_operands;

  /* Expression code to give to the expression when it is built.
     Normally this is CODE, which is what the caller asked for,
     but in some special cases we change it.  */
  ଗଣନା ବୃକ୍ଷ_code resultcode = code;

  /* Data type in which the computation is to be performed.
     In the simplest cases this is the common type of the arguments.  */
  ବୃକ୍ଷ result_type = ଖାଲି;

  /* When the computation is in excess precision, the type of the
     final EXCESS_PRECISION_EXPR.  */
  ବୃକ୍ଷ semantic_result_type = ଖାଲି;

  /* Nonzero means operands have already been type-converted
     in whatever way is necessary.
     Zero means they need to be converted to RESULT_TYPE.  */
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା converted = 0;

  /* Nonzero means create the expression with this type, rather than
     RESULT_TYPE.  */
  ବୃକ୍ଷ build_type = NULL_ବୃକ୍ଷ;

  /* Nonzero means after finally constructing the expression
     convert it to this type.  */
  ବୃକ୍ଷ final_type = NULL_ବୃକ୍ଷ;

  /* Nonzero if this is an operation like MIN or MAX which can
     safely be computed in short if both args are promoted shorts.
     Also implies COMMON.
     -1 indicates a bitwise operation; this makes a difference
     in the exact conditions for when it is safe to do the operation
     in a narrower mode.  */
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା shorten = 0;

  /* Nonzero if this is a comparison operation;
     if both args are promoted shorts, compare the original shorts.
     Also implies COMMON.  */
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା short_compare = 0;

  /* Nonzero if this is a right-shift operation, which can be computed on the
     original short and then promoted if the operand is a promoted short.  */
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା short_shift = 0;

  /* Nonzero means set RESULT_TYPE to the common type of the args.  */
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା common = 0;

  /* True means types are compatible as far as ObjC is concerned.  */
  ତାର୍କିକ objc_ok;

  /* True means this is an arithmetic operation that may need excess
     precision.  */
  ତାର୍କିକ may_need_excess_precision;

  /* True means this is a boolean operation that converts both its
     operands to truth-values.  */
  ତାର୍କିକ boolean_op = ମିଥ୍ୟା;

  /* Remember whether we're doing / or %.  */
  ତାର୍କିକ doing_div_or_mod = ମିଥ୍ୟା;

  /* Remember whether we're doing << or >>.  */
  ତାର୍କିକ doing_shift = ମିଥ୍ୟା;

  /* Tree holding instrumentation expression.  */
  ବୃକ୍ଷ instrument_ପଦସମଷ୍ଟି = ଖାଲି;

  ଯଦି (location == UNKNOWN_LOCATION)
    location = ନିବେଶ_location;

  op0 = orig_op0;
  op1 = orig_op1;

  op0_int_operands = ପଦସମଷ୍ଟି_INT_CONST_OPERANDS (orig_op0);
  ଯଦି (op0_int_operands)
    op0 = remove_c_maybe_const_ପଦସମଷ୍ଟି (op0);
  op1_int_operands = ପଦସମଷ୍ଟି_INT_CONST_OPERANDS (orig_op1);
  ଯଦି (op1_int_operands)
    op1 = remove_c_maybe_const_ପଦସମଷ୍ଟି (op1);
  int_operands = (op0_int_operands && op1_int_operands);
  ଯଦି (int_operands)
    {
      int_const_or_overflow = (ବୃକ୍ଷ_CODE (orig_op0) == INTEGER_CST
			       && ବୃକ୍ଷ_CODE (orig_op1) == INTEGER_CST);
      int_const = (int_const_or_overflow
		   && !ବୃକ୍ଷ_OVERFLOW (orig_op0)
		   && !ବୃକ୍ଷ_OVERFLOW (orig_op1));
    }
  ଅନ୍ୟଥା
    int_const = int_const_or_overflow = ମିଥ୍ୟା;

  /* Do not apply default conversion in mixed vector/scalar expression.  */
  ଯଦି (convert_p
      && VECTOR_TYPE_P (ବୃକ୍ଷ_TYPE (op0)) == VECTOR_TYPE_P (ବୃକ୍ଷ_TYPE (op1)))
    {
      op0 = default_conversion (op0);
      op1 = default_conversion (op1);
    }

  orig_type0 = type0 = ବୃକ୍ଷ_TYPE (op0);

  orig_type1 = type1 = ବୃକ୍ଷ_TYPE (op1);

  /* The expression codes of the data types of the arguments tell us
     whether the arguments are integers, floating, pointers, etc.  */
  code0 = ବୃକ୍ଷ_CODE (type0);
  code1 = ବୃକ୍ଷ_CODE (type1);

  /* Strip NON_LVALUE_EXPRs, etc., since we aren't using as an lvalue.  */
  STRIP_TYPE_NOPS (op0);
  STRIP_TYPE_NOPS (op1);

  /* If an error was already reported for one of the arguments,
     avoid reporting another error.  */

  ଯଦି (code0 == ERROR_MARK || code1 == ERROR_MARK)
    ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;

  ଯଦି (code0 == POINTER_TYPE
      && reject_gcc_builtin (op0, ପଦସମଷ୍ଟି_LOCATION (orig_op0)))
    ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;

  ଯଦି (code1 == POINTER_TYPE
      && reject_gcc_builtin (op1, ପଦସମଷ୍ଟି_LOCATION (orig_op1)))
    ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;

  ଯଦି ((invalid_op_diag
       = targetm.invalid_ଦ୍ୱିମିକ_op (code, type0, type1)))
    {
      error_at (location, invalid_op_diag);
      ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
    }

  ବାଛ (code)
    {
    ସ୍ଥିତି PLUS_ପଦସମଷ୍ଟି:
    ସ୍ଥିତି MINUS_ପଦସମଷ୍ଟି:
    ସ୍ଥିତି MULT_ପଦସମଷ୍ଟି:
    ସ୍ଥିତି TRUNC_DIV_ପଦସମଷ୍ଟି:
    ସ୍ଥିତି CEIL_DIV_ପଦସମଷ୍ଟି:
    ସ୍ଥିତି FLOOR_DIV_ପଦସମଷ୍ଟି:
    ସ୍ଥିତି ROUND_DIV_ପଦସମଷ୍ଟି:
    ସ୍ଥିତି EXACT_DIV_ପଦସମଷ୍ଟି:
      may_need_excess_precision = ସତ୍ୟ;
      ଭାଙ୍ଗ;

    ସ୍ଥିତି EQ_ପଦସମଷ୍ଟି:
    ସ୍ଥିତି NE_ପଦସମଷ୍ଟି:
    ସ୍ଥିତି LE_ପଦସମଷ୍ଟି:
    ସ୍ଥିତି GE_ପଦସମଷ୍ଟି:
    ସ୍ଥିତି LT_ପଦସମଷ୍ଟି:
    ସ୍ଥିତି GT_ପଦସମଷ୍ଟି:
      /* Excess precision for implicit conversions of integers to
	 floating point in C11 and later.  */
      may_need_excess_precision = (flag_isoc11
				   && (ANY_INTEGRAL_TYPE_P (type0)
				       || ANY_INTEGRAL_TYPE_P (type1)));
      ଭାଙ୍ଗ;

    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
      may_need_excess_precision = ମିଥ୍ୟା;
      ଭାଙ୍ଗ;
    }
  ଯଦି (ବୃକ୍ଷ_CODE (op0) == EXCESS_PRECISION_ପଦସମଷ୍ଟି)
    {
      op0 = ବୃକ୍ଷ_OPERAND (op0, 0);
      type0 = ବୃକ୍ଷ_TYPE (op0);
    }
  ଅନ୍ୟଥା ଯଦି (may_need_excess_precision
	   && (eptype = excess_precision_type (type0)) != NULL_ବୃକ୍ଷ)
    {
      type0 = eptype;
      op0 = convert (eptype, op0);
    }
  ଯଦି (ବୃକ୍ଷ_CODE (op1) == EXCESS_PRECISION_ପଦସମଷ୍ଟି)
    {
      op1 = ବୃକ୍ଷ_OPERAND (op1, 0);
      type1 = ବୃକ୍ଷ_TYPE (op1);
    }
  ଅନ୍ୟଥା ଯଦି (may_need_excess_precision
	   && (eptype = excess_precision_type (type1)) != NULL_ବୃକ୍ଷ)
    {
      type1 = eptype;
      op1 = convert (eptype, op1);
    }

  objc_ok = objc_compare_types (type0, type1, -3, NULL_ବୃକ୍ଷ);

  /* In case when one of the operands of the binary operation is
     a vector and another is a scalar -- convert scalar to vector.  */
  ଯଦି ((gnu_vector_type_p (type0) && code1 != VECTOR_TYPE)
      || (gnu_vector_type_p (type1) && code0 != VECTOR_TYPE))
    {
      ଗଣନା stv_conv convert_flag = scalar_to_vector (location, code, orig_op0,
						     orig_op1, ସତ୍ୟ);

      ବାଛ (convert_flag)
	{
	  ସ୍ଥିତି stv_error:
	    ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
	  ସ୍ଥିତି stv_firstarg:
	    {
              ତାର୍କିକ maybe_const = ସତ୍ୟ;
              ବୃକ୍ଷ sc;
              sc = c_fully_fold (op0, ମିଥ୍ୟା, &maybe_const);
              sc = save_ପଦସମଷ୍ଟି (sc);
              sc = convert (ବୃକ୍ଷ_TYPE (type1), sc);
              op0 = build_vector_from_val (type1, sc);
              ଯଦି (!maybe_const)
                op0 = c_wrap_maybe_const (op0, ସତ୍ୟ);
              orig_type0 = type0 = ବୃକ୍ଷ_TYPE (op0);
              code0 = ବୃକ୍ଷ_CODE (type0);
              converted = 1;
              ଭାଙ୍ଗ;
	    }
	  ସ୍ଥିତି stv_secondarg:
	    {
	      ତାର୍କିକ maybe_const = ସତ୍ୟ;
	      ବୃକ୍ଷ sc;
	      sc = c_fully_fold (op1, ମିଥ୍ୟା, &maybe_const);
	      sc = save_ପଦସମଷ୍ଟି (sc);
	      sc = convert (ବୃକ୍ଷ_TYPE (type0), sc);
	      op1 = build_vector_from_val (type0, sc);
	      ଯଦି (!maybe_const)
		op1 = c_wrap_maybe_const (op1, ସତ୍ୟ);
	      orig_type1 = type1 = ବୃକ୍ଷ_TYPE (op1);
	      code1 = ବୃକ୍ଷ_CODE (type1);
	      converted = 1;
	      ଭାଙ୍ଗ;
	    }
	  ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
	    ଭାଙ୍ଗ;
	}
    }

  ବାଛ (code)
    {
    ସ୍ଥିତି PLUS_ପଦସମଷ୍ଟି:
      /* Handle the pointer + int case.  */
      ଯଦି (code0 == POINTER_TYPE
	  && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  ret = pointer_int_sum (location, PLUS_ପଦସମଷ୍ଟି, op0, op1);
	  ଯାଅ return_build_ଦ୍ୱିମିକ_op;
	}
      ଅନ୍ୟଥା ଯଦି (code1 == POINTER_TYPE
	       && (code0 == INTEGER_TYPE || code0 == BITINT_TYPE))
	{
	  ret = pointer_int_sum (location, PLUS_ପଦସମଷ୍ଟି, op1, op0);
	  ଯାଅ return_build_ଦ୍ୱିମିକ_op;
	}
      ଅନ୍ୟଥା
	common = 1;
      ଭାଙ୍ଗ;

    ସ୍ଥିତି MINUS_ପଦସମଷ୍ଟି:
      /* Subtraction of two similar pointers.
	 We must subtract them as integers, then divide by object size.  */
      ଯଦି (code0 == POINTER_TYPE && code1 == POINTER_TYPE
	  && comp_target_types (location, type0, type1))
	{
	  ret = pointer_diff (location, op0, op1, &instrument_ପଦସମଷ୍ଟି);
	  ଯାଅ return_build_ଦ୍ୱିମିକ_op;
	}
      /* Handle pointer minus int.  Just like pointer plus int.  */
      ଅନ୍ୟଥା ଯଦି (code0 == POINTER_TYPE
	       && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  ret = pointer_int_sum (location, MINUS_ପଦସମଷ୍ଟି, op0, op1);
	  ଯାଅ return_build_ଦ୍ୱିମିକ_op;
	}
      ଅନ୍ୟଥା
	common = 1;
      ଭାଙ୍ଗ;

    ସ୍ଥିତି MULT_ପଦସମଷ୍ଟି:
      common = 1;
      ଭାଙ୍ଗ;

    ସ୍ଥିତି TRUNC_DIV_ପଦସମଷ୍ଟି:
    ସ୍ଥିତି CEIL_DIV_ପଦସମଷ୍ଟି:
    ସ୍ଥିତି FLOOR_DIV_ପଦସମଷ୍ଟି:
    ସ୍ଥିତି ROUND_DIV_ପଦସମଷ୍ଟି:
    ସ୍ଥିତି EXACT_DIV_ପଦସମଷ୍ଟି:
      doing_div_or_mod = ସତ୍ୟ;
      warn_for_div_by_zero (location, op1);

      ଯଦି ((code0 == INTEGER_TYPE || code0 == REAL_TYPE
	   || code0 == FIXED_POINT_TYPE || code0 == BITINT_TYPE
	   || code0 == COMPLEX_TYPE
	   || gnu_vector_type_p (type0))
	  && (code1 == INTEGER_TYPE || code1 == REAL_TYPE
	      || code1 == FIXED_POINT_TYPE || code1 == BITINT_TYPE
	      || code1 == COMPLEX_TYPE
	      || gnu_vector_type_p (type1)))
	{
	  ଗଣନା ବୃକ୍ଷ_code tcode0 = code0, tcode1 = code1;

	  ଯଦି (code0 == COMPLEX_TYPE || code0 == VECTOR_TYPE)
	    tcode0 = ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (ବୃକ୍ଷ_TYPE (op0)));
	  ଯଦି (code1 == COMPLEX_TYPE || code1 == VECTOR_TYPE)
	    tcode1 = ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (ବୃକ୍ଷ_TYPE (op1)));

	  ଯଦି (!(((tcode0 == INTEGER_TYPE || tcode0 == BITINT_TYPE
		  || (tcode0 == ENUMERAL_TYPE && code0 == VECTOR_TYPE))
		 && (tcode1 == INTEGER_TYPE || tcode1 == BITINT_TYPE
		     || (tcode1 == ENUMERAL_TYPE && code1 == VECTOR_TYPE)))
		|| (tcode0 == FIXED_POINT_TYPE && tcode1 == FIXED_POINT_TYPE)))
	    resultcode = RDIV_ପଦସମଷ୍ଟି;
	  ଅନ୍ୟଥା
	    /* Although it would be tempting to shorten always here, that
	       loses on some targets, since the modulo instruction is
	       undefined if the quotient can't be represented in the
	       computation mode.  We shorten only if unsigned or if
	       dividing by something we know != -1.  */
	    shorten = may_shorten_divmod (op0, op1);
	  common = 1;
	}
      ଭାଙ୍ଗ;

    ସ୍ଥିତି BIT_AND_ପଦସମଷ୍ଟି:
    ସ୍ଥିତି BIT_IOR_ପଦସମଷ୍ଟି:
    ସ୍ଥିତି BIT_XOR_ପଦସମଷ୍ଟି:
      ଯଦି ((code0 == INTEGER_TYPE || code0 == BITINT_TYPE)
	  && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	shorten = -1;
      /* Allow vector types which are not floating point types.   */
      ଅନ୍ୟଥା ଯଦି (gnu_vector_type_p (type0)
	       && gnu_vector_type_p (type1)
	       && !VECTOR_FLOAT_TYPE_P (type0)
	       && !VECTOR_FLOAT_TYPE_P (type1))
	common = 1;
      ଭାଙ୍ଗ;

    ସ୍ଥିତି TRUNC_MOD_ପଦସମଷ୍ଟି:
    ସ୍ଥିତି FLOOR_MOD_ପଦସମଷ୍ଟି:
      doing_div_or_mod = ସତ୍ୟ;
      warn_for_div_by_zero (location, op1);

      ଯଦି (gnu_vector_type_p (type0)
	  && gnu_vector_type_p (type1)
	  && ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (type0)) == INTEGER_TYPE
	  && ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (type1)) == INTEGER_TYPE)
	common = 1;
      ଅନ୍ୟଥା ଯଦି ((code0 == INTEGER_TYPE || code0 == BITINT_TYPE)
	       && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  /* Although it would be tempting to shorten always here, that loses
	     on some targets, since the modulo instruction is undefined if the
	     quotient can't be represented in the computation mode.  We shorten
	     only if unsigned or if dividing by something we know != -1.  */
	  shorten = may_shorten_divmod (op0, op1);
	  common = 1;
	}
      ଭାଙ୍ଗ;

    ସ୍ଥିତି TRUTH_ANDIF_ପଦସମଷ୍ଟି:
    ସ୍ଥିତି TRUTH_ORIF_ପଦସମଷ୍ଟି:
    ସ୍ଥିତି TRUTH_AND_ପଦସମଷ୍ଟି:
    ସ୍ଥିତି TRUTH_OR_ପଦସମଷ୍ଟି:
    ସ୍ଥିତି TRUTH_XOR_ପଦସମଷ୍ଟି:
      ଯଦି ((code0 == INTEGER_TYPE || code0 == POINTER_TYPE
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
	  result_type = integer_type_ଗଣ୍ଠି;
	  ଯଦି (op0_int_operands)
	    {
	      op0 = c_objc_common_truthvalue_conversion (location, orig_op0);
	      op0 = remove_c_maybe_const_ପଦସମଷ୍ଟି (op0);
	    }
	  ଅନ୍ୟଥା
	    op0 = c_objc_common_truthvalue_conversion (location, op0);
	  ଯଦି (op1_int_operands)
	    {
	      op1 = c_objc_common_truthvalue_conversion (location, orig_op1);
	      op1 = remove_c_maybe_const_ପଦସମଷ୍ଟି (op1);
	    }
	  ଅନ୍ୟଥା
	    op1 = c_objc_common_truthvalue_conversion (location, op1);
	  converted = 1;
	  boolean_op = ସତ୍ୟ;
	}
      ଯଦି (code == TRUTH_ANDIF_ପଦସମଷ୍ଟି)
	{
	  int_const_or_overflow = (int_operands
				   && ବୃକ୍ଷ_CODE (orig_op0) == INTEGER_CST
				   && (op0 == truthvalue_false_ଗଣ୍ଠି
				       || ବୃକ୍ଷ_CODE (orig_op1) == INTEGER_CST));
	  int_const = (int_const_or_overflow
		       && !ବୃକ୍ଷ_OVERFLOW (orig_op0)
		       && (op0 == truthvalue_false_ଗଣ୍ଠି
			   || !ବୃକ୍ଷ_OVERFLOW (orig_op1)));
	}
      ଅନ୍ୟଥା ଯଦି (code == TRUTH_ORIF_ପଦସମଷ୍ଟି)
	{
	  int_const_or_overflow = (int_operands
				   && ବୃକ୍ଷ_CODE (orig_op0) == INTEGER_CST
				   && (op0 == truthvalue_true_ଗଣ୍ଠି
				       || ବୃକ୍ଷ_CODE (orig_op1) == INTEGER_CST));
	  int_const = (int_const_or_overflow
		       && !ବୃକ୍ଷ_OVERFLOW (orig_op0)
		       && (op0 == truthvalue_true_ଗଣ୍ଠି
			   || !ବୃକ୍ଷ_OVERFLOW (orig_op1)));
	}
      ଭାଙ୍ଗ;

      /* Shift operations: result has same type as first operand;
	 always convert second operand to int.
	 Also set SHORT_SHIFT if shifting rightward.  */

    ସ୍ଥିତି RSHIFT_ପଦସମଷ୍ଟି:
      ଯଦି (gnu_vector_type_p (type0)
	  && gnu_vector_type_p (type1)
	  && ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (type0)) == INTEGER_TYPE
	  && ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (type1)) == INTEGER_TYPE
	  && known_eq (TYPE_VECTOR_SUBPARTS (type0),
		       TYPE_VECTOR_SUBPARTS (type1)))
	{
	  result_type = type0;
	  converted = 1;
	}
      ଅନ୍ୟଥା ଯଦି ((code0 == INTEGER_TYPE || code0 == FIXED_POINT_TYPE
		|| code0 == BITINT_TYPE
		|| (gnu_vector_type_p (type0)
		    && ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (type0)) == INTEGER_TYPE))
	       && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  doing_shift = ସତ୍ୟ;
	  ଯଦି (ବୃକ୍ଷ_CODE (op1) == INTEGER_CST)
	    {
	      ଯଦି (ବୃକ୍ଷ_int_cst_sgn (op1) < 0)
		{
		  int_const = ମିଥ୍ୟା;
		  ଯଦି (c_inhibit_evaluation_warnings == 0)
		    warning_at (location, OPT_Wshift_ଗଣନା_negative,
				"right shift count is negative");
		}
	      ଅନ୍ୟଥା ଯଦି (code0 == VECTOR_TYPE)
		{
		  ଯଦି (compare_ବୃକ୍ଷ_int (op1,
					TYPE_PRECISION (ବୃକ୍ଷ_TYPE (type0)))
		      >= 0)
		    {
		      int_const = ମିଥ୍ୟା;
		      ଯଦି (c_inhibit_evaluation_warnings == 0)
			warning_at (location, OPT_Wshift_ଗଣନା_overflow,
				    "right shift count >= width of vector element");
		    }
		}
	      ଅନ୍ୟଥା
		{
		  ଯଦି (!integer_zerop (op1))
		    short_shift = 1;

		  ଯଦି (compare_ବୃକ୍ଷ_int (op1, TYPE_PRECISION (type0)) >= 0)
		    {
		      int_const = ମିଥ୍ୟା;
		      ଯଦି (c_inhibit_evaluation_warnings == 0)
			warning_at (location, OPT_Wshift_ଗଣନା_overflow,
				    "right shift count >= width of type");
		    }
		}
	    }

	  /* Use the type of the value to be shifted.  */
	  result_type = type0;
	  /* Avoid converting op1 to result_type later.  */
	  converted = 1;
	}
      ଭାଙ୍ଗ;

    ସ୍ଥିତି LSHIFT_ପଦସମଷ୍ଟି:
      ଯଦି (gnu_vector_type_p (type0)
	  && gnu_vector_type_p (type1)
	  && ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (type0)) == INTEGER_TYPE
	  && ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (type1)) == INTEGER_TYPE
	  && known_eq (TYPE_VECTOR_SUBPARTS (type0),
		       TYPE_VECTOR_SUBPARTS (type1)))
	{
	  result_type = type0;
	  converted = 1;
	}
      ଅନ୍ୟଥା ଯଦି ((code0 == INTEGER_TYPE || code0 == FIXED_POINT_TYPE
		|| code0 == BITINT_TYPE
		|| (gnu_vector_type_p (type0)
		    && ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (type0)) == INTEGER_TYPE))
	       && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  doing_shift = ସତ୍ୟ;
	  ଯଦି (ବୃକ୍ଷ_CODE (op0) == INTEGER_CST
	      && ବୃକ୍ଷ_int_cst_sgn (op0) < 0
	      && !TYPE_OVERFLOW_WRAPS (type0))
	    {
	      /* Don't reject a left shift of a negative value in a context
		 where a constant expression is needed in C90.  */
	      ଯଦି (flag_isoc99)
		int_const = ମିଥ୍ୟା;
	      ଯଦି (c_inhibit_evaluation_warnings == 0)
		warning_at (location, OPT_Wshift_negative_ମୂଲ୍ୟ,
			    "left shift of negative value");
	    }
	  ଯଦି (ବୃକ୍ଷ_CODE (op1) == INTEGER_CST)
	    {
	      ଯଦି (ବୃକ୍ଷ_int_cst_sgn (op1) < 0)
		{
		  int_const = ମିଥ୍ୟା;
		  ଯଦି (c_inhibit_evaluation_warnings == 0)
		    warning_at (location, OPT_Wshift_ଗଣନା_negative,
				"left shift count is negative");
		}
	      ଅନ୍ୟଥା ଯଦି (code0 == VECTOR_TYPE)
		{
		  ଯଦି (compare_ବୃକ୍ଷ_int (op1,
					TYPE_PRECISION (ବୃକ୍ଷ_TYPE (type0)))
		      >= 0)
		    {
		      int_const = ମିଥ୍ୟା;
		      ଯଦି (c_inhibit_evaluation_warnings == 0)
			warning_at (location, OPT_Wshift_ଗଣନା_overflow,
				    "left shift count >= width of vector element");
		    }
		}
	      ଅନ୍ୟଥା ଯଦି (compare_ବୃକ୍ଷ_int (op1, TYPE_PRECISION (type0)) >= 0)
		{
		  int_const = ମିଥ୍ୟା;
		  ଯଦି (c_inhibit_evaluation_warnings == 0)
		    warning_at (location, OPT_Wshift_ଗଣନା_overflow,
				"left shift count >= width of type");
		}
	      ଅନ୍ୟଥା ଯଦି (ବୃକ୍ଷ_CODE (op0) == INTEGER_CST
		       && maybe_warn_shift_overflow (location, op0, op1)
		       && flag_isoc99)
		int_const = ମିଥ୍ୟା;
	    }

	  /* Use the type of the value to be shifted.  */
	  result_type = type0;
	  /* Avoid converting op1 to result_type later.  */
	  converted = 1;
	}
      ଭାଙ୍ଗ;

    ସ୍ଥିତି EQ_ପଦସମଷ୍ଟି:
    ସ୍ଥିତି NE_ପଦସମଷ୍ଟି:
      ଯଦି (gnu_vector_type_p (type0) && gnu_vector_type_p (type1))
        {
          ବୃକ୍ଷ intt;
	  ଯଦି (!vector_types_compatible_elements_p (type0, type1))
            {
              error_at (location, "comparing vectors with different "
                                  "element types");
              ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
            }

	  ଯଦି (maybe_ne (TYPE_VECTOR_SUBPARTS (type0),
			TYPE_VECTOR_SUBPARTS (type1)))
            {
              error_at (location, "comparing vectors with different "
                                  "number of elements");
              ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
            }

	  /* It's not precisely specified how the usual arithmetic
	     conversions apply to the vector types.  Here, we use
	     the unsigned type if one of the operands is signed and
	     the other one is unsigned.  */
	  ଯଦି (TYPE_UNSIGNED (type0) != TYPE_UNSIGNED (type1))
	    {
	      ଯଦି (!TYPE_UNSIGNED (type0))
		op0 = build1 (VIEW_CONVERT_ପଦସମଷ୍ଟି, type1, op0);
	      ଅନ୍ୟଥା
		op1 = build1 (VIEW_CONVERT_ପଦସମଷ୍ଟି, type0, op1);
	      warning_at (location, OPT_Wsign_compare, "comparison between "
			  "types %qT and %qT", type0, type1);
	    }

          /* Always construct signed integer vector type.  */
	  ଯଦି (VECTOR_BOOLEAN_TYPE_P (type0) && VECTOR_BOOLEAN_TYPE_P (type1))
	    result_type = type0;
	  ଅନ୍ୟଥା
	    {
	      auto nelts = TYPE_VECTOR_SUBPARTS (type0);

	      intt = c_common_type_for_size (GET_MODE_BITSIZE
					     (SCALAR_TYPE_MODE
						(ବୃକ୍ଷ_TYPE (type0))), 0);
	      ଯଦି (!intt)
		{
		  error_at (location, "could not find an integer type "
				      "of the same size as %qT",
			    ବୃକ୍ଷ_TYPE (type0));
		  ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
		}
	      result_type = build_opaque_vector_type (intt, nelts);
	    }
          converted = 1;
	  ret = build_vec_cmp (resultcode, result_type, op0, op1);
	  ଯାଅ return_build_ଦ୍ୱିମିକ_op;
        }
      ଯଦି (FLOAT_TYPE_P (type0) || FLOAT_TYPE_P (type1))
	warning_at (location,
		    OPT_Wfloat_equal,
		    "comparing floating-point with %<==%> or %<!=%> is unsafe");
      /* Result of comparison is always int,
	 but don't convert the args to int!  */
      build_type = integer_type_ଗଣ୍ଠି;
      ଯଦି ((code0 == INTEGER_TYPE || code0 == REAL_TYPE || code0 == BITINT_TYPE
	   || code0 == FIXED_POINT_TYPE || code0 == COMPLEX_TYPE)
	  && (code1 == INTEGER_TYPE || code1 == REAL_TYPE
	      || code1 == BITINT_TYPE
	      || code1 == FIXED_POINT_TYPE || code1 == COMPLEX_TYPE))
	short_compare = 1;
      ଅନ୍ୟଥା ଯଦି (code0 == POINTER_TYPE
	       && (code1 == NULLPTR_TYPE
		   || null_pointer_constant_p (orig_op1)))
	{
	  maybe_warn_for_null_address (location, op0, code);
	  result_type = type0;
	}
      ଅନ୍ୟଥା ଯଦି (code1 == POINTER_TYPE
	       && (code0 == NULLPTR_TYPE
		   || null_pointer_constant_p (orig_op0)))
	{
	  maybe_warn_for_null_address (location, op1, code);
	  result_type = type1;
	}
      ଅନ୍ୟଥା ଯଦି (code0 == POINTER_TYPE && code1 == POINTER_TYPE)
	{
	  ବୃକ୍ଷ tt0 = ବୃକ୍ଷ_TYPE (type0);
	  ବୃକ୍ଷ tt1 = ବୃକ୍ଷ_TYPE (type1);
	  addr_space_t as0 = TYPE_ADDR_SPACE (tt0);
	  addr_space_t as1 = TYPE_ADDR_SPACE (tt1);
	  addr_space_t as_common = ADDR_SPACE_GENERIC;

	  /* Anything compares with void *.  void * compares with anything.
	     Otherwise, the targets must be compatible
	     and both must be object or both incomplete.  */
	  ଯଦି (comp_target_types (location, type0, type1))
	    result_type = common_pointer_type (type0, type1, NULL_ବୃକ୍ଷ);
	  ଅନ୍ୟଥା ଯଦି (!addr_space_superset (as0, as1, &as_common))
	    {
	      error_at (location, "comparison of pointers to "
			"disjoint address spaces");
	      ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
	    }
	  ଅନ୍ୟଥା ଯଦି (VOID_TYPE_P (tt0) && !TYPE_ATOMIC (tt0))
	    {
	      ଯଦି (pedantic && ବୃକ୍ଷ_CODE (tt1) == FUNCTION_TYPE)
		pedwarn (location, OPT_Wpedantic, "ISO C forbids "
			 "comparison of %<void *%> with function pointer");
	    }
	  ଅନ୍ୟଥା ଯଦି (VOID_TYPE_P (tt1) && !TYPE_ATOMIC (tt1))
	    {
	      ଯଦି (pedantic && ବୃକ୍ଷ_CODE (tt0) == FUNCTION_TYPE)
		pedwarn (location, OPT_Wpedantic, "ISO C forbids "
			 "comparison of %<void *%> with function pointer");
	    }
	  ଅନ୍ୟଥା
	    /* Avoid warning about the volatile ObjC EH puts on decls.  */
	    ଯଦି (!objc_ok)
	      pedwarn (location, OPT_Wcompare_distinct_pointer_types,
		       "comparison of distinct pointer types lacks a cast");

	  ଯଦି (result_type == NULL_ବୃକ୍ଷ)
	    {
	      ପୂର୍ଣ୍ଣସଂଖ୍ୟା qual = ENCODE_QUAL_ADDR_SPACE (as_common);
	      result_type = c_build_pointer_type
			      (c_build_qualified_type (void_type_ଗଣ୍ଠି, qual));
	    }
	}
      ଅନ୍ୟଥା ଯଦି (code0 == POINTER_TYPE
	       && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  result_type = type0;
	  pedwarn (location, 0, "comparison between pointer and integer");
	}
      ଅନ୍ୟଥା ଯଦି ((code0 == INTEGER_TYPE || code0 == BITINT_TYPE)
	       && code1 == POINTER_TYPE)
	{
	  result_type = type1;
	  pedwarn (location, 0, "comparison between pointer and integer");
	}
      /* 6.5.9: One of the following shall hold:
	 -- both operands have type nullptr_t;  */
      ଅନ୍ୟଥା ଯଦି (code0 == NULLPTR_TYPE && code1 == NULLPTR_TYPE)
	{
	  result_type = nullptr_type_ଗଣ୍ଠି;
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
      ଅନ୍ୟଥା ଯଦି (code0 == NULLPTR_TYPE && null_pointer_constant_p (orig_op1))
	result_type = (INTEGRAL_TYPE_P (type1)
		       ? c_build_pointer_type (type1) : type1);
      ଅନ୍ୟଥା ଯଦି (code1 == NULLPTR_TYPE && null_pointer_constant_p (orig_op0))
	result_type = (INTEGRAL_TYPE_P (type0)
		       ? c_build_pointer_type (type0) : type0);
      ଯଦି ((C_BOOLEAN_TYPE_P (ବୃକ୍ଷ_TYPE (orig_op0))
	   || truth_ମୂଲ୍ୟ_p (ବୃକ୍ଷ_CODE (orig_op0)))
	  ^ (C_BOOLEAN_TYPE_P (ବୃକ୍ଷ_TYPE (orig_op1))
	     || truth_ମୂଲ୍ୟ_p (ବୃକ୍ଷ_CODE (orig_op1))))
	maybe_warn_bool_compare (location, code, orig_op0, orig_op1);
      ଭାଙ୍ଗ;

    ସ୍ଥିତି LE_ପଦସମଷ୍ଟି:
    ସ୍ଥିତି GE_ପଦସମଷ୍ଟି:
    ସ୍ଥିତି LT_ପଦସମଷ୍ଟି:
    ସ୍ଥିତି GT_ପଦସମଷ୍ଟି:
      ଯଦି (gnu_vector_type_p (type0) && gnu_vector_type_p (type1))
        {
          ବୃକ୍ଷ intt;
	  ଯଦି (!vector_types_compatible_elements_p (type0, type1))
            {
              error_at (location, "comparing vectors with different "
                                  "element types");
              ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
            }

	  ଯଦି (maybe_ne (TYPE_VECTOR_SUBPARTS (type0),
			TYPE_VECTOR_SUBPARTS (type1)))
            {
              error_at (location, "comparing vectors with different "
                                  "number of elements");
              ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
            }

	  /* It's not precisely specified how the usual arithmetic
	     conversions apply to the vector types.  Here, we use
	     the unsigned type if one of the operands is signed and
	     the other one is unsigned.  */
	  ଯଦି (TYPE_UNSIGNED (type0) != TYPE_UNSIGNED (type1))
	    {
	      ଯଦି (!TYPE_UNSIGNED (type0))
		op0 = build1 (VIEW_CONVERT_ପଦସମଷ୍ଟି, type1, op0);
	      ଅନ୍ୟଥା
		op1 = build1 (VIEW_CONVERT_ପଦସମଷ୍ଟି, type0, op1);
	      warning_at (location, OPT_Wsign_compare, "comparison between "
			  "types %qT and %qT", type0, type1);
	    }

          /* Always construct signed integer vector type.  */
          intt = c_common_type_for_size (GET_MODE_BITSIZE
					 (SCALAR_TYPE_MODE
					  (ବୃକ୍ଷ_TYPE (type0))), 0);
	  ଯଦି (!intt)
	    {
	      error_at (location, "could not find an integer type "
				  "of the same size as %qT",
			ବୃକ୍ଷ_TYPE (type0));
	      ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
	    }
          result_type = build_opaque_vector_type (intt,
						  TYPE_VECTOR_SUBPARTS (type0));
          converted = 1;
	  ret = build_vec_cmp (resultcode, result_type, op0, op1);
	  ଯାଅ return_build_ଦ୍ୱିମିକ_op;
        }
      build_type = integer_type_ଗଣ୍ଠି;
      ଯଦି ((code0 == INTEGER_TYPE || code0 == REAL_TYPE
	   || code0 == BITINT_TYPE || code0 == FIXED_POINT_TYPE)
	  && (code1 == INTEGER_TYPE || code1 == REAL_TYPE
	      || code1 == BITINT_TYPE || code1 == FIXED_POINT_TYPE))
	short_compare = 1;
      ଅନ୍ୟଥା ଯଦି (code0 == POINTER_TYPE && code1 == POINTER_TYPE)
	{
	  addr_space_t as0 = TYPE_ADDR_SPACE (ବୃକ୍ଷ_TYPE (type0));
	  addr_space_t as1 = TYPE_ADDR_SPACE (ବୃକ୍ଷ_TYPE (type1));
	  addr_space_t as_common;

	  ଯଦି (comp_target_types (location, type0, type1))
	    {
	      result_type = common_pointer_type (type0, type1, NULL_ବୃକ୍ଷ);
	      ଯଦି (!COMPLETE_TYPE_P (ବୃକ୍ଷ_TYPE (type0))
		  != !COMPLETE_TYPE_P (ବୃକ୍ଷ_TYPE (type1)))
		pedwarn_c99 (location, OPT_Wpedantic,
			     "comparison of complete and incomplete pointers");
	      ଅନ୍ୟଥା ଯଦି (ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (type0)) == FUNCTION_TYPE)
		pedwarn (location, OPT_Wpedantic, "ISO C forbids "
			 "ordered comparisons of pointers to functions");
	      ଅନ୍ୟଥା ଯଦି (null_pointer_constant_p (orig_op0)
		       || null_pointer_constant_p (orig_op1))
		warning_at (location, OPT_Wextra,
			    "ordered comparison of pointer with null pointer");

	    }
	  ଅନ୍ୟଥା ଯଦି (!addr_space_superset (as0, as1, &as_common))
	    {
	      error_at (location, "comparison of pointers to "
			"disjoint address spaces");
	      ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
	    }
	  ଅନ୍ୟଥା
	    {
	      ପୂର୍ଣ୍ଣସଂଖ୍ୟା qual = ENCODE_QUAL_ADDR_SPACE (as_common);
	      result_type = c_build_pointer_type
			      (c_build_qualified_type (void_type_ଗଣ୍ଠି, qual));
              pedwarn (location, OPT_Wcompare_distinct_pointer_types,
                       "comparison of distinct pointer types lacks a cast");
	    }
	}
      ଅନ୍ୟଥା ଯଦି (code0 == POINTER_TYPE && null_pointer_constant_p (orig_op1))
	{
	  result_type = type0;
	  ଯଦି (pedantic)
	    pedwarn (location, OPT_Wpedantic,
		     "ordered comparison of pointer with integer zero");
	  ଅନ୍ୟଥା ଯଦି (extra_warnings)
	    warning_at (location, OPT_Wextra,
			"ordered comparison of pointer with integer zero");
	}
      ଅନ୍ୟଥା ଯଦି (code1 == POINTER_TYPE && null_pointer_constant_p (orig_op0))
	{
	  result_type = type1;
	  ଯଦି (pedantic)
	    pedwarn (location, OPT_Wpedantic,
		     "ordered comparison of pointer with integer zero");
	  ଅନ୍ୟଥା ଯଦି (extra_warnings)
	    warning_at (location, OPT_Wextra,
			"ordered comparison of pointer with integer zero");
	}
      ଅନ୍ୟଥା ଯଦି (code0 == POINTER_TYPE
	       && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  result_type = type0;
	  pedwarn (location, 0, "comparison between pointer and integer");
	}
      ଅନ୍ୟଥା ଯଦି ((code0 == INTEGER_TYPE || code0 == BITINT_TYPE)
	       && code1 == POINTER_TYPE)
	{
	  result_type = type1;
	  pedwarn (location, 0, "comparison between pointer and integer");
	}

      ଯଦି ((code0 == POINTER_TYPE || code1 == POINTER_TYPE)
	  && current_function_decl != NULL_ବୃକ୍ଷ
	  && sanitize_flags_p (SANITIZE_POINTER_COMPARE))
	{
	  op0 = save_ପଦସମଷ୍ଟି (c_fully_fold (op0, ମିଥ୍ୟା, ଖାଲି));
	  op1 = save_ପଦସମଷ୍ଟି (c_fully_fold (op1, ମିଥ୍ୟା, ଖାଲି));

	  ବୃକ୍ଷ tt = builtin_decl_explicit (BUILT_IN_ASAN_POINTER_COMPARE);
	  instrument_ପଦସମଷ୍ଟି = build_call_ପଦସମଷ୍ଟି_loc (location, tt, 2, op0, op1);
	}

      ଯଦି ((C_BOOLEAN_TYPE_P (ବୃକ୍ଷ_TYPE (orig_op0))
	   || truth_ମୂଲ୍ୟ_p (ବୃକ୍ଷ_CODE (orig_op0)))
	  ^ (C_BOOLEAN_TYPE_P (ବୃକ୍ଷ_TYPE (orig_op1))
	     || truth_ମୂଲ୍ୟ_p (ବୃକ୍ଷ_CODE (orig_op1))))
	maybe_warn_bool_compare (location, code, orig_op0, orig_op1);
      ଭାଙ୍ଗ;

    ସ୍ଥିତି MIN_ପଦସମଷ୍ଟି:
    ସ୍ଥିତି MAX_ପଦସମଷ୍ଟି:
      /* Used for OpenMP atomics.  */
      gcc_assert (flag_openmp);
      common = 1;
      ଭାଙ୍ଗ;

    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
      gcc_unreachable ();
    }

  ଯଦି (code0 == ERROR_MARK || code1 == ERROR_MARK)
    ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;

  ଯଦି (gnu_vector_type_p (type0)
      && gnu_vector_type_p (type1)
      && (!ବୃକ୍ଷ_int_cst_equal (TYPE_SIZE (type0), TYPE_SIZE (type1))
	  || !vector_types_compatible_elements_p (type0, type1)))
    {
      gcc_rich_location richloc (location);
      maybe_range_label_for_ବୃକ୍ଷ_type_mismatch
	label_for_op0 (orig_op0, orig_op1),
	label_for_op1 (orig_op1, orig_op0);
      richloc.maybe_add_ପଦସମଷ୍ଟି (orig_op0, &label_for_op0, highlight_colors::lhs);
      richloc.maybe_add_ପଦସମଷ୍ଟି (orig_op1, &label_for_op1, highlight_colors::rhs);
      ଦ୍ୱିମିକ_op_error (&richloc, code, type0, type1);
      ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
    }

  ଯଦି ((code0 == INTEGER_TYPE || code0 == REAL_TYPE || code0 == COMPLEX_TYPE
       || code0 == FIXED_POINT_TYPE || code0 == BITINT_TYPE
       || gnu_vector_type_p (type0))
      && (code1 == INTEGER_TYPE || code1 == REAL_TYPE || code1 == COMPLEX_TYPE
	  || code1 == FIXED_POINT_TYPE || code1 == BITINT_TYPE
	  || gnu_vector_type_p (type1)))
    {
      ତାର୍କିକ first_complex = (code0 == COMPLEX_TYPE);
      ତାର୍କିକ second_complex = (code1 == COMPLEX_TYPE);
      ପୂର୍ଣ୍ଣସଂଖ୍ୟା none_complex = (!first_complex && !second_complex);

      ଯଦି (shorten || common || short_compare)
	{
	  result_type = c_common_type (type0, type1);
	  do_warn_double_promotion (result_type, type0, type1,
				    "implicit conversion from %qT to %qT "
				    "to match other operand of binary "
				    "expression",
				    location);
	  ଯଦି (result_type == error_mark_ଗଣ୍ଠି)
	    ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
	}

      ଯଦି (first_complex != second_complex
	  && (code == PLUS_ପଦସମଷ୍ଟି
	      || code == MINUS_ପଦସମଷ୍ଟି
	      || code == MULT_ପଦସମଷ୍ଟି
	      || (code == TRUNC_DIV_ପଦସମଷ୍ଟି && first_complex))
	  && ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (result_type)) == REAL_TYPE
	  && flag_signed_zeros)
	{
	  /* An operation on mixed real/complex operands must be
	     handled specially, but the language-independent code can
	     more easily optimize the plain complex arithmetic if
	     -fno-signed-zeros.  */
	  ବୃକ୍ଷ real_type = ବୃକ୍ଷ_TYPE (result_type);
	  ବୃକ୍ଷ real, imag;
	  ଯଦି (type0 != orig_type0 || type1 != orig_type1)
	    {
	      gcc_assert (may_need_excess_precision && common);
	      semantic_result_type = c_common_type (orig_type0, orig_type1);
	    }
	  ଯଦି (first_complex)
	    {
	      ଯଦି (ବୃକ୍ଷ_TYPE (op0) != result_type)
		op0 = convert_and_check (location, result_type, op0);
	      ଯଦି (ବୃକ୍ଷ_TYPE (op1) != real_type)
		op1 = convert_and_check (location, real_type, op1);
	    }
	  ଅନ୍ୟଥା
	    {
	      ଯଦି (ବୃକ୍ଷ_TYPE (op0) != real_type)
		op0 = convert_and_check (location, real_type, op0);
	      ଯଦି (ବୃକ୍ଷ_TYPE (op1) != result_type)
		op1 = convert_and_check (location, result_type, op1);
	    }
	  ଯଦି (ବୃକ୍ଷ_CODE (op0) == ERROR_MARK || ବୃକ୍ଷ_CODE (op1) == ERROR_MARK)
	    ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
	  ଯଦି (first_complex)
	    {
	      op0 = save_ପଦସମଷ୍ଟି (op0);
	      real = build_unary_op (ପଦସମଷ୍ଟି_LOCATION (orig_op0), REALPART_ପଦସମଷ୍ଟି,
				     op0, ସତ୍ୟ);
	      imag = build_unary_op (ପଦସମଷ୍ଟି_LOCATION (orig_op0), IMAGPART_ପଦସମଷ୍ଟି,
				     op0, ସତ୍ୟ);
	      ବାଛ (code)
		{
		ସ୍ଥିତି MULT_ପଦସମଷ୍ଟି:
		ସ୍ଥିତି TRUNC_DIV_ପଦସମଷ୍ଟି:
		  op1 = save_ପଦସମଷ୍ଟି (op1);
		  imag = build2 (resultcode, real_type, imag, op1);
		  /* Fall through.  */
		ସ୍ଥିତି PLUS_ପଦସମଷ୍ଟି:
		ସ୍ଥିତି MINUS_ପଦସମଷ୍ଟି:
		  real = build2 (resultcode, real_type, real, op1);
		  ଭାଙ୍ଗ;
		ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
		  gcc_unreachable();
		}
	    }
	  ଅନ୍ୟଥା
	    {
	      op1 = save_ପଦସମଷ୍ଟି (op1);
	      real = build_unary_op (ପଦସମଷ୍ଟି_LOCATION (orig_op1), REALPART_ପଦସମଷ୍ଟି,
				     op1, ସତ୍ୟ);
	      imag = build_unary_op (ପଦସମଷ୍ଟି_LOCATION (orig_op1), IMAGPART_ପଦସମଷ୍ଟି,
				     op1, ସତ୍ୟ);
	      ବାଛ (code)
		{
		ସ୍ଥିତି MULT_ପଦସମଷ୍ଟି:
		  op0 = save_ପଦସମଷ୍ଟି (op0);
		  imag = build2 (resultcode, real_type, op0, imag);
		  /* Fall through.  */
		ସ୍ଥିତି PLUS_ପଦସମଷ୍ଟି:
		  real = build2 (resultcode, real_type, op0, real);
		  ଭାଙ୍ଗ;
		ସ୍ଥିତି MINUS_ପଦସମଷ୍ଟି:
		  real = build2 (resultcode, real_type, op0, real);
		  imag = build1 (NEGATE_ପଦସମଷ୍ଟି, real_type, imag);
		  ଭାଙ୍ଗ;
		ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
		  gcc_unreachable();
		}
	    }
	  ret = build2 (COMPLEX_ପଦସମଷ୍ଟି, result_type, real, imag);
	  ଯାଅ return_build_ଦ୍ୱିମିକ_op;
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

      ଯଦି (shorten && none_complex)
	{
	  final_type = result_type;
	  result_type = shorten_ଦ୍ୱିମିକ_op (result_type, op0, op1,
					   shorten == -1);
	}

      /* Shifts can be shortened if shifting right.  */

      ଯଦି (short_shift)
	{
	  ପୂର୍ଣ୍ଣସଂଖ୍ୟା unsigned_arg;
	  ବୃକ୍ଷ arg0 = get_narrower (op0, &unsigned_arg);

	  final_type = result_type;

	  ଯଦି (arg0 == op0 && final_type == ବୃକ୍ଷ_TYPE (op0))
	    unsigned_arg = TYPE_UNSIGNED (ବୃକ୍ଷ_TYPE (op0));

	  ଯଦି (TYPE_PRECISION (ବୃକ୍ଷ_TYPE (arg0)) < TYPE_PRECISION (result_type)
	      && ବୃକ୍ଷ_int_cst_sgn (op1) > 0
	      /* We can shorten only if the shift count is less than the
		 number of bits in the smaller type size.  */
	      && compare_ବୃକ୍ଷ_int (op1, TYPE_PRECISION (ବୃକ୍ଷ_TYPE (arg0))) < 0
	      /* We cannot drop an unsigned shift after sign-extension.  */
	      && (!TYPE_UNSIGNED (final_type) || unsigned_arg))
	    {
	      /* Do an unsigned shift if the operand was zero-extended.  */
	      result_type
		= c_common_signed_or_unsigned_type (unsigned_arg,
						    ବୃକ୍ଷ_TYPE (arg0));
	      /* Convert value-to-be-shifted to that type.  */
	      ଯଦି (ବୃକ୍ଷ_TYPE (op0) != result_type)
		op0 = convert (result_type, op0);
	      converted = 1;
	    }
	}

      /* Comparison operations are shortened too but differently.
	 They identify themselves by setting short_compare = 1.  */

      ଯଦି (short_compare)
	{
	  /* Don't write &op0, etc., because that would prevent op0
	     from being kept in a register.
	     Instead, make copies of the our local variables and
	     pass the copies by reference, then copy them back afterward.  */
	  ବୃକ୍ଷ xop0 = op0, xop1 = op1, xresult_type = result_type;
	  ଗଣନା ବୃକ୍ଷ_code xresultcode = resultcode;
	  ବୃକ୍ଷ val
	    = shorten_compare (location, &xop0, &xop1, &xresult_type,
			       &xresultcode);

	  ଯଦି (val != NULL_ବୃକ୍ଷ)
	    {
	      ret = val;
	      ଯାଅ return_build_ଦ୍ୱିମିକ_op;
	    }

	  op0 = xop0, op1 = xop1;
	  converted = 1;
	  resultcode = xresultcode;

	  ଯଦି (c_inhibit_evaluation_warnings == 0 && !c_in_omp_for)
	    {
	      ତାର୍କିକ op0_maybe_const = ସତ୍ୟ;
	      ତାର୍କିକ op1_maybe_const = ସତ୍ୟ;
	      ବୃକ୍ଷ orig_op0_folded, orig_op1_folded;

	      ଯଦି (in_late_ଦ୍ୱିମିକ_op)
		{
		  orig_op0_folded = orig_op0;
		  orig_op1_folded = orig_op1;
		}
	      ଅନ୍ୟଥା
		{
		  /* Fold for the sake of possible warnings, as in
		     build_conditional_expr.  This requires the
		     "original" values to be folded, not just op0 and
		     op1.  */
		  c_inhibit_evaluation_warnings++;
		  op0 = c_fully_fold (op0, require_constant_ମୂଲ୍ୟ,
				      &op0_maybe_const);
		  op1 = c_fully_fold (op1, require_constant_ମୂଲ୍ୟ,
				      &op1_maybe_const);
		  c_inhibit_evaluation_warnings--;
		  orig_op0_folded = c_fully_fold (orig_op0,
						  require_constant_ମୂଲ୍ୟ,
						  ଖାଲି);
		  orig_op1_folded = c_fully_fold (orig_op1,
						  require_constant_ମୂଲ୍ୟ,
						  ଖାଲି);
		}

	      ଯଦି (warn_sign_compare)
		warn_for_sign_compare (location, orig_op0_folded,
				       orig_op1_folded, op0, op1,
				       result_type, resultcode);
	      ଯଦି (!in_late_ଦ୍ୱିମିକ_op && !int_operands)
		{
		  ଯଦି (!op0_maybe_const || ବୃକ୍ଷ_CODE (op0) != INTEGER_CST)
		    op0 = c_wrap_maybe_const (op0, !op0_maybe_const);
		  ଯଦି (!op1_maybe_const || ବୃକ୍ଷ_CODE (op1) != INTEGER_CST)
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

  ଯଦି (!result_type)
    {
      /* Favor showing any expression locations that are available. */
      op_location_t oploc (location, UNKNOWN_LOCATION);
      ଦ୍ୱିମିକ_op_rich_location richloc (oploc, orig_op0, orig_op1, ସତ୍ୟ);
      ଦ୍ୱିମିକ_op_error (&richloc, code, ବୃକ୍ଷ_TYPE (op0), ବୃକ୍ଷ_TYPE (op1));
      ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
    }

  ଯଦି (build_type == NULL_ବୃକ୍ଷ)
    {
      build_type = result_type;
      ଯଦି ((type0 != orig_type0 || type1 != orig_type1)
	  && !boolean_op)
	{
	  gcc_assert (may_need_excess_precision && common);
	  semantic_result_type = c_common_type (orig_type0, orig_type1);
	}
    }

  ଯଦି (!converted)
    {
      op0 = ep_convert_and_check (location, result_type, op0,
				  semantic_result_type);
      op1 = ep_convert_and_check (location, result_type, op1,
				  semantic_result_type);

      /* This can happen if one operand has a vector type, and the other
	 has a different type.  */
      ଯଦି (ବୃକ୍ଷ_CODE (op0) == ERROR_MARK || ବୃକ୍ଷ_CODE (op1) == ERROR_MARK)
	ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
    }

  ଯଦି (sanitize_flags_p ((SANITIZE_SHIFT
			 | SANITIZE_DIVIDE
			 | SANITIZE_FLOAT_DIVIDE
			 | SANITIZE_SI_OVERFLOW))
      && current_function_decl != NULL_ବୃକ୍ଷ
      && (doing_div_or_mod || doing_shift)
      && !require_constant_ମୂଲ୍ୟ)
    {
      /* OP0 and/or OP1 might have side-effects.  */
      op0 = save_ପଦସମଷ୍ଟି (op0);
      op1 = save_ପଦସମଷ୍ଟି (op1);
      op0 = c_fully_fold (op0, ମିଥ୍ୟା, ଖାଲି);
      op1 = c_fully_fold (op1, ମିଥ୍ୟା, ଖାଲି);
      ଯଦି (doing_div_or_mod && (sanitize_flags_p ((SANITIZE_DIVIDE
						  | SANITIZE_FLOAT_DIVIDE
						  | SANITIZE_SI_OVERFLOW))))
	instrument_ପଦସମଷ୍ଟି = ubsan_instrument_division (location, op0, op1);
      ଅନ୍ୟଥା ଯଦି (doing_shift && sanitize_flags_p (SANITIZE_SHIFT))
	instrument_ପଦସମଷ୍ଟି = ubsan_instrument_shift (location, code, op0, op1);
    }

  /* Treat expressions in initializers specially as they can't trap.  */
  ଯଦି (int_const_or_overflow)
    ret = (require_constant_ମୂଲ୍ୟ
	   ? fold_build2_initializer_loc (location, resultcode, build_type,
					  op0, op1)
	   : fold_build2_loc (location, resultcode, build_type, op0, op1));
  ଅନ୍ୟଥା
    ret = build2 (resultcode, build_type, op0, op1);
  ଯଦି (final_type != NULL_ବୃକ୍ଷ)
    ret = convert (final_type, ret);

 return_build_ଦ୍ୱିମିକ_op:
  gcc_assert (ret != error_mark_ଗଣ୍ଠି);
  ଯଦି (ବୃକ୍ଷ_CODE (ret) == INTEGER_CST && !ବୃକ୍ଷ_OVERFLOW (ret) && !int_const)
    ret = (int_operands
	   ? note_integer_operands (ret)
	   : build1 (NOP_ପଦସମଷ୍ଟି, ବୃକ୍ଷ_TYPE (ret), ret));
  ଅନ୍ୟଥା ଯଦି (ବୃକ୍ଷ_CODE (ret) != INTEGER_CST && int_operands
	   && !in_late_ଦ୍ୱିମିକ_op)
    ret = note_integer_operands (ret);
  protected_set_ପଦସମଷ୍ଟି_location (ret, location);

  ଯଦି (instrument_ପଦସମଷ୍ଟି != ଖାଲି)
    ret = fold_build2 (COMPOUND_ପଦସମଷ୍ଟି, ବୃକ୍ଷ_TYPE (ret),
		       instrument_ପଦସମଷ୍ଟି, ret);

  ଯଦି (semantic_result_type)
    ret = build1_loc (location, EXCESS_PRECISION_ପଦସମଷ୍ଟି,
		      semantic_result_type, ret);

  ଫେରନ୍ତୁ ret;
}


/* Convert EXPR to be a truth-value (type TYPE), validating its type for this
   purpose.  LOCATION is the source location for the expression.  */

ବୃକ୍ଷ
c_objc_common_truthvalue_conversion (location_t location, ବୃକ୍ଷ ପଦସମଷ୍ଟି, ବୃକ୍ଷ type)
{
  ତାର୍କିକ int_const, int_operands;

  ବାଛ (ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (ପଦସମଷ୍ଟି)))
    {
    ସ୍ଥିତି ARRAY_TYPE:
      error_at (location, "used array that cannot be converted to pointer where scalar is required");
      ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;

    ସ୍ଥିତି RECORD_TYPE:
      error_at (location, "used struct type value where scalar is required");
      ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;

    ସ୍ଥିତି UNION_TYPE:
      error_at (location, "used union type value where scalar is required");
      ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;

    ସ୍ଥିତି VOID_TYPE:
      error_at (location, "void value not ignored as it ought to be");
      ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;

    ସ୍ଥିତି POINTER_TYPE:
      ଯଦି (reject_gcc_builtin (ପଦସମଷ୍ଟି))
	ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
      ଭାଙ୍ଗ;

    ସ୍ଥିତି FUNCTION_TYPE:
      gcc_unreachable ();

    ସ୍ଥିତି VECTOR_TYPE:
      error_at (location, "used vector type where scalar is required");
      ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;

    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
      ଭାଙ୍ଗ;
    }

  /* Conversion of a floating constant to boolean goes through here
     and yields an integer constant expression.  Otherwise, the result
     is only an integer constant expression if the argument is.  */
  int_const = ((ବୃକ୍ଷ_CODE (ପଦସମଷ୍ଟି) == INTEGER_CST && !ବୃକ୍ଷ_OVERFLOW (ପଦସମଷ୍ଟି))
	       || ((ବୃକ୍ଷ_CODE (ପଦସମଷ୍ଟି) == REAL_CST
		    || ବୃକ୍ଷ_CODE (ପଦସମଷ୍ଟି) == COMPLEX_CST)
		   && (ବୃକ୍ଷ_CODE (type) == BOOLEAN_TYPE
		       || (ବୃକ୍ଷ_CODE (type) == ENUMERAL_TYPE
			   && ENUM_UNDERLYING_TYPE (type) != NULL_ବୃକ୍ଷ
			   && (ବୃକ୍ଷ_CODE (ENUM_UNDERLYING_TYPE (type))
			       == BOOLEAN_TYPE)))));
  int_operands = ପଦସମଷ୍ଟି_INT_CONST_OPERANDS (ପଦସମଷ୍ଟି);
  ଯଦି (int_operands && ବୃକ୍ଷ_CODE (ପଦସମଷ୍ଟି) != INTEGER_CST)
    {
      ପଦସମଷ୍ଟି = remove_c_maybe_const_ପଦସମଷ୍ଟି (ପଦସମଷ୍ଟି);
      ପଦସମଷ୍ଟି = build2 (NE_ପଦସମଷ୍ଟି, type, ପଦସମଷ୍ଟି,
		     convert (ବୃକ୍ଷ_TYPE (ପଦସମଷ୍ଟି), integer_zero_ଗଣ୍ଠି));
      ପଦସମଷ୍ଟି = note_integer_operands (ପଦସମଷ୍ଟି);
    }
  ଅନ୍ୟଥା
    {
      /* ??? Should we also give an error for vectors rather than leaving
	 those to give errors later?  */
      ପଦସମଷ୍ଟି = c_common_truthvalue_conversion (location, ପଦସମଷ୍ଟି);
      ପଦସମଷ୍ଟି = fold_convert_loc (location, type, ପଦସମଷ୍ଟି);
    }

  ଯଦି (ବୃକ୍ଷ_CODE (ପଦସମଷ୍ଟି) == INTEGER_CST && int_operands && !int_const)
    {
      ଯଦି (ବୃକ୍ଷ_OVERFLOW (ପଦସମଷ୍ଟି))
	ଫେରନ୍ତୁ ପଦସମଷ୍ଟି;
      ଅନ୍ୟଥା
	ଫେରନ୍ତୁ note_integer_operands (ପଦସମଷ୍ଟି);
    }
  ଯଦି (ବୃକ୍ଷ_CODE (ପଦସମଷ୍ଟି) == INTEGER_CST && !int_const)
    ଫେରନ୍ତୁ build1 (NOP_ପଦସମଷ୍ଟି, ବୃକ୍ଷ_TYPE (ପଦସମଷ୍ଟି), ପଦସମଷ୍ଟି);
  ଫେରନ୍ତୁ ପଦସମଷ୍ଟି;
}


/* Convert EXPR to a contained DECL, updating *TC, *TI and *SE as
   required.  */

ବୃକ୍ଷ
c_ପଦସମଷ୍ଟି_to_decl (ବୃକ୍ଷ ପଦସମଷ୍ଟି, ତାର୍କିକ *tc ATTRIBUTE_UNUSED, ତାର୍କିକ *se)
{
  ଯଦି (ବୃକ୍ଷ_CODE (ପଦସମଷ୍ଟି) == COMPOUND_LITERAL_ପଦସମଷ୍ଟି)
    {
      ବୃକ୍ଷ decl = COMPOUND_LITERAL_ପଦସମଷ୍ଟି_DECL (ପଦସମଷ୍ଟି);
      /* Executing a compound literal inside a function reinitializes
	 it.  */
      ଯଦି (!ବୃକ୍ଷ_STATIC (decl))
	*se = ସତ୍ୟ;
      ଫେରନ୍ତୁ decl;
    }
  ଅନ୍ୟଥା
    ଫେରନ୍ତୁ ପଦସମଷ୍ଟି;
}

/* Generate OMP construct CODE, with BODY and CLAUSES as its compound
   statement.  LOC is the location of the construct.  */

ବୃକ୍ଷ
c_finish_omp_construct (location_t loc, ଗଣନା ବୃକ୍ଷ_code code, ବୃକ୍ଷ body,
			ବୃକ୍ଷ clauses)
{
  body = c_end_compound_stmt (loc, body, ସତ୍ୟ);

  ବୃକ୍ଷ stmt = make_ଗଣ୍ଠି (code);
  ବୃକ୍ଷ_TYPE (stmt) = void_type_ଗଣ୍ଠି;
  OMP_BODY (stmt) = body;
  OMP_CLAUSES (stmt) = clauses;
  SET_ପଦସମଷ୍ଟି_LOCATION (stmt, loc);

  ଫେରନ୍ତୁ add_stmt (stmt);
}

/* Generate OACC_DATA, with CLAUSES and BLOCK as its compound
   statement.  LOC is the location of the OACC_DATA.  */

ବୃକ୍ଷ
c_finish_oacc_data (location_t loc, ବୃକ୍ଷ clauses, ବୃକ୍ଷ block)
{
  ବୃକ୍ଷ stmt;

  block = c_end_compound_stmt (loc, block, ସତ୍ୟ);

  stmt = make_ଗଣ୍ଠି (OACC_DATA);
  ବୃକ୍ଷ_TYPE (stmt) = void_type_ଗଣ୍ଠି;
  OACC_DATA_CLAUSES (stmt) = clauses;
  OACC_DATA_BODY (stmt) = block;
  SET_ପଦସମଷ୍ଟି_LOCATION (stmt, loc);

  ଫେରନ୍ତୁ add_stmt (stmt);
}

/* Generate OACC_HOST_DATA, with CLAUSES and BLOCK as its compound
   statement.  LOC is the location of the OACC_HOST_DATA.  */

ବୃକ୍ଷ
c_finish_oacc_host_data (location_t loc, ବୃକ୍ଷ clauses, ବୃକ୍ଷ block)
{
  ବୃକ୍ଷ stmt;

  block = c_end_compound_stmt (loc, block, ସତ୍ୟ);

  stmt = make_ଗଣ୍ଠି (OACC_HOST_DATA);
  ବୃକ୍ଷ_TYPE (stmt) = void_type_ଗଣ୍ଠି;
  OACC_HOST_DATA_CLAUSES (stmt) = clauses;
  OACC_HOST_DATA_BODY (stmt) = block;
  SET_ପଦସମଷ୍ଟି_LOCATION (stmt, loc);

  ଫେରନ୍ତୁ add_stmt (stmt);
}

/* Like c_begin_compound_stmt, except force the retention of the BLOCK.  */

ବୃକ୍ଷ
c_begin_omp_parallel (ଶୂନ୍ୟ)
{
  ବୃକ୍ଷ block;

  keep_next_level ();
  block = c_begin_compound_stmt (ସତ୍ୟ);

  ଫେରନ୍ତୁ block;
}

/* Generate OMP_PARALLEL, with CLAUSES and BLOCK as its compound
   statement.  LOC is the location of the OMP_PARALLEL.  */

ବୃକ୍ଷ
c_finish_omp_parallel (location_t loc, ବୃକ୍ଷ clauses, ବୃକ୍ଷ block)
{
  ବୃକ୍ଷ stmt;

  block = c_end_compound_stmt (loc, block, ସତ୍ୟ);

  stmt = make_ଗଣ୍ଠି (OMP_PARALLEL);
  ବୃକ୍ଷ_TYPE (stmt) = void_type_ଗଣ୍ଠି;
  OMP_PARALLEL_CLAUSES (stmt) = clauses;
  OMP_PARALLEL_BODY (stmt) = block;
  SET_ପଦସମଷ୍ଟି_LOCATION (stmt, loc);

  ଫେରନ୍ତୁ add_stmt (stmt);
}

/* Like c_begin_compound_stmt, except force the retention of the BLOCK.  */

ବୃକ୍ଷ
c_begin_omp_task (ଶୂନ୍ୟ)
{
  ବୃକ୍ଷ block;

  keep_next_level ();
  block = c_begin_compound_stmt (ସତ୍ୟ);

  ଫେରନ୍ତୁ block;
}

/* Generate OMP_TASK, with CLAUSES and BLOCK as its compound
   statement.  LOC is the location of the #pragma.  */

ବୃକ୍ଷ
c_finish_omp_task (location_t loc, ବୃକ୍ଷ clauses, ବୃକ୍ଷ block)
{
  ବୃକ୍ଷ stmt;

  block = c_end_compound_stmt (loc, block, ସତ୍ୟ);

  stmt = make_ଗଣ୍ଠି (OMP_TASK);
  ବୃକ୍ଷ_TYPE (stmt) = void_type_ଗଣ୍ଠି;
  OMP_TASK_CLAUSES (stmt) = clauses;
  OMP_TASK_BODY (stmt) = block;
  SET_ପଦସମଷ୍ଟି_LOCATION (stmt, loc);

  ଫେରନ୍ତୁ add_stmt (stmt);
}

/* Generate GOMP_cancel call for #pragma omp cancel.  */

ଶୂନ୍ୟ
c_finish_omp_cancel (location_t loc, ବୃକ୍ଷ clauses)
{
  ବୃକ୍ଷ fn = builtin_decl_explicit (BUILT_IN_GOMP_CANCEL);
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା mask = 0;
  ଯଦି (omp_find_clause (clauses, OMP_CLAUSE_PARALLEL))
    mask = 1;
  ଅନ୍ୟଥା ଯଦି (omp_find_clause (clauses, OMP_CLAUSE_FOR))
    mask = 2;
  ଅନ୍ୟଥା ଯଦି (omp_find_clause (clauses, OMP_CLAUSE_SECTIONS))
    mask = 4;
  ଅନ୍ୟଥା ଯଦି (omp_find_clause (clauses, OMP_CLAUSE_TASKGROUP))
    mask = 8;
  ଅନ୍ୟଥା
    {
      error_at (loc, "%<#pragma omp cancel%> must specify one of "
		     "%<parallel%>, %<for%>, %<sections%> or %<taskgroup%> "
		     "clauses");
      ଫେରନ୍ତୁ;
    }
  ବୃକ୍ଷ ifc = omp_find_clause (clauses, OMP_CLAUSE_IF);
  ଯଦି (ifc != NULL_ବୃକ୍ଷ)
    {
      ଯଦି (OMP_CLAUSE_IF_MODIFIER (ifc) != ERROR_MARK
	  && OMP_CLAUSE_IF_MODIFIER (ifc) != VOID_CST)
	error_at (OMP_CLAUSE_LOCATION (ifc),
		  "expected %<cancel%> %<if%> clause modifier");
      ଅନ୍ୟଥା
	{
	  ବୃକ୍ଷ ifc2 = omp_find_clause (OMP_CLAUSE_CHAIN (ifc), OMP_CLAUSE_IF);
	  ଯଦି (ifc2 != NULL_ବୃକ୍ଷ)
	    {
	      gcc_assert (OMP_CLAUSE_IF_MODIFIER (ifc) == VOID_CST
			  && OMP_CLAUSE_IF_MODIFIER (ifc2) != ERROR_MARK
			  && OMP_CLAUSE_IF_MODIFIER (ifc2) != VOID_CST);
	      error_at (OMP_CLAUSE_LOCATION (ifc2),
			"expected %<cancel%> %<if%> clause modifier");
	    }
	}

      ବୃକ୍ଷ type = ବୃକ୍ଷ_TYPE (OMP_CLAUSE_IF_ପଦସମଷ୍ଟି (ifc));
      ifc = fold_build2_loc (OMP_CLAUSE_LOCATION (ifc), NE_ପଦସମଷ୍ଟି,
			     boolean_type_ଗଣ୍ଠି, OMP_CLAUSE_IF_ପଦସମଷ୍ଟି (ifc),
			     build_zero_cst (type));
    }
  ଅନ୍ୟଥା
    ifc = boolean_true_ଗଣ୍ଠି;
  ବୃକ୍ଷ stmt = build_call_ପଦସମଷ୍ଟି_loc (loc, fn, 2,
				   build_int_cst (integer_type_ଗଣ୍ଠି, mask),
				   ifc);
  add_stmt (stmt);
}

/* Generate GOMP_cancellation_point call for
   #pragma omp cancellation point.  */

ଶୂନ୍ୟ
c_finish_omp_cancellation_point (location_t loc, ବୃକ୍ଷ clauses)
{
  ବୃକ୍ଷ fn = builtin_decl_explicit (BUILT_IN_GOMP_CANCELLATION_POINT);
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା mask = 0;
  ଯଦି (omp_find_clause (clauses, OMP_CLAUSE_PARALLEL))
    mask = 1;
  ଅନ୍ୟଥା ଯଦି (omp_find_clause (clauses, OMP_CLAUSE_FOR))
    mask = 2;
  ଅନ୍ୟଥା ଯଦି (omp_find_clause (clauses, OMP_CLAUSE_SECTIONS))
    mask = 4;
  ଅନ୍ୟଥା ଯଦି (omp_find_clause (clauses, OMP_CLAUSE_TASKGROUP))
    mask = 8;
  ଅନ୍ୟଥା
    {
      error_at (loc, "%<#pragma omp cancellation point%> must specify one of "
		     "%<parallel%>, %<for%>, %<sections%> or %<taskgroup%> "
		     "clauses");
      ଫେରନ୍ତୁ;
    }
  ବୃକ୍ଷ stmt = build_call_ପଦସମଷ୍ଟି_loc (loc, fn, 1,
				   build_int_cst (integer_type_ଗଣ୍ଠି, mask));
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

ସ୍ଥିର ବୃକ୍ଷ
handle_omp_array_sections_1 (ବୃକ୍ଷ c, ବୃକ୍ଷ t, vec<ବୃକ୍ଷ> &types,
			     ତାର୍କିକ &maybe_zero_len, unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା &first_non_one,
			     ଗଣନା c_omp_region_type ort)
{
  ବୃକ୍ଷ ret, ତଳ_bound, length, type;
  ତାର୍କିକ openacc = (ort & C_ORT_ACC) != 0;
  ଯଦି (ବୃକ୍ଷ_CODE (t) != OMP_ARRAY_SECTION)
    {
      ଯଦି (error_operand_p (t))
	ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
      c_omp_address_inspector ai (OMP_CLAUSE_LOCATION (c), t);
      ret = t;
      ଯଦି (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_AFFINITY
	  && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_DEPEND
	  && TYPE_ATOMIC (strip_array_types (ବୃକ୍ଷ_TYPE (t))))
	{
	  error_at (OMP_CLAUSE_LOCATION (c), "%<_Atomic%> %qE in %qs clause",
		    t, omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	  ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
	}
      ଯଦି (!ai.check_clause (c))
	ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
      ଅନ୍ୟଥା ଯଦି (ai.component_access_p ()
	       && (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP
		   || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_TO
		   || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_FROM))
	t = ai.get_ମୂଳ_term (ସତ୍ୟ);
      ଅନ୍ୟଥା
	t = ai.unconverted_ref_origin ();
      ଯଦି (t == error_mark_ଗଣ୍ଠି)
	ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
      ଯଦି (!VAR_P (t)
	  && (ort == C_ORT_ACC || !ପଦସମଷ୍ଟି_P (t))
	  && ବୃକ୍ଷ_CODE (t) != PARM_DECL)
	{
	  ଯଦି (DECL_P (t))
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%qD is not a variable in %qs clause", t,
		      omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	  ଅନ୍ୟଥା
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%qE is not a variable in %qs clause", t,
		      omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	  ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
	}
      ଅନ୍ୟଥା ଯଦି (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_AFFINITY
	       && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_DEPEND
	       && TYPE_ATOMIC (ବୃକ୍ଷ_TYPE (t)))
	{
	  error_at (OMP_CLAUSE_LOCATION (c), "%<_Atomic%> %qD in %qs clause",
		    t, omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	  ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
	}
      ଅନ୍ୟଥା ଯଦି (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_AFFINITY
	       && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_DEPEND
	       && VAR_P (t)
	       && DECL_THREAD_LOCAL_P (t))
	{
	  error_at (OMP_CLAUSE_LOCATION (c),
		    "%qD is threadprivate variable in %qs clause", t,
		    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	  ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
	}
      ଯଦି ((OMP_CLAUSE_CODE (c) == OMP_CLAUSE_AFFINITY
	   || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND)
	  && TYPE_ATOMIC (ବୃକ୍ଷ_TYPE (t))
	  && POINTER_TYPE_P (ବୃକ୍ଷ_TYPE (t)))
	{
	  /* If the array section is pointer based and the pointer
	     itself is _Atomic qualified, we need to atomically load
	     the pointer.  */
	  ret = convert_lvalue_to_rvalue (OMP_CLAUSE_LOCATION (c),
					  ret, ମିଥ୍ୟା, ମିଥ୍ୟା);
	}
      ଫେରନ୍ତୁ ret;
    }

  ret = handle_omp_array_sections_1 (c, ବୃକ୍ଷ_OPERAND (t, 0), types,
				     maybe_zero_len, first_non_one, ort);
  ଯଦି (ret == error_mark_ଗଣ୍ଠି || ret == NULL_ବୃକ୍ଷ)
    ଫେରନ୍ତୁ ret;

  type = ବୃକ୍ଷ_TYPE (ret);
  ତଳ_bound = ବୃକ୍ଷ_OPERAND (t, 1);
  length = ବୃକ୍ଷ_OPERAND (t, 2);

  ଯଦି (ତଳ_bound == error_mark_ଗଣ୍ଠି || length == error_mark_ଗଣ୍ଠି)
    ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;

  ଯଦି (ତଳ_bound && !INTEGRAL_TYPE_P (ବୃକ୍ଷ_TYPE (ତଳ_bound)))
    {
      error_at (OMP_CLAUSE_LOCATION (c),
		"low bound %qE of array section does not have integral type",
		ତଳ_bound);
      ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
    }
  ଯଦି (length && !INTEGRAL_TYPE_P (ବୃକ୍ଷ_TYPE (length)))
    {
      error_at (OMP_CLAUSE_LOCATION (c),
		"length %qE of array section does not have integral type",
		length);
      ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
    }
  ଯଦି (ତଳ_bound
      && ବୃକ୍ଷ_CODE (ତଳ_bound) == INTEGER_CST
      && TYPE_PRECISION (ବୃକ୍ଷ_TYPE (ତଳ_bound))
	 > TYPE_PRECISION (sizetype))
    ତଳ_bound = fold_convert (sizetype, ତଳ_bound);
  ଯଦି (length
      && ବୃକ୍ଷ_CODE (length) == INTEGER_CST
      && TYPE_PRECISION (ବୃକ୍ଷ_TYPE (length))
	 > TYPE_PRECISION (sizetype))
    length = fold_convert (sizetype, length);
  ଯଦି (ତଳ_bound == NULL_ବୃକ୍ଷ)
    ତଳ_bound = integer_zero_ଗଣ୍ଠି;
  ଯଦି (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP
      && (OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_ATTACH
	  || OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_DETACH))
    {
      ଯଦି (length != integer_one_ଗଣ୍ଠି)
	{
	  error_at (OMP_CLAUSE_LOCATION (c),
		    "expected single pointer in %qs clause",
		    user_omp_clause_code_name (c, openacc));
	  ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
	}
    }
  ଯଦି (length != NULL_ବୃକ୍ଷ)
    {
      ଯଦି (!integer_nonzerop (length))
	{
	  ଯଦି (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_AFFINITY
	      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND
	      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_REDUCTION
	      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IN_REDUCTION
	      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_TASK_REDUCTION)
	    {
	      ଯଦି (integer_zerop (length))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "zero length array section in %qs clause",
			    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		  ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
		}
	    }
	  ଅନ୍ୟଥା
	    maybe_zero_len = ସତ୍ୟ;
	}
      ଯଦି (first_non_one == types.length ()
	  && (ବୃକ୍ଷ_CODE (length) != INTEGER_CST || integer_onep (length)))
	first_non_one++;
    }
  ଯଦି (ବୃକ୍ଷ_CODE (type) == ARRAY_TYPE)
    {
      ଯଦି (length == NULL_ବୃକ୍ଷ
	  && (TYPE_DOMAIN (type) == NULL_ବୃକ୍ଷ
	      || TYPE_MAX_ମୂଲ୍ୟ (TYPE_DOMAIN (type)) == NULL_ବୃକ୍ଷ))
	{
	  error_at (OMP_CLAUSE_LOCATION (c),
		    "for unknown bound array type length expression must "
		    "be specified");
	  ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
	}
      ଯଦି (ବୃକ୍ଷ_CODE (ତଳ_bound) == INTEGER_CST
	  && ବୃକ୍ଷ_int_cst_sgn (ତଳ_bound) == -1)
	{
	  error_at (OMP_CLAUSE_LOCATION (c),
		    "negative low bound in array section in %qs clause",
		    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	  ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
	}
      ଯଦି (length != NULL_ବୃକ୍ଷ
	  && ବୃକ୍ଷ_CODE (length) == INTEGER_CST
	  && ବୃକ୍ଷ_int_cst_sgn (length) == -1)
	{
	  error_at (OMP_CLAUSE_LOCATION (c),
		    "negative length in array section in %qs clause",
		    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	  ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
	}
      ଯଦି (TYPE_DOMAIN (type)
	  && TYPE_MAX_ମୂଲ୍ୟ (TYPE_DOMAIN (type))
	  && ବୃକ୍ଷ_CODE (TYPE_MAX_ମୂଲ୍ୟ (TYPE_DOMAIN (type)))
			== INTEGER_CST)
	{
	  ବୃକ୍ଷ size
	    = fold_convert (sizetype, TYPE_MAX_ମୂଲ୍ୟ (TYPE_DOMAIN (type)));
	  size = size_binop (PLUS_ପଦସମଷ୍ଟି, size, size_one_ଗଣ୍ଠି);
	  ଯଦି (ବୃକ୍ଷ_CODE (ତଳ_bound) == INTEGER_CST)
	    {
	      ଯଦି (ବୃକ୍ଷ_int_cst_lt (size, ତଳ_bound))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "low bound %qE above array section size "
			    "in %qs clause", ତଳ_bound,
			    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		  ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
		}
	      ଯଦି (ବୃକ୍ଷ_int_cst_equal (size, ତଳ_bound))
		{
		  ଯଦି (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_AFFINITY
		      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND
		      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_REDUCTION
		      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IN_REDUCTION
		      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_TASK_REDUCTION)
		    {
		      error_at (OMP_CLAUSE_LOCATION (c),
				"zero length array section in %qs clause",
				omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		      ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
		    }
		  maybe_zero_len = ସତ୍ୟ;
		}
	      ଅନ୍ୟଥା ଯଦି (length == NULL_ବୃକ୍ଷ
		       && first_non_one == types.length ()
		       && ବୃକ୍ଷ_int_cst_equal
			    (TYPE_MAX_ମୂଲ୍ୟ (TYPE_DOMAIN (type)),
			     ତଳ_bound))
		first_non_one++;
	    }
	  ଅନ୍ୟଥା ଯଦି (length == NULL_ବୃକ୍ଷ)
	    {
	      ଯଦି (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_AFFINITY
		  && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_DEPEND
		  && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_REDUCTION
		  && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_IN_REDUCTION
		  && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_TASK_REDUCTION)
		maybe_zero_len = ସତ୍ୟ;
	      ଯଦି (first_non_one == types.length ())
		first_non_one++;
	    }
	  ଯଦି (length && ବୃକ୍ଷ_CODE (length) == INTEGER_CST)
	    {
	      ଯଦି (ବୃକ୍ଷ_int_cst_lt (size, length))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "length %qE above array section size "
			    "in %qs clause", length,
			    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		  ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
		}
	      ଯଦି (ବୃକ୍ଷ_CODE (ତଳ_bound) == INTEGER_CST)
		{
		  ବୃକ୍ଷ lbpluslen
		    = size_binop (PLUS_ପଦସମଷ୍ଟି,
				  fold_convert (sizetype, ତଳ_bound),
				  fold_convert (sizetype, length));
		  ଯଦି (ବୃକ୍ଷ_CODE (lbpluslen) == INTEGER_CST
		      && ବୃକ୍ଷ_int_cst_lt (size, lbpluslen))
		    {
		      error_at (OMP_CLAUSE_LOCATION (c),
				"high bound %qE above array section size "
				"in %qs clause", lbpluslen,
				omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		      ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
		    }
		}
	    }
	}
      ଅନ୍ୟଥା ଯଦି (length == NULL_ବୃକ୍ଷ)
	{
	  ଯଦି (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_AFFINITY
	      && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_DEPEND
	      && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_REDUCTION
	      && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_IN_REDUCTION
	      && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_TASK_REDUCTION)
	    maybe_zero_len = ସତ୍ୟ;
	  ଯଦି (first_non_one == types.length ())
	    first_non_one++;
	}

      /* For [lb:] we will need to evaluate lb more than once.  */
      ଯଦି (length == NULL_ବୃକ୍ଷ && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_DEPEND)
	{
	  ବୃକ୍ଷ lb = save_ପଦସମଷ୍ଟି (ତଳ_bound);
	  ଯଦି (lb != ତଳ_bound)
	    {
	      ବୃକ୍ଷ_OPERAND (t, 1) = lb;
	      ତଳ_bound = lb;
	    }
	}
    }
  ଅନ୍ୟଥା ଯଦି (ବୃକ୍ଷ_CODE (type) == POINTER_TYPE)
    {
      ଯଦି (length == NULL_ବୃକ୍ଷ)
	{
	  ଯଦି (ବୃକ୍ଷ_CODE (ret) == PARM_DECL && C_ARRAY_PARAMETER (ret))
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "for array function parameter length expression "
		      "must be specified");
	  ଅନ୍ୟଥା
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "for pointer type length expression must be specified");
	  ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
	}
      ଯଦି (length != NULL_ବୃକ୍ଷ
	  && ବୃକ୍ଷ_CODE (length) == INTEGER_CST
	  && ବୃକ୍ଷ_int_cst_sgn (length) == -1)
	{
	  error_at (OMP_CLAUSE_LOCATION (c),
		    "negative length in array section in %qs clause",
		    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	  ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
	}
      /* If there is a pointer type anywhere but in the very first
	 array-section-subscript, the array section could be non-contiguous.  */
      ଯଦି (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_DEPEND
	  && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_AFFINITY
	  && ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_OPERAND (t, 0)) == OMP_ARRAY_SECTION)
	{
	  /* If any prior dimension has a non-one length, then deem this
	     array section as non-contiguous.  */
	  ପାଇଁ (ବୃକ୍ଷ d = ବୃକ୍ଷ_OPERAND (t, 0);
	       ବୃକ୍ଷ_CODE (d) == OMP_ARRAY_SECTION;
	       d = ବୃକ୍ଷ_OPERAND (d, 0))
	    {
	      ବୃକ୍ଷ d_length = ବୃକ୍ଷ_OPERAND (d, 2);
	      ଯଦି (d_length == NULL_ବୃକ୍ଷ || !integer_onep (d_length))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "array section is not contiguous in %qs clause",
			    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		  ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
		}
	    }
	}
    }
  ଅନ୍ୟଥା
    {
      error_at (OMP_CLAUSE_LOCATION (c),
		"%qE does not have pointer or array type", ret);
      ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
    }
  ଯଦି (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_DEPEND)
    types.safe_ଠେଲ (ବୃକ୍ଷ_TYPE (ret));
  /* We will need to evaluate lb more than once.  */
  ବୃକ୍ଷ lb = save_ପଦସମଷ୍ଟି (ତଳ_bound);
  ଯଦି (lb != ତଳ_bound)
    {
      ବୃକ୍ଷ_OPERAND (t, 1) = lb;
      ତଳ_bound = lb;
    }
  ret = build_array_ref (OMP_CLAUSE_LOCATION (c), ret, ତଳ_bound);
  ଫେରନ୍ତୁ ret;
}

/* Handle array sections for clause C.  */

ସ୍ଥିର ତାର୍କିକ
handle_omp_array_sections (ବୃକ୍ଷ &c, ଗଣନା c_omp_region_type ort)
{
  ତାର୍କିକ maybe_zero_len = ମିଥ୍ୟା;
  unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା first_non_one = 0;
  auto_vec<ବୃକ୍ଷ, 10> types;
  ବୃକ୍ଷ *tp = &OMP_CLAUSE_DECL (c);
  ଯଦି ((OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND
       || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_AFFINITY)
      && OMP_ITERATOR_DECL_P (*tp))
    tp = &ବୃକ୍ଷ_ମୂଲ୍ୟ (*tp);
  ବୃକ୍ଷ first = handle_omp_array_sections_1 (c, *tp, types,
					    maybe_zero_len, first_non_one,
					    ort);
  ଯଦି (first == error_mark_ଗଣ୍ଠି)
    ଫେରନ୍ତୁ ସତ୍ୟ;
  ଯଦି (first == NULL_ବୃକ୍ଷ)
    ଫେରନ୍ତୁ ମିଥ୍ୟା;
  ଯଦି (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND
      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_AFFINITY)
    {
      ବୃକ୍ଷ t = *tp;
      ବୃକ୍ଷ tem = NULL_ବୃକ୍ଷ;
      /* Need to evaluate side effects in the length expressions
	 if any.  */
      ଯେତେବେଳେ (ବୃକ୍ଷ_CODE (t) == ବୃକ୍ଷ_LIST)
	{
	  ଯଦି (ବୃକ୍ଷ_ମୂଲ୍ୟ (t) && ବୃକ୍ଷ_SIDE_EFFECTS (ବୃକ୍ଷ_ମୂଲ୍ୟ (t)))
	    {
	      ଯଦି (tem == NULL_ବୃକ୍ଷ)
		tem = ବୃକ୍ଷ_ମୂଲ୍ୟ (t);
	      ଅନ୍ୟଥା
		tem = build2 (COMPOUND_ପଦସମଷ୍ଟି, ବୃକ୍ଷ_TYPE (tem),
			      ବୃକ୍ଷ_ମୂଲ୍ୟ (t), tem);
	    }
	  t = ବୃକ୍ଷ_CHAIN (t);
	}
      ଯଦି (tem)
	first = build2 (COMPOUND_ପଦସମଷ୍ଟି, ବୃକ୍ଷ_TYPE (first), tem, first);
      first = c_fully_fold (first, ମିଥ୍ୟା, ଖାଲି, ସତ୍ୟ);
      *tp = first;
    }
  ଅନ୍ୟଥା
    {
      unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଅଙ୍କ = types.length (), i;
      ବୃକ୍ଷ t, side_effects = NULL_ବୃକ୍ଷ, size = NULL_ବୃକ୍ଷ;
      ବୃକ୍ଷ condition = NULL_ବୃକ୍ଷ;

      ଯଦି (int_size_in_bytes (ବୃକ୍ଷ_TYPE (first)) <= 0)
	maybe_zero_len = ସତ୍ୟ;

      ପାଇଁ (i = ଅଙ୍କ, t = OMP_CLAUSE_DECL (c); i > 0;
	   t = ବୃକ୍ଷ_OPERAND (t, 0))
	{
	  ବୃକ୍ଷ ତଳ_bound = ବୃକ୍ଷ_OPERAND (t, 1);
	  ବୃକ୍ଷ length = ବୃକ୍ଷ_OPERAND (t, 2);

	  i--;
	  ଯଦି (ତଳ_bound
	      && ବୃକ୍ଷ_CODE (ତଳ_bound) == INTEGER_CST
	      && TYPE_PRECISION (ବୃକ୍ଷ_TYPE (ତଳ_bound))
		 > TYPE_PRECISION (sizetype))
	    ତଳ_bound = fold_convert (sizetype, ତଳ_bound);
	  ଯଦି (length
	      && ବୃକ୍ଷ_CODE (length) == INTEGER_CST
	      && TYPE_PRECISION (ବୃକ୍ଷ_TYPE (length))
		 > TYPE_PRECISION (sizetype))
	    length = fold_convert (sizetype, length);
	  ଯଦି (ତଳ_bound == NULL_ବୃକ୍ଷ)
	    ତଳ_bound = integer_zero_ଗଣ୍ଠି;
	  ଯଦି (!maybe_zero_len && i > first_non_one)
	    {
	      ଯଦି (integer_nonzerop (ତଳ_bound))
		ଯାଅ do_warn_noncontiguous;
	      ଯଦି (length != NULL_ବୃକ୍ଷ
		  && ବୃକ୍ଷ_CODE (length) == INTEGER_CST
		  && TYPE_DOMAIN (types[i])
		  && TYPE_MAX_ମୂଲ୍ୟ (TYPE_DOMAIN (types[i]))
		  && ବୃକ୍ଷ_CODE (TYPE_MAX_ମୂଲ୍ୟ (TYPE_DOMAIN (types[i])))
		     == INTEGER_CST)
		{
		  ବୃକ୍ଷ size;
		  size = size_binop (PLUS_ପଦସମଷ୍ଟି,
				     TYPE_MAX_ମୂଲ୍ୟ (TYPE_DOMAIN (types[i])),
				     size_one_ଗଣ୍ଠି);
		  ଯଦି (!ବୃକ୍ଷ_int_cst_equal (length, size))
		    {
		     do_warn_noncontiguous:
		      error_at (OMP_CLAUSE_LOCATION (c),
				"array section is not contiguous in %qs "
				"clause",
				omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		      ଫେରନ୍ତୁ ସତ୍ୟ;
		    }
		}
	      ଯଦି (length != NULL_ବୃକ୍ଷ
		  && ବୃକ୍ଷ_SIDE_EFFECTS (length))
		{
		  ଯଦି (side_effects == NULL_ବୃକ୍ଷ)
		    side_effects = length;
		  ଅନ୍ୟଥା
		    side_effects = build2 (COMPOUND_ପଦସମଷ୍ଟି,
					   ବୃକ୍ଷ_TYPE (side_effects),
					   length, side_effects);
		}
	    }
	  ଅନ୍ୟଥା
	    {
	      ବୃକ୍ଷ l;

	      ଯଦି (i > first_non_one
		  && ((length && integer_nonzerop (length))
		      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_REDUCTION
		      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IN_REDUCTION
		      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_TASK_REDUCTION))
		ଜାରି;
	      ଯଦି (length)
		l = fold_convert (sizetype, length);
	      ଅନ୍ୟଥା
		{
		  l = size_binop (PLUS_ପଦସମଷ୍ଟି,
				  TYPE_MAX_ମୂଲ୍ୟ (TYPE_DOMAIN (types[i])),
				  size_one_ଗଣ୍ଠି);
		  l = size_binop (MINUS_ପଦସମଷ୍ଟି, l,
				  fold_convert (sizetype, ତଳ_bound));
		}
	      ଯଦି (i > first_non_one)
		{
		  l = fold_build2 (NE_ପଦସମଷ୍ଟି, boolean_type_ଗଣ୍ଠି, l,
				   size_zero_ଗଣ୍ଠି);
		  ଯଦି (condition == NULL_ବୃକ୍ଷ)
		    condition = l;
		  ଅନ୍ୟଥା
		    condition = fold_build2 (BIT_AND_ପଦସମଷ୍ଟି, boolean_type_ଗଣ୍ଠି,
					     l, condition);
		}
	      ଅନ୍ୟଥା ଯଦି (size == NULL_ବୃକ୍ଷ)
		{
		  size = size_in_bytes (ବୃକ୍ଷ_TYPE (types[i]));
		  ବୃକ୍ଷ eltype = ବୃକ୍ଷ_TYPE (types[ଅଙ୍କ - 1]);
		  ଯେତେବେଳେ (ବୃକ୍ଷ_CODE (eltype) == ARRAY_TYPE)
		    eltype = ବୃକ୍ଷ_TYPE (eltype);
		  ଯଦି (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_REDUCTION
		      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IN_REDUCTION
		      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_TASK_REDUCTION)
		    {
		      ଯଦି (integer_zerop (size)
			  || integer_zerop (size_in_bytes (eltype)))
			{
			  error_at (OMP_CLAUSE_LOCATION (c),
				    "zero length array section in %qs clause",
				    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
			  ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
			}
		      size = size_binop (EXACT_DIV_ପଦସମଷ୍ଟି, size,
					 size_in_bytes (eltype));
		    }
		  size = size_binop (MULT_ପଦସମଷ୍ଟି, size, l);
		  ଯଦି (condition)
		    size = fold_build3 (COND_ପଦସମଷ୍ଟି, sizetype, condition,
					size, size_zero_ଗଣ୍ଠି);
		}
	      ଅନ୍ୟଥା
		size = size_binop (MULT_ପଦସମଷ୍ଟି, size, l);
	    }
	}
      ଯଦି (side_effects)
	size = build2 (COMPOUND_ପଦସମଷ୍ଟି, sizetype, side_effects, size);
      ଯଦି (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_REDUCTION
	  || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IN_REDUCTION
	  || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_TASK_REDUCTION)
	{
	  size = size_binop (MINUS_ପଦସମଷ୍ଟି, size, size_one_ଗଣ୍ଠି);
	  size = c_fully_fold (size, ମିଥ୍ୟା, ଖାଲି);
	  size = save_ପଦସମଷ୍ଟି (size);
	  ବୃକ୍ଷ index_type = build_index_type (size);
	  ବୃକ୍ଷ eltype = ବୃକ୍ଷ_TYPE (first);
	  ଯେତେବେଳେ (ବୃକ୍ଷ_CODE (eltype) == ARRAY_TYPE)
	    eltype = ବୃକ୍ଷ_TYPE (eltype);
	  ବୃକ୍ଷ type = c_build_array_type (eltype, index_type);
	  ବୃକ୍ଷ ptype = c_build_pointer_type (eltype);
	  ଯଦି (ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (t)) == ARRAY_TYPE)
	    t = build_fold_addr_ପଦସମଷ୍ଟି (t);
	  ବୃକ୍ଷ t2 = build_fold_addr_ପଦସମଷ୍ଟି (first);
	  t2 = fold_convert_loc (OMP_CLAUSE_LOCATION (c),
				 ptrdiff_type_ଗଣ୍ଠି, t2);
	  t2 = fold_build2_loc (OMP_CLAUSE_LOCATION (c), MINUS_ପଦସମଷ୍ଟି,
				ptrdiff_type_ଗଣ୍ଠି, t2,
				fold_convert_loc (OMP_CLAUSE_LOCATION (c),
						  ptrdiff_type_ଗଣ୍ଠି, t));
	  t2 = c_fully_fold (t2, ମିଥ୍ୟା, ଖାଲି);
	  ଯଦି (ବୃକ୍ଷ_fits_shwi_p (t2))
	    t = build2 (MEM_REF, type, t,
			build_int_cst (ptype, ବୃକ୍ଷ_to_shwi (t2)));
	  ଅନ୍ୟଥା
	    {
	      t2 = fold_convert_loc (OMP_CLAUSE_LOCATION (c), sizetype, t2);
	      t = build2_loc (OMP_CLAUSE_LOCATION (c), POINTER_PLUS_ପଦସମଷ୍ଟି,
			      ବୃକ୍ଷ_TYPE (t), t, t2);
	      t = build2 (MEM_REF, type, t, build_int_cst (ptype, 0));
	    }
	  OMP_CLAUSE_DECL (c) = t;
	  ଫେରନ୍ତୁ ମିଥ୍ୟା;
	}
      first = c_fully_fold (first, ମିଥ୍ୟା, ଖାଲି);
      OMP_CLAUSE_DECL (c) = first;
      ଯଦି (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_HAS_DEVICE_ADDR)
	ଫେରନ୍ତୁ ମିଥ୍ୟା;
      /* Don't set OMP_CLAUSE_SIZE for bare attach/detach clauses.  */
      ଯଦି (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_MAP
	  || (OMP_CLAUSE_MAP_KIND (c) != GOMP_MAP_ATTACH
	      && OMP_CLAUSE_MAP_KIND (c) != GOMP_MAP_DETACH
	      && OMP_CLAUSE_MAP_KIND (c) != GOMP_MAP_FORCE_DETACH))
	{
	  ଯଦି (size)
	    size = c_fully_fold (size, ମିଥ୍ୟା, ଖାଲି);
	  OMP_CLAUSE_SIZE (c) = size;
	}

      ଯଦି (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_MAP)
	ଫେରନ୍ତୁ ମିଥ୍ୟା;

      auto_vec<omp_addr_token *, 10> addr_tokens;

      ଯଦି (!omp_parse_ପଦସମଷ୍ଟି (addr_tokens, first))
	ଫେରନ୍ତୁ ସତ୍ୟ;

      c_omp_address_inspector ai (OMP_CLAUSE_LOCATION (c), t);

      ବୃକ୍ଷ nc = ai.expand_map_clause (c, first, addr_tokens, ort);
      ଯଦି (nc != error_mark_ଗଣ୍ଠି)
	{
	  using ନାମାକାଶ omp_addr_tokenizer;

	  ଯଦି (ai.maybe_zero_length_array_section (c))
	    OMP_CLAUSE_MAP_MAYBE_ZERO_LENGTH_ARRAY_SECTION (c) = 1;

	  /* !!! If we're accessing a base decl via chained access
	     methods (e.g. multiple indirections), duplicate clause
	     detection won't work properly.  Skip it in that case.  */
	  ଯଦି ((addr_tokens[0]->type == STRUCTURE_BASE
	       || addr_tokens[0]->type == ARRAY_BASE)
	      && addr_tokens[0]->u.structure_base_kind == BASE_DECL
	      && addr_tokens[1]->type == ACCESS_METHOD
	      && omp_access_chain_p (addr_tokens, 1))
	    c = nc;

	  ଫେରନ୍ତୁ ମିଥ୍ୟା;
	}
    }
  ଫେରନ୍ତୁ ମିଥ୍ୟା;
}

/* Helper function of finish_omp_clauses.  Clone STMT as if we were making
   an inline call.  But, remap
   the OMP_DECL1 VAR_DECL (omp_out resp. omp_orig) to PLACEHOLDER
   and OMP_DECL2 VAR_DECL (omp_in resp. omp_priv) to DECL.  */

ସ୍ଥିର ବୃକ୍ଷ
c_clone_omp_udr (ବୃକ୍ଷ stmt, ବୃକ୍ଷ omp_decl1, ବୃକ୍ଷ omp_decl2,
		 ବୃକ୍ଷ decl, ବୃକ୍ଷ placeholder)
{
  copy_body_data id;
  hash_map<ବୃକ୍ଷ, ବୃକ୍ଷ> decl_map;

  decl_map.put (omp_decl1, placeholder);
  decl_map.put (omp_decl2, decl);
  memset (&id, 0, ଆକାର (id));
  id.src_fn = DECL_CONTEXT (omp_decl1);
  id.dst_fn = current_function_decl;
  id.src_cfun = DECL_STRUCT_FUNCTION (id.src_fn);
  id.decl_map = &decl_map;

  id.copy_decl = copy_decl_no_change;
  id.transform_call_graph_edges = CB_CGE_DUPLICATE;
  id.transform_new_cfg = ସତ୍ୟ;
  id.transform_return_to_modify = ମିଥ୍ୟା;
  id.eh_lp_nr = 0;
  walk_ବୃକ୍ଷ (&stmt, copy_ବୃକ୍ଷ_body_r, &id, ଖାଲି);
  ଫେରନ୍ତୁ stmt;
}

/* Helper function of c_finish_omp_clauses, called via walk_tree.
   Find OMP_CLAUSE_PLACEHOLDER (passed in DATA) in *TP.  */

ସ୍ଥିର ବୃକ୍ଷ
c_find_omp_placeholder_r (ବୃକ୍ଷ *tp, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *, ଶୂନ୍ୟ *data)
{
  ଯଦି (*tp == (ବୃକ୍ଷ) data)
    ଫେରନ୍ତୁ *tp;
  ଫେରନ୍ତୁ NULL_ବୃକ୍ଷ;
}

/* Similarly, but also walk aggregate fields.  */

ସଂରଚନା c_find_omp_var_s { ବୃକ୍ଷ var; hash_set<ବୃକ୍ଷ> *pset; };

ସ୍ଥିର ବୃକ୍ଷ
c_find_omp_var_r (ବୃକ୍ଷ *tp, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *, ଶୂନ୍ୟ *data)
{
  ଯଦି (*tp == ((ସଂରଚନା c_find_omp_var_s *) data)->var)
    ଫେରନ୍ତୁ *tp;
  ଯଦି (RECORD_OR_UNION_TYPE_P (*tp))
    {
      ବୃକ୍ଷ field;
      hash_set<ବୃକ୍ଷ> *pset = ((ସଂରଚନା c_find_omp_var_s *) data)->pset;

      ପାଇଁ (field = TYPE_FIELDS (*tp); field;
	   field = DECL_CHAIN (field))
	ଯଦି (ବୃକ୍ଷ_CODE (field) == FIELD_DECL)
	  {
	    ବୃକ୍ଷ ret = walk_ବୃକ୍ଷ (&DECL_FIELD_OFFSET (field),
				  c_find_omp_var_r, data, pset);
	    ଯଦି (ret)
	      ଫେରନ୍ତୁ ret;
	    ret = walk_ବୃକ୍ଷ (&DECL_SIZE (field), c_find_omp_var_r, data, pset);
	    ଯଦି (ret)
	      ଫେରନ୍ତୁ ret;
	    ret = walk_ବୃକ୍ଷ (&DECL_SIZE_UNIT (field), c_find_omp_var_r, data,
			     pset);
	    ଯଦି (ret)
	      ଫେରନ୍ତୁ ret;
	    ret = walk_ବୃକ୍ଷ (&ବୃକ୍ଷ_TYPE (field), c_find_omp_var_r, data, pset);
	    ଯଦି (ret)
	      ଫେରନ୍ତୁ ret;
	  }
    }
  ଅନ୍ୟଥା ଯଦି (INTEGRAL_TYPE_P (*tp))
    ଫେରନ୍ତୁ walk_ବୃକ୍ଷ (&TYPE_MAX_ମୂଲ୍ୟ (*tp), c_find_omp_var_r, data,
		      ((ସଂରଚନା c_find_omp_var_s *) data)->pset);
  ଫେରନ୍ତୁ NULL_ବୃକ୍ଷ;
}

/* Finish OpenMP iterators ITER.  Return true if they are erroneous
   and clauses containing them should be removed.  */

ସ୍ଥିର ତାର୍କିକ
c_omp_finish_iterators (ବୃକ୍ଷ iter)
{
  ତାର୍କିକ ret = ମିଥ୍ୟା;
  ପାଇଁ (ବୃକ୍ଷ it = iter; it; it = ବୃକ୍ଷ_CHAIN (it))
    {
      ବୃକ୍ଷ var = OMP_ITERATOR_VAR (it);
      ବୃକ୍ଷ begin = OMP_ITERATOR_BEGIN (it);
      ବୃକ୍ଷ end = OMP_ITERATOR_END (it);
      ବୃକ୍ଷ step = OMP_ITERATOR_STEP (it);
      ବୃକ୍ଷ orig_step;
      ବୃକ୍ଷ type = ବୃକ୍ଷ_TYPE (var);
      location_t loc = DECL_SOURCE_LOCATION (var);
      ଯଦି (type == error_mark_ଗଣ୍ଠି)
	{
	  ret = ସତ୍ୟ;
	  ଜାରି;
	}
      ଯଦି (!INTEGRAL_TYPE_P (type) && !POINTER_TYPE_P (type))
	{
	  error_at (loc, "iterator %qD has neither integral nor pointer type",
		    var);
	  ret = ସତ୍ୟ;
	  ଜାରି;
	}
      ଅନ୍ୟଥା ଯଦି (TYPE_ATOMIC (type))
	{
	  error_at (loc, "iterator %qD has %<_Atomic%> qualified type", var);
	  ret = ସତ୍ୟ;
	  ଜାରି;
	}
      ଅନ୍ୟଥା ଯଦି (TYPE_READONLY (type))
	{
	  error_at (loc, "iterator %qD has const qualified type", var);
	  ret = ସତ୍ୟ;
	  ଜାରି;
	}
      ଅନ୍ୟଥା ଯଦି (step == error_mark_ଗଣ୍ଠି
	       || ବୃକ୍ଷ_TYPE (step) == error_mark_ଗଣ୍ଠି)
	{
	  ret = ସତ୍ୟ;
	  ଜାରି;
	}
      ଅନ୍ୟଥା ଯଦି (!INTEGRAL_TYPE_P (ବୃକ୍ଷ_TYPE (step)))
	{
	  error_at (ପଦସମଷ୍ଟି_LOC_OR_LOC (step, loc),
		    "iterator step with non-integral type");
	  ret = ସତ୍ୟ;
	  ଜାରି;
	}
      begin = c_fully_fold (build_c_cast (loc, type, begin), ମିଥ୍ୟା, ଖାଲି);
      end = c_fully_fold (build_c_cast (loc, type, end), ମିଥ୍ୟା, ଖାଲି);
      orig_step = save_ପଦସମଷ୍ଟି (c_fully_fold (step, ମିଥ୍ୟା, ଖାଲି));
      ବୃକ୍ଷ stype = POINTER_TYPE_P (type) ? sizetype : type;
      step = c_fully_fold (build_c_cast (loc, stype, orig_step), ମିଥ୍ୟା, ଖାଲି);
      ଯଦି (POINTER_TYPE_P (type))
	{
	  begin = save_ପଦସମଷ୍ଟି (begin);
	  step = pointer_int_sum (loc, PLUS_ପଦସମଷ୍ଟି, begin, step);
	  step = fold_build2_loc (loc, MINUS_ପଦସମଷ୍ଟି, sizetype,
				  fold_convert (sizetype, step),
				  fold_convert (sizetype, begin));
	  step = fold_convert (ssizetype, step);
	}
      ଯଦି (integer_zerop (step))
	{
	  error_at (loc, "iterator %qD has zero step", var);
	  ret = ସତ୍ୟ;
	  ଜାରି;
	}

      ଯଦି (begin == error_mark_ଗଣ୍ଠି
	  || end == error_mark_ଗଣ୍ଠି
	  || step == error_mark_ଗଣ୍ଠି
	  || orig_step == error_mark_ଗଣ୍ଠି)
	{
	  ret = ସତ୍ୟ;
	  ଜାରି;
	}
      hash_set<ବୃକ୍ଷ> pset;
      ବୃକ୍ଷ it2;
      ପାଇଁ (it2 = ବୃକ୍ଷ_CHAIN (it); it2; it2 = ବୃକ୍ଷ_CHAIN (it2))
	{
	  ବୃକ୍ଷ var2 = OMP_ITERATOR_VAR (it2);
	  ବୃକ୍ଷ begin2 = OMP_ITERATOR_BEGIN (it2);
	  ବୃକ୍ଷ end2 = OMP_ITERATOR_END (it2);
	  ବୃକ୍ଷ step2 = OMP_ITERATOR_STEP (it2);
	  ବୃକ୍ଷ type2 = ବୃକ୍ଷ_TYPE (var2);
	  location_t loc2 = DECL_SOURCE_LOCATION (var2);
	  ସଂରଚନା c_find_omp_var_s data = { var, &pset };
	  ଯଦି (walk_ବୃକ୍ଷ (&type2, c_find_omp_var_r, &data, &pset))
	    {
	      error_at (loc2,
			"type of iterator %qD refers to outer iterator %qD",
			var2, var);
	      ଭାଙ୍ଗ;
	    }
	  ଅନ୍ୟଥା ଯଦି (walk_ବୃକ୍ଷ (&begin2, c_find_omp_var_r, &data, &pset))
	    {
	      error_at (ପଦସମଷ୍ଟି_LOC_OR_LOC (begin2, loc2),
			"begin expression refers to outer iterator %qD", var);
	      ଭାଙ୍ଗ;
	    }
	  ଅନ୍ୟଥା ଯଦି (walk_ବୃକ୍ଷ (&end2, c_find_omp_var_r, &data, &pset))
	    {
	      error_at (ପଦସମଷ୍ଟି_LOC_OR_LOC (end2, loc2),
			"end expression refers to outer iterator %qD", var);
	      ଭାଙ୍ଗ;
	    }
	  ଅନ୍ୟଥା ଯଦି (walk_ବୃକ୍ଷ (&step2, c_find_omp_var_r, &data, &pset))
	    {
	      error_at (ପଦସମଷ୍ଟି_LOC_OR_LOC (step2, loc2),
			"step expression refers to outer iterator %qD", var);
	      ଭାଙ୍ଗ;
	    }
	}
      ଯଦି (it2)
	{
	  ret = ସତ୍ୟ;
	  ଜାରି;
	}
      OMP_ITERATOR_BEGIN (it) = begin;
      OMP_ITERATOR_END (it) = end;
      OMP_ITERATOR_STEP (it) = step;
      OMP_ITERATOR_ORIG_STEP (it) = orig_step;
    }
  ଫେରନ୍ତୁ ret;
}

/* Ensure that pointers are used in OpenACC attach and detach clauses.
   Return true if an error has been detected.  */

ସ୍ଥିର ତାର୍କିକ
c_oacc_check_attachments (ବୃକ୍ଷ c)
{
  ଯଦି (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_MAP)
    ଫେରନ୍ତୁ ମିଥ୍ୟା;

  /* OpenACC attach / detach clauses must be pointers.  */
  ଯଦି (OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_ATTACH
      || OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_DETACH)
    {
      ବୃକ୍ଷ t = OMP_CLAUSE_DECL (c);

      ଯେତେବେଳେ (ବୃକ୍ଷ_CODE (t) == OMP_ARRAY_SECTION)
	t = ବୃକ୍ଷ_OPERAND (t, 0);

      ଯଦି (ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (t)) != POINTER_TYPE)
	{
	  error_at (OMP_CLAUSE_LOCATION (c), "expected pointer in %qs clause",
		    user_omp_clause_code_name (c, ସତ୍ୟ));
	  ଫେରନ୍ତୁ ସତ୍ୟ;
	}
    }

  ଫେରନ୍ତୁ ମିଥ୍ୟା;
}

/* For all elements of CLAUSES, validate them against their constraints.
   Remove any elements from the list that are invalid.  */

ବୃକ୍ଷ
c_finish_omp_clauses (ବୃକ୍ଷ clauses, ଗଣନା c_omp_region_type ort)
{
  bitmap_head generic_head, firstprivate_head, lastprivate_head;
  bitmap_head aligned_head, map_head, map_field_head, map_firstprivate_head;
  bitmap_head oacc_reduction_head, is_on_device_head;
  ବୃକ୍ଷ c, t, type, *pc;
  ବୃକ୍ଷ simdlen = NULL_ବୃକ୍ଷ, safelen = NULL_ବୃକ୍ଷ;
  ତାର୍କିକ branch_seen = ମିଥ୍ୟା;
  ତାର୍କିକ copyprivate_seen = ମିଥ୍ୟା;
  ତାର୍କିକ mergeable_seen = ମିଥ୍ୟା;
  ବୃକ୍ଷ *detach_seen = ଖାଲି;
  ତାର୍କିକ linear_variable_step_check = ମିଥ୍ୟା;
  ବୃକ୍ଷ *nowait_clause = ଖାଲି;
  ବୃକ୍ଷ *grainsize_seen = ଖାଲି;
  ତାର୍କିକ ଅଙ୍କ_tasks_seen = ମିଥ୍ୟା;
  ବୃକ୍ଷ ordered_clause = NULL_ବୃକ୍ଷ;
  ବୃକ୍ଷ schedule_clause = NULL_ବୃକ୍ଷ;
  ତାର୍କିକ oacc_async = ମିଥ୍ୟା;
  ବୃକ୍ଷ last_iterators = NULL_ବୃକ୍ଷ;
  ତାର୍କିକ last_iterators_remove = ମିଥ୍ୟା;
  ବୃକ୍ଷ *nogroup_seen = ଖାଲି;
  ବୃକ୍ଷ *order_clause = ଖାଲି;
  /* 1 if normal/task reduction has been seen, -1 if inscan reduction
     has been seen, -2 if mixed inscan/normal reduction diagnosed.  */
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା reduction_seen = 0;
  ତାର୍କିକ allocate_seen = ମିଥ୍ୟା;
  ତାର୍କିକ implicit_moved = ମିଥ୍ୟା;
  ତାର୍କିକ target_in_reduction_seen = ମିଥ୍ୟା;
  ବୃକ୍ଷ *full_seen = ଖାଲି;
  ତାର୍କିକ partial_seen = ମିଥ୍ୟା;
  ତାର୍କିକ openacc = (ort & C_ORT_ACC) != 0;
  ତାର୍କିକ init_seen = ମିଥ୍ୟା;
  ତାର୍କିକ init_use_destroy_seen = ମିଥ୍ୟା;
  ବୃକ୍ଷ init_no_targetsync_clause = NULL_ବୃକ୍ଷ;
  ବୃକ୍ଷ depend_clause = NULL_ବୃକ୍ଷ;

  ଯଦି (!openacc)
    clauses = omp_remove_duplicate_maps (clauses, ସତ୍ୟ);

  bitmap_obstack_initialize (ଖାଲି);
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

  ଯଦି (openacc)
    ପାଇଁ (c = clauses; c; c = OMP_CLAUSE_CHAIN (c))
      ଯଦି (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_ASYNC)
	{
	  oacc_async = ସତ୍ୟ;
	  ଭାଙ୍ଗ;
	}

  ବୃକ୍ଷ *grp_start_p = ଖାଲି, grp_sentinel = NULL_ବୃକ୍ଷ;

  ପାଇଁ (pc = &clauses, c = clauses; c ; c = *pc)
    {
      ତାର୍କିକ remove = ମିଥ୍ୟା;
      ତାର୍କିକ need_complete = ମିଥ୍ୟା;
      ତାର୍କିକ need_implicitly_determined = ମିଥ୍ୟା;

      /* We've reached the end of a list of expanded nodes.  Reset the group
	 start pointer.  */
      ଯଦି (c == grp_sentinel)
	{
	  ଯଦି (grp_start_p
	      && OMP_CLAUSE_HAS_ITERATORS (*grp_start_p))
	    ପାଇଁ (ବୃକ୍ଷ gc = *grp_start_p; gc != grp_sentinel;
		 gc = OMP_CLAUSE_CHAIN (gc))
	      OMP_CLAUSE_ITERATORS (gc) = OMP_CLAUSE_ITERATORS (*grp_start_p);
	  grp_start_p = ଖାଲି;
	}

      ବାଛ (OMP_CLAUSE_CODE (c))
	{
	ସ୍ଥିତି OMP_CLAUSE_SHARED:
	  need_implicitly_determined = ସତ୍ୟ;
	  ଯାଅ check_dup_generic;

	ସ୍ଥିତି OMP_CLAUSE_PRIVATE:
	  need_complete = ସତ୍ୟ;
	  need_implicitly_determined = ସତ୍ୟ;
	  ଯାଅ check_dup_generic;

	ସ୍ଥିତି OMP_CLAUSE_REDUCTION:
	  ଯଦି (reduction_seen == 0)
	    reduction_seen = OMP_CLAUSE_REDUCTION_INSCAN (c) ? -1 : 1;
	  ଅନ୍ୟଥା ଯଦି (reduction_seen != -2
		   && reduction_seen != (OMP_CLAUSE_REDUCTION_INSCAN (c)
					 ? -1 : 1))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<inscan%> and non-%<inscan%> %<reduction%> clauses "
			"on the same construct");
	      reduction_seen = -2;
	    }
	  /* FALLTHRU */
	ସ୍ଥିତି OMP_CLAUSE_IN_REDUCTION:
	ସ୍ଥିତି OMP_CLAUSE_TASK_REDUCTION:
	  need_implicitly_determined = ସତ୍ୟ;
	  t = OMP_CLAUSE_DECL (c);
	  ଯଦି (ବୃକ୍ଷ_CODE (t) == OMP_ARRAY_SECTION)
	    {
	      ଯଦି (handle_omp_array_sections (c, ort))
		{
		  remove = ସତ୍ୟ;
		  ଭାଙ୍ଗ;
		}

	      t = OMP_CLAUSE_DECL (c);
	      ଯଦି (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_REDUCTION
		  && OMP_CLAUSE_REDUCTION_INSCAN (c))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%<inscan%> %<reduction%> clause with array "
			    "section");
		  remove = ସତ୍ୟ;
		  ଭାଙ୍ଗ;
		}
	    }
	  t = require_complete_type (OMP_CLAUSE_LOCATION (c), t);
	  ଯଦି (t == error_mark_ଗଣ୍ଠି)
	    {
	      remove = ସତ୍ୟ;
	      ଭାଙ୍ଗ;
	    }
	  ଯଦି (oacc_async)
	    c_mark_addressable (t);
	  type = ବୃକ୍ଷ_TYPE (t);
	  ଯଦି (ବୃକ୍ଷ_CODE (t) == MEM_REF)
	    type = ବୃକ୍ଷ_TYPE (type);
	  ଯଦି (ବୃକ୍ଷ_CODE (type) == ARRAY_TYPE)
	    {
	      ବୃକ୍ଷ oatype = type;
	      gcc_assert (ବୃକ୍ଷ_CODE (t) != MEM_REF);
	      ଯେତେବେଳେ (ବୃକ୍ଷ_CODE (type) == ARRAY_TYPE)
		type = ବୃକ୍ଷ_TYPE (type);
	      ଯଦି (integer_zerop (TYPE_SIZE_UNIT (type)))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD in %<reduction%> clause is a zero size array",
			    t);
		  remove = ସତ୍ୟ;
		  ଭାଙ୍ଗ;
		}
	      ବୃକ୍ଷ size = size_binop (EXACT_DIV_ପଦସମଷ୍ଟି, TYPE_SIZE_UNIT (oatype),
				      TYPE_SIZE_UNIT (type));
	      ଯଦି (integer_zerop (size))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD in %<reduction%> clause is a zero size array",
			    t);
		  remove = ସତ୍ୟ;
		  ଭାଙ୍ଗ;
		}
	      size = size_binop (MINUS_ପଦସମଷ୍ଟି, size, size_one_ଗଣ୍ଠି);
	      size = save_ପଦସମଷ୍ଟି (size);
	      ବୃକ୍ଷ index_type = build_index_type (size);
	      ବୃକ୍ଷ atype = c_build_array_type (TYPE_MAIN_VARIANT (type),
					       index_type);
	      atype = c_build_qualified_type (atype, TYPE_QUALS (type));
	      ବୃକ୍ଷ ptype = c_build_pointer_type (type);
	      ଯଦି (ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (t)) == ARRAY_TYPE)
		t = build_fold_addr_ପଦସମଷ୍ଟି (t);
	      t = build2 (MEM_REF, atype, t, build_int_cst (ptype, 0));
	      OMP_CLAUSE_DECL (c) = t;
	    }
	  ଯଦି (TYPE_ATOMIC (type))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<_Atomic%> %qE in %<reduction%> clause", t);
	      remove = ସତ୍ୟ;
	      ଭାଙ୍ଗ;
	    }
	  ଯଦି (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_REDUCTION
	      || OMP_CLAUSE_REDUCTION_TASK (c))
	    {
	      /* Disallow zero sized or potentially zero sized task
		 reductions.  */
	      ଯଦି (integer_zerop (TYPE_SIZE_UNIT (type)))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "zero sized type %qT in %qs clause", type,
			    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		  remove = ସତ୍ୟ;
		  ଭାଙ୍ଗ;
		}
	      ଅନ୍ୟଥା ଯଦି (ବୃକ୍ଷ_CODE (TYPE_SIZE_UNIT (type)) != INTEGER_CST)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "variable sized type %qT in %qs clause", type,
			    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		  remove = ସତ୍ୟ;
		  ଭାଙ୍ଗ;
		}
	    }
	  ଯଦି (OMP_CLAUSE_REDUCTION_PLACEHOLDER (c) == NULL_ବୃକ୍ଷ
	      && (FLOAT_TYPE_P (type)
		  || ବୃକ୍ଷ_CODE (type) == COMPLEX_TYPE))
	    {
	      ଗଣନା ବୃକ୍ଷ_code r_code = OMP_CLAUSE_REDUCTION_CODE (c);
	      ଅଚଳ ଅକ୍ଷର *r_name = ଖାଲି;

	      ବାଛ (r_code)
		{
		ସ୍ଥିତି PLUS_ପଦସମଷ୍ଟି:
		ସ୍ଥିତି MULT_ପଦସମଷ୍ଟି:
		ସ୍ଥିତି MINUS_ପଦସମଷ୍ଟି:
		ସ୍ଥିତି TRUTH_ANDIF_ପଦସମଷ୍ଟି:
		ସ୍ଥିତି TRUTH_ORIF_ପଦସମଷ୍ଟି:
		  ଭାଙ୍ଗ;
		ସ୍ଥିତି MIN_ପଦସମଷ୍ଟି:
		  ଯଦି (ବୃକ୍ଷ_CODE (type) == COMPLEX_TYPE)
		    r_name = "min";
		  ଭାଙ୍ଗ;
		ସ୍ଥିତି MAX_ପଦସମଷ୍ଟି:
		  ଯଦି (ବୃକ୍ଷ_CODE (type) == COMPLEX_TYPE)
		    r_name = "max";
		  ଭାଙ୍ଗ;
		ସ୍ଥିତି BIT_AND_ପଦସମଷ୍ଟି:
		  r_name = "&";
		  ଭାଙ୍ଗ;
		ସ୍ଥିତି BIT_XOR_ପଦସମଷ୍ଟି:
		  r_name = "^";
		  ଭାଙ୍ଗ;
		ସ୍ଥିତି BIT_IOR_ପଦସମଷ୍ଟି:
		  r_name = "|";
		  ଭାଙ୍ଗ;
		ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
		  gcc_unreachable ();
		}
	      ଯଦି (r_name)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qE has invalid type for %<reduction(%s)%>",
			    t, r_name);
		  remove = ସତ୍ୟ;
		  ଭାଙ୍ଗ;
		}
	    }
	  ଅନ୍ୟଥା ଯଦି (OMP_CLAUSE_REDUCTION_PLACEHOLDER (c) == error_mark_ଗଣ୍ଠି)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"user defined reduction not found for %qE", t);
	      remove = ସତ୍ୟ;
	      ଭାଙ୍ଗ;
	    }
	  ଅନ୍ୟଥା ଯଦି (OMP_CLAUSE_REDUCTION_PLACEHOLDER (c))
	    {
	      ବୃକ୍ଷ list = OMP_CLAUSE_REDUCTION_PLACEHOLDER (c);
	      type = TYPE_MAIN_VARIANT (type);
	      ବୃକ୍ଷ placeholder = build_decl (OMP_CLAUSE_LOCATION (c),
					     VAR_DECL, NULL_ବୃକ୍ଷ, type);
	      ବୃକ୍ଷ decl_placeholder = NULL_ବୃକ୍ଷ;
	      OMP_CLAUSE_REDUCTION_PLACEHOLDER (c) = placeholder;
	      DECL_ARTIFICIAL (placeholder) = 1;
	      DECL_IGNORED_P (placeholder) = 1;
	      ଯଦି (ବୃକ୍ଷ_CODE (t) == MEM_REF)
		{
		  decl_placeholder = build_decl (OMP_CLAUSE_LOCATION (c),
						 VAR_DECL, NULL_ବୃକ୍ଷ, type);
		  OMP_CLAUSE_REDUCTION_DECL_PLACEHOLDER (c) = decl_placeholder;
		  DECL_ARTIFICIAL (decl_placeholder) = 1;
		  DECL_IGNORED_P (decl_placeholder) = 1;
		}
	      ଯଦି (ବୃକ୍ଷ_ADDRESSABLE (ବୃକ୍ଷ_VEC_ELT (list, 0)))
		c_mark_addressable (placeholder);
	      ଯଦି (ବୃକ୍ଷ_ADDRESSABLE (ବୃକ୍ଷ_VEC_ELT (list, 1)))
		c_mark_addressable (decl_placeholder ? decl_placeholder
				    : OMP_CLAUSE_DECL (c));
	      OMP_CLAUSE_REDUCTION_MERGE (c)
		= c_clone_omp_udr (ବୃକ୍ଷ_VEC_ELT (list, 2),
				   ବୃକ୍ଷ_VEC_ELT (list, 0),
				   ବୃକ୍ଷ_VEC_ELT (list, 1),
				   decl_placeholder ? decl_placeholder
				   : OMP_CLAUSE_DECL (c), placeholder);
	      OMP_CLAUSE_REDUCTION_MERGE (c)
		= build3_loc (OMP_CLAUSE_LOCATION (c), BIND_ପଦସମଷ୍ଟି,
			      void_type_ଗଣ୍ଠି, NULL_ବୃକ୍ଷ,
			      OMP_CLAUSE_REDUCTION_MERGE (c), NULL_ବୃକ୍ଷ);
	      ବୃକ୍ଷ_SIDE_EFFECTS (OMP_CLAUSE_REDUCTION_MERGE (c)) = 1;
	      ଯଦି (ବୃକ୍ଷ_VEC_LENGTH (list) == 6)
		{
		  ଯଦି (ବୃକ୍ଷ_ADDRESSABLE (ବୃକ୍ଷ_VEC_ELT (list, 3)))
		    c_mark_addressable (decl_placeholder ? decl_placeholder
					: OMP_CLAUSE_DECL (c));
		  ଯଦି (ବୃକ୍ଷ_ADDRESSABLE (ବୃକ୍ଷ_VEC_ELT (list, 4)))
		    c_mark_addressable (placeholder);
		  ବୃକ୍ଷ init = ବୃକ୍ଷ_VEC_ELT (list, 5);
		  ଯଦି (init == error_mark_ଗଣ୍ଠି)
		    init = DECL_INITIAL (ବୃକ୍ଷ_VEC_ELT (list, 3));
		  OMP_CLAUSE_REDUCTION_INIT (c)
		    = c_clone_omp_udr (init, ବୃକ୍ଷ_VEC_ELT (list, 4),
				       ବୃକ୍ଷ_VEC_ELT (list, 3),
				       decl_placeholder ? decl_placeholder
				       : OMP_CLAUSE_DECL (c), placeholder);
		  ଯଦି (ବୃକ୍ଷ_VEC_ELT (list, 5) == error_mark_ଗଣ୍ଠି)
		    {
		      ବୃକ୍ଷ v = decl_placeholder ? decl_placeholder : t;
		      OMP_CLAUSE_REDUCTION_INIT (c)
			= build2 (INIT_ପଦସମଷ୍ଟି, ବୃକ୍ଷ_TYPE (v), v,
				  OMP_CLAUSE_REDUCTION_INIT (c));
		    }
		  ଯଦି (walk_ବୃକ୍ଷ (&OMP_CLAUSE_REDUCTION_INIT (c),
				 c_find_omp_placeholder_r,
				 placeholder, ଖାଲି))
		    OMP_CLAUSE_REDUCTION_OMP_ORIG_REF (c) = 1;
		}
	      ଅନ୍ୟଥା
		{
		  ବୃକ୍ଷ init;
		  ବୃକ୍ଷ v = decl_placeholder ? decl_placeholder : t;
		  ଯଦି (AGGREGATE_TYPE_P (ବୃକ୍ଷ_TYPE (v)))
		    init = build_constructor (ବୃକ୍ଷ_TYPE (v), ଖାଲି);
		  ଅନ୍ୟଥା
		    init = fold_convert (ବୃକ୍ଷ_TYPE (v), integer_zero_ଗଣ୍ଠି);
		  OMP_CLAUSE_REDUCTION_INIT (c)
		    = build2 (INIT_ପଦସମଷ୍ଟି, ବୃକ୍ଷ_TYPE (v), v, init);
		}
	      OMP_CLAUSE_REDUCTION_INIT (c)
		= build3_loc (OMP_CLAUSE_LOCATION (c), BIND_ପଦସମଷ୍ଟି,
			      void_type_ଗଣ୍ଠି, NULL_ବୃକ୍ଷ,
			       OMP_CLAUSE_REDUCTION_INIT (c), NULL_ବୃକ୍ଷ);
	      ବୃକ୍ଷ_SIDE_EFFECTS (OMP_CLAUSE_REDUCTION_INIT (c)) = 1;
	    }
	  ଯଦି (ବୃକ୍ଷ_CODE (t) == MEM_REF)
	    {
	      ଯଦି (TYPE_SIZE_UNIT (ବୃକ୍ଷ_TYPE (ବୃକ୍ଷ_TYPE (t))) == NULL_ବୃକ୍ଷ
		  || ବୃକ୍ଷ_CODE (TYPE_SIZE_UNIT (ବୃକ୍ଷ_TYPE (ବୃକ୍ଷ_TYPE (t))))
		     != INTEGER_CST)
		{
		  sorry ("variable length element type in array "
			 "%<reduction%> clause");
		  remove = ସତ୍ୟ;
		  ଭାଙ୍ଗ;
		}
	      t = ବୃକ୍ଷ_OPERAND (t, 0);
	      ଯଦି (ବୃକ୍ଷ_CODE (t) == POINTER_PLUS_ପଦସମଷ୍ଟି)
		t = ବୃକ୍ଷ_OPERAND (t, 0);
	      ଯଦି (ବୃକ୍ଷ_CODE (t) == ADDR_ପଦସମଷ୍ଟି)
		t = ବୃକ୍ଷ_OPERAND (t, 0);
	    }
	  ଯାଅ check_dup_generic_t;

	ସ୍ଥିତି OMP_CLAUSE_COPYPRIVATE:
	  copyprivate_seen = ସତ୍ୟ;
	  ଯଦି (nowait_clause)
	    {
	      error_at (OMP_CLAUSE_LOCATION (*nowait_clause),
			"%<nowait%> clause must not be used together "
			"with %<copyprivate%> clause");
	      *nowait_clause = OMP_CLAUSE_CHAIN (*nowait_clause);
	      nowait_clause = ଖାଲି;
	    }
	  ଯାଅ check_dup_generic;

	ସ୍ଥିତି OMP_CLAUSE_COPYIN:
	  t = OMP_CLAUSE_DECL (c);
	  ଯଦି (!VAR_P (t) || !DECL_THREAD_LOCAL_P (t))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE must be %<threadprivate%> for %<copyin%>", t);
	      remove = ସତ୍ୟ;
	      ଭାଙ୍ଗ;
	    }
	  ଯାଅ check_dup_generic;

	ସ୍ଥିତି OMP_CLAUSE_LINEAR:
	  ଯଦି (ort != C_ORT_OMP_DECLARE_SIMD)
	    need_implicitly_determined = ସତ୍ୟ;
	  t = OMP_CLAUSE_DECL (c);
	  ଯଦି (ort != C_ORT_OMP_DECLARE_SIMD
	      && OMP_CLAUSE_LINEAR_KIND (c) != OMP_CLAUSE_LINEAR_DEFAULT
	      && OMP_CLAUSE_LINEAR_OLD_LINEAR_MODIFIER (c))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"modifier should not be specified in %<linear%> "
			"clause on %<simd%> or %<for%> constructs when not "
			"using OpenMP 5.2 modifiers");
	      OMP_CLAUSE_LINEAR_KIND (c) = OMP_CLAUSE_LINEAR_DEFAULT;
	    }
	  ଯଦି (!INTEGRAL_TYPE_P (ବୃକ୍ଷ_TYPE (t))
	      && ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (t)) != POINTER_TYPE)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"linear clause applied to non-integral non-pointer "
			"variable with type %qT", ବୃକ୍ଷ_TYPE (t));
	      remove = ସତ୍ୟ;
	      ଭାଙ୍ଗ;
	    }
	  ଯଦି (TYPE_ATOMIC (ବୃକ୍ଷ_TYPE (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<_Atomic%> %qD in %<linear%> clause", t);
	      remove = ସତ୍ୟ;
	      ଭାଙ୍ଗ;
	    }
	  ଯଦି (ort == C_ORT_OMP_DECLARE_SIMD)
	    {
	      ବୃକ୍ଷ s = OMP_CLAUSE_LINEAR_STEP (c);
	      ଯଦି (ବୃକ୍ଷ_CODE (s) == PARM_DECL)
		{
		  OMP_CLAUSE_LINEAR_VARIABLE_STRIDE (c) = 1;
		  /* map_head bitmap is used as uniform_head if
		     declare_simd.  */
		  ଯଦି (!bitmap_bit_p (&map_head, DECL_UID (s)))
		    linear_variable_step_check = ସତ୍ୟ;
		  ଯାଅ check_dup_generic;
		}
	      ଯଦି (ବୃକ୍ଷ_CODE (s) != INTEGER_CST)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%<linear%> clause step %qE is neither constant "
			    "nor a parameter", s);
		  remove = ସତ୍ୟ;
		  ଭାଙ୍ଗ;
		}
	    }
	  ଯଦି (ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (OMP_CLAUSE_DECL (c))) == POINTER_TYPE)
	    {
	      ବୃକ୍ଷ s = OMP_CLAUSE_LINEAR_STEP (c);
	      s = pointer_int_sum (OMP_CLAUSE_LOCATION (c), PLUS_ପଦସମଷ୍ଟି,
				   OMP_CLAUSE_DECL (c), s);
	      s = fold_build2_loc (OMP_CLAUSE_LOCATION (c), MINUS_ପଦସମଷ୍ଟି,
				   sizetype, fold_convert (sizetype, s),
				   fold_convert
				     (sizetype, OMP_CLAUSE_DECL (c)));
	      ଯଦି (s == error_mark_ଗଣ୍ଠି)
		s = size_one_ଗଣ୍ଠି;
	      OMP_CLAUSE_LINEAR_STEP (c) = s;
	    }
	  ଅନ୍ୟଥା
	    OMP_CLAUSE_LINEAR_STEP (c)
	      = fold_convert (ବୃକ୍ଷ_TYPE (t), OMP_CLAUSE_LINEAR_STEP (c));
	  ଯାଅ check_dup_generic;

	check_dup_generic:
	  t = OMP_CLAUSE_DECL (c);
	check_dup_generic_t:
	  ଯଦି (!VAR_P (t) && ବୃକ୍ଷ_CODE (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in clause %qs", t,
			omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	      remove = ସତ୍ୟ;
	    }
	  ଅନ୍ୟଥା ଯଦି ((openacc && OMP_CLAUSE_CODE (c) == OMP_CLAUSE_REDUCTION)
		   || (ort == C_ORT_OMP
		       && (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_USE_DEVICE_PTR
			   || (OMP_CLAUSE_CODE (c)
			       == OMP_CLAUSE_USE_DEVICE_ADDR)))
		   || (ort == C_ORT_OMP_TARGET
		       && OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IN_REDUCTION))
	    {
	      ଯଦି (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IN_REDUCTION
		  && (bitmap_bit_p (&generic_head, DECL_UID (t))
		      || bitmap_bit_p (&firstprivate_head, DECL_UID (t))))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD appears more than once in data-sharing "
			    "clauses", t);
		  remove = ସତ୍ୟ;
		  ଭାଙ୍ଗ;
		}
	      ଯଦି (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IN_REDUCTION)
		target_in_reduction_seen = ସତ୍ୟ;
	      ଯଦି (bitmap_bit_p (&oacc_reduction_head, DECL_UID (t)))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    openacc
			    ? "%qD appears more than once in reduction clauses"
			    : "%qD appears more than once in data clauses",
			    t);
		  remove = ସତ୍ୟ;
		}
	      ଅନ୍ୟଥା
		bitmap_set_bit (&oacc_reduction_head, DECL_UID (t));
	    }
	  ଅନ୍ୟଥା ଯଦି (bitmap_bit_p (&generic_head, DECL_UID (t))
		   || bitmap_bit_p (&firstprivate_head, DECL_UID (t))
		   || bitmap_bit_p (&lastprivate_head, DECL_UID (t))
		   || bitmap_bit_p (&map_firstprivate_head, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE appears more than once in data clauses", t);
	      remove = ସତ୍ୟ;
	    }
	  ଅନ୍ୟଥା ଯଦି ((OMP_CLAUSE_CODE (c) == OMP_CLAUSE_PRIVATE
		    || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_HAS_DEVICE_ADDR
		    || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IS_DEVICE_PTR)
		   && bitmap_bit_p (&map_head, DECL_UID (t)))
	    {
	      ଯଦି (openacc)
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD appears more than once in data clauses", t);
	      ଅନ୍ୟଥା
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD appears both in data and map clauses", t);
	      remove = ସତ୍ୟ;
	    }
	  ଅନ୍ୟଥା
	    bitmap_set_bit (&generic_head, DECL_UID (t));
	  ଭାଙ୍ଗ;

	ସ୍ଥିତି OMP_CLAUSE_FIRSTPRIVATE:
	  ଯଦି (OMP_CLAUSE_FIRSTPRIVATE_IMPLICIT (c) && !implicit_moved)
	    {
	    move_implicit:
	      implicit_moved = ସତ୍ୟ;
	      /* Move firstprivate and map clauses with
		 OMP_CLAUSE_{FIRSTPRIVATE,MAP}_IMPLICIT set to the end of
		 clauses chain.  */
	      ବୃକ୍ଷ cl1 = NULL_ବୃକ୍ଷ, cl2 = NULL_ବୃକ୍ଷ;
	      ବୃକ୍ଷ *pc1 = pc, *pc2 = &cl1, *pc3 = &cl2;
	      ଯେତେବେଳେ (*pc1)
		ଯଦି (OMP_CLAUSE_CODE (*pc1) == OMP_CLAUSE_FIRSTPRIVATE
		    && OMP_CLAUSE_FIRSTPRIVATE_IMPLICIT (*pc1))
		  {
		    *pc3 = *pc1;
		    pc3 = &OMP_CLAUSE_CHAIN (*pc3);
		    *pc1 = OMP_CLAUSE_CHAIN (*pc1);
		  }
		ଅନ୍ୟଥା ଯଦି (OMP_CLAUSE_CODE (*pc1) == OMP_CLAUSE_MAP
			 && OMP_CLAUSE_MAP_IMPLICIT (*pc1))
		  {
		    *pc2 = *pc1;
		    pc2 = &OMP_CLAUSE_CHAIN (*pc2);
		    *pc1 = OMP_CLAUSE_CHAIN (*pc1);
		  }
		ଅନ୍ୟଥା
		  pc1 = &OMP_CLAUSE_CHAIN (*pc1);
	      *pc3 = ଖାଲି;
	      *pc2 = cl2;
	      *pc1 = cl1;
	      ଜାରି;
	    }
	  t = OMP_CLAUSE_DECL (c);
	  need_complete = ସତ୍ୟ;
	  need_implicitly_determined = ସତ୍ୟ;
	  ଯଦି (!VAR_P (t) && ବୃକ୍ଷ_CODE (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in clause %<firstprivate%>", t);
	      remove = ସତ୍ୟ;
	    }
	  ଅନ୍ୟଥା ଯଦି (OMP_CLAUSE_FIRSTPRIVATE_IMPLICIT (c)
		   && !OMP_CLAUSE_FIRSTPRIVATE_IMPLICIT_TARGET (c)
		   && bitmap_bit_p (&map_firstprivate_head, DECL_UID (t)))
	    remove = ସତ୍ୟ;
	  ଅନ୍ୟଥା ଯଦି (bitmap_bit_p (&generic_head, DECL_UID (t))
		   || bitmap_bit_p (&firstprivate_head, DECL_UID (t))
		   || bitmap_bit_p (&map_firstprivate_head, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE appears more than once in data clauses", t);
	      remove = ସତ୍ୟ;
	    }
	  ଅନ୍ୟଥା ଯଦି (bitmap_bit_p (&map_head, DECL_UID (t))
		   || bitmap_bit_p (&map_field_head, DECL_UID (t)))
	    {
	      ଯଦି (openacc)
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD appears more than once in data clauses", t);
	      ଅନ୍ୟଥା ଯଦି (OMP_CLAUSE_FIRSTPRIVATE_IMPLICIT (c)
		       && !OMP_CLAUSE_FIRSTPRIVATE_IMPLICIT_TARGET (c))
		/* Silently drop the clause.  */;
	      ଅନ୍ୟଥା
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD appears both in data and map clauses", t);
	      remove = ସତ୍ୟ;
	    }
	  ଅନ୍ୟଥା
	    bitmap_set_bit (&firstprivate_head, DECL_UID (t));
	  ଭାଙ୍ଗ;

	ସ୍ଥିତି OMP_CLAUSE_LASTPRIVATE:
	  t = OMP_CLAUSE_DECL (c);
	  need_complete = ସତ୍ୟ;
	  need_implicitly_determined = ସତ୍ୟ;
	  ଯଦି (!VAR_P (t) && ବୃକ୍ଷ_CODE (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in clause %<lastprivate%>", t);
	      remove = ସତ୍ୟ;
	    }
	  ଅନ୍ୟଥା ଯଦି (bitmap_bit_p (&generic_head, DECL_UID (t))
		   || bitmap_bit_p (&lastprivate_head, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
		     "%qE appears more than once in data clauses", t);
	      remove = ସତ୍ୟ;
	    }
	  ଅନ୍ୟଥା
	    bitmap_set_bit (&lastprivate_head, DECL_UID (t));
	  ଭାଙ୍ଗ;

	ସ୍ଥିତି OMP_CLAUSE_ALIGNED:
	  t = OMP_CLAUSE_DECL (c);
	  ଯଦି (!VAR_P (t) && ବୃକ୍ଷ_CODE (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in %<aligned%> clause", t);
	      remove = ସତ୍ୟ;
	    }
	  ଅନ୍ୟଥା ଯଦି (!POINTER_TYPE_P (ବୃକ୍ଷ_TYPE (t))
		   && ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (t)) != ARRAY_TYPE)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE in %<aligned%> clause is neither a pointer nor "
			"an array", t);
	      remove = ସତ୍ୟ;
	    }
	  ଅନ୍ୟଥା ଯଦି (TYPE_ATOMIC (ବୃକ୍ଷ_TYPE (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<_Atomic%> %qD in %<aligned%> clause", t);
	      remove = ସତ୍ୟ;
	      ଭାଙ୍ଗ;
	    }
	  ଅନ୍ୟଥା ଯଦି (bitmap_bit_p (&aligned_head, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE appears more than once in %<aligned%> clauses",
			t);
	      remove = ସତ୍ୟ;
	    }
	  ଅନ୍ୟଥା
	    bitmap_set_bit (&aligned_head, DECL_UID (t));
	  ଭାଙ୍ଗ;

	ସ୍ଥିତି OMP_CLAUSE_NONTEMPORAL:
	  t = OMP_CLAUSE_DECL (c);
	  ଯଦି (!VAR_P (t) && ବୃକ୍ଷ_CODE (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in %<nontemporal%> clause", t);
	      remove = ସତ୍ୟ;
	    }
	  ଅନ୍ୟଥା ଯଦି (bitmap_bit_p (&oacc_reduction_head, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE appears more than once in %<nontemporal%> "
			"clauses", t);
	      remove = ସତ୍ୟ;
	    }
	  ଅନ୍ୟଥା
	    bitmap_set_bit (&oacc_reduction_head, DECL_UID (t));
	  ଭାଙ୍ଗ;

	ସ୍ଥିତି OMP_CLAUSE_ALLOCATE:
	  t = OMP_CLAUSE_DECL (c);
	  ଯଦି (!VAR_P (t) && ବୃକ୍ଷ_CODE (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in %<allocate%> clause", t);
	      remove = ସତ୍ୟ;
	    }
	  ଅନ୍ୟଥା ଯଦି (bitmap_bit_p (&aligned_head, DECL_UID (t)))
	    {
	      warning_at (OMP_CLAUSE_LOCATION (c), OPT_Wopenmp,
			  "%qE appears more than once in %<allocate%> clauses",
			  t);
	      remove = ସତ୍ୟ;
	    }
	  ଅନ୍ୟଥା
	    {
	      bitmap_set_bit (&aligned_head, DECL_UID (t));
	      ଯଦି (!OMP_CLAUSE_ALLOCATE_COMBINED (c))
		allocate_seen = ସତ୍ୟ;
	    }
	  ଭାଙ୍ଗ;

	ସ୍ଥିତି OMP_CLAUSE_DOACROSS:
	  t = OMP_CLAUSE_DECL (c);
	  ଯଦି (t == NULL_ବୃକ୍ଷ)
	    ଭାଙ୍ଗ;
	  ଯଦି (OMP_CLAUSE_DOACROSS_KIND (c) == OMP_CLAUSE_DOACROSS_SINK)
	    {
	      gcc_assert (ବୃକ୍ଷ_CODE (t) == ବୃକ୍ଷ_LIST);
	      ପାଇଁ (; t; t = ବୃକ୍ଷ_CHAIN (t))
		{
		  ବୃକ୍ଷ decl = ବୃକ୍ଷ_ମୂଲ୍ୟ (t);
		  ଯଦି (ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (decl)) == POINTER_TYPE)
		    {
		      ବୃକ୍ଷ offset = ବୃକ୍ଷ_PURPOSE (t);
		      ତାର୍କିକ neg = wi::neg_p (wi::to_wide (offset));
		      offset = fold_unary (ABS_ପଦସମଷ୍ଟି, ବୃକ୍ଷ_TYPE (offset), offset);
		      ବୃକ୍ଷ t2 = pointer_int_sum (OMP_CLAUSE_LOCATION (c),
						 neg ? MINUS_ପଦସମଷ୍ଟି : PLUS_ପଦସମଷ୍ଟି,
						 decl, offset);
		      t2 = fold_build2_loc (OMP_CLAUSE_LOCATION (c), MINUS_ପଦସମଷ୍ଟି,
					    sizetype,
					    fold_convert (sizetype, t2),
					    fold_convert (sizetype, decl));
		      ଯଦି (t2 == error_mark_ଗଣ୍ଠି)
			{
			  remove = ସତ୍ୟ;
			  ଭାଙ୍ଗ;
			}
		      ବୃକ୍ଷ_PURPOSE (t) = t2;
		    }
		}
	      ଭାଙ୍ଗ;
	    }
	  gcc_unreachable ();

	ସ୍ଥିତି OMP_CLAUSE_USES_ALLOCATORS:
	  t = OMP_CLAUSE_USES_ALLOCATORS_ALLOCATOR (c);
	  ଯଦି (t == error_mark_ଗଣ୍ଠି)
	    {
	      remove = ସତ୍ୟ;
	      ଭାଙ୍ଗ;
	    }
	  ଯଦି ((VAR_P (t) || ବୃକ୍ଷ_CODE (t) == PARM_DECL)
	      && (bitmap_bit_p (&generic_head, DECL_UID (t))
		  || bitmap_bit_p (&map_head, DECL_UID (t))
		  || bitmap_bit_p (&firstprivate_head, DECL_UID (t))
		  || bitmap_bit_p (&lastprivate_head, DECL_UID (t))))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE appears more than once in data clauses", t);
	      remove = ସତ୍ୟ;
	      ଭାଙ୍ଗ;
	    }
	  ଅନ୍ୟଥା
	    bitmap_set_bit (&generic_head, DECL_UID (t));
	  ଯଦି (ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (t)) != ENUMERAL_TYPE
	      || strcmp (IDENTIFIER_POINTER (TYPE_IDENTIFIER (ବୃକ୍ଷ_TYPE (t))),
			 "omp_allocator_handle_t") != 0)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"allocator %qE must be of %<omp_allocator_handle_t%> "
			"type", t);
	      remove = ସତ୍ୟ;
	      ଭାଙ୍ଗ;
	    }
	  ବୃକ୍ଷ init;
	  ଯଦି (!DECL_P (t)
	      || (ବୃକ୍ଷ_CODE (t) == CONST_DECL
		  && ((init = DECL_INITIAL(t)) == nullptr
		      || ବୃକ୍ଷ_CODE (init) != INTEGER_CST
		      || ((wi::to_widest (init) < 0
			   || wi::to_widest (init) > GOMP_OMP_PREDEF_ALLOC_MAX)
			  && (wi::to_widest (init) < GOMP_OMPX_PREDEF_ALLOC_MIN
			      || (wi::to_widest (init)
				  > GOMP_OMPX_PREDEF_ALLOC_MAX))))))
	    {
	      remove = ସତ୍ୟ;
	      error_at (OMP_CLAUSE_LOCATION (c),
			"allocator %qE must be either a variable or a "
			"predefined allocator", t);
	      ଭାଙ୍ଗ;
	    }
	  ଅନ୍ୟଥା ଯଦି (ବୃକ୍ଷ_CODE (t) == CONST_DECL)
	    {
	      /* omp_null_allocator is ignored and for predefined allocators,
		 no special handling is required; thus, mark them removed. */
	      remove = ସତ୍ୟ;

	      ଯଦି (OMP_CLAUSE_USES_ALLOCATORS_MEMSPACE (c)
		  || OMP_CLAUSE_USES_ALLOCATORS_TRAITS (c))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "modifiers cannot be used with predefined "
			    "allocator %qE", t);
		  ଭାଙ୍ଗ;
		}
	    }
	  t = OMP_CLAUSE_USES_ALLOCATORS_MEMSPACE (c);
	  ଯଦି (t == error_mark_ଗଣ୍ଠି)
	    {
	      remove = ସତ୍ୟ;
	      ଭାଙ୍ଗ;
	    }
	  ଯଦି (t != NULL_ବୃକ୍ଷ
	      && ((ବୃକ୍ଷ_CODE (t) != CONST_DECL && ବୃକ୍ଷ_CODE (t) != INTEGER_CST)
		  || ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (t)) != ENUMERAL_TYPE
		  || strcmp (IDENTIFIER_POINTER (TYPE_IDENTIFIER (ବୃକ୍ଷ_TYPE (t))),
			     "omp_memspace_handle_t") != 0))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c), "memspace modifier %qE must be"
			" constant enum of %<omp_memspace_handle_t%> type", t);
	      remove = ସତ୍ୟ;
	      ଭାଙ୍ଗ;
	    }
	  t = OMP_CLAUSE_USES_ALLOCATORS_TRAITS (c);
	  ଯଦି (t == error_mark_ଗଣ୍ଠି)
	    {
	      remove = ସତ୍ୟ;
	      ଭାଙ୍ଗ;
	    }
	  ଯଦି (t != NULL_ବୃକ୍ଷ
	      && t != error_mark_ଗଣ୍ଠି
	      && (DECL_EXTERNAL (t)
		  || ବୃକ୍ଷ_CODE (t) == PARM_DECL))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c), "traits array %qE must be "
			"defined in same scope as the construct on which the "
			"clause appears", t);
	      remove = ସତ୍ୟ;
	    }
	  ଯଦି (t != NULL_ବୃକ୍ଷ)
	    {
	      ତାର୍କିକ type_err = ମିଥ୍ୟା;

	      ଯଦି (ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (t)) != ARRAY_TYPE
		  || DECL_SIZE (t) == NULL_ବୃକ୍ଷ
		  || !COMPLETE_TYPE_P (ବୃକ୍ଷ_TYPE (t)))
		type_err = ସତ୍ୟ;
	      ଅନ୍ୟଥା
		{
		  ବୃକ୍ଷ elem_t = ବୃକ୍ଷ_TYPE (ବୃକ୍ଷ_TYPE (t));
		  ଯଦି (ବୃକ୍ଷ_CODE (elem_t) != RECORD_TYPE
		      || strcmp (IDENTIFIER_POINTER (TYPE_IDENTIFIER (elem_t)),
				 "omp_alloctrait_t") != 0
		      || !TYPE_READONLY (elem_t))
		    type_err = ସତ୍ୟ;
		}
	      ଯଦି (type_err)
		{
		  ଯଦି (t != error_mark_ଗଣ୍ଠି)
		    error_at (OMP_CLAUSE_LOCATION (c), "traits array %qE must "
			      "be of %<const omp_alloctrait_t []%> type", t);
		  ଅନ୍ୟଥା
		    error_at (OMP_CLAUSE_LOCATION (c), "traits array must "
			      "be of %<const omp_alloctrait_t []%> type");
		  remove = ସତ୍ୟ;
		}
	      ଅନ୍ୟଥା
		{
		  ବୃକ୍ଷ cst_val = decl_constant_ମୂଲ୍ୟ_1 (t, ସତ୍ୟ);
		  ଯଦି (cst_val == t)
		    {
		      error_at (OMP_CLAUSE_LOCATION (c), "traits array must be "
				"initialized with constants");

		      remove = ସତ୍ୟ;
		    }
		}
	    }
	  ଯଦି (remove)
	    ଭାଙ୍ଗ;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  ଜାରି;
	ସ୍ଥିତି OMP_CLAUSE_DEPEND:
	  depend_clause = c;
	  /* FALLTHRU */
	ସ୍ଥିତି OMP_CLAUSE_AFFINITY:
	  t = OMP_CLAUSE_DECL (c);
	  ଯଦି (OMP_ITERATOR_DECL_P (t))
	    {
	      ଯଦି (ବୃକ୍ଷ_PURPOSE (t) != last_iterators)
		last_iterators_remove
		  = c_omp_finish_iterators (ବୃକ୍ଷ_PURPOSE (t));
	      last_iterators = ବୃକ୍ଷ_PURPOSE (t);
	      t = ବୃକ୍ଷ_ମୂଲ୍ୟ (t);
	      ଯଦି (last_iterators_remove)
		t = error_mark_ଗଣ୍ଠି;
	    }
	  ଅନ୍ୟଥା
	    last_iterators = NULL_ବୃକ୍ଷ;
	  ଯଦି (ବୃକ୍ଷ_CODE (t) == OMP_ARRAY_SECTION)
	    {
	      ଯଦି (handle_omp_array_sections (c, ort))
		remove = ସତ୍ୟ;
	      ଅନ୍ୟଥା ଯଦି (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND
		       && OMP_CLAUSE_DEPEND_KIND (c) == OMP_CLAUSE_DEPEND_DEPOBJ)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%<depend%> clause with %<depobj%> dependence "
			    "type on array section");
		  remove = ସତ୍ୟ;
		}
	      ଭାଙ୍ଗ;
	    }
	  ଯଦି (t == error_mark_ଗଣ୍ଠି)
	    remove = ସତ୍ୟ;
	  ଅନ୍ୟଥା ଯଦି (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND
		   && t == ridpointers[RID_OMP_ALL_MEMORY])
	    {
	      ଯଦି (OMP_CLAUSE_DEPEND_KIND (c) != OMP_CLAUSE_DEPEND_OUT
		  && OMP_CLAUSE_DEPEND_KIND (c) != OMP_CLAUSE_DEPEND_INOUT)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%<omp_all_memory%> used with %<depend%> kind "
			    "other than %<out%> or %<inout%>");
		  remove = ସତ୍ୟ;
		}
	    }
	  ଅନ୍ୟଥା ଯଦି (!lvalue_p (t))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not lvalue expression nor array section in "
			"%qs clause", t,
			omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	      remove = ସତ୍ୟ;
	    }
	  ଅନ୍ୟଥା ଯଦି (ବୃକ୍ଷ_CODE (t) == COMPONENT_REF
		   && DECL_C_BIT_FIELD (ବୃକ୍ଷ_OPERAND (t, 1)))
	    {
	      gcc_assert (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND
			  || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_AFFINITY);
	      error_at (OMP_CLAUSE_LOCATION (c),
			"bit-field %qE in %qs clause", t,
			omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	      remove = ସତ୍ୟ;
	    }
	  ଅନ୍ୟଥା ଯଦି (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND
		   && OMP_CLAUSE_DEPEND_KIND (c) == OMP_CLAUSE_DEPEND_DEPOBJ)
	    {
	      ଯଦି (!c_omp_depend_t_p (ବୃକ୍ଷ_TYPE (t)))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qE does not have %<omp_depend_t%> type in "
			    "%<depend%> clause with %<depobj%> dependence "
			    "type", t);
		  remove = ସତ୍ୟ;
		}
	    }
	  ଅନ୍ୟଥା ଯଦି (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND
		   && c_omp_depend_t_p (ବୃକ୍ଷ_TYPE (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE should not have %<omp_depend_t%> type in "
			"%<depend%> clause with dependence type other than "
			"%<depobj%>", t);
	      remove = ସତ୍ୟ;
	    }
	  ଯଦି (!remove)
	    {
	      ଯଦି (t == ridpointers[RID_OMP_ALL_MEMORY])
		t = null_pointer_ଗଣ୍ଠି;
	      ଅନ୍ୟଥା
		{
		  ବୃକ୍ଷ addr = build_unary_op (OMP_CLAUSE_LOCATION (c),
					      ADDR_ପଦସମଷ୍ଟି, t, ମିଥ୍ୟା);
		  ଯଦି (addr == error_mark_ଗଣ୍ଠି)
		    {
		      remove = ସତ୍ୟ;
		      ଭାଙ୍ଗ;
		    }
		  t = build_indirect_ref (OMP_CLAUSE_LOCATION (c), addr,
					  RO_UNARY_STAR);
		  ଯଦି (t == error_mark_ଗଣ୍ଠି)
		    {
		      remove = ସତ୍ୟ;
		      ଭାଙ୍ଗ;
		    }
		}
	      ଯଦି (OMP_ITERATOR_DECL_P (OMP_CLAUSE_DECL (c)))
		ବୃକ୍ଷ_ମୂଲ୍ୟ (OMP_CLAUSE_DECL (c)) = t;
	      ଅନ୍ୟଥା
		OMP_CLAUSE_DECL (c) = t;
	    }
	  ଭାଙ୍ଗ;

	ସ୍ଥିତି OMP_CLAUSE_MAP:
	  ଯଦି (OMP_CLAUSE_MAP_IMPLICIT (c) && !implicit_moved)
	    ଯାଅ move_implicit;
	  ଯଦି (OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_ଠେଲ_MAPPER_NAME
	      || OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_କାଢ଼_MAPPER_NAME)
	    {
	      remove = ସତ୍ୟ;
	      ଭାଙ୍ଗ;
	    }
	  /* FALLTHRU */
	ସ୍ଥିତି OMP_CLAUSE_TO:
	ସ୍ଥିତି OMP_CLAUSE_FROM:
	  ଯଦି (OMP_CLAUSE_ITERATORS (c)
	      && c_omp_finish_iterators (OMP_CLAUSE_ITERATORS (c)))
	    {
	      t = error_mark_ଗଣ୍ଠି;
	      ଭାଙ୍ଗ;
	    }
	  /* FALLTHRU */
	ସ୍ଥିତି OMP_CLAUSE__CACHE_:
	  {
	    using ନାମାକାଶ omp_addr_tokenizer;
	    auto_vec<omp_addr_token *, 10> addr_tokens;

	    t = OMP_CLAUSE_DECL (c);
	    ଯଦି (ବୃକ୍ଷ_CODE (t) == OMP_ARRAY_SECTION)
	      {
		grp_start_p = pc;
		grp_sentinel = OMP_CLAUSE_CHAIN (c);

		ଯଦି (handle_omp_array_sections (c, ort))
		  remove = ସତ୍ୟ;
		ଅନ୍ୟଥା
		  {
		    t = OMP_CLAUSE_DECL (c);
		    ଯଦି (!omp_mappable_type (ବୃକ୍ଷ_TYPE (t)))
		      {
			error_at (OMP_CLAUSE_LOCATION (c),
				  "array section does not have mappable type "
				  "in %qs clause",
				  omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
			remove = ସତ୍ୟ;
		      }
		    ଅନ୍ୟଥା ଯଦି (TYPE_ATOMIC (ବୃକ୍ଷ_TYPE (t)))
		      {
			error_at (OMP_CLAUSE_LOCATION (c),
				  "%<_Atomic%> %qE in %qs clause", t,
				  omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
			remove = ସତ୍ୟ;
		      }
		    ଯେତେବେଳେ (ବୃକ୍ଷ_CODE (t) == ARRAY_REF)
		      t = ବୃକ୍ଷ_OPERAND (t, 0);

		    c_omp_address_inspector ai (OMP_CLAUSE_LOCATION (c), t);

		    ଯଦି (!omp_parse_ପଦସମଷ୍ଟି (addr_tokens, t))
		      {
			sorry_at (OMP_CLAUSE_LOCATION (c),
				  "unsupported map expression %qE",
				  OMP_CLAUSE_DECL (c));
			remove = ସତ୍ୟ;
			ଭାଙ୍ଗ;
		      }

		    /* This check is to determine if this will be the only map
		       node created for this clause.  Otherwise, we'll check
		       the following FIRSTPRIVATE_POINTER or ATTACH_DETACH
		       node on the next iteration(s) of the loop.   */
		    ଯଦି (addr_tokens.length () >= 4
			&& addr_tokens[0]->type == STRUCTURE_BASE
			&& addr_tokens[0]->u.structure_base_kind == BASE_DECL
			&& addr_tokens[1]->type == ACCESS_METHOD
			&& addr_tokens[2]->type == COMPONENT_SELECTOR
			&& addr_tokens[3]->type == ACCESS_METHOD
			&& (addr_tokens[3]->u.access_kind == ACCESS_DIRECT
			    || (addr_tokens[3]->u.access_kind
				== ACCESS_INDEXED_ARRAY)))
		      {
			ବୃକ୍ଷ rt = addr_tokens[1]->ପଦସମଷ୍ଟି;

			gcc_assert (DECL_P (rt));

			ଯଦି (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP
			    && OMP_CLAUSE_MAP_IMPLICIT (c)
			    && (bitmap_bit_p (&map_head, DECL_UID (rt))
				|| bitmap_bit_p (&map_field_head, DECL_UID (rt))
				|| bitmap_bit_p (&map_firstprivate_head,
						 DECL_UID (rt))))
			  {
			    remove = ସତ୍ୟ;
			    ଭାଙ୍ଗ;
			  }
			ଯଦି (bitmap_bit_p (&map_field_head, DECL_UID (rt)))
			  ଭାଙ୍ଗ;
			ଯଦି (bitmap_bit_p (&map_head, DECL_UID (rt)))
			  {
			    ଯଦି (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_MAP)
			      error_at (OMP_CLAUSE_LOCATION (c),
					"%qD appears more than once in motion "
					"clauses", rt);
			    ଅନ୍ୟଥା ଯଦି (openacc)
			      error_at (OMP_CLAUSE_LOCATION (c),
					"%qD appears more than once in data "
					"clauses", rt);
			    ଅନ୍ୟଥା
			      error_at (OMP_CLAUSE_LOCATION (c),
					"%qD appears more than once in map "
					"clauses", rt);
			    remove = ସତ୍ୟ;
			  }
			ଅନ୍ୟଥା
			  {
			    bitmap_set_bit (&map_head, DECL_UID (rt));
			    bitmap_set_bit (&map_field_head, DECL_UID (rt));
			  }
		      }
		  }
		ଯଦି (c_oacc_check_attachments (c))
		  remove = ସତ୍ୟ;
		ଯଦି (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP
		    && (OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_ATTACH
			|| OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_DETACH)
		    && !OMP_CLAUSE_SIZE (c))
		  /* In this case, we have a single array element which is a
		     pointer, and we already set OMP_CLAUSE_SIZE in
		     handle_omp_array_sections above.  For attach/detach
		     clauses, reset the OMP_CLAUSE_SIZE (representing a bias)
		     to zero here.  */
		  OMP_CLAUSE_SIZE (c) = size_zero_ଗଣ୍ଠି;
		ଭାଙ୍ଗ;
	      }
	    ଅନ୍ୟଥା ଯଦି (!omp_parse_ପଦସମଷ୍ଟି (addr_tokens, t))
	      {
		sorry_at (OMP_CLAUSE_LOCATION (c),
			  "unsupported map expression %qE",
			  OMP_CLAUSE_DECL (c));
		remove = ସତ୍ୟ;
		ଭାଙ୍ଗ;
	      }
	    ଯଦି (t == error_mark_ଗଣ୍ଠି)
	      {
		remove = ସତ୍ୟ;
		ଭାଙ୍ଗ;
	      }

	    ବୃକ୍ଷ attr;
	    ଯଦି (DECL_P (t)
		&& OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP
		&& (attr = lookup_attribute ("omp declare target",
					     DECL_ATTRIBUTES (t)))
		&& ମୂଲ୍ୟ_member (get_identifier ("local"),
				 ବୃକ୍ଷ_ମୂଲ୍ୟ (attr)))
	      {
		error_at (OMP_CLAUSE_LOCATION (c),
			  "device-local variable %qD cannot appear "
			  "in map clause", t);
		remove = ସତ୍ୟ;
		ଭାଙ୍ଗ;
	      }

	    /* OpenACC attach / detach clauses must be pointers.  */
	    ଯଦି (c_oacc_check_attachments (c))
	      {
		remove = ସତ୍ୟ;
		ଭାଙ୍ଗ;
	      }
	    ଯଦି (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP
		&& (OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_ATTACH
		    || OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_DETACH)
		&& !OMP_CLAUSE_SIZE (c))
	      /* For attach/detach clauses, set OMP_CLAUSE_SIZE (representing a
		 bias) to zero here, so it is not set erroneously to the pointer
		 size later on in gimplify.cc.  */
	      OMP_CLAUSE_SIZE (c) = size_zero_ଗଣ୍ଠି;

	    c_omp_address_inspector ai (OMP_CLAUSE_LOCATION (c), t);

	    ଯଦି (!ai.check_clause (c))
	      {
		remove = ସତ୍ୟ;
		ଭାଙ୍ଗ;
	      }

	    ଯଦି (!ai.map_supported_p ())
	      {
		sorry_at (OMP_CLAUSE_LOCATION (c),
			  "unsupported map expression %qE",
			  OMP_CLAUSE_DECL (c));
		remove = ସତ୍ୟ;
		ଭାଙ୍ଗ;
	      }

	    gcc_assert ((addr_tokens[0]->type == ARRAY_BASE
			 || addr_tokens[0]->type == STRUCTURE_BASE)
			&& addr_tokens[1]->type == ACCESS_METHOD);

	    t = addr_tokens[1]->ପଦସମଷ୍ଟି;

	    ଯଦି (addr_tokens[0]->u.structure_base_kind != BASE_DECL)
	      ଯାଅ skip_decl_checks;

	    /* For OpenMP, we can access a struct "t" and "t.d" on the same
	       mapping.  OpenACC allows multiple fields of the same structure
	       to be written.  */
	    ଯଦି (addr_tokens[0]->type == STRUCTURE_BASE
		&& (bitmap_bit_p (&map_field_head, DECL_UID (t))
		    || (!openacc && bitmap_bit_p (&map_head, DECL_UID (t)))))
	      ଯାଅ skip_decl_checks;

	    ଯଦି (!VAR_P (t) && ବୃକ୍ଷ_CODE (t) != PARM_DECL)
	      {
		ଯଦି (ort != C_ORT_ACC && ପଦସମଷ୍ଟି_P (t))
		  ଭାଙ୍ଗ;

		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qE is not a variable in %qs clause", t,
			  omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		remove = ସତ୍ୟ;
	      }
	    ଅନ୍ୟଥା ଯଦି (VAR_P (t) && DECL_THREAD_LOCAL_P (t))
	      {
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD is threadprivate variable in %qs clause", t,
			  omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		remove = ସତ୍ୟ;
	      }
	    ଅନ୍ୟଥା ଯଦି ((OMP_CLAUSE_CODE (c) != OMP_CLAUSE_MAP
		      || (OMP_CLAUSE_MAP_KIND (c)
			  != GOMP_MAP_FIRSTPRIVATE_POINTER))
		     && !c_mark_addressable (t))
	      remove = ସତ୍ୟ;
	    ଅନ୍ୟଥା ଯଦି (!(OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP
		       && (OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_POINTER
			   || (OMP_CLAUSE_MAP_KIND (c)
			       == GOMP_MAP_FIRSTPRIVATE_POINTER)
			   || (OMP_CLAUSE_MAP_KIND (c)
			       == GOMP_MAP_FORCE_DEVICEPTR)))
		     && t == OMP_CLAUSE_DECL (c)
		     && !omp_mappable_type (ବୃକ୍ଷ_TYPE (t)))
	      {
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD does not have a mappable type in %qs clause", t,
			  omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		remove = ସତ୍ୟ;
	      }
	    ଅନ୍ୟଥା ଯଦି (ବୃକ୍ଷ_TYPE (t) == error_mark_ଗଣ୍ଠି)
	      remove = ସତ୍ୟ;
	    ଅନ୍ୟଥା ଯଦି (TYPE_ATOMIC (strip_array_types (ବୃକ୍ଷ_TYPE (t))))
	      {
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%<_Atomic%> %qE in %qs clause", t,
			  omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		remove = ସତ୍ୟ;
	      }
	    ଅନ୍ୟଥା ଯଦି (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP
		     && OMP_CLAUSE_MAP_IMPLICIT (c)
		     && (bitmap_bit_p (&map_head, DECL_UID (t))
			 || bitmap_bit_p (&map_field_head, DECL_UID (t))
			 || bitmap_bit_p (&map_firstprivate_head,
					  DECL_UID (t))))
	      remove = ସତ୍ୟ;
	    ଅନ୍ୟଥା ଯଦି (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP
		     && (OMP_CLAUSE_MAP_KIND (c)
			 == GOMP_MAP_FIRSTPRIVATE_POINTER))
	      {
		ଯଦି (bitmap_bit_p (&generic_head, DECL_UID (t))
		    || bitmap_bit_p (&firstprivate_head, DECL_UID (t))
		    || bitmap_bit_p (&map_firstprivate_head, DECL_UID (t)))
		  {
		    error_at (OMP_CLAUSE_LOCATION (c),
			      "%qD appears more than once in data clauses", t);
		    remove = ସତ୍ୟ;
		  }
		ଅନ୍ୟଥା ଯଦି (bitmap_bit_p (&map_head, DECL_UID (t))
			 && !bitmap_bit_p (&map_field_head, DECL_UID (t))
			 && openacc)
		  {
		    error_at (OMP_CLAUSE_LOCATION (c),
			      "%qD appears more than once in data clauses", t);
		    remove = ସତ୍ୟ;
		  }
		ଅନ୍ୟଥା
		  bitmap_set_bit (&map_firstprivate_head, DECL_UID (t));
	      }
	    ଅନ୍ୟଥା ଯଦି (bitmap_bit_p (&map_head, DECL_UID (t))
		     && !bitmap_bit_p (&map_field_head, DECL_UID (t))
		     && ort != C_ORT_OMP
		     && ort != C_ORT_OMP_TARGET
		     && ort != C_ORT_OMP_EXIT_DATA)
	      {
		ଯଦି (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_MAP)
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD appears more than once in motion clauses", t);
		ଅନ୍ୟଥା ଯଦି (openacc)
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD appears more than once in data clauses", t);
		ଅନ୍ୟଥା
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD appears more than once in map clauses", t);
		remove = ସତ୍ୟ;
	      }
	    ଅନ୍ୟଥା ଯଦି (openacc && bitmap_bit_p (&generic_head, DECL_UID (t)))
	      {
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD appears more than once in data clauses", t);
		remove = ସତ୍ୟ;
	      }
	    ଅନ୍ୟଥା ଯଦି (bitmap_bit_p (&firstprivate_head, DECL_UID (t))
		     || bitmap_bit_p (&is_on_device_head, DECL_UID (t)))
	      {
		ଯଦି (openacc)
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD appears more than once in data clauses", t);
		ଅନ୍ୟଥା
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD appears both in data and map clauses", t);
		remove = ସତ୍ୟ;
	      }
	    ଅନ୍ୟଥା ଯଦି (!omp_access_chain_p (addr_tokens, 1))
	      {
		bitmap_set_bit (&map_head, DECL_UID (t));
		ଯଦି (t != OMP_CLAUSE_DECL (c)
		    && ବୃକ୍ଷ_CODE (OMP_CLAUSE_DECL (c)) == COMPONENT_REF)
		  bitmap_set_bit (&map_field_head, DECL_UID (t));
	      }

	  skip_decl_checks:
	    /* If we call omp_expand_map_clause in handle_omp_array_sections,
	       the containing loop (here) iterates through the new nodes
	       created by that expansion.  Avoid expanding those again (just
	       by checking the node type).  */
	    ଯଦି (!remove
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
		ବୃକ୍ଷ nc = ai.expand_map_clause (c, OMP_CLAUSE_DECL (c),
						addr_tokens, ort);
		ଯଦି (nc != error_mark_ଗଣ୍ଠି)
		  c = nc;
	      }
	  }
	  ଭାଙ୍ଗ;

	ସ୍ଥିତି OMP_CLAUSE_ENTER:
	ସ୍ଥିତି OMP_CLAUSE_LINK:
	ସ୍ଥିତି OMP_CLAUSE_LOCAL:
	  t = OMP_CLAUSE_DECL (c);
	  ଅଚଳ ଅକ୍ଷର *cname;
	  cname = omp_clause_code_name[OMP_CLAUSE_CODE (c)];
	  ଯଦି (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_ENTER
	      && OMP_CLAUSE_ENTER_TO (c))
	    cname = "to";
	  ଯଦି (ବୃକ୍ଷ_CODE (t) == FUNCTION_DECL
	      && OMP_CLAUSE_CODE (c) == OMP_CLAUSE_ENTER)
	    ;
	  ଅନ୍ୟଥା ଯଦି (!VAR_P (t))
	    {
	      ଯଦି (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_ENTER)
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qE is neither a variable nor a function name in "
			  "clause %qs", t, cname);
	      ଅନ୍ୟଥା
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qE is not a variable in clause %qs", t, cname);
	      remove = ସତ୍ୟ;
	    }
	  ଅନ୍ୟଥା ଯଦି (DECL_THREAD_LOCAL_P (t))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qD is threadprivate variable in %qs clause", t,
			cname);
	      remove = ସତ୍ୟ;
	    }
	  ଅନ୍ୟଥା ଯଦି (!omp_mappable_type (ବୃକ୍ଷ_TYPE (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qD does not have a mappable type in %qs clause", t,
			cname);
	      remove = ସତ୍ୟ;
	    }
	  ଯଦି (remove)
	    ଭାଙ୍ଗ;
	  ଯଦି (bitmap_bit_p (&generic_head, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE appears more than once on the same "
			"%<declare target%> directive", t);
	      remove = ସତ୍ୟ;
	    }
	  ଅନ୍ୟଥା
	    bitmap_set_bit (&generic_head, DECL_UID (t));
	  ଭାଙ୍ଗ;

	ସ୍ଥିତି OMP_CLAUSE_UNIFORM:
	  t = OMP_CLAUSE_DECL (c);
	  ଯଦି (ବୃକ୍ଷ_CODE (t) != PARM_DECL)
	    {
	      ଯଦି (DECL_P (t))
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD is not an argument in %<uniform%> clause", t);
	      ଅନ୍ୟଥା
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qE is not an argument in %<uniform%> clause", t);
	      remove = ସତ୍ୟ;
	      ଭାଙ୍ଗ;
	    }
	  /* map_head bitmap is used as uniform_head if declare_simd.  */
	  bitmap_set_bit (&map_head, DECL_UID (t));
	  ଯାଅ check_dup_generic;

	ସ୍ଥିତି OMP_CLAUSE_IS_DEVICE_PTR:
	ସ୍ଥିତି OMP_CLAUSE_USE_DEVICE_PTR:
	  t = OMP_CLAUSE_DECL (c);
	  ଯଦି (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IS_DEVICE_PTR)
	    bitmap_set_bit (&is_on_device_head, DECL_UID (t));
	  ଯଦି (ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (t)) != POINTER_TYPE)
	    {
	      ଯଦି (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_USE_DEVICE_PTR
		  && !openacc)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qs variable is not a pointer",
			    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		  remove = ସତ୍ୟ;
		}
	      ଅନ୍ୟଥା ଯଦି (ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (t)) != ARRAY_TYPE)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qs variable is neither a pointer nor an array",
			    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		  remove = ସତ୍ୟ;
		}
	    }
	  ଯାଅ check_dup_generic;

	ସ୍ଥିତି OMP_CLAUSE_HAS_DEVICE_ADDR:
	  t = OMP_CLAUSE_DECL (c);
	  ଯଦି (ବୃକ୍ଷ_CODE (t) == OMP_ARRAY_SECTION)
	    {
	      ଯଦି (handle_omp_array_sections (c, ort))
		remove = ସତ୍ୟ;
	      ଅନ୍ୟଥା
		{
		  t = OMP_CLAUSE_DECL (c);
		  ଯେତେବେଳେ (ବୃକ୍ଷ_CODE (t) == ARRAY_REF)
		    t = ବୃକ୍ଷ_OPERAND (t, 0);
		}
	    }
	  bitmap_set_bit (&is_on_device_head, DECL_UID (t));
	  ଯଦି (VAR_P (t) || ବୃକ୍ଷ_CODE (t) == PARM_DECL)
	    c_mark_addressable (t);
	  ଯାଅ check_dup_generic_t;

	ସ୍ଥିତି OMP_CLAUSE_USE_DEVICE_ADDR:
	  t = OMP_CLAUSE_DECL (c);
	  ଯଦି (VAR_P (t) || ବୃକ୍ଷ_CODE (t) == PARM_DECL)
	    c_mark_addressable (t);
	  ଯାଅ check_dup_generic;

	ସ୍ଥିତି OMP_CLAUSE_NOWAIT:
	  ଯଦି (copyprivate_seen)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<nowait%> clause must not be used together "
			"with %<copyprivate%> clause");
	      remove = ସତ୍ୟ;
	      ଭାଙ୍ଗ;
	    }
	  nowait_clause = pc;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  ଜାରି;

	ସ୍ଥିତି OMP_CLAUSE_ORDER:
	  ଯଦି (ordered_clause)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<order%> clause must not be used together "
			"with %<ordered%> clause");
	      remove = ସତ୍ୟ;
	      ଭାଙ୍ଗ;
	    }
	  ଅନ୍ୟଥା ଯଦି (order_clause)
	    {
	      /* Silently remove duplicates.  */
	      remove = ସତ୍ୟ;
	      ଭାଙ୍ଗ;
	    }
	  order_clause = pc;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  ଜାରି;

	ସ୍ଥିତି OMP_CLAUSE_DETACH:
	  t = OMP_CLAUSE_DECL (c);
	  ଯଦି (detach_seen)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"too many %qs clauses on a task construct",
			"detach");
	      remove = ସତ୍ୟ;
	      ଭାଙ୍ଗ;
	    }
	  detach_seen = pc;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  c_mark_addressable (t);
	  ଜାରି;

	ସ୍ଥିତି OMP_CLAUSE_IF:
	ସ୍ଥିତି OMP_CLAUSE_SELF:
	ସ୍ଥିତି OMP_CLAUSE_ଅଙ୍କ_THREADS:
	ସ୍ଥିତି OMP_CLAUSE_ଅଙ୍କ_TEAMS:
	ସ୍ଥିତି OMP_CLAUSE_THREAD_LIMIT:
	ସ୍ଥିତି OMP_CLAUSE_DEFAULT:
	ସ୍ଥିତି OMP_CLAUSE_UNTIED:
	ସ୍ଥିତି OMP_CLAUSE_COLLAPSE:
	ସ୍ଥିତି OMP_CLAUSE_FINAL:
	ସ୍ଥିତି OMP_CLAUSE_DEVICE:
	ସ୍ଥିତି OMP_CLAUSE_DIST_SCHEDULE:
	ସ୍ଥିତି OMP_CLAUSE_DYN_GROUPPRIVATE:
	ସ୍ଥିତି OMP_CLAUSE_PARALLEL:
	ସ୍ଥିତି OMP_CLAUSE_FOR:
	ସ୍ଥିତି OMP_CLAUSE_SECTIONS:
	ସ୍ଥିତି OMP_CLAUSE_TASKGROUP:
	ସ୍ଥିତି OMP_CLAUSE_PROC_BIND:
	ସ୍ଥିତି OMP_CLAUSE_DEVICE_TYPE:
	ସ୍ଥିତି OMP_CLAUSE_PRIORITY:
	ସ୍ଥିତି OMP_CLAUSE_THREADS:
	ସ୍ଥିତି OMP_CLAUSE_SIMD:
	ସ୍ଥିତି OMP_CLAUSE_HINT:
	ସ୍ଥିତି OMP_CLAUSE_FILTER:
	ସ୍ଥିତି OMP_CLAUSE_DEFAULTMAP:
	ସ୍ଥିତି OMP_CLAUSE_BIND:
	ସ୍ଥିତି OMP_CLAUSE_ଅଙ୍କ_GANGS:
	ସ୍ଥିତି OMP_CLAUSE_ଅଙ୍କ_WORKERS:
	ସ୍ଥିତି OMP_CLAUSE_VECTOR_LENGTH:
	ସ୍ଥିତି OMP_CLAUSE_ASYNC:
	ସ୍ଥିତି OMP_CLAUSE_WAIT:
	ସ୍ଥିତି OMP_CLAUSE_AUTO:
	ସ୍ଥିତି OMP_CLAUSE_INDEPENDENT:
	ସ୍ଥିତି OMP_CLAUSE_SEQ:
	ସ୍ଥିତି OMP_CLAUSE_GANG:
	ସ୍ଥିତି OMP_CLAUSE_WORKER:
	ସ୍ଥିତି OMP_CLAUSE_VECTOR:
	ସ୍ଥିତି OMP_CLAUSE_TILE:
	ସ୍ଥିତି OMP_CLAUSE_IF_PRESENT:
	ସ୍ଥିତି OMP_CLAUSE_FINALIZE:
	ସ୍ଥିତି OMP_CLAUSE_NOHOST:
	ସ୍ଥିତି OMP_CLAUSE_INDIRECT:
	ସ୍ଥିତି OMP_CLAUSE_NOVARIANTS:
	ସ୍ଥିତି OMP_CLAUSE_NOCONTEXT:
	  pc = &OMP_CLAUSE_CHAIN (c);
	  ଜାରି;

	ସ୍ଥିତି OMP_CLAUSE_GRAINSIZE:
	  grainsize_seen = pc;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  ଜାରି;

	ସ୍ଥିତି OMP_CLAUSE_ଅଙ୍କ_TASKS:
	  ଅଙ୍କ_tasks_seen = ସତ୍ୟ;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  ଜାରି;

	ସ୍ଥିତି OMP_CLAUSE_MERGEABLE:
	  mergeable_seen = ସତ୍ୟ;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  ଜାରି;

	ସ୍ଥିତି OMP_CLAUSE_NOGROUP:
	  nogroup_seen = pc;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  ଜାରି;

	ସ୍ଥିତି OMP_CLAUSE_SCHEDULE:
	  schedule_clause = c;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  ଜାରି;

	ସ୍ଥିତି OMP_CLAUSE_ORDERED:
	  ordered_clause = c;
	  ଯଦି (order_clause)
	    {
	      error_at (OMP_CLAUSE_LOCATION (*order_clause),
			"%<order%> clause must not be used together "
			"with %<ordered%> clause");
	      *order_clause = OMP_CLAUSE_CHAIN (*order_clause);
	      order_clause = ଖାଲି;
	    }
	  pc = &OMP_CLAUSE_CHAIN (c);
	  ଜାରି;

	ସ୍ଥିତି OMP_CLAUSE_SAFELEN:
	  safelen = c;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  ଜାରି;
	ସ୍ଥିତି OMP_CLAUSE_SIMDLEN:
	  simdlen = c;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  ଜାରି;

	ସ୍ଥିତି OMP_CLAUSE_FULL:
	  full_seen = pc;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  ଜାରି;

	ସ୍ଥିତି OMP_CLAUSE_PARTIAL:
	  partial_seen = ସତ୍ୟ;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  ଜାରି;

	ସ୍ଥିତି OMP_CLAUSE_SIZES:
	  pc = &OMP_CLAUSE_CHAIN (c);
	  ଜାରି;

	ସ୍ଥିତି OMP_CLAUSE_INBRANCH:
	ସ୍ଥିତି OMP_CLAUSE_NOTINBRANCH:
	  ଯଦି (branch_seen)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<inbranch%> clause is incompatible with "
			"%<notinbranch%>");
	      remove = ସତ୍ୟ;
	      ଭାଙ୍ଗ;
	    }
	  branch_seen = ସତ୍ୟ;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  ଜାରି;

	ସ୍ଥିତି OMP_CLAUSE_INCLUSIVE:
	ସ୍ଥିତି OMP_CLAUSE_EXCLUSIVE:
	  need_complete = ସତ୍ୟ;
	  need_implicitly_determined = ସତ୍ୟ;
	  t = OMP_CLAUSE_DECL (c);
	  ଯଦି (!VAR_P (t) && ବୃକ୍ଷ_CODE (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in clause %qs", t,
			omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	      remove = ସତ୍ୟ;
	    }
	  ଭାଙ୍ଗ;

	ସ୍ଥିତି OMP_CLAUSE_INIT:
	  init_seen = ସତ୍ୟ;
	  ଯଦି (!OMP_CLAUSE_INIT_TARGETSYNC (c))
	    init_no_targetsync_clause = c;
	  /* FALLTHRU */
	ସ୍ଥିତି OMP_CLAUSE_DESTROY:
	ସ୍ଥିତି OMP_CLAUSE_USE:
	  init_use_destroy_seen = ସତ୍ୟ;
	  t = OMP_CLAUSE_DECL (c);
	  ଯଦି (bitmap_bit_p (&generic_head, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qD appears more than once in action clauses", t);
	      remove = ସତ୍ୟ;
	      ଭାଙ୍ଗ;
	    }
	  bitmap_set_bit (&generic_head, DECL_UID (t));
	  /* FALLTHRU */
	ସ୍ଥିତି OMP_CLAUSE_INTEROP:
	  ଯଦି (/* ort == C_ORT_OMP_INTEROP [uncomment for depobj init]  */
		   !c_omp_interop_t_p (ବୃକ୍ଷ_TYPE (OMP_CLAUSE_DECL (c))))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qD must be of %<omp_interop_t%>",
			OMP_CLAUSE_DECL (c));
	      remove = ସତ୍ୟ;
	    }
	  ଅନ୍ୟଥା ଯଦି ((OMP_CLAUSE_CODE (c) == OMP_CLAUSE_INIT
		    || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DESTROY)
		   && ବୃକ୍ଷ_READONLY (OMP_CLAUSE_DECL (c)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
		      "%qD shall not be const", OMP_CLAUSE_DECL (c));
	      remove = ସତ୍ୟ;
	    }
	  pc = &OMP_CLAUSE_CHAIN (c);
	  ଭାଙ୍ଗ;
	ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
	  gcc_unreachable ();
	}

      ଯଦି (!remove)
	{
	  t = OMP_CLAUSE_DECL (c);

	  ଯଦି (need_complete)
	    {
	      t = require_complete_type (OMP_CLAUSE_LOCATION (c), t);
	      ଯଦି (t == error_mark_ଗଣ୍ଠି)
		remove = ସତ୍ୟ;
	    }

	  ଯଦି (need_implicitly_determined)
	    {
	      ଅଚଳ ଅକ୍ଷର *share_name = ଖାଲି;

	      ଯଦି (VAR_P (t) && DECL_THREAD_LOCAL_P (t))
		share_name = "threadprivate";
	      ଅନ୍ୟଥା ବାଛ (c_omp_predetermined_sharing (t))
		{
		ସ୍ଥିତି OMP_CLAUSE_DEFAULT_UNSPECIFIED:
		  ଭାଙ୍ଗ;
		ସ୍ଥିତି OMP_CLAUSE_DEFAULT_SHARED:
		  ଯଦି ((OMP_CLAUSE_CODE (c) == OMP_CLAUSE_SHARED
		       || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_FIRSTPRIVATE)
		      && c_omp_predefined_variable (t))
		    /* The __func__ variable and similar function-local
		       predefined variables may be listed in a shared or
		       firstprivate clause.  */
		    ଭାଙ୍ଗ;
		  share_name = "shared";
		  ଭାଙ୍ଗ;
		ସ୍ଥିତି OMP_CLAUSE_DEFAULT_PRIVATE:
		  share_name = "private";
		  ଭାଙ୍ଗ;
		ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
		  gcc_unreachable ();
		}
	      ଯଦି (share_name)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qE is predetermined %qs for %qs",
			    t, share_name,
			    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		  remove = ସତ୍ୟ;
		}
	      ଅନ୍ୟଥା ଯଦି (ବୃକ୍ଷ_READONLY (t)
		       && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_SHARED
		       && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_FIRSTPRIVATE)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%<const%> qualified %qE may appear only in "
			    "%<shared%> or %<firstprivate%> clauses", t);
		  remove = ସତ୍ୟ;
		}
	    }
	}

      ଯଦି (remove)
	{
	  ଯଦି (grp_start_p)
	    {
	      /* If we found a clause to remove, we want to remove the whole
		 expanded group, otherwise gimplify
		 (omp_resolve_clause_dependencies) can get confused.  */
	      *grp_start_p = grp_sentinel;
	      pc = grp_start_p;
	      grp_start_p = ଖାଲି;
	    }
	  ଅନ୍ୟଥା
	    *pc = OMP_CLAUSE_CHAIN (c);
	}
      ଅନ୍ୟଥା
	pc = &OMP_CLAUSE_CHAIN (c);
    }

  ଯଦି (grp_start_p
      && OMP_CLAUSE_HAS_ITERATORS (*grp_start_p))
    ପାଇଁ (ବୃକ୍ଷ gc = *grp_start_p; gc; gc = OMP_CLAUSE_CHAIN (gc))
      OMP_CLAUSE_ITERATORS (gc) = OMP_CLAUSE_ITERATORS (*grp_start_p);

  ଯଦି (simdlen
      && safelen
      && ବୃକ୍ଷ_int_cst_lt (OMP_CLAUSE_SAFELEN_ପଦସମଷ୍ଟି (safelen),
			  OMP_CLAUSE_SIMDLEN_ପଦସମଷ୍ଟି (simdlen)))
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
      OMP_CLAUSE_SIMDLEN_ପଦସମଷ୍ଟି (simdlen)
	= OMP_CLAUSE_SAFELEN_ପଦସମଷ୍ଟି (safelen);
    }

  ଯଦି (ordered_clause
      && schedule_clause
      && (OMP_CLAUSE_SCHEDULE_KIND (schedule_clause)
	  & OMP_CLAUSE_SCHEDULE_NONMONOTONIC))
    {
      error_at (OMP_CLAUSE_LOCATION (schedule_clause),
		"%<nonmonotonic%> schedule modifier specified together "
		"with %<ordered%> clause");
      OMP_CLAUSE_SCHEDULE_KIND (schedule_clause)
	= (ଗଣନା omp_clause_schedule_kind)
	  (OMP_CLAUSE_SCHEDULE_KIND (schedule_clause)
	   & ~OMP_CLAUSE_SCHEDULE_NONMONOTONIC);
    }

  ଯଦି (reduction_seen < 0 && ordered_clause)
    {
      error_at (OMP_CLAUSE_LOCATION (ordered_clause),
		"%qs clause specified together with %<inscan%> "
		"%<reduction%> clause", "ordered");
      reduction_seen = -2;
    }

  ଯଦି (reduction_seen < 0 && schedule_clause)
    {
      error_at (OMP_CLAUSE_LOCATION (schedule_clause),
		"%qs clause specified together with %<inscan%> "
		"%<reduction%> clause", "schedule");
      reduction_seen = -2;
    }

  ଯଦି (linear_variable_step_check
      || reduction_seen == -2
      || allocate_seen
      || target_in_reduction_seen)
    ପାଇଁ (pc = &clauses, c = clauses; c ; c = *pc)
      {
	ତାର୍କିକ remove = ମିଥ୍ୟା;
	ଯଦି (allocate_seen)
	  ବାଛ (OMP_CLAUSE_CODE (c))
	    {
	    ସ୍ଥିତି OMP_CLAUSE_REDUCTION:
	    ସ୍ଥିତି OMP_CLAUSE_IN_REDUCTION:
	    ସ୍ଥିତି OMP_CLAUSE_TASK_REDUCTION:
	      ଯଦି (ବୃକ୍ଷ_CODE (OMP_CLAUSE_DECL (c)) == MEM_REF)
		{
		  t = ବୃକ୍ଷ_OPERAND (OMP_CLAUSE_DECL (c), 0);
		  ଯଦି (ବୃକ୍ଷ_CODE (t) == POINTER_PLUS_ପଦସମଷ୍ଟି)
		    t = ବୃକ୍ଷ_OPERAND (t, 0);
		  ଯଦି (ବୃକ୍ଷ_CODE (t) == ADDR_ପଦସମଷ୍ଟି
		      || INDIRECT_REF_P (t))
		    t = ବୃକ୍ଷ_OPERAND (t, 0);
		  ଯଦି (DECL_P (t))
		    bitmap_clear_bit (&aligned_head, DECL_UID (t));
		  ଭାଙ୍ଗ;
		}
	      /* FALLTHRU */
	    ସ୍ଥିତି OMP_CLAUSE_PRIVATE:
	    ସ୍ଥିତି OMP_CLAUSE_FIRSTPRIVATE:
	    ସ୍ଥିତି OMP_CLAUSE_LASTPRIVATE:
	    ସ୍ଥିତି OMP_CLAUSE_LINEAR:
	      ଯଦି (DECL_P (OMP_CLAUSE_DECL (c)))
		bitmap_clear_bit (&aligned_head,
				  DECL_UID (OMP_CLAUSE_DECL (c)));
	      ଭାଙ୍ଗ;
	    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
	      ଭାଙ୍ଗ;
	    }
	ଯଦି (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_LINEAR
	    && OMP_CLAUSE_LINEAR_VARIABLE_STRIDE (c)
	    && !bitmap_bit_p (&map_head,
			      DECL_UID (OMP_CLAUSE_LINEAR_STEP (c))))
	  {
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%<linear%> clause step is a parameter %qD not "
		      "specified in %<uniform%> clause",
		      OMP_CLAUSE_LINEAR_STEP (c));
	    remove = ସତ୍ୟ;
	  }
	ଅନ୍ୟଥା ଯଦି (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_REDUCTION
		 && reduction_seen == -2)
	  OMP_CLAUSE_REDUCTION_INSCAN (c) = 0;
	ଯଦି (target_in_reduction_seen
	    && OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP)
	  {
	    ବୃକ୍ଷ t = OMP_CLAUSE_DECL (c);
	    ଯେତେବେଳେ (handled_component_p (t)
		   || INDIRECT_REF_P (t)
		   || ବୃକ୍ଷ_CODE (t) == ADDR_ପଦସମଷ୍ଟି
		   || ବୃକ୍ଷ_CODE (t) == MEM_REF
		   || ବୃକ୍ଷ_CODE (t) == NON_LVALUE_ପଦସମଷ୍ଟି)
	      t = ବୃକ୍ଷ_OPERAND (t, 0);
	    ଯଦି (DECL_P (t)
		&& bitmap_bit_p (&oacc_reduction_head, DECL_UID (t)))
	      OMP_CLAUSE_MAP_IN_REDUCTION (c) = 1;
	  }

	ଯଦି (remove)
	  *pc = OMP_CLAUSE_CHAIN (c);
	ଅନ୍ୟଥା
	  pc = &OMP_CLAUSE_CHAIN (c);
      }

  ଯଦି (allocate_seen)
    ପାଇଁ (pc = &clauses, c = clauses; c ; c = *pc)
      {
	ତାର୍କିକ remove = ମିଥ୍ୟା;
	ଯଦି (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_ALLOCATE
	    && !OMP_CLAUSE_ALLOCATE_COMBINED (c)
	    && bitmap_bit_p (&aligned_head, DECL_UID (OMP_CLAUSE_DECL (c))))
	  {
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%qD specified in %<allocate%> clause but not in "
		      "an explicit privatization clause", OMP_CLAUSE_DECL (c));
	    remove = ସତ୍ୟ;
	  }
	ଯଦି (remove)
	  *pc = OMP_CLAUSE_CHAIN (c);
	ଅନ୍ୟଥା
	  pc = &OMP_CLAUSE_CHAIN (c);
      }

  ଯଦି (nogroup_seen && reduction_seen)
    {
      error_at (OMP_CLAUSE_LOCATION (*nogroup_seen),
		"%<nogroup%> clause must not be used together with "
		"%<reduction%> clause");
      *nogroup_seen = OMP_CLAUSE_CHAIN (*nogroup_seen);
    }

  ଯଦି (grainsize_seen && ଅଙ୍କ_tasks_seen)
    {
      error_at (OMP_CLAUSE_LOCATION (*grainsize_seen),
		"%<grainsize%> clause must not be used together with "
		"%<num_tasks%> clause");
      *grainsize_seen = OMP_CLAUSE_CHAIN (*grainsize_seen);
    }

  ଯଦି (full_seen && partial_seen)
    {
      error_at (OMP_CLAUSE_LOCATION (*full_seen),
		"%<full%> clause must not be used together with "
		"%<partial%> clause");
      *full_seen = OMP_CLAUSE_CHAIN (*full_seen);
    }

  ଯଦି (detach_seen)
    {
      ଯଦି (mergeable_seen)
	{
	  error_at (OMP_CLAUSE_LOCATION (*detach_seen),
		    "%<detach%> clause must not be used together with "
		    "%<mergeable%> clause");
	  *detach_seen = OMP_CLAUSE_CHAIN (*detach_seen);
	}
      ଅନ୍ୟଥା
	{
	  ବୃକ୍ଷ detach_decl = OMP_CLAUSE_DECL (*detach_seen);

	  ପାଇଁ (pc = &clauses, c = clauses; c ; c = *pc)
	    {
	      ତାର୍କିକ remove = ମିଥ୍ୟା;
	      ଯଦି ((OMP_CLAUSE_CODE (c) == OMP_CLAUSE_SHARED
		   || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_PRIVATE
		   || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_FIRSTPRIVATE
		   || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_LASTPRIVATE)
		  && OMP_CLAUSE_DECL (c) == detach_decl)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "the event handle of a %<detach%> clause "
			    "should not be in a data-sharing clause");
		  remove = ସତ୍ୟ;
		}
	      ଯଦି (remove)
		*pc = OMP_CLAUSE_CHAIN (c);
	      ଅନ୍ୟଥା
		pc = &OMP_CLAUSE_CHAIN (c);
	    }
	}
    }

  ଯଦି (ort == C_ORT_OMP_INTEROP
      && depend_clause
      && (!init_use_destroy_seen
	  || (init_seen && init_no_targetsync_clause)))
    {
      error_at (OMP_CLAUSE_LOCATION (depend_clause),
		"%<depend%> clause requires action clauses with "
		"%<targetsync%> interop-type");
      ଯଦି (init_no_targetsync_clause)
	inform (OMP_CLAUSE_LOCATION (init_no_targetsync_clause),
		"%<init%> clause lacks the %<targetsync%> modifier");
    }

  bitmap_obstack_release (ଖାଲି);
  ଫେରନ୍ତୁ clauses;
}

/* Do processing necessary to make CLAUSES well-formed, where CLAUSES result
   from implicit instantiation of user-defined mappers (in gimplify.cc).  */

ବୃକ୍ଷ
c_omp_finish_mapper_clauses (ବୃକ୍ଷ clauses)
{
  ଫେରନ୍ତୁ c_finish_omp_clauses (clauses, C_ORT_OMP);
}

/* Return code to initialize DST with a copy constructor from SRC.
   C doesn't have copy constructors nor assignment operators, only for
   _Atomic vars we need to perform __atomic_load from src into a temporary
   followed by __atomic_store of the temporary to dst.  */

ବୃକ୍ଷ
c_omp_clause_copy_ctor (ବୃକ୍ଷ clause, ବୃକ୍ଷ dst, ବୃକ୍ଷ src)
{
  ଯଦି (!really_atomic_lvalue (dst) && !really_atomic_lvalue (src))
    ଫେରନ୍ତୁ build2 (MODIFY_ପଦସମଷ୍ଟି, ବୃକ୍ଷ_TYPE (dst), dst, src);

  location_t loc = OMP_CLAUSE_LOCATION (clause);
  ବୃକ୍ଷ type = ବୃକ୍ଷ_TYPE (dst);
  ବୃକ୍ଷ nonatomic_type = build_qualified_type (type, TYPE_UNQUALIFIED);
  ବୃକ୍ଷ tmp = create_tmp_var (nonatomic_type);
  ବୃକ୍ଷ tmp_addr = build_fold_addr_ପଦସମଷ୍ଟି (tmp);
  ବୃକ୍ଷ_ADDRESSABLE (tmp) = 1;
  suppress_warning (tmp);
  ବୃକ୍ଷ src_addr = build_fold_addr_ପଦସମଷ୍ଟି (src);
  ବୃକ୍ଷ dst_addr = build_fold_addr_ପଦସମଷ୍ଟି (dst);
  ବୃକ୍ଷ seq_cst = build_int_cst (integer_type_ଗଣ୍ଠି, MEMMODEL_SEQ_CST);
  vec<ବୃକ୍ଷ, va_gc> *params;
  /* Expansion of a generic atomic load may require an addition
     element, so allocate enough to prevent a resize.  */
  vec_alloc (params, 4);

  /* Build __atomic_load (&src, &tmp, SEQ_CST);  */
  ବୃକ୍ଷ fndecl = builtin_decl_explicit (BUILT_IN_ATOMIC_LOAD);
  params->quick_ଠେଲ (src_addr);
  params->quick_ଠେଲ (tmp_addr);
  params->quick_ଠେଲ (seq_cst);
  ବୃକ୍ଷ load = c_build_function_call_vec (loc, vNULL, fndecl, params, ଖାଲି);

  vec_alloc (params, 4);

  /* Build __atomic_store (&dst, &tmp, SEQ_CST);  */
  fndecl = builtin_decl_explicit (BUILT_IN_ATOMIC_STORE);
  params->quick_ଠେଲ (dst_addr);
  params->quick_ଠେଲ (tmp_addr);
  params->quick_ଠେଲ (seq_cst);
  ବୃକ୍ଷ store = c_build_function_call_vec (loc, vNULL, fndecl, params, ଖାଲି);
  ଫେରନ୍ତୁ build2 (COMPOUND_ପଦସମଷ୍ଟି, void_type_ଗଣ୍ଠି, load, store);
}

/* Create a transaction node.  */

ବୃକ୍ଷ
c_finish_transaction (location_t loc, ବୃକ୍ଷ block, ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags)
{
  ବୃକ୍ଷ stmt = build_stmt (loc, TRANSACTION_ପଦସମଷ୍ଟି, block);
  ଯଦି (flags & TM_STMT_ATTR_OUTER)
    TRANSACTION_ପଦସମଷ୍ଟି_OUTER (stmt) = 1;
  ଯଦି (flags & TM_STMT_ATTR_RELAXED)
    TRANSACTION_ପଦସମଷ୍ଟି_RELAXED (stmt) = 1;
  ଫେରନ୍ତୁ add_stmt (stmt);
}

/* Make a variant type in the proper way for C/C++, propagating qualifiers
   down to the element type of an array.  If ORIG_QUAL_TYPE is not
   NULL, then it should be used as the qualified type
   ORIG_QUAL_INDIRECT levels down in array type derivation (to
   preserve information about the typedef name from which an array
   type was derived).  */

ବୃକ୍ଷ
c_build_qualified_type (ବୃକ୍ଷ type, ପୂର୍ଣ୍ଣସଂଖ୍ୟା type_quals, ବୃକ୍ଷ orig_qual_type,
			size_t orig_qual_indirect)
{
  ଯଦି (type == error_mark_ଗଣ୍ଠି)
    ଫେରନ୍ତୁ type;

  ଯଦି (ବୃକ୍ଷ_CODE (type) == ARRAY_TYPE)
    {
      ବୃକ୍ଷ t;
      ବୃକ୍ଷ element_type = c_build_qualified_type (ବୃକ୍ଷ_TYPE (type),
						  type_quals, orig_qual_type,
						  orig_qual_indirect - 1);

      /* See if we already have an identically qualified type.  */
      ଯଦି (orig_qual_type && orig_qual_indirect == 0)
	t = orig_qual_type;
      ଅନ୍ୟଥା
	ପାଇଁ (t = TYPE_MAIN_VARIANT (type); t; t = TYPE_NEXT_VARIANT (t))
	  {
	    ଯଦି (TYPE_QUALS (strip_array_types (t)) == type_quals
		&& TYPE_NAME (t) == TYPE_NAME (type)
		&& TYPE_CONTEXT (t) == TYPE_CONTEXT (type)
		&& attribute_list_equal (TYPE_ATTRIBUTES (t),
					 TYPE_ATTRIBUTES (type)))
	      ଭାଙ୍ଗ;
	  }
      ଯଦି (!t)
	{
          ବୃକ୍ଷ domain = TYPE_DOMAIN (type);

	  t = build_variant_type_copy (type);
	  ବୃକ୍ଷ_TYPE (t) = element_type;
	  TYPE_ADDR_SPACE (t) = TYPE_ADDR_SPACE (element_type);

          ଯଦି (TYPE_STRUCTURAL_EQUALITY_P (element_type)
              || (domain && TYPE_STRUCTURAL_EQUALITY_P (domain)))
            SET_TYPE_STRUCTURAL_EQUALITY (t);
          ଅନ୍ୟଥା ଯଦି (TYPE_CANONICAL (element_type) != element_type
                   || (domain && TYPE_CANONICAL (domain) != domain))
            {
              ବୃକ୍ଷ unqualified_canon
		= c_build_array_type (TYPE_CANONICAL (element_type),
				      domain ? TYPE_CANONICAL (domain)
					     : NULL_ବୃକ୍ଷ);
              ଯଦି (TYPE_REVERSE_STORAGE_ORDER (type))
                {
                  unqualified_canon
		    = build_distinct_type_copy (unqualified_canon);
                  TYPE_REVERSE_STORAGE_ORDER (unqualified_canon) = 1;
                }
              TYPE_CANONICAL (t)
		= c_build_qualified_type (unqualified_canon, type_quals);
            }
          ଅନ୍ୟଥା
            TYPE_CANONICAL (t) = t;
	}
      ଫେରନ୍ତୁ t;
    }

  /* A restrict-qualified pointer type must be a pointer to object or
     incomplete type.  Note that the use of POINTER_TYPE_P also allows
     REFERENCE_TYPEs, which is appropriate for C++.  */
  ଯଦି ((type_quals & TYPE_QUAL_RESTRICT)
      && (!POINTER_TYPE_P (type)
	  || !C_TYPE_OBJECT_OR_INCOMPLETE_P (ବୃକ୍ଷ_TYPE (type))))
    {
      error ("invalid use of %<restrict%>");
      type_quals &= ~TYPE_QUAL_RESTRICT;
    }

  ବୃକ୍ଷ var_type = (orig_qual_type && orig_qual_indirect == 0
		   ? orig_qual_type
		   : build_qualified_type (type, type_quals));

  gcc_checking_assert (C_TYPE_VARIABLE_SIZE (var_type)
		       == C_TYPE_VARIABLE_SIZE (type));
  gcc_checking_assert (c_type_variably_modified_p (var_type)
		       == c_type_variably_modified_p (type));

  /* A variant type does not inherit the list of incomplete vars from the
     type main variant.  */
  ଯଦି ((RECORD_OR_UNION_TYPE_P (var_type)
       || ବୃକ୍ଷ_CODE (var_type) == ENUMERAL_TYPE)
      && TYPE_MAIN_VARIANT (var_type) != var_type)
    C_TYPE_INCOMPLETE_VARS (var_type) = 0;
  ଫେରନ୍ତୁ var_type;
}

/* Build a VA_ARG_EXPR for the C parser.  */

ବୃକ୍ଷ
c_build_va_arg (location_t loc1, ବୃକ୍ଷ ପଦସମଷ୍ଟି, location_t loc2, ବୃକ୍ଷ type,
		ବୃକ୍ଷ type_ପଦସମଷ୍ଟି)
{
  ଯଦି (error_operand_p (type))
    ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
  /* VA_ARG_EXPR cannot be used for a scalar va_list with reverse storage
     order because it takes the address of the expression.  */
  ଅନ୍ୟଥା ଯଦି (handled_component_p (ପଦସମଷ୍ଟି)
	   && reverse_storage_order_for_component_p (ପଦସମଷ୍ଟି))
    {
      error_at (loc1, "cannot use %<va_arg%> with reverse storage order");
      ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
    }
  ଅନ୍ୟଥା ଯଦି (!COMPLETE_TYPE_P (type))
    {
      error_at (loc2, "second argument to %<va_arg%> is of incomplete "
		"type %qT", type);
      ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
    }
  ଅନ୍ୟଥା ଯଦି (ବୃକ୍ଷ_CODE (type) == FUNCTION_TYPE)
    {
      error_at (loc2, "second argument to %<va_arg%> is a function type %qT",
		type);
      ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
    }
  ଅନ୍ୟଥା ଯଦି (ବୃକ୍ଷ_CODE (type) == ARRAY_TYPE && C_TYPE_VARIABLE_SIZE (type)
	   && !flag_isoc99)
    {
      error_at (loc2, "second argument to %<va_arg%> is an array type %qT",
		type);
      ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
    }
  ଅନ୍ୟଥା ଯଦି (warn_cxx_compat && ବୃକ୍ଷ_CODE (type) == ENUMERAL_TYPE)
    warning_at (loc2, OPT_Wc___compat,
		"C++ requires promoted type, not enum type, in %<va_arg%>");

  ଯଦି (flag_isoc99 && ବୃକ୍ଷ_CODE (type) == ARRAY_TYPE)
    {
      warning_at (loc2, 0, "second argument to %<va_arg%> is an array type %qT",
		  type);
      /* We create a trap but evaluate side effects first.  */
      ବୃକ୍ଷ trapfn = builtin_decl_explicit (BUILT_IN_TRAP);
      trapfn = build_call_ପଦସମଷ୍ଟି_loc (loc2, trapfn, 0);
      ବୃକ୍ଷ e2 = build2 (COMPOUND_ପଦସମଷ୍ଟି, void_type_ଗଣ୍ଠି, ପଦସମଷ୍ଟି, trapfn);
      /* Return a compound literal of the right type.  */
      ବୃକ୍ଷ e1 = build_compound_literal (loc2, type, ଖାଲି, ସତ୍ୟ, 0, ଖାଲି);
      ପଦସମଷ୍ଟି = build2 (COMPOUND_ପଦସମଷ୍ଟି, type, e2, e1);
    }
  ଅନ୍ୟଥା
    ପଦସମଷ୍ଟି = build_va_arg (loc2, ପଦସମଷ୍ଟି, type);

  ଯଦି (type_ପଦସମଷ୍ଟି)
    ପଦସମଷ୍ଟି = build2 (COMPOUND_ପଦସମଷ୍ଟି, ବୃକ୍ଷ_TYPE (ପଦସମଷ୍ଟି), type_ପଦସମଷ୍ଟି, ପଦସମଷ୍ଟି);

  ଫେରନ୍ତୁ ପଦସମଷ୍ଟି;
}

/* Return truthvalue of whether T1 is the same tree structure as T2.
   Return 1 if they are the same. Return false if they are different.  */

ତାର୍କିକ
c_ବୃକ୍ଷ_equal (ବୃକ୍ଷ t1, ବୃକ୍ଷ t2)
{
  ଗଣନା ବୃକ୍ଷ_code code1, code2;

  ଯଦି (t1 == t2)
    ଫେରନ୍ତୁ ସତ୍ୟ;
  ଯଦି (!t1 || !t2)
    ଫେରନ୍ତୁ ମିଥ୍ୟା;

  ପାଇଁ (code1 = ବୃକ୍ଷ_CODE (t1); code1 == NON_LVALUE_ପଦସମଷ୍ଟି;
       code1 = ବୃକ୍ଷ_CODE (t1))
    t1 = ବୃକ୍ଷ_OPERAND (t1, 0);
  ପାଇଁ (code2 = ବୃକ୍ଷ_CODE (t2); code2 == NON_LVALUE_ପଦସମଷ୍ଟି;
       code2 = ବୃକ୍ଷ_CODE (t2))
    t2 = ବୃକ୍ଷ_OPERAND (t2, 0);

  /* They might have become equal now.  */
  ଯଦି (t1 == t2)
    ଫେରନ୍ତୁ ସତ୍ୟ;

  ଯଦି (code1 != code2)
    ଫେରନ୍ତୁ ମିଥ୍ୟା;

  ଯଦି (CONSTANT_CLASS_P (t1) && !comptypes (ବୃକ୍ଷ_TYPE (t1), ବୃକ୍ଷ_TYPE (t2)))
    ଫେରନ୍ତୁ ମିଥ୍ୟା;

  ବାଛ (code1)
    {
    ସ୍ଥିତି INTEGER_CST:
      ଫେରନ୍ତୁ wi::to_wide (t1) == wi::to_wide (t2);

    ସ୍ଥିତି REAL_CST:
      ଫେରନ୍ତୁ real_equal (&ବୃକ୍ଷ_REAL_CST (t1), &ବୃକ୍ଷ_REAL_CST (t2));

    ସ୍ଥିତି STRING_CST:
      ଫେରନ୍ତୁ ବୃକ୍ଷ_STRING_LENGTH (t1) == ବୃକ୍ଷ_STRING_LENGTH (t2)
	&& !memcmp (ବୃକ୍ଷ_STRING_POINTER (t1), ବୃକ୍ଷ_STRING_POINTER (t2),
		    ବୃକ୍ଷ_STRING_LENGTH (t1));

    ସ୍ଥିତି FIXED_CST:
      ଫେରନ୍ତୁ FIXED_ମୂଲ୍ୟଗୁଡ଼ିକ_IDENTICAL (ବୃକ୍ଷ_FIXED_CST (t1),
				     ବୃକ୍ଷ_FIXED_CST (t2));

    ସ୍ଥିତି COMPLEX_CST:
      ଫେରନ୍ତୁ c_ବୃକ୍ଷ_equal (ବୃକ୍ଷ_REALPART (t1), ବୃକ୍ଷ_REALPART (t2))
	     && c_ବୃକ୍ଷ_equal (ବୃକ୍ଷ_IMAGPART (t1), ବୃକ୍ଷ_IMAGPART (t2));

    ସ୍ଥିତି VECTOR_CST:
      ଫେରନ୍ତୁ operand_equal_p (t1, t2, OEP_ONLY_CONST);

    ସ୍ଥିତି CONSTRUCTOR:
      /* We need to do this when determining whether or not two
	 non-type pointer to member function template arguments
	 are the same.  */
      ଯଦି (!comptypes (ବୃକ୍ଷ_TYPE (t1), ବୃକ୍ଷ_TYPE (t2))
	  || CONSTRUCTOR_NELTS (t1) != CONSTRUCTOR_NELTS (t2))
	ଫେରନ୍ତୁ ମିଥ୍ୟା;
      {
	ବୃକ୍ଷ field, ମୂଲ୍ୟ;
	unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;
	FOR_EACH_CONSTRUCTOR_ELT (CONSTRUCTOR_ELTS (t1), i, field, ମୂଲ୍ୟ)
	  {
	    constructor_elt *elt2 = CONSTRUCTOR_ELT (t2, i);
	    ଯଦି (!c_ବୃକ୍ଷ_equal (field, elt2->index)
		|| !c_ବୃକ୍ଷ_equal (ମୂଲ୍ୟ, elt2->ମୂଲ୍ୟ))
	      ଫେରନ୍ତୁ ମିଥ୍ୟା;
	  }
      }
      ଫେରନ୍ତୁ ସତ୍ୟ;

    ସ୍ଥିତି ବୃକ୍ଷ_LIST:
      ଯଦି (!c_ବୃକ୍ଷ_equal (ବୃକ୍ଷ_PURPOSE (t1), ବୃକ୍ଷ_PURPOSE (t2)))
	ଫେରନ୍ତୁ ମିଥ୍ୟା;
      ଯଦି (!c_ବୃକ୍ଷ_equal (ବୃକ୍ଷ_ମୂଲ୍ୟ (t1), ବୃକ୍ଷ_ମୂଲ୍ୟ (t2)))
	ଫେରନ୍ତୁ ମିଥ୍ୟା;
      ଫେରନ୍ତୁ c_ବୃକ୍ଷ_equal (ବୃକ୍ଷ_CHAIN (t1), ବୃକ୍ଷ_CHAIN (t2));

    ସ୍ଥିତି SAVE_ପଦସମଷ୍ଟି:
      ଫେରନ୍ତୁ c_ବୃକ୍ଷ_equal (ବୃକ୍ଷ_OPERAND (t1, 0), ବୃକ୍ଷ_OPERAND (t2, 0));

    ସ୍ଥିତି CALL_ପଦସମଷ୍ଟି:
      {
	ବୃକ୍ଷ arg1, arg2;
	call_ପଦସମଷ୍ଟି_arg_iterator iter1, iter2;
	ଯଦି (!c_ବୃକ୍ଷ_equal (CALL_ପଦସମଷ୍ଟି_FN (t1), CALL_ପଦସମଷ୍ଟି_FN (t2)))
	  ଫେରନ୍ତୁ ମିଥ୍ୟା;
	ପାଇଁ (arg1 = first_call_ପଦସମଷ୍ଟି_arg (t1, &iter1),
	       arg2 = first_call_ପଦସମଷ୍ଟି_arg (t2, &iter2);
	     arg1 && arg2;
	     arg1 = next_call_ପଦସମଷ୍ଟି_arg (&iter1),
	       arg2 = next_call_ପଦସମଷ୍ଟି_arg (&iter2))
	  ଯଦି (!c_ବୃକ୍ଷ_equal (arg1, arg2))
	    ଫେରନ୍ତୁ ମିଥ୍ୟା;
	ଯଦି (arg1 || arg2)
	  ଫେରନ୍ତୁ ମିଥ୍ୟା;
	ଫେରନ୍ତୁ ସତ୍ୟ;
      }

    ସ୍ଥିତି TARGET_ପଦସମଷ୍ଟି:
      {
	ବୃକ୍ଷ o1 = ବୃକ୍ଷ_OPERAND (t1, 0);
	ବୃକ୍ଷ o2 = ବୃକ୍ଷ_OPERAND (t2, 0);

	/* Special case: if either target is an unallocated VAR_DECL,
	   it means that it's going to be unified with whatever the
	   TARGET_EXPR is really supposed to initialize, so treat it
	   as being equivalent to anything.  */
	ଯଦି (VAR_P (o1) && DECL_NAME (o1) == NULL_ବୃକ୍ଷ
	    && !DECL_RTL_SET_P (o1))
	  /*Nop*/;
	ଅନ୍ୟଥା ଯଦି (VAR_P (o2) && DECL_NAME (o2) == NULL_ବୃକ୍ଷ
		 && !DECL_RTL_SET_P (o2))
	  /*Nop*/;
	ଅନ୍ୟଥା ଯଦି (!c_ବୃକ୍ଷ_equal (o1, o2))
	  ଫେରନ୍ତୁ ମିଥ୍ୟା;

	ଫେରନ୍ତୁ c_ବୃକ୍ଷ_equal (ବୃକ୍ଷ_OPERAND (t1, 1), ବୃକ୍ଷ_OPERAND (t2, 1));
      }

    ସ୍ଥିତି COMPONENT_REF:
      ଯଦି (ବୃକ୍ଷ_OPERAND (t1, 1) != ବୃକ୍ଷ_OPERAND (t2, 1))
	ଫେରନ୍ତୁ ମିଥ୍ୟା;
      ଫେରନ୍ତୁ c_ବୃକ୍ଷ_equal (ବୃକ୍ଷ_OPERAND (t1, 0), ବୃକ୍ଷ_OPERAND (t2, 0));

    ସ୍ଥିତି PARM_DECL:
    ସ୍ଥିତି VAR_DECL:
    ସ୍ଥିତି CONST_DECL:
    ସ୍ଥିତି FIELD_DECL:
    ସ୍ଥିତି FUNCTION_DECL:
    ସ୍ଥିତି IDENTIFIER_ଗଣ୍ଠି:
    ସ୍ଥିତି SSA_NAME:
      ଫେରନ୍ତୁ ମିଥ୍ୟା;

    ସ୍ଥିତି ବୃକ୍ଷ_VEC:
      {
	unsigned ix;
	ଯଦି (ବୃକ୍ଷ_VEC_LENGTH (t1) != ବୃକ୍ଷ_VEC_LENGTH (t2))
	  ଫେରନ୍ତୁ ମିଥ୍ୟା;
	ପାଇଁ (ix = ବୃକ୍ଷ_VEC_LENGTH (t1); ix--;)
	  ଯଦି (!c_ବୃକ୍ଷ_equal (ବୃକ୍ଷ_VEC_ELT (t1, ix),
			     ବୃକ୍ଷ_VEC_ELT (t2, ix)))
	    ଫେରନ୍ତୁ ମିଥ୍ୟା;
	ଫେରନ୍ତୁ ସତ୍ୟ;
      }

    CASE_CONVERT:
      ଯଦି (!comptypes (ବୃକ୍ଷ_TYPE (t1), ବୃକ୍ଷ_TYPE (t2)))
	ଫେରନ୍ତୁ ମିଥ୍ୟା;
      ଭାଙ୍ଗ;

    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
      ଭାଙ୍ଗ;
    }

  ବାଛ (ବୃକ୍ଷ_CODE_CLASS (code1))
    {
    ସ୍ଥିତି tcc_unary:
    ସ୍ଥିତି tcc_ଦ୍ୱିମିକ:
    ସ୍ଥିତି tcc_comparison:
    ସ୍ଥିତି tcc_expression:
    ସ୍ଥିତି tcc_vl_exp:
    ସ୍ଥିତି tcc_reference:
    ସ୍ଥିତି tcc_statement:
      {
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା i, n = ବୃକ୍ଷ_OPERAND_LENGTH (t1);

	ବାଛ (code1)
	  {
	  ସ୍ଥିତି PREINCREMENT_ପଦସମଷ୍ଟି:
	  ସ୍ଥିତି PREDECREMENT_ପଦସମଷ୍ଟି:
	  ସ୍ଥିତି POSTINCREMENT_ପଦସମଷ୍ଟି:
	  ସ୍ଥିତି POSTDECREMENT_ପଦସମଷ୍ଟି:
	    n = 1;
	    ଭାଙ୍ଗ;
	  ସ୍ଥିତି ARRAY_REF:
	    n = 2;
	    ଭାଙ୍ଗ;
	  ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
	    ଭାଙ୍ଗ;
	  }

	ଯଦି (ବୃକ୍ଷ_CODE_CLASS (code1) == tcc_vl_exp
	    && n != ବୃକ୍ଷ_OPERAND_LENGTH (t2))
	  ଫେରନ୍ତୁ ମିଥ୍ୟା;

	ପାଇଁ (i = 0; i < n; ++i)
	  ଯଦି (!c_ବୃକ୍ଷ_equal (ବୃକ୍ଷ_OPERAND (t1, i), ବୃକ୍ଷ_OPERAND (t2, i)))
	    ଫେରନ୍ତୁ ମିଥ୍ୟା;

	ଫେରନ୍ତୁ ସତ୍ୟ;
      }

    ସ୍ଥିତି tcc_type:
      ଫେରନ୍ତୁ comptypes (t1, t2);
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
      gcc_unreachable ();
    }
}

/* Returns true when the function declaration FNDECL is implicit,
   introduced as a result of a call to an otherwise undeclared
   function, and false otherwise.  */

ତାର୍କିକ
c_decl_implicit (const_ବୃକ୍ଷ fndecl)
{
  ଫେରନ୍ତୁ C_DECL_IMPLICIT (fndecl);
}
