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

#અન્તર્ભાવ "config.h"
#અન્તર્ભાવ "system.h"
#અન્તર્ભાવ "coretypes.h"
#અન્તર્ભાવ "memmodel.h"
#અન્તર્ભાવ "target.h"
#અન્તર્ભાવ "function.h"
#અન્તર્ભાવ "bitmap.h"
#અન્તર્ભાવ "c-tree.h"
#અન્તર્ભાવ "gimple-expr.h"
#અન્તર્ભાવ "predict.h"
#અન્તર્ભાવ "stor-layout.h"
#અન્તર્ભાવ "trans-mem.h"
#અન્તર્ભાવ "varasm.h"
#અન્તર્ભાવ "stmt.h"
#અન્તર્ભાવ "langhooks.h"
#અન્તર્ભાવ "c-lang.h"
#અન્તર્ભાવ "intl.h"
#અન્તર્ભાવ "tree-iterator.h"
#અન્તર્ભાવ "gimplify.h"
#અન્તર્ભાવ "tree-inline.h"
#અન્તર્ભાવ "omp-general.h"
#અન્તર્ભાવ "c-family/c-objc.h"
#અન્તર્ભાવ "c-family/c-ubsan.h"
#અન્તર્ભાવ "gomp-constants.h"
#અન્તર્ભાવ "spellcheck-tree.h"
#અન્તર્ભાવ "c-family/c-type-mismatch.h"
#અન્તર્ભાવ "stringpool.h"
#અન્તર્ભાવ "attribs.h"
#અન્તર્ભાવ "asan.h"
#અન્તર્ભાવ "realmpfr.h"
#અન્તર્ભાવ "tree-pretty-print-markup.h"
#અન્તર્ભાવ "gcc-urlifier.h"

/* Possible cases of implicit conversions.  Used to select diagnostic messages
   and control folding initializers in convert_for_assignment.  */
ગણના impl_conv {
  ic_argpass,
  ic_assign,
  ic_init,
  ic_init_const,
  ic_return
};

/* The level of nesting inside "__alignof__".  */
પૂર્ણાંક in_alignof;

/* The level of nesting inside "sizeof".  */
પૂર્ણાંક in_sizeof;

/* The level of nesting inside "countof".  */
પૂર્ણાંક in_countof;

/* The level of nesting inside "typeof".  */
પૂર્ણાંક in_typeof;

/* The level of nesting inside "_Generic".  */
પૂર્ણાંક in_generic;

/* True when parsing OpenMP loop expressions.  */
તાર્કિક c_in_omp_for;

/* True when parsing OpenMP map clause.  */
તાર્કિક c_omp_array_section_p;

/* The argument of last parsed sizeof expression, only to be tested
   if expr.original_code == SIZEOF_EXPR.  */
વૃક્ષ c_last_sizeof_arg;
location_t c_last_sizeof_loc;

/* Nonzero if we might need to print a "missing braces around
   initializer" message within this initializer.  */
સ્થિર પૂર્ણાંક found_missing_braces;

સ્થિર તાર્કિક require_constant_કિંમત;
સ્થિર તાર્કિક require_constant_elements;
સ્થિર તાર્કિક require_constexpr_કિંમત;

સ્થિર વૃક્ષ qualify_type (વૃક્ષ, વૃક્ષ);
સંરચના comptypes_data;
સ્થિર તાર્કિક tagged_types_tu_compatible_p (const_વૃક્ષ, const_વૃક્ષ,
					  સંરચના comptypes_data *);
સ્થિર તાર્કિક comp_target_types (location_t, વૃક્ષ, વૃક્ષ);
સ્થિર તાર્કિક function_types_compatible_p (const_વૃક્ષ, const_વૃક્ષ,
					 સંરચના comptypes_data *);
સ્થિર તાર્કિક type_lists_compatible_p (const_વૃક્ષ, const_વૃક્ષ,
				     સંરચના comptypes_data *);
સ્થિર પૂર્ણાંક convert_arguments (location_t, vec<location_t>, વૃક્ષ,
			      vec<વૃક્ષ, va_gc> *, vec<વૃક્ષ, va_gc> *, વૃક્ષ,
			      વૃક્ષ);
સ્થિર વૃક્ષ pointer_diff (location_t, વૃક્ષ, વૃક્ષ, વૃક્ષ *);
સ્થિર વૃક્ષ convert_for_assignment (location_t, location_t, વૃક્ષ, વૃક્ષ, વૃક્ષ,
				    ગણના impl_conv, તાર્કિક, વૃક્ષ, વૃક્ષ, પૂર્ણાંક,
				    પૂર્ણાંક = 0);
સ્થિર વૃક્ષ valid_compound_પદાવલિ_initializer (વૃક્ષ, વૃક્ષ);
સ્થિર શૂન્ય ધકેલો_string (અચલ અક્ષર *);
સ્થિર શૂન્ય ધકેલો_member_name (વૃક્ષ);
સ્થિર પૂર્ણાંક spelling_length (શૂન્ય);
સ્થિર અક્ષર *print_spelling (અક્ષર *);
સ્થિર શૂન્ય warning_init (location_t, પૂર્ણાંક, અચલ અક્ષર *);
સ્થિર વૃક્ષ digest_init (location_t, વૃક્ષ, વૃક્ષ, વૃક્ષ, વૃક્ષ, તાર્કિક, તાર્કિક, તાર્કિક,
			 તાર્કિક, તાર્કિક, તાર્કિક);
સ્થિર શૂન્ય output_init_element (location_t, વૃક્ષ, વૃક્ષ, તાર્કિક, વૃક્ષ, વૃક્ષ, તાર્કિક,
				 તાર્કિક, સંરચના obstack *);
સ્થિર શૂન્ય output_pending_init_elements (પૂર્ણાંક, સંરચના obstack *);
સ્થિર તાર્કિક set_designator (location_t, તાર્કિક, સંરચના obstack *);
સ્થિર શૂન્ય ધકેલો_range_ઢગલો (વૃક્ષ, સંરચના obstack *);
સ્થિર શૂન્ય add_pending_init (location_t, વૃક્ષ, વૃક્ષ, વૃક્ષ, તાર્કિક,
			      સંરચના obstack *);
સ્થિર શૂન્ય set_nonincremental_init (સંરચના obstack *);
સ્થિર શૂન્ય set_nonincremental_init_from_string (વૃક્ષ, સંરચના obstack *);
સ્થિર વૃક્ષ find_init_member (વૃક્ષ, સંરચના obstack *);
સ્થિર શૂન્ય readonly_warning (વૃક્ષ, ગણના lvalue_use);
સ્થિર પૂર્ણાંક lvalue_or_else (location_t, const_વૃક્ષ, ગણના lvalue_use);
સ્થિર શૂન્ય record_maybe_used_decl (વૃક્ષ, તાર્કિક address);
સ્થિર તાર્કિક comptypes_internal (const_વૃક્ષ, const_વૃક્ષ,
				સંરચના comptypes_data *data);
સ્થિર તાર્કિક comptypes_check_for_composite (વૃક્ષ t1, વૃક્ષ t2);
સ્થિર તાર્કિક handle_counted_by_p (વૃક્ષ);
સ્થિર તાર્કિક ટોચ_array_vla_p (const_વૃક્ષ type);


/* Return true if EXP is a null pointer constant, false otherwise.  */

તાર્કિક
null_pointer_constant_p (const_વૃક્ષ પદાવલિ)
{
  /* This should really operate on c_expr structures, but they aren't
     yet available everywhere required.  */
  વૃક્ષ type = વૃક્ષ_TYPE (પદાવલિ);

  /* An integer constant expression with the value 0, such an expression
     cast to type void*, or the predefined constant nullptr, are a null
     pointer constant.  */
  જો (પદાવલિ == nullptr_ગાંઠ)
    પાછા સાચું;

  પાછા (વૃક્ષ_CODE (પદાવલિ) == INTEGER_CST
	  && !વૃક્ષ_OVERFLOW (પદાવલિ)
	  && integer_zerop (પદાવલિ)
	  && (INTEGRAL_TYPE_P (type)
	      || (વૃક્ષ_CODE (type) == POINTER_TYPE
		  && VOID_TYPE_P (વૃક્ષ_TYPE (type))
		  && TYPE_QUALS (વૃક્ષ_TYPE (type)) == TYPE_UNQUALIFIED)));
}

/* EXPR may appear in an unevaluated part of an integer constant
   expression, but not in an evaluated part.  Wrap it in a
   C_MAYBE_CONST_EXPR, or mark it with TREE_OVERFLOW if it is just an
   INTEGER_CST and we cannot create a C_MAYBE_CONST_EXPR.  */

સ્થિર વૃક્ષ
note_integer_operands (વૃક્ષ પદાવલિ)
{
  વૃક્ષ ret;
  જો (વૃક્ષ_CODE (પદાવલિ) == INTEGER_CST && in_late_દ્વિઅંકી_op)
    {
      ret = copy_ગાંઠ (પદાવલિ);
      વૃક્ષ_OVERFLOW (ret) = 1;
    }
  નહીંતર
    {
      ret = build2 (C_MAYBE_CONST_પદાવલિ, વૃક્ષ_TYPE (પદાવલિ), NULL_વૃક્ષ, પદાવલિ);
      C_MAYBE_CONST_પદાવલિ_INT_OPERANDS (ret) = 1;
    }
  પાછા ret;
}

/* Having checked whether EXPR may appear in an unevaluated part of an
   integer constant expression and found that it may, remove any
   C_MAYBE_CONST_EXPR noting this fact and return the resulting
   expression.  */

સ્થિર અંતઃરેખ વૃક્ષ
remove_c_maybe_const_પદાવલિ (વૃક્ષ પદાવલિ)
{
  જો (વૃક્ષ_CODE (પદાવલિ) == C_MAYBE_CONST_પદાવલિ)
    પાછા C_MAYBE_CONST_પદાવલિ_પદાવલિ (પદાવલિ);
  નહીંતર
    પાછા પદાવલિ;
}

/* This is a cache to hold if two types are seen.  */

સંરચના tagged_tu_seen_cache {
  અચલ સંરચના tagged_tu_seen_cache * next;
  const_વૃક્ષ t1;
  const_વૃક્ષ t2;
};

/* Do `exp = require_complete_type (loc, exp);' to make sure exp
   does not have an incomplete type.  (That includes void types.)
   LOC is the location of the use.  */

વૃક્ષ
require_complete_type (location_t loc, વૃક્ષ કિંમત)
{
  વૃક્ષ type = વૃક્ષ_TYPE (કિંમત);

  જો (error_operand_p (કિંમત))
    પાછા error_mark_ગાંઠ;

  /* First, detect a valid value with a complete type.  */
  જો (COMPLETE_TYPE_P (type))
    પાછા કિંમત;

  c_incomplete_type_error (loc, કિંમત, type);
  પાછા error_mark_ગાંઠ;
}

/* Print an error message for invalid use of an incomplete type.
   VALUE is the expression that was used (or 0 if that isn't known)
   and TYPE is the type that was invalid.  LOC is the location for
   the error.  */

શૂન્ય
c_incomplete_type_error (location_t loc, const_વૃક્ષ કિંમત, const_વૃક્ષ type)
{
  /* Avoid duplicate error message.  */
  જો (વૃક્ષ_CODE (type) == ERROR_MARK)
    પાછા;

  જો (કિંમત != NULL_વૃક્ષ && (VAR_P (કિંમત) || વૃક્ષ_CODE (કિંમત) == PARM_DECL))
    error_at (loc, "%qD has an incomplete type %qT", કિંમત, type);
  નહીંતર
    {
    retry:
      /* We must print an error message.  Be clever about what it says.  */

      પસંદગી (વૃક્ષ_CODE (type))
	{
	સ્થિતિ RECORD_TYPE:
	સ્થિતિ UNION_TYPE:
	સ્થિતિ ENUMERAL_TYPE:
	  તોડો;

	સ્થિતિ VOID_TYPE:
	  error_at (loc, "invalid use of void expression");
	  પાછા;

	સ્થિતિ ARRAY_TYPE:
	  જો (TYPE_DOMAIN (type))
	    {
	      જો (flexible_array_member_type_p (type))
		{
		  error_at (loc, "invalid use of flexible array member");
		  પાછા;
		}
	      type = વૃક્ષ_TYPE (type);
	      જાઓ retry;
	    }
	  error_at (loc, "invalid use of array with unspecified bounds");
	  પાછા;

	મૂળભૂત:
	  gcc_unreachable ();
	}

      જો (વૃક્ષ_CODE (TYPE_NAME (type)) == IDENTIFIER_ગાંઠ)
	error_at (loc, "invalid use of undefined type %qT", type);
      નહીંતર
	/* If this type has a typedef-name, the TYPE_NAME is a TYPE_DECL.  */
	error_at (loc, "invalid use of incomplete typedef %qT", type);
    }
}

/* Given a type, apply default promotions wrt unnamed function
   arguments and return the new type.  */

વૃક્ષ
c_type_promotes_to (વૃક્ષ type)
{
  વૃક્ષ ret = NULL_વૃક્ષ;

  જો (TYPE_MAIN_VARIANT (type) == float_type_ગાંઠ)
    ret = double_type_ગાંઠ;
  નહીંતર જો (c_promoting_integer_type_p (type))
    {
      /* Preserve unsignedness if not really getting any wider.  */
      જો (TYPE_UNSIGNED (type)
	  && (TYPE_PRECISION (type) == TYPE_PRECISION (integer_type_ગાંઠ)))
	ret = unsigned_type_ગાંઠ;
      નહીંતર
	ret = integer_type_ગાંઠ;
    }

  જો (ret != NULL_વૃક્ષ)
    પાછા (TYPE_ATOMIC (type)
	    ? c_build_qualified_type (ret, TYPE_QUAL_ATOMIC)
	    : ret);

  પાછા type;
}

/* Return true if between two named address spaces, whether there is a superset
   named address space that encompasses both address spaces.  If there is a
   superset, return which address space is the superset.  */

સ્થિર તાર્કિક
addr_space_superset (addr_space_t as1, addr_space_t as2, addr_space_t *common)
{
  જો (as1 == as2)
    {
      *common = as1;
      પાછા સાચું;
    }
  નહીંતર જો (targetm.addr_space.subset_p (as1, as2))
    {
      *common = as2;
      પાછા સાચું;
    }
  નહીંતર જો (targetm.addr_space.subset_p (as2, as1))
    {
      *common = as1;
      પાછા સાચું;
    }
  નહીંતર
    પાછા ખોટું;
}

/* Return a variant of TYPE which has all the type qualifiers of LIKE
   as well as those of TYPE.  */

સ્થિર વૃક્ષ
qualify_type (વૃક્ષ type, વૃક્ષ like)
{
  addr_space_t as_type = TYPE_ADDR_SPACE (type);
  addr_space_t as_like = TYPE_ADDR_SPACE (like);
  addr_space_t as_common;

  /* If the two named address spaces are different, determine the common
     superset address space.  If there isn't one, raise an error.  */
  જો (!addr_space_superset (as_type, as_like, &as_common))
    {
      as_common = as_type;
      error ("%qT and %qT are in disjoint named address spaces",
	     type, like);
    }

  પાછા c_build_qualified_type (type,
				 TYPE_QUALS_NO_ADDR_SPACE (type)
				 | TYPE_QUALS_NO_ADDR_SPACE_NO_ATOMIC (like)
				 | ENCODE_QUAL_ADDR_SPACE (as_common));
}


/* Check consistency of type TYPE.  For derived types, we test that
   C_TYPE_VARIABLE_SIZE and C_TYPE_VARIABLY_MODIFIED are consistent with
   the requirements of the base type.  We also check that arrays with a
   non-constant length are marked with C_TYPE_VARIABLE_SIZE. If any
   inconsistency is detected false is returned and true otherwise.  */

સ્થિર તાર્કિક
c_verify_type (વૃક્ષ type)
{
  પસંદગી (વૃક્ષ_CODE (type))
    {
    સ્થિતિ POINTER_TYPE:
    સ્થિતિ FUNCTION_TYPE:
    સ્થિતિ ARRAY_TYPE:
      /* Pointer, array, functions are variably modified if and only if the
	 target, element, return type is variably modified.  */
      જો (!TYPE_STRUCTURAL_EQUALITY_P (type)
	  && (C_TYPE_VARIABLY_MODIFIED (type)
	      != C_TYPE_VARIABLY_MODIFIED (વૃક્ષ_TYPE (type))))
	પાછા ખોટું;
      /* If the target type is structural equality, the type should also. */
      જો (!TYPE_STRUCTURAL_EQUALITY_P (type)
	  && TYPE_STRUCTURAL_EQUALITY_P (વૃક્ષ_TYPE (type)))
	પાછા ખોટું;
    મૂળભૂત:
       તોડો;
    }

  પસંદગી (વૃક્ષ_CODE (type))
    {
    સ્થિતિ POINTER_TYPE:
    સ્થિતિ FUNCTION_TYPE:
      /* Pointer and functions can not have variable size.  */
      જો (C_TYPE_VARIABLE_SIZE (type))
	પાછા ખોટું;
      તોડો;
    સ્થિતિ ARRAY_TYPE:
      /* An array has variable size if and only if it has a non-constant
	 dimensions or its element type has variable size.  */
      જો ((C_TYPE_VARIABLE_SIZE (વૃક્ષ_TYPE (type))
	   || ટોચ_array_vla_p (type))
	  != C_TYPE_VARIABLE_SIZE (type))
	પાછા ખોટું;
      /* If the element type or the array has variable size, then the
	 array has variable size and is variably modified.  */
      જો (C_TYPE_VARIABLE_SIZE (વૃક્ષ_TYPE (type))
	  || C_TYPE_VARIABLE_SIZE (type))
	{
	  જો (!C_TYPE_VARIABLE_SIZE (type))
	    પાછા ખોટું;
	  જો (!C_TYPE_VARIABLY_MODIFIED (type))
	    પાછા ખોટું;
	}

      /* va_list violates this, accept such types here.  */
      જો (!COMPLETE_TYPE_P (વૃક્ષ_TYPE (type)))
	પાછા સાચું;

      જો (COMPLETE_TYPE_P (type))
	{
	  /* If the size is unknown, it can not be complete.  */
	  જો (NULL_વૃક્ષ == TYPE_DOMAIN (type))
	    પાછા ખોટું;

	  /* Zero-length arrays must have size zero.  */
	  જો (zero_length_array_type_p (type)
	      && !integer_zerop (TYPE_SIZE (type)))
	    પાછા ખોટું;
	}
      નહીંતર
	{
	  /* If not complete but has a domain, it must be a FAM.  */
	  જો (NULL_વૃક્ષ != TYPE_DOMAIN (type)
	      && !flexible_array_member_type_p (type))
	    પાછા ખોટું;
	}
    મૂળભૂત:
      તોડો;
    }
  પાછા સાચું;
}

/* Propagate C_TYPE_VARIABLY_MODIFIED and C_TYPE_VARIABLE_SIZE
   from a base type to a newly built derived or qualified type.  */

સ્થિર વૃક્ષ
c_set_type_bits (વૃક્ષ new_type, વૃક્ષ old_type)
{
  gcc_checking_assert (c_verify_type (old_type));

  જો (c_type_variably_modified_p (old_type))
    C_TYPE_VARIABLY_MODIFIED (new_type) = સાચું;

  જો (વૃક્ષ_CODE (new_type) == ARRAY_TYPE && C_TYPE_VARIABLE_SIZE (old_type))
    {
      C_TYPE_VARIABLY_MODIFIED (new_type) = સાચું;
      C_TYPE_VARIABLE_SIZE (new_type) = સાચું;
    }
  પાછા new_type;
}

/* Build a pointer type using the default pointer mode.  */

વૃક્ષ
c_build_pointer_type (વૃક્ષ to_type)
{
  addr_space_t as = to_type == error_mark_ગાંઠ ? ADDR_SPACE_GENERIC
					       : TYPE_ADDR_SPACE (to_type);
  machine_mode pointer_mode;

  જો (as != ADDR_SPACE_GENERIC || c_default_pointer_mode == VOIDmode)
    pointer_mode = targetm.addr_space.pointer_mode (as);
  નહીંતર
    pointer_mode = c_default_pointer_mode;

  પાછા c_build_pointer_type_for_mode (to_type, pointer_mode, ખોટું);
}

/* Build a pointer type using the given mode.  */

વૃક્ષ
c_build_pointer_type_for_mode (વૃક્ષ type, machine_mode mode, તાર્કિક m)
{
  વૃક્ષ ret = build_pointer_type_for_mode (type, mode, m);
  પાછા c_set_type_bits (ret, type);
}

/* Build a function type.  */

વૃક્ષ
c_build_function_type (વૃક્ષ type, વૃક્ષ args, તાર્કિક no)
{
  વૃક્ષ ret = build_function_type (type, args, no);
  પાછા c_set_type_bits (ret, type);
}

/* Build an array type.  This sets typeless storage as required
   by C2Y and C_TYPE_VARIABLY_MODIFIED and C_TYPE_VARIABLE_SIZE
   based on the element type and domain.  */

વૃક્ષ
c_build_array_type (વૃક્ષ type, વૃક્ષ domain)
{
  પૂર્ણાંક type_quals = TYPE_QUALS (type);

  /* Identify typeless storage as introduced in C2Y
     and supported also in earlier language modes.  */
  તાર્કિક typeless = (char_type_p (type) && !(type_quals & TYPE_QUAL_ATOMIC))
		  || (AGGREGATE_TYPE_P (type) && TYPE_TYPELESS_STORAGE (type));

  વૃક્ષ ret = build_array_type (type, domain, typeless);

  જો (ટોચ_array_vla_p (ret))
    {
      C_TYPE_VARIABLE_SIZE (ret) = 1;
      C_TYPE_VARIABLY_MODIFIED (ret) = 1;
    }

  પાછા c_set_type_bits (ret, type);
}

/* Build an array type of unspecified size.  */
વૃક્ષ
c_build_array_type_unspecified (વૃક્ષ type)
{
  વૃક્ષ upper = build2 (COMPOUND_પદાવલિ, વૃક્ષ_TYPE (size_zero_ગાંઠ),
		       integer_zero_ગાંઠ, size_zero_ગાંઠ);
  પાછા c_build_array_type (type, build_index_type (upper));
}

/* Build an array type of zero size.  */
વૃક્ષ
c_build_array_type_zero_size (વૃક્ષ type)
{
  /* The GCC extension for zero-length arrays differs from
     ISO flexible array members in that sizeof yields
     zero.  */
  type = c_build_array_type (type, build_index_type (NULL_વૃક્ષ));
  type = build_distinct_type_copy (TYPE_MAIN_VARIANT (type));
  TYPE_SIZE (type) = bitsize_zero_ગાંઠ;
  TYPE_SIZE_UNIT (type) = size_zero_ગાંઠ;
  SET_TYPE_STRUCTURAL_EQUALITY (type);
  પાછા type;
}

વૃક્ષ
c_build_type_attribute_qual_variant (વૃક્ષ type, વૃક્ષ attrs, પૂર્ણાંક quals)
{
  વૃક્ષ ret = build_type_attribute_qual_variant (type, attrs, quals);
  પાછા c_set_type_bits (ret, type);
}

વૃક્ષ
c_build_type_attribute_variant (વૃક્ષ type, વૃક્ષ attrs)
{
  પાછા c_build_type_attribute_qual_variant (type, attrs, TYPE_QUALS (type));
}

/* Reconstruct a complex derived type.  This is used to re-construct types
   with the vector attribute.  It is called via a langhook.  */

વૃક્ષ
c_reconstruct_complex_type (વૃક્ષ type, વૃક્ષ bottom)
{
  વૃક્ષ inner, outer;

  જો (વૃક્ષ_CODE (type) == POINTER_TYPE)
    {
      inner = c_reconstruct_complex_type (વૃક્ષ_TYPE (type), bottom);
      outer = c_build_pointer_type_for_mode (inner, TYPE_MODE (type),
					     TYPE_REF_CAN_ALIAS_ALL (type));
    }
  નહીંતર જો (વૃક્ષ_CODE (type) == ARRAY_TYPE)
    {
      તાર્કિક rso = TYPE_REVERSE_STORAGE_ORDER (type);
      inner = c_reconstruct_complex_type (વૃક્ષ_TYPE (type), bottom);
      outer = c_build_array_type (inner, TYPE_DOMAIN (type));
      જો (rso)
	{
	  outer = build_distinct_type_copy (outer);
	  TYPE_REVERSE_STORAGE_ORDER (outer) = 1;
	}

      gcc_checking_assert (C_TYPE_VARIABLE_SIZE (type)
			   == C_TYPE_VARIABLE_SIZE (outer));
    }
  નહીંતર જો (વૃક્ષ_CODE (type) == FUNCTION_TYPE)
    {
      inner = c_reconstruct_complex_type (વૃક્ષ_TYPE (type), bottom);
      outer = c_build_function_type (inner, TYPE_ARG_TYPES (type),
				     TYPE_NO_NAMED_ARGS_STDARG_P (type));
    }
  નહીંતર જો (વૃક્ષ_CODE (type) == REFERENCE_TYPE
	   || વૃક્ષ_CODE (type) == OFFSET_TYPE)
    gcc_unreachable ();
  નહીંતર
    પાછા bottom;

  પાછા c_build_type_attribute_qual_variant (outer, TYPE_ATTRIBUTES (type),
					      TYPE_QUALS (type));
}


/* Helper function for c_canonical_type.  Check whether FIELD
   contains a pointer to a structure or union with tag,
   possibly nested in other type derivations, and return the
   type of this nested structure or union.  */
સ્થિર વૃક્ષ
ptr_to_tagged_member (વૃક્ષ field)
{
  gcc_assert (FIELD_DECL == વૃક્ષ_CODE (field));
  વૃક્ષ type = વૃક્ષ_TYPE (field);
  તાર્કિક ptr_seen = ખોટું;
  જ્યારે (વૃક્ષ_CODE (type) == ARRAY_TYPE
	 || વૃક્ષ_CODE (type) == FUNCTION_TYPE
	 || વૃક્ષ_CODE (type) == POINTER_TYPE)
    {
      જો (વૃક્ષ_CODE (type) == POINTER_TYPE)
	ptr_seen = સાચું;
      type = વૃક્ષ_TYPE (type);
    }

  જો (ptr_seen
      && RECORD_OR_UNION_TYPE_P (type)
      && NULL_વૃક્ષ != c_type_tag (type))
    પાછા type;

  પાછા NULL_વૃક્ષ;
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
વૃક્ષ
c_type_canonical (વૃક્ષ type)
{
  gcc_assert (RECORD_OR_UNION_TYPE_P (type));

  તાર્કિક needs_mod = ખોટું;
  માટે (વૃક્ષ x = TYPE_FIELDS (type); x; x = DECL_CHAIN (x))
    {
      જો (!ptr_to_tagged_member (x))
	ચાલુ;
      needs_mod = સાચું;
      તોડો;
    }
  જો (!needs_mod)
    પાછા type;

  /* Construct new version with such members replaced.  */
  વૃક્ષ n = build_distinct_type_copy (type);
  વૃક્ષ *fields = &TYPE_FIELDS (n);
  માટે (વૃક્ષ x = TYPE_FIELDS (type); x; x = DECL_CHAIN (x))
    {
      વૃક્ષ f = copy_ગાંઠ (x);
      જો (વૃક્ષ m = ptr_to_tagged_member (x))
	{
	  વૃક્ષ new_ગાંઠ = make_ગાંઠ (વૃક્ષ_CODE (m));
	  TYPE_NAME (new_ગાંઠ) = TYPE_NAME (m);
	  SET_TYPE_STRUCTURAL_EQUALITY (new_ગાંઠ);
	  new_ગાંઠ = qualify_type (new_ગાંઠ, m);
	  વૃક્ષ_TYPE (f) = c_reconstruct_complex_type (વૃક્ષ_TYPE (x),
						      new_ગાંઠ);
	}
      *fields = f;
      fields = &DECL_CHAIN (f);
    }
  TYPE_CANONICAL (n) = n;
  પાછા n;
}


/* If NTYPE is a type of a non-variadic function with a prototype
   and OTYPE is a type of a function without a prototype and ATTRS
   contains attribute format, diagnosess and removes it from ATTRS.
   Returns the result of build_type_attribute_variant of NTYPE and
   the (possibly) modified ATTRS.  */

સ્થિર વૃક્ષ
c_build_functype_attribute_variant (વૃક્ષ ntype, વૃક્ષ otype, વૃક્ષ attrs)
{
  જો (!prototype_p (otype)
      && prototype_p (ntype)
      && lookup_attribute ("format", attrs))
    {
      warning_at (આગત_location, OPT_Wattributes,
		  "%qs attribute can only be applied to variadic functions",
		  "format");
      attrs = remove_attribute ("format", attrs);
    }
  પાછા c_build_type_attribute_variant (ntype, attrs);

}

/* Given a type which could be a typedef name, make sure to return the
   original type.  See set_underlying_type. */
સ્થિર const_વૃક્ષ
c_type_original (const_વૃક્ષ t)
{
  /* It may even be a typedef of a typedef...
     In the case of compiler-created builtin structs the TYPE_DECL
     may be a dummy, with no DECL_ORIGINAL_TYPE.  Don't fault.  */
  જ્યારે (TYPE_NAME (t)
	 && વૃક્ષ_CODE (TYPE_NAME (t)) == TYPE_DECL
	 && DECL_ORIGINAL_TYPE (TYPE_NAME (t)))
    t = DECL_ORIGINAL_TYPE (TYPE_NAME (t));
  પાછા t;
}

/* Return the tag for a tagged type.  */
વૃક્ષ
c_type_tag (const_વૃક્ષ t)
{
  gcc_assert (RECORD_OR_UNION_TYPE_P (t) || વૃક્ષ_CODE (t) == ENUMERAL_TYPE);
  const_વૃક્ષ orig = c_type_original (t);
  વૃક્ષ name = TYPE_NAME (orig);
  જો (!name)
    પાછા NULL_વૃક્ષ;
  જો (વૃક્ષ_CODE (name) == TYPE_DECL)
    {
      જો (!DECL_NAME (name))
	પાછા NULL_વૃક્ષ;
      name = DECL_NAME (name);
    }
  gcc_checking_assert (વૃક્ષ_CODE (name) == IDENTIFIER_ગાંઠ);
  પાછા name;
}

/* Remove qualifiers but not atomic.  For arrays remove qualifiers
   on the element type but also do not remove atomic.  */
સ્થિર વૃક્ષ
remove_qualifiers (વૃક્ષ t)
{
  જો (!t || t == error_mark_ગાંઠ)
    પાછા t;
  પાછા TYPE_ATOMIC (strip_array_types (t))
	 ? c_build_qualified_type (TYPE_MAIN_VARIANT (t), TYPE_QUAL_ATOMIC)
	 : TYPE_MAIN_VARIANT (t);
}


/* Helper function for composite_type_internal.  Find a compatible type
   in a (transparent) union U compatible to T.  If found, return the
   type of the corresponding member.  Otherwise, return the union type U.  */
સ્થિર વૃક્ષ
transparent_union_replacement (વૃક્ષ u, વૃક્ષ t)
{
  જો (u == error_mark_ગાંઠ || t == error_mark_ગાંઠ
      || વૃક્ષ_CODE (u) != UNION_TYPE
      || !(TYPE_TRANSPARENT_AGGR (u) || TYPE_NAME (u) == NULL_વૃક્ષ)
      || comptypes (u, t))
    પાછા u;

  માટે (વૃક્ષ memb = TYPE_FIELDS (u); memb; memb = DECL_CHAIN (memb))
    {
      વૃક્ષ m = remove_qualifiers (વૃક્ષ_TYPE (memb));
      જો (comptypes (m, t))
	{
	  pedwarn (આગત_location, OPT_Wpedantic,
		    "function types not truly compatible in ISO C");
	  પાછા m;
	}
    }

  પાછા u;
}



/* Return the composite type of two compatible types.

   We assume that comptypes has already been done and returned
   nonzero; if that isn't so, this may crash.  In particular, we
   assume that qualifiers match.  */

સંરચના composite_cache {
  વૃક્ષ t1;
  વૃક્ષ t2;
  વૃક્ષ composite;
  સંરચના composite_cache* next;
};

વૃક્ષ
composite_type_internal (વૃક્ષ t1, વૃક્ષ t2, વૃક્ષ cond,
			 સંરચના composite_cache* cache)
{
  ગણના વૃક્ષ_code code1;
  ગણના વૃક્ષ_code code2;
  વૃક્ષ attributes;

  /* Save time if the two types are the same.  */

  જો (t1 == t2) પાછા t1;

  /* If one type is nonsense, use the other.  */
  જો (t1 == error_mark_ગાંઠ)
    પાછા t2;
  જો (t2 == error_mark_ગાંઠ)
    પાછા t1;

  code1 = વૃક્ષ_CODE (t1);
  code2 = વૃક્ષ_CODE (t2);

  /* Merge the attributes.  */
  attributes = targetm.merge_type_attributes (t1, t2);

  /* If one is an enumerated type and the other is the compatible
     integer type, the composite type might be either of the two
     (DR#013 question 3).  For consistency, use the enumerated type as
     the composite type.  */

  જો (code1 == ENUMERAL_TYPE
      && (code2 == INTEGER_TYPE
	  || code2 == BOOLEAN_TYPE))
    પાછા t1;
  જો (code2 == ENUMERAL_TYPE
      && (code1 == INTEGER_TYPE
	  || code1 == BOOLEAN_TYPE))
    પાછા t2;

  gcc_assert (code1 == code2);

  પસંદગી (code1)
    {
    સ્થિતિ POINTER_TYPE:
      /* For two pointers, do this recursively on the target type.  */
      {
	gcc_checking_assert (TYPE_QUALS (t1) == TYPE_QUALS (t2));
	વૃક્ષ target = composite_type_internal (વૃક્ષ_TYPE (t1), વૃક્ષ_TYPE (t2),
					       cond, cache);
	વૃક્ષ n = c_build_pointer_type_for_mode (target, TYPE_MODE (t1), ખોટું);
	પાછા c_build_type_attribute_qual_variant (n, attributes,
						    TYPE_QUALS (t2));
      }

    સ્થિતિ ARRAY_TYPE:
      {
	વૃક્ષ d1 = TYPE_DOMAIN (t1);
	વૃક્ષ d2 = TYPE_DOMAIN (t2);

	/* We should not have any type quals on arrays at all.  */
	gcc_assert (!TYPE_QUALS_NO_ADDR_SPACE (t1)
		    && !TYPE_QUALS_NO_ADDR_SPACE (t2));

	તાર્કિક d1_zero = zero_length_array_type_p (t1)
		       || flexible_array_member_type_p (t1);
	તાર્કિક d2_zero = zero_length_array_type_p (t2)
		       || flexible_array_member_type_p (t2);

	તાર્કિક d1_variable = ટોચ_array_vla_p (t1);
	તાર્કિક d2_variable = ટોચ_array_vla_p (t2);

	તાર્કિક use1 = d1 && (d2_variable || !d2 || d2_zero || !d1_variable);
	તાર્કિક use2 = d2 && (d1_variable || !d1 || d1_zero || !d2_variable);

	/* If the first is an unspecified size pick the other one.  */
	જો (d2_variable && c_type_unspecified_p (t1))
	  {
	    gcc_assert (use1 && use2);
	    use1 = ખોટું;
	  }

	/* If both are VLAs but not unspecified and we are in the
	   conditional operator, we create a conditional to select
	   the size of the active branch.  */
	તાર્કિક use0 = cond && d1_variable && !c_type_unspecified_p (t1)
			 && d2_variable && !c_type_unspecified_p (t2);

	વૃક્ષ td;
	વૃક્ષ elt = composite_type_internal (વૃક્ષ_TYPE (t1), વૃક્ષ_TYPE (t2),
					    cond, cache);

	જો (!use0)
	  {
	    /* Save space: see if the result is identical to one of the args.  */
	    જો (elt == વૃક્ષ_TYPE (t1) && use1)
	      પાછા c_build_type_attribute_variant (t1, attributes);
	    જો (elt == વૃક્ષ_TYPE (t2) && use2)
	      પાછા c_build_type_attribute_variant (t2, attributes);

	    જો (elt == વૃક્ષ_TYPE (t1) && !TYPE_DOMAIN (t2) && !TYPE_DOMAIN (t1))
	      પાછા c_build_type_attribute_variant (t1, attributes);
	    જો (elt == વૃક્ષ_TYPE (t2) && !TYPE_DOMAIN (t2) && !TYPE_DOMAIN (t1))
	      પાછા c_build_type_attribute_variant (t2, attributes);

	    td = TYPE_DOMAIN (use1 ? t1 : t2);
	  }
	નહીંતર
	  {
	    /* Not used in C.  */
	    gcc_assert (size_zero_ગાંઠ == TYPE_MIN_કિંમત (d1));
	    gcc_assert (size_zero_ગાંઠ == TYPE_MIN_કિંમત (d2));

	    વૃક્ષ d = fold_build3_loc (UNKNOWN_LOCATION, COND_પદાવલિ, sizetype,
				      cond, TYPE_MAX_કિંમત (d1),
				      TYPE_MAX_કિંમત (d2));

	    td = build_index_type (d);
	  }

	/* Merge the element types, and have a size if either arg has
	   one.  We may have qualifiers on the element types.  To set
	   up TYPE_MAIN_VARIANT correctly, we need to form the
	   composite of the unqualified types and add the qualifiers
	   back at the end.  */
	પૂર્ણાંક quals = TYPE_QUALS (strip_array_types (elt));
	વૃક્ષ unqual_elt = c_build_qualified_type (elt, TYPE_UNQUALIFIED);

	જો ((!d1 || d1_zero) && (!d2 || d2_zero) && (d1 || d2))
	  t1 = c_build_array_type_zero_size (unqual_elt);
	નહીંતર
	  t1 = c_build_array_type (unqual_elt, td);

	/* Check that a type which has a varying outermost dimension
	   got marked as having a variable size.  */
	તાર્કિક varsize = (d1_variable && d2_variable)
		       || (d1_variable && !d2)
		       || (d2_variable && !d1);
	gcc_checking_assert (!varsize || C_TYPE_VARIABLE_SIZE (t1));

	t1 = c_build_qualified_type (t1, quals);
	પાછા c_build_type_attribute_variant (t1, attributes);
      }

    સ્થિતિ RECORD_TYPE:
    સ્થિતિ UNION_TYPE:
      જો (flag_isoc23 && !comptypes_same_p (t1, t2))
	{
	  /* Go to the original type to get the right tag.  */
	  વૃક્ષ tag = c_type_tag (t1);

	  gcc_checking_assert (COMPLETE_TYPE_P (t1) && COMPLETE_TYPE_P (t2));
	  gcc_checking_assert (!tag || comptypes (t1, t2));

	  /* If a composite type for these two types is already under
	     construction, return it.  */

	  માટે (સંરચના composite_cache *c = cache; c != ખાલી; c = c->next)
	    જો ((c->t1 == t1 && c->t2 == t2) || (c->t1 == t2 && c->t2 == t1))
	       પાછા c->composite;

	  /* Otherwise, create a new type node and link it into the cache.  */

	  વૃક્ષ n = make_ગાંઠ (code1);
	  SET_TYPE_STRUCTURAL_EQUALITY (n);
	  TYPE_NAME (n) = tag;

	  સંરચના composite_cache cache2 = { t1, t2, n, cache };
	  cache = &cache2;

	  વૃક્ષ f1 = TYPE_FIELDS (t1);
	  વૃક્ષ f2 = TYPE_FIELDS (t2);
	  વૃક્ષ fields = NULL_વૃક્ષ;

	  માટે (વૃક્ષ a = f1, b = f2; a && b;
	       a = DECL_CHAIN (a), b = DECL_CHAIN (b))
	    {
	      વૃક્ષ ta = વૃક્ષ_TYPE (a);
	      વૃક્ષ tb = વૃક્ષ_TYPE (b);

	      જો (DECL_C_BIT_FIELD (a))
		{
		  ta = DECL_BIT_FIELD_TYPE (a);
		  tb = DECL_BIT_FIELD_TYPE (b);
		}

	      gcc_assert (DECL_NAME (a) == DECL_NAME (b));
	      gcc_checking_assert (!DECL_NAME (a) || comptypes (ta, tb));

	      વૃક્ષ t = composite_type_internal (ta, tb, cond, cache);
	      વૃક્ષ f = build_decl (આગત_location, FIELD_DECL, DECL_NAME (a), t);

	      DECL_PACKED (f) = DECL_PACKED (a);
	      SET_DECL_ALIGN (f, DECL_ALIGN (a));
	      DECL_ATTRIBUTES (f) = DECL_ATTRIBUTES (a);
	      C_DECL_VARIABLE_SIZE (f) = C_TYPE_VARIABLE_SIZE (t);

	      decl_attributes (&f, DECL_ATTRIBUTES (f), 0);

	      finish_decl (f, આગત_location, ખાલી, ખાલી, ખાલી);

	      જો (DECL_C_BIT_FIELD (a))
		{
		  /* This will be processed by finish_struct.  */
		  SET_DECL_C_BIT_FIELD (f);
		  DECL_INITIAL (f) = build_int_cst (integer_type_ગાંઠ,
						    વૃક્ષ_to_uhwi (DECL_SIZE (a)));
		  DECL_NONADDRESSABLE_P (f) = સાચું;
		  DECL_PADDING_P (f) = !DECL_NAME (a);
		}

	      DECL_CHAIN (f) = fields;
	      fields = f;
	    }

	  fields = nreverse (fields);

	  /* Setup the struct/union type.  Because we inherit all variably
	     modified components, we can ignore the size expression.  */
	  વૃક્ષ પદાવલિ = NULL_વૃક્ષ;

	  /* Set TYPE_STUB_DECL for debugging symbols.  */
	  TYPE_STUB_DECL (n) = pushdecl (build_decl (આગત_location, TYPE_DECL,
						     NULL_વૃક્ષ, n));

	  n = finish_struct (આગત_location, n, fields, attributes, ખાલી,
			     &પદાવલિ);

	  પાછા qualify_type (n, t1);
	}
      /* FALLTHRU */
    સ્થિતિ ENUMERAL_TYPE:
      જો (attributes != ખાલી)
	{
	  /* Try harder not to create a new aggregate type.  */
	  જો (attribute_list_equal (TYPE_ATTRIBUTES (t1), attributes))
	    પાછા t1;
	  જો (attribute_list_equal (TYPE_ATTRIBUTES (t2), attributes))
	    પાછા t2;
	}
      પાછા c_build_type_attribute_variant (t1, attributes);

    સ્થિતિ FUNCTION_TYPE:
      /* Function types: prefer the one that specified arg types.
	 If both do, merge the arg types.  Also merge the return types.  */
      {
	વૃક્ષ valtype = composite_type_internal (વૃક્ષ_TYPE (t1), વૃક્ષ_TYPE (t2),
						cond, cache);
	વૃક્ષ p1 = TYPE_ARG_TYPES (t1);
	વૃક્ષ p2 = TYPE_ARG_TYPES (t2);

	/* Save space: see if the result is identical to one of the args.  */
	જો (valtype == વૃક્ષ_TYPE (t1) && !TYPE_ARG_TYPES (t2))
	  પાછા c_build_functype_attribute_variant (t1, t2, attributes);
	જો (valtype == વૃક્ષ_TYPE (t2) && !TYPE_ARG_TYPES (t1))
	  પાછા c_build_functype_attribute_variant (t2, t1, attributes);

	/* Simple way if one arg fails to specify argument types.  */
	જો (TYPE_ARG_TYPES (t1) == NULL_વૃક્ષ)
	  {
	    t1 = c_build_function_type (valtype, TYPE_ARG_TYPES (t2),
					TYPE_NO_NAMED_ARGS_STDARG_P (t2));
	    t1 = c_build_type_attribute_variant (t1, attributes);
	    પાછા qualify_type (t1, t2);
	 }
	જો (TYPE_ARG_TYPES (t2) == NULL_વૃક્ષ)
	  {
	    t1 = c_build_function_type (valtype, TYPE_ARG_TYPES (t1),
					TYPE_NO_NAMED_ARGS_STDARG_P (t1));
	    t1 = c_build_type_attribute_variant (t1, attributes);
	    પાછા qualify_type (t1, t2);
	  }

	/* If both args specify argument types, we must merge the two
	   lists, argument by argument.  */
	વૃક્ષ newargs = NULL_વૃક્ષ;
	વૃક્ષ *endp = &newargs;

	માટે (; p1; p1 = વૃક્ષ_CHAIN (p1), p2 = વૃક્ષ_CHAIN (p2))
	  {
	    જો (p1 == void_list_ગાંઠ)
	      {
		*endp = void_list_ગાંઠ;
		તોડો;
	      }
	    વૃક્ષ mv1 = remove_qualifiers (વૃક્ષ_કિંમત (p1));
	    વૃક્ષ mv2 = remove_qualifiers (વૃક્ષ_કિંમત (p2));

	    gcc_assert (mv1);
	    gcc_assert (mv2);

	    mv1 = transparent_union_replacement (mv1, mv2);
	    mv2 = transparent_union_replacement (mv2, mv1);

	    *endp = વૃક્ષ_cons (NULL_વૃક્ષ,
			       composite_type_internal (mv1, mv2, cond, cache),
			       NULL_વૃક્ષ);

	    endp = &વૃક્ષ_CHAIN (*endp);
	  }

	t1 = c_build_function_type (valtype, newargs);
	t1 = qualify_type (t1, t2);
      }
      /* FALLTHRU */

    મૂળભૂત:
      પાછા c_build_type_attribute_variant (t1, attributes);
    }
}

વૃક્ષ
composite_type_cond (વૃક્ષ t1, વૃક્ષ t2, વૃક્ષ cond)
{
  gcc_checking_assert (comptypes_check_for_composite (t1, t2));

  સંરચના composite_cache cache = { };
  વૃક્ષ n = composite_type_internal (t1, t2, cond, &cache);

  gcc_checking_assert (comptypes_check_for_composite (n, t1));
  gcc_checking_assert (comptypes_check_for_composite (n, t2));
  પાછા n;
}


વૃક્ષ
composite_type (વૃક્ષ t1, વૃક્ષ t2)
{
  પાછા composite_type_cond (t1, t2, NULL_વૃક્ષ);
}

/* Return the type of a conditional expression between pointers to
   possibly differently qualified versions of compatible types.

   We assume that comp_target_types has already been done and returned
   true; if that isn't so, this may crash.  */

સ્થિર વૃક્ષ
common_pointer_type (વૃક્ષ t1, વૃક્ષ t2, વૃક્ષ cond)
{
  વૃક્ષ attributes;
  unsigned target_quals;
  addr_space_t as1, as2, as_common;
  પૂર્ણાંક quals1, quals2;

  /* Save time if the two types are the same.  */

  જો (t1 == t2) પાછા t1;

  /* If one type is nonsense, use the other.  */
  જો (t1 == error_mark_ગાંઠ)
    પાછા t2;
  જો (t2 == error_mark_ગાંઠ)
    પાછા t1;

  gcc_assert (વૃક્ષ_CODE (t1) == POINTER_TYPE
	      && વૃક્ષ_CODE (t2) == POINTER_TYPE);

  /* Merge the attributes.  */
  attributes = targetm.merge_type_attributes (t1, t2);

  /* Find the composite type of the target types, and combine the
     qualifiers of the two types' targets.  */
  વૃક્ષ pointed_to_1 = વૃક્ષ_TYPE (t1);
  વૃક્ષ pointed_to_2 = વૃક્ષ_TYPE (t2);
  વૃક્ષ target = composite_type_cond (TYPE_MAIN_VARIANT (pointed_to_1),
				     TYPE_MAIN_VARIANT (pointed_to_2), cond);

  /* Strip array types to get correct qualifier for pointers to arrays */
  quals1 = TYPE_QUALS_NO_ADDR_SPACE (strip_array_types (pointed_to_1));
  quals2 = TYPE_QUALS_NO_ADDR_SPACE (strip_array_types (pointed_to_2));

  /* For function types do not merge const qualifiers, but drop them
     if used inconsistently.  The middle-end uses these to mark const
     and noreturn functions.  */
  જો (વૃક્ષ_CODE (pointed_to_1) == FUNCTION_TYPE)
    target_quals = (quals1 & quals2);
  નહીંતર
    target_quals = (quals1 | quals2);

  /* If the two named address spaces are different, determine the common
     superset address space.  This is guaranteed to exist due to the
     assumption that comp_target_type returned true.  */
  as1 = TYPE_ADDR_SPACE (pointed_to_1);
  as2 = TYPE_ADDR_SPACE (pointed_to_2);
  જો (!addr_space_superset (as1, as2, &as_common))
    gcc_unreachable ();

  target_quals |= ENCODE_QUAL_ADDR_SPACE (as_common);

  t1 = c_build_pointer_type (c_build_qualified_type (target, target_quals));
  પાછા c_build_type_attribute_variant (t1, attributes);
}

/* Return the common type for two arithmetic types under the usual
   arithmetic conversions.  The default conversions have already been
   applied, and enumerated types converted to their compatible integer
   types.  The resulting type is unqualified and has no attributes.

   This is the type for the result of most arithmetic operations
   if the operands have the given two types.  */

સ્થિર વૃક્ષ
c_common_type (વૃક્ષ t1, વૃક્ષ t2)
{
  ગણના વૃક્ષ_code code1;
  ગણના વૃક્ષ_code code2;

  /* If one type is nonsense, use the other.  */
  જો (t1 == error_mark_ગાંઠ)
    પાછા t2;
  જો (t2 == error_mark_ગાંઠ)
    પાછા t1;

  જો (TYPE_QUALS (t1) != TYPE_UNQUALIFIED)
    t1 = TYPE_MAIN_VARIANT (t1);

  જો (TYPE_QUALS (t2) != TYPE_UNQUALIFIED)
    t2 = TYPE_MAIN_VARIANT (t2);

  જો (TYPE_ATTRIBUTES (t1) != NULL_વૃક્ષ)
    {
      વૃક્ષ attrs = affects_type_identity_attributes (TYPE_ATTRIBUTES (t1));
      t1 = c_build_type_attribute_variant (t1, attrs);
    }

  જો (TYPE_ATTRIBUTES (t2) != NULL_વૃક્ષ)
    {
      વૃક્ષ attrs = affects_type_identity_attributes (TYPE_ATTRIBUTES (t2));
      t2 = c_build_type_attribute_variant (t2, attrs);
    }

  /* Save time if the two types are the same.  */

  જો (t1 == t2) પાછા t1;

  code1 = વૃક્ષ_CODE (t1);
  code2 = વૃક્ષ_CODE (t2);

  gcc_assert (code1 == VECTOR_TYPE || code1 == COMPLEX_TYPE
	      || code1 == FIXED_POINT_TYPE || code1 == REAL_TYPE
	      || code1 == INTEGER_TYPE || code1 == BITINT_TYPE);
  gcc_assert (code2 == VECTOR_TYPE || code2 == COMPLEX_TYPE
	      || code2 == FIXED_POINT_TYPE || code2 == REAL_TYPE
	      || code2 == INTEGER_TYPE || code2 == BITINT_TYPE);

  /* When one operand is a decimal float type, the other operand cannot be
     a generic float type or a complex type.  We also disallow vector types
     here.  */
  જો ((DECIMAL_FLOAT_TYPE_P (t1) || DECIMAL_FLOAT_TYPE_P (t2))
      && !(DECIMAL_FLOAT_TYPE_P (t1) && DECIMAL_FLOAT_TYPE_P (t2)))
    {
      જો (code1 == VECTOR_TYPE || code2 == VECTOR_TYPE)
	{
	  error ("cannot mix operands of decimal floating and vector types");
	  પાછા error_mark_ગાંઠ;
	}
      જો (code1 == COMPLEX_TYPE || code2 == COMPLEX_TYPE)
	{
	  error ("cannot mix operands of decimal floating and complex types");
	  પાછા error_mark_ગાંઠ;
	}
      જો (code1 == REAL_TYPE && code2 == REAL_TYPE)
	{
	  error ("cannot mix operands of decimal floating "
		 "and other floating types");
	  પાછા error_mark_ગાંઠ;
	}
    }

  /* If one type is a vector type, return that type.  (How the usual
     arithmetic conversions apply to the vector types extension is not
     precisely specified.)  */
  જો (code1 == VECTOR_TYPE)
    પાછા t1;

  જો (code2 == VECTOR_TYPE)
    પાછા t2;

  /* If one type is complex, form the common type of the non-complex
     components, then make that complex.  Use T1 or T2 if it is the
     required type.  */
  જો (code1 == COMPLEX_TYPE || code2 == COMPLEX_TYPE)
    {
      વૃક્ષ subtype1 = code1 == COMPLEX_TYPE ? વૃક્ષ_TYPE (t1) : t1;
      વૃક્ષ subtype2 = code2 == COMPLEX_TYPE ? વૃક્ષ_TYPE (t2) : t2;
      વૃક્ષ subtype = c_common_type (subtype1, subtype2);

      જો (code1 == COMPLEX_TYPE && વૃક્ષ_TYPE (t1) == subtype)
	પાછા t1;
      નહીંતર જો (code2 == COMPLEX_TYPE && વૃક્ષ_TYPE (t2) == subtype)
	પાછા t2;
      નહીંતર જો (વૃક્ષ_CODE (subtype) == BITINT_TYPE)
	{
	  sorry ("%<_Complex _BitInt(%d)%> unsupported",
		 TYPE_PRECISION (subtype));
	  પાછા code1 == COMPLEX_TYPE ? t1 : t2;
	}
      નહીંતર
	પાછા build_complex_type (subtype);
    }

  /* If only one is real, use it as the result.  */

  જો (code1 == REAL_TYPE && code2 != REAL_TYPE)
    પાછા t1;

  જો (code2 == REAL_TYPE && code1 != REAL_TYPE)
    પાછા t2;

  /* If both are real and either are decimal floating point types, use
     the decimal floating point type with the greater precision. */

  જો (code1 == REAL_TYPE && code2 == REAL_TYPE)
    {
      જો (TYPE_MAIN_VARIANT (t1) == dfloat128_type_ગાંઠ
	  || TYPE_MAIN_VARIANT (t2) == dfloat128_type_ગાંઠ)
	પાછા dfloat128_type_ગાંઠ;
      /* And prefer _Decimal128 over _Decimal64x which has in GCC's
	 implementation the same mode.  */
      નહીંતર જો (TYPE_MAIN_VARIANT (t1) == dfloat64x_type_ગાંઠ
	       || TYPE_MAIN_VARIANT (t2) == dfloat64x_type_ગાંઠ)
	પાછા dfloat64x_type_ગાંઠ;
      નહીંતર જો (TYPE_MAIN_VARIANT (t1) == dfloat64_type_ગાંઠ
	       || TYPE_MAIN_VARIANT (t2) == dfloat64_type_ગાંઠ)
	પાછા dfloat64_type_ગાંઠ;
      નહીંતર જો (TYPE_MAIN_VARIANT (t1) == dfloat32_type_ગાંઠ
	       || TYPE_MAIN_VARIANT (t2) == dfloat32_type_ગાંઠ)
	પાછા dfloat32_type_ગાંઠ;
    }

  /* Deal with fixed-point types.  */
  જો (code1 == FIXED_POINT_TYPE || code2 == FIXED_POINT_TYPE)
    {
      unsigned પૂર્ણાંક unsignedp = 0, satp = 0;
      scalar_mode m1, m2;
      unsigned પૂર્ણાંક fbit1, ibit1, fbit2, ibit2, max_fbit, max_ibit;

      m1 = SCALAR_TYPE_MODE (t1);
      m2 = SCALAR_TYPE_MODE (t2);

      /* If one input type is saturating, the result type is saturating.  */
      જો (TYPE_SATURATING (t1) || TYPE_SATURATING (t2))
	satp = 1;

      /* If both fixed-point types are unsigned, the result type is unsigned.
	 When mixing fixed-point and integer types, follow the sign of the
	 fixed-point type.
	 Otherwise, the result type is signed.  */
      જો ((TYPE_UNSIGNED (t1) && TYPE_UNSIGNED (t2)
	   && code1 == FIXED_POINT_TYPE && code2 == FIXED_POINT_TYPE)
	  || (code1 == FIXED_POINT_TYPE && code2 != FIXED_POINT_TYPE
	      && TYPE_UNSIGNED (t1))
	  || (code1 != FIXED_POINT_TYPE && code2 == FIXED_POINT_TYPE
	      && TYPE_UNSIGNED (t2)))
	unsignedp = 1;

      /* The result type is signed.  */
      જો (unsignedp == 0)
	{
	  /* If the input type is unsigned, we need to convert to the
	     signed type.  */
	  જો (code1 == FIXED_POINT_TYPE && TYPE_UNSIGNED (t1))
	    {
	      ગણના mode_class mclass = (ગણના mode_class) 0;
	      જો (GET_MODE_CLASS (m1) == MODE_UFRACT)
		mclass = MODE_FRACT;
	      નહીંતર જો (GET_MODE_CLASS (m1) == MODE_UACCUM)
		mclass = MODE_ACCUM;
	      નહીંતર
		gcc_unreachable ();
	      m1 = as_a <scalar_mode>
		(mode_for_size (GET_MODE_PRECISION (m1), mclass, 0));
	    }
	  જો (code2 == FIXED_POINT_TYPE && TYPE_UNSIGNED (t2))
	    {
	      ગણના mode_class mclass = (ગણના mode_class) 0;
	      જો (GET_MODE_CLASS (m2) == MODE_UFRACT)
		mclass = MODE_FRACT;
	      નહીંતર જો (GET_MODE_CLASS (m2) == MODE_UACCUM)
		mclass = MODE_ACCUM;
	      નહીંતર
		gcc_unreachable ();
	      m2 = as_a <scalar_mode>
		(mode_for_size (GET_MODE_PRECISION (m2), mclass, 0));
	    }
	}

      જો (code1 == FIXED_POINT_TYPE)
	{
	  fbit1 = GET_MODE_FBIT (m1);
	  ibit1 = GET_MODE_IBIT (m1);
	}
      નહીંતર
	{
	  fbit1 = 0;
	  /* Signed integers need to subtract one sign bit.  */
	  ibit1 = TYPE_PRECISION (t1) - (!TYPE_UNSIGNED (t1));
	}

      જો (code2 == FIXED_POINT_TYPE)
	{
	  fbit2 = GET_MODE_FBIT (m2);
	  ibit2 = GET_MODE_IBIT (m2);
	}
      નહીંતર
	{
	  fbit2 = 0;
	  /* Signed integers need to subtract one sign bit.  */
	  ibit2 = TYPE_PRECISION (t2) - (!TYPE_UNSIGNED (t2));
	}

      max_ibit = ibit1 >= ibit2 ?  ibit1 : ibit2;
      max_fbit = fbit1 >= fbit2 ?  fbit1 : fbit2;
      પાછા c_common_fixed_point_type_for_size (max_ibit, max_fbit, unsignedp,
						 satp);
    }

  /* Both real or both integers; use the one with greater precision.  */

  જો (TYPE_PRECISION (t1) > TYPE_PRECISION (t2))
    પાછા t1;
  નહીંતર જો (TYPE_PRECISION (t2) > TYPE_PRECISION (t1))
    પાછા t2;

  /* Same precision.  Prefer long longs to longs to ints when the
     same precision, following the C99 rules on integer type rank
     (which are equivalent to the C90 rules for C90 types).  */

  જો (TYPE_MAIN_VARIANT (t1) == long_long_unsigned_type_ગાંઠ
      || TYPE_MAIN_VARIANT (t2) == long_long_unsigned_type_ગાંઠ)
    પાછા long_long_unsigned_type_ગાંઠ;

  જો (TYPE_MAIN_VARIANT (t1) == long_long_integer_type_ગાંઠ
      || TYPE_MAIN_VARIANT (t2) == long_long_integer_type_ગાંઠ)
    {
      જો (TYPE_UNSIGNED (t1) || TYPE_UNSIGNED (t2))
	પાછા long_long_unsigned_type_ગાંઠ;
      નહીંતર
	પાછા long_long_integer_type_ગાંઠ;
    }

  જો (TYPE_MAIN_VARIANT (t1) == long_unsigned_type_ગાંઠ
      || TYPE_MAIN_VARIANT (t2) == long_unsigned_type_ગાંઠ)
    પાછા long_unsigned_type_ગાંઠ;

  જો (TYPE_MAIN_VARIANT (t1) == long_integer_type_ગાંઠ
      || TYPE_MAIN_VARIANT (t2) == long_integer_type_ગાંઠ)
    {
      /* But preserve unsignedness from the other type,
	 since long cannot hold all the values of an unsigned int.  */
      જો (TYPE_UNSIGNED (t1) || TYPE_UNSIGNED (t2))
	પાછા long_unsigned_type_ગાંઠ;
      નહીંતર
	પાછા long_integer_type_ગાંઠ;
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
  વૃક્ષ mv1 = TYPE_MAIN_VARIANT (t1);
  વૃક્ષ mv2 = TYPE_MAIN_VARIANT (t2);

  માટે (પૂર્ણાંક i = અંક_FLOATN_TYPES - 1; i >= 0; i--)
    જો (mv1 == FLOATN_TYPE_ગાંઠ (i) || mv2 == FLOATN_TYPE_ગાંઠ (i))
      પાછા FLOATN_TYPE_ગાંઠ (i);

  /* Likewise, prefer long double to double even if same size.  */
  જો (mv1 == long_double_type_ગાંઠ || mv2 == long_double_type_ગાંઠ)
    પાછા long_double_type_ગાંઠ;

  /* Likewise, prefer double to float even if same size.
     We got a couple of embedded targets with 32 bit doubles, and the
     pdp11 might have 64 bit floats.  */
  જો (mv1 == double_type_ગાંઠ || mv2 == double_type_ગાંઠ)
    પાછા double_type_ગાંઠ;

  જો (mv1 == float_type_ગાંઠ || mv2 == float_type_ગાંઠ)
    પાછા float_type_ગાંઠ;

  માટે (પૂર્ણાંક i = અંક_FLOATNX_TYPES - 1; i >= 0; i--)
    જો (mv1 == FLOATNX_TYPE_ગાંઠ (i) || mv2 == FLOATNX_TYPE_ગાંઠ (i))
      પાછા FLOATNX_TYPE_ગાંઠ (i);

  જો ((code1 == BITINT_TYPE || code2 == BITINT_TYPE) && code1 != code2)
    {
      /* Prefer any other integral types over bit-precise integer types.  */
      જો (TYPE_UNSIGNED (t1) == TYPE_UNSIGNED (t2))
	પાછા code1 == BITINT_TYPE ? t2 : t1;
      /* If BITINT_TYPE is unsigned and the other type is signed
	 non-BITINT_TYPE with the same precision, the latter has higher rank.
	 In that case:
	 Otherwise, both operands are converted to the unsigned integer type
	 corresponding to the type of the operand with signed integer type.  */
      જો (TYPE_UNSIGNED (code1 == BITINT_TYPE ? t1 : t2))
	પાછા c_common_unsigned_type (code1 == BITINT_TYPE ? t2 : t1);
    }

  /* Otherwise prefer the unsigned one.  */

  જો (TYPE_UNSIGNED (t1))
    પાછા t1;
  નહીંતર
    પાછા t2;
}

/* Wrapper around c_common_type that is used by c-common.cc and other
   front end optimizations that remove promotions.  ENUMERAL_TYPEs
   are allowed here and are converted to their compatible integer types.
   BOOLEAN_TYPEs are allowed here and return either boolean_type_node or
   preferably a non-Boolean type as the common type.  */
વૃક્ષ
common_type (વૃક્ષ t1, વૃક્ષ t2)
{
  જો (વૃક્ષ_CODE (t1) == ENUMERAL_TYPE)
    t1 = ENUM_UNDERLYING_TYPE (t1);
  જો (વૃક્ષ_CODE (t2) == ENUMERAL_TYPE)
    t2 = ENUM_UNDERLYING_TYPE (t2);

  /* If both types are BOOLEAN_TYPE, then return boolean_type_node.  */
  જો (વૃક્ષ_CODE (t1) == BOOLEAN_TYPE
      && વૃક્ષ_CODE (t2) == BOOLEAN_TYPE)
    પાછા boolean_type_ગાંઠ;

  /* If either type is BOOLEAN_TYPE, then return the other.  */
  જો (વૃક્ષ_CODE (t1) == BOOLEAN_TYPE)
    પાછા t2;
  જો (વૃક્ષ_CODE (t2) == BOOLEAN_TYPE)
    પાછા t1;

  પાછા c_common_type (t1, t2);
}



/* Helper function for comptypes.  For two compatible types, return 1
   if they pass consistency checks.  In particular we test that
   TYPE_CANONICAL is set correctly, i.e. the two types can alias.  */

સ્થિર તાર્કિક
comptypes_verify (વૃક્ષ type1, વૃક્ષ type2)
{
  જો (type1 == type2 || !type1 || !type2
      || વૃક્ષ_CODE (type1) == ERROR_MARK || વૃક્ષ_CODE (type2) == ERROR_MARK)
    પાછા સાચું;

  gcc_checking_assert (c_verify_type (type1));
  gcc_checking_assert (c_verify_type (type2));

  જો (TYPE_CANONICAL (type1) != TYPE_CANONICAL (type2)
      && !TYPE_STRUCTURAL_EQUALITY_P (type1)
      && !TYPE_STRUCTURAL_EQUALITY_P (type2))
    {
      /* FIXME: check other types. */
      જો (RECORD_OR_UNION_TYPE_P (type1)
	  || વૃક્ષ_CODE (type1) == ENUMERAL_TYPE
	  || વૃક્ષ_CODE (type2) == ENUMERAL_TYPE)
	પાછા ખોટું;
    }
  પાછા સાચું;
}

સંરચના comptypes_data {

  /* output */
  તાર્કિક enum_and_int_p;
  તાર્કિક different_types_p;
  તાર્કિક warning_needed;

  /* context */
  તાર્કિક anon_field;
  તાર્કિક pointedto;

  /* configuration */
  તાર્કિક equiv;
  તાર્કિક ignore_promoting_args;

  અચલ સંરચના tagged_tu_seen_cache* cache;
};


/* Helper function for composite_type.  This function ignores when the
   function type of an old-style declaration is incompatible with a type
   of a declaration with prototype because some are arguments are not
   self-promoting.  This is ignored only for function types but not
   ignored in a nested context.  */

સ્થિર તાર્કિક
comptypes_check_for_composite (વૃક્ષ t1, વૃક્ષ t2)
{
  સંરચના comptypes_data data = { };
  data.ignore_promoting_args = FUNCTION_TYPE == વૃક્ષ_CODE (t1);
  પાછા comptypes_internal (t1, t2, &data);
}


/* C implementation of compatible_types_for_indirection_note_p.  */

તાર્કિક
compatible_types_for_indirection_note_p (વૃક્ષ type1, વૃક્ષ type2)
{
  પાછા comptypes (type1, type2);
}

/* Return true if TYPE1 and TYPE2 are compatible types for assignment
   or various other operations.  */

તાર્કિક
comptypes (વૃક્ષ type1, વૃક્ષ type2)
{
  સંરચના comptypes_data data = { };
  તાર્કિક ret = comptypes_internal (type1, type2, &data);

  gcc_checking_assert (!ret || comptypes_verify (type1, type2));

  પાછા ret;
}


/* Like comptypes, but it returns non-zero only for identical
   types.  */

તાર્કિક
comptypes_same_p (વૃક્ષ type1, વૃક્ષ type2)
{
  સંરચના comptypes_data data = { };
  તાર્કિક ret = comptypes_internal (type1, type2, &data);

  gcc_checking_assert (!ret || comptypes_verify (type1, type2));

  જો (data.different_types_p)
    પાછા ખોટું;

  પાછા ret;
}


/* Like comptypes, but if it returns true because enum and int are
   compatible, it sets *ENUM_AND_INT_P to true.  */

તાર્કિક
comptypes_check_enum_int (વૃક્ષ type1, વૃક્ષ type2, તાર્કિક *enum_and_int_p)
{
  સંરચના comptypes_data data = { };
  તાર્કિક ret = comptypes_internal (type1, type2, &data);
  *enum_and_int_p = data.enum_and_int_p;

  gcc_checking_assert (!ret || comptypes_verify (type1, type2));

  પાછા ret;
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

તાર્કિક
comptypes_equiv_p (વૃક્ષ type1, વૃક્ષ type2)
{
  સંરચના comptypes_data data = { };
  data.equiv = સાચું;
  તાર્કિક ret = comptypes_internal (type1, type2, &data);

  /* check that different equivance classes are assigned only
     to types that are not compatible.  */
  gcc_checking_assert (ret || !comptypes (type1, type2));

  પાછા ret;
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

સ્થિર તાર્કિક
comptypes_internal (const_વૃક્ષ type1, const_વૃક્ષ type2,
		    સંરચના comptypes_data *data)
{
  const_વૃક્ષ t1 = type1;
  const_વૃક્ષ t2 = type2;

  /* Suppress errors caused by previously reported errors.  */

  જો (t1 == t2 || !t1 || !t2
      || વૃક્ષ_CODE (t1) == ERROR_MARK || વૃક્ષ_CODE (t2) == ERROR_MARK)
    પાછા સાચું;

  /* Qualifiers must match. C99 6.7.3p9 */

  જો (TYPE_QUALS (t1) != TYPE_QUALS (t2))
    પાછા ખોટું;

  /* Enumerated types are compatible with integer types, but this is
     not transitive: two enumerated types in the same translation unit
     are compatible with each other only if they are the same type.  */

  જો (વૃક્ષ_CODE (t1) == ENUMERAL_TYPE
      && COMPLETE_TYPE_P (t1)
      && વૃક્ષ_CODE (t2) != ENUMERAL_TYPE)
    {
      t1 = ENUM_UNDERLYING_TYPE (t1);
      જો (વૃક્ષ_CODE (t2) != VOID_TYPE)
	{
	  data->enum_and_int_p = સાચું;
	  data->different_types_p = સાચું;
	}
    }
  નહીંતર જો (વૃક્ષ_CODE (t2) == ENUMERAL_TYPE
	   && COMPLETE_TYPE_P (t2)
	   && વૃક્ષ_CODE (t1) != ENUMERAL_TYPE)
    {
      t2 = ENUM_UNDERLYING_TYPE (t2);
      જો (વૃક્ષ_CODE (t1) != VOID_TYPE)
	{
	  data->enum_and_int_p = સાચું;
	  data->different_types_p = સાચું;
	}
    }

  જો (t1 == t2)
    પાછા સાચું;

  /* Different classes of types can't be compatible.  */

  જો (વૃક્ષ_CODE (t1) != વૃક્ષ_CODE (t2))
    પાછા ખોટું;

  /* Allow for two different type nodes which have essentially the same
     definition.  Note that we already checked for equality of the type
     qualifiers (just above).  */

  જો (વૃક્ષ_CODE (t1) != ARRAY_TYPE
      && TYPE_MAIN_VARIANT (t1) == TYPE_MAIN_VARIANT (t2))
    પાછા સાચું;

  પૂર્ણાંક attrval;

  /* 1 if no need for warning yet, 2 if warning cause has been seen.  */
  જો (!(attrval = comp_type_attributes (t1, t2)))
    પાછા ખોટું;

  જો (2 == attrval)
    data->warning_needed = સાચું;

  પસંદગી (વૃક્ષ_CODE (t1))
    {
    સ્થિતિ INTEGER_TYPE:
    સ્થિતિ FIXED_POINT_TYPE:
    સ્થિતિ REAL_TYPE:
    સ્થિતિ BITINT_TYPE:
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
      પાછા TYPE_CANONICAL (t1) == TYPE_CANONICAL (t2);

    સ્થિતિ POINTER_TYPE:
      /* Do not remove mode information.  */
      જો (TYPE_MODE (t1) != TYPE_MODE (t2))
	પાછા ખોટું;
      data->pointedto = સાચું;
      પાછા comptypes_internal (વૃક્ષ_TYPE (t1), વૃક્ષ_TYPE (t2), data);

    સ્થિતિ FUNCTION_TYPE:
      પાછા function_types_compatible_p (t1, t2, data);

    સ્થિતિ ARRAY_TYPE:
      {
	વૃક્ષ d1 = TYPE_DOMAIN (t1);
	વૃક્ષ d2 = TYPE_DOMAIN (t2);

	/* Target types must match incl. qualifiers.  */
	જો (!comptypes_internal (વૃક્ષ_TYPE (t1), વૃક્ષ_TYPE (t2), data))
	  પાછા ખોટું;

	જો ((d1 == NULL_વૃક્ષ) != (d2 == NULL_વૃક્ષ))
	  data->different_types_p = સાચું;
	/* Ignore size mismatches when forming equivalence classes.  */
	જો (data->equiv)
	  પાછા સાચું;
	/* Sizes must match unless one is missing or variable.  */
	જો (d1 == NULL_વૃક્ષ || d2 == NULL_વૃક્ષ || d1 == d2)
	  પાછા સાચું;

	તાર્કિક d1_variable = ટોચ_array_vla_p (t1);
	તાર્કિક d2_variable = ટોચ_array_vla_p (t2);

	જો (d1_variable != d2_variable)
	  data->different_types_p = સાચું;
	જો (d1_variable || d2_variable)
	  પાછા સાચું;

	તાર્કિક d1_zero = zero_length_array_type_p (t1)
		       || flexible_array_member_type_p (t1);

	તાર્કિક d2_zero = zero_length_array_type_p (t2)
		       || flexible_array_member_type_p (t2);

	જો (d1_zero && d2_zero)
	  પાછા સાચું;
	જો (d1_zero || d2_zero)
	  પાછા ખોટું;

	જો (!વૃક્ષ_int_cst_equal (TYPE_MIN_કિંમત (d1), TYPE_MIN_કિંમત (d2))
	    || !વૃક્ષ_int_cst_equal (TYPE_MAX_કિંમત (d1), TYPE_MAX_કિંમત (d2)))
	  પાછા ખોટું;

	પાછા સાચું;
      }

    સ્થિતિ ENUMERAL_TYPE:
    સ્થિતિ RECORD_TYPE:
    સ્થિતિ UNION_TYPE:

      જો (!flag_isoc23)
	પાછા ખોટું;

      પાછા tagged_types_tu_compatible_p (t1, t2, data);

    સ્થિતિ VECTOR_TYPE:
      પાછા known_eq (TYPE_VECTOR_SUBPARTS (t1), TYPE_VECTOR_SUBPARTS (t2))
	     && comptypes_internal (વૃક્ષ_TYPE (t1), વૃક્ષ_TYPE (t2), data);

    મૂળભૂત:
      પાછા ખોટું;
    }
  gcc_unreachable ();
}

/* Return true if TTL and TTR are pointers to types that are equivalent, ignoring
   their qualifiers, except for named address spaces.  If the pointers point to
   different named addresses, then we must determine if one address space is a
   subset of the other.  */

સ્થિર તાર્કિક
comp_target_types (location_t location, વૃક્ષ ttl, વૃક્ષ ttr)
{
  વૃક્ષ mvl = વૃક્ષ_TYPE (ttl);
  વૃક્ષ mvr = વૃક્ષ_TYPE (ttr);
  addr_space_t asl = TYPE_ADDR_SPACE (mvl);
  addr_space_t asr = TYPE_ADDR_SPACE (mvr);
  addr_space_t as_common;

  /* Fail if pointers point to incompatible address spaces.  */
  જો (!addr_space_superset (asl, asr, &as_common))
    પાછા 0;

  /* Qualifiers on element types of array types that are
     pointer targets are also removed.  */
  સંરચના comptypes_data data = { };
  જો (!comptypes_internal (remove_qualifiers (mvl),
			   remove_qualifiers (mvr), &data))
    પાછા ખોટું;

  /* For pedantic use comptypes on arrays before removing
     qualifiers on the element type. */
  જો (વૃક્ષ_CODE (mvl) == ARRAY_TYPE
      && વૃક્ષ_CODE (mvr) == ARRAY_TYPE
      && !comptypes (mvl, mvr))
    pedwarn_c11 (location, OPT_Wpedantic, "invalid use of pointers to arrays "
					  "with different qualifiers in ISO C "
					  "before C23");

  જો (data.warning_needed)
    pedwarn (location, OPT_Wpedantic, "types are not quite compatible");

  જો (data.enum_and_int_p && warn_cxx_compat)
    warning_at (location, OPT_Wc___compat,
		"pointer target types incompatible in C++");

  પાછા સાચું;
}

/* Subroutines of `comptypes'.  */

/* Return true if two 'struct', 'union', or 'enum' types T1 and T2 are
   compatible.  The two types are not the same (which has been
   checked earlier in comptypes_internal).  */

સ્થિર તાર્કિક
tagged_types_tu_compatible_p (const_વૃક્ષ t1, const_વૃક્ષ t2,
			      સંરચના comptypes_data *data)
{
  વૃક્ષ s1, s2;

  જો (c_type_tag (t1) != c_type_tag (t2))
    પાછા ખોટું;

  /* When forming equivalence classes for TYPE_CANONICAL in C23, we treat
     structs with the same tag as equivalent, but only when they are targets
     of pointers inside other structs.  */
  જો (data->equiv && data->pointedto && NULL_વૃક્ષ != c_type_tag (t1))
    પાછા સાચું;

  /* Different types without tag are incompatible except as an anonymous
     field or when forming equivalence classes for TYPE_CANONICAL.  */
  જો (!data->anon_field && !data->equiv && NULL_વૃક્ષ == c_type_tag (t1))
    પાછા ખોટું;

  જો (!data->anon_field && TYPE_STUB_DECL (t1) != TYPE_STUB_DECL (t2))
    data->different_types_p = સાચું;

  /* Incomplete types are incompatible inside a TU.  */
  જો (TYPE_SIZE (t1) == ખાલી || TYPE_SIZE (t2) == ખાલી)
    પાછા ખોટું;

  જો (ENUMERAL_TYPE != વૃક્ષ_CODE (t1)
      && (TYPE_REVERSE_STORAGE_ORDER (t1)
	  != TYPE_REVERSE_STORAGE_ORDER (t2)))
    પાછા ખોટું;

  જો (TYPE_USER_ALIGN (t1) != TYPE_USER_ALIGN (t2))
    data->different_types_p = સાચું;

  /* For types already being looked at in some active
     invocation of this function, assume compatibility.
     The cache is built as a linked list on the stack
     with the head of the list passed downwards.  */
  માટે (અચલ સંરચના tagged_tu_seen_cache *t = data->cache;
       t != ખાલી; t = t->next)
    જો (t->t1 == t1 && t->t2 == t2)
      પાછા સાચું;

  અચલ સંરચના tagged_tu_seen_cache entry = { data->cache, t1, t2 };

  પસંદગી (વૃક્ષ_CODE (t1))
    {
    સ્થિતિ ENUMERAL_TYPE:
      {
	જો (!comptypes (ENUM_UNDERLYING_TYPE (t1), ENUM_UNDERLYING_TYPE (t2)))
	  પાછા ખોટું;

	/* Speed up the case where the type values are in the same order.  */
	વૃક્ષ tv1 = TYPE_કિંમતો (t1);
	વૃક્ષ tv2 = TYPE_કિંમતો (t2);

	જો (tv1 == tv2)
	  પાછા સાચું;

	માટે (;tv1 && tv2; tv1 = વૃક્ષ_CHAIN (tv1), tv2 = વૃક્ષ_CHAIN (tv2))
	  {
	    જો (વૃક્ષ_PURPOSE (tv1) != વૃક્ષ_PURPOSE (tv2))
	      તોડો;

	    જો (simple_cst_equal (DECL_INITIAL (વૃક્ષ_કિંમત (tv1)),
				  DECL_INITIAL (વૃક્ષ_કિંમત (tv2))) != 1)
	      તોડો;
	  }

	જો (tv1 == NULL_વૃક્ષ && tv2 == NULL_વૃક્ષ)
	  પાછા સાચું;

	જો (tv1 == NULL_વૃક્ષ || tv2 == NULL_વૃક્ષ)
	  પાછા ખોટું;

	જો (list_length (TYPE_કિંમતો (t1)) != list_length (TYPE_કિંમતો (t2)))
	  પાછા ખોટું;

	માટે (s1 = TYPE_કિંમતો (t1); s1; s1 = વૃક્ષ_CHAIN (s1))
	  {
	    s2 = purpose_member (વૃક્ષ_PURPOSE (s1), TYPE_કિંમતો (t2));

	    જો (s2 == ખાલી
		|| simple_cst_equal (DECL_INITIAL (વૃક્ષ_કિંમત (s1)),
				     DECL_INITIAL (વૃક્ષ_કિંમત (s2))) != 1)
	      પાછા ખોટું;
	  }

	પાછા સાચું;
      }

    સ્થિતિ UNION_TYPE:
    સ્થિતિ RECORD_TYPE:

	જો (list_length (TYPE_FIELDS (t1)) != list_length (TYPE_FIELDS (t2)))
	  પાછા ખોટું;

	માટે (s1 = TYPE_FIELDS (t1), s2 = TYPE_FIELDS (t2);
	     s1 && s2;
	     s1 = DECL_CHAIN (s1), s2 = DECL_CHAIN (s2))
	  {
	    gcc_assert (વૃક્ષ_CODE (s1) == FIELD_DECL);
	    gcc_assert (વૃક્ષ_CODE (s2) == FIELD_DECL);

	    વૃક્ષ ft1 = વૃક્ષ_TYPE (s1);
	    વૃક્ષ ft2 = વૃક્ષ_TYPE (s2);

	    જો (DECL_NAME (s1) != DECL_NAME (s2))
	      પાછા ખોટું;

	    જો (DECL_ALIGN (s1) != DECL_ALIGN (s2))
	      પાછા ખોટું;

	    જો (DECL_C_BIT_FIELD (s1) != DECL_C_BIT_FIELD (s2))
	       પાછા ખોટું;

	    જો (DECL_C_BIT_FIELD (s1))
	      {
		જો (!વૃક્ષ_int_cst_equal (DECL_SIZE (s1), DECL_SIZE (s2)))
		  પાછા ખોટું;

		ft1 = DECL_BIT_FIELD_TYPE (s1);
		ft2 = DECL_BIT_FIELD_TYPE (s2);
	      }

	    જો (!ft1 || !ft2)
	      પાછા ખોટું;

	    જો (વૃક્ષ_CODE (ft1) == ERROR_MARK || વૃક્ષ_CODE (ft2) == ERROR_MARK)
	      પાછા ખોટું;

	    data->anon_field = !DECL_NAME (s1);
	    data->pointedto = ખોટું;

	    અચલ સંરચના tagged_tu_seen_cache *cache = data->cache;
	    data->cache = &entry;
	    તાર્કિક ret = comptypes_internal (ft1, ft2, data);
	    data->cache = cache;
	    જો (!ret)
	      પાછા ખોટું;

	    વૃક્ષ st1 = TYPE_SIZE (વૃક્ષ_TYPE (s1));
	    વૃક્ષ st2 = TYPE_SIZE (વૃક્ષ_TYPE (s2));

	    જો (data->equiv
		&& st1 && વૃક્ષ_CODE (st1) == INTEGER_CST
		&& st2 && વૃક્ષ_CODE (st2) == INTEGER_CST
		&& !વૃક્ષ_int_cst_equal (st1, st2))
	     પાછા ખોટું;

	    વૃક્ષ counted_by1 = lookup_attribute ("counted_by",
						 DECL_ATTRIBUTES (s1));
	    વૃક્ષ counted_by2 = lookup_attribute ("counted_by",
						 DECL_ATTRIBUTES (s2));
	    /* If there is no counted_by attribute for both fields.  */
	    જો (!counted_by1 && !counted_by2)
	      ચાલુ;

	    /* If only one field has counted_by attribute.  */
	    જો ((counted_by1 && !counted_by2)
		|| (!counted_by1 && counted_by2))
	      પાછા ખોટું;

	    /* Now both s1 and s2 have counted_by attributes, check
	       whether they are the same.  */

	    વૃક્ષ counted_by_field1
	      = lookup_field (t1, વૃક્ષ_કિંમત (વૃક્ષ_કિંમત (counted_by1)));
	    વૃક્ષ counted_by_field2
	      = lookup_field (t2, વૃક્ષ_કિંમત (વૃક્ષ_કિંમત (counted_by2)));

	    gcc_assert (counted_by_field1 && counted_by_field2);

	    જ્યારે (વૃક્ષ_CHAIN (counted_by_field1))
	      counted_by_field1 = વૃક્ષ_CHAIN (counted_by_field1);
	    જ્યારે (વૃક્ષ_CHAIN (counted_by_field2))
	      counted_by_field2 = વૃક્ષ_CHAIN (counted_by_field2);

	    જો (DECL_NAME (વૃક્ષ_કિંમત (counted_by_field1))
		!= DECL_NAME (વૃક્ષ_કિંમત (counted_by_field2)))
	      પાછા ખોટું;
	  }
	પાછા સાચું;

    મૂળભૂત:
      gcc_unreachable ();
    }
}

/* Return true if two function types F1 and F2 are compatible.
   If either type specifies no argument types,
   the other must specify a fixed number of self-promoting arg types.
   Otherwise, if one type specifies only the number of arguments,
   the other must specify that number of self-promoting arg types.
   Otherwise, the argument types must match.  */

સ્થિર તાર્કિક
function_types_compatible_p (const_વૃક્ષ f1, const_વૃક્ષ f2,
			     સંરચના comptypes_data *data)
{
  વૃક્ષ ret1 = વૃક્ષ_TYPE (f1);
  વૃક્ષ ret2 = વૃક્ષ_TYPE (f2);

  /* 'volatile' qualifiers on a function's return type used to mean
     the function is noreturn.  */
  જો (TYPE_VOLATILE (ret1) != TYPE_VOLATILE (ret2))
    pedwarn (આગત_location, 0, "function return types not compatible due to %<volatile%>");
  જો (TYPE_VOLATILE (ret1))
    ret1 = build_qualified_type (TYPE_MAIN_VARIANT (ret1),
				 TYPE_QUALS (ret1) & ~TYPE_QUAL_VOLATILE);
  જો (TYPE_VOLATILE (ret2))
    ret2 = build_qualified_type (TYPE_MAIN_VARIANT (ret2),
				 TYPE_QUALS (ret2) & ~TYPE_QUAL_VOLATILE);

  તાર્કિક ignore_pargs = data->ignore_promoting_args;
  data->ignore_promoting_args = ખોટું;

  જો (!comptypes_internal (ret1, ret2, data))
    પાછા ખોટું;

  data->ignore_promoting_args = ignore_pargs;

  વૃક્ષ args1 = TYPE_ARG_TYPES (f1);
  વૃક્ષ args2 = TYPE_ARG_TYPES (f2);

  જો ((args1 == NULL_વૃક્ષ) != (args2 == NULL_વૃક્ષ))
    data->different_types_p = સાચું;

  /* An unspecified parmlist matches any specified parmlist
     whose argument types don't need default promotions.  */

  જો (args1 == NULL_વૃક્ષ)
    {
      જો (TYPE_NO_NAMED_ARGS_STDARG_P (f1) != TYPE_NO_NAMED_ARGS_STDARG_P (f2))
	પાછા ખોટું;
      જો (!(data->ignore_promoting_args || self_promoting_args_p (args2)))
	પાછા ખોટું;
      data->ignore_promoting_args = ખોટું;
      /* If one of these types comes from a non-prototype fn definition,
	 compare that with the other type's arglist.
	 If they don't match, ask for a warning (but no error).  */
      જો (TYPE_ACTUAL_ARG_TYPES (f1)
	  && !type_lists_compatible_p (args2, TYPE_ACTUAL_ARG_TYPES (f1), data))
	 data->warning_needed = સાચું;
      પાછા સાચું;
    }
  જો (args2 == NULL_વૃક્ષ)
    {
      જો (TYPE_NO_NAMED_ARGS_STDARG_P (f1) != TYPE_NO_NAMED_ARGS_STDARG_P (f2))
	પાછા ખોટું;
      જો (!(data->ignore_promoting_args || self_promoting_args_p (args1)))
	પાછા ખોટું;
      data->ignore_promoting_args = ખોટું;
      જો (TYPE_ACTUAL_ARG_TYPES (f2)
	  && !type_lists_compatible_p (args1, TYPE_ACTUAL_ARG_TYPES (f2), data))
	data->warning_needed = સાચું;
      પાછા સાચું;
    }

  /* Both types have argument lists: compare them and propagate results.  */
  પાછા type_lists_compatible_p (args1, args2, data);
}

/* Check two lists of types for compatibility, returning false for
   incompatible, true for compatible.  */

સ્થિર તાર્કિક
type_lists_compatible_p (const_વૃક્ષ args1, const_વૃક્ષ args2,
			 સંરચના comptypes_data *data)
{
  જ્યારે (1)
    {
      જો (args1 == NULL_વૃક્ષ && args2 == NULL_વૃક્ષ)
	પાછા સાચું;
      /* If one list is shorter than the other,
	 they fail to match.  */
      જો (args1 == NULL_વૃક્ષ || args2 == NULL_વૃક્ષ)
	પાછા ખોટું;
      વૃક્ષ a1 = વૃક્ષ_કિંમત (args1);
      વૃક્ષ a2 = વૃક્ષ_કિંમત (args2);
      વૃક્ષ mv1 = remove_qualifiers (a1);
      વૃક્ષ mv2 = remove_qualifiers (a2);

      gcc_assert (mv2);
      gcc_assert (mv2);

      /* If one of the lists has an error marker, ignore this arg.  */
      જો (વૃક્ષ_CODE (a1) == ERROR_MARK
	       || વૃક્ષ_CODE (a2) == ERROR_MARK)
	;
      નહીંતર જો (!comptypes_internal (mv1, mv2, data))
	{
	  data->different_types_p = સાચું;
	  /* Allow  wait (union {union wait *u; int *i} *)
	     and  wait (union wait *)  to be compatible.  */
	  જો (વૃક્ષ_CODE (a1) == UNION_TYPE
	      && (TYPE_NAME (a1) == NULL_વૃક્ષ
		  || TYPE_TRANSPARENT_AGGR (a1))
	      && વૃક્ષ_CODE (TYPE_SIZE (a1)) == INTEGER_CST
	      && વૃક્ષ_int_cst_equal (TYPE_SIZE (a1),
				     TYPE_SIZE (a2)))
	    {
	      વૃક્ષ memb;
	      માટે (memb = TYPE_FIELDS (a1);
		   memb; memb = DECL_CHAIN (memb))
		{
		  વૃક્ષ mv3 = remove_qualifiers (વૃક્ષ_TYPE (memb));
		  જો (comptypes_internal (mv3, mv2, data))
		    તોડો;
		}
	      જો (memb == NULL_વૃક્ષ)
		પાછા ખોટું;
	    }
	  નહીંતર જો (વૃક્ષ_CODE (a2) == UNION_TYPE
		   && (TYPE_NAME (a2) == NULL_વૃક્ષ
		       || TYPE_TRANSPARENT_AGGR (a2))
		   && વૃક્ષ_CODE (TYPE_SIZE (a2)) == INTEGER_CST
		   && વૃક્ષ_int_cst_equal (TYPE_SIZE (a2),
					  TYPE_SIZE (a1)))
	    {
	      વૃક્ષ memb;
	      માટે (memb = TYPE_FIELDS (a2);
		   memb; memb = DECL_CHAIN (memb))
		{
		  વૃક્ષ mv3 = remove_qualifiers (વૃક્ષ_TYPE (memb));
		  જો (comptypes_internal (mv3, mv1, data))
		    તોડો;
		}
	      જો (memb == NULL_વૃક્ષ)
		પાછા ખોટું;
	    }
	  નહીંતર
	    પાછા ખોટું;
	}

      args1 = વૃક્ષ_CHAIN (args1);
      args2 = વૃક્ષ_CHAIN (args2);
    }
}

/* Compute the size to increment a pointer by.  When a function type or void
   type or incomplete type is passed, size_one_node is returned.
   This function does not emit any diagnostics; the caller is responsible
   for that.  */

સ્થિર વૃક્ષ
c_size_in_bytes (const_વૃક્ષ type)
{
  ગણના વૃક્ષ_code code = વૃક્ષ_CODE (type);

  જો (code == FUNCTION_TYPE || code == VOID_TYPE || code == ERROR_MARK
      || !COMPLETE_TYPE_P (type))
    પાછા size_one_ગાંઠ;

  /* Convert in case a char is more than one unit.  */
  પાછા size_binop_loc (આગત_location, CEIL_DIV_પદાવલિ, TYPE_SIZE_UNIT (type),
			 size_int (TYPE_PRECISION (char_type_ગાંઠ)
				   / BITS_PER_UNIT));
}

/* Return either DECL or its known constant value (if it has one).  */

વૃક્ષ
decl_constant_કિંમત_1 (વૃક્ષ decl, તાર્કિક in_init)
{
  જો (/* Note that DECL_INITIAL isn't valid for a PARM_DECL.  */
      વૃક્ષ_CODE (decl) != PARM_DECL
      && !વૃક્ષ_THIS_VOLATILE (decl)
      && વૃક્ષ_READONLY (decl)
      && DECL_INITIAL (decl) != NULL_વૃક્ષ
      && !error_operand_p (DECL_INITIAL (decl))
      /* This is invalid if initial value is not constant.
	 If it has either a function call, a memory reference,
	 or a variable, then re-evaluating it could give different results.  */
      && વૃક્ષ_CONSTANT (DECL_INITIAL (decl))
      /* Check for cases where this is sub-optimal, even though valid.  */
      && (in_init || વૃક્ષ_CODE (DECL_INITIAL (decl)) != CONSTRUCTOR))
    પાછા DECL_INITIAL (decl);
  પાછા decl;
}

/* Return either DECL or its known constant value (if it has one).
   Like the above, but always return decl outside of functions.  */

વૃક્ષ
decl_constant_કિંમત (વૃક્ષ decl)
{
  /* Don't change a variable array bound or initial value to a constant
     in a place where a variable is invalid.  */
  પાછા current_function_decl ? decl_constant_કિંમત_1 (decl, ખોટું) : decl;
}

/* Convert the array expression EXP to a pointer.  */
સ્થિર વૃક્ષ
array_to_pointer_conversion (location_t loc, વૃક્ષ exp)
{
  વૃક્ષ orig_exp = exp;
  વૃક્ષ type = વૃક્ષ_TYPE (exp);
  વૃક્ષ adr;
  વૃક્ષ restype = વૃક્ષ_TYPE (type);
  વૃક્ષ ptrtype;

  gcc_assert (વૃક્ષ_CODE (type) == ARRAY_TYPE);

  STRIP_TYPE_NOPS (exp);

  copy_warning (exp, orig_exp);

  ptrtype = c_build_pointer_type (restype);

  જો (INDIRECT_REF_P (exp))
    પાછા convert (ptrtype, વૃક્ષ_OPERAND (exp, 0));

  /* In C++ array compound literals are temporary objects unless they are
     const or appear in namespace scope, so they are destroyed too soon
     to use them for much of anything  (c++/53220).  */
  જો (warn_cxx_compat && વૃક્ષ_CODE (exp) == COMPOUND_LITERAL_પદાવલિ)
    {
      વૃક્ષ decl = વૃક્ષ_OPERAND (વૃક્ષ_OPERAND (exp, 0), 0);
      જો (!વૃક્ષ_READONLY (decl) && !વૃક્ષ_STATIC (decl))
	warning_at (DECL_SOURCE_LOCATION (decl), OPT_Wc___compat,
		    "converting an array compound literal to a pointer "
		    "leads to a dangling pointer in C++");
    }

  adr = build_unary_op (loc, ADDR_પદાવલિ, exp, સાચું);
  પાછા convert (ptrtype, adr);
}

/* Convert the function expression EXP to a pointer.  */
સ્થિર વૃક્ષ
function_to_pointer_conversion (location_t loc, વૃક્ષ exp)
{
  વૃક્ષ orig_exp = exp;

  gcc_assert (વૃક્ષ_CODE (વૃક્ષ_TYPE (exp)) == FUNCTION_TYPE);

  STRIP_TYPE_NOPS (exp);

  copy_warning (exp, orig_exp);

  વૃક્ષ exp2 = build_unary_op (loc, ADDR_પદાવલિ, exp, ખોટું);

  /* If the function is defined and known to not require a non-local
     context, make sure no trampoline is generated.  */
  જો (વૃક્ષ_CODE (exp) == FUNCTION_DECL
      && DECL_INITIAL (exp) && !C_FUNC_NONLOCAL_CONTEXT (exp))
   વૃક્ષ_NO_TRAMPOLINE (exp2) = 1;

  પાછા exp2;
}

/* Mark EXP as read, not just set, for set but not used -Wunused
   warning purposes.  */

શૂન્ય
mark_exp_read (વૃક્ષ exp)
{
  પસંદગી (વૃક્ષ_CODE (exp))
    {
    સ્થિતિ VAR_DECL:
    સ્થિતિ PARM_DECL:
      DECL_READ_P (exp) = 1;
      તોડો;
    CASE_CONVERT:
      જો (VOID_TYPE_P (વૃક્ષ_TYPE (exp)))
	પસંદગી (વૃક્ષ_CODE (વૃક્ષ_OPERAND (exp, 0)))
	  {
	  સ્થિતિ PREINCREMENT_પદાવલિ:
	  સ્થિતિ PREDECREMENT_પદાવલિ:
	  સ્થિતિ POSTINCREMENT_પદાવલિ:
	  સ્થિતિ POSTDECREMENT_પદાવલિ:
	    પાછા;
	  મૂળભૂત:
	    તોડો;
	  }
      /* FALLTHRU */
    સ્થિતિ ARRAY_REF:
    સ્થિતિ COMPONENT_REF:
    સ્થિતિ MODIFY_પદાવલિ:
    સ્થિતિ REALPART_પદાવલિ:
    સ્થિતિ IMAGPART_પદાવલિ:
    સ્થિતિ ADDR_પદાવલિ:
    સ્થિતિ VIEW_CONVERT_પદાવલિ:
    સ્થિતિ PREINCREMENT_પદાવલિ:
    સ્થિતિ PREDECREMENT_પદાવલિ:
    સ્થિતિ POSTINCREMENT_પદાવલિ:
    સ્થિતિ POSTDECREMENT_પદાવલિ:
      mark_exp_read (વૃક્ષ_OPERAND (exp, 0));
      તોડો;
    સ્થિતિ COMPOUND_પદાવલિ:
      /* Pattern match what build_atomic_assign produces with modifycode
	 NOP_EXPR.  */
      જો (VAR_P (વૃક્ષ_OPERAND (exp, 1))
	  && DECL_ARTIFICIAL (વૃક્ષ_OPERAND (exp, 1))
	  && વૃક્ષ_CODE (વૃક્ષ_OPERAND (exp, 0)) == COMPOUND_પદાવલિ)
	{
	  વૃક્ષ t1 = વૃક્ષ_OPERAND (વૃક્ષ_OPERAND (exp, 0), 0);
	  વૃક્ષ t2 = વૃક્ષ_OPERAND (વૃક્ષ_OPERAND (exp, 0), 1);
	  જો (વૃક્ષ_CODE (t1) == TARGET_પદાવલિ
	      && TARGET_પદાવલિ_SLOT (t1) == વૃક્ષ_OPERAND (exp, 1)
	      && વૃક્ષ_CODE (t2) == CALL_પદાવલિ)
	    {
	      વૃક્ષ fndecl = get_callee_fndecl (t2);
	      વૃક્ષ arg = NULL_વૃક્ષ;
	      જો (fndecl
		  && વૃક્ષ_CODE (fndecl) == FUNCTION_DECL
		  && fndecl_built_in_p (fndecl, BUILT_IN_NORMAL)
		  && call_પદાવલિ_nargs (t2) >= 2)
		પસંદગી (DECL_FUNCTION_CODE (fndecl))
		  {
		  સ્થિતિ BUILT_IN_ATOMIC_STORE:
		    arg = CALL_પદાવલિ_ARG (t2, 1);
		    તોડો;
		  સ્થિતિ BUILT_IN_ATOMIC_STORE_1:
		  સ્થિતિ BUILT_IN_ATOMIC_STORE_2:
		  સ્થિતિ BUILT_IN_ATOMIC_STORE_4:
		  સ્થિતિ BUILT_IN_ATOMIC_STORE_8:
		  સ્થિતિ BUILT_IN_ATOMIC_STORE_16:
		    arg = CALL_પદાવલિ_ARG (t2, 0);
		    તોડો;
		  મૂળભૂત:
		    તોડો;
		  }
	      જો (arg)
		{
		  STRIP_NOPS (arg);
		  જો (વૃક્ષ_CODE (arg) == ADDR_પદાવલિ
		      && DECL_P (વૃક્ષ_OPERAND (arg, 0))
		      && TYPE_ATOMIC (વૃક્ષ_TYPE (વૃક્ષ_OPERAND (arg, 0))))
		    mark_exp_read (વૃક્ષ_OPERAND (arg, 0));
		}
	    }
	}
      /* FALLTHRU */
    સ્થિતિ C_MAYBE_CONST_પદાવલિ:
      mark_exp_read (વૃક્ષ_OPERAND (exp, 1));
      તોડો;
    સ્થિતિ OMP_ARRAY_SECTION:
      mark_exp_read (વૃક્ષ_OPERAND (exp, 0));
      જો (વૃક્ષ_OPERAND (exp, 1))
	mark_exp_read (વૃક્ષ_OPERAND (exp, 1));
      જો (વૃક્ષ_OPERAND (exp, 2))
	mark_exp_read (વૃક્ષ_OPERAND (exp, 2));
      તોડો;
    મૂળભૂત:
      તોડો;
    }
}

/* Perform the default conversion of arrays and functions to pointers.
   Return the result of converting EXP.  For any other expression, just
   return EXP.

   LOC is the location of the expression.  */

સંરચના c_પદાવલિ
default_function_array_conversion (location_t loc, સંરચના c_પદાવલિ exp)
{
  વૃક્ષ orig_exp = exp.કિંમત;
  વૃક્ષ type = વૃક્ષ_TYPE (exp.કિંમત);
  ગણના વૃક્ષ_code code = વૃક્ષ_CODE (type);

  પસંદગી (code)
    {
    સ્થિતિ ARRAY_TYPE:
      {
	તાર્કિક not_lvalue = ખોટું;
	તાર્કિક lvalue_array_p;

	જ્યારે ((વૃક્ષ_CODE (exp.કિંમત) == NON_LVALUE_પદાવલિ
		|| CONVERT_પદાવલિ_P (exp.કિંમત))
	       && વૃક્ષ_TYPE (વૃક્ષ_OPERAND (exp.કિંમત, 0)) == type)
	  {
	    જો (વૃક્ષ_CODE (exp.કિંમત) == NON_LVALUE_પદાવલિ)
	      not_lvalue = સાચું;
	    exp.કિંમત = વૃક્ષ_OPERAND (exp.કિંમત, 0);
	  }

	copy_warning (exp.કિંમત, orig_exp);

	lvalue_array_p = !not_lvalue && lvalue_p (exp.કિંમત);
	જો (!flag_isoc99 && !lvalue_array_p)
	  {
	    /* Before C99, non-lvalue arrays do not decay to pointers.
	       Normally, using such an array would be invalid; but it can
	       be used correctly inside sizeof or as a statement expression.
	       Thus, do not give an error here; an error will result later.  */
	    પાછા exp;
	  }

	exp.કિંમત = array_to_pointer_conversion (loc, exp.કિંમત);
      }
      તોડો;
    સ્થિતિ FUNCTION_TYPE:
      exp.કિંમત = function_to_pointer_conversion (loc, exp.કિંમત);
      તોડો;
    મૂળભૂત:
      તોડો;
    }

  પાછા exp;
}

સંરચના c_પદાવલિ
default_function_array_read_conversion (location_t loc, સંરચના c_પદાવલિ exp)
{
  mark_exp_read (exp.કિંમત);
  /* We only generate a call to .ACCESS_WITH_SIZE when it is a read.  */
  જો (વૃક્ષ_CODE (exp.કિંમત) == COMPONENT_REF
      && handle_counted_by_p (exp.કિંમત))
    exp.કિંમત = handle_counted_by_for_component_ref (loc, exp.કિંમત);
  પાછા default_function_array_conversion (loc, exp);
}

/* Return whether EXPR should be treated as an atomic lvalue for the
   purposes of load and store handling.  */

સ્થિર તાર્કિક
really_atomic_lvalue (વૃક્ષ પદાવલિ)
{
  જો (error_operand_p (પદાવલિ))
    પાછા ખોટું;
  જો (!TYPE_ATOMIC (વૃક્ષ_TYPE (પદાવલિ)))
    પાછા ખોટું;
  જો (!COMPLETE_TYPE_P (વૃક્ષ_TYPE (પદાવલિ)))
    પાછા ખોટું;
  જો (!lvalue_p (પદાવલિ))
    પાછા ખોટું;

  /* Ignore _Atomic on register variables, since their addresses can't
     be taken so (a) atomicity is irrelevant and (b) the normal atomic
     sequences wouldn't work.  Ignore _Atomic on structures containing
     bit-fields, since accessing elements of atomic structures or
     unions is undefined behavior (C11 6.5.2.3#5), but it's unclear if
     it's undefined at translation time or execution time, and the
     normal atomic sequences again wouldn't work.  */
  જ્યારે (handled_component_p (પદાવલિ))
    {
      જો (વૃક્ષ_CODE (પદાવલિ) == COMPONENT_REF
	  && DECL_C_BIT_FIELD (વૃક્ષ_OPERAND (પદાવલિ, 1)))
	પાછા ખોટું;
      પદાવલિ = વૃક્ષ_OPERAND (પદાવલિ, 0);
    }
  જો (વૃક્ષ_CODE (પદાવલિ) == COMPOUND_LITERAL_પદાવલિ)
    પદાવલિ = COMPOUND_LITERAL_પદાવલિ_DECL (પદાવલિ);
  જો (DECL_P (પદાવલિ) && C_DECL_REGISTER (પદાવલિ))
    પાછા ખોટું;
  પાછા સાચું;
}

/* If EXPR is a named constant (C23) derived from a constexpr variable
   - that is, a reference to such a variable, or a member extracted by
   a sequence of structure and union (but not array) member accesses
   (where union member accesses must access the same member as
   initialized) - then return the corresponding initializer;
   otherwise, return NULL_TREE.  */

સ્થિર વૃક્ષ
maybe_get_constexpr_init (વૃક્ષ પદાવલિ)
{
  વૃક્ષ decl = NULL_વૃક્ષ;
  જો (વૃક્ષ_CODE (પદાવલિ) == VAR_DECL)
    decl = પદાવલિ;
  નહીંતર જો (વૃક્ષ_CODE (પદાવલિ) == COMPOUND_LITERAL_પદાવલિ)
    decl = COMPOUND_LITERAL_પદાવલિ_DECL (પદાવલિ);
  જો (decl
      && C_DECL_DECLARED_CONSTEXPR (decl)
      && DECL_INITIAL (decl) != NULL_વૃક્ષ
      && !error_operand_p (DECL_INITIAL (decl)))
    પાછા DECL_INITIAL (decl);
  જો (વૃક્ષ_CODE (પદાવલિ) != COMPONENT_REF)
    પાછા NULL_વૃક્ષ;
  વૃક્ષ inner = maybe_get_constexpr_init (વૃક્ષ_OPERAND (પદાવલિ, 0));
  જો (inner == NULL_વૃક્ષ)
    પાછા NULL_વૃક્ષ;
  જ્યારે ((CONVERT_પદાવલિ_P (inner) || વૃક્ષ_CODE (inner) == NON_LVALUE_પદાવલિ)
	 && !error_operand_p (inner)
	 && (TYPE_MAIN_VARIANT (વૃક્ષ_TYPE (inner))
	     == TYPE_MAIN_VARIANT (વૃક્ષ_TYPE (વૃક્ષ_OPERAND (inner, 0)))))
    inner = વૃક્ષ_OPERAND (inner, 0);
  જો (વૃક્ષ_CODE (inner) != CONSTRUCTOR)
    પાછા NULL_વૃક્ષ;
  વૃક્ષ field = વૃક્ષ_OPERAND (પદાવલિ, 1);
  unsigned HOST_WIDE_INT cidx;
  વૃક્ષ cfield, cvalue;
  તાર્કિક have_other_init = ખોટું;
  FOR_EACH_CONSTRUCTOR_ELT (CONSTRUCTOR_ELTS (inner), cidx, cfield, cvalue)
    {
      જો (cfield == field)
	પાછા cvalue;
      have_other_init = સાચું;
    }
  જો (વૃક્ષ_CODE (વૃક્ષ_TYPE (inner)) == UNION_TYPE
      && (have_other_init || field != TYPE_FIELDS (વૃક્ષ_TYPE (inner))))
    પાછા NULL_વૃક્ષ;
  /* Return a default initializer.  */
  જો (RECORD_OR_UNION_TYPE_P (વૃક્ષ_TYPE (પદાવલિ)))
    પાછા build_constructor (વૃક્ષ_TYPE (પદાવલિ), ખાલી);
  પાછા build_zero_cst (વૃક્ષ_TYPE (પદાવલિ));
}

/* Helper function for convert_lvalue_to_rvalue called via
   walk_tree_without_duplicates.  Find DATA inside of the expression.  */

સ્થિર વૃક્ષ
c_find_var_r (વૃક્ષ *tp, પૂર્ણાંક *walk_subtrees, શૂન્ય *data)
{
  જો (TYPE_P (*tp))
    *walk_subtrees = 0;
  નહીંતર જો (*tp == (વૃક્ષ) data)
    પાછા *tp;
  પાછા NULL_વૃક્ષ;
}

/* Convert expression EXP (location LOC) from lvalue to rvalue,
   including converting functions and arrays to pointers if CONVERT_P.
   If READ_P, also mark the expression as having been read.  If
   FOR_INIT, constexpr expressions of structure and union type should
   be replaced by the corresponding CONSTRUCTOR; otherwise, only
   constexpr scalars (including elements of structures and unions) are
   replaced by their initializers.  */

સંરચના c_પદાવલિ
convert_lvalue_to_rvalue (location_t loc, સંરચના c_પદાવલિ exp,
			  તાર્કિક convert_p, તાર્કિક read_p, તાર્કિક for_init)
{
  તાર્કિક force_non_npc = ખોટું;
  જો (read_p)
    mark_exp_read (exp.કિંમત);
  /* We only generate a call to .ACCESS_WITH_SIZE when it is a read.  */
  જો (read_p && વૃક્ષ_CODE (exp.કિંમત) == COMPONENT_REF
      && handle_counted_by_p (exp.કિંમત))
    exp.કિંમત = handle_counted_by_for_component_ref (loc, exp.કિંમત);

  જો (convert_p)
    exp = default_function_array_conversion (loc, exp);
  જો (!VOID_TYPE_P (વૃક્ષ_TYPE (exp.કિંમત))
      || (flag_isoc2y
	  && TYPE_QUALS (વૃક્ષ_TYPE (exp.કિંમત)) != TYPE_UNQUALIFIED))
    exp.કિંમત = require_complete_type (loc, exp.કિંમત);
  જો (for_init || !RECORD_OR_UNION_TYPE_P (વૃક્ષ_TYPE (exp.કિંમત)))
    {
      વૃક્ષ init = maybe_get_constexpr_init (exp.કિંમત);
      જો (init != NULL_વૃક્ષ)
	{
	  /* A named constant of pointer type or type nullptr_t is not
	     a null pointer constant even if the initializer is
	     one.  */
	  જો (વૃક્ષ_CODE (init) == INTEGER_CST
	      && !INTEGRAL_TYPE_P (વૃક્ષ_TYPE (init))
	      && integer_zerop (init))
	    force_non_npc = સાચું;
	  exp.કિંમત = init;
	}
    }
  જો (really_atomic_lvalue (exp.કિંમત))
    {
      vec<વૃક્ષ, va_gc> *params;
      વૃક્ષ nonatomic_type, tmp, tmp_addr, fndecl, func_call;
      વૃક્ષ પદાવલિ_type = વૃક્ષ_TYPE (exp.કિંમત);
      વૃક્ષ પદાવલિ_addr = build_unary_op (loc, ADDR_પદાવલિ, exp.કિંમત, ખોટું);
      વૃક્ષ seq_cst = build_int_cst (integer_type_ગાંઠ, MEMMODEL_SEQ_CST);

      gcc_assert (TYPE_ATOMIC (પદાવલિ_type));

      /* Expansion of a generic atomic load may require an addition
	 element, so allocate enough to prevent a resize.  */
      vec_alloc (params, 4);

      /* Remove the qualifiers for the rest of the expressions and
	 create the VAL temp variable to hold the RHS.  */
      nonatomic_type = build_qualified_type (પદાવલિ_type, TYPE_UNQUALIFIED);
      tmp = create_tmp_var_raw (nonatomic_type);
      tmp_addr = build_unary_op (loc, ADDR_પદાવલિ, tmp, ખોટું);
      વૃક્ષ_ADDRESSABLE (tmp) = 1;
      /* Do not disable warnings for TMP even though it's artificial.
	 -Winvalid-memory-model depends on it.  */

      /* Issue __atomic_load (&expr, &tmp, SEQ_CST);  */
      fndecl = builtin_decl_explicit (BUILT_IN_ATOMIC_LOAD);
      params->quick_ધકેલો (પદાવલિ_addr);
      params->quick_ધકેલો (tmp_addr);
      params->quick_ધકેલો (seq_cst);
      func_call = c_build_function_call_vec (loc, vNULL, fndecl, params, ખાલી);

      /* EXPR is always read.  */
      mark_exp_read (exp.કિંમત);

      /* Optimize the common case where c_build_function_call_vec
	 immediately folds __atomic_load (&expr, &tmp, SEQ_CST); into
	 tmp = __atomic_load_<N> (&expr, SEQ_CST);
	 In that case tmp is not addressable and can be initialized
	 fully by the rhs of the MODIFY_EXPR.  */
      વૃક્ષ tem = func_call;
      જો (CONVERT_પદાવલિ_P (tem) && VOID_TYPE_P (વૃક્ષ_TYPE (tem)))
	{
	  tem = વૃક્ષ_OPERAND (tem, 0);
	  જો (વૃક્ષ_CODE (tem) == MODIFY_પદાવલિ
	      && વૃક્ષ_OPERAND (tem, 0) == tmp
	      && !walk_વૃક્ષ_without_duplicates (&વૃક્ષ_OPERAND (tem, 1),
						c_find_var_r, tmp))
	    {
	      વૃક્ષ_ADDRESSABLE (tmp) = 0;
	      func_call = વૃક્ષ_OPERAND (tem, 1);
	    }
	}

      /* Return tmp which contains the value loaded.  */
      exp.કિંમત = build4 (TARGET_પદાવલિ, nonatomic_type, tmp, func_call,
			  NULL_વૃક્ષ, NULL_વૃક્ષ);
    }
  જો (convert_p && !error_operand_p (exp.કિંમત)
      && (વૃક્ષ_CODE (વૃક્ષ_TYPE (exp.કિંમત)) != ARRAY_TYPE))
    exp.કિંમત = convert (build_qualified_type (વૃક્ષ_TYPE (exp.કિંમત), TYPE_UNQUALIFIED), exp.કિંમત);
  જો (force_non_npc)
    exp.કિંમત = build1 (NOP_પદાવલિ, વૃક્ષ_TYPE (exp.કિંમત), exp.કિંમત);

  {
    વૃક્ષ false_કિંમત, true_કિંમત;
    જો (convert_p && !error_operand_p (exp.કિંમત)
	&& c_hardbool_type_attr (વૃક્ષ_TYPE (exp.કિંમત),
				 &false_કિંમત, &true_કિંમત))
      {
	વૃક્ષ t = save_પદાવલિ (exp.કિંમત);

	mark_exp_read (exp.કિંમત);

	વૃક્ષ trapfn = builtin_decl_explicit (BUILT_IN_TRAP);
	વૃક્ષ પદાવલિ = build_call_પદાવલિ_loc (loc, trapfn, 0);
	પદાવલિ = build_compound_પદાવલિ (loc, પદાવલિ, boolean_true_ગાંઠ);
	પદાવલિ = fold_build3_loc (loc, COND_પદાવલિ, boolean_type_ગાંઠ,
				fold_build2_loc (loc, NE_પદાવલિ,
						 boolean_type_ગાંઠ,
						 t, true_કિંમત),
				પદાવલિ, boolean_true_ગાંઠ);
	પદાવલિ = fold_build3_loc (loc, COND_પદાવલિ, boolean_type_ગાંઠ,
				fold_build2_loc (loc, NE_પદાવલિ,
						 boolean_type_ગાંઠ,
						 t, false_કિંમત),
				પદાવલિ, boolean_false_ગાંઠ);

	exp.કિંમત = પદાવલિ;
      }
  }

  પાછા exp;
}

/* Wrapper for the overload above, same arguments but for tree rather than
   c_expr.  This is important for hardbools to decay to bools.  */

સ્થિર અંતઃરેખ વૃક્ષ
convert_lvalue_to_rvalue (location_t loc, વૃક્ષ val,
			  તાર્કિક convert_p, તાર્કિક read_p, તાર્કિક for_init = ખોટું)
{
  સંરચના c_પદાવલિ પદાવલિ;
  memset (&પદાવલિ, 0, કદ (પદાવલિ));
  પદાવલિ.કિંમત = val;
  પદાવલિ = convert_lvalue_to_rvalue (loc, પદાવલિ, convert_p, read_p, for_init);
  પાછા પદાવલિ.કિંમત;
}

/* EXP is an expression of integer type.  Apply the integer promotions
   to it and return the promoted value.  */

વૃક્ષ
perform_integral_promotions (વૃક્ષ exp)
{
  વૃક્ષ type = વૃક્ષ_TYPE (exp);
  ગણના વૃક્ષ_code code = વૃક્ષ_CODE (type);

  gcc_assert (INTEGRAL_TYPE_P (type));

  /* Convert enums to the result of applying the integer promotions to
     their underlying type.  */
  જો (code == ENUMERAL_TYPE)
    {
      type = ENUM_UNDERLYING_TYPE (type);
      જો (c_promoting_integer_type_p (type))
	{
	  જો (TYPE_UNSIGNED (type)
	      && TYPE_PRECISION (type) == TYPE_PRECISION (integer_type_ગાંઠ))
	    type = unsigned_type_ગાંઠ;
	  નહીંતર
	    type = integer_type_ગાંઠ;
	}

      પાછા convert (type, exp);
    }

  /* ??? This should no longer be needed now bit-fields have their
     proper types.  */
  જો (વૃક્ષ_CODE (exp) == COMPONENT_REF
      && DECL_C_BIT_FIELD (વૃક્ષ_OPERAND (exp, 1)))
    {
      જો (BITINT_TYPE_P (DECL_BIT_FIELD_TYPE (વૃક્ષ_OPERAND (exp, 1))))
	{
	  વૃક્ષ btype = DECL_BIT_FIELD_TYPE (વૃક્ષ_OPERAND (exp, 1));
	  જો (વૃક્ષ_CODE (btype) == BITINT_TYPE)
	    પાછા convert (btype, exp);
	  નહીંતર
	    પાછા convert (ENUM_UNDERLYING_TYPE (btype), exp);
	}
      /* If it's thinner than an int, promote it like a
	 c_promoting_integer_type_p, otherwise leave it alone.  */
      જો (compare_વૃક્ષ_int (DECL_SIZE (વૃક્ષ_OPERAND (exp, 1)),
			    TYPE_PRECISION (integer_type_ગાંઠ)) < 0)
	પાછા convert (integer_type_ગાંઠ, exp);
    }

  જો (c_promoting_integer_type_p (type))
    {
      /* Preserve unsignedness if not really getting any wider.  */
      જો (TYPE_UNSIGNED (type)
	  && TYPE_PRECISION (type) == TYPE_PRECISION (integer_type_ગાંઠ))
	પાછા convert (unsigned_type_ગાંઠ, exp);

      પાછા convert (integer_type_ગાંઠ, exp);
    }

  પાછા exp;
}


/* Perform default promotions for C data used in expressions.
   Enumeral types or short or char are converted to int.
   In addition, manifest constants symbols are replaced by their values.  */

વૃક્ષ
default_conversion (વૃક્ષ exp)
{
  વૃક્ષ orig_exp;
  વૃક્ષ type = વૃક્ષ_TYPE (exp);
  ગણના વૃક્ષ_code code = વૃક્ષ_CODE (type);
  વૃક્ષ promoted_type;

  mark_exp_read (exp);
  /* We only generate a call to .ACCESS_WITH_SIZE when it is a read.  */
  જો (વૃક્ષ_CODE (exp) == COMPONENT_REF
      && handle_counted_by_p (exp))
    exp = handle_counted_by_for_component_ref (પદાવલિ_LOCATION (exp), exp);

  /* Functions and arrays have been converted during parsing.  */
  gcc_assert (code != FUNCTION_TYPE);
  જો (code == ARRAY_TYPE)
    પાછા exp;

  /* Constants can be used directly unless they're not loadable.  */
  જો (વૃક્ષ_CODE (exp) == CONST_DECL)
    exp = DECL_INITIAL (exp);

  /* Strip no-op conversions.  */
  orig_exp = exp;
  STRIP_TYPE_NOPS (exp);

  copy_warning (exp, orig_exp);

  જો (code == VOID_TYPE)
    {
      error_at (પદાવલિ_LOC_OR_LOC (exp, આગત_location),
		"void value not ignored as it ought to be");
      પાછા error_mark_ગાંઠ;
    }

  exp = require_complete_type (પદાવલિ_LOC_OR_LOC (exp, આગત_location), exp);
  જો (exp == error_mark_ગાંઠ)
    પાછા error_mark_ગાંઠ;

  promoted_type = targetm.promoted_type (type);
  જો (promoted_type)
    પાછા convert (promoted_type, exp);

  જો (INTEGRAL_TYPE_P (type))
    {
      /* Avoid performing integral promotion of bit-precise integer
	 type bit-field to its corresponding bit-precise integer if
	 orig_exp is a cast to it to its underlying type.  */
      જો (orig_exp != exp
	  && વૃક્ષ_CODE (exp) == COMPONENT_REF
	  && DECL_C_BIT_FIELD (વૃક્ષ_OPERAND (exp, 1))
	  && BITINT_TYPE_P (DECL_BIT_FIELD_TYPE (વૃક્ષ_OPERAND (exp, 1))))
	પાછા perform_integral_promotions (orig_exp);
      પાછા perform_integral_promotions (exp);
    }

  પાછા exp;
}

/* Look up COMPONENT in a structure or union TYPE.

   If the component name is not found, returns NULL_TREE.  Otherwise,
   the return value is a TREE_LIST, with each TREE_VALUE a FIELD_DECL
   stepping down the chain to the component, which is in the last
   TREE_VALUE of the list.  Normally the list is of length one, but if
   the component is embedded within (nested) anonymous structures or
   unions, the list steps down the chain to the component.  */

વૃક્ષ
lookup_field (const_વૃક્ષ type, વૃક્ષ component)
{
  વૃક્ષ field;

  /* If TYPE_LANG_SPECIFIC is set, then it is a sorted array of pointers
     to the field elements.  Use a binary search on this array to quickly
     find the element.  Otherwise, do a linear search.  TYPE_LANG_SPECIFIC
     will always be set for structures which have many elements.

     Duplicate field checking replaces duplicates with NULL_TREE so
     TYPE_LANG_SPECIFIC arrays are potentially no longer sorted.  In that
     case just iterate using DECL_CHAIN.  */

  જો (TYPE_LANG_SPECIFIC (type) && TYPE_LANG_SPECIFIC (type)->s
      && !seen_error ())
    {
      પૂર્ણાંક bot, ટોચ, half;
      વૃક્ષ *field_array = &TYPE_LANG_SPECIFIC (type)->s->elts[0];

      field = TYPE_FIELDS (type);
      bot = 0;
      ટોચ = TYPE_LANG_SPECIFIC (type)->s->len;
      જ્યારે (ટોચ - bot > 1)
	{
	  half = (ટોચ - bot + 1) >> 1;
	  field = field_array[bot+half];

	  જો (DECL_NAME (field) == NULL_વૃક્ષ)
	    {
	      /* Step through all anon unions in linear fashion.  */
	      જ્યારે (DECL_NAME (field_array[bot]) == NULL_વૃક્ષ)
		{
		  field = field_array[bot++];
		  જો (RECORD_OR_UNION_TYPE_P (વૃક્ષ_TYPE (field)))
		    {
		      વૃક્ષ anon = lookup_field (વૃક્ષ_TYPE (field), component);

		      જો (anon)
			પાછા વૃક્ષ_cons (NULL_વૃક્ષ, field, anon);

		      /* The Plan 9 compiler permits referring
			 directly to an anonymous struct/union field
			 using a typedef name.  */
		      જો (flag_plan9_extensions
			  && TYPE_NAME (વૃક્ષ_TYPE (field)) != NULL_વૃક્ષ
			  && (વૃક્ષ_CODE (TYPE_NAME (વૃક્ષ_TYPE (field)))
			      == TYPE_DECL)
			  && (DECL_NAME (TYPE_NAME (વૃક્ષ_TYPE (field)))
			      == component))
			તોડો;
		    }
		}

	      /* Entire record is only anon unions.  */
	      જો (bot > ટોચ)
		પાછા NULL_વૃક્ષ;

	      /* Restart the binary search, with new lower bound.  */
	      ચાલુ;
	    }

	  જો (DECL_NAME (field) == component)
	    તોડો;
	  જો (DECL_NAME (field) < component)
	    bot += half;
	  નહીંતર
	    ટોચ = bot + half;
	}

      જો (DECL_NAME (field_array[bot]) == component)
	field = field_array[bot];
      નહીંતર જો (DECL_NAME (field) != component)
	પાછા NULL_વૃક્ષ;
    }
  નહીંતર
    {
      માટે (field = TYPE_FIELDS (type); field; field = DECL_CHAIN (field))
	{
	  જો (DECL_NAME (field) == NULL_વૃક્ષ
	      && RECORD_OR_UNION_TYPE_P (વૃક્ષ_TYPE (field)))
	    {
	      વૃક્ષ anon = lookup_field (વૃક્ષ_TYPE (field), component);

	      જો (anon)
		પાછા વૃક્ષ_cons (NULL_વૃક્ષ, field, anon);

	      /* The Plan 9 compiler permits referring directly to an
		 anonymous struct/union field using a typedef
		 name.  */
	      જો (flag_plan9_extensions
		  && TYPE_NAME (વૃક્ષ_TYPE (field)) != NULL_વૃક્ષ
		  && વૃક્ષ_CODE (TYPE_NAME (વૃક્ષ_TYPE (field))) == TYPE_DECL
		  && (DECL_NAME (TYPE_NAME (વૃક્ષ_TYPE (field)))
		      == component))
		તોડો;
	    }

	  જો (DECL_NAME (field) == component)
	    તોડો;
	}

      જો (field == NULL_વૃક્ષ)
	પાછા NULL_વૃક્ષ;
    }

  પાછા વૃક્ષ_cons (NULL_વૃક્ષ, field, NULL_વૃક્ષ);
}

/* Recursively append candidate IDENTIFIER_NODEs to CANDIDATES.  */

સ્થિર શૂન્ય
lookup_field_fuzzy_find_candidates (વૃક્ષ type, વૃક્ષ component,
				    vec<વૃક્ષ> *candidates)
{
  વૃક્ષ field;
  માટે (field = TYPE_FIELDS (type); field; field = DECL_CHAIN (field))
    {
      જો (DECL_NAME (field) == NULL_વૃક્ષ
	  && RECORD_OR_UNION_TYPE_P (વૃક્ષ_TYPE (field)))
	lookup_field_fuzzy_find_candidates (વૃક્ષ_TYPE (field), component,
					    candidates);

      જો (DECL_NAME (field))
	candidates->safe_ધકેલો (DECL_NAME (field));
    }
}

/* Like "lookup_field", but find the closest matching IDENTIFIER_NODE,
   rather than returning a TREE_LIST for an exact match.  */

સ્થિર વૃક્ષ
lookup_field_fuzzy (વૃક્ષ type, વૃક્ષ component)
{
  gcc_assert (વૃક્ષ_CODE (component) == IDENTIFIER_ગાંઠ);

  /* First, gather a list of candidates.  */
  auto_vec <વૃક્ષ> candidates;

  lookup_field_fuzzy_find_candidates (type, component,
				      &candidates);

  પાછા find_closest_identifier (component, &candidates);
}

/* Support function for build_component_ref's error-handling.

   Given DATUM_TYPE, and "DATUM.COMPONENT", where DATUM is *not* a
   struct or union, should we suggest "DATUM->COMPONENT" as a hint?  */

સ્થિર તાર્કિક
should_suggest_deref_p (વૃક્ષ datum_type)
{
  /* We don't do it for Objective-C, since Objective-C 2.0 dot-syntax
     allows "." for ptrs; we could be handling a failed attempt
     to access a property.  */
  જો (c_dialect_objc ())
    પાછા ખોટું;

  /* Only suggest it for pointers...  */
  જો (વૃક્ષ_CODE (datum_type) != POINTER_TYPE)
    પાછા ખોટું;

  /* ...to structs/unions.  */
  વૃક્ષ underlying_type = વૃક્ષ_TYPE (datum_type);
  ગણના વૃક્ષ_code code = વૃક્ષ_CODE (underlying_type);
  જો (code == RECORD_TYPE || code == UNION_TYPE)
    પાછા સાચું;
  નહીંતર
    પાછા ખોટું;
}

/* Give a component ref REF, decide whether we should handle its counted_by
   attribute based on its context:
   Do not handle counted_by when in offsetof, typeof and alignof operator.  */

સ્થિર તાર્કિક
handle_counted_by_p (વૃક્ષ ref)
{
  gcc_assert (વૃક્ષ_CODE (ref) == COMPONENT_REF);
  વૃક્ષ datum = વૃક્ષ_OPERAND (ref, 0);
  /* If the component_ref is build for a offsetof, i.e., the datum
     of the component_ref is a indirect_ref of null_pointer_node,
     we should not generate call to .ACCESS_WITH_SIZE.  */
  જો (વૃક્ષ_CODE (datum) == INDIRECT_REF
      && વૃક્ષ_OPERAND (datum, 0) == null_pointer_ગાંઠ)
    પાછા ખોટું;
  જો (in_typeof || in_alignof)
    પાછા ખોટું;
  પાછા સાચું;
}

/* Given a component ref REF, if there is a counted_by attribute attached,
   issue error when the element_type is a structure or union including a
   flexible array member.  */

સ્થિર શૂન્ય
check_counted_by_attribute (location_t loc, વૃક્ષ ref)
{
  વૃક્ષ subdatum = વૃક્ષ_OPERAND (ref, 1);
  વૃક્ષ sub_type = વૃક્ષ_TYPE (subdatum);

  જો (!flexible_array_member_type_p (sub_type)
      && વૃક્ષ_CODE (sub_type) != POINTER_TYPE)
    પાછા;

  વૃક્ષ element_type = વૃક્ષ_TYPE (sub_type);

  વૃક્ષ attr_counted_by = lookup_attribute ("counted_by",
					   DECL_ATTRIBUTES (subdatum));
  જો (attr_counted_by)
    {
      /* Issue error when the element_type is a structure or
	union including a flexible array member.  */
      જો (RECORD_OR_UNION_TYPE_P (element_type)
	  && TYPE_INCLUDES_FLEXARRAY (element_type))
	{
	  error_at (loc,
		    "%<counted_by%> attribute is not allowed for a pointer to"
		    " structure or union with flexible array member");
	  પાછા;
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

સ્થિર વૃક્ષ
build_counted_by_ref (વૃક્ષ datum, વૃક્ષ subdatum,
		      વૃક્ષ *counted_by_type)
{
  વૃક્ષ sub_type = વૃક્ષ_TYPE (subdatum);
  જો (!flexible_array_member_type_p (sub_type)
      && વૃક્ષ_CODE (sub_type) != POINTER_TYPE)
    પાછા NULL_વૃક્ષ;

  વૃક્ષ attr_counted_by = lookup_attribute ("counted_by",
					   DECL_ATTRIBUTES (subdatum));
  જો (!attr_counted_by)
    પાછા NULL_વૃક્ષ;

  વૃક્ષ counted_by_ref = NULL_વૃક્ષ;
  *counted_by_type = NULL_વૃક્ષ;

  વૃક્ષ type = વૃક્ષ_TYPE (datum);

  /* If the type of the containing structure is an anonymous struct/union,
     and this anonymous struct/union is not a root type, get the first
     outer named structure/union type.  */
  જ્યારે (વૃક્ષ_CODE (datum) == COMPONENT_REF
	 && c_type_tag (type) == NULL_વૃક્ષ
	 && DECL_NAME (વૃક્ષ_OPERAND (datum, 1)) == NULL_વૃક્ષ)
    {
      datum = વૃક્ષ_OPERAND (datum, 0);
      type = વૃક્ષ_TYPE (datum);
    }

  વૃક્ષ field_id = વૃક્ષ_કિંમત (વૃક્ષ_કિંમત (attr_counted_by));
  વૃક્ષ counted_by_field = lookup_field (type, field_id);
  gcc_assert (counted_by_field);

  વૃક્ષ counted_by_subdatum;
  કરો
    {
      counted_by_subdatum = વૃક્ષ_કિંમત (counted_by_field);
      /* Get the TYPE of the counted_by field.  */
      *counted_by_type = વૃક્ષ_TYPE (counted_by_subdatum);

      counted_by_ref
	= build3 (COMPONENT_REF, વૃક્ષ_TYPE (counted_by_subdatum),
		  datum, counted_by_subdatum, NULL_વૃક્ષ);

      datum = counted_by_ref;
      counted_by_field = વૃક્ષ_CHAIN (counted_by_field);
    }
  જ્યારે (counted_by_field);

  counted_by_ref = build_fold_addr_પદાવલિ (counted_by_ref);
  પાછા counted_by_ref;
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
સ્થિર વૃક્ષ
build_access_with_size_for_counted_by (location_t loc, વૃક્ષ ref,
				       વૃક્ષ counted_by_ref,
				       વૃક્ષ counted_by_type)
{
  gcc_assert (flexible_array_member_type_p (વૃક્ષ_TYPE (ref))
	      || વૃક્ષ_CODE (વૃક્ષ_TYPE (ref)) == POINTER_TYPE);

  તાર્કિક is_fam = flexible_array_member_type_p (વૃક્ષ_TYPE (ref));

  /* The result type of the call is a pointer to the flexible array type;
     or is the original pointer type to the pointer field with counted_by.  */
  વૃક્ષ result_type = is_fam ? c_build_pointer_type (વૃક્ષ_TYPE (ref))
		     : વૃક્ષ_TYPE (ref);

  વૃક્ષ element_type = વૃક્ષ_TYPE (વૃક્ષ_TYPE (ref));
  વૃક્ષ element_size = VOID_TYPE_P (element_type)
		      ? size_one_ગાંઠ
		      : TYPE_SIZE_UNIT (element_type);
  જો (element_size == NULL_વૃક્ષ)
    પાછા ref;

  વૃક્ષ first_param = is_fam
		     ? c_fully_fold (array_to_pointer_conversion (loc, ref),
				     ખોટું, ખાલી)
		     : c_fully_fold (ref, ખોટું, ખાલી);
  વૃક્ષ second_param
    = c_fully_fold (counted_by_ref, ખોટું, ખાલી);
  વૃક્ષ third_param = build_int_cst (c_build_pointer_type (counted_by_type), 0);

  વૃક્ષ call
    = build_call_પદાવલિ_internal_loc (loc, IFN_ACCESS_WITH_SIZE,
				    result_type, 4,
				    first_param,
				    second_param,
				    third_param,
				    element_size);

  /* Wrap the call with an INDIRECT_REF with the flexible array type.  */
  જો (is_fam)
    call = build1 (INDIRECT_REF, વૃક્ષ_TYPE (ref), call);
  SET_પદાવલિ_LOCATION (call, loc);
  પાછા call;
}

/* For the COMPONENT_REF ref, check whether it has a counted_by attribute,
   if so, wrap this COMPONENT_REF with the corresponding CALL to the
   function .ACCESS_WITH_SIZE.
   Otherwise, return the ref itself.  */

વૃક્ષ
handle_counted_by_for_component_ref (location_t loc, વૃક્ષ ref)
{
  gcc_assert (વૃક્ષ_CODE (ref) == COMPONENT_REF);
  વૃક્ષ datum = વૃક્ષ_OPERAND (ref, 0);
  વૃક્ષ subdatum = વૃક્ષ_OPERAND (ref, 1);
  વૃક્ષ counted_by_type = NULL_વૃક્ષ;

  જો (!(flexible_array_member_type_p (વૃક્ષ_TYPE (ref))
	|| વૃક્ષ_CODE (વૃક્ષ_TYPE (ref)) == POINTER_TYPE))
    પાછા ref;

  વૃક્ષ counted_by_ref = build_counted_by_ref (datum, subdatum,
					      &counted_by_type);
  જો (counted_by_ref)
    ref = build_access_with_size_for_counted_by (loc, ref,
						 counted_by_ref,
						 counted_by_type);
  પાછા ref;
}

/* Make an expression to refer to the COMPONENT field of structure or
   union value DATUM.  COMPONENT is an IDENTIFIER_NODE.  LOC is the
   location of the COMPONENT_REF.  COMPONENT_LOC is the location
   of COMPONENT.  ARROW_LOC is the location of the first -> operand if
   it is from -> operator.
   If HANDLE_COUNTED_BY is true, check the counted_by attribute and generate
   a call to .ACCESS_WITH_SIZE.  Otherwise, ignore the attribute.  */

વૃક્ષ
build_component_ref (location_t loc, વૃક્ષ datum, વૃક્ષ component,
		     location_t component_loc, location_t arrow_loc)
{
  વૃક્ષ type = વૃક્ષ_TYPE (datum);
  ગણના વૃક્ષ_code code = વૃક્ષ_CODE (type);
  વૃક્ષ field = ખાલી;
  વૃક્ષ ref;
  તાર્કિક datum_lvalue = lvalue_p (datum);

  જો (!objc_is_public (datum, component))
    પાછા error_mark_ગાંઠ;

  /* Detect Objective-C property syntax object.property.  */
  જો (c_dialect_objc ()
      && (ref = objc_maybe_build_component_ref (datum, component)))
    પાછા ref;

  /* See if there is a field or component with name COMPONENT.  */

  જો (code == RECORD_TYPE || code == UNION_TYPE)
    {
      જો (!COMPLETE_TYPE_P (type))
	{
	  c_incomplete_type_error (loc, NULL_વૃક્ષ, type);
	  પાછા error_mark_ગાંઠ;
	}

      field = lookup_field (type, component);

      જો (!field)
	{
	  વૃક્ષ guessed_id = lookup_field_fuzzy (type, component);
	  જો (guessed_id)
	    {
	      /* Attempt to provide a fixit replacement hint, if
		 we have a valid range for the component.  */
	      location_t reported_loc
		= (component_loc != UNKNOWN_LOCATION) ? component_loc : loc;
	      gcc_rich_location rich_loc (reported_loc);
	      જો (component_loc != UNKNOWN_LOCATION)
		rich_loc.add_fixit_misspelled_id (component_loc, guessed_id);
	      error_at (&rich_loc,
			"%qT has no member named %qE; did you mean %qE?",
			type, component, guessed_id);
	    }
	  નહીંતર
	    error_at (loc, "%qT has no member named %qE", type, component);
	  પાછા error_mark_ગાંઠ;
	}

      /* Accessing elements of atomic structures or unions is undefined
	 behavior (C11 6.5.2.3#5).  */
      જો (TYPE_ATOMIC (type) && c_inhibit_evaluation_warnings == 0)
	{
	  જો (code == RECORD_TYPE)
	    warning_at (loc, 0, "accessing a member %qE of an atomic "
			"structure %qE", component, datum);
	  નહીંતર
	    warning_at (loc, 0, "accessing a member %qE of an atomic "
			"union %qE", component, datum);
	}

      /* Chain the COMPONENT_REFs if necessary down to the FIELD.
	 This might be better solved in future the way the C++ front
	 end does it - by giving the anonymous entities each a
	 separate name and type, and then have build_component_ref
	 recursively call itself.  We can't do that here.  */
      કરો
	{
	  વૃક્ષ subdatum = વૃક્ષ_કિંમત (field);
	  પૂર્ણાંક quals;
	  વૃક્ષ subtype;
	  તાર્કિક use_datum_quals;

	  જો (વૃક્ષ_TYPE (subdatum) == error_mark_ગાંઠ)
	    પાછા error_mark_ગાંઠ;

	  /* If this is an rvalue, it does not have qualifiers in C
	     standard terms and we must avoid propagating such
	     qualifiers down to a non-lvalue array that is then
	     converted to a pointer.  */
	  use_datum_quals = (datum_lvalue
			     || વૃક્ષ_CODE (વૃક્ષ_TYPE (subdatum)) != ARRAY_TYPE);

	  quals = TYPE_QUALS (strip_array_types (વૃક્ષ_TYPE (subdatum)));
	  જો (use_datum_quals)
	    quals |= TYPE_QUALS (વૃક્ષ_TYPE (datum));
	  subtype = c_build_qualified_type (વૃક્ષ_TYPE (subdatum), quals);

	  ref = build3 (COMPONENT_REF, subtype, datum, subdatum,
			NULL_વૃક્ષ);
	  SET_પદાવલિ_LOCATION (ref, loc);

	  check_counted_by_attribute (loc, ref);

	  જો (વૃક્ષ_READONLY (subdatum)
	      || (use_datum_quals && વૃક્ષ_READONLY (datum)))
	    વૃક્ષ_READONLY (ref) = 1;
	  જો (વૃક્ષ_THIS_VOLATILE (subdatum)
	      || (use_datum_quals && વૃક્ષ_THIS_VOLATILE (datum)))
	    વૃક્ષ_THIS_VOLATILE (ref) = 1;

	  જો (વૃક્ષ_UNAVAILABLE (subdatum))
	    error_unavailable_use (subdatum, NULL_વૃક્ષ);
	  નહીંતર જો (વૃક્ષ_DEPRECATED (subdatum))
	    warn_deprecated_use (subdatum, NULL_વૃક્ષ);

	  datum = ref;

	  field = વૃક્ષ_CHAIN (field);
	}
      જ્યારે (field);

      પાછા ref;
    }
  નહીંતર જો (should_suggest_deref_p (type))
    {
      /* Special-case the error message for "ptr.field" for the case
	 where the user has confused "." vs "->".  */
      rich_location richloc (લીટી_table, loc);
      જો (INDIRECT_REF_P (datum) && arrow_loc != UNKNOWN_LOCATION)
	{
	  richloc.add_fixit_ઉમેરો_before (arrow_loc, "(*");
	  richloc.add_fixit_ઉમેરો_after (arrow_loc, ")");
	  error_at (&richloc,
		    "%qE is a pointer to pointer; did you mean to dereference "
		    "it before applying %<->%> to it?",
		    વૃક્ષ_OPERAND (datum, 0));
	}
      નહીંતર
	{
	  /* "loc" should be the "." token.  */
	  richloc.add_fixit_replace ("->");
	  error_at (&richloc,
		    "%qE is a pointer; did you mean to use %<->%>?",
		    datum);
	}
      પાછા error_mark_ગાંઠ;
    }
  નહીંતર જો (code != ERROR_MARK)
    error_at (loc,
	      "request for member %qE in something not a structure or union",
	      component);

  પાછા error_mark_ગાંઠ;
}

/* Given an expression PTR for a pointer, return an expression
   for the value pointed to.
   ERRORSTRING is the name of the operator to appear in error messages.

   LOC is the location to use for the generated tree.  */

વૃક્ષ
build_indirect_ref (location_t loc, વૃક્ષ ptr, ref_operator errstring)
{
  વૃક્ષ pointer = default_conversion (ptr);
  વૃક્ષ type = વૃક્ષ_TYPE (pointer);
  વૃક્ષ ref;

  જો (વૃક્ષ_CODE (type) == POINTER_TYPE)
    {
      જો (CONVERT_પદાવલિ_P (pointer)
          || વૃક્ષ_CODE (pointer) == VIEW_CONVERT_પદાવલિ)
	{
	  /* If a warning is issued, mark it to avoid duplicates from
	     the backend.  This only needs to be done at
	     warn_strict_aliasing > 2.  */
	  જો (warn_strict_aliasing > 2)
	    જો (strict_aliasing_warning (પદાવલિ_LOCATION (pointer),
					 type, વૃક્ષ_OPERAND (pointer, 0)))
	      suppress_warning (pointer, OPT_Wstrict_aliasing_);
	}

      જો (વૃક્ષ_CODE (pointer) == ADDR_પદાવલિ
	  && (વૃક્ષ_TYPE (વૃક્ષ_OPERAND (pointer, 0))
	      == વૃક્ષ_TYPE (type)))
	{
	  ref = વૃક્ષ_OPERAND (pointer, 0);
	  protected_set_પદાવલિ_location (ref, loc);
	  પાછા ref;
	}
      નહીંતર
	{
	  વૃક્ષ t = વૃક્ષ_TYPE (type);

	  ref = build1 (INDIRECT_REF, t, pointer);

	  જો (VOID_TYPE_P (t) && c_inhibit_evaluation_warnings == 0)
	    warning_at (loc, 0, "dereferencing %<void *%> pointer");

	  /* We *must* set TREE_READONLY when dereferencing a pointer to const,
	     so that we get the proper error message if the result is used
	     to assign to.  Also, &* is supposed to be a no-op.
	     And ANSI C seems to specify that the type of the result
	     should be the const type.  */
	  /* A de-reference of a pointer to const is not a const.  It is valid
	     to change it via some other pointer.  */
	  વૃક્ષ_READONLY (ref) = TYPE_READONLY (t);
	  વૃક્ષ_SIDE_EFFECTS (ref)
	    = TYPE_VOLATILE (t) || વૃક્ષ_SIDE_EFFECTS (pointer);
	  વૃક્ષ_THIS_VOLATILE (ref) = TYPE_VOLATILE (t);
	  protected_set_પદાવલિ_location (ref, loc);
	  પાછા ref;
	}
    }
  નહીંતર જો (વૃક્ષ_CODE (pointer) != ERROR_MARK)
    invalid_indirection_error (loc, type, errstring);

  પાછા error_mark_ગાંઠ;
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

વૃક્ષ
build_array_ref (location_t loc, વૃક્ષ array, વૃક્ષ index)
{
  વૃક્ષ ret;
  તાર્કિક swapped = ખોટું;
  જો (વૃક્ષ_TYPE (array) == error_mark_ગાંઠ
      || વૃક્ષ_TYPE (index) == error_mark_ગાંઠ)
    પાછા error_mark_ગાંઠ;

  જો (વૃક્ષ_CODE (વૃક્ષ_TYPE (array)) != ARRAY_TYPE
      && વૃક્ષ_CODE (વૃક્ષ_TYPE (array)) != POINTER_TYPE
      /* Allow vector[index] but not index[vector].  */
      && !gnu_vector_type_p (વૃક્ષ_TYPE (array)))
    {
      જો (વૃક્ષ_CODE (વૃક્ષ_TYPE (index)) != ARRAY_TYPE
	  && વૃક્ષ_CODE (વૃક્ષ_TYPE (index)) != POINTER_TYPE)
	{
          error_at (loc,
            "subscripted value is neither array nor pointer nor vector");

	  પાછા error_mark_ગાંઠ;
	}
      std::swap (array, index);
      swapped = સાચું;
    }

  જો (!INTEGRAL_TYPE_P (વૃક્ષ_TYPE (index)))
    {
      error_at (loc, "array subscript is not an integer");
      પાછા error_mark_ગાંઠ;
    }

  જો (વૃક્ષ_CODE (વૃક્ષ_TYPE (વૃક્ષ_TYPE (array))) == FUNCTION_TYPE)
    {
      error_at (loc, "subscripted value is pointer to function");
      પાછા error_mark_ગાંઠ;
    }

  /* ??? Existing practice has been to warn only when the char
     index is syntactically the index, not for char[array].  */
  જો (!swapped)
     warn_array_subscript_with_type_char (loc, index);

  /* Apply default promotions *after* noticing character types.  */
  index = default_conversion (index);
  જો (index == error_mark_ગાંઠ)
    પાછા error_mark_ગાંઠ;

  gcc_assert (વૃક્ષ_CODE (વૃક્ષ_TYPE (index)) == INTEGER_TYPE
	      || વૃક્ષ_CODE (વૃક્ષ_TYPE (index)) == BITINT_TYPE);

  તાર્કિક was_vector = VECTOR_TYPE_P (વૃક્ષ_TYPE (array));
  તાર્કિક non_lvalue = convert_vector_to_array_for_subscript (loc, &array, index);

  /* We only generate a call to .ACCESS_WITH_SIZE when it is a read.  */
  જો (વૃક્ષ_CODE (array) == COMPONENT_REF
      && handle_counted_by_p (array))
    array = handle_counted_by_for_component_ref (loc, array);

  જો (વૃક્ષ_CODE (વૃક્ષ_TYPE (array)) == ARRAY_TYPE)
    {
      વૃક્ષ rval, type;

      /* An array that is indexed by a non-constant
	 cannot be stored in a register; we must be able to do
	 address arithmetic on its address.
	 Likewise an array of elements of variable size.  */
      જો (વૃક્ષ_CODE (index) != INTEGER_CST
	  || (COMPLETE_TYPE_P (વૃક્ષ_TYPE (વૃક્ષ_TYPE (array)))
	      && વૃક્ષ_CODE (TYPE_SIZE (વૃક્ષ_TYPE (વૃક્ષ_TYPE (array)))) != INTEGER_CST))
	{
	  જો (!c_mark_addressable (array, સાચું, સાચું))
	    પાછા error_mark_ગાંઠ;
	}
      /* An array that is indexed by a constant value which is not within
	 the array bounds cannot be stored in a register either; because we
	 would get a crash in store_bit_field/extract_bit_field when trying
	 to access a non-existent part of the register.  */
      જો (વૃક્ષ_CODE (index) == INTEGER_CST
	  && TYPE_DOMAIN (વૃક્ષ_TYPE (array))
	  && !int_fits_type_p (index, TYPE_DOMAIN (વૃક્ષ_TYPE (array))))
	{
	  જો (!c_mark_addressable (array, ખોટું, સાચું))
	    પાછા error_mark_ગાંઠ;
	  /* ISO C2Y disallows a negative integer constant expression index
	     when array subscripting has an operand of array type.  */
	  જો (flag_isoc2y
	      && !વૃક્ષ_OVERFLOW (index)
	      && વૃક્ષ_int_cst_sgn (index) < 0)
	    error_at (loc, "array subscript is negative");
	}

      જો ((pedantic || warn_c90_c99_compat || warn_c23_c2y_compat)
	  && ! was_vector)
	{
	  વૃક્ષ foo = array;
	  જ્યારે (વૃક્ષ_CODE (foo) == COMPONENT_REF)
	    foo = વૃક્ષ_OPERAND (foo, 0);
	  જો ((VAR_P (foo) && C_DECL_REGISTER (foo))
	      || (વૃક્ષ_CODE (foo) == COMPOUND_LITERAL_પદાવલિ
		  && C_DECL_REGISTER (COMPOUND_LITERAL_પદાવલિ_DECL (foo))))
	    pedwarn_c23 (loc, OPT_Wpedantic,
			 "ISO C forbids subscripting %<register%> array "
			 "before C2Y");
	  નહીંતર જો (!lvalue_p (foo))
	    pedwarn_c90 (loc, OPT_Wpedantic,
			 "ISO C90 forbids subscripting non-lvalue "
			 "array");
	}

      જો (વૃક્ષ_CODE (વૃક્ષ_TYPE (index)) == BITINT_TYPE
	  && TYPE_PRECISION (વૃક્ષ_TYPE (index)) > TYPE_PRECISION (sizetype))
	index = fold_convert (sizetype, index);

      type = વૃક્ષ_TYPE (વૃક્ષ_TYPE (array));
      rval = build4 (ARRAY_REF, type, array, index, NULL_વૃક્ષ, NULL_વૃક્ષ);
      /* Array ref is const/volatile if the array elements are
	 or if the array is.  */
      વૃક્ષ_READONLY (rval)
	|= (TYPE_READONLY (વૃક્ષ_TYPE (વૃક્ષ_TYPE (array)))
	    | વૃક્ષ_READONLY (array));
      વૃક્ષ_SIDE_EFFECTS (rval)
	|= (TYPE_VOLATILE (વૃક્ષ_TYPE (વૃક્ષ_TYPE (array)))
	    | વૃક્ષ_SIDE_EFFECTS (array));
      વૃક્ષ_THIS_VOLATILE (rval)
	|= (TYPE_VOLATILE (વૃક્ષ_TYPE (વૃક્ષ_TYPE (array)))
	    /* This was added by rms on 16 Nov 91.
	       It fixes  vol struct foo *a;  a->elts[1]
	       in an inline function.
	       Hope it doesn't break something else.  */
	    | વૃક્ષ_THIS_VOLATILE (array));
      ret = require_complete_type (loc, rval);
      protected_set_પદાવલિ_location (ret, loc);
      જો (non_lvalue)
	ret = non_lvalue_loc (loc, ret);
      પાછા ret;
    }
  નહીંતર
    {
      વૃક્ષ ar = default_conversion (array);

      જો (ar == error_mark_ગાંઠ)
	પાછા ar;

      gcc_assert (વૃક્ષ_CODE (વૃક્ષ_TYPE (ar)) == POINTER_TYPE);
      gcc_assert (વૃક્ષ_CODE (વૃક્ષ_TYPE (વૃક્ષ_TYPE (ar))) != FUNCTION_TYPE);

      ret = build_indirect_ref (loc, build_દ્વિઅંકી_op (loc, PLUS_પદાવલિ, ar,
						      index, ખોટું),
				RO_ARRAY_INDEXING);
      જો (non_lvalue)
	ret = non_lvalue_loc (loc, ret);
      પાછા ret;
    }
}

/* Build an OpenMP array section reference, creating an exact type for the
   resulting expression based on the element type and bounds if possible.  If
   we have variable bounds, create an incomplete array type for the result
   instead.  */

વૃક્ષ
build_omp_array_section (location_t loc, વૃક્ષ array, વૃક્ષ index, વૃક્ષ length)
{
  વૃક્ષ type = વૃક્ષ_TYPE (array);
  gcc_assert (type);

  વૃક્ષ sectype, eltype = વૃક્ષ_TYPE (type);

  /* It's not an array or pointer type.  Just reuse the type of the original
     expression as the type of the array section (an error will be raised
     anyway, later).  */
  જો (eltype == NULL_વૃક્ષ || error_operand_p (eltype))
    sectype = વૃક્ષ_TYPE (array);
  નહીંતર
    {
      વૃક્ષ idxtype = NULL_વૃક્ષ;

      જો (index != NULL_વૃક્ષ
	  && length != NULL_વૃક્ષ
	  && INTEGRAL_TYPE_P (વૃક્ષ_TYPE (index))
	  && INTEGRAL_TYPE_P (વૃક્ષ_TYPE (length)))
	{
	  વૃક્ષ નીચલું = fold_convert (sizetype, index);
	  વૃક્ષ ઉપલું = fold_convert (sizetype, length);
	  ઉપલું = size_binop (PLUS_પદાવલિ, નીચલું, ઉપલું);
	  ઉપલું = size_binop (MINUS_પદાવલિ, ઉપલું, size_one_ગાંઠ);
	  idxtype = build_range_type (sizetype, નીચલું, ઉપલું);
	}
      નહીંતર જો ((index == NULL_વૃક્ષ || integer_zerop (index))
	       && length != NULL_વૃક્ષ
	       && INTEGRAL_TYPE_P (વૃક્ષ_TYPE (length)))
	idxtype = build_index_type (length);

      gcc_assert (!error_operand_p (idxtype));

      sectype = c_build_array_type (eltype, idxtype);
    }

  પાછા build3_loc (loc, OMP_ARRAY_SECTION, sectype, array, index, length);
}


/* Record that REF is used.  This is relevant for undeclared static
   function and declarations referenced from a non-local context.
   ADDRESS indicates whether the address is taken.  */

શૂન્ય
mark_decl_used (વૃક્ષ ref, તાર્કિક address)
{
  જો (!ref || !DECL_P (ref) || in_alignof)
    પાછા;

  /* Non-file-scope and non-local reference in nested function.  */
  તાર્કિક nonloc_p = current_function_decl && DECL_CONTEXT (ref)
		  && DECL_CONTEXT (current_function_decl)
		  && DECL_CONTEXT (ref) != current_function_decl;

  /* An undeclared static function.  */
  તાર્કિક static_p = વૃક્ષ_CODE (ref) == FUNCTION_DECL
		  && DECL_INITIAL (ref) == NULL_વૃક્ષ
		  && DECL_EXTERNAL (ref)
		  && !વૃક્ષ_PUBLIC (ref);

  જો (!static_p && !nonloc_p)
    પાછા;

  /* If we may be in an unevaluated context, delay the decision.  */
  જો (in_sizeof || in_typeof || in_countof || in_generic)
    પાછા record_maybe_used_decl (ref, address);

  જો (static_p)
    C_DECL_USED (ref) = 1;

  જો (nonloc_p && (VAR_OR_FUNCTION_DECL_P (ref)
		   || વૃક્ષ_CODE (ref) == PARM_DECL))
    DECL_NONLOCAL (ref) = 1;

  /* Nothing to do anymore.  */
  જો (!nonloc_p || C_FUNC_NONLOCAL_CONTEXT (current_function_decl))
    પાછા;

  /* Filter out the cases where referencing a non-local variable does not
     require a non-local context passed via the static chain.  */
  જો (!c_type_variably_modified_p (વૃક્ષ_TYPE (ref)))
    પસંદગી (વૃક્ષ_CODE (ref))
      {
      સ્થિતિ FUNCTION_DECL:
	/* Use of another local function that requires no context is ok.  */
	જો (!C_FUNC_NONLOCAL_CONTEXT (ref) && DECL_INITIAL (ref))
	  પાછા;
	તોડો;
      સ્થિતિ VAR_DECL:
	/* Static variables and constexpr are ok, but for the later only
	   when the address is not taken.  */
	જો (વૃક્ષ_STATIC (ref) || (C_DECL_DECLARED_CONSTEXPR (ref) && !address))
	  પાછા;
	તોડો;
      સ્થિતિ TYPE_DECL:
	/* A typedef is ok when not for a variably-modified type. */
	પાછા;
      સ્થિતિ CONST_DECL:
	/* An enumeration constant is ok. */
	પાછા;
      સ્થિતિ PARM_DECL:
	તોડો;
      સ્થિતિ LABEL_DECL:
	તોડો;
      મૂળભૂત:
	gcc_unreachable ();
    }

  /* Mark all parent functions up to the nesting level of the variable as
     as needing the non-local context.  */
  માટે (વૃક્ષ cont = current_function_decl; cont; cont = DECL_CONTEXT (cont))
    {
      જો (cont == DECL_CONTEXT (ref))
	તોડો;

      /* There should not be any other type of context used for function
	 except TRANSLATION_UNIT_DECL which we should be able to reach.  */
      gcc_checking_assert (વૃક્ષ_CODE (cont) == FUNCTION_DECL);

      જો (વૃક્ષ_CODE (cont) == FUNCTION_DECL)
	C_FUNC_NONLOCAL_CONTEXT (cont) = 1;
    }
}


/* Build an external reference to identifier ID.  FUN indicates
   whether this will be used for a function call.  LOC is the source
   location of the identifier.  This sets *TYPE to the type of the
   identifier, which is not the same as the type of the returned value
   for CONST_DECLs defined as enum constants.  If the type of the
   identifier is not available, *TYPE is set to NULL.  */
વૃક્ષ
build_external_ref (location_t loc, વૃક્ષ id, તાર્કિક fun, વૃક્ષ *type)
{
  વૃક્ષ ref;
  વૃક્ષ decl = lookup_name (id);

  /* In Objective-C, an instance variable (ivar) may be preferred to
     whatever lookup_name() found.  */
  decl = objc_lookup_ivar (decl, id);

  *type = ખાલી;
  જો (decl && decl != error_mark_ગાંઠ)
    {
      ref = decl;
      *type = વૃક્ષ_TYPE (ref);
      જો (DECL_P (decl) && C_DECL_UNDERSPECIFIED (decl))
	error_at (loc, "underspecified %qD referenced in its initializer",
		  decl);
    }
  નહીંતર જો (fun)
    /* Implicit function declaration.  */
    ref = implicitly_declare (loc, id);
  નહીંતર જો (decl == error_mark_ગાંઠ)
    /* Don't complain about something that's already been
       complained about.  */
    પાછા error_mark_ગાંઠ;
  નહીંતર
    {
      undeclared_variable (loc, id);
      પાછા error_mark_ગાંઠ;
    }

  /* For an OpenMP map clause, we can get better diagnostics for decls with
     unmappable types if we return the decl with an error_mark_node type,
     rather than returning error_mark_node for the decl itself.  */
  જો (વૃક્ષ_TYPE (ref) == error_mark_ગાંઠ
      && !c_omp_array_section_p)
    પાછા error_mark_ગાંઠ;

  જો (વૃક્ષ_UNAVAILABLE (ref))
    error_unavailable_use (ref, NULL_વૃક્ષ);
  નહીંતર જો (વૃક્ષ_DEPRECATED (ref))
    warn_deprecated_use (ref, NULL_વૃક્ષ);

  /* Recursive call does not count as usage.  */
  જો (ref != current_function_decl)
    {
      વૃક્ષ_USED (ref) = 1;
    }

  mark_decl_used (ref, ખોટું);

  જો (વૃક્ષ_CODE (ref) == CONST_DECL)
    {
      used_types_ઉમેરો (વૃક્ષ_TYPE (ref));

      જો (warn_cxx_compat
	  && વૃક્ષ_CODE (વૃક્ષ_TYPE (ref)) == ENUMERAL_TYPE
	  && C_TYPE_DEFINED_IN_STRUCT (વૃક્ષ_TYPE (ref)))
	{
	  warning_at (loc, OPT_Wc___compat,
		      "enum constant defined in struct or union "
		      "is not visible in C++");
	  inform (DECL_SOURCE_LOCATION (ref), "enum constant defined here");
	}

      ref = DECL_INITIAL (ref);
      વૃક્ષ_CONSTANT (ref) = 1;
    }
  /* C99 6.7.4p3: An inline definition of a function with external
     linkage ... shall not contain a reference to an identifier with
     internal linkage.  */
  નહીંતર જો (current_function_decl != NULL_વૃક્ષ
	   && DECL_DECLARED_INLINE_P (current_function_decl)
	   && DECL_EXTERNAL (current_function_decl)
	   && VAR_OR_FUNCTION_DECL_P (ref)
	   && (!VAR_P (ref) || વૃક્ષ_STATIC (ref))
	   && ! વૃક્ષ_PUBLIC (ref)
	   && DECL_CONTEXT (ref) != current_function_decl)
    record_inline_static (loc, current_function_decl, ref,
			  csi_internal);

  પાછા ref;
}

સ્થિર સંરચના maybe_used_decl *maybe_used_decls;

/* Record that DECL, a reference seen inside sizeof or typeof or _Countof or
   _Generic, might be used if the operand of sizeof is a VLA type or the
   operand of typeof is a variably modified type or the operand of _Countof has
   a variable number of elements or the operand of _Generic is the one selected
   as the result.  */

સ્થિર શૂન્ય
record_maybe_used_decl (વૃક્ષ decl, તાર્કિક address)
{
  સંરચના maybe_used_decl *t = XOBNEW (&parser_obstack, સંરચના maybe_used_decl);
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

શૂન્ય
કાઢો_maybe_used (તાર્કિક used)
{
  સંરચના maybe_used_decl *p = maybe_used_decls;
  પૂર્ણાંક cur_level = in_sizeof + in_typeof + in_countof + in_generic;
  જ્યારે (p && p->level > cur_level)
    {
      જો (used)
	{
	  જો (cur_level == 0)
	    mark_decl_used (p->decl, p->address);
	  નહીંતર
	    p->level = cur_level;
	}
      p = p->next;
    }
  જો (!used || cur_level == 0)
    maybe_used_decls = p;
}

/* Pop the stack of decls possibly used inside sizeof or typeof or _Countof or
   _Generic, without acting on them, and return the pointer to the previous top
   of the stack.  This for use at the end of a default generic association when
   it is not yet known whether the expression is used.  If it later turns out
   the expression is used (or treated as used before C23), restore_maybe_used
   should be called on the return value followed by pop_maybe_used (true);
   otherwise, the return value can be discarded.  */

સંરચના maybe_used_decl *
save_maybe_used ()
{
  સંરચના maybe_used_decl *p = maybe_used_decls, *orig = p;
  પૂર્ણાંક cur_level = in_sizeof + in_typeof + in_countof + in_generic;
  જ્યારે (p && p->level > cur_level)
    p = p->next;
  maybe_used_decls = p;
  પાછા orig;
}

/* Restore the stack of decls possibly used inside sizeof or typeof or _Countof
   or _Generic returned by save_maybe_used.  It is required that the stack is
   at exactly the point where it was left by save_maybe_used.  */

શૂન્ય
restore_maybe_used (સંરચના maybe_used_decl *ઢગલો)
{
  maybe_used_decls = ઢગલો;
}

/* Return the result of sizeof applied to EXPR.  */

સંરચના c_પદાવલિ
c_પદાવલિ_sizeof_પદાવલિ (location_t loc, સંરચના c_પદાવલિ પદાવલિ)
{
  સંરચના c_પદાવલિ ret;
  જો (પદાવલિ.કિંમત == error_mark_ગાંઠ)
    {
      ret.કિંમત = error_mark_ગાંઠ;
      ret.original_code = ERROR_MARK;
      ret.original_type = ખાલી;
      ret.m_decimal = 0;
      કાઢો_maybe_used (ખોટું);
    }
  નહીંતર
    {
      તાર્કિક પદાવલિ_const_operands = સાચું;

      જો (વૃક્ષ_CODE (પદાવલિ.કિંમત) == PARM_DECL
	  && C_ARRAY_PARAMETER (પદાવલિ.કિંમત))
	{
	  auto_diagnostic_group d;
	  જો (warning_at (loc, OPT_Wsizeof_array_argument,
			  "%<sizeof%> on array function parameter %qE will "
			  "return size of %qT", પદાવલિ.કિંમત,
			  વૃક્ષ_TYPE (પદાવલિ.કિંમત)))
	    inform (DECL_SOURCE_LOCATION (પદાવલિ.કિંમત), "declared here");
	}
      વૃક્ષ folded_પદાવલિ = c_fully_fold (પદાવલિ.કિંમત, require_constant_કિંમત,
				       &પદાવલિ_const_operands);
      ret.કિંમત = c_sizeof (loc, વૃક્ષ_TYPE (folded_પદાવલિ));
      c_last_sizeof_arg = પદાવલિ.કિંમત;
      c_last_sizeof_loc = loc;
      ret.original_code = SIZEOF_પદાવલિ;
      ret.original_type = ખાલી;
      ret.m_decimal = 0;
      જો (C_TYPE_VARIABLE_SIZE (વૃક્ષ_TYPE (folded_પદાવલિ)))
	{
	  /* sizeof is evaluated when given a vla (C99 6.5.3.4p2).  */
	  ret.કિંમત = build2 (C_MAYBE_CONST_પદાવલિ, વૃક્ષ_TYPE (ret.કિંમત),
			      folded_પદાવલિ, ret.કિંમત);
	  C_MAYBE_CONST_પદાવલિ_NON_CONST (ret.કિંમત) = !પદાવલિ_const_operands;
	  SET_પદાવલિ_LOCATION (ret.કિંમત, loc);
	}
      કાઢો_maybe_used (C_TYPE_VARIABLE_SIZE (વૃક્ષ_TYPE (folded_પદાવલિ)));
    }
  પાછા ret;
}

/* Return the result of sizeof applied to T, a structure for the type
   name passed to sizeof (rather than the type itself).  LOC is the
   location of the original expression.  */

સંરચના c_પદાવલિ
c_પદાવલિ_sizeof_type (location_t loc, સંરચના c_type_name *t)
{
  વૃક્ષ type;
  સંરચના c_પદાવલિ ret;
  વૃક્ષ type_પદાવલિ = NULL_વૃક્ષ;
  તાર્કિક type_પદાવલિ_const = સાચું;
  type = groktypename (t, &type_પદાવલિ, &type_પદાવલિ_const);
  ret.કિંમત = c_sizeof (loc, type);
  c_last_sizeof_arg = type;
  c_last_sizeof_loc = loc;
  ret.original_code = SIZEOF_પદાવલિ;
  ret.original_type = ખાલી;
  ret.m_decimal = 0;
  જો (type == error_mark_ગાંઠ)
    {
      ret.કિંમત = error_mark_ગાંઠ;
      ret.original_code = ERROR_MARK;
    }
  નહીંતર
  જો ((type_પદાવલિ || વૃક્ષ_CODE (ret.કિંમત) == INTEGER_CST)
      && C_TYPE_VARIABLE_SIZE (type))
    {
      /* If the type is a [*] array, it is a VLA but is represented as
	 having a size of zero.  In such a case we must ensure that
	 the result of sizeof does not get folded to a constant by
	 c_fully_fold, because if the size is evaluated the result is
	 not constant and so constraints on zero or negative size
	 arrays must not be applied when this sizeof call is inside
	 another array declarator.  */
      જો (!type_પદાવલિ)
	type_પદાવલિ = integer_zero_ગાંઠ;
      ret.કિંમત = build2 (C_MAYBE_CONST_પદાવલિ, વૃક્ષ_TYPE (ret.કિંમત),
			  type_પદાવલિ, ret.કિંમત);
      C_MAYBE_CONST_પદાવલિ_NON_CONST (ret.કિંમત) = !type_પદાવલિ_const;
    }
  કાઢો_maybe_used (type != error_mark_ગાંઠ
		  ? C_TYPE_VARIABLE_SIZE (type) : ખોટું);
  પાછા ret;
}

સ્થિર તાર્કિક
ટોચ_array_vla_p (const_વૃક્ષ type)
{
  જો (વૃક્ષ_CODE (type) != ARRAY_TYPE)
    પાછા ખોટું;

  વૃક્ષ d = TYPE_DOMAIN (type);

  જો (!d)
    પાછા ખોટું;
  જો (!TYPE_MAX_કિંમત (d))
    પાછા ખોટું;

  પાછા વૃક્ષ_CODE (TYPE_MAX_કિંમત (d)) != INTEGER_CST
	 || વૃક્ષ_CODE (TYPE_MIN_કિંમત (d)) != INTEGER_CST;
}

/* Return the result of countof applied to EXPR.  */

સંરચના c_પદાવલિ
c_પદાવલિ_countof_પદાવલિ (location_t loc, સંરચના c_પદાવલિ પદાવલિ)
{
  સંરચના c_પદાવલિ ret;
  જો (પદાવલિ.કિંમત == error_mark_ગાંઠ)
    {
      ret.કિંમત = error_mark_ગાંઠ;
      ret.original_code = ERROR_MARK;
      ret.original_type = ખાલી;
      ret.m_decimal = 0;
      કાઢો_maybe_used (ખોટું);
    }
  નહીંતર
    {
      તાર્કિક પદાવલિ_const_operands = સાચું;

      વૃક્ષ folded_પદાવલિ = c_fully_fold (પદાવલિ.કિંમત, require_constant_કિંમત,
				       &પદાવલિ_const_operands);
      ret.કિંમત = c_countof_type (loc, વૃક્ષ_TYPE (folded_પદાવલિ));
      c_last_sizeof_arg = પદાવલિ.કિંમત;
      c_last_sizeof_loc = loc;
      ret.original_code = COUNTOF_પદાવલિ;
      ret.original_type = ખાલી;
      ret.m_decimal = 0;
      જો (ટોચ_array_vla_p (વૃક્ષ_TYPE (folded_પદાવલિ)))
	{
	  /* countof is evaluated when given a vla.  */
	  ret.કિંમત = build2 (C_MAYBE_CONST_પદાવલિ, વૃક્ષ_TYPE (ret.કિંમત),
			      folded_પદાવલિ, ret.કિંમત);
	  C_MAYBE_CONST_પદાવલિ_NON_CONST (ret.કિંમત) = !પદાવલિ_const_operands;
	  SET_પદાવલિ_LOCATION (ret.કિંમત, loc);
	}
      કાઢો_maybe_used (ટોચ_array_vla_p (વૃક્ષ_TYPE (folded_પદાવલિ)));
    }
  પાછા ret;
}

/* Return the result of countof applied to T, a structure for the type
   name passed to countof (rather than the type itself).  LOC is the
   location of the original expression.  */

સંરચના c_પદાવલિ
c_પદાવલિ_countof_type (location_t loc, સંરચના c_type_name *t)
{
  વૃક્ષ type;
  સંરચના c_પદાવલિ ret;
  વૃક્ષ type_પદાવલિ = NULL_વૃક્ષ;
  તાર્કિક type_પદાવલિ_const = સાચું;
  type = groktypename (t, &type_પદાવલિ, &type_પદાવલિ_const);
  ret.કિંમત = c_countof_type (loc, type);
  c_last_sizeof_arg = type;
  c_last_sizeof_loc = loc;
  ret.original_code = COUNTOF_પદાવલિ;
  ret.original_type = ખાલી;
  ret.m_decimal = 0;
  જો (type == error_mark_ગાંઠ)
    {
      ret.કિંમત = error_mark_ગાંઠ;
      ret.original_code = ERROR_MARK;
    }
  નહીંતર
  જો ((type_પદાવલિ || વૃક્ષ_CODE (ret.કિંમત) == INTEGER_CST)
      && ટોચ_array_vla_p (type))
    {
      /* If the type is a [*] array, it is a VLA but is represented as
	 having a size of zero.  In such a case we must ensure that
	 the result of countof does not get folded to a constant by
	 c_fully_fold, because if the number of elements is evaluated
	 the result is not constant and so
	 constraints on zero or negative size arrays must not be applied
	 when this countof call is inside another array declarator.  */
      જો (!type_પદાવલિ)
	type_પદાવલિ = integer_zero_ગાંઠ;
      ret.કિંમત = build2 (C_MAYBE_CONST_પદાવલિ, વૃક્ષ_TYPE (ret.કિંમત),
			  type_પદાવલિ, ret.કિંમત);
      C_MAYBE_CONST_પદાવલિ_NON_CONST (ret.કિંમત) = !type_પદાવલિ_const;
    }
  કાઢો_maybe_used (type != error_mark_ગાંઠ ? ટોચ_array_vla_p (type) : ખોટું);
  પાછા ret;
}

/* Return the result of maxof applied to T, a structure for the type
   name passed to maxof (rather than the type itself).  LOC is the
   location of the original expression.  */

સંરચના c_પદાવલિ
c_પદાવલિ_maxof_type (location_t loc, સંરચના c_type_name *t)
{
  વૃક્ષ type;
  સંરચના c_પદાવલિ ret;
  વૃક્ષ type_પદાવલિ = NULL_વૃક્ષ;
  તાર્કિક type_પદાવલિ_const = સાચું;
  type = groktypename (t, &type_પદાવલિ, &type_પદાવલિ_const);
  ret.કિંમત = c_maxof_type (loc, type);
  c_last_sizeof_arg = type;
  c_last_sizeof_loc = loc;
  ret.original_code = MAXOF_પદાવલિ;
  ret.original_type = ખાલી;
  ret.m_decimal = 0;
  જો (type == error_mark_ગાંઠ)
    {
      ret.કિંમત = error_mark_ગાંઠ;
      ret.original_code = ERROR_MARK;
    }
  કાઢો_maybe_used (type != error_mark_ગાંઠ);
  પાછા ret;
}

/* Return the result of minof applied to T, a structure for the type
   name passed to minof (rather than the type itself).  LOC is the
   location of the original expression.  */

સંરચના c_પદાવલિ
c_પદાવલિ_minof_type (location_t loc, સંરચના c_type_name *t)
{
  વૃક્ષ type;
  સંરચના c_પદાવલિ ret;
  વૃક્ષ type_પદાવલિ = NULL_વૃક્ષ;
  તાર્કિક type_પદાવલિ_const = સાચું;
  type = groktypename (t, &type_પદાવલિ, &type_પદાવલિ_const);
  ret.કિંમત = c_minof_type (loc, type);
  c_last_sizeof_arg = type;
  c_last_sizeof_loc = loc;
  ret.original_code = MINOF_પદાવલિ;
  ret.original_type = ખાલી;
  ret.m_decimal = 0;
  જો (type == error_mark_ગાંઠ)
    {
      ret.કિંમત = error_mark_ગાંઠ;
      ret.original_code = ERROR_MARK;
    }
  કાઢો_maybe_used (type != error_mark_ગાંઠ);
  પાછા ret;
}

/* Build a function call to function FUNCTION with parameters PARAMS.
   The function call is at LOC.
   PARAMS is a list--a chain of TREE_LIST nodes--in which the
   TREE_VALUE of each node is a parameter-expression.
   FUNCTION's data type may be a function type or a pointer-to-function.  */

વૃક્ષ
build_function_call (location_t loc, વૃક્ષ function, વૃક્ષ params)
{
  vec<વૃક્ષ, va_gc> *v;
  વૃક્ષ ret;

  vec_alloc (v, list_length (params));
  માટે (; params; params = વૃક્ષ_CHAIN (params))
    v->quick_ધકેલો (વૃક્ષ_કિંમત (params));
  ret = c_build_function_call_vec (loc, vNULL, function, v, ખાલી);
  vec_free (v);
  પાછા ret;
}

/* Give a note about the location of the declaration of DECL,
   or, failing that, a pertinent declaration for FUNCTION_EXPR.  */

સ્થિર શૂન્ય
inform_declaration (વૃક્ષ decl, વૃક્ષ function_પદાવલિ)
{
  જો (decl && (વૃક્ષ_CODE (decl) != FUNCTION_DECL
	       || !DECL_IS_UNDECLARED_BUILTIN (decl)))
    inform (DECL_SOURCE_LOCATION (decl), "declared here");
  નહીંતર જો (function_પદાવલિ)
    પસંદગી (વૃક્ષ_CODE (function_પદાવલિ))
      {
      મૂળભૂત:
	તોડો;
      સ્થિતિ COMPONENT_REF:
	/* Show the decl of the pertinent field (e.g. for callback
	   fields in a struct.  */
	{
	  વૃક્ષ field_decl = વૃક્ષ_OPERAND (function_પદાવલિ, 1);
	  જો (location_t loc = DECL_SOURCE_LOCATION (field_decl))
	    inform (loc, "declared here");
	}
	તોડો;
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

વૃક્ષ
build_function_call_vec (location_t loc, vec<location_t> arg_loc,
			 વૃક્ષ function, vec<વૃક્ષ, va_gc> *params,
			 vec<વૃક્ષ, va_gc> *origtypes, વૃક્ષ orig_fundecl)
{
  વૃક્ષ fntype, fundecl = NULL_વૃક્ષ;
  વૃક્ષ name = NULL_વૃક્ષ, result;
  વૃક્ષ tem;
  પૂર્ણાંક nargs;
  વૃક્ષ *argarray;


  /* Strip NON_LVALUE_EXPRs, etc., since we aren't using as an lvalue.  */
  STRIP_TYPE_NOPS (function);

  /* Convert anything with function type to a pointer-to-function.  */
  જો (વૃક્ષ_CODE (function) == FUNCTION_DECL)
    {
      name = DECL_NAME (function);

      જો (flag_tm)
	tm_malloc_replacement (function);
      fundecl = function;
      જો (!orig_fundecl)
	orig_fundecl = fundecl;
      /* Atomic functions have type checking/casting already done.  They are
	 often rewritten and don't match the original parameter list.  */
      જો (name && startswith (IDENTIFIER_POINTER (name), "__atomic_"))
        origtypes = ખાલી;
    }
  જો (વૃક્ષ_CODE (વૃક્ષ_TYPE (function)) == FUNCTION_TYPE)
    function = function_to_pointer_conversion (loc, function);

  /* For Objective-C, convert any calls via a cast to OBJC_TYPE_REF
     expressions, like those used for ObjC messenger dispatches.  */
  જો (params && !params->is_empty ())
    function = objc_rewrite_function_call (function, (*params)[0]);

  function = c_fully_fold (function, ખોટું, ખાલી);

  fntype = વૃક્ષ_TYPE (function);

  જો (વૃક્ષ_CODE (fntype) == ERROR_MARK)
    પાછા error_mark_ગાંઠ;

  જો (!(વૃક્ષ_CODE (fntype) == POINTER_TYPE
	&& વૃક્ષ_CODE (વૃક્ષ_TYPE (fntype)) == FUNCTION_TYPE))
    {
      જો (!flag_diagnostics_show_caret && !STATEMENT_CLASS_P (function))
	error_at (loc,
		  "called object %qE is not a function or function pointer",
		  function);
      નહીંતર જો (DECL_P (function))
	{
	  auto_diagnostic_group d;
	  error_at (loc,
		    "called object %qD is not a function or function pointer",
		    function);
	  inform_declaration (function, NULL_વૃક્ષ);
	}
      નહીંતર
	error_at (loc,
		  "called object is not a function or function pointer");
      પાછા error_mark_ગાંઠ;
    }

  જો (fundecl && વૃક્ષ_THIS_VOLATILE (fundecl))
    current_function_returns_abnormally = 1;

  /* fntype now gets the type of function pointed to.  */
  fntype = વૃક્ષ_TYPE (fntype);
  વૃક્ષ return_type = વૃક્ષ_TYPE (fntype);

  /* Convert the parameters to the types declared in the
     function prototype, or apply default promotions.  */

  nargs = convert_arguments (loc, arg_loc, fntype, params,
			     origtypes, function, fundecl);
  જો (nargs < 0)
    પાછા error_mark_ગાંઠ;

  /* Check that the function is called through a compatible prototype.
     If it is not, warn.  */
  જો (CONVERT_પદાવલિ_P (function)
      && વૃક્ષ_CODE (tem = વૃક્ષ_OPERAND (function, 0)) == ADDR_પદાવલિ
      && વૃક્ષ_CODE (tem = વૃક્ષ_OPERAND (tem, 0)) == FUNCTION_DECL
      && !comptypes (fntype, વૃક્ષ_TYPE (tem)))
    {
      /* This situation leads to run-time undefined behavior.  We can't,
	 therefore, simply error unless we can prove that all possible
	 executions of the program must execute the code.  */
      warning_at (loc, 0, "function called through a non-compatible type");

      જો (VOID_TYPE_P (return_type)
	  && TYPE_QUALS (return_type) != TYPE_UNQUALIFIED)
	pedwarn (loc, 0,
		 "function with qualified void return type called");
     }

  argarray = vec_safe_address (params);

  /* Check that arguments to builtin functions match the expectations.  */
  જો (fundecl
      && fndecl_built_in_p (fundecl)
      && !check_builtin_function_arguments (loc, arg_loc, fundecl,
					    orig_fundecl, nargs, argarray))
    પાછા error_mark_ગાંઠ;

  /* Check that the arguments to the function are valid.  */
  તાર્કિક warned_p = check_function_arguments (loc, fundecl, fntype,
					    nargs, argarray, &arg_loc,
					    comptypes);

  જો (TYPE_QUALS (return_type) != TYPE_UNQUALIFIED
      && !VOID_TYPE_P (return_type))
    return_type = c_build_qualified_type (return_type, TYPE_UNQUALIFIED);
  જો (name != NULL_વૃક્ષ
      && startswith (IDENTIFIER_POINTER (name), "__builtin_"))
    {
      જો (require_constant_કિંમત)
	result
	  = fold_build_call_array_initializer_loc (loc, return_type,
						   function, nargs, argarray);
      નહીંતર
	result = fold_build_call_array_loc (loc, return_type,
					    function, nargs, argarray);
      જો (વૃક્ષ_CODE (result) == NOP_પદાવલિ
	  && વૃક્ષ_CODE (વૃક્ષ_OPERAND (result, 0)) == INTEGER_CST)
	STRIP_TYPE_NOPS (result);
    }
  નહીંતર
    result = build_call_array_loc (loc, return_type,
				   function, nargs, argarray);
  /* If -Wnonnull warning has been diagnosed, avoid diagnosing it again
     later.  */
  જો (warned_p && વૃક્ષ_CODE (result) == CALL_પદાવલિ)
    suppress_warning (result, OPT_Wnonnull);

  /* In this improbable scenario, a nested function returns a VM type.
     Create a TARGET_EXPR so that the call always has a LHS, much as
     what the C++ FE does for functions returning non-PODs.  */
  જો (c_type_variably_modified_p (વૃક્ષ_TYPE (fntype)))
    {
      વૃક્ષ tmp = create_tmp_var_raw (વૃક્ષ_TYPE (fntype));
      result = build4 (TARGET_પદાવલિ, વૃક્ષ_TYPE (fntype), tmp, result,
		       NULL_વૃક્ષ, NULL_વૃક્ષ);
    }

  જો (VOID_TYPE_P (વૃક્ષ_TYPE (result)))
    {
      જો (TYPE_QUALS (વૃક્ષ_TYPE (result)) != TYPE_UNQUALIFIED)
	pedwarn (loc, 0,
		 "function with qualified void return type called");
      પાછા result;
    }
  પાછા require_complete_type (loc, result);
}

/* Like build_function_call_vec, but call also resolve_overloaded_builtin.  */

વૃક્ષ
c_build_function_call_vec (location_t loc, અચલ vec<location_t> &arg_loc,
			   વૃક્ષ function, vec<વૃક્ષ, va_gc> *params,
			   vec<વૃક્ષ, va_gc> *origtypes)
{
  /* Strip NON_LVALUE_EXPRs, etc., since we aren't using as an lvalue.  */
  STRIP_TYPE_NOPS (function);

  /* Convert anything with function type to a pointer-to-function.  */
  જો (વૃક્ષ_CODE (function) == FUNCTION_DECL)
    {
      /* Implement type-directed function overloading for builtins.
	 resolve_overloaded_builtin and targetm.resolve_overloaded_builtin
	 handle all the type checking.  The result is a complete expression
	 that implements this function call.  */
      વૃક્ષ tem = resolve_overloaded_builtin (loc, function, params);
      જો (tem)
	પાછા tem;
    }
  પાછા build_function_call_vec (loc, arg_loc, function, params, origtypes);
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

સ્થિર વૃક્ષ
convert_argument (location_t ploc, વૃક્ષ function, વૃક્ષ fundecl,
		  વૃક્ષ type, વૃક્ષ origtype, વૃક્ષ val, વૃક્ષ valtype,
		  તાર્કિક npc, વૃક્ષ rname, પૂર્ણાંક parmnum, પૂર્ણાંક argnum,
		  તાર્કિક excess_precision, પૂર્ણાંક warnopt)
{
  /* Formal parm type is specified by a function prototype.  */

  જો (type == error_mark_ગાંઠ || !COMPLETE_TYPE_P (type))
    {
      error_at (ploc, "type of formal parameter %d is incomplete",
		parmnum + 1);
      પાછા error_mark_ગાંઠ;
    }

  /* Optionally warn about conversions that differ from the default
     conversions.  */
  જો (warn_traditional_conversion || warn_traditional)
    {
      જો (INTEGRAL_TYPE_P (type)
	  && SCALAR_FLOAT_TYPE_P (valtype))
	warning_at (ploc, OPT_Wtraditional_conversion,
		    "passing argument %d of %qE as integer rather "
		    "than floating due to prototype",
		    argnum, rname);
      જો (INTEGRAL_TYPE_P (type)
	  && વૃક્ષ_CODE (valtype) == COMPLEX_TYPE)
	warning_at (ploc, OPT_Wtraditional_conversion,
		    "passing argument %d of %qE as integer rather "
		    "than complex due to prototype",
		    argnum, rname);
      નહીંતર જો (વૃક્ષ_CODE (type) == COMPLEX_TYPE
	       && SCALAR_FLOAT_TYPE_P (valtype))
	warning_at (ploc, OPT_Wtraditional_conversion,
		    "passing argument %d of %qE as complex rather "
		    "than floating due to prototype",
		    argnum, rname);
      નહીંતર જો (SCALAR_FLOAT_TYPE_P (type)
	       && INTEGRAL_TYPE_P (valtype))
	warning_at (ploc, OPT_Wtraditional_conversion,
		    "passing argument %d of %qE as floating rather "
		    "than integer due to prototype",
		    argnum, rname);
      નહીંતર જો (વૃક્ષ_CODE (type) == COMPLEX_TYPE
	       && INTEGRAL_TYPE_P (valtype))
	warning_at (ploc, OPT_Wtraditional_conversion,
		    "passing argument %d of %qE as complex rather "
		    "than integer due to prototype",
		    argnum, rname);
      નહીંતર જો (SCALAR_FLOAT_TYPE_P (type)
	       && વૃક્ષ_CODE (valtype) == COMPLEX_TYPE)
	warning_at (ploc, OPT_Wtraditional_conversion,
		    "passing argument %d of %qE as floating rather "
		    "than complex due to prototype",
		    argnum, rname);
      /* ??? At some point, messages should be written about
	 conversions between complex types, but that's too messy
	 to do now.  */
      નહીંતર જો (SCALAR_FLOAT_TYPE_P (type)
	       && SCALAR_FLOAT_TYPE_P (valtype))
	{
	  unsigned પૂર્ણાંક formal_prec = TYPE_PRECISION (type);

	  /* Warn if any argument is passed as `float',
	     since without a prototype it would be `double'.  */
	  જો (formal_prec == TYPE_PRECISION (float_type_ગાંઠ)
	      && type != dfloat32_type_ગાંઠ)
	    warning_at (ploc, 0,
			"passing argument %d of %qE as %<float%> "
			"rather than %<double%> due to prototype",
			argnum, rname);

	  /* Warn if mismatch between argument and prototype
	     for decimal float types.  Warn of conversions with
	     binary float types and of precision narrowing due to
	     prototype.  */
	  નહીંતર જો (type != valtype
		   && (type == dfloat32_type_ગાંઠ
		       || type == dfloat64_type_ગાંઠ
		       || type == dfloat128_type_ગાંઠ
		       || valtype == dfloat32_type_ગાંઠ
		       || valtype == dfloat64_type_ગાંઠ
		       || valtype == dfloat128_type_ગાંઠ)
		   && (formal_prec
		       <= TYPE_PRECISION (valtype)
		       || (type == dfloat128_type_ગાંઠ
			   && (valtype
			       != dfloat64_type_ગાંઠ
			       && (valtype
				   != dfloat32_type_ગાંઠ)))
		       || (type == dfloat64_type_ગાંઠ
			   && (valtype
			       != dfloat32_type_ગાંઠ))))
	    warning_at (ploc, 0,
			"passing argument %d of %qE as %qT "
			"rather than %qT due to prototype",
			argnum, rname, type, valtype);

	}
      /* Detect integer changing in width or signedness.
	 These warnings are only activated with
	 -Wtraditional-conversion, not with -Wtraditional.  */
      નહીંતર જો (warn_traditional_conversion
	       && INTEGRAL_TYPE_P (type)
	       && INTEGRAL_TYPE_P (valtype))
	{
	  unsigned પૂર્ણાંક formal_prec = TYPE_PRECISION (type);
	  વૃક્ષ would_have_been = default_conversion (val);
	  વૃક્ષ type1 = વૃક્ષ_TYPE (would_have_been);

	  જો (val == error_mark_ગાંઠ)
	    /* VAL could have been of incomplete type.  */;
	  નહીંતર જો (વૃક્ષ_CODE (type) == ENUMERAL_TYPE
		   && (TYPE_MAIN_VARIANT (type)
		       == TYPE_MAIN_VARIANT (valtype)))
	    /* No warning if function asks for enum
	       and the actual arg is that enum type.  */
	    ;
	  નહીંતર જો (formal_prec != TYPE_PRECISION (type1))
	    warning_at (ploc, OPT_Wtraditional_conversion,
			"passing argument %d of %qE "
			"with different width due to prototype",
			argnum, rname);
	  નહીંતર જો (TYPE_UNSIGNED (type) == TYPE_UNSIGNED (type1))
	    ;
	  /* Don't complain if the formal parameter type
	     is an enum, because we can't tell now whether
	     the value was an enum--even the same enum.  */
	  નહીંતર જો (વૃક્ષ_CODE (type) == ENUMERAL_TYPE)
	    ;
	  નહીંતર જો (વૃક્ષ_CODE (val) == INTEGER_CST
		   && int_fits_type_p (val, type))
	    /* Change in signedness doesn't matter
	       if a constant value is unaffected.  */
	    ;
	  /* If the value is extended from a narrower
	     unsigned type, it doesn't matter whether we
	     pass it as signed or unsigned; the value
	     certainly is the same either way.  */
	  નહીંતર જો (TYPE_PRECISION (valtype) < TYPE_PRECISION (type)
		   && TYPE_UNSIGNED (valtype))
	    ;
	  નહીંતર જો (TYPE_UNSIGNED (type))
	    warning_at (ploc, OPT_Wtraditional_conversion,
			"passing argument %d of %qE "
			"as unsigned due to prototype",
			argnum, rname);
	  નહીંતર
	    warning_at (ploc, OPT_Wtraditional_conversion,
			"passing argument %d of %qE "
			"as signed due to prototype",
			argnum, rname);
	}
    }

  /* Possibly restore an EXCESS_PRECISION_EXPR for the
     sake of better warnings from convert_and_check.  */
  જો (excess_precision)
    val = build1 (EXCESS_PRECISION_પદાવલિ, valtype, val);

  વૃક્ષ parmval = convert_for_assignment (ploc, ploc, type,
					 val, origtype, ic_argpass,
					 npc, fundecl, function,
					 parmnum + 1, warnopt);
  પાછા parmval;
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

સ્થિર પૂર્ણાંક
convert_arguments (location_t loc, vec<location_t> arg_loc, વૃક્ષ fntype,
		   vec<વૃક્ષ, va_gc> *કિંમતો, vec<વૃક્ષ, va_gc> *origtypes,
		   વૃક્ષ function, વૃક્ષ fundecl)
{
  વૃક્ષ typelist = TYPE_ARG_TYPES (fntype);
  unsigned પૂર્ણાંક parmnum;
  તાર્કિક error_args = ખોટું;
  અચલ તાર્કિક type_generic = fundecl
    && lookup_attribute ("type generic", TYPE_ATTRIBUTES (વૃક્ષ_TYPE (fundecl)));
  તાર્કિક type_generic_remove_excess_precision = ખોટું;
  તાર્કિક type_generic_overflow_p = ખોટું;
  તાર્કિક type_generic_bit_query = ખોટું;
  વૃક્ષ selector;

  /* Change pointer to function to the function itself for
     diagnostics.  */
  જો (વૃક્ષ_CODE (function) == ADDR_પદાવલિ
      && વૃક્ષ_CODE (વૃક્ષ_OPERAND (function, 0)) == FUNCTION_DECL)
    function = વૃક્ષ_OPERAND (function, 0);

  /* Handle an ObjC selector specially for diagnostics.  */
  selector = objc_message_selector ();

  /* For a call to a built-in function declared without a prototype,
     set to the built-in function's argument list.  */
  વૃક્ષ builtin_typelist = NULL_વૃક્ષ;

  /* For type-generic built-in functions, determine whether excess
     precision should be removed (classification) or not
     (comparison).  */
  જો (fundecl
      && fndecl_built_in_p (fundecl, BUILT_IN_NORMAL))
    {
      built_in_function code = DECL_FUNCTION_CODE (fundecl);
      જો (C_DECL_BUILTIN_PROTOTYPE (fundecl))
	{
	  /* For a call to a built-in function declared without a prototype
	     use the types of the parameters of the internal built-in to
	     match those of the arguments to.  */
	  જો (વૃક્ષ bdecl = builtin_decl_explicit (code))
	    builtin_typelist = TYPE_ARG_TYPES (વૃક્ષ_TYPE (bdecl));
	}

      /* For type-generic built-in functions, determine whether excess
	 precision should be removed (classification) or not
	 (comparison).  */
      જો (type_generic)
	પસંદગી (code)
	  {
	  સ્થિતિ BUILT_IN_ISFINITE:
	  સ્થિતિ BUILT_IN_ISINF:
	  સ્થિતિ BUILT_IN_ISINF_SIGN:
	  સ્થિતિ BUILT_IN_ISNAN:
	  સ્થિતિ BUILT_IN_ISNORMAL:
	  સ્થિતિ BUILT_IN_ISSIGNALING:
	  સ્થિતિ BUILT_IN_FPCLASSIFY:
	    type_generic_remove_excess_precision = સાચું;
	    તોડો;

	  સ્થિતિ BUILT_IN_ADD_OVERFLOW_P:
	  સ્થિતિ BUILT_IN_SUB_OVERFLOW_P:
	  સ્થિતિ BUILT_IN_MUL_OVERFLOW_P:
	    /* The last argument of these type-generic builtins
	       should not be promoted.  */
	    type_generic_overflow_p = સાચું;
	    તોડો;

	  સ્થિતિ BUILT_IN_CLZG:
	  સ્થિતિ BUILT_IN_CTZG:
	  સ્થિતિ BUILT_IN_CLRSBG:
	  સ્થિતિ BUILT_IN_FFSG:
	  સ્થિતિ BUILT_IN_PARITYG:
	  સ્થિતિ BUILT_IN_POPCOUNTG:
	    /* The first argument of these type-generic builtins
	       should not be promoted.  */
	    type_generic_bit_query = સાચું;
	    તોડો;

	  મૂળભૂત:
	    તોડો;
	  }
    }

  /* Scan the given expressions (VALUES) and types (TYPELIST), producing
     individual converted arguments.  */

  વૃક્ષ typetail, builtin_typetail, val;
  માટે (typetail = typelist,
	 builtin_typetail = builtin_typelist,
	 parmnum = 0;
       કિંમતો && કિંમતો->iterate (parmnum, &val);
       ++parmnum)
    {
      /* The type of the function parameter (if it was declared with one).  */
      વૃક્ષ type = typetail ? વૃક્ષ_કિંમત (typetail) : NULL_વૃક્ષ;
      /* The type of the built-in function parameter (if the function
	 is a built-in).  Used to detect type incompatibilities in
	 calls to built-ins declared without a prototype.  */
      વૃક્ષ builtin_type = (builtin_typetail
			   ? વૃક્ષ_કિંમત (builtin_typetail) : NULL_વૃક્ષ);
      /* The original type of the argument being passed to the function.  */
      વૃક્ષ valtype = વૃક્ષ_TYPE (val);
      /* The called function (or function selector in Objective C).  */
      વૃક્ષ rname = function;
      પૂર્ણાંક argnum = parmnum + 1;
      અચલ અક્ષર *invalid_func_diag;
      /* Set for EXCESS_PRECISION_EXPR arguments.  */
      તાર્કિક excess_precision = ખોટું;
      /* The value of the argument after conversion to the type
	 of the function parameter it is passed to.  */
      વૃક્ષ parmval;
      /* Some __atomic_* builtins have additional hidden argument at
	 position 0.  */
      location_t ploc
	= !arg_loc.is_empty () && કિંમતો->length () == arg_loc.length ()
	  ? expansion_point_location_if_in_system_header (arg_loc[parmnum])
	  : આગત_location;

      જો (type == void_type_ગાંઠ)
	{
	  auto_diagnostic_group d;
	  પૂર્ણાંક અંક_expected = parmnum;
	  પૂર્ણાંક અંક_actual = કિંમતો->length ();
	  gcc_rich_location rich_loc (loc);
	  જો (ploc != આગત_location)
	    rich_loc.add_range (ploc);
	  જો (selector)
	    error_at (&rich_loc,
		      "too many arguments to method %qE; expected %i, have %i",
		      selector, અંક_expected, અંક_actual);
	  નહીંતર
	    error_at (&rich_loc,
		      "too many arguments to function %qE; expected %i, have %i",
		      function, અંક_expected, અંક_actual);
	  inform_declaration (fundecl, function);
	  પાછા error_args ? -1 : (પૂર્ણાંક) parmnum;
	}

      જો (builtin_type == void_type_ગાંઠ)
	{
	  auto_diagnostic_group d;
	  જો (warning_at (loc, OPT_Wbuiltin_declaration_mismatch,
			  "too many arguments to built-in function %qE "
			  "expecting %d", function, parmnum))
	    inform_declaration (fundecl, function);
	  builtin_typetail = NULL_વૃક્ષ;
	}

      જો (!typetail && parmnum == 0 && !TYPE_NO_NAMED_ARGS_STDARG_P (fntype)
	  && !(fundecl && fndecl_built_in_p (fundecl)))
	{
	  auto_diagnostic_group d;
	  તાર્કિક warned;
	  જો (selector)
	    warned = warning_at (loc, OPT_Wdeprecated_non_prototype,
				 "ISO C23 does not allow arguments"
				 " for method %qE declared without parameters",
				 function);
	  નહીંતર
	    warned = warning_at (loc, OPT_Wdeprecated_non_prototype,
				 "ISO C23 does not allow arguments"
				 " for function %qE declared without parameters",
				 function);
	  જો (warned)
	    inform_declaration (fundecl, function);
	}

      જો (selector && argnum > 2)
	{
	  rname = selector;
	  argnum -= 2;
	}

      /* Determine if VAL is a null pointer constant before folding it.  */
      તાર્કિક npc = null_pointer_constant_p (val);

      /* If there is excess precision and a prototype, convert once to
	 the required type rather than converting via the semantic
	 type.  Likewise without a prototype a float value represented
	 as long double should be converted once to double.  But for
	 type-generic classification functions excess precision must
	 be removed here.  */
      જો (વૃક્ષ_CODE (val) == EXCESS_PRECISION_પદાવલિ
	  && (type || !type_generic || !type_generic_remove_excess_precision))
	{
	  val = વૃક્ષ_OPERAND (val, 0);
	  excess_precision = સાચું;
	}
      val = c_fully_fold (val, ખોટું, ખાલી);
      STRIP_TYPE_NOPS (val);

      val = require_complete_type (ploc, val);

      /* Some floating-point arguments must be promoted to double when
	 no type is specified by a prototype.  This applies to
	 arguments of type float, and to architecture-specific types
	 (ARM __fp16), but not to _FloatN or _FloatNx types.  */
      તાર્કિક promote_float_arg = ખોટું;
      જો (type == NULL_વૃક્ષ
	  && વૃક્ષ_CODE (valtype) == REAL_TYPE
	  && (TYPE_PRECISION (valtype)
	      <= TYPE_PRECISION (double_type_ગાંઠ))
	  && TYPE_MAIN_VARIANT (valtype) != double_type_ગાંઠ
	  && TYPE_MAIN_VARIANT (valtype) != long_double_type_ગાંઠ
	  && !DECIMAL_FLOAT_MODE_P (TYPE_MODE (valtype)))
	{
	  /* Promote this argument, unless it has a _FloatN or
	     _FloatNx type.  */
	  promote_float_arg = સાચું;
	  માટે (પૂર્ણાંક i = 0; i < અંક_FLOATN_NX_TYPES; i++)
	    જો (TYPE_MAIN_VARIANT (valtype) == FLOATN_NX_TYPE_ગાંઠ (i))
	      {
		promote_float_arg = ખોટું;
		તોડો;
	      }
	  /* Don't promote __bf16 either.  */
	  જો (TYPE_MAIN_VARIANT (valtype) == bfloat16_type_ગાંઠ)
	    promote_float_arg = ખોટું;
	}

      જો (type != NULL_વૃક્ષ)
	{
	  વૃક્ષ origtype = (!origtypes) ? NULL_વૃક્ષ : (*origtypes)[parmnum];
	  parmval = convert_argument (ploc, function, fundecl, type, origtype,
				      val, valtype, npc, rname, parmnum, argnum,
				      excess_precision, 0);
	}
      /* A NULLPTR type is just a nullptr always.  */
      નહીંતર જો (વૃક્ષ_CODE (વૃક્ષ_TYPE (val)) == NULLPTR_TYPE)
	parmval = omit_one_operand_loc (ploc, વૃક્ષ_TYPE (val), nullptr_ગાંઠ, val);
      નહીંતર જો (promote_float_arg)
        {
	  જો (type_generic)
	    parmval = val;
	  નહીંતર
	    {
	      /* Convert `float' to `double'.  */
	      જો (warn_double_promotion && !c_inhibit_evaluation_warnings)
		warning_at (ploc, OPT_Wdouble_promotion,
			    "implicit conversion from %qT to %qT when passing "
			    "argument to function",
			    valtype, double_type_ગાંઠ);
	      parmval = convert (double_type_ગાંઠ, val);
	    }
	}
      નહીંતર જો ((excess_precision && !type_generic)
	       || (type_generic_overflow_p && parmnum == 2)
	       || (type_generic_bit_query && parmnum == 0))
	/* A "double" argument with excess precision being passed
	   without a prototype or in variable arguments.
	   The last argument of __builtin_*_overflow_p should not be
	   promoted, similarly the first argument of
	   __builtin_{clz,ctz,clrsb,ffs,parity,popcount}g.  */
	parmval = convert (valtype, val);
      નહીંતર જો ((invalid_func_diag =
		targetm.calls.invalid_arg_for_unprototyped_fn (typelist, fundecl, val)))
	{
	  error (invalid_func_diag);
	  પાછા -1;
	}
      નહીંતર જો (વૃક્ષ_CODE (val) == ADDR_પદાવલિ && reject_gcc_builtin (val))
	{
	  પાછા -1;
	}
      નહીંતર
	/* Convert `short' and `char' to full-size `int'.  */
	parmval = default_conversion (val);

      (*કિંમતો)[parmnum] = parmval;
      જો (parmval == error_mark_ગાંઠ)
	error_args = સાચું;

      જો (!type && builtin_type && વૃક્ષ_CODE (builtin_type) != VOID_TYPE)
	{
	  /* For a call to a built-in function declared without a prototype,
	     perform the conversions from the argument to the expected type
	     but issue warnings rather than errors for any mismatches.
	     Ignore the converted argument and use the PARMVAL obtained
	     above by applying default conversions instead.  */
	  વૃક્ષ origtype = (!origtypes) ? NULL_વૃક્ષ : (*origtypes)[parmnum];
	  convert_argument (ploc, function, fundecl, builtin_type, origtype,
			    val, valtype, npc, rname, parmnum, argnum,
			    excess_precision,
			    OPT_Wbuiltin_declaration_mismatch);
	}

      જો (typetail)
	typetail = વૃક્ષ_CHAIN (typetail);

      જો (builtin_typetail)
	builtin_typetail = વૃક્ષ_CHAIN (builtin_typetail);
    }

  gcc_assert (parmnum == vec_safe_length (કિંમતો));

  જો (typetail != NULL_વૃક્ષ && વૃક્ષ_કિંમત (typetail) != void_type_ગાંઠ)
    {
      /* Not enough args.
	 Determine minimum number of arguments required.  */
      પૂર્ણાંક min_expected_અંક = 0;
      તાર્કિક at_least_p = ખોટું;
      વૃક્ષ iter = typelist;
      જ્યારે (સાચું)
	{
	  જો (!iter)
	    {
	      /* Variadic arguments; stop iterating.  */
	      at_least_p = સાચું;
	      તોડો;
	    }
	  જો (iter == void_list_ગાંઠ)
	    /* End of arguments; stop iterating.  */
	    તોડો;
	  ++min_expected_અંક;
	  iter = વૃક્ષ_CHAIN (iter);
	}
      auto_diagnostic_group d;
      પૂર્ણાંક actual_અંક = vec_safe_length (કિંમતો);
      error_at (loc,
		at_least_p
		? G_("too few arguments to function %qE; expected at least %i, have %i")
		: G_("too few arguments to function %qE; expected %i, have %i"),
		function, min_expected_અંક, actual_અંક);
      inform_declaration (fundecl, function);
      પાછા -1;
    }

  જો (builtin_typetail && વૃક્ષ_કિંમત (builtin_typetail) != void_type_ગાંઠ)
    {
      unsigned nargs = parmnum;
      માટે (વૃક્ષ t = builtin_typetail; t; t = વૃક્ષ_CHAIN (t))
	++nargs;

      auto_diagnostic_group d;
      જો (warning_at (loc, OPT_Wbuiltin_declaration_mismatch,
		      "too few arguments to built-in function %qE "
		      "expecting %u", function, nargs - 1))
	inform_declaration (fundecl, function);
    }

  પાછા error_args ? -1 : (પૂર્ણાંક) parmnum;
}

/* This is the entry point used by the parser to build unary operators
   in the input.  CODE, a tree_code, specifies the unary operator, and
   ARG is the operand.  For unary plus, the C parser currently uses
   CONVERT_EXPR for code.

   LOC is the location to use for the tree generated.
*/

સંરચના c_પદાવલિ
parser_build_unary_op (location_t loc, ગણના વૃક્ષ_code code, સંરચના c_પદાવલિ arg)
{
  સંરચના c_પદાવલિ result;

  result.original_code = code;
  result.original_type = ખાલી;
  result.m_decimal = 0;

  જો (reject_gcc_builtin (arg.કિંમત))
    {
      result.કિંમત = error_mark_ગાંઠ;
    }
  નહીંતર
    {
      result.કિંમત = build_unary_op (loc, code, arg.કિંમત, ખોટું);

      જો (વૃક્ષ_OVERFLOW_P (result.કિંમત) && !વૃક્ષ_OVERFLOW_P (arg.કિંમત))
	overflow_warning (loc, result.કિંમત, arg.કિંમત);
    }

  /* We are typically called when parsing a prefix token at LOC acting on
     ARG.  Reflect this by updating the source range of the result to
     start at LOC and end at the end of ARG.  */
  set_c_પદાવલિ_source_range (&result,
			   loc, arg.get_finish ());

  પાછા result;
}

/* Returns true if TYPE is a character type, *not* including wchar_t.  */

તાર્કિક
char_type_p (વૃક્ષ type)
{
  પાછા (type == char_type_ગાંઠ
	  || type == unsigned_char_type_ગાંઠ
	  || type == signed_char_type_ગાંઠ
	  || type == char16_type_ગાંઠ
	  || type == char32_type_ગાંઠ);
}

/* This is the entry point used by the parser to build binary operators
   in the input.  CODE, a tree_code, specifies the binary operator, and
   ARG1 and ARG2 are the operands.  In addition to constructing the
   expression, we check for operands that were written with other binary
   operators in a way that is likely to confuse the user.  ORIG_ARG1 is
   the original first operand for TRUTH_{AND,OR}IF_EXPR before it is
   converted to truth value, otherwise NULL_TREE.

   LOCATION is the location of the binary operator.  */

સંરચના c_પદાવલિ
parser_build_દ્વિઅંકી_op (location_t location, ગણના વૃક્ષ_code code,
			સંરચના c_પદાવલિ arg1, સંરચના c_પદાવલિ arg2, વૃક્ષ orig_arg1)
{
  સંરચના c_પદાવલિ result;
  result.m_decimal = 0;

  ગણના વૃક્ષ_code code1 = arg1.original_code;
  ગણના વૃક્ષ_code code2 = arg2.original_code;
  વૃક્ષ type1 = (arg1.original_type
                ? arg1.original_type
                : વૃક્ષ_TYPE (arg1.કિંમત));
  વૃક્ષ type2 = (arg2.original_type
                ? arg2.original_type
                : વૃક્ષ_TYPE (arg2.કિંમત));

  result.કિંમત = build_દ્વિઅંકી_op (location, code,
				  arg1.કિંમત, arg2.કિંમત, સાચું);
  result.original_code = code;
  result.original_type = ખાલી;
  result.m_decimal = 0;

  જો (વૃક્ષ_CODE (result.કિંમત) == ERROR_MARK)
    {
      set_c_પદાવલિ_source_range (&result,
			       arg1.get_start (),
			       arg2.get_finish ());
      પાછા result;
    }

  જો (location != UNKNOWN_LOCATION)
    protected_set_પદાવલિ_location (result.કિંમત, location);

  set_c_પદાવલિ_source_range (&result,
			   arg1.get_start (),
			   arg2.get_finish ());

  /* Check for cases such as x+y<<z which users are likely
     to misinterpret.  */
  જો (warn_parentheses)
    warn_about_parentheses (location, code, code1, arg1.કિંમત, code2,
			    arg2.કિંમત);

  જો (warn_logical_op)
    warn_logical_operator (location, code, વૃક્ષ_TYPE (result.કિંમત),
			   code1, arg1.કિંમત, code2, arg2.કિંમત);

  જો (warn_constant_logical_operand
      && (code == TRUTH_ANDIF_પદાવલિ || code == TRUTH_ORIF_પદાવલિ)
      && INTEGRAL_NB_TYPE_P (type1)
      && INTEGRAL_NB_TYPE_P (type2))
    {
      અચલ અક્ષર *name = code == TRUTH_ANDIF_પદાવલિ ? "&&" : "||";
      જો (orig_arg1 == NULL_વૃક્ષ)
	orig_arg1 = arg1.કિંમત;
      auto enum_other_than_0_1 = [] (વૃક્ષ type) {
	જો (વૃક્ષ_CODE (type) != ENUMERAL_TYPE)
	  પાછા ખોટું;
	માટે (વૃક્ષ l = TYPE_કિંમતો (type); l; l = વૃક્ષ_CHAIN (l))
	  {
	    વૃક્ષ v = DECL_INITIAL (વૃક્ષ_કિંમત (l));
	    જો (!integer_zerop (v) && !integer_onep (v))
	      પાછા સાચું;
	  }
	પાછા ખોટું;
      };
      auto diagnose_constant_logical_operand = [=] (વૃક્ષ val, વૃક્ષ type) {
	જો (વૃક્ષ_CODE (val) != INTEGER_CST || integer_zerop (val))
	  પાછા ખોટું;
	જો (integer_onep (val) && !enum_other_than_0_1 (type))
	  પાછા ખોટું;
	gcc_rich_location richloc (location);
	richloc.add_fixit_replace (name + 1);
	auto_diagnostic_group d;
	જો (warning_at (location, OPT_Wconstant_logical_operand,
			"use of logical %qs with constant operand %qE",
			name, val))
	  inform (&richloc, "use %qs for bitwise operation", name + 1);
	પાછા સાચું;
      };
      જો (!diagnose_constant_logical_operand (arg2.કિંમત, type2))
	diagnose_constant_logical_operand (orig_arg1, type1);
    }

  જો (warn_tautological_compare)
    {
      વૃક્ષ lhs = arg1.કિંમત;
      વૃક્ષ rhs = arg2.કિંમત;
      જો (વૃક્ષ_CODE (lhs) == C_MAYBE_CONST_પદાવલિ)
	{
	  જો (C_MAYBE_CONST_પદાવલિ_PRE (lhs) != NULL_વૃક્ષ
	      && વૃક્ષ_SIDE_EFFECTS (C_MAYBE_CONST_પદાવલિ_PRE (lhs)))
	    lhs = NULL_વૃક્ષ;
	  નહીંતર
	    lhs = C_MAYBE_CONST_પદાવલિ_પદાવલિ (lhs);
	}
      જો (વૃક્ષ_CODE (rhs) == C_MAYBE_CONST_પદાવલિ)
	{
	  જો (C_MAYBE_CONST_પદાવલિ_PRE (rhs) != NULL_વૃક્ષ
	      && વૃક્ષ_SIDE_EFFECTS (C_MAYBE_CONST_પદાવલિ_PRE (rhs)))
	    rhs = NULL_વૃક્ષ;
	  નહીંતર
	    rhs = C_MAYBE_CONST_પદાવલિ_પદાવલિ (rhs);
	}
      જો (lhs != NULL_વૃક્ષ && rhs != NULL_વૃક્ષ)
	warn_tautological_cmp (location, code, lhs, rhs);
    }

  જો (warn_logical_not_paren
      && વૃક્ષ_CODE_CLASS (code) == tcc_comparison
      && code1 == TRUTH_NOT_પદાવલિ
      && code2 != TRUTH_NOT_પદાવલિ
      /* Avoid warning for !!x == y.  */
      && (વૃક્ષ_CODE (arg1.કિંમત) != NE_પદાવલિ
	  || !integer_zerop (વૃક્ષ_OPERAND (arg1.કિંમત, 1))))
    {
      /* Avoid warning for !b == y where b has _Bool type.  */
      વૃક્ષ t = integer_zero_ગાંઠ;
      જો (વૃક્ષ_CODE (arg1.કિંમત) == EQ_પદાવલિ
	  && integer_zerop (વૃક્ષ_OPERAND (arg1.કિંમત, 1))
	  && વૃક્ષ_TYPE (વૃક્ષ_OPERAND (arg1.કિંમત, 0)) == integer_type_ગાંઠ)
	{
	  t = વૃક્ષ_OPERAND (arg1.કિંમત, 0);
	  કરો
	    {
	      જો (વૃક્ષ_TYPE (t) != integer_type_ગાંઠ)
		તોડો;
	      જો (વૃક્ષ_CODE (t) == C_MAYBE_CONST_પદાવલિ)
		t = C_MAYBE_CONST_પદાવલિ_પદાવલિ (t);
	      નહીંતર જો (CONVERT_પદાવલિ_P (t))
		t = વૃક્ષ_OPERAND (t, 0);
	      નહીંતર
		તોડો;
	    }
	  જ્યારે (1);
	}
      જો (!C_BOOLEAN_TYPE_P (વૃક્ષ_TYPE (t)))
	warn_logical_not_parentheses (location, code, arg1.કિંમત, arg2.કિંમત);
    }

  /* Warn about comparisons against string literals, with the exception
     of testing for equality or inequality of a string literal with NULL.  */
  જો (code == EQ_પદાવલિ || code == NE_પદાવલિ)
    {
      જો ((code1 == STRING_CST
	   && !integer_zerop (વૃક્ષ_strip_nop_conversions (arg2.કિંમત)))
	  || (code2 == STRING_CST
	      && !integer_zerop (વૃક્ષ_strip_nop_conversions (arg1.કિંમત))))
	warning_at (location, OPT_Waddress,
		    "comparison with string literal results in unspecified behavior");
      /* Warn for ptr == '\0', it's likely that it should've been ptr[0].  */
      જો (POINTER_TYPE_P (type1)
	  && null_pointer_constant_p (arg2.કિંમત)
	  && char_type_p (type2))
	{
	  auto_diagnostic_group d;
	  જો (warning_at (location, OPT_Wpointer_compare,
			    "comparison between pointer and zero character "
			    "constant"))
	    inform (arg1.get_start (),
		      "did you mean to dereference the pointer?");
	}
      નહીંતર જો (POINTER_TYPE_P (type2)
	       && null_pointer_constant_p (arg1.કિંમત)
	       && char_type_p (type1))
	{
	  auto_diagnostic_group d;
	  જો (warning_at (location, OPT_Wpointer_compare,
			    "comparison between pointer and zero character "
			    "constant"))
	    inform (arg2.get_start (),
		      "did you mean to dereference the pointer?");
	}
    }
  નહીંતર જો (વૃક્ષ_CODE_CLASS (code) == tcc_comparison
	   && (code1 == STRING_CST || code2 == STRING_CST))
    warning_at (location, OPT_Waddress,
		"comparison with string literal results in unspecified "
		"behavior");

  જો (warn_zero_as_null_pointer_constant
      && c_inhibit_evaluation_warnings == 0
      && વૃક્ષ_CODE_CLASS (code) == tcc_comparison)
    {
      જો ((વૃક્ષ_CODE (type1) == POINTER_TYPE
	   || વૃક્ષ_CODE (type1) == NULLPTR_TYPE)
	  && INTEGRAL_TYPE_P (type2)
	  && null_pointer_constant_p (arg2.કિંમત))
	warning_at (arg2.get_location(), OPT_Wzero_as_null_pointer_constant,
		    "zero as null pointer constant");

      જો ((વૃક્ષ_CODE (type2) == POINTER_TYPE
	   || વૃક્ષ_CODE (type2) == NULLPTR_TYPE)
	  && INTEGRAL_TYPE_P (type1)
	  && null_pointer_constant_p (arg1.કિંમત))
	warning_at (arg1.get_location(), OPT_Wzero_as_null_pointer_constant,
		    "zero as null pointer constant");
    }

  જો (warn_array_compare
      && વૃક્ષ_CODE_CLASS (code) == tcc_comparison
      && વૃક્ષ_CODE (type1) == ARRAY_TYPE
      && વૃક્ષ_CODE (type2) == ARRAY_TYPE)
    do_warn_array_compare (location, code, arg1.કિંમત, arg2.કિંમત);

  જો (વૃક્ષ_OVERFLOW_P (result.કિંમત)
      && !વૃક્ષ_OVERFLOW_P (arg1.કિંમત)
      && !વૃક્ષ_OVERFLOW_P (arg2.કિંમત))
    overflow_warning (location, result.કિંમત);

  /* Warn about comparisons of different enum types.  */
  જો (warn_enum_compare
      && વૃક્ષ_CODE_CLASS (code) == tcc_comparison
      && વૃક્ષ_CODE (type1) == ENUMERAL_TYPE
      && વૃક્ષ_CODE (type2) == ENUMERAL_TYPE
      && TYPE_MAIN_VARIANT (type1) != TYPE_MAIN_VARIANT (type2))
    warning_at (location, OPT_Wenum_compare,
		"comparison between %qT and %qT",
		type1, type2);

  જો (warn_xor_used_as_pow
      && code == BIT_XOR_પદાવલિ
      && arg1.m_decimal
      && arg2.m_decimal)
    check_for_xor_used_as_pow (arg1.get_location (), arg1.કિંમત,
			       location,
			       arg2.get_location (), arg2.કિંમત);

  પાછા result;
}

/* Return a tree for the difference of pointers OP0 and OP1.
   The resulting tree has type ptrdiff_t.  If POINTER_SUBTRACT sanitization is
   enabled, assign to INSTRUMENT_EXPR call to libsanitizer.  */

સ્થિર વૃક્ષ
pointer_diff (location_t loc, વૃક્ષ op0, વૃક્ષ op1, વૃક્ષ *instrument_પદાવલિ)
{
  વૃક્ષ restype = ptrdiff_type_ગાંઠ;
  વૃક્ષ result, inttype;

  addr_space_t as0 = TYPE_ADDR_SPACE (વૃક્ષ_TYPE (વૃક્ષ_TYPE (op0)));
  addr_space_t as1 = TYPE_ADDR_SPACE (વૃક્ષ_TYPE (વૃક્ષ_TYPE (op1)));
  વૃક્ષ target_type = વૃક્ષ_TYPE (વૃક્ષ_TYPE (op0));
  વૃક્ષ orig_op0 = op0;
  વૃક્ષ orig_op1 = op1;

  /* If the operands point into different address spaces, we need to
     explicitly convert them to pointers into the common address space
     before we can subtract the numerical address values.  */
  જો (as0 != as1)
    {
      addr_space_t as_common;
      વૃક્ષ common_type;

      /* Determine the common superset address space.  This is guaranteed
	 to exist because the caller verified that comp_target_types
	 returned non-zero.  */
      જો (!addr_space_superset (as0, as1, &as_common))
	gcc_unreachable ();

      common_type = common_pointer_type (વૃક્ષ_TYPE (op0), વૃક્ષ_TYPE (op1), NULL_વૃક્ષ);
      op0 = convert (common_type, op0);
      op1 = convert (common_type, op1);
    }

  /* Determine integer type result of the subtraction.  This will usually
     be the same as the result type (ptrdiff_t), but may need to be a wider
     type if pointers for the address space are wider than ptrdiff_t.  */
  જો (TYPE_PRECISION (restype) < TYPE_PRECISION (વૃક્ષ_TYPE (op0)))
    inttype = c_common_type_for_size (TYPE_PRECISION (વૃક્ષ_TYPE (op0)), 0);
  નહીંતર
    inttype = restype;

  જો (VOID_TYPE_P (target_type))
    pedwarn (loc, OPT_Wpointer_arith,
	     "pointer of type %<void *%> used in subtraction");
  જો (વૃક્ષ_CODE (target_type) == FUNCTION_TYPE)
    pedwarn (loc, OPT_Wpointer_arith,
	     "pointer to a function used in subtraction");

  જો (current_function_decl != NULL_વૃક્ષ
      && sanitize_flags_p (SANITIZE_POINTER_SUBTRACT))
    {
      op0 = save_પદાવલિ (c_fully_fold (op0, ખોટું, ખાલી));
      op1 = save_પદાવલિ (c_fully_fold (op1, ખોટું, ખાલી));

      વૃક્ષ tt = builtin_decl_explicit (BUILT_IN_ASAN_POINTER_SUBTRACT);
      *instrument_પદાવલિ = build_call_પદાવલિ_loc (loc, tt, 2, op0, op1);
    }

  /* First do the subtraction, then build the divide operator
     and only convert at the very end.
     Do not do default conversions in case restype is a short type.  */

  /* POINTER_DIFF_EXPR requires a signed integer type of the same size as
     pointers.  If some platform cannot provide that, or has a larger
     ptrdiff_type to support differences larger than half the address
     space, cast the pointers to some larger integer type and do the
     computations in that type.  */
  જો (TYPE_PRECISION (inttype) > TYPE_PRECISION (વૃક્ષ_TYPE (op0)))
    op0 = build_દ્વિઅંકી_op (loc, MINUS_પદાવલિ, convert (inttype, op0),
			   convert (inttype, op1), ખોટું);
  નહીંતર
    {
      /* Cast away qualifiers.  */
      op0 = convert (c_common_type (વૃક્ષ_TYPE (op0), વૃક્ષ_TYPE (op0)), op0);
      op1 = convert (c_common_type (વૃક્ષ_TYPE (op1), વૃક્ષ_TYPE (op1)), op1);
      op0 = build2_loc (loc, POINTER_DIFF_પદાવલિ, inttype, op0, op1);
    }

  /* This generates an error if op1 is pointer to incomplete type.  */
  જો (!COMPLETE_OR_VOID_TYPE_P (વૃક્ષ_TYPE (વૃક્ષ_TYPE (orig_op1))))
    error_at (loc, "arithmetic on pointer to an incomplete type");
  નહીંતર જો (verify_type_context (loc, TCTX_POINTER_ARITH,
				વૃક્ષ_TYPE (વૃક્ષ_TYPE (orig_op0))))
    verify_type_context (loc, TCTX_POINTER_ARITH,
			 વૃક્ષ_TYPE (વૃક્ષ_TYPE (orig_op1)));

  op1 = c_size_in_bytes (target_type);

  જો (pointer_to_zero_sized_aggr_p (વૃક્ષ_TYPE (orig_op1)))
    error_at (loc, "arithmetic on pointer to an empty aggregate");

  /* Divide by the size, in easiest possible way.  */
  result = fold_build2_loc (loc, EXACT_DIV_પદાવલિ, inttype,
			    op0, convert (inttype, op1));

  /* Convert to final result type if necessary.  */
  પાછા convert (restype, result);
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

સ્થિર વૃક્ષ
build_atomic_assign (location_t loc, વૃક્ષ lhs, ગણના વૃક્ષ_code modifycode,
		     વૃક્ષ rhs, તાર્કિક return_old_p)
{
  વૃક્ષ fndecl, func_call;
  vec<વૃક્ષ, va_gc> *params;
  વૃક્ષ val, nonatomic_lhs_type, nonatomic_rhs_type, newval, newval_addr;
  વૃક્ષ old, old_addr;
  વૃક્ષ compound_stmt = NULL_વૃક્ષ;
  વૃક્ષ stmt, goto_stmt;
  વૃક્ષ loop_label, loop_decl, done_label, done_decl;

  વૃક્ષ lhs_type = વૃક્ષ_TYPE (lhs);
  વૃક્ષ lhs_addr = build_unary_op (loc, ADDR_પદાવલિ, lhs, ખોટું);
  વૃક્ષ seq_cst = build_int_cst (integer_type_ગાંઠ, MEMMODEL_SEQ_CST);
  વૃક્ષ rhs_semantic_type = વૃક્ષ_TYPE (rhs);
  વૃક્ષ nonatomic_rhs_semantic_type;
  વૃક્ષ rhs_type;

  gcc_assert (TYPE_ATOMIC (lhs_type));

  જો (return_old_p)
    gcc_assert (modifycode == PLUS_પદાવલિ || modifycode == MINUS_પદાવલિ);

  /* Allocate enough vector items for a compare_exchange.  */
  vec_alloc (params, 6);

  /* Create a compound statement to hold the sequence of statements
     with a loop.  */
  જો (modifycode != NOP_પદાવલિ)
    {
      compound_stmt = c_begin_compound_stmt (ખોટું);

      /* For consistency with build_modify_expr on non-_Atomic,
	 mark the lhs as read.  Also, it would be very hard to match
	 such expressions in mark_exp_read.  */
      mark_exp_read (lhs);
    }

  /* Remove any excess precision (which is only present here in the
     case of compound assignments).  */
  જો (વૃક્ષ_CODE (rhs) == EXCESS_PRECISION_પદાવલિ)
    {
      gcc_assert (modifycode != NOP_પદાવલિ);
      rhs = વૃક્ષ_OPERAND (rhs, 0);
    }
  rhs_type = વૃક્ષ_TYPE (rhs);

  /* Fold the RHS if it hasn't already been folded.  */
  જો (modifycode != NOP_પદાવલિ)
    rhs = c_fully_fold (rhs, ખોટું, ખાલી);

  /* Remove the qualifiers for the rest of the expressions and create
     the VAL temp variable to hold the RHS.  */
  nonatomic_lhs_type = build_qualified_type (lhs_type, TYPE_UNQUALIFIED);
  nonatomic_rhs_type = build_qualified_type (rhs_type, TYPE_UNQUALIFIED);
  nonatomic_rhs_semantic_type = build_qualified_type (rhs_semantic_type,
						      TYPE_UNQUALIFIED);
  val = create_tmp_var_raw (nonatomic_rhs_type);
  વૃક્ષ_ADDRESSABLE (val) = 1;
  suppress_warning (val);
  rhs = build4 (TARGET_પદાવલિ, nonatomic_rhs_type, val, rhs, NULL_વૃક્ષ,
		NULL_વૃક્ષ);
  વૃક્ષ_SIDE_EFFECTS (rhs) = 1;
  SET_પદાવલિ_LOCATION (rhs, loc);
  જો (modifycode != NOP_પદાવલિ)
    add_stmt (rhs);

  /* NOP_EXPR indicates it's a straight store of the RHS. Simply issue
     an atomic_store.  */
  જો (modifycode == NOP_પદાવલિ)
    {
      compound_stmt = rhs;
      /* Build __atomic_store (&lhs, &val, SEQ_CST)  */
      rhs = build_unary_op (loc, ADDR_પદાવલિ, val, ખોટું);
      fndecl = builtin_decl_explicit (BUILT_IN_ATOMIC_STORE);
      params->quick_ધકેલો (lhs_addr);
      params->quick_ધકેલો (rhs);
      params->quick_ધકેલો (seq_cst);
      func_call = c_build_function_call_vec (loc, vNULL, fndecl, params, ખાલી);

      compound_stmt = build2 (COMPOUND_પદાવલિ, void_type_ગાંઠ,
			      compound_stmt, func_call);

      /* VAL is the value which was stored, return a COMPOUND_STMT of
	 the statement and that value.  */
      પાછા build2 (COMPOUND_પદાવલિ, nonatomic_lhs_type, compound_stmt, val);
    }

  /* Attempt to implement the atomic operation as an __atomic_fetch_* or
     __atomic_*_fetch built-in rather than a CAS loop.  atomic_bool type
     isn't applicable for such builtins.  ??? Do we want to handle enums?  */
  જો ((વૃક્ષ_CODE (lhs_type) == INTEGER_TYPE || POINTER_TYPE_P (lhs_type))
      && વૃક્ષ_CODE (rhs_type) == INTEGER_TYPE)
    {
      built_in_function fncode;
      પસંદગી (modifycode)
	{
	સ્થિતિ PLUS_પદાવલિ:
	સ્થિતિ POINTER_PLUS_પદાવલિ:
	  fncode = (return_old_p
		    ? BUILT_IN_ATOMIC_FETCH_ADD_N
		    : BUILT_IN_ATOMIC_ADD_FETCH_N);
	  તોડો;
	સ્થિતિ MINUS_પદાવલિ:
	  fncode = (return_old_p
		    ? BUILT_IN_ATOMIC_FETCH_SUB_N
		    : BUILT_IN_ATOMIC_SUB_FETCH_N);
	  તોડો;
	સ્થિતિ BIT_AND_પદાવલિ:
	  fncode = (return_old_p
		    ? BUILT_IN_ATOMIC_FETCH_AND_N
		    : BUILT_IN_ATOMIC_AND_FETCH_N);
	  તોડો;
	સ્થિતિ BIT_IOR_પદાવલિ:
	  fncode = (return_old_p
		    ? BUILT_IN_ATOMIC_FETCH_OR_N
		    : BUILT_IN_ATOMIC_OR_FETCH_N);
	  તોડો;
	સ્થિતિ BIT_XOR_પદાવલિ:
	  fncode = (return_old_p
		    ? BUILT_IN_ATOMIC_FETCH_XOR_N
		    : BUILT_IN_ATOMIC_XOR_FETCH_N);
	  તોડો;
	મૂળભૂત:
	  જાઓ cas_loop;
	}

      /* We can only use "_1" through "_16" variants of the atomic fetch
	 built-ins.  */
      unsigned HOST_WIDE_INT size = વૃક્ષ_to_uhwi (TYPE_SIZE_UNIT (lhs_type));
      જો (size != 1 && size != 2 && size != 4 && size != 8 && size != 16)
	જાઓ cas_loop;

      /* If this is a pointer type, we need to multiply by the size of
	 the pointer target type.  */
      જો (POINTER_TYPE_P (lhs_type))
	{
	  જો (!COMPLETE_TYPE_P (વૃક્ષ_TYPE (lhs_type))
	      /* ??? This would introduce -Wdiscarded-qualifiers
		 warning: __atomic_fetch_* expect volatile void *
		 type as the first argument.  (Assignments between
		 atomic and non-atomic objects are OK.) */
	      || TYPE_RESTRICT (lhs_type))
	    જાઓ cas_loop;
	  વૃક્ષ sz = TYPE_SIZE_UNIT (વૃક્ષ_TYPE (lhs_type));
	  rhs = fold_build2_loc (loc, MULT_પદાવલિ, ptrdiff_type_ગાંઠ,
				 convert (ptrdiff_type_ગાંઠ, rhs),
				 convert (ptrdiff_type_ગાંઠ, sz));
	}

      /* Build __atomic_fetch_* (&lhs, &val, SEQ_CST), or
	 __atomic_*_fetch (&lhs, &val, SEQ_CST).  */
      fndecl = builtin_decl_explicit (fncode);
      params->quick_ધકેલો (lhs_addr);
      params->quick_ધકેલો (rhs);
      params->quick_ધકેલો (seq_cst);
      func_call = c_build_function_call_vec (loc, vNULL, fndecl, params, ખાલી);

      newval = create_tmp_var_raw (nonatomic_lhs_type);
      વૃક્ષ_ADDRESSABLE (newval) = 1;
      suppress_warning (newval);
      rhs = build4 (TARGET_પદાવલિ, nonatomic_lhs_type, newval, func_call,
		    NULL_વૃક્ષ, NULL_વૃક્ષ);
      SET_પદાવલિ_LOCATION (rhs, loc);
      add_stmt (rhs);

      /* Finish the compound statement.  */
      compound_stmt = c_end_compound_stmt (loc, compound_stmt, ખોટું);

      /* NEWVAL is the value which was stored, return a COMPOUND_STMT of
	 the statement and that value.  */
      પાછા build2 (COMPOUND_પદાવલિ, nonatomic_lhs_type, compound_stmt, newval);
    }

cas_loop:
  /* Create the variables and labels required for the op= form.  */
  old = create_tmp_var_raw (nonatomic_lhs_type);
  old_addr = build_unary_op (loc, ADDR_પદાવલિ, old, ખોટું);
  વૃક્ષ_ADDRESSABLE (old) = 1;
  suppress_warning (old);

  newval = create_tmp_var_raw (nonatomic_lhs_type);
  newval_addr = build_unary_op (loc, ADDR_પદાવલિ, newval, ખોટું);
  વૃક્ષ_ADDRESSABLE (newval) = 1;
  suppress_warning (newval);

  loop_decl = create_artificial_label (loc);
  loop_label = build1 (LABEL_પદાવલિ, void_type_ગાંઠ, loop_decl);

  done_decl = create_artificial_label (loc);
  done_label = build1 (LABEL_પદાવલિ, void_type_ગાંઠ, done_decl);

  /* __atomic_load (addr, &old, SEQ_CST).  */
  fndecl = builtin_decl_explicit (BUILT_IN_ATOMIC_LOAD);
  params->quick_ધકેલો (lhs_addr);
  params->quick_ધકેલો (old_addr);
  params->quick_ધકેલો (seq_cst);
  func_call = c_build_function_call_vec (loc, vNULL, fndecl, params, ખાલી);
  old = build4 (TARGET_પદાવલિ, nonatomic_lhs_type, old, func_call, NULL_વૃક્ષ,
		NULL_વૃક્ષ);
  add_stmt (old);
  params->truncate (0);

  /* Create the expressions for floating-point environment
     manipulation, if required.  */
  તાર્કિક need_fenv = (flag_trapping_math
		    && (FLOAT_TYPE_P (lhs_type) || FLOAT_TYPE_P (rhs_type)));
  વૃક્ષ hold_call = NULL_વૃક્ષ, clear_call = NULL_વૃક્ષ, update_call = NULL_વૃક્ષ;
  જો (need_fenv)
    targetm.atomic_assign_expand_fenv (&hold_call, &clear_call, &update_call);

  જો (hold_call)
    add_stmt (hold_call);

  /* loop:  */
  add_stmt (loop_label);

  /* newval = old + val;  */
  જો (rhs_type != rhs_semantic_type)
    val = build1 (EXCESS_PRECISION_પદાવલિ, nonatomic_rhs_semantic_type, val);
  rhs = build_દ્વિઅંકી_op (loc, modifycode,
			 convert_lvalue_to_rvalue (loc, old, સાચું, સાચું),
			 val, સાચું);
  જો (વૃક્ષ_CODE (rhs) == EXCESS_PRECISION_પદાવલિ)
    {
      વૃક્ષ eptype = વૃક્ષ_TYPE (rhs);
      rhs = c_fully_fold (વૃક્ષ_OPERAND (rhs, 0), ખોટું, ખાલી);
      rhs = build1 (EXCESS_PRECISION_પદાવલિ, eptype, rhs);
    }
  નહીંતર
    rhs = c_fully_fold (rhs, ખોટું, ખાલી);
  rhs = convert_for_assignment (loc, UNKNOWN_LOCATION, nonatomic_lhs_type,
				rhs, NULL_વૃક્ષ, ic_assign, ખોટું, NULL_વૃક્ષ,
				NULL_વૃક્ષ, 0);
  /* The temporary variable for NEWVAL is only gimplified correctly (in
     particular, given a DECL_CONTEXT) if used in a TARGET_EXPR.  To avoid
     subsequent ICEs in nested function processing after an error, ensure such
     a TARGET_EXPR is built even after an error.  */
  જો (rhs == error_mark_ગાંઠ)
    rhs = old;
  rhs = build4 (TARGET_પદાવલિ, nonatomic_lhs_type, newval, rhs, NULL_વૃક્ષ,
		NULL_વૃક્ષ);
  SET_પદાવલિ_LOCATION (rhs, loc);
  add_stmt (rhs);

  /* if (__atomic_compare_exchange (addr, &old, &new, false, SEQ_CST, SEQ_CST))
       goto done;  */
  fndecl = builtin_decl_explicit (BUILT_IN_ATOMIC_COMPARE_EXCHANGE);
  params->quick_ધકેલો (lhs_addr);
  params->quick_ધકેલો (old_addr);
  params->quick_ધકેલો (newval_addr);
  params->quick_ધકેલો (integer_zero_ગાંઠ);
  params->quick_ધકેલો (seq_cst);
  params->quick_ધકેલો (seq_cst);
  func_call = c_build_function_call_vec (loc, vNULL, fndecl, params, ખાલી);

  goto_stmt = build1 (GOTO_પદાવલિ, void_type_ગાંઠ, done_decl);
  SET_પદાવલિ_LOCATION (goto_stmt, loc);

  stmt = build3 (COND_પદાવલિ, void_type_ગાંઠ, func_call, goto_stmt, NULL_વૃક્ષ);
  SET_પદાવલિ_LOCATION (stmt, loc);
  add_stmt (stmt);

  જો (clear_call)
    add_stmt (clear_call);

  /* goto loop;  */
  goto_stmt  = build1 (GOTO_પદાવલિ, void_type_ગાંઠ, loop_decl);
  SET_પદાવલિ_LOCATION (goto_stmt, loc);
  add_stmt (goto_stmt);

  /* done:  */
  add_stmt (done_label);

  જો (update_call)
    add_stmt (update_call);

  /* Finish the compound statement.  */
  compound_stmt = c_end_compound_stmt (loc, compound_stmt, ખોટું);

  /* NEWVAL is the value that was successfully stored, return a
     COMPOUND_EXPR of the statement and the appropriate value.  */
  પાછા build2 (COMPOUND_પદાવલિ, nonatomic_lhs_type, compound_stmt,
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

વૃક્ષ
build_unary_op (location_t location, ગણના વૃક્ષ_code code, વૃક્ષ xarg,
		તાર્કિક noconvert)
{
  /* No default_conversion here.  It causes trouble for ADDR_EXPR.  */
  વૃક્ષ arg = xarg;
  વૃક્ષ argtype = NULL_વૃક્ષ;
  ગણના વૃક્ષ_code typecode;
  વૃક્ષ val;
  વૃક્ષ ret = error_mark_ગાંઠ;
  વૃક્ષ eptype = NULL_વૃક્ષ;
  અચલ અક્ષર *invalid_op_diag;

  /* If ARG is wrapped in a call to .ACCESS_WITH_SIZE — created when the
     C parser rvalue-converts a counted_by-annotated member access (see
     PR123569) — unwrap it here.  Unary operators that consume an rvalue
     (!, -, +) read the value itself rather than dereferencing into the
     pointed-to data, so the bounds-checking wrapper is unnecessary and
     would otherwise reach build_unary_op while it is not equipped to
     handle the wrapped form.  PR123569 fixed the ++/-- side of this by
     suppressing wrapper creation in the parser; the rvalue-consuming
     ops still receive the wrapper and need to strip it here.  */
  જો (is_access_with_size_p (arg))
    xarg = arg = get_ref_from_access_with_size (arg);

  gcc_checking_assert (!is_access_with_size_p (arg));

  તાર્કિક int_operands = પદાવલિ_INT_CONST_OPERANDS (xarg);
  જો (int_operands)
    arg = remove_c_maybe_const_પદાવલિ (arg);

  જો (code != ADDR_પદાવલિ)
    arg = require_complete_type (location, arg);

  typecode = વૃક્ષ_CODE (વૃક્ષ_TYPE (arg));
  જો (typecode == ERROR_MARK)
    પાછા error_mark_ગાંઠ;
  જો (typecode == ENUMERAL_TYPE || typecode == BOOLEAN_TYPE)
    typecode = INTEGER_TYPE;

  જો ((invalid_op_diag
       = targetm.invalid_unary_op (code, વૃક્ષ_TYPE (xarg))))
    {
      error_at (location, invalid_op_diag);
      પાછા error_mark_ગાંઠ;
    }

  જો (વૃક્ષ_CODE (arg) == EXCESS_PRECISION_પદાવલિ)
    {
      eptype = વૃક્ષ_TYPE (arg);
      arg = વૃક્ષ_OPERAND (arg, 0);
    }

  પસંદગી (code)
    {
    સ્થિતિ CONVERT_પદાવલિ:
      /* This is used for unary plus, because a CONVERT_EXPR
	 is enough to prevent anybody from looking inside for
	 associativity, but won't generate any code.  */
      જો (!(typecode == INTEGER_TYPE || typecode == REAL_TYPE
	    || typecode == FIXED_POINT_TYPE || typecode == COMPLEX_TYPE
	    || typecode == BITINT_TYPE
	    || gnu_vector_type_p (વૃક્ષ_TYPE (arg))))
	{
	  error_at (location, "wrong type argument to unary plus");
	  પાછા error_mark_ગાંઠ;
	}
      નહીંતર જો (!noconvert)
	arg = default_conversion (arg);
      arg = non_lvalue_loc (location, arg);
      તોડો;

    સ્થિતિ NEGATE_પદાવલિ:
      જો (!(typecode == INTEGER_TYPE || typecode == REAL_TYPE
	    || typecode == FIXED_POINT_TYPE || typecode == COMPLEX_TYPE
	    || typecode == BITINT_TYPE
	    || gnu_vector_type_p (વૃક્ષ_TYPE (arg))))
	{
	  error_at (location, "wrong type argument to unary minus");
	  પાછા error_mark_ગાંઠ;
	}
      નહીંતર જો (!noconvert)
	arg = default_conversion (arg);
      તોડો;

    સ્થિતિ BIT_NOT_પદાવલિ:
      /* ~ works on integer types and non float vectors. */
      જો (typecode == INTEGER_TYPE
	  || typecode == BITINT_TYPE
	  || (gnu_vector_type_p (વૃક્ષ_TYPE (arg))
	      && !VECTOR_FLOAT_TYPE_P (વૃક્ષ_TYPE (arg))))
	{
	  વૃક્ષ e = arg;

	  /* Warn if the expression has boolean value.  */
	  જ્યારે (વૃક્ષ_CODE (e) == COMPOUND_પદાવલિ)
	    e = વૃક્ષ_OPERAND (e, 1);

	  જો ((C_BOOLEAN_TYPE_P (વૃક્ષ_TYPE (arg))
	       || truth_કિંમત_p (વૃક્ષ_CODE (e))))
	    {
	      auto_diagnostic_group d;
	      જો (warning_at (location, OPT_Wbool_operation,
				"%<~%> on a boolean expression"))
		{
		  gcc_rich_location richloc (location);
		  richloc.add_fixit_ઉમેરો_before (location, "!");
		  inform (&richloc, "did you mean to use logical not?");
		}
	    }
	  જો (!noconvert)
	    arg = default_conversion (arg);
	}
      નહીંતર જો (typecode == COMPLEX_TYPE)
	{
	  code = CONJ_પદાવલિ;
	  pedwarn (location, OPT_Wpedantic,
		   "ISO C does not support %<~%> for complex conjugation");
	  જો (!noconvert)
	    arg = default_conversion (arg);
	}
      નહીંતર
	{
	  error_at (location, "wrong type argument to bit-complement");
	  પાછા error_mark_ગાંઠ;
	}
      તોડો;

    સ્થિતિ ABS_પદાવલિ:
      જો (!(typecode == INTEGER_TYPE || typecode == REAL_TYPE))
	{
	  error_at (location, "wrong type argument to abs");
	  પાછા error_mark_ગાંઠ;
	}
      નહીંતર જો (!noconvert)
	arg = default_conversion (arg);
      તોડો;

    સ્થિતિ ABSU_પદાવલિ:
      જો (!(typecode == INTEGER_TYPE))
	{
	  error_at (location, "wrong type argument to absu");
	  પાછા error_mark_ગાંઠ;
	}
      નહીંતર જો (!noconvert)
	arg = default_conversion (arg);
      તોડો;

    સ્થિતિ CONJ_પદાવલિ:
      /* Conjugating a real value is a no-op, but allow it anyway.  */
      જો (!(typecode == INTEGER_TYPE || typecode == REAL_TYPE
	    || typecode == COMPLEX_TYPE))
	{
	  error_at (location, "wrong type argument to conjugation");
	  પાછા error_mark_ગાંઠ;
	}
      નહીંતર જો (!noconvert)
	arg = default_conversion (arg);
      તોડો;

    સ્થિતિ TRUTH_NOT_પદાવલિ:
      જો (typecode != INTEGER_TYPE && typecode != FIXED_POINT_TYPE
	  && typecode != REAL_TYPE && typecode != POINTER_TYPE
	  && typecode != COMPLEX_TYPE && typecode != NULLPTR_TYPE
	  && typecode != BITINT_TYPE)
	{
	  error_at (location,
		    "wrong type argument to unary exclamation mark");
	  પાછા error_mark_ગાંઠ;
	}
      જો (int_operands)
	{
	  arg = c_objc_common_truthvalue_conversion (location, xarg);
	  arg = remove_c_maybe_const_પદાવલિ (arg);
	}
      નહીંતર
	arg = c_objc_common_truthvalue_conversion (location, arg);
      ret = invert_truthvalue_loc (location, arg);
      eptype = NULL_વૃક્ષ;
      /* If the TRUTH_NOT_EXPR has been folded, reset the location.  */
      જો (પદાવલિ_P (ret) && પદાવલિ_HAS_LOCATION (ret))
	location = પદાવલિ_LOCATION (ret);
      જાઓ return_build_unary_op;

    સ્થિતિ REALPART_પદાવલિ:
    સ્થિતિ IMAGPART_પદાવલિ:
      ret = build_real_imag_પદાવલિ (location, code, arg);
      જો (ret == error_mark_ગાંઠ)
	પાછા error_mark_ગાંઠ;
      જો (eptype && વૃક્ષ_CODE (eptype) == COMPLEX_TYPE)
	eptype = વૃક્ષ_TYPE (eptype);
      જાઓ return_build_unary_op;

    સ્થિતિ PREINCREMENT_પદાવલિ:
    સ્થિતિ POSTINCREMENT_પદાવલિ:
    સ્થિતિ PREDECREMENT_પદાવલિ:
    સ્થિતિ POSTDECREMENT_પદાવલિ:

      જો (વૃક્ષ_CODE (arg) == C_MAYBE_CONST_પદાવલિ)
	{
	  વૃક્ષ inner = build_unary_op (location, code,
				       C_MAYBE_CONST_પદાવલિ_પદાવલિ (arg),
				       noconvert);
	  જો (inner == error_mark_ગાંઠ)
	    પાછા error_mark_ગાંઠ;
	  ret = build2 (C_MAYBE_CONST_પદાવલિ, વૃક્ષ_TYPE (inner),
			C_MAYBE_CONST_પદાવલિ_PRE (arg), inner);
	  gcc_assert (!C_MAYBE_CONST_પદાવલિ_INT_OPERANDS (arg));
	  C_MAYBE_CONST_પદાવલિ_NON_CONST (ret) = 1;
	  જાઓ return_build_unary_op;
	}

      /* Complain about anything that is not a true lvalue.  In
	 Objective-C, skip this check for property_refs.  */
      જો (!objc_is_property_ref (arg)
	  && !lvalue_or_else (location,
			      arg, ((code == PREINCREMENT_પદાવલિ
				     || code == POSTINCREMENT_પદાવલિ)
				    ? lv_increment
				    : lv_decrement)))
	પાછા error_mark_ગાંઠ;

      જો (warn_cxx_compat && વૃક્ષ_CODE (વૃક્ષ_TYPE (arg)) == ENUMERAL_TYPE)
	{
	  જો (code == PREINCREMENT_પદાવલિ || code == POSTINCREMENT_પદાવલિ)
	    warning_at (location, OPT_Wc___compat,
			"increment of enumeration value is invalid in C++");
	  નહીંતર
	    warning_at (location, OPT_Wc___compat,
			"decrement of enumeration value is invalid in C++");
	}

      જો (C_BOOLEAN_TYPE_P (વૃક્ષ_TYPE (arg)))
	{
	  જો (code == PREINCREMENT_પદાવલિ || code == POSTINCREMENT_પદાવલિ)
	    warning_at (location, OPT_Wbool_operation,
			"increment of a boolean expression");
	  નહીંતર
	    warning_at (location, OPT_Wbool_operation,
			"decrement of a boolean expression");
	}

      /* Ensure the argument is fully folded inside any SAVE_EXPR.  */
      arg = c_fully_fold (arg, ખોટું, ખાલી, સાચું);

      તાર્કિક atomic_op;
      atomic_op = really_atomic_lvalue (arg);

      /* Increment or decrement the real part of the value,
	 and don't change the imaginary part.  */
      જો (typecode == COMPLEX_TYPE)
	{
	  વૃક્ષ real, imag;

	  pedwarn_c23 (location, OPT_Wpedantic,
		       "ISO C does not support %<++%> and %<--%> on complex "
		       "types before C2Y");

	  જો (!atomic_op)
	    {
	      arg = stabilize_reference (arg);
	      real = build_unary_op (પદાવલિ_LOCATION (arg), REALPART_પદાવલિ, arg,
				     સાચું);
	      imag = build_unary_op (પદાવલિ_LOCATION (arg), IMAGPART_પદાવલિ, arg,
				     સાચું);
	      real = build_unary_op (પદાવલિ_LOCATION (arg), code, real, સાચું);
	      જો (real == error_mark_ગાંઠ || imag == error_mark_ગાંઠ)
		પાછા error_mark_ગાંઠ;
	      ret = build2 (COMPLEX_પદાવલિ, વૃક્ષ_TYPE (arg),
			    real, imag);
	      જાઓ return_build_unary_op;
	    }
	}

      /* Report invalid types.  */

      જો (typecode != POINTER_TYPE && typecode != FIXED_POINT_TYPE
	  && typecode != INTEGER_TYPE && typecode != REAL_TYPE
	  && typecode != COMPLEX_TYPE && typecode != BITINT_TYPE
	  && !gnu_vector_type_p (વૃક્ષ_TYPE (arg)))
	{
	  જો (code == PREINCREMENT_પદાવલિ || code == POSTINCREMENT_પદાવલિ)
	    error_at (location, "wrong type argument to increment");
	  નહીંતર
	    error_at (location, "wrong type argument to decrement");

	  પાછા error_mark_ગાંઠ;
	}

      {
	વૃક્ષ inc;

	argtype = વૃક્ષ_TYPE (arg);

	/* Compute the increment.  */

	જો (typecode == POINTER_TYPE)
	  {
	    /* If pointer target is an incomplete type,
	       we just cannot know how to do the arithmetic.  */
	    જો (!COMPLETE_OR_VOID_TYPE_P (વૃક્ષ_TYPE (argtype)))
	      {
		જો (code == PREINCREMENT_પદાવલિ || code == POSTINCREMENT_પદાવલિ)
		  error_at (location,
			    "increment of pointer to an incomplete type %qT",
			    વૃક્ષ_TYPE (argtype));
		નહીંતર
		  error_at (location,
			    "decrement of pointer to an incomplete type %qT",
			    વૃક્ષ_TYPE (argtype));
	      }
	    નહીંતર જો (વૃક્ષ_CODE (વૃક્ષ_TYPE (argtype)) == FUNCTION_TYPE
		     || VOID_TYPE_P (વૃક્ષ_TYPE (argtype)))
	      {
		જો (code == PREINCREMENT_પદાવલિ || code == POSTINCREMENT_પદાવલિ)
		  pedwarn (location, OPT_Wpointer_arith,
			   "wrong type argument to increment");
		નહીંતર
		  pedwarn (location, OPT_Wpointer_arith,
			   "wrong type argument to decrement");
	      }
	    નહીંતર
	      verify_type_context (location, TCTX_POINTER_ARITH,
				   વૃક્ષ_TYPE (argtype));

	    inc = c_size_in_bytes (વૃક્ષ_TYPE (argtype));
	    inc = convert_to_ptrofftype_loc (location, inc);
	  }
	નહીંતર જો (FRACT_MODE_P (TYPE_MODE (argtype)))
	  {
	    /* For signed fract types, we invert ++ to -- or
	       -- to ++, and change inc from 1 to -1, because
	       it is not possible to represent 1 in signed fract constants.
	       For unsigned fract types, the result always overflows and
	       we get an undefined (original) or the maximum value.  */
	    જો (code == PREINCREMENT_પદાવલિ)
	      code = PREDECREMENT_પદાવલિ;
	    નહીંતર જો (code == PREDECREMENT_પદાવલિ)
	      code = PREINCREMENT_પદાવલિ;
	    નહીંતર જો (code == POSTINCREMENT_પદાવલિ)
	      code = POSTDECREMENT_પદાવલિ;
	    નહીંતર /* code == POSTDECREMENT_EXPR  */
	      code = POSTINCREMENT_પદાવલિ;

	    inc = integer_minus_one_ગાંઠ;
	    inc = convert (argtype, inc);
	  }
	નહીંતર
	  {
	    inc = VECTOR_TYPE_P (argtype)
	      ? build_one_cst (argtype)
	      : integer_one_ગાંઠ;
	    inc = convert (argtype, inc);
	  }

	/* If 'arg' is an Objective-C PROPERTY_REF expression, then we
	   need to ask Objective-C to build the increment or decrement
	   expression for it.  */
	જો (objc_is_property_ref (arg))
	  પાછા objc_build_incr_પદાવલિ_for_property_ref (location, code,
							arg, inc);

	/* Report a read-only lvalue.  */
	જો (TYPE_READONLY (argtype))
	  {
	    readonly_error (location, arg,
			    ((code == PREINCREMENT_પદાવલિ
			      || code == POSTINCREMENT_પદાવલિ)
			     ? lv_increment : lv_decrement));
	    પાછા error_mark_ગાંઠ;
	  }
	નહીંતર જો (વૃક્ષ_READONLY (arg))
	  readonly_warning (arg,
			    ((code == PREINCREMENT_પદાવલિ
			      || code == POSTINCREMENT_પદાવલિ)
			     ? lv_increment : lv_decrement));

	/* If the argument is atomic, use the special code sequences for
	   atomic compound assignment.  */
	જો (atomic_op)
	  {
	    arg = stabilize_reference (arg);
	    ret = build_atomic_assign (location, arg,
				       ((code == PREINCREMENT_પદાવલિ
					 || code == POSTINCREMENT_પદાવલિ)
					? PLUS_પદાવલિ
					: MINUS_પદાવલિ),
				       (FRACT_MODE_P (TYPE_MODE (argtype))
					? inc
					: integer_one_ગાંઠ),
				       (code == POSTINCREMENT_પદાવલિ
					|| code == POSTDECREMENT_પદાવલિ));
	    જાઓ return_build_unary_op;
	  }

	વૃક્ષ true_res;
	જો (c_hardbool_type_attr (વૃક્ષ_TYPE (arg), ખાલી, &true_res))
	  {
	    વૃક્ષ larg = stabilize_reference (arg);
	    વૃક્ષ sarg = save_પદાવલિ (larg);
	    પસંદગી (code)
	      {
	      સ્થિતિ PREINCREMENT_પદાવલિ:
		val = build2 (MODIFY_પદાવલિ, વૃક્ષ_TYPE (larg), larg, true_res);
		val = build2 (COMPOUND_પદાવલિ, વૃક્ષ_TYPE (larg), sarg, val);
		તોડો;
	      સ્થિતિ POSTINCREMENT_પદાવલિ:
		val = build2 (MODIFY_પદાવલિ, વૃક્ષ_TYPE (larg), larg, true_res);
		val = build2 (COMPOUND_પદાવલિ, વૃક્ષ_TYPE (larg), val, sarg);
		val = build2 (COMPOUND_પદાવલિ, વૃક્ષ_TYPE (larg), sarg, val);
		તોડો;
	      સ્થિતિ PREDECREMENT_પદાવલિ:
		{
		  વૃક્ષ rarg = convert_lvalue_to_rvalue (location, sarg,
							સાચું, સાચું);
		  rarg = invert_truthvalue_loc (location, rarg);
		  rarg = convert (વૃક્ષ_TYPE (sarg), rarg);
		  val = build2 (MODIFY_પદાવલિ, વૃક્ષ_TYPE (larg), larg, rarg);
		}
		તોડો;
	      સ્થિતિ POSTDECREMENT_પદાવલિ:
		{
		  વૃક્ષ rarg = convert_lvalue_to_rvalue (location, sarg,
							સાચું, સાચું);
		  rarg = invert_truthvalue_loc (location, rarg);
		  વૃક્ષ iarg = convert (વૃક્ષ_TYPE (larg), rarg);
		  val = build2 (MODIFY_પદાવલિ, વૃક્ષ_TYPE (larg), larg, iarg);
		  val = build2 (COMPOUND_પદાવલિ, વૃક્ષ_TYPE (larg), val, sarg);
		  val = build2 (COMPOUND_પદાવલિ, વૃક્ષ_TYPE (larg), sarg, val);
		}
		તોડો;
	      મૂળભૂત:
		gcc_unreachable ();
	      }
	    વૃક્ષ_SIDE_EFFECTS (val) = 1;
	  }
	નહીંતર જો (C_BOOLEAN_TYPE_P (વૃક્ષ_TYPE (arg)))
	  val = boolean_increment (code, arg);
	નહીંતર
	  val = build2 (code, વૃક્ષ_TYPE (arg), arg, inc);
	વૃક્ષ_SIDE_EFFECTS (val) = 1;
	જો (TYPE_QUALS (વૃક્ષ_TYPE (val)) != TYPE_UNQUALIFIED)
	  વૃક્ષ_TYPE (val) = c_build_qualified_type (વૃક્ષ_TYPE (val),
						    TYPE_UNQUALIFIED);
	ret = val;
	જાઓ return_build_unary_op;
      }

    સ્થિતિ ADDR_પદાવલિ:
      /* Note that this operation never does default_conversion.  */

      /* The operand of unary '&' must be an lvalue (which excludes
	 expressions of type void), or, in C99, the result of a [] or
	 unary '*' operator.  */
      જો (VOID_TYPE_P (વૃક્ષ_TYPE (arg))
	  && TYPE_QUALS (વૃક્ષ_TYPE (arg)) == TYPE_UNQUALIFIED
	  && (!INDIRECT_REF_P (arg) || !flag_isoc99))
	pedwarn (location, 0, "taking address of expression of type %<void%>");

      /* Let &* cancel out to simplify resulting code.  */
      જો (INDIRECT_REF_P (arg))
	{
	  /* Don't let this be an lvalue.  */
	  જો (lvalue_p (વૃક્ષ_OPERAND (arg, 0)))
	    પાછા non_lvalue_loc (location, વૃક્ષ_OPERAND (arg, 0));
	  ret = વૃક્ષ_OPERAND (arg, 0);
	  જાઓ return_build_unary_op;
	}

      /* Anything not already handled and not a true memory reference
	 or a non-lvalue array is an error.  */
      જો (typecode != FUNCTION_TYPE && !noconvert
	  && !lvalue_or_else (location, arg, lv_addressof))
	પાછા error_mark_ગાંઠ;

      /* Move address operations inside C_MAYBE_CONST_EXPR to simplify
	 folding later.  */
      જો (વૃક્ષ_CODE (arg) == C_MAYBE_CONST_પદાવલિ)
	{
	  વૃક્ષ inner = build_unary_op (location, code,
				       C_MAYBE_CONST_પદાવલિ_પદાવલિ (arg),
				       noconvert);
	  ret = build2 (C_MAYBE_CONST_પદાવલિ, વૃક્ષ_TYPE (inner),
			C_MAYBE_CONST_પદાવલિ_PRE (arg), inner);
	  gcc_assert (!C_MAYBE_CONST_પદાવલિ_INT_OPERANDS (arg));
	  C_MAYBE_CONST_પદાવલિ_NON_CONST (ret)
	    = C_MAYBE_CONST_પદાવલિ_NON_CONST (arg);
	  જાઓ return_build_unary_op;
	}

      /* Ordinary case; arg is a COMPONENT_REF or a decl.  */

      argtype = વૃક્ષ_TYPE (arg);

      /* If the lvalue is const or volatile, merge that into the type
	 to which the address will point.  This is only needed
	 for function types.  */
      જો ((DECL_P (arg) || REFERENCE_CLASS_P (arg))
	  && (વૃક્ષ_READONLY (arg) || વૃક્ષ_THIS_VOLATILE (arg))
	  && વૃક્ષ_CODE (argtype) == FUNCTION_TYPE)
	{
	  પૂર્ણાંક orig_quals = TYPE_QUALS (strip_array_types (argtype));
	  પૂર્ણાંક quals = orig_quals;

	  જો (વૃક્ષ_READONLY (arg))
	    quals |= TYPE_QUAL_CONST;
	  જો (વૃક્ષ_THIS_VOLATILE (arg))
	    quals |= TYPE_QUAL_VOLATILE;

	  argtype = c_build_qualified_type (argtype, quals);
	}

      પસંદગી (વૃક્ષ_CODE (arg))
	{
	સ્થિતિ COMPONENT_REF:
	  જો (DECL_C_BIT_FIELD (વૃક્ષ_OPERAND (arg, 1)))
	    {
	      error_at (location, "cannot take address of bit-field %qD",
			વૃક્ષ_OPERAND (arg, 1));
	      પાછા error_mark_ગાંઠ;
	    }

	  /* fall through */

	સ્થિતિ ARRAY_REF:
	  જો (TYPE_REVERSE_STORAGE_ORDER (વૃક્ષ_TYPE (વૃક્ષ_OPERAND (arg, 0))))
	    {
	      જો (!AGGREGATE_TYPE_P (વૃક્ષ_TYPE (arg))
		  && !POINTER_TYPE_P (વૃક્ષ_TYPE (arg))
		  && !VECTOR_TYPE_P (વૃક્ષ_TYPE (arg)))
		{
		  error_at (location, "cannot take address of scalar with "
			    "reverse storage order");
		  પાછા error_mark_ગાંઠ;
		}

	      જો (વૃક્ષ_CODE (વૃક્ષ_TYPE (arg)) == ARRAY_TYPE
		  && TYPE_REVERSE_STORAGE_ORDER (વૃક્ષ_TYPE (arg)))
		warning_at (location, OPT_Wscalar_storage_order,
			    "address of array with reverse scalar storage "
			    "order requested");
	    }

	મૂળભૂત:
	  તોડો;
	}

      જો (!c_mark_addressable (arg))
	પાછા error_mark_ગાંઠ;

      gcc_assert (વૃક્ષ_CODE (arg) != COMPONENT_REF
		  || !DECL_C_BIT_FIELD (વૃક્ષ_OPERAND (arg, 1)));

      argtype = c_build_pointer_type (argtype);

      /* ??? Cope with user tricks that amount to offsetof.  Delete this
	 when we have proper support for integer constant expressions.  */
      val = get_base_address (arg);
      જો (val && INDIRECT_REF_P (val)
          && વૃક્ષ_CONSTANT (વૃક્ષ_OPERAND (val, 0)))
	{
	  ret = fold_offsetof (arg, argtype);
	  જાઓ return_build_unary_op;
	}

      val = build1 (ADDR_પદાવલિ, argtype, arg);

      ret = val;
      જાઓ return_build_unary_op;

    સ્થિતિ PAREN_પદાવલિ:
      ret = build1 (code, વૃક્ષ_TYPE (arg), arg);
      જાઓ return_build_unary_op;

    મૂળભૂત:
      gcc_unreachable ();
    }

  જો (argtype == NULL_વૃક્ષ)
    argtype = વૃક્ષ_TYPE (arg);
  જો (વૃક્ષ_CODE (arg) == INTEGER_CST)
    ret = (require_constant_કિંમત
	   ? fold_build1_initializer_loc (location, code, argtype, arg)
	   : fold_build1_loc (location, code, argtype, arg));
  નહીંતર
    ret = build1 (code, argtype, arg);
 return_build_unary_op:
  gcc_assert (ret != error_mark_ગાંઠ);
  જો (વૃક્ષ_CODE (ret) == INTEGER_CST && !વૃક્ષ_OVERFLOW (ret)
      && !(વૃક્ષ_CODE (xarg) == INTEGER_CST && !વૃક્ષ_OVERFLOW (xarg)))
    ret = build1 (NOP_પદાવલિ, વૃક્ષ_TYPE (ret), ret);
  નહીંતર જો (વૃક્ષ_CODE (ret) != INTEGER_CST && int_operands)
    ret = note_integer_operands (ret);
  જો (eptype)
    ret = build1 (EXCESS_PRECISION_પદાવલિ, eptype, ret);
  protected_set_પદાવલિ_location (ret, location);
  પાછા ret;
}

/* Return nonzero if REF is an lvalue valid for this language.
   Lvalues can be assigned, unless their type has TYPE_READONLY.
   Lvalues can have their address taken, unless they have C_DECL_REGISTER.  */

તાર્કિક
lvalue_p (const_વૃક્ષ ref)
{
  અચલ ગણના વૃક્ષ_code code = વૃક્ષ_CODE (ref);

  પસંદગી (code)
    {
    સ્થિતિ REALPART_પદાવલિ:
    સ્થિતિ IMAGPART_પદાવલિ:
    સ્થિતિ COMPONENT_REF:
      પાછા lvalue_p (વૃક્ષ_OPERAND (ref, 0));

    સ્થિતિ C_MAYBE_CONST_પદાવલિ:
      પાછા lvalue_p (વૃક્ષ_OPERAND (ref, 1));

    સ્થિતિ COMPOUND_LITERAL_પદાવલિ:
    સ્થિતિ STRING_CST:
      પાછા સાચું;

    સ્થિતિ MEM_REF:
    સ્થિતિ TARGET_MEM_REF:
      /* MEM_REFs can appear from -fgimple parsing or folding, so allow them
	 here as well.  */
    સ્થિતિ INDIRECT_REF:
    સ્થિતિ ARRAY_REF:
    સ્થિતિ VAR_DECL:
    સ્થિતિ PARM_DECL:
    સ્થિતિ RESULT_DECL:
    સ્થિતિ ERROR_MARK:
      પાછા (વૃક્ષ_CODE (વૃક્ષ_TYPE (ref)) != FUNCTION_TYPE
	      && વૃક્ષ_CODE (વૃક્ષ_TYPE (ref)) != METHOD_TYPE);

    સ્થિતિ BIND_પદાવલિ:
      પાછા વૃક્ષ_CODE (વૃક્ષ_TYPE (ref)) == ARRAY_TYPE;

    સ્થિતિ CALL_પદાવલિ:
      પાછા is_access_with_size_p (ref);

    મૂળભૂત:
      પાછા ખોટું;
    }
}

/* Give a warning for storing in something that is read-only in GCC
   terms but not const in ISO C terms.  */

સ્થિર શૂન્ય
readonly_warning (વૃક્ષ arg, ગણના lvalue_use use)
{
  પસંદગી (use)
    {
    સ્થિતિ lv_assign:
      warning (0, "assignment of read-only location %qE", arg);
      તોડો;
    સ્થિતિ lv_increment:
      warning (0, "increment of read-only location %qE", arg);
      તોડો;
    સ્થિતિ lv_decrement:
      warning (0, "decrement of read-only location %qE", arg);
      તોડો;
    મૂળભૂત:
      gcc_unreachable ();
    }
  પાછા;
}


/* Return nonzero if REF is an lvalue valid for this language;
   otherwise, print an error message and return zero.  USE says
   how the lvalue is being used and so selects the error message.
   LOCATION is the location at which any error should be reported.  */

સ્થિર પૂર્ણાંક
lvalue_or_else (location_t loc, const_વૃક્ષ ref, ગણના lvalue_use use)
{
  પૂર્ણાંક win = lvalue_p (ref);

  જો (!win)
    lvalue_error (loc, use);

  પાછા win;
}

/* Mark EXP saying that we need to be able to take the
   address of it; it should not be allocated in a register.
   Returns true if successful.  ARRAY_REF_P is true if this
   is for ARRAY_REF construction - in that case we don't want
   to look through VIEW_CONVERT_EXPR from VECTOR_TYPE to ARRAY_TYPE,
   it is fine to use ARRAY_REFs for vector subscripts on vector
   register variables.  If OVERRIDE_REGISTER, clear DECL_REGISTER rather
   than producing an error for taking the address of a register.  */

તાર્કિક
c_mark_addressable (વૃક્ષ exp, તાર્કિક array_ref_p, તાર્કિક override_register)
{
  વૃક્ષ x = exp;

  જ્યારે (1)
    પસંદગી (વૃક્ષ_CODE (x))
      {
      સ્થિતિ VIEW_CONVERT_પદાવલિ:
	જો (array_ref_p
	    && વૃક્ષ_CODE (વૃક્ષ_TYPE (x)) == ARRAY_TYPE
	    && VECTOR_TYPE_P (વૃક્ષ_TYPE (વૃક્ષ_OPERAND (x, 0))))
	  પાછા સાચું;
	x = વૃક્ષ_OPERAND (x, 0);
	તોડો;

      સ્થિતિ COMPONENT_REF:
	જો (DECL_C_BIT_FIELD (વૃક્ષ_OPERAND (x, 1)))
	  {
	    error ("cannot take address of bit-field %qD",
		   વૃક્ષ_OPERAND (x, 1));
	    પાછા ખોટું;
	  }
	/* FALLTHRU */
      સ્થિતિ ADDR_પદાવલિ:
      સ્થિતિ ARRAY_REF:
      સ્થિતિ REALPART_પદાવલિ:
      સ્થિતિ IMAGPART_પદાવલિ:
	x = વૃક્ષ_OPERAND (x, 0);
	તોડો;

      સ્થિતિ COMPOUND_LITERAL_પદાવલિ:
	જો (C_DECL_REGISTER (COMPOUND_LITERAL_પદાવલિ_DECL (x)))
	  {
	    જો (override_register)
	      DECL_REGISTER (COMPOUND_LITERAL_પદાવલિ_DECL (x)) = 0;
	    નહીંતર
	      {
		error ("address of register compound literal requested");
		પાછા ખોટું;
	      }
	  }
	વૃક્ષ_ADDRESSABLE (x) = 1;
	વૃક્ષ_ADDRESSABLE (COMPOUND_LITERAL_પદાવલિ_DECL (x)) = 1;
	પાછા સાચું;

      સ્થિતિ CONSTRUCTOR:
	વૃક્ષ_ADDRESSABLE (x) = 1;
	પાછા સાચું;

      સ્થિતિ VAR_DECL:
      સ્થિતિ CONST_DECL:
      સ્થિતિ PARM_DECL:
      સ્થિતિ RESULT_DECL:
	જો (C_DECL_REGISTER (x)
	    && DECL_NONLOCAL (x))
	  {
	    જો (વૃક્ષ_PUBLIC (x) || is_global_var (x))
	      {
		error
		  ("global register variable %qD used in nested function", x);
		પાછા ખોટું;
	      }
	    pedwarn (આગત_location, 0, "register variable %qD used in nested function", x);
	  }
	નહીંતર જો (C_DECL_REGISTER (x))
	  {
	    જો (વૃક્ષ_PUBLIC (x) || is_global_var (x))
	      error ("address of global register variable %qD requested", x);
	    નહીંતર જો (override_register && !DECL_HARD_REGISTER (x))
	      {
		DECL_REGISTER (x) = 0;
		વૃક્ષ_ADDRESSABLE (x) = 1;
		mark_decl_used (x, સાચું);
		પાછા સાચું;
	      }
	    નહીંતર
	      error ("address of register variable %qD requested", x);
	    પાછા ખોટું;
	  }

	/* FALLTHRU */
      સ્થિતિ FUNCTION_DECL:
	વૃક્ષ_ADDRESSABLE (x) = 1;
	mark_decl_used (x, સાચું);
	/* FALLTHRU */
      મૂળભૂત:
	પાછા સાચું;
    }
}

/* Convert EXPR to TYPE, warning about conversion problems with
   constants.  SEMANTIC_TYPE is the type this conversion would use
   without excess precision. If SEMANTIC_TYPE is NULL, this function
   is equivalent to convert_and_check. This function is a wrapper that
   handles conversions that may be different than
   the usual ones because of excess precision.  */

સ્થિર વૃક્ષ
ep_convert_and_check (location_t loc, વૃક્ષ type, વૃક્ષ પદાવલિ,
		      વૃક્ષ semantic_type)
{
  જો (વૃક્ષ_TYPE (પદાવલિ) == type)
    પાછા પદાવલિ;

  /* For C11, integer conversions may have results with excess
     precision.  */
  જો (flag_isoc11 || !semantic_type)
    પાછા convert_and_check (loc, type, પદાવલિ);

  જો (વૃક્ષ_CODE (વૃક્ષ_TYPE (પદાવલિ)) == INTEGER_TYPE
      && વૃક્ષ_TYPE (પદાવલિ) != semantic_type)
    {
      /* For integers, we need to check the real conversion, not
	 the conversion to the excess precision type.  */
      પદાવલિ = convert_and_check (loc, semantic_type, પદાવલિ);
    }
  /* Result type is the excess precision type, which should be
     large enough, so do not check.  */
  પાછા convert (type, પદાવલિ);
}

/* If EXPR refers to a built-in declared without a prototype returns
   the actual type of the built-in and, if non-null, set *BLTIN to
   a pointer to the built-in.  Otherwise return the type of EXPR
   and clear *BLTIN if non-null.  */

સ્થિર વૃક્ષ
type_or_builtin_type (વૃક્ષ પદાવલિ, વૃક્ષ *bltin = ખાલી)
{
  વૃક્ષ dummy;
  જો (!bltin)
    bltin = &dummy;

  *bltin = NULL_વૃક્ષ;

  વૃક્ષ type = વૃક્ષ_TYPE (પદાવલિ);
  જો (વૃક્ષ_CODE (પદાવલિ) != ADDR_પદાવલિ)
    પાછા type;

  વૃક્ષ oper = વૃક્ષ_OPERAND (પદાવલિ, 0);
  જો (!DECL_P (oper)
      || વૃક્ષ_CODE (oper) != FUNCTION_DECL
      || !fndecl_built_in_p (oper, BUILT_IN_NORMAL))
    પાછા type;

  built_in_function code = DECL_FUNCTION_CODE (oper);
  જો (!C_DECL_BUILTIN_PROTOTYPE (oper))
    પાછા type;

  જો ((*bltin = builtin_decl_implicit (code)))
    type = c_build_pointer_type (વૃક્ષ_TYPE (*bltin));

  પાછા type;
}

/* Build and return a conditional expression IFEXP ? OP1 : OP2.  If
   IFEXP_BCP then the condition is a call to __builtin_constant_p, and
   if folded to an integer constant then the unselected half may
   contain arbitrary operations not normally permitted in constant
   expressions.  Set the location of the expression to LOC.  */

વૃક્ષ
build_conditional_પદાવલિ (location_t colon_loc, વૃક્ષ ifexp, તાર્કિક ifexp_bcp,
			વૃક્ષ op1, વૃક્ષ op1_original_type, location_t op1_loc,
			વૃક્ષ op2, વૃક્ષ op2_original_type, location_t op2_loc)
{
  વૃક્ષ type1;
  વૃક્ષ type2;
  વૃક્ષ result_type = ખાલી;
  વૃક્ષ semantic_result_type = ખાલી;
  વૃક્ષ orig_op1 = op1, orig_op2 = op2;
  તાર્કિક int_const, op1_int_operands, op2_int_operands, int_operands;
  તાર્કિક ifexp_int_operands;
  વૃક્ષ ret;

  op1_int_operands = પદાવલિ_INT_CONST_OPERANDS (orig_op1);
  જો (op1_int_operands)
    op1 = remove_c_maybe_const_પદાવલિ (op1);
  op2_int_operands = પદાવલિ_INT_CONST_OPERANDS (orig_op2);
  જો (op2_int_operands)
    op2 = remove_c_maybe_const_પદાવલિ (op2);
  ifexp_int_operands = પદાવલિ_INT_CONST_OPERANDS (ifexp);
  જો (ifexp_int_operands)
    ifexp = remove_c_maybe_const_પદાવલિ (ifexp);

  /* Promote both alternatives.  */

  જો (વૃક્ષ_CODE (વૃક્ષ_TYPE (op1)) != VOID_TYPE)
    op1 = default_conversion (op1);
  જો (વૃક્ષ_CODE (વૃક્ષ_TYPE (op2)) != VOID_TYPE)
    op2 = default_conversion (op2);

  જો (વૃક્ષ_CODE (ifexp) == ERROR_MARK
      || વૃક્ષ_CODE (વૃક્ષ_TYPE (op1)) == ERROR_MARK
      || વૃક્ષ_CODE (વૃક્ષ_TYPE (op2)) == ERROR_MARK)
    પાછા error_mark_ગાંઠ;

  વૃક્ષ bltin1 = NULL_વૃક્ષ;
  વૃક્ષ bltin2 = NULL_વૃક્ષ;
  type1 = type_or_builtin_type (op1, &bltin1);
  અચલ ગણના વૃક્ષ_code code1 = વૃક્ષ_CODE (type1);
  type2 = type_or_builtin_type (op2, &bltin2);
  અચલ ગણના વૃક્ષ_code code2 = વૃક્ષ_CODE (type2);

  જો (code1 == POINTER_TYPE && reject_gcc_builtin (op1))
    પાછા error_mark_ગાંઠ;

  જો (code2 == POINTER_TYPE && reject_gcc_builtin (op2))
    પાછા error_mark_ગાંઠ;

  /* C90 does not permit non-lvalue arrays in conditional expressions.
     In C99 they will be pointers by now.  */
  જો (code1 == ARRAY_TYPE || code2 == ARRAY_TYPE)
    {
      error_at (colon_loc, "non-lvalue array in conditional expression");
      પાછા error_mark_ગાંઠ;
    }

  જો ((વૃક્ષ_CODE (op1) == EXCESS_PRECISION_પદાવલિ
       || વૃક્ષ_CODE (op2) == EXCESS_PRECISION_પદાવલિ)
      && (code1 == INTEGER_TYPE || code1 == REAL_TYPE
	  || code1 == COMPLEX_TYPE || code1 == BITINT_TYPE)
      && (code2 == INTEGER_TYPE || code2 == REAL_TYPE
	  || code2 == COMPLEX_TYPE || code2 == BITINT_TYPE))
    {
      semantic_result_type = c_common_type (type1, type2);
      જો (વૃક્ષ_CODE (op1) == EXCESS_PRECISION_પદાવલિ)
	{
	  op1 = વૃક્ષ_OPERAND (op1, 0);
	  type1 = વૃક્ષ_TYPE (op1);
	  gcc_assert (વૃક્ષ_CODE (type1) == code1);
	}
      જો (વૃક્ષ_CODE (op2) == EXCESS_PRECISION_પદાવલિ)
	{
	  op2 = વૃક્ષ_OPERAND (op2, 0);
	  type2 = વૃક્ષ_TYPE (op2);
	  gcc_assert (વૃક્ષ_CODE (type2) == code2);
	}
    }

  જો (warn_cxx_compat)
    {
      વૃક્ષ t1 = op1_original_type ? op1_original_type : વૃક્ષ_TYPE (orig_op1);
      વૃક્ષ t2 = op2_original_type ? op2_original_type : વૃક્ષ_TYPE (orig_op2);

      જો (વૃક્ષ_CODE (t1) == ENUMERAL_TYPE
	  && વૃક્ષ_CODE (t2) == ENUMERAL_TYPE
	  && TYPE_MAIN_VARIANT (t1) != TYPE_MAIN_VARIANT (t2))
	warning_at (colon_loc, OPT_Wc___compat,
		    "different enum types in conditional is "
		    "invalid in C++: %qT vs %qT", t1, t2);
    }

  જો (warn_zero_as_null_pointer_constant
      && c_inhibit_evaluation_warnings == 0)
    {
      જો ((code1 == POINTER_TYPE || code1 == NULLPTR_TYPE)
	  && INTEGRAL_TYPE_P (type2) && null_pointer_constant_p (orig_op2))
	warning_at (op2_loc, OPT_Wzero_as_null_pointer_constant,
		    "zero as null pointer constant");

      જો ((code2 == POINTER_TYPE || code2 == NULLPTR_TYPE)
	  && INTEGRAL_TYPE_P (type1) && null_pointer_constant_p (orig_op1))
	warning_at (op1_loc, OPT_Wzero_as_null_pointer_constant,
		    "zero as null pointer constant");
    }

  /* Quickly detect the usual case where op1 and op2 have the same type
     after promotion.  */
  જો (TYPE_MAIN_VARIANT (type1) == TYPE_MAIN_VARIANT (type2))
    {
      જો (type1 == type2)
	result_type = type1;
      નહીંતર
	result_type = TYPE_MAIN_VARIANT (type1);
    }
  નહીંતર જો ((code1 == INTEGER_TYPE || code1 == REAL_TYPE
	    || code1 == COMPLEX_TYPE || code1 == BITINT_TYPE)
	   && (code2 == INTEGER_TYPE || code2 == REAL_TYPE
	       || code2 == COMPLEX_TYPE || code2 == BITINT_TYPE))
    {
      /* In C11, a conditional expression between a floating-point
	 type and an integer type should convert the integer type to
	 the evaluation format of the floating-point type, with
	 possible excess precision.  */
      વૃક્ષ eptype1 = type1;
      વૃક્ષ eptype2 = type2;
      જો (flag_isoc11)
	{
	  વૃક્ષ eptype;
	  જો (ANY_INTEGRAL_TYPE_P (type1)
	      && (eptype = excess_precision_type (type2)) != NULL_વૃક્ષ)
	    {
	      eptype2 = eptype;
	      જો (!semantic_result_type)
		semantic_result_type = c_common_type (type1, type2);
	    }
	  નહીંતર જો (ANY_INTEGRAL_TYPE_P (type2)
		   && (eptype = excess_precision_type (type1)) != NULL_વૃક્ષ)
	    {
	      eptype1 = eptype;
	      જો (!semantic_result_type)
		semantic_result_type = c_common_type (type1, type2);
	    }
	}
      result_type = c_common_type (eptype1, eptype2);
      જો (result_type == error_mark_ગાંઠ)
	પાછા error_mark_ગાંઠ;
      do_warn_double_promotion (result_type, type1, type2,
				"implicit conversion from %qT to %qT to "
				"match other result of conditional",
				colon_loc);

      /* If -Wsign-compare, warn here if type1 and type2 have
	 different signedness.  We'll promote the signed to unsigned
	 and later code won't know it used to be different.
	 Do this check on the original types, so that explicit casts
	 will be considered, but default promotions won't.  */
      જો (c_inhibit_evaluation_warnings == 0)
	{
	  પૂર્ણાંક unsigned_op1 = TYPE_UNSIGNED (વૃક્ષ_TYPE (orig_op1));
	  પૂર્ણાંક unsigned_op2 = TYPE_UNSIGNED (વૃક્ષ_TYPE (orig_op2));

	  જો (unsigned_op1 ^ unsigned_op2)
	    {
	      /* Do not warn if the result type is signed, since the
		 signed type will only be chosen if it can represent
		 all the values of the unsigned type.  */
	      જો (!TYPE_UNSIGNED (result_type))
		/* OK */;
	      નહીંતર
		{
		  તાર્કિક op1_maybe_const = સાચું;
		  તાર્કિક op2_maybe_const = સાચું;

		  /* Do not warn if the signed quantity is an
		     unsuffixed integer literal (or some static
		     constant expression involving such literals) and
		     it is non-negative.  This warning requires the
		     operands to be folded for best results, so do
		     that folding in this case even without
		     warn_sign_compare to avoid warning options
		     possibly affecting code generation.  */
		  c_inhibit_evaluation_warnings
		    += (ifexp == truthvalue_false_ગાંઠ);
		  op1 = c_fully_fold (op1, require_constant_કિંમત,
				      &op1_maybe_const);
		  c_inhibit_evaluation_warnings
		    -= (ifexp == truthvalue_false_ગાંઠ);

		  c_inhibit_evaluation_warnings
		    += (ifexp == truthvalue_true_ગાંઠ);
		  op2 = c_fully_fold (op2, require_constant_કિંમત,
				      &op2_maybe_const);
		  c_inhibit_evaluation_warnings
		    -= (ifexp == truthvalue_true_ગાંઠ);

		  જો (warn_sign_compare)
		    {
		      જો ((unsigned_op2
			   && વૃક્ષ_પદાવલિ_nonnegative_p (op1))
			  || (unsigned_op1
			      && વૃક્ષ_પદાવલિ_nonnegative_p (op2)))
			/* OK */;
		      નહીંતર જો (unsigned_op2)
			warning_at (op1_loc, OPT_Wsign_compare,
				    "operand of %<?:%> changes signedness from "
				    "%qT to %qT due to unsignedness of other "
				    "operand", વૃક્ષ_TYPE (orig_op1),
				    વૃક્ષ_TYPE (orig_op2));
		      નહીંતર
			warning_at (op2_loc, OPT_Wsign_compare,
				    "operand of %<?:%> changes signedness from "
				    "%qT to %qT due to unsignedness of other "
				    "operand", વૃક્ષ_TYPE (orig_op2),
				    વૃક્ષ_TYPE (orig_op1));
		    }
		  જો (!op1_maybe_const || વૃક્ષ_CODE (op1) != INTEGER_CST)
		    op1 = c_wrap_maybe_const (op1, !op1_maybe_const);
		  જો (!op2_maybe_const || વૃક્ષ_CODE (op2) != INTEGER_CST)
		    op2 = c_wrap_maybe_const (op2, !op2_maybe_const);
		}
	    }
	}
    }
  નહીંતર જો (code1 == VOID_TYPE || code2 == VOID_TYPE)
    {
      જો (code1 != VOID_TYPE || code2 != VOID_TYPE)
	pedwarn (colon_loc, OPT_Wpedantic,
		 "ISO C forbids conditional expr with only one void side");
      result_type = void_type_ગાંઠ;
    }
  નહીંતર જો (code1 == POINTER_TYPE && code2 == POINTER_TYPE)
    {
      addr_space_t as1 = TYPE_ADDR_SPACE (વૃક્ષ_TYPE (type1));
      addr_space_t as2 = TYPE_ADDR_SPACE (વૃક્ષ_TYPE (type2));
      addr_space_t as_common;

      જો (comp_target_types (colon_loc, type1, type2))
	{
	  ifexp = save_પદાવલિ (ifexp);
	  result_type = common_pointer_type (type1, type2, ifexp);
	}
      નહીંતર જો (null_pointer_constant_p (orig_op1))
	result_type = type2;
      નહીંતર જો (null_pointer_constant_p (orig_op2))
	result_type = type1;
      નહીંતર જો (!addr_space_superset (as1, as2, &as_common))
	{
	  error_at (colon_loc, "pointers to disjoint address spaces "
		    "used in conditional expression");
	  પાછા error_mark_ગાંઠ;
	}
      નહીંતર જો ((VOID_TYPE_P (વૃક્ષ_TYPE (type1))
		&& !TYPE_ATOMIC (વૃક્ષ_TYPE (type1)))
	       || (VOID_TYPE_P (વૃક્ષ_TYPE (type2))
		   && !TYPE_ATOMIC (વૃક્ષ_TYPE (type2))))
	{
	  વૃક્ષ t1 = વૃક્ષ_TYPE (type1);
	  વૃક્ષ t2 = વૃક્ષ_TYPE (type2);
	  જો (!(VOID_TYPE_P (t1)
		&& !TYPE_ATOMIC (t1)))
	   {
	     /* roles are swapped */
	     t1 = t2;
	     t2 = વૃક્ષ_TYPE (type1);
	   }
	  વૃક્ષ t2_stripped = strip_array_types (t2);
	  જો ((વૃક્ષ_CODE (t2) == ARRAY_TYPE)
	      && (TYPE_QUALS (t2_stripped) & ~TYPE_QUALS (t1)))
	    {
	      જો (!flag_isoc23)
		warning_at (colon_loc, OPT_Wdiscarded_array_qualifiers,
			    "pointer to array loses qualifier "
			    "in conditional expression");
	      નહીંતર જો (warn_c11_c23_compat > 0)
		warning_at (colon_loc, OPT_Wc11_c23_compat,
			    "pointer to array loses qualifier "
			    "in conditional expression in ISO C before C23");
	    }
	  જો (વૃક્ષ_CODE (t2) == FUNCTION_TYPE)
	    pedwarn (colon_loc, OPT_Wpedantic,
		     "ISO C forbids conditional expr between "
		     "%<void *%> and function pointer");
	  /* for array, use qualifiers of element type */
	  જો (flag_isoc23)
	    t2 = t2_stripped;
	  result_type = c_build_pointer_type (qualify_type (t1, t2));
	}
      /* Objective-C pointer comparisons are a bit more lenient.  */
      નહીંતર જો (objc_have_common_type (type1, type2, -3, NULL_વૃક્ષ))
	result_type = objc_common_type (type1, type2);
      નહીંતર
	{
	  પૂર્ણાંક qual = ENCODE_QUAL_ADDR_SPACE (as_common);
	  ગણના diagnostics::kind kind = diagnostics::kind::permerror;
	  જો (!flag_isoc99)
	    /* This downgrade to a warning ensures that -std=gnu89
	       -pedantic-errors does not flag these mismatches between
	       builtins as errors (as diagnostics::kind::permerror would)
	       ISO C99 and later do not have implicit function declarations,
	       so the mismatch cannot occur naturally there.  */
	    kind = (bltin1 && bltin2
		    ? diagnostics::kind::warning
		    : diagnostics::kind::pedwarn);
	  જો (emit_diagnostic (kind, colon_loc, OPT_Wincompatible_pointer_types,
			       "pointer type mismatch "
			       "in conditional expression"))
	    {
	      inform (op1_loc, "first expression has type %qT", type1);
	      inform (op2_loc, "second expression has type %qT", type2);
	    }
	  result_type = c_build_pointer_type
			  (c_build_qualified_type (void_type_ગાંઠ, qual));
	}
    }
  નહીંતર જો (code1 == POINTER_TYPE
	   && (code2 == INTEGER_TYPE || code2 == BITINT_TYPE))
    {
      જો (!null_pointer_constant_p (orig_op2))
	permerror_opt (colon_loc, OPT_Wint_conversion,
		       "pointer/integer type mismatch "
		       "in conditional expression");
      નહીંતર
	{
	  op2 = null_pointer_ગાંઠ;
	}
      result_type = type1;
    }
  નહીંતર જો (code2 == POINTER_TYPE
	   && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
    {
      જો (!null_pointer_constant_p (orig_op1))
	permerror_opt (colon_loc, OPT_Wint_conversion,
		       "pointer/integer type mismatch "
		       "in conditional expression");
      નહીંતર
	{
	  op1 = null_pointer_ગાંઠ;
	}
      result_type = type2;
    }
  /* 6.5.15: "if one is a null pointer constant (other than a pointer) or has
     type nullptr_t and the other is a pointer, the result type is the pointer
     type."  */
  નહીંતર જો (code1 == NULLPTR_TYPE && code2 == POINTER_TYPE)
    result_type = type2;
  નહીંતર જો (code1 == POINTER_TYPE && code2 == NULLPTR_TYPE)
    result_type = type1;
  નહીંતર જો (RECORD_OR_UNION_TYPE_P (type1) && RECORD_OR_UNION_TYPE_P (type2)
	   && comptypes (TYPE_MAIN_VARIANT (type1),
			 TYPE_MAIN_VARIANT (type2)))
    result_type = composite_type (TYPE_MAIN_VARIANT (type1),
				  TYPE_MAIN_VARIANT (type2));

  જો (!result_type)
    {
      જો (flag_cond_mismatch)
	result_type = void_type_ગાંઠ;
      નહીંતર
	{
	  error_at (colon_loc, "type mismatch in conditional expression");
	  પાછા error_mark_ગાંઠ;
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

  જો (ifexp_bcp && ifexp == truthvalue_true_ગાંઠ)
    {
      op2_int_operands = સાચું;
      op1 = c_fully_fold (op1, require_constant_કિંમત, ખાલી);
    }
  જો (ifexp_bcp && ifexp == truthvalue_false_ગાંઠ)
    {
      op1_int_operands = સાચું;
      op2 = c_fully_fold (op2, require_constant_કિંમત, ખાલી);
    }
  int_const = int_operands = (ifexp_int_operands
			      && op1_int_operands
			      && op2_int_operands);
  જો (int_operands)
    {
      int_const = ((ifexp == truthvalue_true_ગાંઠ
		    && વૃક્ષ_CODE (orig_op1) == INTEGER_CST
		    && !વૃક્ષ_OVERFLOW (orig_op1))
		   || (ifexp == truthvalue_false_ગાંઠ
		       && વૃક્ષ_CODE (orig_op2) == INTEGER_CST
		       && !વૃક્ષ_OVERFLOW (orig_op2)));
    }

  /* Need to convert condition operand into a vector mask.  */
  જો (VECTOR_TYPE_P (વૃક્ષ_TYPE (ifexp)))
    {
      વૃક્ષ vectype = વૃક્ષ_TYPE (ifexp);
      વૃક્ષ elem_type = વૃક્ષ_TYPE (vectype);
      વૃક્ષ zero = build_int_cst (elem_type, 0);
      વૃક્ષ zero_vec = build_vector_from_val (vectype, zero);
      વૃક્ષ cmp_type = truth_type_for (vectype);
      ifexp = build2 (NE_પદાવલિ, cmp_type, ifexp, zero_vec);
    }

  જો (int_const || (ifexp_bcp && વૃક્ષ_CODE (ifexp) == INTEGER_CST))
    ret = fold_build3_loc (colon_loc, COND_પદાવલિ, result_type, ifexp, op1, op2);
  નહીંતર
    {
      જો (int_operands)
	{
	  /* Use c_fully_fold here, since C_MAYBE_CONST_EXPR might be
	     nested inside of the expression.  */
	  op1 = c_fully_fold (op1, ખોટું, ખાલી);
	  op2 = c_fully_fold (op2, ખોટું, ખાલી);
	}
      ret = build3 (COND_પદાવલિ, result_type, ifexp, op1, op2);
      જો (int_operands)
	ret = note_integer_operands (ret);
    }
  જો (semantic_result_type)
    ret = build1 (EXCESS_PRECISION_પદાવલિ, semantic_result_type, ret);

  protected_set_પદાવલિ_location (ret, colon_loc);

  /* If the OP1 and OP2 are the same and don't have side-effects,
     warn here, because the COND_EXPR will be turned into OP1.  */
  જો (warn_duplicated_branches
      && વૃક્ષ_CODE (ret) == COND_પદાવલિ
      && (op1 == op2 || operand_equal_p (op1, op2, OEP_ADDRESS_OF_SAME_FIELD)))
    warning_at (પદાવલિ_LOCATION (ret), OPT_Wduplicated_branches,
		"this condition has identical branches");

  પાછા ret;
}

/* EXPR is an expression, location LOC, whose result is discarded.
   Warn if it is a call to a nodiscard function (or a COMPOUND_EXPR
   whose right-hand operand is such a call, possibly recursively).  */

સ્થિર શૂન્ય
maybe_warn_nodiscard (location_t loc, વૃક્ષ પદાવલિ)
{
  જો (VOID_TYPE_P (વૃક્ષ_TYPE (પદાવલિ)))
    પાછા;
  જ્યારે (વૃક્ષ_CODE (પદાવલિ) == COMPOUND_પદાવલિ)
    {
      પદાવલિ = વૃક્ષ_OPERAND (પદાવલિ, 1);
      જો (પદાવલિ_HAS_LOCATION (પદાવલિ))
	loc = પદાવલિ_LOCATION (પદાવલિ);
    }
  જો (વૃક્ષ_CODE (પદાવલિ) != CALL_પદાવલિ)
    પાછા;
  વૃક્ષ fn = CALL_પદાવલિ_FN (પદાવલિ);
  જો (!fn)
    પાછા;
  વૃક્ષ attr;
  જો (વૃક્ષ_CODE (fn) == ADDR_પદાવલિ
      && વૃક્ષ_CODE (વૃક્ષ_OPERAND (fn, 0)) == FUNCTION_DECL
      && (attr = lookup_attribute ("nodiscard",
				   DECL_ATTRIBUTES (વૃક્ષ_OPERAND (fn, 0)))))
    {
      fn = વૃક્ષ_OPERAND (fn, 0);
      વૃક્ષ args = વૃક્ષ_કિંમત (attr);
      જો (args)
	args = વૃક્ષ_કિંમત (args);
      auto_diagnostic_group d;
      auto_urlify_attributes sentinel;
      પૂર્ણાંક warned;
      જો (args)
	warned = warning_at (loc, OPT_Wunused_result,
			     "ignoring return value of %qD, declared with "
			     "attribute %<nodiscard%>: %E", fn, args);
      નહીંતર
	warned = warning_at (loc, OPT_Wunused_result,
			     "ignoring return value of %qD, declared with "
			     "attribute %<nodiscard%>", fn);
      જો (warned)
	inform (DECL_SOURCE_LOCATION (fn), "declared here");
    }
  નહીંતર
    {
      વૃક્ષ rettype = વૃક્ષ_TYPE (વૃક્ષ_TYPE (વૃક્ષ_TYPE (fn)));
      attr = lookup_attribute ("nodiscard", TYPE_ATTRIBUTES (rettype));
      જો (!attr)
	પાછા;
      વૃક્ષ args = વૃક્ષ_કિંમત (attr);
      જો (args)
	args = વૃક્ષ_કિંમત (args);
      auto_diagnostic_group d;
      auto_urlify_attributes sentinel;
      પૂર્ણાંક warned;
      જો (args)
	warned = warning_at (loc, OPT_Wunused_result,
			     "ignoring return value of type %qT, declared "
			     "with attribute %<nodiscard%>: %E",
			     rettype, args);
      નહીંતર
	warned = warning_at (loc, OPT_Wunused_result,
			     "ignoring return value of type %qT, declared "
			     "with attribute %<nodiscard%>", rettype);
      જો (warned)
	{
	  જો (વૃક્ષ_CODE (fn) == ADDR_પદાવલિ)
	    {
	      fn = વૃક્ષ_OPERAND (fn, 0);
	      જો (વૃક્ષ_CODE (fn) == FUNCTION_DECL)
		inform (DECL_SOURCE_LOCATION (fn),
			"in call to %qD, declared here", fn);
	    }
	}
    }
}

/* Return a compound expression that performs two expressions and
   returns the value of the second of them.

   LOC is the location of the COMPOUND_EXPR.  */

વૃક્ષ
build_compound_પદાવલિ (location_t loc, વૃક્ષ expr1, વૃક્ષ expr2)
{
  તાર્કિક expr1_int_operands, expr2_int_operands;
  વૃક્ષ eptype = NULL_વૃક્ષ;
  વૃક્ષ ret;

  expr1_int_operands = પદાવલિ_INT_CONST_OPERANDS (expr1);
  જો (expr1_int_operands)
    expr1 = remove_c_maybe_const_પદાવલિ (expr1);
  expr2_int_operands = પદાવલિ_INT_CONST_OPERANDS (expr2);
  જો (expr2_int_operands)
    expr2 = remove_c_maybe_const_પદાવલિ (expr2);

  જો (વૃક્ષ_CODE (expr1) == EXCESS_PRECISION_પદાવલિ)
    expr1 = વૃક્ષ_OPERAND (expr1, 0);
  જો (વૃક્ષ_CODE (expr2) == EXCESS_PRECISION_પદાવલિ)
    {
      eptype = વૃક્ષ_TYPE (expr2);
      expr2 = વૃક્ષ_OPERAND (expr2, 0);
    }

  જો (!વૃક્ષ_SIDE_EFFECTS (expr1))
    {
      /* The left-hand operand of a comma expression is like an expression
	 statement: with -Wunused, we should warn if it doesn't have
	 any side-effects, unless it was explicitly cast to (void).  */
      જો (warn_unused_કિંમત)
	{
	  જો (VOID_TYPE_P (વૃક્ષ_TYPE (expr1))
	      && CONVERT_પદાવલિ_P (expr1))
	    ; /* (void) a, b */
	  નહીંતર જો (VOID_TYPE_P (વૃક્ષ_TYPE (expr1))
		   && વૃક્ષ_CODE (expr1) == COMPOUND_પદાવલિ
		   && CONVERT_પદાવલિ_P (વૃક્ષ_OPERAND (expr1, 1)))
	    ; /* (void) a, (void) b, c */
	  નહીંતર
	    warning_at (loc, OPT_Wunused_કિંમત,
			"left-hand operand of comma expression has no effect");
	}
    }
  નહીંતર જો (વૃક્ષ_CODE (expr1) == COMPOUND_પદાવલિ
	   && warn_unused_કિંમત)
    {
      વૃક્ષ r = expr1;
      location_t cloc = loc;
      જ્યારે (વૃક્ષ_CODE (r) == COMPOUND_પદાવલિ)
        {
	  જો (પદાવલિ_HAS_LOCATION (r))
	    cloc = પદાવલિ_LOCATION (r);
	  r = વૃક્ષ_OPERAND (r, 1);
	}
      જો (!વૃક્ષ_SIDE_EFFECTS (r)
	  && !VOID_TYPE_P (વૃક્ષ_TYPE (r))
	  && !CONVERT_પદાવલિ_P (r))
	warning_at (cloc, OPT_Wunused_કિંમત,
	            "right-hand operand of comma expression has no effect");
    }

  /* With -Wunused, we should also warn if the left-hand operand does have
     side-effects, but computes a value which is not used.  For example, in
     `foo() + bar(), baz()' the result of the `+' operator is not used,
     so we should issue a warning.  */
  નહીંતર જો (warn_unused_કિંમત)
    warn_if_unused_કિંમત (expr1, loc);

  maybe_warn_nodiscard (loc, expr1);

  જો (expr2 == error_mark_ગાંઠ)
    પાછા error_mark_ગાંઠ;

  ret = build2 (COMPOUND_પદાવલિ, વૃક્ષ_TYPE (expr2), expr1, expr2);

  જો (flag_isoc99
      && expr1_int_operands
      && expr2_int_operands)
    ret = note_integer_operands (ret);

  જો (eptype)
    ret = build1 (EXCESS_PRECISION_પદાવલિ, eptype, ret);

  protected_set_પદાવલિ_location (ret, loc);
  પાછા ret;
}

/* Issue -Wcast-qual warnings when appropriate.  TYPE is the type to
   which we are casting.  OTYPE is the type of the expression being
   cast.  Both TYPE and OTYPE are pointer types.  LOC is the location
   of the cast.  -Wcast-qual appeared on the command line.  Named
   address space qualifiers are not handled here, because they result
   in different warnings.  */

સ્થિર શૂન્ય
handle_warn_cast_qual (location_t loc, વૃક્ષ type, વૃક્ષ otype)
{
  વૃક્ષ in_type = type;
  વૃક્ષ in_otype = otype;
  પૂર્ણાંક added = 0;
  પૂર્ણાંક discarded = 0;
  તાર્કિક is_const;

  /* Check that the qualifiers on IN_TYPE are a superset of the
     qualifiers of IN_OTYPE.  The outermost level of POINTER_TYPE
     nodes is uninteresting and we stop as soon as we hit a
     non-POINTER_TYPE node on either type.  */
  કરો
    {
      in_otype = વૃક્ષ_TYPE (in_otype);
      in_type = વૃક્ષ_TYPE (in_type);

      /* GNU C allows cv-qualified function types.  'const' means the
	 function is very pure, 'volatile' means it can't return.  We
	 need to warn when such qualifiers are added, not when they're
	 taken away.  */
      જો (વૃક્ષ_CODE (in_otype) == FUNCTION_TYPE
	  && વૃક્ષ_CODE (in_type) == FUNCTION_TYPE)
	added |= (TYPE_QUALS_NO_ADDR_SPACE (in_type)
		  & ~TYPE_QUALS_NO_ADDR_SPACE (in_otype));
      નહીંતર
	discarded |= (TYPE_QUALS_NO_ADDR_SPACE (in_otype)
		      & ~TYPE_QUALS_NO_ADDR_SPACE (in_type));
    }
  જ્યારે (વૃક્ષ_CODE (in_type) == POINTER_TYPE
	 && વૃક્ષ_CODE (in_otype) == POINTER_TYPE);

  જો (added)
    warning_at (loc, OPT_Wcast_qual,
		"cast adds %q#v qualifier to function type", added);

  જો (discarded)
    /* There are qualifiers present in IN_OTYPE that are not present
       in IN_TYPE.  */
    warning_at (loc, OPT_Wcast_qual,
		"cast discards %qv qualifier from pointer target type",
		discarded);

  જો (added || discarded)
    પાછા;

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

  જો (TYPE_MAIN_VARIANT (in_type) != TYPE_MAIN_VARIANT (in_otype))
    પાછા;
  જો (વૃક્ષ_CODE (વૃક્ષ_TYPE (type)) != POINTER_TYPE)
    પાછા;

  in_type = type;
  in_otype = otype;
  is_const = TYPE_READONLY (વૃક્ષ_TYPE (in_type));
  કરો
    {
      in_type = વૃક્ષ_TYPE (in_type);
      in_otype = વૃક્ષ_TYPE (in_otype);
      જો ((TYPE_QUALS (in_type) &~ TYPE_QUALS (in_otype)) != 0
	  && !is_const)
	{
	  warning_at (loc, OPT_Wcast_qual,
		      "to be safe all intermediate pointers in cast from "
                      "%qT to %qT must be %<const%> qualified",
		      otype, type);
	  તોડો;
	}
      જો (is_const)
	is_const = TYPE_READONLY (in_type);
    }
  જ્યારે (વૃક્ષ_CODE (in_type) == POINTER_TYPE);
}

/* Heuristic check if two parameter types can be considered ABI-equivalent.  */

સ્થિર તાર્કિક
c_safe_arg_type_equiv_p (વૃક્ષ t1, વૃક્ષ t2)
{
  જો (error_operand_p (t1) || error_operand_p (t2))
    પાછા સાચું;

  t1 = TYPE_MAIN_VARIANT (t1);
  t2 = TYPE_MAIN_VARIANT (t2);

  જો (વૃક્ષ_CODE (t1) == POINTER_TYPE
      && વૃક્ષ_CODE (t2) == POINTER_TYPE)
    પાછા સાચું;

  /* Only the precision of the parameter matters.  This check should
     make sure that the callee does not see undefined values in argument
     registers.  */
  જો (INTEGRAL_TYPE_P (t1)
      && INTEGRAL_TYPE_P (t2)
      && TYPE_PRECISION (t1) == TYPE_PRECISION (t2))
    પાછા સાચું;

  પાછા comptypes (t1, t2);
}

/* Check if a type cast between two function types can be considered safe.  */

સ્થિર તાર્કિક
c_safe_function_type_cast_p (વૃક્ષ t1, વૃક્ષ t2)
{
  જો (વૃક્ષ_TYPE (t1) == void_type_ગાંઠ &&
      TYPE_ARG_TYPES (t1) == void_list_ગાંઠ)
    પાછા સાચું;

  જો (વૃક્ષ_TYPE (t2) == void_type_ગાંઠ &&
      TYPE_ARG_TYPES (t2) == void_list_ગાંઠ)
    પાછા સાચું;

  જો (!c_safe_arg_type_equiv_p (વૃક્ષ_TYPE (t1), વૃક્ષ_TYPE (t2)))
    પાછા ખોટું;

  માટે (t1 = TYPE_ARG_TYPES (t1), t2 = TYPE_ARG_TYPES (t2);
       t1 && t2;
       t1 = વૃક્ષ_CHAIN (t1), t2 = વૃક્ષ_CHAIN (t2))
    જો (!c_safe_arg_type_equiv_p (વૃક્ષ_કિંમત (t1), વૃક્ષ_કિંમત (t2)))
      પાછા ખોટું;

  પાછા સાચું;
}

/* Build an expression representing a cast to type TYPE of expression EXPR.
   LOC is the location of the cast-- typically the open paren of the cast.  */

વૃક્ષ
build_c_cast (location_t loc, વૃક્ષ type, વૃક્ષ પદાવલિ)
{
  વૃક્ષ કિંમત;

  તાર્કિક int_operands = પદાવલિ_INT_CONST_OPERANDS (પદાવલિ);

  જો (વૃક્ષ_CODE (પદાવલિ) == EXCESS_PRECISION_પદાવલિ)
    પદાવલિ = વૃક્ષ_OPERAND (પદાવલિ, 0);

  કિંમત = પદાવલિ;
  જો (int_operands)
    કિંમત = remove_c_maybe_const_પદાવલિ (કિંમત);

  જો (type == error_mark_ગાંઠ || પદાવલિ == error_mark_ગાંઠ)
    પાછા error_mark_ગાંઠ;

  /* The ObjC front-end uses TYPE_MAIN_VARIANT to tie together types differing
     only in <protocol> qualifications.  But when constructing cast expressions,
     the protocols do matter and must be kept around.  */
  જો (objc_is_object_ptr (type) && objc_is_object_ptr (વૃક્ષ_TYPE (પદાવલિ)))
    પાછા build1 (NOP_પદાવલિ, type, પદાવલિ);

  type = TYPE_MAIN_VARIANT (type);

  જો (વૃક્ષ_CODE (type) == ARRAY_TYPE)
    {
      error_at (loc, "cast specifies array type");
      પાછા error_mark_ગાંઠ;
    }

  જો (વૃક્ષ_CODE (type) == FUNCTION_TYPE)
    {
      error_at (loc, "cast specifies function type");
      પાછા error_mark_ગાંઠ;
    }

  જો (!VOID_TYPE_P (type))
    {
      કિંમત = require_complete_type (loc, કિંમત);
      જો (કિંમત == error_mark_ગાંઠ)
	પાછા error_mark_ગાંઠ;
    }

  જો (type == TYPE_MAIN_VARIANT (વૃક્ષ_TYPE (કિંમત)))
    {
      જો (RECORD_OR_UNION_TYPE_P (type)
	  && pedwarn (loc, OPT_Wpedantic,
		      "ISO C forbids casting nonscalar to the same type"))
	      ;
      નહીંતર જો (warn_useless_cast && c_inhibit_evaluation_warnings == 0)
	warning_at (loc, OPT_Wuseless_cast,
		    "useless cast to type %qT", type);

      /* Convert to remove any qualifiers from VALUE's type.  */
      કિંમત = convert (type, કિંમત);
    }
  નહીંતર જો (વૃક્ષ_CODE (type) == UNION_TYPE)
    {
      વૃક્ષ field;

      માટે (field = TYPE_FIELDS (type); field; field = DECL_CHAIN (field))
	જો (વૃક્ષ_TYPE (field) != error_mark_ગાંઠ
	    && comptypes (TYPE_MAIN_VARIANT (વૃક્ષ_TYPE (field)),
			  TYPE_MAIN_VARIANT (વૃક્ષ_TYPE (કિંમત))))
	  તોડો;

      જો (field)
	{
	  વૃક્ષ t;
	  તાર્કિક maybe_const = સાચું;

	  pedwarn (loc, OPT_Wpedantic, "ISO C forbids casts to union type");
	  t = c_fully_fold (કિંમત, ખોટું, &maybe_const);
	  t = build_constructor_single (type, field, t);
	  જો (!maybe_const)
	    t = c_wrap_maybe_const (t, સાચું);
	  t = digest_init (loc, field, type, t,
			   NULL_વૃક્ષ, ખોટું, ખોટું, ખોટું, સાચું, ખોટું, ખોટું);
	  વૃક્ષ_CONSTANT (t) = વૃક્ષ_CONSTANT (કિંમત);
	  પાછા t;
	}
      error_at (loc, "cast to union type from type not present in union");
      પાછા error_mark_ગાંઠ;
    }
  નહીંતર
    {
      વૃક્ષ otype, ovalue;

      જો (type == void_type_ગાંઠ)
	{
	  વૃક્ષ t = build1 (CONVERT_પદાવલિ, type, કિંમત);
	  SET_પદાવલિ_LOCATION (t, loc);
	  પાછા t;
	}

      otype = વૃક્ષ_TYPE (કિંમત);

      /* Optionally warn about potentially worrisome casts.  */
      જો (warn_cast_qual
	  && વૃક્ષ_CODE (type) == POINTER_TYPE
	  && વૃક્ષ_CODE (otype) == POINTER_TYPE)
	handle_warn_cast_qual (loc, type, otype);

      /* Warn about conversions between pointers to disjoint
	 address spaces.  */
      જો (વૃક્ષ_CODE (type) == POINTER_TYPE
	  && વૃક્ષ_CODE (otype) == POINTER_TYPE
	  && !null_pointer_constant_p (કિંમત))
	{
	  addr_space_t as_to = TYPE_ADDR_SPACE (વૃક્ષ_TYPE (type));
	  addr_space_t as_from = TYPE_ADDR_SPACE (વૃક્ષ_TYPE (otype));
	  addr_space_t as_common;

	  જો (!addr_space_superset (as_to, as_from, &as_common))
	    {
	      જો (ADDR_SPACE_GENERIC_P (as_from))
		warning_at (loc, 0, "cast to %qs address space pointer "
			    "from disjoint generic address space pointer",
			    c_addr_space_name (as_to));

	      નહીંતર જો (ADDR_SPACE_GENERIC_P (as_to))
		warning_at (loc, 0, "cast to generic address space pointer "
			    "from disjoint %qs address space pointer",
			    c_addr_space_name (as_from));

	      નહીંતર
		warning_at (loc, 0, "cast to %qs address space pointer "
			    "from disjoint %qs address space pointer",
			    c_addr_space_name (as_to),
			    c_addr_space_name (as_from));
	    }

	  /* Warn of new allocations that are not big enough for the target
	     type.  */
	  જો (warn_alloc_size && વૃક્ષ_CODE (કિંમત) == CALL_પદાવલિ)
	    જો (વૃક્ષ fndecl = get_callee_fndecl (કિંમત))
	      જો (DECL_IS_MALLOC (fndecl))
		{
		  વૃક્ષ attrs = TYPE_ATTRIBUTES (વૃક્ષ_TYPE (fndecl));
		  વૃક્ષ alloc_size = lookup_attribute ("alloc_size", attrs);
		  જો (alloc_size)
		    warn_for_alloc_size (loc, વૃક્ષ_TYPE (type), કિંમત,
					 alloc_size);
		}
	}

      /* Warn about possible alignment problems.  */
      જો ((STRICT_ALIGNMENT || warn_cast_align == 2)
	  && વૃક્ષ_CODE (type) == POINTER_TYPE
	  && વૃક્ષ_CODE (otype) == POINTER_TYPE
	  && વૃક્ષ_CODE (વૃક્ષ_TYPE (otype)) != VOID_TYPE
	  && વૃક્ષ_CODE (વૃક્ષ_TYPE (otype)) != FUNCTION_TYPE
	  /* Don't warn about opaque types, where the actual alignment
	     restriction is unknown.  */
	  && !(RECORD_OR_UNION_TYPE_P (વૃક્ષ_TYPE (otype))
	       && TYPE_MODE (વૃક્ષ_TYPE (otype)) == VOIDmode)
	  && min_align_of_type (વૃક્ષ_TYPE (type))
	     > min_align_of_type (વૃક્ષ_TYPE (otype)))
	warning_at (loc, OPT_Wcast_align,
		    "cast increases required alignment of target type");

      જો ((વૃક્ષ_CODE (type) == INTEGER_TYPE
	   || વૃક્ષ_CODE (type) == BITINT_TYPE)
	  && વૃક્ષ_CODE (otype) == POINTER_TYPE
	  && TYPE_PRECISION (type) != TYPE_PRECISION (otype))
      /* Unlike conversion of integers to pointers, where the
         warning is disabled for converting constants because
         of cases such as SIG_*, warn about converting constant
         pointers to integers. In some cases it may cause unwanted
         sign extension, and a warning is appropriate.  */
	warning_at (loc, OPT_Wpointer_to_int_cast,
		    "cast from pointer to integer of different size");

      જો ((વૃક્ષ_CODE (કિંમત) == CALL_પદાવલિ
	   && !is_access_with_size_p (કિંમત))
	  && વૃક્ષ_CODE (type) != વૃક્ષ_CODE (otype))
	warning_at (loc, OPT_Wbad_function_cast,
		    "cast from function call of type %qT "
		    "to non-matching type %qT", otype, type);

      જો (વૃક્ષ_CODE (type) == POINTER_TYPE
	  && (વૃક્ષ_CODE (otype) == INTEGER_TYPE
	      || વૃક્ષ_CODE (otype) == BITINT_TYPE)
	  && TYPE_PRECISION (type) != TYPE_PRECISION (otype)
	  /* Don't warn about converting any constant.  */
	  && !વૃક્ષ_CONSTANT (કિંમત))
	warning_at (loc,
		    OPT_Wint_to_pointer_cast, "cast to pointer from integer "
		    "of different size");

      જો (warn_strict_aliasing <= 2)
        strict_aliasing_warning (પદાવલિ_LOCATION (કિંમત), type, પદાવલિ);

      /* If pedantic, warn for conversions between function and object
	 pointer types, except for converting a null pointer constant
	 to function pointer type.  */
      જો (pedantic
	  && વૃક્ષ_CODE (type) == POINTER_TYPE
	  && વૃક્ષ_CODE (otype) == POINTER_TYPE
	  && વૃક્ષ_CODE (વૃક્ષ_TYPE (otype)) == FUNCTION_TYPE
	  && વૃક્ષ_CODE (વૃક્ષ_TYPE (type)) != FUNCTION_TYPE)
	pedwarn (loc, OPT_Wpedantic, "ISO C forbids "
		 "conversion of function pointer to object pointer type");

      જો (pedantic
	  && વૃક્ષ_CODE (type) == POINTER_TYPE
	  && વૃક્ષ_CODE (otype) == POINTER_TYPE
	  && વૃક્ષ_CODE (વૃક્ષ_TYPE (type)) == FUNCTION_TYPE
	  && વૃક્ષ_CODE (વૃક્ષ_TYPE (otype)) != FUNCTION_TYPE
	  && !null_pointer_constant_p (કિંમત))
	pedwarn (loc, OPT_Wpedantic, "ISO C forbids "
		 "conversion of object pointer to function pointer type");

      જો (વૃક્ષ_CODE (type) == POINTER_TYPE
	  && વૃક્ષ_CODE (otype) == POINTER_TYPE
	  && વૃક્ષ_CODE (વૃક્ષ_TYPE (type)) == FUNCTION_TYPE
	  && વૃક્ષ_CODE (વૃક્ષ_TYPE (otype)) == FUNCTION_TYPE
	  && !c_safe_function_type_cast_p (વૃક્ષ_TYPE (type),
					   વૃક્ષ_TYPE (otype)))
	warning_at (loc, OPT_Wcast_function_type,
		    "cast between incompatible function types"
		    " from %qT to %qT", otype, type);

      ovalue = કિંમત;
      /* If converting to boolean a value with integer operands that
	 is not itself represented as an INTEGER_CST, the call below
	 to note_integer_operands may insert a C_MAYBE_CONST_EXPR, but
	 build_binary_op as called by c_common_truthvalue_conversion
	 may also insert a C_MAYBE_CONST_EXPR to indicate that a
	 subexpression has been fully folded.  To avoid nested
	 C_MAYBE_CONST_EXPR, ensure that
	 c_objc_common_truthvalue_conversion receives an argument
	 properly marked as having integer operands in that case.  */
      જો (int_operands
	  && વૃક્ષ_CODE (કિંમત) != INTEGER_CST
	  && (વૃક્ષ_CODE (type) == BOOLEAN_TYPE
	      || (વૃક્ષ_CODE (type) == ENUMERAL_TYPE
		  && ENUM_UNDERLYING_TYPE (type) != NULL_વૃક્ષ
		  && વૃક્ષ_CODE (ENUM_UNDERLYING_TYPE (type)) == BOOLEAN_TYPE)))
	કિંમત = note_integer_operands (કિંમત);
      કિંમત = convert (type, કિંમત);

      /* Ignore any integer overflow caused by the cast.  */
      જો (વૃક્ષ_CODE (કિંમત) == INTEGER_CST && !FLOAT_TYPE_P (otype))
	{
	  જો (વૃક્ષ_OVERFLOW_P (ovalue))
	    {
	      જો (!વૃક્ષ_OVERFLOW (કિંમત))
		{
		  /* Avoid clobbering a shared constant.  */
		  કિંમત = copy_ગાંઠ (કિંમત);
		  વૃક્ષ_OVERFLOW (કિંમત) = વૃક્ષ_OVERFLOW (ovalue);
		}
	    }
	  નહીંતર જો (વૃક્ષ_OVERFLOW (કિંમત))
	    /* Reset VALUE's overflow flags, ensuring constant sharing.  */
	    કિંમત = wide_int_to_વૃક્ષ (વૃક્ષ_TYPE (કિંમત), wi::to_wide (કિંમત));
	}
    }

  /* Don't let a cast be an lvalue.  */
  જો (lvalue_p (કિંમત)
      /* Also, don't let a cast be a bit-field of a bit-precise integer type,
	 otherwise it could be incorrectly subject of integer promotions.  */
      || (વૃક્ષ_CODE (કિંમત) == COMPONENT_REF
	  && DECL_C_BIT_FIELD (વૃક્ષ_OPERAND (કિંમત, 1))
	  && BITINT_TYPE_P (DECL_BIT_FIELD_TYPE (વૃક્ષ_OPERAND (કિંમત, 1)))))
    કિંમત = non_lvalue_loc (loc, કિંમત);

  /* Don't allow the results of casting to floating-point or complex
     types be confused with actual constants, or casts involving
     integer and pointer types other than direct integer-to-integer
     and integer-to-pointer be confused with integer constant
     expressions and null pointer constants.  */
  જો (વૃક્ષ_CODE (કિંમત) == REAL_CST
      || વૃક્ષ_CODE (કિંમત) == COMPLEX_CST
      || (વૃક્ષ_CODE (કિંમત) == INTEGER_CST
	  && !((વૃક્ષ_CODE (પદાવલિ) == INTEGER_CST
		&& INTEGRAL_TYPE_P (વૃક્ષ_TYPE (પદાવલિ)))
	       || વૃક્ષ_CODE (પદાવલિ) == REAL_CST
	       || વૃક્ષ_CODE (પદાવલિ) == COMPLEX_CST)))
      કિંમત = build1 (NOP_પદાવલિ, type, કિંમત);

  /* If the expression has integer operands and so can occur in an
     unevaluated part of an integer constant expression, ensure the
     return value reflects this.  */
  જો (int_operands
      && INTEGRAL_TYPE_P (type)
      && કિંમત != error_mark_ગાંઠ
      && !પદાવલિ_INT_CONST_OPERANDS (કિંમત))
    કિંમત = note_integer_operands (કિંમત);

  protected_set_પદાવલિ_location (કિંમત, loc);
  પાછા કિંમત;
}

/* Interpret a cast of expression EXPR to type TYPE.  LOC is the
   location of the open paren of the cast, or the position of the cast
   expr.  */
વૃક્ષ
c_cast_પદાવલિ (location_t loc, સંરચના c_type_name *type_name, વૃક્ષ પદાવલિ)
{
  વૃક્ષ type;
  વૃક્ષ type_પદાવલિ = NULL_વૃક્ષ;
  તાર્કિક type_પદાવલિ_const = સાચું;
  વૃક્ષ ret;
  પૂર્ણાંક saved_wsp = warn_strict_prototypes;

  /* This avoids warnings about unprototyped casts on
     integers.  E.g. "#define SIG_DFL (void(*)())0".  */
  જો (વૃક્ષ_CODE (પદાવલિ) == INTEGER_CST)
    warn_strict_prototypes = 0;
  type = groktypename (type_name, &type_પદાવલિ, &type_પદાવલિ_const);
  warn_strict_prototypes = saved_wsp;

  જો (વૃક્ષ_CODE (પદાવલિ) == ADDR_પદાવલિ && !VOID_TYPE_P (type)
      && reject_gcc_builtin (પદાવલિ))
    પાછા error_mark_ગાંઠ;

  ret = build_c_cast (loc, type, પદાવલિ);
  જો (ret == error_mark_ગાંઠ)
    પાછા error_mark_ગાંઠ;

  જો (type_પદાવલિ)
    {
      તાર્કિક inner_પદાવલિ_const = સાચું;
      ret = c_fully_fold (ret, require_constant_કિંમત, &inner_પદાવલિ_const);
      ret = build2 (C_MAYBE_CONST_પદાવલિ, વૃક્ષ_TYPE (ret), type_પદાવલિ, ret);
      C_MAYBE_CONST_પદાવલિ_NON_CONST (ret) = !(type_પદાવલિ_const
					     && inner_પદાવલિ_const);
      SET_પદાવલિ_LOCATION (ret, loc);
    }

  જો (!પદાવલિ_HAS_LOCATION (ret))
    protected_set_પદાવલિ_location (ret, loc);

  /* C++ does not permits types to be defined in a cast, but it
     allows references to incomplete types.  */
  જો (warn_cxx_compat && type_name->specs->typespec_kind == ctsk_tagdef)
    warning_at (loc, OPT_Wc___compat,
		"defining a type in a cast is invalid in C++");

  પાછા ret;
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

વૃક્ષ
build_modify_પદાવલિ (location_t location, વૃક્ષ lhs, વૃક્ષ lhs_origtype,
		   ગણના વૃક્ષ_code modifycode,
		   location_t rhs_loc, વૃક્ષ rhs, વૃક્ષ rhs_origtype)
{
  વૃક્ષ result;
  વૃક્ષ newrhs;
  વૃક્ષ rhseval = NULL_વૃક્ષ;
  વૃક્ષ lhstype = વૃક્ષ_TYPE (lhs);
  વૃક્ષ olhstype = lhstype;
  તાર્કિક npc;
  તાર્કિક is_atomic_op;

  /* Types that aren't fully specified cannot be used in assignments.  */
  lhs = require_complete_type (location, lhs);
  rhs = require_complete_type (location, rhs);

  /* Avoid duplicate error messages from operands that had errors.  */
  જો (વૃક્ષ_CODE (lhs) == ERROR_MARK || વૃક્ષ_CODE (rhs) == ERROR_MARK)
    પાછા error_mark_ગાંઠ;

  /* Ensure an error for assigning a non-lvalue array to an array in
     C90.  */
  જો (વૃક્ષ_CODE (lhstype) == ARRAY_TYPE)
    {
      error_at (location, "assignment to expression with array type");
      પાછા error_mark_ગાંઠ;
    }

  /* For ObjC properties, defer this check.  */
  જો (!objc_is_property_ref (lhs) && !lvalue_or_else (location, lhs, lv_assign))
    પાછા error_mark_ગાંઠ;

  is_atomic_op = really_atomic_lvalue (lhs);

  newrhs = rhs;

  જો (વૃક્ષ_CODE (lhs) == C_MAYBE_CONST_પદાવલિ)
    {
      વૃક્ષ inner = build_modify_પદાવલિ (location, C_MAYBE_CONST_પદાવલિ_પદાવલિ (lhs),
				      lhs_origtype, modifycode, rhs_loc, rhs,
				      rhs_origtype);
      જો (inner == error_mark_ગાંઠ)
	પાછા error_mark_ગાંઠ;
      result = build2 (C_MAYBE_CONST_પદાવલિ, વૃક્ષ_TYPE (inner),
		       C_MAYBE_CONST_પદાવલિ_PRE (lhs), inner);
      gcc_assert (!C_MAYBE_CONST_પદાવલિ_INT_OPERANDS (lhs));
      C_MAYBE_CONST_પદાવલિ_NON_CONST (result) = 1;
      protected_set_પદાવલિ_location (result, location);
      પાછા result;
    }

  /* If a binary op has been requested, combine the old LHS value with the RHS
     producing the value we should actually store into the LHS.  */

  જો (modifycode != NOP_પદાવલિ)
    {
      lhs = c_fully_fold (lhs, ખોટું, ખાલી, સાચું);
      lhs = stabilize_reference (lhs);

      /* Construct the RHS for any non-atomic compound assignment. */
      જો (!is_atomic_op)
        {
	  /* If in LHS op= RHS the RHS has side-effects, ensure they
	     are preevaluated before the rest of the assignment expression's
	     side-effects, because RHS could contain e.g. function calls
	     that modify LHS.  */
	  જો (વૃક્ષ_SIDE_EFFECTS (rhs))
	    {
	      જો (વૃક્ષ_CODE (rhs) == EXCESS_PRECISION_પદાવલિ)
		newrhs = save_પદાવલિ (વૃક્ષ_OPERAND (rhs, 0));
	      નહીંતર
		newrhs = save_પદાવલિ (rhs);
	      rhseval = newrhs;
	      જો (વૃક્ષ_CODE (rhs) == EXCESS_PRECISION_પદાવલિ)
		newrhs = build1 (EXCESS_PRECISION_પદાવલિ, વૃક્ષ_TYPE (rhs),
				 newrhs);
	    }
	  તાર્કિક clear_decl_read = ખોટું;
	  જો ((VAR_P (lhs) || વૃક્ષ_CODE (lhs) == PARM_DECL)
	      && !DECL_READ_P (lhs)
	      && (VAR_P (lhs) ? warn_unused_but_set_variable
			      : warn_unused_but_set_parameter) > 2)
	    {
	      mark_exp_read (newrhs);
	      જો (!DECL_READ_P (lhs))
		clear_decl_read = સાચું;
	    }

	  newrhs = build_દ્વિઅંકી_op (location, modifycode,
				    convert_lvalue_to_rvalue (location, lhs,
							      સાચું, સાચું),
				    newrhs, સાચું);
	  જો (clear_decl_read)
	    DECL_READ_P (lhs) = 0;

	  /* The original type of the right hand side is no longer
	     meaningful.  */
	  rhs_origtype = NULL_વૃક્ષ;
	}
    }

  જો (c_dialect_objc ())
    {
      /* Check if we are modifying an Objective-C property reference;
	 if so, we need to generate setter calls.  */
      જો (વૃક્ષ_CODE (newrhs) == EXCESS_PRECISION_પદાવલિ)
	result = objc_maybe_build_modify_પદાવલિ (lhs, વૃક્ષ_OPERAND (newrhs, 0));
      નહીંતર
	result = objc_maybe_build_modify_પદાવલિ (lhs, newrhs);
      જો (result)
	જાઓ return_result;

      /* Else, do the check that we postponed for Objective-C.  */
      જો (!lvalue_or_else (location, lhs, lv_assign))
	પાછા error_mark_ગાંઠ;
    }

  /* Give an error for storing in something that is 'const'.  */

  જો (TYPE_READONLY (lhstype)
      || (RECORD_OR_UNION_TYPE_P (lhstype)
	  && C_TYPE_FIELDS_READONLY (lhstype)))
    {
      readonly_error (location, lhs, lv_assign);
      પાછા error_mark_ગાંઠ;
    }
  નહીંતર જો (વૃક્ષ_READONLY (lhs))
    readonly_warning (lhs, lv_assign);

  /* If storing into a structure or union member,
     it has probably been given type `int'.
     Compute the type that would go with
     the actual amount of storage the member occupies.  */

  જો (વૃક્ષ_CODE (lhs) == COMPONENT_REF
      && (વૃક્ષ_CODE (lhstype) == INTEGER_TYPE
	  || વૃક્ષ_CODE (lhstype) == BOOLEAN_TYPE
	  || SCALAR_FLOAT_TYPE_P (lhstype)
	  || વૃક્ષ_CODE (lhstype) == ENUMERAL_TYPE))
    lhstype = વૃક્ષ_TYPE (get_unwidened (lhs, 0));

  /* If storing in a field that is in actuality a short or narrower than one,
     we must store in the field in its actual type.  */

  જો (lhstype != વૃક્ષ_TYPE (lhs))
    {
      lhs = copy_ગાંઠ (lhs);
      વૃક્ષ_TYPE (lhs) = lhstype;
    }

  /* Issue -Wc++-compat warnings about an assignment to an enum type
     when LHS does not have its original type.  This happens for,
     e.g., an enum bitfield in a struct.  */
  જો (warn_cxx_compat
      && lhs_origtype != NULL_વૃક્ષ
      && lhs_origtype != lhstype
      && વૃક્ષ_CODE (lhs_origtype) == ENUMERAL_TYPE)
    {
      વૃક્ષ checktype = (rhs_origtype != NULL_વૃક્ષ
			? rhs_origtype
			: વૃક્ષ_TYPE (rhs));
      જો (checktype != error_mark_ગાંઠ
	  && (TYPE_MAIN_VARIANT (checktype) != TYPE_MAIN_VARIANT (lhs_origtype)
	      || (is_atomic_op && modifycode != NOP_પદાવલિ)))
	warning_at (location, OPT_Wc___compat,
		    "enum conversion in assignment is invalid in C++");
    }

  /* Remove qualifiers.  */
  lhstype = c_build_qualified_type (lhstype, TYPE_UNQUALIFIED);
  olhstype = c_build_qualified_type (olhstype, TYPE_UNQUALIFIED);

  /* Convert new value to destination type.  Fold it first, then
     restore any excess precision information, for the sake of
     conversion warnings.  */

  જો (!(is_atomic_op && modifycode != NOP_પદાવલિ))
    {
      વૃક્ષ rhs_semantic_type = NULL_વૃક્ષ;
      જો (!c_in_omp_for)
	{
	  જો (વૃક્ષ_CODE (newrhs) == EXCESS_PRECISION_પદાવલિ)
	    {
	      rhs_semantic_type = વૃક્ષ_TYPE (newrhs);
	      newrhs = વૃક્ષ_OPERAND (newrhs, 0);
	    }
	  npc = null_pointer_constant_p (newrhs);
	  newrhs = c_fully_fold (newrhs, ખોટું, ખાલી);
	  જો (rhs_semantic_type)
	    newrhs = build1 (EXCESS_PRECISION_પદાવલિ, rhs_semantic_type, newrhs);
	}
      નહીંતર
	npc = null_pointer_constant_p (newrhs);
      newrhs = convert_for_assignment (location, rhs_loc, lhstype, newrhs,
				       rhs_origtype, ic_assign, npc,
				       NULL_વૃક્ષ, NULL_વૃક્ષ, 0);
      જો (વૃક્ષ_CODE (newrhs) == ERROR_MARK)
	પાછા error_mark_ગાંઠ;
    }

  /* Emit ObjC write barrier, if necessary.  */
  જો (c_dialect_objc () && flag_objc_gc)
    {
      result = objc_generate_write_barrier (lhs, modifycode, newrhs);
      જો (result)
	{
	  protected_set_પદાવલિ_location (result, location);
	  જાઓ return_result;
	}
    }

  /* Scan operands.  */

  જો (is_atomic_op)
    result = build_atomic_assign (location, lhs, modifycode, newrhs, ખોટું);
  નહીંતર
    {
      result = build2 (MODIFY_પદાવલિ, lhstype, lhs, newrhs);
      વૃક્ષ_SIDE_EFFECTS (result) = 1;
      protected_set_પદાવલિ_location (result, location);
    }

  /* If we got the LHS in a different type for storing in,
     convert the result back to the nominal type of LHS
     so that the value we return always has the same type
     as the LHS argument.  */

  જો (olhstype == વૃક્ષ_TYPE (result))
    જાઓ return_result;

  result = convert_for_assignment (location, rhs_loc, olhstype, result,
				   rhs_origtype, ic_assign, ખોટું, NULL_વૃક્ષ,
				   NULL_વૃક્ષ, 0);
  protected_set_પદાવલિ_location (result, location);

return_result:
  જો (rhseval)
    result = build2 (COMPOUND_પદાવલિ, વૃક્ષ_TYPE (result), rhseval, result);
  પાછા result;
}

/* Return whether STRUCT_TYPE has an anonymous field with type TYPE.
   This is used to implement -fplan9-extensions.  */

સ્થિર તાર્કિક
find_anonymous_field_with_type (વૃક્ષ struct_type, વૃક્ષ type)
{
  વૃક્ષ field;
  તાર્કિક found;

  gcc_assert (RECORD_OR_UNION_TYPE_P (struct_type));
  found = ખોટું;
  માટે (field = TYPE_FIELDS (struct_type);
       field != NULL_વૃક્ષ;
       field = વૃક્ષ_CHAIN (field))
    {
      વૃક્ષ fieldtype = remove_qualifiers (વૃક્ષ_TYPE (field));
      જો (DECL_NAME (field) == ખાલી
	  && comptypes (type, fieldtype))
	{
	  જો (found)
	    પાછા ખોટું;
	  found = સાચું;
	}
      નહીંતર જો (DECL_NAME (field) == ખાલી
	       && RECORD_OR_UNION_TYPE_P (વૃક્ષ_TYPE (field))
	       && find_anonymous_field_with_type (વૃક્ષ_TYPE (field), type))
	{
	  જો (found)
	    પાછા ખોટું;
	  found = સાચું;
	}
    }
  પાછા found;
}

/* RHS is an expression whose type is pointer to struct.  If there is
   an anonymous field in RHS with type TYPE, then return a pointer to
   that field in RHS.  This is used with -fplan9-extensions.  This
   returns NULL if no conversion could be found.  */

સ્થિર વૃક્ષ
convert_to_anonymous_field (location_t location, વૃક્ષ type, વૃક્ષ rhs)
{
  વૃક્ષ rhs_struct_type, lhs_main_type;
  વૃક્ષ field, found_field;
  તાર્કિક found_sub_field;
  વૃક્ષ ret;

  gcc_assert (POINTER_TYPE_P (વૃક્ષ_TYPE (rhs)));
  rhs_struct_type = વૃક્ષ_TYPE (વૃક્ષ_TYPE (rhs));
  gcc_assert (RECORD_OR_UNION_TYPE_P (rhs_struct_type));

  gcc_assert (POINTER_TYPE_P (type));
  lhs_main_type = remove_qualifiers (વૃક્ષ_TYPE (type));

  found_field = NULL_વૃક્ષ;
  found_sub_field = ખોટું;
  માટે (field = TYPE_FIELDS (rhs_struct_type);
       field != NULL_વૃક્ષ;
       field = વૃક્ષ_CHAIN (field))
    {
      જો (DECL_NAME (field) != NULL_વૃક્ષ
	  || !RECORD_OR_UNION_TYPE_P (વૃક્ષ_TYPE (field)))
	ચાલુ;
      વૃક્ષ fieldtype = remove_qualifiers (વૃક્ષ_TYPE (field));
      જો (comptypes (lhs_main_type, fieldtype))
	{
	  જો (found_field != NULL_વૃક્ષ)
	    પાછા NULL_વૃક્ષ;
	  found_field = field;
	}
      નહીંતર જો (find_anonymous_field_with_type (વૃક્ષ_TYPE (field),
					       lhs_main_type))
	{
	  જો (found_field != NULL_વૃક્ષ)
	    પાછા NULL_વૃક્ષ;
	  found_field = field;
	  found_sub_field = સાચું;
	}
    }

  જો (found_field == NULL_વૃક્ષ)
    પાછા NULL_વૃક્ષ;

  ret = fold_build3_loc (location, COMPONENT_REF, વૃક્ષ_TYPE (found_field),
			 build_fold_indirect_ref (rhs), found_field,
			 NULL_વૃક્ષ);
  ret = build_fold_addr_પદાવલિ_loc (location, ret);

  જો (found_sub_field)
    {
      ret = convert_to_anonymous_field (location, type, ret);
      gcc_assert (ret != NULL_વૃક્ષ);
    }

  પાછા ret;
}

/* Issue an error message for a bad initializer component.
   GMSGID identifies the message.
   The component name is taken from the spelling stack.  */

સ્થિર શૂન્ય ATTRIBUTE_GCC_DIAG (2,0)
error_init (location_t loc, અચલ અક્ષર *gmsgid, ...)
{
  અક્ષર *ofwhat;

  auto_diagnostic_group d;

  /* The gmsgid may be a format string with %< and %>. */
  va_list ap;
  va_start (ap, gmsgid);
  તાર્કિક warned = emit_diagnostic_valist (diagnostics::kind::error,
					loc, -1, gmsgid, &ap);
  va_end (ap);

  ofwhat = print_spelling ((અક્ષર *) alloca (spelling_length () + 1));
  જો (*ofwhat && warned)
    inform (loc, "(near initialization for %qs)", ofwhat);
}

/* Used to implement pedwarn_init and permerror_init.  */

સ્થિર તાર્કિક ATTRIBUTE_GCC_DIAG (3,0)
pedwarn_permerror_init (location_t loc, પૂર્ણાંક opt, અચલ અક્ષર *gmsgid,
			va_list *ap, ગણના diagnostics::kind kind)
{
  /* Use the location where a macro was expanded rather than where
     it was defined to make sure macros defined in system headers
     but used incorrectly elsewhere are diagnosed.  */
  location_t exploc = expansion_point_location_if_in_system_header (loc);
  auto_diagnostic_group d;
  તાર્કિક warned = emit_diagnostic_valist (kind, exploc, opt, gmsgid, ap);
  જો (warned)
    {
      અક્ષર *ofwhat = print_spelling ((અક્ષર *) alloca (spelling_length () + 1));
      જો (*ofwhat)
	inform (exploc, "(near initialization for %qs)", ofwhat);
    }
  પાછા warned;
}

/* Issue a pedantic warning for a bad initializer component.  OPT is
   the option OPT_* (from options.h) controlling this warning or 0 if
   it is unconditionally given.  GMSGID identifies the message.  The
   component name is taken from the spelling stack.  */

સ્થિર તાર્કિક ATTRIBUTE_GCC_DIAG (3,0)
pedwarn_init (location_t loc, પૂર્ણાંક opt, અચલ અક્ષર *gmsgid, ...)
{
  va_list ap;
  va_start (ap, gmsgid);
  તાર્કિક warned = pedwarn_permerror_init (loc, opt, gmsgid, &ap,
					diagnostics::kind::pedwarn);
  va_end (ap);
  પાછા warned;
}

/* Like pedwarn_init, but issue a permerror.  */

સ્થિર તાર્કિક ATTRIBUTE_GCC_DIAG (3,0)
permerror_init (location_t loc, પૂર્ણાંક opt, અચલ અક્ષર *gmsgid, ...)
{
  va_list ap;
  va_start (ap, gmsgid);
  તાર્કિક warned = pedwarn_permerror_init (loc, opt, gmsgid, &ap,
					diagnostics::kind::permerror);
  va_end (ap);
  પાછા warned;
}

/* Issue a warning for a bad initializer component.

   OPT is the OPT_W* value corresponding to the warning option that
   controls this warning.  GMSGID identifies the message.  The
   component name is taken from the spelling stack.  */

સ્થિર શૂન્ય
warning_init (location_t loc, પૂર્ણાંક opt, અચલ અક્ષર *gmsgid)
{
  અક્ષર *ofwhat;
  તાર્કિક warned;

  auto_diagnostic_group d;

  /* Use the location where a macro was expanded rather than where
     it was defined to make sure macros defined in system headers
     but used incorrectly elsewhere are diagnosed.  */
  location_t exploc = expansion_point_location_if_in_system_header (loc);

  /* The gmsgid may be a format string with %< and %>. */
  warned = warning_at (exploc, opt, gmsgid);
  જો (warned)
    {
      ofwhat = print_spelling ((અક્ષર *) alloca (spelling_length () + 1));
      જો (*ofwhat)
	inform (exploc, "(near initialization for %qs)", ofwhat);
    }
}

/* If TYPE is an array type and EXPR is a parenthesized string
   constant, warn if pedantic that EXPR is being used to initialize an
   object of type TYPE.  */

શૂન્ય
maybe_warn_string_init (location_t loc, વૃક્ષ type, સંરચના c_પદાવલિ પદાવલિ)
{
  જો (pedantic
      && વૃક્ષ_CODE (type) == ARRAY_TYPE
      && વૃક્ષ_CODE (પદાવલિ.કિંમત) == STRING_CST
      && પદાવલિ.original_code != STRING_CST)
    pedwarn_init (loc, OPT_Wpedantic,
		  "array initialized from parenthesized string constant");
}

/* Attempt to locate the parameter with the given index within FNDECL,
   returning DECL_SOURCE_LOCATION (FNDECL) if it can't be found.  */

સ્થિર location_t
get_fndecl_argument_location (વૃક્ષ fndecl, પૂર્ણાંક argnum)
{
  પૂર્ણાંક i;
  વૃક્ષ param;

  /* Locate param by index within DECL_ARGUMENTS (fndecl).  */
  માટે (i = 0, param = DECL_ARGUMENTS (fndecl);
       i < argnum && param;
       i++, param = વૃક્ષ_CHAIN (param))
    ;

  /* If something went wrong (e.g. if we have a builtin and thus no arguments),
     return DECL_SOURCE_LOCATION (FNDECL).  */
  જો (param == ખાલી)
    પાછા DECL_SOURCE_LOCATION (fndecl);

  પાછા DECL_SOURCE_LOCATION (param);
}

/* Issue a note about a mismatching argument for parameter PARMNUM
   to FUNDECL, for types EXPECTED_TYPE and ACTUAL_TYPE.
   Attempt to issue the note at the pertinent parameter of the decl;
   failing that issue it at the location of FUNDECL; failing that
   issue it at PLOC.
   Use highlight_colors::actual for the ACTUAL_TYPE
   and highlight_colors::expected for EXPECTED_TYPE and the
   parameter of FUNDECL*/

સ્થિર શૂન્ય
inform_for_arg (વૃક્ષ fundecl, location_t ploc, પૂર્ણાંક parmnum,
		વૃક્ષ expected_type, વૃક્ષ actual_type)
{
  location_t loc;
  જો (fundecl && !DECL_IS_UNDECLARED_BUILTIN (fundecl))
    loc = get_fndecl_argument_location (fundecl, parmnum - 1);
  નહીંતર
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

સ્થિર શૂન્ય
maybe_warn_builtin_no_proto_arg (location_t loc, વૃક્ષ fundecl, પૂર્ણાંક parmnum,
				 વૃક્ષ parmtype, વૃક્ષ argtype)
{
  વૃક્ષ_code parmcode = વૃક્ષ_CODE (parmtype);
  વૃક્ષ_code argcode = વૃક્ષ_CODE (argtype);
  વૃક્ષ promoted = c_type_promotes_to (argtype);

  /* Avoid warning for enum arguments that promote to an integer type
     of the same size/mode.  */
  જો (parmcode == INTEGER_TYPE
      && argcode == ENUMERAL_TYPE
      && TYPE_MODE (parmtype) == TYPE_MODE (argtype))
    પાછા;

  જો ((parmcode == argcode
       || (parmcode == INTEGER_TYPE
	   && argcode == ENUMERAL_TYPE))
      && TYPE_MAIN_VARIANT (parmtype) == TYPE_MAIN_VARIANT (promoted))
    પાછા;

  /* This diagnoses even signed/unsigned mismatches.  Those might be
     safe in many cases but GCC may emit suboptimal code for them so
     warning on those cases drives efficiency improvements.  */
  જો (warning_at (loc, OPT_Wbuiltin_declaration_mismatch,
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

વર્ગ pp_element_quoted_decl : જાહેર pp_element
{
જાહેર:
  pp_element_quoted_decl (વૃક્ષ decl, અચલ અક્ષર *highlight_color)
  : m_decl (decl),
    m_highlight_color (highlight_color)
  {
  }

  શૂન્ય add_to_phase_2 (pp_markup::context &ctxt) override
  {
    ctxt.begin_quote ();
    ctxt.begin_highlight_color (m_highlight_color);

    print_decl (ctxt);

    ctxt.end_highlight_color ();
    ctxt.end_quote ();
  }

  શૂન્ય print_decl (pp_markup::context &ctxt)
  {
    pretty_printer *અચલ pp = &ctxt.m_pp;
    pp->set_padding (pp_none);
    જો (DECL_NAME (m_decl))
      pp_identifier (pp, lang_hooks.decl_printable_name (m_decl, 2));
    નહીંતર
      pp_string (pp, _("({anonymous})"));
  }

ખાનગી:
  વૃક્ષ m_decl;
  અચલ અક્ષર *m_highlight_color;
};

/* If TYPE is from a typedef, issue a note showing the location
   to the user.
   Use HIGHLIGHT_COLOR as the highlight color.  */

સ્થિર શૂન્ય
maybe_inform_typedef_location (વૃક્ષ type, અચલ અક્ષર *highlight_color)
{
  જો (!typedef_variant_p (type))
    પાછા;

  વૃક્ષ typedef_decl = TYPE_NAME (type);
  gcc_assert (વૃક્ષ_CODE (typedef_decl) == TYPE_DECL);
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

સ્થિર વૃક્ષ
convert_for_assignment (location_t location, location_t પદાવલિ_loc, વૃક્ષ type,
			વૃક્ષ rhs, વૃક્ષ origtype, ગણના impl_conv errtype,
			તાર્કિક null_pointer_constant, વૃક્ષ fundecl,
			વૃક્ષ function, પૂર્ણાંક parmnum, પૂર્ણાંક warnopt /* = 0 */)
{
  ગણના વૃક્ષ_code codel = વૃક્ષ_CODE (type);
  વૃક્ષ orig_rhs = rhs;
  વૃક્ષ rhstype;
  ગણના વૃક્ષ_code coder;
  વૃક્ષ rname = NULL_વૃક્ષ;
  તાર્કિક objc_ok = ખોટું;

  /* Use the expansion point location to handle cases such as user's
     function returning a wrong-type macro defined in a system header.  */
  location = expansion_point_location_if_in_system_header (location);

  જો (errtype == ic_argpass)
    {
      વૃક્ષ selector;
      /* Change pointer to function to the function itself for
	 diagnostics.  */
      જો (વૃક્ષ_CODE (function) == ADDR_પદાવલિ
	  && વૃક્ષ_CODE (વૃક્ષ_OPERAND (function, 0)) == FUNCTION_DECL)
	function = વૃક્ષ_OPERAND (function, 0);

      /* Handle an ObjC selector specially for diagnostics.  */
      selector = objc_message_selector ();
      rname = function;
      જો (selector && parmnum > 2)
	{
	  rname = selector;
	  parmnum -= 2;
	}
    }

  /* This macro is used to emit diagnostics to ensure that all format
     strings are complete sentences, visible to gettext and checked at
     compile time.  */
#define PEDWARN_FOR_ASSIGNMENT(LOCATION, PLOC, OPT, AR, AS, IN, RE)	 \
  કરો {                                                                   \
    પસંદગી (errtype)                                                     \
      {                                                                  \
      સ્થિતિ ic_argpass:                                                   \
	{								\
	  auto_diagnostic_group d;						\
	  જો (pedwarn (PLOC, OPT, AR, parmnum, rname))		\
	    inform_for_arg (fundecl, (PLOC), parmnum, type, rhstype); \
	}								\
        તોડો;                                                           \
      સ્થિતિ ic_assign:                                                    \
        pedwarn (LOCATION, OPT, AS);                                     \
        તોડો;                                                           \
      સ્થિતિ ic_init:                                                      \
      સ્થિતિ ic_init_const:                                                \
        pedwarn_init (LOCATION, OPT, IN);                                \
        તોડો;                                                           \
      સ્થિતિ ic_return:                                                    \
        pedwarn (LOCATION, OPT, RE);					 \
        તોડો;                                                           \
      મૂળભૂત:                                                           \
        gcc_unreachable ();                                              \
      }                                                                  \
  } જ્યારે (0)

  /* This macro is used to emit diagnostics to ensure that all format
     strings are complete sentences, visible to gettext and checked at
     compile time.  It can be called with 'pedwarn' or 'warning_at'.  */
#define WARNING_FOR_QUALIFIERS(PEDWARN, LOCATION, PLOC, OPT, AR, AS, IN, RE, QUALS) \
  કરો {                                                                   \
    પસંદગી (errtype)                                                     \
      {                                                                  \
      સ્થિતિ ic_argpass:                                                   \
	{								 \
	  auto_diagnostic_group d;					 \
	  જો (PEDWARN) {						 \
	    જો (pedwarn (PLOC, OPT, AR, parmnum, rname, QUALS))          \
	      inform_for_arg (fundecl, (PLOC), parmnum, type, rhstype);  \
	  } નહીંતર {							 \
	    જો (warning_at (PLOC, OPT, AR, parmnum, rname, QUALS))	 \
	      inform_for_arg (fundecl, (PLOC), parmnum, type, rhstype);  \
	  }								 \
	}								 \
        તોડો;                                                           \
      સ્થિતિ ic_assign:                                                    \
	જો (PEDWARN)							 \
	  pedwarn (LOCATION, OPT, AS, QUALS);                            \
	નહીંતર								 \
	  warning_at (LOCATION, OPT, AS, QUALS);                         \
        તોડો;                                                           \
      સ્થિતિ ic_init:                                                      \
      સ્થિતિ ic_init_const:                                                \
	જો (PEDWARN)							 \
	  pedwarn (LOCATION, OPT, IN, QUALS);                            \
	નહીંતર								 \
	  warning_at (LOCATION, OPT, IN, QUALS);                         \
        તોડો;                                                           \
      સ્થિતિ ic_return:                                                    \
	જો (PEDWARN)							 \
	  pedwarn (LOCATION, OPT, RE, QUALS);                            \
	નહીંતર								 \
	  warning_at (LOCATION, OPT, RE, QUALS);                         \
        તોડો;                                                           \
      મૂળભૂત:                                                           \
        gcc_unreachable ();                                              \
      }                                                                  \
  } જ્યારે (0)

  /* This macro is used to emit diagnostics to ensure that all format
     strings are complete sentences, visible to gettext and checked at
     compile time.  It is the same as PEDWARN_FOR_ASSIGNMENT but with an
     extra parameter to enumerate qualifiers.  */
#define PEDWARN_FOR_QUALIFIERS(LOCATION, PLOC, OPT, AR, AS, IN, RE, QUALS) \
   WARNING_FOR_QUALIFIERS (સાચું, LOCATION, PLOC, OPT, AR, AS, IN, RE, QUALS)


  જો (વૃક્ષ_CODE (rhs) == EXCESS_PRECISION_પદાવલિ)
    rhs = વૃક્ષ_OPERAND (rhs, 0);

  rhstype = વૃક્ષ_TYPE (rhs);
  coder = વૃક્ષ_CODE (rhstype);

  જો (coder == ERROR_MARK)
    પાછા error_mark_ગાંઠ;

  જો (c_dialect_objc ())
    {
      પૂર્ણાંક parmno;

      પસંદગી (errtype)
	{
	સ્થિતિ ic_return:
	  parmno = 0;
	  તોડો;

	સ્થિતિ ic_assign:
	  parmno = -1;
	  તોડો;

	સ્થિતિ ic_init:
	સ્થિતિ ic_init_const:
	  parmno = -2;
	  તોડો;

	મૂળભૂત:
	  parmno = parmnum;
	  તોડો;
	}

      objc_ok = objc_compare_types (type, rhstype, parmno, rname);
    }

  જો (warn_cxx_compat)
    {
      વૃક્ષ checktype = origtype != NULL_વૃક્ષ ? origtype : rhstype;
      જો (checktype != error_mark_ગાંઠ
	  && વૃક્ષ_CODE (type) == ENUMERAL_TYPE
	  && TYPE_MAIN_VARIANT (checktype) != TYPE_MAIN_VARIANT (type))
	પસંદગી (errtype)
	  {
	  સ્થિતિ ic_argpass:
	    જો (pedwarn (પદાવલિ_loc, OPT_Wc___compat, "enum conversion when "
			 "passing argument %d of %qE is invalid in C++",
			 parmnum, rname))
	      inform ((fundecl && !DECL_IS_UNDECLARED_BUILTIN (fundecl))
		      ? DECL_SOURCE_LOCATION (fundecl) : પદાવલિ_loc,
		      "expected %qT but argument is of type %qT",
		      type, rhstype);
	    તોડો;
	  સ્થિતિ ic_assign:
	    pedwarn (location, OPT_Wc___compat, "enum conversion from %qT to "
		     "%qT in assignment is invalid in C++", rhstype, type);
	    તોડો;
	  સ્થિતિ ic_init:
	  સ્થિતિ ic_init_const:
	    pedwarn_init (location, OPT_Wc___compat, "enum conversion from "
			  "%qT to %qT in initialization is invalid in C++",
			  rhstype, type);
	    તોડો;
	  સ્થિતિ ic_return:
	    pedwarn (location, OPT_Wc___compat, "enum conversion from %qT to "
		     "%qT in return is invalid in C++", rhstype, type);
	    તોડો;
	  મૂળભૂત:
	    gcc_unreachable ();
	  }
    }

  જો (warn_enum_conversion)
    {
      વૃક્ષ checktype = origtype != NULL_વૃક્ષ ? origtype : rhstype;
      જો (checktype != error_mark_ગાંઠ
	  && વૃક્ષ_CODE (checktype) == ENUMERAL_TYPE
	  && વૃક્ષ_CODE (type) == ENUMERAL_TYPE
	  && !comptypes (TYPE_MAIN_VARIANT (checktype), TYPE_MAIN_VARIANT (type)))
       {
	  gcc_rich_location loc (location);
	  warning_at (&loc, OPT_Wenum_conversion,
		      "implicit conversion from %qT to %qT",
		      checktype, type);
       }
    }

  જો (TYPE_MAIN_VARIANT (type) == TYPE_MAIN_VARIANT (rhstype))
    {
      warn_for_address_of_packed_member (type, orig_rhs);
      જો (type != rhstype)
	/* Convert RHS to TYPE in order to not lose TYPE in diagnostics.  */
	rhs = convert (type, rhs);
      પાછા rhs;
    }

  જો (coder == VOID_TYPE)
    {
      /* Except for passing an argument to an unprototyped function,
	 this is a constraint violation.  When passing an argument to
	 an unprototyped function, it is compile-time undefined;
	 making it a constraint in that case was rejected in
	 DR#252.  */
      અચલ અક્ષર સંદેશ[] = "void value not ignored as it ought to be";
      જો (warnopt)
	warning_at (location, warnopt, સંદેશ);
      નહીંતર
	error_at (location, સંદેશ);
      પાછા error_mark_ગાંઠ;
    }
  rhs = require_complete_type (location, rhs);
  જો (rhs == error_mark_ગાંઠ)
    પાછા error_mark_ગાંઠ;

  જો (coder == POINTER_TYPE && reject_gcc_builtin (rhs))
    પાછા error_mark_ગાંઠ;

  /* A non-reference type can convert to a reference.  This handles
     va_start, va_copy and possibly port built-ins.  */
  જો (codel == REFERENCE_TYPE && coder != REFERENCE_TYPE)
    {
      જો (!lvalue_p (rhs))
	{
	  અચલ અક્ષર સંદેશ[] = "cannot pass rvalue to reference parameter";
	  જો (warnopt)
	    warning_at (location, warnopt, સંદેશ);
	  નહીંતર
	    error_at (location, સંદેશ);
	  પાછા error_mark_ગાંઠ;
	}
      જો (!c_mark_addressable (rhs))
	પાછા error_mark_ગાંઠ;
      rhs = build1 (ADDR_પદાવલિ, c_build_pointer_type (વૃક્ષ_TYPE (rhs)), rhs);
      SET_પદાવલિ_LOCATION (rhs, location);

      rhs = convert_for_assignment (location, પદાવલિ_loc,
				    c_build_pointer_type (વૃક્ષ_TYPE (type)),
				    rhs, origtype, errtype,
				    null_pointer_constant, fundecl, function,
				    parmnum, warnopt);
      જો (rhs == error_mark_ગાંઠ)
	પાછા error_mark_ગાંઠ;

      rhs = build1 (NOP_પદાવલિ, type, rhs);
      SET_પદાવલિ_LOCATION (rhs, location);
      પાછા rhs;
    }
  /* Some types can interconvert without explicit casts.  */
  નહીંતર જો (codel == VECTOR_TYPE && coder == VECTOR_TYPE
	   && vector_types_convertible_p (type, વૃક્ષ_TYPE (rhs), સાચું))
    પાછા convert (type, rhs);
  /* Arithmetic types all interconvert, and enum is treated like int.  */
  નહીંતર જો ((codel == INTEGER_TYPE || codel == REAL_TYPE
	    || codel == FIXED_POINT_TYPE
	    || codel == ENUMERAL_TYPE || codel == COMPLEX_TYPE
	    || codel == BOOLEAN_TYPE || codel == BITINT_TYPE)
	   && (coder == INTEGER_TYPE || coder == REAL_TYPE
	       || coder == FIXED_POINT_TYPE
	       || coder == ENUMERAL_TYPE || coder == COMPLEX_TYPE
	       || coder == BOOLEAN_TYPE || coder == BITINT_TYPE))
    {
      જો (warnopt && errtype == ic_argpass)
	maybe_warn_builtin_no_proto_arg (પદાવલિ_loc, fundecl, parmnum, type,
					 rhstype);

      તાર્કિક save = in_late_દ્વિઅંકી_op;
      જો (C_BOOLEAN_TYPE_P (type) || codel == COMPLEX_TYPE
	  || (coder == REAL_TYPE
	      && (codel == INTEGER_TYPE || codel == ENUMERAL_TYPE)
	      && sanitize_flags_p (SANITIZE_FLOAT_CAST)))
	in_late_દ્વિઅંકી_op = સાચું;
      વૃક્ષ ret = convert_and_check (પદાવલિ_loc != UNKNOWN_LOCATION
				    ? પદાવલિ_loc : location, type, orig_rhs,
				    errtype == ic_init_const);
      in_late_દ્વિઅંકી_op = save;
      પાછા ret;
    }

  /* Aggregates in different TUs might need conversion.  */
  જો ((codel == RECORD_TYPE || codel == UNION_TYPE)
      && codel == coder
      && comptypes (TYPE_MAIN_VARIANT (type), TYPE_MAIN_VARIANT (rhstype)))
    પાછા convert_and_check (પદાવલિ_loc != UNKNOWN_LOCATION
			      ? પદાવલિ_loc : location, type, rhs);

  /* Conversion to a transparent union or record from its member types.
     This applies only to function arguments.  */
  જો (((codel == UNION_TYPE || codel == RECORD_TYPE)
      && TYPE_TRANSPARENT_AGGR (type))
      && errtype == ic_argpass)
    {
      વૃક્ષ memb, marginal_memb = NULL_વૃક્ષ;

      માટે (memb = TYPE_FIELDS (type); memb ; memb = DECL_CHAIN (memb))
	{
	  વૃક્ષ memb_type = વૃક્ષ_TYPE (memb);

	  જો (comptypes (TYPE_MAIN_VARIANT (memb_type),
			 TYPE_MAIN_VARIANT (rhstype)))
	    તોડો;

	  જો (વૃક્ષ_CODE (memb_type) != POINTER_TYPE)
	    ચાલુ;

	  જો (coder == POINTER_TYPE)
	    {
	      વૃક્ષ ttl = વૃક્ષ_TYPE (memb_type);
	      વૃક્ષ ttr = વૃક્ષ_TYPE (rhstype);

	      /* Any non-function converts to a [const][volatile] void *
		 and vice versa; otherwise, targets must be the same.
		 Meanwhile, the lhs target must have all the qualifiers of
		 the rhs.  */
	      જો ((VOID_TYPE_P (ttl) && !TYPE_ATOMIC (ttl))
		  || (VOID_TYPE_P (ttr) && !TYPE_ATOMIC (ttr))
		  || comp_target_types (location, memb_type, rhstype))
		{
		  પૂર્ણાંક lquals = TYPE_QUALS (ttl) & ~TYPE_QUAL_ATOMIC;
		  પૂર્ણાંક rquals = TYPE_QUALS (ttr) & ~TYPE_QUAL_ATOMIC;
		  /* If this type won't generate any warnings, use it.  */
		  જો (lquals == rquals
		      || ((વૃક્ષ_CODE (ttr) == FUNCTION_TYPE
			   && વૃક્ષ_CODE (ttl) == FUNCTION_TYPE)
			  ? ((lquals | rquals) == rquals)
			  : ((lquals | rquals) == lquals)))
		    તોડો;

		  /* Keep looking for a better type, but remember this one.  */
		  જો (!marginal_memb)
		    marginal_memb = memb;
		}
	    }

	  /* Can convert integer zero to any pointer type.  */
	  જો (null_pointer_constant)
	    {
	      rhs = null_pointer_ગાંઠ;
	      તોડો;
	    }
	}

      જો (memb || marginal_memb)
	{
	  જો (!memb)
	    {
	      /* We have only a marginally acceptable member type;
		 it needs a warning.  */
	      વૃક્ષ ttl = વૃક્ષ_TYPE (વૃક્ષ_TYPE (marginal_memb));
	      વૃક્ષ ttr = વૃક્ષ_TYPE (rhstype);

	      /* Const and volatile mean something different for function
		 types, so the usual warnings are not appropriate.  */
	      જો (વૃક્ષ_CODE (ttr) == FUNCTION_TYPE
		  && વૃક્ષ_CODE (ttl) == FUNCTION_TYPE)
		{
		  /* Because const and volatile on functions are
		     restrictions that say the function will not do
		     certain things, it is okay to use a const or volatile
		     function where an ordinary one is wanted, but not
		     vice-versa.  */
		  જો (TYPE_QUALS_NO_ADDR_SPACE (ttl)
		      & ~TYPE_QUALS_NO_ADDR_SPACE (ttr))
		    PEDWARN_FOR_QUALIFIERS (location, પદાવલિ_loc,
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
	      નહીંતર જો (TYPE_QUALS_NO_ADDR_SPACE (ttr)
		       & ~TYPE_QUALS_NO_ADDR_SPACE (ttl))
		PEDWARN_FOR_QUALIFIERS (location, પદાવલિ_loc,
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

	  જો (!fundecl || !DECL_IN_SYSTEM_HEADER (fundecl))
	    pedwarn (location, OPT_Wpedantic,
		     "ISO C prohibits argument conversion to union type");

	  rhs = fold_convert_loc (location, વૃક્ષ_TYPE (memb), rhs);
	  પાછા build_constructor_single (type, memb, rhs);
	}
    }

  /* Conversions among pointers */
  નહીંતર જો ((codel == POINTER_TYPE || codel == REFERENCE_TYPE)
	   && (coder == codel))
    {
      /* If RHS refers to a built-in declared without a prototype
	 BLTIN is the declaration of the built-in with a prototype
	 and RHSTYPE is set to the actual type of the built-in.  */
      વૃક્ષ bltin;
      rhstype = type_or_builtin_type (rhs, &bltin);

      વૃક્ષ ttl = વૃક્ષ_TYPE (type);
      વૃક્ષ ttr = વૃક્ષ_TYPE (rhstype);
      તાર્કિક is_opaque_pointer;
      તાર્કિક target_cmp = ખોટું;   /* Cache comp_target_types () result.  */
      addr_space_t asl;
      addr_space_t asr;

      વૃક્ષ mvl = remove_qualifiers (ttl);
      વૃક્ષ mvr = remove_qualifiers (ttr);

      /* Opaque pointers are treated like void pointers.  */
      is_opaque_pointer = vector_targets_convertible_p (ttl, ttr);

      /* The Plan 9 compiler permits a pointer to a struct to be
	 automatically converted into a pointer to an anonymous field
	 within the struct.  */
      જો (flag_plan9_extensions
	  && RECORD_OR_UNION_TYPE_P (mvl)
	  && RECORD_OR_UNION_TYPE_P (mvr)
	  && mvl != mvr)
	{
	  વૃક્ષ new_rhs = convert_to_anonymous_field (location, type, rhs);
	  જો (new_rhs != NULL_વૃક્ષ)
	    {
	      rhs = new_rhs;
	      rhstype = વૃક્ષ_TYPE (rhs);
	      coder = વૃક્ષ_CODE (rhstype);
	      ttr = વૃક્ષ_TYPE (rhstype);
	      mvr = TYPE_MAIN_VARIANT (ttr);
	    }
	}

      /* C++ does not allow the implicit conversion void* -> T*.  However,
	 for the purpose of reducing the number of false positives, we
	 tolerate the special case of

		int *p = NULL;

	 where NULL is typically defined in C to be '(void *) 0'.  */
      જો (VOID_TYPE_P (ttr) && rhs != null_pointer_ગાંઠ && !VOID_TYPE_P (ttl))
	warning_at (errtype == ic_argpass ? પદાવલિ_loc : location,
		    OPT_Wc___compat,
		    "request for implicit conversion "
		    "from %qT to %qT not permitted in C++", rhstype, type);

      /* Warn of new allocations that are not big enough for the target
	 type.  */
      જો (warn_alloc_size && વૃક્ષ_CODE (rhs) == CALL_પદાવલિ)
	જો (વૃક્ષ fndecl = get_callee_fndecl (rhs))
	  જો (DECL_IS_MALLOC (fndecl))
	    {
	      વૃક્ષ attrs = TYPE_ATTRIBUTES (વૃક્ષ_TYPE (fndecl));
	      વૃક્ષ alloc_size = lookup_attribute ("alloc_size", attrs);
	      જો (alloc_size)
		warn_for_alloc_size (location, ttl, rhs, alloc_size);
	    }

      /* See if the pointers point to incompatible address spaces.  */
      asl = TYPE_ADDR_SPACE (ttl);
      asr = TYPE_ADDR_SPACE (ttr);
      જો (!null_pointer_constant_p (rhs)
	  && asr != asl && !targetm.addr_space.subset_p (asr, asl))
	{
	  auto_diagnostic_group d;
	  તાર્કિક diagnosed = સાચું;
	  પસંદગી (errtype)
	    {
	    સ્થિતિ ic_argpass:
	      {
		અચલ અક્ષર સંદેશ[] = G_("passing argument %d of %qE from "
				      "pointer to non-enclosed address space");
		જો (warnopt)
		  diagnosed
		    = warning_at (પદાવલિ_loc, warnopt, સંદેશ, parmnum, rname);
		નહીંતર
		  error_at (પદાવલિ_loc, સંદેશ, parmnum, rname);
	      તોડો;
	      }
	    સ્થિતિ ic_assign:
	      {
		અચલ અક્ષર સંદેશ[] = G_("assignment from pointer to "
				      "non-enclosed address space");
		જો (warnopt)
		  diagnosed = warning_at (location, warnopt, સંદેશ);
		નહીંતર
		  error_at (location, સંદેશ);
		તોડો;
	      }
	    સ્થિતિ ic_init:
	    સ્થિતિ ic_init_const:
	      {
		અચલ અક્ષર સંદેશ[] = G_("initialization from pointer to "
				      "non-enclosed address space");
		જો (warnopt)
		  diagnosed = warning_at (location, warnopt, સંદેશ);
		નહીંતર
		  error_at (location, સંદેશ);
		તોડો;
	      }
	    સ્થિતિ ic_return:
	      {
		અચલ અક્ષર સંદેશ[] = G_("return from pointer to "
				      "non-enclosed address space");
		જો (warnopt)
		  diagnosed = warning_at (location, warnopt, સંદેશ);
		નહીંતર
		  error_at (location, સંદેશ);
		તોડો;
	      }
	    મૂળભૂત:
	      gcc_unreachable ();
	    }
	  જો (diagnosed)
	    {
	      જો (errtype == ic_argpass)
		inform_for_arg (fundecl, પદાવલિ_loc, parmnum, type, rhstype);
	      નહીંતર
		inform (location, "expected %qT but pointer is of type %qT",
			type, rhstype);
	    }
	  પાછા error_mark_ગાંઠ;
	}

      /* Check if the right-hand side has a format attribute but the
	 left-hand side doesn't.  */
      જો (warn_suggest_attribute_format
	  && check_missing_format_attribute (type, rhstype))
	{
	  પસંદગી (errtype)
	  {
	  સ્થિતિ ic_argpass:
	    warning_at (પદાવલિ_loc, OPT_Wsuggest_attribute_format,
			"argument %d of %qE might be "
			"a candidate for a format attribute",
			parmnum, rname);
	    તોડો;
	  સ્થિતિ ic_assign:
	    warning_at (location, OPT_Wsuggest_attribute_format,
			"assignment left-hand side might be "
			"a candidate for a format attribute");
	    તોડો;
	  સ્થિતિ ic_init:
	  સ્થિતિ ic_init_const:
	    warning_at (location, OPT_Wsuggest_attribute_format,
			"initialization left-hand side might be "
			"a candidate for a format attribute");
	    તોડો;
	  સ્થિતિ ic_return:
	    warning_at (location, OPT_Wsuggest_attribute_format,
			"return type might be "
			"a candidate for a format attribute");
	    તોડો;
	  મૂળભૂત:
	    gcc_unreachable ();
	  }
	}

      /* See if the pointers point to incompatible scalar storage orders.  */
      જો (warn_scalar_storage_order
	  && !null_pointer_constant_p (rhs)
	  && (AGGREGATE_TYPE_P (ttl) && TYPE_REVERSE_STORAGE_ORDER (ttl))
	     != (AGGREGATE_TYPE_P (ttr) && TYPE_REVERSE_STORAGE_ORDER (ttr)))
	{
	  વૃક્ષ t;

	  પસંદગી (errtype)
	  {
	  સ્થિતિ ic_argpass:
	    /* Do not warn for built-in functions, for example memcpy, since we
	       control how they behave and they can be useful in this area.  */
	    જો (વૃક્ષ_CODE (rname) != FUNCTION_DECL
		|| !fndecl_built_in_p (rname))
	      warning_at (location, OPT_Wscalar_storage_order,
			  "passing argument %d of %qE from incompatible "
			  "scalar storage order", parmnum, rname);
	    તોડો;
	  સ્થિતિ ic_assign:
	    /* Do not warn if the RHS is a call to a function that returns a
	       pointer that is not an alias.  */
	    જો (વૃક્ષ_CODE (rhs) != CALL_પદાવલિ
		|| (t = get_callee_fndecl (rhs)) == NULL_વૃક્ષ
		|| !DECL_IS_MALLOC (t))
	      warning_at (location, OPT_Wscalar_storage_order,
			  "assignment to %qT from pointer type %qT with "
			  "incompatible scalar storage order", type, rhstype);
	    તોડો;
	  સ્થિતિ ic_init:
	  સ્થિતિ ic_init_const:
	    /* Likewise.  */
	    જો (વૃક્ષ_CODE (rhs) != CALL_પદાવલિ
		|| (t = get_callee_fndecl (rhs)) == NULL_વૃક્ષ
		|| !DECL_IS_MALLOC (t))
	      warning_at (location, OPT_Wscalar_storage_order,
			  "initialization of %qT from pointer type %qT with "
			  "incompatible scalar storage order", type, rhstype);
	    તોડો;
	  સ્થિતિ ic_return:
	    warning_at (location, OPT_Wscalar_storage_order,
			"returning %qT from pointer type with incompatible "
			"scalar storage order %qT", rhstype, type);
	    તોડો;
	  મૂળભૂત:
	    gcc_unreachable ();
	  }
	}

      /* Any non-function converts to a [const][volatile] void *
	 and vice versa; otherwise, targets must be the same.
	 Meanwhile, the lhs target must have all the qualifiers of the rhs.  */
      જો ((VOID_TYPE_P (ttl) && !TYPE_ATOMIC (ttl))
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
	  જો (વૃક્ષ_CODE (ttr) == ARRAY_TYPE)
	    {
	      ttr = strip_array_types (ttr);
	      ttl = strip_array_types (ttl);

	      જો (TYPE_QUALS_NO_ADDR_SPACE_NO_ATOMIC (ttr)
		  & ~TYPE_QUALS_NO_ADDR_SPACE_NO_ATOMIC (ttl))
		WARNING_FOR_QUALIFIERS (flag_isoc23,
					location, પદાવલિ_loc,
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
          નહીંતર જો (pedantic
	      && ((VOID_TYPE_P (ttl) && વૃક્ષ_CODE (ttr) == FUNCTION_TYPE)
		  ||
		  (VOID_TYPE_P (ttr)
		   && !null_pointer_constant
		   && વૃક્ષ_CODE (ttl) == FUNCTION_TYPE)))
	    PEDWARN_FOR_ASSIGNMENT (location, પદાવલિ_loc, OPT_Wpedantic,
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
	  નહીંતર જો (વૃક્ષ_CODE (ttr) != FUNCTION_TYPE
		   && વૃક્ષ_CODE (ttl) != FUNCTION_TYPE)
	    {
	       /* Assignments between atomic and non-atomic objects are OK.  */
	       તાર્કિક warn_quals_ped = TYPE_QUALS_NO_ADDR_SPACE_NO_ATOMIC (ttr)
				     & ~TYPE_QUALS_NO_ADDR_SPACE_NO_ATOMIC (ttl);
	       તાર્કિક warn_quals = TYPE_QUALS_NO_ADDR_SPACE_NO_ATOMIC (ttr)
				 & ~TYPE_QUALS_NO_ADDR_SPACE_NO_ATOMIC (strip_array_types (ttl));

	      /* Don't warn about loss of qualifier for conversions from
		 qualified void* to pointers to arrays with corresponding
		 qualifier on the element type (except for pedantic before C23). */
	      જો (warn_quals || (warn_quals_ped && pedantic && !flag_isoc23))
		PEDWARN_FOR_QUALIFIERS (location, પદાવલિ_loc,
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
	      નહીંતર જો (warn_quals_ped)
		pedwarn_c11 (location, OPT_Wc11_c23_compat,
			     "array with qualifier on the element is not qualified before C23");

	      /* If this is not a case of ignoring a mismatch in signedness,
		 no warning.  */
	      નહીંતર જો (VOID_TYPE_P (ttl) || VOID_TYPE_P (ttr)
		       || target_cmp)
		;
	      /* If there is a mismatch, do warn.  */
	      નહીંતર જો (warn_pointer_sign)
		પસંદગી (errtype)
		  {
		  સ્થિતિ ic_argpass:
		    {
		      auto_diagnostic_group d;
		      range_label_for_type_mismatch rhs_label (rhstype, type);
		      gcc_rich_location richloc (પદાવલિ_loc, &rhs_label,
						 highlight_colors::actual);
		      જો (pedwarn (&richloc, OPT_Wpointer_sign,
				   "pointer targets in passing argument %d of "
				   "%qE differ in signedness", parmnum, rname))
			inform_for_arg (fundecl, પદાવલિ_loc, parmnum, type,
					rhstype);
		    }
		    તોડો;
		  સ્થિતિ ic_assign:
		    pedwarn (location, OPT_Wpointer_sign,
			     "pointer targets in assignment from %qT to %qT "
			     "differ in signedness", rhstype, type);
		    તોડો;
		  સ્થિતિ ic_init:
		  સ્થિતિ ic_init_const:
		    pedwarn_init (location, OPT_Wpointer_sign,
				  "pointer targets in initialization of %qT "
				  "from %qT differ in signedness", type,
				  rhstype);
		    તોડો;
		  સ્થિતિ ic_return:
		    pedwarn (location, OPT_Wpointer_sign, "pointer targets in "
			     "returning %qT from a function with return type "
			     "%qT differ in signedness", rhstype, type);
		    તોડો;
		  મૂળભૂત:
		    gcc_unreachable ();
		  }
	    }
	  નહીંતર જો (વૃક્ષ_CODE (ttl) == FUNCTION_TYPE
		   && વૃક્ષ_CODE (ttr) == FUNCTION_TYPE)
	    {
	      /* Because const and volatile on functions are restrictions
		 that say the function will not do certain things,
		 it is okay to use a const or volatile function
		 where an ordinary one is wanted, but not vice-versa.  */
	      જો (TYPE_QUALS_NO_ADDR_SPACE (ttl)
		  & ~TYPE_QUALS_NO_ADDR_SPACE (ttr))
		PEDWARN_FOR_QUALIFIERS (location, પદાવલિ_loc,
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
      નહીંતર જો (!objc_ok)
	{
	  auto_diagnostic_group d;
	  તાર્કિક warned = ખોટું;
	  pp_markup::element_expected_type e_type (type);
	  pp_markup::element_actual_type e_rhstype (rhstype);
	  પસંદગી (errtype)
	    {
	    સ્થિતિ ic_argpass:
	      {
		range_label_for_type_mismatch rhs_label (rhstype, type);
		gcc_rich_location richloc (પદાવલિ_loc, &rhs_label,
					   highlight_colors::actual);
		warned
		  = permerror_opt (&richloc, OPT_Wincompatible_pointer_types,
				   "passing argument %d of %qE from "
				   "incompatible pointer type",
				   parmnum, rname);
		જો (warned)
		  inform_for_arg (fundecl, પદાવલિ_loc, parmnum, type, rhstype);
	      }
	      તોડો;
	    સ્થિતિ ic_assign:
	      જો (bltin)
		warned
		  = permerror_opt (location, OPT_Wincompatible_pointer_types,
				   "assignment to %e from pointer to "
				   "%qD with incompatible type %e",
				   &e_type, bltin, &e_rhstype);
	      નહીંતર
		warned
		  = permerror_opt (location, OPT_Wincompatible_pointer_types,
				   "assignment to %e from incompatible "
				   "pointer type %e",
				   &e_type, &e_rhstype);
	      તોડો;
	    સ્થિતિ ic_init:
	    સ્થિતિ ic_init_const:
	      જો (bltin)
		warned
		  = permerror_init (location, OPT_Wincompatible_pointer_types,
				    "initialization of %e from pointer to "
				    "%qD with incompatible type %e",
				    &e_type, bltin, &e_rhstype);
	      નહીંતર
		warned
		  = permerror_init (location, OPT_Wincompatible_pointer_types,
				    "initialization of %e from incompatible "
				    "pointer type %e",
				    &e_type, &e_rhstype);
	      તોડો;
	    સ્થિતિ ic_return:
	      જો (bltin)
		warned
		  = permerror_opt (location, OPT_Wincompatible_pointer_types,
				   "returning pointer to %qD of type %e from "
				   "a function with incompatible type %e",
				   bltin, &e_rhstype, &e_type);
	      નહીંતર
		warned
		  = permerror_opt (location, OPT_Wincompatible_pointer_types,
				   "returning %e from a function with "
				   "incompatible return type %e",
				   &e_rhstype, &e_type);
	      તોડો;
	    મૂળભૂત:
	      gcc_unreachable ();
	    }
	  જો (warned)
	    {
	      /* If the mismatching function type is a pointer to a function,
		 try to show the decl of the function.  */
	      જો (વૃક્ષ_CODE (rhs) == ADDR_પદાવલિ
		  && વૃક્ષ_CODE (વૃક્ષ_OPERAND (rhs, 0)) == FUNCTION_DECL)
		{
		  વૃક્ષ rhs_fndecl = વૃક્ષ_OPERAND (rhs, 0);
		  જો (!DECL_IS_UNDECLARED_BUILTIN (rhs_fndecl))
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

      પાછા convert (type, rhs);
    }
  નહીંતર જો (codel == POINTER_TYPE && coder == ARRAY_TYPE)
    {
      /* ??? This should not be an error when inlining calls to
	 unprototyped functions.  */
      અચલ અક્ષર સંદેશ[] = "invalid use of non-lvalue array";
      જો (warnopt)
	warning_at (location, warnopt, સંદેશ);
      નહીંતર
	error_at (location, સંદેશ);
      પાછા error_mark_ગાંઠ;
    }
  નહીંતર જો (codel == POINTER_TYPE
	   && (coder == INTEGER_TYPE
	       || coder == ENUMERAL_TYPE
	       || coder == BOOLEAN_TYPE
	       || coder == NULLPTR_TYPE
	       || coder == BITINT_TYPE))
    {
      જો (null_pointer_constant && c_inhibit_evaluation_warnings == 0
	  && coder != NULLPTR_TYPE)
	warning_at (location, OPT_Wzero_as_null_pointer_constant,
		    "zero as null pointer constant");
      /* A NULLPTR type is just a nullptr always.  */
      જો (coder == NULLPTR_TYPE)
	પાછા omit_one_operand_loc (પદાવલિ_loc, type, nullptr_ગાંઠ, rhs);
      /* An explicit constant 0 or type nullptr_t can convert to a pointer,
	 or one that results from arithmetic, even including a cast to
	 integer type.  */
      નહીંતર જો (!null_pointer_constant)
	પસંદગી (errtype)
	  {
	  સ્થિતિ ic_argpass:
	    {
	      auto_diagnostic_group d;
	      range_label_for_type_mismatch rhs_label (rhstype, type);
	      gcc_rich_location richloc (પદાવલિ_loc, &rhs_label,
					 highlight_colors::actual);
	      જો (permerror_opt (&richloc, OPT_Wint_conversion,
				 "passing argument %d of %qE makes pointer "
				 "from integer without a cast", parmnum, rname))
		{
		  maybe_emit_indirection_note (પદાવલિ_loc, rhs, type);
		  inform_for_arg (fundecl, પદાવલિ_loc, parmnum, type, rhstype);
		}
	    }
	    તોડો;
	  સ્થિતિ ic_assign:
	    permerror_opt (location, OPT_Wint_conversion,
			   "assignment to %qT from %qT makes pointer from "
			   "integer without a cast", type, rhstype);
	    તોડો;
	  સ્થિતિ ic_init:
	  સ્થિતિ ic_init_const:
	    permerror_init (location, OPT_Wint_conversion,
			    "initialization of %qT from %qT makes pointer "
			    "from integer without a cast", type, rhstype);
	    તોડો;
	  સ્થિતિ ic_return:
	    permerror_init (location, OPT_Wint_conversion,
			    "returning %qT from a function with return type "
			    "%qT makes pointer from integer without a cast",
			    rhstype, type);
	    તોડો;
	  મૂળભૂત:
	    gcc_unreachable ();
	  }

      પાછા convert (type, rhs);
    }
  નહીંતર જો ((codel == INTEGER_TYPE || codel == BITINT_TYPE)
	   && coder == POINTER_TYPE)
    {
      પસંદગી (errtype)
	{
	સ્થિતિ ic_argpass:
	  {
	    auto_diagnostic_group d;
	    range_label_for_type_mismatch rhs_label (rhstype, type);
	    gcc_rich_location richloc (પદાવલિ_loc, &rhs_label,
				       highlight_colors::actual);
	    જો (permerror_opt (&richloc, OPT_Wint_conversion,
			       "passing argument %d of %qE makes integer from "
			       "pointer without a cast", parmnum, rname))
	      {
		maybe_emit_indirection_note (પદાવલિ_loc, rhs, type);
		inform_for_arg (fundecl, પદાવલિ_loc, parmnum, type, rhstype);
	      }
	  }
	  તોડો;
	સ્થિતિ ic_assign:
	  permerror_opt (location, OPT_Wint_conversion,
			 "assignment to %qT from %qT makes integer from "
			 "pointer without a cast", type, rhstype);
	  તોડો;
	સ્થિતિ ic_init:
	સ્થિતિ ic_init_const:
	  permerror_init (location, OPT_Wint_conversion,
			  "initialization of %qT from %qT makes integer "
			  "from pointer without a cast", type, rhstype);
	  તોડો;
	સ્થિતિ ic_return:
	  permerror_opt (location, OPT_Wint_conversion, "returning %qT from a "
			 "function with return type %qT makes integer from "
			 "pointer without a cast", rhstype, type);
	  તોડો;
	મૂળભૂત:
	  gcc_unreachable ();
	}

      પાછા convert (type, rhs);
    }
  નહીંતર જો (C_BOOLEAN_TYPE_P (type)
	   /* The type nullptr_t may be converted to bool.  The
	      result is false.  */
	   && (coder == POINTER_TYPE || coder == NULLPTR_TYPE))
    {
      વૃક્ષ ret;
      તાર્કિક save = in_late_દ્વિઅંકી_op;
      in_late_દ્વિઅંકી_op = સાચું;
      ret = convert (type, rhs);
      in_late_દ્વિઅંકી_op = save;
      પાછા ret;
    }
  નહીંતર જો (codel == NULLPTR_TYPE && null_pointer_constant)
    પાછા convert (type, rhs);

  પસંદગી (errtype)
    {
    સ્થિતિ ic_argpass:
      {
	auto_diagnostic_group d;
	range_label_for_type_mismatch rhs_label (rhstype, type);
	gcc_rich_location richloc (પદાવલિ_loc, &rhs_label,
				   highlight_colors::actual);
	અચલ અક્ષર સંદેશ[] = G_("incompatible type for argument %d of %qE");
	જો (warnopt)
	  warning_at (પદાવલિ_loc, warnopt, સંદેશ, parmnum, rname);
	નહીંતર
	  error_at (&richloc, સંદેશ, parmnum, rname);
	inform_for_arg (fundecl, પદાવલિ_loc, parmnum, type, rhstype);
      }
      તોડો;
    સ્થિતિ ic_assign:
      {
	અચલ અક્ષર સંદેશ[]
	  = G_("incompatible types when assigning to type %qT from type %qT");
	જો (warnopt)
	  warning_at (પદાવલિ_loc, 0, સંદેશ, type, rhstype);
	નહીંતર
	  error_at (પદાવલિ_loc, સંદેશ, type, rhstype);
	તોડો;
      }
    સ્થિતિ ic_init:
    સ્થિતિ ic_init_const:
      {
	અચલ અક્ષર સંદેશ[]
	  = G_("incompatible types when initializing type %qT using type %qT");
	જો (warnopt)
	  warning_at (location, 0, સંદેશ, type, rhstype);
	નહીંતર
	  error_at (location, સંદેશ, type, rhstype);
	તોડો;
      }
    સ્થિતિ ic_return:
      {
	અચલ અક્ષર સંદેશ[]
	  = G_("incompatible types when returning type %qT but %qT was expected");
	જો (warnopt)
	  warning_at (location, 0, સંદેશ, rhstype, type);
	નહીંતર
	  error_at (location, સંદેશ, rhstype, type);
	તોડો;
      }
    મૂળભૂત:
      gcc_unreachable ();
    }

  પાછા error_mark_ગાંઠ;
}

/* If VALUE is a compound expr all of whose expressions are constant, then
   return its value.  Otherwise, return error_mark_node.

   This is for handling COMPOUND_EXPRs as initializer elements
   which is allowed with a warning when -pedantic is specified.  */

સ્થિર વૃક્ષ
valid_compound_પદાવલિ_initializer (વૃક્ષ કિંમત, વૃક્ષ endtype)
{
  જો (વૃક્ષ_CODE (કિંમત) == COMPOUND_પદાવલિ)
    {
      જો (valid_compound_પદાવલિ_initializer (વૃક્ષ_OPERAND (કિંમત, 0), endtype)
	  == error_mark_ગાંઠ)
	પાછા error_mark_ગાંઠ;
      પાછા valid_compound_પદાવલિ_initializer (વૃક્ષ_OPERAND (કિંમત, 1),
					      endtype);
    }
  નહીંતર જો (!initializer_constant_valid_p (કિંમત, endtype))
    પાછા error_mark_ગાંઠ;
  નહીંતર
    પાછા કિંમત;
}

/* Perform appropriate conversions on the initial value of a variable,
   store it in the declaration DECL,
   and print any error messages that are appropriate.
   If ORIGTYPE is not NULL_TREE, it is the original type of INIT.
   If the init is invalid, store an ERROR_MARK.

   INIT_LOC is the location of the initial value.  */

શૂન્ય
store_init_કિંમત (location_t init_loc, વૃક્ષ decl, વૃક્ષ init, વૃક્ષ origtype)
{
  વૃક્ષ કિંમત, type;
  તાર્કિક npc = ખોટું;
  તાર્કિક int_const_પદાવલિ = ખોટું;
  તાર્કિક arith_const_પદાવલિ = ખોટું;

  /* If variable's type was invalidly declared, just ignore it.  */

  type = વૃક્ષ_TYPE (decl);
  જો (વૃક્ષ_CODE (type) == ERROR_MARK)
    પાછા;

  /* Digest the specified initializer into an expression.  */

  જો (init)
    {
      npc = null_pointer_constant_p (init);
      int_const_પદાવલિ = (વૃક્ષ_CODE (init) == INTEGER_CST
			&& !વૃક્ષ_OVERFLOW (init)
			&& INTEGRAL_TYPE_P (વૃક્ષ_TYPE (init)));
      /* Not fully determined before folding.  */
      arith_const_પદાવલિ = સાચું;
    }
  તાર્કિક constexpr_p = (VAR_P (decl)
		      && C_DECL_DECLARED_CONSTEXPR (decl));
  કિંમત = digest_init (init_loc, decl, type, init, origtype, npc,
		       int_const_પદાવલિ, arith_const_પદાવલિ, સાચું,
		       વૃક્ષ_STATIC (decl) || constexpr_p, constexpr_p);

  /* Store the expression if valid; else report error.  */

  જો (!in_system_header_at (આગત_location)
      && AGGREGATE_TYPE_P (વૃક્ષ_TYPE (decl)) && !વૃક્ષ_STATIC (decl))
    warning (OPT_Wtraditional, "traditional C rejects automatic "
	     "aggregate initialization");

  જો (કિંમત != error_mark_ગાંઠ || વૃક્ષ_CODE (decl) != FUNCTION_DECL)
    DECL_INITIAL (decl) = કિંમત;

  /* ANSI wants warnings about out-of-range constant initializers.  */
  STRIP_TYPE_NOPS (કિંમત);
  જો (વૃક્ષ_STATIC (decl))
    constant_expression_warning (કિંમત);

  /* Check if we need to set array size from compound literal size.  */
  જો (વૃક્ષ_CODE (type) == ARRAY_TYPE
      && TYPE_DOMAIN (type) == NULL_વૃક્ષ
      && કિંમત != error_mark_ગાંઠ)
    {
      વૃક્ષ inside_init = init;

      STRIP_TYPE_NOPS (inside_init);
      inside_init = fold (inside_init);

      જો (વૃક્ષ_CODE (inside_init) == COMPOUND_LITERAL_પદાવલિ)
	{
	  વૃક્ષ cldecl = COMPOUND_LITERAL_પદાવલિ_DECL (inside_init);

	  જો (TYPE_DOMAIN (વૃક્ષ_TYPE (cldecl)))
	    {
	      /* For int foo[] = (int [3]){1}; we need to set array size
		 now since later on array initializer will be just the
		 brace enclosed list of the compound literal.  */
	      વૃક્ષ etype = strip_array_types (વૃક્ષ_TYPE (decl));
	      type = build_distinct_type_copy (TYPE_MAIN_VARIANT (type));
	      TYPE_DOMAIN (type) = TYPE_DOMAIN (વૃક્ષ_TYPE (cldecl));
	      layout_type (type);
	      layout_decl (cldecl, 0);
	      વૃક્ષ_TYPE (decl)
		= c_build_qualified_type (type, TYPE_QUALS (etype));
	    }
	}
    }
}

/* Methods for storing and printing names for error messages.  */

/* Implement a spelling stack that allows components of a name to be pushed
   and popped.  Each element on the stack is this structure.  */

સંરચના spelling
{
  પૂર્ણાંક kind;
  સંઘ
    {
      unsigned HOST_WIDE_INT i;
      અચલ અક્ષર *s;
    } u;
};

#define SPELLING_STRING 1
#define SPELLING_MEMBER 2
#define SPELLING_BOUNDS 3

સ્થિર સંરચના spelling *spelling;	/* Next stack element (unused).  */
સ્થિર સંરચના spelling *spelling_base;	/* Spelling stack base.  */
સ્થિર પૂર્ણાંક spelling_size;		/* Size of the spelling stack.  */

/* Macros to save and restore the spelling stack around push_... functions.
   Alternative to SAVE_SPELLING_STACK.  */

#define SPELLING_DEPTH() (spelling - spelling_base)
#define RESTORE_SPELLING_DEPTH(DEPTH) (spelling = spelling_base + (DEPTH))

/* Push an element on the spelling stack with type KIND and assign VALUE
   to MEMBER.  */

#define ધકેલો_SPELLING(KIND, કિંમત_2, MEMBER)				\
{									\
  પૂર્ણાંક depth = SPELLING_DEPTH ();					\
									\
  જો (depth >= spelling_size)						\
    {									\
      spelling_size += 10;						\
      spelling_base = XRESIZEVEC (સંરચના spelling, spelling_base,	\
				  spelling_size);			\
      RESTORE_SPELLING_DEPTH (depth);					\
    }									\
									\
  spelling->kind = (KIND);						\
  spelling->MEMBER = (કિંમત_2);						\
  spelling++;								\
}

/* Push STRING on the stack.  Printed literally.  */

સ્થિર શૂન્ય
ધકેલો_string (અચલ અક્ષર *string)
{
  ધકેલો_SPELLING (SPELLING_STRING, string, u.s);
}

/* Push a member name on the stack.  Printed as '.' STRING.  */

સ્થિર શૂન્ય
ધકેલો_member_name (વૃક્ષ decl)
{
  અચલ અક્ષર *અચલ string
    = (DECL_NAME (decl)
       ? identifier_to_locale (IDENTIFIER_POINTER (DECL_NAME (decl)))
       : _("<anonymous>"));
  ધકેલો_SPELLING (SPELLING_MEMBER, string, u.s);
}

/* Push an array bounds on the stack.  Printed as [BOUNDS].  */

સ્થિર શૂન્ય
ધકેલો_array_bounds (unsigned HOST_WIDE_INT bounds)
{
  ધકેલો_SPELLING (SPELLING_BOUNDS, bounds, u.i);
}

/* Compute the maximum size in bytes of the printed spelling.  */

સ્થિર પૂર્ણાંક
spelling_length (શૂન્ય)
{
  પૂર્ણાંક size = 0;
  સંરચના spelling *p;

  માટે (p = spelling_base; p < spelling; p++)
    {
      જો (p->kind == SPELLING_BOUNDS)
	size += 25;
      નહીંતર
	size += strlen (p->u.s) + 1;
    }

  પાછા size;
}

/* Print the spelling to BUFFER and return it.  */

સ્થિર અક્ષર *
print_spelling (અક્ષર *buffer)
{
  અક્ષર *d = buffer;
  સંરચના spelling *p;

  માટે (p = spelling_base; p < spelling; p++)
    જો (p->kind == SPELLING_BOUNDS)
      {
	sprintf (d, "[" HOST_WIDE_INT_PRINT_UNSIGNED "]", p->u.i);
	d += strlen (d);
      }
    નહીંતર
      {
	અચલ અક્ષર *s;
	જો (p->kind == SPELLING_MEMBER)
	  *d++ = '.';
	માટે (s = p->u.s; (*d = *s++); d++)
	  ;
      }
  *d++ = '\0';
  પાછા buffer;
}

/* Check whether INIT, a floating or integer constant, is
   representable in TYPE, a real floating type with the same radix or
   a decimal floating type initialized with a binary floating
   constant.  Return true if OK, false if not.  */
સ્થિર તાર્કિક
constexpr_init_fits_real_type (વૃક્ષ type, વૃક્ષ init)
{
  gcc_assert (SCALAR_FLOAT_TYPE_P (type));
  gcc_assert (વૃક્ષ_CODE (init) == INTEGER_CST || વૃક્ષ_CODE (init) == REAL_CST);
  જો (વૃક્ષ_CODE (init) == REAL_CST
      && TYPE_MODE (વૃક્ષ_TYPE (init)) == TYPE_MODE (type))
    {
      /* Same mode, no conversion required except for the case of
	 signaling NaNs if the types are incompatible (e.g. double and
	 long double with the same mode).  */
      જો (REAL_કિંમત_ISSIGNALING_NAN (વૃક્ષ_REAL_CST (init))
	  && !comptypes (TYPE_MAIN_VARIANT (type),
			 TYPE_MAIN_VARIANT (વૃક્ષ_TYPE (init))))
	પાછા ખોટું;
      પાછા સાચું;
    }
  જો (વૃક્ષ_CODE (init) == INTEGER_CST)
    {
      વૃક્ષ converted = build_real_from_int_cst (type, init);
      તાર્કિક fail = ખોટું;
      wide_int w = real_to_integer (&વૃક્ષ_REAL_CST (converted), &fail,
				    TYPE_PRECISION (વૃક્ષ_TYPE (init)));
      પાછા !fail && wi::eq_p (w, wi::to_wide (init));
    }
  જો (REAL_કિંમત_ISSIGNALING_NAN (વૃક્ષ_REAL_CST (init)))
    પાછા ખોટું;
  જો ((REAL_કિંમત_ISINF (વૃક્ષ_REAL_CST (init))
       && MODE_HAS_INFINITIES (TYPE_MODE (type)))
      || (REAL_કિંમત_ISNAN (વૃક્ષ_REAL_CST (init))
	  && MODE_HAS_NANS (TYPE_MODE (type))))
    પાછા સાચું;
  જો (DECIMAL_FLOAT_TYPE_P (type)
      && !DECIMAL_FLOAT_TYPE_P (વૃક્ષ_TYPE (init)))
    {
      /* This is valid if the real number represented by the
	 initializer can be exactly represented in the decimal
	 type.  Compare the values using MPFR.  */
      REAL_કિંમત_TYPE t;
      real_convert (&t, TYPE_MODE (type), &વૃક્ષ_REAL_CST (init));
      mpfr_t bin_val, dec_val;
      mpfr_init2 (bin_val, REAL_MODE_FORMAT (TYPE_MODE (વૃક્ષ_TYPE (init)))->p);
      mpfr_init2 (dec_val, REAL_MODE_FORMAT (TYPE_MODE (વૃક્ષ_TYPE (init)))->p);
      mpfr_from_real (bin_val, &વૃક્ષ_REAL_CST (init), MPFR_RNDN);
      અક્ષર string[256];
      real_to_decimal (string, &t, કદ string, 0, 1);
      તાર્કિક res = (mpfr_strtofr (dec_val, string, ખાલી, 10, MPFR_RNDN) == 0
		  && mpfr_equal_p (bin_val, dec_val));
      mpfr_clear (bin_val);
      mpfr_clear (dec_val);
      પાછા res;
    }
  /* exact_real_truncate is not quite right here, since it doesn't
     allow even an exact conversion to subnormal values.  */
  REAL_કિંમત_TYPE t;
  real_convert (&t, TYPE_MODE (type), &વૃક્ષ_REAL_CST (init));
  પાછા real_identical (&t, &વૃક્ષ_REAL_CST (init));
}

/* Check whether INIT (location LOC) is valid as a 'constexpr'
   initializer for type TYPE, and give an error if not.  INIT has
   already been folded and verified to be constant.  INT_CONST_EXPR
   and ARITH_CONST_EXPR say whether it is an integer constant
   expression or arithmetic constant expression, respectively.  If
   TYPE is not a scalar type, this function does nothing.  */

સ્થિર શૂન્ય
check_constexpr_init (location_t loc, વૃક્ષ type, વૃક્ષ init,
		      તાર્કિક int_const_પદાવલિ, તાર્કિક arith_const_પદાવલિ)
{
  જો (POINTER_TYPE_P (type))
    {
      /* The initializer must be null.  */
      જો (વૃક્ષ_CODE (init) != INTEGER_CST || !integer_zerop (init))
	error_at (loc, "%<constexpr%> pointer initializer is not null");
      પાછા;
    }
  જો (INTEGRAL_TYPE_P (type))
    {
      /* The initializer must be an integer constant expression,
	 representable in the target type.  */
      જો (!int_const_પદાવલિ)
	{
	  જો (વૃક્ષ_CODE (init) == RAW_DATA_CST
	      && TYPE_PRECISION (type) == CHAR_BIT)
	    {
	      જો (!TYPE_UNSIGNED (type))
		માટે (unsigned પૂર્ણાંક i = 0;
		     i < (unsigned) RAW_DATA_LENGTH (init); ++i)
		  જો (RAW_DATA_SCHAR_ELT (init, i) < 0)
		    {
		      error_at (loc, "%<constexpr%> initializer not "
				"representable in type of object");
		      તોડો;
		    }
	    }
	  નહીંતર
	    error_at (loc, "%<constexpr%> integer initializer is not an "
		      "integer constant expression");
	}
      નહીંતર જો (!int_fits_type_p (init, type))
	error_at (loc, "%<constexpr%> initializer not representable in "
		  "type of object");
      પાછા;
    }
  /* We don't apply any extra checks to extension types such as vector
     or fixed-point types.  */
  જો (વૃક્ષ_CODE (type) != REAL_TYPE && વૃક્ષ_CODE (type) != COMPLEX_TYPE)
    પાછા;
  જો (!arith_const_પદાવલિ)
    {
      error_at (loc, "%<constexpr%> initializer is not an arithmetic "
		"constant expression");
      પાછા;
    }
  /* We don't apply any extra checks to complex integers.  */
  જો (વૃક્ષ_CODE (type) == COMPLEX_TYPE
      && વૃક્ષ_CODE (વૃક્ષ_TYPE (type)) != REAL_TYPE)
    પાછા;
  /* Following N3082, a real type cannot be initialized from a complex
     type and a binary type cannot be initialized from a decimal type
     (but initializing a decimal type from a binary type is OK).
     Signaling NaN initializers are OK only if the types are
     compatible (not just the same mode); all quiet NaN and infinity
     initializations are considered to preserve the value.  */
  જો (વૃક્ષ_CODE (વૃક્ષ_TYPE (init)) == COMPLEX_TYPE
      && SCALAR_FLOAT_TYPE_P (type))
    {
      error_at (loc, "%<constexpr%> initializer for a real type is of "
		"complex type");
      પાછા;
    }
  જો (SCALAR_FLOAT_TYPE_P (type)
      && SCALAR_FLOAT_TYPE_P (વૃક્ષ_TYPE (init))
      && DECIMAL_FLOAT_TYPE_P (વૃક્ષ_TYPE (init))
      && !DECIMAL_FLOAT_TYPE_P (type))
    {
      error_at (loc, "%<constexpr%> initializer for a binary "
		"floating-point type is of decimal type");
      પાછા;
    }
  તાર્કિક fits;
  જો (વૃક્ષ_CODE (type) == COMPLEX_TYPE)
    {
      પસંદગી (વૃક્ષ_CODE (init))
	{
	સ્થિતિ INTEGER_CST:
	સ્થિતિ REAL_CST:
	  fits = constexpr_init_fits_real_type (વૃક્ષ_TYPE (type), init);
	  તોડો;
	સ્થિતિ COMPLEX_CST:
	  fits = (constexpr_init_fits_real_type (વૃક્ષ_TYPE (type),
						 વૃક્ષ_REALPART (init))
		  && constexpr_init_fits_real_type (વૃક્ષ_TYPE (type),
						    વૃક્ષ_IMAGPART (init)));
	  તોડો;
	મૂળભૂત:
	  gcc_unreachable ();
	}
    }
  નહીંતર
    fits = constexpr_init_fits_real_type (type, init);
  જો (!fits)
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

સ્થિર વૃક્ષ
digest_init (location_t init_loc, વૃક્ષ decl, વૃક્ષ type, વૃક્ષ init,
	     વૃક્ષ origtype, તાર્કિક null_pointer_constant, તાર્કિક int_const_પદાવલિ,
	     તાર્કિક arith_const_પદાવલિ, તાર્કિક strict_string,
	     તાર્કિક require_constant, તાર્કિક require_constexpr)
{
  ગણના વૃક્ષ_code code = વૃક્ષ_CODE (type);
  વૃક્ષ inside_init = init;
  વૃક્ષ semantic_type = NULL_વૃક્ષ;
  તાર્કિક maybe_const = સાચું;

  જો (type == error_mark_ગાંઠ
      || !init
      || error_operand_p (init))
    પાછા error_mark_ગાંઠ;

  STRIP_TYPE_NOPS (inside_init);

  /* If require_constant is TRUE,  when the initializer is a call to
     .ACCESS_WITH_SIZE, use the first argument as the initializer.
     For example:
     y = (char *) .ACCESS_WITH_SIZE ((char *) &static_annotated.c,...)
     will be converted to
     y = &static_annotated.c.  */

  જો (require_constant
      && વૃક્ષ_CODE (inside_init) == NOP_પદાવલિ
      && વૃક્ષ_CODE (વૃક્ષ_OPERAND (inside_init, 0)) == CALL_પદાવલિ
      && is_access_with_size_p (વૃક્ષ_OPERAND (inside_init, 0)))
    inside_init
      = get_ref_from_access_with_size (વૃક્ષ_OPERAND (inside_init, 0));

  જો (!c_in_omp_for)
    {
      જો (વૃક્ષ_CODE (inside_init) == EXCESS_PRECISION_પદાવલિ)
	{
	  semantic_type = વૃક્ષ_TYPE (inside_init);
	  inside_init = વૃક્ષ_OPERAND (inside_init, 0);
	}
      inside_init = c_fully_fold (inside_init, require_constant, &maybe_const);
    }
  /* TODO: this may not detect all cases of expressions folding to
     constants that are not arithmetic constant expressions.  */
  જો (!maybe_const)
    arith_const_પદાવલિ = ખોટું;
  નહીંતર જો (!INTEGRAL_TYPE_P (વૃક્ષ_TYPE (inside_init))
	   && વૃક્ષ_CODE (વૃક્ષ_TYPE (inside_init)) != REAL_TYPE
	   && વૃક્ષ_CODE (વૃક્ષ_TYPE (inside_init)) != COMPLEX_TYPE)
    arith_const_પદાવલિ = ખોટું;
  નહીંતર જો (વૃક્ષ_CODE (inside_init) != INTEGER_CST
	   && વૃક્ષ_CODE (inside_init) != REAL_CST
	   && વૃક્ષ_CODE (inside_init) != COMPLEX_CST
	   && વૃક્ષ_CODE (inside_init) != RAW_DATA_CST)
    arith_const_પદાવલિ = ખોટું;
  નહીંતર જો (વૃક્ષ_OVERFLOW (inside_init))
    arith_const_પદાવલિ = ખોટું;

  /* Initialization of an array of chars from a string constant
     optionally enclosed in braces.  */

  જો (code == ARRAY_TYPE && inside_init
      && વૃક્ષ_CODE (inside_init) == STRING_CST)
    {
      વૃક્ષ typ1
	= (TYPE_ATOMIC (વૃક્ષ_TYPE (type))
	   ? c_build_qualified_type (TYPE_MAIN_VARIANT (વૃક્ષ_TYPE (type)),
				     TYPE_QUAL_ATOMIC)
	   : TYPE_MAIN_VARIANT (વૃક્ષ_TYPE (type)));
      /* Note that an array could be both an array of character type
	 and an array of wchar_t if wchar_t is signed char or unsigned
	 char.  */
      તાર્કિક char_array = (typ1 == char_type_ગાંઠ
			 || typ1 == signed_char_type_ગાંઠ
			 || typ1 == unsigned_char_type_ગાંઠ);
      તાર્કિક wchar_array = comptypes (typ1, wchar_type_ગાંઠ);
      તાર્કિક char16_array = comptypes (typ1, char16_type_ગાંઠ);
      તાર્કિક char32_array = comptypes (typ1, char32_type_ગાંઠ);

      જો (char_array || wchar_array || char16_array || char32_array)
	{
	  સંરચના c_પદાવલિ પદાવલિ;
	  વૃક્ષ typ2 = TYPE_MAIN_VARIANT (વૃક્ષ_TYPE (વૃક્ષ_TYPE (inside_init)));
	  તાર્કિક incompat_string_cst = ખોટું;
	  પદાવલિ.કિંમત = inside_init;
	  પદાવલિ.original_code = (strict_string ? STRING_CST : ERROR_MARK);
	  પદાવલિ.original_type = ખાલી;
	  પદાવલિ.m_decimal = 0;
	  maybe_warn_string_init (init_loc, type, પદાવલિ);

	  જો (flexible_array_member_type_p (type))
	    pedwarn_init (init_loc, OPT_Wpedantic,
			  "initialization of a flexible array member");

	  જો (comptypes (TYPE_MAIN_VARIANT (વૃક્ષ_TYPE (inside_init)),
			 TYPE_MAIN_VARIANT (type)))
	    પાછા inside_init;

	  જો (char_array)
	    {
	      જો (typ2 != char_type_ગાંઠ && typ2 != char8_type_ગાંઠ)
		incompat_string_cst = સાચું;
	    }
	  નહીંતર જો (!comptypes (typ1, typ2))
	    incompat_string_cst = સાચું;

          જો (incompat_string_cst)
            {
	      error_init (init_loc, "cannot initialize array of %qT from "
			  "a string literal with type array of %qT",
			  typ1, typ2);
	      પાછા error_mark_ગાંઠ;
            }

	  જો (require_constexpr
	      && TYPE_UNSIGNED (typ1) != TYPE_UNSIGNED (typ2))
	    {
	      /* Check if all characters of the string can be
		 represented in the type of the constexpr object being
		 initialized.  */
	      unsigned HOST_WIDE_INT len = વૃક્ષ_STRING_LENGTH (inside_init);
	      અચલ unsigned અક્ષર *p =
		(અચલ unsigned અક્ષર *) વૃક્ષ_STRING_POINTER (inside_init);
	      gcc_assert (CHAR_TYPE_SIZE == 8 && CHAR_BIT == 8);
	      માટે (unsigned i = 0; i < len; i++)
		જો (p[i] > 127)
		  {
		    error_init (init_loc, "%<constexpr%> initializer not "
				"representable in type of object");
		    તોડો;
		  }
	    }

	  જો (TYPE_DOMAIN (type) != NULL_વૃક્ષ
	      && TYPE_SIZE (type) != NULL_વૃક્ષ
	      && વૃક્ષ_CODE (TYPE_SIZE (type)) == INTEGER_CST)
	    {
	      unsigned HOST_WIDE_INT len = વૃક્ષ_STRING_LENGTH (inside_init);

	      જો (compare_વૃક્ષ_int (TYPE_SIZE_UNIT (type), len) < 0)
		{
		  unsigned HOST_WIDE_INT avail
		    = વૃક્ષ_to_uhwi (TYPE_SIZE_UNIT (type));
		  unsigned unit = TYPE_PRECISION (typ1) / BITS_PER_UNIT;
		  અચલ અક્ષર *p = વૃક્ષ_STRING_POINTER (inside_init);

		  /* Construct truncated string.  */
		  inside_init = build_string (avail, p);

		  /* Subtract the size of a single (possibly wide) character
		     because it may be ok to ignore the terminating NUL char
		     that is counted in the length of the constant.  */
		  જો (len - unit > avail)
		    pedwarn_init (init_loc, 0,
				  "initializer-string for array of %qT "
				  "is too long (%wu chars into %wu "
				  "available)", typ1, len, avail);
		  નહીંતર જો (warn_cxx_compat)
		    warning_at (init_loc, OPT_Wc___compat,
				"initializer-string for array of %qT "
				"is too long for C++ (%wu chars into %wu "
				"available)", typ1, len, avail);
		  નહીંતર જો (warn_unterminated_string_initialization
			   && get_attr_nonstring_decl (decl) == NULL_વૃક્ષ)
		    warning_at (init_loc,
				OPT_Wunterminated_string_initialization,
				"initializer-string for array of %qT "
				"truncates NUL terminator but destination "
				"lacks %qs attribute (%wu chars into %wu "
				"available)", typ1, "nonstring", len, avail);
		}
	    }

	  વૃક્ષ_TYPE (inside_init) = type;
	  પાછા inside_init;
	}
      નહીંતર જો (INTEGRAL_TYPE_P (typ1))
	{
	  error_init (init_loc, "array of inappropriate type initialized "
		      "from string constant");
	  પાછા error_mark_ગાંઠ;
	}
    }

  /* Build a VECTOR_CST from a *constant* vector constructor.  If the
     vector constructor is not constant (e.g. {1,2,3,foo()}) then punt
     below and handle as a constructor.  */
  જો (code == VECTOR_TYPE
      && VECTOR_TYPE_P (વૃક્ષ_TYPE (inside_init))
      && vector_types_convertible_p (વૃક્ષ_TYPE (inside_init), type, સાચું)
      && વૃક્ષ_CONSTANT (inside_init))
    {
      જો (વૃક્ષ_CODE (inside_init) == VECTOR_CST
	  && comptypes (TYPE_MAIN_VARIANT (વૃક્ષ_TYPE (inside_init)),
			TYPE_MAIN_VARIANT (type)))
	પાછા inside_init;

      જો (વૃક્ષ_CODE (inside_init) == CONSTRUCTOR)
	{
	  unsigned HOST_WIDE_INT ix;
	  વૃક્ષ કિંમત;
	  તાર્કિક constant_p = સાચું;

	  /* Iterate through elements and check if all constructor
	     elements are *_CSTs.  */
	  FOR_EACH_CONSTRUCTOR_કિંમત (CONSTRUCTOR_ELTS (inside_init), ix, કિંમત)
	    જો (!CONSTANT_CLASS_P (કિંમત))
	      {
		constant_p = ખોટું;
		તોડો;
	      }

	  જો (constant_p)
	    પાછા build_vector_from_ctor (type,
					   CONSTRUCTOR_ELTS (inside_init));
	}
    }

  જો (warn_sequence_point)
    verify_sequence_points (inside_init);

  /* Any type can be initialized
     from an expression of the same type, optionally with braces.  */

  જો (inside_init && વૃક્ષ_TYPE (inside_init) != NULL_વૃક્ષ
      && (comptypes (TYPE_MAIN_VARIANT (વૃક્ષ_TYPE (inside_init)),
		     TYPE_MAIN_VARIANT (type))
	  || (code == ARRAY_TYPE
	      && comptypes (વૃક્ષ_TYPE (inside_init), type))
	  || (gnu_vector_type_p (type)
	      && comptypes (વૃક્ષ_TYPE (inside_init), type))
	  || (code == POINTER_TYPE
	      && વૃક્ષ_CODE (વૃક્ષ_TYPE (inside_init)) == ARRAY_TYPE
	      && comptypes (વૃક્ષ_TYPE (વૃક્ષ_TYPE (inside_init)),
			    વૃક્ષ_TYPE (type)))))
    {
      જો (code == POINTER_TYPE)
	{
	  જો (વૃક્ષ_CODE (વૃક્ષ_TYPE (inside_init)) == ARRAY_TYPE)
	    {
	      જો (વૃક્ષ_CODE (inside_init) == STRING_CST
		  || વૃક્ષ_CODE (inside_init) == COMPOUND_LITERAL_પદાવલિ)
		inside_init = array_to_pointer_conversion
		  (init_loc, inside_init);
	      નહીંતર
		{
		  error_init (init_loc, "invalid use of non-lvalue array");
		  પાછા error_mark_ગાંઠ;
		}
	    }
	}

      જો (code == VECTOR_TYPE || c_hardbool_type_attr (type))
	/* Although the types are compatible, we may require a
	   conversion.  */
	inside_init = convert (type, inside_init);

      જો ((code == RECORD_TYPE || code == UNION_TYPE)
	  && !comptypes (TYPE_MAIN_VARIANT (type), TYPE_MAIN_VARIANT (વૃક્ષ_TYPE (inside_init))))
	{
	  error_init (init_loc, "invalid initializer");
	  પાછા error_mark_ગાંઠ;
	}

      જો (require_constant
	  && વૃક્ષ_CODE (inside_init) == COMPOUND_LITERAL_પદાવલિ)
	{
	  /* As an extension, allow initializing objects with static storage
	     duration with compound literals (which are then treated just as
	     the brace enclosed list they contain).  Also allow this for
	     vectors, as we can only assign them with compound literals.  */
	  જો (flag_isoc99 && code != VECTOR_TYPE)
	    pedwarn_init (init_loc, OPT_Wpedantic, "initializer element "
			  "is not constant");
	  વૃક્ષ decl = COMPOUND_LITERAL_પદાવલિ_DECL (inside_init);
	  inside_init = DECL_INITIAL (decl);
	}

      જો (code == ARRAY_TYPE && વૃક્ષ_CODE (inside_init) != STRING_CST
	  && વૃક્ષ_CODE (inside_init) != CONSTRUCTOR)
	{
	  error_init (init_loc, "array initialized from non-constant array "
		      "expression");
	  પાછા error_mark_ગાંઠ;
	}

      /* Compound expressions can only occur here if -Wpedantic or
	 -pedantic-errors is specified.  In the later case, we always want
	 an error.  In the former case, we simply want a warning.  */
      જો (require_constant && pedantic
	  && વૃક્ષ_CODE (inside_init) == COMPOUND_પદાવલિ)
	{
	  inside_init
	    = valid_compound_પદાવલિ_initializer (inside_init,
					       વૃક્ષ_TYPE (inside_init));
	  જો (inside_init == error_mark_ગાંઠ)
	    error_init (init_loc, "initializer element is not constant");
	  નહીંતર
	    pedwarn_init (init_loc, OPT_Wpedantic,
			  "initializer element is not constant");
	  જો (flag_pedantic_errors)
	    inside_init = error_mark_ગાંઠ;
	}
      નહીંતર જો (require_constant
	       && !initializer_constant_valid_p (inside_init,
						 વૃક્ષ_TYPE (inside_init)))
	{
	  error_init (init_loc, "initializer element is not constant");
	  inside_init = error_mark_ગાંઠ;
	}
      નહીંતર જો (require_constant && !maybe_const)
	pedwarn_init (init_loc, OPT_Wpedantic,
		      "initializer element is not a constant expression");
      નહીંતર જો (require_constexpr)
	check_constexpr_init (init_loc, type, inside_init,
			      int_const_પદાવલિ, arith_const_પદાવલિ);

      /* Added to enable additional -Wsuggest-attribute=format warnings.  */
      જો (વૃક્ષ_CODE (વૃક્ષ_TYPE (inside_init)) == POINTER_TYPE)
	inside_init = convert_for_assignment (init_loc, UNKNOWN_LOCATION,
					      type, inside_init, origtype,
					      (require_constant
					       ? ic_init_const
					       : ic_init), null_pointer_constant,
					      NULL_વૃક્ષ, NULL_વૃક્ષ, 0);
      જો (વૃક્ષ_CODE (inside_init) == RAW_DATA_CST
	  && c_inhibit_evaluation_warnings == 0
	  && warn_conversion
	  && !TYPE_UNSIGNED (type)
	  && TYPE_PRECISION (type) == CHAR_BIT)
	માટે (unsigned પૂર્ણાંક i = 0;
	     i < (unsigned) RAW_DATA_LENGTH (inside_init); ++i)
	  જો (RAW_DATA_SCHAR_ELT (inside_init, i) < 0)
	    warning_at (init_loc, OPT_Wconversion,
			"conversion from %qT to %qT changes value from "
			"%qd to %qd",
			integer_type_ગાંઠ, type,
			RAW_DATA_UCHAR_ELT (inside_init, i),
			RAW_DATA_SCHAR_ELT (inside_init, i));
      પાછા inside_init;
    }

  /* Handle scalar types, including conversions.  */

  જો (code == INTEGER_TYPE || code == REAL_TYPE || code == FIXED_POINT_TYPE
      || code == POINTER_TYPE || code == ENUMERAL_TYPE || code == BOOLEAN_TYPE
      || code == COMPLEX_TYPE || code == VECTOR_TYPE || code == NULLPTR_TYPE
      || code == BITINT_TYPE)
    {
      વૃક્ષ unconverted_init = inside_init;
      જો (વૃક્ષ_CODE (વૃક્ષ_TYPE (init)) == ARRAY_TYPE
	  && (વૃક્ષ_CODE (init) == STRING_CST
	      || વૃક્ષ_CODE (init) == COMPOUND_LITERAL_પદાવલિ))
	inside_init = init = array_to_pointer_conversion (init_loc, init);
      જો (semantic_type)
	inside_init = build1 (EXCESS_PRECISION_પદાવલિ, semantic_type,
			      inside_init);
      inside_init
	= convert_for_assignment (init_loc, UNKNOWN_LOCATION, type,
				  inside_init, origtype,
				  require_constant ? ic_init_const : ic_init,
				  null_pointer_constant, NULL_વૃક્ષ, NULL_વૃક્ષ,
				  0);

      /* Check to see if we have already given an error message.  */
      જો (inside_init == error_mark_ગાંઠ)
	;
      નહીંતર જો (require_constant && !વૃક્ષ_CONSTANT (inside_init))
	{
	  error_init (init_loc, "initializer element is not constant");
	  inside_init = error_mark_ગાંઠ;
	}
      નહીંતર જો (require_constant
	       && !initializer_constant_valid_p (inside_init,
						 વૃક્ષ_TYPE (inside_init)))
	{
	  error_init (init_loc, "initializer element is not computable at "
		      "load time");
	  inside_init = error_mark_ગાંઠ;
	}
      નહીંતર જો (require_constant && !maybe_const)
	pedwarn_init (init_loc, OPT_Wpedantic,
		      "initializer element is not a constant expression");
      નહીંતર જો (require_constexpr)
	check_constexpr_init (init_loc, type, unconverted_init,
			      int_const_પદાવલિ, arith_const_પદાવલિ);

      પાછા inside_init;
    }

  /* Come here only for records and arrays.  */

  જો (COMPLETE_TYPE_P (type) && વૃક્ષ_CODE (TYPE_SIZE (type)) != INTEGER_CST)
    {
      error_init (init_loc,
		  "variable-sized object may not be initialized except "
		  "with an empty initializer");
      પાછા error_mark_ગાંઠ;
    }

  error_init (init_loc, "invalid initializer");
  પાછા error_mark_ગાંઠ;
}

/* Handle initializers that use braces.  */

/* Type of object we are accumulating a constructor for.
   This type is always a RECORD_TYPE, UNION_TYPE or ARRAY_TYPE.  */
સ્થિર વૃક્ષ constructor_type;

/* For a RECORD_TYPE or UNION_TYPE, this is the chain of fields
   left to fill.  */
સ્થિર વૃક્ષ constructor_fields;

/* For an ARRAY_TYPE, this is the specified index
   at which to store the next element we get.  */
સ્થિર વૃક્ષ constructor_index;

/* For an ARRAY_TYPE, this is the maximum index.  */
સ્થિર વૃક્ષ constructor_max_index;

/* For a RECORD_TYPE, this is the first field not yet written out.  */
સ્થિર વૃક્ષ constructor_unfilled_fields;

/* For an ARRAY_TYPE, this is the index of the first element
   not yet written out.  */
સ્થિર વૃક્ષ constructor_unfilled_index;

/* In a RECORD_TYPE, the byte index of the next consecutive field.
   This is so we can generate gaps between fields, when appropriate.  */
સ્થિર વૃક્ષ constructor_bit_index;

/* If we are saving up the elements rather than allocating them,
   this is the list of elements so far (in reverse order,
   most recent first).  */
સ્થિર vec<constructor_elt, va_gc> *constructor_elements;

/* 1 if constructor should be incrementally stored into a constructor chain,
   0 if all the elements should be kept in AVL tree.  */
સ્થિર પૂર્ણાંક constructor_incremental;

/* 1 if so far this constructor's elements are all compile-time constants.  */
સ્થિર પૂર્ણાંક constructor_constant;

/* 1 if so far this constructor's elements are all valid address constants.  */
સ્થિર પૂર્ણાંક constructor_simple;

/* 1 if this constructor has an element that cannot be part of a
   constant expression.  */
સ્થિર પૂર્ણાંક constructor_nonconst;

/* 1 if this constructor is erroneous so far.  */
સ્થિર પૂર્ણાંક constructor_erroneous;

/* 1 if this constructor is the universal zero initializer { 0 }.  */
સ્થિર પૂર્ણાંક constructor_zeroinit;

/* 1 if this constructor should have padding bits zeroed (C23 {}.  */
સ્થિર તાર્કિક constructor_zero_padding_bits;

/* 1 if this constructor is a braced scalar initializer (further nested levels
   of braces are an error).  */
સ્થિર તાર્કિક constructor_braced_scalar;

/* Structure for managing pending initializer elements, organized as an
   AVL tree.  */

સંરચના init_ગાંઠ
{
  સંરચના init_ગાંઠ *ડાબું, *જમણું;
  સંરચના init_ગાંઠ *parent;
  પૂર્ણાંક balance;
  વૃક્ષ purpose;
  વૃક્ષ કિંમત;
  વૃક્ષ origtype;
};

/* Tree of pending elements at this constructor level.
   These are elements encountered out of order
   which belong at places we haven't reached yet in actually
   writing the output.
   Will never hold tree nodes across GC runs.  */
સ્થિર સંરચના init_ગાંઠ *constructor_pending_elts;

/* The SPELLING_DEPTH of this constructor.  */
સ્થિર પૂર્ણાંક constructor_depth;

/* DECL node for which an initializer is being read.
   0 means we are reading a constructor expression
   such as (struct foo) {...}.  */
સ્થિર વૃક્ષ constructor_decl;

/* Nonzero if there were any member designators in this initializer.  */
સ્થિર પૂર્ણાંક constructor_designated;

/* Nesting depth of designator list.  */
સ્થિર પૂર્ણાંક designator_depth;

/* Nonzero if there were diagnosed errors in this designator list.  */
સ્થિર પૂર્ણાંક designator_erroneous;


/* This stack has a level for each implicit or explicit level of
   structuring in the initializer, including the outermost one.  It
   saves the values of most of the variables above.  */

સંરચના constructor_range_ઢગલો;

સંરચના constructor_ઢગલો
{
  સંરચના constructor_ઢગલો *next;
  વૃક્ષ type;
  વૃક્ષ fields;
  વૃક્ષ index;
  વૃક્ષ max_index;
  વૃક્ષ unfilled_index;
  વૃક્ષ unfilled_fields;
  વૃક્ષ bit_index;
  vec<constructor_elt, va_gc> *elements;
  સંરચના init_ગાંઠ *pending_elts;
  પૂર્ણાંક offset;
  પૂર્ણાંક depth;
  /* If value nonzero, this value should replace the entire
     constructor at this level.  */
  સંરચના c_પદાવલિ replacement_કિંમત;
  સંરચના constructor_range_ઢગલો *range_ઢગલો;
  અક્ષર constant;
  અક્ષર simple;
  અક્ષર nonconst;
  અક્ષર implicit;
  અક્ષર erroneous;
  અક્ષર outer;
  અક્ષર incremental;
  અક્ષર designated;
  તાર્કિક zero_padding_bits;
  તાર્કિક braced_scalar;
  પૂર્ણાંક designator_depth;
};

સ્થિર સંરચના constructor_ઢગલો *constructor_ઢગલો;

/* This stack represents designators from some range designator up to
   the last designator in the list.  */

સંરચના constructor_range_ઢગલો
{
  સંરચના constructor_range_ઢગલો *next, *prev;
  સંરચના constructor_ઢગલો *ઢગલો;
  વૃક્ષ range_start;
  વૃક્ષ index;
  વૃક્ષ range_end;
  વૃક્ષ fields;
};

સ્થિર સંરચના constructor_range_ઢગલો *constructor_range_ઢગલો;

/* This stack records separate initializers that are nested.
   Nested initializers can't happen in ANSI C, but GNU C allows them
   in cases like { ... (struct foo) { ... } ... }.  */

સંરચના initializer_ઢગલો
{
  સંરચના initializer_ઢગલો *next;
  વૃક્ષ decl;
  સંરચના constructor_ઢગલો *constructor_ઢગલો;
  સંરચના constructor_range_ઢગલો *constructor_range_ઢગલો;
  vec<constructor_elt, va_gc> *elements;
  સંરચના spelling *spelling;
  સંરચના spelling *spelling_base;
  પૂર્ણાંક spelling_size;
  અક્ષર require_constant_કિંમત;
  અક્ષર require_constant_elements;
  અક્ષર require_constexpr_કિંમત;
  અક્ષર designated;
  rich_location *missing_brace_richloc;
};

સ્થિર સંરચના initializer_ઢગલો *initializer_ઢગલો;

/* Prepare to parse and output the initializer for variable DECL.  */

શૂન્ય
start_init (વૃક્ષ decl, વૃક્ષ asmspec_વૃક્ષ ATTRIBUTE_UNUSED,
	    તાર્કિક init_require_constant, તાર્કિક init_require_constexpr,
	    rich_location *richloc)
{
  અચલ અક્ષર *locus;
  સંરચના initializer_ઢગલો *p = XNEW (સંરચના initializer_ઢગલો);

  p->decl = constructor_decl;
  p->require_constant_કિંમત = require_constant_કિંમત;
  p->require_constant_elements = require_constant_elements;
  p->require_constexpr_કિંમત = require_constexpr_કિંમત;
  p->constructor_ઢગલો = constructor_ઢગલો;
  p->constructor_range_ઢગલો = constructor_range_ઢગલો;
  p->elements = constructor_elements;
  p->spelling = spelling;
  p->spelling_base = spelling_base;
  p->spelling_size = spelling_size;
  p->next = initializer_ઢગલો;
  p->missing_brace_richloc = richloc;
  p->designated = constructor_designated;
  initializer_ઢગલો = p;

  constructor_decl = decl;
  constructor_designated = 0;

  require_constant_કિંમત = init_require_constant;
  require_constexpr_કિંમત = init_require_constexpr;
  જો (decl != NULL_વૃક્ષ && decl != error_mark_ગાંઠ)
    {
      require_constant_elements
	= ((init_require_constant || (pedantic && !flag_isoc99))
	   /* For a scalar, you can always use any value to initialize,
	      even within braces.  */
	   && AGGREGATE_TYPE_P (વૃક્ષ_TYPE (decl)));
      locus = identifier_to_locale (IDENTIFIER_POINTER (DECL_NAME (decl)));
    }
  નહીંતર
    {
      require_constant_elements = ખોટું;
      locus = _("(anonymous)");
    }

  constructor_ઢગલો = 0;
  constructor_range_ઢગલો = 0;

  found_missing_braces = 0;

  spelling_base = 0;
  spelling_size = 0;
  RESTORE_SPELLING_DEPTH (0);

  જો (locus)
    ધકેલો_string (locus);
}

શૂન્ય
finish_init (શૂન્ય)
{
  સંરચના initializer_ઢગલો *p = initializer_ઢગલો;

  /* Free the whole constructor stack of this initializer.  */
  જ્યારે (constructor_ઢગલો)
    {
      સંરચના constructor_ઢગલો *q = constructor_ઢગલો;
      constructor_ઢગલો = q->next;
      XDELETE (q);
    }

  gcc_assert (!constructor_range_ઢગલો);

  /* Pop back to the data of the outer initializer (if any).  */
  XDELETE (spelling_base);

  constructor_decl = p->decl;
  require_constant_કિંમત = p->require_constant_કિંમત;
  require_constant_elements = p->require_constant_elements;
  require_constexpr_કિંમત = p->require_constexpr_કિંમત;
  constructor_ઢગલો = p->constructor_ઢગલો;
  constructor_designated = p->designated;
  constructor_range_ઢગલો = p->constructor_range_ઢગલો;
  constructor_elements = p->elements;
  spelling = p->spelling;
  spelling_base = p->spelling_base;
  spelling_size = p->spelling_size;
  initializer_ઢગલો = p->next;
  XDELETE (p);
}

/* Call here when we see the initializer is surrounded by braces.
   This is instead of a call to push_init_level;
   it is matched by a call to pop_init_level.

   TYPE is the type to initialize, for a constructor expression.
   For an initializer for a decl, TYPE is zero.  */

શૂન્ય
really_start_incremental_init (વૃક્ષ type)
{
  સંરચના constructor_ઢગલો *p = XNEW (સંરચના constructor_ઢગલો);

  જો (type == NULL_વૃક્ષ)
    type = વૃક્ષ_TYPE (constructor_decl);

  જો (VECTOR_TYPE_P (type)
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
  p->replacement_કિંમત.કિંમત = 0;
  p->replacement_કિંમત.original_code = ERROR_MARK;
  p->replacement_કિંમત.original_type = ખાલી;
  p->implicit = 0;
  p->range_ઢગલો = 0;
  p->outer = 0;
  p->incremental = constructor_incremental;
  p->designated = constructor_designated;
  p->zero_padding_bits = constructor_zero_padding_bits;
  p->braced_scalar = constructor_braced_scalar;
  p->designator_depth = designator_depth;
  p->next = 0;
  constructor_ઢગલો = p;

  constructor_constant = 1;
  constructor_simple = 1;
  constructor_nonconst = 0;
  constructor_depth = SPELLING_DEPTH ();
  constructor_elements = ખાલી;
  constructor_pending_elts = 0;
  constructor_type = type;
  constructor_incremental = 1;
  constructor_designated = 0;
  constructor_zero_padding_bits = ખોટું;
  constructor_zeroinit = 1;
  constructor_braced_scalar = ખોટું;
  designator_depth = 0;
  designator_erroneous = 0;

  જો (RECORD_OR_UNION_TYPE_P (constructor_type))
    {
      constructor_fields = TYPE_FIELDS (constructor_type);
      /* Skip any nameless bit fields at the beginning.  */
      જ્યારે (constructor_fields != NULL_વૃક્ષ
	     && DECL_UNNAMED_BIT_FIELD (constructor_fields))
	constructor_fields = DECL_CHAIN (constructor_fields);

      constructor_unfilled_fields = constructor_fields;
      constructor_bit_index = bitsize_zero_ગાંઠ;
    }
  નહીંતર જો (વૃક્ષ_CODE (constructor_type) == ARRAY_TYPE)
    {
      જો (TYPE_DOMAIN (constructor_type))
	{
	  constructor_max_index
	    = TYPE_MAX_કિંમત (TYPE_DOMAIN (constructor_type));

	  /* Detect non-empty initializations of zero-length arrays.  */
	  જો (constructor_max_index == NULL_વૃક્ષ
	      && TYPE_SIZE (constructor_type))
	    constructor_max_index = integer_minus_one_ગાંઠ;

	  /* constructor_max_index needs to be an INTEGER_CST.  Attempts
	     to initialize VLAs with a nonempty initializer will cause a
	     proper error; avoid tree checking errors as well by setting a
	     safe value.  */
	  જો (constructor_max_index
	      && વૃક્ષ_CODE (constructor_max_index) != INTEGER_CST)
	    constructor_max_index = integer_minus_one_ગાંઠ;

	  constructor_index
	    = convert (bitsizetype,
		       TYPE_MIN_કિંમત (TYPE_DOMAIN (constructor_type)));
	}
      નહીંતર
	{
	  constructor_index = bitsize_zero_ગાંઠ;
	  constructor_max_index = NULL_વૃક્ષ;
	}

      constructor_unfilled_index = constructor_index;
    }
  નહીંતર જો (gnu_vector_type_p (constructor_type))
    {
      /* Vectors are like simple fixed-size arrays.  */
      constructor_max_index =
	bitsize_int (TYPE_VECTOR_SUBPARTS (constructor_type) - 1);
      constructor_index = bitsize_zero_ગાંઠ;
      constructor_unfilled_index = constructor_index;
    }
  નહીંતર
    {
      /* Handle the case of int x = {5}; */
      constructor_fields = constructor_type;
      constructor_unfilled_fields = constructor_type;
      constructor_braced_scalar = સાચું;
    }
}

બાહ્ય location_t last_init_list_comma;

/* Called when we see an open brace for a nested initializer.  Finish
   off any pending levels with implicit braces.  */
શૂન્ય
finish_implicit_inits (location_t loc, સંરચના obstack *braced_init_obstack)
{
  જ્યારે (constructor_ઢગલો->implicit)
    {
      જો (RECORD_OR_UNION_TYPE_P (constructor_type)
	  && constructor_fields == NULL_વૃક્ષ)
	process_init_element (આગત_location,
			      કાઢો_init_level (loc, 1, braced_init_obstack,
					      last_init_list_comma),
			      સાચું, braced_init_obstack);
      નહીંતર જો (વૃક્ષ_CODE (constructor_type) == ARRAY_TYPE
	       && constructor_max_index
	       && વૃક્ષ_int_cst_lt (constructor_max_index,
				   constructor_index))
	process_init_element (આગત_location,
			      કાઢો_init_level (loc, 1, braced_init_obstack,
					      last_init_list_comma),
			      સાચું, braced_init_obstack);
      નહીંતર
	તોડો;
    }
}

/* Push down into a subobject, for initialization.
   If this is for an explicit set of braces, IMPLICIT is 0.
   If it is because the next element belongs at a lower level,
   IMPLICIT is 1 (or 2 if the push is because of designator list).  */

શૂન્ય
ધકેલો_init_level (location_t loc, પૂર્ણાંક implicit,
		 સંરચના obstack *braced_init_obstack)
{
  સંરચના constructor_ઢગલો *p;
  વૃક્ષ કિંમત = NULL_વૃક્ષ;

  /* Unless this is an explicit brace, we need to preserve previous
     content if any.  */
  જો (implicit)
    {
      જો (RECORD_OR_UNION_TYPE_P (constructor_type) && constructor_fields)
	કિંમત = find_init_member (constructor_fields, braced_init_obstack);
      નહીંતર જો (વૃક્ષ_CODE (constructor_type) == ARRAY_TYPE)
	કિંમત = find_init_member (constructor_index, braced_init_obstack);
    }

  p = XNEW (સંરચના constructor_ઢગલો);
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
  p->replacement_કિંમત.કિંમત = NULL_વૃક્ષ;
  p->replacement_કિંમત.original_code = ERROR_MARK;
  p->replacement_કિંમત.original_type = ખાલી;
  p->implicit = implicit;
  p->outer = 0;
  p->incremental = constructor_incremental;
  p->designated = constructor_designated;
  p->zero_padding_bits = constructor_zero_padding_bits;
  p->braced_scalar = constructor_braced_scalar;
  p->designator_depth = designator_depth;
  p->next = constructor_ઢગલો;
  p->range_ઢગલો = 0;
  constructor_ઢગલો = p;

  constructor_constant = 1;
  constructor_simple = 1;
  constructor_nonconst = 0;
  constructor_depth = SPELLING_DEPTH ();
  constructor_elements = ખાલી;
  constructor_incremental = 1;
  /* If the upper initializer is designated, then mark this as
     designated too to prevent bogus warnings.  */
  constructor_designated = p->designated;
  /* If the upper initializer has padding bits zeroed, that includes
     all nested initializers as well.  */
  constructor_zero_padding_bits = p->zero_padding_bits;
  constructor_braced_scalar = ખોટું;
  constructor_pending_elts = 0;
  જો (!implicit)
    {
      p->range_ઢગલો = constructor_range_ઢગલો;
      constructor_range_ઢગલો = 0;
      designator_depth = 0;
      designator_erroneous = 0;
    }

  /* Don't die if an entire brace-pair level is superfluous
     in the containing level.  */
  જો (constructor_type == NULL_વૃક્ષ)
    ;
  નહીંતર જો (RECORD_OR_UNION_TYPE_P (constructor_type))
    {
      /* Don't die if there are extra init elts at the end.  */
      જો (constructor_fields == NULL_વૃક્ષ)
	constructor_type = NULL_વૃક્ષ;
      નહીંતર
	{
	  constructor_type = વૃક્ષ_TYPE (constructor_fields);
	  ધકેલો_member_name (constructor_fields);
	  constructor_depth++;
	}
    }
  નહીંતર જો (વૃક્ષ_CODE (constructor_type) == ARRAY_TYPE)
    {
      constructor_type = વૃક્ષ_TYPE (constructor_type);
      ધકેલો_array_bounds (વૃક્ષ_to_uhwi (constructor_index));
      constructor_depth++;
    }

  જો (constructor_type == NULL_વૃક્ષ)
    {
      error_init (loc, "extra brace group at end of initializer");
      constructor_fields = NULL_વૃક્ષ;
      constructor_unfilled_fields = NULL_વૃક્ષ;
      પાછા;
    }

  જો (કિંમત && વૃક્ષ_CODE (કિંમત) == CONSTRUCTOR)
    {
      constructor_constant = વૃક્ષ_CONSTANT (કિંમત);
      constructor_simple = વૃક્ષ_STATIC (કિંમત);
      constructor_nonconst = CONSTRUCTOR_NON_CONST (કિંમત);
      constructor_elements = CONSTRUCTOR_ELTS (કિંમત);
      constructor_zero_padding_bits |= CONSTRUCTOR_ZERO_PADDING_BITS (કિંમત);
      જો (!vec_safe_is_empty (constructor_elements)
	  && (વૃક્ષ_CODE (constructor_type) == RECORD_TYPE
	      || વૃક્ષ_CODE (constructor_type) == ARRAY_TYPE))
	set_nonincremental_init (braced_init_obstack);
    }

  જો (implicit == 1)
    {
      found_missing_braces = 1;
      જો (initializer_ઢગલો->missing_brace_richloc)
	initializer_ઢગલો->missing_brace_richloc->add_fixit_ઉમેરો_before
	  (loc, "{");
    }

  જો (RECORD_OR_UNION_TYPE_P (constructor_type))
    {
      constructor_fields = TYPE_FIELDS (constructor_type);
      /* Skip any nameless bit fields at the beginning.  */
      જ્યારે (constructor_fields != NULL_વૃક્ષ
	     && DECL_UNNAMED_BIT_FIELD (constructor_fields))
	constructor_fields = DECL_CHAIN (constructor_fields);

      constructor_unfilled_fields = constructor_fields;
      constructor_bit_index = bitsize_zero_ગાંઠ;
    }
  નહીંતર જો (gnu_vector_type_p (constructor_type))
    {
      /* Vectors are like simple fixed-size arrays.  */
      constructor_max_index =
	bitsize_int (TYPE_VECTOR_SUBPARTS (constructor_type) - 1);
      constructor_index = bitsize_int (0);
      constructor_unfilled_index = constructor_index;
    }
  નહીંતર જો (વૃક્ષ_CODE (constructor_type) == ARRAY_TYPE)
    {
      જો (TYPE_DOMAIN (constructor_type))
	{
	  constructor_max_index
	    = TYPE_MAX_કિંમત (TYPE_DOMAIN (constructor_type));

	  /* Detect non-empty initializations of zero-length arrays.  */
	  જો (constructor_max_index == NULL_વૃક્ષ
	      && TYPE_SIZE (constructor_type))
	    constructor_max_index = integer_minus_one_ગાંઠ;

	  /* constructor_max_index needs to be an INTEGER_CST.  Attempts
	     to initialize VLAs will cause a proper error; avoid tree
	     checking errors as well by setting a safe value.  */
	  જો (constructor_max_index
	      && વૃક્ષ_CODE (constructor_max_index) != INTEGER_CST)
	    constructor_max_index = integer_minus_one_ગાંઠ;

	  constructor_index
	    = convert (bitsizetype,
		       TYPE_MIN_કિંમત (TYPE_DOMAIN (constructor_type)));
	}
      નહીંતર
	constructor_index = bitsize_zero_ગાંઠ;

      constructor_unfilled_index = constructor_index;
      જો (કિંમત && વૃક્ષ_CODE (કિંમત) == STRING_CST)
	{
	  /* We need to split the char/wchar array into individual
	     characters, so that we don't have to special case it
	     everywhere.  */
	  set_nonincremental_init_from_string (કિંમત, braced_init_obstack);
	}
    }
  નહીંતર
    {
      જો (constructor_type != error_mark_ગાંઠ)
	{
	  જો (p->braced_scalar)
	    permerror_init (આગત_location, 0,
			    "braces around scalar initializer");
	  નહીંતર
	    warning_init (આગત_location, 0,
			  "braces around scalar initializer");
	  constructor_braced_scalar = સાચું;
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

સંરચના c_પદાવલિ
કાઢો_init_level (location_t loc, પૂર્ણાંક implicit,
		સંરચના obstack *braced_init_obstack,
		location_t ઉમેરો_before)
{
  સંરચના constructor_ઢગલો *p;
  સંરચના c_પદાવલિ ret;
  ret.કિંમત = NULL_વૃક્ષ;
  ret.original_code = ERROR_MARK;
  ret.original_type = ખાલી;
  ret.m_decimal = 0;

  જો (implicit == 0)
    {
      /* When we come to an explicit close brace,
	 pop any inner levels that didn't have explicit braces.  */
      જ્યારે (constructor_ઢગલો->implicit)
	process_init_element (આગત_location,
			      કાઢો_init_level (loc, 1, braced_init_obstack,
					      ઉમેરો_before),
			      સાચું, braced_init_obstack);
      gcc_assert (!constructor_range_ઢગલો);
    }
  નહીંતર
    જો (initializer_ઢગલો->missing_brace_richloc)
      initializer_ઢગલો->missing_brace_richloc->add_fixit_ઉમેરો_before
	(ઉમેરો_before, "}");

  /* Now output all pending elements.  */
  constructor_incremental = 1;
  output_pending_init_elements (1, braced_init_obstack);

  p = constructor_ઢગલો;

  /* Error for initializing a flexible array member.  */
  જો (constructor_type && constructor_fields
      && flexible_array_member_type_p (constructor_type))
    {
      /* Silently discard empty initializations.  The parser will
	 already have pedwarned for empty brackets for C17 and earlier.  */
      જો (integer_zerop (constructor_unfilled_index))
	constructor_type = NULL_વૃક્ષ;
      જો (constructor_type || flag_isoc23)
	{
	  gcc_assert (!constructor_type || !TYPE_SIZE (constructor_type));

	  જો (constructor_depth <= 2)
	    pedwarn_init (loc, OPT_Wpedantic,
			  "initialization of a flexible array member");
	  નહીંતર જો (constructor_type)
	    error_init (loc, "initialization of flexible array member "
			     "in a nested context");
	  નહીંતર
	    pedwarn_init (loc, OPT_Wpedantic,
			  "initialization of flexible array member "
			  "in a nested context");

	  /* We have already issued an error message for the existence
	     of a flexible array member not at the end of the structure.
	     Discard the initializer so that we do not die later.  */
	  જો (constructor_type
	      && DECL_CHAIN (constructor_fields) != NULL_વૃક્ષ
	      && (!p->type || વૃક્ષ_CODE (p->type) != UNION_TYPE))
	    constructor_type = NULL_વૃક્ષ;
	}
    }

  પસંદગી (vec_safe_length (constructor_elements))
    {
    સ્થિતિ 0:
      /* Initialization with { } counts as zeroinit.  */
      constructor_zeroinit = 1;
      તોડો;
    સ્થિતિ 1:
      /* This might be zeroinit as well.  */
      જો (integer_zerop ((*constructor_elements)[0].કિંમત))
	constructor_zeroinit = 1;
      તોડો;
    મૂળભૂત:
      /* If the constructor has more than one element, it can't be { 0 }.  */
      constructor_zeroinit = 0;
      તોડો;
    }

  /* Warn when some structs are initialized with direct aggregation.  */
  જો (!implicit && found_missing_braces && warn_missing_braces
      && !constructor_zeroinit)
    {
      gcc_assert (initializer_ઢગલો->missing_brace_richloc);
      warning_at (initializer_ઢગલો->missing_brace_richloc,
		  OPT_Wmissing_braces,
		  "missing braces around initializer");
    }

  /* Warn when some struct elements are implicitly initialized to zero.  */
  જો (warn_missing_field_initializers
      && constructor_type
      && વૃક્ષ_CODE (constructor_type) == RECORD_TYPE
      && constructor_unfilled_fields)
    {
	/* Do not warn for flexible array members or zero-length arrays.  */
	જ્યારે (constructor_unfilled_fields
	       && (!DECL_SIZE (constructor_unfilled_fields)
		   || integer_zerop (DECL_SIZE (constructor_unfilled_fields))))
	  constructor_unfilled_fields = DECL_CHAIN (constructor_unfilled_fields);

	જો (constructor_unfilled_fields
	    /* Do not warn if this level of the initializer uses member
	       designators; it is likely to be deliberate.  */
	    && !constructor_designated
	    /* Do not warn about initializing with { 0 } or with { }.  */
	    && !constructor_zeroinit)
	  {
	    જો (warning_at (આગત_location, OPT_Wmissing_field_initializers,
			    "missing initializer for field %qD of %qT",
			    constructor_unfilled_fields,
			    constructor_type))
	      inform (DECL_SOURCE_LOCATION (constructor_unfilled_fields),
		      "%qD declared here", constructor_unfilled_fields);
	  }
    }

  /* Pad out the end of the structure.  */
  જો (p->replacement_કિંમત.કિંમત)
    /* If this closes a superfluous brace pair,
       just pass out the element between them.  */
    ret = p->replacement_કિંમત;
  નહીંતર જો (constructor_type == NULL_વૃક્ષ)
    ;
  નહીંતર જો (!RECORD_OR_UNION_TYPE_P (constructor_type)
	   && વૃક્ષ_CODE (constructor_type) != ARRAY_TYPE
	   && !gnu_vector_type_p (constructor_type))
    {
      /* A nonincremental scalar initializer--just return
	 the element, after verifying there is just one.
         Empty scalar initializers are supported in C23.  */
      જો (vec_safe_is_empty (constructor_elements))
	{
	  જો (constructor_erroneous || constructor_type == error_mark_ગાંઠ)
	    ret.કિંમત = error_mark_ગાંઠ;
	  નહીંતર જો (વૃક્ષ_CODE (constructor_type) == FUNCTION_TYPE)
	    {
	      error_init (loc, "invalid initializer");
	      ret.કિંમત = error_mark_ગાંઠ;
	    }
	  નહીંતર જો (વૃક્ષ_CODE (constructor_type) == POINTER_TYPE)
	    /* Ensure this is a null pointer constant in the case of a
	       'constexpr' object initialized with {}.  */
	    ret.કિંમત = build_zero_cst (ptr_type_ગાંઠ);
	  નહીંતર
	    ret.કિંમત = build_zero_cst (constructor_type);
	}
      નહીંતર જો (vec_safe_length (constructor_elements) != 1)
	{
	  error_init (loc, "extra elements in scalar initializer");
	  ret.કિંમત = (*constructor_elements)[0].કિંમત;
	}
      નહીંતર
	ret.કિંમત = (*constructor_elements)[0].કિંમત;
    }
  નહીંતર
    {
      જો (constructor_erroneous)
	ret.કિંમત = error_mark_ગાંઠ;
      નહીંતર
	{
	  ret.કિંમત = build_constructor (constructor_type,
					 constructor_elements);
	  જો (constructor_constant)
	    વૃક્ષ_CONSTANT (ret.કિંમત) = 1;
	  જો (constructor_constant && constructor_simple)
	    વૃક્ષ_STATIC (ret.કિંમત) = 1;
	  જો (constructor_nonconst)
	    CONSTRUCTOR_NON_CONST (ret.કિંમત) = 1;
	  જો (constructor_zero_padding_bits)
	    CONSTRUCTOR_ZERO_PADDING_BITS (ret.કિંમત) = 1;
	}
    }

  જો (ret.કિંમત && વૃક્ષ_CODE (ret.કિંમત) != CONSTRUCTOR)
    {
      જો (constructor_nonconst)
	ret.original_code = C_MAYBE_CONST_પદાવલિ;
      નહીંતર જો (ret.original_code == C_MAYBE_CONST_પદાવલિ)
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
  જો (!p->implicit)
    constructor_range_ઢગલો = p->range_ઢગલો;
  RESTORE_SPELLING_DEPTH (constructor_depth);

  constructor_ઢગલો = p->next;
  XDELETE (p);

  જો (ret.કિંમત == NULL_વૃક્ષ && constructor_ઢગલો == 0)
    ret.કિંમત = error_mark_ગાંઠ;
  પાછા ret;
}

/* Common handling for both array range and field name designators.
   ARRAY argument is nonzero for array ranges.  Returns false for success.  */

સ્થિર તાર્કિક
set_designator (location_t loc, તાર્કિક array,
		સંરચના obstack *braced_init_obstack)
{
  વૃક્ષ subtype;
  ગણના વૃક્ષ_code subcode;

  /* Don't die if an entire brace-pair level is superfluous
     in the containing level, or for an erroneous type.  */
  જો (constructor_type == NULL_વૃક્ષ || constructor_type == error_mark_ગાંઠ)
    પાછા સાચું;

  /* If there were errors in this designator list already, bail out
     silently.  */
  જો (designator_erroneous)
    પાછા સાચું;

  /* Likewise for an initializer for a variable-size type.  Those are
     diagnosed in the parser, except for empty initializer braces.  */
  જો (COMPLETE_TYPE_P (constructor_type)
      && વૃક્ષ_CODE (TYPE_SIZE (constructor_type)) != INTEGER_CST)
    પાછા સાચું;

  જો (!designator_depth)
    {
      gcc_assert (!constructor_range_ઢગલો);

      /* Designator list starts at the level of closest explicit
	 braces.  */
      જ્યારે (constructor_ઢગલો->implicit)
	process_init_element (આગત_location,
			      કાઢો_init_level (loc, 1, braced_init_obstack,
					      last_init_list_comma),
			      સાચું, braced_init_obstack);
      constructor_designated = 1;
      પાછા ખોટું;
    }

  પસંદગી (વૃક્ષ_CODE (constructor_type))
    {
    સ્થિતિ  RECORD_TYPE:
    સ્થિતિ  UNION_TYPE:
      subtype = વૃક્ષ_TYPE (constructor_fields);
      જો (subtype != error_mark_ગાંઠ)
	subtype = TYPE_MAIN_VARIANT (subtype);
      તોડો;
    સ્થિતિ ARRAY_TYPE:
      subtype = TYPE_MAIN_VARIANT (વૃક્ષ_TYPE (constructor_type));
      તોડો;
    મૂળભૂત:
      gcc_unreachable ();
    }

  subcode = વૃક્ષ_CODE (subtype);
  જો (array && subcode != ARRAY_TYPE)
    {
      error_init (loc, "array index in non-array initializer");
      પાછા સાચું;
    }
  નહીંતર જો (!array && subcode != RECORD_TYPE && subcode != UNION_TYPE)
    {
      error_init (loc, "field name not in record or union initializer");
      પાછા સાચું;
    }

  constructor_designated = 1;
  finish_implicit_inits (loc, braced_init_obstack);
  ધકેલો_init_level (loc, 2, braced_init_obstack);
  પાછા ખોટું;
}

/* If there are range designators in designator list, push a new designator
   to constructor_range_stack.  RANGE_END is end of such stack range or
   NULL_TREE if there is no range designator at this level.  */

સ્થિર શૂન્ય
ધકેલો_range_ઢગલો (વૃક્ષ range_end, સંરચના obstack * braced_init_obstack)
{
  સંરચના constructor_range_ઢગલો *p;

  p = (સંરચના constructor_range_ઢગલો *)
    obstack_alloc (braced_init_obstack,
		   કદ (સંરચના constructor_range_ઢગલો));
  p->prev = constructor_range_ઢગલો;
  p->next = 0;
  p->fields = constructor_fields;
  p->range_start = constructor_index;
  p->index = constructor_index;
  p->ઢગલો = constructor_ઢગલો;
  p->range_end = range_end;
  જો (constructor_range_ઢગલો)
    constructor_range_ઢગલો->next = p;
  constructor_range_ઢગલો = p;
}

/* Within an array initializer, specify the next index to be initialized.
   FIRST is that index.  If LAST is nonzero, then initialize a range
   of indices, running from FIRST through LAST.  */

શૂન્ય
set_init_index (location_t loc, વૃક્ષ first, વૃક્ષ last,
		સંરચના obstack *braced_init_obstack)
{
  જો (set_designator (loc, સાચું, braced_init_obstack))
    પાછા;

  designator_erroneous = 1;

  જો (!INTEGRAL_TYPE_P (વૃક્ષ_TYPE (first))
      || (last && !INTEGRAL_TYPE_P (વૃક્ષ_TYPE (last))))
    {
      error_init (loc, "array index in initializer not of integer type");
      પાછા;
    }

  જો (વૃક્ષ_CODE (first) != INTEGER_CST)
    {
      first = c_fully_fold (first, ખોટું, ખાલી);
      જો (વૃક્ષ_CODE (first) == INTEGER_CST)
	pedwarn_init (loc, OPT_Wpedantic,
		      "array index in initializer is not "
		      "an integer constant expression");
    }

  જો (last && વૃક્ષ_CODE (last) != INTEGER_CST)
    {
      last = c_fully_fold (last, ખોટું, ખાલી);
      જો (વૃક્ષ_CODE (last) == INTEGER_CST)
	pedwarn_init (loc, OPT_Wpedantic,
		      "array index in initializer is not "
		      "an integer constant expression");
    }

  જો (વૃક્ષ_CODE (first) != INTEGER_CST)
    error_init (loc, "nonconstant array index in initializer");
  નહીંતર જો (last != NULL_વૃક્ષ && વૃક્ષ_CODE (last) != INTEGER_CST)
    error_init (loc, "nonconstant array index in initializer");
  નહીંતર જો (વૃક્ષ_CODE (constructor_type) != ARRAY_TYPE)
    error_init (loc, "array index in non-array initializer");
  નહીંતર જો (વૃક્ષ_int_cst_sgn (first) == -1)
    error_init (loc, "array index in initializer exceeds array bounds");
  નહીંતર જો (constructor_max_index
	   && વૃક્ષ_int_cst_lt (constructor_max_index, first))
    error_init (loc, "array index in initializer exceeds array bounds");
  નહીંતર
    {
      constant_expression_warning (first);
      જો (last)
	constant_expression_warning (last);
      constructor_index = convert (bitsizetype, first);
      જો (વૃક્ષ_int_cst_lt (constructor_index, first))
	{
	  constructor_index = copy_ગાંઠ (constructor_index);
	  વૃક્ષ_OVERFLOW (constructor_index) = 1;
	}

      જો (last)
	{
	  જો (વૃક્ષ_int_cst_equal (first, last))
	    last = NULL_વૃક્ષ;
	  નહીંતર જો (વૃક્ષ_int_cst_lt (last, first))
	    {
	      error_init (loc, "empty index range in initializer");
	      last = NULL_વૃક્ષ;
	    }
	  નહીંતર
	    {
	      last = convert (bitsizetype, last);
	      જો (constructor_max_index != NULL_વૃક્ષ
		  && વૃક્ષ_int_cst_lt (constructor_max_index, last))
		{
		  error_init (loc, "array index range in initializer exceeds "
			      "array bounds");
		  last = NULL_વૃક્ષ;
		}
	    }
	}

      designator_depth++;
      designator_erroneous = 0;
      જો (constructor_range_ઢગલો || last)
	ધકેલો_range_ઢગલો (last, braced_init_obstack);
    }
}

/* Within a struct initializer, specify the next field to be initialized.  */

શૂન્ય
set_init_label (location_t loc, વૃક્ષ fieldname, location_t fieldname_loc,
		સંરચના obstack *braced_init_obstack)
{
  વૃક્ષ field;

  જો (set_designator (loc, ખોટું, braced_init_obstack))
    પાછા;

  designator_erroneous = 1;

  જો (!RECORD_OR_UNION_TYPE_P (constructor_type))
    {
      error_init (loc, "field name not in record or union initializer");
      પાછા;
    }

  field = lookup_field (constructor_type, fieldname);

  જો (field == NULL_વૃક્ષ)
    {
      વૃક્ષ guessed_id = lookup_field_fuzzy (constructor_type, fieldname);
      જો (guessed_id)
	{
	  gcc_rich_location rich_loc (fieldname_loc);
	  rich_loc.add_fixit_misspelled_id (fieldname_loc, guessed_id);
	  error_at (&rich_loc,
		    "%qT has no member named %qE; did you mean %qE?",
		    constructor_type, fieldname, guessed_id);
	}
      નહીંતર
	error_at (fieldname_loc, "%qT has no member named %qE",
		  constructor_type, fieldname);
    }
  નહીંતર
    કરો
      {
	constructor_fields = વૃક્ષ_કિંમત (field);
	designator_depth++;
	designator_erroneous = 0;
	જો (constructor_range_ઢગલો)
	  ધકેલો_range_ઢગલો (NULL_વૃક્ષ, braced_init_obstack);
	field = વૃક્ષ_CHAIN (field);
	જો (field)
	  {
	    જો (set_designator (loc, ખોટું, braced_init_obstack))
	      પાછા;
	  }
      }
    જ્યારે (field != NULL_વૃક્ષ);
}

/* Helper function for add_pending_init.  Find inorder successor of P
   in AVL tree.  */
સ્થિર સંરચના init_ગાંઠ *
init_ગાંઠ_successor (સંરચના init_ગાંઠ *p)
{
  સંરચના init_ગાંઠ *r;
  જો (p->જમણું)
    {
      r = p->જમણું;
      જ્યારે (r->ડાબું)
	r = r->ડાબું;
      પાછા r;
    }
  r = p->parent;
  જ્યારે (r && p == r->જમણું)
    {
      p = r;
      r = r->parent;
    }
  પાછા r;
}

/* Add a new initializer to the tree of pending initializers.  PURPOSE
   identifies the initializer, either array index or field in a structure.
   VALUE is the value of that index or field.  If ORIGTYPE is not
   NULL_TREE, it is the original type of VALUE.

   IMPLICIT is true if value comes from pop_init_level (1),
   the new initializer has been merged with the existing one
   and thus no warnings should be emitted about overriding an
   existing initializer.  */

સ્થિર શૂન્ય
add_pending_init (location_t loc, વૃક્ષ purpose, વૃક્ષ કિંમત, વૃક્ષ origtype,
		  તાર્કિક implicit, સંરચના obstack *braced_init_obstack)
{
  સંરચના init_ગાંઠ *p, **q, *r;

  q = &constructor_pending_elts;
  p = 0;

  જો (વૃક્ષ_CODE (constructor_type) == ARRAY_TYPE)
    {
      જ્યારે (*q != 0)
	{
	  p = *q;
	  જો (વૃક્ષ_int_cst_lt (purpose, p->purpose))
	    q = &p->ડાબું;
	  નહીંતર જો (વૃક્ષ_int_cst_lt (p->purpose, purpose))
	    {
	      જો (વૃક્ષ_CODE (p->કિંમત) != RAW_DATA_CST
		  || (p->જમણું
		      && વૃક્ષ_int_cst_le (p->જમણું->purpose, purpose)))
		q = &p->જમણું;
	      નહીંતર
		{
		  widest_int pp = wi::to_widest (p->purpose);
		  widest_int pw = wi::to_widest (purpose);
		  જો (pp + RAW_DATA_LENGTH (p->કિંમત) <= pw)
		    q = &p->જમણું;
		  નહીંતર
		    {
		      /* Override which should split the old RAW_DATA_CST
			 into 2 or 3 pieces.  */
		      જો (!implicit && warn_override_init)
			warning_init (loc, OPT_Woverride_init,
				      "initialized field overwritten");
		      unsigned HOST_WIDE_INT start = (pw - pp).to_uhwi ();
		      unsigned HOST_WIDE_INT len = 1;
		      જો (વૃક્ષ_CODE (કિંમત) == RAW_DATA_CST)
			len = RAW_DATA_LENGTH (કિંમત);
		      unsigned HOST_WIDE_INT end = 0;
		      unsigned plen = RAW_DATA_LENGTH (p->કિંમત);
		      gcc_checking_assert (start < plen && start);
		      જો (plen - start > len)
			end = plen - start - len;
		      વૃક્ષ v = p->કિંમત;
		      વૃક્ષ origtype = p->origtype;
		      જો (start == 1)
			p->કિંમત = build_int_cst (વૃક્ષ_TYPE (v),
						  RAW_DATA_UCHAR_ELT (v, 0));
		      નહીંતર
			{
			  p->કિંમત = v;
			  જો (end > 1)
			    v = copy_ગાંઠ (v);
			  RAW_DATA_LENGTH (p->કિંમત) = start;
			}
		      જો (end)
			{
			  વૃક્ષ epurpose
			    = size_binop (PLUS_પદાવલિ, purpose,
					  bitsize_int (len));
			  જો (end > 1)
			    {
			      RAW_DATA_LENGTH (v) -= plen - end;
			      RAW_DATA_POINTER (v) += plen - end;
			    }
			  નહીંતર
			    v = build_int_cst (વૃક્ષ_TYPE (v),
					       RAW_DATA_UCHAR_ELT (v, plen
								      - end));
			  add_pending_init (loc, epurpose, v, origtype,
					    implicit, braced_init_obstack);
			}
		      q = &constructor_pending_elts;
		      ચાલુ;
		    }
		}
	    }
	  નહીંતર
	    {
	      જો (વૃક્ષ_CODE (p->કિંમત) == RAW_DATA_CST
		  && (RAW_DATA_LENGTH (p->કિંમત)
		      > (વૃક્ષ_CODE (કિંમત) == RAW_DATA_CST
			 ? RAW_DATA_LENGTH (કિંમત) : 1)))
		{
		  /* Override which should split the old RAW_DATA_CST
		     into 2 pieces.  */
		  જો (!implicit && warn_override_init)
		    warning_init (loc, OPT_Woverride_init,
				  "initialized field overwritten");
		  unsigned HOST_WIDE_INT len = 1;
		  જો (વૃક્ષ_CODE (કિંમત) == RAW_DATA_CST)
		    len = RAW_DATA_LENGTH (કિંમત);
		  જો ((unsigned) RAW_DATA_LENGTH (p->કિંમત) > len + 1)
		    {
		      RAW_DATA_LENGTH (p->કિંમત) -= len;
		      RAW_DATA_POINTER (p->કિંમત) += len;
		    }
		  નહીંતર
		    {
		      unsigned પૂર્ણાંક l = RAW_DATA_LENGTH (p->કિંમત) - 1;
		      p->કિંમત
			= build_int_cst (વૃક્ષ_TYPE (p->કિંમત),
					 RAW_DATA_UCHAR_ELT (p->કિંમત, l));
		    }
		  p->purpose = size_binop (PLUS_પદાવલિ, p->purpose,
					   bitsize_int (len));
		  ચાલુ;
		}
	      જો (વૃક્ષ_CODE (કિંમત) == RAW_DATA_CST)
		{
		handle_raw_data:
		  /* RAW_DATA_CST value might overlap various further
		     prior initval entries.  Find out how many.  */
		  unsigned cnt = 0;
		  widest_int w
		    = wi::to_widest (purpose) + RAW_DATA_LENGTH (કિંમત);
		  સંરચના init_ગાંઠ *r = p, *last = ખાલી;
		  તાર્કિક override_init = warn_override_init;
		  જ્યારે ((r = init_ગાંઠ_successor (r))
			 && wi::to_widest (r->purpose) < w)
		    {
		      ++cnt;
		      જો (વૃક્ષ_SIDE_EFFECTS (r->કિંમત))
			warning_init (loc, OPT_Woverride_init_side_effects,
				      "initialized field with side-effects "
				      "overwritten");
		      નહીંતર જો (override_init)
			{
			  warning_init (loc, OPT_Woverride_init,
					"initialized field overwritten");
			  override_init = ખોટું;
			}
		      last = r;
		    }
		  જો (cnt)
		    {
		      જો (વૃક્ષ_CODE (last->કિંમત) == RAW_DATA_CST
			  && (wi::to_widest (last->purpose)
			      + RAW_DATA_LENGTH (last->કિંમત) > w))
			{
			  /* The last overlapping prior initval overlaps
			     only partially.  Shrink it and decrease cnt.  */
			  unsigned પૂર્ણાંક l = (wi::to_widest (last->purpose)
					    + RAW_DATA_LENGTH (last->કિંમત)
					    - w).to_uhwi ();
			  --cnt;
			  RAW_DATA_LENGTH (last->કિંમત) -= l;
			  RAW_DATA_POINTER (last->કિંમત) += l;
			  જો (RAW_DATA_LENGTH (last->કિંમત) == 1)
			    last->કિંમત
			      = build_int_cst (વૃક્ષ_TYPE (last->કિંમત),
					       RAW_DATA_UCHAR_ELT (last->કિંમત,
								   0));
			  last->purpose
			    = size_binop (PLUS_પદાવલિ, last->purpose,
					  bitsize_int (l));
			}
		      /* Instead of deleting cnt nodes from the AVL tree
			 and rebalancing, peel of last cnt bytes from the
			 RAW_DATA_CST.  Overriding thousands of previously
			 initialized array elements with #embed needs to work,
			 but doesn't need to be super efficient.  */
		      gcc_checking_assert ((unsigned) RAW_DATA_LENGTH (કિંમત)
					   > cnt);
		      RAW_DATA_LENGTH (કિંમત) -= cnt;
		      અચલ unsigned અક્ષર *s
			= &RAW_DATA_UCHAR_ELT (કિંમત, RAW_DATA_LENGTH (કિંમત));
		      unsigned પૂર્ણાંક o = RAW_DATA_LENGTH (કિંમત);
		      માટે (r = p; cnt--; ++o, ++s)
			{
			  r = init_ગાંઠ_successor (r);
			  r->purpose = size_binop (PLUS_પદાવલિ, purpose,
						   bitsize_int (o));
			  r->કિંમત = build_int_cst (વૃક્ષ_TYPE (કિંમત), *s);
			  r->origtype = origtype;
			}
		      જો (RAW_DATA_LENGTH (કિંમત) == 1)
			કિંમત = build_int_cst (વૃક્ષ_TYPE (કિંમત),
					       RAW_DATA_UCHAR_ELT (કિંમત, 0));
		    }
		}
	      જો (!implicit)
		{
		  જો (વૃક્ષ_SIDE_EFFECTS (p->કિંમત))
		    warning_init (loc, OPT_Woverride_init_side_effects,
				  "initialized field with side-effects "
				  "overwritten");
		  નહીંતર જો (warn_override_init)
		    warning_init (loc, OPT_Woverride_init,
				  "initialized field overwritten");
		}
	      p->કિંમત = કિંમત;
	      p->origtype = origtype;
	      પાછા;
	    }
	}
      જો (વૃક્ષ_CODE (કિંમત) == RAW_DATA_CST && p)
	{
	  સંરચના init_ગાંઠ *r;
	  જો (q == &p->ડાબું)
	    r = p;
	  નહીંતર
	    r = init_ગાંઠ_successor (p);
	  જો (r && wi::to_widest (r->purpose) < (wi::to_widest (purpose)
						 + RAW_DATA_LENGTH (કિંમત)))
	    {
	      /* Overlap with at least one prior initval in the range but
		 not at the start.  */
	      p = r;
	      p->purpose = purpose;
	      જાઓ handle_raw_data;
	    }
	}
    }
  નહીંતર
    {
      વૃક્ષ bitpos;

      bitpos = bit_position (purpose);
      જ્યારે (*q != ખાલી)
	{
	  p = *q;
	  જો (વૃક્ષ_int_cst_lt (bitpos, bit_position (p->purpose)))
	    q = &p->ડાબું;
	  નહીંતર જો (p->purpose != purpose)
	    q = &p->જમણું;
	  નહીંતર
	    {
	      જો (!implicit)
		{
		  જો (વૃક્ષ_SIDE_EFFECTS (p->કિંમત))
		    warning_init (loc, OPT_Woverride_init_side_effects,
				  "initialized field with side-effects "
				  "overwritten");
		  નહીંતર જો (warn_override_init)
		    warning_init (loc, OPT_Woverride_init,
				  "initialized field overwritten");
		}
	      p->કિંમત = કિંમત;
	      p->origtype = origtype;
	      પાછા;
	    }
	}
    }

  r = (સંરચના init_ગાંઠ *) obstack_alloc (braced_init_obstack,
					  કદ (સંરચના init_ગાંઠ));
  r->purpose = purpose;
  r->કિંમત = કિંમત;
  r->origtype = origtype;

  *q = r;
  r->parent = p;
  r->ડાબું = 0;
  r->જમણું = 0;
  r->balance = 0;

  જ્યારે (p)
    {
      સંરચના init_ગાંઠ *s;

      જો (r == p->ડાબું)
	{
	  જો (p->balance == 0)
	    p->balance = -1;
	  નહીંતર જો (p->balance < 0)
	    {
	      જો (r->balance < 0)
		{
		  /* L rotation.  */
		  p->ડાબું = r->જમણું;
		  જો (p->ડાબું)
		    p->ડાબું->parent = p;
		  r->જમણું = p;

		  p->balance = 0;
		  r->balance = 0;

		  s = p->parent;
		  p->parent = r;
		  r->parent = s;
		  જો (s)
		    {
		      જો (s->ડાબું == p)
			s->ડાબું = r;
		      નહીંતર
			s->જમણું = r;
		    }
		  નહીંતર
		    constructor_pending_elts = r;
		}
	      નહીંતર
		{
		  /* LR rotation.  */
		  સંરચના init_ગાંઠ *t = r->જમણું;

		  r->જમણું = t->ડાબું;
		  જો (r->જમણું)
		    r->જમણું->parent = r;
		  t->ડાબું = r;

		  p->ડાબું = t->જમણું;
		  જો (p->ડાબું)
		    p->ડાબું->parent = p;
		  t->જમણું = p;

		  p->balance = t->balance < 0;
		  r->balance = -(t->balance > 0);
		  t->balance = 0;

		  s = p->parent;
		  p->parent = t;
		  r->parent = t;
		  t->parent = s;
		  જો (s)
		    {
		      જો (s->ડાબું == p)
			s->ડાબું = t;
		      નહીંતર
			s->જમણું = t;
		    }
		  નહીંતર
		    constructor_pending_elts = t;
		}
	      તોડો;
	    }
	  નહીંતર
	    {
	      /* p->balance == +1; growth of left side balances the node.  */
	      p->balance = 0;
	      તોડો;
	    }
	}
      નહીંતર /* r == p->right */
	{
	  જો (p->balance == 0)
	    /* Growth propagation from right side.  */
	    p->balance++;
	  નહીંતર જો (p->balance > 0)
	    {
	      જો (r->balance > 0)
		{
		  /* R rotation.  */
		  p->જમણું = r->ડાબું;
		  જો (p->જમણું)
		    p->જમણું->parent = p;
		  r->ડાબું = p;

		  p->balance = 0;
		  r->balance = 0;

		  s = p->parent;
		  p->parent = r;
		  r->parent = s;
		  જો (s)
		    {
		      જો (s->ડાબું == p)
			s->ડાબું = r;
		      નહીંતર
			s->જમણું = r;
		    }
		  નહીંતર
		    constructor_pending_elts = r;
		}
	      નહીંતર /* r->balance == -1 */
		{
		  /* RL rotation */
		  સંરચના init_ગાંઠ *t = r->ડાબું;

		  r->ડાબું = t->જમણું;
		  જો (r->ડાબું)
		    r->ડાબું->parent = r;
		  t->જમણું = r;

		  p->જમણું = t->ડાબું;
		  જો (p->જમણું)
		    p->જમણું->parent = p;
		  t->ડાબું = p;

		  r->balance = (t->balance < 0);
		  p->balance = -(t->balance > 0);
		  t->balance = 0;

		  s = p->parent;
		  p->parent = t;
		  r->parent = t;
		  t->parent = s;
		  જો (s)
		    {
		      જો (s->ડાબું == p)
			s->ડાબું = t;
		      નહીંતર
			s->જમણું = t;
		    }
		  નહીંતર
		    constructor_pending_elts = t;
		}
	      તોડો;
	    }
	  નહીંતર
	    {
	      /* p->balance == -1; growth of right side balances the node.  */
	      p->balance = 0;
	      તોડો;
	    }
	}

      r = p;
      p = p->parent;
    }
}

/* Build AVL tree from a sorted chain.  */

સ્થિર શૂન્ય
set_nonincremental_init (સંરચના obstack * braced_init_obstack)
{
  unsigned HOST_WIDE_INT ix;
  વૃક્ષ index, કિંમત;

  જો (વૃક્ષ_CODE (constructor_type) != RECORD_TYPE
      && વૃક્ષ_CODE (constructor_type) != ARRAY_TYPE)
    પાછા;

  FOR_EACH_CONSTRUCTOR_ELT (constructor_elements, ix, index, કિંમત)
    add_pending_init (આગત_location, index, કિંમત, NULL_વૃક્ષ, સાચું,
		      braced_init_obstack);
  constructor_elements = ખાલી;
  જો (વૃક્ષ_CODE (constructor_type) == RECORD_TYPE)
    {
      constructor_unfilled_fields = TYPE_FIELDS (constructor_type);
      /* Skip any nameless bit fields at the beginning.  */
      જ્યારે (constructor_unfilled_fields != NULL_વૃક્ષ
	     && DECL_UNNAMED_BIT_FIELD (constructor_unfilled_fields))
	constructor_unfilled_fields = વૃક્ષ_CHAIN (constructor_unfilled_fields);

    }
  નહીંતર જો (વૃક્ષ_CODE (constructor_type) == ARRAY_TYPE)
    {
      જો (TYPE_DOMAIN (constructor_type))
	constructor_unfilled_index
	  = convert (bitsizetype,
		     TYPE_MIN_કિંમત (TYPE_DOMAIN (constructor_type)));
      નહીંતર
	constructor_unfilled_index = bitsize_zero_ગાંઠ;
    }
  constructor_incremental = 0;
}

/* Build AVL tree from a string constant.  */

સ્થિર શૂન્ય
set_nonincremental_init_from_string (વૃક્ષ str,
				     સંરચના obstack * braced_init_obstack)
{
  વૃક્ષ કિંમત, purpose, type;
  HOST_WIDE_INT val[2];
  અચલ અક્ષર *p, *end;
  પૂર્ણાંક byte, wchar_bytes, charwidth, bitpos;

  gcc_assert (વૃક્ષ_CODE (constructor_type) == ARRAY_TYPE);

  wchar_bytes = TYPE_PRECISION (વૃક્ષ_TYPE (વૃક્ષ_TYPE (str))) / BITS_PER_UNIT;
  charwidth = TYPE_PRECISION (char_type_ગાંઠ);
  gcc_assert ((size_t) wchar_bytes * charwidth
	      <= ARRAY_SIZE (val) * HOST_BITS_PER_WIDE_INT);
  type = વૃક્ષ_TYPE (constructor_type);
  p = વૃક્ષ_STRING_POINTER (str);
  end = p + વૃક્ષ_STRING_LENGTH (str);

  માટે (purpose = bitsize_zero_ગાંઠ;
       p < end
       && !(constructor_max_index
	    && વૃક્ષ_int_cst_lt (constructor_max_index, purpose));
       purpose = size_binop (PLUS_પદાવલિ, purpose, bitsize_one_ગાંઠ))
    {
      જો (wchar_bytes == 1)
	{
	  val[0] = (unsigned અક્ષર) *p++;
	  val[1] = 0;
	}
      નહીંતર
	{
	  val[1] = 0;
	  val[0] = 0;
	  માટે (byte = 0; byte < wchar_bytes; byte++)
	    {
	      જો (BYTES_BIG_ENDIAN)
		bitpos = (wchar_bytes - byte - 1) * charwidth;
	      નહીંતર
		bitpos = byte * charwidth;
	      val[bitpos / HOST_BITS_PER_WIDE_INT]
		|= ((unsigned HOST_WIDE_INT) ((unsigned અક્ષર) *p++))
		   << (bitpos % HOST_BITS_PER_WIDE_INT);
	    }
	}

      જો (!TYPE_UNSIGNED (type))
	{
	  bitpos = ((wchar_bytes - 1) * charwidth) + HOST_BITS_PER_CHAR;
	  જો (bitpos < HOST_BITS_PER_WIDE_INT)
	    {
	      જો (val[0] & (HOST_WIDE_INT_1 << (bitpos - 1)))
		{
		  val[0] |= HOST_WIDE_INT_M1U << bitpos;
		  val[1] = -1;
		}
	    }
	  નહીંતર જો (bitpos == HOST_BITS_PER_WIDE_INT)
	    {
	      જો (val[0] < 0)
		val[1] = -1;
	    }
	  નહીંતર જો (val[1] & (HOST_WIDE_INT_1
			     << (bitpos - 1 - HOST_BITS_PER_WIDE_INT)))
	    val[1] |= HOST_WIDE_INT_M1U << (bitpos - HOST_BITS_PER_WIDE_INT);
	}

      કિંમત = wide_int_to_વૃક્ષ (type,
				wide_int::from_array (val, 2,
						      HOST_BITS_PER_WIDE_INT * 2));
      add_pending_init (આગત_location, purpose, કિંમત, NULL_વૃક્ષ, સાચું,
                        braced_init_obstack);
    }

  constructor_incremental = 0;
}

/* Return value of FIELD in pending initializer or NULL_TREE if the field was
   not initialized yet.  */

સ્થિર વૃક્ષ
find_init_member (વૃક્ષ field, સંરચના obstack * braced_init_obstack)
{
  સંરચના init_ગાંઠ *p;

  જો (વૃક્ષ_CODE (constructor_type) == ARRAY_TYPE)
    {
      જો (constructor_incremental
	  && વૃક્ષ_int_cst_lt (field, constructor_unfilled_index))
	set_nonincremental_init (braced_init_obstack);

      p = constructor_pending_elts;
      જ્યારે (p)
	{
	  જો (વૃક્ષ_int_cst_lt (field, p->purpose))
	    p = p->ડાબું;
	  નહીંતર જો (વૃક્ષ_int_cst_lt (p->purpose, field))
	    p = p->જમણું;
	  નહીંતર
	    પાછા p->કિંમત;
	}
    }
  નહીંતર જો (વૃક્ષ_CODE (constructor_type) == RECORD_TYPE)
    {
      વૃક્ષ bitpos = bit_position (field);

      જો (constructor_incremental
	  && (!constructor_unfilled_fields
	      || વૃક્ષ_int_cst_lt (bitpos,
				  bit_position (constructor_unfilled_fields))))
	set_nonincremental_init (braced_init_obstack);

      p = constructor_pending_elts;
      જ્યારે (p)
	{
	  જો (field == p->purpose)
	    પાછા p->કિંમત;
	  નહીંતર જો (વૃક્ષ_int_cst_lt (bitpos, bit_position (p->purpose)))
	    p = p->ડાબું;
	  નહીંતર
	    p = p->જમણું;
	}
    }
  નહીંતર જો (વૃક્ષ_CODE (constructor_type) == UNION_TYPE)
    {
      જો (!vec_safe_is_empty (constructor_elements)
	  && (constructor_elements->last ().index == field))
	પાછા constructor_elements->last ().કિંમત;
    }
  પાછા NULL_વૃક્ષ;
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

સ્થિર શૂન્ય
output_init_element (location_t loc, વૃક્ષ કિંમત, વૃક્ષ origtype,
		     તાર્કિક strict_string, વૃક્ષ type, વૃક્ષ field, તાર્કિક pending,
		     તાર્કિક implicit, સંરચના obstack * braced_init_obstack)
{
  વૃક્ષ semantic_type = NULL_વૃક્ષ;
  તાર્કિક maybe_const = સાચું;
  તાર્કિક npc, int_const_પદાવલિ, arith_const_પદાવલિ;

  જો (type == error_mark_ગાંઠ || કિંમત == error_mark_ગાંઠ)
    {
      constructor_erroneous = 1;
      પાછા;
    }
  જો (વૃક્ષ_CODE (વૃક્ષ_TYPE (કિંમત)) == ARRAY_TYPE
      && (વૃક્ષ_CODE (કિંમત) == STRING_CST
	  || વૃક્ષ_CODE (કિંમત) == COMPOUND_LITERAL_પદાવલિ)
      && !(વૃક્ષ_CODE (કિંમત) == STRING_CST
	   && વૃક્ષ_CODE (type) == ARRAY_TYPE
	   && INTEGRAL_TYPE_P (વૃક્ષ_TYPE (type)))
      && !comptypes (TYPE_MAIN_VARIANT (વૃક્ષ_TYPE (કિંમત)),
		     TYPE_MAIN_VARIANT (type)))
    કિંમત = array_to_pointer_conversion (આગત_location, કિંમત);

  જો (વૃક્ષ_CODE (કિંમત) == COMPOUND_LITERAL_પદાવલિ
      && require_constant_કિંમત && pending)
    {
      /* As an extension, allow initializing objects with static storage
	 duration with compound literals (which are then treated just as
	 the brace enclosed list they contain).  */
      જો (flag_isoc99)
	pedwarn_init (loc, OPT_Wpedantic, "initializer element is not "
		      "constant");
      વૃક્ષ decl = COMPOUND_LITERAL_પદાવલિ_DECL (કિંમત);
      કિંમત = DECL_INITIAL (decl);
    }

  npc = null_pointer_constant_p (કિંમત);
  int_const_પદાવલિ = (વૃક્ષ_CODE (કિંમત) == INTEGER_CST
		    && !વૃક્ષ_OVERFLOW (કિંમત)
		    && INTEGRAL_TYPE_P (વૃક્ષ_TYPE (કિંમત)));
  /* Not fully determined before folding.  */
  arith_const_પદાવલિ = સાચું;
  જો (વૃક્ષ_CODE (કિંમત) == EXCESS_PRECISION_પદાવલિ)
    {
      semantic_type = વૃક્ષ_TYPE (કિંમત);
      કિંમત = વૃક્ષ_OPERAND (કિંમત, 0);
    }
  કિંમત = c_fully_fold (કિંમત, require_constant_કિંમત, &maybe_const);
  /* TODO: this may not detect all cases of expressions folding to
     constants that are not arithmetic constant expressions.  */
  જો (!maybe_const)
    arith_const_પદાવલિ = ખોટું;
  નહીંતર જો (!INTEGRAL_TYPE_P (વૃક્ષ_TYPE (કિંમત))
	   && વૃક્ષ_CODE (વૃક્ષ_TYPE (કિંમત)) != REAL_TYPE
	   && વૃક્ષ_CODE (વૃક્ષ_TYPE (કિંમત)) != COMPLEX_TYPE)
    arith_const_પદાવલિ = ખોટું;
  નહીંતર જો (વૃક્ષ_CODE (કિંમત) != INTEGER_CST
	   && વૃક્ષ_CODE (કિંમત) != REAL_CST
	   && વૃક્ષ_CODE (કિંમત) != COMPLEX_CST
	   && વૃક્ષ_CODE (કિંમત) != RAW_DATA_CST)
    arith_const_પદાવલિ = ખોટું;
  નહીંતર જો (વૃક્ષ_OVERFLOW (કિંમત))
    arith_const_પદાવલિ = ખોટું;

  જો (કિંમત == error_mark_ગાંઠ)
    constructor_erroneous = 1;
  નહીંતર જો (!વૃક્ષ_CONSTANT (કિંમત))
    constructor_constant = 0;
  નહીંતર જો (!initializer_constant_valid_p (કિંમત,
					  વૃક્ષ_TYPE (કિંમત),
					  AGGREGATE_TYPE_P (constructor_type)
					  && TYPE_REVERSE_STORAGE_ORDER
					     (constructor_type))
	   || (RECORD_OR_UNION_TYPE_P (constructor_type)
	       && DECL_C_BIT_FIELD (field)
	       && વૃક્ષ_CODE (કિંમત) != INTEGER_CST))
    constructor_simple = 0;
  જો (!maybe_const)
    constructor_nonconst = 1;

  /* Digest the initializer and issue any errors about incompatible
     types before issuing errors about non-constant initializers.  */
  વૃક્ષ new_કિંમત = કિંમત;
  જો (semantic_type)
    new_કિંમત = build1 (EXCESS_PRECISION_પદાવલિ, semantic_type, કિંમત);
  /* In the case of braces around a scalar initializer, the result of
     this initializer processing goes through digest_init again at the
     outer level.  In the case of a constexpr initializer for a
     pointer, avoid converting a null pointer constant to something
     that is not a null pointer constant to avoid a spurious error
     from that second processing.  */
  જો (!require_constexpr_કિંમત
      || !npc
      || વૃક્ષ_CODE (constructor_type) != POINTER_TYPE)
    new_કિંમત = digest_init (loc,
			     RECORD_OR_UNION_TYPE_P (constructor_type)
			     ? field : constructor_fields
			     ? constructor_fields : constructor_decl,
			     type, new_કિંમત, origtype, npc,
			     int_const_પદાવલિ, arith_const_પદાવલિ, strict_string,
			     require_constant_કિંમત, require_constexpr_કિંમત);
  જો (new_કિંમત == error_mark_ગાંઠ)
    {
      constructor_erroneous = 1;
      પાછા;
    }
  જો (require_constant_કિંમત || require_constant_elements)
    constant_expression_warning (new_કિંમત);

  /* Proceed to check the constness of the original initializer.  */
  જો (!initializer_constant_valid_p (કિંમત, વૃક્ષ_TYPE (કિંમત)))
    {
      જો (require_constant_કિંમત)
	{
	  error_init (loc, "initializer element is not constant");
	  કિંમત = error_mark_ગાંઠ;
	}
      નહીંતર જો (require_constant_elements)
	pedwarn (loc, OPT_Wpedantic,
		 "initializer element is not computable at load time");
    }
  નહીંતર જો (!maybe_const
	   && (require_constant_કિંમત || require_constant_elements))
    pedwarn_init (loc, OPT_Wpedantic,
		  "initializer element is not a constant expression");
  /* digest_init has already carried out the additional checks
     required for 'constexpr' initializers (using the information
     passed to it about whether the original initializer was certain
     kinds of constant expression), so that check does not need to be
     repeated here.  */

  /* Issue -Wc++-compat warnings about initializing a bitfield with
     enum type.  */
  જો (warn_cxx_compat
      && field != NULL_વૃક્ષ
      && વૃક્ષ_CODE (field) == FIELD_DECL
      && DECL_BIT_FIELD_TYPE (field) != NULL_વૃક્ષ
      && (TYPE_MAIN_VARIANT (DECL_BIT_FIELD_TYPE (field))
	  != TYPE_MAIN_VARIANT (type))
      && વૃક્ષ_CODE (DECL_BIT_FIELD_TYPE (field)) == ENUMERAL_TYPE)
    {
      વૃક્ષ checktype = origtype != NULL_વૃક્ષ ? origtype : વૃક્ષ_TYPE (કિંમત);
      જો (checktype != error_mark_ગાંઠ
	  && (TYPE_MAIN_VARIANT (checktype)
	      != TYPE_MAIN_VARIANT (DECL_BIT_FIELD_TYPE (field))))
	warning_init (loc, OPT_Wc___compat,
		      "enum conversion in initialization is invalid in C++");
    }

  /* If this field is empty and does not have side effects (and is not at
     the end of structure), don't do anything other than checking the
     initializer.  */
  જો (field
      && (વૃક્ષ_TYPE (field) == error_mark_ગાંઠ
	  || (COMPLETE_TYPE_P (વૃક્ષ_TYPE (field))
	      && integer_zerop (TYPE_SIZE (વૃક્ષ_TYPE (field)))
	      && !વૃક્ષ_SIDE_EFFECTS (new_કિંમત)
	      && (વૃક્ષ_CODE (constructor_type) == ARRAY_TYPE
		  || DECL_CHAIN (field)))))
    પાછા;

  /* Finally, set VALUE to the initializer value digested above.  */
  કિંમત = new_કિંમત;

  /* If this element doesn't come next in sequence,
     put it on constructor_pending_elts.  */
  જો (વૃક્ષ_CODE (constructor_type) == ARRAY_TYPE
      && (!constructor_incremental
	  || !વૃક્ષ_int_cst_equal (field, constructor_unfilled_index)
	  || (વૃક્ષ_CODE (કિંમત) == RAW_DATA_CST
	      && constructor_pending_elts
	      && pending)))
    {
      જો (constructor_incremental
	  && (વૃક્ષ_int_cst_lt (field, constructor_unfilled_index)
	      || (વૃક્ષ_CODE (કિંમત) == RAW_DATA_CST
		  && constructor_pending_elts
		  && pending)))
	set_nonincremental_init (braced_init_obstack);

      add_pending_init (loc, field, કિંમત, origtype, implicit,
			braced_init_obstack);
      પાછા;
    }
  નહીંતર જો (વૃક્ષ_CODE (constructor_type) == RECORD_TYPE
	   && (!constructor_incremental
	       || field != constructor_unfilled_fields))
    {
      /* We do this for records but not for unions.  In a union,
	 no matter which field is specified, it can be initialized
	 right away since it starts at the beginning of the union.  */
      જો (constructor_incremental)
	{
	  જો (!constructor_unfilled_fields)
	    set_nonincremental_init (braced_init_obstack);
	  નહીંતર
	    {
	      વૃક્ષ bitpos, unfillpos;

	      bitpos = bit_position (field);
	      unfillpos = bit_position (constructor_unfilled_fields);

	      જો (વૃક્ષ_int_cst_lt (bitpos, unfillpos))
		set_nonincremental_init (braced_init_obstack);
	    }
	}

      add_pending_init (loc, field, કિંમત, origtype, implicit,
			braced_init_obstack);
      પાછા;
    }
  નહીંતર જો (વૃક્ષ_CODE (constructor_type) == UNION_TYPE
	   && !vec_safe_is_empty (constructor_elements))
    {
      જો (!implicit)
	{
	  જો (વૃક્ષ_SIDE_EFFECTS (constructor_elements->last ().કિંમત))
	    warning_init (loc, OPT_Woverride_init_side_effects,
			  "initialized field with side-effects overwritten");
	  નહીંતર જો (warn_override_init)
	    warning_init (loc, OPT_Woverride_init,
			  "initialized field overwritten");
	}

      /* We can have just one union field set.  */
      constructor_elements = ખાલી;
    }

  /* Otherwise, output this element either to
     constructor_elements or to the assembler file.  */

  constructor_elt celt = {field, કિંમત};
  vec_safe_ધકેલો (constructor_elements, celt);

  /* Advance the variable that indicates sequential elements output.  */
  જો (વૃક્ષ_CODE (constructor_type) == ARRAY_TYPE)
    {
      વૃક્ષ inc = bitsize_one_ગાંઠ;
      જો (કિંમત && વૃક્ષ_CODE (કિંમત) == RAW_DATA_CST)
	inc = bitsize_int (RAW_DATA_LENGTH (કિંમત));
      constructor_unfilled_index
	= size_binop_loc (આગત_location, PLUS_પદાવલિ,
			  constructor_unfilled_index, inc);
    }
  નહીંતર જો (વૃક્ષ_CODE (constructor_type) == RECORD_TYPE)
    {
      constructor_unfilled_fields
	= DECL_CHAIN (constructor_unfilled_fields);

      /* Skip any nameless bit fields.  */
      જ્યારે (constructor_unfilled_fields != NULL_વૃક્ષ
	     && DECL_UNNAMED_BIT_FIELD (constructor_unfilled_fields))
	constructor_unfilled_fields
	  = DECL_CHAIN (constructor_unfilled_fields);
    }
  નહીંતર જો (વૃક્ષ_CODE (constructor_type) == UNION_TYPE)
    constructor_unfilled_fields = NULL_વૃક્ષ;

  /* Now output any pending elements which have become next.  */
  જો (pending)
    output_pending_init_elements (0, braced_init_obstack);
}

/* For two FIELD_DECLs in the same chain, return -1 if field1
   comes before field2, 1 if field1 comes after field2 and
   0 if field1 == field2.  */

સ્થિર પૂર્ણાંક
init_field_decl_cmp (વૃક્ષ field1, વૃક્ષ field2)
{
  જો (field1 == field2)
    પાછા 0;

  વૃક્ષ bitpos1 = bit_position (field1);
  વૃક્ષ bitpos2 = bit_position (field2);
  જો (વૃક્ષ_int_cst_equal (bitpos1, bitpos2))
    {
      /* If one of the fields has non-zero bitsize, then that
	 field must be the last one in a sequence of zero
	 sized fields, fields after it will have bigger
	 bit_position.  */
      જો (વૃક્ષ_TYPE (field1) != error_mark_ગાંઠ
	  && COMPLETE_TYPE_P (વૃક્ષ_TYPE (field1))
	  && integer_nonzerop (વૃક્ષ_TYPE (field1)))
	પાછા 1;
      જો (વૃક્ષ_TYPE (field2) != error_mark_ગાંઠ
	  && COMPLETE_TYPE_P (વૃક્ષ_TYPE (field2))
	  && integer_nonzerop (વૃક્ષ_TYPE (field2)))
	પાછા -1;
      /* Otherwise, fallback to DECL_CHAIN walk to find out
	 which field comes earlier.  Walk chains of both
	 fields, so that if field1 and field2 are close to each
	 other in either order, it is found soon even for large
	 sequences of zero sized fields.  */
      વૃક્ષ f1 = field1, f2 = field2;
      જ્યારે (1)
	{
	  f1 = DECL_CHAIN (f1);
	  f2 = DECL_CHAIN (f2);
	  જો (f1 == NULL_વૃક્ષ)
	    {
	      gcc_assert (f2);
	      પાછા 1;
	    }
	  જો (f2 == NULL_વૃક્ષ)
	    પાછા -1;
	  જો (f1 == field2)
	    પાછા -1;
	  જો (f2 == field1)
	    પાછા 1;
	  જો (!વૃક્ષ_int_cst_equal (bit_position (f1), bitpos1))
	    પાછા 1;
	  જો (!વૃક્ષ_int_cst_equal (bit_position (f2), bitpos1))
	    પાછા -1;
	}
    }
  નહીંતર જો (વૃક્ષ_int_cst_lt (bitpos1, bitpos2))
    પાછા -1;
  નહીંતર
    પાછા 1;
}

/* Output any pending elements which have become next.
   As we output elements, constructor_unfilled_{fields,index}
   advances, which may cause other elements to become next;
   if so, they too are output.

   If ALL is 0, we return when there are
   no more pending elements to output now.

   If ALL is 1, we output space as necessary so that
   we can output all the pending elements.  */
સ્થિર શૂન્ય
output_pending_init_elements (પૂર્ણાંક all, સંરચના obstack * braced_init_obstack)
{
  સંરચના init_ગાંઠ *elt = constructor_pending_elts;
  વૃક્ષ next;

 retry:

  /* Look through the whole pending tree.
     If we find an element that should be output now,
     output it.  Otherwise, set NEXT to the element
     that comes first among those still pending.  */

  next = NULL_વૃક્ષ;
  જ્યારે (elt)
    {
      જો (વૃક્ષ_CODE (constructor_type) == ARRAY_TYPE)
	{
	  જો (વૃક્ષ_int_cst_equal (elt->purpose,
				  constructor_unfilled_index))
	    output_init_element (આગત_location, elt->કિંમત, elt->origtype,
				 સાચું, વૃક્ષ_TYPE (constructor_type),
				 constructor_unfilled_index, ખોટું, ખોટું,
				 braced_init_obstack);
	  નહીંતર જો (વૃક્ષ_int_cst_lt (constructor_unfilled_index,
				    elt->purpose))
	    {
	      /* Advance to the next smaller node.  */
	      જો (elt->ડાબું)
		elt = elt->ડાબું;
	      નહીંતર
		{
		  /* We have reached the smallest node bigger than the
		     current unfilled index.  Fill the space first.  */
		  next = elt->purpose;
		  તોડો;
		}
	    }
	  નહીંતર
	    {
	      /* Advance to the next bigger node.  */
	      જો (elt->જમણું)
		elt = elt->જમણું;
	      નહીંતર
		{
		  /* We have reached the biggest node in a subtree.  Find
		     the parent of it, which is the next bigger node.  */
		  જ્યારે (elt->parent && elt->parent->જમણું == elt)
		    elt = elt->parent;
		  elt = elt->parent;
		  જો (elt && વૃક્ષ_int_cst_lt (constructor_unfilled_index,
					      elt->purpose))
		    {
		      next = elt->purpose;
		      તોડો;
		    }
		}
	    }
	}
      નહીંતર જો (RECORD_OR_UNION_TYPE_P (constructor_type))
	{
	  /* If the current record is complete we are done.  */
	  જો (constructor_unfilled_fields == NULL_વૃક્ષ)
	    તોડો;

	  પૂર્ણાંક cmp = init_field_decl_cmp (constructor_unfilled_fields,
					 elt->purpose);
	  જો (cmp == 0)
	    output_init_element (આગત_location, elt->કિંમત, elt->origtype,
				 સાચું, વૃક્ષ_TYPE (elt->purpose),
				 elt->purpose, ખોટું, ખોટું,
				 braced_init_obstack);
	  નહીંતર જો (cmp < 0)
	    {
	      /* Advance to the next smaller node.  */
	      જો (elt->ડાબું)
		elt = elt->ડાબું;
	      નહીંતર
		{
		  /* We have reached the smallest node bigger than the
		     current unfilled field.  Fill the space first.  */
		  next = elt->purpose;
		  તોડો;
		}
	    }
	  નહીંતર
	    {
	      /* Advance to the next bigger node.  */
	      જો (elt->જમણું)
		elt = elt->જમણું;
	      નહીંતર
		{
		  /* We have reached the biggest node in a subtree.  Find
		     the parent of it, which is the next bigger node.  */
		  જ્યારે (elt->parent && elt->parent->જમણું == elt)
		    elt = elt->parent;
		  elt = elt->parent;
		  જો (elt
		      && init_field_decl_cmp (constructor_unfilled_fields,
					      elt->purpose) < 0)
		    {
		      next = elt->purpose;
		      તોડો;
		    }
		}
	    }
	}
    }

  /* Ordinarily return, but not if we want to output all
     and there are elements left.  */
  જો (!(all && next != NULL_વૃક્ષ))
    પાછા;

  /* If it's not incremental, just skip over the gap, so that after
     jumping to retry we will output the next successive element.  */
  જો (RECORD_OR_UNION_TYPE_P (constructor_type))
    constructor_unfilled_fields = next;
  નહીંતર જો (વૃક્ષ_CODE (constructor_type) == ARRAY_TYPE)
    constructor_unfilled_index = next;

  /* ELT now points to the node in the pending tree with the next
     initializer to output.  */
  જાઓ retry;
}

/* Expression VALUE coincides with the start of type TYPE in a braced
   initializer.  Return true if we should treat VALUE as initializing
   the first element of TYPE, false if we should treat it as initializing
   TYPE as a whole.

   If the initializer is clearly invalid, the question becomes:
   which choice gives the best error message?  */

સ્થિર તાર્કિક
initialize_elementwise_p (વૃક્ષ type, વૃક્ષ કિંમત)
{
  જો (type == error_mark_ગાંઠ || કિંમત == error_mark_ગાંઠ)
    પાછા ખોટું;

  gcc_checking_assert (TYPE_MAIN_VARIANT (type) == type);

  વૃક્ષ કિંમત_type = વૃક્ષ_TYPE (કિંમત);
  જો (કિંમત_type == error_mark_ગાંઠ)
    પાછા ખોટું;

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
  જો (gnu_vector_type_p (type))
    પાછા !VECTOR_TYPE_P (કિંમત_type);

  જો (AGGREGATE_TYPE_P (type))
    પાછા !comptypes (type, TYPE_MAIN_VARIANT (કિંમત_type));

  પાછા ખોટું;
}

/* Helper function for process_init_element.  Split first element of
   RAW_DATA_CST and save the rest to *RAW_DATA.  */

સ્થિર અંતઃરેખ વૃક્ષ
maybe_split_raw_data (વૃક્ષ કિંમત, વૃક્ષ *raw_data)
{
  જો (કિંમત == NULL_વૃક્ષ || વૃક્ષ_CODE (કિંમત) != RAW_DATA_CST)
    પાછા કિંમત;
  *raw_data = કિંમત;
  કિંમત = build_int_cst (integer_type_ગાંઠ,
			 RAW_DATA_UCHAR_ELT (*raw_data, 0));
  ++RAW_DATA_POINTER (*raw_data);
  --RAW_DATA_LENGTH (*raw_data);
  પાછા કિંમત;
}

/* Return non-zero if c_parser_initval should attempt to optimize
   large initializers into RAW_DATA_CST.  In that case return how
   many elements to optimize at most.  */

unsigned
c_maybe_optimize_large_byte_initializer (શૂન્ય)
{
  જો (!constructor_type
      || વૃક્ષ_CODE (constructor_type) != ARRAY_TYPE
      || constructor_ઢગલો->implicit)
    પાછા 0;
  વૃક્ષ elttype = TYPE_MAIN_VARIANT (વૃક્ષ_TYPE (constructor_type));
  જો (વૃક્ષ_CODE (elttype) != INTEGER_TYPE
      && વૃક્ષ_CODE (elttype) != BITINT_TYPE)
    પાછા 0;
  જો (TYPE_PRECISION (elttype) != CHAR_BIT
      || constructor_ઢગલો->replacement_કિંમત.કિંમત
      || (COMPLETE_TYPE_P (constructor_type)
	  && !poly_int_વૃક્ષ_p (TYPE_SIZE (constructor_type)))
      || constructor_range_ઢગલો)
    પાછા 0;
  જો (constructor_max_index == NULL_વૃક્ષ)
    પાછા INT_MAX;
  જો (વૃક્ષ_int_cst_le (constructor_max_index, constructor_index)
      || integer_all_onesp (constructor_max_index))
    પાછા 0;
  widest_int w = wi::to_widest (constructor_max_index);
  w -= wi::to_widest (constructor_index);
  w += 1;
  જો (w < 64)
    પાછા 0;
  જો (w > INT_MAX)
    પાછા INT_MAX;
  પાછા w.to_uhwi ();
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

શૂન્ય
process_init_element (location_t loc, સંરચના c_પદાવલિ કિંમત, તાર્કિક implicit,
		      સંરચના obstack * braced_init_obstack)
{
  વૃક્ષ orig_કિંમત = કિંમત.કિંમત;
  પૂર્ણાંક string_flag
    = (orig_કિંમત != NULL_વૃક્ષ && વૃક્ષ_CODE (orig_કિંમત) == STRING_CST);
  તાર્કિક strict_string = કિંમત.original_code == STRING_CST;
  તાર્કિક was_designated = designator_depth != 0;
  વૃક્ષ raw_data = NULL_વૃક્ષ;

retry:
  designator_depth = 0;
  designator_erroneous = 0;

  જો (!implicit && કિંમત.કિંમત && !integer_zerop (કિંમત.કિંમત))
    constructor_zeroinit = 0;

  /* Handle superfluous braces around string cst as in
     char x[] = {"foo"}; */
  જો (constructor_type
      && !was_designated
      && વૃક્ષ_CODE (constructor_type) == ARRAY_TYPE
      && INTEGRAL_TYPE_P (વૃક્ષ_TYPE (constructor_type))
      && integer_zerop (constructor_unfilled_index))
    {
      જો (constructor_ઢગલો->replacement_કિંમત.કિંમત)
	{
	  error_init (loc, "excess elements in %qT initializer", constructor_type);
	  પાછા;
	}
      નહીંતર જો (string_flag)
	{
	  constructor_ઢગલો->replacement_કિંમત = કિંમત;
	  પાછા;
	}
    }

  જો (constructor_ઢગલો->replacement_કિંમત.કિંમત != NULL_વૃક્ષ)
    {
      error_init (loc, "excess elements in struct initializer");
      પાછા;
    }

  /* Ignore elements of a brace group if it is entirely superfluous
     and has already been diagnosed, or if the type is erroneous.  */
  જો (constructor_type == NULL_વૃક્ષ || constructor_type == error_mark_ગાંઠ)
    પાછા;

  /* Ignore elements of an initializer for a variable-size type.
     Those are diagnosed in the parser (empty initializer braces are OK).  */
  જો (COMPLETE_TYPE_P (constructor_type)
      && !poly_int_વૃક્ષ_p (TYPE_SIZE (constructor_type)))
    પાછા;

  જો (!implicit && warn_designated_init && !was_designated
      && વૃક્ષ_CODE (constructor_type) == RECORD_TYPE
      && lookup_attribute ("designated_init",
			   TYPE_ATTRIBUTES (constructor_type)))
    warning_init (loc,
		  OPT_Wdesignated_init,
		  "positional initialization of field "
		  "in %<struct%> declared with %<designated_init%> attribute");

  /* If we've exhausted any levels that didn't have braces,
     pop them now.  */
  જ્યારે (constructor_ઢગલો->implicit)
    {
      જો (RECORD_OR_UNION_TYPE_P (constructor_type)
	  && constructor_fields == NULL_વૃક્ષ)
	process_init_element (loc,
			      કાઢો_init_level (loc, 1, braced_init_obstack,
					      last_init_list_comma),
			      સાચું, braced_init_obstack);
      નહીંતર જો ((વૃક્ષ_CODE (constructor_type) == ARRAY_TYPE
		|| gnu_vector_type_p (constructor_type))
	       && constructor_max_index
	       && વૃક્ષ_int_cst_lt (constructor_max_index,
				   constructor_index))
	process_init_element (loc,
			      કાઢો_init_level (loc, 1, braced_init_obstack,
					      last_init_list_comma),
			      સાચું, braced_init_obstack);
      નહીંતર
	તોડો;
    }

  /* In the case of [LO ... HI] = VALUE, only evaluate VALUE once.  */
  જો (constructor_range_ઢગલો)
    {
      /* If value is a compound literal and we'll be just using its
	 content, don't put it into a SAVE_EXPR.  */
      જો (વૃક્ષ_CODE (કિંમત.કિંમત) != COMPOUND_LITERAL_પદાવલિ
	  || !require_constant_કિંમત)
	{
	  વૃક્ષ semantic_type = NULL_વૃક્ષ;
	  જો (વૃક્ષ_CODE (કિંમત.કિંમત) == EXCESS_PRECISION_પદાવલિ)
	    {
	      semantic_type = વૃક્ષ_TYPE (કિંમત.કિંમત);
	      કિંમત.કિંમત = વૃક્ષ_OPERAND (કિંમત.કિંમત, 0);
	    }
	  કિંમત.કિંમત = save_પદાવલિ (કિંમત.કિંમત);
	  જો (semantic_type)
	    કિંમત.કિંમત = build1 (EXCESS_PRECISION_પદાવલિ, semantic_type,
				  કિંમત.કિંમત);
	}
    }

  જ્યારે (1)
    {
      જો (વૃક્ષ_CODE (constructor_type) == RECORD_TYPE)
	{
	  વૃક્ષ fieldtype;
	  ગણના વૃક્ષ_code fieldcode;

	  જો (constructor_fields == NULL_વૃક્ષ)
	    {
	      pedwarn_init (loc, 0, "excess elements in struct initializer");
	      તોડો;
	    }

	  fieldtype = વૃક્ષ_TYPE (constructor_fields);
	  જો (fieldtype != error_mark_ગાંઠ)
	    fieldtype = TYPE_MAIN_VARIANT (fieldtype);
	  fieldcode = વૃક્ષ_CODE (fieldtype);

	  /* Error for non-static initialization of a flexible array member.  */
	  જો (fieldcode == ARRAY_TYPE
	      && !require_constant_કિંમત
	      && TYPE_SIZE (fieldtype) == NULL_વૃક્ષ
	      && DECL_CHAIN (constructor_fields) == NULL_વૃક્ષ)
	    {
	      error_init (loc, "non-static initialization of a flexible "
			  "array member");
	      તોડો;
	    }

	  /* Error for initialization of a flexible array member with
	     a string constant if the structure is in an array.  E.g.:
	     struct S { int x; char y[]; };
	     struct S s[] = { { 1, "foo" } };
	     is invalid.  */
	  જો (string_flag
	      && fieldcode == ARRAY_TYPE
	      && constructor_depth > 1
	      && TYPE_SIZE (fieldtype) == NULL_વૃક્ષ
	      && DECL_CHAIN (constructor_fields) == NULL_વૃક્ષ)
	    {
	      તાર્કિક in_array_p = ખોટું;
	      માટે (સંરચના constructor_ઢગલો *p = constructor_ઢગલો;
		   p && p->type; p = p->next)
		જો (વૃક્ષ_CODE (p->type) == ARRAY_TYPE)
		  {
		    in_array_p = સાચું;
		    તોડો;
		  }
	      જો (in_array_p)
		{
		  error_init (loc, "initialization of flexible array "
			      "member in a nested context");
		  તોડો;
		}
	    }

	  /* Accept a string constant to initialize a subarray.  */
	  જો (કિંમત.કિંમત != NULL_વૃક્ષ
	      && fieldcode == ARRAY_TYPE
	      && INTEGRAL_TYPE_P (વૃક્ષ_TYPE (fieldtype))
	      && string_flag)
	    કિંમત.કિંમત = orig_કિંમત;
	  /* Otherwise, if we have come to a subaggregate,
	     and we don't have an element of its type, push into it.  */
	  નહીંતર જો (કિંમત.કિંમત != NULL_વૃક્ષ
		   && initialize_elementwise_p (fieldtype, કિંમત.કિંમત))
	    {
	      ધકેલો_init_level (loc, 1, braced_init_obstack);
	      ચાલુ;
	    }

	  કિંમત.કિંમત = maybe_split_raw_data (કિંમત.કિંમત, &raw_data);
	  જો (કિંમત.કિંમત)
	    {
	      ધકેલો_member_name (constructor_fields);
	      output_init_element (loc, કિંમત.કિંમત, કિંમત.original_type,
				   strict_string, fieldtype,
				   constructor_fields, સાચું, implicit,
				   braced_init_obstack);
	      RESTORE_SPELLING_DEPTH (constructor_depth);
	    }
	  નહીંતર
	    /* Do the bookkeeping for an element that was
	       directly output as a constructor.  */
	    {
	      /* For a record, keep track of end position of last field.  */
	      જો (DECL_SIZE (constructor_fields))
		constructor_bit_index
		  = size_binop_loc (આગત_location, PLUS_પદાવલિ,
				    bit_position (constructor_fields),
				    DECL_SIZE (constructor_fields));

	      /* If the current field was the first one not yet written out,
		 it isn't now, so update.  */
	      જો (constructor_unfilled_fields == constructor_fields)
		{
		  constructor_unfilled_fields = DECL_CHAIN (constructor_fields);
		  /* Skip any nameless bit fields.  */
		  જ્યારે (constructor_unfilled_fields != 0
			 && (DECL_UNNAMED_BIT_FIELD
			     (constructor_unfilled_fields)))
		    constructor_unfilled_fields =
		      DECL_CHAIN (constructor_unfilled_fields);
		}
	    }

	  constructor_fields = DECL_CHAIN (constructor_fields);
	  /* Skip any nameless bit fields at the beginning.  */
	  જ્યારે (constructor_fields != NULL_વૃક્ષ
		 && DECL_UNNAMED_BIT_FIELD (constructor_fields))
	    constructor_fields = DECL_CHAIN (constructor_fields);
	}
      નહીંતર જો (વૃક્ષ_CODE (constructor_type) == UNION_TYPE)
	{
	  વૃક્ષ fieldtype;
	  ગણના વૃક્ષ_code fieldcode;

	  જો (constructor_fields == NULL_વૃક્ષ)
	    {
	      pedwarn_init (loc, 0,
			    "excess elements in union initializer");
	      તોડો;
	    }

	  fieldtype = વૃક્ષ_TYPE (constructor_fields);
	  જો (fieldtype != error_mark_ગાંઠ)
	    fieldtype = TYPE_MAIN_VARIANT (fieldtype);
	  fieldcode = વૃક્ષ_CODE (fieldtype);

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
	  જો (!in_system_header_at (આગત_location) && !constructor_designated
	      && !(કિંમત.કિંમત && (integer_zerop (કિંમત.કિંમત)
				   || real_zerop (કિંમત.કિંમત))))
	    warning (OPT_Wtraditional, "traditional C rejects initialization "
		     "of unions");

	  /* Error for non-static initialization of a flexible array member.  */
	  જો (fieldcode == ARRAY_TYPE
	      && !require_constant_કિંમત
	      && TYPE_SIZE (fieldtype) == NULL_વૃક્ષ)
	    {
	      error_init (loc, "non-static initialization of a flexible "
			  "array member");
	      તોડો;
	    }

	  /* Error for initialization of a flexible array member with
	     a string constant if the structure is in an array.  E.g.:
	     union U { int x; char y[]; };
	     union U s[] = { { 1, "foo" } };
	     is invalid.  */
	  જો (string_flag
	      && fieldcode == ARRAY_TYPE
	      && constructor_depth > 1
	      && TYPE_SIZE (fieldtype) == NULL_વૃક્ષ)
	    {
	      તાર્કિક in_array_p = ખોટું;
	      માટે (સંરચના constructor_ઢગલો *p = constructor_ઢગલો;
		   p && p->type; p = p->next)
		જો (વૃક્ષ_CODE (p->type) == ARRAY_TYPE)
		  {
		    in_array_p = સાચું;
		    તોડો;
		  }
	      જો (in_array_p)
		{
		  error_init (loc, "initialization of flexible array "
			      "member in a nested context");
		  તોડો;
		}
	    }

	  /* Accept a string constant to initialize a subarray.  */
	  જો (કિંમત.કિંમત != NULL_વૃક્ષ
	      && fieldcode == ARRAY_TYPE
	      && INTEGRAL_TYPE_P (વૃક્ષ_TYPE (fieldtype))
	      && string_flag)
	    કિંમત.કિંમત = orig_કિંમત;
	  /* Otherwise, if we have come to a subaggregate,
	     and we don't have an element of its type, push into it.  */
	  નહીંતર જો (કિંમત.કિંમત != NULL_વૃક્ષ
		   && initialize_elementwise_p (fieldtype, કિંમત.કિંમત))
	    {
	      ધકેલો_init_level (loc, 1, braced_init_obstack);
	      ચાલુ;
	    }

	  કિંમત.કિંમત = maybe_split_raw_data (કિંમત.કિંમત, &raw_data);
	  જો (કિંમત.કિંમત)
	    {
	      ધકેલો_member_name (constructor_fields);
	      output_init_element (loc, કિંમત.કિંમત, કિંમત.original_type,
				   strict_string, fieldtype,
				   constructor_fields, સાચું, implicit,
				   braced_init_obstack);
	      RESTORE_SPELLING_DEPTH (constructor_depth);
	    }
	  નહીંતર
	    /* Do the bookkeeping for an element that was
	       directly output as a constructor.  */
	    {
	      constructor_bit_index = DECL_SIZE (constructor_fields);
	      constructor_unfilled_fields = DECL_CHAIN (constructor_fields);
	    }

	  constructor_fields = NULL_વૃક્ષ;
	}
      નહીંતર જો (વૃક્ષ_CODE (constructor_type) == ARRAY_TYPE)
	{
	  વૃક્ષ elttype = TYPE_MAIN_VARIANT (વૃક્ષ_TYPE (constructor_type));
	  ગણના વૃક્ષ_code eltcode = વૃક્ષ_CODE (elttype);

	  /* Accept a string constant to initialize a subarray.  */
	  જો (કિંમત.કિંમત != NULL_વૃક્ષ
	      && eltcode == ARRAY_TYPE
	      && INTEGRAL_TYPE_P (વૃક્ષ_TYPE (elttype))
	      && string_flag)
	    કિંમત.કિંમત = orig_કિંમત;
	  /* Otherwise, if we have come to a subaggregate,
	     and we don't have an element of its type, push into it.  */
	  નહીંતર જો (કિંમત.કિંમત != NULL_વૃક્ષ
		   && initialize_elementwise_p (elttype, કિંમત.કિંમત))
	    {
	      ધકેલો_init_level (loc, 1, braced_init_obstack);
	      ચાલુ;
	    }

	  જો (constructor_max_index != NULL_વૃક્ષ
	      && (વૃક્ષ_int_cst_lt (constructor_max_index, constructor_index)
		  || integer_all_onesp (constructor_max_index))
	      /* For VLA we got an error already.  */
	      && !C_TYPE_VARIABLE_SIZE (constructor_type))
	    {
	      pedwarn_init (loc, 0,
			    "excess elements in array initializer");
	      તોડો;
	    }

	  જો (કિંમત.કિંમત
	      && વૃક્ષ_CODE (કિંમત.કિંમત) == RAW_DATA_CST
	      && RAW_DATA_LENGTH (કિંમત.કિંમત) > 1
	      && (વૃક્ષ_CODE (elttype) == INTEGER_TYPE
		  || વૃક્ષ_CODE (elttype) == BITINT_TYPE)
	      && TYPE_PRECISION (elttype) == CHAR_BIT
	      && (constructor_max_index == NULL_વૃક્ષ
		  || વૃક્ષ_int_cst_lt (constructor_index,
				      constructor_max_index)))
	    {
	      unsigned પૂર્ણાંક len = RAW_DATA_LENGTH (કિંમત.કિંમત);
	      જો (constructor_max_index)
		{
		  widest_int w = wi::to_widest (constructor_max_index);
		  w -= wi::to_widest (constructor_index);
		  w += 1;
		  જો (w < len)
		    len = w.to_uhwi ();
		}
	      જો (len < (unsigned) RAW_DATA_LENGTH (કિંમત.કિંમત))
		{
		  raw_data = copy_ગાંઠ (કિંમત.કિંમત);
		  RAW_DATA_LENGTH (raw_data) -= len;
		  RAW_DATA_POINTER (raw_data) += len;
		  RAW_DATA_LENGTH (કિંમત.કિંમત) = len;
		}
	      વૃક્ષ_TYPE (કિંમત.કિંમત) = elttype;
	      ધકેલો_array_bounds (વૃક્ષ_to_uhwi (constructor_index));
	      output_init_element (loc, કિંમત.કિંમત, કિંમત.original_type,
				   ખોટું, elttype, constructor_index, સાચું,
				   implicit, braced_init_obstack);
	      RESTORE_SPELLING_DEPTH (constructor_depth);
	      constructor_index
		= size_binop_loc (આગત_location, PLUS_પદાવલિ,
				  constructor_index, bitsize_int (len));
	    }
	  નહીંતર
	    {
	      કિંમત.કિંમત = maybe_split_raw_data (કિંમત.કિંમત, &raw_data);
	      /* Now output the actual element.  */
	      જો (કિંમત.કિંમત)
		{
		  ધકેલો_array_bounds (વૃક્ષ_to_uhwi (constructor_index));
		  output_init_element (loc, કિંમત.કિંમત, કિંમત.original_type,
				       strict_string, elttype,
				       constructor_index, સાચું, implicit,
				       braced_init_obstack);
		  RESTORE_SPELLING_DEPTH (constructor_depth);
		}

	      constructor_index
		= size_binop_loc (આગત_location, PLUS_પદાવલિ,
				  constructor_index, bitsize_one_ગાંઠ);

	      જો (!કિંમત.કિંમત)
		/* If we are doing the bookkeeping for an element that was
		   directly output as a constructor, we must update
		   constructor_unfilled_index.  */
		constructor_unfilled_index = constructor_index;
	    }
	}
      નહીંતર જો (gnu_vector_type_p (constructor_type))
	{
	  વૃક્ષ elttype = TYPE_MAIN_VARIANT (વૃક્ષ_TYPE (constructor_type));

	  /* Do a basic check of initializer size.  Note that vectors
	     may not always have a fixed size derived from their type.  */
	  જો (maybe_lt (વૃક્ષ_to_poly_uint64 (constructor_max_index),
			વૃક્ષ_to_poly_uint64 (constructor_index)))
	    {
	      /* Diagose VLA out-of-bounds as errors.  */
	      જો (વૃક્ષ_to_poly_uint64 (constructor_max_index).is_constant())
		pedwarn_init (loc, 0,
			      "excess elements in vector initializer");
	      નહીંતર
		error_init (loc, "excess elements in vector initializer");

	      તોડો;
	    }

	  કિંમત.કિંમત = maybe_split_raw_data (કિંમત.કિંમત, &raw_data);
	  /* Now output the actual element.  */
	  જો (કિંમત.કિંમત)
	    {
	      જો (વૃક્ષ_CODE (કિંમત.કિંમત) == VECTOR_CST)
		elttype = TYPE_MAIN_VARIANT (constructor_type);
	      output_init_element (loc, કિંમત.કિંમત, કિંમત.original_type,
				   strict_string, elttype,
				   constructor_index, સાચું, implicit,
				   braced_init_obstack);
	    }

	  constructor_index
	    = size_binop_loc (આગત_location,
			      PLUS_પદાવલિ, constructor_index, bitsize_one_ગાંઠ);

	  જો (!કિંમત.કિંમત)
	    /* If we are doing the bookkeeping for an element that was
	       directly output as a constructor, we must update
	       constructor_unfilled_index.  */
	    constructor_unfilled_index = constructor_index;
	}

      /* Handle the sole element allowed in a braced initializer
	 for a scalar variable.  */
      નહીંતર જો (constructor_type != error_mark_ગાંઠ
	       && constructor_fields == NULL_વૃક્ષ)
	{
	  pedwarn_init (loc, 0,
			"excess elements in scalar initializer");
	  તોડો;
	}
      નહીંતર
	{
	  કિંમત.કિંમત = maybe_split_raw_data (કિંમત.કિંમત, &raw_data);
	  જો (કિંમત.કિંમત)
	    output_init_element (loc, કિંમત.કિંમત, કિંમત.original_type,
				 strict_string, constructor_type,
				 NULL_વૃક્ષ, સાચું, implicit,
				 braced_init_obstack);
	  constructor_fields = NULL_વૃક્ષ;
	}

      /* Handle range initializers either at this level or anywhere higher
	 in the designator stack.  */
      જો (constructor_range_ઢગલો)
	{
	  સંરચના constructor_range_ઢગલો *p, *range_ઢગલો;
	  પૂર્ણાંક finish = 0;

	  range_ઢગલો = constructor_range_ઢગલો;
	  constructor_range_ઢગલો = 0;
	  જ્યારે (constructor_ઢગલો != range_ઢગલો->ઢગલો)
	    {
	      gcc_assert (constructor_ઢગલો->implicit);
	      process_init_element (loc,
				    કાઢો_init_level (loc, 1,
						    braced_init_obstack,
						    last_init_list_comma),
				    સાચું, braced_init_obstack);
	    }
	  માટે (p = range_ઢગલો;
	       !p->range_end || વૃક્ષ_int_cst_equal (p->index, p->range_end);
	       p = p->prev)
	    {
	      gcc_assert (constructor_ઢગલો->implicit);
	      process_init_element (loc,
				    કાઢો_init_level (loc, 1,
						    braced_init_obstack,
						    last_init_list_comma),
				    સાચું, braced_init_obstack);
	    }

	  p->index = size_binop_loc (આગત_location,
				     PLUS_પદાવલિ, p->index, bitsize_one_ગાંઠ);
	  જો (વૃક્ષ_int_cst_equal (p->index, p->range_end) && !p->prev)
	    finish = 1;

	  જ્યારે (1)
	    {
	      constructor_index = p->index;
	      constructor_fields = p->fields;
	      જો (finish && p->range_end && p->index == p->range_start)
		{
		  finish = 0;
		  p->prev = 0;
		}
	      p = p->next;
	      જો (!p)
		તોડો;
	      finish_implicit_inits (loc, braced_init_obstack);
	      ધકેલો_init_level (loc, 2, braced_init_obstack);
	      p->ઢગલો = constructor_ઢગલો;
	      જો (p->range_end && વૃક્ષ_int_cst_equal (p->index, p->range_end))
		p->index = p->range_start;
	    }

	  જો (!finish)
	    constructor_range_ઢગલો = range_ઢગલો;
	  ચાલુ;
	}

      તોડો;
    }

  constructor_range_ઢગલો = 0;

  જો (raw_data && RAW_DATA_LENGTH (raw_data))
    {
      gcc_assert (!string_flag && !was_designated);
      કિંમત.કિંમત = raw_data;
      raw_data = NULL_વૃક્ષ;
      જાઓ retry;
    }
}

/* Build a complete asm-statement, whose components are a CV_QUALIFIER
   (guaranteed to be 'volatile' or null) and ARGS (represented using
   an ASM_EXPR node).  */
વૃક્ષ
build_asm_stmt (તાર્કિક is_volatile, વૃક્ષ args)
{
  જો (is_volatile)
    ASM_VOLATILE_P (args) = 1;
  પાછા add_stmt (args);
}

/* Build an asm-expr, whose components are a STRING, some OUTPUTS,
   some INPUTS, and some CLOBBERS.  The latter three may be NULL.
   SIMPLE indicates whether there was anything at all after the
   string in the asm expression -- asm("blah") and asm("blah" : )
   are subtly different.  We use a ASM_EXPR node to represent this.
   LOC is the location of the asm, and IS_INLINE says whether this
   is asm inline.  */
વૃક્ષ
build_asm_પદાવલિ (location_t loc, વૃક્ષ string, વૃક્ષ outputs, વૃક્ષ inputs,
		વૃક્ષ clobbers, વૃક્ષ labels, તાર્કિક simple, તાર્કિક is_inline)
{
  વૃક્ષ tail;
  વૃક્ષ args;
  પૂર્ણાંક i;
  અચલ અક્ષર *constraint;
  અચલ અક્ષર **oconstraints;
  તાર્કિક allows_mem, allows_reg, is_inout;
  પૂર્ણાંક ninputs, noutputs;

  ninputs = list_length (inputs);
  noutputs = list_length (outputs);
  oconstraints = (અચલ અક્ષર **) alloca (noutputs * કદ (અચલ અક્ષર *));

  string = resolve_asm_operand_names (string, outputs, inputs, labels);

  /* Remove output conversions that change the type but not the mode.  */
  માટે (i = 0, tail = outputs; tail; ++i, tail = વૃક્ષ_CHAIN (tail))
    {
      વૃક્ષ output = વૃક્ષ_કિંમત (tail);

      output = c_fully_fold (output, ખોટું, ખાલી, સાચું);

      /* ??? Really, this should not be here.  Users should be using a
	 proper lvalue, dammit.  But there's a long history of using casts
	 in the output operands.  In cases like longlong.h, this becomes a
	 primitive form of typechecking -- if the cast can be removed, then
	 the output operand had a type of the proper width; otherwise we'll
	 get an error.  Gross, but ...  */
      STRIP_NOPS (output);

      જો (!lvalue_or_else (loc, output, lv_asm))
	output = error_mark_ગાંઠ;

      જો (output != error_mark_ગાંઠ
	  && (વૃક્ષ_READONLY (output)
	      || TYPE_READONLY (વૃક્ષ_TYPE (output))
	      || (RECORD_OR_UNION_TYPE_P (વૃક્ષ_TYPE (output))
		  && C_TYPE_FIELDS_READONLY (વૃક્ષ_TYPE (output)))))
	readonly_error (loc, output, lv_asm);

      constraint = વૃક્ષ_STRING_POINTER (વૃક્ષ_કિંમત (વૃક્ષ_PURPOSE (tail)));
      oconstraints[i] = constraint;

      જો (parse_output_constraint (&constraint, i, ninputs, noutputs,
				   &allows_mem, &allows_reg, &is_inout,
				   nullptr))
	{
	  /* If the operand is going to end up in memory,
	     mark it addressable.  */
	  જો (!allows_reg && !c_mark_addressable (output))
	    output = error_mark_ગાંઠ;
	  જો (!(!allows_reg && allows_mem)
	      && output != error_mark_ગાંઠ
	      && VOID_TYPE_P (વૃક્ષ_TYPE (output)))
	    {
	      error_at (loc, "invalid use of void expression");
	      output = error_mark_ગાંઠ;
	    }
	  જો (allows_reg && current_function_decl == NULL_વૃક્ષ)
	    {
	      error_at (loc, "constraint allows registers outside of "
			     "a function");
	      output = error_mark_ગાંઠ;
	    }
	}
      નહીંતર
	output = error_mark_ગાંઠ;

      જો (current_function_decl == NULL_વૃક્ષ && output != error_mark_ગાંઠ)
	{
	  જો (વૃક્ષ_SIDE_EFFECTS (output))
	    {
	      error_at (loc, "side-effects in output operand outside "
			     "of a function");
	      output = error_mark_ગાંઠ;
	    }
	  નહીંતર
	    {
	      વૃક્ષ addr = build_unary_op (loc, ADDR_પદાવલિ, output, ખોટું);
	      જો (addr == error_mark_ગાંઠ)
		output = error_mark_ગાંઠ;
	      નહીંતર જો (!initializer_constant_valid_p (addr, વૃક્ષ_TYPE (addr)))
		{
		  error_at (loc, "output operand outside of a function is not "
				 "constant");
		  output = error_mark_ગાંઠ;
		}
	    }
	}
      નહીંતર જો (output != error_mark_ગાંઠ && strstr (constraint, "-"))
	{
	  error_at (loc, "%<-%> modifier used inside of a function");
	  output = error_mark_ગાંઠ;
	}

      વૃક્ષ_કિંમત (tail) = output;
    }

  માટે (i = 0, tail = inputs; tail; ++i, tail = વૃક્ષ_CHAIN (tail))
    {
      વૃક્ષ આગત;

      constraint = વૃક્ષ_STRING_POINTER (વૃક્ષ_કિંમત (વૃક્ષ_PURPOSE (tail)));
      આગત = વૃક્ષ_કિંમત (tail);

      જો (parse_આગત_constraint (&constraint, i, ninputs, noutputs, 0,
				  oconstraints, &allows_mem, &allows_reg,
				  nullptr))
	{
	  /* If the operand is going to end up in memory,
	     mark it addressable.  */
	  જો (!allows_reg && allows_mem)
	    {
	      આગત = c_fully_fold (આગત, ખોટું, ખાલી, સાચું);

	      /* Strip the nops as we allow this case.  FIXME, this really
		 should be rejected or made deprecated.  */
	      STRIP_NOPS (આગત);
	      જો (!c_mark_addressable (આગત))
		આગત = error_mark_ગાંઠ;
	    }
	  નહીંતર
	    {
	      આગત = c_fully_fold (convert_lvalue_to_rvalue (loc, આગત,
							      સાચું, ખોટું),
				    ખોટું, ખાલી);

	      જો (આગત != error_mark_ગાંઠ && VOID_TYPE_P (વૃક્ષ_TYPE (આગત)))
		{
		  error_at (loc, "invalid use of void expression");
		  આગત = error_mark_ગાંઠ;
		}
	    }
	  જો (allows_reg && current_function_decl == NULL_વૃક્ષ)
	    {
	      error_at (loc, "constraint allows registers outside of "
			     "a function");
	      આગત = error_mark_ગાંઠ;
	    }
	  જો (constraint[0] == ':' && આગત != error_mark_ગાંઠ)
	    {
	      વૃક્ષ t = આગત;
	      STRIP_NOPS (t);
	      જો (વૃક્ષ_CODE (t) != ADDR_પદાવલિ
		  || !(વૃક્ષ_CODE (વૃક્ષ_OPERAND (t, 0)) == FUNCTION_DECL
		       || (VAR_P (વૃક્ષ_OPERAND (t, 0))
			   && is_global_var (વૃક્ષ_OPERAND (t, 0)))))
		{
		  error_at (loc, "%<:%> constraint operand is not address "
				 "of a function or non-automatic variable");
		  આગત = error_mark_ગાંઠ;
		}
	      નહીંતર જો (વૃક્ષ_CODE (વૃક્ષ_OPERAND (t, 0)) == FUNCTION_DECL)
		suppress_warning (વૃક્ષ_OPERAND (t, 0), OPT_Wunused);
	    }
	}
      નહીંતર
	આગત = error_mark_ગાંઠ;

      જો (current_function_decl == NULL_વૃક્ષ && આગત != error_mark_ગાંઠ)
	{
	  જો (વૃક્ષ_SIDE_EFFECTS (આગત))
	    {
	      error_at (loc, "side-effects in input operand outside "
			     "of a function");
	      આગત = error_mark_ગાંઠ;
	    }
	  નહીંતર
	    {
	      વૃક્ષ tem = આગત;
	      જો (allows_mem && lvalue_p (આગત))
		tem = build_unary_op (loc, ADDR_પદાવલિ, આગત, ખોટું);
	      જો (!initializer_constant_valid_p (tem, વૃક્ષ_TYPE (tem)))
		{
		  error_at (loc, "input operand outside of a function is not "
				 "constant");
		  આગત = error_mark_ગાંઠ;
		}
	    }
	}
      નહીંતર જો (આગત != error_mark_ગાંઠ && strstr (constraint, "-"))
	{
	  error_at (loc, "%<-%> modifier used inside of a function");
	  આગત = error_mark_ગાંઠ;
	}

      વૃક્ષ_કિંમત (tail) = આગત;
    }

  args = build_stmt (loc, ASM_પદાવલિ, string, outputs, inputs, clobbers, labels);

  /* asm statements without outputs, including simple ones, are treated
     as volatile.  */
  ASM_BASIC_P (args) = simple;
  ASM_VOLATILE_P (args) = (noutputs == 0);
  ASM_INLINE_P (args) = is_inline;

  પાછા args;
}

/* Generate a goto statement to LABEL.  LOC is the location of the
   GOTO.  */

વૃક્ષ
c_finish_goto_label (location_t loc, વૃક્ષ label)
{
  વૃક્ષ decl = lookup_label_for_goto (loc, label);
  જો (!decl)
    પાછા NULL_વૃક્ષ;
  વૃક્ષ_USED (decl) = 1;
  mark_decl_used (decl, ખોટું);
  {
    add_stmt (build_predict_પદાવલિ (PRED_GOTO, NOT_TAKEN));
    વૃક્ષ t = build1 (GOTO_પદાવલિ, void_type_ગાંઠ, decl);
    SET_પદાવલિ_LOCATION (t, loc);
    પાછા add_stmt (t);
  }
}

/* Generate a computed goto statement to EXPR.  LOC is the location of
   the GOTO.  */

વૃક્ષ
c_finish_goto_ptr (location_t loc, c_પદાવલિ val)
{
  વૃક્ષ પદાવલિ = val.કિંમત;
  વૃક્ષ t;
  pedwarn (loc, OPT_Wpedantic, "ISO C forbids %<goto *expr;%>");
  જો (પદાવલિ != error_mark_ગાંઠ
      && !POINTER_TYPE_P (વૃક્ષ_TYPE (પદાવલિ))
      && !null_pointer_constant_p (પદાવલિ))
    {
      error_at (val.get_location (),
		"computed goto must be pointer type");
      પદાવલિ = build_zero_cst (ptr_type_ગાંઠ);
    }
  પદાવલિ = c_fully_fold (પદાવલિ, ખોટું, ખાલી);
  પદાવલિ = convert (ptr_type_ગાંઠ, પદાવલિ);
  t = build1 (GOTO_પદાવલિ, void_type_ગાંઠ, પદાવલિ);
  SET_પદાવલિ_LOCATION (t, loc);
  પાછા add_stmt (t);
}

/* Generate a C `return' statement.  RETVAL is the expression for what
   to return, or a null pointer for `return;' with no value.  LOC is
   the location of the return statement, or the location of the expression,
   if the statement has any.  If ORIGTYPE is not NULL_TREE, it
   is the original type of RETVAL.  MUSTTAIL_P indicates a musttail
   attribute.  */

વૃક્ષ
c_finish_return (location_t loc, વૃક્ષ retval, વૃક્ષ origtype, તાર્કિક musttail_p)
{
  વૃક્ષ valtype = વૃક્ષ_TYPE (વૃક્ષ_TYPE (current_function_decl)), ret_stmt;
  તાર્કિક no_warning = ખોટું;
  તાર્કિક npc = ખોટું;

  /* Use the expansion point to handle cases such as returning NULL
     in a function returning void.  */
  location_t xloc = expansion_point_location_if_in_system_header (loc);

  જો (વૃક્ષ_THIS_VOLATILE (current_function_decl))
    warning_at (xloc, 0,
		"function declared %<noreturn%> has a %<return%> statement");

  set_musttail_on_return (retval, xloc, musttail_p);

  જો (retval)
    {
      વૃક્ષ semantic_type = NULL_વૃક્ષ;
      npc = null_pointer_constant_p (retval);
      જો (વૃક્ષ_CODE (retval) == EXCESS_PRECISION_પદાવલિ)
	{
	  semantic_type = વૃક્ષ_TYPE (retval);
	  retval = વૃક્ષ_OPERAND (retval, 0);
	}
      retval = c_fully_fold (retval, ખોટું, ખાલી);
      જો (semantic_type
	  && valtype != NULL_વૃક્ષ
	  && વૃક્ષ_CODE (valtype) != VOID_TYPE)
	retval = build1 (EXCESS_PRECISION_પદાવલિ, semantic_type, retval);
    }

  જો (!retval)
    {
      current_function_returns_null = 1;
      જો ((warn_return_type >= 0 || flag_isoc99)
	  && valtype != NULL_વૃક્ષ && વૃક્ષ_CODE (valtype) != VOID_TYPE)
	{
	  no_warning = સાચું;
	  જો (emit_diagnostic (flag_isoc99
			       ? diagnostics::kind::permerror
			       : diagnostics::kind::warning,
			       loc, OPT_Wreturn_mismatch,
			       "%<return%> with no value,"
			       " in function returning non-void"))
	    inform (DECL_SOURCE_LOCATION (current_function_decl),
		    "declared here");
	}
    }
  નહીંતર જો (valtype == NULL_વૃક્ષ || VOID_TYPE_P (valtype))
    {
      current_function_returns_null = 1;
      તાર્કિક warned_here;
      જો (વૃક્ષ_CODE (વૃક્ષ_TYPE (retval)) != VOID_TYPE)
	warned_here = permerror_opt
	  (xloc, OPT_Wreturn_mismatch,
	   "%<return%> with a value, in function returning void");
      નહીંતર
	warned_here = pedwarn
	  (xloc, OPT_Wpedantic, "ISO C forbids "
	   "%<return%> with expression, in function returning void");
      જો (warned_here)
	inform (DECL_SOURCE_LOCATION (current_function_decl),
		"declared here");
    }
  નહીંતર
    {
      વૃક્ષ t = convert_for_assignment (loc, UNKNOWN_LOCATION, valtype,
				       retval, origtype, ic_return,
				       npc, NULL_વૃક્ષ, NULL_વૃક્ષ, 0);
      વૃક્ષ res = DECL_RESULT (current_function_decl);
      વૃક્ષ inner;
      તાર્કિક save;

      current_function_returns_કિંમત = 1;
      જો (t == error_mark_ગાંઠ)
	{
	  /* Suppress -Wreturn-type for this function.  */
	  જો (warn_return_type)
	    suppress_warning (current_function_decl, OPT_Wreturn_type);
	  પાછા NULL_વૃક્ષ;
	}

      save = in_late_દ્વિઅંકી_op;
      જો (C_BOOLEAN_TYPE_P (વૃક્ષ_TYPE (res))
	  || વૃક્ષ_CODE (વૃક્ષ_TYPE (res)) == COMPLEX_TYPE
	  || (SCALAR_FLOAT_TYPE_P (વૃક્ષ_TYPE (t))
	      && (વૃક્ષ_CODE (વૃક્ષ_TYPE (res)) == INTEGER_TYPE
		  || વૃક્ષ_CODE (વૃક્ષ_TYPE (res)) == ENUMERAL_TYPE)
	      && sanitize_flags_p (SANITIZE_FLOAT_CAST)))
        in_late_દ્વિઅંકી_op = સાચું;
      inner = t = convert (વૃક્ષ_TYPE (res), t);
      in_late_દ્વિઅંકી_op = save;

      /* Strip any conversions, additions, and subtractions, and see if
	 we are returning the address of a local variable.  Warn if so.  */
      જ્યારે (1)
	{
	  પસંદગી (વૃક્ષ_CODE (inner))
	    {
	    CASE_CONVERT:
	    સ્થિતિ NON_LVALUE_પદાવલિ:
	    સ્થિતિ PLUS_પદાવલિ:
	    સ્થિતિ POINTER_PLUS_પદાવલિ:
	      inner = વૃક્ષ_OPERAND (inner, 0);
	      ચાલુ;

	    સ્થિતિ MINUS_પદાવલિ:
	      /* If the second operand of the MINUS_EXPR has a pointer
		 type (or is converted from it), this may be valid, so
		 don't give a warning.  */
	      {
		વૃક્ષ op1 = વૃક્ષ_OPERAND (inner, 1);

		જ્યારે (!POINTER_TYPE_P (વૃક્ષ_TYPE (op1))
		       && (CONVERT_પદાવલિ_P (op1)
			   || વૃક્ષ_CODE (op1) == NON_LVALUE_પદાવલિ))
		  op1 = વૃક્ષ_OPERAND (op1, 0);

		જો (POINTER_TYPE_P (વૃક્ષ_TYPE (op1)))
		  તોડો;

		inner = વૃક્ષ_OPERAND (inner, 0);
		ચાલુ;
	      }

	    સ્થિતિ ADDR_પદાવલિ:
	      inner = વૃક્ષ_OPERAND (inner, 0);

	      જ્યારે (REFERENCE_CLASS_P (inner)
		     && !INDIRECT_REF_P (inner))
		inner = વૃક્ષ_OPERAND (inner, 0);

	      જો (DECL_P (inner)
		  && !DECL_EXTERNAL (inner)
		  && DECL_CONTEXT (inner) == current_function_decl
		  && POINTER_TYPE_P (વૃક્ષ_TYPE (વૃક્ષ_TYPE (current_function_decl))))
		{
		  જો (વૃક્ષ_CODE (inner) == LABEL_DECL)
		    warning_at (loc, OPT_Wreturn_local_addr,
				"function returns address of label");
		  નહીંતર જો (વૃક્ષ_CODE (inner) == FUNCTION_DECL
			   && (C_FUNC_NONLOCAL_CONTEXT (inner)
			       || !DECL_INITIAL (inner)))
		    warning_at (loc, OPT_Wreturn_local_addr,
				"function returns address of nested function "
				"referencing local context");
		  નહીંતર જો (વૃક્ષ_CODE (inner) != FUNCTION_DECL
			   && !વૃક્ષ_STATIC (inner))
		    {
		      warning_at (loc, OPT_Wreturn_local_addr,
				  "function returns address of local variable");
		      વૃક્ષ zero = build_zero_cst (વૃક્ષ_TYPE (res));
		      t = build2 (COMPOUND_પદાવલિ, વૃક્ષ_TYPE (res), t, zero);
		    }
		}
	      તોડો;

	    મૂળભૂત:
	      તોડો;
	    }

	  તોડો;
	}

      retval = build2 (MODIFY_પદાવલિ, વૃક્ષ_TYPE (res), res, t);
      SET_પદાવલિ_LOCATION (retval, loc);

      જો (warn_sequence_point)
	verify_sequence_points (retval);
    }

  ret_stmt = build_stmt (loc, RETURN_પદાવલિ, retval);
  જો (no_warning)
    suppress_warning (ret_stmt, OPT_Wreturn_type);
  પાછા add_stmt (ret_stmt);
}

સંરચના c_switch {
  /* The SWITCH_STMT being built.  */
  વૃક્ષ switch_stmt;

  /* The original type of the testing expression, i.e. before the
     default conversion is applied.  */
  વૃક્ષ orig_type;

  /* A splay-tree mapping the low element of a case range to the high
     element, or NULL_TREE if there is no high element.  Used to
     determine whether or not a new case label duplicates an old case
     label.  We need a tree, rather than simply a hash table, because
     of the GNU case range extension.  */
  splay_વૃક્ષ cases;

  /* The bindings at the point of the switch.  This is used for
     warnings crossing decls when branching to a case label.  */
  સંરચના c_spot_bindings *bindings;

  /* Whether the switch includes any break statements.  */
  તાર્કિક break_stmt_seen_p;

  /* The next node on the stack.  */
  સંરચના c_switch *next;

  /* Remember whether the controlling expression had boolean type
     before integer promotions for the sake of -Wswitch-bool.  */
  તાર્કિક bool_cond_p;
};

/* A stack of the currently active switch statements.  The innermost
   switch statement is on the top of the stack.  There is no need to
   mark the stack for garbage collection because it is only active
   during the processing of the body of a function, and we never
   collect at that point.  */

સંરચના c_switch *c_switch_ઢગલો;

/* Start a C switch statement, testing expression EXP.  Return the new
   SWITCH_STMT.  SWITCH_LOC is the location of the `switch'.
   SWITCH_COND_LOC is the location of the switch's condition.
   EXPLICIT_CAST_P is true if the expression EXP has an explicit cast.  */

વૃક્ષ
c_start_switch (location_t switch_loc,
		location_t switch_cond_loc,
		વૃક્ષ exp, તાર્કિક explicit_cast_p, વૃક્ષ switch_name)
{
  વૃક્ષ orig_type = error_mark_ગાંઠ;
  તાર્કિક bool_cond_p = ખોટું;
  સંરચના c_switch *cs;

  જો (exp != error_mark_ગાંઠ)
    {
      orig_type = વૃક્ષ_TYPE (exp);

      જો (!INTEGRAL_TYPE_P (orig_type))
	{
	  જો (orig_type != error_mark_ગાંઠ)
	    {
	      error_at (switch_cond_loc, "switch quantity not an integer");
	      orig_type = error_mark_ગાંઠ;
	    }
	  exp = integer_zero_ગાંઠ;
	}
      નહીંતર
	{
	  વૃક્ષ type = TYPE_MAIN_VARIANT (orig_type);
	  વૃક્ષ e = exp;

	  /* Warn if the condition has boolean value.  */
	  જ્યારે (વૃક્ષ_CODE (e) == COMPOUND_પદાવલિ)
	    e = વૃક્ષ_OPERAND (e, 1);

	  જો ((C_BOOLEAN_TYPE_P (type)
	       || truth_કિંમત_p (વૃક્ષ_CODE (e)))
	      /* Explicit cast to int suppresses this warning.  */
	      && !(વૃક્ષ_CODE (type) == INTEGER_TYPE
		   && explicit_cast_p))
	    bool_cond_p = સાચું;

	  જો (!in_system_header_at (આગત_location)
	      && (type == long_integer_type_ગાંઠ
		  || type == long_unsigned_type_ગાંઠ))
	    warning_at (switch_cond_loc,
			OPT_Wtraditional, "%<long%> switch expression not "
			"converted to %<int%> in ISO C");

	  exp = c_fully_fold (exp, ખોટું, ખાલી);
	  exp = default_conversion (exp);

	  જો (warn_sequence_point)
	    verify_sequence_points (exp);
	}
    }

  /* Add this new SWITCH_STMT to the stack.  */
  cs = XNEW (સંરચના c_switch);
  cs->switch_stmt = build_stmt (switch_loc, SWITCH_STMT, exp,
				NULL_વૃક્ષ, orig_type, NULL_વૃક્ષ, switch_name);
  cs->orig_type = orig_type;
  cs->cases = splay_વૃક્ષ_new (case_compare, ખાલી, ખાલી);
  cs->bindings = c_get_switch_bindings ();
  cs->break_stmt_seen_p = ખોટું;
  cs->bool_cond_p = bool_cond_p;
  cs->next = c_switch_ઢગલો;
  c_switch_ઢગલો = cs;

  પાછા add_stmt (cs->switch_stmt);
}

/* Process a case label at location LOC, with attributes ATTRS.  */

વૃક્ષ
do_case (location_t loc, વૃક્ષ નીચલું_કિંમત, વૃક્ષ ઉપલું_કિંમત, વૃક્ષ attrs)
{
  વૃક્ષ label = NULL_વૃક્ષ;

  જો (નીચલું_કિંમત && વૃક્ષ_CODE (નીચલું_કિંમત) != INTEGER_CST)
    {
      નીચલું_કિંમત = c_fully_fold (નીચલું_કિંમત, ખોટું, ખાલી);
      જો (વૃક્ષ_CODE (નીચલું_કિંમત) == INTEGER_CST)
	pedwarn (loc, OPT_Wpedantic,
		 "case label is not an integer constant expression");
    }

  જો (ઉપલું_કિંમત && વૃક્ષ_CODE (ઉપલું_કિંમત) != INTEGER_CST)
    {
      ઉપલું_કિંમત = c_fully_fold (ઉપલું_કિંમત, ખોટું, ખાલી);
      જો (વૃક્ષ_CODE (ઉપલું_કિંમત) == INTEGER_CST)
	pedwarn (આગત_location, OPT_Wpedantic,
		 "case label is not an integer constant expression");
    }

  જો (c_switch_ઢગલો == ખાલી)
    {
      જો (નીચલું_કિંમત)
	error_at (loc, "case label not within a switch statement");
      નહીંતર
	error_at (loc, "%<default%> label not within a switch statement");
      પાછા NULL_વૃક્ષ;
    }

  જો (c_check_switch_jump_warnings (c_switch_ઢગલો->bindings,
				    પદાવલિ_LOCATION (c_switch_ઢગલો->switch_stmt),
				    loc))
    પાછા NULL_વૃક્ષ;

  label = c_add_case_label (loc, c_switch_ઢગલો->cases,
			    SWITCH_STMT_COND (c_switch_ઢગલો->switch_stmt),
			    નીચલું_કિંમત, ઉપલું_કિંમત, attrs);
  જો (label == error_mark_ગાંઠ)
    label = NULL_વૃક્ષ;
  પાછા label;
}

/* Finish the switch statement.  TYPE is the original type of the
   controlling expression of the switch, or NULL_TREE.  */

શૂન્ય
c_finish_switch (વૃક્ષ body, વૃક્ષ type)
{
  સંરચના c_switch *cs = c_switch_ઢગલો;
  location_t switch_location;

  SWITCH_STMT_BODY (cs->switch_stmt) = body;

  /* Emit warnings as needed.  */
  switch_location = પદાવલિ_LOCATION (cs->switch_stmt);
  c_do_switch_warnings (cs->cases, switch_location,
			type ? type : SWITCH_STMT_TYPE (cs->switch_stmt),
			SWITCH_STMT_COND (cs->switch_stmt), cs->bool_cond_p);
  જો (c_switch_covers_all_cases_p (cs->cases,
				   SWITCH_STMT_TYPE (cs->switch_stmt)))
    SWITCH_STMT_ALL_CASES_P (cs->switch_stmt) = 1;
  SWITCH_STMT_NO_BREAK_P (cs->switch_stmt) = !cs->break_stmt_seen_p;

  /* Pop the stack.  */
  c_switch_ઢગલો = cs->next;
  splay_વૃક્ષ_delete (cs->cases);
  c_release_switch_bindings (cs->bindings);
  XDELETE (cs);
}

/* Emit an if statement.  IF_LOCUS is the location of the 'if'.  COND,
   THEN_BLOCK and ELSE_BLOCK are expressions to be used; ELSE_BLOCK
   may be null.  */

શૂન્ય
c_finish_if_stmt (location_t if_locus, વૃક્ષ cond, વૃક્ષ then_block,
		  વૃક્ષ else_block)
{
  વૃક્ષ stmt;

  stmt = build3 (COND_પદાવલિ, void_type_ગાંઠ, cond, then_block, else_block);
  SET_પદાવલિ_LOCATION (stmt, if_locus);
  add_stmt (stmt);
}

વૃક્ષ
c_finish_bc_stmt (location_t loc, વૃક્ષ label, તાર્કિક is_break, વૃક્ષ name)
{
  /* In switch statements break is sometimes stylistically used after
     a return statement.  This can lead to spurious warnings about
     control reaching the end of a non-void function when it is
     inlined.  Note that we are calling block_may_fallthru with
     language specific tree nodes; this works because
     block_may_fallthru returns true when given something it does not
     understand.  */
  તાર્કિક skip = !block_may_fallthru (cur_stmt_list);

  જો (is_break)
    પસંદગી (in_statement & ~IN_NAMED_STMT)
      {
      સ્થિતિ 0:
	error_at (loc, "break statement not within loop or switch");
	પાછા NULL_વૃક્ષ;
      સ્થિતિ IN_OMP_BLOCK:
	error_at (loc, "invalid exit from OpenMP structured block");
	પાછા NULL_વૃક્ષ;
      સ્થિતિ IN_OMP_FOR:
	error_at (loc, "break statement used with OpenMP for loop");
	પાછા NULL_વૃક્ષ;
      સ્થિતિ IN_ITERATION_STMT:
      સ્થિતિ IN_OBJC_FOREACH:
	તોડો;
      મૂળભૂત:
	gcc_assert (in_statement & IN_SWITCH_STMT);
	c_switch_ઢગલો->break_stmt_seen_p = સાચું;
	તોડો;
      }
  નહીંતર
    પસંદગી (in_statement & ~(IN_SWITCH_STMT | IN_NAMED_STMT))
      {
      સ્થિતિ 0:
	error_at (loc, "continue statement not within a loop");
	પાછા NULL_વૃક્ષ;
      સ્થિતિ IN_OMP_BLOCK:
	error_at (loc, "invalid exit from OpenMP structured block");
	પાછા NULL_વૃક્ષ;
      સ્થિતિ IN_ITERATION_STMT:
      સ્થિતિ IN_OMP_FOR:
      સ્થિતિ IN_OBJC_FOREACH:
	તોડો;
      મૂળભૂત:
	gcc_unreachable ();
      }

  જો (skip)
    પાછા NULL_વૃક્ષ;
  નહીંતર જો ((in_statement & IN_OBJC_FOREACH)
	   && !(is_break && (in_statement & IN_SWITCH_STMT))
	   && name == NULL_વૃક્ષ)
    {
      /* The foreach expander produces low-level code using gotos instead
	 of a structured loop construct.  */
      gcc_assert (label);
      પાછા add_stmt (build_stmt (loc, GOTO_પદાવલિ, label));
    }
  નહીંતર જો (name && C_DECL_LOOP_NAME (name) && C_DECL_SWITCH_NAME (name))
    {
      label = DECL_CHAIN (name);
      જો (!is_break)
	label = DECL_CHAIN (label);
      /* Foreach expander from some outer level.  */
      પાછા add_stmt (build_stmt (loc, GOTO_પદાવલિ, label));
    }
  પાછા add_stmt (build_stmt (loc, is_break ? BREAK_STMT : CONTINUE_STMT,
			       name));
}

/* A helper routine for c_process_expr_stmt and c_finish_stmt_expr.  */

સ્થિર શૂન્ય
emit_side_effect_warnings (location_t loc, વૃક્ષ પદાવલિ)
{
  maybe_warn_nodiscard (loc, પદાવલિ);
  જો (!warn_unused_કિંમત)
    પાછા;
  જો (પદાવલિ == error_mark_ગાંઠ)
    ;
  નહીંતર જો (!વૃક્ષ_SIDE_EFFECTS (પદાવલિ))
    {
      જો (!VOID_TYPE_P (વૃક્ષ_TYPE (પદાવલિ))
	  && !warning_suppressed_p (પદાવલિ, OPT_Wunused_કિંમત))
	warning_at (loc, OPT_Wunused_કિંમત, "statement with no effect");
    }
  નહીંતર જો (વૃક્ષ_CODE (પદાવલિ) == COMPOUND_પદાવલિ)
    {
      વૃક્ષ r = પદાવલિ;
      location_t cloc = loc;
      જ્યારે (વૃક્ષ_CODE (r) == COMPOUND_પદાવલિ)
	{
	  જો (પદાવલિ_HAS_LOCATION (r))
	    cloc = પદાવલિ_LOCATION (r);
	  r = વૃક્ષ_OPERAND (r, 1);
	}
      જો (!વૃક્ષ_SIDE_EFFECTS (r)
	  && !VOID_TYPE_P (વૃક્ષ_TYPE (r))
	  && !CONVERT_પદાવલિ_P (r)
	  && !warning_suppressed_p (r, OPT_Wunused_કિંમત)
	  && !warning_suppressed_p (પદાવલિ, OPT_Wunused_કિંમત))
	warning_at (cloc, OPT_Wunused_કિંમત,
		    "right-hand operand of comma expression has no effect");
    }
  નહીંતર
    warn_if_unused_કિંમત (પદાવલિ, loc);
}

/* Process an expression as if it were a complete statement.  Emit
   diagnostics, but do not call ADD_STMT.  LOC is the location of the
   statement.  */

વૃક્ષ
c_process_પદાવલિ_stmt (location_t loc, વૃક્ષ પદાવલિ)
{
  વૃક્ષ exprv;

  જો (!પદાવલિ)
    પાછા NULL_વૃક્ષ;

  પદાવલિ = c_fully_fold (પદાવલિ, ખોટું, ખાલી);

  જો (warn_sequence_point)
    verify_sequence_points (પદાવલિ);

  જો (વૃક્ષ_TYPE (પદાવલિ) != error_mark_ગાંઠ
      && !COMPLETE_OR_VOID_TYPE_P (વૃક્ષ_TYPE (પદાવલિ))
      && વૃક્ષ_CODE (વૃક્ષ_TYPE (પદાવલિ)) != ARRAY_TYPE)
    error_at (loc, "expression statement has incomplete type");

  /* If we're not processing a statement expression, warn about unused values.
     Warnings for statement expressions will be emitted later, once we figure
     out which is the result.  */
  જો (!STATEMENT_LIST_STMT_પદાવલિ (cur_stmt_list)
      && (warn_unused_કિંમત || warn_unused_result))
    emit_side_effect_warnings (પદાવલિ_LOC_OR_LOC (પદાવલિ, loc), પદાવલિ);

  exprv = પદાવલિ;
  જ્યારે (વૃક્ષ_CODE (exprv) == COMPOUND_પદાવલિ)
    exprv = વૃક્ષ_OPERAND (exprv, 1);
  જ્યારે (CONVERT_પદાવલિ_P (exprv))
    exprv = વૃક્ષ_OPERAND (exprv, 0);
  જો (DECL_P (exprv)
      || handled_component_p (exprv)
      || વૃક્ષ_CODE (exprv) == ADDR_પદાવલિ)
    mark_exp_read (exprv);

  /* If the expression is not of a type to which we cannot assign a line
     number, wrap the thing in a no-op NOP_EXPR.  */
  જો (DECL_P (પદાવલિ) || CONSTANT_CLASS_P (પદાવલિ))
    {
      પદાવલિ = build1 (NOP_પદાવલિ, વૃક્ષ_TYPE (પદાવલિ), પદાવલિ);
      SET_પદાવલિ_LOCATION (પદાવલિ, loc);
    }

  પાછા પદાવલિ;
}

/* Emit an expression as a statement.  LOC is the location of the
   expression.  */

વૃક્ષ
c_finish_પદાવલિ_stmt (location_t loc, વૃક્ષ પદાવલિ)
{
  જો (પદાવલિ)
    પાછા add_stmt (c_process_પદાવલિ_stmt (loc, પદાવલિ));
  નહીંતર
    પાછા ખાલી;
}

/* Do the opposite and emit a statement as an expression.  To begin,
   create a new binding level and return it.  */

વૃક્ષ
c_begin_stmt_પદાવલિ (શૂન્ય)
{
  વૃક્ષ ret;

  /* We must force a BLOCK for this level so that, if it is not expanded
     later, there is a way to turn off the entire subtree of blocks that
     are contained in it.  */
  keep_next_level ();
  ret = c_begin_compound_stmt (સાચું);

  c_bindings_start_stmt_પદાવલિ (c_switch_ઢગલો == ખાલી
			      ? ખાલી
			      : c_switch_ઢગલો->bindings);

  /* Mark the current statement list as belonging to a statement list.  */
  STATEMENT_LIST_STMT_પદાવલિ (ret) = 1;

  પાછા ret;
}

/* LOC is the location of the compound statement to which this body
   belongs.  */

વૃક્ષ
c_finish_stmt_પદાવલિ (location_t loc, વૃક્ષ body)
{
  વૃક્ષ last, type, tmp, val;
  વૃક્ષ *last_p;

  body = c_end_compound_stmt (loc, body, સાચું);

  c_bindings_end_stmt_પદાવલિ (c_switch_ઢગલો == ખાલી
			    ? ખાલી
			    : c_switch_ઢગલો->bindings);

  /* Locate the last statement in BODY.  See c_end_compound_stmt
     about always returning a BIND_EXPR.  */
  last_p = &BIND_પદાવલિ_BODY (body);
  last = BIND_પદાવલિ_BODY (body);

 continue_searching:
  જો (વૃક્ષ_CODE (last) == STATEMENT_LIST)
    {
      વૃક્ષ_stmt_iterator l = tsi_last (last);

      જ્યારે (!tsi_end_p (l) && વૃક્ષ_CODE (tsi_stmt (l)) == DEBUG_BEGIN_STMT)
	tsi_prev (&l);

      /* This can happen with degenerate cases like ({ }).  No value.  */
      જો (tsi_end_p (l))
	પાછા body;

      /* If we're supposed to generate side effects warnings, process
	 all of the statements except the last.  */
      જો (warn_unused_કિંમત || warn_unused_result)
	{
	  માટે (વૃક્ષ_stmt_iterator i = tsi_start (last);
	       tsi_stmt (i) != tsi_stmt (l); tsi_next (&i))
	    {
	      location_t tloc;
	      વૃક્ષ t = tsi_stmt (i);

	      tloc = પદાવલિ_HAS_LOCATION (t) ? પદાવલિ_LOCATION (t) : loc;
	      emit_side_effect_warnings (tloc, t);
	    }
	}
      last_p = tsi_stmt_ptr (l);
      last = *last_p;
    }

  /* If the end of the list is exception related, then the list was split
     by a call to push_cleanup.  Continue searching.  */
  જો (વૃક્ષ_CODE (last) == TRY_FINALLY_પદાવલિ
      || વૃક્ષ_CODE (last) == TRY_CATCH_પદાવલિ)
    {
      last_p = &વૃક્ષ_OPERAND (last, 0);
      last = *last_p;
      જાઓ continue_searching;
    }

  જો (last == error_mark_ગાંઠ)
    પાછા last;

  /* In the case that the BIND_EXPR is not necessary, return the
     expression out from inside it.  */
  જો ((last == BIND_પદાવલિ_BODY (body)
       /* Skip nested debug stmts.  */
       || last == પદાવલિ_first (BIND_પદાવલિ_BODY (body)))
      && BIND_પદાવલિ_VARS (body) == ખાલી)
    {
      /* Even if this looks constant, do not allow it in a constant
	 expression.  */
      last = c_wrap_maybe_const (last, સાચું);
      /* Do not warn if the return value of a statement expression is
	 unused.  */
      suppress_warning (last, OPT_Wunused);
      પાછા last;
    }

  /* Extract the type of said expression.  */
  type = વૃક્ષ_TYPE (last);

  /* If we're not returning a value at all, then the BIND_EXPR that
     we already have is a fine expression to return.  */
  જો (!type || VOID_TYPE_P (type))
    પાછા body;

  /* Now that we've located the expression containing the value, it seems
     silly to make voidify_wrapper_expr repeat the process.  Create a
     temporary of the appropriate type and stick it in a TARGET_EXPR.  */
  tmp = create_tmp_var_raw (type);

  /* Unwrap a no-op NOP_EXPR as added by c_finish_expr_stmt.  This avoids
     tree_expr_nonnegative_p giving up immediately.  */
  val = last;
  જો (વૃક્ષ_CODE (val) == NOP_પદાવલિ
      && વૃક્ષ_TYPE (val) == વૃક્ષ_TYPE (વૃક્ષ_OPERAND (val, 0)))
    val = વૃક્ષ_OPERAND (val, 0);

  *last_p = build2 (MODIFY_પદાવલિ, void_type_ગાંઠ, tmp, val);
  SET_પદાવલિ_LOCATION (*last_p, પદાવલિ_LOCATION (last));

  {
    વૃક્ષ t = build4 (TARGET_પદાવલિ, type, tmp, body, NULL_વૃક્ષ, NULL_વૃક્ષ);
    SET_પદાવલિ_LOCATION (t, loc);
    પાછા t;
  }
}

/* Begin and end compound statements.  This is as simple as pushing
   and popping new statement lists from the tree.  */

વૃક્ષ
c_begin_compound_stmt (તાર્કિક do_scope)
{
  વૃક્ષ stmt = ધકેલો_stmt_list ();
  જો (do_scope)
    ધકેલો_scope ();
  પાછા stmt;
}

/* End a compound statement.  STMT is the statement.  LOC is the
   location of the compound statement-- this is usually the location
   of the opening brace.  */

વૃક્ષ
c_end_compound_stmt (location_t loc, વૃક્ષ stmt, તાર્કિક do_scope)
{
  વૃક્ષ block = ખાલી;

  જો (do_scope)
    {
      જો (c_dialect_objc ())
	objc_clear_super_receiver ();
      block = કાઢો_scope ();
    }

  stmt = કાઢો_stmt_list (stmt);
  stmt = c_build_bind_પદાવલિ (loc, block, stmt);

  /* If this compound statement is nested immediately inside a statement
     expression, then force a BIND_EXPR to be created.  Otherwise we'll
     do the wrong thing for ({ { 1; } }) or ({ 1; { } }).  In particular,
     STATEMENT_LISTs merge, and thus we can lose track of what statement
     was really last.  */
  જો (building_stmt_list_p ()
      && STATEMENT_LIST_STMT_પદાવલિ (cur_stmt_list)
      && વૃક્ષ_CODE (stmt) != BIND_પદાવલિ)
    {
      stmt = build3 (BIND_પદાવલિ, void_type_ગાંઠ, ખાલી, stmt, ખાલી);
      વૃક્ષ_SIDE_EFFECTS (stmt) = 1;
      SET_પદાવલિ_LOCATION (stmt, loc);
    }

  પાછા stmt;
}

/* Queue a cleanup.  CLEANUP is an expression/statement to be executed
   when the current scope is exited.  EH_ONLY is true when this is not
   meant to apply to normal control flow transfer.  */

શૂન્ય
ધકેલો_cleanup (વૃક્ષ decl, વૃક્ષ cleanup, તાર્કિક eh_only)
{
  ગણના વૃક્ષ_code code;
  વૃક્ષ stmt, list;
  તાર્કિક stmt_પદાવલિ;

  code = eh_only ? TRY_CATCH_પદાવલિ : TRY_FINALLY_પદાવલિ;
  stmt = build_stmt (DECL_SOURCE_LOCATION (decl), code, ખાલી, cleanup);
  add_stmt (stmt);
  stmt_પદાવલિ = STATEMENT_LIST_STMT_પદાવલિ (cur_stmt_list);
  list = ધકેલો_stmt_list ();
  વૃક્ષ_OPERAND (stmt, 0) = list;
  STATEMENT_LIST_STMT_પદાવલિ (list) = stmt_પદાવલિ;
}

/* Build a vector comparison of ARG0 and ARG1 using CODE opcode
   into a value of TYPE type.  Comparison is done via VEC_COND_EXPR.  */

સ્થિર વૃક્ષ
build_vec_cmp (વૃક્ષ_code code, વૃક્ષ type,
	       વૃક્ષ arg0, વૃક્ષ arg1)
{
  વૃક્ષ zero_vec = build_zero_cst (type);
  વૃક્ષ minus_one_vec = build_minus_one_cst (type);
  વૃક્ષ cmp_type = truth_type_for (વૃક્ષ_TYPE (arg0));
  વૃક્ષ cmp = build2 (code, cmp_type, arg0, arg1);
  પાછા build3 (VEC_COND_પદાવલિ, type, cmp, minus_one_vec, zero_vec);
}

/* Possibly warn about an address of OP never being NULL in a comparison
   operation CODE involving null.  */

સ્થિર શૂન્ય
maybe_warn_for_null_address (location_t loc, વૃક્ષ op, વૃક્ષ_code code)
{
  /* Prevent warnings issued for macro expansion.  */
  જો (!warn_address
      || warning_suppressed_p (op, OPT_Waddress)
      || from_macro_expansion_at (loc))
    પાછા;

  જો (વૃક્ષ_CODE (op) == NOP_પદાવલિ)
    {
      /* Allow casts to intptr_t to suppress the warning.  */
      વૃક્ષ type = વૃક્ષ_TYPE (op);
      જો (વૃક્ષ_CODE (type) == INTEGER_TYPE)
	પાછા;
      op = વૃક્ષ_OPERAND (op, 0);
    }

  જો (વૃક્ષ_CODE (op) == POINTER_PLUS_પદાવલિ)
    {
      /* Allow a cast to void* to suppress the warning.  */
      વૃક્ષ type = વૃક્ષ_TYPE (વૃક્ષ_TYPE (op));
      જો (VOID_TYPE_P (type))
	પાછા;

      /* Adding any value to a null pointer, including zero, is undefined
	 in C.  This includes the expression &p[0] where p is the null
	 pointer, although &p[0] will have been folded to p by this point
	 and so not diagnosed.  */
      જો (code == EQ_પદાવલિ)
	warning_at (loc, OPT_Waddress,
		    "the comparison will always evaluate as %<false%> "
		    "for the pointer operand in %qE must not be NULL",
		    op);
      નહીંતર
	warning_at (loc, OPT_Waddress,
		    "the comparison will always evaluate as %<true%> "
		    "for the pointer operand in %qE must not be NULL",
		    op);

      પાછા;
    }

  જો (વૃક્ષ_CODE (op) != ADDR_પદાવલિ)
    પાછા;

  op = વૃક્ષ_OPERAND (op, 0);

  જો (વૃક્ષ_CODE (op) == IMAGPART_પદાવલિ
      || વૃક્ષ_CODE (op) == REALPART_પદાવલિ)
    {
      /* The address of either complex part may not be null.  */
      જો (code == EQ_પદાવલિ)
	warning_at (loc, OPT_Waddress,
		    "the comparison will always evaluate as %<false%> "
		    "for the address of %qE will never be NULL",
		    op);
      નહીંતર
	warning_at (loc, OPT_Waddress,
		    "the comparison will always evaluate as %<true%> "
		    "for the address of %qE will never be NULL",
		    op);
      પાછા;
    }

  /* Set to true in the loop below if OP dereferences is operand.
     In such a case the ultimate target need not be a decl for
     the null [in]equality test to be constant.  */
  તાર્કિક deref = ખોટું;

  /* Get the outermost array or object, or member.  */
  જ્યારે (handled_component_p (op))
    {
      જો (વૃક્ષ_CODE (op) == COMPONENT_REF)
	{
	  /* Get the member (its address is never null).  */
	  op = વૃક્ષ_OPERAND (op, 1);
	  તોડો;
	}

      /* Get the outer array/object to refer to in the warning.  */
      op = વૃક્ષ_OPERAND (op, 0);
      deref = સાચું;
    }

  જો ((!deref && !decl_with_nonnull_addr_p (op))
      || from_macro_expansion_at (loc))
    પાછા;

  તાર્કિક w;
  જો (code == EQ_પદાવલિ)
    w = warning_at (loc, OPT_Waddress,
		    "the comparison will always evaluate as %<false%> "
		    "for the address of %qE will never be NULL",
		    op);
  નહીંતર
    w = warning_at (loc, OPT_Waddress,
		    "the comparison will always evaluate as %<true%> "
		    "for the address of %qE will never be NULL",
		    op);

  જો (w && DECL_P (op))
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

વૃક્ષ
build_દ્વિઅંકી_op (location_t location, ગણના વૃક્ષ_code code,
		 વૃક્ષ orig_op0, વૃક્ષ orig_op1, તાર્કિક convert_p)
{
  વૃક્ષ type0, type1, orig_type0, orig_type1;
  વૃક્ષ eptype;
  ગણના વૃક્ષ_code code0, code1;
  વૃક્ષ op0, op1;
  વૃક્ષ ret = error_mark_ગાંઠ;
  અચલ અક્ષર *invalid_op_diag;
  તાર્કિક op0_int_operands, op1_int_operands;
  તાર્કિક int_const, int_const_or_overflow, int_operands;

  /* Expression code to give to the expression when it is built.
     Normally this is CODE, which is what the caller asked for,
     but in some special cases we change it.  */
  ગણના વૃક્ષ_code resultcode = code;

  /* Data type in which the computation is to be performed.
     In the simplest cases this is the common type of the arguments.  */
  વૃક્ષ result_type = ખાલી;

  /* When the computation is in excess precision, the type of the
     final EXCESS_PRECISION_EXPR.  */
  વૃક્ષ semantic_result_type = ખાલી;

  /* Nonzero means operands have already been type-converted
     in whatever way is necessary.
     Zero means they need to be converted to RESULT_TYPE.  */
  પૂર્ણાંક converted = 0;

  /* Nonzero means create the expression with this type, rather than
     RESULT_TYPE.  */
  વૃક્ષ build_type = NULL_વૃક્ષ;

  /* Nonzero means after finally constructing the expression
     convert it to this type.  */
  વૃક્ષ final_type = NULL_વૃક્ષ;

  /* Nonzero if this is an operation like MIN or MAX which can
     safely be computed in short if both args are promoted shorts.
     Also implies COMMON.
     -1 indicates a bitwise operation; this makes a difference
     in the exact conditions for when it is safe to do the operation
     in a narrower mode.  */
  પૂર્ણાંક shorten = 0;

  /* Nonzero if this is a comparison operation;
     if both args are promoted shorts, compare the original shorts.
     Also implies COMMON.  */
  પૂર્ણાંક short_compare = 0;

  /* Nonzero if this is a right-shift operation, which can be computed on the
     original short and then promoted if the operand is a promoted short.  */
  પૂર્ણાંક short_shift = 0;

  /* Nonzero means set RESULT_TYPE to the common type of the args.  */
  પૂર્ણાંક common = 0;

  /* True means types are compatible as far as ObjC is concerned.  */
  તાર્કિક objc_ok;

  /* True means this is an arithmetic operation that may need excess
     precision.  */
  તાર્કિક may_need_excess_precision;

  /* True means this is a boolean operation that converts both its
     operands to truth-values.  */
  તાર્કિક boolean_op = ખોટું;

  /* Remember whether we're doing / or %.  */
  તાર્કિક doing_div_or_mod = ખોટું;

  /* Remember whether we're doing << or >>.  */
  તાર્કિક doing_shift = ખોટું;

  /* Tree holding instrumentation expression.  */
  વૃક્ષ instrument_પદાવલિ = ખાલી;

  જો (location == UNKNOWN_LOCATION)
    location = આગત_location;

  op0 = orig_op0;
  op1 = orig_op1;

  op0_int_operands = પદાવલિ_INT_CONST_OPERANDS (orig_op0);
  જો (op0_int_operands)
    op0 = remove_c_maybe_const_પદાવલિ (op0);
  op1_int_operands = પદાવલિ_INT_CONST_OPERANDS (orig_op1);
  જો (op1_int_operands)
    op1 = remove_c_maybe_const_પદાવલિ (op1);
  int_operands = (op0_int_operands && op1_int_operands);
  જો (int_operands)
    {
      int_const_or_overflow = (વૃક્ષ_CODE (orig_op0) == INTEGER_CST
			       && વૃક્ષ_CODE (orig_op1) == INTEGER_CST);
      int_const = (int_const_or_overflow
		   && !વૃક્ષ_OVERFLOW (orig_op0)
		   && !વૃક્ષ_OVERFLOW (orig_op1));
    }
  નહીંતર
    int_const = int_const_or_overflow = ખોટું;

  /* Do not apply default conversion in mixed vector/scalar expression.  */
  જો (convert_p
      && VECTOR_TYPE_P (વૃક્ષ_TYPE (op0)) == VECTOR_TYPE_P (વૃક્ષ_TYPE (op1)))
    {
      op0 = default_conversion (op0);
      op1 = default_conversion (op1);
    }

  orig_type0 = type0 = વૃક્ષ_TYPE (op0);

  orig_type1 = type1 = વૃક્ષ_TYPE (op1);

  /* The expression codes of the data types of the arguments tell us
     whether the arguments are integers, floating, pointers, etc.  */
  code0 = વૃક્ષ_CODE (type0);
  code1 = વૃક્ષ_CODE (type1);

  /* Strip NON_LVALUE_EXPRs, etc., since we aren't using as an lvalue.  */
  STRIP_TYPE_NOPS (op0);
  STRIP_TYPE_NOPS (op1);

  /* If an error was already reported for one of the arguments,
     avoid reporting another error.  */

  જો (code0 == ERROR_MARK || code1 == ERROR_MARK)
    પાછા error_mark_ગાંઠ;

  જો (code0 == POINTER_TYPE
      && reject_gcc_builtin (op0, પદાવલિ_LOCATION (orig_op0)))
    પાછા error_mark_ગાંઠ;

  જો (code1 == POINTER_TYPE
      && reject_gcc_builtin (op1, પદાવલિ_LOCATION (orig_op1)))
    પાછા error_mark_ગાંઠ;

  જો ((invalid_op_diag
       = targetm.invalid_દ્વિઅંકી_op (code, type0, type1)))
    {
      error_at (location, invalid_op_diag);
      પાછા error_mark_ગાંઠ;
    }

  પસંદગી (code)
    {
    સ્થિતિ PLUS_પદાવલિ:
    સ્થિતિ MINUS_પદાવલિ:
    સ્થિતિ MULT_પદાવલિ:
    સ્થિતિ TRUNC_DIV_પદાવલિ:
    સ્થિતિ CEIL_DIV_પદાવલિ:
    સ્થિતિ FLOOR_DIV_પદાવલિ:
    સ્થિતિ ROUND_DIV_પદાવલિ:
    સ્થિતિ EXACT_DIV_પદાવલિ:
      may_need_excess_precision = સાચું;
      તોડો;

    સ્થિતિ EQ_પદાવલિ:
    સ્થિતિ NE_પદાવલિ:
    સ્થિતિ LE_પદાવલિ:
    સ્થિતિ GE_પદાવલિ:
    સ્થિતિ LT_પદાવલિ:
    સ્થિતિ GT_પદાવલિ:
      /* Excess precision for implicit conversions of integers to
	 floating point in C11 and later.  */
      may_need_excess_precision = (flag_isoc11
				   && (ANY_INTEGRAL_TYPE_P (type0)
				       || ANY_INTEGRAL_TYPE_P (type1)));
      તોડો;

    મૂળભૂત:
      may_need_excess_precision = ખોટું;
      તોડો;
    }
  જો (વૃક્ષ_CODE (op0) == EXCESS_PRECISION_પદાવલિ)
    {
      op0 = વૃક્ષ_OPERAND (op0, 0);
      type0 = વૃક્ષ_TYPE (op0);
    }
  નહીંતર જો (may_need_excess_precision
	   && (eptype = excess_precision_type (type0)) != NULL_વૃક્ષ)
    {
      type0 = eptype;
      op0 = convert (eptype, op0);
    }
  જો (વૃક્ષ_CODE (op1) == EXCESS_PRECISION_પદાવલિ)
    {
      op1 = વૃક્ષ_OPERAND (op1, 0);
      type1 = વૃક્ષ_TYPE (op1);
    }
  નહીંતર જો (may_need_excess_precision
	   && (eptype = excess_precision_type (type1)) != NULL_વૃક્ષ)
    {
      type1 = eptype;
      op1 = convert (eptype, op1);
    }

  objc_ok = objc_compare_types (type0, type1, -3, NULL_વૃક્ષ);

  /* In case when one of the operands of the binary operation is
     a vector and another is a scalar -- convert scalar to vector.  */
  જો ((gnu_vector_type_p (type0) && code1 != VECTOR_TYPE)
      || (gnu_vector_type_p (type1) && code0 != VECTOR_TYPE))
    {
      ગણના stv_conv convert_flag = scalar_to_vector (location, code, orig_op0,
						     orig_op1, સાચું);

      પસંદગી (convert_flag)
	{
	  સ્થિતિ stv_error:
	    પાછા error_mark_ગાંઠ;
	  સ્થિતિ stv_firstarg:
	    {
              તાર્કિક maybe_const = સાચું;
              વૃક્ષ sc;
              sc = c_fully_fold (op0, ખોટું, &maybe_const);
              sc = save_પદાવલિ (sc);
              sc = convert (વૃક્ષ_TYPE (type1), sc);
              op0 = build_vector_from_val (type1, sc);
              જો (!maybe_const)
                op0 = c_wrap_maybe_const (op0, સાચું);
              orig_type0 = type0 = વૃક્ષ_TYPE (op0);
              code0 = વૃક્ષ_CODE (type0);
              converted = 1;
              તોડો;
	    }
	  સ્થિતિ stv_secondarg:
	    {
	      તાર્કિક maybe_const = સાચું;
	      વૃક્ષ sc;
	      sc = c_fully_fold (op1, ખોટું, &maybe_const);
	      sc = save_પદાવલિ (sc);
	      sc = convert (વૃક્ષ_TYPE (type0), sc);
	      op1 = build_vector_from_val (type0, sc);
	      જો (!maybe_const)
		op1 = c_wrap_maybe_const (op1, સાચું);
	      orig_type1 = type1 = વૃક્ષ_TYPE (op1);
	      code1 = વૃક્ષ_CODE (type1);
	      converted = 1;
	      તોડો;
	    }
	  મૂળભૂત:
	    તોડો;
	}
    }

  પસંદગી (code)
    {
    સ્થિતિ PLUS_પદાવલિ:
      /* Handle the pointer + int case.  */
      જો (code0 == POINTER_TYPE
	  && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  ret = pointer_int_sum (location, PLUS_પદાવલિ, op0, op1);
	  જાઓ return_build_દ્વિઅંકી_op;
	}
      નહીંતર જો (code1 == POINTER_TYPE
	       && (code0 == INTEGER_TYPE || code0 == BITINT_TYPE))
	{
	  ret = pointer_int_sum (location, PLUS_પદાવલિ, op1, op0);
	  જાઓ return_build_દ્વિઅંકી_op;
	}
      નહીંતર
	common = 1;
      તોડો;

    સ્થિતિ MINUS_પદાવલિ:
      /* Subtraction of two similar pointers.
	 We must subtract them as integers, then divide by object size.  */
      જો (code0 == POINTER_TYPE && code1 == POINTER_TYPE
	  && comp_target_types (location, type0, type1))
	{
	  ret = pointer_diff (location, op0, op1, &instrument_પદાવલિ);
	  જાઓ return_build_દ્વિઅંકી_op;
	}
      /* Handle pointer minus int.  Just like pointer plus int.  */
      નહીંતર જો (code0 == POINTER_TYPE
	       && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  ret = pointer_int_sum (location, MINUS_પદાવલિ, op0, op1);
	  જાઓ return_build_દ્વિઅંકી_op;
	}
      નહીંતર
	common = 1;
      તોડો;

    સ્થિતિ MULT_પદાવલિ:
      common = 1;
      તોડો;

    સ્થિતિ TRUNC_DIV_પદાવલિ:
    સ્થિતિ CEIL_DIV_પદાવલિ:
    સ્થિતિ FLOOR_DIV_પદાવલિ:
    સ્થિતિ ROUND_DIV_પદાવલિ:
    સ્થિતિ EXACT_DIV_પદાવલિ:
      doing_div_or_mod = સાચું;
      warn_for_div_by_zero (location, op1);

      જો ((code0 == INTEGER_TYPE || code0 == REAL_TYPE
	   || code0 == FIXED_POINT_TYPE || code0 == BITINT_TYPE
	   || code0 == COMPLEX_TYPE
	   || gnu_vector_type_p (type0))
	  && (code1 == INTEGER_TYPE || code1 == REAL_TYPE
	      || code1 == FIXED_POINT_TYPE || code1 == BITINT_TYPE
	      || code1 == COMPLEX_TYPE
	      || gnu_vector_type_p (type1)))
	{
	  ગણના વૃક્ષ_code tcode0 = code0, tcode1 = code1;

	  જો (code0 == COMPLEX_TYPE || code0 == VECTOR_TYPE)
	    tcode0 = વૃક્ષ_CODE (વૃક્ષ_TYPE (વૃક્ષ_TYPE (op0)));
	  જો (code1 == COMPLEX_TYPE || code1 == VECTOR_TYPE)
	    tcode1 = વૃક્ષ_CODE (વૃક્ષ_TYPE (વૃક્ષ_TYPE (op1)));

	  જો (!(((tcode0 == INTEGER_TYPE || tcode0 == BITINT_TYPE
		  || (tcode0 == ENUMERAL_TYPE && code0 == VECTOR_TYPE))
		 && (tcode1 == INTEGER_TYPE || tcode1 == BITINT_TYPE
		     || (tcode1 == ENUMERAL_TYPE && code1 == VECTOR_TYPE)))
		|| (tcode0 == FIXED_POINT_TYPE && tcode1 == FIXED_POINT_TYPE)))
	    resultcode = RDIV_પદાવલિ;
	  નહીંતર
	    /* Although it would be tempting to shorten always here, that
	       loses on some targets, since the modulo instruction is
	       undefined if the quotient can't be represented in the
	       computation mode.  We shorten only if unsigned or if
	       dividing by something we know != -1.  */
	    shorten = may_shorten_divmod (op0, op1);
	  common = 1;
	}
      તોડો;

    સ્થિતિ BIT_AND_પદાવલિ:
    સ્થિતિ BIT_IOR_પદાવલિ:
    સ્થિતિ BIT_XOR_પદાવલિ:
      જો ((code0 == INTEGER_TYPE || code0 == BITINT_TYPE)
	  && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	shorten = -1;
      /* Allow vector types which are not floating point types.   */
      નહીંતર જો (gnu_vector_type_p (type0)
	       && gnu_vector_type_p (type1)
	       && !VECTOR_FLOAT_TYPE_P (type0)
	       && !VECTOR_FLOAT_TYPE_P (type1))
	common = 1;
      તોડો;

    સ્થિતિ TRUNC_MOD_પદાવલિ:
    સ્થિતિ FLOOR_MOD_પદાવલિ:
      doing_div_or_mod = સાચું;
      warn_for_div_by_zero (location, op1);

      જો (gnu_vector_type_p (type0)
	  && gnu_vector_type_p (type1)
	  && વૃક્ષ_CODE (વૃક્ષ_TYPE (type0)) == INTEGER_TYPE
	  && વૃક્ષ_CODE (વૃક્ષ_TYPE (type1)) == INTEGER_TYPE)
	common = 1;
      નહીંતર જો ((code0 == INTEGER_TYPE || code0 == BITINT_TYPE)
	       && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  /* Although it would be tempting to shorten always here, that loses
	     on some targets, since the modulo instruction is undefined if the
	     quotient can't be represented in the computation mode.  We shorten
	     only if unsigned or if dividing by something we know != -1.  */
	  shorten = may_shorten_divmod (op0, op1);
	  common = 1;
	}
      તોડો;

    સ્થિતિ TRUTH_ANDIF_પદાવલિ:
    સ્થિતિ TRUTH_ORIF_પદાવલિ:
    સ્થિતિ TRUTH_AND_પદાવલિ:
    સ્થિતિ TRUTH_OR_પદાવલિ:
    સ્થિતિ TRUTH_XOR_પદાવલિ:
      જો ((code0 == INTEGER_TYPE || code0 == POINTER_TYPE
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
	  result_type = integer_type_ગાંઠ;
	  જો (op0_int_operands)
	    {
	      op0 = c_objc_common_truthvalue_conversion (location, orig_op0);
	      op0 = remove_c_maybe_const_પદાવલિ (op0);
	    }
	  નહીંતર
	    op0 = c_objc_common_truthvalue_conversion (location, op0);
	  જો (op1_int_operands)
	    {
	      op1 = c_objc_common_truthvalue_conversion (location, orig_op1);
	      op1 = remove_c_maybe_const_પદાવલિ (op1);
	    }
	  નહીંતર
	    op1 = c_objc_common_truthvalue_conversion (location, op1);
	  converted = 1;
	  boolean_op = સાચું;
	}
      જો (code == TRUTH_ANDIF_પદાવલિ)
	{
	  int_const_or_overflow = (int_operands
				   && વૃક્ષ_CODE (orig_op0) == INTEGER_CST
				   && (op0 == truthvalue_false_ગાંઠ
				       || વૃક્ષ_CODE (orig_op1) == INTEGER_CST));
	  int_const = (int_const_or_overflow
		       && !વૃક્ષ_OVERFLOW (orig_op0)
		       && (op0 == truthvalue_false_ગાંઠ
			   || !વૃક્ષ_OVERFLOW (orig_op1)));
	}
      નહીંતર જો (code == TRUTH_ORIF_પદાવલિ)
	{
	  int_const_or_overflow = (int_operands
				   && વૃક્ષ_CODE (orig_op0) == INTEGER_CST
				   && (op0 == truthvalue_true_ગાંઠ
				       || વૃક્ષ_CODE (orig_op1) == INTEGER_CST));
	  int_const = (int_const_or_overflow
		       && !વૃક્ષ_OVERFLOW (orig_op0)
		       && (op0 == truthvalue_true_ગાંઠ
			   || !વૃક્ષ_OVERFLOW (orig_op1)));
	}
      તોડો;

      /* Shift operations: result has same type as first operand;
	 always convert second operand to int.
	 Also set SHORT_SHIFT if shifting rightward.  */

    સ્થિતિ RSHIFT_પદાવલિ:
      જો (gnu_vector_type_p (type0)
	  && gnu_vector_type_p (type1)
	  && વૃક્ષ_CODE (વૃક્ષ_TYPE (type0)) == INTEGER_TYPE
	  && વૃક્ષ_CODE (વૃક્ષ_TYPE (type1)) == INTEGER_TYPE
	  && known_eq (TYPE_VECTOR_SUBPARTS (type0),
		       TYPE_VECTOR_SUBPARTS (type1)))
	{
	  result_type = type0;
	  converted = 1;
	}
      નહીંતર જો ((code0 == INTEGER_TYPE || code0 == FIXED_POINT_TYPE
		|| code0 == BITINT_TYPE
		|| (gnu_vector_type_p (type0)
		    && વૃક્ષ_CODE (વૃક્ષ_TYPE (type0)) == INTEGER_TYPE))
	       && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  doing_shift = સાચું;
	  જો (વૃક્ષ_CODE (op1) == INTEGER_CST)
	    {
	      જો (વૃક્ષ_int_cst_sgn (op1) < 0)
		{
		  int_const = ખોટું;
		  જો (c_inhibit_evaluation_warnings == 0)
		    warning_at (location, OPT_Wshift_ગણતરી_negative,
				"right shift count is negative");
		}
	      નહીંતર જો (code0 == VECTOR_TYPE)
		{
		  જો (compare_વૃક્ષ_int (op1,
					TYPE_PRECISION (વૃક્ષ_TYPE (type0)))
		      >= 0)
		    {
		      int_const = ખોટું;
		      જો (c_inhibit_evaluation_warnings == 0)
			warning_at (location, OPT_Wshift_ગણતરી_overflow,
				    "right shift count >= width of vector element");
		    }
		}
	      નહીંતર
		{
		  જો (!integer_zerop (op1))
		    short_shift = 1;

		  જો (compare_વૃક્ષ_int (op1, TYPE_PRECISION (type0)) >= 0)
		    {
		      int_const = ખોટું;
		      જો (c_inhibit_evaluation_warnings == 0)
			warning_at (location, OPT_Wshift_ગણતરી_overflow,
				    "right shift count >= width of type");
		    }
		}
	    }

	  /* Use the type of the value to be shifted.  */
	  result_type = type0;
	  /* Avoid converting op1 to result_type later.  */
	  converted = 1;
	}
      તોડો;

    સ્થિતિ LSHIFT_પદાવલિ:
      જો (gnu_vector_type_p (type0)
	  && gnu_vector_type_p (type1)
	  && વૃક્ષ_CODE (વૃક્ષ_TYPE (type0)) == INTEGER_TYPE
	  && વૃક્ષ_CODE (વૃક્ષ_TYPE (type1)) == INTEGER_TYPE
	  && known_eq (TYPE_VECTOR_SUBPARTS (type0),
		       TYPE_VECTOR_SUBPARTS (type1)))
	{
	  result_type = type0;
	  converted = 1;
	}
      નહીંતર જો ((code0 == INTEGER_TYPE || code0 == FIXED_POINT_TYPE
		|| code0 == BITINT_TYPE
		|| (gnu_vector_type_p (type0)
		    && વૃક્ષ_CODE (વૃક્ષ_TYPE (type0)) == INTEGER_TYPE))
	       && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  doing_shift = સાચું;
	  જો (વૃક્ષ_CODE (op0) == INTEGER_CST
	      && વૃક્ષ_int_cst_sgn (op0) < 0
	      && !TYPE_OVERFLOW_WRAPS (type0))
	    {
	      /* Don't reject a left shift of a negative value in a context
		 where a constant expression is needed in C90.  */
	      જો (flag_isoc99)
		int_const = ખોટું;
	      જો (c_inhibit_evaluation_warnings == 0)
		warning_at (location, OPT_Wshift_negative_કિંમત,
			    "left shift of negative value");
	    }
	  જો (વૃક્ષ_CODE (op1) == INTEGER_CST)
	    {
	      જો (વૃક્ષ_int_cst_sgn (op1) < 0)
		{
		  int_const = ખોટું;
		  જો (c_inhibit_evaluation_warnings == 0)
		    warning_at (location, OPT_Wshift_ગણતરી_negative,
				"left shift count is negative");
		}
	      નહીંતર જો (code0 == VECTOR_TYPE)
		{
		  જો (compare_વૃક્ષ_int (op1,
					TYPE_PRECISION (વૃક્ષ_TYPE (type0)))
		      >= 0)
		    {
		      int_const = ખોટું;
		      જો (c_inhibit_evaluation_warnings == 0)
			warning_at (location, OPT_Wshift_ગણતરી_overflow,
				    "left shift count >= width of vector element");
		    }
		}
	      નહીંતર જો (compare_વૃક્ષ_int (op1, TYPE_PRECISION (type0)) >= 0)
		{
		  int_const = ખોટું;
		  જો (c_inhibit_evaluation_warnings == 0)
		    warning_at (location, OPT_Wshift_ગણતરી_overflow,
				"left shift count >= width of type");
		}
	      નહીંતર જો (વૃક્ષ_CODE (op0) == INTEGER_CST
		       && maybe_warn_shift_overflow (location, op0, op1)
		       && flag_isoc99)
		int_const = ખોટું;
	    }

	  /* Use the type of the value to be shifted.  */
	  result_type = type0;
	  /* Avoid converting op1 to result_type later.  */
	  converted = 1;
	}
      તોડો;

    સ્થિતિ EQ_પદાવલિ:
    સ્થિતિ NE_પદાવલિ:
      જો (gnu_vector_type_p (type0) && gnu_vector_type_p (type1))
        {
          વૃક્ષ intt;
	  જો (!vector_types_compatible_elements_p (type0, type1))
            {
              error_at (location, "comparing vectors with different "
                                  "element types");
              પાછા error_mark_ગાંઠ;
            }

	  જો (maybe_ne (TYPE_VECTOR_SUBPARTS (type0),
			TYPE_VECTOR_SUBPARTS (type1)))
            {
              error_at (location, "comparing vectors with different "
                                  "number of elements");
              પાછા error_mark_ગાંઠ;
            }

	  /* It's not precisely specified how the usual arithmetic
	     conversions apply to the vector types.  Here, we use
	     the unsigned type if one of the operands is signed and
	     the other one is unsigned.  */
	  જો (TYPE_UNSIGNED (type0) != TYPE_UNSIGNED (type1))
	    {
	      જો (!TYPE_UNSIGNED (type0))
		op0 = build1 (VIEW_CONVERT_પદાવલિ, type1, op0);
	      નહીંતર
		op1 = build1 (VIEW_CONVERT_પદાવલિ, type0, op1);
	      warning_at (location, OPT_Wsign_compare, "comparison between "
			  "types %qT and %qT", type0, type1);
	    }

          /* Always construct signed integer vector type.  */
	  જો (VECTOR_BOOLEAN_TYPE_P (type0) && VECTOR_BOOLEAN_TYPE_P (type1))
	    result_type = type0;
	  નહીંતર
	    {
	      auto nelts = TYPE_VECTOR_SUBPARTS (type0);

	      intt = c_common_type_for_size (GET_MODE_BITSIZE
					     (SCALAR_TYPE_MODE
						(વૃક્ષ_TYPE (type0))), 0);
	      જો (!intt)
		{
		  error_at (location, "could not find an integer type "
				      "of the same size as %qT",
			    વૃક્ષ_TYPE (type0));
		  પાછા error_mark_ગાંઠ;
		}
	      result_type = build_opaque_vector_type (intt, nelts);
	    }
          converted = 1;
	  ret = build_vec_cmp (resultcode, result_type, op0, op1);
	  જાઓ return_build_દ્વિઅંકી_op;
        }
      જો (FLOAT_TYPE_P (type0) || FLOAT_TYPE_P (type1))
	warning_at (location,
		    OPT_Wfloat_equal,
		    "comparing floating-point with %<==%> or %<!=%> is unsafe");
      /* Result of comparison is always int,
	 but don't convert the args to int!  */
      build_type = integer_type_ગાંઠ;
      જો ((code0 == INTEGER_TYPE || code0 == REAL_TYPE || code0 == BITINT_TYPE
	   || code0 == FIXED_POINT_TYPE || code0 == COMPLEX_TYPE)
	  && (code1 == INTEGER_TYPE || code1 == REAL_TYPE
	      || code1 == BITINT_TYPE
	      || code1 == FIXED_POINT_TYPE || code1 == COMPLEX_TYPE))
	short_compare = 1;
      નહીંતર જો (code0 == POINTER_TYPE
	       && (code1 == NULLPTR_TYPE
		   || null_pointer_constant_p (orig_op1)))
	{
	  maybe_warn_for_null_address (location, op0, code);
	  result_type = type0;
	}
      નહીંતર જો (code1 == POINTER_TYPE
	       && (code0 == NULLPTR_TYPE
		   || null_pointer_constant_p (orig_op0)))
	{
	  maybe_warn_for_null_address (location, op1, code);
	  result_type = type1;
	}
      નહીંતર જો (code0 == POINTER_TYPE && code1 == POINTER_TYPE)
	{
	  વૃક્ષ tt0 = વૃક્ષ_TYPE (type0);
	  વૃક્ષ tt1 = વૃક્ષ_TYPE (type1);
	  addr_space_t as0 = TYPE_ADDR_SPACE (tt0);
	  addr_space_t as1 = TYPE_ADDR_SPACE (tt1);
	  addr_space_t as_common = ADDR_SPACE_GENERIC;

	  /* Anything compares with void *.  void * compares with anything.
	     Otherwise, the targets must be compatible
	     and both must be object or both incomplete.  */
	  જો (comp_target_types (location, type0, type1))
	    result_type = common_pointer_type (type0, type1, NULL_વૃક્ષ);
	  નહીંતર જો (!addr_space_superset (as0, as1, &as_common))
	    {
	      error_at (location, "comparison of pointers to "
			"disjoint address spaces");
	      પાછા error_mark_ગાંઠ;
	    }
	  નહીંતર જો (VOID_TYPE_P (tt0) && !TYPE_ATOMIC (tt0))
	    {
	      જો (pedantic && વૃક્ષ_CODE (tt1) == FUNCTION_TYPE)
		pedwarn (location, OPT_Wpedantic, "ISO C forbids "
			 "comparison of %<void *%> with function pointer");
	    }
	  નહીંતર જો (VOID_TYPE_P (tt1) && !TYPE_ATOMIC (tt1))
	    {
	      જો (pedantic && વૃક્ષ_CODE (tt0) == FUNCTION_TYPE)
		pedwarn (location, OPT_Wpedantic, "ISO C forbids "
			 "comparison of %<void *%> with function pointer");
	    }
	  નહીંતર
	    /* Avoid warning about the volatile ObjC EH puts on decls.  */
	    જો (!objc_ok)
	      pedwarn (location, OPT_Wcompare_distinct_pointer_types,
		       "comparison of distinct pointer types lacks a cast");

	  જો (result_type == NULL_વૃક્ષ)
	    {
	      પૂર્ણાંક qual = ENCODE_QUAL_ADDR_SPACE (as_common);
	      result_type = c_build_pointer_type
			      (c_build_qualified_type (void_type_ગાંઠ, qual));
	    }
	}
      નહીંતર જો (code0 == POINTER_TYPE
	       && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  result_type = type0;
	  pedwarn (location, 0, "comparison between pointer and integer");
	}
      નહીંતર જો ((code0 == INTEGER_TYPE || code0 == BITINT_TYPE)
	       && code1 == POINTER_TYPE)
	{
	  result_type = type1;
	  pedwarn (location, 0, "comparison between pointer and integer");
	}
      /* 6.5.9: One of the following shall hold:
	 -- both operands have type nullptr_t;  */
      નહીંતર જો (code0 == NULLPTR_TYPE && code1 == NULLPTR_TYPE)
	{
	  result_type = nullptr_type_ગાંઠ;
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
      નહીંતર જો (code0 == NULLPTR_TYPE && null_pointer_constant_p (orig_op1))
	result_type = (INTEGRAL_TYPE_P (type1)
		       ? c_build_pointer_type (type1) : type1);
      નહીંતર જો (code1 == NULLPTR_TYPE && null_pointer_constant_p (orig_op0))
	result_type = (INTEGRAL_TYPE_P (type0)
		       ? c_build_pointer_type (type0) : type0);
      જો ((C_BOOLEAN_TYPE_P (વૃક્ષ_TYPE (orig_op0))
	   || truth_કિંમત_p (વૃક્ષ_CODE (orig_op0)))
	  ^ (C_BOOLEAN_TYPE_P (વૃક્ષ_TYPE (orig_op1))
	     || truth_કિંમત_p (વૃક્ષ_CODE (orig_op1))))
	maybe_warn_bool_compare (location, code, orig_op0, orig_op1);
      તોડો;

    સ્થિતિ LE_પદાવલિ:
    સ્થિતિ GE_પદાવલિ:
    સ્થિતિ LT_પદાવલિ:
    સ્થિતિ GT_પદાવલિ:
      જો (gnu_vector_type_p (type0) && gnu_vector_type_p (type1))
        {
          વૃક્ષ intt;
	  જો (!vector_types_compatible_elements_p (type0, type1))
            {
              error_at (location, "comparing vectors with different "
                                  "element types");
              પાછા error_mark_ગાંઠ;
            }

	  જો (maybe_ne (TYPE_VECTOR_SUBPARTS (type0),
			TYPE_VECTOR_SUBPARTS (type1)))
            {
              error_at (location, "comparing vectors with different "
                                  "number of elements");
              પાછા error_mark_ગાંઠ;
            }

	  /* It's not precisely specified how the usual arithmetic
	     conversions apply to the vector types.  Here, we use
	     the unsigned type if one of the operands is signed and
	     the other one is unsigned.  */
	  જો (TYPE_UNSIGNED (type0) != TYPE_UNSIGNED (type1))
	    {
	      જો (!TYPE_UNSIGNED (type0))
		op0 = build1 (VIEW_CONVERT_પદાવલિ, type1, op0);
	      નહીંતર
		op1 = build1 (VIEW_CONVERT_પદાવલિ, type0, op1);
	      warning_at (location, OPT_Wsign_compare, "comparison between "
			  "types %qT and %qT", type0, type1);
	    }

          /* Always construct signed integer vector type.  */
          intt = c_common_type_for_size (GET_MODE_BITSIZE
					 (SCALAR_TYPE_MODE
					  (વૃક્ષ_TYPE (type0))), 0);
	  જો (!intt)
	    {
	      error_at (location, "could not find an integer type "
				  "of the same size as %qT",
			વૃક્ષ_TYPE (type0));
	      પાછા error_mark_ગાંઠ;
	    }
          result_type = build_opaque_vector_type (intt,
						  TYPE_VECTOR_SUBPARTS (type0));
          converted = 1;
	  ret = build_vec_cmp (resultcode, result_type, op0, op1);
	  જાઓ return_build_દ્વિઅંકી_op;
        }
      build_type = integer_type_ગાંઠ;
      જો ((code0 == INTEGER_TYPE || code0 == REAL_TYPE
	   || code0 == BITINT_TYPE || code0 == FIXED_POINT_TYPE)
	  && (code1 == INTEGER_TYPE || code1 == REAL_TYPE
	      || code1 == BITINT_TYPE || code1 == FIXED_POINT_TYPE))
	short_compare = 1;
      નહીંતર જો (code0 == POINTER_TYPE && code1 == POINTER_TYPE)
	{
	  addr_space_t as0 = TYPE_ADDR_SPACE (વૃક્ષ_TYPE (type0));
	  addr_space_t as1 = TYPE_ADDR_SPACE (વૃક્ષ_TYPE (type1));
	  addr_space_t as_common;

	  જો (comp_target_types (location, type0, type1))
	    {
	      result_type = common_pointer_type (type0, type1, NULL_વૃક્ષ);
	      જો (!COMPLETE_TYPE_P (વૃક્ષ_TYPE (type0))
		  != !COMPLETE_TYPE_P (વૃક્ષ_TYPE (type1)))
		pedwarn_c99 (location, OPT_Wpedantic,
			     "comparison of complete and incomplete pointers");
	      નહીંતર જો (વૃક્ષ_CODE (વૃક્ષ_TYPE (type0)) == FUNCTION_TYPE)
		pedwarn (location, OPT_Wpedantic, "ISO C forbids "
			 "ordered comparisons of pointers to functions");
	      નહીંતર જો (null_pointer_constant_p (orig_op0)
		       || null_pointer_constant_p (orig_op1))
		warning_at (location, OPT_Wextra,
			    "ordered comparison of pointer with null pointer");

	    }
	  નહીંતર જો (!addr_space_superset (as0, as1, &as_common))
	    {
	      error_at (location, "comparison of pointers to "
			"disjoint address spaces");
	      પાછા error_mark_ગાંઠ;
	    }
	  નહીંતર
	    {
	      પૂર્ણાંક qual = ENCODE_QUAL_ADDR_SPACE (as_common);
	      result_type = c_build_pointer_type
			      (c_build_qualified_type (void_type_ગાંઠ, qual));
              pedwarn (location, OPT_Wcompare_distinct_pointer_types,
                       "comparison of distinct pointer types lacks a cast");
	    }
	}
      નહીંતર જો (code0 == POINTER_TYPE && null_pointer_constant_p (orig_op1))
	{
	  result_type = type0;
	  જો (pedantic)
	    pedwarn (location, OPT_Wpedantic,
		     "ordered comparison of pointer with integer zero");
	  નહીંતર જો (extra_warnings)
	    warning_at (location, OPT_Wextra,
			"ordered comparison of pointer with integer zero");
	}
      નહીંતર જો (code1 == POINTER_TYPE && null_pointer_constant_p (orig_op0))
	{
	  result_type = type1;
	  જો (pedantic)
	    pedwarn (location, OPT_Wpedantic,
		     "ordered comparison of pointer with integer zero");
	  નહીંતર જો (extra_warnings)
	    warning_at (location, OPT_Wextra,
			"ordered comparison of pointer with integer zero");
	}
      નહીંતર જો (code0 == POINTER_TYPE
	       && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  result_type = type0;
	  pedwarn (location, 0, "comparison between pointer and integer");
	}
      નહીંતર જો ((code0 == INTEGER_TYPE || code0 == BITINT_TYPE)
	       && code1 == POINTER_TYPE)
	{
	  result_type = type1;
	  pedwarn (location, 0, "comparison between pointer and integer");
	}

      જો ((code0 == POINTER_TYPE || code1 == POINTER_TYPE)
	  && current_function_decl != NULL_વૃક્ષ
	  && sanitize_flags_p (SANITIZE_POINTER_COMPARE))
	{
	  op0 = save_પદાવલિ (c_fully_fold (op0, ખોટું, ખાલી));
	  op1 = save_પદાવલિ (c_fully_fold (op1, ખોટું, ખાલી));

	  વૃક્ષ tt = builtin_decl_explicit (BUILT_IN_ASAN_POINTER_COMPARE);
	  instrument_પદાવલિ = build_call_પદાવલિ_loc (location, tt, 2, op0, op1);
	}

      જો ((C_BOOLEAN_TYPE_P (વૃક્ષ_TYPE (orig_op0))
	   || truth_કિંમત_p (વૃક્ષ_CODE (orig_op0)))
	  ^ (C_BOOLEAN_TYPE_P (વૃક્ષ_TYPE (orig_op1))
	     || truth_કિંમત_p (વૃક્ષ_CODE (orig_op1))))
	maybe_warn_bool_compare (location, code, orig_op0, orig_op1);
      તોડો;

    સ્થિતિ MIN_પદાવલિ:
    સ્થિતિ MAX_પદાવલિ:
      /* Used for OpenMP atomics.  */
      gcc_assert (flag_openmp);
      common = 1;
      તોડો;

    મૂળભૂત:
      gcc_unreachable ();
    }

  જો (code0 == ERROR_MARK || code1 == ERROR_MARK)
    પાછા error_mark_ગાંઠ;

  જો (gnu_vector_type_p (type0)
      && gnu_vector_type_p (type1)
      && (!વૃક્ષ_int_cst_equal (TYPE_SIZE (type0), TYPE_SIZE (type1))
	  || !vector_types_compatible_elements_p (type0, type1)))
    {
      gcc_rich_location richloc (location);
      maybe_range_label_for_વૃક્ષ_type_mismatch
	label_for_op0 (orig_op0, orig_op1),
	label_for_op1 (orig_op1, orig_op0);
      richloc.maybe_add_પદાવલિ (orig_op0, &label_for_op0, highlight_colors::lhs);
      richloc.maybe_add_પદાવલિ (orig_op1, &label_for_op1, highlight_colors::rhs);
      દ્વિઅંકી_op_error (&richloc, code, type0, type1);
      પાછા error_mark_ગાંઠ;
    }

  જો ((code0 == INTEGER_TYPE || code0 == REAL_TYPE || code0 == COMPLEX_TYPE
       || code0 == FIXED_POINT_TYPE || code0 == BITINT_TYPE
       || gnu_vector_type_p (type0))
      && (code1 == INTEGER_TYPE || code1 == REAL_TYPE || code1 == COMPLEX_TYPE
	  || code1 == FIXED_POINT_TYPE || code1 == BITINT_TYPE
	  || gnu_vector_type_p (type1)))
    {
      તાર્કિક first_complex = (code0 == COMPLEX_TYPE);
      તાર્કિક second_complex = (code1 == COMPLEX_TYPE);
      પૂર્ણાંક none_complex = (!first_complex && !second_complex);

      જો (shorten || common || short_compare)
	{
	  result_type = c_common_type (type0, type1);
	  do_warn_double_promotion (result_type, type0, type1,
				    "implicit conversion from %qT to %qT "
				    "to match other operand of binary "
				    "expression",
				    location);
	  જો (result_type == error_mark_ગાંઠ)
	    પાછા error_mark_ગાંઠ;
	}

      જો (first_complex != second_complex
	  && (code == PLUS_પદાવલિ
	      || code == MINUS_પદાવલિ
	      || code == MULT_પદાવલિ
	      || (code == TRUNC_DIV_પદાવલિ && first_complex))
	  && વૃક્ષ_CODE (વૃક્ષ_TYPE (result_type)) == REAL_TYPE
	  && flag_signed_zeros)
	{
	  /* An operation on mixed real/complex operands must be
	     handled specially, but the language-independent code can
	     more easily optimize the plain complex arithmetic if
	     -fno-signed-zeros.  */
	  વૃક્ષ real_type = વૃક્ષ_TYPE (result_type);
	  વૃક્ષ real, imag;
	  જો (type0 != orig_type0 || type1 != orig_type1)
	    {
	      gcc_assert (may_need_excess_precision && common);
	      semantic_result_type = c_common_type (orig_type0, orig_type1);
	    }
	  જો (first_complex)
	    {
	      જો (વૃક્ષ_TYPE (op0) != result_type)
		op0 = convert_and_check (location, result_type, op0);
	      જો (વૃક્ષ_TYPE (op1) != real_type)
		op1 = convert_and_check (location, real_type, op1);
	    }
	  નહીંતર
	    {
	      જો (વૃક્ષ_TYPE (op0) != real_type)
		op0 = convert_and_check (location, real_type, op0);
	      જો (વૃક્ષ_TYPE (op1) != result_type)
		op1 = convert_and_check (location, result_type, op1);
	    }
	  જો (વૃક્ષ_CODE (op0) == ERROR_MARK || વૃક્ષ_CODE (op1) == ERROR_MARK)
	    પાછા error_mark_ગાંઠ;
	  જો (first_complex)
	    {
	      op0 = save_પદાવલિ (op0);
	      real = build_unary_op (પદાવલિ_LOCATION (orig_op0), REALPART_પદાવલિ,
				     op0, સાચું);
	      imag = build_unary_op (પદાવલિ_LOCATION (orig_op0), IMAGPART_પદાવલિ,
				     op0, સાચું);
	      પસંદગી (code)
		{
		સ્થિતિ MULT_પદાવલિ:
		સ્થિતિ TRUNC_DIV_પદાવલિ:
		  op1 = save_પદાવલિ (op1);
		  imag = build2 (resultcode, real_type, imag, op1);
		  /* Fall through.  */
		સ્થિતિ PLUS_પદાવલિ:
		સ્થિતિ MINUS_પદાવલિ:
		  real = build2 (resultcode, real_type, real, op1);
		  તોડો;
		મૂળભૂત:
		  gcc_unreachable();
		}
	    }
	  નહીંતર
	    {
	      op1 = save_પદાવલિ (op1);
	      real = build_unary_op (પદાવલિ_LOCATION (orig_op1), REALPART_પદાવલિ,
				     op1, સાચું);
	      imag = build_unary_op (પદાવલિ_LOCATION (orig_op1), IMAGPART_પદાવલિ,
				     op1, સાચું);
	      પસંદગી (code)
		{
		સ્થિતિ MULT_પદાવલિ:
		  op0 = save_પદાવલિ (op0);
		  imag = build2 (resultcode, real_type, op0, imag);
		  /* Fall through.  */
		સ્થિતિ PLUS_પદાવલિ:
		  real = build2 (resultcode, real_type, op0, real);
		  તોડો;
		સ્થિતિ MINUS_પદાવલિ:
		  real = build2 (resultcode, real_type, op0, real);
		  imag = build1 (NEGATE_પદાવલિ, real_type, imag);
		  તોડો;
		મૂળભૂત:
		  gcc_unreachable();
		}
	    }
	  ret = build2 (COMPLEX_પદાવલિ, result_type, real, imag);
	  જાઓ return_build_દ્વિઅંકી_op;
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

      જો (shorten && none_complex)
	{
	  final_type = result_type;
	  result_type = shorten_દ્વિઅંકી_op (result_type, op0, op1,
					   shorten == -1);
	}

      /* Shifts can be shortened if shifting right.  */

      જો (short_shift)
	{
	  પૂર્ણાંક unsigned_arg;
	  વૃક્ષ arg0 = get_narrower (op0, &unsigned_arg);

	  final_type = result_type;

	  જો (arg0 == op0 && final_type == વૃક્ષ_TYPE (op0))
	    unsigned_arg = TYPE_UNSIGNED (વૃક્ષ_TYPE (op0));

	  જો (TYPE_PRECISION (વૃક્ષ_TYPE (arg0)) < TYPE_PRECISION (result_type)
	      && વૃક્ષ_int_cst_sgn (op1) > 0
	      /* We can shorten only if the shift count is less than the
		 number of bits in the smaller type size.  */
	      && compare_વૃક્ષ_int (op1, TYPE_PRECISION (વૃક્ષ_TYPE (arg0))) < 0
	      /* We cannot drop an unsigned shift after sign-extension.  */
	      && (!TYPE_UNSIGNED (final_type) || unsigned_arg))
	    {
	      /* Do an unsigned shift if the operand was zero-extended.  */
	      result_type
		= c_common_signed_or_unsigned_type (unsigned_arg,
						    વૃક્ષ_TYPE (arg0));
	      /* Convert value-to-be-shifted to that type.  */
	      જો (વૃક્ષ_TYPE (op0) != result_type)
		op0 = convert (result_type, op0);
	      converted = 1;
	    }
	}

      /* Comparison operations are shortened too but differently.
	 They identify themselves by setting short_compare = 1.  */

      જો (short_compare)
	{
	  /* Don't write &op0, etc., because that would prevent op0
	     from being kept in a register.
	     Instead, make copies of the our local variables and
	     pass the copies by reference, then copy them back afterward.  */
	  વૃક્ષ xop0 = op0, xop1 = op1, xresult_type = result_type;
	  ગણના વૃક્ષ_code xresultcode = resultcode;
	  વૃક્ષ val
	    = shorten_compare (location, &xop0, &xop1, &xresult_type,
			       &xresultcode);

	  જો (val != NULL_વૃક્ષ)
	    {
	      ret = val;
	      જાઓ return_build_દ્વિઅંકી_op;
	    }

	  op0 = xop0, op1 = xop1;
	  converted = 1;
	  resultcode = xresultcode;

	  જો (c_inhibit_evaluation_warnings == 0 && !c_in_omp_for)
	    {
	      તાર્કિક op0_maybe_const = સાચું;
	      તાર્કિક op1_maybe_const = સાચું;
	      વૃક્ષ orig_op0_folded, orig_op1_folded;

	      જો (in_late_દ્વિઅંકી_op)
		{
		  orig_op0_folded = orig_op0;
		  orig_op1_folded = orig_op1;
		}
	      નહીંતર
		{
		  /* Fold for the sake of possible warnings, as in
		     build_conditional_expr.  This requires the
		     "original" values to be folded, not just op0 and
		     op1.  */
		  c_inhibit_evaluation_warnings++;
		  op0 = c_fully_fold (op0, require_constant_કિંમત,
				      &op0_maybe_const);
		  op1 = c_fully_fold (op1, require_constant_કિંમત,
				      &op1_maybe_const);
		  c_inhibit_evaluation_warnings--;
		  orig_op0_folded = c_fully_fold (orig_op0,
						  require_constant_કિંમત,
						  ખાલી);
		  orig_op1_folded = c_fully_fold (orig_op1,
						  require_constant_કિંમત,
						  ખાલી);
		}

	      જો (warn_sign_compare)
		warn_for_sign_compare (location, orig_op0_folded,
				       orig_op1_folded, op0, op1,
				       result_type, resultcode);
	      જો (!in_late_દ્વિઅંકી_op && !int_operands)
		{
		  જો (!op0_maybe_const || વૃક્ષ_CODE (op0) != INTEGER_CST)
		    op0 = c_wrap_maybe_const (op0, !op0_maybe_const);
		  જો (!op1_maybe_const || વૃક્ષ_CODE (op1) != INTEGER_CST)
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

  જો (!result_type)
    {
      /* Favor showing any expression locations that are available. */
      op_location_t oploc (location, UNKNOWN_LOCATION);
      દ્વિઅંકી_op_rich_location richloc (oploc, orig_op0, orig_op1, સાચું);
      દ્વિઅંકી_op_error (&richloc, code, વૃક્ષ_TYPE (op0), વૃક્ષ_TYPE (op1));
      પાછા error_mark_ગાંઠ;
    }

  જો (build_type == NULL_વૃક્ષ)
    {
      build_type = result_type;
      જો ((type0 != orig_type0 || type1 != orig_type1)
	  && !boolean_op)
	{
	  gcc_assert (may_need_excess_precision && common);
	  semantic_result_type = c_common_type (orig_type0, orig_type1);
	}
    }

  જો (!converted)
    {
      op0 = ep_convert_and_check (location, result_type, op0,
				  semantic_result_type);
      op1 = ep_convert_and_check (location, result_type, op1,
				  semantic_result_type);

      /* This can happen if one operand has a vector type, and the other
	 has a different type.  */
      જો (વૃક્ષ_CODE (op0) == ERROR_MARK || વૃક્ષ_CODE (op1) == ERROR_MARK)
	પાછા error_mark_ગાંઠ;
    }

  જો (sanitize_flags_p ((SANITIZE_SHIFT
			 | SANITIZE_DIVIDE
			 | SANITIZE_FLOAT_DIVIDE
			 | SANITIZE_SI_OVERFLOW))
      && current_function_decl != NULL_વૃક્ષ
      && (doing_div_or_mod || doing_shift)
      && !require_constant_કિંમત)
    {
      /* OP0 and/or OP1 might have side-effects.  */
      op0 = save_પદાવલિ (op0);
      op1 = save_પદાવલિ (op1);
      op0 = c_fully_fold (op0, ખોટું, ખાલી);
      op1 = c_fully_fold (op1, ખોટું, ખાલી);
      જો (doing_div_or_mod && (sanitize_flags_p ((SANITIZE_DIVIDE
						  | SANITIZE_FLOAT_DIVIDE
						  | SANITIZE_SI_OVERFLOW))))
	instrument_પદાવલિ = ubsan_instrument_division (location, op0, op1);
      નહીંતર જો (doing_shift && sanitize_flags_p (SANITIZE_SHIFT))
	instrument_પદાવલિ = ubsan_instrument_shift (location, code, op0, op1);
    }

  /* Treat expressions in initializers specially as they can't trap.  */
  જો (int_const_or_overflow)
    ret = (require_constant_કિંમત
	   ? fold_build2_initializer_loc (location, resultcode, build_type,
					  op0, op1)
	   : fold_build2_loc (location, resultcode, build_type, op0, op1));
  નહીંતર
    ret = build2 (resultcode, build_type, op0, op1);
  જો (final_type != NULL_વૃક્ષ)
    ret = convert (final_type, ret);

 return_build_દ્વિઅંકી_op:
  gcc_assert (ret != error_mark_ગાંઠ);
  જો (વૃક્ષ_CODE (ret) == INTEGER_CST && !વૃક્ષ_OVERFLOW (ret) && !int_const)
    ret = (int_operands
	   ? note_integer_operands (ret)
	   : build1 (NOP_પદાવલિ, વૃક્ષ_TYPE (ret), ret));
  નહીંતર જો (વૃક્ષ_CODE (ret) != INTEGER_CST && int_operands
	   && !in_late_દ્વિઅંકી_op)
    ret = note_integer_operands (ret);
  protected_set_પદાવલિ_location (ret, location);

  જો (instrument_પદાવલિ != ખાલી)
    ret = fold_build2 (COMPOUND_પદાવલિ, વૃક્ષ_TYPE (ret),
		       instrument_પદાવલિ, ret);

  જો (semantic_result_type)
    ret = build1_loc (location, EXCESS_PRECISION_પદાવલિ,
		      semantic_result_type, ret);

  પાછા ret;
}


/* Convert EXPR to be a truth-value (type TYPE), validating its type for this
   purpose.  LOCATION is the source location for the expression.  */

વૃક્ષ
c_objc_common_truthvalue_conversion (location_t location, વૃક્ષ પદાવલિ, વૃક્ષ type)
{
  તાર્કિક int_const, int_operands;

  પસંદગી (વૃક્ષ_CODE (વૃક્ષ_TYPE (પદાવલિ)))
    {
    સ્થિતિ ARRAY_TYPE:
      error_at (location, "used array that cannot be converted to pointer where scalar is required");
      પાછા error_mark_ગાંઠ;

    સ્થિતિ RECORD_TYPE:
      error_at (location, "used struct type value where scalar is required");
      પાછા error_mark_ગાંઠ;

    સ્થિતિ UNION_TYPE:
      error_at (location, "used union type value where scalar is required");
      પાછા error_mark_ગાંઠ;

    સ્થિતિ VOID_TYPE:
      error_at (location, "void value not ignored as it ought to be");
      પાછા error_mark_ગાંઠ;

    સ્થિતિ POINTER_TYPE:
      જો (reject_gcc_builtin (પદાવલિ))
	પાછા error_mark_ગાંઠ;
      તોડો;

    સ્થિતિ FUNCTION_TYPE:
      gcc_unreachable ();

    સ્થિતિ VECTOR_TYPE:
      error_at (location, "used vector type where scalar is required");
      પાછા error_mark_ગાંઠ;

    મૂળભૂત:
      તોડો;
    }

  /* Conversion of a floating constant to boolean goes through here
     and yields an integer constant expression.  Otherwise, the result
     is only an integer constant expression if the argument is.  */
  int_const = ((વૃક્ષ_CODE (પદાવલિ) == INTEGER_CST && !વૃક્ષ_OVERFLOW (પદાવલિ))
	       || ((વૃક્ષ_CODE (પદાવલિ) == REAL_CST
		    || વૃક્ષ_CODE (પદાવલિ) == COMPLEX_CST)
		   && (વૃક્ષ_CODE (type) == BOOLEAN_TYPE
		       || (વૃક્ષ_CODE (type) == ENUMERAL_TYPE
			   && ENUM_UNDERLYING_TYPE (type) != NULL_વૃક્ષ
			   && (વૃક્ષ_CODE (ENUM_UNDERLYING_TYPE (type))
			       == BOOLEAN_TYPE)))));
  int_operands = પદાવલિ_INT_CONST_OPERANDS (પદાવલિ);
  જો (int_operands && વૃક્ષ_CODE (પદાવલિ) != INTEGER_CST)
    {
      પદાવલિ = remove_c_maybe_const_પદાવલિ (પદાવલિ);
      પદાવલિ = build2 (NE_પદાવલિ, type, પદાવલિ,
		     convert (વૃક્ષ_TYPE (પદાવલિ), integer_zero_ગાંઠ));
      પદાવલિ = note_integer_operands (પદાવલિ);
    }
  નહીંતર
    {
      /* ??? Should we also give an error for vectors rather than leaving
	 those to give errors later?  */
      પદાવલિ = c_common_truthvalue_conversion (location, પદાવલિ);
      પદાવલિ = fold_convert_loc (location, type, પદાવલિ);
    }

  જો (વૃક્ષ_CODE (પદાવલિ) == INTEGER_CST && int_operands && !int_const)
    {
      જો (વૃક્ષ_OVERFLOW (પદાવલિ))
	પાછા પદાવલિ;
      નહીંતર
	પાછા note_integer_operands (પદાવલિ);
    }
  જો (વૃક્ષ_CODE (પદાવલિ) == INTEGER_CST && !int_const)
    પાછા build1 (NOP_પદાવલિ, વૃક્ષ_TYPE (પદાવલિ), પદાવલિ);
  પાછા પદાવલિ;
}


/* Convert EXPR to a contained DECL, updating *TC, *TI and *SE as
   required.  */

વૃક્ષ
c_પદાવલિ_to_decl (વૃક્ષ પદાવલિ, તાર્કિક *tc ATTRIBUTE_UNUSED, તાર્કિક *se)
{
  જો (વૃક્ષ_CODE (પદાવલિ) == COMPOUND_LITERAL_પદાવલિ)
    {
      વૃક્ષ decl = COMPOUND_LITERAL_પદાવલિ_DECL (પદાવલિ);
      /* Executing a compound literal inside a function reinitializes
	 it.  */
      જો (!વૃક્ષ_STATIC (decl))
	*se = સાચું;
      પાછા decl;
    }
  નહીંતર
    પાછા પદાવલિ;
}

/* Generate OMP construct CODE, with BODY and CLAUSES as its compound
   statement.  LOC is the location of the construct.  */

વૃક્ષ
c_finish_omp_construct (location_t loc, ગણના વૃક્ષ_code code, વૃક્ષ body,
			વૃક્ષ clauses)
{
  body = c_end_compound_stmt (loc, body, સાચું);

  વૃક્ષ stmt = make_ગાંઠ (code);
  વૃક્ષ_TYPE (stmt) = void_type_ગાંઠ;
  OMP_BODY (stmt) = body;
  OMP_CLAUSES (stmt) = clauses;
  SET_પદાવલિ_LOCATION (stmt, loc);

  પાછા add_stmt (stmt);
}

/* Generate OACC_DATA, with CLAUSES and BLOCK as its compound
   statement.  LOC is the location of the OACC_DATA.  */

વૃક્ષ
c_finish_oacc_data (location_t loc, વૃક્ષ clauses, વૃક્ષ block)
{
  વૃક્ષ stmt;

  block = c_end_compound_stmt (loc, block, સાચું);

  stmt = make_ગાંઠ (OACC_DATA);
  વૃક્ષ_TYPE (stmt) = void_type_ગાંઠ;
  OACC_DATA_CLAUSES (stmt) = clauses;
  OACC_DATA_BODY (stmt) = block;
  SET_પદાવલિ_LOCATION (stmt, loc);

  પાછા add_stmt (stmt);
}

/* Generate OACC_HOST_DATA, with CLAUSES and BLOCK as its compound
   statement.  LOC is the location of the OACC_HOST_DATA.  */

વૃક્ષ
c_finish_oacc_host_data (location_t loc, વૃક્ષ clauses, વૃક્ષ block)
{
  વૃક્ષ stmt;

  block = c_end_compound_stmt (loc, block, સાચું);

  stmt = make_ગાંઠ (OACC_HOST_DATA);
  વૃક્ષ_TYPE (stmt) = void_type_ગાંઠ;
  OACC_HOST_DATA_CLAUSES (stmt) = clauses;
  OACC_HOST_DATA_BODY (stmt) = block;
  SET_પદાવલિ_LOCATION (stmt, loc);

  પાછા add_stmt (stmt);
}

/* Like c_begin_compound_stmt, except force the retention of the BLOCK.  */

વૃક્ષ
c_begin_omp_parallel (શૂન્ય)
{
  વૃક્ષ block;

  keep_next_level ();
  block = c_begin_compound_stmt (સાચું);

  પાછા block;
}

/* Generate OMP_PARALLEL, with CLAUSES and BLOCK as its compound
   statement.  LOC is the location of the OMP_PARALLEL.  */

વૃક્ષ
c_finish_omp_parallel (location_t loc, વૃક્ષ clauses, વૃક્ષ block)
{
  વૃક્ષ stmt;

  block = c_end_compound_stmt (loc, block, સાચું);

  stmt = make_ગાંઠ (OMP_PARALLEL);
  વૃક્ષ_TYPE (stmt) = void_type_ગાંઠ;
  OMP_PARALLEL_CLAUSES (stmt) = clauses;
  OMP_PARALLEL_BODY (stmt) = block;
  SET_પદાવલિ_LOCATION (stmt, loc);

  પાછા add_stmt (stmt);
}

/* Like c_begin_compound_stmt, except force the retention of the BLOCK.  */

વૃક્ષ
c_begin_omp_task (શૂન્ય)
{
  વૃક્ષ block;

  keep_next_level ();
  block = c_begin_compound_stmt (સાચું);

  પાછા block;
}

/* Generate OMP_TASK, with CLAUSES and BLOCK as its compound
   statement.  LOC is the location of the #pragma.  */

વૃક્ષ
c_finish_omp_task (location_t loc, વૃક્ષ clauses, વૃક્ષ block)
{
  વૃક્ષ stmt;

  block = c_end_compound_stmt (loc, block, સાચું);

  stmt = make_ગાંઠ (OMP_TASK);
  વૃક્ષ_TYPE (stmt) = void_type_ગાંઠ;
  OMP_TASK_CLAUSES (stmt) = clauses;
  OMP_TASK_BODY (stmt) = block;
  SET_પદાવલિ_LOCATION (stmt, loc);

  પાછા add_stmt (stmt);
}

/* Generate GOMP_cancel call for #pragma omp cancel.  */

શૂન્ય
c_finish_omp_cancel (location_t loc, વૃક્ષ clauses)
{
  વૃક્ષ fn = builtin_decl_explicit (BUILT_IN_GOMP_CANCEL);
  પૂર્ણાંક mask = 0;
  જો (omp_find_clause (clauses, OMP_CLAUSE_PARALLEL))
    mask = 1;
  નહીંતર જો (omp_find_clause (clauses, OMP_CLAUSE_FOR))
    mask = 2;
  નહીંતર જો (omp_find_clause (clauses, OMP_CLAUSE_SECTIONS))
    mask = 4;
  નહીંતર જો (omp_find_clause (clauses, OMP_CLAUSE_TASKGROUP))
    mask = 8;
  નહીંતર
    {
      error_at (loc, "%<#pragma omp cancel%> must specify one of "
		     "%<parallel%>, %<for%>, %<sections%> or %<taskgroup%> "
		     "clauses");
      પાછા;
    }
  વૃક્ષ ifc = omp_find_clause (clauses, OMP_CLAUSE_IF);
  જો (ifc != NULL_વૃક્ષ)
    {
      જો (OMP_CLAUSE_IF_MODIFIER (ifc) != ERROR_MARK
	  && OMP_CLAUSE_IF_MODIFIER (ifc) != VOID_CST)
	error_at (OMP_CLAUSE_LOCATION (ifc),
		  "expected %<cancel%> %<if%> clause modifier");
      નહીંતર
	{
	  વૃક્ષ ifc2 = omp_find_clause (OMP_CLAUSE_CHAIN (ifc), OMP_CLAUSE_IF);
	  જો (ifc2 != NULL_વૃક્ષ)
	    {
	      gcc_assert (OMP_CLAUSE_IF_MODIFIER (ifc) == VOID_CST
			  && OMP_CLAUSE_IF_MODIFIER (ifc2) != ERROR_MARK
			  && OMP_CLAUSE_IF_MODIFIER (ifc2) != VOID_CST);
	      error_at (OMP_CLAUSE_LOCATION (ifc2),
			"expected %<cancel%> %<if%> clause modifier");
	    }
	}

      વૃક્ષ type = વૃક્ષ_TYPE (OMP_CLAUSE_IF_પદાવલિ (ifc));
      ifc = fold_build2_loc (OMP_CLAUSE_LOCATION (ifc), NE_પદાવલિ,
			     boolean_type_ગાંઠ, OMP_CLAUSE_IF_પદાવલિ (ifc),
			     build_zero_cst (type));
    }
  નહીંતર
    ifc = boolean_true_ગાંઠ;
  વૃક્ષ stmt = build_call_પદાવલિ_loc (loc, fn, 2,
				   build_int_cst (integer_type_ગાંઠ, mask),
				   ifc);
  add_stmt (stmt);
}

/* Generate GOMP_cancellation_point call for
   #pragma omp cancellation point.  */

શૂન્ય
c_finish_omp_cancellation_point (location_t loc, વૃક્ષ clauses)
{
  વૃક્ષ fn = builtin_decl_explicit (BUILT_IN_GOMP_CANCELLATION_POINT);
  પૂર્ણાંક mask = 0;
  જો (omp_find_clause (clauses, OMP_CLAUSE_PARALLEL))
    mask = 1;
  નહીંતર જો (omp_find_clause (clauses, OMP_CLAUSE_FOR))
    mask = 2;
  નહીંતર જો (omp_find_clause (clauses, OMP_CLAUSE_SECTIONS))
    mask = 4;
  નહીંતર જો (omp_find_clause (clauses, OMP_CLAUSE_TASKGROUP))
    mask = 8;
  નહીંતર
    {
      error_at (loc, "%<#pragma omp cancellation point%> must specify one of "
		     "%<parallel%>, %<for%>, %<sections%> or %<taskgroup%> "
		     "clauses");
      પાછા;
    }
  વૃક્ષ stmt = build_call_પદાવલિ_loc (loc, fn, 1,
				   build_int_cst (integer_type_ગાંઠ, mask));
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

સ્થિર વૃક્ષ
handle_omp_array_sections_1 (વૃક્ષ c, વૃક્ષ t, vec<વૃક્ષ> &types,
			     તાર્કિક &maybe_zero_len, unsigned પૂર્ણાંક &first_non_one,
			     ગણના c_omp_region_type ort)
{
  વૃક્ષ ret, નીચલું_bound, length, type;
  તાર્કિક openacc = (ort & C_ORT_ACC) != 0;
  જો (વૃક્ષ_CODE (t) != OMP_ARRAY_SECTION)
    {
      જો (error_operand_p (t))
	પાછા error_mark_ગાંઠ;
      c_omp_address_inspector ai (OMP_CLAUSE_LOCATION (c), t);
      ret = t;
      જો (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_AFFINITY
	  && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_DEPEND
	  && TYPE_ATOMIC (strip_array_types (વૃક્ષ_TYPE (t))))
	{
	  error_at (OMP_CLAUSE_LOCATION (c), "%<_Atomic%> %qE in %qs clause",
		    t, omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	  પાછા error_mark_ગાંઠ;
	}
      જો (!ai.check_clause (c))
	પાછા error_mark_ગાંઠ;
      નહીંતર જો (ai.component_access_p ()
	       && (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP
		   || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_TO
		   || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_FROM))
	t = ai.get_મૂળ_term (સાચું);
      નહીંતર
	t = ai.unconverted_ref_origin ();
      જો (t == error_mark_ગાંઠ)
	પાછા error_mark_ગાંઠ;
      જો (!VAR_P (t)
	  && (ort == C_ORT_ACC || !પદાવલિ_P (t))
	  && વૃક્ષ_CODE (t) != PARM_DECL)
	{
	  જો (DECL_P (t))
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%qD is not a variable in %qs clause", t,
		      omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	  નહીંતર
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%qE is not a variable in %qs clause", t,
		      omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	  પાછા error_mark_ગાંઠ;
	}
      નહીંતર જો (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_AFFINITY
	       && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_DEPEND
	       && TYPE_ATOMIC (વૃક્ષ_TYPE (t)))
	{
	  error_at (OMP_CLAUSE_LOCATION (c), "%<_Atomic%> %qD in %qs clause",
		    t, omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	  પાછા error_mark_ગાંઠ;
	}
      નહીંતર જો (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_AFFINITY
	       && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_DEPEND
	       && VAR_P (t)
	       && DECL_THREAD_LOCAL_P (t))
	{
	  error_at (OMP_CLAUSE_LOCATION (c),
		    "%qD is threadprivate variable in %qs clause", t,
		    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	  પાછા error_mark_ગાંઠ;
	}
      જો ((OMP_CLAUSE_CODE (c) == OMP_CLAUSE_AFFINITY
	   || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND)
	  && TYPE_ATOMIC (વૃક્ષ_TYPE (t))
	  && POINTER_TYPE_P (વૃક્ષ_TYPE (t)))
	{
	  /* If the array section is pointer based and the pointer
	     itself is _Atomic qualified, we need to atomically load
	     the pointer.  */
	  ret = convert_lvalue_to_rvalue (OMP_CLAUSE_LOCATION (c),
					  ret, ખોટું, ખોટું);
	}
      પાછા ret;
    }

  ret = handle_omp_array_sections_1 (c, વૃક્ષ_OPERAND (t, 0), types,
				     maybe_zero_len, first_non_one, ort);
  જો (ret == error_mark_ગાંઠ || ret == NULL_વૃક્ષ)
    પાછા ret;

  type = વૃક્ષ_TYPE (ret);
  નીચલું_bound = વૃક્ષ_OPERAND (t, 1);
  length = વૃક્ષ_OPERAND (t, 2);

  જો (નીચલું_bound == error_mark_ગાંઠ || length == error_mark_ગાંઠ)
    પાછા error_mark_ગાંઠ;

  જો (નીચલું_bound && !INTEGRAL_TYPE_P (વૃક્ષ_TYPE (નીચલું_bound)))
    {
      error_at (OMP_CLAUSE_LOCATION (c),
		"low bound %qE of array section does not have integral type",
		નીચલું_bound);
      પાછા error_mark_ગાંઠ;
    }
  જો (length && !INTEGRAL_TYPE_P (વૃક્ષ_TYPE (length)))
    {
      error_at (OMP_CLAUSE_LOCATION (c),
		"length %qE of array section does not have integral type",
		length);
      પાછા error_mark_ગાંઠ;
    }
  જો (નીચલું_bound
      && વૃક્ષ_CODE (નીચલું_bound) == INTEGER_CST
      && TYPE_PRECISION (વૃક્ષ_TYPE (નીચલું_bound))
	 > TYPE_PRECISION (sizetype))
    નીચલું_bound = fold_convert (sizetype, નીચલું_bound);
  જો (length
      && વૃક્ષ_CODE (length) == INTEGER_CST
      && TYPE_PRECISION (વૃક્ષ_TYPE (length))
	 > TYPE_PRECISION (sizetype))
    length = fold_convert (sizetype, length);
  જો (નીચલું_bound == NULL_વૃક્ષ)
    નીચલું_bound = integer_zero_ગાંઠ;
  જો (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP
      && (OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_ATTACH
	  || OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_DETACH))
    {
      જો (length != integer_one_ગાંઠ)
	{
	  error_at (OMP_CLAUSE_LOCATION (c),
		    "expected single pointer in %qs clause",
		    user_omp_clause_code_name (c, openacc));
	  પાછા error_mark_ગાંઠ;
	}
    }
  જો (length != NULL_વૃક્ષ)
    {
      જો (!integer_nonzerop (length))
	{
	  જો (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_AFFINITY
	      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND
	      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_REDUCTION
	      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IN_REDUCTION
	      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_TASK_REDUCTION)
	    {
	      જો (integer_zerop (length))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "zero length array section in %qs clause",
			    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		  પાછા error_mark_ગાંઠ;
		}
	    }
	  નહીંતર
	    maybe_zero_len = સાચું;
	}
      જો (first_non_one == types.length ()
	  && (વૃક્ષ_CODE (length) != INTEGER_CST || integer_onep (length)))
	first_non_one++;
    }
  જો (વૃક્ષ_CODE (type) == ARRAY_TYPE)
    {
      જો (length == NULL_વૃક્ષ
	  && (TYPE_DOMAIN (type) == NULL_વૃક્ષ
	      || TYPE_MAX_કિંમત (TYPE_DOMAIN (type)) == NULL_વૃક્ષ))
	{
	  error_at (OMP_CLAUSE_LOCATION (c),
		    "for unknown bound array type length expression must "
		    "be specified");
	  પાછા error_mark_ગાંઠ;
	}
      જો (વૃક્ષ_CODE (નીચલું_bound) == INTEGER_CST
	  && વૃક્ષ_int_cst_sgn (નીચલું_bound) == -1)
	{
	  error_at (OMP_CLAUSE_LOCATION (c),
		    "negative low bound in array section in %qs clause",
		    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	  પાછા error_mark_ગાંઠ;
	}
      જો (length != NULL_વૃક્ષ
	  && વૃક્ષ_CODE (length) == INTEGER_CST
	  && વૃક્ષ_int_cst_sgn (length) == -1)
	{
	  error_at (OMP_CLAUSE_LOCATION (c),
		    "negative length in array section in %qs clause",
		    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	  પાછા error_mark_ગાંઠ;
	}
      જો (TYPE_DOMAIN (type)
	  && TYPE_MAX_કિંમત (TYPE_DOMAIN (type))
	  && વૃક્ષ_CODE (TYPE_MAX_કિંમત (TYPE_DOMAIN (type)))
			== INTEGER_CST)
	{
	  વૃક્ષ size
	    = fold_convert (sizetype, TYPE_MAX_કિંમત (TYPE_DOMAIN (type)));
	  size = size_binop (PLUS_પદાવલિ, size, size_one_ગાંઠ);
	  જો (વૃક્ષ_CODE (નીચલું_bound) == INTEGER_CST)
	    {
	      જો (વૃક્ષ_int_cst_lt (size, નીચલું_bound))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "low bound %qE above array section size "
			    "in %qs clause", નીચલું_bound,
			    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		  પાછા error_mark_ગાંઠ;
		}
	      જો (વૃક્ષ_int_cst_equal (size, નીચલું_bound))
		{
		  જો (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_AFFINITY
		      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND
		      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_REDUCTION
		      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IN_REDUCTION
		      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_TASK_REDUCTION)
		    {
		      error_at (OMP_CLAUSE_LOCATION (c),
				"zero length array section in %qs clause",
				omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		      પાછા error_mark_ગાંઠ;
		    }
		  maybe_zero_len = સાચું;
		}
	      નહીંતર જો (length == NULL_વૃક્ષ
		       && first_non_one == types.length ()
		       && વૃક્ષ_int_cst_equal
			    (TYPE_MAX_કિંમત (TYPE_DOMAIN (type)),
			     નીચલું_bound))
		first_non_one++;
	    }
	  નહીંતર જો (length == NULL_વૃક્ષ)
	    {
	      જો (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_AFFINITY
		  && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_DEPEND
		  && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_REDUCTION
		  && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_IN_REDUCTION
		  && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_TASK_REDUCTION)
		maybe_zero_len = સાચું;
	      જો (first_non_one == types.length ())
		first_non_one++;
	    }
	  જો (length && વૃક્ષ_CODE (length) == INTEGER_CST)
	    {
	      જો (વૃક્ષ_int_cst_lt (size, length))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "length %qE above array section size "
			    "in %qs clause", length,
			    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		  પાછા error_mark_ગાંઠ;
		}
	      જો (વૃક્ષ_CODE (નીચલું_bound) == INTEGER_CST)
		{
		  વૃક્ષ lbpluslen
		    = size_binop (PLUS_પદાવલિ,
				  fold_convert (sizetype, નીચલું_bound),
				  fold_convert (sizetype, length));
		  જો (વૃક્ષ_CODE (lbpluslen) == INTEGER_CST
		      && વૃક્ષ_int_cst_lt (size, lbpluslen))
		    {
		      error_at (OMP_CLAUSE_LOCATION (c),
				"high bound %qE above array section size "
				"in %qs clause", lbpluslen,
				omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		      પાછા error_mark_ગાંઠ;
		    }
		}
	    }
	}
      નહીંતર જો (length == NULL_વૃક્ષ)
	{
	  જો (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_AFFINITY
	      && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_DEPEND
	      && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_REDUCTION
	      && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_IN_REDUCTION
	      && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_TASK_REDUCTION)
	    maybe_zero_len = સાચું;
	  જો (first_non_one == types.length ())
	    first_non_one++;
	}

      /* For [lb:] we will need to evaluate lb more than once.  */
      જો (length == NULL_વૃક્ષ && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_DEPEND)
	{
	  વૃક્ષ lb = save_પદાવલિ (નીચલું_bound);
	  જો (lb != નીચલું_bound)
	    {
	      વૃક્ષ_OPERAND (t, 1) = lb;
	      નીચલું_bound = lb;
	    }
	}
    }
  નહીંતર જો (વૃક્ષ_CODE (type) == POINTER_TYPE)
    {
      જો (length == NULL_વૃક્ષ)
	{
	  જો (વૃક્ષ_CODE (ret) == PARM_DECL && C_ARRAY_PARAMETER (ret))
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "for array function parameter length expression "
		      "must be specified");
	  નહીંતર
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "for pointer type length expression must be specified");
	  પાછા error_mark_ગાંઠ;
	}
      જો (length != NULL_વૃક્ષ
	  && વૃક્ષ_CODE (length) == INTEGER_CST
	  && વૃક્ષ_int_cst_sgn (length) == -1)
	{
	  error_at (OMP_CLAUSE_LOCATION (c),
		    "negative length in array section in %qs clause",
		    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	  પાછા error_mark_ગાંઠ;
	}
      /* If there is a pointer type anywhere but in the very first
	 array-section-subscript, the array section could be non-contiguous.  */
      જો (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_DEPEND
	  && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_AFFINITY
	  && વૃક્ષ_CODE (વૃક્ષ_OPERAND (t, 0)) == OMP_ARRAY_SECTION)
	{
	  /* If any prior dimension has a non-one length, then deem this
	     array section as non-contiguous.  */
	  માટે (વૃક્ષ d = વૃક્ષ_OPERAND (t, 0);
	       વૃક્ષ_CODE (d) == OMP_ARRAY_SECTION;
	       d = વૃક્ષ_OPERAND (d, 0))
	    {
	      વૃક્ષ d_length = વૃક્ષ_OPERAND (d, 2);
	      જો (d_length == NULL_વૃક્ષ || !integer_onep (d_length))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "array section is not contiguous in %qs clause",
			    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		  પાછા error_mark_ગાંઠ;
		}
	    }
	}
    }
  નહીંતર
    {
      error_at (OMP_CLAUSE_LOCATION (c),
		"%qE does not have pointer or array type", ret);
      પાછા error_mark_ગાંઠ;
    }
  જો (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_DEPEND)
    types.safe_ધકેલો (વૃક્ષ_TYPE (ret));
  /* We will need to evaluate lb more than once.  */
  વૃક્ષ lb = save_પદાવલિ (નીચલું_bound);
  જો (lb != નીચલું_bound)
    {
      વૃક્ષ_OPERAND (t, 1) = lb;
      નીચલું_bound = lb;
    }
  ret = build_array_ref (OMP_CLAUSE_LOCATION (c), ret, નીચલું_bound);
  પાછા ret;
}

/* Handle array sections for clause C.  */

સ્થિર તાર્કિક
handle_omp_array_sections (વૃક્ષ &c, ગણના c_omp_region_type ort)
{
  તાર્કિક maybe_zero_len = ખોટું;
  unsigned પૂર્ણાંક first_non_one = 0;
  auto_vec<વૃક્ષ, 10> types;
  વૃક્ષ *tp = &OMP_CLAUSE_DECL (c);
  જો ((OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND
       || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_AFFINITY)
      && OMP_ITERATOR_DECL_P (*tp))
    tp = &વૃક્ષ_કિંમત (*tp);
  વૃક્ષ first = handle_omp_array_sections_1 (c, *tp, types,
					    maybe_zero_len, first_non_one,
					    ort);
  જો (first == error_mark_ગાંઠ)
    પાછા સાચું;
  જો (first == NULL_વૃક્ષ)
    પાછા ખોટું;
  જો (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND
      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_AFFINITY)
    {
      વૃક્ષ t = *tp;
      વૃક્ષ tem = NULL_વૃક્ષ;
      /* Need to evaluate side effects in the length expressions
	 if any.  */
      જ્યારે (વૃક્ષ_CODE (t) == વૃક્ષ_LIST)
	{
	  જો (વૃક્ષ_કિંમત (t) && વૃક્ષ_SIDE_EFFECTS (વૃક્ષ_કિંમત (t)))
	    {
	      જો (tem == NULL_વૃક્ષ)
		tem = વૃક્ષ_કિંમત (t);
	      નહીંતર
		tem = build2 (COMPOUND_પદાવલિ, વૃક્ષ_TYPE (tem),
			      વૃક્ષ_કિંમત (t), tem);
	    }
	  t = વૃક્ષ_CHAIN (t);
	}
      જો (tem)
	first = build2 (COMPOUND_પદાવલિ, વૃક્ષ_TYPE (first), tem, first);
      first = c_fully_fold (first, ખોટું, ખાલી, સાચું);
      *tp = first;
    }
  નહીંતર
    {
      unsigned પૂર્ણાંક અંક = types.length (), i;
      વૃક્ષ t, side_effects = NULL_વૃક્ષ, size = NULL_વૃક્ષ;
      વૃક્ષ condition = NULL_વૃક્ષ;

      જો (int_size_in_bytes (વૃક્ષ_TYPE (first)) <= 0)
	maybe_zero_len = સાચું;

      માટે (i = અંક, t = OMP_CLAUSE_DECL (c); i > 0;
	   t = વૃક્ષ_OPERAND (t, 0))
	{
	  વૃક્ષ નીચલું_bound = વૃક્ષ_OPERAND (t, 1);
	  વૃક્ષ length = વૃક્ષ_OPERAND (t, 2);

	  i--;
	  જો (નીચલું_bound
	      && વૃક્ષ_CODE (નીચલું_bound) == INTEGER_CST
	      && TYPE_PRECISION (વૃક્ષ_TYPE (નીચલું_bound))
		 > TYPE_PRECISION (sizetype))
	    નીચલું_bound = fold_convert (sizetype, નીચલું_bound);
	  જો (length
	      && વૃક્ષ_CODE (length) == INTEGER_CST
	      && TYPE_PRECISION (વૃક્ષ_TYPE (length))
		 > TYPE_PRECISION (sizetype))
	    length = fold_convert (sizetype, length);
	  જો (નીચલું_bound == NULL_વૃક્ષ)
	    નીચલું_bound = integer_zero_ગાંઠ;
	  જો (!maybe_zero_len && i > first_non_one)
	    {
	      જો (integer_nonzerop (નીચલું_bound))
		જાઓ do_warn_noncontiguous;
	      જો (length != NULL_વૃક્ષ
		  && વૃક્ષ_CODE (length) == INTEGER_CST
		  && TYPE_DOMAIN (types[i])
		  && TYPE_MAX_કિંમત (TYPE_DOMAIN (types[i]))
		  && વૃક્ષ_CODE (TYPE_MAX_કિંમત (TYPE_DOMAIN (types[i])))
		     == INTEGER_CST)
		{
		  વૃક્ષ size;
		  size = size_binop (PLUS_પદાવલિ,
				     TYPE_MAX_કિંમત (TYPE_DOMAIN (types[i])),
				     size_one_ગાંઠ);
		  જો (!વૃક્ષ_int_cst_equal (length, size))
		    {
		     do_warn_noncontiguous:
		      error_at (OMP_CLAUSE_LOCATION (c),
				"array section is not contiguous in %qs "
				"clause",
				omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		      પાછા સાચું;
		    }
		}
	      જો (length != NULL_વૃક્ષ
		  && વૃક્ષ_SIDE_EFFECTS (length))
		{
		  જો (side_effects == NULL_વૃક્ષ)
		    side_effects = length;
		  નહીંતર
		    side_effects = build2 (COMPOUND_પદાવલિ,
					   વૃક્ષ_TYPE (side_effects),
					   length, side_effects);
		}
	    }
	  નહીંતર
	    {
	      વૃક્ષ l;

	      જો (i > first_non_one
		  && ((length && integer_nonzerop (length))
		      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_REDUCTION
		      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IN_REDUCTION
		      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_TASK_REDUCTION))
		ચાલુ;
	      જો (length)
		l = fold_convert (sizetype, length);
	      નહીંતર
		{
		  l = size_binop (PLUS_પદાવલિ,
				  TYPE_MAX_કિંમત (TYPE_DOMAIN (types[i])),
				  size_one_ગાંઠ);
		  l = size_binop (MINUS_પદાવલિ, l,
				  fold_convert (sizetype, નીચલું_bound));
		}
	      જો (i > first_non_one)
		{
		  l = fold_build2 (NE_પદાવલિ, boolean_type_ગાંઠ, l,
				   size_zero_ગાંઠ);
		  જો (condition == NULL_વૃક્ષ)
		    condition = l;
		  નહીંતર
		    condition = fold_build2 (BIT_AND_પદાવલિ, boolean_type_ગાંઠ,
					     l, condition);
		}
	      નહીંતર જો (size == NULL_વૃક્ષ)
		{
		  size = size_in_bytes (વૃક્ષ_TYPE (types[i]));
		  વૃક્ષ eltype = વૃક્ષ_TYPE (types[અંક - 1]);
		  જ્યારે (વૃક્ષ_CODE (eltype) == ARRAY_TYPE)
		    eltype = વૃક્ષ_TYPE (eltype);
		  જો (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_REDUCTION
		      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IN_REDUCTION
		      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_TASK_REDUCTION)
		    {
		      જો (integer_zerop (size)
			  || integer_zerop (size_in_bytes (eltype)))
			{
			  error_at (OMP_CLAUSE_LOCATION (c),
				    "zero length array section in %qs clause",
				    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
			  પાછા error_mark_ગાંઠ;
			}
		      size = size_binop (EXACT_DIV_પદાવલિ, size,
					 size_in_bytes (eltype));
		    }
		  size = size_binop (MULT_પદાવલિ, size, l);
		  જો (condition)
		    size = fold_build3 (COND_પદાવલિ, sizetype, condition,
					size, size_zero_ગાંઠ);
		}
	      નહીંતર
		size = size_binop (MULT_પદાવલિ, size, l);
	    }
	}
      જો (side_effects)
	size = build2 (COMPOUND_પદાવલિ, sizetype, side_effects, size);
      જો (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_REDUCTION
	  || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IN_REDUCTION
	  || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_TASK_REDUCTION)
	{
	  size = size_binop (MINUS_પદાવલિ, size, size_one_ગાંઠ);
	  size = c_fully_fold (size, ખોટું, ખાલી);
	  size = save_પદાવલિ (size);
	  વૃક્ષ index_type = build_index_type (size);
	  વૃક્ષ eltype = વૃક્ષ_TYPE (first);
	  જ્યારે (વૃક્ષ_CODE (eltype) == ARRAY_TYPE)
	    eltype = વૃક્ષ_TYPE (eltype);
	  વૃક્ષ type = c_build_array_type (eltype, index_type);
	  વૃક્ષ ptype = c_build_pointer_type (eltype);
	  જો (વૃક્ષ_CODE (વૃક્ષ_TYPE (t)) == ARRAY_TYPE)
	    t = build_fold_addr_પદાવલિ (t);
	  વૃક્ષ t2 = build_fold_addr_પદાવલિ (first);
	  t2 = fold_convert_loc (OMP_CLAUSE_LOCATION (c),
				 ptrdiff_type_ગાંઠ, t2);
	  t2 = fold_build2_loc (OMP_CLAUSE_LOCATION (c), MINUS_પદાવલિ,
				ptrdiff_type_ગાંઠ, t2,
				fold_convert_loc (OMP_CLAUSE_LOCATION (c),
						  ptrdiff_type_ગાંઠ, t));
	  t2 = c_fully_fold (t2, ખોટું, ખાલી);
	  જો (વૃક્ષ_fits_shwi_p (t2))
	    t = build2 (MEM_REF, type, t,
			build_int_cst (ptype, વૃક્ષ_to_shwi (t2)));
	  નહીંતર
	    {
	      t2 = fold_convert_loc (OMP_CLAUSE_LOCATION (c), sizetype, t2);
	      t = build2_loc (OMP_CLAUSE_LOCATION (c), POINTER_PLUS_પદાવલિ,
			      વૃક્ષ_TYPE (t), t, t2);
	      t = build2 (MEM_REF, type, t, build_int_cst (ptype, 0));
	    }
	  OMP_CLAUSE_DECL (c) = t;
	  પાછા ખોટું;
	}
      first = c_fully_fold (first, ખોટું, ખાલી);
      OMP_CLAUSE_DECL (c) = first;
      જો (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_HAS_DEVICE_ADDR)
	પાછા ખોટું;
      /* Don't set OMP_CLAUSE_SIZE for bare attach/detach clauses.  */
      જો (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_MAP
	  || (OMP_CLAUSE_MAP_KIND (c) != GOMP_MAP_ATTACH
	      && OMP_CLAUSE_MAP_KIND (c) != GOMP_MAP_DETACH
	      && OMP_CLAUSE_MAP_KIND (c) != GOMP_MAP_FORCE_DETACH))
	{
	  જો (size)
	    size = c_fully_fold (size, ખોટું, ખાલી);
	  OMP_CLAUSE_SIZE (c) = size;
	}

      જો (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_MAP)
	પાછા ખોટું;

      auto_vec<omp_addr_token *, 10> addr_tokens;

      જો (!omp_parse_પદાવલિ (addr_tokens, first))
	પાછા સાચું;

      c_omp_address_inspector ai (OMP_CLAUSE_LOCATION (c), t);

      વૃક્ષ nc = ai.expand_map_clause (c, first, addr_tokens, ort);
      જો (nc != error_mark_ગાંઠ)
	{
	  using નામાકાશ omp_addr_tokenizer;

	  જો (ai.maybe_zero_length_array_section (c))
	    OMP_CLAUSE_MAP_MAYBE_ZERO_LENGTH_ARRAY_SECTION (c) = 1;

	  /* !!! If we're accessing a base decl via chained access
	     methods (e.g. multiple indirections), duplicate clause
	     detection won't work properly.  Skip it in that case.  */
	  જો ((addr_tokens[0]->type == STRUCTURE_BASE
	       || addr_tokens[0]->type == ARRAY_BASE)
	      && addr_tokens[0]->u.structure_base_kind == BASE_DECL
	      && addr_tokens[1]->type == ACCESS_METHOD
	      && omp_access_chain_p (addr_tokens, 1))
	    c = nc;

	  પાછા ખોટું;
	}
    }
  પાછા ખોટું;
}

/* Helper function of finish_omp_clauses.  Clone STMT as if we were making
   an inline call.  But, remap
   the OMP_DECL1 VAR_DECL (omp_out resp. omp_orig) to PLACEHOLDER
   and OMP_DECL2 VAR_DECL (omp_in resp. omp_priv) to DECL.  */

સ્થિર વૃક્ષ
c_clone_omp_udr (વૃક્ષ stmt, વૃક્ષ omp_decl1, વૃક્ષ omp_decl2,
		 વૃક્ષ decl, વૃક્ષ placeholder)
{
  copy_body_data id;
  hash_map<વૃક્ષ, વૃક્ષ> decl_map;

  decl_map.put (omp_decl1, placeholder);
  decl_map.put (omp_decl2, decl);
  memset (&id, 0, કદ (id));
  id.src_fn = DECL_CONTEXT (omp_decl1);
  id.dst_fn = current_function_decl;
  id.src_cfun = DECL_STRUCT_FUNCTION (id.src_fn);
  id.decl_map = &decl_map;

  id.copy_decl = copy_decl_no_change;
  id.transform_call_graph_edges = CB_CGE_DUPLICATE;
  id.transform_new_cfg = સાચું;
  id.transform_return_to_modify = ખોટું;
  id.eh_lp_nr = 0;
  walk_વૃક્ષ (&stmt, copy_વૃક્ષ_body_r, &id, ખાલી);
  પાછા stmt;
}

/* Helper function of c_finish_omp_clauses, called via walk_tree.
   Find OMP_CLAUSE_PLACEHOLDER (passed in DATA) in *TP.  */

સ્થિર વૃક્ષ
c_find_omp_placeholder_r (વૃક્ષ *tp, પૂર્ણાંક *, શૂન્ય *data)
{
  જો (*tp == (વૃક્ષ) data)
    પાછા *tp;
  પાછા NULL_વૃક્ષ;
}

/* Similarly, but also walk aggregate fields.  */

સંરચના c_find_omp_var_s { વૃક્ષ var; hash_set<વૃક્ષ> *pset; };

સ્થિર વૃક્ષ
c_find_omp_var_r (વૃક્ષ *tp, પૂર્ણાંક *, શૂન્ય *data)
{
  જો (*tp == ((સંરચના c_find_omp_var_s *) data)->var)
    પાછા *tp;
  જો (RECORD_OR_UNION_TYPE_P (*tp))
    {
      વૃક્ષ field;
      hash_set<વૃક્ષ> *pset = ((સંરચના c_find_omp_var_s *) data)->pset;

      માટે (field = TYPE_FIELDS (*tp); field;
	   field = DECL_CHAIN (field))
	જો (વૃક્ષ_CODE (field) == FIELD_DECL)
	  {
	    વૃક્ષ ret = walk_વૃક્ષ (&DECL_FIELD_OFFSET (field),
				  c_find_omp_var_r, data, pset);
	    જો (ret)
	      પાછા ret;
	    ret = walk_વૃક્ષ (&DECL_SIZE (field), c_find_omp_var_r, data, pset);
	    જો (ret)
	      પાછા ret;
	    ret = walk_વૃક્ષ (&DECL_SIZE_UNIT (field), c_find_omp_var_r, data,
			     pset);
	    જો (ret)
	      પાછા ret;
	    ret = walk_વૃક્ષ (&વૃક્ષ_TYPE (field), c_find_omp_var_r, data, pset);
	    જો (ret)
	      પાછા ret;
	  }
    }
  નહીંતર જો (INTEGRAL_TYPE_P (*tp))
    પાછા walk_વૃક્ષ (&TYPE_MAX_કિંમત (*tp), c_find_omp_var_r, data,
		      ((સંરચના c_find_omp_var_s *) data)->pset);
  પાછા NULL_વૃક્ષ;
}

/* Finish OpenMP iterators ITER.  Return true if they are erroneous
   and clauses containing them should be removed.  */

સ્થિર તાર્કિક
c_omp_finish_iterators (વૃક્ષ iter)
{
  તાર્કિક ret = ખોટું;
  માટે (વૃક્ષ it = iter; it; it = વૃક્ષ_CHAIN (it))
    {
      વૃક્ષ var = OMP_ITERATOR_VAR (it);
      વૃક્ષ begin = OMP_ITERATOR_BEGIN (it);
      વૃક્ષ end = OMP_ITERATOR_END (it);
      વૃક્ષ step = OMP_ITERATOR_STEP (it);
      વૃક્ષ orig_step;
      વૃક્ષ type = વૃક્ષ_TYPE (var);
      location_t loc = DECL_SOURCE_LOCATION (var);
      જો (type == error_mark_ગાંઠ)
	{
	  ret = સાચું;
	  ચાલુ;
	}
      જો (!INTEGRAL_TYPE_P (type) && !POINTER_TYPE_P (type))
	{
	  error_at (loc, "iterator %qD has neither integral nor pointer type",
		    var);
	  ret = સાચું;
	  ચાલુ;
	}
      નહીંતર જો (TYPE_ATOMIC (type))
	{
	  error_at (loc, "iterator %qD has %<_Atomic%> qualified type", var);
	  ret = સાચું;
	  ચાલુ;
	}
      નહીંતર જો (TYPE_READONLY (type))
	{
	  error_at (loc, "iterator %qD has const qualified type", var);
	  ret = સાચું;
	  ચાલુ;
	}
      નહીંતર જો (step == error_mark_ગાંઠ
	       || વૃક્ષ_TYPE (step) == error_mark_ગાંઠ)
	{
	  ret = સાચું;
	  ચાલુ;
	}
      નહીંતર જો (!INTEGRAL_TYPE_P (વૃક્ષ_TYPE (step)))
	{
	  error_at (પદાવલિ_LOC_OR_LOC (step, loc),
		    "iterator step with non-integral type");
	  ret = સાચું;
	  ચાલુ;
	}
      begin = c_fully_fold (build_c_cast (loc, type, begin), ખોટું, ખાલી);
      end = c_fully_fold (build_c_cast (loc, type, end), ખોટું, ખાલી);
      orig_step = save_પદાવલિ (c_fully_fold (step, ખોટું, ખાલી));
      વૃક્ષ stype = POINTER_TYPE_P (type) ? sizetype : type;
      step = c_fully_fold (build_c_cast (loc, stype, orig_step), ખોટું, ખાલી);
      જો (POINTER_TYPE_P (type))
	{
	  begin = save_પદાવલિ (begin);
	  step = pointer_int_sum (loc, PLUS_પદાવલિ, begin, step);
	  step = fold_build2_loc (loc, MINUS_પદાવલિ, sizetype,
				  fold_convert (sizetype, step),
				  fold_convert (sizetype, begin));
	  step = fold_convert (ssizetype, step);
	}
      જો (integer_zerop (step))
	{
	  error_at (loc, "iterator %qD has zero step", var);
	  ret = સાચું;
	  ચાલુ;
	}

      જો (begin == error_mark_ગાંઠ
	  || end == error_mark_ગાંઠ
	  || step == error_mark_ગાંઠ
	  || orig_step == error_mark_ગાંઠ)
	{
	  ret = સાચું;
	  ચાલુ;
	}
      hash_set<વૃક્ષ> pset;
      વૃક્ષ it2;
      માટે (it2 = વૃક્ષ_CHAIN (it); it2; it2 = વૃક્ષ_CHAIN (it2))
	{
	  વૃક્ષ var2 = OMP_ITERATOR_VAR (it2);
	  વૃક્ષ begin2 = OMP_ITERATOR_BEGIN (it2);
	  વૃક્ષ end2 = OMP_ITERATOR_END (it2);
	  વૃક્ષ step2 = OMP_ITERATOR_STEP (it2);
	  વૃક્ષ type2 = વૃક્ષ_TYPE (var2);
	  location_t loc2 = DECL_SOURCE_LOCATION (var2);
	  સંરચના c_find_omp_var_s data = { var, &pset };
	  જો (walk_વૃક્ષ (&type2, c_find_omp_var_r, &data, &pset))
	    {
	      error_at (loc2,
			"type of iterator %qD refers to outer iterator %qD",
			var2, var);
	      તોડો;
	    }
	  નહીંતર જો (walk_વૃક્ષ (&begin2, c_find_omp_var_r, &data, &pset))
	    {
	      error_at (પદાવલિ_LOC_OR_LOC (begin2, loc2),
			"begin expression refers to outer iterator %qD", var);
	      તોડો;
	    }
	  નહીંતર જો (walk_વૃક્ષ (&end2, c_find_omp_var_r, &data, &pset))
	    {
	      error_at (પદાવલિ_LOC_OR_LOC (end2, loc2),
			"end expression refers to outer iterator %qD", var);
	      તોડો;
	    }
	  નહીંતર જો (walk_વૃક્ષ (&step2, c_find_omp_var_r, &data, &pset))
	    {
	      error_at (પદાવલિ_LOC_OR_LOC (step2, loc2),
			"step expression refers to outer iterator %qD", var);
	      તોડો;
	    }
	}
      જો (it2)
	{
	  ret = સાચું;
	  ચાલુ;
	}
      OMP_ITERATOR_BEGIN (it) = begin;
      OMP_ITERATOR_END (it) = end;
      OMP_ITERATOR_STEP (it) = step;
      OMP_ITERATOR_ORIG_STEP (it) = orig_step;
    }
  પાછા ret;
}

/* Ensure that pointers are used in OpenACC attach and detach clauses.
   Return true if an error has been detected.  */

સ્થિર તાર્કિક
c_oacc_check_attachments (વૃક્ષ c)
{
  જો (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_MAP)
    પાછા ખોટું;

  /* OpenACC attach / detach clauses must be pointers.  */
  જો (OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_ATTACH
      || OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_DETACH)
    {
      વૃક્ષ t = OMP_CLAUSE_DECL (c);

      જ્યારે (વૃક્ષ_CODE (t) == OMP_ARRAY_SECTION)
	t = વૃક્ષ_OPERAND (t, 0);

      જો (વૃક્ષ_CODE (વૃક્ષ_TYPE (t)) != POINTER_TYPE)
	{
	  error_at (OMP_CLAUSE_LOCATION (c), "expected pointer in %qs clause",
		    user_omp_clause_code_name (c, સાચું));
	  પાછા સાચું;
	}
    }

  પાછા ખોટું;
}

/* For all elements of CLAUSES, validate them against their constraints.
   Remove any elements from the list that are invalid.  */

વૃક્ષ
c_finish_omp_clauses (વૃક્ષ clauses, ગણના c_omp_region_type ort)
{
  bitmap_head generic_head, firstprivate_head, lastprivate_head;
  bitmap_head aligned_head, map_head, map_field_head, map_firstprivate_head;
  bitmap_head oacc_reduction_head, is_on_device_head;
  વૃક્ષ c, t, type, *pc;
  વૃક્ષ simdlen = NULL_વૃક્ષ, safelen = NULL_વૃક્ષ;
  તાર્કિક branch_seen = ખોટું;
  તાર્કિક copyprivate_seen = ખોટું;
  તાર્કિક mergeable_seen = ખોટું;
  વૃક્ષ *detach_seen = ખાલી;
  તાર્કિક linear_variable_step_check = ખોટું;
  વૃક્ષ *nowait_clause = ખાલી;
  વૃક્ષ *grainsize_seen = ખાલી;
  તાર્કિક અંક_tasks_seen = ખોટું;
  વૃક્ષ ordered_clause = NULL_વૃક્ષ;
  વૃક્ષ schedule_clause = NULL_વૃક્ષ;
  તાર્કિક oacc_async = ખોટું;
  વૃક્ષ last_iterators = NULL_વૃક્ષ;
  તાર્કિક last_iterators_remove = ખોટું;
  વૃક્ષ *nogroup_seen = ખાલી;
  વૃક્ષ *order_clause = ખાલી;
  /* 1 if normal/task reduction has been seen, -1 if inscan reduction
     has been seen, -2 if mixed inscan/normal reduction diagnosed.  */
  પૂર્ણાંક reduction_seen = 0;
  તાર્કિક allocate_seen = ખોટું;
  તાર્કિક implicit_moved = ખોટું;
  તાર્કિક target_in_reduction_seen = ખોટું;
  વૃક્ષ *full_seen = ખાલી;
  તાર્કિક partial_seen = ખોટું;
  તાર્કિક openacc = (ort & C_ORT_ACC) != 0;
  તાર્કિક init_seen = ખોટું;
  તાર્કિક init_use_destroy_seen = ખોટું;
  વૃક્ષ init_no_targetsync_clause = NULL_વૃક્ષ;
  વૃક્ષ depend_clause = NULL_વૃક્ષ;

  જો (!openacc)
    clauses = omp_remove_duplicate_maps (clauses, સાચું);

  bitmap_obstack_initialize (ખાલી);
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

  જો (openacc)
    માટે (c = clauses; c; c = OMP_CLAUSE_CHAIN (c))
      જો (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_ASYNC)
	{
	  oacc_async = સાચું;
	  તોડો;
	}

  વૃક્ષ *grp_start_p = ખાલી, grp_sentinel = NULL_વૃક્ષ;

  માટે (pc = &clauses, c = clauses; c ; c = *pc)
    {
      તાર્કિક remove = ખોટું;
      તાર્કિક need_complete = ખોટું;
      તાર્કિક need_implicitly_determined = ખોટું;

      /* We've reached the end of a list of expanded nodes.  Reset the group
	 start pointer.  */
      જો (c == grp_sentinel)
	{
	  જો (grp_start_p
	      && OMP_CLAUSE_HAS_ITERATORS (*grp_start_p))
	    માટે (વૃક્ષ gc = *grp_start_p; gc != grp_sentinel;
		 gc = OMP_CLAUSE_CHAIN (gc))
	      OMP_CLAUSE_ITERATORS (gc) = OMP_CLAUSE_ITERATORS (*grp_start_p);
	  grp_start_p = ખાલી;
	}

      પસંદગી (OMP_CLAUSE_CODE (c))
	{
	સ્થિતિ OMP_CLAUSE_SHARED:
	  need_implicitly_determined = સાચું;
	  જાઓ check_dup_generic;

	સ્થિતિ OMP_CLAUSE_PRIVATE:
	  need_complete = સાચું;
	  need_implicitly_determined = સાચું;
	  જાઓ check_dup_generic;

	સ્થિતિ OMP_CLAUSE_REDUCTION:
	  જો (reduction_seen == 0)
	    reduction_seen = OMP_CLAUSE_REDUCTION_INSCAN (c) ? -1 : 1;
	  નહીંતર જો (reduction_seen != -2
		   && reduction_seen != (OMP_CLAUSE_REDUCTION_INSCAN (c)
					 ? -1 : 1))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<inscan%> and non-%<inscan%> %<reduction%> clauses "
			"on the same construct");
	      reduction_seen = -2;
	    }
	  /* FALLTHRU */
	સ્થિતિ OMP_CLAUSE_IN_REDUCTION:
	સ્થિતિ OMP_CLAUSE_TASK_REDUCTION:
	  need_implicitly_determined = સાચું;
	  t = OMP_CLAUSE_DECL (c);
	  જો (વૃક્ષ_CODE (t) == OMP_ARRAY_SECTION)
	    {
	      જો (handle_omp_array_sections (c, ort))
		{
		  remove = સાચું;
		  તોડો;
		}

	      t = OMP_CLAUSE_DECL (c);
	      જો (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_REDUCTION
		  && OMP_CLAUSE_REDUCTION_INSCAN (c))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%<inscan%> %<reduction%> clause with array "
			    "section");
		  remove = સાચું;
		  તોડો;
		}
	    }
	  t = require_complete_type (OMP_CLAUSE_LOCATION (c), t);
	  જો (t == error_mark_ગાંઠ)
	    {
	      remove = સાચું;
	      તોડો;
	    }
	  જો (oacc_async)
	    c_mark_addressable (t);
	  type = વૃક્ષ_TYPE (t);
	  જો (વૃક્ષ_CODE (t) == MEM_REF)
	    type = વૃક્ષ_TYPE (type);
	  જો (વૃક્ષ_CODE (type) == ARRAY_TYPE)
	    {
	      વૃક્ષ oatype = type;
	      gcc_assert (વૃક્ષ_CODE (t) != MEM_REF);
	      જ્યારે (વૃક્ષ_CODE (type) == ARRAY_TYPE)
		type = વૃક્ષ_TYPE (type);
	      જો (integer_zerop (TYPE_SIZE_UNIT (type)))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD in %<reduction%> clause is a zero size array",
			    t);
		  remove = સાચું;
		  તોડો;
		}
	      વૃક્ષ size = size_binop (EXACT_DIV_પદાવલિ, TYPE_SIZE_UNIT (oatype),
				      TYPE_SIZE_UNIT (type));
	      જો (integer_zerop (size))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD in %<reduction%> clause is a zero size array",
			    t);
		  remove = સાચું;
		  તોડો;
		}
	      size = size_binop (MINUS_પદાવલિ, size, size_one_ગાંઠ);
	      size = save_પદાવલિ (size);
	      વૃક્ષ index_type = build_index_type (size);
	      વૃક્ષ atype = c_build_array_type (TYPE_MAIN_VARIANT (type),
					       index_type);
	      atype = c_build_qualified_type (atype, TYPE_QUALS (type));
	      વૃક્ષ ptype = c_build_pointer_type (type);
	      જો (વૃક્ષ_CODE (વૃક્ષ_TYPE (t)) == ARRAY_TYPE)
		t = build_fold_addr_પદાવલિ (t);
	      t = build2 (MEM_REF, atype, t, build_int_cst (ptype, 0));
	      OMP_CLAUSE_DECL (c) = t;
	    }
	  જો (TYPE_ATOMIC (type))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<_Atomic%> %qE in %<reduction%> clause", t);
	      remove = સાચું;
	      તોડો;
	    }
	  જો (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_REDUCTION
	      || OMP_CLAUSE_REDUCTION_TASK (c))
	    {
	      /* Disallow zero sized or potentially zero sized task
		 reductions.  */
	      જો (integer_zerop (TYPE_SIZE_UNIT (type)))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "zero sized type %qT in %qs clause", type,
			    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		  remove = સાચું;
		  તોડો;
		}
	      નહીંતર જો (વૃક્ષ_CODE (TYPE_SIZE_UNIT (type)) != INTEGER_CST)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "variable sized type %qT in %qs clause", type,
			    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		  remove = સાચું;
		  તોડો;
		}
	    }
	  જો (OMP_CLAUSE_REDUCTION_PLACEHOLDER (c) == NULL_વૃક્ષ
	      && (FLOAT_TYPE_P (type)
		  || વૃક્ષ_CODE (type) == COMPLEX_TYPE))
	    {
	      ગણના વૃક્ષ_code r_code = OMP_CLAUSE_REDUCTION_CODE (c);
	      અચલ અક્ષર *r_name = ખાલી;

	      પસંદગી (r_code)
		{
		સ્થિતિ PLUS_પદાવલિ:
		સ્થિતિ MULT_પદાવલિ:
		સ્થિતિ MINUS_પદાવલિ:
		સ્થિતિ TRUTH_ANDIF_પદાવલિ:
		સ્થિતિ TRUTH_ORIF_પદાવલિ:
		  તોડો;
		સ્થિતિ MIN_પદાવલિ:
		  જો (વૃક્ષ_CODE (type) == COMPLEX_TYPE)
		    r_name = "min";
		  તોડો;
		સ્થિતિ MAX_પદાવલિ:
		  જો (વૃક્ષ_CODE (type) == COMPLEX_TYPE)
		    r_name = "max";
		  તોડો;
		સ્થિતિ BIT_AND_પદાવલિ:
		  r_name = "&";
		  તોડો;
		સ્થિતિ BIT_XOR_પદાવલિ:
		  r_name = "^";
		  તોડો;
		સ્થિતિ BIT_IOR_પદાવલિ:
		  r_name = "|";
		  તોડો;
		મૂળભૂત:
		  gcc_unreachable ();
		}
	      જો (r_name)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qE has invalid type for %<reduction(%s)%>",
			    t, r_name);
		  remove = સાચું;
		  તોડો;
		}
	    }
	  નહીંતર જો (OMP_CLAUSE_REDUCTION_PLACEHOLDER (c) == error_mark_ગાંઠ)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"user defined reduction not found for %qE", t);
	      remove = સાચું;
	      તોડો;
	    }
	  નહીંતર જો (OMP_CLAUSE_REDUCTION_PLACEHOLDER (c))
	    {
	      વૃક્ષ list = OMP_CLAUSE_REDUCTION_PLACEHOLDER (c);
	      type = TYPE_MAIN_VARIANT (type);
	      વૃક્ષ placeholder = build_decl (OMP_CLAUSE_LOCATION (c),
					     VAR_DECL, NULL_વૃક્ષ, type);
	      વૃક્ષ decl_placeholder = NULL_વૃક્ષ;
	      OMP_CLAUSE_REDUCTION_PLACEHOLDER (c) = placeholder;
	      DECL_ARTIFICIAL (placeholder) = 1;
	      DECL_IGNORED_P (placeholder) = 1;
	      જો (વૃક્ષ_CODE (t) == MEM_REF)
		{
		  decl_placeholder = build_decl (OMP_CLAUSE_LOCATION (c),
						 VAR_DECL, NULL_વૃક્ષ, type);
		  OMP_CLAUSE_REDUCTION_DECL_PLACEHOLDER (c) = decl_placeholder;
		  DECL_ARTIFICIAL (decl_placeholder) = 1;
		  DECL_IGNORED_P (decl_placeholder) = 1;
		}
	      જો (વૃક્ષ_ADDRESSABLE (વૃક્ષ_VEC_ELT (list, 0)))
		c_mark_addressable (placeholder);
	      જો (વૃક્ષ_ADDRESSABLE (વૃક્ષ_VEC_ELT (list, 1)))
		c_mark_addressable (decl_placeholder ? decl_placeholder
				    : OMP_CLAUSE_DECL (c));
	      OMP_CLAUSE_REDUCTION_MERGE (c)
		= c_clone_omp_udr (વૃક્ષ_VEC_ELT (list, 2),
				   વૃક્ષ_VEC_ELT (list, 0),
				   વૃક્ષ_VEC_ELT (list, 1),
				   decl_placeholder ? decl_placeholder
				   : OMP_CLAUSE_DECL (c), placeholder);
	      OMP_CLAUSE_REDUCTION_MERGE (c)
		= build3_loc (OMP_CLAUSE_LOCATION (c), BIND_પદાવલિ,
			      void_type_ગાંઠ, NULL_વૃક્ષ,
			      OMP_CLAUSE_REDUCTION_MERGE (c), NULL_વૃક્ષ);
	      વૃક્ષ_SIDE_EFFECTS (OMP_CLAUSE_REDUCTION_MERGE (c)) = 1;
	      જો (વૃક્ષ_VEC_LENGTH (list) == 6)
		{
		  જો (વૃક્ષ_ADDRESSABLE (વૃક્ષ_VEC_ELT (list, 3)))
		    c_mark_addressable (decl_placeholder ? decl_placeholder
					: OMP_CLAUSE_DECL (c));
		  જો (વૃક્ષ_ADDRESSABLE (વૃક્ષ_VEC_ELT (list, 4)))
		    c_mark_addressable (placeholder);
		  વૃક્ષ init = વૃક્ષ_VEC_ELT (list, 5);
		  જો (init == error_mark_ગાંઠ)
		    init = DECL_INITIAL (વૃક્ષ_VEC_ELT (list, 3));
		  OMP_CLAUSE_REDUCTION_INIT (c)
		    = c_clone_omp_udr (init, વૃક્ષ_VEC_ELT (list, 4),
				       વૃક્ષ_VEC_ELT (list, 3),
				       decl_placeholder ? decl_placeholder
				       : OMP_CLAUSE_DECL (c), placeholder);
		  જો (વૃક્ષ_VEC_ELT (list, 5) == error_mark_ગાંઠ)
		    {
		      વૃક્ષ v = decl_placeholder ? decl_placeholder : t;
		      OMP_CLAUSE_REDUCTION_INIT (c)
			= build2 (INIT_પદાવલિ, વૃક્ષ_TYPE (v), v,
				  OMP_CLAUSE_REDUCTION_INIT (c));
		    }
		  જો (walk_વૃક્ષ (&OMP_CLAUSE_REDUCTION_INIT (c),
				 c_find_omp_placeholder_r,
				 placeholder, ખાલી))
		    OMP_CLAUSE_REDUCTION_OMP_ORIG_REF (c) = 1;
		}
	      નહીંતર
		{
		  વૃક્ષ init;
		  વૃક્ષ v = decl_placeholder ? decl_placeholder : t;
		  જો (AGGREGATE_TYPE_P (વૃક્ષ_TYPE (v)))
		    init = build_constructor (વૃક્ષ_TYPE (v), ખાલી);
		  નહીંતર
		    init = fold_convert (વૃક્ષ_TYPE (v), integer_zero_ગાંઠ);
		  OMP_CLAUSE_REDUCTION_INIT (c)
		    = build2 (INIT_પદાવલિ, વૃક્ષ_TYPE (v), v, init);
		}
	      OMP_CLAUSE_REDUCTION_INIT (c)
		= build3_loc (OMP_CLAUSE_LOCATION (c), BIND_પદાવલિ,
			      void_type_ગાંઠ, NULL_વૃક્ષ,
			       OMP_CLAUSE_REDUCTION_INIT (c), NULL_વૃક્ષ);
	      વૃક્ષ_SIDE_EFFECTS (OMP_CLAUSE_REDUCTION_INIT (c)) = 1;
	    }
	  જો (વૃક્ષ_CODE (t) == MEM_REF)
	    {
	      જો (TYPE_SIZE_UNIT (વૃક્ષ_TYPE (વૃક્ષ_TYPE (t))) == NULL_વૃક્ષ
		  || વૃક્ષ_CODE (TYPE_SIZE_UNIT (વૃક્ષ_TYPE (વૃક્ષ_TYPE (t))))
		     != INTEGER_CST)
		{
		  sorry ("variable length element type in array "
			 "%<reduction%> clause");
		  remove = સાચું;
		  તોડો;
		}
	      t = વૃક્ષ_OPERAND (t, 0);
	      જો (વૃક્ષ_CODE (t) == POINTER_PLUS_પદાવલિ)
		t = વૃક્ષ_OPERAND (t, 0);
	      જો (વૃક્ષ_CODE (t) == ADDR_પદાવલિ)
		t = વૃક્ષ_OPERAND (t, 0);
	    }
	  જાઓ check_dup_generic_t;

	સ્થિતિ OMP_CLAUSE_COPYPRIVATE:
	  copyprivate_seen = સાચું;
	  જો (nowait_clause)
	    {
	      error_at (OMP_CLAUSE_LOCATION (*nowait_clause),
			"%<nowait%> clause must not be used together "
			"with %<copyprivate%> clause");
	      *nowait_clause = OMP_CLAUSE_CHAIN (*nowait_clause);
	      nowait_clause = ખાલી;
	    }
	  જાઓ check_dup_generic;

	સ્થિતિ OMP_CLAUSE_COPYIN:
	  t = OMP_CLAUSE_DECL (c);
	  જો (!VAR_P (t) || !DECL_THREAD_LOCAL_P (t))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE must be %<threadprivate%> for %<copyin%>", t);
	      remove = સાચું;
	      તોડો;
	    }
	  જાઓ check_dup_generic;

	સ્થિતિ OMP_CLAUSE_LINEAR:
	  જો (ort != C_ORT_OMP_DECLARE_SIMD)
	    need_implicitly_determined = સાચું;
	  t = OMP_CLAUSE_DECL (c);
	  જો (ort != C_ORT_OMP_DECLARE_SIMD
	      && OMP_CLAUSE_LINEAR_KIND (c) != OMP_CLAUSE_LINEAR_DEFAULT
	      && OMP_CLAUSE_LINEAR_OLD_LINEAR_MODIFIER (c))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"modifier should not be specified in %<linear%> "
			"clause on %<simd%> or %<for%> constructs when not "
			"using OpenMP 5.2 modifiers");
	      OMP_CLAUSE_LINEAR_KIND (c) = OMP_CLAUSE_LINEAR_DEFAULT;
	    }
	  જો (!INTEGRAL_TYPE_P (વૃક્ષ_TYPE (t))
	      && વૃક્ષ_CODE (વૃક્ષ_TYPE (t)) != POINTER_TYPE)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"linear clause applied to non-integral non-pointer "
			"variable with type %qT", વૃક્ષ_TYPE (t));
	      remove = સાચું;
	      તોડો;
	    }
	  જો (TYPE_ATOMIC (વૃક્ષ_TYPE (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<_Atomic%> %qD in %<linear%> clause", t);
	      remove = સાચું;
	      તોડો;
	    }
	  જો (ort == C_ORT_OMP_DECLARE_SIMD)
	    {
	      વૃક્ષ s = OMP_CLAUSE_LINEAR_STEP (c);
	      જો (વૃક્ષ_CODE (s) == PARM_DECL)
		{
		  OMP_CLAUSE_LINEAR_VARIABLE_STRIDE (c) = 1;
		  /* map_head bitmap is used as uniform_head if
		     declare_simd.  */
		  જો (!bitmap_bit_p (&map_head, DECL_UID (s)))
		    linear_variable_step_check = સાચું;
		  જાઓ check_dup_generic;
		}
	      જો (વૃક્ષ_CODE (s) != INTEGER_CST)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%<linear%> clause step %qE is neither constant "
			    "nor a parameter", s);
		  remove = સાચું;
		  તોડો;
		}
	    }
	  જો (વૃક્ષ_CODE (વૃક્ષ_TYPE (OMP_CLAUSE_DECL (c))) == POINTER_TYPE)
	    {
	      વૃક્ષ s = OMP_CLAUSE_LINEAR_STEP (c);
	      s = pointer_int_sum (OMP_CLAUSE_LOCATION (c), PLUS_પદાવલિ,
				   OMP_CLAUSE_DECL (c), s);
	      s = fold_build2_loc (OMP_CLAUSE_LOCATION (c), MINUS_પદાવલિ,
				   sizetype, fold_convert (sizetype, s),
				   fold_convert
				     (sizetype, OMP_CLAUSE_DECL (c)));
	      જો (s == error_mark_ગાંઠ)
		s = size_one_ગાંઠ;
	      OMP_CLAUSE_LINEAR_STEP (c) = s;
	    }
	  નહીંતર
	    OMP_CLAUSE_LINEAR_STEP (c)
	      = fold_convert (વૃક્ષ_TYPE (t), OMP_CLAUSE_LINEAR_STEP (c));
	  જાઓ check_dup_generic;

	check_dup_generic:
	  t = OMP_CLAUSE_DECL (c);
	check_dup_generic_t:
	  જો (!VAR_P (t) && વૃક્ષ_CODE (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in clause %qs", t,
			omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	      remove = સાચું;
	    }
	  નહીંતર જો ((openacc && OMP_CLAUSE_CODE (c) == OMP_CLAUSE_REDUCTION)
		   || (ort == C_ORT_OMP
		       && (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_USE_DEVICE_PTR
			   || (OMP_CLAUSE_CODE (c)
			       == OMP_CLAUSE_USE_DEVICE_ADDR)))
		   || (ort == C_ORT_OMP_TARGET
		       && OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IN_REDUCTION))
	    {
	      જો (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IN_REDUCTION
		  && (bitmap_bit_p (&generic_head, DECL_UID (t))
		      || bitmap_bit_p (&firstprivate_head, DECL_UID (t))))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD appears more than once in data-sharing "
			    "clauses", t);
		  remove = સાચું;
		  તોડો;
		}
	      જો (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IN_REDUCTION)
		target_in_reduction_seen = સાચું;
	      જો (bitmap_bit_p (&oacc_reduction_head, DECL_UID (t)))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    openacc
			    ? "%qD appears more than once in reduction clauses"
			    : "%qD appears more than once in data clauses",
			    t);
		  remove = સાચું;
		}
	      નહીંતર
		bitmap_set_bit (&oacc_reduction_head, DECL_UID (t));
	    }
	  નહીંતર જો (bitmap_bit_p (&generic_head, DECL_UID (t))
		   || bitmap_bit_p (&firstprivate_head, DECL_UID (t))
		   || bitmap_bit_p (&lastprivate_head, DECL_UID (t))
		   || bitmap_bit_p (&map_firstprivate_head, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE appears more than once in data clauses", t);
	      remove = સાચું;
	    }
	  નહીંતર જો ((OMP_CLAUSE_CODE (c) == OMP_CLAUSE_PRIVATE
		    || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_HAS_DEVICE_ADDR
		    || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IS_DEVICE_PTR)
		   && bitmap_bit_p (&map_head, DECL_UID (t)))
	    {
	      જો (openacc)
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD appears more than once in data clauses", t);
	      નહીંતર
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD appears both in data and map clauses", t);
	      remove = સાચું;
	    }
	  નહીંતર
	    bitmap_set_bit (&generic_head, DECL_UID (t));
	  તોડો;

	સ્થિતિ OMP_CLAUSE_FIRSTPRIVATE:
	  જો (OMP_CLAUSE_FIRSTPRIVATE_IMPLICIT (c) && !implicit_moved)
	    {
	    move_implicit:
	      implicit_moved = સાચું;
	      /* Move firstprivate and map clauses with
		 OMP_CLAUSE_{FIRSTPRIVATE,MAP}_IMPLICIT set to the end of
		 clauses chain.  */
	      વૃક્ષ cl1 = NULL_વૃક્ષ, cl2 = NULL_વૃક્ષ;
	      વૃક્ષ *pc1 = pc, *pc2 = &cl1, *pc3 = &cl2;
	      જ્યારે (*pc1)
		જો (OMP_CLAUSE_CODE (*pc1) == OMP_CLAUSE_FIRSTPRIVATE
		    && OMP_CLAUSE_FIRSTPRIVATE_IMPLICIT (*pc1))
		  {
		    *pc3 = *pc1;
		    pc3 = &OMP_CLAUSE_CHAIN (*pc3);
		    *pc1 = OMP_CLAUSE_CHAIN (*pc1);
		  }
		નહીંતર જો (OMP_CLAUSE_CODE (*pc1) == OMP_CLAUSE_MAP
			 && OMP_CLAUSE_MAP_IMPLICIT (*pc1))
		  {
		    *pc2 = *pc1;
		    pc2 = &OMP_CLAUSE_CHAIN (*pc2);
		    *pc1 = OMP_CLAUSE_CHAIN (*pc1);
		  }
		નહીંતર
		  pc1 = &OMP_CLAUSE_CHAIN (*pc1);
	      *pc3 = ખાલી;
	      *pc2 = cl2;
	      *pc1 = cl1;
	      ચાલુ;
	    }
	  t = OMP_CLAUSE_DECL (c);
	  need_complete = સાચું;
	  need_implicitly_determined = સાચું;
	  જો (!VAR_P (t) && વૃક્ષ_CODE (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in clause %<firstprivate%>", t);
	      remove = સાચું;
	    }
	  નહીંતર જો (OMP_CLAUSE_FIRSTPRIVATE_IMPLICIT (c)
		   && !OMP_CLAUSE_FIRSTPRIVATE_IMPLICIT_TARGET (c)
		   && bitmap_bit_p (&map_firstprivate_head, DECL_UID (t)))
	    remove = સાચું;
	  નહીંતર જો (bitmap_bit_p (&generic_head, DECL_UID (t))
		   || bitmap_bit_p (&firstprivate_head, DECL_UID (t))
		   || bitmap_bit_p (&map_firstprivate_head, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE appears more than once in data clauses", t);
	      remove = સાચું;
	    }
	  નહીંતર જો (bitmap_bit_p (&map_head, DECL_UID (t))
		   || bitmap_bit_p (&map_field_head, DECL_UID (t)))
	    {
	      જો (openacc)
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD appears more than once in data clauses", t);
	      નહીંતર જો (OMP_CLAUSE_FIRSTPRIVATE_IMPLICIT (c)
		       && !OMP_CLAUSE_FIRSTPRIVATE_IMPLICIT_TARGET (c))
		/* Silently drop the clause.  */;
	      નહીંતર
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD appears both in data and map clauses", t);
	      remove = સાચું;
	    }
	  નહીંતર
	    bitmap_set_bit (&firstprivate_head, DECL_UID (t));
	  તોડો;

	સ્થિતિ OMP_CLAUSE_LASTPRIVATE:
	  t = OMP_CLAUSE_DECL (c);
	  need_complete = સાચું;
	  need_implicitly_determined = સાચું;
	  જો (!VAR_P (t) && વૃક્ષ_CODE (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in clause %<lastprivate%>", t);
	      remove = સાચું;
	    }
	  નહીંતર જો (bitmap_bit_p (&generic_head, DECL_UID (t))
		   || bitmap_bit_p (&lastprivate_head, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
		     "%qE appears more than once in data clauses", t);
	      remove = સાચું;
	    }
	  નહીંતર
	    bitmap_set_bit (&lastprivate_head, DECL_UID (t));
	  તોડો;

	સ્થિતિ OMP_CLAUSE_ALIGNED:
	  t = OMP_CLAUSE_DECL (c);
	  જો (!VAR_P (t) && વૃક્ષ_CODE (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in %<aligned%> clause", t);
	      remove = સાચું;
	    }
	  નહીંતર જો (!POINTER_TYPE_P (વૃક્ષ_TYPE (t))
		   && વૃક્ષ_CODE (વૃક્ષ_TYPE (t)) != ARRAY_TYPE)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE in %<aligned%> clause is neither a pointer nor "
			"an array", t);
	      remove = સાચું;
	    }
	  નહીંતર જો (TYPE_ATOMIC (વૃક્ષ_TYPE (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<_Atomic%> %qD in %<aligned%> clause", t);
	      remove = સાચું;
	      તોડો;
	    }
	  નહીંતર જો (bitmap_bit_p (&aligned_head, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE appears more than once in %<aligned%> clauses",
			t);
	      remove = સાચું;
	    }
	  નહીંતર
	    bitmap_set_bit (&aligned_head, DECL_UID (t));
	  તોડો;

	સ્થિતિ OMP_CLAUSE_NONTEMPORAL:
	  t = OMP_CLAUSE_DECL (c);
	  જો (!VAR_P (t) && વૃક્ષ_CODE (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in %<nontemporal%> clause", t);
	      remove = સાચું;
	    }
	  નહીંતર જો (bitmap_bit_p (&oacc_reduction_head, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE appears more than once in %<nontemporal%> "
			"clauses", t);
	      remove = સાચું;
	    }
	  નહીંતર
	    bitmap_set_bit (&oacc_reduction_head, DECL_UID (t));
	  તોડો;

	સ્થિતિ OMP_CLAUSE_ALLOCATE:
	  t = OMP_CLAUSE_DECL (c);
	  જો (!VAR_P (t) && વૃક્ષ_CODE (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in %<allocate%> clause", t);
	      remove = સાચું;
	    }
	  નહીંતર જો (bitmap_bit_p (&aligned_head, DECL_UID (t)))
	    {
	      warning_at (OMP_CLAUSE_LOCATION (c), OPT_Wopenmp,
			  "%qE appears more than once in %<allocate%> clauses",
			  t);
	      remove = સાચું;
	    }
	  નહીંતર
	    {
	      bitmap_set_bit (&aligned_head, DECL_UID (t));
	      જો (!OMP_CLAUSE_ALLOCATE_COMBINED (c))
		allocate_seen = સાચું;
	    }
	  તોડો;

	સ્થિતિ OMP_CLAUSE_DOACROSS:
	  t = OMP_CLAUSE_DECL (c);
	  જો (t == NULL_વૃક્ષ)
	    તોડો;
	  જો (OMP_CLAUSE_DOACROSS_KIND (c) == OMP_CLAUSE_DOACROSS_SINK)
	    {
	      gcc_assert (વૃક્ષ_CODE (t) == વૃક્ષ_LIST);
	      માટે (; t; t = વૃક્ષ_CHAIN (t))
		{
		  વૃક્ષ decl = વૃક્ષ_કિંમત (t);
		  જો (વૃક્ષ_CODE (વૃક્ષ_TYPE (decl)) == POINTER_TYPE)
		    {
		      વૃક્ષ offset = વૃક્ષ_PURPOSE (t);
		      તાર્કિક neg = wi::neg_p (wi::to_wide (offset));
		      offset = fold_unary (ABS_પદાવલિ, વૃક્ષ_TYPE (offset), offset);
		      વૃક્ષ t2 = pointer_int_sum (OMP_CLAUSE_LOCATION (c),
						 neg ? MINUS_પદાવલિ : PLUS_પદાવલિ,
						 decl, offset);
		      t2 = fold_build2_loc (OMP_CLAUSE_LOCATION (c), MINUS_પદાવલિ,
					    sizetype,
					    fold_convert (sizetype, t2),
					    fold_convert (sizetype, decl));
		      જો (t2 == error_mark_ગાંઠ)
			{
			  remove = સાચું;
			  તોડો;
			}
		      વૃક્ષ_PURPOSE (t) = t2;
		    }
		}
	      તોડો;
	    }
	  gcc_unreachable ();

	સ્થિતિ OMP_CLAUSE_USES_ALLOCATORS:
	  t = OMP_CLAUSE_USES_ALLOCATORS_ALLOCATOR (c);
	  જો (t == error_mark_ગાંઠ)
	    {
	      remove = સાચું;
	      તોડો;
	    }
	  જો ((VAR_P (t) || વૃક્ષ_CODE (t) == PARM_DECL)
	      && (bitmap_bit_p (&generic_head, DECL_UID (t))
		  || bitmap_bit_p (&map_head, DECL_UID (t))
		  || bitmap_bit_p (&firstprivate_head, DECL_UID (t))
		  || bitmap_bit_p (&lastprivate_head, DECL_UID (t))))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE appears more than once in data clauses", t);
	      remove = સાચું;
	      તોડો;
	    }
	  નહીંતર
	    bitmap_set_bit (&generic_head, DECL_UID (t));
	  જો (વૃક્ષ_CODE (વૃક્ષ_TYPE (t)) != ENUMERAL_TYPE
	      || strcmp (IDENTIFIER_POINTER (TYPE_IDENTIFIER (વૃક્ષ_TYPE (t))),
			 "omp_allocator_handle_t") != 0)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"allocator %qE must be of %<omp_allocator_handle_t%> "
			"type", t);
	      remove = સાચું;
	      તોડો;
	    }
	  વૃક્ષ init;
	  જો (!DECL_P (t)
	      || (વૃક્ષ_CODE (t) == CONST_DECL
		  && ((init = DECL_INITIAL(t)) == nullptr
		      || વૃક્ષ_CODE (init) != INTEGER_CST
		      || ((wi::to_widest (init) < 0
			   || wi::to_widest (init) > GOMP_OMP_PREDEF_ALLOC_MAX)
			  && (wi::to_widest (init) < GOMP_OMPX_PREDEF_ALLOC_MIN
			      || (wi::to_widest (init)
				  > GOMP_OMPX_PREDEF_ALLOC_MAX))))))
	    {
	      remove = સાચું;
	      error_at (OMP_CLAUSE_LOCATION (c),
			"allocator %qE must be either a variable or a "
			"predefined allocator", t);
	      તોડો;
	    }
	  નહીંતર જો (વૃક્ષ_CODE (t) == CONST_DECL)
	    {
	      /* omp_null_allocator is ignored and for predefined allocators,
		 no special handling is required; thus, mark them removed. */
	      remove = સાચું;

	      જો (OMP_CLAUSE_USES_ALLOCATORS_MEMSPACE (c)
		  || OMP_CLAUSE_USES_ALLOCATORS_TRAITS (c))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "modifiers cannot be used with predefined "
			    "allocator %qE", t);
		  તોડો;
		}
	    }
	  t = OMP_CLAUSE_USES_ALLOCATORS_MEMSPACE (c);
	  જો (t == error_mark_ગાંઠ)
	    {
	      remove = સાચું;
	      તોડો;
	    }
	  જો (t != NULL_વૃક્ષ
	      && ((વૃક્ષ_CODE (t) != CONST_DECL && વૃક્ષ_CODE (t) != INTEGER_CST)
		  || વૃક્ષ_CODE (વૃક્ષ_TYPE (t)) != ENUMERAL_TYPE
		  || strcmp (IDENTIFIER_POINTER (TYPE_IDENTIFIER (વૃક્ષ_TYPE (t))),
			     "omp_memspace_handle_t") != 0))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c), "memspace modifier %qE must be"
			" constant enum of %<omp_memspace_handle_t%> type", t);
	      remove = સાચું;
	      તોડો;
	    }
	  t = OMP_CLAUSE_USES_ALLOCATORS_TRAITS (c);
	  જો (t == error_mark_ગાંઠ)
	    {
	      remove = સાચું;
	      તોડો;
	    }
	  જો (t != NULL_વૃક્ષ
	      && t != error_mark_ગાંઠ
	      && (DECL_EXTERNAL (t)
		  || વૃક્ષ_CODE (t) == PARM_DECL))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c), "traits array %qE must be "
			"defined in same scope as the construct on which the "
			"clause appears", t);
	      remove = સાચું;
	    }
	  જો (t != NULL_વૃક્ષ)
	    {
	      તાર્કિક type_err = ખોટું;

	      જો (વૃક્ષ_CODE (વૃક્ષ_TYPE (t)) != ARRAY_TYPE
		  || DECL_SIZE (t) == NULL_વૃક્ષ
		  || !COMPLETE_TYPE_P (વૃક્ષ_TYPE (t)))
		type_err = સાચું;
	      નહીંતર
		{
		  વૃક્ષ elem_t = વૃક્ષ_TYPE (વૃક્ષ_TYPE (t));
		  જો (વૃક્ષ_CODE (elem_t) != RECORD_TYPE
		      || strcmp (IDENTIFIER_POINTER (TYPE_IDENTIFIER (elem_t)),
				 "omp_alloctrait_t") != 0
		      || !TYPE_READONLY (elem_t))
		    type_err = સાચું;
		}
	      જો (type_err)
		{
		  જો (t != error_mark_ગાંઠ)
		    error_at (OMP_CLAUSE_LOCATION (c), "traits array %qE must "
			      "be of %<const omp_alloctrait_t []%> type", t);
		  નહીંતર
		    error_at (OMP_CLAUSE_LOCATION (c), "traits array must "
			      "be of %<const omp_alloctrait_t []%> type");
		  remove = સાચું;
		}
	      નહીંતર
		{
		  વૃક્ષ cst_val = decl_constant_કિંમત_1 (t, સાચું);
		  જો (cst_val == t)
		    {
		      error_at (OMP_CLAUSE_LOCATION (c), "traits array must be "
				"initialized with constants");

		      remove = સાચું;
		    }
		}
	    }
	  જો (remove)
	    તોડો;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  ચાલુ;
	સ્થિતિ OMP_CLAUSE_DEPEND:
	  depend_clause = c;
	  /* FALLTHRU */
	સ્થિતિ OMP_CLAUSE_AFFINITY:
	  t = OMP_CLAUSE_DECL (c);
	  જો (OMP_ITERATOR_DECL_P (t))
	    {
	      જો (વૃક્ષ_PURPOSE (t) != last_iterators)
		last_iterators_remove
		  = c_omp_finish_iterators (વૃક્ષ_PURPOSE (t));
	      last_iterators = વૃક્ષ_PURPOSE (t);
	      t = વૃક્ષ_કિંમત (t);
	      જો (last_iterators_remove)
		t = error_mark_ગાંઠ;
	    }
	  નહીંતર
	    last_iterators = NULL_વૃક્ષ;
	  જો (વૃક્ષ_CODE (t) == OMP_ARRAY_SECTION)
	    {
	      જો (handle_omp_array_sections (c, ort))
		remove = સાચું;
	      નહીંતર જો (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND
		       && OMP_CLAUSE_DEPEND_KIND (c) == OMP_CLAUSE_DEPEND_DEPOBJ)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%<depend%> clause with %<depobj%> dependence "
			    "type on array section");
		  remove = સાચું;
		}
	      તોડો;
	    }
	  જો (t == error_mark_ગાંઠ)
	    remove = સાચું;
	  નહીંતર જો (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND
		   && t == ridpointers[RID_OMP_ALL_MEMORY])
	    {
	      જો (OMP_CLAUSE_DEPEND_KIND (c) != OMP_CLAUSE_DEPEND_OUT
		  && OMP_CLAUSE_DEPEND_KIND (c) != OMP_CLAUSE_DEPEND_INOUT)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%<omp_all_memory%> used with %<depend%> kind "
			    "other than %<out%> or %<inout%>");
		  remove = સાચું;
		}
	    }
	  નહીંતર જો (!lvalue_p (t))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not lvalue expression nor array section in "
			"%qs clause", t,
			omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	      remove = સાચું;
	    }
	  નહીંતર જો (વૃક્ષ_CODE (t) == COMPONENT_REF
		   && DECL_C_BIT_FIELD (વૃક્ષ_OPERAND (t, 1)))
	    {
	      gcc_assert (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND
			  || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_AFFINITY);
	      error_at (OMP_CLAUSE_LOCATION (c),
			"bit-field %qE in %qs clause", t,
			omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	      remove = સાચું;
	    }
	  નહીંતર જો (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND
		   && OMP_CLAUSE_DEPEND_KIND (c) == OMP_CLAUSE_DEPEND_DEPOBJ)
	    {
	      જો (!c_omp_depend_t_p (વૃક્ષ_TYPE (t)))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qE does not have %<omp_depend_t%> type in "
			    "%<depend%> clause with %<depobj%> dependence "
			    "type", t);
		  remove = સાચું;
		}
	    }
	  નહીંતર જો (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND
		   && c_omp_depend_t_p (વૃક્ષ_TYPE (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE should not have %<omp_depend_t%> type in "
			"%<depend%> clause with dependence type other than "
			"%<depobj%>", t);
	      remove = સાચું;
	    }
	  જો (!remove)
	    {
	      જો (t == ridpointers[RID_OMP_ALL_MEMORY])
		t = null_pointer_ગાંઠ;
	      નહીંતર
		{
		  વૃક્ષ addr = build_unary_op (OMP_CLAUSE_LOCATION (c),
					      ADDR_પદાવલિ, t, ખોટું);
		  જો (addr == error_mark_ગાંઠ)
		    {
		      remove = સાચું;
		      તોડો;
		    }
		  t = build_indirect_ref (OMP_CLAUSE_LOCATION (c), addr,
					  RO_UNARY_STAR);
		  જો (t == error_mark_ગાંઠ)
		    {
		      remove = સાચું;
		      તોડો;
		    }
		}
	      જો (OMP_ITERATOR_DECL_P (OMP_CLAUSE_DECL (c)))
		વૃક્ષ_કિંમત (OMP_CLAUSE_DECL (c)) = t;
	      નહીંતર
		OMP_CLAUSE_DECL (c) = t;
	    }
	  તોડો;

	સ્થિતિ OMP_CLAUSE_MAP:
	  જો (OMP_CLAUSE_MAP_IMPLICIT (c) && !implicit_moved)
	    જાઓ move_implicit;
	  જો (OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_ધકેલો_MAPPER_NAME
	      || OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_કાઢો_MAPPER_NAME)
	    {
	      remove = સાચું;
	      તોડો;
	    }
	  /* FALLTHRU */
	સ્થિતિ OMP_CLAUSE_TO:
	સ્થિતિ OMP_CLAUSE_FROM:
	  જો (OMP_CLAUSE_ITERATORS (c)
	      && c_omp_finish_iterators (OMP_CLAUSE_ITERATORS (c)))
	    {
	      t = error_mark_ગાંઠ;
	      તોડો;
	    }
	  /* FALLTHRU */
	સ્થિતિ OMP_CLAUSE__CACHE_:
	  {
	    using નામાકાશ omp_addr_tokenizer;
	    auto_vec<omp_addr_token *, 10> addr_tokens;

	    t = OMP_CLAUSE_DECL (c);
	    જો (વૃક્ષ_CODE (t) == OMP_ARRAY_SECTION)
	      {
		grp_start_p = pc;
		grp_sentinel = OMP_CLAUSE_CHAIN (c);

		જો (handle_omp_array_sections (c, ort))
		  remove = સાચું;
		નહીંતર
		  {
		    t = OMP_CLAUSE_DECL (c);
		    જો (!omp_mappable_type (વૃક્ષ_TYPE (t)))
		      {
			error_at (OMP_CLAUSE_LOCATION (c),
				  "array section does not have mappable type "
				  "in %qs clause",
				  omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
			remove = સાચું;
		      }
		    નહીંતર જો (TYPE_ATOMIC (વૃક્ષ_TYPE (t)))
		      {
			error_at (OMP_CLAUSE_LOCATION (c),
				  "%<_Atomic%> %qE in %qs clause", t,
				  omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
			remove = સાચું;
		      }
		    જ્યારે (વૃક્ષ_CODE (t) == ARRAY_REF)
		      t = વૃક્ષ_OPERAND (t, 0);

		    c_omp_address_inspector ai (OMP_CLAUSE_LOCATION (c), t);

		    જો (!omp_parse_પદાવલિ (addr_tokens, t))
		      {
			sorry_at (OMP_CLAUSE_LOCATION (c),
				  "unsupported map expression %qE",
				  OMP_CLAUSE_DECL (c));
			remove = સાચું;
			તોડો;
		      }

		    /* This check is to determine if this will be the only map
		       node created for this clause.  Otherwise, we'll check
		       the following FIRSTPRIVATE_POINTER or ATTACH_DETACH
		       node on the next iteration(s) of the loop.   */
		    જો (addr_tokens.length () >= 4
			&& addr_tokens[0]->type == STRUCTURE_BASE
			&& addr_tokens[0]->u.structure_base_kind == BASE_DECL
			&& addr_tokens[1]->type == ACCESS_METHOD
			&& addr_tokens[2]->type == COMPONENT_SELECTOR
			&& addr_tokens[3]->type == ACCESS_METHOD
			&& (addr_tokens[3]->u.access_kind == ACCESS_DIRECT
			    || (addr_tokens[3]->u.access_kind
				== ACCESS_INDEXED_ARRAY)))
		      {
			વૃક્ષ rt = addr_tokens[1]->પદાવલિ;

			gcc_assert (DECL_P (rt));

			જો (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP
			    && OMP_CLAUSE_MAP_IMPLICIT (c)
			    && (bitmap_bit_p (&map_head, DECL_UID (rt))
				|| bitmap_bit_p (&map_field_head, DECL_UID (rt))
				|| bitmap_bit_p (&map_firstprivate_head,
						 DECL_UID (rt))))
			  {
			    remove = સાચું;
			    તોડો;
			  }
			જો (bitmap_bit_p (&map_field_head, DECL_UID (rt)))
			  તોડો;
			જો (bitmap_bit_p (&map_head, DECL_UID (rt)))
			  {
			    જો (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_MAP)
			      error_at (OMP_CLAUSE_LOCATION (c),
					"%qD appears more than once in motion "
					"clauses", rt);
			    નહીંતર જો (openacc)
			      error_at (OMP_CLAUSE_LOCATION (c),
					"%qD appears more than once in data "
					"clauses", rt);
			    નહીંતર
			      error_at (OMP_CLAUSE_LOCATION (c),
					"%qD appears more than once in map "
					"clauses", rt);
			    remove = સાચું;
			  }
			નહીંતર
			  {
			    bitmap_set_bit (&map_head, DECL_UID (rt));
			    bitmap_set_bit (&map_field_head, DECL_UID (rt));
			  }
		      }
		  }
		જો (c_oacc_check_attachments (c))
		  remove = સાચું;
		જો (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP
		    && (OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_ATTACH
			|| OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_DETACH)
		    && !OMP_CLAUSE_SIZE (c))
		  /* In this case, we have a single array element which is a
		     pointer, and we already set OMP_CLAUSE_SIZE in
		     handle_omp_array_sections above.  For attach/detach
		     clauses, reset the OMP_CLAUSE_SIZE (representing a bias)
		     to zero here.  */
		  OMP_CLAUSE_SIZE (c) = size_zero_ગાંઠ;
		તોડો;
	      }
	    નહીંતર જો (!omp_parse_પદાવલિ (addr_tokens, t))
	      {
		sorry_at (OMP_CLAUSE_LOCATION (c),
			  "unsupported map expression %qE",
			  OMP_CLAUSE_DECL (c));
		remove = સાચું;
		તોડો;
	      }
	    જો (t == error_mark_ગાંઠ)
	      {
		remove = સાચું;
		તોડો;
	      }

	    વૃક્ષ attr;
	    જો (DECL_P (t)
		&& OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP
		&& (attr = lookup_attribute ("omp declare target",
					     DECL_ATTRIBUTES (t)))
		&& કિંમત_member (get_identifier ("local"),
				 વૃક્ષ_કિંમત (attr)))
	      {
		error_at (OMP_CLAUSE_LOCATION (c),
			  "device-local variable %qD cannot appear "
			  "in map clause", t);
		remove = સાચું;
		તોડો;
	      }

	    /* OpenACC attach / detach clauses must be pointers.  */
	    જો (c_oacc_check_attachments (c))
	      {
		remove = સાચું;
		તોડો;
	      }
	    જો (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP
		&& (OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_ATTACH
		    || OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_DETACH)
		&& !OMP_CLAUSE_SIZE (c))
	      /* For attach/detach clauses, set OMP_CLAUSE_SIZE (representing a
		 bias) to zero here, so it is not set erroneously to the pointer
		 size later on in gimplify.cc.  */
	      OMP_CLAUSE_SIZE (c) = size_zero_ગાંઠ;

	    c_omp_address_inspector ai (OMP_CLAUSE_LOCATION (c), t);

	    જો (!ai.check_clause (c))
	      {
		remove = સાચું;
		તોડો;
	      }

	    જો (!ai.map_supported_p ())
	      {
		sorry_at (OMP_CLAUSE_LOCATION (c),
			  "unsupported map expression %qE",
			  OMP_CLAUSE_DECL (c));
		remove = સાચું;
		તોડો;
	      }

	    gcc_assert ((addr_tokens[0]->type == ARRAY_BASE
			 || addr_tokens[0]->type == STRUCTURE_BASE)
			&& addr_tokens[1]->type == ACCESS_METHOD);

	    t = addr_tokens[1]->પદાવલિ;

	    જો (addr_tokens[0]->u.structure_base_kind != BASE_DECL)
	      જાઓ skip_decl_checks;

	    /* For OpenMP, we can access a struct "t" and "t.d" on the same
	       mapping.  OpenACC allows multiple fields of the same structure
	       to be written.  */
	    જો (addr_tokens[0]->type == STRUCTURE_BASE
		&& (bitmap_bit_p (&map_field_head, DECL_UID (t))
		    || (!openacc && bitmap_bit_p (&map_head, DECL_UID (t)))))
	      જાઓ skip_decl_checks;

	    જો (!VAR_P (t) && વૃક્ષ_CODE (t) != PARM_DECL)
	      {
		જો (ort != C_ORT_ACC && પદાવલિ_P (t))
		  તોડો;

		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qE is not a variable in %qs clause", t,
			  omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		remove = સાચું;
	      }
	    નહીંતર જો (VAR_P (t) && DECL_THREAD_LOCAL_P (t))
	      {
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD is threadprivate variable in %qs clause", t,
			  omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		remove = સાચું;
	      }
	    નહીંતર જો ((OMP_CLAUSE_CODE (c) != OMP_CLAUSE_MAP
		      || (OMP_CLAUSE_MAP_KIND (c)
			  != GOMP_MAP_FIRSTPRIVATE_POINTER))
		     && !c_mark_addressable (t))
	      remove = સાચું;
	    નહીંતર જો (!(OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP
		       && (OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_POINTER
			   || (OMP_CLAUSE_MAP_KIND (c)
			       == GOMP_MAP_FIRSTPRIVATE_POINTER)
			   || (OMP_CLAUSE_MAP_KIND (c)
			       == GOMP_MAP_FORCE_DEVICEPTR)))
		     && t == OMP_CLAUSE_DECL (c)
		     && !omp_mappable_type (વૃક્ષ_TYPE (t)))
	      {
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD does not have a mappable type in %qs clause", t,
			  omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		remove = સાચું;
	      }
	    નહીંતર જો (વૃક્ષ_TYPE (t) == error_mark_ગાંઠ)
	      remove = સાચું;
	    નહીંતર જો (TYPE_ATOMIC (strip_array_types (વૃક્ષ_TYPE (t))))
	      {
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%<_Atomic%> %qE in %qs clause", t,
			  omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		remove = સાચું;
	      }
	    નહીંતર જો (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP
		     && OMP_CLAUSE_MAP_IMPLICIT (c)
		     && (bitmap_bit_p (&map_head, DECL_UID (t))
			 || bitmap_bit_p (&map_field_head, DECL_UID (t))
			 || bitmap_bit_p (&map_firstprivate_head,
					  DECL_UID (t))))
	      remove = સાચું;
	    નહીંતર જો (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP
		     && (OMP_CLAUSE_MAP_KIND (c)
			 == GOMP_MAP_FIRSTPRIVATE_POINTER))
	      {
		જો (bitmap_bit_p (&generic_head, DECL_UID (t))
		    || bitmap_bit_p (&firstprivate_head, DECL_UID (t))
		    || bitmap_bit_p (&map_firstprivate_head, DECL_UID (t)))
		  {
		    error_at (OMP_CLAUSE_LOCATION (c),
			      "%qD appears more than once in data clauses", t);
		    remove = સાચું;
		  }
		નહીંતર જો (bitmap_bit_p (&map_head, DECL_UID (t))
			 && !bitmap_bit_p (&map_field_head, DECL_UID (t))
			 && openacc)
		  {
		    error_at (OMP_CLAUSE_LOCATION (c),
			      "%qD appears more than once in data clauses", t);
		    remove = સાચું;
		  }
		નહીંતર
		  bitmap_set_bit (&map_firstprivate_head, DECL_UID (t));
	      }
	    નહીંતર જો (bitmap_bit_p (&map_head, DECL_UID (t))
		     && !bitmap_bit_p (&map_field_head, DECL_UID (t))
		     && ort != C_ORT_OMP
		     && ort != C_ORT_OMP_TARGET
		     && ort != C_ORT_OMP_EXIT_DATA)
	      {
		જો (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_MAP)
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD appears more than once in motion clauses", t);
		નહીંતર જો (openacc)
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD appears more than once in data clauses", t);
		નહીંતર
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD appears more than once in map clauses", t);
		remove = સાચું;
	      }
	    નહીંતર જો (openacc && bitmap_bit_p (&generic_head, DECL_UID (t)))
	      {
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD appears more than once in data clauses", t);
		remove = સાચું;
	      }
	    નહીંતર જો (bitmap_bit_p (&firstprivate_head, DECL_UID (t))
		     || bitmap_bit_p (&is_on_device_head, DECL_UID (t)))
	      {
		જો (openacc)
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD appears more than once in data clauses", t);
		નહીંતર
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD appears both in data and map clauses", t);
		remove = સાચું;
	      }
	    નહીંતર જો (!omp_access_chain_p (addr_tokens, 1))
	      {
		bitmap_set_bit (&map_head, DECL_UID (t));
		જો (t != OMP_CLAUSE_DECL (c)
		    && વૃક્ષ_CODE (OMP_CLAUSE_DECL (c)) == COMPONENT_REF)
		  bitmap_set_bit (&map_field_head, DECL_UID (t));
	      }

	  skip_decl_checks:
	    /* If we call omp_expand_map_clause in handle_omp_array_sections,
	       the containing loop (here) iterates through the new nodes
	       created by that expansion.  Avoid expanding those again (just
	       by checking the node type).  */
	    જો (!remove
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
		વૃક્ષ nc = ai.expand_map_clause (c, OMP_CLAUSE_DECL (c),
						addr_tokens, ort);
		જો (nc != error_mark_ગાંઠ)
		  c = nc;
	      }
	  }
	  તોડો;

	સ્થિતિ OMP_CLAUSE_ENTER:
	સ્થિતિ OMP_CLAUSE_LINK:
	સ્થિતિ OMP_CLAUSE_LOCAL:
	  t = OMP_CLAUSE_DECL (c);
	  અચલ અક્ષર *cname;
	  cname = omp_clause_code_name[OMP_CLAUSE_CODE (c)];
	  જો (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_ENTER
	      && OMP_CLAUSE_ENTER_TO (c))
	    cname = "to";
	  જો (વૃક્ષ_CODE (t) == FUNCTION_DECL
	      && OMP_CLAUSE_CODE (c) == OMP_CLAUSE_ENTER)
	    ;
	  નહીંતર જો (!VAR_P (t))
	    {
	      જો (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_ENTER)
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qE is neither a variable nor a function name in "
			  "clause %qs", t, cname);
	      નહીંતર
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qE is not a variable in clause %qs", t, cname);
	      remove = સાચું;
	    }
	  નહીંતર જો (DECL_THREAD_LOCAL_P (t))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qD is threadprivate variable in %qs clause", t,
			cname);
	      remove = સાચું;
	    }
	  નહીંતર જો (!omp_mappable_type (વૃક્ષ_TYPE (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qD does not have a mappable type in %qs clause", t,
			cname);
	      remove = સાચું;
	    }
	  જો (remove)
	    તોડો;
	  જો (bitmap_bit_p (&generic_head, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE appears more than once on the same "
			"%<declare target%> directive", t);
	      remove = સાચું;
	    }
	  નહીંતર
	    bitmap_set_bit (&generic_head, DECL_UID (t));
	  તોડો;

	સ્થિતિ OMP_CLAUSE_UNIFORM:
	  t = OMP_CLAUSE_DECL (c);
	  જો (વૃક્ષ_CODE (t) != PARM_DECL)
	    {
	      જો (DECL_P (t))
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD is not an argument in %<uniform%> clause", t);
	      નહીંતર
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qE is not an argument in %<uniform%> clause", t);
	      remove = સાચું;
	      તોડો;
	    }
	  /* map_head bitmap is used as uniform_head if declare_simd.  */
	  bitmap_set_bit (&map_head, DECL_UID (t));
	  જાઓ check_dup_generic;

	સ્થિતિ OMP_CLAUSE_IS_DEVICE_PTR:
	સ્થિતિ OMP_CLAUSE_USE_DEVICE_PTR:
	  t = OMP_CLAUSE_DECL (c);
	  જો (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IS_DEVICE_PTR)
	    bitmap_set_bit (&is_on_device_head, DECL_UID (t));
	  જો (વૃક્ષ_CODE (વૃક્ષ_TYPE (t)) != POINTER_TYPE)
	    {
	      જો (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_USE_DEVICE_PTR
		  && !openacc)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qs variable is not a pointer",
			    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		  remove = સાચું;
		}
	      નહીંતર જો (વૃક્ષ_CODE (વૃક્ષ_TYPE (t)) != ARRAY_TYPE)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qs variable is neither a pointer nor an array",
			    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		  remove = સાચું;
		}
	    }
	  જાઓ check_dup_generic;

	સ્થિતિ OMP_CLAUSE_HAS_DEVICE_ADDR:
	  t = OMP_CLAUSE_DECL (c);
	  જો (વૃક્ષ_CODE (t) == OMP_ARRAY_SECTION)
	    {
	      જો (handle_omp_array_sections (c, ort))
		remove = સાચું;
	      નહીંતર
		{
		  t = OMP_CLAUSE_DECL (c);
		  જ્યારે (વૃક્ષ_CODE (t) == ARRAY_REF)
		    t = વૃક્ષ_OPERAND (t, 0);
		}
	    }
	  bitmap_set_bit (&is_on_device_head, DECL_UID (t));
	  જો (VAR_P (t) || વૃક્ષ_CODE (t) == PARM_DECL)
	    c_mark_addressable (t);
	  જાઓ check_dup_generic_t;

	સ્થિતિ OMP_CLAUSE_USE_DEVICE_ADDR:
	  t = OMP_CLAUSE_DECL (c);
	  જો (VAR_P (t) || વૃક્ષ_CODE (t) == PARM_DECL)
	    c_mark_addressable (t);
	  જાઓ check_dup_generic;

	સ્થિતિ OMP_CLAUSE_NOWAIT:
	  જો (copyprivate_seen)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<nowait%> clause must not be used together "
			"with %<copyprivate%> clause");
	      remove = સાચું;
	      તોડો;
	    }
	  nowait_clause = pc;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  ચાલુ;

	સ્થિતિ OMP_CLAUSE_ORDER:
	  જો (ordered_clause)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<order%> clause must not be used together "
			"with %<ordered%> clause");
	      remove = સાચું;
	      તોડો;
	    }
	  નહીંતર જો (order_clause)
	    {
	      /* Silently remove duplicates.  */
	      remove = સાચું;
	      તોડો;
	    }
	  order_clause = pc;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  ચાલુ;

	સ્થિતિ OMP_CLAUSE_DETACH:
	  t = OMP_CLAUSE_DECL (c);
	  જો (detach_seen)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"too many %qs clauses on a task construct",
			"detach");
	      remove = સાચું;
	      તોડો;
	    }
	  detach_seen = pc;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  c_mark_addressable (t);
	  ચાલુ;

	સ્થિતિ OMP_CLAUSE_IF:
	સ્થિતિ OMP_CLAUSE_SELF:
	સ્થિતિ OMP_CLAUSE_અંક_THREADS:
	સ્થિતિ OMP_CLAUSE_અંક_TEAMS:
	સ્થિતિ OMP_CLAUSE_THREAD_LIMIT:
	સ્થિતિ OMP_CLAUSE_DEFAULT:
	સ્થિતિ OMP_CLAUSE_UNTIED:
	સ્થિતિ OMP_CLAUSE_COLLAPSE:
	સ્થિતિ OMP_CLAUSE_FINAL:
	સ્થિતિ OMP_CLAUSE_DEVICE:
	સ્થિતિ OMP_CLAUSE_DIST_SCHEDULE:
	સ્થિતિ OMP_CLAUSE_DYN_GROUPPRIVATE:
	સ્થિતિ OMP_CLAUSE_PARALLEL:
	સ્થિતિ OMP_CLAUSE_FOR:
	સ્થિતિ OMP_CLAUSE_SECTIONS:
	સ્થિતિ OMP_CLAUSE_TASKGROUP:
	સ્થિતિ OMP_CLAUSE_PROC_BIND:
	સ્થિતિ OMP_CLAUSE_DEVICE_TYPE:
	સ્થિતિ OMP_CLAUSE_PRIORITY:
	સ્થિતિ OMP_CLAUSE_THREADS:
	સ્થિતિ OMP_CLAUSE_SIMD:
	સ્થિતિ OMP_CLAUSE_HINT:
	સ્થિતિ OMP_CLAUSE_FILTER:
	સ્થિતિ OMP_CLAUSE_DEFAULTMAP:
	સ્થિતિ OMP_CLAUSE_BIND:
	સ્થિતિ OMP_CLAUSE_અંક_GANGS:
	સ્થિતિ OMP_CLAUSE_અંક_WORKERS:
	સ્થિતિ OMP_CLAUSE_VECTOR_LENGTH:
	સ્થિતિ OMP_CLAUSE_ASYNC:
	સ્થિતિ OMP_CLAUSE_WAIT:
	સ્થિતિ OMP_CLAUSE_AUTO:
	સ્થિતિ OMP_CLAUSE_INDEPENDENT:
	સ્થિતિ OMP_CLAUSE_SEQ:
	સ્થિતિ OMP_CLAUSE_GANG:
	સ્થિતિ OMP_CLAUSE_WORKER:
	સ્થિતિ OMP_CLAUSE_VECTOR:
	સ્થિતિ OMP_CLAUSE_TILE:
	સ્થિતિ OMP_CLAUSE_IF_PRESENT:
	સ્થિતિ OMP_CLAUSE_FINALIZE:
	સ્થિતિ OMP_CLAUSE_NOHOST:
	સ્થિતિ OMP_CLAUSE_INDIRECT:
	સ્થિતિ OMP_CLAUSE_NOVARIANTS:
	સ્થિતિ OMP_CLAUSE_NOCONTEXT:
	  pc = &OMP_CLAUSE_CHAIN (c);
	  ચાલુ;

	સ્થિતિ OMP_CLAUSE_GRAINSIZE:
	  grainsize_seen = pc;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  ચાલુ;

	સ્થિતિ OMP_CLAUSE_અંક_TASKS:
	  અંક_tasks_seen = સાચું;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  ચાલુ;

	સ્થિતિ OMP_CLAUSE_MERGEABLE:
	  mergeable_seen = સાચું;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  ચાલુ;

	સ્થિતિ OMP_CLAUSE_NOGROUP:
	  nogroup_seen = pc;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  ચાલુ;

	સ્થિતિ OMP_CLAUSE_SCHEDULE:
	  schedule_clause = c;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  ચાલુ;

	સ્થિતિ OMP_CLAUSE_ORDERED:
	  ordered_clause = c;
	  જો (order_clause)
	    {
	      error_at (OMP_CLAUSE_LOCATION (*order_clause),
			"%<order%> clause must not be used together "
			"with %<ordered%> clause");
	      *order_clause = OMP_CLAUSE_CHAIN (*order_clause);
	      order_clause = ખાલી;
	    }
	  pc = &OMP_CLAUSE_CHAIN (c);
	  ચાલુ;

	સ્થિતિ OMP_CLAUSE_SAFELEN:
	  safelen = c;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  ચાલુ;
	સ્થિતિ OMP_CLAUSE_SIMDLEN:
	  simdlen = c;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  ચાલુ;

	સ્થિતિ OMP_CLAUSE_FULL:
	  full_seen = pc;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  ચાલુ;

	સ્થિતિ OMP_CLAUSE_PARTIAL:
	  partial_seen = સાચું;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  ચાલુ;

	સ્થિતિ OMP_CLAUSE_SIZES:
	  pc = &OMP_CLAUSE_CHAIN (c);
	  ચાલુ;

	સ્થિતિ OMP_CLAUSE_INBRANCH:
	સ્થિતિ OMP_CLAUSE_NOTINBRANCH:
	  જો (branch_seen)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<inbranch%> clause is incompatible with "
			"%<notinbranch%>");
	      remove = સાચું;
	      તોડો;
	    }
	  branch_seen = સાચું;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  ચાલુ;

	સ્થિતિ OMP_CLAUSE_INCLUSIVE:
	સ્થિતિ OMP_CLAUSE_EXCLUSIVE:
	  need_complete = સાચું;
	  need_implicitly_determined = સાચું;
	  t = OMP_CLAUSE_DECL (c);
	  જો (!VAR_P (t) && વૃક્ષ_CODE (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in clause %qs", t,
			omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	      remove = સાચું;
	    }
	  તોડો;

	સ્થિતિ OMP_CLAUSE_INIT:
	  init_seen = સાચું;
	  જો (!OMP_CLAUSE_INIT_TARGETSYNC (c))
	    init_no_targetsync_clause = c;
	  /* FALLTHRU */
	સ્થિતિ OMP_CLAUSE_DESTROY:
	સ્થિતિ OMP_CLAUSE_USE:
	  init_use_destroy_seen = સાચું;
	  t = OMP_CLAUSE_DECL (c);
	  જો (bitmap_bit_p (&generic_head, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qD appears more than once in action clauses", t);
	      remove = સાચું;
	      તોડો;
	    }
	  bitmap_set_bit (&generic_head, DECL_UID (t));
	  /* FALLTHRU */
	સ્થિતિ OMP_CLAUSE_INTEROP:
	  જો (/* ort == C_ORT_OMP_INTEROP [uncomment for depobj init]  */
		   !c_omp_interop_t_p (વૃક્ષ_TYPE (OMP_CLAUSE_DECL (c))))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qD must be of %<omp_interop_t%>",
			OMP_CLAUSE_DECL (c));
	      remove = સાચું;
	    }
	  નહીંતર જો ((OMP_CLAUSE_CODE (c) == OMP_CLAUSE_INIT
		    || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DESTROY)
		   && વૃક્ષ_READONLY (OMP_CLAUSE_DECL (c)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
		      "%qD shall not be const", OMP_CLAUSE_DECL (c));
	      remove = સાચું;
	    }
	  pc = &OMP_CLAUSE_CHAIN (c);
	  તોડો;
	મૂળભૂત:
	  gcc_unreachable ();
	}

      જો (!remove)
	{
	  t = OMP_CLAUSE_DECL (c);

	  જો (need_complete)
	    {
	      t = require_complete_type (OMP_CLAUSE_LOCATION (c), t);
	      જો (t == error_mark_ગાંઠ)
		remove = સાચું;
	    }

	  જો (need_implicitly_determined)
	    {
	      અચલ અક્ષર *share_name = ખાલી;

	      જો (VAR_P (t) && DECL_THREAD_LOCAL_P (t))
		share_name = "threadprivate";
	      નહીંતર પસંદગી (c_omp_predetermined_sharing (t))
		{
		સ્થિતિ OMP_CLAUSE_DEFAULT_UNSPECIFIED:
		  તોડો;
		સ્થિતિ OMP_CLAUSE_DEFAULT_SHARED:
		  જો ((OMP_CLAUSE_CODE (c) == OMP_CLAUSE_SHARED
		       || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_FIRSTPRIVATE)
		      && c_omp_predefined_variable (t))
		    /* The __func__ variable and similar function-local
		       predefined variables may be listed in a shared or
		       firstprivate clause.  */
		    તોડો;
		  share_name = "shared";
		  તોડો;
		સ્થિતિ OMP_CLAUSE_DEFAULT_PRIVATE:
		  share_name = "private";
		  તોડો;
		મૂળભૂત:
		  gcc_unreachable ();
		}
	      જો (share_name)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qE is predetermined %qs for %qs",
			    t, share_name,
			    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		  remove = સાચું;
		}
	      નહીંતર જો (વૃક્ષ_READONLY (t)
		       && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_SHARED
		       && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_FIRSTPRIVATE)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%<const%> qualified %qE may appear only in "
			    "%<shared%> or %<firstprivate%> clauses", t);
		  remove = સાચું;
		}
	    }
	}

      જો (remove)
	{
	  જો (grp_start_p)
	    {
	      /* If we found a clause to remove, we want to remove the whole
		 expanded group, otherwise gimplify
		 (omp_resolve_clause_dependencies) can get confused.  */
	      *grp_start_p = grp_sentinel;
	      pc = grp_start_p;
	      grp_start_p = ખાલી;
	    }
	  નહીંતર
	    *pc = OMP_CLAUSE_CHAIN (c);
	}
      નહીંતર
	pc = &OMP_CLAUSE_CHAIN (c);
    }

  જો (grp_start_p
      && OMP_CLAUSE_HAS_ITERATORS (*grp_start_p))
    માટે (વૃક્ષ gc = *grp_start_p; gc; gc = OMP_CLAUSE_CHAIN (gc))
      OMP_CLAUSE_ITERATORS (gc) = OMP_CLAUSE_ITERATORS (*grp_start_p);

  જો (simdlen
      && safelen
      && વૃક્ષ_int_cst_lt (OMP_CLAUSE_SAFELEN_પદાવલિ (safelen),
			  OMP_CLAUSE_SIMDLEN_પદાવલિ (simdlen)))
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
      OMP_CLAUSE_SIMDLEN_પદાવલિ (simdlen)
	= OMP_CLAUSE_SAFELEN_પદાવલિ (safelen);
    }

  જો (ordered_clause
      && schedule_clause
      && (OMP_CLAUSE_SCHEDULE_KIND (schedule_clause)
	  & OMP_CLAUSE_SCHEDULE_NONMONOTONIC))
    {
      error_at (OMP_CLAUSE_LOCATION (schedule_clause),
		"%<nonmonotonic%> schedule modifier specified together "
		"with %<ordered%> clause");
      OMP_CLAUSE_SCHEDULE_KIND (schedule_clause)
	= (ગણના omp_clause_schedule_kind)
	  (OMP_CLAUSE_SCHEDULE_KIND (schedule_clause)
	   & ~OMP_CLAUSE_SCHEDULE_NONMONOTONIC);
    }

  જો (reduction_seen < 0 && ordered_clause)
    {
      error_at (OMP_CLAUSE_LOCATION (ordered_clause),
		"%qs clause specified together with %<inscan%> "
		"%<reduction%> clause", "ordered");
      reduction_seen = -2;
    }

  જો (reduction_seen < 0 && schedule_clause)
    {
      error_at (OMP_CLAUSE_LOCATION (schedule_clause),
		"%qs clause specified together with %<inscan%> "
		"%<reduction%> clause", "schedule");
      reduction_seen = -2;
    }

  જો (linear_variable_step_check
      || reduction_seen == -2
      || allocate_seen
      || target_in_reduction_seen)
    માટે (pc = &clauses, c = clauses; c ; c = *pc)
      {
	તાર્કિક remove = ખોટું;
	જો (allocate_seen)
	  પસંદગી (OMP_CLAUSE_CODE (c))
	    {
	    સ્થિતિ OMP_CLAUSE_REDUCTION:
	    સ્થિતિ OMP_CLAUSE_IN_REDUCTION:
	    સ્થિતિ OMP_CLAUSE_TASK_REDUCTION:
	      જો (વૃક્ષ_CODE (OMP_CLAUSE_DECL (c)) == MEM_REF)
		{
		  t = વૃક્ષ_OPERAND (OMP_CLAUSE_DECL (c), 0);
		  જો (વૃક્ષ_CODE (t) == POINTER_PLUS_પદાવલિ)
		    t = વૃક્ષ_OPERAND (t, 0);
		  જો (વૃક્ષ_CODE (t) == ADDR_પદાવલિ
		      || INDIRECT_REF_P (t))
		    t = વૃક્ષ_OPERAND (t, 0);
		  જો (DECL_P (t))
		    bitmap_clear_bit (&aligned_head, DECL_UID (t));
		  તોડો;
		}
	      /* FALLTHRU */
	    સ્થિતિ OMP_CLAUSE_PRIVATE:
	    સ્થિતિ OMP_CLAUSE_FIRSTPRIVATE:
	    સ્થિતિ OMP_CLAUSE_LASTPRIVATE:
	    સ્થિતિ OMP_CLAUSE_LINEAR:
	      જો (DECL_P (OMP_CLAUSE_DECL (c)))
		bitmap_clear_bit (&aligned_head,
				  DECL_UID (OMP_CLAUSE_DECL (c)));
	      તોડો;
	    મૂળભૂત:
	      તોડો;
	    }
	જો (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_LINEAR
	    && OMP_CLAUSE_LINEAR_VARIABLE_STRIDE (c)
	    && !bitmap_bit_p (&map_head,
			      DECL_UID (OMP_CLAUSE_LINEAR_STEP (c))))
	  {
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%<linear%> clause step is a parameter %qD not "
		      "specified in %<uniform%> clause",
		      OMP_CLAUSE_LINEAR_STEP (c));
	    remove = સાચું;
	  }
	નહીંતર જો (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_REDUCTION
		 && reduction_seen == -2)
	  OMP_CLAUSE_REDUCTION_INSCAN (c) = 0;
	જો (target_in_reduction_seen
	    && OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP)
	  {
	    વૃક્ષ t = OMP_CLAUSE_DECL (c);
	    જ્યારે (handled_component_p (t)
		   || INDIRECT_REF_P (t)
		   || વૃક્ષ_CODE (t) == ADDR_પદાવલિ
		   || વૃક્ષ_CODE (t) == MEM_REF
		   || વૃક્ષ_CODE (t) == NON_LVALUE_પદાવલિ)
	      t = વૃક્ષ_OPERAND (t, 0);
	    જો (DECL_P (t)
		&& bitmap_bit_p (&oacc_reduction_head, DECL_UID (t)))
	      OMP_CLAUSE_MAP_IN_REDUCTION (c) = 1;
	  }

	જો (remove)
	  *pc = OMP_CLAUSE_CHAIN (c);
	નહીંતર
	  pc = &OMP_CLAUSE_CHAIN (c);
      }

  જો (allocate_seen)
    માટે (pc = &clauses, c = clauses; c ; c = *pc)
      {
	તાર્કિક remove = ખોટું;
	જો (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_ALLOCATE
	    && !OMP_CLAUSE_ALLOCATE_COMBINED (c)
	    && bitmap_bit_p (&aligned_head, DECL_UID (OMP_CLAUSE_DECL (c))))
	  {
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%qD specified in %<allocate%> clause but not in "
		      "an explicit privatization clause", OMP_CLAUSE_DECL (c));
	    remove = સાચું;
	  }
	જો (remove)
	  *pc = OMP_CLAUSE_CHAIN (c);
	નહીંતર
	  pc = &OMP_CLAUSE_CHAIN (c);
      }

  જો (nogroup_seen && reduction_seen)
    {
      error_at (OMP_CLAUSE_LOCATION (*nogroup_seen),
		"%<nogroup%> clause must not be used together with "
		"%<reduction%> clause");
      *nogroup_seen = OMP_CLAUSE_CHAIN (*nogroup_seen);
    }

  જો (grainsize_seen && અંક_tasks_seen)
    {
      error_at (OMP_CLAUSE_LOCATION (*grainsize_seen),
		"%<grainsize%> clause must not be used together with "
		"%<num_tasks%> clause");
      *grainsize_seen = OMP_CLAUSE_CHAIN (*grainsize_seen);
    }

  જો (full_seen && partial_seen)
    {
      error_at (OMP_CLAUSE_LOCATION (*full_seen),
		"%<full%> clause must not be used together with "
		"%<partial%> clause");
      *full_seen = OMP_CLAUSE_CHAIN (*full_seen);
    }

  જો (detach_seen)
    {
      જો (mergeable_seen)
	{
	  error_at (OMP_CLAUSE_LOCATION (*detach_seen),
		    "%<detach%> clause must not be used together with "
		    "%<mergeable%> clause");
	  *detach_seen = OMP_CLAUSE_CHAIN (*detach_seen);
	}
      નહીંતર
	{
	  વૃક્ષ detach_decl = OMP_CLAUSE_DECL (*detach_seen);

	  માટે (pc = &clauses, c = clauses; c ; c = *pc)
	    {
	      તાર્કિક remove = ખોટું;
	      જો ((OMP_CLAUSE_CODE (c) == OMP_CLAUSE_SHARED
		   || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_PRIVATE
		   || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_FIRSTPRIVATE
		   || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_LASTPRIVATE)
		  && OMP_CLAUSE_DECL (c) == detach_decl)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "the event handle of a %<detach%> clause "
			    "should not be in a data-sharing clause");
		  remove = સાચું;
		}
	      જો (remove)
		*pc = OMP_CLAUSE_CHAIN (c);
	      નહીંતર
		pc = &OMP_CLAUSE_CHAIN (c);
	    }
	}
    }

  જો (ort == C_ORT_OMP_INTEROP
      && depend_clause
      && (!init_use_destroy_seen
	  || (init_seen && init_no_targetsync_clause)))
    {
      error_at (OMP_CLAUSE_LOCATION (depend_clause),
		"%<depend%> clause requires action clauses with "
		"%<targetsync%> interop-type");
      જો (init_no_targetsync_clause)
	inform (OMP_CLAUSE_LOCATION (init_no_targetsync_clause),
		"%<init%> clause lacks the %<targetsync%> modifier");
    }

  bitmap_obstack_release (ખાલી);
  પાછા clauses;
}

/* Do processing necessary to make CLAUSES well-formed, where CLAUSES result
   from implicit instantiation of user-defined mappers (in gimplify.cc).  */

વૃક્ષ
c_omp_finish_mapper_clauses (વૃક્ષ clauses)
{
  પાછા c_finish_omp_clauses (clauses, C_ORT_OMP);
}

/* Return code to initialize DST with a copy constructor from SRC.
   C doesn't have copy constructors nor assignment operators, only for
   _Atomic vars we need to perform __atomic_load from src into a temporary
   followed by __atomic_store of the temporary to dst.  */

વૃક્ષ
c_omp_clause_copy_ctor (વૃક્ષ clause, વૃક્ષ dst, વૃક્ષ src)
{
  જો (!really_atomic_lvalue (dst) && !really_atomic_lvalue (src))
    પાછા build2 (MODIFY_પદાવલિ, વૃક્ષ_TYPE (dst), dst, src);

  location_t loc = OMP_CLAUSE_LOCATION (clause);
  વૃક્ષ type = વૃક્ષ_TYPE (dst);
  વૃક્ષ nonatomic_type = build_qualified_type (type, TYPE_UNQUALIFIED);
  વૃક્ષ tmp = create_tmp_var (nonatomic_type);
  વૃક્ષ tmp_addr = build_fold_addr_પદાવલિ (tmp);
  વૃક્ષ_ADDRESSABLE (tmp) = 1;
  suppress_warning (tmp);
  વૃક્ષ src_addr = build_fold_addr_પદાવલિ (src);
  વૃક્ષ dst_addr = build_fold_addr_પદાવલિ (dst);
  વૃક્ષ seq_cst = build_int_cst (integer_type_ગાંઠ, MEMMODEL_SEQ_CST);
  vec<વૃક્ષ, va_gc> *params;
  /* Expansion of a generic atomic load may require an addition
     element, so allocate enough to prevent a resize.  */
  vec_alloc (params, 4);

  /* Build __atomic_load (&src, &tmp, SEQ_CST);  */
  વૃક્ષ fndecl = builtin_decl_explicit (BUILT_IN_ATOMIC_LOAD);
  params->quick_ધકેલો (src_addr);
  params->quick_ધકેલો (tmp_addr);
  params->quick_ધકેલો (seq_cst);
  વૃક્ષ load = c_build_function_call_vec (loc, vNULL, fndecl, params, ખાલી);

  vec_alloc (params, 4);

  /* Build __atomic_store (&dst, &tmp, SEQ_CST);  */
  fndecl = builtin_decl_explicit (BUILT_IN_ATOMIC_STORE);
  params->quick_ધકેલો (dst_addr);
  params->quick_ધકેલો (tmp_addr);
  params->quick_ધકેલો (seq_cst);
  વૃક્ષ store = c_build_function_call_vec (loc, vNULL, fndecl, params, ખાલી);
  પાછા build2 (COMPOUND_પદાવલિ, void_type_ગાંઠ, load, store);
}

/* Create a transaction node.  */

વૃક્ષ
c_finish_transaction (location_t loc, વૃક્ષ block, પૂર્ણાંક flags)
{
  વૃક્ષ stmt = build_stmt (loc, TRANSACTION_પદાવલિ, block);
  જો (flags & TM_STMT_ATTR_OUTER)
    TRANSACTION_પદાવલિ_OUTER (stmt) = 1;
  જો (flags & TM_STMT_ATTR_RELAXED)
    TRANSACTION_પદાવલિ_RELAXED (stmt) = 1;
  પાછા add_stmt (stmt);
}

/* Make a variant type in the proper way for C/C++, propagating qualifiers
   down to the element type of an array.  If ORIG_QUAL_TYPE is not
   NULL, then it should be used as the qualified type
   ORIG_QUAL_INDIRECT levels down in array type derivation (to
   preserve information about the typedef name from which an array
   type was derived).  */

વૃક્ષ
c_build_qualified_type (વૃક્ષ type, પૂર્ણાંક type_quals, વૃક્ષ orig_qual_type,
			size_t orig_qual_indirect)
{
  જો (type == error_mark_ગાંઠ)
    પાછા type;

  જો (વૃક્ષ_CODE (type) == ARRAY_TYPE)
    {
      વૃક્ષ t;
      વૃક્ષ element_type = c_build_qualified_type (વૃક્ષ_TYPE (type),
						  type_quals, orig_qual_type,
						  orig_qual_indirect - 1);

      /* See if we already have an identically qualified type.  */
      જો (orig_qual_type && orig_qual_indirect == 0)
	t = orig_qual_type;
      નહીંતર
	માટે (t = TYPE_MAIN_VARIANT (type); t; t = TYPE_NEXT_VARIANT (t))
	  {
	    જો (TYPE_QUALS (strip_array_types (t)) == type_quals
		&& TYPE_NAME (t) == TYPE_NAME (type)
		&& TYPE_CONTEXT (t) == TYPE_CONTEXT (type)
		&& attribute_list_equal (TYPE_ATTRIBUTES (t),
					 TYPE_ATTRIBUTES (type)))
	      તોડો;
	  }
      જો (!t)
	{
          વૃક્ષ domain = TYPE_DOMAIN (type);

	  t = build_variant_type_copy (type);
	  વૃક્ષ_TYPE (t) = element_type;
	  TYPE_ADDR_SPACE (t) = TYPE_ADDR_SPACE (element_type);

          જો (TYPE_STRUCTURAL_EQUALITY_P (element_type)
              || (domain && TYPE_STRUCTURAL_EQUALITY_P (domain)))
            SET_TYPE_STRUCTURAL_EQUALITY (t);
          નહીંતર જો (TYPE_CANONICAL (element_type) != element_type
                   || (domain && TYPE_CANONICAL (domain) != domain))
            {
              વૃક્ષ unqualified_canon
		= c_build_array_type (TYPE_CANONICAL (element_type),
				      domain ? TYPE_CANONICAL (domain)
					     : NULL_વૃક્ષ);
              જો (TYPE_REVERSE_STORAGE_ORDER (type))
                {
                  unqualified_canon
		    = build_distinct_type_copy (unqualified_canon);
                  TYPE_REVERSE_STORAGE_ORDER (unqualified_canon) = 1;
                }
              TYPE_CANONICAL (t)
		= c_build_qualified_type (unqualified_canon, type_quals);
            }
          નહીંતર
            TYPE_CANONICAL (t) = t;
	}
      પાછા t;
    }

  /* A restrict-qualified pointer type must be a pointer to object or
     incomplete type.  Note that the use of POINTER_TYPE_P also allows
     REFERENCE_TYPEs, which is appropriate for C++.  */
  જો ((type_quals & TYPE_QUAL_RESTRICT)
      && (!POINTER_TYPE_P (type)
	  || !C_TYPE_OBJECT_OR_INCOMPLETE_P (વૃક્ષ_TYPE (type))))
    {
      error ("invalid use of %<restrict%>");
      type_quals &= ~TYPE_QUAL_RESTRICT;
    }

  વૃક્ષ var_type = (orig_qual_type && orig_qual_indirect == 0
		   ? orig_qual_type
		   : build_qualified_type (type, type_quals));

  gcc_checking_assert (C_TYPE_VARIABLE_SIZE (var_type)
		       == C_TYPE_VARIABLE_SIZE (type));
  gcc_checking_assert (c_type_variably_modified_p (var_type)
		       == c_type_variably_modified_p (type));

  /* A variant type does not inherit the list of incomplete vars from the
     type main variant.  */
  જો ((RECORD_OR_UNION_TYPE_P (var_type)
       || વૃક્ષ_CODE (var_type) == ENUMERAL_TYPE)
      && TYPE_MAIN_VARIANT (var_type) != var_type)
    C_TYPE_INCOMPLETE_VARS (var_type) = 0;
  પાછા var_type;
}

/* Build a VA_ARG_EXPR for the C parser.  */

વૃક્ષ
c_build_va_arg (location_t loc1, વૃક્ષ પદાવલિ, location_t loc2, વૃક્ષ type,
		વૃક્ષ type_પદાવલિ)
{
  જો (error_operand_p (type))
    પાછા error_mark_ગાંઠ;
  /* VA_ARG_EXPR cannot be used for a scalar va_list with reverse storage
     order because it takes the address of the expression.  */
  નહીંતર જો (handled_component_p (પદાવલિ)
	   && reverse_storage_order_for_component_p (પદાવલિ))
    {
      error_at (loc1, "cannot use %<va_arg%> with reverse storage order");
      પાછા error_mark_ગાંઠ;
    }
  નહીંતર જો (!COMPLETE_TYPE_P (type))
    {
      error_at (loc2, "second argument to %<va_arg%> is of incomplete "
		"type %qT", type);
      પાછા error_mark_ગાંઠ;
    }
  નહીંતર જો (વૃક્ષ_CODE (type) == FUNCTION_TYPE)
    {
      error_at (loc2, "second argument to %<va_arg%> is a function type %qT",
		type);
      પાછા error_mark_ગાંઠ;
    }
  નહીંતર જો (વૃક્ષ_CODE (type) == ARRAY_TYPE && C_TYPE_VARIABLE_SIZE (type)
	   && !flag_isoc99)
    {
      error_at (loc2, "second argument to %<va_arg%> is an array type %qT",
		type);
      પાછા error_mark_ગાંઠ;
    }
  નહીંતર જો (warn_cxx_compat && વૃક્ષ_CODE (type) == ENUMERAL_TYPE)
    warning_at (loc2, OPT_Wc___compat,
		"C++ requires promoted type, not enum type, in %<va_arg%>");

  જો (flag_isoc99 && વૃક્ષ_CODE (type) == ARRAY_TYPE)
    {
      warning_at (loc2, 0, "second argument to %<va_arg%> is an array type %qT",
		  type);
      /* We create a trap but evaluate side effects first.  */
      વૃક્ષ trapfn = builtin_decl_explicit (BUILT_IN_TRAP);
      trapfn = build_call_પદાવલિ_loc (loc2, trapfn, 0);
      વૃક્ષ e2 = build2 (COMPOUND_પદાવલિ, void_type_ગાંઠ, પદાવલિ, trapfn);
      /* Return a compound literal of the right type.  */
      વૃક્ષ e1 = build_compound_literal (loc2, type, ખાલી, સાચું, 0, ખાલી);
      પદાવલિ = build2 (COMPOUND_પદાવલિ, type, e2, e1);
    }
  નહીંતર
    પદાવલિ = build_va_arg (loc2, પદાવલિ, type);

  જો (type_પદાવલિ)
    પદાવલિ = build2 (COMPOUND_પદાવલિ, વૃક્ષ_TYPE (પદાવલિ), type_પદાવલિ, પદાવલિ);

  પાછા પદાવલિ;
}

/* Return truthvalue of whether T1 is the same tree structure as T2.
   Return 1 if they are the same. Return false if they are different.  */

તાર્કિક
c_વૃક્ષ_equal (વૃક્ષ t1, વૃક્ષ t2)
{
  ગણના વૃક્ષ_code code1, code2;

  જો (t1 == t2)
    પાછા સાચું;
  જો (!t1 || !t2)
    પાછા ખોટું;

  માટે (code1 = વૃક્ષ_CODE (t1); code1 == NON_LVALUE_પદાવલિ;
       code1 = વૃક્ષ_CODE (t1))
    t1 = વૃક્ષ_OPERAND (t1, 0);
  માટે (code2 = વૃક્ષ_CODE (t2); code2 == NON_LVALUE_પદાવલિ;
       code2 = વૃક્ષ_CODE (t2))
    t2 = વૃક્ષ_OPERAND (t2, 0);

  /* They might have become equal now.  */
  જો (t1 == t2)
    પાછા સાચું;

  જો (code1 != code2)
    પાછા ખોટું;

  જો (CONSTANT_CLASS_P (t1) && !comptypes (વૃક્ષ_TYPE (t1), વૃક્ષ_TYPE (t2)))
    પાછા ખોટું;

  પસંદગી (code1)
    {
    સ્થિતિ INTEGER_CST:
      પાછા wi::to_wide (t1) == wi::to_wide (t2);

    સ્થિતિ REAL_CST:
      પાછા real_equal (&વૃક્ષ_REAL_CST (t1), &વૃક્ષ_REAL_CST (t2));

    સ્થિતિ STRING_CST:
      પાછા વૃક્ષ_STRING_LENGTH (t1) == વૃક્ષ_STRING_LENGTH (t2)
	&& !memcmp (વૃક્ષ_STRING_POINTER (t1), વૃક્ષ_STRING_POINTER (t2),
		    વૃક્ષ_STRING_LENGTH (t1));

    સ્થિતિ FIXED_CST:
      પાછા FIXED_કિંમતો_IDENTICAL (વૃક્ષ_FIXED_CST (t1),
				     વૃક્ષ_FIXED_CST (t2));

    સ્થિતિ COMPLEX_CST:
      પાછા c_વૃક્ષ_equal (વૃક્ષ_REALPART (t1), વૃક્ષ_REALPART (t2))
	     && c_વૃક્ષ_equal (વૃક્ષ_IMAGPART (t1), વૃક્ષ_IMAGPART (t2));

    સ્થિતિ VECTOR_CST:
      પાછા operand_equal_p (t1, t2, OEP_ONLY_CONST);

    સ્થિતિ CONSTRUCTOR:
      /* We need to do this when determining whether or not two
	 non-type pointer to member function template arguments
	 are the same.  */
      જો (!comptypes (વૃક્ષ_TYPE (t1), વૃક્ષ_TYPE (t2))
	  || CONSTRUCTOR_NELTS (t1) != CONSTRUCTOR_NELTS (t2))
	પાછા ખોટું;
      {
	વૃક્ષ field, કિંમત;
	unsigned પૂર્ણાંક i;
	FOR_EACH_CONSTRUCTOR_ELT (CONSTRUCTOR_ELTS (t1), i, field, કિંમત)
	  {
	    constructor_elt *elt2 = CONSTRUCTOR_ELT (t2, i);
	    જો (!c_વૃક્ષ_equal (field, elt2->index)
		|| !c_વૃક્ષ_equal (કિંમત, elt2->કિંમત))
	      પાછા ખોટું;
	  }
      }
      પાછા સાચું;

    સ્થિતિ વૃક્ષ_LIST:
      જો (!c_વૃક્ષ_equal (વૃક્ષ_PURPOSE (t1), વૃક્ષ_PURPOSE (t2)))
	પાછા ખોટું;
      જો (!c_વૃક્ષ_equal (વૃક્ષ_કિંમત (t1), વૃક્ષ_કિંમત (t2)))
	પાછા ખોટું;
      પાછા c_વૃક્ષ_equal (વૃક્ષ_CHAIN (t1), વૃક્ષ_CHAIN (t2));

    સ્થિતિ SAVE_પદાવલિ:
      પાછા c_વૃક્ષ_equal (વૃક્ષ_OPERAND (t1, 0), વૃક્ષ_OPERAND (t2, 0));

    સ્થિતિ CALL_પદાવલિ:
      {
	વૃક્ષ arg1, arg2;
	call_પદાવલિ_arg_iterator iter1, iter2;
	જો (!c_વૃક્ષ_equal (CALL_પદાવલિ_FN (t1), CALL_પદાવલિ_FN (t2)))
	  પાછા ખોટું;
	માટે (arg1 = first_call_પદાવલિ_arg (t1, &iter1),
	       arg2 = first_call_પદાવલિ_arg (t2, &iter2);
	     arg1 && arg2;
	     arg1 = next_call_પદાવલિ_arg (&iter1),
	       arg2 = next_call_પદાવલિ_arg (&iter2))
	  જો (!c_વૃક્ષ_equal (arg1, arg2))
	    પાછા ખોટું;
	જો (arg1 || arg2)
	  પાછા ખોટું;
	પાછા સાચું;
      }

    સ્થિતિ TARGET_પદાવલિ:
      {
	વૃક્ષ o1 = વૃક્ષ_OPERAND (t1, 0);
	વૃક્ષ o2 = વૃક્ષ_OPERAND (t2, 0);

	/* Special case: if either target is an unallocated VAR_DECL,
	   it means that it's going to be unified with whatever the
	   TARGET_EXPR is really supposed to initialize, so treat it
	   as being equivalent to anything.  */
	જો (VAR_P (o1) && DECL_NAME (o1) == NULL_વૃક્ષ
	    && !DECL_RTL_SET_P (o1))
	  /*Nop*/;
	નહીંતર જો (VAR_P (o2) && DECL_NAME (o2) == NULL_વૃક્ષ
		 && !DECL_RTL_SET_P (o2))
	  /*Nop*/;
	નહીંતર જો (!c_વૃક્ષ_equal (o1, o2))
	  પાછા ખોટું;

	પાછા c_વૃક્ષ_equal (વૃક્ષ_OPERAND (t1, 1), વૃક્ષ_OPERAND (t2, 1));
      }

    સ્થિતિ COMPONENT_REF:
      જો (વૃક્ષ_OPERAND (t1, 1) != વૃક્ષ_OPERAND (t2, 1))
	પાછા ખોટું;
      પાછા c_વૃક્ષ_equal (વૃક્ષ_OPERAND (t1, 0), વૃક્ષ_OPERAND (t2, 0));

    સ્થિતિ PARM_DECL:
    સ્થિતિ VAR_DECL:
    સ્થિતિ CONST_DECL:
    સ્થિતિ FIELD_DECL:
    સ્થિતિ FUNCTION_DECL:
    સ્થિતિ IDENTIFIER_ગાંઠ:
    સ્થિતિ SSA_NAME:
      પાછા ખોટું;

    સ્થિતિ વૃક્ષ_VEC:
      {
	unsigned ix;
	જો (વૃક્ષ_VEC_LENGTH (t1) != વૃક્ષ_VEC_LENGTH (t2))
	  પાછા ખોટું;
	માટે (ix = વૃક્ષ_VEC_LENGTH (t1); ix--;)
	  જો (!c_વૃક્ષ_equal (વૃક્ષ_VEC_ELT (t1, ix),
			     વૃક્ષ_VEC_ELT (t2, ix)))
	    પાછા ખોટું;
	પાછા સાચું;
      }

    CASE_CONVERT:
      જો (!comptypes (વૃક્ષ_TYPE (t1), વૃક્ષ_TYPE (t2)))
	પાછા ખોટું;
      તોડો;

    મૂળભૂત:
      તોડો;
    }

  પસંદગી (વૃક્ષ_CODE_CLASS (code1))
    {
    સ્થિતિ tcc_unary:
    સ્થિતિ tcc_દ્વિઅંકી:
    સ્થિતિ tcc_comparison:
    સ્થિતિ tcc_expression:
    સ્થિતિ tcc_vl_exp:
    સ્થિતિ tcc_reference:
    સ્થિતિ tcc_statement:
      {
	પૂર્ણાંક i, n = વૃક્ષ_OPERAND_LENGTH (t1);

	પસંદગી (code1)
	  {
	  સ્થિતિ PREINCREMENT_પદાવલિ:
	  સ્થિતિ PREDECREMENT_પદાવલિ:
	  સ્થિતિ POSTINCREMENT_પદાવલિ:
	  સ્થિતિ POSTDECREMENT_પદાવલિ:
	    n = 1;
	    તોડો;
	  સ્થિતિ ARRAY_REF:
	    n = 2;
	    તોડો;
	  મૂળભૂત:
	    તોડો;
	  }

	જો (વૃક્ષ_CODE_CLASS (code1) == tcc_vl_exp
	    && n != વૃક્ષ_OPERAND_LENGTH (t2))
	  પાછા ખોટું;

	માટે (i = 0; i < n; ++i)
	  જો (!c_વૃક્ષ_equal (વૃક્ષ_OPERAND (t1, i), વૃક્ષ_OPERAND (t2, i)))
	    પાછા ખોટું;

	પાછા સાચું;
      }

    સ્થિતિ tcc_type:
      પાછા comptypes (t1, t2);
    મૂળભૂત:
      gcc_unreachable ();
    }
}

/* Returns true when the function declaration FNDECL is implicit,
   introduced as a result of a call to an otherwise undeclared
   function, and false otherwise.  */

તાર્કિક
c_decl_implicit (const_વૃક્ષ fndecl)
{
  પાછા C_DECL_IMPLICIT (fndecl);
}
