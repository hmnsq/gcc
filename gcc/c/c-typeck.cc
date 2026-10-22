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

#അന്തര്ഭാവ "config.h"
#അന്തര്ഭാവ "system.h"
#അന്തര്ഭാവ "coretypes.h"
#അന്തര്ഭാവ "memmodel.h"
#അന്തര്ഭാവ "target.h"
#അന്തര്ഭാവ "function.h"
#അന്തര്ഭാവ "bitmap.h"
#അന്തര്ഭാവ "c-tree.h"
#അന്തര്ഭാവ "gimple-expr.h"
#അന്തര്ഭാവ "predict.h"
#അന്തര്ഭാവ "stor-layout.h"
#അന്തര്ഭാവ "trans-mem.h"
#അന്തര്ഭാവ "varasm.h"
#അന്തര്ഭാവ "stmt.h"
#അന്തര്ഭാവ "langhooks.h"
#അന്തര്ഭാവ "c-lang.h"
#അന്തര്ഭാവ "intl.h"
#അന്തര്ഭാവ "tree-iterator.h"
#അന്തര്ഭാവ "gimplify.h"
#അന്തര്ഭാവ "tree-inline.h"
#അന്തര്ഭാവ "omp-general.h"
#അന്തര്ഭാവ "c-family/c-objc.h"
#അന്തര്ഭാവ "c-family/c-ubsan.h"
#അന്തര്ഭാവ "gomp-constants.h"
#അന്തര്ഭാവ "spellcheck-tree.h"
#അന്തര്ഭാവ "c-family/c-type-mismatch.h"
#അന്തര്ഭാവ "stringpool.h"
#അന്തര്ഭാവ "attribs.h"
#അന്തര്ഭാവ "asan.h"
#അന്തര്ഭാവ "realmpfr.h"
#അന്തര്ഭാവ "tree-pretty-print-markup.h"
#അന്തര്ഭാവ "gcc-urlifier.h"

/* Possible cases of implicit conversions.  Used to select diagnostic messages
   and control folding initializers in convert_for_assignment.  */
എണ്ണൽ impl_conv {
  ic_argpass,
  ic_assign,
  ic_init,
  ic_init_const,
  ic_return
};

/* The level of nesting inside "__alignof__".  */
പൂർണ്ണസംഖ്യ in_alignof;

/* The level of nesting inside "sizeof".  */
പൂർണ്ണസംഖ്യ in_sizeof;

/* The level of nesting inside "countof".  */
പൂർണ്ണസംഖ്യ in_countof;

/* The level of nesting inside "typeof".  */
പൂർണ്ണസംഖ്യ in_typeof;

/* The level of nesting inside "_Generic".  */
പൂർണ്ണസംഖ്യ in_generic;

/* True when parsing OpenMP loop expressions.  */
തർക്കം c_in_omp_for;

/* True when parsing OpenMP map clause.  */
തർക്കം c_omp_array_section_p;

/* The argument of last parsed sizeof expression, only to be tested
   if expr.original_code == SIZEOF_EXPR.  */
വൃക്ഷം c_last_sizeof_arg;
location_t c_last_sizeof_loc;

/* Nonzero if we might need to print a "missing braces around
   initializer" message within this initializer.  */
സ്ഥിതം പൂർണ്ണസംഖ്യ found_missing_braces;

സ്ഥിതം തർക്കം require_constant_മൂല്യം;
സ്ഥിതം തർക്കം require_constant_elements;
സ്ഥിതം തർക്കം require_constexpr_മൂല്യം;

സ്ഥിതം വൃക്ഷം qualify_type (വൃക്ഷം, വൃക്ഷം);
ഘടന comptypes_data;
സ്ഥിതം തർക്കം tagged_types_tu_compatible_p (const_വൃക്ഷം, const_വൃക്ഷം,
					  ഘടന comptypes_data *);
സ്ഥിതം തർക്കം comp_target_types (location_t, വൃക്ഷം, വൃക്ഷം);
സ്ഥിതം തർക്കം function_types_compatible_p (const_വൃക്ഷം, const_വൃക്ഷം,
					 ഘടന comptypes_data *);
സ്ഥിതം തർക്കം type_lists_compatible_p (const_വൃക്ഷം, const_വൃക്ഷം,
				     ഘടന comptypes_data *);
സ്ഥിതം പൂർണ്ണസംഖ്യ convert_arguments (location_t, vec<location_t>, വൃക്ഷം,
			      vec<വൃക്ഷം, va_gc> *, vec<വൃക്ഷം, va_gc> *, വൃക്ഷം,
			      വൃക്ഷം);
സ്ഥിതം വൃക്ഷം pointer_diff (location_t, വൃക്ഷം, വൃക്ഷം, വൃക്ഷം *);
സ്ഥിതം വൃക്ഷം convert_for_assignment (location_t, location_t, വൃക്ഷം, വൃക്ഷം, വൃക്ഷം,
				    എണ്ണൽ impl_conv, തർക്കം, വൃക്ഷം, വൃക്ഷം, പൂർണ്ണസംഖ്യ,
				    പൂർണ്ണസംഖ്യ = 0);
സ്ഥിതം വൃക്ഷം valid_compound_വ്യഞ്ജകം_initializer (വൃക്ഷം, വൃക്ഷം);
സ്ഥിതം ശൂന്യം തള്ളുക_string (സ്ഥിരം അക്ഷരം *);
സ്ഥിതം ശൂന്യം തള്ളുക_member_name (വൃക്ഷം);
സ്ഥിതം പൂർണ്ണസംഖ്യ spelling_length (ശൂന്യം);
സ്ഥിതം അക്ഷരം *print_spelling (അക്ഷരം *);
സ്ഥിതം ശൂന്യം warning_init (location_t, പൂർണ്ണസംഖ്യ, സ്ഥിരം അക്ഷരം *);
സ്ഥിതം വൃക്ഷം digest_init (location_t, വൃക്ഷം, വൃക്ഷം, വൃക്ഷം, വൃക്ഷം, തർക്കം, തർക്കം, തർക്കം,
			 തർക്കം, തർക്കം, തർക്കം);
സ്ഥിതം ശൂന്യം output_init_element (location_t, വൃക്ഷം, വൃക്ഷം, തർക്കം, വൃക്ഷം, വൃക്ഷം, തർക്കം,
				 തർക്കം, ഘടന obstack *);
സ്ഥിതം ശൂന്യം output_pending_init_elements (പൂർണ്ണസംഖ്യ, ഘടന obstack *);
സ്ഥിതം തർക്കം set_designator (location_t, തർക്കം, ഘടന obstack *);
സ്ഥിതം ശൂന്യം തള്ളുക_range_അട്ടി (വൃക്ഷം, ഘടന obstack *);
സ്ഥിതം ശൂന്യം add_pending_init (location_t, വൃക്ഷം, വൃക്ഷം, വൃക്ഷം, തർക്കം,
			      ഘടന obstack *);
സ്ഥിതം ശൂന്യം set_nonincremental_init (ഘടന obstack *);
സ്ഥിതം ശൂന്യം set_nonincremental_init_from_string (വൃക്ഷം, ഘടന obstack *);
സ്ഥിതം വൃക്ഷം find_init_member (വൃക്ഷം, ഘടന obstack *);
സ്ഥിതം ശൂന്യം readonly_warning (വൃക്ഷം, എണ്ണൽ lvalue_use);
സ്ഥിതം പൂർണ്ണസംഖ്യ lvalue_or_else (location_t, const_വൃക്ഷം, എണ്ണൽ lvalue_use);
സ്ഥിതം ശൂന്യം record_maybe_used_decl (വൃക്ഷം, തർക്കം address);
സ്ഥിതം തർക്കം comptypes_internal (const_വൃക്ഷം, const_വൃക്ഷം,
				ഘടന comptypes_data *data);
സ്ഥിതം തർക്കം comptypes_check_for_composite (വൃക്ഷം t1, വൃക്ഷം t2);
സ്ഥിതം തർക്കം handle_counted_by_p (വൃക്ഷം);
സ്ഥിതം തർക്കം മുകൾ_array_vla_p (const_വൃക്ഷം type);


/* Return true if EXP is a null pointer constant, false otherwise.  */

തർക്കം
null_pointer_constant_p (const_വൃക്ഷം വ്യഞ്ജകം)
{
  /* This should really operate on c_expr structures, but they aren't
     yet available everywhere required.  */
  വൃക്ഷം type = വൃക്ഷം_TYPE (വ്യഞ്ജകം);

  /* An integer constant expression with the value 0, such an expression
     cast to type void*, or the predefined constant nullptr, are a null
     pointer constant.  */
  എങ്കിൽ (വ്യഞ്ജകം == nullptr_കണ്ണി)
    തിരികെ സത്യം;

  തിരികെ (വൃക്ഷം_CODE (വ്യഞ്ജകം) == INTEGER_CST
	  && !വൃക്ഷം_OVERFLOW (വ്യഞ്ജകം)
	  && integer_zerop (വ്യഞ്ജകം)
	  && (INTEGRAL_TYPE_P (type)
	      || (വൃക്ഷം_CODE (type) == POINTER_TYPE
		  && VOID_TYPE_P (വൃക്ഷം_TYPE (type))
		  && TYPE_QUALS (വൃക്ഷം_TYPE (type)) == TYPE_UNQUALIFIED)));
}

/* EXPR may appear in an unevaluated part of an integer constant
   expression, but not in an evaluated part.  Wrap it in a
   C_MAYBE_CONST_EXPR, or mark it with TREE_OVERFLOW if it is just an
   INTEGER_CST and we cannot create a C_MAYBE_CONST_EXPR.  */

സ്ഥിതം വൃക്ഷം
note_integer_operands (വൃക്ഷം വ്യഞ്ജകം)
{
  വൃക്ഷം ret;
  എങ്കിൽ (വൃക്ഷം_CODE (വ്യഞ്ജകം) == INTEGER_CST && in_late_ദ്വിമാന_op)
    {
      ret = copy_കണ്ണി (വ്യഞ്ജകം);
      വൃക്ഷം_OVERFLOW (ret) = 1;
    }
  അല്ലെങ്കിൽ
    {
      ret = build2 (C_MAYBE_CONST_വ്യഞ്ജകം, വൃക്ഷം_TYPE (വ്യഞ്ജകം), NULL_വൃക്ഷം, വ്യഞ്ജകം);
      C_MAYBE_CONST_വ്യഞ്ജകം_INT_OPERANDS (ret) = 1;
    }
  തിരികെ ret;
}

/* Having checked whether EXPR may appear in an unevaluated part of an
   integer constant expression and found that it may, remove any
   C_MAYBE_CONST_EXPR noting this fact and return the resulting
   expression.  */

സ്ഥിതം വരിയിൽ വൃക്ഷം
remove_c_maybe_const_വ്യഞ്ജകം (വൃക്ഷം വ്യഞ്ജകം)
{
  എങ്കിൽ (വൃക്ഷം_CODE (വ്യഞ്ജകം) == C_MAYBE_CONST_വ്യഞ്ജകം)
    തിരികെ C_MAYBE_CONST_വ്യഞ്ജകം_വ്യഞ്ജകം (വ്യഞ്ജകം);
  അല്ലെങ്കിൽ
    തിരികെ വ്യഞ്ജകം;
}

/* This is a cache to hold if two types are seen.  */

ഘടന tagged_tu_seen_cache {
  സ്ഥിരം ഘടന tagged_tu_seen_cache * next;
  const_വൃക്ഷം t1;
  const_വൃക്ഷം t2;
};

/* Do `exp = require_complete_type (loc, exp);' to make sure exp
   does not have an incomplete type.  (That includes void types.)
   LOC is the location of the use.  */

വൃക്ഷം
require_complete_type (location_t loc, വൃക്ഷം മൂല്യം)
{
  വൃക്ഷം type = വൃക്ഷം_TYPE (മൂല്യം);

  എങ്കിൽ (error_operand_p (മൂല്യം))
    തിരികെ error_mark_കണ്ണി;

  /* First, detect a valid value with a complete type.  */
  എങ്കിൽ (COMPLETE_TYPE_P (type))
    തിരികെ മൂല്യം;

  c_incomplete_type_error (loc, മൂല്യം, type);
  തിരികെ error_mark_കണ്ണി;
}

/* Print an error message for invalid use of an incomplete type.
   VALUE is the expression that was used (or 0 if that isn't known)
   and TYPE is the type that was invalid.  LOC is the location for
   the error.  */

ശൂന്യം
c_incomplete_type_error (location_t loc, const_വൃക്ഷം മൂല്യം, const_വൃക്ഷം type)
{
  /* Avoid duplicate error message.  */
  എങ്കിൽ (വൃക്ഷം_CODE (type) == ERROR_MARK)
    തിരികെ;

  എങ്കിൽ (മൂല്യം != NULL_വൃക്ഷം && (VAR_P (മൂല്യം) || വൃക്ഷം_CODE (മൂല്യം) == PARM_DECL))
    error_at (loc, "%qD has an incomplete type %qT", മൂല്യം, type);
  അല്ലെങ്കിൽ
    {
    retry:
      /* We must print an error message.  Be clever about what it says.  */

      തിരഞ്ഞെടുപ്പ് (വൃക്ഷം_CODE (type))
	{
	അവസ്ഥ RECORD_TYPE:
	അവസ്ഥ UNION_TYPE:
	അവസ്ഥ ENUMERAL_TYPE:
	  നിർത്തുക;

	അവസ്ഥ VOID_TYPE:
	  error_at (loc, "invalid use of void expression");
	  തിരികെ;

	അവസ്ഥ ARRAY_TYPE:
	  എങ്കിൽ (TYPE_DOMAIN (type))
	    {
	      എങ്കിൽ (flexible_array_member_type_p (type))
		{
		  error_at (loc, "invalid use of flexible array member");
		  തിരികെ;
		}
	      type = വൃക്ഷം_TYPE (type);
	      പോകുക retry;
	    }
	  error_at (loc, "invalid use of array with unspecified bounds");
	  തിരികെ;

	സ്ഥിരസ്ഥിതി:
	  gcc_unreachable ();
	}

      എങ്കിൽ (വൃക്ഷം_CODE (TYPE_NAME (type)) == IDENTIFIER_കണ്ണി)
	error_at (loc, "invalid use of undefined type %qT", type);
      അല്ലെങ്കിൽ
	/* If this type has a typedef-name, the TYPE_NAME is a TYPE_DECL.  */
	error_at (loc, "invalid use of incomplete typedef %qT", type);
    }
}

/* Given a type, apply default promotions wrt unnamed function
   arguments and return the new type.  */

വൃക്ഷം
c_type_promotes_to (വൃക്ഷം type)
{
  വൃക്ഷം ret = NULL_വൃക്ഷം;

  എങ്കിൽ (TYPE_MAIN_VARIANT (type) == float_type_കണ്ണി)
    ret = double_type_കണ്ണി;
  അല്ലെങ്കിൽ എങ്കിൽ (c_promoting_integer_type_p (type))
    {
      /* Preserve unsignedness if not really getting any wider.  */
      എങ്കിൽ (TYPE_UNSIGNED (type)
	  && (TYPE_PRECISION (type) == TYPE_PRECISION (integer_type_കണ്ണി)))
	ret = unsigned_type_കണ്ണി;
      അല്ലെങ്കിൽ
	ret = integer_type_കണ്ണി;
    }

  എങ്കിൽ (ret != NULL_വൃക്ഷം)
    തിരികെ (TYPE_ATOMIC (type)
	    ? c_build_qualified_type (ret, TYPE_QUAL_ATOMIC)
	    : ret);

  തിരികെ type;
}

/* Return true if between two named address spaces, whether there is a superset
   named address space that encompasses both address spaces.  If there is a
   superset, return which address space is the superset.  */

സ്ഥിതം തർക്കം
addr_space_superset (addr_space_t as1, addr_space_t as2, addr_space_t *common)
{
  എങ്കിൽ (as1 == as2)
    {
      *common = as1;
      തിരികെ സത്യം;
    }
  അല്ലെങ്കിൽ എങ്കിൽ (targetm.addr_space.subset_p (as1, as2))
    {
      *common = as2;
      തിരികെ സത്യം;
    }
  അല്ലെങ്കിൽ എങ്കിൽ (targetm.addr_space.subset_p (as2, as1))
    {
      *common = as1;
      തിരികെ സത്യം;
    }
  അല്ലെങ്കിൽ
    തിരികെ അസത്യം;
}

/* Return a variant of TYPE which has all the type qualifiers of LIKE
   as well as those of TYPE.  */

സ്ഥിതം വൃക്ഷം
qualify_type (വൃക്ഷം type, വൃക്ഷം like)
{
  addr_space_t as_type = TYPE_ADDR_SPACE (type);
  addr_space_t as_like = TYPE_ADDR_SPACE (like);
  addr_space_t as_common;

  /* If the two named address spaces are different, determine the common
     superset address space.  If there isn't one, raise an error.  */
  എങ്കിൽ (!addr_space_superset (as_type, as_like, &as_common))
    {
      as_common = as_type;
      error ("%qT and %qT are in disjoint named address spaces",
	     type, like);
    }

  തിരികെ c_build_qualified_type (type,
				 TYPE_QUALS_NO_ADDR_SPACE (type)
				 | TYPE_QUALS_NO_ADDR_SPACE_NO_ATOMIC (like)
				 | ENCODE_QUAL_ADDR_SPACE (as_common));
}


/* Check consistency of type TYPE.  For derived types, we test that
   C_TYPE_VARIABLE_SIZE and C_TYPE_VARIABLY_MODIFIED are consistent with
   the requirements of the base type.  We also check that arrays with a
   non-constant length are marked with C_TYPE_VARIABLE_SIZE. If any
   inconsistency is detected false is returned and true otherwise.  */

സ്ഥിതം തർക്കം
c_verify_type (വൃക്ഷം type)
{
  തിരഞ്ഞെടുപ്പ് (വൃക്ഷം_CODE (type))
    {
    അവസ്ഥ POINTER_TYPE:
    അവസ്ഥ FUNCTION_TYPE:
    അവസ്ഥ ARRAY_TYPE:
      /* Pointer, array, functions are variably modified if and only if the
	 target, element, return type is variably modified.  */
      എങ്കിൽ (!TYPE_STRUCTURAL_EQUALITY_P (type)
	  && (C_TYPE_VARIABLY_MODIFIED (type)
	      != C_TYPE_VARIABLY_MODIFIED (വൃക്ഷം_TYPE (type))))
	തിരികെ അസത്യം;
      /* If the target type is structural equality, the type should also. */
      എങ്കിൽ (!TYPE_STRUCTURAL_EQUALITY_P (type)
	  && TYPE_STRUCTURAL_EQUALITY_P (വൃക്ഷം_TYPE (type)))
	തിരികെ അസത്യം;
    സ്ഥിരസ്ഥിതി:
       നിർത്തുക;
    }

  തിരഞ്ഞെടുപ്പ് (വൃക്ഷം_CODE (type))
    {
    അവസ്ഥ POINTER_TYPE:
    അവസ്ഥ FUNCTION_TYPE:
      /* Pointer and functions can not have variable size.  */
      എങ്കിൽ (C_TYPE_VARIABLE_SIZE (type))
	തിരികെ അസത്യം;
      നിർത്തുക;
    അവസ്ഥ ARRAY_TYPE:
      /* An array has variable size if and only if it has a non-constant
	 dimensions or its element type has variable size.  */
      എങ്കിൽ ((C_TYPE_VARIABLE_SIZE (വൃക്ഷം_TYPE (type))
	   || മുകൾ_array_vla_p (type))
	  != C_TYPE_VARIABLE_SIZE (type))
	തിരികെ അസത്യം;
      /* If the element type or the array has variable size, then the
	 array has variable size and is variably modified.  */
      എങ്കിൽ (C_TYPE_VARIABLE_SIZE (വൃക്ഷം_TYPE (type))
	  || C_TYPE_VARIABLE_SIZE (type))
	{
	  എങ്കിൽ (!C_TYPE_VARIABLE_SIZE (type))
	    തിരികെ അസത്യം;
	  എങ്കിൽ (!C_TYPE_VARIABLY_MODIFIED (type))
	    തിരികെ അസത്യം;
	}

      /* va_list violates this, accept such types here.  */
      എങ്കിൽ (!COMPLETE_TYPE_P (വൃക്ഷം_TYPE (type)))
	തിരികെ സത്യം;

      എങ്കിൽ (COMPLETE_TYPE_P (type))
	{
	  /* If the size is unknown, it can not be complete.  */
	  എങ്കിൽ (NULL_വൃക്ഷം == TYPE_DOMAIN (type))
	    തിരികെ അസത്യം;

	  /* Zero-length arrays must have size zero.  */
	  എങ്കിൽ (zero_length_array_type_p (type)
	      && !integer_zerop (TYPE_SIZE (type)))
	    തിരികെ അസത്യം;
	}
      അല്ലെങ്കിൽ
	{
	  /* If not complete but has a domain, it must be a FAM.  */
	  എങ്കിൽ (NULL_വൃക്ഷം != TYPE_DOMAIN (type)
	      && !flexible_array_member_type_p (type))
	    തിരികെ അസത്യം;
	}
    സ്ഥിരസ്ഥിതി:
      നിർത്തുക;
    }
  തിരികെ സത്യം;
}

/* Propagate C_TYPE_VARIABLY_MODIFIED and C_TYPE_VARIABLE_SIZE
   from a base type to a newly built derived or qualified type.  */

സ്ഥിതം വൃക്ഷം
c_set_type_bits (വൃക്ഷം new_type, വൃക്ഷം old_type)
{
  gcc_checking_assert (c_verify_type (old_type));

  എങ്കിൽ (c_type_variably_modified_p (old_type))
    C_TYPE_VARIABLY_MODIFIED (new_type) = സത്യം;

  എങ്കിൽ (വൃക്ഷം_CODE (new_type) == ARRAY_TYPE && C_TYPE_VARIABLE_SIZE (old_type))
    {
      C_TYPE_VARIABLY_MODIFIED (new_type) = സത്യം;
      C_TYPE_VARIABLE_SIZE (new_type) = സത്യം;
    }
  തിരികെ new_type;
}

/* Build a pointer type using the default pointer mode.  */

വൃക്ഷം
c_build_pointer_type (വൃക്ഷം to_type)
{
  addr_space_t as = to_type == error_mark_കണ്ണി ? ADDR_SPACE_GENERIC
					       : TYPE_ADDR_SPACE (to_type);
  machine_mode pointer_mode;

  എങ്കിൽ (as != ADDR_SPACE_GENERIC || c_default_pointer_mode == VOIDmode)
    pointer_mode = targetm.addr_space.pointer_mode (as);
  അല്ലെങ്കിൽ
    pointer_mode = c_default_pointer_mode;

  തിരികെ c_build_pointer_type_for_mode (to_type, pointer_mode, അസത്യം);
}

/* Build a pointer type using the given mode.  */

വൃക്ഷം
c_build_pointer_type_for_mode (വൃക്ഷം type, machine_mode mode, തർക്കം m)
{
  വൃക്ഷം ret = build_pointer_type_for_mode (type, mode, m);
  തിരികെ c_set_type_bits (ret, type);
}

/* Build a function type.  */

വൃക്ഷം
c_build_function_type (വൃക്ഷം type, വൃക്ഷം args, തർക്കം no)
{
  വൃക്ഷം ret = build_function_type (type, args, no);
  തിരികെ c_set_type_bits (ret, type);
}

/* Build an array type.  This sets typeless storage as required
   by C2Y and C_TYPE_VARIABLY_MODIFIED and C_TYPE_VARIABLE_SIZE
   based on the element type and domain.  */

വൃക്ഷം
c_build_array_type (വൃക്ഷം type, വൃക്ഷം domain)
{
  പൂർണ്ണസംഖ്യ type_quals = TYPE_QUALS (type);

  /* Identify typeless storage as introduced in C2Y
     and supported also in earlier language modes.  */
  തർക്കം typeless = (char_type_p (type) && !(type_quals & TYPE_QUAL_ATOMIC))
		  || (AGGREGATE_TYPE_P (type) && TYPE_TYPELESS_STORAGE (type));

  വൃക്ഷം ret = build_array_type (type, domain, typeless);

  എങ്കിൽ (മുകൾ_array_vla_p (ret))
    {
      C_TYPE_VARIABLE_SIZE (ret) = 1;
      C_TYPE_VARIABLY_MODIFIED (ret) = 1;
    }

  തിരികെ c_set_type_bits (ret, type);
}

/* Build an array type of unspecified size.  */
വൃക്ഷം
c_build_array_type_unspecified (വൃക്ഷം type)
{
  വൃക്ഷം upper = build2 (COMPOUND_വ്യഞ്ജകം, വൃക്ഷം_TYPE (size_zero_കണ്ണി),
		       integer_zero_കണ്ണി, size_zero_കണ്ണി);
  തിരികെ c_build_array_type (type, build_index_type (upper));
}

/* Build an array type of zero size.  */
വൃക്ഷം
c_build_array_type_zero_size (വൃക്ഷം type)
{
  /* The GCC extension for zero-length arrays differs from
     ISO flexible array members in that sizeof yields
     zero.  */
  type = c_build_array_type (type, build_index_type (NULL_വൃക്ഷം));
  type = build_distinct_type_copy (TYPE_MAIN_VARIANT (type));
  TYPE_SIZE (type) = bitsize_zero_കണ്ണി;
  TYPE_SIZE_UNIT (type) = size_zero_കണ്ണി;
  SET_TYPE_STRUCTURAL_EQUALITY (type);
  തിരികെ type;
}

വൃക്ഷം
c_build_type_attribute_qual_variant (വൃക്ഷം type, വൃക്ഷം attrs, പൂർണ്ണസംഖ്യ quals)
{
  വൃക്ഷം ret = build_type_attribute_qual_variant (type, attrs, quals);
  തിരികെ c_set_type_bits (ret, type);
}

വൃക്ഷം
c_build_type_attribute_variant (വൃക്ഷം type, വൃക്ഷം attrs)
{
  തിരികെ c_build_type_attribute_qual_variant (type, attrs, TYPE_QUALS (type));
}

/* Reconstruct a complex derived type.  This is used to re-construct types
   with the vector attribute.  It is called via a langhook.  */

വൃക്ഷം
c_reconstruct_complex_type (വൃക്ഷം type, വൃക്ഷം bottom)
{
  വൃക്ഷം inner, outer;

  എങ്കിൽ (വൃക്ഷം_CODE (type) == POINTER_TYPE)
    {
      inner = c_reconstruct_complex_type (വൃക്ഷം_TYPE (type), bottom);
      outer = c_build_pointer_type_for_mode (inner, TYPE_MODE (type),
					     TYPE_REF_CAN_ALIAS_ALL (type));
    }
  അല്ലെങ്കിൽ എങ്കിൽ (വൃക്ഷം_CODE (type) == ARRAY_TYPE)
    {
      തർക്കം rso = TYPE_REVERSE_STORAGE_ORDER (type);
      inner = c_reconstruct_complex_type (വൃക്ഷം_TYPE (type), bottom);
      outer = c_build_array_type (inner, TYPE_DOMAIN (type));
      എങ്കിൽ (rso)
	{
	  outer = build_distinct_type_copy (outer);
	  TYPE_REVERSE_STORAGE_ORDER (outer) = 1;
	}

      gcc_checking_assert (C_TYPE_VARIABLE_SIZE (type)
			   == C_TYPE_VARIABLE_SIZE (outer));
    }
  അല്ലെങ്കിൽ എങ്കിൽ (വൃക്ഷം_CODE (type) == FUNCTION_TYPE)
    {
      inner = c_reconstruct_complex_type (വൃക്ഷം_TYPE (type), bottom);
      outer = c_build_function_type (inner, TYPE_ARG_TYPES (type),
				     TYPE_NO_NAMED_ARGS_STDARG_P (type));
    }
  അല്ലെങ്കിൽ എങ്കിൽ (വൃക്ഷം_CODE (type) == REFERENCE_TYPE
	   || വൃക്ഷം_CODE (type) == OFFSET_TYPE)
    gcc_unreachable ();
  അല്ലെങ്കിൽ
    തിരികെ bottom;

  തിരികെ c_build_type_attribute_qual_variant (outer, TYPE_ATTRIBUTES (type),
					      TYPE_QUALS (type));
}


/* Helper function for c_canonical_type.  Check whether FIELD
   contains a pointer to a structure or union with tag,
   possibly nested in other type derivations, and return the
   type of this nested structure or union.  */
സ്ഥിതം വൃക്ഷം
ptr_to_tagged_member (വൃക്ഷം field)
{
  gcc_assert (FIELD_DECL == വൃക്ഷം_CODE (field));
  വൃക്ഷം type = വൃക്ഷം_TYPE (field);
  തർക്കം ptr_seen = അസത്യം;
  ആകുമ്പോൾ (വൃക്ഷം_CODE (type) == ARRAY_TYPE
	 || വൃക്ഷം_CODE (type) == FUNCTION_TYPE
	 || വൃക്ഷം_CODE (type) == POINTER_TYPE)
    {
      എങ്കിൽ (വൃക്ഷം_CODE (type) == POINTER_TYPE)
	ptr_seen = സത്യം;
      type = വൃക്ഷം_TYPE (type);
    }

  എങ്കിൽ (ptr_seen
      && RECORD_OR_UNION_TYPE_P (type)
      && NULL_വൃക്ഷം != c_type_tag (type))
    തിരികെ type;

  തിരികെ NULL_വൃക്ഷം;
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
വൃക്ഷം
c_type_canonical (വൃക്ഷം type)
{
  gcc_assert (RECORD_OR_UNION_TYPE_P (type));

  തർക്കം needs_mod = അസത്യം;
  വേണ്ടി (വൃക്ഷം x = TYPE_FIELDS (type); x; x = DECL_CHAIN (x))
    {
      എങ്കിൽ (!ptr_to_tagged_member (x))
	തുടരുക;
      needs_mod = സത്യം;
      നിർത്തുക;
    }
  എങ്കിൽ (!needs_mod)
    തിരികെ type;

  /* Construct new version with such members replaced.  */
  വൃക്ഷം n = build_distinct_type_copy (type);
  വൃക്ഷം *fields = &TYPE_FIELDS (n);
  വേണ്ടി (വൃക്ഷം x = TYPE_FIELDS (type); x; x = DECL_CHAIN (x))
    {
      വൃക്ഷം f = copy_കണ്ണി (x);
      എങ്കിൽ (വൃക്ഷം m = ptr_to_tagged_member (x))
	{
	  വൃക്ഷം new_കണ്ണി = make_കണ്ണി (വൃക്ഷം_CODE (m));
	  TYPE_NAME (new_കണ്ണി) = TYPE_NAME (m);
	  SET_TYPE_STRUCTURAL_EQUALITY (new_കണ്ണി);
	  new_കണ്ണി = qualify_type (new_കണ്ണി, m);
	  വൃക്ഷം_TYPE (f) = c_reconstruct_complex_type (വൃക്ഷം_TYPE (x),
						      new_കണ്ണി);
	}
      *fields = f;
      fields = &DECL_CHAIN (f);
    }
  TYPE_CANONICAL (n) = n;
  തിരികെ n;
}


/* If NTYPE is a type of a non-variadic function with a prototype
   and OTYPE is a type of a function without a prototype and ATTRS
   contains attribute format, diagnosess and removes it from ATTRS.
   Returns the result of build_type_attribute_variant of NTYPE and
   the (possibly) modified ATTRS.  */

സ്ഥിതം വൃക്ഷം
c_build_functype_attribute_variant (വൃക്ഷം ntype, വൃക്ഷം otype, വൃക്ഷം attrs)
{
  എങ്കിൽ (!prototype_p (otype)
      && prototype_p (ntype)
      && lookup_attribute ("format", attrs))
    {
      warning_at (നിവേശം_location, OPT_Wattributes,
		  "%qs attribute can only be applied to variadic functions",
		  "format");
      attrs = remove_attribute ("format", attrs);
    }
  തിരികെ c_build_type_attribute_variant (ntype, attrs);

}

/* Given a type which could be a typedef name, make sure to return the
   original type.  See set_underlying_type. */
സ്ഥിതം const_വൃക്ഷം
c_type_original (const_വൃക്ഷം t)
{
  /* It may even be a typedef of a typedef...
     In the case of compiler-created builtin structs the TYPE_DECL
     may be a dummy, with no DECL_ORIGINAL_TYPE.  Don't fault.  */
  ആകുമ്പോൾ (TYPE_NAME (t)
	 && വൃക്ഷം_CODE (TYPE_NAME (t)) == TYPE_DECL
	 && DECL_ORIGINAL_TYPE (TYPE_NAME (t)))
    t = DECL_ORIGINAL_TYPE (TYPE_NAME (t));
  തിരികെ t;
}

/* Return the tag for a tagged type.  */
വൃക്ഷം
c_type_tag (const_വൃക്ഷം t)
{
  gcc_assert (RECORD_OR_UNION_TYPE_P (t) || വൃക്ഷം_CODE (t) == ENUMERAL_TYPE);
  const_വൃക്ഷം orig = c_type_original (t);
  വൃക്ഷം name = TYPE_NAME (orig);
  എങ്കിൽ (!name)
    തിരികെ NULL_വൃക്ഷം;
  എങ്കിൽ (വൃക്ഷം_CODE (name) == TYPE_DECL)
    {
      എങ്കിൽ (!DECL_NAME (name))
	തിരികെ NULL_വൃക്ഷം;
      name = DECL_NAME (name);
    }
  gcc_checking_assert (വൃക്ഷം_CODE (name) == IDENTIFIER_കണ്ണി);
  തിരികെ name;
}

/* Remove qualifiers but not atomic.  For arrays remove qualifiers
   on the element type but also do not remove atomic.  */
സ്ഥിതം വൃക്ഷം
remove_qualifiers (വൃക്ഷം t)
{
  എങ്കിൽ (!t || t == error_mark_കണ്ണി)
    തിരികെ t;
  തിരികെ TYPE_ATOMIC (strip_array_types (t))
	 ? c_build_qualified_type (TYPE_MAIN_VARIANT (t), TYPE_QUAL_ATOMIC)
	 : TYPE_MAIN_VARIANT (t);
}


/* Helper function for composite_type_internal.  Find a compatible type
   in a (transparent) union U compatible to T.  If found, return the
   type of the corresponding member.  Otherwise, return the union type U.  */
സ്ഥിതം വൃക്ഷം
transparent_union_replacement (വൃക്ഷം u, വൃക്ഷം t)
{
  എങ്കിൽ (u == error_mark_കണ്ണി || t == error_mark_കണ്ണി
      || വൃക്ഷം_CODE (u) != UNION_TYPE
      || !(TYPE_TRANSPARENT_AGGR (u) || TYPE_NAME (u) == NULL_വൃക്ഷം)
      || comptypes (u, t))
    തിരികെ u;

  വേണ്ടി (വൃക്ഷം memb = TYPE_FIELDS (u); memb; memb = DECL_CHAIN (memb))
    {
      വൃക്ഷം m = remove_qualifiers (വൃക്ഷം_TYPE (memb));
      എങ്കിൽ (comptypes (m, t))
	{
	  pedwarn (നിവേശം_location, OPT_Wpedantic,
		    "function types not truly compatible in ISO C");
	  തിരികെ m;
	}
    }

  തിരികെ u;
}



/* Return the composite type of two compatible types.

   We assume that comptypes has already been done and returned
   nonzero; if that isn't so, this may crash.  In particular, we
   assume that qualifiers match.  */

ഘടന composite_cache {
  വൃക്ഷം t1;
  വൃക്ഷം t2;
  വൃക്ഷം composite;
  ഘടന composite_cache* next;
};

വൃക്ഷം
composite_type_internal (വൃക്ഷം t1, വൃക്ഷം t2, വൃക്ഷം cond,
			 ഘടന composite_cache* cache)
{
  എണ്ണൽ വൃക്ഷം_code code1;
  എണ്ണൽ വൃക്ഷം_code code2;
  വൃക്ഷം attributes;

  /* Save time if the two types are the same.  */

  എങ്കിൽ (t1 == t2) തിരികെ t1;

  /* If one type is nonsense, use the other.  */
  എങ്കിൽ (t1 == error_mark_കണ്ണി)
    തിരികെ t2;
  എങ്കിൽ (t2 == error_mark_കണ്ണി)
    തിരികെ t1;

  code1 = വൃക്ഷം_CODE (t1);
  code2 = വൃക്ഷം_CODE (t2);

  /* Merge the attributes.  */
  attributes = targetm.merge_type_attributes (t1, t2);

  /* If one is an enumerated type and the other is the compatible
     integer type, the composite type might be either of the two
     (DR#013 question 3).  For consistency, use the enumerated type as
     the composite type.  */

  എങ്കിൽ (code1 == ENUMERAL_TYPE
      && (code2 == INTEGER_TYPE
	  || code2 == BOOLEAN_TYPE))
    തിരികെ t1;
  എങ്കിൽ (code2 == ENUMERAL_TYPE
      && (code1 == INTEGER_TYPE
	  || code1 == BOOLEAN_TYPE))
    തിരികെ t2;

  gcc_assert (code1 == code2);

  തിരഞ്ഞെടുപ്പ് (code1)
    {
    അവസ്ഥ POINTER_TYPE:
      /* For two pointers, do this recursively on the target type.  */
      {
	gcc_checking_assert (TYPE_QUALS (t1) == TYPE_QUALS (t2));
	വൃക്ഷം target = composite_type_internal (വൃക്ഷം_TYPE (t1), വൃക്ഷം_TYPE (t2),
					       cond, cache);
	വൃക്ഷം n = c_build_pointer_type_for_mode (target, TYPE_MODE (t1), അസത്യം);
	തിരികെ c_build_type_attribute_qual_variant (n, attributes,
						    TYPE_QUALS (t2));
      }

    അവസ്ഥ ARRAY_TYPE:
      {
	വൃക്ഷം d1 = TYPE_DOMAIN (t1);
	വൃക്ഷം d2 = TYPE_DOMAIN (t2);

	/* We should not have any type quals on arrays at all.  */
	gcc_assert (!TYPE_QUALS_NO_ADDR_SPACE (t1)
		    && !TYPE_QUALS_NO_ADDR_SPACE (t2));

	തർക്കം d1_zero = zero_length_array_type_p (t1)
		       || flexible_array_member_type_p (t1);
	തർക്കം d2_zero = zero_length_array_type_p (t2)
		       || flexible_array_member_type_p (t2);

	തർക്കം d1_variable = മുകൾ_array_vla_p (t1);
	തർക്കം d2_variable = മുകൾ_array_vla_p (t2);

	തർക്കം use1 = d1 && (d2_variable || !d2 || d2_zero || !d1_variable);
	തർക്കം use2 = d2 && (d1_variable || !d1 || d1_zero || !d2_variable);

	/* If the first is an unspecified size pick the other one.  */
	എങ്കിൽ (d2_variable && c_type_unspecified_p (t1))
	  {
	    gcc_assert (use1 && use2);
	    use1 = അസത്യം;
	  }

	/* If both are VLAs but not unspecified and we are in the
	   conditional operator, we create a conditional to select
	   the size of the active branch.  */
	തർക്കം use0 = cond && d1_variable && !c_type_unspecified_p (t1)
			 && d2_variable && !c_type_unspecified_p (t2);

	വൃക്ഷം td;
	വൃക്ഷം elt = composite_type_internal (വൃക്ഷം_TYPE (t1), വൃക്ഷം_TYPE (t2),
					    cond, cache);

	എങ്കിൽ (!use0)
	  {
	    /* Save space: see if the result is identical to one of the args.  */
	    എങ്കിൽ (elt == വൃക്ഷം_TYPE (t1) && use1)
	      തിരികെ c_build_type_attribute_variant (t1, attributes);
	    എങ്കിൽ (elt == വൃക്ഷം_TYPE (t2) && use2)
	      തിരികെ c_build_type_attribute_variant (t2, attributes);

	    എങ്കിൽ (elt == വൃക്ഷം_TYPE (t1) && !TYPE_DOMAIN (t2) && !TYPE_DOMAIN (t1))
	      തിരികെ c_build_type_attribute_variant (t1, attributes);
	    എങ്കിൽ (elt == വൃക്ഷം_TYPE (t2) && !TYPE_DOMAIN (t2) && !TYPE_DOMAIN (t1))
	      തിരികെ c_build_type_attribute_variant (t2, attributes);

	    td = TYPE_DOMAIN (use1 ? t1 : t2);
	  }
	അല്ലെങ്കിൽ
	  {
	    /* Not used in C.  */
	    gcc_assert (size_zero_കണ്ണി == TYPE_MIN_മൂല്യം (d1));
	    gcc_assert (size_zero_കണ്ണി == TYPE_MIN_മൂല്യം (d2));

	    വൃക്ഷം d = fold_build3_loc (UNKNOWN_LOCATION, COND_വ്യഞ്ജകം, sizetype,
				      cond, TYPE_MAX_മൂല്യം (d1),
				      TYPE_MAX_മൂല്യം (d2));

	    td = build_index_type (d);
	  }

	/* Merge the element types, and have a size if either arg has
	   one.  We may have qualifiers on the element types.  To set
	   up TYPE_MAIN_VARIANT correctly, we need to form the
	   composite of the unqualified types and add the qualifiers
	   back at the end.  */
	പൂർണ്ണസംഖ്യ quals = TYPE_QUALS (strip_array_types (elt));
	വൃക്ഷം unqual_elt = c_build_qualified_type (elt, TYPE_UNQUALIFIED);

	എങ്കിൽ ((!d1 || d1_zero) && (!d2 || d2_zero) && (d1 || d2))
	  t1 = c_build_array_type_zero_size (unqual_elt);
	അല്ലെങ്കിൽ
	  t1 = c_build_array_type (unqual_elt, td);

	/* Check that a type which has a varying outermost dimension
	   got marked as having a variable size.  */
	തർക്കം varsize = (d1_variable && d2_variable)
		       || (d1_variable && !d2)
		       || (d2_variable && !d1);
	gcc_checking_assert (!varsize || C_TYPE_VARIABLE_SIZE (t1));

	t1 = c_build_qualified_type (t1, quals);
	തിരികെ c_build_type_attribute_variant (t1, attributes);
      }

    അവസ്ഥ RECORD_TYPE:
    അവസ്ഥ UNION_TYPE:
      എങ്കിൽ (flag_isoc23 && !comptypes_same_p (t1, t2))
	{
	  /* Go to the original type to get the right tag.  */
	  വൃക്ഷം tag = c_type_tag (t1);

	  gcc_checking_assert (COMPLETE_TYPE_P (t1) && COMPLETE_TYPE_P (t2));
	  gcc_checking_assert (!tag || comptypes (t1, t2));

	  /* If a composite type for these two types is already under
	     construction, return it.  */

	  വേണ്ടി (ഘടന composite_cache *c = cache; c != ശൂന്യ; c = c->next)
	    എങ്കിൽ ((c->t1 == t1 && c->t2 == t2) || (c->t1 == t2 && c->t2 == t1))
	       തിരികെ c->composite;

	  /* Otherwise, create a new type node and link it into the cache.  */

	  വൃക്ഷം n = make_കണ്ണി (code1);
	  SET_TYPE_STRUCTURAL_EQUALITY (n);
	  TYPE_NAME (n) = tag;

	  ഘടന composite_cache cache2 = { t1, t2, n, cache };
	  cache = &cache2;

	  വൃക്ഷം f1 = TYPE_FIELDS (t1);
	  വൃക്ഷം f2 = TYPE_FIELDS (t2);
	  വൃക്ഷം fields = NULL_വൃക്ഷം;

	  വേണ്ടി (വൃക്ഷം a = f1, b = f2; a && b;
	       a = DECL_CHAIN (a), b = DECL_CHAIN (b))
	    {
	      വൃക്ഷം ta = വൃക്ഷം_TYPE (a);
	      വൃക്ഷം tb = വൃക്ഷം_TYPE (b);

	      എങ്കിൽ (DECL_C_BIT_FIELD (a))
		{
		  ta = DECL_BIT_FIELD_TYPE (a);
		  tb = DECL_BIT_FIELD_TYPE (b);
		}

	      gcc_assert (DECL_NAME (a) == DECL_NAME (b));
	      gcc_checking_assert (!DECL_NAME (a) || comptypes (ta, tb));

	      വൃക്ഷം t = composite_type_internal (ta, tb, cond, cache);
	      വൃക്ഷം f = build_decl (നിവേശം_location, FIELD_DECL, DECL_NAME (a), t);

	      DECL_PACKED (f) = DECL_PACKED (a);
	      SET_DECL_ALIGN (f, DECL_ALIGN (a));
	      DECL_ATTRIBUTES (f) = DECL_ATTRIBUTES (a);
	      C_DECL_VARIABLE_SIZE (f) = C_TYPE_VARIABLE_SIZE (t);

	      decl_attributes (&f, DECL_ATTRIBUTES (f), 0);

	      finish_decl (f, നിവേശം_location, ശൂന്യ, ശൂന്യ, ശൂന്യ);

	      എങ്കിൽ (DECL_C_BIT_FIELD (a))
		{
		  /* This will be processed by finish_struct.  */
		  SET_DECL_C_BIT_FIELD (f);
		  DECL_INITIAL (f) = build_int_cst (integer_type_കണ്ണി,
						    വൃക്ഷം_to_uhwi (DECL_SIZE (a)));
		  DECL_NONADDRESSABLE_P (f) = സത്യം;
		  DECL_PADDING_P (f) = !DECL_NAME (a);
		}

	      DECL_CHAIN (f) = fields;
	      fields = f;
	    }

	  fields = nreverse (fields);

	  /* Setup the struct/union type.  Because we inherit all variably
	     modified components, we can ignore the size expression.  */
	  വൃക്ഷം വ്യഞ്ജകം = NULL_വൃക്ഷം;

	  /* Set TYPE_STUB_DECL for debugging symbols.  */
	  TYPE_STUB_DECL (n) = pushdecl (build_decl (നിവേശം_location, TYPE_DECL,
						     NULL_വൃക്ഷം, n));

	  n = finish_struct (നിവേശം_location, n, fields, attributes, ശൂന്യ,
			     &വ്യഞ്ജകം);

	  തിരികെ qualify_type (n, t1);
	}
      /* FALLTHRU */
    അവസ്ഥ ENUMERAL_TYPE:
      എങ്കിൽ (attributes != ശൂന്യ)
	{
	  /* Try harder not to create a new aggregate type.  */
	  എങ്കിൽ (attribute_list_equal (TYPE_ATTRIBUTES (t1), attributes))
	    തിരികെ t1;
	  എങ്കിൽ (attribute_list_equal (TYPE_ATTRIBUTES (t2), attributes))
	    തിരികെ t2;
	}
      തിരികെ c_build_type_attribute_variant (t1, attributes);

    അവസ്ഥ FUNCTION_TYPE:
      /* Function types: prefer the one that specified arg types.
	 If both do, merge the arg types.  Also merge the return types.  */
      {
	വൃക്ഷം valtype = composite_type_internal (വൃക്ഷം_TYPE (t1), വൃക്ഷം_TYPE (t2),
						cond, cache);
	വൃക്ഷം p1 = TYPE_ARG_TYPES (t1);
	വൃക്ഷം p2 = TYPE_ARG_TYPES (t2);

	/* Save space: see if the result is identical to one of the args.  */
	എങ്കിൽ (valtype == വൃക്ഷം_TYPE (t1) && !TYPE_ARG_TYPES (t2))
	  തിരികെ c_build_functype_attribute_variant (t1, t2, attributes);
	എങ്കിൽ (valtype == വൃക്ഷം_TYPE (t2) && !TYPE_ARG_TYPES (t1))
	  തിരികെ c_build_functype_attribute_variant (t2, t1, attributes);

	/* Simple way if one arg fails to specify argument types.  */
	എങ്കിൽ (TYPE_ARG_TYPES (t1) == NULL_വൃക്ഷം)
	  {
	    t1 = c_build_function_type (valtype, TYPE_ARG_TYPES (t2),
					TYPE_NO_NAMED_ARGS_STDARG_P (t2));
	    t1 = c_build_type_attribute_variant (t1, attributes);
	    തിരികെ qualify_type (t1, t2);
	 }
	എങ്കിൽ (TYPE_ARG_TYPES (t2) == NULL_വൃക്ഷം)
	  {
	    t1 = c_build_function_type (valtype, TYPE_ARG_TYPES (t1),
					TYPE_NO_NAMED_ARGS_STDARG_P (t1));
	    t1 = c_build_type_attribute_variant (t1, attributes);
	    തിരികെ qualify_type (t1, t2);
	  }

	/* If both args specify argument types, we must merge the two
	   lists, argument by argument.  */
	വൃക്ഷം newargs = NULL_വൃക്ഷം;
	വൃക്ഷം *endp = &newargs;

	വേണ്ടി (; p1; p1 = വൃക്ഷം_CHAIN (p1), p2 = വൃക്ഷം_CHAIN (p2))
	  {
	    എങ്കിൽ (p1 == void_list_കണ്ണി)
	      {
		*endp = void_list_കണ്ണി;
		നിർത്തുക;
	      }
	    വൃക്ഷം mv1 = remove_qualifiers (വൃക്ഷം_മൂല്യം (p1));
	    വൃക്ഷം mv2 = remove_qualifiers (വൃക്ഷം_മൂല്യം (p2));

	    gcc_assert (mv1);
	    gcc_assert (mv2);

	    mv1 = transparent_union_replacement (mv1, mv2);
	    mv2 = transparent_union_replacement (mv2, mv1);

	    *endp = വൃക്ഷം_cons (NULL_വൃക്ഷം,
			       composite_type_internal (mv1, mv2, cond, cache),
			       NULL_വൃക്ഷം);

	    endp = &വൃക്ഷം_CHAIN (*endp);
	  }

	t1 = c_build_function_type (valtype, newargs);
	t1 = qualify_type (t1, t2);
      }
      /* FALLTHRU */

    സ്ഥിരസ്ഥിതി:
      തിരികെ c_build_type_attribute_variant (t1, attributes);
    }
}

വൃക്ഷം
composite_type_cond (വൃക്ഷം t1, വൃക്ഷം t2, വൃക്ഷം cond)
{
  gcc_checking_assert (comptypes_check_for_composite (t1, t2));

  ഘടന composite_cache cache = { };
  വൃക്ഷം n = composite_type_internal (t1, t2, cond, &cache);

  gcc_checking_assert (comptypes_check_for_composite (n, t1));
  gcc_checking_assert (comptypes_check_for_composite (n, t2));
  തിരികെ n;
}


വൃക്ഷം
composite_type (വൃക്ഷം t1, വൃക്ഷം t2)
{
  തിരികെ composite_type_cond (t1, t2, NULL_വൃക്ഷം);
}

/* Return the type of a conditional expression between pointers to
   possibly differently qualified versions of compatible types.

   We assume that comp_target_types has already been done and returned
   true; if that isn't so, this may crash.  */

സ്ഥിതം വൃക്ഷം
common_pointer_type (വൃക്ഷം t1, വൃക്ഷം t2, വൃക്ഷം cond)
{
  വൃക്ഷം attributes;
  unsigned target_quals;
  addr_space_t as1, as2, as_common;
  പൂർണ്ണസംഖ്യ quals1, quals2;

  /* Save time if the two types are the same.  */

  എങ്കിൽ (t1 == t2) തിരികെ t1;

  /* If one type is nonsense, use the other.  */
  എങ്കിൽ (t1 == error_mark_കണ്ണി)
    തിരികെ t2;
  എങ്കിൽ (t2 == error_mark_കണ്ണി)
    തിരികെ t1;

  gcc_assert (വൃക്ഷം_CODE (t1) == POINTER_TYPE
	      && വൃക്ഷം_CODE (t2) == POINTER_TYPE);

  /* Merge the attributes.  */
  attributes = targetm.merge_type_attributes (t1, t2);

  /* Find the composite type of the target types, and combine the
     qualifiers of the two types' targets.  */
  വൃക്ഷം pointed_to_1 = വൃക്ഷം_TYPE (t1);
  വൃക്ഷം pointed_to_2 = വൃക്ഷം_TYPE (t2);
  വൃക്ഷം target = composite_type_cond (TYPE_MAIN_VARIANT (pointed_to_1),
				     TYPE_MAIN_VARIANT (pointed_to_2), cond);

  /* Strip array types to get correct qualifier for pointers to arrays */
  quals1 = TYPE_QUALS_NO_ADDR_SPACE (strip_array_types (pointed_to_1));
  quals2 = TYPE_QUALS_NO_ADDR_SPACE (strip_array_types (pointed_to_2));

  /* For function types do not merge const qualifiers, but drop them
     if used inconsistently.  The middle-end uses these to mark const
     and noreturn functions.  */
  എങ്കിൽ (വൃക്ഷം_CODE (pointed_to_1) == FUNCTION_TYPE)
    target_quals = (quals1 & quals2);
  അല്ലെങ്കിൽ
    target_quals = (quals1 | quals2);

  /* If the two named address spaces are different, determine the common
     superset address space.  This is guaranteed to exist due to the
     assumption that comp_target_type returned true.  */
  as1 = TYPE_ADDR_SPACE (pointed_to_1);
  as2 = TYPE_ADDR_SPACE (pointed_to_2);
  എങ്കിൽ (!addr_space_superset (as1, as2, &as_common))
    gcc_unreachable ();

  target_quals |= ENCODE_QUAL_ADDR_SPACE (as_common);

  t1 = c_build_pointer_type (c_build_qualified_type (target, target_quals));
  തിരികെ c_build_type_attribute_variant (t1, attributes);
}

/* Return the common type for two arithmetic types under the usual
   arithmetic conversions.  The default conversions have already been
   applied, and enumerated types converted to their compatible integer
   types.  The resulting type is unqualified and has no attributes.

   This is the type for the result of most arithmetic operations
   if the operands have the given two types.  */

സ്ഥിതം വൃക്ഷം
c_common_type (വൃക്ഷം t1, വൃക്ഷം t2)
{
  എണ്ണൽ വൃക്ഷം_code code1;
  എണ്ണൽ വൃക്ഷം_code code2;

  /* If one type is nonsense, use the other.  */
  എങ്കിൽ (t1 == error_mark_കണ്ണി)
    തിരികെ t2;
  എങ്കിൽ (t2 == error_mark_കണ്ണി)
    തിരികെ t1;

  എങ്കിൽ (TYPE_QUALS (t1) != TYPE_UNQUALIFIED)
    t1 = TYPE_MAIN_VARIANT (t1);

  എങ്കിൽ (TYPE_QUALS (t2) != TYPE_UNQUALIFIED)
    t2 = TYPE_MAIN_VARIANT (t2);

  എങ്കിൽ (TYPE_ATTRIBUTES (t1) != NULL_വൃക്ഷം)
    {
      വൃക്ഷം attrs = affects_type_identity_attributes (TYPE_ATTRIBUTES (t1));
      t1 = c_build_type_attribute_variant (t1, attrs);
    }

  എങ്കിൽ (TYPE_ATTRIBUTES (t2) != NULL_വൃക്ഷം)
    {
      വൃക്ഷം attrs = affects_type_identity_attributes (TYPE_ATTRIBUTES (t2));
      t2 = c_build_type_attribute_variant (t2, attrs);
    }

  /* Save time if the two types are the same.  */

  എങ്കിൽ (t1 == t2) തിരികെ t1;

  code1 = വൃക്ഷം_CODE (t1);
  code2 = വൃക്ഷം_CODE (t2);

  gcc_assert (code1 == VECTOR_TYPE || code1 == COMPLEX_TYPE
	      || code1 == FIXED_POINT_TYPE || code1 == REAL_TYPE
	      || code1 == INTEGER_TYPE || code1 == BITINT_TYPE);
  gcc_assert (code2 == VECTOR_TYPE || code2 == COMPLEX_TYPE
	      || code2 == FIXED_POINT_TYPE || code2 == REAL_TYPE
	      || code2 == INTEGER_TYPE || code2 == BITINT_TYPE);

  /* When one operand is a decimal float type, the other operand cannot be
     a generic float type or a complex type.  We also disallow vector types
     here.  */
  എങ്കിൽ ((DECIMAL_FLOAT_TYPE_P (t1) || DECIMAL_FLOAT_TYPE_P (t2))
      && !(DECIMAL_FLOAT_TYPE_P (t1) && DECIMAL_FLOAT_TYPE_P (t2)))
    {
      എങ്കിൽ (code1 == VECTOR_TYPE || code2 == VECTOR_TYPE)
	{
	  error ("cannot mix operands of decimal floating and vector types");
	  തിരികെ error_mark_കണ്ണി;
	}
      എങ്കിൽ (code1 == COMPLEX_TYPE || code2 == COMPLEX_TYPE)
	{
	  error ("cannot mix operands of decimal floating and complex types");
	  തിരികെ error_mark_കണ്ണി;
	}
      എങ്കിൽ (code1 == REAL_TYPE && code2 == REAL_TYPE)
	{
	  error ("cannot mix operands of decimal floating "
		 "and other floating types");
	  തിരികെ error_mark_കണ്ണി;
	}
    }

  /* If one type is a vector type, return that type.  (How the usual
     arithmetic conversions apply to the vector types extension is not
     precisely specified.)  */
  എങ്കിൽ (code1 == VECTOR_TYPE)
    തിരികെ t1;

  എങ്കിൽ (code2 == VECTOR_TYPE)
    തിരികെ t2;

  /* If one type is complex, form the common type of the non-complex
     components, then make that complex.  Use T1 or T2 if it is the
     required type.  */
  എങ്കിൽ (code1 == COMPLEX_TYPE || code2 == COMPLEX_TYPE)
    {
      വൃക്ഷം subtype1 = code1 == COMPLEX_TYPE ? വൃക്ഷം_TYPE (t1) : t1;
      വൃക്ഷം subtype2 = code2 == COMPLEX_TYPE ? വൃക്ഷം_TYPE (t2) : t2;
      വൃക്ഷം subtype = c_common_type (subtype1, subtype2);

      എങ്കിൽ (code1 == COMPLEX_TYPE && വൃക്ഷം_TYPE (t1) == subtype)
	തിരികെ t1;
      അല്ലെങ്കിൽ എങ്കിൽ (code2 == COMPLEX_TYPE && വൃക്ഷം_TYPE (t2) == subtype)
	തിരികെ t2;
      അല്ലെങ്കിൽ എങ്കിൽ (വൃക്ഷം_CODE (subtype) == BITINT_TYPE)
	{
	  sorry ("%<_Complex _BitInt(%d)%> unsupported",
		 TYPE_PRECISION (subtype));
	  തിരികെ code1 == COMPLEX_TYPE ? t1 : t2;
	}
      അല്ലെങ്കിൽ
	തിരികെ build_complex_type (subtype);
    }

  /* If only one is real, use it as the result.  */

  എങ്കിൽ (code1 == REAL_TYPE && code2 != REAL_TYPE)
    തിരികെ t1;

  എങ്കിൽ (code2 == REAL_TYPE && code1 != REAL_TYPE)
    തിരികെ t2;

  /* If both are real and either are decimal floating point types, use
     the decimal floating point type with the greater precision. */

  എങ്കിൽ (code1 == REAL_TYPE && code2 == REAL_TYPE)
    {
      എങ്കിൽ (TYPE_MAIN_VARIANT (t1) == dfloat128_type_കണ്ണി
	  || TYPE_MAIN_VARIANT (t2) == dfloat128_type_കണ്ണി)
	തിരികെ dfloat128_type_കണ്ണി;
      /* And prefer _Decimal128 over _Decimal64x which has in GCC's
	 implementation the same mode.  */
      അല്ലെങ്കിൽ എങ്കിൽ (TYPE_MAIN_VARIANT (t1) == dfloat64x_type_കണ്ണി
	       || TYPE_MAIN_VARIANT (t2) == dfloat64x_type_കണ്ണി)
	തിരികെ dfloat64x_type_കണ്ണി;
      അല്ലെങ്കിൽ എങ്കിൽ (TYPE_MAIN_VARIANT (t1) == dfloat64_type_കണ്ണി
	       || TYPE_MAIN_VARIANT (t2) == dfloat64_type_കണ്ണി)
	തിരികെ dfloat64_type_കണ്ണി;
      അല്ലെങ്കിൽ എങ്കിൽ (TYPE_MAIN_VARIANT (t1) == dfloat32_type_കണ്ണി
	       || TYPE_MAIN_VARIANT (t2) == dfloat32_type_കണ്ണി)
	തിരികെ dfloat32_type_കണ്ണി;
    }

  /* Deal with fixed-point types.  */
  എങ്കിൽ (code1 == FIXED_POINT_TYPE || code2 == FIXED_POINT_TYPE)
    {
      unsigned പൂർണ്ണസംഖ്യ unsignedp = 0, satp = 0;
      scalar_mode m1, m2;
      unsigned പൂർണ്ണസംഖ്യ fbit1, ibit1, fbit2, ibit2, max_fbit, max_ibit;

      m1 = SCALAR_TYPE_MODE (t1);
      m2 = SCALAR_TYPE_MODE (t2);

      /* If one input type is saturating, the result type is saturating.  */
      എങ്കിൽ (TYPE_SATURATING (t1) || TYPE_SATURATING (t2))
	satp = 1;

      /* If both fixed-point types are unsigned, the result type is unsigned.
	 When mixing fixed-point and integer types, follow the sign of the
	 fixed-point type.
	 Otherwise, the result type is signed.  */
      എങ്കിൽ ((TYPE_UNSIGNED (t1) && TYPE_UNSIGNED (t2)
	   && code1 == FIXED_POINT_TYPE && code2 == FIXED_POINT_TYPE)
	  || (code1 == FIXED_POINT_TYPE && code2 != FIXED_POINT_TYPE
	      && TYPE_UNSIGNED (t1))
	  || (code1 != FIXED_POINT_TYPE && code2 == FIXED_POINT_TYPE
	      && TYPE_UNSIGNED (t2)))
	unsignedp = 1;

      /* The result type is signed.  */
      എങ്കിൽ (unsignedp == 0)
	{
	  /* If the input type is unsigned, we need to convert to the
	     signed type.  */
	  എങ്കിൽ (code1 == FIXED_POINT_TYPE && TYPE_UNSIGNED (t1))
	    {
	      എണ്ണൽ mode_class mclass = (എണ്ണൽ mode_class) 0;
	      എങ്കിൽ (GET_MODE_CLASS (m1) == MODE_UFRACT)
		mclass = MODE_FRACT;
	      അല്ലെങ്കിൽ എങ്കിൽ (GET_MODE_CLASS (m1) == MODE_UACCUM)
		mclass = MODE_ACCUM;
	      അല്ലെങ്കിൽ
		gcc_unreachable ();
	      m1 = as_a <scalar_mode>
		(mode_for_size (GET_MODE_PRECISION (m1), mclass, 0));
	    }
	  എങ്കിൽ (code2 == FIXED_POINT_TYPE && TYPE_UNSIGNED (t2))
	    {
	      എണ്ണൽ mode_class mclass = (എണ്ണൽ mode_class) 0;
	      എങ്കിൽ (GET_MODE_CLASS (m2) == MODE_UFRACT)
		mclass = MODE_FRACT;
	      അല്ലെങ്കിൽ എങ്കിൽ (GET_MODE_CLASS (m2) == MODE_UACCUM)
		mclass = MODE_ACCUM;
	      അല്ലെങ്കിൽ
		gcc_unreachable ();
	      m2 = as_a <scalar_mode>
		(mode_for_size (GET_MODE_PRECISION (m2), mclass, 0));
	    }
	}

      എങ്കിൽ (code1 == FIXED_POINT_TYPE)
	{
	  fbit1 = GET_MODE_FBIT (m1);
	  ibit1 = GET_MODE_IBIT (m1);
	}
      അല്ലെങ്കിൽ
	{
	  fbit1 = 0;
	  /* Signed integers need to subtract one sign bit.  */
	  ibit1 = TYPE_PRECISION (t1) - (!TYPE_UNSIGNED (t1));
	}

      എങ്കിൽ (code2 == FIXED_POINT_TYPE)
	{
	  fbit2 = GET_MODE_FBIT (m2);
	  ibit2 = GET_MODE_IBIT (m2);
	}
      അല്ലെങ്കിൽ
	{
	  fbit2 = 0;
	  /* Signed integers need to subtract one sign bit.  */
	  ibit2 = TYPE_PRECISION (t2) - (!TYPE_UNSIGNED (t2));
	}

      max_ibit = ibit1 >= ibit2 ?  ibit1 : ibit2;
      max_fbit = fbit1 >= fbit2 ?  fbit1 : fbit2;
      തിരികെ c_common_fixed_point_type_for_size (max_ibit, max_fbit, unsignedp,
						 satp);
    }

  /* Both real or both integers; use the one with greater precision.  */

  എങ്കിൽ (TYPE_PRECISION (t1) > TYPE_PRECISION (t2))
    തിരികെ t1;
  അല്ലെങ്കിൽ എങ്കിൽ (TYPE_PRECISION (t2) > TYPE_PRECISION (t1))
    തിരികെ t2;

  /* Same precision.  Prefer long longs to longs to ints when the
     same precision, following the C99 rules on integer type rank
     (which are equivalent to the C90 rules for C90 types).  */

  എങ്കിൽ (TYPE_MAIN_VARIANT (t1) == long_long_unsigned_type_കണ്ണി
      || TYPE_MAIN_VARIANT (t2) == long_long_unsigned_type_കണ്ണി)
    തിരികെ long_long_unsigned_type_കണ്ണി;

  എങ്കിൽ (TYPE_MAIN_VARIANT (t1) == long_long_integer_type_കണ്ണി
      || TYPE_MAIN_VARIANT (t2) == long_long_integer_type_കണ്ണി)
    {
      എങ്കിൽ (TYPE_UNSIGNED (t1) || TYPE_UNSIGNED (t2))
	തിരികെ long_long_unsigned_type_കണ്ണി;
      അല്ലെങ്കിൽ
	തിരികെ long_long_integer_type_കണ്ണി;
    }

  എങ്കിൽ (TYPE_MAIN_VARIANT (t1) == long_unsigned_type_കണ്ണി
      || TYPE_MAIN_VARIANT (t2) == long_unsigned_type_കണ്ണി)
    തിരികെ long_unsigned_type_കണ്ണി;

  എങ്കിൽ (TYPE_MAIN_VARIANT (t1) == long_integer_type_കണ്ണി
      || TYPE_MAIN_VARIANT (t2) == long_integer_type_കണ്ണി)
    {
      /* But preserve unsignedness from the other type,
	 since long cannot hold all the values of an unsigned int.  */
      എങ്കിൽ (TYPE_UNSIGNED (t1) || TYPE_UNSIGNED (t2))
	തിരികെ long_unsigned_type_കണ്ണി;
      അല്ലെങ്കിൽ
	തിരികെ long_integer_type_കണ്ണി;
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
  വൃക്ഷം mv1 = TYPE_MAIN_VARIANT (t1);
  വൃക്ഷം mv2 = TYPE_MAIN_VARIANT (t2);

  വേണ്ടി (പൂർണ്ണസംഖ്യ i = അക്കം_FLOATN_TYPES - 1; i >= 0; i--)
    എങ്കിൽ (mv1 == FLOATN_TYPE_കണ്ണി (i) || mv2 == FLOATN_TYPE_കണ്ണി (i))
      തിരികെ FLOATN_TYPE_കണ്ണി (i);

  /* Likewise, prefer long double to double even if same size.  */
  എങ്കിൽ (mv1 == long_double_type_കണ്ണി || mv2 == long_double_type_കണ്ണി)
    തിരികെ long_double_type_കണ്ണി;

  /* Likewise, prefer double to float even if same size.
     We got a couple of embedded targets with 32 bit doubles, and the
     pdp11 might have 64 bit floats.  */
  എങ്കിൽ (mv1 == double_type_കണ്ണി || mv2 == double_type_കണ്ണി)
    തിരികെ double_type_കണ്ണി;

  എങ്കിൽ (mv1 == float_type_കണ്ണി || mv2 == float_type_കണ്ണി)
    തിരികെ float_type_കണ്ണി;

  വേണ്ടി (പൂർണ്ണസംഖ്യ i = അക്കം_FLOATNX_TYPES - 1; i >= 0; i--)
    എങ്കിൽ (mv1 == FLOATNX_TYPE_കണ്ണി (i) || mv2 == FLOATNX_TYPE_കണ്ണി (i))
      തിരികെ FLOATNX_TYPE_കണ്ണി (i);

  എങ്കിൽ ((code1 == BITINT_TYPE || code2 == BITINT_TYPE) && code1 != code2)
    {
      /* Prefer any other integral types over bit-precise integer types.  */
      എങ്കിൽ (TYPE_UNSIGNED (t1) == TYPE_UNSIGNED (t2))
	തിരികെ code1 == BITINT_TYPE ? t2 : t1;
      /* If BITINT_TYPE is unsigned and the other type is signed
	 non-BITINT_TYPE with the same precision, the latter has higher rank.
	 In that case:
	 Otherwise, both operands are converted to the unsigned integer type
	 corresponding to the type of the operand with signed integer type.  */
      എങ്കിൽ (TYPE_UNSIGNED (code1 == BITINT_TYPE ? t1 : t2))
	തിരികെ c_common_unsigned_type (code1 == BITINT_TYPE ? t2 : t1);
    }

  /* Otherwise prefer the unsigned one.  */

  എങ്കിൽ (TYPE_UNSIGNED (t1))
    തിരികെ t1;
  അല്ലെങ്കിൽ
    തിരികെ t2;
}

/* Wrapper around c_common_type that is used by c-common.cc and other
   front end optimizations that remove promotions.  ENUMERAL_TYPEs
   are allowed here and are converted to their compatible integer types.
   BOOLEAN_TYPEs are allowed here and return either boolean_type_node or
   preferably a non-Boolean type as the common type.  */
വൃക്ഷം
common_type (വൃക്ഷം t1, വൃക്ഷം t2)
{
  എങ്കിൽ (വൃക്ഷം_CODE (t1) == ENUMERAL_TYPE)
    t1 = ENUM_UNDERLYING_TYPE (t1);
  എങ്കിൽ (വൃക്ഷം_CODE (t2) == ENUMERAL_TYPE)
    t2 = ENUM_UNDERLYING_TYPE (t2);

  /* If both types are BOOLEAN_TYPE, then return boolean_type_node.  */
  എങ്കിൽ (വൃക്ഷം_CODE (t1) == BOOLEAN_TYPE
      && വൃക്ഷം_CODE (t2) == BOOLEAN_TYPE)
    തിരികെ boolean_type_കണ്ണി;

  /* If either type is BOOLEAN_TYPE, then return the other.  */
  എങ്കിൽ (വൃക്ഷം_CODE (t1) == BOOLEAN_TYPE)
    തിരികെ t2;
  എങ്കിൽ (വൃക്ഷം_CODE (t2) == BOOLEAN_TYPE)
    തിരികെ t1;

  തിരികെ c_common_type (t1, t2);
}



/* Helper function for comptypes.  For two compatible types, return 1
   if they pass consistency checks.  In particular we test that
   TYPE_CANONICAL is set correctly, i.e. the two types can alias.  */

സ്ഥിതം തർക്കം
comptypes_verify (വൃക്ഷം type1, വൃക്ഷം type2)
{
  എങ്കിൽ (type1 == type2 || !type1 || !type2
      || വൃക്ഷം_CODE (type1) == ERROR_MARK || വൃക്ഷം_CODE (type2) == ERROR_MARK)
    തിരികെ സത്യം;

  gcc_checking_assert (c_verify_type (type1));
  gcc_checking_assert (c_verify_type (type2));

  എങ്കിൽ (TYPE_CANONICAL (type1) != TYPE_CANONICAL (type2)
      && !TYPE_STRUCTURAL_EQUALITY_P (type1)
      && !TYPE_STRUCTURAL_EQUALITY_P (type2))
    {
      /* FIXME: check other types. */
      എങ്കിൽ (RECORD_OR_UNION_TYPE_P (type1)
	  || വൃക്ഷം_CODE (type1) == ENUMERAL_TYPE
	  || വൃക്ഷം_CODE (type2) == ENUMERAL_TYPE)
	തിരികെ അസത്യം;
    }
  തിരികെ സത്യം;
}

ഘടന comptypes_data {

  /* output */
  തർക്കം enum_and_int_p;
  തർക്കം different_types_p;
  തർക്കം warning_needed;

  /* context */
  തർക്കം anon_field;
  തർക്കം pointedto;

  /* configuration */
  തർക്കം equiv;
  തർക്കം ignore_promoting_args;

  സ്ഥിരം ഘടന tagged_tu_seen_cache* cache;
};


/* Helper function for composite_type.  This function ignores when the
   function type of an old-style declaration is incompatible with a type
   of a declaration with prototype because some are arguments are not
   self-promoting.  This is ignored only for function types but not
   ignored in a nested context.  */

സ്ഥിതം തർക്കം
comptypes_check_for_composite (വൃക്ഷം t1, വൃക്ഷം t2)
{
  ഘടന comptypes_data data = { };
  data.ignore_promoting_args = FUNCTION_TYPE == വൃക്ഷം_CODE (t1);
  തിരികെ comptypes_internal (t1, t2, &data);
}


/* C implementation of compatible_types_for_indirection_note_p.  */

തർക്കം
compatible_types_for_indirection_note_p (വൃക്ഷം type1, വൃക്ഷം type2)
{
  തിരികെ comptypes (type1, type2);
}

/* Return true if TYPE1 and TYPE2 are compatible types for assignment
   or various other operations.  */

തർക്കം
comptypes (വൃക്ഷം type1, വൃക്ഷം type2)
{
  ഘടന comptypes_data data = { };
  തർക്കം ret = comptypes_internal (type1, type2, &data);

  gcc_checking_assert (!ret || comptypes_verify (type1, type2));

  തിരികെ ret;
}


/* Like comptypes, but it returns non-zero only for identical
   types.  */

തർക്കം
comptypes_same_p (വൃക്ഷം type1, വൃക്ഷം type2)
{
  ഘടന comptypes_data data = { };
  തർക്കം ret = comptypes_internal (type1, type2, &data);

  gcc_checking_assert (!ret || comptypes_verify (type1, type2));

  എങ്കിൽ (data.different_types_p)
    തിരികെ അസത്യം;

  തിരികെ ret;
}


/* Like comptypes, but if it returns true because enum and int are
   compatible, it sets *ENUM_AND_INT_P to true.  */

തർക്കം
comptypes_check_enum_int (വൃക്ഷം type1, വൃക്ഷം type2, തർക്കം *enum_and_int_p)
{
  ഘടന comptypes_data data = { };
  തർക്കം ret = comptypes_internal (type1, type2, &data);
  *enum_and_int_p = data.enum_and_int_p;

  gcc_checking_assert (!ret || comptypes_verify (type1, type2));

  തിരികെ ret;
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

തർക്കം
comptypes_equiv_p (വൃക്ഷം type1, വൃക്ഷം type2)
{
  ഘടന comptypes_data data = { };
  data.equiv = സത്യം;
  തർക്കം ret = comptypes_internal (type1, type2, &data);

  /* check that different equivance classes are assigned only
     to types that are not compatible.  */
  gcc_checking_assert (ret || !comptypes (type1, type2));

  തിരികെ ret;
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

സ്ഥിതം തർക്കം
comptypes_internal (const_വൃക്ഷം type1, const_വൃക്ഷം type2,
		    ഘടന comptypes_data *data)
{
  const_വൃക്ഷം t1 = type1;
  const_വൃക്ഷം t2 = type2;

  /* Suppress errors caused by previously reported errors.  */

  എങ്കിൽ (t1 == t2 || !t1 || !t2
      || വൃക്ഷം_CODE (t1) == ERROR_MARK || വൃക്ഷം_CODE (t2) == ERROR_MARK)
    തിരികെ സത്യം;

  /* Qualifiers must match. C99 6.7.3p9 */

  എങ്കിൽ (TYPE_QUALS (t1) != TYPE_QUALS (t2))
    തിരികെ അസത്യം;

  /* Enumerated types are compatible with integer types, but this is
     not transitive: two enumerated types in the same translation unit
     are compatible with each other only if they are the same type.  */

  എങ്കിൽ (വൃക്ഷം_CODE (t1) == ENUMERAL_TYPE
      && COMPLETE_TYPE_P (t1)
      && വൃക്ഷം_CODE (t2) != ENUMERAL_TYPE)
    {
      t1 = ENUM_UNDERLYING_TYPE (t1);
      എങ്കിൽ (വൃക്ഷം_CODE (t2) != VOID_TYPE)
	{
	  data->enum_and_int_p = സത്യം;
	  data->different_types_p = സത്യം;
	}
    }
  അല്ലെങ്കിൽ എങ്കിൽ (വൃക്ഷം_CODE (t2) == ENUMERAL_TYPE
	   && COMPLETE_TYPE_P (t2)
	   && വൃക്ഷം_CODE (t1) != ENUMERAL_TYPE)
    {
      t2 = ENUM_UNDERLYING_TYPE (t2);
      എങ്കിൽ (വൃക്ഷം_CODE (t1) != VOID_TYPE)
	{
	  data->enum_and_int_p = സത്യം;
	  data->different_types_p = സത്യം;
	}
    }

  എങ്കിൽ (t1 == t2)
    തിരികെ സത്യം;

  /* Different classes of types can't be compatible.  */

  എങ്കിൽ (വൃക്ഷം_CODE (t1) != വൃക്ഷം_CODE (t2))
    തിരികെ അസത്യം;

  /* Allow for two different type nodes which have essentially the same
     definition.  Note that we already checked for equality of the type
     qualifiers (just above).  */

  എങ്കിൽ (വൃക്ഷം_CODE (t1) != ARRAY_TYPE
      && TYPE_MAIN_VARIANT (t1) == TYPE_MAIN_VARIANT (t2))
    തിരികെ സത്യം;

  പൂർണ്ണസംഖ്യ attrval;

  /* 1 if no need for warning yet, 2 if warning cause has been seen.  */
  എങ്കിൽ (!(attrval = comp_type_attributes (t1, t2)))
    തിരികെ അസത്യം;

  എങ്കിൽ (2 == attrval)
    data->warning_needed = സത്യം;

  തിരഞ്ഞെടുപ്പ് (വൃക്ഷം_CODE (t1))
    {
    അവസ്ഥ INTEGER_TYPE:
    അവസ്ഥ FIXED_POINT_TYPE:
    അവസ്ഥ REAL_TYPE:
    അവസ്ഥ BITINT_TYPE:
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
      തിരികെ TYPE_CANONICAL (t1) == TYPE_CANONICAL (t2);

    അവസ്ഥ POINTER_TYPE:
      /* Do not remove mode information.  */
      എങ്കിൽ (TYPE_MODE (t1) != TYPE_MODE (t2))
	തിരികെ അസത്യം;
      data->pointedto = സത്യം;
      തിരികെ comptypes_internal (വൃക്ഷം_TYPE (t1), വൃക്ഷം_TYPE (t2), data);

    അവസ്ഥ FUNCTION_TYPE:
      തിരികെ function_types_compatible_p (t1, t2, data);

    അവസ്ഥ ARRAY_TYPE:
      {
	വൃക്ഷം d1 = TYPE_DOMAIN (t1);
	വൃക്ഷം d2 = TYPE_DOMAIN (t2);

	/* Target types must match incl. qualifiers.  */
	എങ്കിൽ (!comptypes_internal (വൃക്ഷം_TYPE (t1), വൃക്ഷം_TYPE (t2), data))
	  തിരികെ അസത്യം;

	എങ്കിൽ ((d1 == NULL_വൃക്ഷം) != (d2 == NULL_വൃക്ഷം))
	  data->different_types_p = സത്യം;
	/* Ignore size mismatches when forming equivalence classes.  */
	എങ്കിൽ (data->equiv)
	  തിരികെ സത്യം;
	/* Sizes must match unless one is missing or variable.  */
	എങ്കിൽ (d1 == NULL_വൃക്ഷം || d2 == NULL_വൃക്ഷം || d1 == d2)
	  തിരികെ സത്യം;

	തർക്കം d1_variable = മുകൾ_array_vla_p (t1);
	തർക്കം d2_variable = മുകൾ_array_vla_p (t2);

	എങ്കിൽ (d1_variable != d2_variable)
	  data->different_types_p = സത്യം;
	എങ്കിൽ (d1_variable || d2_variable)
	  തിരികെ സത്യം;

	തർക്കം d1_zero = zero_length_array_type_p (t1)
		       || flexible_array_member_type_p (t1);

	തർക്കം d2_zero = zero_length_array_type_p (t2)
		       || flexible_array_member_type_p (t2);

	എങ്കിൽ (d1_zero && d2_zero)
	  തിരികെ സത്യം;
	എങ്കിൽ (d1_zero || d2_zero)
	  തിരികെ അസത്യം;

	എങ്കിൽ (!വൃക്ഷം_int_cst_equal (TYPE_MIN_മൂല്യം (d1), TYPE_MIN_മൂല്യം (d2))
	    || !വൃക്ഷം_int_cst_equal (TYPE_MAX_മൂല്യം (d1), TYPE_MAX_മൂല്യം (d2)))
	  തിരികെ അസത്യം;

	തിരികെ സത്യം;
      }

    അവസ്ഥ ENUMERAL_TYPE:
    അവസ്ഥ RECORD_TYPE:
    അവസ്ഥ UNION_TYPE:

      എങ്കിൽ (!flag_isoc23)
	തിരികെ അസത്യം;

      തിരികെ tagged_types_tu_compatible_p (t1, t2, data);

    അവസ്ഥ VECTOR_TYPE:
      തിരികെ known_eq (TYPE_VECTOR_SUBPARTS (t1), TYPE_VECTOR_SUBPARTS (t2))
	     && comptypes_internal (വൃക്ഷം_TYPE (t1), വൃക്ഷം_TYPE (t2), data);

    സ്ഥിരസ്ഥിതി:
      തിരികെ അസത്യം;
    }
  gcc_unreachable ();
}

/* Return true if TTL and TTR are pointers to types that are equivalent, ignoring
   their qualifiers, except for named address spaces.  If the pointers point to
   different named addresses, then we must determine if one address space is a
   subset of the other.  */

സ്ഥിതം തർക്കം
comp_target_types (location_t location, വൃക്ഷം ttl, വൃക്ഷം ttr)
{
  വൃക്ഷം mvl = വൃക്ഷം_TYPE (ttl);
  വൃക്ഷം mvr = വൃക്ഷം_TYPE (ttr);
  addr_space_t asl = TYPE_ADDR_SPACE (mvl);
  addr_space_t asr = TYPE_ADDR_SPACE (mvr);
  addr_space_t as_common;

  /* Fail if pointers point to incompatible address spaces.  */
  എങ്കിൽ (!addr_space_superset (asl, asr, &as_common))
    തിരികെ 0;

  /* Qualifiers on element types of array types that are
     pointer targets are also removed.  */
  ഘടന comptypes_data data = { };
  എങ്കിൽ (!comptypes_internal (remove_qualifiers (mvl),
			   remove_qualifiers (mvr), &data))
    തിരികെ അസത്യം;

  /* For pedantic use comptypes on arrays before removing
     qualifiers on the element type. */
  എങ്കിൽ (വൃക്ഷം_CODE (mvl) == ARRAY_TYPE
      && വൃക്ഷം_CODE (mvr) == ARRAY_TYPE
      && !comptypes (mvl, mvr))
    pedwarn_c11 (location, OPT_Wpedantic, "invalid use of pointers to arrays "
					  "with different qualifiers in ISO C "
					  "before C23");

  എങ്കിൽ (data.warning_needed)
    pedwarn (location, OPT_Wpedantic, "types are not quite compatible");

  എങ്കിൽ (data.enum_and_int_p && warn_cxx_compat)
    warning_at (location, OPT_Wc___compat,
		"pointer target types incompatible in C++");

  തിരികെ സത്യം;
}

/* Subroutines of `comptypes'.  */

/* Return true if two 'struct', 'union', or 'enum' types T1 and T2 are
   compatible.  The two types are not the same (which has been
   checked earlier in comptypes_internal).  */

സ്ഥിതം തർക്കം
tagged_types_tu_compatible_p (const_വൃക്ഷം t1, const_വൃക്ഷം t2,
			      ഘടന comptypes_data *data)
{
  വൃക്ഷം s1, s2;

  എങ്കിൽ (c_type_tag (t1) != c_type_tag (t2))
    തിരികെ അസത്യം;

  /* When forming equivalence classes for TYPE_CANONICAL in C23, we treat
     structs with the same tag as equivalent, but only when they are targets
     of pointers inside other structs.  */
  എങ്കിൽ (data->equiv && data->pointedto && NULL_വൃക്ഷം != c_type_tag (t1))
    തിരികെ സത്യം;

  /* Different types without tag are incompatible except as an anonymous
     field or when forming equivalence classes for TYPE_CANONICAL.  */
  എങ്കിൽ (!data->anon_field && !data->equiv && NULL_വൃക്ഷം == c_type_tag (t1))
    തിരികെ അസത്യം;

  എങ്കിൽ (!data->anon_field && TYPE_STUB_DECL (t1) != TYPE_STUB_DECL (t2))
    data->different_types_p = സത്യം;

  /* Incomplete types are incompatible inside a TU.  */
  എങ്കിൽ (TYPE_SIZE (t1) == ശൂന്യ || TYPE_SIZE (t2) == ശൂന്യ)
    തിരികെ അസത്യം;

  എങ്കിൽ (ENUMERAL_TYPE != വൃക്ഷം_CODE (t1)
      && (TYPE_REVERSE_STORAGE_ORDER (t1)
	  != TYPE_REVERSE_STORAGE_ORDER (t2)))
    തിരികെ അസത്യം;

  എങ്കിൽ (TYPE_USER_ALIGN (t1) != TYPE_USER_ALIGN (t2))
    data->different_types_p = സത്യം;

  /* For types already being looked at in some active
     invocation of this function, assume compatibility.
     The cache is built as a linked list on the stack
     with the head of the list passed downwards.  */
  വേണ്ടി (സ്ഥിരം ഘടന tagged_tu_seen_cache *t = data->cache;
       t != ശൂന്യ; t = t->next)
    എങ്കിൽ (t->t1 == t1 && t->t2 == t2)
      തിരികെ സത്യം;

  സ്ഥിരം ഘടന tagged_tu_seen_cache entry = { data->cache, t1, t2 };

  തിരഞ്ഞെടുപ്പ് (വൃക്ഷം_CODE (t1))
    {
    അവസ്ഥ ENUMERAL_TYPE:
      {
	എങ്കിൽ (!comptypes (ENUM_UNDERLYING_TYPE (t1), ENUM_UNDERLYING_TYPE (t2)))
	  തിരികെ അസത്യം;

	/* Speed up the case where the type values are in the same order.  */
	വൃക്ഷം tv1 = TYPE_മൂല്യങ്ങൾ (t1);
	വൃക്ഷം tv2 = TYPE_മൂല്യങ്ങൾ (t2);

	എങ്കിൽ (tv1 == tv2)
	  തിരികെ സത്യം;

	വേണ്ടി (;tv1 && tv2; tv1 = വൃക്ഷം_CHAIN (tv1), tv2 = വൃക്ഷം_CHAIN (tv2))
	  {
	    എങ്കിൽ (വൃക്ഷം_PURPOSE (tv1) != വൃക്ഷം_PURPOSE (tv2))
	      നിർത്തുക;

	    എങ്കിൽ (simple_cst_equal (DECL_INITIAL (വൃക്ഷം_മൂല്യം (tv1)),
				  DECL_INITIAL (വൃക്ഷം_മൂല്യം (tv2))) != 1)
	      നിർത്തുക;
	  }

	എങ്കിൽ (tv1 == NULL_വൃക്ഷം && tv2 == NULL_വൃക്ഷം)
	  തിരികെ സത്യം;

	എങ്കിൽ (tv1 == NULL_വൃക്ഷം || tv2 == NULL_വൃക്ഷം)
	  തിരികെ അസത്യം;

	എങ്കിൽ (list_length (TYPE_മൂല്യങ്ങൾ (t1)) != list_length (TYPE_മൂല്യങ്ങൾ (t2)))
	  തിരികെ അസത്യം;

	വേണ്ടി (s1 = TYPE_മൂല്യങ്ങൾ (t1); s1; s1 = വൃക്ഷം_CHAIN (s1))
	  {
	    s2 = purpose_member (വൃക്ഷം_PURPOSE (s1), TYPE_മൂല്യങ്ങൾ (t2));

	    എങ്കിൽ (s2 == ശൂന്യ
		|| simple_cst_equal (DECL_INITIAL (വൃക്ഷം_മൂല്യം (s1)),
				     DECL_INITIAL (വൃക്ഷം_മൂല്യം (s2))) != 1)
	      തിരികെ അസത്യം;
	  }

	തിരികെ സത്യം;
      }

    അവസ്ഥ UNION_TYPE:
    അവസ്ഥ RECORD_TYPE:

	എങ്കിൽ (list_length (TYPE_FIELDS (t1)) != list_length (TYPE_FIELDS (t2)))
	  തിരികെ അസത്യം;

	വേണ്ടി (s1 = TYPE_FIELDS (t1), s2 = TYPE_FIELDS (t2);
	     s1 && s2;
	     s1 = DECL_CHAIN (s1), s2 = DECL_CHAIN (s2))
	  {
	    gcc_assert (വൃക്ഷം_CODE (s1) == FIELD_DECL);
	    gcc_assert (വൃക്ഷം_CODE (s2) == FIELD_DECL);

	    വൃക്ഷം ft1 = വൃക്ഷം_TYPE (s1);
	    വൃക്ഷം ft2 = വൃക്ഷം_TYPE (s2);

	    എങ്കിൽ (DECL_NAME (s1) != DECL_NAME (s2))
	      തിരികെ അസത്യം;

	    എങ്കിൽ (DECL_ALIGN (s1) != DECL_ALIGN (s2))
	      തിരികെ അസത്യം;

	    എങ്കിൽ (DECL_C_BIT_FIELD (s1) != DECL_C_BIT_FIELD (s2))
	       തിരികെ അസത്യം;

	    എങ്കിൽ (DECL_C_BIT_FIELD (s1))
	      {
		എങ്കിൽ (!വൃക്ഷം_int_cst_equal (DECL_SIZE (s1), DECL_SIZE (s2)))
		  തിരികെ അസത്യം;

		ft1 = DECL_BIT_FIELD_TYPE (s1);
		ft2 = DECL_BIT_FIELD_TYPE (s2);
	      }

	    എങ്കിൽ (!ft1 || !ft2)
	      തിരികെ അസത്യം;

	    എങ്കിൽ (വൃക്ഷം_CODE (ft1) == ERROR_MARK || വൃക്ഷം_CODE (ft2) == ERROR_MARK)
	      തിരികെ അസത്യം;

	    data->anon_field = !DECL_NAME (s1);
	    data->pointedto = അസത്യം;

	    സ്ഥിരം ഘടന tagged_tu_seen_cache *cache = data->cache;
	    data->cache = &entry;
	    തർക്കം ret = comptypes_internal (ft1, ft2, data);
	    data->cache = cache;
	    എങ്കിൽ (!ret)
	      തിരികെ അസത്യം;

	    വൃക്ഷം st1 = TYPE_SIZE (വൃക്ഷം_TYPE (s1));
	    വൃക്ഷം st2 = TYPE_SIZE (വൃക്ഷം_TYPE (s2));

	    എങ്കിൽ (data->equiv
		&& st1 && വൃക്ഷം_CODE (st1) == INTEGER_CST
		&& st2 && വൃക്ഷം_CODE (st2) == INTEGER_CST
		&& !വൃക്ഷം_int_cst_equal (st1, st2))
	     തിരികെ അസത്യം;

	    വൃക്ഷം counted_by1 = lookup_attribute ("counted_by",
						 DECL_ATTRIBUTES (s1));
	    വൃക്ഷം counted_by2 = lookup_attribute ("counted_by",
						 DECL_ATTRIBUTES (s2));
	    /* If there is no counted_by attribute for both fields.  */
	    എങ്കിൽ (!counted_by1 && !counted_by2)
	      തുടരുക;

	    /* If only one field has counted_by attribute.  */
	    എങ്കിൽ ((counted_by1 && !counted_by2)
		|| (!counted_by1 && counted_by2))
	      തിരികെ അസത്യം;

	    /* Now both s1 and s2 have counted_by attributes, check
	       whether they are the same.  */

	    വൃക്ഷം counted_by_field1
	      = lookup_field (t1, വൃക്ഷം_മൂല്യം (വൃക്ഷം_മൂല്യം (counted_by1)));
	    വൃക്ഷം counted_by_field2
	      = lookup_field (t2, വൃക്ഷം_മൂല്യം (വൃക്ഷം_മൂല്യം (counted_by2)));

	    gcc_assert (counted_by_field1 && counted_by_field2);

	    ആകുമ്പോൾ (വൃക്ഷം_CHAIN (counted_by_field1))
	      counted_by_field1 = വൃക്ഷം_CHAIN (counted_by_field1);
	    ആകുമ്പോൾ (വൃക്ഷം_CHAIN (counted_by_field2))
	      counted_by_field2 = വൃക്ഷം_CHAIN (counted_by_field2);

	    എങ്കിൽ (DECL_NAME (വൃക്ഷം_മൂല്യം (counted_by_field1))
		!= DECL_NAME (വൃക്ഷം_മൂല്യം (counted_by_field2)))
	      തിരികെ അസത്യം;
	  }
	തിരികെ സത്യം;

    സ്ഥിരസ്ഥിതി:
      gcc_unreachable ();
    }
}

/* Return true if two function types F1 and F2 are compatible.
   If either type specifies no argument types,
   the other must specify a fixed number of self-promoting arg types.
   Otherwise, if one type specifies only the number of arguments,
   the other must specify that number of self-promoting arg types.
   Otherwise, the argument types must match.  */

സ്ഥിതം തർക്കം
function_types_compatible_p (const_വൃക്ഷം f1, const_വൃക്ഷം f2,
			     ഘടന comptypes_data *data)
{
  വൃക്ഷം ret1 = വൃക്ഷം_TYPE (f1);
  വൃക്ഷം ret2 = വൃക്ഷം_TYPE (f2);

  /* 'volatile' qualifiers on a function's return type used to mean
     the function is noreturn.  */
  എങ്കിൽ (TYPE_VOLATILE (ret1) != TYPE_VOLATILE (ret2))
    pedwarn (നിവേശം_location, 0, "function return types not compatible due to %<volatile%>");
  എങ്കിൽ (TYPE_VOLATILE (ret1))
    ret1 = build_qualified_type (TYPE_MAIN_VARIANT (ret1),
				 TYPE_QUALS (ret1) & ~TYPE_QUAL_VOLATILE);
  എങ്കിൽ (TYPE_VOLATILE (ret2))
    ret2 = build_qualified_type (TYPE_MAIN_VARIANT (ret2),
				 TYPE_QUALS (ret2) & ~TYPE_QUAL_VOLATILE);

  തർക്കം ignore_pargs = data->ignore_promoting_args;
  data->ignore_promoting_args = അസത്യം;

  എങ്കിൽ (!comptypes_internal (ret1, ret2, data))
    തിരികെ അസത്യം;

  data->ignore_promoting_args = ignore_pargs;

  വൃക്ഷം args1 = TYPE_ARG_TYPES (f1);
  വൃക്ഷം args2 = TYPE_ARG_TYPES (f2);

  എങ്കിൽ ((args1 == NULL_വൃക്ഷം) != (args2 == NULL_വൃക്ഷം))
    data->different_types_p = സത്യം;

  /* An unspecified parmlist matches any specified parmlist
     whose argument types don't need default promotions.  */

  എങ്കിൽ (args1 == NULL_വൃക്ഷം)
    {
      എങ്കിൽ (TYPE_NO_NAMED_ARGS_STDARG_P (f1) != TYPE_NO_NAMED_ARGS_STDARG_P (f2))
	തിരികെ അസത്യം;
      എങ്കിൽ (!(data->ignore_promoting_args || self_promoting_args_p (args2)))
	തിരികെ അസത്യം;
      data->ignore_promoting_args = അസത്യം;
      /* If one of these types comes from a non-prototype fn definition,
	 compare that with the other type's arglist.
	 If they don't match, ask for a warning (but no error).  */
      എങ്കിൽ (TYPE_ACTUAL_ARG_TYPES (f1)
	  && !type_lists_compatible_p (args2, TYPE_ACTUAL_ARG_TYPES (f1), data))
	 data->warning_needed = സത്യം;
      തിരികെ സത്യം;
    }
  എങ്കിൽ (args2 == NULL_വൃക്ഷം)
    {
      എങ്കിൽ (TYPE_NO_NAMED_ARGS_STDARG_P (f1) != TYPE_NO_NAMED_ARGS_STDARG_P (f2))
	തിരികെ അസത്യം;
      എങ്കിൽ (!(data->ignore_promoting_args || self_promoting_args_p (args1)))
	തിരികെ അസത്യം;
      data->ignore_promoting_args = അസത്യം;
      എങ്കിൽ (TYPE_ACTUAL_ARG_TYPES (f2)
	  && !type_lists_compatible_p (args1, TYPE_ACTUAL_ARG_TYPES (f2), data))
	data->warning_needed = സത്യം;
      തിരികെ സത്യം;
    }

  /* Both types have argument lists: compare them and propagate results.  */
  തിരികെ type_lists_compatible_p (args1, args2, data);
}

/* Check two lists of types for compatibility, returning false for
   incompatible, true for compatible.  */

സ്ഥിതം തർക്കം
type_lists_compatible_p (const_വൃക്ഷം args1, const_വൃക്ഷം args2,
			 ഘടന comptypes_data *data)
{
  ആകുമ്പോൾ (1)
    {
      എങ്കിൽ (args1 == NULL_വൃക്ഷം && args2 == NULL_വൃക്ഷം)
	തിരികെ സത്യം;
      /* If one list is shorter than the other,
	 they fail to match.  */
      എങ്കിൽ (args1 == NULL_വൃക്ഷം || args2 == NULL_വൃക്ഷം)
	തിരികെ അസത്യം;
      വൃക്ഷം a1 = വൃക്ഷം_മൂല്യം (args1);
      വൃക്ഷം a2 = വൃക്ഷം_മൂല്യം (args2);
      വൃക്ഷം mv1 = remove_qualifiers (a1);
      വൃക്ഷം mv2 = remove_qualifiers (a2);

      gcc_assert (mv2);
      gcc_assert (mv2);

      /* If one of the lists has an error marker, ignore this arg.  */
      എങ്കിൽ (വൃക്ഷം_CODE (a1) == ERROR_MARK
	       || വൃക്ഷം_CODE (a2) == ERROR_MARK)
	;
      അല്ലെങ്കിൽ എങ്കിൽ (!comptypes_internal (mv1, mv2, data))
	{
	  data->different_types_p = സത്യം;
	  /* Allow  wait (union {union wait *u; int *i} *)
	     and  wait (union wait *)  to be compatible.  */
	  എങ്കിൽ (വൃക്ഷം_CODE (a1) == UNION_TYPE
	      && (TYPE_NAME (a1) == NULL_വൃക്ഷം
		  || TYPE_TRANSPARENT_AGGR (a1))
	      && വൃക്ഷം_CODE (TYPE_SIZE (a1)) == INTEGER_CST
	      && വൃക്ഷം_int_cst_equal (TYPE_SIZE (a1),
				     TYPE_SIZE (a2)))
	    {
	      വൃക്ഷം memb;
	      വേണ്ടി (memb = TYPE_FIELDS (a1);
		   memb; memb = DECL_CHAIN (memb))
		{
		  വൃക്ഷം mv3 = remove_qualifiers (വൃക്ഷം_TYPE (memb));
		  എങ്കിൽ (comptypes_internal (mv3, mv2, data))
		    നിർത്തുക;
		}
	      എങ്കിൽ (memb == NULL_വൃക്ഷം)
		തിരികെ അസത്യം;
	    }
	  അല്ലെങ്കിൽ എങ്കിൽ (വൃക്ഷം_CODE (a2) == UNION_TYPE
		   && (TYPE_NAME (a2) == NULL_വൃക്ഷം
		       || TYPE_TRANSPARENT_AGGR (a2))
		   && വൃക്ഷം_CODE (TYPE_SIZE (a2)) == INTEGER_CST
		   && വൃക്ഷം_int_cst_equal (TYPE_SIZE (a2),
					  TYPE_SIZE (a1)))
	    {
	      വൃക്ഷം memb;
	      വേണ്ടി (memb = TYPE_FIELDS (a2);
		   memb; memb = DECL_CHAIN (memb))
		{
		  വൃക്ഷം mv3 = remove_qualifiers (വൃക്ഷം_TYPE (memb));
		  എങ്കിൽ (comptypes_internal (mv3, mv1, data))
		    നിർത്തുക;
		}
	      എങ്കിൽ (memb == NULL_വൃക്ഷം)
		തിരികെ അസത്യം;
	    }
	  അല്ലെങ്കിൽ
	    തിരികെ അസത്യം;
	}

      args1 = വൃക്ഷം_CHAIN (args1);
      args2 = വൃക്ഷം_CHAIN (args2);
    }
}

/* Compute the size to increment a pointer by.  When a function type or void
   type or incomplete type is passed, size_one_node is returned.
   This function does not emit any diagnostics; the caller is responsible
   for that.  */

സ്ഥിതം വൃക്ഷം
c_size_in_bytes (const_വൃക്ഷം type)
{
  എണ്ണൽ വൃക്ഷം_code code = വൃക്ഷം_CODE (type);

  എങ്കിൽ (code == FUNCTION_TYPE || code == VOID_TYPE || code == ERROR_MARK
      || !COMPLETE_TYPE_P (type))
    തിരികെ size_one_കണ്ണി;

  /* Convert in case a char is more than one unit.  */
  തിരികെ size_binop_loc (നിവേശം_location, CEIL_DIV_വ്യഞ്ജകം, TYPE_SIZE_UNIT (type),
			 size_int (TYPE_PRECISION (char_type_കണ്ണി)
				   / BITS_PER_UNIT));
}

/* Return either DECL or its known constant value (if it has one).  */

വൃക്ഷം
decl_constant_മൂല്യം_1 (വൃക്ഷം decl, തർക്കം in_init)
{
  എങ്കിൽ (/* Note that DECL_INITIAL isn't valid for a PARM_DECL.  */
      വൃക്ഷം_CODE (decl) != PARM_DECL
      && !വൃക്ഷം_THIS_VOLATILE (decl)
      && വൃക്ഷം_READONLY (decl)
      && DECL_INITIAL (decl) != NULL_വൃക്ഷം
      && !error_operand_p (DECL_INITIAL (decl))
      /* This is invalid if initial value is not constant.
	 If it has either a function call, a memory reference,
	 or a variable, then re-evaluating it could give different results.  */
      && വൃക്ഷം_CONSTANT (DECL_INITIAL (decl))
      /* Check for cases where this is sub-optimal, even though valid.  */
      && (in_init || വൃക്ഷം_CODE (DECL_INITIAL (decl)) != CONSTRUCTOR))
    തിരികെ DECL_INITIAL (decl);
  തിരികെ decl;
}

/* Return either DECL or its known constant value (if it has one).
   Like the above, but always return decl outside of functions.  */

വൃക്ഷം
decl_constant_മൂല്യം (വൃക്ഷം decl)
{
  /* Don't change a variable array bound or initial value to a constant
     in a place where a variable is invalid.  */
  തിരികെ current_function_decl ? decl_constant_മൂല്യം_1 (decl, അസത്യം) : decl;
}

/* Convert the array expression EXP to a pointer.  */
സ്ഥിതം വൃക്ഷം
array_to_pointer_conversion (location_t loc, വൃക്ഷം exp)
{
  വൃക്ഷം orig_exp = exp;
  വൃക്ഷം type = വൃക്ഷം_TYPE (exp);
  വൃക്ഷം adr;
  വൃക്ഷം restype = വൃക്ഷം_TYPE (type);
  വൃക്ഷം ptrtype;

  gcc_assert (വൃക്ഷം_CODE (type) == ARRAY_TYPE);

  STRIP_TYPE_NOPS (exp);

  copy_warning (exp, orig_exp);

  ptrtype = c_build_pointer_type (restype);

  എങ്കിൽ (INDIRECT_REF_P (exp))
    തിരികെ convert (ptrtype, വൃക്ഷം_OPERAND (exp, 0));

  /* In C++ array compound literals are temporary objects unless they are
     const or appear in namespace scope, so they are destroyed too soon
     to use them for much of anything  (c++/53220).  */
  എങ്കിൽ (warn_cxx_compat && വൃക്ഷം_CODE (exp) == COMPOUND_LITERAL_വ്യഞ്ജകം)
    {
      വൃക്ഷം decl = വൃക്ഷം_OPERAND (വൃക്ഷം_OPERAND (exp, 0), 0);
      എങ്കിൽ (!വൃക്ഷം_READONLY (decl) && !വൃക്ഷം_STATIC (decl))
	warning_at (DECL_SOURCE_LOCATION (decl), OPT_Wc___compat,
		    "converting an array compound literal to a pointer "
		    "leads to a dangling pointer in C++");
    }

  adr = build_unary_op (loc, ADDR_വ്യഞ്ജകം, exp, സത്യം);
  തിരികെ convert (ptrtype, adr);
}

/* Convert the function expression EXP to a pointer.  */
സ്ഥിതം വൃക്ഷം
function_to_pointer_conversion (location_t loc, വൃക്ഷം exp)
{
  വൃക്ഷം orig_exp = exp;

  gcc_assert (വൃക്ഷം_CODE (വൃക്ഷം_TYPE (exp)) == FUNCTION_TYPE);

  STRIP_TYPE_NOPS (exp);

  copy_warning (exp, orig_exp);

  വൃക്ഷം exp2 = build_unary_op (loc, ADDR_വ്യഞ്ജകം, exp, അസത്യം);

  /* If the function is defined and known to not require a non-local
     context, make sure no trampoline is generated.  */
  എങ്കിൽ (വൃക്ഷം_CODE (exp) == FUNCTION_DECL
      && DECL_INITIAL (exp) && !C_FUNC_NONLOCAL_CONTEXT (exp))
   വൃക്ഷം_NO_TRAMPOLINE (exp2) = 1;

  തിരികെ exp2;
}

/* Mark EXP as read, not just set, for set but not used -Wunused
   warning purposes.  */

ശൂന്യം
mark_exp_read (വൃക്ഷം exp)
{
  തിരഞ്ഞെടുപ്പ് (വൃക്ഷം_CODE (exp))
    {
    അവസ്ഥ VAR_DECL:
    അവസ്ഥ PARM_DECL:
      DECL_READ_P (exp) = 1;
      നിർത്തുക;
    CASE_CONVERT:
      എങ്കിൽ (VOID_TYPE_P (വൃക്ഷം_TYPE (exp)))
	തിരഞ്ഞെടുപ്പ് (വൃക്ഷം_CODE (വൃക്ഷം_OPERAND (exp, 0)))
	  {
	  അവസ്ഥ PREINCREMENT_വ്യഞ്ജകം:
	  അവസ്ഥ PREDECREMENT_വ്യഞ്ജകം:
	  അവസ്ഥ POSTINCREMENT_വ്യഞ്ജകം:
	  അവസ്ഥ POSTDECREMENT_വ്യഞ്ജകം:
	    തിരികെ;
	  സ്ഥിരസ്ഥിതി:
	    നിർത്തുക;
	  }
      /* FALLTHRU */
    അവസ്ഥ ARRAY_REF:
    അവസ്ഥ COMPONENT_REF:
    അവസ്ഥ MODIFY_വ്യഞ്ജകം:
    അവസ്ഥ REALPART_വ്യഞ്ജകം:
    അവസ്ഥ IMAGPART_വ്യഞ്ജകം:
    അവസ്ഥ ADDR_വ്യഞ്ജകം:
    അവസ്ഥ VIEW_CONVERT_വ്യഞ്ജകം:
    അവസ്ഥ PREINCREMENT_വ്യഞ്ജകം:
    അവസ്ഥ PREDECREMENT_വ്യഞ്ജകം:
    അവസ്ഥ POSTINCREMENT_വ്യഞ്ജകം:
    അവസ്ഥ POSTDECREMENT_വ്യഞ്ജകം:
      mark_exp_read (വൃക്ഷം_OPERAND (exp, 0));
      നിർത്തുക;
    അവസ്ഥ COMPOUND_വ്യഞ്ജകം:
      /* Pattern match what build_atomic_assign produces with modifycode
	 NOP_EXPR.  */
      എങ്കിൽ (VAR_P (വൃക്ഷം_OPERAND (exp, 1))
	  && DECL_ARTIFICIAL (വൃക്ഷം_OPERAND (exp, 1))
	  && വൃക്ഷം_CODE (വൃക്ഷം_OPERAND (exp, 0)) == COMPOUND_വ്യഞ്ജകം)
	{
	  വൃക്ഷം t1 = വൃക്ഷം_OPERAND (വൃക്ഷം_OPERAND (exp, 0), 0);
	  വൃക്ഷം t2 = വൃക്ഷം_OPERAND (വൃക്ഷം_OPERAND (exp, 0), 1);
	  എങ്കിൽ (വൃക്ഷം_CODE (t1) == TARGET_വ്യഞ്ജകം
	      && TARGET_വ്യഞ്ജകം_SLOT (t1) == വൃക്ഷം_OPERAND (exp, 1)
	      && വൃക്ഷം_CODE (t2) == CALL_വ്യഞ്ജകം)
	    {
	      വൃക്ഷം fndecl = get_callee_fndecl (t2);
	      വൃക്ഷം arg = NULL_വൃക്ഷം;
	      എങ്കിൽ (fndecl
		  && വൃക്ഷം_CODE (fndecl) == FUNCTION_DECL
		  && fndecl_built_in_p (fndecl, BUILT_IN_NORMAL)
		  && call_വ്യഞ്ജകം_nargs (t2) >= 2)
		തിരഞ്ഞെടുപ്പ് (DECL_FUNCTION_CODE (fndecl))
		  {
		  അവസ്ഥ BUILT_IN_ATOMIC_STORE:
		    arg = CALL_വ്യഞ്ജകം_ARG (t2, 1);
		    നിർത്തുക;
		  അവസ്ഥ BUILT_IN_ATOMIC_STORE_1:
		  അവസ്ഥ BUILT_IN_ATOMIC_STORE_2:
		  അവസ്ഥ BUILT_IN_ATOMIC_STORE_4:
		  അവസ്ഥ BUILT_IN_ATOMIC_STORE_8:
		  അവസ്ഥ BUILT_IN_ATOMIC_STORE_16:
		    arg = CALL_വ്യഞ്ജകം_ARG (t2, 0);
		    നിർത്തുക;
		  സ്ഥിരസ്ഥിതി:
		    നിർത്തുക;
		  }
	      എങ്കിൽ (arg)
		{
		  STRIP_NOPS (arg);
		  എങ്കിൽ (വൃക്ഷം_CODE (arg) == ADDR_വ്യഞ്ജകം
		      && DECL_P (വൃക്ഷം_OPERAND (arg, 0))
		      && TYPE_ATOMIC (വൃക്ഷം_TYPE (വൃക്ഷം_OPERAND (arg, 0))))
		    mark_exp_read (വൃക്ഷം_OPERAND (arg, 0));
		}
	    }
	}
      /* FALLTHRU */
    അവസ്ഥ C_MAYBE_CONST_വ്യഞ്ജകം:
      mark_exp_read (വൃക്ഷം_OPERAND (exp, 1));
      നിർത്തുക;
    അവസ്ഥ OMP_ARRAY_SECTION:
      mark_exp_read (വൃക്ഷം_OPERAND (exp, 0));
      എങ്കിൽ (വൃക്ഷം_OPERAND (exp, 1))
	mark_exp_read (വൃക്ഷം_OPERAND (exp, 1));
      എങ്കിൽ (വൃക്ഷം_OPERAND (exp, 2))
	mark_exp_read (വൃക്ഷം_OPERAND (exp, 2));
      നിർത്തുക;
    സ്ഥിരസ്ഥിതി:
      നിർത്തുക;
    }
}

/* Perform the default conversion of arrays and functions to pointers.
   Return the result of converting EXP.  For any other expression, just
   return EXP.

   LOC is the location of the expression.  */

ഘടന c_വ്യഞ്ജകം
default_function_array_conversion (location_t loc, ഘടന c_വ്യഞ്ജകം exp)
{
  വൃക്ഷം orig_exp = exp.മൂല്യം;
  വൃക്ഷം type = വൃക്ഷം_TYPE (exp.മൂല്യം);
  എണ്ണൽ വൃക്ഷം_code code = വൃക്ഷം_CODE (type);

  തിരഞ്ഞെടുപ്പ് (code)
    {
    അവസ്ഥ ARRAY_TYPE:
      {
	തർക്കം not_lvalue = അസത്യം;
	തർക്കം lvalue_array_p;

	ആകുമ്പോൾ ((വൃക്ഷം_CODE (exp.മൂല്യം) == NON_LVALUE_വ്യഞ്ജകം
		|| CONVERT_വ്യഞ്ജകം_P (exp.മൂല്യം))
	       && വൃക്ഷം_TYPE (വൃക്ഷം_OPERAND (exp.മൂല്യം, 0)) == type)
	  {
	    എങ്കിൽ (വൃക്ഷം_CODE (exp.മൂല്യം) == NON_LVALUE_വ്യഞ്ജകം)
	      not_lvalue = സത്യം;
	    exp.മൂല്യം = വൃക്ഷം_OPERAND (exp.മൂല്യം, 0);
	  }

	copy_warning (exp.മൂല്യം, orig_exp);

	lvalue_array_p = !not_lvalue && lvalue_p (exp.മൂല്യം);
	എങ്കിൽ (!flag_isoc99 && !lvalue_array_p)
	  {
	    /* Before C99, non-lvalue arrays do not decay to pointers.
	       Normally, using such an array would be invalid; but it can
	       be used correctly inside sizeof or as a statement expression.
	       Thus, do not give an error here; an error will result later.  */
	    തിരികെ exp;
	  }

	exp.മൂല്യം = array_to_pointer_conversion (loc, exp.മൂല്യം);
      }
      നിർത്തുക;
    അവസ്ഥ FUNCTION_TYPE:
      exp.മൂല്യം = function_to_pointer_conversion (loc, exp.മൂല്യം);
      നിർത്തുക;
    സ്ഥിരസ്ഥിതി:
      നിർത്തുക;
    }

  തിരികെ exp;
}

ഘടന c_വ്യഞ്ജകം
default_function_array_read_conversion (location_t loc, ഘടന c_വ്യഞ്ജകം exp)
{
  mark_exp_read (exp.മൂല്യം);
  /* We only generate a call to .ACCESS_WITH_SIZE when it is a read.  */
  എങ്കിൽ (വൃക്ഷം_CODE (exp.മൂല്യം) == COMPONENT_REF
      && handle_counted_by_p (exp.മൂല്യം))
    exp.മൂല്യം = handle_counted_by_for_component_ref (loc, exp.മൂല്യം);
  തിരികെ default_function_array_conversion (loc, exp);
}

/* Return whether EXPR should be treated as an atomic lvalue for the
   purposes of load and store handling.  */

സ്ഥിതം തർക്കം
really_atomic_lvalue (വൃക്ഷം വ്യഞ്ജകം)
{
  എങ്കിൽ (error_operand_p (വ്യഞ്ജകം))
    തിരികെ അസത്യം;
  എങ്കിൽ (!TYPE_ATOMIC (വൃക്ഷം_TYPE (വ്യഞ്ജകം)))
    തിരികെ അസത്യം;
  എങ്കിൽ (!COMPLETE_TYPE_P (വൃക്ഷം_TYPE (വ്യഞ്ജകം)))
    തിരികെ അസത്യം;
  എങ്കിൽ (!lvalue_p (വ്യഞ്ജകം))
    തിരികെ അസത്യം;

  /* Ignore _Atomic on register variables, since their addresses can't
     be taken so (a) atomicity is irrelevant and (b) the normal atomic
     sequences wouldn't work.  Ignore _Atomic on structures containing
     bit-fields, since accessing elements of atomic structures or
     unions is undefined behavior (C11 6.5.2.3#5), but it's unclear if
     it's undefined at translation time or execution time, and the
     normal atomic sequences again wouldn't work.  */
  ആകുമ്പോൾ (handled_component_p (വ്യഞ്ജകം))
    {
      എങ്കിൽ (വൃക്ഷം_CODE (വ്യഞ്ജകം) == COMPONENT_REF
	  && DECL_C_BIT_FIELD (വൃക്ഷം_OPERAND (വ്യഞ്ജകം, 1)))
	തിരികെ അസത്യം;
      വ്യഞ്ജകം = വൃക്ഷം_OPERAND (വ്യഞ്ജകം, 0);
    }
  എങ്കിൽ (വൃക്ഷം_CODE (വ്യഞ്ജകം) == COMPOUND_LITERAL_വ്യഞ്ജകം)
    വ്യഞ്ജകം = COMPOUND_LITERAL_വ്യഞ്ജകം_DECL (വ്യഞ്ജകം);
  എങ്കിൽ (DECL_P (വ്യഞ്ജകം) && C_DECL_REGISTER (വ്യഞ്ജകം))
    തിരികെ അസത്യം;
  തിരികെ സത്യം;
}

/* If EXPR is a named constant (C23) derived from a constexpr variable
   - that is, a reference to such a variable, or a member extracted by
   a sequence of structure and union (but not array) member accesses
   (where union member accesses must access the same member as
   initialized) - then return the corresponding initializer;
   otherwise, return NULL_TREE.  */

സ്ഥിതം വൃക്ഷം
maybe_get_constexpr_init (വൃക്ഷം വ്യഞ്ജകം)
{
  വൃക്ഷം decl = NULL_വൃക്ഷം;
  എങ്കിൽ (വൃക്ഷം_CODE (വ്യഞ്ജകം) == VAR_DECL)
    decl = വ്യഞ്ജകം;
  അല്ലെങ്കിൽ എങ്കിൽ (വൃക്ഷം_CODE (വ്യഞ്ജകം) == COMPOUND_LITERAL_വ്യഞ്ജകം)
    decl = COMPOUND_LITERAL_വ്യഞ്ജകം_DECL (വ്യഞ്ജകം);
  എങ്കിൽ (decl
      && C_DECL_DECLARED_CONSTEXPR (decl)
      && DECL_INITIAL (decl) != NULL_വൃക്ഷം
      && !error_operand_p (DECL_INITIAL (decl)))
    തിരികെ DECL_INITIAL (decl);
  എങ്കിൽ (വൃക്ഷം_CODE (വ്യഞ്ജകം) != COMPONENT_REF)
    തിരികെ NULL_വൃക്ഷം;
  വൃക്ഷം inner = maybe_get_constexpr_init (വൃക്ഷം_OPERAND (വ്യഞ്ജകം, 0));
  എങ്കിൽ (inner == NULL_വൃക്ഷം)
    തിരികെ NULL_വൃക്ഷം;
  ആകുമ്പോൾ ((CONVERT_വ്യഞ്ജകം_P (inner) || വൃക്ഷം_CODE (inner) == NON_LVALUE_വ്യഞ്ജകം)
	 && !error_operand_p (inner)
	 && (TYPE_MAIN_VARIANT (വൃക്ഷം_TYPE (inner))
	     == TYPE_MAIN_VARIANT (വൃക്ഷം_TYPE (വൃക്ഷം_OPERAND (inner, 0)))))
    inner = വൃക്ഷം_OPERAND (inner, 0);
  എങ്കിൽ (വൃക്ഷം_CODE (inner) != CONSTRUCTOR)
    തിരികെ NULL_വൃക്ഷം;
  വൃക്ഷം field = വൃക്ഷം_OPERAND (വ്യഞ്ജകം, 1);
  unsigned HOST_WIDE_INT cidx;
  വൃക്ഷം cfield, cvalue;
  തർക്കം have_other_init = അസത്യം;
  FOR_EACH_CONSTRUCTOR_ELT (CONSTRUCTOR_ELTS (inner), cidx, cfield, cvalue)
    {
      എങ്കിൽ (cfield == field)
	തിരികെ cvalue;
      have_other_init = സത്യം;
    }
  എങ്കിൽ (വൃക്ഷം_CODE (വൃക്ഷം_TYPE (inner)) == UNION_TYPE
      && (have_other_init || field != TYPE_FIELDS (വൃക്ഷം_TYPE (inner))))
    തിരികെ NULL_വൃക്ഷം;
  /* Return a default initializer.  */
  എങ്കിൽ (RECORD_OR_UNION_TYPE_P (വൃക്ഷം_TYPE (വ്യഞ്ജകം)))
    തിരികെ build_constructor (വൃക്ഷം_TYPE (വ്യഞ്ജകം), ശൂന്യ);
  തിരികെ build_zero_cst (വൃക്ഷം_TYPE (വ്യഞ്ജകം));
}

/* Helper function for convert_lvalue_to_rvalue called via
   walk_tree_without_duplicates.  Find DATA inside of the expression.  */

സ്ഥിതം വൃക്ഷം
c_find_var_r (വൃക്ഷം *tp, പൂർണ്ണസംഖ്യ *walk_subtrees, ശൂന്യം *data)
{
  എങ്കിൽ (TYPE_P (*tp))
    *walk_subtrees = 0;
  അല്ലെങ്കിൽ എങ്കിൽ (*tp == (വൃക്ഷം) data)
    തിരികെ *tp;
  തിരികെ NULL_വൃക്ഷം;
}

/* Convert expression EXP (location LOC) from lvalue to rvalue,
   including converting functions and arrays to pointers if CONVERT_P.
   If READ_P, also mark the expression as having been read.  If
   FOR_INIT, constexpr expressions of structure and union type should
   be replaced by the corresponding CONSTRUCTOR; otherwise, only
   constexpr scalars (including elements of structures and unions) are
   replaced by their initializers.  */

ഘടന c_വ്യഞ്ജകം
convert_lvalue_to_rvalue (location_t loc, ഘടന c_വ്യഞ്ജകം exp,
			  തർക്കം convert_p, തർക്കം read_p, തർക്കം for_init)
{
  തർക്കം force_non_npc = അസത്യം;
  എങ്കിൽ (read_p)
    mark_exp_read (exp.മൂല്യം);
  /* We only generate a call to .ACCESS_WITH_SIZE when it is a read.  */
  എങ്കിൽ (read_p && വൃക്ഷം_CODE (exp.മൂല്യം) == COMPONENT_REF
      && handle_counted_by_p (exp.മൂല്യം))
    exp.മൂല്യം = handle_counted_by_for_component_ref (loc, exp.മൂല്യം);

  എങ്കിൽ (convert_p)
    exp = default_function_array_conversion (loc, exp);
  എങ്കിൽ (!VOID_TYPE_P (വൃക്ഷം_TYPE (exp.മൂല്യം))
      || (flag_isoc2y
	  && TYPE_QUALS (വൃക്ഷം_TYPE (exp.മൂല്യം)) != TYPE_UNQUALIFIED))
    exp.മൂല്യം = require_complete_type (loc, exp.മൂല്യം);
  എങ്കിൽ (for_init || !RECORD_OR_UNION_TYPE_P (വൃക്ഷം_TYPE (exp.മൂല്യം)))
    {
      വൃക്ഷം init = maybe_get_constexpr_init (exp.മൂല്യം);
      എങ്കിൽ (init != NULL_വൃക്ഷം)
	{
	  /* A named constant of pointer type or type nullptr_t is not
	     a null pointer constant even if the initializer is
	     one.  */
	  എങ്കിൽ (വൃക്ഷം_CODE (init) == INTEGER_CST
	      && !INTEGRAL_TYPE_P (വൃക്ഷം_TYPE (init))
	      && integer_zerop (init))
	    force_non_npc = സത്യം;
	  exp.മൂല്യം = init;
	}
    }
  എങ്കിൽ (really_atomic_lvalue (exp.മൂല്യം))
    {
      vec<വൃക്ഷം, va_gc> *params;
      വൃക്ഷം nonatomic_type, tmp, tmp_addr, fndecl, func_call;
      വൃക്ഷം വ്യഞ്ജകം_type = വൃക്ഷം_TYPE (exp.മൂല്യം);
      വൃക്ഷം വ്യഞ്ജകം_addr = build_unary_op (loc, ADDR_വ്യഞ്ജകം, exp.മൂല്യം, അസത്യം);
      വൃക്ഷം seq_cst = build_int_cst (integer_type_കണ്ണി, MEMMODEL_SEQ_CST);

      gcc_assert (TYPE_ATOMIC (വ്യഞ്ജകം_type));

      /* Expansion of a generic atomic load may require an addition
	 element, so allocate enough to prevent a resize.  */
      vec_alloc (params, 4);

      /* Remove the qualifiers for the rest of the expressions and
	 create the VAL temp variable to hold the RHS.  */
      nonatomic_type = build_qualified_type (വ്യഞ്ജകം_type, TYPE_UNQUALIFIED);
      tmp = create_tmp_var_raw (nonatomic_type);
      tmp_addr = build_unary_op (loc, ADDR_വ്യഞ്ജകം, tmp, അസത്യം);
      വൃക്ഷം_ADDRESSABLE (tmp) = 1;
      /* Do not disable warnings for TMP even though it's artificial.
	 -Winvalid-memory-model depends on it.  */

      /* Issue __atomic_load (&expr, &tmp, SEQ_CST);  */
      fndecl = builtin_decl_explicit (BUILT_IN_ATOMIC_LOAD);
      params->quick_തള്ളുക (വ്യഞ്ജകം_addr);
      params->quick_തള്ളുക (tmp_addr);
      params->quick_തള്ളുക (seq_cst);
      func_call = c_build_function_call_vec (loc, vNULL, fndecl, params, ശൂന്യ);

      /* EXPR is always read.  */
      mark_exp_read (exp.മൂല്യം);

      /* Optimize the common case where c_build_function_call_vec
	 immediately folds __atomic_load (&expr, &tmp, SEQ_CST); into
	 tmp = __atomic_load_<N> (&expr, SEQ_CST);
	 In that case tmp is not addressable and can be initialized
	 fully by the rhs of the MODIFY_EXPR.  */
      വൃക്ഷം tem = func_call;
      എങ്കിൽ (CONVERT_വ്യഞ്ജകം_P (tem) && VOID_TYPE_P (വൃക്ഷം_TYPE (tem)))
	{
	  tem = വൃക്ഷം_OPERAND (tem, 0);
	  എങ്കിൽ (വൃക്ഷം_CODE (tem) == MODIFY_വ്യഞ്ജകം
	      && വൃക്ഷം_OPERAND (tem, 0) == tmp
	      && !walk_വൃക്ഷം_without_duplicates (&വൃക്ഷം_OPERAND (tem, 1),
						c_find_var_r, tmp))
	    {
	      വൃക്ഷം_ADDRESSABLE (tmp) = 0;
	      func_call = വൃക്ഷം_OPERAND (tem, 1);
	    }
	}

      /* Return tmp which contains the value loaded.  */
      exp.മൂല്യം = build4 (TARGET_വ്യഞ്ജകം, nonatomic_type, tmp, func_call,
			  NULL_വൃക്ഷം, NULL_വൃക്ഷം);
    }
  എങ്കിൽ (convert_p && !error_operand_p (exp.മൂല്യം)
      && (വൃക്ഷം_CODE (വൃക്ഷം_TYPE (exp.മൂല്യം)) != ARRAY_TYPE))
    exp.മൂല്യം = convert (build_qualified_type (വൃക്ഷം_TYPE (exp.മൂല്യം), TYPE_UNQUALIFIED), exp.മൂല്യം);
  എങ്കിൽ (force_non_npc)
    exp.മൂല്യം = build1 (NOP_വ്യഞ്ജകം, വൃക്ഷം_TYPE (exp.മൂല്യം), exp.മൂല്യം);

  {
    വൃക്ഷം false_മൂല്യം, true_മൂല്യം;
    എങ്കിൽ (convert_p && !error_operand_p (exp.മൂല്യം)
	&& c_hardbool_type_attr (വൃക്ഷം_TYPE (exp.മൂല്യം),
				 &false_മൂല്യം, &true_മൂല്യം))
      {
	വൃക്ഷം t = save_വ്യഞ്ജകം (exp.മൂല്യം);

	mark_exp_read (exp.മൂല്യം);

	വൃക്ഷം trapfn = builtin_decl_explicit (BUILT_IN_TRAP);
	വൃക്ഷം വ്യഞ്ജകം = build_call_വ്യഞ്ജകം_loc (loc, trapfn, 0);
	വ്യഞ്ജകം = build_compound_വ്യഞ്ജകം (loc, വ്യഞ്ജകം, boolean_true_കണ്ണി);
	വ്യഞ്ജകം = fold_build3_loc (loc, COND_വ്യഞ്ജകം, boolean_type_കണ്ണി,
				fold_build2_loc (loc, NE_വ്യഞ്ജകം,
						 boolean_type_കണ്ണി,
						 t, true_മൂല്യം),
				വ്യഞ്ജകം, boolean_true_കണ്ണി);
	വ്യഞ്ജകം = fold_build3_loc (loc, COND_വ്യഞ്ജകം, boolean_type_കണ്ണി,
				fold_build2_loc (loc, NE_വ്യഞ്ജകം,
						 boolean_type_കണ്ണി,
						 t, false_മൂല്യം),
				വ്യഞ്ജകം, boolean_false_കണ്ണി);

	exp.മൂല്യം = വ്യഞ്ജകം;
      }
  }

  തിരികെ exp;
}

/* Wrapper for the overload above, same arguments but for tree rather than
   c_expr.  This is important for hardbools to decay to bools.  */

സ്ഥിതം വരിയിൽ വൃക്ഷം
convert_lvalue_to_rvalue (location_t loc, വൃക്ഷം val,
			  തർക്കം convert_p, തർക്കം read_p, തർക്കം for_init = അസത്യം)
{
  ഘടന c_വ്യഞ്ജകം വ്യഞ്ജകം;
  memset (&വ്യഞ്ജകം, 0, വലുപ്പം (വ്യഞ്ജകം));
  വ്യഞ്ജകം.മൂല്യം = val;
  വ്യഞ്ജകം = convert_lvalue_to_rvalue (loc, വ്യഞ്ജകം, convert_p, read_p, for_init);
  തിരികെ വ്യഞ്ജകം.മൂല്യം;
}

/* EXP is an expression of integer type.  Apply the integer promotions
   to it and return the promoted value.  */

വൃക്ഷം
perform_integral_promotions (വൃക്ഷം exp)
{
  വൃക്ഷം type = വൃക്ഷം_TYPE (exp);
  എണ്ണൽ വൃക്ഷം_code code = വൃക്ഷം_CODE (type);

  gcc_assert (INTEGRAL_TYPE_P (type));

  /* Convert enums to the result of applying the integer promotions to
     their underlying type.  */
  എങ്കിൽ (code == ENUMERAL_TYPE)
    {
      type = ENUM_UNDERLYING_TYPE (type);
      എങ്കിൽ (c_promoting_integer_type_p (type))
	{
	  എങ്കിൽ (TYPE_UNSIGNED (type)
	      && TYPE_PRECISION (type) == TYPE_PRECISION (integer_type_കണ്ണി))
	    type = unsigned_type_കണ്ണി;
	  അല്ലെങ്കിൽ
	    type = integer_type_കണ്ണി;
	}

      തിരികെ convert (type, exp);
    }

  /* ??? This should no longer be needed now bit-fields have their
     proper types.  */
  എങ്കിൽ (വൃക്ഷം_CODE (exp) == COMPONENT_REF
      && DECL_C_BIT_FIELD (വൃക്ഷം_OPERAND (exp, 1)))
    {
      എങ്കിൽ (BITINT_TYPE_P (DECL_BIT_FIELD_TYPE (വൃക്ഷം_OPERAND (exp, 1))))
	{
	  വൃക്ഷം btype = DECL_BIT_FIELD_TYPE (വൃക്ഷം_OPERAND (exp, 1));
	  എങ്കിൽ (വൃക്ഷം_CODE (btype) == BITINT_TYPE)
	    തിരികെ convert (btype, exp);
	  അല്ലെങ്കിൽ
	    തിരികെ convert (ENUM_UNDERLYING_TYPE (btype), exp);
	}
      /* If it's thinner than an int, promote it like a
	 c_promoting_integer_type_p, otherwise leave it alone.  */
      എങ്കിൽ (compare_വൃക്ഷം_int (DECL_SIZE (വൃക്ഷം_OPERAND (exp, 1)),
			    TYPE_PRECISION (integer_type_കണ്ണി)) < 0)
	തിരികെ convert (integer_type_കണ്ണി, exp);
    }

  എങ്കിൽ (c_promoting_integer_type_p (type))
    {
      /* Preserve unsignedness if not really getting any wider.  */
      എങ്കിൽ (TYPE_UNSIGNED (type)
	  && TYPE_PRECISION (type) == TYPE_PRECISION (integer_type_കണ്ണി))
	തിരികെ convert (unsigned_type_കണ്ണി, exp);

      തിരികെ convert (integer_type_കണ്ണി, exp);
    }

  തിരികെ exp;
}


/* Perform default promotions for C data used in expressions.
   Enumeral types or short or char are converted to int.
   In addition, manifest constants symbols are replaced by their values.  */

വൃക്ഷം
default_conversion (വൃക്ഷം exp)
{
  വൃക്ഷം orig_exp;
  വൃക്ഷം type = വൃക്ഷം_TYPE (exp);
  എണ്ണൽ വൃക്ഷം_code code = വൃക്ഷം_CODE (type);
  വൃക്ഷം promoted_type;

  mark_exp_read (exp);
  /* We only generate a call to .ACCESS_WITH_SIZE when it is a read.  */
  എങ്കിൽ (വൃക്ഷം_CODE (exp) == COMPONENT_REF
      && handle_counted_by_p (exp))
    exp = handle_counted_by_for_component_ref (വ്യഞ്ജകം_LOCATION (exp), exp);

  /* Functions and arrays have been converted during parsing.  */
  gcc_assert (code != FUNCTION_TYPE);
  എങ്കിൽ (code == ARRAY_TYPE)
    തിരികെ exp;

  /* Constants can be used directly unless they're not loadable.  */
  എങ്കിൽ (വൃക്ഷം_CODE (exp) == CONST_DECL)
    exp = DECL_INITIAL (exp);

  /* Strip no-op conversions.  */
  orig_exp = exp;
  STRIP_TYPE_NOPS (exp);

  copy_warning (exp, orig_exp);

  എങ്കിൽ (code == VOID_TYPE)
    {
      error_at (വ്യഞ്ജകം_LOC_OR_LOC (exp, നിവേശം_location),
		"void value not ignored as it ought to be");
      തിരികെ error_mark_കണ്ണി;
    }

  exp = require_complete_type (വ്യഞ്ജകം_LOC_OR_LOC (exp, നിവേശം_location), exp);
  എങ്കിൽ (exp == error_mark_കണ്ണി)
    തിരികെ error_mark_കണ്ണി;

  promoted_type = targetm.promoted_type (type);
  എങ്കിൽ (promoted_type)
    തിരികെ convert (promoted_type, exp);

  എങ്കിൽ (INTEGRAL_TYPE_P (type))
    {
      /* Avoid performing integral promotion of bit-precise integer
	 type bit-field to its corresponding bit-precise integer if
	 orig_exp is a cast to it to its underlying type.  */
      എങ്കിൽ (orig_exp != exp
	  && വൃക്ഷം_CODE (exp) == COMPONENT_REF
	  && DECL_C_BIT_FIELD (വൃക്ഷം_OPERAND (exp, 1))
	  && BITINT_TYPE_P (DECL_BIT_FIELD_TYPE (വൃക്ഷം_OPERAND (exp, 1))))
	തിരികെ perform_integral_promotions (orig_exp);
      തിരികെ perform_integral_promotions (exp);
    }

  തിരികെ exp;
}

/* Look up COMPONENT in a structure or union TYPE.

   If the component name is not found, returns NULL_TREE.  Otherwise,
   the return value is a TREE_LIST, with each TREE_VALUE a FIELD_DECL
   stepping down the chain to the component, which is in the last
   TREE_VALUE of the list.  Normally the list is of length one, but if
   the component is embedded within (nested) anonymous structures or
   unions, the list steps down the chain to the component.  */

വൃക്ഷം
lookup_field (const_വൃക്ഷം type, വൃക്ഷം component)
{
  വൃക്ഷം field;

  /* If TYPE_LANG_SPECIFIC is set, then it is a sorted array of pointers
     to the field elements.  Use a binary search on this array to quickly
     find the element.  Otherwise, do a linear search.  TYPE_LANG_SPECIFIC
     will always be set for structures which have many elements.

     Duplicate field checking replaces duplicates with NULL_TREE so
     TYPE_LANG_SPECIFIC arrays are potentially no longer sorted.  In that
     case just iterate using DECL_CHAIN.  */

  എങ്കിൽ (TYPE_LANG_SPECIFIC (type) && TYPE_LANG_SPECIFIC (type)->s
      && !seen_error ())
    {
      പൂർണ്ണസംഖ്യ bot, മുകൾ, half;
      വൃക്ഷം *field_array = &TYPE_LANG_SPECIFIC (type)->s->elts[0];

      field = TYPE_FIELDS (type);
      bot = 0;
      മുകൾ = TYPE_LANG_SPECIFIC (type)->s->len;
      ആകുമ്പോൾ (മുകൾ - bot > 1)
	{
	  half = (മുകൾ - bot + 1) >> 1;
	  field = field_array[bot+half];

	  എങ്കിൽ (DECL_NAME (field) == NULL_വൃക്ഷം)
	    {
	      /* Step through all anon unions in linear fashion.  */
	      ആകുമ്പോൾ (DECL_NAME (field_array[bot]) == NULL_വൃക്ഷം)
		{
		  field = field_array[bot++];
		  എങ്കിൽ (RECORD_OR_UNION_TYPE_P (വൃക്ഷം_TYPE (field)))
		    {
		      വൃക്ഷം anon = lookup_field (വൃക്ഷം_TYPE (field), component);

		      എങ്കിൽ (anon)
			തിരികെ വൃക്ഷം_cons (NULL_വൃക്ഷം, field, anon);

		      /* The Plan 9 compiler permits referring
			 directly to an anonymous struct/union field
			 using a typedef name.  */
		      എങ്കിൽ (flag_plan9_extensions
			  && TYPE_NAME (വൃക്ഷം_TYPE (field)) != NULL_വൃക്ഷം
			  && (വൃക്ഷം_CODE (TYPE_NAME (വൃക്ഷം_TYPE (field)))
			      == TYPE_DECL)
			  && (DECL_NAME (TYPE_NAME (വൃക്ഷം_TYPE (field)))
			      == component))
			നിർത്തുക;
		    }
		}

	      /* Entire record is only anon unions.  */
	      എങ്കിൽ (bot > മുകൾ)
		തിരികെ NULL_വൃക്ഷം;

	      /* Restart the binary search, with new lower bound.  */
	      തുടരുക;
	    }

	  എങ്കിൽ (DECL_NAME (field) == component)
	    നിർത്തുക;
	  എങ്കിൽ (DECL_NAME (field) < component)
	    bot += half;
	  അല്ലെങ്കിൽ
	    മുകൾ = bot + half;
	}

      എങ്കിൽ (DECL_NAME (field_array[bot]) == component)
	field = field_array[bot];
      അല്ലെങ്കിൽ എങ്കിൽ (DECL_NAME (field) != component)
	തിരികെ NULL_വൃക്ഷം;
    }
  അല്ലെങ്കിൽ
    {
      വേണ്ടി (field = TYPE_FIELDS (type); field; field = DECL_CHAIN (field))
	{
	  എങ്കിൽ (DECL_NAME (field) == NULL_വൃക്ഷം
	      && RECORD_OR_UNION_TYPE_P (വൃക്ഷം_TYPE (field)))
	    {
	      വൃക്ഷം anon = lookup_field (വൃക്ഷം_TYPE (field), component);

	      എങ്കിൽ (anon)
		തിരികെ വൃക്ഷം_cons (NULL_വൃക്ഷം, field, anon);

	      /* The Plan 9 compiler permits referring directly to an
		 anonymous struct/union field using a typedef
		 name.  */
	      എങ്കിൽ (flag_plan9_extensions
		  && TYPE_NAME (വൃക്ഷം_TYPE (field)) != NULL_വൃക്ഷം
		  && വൃക്ഷം_CODE (TYPE_NAME (വൃക്ഷം_TYPE (field))) == TYPE_DECL
		  && (DECL_NAME (TYPE_NAME (വൃക്ഷം_TYPE (field)))
		      == component))
		നിർത്തുക;
	    }

	  എങ്കിൽ (DECL_NAME (field) == component)
	    നിർത്തുക;
	}

      എങ്കിൽ (field == NULL_വൃക്ഷം)
	തിരികെ NULL_വൃക്ഷം;
    }

  തിരികെ വൃക്ഷം_cons (NULL_വൃക്ഷം, field, NULL_വൃക്ഷം);
}

/* Recursively append candidate IDENTIFIER_NODEs to CANDIDATES.  */

സ്ഥിതം ശൂന്യം
lookup_field_fuzzy_find_candidates (വൃക്ഷം type, വൃക്ഷം component,
				    vec<വൃക്ഷം> *candidates)
{
  വൃക്ഷം field;
  വേണ്ടി (field = TYPE_FIELDS (type); field; field = DECL_CHAIN (field))
    {
      എങ്കിൽ (DECL_NAME (field) == NULL_വൃക്ഷം
	  && RECORD_OR_UNION_TYPE_P (വൃക്ഷം_TYPE (field)))
	lookup_field_fuzzy_find_candidates (വൃക്ഷം_TYPE (field), component,
					    candidates);

      എങ്കിൽ (DECL_NAME (field))
	candidates->safe_തള്ളുക (DECL_NAME (field));
    }
}

/* Like "lookup_field", but find the closest matching IDENTIFIER_NODE,
   rather than returning a TREE_LIST for an exact match.  */

സ്ഥിതം വൃക്ഷം
lookup_field_fuzzy (വൃക്ഷം type, വൃക്ഷം component)
{
  gcc_assert (വൃക്ഷം_CODE (component) == IDENTIFIER_കണ്ണി);

  /* First, gather a list of candidates.  */
  auto_vec <വൃക്ഷം> candidates;

  lookup_field_fuzzy_find_candidates (type, component,
				      &candidates);

  തിരികെ find_closest_identifier (component, &candidates);
}

/* Support function for build_component_ref's error-handling.

   Given DATUM_TYPE, and "DATUM.COMPONENT", where DATUM is *not* a
   struct or union, should we suggest "DATUM->COMPONENT" as a hint?  */

സ്ഥിതം തർക്കം
should_suggest_deref_p (വൃക്ഷം datum_type)
{
  /* We don't do it for Objective-C, since Objective-C 2.0 dot-syntax
     allows "." for ptrs; we could be handling a failed attempt
     to access a property.  */
  എങ്കിൽ (c_dialect_objc ())
    തിരികെ അസത്യം;

  /* Only suggest it for pointers...  */
  എങ്കിൽ (വൃക്ഷം_CODE (datum_type) != POINTER_TYPE)
    തിരികെ അസത്യം;

  /* ...to structs/unions.  */
  വൃക്ഷം underlying_type = വൃക്ഷം_TYPE (datum_type);
  എണ്ണൽ വൃക്ഷം_code code = വൃക്ഷം_CODE (underlying_type);
  എങ്കിൽ (code == RECORD_TYPE || code == UNION_TYPE)
    തിരികെ സത്യം;
  അല്ലെങ്കിൽ
    തിരികെ അസത്യം;
}

/* Give a component ref REF, decide whether we should handle its counted_by
   attribute based on its context:
   Do not handle counted_by when in offsetof, typeof and alignof operator.  */

സ്ഥിതം തർക്കം
handle_counted_by_p (വൃക്ഷം ref)
{
  gcc_assert (വൃക്ഷം_CODE (ref) == COMPONENT_REF);
  വൃക്ഷം datum = വൃക്ഷം_OPERAND (ref, 0);
  /* If the component_ref is build for a offsetof, i.e., the datum
     of the component_ref is a indirect_ref of null_pointer_node,
     we should not generate call to .ACCESS_WITH_SIZE.  */
  എങ്കിൽ (വൃക്ഷം_CODE (datum) == INDIRECT_REF
      && വൃക്ഷം_OPERAND (datum, 0) == null_pointer_കണ്ണി)
    തിരികെ അസത്യം;
  എങ്കിൽ (in_typeof || in_alignof)
    തിരികെ അസത്യം;
  തിരികെ സത്യം;
}

/* Given a component ref REF, if there is a counted_by attribute attached,
   issue error when the element_type is a structure or union including a
   flexible array member.  */

സ്ഥിതം ശൂന്യം
check_counted_by_attribute (location_t loc, വൃക്ഷം ref)
{
  വൃക്ഷം subdatum = വൃക്ഷം_OPERAND (ref, 1);
  വൃക്ഷം sub_type = വൃക്ഷം_TYPE (subdatum);

  എങ്കിൽ (!flexible_array_member_type_p (sub_type)
      && വൃക്ഷം_CODE (sub_type) != POINTER_TYPE)
    തിരികെ;

  വൃക്ഷം element_type = വൃക്ഷം_TYPE (sub_type);

  വൃക്ഷം attr_counted_by = lookup_attribute ("counted_by",
					   DECL_ATTRIBUTES (subdatum));
  എങ്കിൽ (attr_counted_by)
    {
      /* Issue error when the element_type is a structure or
	union including a flexible array member.  */
      എങ്കിൽ (RECORD_OR_UNION_TYPE_P (element_type)
	  && TYPE_INCLUDES_FLEXARRAY (element_type))
	{
	  error_at (loc,
		    "%<counted_by%> attribute is not allowed for a pointer to"
		    " structure or union with flexible array member");
	  തിരികെ;
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

സ്ഥിതം വൃക്ഷം
build_counted_by_ref (വൃക്ഷം datum, വൃക്ഷം subdatum,
		      വൃക്ഷം *counted_by_type)
{
  വൃക്ഷം sub_type = വൃക്ഷം_TYPE (subdatum);
  എങ്കിൽ (!flexible_array_member_type_p (sub_type)
      && വൃക്ഷം_CODE (sub_type) != POINTER_TYPE)
    തിരികെ NULL_വൃക്ഷം;

  വൃക്ഷം attr_counted_by = lookup_attribute ("counted_by",
					   DECL_ATTRIBUTES (subdatum));
  എങ്കിൽ (!attr_counted_by)
    തിരികെ NULL_വൃക്ഷം;

  വൃക്ഷം counted_by_ref = NULL_വൃക്ഷം;
  *counted_by_type = NULL_വൃക്ഷം;

  വൃക്ഷം type = വൃക്ഷം_TYPE (datum);

  /* If the type of the containing structure is an anonymous struct/union,
     and this anonymous struct/union is not a root type, get the first
     outer named structure/union type.  */
  ആകുമ്പോൾ (വൃക്ഷം_CODE (datum) == COMPONENT_REF
	 && c_type_tag (type) == NULL_വൃക്ഷം
	 && DECL_NAME (വൃക്ഷം_OPERAND (datum, 1)) == NULL_വൃക്ഷം)
    {
      datum = വൃക്ഷം_OPERAND (datum, 0);
      type = വൃക്ഷം_TYPE (datum);
    }

  വൃക്ഷം field_id = വൃക്ഷം_മൂല്യം (വൃക്ഷം_മൂല്യം (attr_counted_by));
  വൃക്ഷം counted_by_field = lookup_field (type, field_id);
  gcc_assert (counted_by_field);

  വൃക്ഷം counted_by_subdatum;
  ചെയ്യുക
    {
      counted_by_subdatum = വൃക്ഷം_മൂല്യം (counted_by_field);
      /* Get the TYPE of the counted_by field.  */
      *counted_by_type = വൃക്ഷം_TYPE (counted_by_subdatum);

      counted_by_ref
	= build3 (COMPONENT_REF, വൃക്ഷം_TYPE (counted_by_subdatum),
		  datum, counted_by_subdatum, NULL_വൃക്ഷം);

      datum = counted_by_ref;
      counted_by_field = വൃക്ഷം_CHAIN (counted_by_field);
    }
  ആകുമ്പോൾ (counted_by_field);

  counted_by_ref = build_fold_addr_വ്യഞ്ജകം (counted_by_ref);
  തിരികെ counted_by_ref;
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
സ്ഥിതം വൃക്ഷം
build_access_with_size_for_counted_by (location_t loc, വൃക്ഷം ref,
				       വൃക്ഷം counted_by_ref,
				       വൃക്ഷം counted_by_type)
{
  gcc_assert (flexible_array_member_type_p (വൃക്ഷം_TYPE (ref))
	      || വൃക്ഷം_CODE (വൃക്ഷം_TYPE (ref)) == POINTER_TYPE);

  തർക്കം is_fam = flexible_array_member_type_p (വൃക്ഷം_TYPE (ref));

  /* The result type of the call is a pointer to the flexible array type;
     or is the original pointer type to the pointer field with counted_by.  */
  വൃക്ഷം result_type = is_fam ? c_build_pointer_type (വൃക്ഷം_TYPE (ref))
		     : വൃക്ഷം_TYPE (ref);

  വൃക്ഷം element_type = വൃക്ഷം_TYPE (വൃക്ഷം_TYPE (ref));
  വൃക്ഷം element_size = VOID_TYPE_P (element_type)
		      ? size_one_കണ്ണി
		      : TYPE_SIZE_UNIT (element_type);
  എങ്കിൽ (element_size == NULL_വൃക്ഷം)
    തിരികെ ref;

  വൃക്ഷം first_param = is_fam
		     ? c_fully_fold (array_to_pointer_conversion (loc, ref),
				     അസത്യം, ശൂന്യ)
		     : c_fully_fold (ref, അസത്യം, ശൂന്യ);
  വൃക്ഷം second_param
    = c_fully_fold (counted_by_ref, അസത്യം, ശൂന്യ);
  വൃക്ഷം third_param = build_int_cst (c_build_pointer_type (counted_by_type), 0);

  വൃക്ഷം call
    = build_call_വ്യഞ്ജകം_internal_loc (loc, IFN_ACCESS_WITH_SIZE,
				    result_type, 4,
				    first_param,
				    second_param,
				    third_param,
				    element_size);

  /* Wrap the call with an INDIRECT_REF with the flexible array type.  */
  എങ്കിൽ (is_fam)
    call = build1 (INDIRECT_REF, വൃക്ഷം_TYPE (ref), call);
  SET_വ്യഞ്ജകം_LOCATION (call, loc);
  തിരികെ call;
}

/* For the COMPONENT_REF ref, check whether it has a counted_by attribute,
   if so, wrap this COMPONENT_REF with the corresponding CALL to the
   function .ACCESS_WITH_SIZE.
   Otherwise, return the ref itself.  */

വൃക്ഷം
handle_counted_by_for_component_ref (location_t loc, വൃക്ഷം ref)
{
  gcc_assert (വൃക്ഷം_CODE (ref) == COMPONENT_REF);
  വൃക്ഷം datum = വൃക്ഷം_OPERAND (ref, 0);
  വൃക്ഷം subdatum = വൃക്ഷം_OPERAND (ref, 1);
  വൃക്ഷം counted_by_type = NULL_വൃക്ഷം;

  എങ്കിൽ (!(flexible_array_member_type_p (വൃക്ഷം_TYPE (ref))
	|| വൃക്ഷം_CODE (വൃക്ഷം_TYPE (ref)) == POINTER_TYPE))
    തിരികെ ref;

  വൃക്ഷം counted_by_ref = build_counted_by_ref (datum, subdatum,
					      &counted_by_type);
  എങ്കിൽ (counted_by_ref)
    ref = build_access_with_size_for_counted_by (loc, ref,
						 counted_by_ref,
						 counted_by_type);
  തിരികെ ref;
}

/* Make an expression to refer to the COMPONENT field of structure or
   union value DATUM.  COMPONENT is an IDENTIFIER_NODE.  LOC is the
   location of the COMPONENT_REF.  COMPONENT_LOC is the location
   of COMPONENT.  ARROW_LOC is the location of the first -> operand if
   it is from -> operator.
   If HANDLE_COUNTED_BY is true, check the counted_by attribute and generate
   a call to .ACCESS_WITH_SIZE.  Otherwise, ignore the attribute.  */

വൃക്ഷം
build_component_ref (location_t loc, വൃക്ഷം datum, വൃക്ഷം component,
		     location_t component_loc, location_t arrow_loc)
{
  വൃക്ഷം type = വൃക്ഷം_TYPE (datum);
  എണ്ണൽ വൃക്ഷം_code code = വൃക്ഷം_CODE (type);
  വൃക്ഷം field = ശൂന്യ;
  വൃക്ഷം ref;
  തർക്കം datum_lvalue = lvalue_p (datum);

  എങ്കിൽ (!objc_is_public (datum, component))
    തിരികെ error_mark_കണ്ണി;

  /* Detect Objective-C property syntax object.property.  */
  എങ്കിൽ (c_dialect_objc ()
      && (ref = objc_maybe_build_component_ref (datum, component)))
    തിരികെ ref;

  /* See if there is a field or component with name COMPONENT.  */

  എങ്കിൽ (code == RECORD_TYPE || code == UNION_TYPE)
    {
      എങ്കിൽ (!COMPLETE_TYPE_P (type))
	{
	  c_incomplete_type_error (loc, NULL_വൃക്ഷം, type);
	  തിരികെ error_mark_കണ്ണി;
	}

      field = lookup_field (type, component);

      എങ്കിൽ (!field)
	{
	  വൃക്ഷം guessed_id = lookup_field_fuzzy (type, component);
	  എങ്കിൽ (guessed_id)
	    {
	      /* Attempt to provide a fixit replacement hint, if
		 we have a valid range for the component.  */
	      location_t reported_loc
		= (component_loc != UNKNOWN_LOCATION) ? component_loc : loc;
	      gcc_rich_location rich_loc (reported_loc);
	      എങ്കിൽ (component_loc != UNKNOWN_LOCATION)
		rich_loc.add_fixit_misspelled_id (component_loc, guessed_id);
	      error_at (&rich_loc,
			"%qT has no member named %qE; did you mean %qE?",
			type, component, guessed_id);
	    }
	  അല്ലെങ്കിൽ
	    error_at (loc, "%qT has no member named %qE", type, component);
	  തിരികെ error_mark_കണ്ണി;
	}

      /* Accessing elements of atomic structures or unions is undefined
	 behavior (C11 6.5.2.3#5).  */
      എങ്കിൽ (TYPE_ATOMIC (type) && c_inhibit_evaluation_warnings == 0)
	{
	  എങ്കിൽ (code == RECORD_TYPE)
	    warning_at (loc, 0, "accessing a member %qE of an atomic "
			"structure %qE", component, datum);
	  അല്ലെങ്കിൽ
	    warning_at (loc, 0, "accessing a member %qE of an atomic "
			"union %qE", component, datum);
	}

      /* Chain the COMPONENT_REFs if necessary down to the FIELD.
	 This might be better solved in future the way the C++ front
	 end does it - by giving the anonymous entities each a
	 separate name and type, and then have build_component_ref
	 recursively call itself.  We can't do that here.  */
      ചെയ്യുക
	{
	  വൃക്ഷം subdatum = വൃക്ഷം_മൂല്യം (field);
	  പൂർണ്ണസംഖ്യ quals;
	  വൃക്ഷം subtype;
	  തർക്കം use_datum_quals;

	  എങ്കിൽ (വൃക്ഷം_TYPE (subdatum) == error_mark_കണ്ണി)
	    തിരികെ error_mark_കണ്ണി;

	  /* If this is an rvalue, it does not have qualifiers in C
	     standard terms and we must avoid propagating such
	     qualifiers down to a non-lvalue array that is then
	     converted to a pointer.  */
	  use_datum_quals = (datum_lvalue
			     || വൃക്ഷം_CODE (വൃക്ഷം_TYPE (subdatum)) != ARRAY_TYPE);

	  quals = TYPE_QUALS (strip_array_types (വൃക്ഷം_TYPE (subdatum)));
	  എങ്കിൽ (use_datum_quals)
	    quals |= TYPE_QUALS (വൃക്ഷം_TYPE (datum));
	  subtype = c_build_qualified_type (വൃക്ഷം_TYPE (subdatum), quals);

	  ref = build3 (COMPONENT_REF, subtype, datum, subdatum,
			NULL_വൃക്ഷം);
	  SET_വ്യഞ്ജകം_LOCATION (ref, loc);

	  check_counted_by_attribute (loc, ref);

	  എങ്കിൽ (വൃക്ഷം_READONLY (subdatum)
	      || (use_datum_quals && വൃക്ഷം_READONLY (datum)))
	    വൃക്ഷം_READONLY (ref) = 1;
	  എങ്കിൽ (വൃക്ഷം_THIS_VOLATILE (subdatum)
	      || (use_datum_quals && വൃക്ഷം_THIS_VOLATILE (datum)))
	    വൃക്ഷം_THIS_VOLATILE (ref) = 1;

	  എങ്കിൽ (വൃക്ഷം_UNAVAILABLE (subdatum))
	    error_unavailable_use (subdatum, NULL_വൃക്ഷം);
	  അല്ലെങ്കിൽ എങ്കിൽ (വൃക്ഷം_DEPRECATED (subdatum))
	    warn_deprecated_use (subdatum, NULL_വൃക്ഷം);

	  datum = ref;

	  field = വൃക്ഷം_CHAIN (field);
	}
      ആകുമ്പോൾ (field);

      തിരികെ ref;
    }
  അല്ലെങ്കിൽ എങ്കിൽ (should_suggest_deref_p (type))
    {
      /* Special-case the error message for "ptr.field" for the case
	 where the user has confused "." vs "->".  */
      rich_location richloc (വരി_table, loc);
      എങ്കിൽ (INDIRECT_REF_P (datum) && arrow_loc != UNKNOWN_LOCATION)
	{
	  richloc.add_fixit_തിരുകുക_before (arrow_loc, "(*");
	  richloc.add_fixit_തിരുകുക_after (arrow_loc, ")");
	  error_at (&richloc,
		    "%qE is a pointer to pointer; did you mean to dereference "
		    "it before applying %<->%> to it?",
		    വൃക്ഷം_OPERAND (datum, 0));
	}
      അല്ലെങ്കിൽ
	{
	  /* "loc" should be the "." token.  */
	  richloc.add_fixit_replace ("->");
	  error_at (&richloc,
		    "%qE is a pointer; did you mean to use %<->%>?",
		    datum);
	}
      തിരികെ error_mark_കണ്ണി;
    }
  അല്ലെങ്കിൽ എങ്കിൽ (code != ERROR_MARK)
    error_at (loc,
	      "request for member %qE in something not a structure or union",
	      component);

  തിരികെ error_mark_കണ്ണി;
}

/* Given an expression PTR for a pointer, return an expression
   for the value pointed to.
   ERRORSTRING is the name of the operator to appear in error messages.

   LOC is the location to use for the generated tree.  */

വൃക്ഷം
build_indirect_ref (location_t loc, വൃക്ഷം ptr, ref_operator errstring)
{
  വൃക്ഷം pointer = default_conversion (ptr);
  വൃക്ഷം type = വൃക്ഷം_TYPE (pointer);
  വൃക്ഷം ref;

  എങ്കിൽ (വൃക്ഷം_CODE (type) == POINTER_TYPE)
    {
      എങ്കിൽ (CONVERT_വ്യഞ്ജകം_P (pointer)
          || വൃക്ഷം_CODE (pointer) == VIEW_CONVERT_വ്യഞ്ജകം)
	{
	  /* If a warning is issued, mark it to avoid duplicates from
	     the backend.  This only needs to be done at
	     warn_strict_aliasing > 2.  */
	  എങ്കിൽ (warn_strict_aliasing > 2)
	    എങ്കിൽ (strict_aliasing_warning (വ്യഞ്ജകം_LOCATION (pointer),
					 type, വൃക്ഷം_OPERAND (pointer, 0)))
	      suppress_warning (pointer, OPT_Wstrict_aliasing_);
	}

      എങ്കിൽ (വൃക്ഷം_CODE (pointer) == ADDR_വ്യഞ്ജകം
	  && (വൃക്ഷം_TYPE (വൃക്ഷം_OPERAND (pointer, 0))
	      == വൃക്ഷം_TYPE (type)))
	{
	  ref = വൃക്ഷം_OPERAND (pointer, 0);
	  protected_set_വ്യഞ്ജകം_location (ref, loc);
	  തിരികെ ref;
	}
      അല്ലെങ്കിൽ
	{
	  വൃക്ഷം t = വൃക്ഷം_TYPE (type);

	  ref = build1 (INDIRECT_REF, t, pointer);

	  എങ്കിൽ (VOID_TYPE_P (t) && c_inhibit_evaluation_warnings == 0)
	    warning_at (loc, 0, "dereferencing %<void *%> pointer");

	  /* We *must* set TREE_READONLY when dereferencing a pointer to const,
	     so that we get the proper error message if the result is used
	     to assign to.  Also, &* is supposed to be a no-op.
	     And ANSI C seems to specify that the type of the result
	     should be the const type.  */
	  /* A de-reference of a pointer to const is not a const.  It is valid
	     to change it via some other pointer.  */
	  വൃക്ഷം_READONLY (ref) = TYPE_READONLY (t);
	  വൃക്ഷം_SIDE_EFFECTS (ref)
	    = TYPE_VOLATILE (t) || വൃക്ഷം_SIDE_EFFECTS (pointer);
	  വൃക്ഷം_THIS_VOLATILE (ref) = TYPE_VOLATILE (t);
	  protected_set_വ്യഞ്ജകം_location (ref, loc);
	  തിരികെ ref;
	}
    }
  അല്ലെങ്കിൽ എങ്കിൽ (വൃക്ഷം_CODE (pointer) != ERROR_MARK)
    invalid_indirection_error (loc, type, errstring);

  തിരികെ error_mark_കണ്ണി;
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

വൃക്ഷം
build_array_ref (location_t loc, വൃക്ഷം array, വൃക്ഷം index)
{
  വൃക്ഷം ret;
  തർക്കം swapped = അസത്യം;
  എങ്കിൽ (വൃക്ഷം_TYPE (array) == error_mark_കണ്ണി
      || വൃക്ഷം_TYPE (index) == error_mark_കണ്ണി)
    തിരികെ error_mark_കണ്ണി;

  എങ്കിൽ (വൃക്ഷം_CODE (വൃക്ഷം_TYPE (array)) != ARRAY_TYPE
      && വൃക്ഷം_CODE (വൃക്ഷം_TYPE (array)) != POINTER_TYPE
      /* Allow vector[index] but not index[vector].  */
      && !gnu_vector_type_p (വൃക്ഷം_TYPE (array)))
    {
      എങ്കിൽ (വൃക്ഷം_CODE (വൃക്ഷം_TYPE (index)) != ARRAY_TYPE
	  && വൃക്ഷം_CODE (വൃക്ഷം_TYPE (index)) != POINTER_TYPE)
	{
          error_at (loc,
            "subscripted value is neither array nor pointer nor vector");

	  തിരികെ error_mark_കണ്ണി;
	}
      std::swap (array, index);
      swapped = സത്യം;
    }

  എങ്കിൽ (!INTEGRAL_TYPE_P (വൃക്ഷം_TYPE (index)))
    {
      error_at (loc, "array subscript is not an integer");
      തിരികെ error_mark_കണ്ണി;
    }

  എങ്കിൽ (വൃക്ഷം_CODE (വൃക്ഷം_TYPE (വൃക്ഷം_TYPE (array))) == FUNCTION_TYPE)
    {
      error_at (loc, "subscripted value is pointer to function");
      തിരികെ error_mark_കണ്ണി;
    }

  /* ??? Existing practice has been to warn only when the char
     index is syntactically the index, not for char[array].  */
  എങ്കിൽ (!swapped)
     warn_array_subscript_with_type_char (loc, index);

  /* Apply default promotions *after* noticing character types.  */
  index = default_conversion (index);
  എങ്കിൽ (index == error_mark_കണ്ണി)
    തിരികെ error_mark_കണ്ണി;

  gcc_assert (വൃക്ഷം_CODE (വൃക്ഷം_TYPE (index)) == INTEGER_TYPE
	      || വൃക്ഷം_CODE (വൃക്ഷം_TYPE (index)) == BITINT_TYPE);

  തർക്കം was_vector = VECTOR_TYPE_P (വൃക്ഷം_TYPE (array));
  തർക്കം non_lvalue = convert_vector_to_array_for_subscript (loc, &array, index);

  /* We only generate a call to .ACCESS_WITH_SIZE when it is a read.  */
  എങ്കിൽ (വൃക്ഷം_CODE (array) == COMPONENT_REF
      && handle_counted_by_p (array))
    array = handle_counted_by_for_component_ref (loc, array);

  എങ്കിൽ (വൃക്ഷം_CODE (വൃക്ഷം_TYPE (array)) == ARRAY_TYPE)
    {
      വൃക്ഷം rval, type;

      /* An array that is indexed by a non-constant
	 cannot be stored in a register; we must be able to do
	 address arithmetic on its address.
	 Likewise an array of elements of variable size.  */
      എങ്കിൽ (വൃക്ഷം_CODE (index) != INTEGER_CST
	  || (COMPLETE_TYPE_P (വൃക്ഷം_TYPE (വൃക്ഷം_TYPE (array)))
	      && വൃക്ഷം_CODE (TYPE_SIZE (വൃക്ഷം_TYPE (വൃക്ഷം_TYPE (array)))) != INTEGER_CST))
	{
	  എങ്കിൽ (!c_mark_addressable (array, സത്യം, സത്യം))
	    തിരികെ error_mark_കണ്ണി;
	}
      /* An array that is indexed by a constant value which is not within
	 the array bounds cannot be stored in a register either; because we
	 would get a crash in store_bit_field/extract_bit_field when trying
	 to access a non-existent part of the register.  */
      എങ്കിൽ (വൃക്ഷം_CODE (index) == INTEGER_CST
	  && TYPE_DOMAIN (വൃക്ഷം_TYPE (array))
	  && !int_fits_type_p (index, TYPE_DOMAIN (വൃക്ഷം_TYPE (array))))
	{
	  എങ്കിൽ (!c_mark_addressable (array, അസത്യം, സത്യം))
	    തിരികെ error_mark_കണ്ണി;
	  /* ISO C2Y disallows a negative integer constant expression index
	     when array subscripting has an operand of array type.  */
	  എങ്കിൽ (flag_isoc2y
	      && !വൃക്ഷം_OVERFLOW (index)
	      && വൃക്ഷം_int_cst_sgn (index) < 0)
	    error_at (loc, "array subscript is negative");
	}

      എങ്കിൽ ((pedantic || warn_c90_c99_compat || warn_c23_c2y_compat)
	  && ! was_vector)
	{
	  വൃക്ഷം foo = array;
	  ആകുമ്പോൾ (വൃക്ഷം_CODE (foo) == COMPONENT_REF)
	    foo = വൃക്ഷം_OPERAND (foo, 0);
	  എങ്കിൽ ((VAR_P (foo) && C_DECL_REGISTER (foo))
	      || (വൃക്ഷം_CODE (foo) == COMPOUND_LITERAL_വ്യഞ്ജകം
		  && C_DECL_REGISTER (COMPOUND_LITERAL_വ്യഞ്ജകം_DECL (foo))))
	    pedwarn_c23 (loc, OPT_Wpedantic,
			 "ISO C forbids subscripting %<register%> array "
			 "before C2Y");
	  അല്ലെങ്കിൽ എങ്കിൽ (!lvalue_p (foo))
	    pedwarn_c90 (loc, OPT_Wpedantic,
			 "ISO C90 forbids subscripting non-lvalue "
			 "array");
	}

      എങ്കിൽ (വൃക്ഷം_CODE (വൃക്ഷം_TYPE (index)) == BITINT_TYPE
	  && TYPE_PRECISION (വൃക്ഷം_TYPE (index)) > TYPE_PRECISION (sizetype))
	index = fold_convert (sizetype, index);

      type = വൃക്ഷം_TYPE (വൃക്ഷം_TYPE (array));
      rval = build4 (ARRAY_REF, type, array, index, NULL_വൃക്ഷം, NULL_വൃക്ഷം);
      /* Array ref is const/volatile if the array elements are
	 or if the array is.  */
      വൃക്ഷം_READONLY (rval)
	|= (TYPE_READONLY (വൃക്ഷം_TYPE (വൃക്ഷം_TYPE (array)))
	    | വൃക്ഷം_READONLY (array));
      വൃക്ഷം_SIDE_EFFECTS (rval)
	|= (TYPE_VOLATILE (വൃക്ഷം_TYPE (വൃക്ഷം_TYPE (array)))
	    | വൃക്ഷം_SIDE_EFFECTS (array));
      വൃക്ഷം_THIS_VOLATILE (rval)
	|= (TYPE_VOLATILE (വൃക്ഷം_TYPE (വൃക്ഷം_TYPE (array)))
	    /* This was added by rms on 16 Nov 91.
	       It fixes  vol struct foo *a;  a->elts[1]
	       in an inline function.
	       Hope it doesn't break something else.  */
	    | വൃക്ഷം_THIS_VOLATILE (array));
      ret = require_complete_type (loc, rval);
      protected_set_വ്യഞ്ജകം_location (ret, loc);
      എങ്കിൽ (non_lvalue)
	ret = non_lvalue_loc (loc, ret);
      തിരികെ ret;
    }
  അല്ലെങ്കിൽ
    {
      വൃക്ഷം ar = default_conversion (array);

      എങ്കിൽ (ar == error_mark_കണ്ണി)
	തിരികെ ar;

      gcc_assert (വൃക്ഷം_CODE (വൃക്ഷം_TYPE (ar)) == POINTER_TYPE);
      gcc_assert (വൃക്ഷം_CODE (വൃക്ഷം_TYPE (വൃക്ഷം_TYPE (ar))) != FUNCTION_TYPE);

      ret = build_indirect_ref (loc, build_ദ്വിമാന_op (loc, PLUS_വ്യഞ്ജകം, ar,
						      index, അസത്യം),
				RO_ARRAY_INDEXING);
      എങ്കിൽ (non_lvalue)
	ret = non_lvalue_loc (loc, ret);
      തിരികെ ret;
    }
}

/* Build an OpenMP array section reference, creating an exact type for the
   resulting expression based on the element type and bounds if possible.  If
   we have variable bounds, create an incomplete array type for the result
   instead.  */

വൃക്ഷം
build_omp_array_section (location_t loc, വൃക്ഷം array, വൃക്ഷം index, വൃക്ഷം length)
{
  വൃക്ഷം type = വൃക്ഷം_TYPE (array);
  gcc_assert (type);

  വൃക്ഷം sectype, eltype = വൃക്ഷം_TYPE (type);

  /* It's not an array or pointer type.  Just reuse the type of the original
     expression as the type of the array section (an error will be raised
     anyway, later).  */
  എങ്കിൽ (eltype == NULL_വൃക്ഷം || error_operand_p (eltype))
    sectype = വൃക്ഷം_TYPE (array);
  അല്ലെങ്കിൽ
    {
      വൃക്ഷം idxtype = NULL_വൃക്ഷം;

      എങ്കിൽ (index != NULL_വൃക്ഷം
	  && length != NULL_വൃക്ഷം
	  && INTEGRAL_TYPE_P (വൃക്ഷം_TYPE (index))
	  && INTEGRAL_TYPE_P (വൃക്ഷം_TYPE (length)))
	{
	  വൃക്ഷം താഴെയുള്ള = fold_convert (sizetype, index);
	  വൃക്ഷം മുകളിലെ = fold_convert (sizetype, length);
	  മുകളിലെ = size_binop (PLUS_വ്യഞ്ജകം, താഴെയുള്ള, മുകളിലെ);
	  മുകളിലെ = size_binop (MINUS_വ്യഞ്ജകം, മുകളിലെ, size_one_കണ്ണി);
	  idxtype = build_range_type (sizetype, താഴെയുള്ള, മുകളിലെ);
	}
      അല്ലെങ്കിൽ എങ്കിൽ ((index == NULL_വൃക്ഷം || integer_zerop (index))
	       && length != NULL_വൃക്ഷം
	       && INTEGRAL_TYPE_P (വൃക്ഷം_TYPE (length)))
	idxtype = build_index_type (length);

      gcc_assert (!error_operand_p (idxtype));

      sectype = c_build_array_type (eltype, idxtype);
    }

  തിരികെ build3_loc (loc, OMP_ARRAY_SECTION, sectype, array, index, length);
}


/* Record that REF is used.  This is relevant for undeclared static
   function and declarations referenced from a non-local context.
   ADDRESS indicates whether the address is taken.  */

ശൂന്യം
mark_decl_used (വൃക്ഷം ref, തർക്കം address)
{
  എങ്കിൽ (!ref || !DECL_P (ref) || in_alignof)
    തിരികെ;

  /* Non-file-scope and non-local reference in nested function.  */
  തർക്കം nonloc_p = current_function_decl && DECL_CONTEXT (ref)
		  && DECL_CONTEXT (current_function_decl)
		  && DECL_CONTEXT (ref) != current_function_decl;

  /* An undeclared static function.  */
  തർക്കം static_p = വൃക്ഷം_CODE (ref) == FUNCTION_DECL
		  && DECL_INITIAL (ref) == NULL_വൃക്ഷം
		  && DECL_EXTERNAL (ref)
		  && !വൃക്ഷം_PUBLIC (ref);

  എങ്കിൽ (!static_p && !nonloc_p)
    തിരികെ;

  /* If we may be in an unevaluated context, delay the decision.  */
  എങ്കിൽ (in_sizeof || in_typeof || in_countof || in_generic)
    തിരികെ record_maybe_used_decl (ref, address);

  എങ്കിൽ (static_p)
    C_DECL_USED (ref) = 1;

  എങ്കിൽ (nonloc_p && (VAR_OR_FUNCTION_DECL_P (ref)
		   || വൃക്ഷം_CODE (ref) == PARM_DECL))
    DECL_NONLOCAL (ref) = 1;

  /* Nothing to do anymore.  */
  എങ്കിൽ (!nonloc_p || C_FUNC_NONLOCAL_CONTEXT (current_function_decl))
    തിരികെ;

  /* Filter out the cases where referencing a non-local variable does not
     require a non-local context passed via the static chain.  */
  എങ്കിൽ (!c_type_variably_modified_p (വൃക്ഷം_TYPE (ref)))
    തിരഞ്ഞെടുപ്പ് (വൃക്ഷം_CODE (ref))
      {
      അവസ്ഥ FUNCTION_DECL:
	/* Use of another local function that requires no context is ok.  */
	എങ്കിൽ (!C_FUNC_NONLOCAL_CONTEXT (ref) && DECL_INITIAL (ref))
	  തിരികെ;
	നിർത്തുക;
      അവസ്ഥ VAR_DECL:
	/* Static variables and constexpr are ok, but for the later only
	   when the address is not taken.  */
	എങ്കിൽ (വൃക്ഷം_STATIC (ref) || (C_DECL_DECLARED_CONSTEXPR (ref) && !address))
	  തിരികെ;
	നിർത്തുക;
      അവസ്ഥ TYPE_DECL:
	/* A typedef is ok when not for a variably-modified type. */
	തിരികെ;
      അവസ്ഥ CONST_DECL:
	/* An enumeration constant is ok. */
	തിരികെ;
      അവസ്ഥ PARM_DECL:
	നിർത്തുക;
      അവസ്ഥ LABEL_DECL:
	നിർത്തുക;
      സ്ഥിരസ്ഥിതി:
	gcc_unreachable ();
    }

  /* Mark all parent functions up to the nesting level of the variable as
     as needing the non-local context.  */
  വേണ്ടി (വൃക്ഷം cont = current_function_decl; cont; cont = DECL_CONTEXT (cont))
    {
      എങ്കിൽ (cont == DECL_CONTEXT (ref))
	നിർത്തുക;

      /* There should not be any other type of context used for function
	 except TRANSLATION_UNIT_DECL which we should be able to reach.  */
      gcc_checking_assert (വൃക്ഷം_CODE (cont) == FUNCTION_DECL);

      എങ്കിൽ (വൃക്ഷം_CODE (cont) == FUNCTION_DECL)
	C_FUNC_NONLOCAL_CONTEXT (cont) = 1;
    }
}


/* Build an external reference to identifier ID.  FUN indicates
   whether this will be used for a function call.  LOC is the source
   location of the identifier.  This sets *TYPE to the type of the
   identifier, which is not the same as the type of the returned value
   for CONST_DECLs defined as enum constants.  If the type of the
   identifier is not available, *TYPE is set to NULL.  */
വൃക്ഷം
build_external_ref (location_t loc, വൃക്ഷം id, തർക്കം fun, വൃക്ഷം *type)
{
  വൃക്ഷം ref;
  വൃക്ഷം decl = lookup_name (id);

  /* In Objective-C, an instance variable (ivar) may be preferred to
     whatever lookup_name() found.  */
  decl = objc_lookup_ivar (decl, id);

  *type = ശൂന്യ;
  എങ്കിൽ (decl && decl != error_mark_കണ്ണി)
    {
      ref = decl;
      *type = വൃക്ഷം_TYPE (ref);
      എങ്കിൽ (DECL_P (decl) && C_DECL_UNDERSPECIFIED (decl))
	error_at (loc, "underspecified %qD referenced in its initializer",
		  decl);
    }
  അല്ലെങ്കിൽ എങ്കിൽ (fun)
    /* Implicit function declaration.  */
    ref = implicitly_declare (loc, id);
  അല്ലെങ്കിൽ എങ്കിൽ (decl == error_mark_കണ്ണി)
    /* Don't complain about something that's already been
       complained about.  */
    തിരികെ error_mark_കണ്ണി;
  അല്ലെങ്കിൽ
    {
      undeclared_variable (loc, id);
      തിരികെ error_mark_കണ്ണി;
    }

  /* For an OpenMP map clause, we can get better diagnostics for decls with
     unmappable types if we return the decl with an error_mark_node type,
     rather than returning error_mark_node for the decl itself.  */
  എങ്കിൽ (വൃക്ഷം_TYPE (ref) == error_mark_കണ്ണി
      && !c_omp_array_section_p)
    തിരികെ error_mark_കണ്ണി;

  എങ്കിൽ (വൃക്ഷം_UNAVAILABLE (ref))
    error_unavailable_use (ref, NULL_വൃക്ഷം);
  അല്ലെങ്കിൽ എങ്കിൽ (വൃക്ഷം_DEPRECATED (ref))
    warn_deprecated_use (ref, NULL_വൃക്ഷം);

  /* Recursive call does not count as usage.  */
  എങ്കിൽ (ref != current_function_decl)
    {
      വൃക്ഷം_USED (ref) = 1;
    }

  mark_decl_used (ref, അസത്യം);

  എങ്കിൽ (വൃക്ഷം_CODE (ref) == CONST_DECL)
    {
      used_types_തിരുകുക (വൃക്ഷം_TYPE (ref));

      എങ്കിൽ (warn_cxx_compat
	  && വൃക്ഷം_CODE (വൃക്ഷം_TYPE (ref)) == ENUMERAL_TYPE
	  && C_TYPE_DEFINED_IN_STRUCT (വൃക്ഷം_TYPE (ref)))
	{
	  warning_at (loc, OPT_Wc___compat,
		      "enum constant defined in struct or union "
		      "is not visible in C++");
	  inform (DECL_SOURCE_LOCATION (ref), "enum constant defined here");
	}

      ref = DECL_INITIAL (ref);
      വൃക്ഷം_CONSTANT (ref) = 1;
    }
  /* C99 6.7.4p3: An inline definition of a function with external
     linkage ... shall not contain a reference to an identifier with
     internal linkage.  */
  അല്ലെങ്കിൽ എങ്കിൽ (current_function_decl != NULL_വൃക്ഷം
	   && DECL_DECLARED_INLINE_P (current_function_decl)
	   && DECL_EXTERNAL (current_function_decl)
	   && VAR_OR_FUNCTION_DECL_P (ref)
	   && (!VAR_P (ref) || വൃക്ഷം_STATIC (ref))
	   && ! വൃക്ഷം_PUBLIC (ref)
	   && DECL_CONTEXT (ref) != current_function_decl)
    record_inline_static (loc, current_function_decl, ref,
			  csi_internal);

  തിരികെ ref;
}

സ്ഥിതം ഘടന maybe_used_decl *maybe_used_decls;

/* Record that DECL, a reference seen inside sizeof or typeof or _Countof or
   _Generic, might be used if the operand of sizeof is a VLA type or the
   operand of typeof is a variably modified type or the operand of _Countof has
   a variable number of elements or the operand of _Generic is the one selected
   as the result.  */

സ്ഥിതം ശൂന്യം
record_maybe_used_decl (വൃക്ഷം decl, തർക്കം address)
{
  ഘടന maybe_used_decl *t = XOBNEW (&parser_obstack, ഘടന maybe_used_decl);
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

ശൂന്യം
എടുക്കുക_maybe_used (തർക്കം used)
{
  ഘടന maybe_used_decl *p = maybe_used_decls;
  പൂർണ്ണസംഖ്യ cur_level = in_sizeof + in_typeof + in_countof + in_generic;
  ആകുമ്പോൾ (p && p->level > cur_level)
    {
      എങ്കിൽ (used)
	{
	  എങ്കിൽ (cur_level == 0)
	    mark_decl_used (p->decl, p->address);
	  അല്ലെങ്കിൽ
	    p->level = cur_level;
	}
      p = p->next;
    }
  എങ്കിൽ (!used || cur_level == 0)
    maybe_used_decls = p;
}

/* Pop the stack of decls possibly used inside sizeof or typeof or _Countof or
   _Generic, without acting on them, and return the pointer to the previous top
   of the stack.  This for use at the end of a default generic association when
   it is not yet known whether the expression is used.  If it later turns out
   the expression is used (or treated as used before C23), restore_maybe_used
   should be called on the return value followed by pop_maybe_used (true);
   otherwise, the return value can be discarded.  */

ഘടന maybe_used_decl *
save_maybe_used ()
{
  ഘടന maybe_used_decl *p = maybe_used_decls, *orig = p;
  പൂർണ്ണസംഖ്യ cur_level = in_sizeof + in_typeof + in_countof + in_generic;
  ആകുമ്പോൾ (p && p->level > cur_level)
    p = p->next;
  maybe_used_decls = p;
  തിരികെ orig;
}

/* Restore the stack of decls possibly used inside sizeof or typeof or _Countof
   or _Generic returned by save_maybe_used.  It is required that the stack is
   at exactly the point where it was left by save_maybe_used.  */

ശൂന്യം
restore_maybe_used (ഘടന maybe_used_decl *അട്ടി)
{
  maybe_used_decls = അട്ടി;
}

/* Return the result of sizeof applied to EXPR.  */

ഘടന c_വ്യഞ്ജകം
c_വ്യഞ്ജകം_sizeof_വ്യഞ്ജകം (location_t loc, ഘടന c_വ്യഞ്ജകം വ്യഞ്ജകം)
{
  ഘടന c_വ്യഞ്ജകം ret;
  എങ്കിൽ (വ്യഞ്ജകം.മൂല്യം == error_mark_കണ്ണി)
    {
      ret.മൂല്യം = error_mark_കണ്ണി;
      ret.original_code = ERROR_MARK;
      ret.original_type = ശൂന്യ;
      ret.m_decimal = 0;
      എടുക്കുക_maybe_used (അസത്യം);
    }
  അല്ലെങ്കിൽ
    {
      തർക്കം വ്യഞ്ജകം_const_operands = സത്യം;

      എങ്കിൽ (വൃക്ഷം_CODE (വ്യഞ്ജകം.മൂല്യം) == PARM_DECL
	  && C_ARRAY_PARAMETER (വ്യഞ്ജകം.മൂല്യം))
	{
	  auto_diagnostic_group d;
	  എങ്കിൽ (warning_at (loc, OPT_Wsizeof_array_argument,
			  "%<sizeof%> on array function parameter %qE will "
			  "return size of %qT", വ്യഞ്ജകം.മൂല്യം,
			  വൃക്ഷം_TYPE (വ്യഞ്ജകം.മൂല്യം)))
	    inform (DECL_SOURCE_LOCATION (വ്യഞ്ജകം.മൂല്യം), "declared here");
	}
      വൃക്ഷം folded_വ്യഞ്ജകം = c_fully_fold (വ്യഞ്ജകം.മൂല്യം, require_constant_മൂല്യം,
				       &വ്യഞ്ജകം_const_operands);
      ret.മൂല്യം = c_sizeof (loc, വൃക്ഷം_TYPE (folded_വ്യഞ്ജകം));
      c_last_sizeof_arg = വ്യഞ്ജകം.മൂല്യം;
      c_last_sizeof_loc = loc;
      ret.original_code = SIZEOF_വ്യഞ്ജകം;
      ret.original_type = ശൂന്യ;
      ret.m_decimal = 0;
      എങ്കിൽ (C_TYPE_VARIABLE_SIZE (വൃക്ഷം_TYPE (folded_വ്യഞ്ജകം)))
	{
	  /* sizeof is evaluated when given a vla (C99 6.5.3.4p2).  */
	  ret.മൂല്യം = build2 (C_MAYBE_CONST_വ്യഞ്ജകം, വൃക്ഷം_TYPE (ret.മൂല്യം),
			      folded_വ്യഞ്ജകം, ret.മൂല്യം);
	  C_MAYBE_CONST_വ്യഞ്ജകം_NON_CONST (ret.മൂല്യം) = !വ്യഞ്ജകം_const_operands;
	  SET_വ്യഞ്ജകം_LOCATION (ret.മൂല്യം, loc);
	}
      എടുക്കുക_maybe_used (C_TYPE_VARIABLE_SIZE (വൃക്ഷം_TYPE (folded_വ്യഞ്ജകം)));
    }
  തിരികെ ret;
}

/* Return the result of sizeof applied to T, a structure for the type
   name passed to sizeof (rather than the type itself).  LOC is the
   location of the original expression.  */

ഘടന c_വ്യഞ്ജകം
c_വ്യഞ്ജകം_sizeof_type (location_t loc, ഘടന c_type_name *t)
{
  വൃക്ഷം type;
  ഘടന c_വ്യഞ്ജകം ret;
  വൃക്ഷം type_വ്യഞ്ജകം = NULL_വൃക്ഷം;
  തർക്കം type_വ്യഞ്ജകം_const = സത്യം;
  type = groktypename (t, &type_വ്യഞ്ജകം, &type_വ്യഞ്ജകം_const);
  ret.മൂല്യം = c_sizeof (loc, type);
  c_last_sizeof_arg = type;
  c_last_sizeof_loc = loc;
  ret.original_code = SIZEOF_വ്യഞ്ജകം;
  ret.original_type = ശൂന്യ;
  ret.m_decimal = 0;
  എങ്കിൽ (type == error_mark_കണ്ണി)
    {
      ret.മൂല്യം = error_mark_കണ്ണി;
      ret.original_code = ERROR_MARK;
    }
  അല്ലെങ്കിൽ
  എങ്കിൽ ((type_വ്യഞ്ജകം || വൃക്ഷം_CODE (ret.മൂല്യം) == INTEGER_CST)
      && C_TYPE_VARIABLE_SIZE (type))
    {
      /* If the type is a [*] array, it is a VLA but is represented as
	 having a size of zero.  In such a case we must ensure that
	 the result of sizeof does not get folded to a constant by
	 c_fully_fold, because if the size is evaluated the result is
	 not constant and so constraints on zero or negative size
	 arrays must not be applied when this sizeof call is inside
	 another array declarator.  */
      എങ്കിൽ (!type_വ്യഞ്ജകം)
	type_വ്യഞ്ജകം = integer_zero_കണ്ണി;
      ret.മൂല്യം = build2 (C_MAYBE_CONST_വ്യഞ്ജകം, വൃക്ഷം_TYPE (ret.മൂല്യം),
			  type_വ്യഞ്ജകം, ret.മൂല്യം);
      C_MAYBE_CONST_വ്യഞ്ജകം_NON_CONST (ret.മൂല്യം) = !type_വ്യഞ്ജകം_const;
    }
  എടുക്കുക_maybe_used (type != error_mark_കണ്ണി
		  ? C_TYPE_VARIABLE_SIZE (type) : അസത്യം);
  തിരികെ ret;
}

സ്ഥിതം തർക്കം
മുകൾ_array_vla_p (const_വൃക്ഷം type)
{
  എങ്കിൽ (വൃക്ഷം_CODE (type) != ARRAY_TYPE)
    തിരികെ അസത്യം;

  വൃക്ഷം d = TYPE_DOMAIN (type);

  എങ്കിൽ (!d)
    തിരികെ അസത്യം;
  എങ്കിൽ (!TYPE_MAX_മൂല്യം (d))
    തിരികെ അസത്യം;

  തിരികെ വൃക്ഷം_CODE (TYPE_MAX_മൂല്യം (d)) != INTEGER_CST
	 || വൃക്ഷം_CODE (TYPE_MIN_മൂല്യം (d)) != INTEGER_CST;
}

/* Return the result of countof applied to EXPR.  */

ഘടന c_വ്യഞ്ജകം
c_വ്യഞ്ജകം_countof_വ്യഞ്ജകം (location_t loc, ഘടന c_വ്യഞ്ജകം വ്യഞ്ജകം)
{
  ഘടന c_വ്യഞ്ജകം ret;
  എങ്കിൽ (വ്യഞ്ജകം.മൂല്യം == error_mark_കണ്ണി)
    {
      ret.മൂല്യം = error_mark_കണ്ണി;
      ret.original_code = ERROR_MARK;
      ret.original_type = ശൂന്യ;
      ret.m_decimal = 0;
      എടുക്കുക_maybe_used (അസത്യം);
    }
  അല്ലെങ്കിൽ
    {
      തർക്കം വ്യഞ്ജകം_const_operands = സത്യം;

      വൃക്ഷം folded_വ്യഞ്ജകം = c_fully_fold (വ്യഞ്ജകം.മൂല്യം, require_constant_മൂല്യം,
				       &വ്യഞ്ജകം_const_operands);
      ret.മൂല്യം = c_countof_type (loc, വൃക്ഷം_TYPE (folded_വ്യഞ്ജകം));
      c_last_sizeof_arg = വ്യഞ്ജകം.മൂല്യം;
      c_last_sizeof_loc = loc;
      ret.original_code = COUNTOF_വ്യഞ്ജകം;
      ret.original_type = ശൂന്യ;
      ret.m_decimal = 0;
      എങ്കിൽ (മുകൾ_array_vla_p (വൃക്ഷം_TYPE (folded_വ്യഞ്ജകം)))
	{
	  /* countof is evaluated when given a vla.  */
	  ret.മൂല്യം = build2 (C_MAYBE_CONST_വ്യഞ്ജകം, വൃക്ഷം_TYPE (ret.മൂല്യം),
			      folded_വ്യഞ്ജകം, ret.മൂല്യം);
	  C_MAYBE_CONST_വ്യഞ്ജകം_NON_CONST (ret.മൂല്യം) = !വ്യഞ്ജകം_const_operands;
	  SET_വ്യഞ്ജകം_LOCATION (ret.മൂല്യം, loc);
	}
      എടുക്കുക_maybe_used (മുകൾ_array_vla_p (വൃക്ഷം_TYPE (folded_വ്യഞ്ജകം)));
    }
  തിരികെ ret;
}

/* Return the result of countof applied to T, a structure for the type
   name passed to countof (rather than the type itself).  LOC is the
   location of the original expression.  */

ഘടന c_വ്യഞ്ജകം
c_വ്യഞ്ജകം_countof_type (location_t loc, ഘടന c_type_name *t)
{
  വൃക്ഷം type;
  ഘടന c_വ്യഞ്ജകം ret;
  വൃക്ഷം type_വ്യഞ്ജകം = NULL_വൃക്ഷം;
  തർക്കം type_വ്യഞ്ജകം_const = സത്യം;
  type = groktypename (t, &type_വ്യഞ്ജകം, &type_വ്യഞ്ജകം_const);
  ret.മൂല്യം = c_countof_type (loc, type);
  c_last_sizeof_arg = type;
  c_last_sizeof_loc = loc;
  ret.original_code = COUNTOF_വ്യഞ്ജകം;
  ret.original_type = ശൂന്യ;
  ret.m_decimal = 0;
  എങ്കിൽ (type == error_mark_കണ്ണി)
    {
      ret.മൂല്യം = error_mark_കണ്ണി;
      ret.original_code = ERROR_MARK;
    }
  അല്ലെങ്കിൽ
  എങ്കിൽ ((type_വ്യഞ്ജകം || വൃക്ഷം_CODE (ret.മൂല്യം) == INTEGER_CST)
      && മുകൾ_array_vla_p (type))
    {
      /* If the type is a [*] array, it is a VLA but is represented as
	 having a size of zero.  In such a case we must ensure that
	 the result of countof does not get folded to a constant by
	 c_fully_fold, because if the number of elements is evaluated
	 the result is not constant and so
	 constraints on zero or negative size arrays must not be applied
	 when this countof call is inside another array declarator.  */
      എങ്കിൽ (!type_വ്യഞ്ജകം)
	type_വ്യഞ്ജകം = integer_zero_കണ്ണി;
      ret.മൂല്യം = build2 (C_MAYBE_CONST_വ്യഞ്ജകം, വൃക്ഷം_TYPE (ret.മൂല്യം),
			  type_വ്യഞ്ജകം, ret.മൂല്യം);
      C_MAYBE_CONST_വ്യഞ്ജകം_NON_CONST (ret.മൂല്യം) = !type_വ്യഞ്ജകം_const;
    }
  എടുക്കുക_maybe_used (type != error_mark_കണ്ണി ? മുകൾ_array_vla_p (type) : അസത്യം);
  തിരികെ ret;
}

/* Return the result of maxof applied to T, a structure for the type
   name passed to maxof (rather than the type itself).  LOC is the
   location of the original expression.  */

ഘടന c_വ്യഞ്ജകം
c_വ്യഞ്ജകം_maxof_type (location_t loc, ഘടന c_type_name *t)
{
  വൃക്ഷം type;
  ഘടന c_വ്യഞ്ജകം ret;
  വൃക്ഷം type_വ്യഞ്ജകം = NULL_വൃക്ഷം;
  തർക്കം type_വ്യഞ്ജകം_const = സത്യം;
  type = groktypename (t, &type_വ്യഞ്ജകം, &type_വ്യഞ്ജകം_const);
  ret.മൂല്യം = c_maxof_type (loc, type);
  c_last_sizeof_arg = type;
  c_last_sizeof_loc = loc;
  ret.original_code = MAXOF_വ്യഞ്ജകം;
  ret.original_type = ശൂന്യ;
  ret.m_decimal = 0;
  എങ്കിൽ (type == error_mark_കണ്ണി)
    {
      ret.മൂല്യം = error_mark_കണ്ണി;
      ret.original_code = ERROR_MARK;
    }
  എടുക്കുക_maybe_used (type != error_mark_കണ്ണി);
  തിരികെ ret;
}

/* Return the result of minof applied to T, a structure for the type
   name passed to minof (rather than the type itself).  LOC is the
   location of the original expression.  */

ഘടന c_വ്യഞ്ജകം
c_വ്യഞ്ജകം_minof_type (location_t loc, ഘടന c_type_name *t)
{
  വൃക്ഷം type;
  ഘടന c_വ്യഞ്ജകം ret;
  വൃക്ഷം type_വ്യഞ്ജകം = NULL_വൃക്ഷം;
  തർക്കം type_വ്യഞ്ജകം_const = സത്യം;
  type = groktypename (t, &type_വ്യഞ്ജകം, &type_വ്യഞ്ജകം_const);
  ret.മൂല്യം = c_minof_type (loc, type);
  c_last_sizeof_arg = type;
  c_last_sizeof_loc = loc;
  ret.original_code = MINOF_വ്യഞ്ജകം;
  ret.original_type = ശൂന്യ;
  ret.m_decimal = 0;
  എങ്കിൽ (type == error_mark_കണ്ണി)
    {
      ret.മൂല്യം = error_mark_കണ്ണി;
      ret.original_code = ERROR_MARK;
    }
  എടുക്കുക_maybe_used (type != error_mark_കണ്ണി);
  തിരികെ ret;
}

/* Build a function call to function FUNCTION with parameters PARAMS.
   The function call is at LOC.
   PARAMS is a list--a chain of TREE_LIST nodes--in which the
   TREE_VALUE of each node is a parameter-expression.
   FUNCTION's data type may be a function type or a pointer-to-function.  */

വൃക്ഷം
build_function_call (location_t loc, വൃക്ഷം function, വൃക്ഷം params)
{
  vec<വൃക്ഷം, va_gc> *v;
  വൃക്ഷം ret;

  vec_alloc (v, list_length (params));
  വേണ്ടി (; params; params = വൃക്ഷം_CHAIN (params))
    v->quick_തള്ളുക (വൃക്ഷം_മൂല്യം (params));
  ret = c_build_function_call_vec (loc, vNULL, function, v, ശൂന്യ);
  vec_free (v);
  തിരികെ ret;
}

/* Give a note about the location of the declaration of DECL,
   or, failing that, a pertinent declaration for FUNCTION_EXPR.  */

സ്ഥിതം ശൂന്യം
inform_declaration (വൃക്ഷം decl, വൃക്ഷം function_വ്യഞ്ജകം)
{
  എങ്കിൽ (decl && (വൃക്ഷം_CODE (decl) != FUNCTION_DECL
	       || !DECL_IS_UNDECLARED_BUILTIN (decl)))
    inform (DECL_SOURCE_LOCATION (decl), "declared here");
  അല്ലെങ്കിൽ എങ്കിൽ (function_വ്യഞ്ജകം)
    തിരഞ്ഞെടുപ്പ് (വൃക്ഷം_CODE (function_വ്യഞ്ജകം))
      {
      സ്ഥിരസ്ഥിതി:
	നിർത്തുക;
      അവസ്ഥ COMPONENT_REF:
	/* Show the decl of the pertinent field (e.g. for callback
	   fields in a struct.  */
	{
	  വൃക്ഷം field_decl = വൃക്ഷം_OPERAND (function_വ്യഞ്ജകം, 1);
	  എങ്കിൽ (location_t loc = DECL_SOURCE_LOCATION (field_decl))
	    inform (loc, "declared here");
	}
	നിർത്തുക;
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

വൃക്ഷം
build_function_call_vec (location_t loc, vec<location_t> arg_loc,
			 വൃക്ഷം function, vec<വൃക്ഷം, va_gc> *params,
			 vec<വൃക്ഷം, va_gc> *origtypes, വൃക്ഷം orig_fundecl)
{
  വൃക്ഷം fntype, fundecl = NULL_വൃക്ഷം;
  വൃക്ഷം name = NULL_വൃക്ഷം, result;
  വൃക്ഷം tem;
  പൂർണ്ണസംഖ്യ nargs;
  വൃക്ഷം *argarray;


  /* Strip NON_LVALUE_EXPRs, etc., since we aren't using as an lvalue.  */
  STRIP_TYPE_NOPS (function);

  /* Convert anything with function type to a pointer-to-function.  */
  എങ്കിൽ (വൃക്ഷം_CODE (function) == FUNCTION_DECL)
    {
      name = DECL_NAME (function);

      എങ്കിൽ (flag_tm)
	tm_malloc_replacement (function);
      fundecl = function;
      എങ്കിൽ (!orig_fundecl)
	orig_fundecl = fundecl;
      /* Atomic functions have type checking/casting already done.  They are
	 often rewritten and don't match the original parameter list.  */
      എങ്കിൽ (name && startswith (IDENTIFIER_POINTER (name), "__atomic_"))
        origtypes = ശൂന്യ;
    }
  എങ്കിൽ (വൃക്ഷം_CODE (വൃക്ഷം_TYPE (function)) == FUNCTION_TYPE)
    function = function_to_pointer_conversion (loc, function);

  /* For Objective-C, convert any calls via a cast to OBJC_TYPE_REF
     expressions, like those used for ObjC messenger dispatches.  */
  എങ്കിൽ (params && !params->is_empty ())
    function = objc_rewrite_function_call (function, (*params)[0]);

  function = c_fully_fold (function, അസത്യം, ശൂന്യ);

  fntype = വൃക്ഷം_TYPE (function);

  എങ്കിൽ (വൃക്ഷം_CODE (fntype) == ERROR_MARK)
    തിരികെ error_mark_കണ്ണി;

  എങ്കിൽ (!(വൃക്ഷം_CODE (fntype) == POINTER_TYPE
	&& വൃക്ഷം_CODE (വൃക്ഷം_TYPE (fntype)) == FUNCTION_TYPE))
    {
      എങ്കിൽ (!flag_diagnostics_show_caret && !STATEMENT_CLASS_P (function))
	error_at (loc,
		  "called object %qE is not a function or function pointer",
		  function);
      അല്ലെങ്കിൽ എങ്കിൽ (DECL_P (function))
	{
	  auto_diagnostic_group d;
	  error_at (loc,
		    "called object %qD is not a function or function pointer",
		    function);
	  inform_declaration (function, NULL_വൃക്ഷം);
	}
      അല്ലെങ്കിൽ
	error_at (loc,
		  "called object is not a function or function pointer");
      തിരികെ error_mark_കണ്ണി;
    }

  എങ്കിൽ (fundecl && വൃക്ഷം_THIS_VOLATILE (fundecl))
    current_function_returns_abnormally = 1;

  /* fntype now gets the type of function pointed to.  */
  fntype = വൃക്ഷം_TYPE (fntype);
  വൃക്ഷം return_type = വൃക്ഷം_TYPE (fntype);

  /* Convert the parameters to the types declared in the
     function prototype, or apply default promotions.  */

  nargs = convert_arguments (loc, arg_loc, fntype, params,
			     origtypes, function, fundecl);
  എങ്കിൽ (nargs < 0)
    തിരികെ error_mark_കണ്ണി;

  /* Check that the function is called through a compatible prototype.
     If it is not, warn.  */
  എങ്കിൽ (CONVERT_വ്യഞ്ജകം_P (function)
      && വൃക്ഷം_CODE (tem = വൃക്ഷം_OPERAND (function, 0)) == ADDR_വ്യഞ്ജകം
      && വൃക്ഷം_CODE (tem = വൃക്ഷം_OPERAND (tem, 0)) == FUNCTION_DECL
      && !comptypes (fntype, വൃക്ഷം_TYPE (tem)))
    {
      /* This situation leads to run-time undefined behavior.  We can't,
	 therefore, simply error unless we can prove that all possible
	 executions of the program must execute the code.  */
      warning_at (loc, 0, "function called through a non-compatible type");

      എങ്കിൽ (VOID_TYPE_P (return_type)
	  && TYPE_QUALS (return_type) != TYPE_UNQUALIFIED)
	pedwarn (loc, 0,
		 "function with qualified void return type called");
     }

  argarray = vec_safe_address (params);

  /* Check that arguments to builtin functions match the expectations.  */
  എങ്കിൽ (fundecl
      && fndecl_built_in_p (fundecl)
      && !check_builtin_function_arguments (loc, arg_loc, fundecl,
					    orig_fundecl, nargs, argarray))
    തിരികെ error_mark_കണ്ണി;

  /* Check that the arguments to the function are valid.  */
  തർക്കം warned_p = check_function_arguments (loc, fundecl, fntype,
					    nargs, argarray, &arg_loc,
					    comptypes);

  എങ്കിൽ (TYPE_QUALS (return_type) != TYPE_UNQUALIFIED
      && !VOID_TYPE_P (return_type))
    return_type = c_build_qualified_type (return_type, TYPE_UNQUALIFIED);
  എങ്കിൽ (name != NULL_വൃക്ഷം
      && startswith (IDENTIFIER_POINTER (name), "__builtin_"))
    {
      എങ്കിൽ (require_constant_മൂല്യം)
	result
	  = fold_build_call_array_initializer_loc (loc, return_type,
						   function, nargs, argarray);
      അല്ലെങ്കിൽ
	result = fold_build_call_array_loc (loc, return_type,
					    function, nargs, argarray);
      എങ്കിൽ (വൃക്ഷം_CODE (result) == NOP_വ്യഞ്ജകം
	  && വൃക്ഷം_CODE (വൃക്ഷം_OPERAND (result, 0)) == INTEGER_CST)
	STRIP_TYPE_NOPS (result);
    }
  അല്ലെങ്കിൽ
    result = build_call_array_loc (loc, return_type,
				   function, nargs, argarray);
  /* If -Wnonnull warning has been diagnosed, avoid diagnosing it again
     later.  */
  എങ്കിൽ (warned_p && വൃക്ഷം_CODE (result) == CALL_വ്യഞ്ജകം)
    suppress_warning (result, OPT_Wnonnull);

  /* In this improbable scenario, a nested function returns a VM type.
     Create a TARGET_EXPR so that the call always has a LHS, much as
     what the C++ FE does for functions returning non-PODs.  */
  എങ്കിൽ (c_type_variably_modified_p (വൃക്ഷം_TYPE (fntype)))
    {
      വൃക്ഷം tmp = create_tmp_var_raw (വൃക്ഷം_TYPE (fntype));
      result = build4 (TARGET_വ്യഞ്ജകം, വൃക്ഷം_TYPE (fntype), tmp, result,
		       NULL_വൃക്ഷം, NULL_വൃക്ഷം);
    }

  എങ്കിൽ (VOID_TYPE_P (വൃക്ഷം_TYPE (result)))
    {
      എങ്കിൽ (TYPE_QUALS (വൃക്ഷം_TYPE (result)) != TYPE_UNQUALIFIED)
	pedwarn (loc, 0,
		 "function with qualified void return type called");
      തിരികെ result;
    }
  തിരികെ require_complete_type (loc, result);
}

/* Like build_function_call_vec, but call also resolve_overloaded_builtin.  */

വൃക്ഷം
c_build_function_call_vec (location_t loc, സ്ഥിരം vec<location_t> &arg_loc,
			   വൃക്ഷം function, vec<വൃക്ഷം, va_gc> *params,
			   vec<വൃക്ഷം, va_gc> *origtypes)
{
  /* Strip NON_LVALUE_EXPRs, etc., since we aren't using as an lvalue.  */
  STRIP_TYPE_NOPS (function);

  /* Convert anything with function type to a pointer-to-function.  */
  എങ്കിൽ (വൃക്ഷം_CODE (function) == FUNCTION_DECL)
    {
      /* Implement type-directed function overloading for builtins.
	 resolve_overloaded_builtin and targetm.resolve_overloaded_builtin
	 handle all the type checking.  The result is a complete expression
	 that implements this function call.  */
      വൃക്ഷം tem = resolve_overloaded_builtin (loc, function, params);
      എങ്കിൽ (tem)
	തിരികെ tem;
    }
  തിരികെ build_function_call_vec (loc, arg_loc, function, params, origtypes);
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

സ്ഥിതം വൃക്ഷം
convert_argument (location_t ploc, വൃക്ഷം function, വൃക്ഷം fundecl,
		  വൃക്ഷം type, വൃക്ഷം origtype, വൃക്ഷം val, വൃക്ഷം valtype,
		  തർക്കം npc, വൃക്ഷം rname, പൂർണ്ണസംഖ്യ parmnum, പൂർണ്ണസംഖ്യ argnum,
		  തർക്കം excess_precision, പൂർണ്ണസംഖ്യ warnopt)
{
  /* Formal parm type is specified by a function prototype.  */

  എങ്കിൽ (type == error_mark_കണ്ണി || !COMPLETE_TYPE_P (type))
    {
      error_at (ploc, "type of formal parameter %d is incomplete",
		parmnum + 1);
      തിരികെ error_mark_കണ്ണി;
    }

  /* Optionally warn about conversions that differ from the default
     conversions.  */
  എങ്കിൽ (warn_traditional_conversion || warn_traditional)
    {
      എങ്കിൽ (INTEGRAL_TYPE_P (type)
	  && SCALAR_FLOAT_TYPE_P (valtype))
	warning_at (ploc, OPT_Wtraditional_conversion,
		    "passing argument %d of %qE as integer rather "
		    "than floating due to prototype",
		    argnum, rname);
      എങ്കിൽ (INTEGRAL_TYPE_P (type)
	  && വൃക്ഷം_CODE (valtype) == COMPLEX_TYPE)
	warning_at (ploc, OPT_Wtraditional_conversion,
		    "passing argument %d of %qE as integer rather "
		    "than complex due to prototype",
		    argnum, rname);
      അല്ലെങ്കിൽ എങ്കിൽ (വൃക്ഷം_CODE (type) == COMPLEX_TYPE
	       && SCALAR_FLOAT_TYPE_P (valtype))
	warning_at (ploc, OPT_Wtraditional_conversion,
		    "passing argument %d of %qE as complex rather "
		    "than floating due to prototype",
		    argnum, rname);
      അല്ലെങ്കിൽ എങ്കിൽ (SCALAR_FLOAT_TYPE_P (type)
	       && INTEGRAL_TYPE_P (valtype))
	warning_at (ploc, OPT_Wtraditional_conversion,
		    "passing argument %d of %qE as floating rather "
		    "than integer due to prototype",
		    argnum, rname);
      അല്ലെങ്കിൽ എങ്കിൽ (വൃക്ഷം_CODE (type) == COMPLEX_TYPE
	       && INTEGRAL_TYPE_P (valtype))
	warning_at (ploc, OPT_Wtraditional_conversion,
		    "passing argument %d of %qE as complex rather "
		    "than integer due to prototype",
		    argnum, rname);
      അല്ലെങ്കിൽ എങ്കിൽ (SCALAR_FLOAT_TYPE_P (type)
	       && വൃക്ഷം_CODE (valtype) == COMPLEX_TYPE)
	warning_at (ploc, OPT_Wtraditional_conversion,
		    "passing argument %d of %qE as floating rather "
		    "than complex due to prototype",
		    argnum, rname);
      /* ??? At some point, messages should be written about
	 conversions between complex types, but that's too messy
	 to do now.  */
      അല്ലെങ്കിൽ എങ്കിൽ (SCALAR_FLOAT_TYPE_P (type)
	       && SCALAR_FLOAT_TYPE_P (valtype))
	{
	  unsigned പൂർണ്ണസംഖ്യ formal_prec = TYPE_PRECISION (type);

	  /* Warn if any argument is passed as `float',
	     since without a prototype it would be `double'.  */
	  എങ്കിൽ (formal_prec == TYPE_PRECISION (float_type_കണ്ണി)
	      && type != dfloat32_type_കണ്ണി)
	    warning_at (ploc, 0,
			"passing argument %d of %qE as %<float%> "
			"rather than %<double%> due to prototype",
			argnum, rname);

	  /* Warn if mismatch between argument and prototype
	     for decimal float types.  Warn of conversions with
	     binary float types and of precision narrowing due to
	     prototype.  */
	  അല്ലെങ്കിൽ എങ്കിൽ (type != valtype
		   && (type == dfloat32_type_കണ്ണി
		       || type == dfloat64_type_കണ്ണി
		       || type == dfloat128_type_കണ്ണി
		       || valtype == dfloat32_type_കണ്ണി
		       || valtype == dfloat64_type_കണ്ണി
		       || valtype == dfloat128_type_കണ്ണി)
		   && (formal_prec
		       <= TYPE_PRECISION (valtype)
		       || (type == dfloat128_type_കണ്ണി
			   && (valtype
			       != dfloat64_type_കണ്ണി
			       && (valtype
				   != dfloat32_type_കണ്ണി)))
		       || (type == dfloat64_type_കണ്ണി
			   && (valtype
			       != dfloat32_type_കണ്ണി))))
	    warning_at (ploc, 0,
			"passing argument %d of %qE as %qT "
			"rather than %qT due to prototype",
			argnum, rname, type, valtype);

	}
      /* Detect integer changing in width or signedness.
	 These warnings are only activated with
	 -Wtraditional-conversion, not with -Wtraditional.  */
      അല്ലെങ്കിൽ എങ്കിൽ (warn_traditional_conversion
	       && INTEGRAL_TYPE_P (type)
	       && INTEGRAL_TYPE_P (valtype))
	{
	  unsigned പൂർണ്ണസംഖ്യ formal_prec = TYPE_PRECISION (type);
	  വൃക്ഷം would_have_been = default_conversion (val);
	  വൃക്ഷം type1 = വൃക്ഷം_TYPE (would_have_been);

	  എങ്കിൽ (val == error_mark_കണ്ണി)
	    /* VAL could have been of incomplete type.  */;
	  അല്ലെങ്കിൽ എങ്കിൽ (വൃക്ഷം_CODE (type) == ENUMERAL_TYPE
		   && (TYPE_MAIN_VARIANT (type)
		       == TYPE_MAIN_VARIANT (valtype)))
	    /* No warning if function asks for enum
	       and the actual arg is that enum type.  */
	    ;
	  അല്ലെങ്കിൽ എങ്കിൽ (formal_prec != TYPE_PRECISION (type1))
	    warning_at (ploc, OPT_Wtraditional_conversion,
			"passing argument %d of %qE "
			"with different width due to prototype",
			argnum, rname);
	  അല്ലെങ്കിൽ എങ്കിൽ (TYPE_UNSIGNED (type) == TYPE_UNSIGNED (type1))
	    ;
	  /* Don't complain if the formal parameter type
	     is an enum, because we can't tell now whether
	     the value was an enum--even the same enum.  */
	  അല്ലെങ്കിൽ എങ്കിൽ (വൃക്ഷം_CODE (type) == ENUMERAL_TYPE)
	    ;
	  അല്ലെങ്കിൽ എങ്കിൽ (വൃക്ഷം_CODE (val) == INTEGER_CST
		   && int_fits_type_p (val, type))
	    /* Change in signedness doesn't matter
	       if a constant value is unaffected.  */
	    ;
	  /* If the value is extended from a narrower
	     unsigned type, it doesn't matter whether we
	     pass it as signed or unsigned; the value
	     certainly is the same either way.  */
	  അല്ലെങ്കിൽ എങ്കിൽ (TYPE_PRECISION (valtype) < TYPE_PRECISION (type)
		   && TYPE_UNSIGNED (valtype))
	    ;
	  അല്ലെങ്കിൽ എങ്കിൽ (TYPE_UNSIGNED (type))
	    warning_at (ploc, OPT_Wtraditional_conversion,
			"passing argument %d of %qE "
			"as unsigned due to prototype",
			argnum, rname);
	  അല്ലെങ്കിൽ
	    warning_at (ploc, OPT_Wtraditional_conversion,
			"passing argument %d of %qE "
			"as signed due to prototype",
			argnum, rname);
	}
    }

  /* Possibly restore an EXCESS_PRECISION_EXPR for the
     sake of better warnings from convert_and_check.  */
  എങ്കിൽ (excess_precision)
    val = build1 (EXCESS_PRECISION_വ്യഞ്ജകം, valtype, val);

  വൃക്ഷം parmval = convert_for_assignment (ploc, ploc, type,
					 val, origtype, ic_argpass,
					 npc, fundecl, function,
					 parmnum + 1, warnopt);
  തിരികെ parmval;
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

സ്ഥിതം പൂർണ്ണസംഖ്യ
convert_arguments (location_t loc, vec<location_t> arg_loc, വൃക്ഷം fntype,
		   vec<വൃക്ഷം, va_gc> *മൂല്യങ്ങൾ, vec<വൃക്ഷം, va_gc> *origtypes,
		   വൃക്ഷം function, വൃക്ഷം fundecl)
{
  വൃക്ഷം typelist = TYPE_ARG_TYPES (fntype);
  unsigned പൂർണ്ണസംഖ്യ parmnum;
  തർക്കം error_args = അസത്യം;
  സ്ഥിരം തർക്കം type_generic = fundecl
    && lookup_attribute ("type generic", TYPE_ATTRIBUTES (വൃക്ഷം_TYPE (fundecl)));
  തർക്കം type_generic_remove_excess_precision = അസത്യം;
  തർക്കം type_generic_overflow_p = അസത്യം;
  തർക്കം type_generic_bit_query = അസത്യം;
  വൃക്ഷം selector;

  /* Change pointer to function to the function itself for
     diagnostics.  */
  എങ്കിൽ (വൃക്ഷം_CODE (function) == ADDR_വ്യഞ്ജകം
      && വൃക്ഷം_CODE (വൃക്ഷം_OPERAND (function, 0)) == FUNCTION_DECL)
    function = വൃക്ഷം_OPERAND (function, 0);

  /* Handle an ObjC selector specially for diagnostics.  */
  selector = objc_message_selector ();

  /* For a call to a built-in function declared without a prototype,
     set to the built-in function's argument list.  */
  വൃക്ഷം builtin_typelist = NULL_വൃക്ഷം;

  /* For type-generic built-in functions, determine whether excess
     precision should be removed (classification) or not
     (comparison).  */
  എങ്കിൽ (fundecl
      && fndecl_built_in_p (fundecl, BUILT_IN_NORMAL))
    {
      built_in_function code = DECL_FUNCTION_CODE (fundecl);
      എങ്കിൽ (C_DECL_BUILTIN_PROTOTYPE (fundecl))
	{
	  /* For a call to a built-in function declared without a prototype
	     use the types of the parameters of the internal built-in to
	     match those of the arguments to.  */
	  എങ്കിൽ (വൃക്ഷം bdecl = builtin_decl_explicit (code))
	    builtin_typelist = TYPE_ARG_TYPES (വൃക്ഷം_TYPE (bdecl));
	}

      /* For type-generic built-in functions, determine whether excess
	 precision should be removed (classification) or not
	 (comparison).  */
      എങ്കിൽ (type_generic)
	തിരഞ്ഞെടുപ്പ് (code)
	  {
	  അവസ്ഥ BUILT_IN_ISFINITE:
	  അവസ്ഥ BUILT_IN_ISINF:
	  അവസ്ഥ BUILT_IN_ISINF_SIGN:
	  അവസ്ഥ BUILT_IN_ISNAN:
	  അവസ്ഥ BUILT_IN_ISNORMAL:
	  അവസ്ഥ BUILT_IN_ISSIGNALING:
	  അവസ്ഥ BUILT_IN_FPCLASSIFY:
	    type_generic_remove_excess_precision = സത്യം;
	    നിർത്തുക;

	  അവസ്ഥ BUILT_IN_ADD_OVERFLOW_P:
	  അവസ്ഥ BUILT_IN_SUB_OVERFLOW_P:
	  അവസ്ഥ BUILT_IN_MUL_OVERFLOW_P:
	    /* The last argument of these type-generic builtins
	       should not be promoted.  */
	    type_generic_overflow_p = സത്യം;
	    നിർത്തുക;

	  അവസ്ഥ BUILT_IN_CLZG:
	  അവസ്ഥ BUILT_IN_CTZG:
	  അവസ്ഥ BUILT_IN_CLRSBG:
	  അവസ്ഥ BUILT_IN_FFSG:
	  അവസ്ഥ BUILT_IN_PARITYG:
	  അവസ്ഥ BUILT_IN_POPCOUNTG:
	    /* The first argument of these type-generic builtins
	       should not be promoted.  */
	    type_generic_bit_query = സത്യം;
	    നിർത്തുക;

	  സ്ഥിരസ്ഥിതി:
	    നിർത്തുക;
	  }
    }

  /* Scan the given expressions (VALUES) and types (TYPELIST), producing
     individual converted arguments.  */

  വൃക്ഷം typetail, builtin_typetail, val;
  വേണ്ടി (typetail = typelist,
	 builtin_typetail = builtin_typelist,
	 parmnum = 0;
       മൂല്യങ്ങൾ && മൂല്യങ്ങൾ->iterate (parmnum, &val);
       ++parmnum)
    {
      /* The type of the function parameter (if it was declared with one).  */
      വൃക്ഷം type = typetail ? വൃക്ഷം_മൂല്യം (typetail) : NULL_വൃക്ഷം;
      /* The type of the built-in function parameter (if the function
	 is a built-in).  Used to detect type incompatibilities in
	 calls to built-ins declared without a prototype.  */
      വൃക്ഷം builtin_type = (builtin_typetail
			   ? വൃക്ഷം_മൂല്യം (builtin_typetail) : NULL_വൃക്ഷം);
      /* The original type of the argument being passed to the function.  */
      വൃക്ഷം valtype = വൃക്ഷം_TYPE (val);
      /* The called function (or function selector in Objective C).  */
      വൃക്ഷം rname = function;
      പൂർണ്ണസംഖ്യ argnum = parmnum + 1;
      സ്ഥിരം അക്ഷരം *invalid_func_diag;
      /* Set for EXCESS_PRECISION_EXPR arguments.  */
      തർക്കം excess_precision = അസത്യം;
      /* The value of the argument after conversion to the type
	 of the function parameter it is passed to.  */
      വൃക്ഷം parmval;
      /* Some __atomic_* builtins have additional hidden argument at
	 position 0.  */
      location_t ploc
	= !arg_loc.is_empty () && മൂല്യങ്ങൾ->length () == arg_loc.length ()
	  ? expansion_point_location_if_in_system_header (arg_loc[parmnum])
	  : നിവേശം_location;

      എങ്കിൽ (type == void_type_കണ്ണി)
	{
	  auto_diagnostic_group d;
	  പൂർണ്ണസംഖ്യ അക്കം_expected = parmnum;
	  പൂർണ്ണസംഖ്യ അക്കം_actual = മൂല്യങ്ങൾ->length ();
	  gcc_rich_location rich_loc (loc);
	  എങ്കിൽ (ploc != നിവേശം_location)
	    rich_loc.add_range (ploc);
	  എങ്കിൽ (selector)
	    error_at (&rich_loc,
		      "too many arguments to method %qE; expected %i, have %i",
		      selector, അക്കം_expected, അക്കം_actual);
	  അല്ലെങ്കിൽ
	    error_at (&rich_loc,
		      "too many arguments to function %qE; expected %i, have %i",
		      function, അക്കം_expected, അക്കം_actual);
	  inform_declaration (fundecl, function);
	  തിരികെ error_args ? -1 : (പൂർണ്ണസംഖ്യ) parmnum;
	}

      എങ്കിൽ (builtin_type == void_type_കണ്ണി)
	{
	  auto_diagnostic_group d;
	  എങ്കിൽ (warning_at (loc, OPT_Wbuiltin_declaration_mismatch,
			  "too many arguments to built-in function %qE "
			  "expecting %d", function, parmnum))
	    inform_declaration (fundecl, function);
	  builtin_typetail = NULL_വൃക്ഷം;
	}

      എങ്കിൽ (!typetail && parmnum == 0 && !TYPE_NO_NAMED_ARGS_STDARG_P (fntype)
	  && !(fundecl && fndecl_built_in_p (fundecl)))
	{
	  auto_diagnostic_group d;
	  തർക്കം warned;
	  എങ്കിൽ (selector)
	    warned = warning_at (loc, OPT_Wdeprecated_non_prototype,
				 "ISO C23 does not allow arguments"
				 " for method %qE declared without parameters",
				 function);
	  അല്ലെങ്കിൽ
	    warned = warning_at (loc, OPT_Wdeprecated_non_prototype,
				 "ISO C23 does not allow arguments"
				 " for function %qE declared without parameters",
				 function);
	  എങ്കിൽ (warned)
	    inform_declaration (fundecl, function);
	}

      എങ്കിൽ (selector && argnum > 2)
	{
	  rname = selector;
	  argnum -= 2;
	}

      /* Determine if VAL is a null pointer constant before folding it.  */
      തർക്കം npc = null_pointer_constant_p (val);

      /* If there is excess precision and a prototype, convert once to
	 the required type rather than converting via the semantic
	 type.  Likewise without a prototype a float value represented
	 as long double should be converted once to double.  But for
	 type-generic classification functions excess precision must
	 be removed here.  */
      എങ്കിൽ (വൃക്ഷം_CODE (val) == EXCESS_PRECISION_വ്യഞ്ജകം
	  && (type || !type_generic || !type_generic_remove_excess_precision))
	{
	  val = വൃക്ഷം_OPERAND (val, 0);
	  excess_precision = സത്യം;
	}
      val = c_fully_fold (val, അസത്യം, ശൂന്യ);
      STRIP_TYPE_NOPS (val);

      val = require_complete_type (ploc, val);

      /* Some floating-point arguments must be promoted to double when
	 no type is specified by a prototype.  This applies to
	 arguments of type float, and to architecture-specific types
	 (ARM __fp16), but not to _FloatN or _FloatNx types.  */
      തർക്കം promote_float_arg = അസത്യം;
      എങ്കിൽ (type == NULL_വൃക്ഷം
	  && വൃക്ഷം_CODE (valtype) == REAL_TYPE
	  && (TYPE_PRECISION (valtype)
	      <= TYPE_PRECISION (double_type_കണ്ണി))
	  && TYPE_MAIN_VARIANT (valtype) != double_type_കണ്ണി
	  && TYPE_MAIN_VARIANT (valtype) != long_double_type_കണ്ണി
	  && !DECIMAL_FLOAT_MODE_P (TYPE_MODE (valtype)))
	{
	  /* Promote this argument, unless it has a _FloatN or
	     _FloatNx type.  */
	  promote_float_arg = സത്യം;
	  വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < അക്കം_FLOATN_NX_TYPES; i++)
	    എങ്കിൽ (TYPE_MAIN_VARIANT (valtype) == FLOATN_NX_TYPE_കണ്ണി (i))
	      {
		promote_float_arg = അസത്യം;
		നിർത്തുക;
	      }
	  /* Don't promote __bf16 either.  */
	  എങ്കിൽ (TYPE_MAIN_VARIANT (valtype) == bfloat16_type_കണ്ണി)
	    promote_float_arg = അസത്യം;
	}

      എങ്കിൽ (type != NULL_വൃക്ഷം)
	{
	  വൃക്ഷം origtype = (!origtypes) ? NULL_വൃക്ഷം : (*origtypes)[parmnum];
	  parmval = convert_argument (ploc, function, fundecl, type, origtype,
				      val, valtype, npc, rname, parmnum, argnum,
				      excess_precision, 0);
	}
      /* A NULLPTR type is just a nullptr always.  */
      അല്ലെങ്കിൽ എങ്കിൽ (വൃക്ഷം_CODE (വൃക്ഷം_TYPE (val)) == NULLPTR_TYPE)
	parmval = omit_one_operand_loc (ploc, വൃക്ഷം_TYPE (val), nullptr_കണ്ണി, val);
      അല്ലെങ്കിൽ എങ്കിൽ (promote_float_arg)
        {
	  എങ്കിൽ (type_generic)
	    parmval = val;
	  അല്ലെങ്കിൽ
	    {
	      /* Convert `float' to `double'.  */
	      എങ്കിൽ (warn_double_promotion && !c_inhibit_evaluation_warnings)
		warning_at (ploc, OPT_Wdouble_promotion,
			    "implicit conversion from %qT to %qT when passing "
			    "argument to function",
			    valtype, double_type_കണ്ണി);
	      parmval = convert (double_type_കണ്ണി, val);
	    }
	}
      അല്ലെങ്കിൽ എങ്കിൽ ((excess_precision && !type_generic)
	       || (type_generic_overflow_p && parmnum == 2)
	       || (type_generic_bit_query && parmnum == 0))
	/* A "double" argument with excess precision being passed
	   without a prototype or in variable arguments.
	   The last argument of __builtin_*_overflow_p should not be
	   promoted, similarly the first argument of
	   __builtin_{clz,ctz,clrsb,ffs,parity,popcount}g.  */
	parmval = convert (valtype, val);
      അല്ലെങ്കിൽ എങ്കിൽ ((invalid_func_diag =
		targetm.calls.invalid_arg_for_unprototyped_fn (typelist, fundecl, val)))
	{
	  error (invalid_func_diag);
	  തിരികെ -1;
	}
      അല്ലെങ്കിൽ എങ്കിൽ (വൃക്ഷം_CODE (val) == ADDR_വ്യഞ്ജകം && reject_gcc_builtin (val))
	{
	  തിരികെ -1;
	}
      അല്ലെങ്കിൽ
	/* Convert `short' and `char' to full-size `int'.  */
	parmval = default_conversion (val);

      (*മൂല്യങ്ങൾ)[parmnum] = parmval;
      എങ്കിൽ (parmval == error_mark_കണ്ണി)
	error_args = സത്യം;

      എങ്കിൽ (!type && builtin_type && വൃക്ഷം_CODE (builtin_type) != VOID_TYPE)
	{
	  /* For a call to a built-in function declared without a prototype,
	     perform the conversions from the argument to the expected type
	     but issue warnings rather than errors for any mismatches.
	     Ignore the converted argument and use the PARMVAL obtained
	     above by applying default conversions instead.  */
	  വൃക്ഷം origtype = (!origtypes) ? NULL_വൃക്ഷം : (*origtypes)[parmnum];
	  convert_argument (ploc, function, fundecl, builtin_type, origtype,
			    val, valtype, npc, rname, parmnum, argnum,
			    excess_precision,
			    OPT_Wbuiltin_declaration_mismatch);
	}

      എങ്കിൽ (typetail)
	typetail = വൃക്ഷം_CHAIN (typetail);

      എങ്കിൽ (builtin_typetail)
	builtin_typetail = വൃക്ഷം_CHAIN (builtin_typetail);
    }

  gcc_assert (parmnum == vec_safe_length (മൂല്യങ്ങൾ));

  എങ്കിൽ (typetail != NULL_വൃക്ഷം && വൃക്ഷം_മൂല്യം (typetail) != void_type_കണ്ണി)
    {
      /* Not enough args.
	 Determine minimum number of arguments required.  */
      പൂർണ്ണസംഖ്യ min_expected_അക്കം = 0;
      തർക്കം at_least_p = അസത്യം;
      വൃക്ഷം iter = typelist;
      ആകുമ്പോൾ (സത്യം)
	{
	  എങ്കിൽ (!iter)
	    {
	      /* Variadic arguments; stop iterating.  */
	      at_least_p = സത്യം;
	      നിർത്തുക;
	    }
	  എങ്കിൽ (iter == void_list_കണ്ണി)
	    /* End of arguments; stop iterating.  */
	    നിർത്തുക;
	  ++min_expected_അക്കം;
	  iter = വൃക്ഷം_CHAIN (iter);
	}
      auto_diagnostic_group d;
      പൂർണ്ണസംഖ്യ actual_അക്കം = vec_safe_length (മൂല്യങ്ങൾ);
      error_at (loc,
		at_least_p
		? G_("too few arguments to function %qE; expected at least %i, have %i")
		: G_("too few arguments to function %qE; expected %i, have %i"),
		function, min_expected_അക്കം, actual_അക്കം);
      inform_declaration (fundecl, function);
      തിരികെ -1;
    }

  എങ്കിൽ (builtin_typetail && വൃക്ഷം_മൂല്യം (builtin_typetail) != void_type_കണ്ണി)
    {
      unsigned nargs = parmnum;
      വേണ്ടി (വൃക്ഷം t = builtin_typetail; t; t = വൃക്ഷം_CHAIN (t))
	++nargs;

      auto_diagnostic_group d;
      എങ്കിൽ (warning_at (loc, OPT_Wbuiltin_declaration_mismatch,
		      "too few arguments to built-in function %qE "
		      "expecting %u", function, nargs - 1))
	inform_declaration (fundecl, function);
    }

  തിരികെ error_args ? -1 : (പൂർണ്ണസംഖ്യ) parmnum;
}

/* This is the entry point used by the parser to build unary operators
   in the input.  CODE, a tree_code, specifies the unary operator, and
   ARG is the operand.  For unary plus, the C parser currently uses
   CONVERT_EXPR for code.

   LOC is the location to use for the tree generated.
*/

ഘടന c_വ്യഞ്ജകം
parser_build_unary_op (location_t loc, എണ്ണൽ വൃക്ഷം_code code, ഘടന c_വ്യഞ്ജകം arg)
{
  ഘടന c_വ്യഞ്ജകം result;

  result.original_code = code;
  result.original_type = ശൂന്യ;
  result.m_decimal = 0;

  എങ്കിൽ (reject_gcc_builtin (arg.മൂല്യം))
    {
      result.മൂല്യം = error_mark_കണ്ണി;
    }
  അല്ലെങ്കിൽ
    {
      result.മൂല്യം = build_unary_op (loc, code, arg.മൂല്യം, അസത്യം);

      എങ്കിൽ (വൃക്ഷം_OVERFLOW_P (result.മൂല്യം) && !വൃക്ഷം_OVERFLOW_P (arg.മൂല്യം))
	overflow_warning (loc, result.മൂല്യം, arg.മൂല്യം);
    }

  /* We are typically called when parsing a prefix token at LOC acting on
     ARG.  Reflect this by updating the source range of the result to
     start at LOC and end at the end of ARG.  */
  set_c_വ്യഞ്ജകം_source_range (&result,
			   loc, arg.get_finish ());

  തിരികെ result;
}

/* Returns true if TYPE is a character type, *not* including wchar_t.  */

തർക്കം
char_type_p (വൃക്ഷം type)
{
  തിരികെ (type == char_type_കണ്ണി
	  || type == unsigned_char_type_കണ്ണി
	  || type == signed_char_type_കണ്ണി
	  || type == char16_type_കണ്ണി
	  || type == char32_type_കണ്ണി);
}

/* This is the entry point used by the parser to build binary operators
   in the input.  CODE, a tree_code, specifies the binary operator, and
   ARG1 and ARG2 are the operands.  In addition to constructing the
   expression, we check for operands that were written with other binary
   operators in a way that is likely to confuse the user.  ORIG_ARG1 is
   the original first operand for TRUTH_{AND,OR}IF_EXPR before it is
   converted to truth value, otherwise NULL_TREE.

   LOCATION is the location of the binary operator.  */

ഘടന c_വ്യഞ്ജകം
parser_build_ദ്വിമാന_op (location_t location, എണ്ണൽ വൃക്ഷം_code code,
			ഘടന c_വ്യഞ്ജകം arg1, ഘടന c_വ്യഞ്ജകം arg2, വൃക്ഷം orig_arg1)
{
  ഘടന c_വ്യഞ്ജകം result;
  result.m_decimal = 0;

  എണ്ണൽ വൃക്ഷം_code code1 = arg1.original_code;
  എണ്ണൽ വൃക്ഷം_code code2 = arg2.original_code;
  വൃക്ഷം type1 = (arg1.original_type
                ? arg1.original_type
                : വൃക്ഷം_TYPE (arg1.മൂല്യം));
  വൃക്ഷം type2 = (arg2.original_type
                ? arg2.original_type
                : വൃക്ഷം_TYPE (arg2.മൂല്യം));

  result.മൂല്യം = build_ദ്വിമാന_op (location, code,
				  arg1.മൂല്യം, arg2.മൂല്യം, സത്യം);
  result.original_code = code;
  result.original_type = ശൂന്യ;
  result.m_decimal = 0;

  എങ്കിൽ (വൃക്ഷം_CODE (result.മൂല്യം) == ERROR_MARK)
    {
      set_c_വ്യഞ്ജകം_source_range (&result,
			       arg1.get_start (),
			       arg2.get_finish ());
      തിരികെ result;
    }

  എങ്കിൽ (location != UNKNOWN_LOCATION)
    protected_set_വ്യഞ്ജകം_location (result.മൂല്യം, location);

  set_c_വ്യഞ്ജകം_source_range (&result,
			   arg1.get_start (),
			   arg2.get_finish ());

  /* Check for cases such as x+y<<z which users are likely
     to misinterpret.  */
  എങ്കിൽ (warn_parentheses)
    warn_about_parentheses (location, code, code1, arg1.മൂല്യം, code2,
			    arg2.മൂല്യം);

  എങ്കിൽ (warn_logical_op)
    warn_logical_operator (location, code, വൃക്ഷം_TYPE (result.മൂല്യം),
			   code1, arg1.മൂല്യം, code2, arg2.മൂല്യം);

  എങ്കിൽ (warn_constant_logical_operand
      && (code == TRUTH_ANDIF_വ്യഞ്ജകം || code == TRUTH_ORIF_വ്യഞ്ജകം)
      && INTEGRAL_NB_TYPE_P (type1)
      && INTEGRAL_NB_TYPE_P (type2))
    {
      സ്ഥിരം അക്ഷരം *name = code == TRUTH_ANDIF_വ്യഞ്ജകം ? "&&" : "||";
      എങ്കിൽ (orig_arg1 == NULL_വൃക്ഷം)
	orig_arg1 = arg1.മൂല്യം;
      auto enum_other_than_0_1 = [] (വൃക്ഷം type) {
	എങ്കിൽ (വൃക്ഷം_CODE (type) != ENUMERAL_TYPE)
	  തിരികെ അസത്യം;
	വേണ്ടി (വൃക്ഷം l = TYPE_മൂല്യങ്ങൾ (type); l; l = വൃക്ഷം_CHAIN (l))
	  {
	    വൃക്ഷം v = DECL_INITIAL (വൃക്ഷം_മൂല്യം (l));
	    എങ്കിൽ (!integer_zerop (v) && !integer_onep (v))
	      തിരികെ സത്യം;
	  }
	തിരികെ അസത്യം;
      };
      auto diagnose_constant_logical_operand = [=] (വൃക്ഷം val, വൃക്ഷം type) {
	എങ്കിൽ (വൃക്ഷം_CODE (val) != INTEGER_CST || integer_zerop (val))
	  തിരികെ അസത്യം;
	എങ്കിൽ (integer_onep (val) && !enum_other_than_0_1 (type))
	  തിരികെ അസത്യം;
	gcc_rich_location richloc (location);
	richloc.add_fixit_replace (name + 1);
	auto_diagnostic_group d;
	എങ്കിൽ (warning_at (location, OPT_Wconstant_logical_operand,
			"use of logical %qs with constant operand %qE",
			name, val))
	  inform (&richloc, "use %qs for bitwise operation", name + 1);
	തിരികെ സത്യം;
      };
      എങ്കിൽ (!diagnose_constant_logical_operand (arg2.മൂല്യം, type2))
	diagnose_constant_logical_operand (orig_arg1, type1);
    }

  എങ്കിൽ (warn_tautological_compare)
    {
      വൃക്ഷം lhs = arg1.മൂല്യം;
      വൃക്ഷം rhs = arg2.മൂല്യം;
      എങ്കിൽ (വൃക്ഷം_CODE (lhs) == C_MAYBE_CONST_വ്യഞ്ജകം)
	{
	  എങ്കിൽ (C_MAYBE_CONST_വ്യഞ്ജകം_PRE (lhs) != NULL_വൃക്ഷം
	      && വൃക്ഷം_SIDE_EFFECTS (C_MAYBE_CONST_വ്യഞ്ജകം_PRE (lhs)))
	    lhs = NULL_വൃക്ഷം;
	  അല്ലെങ്കിൽ
	    lhs = C_MAYBE_CONST_വ്യഞ്ജകം_വ്യഞ്ജകം (lhs);
	}
      എങ്കിൽ (വൃക്ഷം_CODE (rhs) == C_MAYBE_CONST_വ്യഞ്ജകം)
	{
	  എങ്കിൽ (C_MAYBE_CONST_വ്യഞ്ജകം_PRE (rhs) != NULL_വൃക്ഷം
	      && വൃക്ഷം_SIDE_EFFECTS (C_MAYBE_CONST_വ്യഞ്ജകം_PRE (rhs)))
	    rhs = NULL_വൃക്ഷം;
	  അല്ലെങ്കിൽ
	    rhs = C_MAYBE_CONST_വ്യഞ്ജകം_വ്യഞ്ജകം (rhs);
	}
      എങ്കിൽ (lhs != NULL_വൃക്ഷം && rhs != NULL_വൃക്ഷം)
	warn_tautological_cmp (location, code, lhs, rhs);
    }

  എങ്കിൽ (warn_logical_not_paren
      && വൃക്ഷം_CODE_CLASS (code) == tcc_comparison
      && code1 == TRUTH_NOT_വ്യഞ്ജകം
      && code2 != TRUTH_NOT_വ്യഞ്ജകം
      /* Avoid warning for !!x == y.  */
      && (വൃക്ഷം_CODE (arg1.മൂല്യം) != NE_വ്യഞ്ജകം
	  || !integer_zerop (വൃക്ഷം_OPERAND (arg1.മൂല്യം, 1))))
    {
      /* Avoid warning for !b == y where b has _Bool type.  */
      വൃക്ഷം t = integer_zero_കണ്ണി;
      എങ്കിൽ (വൃക്ഷം_CODE (arg1.മൂല്യം) == EQ_വ്യഞ്ജകം
	  && integer_zerop (വൃക്ഷം_OPERAND (arg1.മൂല്യം, 1))
	  && വൃക്ഷം_TYPE (വൃക്ഷം_OPERAND (arg1.മൂല്യം, 0)) == integer_type_കണ്ണി)
	{
	  t = വൃക്ഷം_OPERAND (arg1.മൂല്യം, 0);
	  ചെയ്യുക
	    {
	      എങ്കിൽ (വൃക്ഷം_TYPE (t) != integer_type_കണ്ണി)
		നിർത്തുക;
	      എങ്കിൽ (വൃക്ഷം_CODE (t) == C_MAYBE_CONST_വ്യഞ്ജകം)
		t = C_MAYBE_CONST_വ്യഞ്ജകം_വ്യഞ്ജകം (t);
	      അല്ലെങ്കിൽ എങ്കിൽ (CONVERT_വ്യഞ്ജകം_P (t))
		t = വൃക്ഷം_OPERAND (t, 0);
	      അല്ലെങ്കിൽ
		നിർത്തുക;
	    }
	  ആകുമ്പോൾ (1);
	}
      എങ്കിൽ (!C_BOOLEAN_TYPE_P (വൃക്ഷം_TYPE (t)))
	warn_logical_not_parentheses (location, code, arg1.മൂല്യം, arg2.മൂല്യം);
    }

  /* Warn about comparisons against string literals, with the exception
     of testing for equality or inequality of a string literal with NULL.  */
  എങ്കിൽ (code == EQ_വ്യഞ്ജകം || code == NE_വ്യഞ്ജകം)
    {
      എങ്കിൽ ((code1 == STRING_CST
	   && !integer_zerop (വൃക്ഷം_strip_nop_conversions (arg2.മൂല്യം)))
	  || (code2 == STRING_CST
	      && !integer_zerop (വൃക്ഷം_strip_nop_conversions (arg1.മൂല്യം))))
	warning_at (location, OPT_Waddress,
		    "comparison with string literal results in unspecified behavior");
      /* Warn for ptr == '\0', it's likely that it should've been ptr[0].  */
      എങ്കിൽ (POINTER_TYPE_P (type1)
	  && null_pointer_constant_p (arg2.മൂല്യം)
	  && char_type_p (type2))
	{
	  auto_diagnostic_group d;
	  എങ്കിൽ (warning_at (location, OPT_Wpointer_compare,
			    "comparison between pointer and zero character "
			    "constant"))
	    inform (arg1.get_start (),
		      "did you mean to dereference the pointer?");
	}
      അല്ലെങ്കിൽ എങ്കിൽ (POINTER_TYPE_P (type2)
	       && null_pointer_constant_p (arg1.മൂല്യം)
	       && char_type_p (type1))
	{
	  auto_diagnostic_group d;
	  എങ്കിൽ (warning_at (location, OPT_Wpointer_compare,
			    "comparison between pointer and zero character "
			    "constant"))
	    inform (arg2.get_start (),
		      "did you mean to dereference the pointer?");
	}
    }
  അല്ലെങ്കിൽ എങ്കിൽ (വൃക്ഷം_CODE_CLASS (code) == tcc_comparison
	   && (code1 == STRING_CST || code2 == STRING_CST))
    warning_at (location, OPT_Waddress,
		"comparison with string literal results in unspecified "
		"behavior");

  എങ്കിൽ (warn_zero_as_null_pointer_constant
      && c_inhibit_evaluation_warnings == 0
      && വൃക്ഷം_CODE_CLASS (code) == tcc_comparison)
    {
      എങ്കിൽ ((വൃക്ഷം_CODE (type1) == POINTER_TYPE
	   || വൃക്ഷം_CODE (type1) == NULLPTR_TYPE)
	  && INTEGRAL_TYPE_P (type2)
	  && null_pointer_constant_p (arg2.മൂല്യം))
	warning_at (arg2.get_location(), OPT_Wzero_as_null_pointer_constant,
		    "zero as null pointer constant");

      എങ്കിൽ ((വൃക്ഷം_CODE (type2) == POINTER_TYPE
	   || വൃക്ഷം_CODE (type2) == NULLPTR_TYPE)
	  && INTEGRAL_TYPE_P (type1)
	  && null_pointer_constant_p (arg1.മൂല്യം))
	warning_at (arg1.get_location(), OPT_Wzero_as_null_pointer_constant,
		    "zero as null pointer constant");
    }

  എങ്കിൽ (warn_array_compare
      && വൃക്ഷം_CODE_CLASS (code) == tcc_comparison
      && വൃക്ഷം_CODE (type1) == ARRAY_TYPE
      && വൃക്ഷം_CODE (type2) == ARRAY_TYPE)
    do_warn_array_compare (location, code, arg1.മൂല്യം, arg2.മൂല്യം);

  എങ്കിൽ (വൃക്ഷം_OVERFLOW_P (result.മൂല്യം)
      && !വൃക്ഷം_OVERFLOW_P (arg1.മൂല്യം)
      && !വൃക്ഷം_OVERFLOW_P (arg2.മൂല്യം))
    overflow_warning (location, result.മൂല്യം);

  /* Warn about comparisons of different enum types.  */
  എങ്കിൽ (warn_enum_compare
      && വൃക്ഷം_CODE_CLASS (code) == tcc_comparison
      && വൃക്ഷം_CODE (type1) == ENUMERAL_TYPE
      && വൃക്ഷം_CODE (type2) == ENUMERAL_TYPE
      && TYPE_MAIN_VARIANT (type1) != TYPE_MAIN_VARIANT (type2))
    warning_at (location, OPT_Wenum_compare,
		"comparison between %qT and %qT",
		type1, type2);

  എങ്കിൽ (warn_xor_used_as_pow
      && code == BIT_XOR_വ്യഞ്ജകം
      && arg1.m_decimal
      && arg2.m_decimal)
    check_for_xor_used_as_pow (arg1.get_location (), arg1.മൂല്യം,
			       location,
			       arg2.get_location (), arg2.മൂല്യം);

  തിരികെ result;
}

/* Return a tree for the difference of pointers OP0 and OP1.
   The resulting tree has type ptrdiff_t.  If POINTER_SUBTRACT sanitization is
   enabled, assign to INSTRUMENT_EXPR call to libsanitizer.  */

സ്ഥിതം വൃക്ഷം
pointer_diff (location_t loc, വൃക്ഷം op0, വൃക്ഷം op1, വൃക്ഷം *instrument_വ്യഞ്ജകം)
{
  വൃക്ഷം restype = ptrdiff_type_കണ്ണി;
  വൃക്ഷം result, inttype;

  addr_space_t as0 = TYPE_ADDR_SPACE (വൃക്ഷം_TYPE (വൃക്ഷം_TYPE (op0)));
  addr_space_t as1 = TYPE_ADDR_SPACE (വൃക്ഷം_TYPE (വൃക്ഷം_TYPE (op1)));
  വൃക്ഷം target_type = വൃക്ഷം_TYPE (വൃക്ഷം_TYPE (op0));
  വൃക്ഷം orig_op0 = op0;
  വൃക്ഷം orig_op1 = op1;

  /* If the operands point into different address spaces, we need to
     explicitly convert them to pointers into the common address space
     before we can subtract the numerical address values.  */
  എങ്കിൽ (as0 != as1)
    {
      addr_space_t as_common;
      വൃക്ഷം common_type;

      /* Determine the common superset address space.  This is guaranteed
	 to exist because the caller verified that comp_target_types
	 returned non-zero.  */
      എങ്കിൽ (!addr_space_superset (as0, as1, &as_common))
	gcc_unreachable ();

      common_type = common_pointer_type (വൃക്ഷം_TYPE (op0), വൃക്ഷം_TYPE (op1), NULL_വൃക്ഷം);
      op0 = convert (common_type, op0);
      op1 = convert (common_type, op1);
    }

  /* Determine integer type result of the subtraction.  This will usually
     be the same as the result type (ptrdiff_t), but may need to be a wider
     type if pointers for the address space are wider than ptrdiff_t.  */
  എങ്കിൽ (TYPE_PRECISION (restype) < TYPE_PRECISION (വൃക്ഷം_TYPE (op0)))
    inttype = c_common_type_for_size (TYPE_PRECISION (വൃക്ഷം_TYPE (op0)), 0);
  അല്ലെങ്കിൽ
    inttype = restype;

  എങ്കിൽ (VOID_TYPE_P (target_type))
    pedwarn (loc, OPT_Wpointer_arith,
	     "pointer of type %<void *%> used in subtraction");
  എങ്കിൽ (വൃക്ഷം_CODE (target_type) == FUNCTION_TYPE)
    pedwarn (loc, OPT_Wpointer_arith,
	     "pointer to a function used in subtraction");

  എങ്കിൽ (current_function_decl != NULL_വൃക്ഷം
      && sanitize_flags_p (SANITIZE_POINTER_SUBTRACT))
    {
      op0 = save_വ്യഞ്ജകം (c_fully_fold (op0, അസത്യം, ശൂന്യ));
      op1 = save_വ്യഞ്ജകം (c_fully_fold (op1, അസത്യം, ശൂന്യ));

      വൃക്ഷം tt = builtin_decl_explicit (BUILT_IN_ASAN_POINTER_SUBTRACT);
      *instrument_വ്യഞ്ജകം = build_call_വ്യഞ്ജകം_loc (loc, tt, 2, op0, op1);
    }

  /* First do the subtraction, then build the divide operator
     and only convert at the very end.
     Do not do default conversions in case restype is a short type.  */

  /* POINTER_DIFF_EXPR requires a signed integer type of the same size as
     pointers.  If some platform cannot provide that, or has a larger
     ptrdiff_type to support differences larger than half the address
     space, cast the pointers to some larger integer type and do the
     computations in that type.  */
  എങ്കിൽ (TYPE_PRECISION (inttype) > TYPE_PRECISION (വൃക്ഷം_TYPE (op0)))
    op0 = build_ദ്വിമാന_op (loc, MINUS_വ്യഞ്ജകം, convert (inttype, op0),
			   convert (inttype, op1), അസത്യം);
  അല്ലെങ്കിൽ
    {
      /* Cast away qualifiers.  */
      op0 = convert (c_common_type (വൃക്ഷം_TYPE (op0), വൃക്ഷം_TYPE (op0)), op0);
      op1 = convert (c_common_type (വൃക്ഷം_TYPE (op1), വൃക്ഷം_TYPE (op1)), op1);
      op0 = build2_loc (loc, POINTER_DIFF_വ്യഞ്ജകം, inttype, op0, op1);
    }

  /* This generates an error if op1 is pointer to incomplete type.  */
  എങ്കിൽ (!COMPLETE_OR_VOID_TYPE_P (വൃക്ഷം_TYPE (വൃക്ഷം_TYPE (orig_op1))))
    error_at (loc, "arithmetic on pointer to an incomplete type");
  അല്ലെങ്കിൽ എങ്കിൽ (verify_type_context (loc, TCTX_POINTER_ARITH,
				വൃക്ഷം_TYPE (വൃക്ഷം_TYPE (orig_op0))))
    verify_type_context (loc, TCTX_POINTER_ARITH,
			 വൃക്ഷം_TYPE (വൃക്ഷം_TYPE (orig_op1)));

  op1 = c_size_in_bytes (target_type);

  എങ്കിൽ (pointer_to_zero_sized_aggr_p (വൃക്ഷം_TYPE (orig_op1)))
    error_at (loc, "arithmetic on pointer to an empty aggregate");

  /* Divide by the size, in easiest possible way.  */
  result = fold_build2_loc (loc, EXACT_DIV_വ്യഞ്ജകം, inttype,
			    op0, convert (inttype, op1));

  /* Convert to final result type if necessary.  */
  തിരികെ convert (restype, result);
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

സ്ഥിതം വൃക്ഷം
build_atomic_assign (location_t loc, വൃക്ഷം lhs, എണ്ണൽ വൃക്ഷം_code modifycode,
		     വൃക്ഷം rhs, തർക്കം return_old_p)
{
  വൃക്ഷം fndecl, func_call;
  vec<വൃക്ഷം, va_gc> *params;
  വൃക്ഷം val, nonatomic_lhs_type, nonatomic_rhs_type, newval, newval_addr;
  വൃക്ഷം old, old_addr;
  വൃക്ഷം compound_stmt = NULL_വൃക്ഷം;
  വൃക്ഷം stmt, goto_stmt;
  വൃക്ഷം loop_label, loop_decl, done_label, done_decl;

  വൃക്ഷം lhs_type = വൃക്ഷം_TYPE (lhs);
  വൃക്ഷം lhs_addr = build_unary_op (loc, ADDR_വ്യഞ്ജകം, lhs, അസത്യം);
  വൃക്ഷം seq_cst = build_int_cst (integer_type_കണ്ണി, MEMMODEL_SEQ_CST);
  വൃക്ഷം rhs_semantic_type = വൃക്ഷം_TYPE (rhs);
  വൃക്ഷം nonatomic_rhs_semantic_type;
  വൃക്ഷം rhs_type;

  gcc_assert (TYPE_ATOMIC (lhs_type));

  എങ്കിൽ (return_old_p)
    gcc_assert (modifycode == PLUS_വ്യഞ്ജകം || modifycode == MINUS_വ്യഞ്ജകം);

  /* Allocate enough vector items for a compare_exchange.  */
  vec_alloc (params, 6);

  /* Create a compound statement to hold the sequence of statements
     with a loop.  */
  എങ്കിൽ (modifycode != NOP_വ്യഞ്ജകം)
    {
      compound_stmt = c_begin_compound_stmt (അസത്യം);

      /* For consistency with build_modify_expr on non-_Atomic,
	 mark the lhs as read.  Also, it would be very hard to match
	 such expressions in mark_exp_read.  */
      mark_exp_read (lhs);
    }

  /* Remove any excess precision (which is only present here in the
     case of compound assignments).  */
  എങ്കിൽ (വൃക്ഷം_CODE (rhs) == EXCESS_PRECISION_വ്യഞ്ജകം)
    {
      gcc_assert (modifycode != NOP_വ്യഞ്ജകം);
      rhs = വൃക്ഷം_OPERAND (rhs, 0);
    }
  rhs_type = വൃക്ഷം_TYPE (rhs);

  /* Fold the RHS if it hasn't already been folded.  */
  എങ്കിൽ (modifycode != NOP_വ്യഞ്ജകം)
    rhs = c_fully_fold (rhs, അസത്യം, ശൂന്യ);

  /* Remove the qualifiers for the rest of the expressions and create
     the VAL temp variable to hold the RHS.  */
  nonatomic_lhs_type = build_qualified_type (lhs_type, TYPE_UNQUALIFIED);
  nonatomic_rhs_type = build_qualified_type (rhs_type, TYPE_UNQUALIFIED);
  nonatomic_rhs_semantic_type = build_qualified_type (rhs_semantic_type,
						      TYPE_UNQUALIFIED);
  val = create_tmp_var_raw (nonatomic_rhs_type);
  വൃക്ഷം_ADDRESSABLE (val) = 1;
  suppress_warning (val);
  rhs = build4 (TARGET_വ്യഞ്ജകം, nonatomic_rhs_type, val, rhs, NULL_വൃക്ഷം,
		NULL_വൃക്ഷം);
  വൃക്ഷം_SIDE_EFFECTS (rhs) = 1;
  SET_വ്യഞ്ജകം_LOCATION (rhs, loc);
  എങ്കിൽ (modifycode != NOP_വ്യഞ്ജകം)
    add_stmt (rhs);

  /* NOP_EXPR indicates it's a straight store of the RHS. Simply issue
     an atomic_store.  */
  എങ്കിൽ (modifycode == NOP_വ്യഞ്ജകം)
    {
      compound_stmt = rhs;
      /* Build __atomic_store (&lhs, &val, SEQ_CST)  */
      rhs = build_unary_op (loc, ADDR_വ്യഞ്ജകം, val, അസത്യം);
      fndecl = builtin_decl_explicit (BUILT_IN_ATOMIC_STORE);
      params->quick_തള്ളുക (lhs_addr);
      params->quick_തള്ളുക (rhs);
      params->quick_തള്ളുക (seq_cst);
      func_call = c_build_function_call_vec (loc, vNULL, fndecl, params, ശൂന്യ);

      compound_stmt = build2 (COMPOUND_വ്യഞ്ജകം, void_type_കണ്ണി,
			      compound_stmt, func_call);

      /* VAL is the value which was stored, return a COMPOUND_STMT of
	 the statement and that value.  */
      തിരികെ build2 (COMPOUND_വ്യഞ്ജകം, nonatomic_lhs_type, compound_stmt, val);
    }

  /* Attempt to implement the atomic operation as an __atomic_fetch_* or
     __atomic_*_fetch built-in rather than a CAS loop.  atomic_bool type
     isn't applicable for such builtins.  ??? Do we want to handle enums?  */
  എങ്കിൽ ((വൃക്ഷം_CODE (lhs_type) == INTEGER_TYPE || POINTER_TYPE_P (lhs_type))
      && വൃക്ഷം_CODE (rhs_type) == INTEGER_TYPE)
    {
      built_in_function fncode;
      തിരഞ്ഞെടുപ്പ് (modifycode)
	{
	അവസ്ഥ PLUS_വ്യഞ്ജകം:
	അവസ്ഥ POINTER_PLUS_വ്യഞ്ജകം:
	  fncode = (return_old_p
		    ? BUILT_IN_ATOMIC_FETCH_ADD_N
		    : BUILT_IN_ATOMIC_ADD_FETCH_N);
	  നിർത്തുക;
	അവസ്ഥ MINUS_വ്യഞ്ജകം:
	  fncode = (return_old_p
		    ? BUILT_IN_ATOMIC_FETCH_SUB_N
		    : BUILT_IN_ATOMIC_SUB_FETCH_N);
	  നിർത്തുക;
	അവസ്ഥ BIT_AND_വ്യഞ്ജകം:
	  fncode = (return_old_p
		    ? BUILT_IN_ATOMIC_FETCH_AND_N
		    : BUILT_IN_ATOMIC_AND_FETCH_N);
	  നിർത്തുക;
	അവസ്ഥ BIT_IOR_വ്യഞ്ജകം:
	  fncode = (return_old_p
		    ? BUILT_IN_ATOMIC_FETCH_OR_N
		    : BUILT_IN_ATOMIC_OR_FETCH_N);
	  നിർത്തുക;
	അവസ്ഥ BIT_XOR_വ്യഞ്ജകം:
	  fncode = (return_old_p
		    ? BUILT_IN_ATOMIC_FETCH_XOR_N
		    : BUILT_IN_ATOMIC_XOR_FETCH_N);
	  നിർത്തുക;
	സ്ഥിരസ്ഥിതി:
	  പോകുക cas_loop;
	}

      /* We can only use "_1" through "_16" variants of the atomic fetch
	 built-ins.  */
      unsigned HOST_WIDE_INT size = വൃക്ഷം_to_uhwi (TYPE_SIZE_UNIT (lhs_type));
      എങ്കിൽ (size != 1 && size != 2 && size != 4 && size != 8 && size != 16)
	പോകുക cas_loop;

      /* If this is a pointer type, we need to multiply by the size of
	 the pointer target type.  */
      എങ്കിൽ (POINTER_TYPE_P (lhs_type))
	{
	  എങ്കിൽ (!COMPLETE_TYPE_P (വൃക്ഷം_TYPE (lhs_type))
	      /* ??? This would introduce -Wdiscarded-qualifiers
		 warning: __atomic_fetch_* expect volatile void *
		 type as the first argument.  (Assignments between
		 atomic and non-atomic objects are OK.) */
	      || TYPE_RESTRICT (lhs_type))
	    പോകുക cas_loop;
	  വൃക്ഷം sz = TYPE_SIZE_UNIT (വൃക്ഷം_TYPE (lhs_type));
	  rhs = fold_build2_loc (loc, MULT_വ്യഞ്ജകം, ptrdiff_type_കണ്ണി,
				 convert (ptrdiff_type_കണ്ണി, rhs),
				 convert (ptrdiff_type_കണ്ണി, sz));
	}

      /* Build __atomic_fetch_* (&lhs, &val, SEQ_CST), or
	 __atomic_*_fetch (&lhs, &val, SEQ_CST).  */
      fndecl = builtin_decl_explicit (fncode);
      params->quick_തള്ളുക (lhs_addr);
      params->quick_തള്ളുക (rhs);
      params->quick_തള്ളുക (seq_cst);
      func_call = c_build_function_call_vec (loc, vNULL, fndecl, params, ശൂന്യ);

      newval = create_tmp_var_raw (nonatomic_lhs_type);
      വൃക്ഷം_ADDRESSABLE (newval) = 1;
      suppress_warning (newval);
      rhs = build4 (TARGET_വ്യഞ്ജകം, nonatomic_lhs_type, newval, func_call,
		    NULL_വൃക്ഷം, NULL_വൃക്ഷം);
      SET_വ്യഞ്ജകം_LOCATION (rhs, loc);
      add_stmt (rhs);

      /* Finish the compound statement.  */
      compound_stmt = c_end_compound_stmt (loc, compound_stmt, അസത്യം);

      /* NEWVAL is the value which was stored, return a COMPOUND_STMT of
	 the statement and that value.  */
      തിരികെ build2 (COMPOUND_വ്യഞ്ജകം, nonatomic_lhs_type, compound_stmt, newval);
    }

cas_loop:
  /* Create the variables and labels required for the op= form.  */
  old = create_tmp_var_raw (nonatomic_lhs_type);
  old_addr = build_unary_op (loc, ADDR_വ്യഞ്ജകം, old, അസത്യം);
  വൃക്ഷം_ADDRESSABLE (old) = 1;
  suppress_warning (old);

  newval = create_tmp_var_raw (nonatomic_lhs_type);
  newval_addr = build_unary_op (loc, ADDR_വ്യഞ്ജകം, newval, അസത്യം);
  വൃക്ഷം_ADDRESSABLE (newval) = 1;
  suppress_warning (newval);

  loop_decl = create_artificial_label (loc);
  loop_label = build1 (LABEL_വ്യഞ്ജകം, void_type_കണ്ണി, loop_decl);

  done_decl = create_artificial_label (loc);
  done_label = build1 (LABEL_വ്യഞ്ജകം, void_type_കണ്ണി, done_decl);

  /* __atomic_load (addr, &old, SEQ_CST).  */
  fndecl = builtin_decl_explicit (BUILT_IN_ATOMIC_LOAD);
  params->quick_തള്ളുക (lhs_addr);
  params->quick_തള്ളുക (old_addr);
  params->quick_തള്ളുക (seq_cst);
  func_call = c_build_function_call_vec (loc, vNULL, fndecl, params, ശൂന്യ);
  old = build4 (TARGET_വ്യഞ്ജകം, nonatomic_lhs_type, old, func_call, NULL_വൃക്ഷം,
		NULL_വൃക്ഷം);
  add_stmt (old);
  params->truncate (0);

  /* Create the expressions for floating-point environment
     manipulation, if required.  */
  തർക്കം need_fenv = (flag_trapping_math
		    && (FLOAT_TYPE_P (lhs_type) || FLOAT_TYPE_P (rhs_type)));
  വൃക്ഷം hold_call = NULL_വൃക്ഷം, clear_call = NULL_വൃക്ഷം, update_call = NULL_വൃക്ഷം;
  എങ്കിൽ (need_fenv)
    targetm.atomic_assign_expand_fenv (&hold_call, &clear_call, &update_call);

  എങ്കിൽ (hold_call)
    add_stmt (hold_call);

  /* loop:  */
  add_stmt (loop_label);

  /* newval = old + val;  */
  എങ്കിൽ (rhs_type != rhs_semantic_type)
    val = build1 (EXCESS_PRECISION_വ്യഞ്ജകം, nonatomic_rhs_semantic_type, val);
  rhs = build_ദ്വിമാന_op (loc, modifycode,
			 convert_lvalue_to_rvalue (loc, old, സത്യം, സത്യം),
			 val, സത്യം);
  എങ്കിൽ (വൃക്ഷം_CODE (rhs) == EXCESS_PRECISION_വ്യഞ്ജകം)
    {
      വൃക്ഷം eptype = വൃക്ഷം_TYPE (rhs);
      rhs = c_fully_fold (വൃക്ഷം_OPERAND (rhs, 0), അസത്യം, ശൂന്യ);
      rhs = build1 (EXCESS_PRECISION_വ്യഞ്ജകം, eptype, rhs);
    }
  അല്ലെങ്കിൽ
    rhs = c_fully_fold (rhs, അസത്യം, ശൂന്യ);
  rhs = convert_for_assignment (loc, UNKNOWN_LOCATION, nonatomic_lhs_type,
				rhs, NULL_വൃക്ഷം, ic_assign, അസത്യം, NULL_വൃക്ഷം,
				NULL_വൃക്ഷം, 0);
  /* The temporary variable for NEWVAL is only gimplified correctly (in
     particular, given a DECL_CONTEXT) if used in a TARGET_EXPR.  To avoid
     subsequent ICEs in nested function processing after an error, ensure such
     a TARGET_EXPR is built even after an error.  */
  എങ്കിൽ (rhs == error_mark_കണ്ണി)
    rhs = old;
  rhs = build4 (TARGET_വ്യഞ്ജകം, nonatomic_lhs_type, newval, rhs, NULL_വൃക്ഷം,
		NULL_വൃക്ഷം);
  SET_വ്യഞ്ജകം_LOCATION (rhs, loc);
  add_stmt (rhs);

  /* if (__atomic_compare_exchange (addr, &old, &new, false, SEQ_CST, SEQ_CST))
       goto done;  */
  fndecl = builtin_decl_explicit (BUILT_IN_ATOMIC_COMPARE_EXCHANGE);
  params->quick_തള്ളുക (lhs_addr);
  params->quick_തള്ളുക (old_addr);
  params->quick_തള്ളുക (newval_addr);
  params->quick_തള്ളുക (integer_zero_കണ്ണി);
  params->quick_തള്ളുക (seq_cst);
  params->quick_തള്ളുക (seq_cst);
  func_call = c_build_function_call_vec (loc, vNULL, fndecl, params, ശൂന്യ);

  goto_stmt = build1 (GOTO_വ്യഞ്ജകം, void_type_കണ്ണി, done_decl);
  SET_വ്യഞ്ജകം_LOCATION (goto_stmt, loc);

  stmt = build3 (COND_വ്യഞ്ജകം, void_type_കണ്ണി, func_call, goto_stmt, NULL_വൃക്ഷം);
  SET_വ്യഞ്ജകം_LOCATION (stmt, loc);
  add_stmt (stmt);

  എങ്കിൽ (clear_call)
    add_stmt (clear_call);

  /* goto loop;  */
  goto_stmt  = build1 (GOTO_വ്യഞ്ജകം, void_type_കണ്ണി, loop_decl);
  SET_വ്യഞ്ജകം_LOCATION (goto_stmt, loc);
  add_stmt (goto_stmt);

  /* done:  */
  add_stmt (done_label);

  എങ്കിൽ (update_call)
    add_stmt (update_call);

  /* Finish the compound statement.  */
  compound_stmt = c_end_compound_stmt (loc, compound_stmt, അസത്യം);

  /* NEWVAL is the value that was successfully stored, return a
     COMPOUND_EXPR of the statement and the appropriate value.  */
  തിരികെ build2 (COMPOUND_വ്യഞ്ജകം, nonatomic_lhs_type, compound_stmt,
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

വൃക്ഷം
build_unary_op (location_t location, എണ്ണൽ വൃക്ഷം_code code, വൃക്ഷം xarg,
		തർക്കം noconvert)
{
  /* No default_conversion here.  It causes trouble for ADDR_EXPR.  */
  വൃക്ഷം arg = xarg;
  വൃക്ഷം argtype = NULL_വൃക്ഷം;
  എണ്ണൽ വൃക്ഷം_code typecode;
  വൃക്ഷം val;
  വൃക്ഷം ret = error_mark_കണ്ണി;
  വൃക്ഷം eptype = NULL_വൃക്ഷം;
  സ്ഥിരം അക്ഷരം *invalid_op_diag;

  /* If ARG is wrapped in a call to .ACCESS_WITH_SIZE — created when the
     C parser rvalue-converts a counted_by-annotated member access (see
     PR123569) — unwrap it here.  Unary operators that consume an rvalue
     (!, -, +) read the value itself rather than dereferencing into the
     pointed-to data, so the bounds-checking wrapper is unnecessary and
     would otherwise reach build_unary_op while it is not equipped to
     handle the wrapped form.  PR123569 fixed the ++/-- side of this by
     suppressing wrapper creation in the parser; the rvalue-consuming
     ops still receive the wrapper and need to strip it here.  */
  എങ്കിൽ (is_access_with_size_p (arg))
    xarg = arg = get_ref_from_access_with_size (arg);

  gcc_checking_assert (!is_access_with_size_p (arg));

  തർക്കം int_operands = വ്യഞ്ജകം_INT_CONST_OPERANDS (xarg);
  എങ്കിൽ (int_operands)
    arg = remove_c_maybe_const_വ്യഞ്ജകം (arg);

  എങ്കിൽ (code != ADDR_വ്യഞ്ജകം)
    arg = require_complete_type (location, arg);

  typecode = വൃക്ഷം_CODE (വൃക്ഷം_TYPE (arg));
  എങ്കിൽ (typecode == ERROR_MARK)
    തിരികെ error_mark_കണ്ണി;
  എങ്കിൽ (typecode == ENUMERAL_TYPE || typecode == BOOLEAN_TYPE)
    typecode = INTEGER_TYPE;

  എങ്കിൽ ((invalid_op_diag
       = targetm.invalid_unary_op (code, വൃക്ഷം_TYPE (xarg))))
    {
      error_at (location, invalid_op_diag);
      തിരികെ error_mark_കണ്ണി;
    }

  എങ്കിൽ (വൃക്ഷം_CODE (arg) == EXCESS_PRECISION_വ്യഞ്ജകം)
    {
      eptype = വൃക്ഷം_TYPE (arg);
      arg = വൃക്ഷം_OPERAND (arg, 0);
    }

  തിരഞ്ഞെടുപ്പ് (code)
    {
    അവസ്ഥ CONVERT_വ്യഞ്ജകം:
      /* This is used for unary plus, because a CONVERT_EXPR
	 is enough to prevent anybody from looking inside for
	 associativity, but won't generate any code.  */
      എങ്കിൽ (!(typecode == INTEGER_TYPE || typecode == REAL_TYPE
	    || typecode == FIXED_POINT_TYPE || typecode == COMPLEX_TYPE
	    || typecode == BITINT_TYPE
	    || gnu_vector_type_p (വൃക്ഷം_TYPE (arg))))
	{
	  error_at (location, "wrong type argument to unary plus");
	  തിരികെ error_mark_കണ്ണി;
	}
      അല്ലെങ്കിൽ എങ്കിൽ (!noconvert)
	arg = default_conversion (arg);
      arg = non_lvalue_loc (location, arg);
      നിർത്തുക;

    അവസ്ഥ NEGATE_വ്യഞ്ജകം:
      എങ്കിൽ (!(typecode == INTEGER_TYPE || typecode == REAL_TYPE
	    || typecode == FIXED_POINT_TYPE || typecode == COMPLEX_TYPE
	    || typecode == BITINT_TYPE
	    || gnu_vector_type_p (വൃക്ഷം_TYPE (arg))))
	{
	  error_at (location, "wrong type argument to unary minus");
	  തിരികെ error_mark_കണ്ണി;
	}
      അല്ലെങ്കിൽ എങ്കിൽ (!noconvert)
	arg = default_conversion (arg);
      നിർത്തുക;

    അവസ്ഥ BIT_NOT_വ്യഞ്ജകം:
      /* ~ works on integer types and non float vectors. */
      എങ്കിൽ (typecode == INTEGER_TYPE
	  || typecode == BITINT_TYPE
	  || (gnu_vector_type_p (വൃക്ഷം_TYPE (arg))
	      && !VECTOR_FLOAT_TYPE_P (വൃക്ഷം_TYPE (arg))))
	{
	  വൃക്ഷം e = arg;

	  /* Warn if the expression has boolean value.  */
	  ആകുമ്പോൾ (വൃക്ഷം_CODE (e) == COMPOUND_വ്യഞ്ജകം)
	    e = വൃക്ഷം_OPERAND (e, 1);

	  എങ്കിൽ ((C_BOOLEAN_TYPE_P (വൃക്ഷം_TYPE (arg))
	       || truth_മൂല്യം_p (വൃക്ഷം_CODE (e))))
	    {
	      auto_diagnostic_group d;
	      എങ്കിൽ (warning_at (location, OPT_Wbool_operation,
				"%<~%> on a boolean expression"))
		{
		  gcc_rich_location richloc (location);
		  richloc.add_fixit_തിരുകുക_before (location, "!");
		  inform (&richloc, "did you mean to use logical not?");
		}
	    }
	  എങ്കിൽ (!noconvert)
	    arg = default_conversion (arg);
	}
      അല്ലെങ്കിൽ എങ്കിൽ (typecode == COMPLEX_TYPE)
	{
	  code = CONJ_വ്യഞ്ജകം;
	  pedwarn (location, OPT_Wpedantic,
		   "ISO C does not support %<~%> for complex conjugation");
	  എങ്കിൽ (!noconvert)
	    arg = default_conversion (arg);
	}
      അല്ലെങ്കിൽ
	{
	  error_at (location, "wrong type argument to bit-complement");
	  തിരികെ error_mark_കണ്ണി;
	}
      നിർത്തുക;

    അവസ്ഥ ABS_വ്യഞ്ജകം:
      എങ്കിൽ (!(typecode == INTEGER_TYPE || typecode == REAL_TYPE))
	{
	  error_at (location, "wrong type argument to abs");
	  തിരികെ error_mark_കണ്ണി;
	}
      അല്ലെങ്കിൽ എങ്കിൽ (!noconvert)
	arg = default_conversion (arg);
      നിർത്തുക;

    അവസ്ഥ ABSU_വ്യഞ്ജകം:
      എങ്കിൽ (!(typecode == INTEGER_TYPE))
	{
	  error_at (location, "wrong type argument to absu");
	  തിരികെ error_mark_കണ്ണി;
	}
      അല്ലെങ്കിൽ എങ്കിൽ (!noconvert)
	arg = default_conversion (arg);
      നിർത്തുക;

    അവസ്ഥ CONJ_വ്യഞ്ജകം:
      /* Conjugating a real value is a no-op, but allow it anyway.  */
      എങ്കിൽ (!(typecode == INTEGER_TYPE || typecode == REAL_TYPE
	    || typecode == COMPLEX_TYPE))
	{
	  error_at (location, "wrong type argument to conjugation");
	  തിരികെ error_mark_കണ്ണി;
	}
      അല്ലെങ്കിൽ എങ്കിൽ (!noconvert)
	arg = default_conversion (arg);
      നിർത്തുക;

    അവസ്ഥ TRUTH_NOT_വ്യഞ്ജകം:
      എങ്കിൽ (typecode != INTEGER_TYPE && typecode != FIXED_POINT_TYPE
	  && typecode != REAL_TYPE && typecode != POINTER_TYPE
	  && typecode != COMPLEX_TYPE && typecode != NULLPTR_TYPE
	  && typecode != BITINT_TYPE)
	{
	  error_at (location,
		    "wrong type argument to unary exclamation mark");
	  തിരികെ error_mark_കണ്ണി;
	}
      എങ്കിൽ (int_operands)
	{
	  arg = c_objc_common_truthvalue_conversion (location, xarg);
	  arg = remove_c_maybe_const_വ്യഞ്ജകം (arg);
	}
      അല്ലെങ്കിൽ
	arg = c_objc_common_truthvalue_conversion (location, arg);
      ret = invert_truthvalue_loc (location, arg);
      eptype = NULL_വൃക്ഷം;
      /* If the TRUTH_NOT_EXPR has been folded, reset the location.  */
      എങ്കിൽ (വ്യഞ്ജകം_P (ret) && വ്യഞ്ജകം_HAS_LOCATION (ret))
	location = വ്യഞ്ജകം_LOCATION (ret);
      പോകുക return_build_unary_op;

    അവസ്ഥ REALPART_വ്യഞ്ജകം:
    അവസ്ഥ IMAGPART_വ്യഞ്ജകം:
      ret = build_real_imag_വ്യഞ്ജകം (location, code, arg);
      എങ്കിൽ (ret == error_mark_കണ്ണി)
	തിരികെ error_mark_കണ്ണി;
      എങ്കിൽ (eptype && വൃക്ഷം_CODE (eptype) == COMPLEX_TYPE)
	eptype = വൃക്ഷം_TYPE (eptype);
      പോകുക return_build_unary_op;

    അവസ്ഥ PREINCREMENT_വ്യഞ്ജകം:
    അവസ്ഥ POSTINCREMENT_വ്യഞ്ജകം:
    അവസ്ഥ PREDECREMENT_വ്യഞ്ജകം:
    അവസ്ഥ POSTDECREMENT_വ്യഞ്ജകം:

      എങ്കിൽ (വൃക്ഷം_CODE (arg) == C_MAYBE_CONST_വ്യഞ്ജകം)
	{
	  വൃക്ഷം inner = build_unary_op (location, code,
				       C_MAYBE_CONST_വ്യഞ്ജകം_വ്യഞ്ജകം (arg),
				       noconvert);
	  എങ്കിൽ (inner == error_mark_കണ്ണി)
	    തിരികെ error_mark_കണ്ണി;
	  ret = build2 (C_MAYBE_CONST_വ്യഞ്ജകം, വൃക്ഷം_TYPE (inner),
			C_MAYBE_CONST_വ്യഞ്ജകം_PRE (arg), inner);
	  gcc_assert (!C_MAYBE_CONST_വ്യഞ്ജകം_INT_OPERANDS (arg));
	  C_MAYBE_CONST_വ്യഞ്ജകം_NON_CONST (ret) = 1;
	  പോകുക return_build_unary_op;
	}

      /* Complain about anything that is not a true lvalue.  In
	 Objective-C, skip this check for property_refs.  */
      എങ്കിൽ (!objc_is_property_ref (arg)
	  && !lvalue_or_else (location,
			      arg, ((code == PREINCREMENT_വ്യഞ്ജകം
				     || code == POSTINCREMENT_വ്യഞ്ജകം)
				    ? lv_increment
				    : lv_decrement)))
	തിരികെ error_mark_കണ്ണി;

      എങ്കിൽ (warn_cxx_compat && വൃക്ഷം_CODE (വൃക്ഷം_TYPE (arg)) == ENUMERAL_TYPE)
	{
	  എങ്കിൽ (code == PREINCREMENT_വ്യഞ്ജകം || code == POSTINCREMENT_വ്യഞ്ജകം)
	    warning_at (location, OPT_Wc___compat,
			"increment of enumeration value is invalid in C++");
	  അല്ലെങ്കിൽ
	    warning_at (location, OPT_Wc___compat,
			"decrement of enumeration value is invalid in C++");
	}

      എങ്കിൽ (C_BOOLEAN_TYPE_P (വൃക്ഷം_TYPE (arg)))
	{
	  എങ്കിൽ (code == PREINCREMENT_വ്യഞ്ജകം || code == POSTINCREMENT_വ്യഞ്ജകം)
	    warning_at (location, OPT_Wbool_operation,
			"increment of a boolean expression");
	  അല്ലെങ്കിൽ
	    warning_at (location, OPT_Wbool_operation,
			"decrement of a boolean expression");
	}

      /* Ensure the argument is fully folded inside any SAVE_EXPR.  */
      arg = c_fully_fold (arg, അസത്യം, ശൂന്യ, സത്യം);

      തർക്കം atomic_op;
      atomic_op = really_atomic_lvalue (arg);

      /* Increment or decrement the real part of the value,
	 and don't change the imaginary part.  */
      എങ്കിൽ (typecode == COMPLEX_TYPE)
	{
	  വൃക്ഷം real, imag;

	  pedwarn_c23 (location, OPT_Wpedantic,
		       "ISO C does not support %<++%> and %<--%> on complex "
		       "types before C2Y");

	  എങ്കിൽ (!atomic_op)
	    {
	      arg = stabilize_reference (arg);
	      real = build_unary_op (വ്യഞ്ജകം_LOCATION (arg), REALPART_വ്യഞ്ജകം, arg,
				     സത്യം);
	      imag = build_unary_op (വ്യഞ്ജകം_LOCATION (arg), IMAGPART_വ്യഞ്ജകം, arg,
				     സത്യം);
	      real = build_unary_op (വ്യഞ്ജകം_LOCATION (arg), code, real, സത്യം);
	      എങ്കിൽ (real == error_mark_കണ്ണി || imag == error_mark_കണ്ണി)
		തിരികെ error_mark_കണ്ണി;
	      ret = build2 (COMPLEX_വ്യഞ്ജകം, വൃക്ഷം_TYPE (arg),
			    real, imag);
	      പോകുക return_build_unary_op;
	    }
	}

      /* Report invalid types.  */

      എങ്കിൽ (typecode != POINTER_TYPE && typecode != FIXED_POINT_TYPE
	  && typecode != INTEGER_TYPE && typecode != REAL_TYPE
	  && typecode != COMPLEX_TYPE && typecode != BITINT_TYPE
	  && !gnu_vector_type_p (വൃക്ഷം_TYPE (arg)))
	{
	  എങ്കിൽ (code == PREINCREMENT_വ്യഞ്ജകം || code == POSTINCREMENT_വ്യഞ്ജകം)
	    error_at (location, "wrong type argument to increment");
	  അല്ലെങ്കിൽ
	    error_at (location, "wrong type argument to decrement");

	  തിരികെ error_mark_കണ്ണി;
	}

      {
	വൃക്ഷം inc;

	argtype = വൃക്ഷം_TYPE (arg);

	/* Compute the increment.  */

	എങ്കിൽ (typecode == POINTER_TYPE)
	  {
	    /* If pointer target is an incomplete type,
	       we just cannot know how to do the arithmetic.  */
	    എങ്കിൽ (!COMPLETE_OR_VOID_TYPE_P (വൃക്ഷം_TYPE (argtype)))
	      {
		എങ്കിൽ (code == PREINCREMENT_വ്യഞ്ജകം || code == POSTINCREMENT_വ്യഞ്ജകം)
		  error_at (location,
			    "increment of pointer to an incomplete type %qT",
			    വൃക്ഷം_TYPE (argtype));
		അല്ലെങ്കിൽ
		  error_at (location,
			    "decrement of pointer to an incomplete type %qT",
			    വൃക്ഷം_TYPE (argtype));
	      }
	    അല്ലെങ്കിൽ എങ്കിൽ (വൃക്ഷം_CODE (വൃക്ഷം_TYPE (argtype)) == FUNCTION_TYPE
		     || VOID_TYPE_P (വൃക്ഷം_TYPE (argtype)))
	      {
		എങ്കിൽ (code == PREINCREMENT_വ്യഞ്ജകം || code == POSTINCREMENT_വ്യഞ്ജകം)
		  pedwarn (location, OPT_Wpointer_arith,
			   "wrong type argument to increment");
		അല്ലെങ്കിൽ
		  pedwarn (location, OPT_Wpointer_arith,
			   "wrong type argument to decrement");
	      }
	    അല്ലെങ്കിൽ
	      verify_type_context (location, TCTX_POINTER_ARITH,
				   വൃക്ഷം_TYPE (argtype));

	    inc = c_size_in_bytes (വൃക്ഷം_TYPE (argtype));
	    inc = convert_to_ptrofftype_loc (location, inc);
	  }
	അല്ലെങ്കിൽ എങ്കിൽ (FRACT_MODE_P (TYPE_MODE (argtype)))
	  {
	    /* For signed fract types, we invert ++ to -- or
	       -- to ++, and change inc from 1 to -1, because
	       it is not possible to represent 1 in signed fract constants.
	       For unsigned fract types, the result always overflows and
	       we get an undefined (original) or the maximum value.  */
	    എങ്കിൽ (code == PREINCREMENT_വ്യഞ്ജകം)
	      code = PREDECREMENT_വ്യഞ്ജകം;
	    അല്ലെങ്കിൽ എങ്കിൽ (code == PREDECREMENT_വ്യഞ്ജകം)
	      code = PREINCREMENT_വ്യഞ്ജകം;
	    അല്ലെങ്കിൽ എങ്കിൽ (code == POSTINCREMENT_വ്യഞ്ജകം)
	      code = POSTDECREMENT_വ്യഞ്ജകം;
	    അല്ലെങ്കിൽ /* code == POSTDECREMENT_EXPR  */
	      code = POSTINCREMENT_വ്യഞ്ജകം;

	    inc = integer_minus_one_കണ്ണി;
	    inc = convert (argtype, inc);
	  }
	അല്ലെങ്കിൽ
	  {
	    inc = VECTOR_TYPE_P (argtype)
	      ? build_one_cst (argtype)
	      : integer_one_കണ്ണി;
	    inc = convert (argtype, inc);
	  }

	/* If 'arg' is an Objective-C PROPERTY_REF expression, then we
	   need to ask Objective-C to build the increment or decrement
	   expression for it.  */
	എങ്കിൽ (objc_is_property_ref (arg))
	  തിരികെ objc_build_incr_വ്യഞ്ജകം_for_property_ref (location, code,
							arg, inc);

	/* Report a read-only lvalue.  */
	എങ്കിൽ (TYPE_READONLY (argtype))
	  {
	    readonly_error (location, arg,
			    ((code == PREINCREMENT_വ്യഞ്ജകം
			      || code == POSTINCREMENT_വ്യഞ്ജകം)
			     ? lv_increment : lv_decrement));
	    തിരികെ error_mark_കണ്ണി;
	  }
	അല്ലെങ്കിൽ എങ്കിൽ (വൃക്ഷം_READONLY (arg))
	  readonly_warning (arg,
			    ((code == PREINCREMENT_വ്യഞ്ജകം
			      || code == POSTINCREMENT_വ്യഞ്ജകം)
			     ? lv_increment : lv_decrement));

	/* If the argument is atomic, use the special code sequences for
	   atomic compound assignment.  */
	എങ്കിൽ (atomic_op)
	  {
	    arg = stabilize_reference (arg);
	    ret = build_atomic_assign (location, arg,
				       ((code == PREINCREMENT_വ്യഞ്ജകം
					 || code == POSTINCREMENT_വ്യഞ്ജകം)
					? PLUS_വ്യഞ്ജകം
					: MINUS_വ്യഞ്ജകം),
				       (FRACT_MODE_P (TYPE_MODE (argtype))
					? inc
					: integer_one_കണ്ണി),
				       (code == POSTINCREMENT_വ്യഞ്ജകം
					|| code == POSTDECREMENT_വ്യഞ്ജകം));
	    പോകുക return_build_unary_op;
	  }

	വൃക്ഷം true_res;
	എങ്കിൽ (c_hardbool_type_attr (വൃക്ഷം_TYPE (arg), ശൂന്യ, &true_res))
	  {
	    വൃക്ഷം larg = stabilize_reference (arg);
	    വൃക്ഷം sarg = save_വ്യഞ്ജകം (larg);
	    തിരഞ്ഞെടുപ്പ് (code)
	      {
	      അവസ്ഥ PREINCREMENT_വ്യഞ്ജകം:
		val = build2 (MODIFY_വ്യഞ്ജകം, വൃക്ഷം_TYPE (larg), larg, true_res);
		val = build2 (COMPOUND_വ്യഞ്ജകം, വൃക്ഷം_TYPE (larg), sarg, val);
		നിർത്തുക;
	      അവസ്ഥ POSTINCREMENT_വ്യഞ്ജകം:
		val = build2 (MODIFY_വ്യഞ്ജകം, വൃക്ഷം_TYPE (larg), larg, true_res);
		val = build2 (COMPOUND_വ്യഞ്ജകം, വൃക്ഷം_TYPE (larg), val, sarg);
		val = build2 (COMPOUND_വ്യഞ്ജകം, വൃക്ഷം_TYPE (larg), sarg, val);
		നിർത്തുക;
	      അവസ്ഥ PREDECREMENT_വ്യഞ്ജകം:
		{
		  വൃക്ഷം rarg = convert_lvalue_to_rvalue (location, sarg,
							സത്യം, സത്യം);
		  rarg = invert_truthvalue_loc (location, rarg);
		  rarg = convert (വൃക്ഷം_TYPE (sarg), rarg);
		  val = build2 (MODIFY_വ്യഞ്ജകം, വൃക്ഷം_TYPE (larg), larg, rarg);
		}
		നിർത്തുക;
	      അവസ്ഥ POSTDECREMENT_വ്യഞ്ജകം:
		{
		  വൃക്ഷം rarg = convert_lvalue_to_rvalue (location, sarg,
							സത്യം, സത്യം);
		  rarg = invert_truthvalue_loc (location, rarg);
		  വൃക്ഷം iarg = convert (വൃക്ഷം_TYPE (larg), rarg);
		  val = build2 (MODIFY_വ്യഞ്ജകം, വൃക്ഷം_TYPE (larg), larg, iarg);
		  val = build2 (COMPOUND_വ്യഞ്ജകം, വൃക്ഷം_TYPE (larg), val, sarg);
		  val = build2 (COMPOUND_വ്യഞ്ജകം, വൃക്ഷം_TYPE (larg), sarg, val);
		}
		നിർത്തുക;
	      സ്ഥിരസ്ഥിതി:
		gcc_unreachable ();
	      }
	    വൃക്ഷം_SIDE_EFFECTS (val) = 1;
	  }
	അല്ലെങ്കിൽ എങ്കിൽ (C_BOOLEAN_TYPE_P (വൃക്ഷം_TYPE (arg)))
	  val = boolean_increment (code, arg);
	അല്ലെങ്കിൽ
	  val = build2 (code, വൃക്ഷം_TYPE (arg), arg, inc);
	വൃക്ഷം_SIDE_EFFECTS (val) = 1;
	എങ്കിൽ (TYPE_QUALS (വൃക്ഷം_TYPE (val)) != TYPE_UNQUALIFIED)
	  വൃക്ഷം_TYPE (val) = c_build_qualified_type (വൃക്ഷം_TYPE (val),
						    TYPE_UNQUALIFIED);
	ret = val;
	പോകുക return_build_unary_op;
      }

    അവസ്ഥ ADDR_വ്യഞ്ജകം:
      /* Note that this operation never does default_conversion.  */

      /* The operand of unary '&' must be an lvalue (which excludes
	 expressions of type void), or, in C99, the result of a [] or
	 unary '*' operator.  */
      എങ്കിൽ (VOID_TYPE_P (വൃക്ഷം_TYPE (arg))
	  && TYPE_QUALS (വൃക്ഷം_TYPE (arg)) == TYPE_UNQUALIFIED
	  && (!INDIRECT_REF_P (arg) || !flag_isoc99))
	pedwarn (location, 0, "taking address of expression of type %<void%>");

      /* Let &* cancel out to simplify resulting code.  */
      എങ്കിൽ (INDIRECT_REF_P (arg))
	{
	  /* Don't let this be an lvalue.  */
	  എങ്കിൽ (lvalue_p (വൃക്ഷം_OPERAND (arg, 0)))
	    തിരികെ non_lvalue_loc (location, വൃക്ഷം_OPERAND (arg, 0));
	  ret = വൃക്ഷം_OPERAND (arg, 0);
	  പോകുക return_build_unary_op;
	}

      /* Anything not already handled and not a true memory reference
	 or a non-lvalue array is an error.  */
      എങ്കിൽ (typecode != FUNCTION_TYPE && !noconvert
	  && !lvalue_or_else (location, arg, lv_addressof))
	തിരികെ error_mark_കണ്ണി;

      /* Move address operations inside C_MAYBE_CONST_EXPR to simplify
	 folding later.  */
      എങ്കിൽ (വൃക്ഷം_CODE (arg) == C_MAYBE_CONST_വ്യഞ്ജകം)
	{
	  വൃക്ഷം inner = build_unary_op (location, code,
				       C_MAYBE_CONST_വ്യഞ്ജകം_വ്യഞ്ജകം (arg),
				       noconvert);
	  ret = build2 (C_MAYBE_CONST_വ്യഞ്ജകം, വൃക്ഷം_TYPE (inner),
			C_MAYBE_CONST_വ്യഞ്ജകം_PRE (arg), inner);
	  gcc_assert (!C_MAYBE_CONST_വ്യഞ്ജകം_INT_OPERANDS (arg));
	  C_MAYBE_CONST_വ്യഞ്ജകം_NON_CONST (ret)
	    = C_MAYBE_CONST_വ്യഞ്ജകം_NON_CONST (arg);
	  പോകുക return_build_unary_op;
	}

      /* Ordinary case; arg is a COMPONENT_REF or a decl.  */

      argtype = വൃക്ഷം_TYPE (arg);

      /* If the lvalue is const or volatile, merge that into the type
	 to which the address will point.  This is only needed
	 for function types.  */
      എങ്കിൽ ((DECL_P (arg) || REFERENCE_CLASS_P (arg))
	  && (വൃക്ഷം_READONLY (arg) || വൃക്ഷം_THIS_VOLATILE (arg))
	  && വൃക്ഷം_CODE (argtype) == FUNCTION_TYPE)
	{
	  പൂർണ്ണസംഖ്യ orig_quals = TYPE_QUALS (strip_array_types (argtype));
	  പൂർണ്ണസംഖ്യ quals = orig_quals;

	  എങ്കിൽ (വൃക്ഷം_READONLY (arg))
	    quals |= TYPE_QUAL_CONST;
	  എങ്കിൽ (വൃക്ഷം_THIS_VOLATILE (arg))
	    quals |= TYPE_QUAL_VOLATILE;

	  argtype = c_build_qualified_type (argtype, quals);
	}

      തിരഞ്ഞെടുപ്പ് (വൃക്ഷം_CODE (arg))
	{
	അവസ്ഥ COMPONENT_REF:
	  എങ്കിൽ (DECL_C_BIT_FIELD (വൃക്ഷം_OPERAND (arg, 1)))
	    {
	      error_at (location, "cannot take address of bit-field %qD",
			വൃക്ഷം_OPERAND (arg, 1));
	      തിരികെ error_mark_കണ്ണി;
	    }

	  /* fall through */

	അവസ്ഥ ARRAY_REF:
	  എങ്കിൽ (TYPE_REVERSE_STORAGE_ORDER (വൃക്ഷം_TYPE (വൃക്ഷം_OPERAND (arg, 0))))
	    {
	      എങ്കിൽ (!AGGREGATE_TYPE_P (വൃക്ഷം_TYPE (arg))
		  && !POINTER_TYPE_P (വൃക്ഷം_TYPE (arg))
		  && !VECTOR_TYPE_P (വൃക്ഷം_TYPE (arg)))
		{
		  error_at (location, "cannot take address of scalar with "
			    "reverse storage order");
		  തിരികെ error_mark_കണ്ണി;
		}

	      എങ്കിൽ (വൃക്ഷം_CODE (വൃക്ഷം_TYPE (arg)) == ARRAY_TYPE
		  && TYPE_REVERSE_STORAGE_ORDER (വൃക്ഷം_TYPE (arg)))
		warning_at (location, OPT_Wscalar_storage_order,
			    "address of array with reverse scalar storage "
			    "order requested");
	    }

	സ്ഥിരസ്ഥിതി:
	  നിർത്തുക;
	}

      എങ്കിൽ (!c_mark_addressable (arg))
	തിരികെ error_mark_കണ്ണി;

      gcc_assert (വൃക്ഷം_CODE (arg) != COMPONENT_REF
		  || !DECL_C_BIT_FIELD (വൃക്ഷം_OPERAND (arg, 1)));

      argtype = c_build_pointer_type (argtype);

      /* ??? Cope with user tricks that amount to offsetof.  Delete this
	 when we have proper support for integer constant expressions.  */
      val = get_base_address (arg);
      എങ്കിൽ (val && INDIRECT_REF_P (val)
          && വൃക്ഷം_CONSTANT (വൃക്ഷം_OPERAND (val, 0)))
	{
	  ret = fold_offsetof (arg, argtype);
	  പോകുക return_build_unary_op;
	}

      val = build1 (ADDR_വ്യഞ്ജകം, argtype, arg);

      ret = val;
      പോകുക return_build_unary_op;

    അവസ്ഥ PAREN_വ്യഞ്ജകം:
      ret = build1 (code, വൃക്ഷം_TYPE (arg), arg);
      പോകുക return_build_unary_op;

    സ്ഥിരസ്ഥിതി:
      gcc_unreachable ();
    }

  എങ്കിൽ (argtype == NULL_വൃക്ഷം)
    argtype = വൃക്ഷം_TYPE (arg);
  എങ്കിൽ (വൃക്ഷം_CODE (arg) == INTEGER_CST)
    ret = (require_constant_മൂല്യം
	   ? fold_build1_initializer_loc (location, code, argtype, arg)
	   : fold_build1_loc (location, code, argtype, arg));
  അല്ലെങ്കിൽ
    ret = build1 (code, argtype, arg);
 return_build_unary_op:
  gcc_assert (ret != error_mark_കണ്ണി);
  എങ്കിൽ (വൃക്ഷം_CODE (ret) == INTEGER_CST && !വൃക്ഷം_OVERFLOW (ret)
      && !(വൃക്ഷം_CODE (xarg) == INTEGER_CST && !വൃക്ഷം_OVERFLOW (xarg)))
    ret = build1 (NOP_വ്യഞ്ജകം, വൃക്ഷം_TYPE (ret), ret);
  അല്ലെങ്കിൽ എങ്കിൽ (വൃക്ഷം_CODE (ret) != INTEGER_CST && int_operands)
    ret = note_integer_operands (ret);
  എങ്കിൽ (eptype)
    ret = build1 (EXCESS_PRECISION_വ്യഞ്ജകം, eptype, ret);
  protected_set_വ്യഞ്ജകം_location (ret, location);
  തിരികെ ret;
}

/* Return nonzero if REF is an lvalue valid for this language.
   Lvalues can be assigned, unless their type has TYPE_READONLY.
   Lvalues can have their address taken, unless they have C_DECL_REGISTER.  */

തർക്കം
lvalue_p (const_വൃക്ഷം ref)
{
  സ്ഥിരം എണ്ണൽ വൃക്ഷം_code code = വൃക്ഷം_CODE (ref);

  തിരഞ്ഞെടുപ്പ് (code)
    {
    അവസ്ഥ REALPART_വ്യഞ്ജകം:
    അവസ്ഥ IMAGPART_വ്യഞ്ജകം:
    അവസ്ഥ COMPONENT_REF:
      തിരികെ lvalue_p (വൃക്ഷം_OPERAND (ref, 0));

    അവസ്ഥ C_MAYBE_CONST_വ്യഞ്ജകം:
      തിരികെ lvalue_p (വൃക്ഷം_OPERAND (ref, 1));

    അവസ്ഥ COMPOUND_LITERAL_വ്യഞ്ജകം:
    അവസ്ഥ STRING_CST:
      തിരികെ സത്യം;

    അവസ്ഥ MEM_REF:
    അവസ്ഥ TARGET_MEM_REF:
      /* MEM_REFs can appear from -fgimple parsing or folding, so allow them
	 here as well.  */
    അവസ്ഥ INDIRECT_REF:
    അവസ്ഥ ARRAY_REF:
    അവസ്ഥ VAR_DECL:
    അവസ്ഥ PARM_DECL:
    അവസ്ഥ RESULT_DECL:
    അവസ്ഥ ERROR_MARK:
      തിരികെ (വൃക്ഷം_CODE (വൃക്ഷം_TYPE (ref)) != FUNCTION_TYPE
	      && വൃക്ഷം_CODE (വൃക്ഷം_TYPE (ref)) != METHOD_TYPE);

    അവസ്ഥ BIND_വ്യഞ്ജകം:
      തിരികെ വൃക്ഷം_CODE (വൃക്ഷം_TYPE (ref)) == ARRAY_TYPE;

    അവസ്ഥ CALL_വ്യഞ്ജകം:
      തിരികെ is_access_with_size_p (ref);

    സ്ഥിരസ്ഥിതി:
      തിരികെ അസത്യം;
    }
}

/* Give a warning for storing in something that is read-only in GCC
   terms but not const in ISO C terms.  */

സ്ഥിതം ശൂന്യം
readonly_warning (വൃക്ഷം arg, എണ്ണൽ lvalue_use use)
{
  തിരഞ്ഞെടുപ്പ് (use)
    {
    അവസ്ഥ lv_assign:
      warning (0, "assignment of read-only location %qE", arg);
      നിർത്തുക;
    അവസ്ഥ lv_increment:
      warning (0, "increment of read-only location %qE", arg);
      നിർത്തുക;
    അവസ്ഥ lv_decrement:
      warning (0, "decrement of read-only location %qE", arg);
      നിർത്തുക;
    സ്ഥിരസ്ഥിതി:
      gcc_unreachable ();
    }
  തിരികെ;
}


/* Return nonzero if REF is an lvalue valid for this language;
   otherwise, print an error message and return zero.  USE says
   how the lvalue is being used and so selects the error message.
   LOCATION is the location at which any error should be reported.  */

സ്ഥിതം പൂർണ്ണസംഖ്യ
lvalue_or_else (location_t loc, const_വൃക്ഷം ref, എണ്ണൽ lvalue_use use)
{
  പൂർണ്ണസംഖ്യ win = lvalue_p (ref);

  എങ്കിൽ (!win)
    lvalue_error (loc, use);

  തിരികെ win;
}

/* Mark EXP saying that we need to be able to take the
   address of it; it should not be allocated in a register.
   Returns true if successful.  ARRAY_REF_P is true if this
   is for ARRAY_REF construction - in that case we don't want
   to look through VIEW_CONVERT_EXPR from VECTOR_TYPE to ARRAY_TYPE,
   it is fine to use ARRAY_REFs for vector subscripts on vector
   register variables.  If OVERRIDE_REGISTER, clear DECL_REGISTER rather
   than producing an error for taking the address of a register.  */

തർക്കം
c_mark_addressable (വൃക്ഷം exp, തർക്കം array_ref_p, തർക്കം override_register)
{
  വൃക്ഷം x = exp;

  ആകുമ്പോൾ (1)
    തിരഞ്ഞെടുപ്പ് (വൃക്ഷം_CODE (x))
      {
      അവസ്ഥ VIEW_CONVERT_വ്യഞ്ജകം:
	എങ്കിൽ (array_ref_p
	    && വൃക്ഷം_CODE (വൃക്ഷം_TYPE (x)) == ARRAY_TYPE
	    && VECTOR_TYPE_P (വൃക്ഷം_TYPE (വൃക്ഷം_OPERAND (x, 0))))
	  തിരികെ സത്യം;
	x = വൃക്ഷം_OPERAND (x, 0);
	നിർത്തുക;

      അവസ്ഥ COMPONENT_REF:
	എങ്കിൽ (DECL_C_BIT_FIELD (വൃക്ഷം_OPERAND (x, 1)))
	  {
	    error ("cannot take address of bit-field %qD",
		   വൃക്ഷം_OPERAND (x, 1));
	    തിരികെ അസത്യം;
	  }
	/* FALLTHRU */
      അവസ്ഥ ADDR_വ്യഞ്ജകം:
      അവസ്ഥ ARRAY_REF:
      അവസ്ഥ REALPART_വ്യഞ്ജകം:
      അവസ്ഥ IMAGPART_വ്യഞ്ജകം:
	x = വൃക്ഷം_OPERAND (x, 0);
	നിർത്തുക;

      അവസ്ഥ COMPOUND_LITERAL_വ്യഞ്ജകം:
	എങ്കിൽ (C_DECL_REGISTER (COMPOUND_LITERAL_വ്യഞ്ജകം_DECL (x)))
	  {
	    എങ്കിൽ (override_register)
	      DECL_REGISTER (COMPOUND_LITERAL_വ്യഞ്ജകം_DECL (x)) = 0;
	    അല്ലെങ്കിൽ
	      {
		error ("address of register compound literal requested");
		തിരികെ അസത്യം;
	      }
	  }
	വൃക്ഷം_ADDRESSABLE (x) = 1;
	വൃക്ഷം_ADDRESSABLE (COMPOUND_LITERAL_വ്യഞ്ജകം_DECL (x)) = 1;
	തിരികെ സത്യം;

      അവസ്ഥ CONSTRUCTOR:
	വൃക്ഷം_ADDRESSABLE (x) = 1;
	തിരികെ സത്യം;

      അവസ്ഥ VAR_DECL:
      അവസ്ഥ CONST_DECL:
      അവസ്ഥ PARM_DECL:
      അവസ്ഥ RESULT_DECL:
	എങ്കിൽ (C_DECL_REGISTER (x)
	    && DECL_NONLOCAL (x))
	  {
	    എങ്കിൽ (വൃക്ഷം_PUBLIC (x) || is_global_var (x))
	      {
		error
		  ("global register variable %qD used in nested function", x);
		തിരികെ അസത്യം;
	      }
	    pedwarn (നിവേശം_location, 0, "register variable %qD used in nested function", x);
	  }
	അല്ലെങ്കിൽ എങ്കിൽ (C_DECL_REGISTER (x))
	  {
	    എങ്കിൽ (വൃക്ഷം_PUBLIC (x) || is_global_var (x))
	      error ("address of global register variable %qD requested", x);
	    അല്ലെങ്കിൽ എങ്കിൽ (override_register && !DECL_HARD_REGISTER (x))
	      {
		DECL_REGISTER (x) = 0;
		വൃക്ഷം_ADDRESSABLE (x) = 1;
		mark_decl_used (x, സത്യം);
		തിരികെ സത്യം;
	      }
	    അല്ലെങ്കിൽ
	      error ("address of register variable %qD requested", x);
	    തിരികെ അസത്യം;
	  }

	/* FALLTHRU */
      അവസ്ഥ FUNCTION_DECL:
	വൃക്ഷം_ADDRESSABLE (x) = 1;
	mark_decl_used (x, സത്യം);
	/* FALLTHRU */
      സ്ഥിരസ്ഥിതി:
	തിരികെ സത്യം;
    }
}

/* Convert EXPR to TYPE, warning about conversion problems with
   constants.  SEMANTIC_TYPE is the type this conversion would use
   without excess precision. If SEMANTIC_TYPE is NULL, this function
   is equivalent to convert_and_check. This function is a wrapper that
   handles conversions that may be different than
   the usual ones because of excess precision.  */

സ്ഥിതം വൃക്ഷം
ep_convert_and_check (location_t loc, വൃക്ഷം type, വൃക്ഷം വ്യഞ്ജകം,
		      വൃക്ഷം semantic_type)
{
  എങ്കിൽ (വൃക്ഷം_TYPE (വ്യഞ്ജകം) == type)
    തിരികെ വ്യഞ്ജകം;

  /* For C11, integer conversions may have results with excess
     precision.  */
  എങ്കിൽ (flag_isoc11 || !semantic_type)
    തിരികെ convert_and_check (loc, type, വ്യഞ്ജകം);

  എങ്കിൽ (വൃക്ഷം_CODE (വൃക്ഷം_TYPE (വ്യഞ്ജകം)) == INTEGER_TYPE
      && വൃക്ഷം_TYPE (വ്യഞ്ജകം) != semantic_type)
    {
      /* For integers, we need to check the real conversion, not
	 the conversion to the excess precision type.  */
      വ്യഞ്ജകം = convert_and_check (loc, semantic_type, വ്യഞ്ജകം);
    }
  /* Result type is the excess precision type, which should be
     large enough, so do not check.  */
  തിരികെ convert (type, വ്യഞ്ജകം);
}

/* If EXPR refers to a built-in declared without a prototype returns
   the actual type of the built-in and, if non-null, set *BLTIN to
   a pointer to the built-in.  Otherwise return the type of EXPR
   and clear *BLTIN if non-null.  */

സ്ഥിതം വൃക്ഷം
type_or_builtin_type (വൃക്ഷം വ്യഞ്ജകം, വൃക്ഷം *bltin = ശൂന്യ)
{
  വൃക്ഷം dummy;
  എങ്കിൽ (!bltin)
    bltin = &dummy;

  *bltin = NULL_വൃക്ഷം;

  വൃക്ഷം type = വൃക്ഷം_TYPE (വ്യഞ്ജകം);
  എങ്കിൽ (വൃക്ഷം_CODE (വ്യഞ്ജകം) != ADDR_വ്യഞ്ജകം)
    തിരികെ type;

  വൃക്ഷം oper = വൃക്ഷം_OPERAND (വ്യഞ്ജകം, 0);
  എങ്കിൽ (!DECL_P (oper)
      || വൃക്ഷം_CODE (oper) != FUNCTION_DECL
      || !fndecl_built_in_p (oper, BUILT_IN_NORMAL))
    തിരികെ type;

  built_in_function code = DECL_FUNCTION_CODE (oper);
  എങ്കിൽ (!C_DECL_BUILTIN_PROTOTYPE (oper))
    തിരികെ type;

  എങ്കിൽ ((*bltin = builtin_decl_implicit (code)))
    type = c_build_pointer_type (വൃക്ഷം_TYPE (*bltin));

  തിരികെ type;
}

/* Build and return a conditional expression IFEXP ? OP1 : OP2.  If
   IFEXP_BCP then the condition is a call to __builtin_constant_p, and
   if folded to an integer constant then the unselected half may
   contain arbitrary operations not normally permitted in constant
   expressions.  Set the location of the expression to LOC.  */

വൃക്ഷം
build_conditional_വ്യഞ്ജകം (location_t colon_loc, വൃക്ഷം ifexp, തർക്കം ifexp_bcp,
			വൃക്ഷം op1, വൃക്ഷം op1_original_type, location_t op1_loc,
			വൃക്ഷം op2, വൃക്ഷം op2_original_type, location_t op2_loc)
{
  വൃക്ഷം type1;
  വൃക്ഷം type2;
  വൃക്ഷം result_type = ശൂന്യ;
  വൃക്ഷം semantic_result_type = ശൂന്യ;
  വൃക്ഷം orig_op1 = op1, orig_op2 = op2;
  തർക്കം int_const, op1_int_operands, op2_int_operands, int_operands;
  തർക്കം ifexp_int_operands;
  വൃക്ഷം ret;

  op1_int_operands = വ്യഞ്ജകം_INT_CONST_OPERANDS (orig_op1);
  എങ്കിൽ (op1_int_operands)
    op1 = remove_c_maybe_const_വ്യഞ്ജകം (op1);
  op2_int_operands = വ്യഞ്ജകം_INT_CONST_OPERANDS (orig_op2);
  എങ്കിൽ (op2_int_operands)
    op2 = remove_c_maybe_const_വ്യഞ്ജകം (op2);
  ifexp_int_operands = വ്യഞ്ജകം_INT_CONST_OPERANDS (ifexp);
  എങ്കിൽ (ifexp_int_operands)
    ifexp = remove_c_maybe_const_വ്യഞ്ജകം (ifexp);

  /* Promote both alternatives.  */

  എങ്കിൽ (വൃക്ഷം_CODE (വൃക്ഷം_TYPE (op1)) != VOID_TYPE)
    op1 = default_conversion (op1);
  എങ്കിൽ (വൃക്ഷം_CODE (വൃക്ഷം_TYPE (op2)) != VOID_TYPE)
    op2 = default_conversion (op2);

  എങ്കിൽ (വൃക്ഷം_CODE (ifexp) == ERROR_MARK
      || വൃക്ഷം_CODE (വൃക്ഷം_TYPE (op1)) == ERROR_MARK
      || വൃക്ഷം_CODE (വൃക്ഷം_TYPE (op2)) == ERROR_MARK)
    തിരികെ error_mark_കണ്ണി;

  വൃക്ഷം bltin1 = NULL_വൃക്ഷം;
  വൃക്ഷം bltin2 = NULL_വൃക്ഷം;
  type1 = type_or_builtin_type (op1, &bltin1);
  സ്ഥിരം എണ്ണൽ വൃക്ഷം_code code1 = വൃക്ഷം_CODE (type1);
  type2 = type_or_builtin_type (op2, &bltin2);
  സ്ഥിരം എണ്ണൽ വൃക്ഷം_code code2 = വൃക്ഷം_CODE (type2);

  എങ്കിൽ (code1 == POINTER_TYPE && reject_gcc_builtin (op1))
    തിരികെ error_mark_കണ്ണി;

  എങ്കിൽ (code2 == POINTER_TYPE && reject_gcc_builtin (op2))
    തിരികെ error_mark_കണ്ണി;

  /* C90 does not permit non-lvalue arrays in conditional expressions.
     In C99 they will be pointers by now.  */
  എങ്കിൽ (code1 == ARRAY_TYPE || code2 == ARRAY_TYPE)
    {
      error_at (colon_loc, "non-lvalue array in conditional expression");
      തിരികെ error_mark_കണ്ണി;
    }

  എങ്കിൽ ((വൃക്ഷം_CODE (op1) == EXCESS_PRECISION_വ്യഞ്ജകം
       || വൃക്ഷം_CODE (op2) == EXCESS_PRECISION_വ്യഞ്ജകം)
      && (code1 == INTEGER_TYPE || code1 == REAL_TYPE
	  || code1 == COMPLEX_TYPE || code1 == BITINT_TYPE)
      && (code2 == INTEGER_TYPE || code2 == REAL_TYPE
	  || code2 == COMPLEX_TYPE || code2 == BITINT_TYPE))
    {
      semantic_result_type = c_common_type (type1, type2);
      എങ്കിൽ (വൃക്ഷം_CODE (op1) == EXCESS_PRECISION_വ്യഞ്ജകം)
	{
	  op1 = വൃക്ഷം_OPERAND (op1, 0);
	  type1 = വൃക്ഷം_TYPE (op1);
	  gcc_assert (വൃക്ഷം_CODE (type1) == code1);
	}
      എങ്കിൽ (വൃക്ഷം_CODE (op2) == EXCESS_PRECISION_വ്യഞ്ജകം)
	{
	  op2 = വൃക്ഷം_OPERAND (op2, 0);
	  type2 = വൃക്ഷം_TYPE (op2);
	  gcc_assert (വൃക്ഷം_CODE (type2) == code2);
	}
    }

  എങ്കിൽ (warn_cxx_compat)
    {
      വൃക്ഷം t1 = op1_original_type ? op1_original_type : വൃക്ഷം_TYPE (orig_op1);
      വൃക്ഷം t2 = op2_original_type ? op2_original_type : വൃക്ഷം_TYPE (orig_op2);

      എങ്കിൽ (വൃക്ഷം_CODE (t1) == ENUMERAL_TYPE
	  && വൃക്ഷം_CODE (t2) == ENUMERAL_TYPE
	  && TYPE_MAIN_VARIANT (t1) != TYPE_MAIN_VARIANT (t2))
	warning_at (colon_loc, OPT_Wc___compat,
		    "different enum types in conditional is "
		    "invalid in C++: %qT vs %qT", t1, t2);
    }

  എങ്കിൽ (warn_zero_as_null_pointer_constant
      && c_inhibit_evaluation_warnings == 0)
    {
      എങ്കിൽ ((code1 == POINTER_TYPE || code1 == NULLPTR_TYPE)
	  && INTEGRAL_TYPE_P (type2) && null_pointer_constant_p (orig_op2))
	warning_at (op2_loc, OPT_Wzero_as_null_pointer_constant,
		    "zero as null pointer constant");

      എങ്കിൽ ((code2 == POINTER_TYPE || code2 == NULLPTR_TYPE)
	  && INTEGRAL_TYPE_P (type1) && null_pointer_constant_p (orig_op1))
	warning_at (op1_loc, OPT_Wzero_as_null_pointer_constant,
		    "zero as null pointer constant");
    }

  /* Quickly detect the usual case where op1 and op2 have the same type
     after promotion.  */
  എങ്കിൽ (TYPE_MAIN_VARIANT (type1) == TYPE_MAIN_VARIANT (type2))
    {
      എങ്കിൽ (type1 == type2)
	result_type = type1;
      അല്ലെങ്കിൽ
	result_type = TYPE_MAIN_VARIANT (type1);
    }
  അല്ലെങ്കിൽ എങ്കിൽ ((code1 == INTEGER_TYPE || code1 == REAL_TYPE
	    || code1 == COMPLEX_TYPE || code1 == BITINT_TYPE)
	   && (code2 == INTEGER_TYPE || code2 == REAL_TYPE
	       || code2 == COMPLEX_TYPE || code2 == BITINT_TYPE))
    {
      /* In C11, a conditional expression between a floating-point
	 type and an integer type should convert the integer type to
	 the evaluation format of the floating-point type, with
	 possible excess precision.  */
      വൃക്ഷം eptype1 = type1;
      വൃക്ഷം eptype2 = type2;
      എങ്കിൽ (flag_isoc11)
	{
	  വൃക്ഷം eptype;
	  എങ്കിൽ (ANY_INTEGRAL_TYPE_P (type1)
	      && (eptype = excess_precision_type (type2)) != NULL_വൃക്ഷം)
	    {
	      eptype2 = eptype;
	      എങ്കിൽ (!semantic_result_type)
		semantic_result_type = c_common_type (type1, type2);
	    }
	  അല്ലെങ്കിൽ എങ്കിൽ (ANY_INTEGRAL_TYPE_P (type2)
		   && (eptype = excess_precision_type (type1)) != NULL_വൃക്ഷം)
	    {
	      eptype1 = eptype;
	      എങ്കിൽ (!semantic_result_type)
		semantic_result_type = c_common_type (type1, type2);
	    }
	}
      result_type = c_common_type (eptype1, eptype2);
      എങ്കിൽ (result_type == error_mark_കണ്ണി)
	തിരികെ error_mark_കണ്ണി;
      do_warn_double_promotion (result_type, type1, type2,
				"implicit conversion from %qT to %qT to "
				"match other result of conditional",
				colon_loc);

      /* If -Wsign-compare, warn here if type1 and type2 have
	 different signedness.  We'll promote the signed to unsigned
	 and later code won't know it used to be different.
	 Do this check on the original types, so that explicit casts
	 will be considered, but default promotions won't.  */
      എങ്കിൽ (c_inhibit_evaluation_warnings == 0)
	{
	  പൂർണ്ണസംഖ്യ unsigned_op1 = TYPE_UNSIGNED (വൃക്ഷം_TYPE (orig_op1));
	  പൂർണ്ണസംഖ്യ unsigned_op2 = TYPE_UNSIGNED (വൃക്ഷം_TYPE (orig_op2));

	  എങ്കിൽ (unsigned_op1 ^ unsigned_op2)
	    {
	      /* Do not warn if the result type is signed, since the
		 signed type will only be chosen if it can represent
		 all the values of the unsigned type.  */
	      എങ്കിൽ (!TYPE_UNSIGNED (result_type))
		/* OK */;
	      അല്ലെങ്കിൽ
		{
		  തർക്കം op1_maybe_const = സത്യം;
		  തർക്കം op2_maybe_const = സത്യം;

		  /* Do not warn if the signed quantity is an
		     unsuffixed integer literal (or some static
		     constant expression involving such literals) and
		     it is non-negative.  This warning requires the
		     operands to be folded for best results, so do
		     that folding in this case even without
		     warn_sign_compare to avoid warning options
		     possibly affecting code generation.  */
		  c_inhibit_evaluation_warnings
		    += (ifexp == truthvalue_false_കണ്ണി);
		  op1 = c_fully_fold (op1, require_constant_മൂല്യം,
				      &op1_maybe_const);
		  c_inhibit_evaluation_warnings
		    -= (ifexp == truthvalue_false_കണ്ണി);

		  c_inhibit_evaluation_warnings
		    += (ifexp == truthvalue_true_കണ്ണി);
		  op2 = c_fully_fold (op2, require_constant_മൂല്യം,
				      &op2_maybe_const);
		  c_inhibit_evaluation_warnings
		    -= (ifexp == truthvalue_true_കണ്ണി);

		  എങ്കിൽ (warn_sign_compare)
		    {
		      എങ്കിൽ ((unsigned_op2
			   && വൃക്ഷം_വ്യഞ്ജകം_nonnegative_p (op1))
			  || (unsigned_op1
			      && വൃക്ഷം_വ്യഞ്ജകം_nonnegative_p (op2)))
			/* OK */;
		      അല്ലെങ്കിൽ എങ്കിൽ (unsigned_op2)
			warning_at (op1_loc, OPT_Wsign_compare,
				    "operand of %<?:%> changes signedness from "
				    "%qT to %qT due to unsignedness of other "
				    "operand", വൃക്ഷം_TYPE (orig_op1),
				    വൃക്ഷം_TYPE (orig_op2));
		      അല്ലെങ്കിൽ
			warning_at (op2_loc, OPT_Wsign_compare,
				    "operand of %<?:%> changes signedness from "
				    "%qT to %qT due to unsignedness of other "
				    "operand", വൃക്ഷം_TYPE (orig_op2),
				    വൃക്ഷം_TYPE (orig_op1));
		    }
		  എങ്കിൽ (!op1_maybe_const || വൃക്ഷം_CODE (op1) != INTEGER_CST)
		    op1 = c_wrap_maybe_const (op1, !op1_maybe_const);
		  എങ്കിൽ (!op2_maybe_const || വൃക്ഷം_CODE (op2) != INTEGER_CST)
		    op2 = c_wrap_maybe_const (op2, !op2_maybe_const);
		}
	    }
	}
    }
  അല്ലെങ്കിൽ എങ്കിൽ (code1 == VOID_TYPE || code2 == VOID_TYPE)
    {
      എങ്കിൽ (code1 != VOID_TYPE || code2 != VOID_TYPE)
	pedwarn (colon_loc, OPT_Wpedantic,
		 "ISO C forbids conditional expr with only one void side");
      result_type = void_type_കണ്ണി;
    }
  അല്ലെങ്കിൽ എങ്കിൽ (code1 == POINTER_TYPE && code2 == POINTER_TYPE)
    {
      addr_space_t as1 = TYPE_ADDR_SPACE (വൃക്ഷം_TYPE (type1));
      addr_space_t as2 = TYPE_ADDR_SPACE (വൃക്ഷം_TYPE (type2));
      addr_space_t as_common;

      എങ്കിൽ (comp_target_types (colon_loc, type1, type2))
	{
	  ifexp = save_വ്യഞ്ജകം (ifexp);
	  result_type = common_pointer_type (type1, type2, ifexp);
	}
      അല്ലെങ്കിൽ എങ്കിൽ (null_pointer_constant_p (orig_op1))
	result_type = type2;
      അല്ലെങ്കിൽ എങ്കിൽ (null_pointer_constant_p (orig_op2))
	result_type = type1;
      അല്ലെങ്കിൽ എങ്കിൽ (!addr_space_superset (as1, as2, &as_common))
	{
	  error_at (colon_loc, "pointers to disjoint address spaces "
		    "used in conditional expression");
	  തിരികെ error_mark_കണ്ണി;
	}
      അല്ലെങ്കിൽ എങ്കിൽ ((VOID_TYPE_P (വൃക്ഷം_TYPE (type1))
		&& !TYPE_ATOMIC (വൃക്ഷം_TYPE (type1)))
	       || (VOID_TYPE_P (വൃക്ഷം_TYPE (type2))
		   && !TYPE_ATOMIC (വൃക്ഷം_TYPE (type2))))
	{
	  വൃക്ഷം t1 = വൃക്ഷം_TYPE (type1);
	  വൃക്ഷം t2 = വൃക്ഷം_TYPE (type2);
	  എങ്കിൽ (!(VOID_TYPE_P (t1)
		&& !TYPE_ATOMIC (t1)))
	   {
	     /* roles are swapped */
	     t1 = t2;
	     t2 = വൃക്ഷം_TYPE (type1);
	   }
	  വൃക്ഷം t2_stripped = strip_array_types (t2);
	  എങ്കിൽ ((വൃക്ഷം_CODE (t2) == ARRAY_TYPE)
	      && (TYPE_QUALS (t2_stripped) & ~TYPE_QUALS (t1)))
	    {
	      എങ്കിൽ (!flag_isoc23)
		warning_at (colon_loc, OPT_Wdiscarded_array_qualifiers,
			    "pointer to array loses qualifier "
			    "in conditional expression");
	      അല്ലെങ്കിൽ എങ്കിൽ (warn_c11_c23_compat > 0)
		warning_at (colon_loc, OPT_Wc11_c23_compat,
			    "pointer to array loses qualifier "
			    "in conditional expression in ISO C before C23");
	    }
	  എങ്കിൽ (വൃക്ഷം_CODE (t2) == FUNCTION_TYPE)
	    pedwarn (colon_loc, OPT_Wpedantic,
		     "ISO C forbids conditional expr between "
		     "%<void *%> and function pointer");
	  /* for array, use qualifiers of element type */
	  എങ്കിൽ (flag_isoc23)
	    t2 = t2_stripped;
	  result_type = c_build_pointer_type (qualify_type (t1, t2));
	}
      /* Objective-C pointer comparisons are a bit more lenient.  */
      അല്ലെങ്കിൽ എങ്കിൽ (objc_have_common_type (type1, type2, -3, NULL_വൃക്ഷം))
	result_type = objc_common_type (type1, type2);
      അല്ലെങ്കിൽ
	{
	  പൂർണ്ണസംഖ്യ qual = ENCODE_QUAL_ADDR_SPACE (as_common);
	  എണ്ണൽ diagnostics::kind kind = diagnostics::kind::permerror;
	  എങ്കിൽ (!flag_isoc99)
	    /* This downgrade to a warning ensures that -std=gnu89
	       -pedantic-errors does not flag these mismatches between
	       builtins as errors (as diagnostics::kind::permerror would)
	       ISO C99 and later do not have implicit function declarations,
	       so the mismatch cannot occur naturally there.  */
	    kind = (bltin1 && bltin2
		    ? diagnostics::kind::warning
		    : diagnostics::kind::pedwarn);
	  എങ്കിൽ (emit_diagnostic (kind, colon_loc, OPT_Wincompatible_pointer_types,
			       "pointer type mismatch "
			       "in conditional expression"))
	    {
	      inform (op1_loc, "first expression has type %qT", type1);
	      inform (op2_loc, "second expression has type %qT", type2);
	    }
	  result_type = c_build_pointer_type
			  (c_build_qualified_type (void_type_കണ്ണി, qual));
	}
    }
  അല്ലെങ്കിൽ എങ്കിൽ (code1 == POINTER_TYPE
	   && (code2 == INTEGER_TYPE || code2 == BITINT_TYPE))
    {
      എങ്കിൽ (!null_pointer_constant_p (orig_op2))
	permerror_opt (colon_loc, OPT_Wint_conversion,
		       "pointer/integer type mismatch "
		       "in conditional expression");
      അല്ലെങ്കിൽ
	{
	  op2 = null_pointer_കണ്ണി;
	}
      result_type = type1;
    }
  അല്ലെങ്കിൽ എങ്കിൽ (code2 == POINTER_TYPE
	   && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
    {
      എങ്കിൽ (!null_pointer_constant_p (orig_op1))
	permerror_opt (colon_loc, OPT_Wint_conversion,
		       "pointer/integer type mismatch "
		       "in conditional expression");
      അല്ലെങ്കിൽ
	{
	  op1 = null_pointer_കണ്ണി;
	}
      result_type = type2;
    }
  /* 6.5.15: "if one is a null pointer constant (other than a pointer) or has
     type nullptr_t and the other is a pointer, the result type is the pointer
     type."  */
  അല്ലെങ്കിൽ എങ്കിൽ (code1 == NULLPTR_TYPE && code2 == POINTER_TYPE)
    result_type = type2;
  അല്ലെങ്കിൽ എങ്കിൽ (code1 == POINTER_TYPE && code2 == NULLPTR_TYPE)
    result_type = type1;
  അല്ലെങ്കിൽ എങ്കിൽ (RECORD_OR_UNION_TYPE_P (type1) && RECORD_OR_UNION_TYPE_P (type2)
	   && comptypes (TYPE_MAIN_VARIANT (type1),
			 TYPE_MAIN_VARIANT (type2)))
    result_type = composite_type (TYPE_MAIN_VARIANT (type1),
				  TYPE_MAIN_VARIANT (type2));

  എങ്കിൽ (!result_type)
    {
      എങ്കിൽ (flag_cond_mismatch)
	result_type = void_type_കണ്ണി;
      അല്ലെങ്കിൽ
	{
	  error_at (colon_loc, "type mismatch in conditional expression");
	  തിരികെ error_mark_കണ്ണി;
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

  എങ്കിൽ (ifexp_bcp && ifexp == truthvalue_true_കണ്ണി)
    {
      op2_int_operands = സത്യം;
      op1 = c_fully_fold (op1, require_constant_മൂല്യം, ശൂന്യ);
    }
  എങ്കിൽ (ifexp_bcp && ifexp == truthvalue_false_കണ്ണി)
    {
      op1_int_operands = സത്യം;
      op2 = c_fully_fold (op2, require_constant_മൂല്യം, ശൂന്യ);
    }
  int_const = int_operands = (ifexp_int_operands
			      && op1_int_operands
			      && op2_int_operands);
  എങ്കിൽ (int_operands)
    {
      int_const = ((ifexp == truthvalue_true_കണ്ണി
		    && വൃക്ഷം_CODE (orig_op1) == INTEGER_CST
		    && !വൃക്ഷം_OVERFLOW (orig_op1))
		   || (ifexp == truthvalue_false_കണ്ണി
		       && വൃക്ഷം_CODE (orig_op2) == INTEGER_CST
		       && !വൃക്ഷം_OVERFLOW (orig_op2)));
    }

  /* Need to convert condition operand into a vector mask.  */
  എങ്കിൽ (VECTOR_TYPE_P (വൃക്ഷം_TYPE (ifexp)))
    {
      വൃക്ഷം vectype = വൃക്ഷം_TYPE (ifexp);
      വൃക്ഷം elem_type = വൃക്ഷം_TYPE (vectype);
      വൃക്ഷം zero = build_int_cst (elem_type, 0);
      വൃക്ഷം zero_vec = build_vector_from_val (vectype, zero);
      വൃക്ഷം cmp_type = truth_type_for (vectype);
      ifexp = build2 (NE_വ്യഞ്ജകം, cmp_type, ifexp, zero_vec);
    }

  എങ്കിൽ (int_const || (ifexp_bcp && വൃക്ഷം_CODE (ifexp) == INTEGER_CST))
    ret = fold_build3_loc (colon_loc, COND_വ്യഞ്ജകം, result_type, ifexp, op1, op2);
  അല്ലെങ്കിൽ
    {
      എങ്കിൽ (int_operands)
	{
	  /* Use c_fully_fold here, since C_MAYBE_CONST_EXPR might be
	     nested inside of the expression.  */
	  op1 = c_fully_fold (op1, അസത്യം, ശൂന്യ);
	  op2 = c_fully_fold (op2, അസത്യം, ശൂന്യ);
	}
      ret = build3 (COND_വ്യഞ്ജകം, result_type, ifexp, op1, op2);
      എങ്കിൽ (int_operands)
	ret = note_integer_operands (ret);
    }
  എങ്കിൽ (semantic_result_type)
    ret = build1 (EXCESS_PRECISION_വ്യഞ്ജകം, semantic_result_type, ret);

  protected_set_വ്യഞ്ജകം_location (ret, colon_loc);

  /* If the OP1 and OP2 are the same and don't have side-effects,
     warn here, because the COND_EXPR will be turned into OP1.  */
  എങ്കിൽ (warn_duplicated_branches
      && വൃക്ഷം_CODE (ret) == COND_വ്യഞ്ജകം
      && (op1 == op2 || operand_equal_p (op1, op2, OEP_ADDRESS_OF_SAME_FIELD)))
    warning_at (വ്യഞ്ജകം_LOCATION (ret), OPT_Wduplicated_branches,
		"this condition has identical branches");

  തിരികെ ret;
}

/* EXPR is an expression, location LOC, whose result is discarded.
   Warn if it is a call to a nodiscard function (or a COMPOUND_EXPR
   whose right-hand operand is such a call, possibly recursively).  */

സ്ഥിതം ശൂന്യം
maybe_warn_nodiscard (location_t loc, വൃക്ഷം വ്യഞ്ജകം)
{
  എങ്കിൽ (VOID_TYPE_P (വൃക്ഷം_TYPE (വ്യഞ്ജകം)))
    തിരികെ;
  ആകുമ്പോൾ (വൃക്ഷം_CODE (വ്യഞ്ജകം) == COMPOUND_വ്യഞ്ജകം)
    {
      വ്യഞ്ജകം = വൃക്ഷം_OPERAND (വ്യഞ്ജകം, 1);
      എങ്കിൽ (വ്യഞ്ജകം_HAS_LOCATION (വ്യഞ്ജകം))
	loc = വ്യഞ്ജകം_LOCATION (വ്യഞ്ജകം);
    }
  എങ്കിൽ (വൃക്ഷം_CODE (വ്യഞ്ജകം) != CALL_വ്യഞ്ജകം)
    തിരികെ;
  വൃക്ഷം fn = CALL_വ്യഞ്ജകം_FN (വ്യഞ്ജകം);
  എങ്കിൽ (!fn)
    തിരികെ;
  വൃക്ഷം attr;
  എങ്കിൽ (വൃക്ഷം_CODE (fn) == ADDR_വ്യഞ്ജകം
      && വൃക്ഷം_CODE (വൃക്ഷം_OPERAND (fn, 0)) == FUNCTION_DECL
      && (attr = lookup_attribute ("nodiscard",
				   DECL_ATTRIBUTES (വൃക്ഷം_OPERAND (fn, 0)))))
    {
      fn = വൃക്ഷം_OPERAND (fn, 0);
      വൃക്ഷം args = വൃക്ഷം_മൂല്യം (attr);
      എങ്കിൽ (args)
	args = വൃക്ഷം_മൂല്യം (args);
      auto_diagnostic_group d;
      auto_urlify_attributes sentinel;
      പൂർണ്ണസംഖ്യ warned;
      എങ്കിൽ (args)
	warned = warning_at (loc, OPT_Wunused_result,
			     "ignoring return value of %qD, declared with "
			     "attribute %<nodiscard%>: %E", fn, args);
      അല്ലെങ്കിൽ
	warned = warning_at (loc, OPT_Wunused_result,
			     "ignoring return value of %qD, declared with "
			     "attribute %<nodiscard%>", fn);
      എങ്കിൽ (warned)
	inform (DECL_SOURCE_LOCATION (fn), "declared here");
    }
  അല്ലെങ്കിൽ
    {
      വൃക്ഷം rettype = വൃക്ഷം_TYPE (വൃക്ഷം_TYPE (വൃക്ഷം_TYPE (fn)));
      attr = lookup_attribute ("nodiscard", TYPE_ATTRIBUTES (rettype));
      എങ്കിൽ (!attr)
	തിരികെ;
      വൃക്ഷം args = വൃക്ഷം_മൂല്യം (attr);
      എങ്കിൽ (args)
	args = വൃക്ഷം_മൂല്യം (args);
      auto_diagnostic_group d;
      auto_urlify_attributes sentinel;
      പൂർണ്ണസംഖ്യ warned;
      എങ്കിൽ (args)
	warned = warning_at (loc, OPT_Wunused_result,
			     "ignoring return value of type %qT, declared "
			     "with attribute %<nodiscard%>: %E",
			     rettype, args);
      അല്ലെങ്കിൽ
	warned = warning_at (loc, OPT_Wunused_result,
			     "ignoring return value of type %qT, declared "
			     "with attribute %<nodiscard%>", rettype);
      എങ്കിൽ (warned)
	{
	  എങ്കിൽ (വൃക്ഷം_CODE (fn) == ADDR_വ്യഞ്ജകം)
	    {
	      fn = വൃക്ഷം_OPERAND (fn, 0);
	      എങ്കിൽ (വൃക്ഷം_CODE (fn) == FUNCTION_DECL)
		inform (DECL_SOURCE_LOCATION (fn),
			"in call to %qD, declared here", fn);
	    }
	}
    }
}

/* Return a compound expression that performs two expressions and
   returns the value of the second of them.

   LOC is the location of the COMPOUND_EXPR.  */

വൃക്ഷം
build_compound_വ്യഞ്ജകം (location_t loc, വൃക്ഷം expr1, വൃക്ഷം expr2)
{
  തർക്കം expr1_int_operands, expr2_int_operands;
  വൃക്ഷം eptype = NULL_വൃക്ഷം;
  വൃക്ഷം ret;

  expr1_int_operands = വ്യഞ്ജകം_INT_CONST_OPERANDS (expr1);
  എങ്കിൽ (expr1_int_operands)
    expr1 = remove_c_maybe_const_വ്യഞ്ജകം (expr1);
  expr2_int_operands = വ്യഞ്ജകം_INT_CONST_OPERANDS (expr2);
  എങ്കിൽ (expr2_int_operands)
    expr2 = remove_c_maybe_const_വ്യഞ്ജകം (expr2);

  എങ്കിൽ (വൃക്ഷം_CODE (expr1) == EXCESS_PRECISION_വ്യഞ്ജകം)
    expr1 = വൃക്ഷം_OPERAND (expr1, 0);
  എങ്കിൽ (വൃക്ഷം_CODE (expr2) == EXCESS_PRECISION_വ്യഞ്ജകം)
    {
      eptype = വൃക്ഷം_TYPE (expr2);
      expr2 = വൃക്ഷം_OPERAND (expr2, 0);
    }

  എങ്കിൽ (!വൃക്ഷം_SIDE_EFFECTS (expr1))
    {
      /* The left-hand operand of a comma expression is like an expression
	 statement: with -Wunused, we should warn if it doesn't have
	 any side-effects, unless it was explicitly cast to (void).  */
      എങ്കിൽ (warn_unused_മൂല്യം)
	{
	  എങ്കിൽ (VOID_TYPE_P (വൃക്ഷം_TYPE (expr1))
	      && CONVERT_വ്യഞ്ജകം_P (expr1))
	    ; /* (void) a, b */
	  അല്ലെങ്കിൽ എങ്കിൽ (VOID_TYPE_P (വൃക്ഷം_TYPE (expr1))
		   && വൃക്ഷം_CODE (expr1) == COMPOUND_വ്യഞ്ജകം
		   && CONVERT_വ്യഞ്ജകം_P (വൃക്ഷം_OPERAND (expr1, 1)))
	    ; /* (void) a, (void) b, c */
	  അല്ലെങ്കിൽ
	    warning_at (loc, OPT_Wunused_മൂല്യം,
			"left-hand operand of comma expression has no effect");
	}
    }
  അല്ലെങ്കിൽ എങ്കിൽ (വൃക്ഷം_CODE (expr1) == COMPOUND_വ്യഞ്ജകം
	   && warn_unused_മൂല്യം)
    {
      വൃക്ഷം r = expr1;
      location_t cloc = loc;
      ആകുമ്പോൾ (വൃക്ഷം_CODE (r) == COMPOUND_വ്യഞ്ജകം)
        {
	  എങ്കിൽ (വ്യഞ്ജകം_HAS_LOCATION (r))
	    cloc = വ്യഞ്ജകം_LOCATION (r);
	  r = വൃക്ഷം_OPERAND (r, 1);
	}
      എങ്കിൽ (!വൃക്ഷം_SIDE_EFFECTS (r)
	  && !VOID_TYPE_P (വൃക്ഷം_TYPE (r))
	  && !CONVERT_വ്യഞ്ജകം_P (r))
	warning_at (cloc, OPT_Wunused_മൂല്യം,
	            "right-hand operand of comma expression has no effect");
    }

  /* With -Wunused, we should also warn if the left-hand operand does have
     side-effects, but computes a value which is not used.  For example, in
     `foo() + bar(), baz()' the result of the `+' operator is not used,
     so we should issue a warning.  */
  അല്ലെങ്കിൽ എങ്കിൽ (warn_unused_മൂല്യം)
    warn_if_unused_മൂല്യം (expr1, loc);

  maybe_warn_nodiscard (loc, expr1);

  എങ്കിൽ (expr2 == error_mark_കണ്ണി)
    തിരികെ error_mark_കണ്ണി;

  ret = build2 (COMPOUND_വ്യഞ്ജകം, വൃക്ഷം_TYPE (expr2), expr1, expr2);

  എങ്കിൽ (flag_isoc99
      && expr1_int_operands
      && expr2_int_operands)
    ret = note_integer_operands (ret);

  എങ്കിൽ (eptype)
    ret = build1 (EXCESS_PRECISION_വ്യഞ്ജകം, eptype, ret);

  protected_set_വ്യഞ്ജകം_location (ret, loc);
  തിരികെ ret;
}

/* Issue -Wcast-qual warnings when appropriate.  TYPE is the type to
   which we are casting.  OTYPE is the type of the expression being
   cast.  Both TYPE and OTYPE are pointer types.  LOC is the location
   of the cast.  -Wcast-qual appeared on the command line.  Named
   address space qualifiers are not handled here, because they result
   in different warnings.  */

സ്ഥിതം ശൂന്യം
handle_warn_cast_qual (location_t loc, വൃക്ഷം type, വൃക്ഷം otype)
{
  വൃക്ഷം in_type = type;
  വൃക്ഷം in_otype = otype;
  പൂർണ്ണസംഖ്യ added = 0;
  പൂർണ്ണസംഖ്യ discarded = 0;
  തർക്കം is_const;

  /* Check that the qualifiers on IN_TYPE are a superset of the
     qualifiers of IN_OTYPE.  The outermost level of POINTER_TYPE
     nodes is uninteresting and we stop as soon as we hit a
     non-POINTER_TYPE node on either type.  */
  ചെയ്യുക
    {
      in_otype = വൃക്ഷം_TYPE (in_otype);
      in_type = വൃക്ഷം_TYPE (in_type);

      /* GNU C allows cv-qualified function types.  'const' means the
	 function is very pure, 'volatile' means it can't return.  We
	 need to warn when such qualifiers are added, not when they're
	 taken away.  */
      എങ്കിൽ (വൃക്ഷം_CODE (in_otype) == FUNCTION_TYPE
	  && വൃക്ഷം_CODE (in_type) == FUNCTION_TYPE)
	added |= (TYPE_QUALS_NO_ADDR_SPACE (in_type)
		  & ~TYPE_QUALS_NO_ADDR_SPACE (in_otype));
      അല്ലെങ്കിൽ
	discarded |= (TYPE_QUALS_NO_ADDR_SPACE (in_otype)
		      & ~TYPE_QUALS_NO_ADDR_SPACE (in_type));
    }
  ആകുമ്പോൾ (വൃക്ഷം_CODE (in_type) == POINTER_TYPE
	 && വൃക്ഷം_CODE (in_otype) == POINTER_TYPE);

  എങ്കിൽ (added)
    warning_at (loc, OPT_Wcast_qual,
		"cast adds %q#v qualifier to function type", added);

  എങ്കിൽ (discarded)
    /* There are qualifiers present in IN_OTYPE that are not present
       in IN_TYPE.  */
    warning_at (loc, OPT_Wcast_qual,
		"cast discards %qv qualifier from pointer target type",
		discarded);

  എങ്കിൽ (added || discarded)
    തിരികെ;

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

  എങ്കിൽ (TYPE_MAIN_VARIANT (in_type) != TYPE_MAIN_VARIANT (in_otype))
    തിരികെ;
  എങ്കിൽ (വൃക്ഷം_CODE (വൃക്ഷം_TYPE (type)) != POINTER_TYPE)
    തിരികെ;

  in_type = type;
  in_otype = otype;
  is_const = TYPE_READONLY (വൃക്ഷം_TYPE (in_type));
  ചെയ്യുക
    {
      in_type = വൃക്ഷം_TYPE (in_type);
      in_otype = വൃക്ഷം_TYPE (in_otype);
      എങ്കിൽ ((TYPE_QUALS (in_type) &~ TYPE_QUALS (in_otype)) != 0
	  && !is_const)
	{
	  warning_at (loc, OPT_Wcast_qual,
		      "to be safe all intermediate pointers in cast from "
                      "%qT to %qT must be %<const%> qualified",
		      otype, type);
	  നിർത്തുക;
	}
      എങ്കിൽ (is_const)
	is_const = TYPE_READONLY (in_type);
    }
  ആകുമ്പോൾ (വൃക്ഷം_CODE (in_type) == POINTER_TYPE);
}

/* Heuristic check if two parameter types can be considered ABI-equivalent.  */

സ്ഥിതം തർക്കം
c_safe_arg_type_equiv_p (വൃക്ഷം t1, വൃക്ഷം t2)
{
  എങ്കിൽ (error_operand_p (t1) || error_operand_p (t2))
    തിരികെ സത്യം;

  t1 = TYPE_MAIN_VARIANT (t1);
  t2 = TYPE_MAIN_VARIANT (t2);

  എങ്കിൽ (വൃക്ഷം_CODE (t1) == POINTER_TYPE
      && വൃക്ഷം_CODE (t2) == POINTER_TYPE)
    തിരികെ സത്യം;

  /* Only the precision of the parameter matters.  This check should
     make sure that the callee does not see undefined values in argument
     registers.  */
  എങ്കിൽ (INTEGRAL_TYPE_P (t1)
      && INTEGRAL_TYPE_P (t2)
      && TYPE_PRECISION (t1) == TYPE_PRECISION (t2))
    തിരികെ സത്യം;

  തിരികെ comptypes (t1, t2);
}

/* Check if a type cast between two function types can be considered safe.  */

സ്ഥിതം തർക്കം
c_safe_function_type_cast_p (വൃക്ഷം t1, വൃക്ഷം t2)
{
  എങ്കിൽ (വൃക്ഷം_TYPE (t1) == void_type_കണ്ണി &&
      TYPE_ARG_TYPES (t1) == void_list_കണ്ണി)
    തിരികെ സത്യം;

  എങ്കിൽ (വൃക്ഷം_TYPE (t2) == void_type_കണ്ണി &&
      TYPE_ARG_TYPES (t2) == void_list_കണ്ണി)
    തിരികെ സത്യം;

  എങ്കിൽ (!c_safe_arg_type_equiv_p (വൃക്ഷം_TYPE (t1), വൃക്ഷം_TYPE (t2)))
    തിരികെ അസത്യം;

  വേണ്ടി (t1 = TYPE_ARG_TYPES (t1), t2 = TYPE_ARG_TYPES (t2);
       t1 && t2;
       t1 = വൃക്ഷം_CHAIN (t1), t2 = വൃക്ഷം_CHAIN (t2))
    എങ്കിൽ (!c_safe_arg_type_equiv_p (വൃക്ഷം_മൂല്യം (t1), വൃക്ഷം_മൂല്യം (t2)))
      തിരികെ അസത്യം;

  തിരികെ സത്യം;
}

/* Build an expression representing a cast to type TYPE of expression EXPR.
   LOC is the location of the cast-- typically the open paren of the cast.  */

വൃക്ഷം
build_c_cast (location_t loc, വൃക്ഷം type, വൃക്ഷം വ്യഞ്ജകം)
{
  വൃക്ഷം മൂല്യം;

  തർക്കം int_operands = വ്യഞ്ജകം_INT_CONST_OPERANDS (വ്യഞ്ജകം);

  എങ്കിൽ (വൃക്ഷം_CODE (വ്യഞ്ജകം) == EXCESS_PRECISION_വ്യഞ്ജകം)
    വ്യഞ്ജകം = വൃക്ഷം_OPERAND (വ്യഞ്ജകം, 0);

  മൂല്യം = വ്യഞ്ജകം;
  എങ്കിൽ (int_operands)
    മൂല്യം = remove_c_maybe_const_വ്യഞ്ജകം (മൂല്യം);

  എങ്കിൽ (type == error_mark_കണ്ണി || വ്യഞ്ജകം == error_mark_കണ്ണി)
    തിരികെ error_mark_കണ്ണി;

  /* The ObjC front-end uses TYPE_MAIN_VARIANT to tie together types differing
     only in <protocol> qualifications.  But when constructing cast expressions,
     the protocols do matter and must be kept around.  */
  എങ്കിൽ (objc_is_object_ptr (type) && objc_is_object_ptr (വൃക്ഷം_TYPE (വ്യഞ്ജകം)))
    തിരികെ build1 (NOP_വ്യഞ്ജകം, type, വ്യഞ്ജകം);

  type = TYPE_MAIN_VARIANT (type);

  എങ്കിൽ (വൃക്ഷം_CODE (type) == ARRAY_TYPE)
    {
      error_at (loc, "cast specifies array type");
      തിരികെ error_mark_കണ്ണി;
    }

  എങ്കിൽ (വൃക്ഷം_CODE (type) == FUNCTION_TYPE)
    {
      error_at (loc, "cast specifies function type");
      തിരികെ error_mark_കണ്ണി;
    }

  എങ്കിൽ (!VOID_TYPE_P (type))
    {
      മൂല്യം = require_complete_type (loc, മൂല്യം);
      എങ്കിൽ (മൂല്യം == error_mark_കണ്ണി)
	തിരികെ error_mark_കണ്ണി;
    }

  എങ്കിൽ (type == TYPE_MAIN_VARIANT (വൃക്ഷം_TYPE (മൂല്യം)))
    {
      എങ്കിൽ (RECORD_OR_UNION_TYPE_P (type)
	  && pedwarn (loc, OPT_Wpedantic,
		      "ISO C forbids casting nonscalar to the same type"))
	      ;
      അല്ലെങ്കിൽ എങ്കിൽ (warn_useless_cast && c_inhibit_evaluation_warnings == 0)
	warning_at (loc, OPT_Wuseless_cast,
		    "useless cast to type %qT", type);

      /* Convert to remove any qualifiers from VALUE's type.  */
      മൂല്യം = convert (type, മൂല്യം);
    }
  അല്ലെങ്കിൽ എങ്കിൽ (വൃക്ഷം_CODE (type) == UNION_TYPE)
    {
      വൃക്ഷം field;

      വേണ്ടി (field = TYPE_FIELDS (type); field; field = DECL_CHAIN (field))
	എങ്കിൽ (വൃക്ഷം_TYPE (field) != error_mark_കണ്ണി
	    && comptypes (TYPE_MAIN_VARIANT (വൃക്ഷം_TYPE (field)),
			  TYPE_MAIN_VARIANT (വൃക്ഷം_TYPE (മൂല്യം))))
	  നിർത്തുക;

      എങ്കിൽ (field)
	{
	  വൃക്ഷം t;
	  തർക്കം maybe_const = സത്യം;

	  pedwarn (loc, OPT_Wpedantic, "ISO C forbids casts to union type");
	  t = c_fully_fold (മൂല്യം, അസത്യം, &maybe_const);
	  t = build_constructor_single (type, field, t);
	  എങ്കിൽ (!maybe_const)
	    t = c_wrap_maybe_const (t, സത്യം);
	  t = digest_init (loc, field, type, t,
			   NULL_വൃക്ഷം, അസത്യം, അസത്യം, അസത്യം, സത്യം, അസത്യം, അസത്യം);
	  വൃക്ഷം_CONSTANT (t) = വൃക്ഷം_CONSTANT (മൂല്യം);
	  തിരികെ t;
	}
      error_at (loc, "cast to union type from type not present in union");
      തിരികെ error_mark_കണ്ണി;
    }
  അല്ലെങ്കിൽ
    {
      വൃക്ഷം otype, ovalue;

      എങ്കിൽ (type == void_type_കണ്ണി)
	{
	  വൃക്ഷം t = build1 (CONVERT_വ്യഞ്ജകം, type, മൂല്യം);
	  SET_വ്യഞ്ജകം_LOCATION (t, loc);
	  തിരികെ t;
	}

      otype = വൃക്ഷം_TYPE (മൂല്യം);

      /* Optionally warn about potentially worrisome casts.  */
      എങ്കിൽ (warn_cast_qual
	  && വൃക്ഷം_CODE (type) == POINTER_TYPE
	  && വൃക്ഷം_CODE (otype) == POINTER_TYPE)
	handle_warn_cast_qual (loc, type, otype);

      /* Warn about conversions between pointers to disjoint
	 address spaces.  */
      എങ്കിൽ (വൃക്ഷം_CODE (type) == POINTER_TYPE
	  && വൃക്ഷം_CODE (otype) == POINTER_TYPE
	  && !null_pointer_constant_p (മൂല്യം))
	{
	  addr_space_t as_to = TYPE_ADDR_SPACE (വൃക്ഷം_TYPE (type));
	  addr_space_t as_from = TYPE_ADDR_SPACE (വൃക്ഷം_TYPE (otype));
	  addr_space_t as_common;

	  എങ്കിൽ (!addr_space_superset (as_to, as_from, &as_common))
	    {
	      എങ്കിൽ (ADDR_SPACE_GENERIC_P (as_from))
		warning_at (loc, 0, "cast to %qs address space pointer "
			    "from disjoint generic address space pointer",
			    c_addr_space_name (as_to));

	      അല്ലെങ്കിൽ എങ്കിൽ (ADDR_SPACE_GENERIC_P (as_to))
		warning_at (loc, 0, "cast to generic address space pointer "
			    "from disjoint %qs address space pointer",
			    c_addr_space_name (as_from));

	      അല്ലെങ്കിൽ
		warning_at (loc, 0, "cast to %qs address space pointer "
			    "from disjoint %qs address space pointer",
			    c_addr_space_name (as_to),
			    c_addr_space_name (as_from));
	    }

	  /* Warn of new allocations that are not big enough for the target
	     type.  */
	  എങ്കിൽ (warn_alloc_size && വൃക്ഷം_CODE (മൂല്യം) == CALL_വ്യഞ്ജകം)
	    എങ്കിൽ (വൃക്ഷം fndecl = get_callee_fndecl (മൂല്യം))
	      എങ്കിൽ (DECL_IS_MALLOC (fndecl))
		{
		  വൃക്ഷം attrs = TYPE_ATTRIBUTES (വൃക്ഷം_TYPE (fndecl));
		  വൃക്ഷം alloc_size = lookup_attribute ("alloc_size", attrs);
		  എങ്കിൽ (alloc_size)
		    warn_for_alloc_size (loc, വൃക്ഷം_TYPE (type), മൂല്യം,
					 alloc_size);
		}
	}

      /* Warn about possible alignment problems.  */
      എങ്കിൽ ((STRICT_ALIGNMENT || warn_cast_align == 2)
	  && വൃക്ഷം_CODE (type) == POINTER_TYPE
	  && വൃക്ഷം_CODE (otype) == POINTER_TYPE
	  && വൃക്ഷം_CODE (വൃക്ഷം_TYPE (otype)) != VOID_TYPE
	  && വൃക്ഷം_CODE (വൃക്ഷം_TYPE (otype)) != FUNCTION_TYPE
	  /* Don't warn about opaque types, where the actual alignment
	     restriction is unknown.  */
	  && !(RECORD_OR_UNION_TYPE_P (വൃക്ഷം_TYPE (otype))
	       && TYPE_MODE (വൃക്ഷം_TYPE (otype)) == VOIDmode)
	  && min_align_of_type (വൃക്ഷം_TYPE (type))
	     > min_align_of_type (വൃക്ഷം_TYPE (otype)))
	warning_at (loc, OPT_Wcast_align,
		    "cast increases required alignment of target type");

      എങ്കിൽ ((വൃക്ഷം_CODE (type) == INTEGER_TYPE
	   || വൃക്ഷം_CODE (type) == BITINT_TYPE)
	  && വൃക്ഷം_CODE (otype) == POINTER_TYPE
	  && TYPE_PRECISION (type) != TYPE_PRECISION (otype))
      /* Unlike conversion of integers to pointers, where the
         warning is disabled for converting constants because
         of cases such as SIG_*, warn about converting constant
         pointers to integers. In some cases it may cause unwanted
         sign extension, and a warning is appropriate.  */
	warning_at (loc, OPT_Wpointer_to_int_cast,
		    "cast from pointer to integer of different size");

      എങ്കിൽ ((വൃക്ഷം_CODE (മൂല്യം) == CALL_വ്യഞ്ജകം
	   && !is_access_with_size_p (മൂല്യം))
	  && വൃക്ഷം_CODE (type) != വൃക്ഷം_CODE (otype))
	warning_at (loc, OPT_Wbad_function_cast,
		    "cast from function call of type %qT "
		    "to non-matching type %qT", otype, type);

      എങ്കിൽ (വൃക്ഷം_CODE (type) == POINTER_TYPE
	  && (വൃക്ഷം_CODE (otype) == INTEGER_TYPE
	      || വൃക്ഷം_CODE (otype) == BITINT_TYPE)
	  && TYPE_PRECISION (type) != TYPE_PRECISION (otype)
	  /* Don't warn about converting any constant.  */
	  && !വൃക്ഷം_CONSTANT (മൂല്യം))
	warning_at (loc,
		    OPT_Wint_to_pointer_cast, "cast to pointer from integer "
		    "of different size");

      എങ്കിൽ (warn_strict_aliasing <= 2)
        strict_aliasing_warning (വ്യഞ്ജകം_LOCATION (മൂല്യം), type, വ്യഞ്ജകം);

      /* If pedantic, warn for conversions between function and object
	 pointer types, except for converting a null pointer constant
	 to function pointer type.  */
      എങ്കിൽ (pedantic
	  && വൃക്ഷം_CODE (type) == POINTER_TYPE
	  && വൃക്ഷം_CODE (otype) == POINTER_TYPE
	  && വൃക്ഷം_CODE (വൃക്ഷം_TYPE (otype)) == FUNCTION_TYPE
	  && വൃക്ഷം_CODE (വൃക്ഷം_TYPE (type)) != FUNCTION_TYPE)
	pedwarn (loc, OPT_Wpedantic, "ISO C forbids "
		 "conversion of function pointer to object pointer type");

      എങ്കിൽ (pedantic
	  && വൃക്ഷം_CODE (type) == POINTER_TYPE
	  && വൃക്ഷം_CODE (otype) == POINTER_TYPE
	  && വൃക്ഷം_CODE (വൃക്ഷം_TYPE (type)) == FUNCTION_TYPE
	  && വൃക്ഷം_CODE (വൃക്ഷം_TYPE (otype)) != FUNCTION_TYPE
	  && !null_pointer_constant_p (മൂല്യം))
	pedwarn (loc, OPT_Wpedantic, "ISO C forbids "
		 "conversion of object pointer to function pointer type");

      എങ്കിൽ (വൃക്ഷം_CODE (type) == POINTER_TYPE
	  && വൃക്ഷം_CODE (otype) == POINTER_TYPE
	  && വൃക്ഷം_CODE (വൃക്ഷം_TYPE (type)) == FUNCTION_TYPE
	  && വൃക്ഷം_CODE (വൃക്ഷം_TYPE (otype)) == FUNCTION_TYPE
	  && !c_safe_function_type_cast_p (വൃക്ഷം_TYPE (type),
					   വൃക്ഷം_TYPE (otype)))
	warning_at (loc, OPT_Wcast_function_type,
		    "cast between incompatible function types"
		    " from %qT to %qT", otype, type);

      ovalue = മൂല്യം;
      /* If converting to boolean a value with integer operands that
	 is not itself represented as an INTEGER_CST, the call below
	 to note_integer_operands may insert a C_MAYBE_CONST_EXPR, but
	 build_binary_op as called by c_common_truthvalue_conversion
	 may also insert a C_MAYBE_CONST_EXPR to indicate that a
	 subexpression has been fully folded.  To avoid nested
	 C_MAYBE_CONST_EXPR, ensure that
	 c_objc_common_truthvalue_conversion receives an argument
	 properly marked as having integer operands in that case.  */
      എങ്കിൽ (int_operands
	  && വൃക്ഷം_CODE (മൂല്യം) != INTEGER_CST
	  && (വൃക്ഷം_CODE (type) == BOOLEAN_TYPE
	      || (വൃക്ഷം_CODE (type) == ENUMERAL_TYPE
		  && ENUM_UNDERLYING_TYPE (type) != NULL_വൃക്ഷം
		  && വൃക്ഷം_CODE (ENUM_UNDERLYING_TYPE (type)) == BOOLEAN_TYPE)))
	മൂല്യം = note_integer_operands (മൂല്യം);
      മൂല്യം = convert (type, മൂല്യം);

      /* Ignore any integer overflow caused by the cast.  */
      എങ്കിൽ (വൃക്ഷം_CODE (മൂല്യം) == INTEGER_CST && !FLOAT_TYPE_P (otype))
	{
	  എങ്കിൽ (വൃക്ഷം_OVERFLOW_P (ovalue))
	    {
	      എങ്കിൽ (!വൃക്ഷം_OVERFLOW (മൂല്യം))
		{
		  /* Avoid clobbering a shared constant.  */
		  മൂല്യം = copy_കണ്ണി (മൂല്യം);
		  വൃക്ഷം_OVERFLOW (മൂല്യം) = വൃക്ഷം_OVERFLOW (ovalue);
		}
	    }
	  അല്ലെങ്കിൽ എങ്കിൽ (വൃക്ഷം_OVERFLOW (മൂല്യം))
	    /* Reset VALUE's overflow flags, ensuring constant sharing.  */
	    മൂല്യം = wide_int_to_വൃക്ഷം (വൃക്ഷം_TYPE (മൂല്യം), wi::to_wide (മൂല്യം));
	}
    }

  /* Don't let a cast be an lvalue.  */
  എങ്കിൽ (lvalue_p (മൂല്യം)
      /* Also, don't let a cast be a bit-field of a bit-precise integer type,
	 otherwise it could be incorrectly subject of integer promotions.  */
      || (വൃക്ഷം_CODE (മൂല്യം) == COMPONENT_REF
	  && DECL_C_BIT_FIELD (വൃക്ഷം_OPERAND (മൂല്യം, 1))
	  && BITINT_TYPE_P (DECL_BIT_FIELD_TYPE (വൃക്ഷം_OPERAND (മൂല്യം, 1)))))
    മൂല്യം = non_lvalue_loc (loc, മൂല്യം);

  /* Don't allow the results of casting to floating-point or complex
     types be confused with actual constants, or casts involving
     integer and pointer types other than direct integer-to-integer
     and integer-to-pointer be confused with integer constant
     expressions and null pointer constants.  */
  എങ്കിൽ (വൃക്ഷം_CODE (മൂല്യം) == REAL_CST
      || വൃക്ഷം_CODE (മൂല്യം) == COMPLEX_CST
      || (വൃക്ഷം_CODE (മൂല്യം) == INTEGER_CST
	  && !((വൃക്ഷം_CODE (വ്യഞ്ജകം) == INTEGER_CST
		&& INTEGRAL_TYPE_P (വൃക്ഷം_TYPE (വ്യഞ്ജകം)))
	       || വൃക്ഷം_CODE (വ്യഞ്ജകം) == REAL_CST
	       || വൃക്ഷം_CODE (വ്യഞ്ജകം) == COMPLEX_CST)))
      മൂല്യം = build1 (NOP_വ്യഞ്ജകം, type, മൂല്യം);

  /* If the expression has integer operands and so can occur in an
     unevaluated part of an integer constant expression, ensure the
     return value reflects this.  */
  എങ്കിൽ (int_operands
      && INTEGRAL_TYPE_P (type)
      && മൂല്യം != error_mark_കണ്ണി
      && !വ്യഞ്ജകം_INT_CONST_OPERANDS (മൂല്യം))
    മൂല്യം = note_integer_operands (മൂല്യം);

  protected_set_വ്യഞ്ജകം_location (മൂല്യം, loc);
  തിരികെ മൂല്യം;
}

/* Interpret a cast of expression EXPR to type TYPE.  LOC is the
   location of the open paren of the cast, or the position of the cast
   expr.  */
വൃക്ഷം
c_cast_വ്യഞ്ജകം (location_t loc, ഘടന c_type_name *type_name, വൃക്ഷം വ്യഞ്ജകം)
{
  വൃക്ഷം type;
  വൃക്ഷം type_വ്യഞ്ജകം = NULL_വൃക്ഷം;
  തർക്കം type_വ്യഞ്ജകം_const = സത്യം;
  വൃക്ഷം ret;
  പൂർണ്ണസംഖ്യ saved_wsp = warn_strict_prototypes;

  /* This avoids warnings about unprototyped casts on
     integers.  E.g. "#define SIG_DFL (void(*)())0".  */
  എങ്കിൽ (വൃക്ഷം_CODE (വ്യഞ്ജകം) == INTEGER_CST)
    warn_strict_prototypes = 0;
  type = groktypename (type_name, &type_വ്യഞ്ജകം, &type_വ്യഞ്ജകം_const);
  warn_strict_prototypes = saved_wsp;

  എങ്കിൽ (വൃക്ഷം_CODE (വ്യഞ്ജകം) == ADDR_വ്യഞ്ജകം && !VOID_TYPE_P (type)
      && reject_gcc_builtin (വ്യഞ്ജകം))
    തിരികെ error_mark_കണ്ണി;

  ret = build_c_cast (loc, type, വ്യഞ്ജകം);
  എങ്കിൽ (ret == error_mark_കണ്ണി)
    തിരികെ error_mark_കണ്ണി;

  എങ്കിൽ (type_വ്യഞ്ജകം)
    {
      തർക്കം inner_വ്യഞ്ജകം_const = സത്യം;
      ret = c_fully_fold (ret, require_constant_മൂല്യം, &inner_വ്യഞ്ജകം_const);
      ret = build2 (C_MAYBE_CONST_വ്യഞ്ജകം, വൃക്ഷം_TYPE (ret), type_വ്യഞ്ജകം, ret);
      C_MAYBE_CONST_വ്യഞ്ജകം_NON_CONST (ret) = !(type_വ്യഞ്ജകം_const
					     && inner_വ്യഞ്ജകം_const);
      SET_വ്യഞ്ജകം_LOCATION (ret, loc);
    }

  എങ്കിൽ (!വ്യഞ്ജകം_HAS_LOCATION (ret))
    protected_set_വ്യഞ്ജകം_location (ret, loc);

  /* C++ does not permits types to be defined in a cast, but it
     allows references to incomplete types.  */
  എങ്കിൽ (warn_cxx_compat && type_name->specs->typespec_kind == ctsk_tagdef)
    warning_at (loc, OPT_Wc___compat,
		"defining a type in a cast is invalid in C++");

  തിരികെ ret;
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

വൃക്ഷം
build_modify_വ്യഞ്ജകം (location_t location, വൃക്ഷം lhs, വൃക്ഷം lhs_origtype,
		   എണ്ണൽ വൃക്ഷം_code modifycode,
		   location_t rhs_loc, വൃക്ഷം rhs, വൃക്ഷം rhs_origtype)
{
  വൃക്ഷം result;
  വൃക്ഷം newrhs;
  വൃക്ഷം rhseval = NULL_വൃക്ഷം;
  വൃക്ഷം lhstype = വൃക്ഷം_TYPE (lhs);
  വൃക്ഷം olhstype = lhstype;
  തർക്കം npc;
  തർക്കം is_atomic_op;

  /* Types that aren't fully specified cannot be used in assignments.  */
  lhs = require_complete_type (location, lhs);
  rhs = require_complete_type (location, rhs);

  /* Avoid duplicate error messages from operands that had errors.  */
  എങ്കിൽ (വൃക്ഷം_CODE (lhs) == ERROR_MARK || വൃക്ഷം_CODE (rhs) == ERROR_MARK)
    തിരികെ error_mark_കണ്ണി;

  /* Ensure an error for assigning a non-lvalue array to an array in
     C90.  */
  എങ്കിൽ (വൃക്ഷം_CODE (lhstype) == ARRAY_TYPE)
    {
      error_at (location, "assignment to expression with array type");
      തിരികെ error_mark_കണ്ണി;
    }

  /* For ObjC properties, defer this check.  */
  എങ്കിൽ (!objc_is_property_ref (lhs) && !lvalue_or_else (location, lhs, lv_assign))
    തിരികെ error_mark_കണ്ണി;

  is_atomic_op = really_atomic_lvalue (lhs);

  newrhs = rhs;

  എങ്കിൽ (വൃക്ഷം_CODE (lhs) == C_MAYBE_CONST_വ്യഞ്ജകം)
    {
      വൃക്ഷം inner = build_modify_വ്യഞ്ജകം (location, C_MAYBE_CONST_വ്യഞ്ജകം_വ്യഞ്ജകം (lhs),
				      lhs_origtype, modifycode, rhs_loc, rhs,
				      rhs_origtype);
      എങ്കിൽ (inner == error_mark_കണ്ണി)
	തിരികെ error_mark_കണ്ണി;
      result = build2 (C_MAYBE_CONST_വ്യഞ്ജകം, വൃക്ഷം_TYPE (inner),
		       C_MAYBE_CONST_വ്യഞ്ജകം_PRE (lhs), inner);
      gcc_assert (!C_MAYBE_CONST_വ്യഞ്ജകം_INT_OPERANDS (lhs));
      C_MAYBE_CONST_വ്യഞ്ജകം_NON_CONST (result) = 1;
      protected_set_വ്യഞ്ജകം_location (result, location);
      തിരികെ result;
    }

  /* If a binary op has been requested, combine the old LHS value with the RHS
     producing the value we should actually store into the LHS.  */

  എങ്കിൽ (modifycode != NOP_വ്യഞ്ജകം)
    {
      lhs = c_fully_fold (lhs, അസത്യം, ശൂന്യ, സത്യം);
      lhs = stabilize_reference (lhs);

      /* Construct the RHS for any non-atomic compound assignment. */
      എങ്കിൽ (!is_atomic_op)
        {
	  /* If in LHS op= RHS the RHS has side-effects, ensure they
	     are preevaluated before the rest of the assignment expression's
	     side-effects, because RHS could contain e.g. function calls
	     that modify LHS.  */
	  എങ്കിൽ (വൃക്ഷം_SIDE_EFFECTS (rhs))
	    {
	      എങ്കിൽ (വൃക്ഷം_CODE (rhs) == EXCESS_PRECISION_വ്യഞ്ജകം)
		newrhs = save_വ്യഞ്ജകം (വൃക്ഷം_OPERAND (rhs, 0));
	      അല്ലെങ്കിൽ
		newrhs = save_വ്യഞ്ജകം (rhs);
	      rhseval = newrhs;
	      എങ്കിൽ (വൃക്ഷം_CODE (rhs) == EXCESS_PRECISION_വ്യഞ്ജകം)
		newrhs = build1 (EXCESS_PRECISION_വ്യഞ്ജകം, വൃക്ഷം_TYPE (rhs),
				 newrhs);
	    }
	  തർക്കം clear_decl_read = അസത്യം;
	  എങ്കിൽ ((VAR_P (lhs) || വൃക്ഷം_CODE (lhs) == PARM_DECL)
	      && !DECL_READ_P (lhs)
	      && (VAR_P (lhs) ? warn_unused_but_set_variable
			      : warn_unused_but_set_parameter) > 2)
	    {
	      mark_exp_read (newrhs);
	      എങ്കിൽ (!DECL_READ_P (lhs))
		clear_decl_read = സത്യം;
	    }

	  newrhs = build_ദ്വിമാന_op (location, modifycode,
				    convert_lvalue_to_rvalue (location, lhs,
							      സത്യം, സത്യം),
				    newrhs, സത്യം);
	  എങ്കിൽ (clear_decl_read)
	    DECL_READ_P (lhs) = 0;

	  /* The original type of the right hand side is no longer
	     meaningful.  */
	  rhs_origtype = NULL_വൃക്ഷം;
	}
    }

  എങ്കിൽ (c_dialect_objc ())
    {
      /* Check if we are modifying an Objective-C property reference;
	 if so, we need to generate setter calls.  */
      എങ്കിൽ (വൃക്ഷം_CODE (newrhs) == EXCESS_PRECISION_വ്യഞ്ജകം)
	result = objc_maybe_build_modify_വ്യഞ്ജകം (lhs, വൃക്ഷം_OPERAND (newrhs, 0));
      അല്ലെങ്കിൽ
	result = objc_maybe_build_modify_വ്യഞ്ജകം (lhs, newrhs);
      എങ്കിൽ (result)
	പോകുക return_result;

      /* Else, do the check that we postponed for Objective-C.  */
      എങ്കിൽ (!lvalue_or_else (location, lhs, lv_assign))
	തിരികെ error_mark_കണ്ണി;
    }

  /* Give an error for storing in something that is 'const'.  */

  എങ്കിൽ (TYPE_READONLY (lhstype)
      || (RECORD_OR_UNION_TYPE_P (lhstype)
	  && C_TYPE_FIELDS_READONLY (lhstype)))
    {
      readonly_error (location, lhs, lv_assign);
      തിരികെ error_mark_കണ്ണി;
    }
  അല്ലെങ്കിൽ എങ്കിൽ (വൃക്ഷം_READONLY (lhs))
    readonly_warning (lhs, lv_assign);

  /* If storing into a structure or union member,
     it has probably been given type `int'.
     Compute the type that would go with
     the actual amount of storage the member occupies.  */

  എങ്കിൽ (വൃക്ഷം_CODE (lhs) == COMPONENT_REF
      && (വൃക്ഷം_CODE (lhstype) == INTEGER_TYPE
	  || വൃക്ഷം_CODE (lhstype) == BOOLEAN_TYPE
	  || SCALAR_FLOAT_TYPE_P (lhstype)
	  || വൃക്ഷം_CODE (lhstype) == ENUMERAL_TYPE))
    lhstype = വൃക്ഷം_TYPE (get_unwidened (lhs, 0));

  /* If storing in a field that is in actuality a short or narrower than one,
     we must store in the field in its actual type.  */

  എങ്കിൽ (lhstype != വൃക്ഷം_TYPE (lhs))
    {
      lhs = copy_കണ്ണി (lhs);
      വൃക്ഷം_TYPE (lhs) = lhstype;
    }

  /* Issue -Wc++-compat warnings about an assignment to an enum type
     when LHS does not have its original type.  This happens for,
     e.g., an enum bitfield in a struct.  */
  എങ്കിൽ (warn_cxx_compat
      && lhs_origtype != NULL_വൃക്ഷം
      && lhs_origtype != lhstype
      && വൃക്ഷം_CODE (lhs_origtype) == ENUMERAL_TYPE)
    {
      വൃക്ഷം checktype = (rhs_origtype != NULL_വൃക്ഷം
			? rhs_origtype
			: വൃക്ഷം_TYPE (rhs));
      എങ്കിൽ (checktype != error_mark_കണ്ണി
	  && (TYPE_MAIN_VARIANT (checktype) != TYPE_MAIN_VARIANT (lhs_origtype)
	      || (is_atomic_op && modifycode != NOP_വ്യഞ്ജകം)))
	warning_at (location, OPT_Wc___compat,
		    "enum conversion in assignment is invalid in C++");
    }

  /* Remove qualifiers.  */
  lhstype = c_build_qualified_type (lhstype, TYPE_UNQUALIFIED);
  olhstype = c_build_qualified_type (olhstype, TYPE_UNQUALIFIED);

  /* Convert new value to destination type.  Fold it first, then
     restore any excess precision information, for the sake of
     conversion warnings.  */

  എങ്കിൽ (!(is_atomic_op && modifycode != NOP_വ്യഞ്ജകം))
    {
      വൃക്ഷം rhs_semantic_type = NULL_വൃക്ഷം;
      എങ്കിൽ (!c_in_omp_for)
	{
	  എങ്കിൽ (വൃക്ഷം_CODE (newrhs) == EXCESS_PRECISION_വ്യഞ്ജകം)
	    {
	      rhs_semantic_type = വൃക്ഷം_TYPE (newrhs);
	      newrhs = വൃക്ഷം_OPERAND (newrhs, 0);
	    }
	  npc = null_pointer_constant_p (newrhs);
	  newrhs = c_fully_fold (newrhs, അസത്യം, ശൂന്യ);
	  എങ്കിൽ (rhs_semantic_type)
	    newrhs = build1 (EXCESS_PRECISION_വ്യഞ്ജകം, rhs_semantic_type, newrhs);
	}
      അല്ലെങ്കിൽ
	npc = null_pointer_constant_p (newrhs);
      newrhs = convert_for_assignment (location, rhs_loc, lhstype, newrhs,
				       rhs_origtype, ic_assign, npc,
				       NULL_വൃക്ഷം, NULL_വൃക്ഷം, 0);
      എങ്കിൽ (വൃക്ഷം_CODE (newrhs) == ERROR_MARK)
	തിരികെ error_mark_കണ്ണി;
    }

  /* Emit ObjC write barrier, if necessary.  */
  എങ്കിൽ (c_dialect_objc () && flag_objc_gc)
    {
      result = objc_generate_write_barrier (lhs, modifycode, newrhs);
      എങ്കിൽ (result)
	{
	  protected_set_വ്യഞ്ജകം_location (result, location);
	  പോകുക return_result;
	}
    }

  /* Scan operands.  */

  എങ്കിൽ (is_atomic_op)
    result = build_atomic_assign (location, lhs, modifycode, newrhs, അസത്യം);
  അല്ലെങ്കിൽ
    {
      result = build2 (MODIFY_വ്യഞ്ജകം, lhstype, lhs, newrhs);
      വൃക്ഷം_SIDE_EFFECTS (result) = 1;
      protected_set_വ്യഞ്ജകം_location (result, location);
    }

  /* If we got the LHS in a different type for storing in,
     convert the result back to the nominal type of LHS
     so that the value we return always has the same type
     as the LHS argument.  */

  എങ്കിൽ (olhstype == വൃക്ഷം_TYPE (result))
    പോകുക return_result;

  result = convert_for_assignment (location, rhs_loc, olhstype, result,
				   rhs_origtype, ic_assign, അസത്യം, NULL_വൃക്ഷം,
				   NULL_വൃക്ഷം, 0);
  protected_set_വ്യഞ്ജകം_location (result, location);

return_result:
  എങ്കിൽ (rhseval)
    result = build2 (COMPOUND_വ്യഞ്ജകം, വൃക്ഷം_TYPE (result), rhseval, result);
  തിരികെ result;
}

/* Return whether STRUCT_TYPE has an anonymous field with type TYPE.
   This is used to implement -fplan9-extensions.  */

സ്ഥിതം തർക്കം
find_anonymous_field_with_type (വൃക്ഷം struct_type, വൃക്ഷം type)
{
  വൃക്ഷം field;
  തർക്കം found;

  gcc_assert (RECORD_OR_UNION_TYPE_P (struct_type));
  found = അസത്യം;
  വേണ്ടി (field = TYPE_FIELDS (struct_type);
       field != NULL_വൃക്ഷം;
       field = വൃക്ഷം_CHAIN (field))
    {
      വൃക്ഷം fieldtype = remove_qualifiers (വൃക്ഷം_TYPE (field));
      എങ്കിൽ (DECL_NAME (field) == ശൂന്യ
	  && comptypes (type, fieldtype))
	{
	  എങ്കിൽ (found)
	    തിരികെ അസത്യം;
	  found = സത്യം;
	}
      അല്ലെങ്കിൽ എങ്കിൽ (DECL_NAME (field) == ശൂന്യ
	       && RECORD_OR_UNION_TYPE_P (വൃക്ഷം_TYPE (field))
	       && find_anonymous_field_with_type (വൃക്ഷം_TYPE (field), type))
	{
	  എങ്കിൽ (found)
	    തിരികെ അസത്യം;
	  found = സത്യം;
	}
    }
  തിരികെ found;
}

/* RHS is an expression whose type is pointer to struct.  If there is
   an anonymous field in RHS with type TYPE, then return a pointer to
   that field in RHS.  This is used with -fplan9-extensions.  This
   returns NULL if no conversion could be found.  */

സ്ഥിതം വൃക്ഷം
convert_to_anonymous_field (location_t location, വൃക്ഷം type, വൃക്ഷം rhs)
{
  വൃക്ഷം rhs_struct_type, lhs_main_type;
  വൃക്ഷം field, found_field;
  തർക്കം found_sub_field;
  വൃക്ഷം ret;

  gcc_assert (POINTER_TYPE_P (വൃക്ഷം_TYPE (rhs)));
  rhs_struct_type = വൃക്ഷം_TYPE (വൃക്ഷം_TYPE (rhs));
  gcc_assert (RECORD_OR_UNION_TYPE_P (rhs_struct_type));

  gcc_assert (POINTER_TYPE_P (type));
  lhs_main_type = remove_qualifiers (വൃക്ഷം_TYPE (type));

  found_field = NULL_വൃക്ഷം;
  found_sub_field = അസത്യം;
  വേണ്ടി (field = TYPE_FIELDS (rhs_struct_type);
       field != NULL_വൃക്ഷം;
       field = വൃക്ഷം_CHAIN (field))
    {
      എങ്കിൽ (DECL_NAME (field) != NULL_വൃക്ഷം
	  || !RECORD_OR_UNION_TYPE_P (വൃക്ഷം_TYPE (field)))
	തുടരുക;
      വൃക്ഷം fieldtype = remove_qualifiers (വൃക്ഷം_TYPE (field));
      എങ്കിൽ (comptypes (lhs_main_type, fieldtype))
	{
	  എങ്കിൽ (found_field != NULL_വൃക്ഷം)
	    തിരികെ NULL_വൃക്ഷം;
	  found_field = field;
	}
      അല്ലെങ്കിൽ എങ്കിൽ (find_anonymous_field_with_type (വൃക്ഷം_TYPE (field),
					       lhs_main_type))
	{
	  എങ്കിൽ (found_field != NULL_വൃക്ഷം)
	    തിരികെ NULL_വൃക്ഷം;
	  found_field = field;
	  found_sub_field = സത്യം;
	}
    }

  എങ്കിൽ (found_field == NULL_വൃക്ഷം)
    തിരികെ NULL_വൃക്ഷം;

  ret = fold_build3_loc (location, COMPONENT_REF, വൃക്ഷം_TYPE (found_field),
			 build_fold_indirect_ref (rhs), found_field,
			 NULL_വൃക്ഷം);
  ret = build_fold_addr_വ്യഞ്ജകം_loc (location, ret);

  എങ്കിൽ (found_sub_field)
    {
      ret = convert_to_anonymous_field (location, type, ret);
      gcc_assert (ret != NULL_വൃക്ഷം);
    }

  തിരികെ ret;
}

/* Issue an error message for a bad initializer component.
   GMSGID identifies the message.
   The component name is taken from the spelling stack.  */

സ്ഥിതം ശൂന്യം ATTRIBUTE_GCC_DIAG (2,0)
error_init (location_t loc, സ്ഥിരം അക്ഷരം *gmsgid, ...)
{
  അക്ഷരം *ofwhat;

  auto_diagnostic_group d;

  /* The gmsgid may be a format string with %< and %>. */
  va_list ap;
  va_start (ap, gmsgid);
  തർക്കം warned = emit_diagnostic_valist (diagnostics::kind::error,
					loc, -1, gmsgid, &ap);
  va_end (ap);

  ofwhat = print_spelling ((അക്ഷരം *) alloca (spelling_length () + 1));
  എങ്കിൽ (*ofwhat && warned)
    inform (loc, "(near initialization for %qs)", ofwhat);
}

/* Used to implement pedwarn_init and permerror_init.  */

സ്ഥിതം തർക്കം ATTRIBUTE_GCC_DIAG (3,0)
pedwarn_permerror_init (location_t loc, പൂർണ്ണസംഖ്യ opt, സ്ഥിരം അക്ഷരം *gmsgid,
			va_list *ap, എണ്ണൽ diagnostics::kind kind)
{
  /* Use the location where a macro was expanded rather than where
     it was defined to make sure macros defined in system headers
     but used incorrectly elsewhere are diagnosed.  */
  location_t exploc = expansion_point_location_if_in_system_header (loc);
  auto_diagnostic_group d;
  തർക്കം warned = emit_diagnostic_valist (kind, exploc, opt, gmsgid, ap);
  എങ്കിൽ (warned)
    {
      അക്ഷരം *ofwhat = print_spelling ((അക്ഷരം *) alloca (spelling_length () + 1));
      എങ്കിൽ (*ofwhat)
	inform (exploc, "(near initialization for %qs)", ofwhat);
    }
  തിരികെ warned;
}

/* Issue a pedantic warning for a bad initializer component.  OPT is
   the option OPT_* (from options.h) controlling this warning or 0 if
   it is unconditionally given.  GMSGID identifies the message.  The
   component name is taken from the spelling stack.  */

സ്ഥിതം തർക്കം ATTRIBUTE_GCC_DIAG (3,0)
pedwarn_init (location_t loc, പൂർണ്ണസംഖ്യ opt, സ്ഥിരം അക്ഷരം *gmsgid, ...)
{
  va_list ap;
  va_start (ap, gmsgid);
  തർക്കം warned = pedwarn_permerror_init (loc, opt, gmsgid, &ap,
					diagnostics::kind::pedwarn);
  va_end (ap);
  തിരികെ warned;
}

/* Like pedwarn_init, but issue a permerror.  */

സ്ഥിതം തർക്കം ATTRIBUTE_GCC_DIAG (3,0)
permerror_init (location_t loc, പൂർണ്ണസംഖ്യ opt, സ്ഥിരം അക്ഷരം *gmsgid, ...)
{
  va_list ap;
  va_start (ap, gmsgid);
  തർക്കം warned = pedwarn_permerror_init (loc, opt, gmsgid, &ap,
					diagnostics::kind::permerror);
  va_end (ap);
  തിരികെ warned;
}

/* Issue a warning for a bad initializer component.

   OPT is the OPT_W* value corresponding to the warning option that
   controls this warning.  GMSGID identifies the message.  The
   component name is taken from the spelling stack.  */

സ്ഥിതം ശൂന്യം
warning_init (location_t loc, പൂർണ്ണസംഖ്യ opt, സ്ഥിരം അക്ഷരം *gmsgid)
{
  അക്ഷരം *ofwhat;
  തർക്കം warned;

  auto_diagnostic_group d;

  /* Use the location where a macro was expanded rather than where
     it was defined to make sure macros defined in system headers
     but used incorrectly elsewhere are diagnosed.  */
  location_t exploc = expansion_point_location_if_in_system_header (loc);

  /* The gmsgid may be a format string with %< and %>. */
  warned = warning_at (exploc, opt, gmsgid);
  എങ്കിൽ (warned)
    {
      ofwhat = print_spelling ((അക്ഷരം *) alloca (spelling_length () + 1));
      എങ്കിൽ (*ofwhat)
	inform (exploc, "(near initialization for %qs)", ofwhat);
    }
}

/* If TYPE is an array type and EXPR is a parenthesized string
   constant, warn if pedantic that EXPR is being used to initialize an
   object of type TYPE.  */

ശൂന്യം
maybe_warn_string_init (location_t loc, വൃക്ഷം type, ഘടന c_വ്യഞ്ജകം വ്യഞ്ജകം)
{
  എങ്കിൽ (pedantic
      && വൃക്ഷം_CODE (type) == ARRAY_TYPE
      && വൃക്ഷം_CODE (വ്യഞ്ജകം.മൂല്യം) == STRING_CST
      && വ്യഞ്ജകം.original_code != STRING_CST)
    pedwarn_init (loc, OPT_Wpedantic,
		  "array initialized from parenthesized string constant");
}

/* Attempt to locate the parameter with the given index within FNDECL,
   returning DECL_SOURCE_LOCATION (FNDECL) if it can't be found.  */

സ്ഥിതം location_t
get_fndecl_argument_location (വൃക്ഷം fndecl, പൂർണ്ണസംഖ്യ argnum)
{
  പൂർണ്ണസംഖ്യ i;
  വൃക്ഷം param;

  /* Locate param by index within DECL_ARGUMENTS (fndecl).  */
  വേണ്ടി (i = 0, param = DECL_ARGUMENTS (fndecl);
       i < argnum && param;
       i++, param = വൃക്ഷം_CHAIN (param))
    ;

  /* If something went wrong (e.g. if we have a builtin and thus no arguments),
     return DECL_SOURCE_LOCATION (FNDECL).  */
  എങ്കിൽ (param == ശൂന്യ)
    തിരികെ DECL_SOURCE_LOCATION (fndecl);

  തിരികെ DECL_SOURCE_LOCATION (param);
}

/* Issue a note about a mismatching argument for parameter PARMNUM
   to FUNDECL, for types EXPECTED_TYPE and ACTUAL_TYPE.
   Attempt to issue the note at the pertinent parameter of the decl;
   failing that issue it at the location of FUNDECL; failing that
   issue it at PLOC.
   Use highlight_colors::actual for the ACTUAL_TYPE
   and highlight_colors::expected for EXPECTED_TYPE and the
   parameter of FUNDECL*/

സ്ഥിതം ശൂന്യം
inform_for_arg (വൃക്ഷം fundecl, location_t ploc, പൂർണ്ണസംഖ്യ parmnum,
		വൃക്ഷം expected_type, വൃക്ഷം actual_type)
{
  location_t loc;
  എങ്കിൽ (fundecl && !DECL_IS_UNDECLARED_BUILTIN (fundecl))
    loc = get_fndecl_argument_location (fundecl, parmnum - 1);
  അല്ലെങ്കിൽ
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

സ്ഥിതം ശൂന്യം
maybe_warn_builtin_no_proto_arg (location_t loc, വൃക്ഷം fundecl, പൂർണ്ണസംഖ്യ parmnum,
				 വൃക്ഷം parmtype, വൃക്ഷം argtype)
{
  വൃക്ഷം_code parmcode = വൃക്ഷം_CODE (parmtype);
  വൃക്ഷം_code argcode = വൃക്ഷം_CODE (argtype);
  വൃക്ഷം promoted = c_type_promotes_to (argtype);

  /* Avoid warning for enum arguments that promote to an integer type
     of the same size/mode.  */
  എങ്കിൽ (parmcode == INTEGER_TYPE
      && argcode == ENUMERAL_TYPE
      && TYPE_MODE (parmtype) == TYPE_MODE (argtype))
    തിരികെ;

  എങ്കിൽ ((parmcode == argcode
       || (parmcode == INTEGER_TYPE
	   && argcode == ENUMERAL_TYPE))
      && TYPE_MAIN_VARIANT (parmtype) == TYPE_MAIN_VARIANT (promoted))
    തിരികെ;

  /* This diagnoses even signed/unsigned mismatches.  Those might be
     safe in many cases but GCC may emit suboptimal code for them so
     warning on those cases drives efficiency improvements.  */
  എങ്കിൽ (warning_at (loc, OPT_Wbuiltin_declaration_mismatch,
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

വർഗ്ഗം pp_element_quoted_decl : പൊതു pp_element
{
പൊതു:
  pp_element_quoted_decl (വൃക്ഷം decl, സ്ഥിരം അക്ഷരം *highlight_color)
  : m_decl (decl),
    m_highlight_color (highlight_color)
  {
  }

  ശൂന്യം add_to_phase_2 (pp_markup::context &ctxt) override
  {
    ctxt.begin_quote ();
    ctxt.begin_highlight_color (m_highlight_color);

    print_decl (ctxt);

    ctxt.end_highlight_color ();
    ctxt.end_quote ();
  }

  ശൂന്യം print_decl (pp_markup::context &ctxt)
  {
    pretty_printer *സ്ഥിരം pp = &ctxt.m_pp;
    pp->set_padding (pp_none);
    എങ്കിൽ (DECL_NAME (m_decl))
      pp_identifier (pp, lang_hooks.decl_printable_name (m_decl, 2));
    അല്ലെങ്കിൽ
      pp_string (pp, _("({anonymous})"));
  }

സ്വകാര്യ:
  വൃക്ഷം m_decl;
  സ്ഥിരം അക്ഷരം *m_highlight_color;
};

/* If TYPE is from a typedef, issue a note showing the location
   to the user.
   Use HIGHLIGHT_COLOR as the highlight color.  */

സ്ഥിതം ശൂന്യം
maybe_inform_typedef_location (വൃക്ഷം type, സ്ഥിരം അക്ഷരം *highlight_color)
{
  എങ്കിൽ (!typedef_variant_p (type))
    തിരികെ;

  വൃക്ഷം typedef_decl = TYPE_NAME (type);
  gcc_assert (വൃക്ഷം_CODE (typedef_decl) == TYPE_DECL);
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

സ്ഥിതം വൃക്ഷം
convert_for_assignment (location_t location, location_t വ്യഞ്ജകം_loc, വൃക്ഷം type,
			വൃക്ഷം rhs, വൃക്ഷം origtype, എണ്ണൽ impl_conv errtype,
			തർക്കം null_pointer_constant, വൃക്ഷം fundecl,
			വൃക്ഷം function, പൂർണ്ണസംഖ്യ parmnum, പൂർണ്ണസംഖ്യ warnopt /* = 0 */)
{
  എണ്ണൽ വൃക്ഷം_code codel = വൃക്ഷം_CODE (type);
  വൃക്ഷം orig_rhs = rhs;
  വൃക്ഷം rhstype;
  എണ്ണൽ വൃക്ഷം_code coder;
  വൃക്ഷം rname = NULL_വൃക്ഷം;
  തർക്കം objc_ok = അസത്യം;

  /* Use the expansion point location to handle cases such as user's
     function returning a wrong-type macro defined in a system header.  */
  location = expansion_point_location_if_in_system_header (location);

  എങ്കിൽ (errtype == ic_argpass)
    {
      വൃക്ഷം selector;
      /* Change pointer to function to the function itself for
	 diagnostics.  */
      എങ്കിൽ (വൃക്ഷം_CODE (function) == ADDR_വ്യഞ്ജകം
	  && വൃക്ഷം_CODE (വൃക്ഷം_OPERAND (function, 0)) == FUNCTION_DECL)
	function = വൃക്ഷം_OPERAND (function, 0);

      /* Handle an ObjC selector specially for diagnostics.  */
      selector = objc_message_selector ();
      rname = function;
      എങ്കിൽ (selector && parmnum > 2)
	{
	  rname = selector;
	  parmnum -= 2;
	}
    }

  /* This macro is used to emit diagnostics to ensure that all format
     strings are complete sentences, visible to gettext and checked at
     compile time.  */
#define PEDWARN_FOR_ASSIGNMENT(LOCATION, PLOC, OPT, AR, AS, IN, RE)	 \
  ചെയ്യുക {                                                                   \
    തിരഞ്ഞെടുപ്പ് (errtype)                                                     \
      {                                                                  \
      അവസ്ഥ ic_argpass:                                                   \
	{								\
	  auto_diagnostic_group d;						\
	  എങ്കിൽ (pedwarn (PLOC, OPT, AR, parmnum, rname))		\
	    inform_for_arg (fundecl, (PLOC), parmnum, type, rhstype); \
	}								\
        നിർത്തുക;                                                           \
      അവസ്ഥ ic_assign:                                                    \
        pedwarn (LOCATION, OPT, AS);                                     \
        നിർത്തുക;                                                           \
      അവസ്ഥ ic_init:                                                      \
      അവസ്ഥ ic_init_const:                                                \
        pedwarn_init (LOCATION, OPT, IN);                                \
        നിർത്തുക;                                                           \
      അവസ്ഥ ic_return:                                                    \
        pedwarn (LOCATION, OPT, RE);					 \
        നിർത്തുക;                                                           \
      സ്ഥിരസ്ഥിതി:                                                           \
        gcc_unreachable ();                                              \
      }                                                                  \
  } ആകുമ്പോൾ (0)

  /* This macro is used to emit diagnostics to ensure that all format
     strings are complete sentences, visible to gettext and checked at
     compile time.  It can be called with 'pedwarn' or 'warning_at'.  */
#define WARNING_FOR_QUALIFIERS(PEDWARN, LOCATION, PLOC, OPT, AR, AS, IN, RE, QUALS) \
  ചെയ്യുക {                                                                   \
    തിരഞ്ഞെടുപ്പ് (errtype)                                                     \
      {                                                                  \
      അവസ്ഥ ic_argpass:                                                   \
	{								 \
	  auto_diagnostic_group d;					 \
	  എങ്കിൽ (PEDWARN) {						 \
	    എങ്കിൽ (pedwarn (PLOC, OPT, AR, parmnum, rname, QUALS))          \
	      inform_for_arg (fundecl, (PLOC), parmnum, type, rhstype);  \
	  } അല്ലെങ്കിൽ {							 \
	    എങ്കിൽ (warning_at (PLOC, OPT, AR, parmnum, rname, QUALS))	 \
	      inform_for_arg (fundecl, (PLOC), parmnum, type, rhstype);  \
	  }								 \
	}								 \
        നിർത്തുക;                                                           \
      അവസ്ഥ ic_assign:                                                    \
	എങ്കിൽ (PEDWARN)							 \
	  pedwarn (LOCATION, OPT, AS, QUALS);                            \
	അല്ലെങ്കിൽ								 \
	  warning_at (LOCATION, OPT, AS, QUALS);                         \
        നിർത്തുക;                                                           \
      അവസ്ഥ ic_init:                                                      \
      അവസ്ഥ ic_init_const:                                                \
	എങ്കിൽ (PEDWARN)							 \
	  pedwarn (LOCATION, OPT, IN, QUALS);                            \
	അല്ലെങ്കിൽ								 \
	  warning_at (LOCATION, OPT, IN, QUALS);                         \
        നിർത്തുക;                                                           \
      അവസ്ഥ ic_return:                                                    \
	എങ്കിൽ (PEDWARN)							 \
	  pedwarn (LOCATION, OPT, RE, QUALS);                            \
	അല്ലെങ്കിൽ								 \
	  warning_at (LOCATION, OPT, RE, QUALS);                         \
        നിർത്തുക;                                                           \
      സ്ഥിരസ്ഥിതി:                                                           \
        gcc_unreachable ();                                              \
      }                                                                  \
  } ആകുമ്പോൾ (0)

  /* This macro is used to emit diagnostics to ensure that all format
     strings are complete sentences, visible to gettext and checked at
     compile time.  It is the same as PEDWARN_FOR_ASSIGNMENT but with an
     extra parameter to enumerate qualifiers.  */
#define PEDWARN_FOR_QUALIFIERS(LOCATION, PLOC, OPT, AR, AS, IN, RE, QUALS) \
   WARNING_FOR_QUALIFIERS (സത്യം, LOCATION, PLOC, OPT, AR, AS, IN, RE, QUALS)


  എങ്കിൽ (വൃക്ഷം_CODE (rhs) == EXCESS_PRECISION_വ്യഞ്ജകം)
    rhs = വൃക്ഷം_OPERAND (rhs, 0);

  rhstype = വൃക്ഷം_TYPE (rhs);
  coder = വൃക്ഷം_CODE (rhstype);

  എങ്കിൽ (coder == ERROR_MARK)
    തിരികെ error_mark_കണ്ണി;

  എങ്കിൽ (c_dialect_objc ())
    {
      പൂർണ്ണസംഖ്യ parmno;

      തിരഞ്ഞെടുപ്പ് (errtype)
	{
	അവസ്ഥ ic_return:
	  parmno = 0;
	  നിർത്തുക;

	അവസ്ഥ ic_assign:
	  parmno = -1;
	  നിർത്തുക;

	അവസ്ഥ ic_init:
	അവസ്ഥ ic_init_const:
	  parmno = -2;
	  നിർത്തുക;

	സ്ഥിരസ്ഥിതി:
	  parmno = parmnum;
	  നിർത്തുക;
	}

      objc_ok = objc_compare_types (type, rhstype, parmno, rname);
    }

  എങ്കിൽ (warn_cxx_compat)
    {
      വൃക്ഷം checktype = origtype != NULL_വൃക്ഷം ? origtype : rhstype;
      എങ്കിൽ (checktype != error_mark_കണ്ണി
	  && വൃക്ഷം_CODE (type) == ENUMERAL_TYPE
	  && TYPE_MAIN_VARIANT (checktype) != TYPE_MAIN_VARIANT (type))
	തിരഞ്ഞെടുപ്പ് (errtype)
	  {
	  അവസ്ഥ ic_argpass:
	    എങ്കിൽ (pedwarn (വ്യഞ്ജകം_loc, OPT_Wc___compat, "enum conversion when "
			 "passing argument %d of %qE is invalid in C++",
			 parmnum, rname))
	      inform ((fundecl && !DECL_IS_UNDECLARED_BUILTIN (fundecl))
		      ? DECL_SOURCE_LOCATION (fundecl) : വ്യഞ്ജകം_loc,
		      "expected %qT but argument is of type %qT",
		      type, rhstype);
	    നിർത്തുക;
	  അവസ്ഥ ic_assign:
	    pedwarn (location, OPT_Wc___compat, "enum conversion from %qT to "
		     "%qT in assignment is invalid in C++", rhstype, type);
	    നിർത്തുക;
	  അവസ്ഥ ic_init:
	  അവസ്ഥ ic_init_const:
	    pedwarn_init (location, OPT_Wc___compat, "enum conversion from "
			  "%qT to %qT in initialization is invalid in C++",
			  rhstype, type);
	    നിർത്തുക;
	  അവസ്ഥ ic_return:
	    pedwarn (location, OPT_Wc___compat, "enum conversion from %qT to "
		     "%qT in return is invalid in C++", rhstype, type);
	    നിർത്തുക;
	  സ്ഥിരസ്ഥിതി:
	    gcc_unreachable ();
	  }
    }

  എങ്കിൽ (warn_enum_conversion)
    {
      വൃക്ഷം checktype = origtype != NULL_വൃക്ഷം ? origtype : rhstype;
      എങ്കിൽ (checktype != error_mark_കണ്ണി
	  && വൃക്ഷം_CODE (checktype) == ENUMERAL_TYPE
	  && വൃക്ഷം_CODE (type) == ENUMERAL_TYPE
	  && !comptypes (TYPE_MAIN_VARIANT (checktype), TYPE_MAIN_VARIANT (type)))
       {
	  gcc_rich_location loc (location);
	  warning_at (&loc, OPT_Wenum_conversion,
		      "implicit conversion from %qT to %qT",
		      checktype, type);
       }
    }

  എങ്കിൽ (TYPE_MAIN_VARIANT (type) == TYPE_MAIN_VARIANT (rhstype))
    {
      warn_for_address_of_packed_member (type, orig_rhs);
      എങ്കിൽ (type != rhstype)
	/* Convert RHS to TYPE in order to not lose TYPE in diagnostics.  */
	rhs = convert (type, rhs);
      തിരികെ rhs;
    }

  എങ്കിൽ (coder == VOID_TYPE)
    {
      /* Except for passing an argument to an unprototyped function,
	 this is a constraint violation.  When passing an argument to
	 an unprototyped function, it is compile-time undefined;
	 making it a constraint in that case was rejected in
	 DR#252.  */
      സ്ഥിരം അക്ഷരം സന്ദേശം[] = "void value not ignored as it ought to be";
      എങ്കിൽ (warnopt)
	warning_at (location, warnopt, സന്ദേശം);
      അല്ലെങ്കിൽ
	error_at (location, സന്ദേശം);
      തിരികെ error_mark_കണ്ണി;
    }
  rhs = require_complete_type (location, rhs);
  എങ്കിൽ (rhs == error_mark_കണ്ണി)
    തിരികെ error_mark_കണ്ണി;

  എങ്കിൽ (coder == POINTER_TYPE && reject_gcc_builtin (rhs))
    തിരികെ error_mark_കണ്ണി;

  /* A non-reference type can convert to a reference.  This handles
     va_start, va_copy and possibly port built-ins.  */
  എങ്കിൽ (codel == REFERENCE_TYPE && coder != REFERENCE_TYPE)
    {
      എങ്കിൽ (!lvalue_p (rhs))
	{
	  സ്ഥിരം അക്ഷരം സന്ദേശം[] = "cannot pass rvalue to reference parameter";
	  എങ്കിൽ (warnopt)
	    warning_at (location, warnopt, സന്ദേശം);
	  അല്ലെങ്കിൽ
	    error_at (location, സന്ദേശം);
	  തിരികെ error_mark_കണ്ണി;
	}
      എങ്കിൽ (!c_mark_addressable (rhs))
	തിരികെ error_mark_കണ്ണി;
      rhs = build1 (ADDR_വ്യഞ്ജകം, c_build_pointer_type (വൃക്ഷം_TYPE (rhs)), rhs);
      SET_വ്യഞ്ജകം_LOCATION (rhs, location);

      rhs = convert_for_assignment (location, വ്യഞ്ജകം_loc,
				    c_build_pointer_type (വൃക്ഷം_TYPE (type)),
				    rhs, origtype, errtype,
				    null_pointer_constant, fundecl, function,
				    parmnum, warnopt);
      എങ്കിൽ (rhs == error_mark_കണ്ണി)
	തിരികെ error_mark_കണ്ണി;

      rhs = build1 (NOP_വ്യഞ്ജകം, type, rhs);
      SET_വ്യഞ്ജകം_LOCATION (rhs, location);
      തിരികെ rhs;
    }
  /* Some types can interconvert without explicit casts.  */
  അല്ലെങ്കിൽ എങ്കിൽ (codel == VECTOR_TYPE && coder == VECTOR_TYPE
	   && vector_types_convertible_p (type, വൃക്ഷം_TYPE (rhs), സത്യം))
    തിരികെ convert (type, rhs);
  /* Arithmetic types all interconvert, and enum is treated like int.  */
  അല്ലെങ്കിൽ എങ്കിൽ ((codel == INTEGER_TYPE || codel == REAL_TYPE
	    || codel == FIXED_POINT_TYPE
	    || codel == ENUMERAL_TYPE || codel == COMPLEX_TYPE
	    || codel == BOOLEAN_TYPE || codel == BITINT_TYPE)
	   && (coder == INTEGER_TYPE || coder == REAL_TYPE
	       || coder == FIXED_POINT_TYPE
	       || coder == ENUMERAL_TYPE || coder == COMPLEX_TYPE
	       || coder == BOOLEAN_TYPE || coder == BITINT_TYPE))
    {
      എങ്കിൽ (warnopt && errtype == ic_argpass)
	maybe_warn_builtin_no_proto_arg (വ്യഞ്ജകം_loc, fundecl, parmnum, type,
					 rhstype);

      തർക്കം save = in_late_ദ്വിമാന_op;
      എങ്കിൽ (C_BOOLEAN_TYPE_P (type) || codel == COMPLEX_TYPE
	  || (coder == REAL_TYPE
	      && (codel == INTEGER_TYPE || codel == ENUMERAL_TYPE)
	      && sanitize_flags_p (SANITIZE_FLOAT_CAST)))
	in_late_ദ്വിമാന_op = സത്യം;
      വൃക്ഷം ret = convert_and_check (വ്യഞ്ജകം_loc != UNKNOWN_LOCATION
				    ? വ്യഞ്ജകം_loc : location, type, orig_rhs,
				    errtype == ic_init_const);
      in_late_ദ്വിമാന_op = save;
      തിരികെ ret;
    }

  /* Aggregates in different TUs might need conversion.  */
  എങ്കിൽ ((codel == RECORD_TYPE || codel == UNION_TYPE)
      && codel == coder
      && comptypes (TYPE_MAIN_VARIANT (type), TYPE_MAIN_VARIANT (rhstype)))
    തിരികെ convert_and_check (വ്യഞ്ജകം_loc != UNKNOWN_LOCATION
			      ? വ്യഞ്ജകം_loc : location, type, rhs);

  /* Conversion to a transparent union or record from its member types.
     This applies only to function arguments.  */
  എങ്കിൽ (((codel == UNION_TYPE || codel == RECORD_TYPE)
      && TYPE_TRANSPARENT_AGGR (type))
      && errtype == ic_argpass)
    {
      വൃക്ഷം memb, marginal_memb = NULL_വൃക്ഷം;

      വേണ്ടി (memb = TYPE_FIELDS (type); memb ; memb = DECL_CHAIN (memb))
	{
	  വൃക്ഷം memb_type = വൃക്ഷം_TYPE (memb);

	  എങ്കിൽ (comptypes (TYPE_MAIN_VARIANT (memb_type),
			 TYPE_MAIN_VARIANT (rhstype)))
	    നിർത്തുക;

	  എങ്കിൽ (വൃക്ഷം_CODE (memb_type) != POINTER_TYPE)
	    തുടരുക;

	  എങ്കിൽ (coder == POINTER_TYPE)
	    {
	      വൃക്ഷം ttl = വൃക്ഷം_TYPE (memb_type);
	      വൃക്ഷം ttr = വൃക്ഷം_TYPE (rhstype);

	      /* Any non-function converts to a [const][volatile] void *
		 and vice versa; otherwise, targets must be the same.
		 Meanwhile, the lhs target must have all the qualifiers of
		 the rhs.  */
	      എങ്കിൽ ((VOID_TYPE_P (ttl) && !TYPE_ATOMIC (ttl))
		  || (VOID_TYPE_P (ttr) && !TYPE_ATOMIC (ttr))
		  || comp_target_types (location, memb_type, rhstype))
		{
		  പൂർണ്ണസംഖ്യ lquals = TYPE_QUALS (ttl) & ~TYPE_QUAL_ATOMIC;
		  പൂർണ്ണസംഖ്യ rquals = TYPE_QUALS (ttr) & ~TYPE_QUAL_ATOMIC;
		  /* If this type won't generate any warnings, use it.  */
		  എങ്കിൽ (lquals == rquals
		      || ((വൃക്ഷം_CODE (ttr) == FUNCTION_TYPE
			   && വൃക്ഷം_CODE (ttl) == FUNCTION_TYPE)
			  ? ((lquals | rquals) == rquals)
			  : ((lquals | rquals) == lquals)))
		    നിർത്തുക;

		  /* Keep looking for a better type, but remember this one.  */
		  എങ്കിൽ (!marginal_memb)
		    marginal_memb = memb;
		}
	    }

	  /* Can convert integer zero to any pointer type.  */
	  എങ്കിൽ (null_pointer_constant)
	    {
	      rhs = null_pointer_കണ്ണി;
	      നിർത്തുക;
	    }
	}

      എങ്കിൽ (memb || marginal_memb)
	{
	  എങ്കിൽ (!memb)
	    {
	      /* We have only a marginally acceptable member type;
		 it needs a warning.  */
	      വൃക്ഷം ttl = വൃക്ഷം_TYPE (വൃക്ഷം_TYPE (marginal_memb));
	      വൃക്ഷം ttr = വൃക്ഷം_TYPE (rhstype);

	      /* Const and volatile mean something different for function
		 types, so the usual warnings are not appropriate.  */
	      എങ്കിൽ (വൃക്ഷം_CODE (ttr) == FUNCTION_TYPE
		  && വൃക്ഷം_CODE (ttl) == FUNCTION_TYPE)
		{
		  /* Because const and volatile on functions are
		     restrictions that say the function will not do
		     certain things, it is okay to use a const or volatile
		     function where an ordinary one is wanted, but not
		     vice-versa.  */
		  എങ്കിൽ (TYPE_QUALS_NO_ADDR_SPACE (ttl)
		      & ~TYPE_QUALS_NO_ADDR_SPACE (ttr))
		    PEDWARN_FOR_QUALIFIERS (location, വ്യഞ്ജകം_loc,
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
	      അല്ലെങ്കിൽ എങ്കിൽ (TYPE_QUALS_NO_ADDR_SPACE (ttr)
		       & ~TYPE_QUALS_NO_ADDR_SPACE (ttl))
		PEDWARN_FOR_QUALIFIERS (location, വ്യഞ്ജകം_loc,
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

	  എങ്കിൽ (!fundecl || !DECL_IN_SYSTEM_HEADER (fundecl))
	    pedwarn (location, OPT_Wpedantic,
		     "ISO C prohibits argument conversion to union type");

	  rhs = fold_convert_loc (location, വൃക്ഷം_TYPE (memb), rhs);
	  തിരികെ build_constructor_single (type, memb, rhs);
	}
    }

  /* Conversions among pointers */
  അല്ലെങ്കിൽ എങ്കിൽ ((codel == POINTER_TYPE || codel == REFERENCE_TYPE)
	   && (coder == codel))
    {
      /* If RHS refers to a built-in declared without a prototype
	 BLTIN is the declaration of the built-in with a prototype
	 and RHSTYPE is set to the actual type of the built-in.  */
      വൃക്ഷം bltin;
      rhstype = type_or_builtin_type (rhs, &bltin);

      വൃക്ഷം ttl = വൃക്ഷം_TYPE (type);
      വൃക്ഷം ttr = വൃക്ഷം_TYPE (rhstype);
      തർക്കം is_opaque_pointer;
      തർക്കം target_cmp = അസത്യം;   /* Cache comp_target_types () result.  */
      addr_space_t asl;
      addr_space_t asr;

      വൃക്ഷം mvl = remove_qualifiers (ttl);
      വൃക്ഷം mvr = remove_qualifiers (ttr);

      /* Opaque pointers are treated like void pointers.  */
      is_opaque_pointer = vector_targets_convertible_p (ttl, ttr);

      /* The Plan 9 compiler permits a pointer to a struct to be
	 automatically converted into a pointer to an anonymous field
	 within the struct.  */
      എങ്കിൽ (flag_plan9_extensions
	  && RECORD_OR_UNION_TYPE_P (mvl)
	  && RECORD_OR_UNION_TYPE_P (mvr)
	  && mvl != mvr)
	{
	  വൃക്ഷം new_rhs = convert_to_anonymous_field (location, type, rhs);
	  എങ്കിൽ (new_rhs != NULL_വൃക്ഷം)
	    {
	      rhs = new_rhs;
	      rhstype = വൃക്ഷം_TYPE (rhs);
	      coder = വൃക്ഷം_CODE (rhstype);
	      ttr = വൃക്ഷം_TYPE (rhstype);
	      mvr = TYPE_MAIN_VARIANT (ttr);
	    }
	}

      /* C++ does not allow the implicit conversion void* -> T*.  However,
	 for the purpose of reducing the number of false positives, we
	 tolerate the special case of

		int *p = NULL;

	 where NULL is typically defined in C to be '(void *) 0'.  */
      എങ്കിൽ (VOID_TYPE_P (ttr) && rhs != null_pointer_കണ്ണി && !VOID_TYPE_P (ttl))
	warning_at (errtype == ic_argpass ? വ്യഞ്ജകം_loc : location,
		    OPT_Wc___compat,
		    "request for implicit conversion "
		    "from %qT to %qT not permitted in C++", rhstype, type);

      /* Warn of new allocations that are not big enough for the target
	 type.  */
      എങ്കിൽ (warn_alloc_size && വൃക്ഷം_CODE (rhs) == CALL_വ്യഞ്ജകം)
	എങ്കിൽ (വൃക്ഷം fndecl = get_callee_fndecl (rhs))
	  എങ്കിൽ (DECL_IS_MALLOC (fndecl))
	    {
	      വൃക്ഷം attrs = TYPE_ATTRIBUTES (വൃക്ഷം_TYPE (fndecl));
	      വൃക്ഷം alloc_size = lookup_attribute ("alloc_size", attrs);
	      എങ്കിൽ (alloc_size)
		warn_for_alloc_size (location, ttl, rhs, alloc_size);
	    }

      /* See if the pointers point to incompatible address spaces.  */
      asl = TYPE_ADDR_SPACE (ttl);
      asr = TYPE_ADDR_SPACE (ttr);
      എങ്കിൽ (!null_pointer_constant_p (rhs)
	  && asr != asl && !targetm.addr_space.subset_p (asr, asl))
	{
	  auto_diagnostic_group d;
	  തർക്കം diagnosed = സത്യം;
	  തിരഞ്ഞെടുപ്പ് (errtype)
	    {
	    അവസ്ഥ ic_argpass:
	      {
		സ്ഥിരം അക്ഷരം സന്ദേശം[] = G_("passing argument %d of %qE from "
				      "pointer to non-enclosed address space");
		എങ്കിൽ (warnopt)
		  diagnosed
		    = warning_at (വ്യഞ്ജകം_loc, warnopt, സന്ദേശം, parmnum, rname);
		അല്ലെങ്കിൽ
		  error_at (വ്യഞ്ജകം_loc, സന്ദേശം, parmnum, rname);
	      നിർത്തുക;
	      }
	    അവസ്ഥ ic_assign:
	      {
		സ്ഥിരം അക്ഷരം സന്ദേശം[] = G_("assignment from pointer to "
				      "non-enclosed address space");
		എങ്കിൽ (warnopt)
		  diagnosed = warning_at (location, warnopt, സന്ദേശം);
		അല്ലെങ്കിൽ
		  error_at (location, സന്ദേശം);
		നിർത്തുക;
	      }
	    അവസ്ഥ ic_init:
	    അവസ്ഥ ic_init_const:
	      {
		സ്ഥിരം അക്ഷരം സന്ദേശം[] = G_("initialization from pointer to "
				      "non-enclosed address space");
		എങ്കിൽ (warnopt)
		  diagnosed = warning_at (location, warnopt, സന്ദേശം);
		അല്ലെങ്കിൽ
		  error_at (location, സന്ദേശം);
		നിർത്തുക;
	      }
	    അവസ്ഥ ic_return:
	      {
		സ്ഥിരം അക്ഷരം സന്ദേശം[] = G_("return from pointer to "
				      "non-enclosed address space");
		എങ്കിൽ (warnopt)
		  diagnosed = warning_at (location, warnopt, സന്ദേശം);
		അല്ലെങ്കിൽ
		  error_at (location, സന്ദേശം);
		നിർത്തുക;
	      }
	    സ്ഥിരസ്ഥിതി:
	      gcc_unreachable ();
	    }
	  എങ്കിൽ (diagnosed)
	    {
	      എങ്കിൽ (errtype == ic_argpass)
		inform_for_arg (fundecl, വ്യഞ്ജകം_loc, parmnum, type, rhstype);
	      അല്ലെങ്കിൽ
		inform (location, "expected %qT but pointer is of type %qT",
			type, rhstype);
	    }
	  തിരികെ error_mark_കണ്ണി;
	}

      /* Check if the right-hand side has a format attribute but the
	 left-hand side doesn't.  */
      എങ്കിൽ (warn_suggest_attribute_format
	  && check_missing_format_attribute (type, rhstype))
	{
	  തിരഞ്ഞെടുപ്പ് (errtype)
	  {
	  അവസ്ഥ ic_argpass:
	    warning_at (വ്യഞ്ജകം_loc, OPT_Wsuggest_attribute_format,
			"argument %d of %qE might be "
			"a candidate for a format attribute",
			parmnum, rname);
	    നിർത്തുക;
	  അവസ്ഥ ic_assign:
	    warning_at (location, OPT_Wsuggest_attribute_format,
			"assignment left-hand side might be "
			"a candidate for a format attribute");
	    നിർത്തുക;
	  അവസ്ഥ ic_init:
	  അവസ്ഥ ic_init_const:
	    warning_at (location, OPT_Wsuggest_attribute_format,
			"initialization left-hand side might be "
			"a candidate for a format attribute");
	    നിർത്തുക;
	  അവസ്ഥ ic_return:
	    warning_at (location, OPT_Wsuggest_attribute_format,
			"return type might be "
			"a candidate for a format attribute");
	    നിർത്തുക;
	  സ്ഥിരസ്ഥിതി:
	    gcc_unreachable ();
	  }
	}

      /* See if the pointers point to incompatible scalar storage orders.  */
      എങ്കിൽ (warn_scalar_storage_order
	  && !null_pointer_constant_p (rhs)
	  && (AGGREGATE_TYPE_P (ttl) && TYPE_REVERSE_STORAGE_ORDER (ttl))
	     != (AGGREGATE_TYPE_P (ttr) && TYPE_REVERSE_STORAGE_ORDER (ttr)))
	{
	  വൃക്ഷം t;

	  തിരഞ്ഞെടുപ്പ് (errtype)
	  {
	  അവസ്ഥ ic_argpass:
	    /* Do not warn for built-in functions, for example memcpy, since we
	       control how they behave and they can be useful in this area.  */
	    എങ്കിൽ (വൃക്ഷം_CODE (rname) != FUNCTION_DECL
		|| !fndecl_built_in_p (rname))
	      warning_at (location, OPT_Wscalar_storage_order,
			  "passing argument %d of %qE from incompatible "
			  "scalar storage order", parmnum, rname);
	    നിർത്തുക;
	  അവസ്ഥ ic_assign:
	    /* Do not warn if the RHS is a call to a function that returns a
	       pointer that is not an alias.  */
	    എങ്കിൽ (വൃക്ഷം_CODE (rhs) != CALL_വ്യഞ്ജകം
		|| (t = get_callee_fndecl (rhs)) == NULL_വൃക്ഷം
		|| !DECL_IS_MALLOC (t))
	      warning_at (location, OPT_Wscalar_storage_order,
			  "assignment to %qT from pointer type %qT with "
			  "incompatible scalar storage order", type, rhstype);
	    നിർത്തുക;
	  അവസ്ഥ ic_init:
	  അവസ്ഥ ic_init_const:
	    /* Likewise.  */
	    എങ്കിൽ (വൃക്ഷം_CODE (rhs) != CALL_വ്യഞ്ജകം
		|| (t = get_callee_fndecl (rhs)) == NULL_വൃക്ഷം
		|| !DECL_IS_MALLOC (t))
	      warning_at (location, OPT_Wscalar_storage_order,
			  "initialization of %qT from pointer type %qT with "
			  "incompatible scalar storage order", type, rhstype);
	    നിർത്തുക;
	  അവസ്ഥ ic_return:
	    warning_at (location, OPT_Wscalar_storage_order,
			"returning %qT from pointer type with incompatible "
			"scalar storage order %qT", rhstype, type);
	    നിർത്തുക;
	  സ്ഥിരസ്ഥിതി:
	    gcc_unreachable ();
	  }
	}

      /* Any non-function converts to a [const][volatile] void *
	 and vice versa; otherwise, targets must be the same.
	 Meanwhile, the lhs target must have all the qualifiers of the rhs.  */
      എങ്കിൽ ((VOID_TYPE_P (ttl) && !TYPE_ATOMIC (ttl))
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
	  എങ്കിൽ (വൃക്ഷം_CODE (ttr) == ARRAY_TYPE)
	    {
	      ttr = strip_array_types (ttr);
	      ttl = strip_array_types (ttl);

	      എങ്കിൽ (TYPE_QUALS_NO_ADDR_SPACE_NO_ATOMIC (ttr)
		  & ~TYPE_QUALS_NO_ADDR_SPACE_NO_ATOMIC (ttl))
		WARNING_FOR_QUALIFIERS (flag_isoc23,
					location, വ്യഞ്ജകം_loc,
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
          അല്ലെങ്കിൽ എങ്കിൽ (pedantic
	      && ((VOID_TYPE_P (ttl) && വൃക്ഷം_CODE (ttr) == FUNCTION_TYPE)
		  ||
		  (VOID_TYPE_P (ttr)
		   && !null_pointer_constant
		   && വൃക്ഷം_CODE (ttl) == FUNCTION_TYPE)))
	    PEDWARN_FOR_ASSIGNMENT (location, വ്യഞ്ജകം_loc, OPT_Wpedantic,
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
	  അല്ലെങ്കിൽ എങ്കിൽ (വൃക്ഷം_CODE (ttr) != FUNCTION_TYPE
		   && വൃക്ഷം_CODE (ttl) != FUNCTION_TYPE)
	    {
	       /* Assignments between atomic and non-atomic objects are OK.  */
	       തർക്കം warn_quals_ped = TYPE_QUALS_NO_ADDR_SPACE_NO_ATOMIC (ttr)
				     & ~TYPE_QUALS_NO_ADDR_SPACE_NO_ATOMIC (ttl);
	       തർക്കം warn_quals = TYPE_QUALS_NO_ADDR_SPACE_NO_ATOMIC (ttr)
				 & ~TYPE_QUALS_NO_ADDR_SPACE_NO_ATOMIC (strip_array_types (ttl));

	      /* Don't warn about loss of qualifier for conversions from
		 qualified void* to pointers to arrays with corresponding
		 qualifier on the element type (except for pedantic before C23). */
	      എങ്കിൽ (warn_quals || (warn_quals_ped && pedantic && !flag_isoc23))
		PEDWARN_FOR_QUALIFIERS (location, വ്യഞ്ജകം_loc,
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
	      അല്ലെങ്കിൽ എങ്കിൽ (warn_quals_ped)
		pedwarn_c11 (location, OPT_Wc11_c23_compat,
			     "array with qualifier on the element is not qualified before C23");

	      /* If this is not a case of ignoring a mismatch in signedness,
		 no warning.  */
	      അല്ലെങ്കിൽ എങ്കിൽ (VOID_TYPE_P (ttl) || VOID_TYPE_P (ttr)
		       || target_cmp)
		;
	      /* If there is a mismatch, do warn.  */
	      അല്ലെങ്കിൽ എങ്കിൽ (warn_pointer_sign)
		തിരഞ്ഞെടുപ്പ് (errtype)
		  {
		  അവസ്ഥ ic_argpass:
		    {
		      auto_diagnostic_group d;
		      range_label_for_type_mismatch rhs_label (rhstype, type);
		      gcc_rich_location richloc (വ്യഞ്ജകം_loc, &rhs_label,
						 highlight_colors::actual);
		      എങ്കിൽ (pedwarn (&richloc, OPT_Wpointer_sign,
				   "pointer targets in passing argument %d of "
				   "%qE differ in signedness", parmnum, rname))
			inform_for_arg (fundecl, വ്യഞ്ജകം_loc, parmnum, type,
					rhstype);
		    }
		    നിർത്തുക;
		  അവസ്ഥ ic_assign:
		    pedwarn (location, OPT_Wpointer_sign,
			     "pointer targets in assignment from %qT to %qT "
			     "differ in signedness", rhstype, type);
		    നിർത്തുക;
		  അവസ്ഥ ic_init:
		  അവസ്ഥ ic_init_const:
		    pedwarn_init (location, OPT_Wpointer_sign,
				  "pointer targets in initialization of %qT "
				  "from %qT differ in signedness", type,
				  rhstype);
		    നിർത്തുക;
		  അവസ്ഥ ic_return:
		    pedwarn (location, OPT_Wpointer_sign, "pointer targets in "
			     "returning %qT from a function with return type "
			     "%qT differ in signedness", rhstype, type);
		    നിർത്തുക;
		  സ്ഥിരസ്ഥിതി:
		    gcc_unreachable ();
		  }
	    }
	  അല്ലെങ്കിൽ എങ്കിൽ (വൃക്ഷം_CODE (ttl) == FUNCTION_TYPE
		   && വൃക്ഷം_CODE (ttr) == FUNCTION_TYPE)
	    {
	      /* Because const and volatile on functions are restrictions
		 that say the function will not do certain things,
		 it is okay to use a const or volatile function
		 where an ordinary one is wanted, but not vice-versa.  */
	      എങ്കിൽ (TYPE_QUALS_NO_ADDR_SPACE (ttl)
		  & ~TYPE_QUALS_NO_ADDR_SPACE (ttr))
		PEDWARN_FOR_QUALIFIERS (location, വ്യഞ്ജകം_loc,
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
      അല്ലെങ്കിൽ എങ്കിൽ (!objc_ok)
	{
	  auto_diagnostic_group d;
	  തർക്കം warned = അസത്യം;
	  pp_markup::element_expected_type e_type (type);
	  pp_markup::element_actual_type e_rhstype (rhstype);
	  തിരഞ്ഞെടുപ്പ് (errtype)
	    {
	    അവസ്ഥ ic_argpass:
	      {
		range_label_for_type_mismatch rhs_label (rhstype, type);
		gcc_rich_location richloc (വ്യഞ്ജകം_loc, &rhs_label,
					   highlight_colors::actual);
		warned
		  = permerror_opt (&richloc, OPT_Wincompatible_pointer_types,
				   "passing argument %d of %qE from "
				   "incompatible pointer type",
				   parmnum, rname);
		എങ്കിൽ (warned)
		  inform_for_arg (fundecl, വ്യഞ്ജകം_loc, parmnum, type, rhstype);
	      }
	      നിർത്തുക;
	    അവസ്ഥ ic_assign:
	      എങ്കിൽ (bltin)
		warned
		  = permerror_opt (location, OPT_Wincompatible_pointer_types,
				   "assignment to %e from pointer to "
				   "%qD with incompatible type %e",
				   &e_type, bltin, &e_rhstype);
	      അല്ലെങ്കിൽ
		warned
		  = permerror_opt (location, OPT_Wincompatible_pointer_types,
				   "assignment to %e from incompatible "
				   "pointer type %e",
				   &e_type, &e_rhstype);
	      നിർത്തുക;
	    അവസ്ഥ ic_init:
	    അവസ്ഥ ic_init_const:
	      എങ്കിൽ (bltin)
		warned
		  = permerror_init (location, OPT_Wincompatible_pointer_types,
				    "initialization of %e from pointer to "
				    "%qD with incompatible type %e",
				    &e_type, bltin, &e_rhstype);
	      അല്ലെങ്കിൽ
		warned
		  = permerror_init (location, OPT_Wincompatible_pointer_types,
				    "initialization of %e from incompatible "
				    "pointer type %e",
				    &e_type, &e_rhstype);
	      നിർത്തുക;
	    അവസ്ഥ ic_return:
	      എങ്കിൽ (bltin)
		warned
		  = permerror_opt (location, OPT_Wincompatible_pointer_types,
				   "returning pointer to %qD of type %e from "
				   "a function with incompatible type %e",
				   bltin, &e_rhstype, &e_type);
	      അല്ലെങ്കിൽ
		warned
		  = permerror_opt (location, OPT_Wincompatible_pointer_types,
				   "returning %e from a function with "
				   "incompatible return type %e",
				   &e_rhstype, &e_type);
	      നിർത്തുക;
	    സ്ഥിരസ്ഥിതി:
	      gcc_unreachable ();
	    }
	  എങ്കിൽ (warned)
	    {
	      /* If the mismatching function type is a pointer to a function,
		 try to show the decl of the function.  */
	      എങ്കിൽ (വൃക്ഷം_CODE (rhs) == ADDR_വ്യഞ്ജകം
		  && വൃക്ഷം_CODE (വൃക്ഷം_OPERAND (rhs, 0)) == FUNCTION_DECL)
		{
		  വൃക്ഷം rhs_fndecl = വൃക്ഷം_OPERAND (rhs, 0);
		  എങ്കിൽ (!DECL_IS_UNDECLARED_BUILTIN (rhs_fndecl))
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

      തിരികെ convert (type, rhs);
    }
  അല്ലെങ്കിൽ എങ്കിൽ (codel == POINTER_TYPE && coder == ARRAY_TYPE)
    {
      /* ??? This should not be an error when inlining calls to
	 unprototyped functions.  */
      സ്ഥിരം അക്ഷരം സന്ദേശം[] = "invalid use of non-lvalue array";
      എങ്കിൽ (warnopt)
	warning_at (location, warnopt, സന്ദേശം);
      അല്ലെങ്കിൽ
	error_at (location, സന്ദേശം);
      തിരികെ error_mark_കണ്ണി;
    }
  അല്ലെങ്കിൽ എങ്കിൽ (codel == POINTER_TYPE
	   && (coder == INTEGER_TYPE
	       || coder == ENUMERAL_TYPE
	       || coder == BOOLEAN_TYPE
	       || coder == NULLPTR_TYPE
	       || coder == BITINT_TYPE))
    {
      എങ്കിൽ (null_pointer_constant && c_inhibit_evaluation_warnings == 0
	  && coder != NULLPTR_TYPE)
	warning_at (location, OPT_Wzero_as_null_pointer_constant,
		    "zero as null pointer constant");
      /* A NULLPTR type is just a nullptr always.  */
      എങ്കിൽ (coder == NULLPTR_TYPE)
	തിരികെ omit_one_operand_loc (വ്യഞ്ജകം_loc, type, nullptr_കണ്ണി, rhs);
      /* An explicit constant 0 or type nullptr_t can convert to a pointer,
	 or one that results from arithmetic, even including a cast to
	 integer type.  */
      അല്ലെങ്കിൽ എങ്കിൽ (!null_pointer_constant)
	തിരഞ്ഞെടുപ്പ് (errtype)
	  {
	  അവസ്ഥ ic_argpass:
	    {
	      auto_diagnostic_group d;
	      range_label_for_type_mismatch rhs_label (rhstype, type);
	      gcc_rich_location richloc (വ്യഞ്ജകം_loc, &rhs_label,
					 highlight_colors::actual);
	      എങ്കിൽ (permerror_opt (&richloc, OPT_Wint_conversion,
				 "passing argument %d of %qE makes pointer "
				 "from integer without a cast", parmnum, rname))
		{
		  maybe_emit_indirection_note (വ്യഞ്ജകം_loc, rhs, type);
		  inform_for_arg (fundecl, വ്യഞ്ജകം_loc, parmnum, type, rhstype);
		}
	    }
	    നിർത്തുക;
	  അവസ്ഥ ic_assign:
	    permerror_opt (location, OPT_Wint_conversion,
			   "assignment to %qT from %qT makes pointer from "
			   "integer without a cast", type, rhstype);
	    നിർത്തുക;
	  അവസ്ഥ ic_init:
	  അവസ്ഥ ic_init_const:
	    permerror_init (location, OPT_Wint_conversion,
			    "initialization of %qT from %qT makes pointer "
			    "from integer without a cast", type, rhstype);
	    നിർത്തുക;
	  അവസ്ഥ ic_return:
	    permerror_init (location, OPT_Wint_conversion,
			    "returning %qT from a function with return type "
			    "%qT makes pointer from integer without a cast",
			    rhstype, type);
	    നിർത്തുക;
	  സ്ഥിരസ്ഥിതി:
	    gcc_unreachable ();
	  }

      തിരികെ convert (type, rhs);
    }
  അല്ലെങ്കിൽ എങ്കിൽ ((codel == INTEGER_TYPE || codel == BITINT_TYPE)
	   && coder == POINTER_TYPE)
    {
      തിരഞ്ഞെടുപ്പ് (errtype)
	{
	അവസ്ഥ ic_argpass:
	  {
	    auto_diagnostic_group d;
	    range_label_for_type_mismatch rhs_label (rhstype, type);
	    gcc_rich_location richloc (വ്യഞ്ജകം_loc, &rhs_label,
				       highlight_colors::actual);
	    എങ്കിൽ (permerror_opt (&richloc, OPT_Wint_conversion,
			       "passing argument %d of %qE makes integer from "
			       "pointer without a cast", parmnum, rname))
	      {
		maybe_emit_indirection_note (വ്യഞ്ജകം_loc, rhs, type);
		inform_for_arg (fundecl, വ്യഞ്ജകം_loc, parmnum, type, rhstype);
	      }
	  }
	  നിർത്തുക;
	അവസ്ഥ ic_assign:
	  permerror_opt (location, OPT_Wint_conversion,
			 "assignment to %qT from %qT makes integer from "
			 "pointer without a cast", type, rhstype);
	  നിർത്തുക;
	അവസ്ഥ ic_init:
	അവസ്ഥ ic_init_const:
	  permerror_init (location, OPT_Wint_conversion,
			  "initialization of %qT from %qT makes integer "
			  "from pointer without a cast", type, rhstype);
	  നിർത്തുക;
	അവസ്ഥ ic_return:
	  permerror_opt (location, OPT_Wint_conversion, "returning %qT from a "
			 "function with return type %qT makes integer from "
			 "pointer without a cast", rhstype, type);
	  നിർത്തുക;
	സ്ഥിരസ്ഥിതി:
	  gcc_unreachable ();
	}

      തിരികെ convert (type, rhs);
    }
  അല്ലെങ്കിൽ എങ്കിൽ (C_BOOLEAN_TYPE_P (type)
	   /* The type nullptr_t may be converted to bool.  The
	      result is false.  */
	   && (coder == POINTER_TYPE || coder == NULLPTR_TYPE))
    {
      വൃക്ഷം ret;
      തർക്കം save = in_late_ദ്വിമാന_op;
      in_late_ദ്വിമാന_op = സത്യം;
      ret = convert (type, rhs);
      in_late_ദ്വിമാന_op = save;
      തിരികെ ret;
    }
  അല്ലെങ്കിൽ എങ്കിൽ (codel == NULLPTR_TYPE && null_pointer_constant)
    തിരികെ convert (type, rhs);

  തിരഞ്ഞെടുപ്പ് (errtype)
    {
    അവസ്ഥ ic_argpass:
      {
	auto_diagnostic_group d;
	range_label_for_type_mismatch rhs_label (rhstype, type);
	gcc_rich_location richloc (വ്യഞ്ജകം_loc, &rhs_label,
				   highlight_colors::actual);
	സ്ഥിരം അക്ഷരം സന്ദേശം[] = G_("incompatible type for argument %d of %qE");
	എങ്കിൽ (warnopt)
	  warning_at (വ്യഞ്ജകം_loc, warnopt, സന്ദേശം, parmnum, rname);
	അല്ലെങ്കിൽ
	  error_at (&richloc, സന്ദേശം, parmnum, rname);
	inform_for_arg (fundecl, വ്യഞ്ജകം_loc, parmnum, type, rhstype);
      }
      നിർത്തുക;
    അവസ്ഥ ic_assign:
      {
	സ്ഥിരം അക്ഷരം സന്ദേശം[]
	  = G_("incompatible types when assigning to type %qT from type %qT");
	എങ്കിൽ (warnopt)
	  warning_at (വ്യഞ്ജകം_loc, 0, സന്ദേശം, type, rhstype);
	അല്ലെങ്കിൽ
	  error_at (വ്യഞ്ജകം_loc, സന്ദേശം, type, rhstype);
	നിർത്തുക;
      }
    അവസ്ഥ ic_init:
    അവസ്ഥ ic_init_const:
      {
	സ്ഥിരം അക്ഷരം സന്ദേശം[]
	  = G_("incompatible types when initializing type %qT using type %qT");
	എങ്കിൽ (warnopt)
	  warning_at (location, 0, സന്ദേശം, type, rhstype);
	അല്ലെങ്കിൽ
	  error_at (location, സന്ദേശം, type, rhstype);
	നിർത്തുക;
      }
    അവസ്ഥ ic_return:
      {
	സ്ഥിരം അക്ഷരം സന്ദേശം[]
	  = G_("incompatible types when returning type %qT but %qT was expected");
	എങ്കിൽ (warnopt)
	  warning_at (location, 0, സന്ദേശം, rhstype, type);
	അല്ലെങ്കിൽ
	  error_at (location, സന്ദേശം, rhstype, type);
	നിർത്തുക;
      }
    സ്ഥിരസ്ഥിതി:
      gcc_unreachable ();
    }

  തിരികെ error_mark_കണ്ണി;
}

/* If VALUE is a compound expr all of whose expressions are constant, then
   return its value.  Otherwise, return error_mark_node.

   This is for handling COMPOUND_EXPRs as initializer elements
   which is allowed with a warning when -pedantic is specified.  */

സ്ഥിതം വൃക്ഷം
valid_compound_വ്യഞ്ജകം_initializer (വൃക്ഷം മൂല്യം, വൃക്ഷം endtype)
{
  എങ്കിൽ (വൃക്ഷം_CODE (മൂല്യം) == COMPOUND_വ്യഞ്ജകം)
    {
      എങ്കിൽ (valid_compound_വ്യഞ്ജകം_initializer (വൃക്ഷം_OPERAND (മൂല്യം, 0), endtype)
	  == error_mark_കണ്ണി)
	തിരികെ error_mark_കണ്ണി;
      തിരികെ valid_compound_വ്യഞ്ജകം_initializer (വൃക്ഷം_OPERAND (മൂല്യം, 1),
					      endtype);
    }
  അല്ലെങ്കിൽ എങ്കിൽ (!initializer_constant_valid_p (മൂല്യം, endtype))
    തിരികെ error_mark_കണ്ണി;
  അല്ലെങ്കിൽ
    തിരികെ മൂല്യം;
}

/* Perform appropriate conversions on the initial value of a variable,
   store it in the declaration DECL,
   and print any error messages that are appropriate.
   If ORIGTYPE is not NULL_TREE, it is the original type of INIT.
   If the init is invalid, store an ERROR_MARK.

   INIT_LOC is the location of the initial value.  */

ശൂന്യം
store_init_മൂല്യം (location_t init_loc, വൃക്ഷം decl, വൃക്ഷം init, വൃക്ഷം origtype)
{
  വൃക്ഷം മൂല്യം, type;
  തർക്കം npc = അസത്യം;
  തർക്കം int_const_വ്യഞ്ജകം = അസത്യം;
  തർക്കം arith_const_വ്യഞ്ജകം = അസത്യം;

  /* If variable's type was invalidly declared, just ignore it.  */

  type = വൃക്ഷം_TYPE (decl);
  എങ്കിൽ (വൃക്ഷം_CODE (type) == ERROR_MARK)
    തിരികെ;

  /* Digest the specified initializer into an expression.  */

  എങ്കിൽ (init)
    {
      npc = null_pointer_constant_p (init);
      int_const_വ്യഞ്ജകം = (വൃക്ഷം_CODE (init) == INTEGER_CST
			&& !വൃക്ഷം_OVERFLOW (init)
			&& INTEGRAL_TYPE_P (വൃക്ഷം_TYPE (init)));
      /* Not fully determined before folding.  */
      arith_const_വ്യഞ്ജകം = സത്യം;
    }
  തർക്കം constexpr_p = (VAR_P (decl)
		      && C_DECL_DECLARED_CONSTEXPR (decl));
  മൂല്യം = digest_init (init_loc, decl, type, init, origtype, npc,
		       int_const_വ്യഞ്ജകം, arith_const_വ്യഞ്ജകം, സത്യം,
		       വൃക്ഷം_STATIC (decl) || constexpr_p, constexpr_p);

  /* Store the expression if valid; else report error.  */

  എങ്കിൽ (!in_system_header_at (നിവേശം_location)
      && AGGREGATE_TYPE_P (വൃക്ഷം_TYPE (decl)) && !വൃക്ഷം_STATIC (decl))
    warning (OPT_Wtraditional, "traditional C rejects automatic "
	     "aggregate initialization");

  എങ്കിൽ (മൂല്യം != error_mark_കണ്ണി || വൃക്ഷം_CODE (decl) != FUNCTION_DECL)
    DECL_INITIAL (decl) = മൂല്യം;

  /* ANSI wants warnings about out-of-range constant initializers.  */
  STRIP_TYPE_NOPS (മൂല്യം);
  എങ്കിൽ (വൃക്ഷം_STATIC (decl))
    constant_expression_warning (മൂല്യം);

  /* Check if we need to set array size from compound literal size.  */
  എങ്കിൽ (വൃക്ഷം_CODE (type) == ARRAY_TYPE
      && TYPE_DOMAIN (type) == NULL_വൃക്ഷം
      && മൂല്യം != error_mark_കണ്ണി)
    {
      വൃക്ഷം inside_init = init;

      STRIP_TYPE_NOPS (inside_init);
      inside_init = fold (inside_init);

      എങ്കിൽ (വൃക്ഷം_CODE (inside_init) == COMPOUND_LITERAL_വ്യഞ്ജകം)
	{
	  വൃക്ഷം cldecl = COMPOUND_LITERAL_വ്യഞ്ജകം_DECL (inside_init);

	  എങ്കിൽ (TYPE_DOMAIN (വൃക്ഷം_TYPE (cldecl)))
	    {
	      /* For int foo[] = (int [3]){1}; we need to set array size
		 now since later on array initializer will be just the
		 brace enclosed list of the compound literal.  */
	      വൃക്ഷം etype = strip_array_types (വൃക്ഷം_TYPE (decl));
	      type = build_distinct_type_copy (TYPE_MAIN_VARIANT (type));
	      TYPE_DOMAIN (type) = TYPE_DOMAIN (വൃക്ഷം_TYPE (cldecl));
	      layout_type (type);
	      layout_decl (cldecl, 0);
	      വൃക്ഷം_TYPE (decl)
		= c_build_qualified_type (type, TYPE_QUALS (etype));
	    }
	}
    }
}

/* Methods for storing and printing names for error messages.  */

/* Implement a spelling stack that allows components of a name to be pushed
   and popped.  Each element on the stack is this structure.  */

ഘടന spelling
{
  പൂർണ്ണസംഖ്യ kind;
  സംഘം
    {
      unsigned HOST_WIDE_INT i;
      സ്ഥിരം അക്ഷരം *s;
    } u;
};

#define SPELLING_STRING 1
#define SPELLING_MEMBER 2
#define SPELLING_BOUNDS 3

സ്ഥിതം ഘടന spelling *spelling;	/* Next stack element (unused).  */
സ്ഥിതം ഘടന spelling *spelling_base;	/* Spelling stack base.  */
സ്ഥിതം പൂർണ്ണസംഖ്യ spelling_size;		/* Size of the spelling stack.  */

/* Macros to save and restore the spelling stack around push_... functions.
   Alternative to SAVE_SPELLING_STACK.  */

#define SPELLING_DEPTH() (spelling - spelling_base)
#define RESTORE_SPELLING_DEPTH(DEPTH) (spelling = spelling_base + (DEPTH))

/* Push an element on the spelling stack with type KIND and assign VALUE
   to MEMBER.  */

#define തള്ളുക_SPELLING(KIND, മൂല്യം_2, MEMBER)				\
{									\
  പൂർണ്ണസംഖ്യ depth = SPELLING_DEPTH ();					\
									\
  എങ്കിൽ (depth >= spelling_size)						\
    {									\
      spelling_size += 10;						\
      spelling_base = XRESIZEVEC (ഘടന spelling, spelling_base,	\
				  spelling_size);			\
      RESTORE_SPELLING_DEPTH (depth);					\
    }									\
									\
  spelling->kind = (KIND);						\
  spelling->MEMBER = (മൂല്യം_2);						\
  spelling++;								\
}

/* Push STRING on the stack.  Printed literally.  */

സ്ഥിതം ശൂന്യം
തള്ളുക_string (സ്ഥിരം അക്ഷരം *string)
{
  തള്ളുക_SPELLING (SPELLING_STRING, string, u.s);
}

/* Push a member name on the stack.  Printed as '.' STRING.  */

സ്ഥിതം ശൂന്യം
തള്ളുക_member_name (വൃക്ഷം decl)
{
  സ്ഥിരം അക്ഷരം *സ്ഥിരം string
    = (DECL_NAME (decl)
       ? identifier_to_locale (IDENTIFIER_POINTER (DECL_NAME (decl)))
       : _("<anonymous>"));
  തള്ളുക_SPELLING (SPELLING_MEMBER, string, u.s);
}

/* Push an array bounds on the stack.  Printed as [BOUNDS].  */

സ്ഥിതം ശൂന്യം
തള്ളുക_array_bounds (unsigned HOST_WIDE_INT bounds)
{
  തള്ളുക_SPELLING (SPELLING_BOUNDS, bounds, u.i);
}

/* Compute the maximum size in bytes of the printed spelling.  */

സ്ഥിതം പൂർണ്ണസംഖ്യ
spelling_length (ശൂന്യം)
{
  പൂർണ്ണസംഖ്യ size = 0;
  ഘടന spelling *p;

  വേണ്ടി (p = spelling_base; p < spelling; p++)
    {
      എങ്കിൽ (p->kind == SPELLING_BOUNDS)
	size += 25;
      അല്ലെങ്കിൽ
	size += strlen (p->u.s) + 1;
    }

  തിരികെ size;
}

/* Print the spelling to BUFFER and return it.  */

സ്ഥിതം അക്ഷരം *
print_spelling (അക്ഷരം *buffer)
{
  അക്ഷരം *d = buffer;
  ഘടന spelling *p;

  വേണ്ടി (p = spelling_base; p < spelling; p++)
    എങ്കിൽ (p->kind == SPELLING_BOUNDS)
      {
	sprintf (d, "[" HOST_WIDE_INT_PRINT_UNSIGNED "]", p->u.i);
	d += strlen (d);
      }
    അല്ലെങ്കിൽ
      {
	സ്ഥിരം അക്ഷരം *s;
	എങ്കിൽ (p->kind == SPELLING_MEMBER)
	  *d++ = '.';
	വേണ്ടി (s = p->u.s; (*d = *s++); d++)
	  ;
      }
  *d++ = '\0';
  തിരികെ buffer;
}

/* Check whether INIT, a floating or integer constant, is
   representable in TYPE, a real floating type with the same radix or
   a decimal floating type initialized with a binary floating
   constant.  Return true if OK, false if not.  */
സ്ഥിതം തർക്കം
constexpr_init_fits_real_type (വൃക്ഷം type, വൃക്ഷം init)
{
  gcc_assert (SCALAR_FLOAT_TYPE_P (type));
  gcc_assert (വൃക്ഷം_CODE (init) == INTEGER_CST || വൃക്ഷം_CODE (init) == REAL_CST);
  എങ്കിൽ (വൃക്ഷം_CODE (init) == REAL_CST
      && TYPE_MODE (വൃക്ഷം_TYPE (init)) == TYPE_MODE (type))
    {
      /* Same mode, no conversion required except for the case of
	 signaling NaNs if the types are incompatible (e.g. double and
	 long double with the same mode).  */
      എങ്കിൽ (REAL_മൂല്യം_ISSIGNALING_NAN (വൃക്ഷം_REAL_CST (init))
	  && !comptypes (TYPE_MAIN_VARIANT (type),
			 TYPE_MAIN_VARIANT (വൃക്ഷം_TYPE (init))))
	തിരികെ അസത്യം;
      തിരികെ സത്യം;
    }
  എങ്കിൽ (വൃക്ഷം_CODE (init) == INTEGER_CST)
    {
      വൃക്ഷം converted = build_real_from_int_cst (type, init);
      തർക്കം fail = അസത്യം;
      wide_int w = real_to_integer (&വൃക്ഷം_REAL_CST (converted), &fail,
				    TYPE_PRECISION (വൃക്ഷം_TYPE (init)));
      തിരികെ !fail && wi::eq_p (w, wi::to_wide (init));
    }
  എങ്കിൽ (REAL_മൂല്യം_ISSIGNALING_NAN (വൃക്ഷം_REAL_CST (init)))
    തിരികെ അസത്യം;
  എങ്കിൽ ((REAL_മൂല്യം_ISINF (വൃക്ഷം_REAL_CST (init))
       && MODE_HAS_INFINITIES (TYPE_MODE (type)))
      || (REAL_മൂല്യം_ISNAN (വൃക്ഷം_REAL_CST (init))
	  && MODE_HAS_NANS (TYPE_MODE (type))))
    തിരികെ സത്യം;
  എങ്കിൽ (DECIMAL_FLOAT_TYPE_P (type)
      && !DECIMAL_FLOAT_TYPE_P (വൃക്ഷം_TYPE (init)))
    {
      /* This is valid if the real number represented by the
	 initializer can be exactly represented in the decimal
	 type.  Compare the values using MPFR.  */
      REAL_മൂല്യം_TYPE t;
      real_convert (&t, TYPE_MODE (type), &വൃക്ഷം_REAL_CST (init));
      mpfr_t bin_val, dec_val;
      mpfr_init2 (bin_val, REAL_MODE_FORMAT (TYPE_MODE (വൃക്ഷം_TYPE (init)))->p);
      mpfr_init2 (dec_val, REAL_MODE_FORMAT (TYPE_MODE (വൃക്ഷം_TYPE (init)))->p);
      mpfr_from_real (bin_val, &വൃക്ഷം_REAL_CST (init), MPFR_RNDN);
      അക്ഷരം string[256];
      real_to_decimal (string, &t, വലുപ്പം string, 0, 1);
      തർക്കം res = (mpfr_strtofr (dec_val, string, ശൂന്യ, 10, MPFR_RNDN) == 0
		  && mpfr_equal_p (bin_val, dec_val));
      mpfr_clear (bin_val);
      mpfr_clear (dec_val);
      തിരികെ res;
    }
  /* exact_real_truncate is not quite right here, since it doesn't
     allow even an exact conversion to subnormal values.  */
  REAL_മൂല്യം_TYPE t;
  real_convert (&t, TYPE_MODE (type), &വൃക്ഷം_REAL_CST (init));
  തിരികെ real_identical (&t, &വൃക്ഷം_REAL_CST (init));
}

/* Check whether INIT (location LOC) is valid as a 'constexpr'
   initializer for type TYPE, and give an error if not.  INIT has
   already been folded and verified to be constant.  INT_CONST_EXPR
   and ARITH_CONST_EXPR say whether it is an integer constant
   expression or arithmetic constant expression, respectively.  If
   TYPE is not a scalar type, this function does nothing.  */

സ്ഥിതം ശൂന്യം
check_constexpr_init (location_t loc, വൃക്ഷം type, വൃക്ഷം init,
		      തർക്കം int_const_വ്യഞ്ജകം, തർക്കം arith_const_വ്യഞ്ജകം)
{
  എങ്കിൽ (POINTER_TYPE_P (type))
    {
      /* The initializer must be null.  */
      എങ്കിൽ (വൃക്ഷം_CODE (init) != INTEGER_CST || !integer_zerop (init))
	error_at (loc, "%<constexpr%> pointer initializer is not null");
      തിരികെ;
    }
  എങ്കിൽ (INTEGRAL_TYPE_P (type))
    {
      /* The initializer must be an integer constant expression,
	 representable in the target type.  */
      എങ്കിൽ (!int_const_വ്യഞ്ജകം)
	{
	  എങ്കിൽ (വൃക്ഷം_CODE (init) == RAW_DATA_CST
	      && TYPE_PRECISION (type) == CHAR_BIT)
	    {
	      എങ്കിൽ (!TYPE_UNSIGNED (type))
		വേണ്ടി (unsigned പൂർണ്ണസംഖ്യ i = 0;
		     i < (unsigned) RAW_DATA_LENGTH (init); ++i)
		  എങ്കിൽ (RAW_DATA_SCHAR_ELT (init, i) < 0)
		    {
		      error_at (loc, "%<constexpr%> initializer not "
				"representable in type of object");
		      നിർത്തുക;
		    }
	    }
	  അല്ലെങ്കിൽ
	    error_at (loc, "%<constexpr%> integer initializer is not an "
		      "integer constant expression");
	}
      അല്ലെങ്കിൽ എങ്കിൽ (!int_fits_type_p (init, type))
	error_at (loc, "%<constexpr%> initializer not representable in "
		  "type of object");
      തിരികെ;
    }
  /* We don't apply any extra checks to extension types such as vector
     or fixed-point types.  */
  എങ്കിൽ (വൃക്ഷം_CODE (type) != REAL_TYPE && വൃക്ഷം_CODE (type) != COMPLEX_TYPE)
    തിരികെ;
  എങ്കിൽ (!arith_const_വ്യഞ്ജകം)
    {
      error_at (loc, "%<constexpr%> initializer is not an arithmetic "
		"constant expression");
      തിരികെ;
    }
  /* We don't apply any extra checks to complex integers.  */
  എങ്കിൽ (വൃക്ഷം_CODE (type) == COMPLEX_TYPE
      && വൃക്ഷം_CODE (വൃക്ഷം_TYPE (type)) != REAL_TYPE)
    തിരികെ;
  /* Following N3082, a real type cannot be initialized from a complex
     type and a binary type cannot be initialized from a decimal type
     (but initializing a decimal type from a binary type is OK).
     Signaling NaN initializers are OK only if the types are
     compatible (not just the same mode); all quiet NaN and infinity
     initializations are considered to preserve the value.  */
  എങ്കിൽ (വൃക്ഷം_CODE (വൃക്ഷം_TYPE (init)) == COMPLEX_TYPE
      && SCALAR_FLOAT_TYPE_P (type))
    {
      error_at (loc, "%<constexpr%> initializer for a real type is of "
		"complex type");
      തിരികെ;
    }
  എങ്കിൽ (SCALAR_FLOAT_TYPE_P (type)
      && SCALAR_FLOAT_TYPE_P (വൃക്ഷം_TYPE (init))
      && DECIMAL_FLOAT_TYPE_P (വൃക്ഷം_TYPE (init))
      && !DECIMAL_FLOAT_TYPE_P (type))
    {
      error_at (loc, "%<constexpr%> initializer for a binary "
		"floating-point type is of decimal type");
      തിരികെ;
    }
  തർക്കം fits;
  എങ്കിൽ (വൃക്ഷം_CODE (type) == COMPLEX_TYPE)
    {
      തിരഞ്ഞെടുപ്പ് (വൃക്ഷം_CODE (init))
	{
	അവസ്ഥ INTEGER_CST:
	അവസ്ഥ REAL_CST:
	  fits = constexpr_init_fits_real_type (വൃക്ഷം_TYPE (type), init);
	  നിർത്തുക;
	അവസ്ഥ COMPLEX_CST:
	  fits = (constexpr_init_fits_real_type (വൃക്ഷം_TYPE (type),
						 വൃക്ഷം_REALPART (init))
		  && constexpr_init_fits_real_type (വൃക്ഷം_TYPE (type),
						    വൃക്ഷം_IMAGPART (init)));
	  നിർത്തുക;
	സ്ഥിരസ്ഥിതി:
	  gcc_unreachable ();
	}
    }
  അല്ലെങ്കിൽ
    fits = constexpr_init_fits_real_type (type, init);
  എങ്കിൽ (!fits)
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

സ്ഥിതം വൃക്ഷം
digest_init (location_t init_loc, വൃക്ഷം decl, വൃക്ഷം type, വൃക്ഷം init,
	     വൃക്ഷം origtype, തർക്കം null_pointer_constant, തർക്കം int_const_വ്യഞ്ജകം,
	     തർക്കം arith_const_വ്യഞ്ജകം, തർക്കം strict_string,
	     തർക്കം require_constant, തർക്കം require_constexpr)
{
  എണ്ണൽ വൃക്ഷം_code code = വൃക്ഷം_CODE (type);
  വൃക്ഷം inside_init = init;
  വൃക്ഷം semantic_type = NULL_വൃക്ഷം;
  തർക്കം maybe_const = സത്യം;

  എങ്കിൽ (type == error_mark_കണ്ണി
      || !init
      || error_operand_p (init))
    തിരികെ error_mark_കണ്ണി;

  STRIP_TYPE_NOPS (inside_init);

  /* If require_constant is TRUE,  when the initializer is a call to
     .ACCESS_WITH_SIZE, use the first argument as the initializer.
     For example:
     y = (char *) .ACCESS_WITH_SIZE ((char *) &static_annotated.c,...)
     will be converted to
     y = &static_annotated.c.  */

  എങ്കിൽ (require_constant
      && വൃക്ഷം_CODE (inside_init) == NOP_വ്യഞ്ജകം
      && വൃക്ഷം_CODE (വൃക്ഷം_OPERAND (inside_init, 0)) == CALL_വ്യഞ്ജകം
      && is_access_with_size_p (വൃക്ഷം_OPERAND (inside_init, 0)))
    inside_init
      = get_ref_from_access_with_size (വൃക്ഷം_OPERAND (inside_init, 0));

  എങ്കിൽ (!c_in_omp_for)
    {
      എങ്കിൽ (വൃക്ഷം_CODE (inside_init) == EXCESS_PRECISION_വ്യഞ്ജകം)
	{
	  semantic_type = വൃക്ഷം_TYPE (inside_init);
	  inside_init = വൃക്ഷം_OPERAND (inside_init, 0);
	}
      inside_init = c_fully_fold (inside_init, require_constant, &maybe_const);
    }
  /* TODO: this may not detect all cases of expressions folding to
     constants that are not arithmetic constant expressions.  */
  എങ്കിൽ (!maybe_const)
    arith_const_വ്യഞ്ജകം = അസത്യം;
  അല്ലെങ്കിൽ എങ്കിൽ (!INTEGRAL_TYPE_P (വൃക്ഷം_TYPE (inside_init))
	   && വൃക്ഷം_CODE (വൃക്ഷം_TYPE (inside_init)) != REAL_TYPE
	   && വൃക്ഷം_CODE (വൃക്ഷം_TYPE (inside_init)) != COMPLEX_TYPE)
    arith_const_വ്യഞ്ജകം = അസത്യം;
  അല്ലെങ്കിൽ എങ്കിൽ (വൃക്ഷം_CODE (inside_init) != INTEGER_CST
	   && വൃക്ഷം_CODE (inside_init) != REAL_CST
	   && വൃക്ഷം_CODE (inside_init) != COMPLEX_CST
	   && വൃക്ഷം_CODE (inside_init) != RAW_DATA_CST)
    arith_const_വ്യഞ്ജകം = അസത്യം;
  അല്ലെങ്കിൽ എങ്കിൽ (വൃക്ഷം_OVERFLOW (inside_init))
    arith_const_വ്യഞ്ജകം = അസത്യം;

  /* Initialization of an array of chars from a string constant
     optionally enclosed in braces.  */

  എങ്കിൽ (code == ARRAY_TYPE && inside_init
      && വൃക്ഷം_CODE (inside_init) == STRING_CST)
    {
      വൃക്ഷം typ1
	= (TYPE_ATOMIC (വൃക്ഷം_TYPE (type))
	   ? c_build_qualified_type (TYPE_MAIN_VARIANT (വൃക്ഷം_TYPE (type)),
				     TYPE_QUAL_ATOMIC)
	   : TYPE_MAIN_VARIANT (വൃക്ഷം_TYPE (type)));
      /* Note that an array could be both an array of character type
	 and an array of wchar_t if wchar_t is signed char or unsigned
	 char.  */
      തർക്കം char_array = (typ1 == char_type_കണ്ണി
			 || typ1 == signed_char_type_കണ്ണി
			 || typ1 == unsigned_char_type_കണ്ണി);
      തർക്കം wchar_array = comptypes (typ1, wchar_type_കണ്ണി);
      തർക്കം char16_array = comptypes (typ1, char16_type_കണ്ണി);
      തർക്കം char32_array = comptypes (typ1, char32_type_കണ്ണി);

      എങ്കിൽ (char_array || wchar_array || char16_array || char32_array)
	{
	  ഘടന c_വ്യഞ്ജകം വ്യഞ്ജകം;
	  വൃക്ഷം typ2 = TYPE_MAIN_VARIANT (വൃക്ഷം_TYPE (വൃക്ഷം_TYPE (inside_init)));
	  തർക്കം incompat_string_cst = അസത്യം;
	  വ്യഞ്ജകം.മൂല്യം = inside_init;
	  വ്യഞ്ജകം.original_code = (strict_string ? STRING_CST : ERROR_MARK);
	  വ്യഞ്ജകം.original_type = ശൂന്യ;
	  വ്യഞ്ജകം.m_decimal = 0;
	  maybe_warn_string_init (init_loc, type, വ്യഞ്ജകം);

	  എങ്കിൽ (flexible_array_member_type_p (type))
	    pedwarn_init (init_loc, OPT_Wpedantic,
			  "initialization of a flexible array member");

	  എങ്കിൽ (comptypes (TYPE_MAIN_VARIANT (വൃക്ഷം_TYPE (inside_init)),
			 TYPE_MAIN_VARIANT (type)))
	    തിരികെ inside_init;

	  എങ്കിൽ (char_array)
	    {
	      എങ്കിൽ (typ2 != char_type_കണ്ണി && typ2 != char8_type_കണ്ണി)
		incompat_string_cst = സത്യം;
	    }
	  അല്ലെങ്കിൽ എങ്കിൽ (!comptypes (typ1, typ2))
	    incompat_string_cst = സത്യം;

          എങ്കിൽ (incompat_string_cst)
            {
	      error_init (init_loc, "cannot initialize array of %qT from "
			  "a string literal with type array of %qT",
			  typ1, typ2);
	      തിരികെ error_mark_കണ്ണി;
            }

	  എങ്കിൽ (require_constexpr
	      && TYPE_UNSIGNED (typ1) != TYPE_UNSIGNED (typ2))
	    {
	      /* Check if all characters of the string can be
		 represented in the type of the constexpr object being
		 initialized.  */
	      unsigned HOST_WIDE_INT len = വൃക്ഷം_STRING_LENGTH (inside_init);
	      സ്ഥിരം unsigned അക്ഷരം *p =
		(സ്ഥിരം unsigned അക്ഷരം *) വൃക്ഷം_STRING_POINTER (inside_init);
	      gcc_assert (CHAR_TYPE_SIZE == 8 && CHAR_BIT == 8);
	      വേണ്ടി (unsigned i = 0; i < len; i++)
		എങ്കിൽ (p[i] > 127)
		  {
		    error_init (init_loc, "%<constexpr%> initializer not "
				"representable in type of object");
		    നിർത്തുക;
		  }
	    }

	  എങ്കിൽ (TYPE_DOMAIN (type) != NULL_വൃക്ഷം
	      && TYPE_SIZE (type) != NULL_വൃക്ഷം
	      && വൃക്ഷം_CODE (TYPE_SIZE (type)) == INTEGER_CST)
	    {
	      unsigned HOST_WIDE_INT len = വൃക്ഷം_STRING_LENGTH (inside_init);

	      എങ്കിൽ (compare_വൃക്ഷം_int (TYPE_SIZE_UNIT (type), len) < 0)
		{
		  unsigned HOST_WIDE_INT avail
		    = വൃക്ഷം_to_uhwi (TYPE_SIZE_UNIT (type));
		  unsigned unit = TYPE_PRECISION (typ1) / BITS_PER_UNIT;
		  സ്ഥിരം അക്ഷരം *p = വൃക്ഷം_STRING_POINTER (inside_init);

		  /* Construct truncated string.  */
		  inside_init = build_string (avail, p);

		  /* Subtract the size of a single (possibly wide) character
		     because it may be ok to ignore the terminating NUL char
		     that is counted in the length of the constant.  */
		  എങ്കിൽ (len - unit > avail)
		    pedwarn_init (init_loc, 0,
				  "initializer-string for array of %qT "
				  "is too long (%wu chars into %wu "
				  "available)", typ1, len, avail);
		  അല്ലെങ്കിൽ എങ്കിൽ (warn_cxx_compat)
		    warning_at (init_loc, OPT_Wc___compat,
				"initializer-string for array of %qT "
				"is too long for C++ (%wu chars into %wu "
				"available)", typ1, len, avail);
		  അല്ലെങ്കിൽ എങ്കിൽ (warn_unterminated_string_initialization
			   && get_attr_nonstring_decl (decl) == NULL_വൃക്ഷം)
		    warning_at (init_loc,
				OPT_Wunterminated_string_initialization,
				"initializer-string for array of %qT "
				"truncates NUL terminator but destination "
				"lacks %qs attribute (%wu chars into %wu "
				"available)", typ1, "nonstring", len, avail);
		}
	    }

	  വൃക്ഷം_TYPE (inside_init) = type;
	  തിരികെ inside_init;
	}
      അല്ലെങ്കിൽ എങ്കിൽ (INTEGRAL_TYPE_P (typ1))
	{
	  error_init (init_loc, "array of inappropriate type initialized "
		      "from string constant");
	  തിരികെ error_mark_കണ്ണി;
	}
    }

  /* Build a VECTOR_CST from a *constant* vector constructor.  If the
     vector constructor is not constant (e.g. {1,2,3,foo()}) then punt
     below and handle as a constructor.  */
  എങ്കിൽ (code == VECTOR_TYPE
      && VECTOR_TYPE_P (വൃക്ഷം_TYPE (inside_init))
      && vector_types_convertible_p (വൃക്ഷം_TYPE (inside_init), type, സത്യം)
      && വൃക്ഷം_CONSTANT (inside_init))
    {
      എങ്കിൽ (വൃക്ഷം_CODE (inside_init) == VECTOR_CST
	  && comptypes (TYPE_MAIN_VARIANT (വൃക്ഷം_TYPE (inside_init)),
			TYPE_MAIN_VARIANT (type)))
	തിരികെ inside_init;

      എങ്കിൽ (വൃക്ഷം_CODE (inside_init) == CONSTRUCTOR)
	{
	  unsigned HOST_WIDE_INT ix;
	  വൃക്ഷം മൂല്യം;
	  തർക്കം constant_p = സത്യം;

	  /* Iterate through elements and check if all constructor
	     elements are *_CSTs.  */
	  FOR_EACH_CONSTRUCTOR_മൂല്യം (CONSTRUCTOR_ELTS (inside_init), ix, മൂല്യം)
	    എങ്കിൽ (!CONSTANT_CLASS_P (മൂല്യം))
	      {
		constant_p = അസത്യം;
		നിർത്തുക;
	      }

	  എങ്കിൽ (constant_p)
	    തിരികെ build_vector_from_ctor (type,
					   CONSTRUCTOR_ELTS (inside_init));
	}
    }

  എങ്കിൽ (warn_sequence_point)
    verify_sequence_points (inside_init);

  /* Any type can be initialized
     from an expression of the same type, optionally with braces.  */

  എങ്കിൽ (inside_init && വൃക്ഷം_TYPE (inside_init) != NULL_വൃക്ഷം
      && (comptypes (TYPE_MAIN_VARIANT (വൃക്ഷം_TYPE (inside_init)),
		     TYPE_MAIN_VARIANT (type))
	  || (code == ARRAY_TYPE
	      && comptypes (വൃക്ഷം_TYPE (inside_init), type))
	  || (gnu_vector_type_p (type)
	      && comptypes (വൃക്ഷം_TYPE (inside_init), type))
	  || (code == POINTER_TYPE
	      && വൃക്ഷം_CODE (വൃക്ഷം_TYPE (inside_init)) == ARRAY_TYPE
	      && comptypes (വൃക്ഷം_TYPE (വൃക്ഷം_TYPE (inside_init)),
			    വൃക്ഷം_TYPE (type)))))
    {
      എങ്കിൽ (code == POINTER_TYPE)
	{
	  എങ്കിൽ (വൃക്ഷം_CODE (വൃക്ഷം_TYPE (inside_init)) == ARRAY_TYPE)
	    {
	      എങ്കിൽ (വൃക്ഷം_CODE (inside_init) == STRING_CST
		  || വൃക്ഷം_CODE (inside_init) == COMPOUND_LITERAL_വ്യഞ്ജകം)
		inside_init = array_to_pointer_conversion
		  (init_loc, inside_init);
	      അല്ലെങ്കിൽ
		{
		  error_init (init_loc, "invalid use of non-lvalue array");
		  തിരികെ error_mark_കണ്ണി;
		}
	    }
	}

      എങ്കിൽ (code == VECTOR_TYPE || c_hardbool_type_attr (type))
	/* Although the types are compatible, we may require a
	   conversion.  */
	inside_init = convert (type, inside_init);

      എങ്കിൽ ((code == RECORD_TYPE || code == UNION_TYPE)
	  && !comptypes (TYPE_MAIN_VARIANT (type), TYPE_MAIN_VARIANT (വൃക്ഷം_TYPE (inside_init))))
	{
	  error_init (init_loc, "invalid initializer");
	  തിരികെ error_mark_കണ്ണി;
	}

      എങ്കിൽ (require_constant
	  && വൃക്ഷം_CODE (inside_init) == COMPOUND_LITERAL_വ്യഞ്ജകം)
	{
	  /* As an extension, allow initializing objects with static storage
	     duration with compound literals (which are then treated just as
	     the brace enclosed list they contain).  Also allow this for
	     vectors, as we can only assign them with compound literals.  */
	  എങ്കിൽ (flag_isoc99 && code != VECTOR_TYPE)
	    pedwarn_init (init_loc, OPT_Wpedantic, "initializer element "
			  "is not constant");
	  വൃക്ഷം decl = COMPOUND_LITERAL_വ്യഞ്ജകം_DECL (inside_init);
	  inside_init = DECL_INITIAL (decl);
	}

      എങ്കിൽ (code == ARRAY_TYPE && വൃക്ഷം_CODE (inside_init) != STRING_CST
	  && വൃക്ഷം_CODE (inside_init) != CONSTRUCTOR)
	{
	  error_init (init_loc, "array initialized from non-constant array "
		      "expression");
	  തിരികെ error_mark_കണ്ണി;
	}

      /* Compound expressions can only occur here if -Wpedantic or
	 -pedantic-errors is specified.  In the later case, we always want
	 an error.  In the former case, we simply want a warning.  */
      എങ്കിൽ (require_constant && pedantic
	  && വൃക്ഷം_CODE (inside_init) == COMPOUND_വ്യഞ്ജകം)
	{
	  inside_init
	    = valid_compound_വ്യഞ്ജകം_initializer (inside_init,
					       വൃക്ഷം_TYPE (inside_init));
	  എങ്കിൽ (inside_init == error_mark_കണ്ണി)
	    error_init (init_loc, "initializer element is not constant");
	  അല്ലെങ്കിൽ
	    pedwarn_init (init_loc, OPT_Wpedantic,
			  "initializer element is not constant");
	  എങ്കിൽ (flag_pedantic_errors)
	    inside_init = error_mark_കണ്ണി;
	}
      അല്ലെങ്കിൽ എങ്കിൽ (require_constant
	       && !initializer_constant_valid_p (inside_init,
						 വൃക്ഷം_TYPE (inside_init)))
	{
	  error_init (init_loc, "initializer element is not constant");
	  inside_init = error_mark_കണ്ണി;
	}
      അല്ലെങ്കിൽ എങ്കിൽ (require_constant && !maybe_const)
	pedwarn_init (init_loc, OPT_Wpedantic,
		      "initializer element is not a constant expression");
      അല്ലെങ്കിൽ എങ്കിൽ (require_constexpr)
	check_constexpr_init (init_loc, type, inside_init,
			      int_const_വ്യഞ്ജകം, arith_const_വ്യഞ്ജകം);

      /* Added to enable additional -Wsuggest-attribute=format warnings.  */
      എങ്കിൽ (വൃക്ഷം_CODE (വൃക്ഷം_TYPE (inside_init)) == POINTER_TYPE)
	inside_init = convert_for_assignment (init_loc, UNKNOWN_LOCATION,
					      type, inside_init, origtype,
					      (require_constant
					       ? ic_init_const
					       : ic_init), null_pointer_constant,
					      NULL_വൃക്ഷം, NULL_വൃക്ഷം, 0);
      എങ്കിൽ (വൃക്ഷം_CODE (inside_init) == RAW_DATA_CST
	  && c_inhibit_evaluation_warnings == 0
	  && warn_conversion
	  && !TYPE_UNSIGNED (type)
	  && TYPE_PRECISION (type) == CHAR_BIT)
	വേണ്ടി (unsigned പൂർണ്ണസംഖ്യ i = 0;
	     i < (unsigned) RAW_DATA_LENGTH (inside_init); ++i)
	  എങ്കിൽ (RAW_DATA_SCHAR_ELT (inside_init, i) < 0)
	    warning_at (init_loc, OPT_Wconversion,
			"conversion from %qT to %qT changes value from "
			"%qd to %qd",
			integer_type_കണ്ണി, type,
			RAW_DATA_UCHAR_ELT (inside_init, i),
			RAW_DATA_SCHAR_ELT (inside_init, i));
      തിരികെ inside_init;
    }

  /* Handle scalar types, including conversions.  */

  എങ്കിൽ (code == INTEGER_TYPE || code == REAL_TYPE || code == FIXED_POINT_TYPE
      || code == POINTER_TYPE || code == ENUMERAL_TYPE || code == BOOLEAN_TYPE
      || code == COMPLEX_TYPE || code == VECTOR_TYPE || code == NULLPTR_TYPE
      || code == BITINT_TYPE)
    {
      വൃക്ഷം unconverted_init = inside_init;
      എങ്കിൽ (വൃക്ഷം_CODE (വൃക്ഷം_TYPE (init)) == ARRAY_TYPE
	  && (വൃക്ഷം_CODE (init) == STRING_CST
	      || വൃക്ഷം_CODE (init) == COMPOUND_LITERAL_വ്യഞ്ജകം))
	inside_init = init = array_to_pointer_conversion (init_loc, init);
      എങ്കിൽ (semantic_type)
	inside_init = build1 (EXCESS_PRECISION_വ്യഞ്ജകം, semantic_type,
			      inside_init);
      inside_init
	= convert_for_assignment (init_loc, UNKNOWN_LOCATION, type,
				  inside_init, origtype,
				  require_constant ? ic_init_const : ic_init,
				  null_pointer_constant, NULL_വൃക്ഷം, NULL_വൃക്ഷം,
				  0);

      /* Check to see if we have already given an error message.  */
      എങ്കിൽ (inside_init == error_mark_കണ്ണി)
	;
      അല്ലെങ്കിൽ എങ്കിൽ (require_constant && !വൃക്ഷം_CONSTANT (inside_init))
	{
	  error_init (init_loc, "initializer element is not constant");
	  inside_init = error_mark_കണ്ണി;
	}
      അല്ലെങ്കിൽ എങ്കിൽ (require_constant
	       && !initializer_constant_valid_p (inside_init,
						 വൃക്ഷം_TYPE (inside_init)))
	{
	  error_init (init_loc, "initializer element is not computable at "
		      "load time");
	  inside_init = error_mark_കണ്ണി;
	}
      അല്ലെങ്കിൽ എങ്കിൽ (require_constant && !maybe_const)
	pedwarn_init (init_loc, OPT_Wpedantic,
		      "initializer element is not a constant expression");
      അല്ലെങ്കിൽ എങ്കിൽ (require_constexpr)
	check_constexpr_init (init_loc, type, unconverted_init,
			      int_const_വ്യഞ്ജകം, arith_const_വ്യഞ്ജകം);

      തിരികെ inside_init;
    }

  /* Come here only for records and arrays.  */

  എങ്കിൽ (COMPLETE_TYPE_P (type) && വൃക്ഷം_CODE (TYPE_SIZE (type)) != INTEGER_CST)
    {
      error_init (init_loc,
		  "variable-sized object may not be initialized except "
		  "with an empty initializer");
      തിരികെ error_mark_കണ്ണി;
    }

  error_init (init_loc, "invalid initializer");
  തിരികെ error_mark_കണ്ണി;
}

/* Handle initializers that use braces.  */

/* Type of object we are accumulating a constructor for.
   This type is always a RECORD_TYPE, UNION_TYPE or ARRAY_TYPE.  */
സ്ഥിതം വൃക്ഷം constructor_type;

/* For a RECORD_TYPE or UNION_TYPE, this is the chain of fields
   left to fill.  */
സ്ഥിതം വൃക്ഷം constructor_fields;

/* For an ARRAY_TYPE, this is the specified index
   at which to store the next element we get.  */
സ്ഥിതം വൃക്ഷം constructor_index;

/* For an ARRAY_TYPE, this is the maximum index.  */
സ്ഥിതം വൃക്ഷം constructor_max_index;

/* For a RECORD_TYPE, this is the first field not yet written out.  */
സ്ഥിതം വൃക്ഷം constructor_unfilled_fields;

/* For an ARRAY_TYPE, this is the index of the first element
   not yet written out.  */
സ്ഥിതം വൃക്ഷം constructor_unfilled_index;

/* In a RECORD_TYPE, the byte index of the next consecutive field.
   This is so we can generate gaps between fields, when appropriate.  */
സ്ഥിതം വൃക്ഷം constructor_bit_index;

/* If we are saving up the elements rather than allocating them,
   this is the list of elements so far (in reverse order,
   most recent first).  */
സ്ഥിതം vec<constructor_elt, va_gc> *constructor_elements;

/* 1 if constructor should be incrementally stored into a constructor chain,
   0 if all the elements should be kept in AVL tree.  */
സ്ഥിതം പൂർണ്ണസംഖ്യ constructor_incremental;

/* 1 if so far this constructor's elements are all compile-time constants.  */
സ്ഥിതം പൂർണ്ണസംഖ്യ constructor_constant;

/* 1 if so far this constructor's elements are all valid address constants.  */
സ്ഥിതം പൂർണ്ണസംഖ്യ constructor_simple;

/* 1 if this constructor has an element that cannot be part of a
   constant expression.  */
സ്ഥിതം പൂർണ്ണസംഖ്യ constructor_nonconst;

/* 1 if this constructor is erroneous so far.  */
സ്ഥിതം പൂർണ്ണസംഖ്യ constructor_erroneous;

/* 1 if this constructor is the universal zero initializer { 0 }.  */
സ്ഥിതം പൂർണ്ണസംഖ്യ constructor_zeroinit;

/* 1 if this constructor should have padding bits zeroed (C23 {}.  */
സ്ഥിതം തർക്കം constructor_zero_padding_bits;

/* 1 if this constructor is a braced scalar initializer (further nested levels
   of braces are an error).  */
സ്ഥിതം തർക്കം constructor_braced_scalar;

/* Structure for managing pending initializer elements, organized as an
   AVL tree.  */

ഘടന init_കണ്ണി
{
  ഘടന init_കണ്ണി *ഇടത്, *വലത്;
  ഘടന init_കണ്ണി *parent;
  പൂർണ്ണസംഖ്യ balance;
  വൃക്ഷം purpose;
  വൃക്ഷം മൂല്യം;
  വൃക്ഷം origtype;
};

/* Tree of pending elements at this constructor level.
   These are elements encountered out of order
   which belong at places we haven't reached yet in actually
   writing the output.
   Will never hold tree nodes across GC runs.  */
സ്ഥിതം ഘടന init_കണ്ണി *constructor_pending_elts;

/* The SPELLING_DEPTH of this constructor.  */
സ്ഥിതം പൂർണ്ണസംഖ്യ constructor_depth;

/* DECL node for which an initializer is being read.
   0 means we are reading a constructor expression
   such as (struct foo) {...}.  */
സ്ഥിതം വൃക്ഷം constructor_decl;

/* Nonzero if there were any member designators in this initializer.  */
സ്ഥിതം പൂർണ്ണസംഖ്യ constructor_designated;

/* Nesting depth of designator list.  */
സ്ഥിതം പൂർണ്ണസംഖ്യ designator_depth;

/* Nonzero if there were diagnosed errors in this designator list.  */
സ്ഥിതം പൂർണ്ണസംഖ്യ designator_erroneous;


/* This stack has a level for each implicit or explicit level of
   structuring in the initializer, including the outermost one.  It
   saves the values of most of the variables above.  */

ഘടന constructor_range_അട്ടി;

ഘടന constructor_അട്ടി
{
  ഘടന constructor_അട്ടി *next;
  വൃക്ഷം type;
  വൃക്ഷം fields;
  വൃക്ഷം index;
  വൃക്ഷം max_index;
  വൃക്ഷം unfilled_index;
  വൃക്ഷം unfilled_fields;
  വൃക്ഷം bit_index;
  vec<constructor_elt, va_gc> *elements;
  ഘടന init_കണ്ണി *pending_elts;
  പൂർണ്ണസംഖ്യ offset;
  പൂർണ്ണസംഖ്യ depth;
  /* If value nonzero, this value should replace the entire
     constructor at this level.  */
  ഘടന c_വ്യഞ്ജകം replacement_മൂല്യം;
  ഘടന constructor_range_അട്ടി *range_അട്ടി;
  അക്ഷരം constant;
  അക്ഷരം simple;
  അക്ഷരം nonconst;
  അക്ഷരം implicit;
  അക്ഷരം erroneous;
  അക്ഷരം outer;
  അക്ഷരം incremental;
  അക്ഷരം designated;
  തർക്കം zero_padding_bits;
  തർക്കം braced_scalar;
  പൂർണ്ണസംഖ്യ designator_depth;
};

സ്ഥിതം ഘടന constructor_അട്ടി *constructor_അട്ടി;

/* This stack represents designators from some range designator up to
   the last designator in the list.  */

ഘടന constructor_range_അട്ടി
{
  ഘടന constructor_range_അട്ടി *next, *prev;
  ഘടന constructor_അട്ടി *അട്ടി;
  വൃക്ഷം range_start;
  വൃക്ഷം index;
  വൃക്ഷം range_end;
  വൃക്ഷം fields;
};

സ്ഥിതം ഘടന constructor_range_അട്ടി *constructor_range_അട്ടി;

/* This stack records separate initializers that are nested.
   Nested initializers can't happen in ANSI C, but GNU C allows them
   in cases like { ... (struct foo) { ... } ... }.  */

ഘടന initializer_അട്ടി
{
  ഘടന initializer_അട്ടി *next;
  വൃക്ഷം decl;
  ഘടന constructor_അട്ടി *constructor_അട്ടി;
  ഘടന constructor_range_അട്ടി *constructor_range_അട്ടി;
  vec<constructor_elt, va_gc> *elements;
  ഘടന spelling *spelling;
  ഘടന spelling *spelling_base;
  പൂർണ്ണസംഖ്യ spelling_size;
  അക്ഷരം require_constant_മൂല്യം;
  അക്ഷരം require_constant_elements;
  അക്ഷരം require_constexpr_മൂല്യം;
  അക്ഷരം designated;
  rich_location *missing_brace_richloc;
};

സ്ഥിതം ഘടന initializer_അട്ടി *initializer_അട്ടി;

/* Prepare to parse and output the initializer for variable DECL.  */

ശൂന്യം
start_init (വൃക്ഷം decl, വൃക്ഷം asmspec_വൃക്ഷം ATTRIBUTE_UNUSED,
	    തർക്കം init_require_constant, തർക്കം init_require_constexpr,
	    rich_location *richloc)
{
  സ്ഥിരം അക്ഷരം *locus;
  ഘടന initializer_അട്ടി *p = XNEW (ഘടന initializer_അട്ടി);

  p->decl = constructor_decl;
  p->require_constant_മൂല്യം = require_constant_മൂല്യം;
  p->require_constant_elements = require_constant_elements;
  p->require_constexpr_മൂല്യം = require_constexpr_മൂല്യം;
  p->constructor_അട്ടി = constructor_അട്ടി;
  p->constructor_range_അട്ടി = constructor_range_അട്ടി;
  p->elements = constructor_elements;
  p->spelling = spelling;
  p->spelling_base = spelling_base;
  p->spelling_size = spelling_size;
  p->next = initializer_അട്ടി;
  p->missing_brace_richloc = richloc;
  p->designated = constructor_designated;
  initializer_അട്ടി = p;

  constructor_decl = decl;
  constructor_designated = 0;

  require_constant_മൂല്യം = init_require_constant;
  require_constexpr_മൂല്യം = init_require_constexpr;
  എങ്കിൽ (decl != NULL_വൃക്ഷം && decl != error_mark_കണ്ണി)
    {
      require_constant_elements
	= ((init_require_constant || (pedantic && !flag_isoc99))
	   /* For a scalar, you can always use any value to initialize,
	      even within braces.  */
	   && AGGREGATE_TYPE_P (വൃക്ഷം_TYPE (decl)));
      locus = identifier_to_locale (IDENTIFIER_POINTER (DECL_NAME (decl)));
    }
  അല്ലെങ്കിൽ
    {
      require_constant_elements = അസത്യം;
      locus = _("(anonymous)");
    }

  constructor_അട്ടി = 0;
  constructor_range_അട്ടി = 0;

  found_missing_braces = 0;

  spelling_base = 0;
  spelling_size = 0;
  RESTORE_SPELLING_DEPTH (0);

  എങ്കിൽ (locus)
    തള്ളുക_string (locus);
}

ശൂന്യം
finish_init (ശൂന്യം)
{
  ഘടന initializer_അട്ടി *p = initializer_അട്ടി;

  /* Free the whole constructor stack of this initializer.  */
  ആകുമ്പോൾ (constructor_അട്ടി)
    {
      ഘടന constructor_അട്ടി *q = constructor_അട്ടി;
      constructor_അട്ടി = q->next;
      XDELETE (q);
    }

  gcc_assert (!constructor_range_അട്ടി);

  /* Pop back to the data of the outer initializer (if any).  */
  XDELETE (spelling_base);

  constructor_decl = p->decl;
  require_constant_മൂല്യം = p->require_constant_മൂല്യം;
  require_constant_elements = p->require_constant_elements;
  require_constexpr_മൂല്യം = p->require_constexpr_മൂല്യം;
  constructor_അട്ടി = p->constructor_അട്ടി;
  constructor_designated = p->designated;
  constructor_range_അട്ടി = p->constructor_range_അട്ടി;
  constructor_elements = p->elements;
  spelling = p->spelling;
  spelling_base = p->spelling_base;
  spelling_size = p->spelling_size;
  initializer_അട്ടി = p->next;
  XDELETE (p);
}

/* Call here when we see the initializer is surrounded by braces.
   This is instead of a call to push_init_level;
   it is matched by a call to pop_init_level.

   TYPE is the type to initialize, for a constructor expression.
   For an initializer for a decl, TYPE is zero.  */

ശൂന്യം
really_start_incremental_init (വൃക്ഷം type)
{
  ഘടന constructor_അട്ടി *p = XNEW (ഘടന constructor_അട്ടി);

  എങ്കിൽ (type == NULL_വൃക്ഷം)
    type = വൃക്ഷം_TYPE (constructor_decl);

  എങ്കിൽ (VECTOR_TYPE_P (type)
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
  p->replacement_മൂല്യം.മൂല്യം = 0;
  p->replacement_മൂല്യം.original_code = ERROR_MARK;
  p->replacement_മൂല്യം.original_type = ശൂന്യ;
  p->implicit = 0;
  p->range_അട്ടി = 0;
  p->outer = 0;
  p->incremental = constructor_incremental;
  p->designated = constructor_designated;
  p->zero_padding_bits = constructor_zero_padding_bits;
  p->braced_scalar = constructor_braced_scalar;
  p->designator_depth = designator_depth;
  p->next = 0;
  constructor_അട്ടി = p;

  constructor_constant = 1;
  constructor_simple = 1;
  constructor_nonconst = 0;
  constructor_depth = SPELLING_DEPTH ();
  constructor_elements = ശൂന്യ;
  constructor_pending_elts = 0;
  constructor_type = type;
  constructor_incremental = 1;
  constructor_designated = 0;
  constructor_zero_padding_bits = അസത്യം;
  constructor_zeroinit = 1;
  constructor_braced_scalar = അസത്യം;
  designator_depth = 0;
  designator_erroneous = 0;

  എങ്കിൽ (RECORD_OR_UNION_TYPE_P (constructor_type))
    {
      constructor_fields = TYPE_FIELDS (constructor_type);
      /* Skip any nameless bit fields at the beginning.  */
      ആകുമ്പോൾ (constructor_fields != NULL_വൃക്ഷം
	     && DECL_UNNAMED_BIT_FIELD (constructor_fields))
	constructor_fields = DECL_CHAIN (constructor_fields);

      constructor_unfilled_fields = constructor_fields;
      constructor_bit_index = bitsize_zero_കണ്ണി;
    }
  അല്ലെങ്കിൽ എങ്കിൽ (വൃക്ഷം_CODE (constructor_type) == ARRAY_TYPE)
    {
      എങ്കിൽ (TYPE_DOMAIN (constructor_type))
	{
	  constructor_max_index
	    = TYPE_MAX_മൂല്യം (TYPE_DOMAIN (constructor_type));

	  /* Detect non-empty initializations of zero-length arrays.  */
	  എങ്കിൽ (constructor_max_index == NULL_വൃക്ഷം
	      && TYPE_SIZE (constructor_type))
	    constructor_max_index = integer_minus_one_കണ്ണി;

	  /* constructor_max_index needs to be an INTEGER_CST.  Attempts
	     to initialize VLAs with a nonempty initializer will cause a
	     proper error; avoid tree checking errors as well by setting a
	     safe value.  */
	  എങ്കിൽ (constructor_max_index
	      && വൃക്ഷം_CODE (constructor_max_index) != INTEGER_CST)
	    constructor_max_index = integer_minus_one_കണ്ണി;

	  constructor_index
	    = convert (bitsizetype,
		       TYPE_MIN_മൂല്യം (TYPE_DOMAIN (constructor_type)));
	}
      അല്ലെങ്കിൽ
	{
	  constructor_index = bitsize_zero_കണ്ണി;
	  constructor_max_index = NULL_വൃക്ഷം;
	}

      constructor_unfilled_index = constructor_index;
    }
  അല്ലെങ്കിൽ എങ്കിൽ (gnu_vector_type_p (constructor_type))
    {
      /* Vectors are like simple fixed-size arrays.  */
      constructor_max_index =
	bitsize_int (TYPE_VECTOR_SUBPARTS (constructor_type) - 1);
      constructor_index = bitsize_zero_കണ്ണി;
      constructor_unfilled_index = constructor_index;
    }
  അല്ലെങ്കിൽ
    {
      /* Handle the case of int x = {5}; */
      constructor_fields = constructor_type;
      constructor_unfilled_fields = constructor_type;
      constructor_braced_scalar = സത്യം;
    }
}

ബാഹ്യ location_t last_init_list_comma;

/* Called when we see an open brace for a nested initializer.  Finish
   off any pending levels with implicit braces.  */
ശൂന്യം
finish_implicit_inits (location_t loc, ഘടന obstack *braced_init_obstack)
{
  ആകുമ്പോൾ (constructor_അട്ടി->implicit)
    {
      എങ്കിൽ (RECORD_OR_UNION_TYPE_P (constructor_type)
	  && constructor_fields == NULL_വൃക്ഷം)
	process_init_element (നിവേശം_location,
			      എടുക്കുക_init_level (loc, 1, braced_init_obstack,
					      last_init_list_comma),
			      സത്യം, braced_init_obstack);
      അല്ലെങ്കിൽ എങ്കിൽ (വൃക്ഷം_CODE (constructor_type) == ARRAY_TYPE
	       && constructor_max_index
	       && വൃക്ഷം_int_cst_lt (constructor_max_index,
				   constructor_index))
	process_init_element (നിവേശം_location,
			      എടുക്കുക_init_level (loc, 1, braced_init_obstack,
					      last_init_list_comma),
			      സത്യം, braced_init_obstack);
      അല്ലെങ്കിൽ
	നിർത്തുക;
    }
}

/* Push down into a subobject, for initialization.
   If this is for an explicit set of braces, IMPLICIT is 0.
   If it is because the next element belongs at a lower level,
   IMPLICIT is 1 (or 2 if the push is because of designator list).  */

ശൂന്യം
തള്ളുക_init_level (location_t loc, പൂർണ്ണസംഖ്യ implicit,
		 ഘടന obstack *braced_init_obstack)
{
  ഘടന constructor_അട്ടി *p;
  വൃക്ഷം മൂല്യം = NULL_വൃക്ഷം;

  /* Unless this is an explicit brace, we need to preserve previous
     content if any.  */
  എങ്കിൽ (implicit)
    {
      എങ്കിൽ (RECORD_OR_UNION_TYPE_P (constructor_type) && constructor_fields)
	മൂല്യം = find_init_member (constructor_fields, braced_init_obstack);
      അല്ലെങ്കിൽ എങ്കിൽ (വൃക്ഷം_CODE (constructor_type) == ARRAY_TYPE)
	മൂല്യം = find_init_member (constructor_index, braced_init_obstack);
    }

  p = XNEW (ഘടന constructor_അട്ടി);
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
  p->replacement_മൂല്യം.മൂല്യം = NULL_വൃക്ഷം;
  p->replacement_മൂല്യം.original_code = ERROR_MARK;
  p->replacement_മൂല്യം.original_type = ശൂന്യ;
  p->implicit = implicit;
  p->outer = 0;
  p->incremental = constructor_incremental;
  p->designated = constructor_designated;
  p->zero_padding_bits = constructor_zero_padding_bits;
  p->braced_scalar = constructor_braced_scalar;
  p->designator_depth = designator_depth;
  p->next = constructor_അട്ടി;
  p->range_അട്ടി = 0;
  constructor_അട്ടി = p;

  constructor_constant = 1;
  constructor_simple = 1;
  constructor_nonconst = 0;
  constructor_depth = SPELLING_DEPTH ();
  constructor_elements = ശൂന്യ;
  constructor_incremental = 1;
  /* If the upper initializer is designated, then mark this as
     designated too to prevent bogus warnings.  */
  constructor_designated = p->designated;
  /* If the upper initializer has padding bits zeroed, that includes
     all nested initializers as well.  */
  constructor_zero_padding_bits = p->zero_padding_bits;
  constructor_braced_scalar = അസത്യം;
  constructor_pending_elts = 0;
  എങ്കിൽ (!implicit)
    {
      p->range_അട്ടി = constructor_range_അട്ടി;
      constructor_range_അട്ടി = 0;
      designator_depth = 0;
      designator_erroneous = 0;
    }

  /* Don't die if an entire brace-pair level is superfluous
     in the containing level.  */
  എങ്കിൽ (constructor_type == NULL_വൃക്ഷം)
    ;
  അല്ലെങ്കിൽ എങ്കിൽ (RECORD_OR_UNION_TYPE_P (constructor_type))
    {
      /* Don't die if there are extra init elts at the end.  */
      എങ്കിൽ (constructor_fields == NULL_വൃക്ഷം)
	constructor_type = NULL_വൃക്ഷം;
      അല്ലെങ്കിൽ
	{
	  constructor_type = വൃക്ഷം_TYPE (constructor_fields);
	  തള്ളുക_member_name (constructor_fields);
	  constructor_depth++;
	}
    }
  അല്ലെങ്കിൽ എങ്കിൽ (വൃക്ഷം_CODE (constructor_type) == ARRAY_TYPE)
    {
      constructor_type = വൃക്ഷം_TYPE (constructor_type);
      തള്ളുക_array_bounds (വൃക്ഷം_to_uhwi (constructor_index));
      constructor_depth++;
    }

  എങ്കിൽ (constructor_type == NULL_വൃക്ഷം)
    {
      error_init (loc, "extra brace group at end of initializer");
      constructor_fields = NULL_വൃക്ഷം;
      constructor_unfilled_fields = NULL_വൃക്ഷം;
      തിരികെ;
    }

  എങ്കിൽ (മൂല്യം && വൃക്ഷം_CODE (മൂല്യം) == CONSTRUCTOR)
    {
      constructor_constant = വൃക്ഷം_CONSTANT (മൂല്യം);
      constructor_simple = വൃക്ഷം_STATIC (മൂല്യം);
      constructor_nonconst = CONSTRUCTOR_NON_CONST (മൂല്യം);
      constructor_elements = CONSTRUCTOR_ELTS (മൂല്യം);
      constructor_zero_padding_bits |= CONSTRUCTOR_ZERO_PADDING_BITS (മൂല്യം);
      എങ്കിൽ (!vec_safe_is_empty (constructor_elements)
	  && (വൃക്ഷം_CODE (constructor_type) == RECORD_TYPE
	      || വൃക്ഷം_CODE (constructor_type) == ARRAY_TYPE))
	set_nonincremental_init (braced_init_obstack);
    }

  എങ്കിൽ (implicit == 1)
    {
      found_missing_braces = 1;
      എങ്കിൽ (initializer_അട്ടി->missing_brace_richloc)
	initializer_അട്ടി->missing_brace_richloc->add_fixit_തിരുകുക_before
	  (loc, "{");
    }

  എങ്കിൽ (RECORD_OR_UNION_TYPE_P (constructor_type))
    {
      constructor_fields = TYPE_FIELDS (constructor_type);
      /* Skip any nameless bit fields at the beginning.  */
      ആകുമ്പോൾ (constructor_fields != NULL_വൃക്ഷം
	     && DECL_UNNAMED_BIT_FIELD (constructor_fields))
	constructor_fields = DECL_CHAIN (constructor_fields);

      constructor_unfilled_fields = constructor_fields;
      constructor_bit_index = bitsize_zero_കണ്ണി;
    }
  അല്ലെങ്കിൽ എങ്കിൽ (gnu_vector_type_p (constructor_type))
    {
      /* Vectors are like simple fixed-size arrays.  */
      constructor_max_index =
	bitsize_int (TYPE_VECTOR_SUBPARTS (constructor_type) - 1);
      constructor_index = bitsize_int (0);
      constructor_unfilled_index = constructor_index;
    }
  അല്ലെങ്കിൽ എങ്കിൽ (വൃക്ഷം_CODE (constructor_type) == ARRAY_TYPE)
    {
      എങ്കിൽ (TYPE_DOMAIN (constructor_type))
	{
	  constructor_max_index
	    = TYPE_MAX_മൂല്യം (TYPE_DOMAIN (constructor_type));

	  /* Detect non-empty initializations of zero-length arrays.  */
	  എങ്കിൽ (constructor_max_index == NULL_വൃക്ഷം
	      && TYPE_SIZE (constructor_type))
	    constructor_max_index = integer_minus_one_കണ്ണി;

	  /* constructor_max_index needs to be an INTEGER_CST.  Attempts
	     to initialize VLAs will cause a proper error; avoid tree
	     checking errors as well by setting a safe value.  */
	  എങ്കിൽ (constructor_max_index
	      && വൃക്ഷം_CODE (constructor_max_index) != INTEGER_CST)
	    constructor_max_index = integer_minus_one_കണ്ണി;

	  constructor_index
	    = convert (bitsizetype,
		       TYPE_MIN_മൂല്യം (TYPE_DOMAIN (constructor_type)));
	}
      അല്ലെങ്കിൽ
	constructor_index = bitsize_zero_കണ്ണി;

      constructor_unfilled_index = constructor_index;
      എങ്കിൽ (മൂല്യം && വൃക്ഷം_CODE (മൂല്യം) == STRING_CST)
	{
	  /* We need to split the char/wchar array into individual
	     characters, so that we don't have to special case it
	     everywhere.  */
	  set_nonincremental_init_from_string (മൂല്യം, braced_init_obstack);
	}
    }
  അല്ലെങ്കിൽ
    {
      എങ്കിൽ (constructor_type != error_mark_കണ്ണി)
	{
	  എങ്കിൽ (p->braced_scalar)
	    permerror_init (നിവേശം_location, 0,
			    "braces around scalar initializer");
	  അല്ലെങ്കിൽ
	    warning_init (നിവേശം_location, 0,
			  "braces around scalar initializer");
	  constructor_braced_scalar = സത്യം;
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

ഘടന c_വ്യഞ്ജകം
എടുക്കുക_init_level (location_t loc, പൂർണ്ണസംഖ്യ implicit,
		ഘടന obstack *braced_init_obstack,
		location_t തിരുകുക_before)
{
  ഘടന constructor_അട്ടി *p;
  ഘടന c_വ്യഞ്ജകം ret;
  ret.മൂല്യം = NULL_വൃക്ഷം;
  ret.original_code = ERROR_MARK;
  ret.original_type = ശൂന്യ;
  ret.m_decimal = 0;

  എങ്കിൽ (implicit == 0)
    {
      /* When we come to an explicit close brace,
	 pop any inner levels that didn't have explicit braces.  */
      ആകുമ്പോൾ (constructor_അട്ടി->implicit)
	process_init_element (നിവേശം_location,
			      എടുക്കുക_init_level (loc, 1, braced_init_obstack,
					      തിരുകുക_before),
			      സത്യം, braced_init_obstack);
      gcc_assert (!constructor_range_അട്ടി);
    }
  അല്ലെങ്കിൽ
    എങ്കിൽ (initializer_അട്ടി->missing_brace_richloc)
      initializer_അട്ടി->missing_brace_richloc->add_fixit_തിരുകുക_before
	(തിരുകുക_before, "}");

  /* Now output all pending elements.  */
  constructor_incremental = 1;
  output_pending_init_elements (1, braced_init_obstack);

  p = constructor_അട്ടി;

  /* Error for initializing a flexible array member.  */
  എങ്കിൽ (constructor_type && constructor_fields
      && flexible_array_member_type_p (constructor_type))
    {
      /* Silently discard empty initializations.  The parser will
	 already have pedwarned for empty brackets for C17 and earlier.  */
      എങ്കിൽ (integer_zerop (constructor_unfilled_index))
	constructor_type = NULL_വൃക്ഷം;
      എങ്കിൽ (constructor_type || flag_isoc23)
	{
	  gcc_assert (!constructor_type || !TYPE_SIZE (constructor_type));

	  എങ്കിൽ (constructor_depth <= 2)
	    pedwarn_init (loc, OPT_Wpedantic,
			  "initialization of a flexible array member");
	  അല്ലെങ്കിൽ എങ്കിൽ (constructor_type)
	    error_init (loc, "initialization of flexible array member "
			     "in a nested context");
	  അല്ലെങ്കിൽ
	    pedwarn_init (loc, OPT_Wpedantic,
			  "initialization of flexible array member "
			  "in a nested context");

	  /* We have already issued an error message for the existence
	     of a flexible array member not at the end of the structure.
	     Discard the initializer so that we do not die later.  */
	  എങ്കിൽ (constructor_type
	      && DECL_CHAIN (constructor_fields) != NULL_വൃക്ഷം
	      && (!p->type || വൃക്ഷം_CODE (p->type) != UNION_TYPE))
	    constructor_type = NULL_വൃക്ഷം;
	}
    }

  തിരഞ്ഞെടുപ്പ് (vec_safe_length (constructor_elements))
    {
    അവസ്ഥ 0:
      /* Initialization with { } counts as zeroinit.  */
      constructor_zeroinit = 1;
      നിർത്തുക;
    അവസ്ഥ 1:
      /* This might be zeroinit as well.  */
      എങ്കിൽ (integer_zerop ((*constructor_elements)[0].മൂല്യം))
	constructor_zeroinit = 1;
      നിർത്തുക;
    സ്ഥിരസ്ഥിതി:
      /* If the constructor has more than one element, it can't be { 0 }.  */
      constructor_zeroinit = 0;
      നിർത്തുക;
    }

  /* Warn when some structs are initialized with direct aggregation.  */
  എങ്കിൽ (!implicit && found_missing_braces && warn_missing_braces
      && !constructor_zeroinit)
    {
      gcc_assert (initializer_അട്ടി->missing_brace_richloc);
      warning_at (initializer_അട്ടി->missing_brace_richloc,
		  OPT_Wmissing_braces,
		  "missing braces around initializer");
    }

  /* Warn when some struct elements are implicitly initialized to zero.  */
  എങ്കിൽ (warn_missing_field_initializers
      && constructor_type
      && വൃക്ഷം_CODE (constructor_type) == RECORD_TYPE
      && constructor_unfilled_fields)
    {
	/* Do not warn for flexible array members or zero-length arrays.  */
	ആകുമ്പോൾ (constructor_unfilled_fields
	       && (!DECL_SIZE (constructor_unfilled_fields)
		   || integer_zerop (DECL_SIZE (constructor_unfilled_fields))))
	  constructor_unfilled_fields = DECL_CHAIN (constructor_unfilled_fields);

	എങ്കിൽ (constructor_unfilled_fields
	    /* Do not warn if this level of the initializer uses member
	       designators; it is likely to be deliberate.  */
	    && !constructor_designated
	    /* Do not warn about initializing with { 0 } or with { }.  */
	    && !constructor_zeroinit)
	  {
	    എങ്കിൽ (warning_at (നിവേശം_location, OPT_Wmissing_field_initializers,
			    "missing initializer for field %qD of %qT",
			    constructor_unfilled_fields,
			    constructor_type))
	      inform (DECL_SOURCE_LOCATION (constructor_unfilled_fields),
		      "%qD declared here", constructor_unfilled_fields);
	  }
    }

  /* Pad out the end of the structure.  */
  എങ്കിൽ (p->replacement_മൂല്യം.മൂല്യം)
    /* If this closes a superfluous brace pair,
       just pass out the element between them.  */
    ret = p->replacement_മൂല്യം;
  അല്ലെങ്കിൽ എങ്കിൽ (constructor_type == NULL_വൃക്ഷം)
    ;
  അല്ലെങ്കിൽ എങ്കിൽ (!RECORD_OR_UNION_TYPE_P (constructor_type)
	   && വൃക്ഷം_CODE (constructor_type) != ARRAY_TYPE
	   && !gnu_vector_type_p (constructor_type))
    {
      /* A nonincremental scalar initializer--just return
	 the element, after verifying there is just one.
         Empty scalar initializers are supported in C23.  */
      എങ്കിൽ (vec_safe_is_empty (constructor_elements))
	{
	  എങ്കിൽ (constructor_erroneous || constructor_type == error_mark_കണ്ണി)
	    ret.മൂല്യം = error_mark_കണ്ണി;
	  അല്ലെങ്കിൽ എങ്കിൽ (വൃക്ഷം_CODE (constructor_type) == FUNCTION_TYPE)
	    {
	      error_init (loc, "invalid initializer");
	      ret.മൂല്യം = error_mark_കണ്ണി;
	    }
	  അല്ലെങ്കിൽ എങ്കിൽ (വൃക്ഷം_CODE (constructor_type) == POINTER_TYPE)
	    /* Ensure this is a null pointer constant in the case of a
	       'constexpr' object initialized with {}.  */
	    ret.മൂല്യം = build_zero_cst (ptr_type_കണ്ണി);
	  അല്ലെങ്കിൽ
	    ret.മൂല്യം = build_zero_cst (constructor_type);
	}
      അല്ലെങ്കിൽ എങ്കിൽ (vec_safe_length (constructor_elements) != 1)
	{
	  error_init (loc, "extra elements in scalar initializer");
	  ret.മൂല്യം = (*constructor_elements)[0].മൂല്യം;
	}
      അല്ലെങ്കിൽ
	ret.മൂല്യം = (*constructor_elements)[0].മൂല്യം;
    }
  അല്ലെങ്കിൽ
    {
      എങ്കിൽ (constructor_erroneous)
	ret.മൂല്യം = error_mark_കണ്ണി;
      അല്ലെങ്കിൽ
	{
	  ret.മൂല്യം = build_constructor (constructor_type,
					 constructor_elements);
	  എങ്കിൽ (constructor_constant)
	    വൃക്ഷം_CONSTANT (ret.മൂല്യം) = 1;
	  എങ്കിൽ (constructor_constant && constructor_simple)
	    വൃക്ഷം_STATIC (ret.മൂല്യം) = 1;
	  എങ്കിൽ (constructor_nonconst)
	    CONSTRUCTOR_NON_CONST (ret.മൂല്യം) = 1;
	  എങ്കിൽ (constructor_zero_padding_bits)
	    CONSTRUCTOR_ZERO_PADDING_BITS (ret.മൂല്യം) = 1;
	}
    }

  എങ്കിൽ (ret.മൂല്യം && വൃക്ഷം_CODE (ret.മൂല്യം) != CONSTRUCTOR)
    {
      എങ്കിൽ (constructor_nonconst)
	ret.original_code = C_MAYBE_CONST_വ്യഞ്ജകം;
      അല്ലെങ്കിൽ എങ്കിൽ (ret.original_code == C_MAYBE_CONST_വ്യഞ്ജകം)
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
  എങ്കിൽ (!p->implicit)
    constructor_range_അട്ടി = p->range_അട്ടി;
  RESTORE_SPELLING_DEPTH (constructor_depth);

  constructor_അട്ടി = p->next;
  XDELETE (p);

  എങ്കിൽ (ret.മൂല്യം == NULL_വൃക്ഷം && constructor_അട്ടി == 0)
    ret.മൂല്യം = error_mark_കണ്ണി;
  തിരികെ ret;
}

/* Common handling for both array range and field name designators.
   ARRAY argument is nonzero for array ranges.  Returns false for success.  */

സ്ഥിതം തർക്കം
set_designator (location_t loc, തർക്കം array,
		ഘടന obstack *braced_init_obstack)
{
  വൃക്ഷം subtype;
  എണ്ണൽ വൃക്ഷം_code subcode;

  /* Don't die if an entire brace-pair level is superfluous
     in the containing level, or for an erroneous type.  */
  എങ്കിൽ (constructor_type == NULL_വൃക്ഷം || constructor_type == error_mark_കണ്ണി)
    തിരികെ സത്യം;

  /* If there were errors in this designator list already, bail out
     silently.  */
  എങ്കിൽ (designator_erroneous)
    തിരികെ സത്യം;

  /* Likewise for an initializer for a variable-size type.  Those are
     diagnosed in the parser, except for empty initializer braces.  */
  എങ്കിൽ (COMPLETE_TYPE_P (constructor_type)
      && വൃക്ഷം_CODE (TYPE_SIZE (constructor_type)) != INTEGER_CST)
    തിരികെ സത്യം;

  എങ്കിൽ (!designator_depth)
    {
      gcc_assert (!constructor_range_അട്ടി);

      /* Designator list starts at the level of closest explicit
	 braces.  */
      ആകുമ്പോൾ (constructor_അട്ടി->implicit)
	process_init_element (നിവേശം_location,
			      എടുക്കുക_init_level (loc, 1, braced_init_obstack,
					      last_init_list_comma),
			      സത്യം, braced_init_obstack);
      constructor_designated = 1;
      തിരികെ അസത്യം;
    }

  തിരഞ്ഞെടുപ്പ് (വൃക്ഷം_CODE (constructor_type))
    {
    അവസ്ഥ  RECORD_TYPE:
    അവസ്ഥ  UNION_TYPE:
      subtype = വൃക്ഷം_TYPE (constructor_fields);
      എങ്കിൽ (subtype != error_mark_കണ്ണി)
	subtype = TYPE_MAIN_VARIANT (subtype);
      നിർത്തുക;
    അവസ്ഥ ARRAY_TYPE:
      subtype = TYPE_MAIN_VARIANT (വൃക്ഷം_TYPE (constructor_type));
      നിർത്തുക;
    സ്ഥിരസ്ഥിതി:
      gcc_unreachable ();
    }

  subcode = വൃക്ഷം_CODE (subtype);
  എങ്കിൽ (array && subcode != ARRAY_TYPE)
    {
      error_init (loc, "array index in non-array initializer");
      തിരികെ സത്യം;
    }
  അല്ലെങ്കിൽ എങ്കിൽ (!array && subcode != RECORD_TYPE && subcode != UNION_TYPE)
    {
      error_init (loc, "field name not in record or union initializer");
      തിരികെ സത്യം;
    }

  constructor_designated = 1;
  finish_implicit_inits (loc, braced_init_obstack);
  തള്ളുക_init_level (loc, 2, braced_init_obstack);
  തിരികെ അസത്യം;
}

/* If there are range designators in designator list, push a new designator
   to constructor_range_stack.  RANGE_END is end of such stack range or
   NULL_TREE if there is no range designator at this level.  */

സ്ഥിതം ശൂന്യം
തള്ളുക_range_അട്ടി (വൃക്ഷം range_end, ഘടന obstack * braced_init_obstack)
{
  ഘടന constructor_range_അട്ടി *p;

  p = (ഘടന constructor_range_അട്ടി *)
    obstack_alloc (braced_init_obstack,
		   വലുപ്പം (ഘടന constructor_range_അട്ടി));
  p->prev = constructor_range_അട്ടി;
  p->next = 0;
  p->fields = constructor_fields;
  p->range_start = constructor_index;
  p->index = constructor_index;
  p->അട്ടി = constructor_അട്ടി;
  p->range_end = range_end;
  എങ്കിൽ (constructor_range_അട്ടി)
    constructor_range_അട്ടി->next = p;
  constructor_range_അട്ടി = p;
}

/* Within an array initializer, specify the next index to be initialized.
   FIRST is that index.  If LAST is nonzero, then initialize a range
   of indices, running from FIRST through LAST.  */

ശൂന്യം
set_init_index (location_t loc, വൃക്ഷം first, വൃക്ഷം last,
		ഘടന obstack *braced_init_obstack)
{
  എങ്കിൽ (set_designator (loc, സത്യം, braced_init_obstack))
    തിരികെ;

  designator_erroneous = 1;

  എങ്കിൽ (!INTEGRAL_TYPE_P (വൃക്ഷം_TYPE (first))
      || (last && !INTEGRAL_TYPE_P (വൃക്ഷം_TYPE (last))))
    {
      error_init (loc, "array index in initializer not of integer type");
      തിരികെ;
    }

  എങ്കിൽ (വൃക്ഷം_CODE (first) != INTEGER_CST)
    {
      first = c_fully_fold (first, അസത്യം, ശൂന്യ);
      എങ്കിൽ (വൃക്ഷം_CODE (first) == INTEGER_CST)
	pedwarn_init (loc, OPT_Wpedantic,
		      "array index in initializer is not "
		      "an integer constant expression");
    }

  എങ്കിൽ (last && വൃക്ഷം_CODE (last) != INTEGER_CST)
    {
      last = c_fully_fold (last, അസത്യം, ശൂന്യ);
      എങ്കിൽ (വൃക്ഷം_CODE (last) == INTEGER_CST)
	pedwarn_init (loc, OPT_Wpedantic,
		      "array index in initializer is not "
		      "an integer constant expression");
    }

  എങ്കിൽ (വൃക്ഷം_CODE (first) != INTEGER_CST)
    error_init (loc, "nonconstant array index in initializer");
  അല്ലെങ്കിൽ എങ്കിൽ (last != NULL_വൃക്ഷം && വൃക്ഷം_CODE (last) != INTEGER_CST)
    error_init (loc, "nonconstant array index in initializer");
  അല്ലെങ്കിൽ എങ്കിൽ (വൃക്ഷം_CODE (constructor_type) != ARRAY_TYPE)
    error_init (loc, "array index in non-array initializer");
  അല്ലെങ്കിൽ എങ്കിൽ (വൃക്ഷം_int_cst_sgn (first) == -1)
    error_init (loc, "array index in initializer exceeds array bounds");
  അല്ലെങ്കിൽ എങ്കിൽ (constructor_max_index
	   && വൃക്ഷം_int_cst_lt (constructor_max_index, first))
    error_init (loc, "array index in initializer exceeds array bounds");
  അല്ലെങ്കിൽ
    {
      constant_expression_warning (first);
      എങ്കിൽ (last)
	constant_expression_warning (last);
      constructor_index = convert (bitsizetype, first);
      എങ്കിൽ (വൃക്ഷം_int_cst_lt (constructor_index, first))
	{
	  constructor_index = copy_കണ്ണി (constructor_index);
	  വൃക്ഷം_OVERFLOW (constructor_index) = 1;
	}

      എങ്കിൽ (last)
	{
	  എങ്കിൽ (വൃക്ഷം_int_cst_equal (first, last))
	    last = NULL_വൃക്ഷം;
	  അല്ലെങ്കിൽ എങ്കിൽ (വൃക്ഷം_int_cst_lt (last, first))
	    {
	      error_init (loc, "empty index range in initializer");
	      last = NULL_വൃക്ഷം;
	    }
	  അല്ലെങ്കിൽ
	    {
	      last = convert (bitsizetype, last);
	      എങ്കിൽ (constructor_max_index != NULL_വൃക്ഷം
		  && വൃക്ഷം_int_cst_lt (constructor_max_index, last))
		{
		  error_init (loc, "array index range in initializer exceeds "
			      "array bounds");
		  last = NULL_വൃക്ഷം;
		}
	    }
	}

      designator_depth++;
      designator_erroneous = 0;
      എങ്കിൽ (constructor_range_അട്ടി || last)
	തള്ളുക_range_അട്ടി (last, braced_init_obstack);
    }
}

/* Within a struct initializer, specify the next field to be initialized.  */

ശൂന്യം
set_init_label (location_t loc, വൃക്ഷം fieldname, location_t fieldname_loc,
		ഘടന obstack *braced_init_obstack)
{
  വൃക്ഷം field;

  എങ്കിൽ (set_designator (loc, അസത്യം, braced_init_obstack))
    തിരികെ;

  designator_erroneous = 1;

  എങ്കിൽ (!RECORD_OR_UNION_TYPE_P (constructor_type))
    {
      error_init (loc, "field name not in record or union initializer");
      തിരികെ;
    }

  field = lookup_field (constructor_type, fieldname);

  എങ്കിൽ (field == NULL_വൃക്ഷം)
    {
      വൃക്ഷം guessed_id = lookup_field_fuzzy (constructor_type, fieldname);
      എങ്കിൽ (guessed_id)
	{
	  gcc_rich_location rich_loc (fieldname_loc);
	  rich_loc.add_fixit_misspelled_id (fieldname_loc, guessed_id);
	  error_at (&rich_loc,
		    "%qT has no member named %qE; did you mean %qE?",
		    constructor_type, fieldname, guessed_id);
	}
      അല്ലെങ്കിൽ
	error_at (fieldname_loc, "%qT has no member named %qE",
		  constructor_type, fieldname);
    }
  അല്ലെങ്കിൽ
    ചെയ്യുക
      {
	constructor_fields = വൃക്ഷം_മൂല്യം (field);
	designator_depth++;
	designator_erroneous = 0;
	എങ്കിൽ (constructor_range_അട്ടി)
	  തള്ളുക_range_അട്ടി (NULL_വൃക്ഷം, braced_init_obstack);
	field = വൃക്ഷം_CHAIN (field);
	എങ്കിൽ (field)
	  {
	    എങ്കിൽ (set_designator (loc, അസത്യം, braced_init_obstack))
	      തിരികെ;
	  }
      }
    ആകുമ്പോൾ (field != NULL_വൃക്ഷം);
}

/* Helper function for add_pending_init.  Find inorder successor of P
   in AVL tree.  */
സ്ഥിതം ഘടന init_കണ്ണി *
init_കണ്ണി_successor (ഘടന init_കണ്ണി *p)
{
  ഘടന init_കണ്ണി *r;
  എങ്കിൽ (p->വലത്)
    {
      r = p->വലത്;
      ആകുമ്പോൾ (r->ഇടത്)
	r = r->ഇടത്;
      തിരികെ r;
    }
  r = p->parent;
  ആകുമ്പോൾ (r && p == r->വലത്)
    {
      p = r;
      r = r->parent;
    }
  തിരികെ r;
}

/* Add a new initializer to the tree of pending initializers.  PURPOSE
   identifies the initializer, either array index or field in a structure.
   VALUE is the value of that index or field.  If ORIGTYPE is not
   NULL_TREE, it is the original type of VALUE.

   IMPLICIT is true if value comes from pop_init_level (1),
   the new initializer has been merged with the existing one
   and thus no warnings should be emitted about overriding an
   existing initializer.  */

സ്ഥിതം ശൂന്യം
add_pending_init (location_t loc, വൃക്ഷം purpose, വൃക്ഷം മൂല്യം, വൃക്ഷം origtype,
		  തർക്കം implicit, ഘടന obstack *braced_init_obstack)
{
  ഘടന init_കണ്ണി *p, **q, *r;

  q = &constructor_pending_elts;
  p = 0;

  എങ്കിൽ (വൃക്ഷം_CODE (constructor_type) == ARRAY_TYPE)
    {
      ആകുമ്പോൾ (*q != 0)
	{
	  p = *q;
	  എങ്കിൽ (വൃക്ഷം_int_cst_lt (purpose, p->purpose))
	    q = &p->ഇടത്;
	  അല്ലെങ്കിൽ എങ്കിൽ (വൃക്ഷം_int_cst_lt (p->purpose, purpose))
	    {
	      എങ്കിൽ (വൃക്ഷം_CODE (p->മൂല്യം) != RAW_DATA_CST
		  || (p->വലത്
		      && വൃക്ഷം_int_cst_le (p->വലത്->purpose, purpose)))
		q = &p->വലത്;
	      അല്ലെങ്കിൽ
		{
		  widest_int pp = wi::to_widest (p->purpose);
		  widest_int pw = wi::to_widest (purpose);
		  എങ്കിൽ (pp + RAW_DATA_LENGTH (p->മൂല്യം) <= pw)
		    q = &p->വലത്;
		  അല്ലെങ്കിൽ
		    {
		      /* Override which should split the old RAW_DATA_CST
			 into 2 or 3 pieces.  */
		      എങ്കിൽ (!implicit && warn_override_init)
			warning_init (loc, OPT_Woverride_init,
				      "initialized field overwritten");
		      unsigned HOST_WIDE_INT start = (pw - pp).to_uhwi ();
		      unsigned HOST_WIDE_INT len = 1;
		      എങ്കിൽ (വൃക്ഷം_CODE (മൂല്യം) == RAW_DATA_CST)
			len = RAW_DATA_LENGTH (മൂല്യം);
		      unsigned HOST_WIDE_INT end = 0;
		      unsigned plen = RAW_DATA_LENGTH (p->മൂല്യം);
		      gcc_checking_assert (start < plen && start);
		      എങ്കിൽ (plen - start > len)
			end = plen - start - len;
		      വൃക്ഷം v = p->മൂല്യം;
		      വൃക്ഷം origtype = p->origtype;
		      എങ്കിൽ (start == 1)
			p->മൂല്യം = build_int_cst (വൃക്ഷം_TYPE (v),
						  RAW_DATA_UCHAR_ELT (v, 0));
		      അല്ലെങ്കിൽ
			{
			  p->മൂല്യം = v;
			  എങ്കിൽ (end > 1)
			    v = copy_കണ്ണി (v);
			  RAW_DATA_LENGTH (p->മൂല്യം) = start;
			}
		      എങ്കിൽ (end)
			{
			  വൃക്ഷം epurpose
			    = size_binop (PLUS_വ്യഞ്ജകം, purpose,
					  bitsize_int (len));
			  എങ്കിൽ (end > 1)
			    {
			      RAW_DATA_LENGTH (v) -= plen - end;
			      RAW_DATA_POINTER (v) += plen - end;
			    }
			  അല്ലെങ്കിൽ
			    v = build_int_cst (വൃക്ഷം_TYPE (v),
					       RAW_DATA_UCHAR_ELT (v, plen
								      - end));
			  add_pending_init (loc, epurpose, v, origtype,
					    implicit, braced_init_obstack);
			}
		      q = &constructor_pending_elts;
		      തുടരുക;
		    }
		}
	    }
	  അല്ലെങ്കിൽ
	    {
	      എങ്കിൽ (വൃക്ഷം_CODE (p->മൂല്യം) == RAW_DATA_CST
		  && (RAW_DATA_LENGTH (p->മൂല്യം)
		      > (വൃക്ഷം_CODE (മൂല്യം) == RAW_DATA_CST
			 ? RAW_DATA_LENGTH (മൂല്യം) : 1)))
		{
		  /* Override which should split the old RAW_DATA_CST
		     into 2 pieces.  */
		  എങ്കിൽ (!implicit && warn_override_init)
		    warning_init (loc, OPT_Woverride_init,
				  "initialized field overwritten");
		  unsigned HOST_WIDE_INT len = 1;
		  എങ്കിൽ (വൃക്ഷം_CODE (മൂല്യം) == RAW_DATA_CST)
		    len = RAW_DATA_LENGTH (മൂല്യം);
		  എങ്കിൽ ((unsigned) RAW_DATA_LENGTH (p->മൂല്യം) > len + 1)
		    {
		      RAW_DATA_LENGTH (p->മൂല്യം) -= len;
		      RAW_DATA_POINTER (p->മൂല്യം) += len;
		    }
		  അല്ലെങ്കിൽ
		    {
		      unsigned പൂർണ്ണസംഖ്യ l = RAW_DATA_LENGTH (p->മൂല്യം) - 1;
		      p->മൂല്യം
			= build_int_cst (വൃക്ഷം_TYPE (p->മൂല്യം),
					 RAW_DATA_UCHAR_ELT (p->മൂല്യം, l));
		    }
		  p->purpose = size_binop (PLUS_വ്യഞ്ജകം, p->purpose,
					   bitsize_int (len));
		  തുടരുക;
		}
	      എങ്കിൽ (വൃക്ഷം_CODE (മൂല്യം) == RAW_DATA_CST)
		{
		handle_raw_data:
		  /* RAW_DATA_CST value might overlap various further
		     prior initval entries.  Find out how many.  */
		  unsigned cnt = 0;
		  widest_int w
		    = wi::to_widest (purpose) + RAW_DATA_LENGTH (മൂല്യം);
		  ഘടന init_കണ്ണി *r = p, *last = ശൂന്യ;
		  തർക്കം override_init = warn_override_init;
		  ആകുമ്പോൾ ((r = init_കണ്ണി_successor (r))
			 && wi::to_widest (r->purpose) < w)
		    {
		      ++cnt;
		      എങ്കിൽ (വൃക്ഷം_SIDE_EFFECTS (r->മൂല്യം))
			warning_init (loc, OPT_Woverride_init_side_effects,
				      "initialized field with side-effects "
				      "overwritten");
		      അല്ലെങ്കിൽ എങ്കിൽ (override_init)
			{
			  warning_init (loc, OPT_Woverride_init,
					"initialized field overwritten");
			  override_init = അസത്യം;
			}
		      last = r;
		    }
		  എങ്കിൽ (cnt)
		    {
		      എങ്കിൽ (വൃക്ഷം_CODE (last->മൂല്യം) == RAW_DATA_CST
			  && (wi::to_widest (last->purpose)
			      + RAW_DATA_LENGTH (last->മൂല്യം) > w))
			{
			  /* The last overlapping prior initval overlaps
			     only partially.  Shrink it and decrease cnt.  */
			  unsigned പൂർണ്ണസംഖ്യ l = (wi::to_widest (last->purpose)
					    + RAW_DATA_LENGTH (last->മൂല്യം)
					    - w).to_uhwi ();
			  --cnt;
			  RAW_DATA_LENGTH (last->മൂല്യം) -= l;
			  RAW_DATA_POINTER (last->മൂല്യം) += l;
			  എങ്കിൽ (RAW_DATA_LENGTH (last->മൂല്യം) == 1)
			    last->മൂല്യം
			      = build_int_cst (വൃക്ഷം_TYPE (last->മൂല്യം),
					       RAW_DATA_UCHAR_ELT (last->മൂല്യം,
								   0));
			  last->purpose
			    = size_binop (PLUS_വ്യഞ്ജകം, last->purpose,
					  bitsize_int (l));
			}
		      /* Instead of deleting cnt nodes from the AVL tree
			 and rebalancing, peel of last cnt bytes from the
			 RAW_DATA_CST.  Overriding thousands of previously
			 initialized array elements with #embed needs to work,
			 but doesn't need to be super efficient.  */
		      gcc_checking_assert ((unsigned) RAW_DATA_LENGTH (മൂല്യം)
					   > cnt);
		      RAW_DATA_LENGTH (മൂല്യം) -= cnt;
		      സ്ഥിരം unsigned അക്ഷരം *s
			= &RAW_DATA_UCHAR_ELT (മൂല്യം, RAW_DATA_LENGTH (മൂല്യം));
		      unsigned പൂർണ്ണസംഖ്യ o = RAW_DATA_LENGTH (മൂല്യം);
		      വേണ്ടി (r = p; cnt--; ++o, ++s)
			{
			  r = init_കണ്ണി_successor (r);
			  r->purpose = size_binop (PLUS_വ്യഞ്ജകം, purpose,
						   bitsize_int (o));
			  r->മൂല്യം = build_int_cst (വൃക്ഷം_TYPE (മൂല്യം), *s);
			  r->origtype = origtype;
			}
		      എങ്കിൽ (RAW_DATA_LENGTH (മൂല്യം) == 1)
			മൂല്യം = build_int_cst (വൃക്ഷം_TYPE (മൂല്യം),
					       RAW_DATA_UCHAR_ELT (മൂല്യം, 0));
		    }
		}
	      എങ്കിൽ (!implicit)
		{
		  എങ്കിൽ (വൃക്ഷം_SIDE_EFFECTS (p->മൂല്യം))
		    warning_init (loc, OPT_Woverride_init_side_effects,
				  "initialized field with side-effects "
				  "overwritten");
		  അല്ലെങ്കിൽ എങ്കിൽ (warn_override_init)
		    warning_init (loc, OPT_Woverride_init,
				  "initialized field overwritten");
		}
	      p->മൂല്യം = മൂല്യം;
	      p->origtype = origtype;
	      തിരികെ;
	    }
	}
      എങ്കിൽ (വൃക്ഷം_CODE (മൂല്യം) == RAW_DATA_CST && p)
	{
	  ഘടന init_കണ്ണി *r;
	  എങ്കിൽ (q == &p->ഇടത്)
	    r = p;
	  അല്ലെങ്കിൽ
	    r = init_കണ്ണി_successor (p);
	  എങ്കിൽ (r && wi::to_widest (r->purpose) < (wi::to_widest (purpose)
						 + RAW_DATA_LENGTH (മൂല്യം)))
	    {
	      /* Overlap with at least one prior initval in the range but
		 not at the start.  */
	      p = r;
	      p->purpose = purpose;
	      പോകുക handle_raw_data;
	    }
	}
    }
  അല്ലെങ്കിൽ
    {
      വൃക്ഷം bitpos;

      bitpos = bit_position (purpose);
      ആകുമ്പോൾ (*q != ശൂന്യ)
	{
	  p = *q;
	  എങ്കിൽ (വൃക്ഷം_int_cst_lt (bitpos, bit_position (p->purpose)))
	    q = &p->ഇടത്;
	  അല്ലെങ്കിൽ എങ്കിൽ (p->purpose != purpose)
	    q = &p->വലത്;
	  അല്ലെങ്കിൽ
	    {
	      എങ്കിൽ (!implicit)
		{
		  എങ്കിൽ (വൃക്ഷം_SIDE_EFFECTS (p->മൂല്യം))
		    warning_init (loc, OPT_Woverride_init_side_effects,
				  "initialized field with side-effects "
				  "overwritten");
		  അല്ലെങ്കിൽ എങ്കിൽ (warn_override_init)
		    warning_init (loc, OPT_Woverride_init,
				  "initialized field overwritten");
		}
	      p->മൂല്യം = മൂല്യം;
	      p->origtype = origtype;
	      തിരികെ;
	    }
	}
    }

  r = (ഘടന init_കണ്ണി *) obstack_alloc (braced_init_obstack,
					  വലുപ്പം (ഘടന init_കണ്ണി));
  r->purpose = purpose;
  r->മൂല്യം = മൂല്യം;
  r->origtype = origtype;

  *q = r;
  r->parent = p;
  r->ഇടത് = 0;
  r->വലത് = 0;
  r->balance = 0;

  ആകുമ്പോൾ (p)
    {
      ഘടന init_കണ്ണി *s;

      എങ്കിൽ (r == p->ഇടത്)
	{
	  എങ്കിൽ (p->balance == 0)
	    p->balance = -1;
	  അല്ലെങ്കിൽ എങ്കിൽ (p->balance < 0)
	    {
	      എങ്കിൽ (r->balance < 0)
		{
		  /* L rotation.  */
		  p->ഇടത് = r->വലത്;
		  എങ്കിൽ (p->ഇടത്)
		    p->ഇടത്->parent = p;
		  r->വലത് = p;

		  p->balance = 0;
		  r->balance = 0;

		  s = p->parent;
		  p->parent = r;
		  r->parent = s;
		  എങ്കിൽ (s)
		    {
		      എങ്കിൽ (s->ഇടത് == p)
			s->ഇടത് = r;
		      അല്ലെങ്കിൽ
			s->വലത് = r;
		    }
		  അല്ലെങ്കിൽ
		    constructor_pending_elts = r;
		}
	      അല്ലെങ്കിൽ
		{
		  /* LR rotation.  */
		  ഘടന init_കണ്ണി *t = r->വലത്;

		  r->വലത് = t->ഇടത്;
		  എങ്കിൽ (r->വലത്)
		    r->വലത്->parent = r;
		  t->ഇടത് = r;

		  p->ഇടത് = t->വലത്;
		  എങ്കിൽ (p->ഇടത്)
		    p->ഇടത്->parent = p;
		  t->വലത് = p;

		  p->balance = t->balance < 0;
		  r->balance = -(t->balance > 0);
		  t->balance = 0;

		  s = p->parent;
		  p->parent = t;
		  r->parent = t;
		  t->parent = s;
		  എങ്കിൽ (s)
		    {
		      എങ്കിൽ (s->ഇടത് == p)
			s->ഇടത് = t;
		      അല്ലെങ്കിൽ
			s->വലത് = t;
		    }
		  അല്ലെങ്കിൽ
		    constructor_pending_elts = t;
		}
	      നിർത്തുക;
	    }
	  അല്ലെങ്കിൽ
	    {
	      /* p->balance == +1; growth of left side balances the node.  */
	      p->balance = 0;
	      നിർത്തുക;
	    }
	}
      അല്ലെങ്കിൽ /* r == p->right */
	{
	  എങ്കിൽ (p->balance == 0)
	    /* Growth propagation from right side.  */
	    p->balance++;
	  അല്ലെങ്കിൽ എങ്കിൽ (p->balance > 0)
	    {
	      എങ്കിൽ (r->balance > 0)
		{
		  /* R rotation.  */
		  p->വലത് = r->ഇടത്;
		  എങ്കിൽ (p->വലത്)
		    p->വലത്->parent = p;
		  r->ഇടത് = p;

		  p->balance = 0;
		  r->balance = 0;

		  s = p->parent;
		  p->parent = r;
		  r->parent = s;
		  എങ്കിൽ (s)
		    {
		      എങ്കിൽ (s->ഇടത് == p)
			s->ഇടത് = r;
		      അല്ലെങ്കിൽ
			s->വലത് = r;
		    }
		  അല്ലെങ്കിൽ
		    constructor_pending_elts = r;
		}
	      അല്ലെങ്കിൽ /* r->balance == -1 */
		{
		  /* RL rotation */
		  ഘടന init_കണ്ണി *t = r->ഇടത്;

		  r->ഇടത് = t->വലത്;
		  എങ്കിൽ (r->ഇടത്)
		    r->ഇടത്->parent = r;
		  t->വലത് = r;

		  p->വലത് = t->ഇടത്;
		  എങ്കിൽ (p->വലത്)
		    p->വലത്->parent = p;
		  t->ഇടത് = p;

		  r->balance = (t->balance < 0);
		  p->balance = -(t->balance > 0);
		  t->balance = 0;

		  s = p->parent;
		  p->parent = t;
		  r->parent = t;
		  t->parent = s;
		  എങ്കിൽ (s)
		    {
		      എങ്കിൽ (s->ഇടത് == p)
			s->ഇടത് = t;
		      അല്ലെങ്കിൽ
			s->വലത് = t;
		    }
		  അല്ലെങ്കിൽ
		    constructor_pending_elts = t;
		}
	      നിർത്തുക;
	    }
	  അല്ലെങ്കിൽ
	    {
	      /* p->balance == -1; growth of right side balances the node.  */
	      p->balance = 0;
	      നിർത്തുക;
	    }
	}

      r = p;
      p = p->parent;
    }
}

/* Build AVL tree from a sorted chain.  */

സ്ഥിതം ശൂന്യം
set_nonincremental_init (ഘടന obstack * braced_init_obstack)
{
  unsigned HOST_WIDE_INT ix;
  വൃക്ഷം index, മൂല്യം;

  എങ്കിൽ (വൃക്ഷം_CODE (constructor_type) != RECORD_TYPE
      && വൃക്ഷം_CODE (constructor_type) != ARRAY_TYPE)
    തിരികെ;

  FOR_EACH_CONSTRUCTOR_ELT (constructor_elements, ix, index, മൂല്യം)
    add_pending_init (നിവേശം_location, index, മൂല്യം, NULL_വൃക്ഷം, സത്യം,
		      braced_init_obstack);
  constructor_elements = ശൂന്യ;
  എങ്കിൽ (വൃക്ഷം_CODE (constructor_type) == RECORD_TYPE)
    {
      constructor_unfilled_fields = TYPE_FIELDS (constructor_type);
      /* Skip any nameless bit fields at the beginning.  */
      ആകുമ്പോൾ (constructor_unfilled_fields != NULL_വൃക്ഷം
	     && DECL_UNNAMED_BIT_FIELD (constructor_unfilled_fields))
	constructor_unfilled_fields = വൃക്ഷം_CHAIN (constructor_unfilled_fields);

    }
  അല്ലെങ്കിൽ എങ്കിൽ (വൃക്ഷം_CODE (constructor_type) == ARRAY_TYPE)
    {
      എങ്കിൽ (TYPE_DOMAIN (constructor_type))
	constructor_unfilled_index
	  = convert (bitsizetype,
		     TYPE_MIN_മൂല്യം (TYPE_DOMAIN (constructor_type)));
      അല്ലെങ്കിൽ
	constructor_unfilled_index = bitsize_zero_കണ്ണി;
    }
  constructor_incremental = 0;
}

/* Build AVL tree from a string constant.  */

സ്ഥിതം ശൂന്യം
set_nonincremental_init_from_string (വൃക്ഷം str,
				     ഘടന obstack * braced_init_obstack)
{
  വൃക്ഷം മൂല്യം, purpose, type;
  HOST_WIDE_INT val[2];
  സ്ഥിരം അക്ഷരം *p, *end;
  പൂർണ്ണസംഖ്യ byte, wchar_bytes, charwidth, bitpos;

  gcc_assert (വൃക്ഷം_CODE (constructor_type) == ARRAY_TYPE);

  wchar_bytes = TYPE_PRECISION (വൃക്ഷം_TYPE (വൃക്ഷം_TYPE (str))) / BITS_PER_UNIT;
  charwidth = TYPE_PRECISION (char_type_കണ്ണി);
  gcc_assert ((size_t) wchar_bytes * charwidth
	      <= ARRAY_SIZE (val) * HOST_BITS_PER_WIDE_INT);
  type = വൃക്ഷം_TYPE (constructor_type);
  p = വൃക്ഷം_STRING_POINTER (str);
  end = p + വൃക്ഷം_STRING_LENGTH (str);

  വേണ്ടി (purpose = bitsize_zero_കണ്ണി;
       p < end
       && !(constructor_max_index
	    && വൃക്ഷം_int_cst_lt (constructor_max_index, purpose));
       purpose = size_binop (PLUS_വ്യഞ്ജകം, purpose, bitsize_one_കണ്ണി))
    {
      എങ്കിൽ (wchar_bytes == 1)
	{
	  val[0] = (unsigned അക്ഷരം) *p++;
	  val[1] = 0;
	}
      അല്ലെങ്കിൽ
	{
	  val[1] = 0;
	  val[0] = 0;
	  വേണ്ടി (byte = 0; byte < wchar_bytes; byte++)
	    {
	      എങ്കിൽ (BYTES_BIG_ENDIAN)
		bitpos = (wchar_bytes - byte - 1) * charwidth;
	      അല്ലെങ്കിൽ
		bitpos = byte * charwidth;
	      val[bitpos / HOST_BITS_PER_WIDE_INT]
		|= ((unsigned HOST_WIDE_INT) ((unsigned അക്ഷരം) *p++))
		   << (bitpos % HOST_BITS_PER_WIDE_INT);
	    }
	}

      എങ്കിൽ (!TYPE_UNSIGNED (type))
	{
	  bitpos = ((wchar_bytes - 1) * charwidth) + HOST_BITS_PER_CHAR;
	  എങ്കിൽ (bitpos < HOST_BITS_PER_WIDE_INT)
	    {
	      എങ്കിൽ (val[0] & (HOST_WIDE_INT_1 << (bitpos - 1)))
		{
		  val[0] |= HOST_WIDE_INT_M1U << bitpos;
		  val[1] = -1;
		}
	    }
	  അല്ലെങ്കിൽ എങ്കിൽ (bitpos == HOST_BITS_PER_WIDE_INT)
	    {
	      എങ്കിൽ (val[0] < 0)
		val[1] = -1;
	    }
	  അല്ലെങ്കിൽ എങ്കിൽ (val[1] & (HOST_WIDE_INT_1
			     << (bitpos - 1 - HOST_BITS_PER_WIDE_INT)))
	    val[1] |= HOST_WIDE_INT_M1U << (bitpos - HOST_BITS_PER_WIDE_INT);
	}

      മൂല്യം = wide_int_to_വൃക്ഷം (type,
				wide_int::from_array (val, 2,
						      HOST_BITS_PER_WIDE_INT * 2));
      add_pending_init (നിവേശം_location, purpose, മൂല്യം, NULL_വൃക്ഷം, സത്യം,
                        braced_init_obstack);
    }

  constructor_incremental = 0;
}

/* Return value of FIELD in pending initializer or NULL_TREE if the field was
   not initialized yet.  */

സ്ഥിതം വൃക്ഷം
find_init_member (വൃക്ഷം field, ഘടന obstack * braced_init_obstack)
{
  ഘടന init_കണ്ണി *p;

  എങ്കിൽ (വൃക്ഷം_CODE (constructor_type) == ARRAY_TYPE)
    {
      എങ്കിൽ (constructor_incremental
	  && വൃക്ഷം_int_cst_lt (field, constructor_unfilled_index))
	set_nonincremental_init (braced_init_obstack);

      p = constructor_pending_elts;
      ആകുമ്പോൾ (p)
	{
	  എങ്കിൽ (വൃക്ഷം_int_cst_lt (field, p->purpose))
	    p = p->ഇടത്;
	  അല്ലെങ്കിൽ എങ്കിൽ (വൃക്ഷം_int_cst_lt (p->purpose, field))
	    p = p->വലത്;
	  അല്ലെങ്കിൽ
	    തിരികെ p->മൂല്യം;
	}
    }
  അല്ലെങ്കിൽ എങ്കിൽ (വൃക്ഷം_CODE (constructor_type) == RECORD_TYPE)
    {
      വൃക്ഷം bitpos = bit_position (field);

      എങ്കിൽ (constructor_incremental
	  && (!constructor_unfilled_fields
	      || വൃക്ഷം_int_cst_lt (bitpos,
				  bit_position (constructor_unfilled_fields))))
	set_nonincremental_init (braced_init_obstack);

      p = constructor_pending_elts;
      ആകുമ്പോൾ (p)
	{
	  എങ്കിൽ (field == p->purpose)
	    തിരികെ p->മൂല്യം;
	  അല്ലെങ്കിൽ എങ്കിൽ (വൃക്ഷം_int_cst_lt (bitpos, bit_position (p->purpose)))
	    p = p->ഇടത്;
	  അല്ലെങ്കിൽ
	    p = p->വലത്;
	}
    }
  അല്ലെങ്കിൽ എങ്കിൽ (വൃക്ഷം_CODE (constructor_type) == UNION_TYPE)
    {
      എങ്കിൽ (!vec_safe_is_empty (constructor_elements)
	  && (constructor_elements->last ().index == field))
	തിരികെ constructor_elements->last ().മൂല്യം;
    }
  തിരികെ NULL_വൃക്ഷം;
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

സ്ഥിതം ശൂന്യം
output_init_element (location_t loc, വൃക്ഷം മൂല്യം, വൃക്ഷം origtype,
		     തർക്കം strict_string, വൃക്ഷം type, വൃക്ഷം field, തർക്കം pending,
		     തർക്കം implicit, ഘടന obstack * braced_init_obstack)
{
  വൃക്ഷം semantic_type = NULL_വൃക്ഷം;
  തർക്കം maybe_const = സത്യം;
  തർക്കം npc, int_const_വ്യഞ്ജകം, arith_const_വ്യഞ്ജകം;

  എങ്കിൽ (type == error_mark_കണ്ണി || മൂല്യം == error_mark_കണ്ണി)
    {
      constructor_erroneous = 1;
      തിരികെ;
    }
  എങ്കിൽ (വൃക്ഷം_CODE (വൃക്ഷം_TYPE (മൂല്യം)) == ARRAY_TYPE
      && (വൃക്ഷം_CODE (മൂല്യം) == STRING_CST
	  || വൃക്ഷം_CODE (മൂല്യം) == COMPOUND_LITERAL_വ്യഞ്ജകം)
      && !(വൃക്ഷം_CODE (മൂല്യം) == STRING_CST
	   && വൃക്ഷം_CODE (type) == ARRAY_TYPE
	   && INTEGRAL_TYPE_P (വൃക്ഷം_TYPE (type)))
      && !comptypes (TYPE_MAIN_VARIANT (വൃക്ഷം_TYPE (മൂല്യം)),
		     TYPE_MAIN_VARIANT (type)))
    മൂല്യം = array_to_pointer_conversion (നിവേശം_location, മൂല്യം);

  എങ്കിൽ (വൃക്ഷം_CODE (മൂല്യം) == COMPOUND_LITERAL_വ്യഞ്ജകം
      && require_constant_മൂല്യം && pending)
    {
      /* As an extension, allow initializing objects with static storage
	 duration with compound literals (which are then treated just as
	 the brace enclosed list they contain).  */
      എങ്കിൽ (flag_isoc99)
	pedwarn_init (loc, OPT_Wpedantic, "initializer element is not "
		      "constant");
      വൃക്ഷം decl = COMPOUND_LITERAL_വ്യഞ്ജകം_DECL (മൂല്യം);
      മൂല്യം = DECL_INITIAL (decl);
    }

  npc = null_pointer_constant_p (മൂല്യം);
  int_const_വ്യഞ്ജകം = (വൃക്ഷം_CODE (മൂല്യം) == INTEGER_CST
		    && !വൃക്ഷം_OVERFLOW (മൂല്യം)
		    && INTEGRAL_TYPE_P (വൃക്ഷം_TYPE (മൂല്യം)));
  /* Not fully determined before folding.  */
  arith_const_വ്യഞ്ജകം = സത്യം;
  എങ്കിൽ (വൃക്ഷം_CODE (മൂല്യം) == EXCESS_PRECISION_വ്യഞ്ജകം)
    {
      semantic_type = വൃക്ഷം_TYPE (മൂല്യം);
      മൂല്യം = വൃക്ഷം_OPERAND (മൂല്യം, 0);
    }
  മൂല്യം = c_fully_fold (മൂല്യം, require_constant_മൂല്യം, &maybe_const);
  /* TODO: this may not detect all cases of expressions folding to
     constants that are not arithmetic constant expressions.  */
  എങ്കിൽ (!maybe_const)
    arith_const_വ്യഞ്ജകം = അസത്യം;
  അല്ലെങ്കിൽ എങ്കിൽ (!INTEGRAL_TYPE_P (വൃക്ഷം_TYPE (മൂല്യം))
	   && വൃക്ഷം_CODE (വൃക്ഷം_TYPE (മൂല്യം)) != REAL_TYPE
	   && വൃക്ഷം_CODE (വൃക്ഷം_TYPE (മൂല്യം)) != COMPLEX_TYPE)
    arith_const_വ്യഞ്ജകം = അസത്യം;
  അല്ലെങ്കിൽ എങ്കിൽ (വൃക്ഷം_CODE (മൂല്യം) != INTEGER_CST
	   && വൃക്ഷം_CODE (മൂല്യം) != REAL_CST
	   && വൃക്ഷം_CODE (മൂല്യം) != COMPLEX_CST
	   && വൃക്ഷം_CODE (മൂല്യം) != RAW_DATA_CST)
    arith_const_വ്യഞ്ജകം = അസത്യം;
  അല്ലെങ്കിൽ എങ്കിൽ (വൃക്ഷം_OVERFLOW (മൂല്യം))
    arith_const_വ്യഞ്ജകം = അസത്യം;

  എങ്കിൽ (മൂല്യം == error_mark_കണ്ണി)
    constructor_erroneous = 1;
  അല്ലെങ്കിൽ എങ്കിൽ (!വൃക്ഷം_CONSTANT (മൂല്യം))
    constructor_constant = 0;
  അല്ലെങ്കിൽ എങ്കിൽ (!initializer_constant_valid_p (മൂല്യം,
					  വൃക്ഷം_TYPE (മൂല്യം),
					  AGGREGATE_TYPE_P (constructor_type)
					  && TYPE_REVERSE_STORAGE_ORDER
					     (constructor_type))
	   || (RECORD_OR_UNION_TYPE_P (constructor_type)
	       && DECL_C_BIT_FIELD (field)
	       && വൃക്ഷം_CODE (മൂല്യം) != INTEGER_CST))
    constructor_simple = 0;
  എങ്കിൽ (!maybe_const)
    constructor_nonconst = 1;

  /* Digest the initializer and issue any errors about incompatible
     types before issuing errors about non-constant initializers.  */
  വൃക്ഷം new_മൂല്യം = മൂല്യം;
  എങ്കിൽ (semantic_type)
    new_മൂല്യം = build1 (EXCESS_PRECISION_വ്യഞ്ജകം, semantic_type, മൂല്യം);
  /* In the case of braces around a scalar initializer, the result of
     this initializer processing goes through digest_init again at the
     outer level.  In the case of a constexpr initializer for a
     pointer, avoid converting a null pointer constant to something
     that is not a null pointer constant to avoid a spurious error
     from that second processing.  */
  എങ്കിൽ (!require_constexpr_മൂല്യം
      || !npc
      || വൃക്ഷം_CODE (constructor_type) != POINTER_TYPE)
    new_മൂല്യം = digest_init (loc,
			     RECORD_OR_UNION_TYPE_P (constructor_type)
			     ? field : constructor_fields
			     ? constructor_fields : constructor_decl,
			     type, new_മൂല്യം, origtype, npc,
			     int_const_വ്യഞ്ജകം, arith_const_വ്യഞ്ജകം, strict_string,
			     require_constant_മൂല്യം, require_constexpr_മൂല്യം);
  എങ്കിൽ (new_മൂല്യം == error_mark_കണ്ണി)
    {
      constructor_erroneous = 1;
      തിരികെ;
    }
  എങ്കിൽ (require_constant_മൂല്യം || require_constant_elements)
    constant_expression_warning (new_മൂല്യം);

  /* Proceed to check the constness of the original initializer.  */
  എങ്കിൽ (!initializer_constant_valid_p (മൂല്യം, വൃക്ഷം_TYPE (മൂല്യം)))
    {
      എങ്കിൽ (require_constant_മൂല്യം)
	{
	  error_init (loc, "initializer element is not constant");
	  മൂല്യം = error_mark_കണ്ണി;
	}
      അല്ലെങ്കിൽ എങ്കിൽ (require_constant_elements)
	pedwarn (loc, OPT_Wpedantic,
		 "initializer element is not computable at load time");
    }
  അല്ലെങ്കിൽ എങ്കിൽ (!maybe_const
	   && (require_constant_മൂല്യം || require_constant_elements))
    pedwarn_init (loc, OPT_Wpedantic,
		  "initializer element is not a constant expression");
  /* digest_init has already carried out the additional checks
     required for 'constexpr' initializers (using the information
     passed to it about whether the original initializer was certain
     kinds of constant expression), so that check does not need to be
     repeated here.  */

  /* Issue -Wc++-compat warnings about initializing a bitfield with
     enum type.  */
  എങ്കിൽ (warn_cxx_compat
      && field != NULL_വൃക്ഷം
      && വൃക്ഷം_CODE (field) == FIELD_DECL
      && DECL_BIT_FIELD_TYPE (field) != NULL_വൃക്ഷം
      && (TYPE_MAIN_VARIANT (DECL_BIT_FIELD_TYPE (field))
	  != TYPE_MAIN_VARIANT (type))
      && വൃക്ഷം_CODE (DECL_BIT_FIELD_TYPE (field)) == ENUMERAL_TYPE)
    {
      വൃക്ഷം checktype = origtype != NULL_വൃക്ഷം ? origtype : വൃക്ഷം_TYPE (മൂല്യം);
      എങ്കിൽ (checktype != error_mark_കണ്ണി
	  && (TYPE_MAIN_VARIANT (checktype)
	      != TYPE_MAIN_VARIANT (DECL_BIT_FIELD_TYPE (field))))
	warning_init (loc, OPT_Wc___compat,
		      "enum conversion in initialization is invalid in C++");
    }

  /* If this field is empty and does not have side effects (and is not at
     the end of structure), don't do anything other than checking the
     initializer.  */
  എങ്കിൽ (field
      && (വൃക്ഷം_TYPE (field) == error_mark_കണ്ണി
	  || (COMPLETE_TYPE_P (വൃക്ഷം_TYPE (field))
	      && integer_zerop (TYPE_SIZE (വൃക്ഷം_TYPE (field)))
	      && !വൃക്ഷം_SIDE_EFFECTS (new_മൂല്യം)
	      && (വൃക്ഷം_CODE (constructor_type) == ARRAY_TYPE
		  || DECL_CHAIN (field)))))
    തിരികെ;

  /* Finally, set VALUE to the initializer value digested above.  */
  മൂല്യം = new_മൂല്യം;

  /* If this element doesn't come next in sequence,
     put it on constructor_pending_elts.  */
  എങ്കിൽ (വൃക്ഷം_CODE (constructor_type) == ARRAY_TYPE
      && (!constructor_incremental
	  || !വൃക്ഷം_int_cst_equal (field, constructor_unfilled_index)
	  || (വൃക്ഷം_CODE (മൂല്യം) == RAW_DATA_CST
	      && constructor_pending_elts
	      && pending)))
    {
      എങ്കിൽ (constructor_incremental
	  && (വൃക്ഷം_int_cst_lt (field, constructor_unfilled_index)
	      || (വൃക്ഷം_CODE (മൂല്യം) == RAW_DATA_CST
		  && constructor_pending_elts
		  && pending)))
	set_nonincremental_init (braced_init_obstack);

      add_pending_init (loc, field, മൂല്യം, origtype, implicit,
			braced_init_obstack);
      തിരികെ;
    }
  അല്ലെങ്കിൽ എങ്കിൽ (വൃക്ഷം_CODE (constructor_type) == RECORD_TYPE
	   && (!constructor_incremental
	       || field != constructor_unfilled_fields))
    {
      /* We do this for records but not for unions.  In a union,
	 no matter which field is specified, it can be initialized
	 right away since it starts at the beginning of the union.  */
      എങ്കിൽ (constructor_incremental)
	{
	  എങ്കിൽ (!constructor_unfilled_fields)
	    set_nonincremental_init (braced_init_obstack);
	  അല്ലെങ്കിൽ
	    {
	      വൃക്ഷം bitpos, unfillpos;

	      bitpos = bit_position (field);
	      unfillpos = bit_position (constructor_unfilled_fields);

	      എങ്കിൽ (വൃക്ഷം_int_cst_lt (bitpos, unfillpos))
		set_nonincremental_init (braced_init_obstack);
	    }
	}

      add_pending_init (loc, field, മൂല്യം, origtype, implicit,
			braced_init_obstack);
      തിരികെ;
    }
  അല്ലെങ്കിൽ എങ്കിൽ (വൃക്ഷം_CODE (constructor_type) == UNION_TYPE
	   && !vec_safe_is_empty (constructor_elements))
    {
      എങ്കിൽ (!implicit)
	{
	  എങ്കിൽ (വൃക്ഷം_SIDE_EFFECTS (constructor_elements->last ().മൂല്യം))
	    warning_init (loc, OPT_Woverride_init_side_effects,
			  "initialized field with side-effects overwritten");
	  അല്ലെങ്കിൽ എങ്കിൽ (warn_override_init)
	    warning_init (loc, OPT_Woverride_init,
			  "initialized field overwritten");
	}

      /* We can have just one union field set.  */
      constructor_elements = ശൂന്യ;
    }

  /* Otherwise, output this element either to
     constructor_elements or to the assembler file.  */

  constructor_elt celt = {field, മൂല്യം};
  vec_safe_തള്ളുക (constructor_elements, celt);

  /* Advance the variable that indicates sequential elements output.  */
  എങ്കിൽ (വൃക്ഷം_CODE (constructor_type) == ARRAY_TYPE)
    {
      വൃക്ഷം inc = bitsize_one_കണ്ണി;
      എങ്കിൽ (മൂല്യം && വൃക്ഷം_CODE (മൂല്യം) == RAW_DATA_CST)
	inc = bitsize_int (RAW_DATA_LENGTH (മൂല്യം));
      constructor_unfilled_index
	= size_binop_loc (നിവേശം_location, PLUS_വ്യഞ്ജകം,
			  constructor_unfilled_index, inc);
    }
  അല്ലെങ്കിൽ എങ്കിൽ (വൃക്ഷം_CODE (constructor_type) == RECORD_TYPE)
    {
      constructor_unfilled_fields
	= DECL_CHAIN (constructor_unfilled_fields);

      /* Skip any nameless bit fields.  */
      ആകുമ്പോൾ (constructor_unfilled_fields != NULL_വൃക്ഷം
	     && DECL_UNNAMED_BIT_FIELD (constructor_unfilled_fields))
	constructor_unfilled_fields
	  = DECL_CHAIN (constructor_unfilled_fields);
    }
  അല്ലെങ്കിൽ എങ്കിൽ (വൃക്ഷം_CODE (constructor_type) == UNION_TYPE)
    constructor_unfilled_fields = NULL_വൃക്ഷം;

  /* Now output any pending elements which have become next.  */
  എങ്കിൽ (pending)
    output_pending_init_elements (0, braced_init_obstack);
}

/* For two FIELD_DECLs in the same chain, return -1 if field1
   comes before field2, 1 if field1 comes after field2 and
   0 if field1 == field2.  */

സ്ഥിതം പൂർണ്ണസംഖ്യ
init_field_decl_cmp (വൃക്ഷം field1, വൃക്ഷം field2)
{
  എങ്കിൽ (field1 == field2)
    തിരികെ 0;

  വൃക്ഷം bitpos1 = bit_position (field1);
  വൃക്ഷം bitpos2 = bit_position (field2);
  എങ്കിൽ (വൃക്ഷം_int_cst_equal (bitpos1, bitpos2))
    {
      /* If one of the fields has non-zero bitsize, then that
	 field must be the last one in a sequence of zero
	 sized fields, fields after it will have bigger
	 bit_position.  */
      എങ്കിൽ (വൃക്ഷം_TYPE (field1) != error_mark_കണ്ണി
	  && COMPLETE_TYPE_P (വൃക്ഷം_TYPE (field1))
	  && integer_nonzerop (വൃക്ഷം_TYPE (field1)))
	തിരികെ 1;
      എങ്കിൽ (വൃക്ഷം_TYPE (field2) != error_mark_കണ്ണി
	  && COMPLETE_TYPE_P (വൃക്ഷം_TYPE (field2))
	  && integer_nonzerop (വൃക്ഷം_TYPE (field2)))
	തിരികെ -1;
      /* Otherwise, fallback to DECL_CHAIN walk to find out
	 which field comes earlier.  Walk chains of both
	 fields, so that if field1 and field2 are close to each
	 other in either order, it is found soon even for large
	 sequences of zero sized fields.  */
      വൃക്ഷം f1 = field1, f2 = field2;
      ആകുമ്പോൾ (1)
	{
	  f1 = DECL_CHAIN (f1);
	  f2 = DECL_CHAIN (f2);
	  എങ്കിൽ (f1 == NULL_വൃക്ഷം)
	    {
	      gcc_assert (f2);
	      തിരികെ 1;
	    }
	  എങ്കിൽ (f2 == NULL_വൃക്ഷം)
	    തിരികെ -1;
	  എങ്കിൽ (f1 == field2)
	    തിരികെ -1;
	  എങ്കിൽ (f2 == field1)
	    തിരികെ 1;
	  എങ്കിൽ (!വൃക്ഷം_int_cst_equal (bit_position (f1), bitpos1))
	    തിരികെ 1;
	  എങ്കിൽ (!വൃക്ഷം_int_cst_equal (bit_position (f2), bitpos1))
	    തിരികെ -1;
	}
    }
  അല്ലെങ്കിൽ എങ്കിൽ (വൃക്ഷം_int_cst_lt (bitpos1, bitpos2))
    തിരികെ -1;
  അല്ലെങ്കിൽ
    തിരികെ 1;
}

/* Output any pending elements which have become next.
   As we output elements, constructor_unfilled_{fields,index}
   advances, which may cause other elements to become next;
   if so, they too are output.

   If ALL is 0, we return when there are
   no more pending elements to output now.

   If ALL is 1, we output space as necessary so that
   we can output all the pending elements.  */
സ്ഥിതം ശൂന്യം
output_pending_init_elements (പൂർണ്ണസംഖ്യ all, ഘടന obstack * braced_init_obstack)
{
  ഘടന init_കണ്ണി *elt = constructor_pending_elts;
  വൃക്ഷം next;

 retry:

  /* Look through the whole pending tree.
     If we find an element that should be output now,
     output it.  Otherwise, set NEXT to the element
     that comes first among those still pending.  */

  next = NULL_വൃക്ഷം;
  ആകുമ്പോൾ (elt)
    {
      എങ്കിൽ (വൃക്ഷം_CODE (constructor_type) == ARRAY_TYPE)
	{
	  എങ്കിൽ (വൃക്ഷം_int_cst_equal (elt->purpose,
				  constructor_unfilled_index))
	    output_init_element (നിവേശം_location, elt->മൂല്യം, elt->origtype,
				 സത്യം, വൃക്ഷം_TYPE (constructor_type),
				 constructor_unfilled_index, അസത്യം, അസത്യം,
				 braced_init_obstack);
	  അല്ലെങ്കിൽ എങ്കിൽ (വൃക്ഷം_int_cst_lt (constructor_unfilled_index,
				    elt->purpose))
	    {
	      /* Advance to the next smaller node.  */
	      എങ്കിൽ (elt->ഇടത്)
		elt = elt->ഇടത്;
	      അല്ലെങ്കിൽ
		{
		  /* We have reached the smallest node bigger than the
		     current unfilled index.  Fill the space first.  */
		  next = elt->purpose;
		  നിർത്തുക;
		}
	    }
	  അല്ലെങ്കിൽ
	    {
	      /* Advance to the next bigger node.  */
	      എങ്കിൽ (elt->വലത്)
		elt = elt->വലത്;
	      അല്ലെങ്കിൽ
		{
		  /* We have reached the biggest node in a subtree.  Find
		     the parent of it, which is the next bigger node.  */
		  ആകുമ്പോൾ (elt->parent && elt->parent->വലത് == elt)
		    elt = elt->parent;
		  elt = elt->parent;
		  എങ്കിൽ (elt && വൃക്ഷം_int_cst_lt (constructor_unfilled_index,
					      elt->purpose))
		    {
		      next = elt->purpose;
		      നിർത്തുക;
		    }
		}
	    }
	}
      അല്ലെങ്കിൽ എങ്കിൽ (RECORD_OR_UNION_TYPE_P (constructor_type))
	{
	  /* If the current record is complete we are done.  */
	  എങ്കിൽ (constructor_unfilled_fields == NULL_വൃക്ഷം)
	    നിർത്തുക;

	  പൂർണ്ണസംഖ്യ cmp = init_field_decl_cmp (constructor_unfilled_fields,
					 elt->purpose);
	  എങ്കിൽ (cmp == 0)
	    output_init_element (നിവേശം_location, elt->മൂല്യം, elt->origtype,
				 സത്യം, വൃക്ഷം_TYPE (elt->purpose),
				 elt->purpose, അസത്യം, അസത്യം,
				 braced_init_obstack);
	  അല്ലെങ്കിൽ എങ്കിൽ (cmp < 0)
	    {
	      /* Advance to the next smaller node.  */
	      എങ്കിൽ (elt->ഇടത്)
		elt = elt->ഇടത്;
	      അല്ലെങ്കിൽ
		{
		  /* We have reached the smallest node bigger than the
		     current unfilled field.  Fill the space first.  */
		  next = elt->purpose;
		  നിർത്തുക;
		}
	    }
	  അല്ലെങ്കിൽ
	    {
	      /* Advance to the next bigger node.  */
	      എങ്കിൽ (elt->വലത്)
		elt = elt->വലത്;
	      അല്ലെങ്കിൽ
		{
		  /* We have reached the biggest node in a subtree.  Find
		     the parent of it, which is the next bigger node.  */
		  ആകുമ്പോൾ (elt->parent && elt->parent->വലത് == elt)
		    elt = elt->parent;
		  elt = elt->parent;
		  എങ്കിൽ (elt
		      && init_field_decl_cmp (constructor_unfilled_fields,
					      elt->purpose) < 0)
		    {
		      next = elt->purpose;
		      നിർത്തുക;
		    }
		}
	    }
	}
    }

  /* Ordinarily return, but not if we want to output all
     and there are elements left.  */
  എങ്കിൽ (!(all && next != NULL_വൃക്ഷം))
    തിരികെ;

  /* If it's not incremental, just skip over the gap, so that after
     jumping to retry we will output the next successive element.  */
  എങ്കിൽ (RECORD_OR_UNION_TYPE_P (constructor_type))
    constructor_unfilled_fields = next;
  അല്ലെങ്കിൽ എങ്കിൽ (വൃക്ഷം_CODE (constructor_type) == ARRAY_TYPE)
    constructor_unfilled_index = next;

  /* ELT now points to the node in the pending tree with the next
     initializer to output.  */
  പോകുക retry;
}

/* Expression VALUE coincides with the start of type TYPE in a braced
   initializer.  Return true if we should treat VALUE as initializing
   the first element of TYPE, false if we should treat it as initializing
   TYPE as a whole.

   If the initializer is clearly invalid, the question becomes:
   which choice gives the best error message?  */

സ്ഥിതം തർക്കം
initialize_elementwise_p (വൃക്ഷം type, വൃക്ഷം മൂല്യം)
{
  എങ്കിൽ (type == error_mark_കണ്ണി || മൂല്യം == error_mark_കണ്ണി)
    തിരികെ അസത്യം;

  gcc_checking_assert (TYPE_MAIN_VARIANT (type) == type);

  വൃക്ഷം മൂല്യം_type = വൃക്ഷം_TYPE (മൂല്യം);
  എങ്കിൽ (മൂല്യം_type == error_mark_കണ്ണി)
    തിരികെ അസത്യം;

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
  എങ്കിൽ (gnu_vector_type_p (type))
    തിരികെ !VECTOR_TYPE_P (മൂല്യം_type);

  എങ്കിൽ (AGGREGATE_TYPE_P (type))
    തിരികെ !comptypes (type, TYPE_MAIN_VARIANT (മൂല്യം_type));

  തിരികെ അസത്യം;
}

/* Helper function for process_init_element.  Split first element of
   RAW_DATA_CST and save the rest to *RAW_DATA.  */

സ്ഥിതം വരിയിൽ വൃക്ഷം
maybe_split_raw_data (വൃക്ഷം മൂല്യം, വൃക്ഷം *raw_data)
{
  എങ്കിൽ (മൂല്യം == NULL_വൃക്ഷം || വൃക്ഷം_CODE (മൂല്യം) != RAW_DATA_CST)
    തിരികെ മൂല്യം;
  *raw_data = മൂല്യം;
  മൂല്യം = build_int_cst (integer_type_കണ്ണി,
			 RAW_DATA_UCHAR_ELT (*raw_data, 0));
  ++RAW_DATA_POINTER (*raw_data);
  --RAW_DATA_LENGTH (*raw_data);
  തിരികെ മൂല്യം;
}

/* Return non-zero if c_parser_initval should attempt to optimize
   large initializers into RAW_DATA_CST.  In that case return how
   many elements to optimize at most.  */

unsigned
c_maybe_optimize_large_byte_initializer (ശൂന്യം)
{
  എങ്കിൽ (!constructor_type
      || വൃക്ഷം_CODE (constructor_type) != ARRAY_TYPE
      || constructor_അട്ടി->implicit)
    തിരികെ 0;
  വൃക്ഷം elttype = TYPE_MAIN_VARIANT (വൃക്ഷം_TYPE (constructor_type));
  എങ്കിൽ (വൃക്ഷം_CODE (elttype) != INTEGER_TYPE
      && വൃക്ഷം_CODE (elttype) != BITINT_TYPE)
    തിരികെ 0;
  എങ്കിൽ (TYPE_PRECISION (elttype) != CHAR_BIT
      || constructor_അട്ടി->replacement_മൂല്യം.മൂല്യം
      || (COMPLETE_TYPE_P (constructor_type)
	  && !poly_int_വൃക്ഷം_p (TYPE_SIZE (constructor_type)))
      || constructor_range_അട്ടി)
    തിരികെ 0;
  എങ്കിൽ (constructor_max_index == NULL_വൃക്ഷം)
    തിരികെ INT_MAX;
  എങ്കിൽ (വൃക്ഷം_int_cst_le (constructor_max_index, constructor_index)
      || integer_all_onesp (constructor_max_index))
    തിരികെ 0;
  widest_int w = wi::to_widest (constructor_max_index);
  w -= wi::to_widest (constructor_index);
  w += 1;
  എങ്കിൽ (w < 64)
    തിരികെ 0;
  എങ്കിൽ (w > INT_MAX)
    തിരികെ INT_MAX;
  തിരികെ w.to_uhwi ();
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

ശൂന്യം
process_init_element (location_t loc, ഘടന c_വ്യഞ്ജകം മൂല്യം, തർക്കം implicit,
		      ഘടന obstack * braced_init_obstack)
{
  വൃക്ഷം orig_മൂല്യം = മൂല്യം.മൂല്യം;
  പൂർണ്ണസംഖ്യ string_flag
    = (orig_മൂല്യം != NULL_വൃക്ഷം && വൃക്ഷം_CODE (orig_മൂല്യം) == STRING_CST);
  തർക്കം strict_string = മൂല്യം.original_code == STRING_CST;
  തർക്കം was_designated = designator_depth != 0;
  വൃക്ഷം raw_data = NULL_വൃക്ഷം;

retry:
  designator_depth = 0;
  designator_erroneous = 0;

  എങ്കിൽ (!implicit && മൂല്യം.മൂല്യം && !integer_zerop (മൂല്യം.മൂല്യം))
    constructor_zeroinit = 0;

  /* Handle superfluous braces around string cst as in
     char x[] = {"foo"}; */
  എങ്കിൽ (constructor_type
      && !was_designated
      && വൃക്ഷം_CODE (constructor_type) == ARRAY_TYPE
      && INTEGRAL_TYPE_P (വൃക്ഷം_TYPE (constructor_type))
      && integer_zerop (constructor_unfilled_index))
    {
      എങ്കിൽ (constructor_അട്ടി->replacement_മൂല്യം.മൂല്യം)
	{
	  error_init (loc, "excess elements in %qT initializer", constructor_type);
	  തിരികെ;
	}
      അല്ലെങ്കിൽ എങ്കിൽ (string_flag)
	{
	  constructor_അട്ടി->replacement_മൂല്യം = മൂല്യം;
	  തിരികെ;
	}
    }

  എങ്കിൽ (constructor_അട്ടി->replacement_മൂല്യം.മൂല്യം != NULL_വൃക്ഷം)
    {
      error_init (loc, "excess elements in struct initializer");
      തിരികെ;
    }

  /* Ignore elements of a brace group if it is entirely superfluous
     and has already been diagnosed, or if the type is erroneous.  */
  എങ്കിൽ (constructor_type == NULL_വൃക്ഷം || constructor_type == error_mark_കണ്ണി)
    തിരികെ;

  /* Ignore elements of an initializer for a variable-size type.
     Those are diagnosed in the parser (empty initializer braces are OK).  */
  എങ്കിൽ (COMPLETE_TYPE_P (constructor_type)
      && !poly_int_വൃക്ഷം_p (TYPE_SIZE (constructor_type)))
    തിരികെ;

  എങ്കിൽ (!implicit && warn_designated_init && !was_designated
      && വൃക്ഷം_CODE (constructor_type) == RECORD_TYPE
      && lookup_attribute ("designated_init",
			   TYPE_ATTRIBUTES (constructor_type)))
    warning_init (loc,
		  OPT_Wdesignated_init,
		  "positional initialization of field "
		  "in %<struct%> declared with %<designated_init%> attribute");

  /* If we've exhausted any levels that didn't have braces,
     pop them now.  */
  ആകുമ്പോൾ (constructor_അട്ടി->implicit)
    {
      എങ്കിൽ (RECORD_OR_UNION_TYPE_P (constructor_type)
	  && constructor_fields == NULL_വൃക്ഷം)
	process_init_element (loc,
			      എടുക്കുക_init_level (loc, 1, braced_init_obstack,
					      last_init_list_comma),
			      സത്യം, braced_init_obstack);
      അല്ലെങ്കിൽ എങ്കിൽ ((വൃക്ഷം_CODE (constructor_type) == ARRAY_TYPE
		|| gnu_vector_type_p (constructor_type))
	       && constructor_max_index
	       && വൃക്ഷം_int_cst_lt (constructor_max_index,
				   constructor_index))
	process_init_element (loc,
			      എടുക്കുക_init_level (loc, 1, braced_init_obstack,
					      last_init_list_comma),
			      സത്യം, braced_init_obstack);
      അല്ലെങ്കിൽ
	നിർത്തുക;
    }

  /* In the case of [LO ... HI] = VALUE, only evaluate VALUE once.  */
  എങ്കിൽ (constructor_range_അട്ടി)
    {
      /* If value is a compound literal and we'll be just using its
	 content, don't put it into a SAVE_EXPR.  */
      എങ്കിൽ (വൃക്ഷം_CODE (മൂല്യം.മൂല്യം) != COMPOUND_LITERAL_വ്യഞ്ജകം
	  || !require_constant_മൂല്യം)
	{
	  വൃക്ഷം semantic_type = NULL_വൃക്ഷം;
	  എങ്കിൽ (വൃക്ഷം_CODE (മൂല്യം.മൂല്യം) == EXCESS_PRECISION_വ്യഞ്ജകം)
	    {
	      semantic_type = വൃക്ഷം_TYPE (മൂല്യം.മൂല്യം);
	      മൂല്യം.മൂല്യം = വൃക്ഷം_OPERAND (മൂല്യം.മൂല്യം, 0);
	    }
	  മൂല്യം.മൂല്യം = save_വ്യഞ്ജകം (മൂല്യം.മൂല്യം);
	  എങ്കിൽ (semantic_type)
	    മൂല്യം.മൂല്യം = build1 (EXCESS_PRECISION_വ്യഞ്ജകം, semantic_type,
				  മൂല്യം.മൂല്യം);
	}
    }

  ആകുമ്പോൾ (1)
    {
      എങ്കിൽ (വൃക്ഷം_CODE (constructor_type) == RECORD_TYPE)
	{
	  വൃക്ഷം fieldtype;
	  എണ്ണൽ വൃക്ഷം_code fieldcode;

	  എങ്കിൽ (constructor_fields == NULL_വൃക്ഷം)
	    {
	      pedwarn_init (loc, 0, "excess elements in struct initializer");
	      നിർത്തുക;
	    }

	  fieldtype = വൃക്ഷം_TYPE (constructor_fields);
	  എങ്കിൽ (fieldtype != error_mark_കണ്ണി)
	    fieldtype = TYPE_MAIN_VARIANT (fieldtype);
	  fieldcode = വൃക്ഷം_CODE (fieldtype);

	  /* Error for non-static initialization of a flexible array member.  */
	  എങ്കിൽ (fieldcode == ARRAY_TYPE
	      && !require_constant_മൂല്യം
	      && TYPE_SIZE (fieldtype) == NULL_വൃക്ഷം
	      && DECL_CHAIN (constructor_fields) == NULL_വൃക്ഷം)
	    {
	      error_init (loc, "non-static initialization of a flexible "
			  "array member");
	      നിർത്തുക;
	    }

	  /* Error for initialization of a flexible array member with
	     a string constant if the structure is in an array.  E.g.:
	     struct S { int x; char y[]; };
	     struct S s[] = { { 1, "foo" } };
	     is invalid.  */
	  എങ്കിൽ (string_flag
	      && fieldcode == ARRAY_TYPE
	      && constructor_depth > 1
	      && TYPE_SIZE (fieldtype) == NULL_വൃക്ഷം
	      && DECL_CHAIN (constructor_fields) == NULL_വൃക്ഷം)
	    {
	      തർക്കം in_array_p = അസത്യം;
	      വേണ്ടി (ഘടന constructor_അട്ടി *p = constructor_അട്ടി;
		   p && p->type; p = p->next)
		എങ്കിൽ (വൃക്ഷം_CODE (p->type) == ARRAY_TYPE)
		  {
		    in_array_p = സത്യം;
		    നിർത്തുക;
		  }
	      എങ്കിൽ (in_array_p)
		{
		  error_init (loc, "initialization of flexible array "
			      "member in a nested context");
		  നിർത്തുക;
		}
	    }

	  /* Accept a string constant to initialize a subarray.  */
	  എങ്കിൽ (മൂല്യം.മൂല്യം != NULL_വൃക്ഷം
	      && fieldcode == ARRAY_TYPE
	      && INTEGRAL_TYPE_P (വൃക്ഷം_TYPE (fieldtype))
	      && string_flag)
	    മൂല്യം.മൂല്യം = orig_മൂല്യം;
	  /* Otherwise, if we have come to a subaggregate,
	     and we don't have an element of its type, push into it.  */
	  അല്ലെങ്കിൽ എങ്കിൽ (മൂല്യം.മൂല്യം != NULL_വൃക്ഷം
		   && initialize_elementwise_p (fieldtype, മൂല്യം.മൂല്യം))
	    {
	      തള്ളുക_init_level (loc, 1, braced_init_obstack);
	      തുടരുക;
	    }

	  മൂല്യം.മൂല്യം = maybe_split_raw_data (മൂല്യം.മൂല്യം, &raw_data);
	  എങ്കിൽ (മൂല്യം.മൂല്യം)
	    {
	      തള്ളുക_member_name (constructor_fields);
	      output_init_element (loc, മൂല്യം.മൂല്യം, മൂല്യം.original_type,
				   strict_string, fieldtype,
				   constructor_fields, സത്യം, implicit,
				   braced_init_obstack);
	      RESTORE_SPELLING_DEPTH (constructor_depth);
	    }
	  അല്ലെങ്കിൽ
	    /* Do the bookkeeping for an element that was
	       directly output as a constructor.  */
	    {
	      /* For a record, keep track of end position of last field.  */
	      എങ്കിൽ (DECL_SIZE (constructor_fields))
		constructor_bit_index
		  = size_binop_loc (നിവേശം_location, PLUS_വ്യഞ്ജകം,
				    bit_position (constructor_fields),
				    DECL_SIZE (constructor_fields));

	      /* If the current field was the first one not yet written out,
		 it isn't now, so update.  */
	      എങ്കിൽ (constructor_unfilled_fields == constructor_fields)
		{
		  constructor_unfilled_fields = DECL_CHAIN (constructor_fields);
		  /* Skip any nameless bit fields.  */
		  ആകുമ്പോൾ (constructor_unfilled_fields != 0
			 && (DECL_UNNAMED_BIT_FIELD
			     (constructor_unfilled_fields)))
		    constructor_unfilled_fields =
		      DECL_CHAIN (constructor_unfilled_fields);
		}
	    }

	  constructor_fields = DECL_CHAIN (constructor_fields);
	  /* Skip any nameless bit fields at the beginning.  */
	  ആകുമ്പോൾ (constructor_fields != NULL_വൃക്ഷം
		 && DECL_UNNAMED_BIT_FIELD (constructor_fields))
	    constructor_fields = DECL_CHAIN (constructor_fields);
	}
      അല്ലെങ്കിൽ എങ്കിൽ (വൃക്ഷം_CODE (constructor_type) == UNION_TYPE)
	{
	  വൃക്ഷം fieldtype;
	  എണ്ണൽ വൃക്ഷം_code fieldcode;

	  എങ്കിൽ (constructor_fields == NULL_വൃക്ഷം)
	    {
	      pedwarn_init (loc, 0,
			    "excess elements in union initializer");
	      നിർത്തുക;
	    }

	  fieldtype = വൃക്ഷം_TYPE (constructor_fields);
	  എങ്കിൽ (fieldtype != error_mark_കണ്ണി)
	    fieldtype = TYPE_MAIN_VARIANT (fieldtype);
	  fieldcode = വൃക്ഷം_CODE (fieldtype);

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
	  എങ്കിൽ (!in_system_header_at (നിവേശം_location) && !constructor_designated
	      && !(മൂല്യം.മൂല്യം && (integer_zerop (മൂല്യം.മൂല്യം)
				   || real_zerop (മൂല്യം.മൂല്യം))))
	    warning (OPT_Wtraditional, "traditional C rejects initialization "
		     "of unions");

	  /* Error for non-static initialization of a flexible array member.  */
	  എങ്കിൽ (fieldcode == ARRAY_TYPE
	      && !require_constant_മൂല്യം
	      && TYPE_SIZE (fieldtype) == NULL_വൃക്ഷം)
	    {
	      error_init (loc, "non-static initialization of a flexible "
			  "array member");
	      നിർത്തുക;
	    }

	  /* Error for initialization of a flexible array member with
	     a string constant if the structure is in an array.  E.g.:
	     union U { int x; char y[]; };
	     union U s[] = { { 1, "foo" } };
	     is invalid.  */
	  എങ്കിൽ (string_flag
	      && fieldcode == ARRAY_TYPE
	      && constructor_depth > 1
	      && TYPE_SIZE (fieldtype) == NULL_വൃക്ഷം)
	    {
	      തർക്കം in_array_p = അസത്യം;
	      വേണ്ടി (ഘടന constructor_അട്ടി *p = constructor_അട്ടി;
		   p && p->type; p = p->next)
		എങ്കിൽ (വൃക്ഷം_CODE (p->type) == ARRAY_TYPE)
		  {
		    in_array_p = സത്യം;
		    നിർത്തുക;
		  }
	      എങ്കിൽ (in_array_p)
		{
		  error_init (loc, "initialization of flexible array "
			      "member in a nested context");
		  നിർത്തുക;
		}
	    }

	  /* Accept a string constant to initialize a subarray.  */
	  എങ്കിൽ (മൂല്യം.മൂല്യം != NULL_വൃക്ഷം
	      && fieldcode == ARRAY_TYPE
	      && INTEGRAL_TYPE_P (വൃക്ഷം_TYPE (fieldtype))
	      && string_flag)
	    മൂല്യം.മൂല്യം = orig_മൂല്യം;
	  /* Otherwise, if we have come to a subaggregate,
	     and we don't have an element of its type, push into it.  */
	  അല്ലെങ്കിൽ എങ്കിൽ (മൂല്യം.മൂല്യം != NULL_വൃക്ഷം
		   && initialize_elementwise_p (fieldtype, മൂല്യം.മൂല്യം))
	    {
	      തള്ളുക_init_level (loc, 1, braced_init_obstack);
	      തുടരുക;
	    }

	  മൂല്യം.മൂല്യം = maybe_split_raw_data (മൂല്യം.മൂല്യം, &raw_data);
	  എങ്കിൽ (മൂല്യം.മൂല്യം)
	    {
	      തള്ളുക_member_name (constructor_fields);
	      output_init_element (loc, മൂല്യം.മൂല്യം, മൂല്യം.original_type,
				   strict_string, fieldtype,
				   constructor_fields, സത്യം, implicit,
				   braced_init_obstack);
	      RESTORE_SPELLING_DEPTH (constructor_depth);
	    }
	  അല്ലെങ്കിൽ
	    /* Do the bookkeeping for an element that was
	       directly output as a constructor.  */
	    {
	      constructor_bit_index = DECL_SIZE (constructor_fields);
	      constructor_unfilled_fields = DECL_CHAIN (constructor_fields);
	    }

	  constructor_fields = NULL_വൃക്ഷം;
	}
      അല്ലെങ്കിൽ എങ്കിൽ (വൃക്ഷം_CODE (constructor_type) == ARRAY_TYPE)
	{
	  വൃക്ഷം elttype = TYPE_MAIN_VARIANT (വൃക്ഷം_TYPE (constructor_type));
	  എണ്ണൽ വൃക്ഷം_code eltcode = വൃക്ഷം_CODE (elttype);

	  /* Accept a string constant to initialize a subarray.  */
	  എങ്കിൽ (മൂല്യം.മൂല്യം != NULL_വൃക്ഷം
	      && eltcode == ARRAY_TYPE
	      && INTEGRAL_TYPE_P (വൃക്ഷം_TYPE (elttype))
	      && string_flag)
	    മൂല്യം.മൂല്യം = orig_മൂല്യം;
	  /* Otherwise, if we have come to a subaggregate,
	     and we don't have an element of its type, push into it.  */
	  അല്ലെങ്കിൽ എങ്കിൽ (മൂല്യം.മൂല്യം != NULL_വൃക്ഷം
		   && initialize_elementwise_p (elttype, മൂല്യം.മൂല്യം))
	    {
	      തള്ളുക_init_level (loc, 1, braced_init_obstack);
	      തുടരുക;
	    }

	  എങ്കിൽ (constructor_max_index != NULL_വൃക്ഷം
	      && (വൃക്ഷം_int_cst_lt (constructor_max_index, constructor_index)
		  || integer_all_onesp (constructor_max_index))
	      /* For VLA we got an error already.  */
	      && !C_TYPE_VARIABLE_SIZE (constructor_type))
	    {
	      pedwarn_init (loc, 0,
			    "excess elements in array initializer");
	      നിർത്തുക;
	    }

	  എങ്കിൽ (മൂല്യം.മൂല്യം
	      && വൃക്ഷം_CODE (മൂല്യം.മൂല്യം) == RAW_DATA_CST
	      && RAW_DATA_LENGTH (മൂല്യം.മൂല്യം) > 1
	      && (വൃക്ഷം_CODE (elttype) == INTEGER_TYPE
		  || വൃക്ഷം_CODE (elttype) == BITINT_TYPE)
	      && TYPE_PRECISION (elttype) == CHAR_BIT
	      && (constructor_max_index == NULL_വൃക്ഷം
		  || വൃക്ഷം_int_cst_lt (constructor_index,
				      constructor_max_index)))
	    {
	      unsigned പൂർണ്ണസംഖ്യ len = RAW_DATA_LENGTH (മൂല്യം.മൂല്യം);
	      എങ്കിൽ (constructor_max_index)
		{
		  widest_int w = wi::to_widest (constructor_max_index);
		  w -= wi::to_widest (constructor_index);
		  w += 1;
		  എങ്കിൽ (w < len)
		    len = w.to_uhwi ();
		}
	      എങ്കിൽ (len < (unsigned) RAW_DATA_LENGTH (മൂല്യം.മൂല്യം))
		{
		  raw_data = copy_കണ്ണി (മൂല്യം.മൂല്യം);
		  RAW_DATA_LENGTH (raw_data) -= len;
		  RAW_DATA_POINTER (raw_data) += len;
		  RAW_DATA_LENGTH (മൂല്യം.മൂല്യം) = len;
		}
	      വൃക്ഷം_TYPE (മൂല്യം.മൂല്യം) = elttype;
	      തള്ളുക_array_bounds (വൃക്ഷം_to_uhwi (constructor_index));
	      output_init_element (loc, മൂല്യം.മൂല്യം, മൂല്യം.original_type,
				   അസത്യം, elttype, constructor_index, സത്യം,
				   implicit, braced_init_obstack);
	      RESTORE_SPELLING_DEPTH (constructor_depth);
	      constructor_index
		= size_binop_loc (നിവേശം_location, PLUS_വ്യഞ്ജകം,
				  constructor_index, bitsize_int (len));
	    }
	  അല്ലെങ്കിൽ
	    {
	      മൂല്യം.മൂല്യം = maybe_split_raw_data (മൂല്യം.മൂല്യം, &raw_data);
	      /* Now output the actual element.  */
	      എങ്കിൽ (മൂല്യം.മൂല്യം)
		{
		  തള്ളുക_array_bounds (വൃക്ഷം_to_uhwi (constructor_index));
		  output_init_element (loc, മൂല്യം.മൂല്യം, മൂല്യം.original_type,
				       strict_string, elttype,
				       constructor_index, സത്യം, implicit,
				       braced_init_obstack);
		  RESTORE_SPELLING_DEPTH (constructor_depth);
		}

	      constructor_index
		= size_binop_loc (നിവേശം_location, PLUS_വ്യഞ്ജകം,
				  constructor_index, bitsize_one_കണ്ണി);

	      എങ്കിൽ (!മൂല്യം.മൂല്യം)
		/* If we are doing the bookkeeping for an element that was
		   directly output as a constructor, we must update
		   constructor_unfilled_index.  */
		constructor_unfilled_index = constructor_index;
	    }
	}
      അല്ലെങ്കിൽ എങ്കിൽ (gnu_vector_type_p (constructor_type))
	{
	  വൃക്ഷം elttype = TYPE_MAIN_VARIANT (വൃക്ഷം_TYPE (constructor_type));

	  /* Do a basic check of initializer size.  Note that vectors
	     may not always have a fixed size derived from their type.  */
	  എങ്കിൽ (maybe_lt (വൃക്ഷം_to_poly_uint64 (constructor_max_index),
			വൃക്ഷം_to_poly_uint64 (constructor_index)))
	    {
	      /* Diagose VLA out-of-bounds as errors.  */
	      എങ്കിൽ (വൃക്ഷം_to_poly_uint64 (constructor_max_index).is_constant())
		pedwarn_init (loc, 0,
			      "excess elements in vector initializer");
	      അല്ലെങ്കിൽ
		error_init (loc, "excess elements in vector initializer");

	      നിർത്തുക;
	    }

	  മൂല്യം.മൂല്യം = maybe_split_raw_data (മൂല്യം.മൂല്യം, &raw_data);
	  /* Now output the actual element.  */
	  എങ്കിൽ (മൂല്യം.മൂല്യം)
	    {
	      എങ്കിൽ (വൃക്ഷം_CODE (മൂല്യം.മൂല്യം) == VECTOR_CST)
		elttype = TYPE_MAIN_VARIANT (constructor_type);
	      output_init_element (loc, മൂല്യം.മൂല്യം, മൂല്യം.original_type,
				   strict_string, elttype,
				   constructor_index, സത്യം, implicit,
				   braced_init_obstack);
	    }

	  constructor_index
	    = size_binop_loc (നിവേശം_location,
			      PLUS_വ്യഞ്ജകം, constructor_index, bitsize_one_കണ്ണി);

	  എങ്കിൽ (!മൂല്യം.മൂല്യം)
	    /* If we are doing the bookkeeping for an element that was
	       directly output as a constructor, we must update
	       constructor_unfilled_index.  */
	    constructor_unfilled_index = constructor_index;
	}

      /* Handle the sole element allowed in a braced initializer
	 for a scalar variable.  */
      അല്ലെങ്കിൽ എങ്കിൽ (constructor_type != error_mark_കണ്ണി
	       && constructor_fields == NULL_വൃക്ഷം)
	{
	  pedwarn_init (loc, 0,
			"excess elements in scalar initializer");
	  നിർത്തുക;
	}
      അല്ലെങ്കിൽ
	{
	  മൂല്യം.മൂല്യം = maybe_split_raw_data (മൂല്യം.മൂല്യം, &raw_data);
	  എങ്കിൽ (മൂല്യം.മൂല്യം)
	    output_init_element (loc, മൂല്യം.മൂല്യം, മൂല്യം.original_type,
				 strict_string, constructor_type,
				 NULL_വൃക്ഷം, സത്യം, implicit,
				 braced_init_obstack);
	  constructor_fields = NULL_വൃക്ഷം;
	}

      /* Handle range initializers either at this level or anywhere higher
	 in the designator stack.  */
      എങ്കിൽ (constructor_range_അട്ടി)
	{
	  ഘടന constructor_range_അട്ടി *p, *range_അട്ടി;
	  പൂർണ്ണസംഖ്യ finish = 0;

	  range_അട്ടി = constructor_range_അട്ടി;
	  constructor_range_അട്ടി = 0;
	  ആകുമ്പോൾ (constructor_അട്ടി != range_അട്ടി->അട്ടി)
	    {
	      gcc_assert (constructor_അട്ടി->implicit);
	      process_init_element (loc,
				    എടുക്കുക_init_level (loc, 1,
						    braced_init_obstack,
						    last_init_list_comma),
				    സത്യം, braced_init_obstack);
	    }
	  വേണ്ടി (p = range_അട്ടി;
	       !p->range_end || വൃക്ഷം_int_cst_equal (p->index, p->range_end);
	       p = p->prev)
	    {
	      gcc_assert (constructor_അട്ടി->implicit);
	      process_init_element (loc,
				    എടുക്കുക_init_level (loc, 1,
						    braced_init_obstack,
						    last_init_list_comma),
				    സത്യം, braced_init_obstack);
	    }

	  p->index = size_binop_loc (നിവേശം_location,
				     PLUS_വ്യഞ്ജകം, p->index, bitsize_one_കണ്ണി);
	  എങ്കിൽ (വൃക്ഷം_int_cst_equal (p->index, p->range_end) && !p->prev)
	    finish = 1;

	  ആകുമ്പോൾ (1)
	    {
	      constructor_index = p->index;
	      constructor_fields = p->fields;
	      എങ്കിൽ (finish && p->range_end && p->index == p->range_start)
		{
		  finish = 0;
		  p->prev = 0;
		}
	      p = p->next;
	      എങ്കിൽ (!p)
		നിർത്തുക;
	      finish_implicit_inits (loc, braced_init_obstack);
	      തള്ളുക_init_level (loc, 2, braced_init_obstack);
	      p->അട്ടി = constructor_അട്ടി;
	      എങ്കിൽ (p->range_end && വൃക്ഷം_int_cst_equal (p->index, p->range_end))
		p->index = p->range_start;
	    }

	  എങ്കിൽ (!finish)
	    constructor_range_അട്ടി = range_അട്ടി;
	  തുടരുക;
	}

      നിർത്തുക;
    }

  constructor_range_അട്ടി = 0;

  എങ്കിൽ (raw_data && RAW_DATA_LENGTH (raw_data))
    {
      gcc_assert (!string_flag && !was_designated);
      മൂല്യം.മൂല്യം = raw_data;
      raw_data = NULL_വൃക്ഷം;
      പോകുക retry;
    }
}

/* Build a complete asm-statement, whose components are a CV_QUALIFIER
   (guaranteed to be 'volatile' or null) and ARGS (represented using
   an ASM_EXPR node).  */
വൃക്ഷം
build_asm_stmt (തർക്കം is_volatile, വൃക്ഷം args)
{
  എങ്കിൽ (is_volatile)
    ASM_VOLATILE_P (args) = 1;
  തിരികെ add_stmt (args);
}

/* Build an asm-expr, whose components are a STRING, some OUTPUTS,
   some INPUTS, and some CLOBBERS.  The latter three may be NULL.
   SIMPLE indicates whether there was anything at all after the
   string in the asm expression -- asm("blah") and asm("blah" : )
   are subtly different.  We use a ASM_EXPR node to represent this.
   LOC is the location of the asm, and IS_INLINE says whether this
   is asm inline.  */
വൃക്ഷം
build_asm_വ്യഞ്ജകം (location_t loc, വൃക്ഷം string, വൃക്ഷം outputs, വൃക്ഷം inputs,
		വൃക്ഷം clobbers, വൃക്ഷം labels, തർക്കം simple, തർക്കം is_inline)
{
  വൃക്ഷം tail;
  വൃക്ഷം args;
  പൂർണ്ണസംഖ്യ i;
  സ്ഥിരം അക്ഷരം *constraint;
  സ്ഥിരം അക്ഷരം **oconstraints;
  തർക്കം allows_mem, allows_reg, is_inout;
  പൂർണ്ണസംഖ്യ ninputs, noutputs;

  ninputs = list_length (inputs);
  noutputs = list_length (outputs);
  oconstraints = (സ്ഥിരം അക്ഷരം **) alloca (noutputs * വലുപ്പം (സ്ഥിരം അക്ഷരം *));

  string = resolve_asm_operand_names (string, outputs, inputs, labels);

  /* Remove output conversions that change the type but not the mode.  */
  വേണ്ടി (i = 0, tail = outputs; tail; ++i, tail = വൃക്ഷം_CHAIN (tail))
    {
      വൃക്ഷം output = വൃക്ഷം_മൂല്യം (tail);

      output = c_fully_fold (output, അസത്യം, ശൂന്യ, സത്യം);

      /* ??? Really, this should not be here.  Users should be using a
	 proper lvalue, dammit.  But there's a long history of using casts
	 in the output operands.  In cases like longlong.h, this becomes a
	 primitive form of typechecking -- if the cast can be removed, then
	 the output operand had a type of the proper width; otherwise we'll
	 get an error.  Gross, but ...  */
      STRIP_NOPS (output);

      എങ്കിൽ (!lvalue_or_else (loc, output, lv_asm))
	output = error_mark_കണ്ണി;

      എങ്കിൽ (output != error_mark_കണ്ണി
	  && (വൃക്ഷം_READONLY (output)
	      || TYPE_READONLY (വൃക്ഷം_TYPE (output))
	      || (RECORD_OR_UNION_TYPE_P (വൃക്ഷം_TYPE (output))
		  && C_TYPE_FIELDS_READONLY (വൃക്ഷം_TYPE (output)))))
	readonly_error (loc, output, lv_asm);

      constraint = വൃക്ഷം_STRING_POINTER (വൃക്ഷം_മൂല്യം (വൃക്ഷം_PURPOSE (tail)));
      oconstraints[i] = constraint;

      എങ്കിൽ (parse_output_constraint (&constraint, i, ninputs, noutputs,
				   &allows_mem, &allows_reg, &is_inout,
				   nullptr))
	{
	  /* If the operand is going to end up in memory,
	     mark it addressable.  */
	  എങ്കിൽ (!allows_reg && !c_mark_addressable (output))
	    output = error_mark_കണ്ണി;
	  എങ്കിൽ (!(!allows_reg && allows_mem)
	      && output != error_mark_കണ്ണി
	      && VOID_TYPE_P (വൃക്ഷം_TYPE (output)))
	    {
	      error_at (loc, "invalid use of void expression");
	      output = error_mark_കണ്ണി;
	    }
	  എങ്കിൽ (allows_reg && current_function_decl == NULL_വൃക്ഷം)
	    {
	      error_at (loc, "constraint allows registers outside of "
			     "a function");
	      output = error_mark_കണ്ണി;
	    }
	}
      അല്ലെങ്കിൽ
	output = error_mark_കണ്ണി;

      എങ്കിൽ (current_function_decl == NULL_വൃക്ഷം && output != error_mark_കണ്ണി)
	{
	  എങ്കിൽ (വൃക്ഷം_SIDE_EFFECTS (output))
	    {
	      error_at (loc, "side-effects in output operand outside "
			     "of a function");
	      output = error_mark_കണ്ണി;
	    }
	  അല്ലെങ്കിൽ
	    {
	      വൃക്ഷം addr = build_unary_op (loc, ADDR_വ്യഞ്ജകം, output, അസത്യം);
	      എങ്കിൽ (addr == error_mark_കണ്ണി)
		output = error_mark_കണ്ണി;
	      അല്ലെങ്കിൽ എങ്കിൽ (!initializer_constant_valid_p (addr, വൃക്ഷം_TYPE (addr)))
		{
		  error_at (loc, "output operand outside of a function is not "
				 "constant");
		  output = error_mark_കണ്ണി;
		}
	    }
	}
      അല്ലെങ്കിൽ എങ്കിൽ (output != error_mark_കണ്ണി && strstr (constraint, "-"))
	{
	  error_at (loc, "%<-%> modifier used inside of a function");
	  output = error_mark_കണ്ണി;
	}

      വൃക്ഷം_മൂല്യം (tail) = output;
    }

  വേണ്ടി (i = 0, tail = inputs; tail; ++i, tail = വൃക്ഷം_CHAIN (tail))
    {
      വൃക്ഷം നിവേശം;

      constraint = വൃക്ഷം_STRING_POINTER (വൃക്ഷം_മൂല്യം (വൃക്ഷം_PURPOSE (tail)));
      നിവേശം = വൃക്ഷം_മൂല്യം (tail);

      എങ്കിൽ (parse_നിവേശം_constraint (&constraint, i, ninputs, noutputs, 0,
				  oconstraints, &allows_mem, &allows_reg,
				  nullptr))
	{
	  /* If the operand is going to end up in memory,
	     mark it addressable.  */
	  എങ്കിൽ (!allows_reg && allows_mem)
	    {
	      നിവേശം = c_fully_fold (നിവേശം, അസത്യം, ശൂന്യ, സത്യം);

	      /* Strip the nops as we allow this case.  FIXME, this really
		 should be rejected or made deprecated.  */
	      STRIP_NOPS (നിവേശം);
	      എങ്കിൽ (!c_mark_addressable (നിവേശം))
		നിവേശം = error_mark_കണ്ണി;
	    }
	  അല്ലെങ്കിൽ
	    {
	      നിവേശം = c_fully_fold (convert_lvalue_to_rvalue (loc, നിവേശം,
							      സത്യം, അസത്യം),
				    അസത്യം, ശൂന്യ);

	      എങ്കിൽ (നിവേശം != error_mark_കണ്ണി && VOID_TYPE_P (വൃക്ഷം_TYPE (നിവേശം)))
		{
		  error_at (loc, "invalid use of void expression");
		  നിവേശം = error_mark_കണ്ണി;
		}
	    }
	  എങ്കിൽ (allows_reg && current_function_decl == NULL_വൃക്ഷം)
	    {
	      error_at (loc, "constraint allows registers outside of "
			     "a function");
	      നിവേശം = error_mark_കണ്ണി;
	    }
	  എങ്കിൽ (constraint[0] == ':' && നിവേശം != error_mark_കണ്ണി)
	    {
	      വൃക്ഷം t = നിവേശം;
	      STRIP_NOPS (t);
	      എങ്കിൽ (വൃക്ഷം_CODE (t) != ADDR_വ്യഞ്ജകം
		  || !(വൃക്ഷം_CODE (വൃക്ഷം_OPERAND (t, 0)) == FUNCTION_DECL
		       || (VAR_P (വൃക്ഷം_OPERAND (t, 0))
			   && is_global_var (വൃക്ഷം_OPERAND (t, 0)))))
		{
		  error_at (loc, "%<:%> constraint operand is not address "
				 "of a function or non-automatic variable");
		  നിവേശം = error_mark_കണ്ണി;
		}
	      അല്ലെങ്കിൽ എങ്കിൽ (വൃക്ഷം_CODE (വൃക്ഷം_OPERAND (t, 0)) == FUNCTION_DECL)
		suppress_warning (വൃക്ഷം_OPERAND (t, 0), OPT_Wunused);
	    }
	}
      അല്ലെങ്കിൽ
	നിവേശം = error_mark_കണ്ണി;

      എങ്കിൽ (current_function_decl == NULL_വൃക്ഷം && നിവേശം != error_mark_കണ്ണി)
	{
	  എങ്കിൽ (വൃക്ഷം_SIDE_EFFECTS (നിവേശം))
	    {
	      error_at (loc, "side-effects in input operand outside "
			     "of a function");
	      നിവേശം = error_mark_കണ്ണി;
	    }
	  അല്ലെങ്കിൽ
	    {
	      വൃക്ഷം tem = നിവേശം;
	      എങ്കിൽ (allows_mem && lvalue_p (നിവേശം))
		tem = build_unary_op (loc, ADDR_വ്യഞ്ജകം, നിവേശം, അസത്യം);
	      എങ്കിൽ (!initializer_constant_valid_p (tem, വൃക്ഷം_TYPE (tem)))
		{
		  error_at (loc, "input operand outside of a function is not "
				 "constant");
		  നിവേശം = error_mark_കണ്ണി;
		}
	    }
	}
      അല്ലെങ്കിൽ എങ്കിൽ (നിവേശം != error_mark_കണ്ണി && strstr (constraint, "-"))
	{
	  error_at (loc, "%<-%> modifier used inside of a function");
	  നിവേശം = error_mark_കണ്ണി;
	}

      വൃക്ഷം_മൂല്യം (tail) = നിവേശം;
    }

  args = build_stmt (loc, ASM_വ്യഞ്ജകം, string, outputs, inputs, clobbers, labels);

  /* asm statements without outputs, including simple ones, are treated
     as volatile.  */
  ASM_BASIC_P (args) = simple;
  ASM_VOLATILE_P (args) = (noutputs == 0);
  ASM_INLINE_P (args) = is_inline;

  തിരികെ args;
}

/* Generate a goto statement to LABEL.  LOC is the location of the
   GOTO.  */

വൃക്ഷം
c_finish_goto_label (location_t loc, വൃക്ഷം label)
{
  വൃക്ഷം decl = lookup_label_for_goto (loc, label);
  എങ്കിൽ (!decl)
    തിരികെ NULL_വൃക്ഷം;
  വൃക്ഷം_USED (decl) = 1;
  mark_decl_used (decl, അസത്യം);
  {
    add_stmt (build_predict_വ്യഞ്ജകം (PRED_GOTO, NOT_TAKEN));
    വൃക്ഷം t = build1 (GOTO_വ്യഞ്ജകം, void_type_കണ്ണി, decl);
    SET_വ്യഞ്ജകം_LOCATION (t, loc);
    തിരികെ add_stmt (t);
  }
}

/* Generate a computed goto statement to EXPR.  LOC is the location of
   the GOTO.  */

വൃക്ഷം
c_finish_goto_ptr (location_t loc, c_വ്യഞ്ജകം val)
{
  വൃക്ഷം വ്യഞ്ജകം = val.മൂല്യം;
  വൃക്ഷം t;
  pedwarn (loc, OPT_Wpedantic, "ISO C forbids %<goto *expr;%>");
  എങ്കിൽ (വ്യഞ്ജകം != error_mark_കണ്ണി
      && !POINTER_TYPE_P (വൃക്ഷം_TYPE (വ്യഞ്ജകം))
      && !null_pointer_constant_p (വ്യഞ്ജകം))
    {
      error_at (val.get_location (),
		"computed goto must be pointer type");
      വ്യഞ്ജകം = build_zero_cst (ptr_type_കണ്ണി);
    }
  വ്യഞ്ജകം = c_fully_fold (വ്യഞ്ജകം, അസത്യം, ശൂന്യ);
  വ്യഞ്ജകം = convert (ptr_type_കണ്ണി, വ്യഞ്ജകം);
  t = build1 (GOTO_വ്യഞ്ജകം, void_type_കണ്ണി, വ്യഞ്ജകം);
  SET_വ്യഞ്ജകം_LOCATION (t, loc);
  തിരികെ add_stmt (t);
}

/* Generate a C `return' statement.  RETVAL is the expression for what
   to return, or a null pointer for `return;' with no value.  LOC is
   the location of the return statement, or the location of the expression,
   if the statement has any.  If ORIGTYPE is not NULL_TREE, it
   is the original type of RETVAL.  MUSTTAIL_P indicates a musttail
   attribute.  */

വൃക്ഷം
c_finish_return (location_t loc, വൃക്ഷം retval, വൃക്ഷം origtype, തർക്കം musttail_p)
{
  വൃക്ഷം valtype = വൃക്ഷം_TYPE (വൃക്ഷം_TYPE (current_function_decl)), ret_stmt;
  തർക്കം no_warning = അസത്യം;
  തർക്കം npc = അസത്യം;

  /* Use the expansion point to handle cases such as returning NULL
     in a function returning void.  */
  location_t xloc = expansion_point_location_if_in_system_header (loc);

  എങ്കിൽ (വൃക്ഷം_THIS_VOLATILE (current_function_decl))
    warning_at (xloc, 0,
		"function declared %<noreturn%> has a %<return%> statement");

  set_musttail_on_return (retval, xloc, musttail_p);

  എങ്കിൽ (retval)
    {
      വൃക്ഷം semantic_type = NULL_വൃക്ഷം;
      npc = null_pointer_constant_p (retval);
      എങ്കിൽ (വൃക്ഷം_CODE (retval) == EXCESS_PRECISION_വ്യഞ്ജകം)
	{
	  semantic_type = വൃക്ഷം_TYPE (retval);
	  retval = വൃക്ഷം_OPERAND (retval, 0);
	}
      retval = c_fully_fold (retval, അസത്യം, ശൂന്യ);
      എങ്കിൽ (semantic_type
	  && valtype != NULL_വൃക്ഷം
	  && വൃക്ഷം_CODE (valtype) != VOID_TYPE)
	retval = build1 (EXCESS_PRECISION_വ്യഞ്ജകം, semantic_type, retval);
    }

  എങ്കിൽ (!retval)
    {
      current_function_returns_null = 1;
      എങ്കിൽ ((warn_return_type >= 0 || flag_isoc99)
	  && valtype != NULL_വൃക്ഷം && വൃക്ഷം_CODE (valtype) != VOID_TYPE)
	{
	  no_warning = സത്യം;
	  എങ്കിൽ (emit_diagnostic (flag_isoc99
			       ? diagnostics::kind::permerror
			       : diagnostics::kind::warning,
			       loc, OPT_Wreturn_mismatch,
			       "%<return%> with no value,"
			       " in function returning non-void"))
	    inform (DECL_SOURCE_LOCATION (current_function_decl),
		    "declared here");
	}
    }
  അല്ലെങ്കിൽ എങ്കിൽ (valtype == NULL_വൃക്ഷം || VOID_TYPE_P (valtype))
    {
      current_function_returns_null = 1;
      തർക്കം warned_here;
      എങ്കിൽ (വൃക്ഷം_CODE (വൃക്ഷം_TYPE (retval)) != VOID_TYPE)
	warned_here = permerror_opt
	  (xloc, OPT_Wreturn_mismatch,
	   "%<return%> with a value, in function returning void");
      അല്ലെങ്കിൽ
	warned_here = pedwarn
	  (xloc, OPT_Wpedantic, "ISO C forbids "
	   "%<return%> with expression, in function returning void");
      എങ്കിൽ (warned_here)
	inform (DECL_SOURCE_LOCATION (current_function_decl),
		"declared here");
    }
  അല്ലെങ്കിൽ
    {
      വൃക്ഷം t = convert_for_assignment (loc, UNKNOWN_LOCATION, valtype,
				       retval, origtype, ic_return,
				       npc, NULL_വൃക്ഷം, NULL_വൃക്ഷം, 0);
      വൃക്ഷം res = DECL_RESULT (current_function_decl);
      വൃക്ഷം inner;
      തർക്കം save;

      current_function_returns_മൂല്യം = 1;
      എങ്കിൽ (t == error_mark_കണ്ണി)
	{
	  /* Suppress -Wreturn-type for this function.  */
	  എങ്കിൽ (warn_return_type)
	    suppress_warning (current_function_decl, OPT_Wreturn_type);
	  തിരികെ NULL_വൃക്ഷം;
	}

      save = in_late_ദ്വിമാന_op;
      എങ്കിൽ (C_BOOLEAN_TYPE_P (വൃക്ഷം_TYPE (res))
	  || വൃക്ഷം_CODE (വൃക്ഷം_TYPE (res)) == COMPLEX_TYPE
	  || (SCALAR_FLOAT_TYPE_P (വൃക്ഷം_TYPE (t))
	      && (വൃക്ഷം_CODE (വൃക്ഷം_TYPE (res)) == INTEGER_TYPE
		  || വൃക്ഷം_CODE (വൃക്ഷം_TYPE (res)) == ENUMERAL_TYPE)
	      && sanitize_flags_p (SANITIZE_FLOAT_CAST)))
        in_late_ദ്വിമാന_op = സത്യം;
      inner = t = convert (വൃക്ഷം_TYPE (res), t);
      in_late_ദ്വിമാന_op = save;

      /* Strip any conversions, additions, and subtractions, and see if
	 we are returning the address of a local variable.  Warn if so.  */
      ആകുമ്പോൾ (1)
	{
	  തിരഞ്ഞെടുപ്പ് (വൃക്ഷം_CODE (inner))
	    {
	    CASE_CONVERT:
	    അവസ്ഥ NON_LVALUE_വ്യഞ്ജകം:
	    അവസ്ഥ PLUS_വ്യഞ്ജകം:
	    അവസ്ഥ POINTER_PLUS_വ്യഞ്ജകം:
	      inner = വൃക്ഷം_OPERAND (inner, 0);
	      തുടരുക;

	    അവസ്ഥ MINUS_വ്യഞ്ജകം:
	      /* If the second operand of the MINUS_EXPR has a pointer
		 type (or is converted from it), this may be valid, so
		 don't give a warning.  */
	      {
		വൃക്ഷം op1 = വൃക്ഷം_OPERAND (inner, 1);

		ആകുമ്പോൾ (!POINTER_TYPE_P (വൃക്ഷം_TYPE (op1))
		       && (CONVERT_വ്യഞ്ജകം_P (op1)
			   || വൃക്ഷം_CODE (op1) == NON_LVALUE_വ്യഞ്ജകം))
		  op1 = വൃക്ഷം_OPERAND (op1, 0);

		എങ്കിൽ (POINTER_TYPE_P (വൃക്ഷം_TYPE (op1)))
		  നിർത്തുക;

		inner = വൃക്ഷം_OPERAND (inner, 0);
		തുടരുക;
	      }

	    അവസ്ഥ ADDR_വ്യഞ്ജകം:
	      inner = വൃക്ഷം_OPERAND (inner, 0);

	      ആകുമ്പോൾ (REFERENCE_CLASS_P (inner)
		     && !INDIRECT_REF_P (inner))
		inner = വൃക്ഷം_OPERAND (inner, 0);

	      എങ്കിൽ (DECL_P (inner)
		  && !DECL_EXTERNAL (inner)
		  && DECL_CONTEXT (inner) == current_function_decl
		  && POINTER_TYPE_P (വൃക്ഷം_TYPE (വൃക്ഷം_TYPE (current_function_decl))))
		{
		  എങ്കിൽ (വൃക്ഷം_CODE (inner) == LABEL_DECL)
		    warning_at (loc, OPT_Wreturn_local_addr,
				"function returns address of label");
		  അല്ലെങ്കിൽ എങ്കിൽ (വൃക്ഷം_CODE (inner) == FUNCTION_DECL
			   && (C_FUNC_NONLOCAL_CONTEXT (inner)
			       || !DECL_INITIAL (inner)))
		    warning_at (loc, OPT_Wreturn_local_addr,
				"function returns address of nested function "
				"referencing local context");
		  അല്ലെങ്കിൽ എങ്കിൽ (വൃക്ഷം_CODE (inner) != FUNCTION_DECL
			   && !വൃക്ഷം_STATIC (inner))
		    {
		      warning_at (loc, OPT_Wreturn_local_addr,
				  "function returns address of local variable");
		      വൃക്ഷം zero = build_zero_cst (വൃക്ഷം_TYPE (res));
		      t = build2 (COMPOUND_വ്യഞ്ജകം, വൃക്ഷം_TYPE (res), t, zero);
		    }
		}
	      നിർത്തുക;

	    സ്ഥിരസ്ഥിതി:
	      നിർത്തുക;
	    }

	  നിർത്തുക;
	}

      retval = build2 (MODIFY_വ്യഞ്ജകം, വൃക്ഷം_TYPE (res), res, t);
      SET_വ്യഞ്ജകം_LOCATION (retval, loc);

      എങ്കിൽ (warn_sequence_point)
	verify_sequence_points (retval);
    }

  ret_stmt = build_stmt (loc, RETURN_വ്യഞ്ജകം, retval);
  എങ്കിൽ (no_warning)
    suppress_warning (ret_stmt, OPT_Wreturn_type);
  തിരികെ add_stmt (ret_stmt);
}

ഘടന c_switch {
  /* The SWITCH_STMT being built.  */
  വൃക്ഷം switch_stmt;

  /* The original type of the testing expression, i.e. before the
     default conversion is applied.  */
  വൃക്ഷം orig_type;

  /* A splay-tree mapping the low element of a case range to the high
     element, or NULL_TREE if there is no high element.  Used to
     determine whether or not a new case label duplicates an old case
     label.  We need a tree, rather than simply a hash table, because
     of the GNU case range extension.  */
  splay_വൃക്ഷം cases;

  /* The bindings at the point of the switch.  This is used for
     warnings crossing decls when branching to a case label.  */
  ഘടന c_spot_bindings *bindings;

  /* Whether the switch includes any break statements.  */
  തർക്കം break_stmt_seen_p;

  /* The next node on the stack.  */
  ഘടന c_switch *next;

  /* Remember whether the controlling expression had boolean type
     before integer promotions for the sake of -Wswitch-bool.  */
  തർക്കം bool_cond_p;
};

/* A stack of the currently active switch statements.  The innermost
   switch statement is on the top of the stack.  There is no need to
   mark the stack for garbage collection because it is only active
   during the processing of the body of a function, and we never
   collect at that point.  */

ഘടന c_switch *c_switch_അട്ടി;

/* Start a C switch statement, testing expression EXP.  Return the new
   SWITCH_STMT.  SWITCH_LOC is the location of the `switch'.
   SWITCH_COND_LOC is the location of the switch's condition.
   EXPLICIT_CAST_P is true if the expression EXP has an explicit cast.  */

വൃക്ഷം
c_start_switch (location_t switch_loc,
		location_t switch_cond_loc,
		വൃക്ഷം exp, തർക്കം explicit_cast_p, വൃക്ഷം switch_name)
{
  വൃക്ഷം orig_type = error_mark_കണ്ണി;
  തർക്കം bool_cond_p = അസത്യം;
  ഘടന c_switch *cs;

  എങ്കിൽ (exp != error_mark_കണ്ണി)
    {
      orig_type = വൃക്ഷം_TYPE (exp);

      എങ്കിൽ (!INTEGRAL_TYPE_P (orig_type))
	{
	  എങ്കിൽ (orig_type != error_mark_കണ്ണി)
	    {
	      error_at (switch_cond_loc, "switch quantity not an integer");
	      orig_type = error_mark_കണ്ണി;
	    }
	  exp = integer_zero_കണ്ണി;
	}
      അല്ലെങ്കിൽ
	{
	  വൃക്ഷം type = TYPE_MAIN_VARIANT (orig_type);
	  വൃക്ഷം e = exp;

	  /* Warn if the condition has boolean value.  */
	  ആകുമ്പോൾ (വൃക്ഷം_CODE (e) == COMPOUND_വ്യഞ്ജകം)
	    e = വൃക്ഷം_OPERAND (e, 1);

	  എങ്കിൽ ((C_BOOLEAN_TYPE_P (type)
	       || truth_മൂല്യം_p (വൃക്ഷം_CODE (e)))
	      /* Explicit cast to int suppresses this warning.  */
	      && !(വൃക്ഷം_CODE (type) == INTEGER_TYPE
		   && explicit_cast_p))
	    bool_cond_p = സത്യം;

	  എങ്കിൽ (!in_system_header_at (നിവേശം_location)
	      && (type == long_integer_type_കണ്ണി
		  || type == long_unsigned_type_കണ്ണി))
	    warning_at (switch_cond_loc,
			OPT_Wtraditional, "%<long%> switch expression not "
			"converted to %<int%> in ISO C");

	  exp = c_fully_fold (exp, അസത്യം, ശൂന്യ);
	  exp = default_conversion (exp);

	  എങ്കിൽ (warn_sequence_point)
	    verify_sequence_points (exp);
	}
    }

  /* Add this new SWITCH_STMT to the stack.  */
  cs = XNEW (ഘടന c_switch);
  cs->switch_stmt = build_stmt (switch_loc, SWITCH_STMT, exp,
				NULL_വൃക്ഷം, orig_type, NULL_വൃക്ഷം, switch_name);
  cs->orig_type = orig_type;
  cs->cases = splay_വൃക്ഷം_new (case_compare, ശൂന്യ, ശൂന്യ);
  cs->bindings = c_get_switch_bindings ();
  cs->break_stmt_seen_p = അസത്യം;
  cs->bool_cond_p = bool_cond_p;
  cs->next = c_switch_അട്ടി;
  c_switch_അട്ടി = cs;

  തിരികെ add_stmt (cs->switch_stmt);
}

/* Process a case label at location LOC, with attributes ATTRS.  */

വൃക്ഷം
do_case (location_t loc, വൃക്ഷം താഴെയുള്ള_മൂല്യം, വൃക്ഷം മുകളിലെ_മൂല്യം, വൃക്ഷം attrs)
{
  വൃക്ഷം label = NULL_വൃക്ഷം;

  എങ്കിൽ (താഴെയുള്ള_മൂല്യം && വൃക്ഷം_CODE (താഴെയുള്ള_മൂല്യം) != INTEGER_CST)
    {
      താഴെയുള്ള_മൂല്യം = c_fully_fold (താഴെയുള്ള_മൂല്യം, അസത്യം, ശൂന്യ);
      എങ്കിൽ (വൃക്ഷം_CODE (താഴെയുള്ള_മൂല്യം) == INTEGER_CST)
	pedwarn (loc, OPT_Wpedantic,
		 "case label is not an integer constant expression");
    }

  എങ്കിൽ (മുകളിലെ_മൂല്യം && വൃക്ഷം_CODE (മുകളിലെ_മൂല്യം) != INTEGER_CST)
    {
      മുകളിലെ_മൂല്യം = c_fully_fold (മുകളിലെ_മൂല്യം, അസത്യം, ശൂന്യ);
      എങ്കിൽ (വൃക്ഷം_CODE (മുകളിലെ_മൂല്യം) == INTEGER_CST)
	pedwarn (നിവേശം_location, OPT_Wpedantic,
		 "case label is not an integer constant expression");
    }

  എങ്കിൽ (c_switch_അട്ടി == ശൂന്യ)
    {
      എങ്കിൽ (താഴെയുള്ള_മൂല്യം)
	error_at (loc, "case label not within a switch statement");
      അല്ലെങ്കിൽ
	error_at (loc, "%<default%> label not within a switch statement");
      തിരികെ NULL_വൃക്ഷം;
    }

  എങ്കിൽ (c_check_switch_jump_warnings (c_switch_അട്ടി->bindings,
				    വ്യഞ്ജകം_LOCATION (c_switch_അട്ടി->switch_stmt),
				    loc))
    തിരികെ NULL_വൃക്ഷം;

  label = c_add_case_label (loc, c_switch_അട്ടി->cases,
			    SWITCH_STMT_COND (c_switch_അട്ടി->switch_stmt),
			    താഴെയുള്ള_മൂല്യം, മുകളിലെ_മൂല്യം, attrs);
  എങ്കിൽ (label == error_mark_കണ്ണി)
    label = NULL_വൃക്ഷം;
  തിരികെ label;
}

/* Finish the switch statement.  TYPE is the original type of the
   controlling expression of the switch, or NULL_TREE.  */

ശൂന്യം
c_finish_switch (വൃക്ഷം body, വൃക്ഷം type)
{
  ഘടന c_switch *cs = c_switch_അട്ടി;
  location_t switch_location;

  SWITCH_STMT_BODY (cs->switch_stmt) = body;

  /* Emit warnings as needed.  */
  switch_location = വ്യഞ്ജകം_LOCATION (cs->switch_stmt);
  c_do_switch_warnings (cs->cases, switch_location,
			type ? type : SWITCH_STMT_TYPE (cs->switch_stmt),
			SWITCH_STMT_COND (cs->switch_stmt), cs->bool_cond_p);
  എങ്കിൽ (c_switch_covers_all_cases_p (cs->cases,
				   SWITCH_STMT_TYPE (cs->switch_stmt)))
    SWITCH_STMT_ALL_CASES_P (cs->switch_stmt) = 1;
  SWITCH_STMT_NO_BREAK_P (cs->switch_stmt) = !cs->break_stmt_seen_p;

  /* Pop the stack.  */
  c_switch_അട്ടി = cs->next;
  splay_വൃക്ഷം_delete (cs->cases);
  c_release_switch_bindings (cs->bindings);
  XDELETE (cs);
}

/* Emit an if statement.  IF_LOCUS is the location of the 'if'.  COND,
   THEN_BLOCK and ELSE_BLOCK are expressions to be used; ELSE_BLOCK
   may be null.  */

ശൂന്യം
c_finish_if_stmt (location_t if_locus, വൃക്ഷം cond, വൃക്ഷം then_block,
		  വൃക്ഷം else_block)
{
  വൃക്ഷം stmt;

  stmt = build3 (COND_വ്യഞ്ജകം, void_type_കണ്ണി, cond, then_block, else_block);
  SET_വ്യഞ്ജകം_LOCATION (stmt, if_locus);
  add_stmt (stmt);
}

വൃക്ഷം
c_finish_bc_stmt (location_t loc, വൃക്ഷം label, തർക്കം is_break, വൃക്ഷം name)
{
  /* In switch statements break is sometimes stylistically used after
     a return statement.  This can lead to spurious warnings about
     control reaching the end of a non-void function when it is
     inlined.  Note that we are calling block_may_fallthru with
     language specific tree nodes; this works because
     block_may_fallthru returns true when given something it does not
     understand.  */
  തർക്കം skip = !block_may_fallthru (cur_stmt_list);

  എങ്കിൽ (is_break)
    തിരഞ്ഞെടുപ്പ് (in_statement & ~IN_NAMED_STMT)
      {
      അവസ്ഥ 0:
	error_at (loc, "break statement not within loop or switch");
	തിരികെ NULL_വൃക്ഷം;
      അവസ്ഥ IN_OMP_BLOCK:
	error_at (loc, "invalid exit from OpenMP structured block");
	തിരികെ NULL_വൃക്ഷം;
      അവസ്ഥ IN_OMP_FOR:
	error_at (loc, "break statement used with OpenMP for loop");
	തിരികെ NULL_വൃക്ഷം;
      അവസ്ഥ IN_ITERATION_STMT:
      അവസ്ഥ IN_OBJC_FOREACH:
	നിർത്തുക;
      സ്ഥിരസ്ഥിതി:
	gcc_assert (in_statement & IN_SWITCH_STMT);
	c_switch_അട്ടി->break_stmt_seen_p = സത്യം;
	നിർത്തുക;
      }
  അല്ലെങ്കിൽ
    തിരഞ്ഞെടുപ്പ് (in_statement & ~(IN_SWITCH_STMT | IN_NAMED_STMT))
      {
      അവസ്ഥ 0:
	error_at (loc, "continue statement not within a loop");
	തിരികെ NULL_വൃക്ഷം;
      അവസ്ഥ IN_OMP_BLOCK:
	error_at (loc, "invalid exit from OpenMP structured block");
	തിരികെ NULL_വൃക്ഷം;
      അവസ്ഥ IN_ITERATION_STMT:
      അവസ്ഥ IN_OMP_FOR:
      അവസ്ഥ IN_OBJC_FOREACH:
	നിർത്തുക;
      സ്ഥിരസ്ഥിതി:
	gcc_unreachable ();
      }

  എങ്കിൽ (skip)
    തിരികെ NULL_വൃക്ഷം;
  അല്ലെങ്കിൽ എങ്കിൽ ((in_statement & IN_OBJC_FOREACH)
	   && !(is_break && (in_statement & IN_SWITCH_STMT))
	   && name == NULL_വൃക്ഷം)
    {
      /* The foreach expander produces low-level code using gotos instead
	 of a structured loop construct.  */
      gcc_assert (label);
      തിരികെ add_stmt (build_stmt (loc, GOTO_വ്യഞ്ജകം, label));
    }
  അല്ലെങ്കിൽ എങ്കിൽ (name && C_DECL_LOOP_NAME (name) && C_DECL_SWITCH_NAME (name))
    {
      label = DECL_CHAIN (name);
      എങ്കിൽ (!is_break)
	label = DECL_CHAIN (label);
      /* Foreach expander from some outer level.  */
      തിരികെ add_stmt (build_stmt (loc, GOTO_വ്യഞ്ജകം, label));
    }
  തിരികെ add_stmt (build_stmt (loc, is_break ? BREAK_STMT : CONTINUE_STMT,
			       name));
}

/* A helper routine for c_process_expr_stmt and c_finish_stmt_expr.  */

സ്ഥിതം ശൂന്യം
emit_side_effect_warnings (location_t loc, വൃക്ഷം വ്യഞ്ജകം)
{
  maybe_warn_nodiscard (loc, വ്യഞ്ജകം);
  എങ്കിൽ (!warn_unused_മൂല്യം)
    തിരികെ;
  എങ്കിൽ (വ്യഞ്ജകം == error_mark_കണ്ണി)
    ;
  അല്ലെങ്കിൽ എങ്കിൽ (!വൃക്ഷം_SIDE_EFFECTS (വ്യഞ്ജകം))
    {
      എങ്കിൽ (!VOID_TYPE_P (വൃക്ഷം_TYPE (വ്യഞ്ജകം))
	  && !warning_suppressed_p (വ്യഞ്ജകം, OPT_Wunused_മൂല്യം))
	warning_at (loc, OPT_Wunused_മൂല്യം, "statement with no effect");
    }
  അല്ലെങ്കിൽ എങ്കിൽ (വൃക്ഷം_CODE (വ്യഞ്ജകം) == COMPOUND_വ്യഞ്ജകം)
    {
      വൃക്ഷം r = വ്യഞ്ജകം;
      location_t cloc = loc;
      ആകുമ്പോൾ (വൃക്ഷം_CODE (r) == COMPOUND_വ്യഞ്ജകം)
	{
	  എങ്കിൽ (വ്യഞ്ജകം_HAS_LOCATION (r))
	    cloc = വ്യഞ്ജകം_LOCATION (r);
	  r = വൃക്ഷം_OPERAND (r, 1);
	}
      എങ്കിൽ (!വൃക്ഷം_SIDE_EFFECTS (r)
	  && !VOID_TYPE_P (വൃക്ഷം_TYPE (r))
	  && !CONVERT_വ്യഞ്ജകം_P (r)
	  && !warning_suppressed_p (r, OPT_Wunused_മൂല്യം)
	  && !warning_suppressed_p (വ്യഞ്ജകം, OPT_Wunused_മൂല്യം))
	warning_at (cloc, OPT_Wunused_മൂല്യം,
		    "right-hand operand of comma expression has no effect");
    }
  അല്ലെങ്കിൽ
    warn_if_unused_മൂല്യം (വ്യഞ്ജകം, loc);
}

/* Process an expression as if it were a complete statement.  Emit
   diagnostics, but do not call ADD_STMT.  LOC is the location of the
   statement.  */

വൃക്ഷം
c_process_വ്യഞ്ജകം_stmt (location_t loc, വൃക്ഷം വ്യഞ്ജകം)
{
  വൃക്ഷം exprv;

  എങ്കിൽ (!വ്യഞ്ജകം)
    തിരികെ NULL_വൃക്ഷം;

  വ്യഞ്ജകം = c_fully_fold (വ്യഞ്ജകം, അസത്യം, ശൂന്യ);

  എങ്കിൽ (warn_sequence_point)
    verify_sequence_points (വ്യഞ്ജകം);

  എങ്കിൽ (വൃക്ഷം_TYPE (വ്യഞ്ജകം) != error_mark_കണ്ണി
      && !COMPLETE_OR_VOID_TYPE_P (വൃക്ഷം_TYPE (വ്യഞ്ജകം))
      && വൃക്ഷം_CODE (വൃക്ഷം_TYPE (വ്യഞ്ജകം)) != ARRAY_TYPE)
    error_at (loc, "expression statement has incomplete type");

  /* If we're not processing a statement expression, warn about unused values.
     Warnings for statement expressions will be emitted later, once we figure
     out which is the result.  */
  എങ്കിൽ (!STATEMENT_LIST_STMT_വ്യഞ്ജകം (cur_stmt_list)
      && (warn_unused_മൂല്യം || warn_unused_result))
    emit_side_effect_warnings (വ്യഞ്ജകം_LOC_OR_LOC (വ്യഞ്ജകം, loc), വ്യഞ്ജകം);

  exprv = വ്യഞ്ജകം;
  ആകുമ്പോൾ (വൃക്ഷം_CODE (exprv) == COMPOUND_വ്യഞ്ജകം)
    exprv = വൃക്ഷം_OPERAND (exprv, 1);
  ആകുമ്പോൾ (CONVERT_വ്യഞ്ജകം_P (exprv))
    exprv = വൃക്ഷം_OPERAND (exprv, 0);
  എങ്കിൽ (DECL_P (exprv)
      || handled_component_p (exprv)
      || വൃക്ഷം_CODE (exprv) == ADDR_വ്യഞ്ജകം)
    mark_exp_read (exprv);

  /* If the expression is not of a type to which we cannot assign a line
     number, wrap the thing in a no-op NOP_EXPR.  */
  എങ്കിൽ (DECL_P (വ്യഞ്ജകം) || CONSTANT_CLASS_P (വ്യഞ്ജകം))
    {
      വ്യഞ്ജകം = build1 (NOP_വ്യഞ്ജകം, വൃക്ഷം_TYPE (വ്യഞ്ജകം), വ്യഞ്ജകം);
      SET_വ്യഞ്ജകം_LOCATION (വ്യഞ്ജകം, loc);
    }

  തിരികെ വ്യഞ്ജകം;
}

/* Emit an expression as a statement.  LOC is the location of the
   expression.  */

വൃക്ഷം
c_finish_വ്യഞ്ജകം_stmt (location_t loc, വൃക്ഷം വ്യഞ്ജകം)
{
  എങ്കിൽ (വ്യഞ്ജകം)
    തിരികെ add_stmt (c_process_വ്യഞ്ജകം_stmt (loc, വ്യഞ്ജകം));
  അല്ലെങ്കിൽ
    തിരികെ ശൂന്യ;
}

/* Do the opposite and emit a statement as an expression.  To begin,
   create a new binding level and return it.  */

വൃക്ഷം
c_begin_stmt_വ്യഞ്ജകം (ശൂന്യം)
{
  വൃക്ഷം ret;

  /* We must force a BLOCK for this level so that, if it is not expanded
     later, there is a way to turn off the entire subtree of blocks that
     are contained in it.  */
  keep_next_level ();
  ret = c_begin_compound_stmt (സത്യം);

  c_bindings_start_stmt_വ്യഞ്ജകം (c_switch_അട്ടി == ശൂന്യ
			      ? ശൂന്യ
			      : c_switch_അട്ടി->bindings);

  /* Mark the current statement list as belonging to a statement list.  */
  STATEMENT_LIST_STMT_വ്യഞ്ജകം (ret) = 1;

  തിരികെ ret;
}

/* LOC is the location of the compound statement to which this body
   belongs.  */

വൃക്ഷം
c_finish_stmt_വ്യഞ്ജകം (location_t loc, വൃക്ഷം body)
{
  വൃക്ഷം last, type, tmp, val;
  വൃക്ഷം *last_p;

  body = c_end_compound_stmt (loc, body, സത്യം);

  c_bindings_end_stmt_വ്യഞ്ജകം (c_switch_അട്ടി == ശൂന്യ
			    ? ശൂന്യ
			    : c_switch_അട്ടി->bindings);

  /* Locate the last statement in BODY.  See c_end_compound_stmt
     about always returning a BIND_EXPR.  */
  last_p = &BIND_വ്യഞ്ജകം_BODY (body);
  last = BIND_വ്യഞ്ജകം_BODY (body);

 continue_searching:
  എങ്കിൽ (വൃക്ഷം_CODE (last) == STATEMENT_LIST)
    {
      വൃക്ഷം_stmt_iterator l = tsi_last (last);

      ആകുമ്പോൾ (!tsi_end_p (l) && വൃക്ഷം_CODE (tsi_stmt (l)) == DEBUG_BEGIN_STMT)
	tsi_prev (&l);

      /* This can happen with degenerate cases like ({ }).  No value.  */
      എങ്കിൽ (tsi_end_p (l))
	തിരികെ body;

      /* If we're supposed to generate side effects warnings, process
	 all of the statements except the last.  */
      എങ്കിൽ (warn_unused_മൂല്യം || warn_unused_result)
	{
	  വേണ്ടി (വൃക്ഷം_stmt_iterator i = tsi_start (last);
	       tsi_stmt (i) != tsi_stmt (l); tsi_next (&i))
	    {
	      location_t tloc;
	      വൃക്ഷം t = tsi_stmt (i);

	      tloc = വ്യഞ്ജകം_HAS_LOCATION (t) ? വ്യഞ്ജകം_LOCATION (t) : loc;
	      emit_side_effect_warnings (tloc, t);
	    }
	}
      last_p = tsi_stmt_ptr (l);
      last = *last_p;
    }

  /* If the end of the list is exception related, then the list was split
     by a call to push_cleanup.  Continue searching.  */
  എങ്കിൽ (വൃക്ഷം_CODE (last) == TRY_FINALLY_വ്യഞ്ജകം
      || വൃക്ഷം_CODE (last) == TRY_CATCH_വ്യഞ്ജകം)
    {
      last_p = &വൃക്ഷം_OPERAND (last, 0);
      last = *last_p;
      പോകുക continue_searching;
    }

  എങ്കിൽ (last == error_mark_കണ്ണി)
    തിരികെ last;

  /* In the case that the BIND_EXPR is not necessary, return the
     expression out from inside it.  */
  എങ്കിൽ ((last == BIND_വ്യഞ്ജകം_BODY (body)
       /* Skip nested debug stmts.  */
       || last == വ്യഞ്ജകം_first (BIND_വ്യഞ്ജകം_BODY (body)))
      && BIND_വ്യഞ്ജകം_VARS (body) == ശൂന്യ)
    {
      /* Even if this looks constant, do not allow it in a constant
	 expression.  */
      last = c_wrap_maybe_const (last, സത്യം);
      /* Do not warn if the return value of a statement expression is
	 unused.  */
      suppress_warning (last, OPT_Wunused);
      തിരികെ last;
    }

  /* Extract the type of said expression.  */
  type = വൃക്ഷം_TYPE (last);

  /* If we're not returning a value at all, then the BIND_EXPR that
     we already have is a fine expression to return.  */
  എങ്കിൽ (!type || VOID_TYPE_P (type))
    തിരികെ body;

  /* Now that we've located the expression containing the value, it seems
     silly to make voidify_wrapper_expr repeat the process.  Create a
     temporary of the appropriate type and stick it in a TARGET_EXPR.  */
  tmp = create_tmp_var_raw (type);

  /* Unwrap a no-op NOP_EXPR as added by c_finish_expr_stmt.  This avoids
     tree_expr_nonnegative_p giving up immediately.  */
  val = last;
  എങ്കിൽ (വൃക്ഷം_CODE (val) == NOP_വ്യഞ്ജകം
      && വൃക്ഷം_TYPE (val) == വൃക്ഷം_TYPE (വൃക്ഷം_OPERAND (val, 0)))
    val = വൃക്ഷം_OPERAND (val, 0);

  *last_p = build2 (MODIFY_വ്യഞ്ജകം, void_type_കണ്ണി, tmp, val);
  SET_വ്യഞ്ജകം_LOCATION (*last_p, വ്യഞ്ജകം_LOCATION (last));

  {
    വൃക്ഷം t = build4 (TARGET_വ്യഞ്ജകം, type, tmp, body, NULL_വൃക്ഷം, NULL_വൃക്ഷം);
    SET_വ്യഞ്ജകം_LOCATION (t, loc);
    തിരികെ t;
  }
}

/* Begin and end compound statements.  This is as simple as pushing
   and popping new statement lists from the tree.  */

വൃക്ഷം
c_begin_compound_stmt (തർക്കം do_scope)
{
  വൃക്ഷം stmt = തള്ളുക_stmt_list ();
  എങ്കിൽ (do_scope)
    തള്ളുക_scope ();
  തിരികെ stmt;
}

/* End a compound statement.  STMT is the statement.  LOC is the
   location of the compound statement-- this is usually the location
   of the opening brace.  */

വൃക്ഷം
c_end_compound_stmt (location_t loc, വൃക്ഷം stmt, തർക്കം do_scope)
{
  വൃക്ഷം block = ശൂന്യ;

  എങ്കിൽ (do_scope)
    {
      എങ്കിൽ (c_dialect_objc ())
	objc_clear_super_receiver ();
      block = എടുക്കുക_scope ();
    }

  stmt = എടുക്കുക_stmt_list (stmt);
  stmt = c_build_bind_വ്യഞ്ജകം (loc, block, stmt);

  /* If this compound statement is nested immediately inside a statement
     expression, then force a BIND_EXPR to be created.  Otherwise we'll
     do the wrong thing for ({ { 1; } }) or ({ 1; { } }).  In particular,
     STATEMENT_LISTs merge, and thus we can lose track of what statement
     was really last.  */
  എങ്കിൽ (building_stmt_list_p ()
      && STATEMENT_LIST_STMT_വ്യഞ്ജകം (cur_stmt_list)
      && വൃക്ഷം_CODE (stmt) != BIND_വ്യഞ്ജകം)
    {
      stmt = build3 (BIND_വ്യഞ്ജകം, void_type_കണ്ണി, ശൂന്യ, stmt, ശൂന്യ);
      വൃക്ഷം_SIDE_EFFECTS (stmt) = 1;
      SET_വ്യഞ്ജകം_LOCATION (stmt, loc);
    }

  തിരികെ stmt;
}

/* Queue a cleanup.  CLEANUP is an expression/statement to be executed
   when the current scope is exited.  EH_ONLY is true when this is not
   meant to apply to normal control flow transfer.  */

ശൂന്യം
തള്ളുക_cleanup (വൃക്ഷം decl, വൃക്ഷം cleanup, തർക്കം eh_only)
{
  എണ്ണൽ വൃക്ഷം_code code;
  വൃക്ഷം stmt, list;
  തർക്കം stmt_വ്യഞ്ജകം;

  code = eh_only ? TRY_CATCH_വ്യഞ്ജകം : TRY_FINALLY_വ്യഞ്ജകം;
  stmt = build_stmt (DECL_SOURCE_LOCATION (decl), code, ശൂന്യ, cleanup);
  add_stmt (stmt);
  stmt_വ്യഞ്ജകം = STATEMENT_LIST_STMT_വ്യഞ്ജകം (cur_stmt_list);
  list = തള്ളുക_stmt_list ();
  വൃക്ഷം_OPERAND (stmt, 0) = list;
  STATEMENT_LIST_STMT_വ്യഞ്ജകം (list) = stmt_വ്യഞ്ജകം;
}

/* Build a vector comparison of ARG0 and ARG1 using CODE opcode
   into a value of TYPE type.  Comparison is done via VEC_COND_EXPR.  */

സ്ഥിതം വൃക്ഷം
build_vec_cmp (വൃക്ഷം_code code, വൃക്ഷം type,
	       വൃക്ഷം arg0, വൃക്ഷം arg1)
{
  വൃക്ഷം zero_vec = build_zero_cst (type);
  വൃക്ഷം minus_one_vec = build_minus_one_cst (type);
  വൃക്ഷം cmp_type = truth_type_for (വൃക്ഷം_TYPE (arg0));
  വൃക്ഷം cmp = build2 (code, cmp_type, arg0, arg1);
  തിരികെ build3 (VEC_COND_വ്യഞ്ജകം, type, cmp, minus_one_vec, zero_vec);
}

/* Possibly warn about an address of OP never being NULL in a comparison
   operation CODE involving null.  */

സ്ഥിതം ശൂന്യം
maybe_warn_for_null_address (location_t loc, വൃക്ഷം op, വൃക്ഷം_code code)
{
  /* Prevent warnings issued for macro expansion.  */
  എങ്കിൽ (!warn_address
      || warning_suppressed_p (op, OPT_Waddress)
      || from_macro_expansion_at (loc))
    തിരികെ;

  എങ്കിൽ (വൃക്ഷം_CODE (op) == NOP_വ്യഞ്ജകം)
    {
      /* Allow casts to intptr_t to suppress the warning.  */
      വൃക്ഷം type = വൃക്ഷം_TYPE (op);
      എങ്കിൽ (വൃക്ഷം_CODE (type) == INTEGER_TYPE)
	തിരികെ;
      op = വൃക്ഷം_OPERAND (op, 0);
    }

  എങ്കിൽ (വൃക്ഷം_CODE (op) == POINTER_PLUS_വ്യഞ്ജകം)
    {
      /* Allow a cast to void* to suppress the warning.  */
      വൃക്ഷം type = വൃക്ഷം_TYPE (വൃക്ഷം_TYPE (op));
      എങ്കിൽ (VOID_TYPE_P (type))
	തിരികെ;

      /* Adding any value to a null pointer, including zero, is undefined
	 in C.  This includes the expression &p[0] where p is the null
	 pointer, although &p[0] will have been folded to p by this point
	 and so not diagnosed.  */
      എങ്കിൽ (code == EQ_വ്യഞ്ജകം)
	warning_at (loc, OPT_Waddress,
		    "the comparison will always evaluate as %<false%> "
		    "for the pointer operand in %qE must not be NULL",
		    op);
      അല്ലെങ്കിൽ
	warning_at (loc, OPT_Waddress,
		    "the comparison will always evaluate as %<true%> "
		    "for the pointer operand in %qE must not be NULL",
		    op);

      തിരികെ;
    }

  എങ്കിൽ (വൃക്ഷം_CODE (op) != ADDR_വ്യഞ്ജകം)
    തിരികെ;

  op = വൃക്ഷം_OPERAND (op, 0);

  എങ്കിൽ (വൃക്ഷം_CODE (op) == IMAGPART_വ്യഞ്ജകം
      || വൃക്ഷം_CODE (op) == REALPART_വ്യഞ്ജകം)
    {
      /* The address of either complex part may not be null.  */
      എങ്കിൽ (code == EQ_വ്യഞ്ജകം)
	warning_at (loc, OPT_Waddress,
		    "the comparison will always evaluate as %<false%> "
		    "for the address of %qE will never be NULL",
		    op);
      അല്ലെങ്കിൽ
	warning_at (loc, OPT_Waddress,
		    "the comparison will always evaluate as %<true%> "
		    "for the address of %qE will never be NULL",
		    op);
      തിരികെ;
    }

  /* Set to true in the loop below if OP dereferences is operand.
     In such a case the ultimate target need not be a decl for
     the null [in]equality test to be constant.  */
  തർക്കം deref = അസത്യം;

  /* Get the outermost array or object, or member.  */
  ആകുമ്പോൾ (handled_component_p (op))
    {
      എങ്കിൽ (വൃക്ഷം_CODE (op) == COMPONENT_REF)
	{
	  /* Get the member (its address is never null).  */
	  op = വൃക്ഷം_OPERAND (op, 1);
	  നിർത്തുക;
	}

      /* Get the outer array/object to refer to in the warning.  */
      op = വൃക്ഷം_OPERAND (op, 0);
      deref = സത്യം;
    }

  എങ്കിൽ ((!deref && !decl_with_nonnull_addr_p (op))
      || from_macro_expansion_at (loc))
    തിരികെ;

  തർക്കം w;
  എങ്കിൽ (code == EQ_വ്യഞ്ജകം)
    w = warning_at (loc, OPT_Waddress,
		    "the comparison will always evaluate as %<false%> "
		    "for the address of %qE will never be NULL",
		    op);
  അല്ലെങ്കിൽ
    w = warning_at (loc, OPT_Waddress,
		    "the comparison will always evaluate as %<true%> "
		    "for the address of %qE will never be NULL",
		    op);

  എങ്കിൽ (w && DECL_P (op))
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

വൃക്ഷം
build_ദ്വിമാന_op (location_t location, എണ്ണൽ വൃക്ഷം_code code,
		 വൃക്ഷം orig_op0, വൃക്ഷം orig_op1, തർക്കം convert_p)
{
  വൃക്ഷം type0, type1, orig_type0, orig_type1;
  വൃക്ഷം eptype;
  എണ്ണൽ വൃക്ഷം_code code0, code1;
  വൃക്ഷം op0, op1;
  വൃക്ഷം ret = error_mark_കണ്ണി;
  സ്ഥിരം അക്ഷരം *invalid_op_diag;
  തർക്കം op0_int_operands, op1_int_operands;
  തർക്കം int_const, int_const_or_overflow, int_operands;

  /* Expression code to give to the expression when it is built.
     Normally this is CODE, which is what the caller asked for,
     but in some special cases we change it.  */
  എണ്ണൽ വൃക്ഷം_code resultcode = code;

  /* Data type in which the computation is to be performed.
     In the simplest cases this is the common type of the arguments.  */
  വൃക്ഷം result_type = ശൂന്യ;

  /* When the computation is in excess precision, the type of the
     final EXCESS_PRECISION_EXPR.  */
  വൃക്ഷം semantic_result_type = ശൂന്യ;

  /* Nonzero means operands have already been type-converted
     in whatever way is necessary.
     Zero means they need to be converted to RESULT_TYPE.  */
  പൂർണ്ണസംഖ്യ converted = 0;

  /* Nonzero means create the expression with this type, rather than
     RESULT_TYPE.  */
  വൃക്ഷം build_type = NULL_വൃക്ഷം;

  /* Nonzero means after finally constructing the expression
     convert it to this type.  */
  വൃക്ഷം final_type = NULL_വൃക്ഷം;

  /* Nonzero if this is an operation like MIN or MAX which can
     safely be computed in short if both args are promoted shorts.
     Also implies COMMON.
     -1 indicates a bitwise operation; this makes a difference
     in the exact conditions for when it is safe to do the operation
     in a narrower mode.  */
  പൂർണ്ണസംഖ്യ shorten = 0;

  /* Nonzero if this is a comparison operation;
     if both args are promoted shorts, compare the original shorts.
     Also implies COMMON.  */
  പൂർണ്ണസംഖ്യ short_compare = 0;

  /* Nonzero if this is a right-shift operation, which can be computed on the
     original short and then promoted if the operand is a promoted short.  */
  പൂർണ്ണസംഖ്യ short_shift = 0;

  /* Nonzero means set RESULT_TYPE to the common type of the args.  */
  പൂർണ്ണസംഖ്യ common = 0;

  /* True means types are compatible as far as ObjC is concerned.  */
  തർക്കം objc_ok;

  /* True means this is an arithmetic operation that may need excess
     precision.  */
  തർക്കം may_need_excess_precision;

  /* True means this is a boolean operation that converts both its
     operands to truth-values.  */
  തർക്കം boolean_op = അസത്യം;

  /* Remember whether we're doing / or %.  */
  തർക്കം doing_div_or_mod = അസത്യം;

  /* Remember whether we're doing << or >>.  */
  തർക്കം doing_shift = അസത്യം;

  /* Tree holding instrumentation expression.  */
  വൃക്ഷം instrument_വ്യഞ്ജകം = ശൂന്യ;

  എങ്കിൽ (location == UNKNOWN_LOCATION)
    location = നിവേശം_location;

  op0 = orig_op0;
  op1 = orig_op1;

  op0_int_operands = വ്യഞ്ജകം_INT_CONST_OPERANDS (orig_op0);
  എങ്കിൽ (op0_int_operands)
    op0 = remove_c_maybe_const_വ്യഞ്ജകം (op0);
  op1_int_operands = വ്യഞ്ജകം_INT_CONST_OPERANDS (orig_op1);
  എങ്കിൽ (op1_int_operands)
    op1 = remove_c_maybe_const_വ്യഞ്ജകം (op1);
  int_operands = (op0_int_operands && op1_int_operands);
  എങ്കിൽ (int_operands)
    {
      int_const_or_overflow = (വൃക്ഷം_CODE (orig_op0) == INTEGER_CST
			       && വൃക്ഷം_CODE (orig_op1) == INTEGER_CST);
      int_const = (int_const_or_overflow
		   && !വൃക്ഷം_OVERFLOW (orig_op0)
		   && !വൃക്ഷം_OVERFLOW (orig_op1));
    }
  അല്ലെങ്കിൽ
    int_const = int_const_or_overflow = അസത്യം;

  /* Do not apply default conversion in mixed vector/scalar expression.  */
  എങ്കിൽ (convert_p
      && VECTOR_TYPE_P (വൃക്ഷം_TYPE (op0)) == VECTOR_TYPE_P (വൃക്ഷം_TYPE (op1)))
    {
      op0 = default_conversion (op0);
      op1 = default_conversion (op1);
    }

  orig_type0 = type0 = വൃക്ഷം_TYPE (op0);

  orig_type1 = type1 = വൃക്ഷം_TYPE (op1);

  /* The expression codes of the data types of the arguments tell us
     whether the arguments are integers, floating, pointers, etc.  */
  code0 = വൃക്ഷം_CODE (type0);
  code1 = വൃക്ഷം_CODE (type1);

  /* Strip NON_LVALUE_EXPRs, etc., since we aren't using as an lvalue.  */
  STRIP_TYPE_NOPS (op0);
  STRIP_TYPE_NOPS (op1);

  /* If an error was already reported for one of the arguments,
     avoid reporting another error.  */

  എങ്കിൽ (code0 == ERROR_MARK || code1 == ERROR_MARK)
    തിരികെ error_mark_കണ്ണി;

  എങ്കിൽ (code0 == POINTER_TYPE
      && reject_gcc_builtin (op0, വ്യഞ്ജകം_LOCATION (orig_op0)))
    തിരികെ error_mark_കണ്ണി;

  എങ്കിൽ (code1 == POINTER_TYPE
      && reject_gcc_builtin (op1, വ്യഞ്ജകം_LOCATION (orig_op1)))
    തിരികെ error_mark_കണ്ണി;

  എങ്കിൽ ((invalid_op_diag
       = targetm.invalid_ദ്വിമാന_op (code, type0, type1)))
    {
      error_at (location, invalid_op_diag);
      തിരികെ error_mark_കണ്ണി;
    }

  തിരഞ്ഞെടുപ്പ് (code)
    {
    അവസ്ഥ PLUS_വ്യഞ്ജകം:
    അവസ്ഥ MINUS_വ്യഞ്ജകം:
    അവസ്ഥ MULT_വ്യഞ്ജകം:
    അവസ്ഥ TRUNC_DIV_വ്യഞ്ജകം:
    അവസ്ഥ CEIL_DIV_വ്യഞ്ജകം:
    അവസ്ഥ FLOOR_DIV_വ്യഞ്ജകം:
    അവസ്ഥ ROUND_DIV_വ്യഞ്ജകം:
    അവസ്ഥ EXACT_DIV_വ്യഞ്ജകം:
      may_need_excess_precision = സത്യം;
      നിർത്തുക;

    അവസ്ഥ EQ_വ്യഞ്ജകം:
    അവസ്ഥ NE_വ്യഞ്ജകം:
    അവസ്ഥ LE_വ്യഞ്ജകം:
    അവസ്ഥ GE_വ്യഞ്ജകം:
    അവസ്ഥ LT_വ്യഞ്ജകം:
    അവസ്ഥ GT_വ്യഞ്ജകം:
      /* Excess precision for implicit conversions of integers to
	 floating point in C11 and later.  */
      may_need_excess_precision = (flag_isoc11
				   && (ANY_INTEGRAL_TYPE_P (type0)
				       || ANY_INTEGRAL_TYPE_P (type1)));
      നിർത്തുക;

    സ്ഥിരസ്ഥിതി:
      may_need_excess_precision = അസത്യം;
      നിർത്തുക;
    }
  എങ്കിൽ (വൃക്ഷം_CODE (op0) == EXCESS_PRECISION_വ്യഞ്ജകം)
    {
      op0 = വൃക്ഷം_OPERAND (op0, 0);
      type0 = വൃക്ഷം_TYPE (op0);
    }
  അല്ലെങ്കിൽ എങ്കിൽ (may_need_excess_precision
	   && (eptype = excess_precision_type (type0)) != NULL_വൃക്ഷം)
    {
      type0 = eptype;
      op0 = convert (eptype, op0);
    }
  എങ്കിൽ (വൃക്ഷം_CODE (op1) == EXCESS_PRECISION_വ്യഞ്ജകം)
    {
      op1 = വൃക്ഷം_OPERAND (op1, 0);
      type1 = വൃക്ഷം_TYPE (op1);
    }
  അല്ലെങ്കിൽ എങ്കിൽ (may_need_excess_precision
	   && (eptype = excess_precision_type (type1)) != NULL_വൃക്ഷം)
    {
      type1 = eptype;
      op1 = convert (eptype, op1);
    }

  objc_ok = objc_compare_types (type0, type1, -3, NULL_വൃക്ഷം);

  /* In case when one of the operands of the binary operation is
     a vector and another is a scalar -- convert scalar to vector.  */
  എങ്കിൽ ((gnu_vector_type_p (type0) && code1 != VECTOR_TYPE)
      || (gnu_vector_type_p (type1) && code0 != VECTOR_TYPE))
    {
      എണ്ണൽ stv_conv convert_flag = scalar_to_vector (location, code, orig_op0,
						     orig_op1, സത്യം);

      തിരഞ്ഞെടുപ്പ് (convert_flag)
	{
	  അവസ്ഥ stv_error:
	    തിരികെ error_mark_കണ്ണി;
	  അവസ്ഥ stv_firstarg:
	    {
              തർക്കം maybe_const = സത്യം;
              വൃക്ഷം sc;
              sc = c_fully_fold (op0, അസത്യം, &maybe_const);
              sc = save_വ്യഞ്ജകം (sc);
              sc = convert (വൃക്ഷം_TYPE (type1), sc);
              op0 = build_vector_from_val (type1, sc);
              എങ്കിൽ (!maybe_const)
                op0 = c_wrap_maybe_const (op0, സത്യം);
              orig_type0 = type0 = വൃക്ഷം_TYPE (op0);
              code0 = വൃക്ഷം_CODE (type0);
              converted = 1;
              നിർത്തുക;
	    }
	  അവസ്ഥ stv_secondarg:
	    {
	      തർക്കം maybe_const = സത്യം;
	      വൃക്ഷം sc;
	      sc = c_fully_fold (op1, അസത്യം, &maybe_const);
	      sc = save_വ്യഞ്ജകം (sc);
	      sc = convert (വൃക്ഷം_TYPE (type0), sc);
	      op1 = build_vector_from_val (type0, sc);
	      എങ്കിൽ (!maybe_const)
		op1 = c_wrap_maybe_const (op1, സത്യം);
	      orig_type1 = type1 = വൃക്ഷം_TYPE (op1);
	      code1 = വൃക്ഷം_CODE (type1);
	      converted = 1;
	      നിർത്തുക;
	    }
	  സ്ഥിരസ്ഥിതി:
	    നിർത്തുക;
	}
    }

  തിരഞ്ഞെടുപ്പ് (code)
    {
    അവസ്ഥ PLUS_വ്യഞ്ജകം:
      /* Handle the pointer + int case.  */
      എങ്കിൽ (code0 == POINTER_TYPE
	  && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  ret = pointer_int_sum (location, PLUS_വ്യഞ്ജകം, op0, op1);
	  പോകുക return_build_ദ്വിമാന_op;
	}
      അല്ലെങ്കിൽ എങ്കിൽ (code1 == POINTER_TYPE
	       && (code0 == INTEGER_TYPE || code0 == BITINT_TYPE))
	{
	  ret = pointer_int_sum (location, PLUS_വ്യഞ്ജകം, op1, op0);
	  പോകുക return_build_ദ്വിമാന_op;
	}
      അല്ലെങ്കിൽ
	common = 1;
      നിർത്തുക;

    അവസ്ഥ MINUS_വ്യഞ്ജകം:
      /* Subtraction of two similar pointers.
	 We must subtract them as integers, then divide by object size.  */
      എങ്കിൽ (code0 == POINTER_TYPE && code1 == POINTER_TYPE
	  && comp_target_types (location, type0, type1))
	{
	  ret = pointer_diff (location, op0, op1, &instrument_വ്യഞ്ജകം);
	  പോകുക return_build_ദ്വിമാന_op;
	}
      /* Handle pointer minus int.  Just like pointer plus int.  */
      അല്ലെങ്കിൽ എങ്കിൽ (code0 == POINTER_TYPE
	       && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  ret = pointer_int_sum (location, MINUS_വ്യഞ്ജകം, op0, op1);
	  പോകുക return_build_ദ്വിമാന_op;
	}
      അല്ലെങ്കിൽ
	common = 1;
      നിർത്തുക;

    അവസ്ഥ MULT_വ്യഞ്ജകം:
      common = 1;
      നിർത്തുക;

    അവസ്ഥ TRUNC_DIV_വ്യഞ്ജകം:
    അവസ്ഥ CEIL_DIV_വ്യഞ്ജകം:
    അവസ്ഥ FLOOR_DIV_വ്യഞ്ജകം:
    അവസ്ഥ ROUND_DIV_വ്യഞ്ജകം:
    അവസ്ഥ EXACT_DIV_വ്യഞ്ജകം:
      doing_div_or_mod = സത്യം;
      warn_for_div_by_zero (location, op1);

      എങ്കിൽ ((code0 == INTEGER_TYPE || code0 == REAL_TYPE
	   || code0 == FIXED_POINT_TYPE || code0 == BITINT_TYPE
	   || code0 == COMPLEX_TYPE
	   || gnu_vector_type_p (type0))
	  && (code1 == INTEGER_TYPE || code1 == REAL_TYPE
	      || code1 == FIXED_POINT_TYPE || code1 == BITINT_TYPE
	      || code1 == COMPLEX_TYPE
	      || gnu_vector_type_p (type1)))
	{
	  എണ്ണൽ വൃക്ഷം_code tcode0 = code0, tcode1 = code1;

	  എങ്കിൽ (code0 == COMPLEX_TYPE || code0 == VECTOR_TYPE)
	    tcode0 = വൃക്ഷം_CODE (വൃക്ഷം_TYPE (വൃക്ഷം_TYPE (op0)));
	  എങ്കിൽ (code1 == COMPLEX_TYPE || code1 == VECTOR_TYPE)
	    tcode1 = വൃക്ഷം_CODE (വൃക്ഷം_TYPE (വൃക്ഷം_TYPE (op1)));

	  എങ്കിൽ (!(((tcode0 == INTEGER_TYPE || tcode0 == BITINT_TYPE
		  || (tcode0 == ENUMERAL_TYPE && code0 == VECTOR_TYPE))
		 && (tcode1 == INTEGER_TYPE || tcode1 == BITINT_TYPE
		     || (tcode1 == ENUMERAL_TYPE && code1 == VECTOR_TYPE)))
		|| (tcode0 == FIXED_POINT_TYPE && tcode1 == FIXED_POINT_TYPE)))
	    resultcode = RDIV_വ്യഞ്ജകം;
	  അല്ലെങ്കിൽ
	    /* Although it would be tempting to shorten always here, that
	       loses on some targets, since the modulo instruction is
	       undefined if the quotient can't be represented in the
	       computation mode.  We shorten only if unsigned or if
	       dividing by something we know != -1.  */
	    shorten = may_shorten_divmod (op0, op1);
	  common = 1;
	}
      നിർത്തുക;

    അവസ്ഥ BIT_AND_വ്യഞ്ജകം:
    അവസ്ഥ BIT_IOR_വ്യഞ്ജകം:
    അവസ്ഥ BIT_XOR_വ്യഞ്ജകം:
      എങ്കിൽ ((code0 == INTEGER_TYPE || code0 == BITINT_TYPE)
	  && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	shorten = -1;
      /* Allow vector types which are not floating point types.   */
      അല്ലെങ്കിൽ എങ്കിൽ (gnu_vector_type_p (type0)
	       && gnu_vector_type_p (type1)
	       && !VECTOR_FLOAT_TYPE_P (type0)
	       && !VECTOR_FLOAT_TYPE_P (type1))
	common = 1;
      നിർത്തുക;

    അവസ്ഥ TRUNC_MOD_വ്യഞ്ജകം:
    അവസ്ഥ FLOOR_MOD_വ്യഞ്ജകം:
      doing_div_or_mod = സത്യം;
      warn_for_div_by_zero (location, op1);

      എങ്കിൽ (gnu_vector_type_p (type0)
	  && gnu_vector_type_p (type1)
	  && വൃക്ഷം_CODE (വൃക്ഷം_TYPE (type0)) == INTEGER_TYPE
	  && വൃക്ഷം_CODE (വൃക്ഷം_TYPE (type1)) == INTEGER_TYPE)
	common = 1;
      അല്ലെങ്കിൽ എങ്കിൽ ((code0 == INTEGER_TYPE || code0 == BITINT_TYPE)
	       && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  /* Although it would be tempting to shorten always here, that loses
	     on some targets, since the modulo instruction is undefined if the
	     quotient can't be represented in the computation mode.  We shorten
	     only if unsigned or if dividing by something we know != -1.  */
	  shorten = may_shorten_divmod (op0, op1);
	  common = 1;
	}
      നിർത്തുക;

    അവസ്ഥ TRUTH_ANDIF_വ്യഞ്ജകം:
    അവസ്ഥ TRUTH_ORIF_വ്യഞ്ജകം:
    അവസ്ഥ TRUTH_AND_വ്യഞ്ജകം:
    അവസ്ഥ TRUTH_OR_വ്യഞ്ജകം:
    അവസ്ഥ TRUTH_XOR_വ്യഞ്ജകം:
      എങ്കിൽ ((code0 == INTEGER_TYPE || code0 == POINTER_TYPE
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
	  result_type = integer_type_കണ്ണി;
	  എങ്കിൽ (op0_int_operands)
	    {
	      op0 = c_objc_common_truthvalue_conversion (location, orig_op0);
	      op0 = remove_c_maybe_const_വ്യഞ്ജകം (op0);
	    }
	  അല്ലെങ്കിൽ
	    op0 = c_objc_common_truthvalue_conversion (location, op0);
	  എങ്കിൽ (op1_int_operands)
	    {
	      op1 = c_objc_common_truthvalue_conversion (location, orig_op1);
	      op1 = remove_c_maybe_const_വ്യഞ്ജകം (op1);
	    }
	  അല്ലെങ്കിൽ
	    op1 = c_objc_common_truthvalue_conversion (location, op1);
	  converted = 1;
	  boolean_op = സത്യം;
	}
      എങ്കിൽ (code == TRUTH_ANDIF_വ്യഞ്ജകം)
	{
	  int_const_or_overflow = (int_operands
				   && വൃക്ഷം_CODE (orig_op0) == INTEGER_CST
				   && (op0 == truthvalue_false_കണ്ണി
				       || വൃക്ഷം_CODE (orig_op1) == INTEGER_CST));
	  int_const = (int_const_or_overflow
		       && !വൃക്ഷം_OVERFLOW (orig_op0)
		       && (op0 == truthvalue_false_കണ്ണി
			   || !വൃക്ഷം_OVERFLOW (orig_op1)));
	}
      അല്ലെങ്കിൽ എങ്കിൽ (code == TRUTH_ORIF_വ്യഞ്ജകം)
	{
	  int_const_or_overflow = (int_operands
				   && വൃക്ഷം_CODE (orig_op0) == INTEGER_CST
				   && (op0 == truthvalue_true_കണ്ണി
				       || വൃക്ഷം_CODE (orig_op1) == INTEGER_CST));
	  int_const = (int_const_or_overflow
		       && !വൃക്ഷം_OVERFLOW (orig_op0)
		       && (op0 == truthvalue_true_കണ്ണി
			   || !വൃക്ഷം_OVERFLOW (orig_op1)));
	}
      നിർത്തുക;

      /* Shift operations: result has same type as first operand;
	 always convert second operand to int.
	 Also set SHORT_SHIFT if shifting rightward.  */

    അവസ്ഥ RSHIFT_വ്യഞ്ജകം:
      എങ്കിൽ (gnu_vector_type_p (type0)
	  && gnu_vector_type_p (type1)
	  && വൃക്ഷം_CODE (വൃക്ഷം_TYPE (type0)) == INTEGER_TYPE
	  && വൃക്ഷം_CODE (വൃക്ഷം_TYPE (type1)) == INTEGER_TYPE
	  && known_eq (TYPE_VECTOR_SUBPARTS (type0),
		       TYPE_VECTOR_SUBPARTS (type1)))
	{
	  result_type = type0;
	  converted = 1;
	}
      അല്ലെങ്കിൽ എങ്കിൽ ((code0 == INTEGER_TYPE || code0 == FIXED_POINT_TYPE
		|| code0 == BITINT_TYPE
		|| (gnu_vector_type_p (type0)
		    && വൃക്ഷം_CODE (വൃക്ഷം_TYPE (type0)) == INTEGER_TYPE))
	       && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  doing_shift = സത്യം;
	  എങ്കിൽ (വൃക്ഷം_CODE (op1) == INTEGER_CST)
	    {
	      എങ്കിൽ (വൃക്ഷം_int_cst_sgn (op1) < 0)
		{
		  int_const = അസത്യം;
		  എങ്കിൽ (c_inhibit_evaluation_warnings == 0)
		    warning_at (location, OPT_Wshift_എണ്ണം_negative,
				"right shift count is negative");
		}
	      അല്ലെങ്കിൽ എങ്കിൽ (code0 == VECTOR_TYPE)
		{
		  എങ്കിൽ (compare_വൃക്ഷം_int (op1,
					TYPE_PRECISION (വൃക്ഷം_TYPE (type0)))
		      >= 0)
		    {
		      int_const = അസത്യം;
		      എങ്കിൽ (c_inhibit_evaluation_warnings == 0)
			warning_at (location, OPT_Wshift_എണ്ണം_overflow,
				    "right shift count >= width of vector element");
		    }
		}
	      അല്ലെങ്കിൽ
		{
		  എങ്കിൽ (!integer_zerop (op1))
		    short_shift = 1;

		  എങ്കിൽ (compare_വൃക്ഷം_int (op1, TYPE_PRECISION (type0)) >= 0)
		    {
		      int_const = അസത്യം;
		      എങ്കിൽ (c_inhibit_evaluation_warnings == 0)
			warning_at (location, OPT_Wshift_എണ്ണം_overflow,
				    "right shift count >= width of type");
		    }
		}
	    }

	  /* Use the type of the value to be shifted.  */
	  result_type = type0;
	  /* Avoid converting op1 to result_type later.  */
	  converted = 1;
	}
      നിർത്തുക;

    അവസ്ഥ LSHIFT_വ്യഞ്ജകം:
      എങ്കിൽ (gnu_vector_type_p (type0)
	  && gnu_vector_type_p (type1)
	  && വൃക്ഷം_CODE (വൃക്ഷം_TYPE (type0)) == INTEGER_TYPE
	  && വൃക്ഷം_CODE (വൃക്ഷം_TYPE (type1)) == INTEGER_TYPE
	  && known_eq (TYPE_VECTOR_SUBPARTS (type0),
		       TYPE_VECTOR_SUBPARTS (type1)))
	{
	  result_type = type0;
	  converted = 1;
	}
      അല്ലെങ്കിൽ എങ്കിൽ ((code0 == INTEGER_TYPE || code0 == FIXED_POINT_TYPE
		|| code0 == BITINT_TYPE
		|| (gnu_vector_type_p (type0)
		    && വൃക്ഷം_CODE (വൃക്ഷം_TYPE (type0)) == INTEGER_TYPE))
	       && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  doing_shift = സത്യം;
	  എങ്കിൽ (വൃക്ഷം_CODE (op0) == INTEGER_CST
	      && വൃക്ഷം_int_cst_sgn (op0) < 0
	      && !TYPE_OVERFLOW_WRAPS (type0))
	    {
	      /* Don't reject a left shift of a negative value in a context
		 where a constant expression is needed in C90.  */
	      എങ്കിൽ (flag_isoc99)
		int_const = അസത്യം;
	      എങ്കിൽ (c_inhibit_evaluation_warnings == 0)
		warning_at (location, OPT_Wshift_negative_മൂല്യം,
			    "left shift of negative value");
	    }
	  എങ്കിൽ (വൃക്ഷം_CODE (op1) == INTEGER_CST)
	    {
	      എങ്കിൽ (വൃക്ഷം_int_cst_sgn (op1) < 0)
		{
		  int_const = അസത്യം;
		  എങ്കിൽ (c_inhibit_evaluation_warnings == 0)
		    warning_at (location, OPT_Wshift_എണ്ണം_negative,
				"left shift count is negative");
		}
	      അല്ലെങ്കിൽ എങ്കിൽ (code0 == VECTOR_TYPE)
		{
		  എങ്കിൽ (compare_വൃക്ഷം_int (op1,
					TYPE_PRECISION (വൃക്ഷം_TYPE (type0)))
		      >= 0)
		    {
		      int_const = അസത്യം;
		      എങ്കിൽ (c_inhibit_evaluation_warnings == 0)
			warning_at (location, OPT_Wshift_എണ്ണം_overflow,
				    "left shift count >= width of vector element");
		    }
		}
	      അല്ലെങ്കിൽ എങ്കിൽ (compare_വൃക്ഷം_int (op1, TYPE_PRECISION (type0)) >= 0)
		{
		  int_const = അസത്യം;
		  എങ്കിൽ (c_inhibit_evaluation_warnings == 0)
		    warning_at (location, OPT_Wshift_എണ്ണം_overflow,
				"left shift count >= width of type");
		}
	      അല്ലെങ്കിൽ എങ്കിൽ (വൃക്ഷം_CODE (op0) == INTEGER_CST
		       && maybe_warn_shift_overflow (location, op0, op1)
		       && flag_isoc99)
		int_const = അസത്യം;
	    }

	  /* Use the type of the value to be shifted.  */
	  result_type = type0;
	  /* Avoid converting op1 to result_type later.  */
	  converted = 1;
	}
      നിർത്തുക;

    അവസ്ഥ EQ_വ്യഞ്ജകം:
    അവസ്ഥ NE_വ്യഞ്ജകം:
      എങ്കിൽ (gnu_vector_type_p (type0) && gnu_vector_type_p (type1))
        {
          വൃക്ഷം intt;
	  എങ്കിൽ (!vector_types_compatible_elements_p (type0, type1))
            {
              error_at (location, "comparing vectors with different "
                                  "element types");
              തിരികെ error_mark_കണ്ണി;
            }

	  എങ്കിൽ (maybe_ne (TYPE_VECTOR_SUBPARTS (type0),
			TYPE_VECTOR_SUBPARTS (type1)))
            {
              error_at (location, "comparing vectors with different "
                                  "number of elements");
              തിരികെ error_mark_കണ്ണി;
            }

	  /* It's not precisely specified how the usual arithmetic
	     conversions apply to the vector types.  Here, we use
	     the unsigned type if one of the operands is signed and
	     the other one is unsigned.  */
	  എങ്കിൽ (TYPE_UNSIGNED (type0) != TYPE_UNSIGNED (type1))
	    {
	      എങ്കിൽ (!TYPE_UNSIGNED (type0))
		op0 = build1 (VIEW_CONVERT_വ്യഞ്ജകം, type1, op0);
	      അല്ലെങ്കിൽ
		op1 = build1 (VIEW_CONVERT_വ്യഞ്ജകം, type0, op1);
	      warning_at (location, OPT_Wsign_compare, "comparison between "
			  "types %qT and %qT", type0, type1);
	    }

          /* Always construct signed integer vector type.  */
	  എങ്കിൽ (VECTOR_BOOLEAN_TYPE_P (type0) && VECTOR_BOOLEAN_TYPE_P (type1))
	    result_type = type0;
	  അല്ലെങ്കിൽ
	    {
	      auto nelts = TYPE_VECTOR_SUBPARTS (type0);

	      intt = c_common_type_for_size (GET_MODE_BITSIZE
					     (SCALAR_TYPE_MODE
						(വൃക്ഷം_TYPE (type0))), 0);
	      എങ്കിൽ (!intt)
		{
		  error_at (location, "could not find an integer type "
				      "of the same size as %qT",
			    വൃക്ഷം_TYPE (type0));
		  തിരികെ error_mark_കണ്ണി;
		}
	      result_type = build_opaque_vector_type (intt, nelts);
	    }
          converted = 1;
	  ret = build_vec_cmp (resultcode, result_type, op0, op1);
	  പോകുക return_build_ദ്വിമാന_op;
        }
      എങ്കിൽ (FLOAT_TYPE_P (type0) || FLOAT_TYPE_P (type1))
	warning_at (location,
		    OPT_Wfloat_equal,
		    "comparing floating-point with %<==%> or %<!=%> is unsafe");
      /* Result of comparison is always int,
	 but don't convert the args to int!  */
      build_type = integer_type_കണ്ണി;
      എങ്കിൽ ((code0 == INTEGER_TYPE || code0 == REAL_TYPE || code0 == BITINT_TYPE
	   || code0 == FIXED_POINT_TYPE || code0 == COMPLEX_TYPE)
	  && (code1 == INTEGER_TYPE || code1 == REAL_TYPE
	      || code1 == BITINT_TYPE
	      || code1 == FIXED_POINT_TYPE || code1 == COMPLEX_TYPE))
	short_compare = 1;
      അല്ലെങ്കിൽ എങ്കിൽ (code0 == POINTER_TYPE
	       && (code1 == NULLPTR_TYPE
		   || null_pointer_constant_p (orig_op1)))
	{
	  maybe_warn_for_null_address (location, op0, code);
	  result_type = type0;
	}
      അല്ലെങ്കിൽ എങ്കിൽ (code1 == POINTER_TYPE
	       && (code0 == NULLPTR_TYPE
		   || null_pointer_constant_p (orig_op0)))
	{
	  maybe_warn_for_null_address (location, op1, code);
	  result_type = type1;
	}
      അല്ലെങ്കിൽ എങ്കിൽ (code0 == POINTER_TYPE && code1 == POINTER_TYPE)
	{
	  വൃക്ഷം tt0 = വൃക്ഷം_TYPE (type0);
	  വൃക്ഷം tt1 = വൃക്ഷം_TYPE (type1);
	  addr_space_t as0 = TYPE_ADDR_SPACE (tt0);
	  addr_space_t as1 = TYPE_ADDR_SPACE (tt1);
	  addr_space_t as_common = ADDR_SPACE_GENERIC;

	  /* Anything compares with void *.  void * compares with anything.
	     Otherwise, the targets must be compatible
	     and both must be object or both incomplete.  */
	  എങ്കിൽ (comp_target_types (location, type0, type1))
	    result_type = common_pointer_type (type0, type1, NULL_വൃക്ഷം);
	  അല്ലെങ്കിൽ എങ്കിൽ (!addr_space_superset (as0, as1, &as_common))
	    {
	      error_at (location, "comparison of pointers to "
			"disjoint address spaces");
	      തിരികെ error_mark_കണ്ണി;
	    }
	  അല്ലെങ്കിൽ എങ്കിൽ (VOID_TYPE_P (tt0) && !TYPE_ATOMIC (tt0))
	    {
	      എങ്കിൽ (pedantic && വൃക്ഷം_CODE (tt1) == FUNCTION_TYPE)
		pedwarn (location, OPT_Wpedantic, "ISO C forbids "
			 "comparison of %<void *%> with function pointer");
	    }
	  അല്ലെങ്കിൽ എങ്കിൽ (VOID_TYPE_P (tt1) && !TYPE_ATOMIC (tt1))
	    {
	      എങ്കിൽ (pedantic && വൃക്ഷം_CODE (tt0) == FUNCTION_TYPE)
		pedwarn (location, OPT_Wpedantic, "ISO C forbids "
			 "comparison of %<void *%> with function pointer");
	    }
	  അല്ലെങ്കിൽ
	    /* Avoid warning about the volatile ObjC EH puts on decls.  */
	    എങ്കിൽ (!objc_ok)
	      pedwarn (location, OPT_Wcompare_distinct_pointer_types,
		       "comparison of distinct pointer types lacks a cast");

	  എങ്കിൽ (result_type == NULL_വൃക്ഷം)
	    {
	      പൂർണ്ണസംഖ്യ qual = ENCODE_QUAL_ADDR_SPACE (as_common);
	      result_type = c_build_pointer_type
			      (c_build_qualified_type (void_type_കണ്ണി, qual));
	    }
	}
      അല്ലെങ്കിൽ എങ്കിൽ (code0 == POINTER_TYPE
	       && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  result_type = type0;
	  pedwarn (location, 0, "comparison between pointer and integer");
	}
      അല്ലെങ്കിൽ എങ്കിൽ ((code0 == INTEGER_TYPE || code0 == BITINT_TYPE)
	       && code1 == POINTER_TYPE)
	{
	  result_type = type1;
	  pedwarn (location, 0, "comparison between pointer and integer");
	}
      /* 6.5.9: One of the following shall hold:
	 -- both operands have type nullptr_t;  */
      അല്ലെങ്കിൽ എങ്കിൽ (code0 == NULLPTR_TYPE && code1 == NULLPTR_TYPE)
	{
	  result_type = nullptr_type_കണ്ണി;
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
      അല്ലെങ്കിൽ എങ്കിൽ (code0 == NULLPTR_TYPE && null_pointer_constant_p (orig_op1))
	result_type = (INTEGRAL_TYPE_P (type1)
		       ? c_build_pointer_type (type1) : type1);
      അല്ലെങ്കിൽ എങ്കിൽ (code1 == NULLPTR_TYPE && null_pointer_constant_p (orig_op0))
	result_type = (INTEGRAL_TYPE_P (type0)
		       ? c_build_pointer_type (type0) : type0);
      എങ്കിൽ ((C_BOOLEAN_TYPE_P (വൃക്ഷം_TYPE (orig_op0))
	   || truth_മൂല്യം_p (വൃക്ഷം_CODE (orig_op0)))
	  ^ (C_BOOLEAN_TYPE_P (വൃക്ഷം_TYPE (orig_op1))
	     || truth_മൂല്യം_p (വൃക്ഷം_CODE (orig_op1))))
	maybe_warn_bool_compare (location, code, orig_op0, orig_op1);
      നിർത്തുക;

    അവസ്ഥ LE_വ്യഞ്ജകം:
    അവസ്ഥ GE_വ്യഞ്ജകം:
    അവസ്ഥ LT_വ്യഞ്ജകം:
    അവസ്ഥ GT_വ്യഞ്ജകം:
      എങ്കിൽ (gnu_vector_type_p (type0) && gnu_vector_type_p (type1))
        {
          വൃക്ഷം intt;
	  എങ്കിൽ (!vector_types_compatible_elements_p (type0, type1))
            {
              error_at (location, "comparing vectors with different "
                                  "element types");
              തിരികെ error_mark_കണ്ണി;
            }

	  എങ്കിൽ (maybe_ne (TYPE_VECTOR_SUBPARTS (type0),
			TYPE_VECTOR_SUBPARTS (type1)))
            {
              error_at (location, "comparing vectors with different "
                                  "number of elements");
              തിരികെ error_mark_കണ്ണി;
            }

	  /* It's not precisely specified how the usual arithmetic
	     conversions apply to the vector types.  Here, we use
	     the unsigned type if one of the operands is signed and
	     the other one is unsigned.  */
	  എങ്കിൽ (TYPE_UNSIGNED (type0) != TYPE_UNSIGNED (type1))
	    {
	      എങ്കിൽ (!TYPE_UNSIGNED (type0))
		op0 = build1 (VIEW_CONVERT_വ്യഞ്ജകം, type1, op0);
	      അല്ലെങ്കിൽ
		op1 = build1 (VIEW_CONVERT_വ്യഞ്ജകം, type0, op1);
	      warning_at (location, OPT_Wsign_compare, "comparison between "
			  "types %qT and %qT", type0, type1);
	    }

          /* Always construct signed integer vector type.  */
          intt = c_common_type_for_size (GET_MODE_BITSIZE
					 (SCALAR_TYPE_MODE
					  (വൃക്ഷം_TYPE (type0))), 0);
	  എങ്കിൽ (!intt)
	    {
	      error_at (location, "could not find an integer type "
				  "of the same size as %qT",
			വൃക്ഷം_TYPE (type0));
	      തിരികെ error_mark_കണ്ണി;
	    }
          result_type = build_opaque_vector_type (intt,
						  TYPE_VECTOR_SUBPARTS (type0));
          converted = 1;
	  ret = build_vec_cmp (resultcode, result_type, op0, op1);
	  പോകുക return_build_ദ്വിമാന_op;
        }
      build_type = integer_type_കണ്ണി;
      എങ്കിൽ ((code0 == INTEGER_TYPE || code0 == REAL_TYPE
	   || code0 == BITINT_TYPE || code0 == FIXED_POINT_TYPE)
	  && (code1 == INTEGER_TYPE || code1 == REAL_TYPE
	      || code1 == BITINT_TYPE || code1 == FIXED_POINT_TYPE))
	short_compare = 1;
      അല്ലെങ്കിൽ എങ്കിൽ (code0 == POINTER_TYPE && code1 == POINTER_TYPE)
	{
	  addr_space_t as0 = TYPE_ADDR_SPACE (വൃക്ഷം_TYPE (type0));
	  addr_space_t as1 = TYPE_ADDR_SPACE (വൃക്ഷം_TYPE (type1));
	  addr_space_t as_common;

	  എങ്കിൽ (comp_target_types (location, type0, type1))
	    {
	      result_type = common_pointer_type (type0, type1, NULL_വൃക്ഷം);
	      എങ്കിൽ (!COMPLETE_TYPE_P (വൃക്ഷം_TYPE (type0))
		  != !COMPLETE_TYPE_P (വൃക്ഷം_TYPE (type1)))
		pedwarn_c99 (location, OPT_Wpedantic,
			     "comparison of complete and incomplete pointers");
	      അല്ലെങ്കിൽ എങ്കിൽ (വൃക്ഷം_CODE (വൃക്ഷം_TYPE (type0)) == FUNCTION_TYPE)
		pedwarn (location, OPT_Wpedantic, "ISO C forbids "
			 "ordered comparisons of pointers to functions");
	      അല്ലെങ്കിൽ എങ്കിൽ (null_pointer_constant_p (orig_op0)
		       || null_pointer_constant_p (orig_op1))
		warning_at (location, OPT_Wextra,
			    "ordered comparison of pointer with null pointer");

	    }
	  അല്ലെങ്കിൽ എങ്കിൽ (!addr_space_superset (as0, as1, &as_common))
	    {
	      error_at (location, "comparison of pointers to "
			"disjoint address spaces");
	      തിരികെ error_mark_കണ്ണി;
	    }
	  അല്ലെങ്കിൽ
	    {
	      പൂർണ്ണസംഖ്യ qual = ENCODE_QUAL_ADDR_SPACE (as_common);
	      result_type = c_build_pointer_type
			      (c_build_qualified_type (void_type_കണ്ണി, qual));
              pedwarn (location, OPT_Wcompare_distinct_pointer_types,
                       "comparison of distinct pointer types lacks a cast");
	    }
	}
      അല്ലെങ്കിൽ എങ്കിൽ (code0 == POINTER_TYPE && null_pointer_constant_p (orig_op1))
	{
	  result_type = type0;
	  എങ്കിൽ (pedantic)
	    pedwarn (location, OPT_Wpedantic,
		     "ordered comparison of pointer with integer zero");
	  അല്ലെങ്കിൽ എങ്കിൽ (extra_warnings)
	    warning_at (location, OPT_Wextra,
			"ordered comparison of pointer with integer zero");
	}
      അല്ലെങ്കിൽ എങ്കിൽ (code1 == POINTER_TYPE && null_pointer_constant_p (orig_op0))
	{
	  result_type = type1;
	  എങ്കിൽ (pedantic)
	    pedwarn (location, OPT_Wpedantic,
		     "ordered comparison of pointer with integer zero");
	  അല്ലെങ്കിൽ എങ്കിൽ (extra_warnings)
	    warning_at (location, OPT_Wextra,
			"ordered comparison of pointer with integer zero");
	}
      അല്ലെങ്കിൽ എങ്കിൽ (code0 == POINTER_TYPE
	       && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  result_type = type0;
	  pedwarn (location, 0, "comparison between pointer and integer");
	}
      അല്ലെങ്കിൽ എങ്കിൽ ((code0 == INTEGER_TYPE || code0 == BITINT_TYPE)
	       && code1 == POINTER_TYPE)
	{
	  result_type = type1;
	  pedwarn (location, 0, "comparison between pointer and integer");
	}

      എങ്കിൽ ((code0 == POINTER_TYPE || code1 == POINTER_TYPE)
	  && current_function_decl != NULL_വൃക്ഷം
	  && sanitize_flags_p (SANITIZE_POINTER_COMPARE))
	{
	  op0 = save_വ്യഞ്ജകം (c_fully_fold (op0, അസത്യം, ശൂന്യ));
	  op1 = save_വ്യഞ്ജകം (c_fully_fold (op1, അസത്യം, ശൂന്യ));

	  വൃക്ഷം tt = builtin_decl_explicit (BUILT_IN_ASAN_POINTER_COMPARE);
	  instrument_വ്യഞ്ജകം = build_call_വ്യഞ്ജകം_loc (location, tt, 2, op0, op1);
	}

      എങ്കിൽ ((C_BOOLEAN_TYPE_P (വൃക്ഷം_TYPE (orig_op0))
	   || truth_മൂല്യം_p (വൃക്ഷം_CODE (orig_op0)))
	  ^ (C_BOOLEAN_TYPE_P (വൃക്ഷം_TYPE (orig_op1))
	     || truth_മൂല്യം_p (വൃക്ഷം_CODE (orig_op1))))
	maybe_warn_bool_compare (location, code, orig_op0, orig_op1);
      നിർത്തുക;

    അവസ്ഥ MIN_വ്യഞ്ജകം:
    അവസ്ഥ MAX_വ്യഞ്ജകം:
      /* Used for OpenMP atomics.  */
      gcc_assert (flag_openmp);
      common = 1;
      നിർത്തുക;

    സ്ഥിരസ്ഥിതി:
      gcc_unreachable ();
    }

  എങ്കിൽ (code0 == ERROR_MARK || code1 == ERROR_MARK)
    തിരികെ error_mark_കണ്ണി;

  എങ്കിൽ (gnu_vector_type_p (type0)
      && gnu_vector_type_p (type1)
      && (!വൃക്ഷം_int_cst_equal (TYPE_SIZE (type0), TYPE_SIZE (type1))
	  || !vector_types_compatible_elements_p (type0, type1)))
    {
      gcc_rich_location richloc (location);
      maybe_range_label_for_വൃക്ഷം_type_mismatch
	label_for_op0 (orig_op0, orig_op1),
	label_for_op1 (orig_op1, orig_op0);
      richloc.maybe_add_വ്യഞ്ജകം (orig_op0, &label_for_op0, highlight_colors::lhs);
      richloc.maybe_add_വ്യഞ്ജകം (orig_op1, &label_for_op1, highlight_colors::rhs);
      ദ്വിമാന_op_error (&richloc, code, type0, type1);
      തിരികെ error_mark_കണ്ണി;
    }

  എങ്കിൽ ((code0 == INTEGER_TYPE || code0 == REAL_TYPE || code0 == COMPLEX_TYPE
       || code0 == FIXED_POINT_TYPE || code0 == BITINT_TYPE
       || gnu_vector_type_p (type0))
      && (code1 == INTEGER_TYPE || code1 == REAL_TYPE || code1 == COMPLEX_TYPE
	  || code1 == FIXED_POINT_TYPE || code1 == BITINT_TYPE
	  || gnu_vector_type_p (type1)))
    {
      തർക്കം first_complex = (code0 == COMPLEX_TYPE);
      തർക്കം second_complex = (code1 == COMPLEX_TYPE);
      പൂർണ്ണസംഖ്യ none_complex = (!first_complex && !second_complex);

      എങ്കിൽ (shorten || common || short_compare)
	{
	  result_type = c_common_type (type0, type1);
	  do_warn_double_promotion (result_type, type0, type1,
				    "implicit conversion from %qT to %qT "
				    "to match other operand of binary "
				    "expression",
				    location);
	  എങ്കിൽ (result_type == error_mark_കണ്ണി)
	    തിരികെ error_mark_കണ്ണി;
	}

      എങ്കിൽ (first_complex != second_complex
	  && (code == PLUS_വ്യഞ്ജകം
	      || code == MINUS_വ്യഞ്ജകം
	      || code == MULT_വ്യഞ്ജകം
	      || (code == TRUNC_DIV_വ്യഞ്ജകം && first_complex))
	  && വൃക്ഷം_CODE (വൃക്ഷം_TYPE (result_type)) == REAL_TYPE
	  && flag_signed_zeros)
	{
	  /* An operation on mixed real/complex operands must be
	     handled specially, but the language-independent code can
	     more easily optimize the plain complex arithmetic if
	     -fno-signed-zeros.  */
	  വൃക്ഷം real_type = വൃക്ഷം_TYPE (result_type);
	  വൃക്ഷം real, imag;
	  എങ്കിൽ (type0 != orig_type0 || type1 != orig_type1)
	    {
	      gcc_assert (may_need_excess_precision && common);
	      semantic_result_type = c_common_type (orig_type0, orig_type1);
	    }
	  എങ്കിൽ (first_complex)
	    {
	      എങ്കിൽ (വൃക്ഷം_TYPE (op0) != result_type)
		op0 = convert_and_check (location, result_type, op0);
	      എങ്കിൽ (വൃക്ഷം_TYPE (op1) != real_type)
		op1 = convert_and_check (location, real_type, op1);
	    }
	  അല്ലെങ്കിൽ
	    {
	      എങ്കിൽ (വൃക്ഷം_TYPE (op0) != real_type)
		op0 = convert_and_check (location, real_type, op0);
	      എങ്കിൽ (വൃക്ഷം_TYPE (op1) != result_type)
		op1 = convert_and_check (location, result_type, op1);
	    }
	  എങ്കിൽ (വൃക്ഷം_CODE (op0) == ERROR_MARK || വൃക്ഷം_CODE (op1) == ERROR_MARK)
	    തിരികെ error_mark_കണ്ണി;
	  എങ്കിൽ (first_complex)
	    {
	      op0 = save_വ്യഞ്ജകം (op0);
	      real = build_unary_op (വ്യഞ്ജകം_LOCATION (orig_op0), REALPART_വ്യഞ്ജകം,
				     op0, സത്യം);
	      imag = build_unary_op (വ്യഞ്ജകം_LOCATION (orig_op0), IMAGPART_വ്യഞ്ജകം,
				     op0, സത്യം);
	      തിരഞ്ഞെടുപ്പ് (code)
		{
		അവസ്ഥ MULT_വ്യഞ്ജകം:
		അവസ്ഥ TRUNC_DIV_വ്യഞ്ജകം:
		  op1 = save_വ്യഞ്ജകം (op1);
		  imag = build2 (resultcode, real_type, imag, op1);
		  /* Fall through.  */
		അവസ്ഥ PLUS_വ്യഞ്ജകം:
		അവസ്ഥ MINUS_വ്യഞ്ജകം:
		  real = build2 (resultcode, real_type, real, op1);
		  നിർത്തുക;
		സ്ഥിരസ്ഥിതി:
		  gcc_unreachable();
		}
	    }
	  അല്ലെങ്കിൽ
	    {
	      op1 = save_വ്യഞ്ജകം (op1);
	      real = build_unary_op (വ്യഞ്ജകം_LOCATION (orig_op1), REALPART_വ്യഞ്ജകം,
				     op1, സത്യം);
	      imag = build_unary_op (വ്യഞ്ജകം_LOCATION (orig_op1), IMAGPART_വ്യഞ്ജകം,
				     op1, സത്യം);
	      തിരഞ്ഞെടുപ്പ് (code)
		{
		അവസ്ഥ MULT_വ്യഞ്ജകം:
		  op0 = save_വ്യഞ്ജകം (op0);
		  imag = build2 (resultcode, real_type, op0, imag);
		  /* Fall through.  */
		അവസ്ഥ PLUS_വ്യഞ്ജകം:
		  real = build2 (resultcode, real_type, op0, real);
		  നിർത്തുക;
		അവസ്ഥ MINUS_വ്യഞ്ജകം:
		  real = build2 (resultcode, real_type, op0, real);
		  imag = build1 (NEGATE_വ്യഞ്ജകം, real_type, imag);
		  നിർത്തുക;
		സ്ഥിരസ്ഥിതി:
		  gcc_unreachable();
		}
	    }
	  ret = build2 (COMPLEX_വ്യഞ്ജകം, result_type, real, imag);
	  പോകുക return_build_ദ്വിമാന_op;
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

      എങ്കിൽ (shorten && none_complex)
	{
	  final_type = result_type;
	  result_type = shorten_ദ്വിമാന_op (result_type, op0, op1,
					   shorten == -1);
	}

      /* Shifts can be shortened if shifting right.  */

      എങ്കിൽ (short_shift)
	{
	  പൂർണ്ണസംഖ്യ unsigned_arg;
	  വൃക്ഷം arg0 = get_narrower (op0, &unsigned_arg);

	  final_type = result_type;

	  എങ്കിൽ (arg0 == op0 && final_type == വൃക്ഷം_TYPE (op0))
	    unsigned_arg = TYPE_UNSIGNED (വൃക്ഷം_TYPE (op0));

	  എങ്കിൽ (TYPE_PRECISION (വൃക്ഷം_TYPE (arg0)) < TYPE_PRECISION (result_type)
	      && വൃക്ഷം_int_cst_sgn (op1) > 0
	      /* We can shorten only if the shift count is less than the
		 number of bits in the smaller type size.  */
	      && compare_വൃക്ഷം_int (op1, TYPE_PRECISION (വൃക്ഷം_TYPE (arg0))) < 0
	      /* We cannot drop an unsigned shift after sign-extension.  */
	      && (!TYPE_UNSIGNED (final_type) || unsigned_arg))
	    {
	      /* Do an unsigned shift if the operand was zero-extended.  */
	      result_type
		= c_common_signed_or_unsigned_type (unsigned_arg,
						    വൃക്ഷം_TYPE (arg0));
	      /* Convert value-to-be-shifted to that type.  */
	      എങ്കിൽ (വൃക്ഷം_TYPE (op0) != result_type)
		op0 = convert (result_type, op0);
	      converted = 1;
	    }
	}

      /* Comparison operations are shortened too but differently.
	 They identify themselves by setting short_compare = 1.  */

      എങ്കിൽ (short_compare)
	{
	  /* Don't write &op0, etc., because that would prevent op0
	     from being kept in a register.
	     Instead, make copies of the our local variables and
	     pass the copies by reference, then copy them back afterward.  */
	  വൃക്ഷം xop0 = op0, xop1 = op1, xresult_type = result_type;
	  എണ്ണൽ വൃക്ഷം_code xresultcode = resultcode;
	  വൃക്ഷം val
	    = shorten_compare (location, &xop0, &xop1, &xresult_type,
			       &xresultcode);

	  എങ്കിൽ (val != NULL_വൃക്ഷം)
	    {
	      ret = val;
	      പോകുക return_build_ദ്വിമാന_op;
	    }

	  op0 = xop0, op1 = xop1;
	  converted = 1;
	  resultcode = xresultcode;

	  എങ്കിൽ (c_inhibit_evaluation_warnings == 0 && !c_in_omp_for)
	    {
	      തർക്കം op0_maybe_const = സത്യം;
	      തർക്കം op1_maybe_const = സത്യം;
	      വൃക്ഷം orig_op0_folded, orig_op1_folded;

	      എങ്കിൽ (in_late_ദ്വിമാന_op)
		{
		  orig_op0_folded = orig_op0;
		  orig_op1_folded = orig_op1;
		}
	      അല്ലെങ്കിൽ
		{
		  /* Fold for the sake of possible warnings, as in
		     build_conditional_expr.  This requires the
		     "original" values to be folded, not just op0 and
		     op1.  */
		  c_inhibit_evaluation_warnings++;
		  op0 = c_fully_fold (op0, require_constant_മൂല്യം,
				      &op0_maybe_const);
		  op1 = c_fully_fold (op1, require_constant_മൂല്യം,
				      &op1_maybe_const);
		  c_inhibit_evaluation_warnings--;
		  orig_op0_folded = c_fully_fold (orig_op0,
						  require_constant_മൂല്യം,
						  ശൂന്യ);
		  orig_op1_folded = c_fully_fold (orig_op1,
						  require_constant_മൂല്യം,
						  ശൂന്യ);
		}

	      എങ്കിൽ (warn_sign_compare)
		warn_for_sign_compare (location, orig_op0_folded,
				       orig_op1_folded, op0, op1,
				       result_type, resultcode);
	      എങ്കിൽ (!in_late_ദ്വിമാന_op && !int_operands)
		{
		  എങ്കിൽ (!op0_maybe_const || വൃക്ഷം_CODE (op0) != INTEGER_CST)
		    op0 = c_wrap_maybe_const (op0, !op0_maybe_const);
		  എങ്കിൽ (!op1_maybe_const || വൃക്ഷം_CODE (op1) != INTEGER_CST)
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

  എങ്കിൽ (!result_type)
    {
      /* Favor showing any expression locations that are available. */
      op_location_t oploc (location, UNKNOWN_LOCATION);
      ദ്വിമാന_op_rich_location richloc (oploc, orig_op0, orig_op1, സത്യം);
      ദ്വിമാന_op_error (&richloc, code, വൃക്ഷം_TYPE (op0), വൃക്ഷം_TYPE (op1));
      തിരികെ error_mark_കണ്ണി;
    }

  എങ്കിൽ (build_type == NULL_വൃക്ഷം)
    {
      build_type = result_type;
      എങ്കിൽ ((type0 != orig_type0 || type1 != orig_type1)
	  && !boolean_op)
	{
	  gcc_assert (may_need_excess_precision && common);
	  semantic_result_type = c_common_type (orig_type0, orig_type1);
	}
    }

  എങ്കിൽ (!converted)
    {
      op0 = ep_convert_and_check (location, result_type, op0,
				  semantic_result_type);
      op1 = ep_convert_and_check (location, result_type, op1,
				  semantic_result_type);

      /* This can happen if one operand has a vector type, and the other
	 has a different type.  */
      എങ്കിൽ (വൃക്ഷം_CODE (op0) == ERROR_MARK || വൃക്ഷം_CODE (op1) == ERROR_MARK)
	തിരികെ error_mark_കണ്ണി;
    }

  എങ്കിൽ (sanitize_flags_p ((SANITIZE_SHIFT
			 | SANITIZE_DIVIDE
			 | SANITIZE_FLOAT_DIVIDE
			 | SANITIZE_SI_OVERFLOW))
      && current_function_decl != NULL_വൃക്ഷം
      && (doing_div_or_mod || doing_shift)
      && !require_constant_മൂല്യം)
    {
      /* OP0 and/or OP1 might have side-effects.  */
      op0 = save_വ്യഞ്ജകം (op0);
      op1 = save_വ്യഞ്ജകം (op1);
      op0 = c_fully_fold (op0, അസത്യം, ശൂന്യ);
      op1 = c_fully_fold (op1, അസത്യം, ശൂന്യ);
      എങ്കിൽ (doing_div_or_mod && (sanitize_flags_p ((SANITIZE_DIVIDE
						  | SANITIZE_FLOAT_DIVIDE
						  | SANITIZE_SI_OVERFLOW))))
	instrument_വ്യഞ്ജകം = ubsan_instrument_division (location, op0, op1);
      അല്ലെങ്കിൽ എങ്കിൽ (doing_shift && sanitize_flags_p (SANITIZE_SHIFT))
	instrument_വ്യഞ്ജകം = ubsan_instrument_shift (location, code, op0, op1);
    }

  /* Treat expressions in initializers specially as they can't trap.  */
  എങ്കിൽ (int_const_or_overflow)
    ret = (require_constant_മൂല്യം
	   ? fold_build2_initializer_loc (location, resultcode, build_type,
					  op0, op1)
	   : fold_build2_loc (location, resultcode, build_type, op0, op1));
  അല്ലെങ്കിൽ
    ret = build2 (resultcode, build_type, op0, op1);
  എങ്കിൽ (final_type != NULL_വൃക്ഷം)
    ret = convert (final_type, ret);

 return_build_ദ്വിമാന_op:
  gcc_assert (ret != error_mark_കണ്ണി);
  എങ്കിൽ (വൃക്ഷം_CODE (ret) == INTEGER_CST && !വൃക്ഷം_OVERFLOW (ret) && !int_const)
    ret = (int_operands
	   ? note_integer_operands (ret)
	   : build1 (NOP_വ്യഞ്ജകം, വൃക്ഷം_TYPE (ret), ret));
  അല്ലെങ്കിൽ എങ്കിൽ (വൃക്ഷം_CODE (ret) != INTEGER_CST && int_operands
	   && !in_late_ദ്വിമാന_op)
    ret = note_integer_operands (ret);
  protected_set_വ്യഞ്ജകം_location (ret, location);

  എങ്കിൽ (instrument_വ്യഞ്ജകം != ശൂന്യ)
    ret = fold_build2 (COMPOUND_വ്യഞ്ജകം, വൃക്ഷം_TYPE (ret),
		       instrument_വ്യഞ്ജകം, ret);

  എങ്കിൽ (semantic_result_type)
    ret = build1_loc (location, EXCESS_PRECISION_വ്യഞ്ജകം,
		      semantic_result_type, ret);

  തിരികെ ret;
}


/* Convert EXPR to be a truth-value (type TYPE), validating its type for this
   purpose.  LOCATION is the source location for the expression.  */

വൃക്ഷം
c_objc_common_truthvalue_conversion (location_t location, വൃക്ഷം വ്യഞ്ജകം, വൃക്ഷം type)
{
  തർക്കം int_const, int_operands;

  തിരഞ്ഞെടുപ്പ് (വൃക്ഷം_CODE (വൃക്ഷം_TYPE (വ്യഞ്ജകം)))
    {
    അവസ്ഥ ARRAY_TYPE:
      error_at (location, "used array that cannot be converted to pointer where scalar is required");
      തിരികെ error_mark_കണ്ണി;

    അവസ്ഥ RECORD_TYPE:
      error_at (location, "used struct type value where scalar is required");
      തിരികെ error_mark_കണ്ണി;

    അവസ്ഥ UNION_TYPE:
      error_at (location, "used union type value where scalar is required");
      തിരികെ error_mark_കണ്ണി;

    അവസ്ഥ VOID_TYPE:
      error_at (location, "void value not ignored as it ought to be");
      തിരികെ error_mark_കണ്ണി;

    അവസ്ഥ POINTER_TYPE:
      എങ്കിൽ (reject_gcc_builtin (വ്യഞ്ജകം))
	തിരികെ error_mark_കണ്ണി;
      നിർത്തുക;

    അവസ്ഥ FUNCTION_TYPE:
      gcc_unreachable ();

    അവസ്ഥ VECTOR_TYPE:
      error_at (location, "used vector type where scalar is required");
      തിരികെ error_mark_കണ്ണി;

    സ്ഥിരസ്ഥിതി:
      നിർത്തുക;
    }

  /* Conversion of a floating constant to boolean goes through here
     and yields an integer constant expression.  Otherwise, the result
     is only an integer constant expression if the argument is.  */
  int_const = ((വൃക്ഷം_CODE (വ്യഞ്ജകം) == INTEGER_CST && !വൃക്ഷം_OVERFLOW (വ്യഞ്ജകം))
	       || ((വൃക്ഷം_CODE (വ്യഞ്ജകം) == REAL_CST
		    || വൃക്ഷം_CODE (വ്യഞ്ജകം) == COMPLEX_CST)
		   && (വൃക്ഷം_CODE (type) == BOOLEAN_TYPE
		       || (വൃക്ഷം_CODE (type) == ENUMERAL_TYPE
			   && ENUM_UNDERLYING_TYPE (type) != NULL_വൃക്ഷം
			   && (വൃക്ഷം_CODE (ENUM_UNDERLYING_TYPE (type))
			       == BOOLEAN_TYPE)))));
  int_operands = വ്യഞ്ജകം_INT_CONST_OPERANDS (വ്യഞ്ജകം);
  എങ്കിൽ (int_operands && വൃക്ഷം_CODE (വ്യഞ്ജകം) != INTEGER_CST)
    {
      വ്യഞ്ജകം = remove_c_maybe_const_വ്യഞ്ജകം (വ്യഞ്ജകം);
      വ്യഞ്ജകം = build2 (NE_വ്യഞ്ജകം, type, വ്യഞ്ജകം,
		     convert (വൃക്ഷം_TYPE (വ്യഞ്ജകം), integer_zero_കണ്ണി));
      വ്യഞ്ജകം = note_integer_operands (വ്യഞ്ജകം);
    }
  അല്ലെങ്കിൽ
    {
      /* ??? Should we also give an error for vectors rather than leaving
	 those to give errors later?  */
      വ്യഞ്ജകം = c_common_truthvalue_conversion (location, വ്യഞ്ജകം);
      വ്യഞ്ജകം = fold_convert_loc (location, type, വ്യഞ്ജകം);
    }

  എങ്കിൽ (വൃക്ഷം_CODE (വ്യഞ്ജകം) == INTEGER_CST && int_operands && !int_const)
    {
      എങ്കിൽ (വൃക്ഷം_OVERFLOW (വ്യഞ്ജകം))
	തിരികെ വ്യഞ്ജകം;
      അല്ലെങ്കിൽ
	തിരികെ note_integer_operands (വ്യഞ്ജകം);
    }
  എങ്കിൽ (വൃക്ഷം_CODE (വ്യഞ്ജകം) == INTEGER_CST && !int_const)
    തിരികെ build1 (NOP_വ്യഞ്ജകം, വൃക്ഷം_TYPE (വ്യഞ്ജകം), വ്യഞ്ജകം);
  തിരികെ വ്യഞ്ജകം;
}


/* Convert EXPR to a contained DECL, updating *TC, *TI and *SE as
   required.  */

വൃക്ഷം
c_വ്യഞ്ജകം_to_decl (വൃക്ഷം വ്യഞ്ജകം, തർക്കം *tc ATTRIBUTE_UNUSED, തർക്കം *se)
{
  എങ്കിൽ (വൃക്ഷം_CODE (വ്യഞ്ജകം) == COMPOUND_LITERAL_വ്യഞ്ജകം)
    {
      വൃക്ഷം decl = COMPOUND_LITERAL_വ്യഞ്ജകം_DECL (വ്യഞ്ജകം);
      /* Executing a compound literal inside a function reinitializes
	 it.  */
      എങ്കിൽ (!വൃക്ഷം_STATIC (decl))
	*se = സത്യം;
      തിരികെ decl;
    }
  അല്ലെങ്കിൽ
    തിരികെ വ്യഞ്ജകം;
}

/* Generate OMP construct CODE, with BODY and CLAUSES as its compound
   statement.  LOC is the location of the construct.  */

വൃക്ഷം
c_finish_omp_construct (location_t loc, എണ്ണൽ വൃക്ഷം_code code, വൃക്ഷം body,
			വൃക്ഷം clauses)
{
  body = c_end_compound_stmt (loc, body, സത്യം);

  വൃക്ഷം stmt = make_കണ്ണി (code);
  വൃക്ഷം_TYPE (stmt) = void_type_കണ്ണി;
  OMP_BODY (stmt) = body;
  OMP_CLAUSES (stmt) = clauses;
  SET_വ്യഞ്ജകം_LOCATION (stmt, loc);

  തിരികെ add_stmt (stmt);
}

/* Generate OACC_DATA, with CLAUSES and BLOCK as its compound
   statement.  LOC is the location of the OACC_DATA.  */

വൃക്ഷം
c_finish_oacc_data (location_t loc, വൃക്ഷം clauses, വൃക്ഷം block)
{
  വൃക്ഷം stmt;

  block = c_end_compound_stmt (loc, block, സത്യം);

  stmt = make_കണ്ണി (OACC_DATA);
  വൃക്ഷം_TYPE (stmt) = void_type_കണ്ണി;
  OACC_DATA_CLAUSES (stmt) = clauses;
  OACC_DATA_BODY (stmt) = block;
  SET_വ്യഞ്ജകം_LOCATION (stmt, loc);

  തിരികെ add_stmt (stmt);
}

/* Generate OACC_HOST_DATA, with CLAUSES and BLOCK as its compound
   statement.  LOC is the location of the OACC_HOST_DATA.  */

വൃക്ഷം
c_finish_oacc_host_data (location_t loc, വൃക്ഷം clauses, വൃക്ഷം block)
{
  വൃക്ഷം stmt;

  block = c_end_compound_stmt (loc, block, സത്യം);

  stmt = make_കണ്ണി (OACC_HOST_DATA);
  വൃക്ഷം_TYPE (stmt) = void_type_കണ്ണി;
  OACC_HOST_DATA_CLAUSES (stmt) = clauses;
  OACC_HOST_DATA_BODY (stmt) = block;
  SET_വ്യഞ്ജകം_LOCATION (stmt, loc);

  തിരികെ add_stmt (stmt);
}

/* Like c_begin_compound_stmt, except force the retention of the BLOCK.  */

വൃക്ഷം
c_begin_omp_parallel (ശൂന്യം)
{
  വൃക്ഷം block;

  keep_next_level ();
  block = c_begin_compound_stmt (സത്യം);

  തിരികെ block;
}

/* Generate OMP_PARALLEL, with CLAUSES and BLOCK as its compound
   statement.  LOC is the location of the OMP_PARALLEL.  */

വൃക്ഷം
c_finish_omp_parallel (location_t loc, വൃക്ഷം clauses, വൃക്ഷം block)
{
  വൃക്ഷം stmt;

  block = c_end_compound_stmt (loc, block, സത്യം);

  stmt = make_കണ്ണി (OMP_PARALLEL);
  വൃക്ഷം_TYPE (stmt) = void_type_കണ്ണി;
  OMP_PARALLEL_CLAUSES (stmt) = clauses;
  OMP_PARALLEL_BODY (stmt) = block;
  SET_വ്യഞ്ജകം_LOCATION (stmt, loc);

  തിരികെ add_stmt (stmt);
}

/* Like c_begin_compound_stmt, except force the retention of the BLOCK.  */

വൃക്ഷം
c_begin_omp_task (ശൂന്യം)
{
  വൃക്ഷം block;

  keep_next_level ();
  block = c_begin_compound_stmt (സത്യം);

  തിരികെ block;
}

/* Generate OMP_TASK, with CLAUSES and BLOCK as its compound
   statement.  LOC is the location of the #pragma.  */

വൃക്ഷം
c_finish_omp_task (location_t loc, വൃക്ഷം clauses, വൃക്ഷം block)
{
  വൃക്ഷം stmt;

  block = c_end_compound_stmt (loc, block, സത്യം);

  stmt = make_കണ്ണി (OMP_TASK);
  വൃക്ഷം_TYPE (stmt) = void_type_കണ്ണി;
  OMP_TASK_CLAUSES (stmt) = clauses;
  OMP_TASK_BODY (stmt) = block;
  SET_വ്യഞ്ജകം_LOCATION (stmt, loc);

  തിരികെ add_stmt (stmt);
}

/* Generate GOMP_cancel call for #pragma omp cancel.  */

ശൂന്യം
c_finish_omp_cancel (location_t loc, വൃക്ഷം clauses)
{
  വൃക്ഷം fn = builtin_decl_explicit (BUILT_IN_GOMP_CANCEL);
  പൂർണ്ണസംഖ്യ mask = 0;
  എങ്കിൽ (omp_find_clause (clauses, OMP_CLAUSE_PARALLEL))
    mask = 1;
  അല്ലെങ്കിൽ എങ്കിൽ (omp_find_clause (clauses, OMP_CLAUSE_FOR))
    mask = 2;
  അല്ലെങ്കിൽ എങ്കിൽ (omp_find_clause (clauses, OMP_CLAUSE_SECTIONS))
    mask = 4;
  അല്ലെങ്കിൽ എങ്കിൽ (omp_find_clause (clauses, OMP_CLAUSE_TASKGROUP))
    mask = 8;
  അല്ലെങ്കിൽ
    {
      error_at (loc, "%<#pragma omp cancel%> must specify one of "
		     "%<parallel%>, %<for%>, %<sections%> or %<taskgroup%> "
		     "clauses");
      തിരികെ;
    }
  വൃക്ഷം ifc = omp_find_clause (clauses, OMP_CLAUSE_IF);
  എങ്കിൽ (ifc != NULL_വൃക്ഷം)
    {
      എങ്കിൽ (OMP_CLAUSE_IF_MODIFIER (ifc) != ERROR_MARK
	  && OMP_CLAUSE_IF_MODIFIER (ifc) != VOID_CST)
	error_at (OMP_CLAUSE_LOCATION (ifc),
		  "expected %<cancel%> %<if%> clause modifier");
      അല്ലെങ്കിൽ
	{
	  വൃക്ഷം ifc2 = omp_find_clause (OMP_CLAUSE_CHAIN (ifc), OMP_CLAUSE_IF);
	  എങ്കിൽ (ifc2 != NULL_വൃക്ഷം)
	    {
	      gcc_assert (OMP_CLAUSE_IF_MODIFIER (ifc) == VOID_CST
			  && OMP_CLAUSE_IF_MODIFIER (ifc2) != ERROR_MARK
			  && OMP_CLAUSE_IF_MODIFIER (ifc2) != VOID_CST);
	      error_at (OMP_CLAUSE_LOCATION (ifc2),
			"expected %<cancel%> %<if%> clause modifier");
	    }
	}

      വൃക്ഷം type = വൃക്ഷം_TYPE (OMP_CLAUSE_IF_വ്യഞ്ജകം (ifc));
      ifc = fold_build2_loc (OMP_CLAUSE_LOCATION (ifc), NE_വ്യഞ്ജകം,
			     boolean_type_കണ്ണി, OMP_CLAUSE_IF_വ്യഞ്ജകം (ifc),
			     build_zero_cst (type));
    }
  അല്ലെങ്കിൽ
    ifc = boolean_true_കണ്ണി;
  വൃക്ഷം stmt = build_call_വ്യഞ്ജകം_loc (loc, fn, 2,
				   build_int_cst (integer_type_കണ്ണി, mask),
				   ifc);
  add_stmt (stmt);
}

/* Generate GOMP_cancellation_point call for
   #pragma omp cancellation point.  */

ശൂന്യം
c_finish_omp_cancellation_point (location_t loc, വൃക്ഷം clauses)
{
  വൃക്ഷം fn = builtin_decl_explicit (BUILT_IN_GOMP_CANCELLATION_POINT);
  പൂർണ്ണസംഖ്യ mask = 0;
  എങ്കിൽ (omp_find_clause (clauses, OMP_CLAUSE_PARALLEL))
    mask = 1;
  അല്ലെങ്കിൽ എങ്കിൽ (omp_find_clause (clauses, OMP_CLAUSE_FOR))
    mask = 2;
  അല്ലെങ്കിൽ എങ്കിൽ (omp_find_clause (clauses, OMP_CLAUSE_SECTIONS))
    mask = 4;
  അല്ലെങ്കിൽ എങ്കിൽ (omp_find_clause (clauses, OMP_CLAUSE_TASKGROUP))
    mask = 8;
  അല്ലെങ്കിൽ
    {
      error_at (loc, "%<#pragma omp cancellation point%> must specify one of "
		     "%<parallel%>, %<for%>, %<sections%> or %<taskgroup%> "
		     "clauses");
      തിരികെ;
    }
  വൃക്ഷം stmt = build_call_വ്യഞ്ജകം_loc (loc, fn, 1,
				   build_int_cst (integer_type_കണ്ണി, mask));
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

സ്ഥിതം വൃക്ഷം
handle_omp_array_sections_1 (വൃക്ഷം c, വൃക്ഷം t, vec<വൃക്ഷം> &types,
			     തർക്കം &maybe_zero_len, unsigned പൂർണ്ണസംഖ്യ &first_non_one,
			     എണ്ണൽ c_omp_region_type ort)
{
  വൃക്ഷം ret, താഴെയുള്ള_bound, length, type;
  തർക്കം openacc = (ort & C_ORT_ACC) != 0;
  എങ്കിൽ (വൃക്ഷം_CODE (t) != OMP_ARRAY_SECTION)
    {
      എങ്കിൽ (error_operand_p (t))
	തിരികെ error_mark_കണ്ണി;
      c_omp_address_inspector ai (OMP_CLAUSE_LOCATION (c), t);
      ret = t;
      എങ്കിൽ (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_AFFINITY
	  && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_DEPEND
	  && TYPE_ATOMIC (strip_array_types (വൃക്ഷം_TYPE (t))))
	{
	  error_at (OMP_CLAUSE_LOCATION (c), "%<_Atomic%> %qE in %qs clause",
		    t, omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	  തിരികെ error_mark_കണ്ണി;
	}
      എങ്കിൽ (!ai.check_clause (c))
	തിരികെ error_mark_കണ്ണി;
      അല്ലെങ്കിൽ എങ്കിൽ (ai.component_access_p ()
	       && (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP
		   || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_TO
		   || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_FROM))
	t = ai.get_വേര്_term (സത്യം);
      അല്ലെങ്കിൽ
	t = ai.unconverted_ref_origin ();
      എങ്കിൽ (t == error_mark_കണ്ണി)
	തിരികെ error_mark_കണ്ണി;
      എങ്കിൽ (!VAR_P (t)
	  && (ort == C_ORT_ACC || !വ്യഞ്ജകം_P (t))
	  && വൃക്ഷം_CODE (t) != PARM_DECL)
	{
	  എങ്കിൽ (DECL_P (t))
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%qD is not a variable in %qs clause", t,
		      omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	  അല്ലെങ്കിൽ
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%qE is not a variable in %qs clause", t,
		      omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	  തിരികെ error_mark_കണ്ണി;
	}
      അല്ലെങ്കിൽ എങ്കിൽ (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_AFFINITY
	       && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_DEPEND
	       && TYPE_ATOMIC (വൃക്ഷം_TYPE (t)))
	{
	  error_at (OMP_CLAUSE_LOCATION (c), "%<_Atomic%> %qD in %qs clause",
		    t, omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	  തിരികെ error_mark_കണ്ണി;
	}
      അല്ലെങ്കിൽ എങ്കിൽ (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_AFFINITY
	       && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_DEPEND
	       && VAR_P (t)
	       && DECL_THREAD_LOCAL_P (t))
	{
	  error_at (OMP_CLAUSE_LOCATION (c),
		    "%qD is threadprivate variable in %qs clause", t,
		    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	  തിരികെ error_mark_കണ്ണി;
	}
      എങ്കിൽ ((OMP_CLAUSE_CODE (c) == OMP_CLAUSE_AFFINITY
	   || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND)
	  && TYPE_ATOMIC (വൃക്ഷം_TYPE (t))
	  && POINTER_TYPE_P (വൃക്ഷം_TYPE (t)))
	{
	  /* If the array section is pointer based and the pointer
	     itself is _Atomic qualified, we need to atomically load
	     the pointer.  */
	  ret = convert_lvalue_to_rvalue (OMP_CLAUSE_LOCATION (c),
					  ret, അസത്യം, അസത്യം);
	}
      തിരികെ ret;
    }

  ret = handle_omp_array_sections_1 (c, വൃക്ഷം_OPERAND (t, 0), types,
				     maybe_zero_len, first_non_one, ort);
  എങ്കിൽ (ret == error_mark_കണ്ണി || ret == NULL_വൃക്ഷം)
    തിരികെ ret;

  type = വൃക്ഷം_TYPE (ret);
  താഴെയുള്ള_bound = വൃക്ഷം_OPERAND (t, 1);
  length = വൃക്ഷം_OPERAND (t, 2);

  എങ്കിൽ (താഴെയുള്ള_bound == error_mark_കണ്ണി || length == error_mark_കണ്ണി)
    തിരികെ error_mark_കണ്ണി;

  എങ്കിൽ (താഴെയുള്ള_bound && !INTEGRAL_TYPE_P (വൃക്ഷം_TYPE (താഴെയുള്ള_bound)))
    {
      error_at (OMP_CLAUSE_LOCATION (c),
		"low bound %qE of array section does not have integral type",
		താഴെയുള്ള_bound);
      തിരികെ error_mark_കണ്ണി;
    }
  എങ്കിൽ (length && !INTEGRAL_TYPE_P (വൃക്ഷം_TYPE (length)))
    {
      error_at (OMP_CLAUSE_LOCATION (c),
		"length %qE of array section does not have integral type",
		length);
      തിരികെ error_mark_കണ്ണി;
    }
  എങ്കിൽ (താഴെയുള്ള_bound
      && വൃക്ഷം_CODE (താഴെയുള്ള_bound) == INTEGER_CST
      && TYPE_PRECISION (വൃക്ഷം_TYPE (താഴെയുള്ള_bound))
	 > TYPE_PRECISION (sizetype))
    താഴെയുള്ള_bound = fold_convert (sizetype, താഴെയുള്ള_bound);
  എങ്കിൽ (length
      && വൃക്ഷം_CODE (length) == INTEGER_CST
      && TYPE_PRECISION (വൃക്ഷം_TYPE (length))
	 > TYPE_PRECISION (sizetype))
    length = fold_convert (sizetype, length);
  എങ്കിൽ (താഴെയുള്ള_bound == NULL_വൃക്ഷം)
    താഴെയുള്ള_bound = integer_zero_കണ്ണി;
  എങ്കിൽ (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP
      && (OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_ATTACH
	  || OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_DETACH))
    {
      എങ്കിൽ (length != integer_one_കണ്ണി)
	{
	  error_at (OMP_CLAUSE_LOCATION (c),
		    "expected single pointer in %qs clause",
		    user_omp_clause_code_name (c, openacc));
	  തിരികെ error_mark_കണ്ണി;
	}
    }
  എങ്കിൽ (length != NULL_വൃക്ഷം)
    {
      എങ്കിൽ (!integer_nonzerop (length))
	{
	  എങ്കിൽ (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_AFFINITY
	      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND
	      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_REDUCTION
	      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IN_REDUCTION
	      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_TASK_REDUCTION)
	    {
	      എങ്കിൽ (integer_zerop (length))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "zero length array section in %qs clause",
			    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		  തിരികെ error_mark_കണ്ണി;
		}
	    }
	  അല്ലെങ്കിൽ
	    maybe_zero_len = സത്യം;
	}
      എങ്കിൽ (first_non_one == types.length ()
	  && (വൃക്ഷം_CODE (length) != INTEGER_CST || integer_onep (length)))
	first_non_one++;
    }
  എങ്കിൽ (വൃക്ഷം_CODE (type) == ARRAY_TYPE)
    {
      എങ്കിൽ (length == NULL_വൃക്ഷം
	  && (TYPE_DOMAIN (type) == NULL_വൃക്ഷം
	      || TYPE_MAX_മൂല്യം (TYPE_DOMAIN (type)) == NULL_വൃക്ഷം))
	{
	  error_at (OMP_CLAUSE_LOCATION (c),
		    "for unknown bound array type length expression must "
		    "be specified");
	  തിരികെ error_mark_കണ്ണി;
	}
      എങ്കിൽ (വൃക്ഷം_CODE (താഴെയുള്ള_bound) == INTEGER_CST
	  && വൃക്ഷം_int_cst_sgn (താഴെയുള്ള_bound) == -1)
	{
	  error_at (OMP_CLAUSE_LOCATION (c),
		    "negative low bound in array section in %qs clause",
		    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	  തിരികെ error_mark_കണ്ണി;
	}
      എങ്കിൽ (length != NULL_വൃക്ഷം
	  && വൃക്ഷം_CODE (length) == INTEGER_CST
	  && വൃക്ഷം_int_cst_sgn (length) == -1)
	{
	  error_at (OMP_CLAUSE_LOCATION (c),
		    "negative length in array section in %qs clause",
		    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	  തിരികെ error_mark_കണ്ണി;
	}
      എങ്കിൽ (TYPE_DOMAIN (type)
	  && TYPE_MAX_മൂല്യം (TYPE_DOMAIN (type))
	  && വൃക്ഷം_CODE (TYPE_MAX_മൂല്യം (TYPE_DOMAIN (type)))
			== INTEGER_CST)
	{
	  വൃക്ഷം size
	    = fold_convert (sizetype, TYPE_MAX_മൂല്യം (TYPE_DOMAIN (type)));
	  size = size_binop (PLUS_വ്യഞ്ജകം, size, size_one_കണ്ണി);
	  എങ്കിൽ (വൃക്ഷം_CODE (താഴെയുള്ള_bound) == INTEGER_CST)
	    {
	      എങ്കിൽ (വൃക്ഷം_int_cst_lt (size, താഴെയുള്ള_bound))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "low bound %qE above array section size "
			    "in %qs clause", താഴെയുള്ള_bound,
			    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		  തിരികെ error_mark_കണ്ണി;
		}
	      എങ്കിൽ (വൃക്ഷം_int_cst_equal (size, താഴെയുള്ള_bound))
		{
		  എങ്കിൽ (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_AFFINITY
		      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND
		      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_REDUCTION
		      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IN_REDUCTION
		      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_TASK_REDUCTION)
		    {
		      error_at (OMP_CLAUSE_LOCATION (c),
				"zero length array section in %qs clause",
				omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		      തിരികെ error_mark_കണ്ണി;
		    }
		  maybe_zero_len = സത്യം;
		}
	      അല്ലെങ്കിൽ എങ്കിൽ (length == NULL_വൃക്ഷം
		       && first_non_one == types.length ()
		       && വൃക്ഷം_int_cst_equal
			    (TYPE_MAX_മൂല്യം (TYPE_DOMAIN (type)),
			     താഴെയുള്ള_bound))
		first_non_one++;
	    }
	  അല്ലെങ്കിൽ എങ്കിൽ (length == NULL_വൃക്ഷം)
	    {
	      എങ്കിൽ (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_AFFINITY
		  && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_DEPEND
		  && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_REDUCTION
		  && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_IN_REDUCTION
		  && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_TASK_REDUCTION)
		maybe_zero_len = സത്യം;
	      എങ്കിൽ (first_non_one == types.length ())
		first_non_one++;
	    }
	  എങ്കിൽ (length && വൃക്ഷം_CODE (length) == INTEGER_CST)
	    {
	      എങ്കിൽ (വൃക്ഷം_int_cst_lt (size, length))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "length %qE above array section size "
			    "in %qs clause", length,
			    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		  തിരികെ error_mark_കണ്ണി;
		}
	      എങ്കിൽ (വൃക്ഷം_CODE (താഴെയുള്ള_bound) == INTEGER_CST)
		{
		  വൃക്ഷം lbpluslen
		    = size_binop (PLUS_വ്യഞ്ജകം,
				  fold_convert (sizetype, താഴെയുള്ള_bound),
				  fold_convert (sizetype, length));
		  എങ്കിൽ (വൃക്ഷം_CODE (lbpluslen) == INTEGER_CST
		      && വൃക്ഷം_int_cst_lt (size, lbpluslen))
		    {
		      error_at (OMP_CLAUSE_LOCATION (c),
				"high bound %qE above array section size "
				"in %qs clause", lbpluslen,
				omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		      തിരികെ error_mark_കണ്ണി;
		    }
		}
	    }
	}
      അല്ലെങ്കിൽ എങ്കിൽ (length == NULL_വൃക്ഷം)
	{
	  എങ്കിൽ (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_AFFINITY
	      && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_DEPEND
	      && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_REDUCTION
	      && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_IN_REDUCTION
	      && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_TASK_REDUCTION)
	    maybe_zero_len = സത്യം;
	  എങ്കിൽ (first_non_one == types.length ())
	    first_non_one++;
	}

      /* For [lb:] we will need to evaluate lb more than once.  */
      എങ്കിൽ (length == NULL_വൃക്ഷം && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_DEPEND)
	{
	  വൃക്ഷം lb = save_വ്യഞ്ജകം (താഴെയുള്ള_bound);
	  എങ്കിൽ (lb != താഴെയുള്ള_bound)
	    {
	      വൃക്ഷം_OPERAND (t, 1) = lb;
	      താഴെയുള്ള_bound = lb;
	    }
	}
    }
  അല്ലെങ്കിൽ എങ്കിൽ (വൃക്ഷം_CODE (type) == POINTER_TYPE)
    {
      എങ്കിൽ (length == NULL_വൃക്ഷം)
	{
	  എങ്കിൽ (വൃക്ഷം_CODE (ret) == PARM_DECL && C_ARRAY_PARAMETER (ret))
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "for array function parameter length expression "
		      "must be specified");
	  അല്ലെങ്കിൽ
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "for pointer type length expression must be specified");
	  തിരികെ error_mark_കണ്ണി;
	}
      എങ്കിൽ (length != NULL_വൃക്ഷം
	  && വൃക്ഷം_CODE (length) == INTEGER_CST
	  && വൃക്ഷം_int_cst_sgn (length) == -1)
	{
	  error_at (OMP_CLAUSE_LOCATION (c),
		    "negative length in array section in %qs clause",
		    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	  തിരികെ error_mark_കണ്ണി;
	}
      /* If there is a pointer type anywhere but in the very first
	 array-section-subscript, the array section could be non-contiguous.  */
      എങ്കിൽ (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_DEPEND
	  && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_AFFINITY
	  && വൃക്ഷം_CODE (വൃക്ഷം_OPERAND (t, 0)) == OMP_ARRAY_SECTION)
	{
	  /* If any prior dimension has a non-one length, then deem this
	     array section as non-contiguous.  */
	  വേണ്ടി (വൃക്ഷം d = വൃക്ഷം_OPERAND (t, 0);
	       വൃക്ഷം_CODE (d) == OMP_ARRAY_SECTION;
	       d = വൃക്ഷം_OPERAND (d, 0))
	    {
	      വൃക്ഷം d_length = വൃക്ഷം_OPERAND (d, 2);
	      എങ്കിൽ (d_length == NULL_വൃക്ഷം || !integer_onep (d_length))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "array section is not contiguous in %qs clause",
			    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		  തിരികെ error_mark_കണ്ണി;
		}
	    }
	}
    }
  അല്ലെങ്കിൽ
    {
      error_at (OMP_CLAUSE_LOCATION (c),
		"%qE does not have pointer or array type", ret);
      തിരികെ error_mark_കണ്ണി;
    }
  എങ്കിൽ (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_DEPEND)
    types.safe_തള്ളുക (വൃക്ഷം_TYPE (ret));
  /* We will need to evaluate lb more than once.  */
  വൃക്ഷം lb = save_വ്യഞ്ജകം (താഴെയുള്ള_bound);
  എങ്കിൽ (lb != താഴെയുള്ള_bound)
    {
      വൃക്ഷം_OPERAND (t, 1) = lb;
      താഴെയുള്ള_bound = lb;
    }
  ret = build_array_ref (OMP_CLAUSE_LOCATION (c), ret, താഴെയുള്ള_bound);
  തിരികെ ret;
}

/* Handle array sections for clause C.  */

സ്ഥിതം തർക്കം
handle_omp_array_sections (വൃക്ഷം &c, എണ്ണൽ c_omp_region_type ort)
{
  തർക്കം maybe_zero_len = അസത്യം;
  unsigned പൂർണ്ണസംഖ്യ first_non_one = 0;
  auto_vec<വൃക്ഷം, 10> types;
  വൃക്ഷം *tp = &OMP_CLAUSE_DECL (c);
  എങ്കിൽ ((OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND
       || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_AFFINITY)
      && OMP_ITERATOR_DECL_P (*tp))
    tp = &വൃക്ഷം_മൂല്യം (*tp);
  വൃക്ഷം first = handle_omp_array_sections_1 (c, *tp, types,
					    maybe_zero_len, first_non_one,
					    ort);
  എങ്കിൽ (first == error_mark_കണ്ണി)
    തിരികെ സത്യം;
  എങ്കിൽ (first == NULL_വൃക്ഷം)
    തിരികെ അസത്യം;
  എങ്കിൽ (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND
      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_AFFINITY)
    {
      വൃക്ഷം t = *tp;
      വൃക്ഷം tem = NULL_വൃക്ഷം;
      /* Need to evaluate side effects in the length expressions
	 if any.  */
      ആകുമ്പോൾ (വൃക്ഷം_CODE (t) == വൃക്ഷം_LIST)
	{
	  എങ്കിൽ (വൃക്ഷം_മൂല്യം (t) && വൃക്ഷം_SIDE_EFFECTS (വൃക്ഷം_മൂല്യം (t)))
	    {
	      എങ്കിൽ (tem == NULL_വൃക്ഷം)
		tem = വൃക്ഷം_മൂല്യം (t);
	      അല്ലെങ്കിൽ
		tem = build2 (COMPOUND_വ്യഞ്ജകം, വൃക്ഷം_TYPE (tem),
			      വൃക്ഷം_മൂല്യം (t), tem);
	    }
	  t = വൃക്ഷം_CHAIN (t);
	}
      എങ്കിൽ (tem)
	first = build2 (COMPOUND_വ്യഞ്ജകം, വൃക്ഷം_TYPE (first), tem, first);
      first = c_fully_fold (first, അസത്യം, ശൂന്യ, സത്യം);
      *tp = first;
    }
  അല്ലെങ്കിൽ
    {
      unsigned പൂർണ്ണസംഖ്യ അക്കം = types.length (), i;
      വൃക്ഷം t, side_effects = NULL_വൃക്ഷം, size = NULL_വൃക്ഷം;
      വൃക്ഷം condition = NULL_വൃക്ഷം;

      എങ്കിൽ (int_size_in_bytes (വൃക്ഷം_TYPE (first)) <= 0)
	maybe_zero_len = സത്യം;

      വേണ്ടി (i = അക്കം, t = OMP_CLAUSE_DECL (c); i > 0;
	   t = വൃക്ഷം_OPERAND (t, 0))
	{
	  വൃക്ഷം താഴെയുള്ള_bound = വൃക്ഷം_OPERAND (t, 1);
	  വൃക്ഷം length = വൃക്ഷം_OPERAND (t, 2);

	  i--;
	  എങ്കിൽ (താഴെയുള്ള_bound
	      && വൃക്ഷം_CODE (താഴെയുള്ള_bound) == INTEGER_CST
	      && TYPE_PRECISION (വൃക്ഷം_TYPE (താഴെയുള്ള_bound))
		 > TYPE_PRECISION (sizetype))
	    താഴെയുള്ള_bound = fold_convert (sizetype, താഴെയുള്ള_bound);
	  എങ്കിൽ (length
	      && വൃക്ഷം_CODE (length) == INTEGER_CST
	      && TYPE_PRECISION (വൃക്ഷം_TYPE (length))
		 > TYPE_PRECISION (sizetype))
	    length = fold_convert (sizetype, length);
	  എങ്കിൽ (താഴെയുള്ള_bound == NULL_വൃക്ഷം)
	    താഴെയുള്ള_bound = integer_zero_കണ്ണി;
	  എങ്കിൽ (!maybe_zero_len && i > first_non_one)
	    {
	      എങ്കിൽ (integer_nonzerop (താഴെയുള്ള_bound))
		പോകുക do_warn_noncontiguous;
	      എങ്കിൽ (length != NULL_വൃക്ഷം
		  && വൃക്ഷം_CODE (length) == INTEGER_CST
		  && TYPE_DOMAIN (types[i])
		  && TYPE_MAX_മൂല്യം (TYPE_DOMAIN (types[i]))
		  && വൃക്ഷം_CODE (TYPE_MAX_മൂല്യം (TYPE_DOMAIN (types[i])))
		     == INTEGER_CST)
		{
		  വൃക്ഷം size;
		  size = size_binop (PLUS_വ്യഞ്ജകം,
				     TYPE_MAX_മൂല്യം (TYPE_DOMAIN (types[i])),
				     size_one_കണ്ണി);
		  എങ്കിൽ (!വൃക്ഷം_int_cst_equal (length, size))
		    {
		     do_warn_noncontiguous:
		      error_at (OMP_CLAUSE_LOCATION (c),
				"array section is not contiguous in %qs "
				"clause",
				omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		      തിരികെ സത്യം;
		    }
		}
	      എങ്കിൽ (length != NULL_വൃക്ഷം
		  && വൃക്ഷം_SIDE_EFFECTS (length))
		{
		  എങ്കിൽ (side_effects == NULL_വൃക്ഷം)
		    side_effects = length;
		  അല്ലെങ്കിൽ
		    side_effects = build2 (COMPOUND_വ്യഞ്ജകം,
					   വൃക്ഷം_TYPE (side_effects),
					   length, side_effects);
		}
	    }
	  അല്ലെങ്കിൽ
	    {
	      വൃക്ഷം l;

	      എങ്കിൽ (i > first_non_one
		  && ((length && integer_nonzerop (length))
		      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_REDUCTION
		      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IN_REDUCTION
		      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_TASK_REDUCTION))
		തുടരുക;
	      എങ്കിൽ (length)
		l = fold_convert (sizetype, length);
	      അല്ലെങ്കിൽ
		{
		  l = size_binop (PLUS_വ്യഞ്ജകം,
				  TYPE_MAX_മൂല്യം (TYPE_DOMAIN (types[i])),
				  size_one_കണ്ണി);
		  l = size_binop (MINUS_വ്യഞ്ജകം, l,
				  fold_convert (sizetype, താഴെയുള്ള_bound));
		}
	      എങ്കിൽ (i > first_non_one)
		{
		  l = fold_build2 (NE_വ്യഞ്ജകം, boolean_type_കണ്ണി, l,
				   size_zero_കണ്ണി);
		  എങ്കിൽ (condition == NULL_വൃക്ഷം)
		    condition = l;
		  അല്ലെങ്കിൽ
		    condition = fold_build2 (BIT_AND_വ്യഞ്ജകം, boolean_type_കണ്ണി,
					     l, condition);
		}
	      അല്ലെങ്കിൽ എങ്കിൽ (size == NULL_വൃക്ഷം)
		{
		  size = size_in_bytes (വൃക്ഷം_TYPE (types[i]));
		  വൃക്ഷം eltype = വൃക്ഷം_TYPE (types[അക്കം - 1]);
		  ആകുമ്പോൾ (വൃക്ഷം_CODE (eltype) == ARRAY_TYPE)
		    eltype = വൃക്ഷം_TYPE (eltype);
		  എങ്കിൽ (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_REDUCTION
		      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IN_REDUCTION
		      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_TASK_REDUCTION)
		    {
		      എങ്കിൽ (integer_zerop (size)
			  || integer_zerop (size_in_bytes (eltype)))
			{
			  error_at (OMP_CLAUSE_LOCATION (c),
				    "zero length array section in %qs clause",
				    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
			  തിരികെ error_mark_കണ്ണി;
			}
		      size = size_binop (EXACT_DIV_വ്യഞ്ജകം, size,
					 size_in_bytes (eltype));
		    }
		  size = size_binop (MULT_വ്യഞ്ജകം, size, l);
		  എങ്കിൽ (condition)
		    size = fold_build3 (COND_വ്യഞ്ജകം, sizetype, condition,
					size, size_zero_കണ്ണി);
		}
	      അല്ലെങ്കിൽ
		size = size_binop (MULT_വ്യഞ്ജകം, size, l);
	    }
	}
      എങ്കിൽ (side_effects)
	size = build2 (COMPOUND_വ്യഞ്ജകം, sizetype, side_effects, size);
      എങ്കിൽ (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_REDUCTION
	  || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IN_REDUCTION
	  || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_TASK_REDUCTION)
	{
	  size = size_binop (MINUS_വ്യഞ്ജകം, size, size_one_കണ്ണി);
	  size = c_fully_fold (size, അസത്യം, ശൂന്യ);
	  size = save_വ്യഞ്ജകം (size);
	  വൃക്ഷം index_type = build_index_type (size);
	  വൃക്ഷം eltype = വൃക്ഷം_TYPE (first);
	  ആകുമ്പോൾ (വൃക്ഷം_CODE (eltype) == ARRAY_TYPE)
	    eltype = വൃക്ഷം_TYPE (eltype);
	  വൃക്ഷം type = c_build_array_type (eltype, index_type);
	  വൃക്ഷം ptype = c_build_pointer_type (eltype);
	  എങ്കിൽ (വൃക്ഷം_CODE (വൃക്ഷം_TYPE (t)) == ARRAY_TYPE)
	    t = build_fold_addr_വ്യഞ്ജകം (t);
	  വൃക്ഷം t2 = build_fold_addr_വ്യഞ്ജകം (first);
	  t2 = fold_convert_loc (OMP_CLAUSE_LOCATION (c),
				 ptrdiff_type_കണ്ണി, t2);
	  t2 = fold_build2_loc (OMP_CLAUSE_LOCATION (c), MINUS_വ്യഞ്ജകം,
				ptrdiff_type_കണ്ണി, t2,
				fold_convert_loc (OMP_CLAUSE_LOCATION (c),
						  ptrdiff_type_കണ്ണി, t));
	  t2 = c_fully_fold (t2, അസത്യം, ശൂന്യ);
	  എങ്കിൽ (വൃക്ഷം_fits_shwi_p (t2))
	    t = build2 (MEM_REF, type, t,
			build_int_cst (ptype, വൃക്ഷം_to_shwi (t2)));
	  അല്ലെങ്കിൽ
	    {
	      t2 = fold_convert_loc (OMP_CLAUSE_LOCATION (c), sizetype, t2);
	      t = build2_loc (OMP_CLAUSE_LOCATION (c), POINTER_PLUS_വ്യഞ്ജകം,
			      വൃക്ഷം_TYPE (t), t, t2);
	      t = build2 (MEM_REF, type, t, build_int_cst (ptype, 0));
	    }
	  OMP_CLAUSE_DECL (c) = t;
	  തിരികെ അസത്യം;
	}
      first = c_fully_fold (first, അസത്യം, ശൂന്യ);
      OMP_CLAUSE_DECL (c) = first;
      എങ്കിൽ (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_HAS_DEVICE_ADDR)
	തിരികെ അസത്യം;
      /* Don't set OMP_CLAUSE_SIZE for bare attach/detach clauses.  */
      എങ്കിൽ (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_MAP
	  || (OMP_CLAUSE_MAP_KIND (c) != GOMP_MAP_ATTACH
	      && OMP_CLAUSE_MAP_KIND (c) != GOMP_MAP_DETACH
	      && OMP_CLAUSE_MAP_KIND (c) != GOMP_MAP_FORCE_DETACH))
	{
	  എങ്കിൽ (size)
	    size = c_fully_fold (size, അസത്യം, ശൂന്യ);
	  OMP_CLAUSE_SIZE (c) = size;
	}

      എങ്കിൽ (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_MAP)
	തിരികെ അസത്യം;

      auto_vec<omp_addr_token *, 10> addr_tokens;

      എങ്കിൽ (!omp_parse_വ്യഞ്ജകം (addr_tokens, first))
	തിരികെ സത്യം;

      c_omp_address_inspector ai (OMP_CLAUSE_LOCATION (c), t);

      വൃക്ഷം nc = ai.expand_map_clause (c, first, addr_tokens, ort);
      എങ്കിൽ (nc != error_mark_കണ്ണി)
	{
	  using നാമാകാശ omp_addr_tokenizer;

	  എങ്കിൽ (ai.maybe_zero_length_array_section (c))
	    OMP_CLAUSE_MAP_MAYBE_ZERO_LENGTH_ARRAY_SECTION (c) = 1;

	  /* !!! If we're accessing a base decl via chained access
	     methods (e.g. multiple indirections), duplicate clause
	     detection won't work properly.  Skip it in that case.  */
	  എങ്കിൽ ((addr_tokens[0]->type == STRUCTURE_BASE
	       || addr_tokens[0]->type == ARRAY_BASE)
	      && addr_tokens[0]->u.structure_base_kind == BASE_DECL
	      && addr_tokens[1]->type == ACCESS_METHOD
	      && omp_access_chain_p (addr_tokens, 1))
	    c = nc;

	  തിരികെ അസത്യം;
	}
    }
  തിരികെ അസത്യം;
}

/* Helper function of finish_omp_clauses.  Clone STMT as if we were making
   an inline call.  But, remap
   the OMP_DECL1 VAR_DECL (omp_out resp. omp_orig) to PLACEHOLDER
   and OMP_DECL2 VAR_DECL (omp_in resp. omp_priv) to DECL.  */

സ്ഥിതം വൃക്ഷം
c_clone_omp_udr (വൃക്ഷം stmt, വൃക്ഷം omp_decl1, വൃക്ഷം omp_decl2,
		 വൃക്ഷം decl, വൃക്ഷം placeholder)
{
  copy_body_data id;
  hash_map<വൃക്ഷം, വൃക്ഷം> decl_map;

  decl_map.put (omp_decl1, placeholder);
  decl_map.put (omp_decl2, decl);
  memset (&id, 0, വലുപ്പം (id));
  id.src_fn = DECL_CONTEXT (omp_decl1);
  id.dst_fn = current_function_decl;
  id.src_cfun = DECL_STRUCT_FUNCTION (id.src_fn);
  id.decl_map = &decl_map;

  id.copy_decl = copy_decl_no_change;
  id.transform_call_graph_edges = CB_CGE_DUPLICATE;
  id.transform_new_cfg = സത്യം;
  id.transform_return_to_modify = അസത്യം;
  id.eh_lp_nr = 0;
  walk_വൃക്ഷം (&stmt, copy_വൃക്ഷം_body_r, &id, ശൂന്യ);
  തിരികെ stmt;
}

/* Helper function of c_finish_omp_clauses, called via walk_tree.
   Find OMP_CLAUSE_PLACEHOLDER (passed in DATA) in *TP.  */

സ്ഥിതം വൃക്ഷം
c_find_omp_placeholder_r (വൃക്ഷം *tp, പൂർണ്ണസംഖ്യ *, ശൂന്യം *data)
{
  എങ്കിൽ (*tp == (വൃക്ഷം) data)
    തിരികെ *tp;
  തിരികെ NULL_വൃക്ഷം;
}

/* Similarly, but also walk aggregate fields.  */

ഘടന c_find_omp_var_s { വൃക്ഷം var; hash_set<വൃക്ഷം> *pset; };

സ്ഥിതം വൃക്ഷം
c_find_omp_var_r (വൃക്ഷം *tp, പൂർണ്ണസംഖ്യ *, ശൂന്യം *data)
{
  എങ്കിൽ (*tp == ((ഘടന c_find_omp_var_s *) data)->var)
    തിരികെ *tp;
  എങ്കിൽ (RECORD_OR_UNION_TYPE_P (*tp))
    {
      വൃക്ഷം field;
      hash_set<വൃക്ഷം> *pset = ((ഘടന c_find_omp_var_s *) data)->pset;

      വേണ്ടി (field = TYPE_FIELDS (*tp); field;
	   field = DECL_CHAIN (field))
	എങ്കിൽ (വൃക്ഷം_CODE (field) == FIELD_DECL)
	  {
	    വൃക്ഷം ret = walk_വൃക്ഷം (&DECL_FIELD_OFFSET (field),
				  c_find_omp_var_r, data, pset);
	    എങ്കിൽ (ret)
	      തിരികെ ret;
	    ret = walk_വൃക്ഷം (&DECL_SIZE (field), c_find_omp_var_r, data, pset);
	    എങ്കിൽ (ret)
	      തിരികെ ret;
	    ret = walk_വൃക്ഷം (&DECL_SIZE_UNIT (field), c_find_omp_var_r, data,
			     pset);
	    എങ്കിൽ (ret)
	      തിരികെ ret;
	    ret = walk_വൃക്ഷം (&വൃക്ഷം_TYPE (field), c_find_omp_var_r, data, pset);
	    എങ്കിൽ (ret)
	      തിരികെ ret;
	  }
    }
  അല്ലെങ്കിൽ എങ്കിൽ (INTEGRAL_TYPE_P (*tp))
    തിരികെ walk_വൃക്ഷം (&TYPE_MAX_മൂല്യം (*tp), c_find_omp_var_r, data,
		      ((ഘടന c_find_omp_var_s *) data)->pset);
  തിരികെ NULL_വൃക്ഷം;
}

/* Finish OpenMP iterators ITER.  Return true if they are erroneous
   and clauses containing them should be removed.  */

സ്ഥിതം തർക്കം
c_omp_finish_iterators (വൃക്ഷം iter)
{
  തർക്കം ret = അസത്യം;
  വേണ്ടി (വൃക്ഷം it = iter; it; it = വൃക്ഷം_CHAIN (it))
    {
      വൃക്ഷം var = OMP_ITERATOR_VAR (it);
      വൃക്ഷം begin = OMP_ITERATOR_BEGIN (it);
      വൃക്ഷം end = OMP_ITERATOR_END (it);
      വൃക്ഷം step = OMP_ITERATOR_STEP (it);
      വൃക്ഷം orig_step;
      വൃക്ഷം type = വൃക്ഷം_TYPE (var);
      location_t loc = DECL_SOURCE_LOCATION (var);
      എങ്കിൽ (type == error_mark_കണ്ണി)
	{
	  ret = സത്യം;
	  തുടരുക;
	}
      എങ്കിൽ (!INTEGRAL_TYPE_P (type) && !POINTER_TYPE_P (type))
	{
	  error_at (loc, "iterator %qD has neither integral nor pointer type",
		    var);
	  ret = സത്യം;
	  തുടരുക;
	}
      അല്ലെങ്കിൽ എങ്കിൽ (TYPE_ATOMIC (type))
	{
	  error_at (loc, "iterator %qD has %<_Atomic%> qualified type", var);
	  ret = സത്യം;
	  തുടരുക;
	}
      അല്ലെങ്കിൽ എങ്കിൽ (TYPE_READONLY (type))
	{
	  error_at (loc, "iterator %qD has const qualified type", var);
	  ret = സത്യം;
	  തുടരുക;
	}
      അല്ലെങ്കിൽ എങ്കിൽ (step == error_mark_കണ്ണി
	       || വൃക്ഷം_TYPE (step) == error_mark_കണ്ണി)
	{
	  ret = സത്യം;
	  തുടരുക;
	}
      അല്ലെങ്കിൽ എങ്കിൽ (!INTEGRAL_TYPE_P (വൃക്ഷം_TYPE (step)))
	{
	  error_at (വ്യഞ്ജകം_LOC_OR_LOC (step, loc),
		    "iterator step with non-integral type");
	  ret = സത്യം;
	  തുടരുക;
	}
      begin = c_fully_fold (build_c_cast (loc, type, begin), അസത്യം, ശൂന്യ);
      end = c_fully_fold (build_c_cast (loc, type, end), അസത്യം, ശൂന്യ);
      orig_step = save_വ്യഞ്ജകം (c_fully_fold (step, അസത്യം, ശൂന്യ));
      വൃക്ഷം stype = POINTER_TYPE_P (type) ? sizetype : type;
      step = c_fully_fold (build_c_cast (loc, stype, orig_step), അസത്യം, ശൂന്യ);
      എങ്കിൽ (POINTER_TYPE_P (type))
	{
	  begin = save_വ്യഞ്ജകം (begin);
	  step = pointer_int_sum (loc, PLUS_വ്യഞ്ജകം, begin, step);
	  step = fold_build2_loc (loc, MINUS_വ്യഞ്ജകം, sizetype,
				  fold_convert (sizetype, step),
				  fold_convert (sizetype, begin));
	  step = fold_convert (ssizetype, step);
	}
      എങ്കിൽ (integer_zerop (step))
	{
	  error_at (loc, "iterator %qD has zero step", var);
	  ret = സത്യം;
	  തുടരുക;
	}

      എങ്കിൽ (begin == error_mark_കണ്ണി
	  || end == error_mark_കണ്ണി
	  || step == error_mark_കണ്ണി
	  || orig_step == error_mark_കണ്ണി)
	{
	  ret = സത്യം;
	  തുടരുക;
	}
      hash_set<വൃക്ഷം> pset;
      വൃക്ഷം it2;
      വേണ്ടി (it2 = വൃക്ഷം_CHAIN (it); it2; it2 = വൃക്ഷം_CHAIN (it2))
	{
	  വൃക്ഷം var2 = OMP_ITERATOR_VAR (it2);
	  വൃക്ഷം begin2 = OMP_ITERATOR_BEGIN (it2);
	  വൃക്ഷം end2 = OMP_ITERATOR_END (it2);
	  വൃക്ഷം step2 = OMP_ITERATOR_STEP (it2);
	  വൃക്ഷം type2 = വൃക്ഷം_TYPE (var2);
	  location_t loc2 = DECL_SOURCE_LOCATION (var2);
	  ഘടന c_find_omp_var_s data = { var, &pset };
	  എങ്കിൽ (walk_വൃക്ഷം (&type2, c_find_omp_var_r, &data, &pset))
	    {
	      error_at (loc2,
			"type of iterator %qD refers to outer iterator %qD",
			var2, var);
	      നിർത്തുക;
	    }
	  അല്ലെങ്കിൽ എങ്കിൽ (walk_വൃക്ഷം (&begin2, c_find_omp_var_r, &data, &pset))
	    {
	      error_at (വ്യഞ്ജകം_LOC_OR_LOC (begin2, loc2),
			"begin expression refers to outer iterator %qD", var);
	      നിർത്തുക;
	    }
	  അല്ലെങ്കിൽ എങ്കിൽ (walk_വൃക്ഷം (&end2, c_find_omp_var_r, &data, &pset))
	    {
	      error_at (വ്യഞ്ജകം_LOC_OR_LOC (end2, loc2),
			"end expression refers to outer iterator %qD", var);
	      നിർത്തുക;
	    }
	  അല്ലെങ്കിൽ എങ്കിൽ (walk_വൃക്ഷം (&step2, c_find_omp_var_r, &data, &pset))
	    {
	      error_at (വ്യഞ്ജകം_LOC_OR_LOC (step2, loc2),
			"step expression refers to outer iterator %qD", var);
	      നിർത്തുക;
	    }
	}
      എങ്കിൽ (it2)
	{
	  ret = സത്യം;
	  തുടരുക;
	}
      OMP_ITERATOR_BEGIN (it) = begin;
      OMP_ITERATOR_END (it) = end;
      OMP_ITERATOR_STEP (it) = step;
      OMP_ITERATOR_ORIG_STEP (it) = orig_step;
    }
  തിരികെ ret;
}

/* Ensure that pointers are used in OpenACC attach and detach clauses.
   Return true if an error has been detected.  */

സ്ഥിതം തർക്കം
c_oacc_check_attachments (വൃക്ഷം c)
{
  എങ്കിൽ (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_MAP)
    തിരികെ അസത്യം;

  /* OpenACC attach / detach clauses must be pointers.  */
  എങ്കിൽ (OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_ATTACH
      || OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_DETACH)
    {
      വൃക്ഷം t = OMP_CLAUSE_DECL (c);

      ആകുമ്പോൾ (വൃക്ഷം_CODE (t) == OMP_ARRAY_SECTION)
	t = വൃക്ഷം_OPERAND (t, 0);

      എങ്കിൽ (വൃക്ഷം_CODE (വൃക്ഷം_TYPE (t)) != POINTER_TYPE)
	{
	  error_at (OMP_CLAUSE_LOCATION (c), "expected pointer in %qs clause",
		    user_omp_clause_code_name (c, സത്യം));
	  തിരികെ സത്യം;
	}
    }

  തിരികെ അസത്യം;
}

/* For all elements of CLAUSES, validate them against their constraints.
   Remove any elements from the list that are invalid.  */

വൃക്ഷം
c_finish_omp_clauses (വൃക്ഷം clauses, എണ്ണൽ c_omp_region_type ort)
{
  bitmap_head generic_head, firstprivate_head, lastprivate_head;
  bitmap_head aligned_head, map_head, map_field_head, map_firstprivate_head;
  bitmap_head oacc_reduction_head, is_on_device_head;
  വൃക്ഷം c, t, type, *pc;
  വൃക്ഷം simdlen = NULL_വൃക്ഷം, safelen = NULL_വൃക്ഷം;
  തർക്കം branch_seen = അസത്യം;
  തർക്കം copyprivate_seen = അസത്യം;
  തർക്കം mergeable_seen = അസത്യം;
  വൃക്ഷം *detach_seen = ശൂന്യ;
  തർക്കം linear_variable_step_check = അസത്യം;
  വൃക്ഷം *nowait_clause = ശൂന്യ;
  വൃക്ഷം *grainsize_seen = ശൂന്യ;
  തർക്കം അക്കം_tasks_seen = അസത്യം;
  വൃക്ഷം ordered_clause = NULL_വൃക്ഷം;
  വൃക്ഷം schedule_clause = NULL_വൃക്ഷം;
  തർക്കം oacc_async = അസത്യം;
  വൃക്ഷം last_iterators = NULL_വൃക്ഷം;
  തർക്കം last_iterators_remove = അസത്യം;
  വൃക്ഷം *nogroup_seen = ശൂന്യ;
  വൃക്ഷം *order_clause = ശൂന്യ;
  /* 1 if normal/task reduction has been seen, -1 if inscan reduction
     has been seen, -2 if mixed inscan/normal reduction diagnosed.  */
  പൂർണ്ണസംഖ്യ reduction_seen = 0;
  തർക്കം allocate_seen = അസത്യം;
  തർക്കം implicit_moved = അസത്യം;
  തർക്കം target_in_reduction_seen = അസത്യം;
  വൃക്ഷം *full_seen = ശൂന്യ;
  തർക്കം partial_seen = അസത്യം;
  തർക്കം openacc = (ort & C_ORT_ACC) != 0;
  തർക്കം init_seen = അസത്യം;
  തർക്കം init_use_destroy_seen = അസത്യം;
  വൃക്ഷം init_no_targetsync_clause = NULL_വൃക്ഷം;
  വൃക്ഷം depend_clause = NULL_വൃക്ഷം;

  എങ്കിൽ (!openacc)
    clauses = omp_remove_duplicate_maps (clauses, സത്യം);

  bitmap_obstack_initialize (ശൂന്യ);
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

  എങ്കിൽ (openacc)
    വേണ്ടി (c = clauses; c; c = OMP_CLAUSE_CHAIN (c))
      എങ്കിൽ (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_ASYNC)
	{
	  oacc_async = സത്യം;
	  നിർത്തുക;
	}

  വൃക്ഷം *grp_start_p = ശൂന്യ, grp_sentinel = NULL_വൃക്ഷം;

  വേണ്ടി (pc = &clauses, c = clauses; c ; c = *pc)
    {
      തർക്കം remove = അസത്യം;
      തർക്കം need_complete = അസത്യം;
      തർക്കം need_implicitly_determined = അസത്യം;

      /* We've reached the end of a list of expanded nodes.  Reset the group
	 start pointer.  */
      എങ്കിൽ (c == grp_sentinel)
	{
	  എങ്കിൽ (grp_start_p
	      && OMP_CLAUSE_HAS_ITERATORS (*grp_start_p))
	    വേണ്ടി (വൃക്ഷം gc = *grp_start_p; gc != grp_sentinel;
		 gc = OMP_CLAUSE_CHAIN (gc))
	      OMP_CLAUSE_ITERATORS (gc) = OMP_CLAUSE_ITERATORS (*grp_start_p);
	  grp_start_p = ശൂന്യ;
	}

      തിരഞ്ഞെടുപ്പ് (OMP_CLAUSE_CODE (c))
	{
	അവസ്ഥ OMP_CLAUSE_SHARED:
	  need_implicitly_determined = സത്യം;
	  പോകുക check_dup_generic;

	അവസ്ഥ OMP_CLAUSE_PRIVATE:
	  need_complete = സത്യം;
	  need_implicitly_determined = സത്യം;
	  പോകുക check_dup_generic;

	അവസ്ഥ OMP_CLAUSE_REDUCTION:
	  എങ്കിൽ (reduction_seen == 0)
	    reduction_seen = OMP_CLAUSE_REDUCTION_INSCAN (c) ? -1 : 1;
	  അല്ലെങ്കിൽ എങ്കിൽ (reduction_seen != -2
		   && reduction_seen != (OMP_CLAUSE_REDUCTION_INSCAN (c)
					 ? -1 : 1))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<inscan%> and non-%<inscan%> %<reduction%> clauses "
			"on the same construct");
	      reduction_seen = -2;
	    }
	  /* FALLTHRU */
	അവസ്ഥ OMP_CLAUSE_IN_REDUCTION:
	അവസ്ഥ OMP_CLAUSE_TASK_REDUCTION:
	  need_implicitly_determined = സത്യം;
	  t = OMP_CLAUSE_DECL (c);
	  എങ്കിൽ (വൃക്ഷം_CODE (t) == OMP_ARRAY_SECTION)
	    {
	      എങ്കിൽ (handle_omp_array_sections (c, ort))
		{
		  remove = സത്യം;
		  നിർത്തുക;
		}

	      t = OMP_CLAUSE_DECL (c);
	      എങ്കിൽ (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_REDUCTION
		  && OMP_CLAUSE_REDUCTION_INSCAN (c))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%<inscan%> %<reduction%> clause with array "
			    "section");
		  remove = സത്യം;
		  നിർത്തുക;
		}
	    }
	  t = require_complete_type (OMP_CLAUSE_LOCATION (c), t);
	  എങ്കിൽ (t == error_mark_കണ്ണി)
	    {
	      remove = സത്യം;
	      നിർത്തുക;
	    }
	  എങ്കിൽ (oacc_async)
	    c_mark_addressable (t);
	  type = വൃക്ഷം_TYPE (t);
	  എങ്കിൽ (വൃക്ഷം_CODE (t) == MEM_REF)
	    type = വൃക്ഷം_TYPE (type);
	  എങ്കിൽ (വൃക്ഷം_CODE (type) == ARRAY_TYPE)
	    {
	      വൃക്ഷം oatype = type;
	      gcc_assert (വൃക്ഷം_CODE (t) != MEM_REF);
	      ആകുമ്പോൾ (വൃക്ഷം_CODE (type) == ARRAY_TYPE)
		type = വൃക്ഷം_TYPE (type);
	      എങ്കിൽ (integer_zerop (TYPE_SIZE_UNIT (type)))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD in %<reduction%> clause is a zero size array",
			    t);
		  remove = സത്യം;
		  നിർത്തുക;
		}
	      വൃക്ഷം size = size_binop (EXACT_DIV_വ്യഞ്ജകം, TYPE_SIZE_UNIT (oatype),
				      TYPE_SIZE_UNIT (type));
	      എങ്കിൽ (integer_zerop (size))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD in %<reduction%> clause is a zero size array",
			    t);
		  remove = സത്യം;
		  നിർത്തുക;
		}
	      size = size_binop (MINUS_വ്യഞ്ജകം, size, size_one_കണ്ണി);
	      size = save_വ്യഞ്ജകം (size);
	      വൃക്ഷം index_type = build_index_type (size);
	      വൃക്ഷം atype = c_build_array_type (TYPE_MAIN_VARIANT (type),
					       index_type);
	      atype = c_build_qualified_type (atype, TYPE_QUALS (type));
	      വൃക്ഷം ptype = c_build_pointer_type (type);
	      എങ്കിൽ (വൃക്ഷം_CODE (വൃക്ഷം_TYPE (t)) == ARRAY_TYPE)
		t = build_fold_addr_വ്യഞ്ജകം (t);
	      t = build2 (MEM_REF, atype, t, build_int_cst (ptype, 0));
	      OMP_CLAUSE_DECL (c) = t;
	    }
	  എങ്കിൽ (TYPE_ATOMIC (type))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<_Atomic%> %qE in %<reduction%> clause", t);
	      remove = സത്യം;
	      നിർത്തുക;
	    }
	  എങ്കിൽ (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_REDUCTION
	      || OMP_CLAUSE_REDUCTION_TASK (c))
	    {
	      /* Disallow zero sized or potentially zero sized task
		 reductions.  */
	      എങ്കിൽ (integer_zerop (TYPE_SIZE_UNIT (type)))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "zero sized type %qT in %qs clause", type,
			    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		  remove = സത്യം;
		  നിർത്തുക;
		}
	      അല്ലെങ്കിൽ എങ്കിൽ (വൃക്ഷം_CODE (TYPE_SIZE_UNIT (type)) != INTEGER_CST)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "variable sized type %qT in %qs clause", type,
			    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		  remove = സത്യം;
		  നിർത്തുക;
		}
	    }
	  എങ്കിൽ (OMP_CLAUSE_REDUCTION_PLACEHOLDER (c) == NULL_വൃക്ഷം
	      && (FLOAT_TYPE_P (type)
		  || വൃക്ഷം_CODE (type) == COMPLEX_TYPE))
	    {
	      എണ്ണൽ വൃക്ഷം_code r_code = OMP_CLAUSE_REDUCTION_CODE (c);
	      സ്ഥിരം അക്ഷരം *r_name = ശൂന്യ;

	      തിരഞ്ഞെടുപ്പ് (r_code)
		{
		അവസ്ഥ PLUS_വ്യഞ്ജകം:
		അവസ്ഥ MULT_വ്യഞ്ജകം:
		അവസ്ഥ MINUS_വ്യഞ്ജകം:
		അവസ്ഥ TRUTH_ANDIF_വ്യഞ്ജകം:
		അവസ്ഥ TRUTH_ORIF_വ്യഞ്ജകം:
		  നിർത്തുക;
		അവസ്ഥ MIN_വ്യഞ്ജകം:
		  എങ്കിൽ (വൃക്ഷം_CODE (type) == COMPLEX_TYPE)
		    r_name = "min";
		  നിർത്തുക;
		അവസ്ഥ MAX_വ്യഞ്ജകം:
		  എങ്കിൽ (വൃക്ഷം_CODE (type) == COMPLEX_TYPE)
		    r_name = "max";
		  നിർത്തുക;
		അവസ്ഥ BIT_AND_വ്യഞ്ജകം:
		  r_name = "&";
		  നിർത്തുക;
		അവസ്ഥ BIT_XOR_വ്യഞ്ജകം:
		  r_name = "^";
		  നിർത്തുക;
		അവസ്ഥ BIT_IOR_വ്യഞ്ജകം:
		  r_name = "|";
		  നിർത്തുക;
		സ്ഥിരസ്ഥിതി:
		  gcc_unreachable ();
		}
	      എങ്കിൽ (r_name)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qE has invalid type for %<reduction(%s)%>",
			    t, r_name);
		  remove = സത്യം;
		  നിർത്തുക;
		}
	    }
	  അല്ലെങ്കിൽ എങ്കിൽ (OMP_CLAUSE_REDUCTION_PLACEHOLDER (c) == error_mark_കണ്ണി)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"user defined reduction not found for %qE", t);
	      remove = സത്യം;
	      നിർത്തുക;
	    }
	  അല്ലെങ്കിൽ എങ്കിൽ (OMP_CLAUSE_REDUCTION_PLACEHOLDER (c))
	    {
	      വൃക്ഷം list = OMP_CLAUSE_REDUCTION_PLACEHOLDER (c);
	      type = TYPE_MAIN_VARIANT (type);
	      വൃക്ഷം placeholder = build_decl (OMP_CLAUSE_LOCATION (c),
					     VAR_DECL, NULL_വൃക്ഷം, type);
	      വൃക്ഷം decl_placeholder = NULL_വൃക്ഷം;
	      OMP_CLAUSE_REDUCTION_PLACEHOLDER (c) = placeholder;
	      DECL_ARTIFICIAL (placeholder) = 1;
	      DECL_IGNORED_P (placeholder) = 1;
	      എങ്കിൽ (വൃക്ഷം_CODE (t) == MEM_REF)
		{
		  decl_placeholder = build_decl (OMP_CLAUSE_LOCATION (c),
						 VAR_DECL, NULL_വൃക്ഷം, type);
		  OMP_CLAUSE_REDUCTION_DECL_PLACEHOLDER (c) = decl_placeholder;
		  DECL_ARTIFICIAL (decl_placeholder) = 1;
		  DECL_IGNORED_P (decl_placeholder) = 1;
		}
	      എങ്കിൽ (വൃക്ഷം_ADDRESSABLE (വൃക്ഷം_VEC_ELT (list, 0)))
		c_mark_addressable (placeholder);
	      എങ്കിൽ (വൃക്ഷം_ADDRESSABLE (വൃക്ഷം_VEC_ELT (list, 1)))
		c_mark_addressable (decl_placeholder ? decl_placeholder
				    : OMP_CLAUSE_DECL (c));
	      OMP_CLAUSE_REDUCTION_MERGE (c)
		= c_clone_omp_udr (വൃക്ഷം_VEC_ELT (list, 2),
				   വൃക്ഷം_VEC_ELT (list, 0),
				   വൃക്ഷം_VEC_ELT (list, 1),
				   decl_placeholder ? decl_placeholder
				   : OMP_CLAUSE_DECL (c), placeholder);
	      OMP_CLAUSE_REDUCTION_MERGE (c)
		= build3_loc (OMP_CLAUSE_LOCATION (c), BIND_വ്യഞ്ജകം,
			      void_type_കണ്ണി, NULL_വൃക്ഷം,
			      OMP_CLAUSE_REDUCTION_MERGE (c), NULL_വൃക്ഷം);
	      വൃക്ഷം_SIDE_EFFECTS (OMP_CLAUSE_REDUCTION_MERGE (c)) = 1;
	      എങ്കിൽ (വൃക്ഷം_VEC_LENGTH (list) == 6)
		{
		  എങ്കിൽ (വൃക്ഷം_ADDRESSABLE (വൃക്ഷം_VEC_ELT (list, 3)))
		    c_mark_addressable (decl_placeholder ? decl_placeholder
					: OMP_CLAUSE_DECL (c));
		  എങ്കിൽ (വൃക്ഷം_ADDRESSABLE (വൃക്ഷം_VEC_ELT (list, 4)))
		    c_mark_addressable (placeholder);
		  വൃക്ഷം init = വൃക്ഷം_VEC_ELT (list, 5);
		  എങ്കിൽ (init == error_mark_കണ്ണി)
		    init = DECL_INITIAL (വൃക്ഷം_VEC_ELT (list, 3));
		  OMP_CLAUSE_REDUCTION_INIT (c)
		    = c_clone_omp_udr (init, വൃക്ഷം_VEC_ELT (list, 4),
				       വൃക്ഷം_VEC_ELT (list, 3),
				       decl_placeholder ? decl_placeholder
				       : OMP_CLAUSE_DECL (c), placeholder);
		  എങ്കിൽ (വൃക്ഷം_VEC_ELT (list, 5) == error_mark_കണ്ണി)
		    {
		      വൃക്ഷം v = decl_placeholder ? decl_placeholder : t;
		      OMP_CLAUSE_REDUCTION_INIT (c)
			= build2 (INIT_വ്യഞ്ജകം, വൃക്ഷം_TYPE (v), v,
				  OMP_CLAUSE_REDUCTION_INIT (c));
		    }
		  എങ്കിൽ (walk_വൃക്ഷം (&OMP_CLAUSE_REDUCTION_INIT (c),
				 c_find_omp_placeholder_r,
				 placeholder, ശൂന്യ))
		    OMP_CLAUSE_REDUCTION_OMP_ORIG_REF (c) = 1;
		}
	      അല്ലെങ്കിൽ
		{
		  വൃക്ഷം init;
		  വൃക്ഷം v = decl_placeholder ? decl_placeholder : t;
		  എങ്കിൽ (AGGREGATE_TYPE_P (വൃക്ഷം_TYPE (v)))
		    init = build_constructor (വൃക്ഷം_TYPE (v), ശൂന്യ);
		  അല്ലെങ്കിൽ
		    init = fold_convert (വൃക്ഷം_TYPE (v), integer_zero_കണ്ണി);
		  OMP_CLAUSE_REDUCTION_INIT (c)
		    = build2 (INIT_വ്യഞ്ജകം, വൃക്ഷം_TYPE (v), v, init);
		}
	      OMP_CLAUSE_REDUCTION_INIT (c)
		= build3_loc (OMP_CLAUSE_LOCATION (c), BIND_വ്യഞ്ജകം,
			      void_type_കണ്ണി, NULL_വൃക്ഷം,
			       OMP_CLAUSE_REDUCTION_INIT (c), NULL_വൃക്ഷം);
	      വൃക്ഷം_SIDE_EFFECTS (OMP_CLAUSE_REDUCTION_INIT (c)) = 1;
	    }
	  എങ്കിൽ (വൃക്ഷം_CODE (t) == MEM_REF)
	    {
	      എങ്കിൽ (TYPE_SIZE_UNIT (വൃക്ഷം_TYPE (വൃക്ഷം_TYPE (t))) == NULL_വൃക്ഷം
		  || വൃക്ഷം_CODE (TYPE_SIZE_UNIT (വൃക്ഷം_TYPE (വൃക്ഷം_TYPE (t))))
		     != INTEGER_CST)
		{
		  sorry ("variable length element type in array "
			 "%<reduction%> clause");
		  remove = സത്യം;
		  നിർത്തുക;
		}
	      t = വൃക്ഷം_OPERAND (t, 0);
	      എങ്കിൽ (വൃക്ഷം_CODE (t) == POINTER_PLUS_വ്യഞ്ജകം)
		t = വൃക്ഷം_OPERAND (t, 0);
	      എങ്കിൽ (വൃക്ഷം_CODE (t) == ADDR_വ്യഞ്ജകം)
		t = വൃക്ഷം_OPERAND (t, 0);
	    }
	  പോകുക check_dup_generic_t;

	അവസ്ഥ OMP_CLAUSE_COPYPRIVATE:
	  copyprivate_seen = സത്യം;
	  എങ്കിൽ (nowait_clause)
	    {
	      error_at (OMP_CLAUSE_LOCATION (*nowait_clause),
			"%<nowait%> clause must not be used together "
			"with %<copyprivate%> clause");
	      *nowait_clause = OMP_CLAUSE_CHAIN (*nowait_clause);
	      nowait_clause = ശൂന്യ;
	    }
	  പോകുക check_dup_generic;

	അവസ്ഥ OMP_CLAUSE_COPYIN:
	  t = OMP_CLAUSE_DECL (c);
	  എങ്കിൽ (!VAR_P (t) || !DECL_THREAD_LOCAL_P (t))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE must be %<threadprivate%> for %<copyin%>", t);
	      remove = സത്യം;
	      നിർത്തുക;
	    }
	  പോകുക check_dup_generic;

	അവസ്ഥ OMP_CLAUSE_LINEAR:
	  എങ്കിൽ (ort != C_ORT_OMP_DECLARE_SIMD)
	    need_implicitly_determined = സത്യം;
	  t = OMP_CLAUSE_DECL (c);
	  എങ്കിൽ (ort != C_ORT_OMP_DECLARE_SIMD
	      && OMP_CLAUSE_LINEAR_KIND (c) != OMP_CLAUSE_LINEAR_DEFAULT
	      && OMP_CLAUSE_LINEAR_OLD_LINEAR_MODIFIER (c))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"modifier should not be specified in %<linear%> "
			"clause on %<simd%> or %<for%> constructs when not "
			"using OpenMP 5.2 modifiers");
	      OMP_CLAUSE_LINEAR_KIND (c) = OMP_CLAUSE_LINEAR_DEFAULT;
	    }
	  എങ്കിൽ (!INTEGRAL_TYPE_P (വൃക്ഷം_TYPE (t))
	      && വൃക്ഷം_CODE (വൃക്ഷം_TYPE (t)) != POINTER_TYPE)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"linear clause applied to non-integral non-pointer "
			"variable with type %qT", വൃക്ഷം_TYPE (t));
	      remove = സത്യം;
	      നിർത്തുക;
	    }
	  എങ്കിൽ (TYPE_ATOMIC (വൃക്ഷം_TYPE (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<_Atomic%> %qD in %<linear%> clause", t);
	      remove = സത്യം;
	      നിർത്തുക;
	    }
	  എങ്കിൽ (ort == C_ORT_OMP_DECLARE_SIMD)
	    {
	      വൃക്ഷം s = OMP_CLAUSE_LINEAR_STEP (c);
	      എങ്കിൽ (വൃക്ഷം_CODE (s) == PARM_DECL)
		{
		  OMP_CLAUSE_LINEAR_VARIABLE_STRIDE (c) = 1;
		  /* map_head bitmap is used as uniform_head if
		     declare_simd.  */
		  എങ്കിൽ (!bitmap_bit_p (&map_head, DECL_UID (s)))
		    linear_variable_step_check = സത്യം;
		  പോകുക check_dup_generic;
		}
	      എങ്കിൽ (വൃക്ഷം_CODE (s) != INTEGER_CST)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%<linear%> clause step %qE is neither constant "
			    "nor a parameter", s);
		  remove = സത്യം;
		  നിർത്തുക;
		}
	    }
	  എങ്കിൽ (വൃക്ഷം_CODE (വൃക്ഷം_TYPE (OMP_CLAUSE_DECL (c))) == POINTER_TYPE)
	    {
	      വൃക്ഷം s = OMP_CLAUSE_LINEAR_STEP (c);
	      s = pointer_int_sum (OMP_CLAUSE_LOCATION (c), PLUS_വ്യഞ്ജകം,
				   OMP_CLAUSE_DECL (c), s);
	      s = fold_build2_loc (OMP_CLAUSE_LOCATION (c), MINUS_വ്യഞ്ജകം,
				   sizetype, fold_convert (sizetype, s),
				   fold_convert
				     (sizetype, OMP_CLAUSE_DECL (c)));
	      എങ്കിൽ (s == error_mark_കണ്ണി)
		s = size_one_കണ്ണി;
	      OMP_CLAUSE_LINEAR_STEP (c) = s;
	    }
	  അല്ലെങ്കിൽ
	    OMP_CLAUSE_LINEAR_STEP (c)
	      = fold_convert (വൃക്ഷം_TYPE (t), OMP_CLAUSE_LINEAR_STEP (c));
	  പോകുക check_dup_generic;

	check_dup_generic:
	  t = OMP_CLAUSE_DECL (c);
	check_dup_generic_t:
	  എങ്കിൽ (!VAR_P (t) && വൃക്ഷം_CODE (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in clause %qs", t,
			omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	      remove = സത്യം;
	    }
	  അല്ലെങ്കിൽ എങ്കിൽ ((openacc && OMP_CLAUSE_CODE (c) == OMP_CLAUSE_REDUCTION)
		   || (ort == C_ORT_OMP
		       && (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_USE_DEVICE_PTR
			   || (OMP_CLAUSE_CODE (c)
			       == OMP_CLAUSE_USE_DEVICE_ADDR)))
		   || (ort == C_ORT_OMP_TARGET
		       && OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IN_REDUCTION))
	    {
	      എങ്കിൽ (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IN_REDUCTION
		  && (bitmap_bit_p (&generic_head, DECL_UID (t))
		      || bitmap_bit_p (&firstprivate_head, DECL_UID (t))))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD appears more than once in data-sharing "
			    "clauses", t);
		  remove = സത്യം;
		  നിർത്തുക;
		}
	      എങ്കിൽ (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IN_REDUCTION)
		target_in_reduction_seen = സത്യം;
	      എങ്കിൽ (bitmap_bit_p (&oacc_reduction_head, DECL_UID (t)))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    openacc
			    ? "%qD appears more than once in reduction clauses"
			    : "%qD appears more than once in data clauses",
			    t);
		  remove = സത്യം;
		}
	      അല്ലെങ്കിൽ
		bitmap_set_bit (&oacc_reduction_head, DECL_UID (t));
	    }
	  അല്ലെങ്കിൽ എങ്കിൽ (bitmap_bit_p (&generic_head, DECL_UID (t))
		   || bitmap_bit_p (&firstprivate_head, DECL_UID (t))
		   || bitmap_bit_p (&lastprivate_head, DECL_UID (t))
		   || bitmap_bit_p (&map_firstprivate_head, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE appears more than once in data clauses", t);
	      remove = സത്യം;
	    }
	  അല്ലെങ്കിൽ എങ്കിൽ ((OMP_CLAUSE_CODE (c) == OMP_CLAUSE_PRIVATE
		    || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_HAS_DEVICE_ADDR
		    || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IS_DEVICE_PTR)
		   && bitmap_bit_p (&map_head, DECL_UID (t)))
	    {
	      എങ്കിൽ (openacc)
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD appears more than once in data clauses", t);
	      അല്ലെങ്കിൽ
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD appears both in data and map clauses", t);
	      remove = സത്യം;
	    }
	  അല്ലെങ്കിൽ
	    bitmap_set_bit (&generic_head, DECL_UID (t));
	  നിർത്തുക;

	അവസ്ഥ OMP_CLAUSE_FIRSTPRIVATE:
	  എങ്കിൽ (OMP_CLAUSE_FIRSTPRIVATE_IMPLICIT (c) && !implicit_moved)
	    {
	    move_implicit:
	      implicit_moved = സത്യം;
	      /* Move firstprivate and map clauses with
		 OMP_CLAUSE_{FIRSTPRIVATE,MAP}_IMPLICIT set to the end of
		 clauses chain.  */
	      വൃക്ഷം cl1 = NULL_വൃക്ഷം, cl2 = NULL_വൃക്ഷം;
	      വൃക്ഷം *pc1 = pc, *pc2 = &cl1, *pc3 = &cl2;
	      ആകുമ്പോൾ (*pc1)
		എങ്കിൽ (OMP_CLAUSE_CODE (*pc1) == OMP_CLAUSE_FIRSTPRIVATE
		    && OMP_CLAUSE_FIRSTPRIVATE_IMPLICIT (*pc1))
		  {
		    *pc3 = *pc1;
		    pc3 = &OMP_CLAUSE_CHAIN (*pc3);
		    *pc1 = OMP_CLAUSE_CHAIN (*pc1);
		  }
		അല്ലെങ്കിൽ എങ്കിൽ (OMP_CLAUSE_CODE (*pc1) == OMP_CLAUSE_MAP
			 && OMP_CLAUSE_MAP_IMPLICIT (*pc1))
		  {
		    *pc2 = *pc1;
		    pc2 = &OMP_CLAUSE_CHAIN (*pc2);
		    *pc1 = OMP_CLAUSE_CHAIN (*pc1);
		  }
		അല്ലെങ്കിൽ
		  pc1 = &OMP_CLAUSE_CHAIN (*pc1);
	      *pc3 = ശൂന്യ;
	      *pc2 = cl2;
	      *pc1 = cl1;
	      തുടരുക;
	    }
	  t = OMP_CLAUSE_DECL (c);
	  need_complete = സത്യം;
	  need_implicitly_determined = സത്യം;
	  എങ്കിൽ (!VAR_P (t) && വൃക്ഷം_CODE (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in clause %<firstprivate%>", t);
	      remove = സത്യം;
	    }
	  അല്ലെങ്കിൽ എങ്കിൽ (OMP_CLAUSE_FIRSTPRIVATE_IMPLICIT (c)
		   && !OMP_CLAUSE_FIRSTPRIVATE_IMPLICIT_TARGET (c)
		   && bitmap_bit_p (&map_firstprivate_head, DECL_UID (t)))
	    remove = സത്യം;
	  അല്ലെങ്കിൽ എങ്കിൽ (bitmap_bit_p (&generic_head, DECL_UID (t))
		   || bitmap_bit_p (&firstprivate_head, DECL_UID (t))
		   || bitmap_bit_p (&map_firstprivate_head, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE appears more than once in data clauses", t);
	      remove = സത്യം;
	    }
	  അല്ലെങ്കിൽ എങ്കിൽ (bitmap_bit_p (&map_head, DECL_UID (t))
		   || bitmap_bit_p (&map_field_head, DECL_UID (t)))
	    {
	      എങ്കിൽ (openacc)
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD appears more than once in data clauses", t);
	      അല്ലെങ്കിൽ എങ്കിൽ (OMP_CLAUSE_FIRSTPRIVATE_IMPLICIT (c)
		       && !OMP_CLAUSE_FIRSTPRIVATE_IMPLICIT_TARGET (c))
		/* Silently drop the clause.  */;
	      അല്ലെങ്കിൽ
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD appears both in data and map clauses", t);
	      remove = സത്യം;
	    }
	  അല്ലെങ്കിൽ
	    bitmap_set_bit (&firstprivate_head, DECL_UID (t));
	  നിർത്തുക;

	അവസ്ഥ OMP_CLAUSE_LASTPRIVATE:
	  t = OMP_CLAUSE_DECL (c);
	  need_complete = സത്യം;
	  need_implicitly_determined = സത്യം;
	  എങ്കിൽ (!VAR_P (t) && വൃക്ഷം_CODE (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in clause %<lastprivate%>", t);
	      remove = സത്യം;
	    }
	  അല്ലെങ്കിൽ എങ്കിൽ (bitmap_bit_p (&generic_head, DECL_UID (t))
		   || bitmap_bit_p (&lastprivate_head, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
		     "%qE appears more than once in data clauses", t);
	      remove = സത്യം;
	    }
	  അല്ലെങ്കിൽ
	    bitmap_set_bit (&lastprivate_head, DECL_UID (t));
	  നിർത്തുക;

	അവസ്ഥ OMP_CLAUSE_ALIGNED:
	  t = OMP_CLAUSE_DECL (c);
	  എങ്കിൽ (!VAR_P (t) && വൃക്ഷം_CODE (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in %<aligned%> clause", t);
	      remove = സത്യം;
	    }
	  അല്ലെങ്കിൽ എങ്കിൽ (!POINTER_TYPE_P (വൃക്ഷം_TYPE (t))
		   && വൃക്ഷം_CODE (വൃക്ഷം_TYPE (t)) != ARRAY_TYPE)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE in %<aligned%> clause is neither a pointer nor "
			"an array", t);
	      remove = സത്യം;
	    }
	  അല്ലെങ്കിൽ എങ്കിൽ (TYPE_ATOMIC (വൃക്ഷം_TYPE (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<_Atomic%> %qD in %<aligned%> clause", t);
	      remove = സത്യം;
	      നിർത്തുക;
	    }
	  അല്ലെങ്കിൽ എങ്കിൽ (bitmap_bit_p (&aligned_head, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE appears more than once in %<aligned%> clauses",
			t);
	      remove = സത്യം;
	    }
	  അല്ലെങ്കിൽ
	    bitmap_set_bit (&aligned_head, DECL_UID (t));
	  നിർത്തുക;

	അവസ്ഥ OMP_CLAUSE_NONTEMPORAL:
	  t = OMP_CLAUSE_DECL (c);
	  എങ്കിൽ (!VAR_P (t) && വൃക്ഷം_CODE (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in %<nontemporal%> clause", t);
	      remove = സത്യം;
	    }
	  അല്ലെങ്കിൽ എങ്കിൽ (bitmap_bit_p (&oacc_reduction_head, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE appears more than once in %<nontemporal%> "
			"clauses", t);
	      remove = സത്യം;
	    }
	  അല്ലെങ്കിൽ
	    bitmap_set_bit (&oacc_reduction_head, DECL_UID (t));
	  നിർത്തുക;

	അവസ്ഥ OMP_CLAUSE_ALLOCATE:
	  t = OMP_CLAUSE_DECL (c);
	  എങ്കിൽ (!VAR_P (t) && വൃക്ഷം_CODE (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in %<allocate%> clause", t);
	      remove = സത്യം;
	    }
	  അല്ലെങ്കിൽ എങ്കിൽ (bitmap_bit_p (&aligned_head, DECL_UID (t)))
	    {
	      warning_at (OMP_CLAUSE_LOCATION (c), OPT_Wopenmp,
			  "%qE appears more than once in %<allocate%> clauses",
			  t);
	      remove = സത്യം;
	    }
	  അല്ലെങ്കിൽ
	    {
	      bitmap_set_bit (&aligned_head, DECL_UID (t));
	      എങ്കിൽ (!OMP_CLAUSE_ALLOCATE_COMBINED (c))
		allocate_seen = സത്യം;
	    }
	  നിർത്തുക;

	അവസ്ഥ OMP_CLAUSE_DOACROSS:
	  t = OMP_CLAUSE_DECL (c);
	  എങ്കിൽ (t == NULL_വൃക്ഷം)
	    നിർത്തുക;
	  എങ്കിൽ (OMP_CLAUSE_DOACROSS_KIND (c) == OMP_CLAUSE_DOACROSS_SINK)
	    {
	      gcc_assert (വൃക്ഷം_CODE (t) == വൃക്ഷം_LIST);
	      വേണ്ടി (; t; t = വൃക്ഷം_CHAIN (t))
		{
		  വൃക്ഷം decl = വൃക്ഷം_മൂല്യം (t);
		  എങ്കിൽ (വൃക്ഷം_CODE (വൃക്ഷം_TYPE (decl)) == POINTER_TYPE)
		    {
		      വൃക്ഷം offset = വൃക്ഷം_PURPOSE (t);
		      തർക്കം neg = wi::neg_p (wi::to_wide (offset));
		      offset = fold_unary (ABS_വ്യഞ്ജകം, വൃക്ഷം_TYPE (offset), offset);
		      വൃക്ഷം t2 = pointer_int_sum (OMP_CLAUSE_LOCATION (c),
						 neg ? MINUS_വ്യഞ്ജകം : PLUS_വ്യഞ്ജകം,
						 decl, offset);
		      t2 = fold_build2_loc (OMP_CLAUSE_LOCATION (c), MINUS_വ്യഞ്ജകം,
					    sizetype,
					    fold_convert (sizetype, t2),
					    fold_convert (sizetype, decl));
		      എങ്കിൽ (t2 == error_mark_കണ്ണി)
			{
			  remove = സത്യം;
			  നിർത്തുക;
			}
		      വൃക്ഷം_PURPOSE (t) = t2;
		    }
		}
	      നിർത്തുക;
	    }
	  gcc_unreachable ();

	അവസ്ഥ OMP_CLAUSE_USES_ALLOCATORS:
	  t = OMP_CLAUSE_USES_ALLOCATORS_ALLOCATOR (c);
	  എങ്കിൽ (t == error_mark_കണ്ണി)
	    {
	      remove = സത്യം;
	      നിർത്തുക;
	    }
	  എങ്കിൽ ((VAR_P (t) || വൃക്ഷം_CODE (t) == PARM_DECL)
	      && (bitmap_bit_p (&generic_head, DECL_UID (t))
		  || bitmap_bit_p (&map_head, DECL_UID (t))
		  || bitmap_bit_p (&firstprivate_head, DECL_UID (t))
		  || bitmap_bit_p (&lastprivate_head, DECL_UID (t))))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE appears more than once in data clauses", t);
	      remove = സത്യം;
	      നിർത്തുക;
	    }
	  അല്ലെങ്കിൽ
	    bitmap_set_bit (&generic_head, DECL_UID (t));
	  എങ്കിൽ (വൃക്ഷം_CODE (വൃക്ഷം_TYPE (t)) != ENUMERAL_TYPE
	      || strcmp (IDENTIFIER_POINTER (TYPE_IDENTIFIER (വൃക്ഷം_TYPE (t))),
			 "omp_allocator_handle_t") != 0)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"allocator %qE must be of %<omp_allocator_handle_t%> "
			"type", t);
	      remove = സത്യം;
	      നിർത്തുക;
	    }
	  വൃക്ഷം init;
	  എങ്കിൽ (!DECL_P (t)
	      || (വൃക്ഷം_CODE (t) == CONST_DECL
		  && ((init = DECL_INITIAL(t)) == nullptr
		      || വൃക്ഷം_CODE (init) != INTEGER_CST
		      || ((wi::to_widest (init) < 0
			   || wi::to_widest (init) > GOMP_OMP_PREDEF_ALLOC_MAX)
			  && (wi::to_widest (init) < GOMP_OMPX_PREDEF_ALLOC_MIN
			      || (wi::to_widest (init)
				  > GOMP_OMPX_PREDEF_ALLOC_MAX))))))
	    {
	      remove = സത്യം;
	      error_at (OMP_CLAUSE_LOCATION (c),
			"allocator %qE must be either a variable or a "
			"predefined allocator", t);
	      നിർത്തുക;
	    }
	  അല്ലെങ്കിൽ എങ്കിൽ (വൃക്ഷം_CODE (t) == CONST_DECL)
	    {
	      /* omp_null_allocator is ignored and for predefined allocators,
		 no special handling is required; thus, mark them removed. */
	      remove = സത്യം;

	      എങ്കിൽ (OMP_CLAUSE_USES_ALLOCATORS_MEMSPACE (c)
		  || OMP_CLAUSE_USES_ALLOCATORS_TRAITS (c))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "modifiers cannot be used with predefined "
			    "allocator %qE", t);
		  നിർത്തുക;
		}
	    }
	  t = OMP_CLAUSE_USES_ALLOCATORS_MEMSPACE (c);
	  എങ്കിൽ (t == error_mark_കണ്ണി)
	    {
	      remove = സത്യം;
	      നിർത്തുക;
	    }
	  എങ്കിൽ (t != NULL_വൃക്ഷം
	      && ((വൃക്ഷം_CODE (t) != CONST_DECL && വൃക്ഷം_CODE (t) != INTEGER_CST)
		  || വൃക്ഷം_CODE (വൃക്ഷം_TYPE (t)) != ENUMERAL_TYPE
		  || strcmp (IDENTIFIER_POINTER (TYPE_IDENTIFIER (വൃക്ഷം_TYPE (t))),
			     "omp_memspace_handle_t") != 0))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c), "memspace modifier %qE must be"
			" constant enum of %<omp_memspace_handle_t%> type", t);
	      remove = സത്യം;
	      നിർത്തുക;
	    }
	  t = OMP_CLAUSE_USES_ALLOCATORS_TRAITS (c);
	  എങ്കിൽ (t == error_mark_കണ്ണി)
	    {
	      remove = സത്യം;
	      നിർത്തുക;
	    }
	  എങ്കിൽ (t != NULL_വൃക്ഷം
	      && t != error_mark_കണ്ണി
	      && (DECL_EXTERNAL (t)
		  || വൃക്ഷം_CODE (t) == PARM_DECL))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c), "traits array %qE must be "
			"defined in same scope as the construct on which the "
			"clause appears", t);
	      remove = സത്യം;
	    }
	  എങ്കിൽ (t != NULL_വൃക്ഷം)
	    {
	      തർക്കം type_err = അസത്യം;

	      എങ്കിൽ (വൃക്ഷം_CODE (വൃക്ഷം_TYPE (t)) != ARRAY_TYPE
		  || DECL_SIZE (t) == NULL_വൃക്ഷം
		  || !COMPLETE_TYPE_P (വൃക്ഷം_TYPE (t)))
		type_err = സത്യം;
	      അല്ലെങ്കിൽ
		{
		  വൃക്ഷം elem_t = വൃക്ഷം_TYPE (വൃക്ഷം_TYPE (t));
		  എങ്കിൽ (വൃക്ഷം_CODE (elem_t) != RECORD_TYPE
		      || strcmp (IDENTIFIER_POINTER (TYPE_IDENTIFIER (elem_t)),
				 "omp_alloctrait_t") != 0
		      || !TYPE_READONLY (elem_t))
		    type_err = സത്യം;
		}
	      എങ്കിൽ (type_err)
		{
		  എങ്കിൽ (t != error_mark_കണ്ണി)
		    error_at (OMP_CLAUSE_LOCATION (c), "traits array %qE must "
			      "be of %<const omp_alloctrait_t []%> type", t);
		  അല്ലെങ്കിൽ
		    error_at (OMP_CLAUSE_LOCATION (c), "traits array must "
			      "be of %<const omp_alloctrait_t []%> type");
		  remove = സത്യം;
		}
	      അല്ലെങ്കിൽ
		{
		  വൃക്ഷം cst_val = decl_constant_മൂല്യം_1 (t, സത്യം);
		  എങ്കിൽ (cst_val == t)
		    {
		      error_at (OMP_CLAUSE_LOCATION (c), "traits array must be "
				"initialized with constants");

		      remove = സത്യം;
		    }
		}
	    }
	  എങ്കിൽ (remove)
	    നിർത്തുക;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  തുടരുക;
	അവസ്ഥ OMP_CLAUSE_DEPEND:
	  depend_clause = c;
	  /* FALLTHRU */
	അവസ്ഥ OMP_CLAUSE_AFFINITY:
	  t = OMP_CLAUSE_DECL (c);
	  എങ്കിൽ (OMP_ITERATOR_DECL_P (t))
	    {
	      എങ്കിൽ (വൃക്ഷം_PURPOSE (t) != last_iterators)
		last_iterators_remove
		  = c_omp_finish_iterators (വൃക്ഷം_PURPOSE (t));
	      last_iterators = വൃക്ഷം_PURPOSE (t);
	      t = വൃക്ഷം_മൂല്യം (t);
	      എങ്കിൽ (last_iterators_remove)
		t = error_mark_കണ്ണി;
	    }
	  അല്ലെങ്കിൽ
	    last_iterators = NULL_വൃക്ഷം;
	  എങ്കിൽ (വൃക്ഷം_CODE (t) == OMP_ARRAY_SECTION)
	    {
	      എങ്കിൽ (handle_omp_array_sections (c, ort))
		remove = സത്യം;
	      അല്ലെങ്കിൽ എങ്കിൽ (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND
		       && OMP_CLAUSE_DEPEND_KIND (c) == OMP_CLAUSE_DEPEND_DEPOBJ)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%<depend%> clause with %<depobj%> dependence "
			    "type on array section");
		  remove = സത്യം;
		}
	      നിർത്തുക;
	    }
	  എങ്കിൽ (t == error_mark_കണ്ണി)
	    remove = സത്യം;
	  അല്ലെങ്കിൽ എങ്കിൽ (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND
		   && t == ridpointers[RID_OMP_ALL_MEMORY])
	    {
	      എങ്കിൽ (OMP_CLAUSE_DEPEND_KIND (c) != OMP_CLAUSE_DEPEND_OUT
		  && OMP_CLAUSE_DEPEND_KIND (c) != OMP_CLAUSE_DEPEND_INOUT)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%<omp_all_memory%> used with %<depend%> kind "
			    "other than %<out%> or %<inout%>");
		  remove = സത്യം;
		}
	    }
	  അല്ലെങ്കിൽ എങ്കിൽ (!lvalue_p (t))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not lvalue expression nor array section in "
			"%qs clause", t,
			omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	      remove = സത്യം;
	    }
	  അല്ലെങ്കിൽ എങ്കിൽ (വൃക്ഷം_CODE (t) == COMPONENT_REF
		   && DECL_C_BIT_FIELD (വൃക്ഷം_OPERAND (t, 1)))
	    {
	      gcc_assert (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND
			  || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_AFFINITY);
	      error_at (OMP_CLAUSE_LOCATION (c),
			"bit-field %qE in %qs clause", t,
			omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	      remove = സത്യം;
	    }
	  അല്ലെങ്കിൽ എങ്കിൽ (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND
		   && OMP_CLAUSE_DEPEND_KIND (c) == OMP_CLAUSE_DEPEND_DEPOBJ)
	    {
	      എങ്കിൽ (!c_omp_depend_t_p (വൃക്ഷം_TYPE (t)))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qE does not have %<omp_depend_t%> type in "
			    "%<depend%> clause with %<depobj%> dependence "
			    "type", t);
		  remove = സത്യം;
		}
	    }
	  അല്ലെങ്കിൽ എങ്കിൽ (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND
		   && c_omp_depend_t_p (വൃക്ഷം_TYPE (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE should not have %<omp_depend_t%> type in "
			"%<depend%> clause with dependence type other than "
			"%<depobj%>", t);
	      remove = സത്യം;
	    }
	  എങ്കിൽ (!remove)
	    {
	      എങ്കിൽ (t == ridpointers[RID_OMP_ALL_MEMORY])
		t = null_pointer_കണ്ണി;
	      അല്ലെങ്കിൽ
		{
		  വൃക്ഷം addr = build_unary_op (OMP_CLAUSE_LOCATION (c),
					      ADDR_വ്യഞ്ജകം, t, അസത്യം);
		  എങ്കിൽ (addr == error_mark_കണ്ണി)
		    {
		      remove = സത്യം;
		      നിർത്തുക;
		    }
		  t = build_indirect_ref (OMP_CLAUSE_LOCATION (c), addr,
					  RO_UNARY_STAR);
		  എങ്കിൽ (t == error_mark_കണ്ണി)
		    {
		      remove = സത്യം;
		      നിർത്തുക;
		    }
		}
	      എങ്കിൽ (OMP_ITERATOR_DECL_P (OMP_CLAUSE_DECL (c)))
		വൃക്ഷം_മൂല്യം (OMP_CLAUSE_DECL (c)) = t;
	      അല്ലെങ്കിൽ
		OMP_CLAUSE_DECL (c) = t;
	    }
	  നിർത്തുക;

	അവസ്ഥ OMP_CLAUSE_MAP:
	  എങ്കിൽ (OMP_CLAUSE_MAP_IMPLICIT (c) && !implicit_moved)
	    പോകുക move_implicit;
	  എങ്കിൽ (OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_തള്ളുക_MAPPER_NAME
	      || OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_എടുക്കുക_MAPPER_NAME)
	    {
	      remove = സത്യം;
	      നിർത്തുക;
	    }
	  /* FALLTHRU */
	അവസ്ഥ OMP_CLAUSE_TO:
	അവസ്ഥ OMP_CLAUSE_FROM:
	  എങ്കിൽ (OMP_CLAUSE_ITERATORS (c)
	      && c_omp_finish_iterators (OMP_CLAUSE_ITERATORS (c)))
	    {
	      t = error_mark_കണ്ണി;
	      നിർത്തുക;
	    }
	  /* FALLTHRU */
	അവസ്ഥ OMP_CLAUSE__CACHE_:
	  {
	    using നാമാകാശ omp_addr_tokenizer;
	    auto_vec<omp_addr_token *, 10> addr_tokens;

	    t = OMP_CLAUSE_DECL (c);
	    എങ്കിൽ (വൃക്ഷം_CODE (t) == OMP_ARRAY_SECTION)
	      {
		grp_start_p = pc;
		grp_sentinel = OMP_CLAUSE_CHAIN (c);

		എങ്കിൽ (handle_omp_array_sections (c, ort))
		  remove = സത്യം;
		അല്ലെങ്കിൽ
		  {
		    t = OMP_CLAUSE_DECL (c);
		    എങ്കിൽ (!omp_mappable_type (വൃക്ഷം_TYPE (t)))
		      {
			error_at (OMP_CLAUSE_LOCATION (c),
				  "array section does not have mappable type "
				  "in %qs clause",
				  omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
			remove = സത്യം;
		      }
		    അല്ലെങ്കിൽ എങ്കിൽ (TYPE_ATOMIC (വൃക്ഷം_TYPE (t)))
		      {
			error_at (OMP_CLAUSE_LOCATION (c),
				  "%<_Atomic%> %qE in %qs clause", t,
				  omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
			remove = സത്യം;
		      }
		    ആകുമ്പോൾ (വൃക്ഷം_CODE (t) == ARRAY_REF)
		      t = വൃക്ഷം_OPERAND (t, 0);

		    c_omp_address_inspector ai (OMP_CLAUSE_LOCATION (c), t);

		    എങ്കിൽ (!omp_parse_വ്യഞ്ജകം (addr_tokens, t))
		      {
			sorry_at (OMP_CLAUSE_LOCATION (c),
				  "unsupported map expression %qE",
				  OMP_CLAUSE_DECL (c));
			remove = സത്യം;
			നിർത്തുക;
		      }

		    /* This check is to determine if this will be the only map
		       node created for this clause.  Otherwise, we'll check
		       the following FIRSTPRIVATE_POINTER or ATTACH_DETACH
		       node on the next iteration(s) of the loop.   */
		    എങ്കിൽ (addr_tokens.length () >= 4
			&& addr_tokens[0]->type == STRUCTURE_BASE
			&& addr_tokens[0]->u.structure_base_kind == BASE_DECL
			&& addr_tokens[1]->type == ACCESS_METHOD
			&& addr_tokens[2]->type == COMPONENT_SELECTOR
			&& addr_tokens[3]->type == ACCESS_METHOD
			&& (addr_tokens[3]->u.access_kind == ACCESS_DIRECT
			    || (addr_tokens[3]->u.access_kind
				== ACCESS_INDEXED_ARRAY)))
		      {
			വൃക്ഷം rt = addr_tokens[1]->വ്യഞ്ജകം;

			gcc_assert (DECL_P (rt));

			എങ്കിൽ (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP
			    && OMP_CLAUSE_MAP_IMPLICIT (c)
			    && (bitmap_bit_p (&map_head, DECL_UID (rt))
				|| bitmap_bit_p (&map_field_head, DECL_UID (rt))
				|| bitmap_bit_p (&map_firstprivate_head,
						 DECL_UID (rt))))
			  {
			    remove = സത്യം;
			    നിർത്തുക;
			  }
			എങ്കിൽ (bitmap_bit_p (&map_field_head, DECL_UID (rt)))
			  നിർത്തുക;
			എങ്കിൽ (bitmap_bit_p (&map_head, DECL_UID (rt)))
			  {
			    എങ്കിൽ (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_MAP)
			      error_at (OMP_CLAUSE_LOCATION (c),
					"%qD appears more than once in motion "
					"clauses", rt);
			    അല്ലെങ്കിൽ എങ്കിൽ (openacc)
			      error_at (OMP_CLAUSE_LOCATION (c),
					"%qD appears more than once in data "
					"clauses", rt);
			    അല്ലെങ്കിൽ
			      error_at (OMP_CLAUSE_LOCATION (c),
					"%qD appears more than once in map "
					"clauses", rt);
			    remove = സത്യം;
			  }
			അല്ലെങ്കിൽ
			  {
			    bitmap_set_bit (&map_head, DECL_UID (rt));
			    bitmap_set_bit (&map_field_head, DECL_UID (rt));
			  }
		      }
		  }
		എങ്കിൽ (c_oacc_check_attachments (c))
		  remove = സത്യം;
		എങ്കിൽ (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP
		    && (OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_ATTACH
			|| OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_DETACH)
		    && !OMP_CLAUSE_SIZE (c))
		  /* In this case, we have a single array element which is a
		     pointer, and we already set OMP_CLAUSE_SIZE in
		     handle_omp_array_sections above.  For attach/detach
		     clauses, reset the OMP_CLAUSE_SIZE (representing a bias)
		     to zero here.  */
		  OMP_CLAUSE_SIZE (c) = size_zero_കണ്ണി;
		നിർത്തുക;
	      }
	    അല്ലെങ്കിൽ എങ്കിൽ (!omp_parse_വ്യഞ്ജകം (addr_tokens, t))
	      {
		sorry_at (OMP_CLAUSE_LOCATION (c),
			  "unsupported map expression %qE",
			  OMP_CLAUSE_DECL (c));
		remove = സത്യം;
		നിർത്തുക;
	      }
	    എങ്കിൽ (t == error_mark_കണ്ണി)
	      {
		remove = സത്യം;
		നിർത്തുക;
	      }

	    വൃക്ഷം attr;
	    എങ്കിൽ (DECL_P (t)
		&& OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP
		&& (attr = lookup_attribute ("omp declare target",
					     DECL_ATTRIBUTES (t)))
		&& മൂല്യം_member (get_identifier ("local"),
				 വൃക്ഷം_മൂല്യം (attr)))
	      {
		error_at (OMP_CLAUSE_LOCATION (c),
			  "device-local variable %qD cannot appear "
			  "in map clause", t);
		remove = സത്യം;
		നിർത്തുക;
	      }

	    /* OpenACC attach / detach clauses must be pointers.  */
	    എങ്കിൽ (c_oacc_check_attachments (c))
	      {
		remove = സത്യം;
		നിർത്തുക;
	      }
	    എങ്കിൽ (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP
		&& (OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_ATTACH
		    || OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_DETACH)
		&& !OMP_CLAUSE_SIZE (c))
	      /* For attach/detach clauses, set OMP_CLAUSE_SIZE (representing a
		 bias) to zero here, so it is not set erroneously to the pointer
		 size later on in gimplify.cc.  */
	      OMP_CLAUSE_SIZE (c) = size_zero_കണ്ണി;

	    c_omp_address_inspector ai (OMP_CLAUSE_LOCATION (c), t);

	    എങ്കിൽ (!ai.check_clause (c))
	      {
		remove = സത്യം;
		നിർത്തുക;
	      }

	    എങ്കിൽ (!ai.map_supported_p ())
	      {
		sorry_at (OMP_CLAUSE_LOCATION (c),
			  "unsupported map expression %qE",
			  OMP_CLAUSE_DECL (c));
		remove = സത്യം;
		നിർത്തുക;
	      }

	    gcc_assert ((addr_tokens[0]->type == ARRAY_BASE
			 || addr_tokens[0]->type == STRUCTURE_BASE)
			&& addr_tokens[1]->type == ACCESS_METHOD);

	    t = addr_tokens[1]->വ്യഞ്ജകം;

	    എങ്കിൽ (addr_tokens[0]->u.structure_base_kind != BASE_DECL)
	      പോകുക skip_decl_checks;

	    /* For OpenMP, we can access a struct "t" and "t.d" on the same
	       mapping.  OpenACC allows multiple fields of the same structure
	       to be written.  */
	    എങ്കിൽ (addr_tokens[0]->type == STRUCTURE_BASE
		&& (bitmap_bit_p (&map_field_head, DECL_UID (t))
		    || (!openacc && bitmap_bit_p (&map_head, DECL_UID (t)))))
	      പോകുക skip_decl_checks;

	    എങ്കിൽ (!VAR_P (t) && വൃക്ഷം_CODE (t) != PARM_DECL)
	      {
		എങ്കിൽ (ort != C_ORT_ACC && വ്യഞ്ജകം_P (t))
		  നിർത്തുക;

		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qE is not a variable in %qs clause", t,
			  omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		remove = സത്യം;
	      }
	    അല്ലെങ്കിൽ എങ്കിൽ (VAR_P (t) && DECL_THREAD_LOCAL_P (t))
	      {
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD is threadprivate variable in %qs clause", t,
			  omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		remove = സത്യം;
	      }
	    അല്ലെങ്കിൽ എങ്കിൽ ((OMP_CLAUSE_CODE (c) != OMP_CLAUSE_MAP
		      || (OMP_CLAUSE_MAP_KIND (c)
			  != GOMP_MAP_FIRSTPRIVATE_POINTER))
		     && !c_mark_addressable (t))
	      remove = സത്യം;
	    അല്ലെങ്കിൽ എങ്കിൽ (!(OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP
		       && (OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_POINTER
			   || (OMP_CLAUSE_MAP_KIND (c)
			       == GOMP_MAP_FIRSTPRIVATE_POINTER)
			   || (OMP_CLAUSE_MAP_KIND (c)
			       == GOMP_MAP_FORCE_DEVICEPTR)))
		     && t == OMP_CLAUSE_DECL (c)
		     && !omp_mappable_type (വൃക്ഷം_TYPE (t)))
	      {
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD does not have a mappable type in %qs clause", t,
			  omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		remove = സത്യം;
	      }
	    അല്ലെങ്കിൽ എങ്കിൽ (വൃക്ഷം_TYPE (t) == error_mark_കണ്ണി)
	      remove = സത്യം;
	    അല്ലെങ്കിൽ എങ്കിൽ (TYPE_ATOMIC (strip_array_types (വൃക്ഷം_TYPE (t))))
	      {
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%<_Atomic%> %qE in %qs clause", t,
			  omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		remove = സത്യം;
	      }
	    അല്ലെങ്കിൽ എങ്കിൽ (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP
		     && OMP_CLAUSE_MAP_IMPLICIT (c)
		     && (bitmap_bit_p (&map_head, DECL_UID (t))
			 || bitmap_bit_p (&map_field_head, DECL_UID (t))
			 || bitmap_bit_p (&map_firstprivate_head,
					  DECL_UID (t))))
	      remove = സത്യം;
	    അല്ലെങ്കിൽ എങ്കിൽ (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP
		     && (OMP_CLAUSE_MAP_KIND (c)
			 == GOMP_MAP_FIRSTPRIVATE_POINTER))
	      {
		എങ്കിൽ (bitmap_bit_p (&generic_head, DECL_UID (t))
		    || bitmap_bit_p (&firstprivate_head, DECL_UID (t))
		    || bitmap_bit_p (&map_firstprivate_head, DECL_UID (t)))
		  {
		    error_at (OMP_CLAUSE_LOCATION (c),
			      "%qD appears more than once in data clauses", t);
		    remove = സത്യം;
		  }
		അല്ലെങ്കിൽ എങ്കിൽ (bitmap_bit_p (&map_head, DECL_UID (t))
			 && !bitmap_bit_p (&map_field_head, DECL_UID (t))
			 && openacc)
		  {
		    error_at (OMP_CLAUSE_LOCATION (c),
			      "%qD appears more than once in data clauses", t);
		    remove = സത്യം;
		  }
		അല്ലെങ്കിൽ
		  bitmap_set_bit (&map_firstprivate_head, DECL_UID (t));
	      }
	    അല്ലെങ്കിൽ എങ്കിൽ (bitmap_bit_p (&map_head, DECL_UID (t))
		     && !bitmap_bit_p (&map_field_head, DECL_UID (t))
		     && ort != C_ORT_OMP
		     && ort != C_ORT_OMP_TARGET
		     && ort != C_ORT_OMP_EXIT_DATA)
	      {
		എങ്കിൽ (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_MAP)
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD appears more than once in motion clauses", t);
		അല്ലെങ്കിൽ എങ്കിൽ (openacc)
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD appears more than once in data clauses", t);
		അല്ലെങ്കിൽ
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD appears more than once in map clauses", t);
		remove = സത്യം;
	      }
	    അല്ലെങ്കിൽ എങ്കിൽ (openacc && bitmap_bit_p (&generic_head, DECL_UID (t)))
	      {
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD appears more than once in data clauses", t);
		remove = സത്യം;
	      }
	    അല്ലെങ്കിൽ എങ്കിൽ (bitmap_bit_p (&firstprivate_head, DECL_UID (t))
		     || bitmap_bit_p (&is_on_device_head, DECL_UID (t)))
	      {
		എങ്കിൽ (openacc)
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD appears more than once in data clauses", t);
		അല്ലെങ്കിൽ
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD appears both in data and map clauses", t);
		remove = സത്യം;
	      }
	    അല്ലെങ്കിൽ എങ്കിൽ (!omp_access_chain_p (addr_tokens, 1))
	      {
		bitmap_set_bit (&map_head, DECL_UID (t));
		എങ്കിൽ (t != OMP_CLAUSE_DECL (c)
		    && വൃക്ഷം_CODE (OMP_CLAUSE_DECL (c)) == COMPONENT_REF)
		  bitmap_set_bit (&map_field_head, DECL_UID (t));
	      }

	  skip_decl_checks:
	    /* If we call omp_expand_map_clause in handle_omp_array_sections,
	       the containing loop (here) iterates through the new nodes
	       created by that expansion.  Avoid expanding those again (just
	       by checking the node type).  */
	    എങ്കിൽ (!remove
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
		വൃക്ഷം nc = ai.expand_map_clause (c, OMP_CLAUSE_DECL (c),
						addr_tokens, ort);
		എങ്കിൽ (nc != error_mark_കണ്ണി)
		  c = nc;
	      }
	  }
	  നിർത്തുക;

	അവസ്ഥ OMP_CLAUSE_ENTER:
	അവസ്ഥ OMP_CLAUSE_LINK:
	അവസ്ഥ OMP_CLAUSE_LOCAL:
	  t = OMP_CLAUSE_DECL (c);
	  സ്ഥിരം അക്ഷരം *cname;
	  cname = omp_clause_code_name[OMP_CLAUSE_CODE (c)];
	  എങ്കിൽ (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_ENTER
	      && OMP_CLAUSE_ENTER_TO (c))
	    cname = "to";
	  എങ്കിൽ (വൃക്ഷം_CODE (t) == FUNCTION_DECL
	      && OMP_CLAUSE_CODE (c) == OMP_CLAUSE_ENTER)
	    ;
	  അല്ലെങ്കിൽ എങ്കിൽ (!VAR_P (t))
	    {
	      എങ്കിൽ (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_ENTER)
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qE is neither a variable nor a function name in "
			  "clause %qs", t, cname);
	      അല്ലെങ്കിൽ
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qE is not a variable in clause %qs", t, cname);
	      remove = സത്യം;
	    }
	  അല്ലെങ്കിൽ എങ്കിൽ (DECL_THREAD_LOCAL_P (t))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qD is threadprivate variable in %qs clause", t,
			cname);
	      remove = സത്യം;
	    }
	  അല്ലെങ്കിൽ എങ്കിൽ (!omp_mappable_type (വൃക്ഷം_TYPE (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qD does not have a mappable type in %qs clause", t,
			cname);
	      remove = സത്യം;
	    }
	  എങ്കിൽ (remove)
	    നിർത്തുക;
	  എങ്കിൽ (bitmap_bit_p (&generic_head, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE appears more than once on the same "
			"%<declare target%> directive", t);
	      remove = സത്യം;
	    }
	  അല്ലെങ്കിൽ
	    bitmap_set_bit (&generic_head, DECL_UID (t));
	  നിർത്തുക;

	അവസ്ഥ OMP_CLAUSE_UNIFORM:
	  t = OMP_CLAUSE_DECL (c);
	  എങ്കിൽ (വൃക്ഷം_CODE (t) != PARM_DECL)
	    {
	      എങ്കിൽ (DECL_P (t))
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD is not an argument in %<uniform%> clause", t);
	      അല്ലെങ്കിൽ
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qE is not an argument in %<uniform%> clause", t);
	      remove = സത്യം;
	      നിർത്തുക;
	    }
	  /* map_head bitmap is used as uniform_head if declare_simd.  */
	  bitmap_set_bit (&map_head, DECL_UID (t));
	  പോകുക check_dup_generic;

	അവസ്ഥ OMP_CLAUSE_IS_DEVICE_PTR:
	അവസ്ഥ OMP_CLAUSE_USE_DEVICE_PTR:
	  t = OMP_CLAUSE_DECL (c);
	  എങ്കിൽ (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IS_DEVICE_PTR)
	    bitmap_set_bit (&is_on_device_head, DECL_UID (t));
	  എങ്കിൽ (വൃക്ഷം_CODE (വൃക്ഷം_TYPE (t)) != POINTER_TYPE)
	    {
	      എങ്കിൽ (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_USE_DEVICE_PTR
		  && !openacc)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qs variable is not a pointer",
			    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		  remove = സത്യം;
		}
	      അല്ലെങ്കിൽ എങ്കിൽ (വൃക്ഷം_CODE (വൃക്ഷം_TYPE (t)) != ARRAY_TYPE)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qs variable is neither a pointer nor an array",
			    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		  remove = സത്യം;
		}
	    }
	  പോകുക check_dup_generic;

	അവസ്ഥ OMP_CLAUSE_HAS_DEVICE_ADDR:
	  t = OMP_CLAUSE_DECL (c);
	  എങ്കിൽ (വൃക്ഷം_CODE (t) == OMP_ARRAY_SECTION)
	    {
	      എങ്കിൽ (handle_omp_array_sections (c, ort))
		remove = സത്യം;
	      അല്ലെങ്കിൽ
		{
		  t = OMP_CLAUSE_DECL (c);
		  ആകുമ്പോൾ (വൃക്ഷം_CODE (t) == ARRAY_REF)
		    t = വൃക്ഷം_OPERAND (t, 0);
		}
	    }
	  bitmap_set_bit (&is_on_device_head, DECL_UID (t));
	  എങ്കിൽ (VAR_P (t) || വൃക്ഷം_CODE (t) == PARM_DECL)
	    c_mark_addressable (t);
	  പോകുക check_dup_generic_t;

	അവസ്ഥ OMP_CLAUSE_USE_DEVICE_ADDR:
	  t = OMP_CLAUSE_DECL (c);
	  എങ്കിൽ (VAR_P (t) || വൃക്ഷം_CODE (t) == PARM_DECL)
	    c_mark_addressable (t);
	  പോകുക check_dup_generic;

	അവസ്ഥ OMP_CLAUSE_NOWAIT:
	  എങ്കിൽ (copyprivate_seen)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<nowait%> clause must not be used together "
			"with %<copyprivate%> clause");
	      remove = സത്യം;
	      നിർത്തുക;
	    }
	  nowait_clause = pc;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  തുടരുക;

	അവസ്ഥ OMP_CLAUSE_ORDER:
	  എങ്കിൽ (ordered_clause)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<order%> clause must not be used together "
			"with %<ordered%> clause");
	      remove = സത്യം;
	      നിർത്തുക;
	    }
	  അല്ലെങ്കിൽ എങ്കിൽ (order_clause)
	    {
	      /* Silently remove duplicates.  */
	      remove = സത്യം;
	      നിർത്തുക;
	    }
	  order_clause = pc;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  തുടരുക;

	അവസ്ഥ OMP_CLAUSE_DETACH:
	  t = OMP_CLAUSE_DECL (c);
	  എങ്കിൽ (detach_seen)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"too many %qs clauses on a task construct",
			"detach");
	      remove = സത്യം;
	      നിർത്തുക;
	    }
	  detach_seen = pc;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  c_mark_addressable (t);
	  തുടരുക;

	അവസ്ഥ OMP_CLAUSE_IF:
	അവസ്ഥ OMP_CLAUSE_SELF:
	അവസ്ഥ OMP_CLAUSE_അക്കം_THREADS:
	അവസ്ഥ OMP_CLAUSE_അക്കം_TEAMS:
	അവസ്ഥ OMP_CLAUSE_THREAD_LIMIT:
	അവസ്ഥ OMP_CLAUSE_DEFAULT:
	അവസ്ഥ OMP_CLAUSE_UNTIED:
	അവസ്ഥ OMP_CLAUSE_COLLAPSE:
	അവസ്ഥ OMP_CLAUSE_FINAL:
	അവസ്ഥ OMP_CLAUSE_DEVICE:
	അവസ്ഥ OMP_CLAUSE_DIST_SCHEDULE:
	അവസ്ഥ OMP_CLAUSE_DYN_GROUPPRIVATE:
	അവസ്ഥ OMP_CLAUSE_PARALLEL:
	അവസ്ഥ OMP_CLAUSE_FOR:
	അവസ്ഥ OMP_CLAUSE_SECTIONS:
	അവസ്ഥ OMP_CLAUSE_TASKGROUP:
	അവസ്ഥ OMP_CLAUSE_PROC_BIND:
	അവസ്ഥ OMP_CLAUSE_DEVICE_TYPE:
	അവസ്ഥ OMP_CLAUSE_PRIORITY:
	അവസ്ഥ OMP_CLAUSE_THREADS:
	അവസ്ഥ OMP_CLAUSE_SIMD:
	അവസ്ഥ OMP_CLAUSE_HINT:
	അവസ്ഥ OMP_CLAUSE_FILTER:
	അവസ്ഥ OMP_CLAUSE_DEFAULTMAP:
	അവസ്ഥ OMP_CLAUSE_BIND:
	അവസ്ഥ OMP_CLAUSE_അക്കം_GANGS:
	അവസ്ഥ OMP_CLAUSE_അക്കം_WORKERS:
	അവസ്ഥ OMP_CLAUSE_VECTOR_LENGTH:
	അവസ്ഥ OMP_CLAUSE_ASYNC:
	അവസ്ഥ OMP_CLAUSE_WAIT:
	അവസ്ഥ OMP_CLAUSE_AUTO:
	അവസ്ഥ OMP_CLAUSE_INDEPENDENT:
	അവസ്ഥ OMP_CLAUSE_SEQ:
	അവസ്ഥ OMP_CLAUSE_GANG:
	അവസ്ഥ OMP_CLAUSE_WORKER:
	അവസ്ഥ OMP_CLAUSE_VECTOR:
	അവസ്ഥ OMP_CLAUSE_TILE:
	അവസ്ഥ OMP_CLAUSE_IF_PRESENT:
	അവസ്ഥ OMP_CLAUSE_FINALIZE:
	അവസ്ഥ OMP_CLAUSE_NOHOST:
	അവസ്ഥ OMP_CLAUSE_INDIRECT:
	അവസ്ഥ OMP_CLAUSE_NOVARIANTS:
	അവസ്ഥ OMP_CLAUSE_NOCONTEXT:
	  pc = &OMP_CLAUSE_CHAIN (c);
	  തുടരുക;

	അവസ്ഥ OMP_CLAUSE_GRAINSIZE:
	  grainsize_seen = pc;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  തുടരുക;

	അവസ്ഥ OMP_CLAUSE_അക്കം_TASKS:
	  അക്കം_tasks_seen = സത്യം;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  തുടരുക;

	അവസ്ഥ OMP_CLAUSE_MERGEABLE:
	  mergeable_seen = സത്യം;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  തുടരുക;

	അവസ്ഥ OMP_CLAUSE_NOGROUP:
	  nogroup_seen = pc;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  തുടരുക;

	അവസ്ഥ OMP_CLAUSE_SCHEDULE:
	  schedule_clause = c;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  തുടരുക;

	അവസ്ഥ OMP_CLAUSE_ORDERED:
	  ordered_clause = c;
	  എങ്കിൽ (order_clause)
	    {
	      error_at (OMP_CLAUSE_LOCATION (*order_clause),
			"%<order%> clause must not be used together "
			"with %<ordered%> clause");
	      *order_clause = OMP_CLAUSE_CHAIN (*order_clause);
	      order_clause = ശൂന്യ;
	    }
	  pc = &OMP_CLAUSE_CHAIN (c);
	  തുടരുക;

	അവസ്ഥ OMP_CLAUSE_SAFELEN:
	  safelen = c;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  തുടരുക;
	അവസ്ഥ OMP_CLAUSE_SIMDLEN:
	  simdlen = c;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  തുടരുക;

	അവസ്ഥ OMP_CLAUSE_FULL:
	  full_seen = pc;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  തുടരുക;

	അവസ്ഥ OMP_CLAUSE_PARTIAL:
	  partial_seen = സത്യം;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  തുടരുക;

	അവസ്ഥ OMP_CLAUSE_SIZES:
	  pc = &OMP_CLAUSE_CHAIN (c);
	  തുടരുക;

	അവസ്ഥ OMP_CLAUSE_INBRANCH:
	അവസ്ഥ OMP_CLAUSE_NOTINBRANCH:
	  എങ്കിൽ (branch_seen)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<inbranch%> clause is incompatible with "
			"%<notinbranch%>");
	      remove = സത്യം;
	      നിർത്തുക;
	    }
	  branch_seen = സത്യം;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  തുടരുക;

	അവസ്ഥ OMP_CLAUSE_INCLUSIVE:
	അവസ്ഥ OMP_CLAUSE_EXCLUSIVE:
	  need_complete = സത്യം;
	  need_implicitly_determined = സത്യം;
	  t = OMP_CLAUSE_DECL (c);
	  എങ്കിൽ (!VAR_P (t) && വൃക്ഷം_CODE (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in clause %qs", t,
			omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	      remove = സത്യം;
	    }
	  നിർത്തുക;

	അവസ്ഥ OMP_CLAUSE_INIT:
	  init_seen = സത്യം;
	  എങ്കിൽ (!OMP_CLAUSE_INIT_TARGETSYNC (c))
	    init_no_targetsync_clause = c;
	  /* FALLTHRU */
	അവസ്ഥ OMP_CLAUSE_DESTROY:
	അവസ്ഥ OMP_CLAUSE_USE:
	  init_use_destroy_seen = സത്യം;
	  t = OMP_CLAUSE_DECL (c);
	  എങ്കിൽ (bitmap_bit_p (&generic_head, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qD appears more than once in action clauses", t);
	      remove = സത്യം;
	      നിർത്തുക;
	    }
	  bitmap_set_bit (&generic_head, DECL_UID (t));
	  /* FALLTHRU */
	അവസ്ഥ OMP_CLAUSE_INTEROP:
	  എങ്കിൽ (/* ort == C_ORT_OMP_INTEROP [uncomment for depobj init]  */
		   !c_omp_interop_t_p (വൃക്ഷം_TYPE (OMP_CLAUSE_DECL (c))))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qD must be of %<omp_interop_t%>",
			OMP_CLAUSE_DECL (c));
	      remove = സത്യം;
	    }
	  അല്ലെങ്കിൽ എങ്കിൽ ((OMP_CLAUSE_CODE (c) == OMP_CLAUSE_INIT
		    || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DESTROY)
		   && വൃക്ഷം_READONLY (OMP_CLAUSE_DECL (c)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
		      "%qD shall not be const", OMP_CLAUSE_DECL (c));
	      remove = സത്യം;
	    }
	  pc = &OMP_CLAUSE_CHAIN (c);
	  നിർത്തുക;
	സ്ഥിരസ്ഥിതി:
	  gcc_unreachable ();
	}

      എങ്കിൽ (!remove)
	{
	  t = OMP_CLAUSE_DECL (c);

	  എങ്കിൽ (need_complete)
	    {
	      t = require_complete_type (OMP_CLAUSE_LOCATION (c), t);
	      എങ്കിൽ (t == error_mark_കണ്ണി)
		remove = സത്യം;
	    }

	  എങ്കിൽ (need_implicitly_determined)
	    {
	      സ്ഥിരം അക്ഷരം *share_name = ശൂന്യ;

	      എങ്കിൽ (VAR_P (t) && DECL_THREAD_LOCAL_P (t))
		share_name = "threadprivate";
	      അല്ലെങ്കിൽ തിരഞ്ഞെടുപ്പ് (c_omp_predetermined_sharing (t))
		{
		അവസ്ഥ OMP_CLAUSE_DEFAULT_UNSPECIFIED:
		  നിർത്തുക;
		അവസ്ഥ OMP_CLAUSE_DEFAULT_SHARED:
		  എങ്കിൽ ((OMP_CLAUSE_CODE (c) == OMP_CLAUSE_SHARED
		       || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_FIRSTPRIVATE)
		      && c_omp_predefined_variable (t))
		    /* The __func__ variable and similar function-local
		       predefined variables may be listed in a shared or
		       firstprivate clause.  */
		    നിർത്തുക;
		  share_name = "shared";
		  നിർത്തുക;
		അവസ്ഥ OMP_CLAUSE_DEFAULT_PRIVATE:
		  share_name = "private";
		  നിർത്തുക;
		സ്ഥിരസ്ഥിതി:
		  gcc_unreachable ();
		}
	      എങ്കിൽ (share_name)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qE is predetermined %qs for %qs",
			    t, share_name,
			    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		  remove = സത്യം;
		}
	      അല്ലെങ്കിൽ എങ്കിൽ (വൃക്ഷം_READONLY (t)
		       && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_SHARED
		       && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_FIRSTPRIVATE)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%<const%> qualified %qE may appear only in "
			    "%<shared%> or %<firstprivate%> clauses", t);
		  remove = സത്യം;
		}
	    }
	}

      എങ്കിൽ (remove)
	{
	  എങ്കിൽ (grp_start_p)
	    {
	      /* If we found a clause to remove, we want to remove the whole
		 expanded group, otherwise gimplify
		 (omp_resolve_clause_dependencies) can get confused.  */
	      *grp_start_p = grp_sentinel;
	      pc = grp_start_p;
	      grp_start_p = ശൂന്യ;
	    }
	  അല്ലെങ്കിൽ
	    *pc = OMP_CLAUSE_CHAIN (c);
	}
      അല്ലെങ്കിൽ
	pc = &OMP_CLAUSE_CHAIN (c);
    }

  എങ്കിൽ (grp_start_p
      && OMP_CLAUSE_HAS_ITERATORS (*grp_start_p))
    വേണ്ടി (വൃക്ഷം gc = *grp_start_p; gc; gc = OMP_CLAUSE_CHAIN (gc))
      OMP_CLAUSE_ITERATORS (gc) = OMP_CLAUSE_ITERATORS (*grp_start_p);

  എങ്കിൽ (simdlen
      && safelen
      && വൃക്ഷം_int_cst_lt (OMP_CLAUSE_SAFELEN_വ്യഞ്ജകം (safelen),
			  OMP_CLAUSE_SIMDLEN_വ്യഞ്ജകം (simdlen)))
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
      OMP_CLAUSE_SIMDLEN_വ്യഞ്ജകം (simdlen)
	= OMP_CLAUSE_SAFELEN_വ്യഞ്ജകം (safelen);
    }

  എങ്കിൽ (ordered_clause
      && schedule_clause
      && (OMP_CLAUSE_SCHEDULE_KIND (schedule_clause)
	  & OMP_CLAUSE_SCHEDULE_NONMONOTONIC))
    {
      error_at (OMP_CLAUSE_LOCATION (schedule_clause),
		"%<nonmonotonic%> schedule modifier specified together "
		"with %<ordered%> clause");
      OMP_CLAUSE_SCHEDULE_KIND (schedule_clause)
	= (എണ്ണൽ omp_clause_schedule_kind)
	  (OMP_CLAUSE_SCHEDULE_KIND (schedule_clause)
	   & ~OMP_CLAUSE_SCHEDULE_NONMONOTONIC);
    }

  എങ്കിൽ (reduction_seen < 0 && ordered_clause)
    {
      error_at (OMP_CLAUSE_LOCATION (ordered_clause),
		"%qs clause specified together with %<inscan%> "
		"%<reduction%> clause", "ordered");
      reduction_seen = -2;
    }

  എങ്കിൽ (reduction_seen < 0 && schedule_clause)
    {
      error_at (OMP_CLAUSE_LOCATION (schedule_clause),
		"%qs clause specified together with %<inscan%> "
		"%<reduction%> clause", "schedule");
      reduction_seen = -2;
    }

  എങ്കിൽ (linear_variable_step_check
      || reduction_seen == -2
      || allocate_seen
      || target_in_reduction_seen)
    വേണ്ടി (pc = &clauses, c = clauses; c ; c = *pc)
      {
	തർക്കം remove = അസത്യം;
	എങ്കിൽ (allocate_seen)
	  തിരഞ്ഞെടുപ്പ് (OMP_CLAUSE_CODE (c))
	    {
	    അവസ്ഥ OMP_CLAUSE_REDUCTION:
	    അവസ്ഥ OMP_CLAUSE_IN_REDUCTION:
	    അവസ്ഥ OMP_CLAUSE_TASK_REDUCTION:
	      എങ്കിൽ (വൃക്ഷം_CODE (OMP_CLAUSE_DECL (c)) == MEM_REF)
		{
		  t = വൃക്ഷം_OPERAND (OMP_CLAUSE_DECL (c), 0);
		  എങ്കിൽ (വൃക്ഷം_CODE (t) == POINTER_PLUS_വ്യഞ്ജകം)
		    t = വൃക്ഷം_OPERAND (t, 0);
		  എങ്കിൽ (വൃക്ഷം_CODE (t) == ADDR_വ്യഞ്ജകം
		      || INDIRECT_REF_P (t))
		    t = വൃക്ഷം_OPERAND (t, 0);
		  എങ്കിൽ (DECL_P (t))
		    bitmap_clear_bit (&aligned_head, DECL_UID (t));
		  നിർത്തുക;
		}
	      /* FALLTHRU */
	    അവസ്ഥ OMP_CLAUSE_PRIVATE:
	    അവസ്ഥ OMP_CLAUSE_FIRSTPRIVATE:
	    അവസ്ഥ OMP_CLAUSE_LASTPRIVATE:
	    അവസ്ഥ OMP_CLAUSE_LINEAR:
	      എങ്കിൽ (DECL_P (OMP_CLAUSE_DECL (c)))
		bitmap_clear_bit (&aligned_head,
				  DECL_UID (OMP_CLAUSE_DECL (c)));
	      നിർത്തുക;
	    സ്ഥിരസ്ഥിതി:
	      നിർത്തുക;
	    }
	എങ്കിൽ (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_LINEAR
	    && OMP_CLAUSE_LINEAR_VARIABLE_STRIDE (c)
	    && !bitmap_bit_p (&map_head,
			      DECL_UID (OMP_CLAUSE_LINEAR_STEP (c))))
	  {
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%<linear%> clause step is a parameter %qD not "
		      "specified in %<uniform%> clause",
		      OMP_CLAUSE_LINEAR_STEP (c));
	    remove = സത്യം;
	  }
	അല്ലെങ്കിൽ എങ്കിൽ (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_REDUCTION
		 && reduction_seen == -2)
	  OMP_CLAUSE_REDUCTION_INSCAN (c) = 0;
	എങ്കിൽ (target_in_reduction_seen
	    && OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP)
	  {
	    വൃക്ഷം t = OMP_CLAUSE_DECL (c);
	    ആകുമ്പോൾ (handled_component_p (t)
		   || INDIRECT_REF_P (t)
		   || വൃക്ഷം_CODE (t) == ADDR_വ്യഞ്ജകം
		   || വൃക്ഷം_CODE (t) == MEM_REF
		   || വൃക്ഷം_CODE (t) == NON_LVALUE_വ്യഞ്ജകം)
	      t = വൃക്ഷം_OPERAND (t, 0);
	    എങ്കിൽ (DECL_P (t)
		&& bitmap_bit_p (&oacc_reduction_head, DECL_UID (t)))
	      OMP_CLAUSE_MAP_IN_REDUCTION (c) = 1;
	  }

	എങ്കിൽ (remove)
	  *pc = OMP_CLAUSE_CHAIN (c);
	അല്ലെങ്കിൽ
	  pc = &OMP_CLAUSE_CHAIN (c);
      }

  എങ്കിൽ (allocate_seen)
    വേണ്ടി (pc = &clauses, c = clauses; c ; c = *pc)
      {
	തർക്കം remove = അസത്യം;
	എങ്കിൽ (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_ALLOCATE
	    && !OMP_CLAUSE_ALLOCATE_COMBINED (c)
	    && bitmap_bit_p (&aligned_head, DECL_UID (OMP_CLAUSE_DECL (c))))
	  {
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%qD specified in %<allocate%> clause but not in "
		      "an explicit privatization clause", OMP_CLAUSE_DECL (c));
	    remove = സത്യം;
	  }
	എങ്കിൽ (remove)
	  *pc = OMP_CLAUSE_CHAIN (c);
	അല്ലെങ്കിൽ
	  pc = &OMP_CLAUSE_CHAIN (c);
      }

  എങ്കിൽ (nogroup_seen && reduction_seen)
    {
      error_at (OMP_CLAUSE_LOCATION (*nogroup_seen),
		"%<nogroup%> clause must not be used together with "
		"%<reduction%> clause");
      *nogroup_seen = OMP_CLAUSE_CHAIN (*nogroup_seen);
    }

  എങ്കിൽ (grainsize_seen && അക്കം_tasks_seen)
    {
      error_at (OMP_CLAUSE_LOCATION (*grainsize_seen),
		"%<grainsize%> clause must not be used together with "
		"%<num_tasks%> clause");
      *grainsize_seen = OMP_CLAUSE_CHAIN (*grainsize_seen);
    }

  എങ്കിൽ (full_seen && partial_seen)
    {
      error_at (OMP_CLAUSE_LOCATION (*full_seen),
		"%<full%> clause must not be used together with "
		"%<partial%> clause");
      *full_seen = OMP_CLAUSE_CHAIN (*full_seen);
    }

  എങ്കിൽ (detach_seen)
    {
      എങ്കിൽ (mergeable_seen)
	{
	  error_at (OMP_CLAUSE_LOCATION (*detach_seen),
		    "%<detach%> clause must not be used together with "
		    "%<mergeable%> clause");
	  *detach_seen = OMP_CLAUSE_CHAIN (*detach_seen);
	}
      അല്ലെങ്കിൽ
	{
	  വൃക്ഷം detach_decl = OMP_CLAUSE_DECL (*detach_seen);

	  വേണ്ടി (pc = &clauses, c = clauses; c ; c = *pc)
	    {
	      തർക്കം remove = അസത്യം;
	      എങ്കിൽ ((OMP_CLAUSE_CODE (c) == OMP_CLAUSE_SHARED
		   || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_PRIVATE
		   || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_FIRSTPRIVATE
		   || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_LASTPRIVATE)
		  && OMP_CLAUSE_DECL (c) == detach_decl)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "the event handle of a %<detach%> clause "
			    "should not be in a data-sharing clause");
		  remove = സത്യം;
		}
	      എങ്കിൽ (remove)
		*pc = OMP_CLAUSE_CHAIN (c);
	      അല്ലെങ്കിൽ
		pc = &OMP_CLAUSE_CHAIN (c);
	    }
	}
    }

  എങ്കിൽ (ort == C_ORT_OMP_INTEROP
      && depend_clause
      && (!init_use_destroy_seen
	  || (init_seen && init_no_targetsync_clause)))
    {
      error_at (OMP_CLAUSE_LOCATION (depend_clause),
		"%<depend%> clause requires action clauses with "
		"%<targetsync%> interop-type");
      എങ്കിൽ (init_no_targetsync_clause)
	inform (OMP_CLAUSE_LOCATION (init_no_targetsync_clause),
		"%<init%> clause lacks the %<targetsync%> modifier");
    }

  bitmap_obstack_release (ശൂന്യ);
  തിരികെ clauses;
}

/* Do processing necessary to make CLAUSES well-formed, where CLAUSES result
   from implicit instantiation of user-defined mappers (in gimplify.cc).  */

വൃക്ഷം
c_omp_finish_mapper_clauses (വൃക്ഷം clauses)
{
  തിരികെ c_finish_omp_clauses (clauses, C_ORT_OMP);
}

/* Return code to initialize DST with a copy constructor from SRC.
   C doesn't have copy constructors nor assignment operators, only for
   _Atomic vars we need to perform __atomic_load from src into a temporary
   followed by __atomic_store of the temporary to dst.  */

വൃക്ഷം
c_omp_clause_copy_ctor (വൃക്ഷം clause, വൃക്ഷം dst, വൃക്ഷം src)
{
  എങ്കിൽ (!really_atomic_lvalue (dst) && !really_atomic_lvalue (src))
    തിരികെ build2 (MODIFY_വ്യഞ്ജകം, വൃക്ഷം_TYPE (dst), dst, src);

  location_t loc = OMP_CLAUSE_LOCATION (clause);
  വൃക്ഷം type = വൃക്ഷം_TYPE (dst);
  വൃക്ഷം nonatomic_type = build_qualified_type (type, TYPE_UNQUALIFIED);
  വൃക്ഷം tmp = create_tmp_var (nonatomic_type);
  വൃക്ഷം tmp_addr = build_fold_addr_വ്യഞ്ജകം (tmp);
  വൃക്ഷം_ADDRESSABLE (tmp) = 1;
  suppress_warning (tmp);
  വൃക്ഷം src_addr = build_fold_addr_വ്യഞ്ജകം (src);
  വൃക്ഷം dst_addr = build_fold_addr_വ്യഞ്ജകം (dst);
  വൃക്ഷം seq_cst = build_int_cst (integer_type_കണ്ണി, MEMMODEL_SEQ_CST);
  vec<വൃക്ഷം, va_gc> *params;
  /* Expansion of a generic atomic load may require an addition
     element, so allocate enough to prevent a resize.  */
  vec_alloc (params, 4);

  /* Build __atomic_load (&src, &tmp, SEQ_CST);  */
  വൃക്ഷം fndecl = builtin_decl_explicit (BUILT_IN_ATOMIC_LOAD);
  params->quick_തള്ളുക (src_addr);
  params->quick_തള്ളുക (tmp_addr);
  params->quick_തള്ളുക (seq_cst);
  വൃക്ഷം load = c_build_function_call_vec (loc, vNULL, fndecl, params, ശൂന്യ);

  vec_alloc (params, 4);

  /* Build __atomic_store (&dst, &tmp, SEQ_CST);  */
  fndecl = builtin_decl_explicit (BUILT_IN_ATOMIC_STORE);
  params->quick_തള്ളുക (dst_addr);
  params->quick_തള്ളുക (tmp_addr);
  params->quick_തള്ളുക (seq_cst);
  വൃക്ഷം store = c_build_function_call_vec (loc, vNULL, fndecl, params, ശൂന്യ);
  തിരികെ build2 (COMPOUND_വ്യഞ്ജകം, void_type_കണ്ണി, load, store);
}

/* Create a transaction node.  */

വൃക്ഷം
c_finish_transaction (location_t loc, വൃക്ഷം block, പൂർണ്ണസംഖ്യ flags)
{
  വൃക്ഷം stmt = build_stmt (loc, TRANSACTION_വ്യഞ്ജകം, block);
  എങ്കിൽ (flags & TM_STMT_ATTR_OUTER)
    TRANSACTION_വ്യഞ്ജകം_OUTER (stmt) = 1;
  എങ്കിൽ (flags & TM_STMT_ATTR_RELAXED)
    TRANSACTION_വ്യഞ്ജകം_RELAXED (stmt) = 1;
  തിരികെ add_stmt (stmt);
}

/* Make a variant type in the proper way for C/C++, propagating qualifiers
   down to the element type of an array.  If ORIG_QUAL_TYPE is not
   NULL, then it should be used as the qualified type
   ORIG_QUAL_INDIRECT levels down in array type derivation (to
   preserve information about the typedef name from which an array
   type was derived).  */

വൃക്ഷം
c_build_qualified_type (വൃക്ഷം type, പൂർണ്ണസംഖ്യ type_quals, വൃക്ഷം orig_qual_type,
			size_t orig_qual_indirect)
{
  എങ്കിൽ (type == error_mark_കണ്ണി)
    തിരികെ type;

  എങ്കിൽ (വൃക്ഷം_CODE (type) == ARRAY_TYPE)
    {
      വൃക്ഷം t;
      വൃക്ഷം element_type = c_build_qualified_type (വൃക്ഷം_TYPE (type),
						  type_quals, orig_qual_type,
						  orig_qual_indirect - 1);

      /* See if we already have an identically qualified type.  */
      എങ്കിൽ (orig_qual_type && orig_qual_indirect == 0)
	t = orig_qual_type;
      അല്ലെങ്കിൽ
	വേണ്ടി (t = TYPE_MAIN_VARIANT (type); t; t = TYPE_NEXT_VARIANT (t))
	  {
	    എങ്കിൽ (TYPE_QUALS (strip_array_types (t)) == type_quals
		&& TYPE_NAME (t) == TYPE_NAME (type)
		&& TYPE_CONTEXT (t) == TYPE_CONTEXT (type)
		&& attribute_list_equal (TYPE_ATTRIBUTES (t),
					 TYPE_ATTRIBUTES (type)))
	      നിർത്തുക;
	  }
      എങ്കിൽ (!t)
	{
          വൃക്ഷം domain = TYPE_DOMAIN (type);

	  t = build_variant_type_copy (type);
	  വൃക്ഷം_TYPE (t) = element_type;
	  TYPE_ADDR_SPACE (t) = TYPE_ADDR_SPACE (element_type);

          എങ്കിൽ (TYPE_STRUCTURAL_EQUALITY_P (element_type)
              || (domain && TYPE_STRUCTURAL_EQUALITY_P (domain)))
            SET_TYPE_STRUCTURAL_EQUALITY (t);
          അല്ലെങ്കിൽ എങ്കിൽ (TYPE_CANONICAL (element_type) != element_type
                   || (domain && TYPE_CANONICAL (domain) != domain))
            {
              വൃക്ഷം unqualified_canon
		= c_build_array_type (TYPE_CANONICAL (element_type),
				      domain ? TYPE_CANONICAL (domain)
					     : NULL_വൃക്ഷം);
              എങ്കിൽ (TYPE_REVERSE_STORAGE_ORDER (type))
                {
                  unqualified_canon
		    = build_distinct_type_copy (unqualified_canon);
                  TYPE_REVERSE_STORAGE_ORDER (unqualified_canon) = 1;
                }
              TYPE_CANONICAL (t)
		= c_build_qualified_type (unqualified_canon, type_quals);
            }
          അല്ലെങ്കിൽ
            TYPE_CANONICAL (t) = t;
	}
      തിരികെ t;
    }

  /* A restrict-qualified pointer type must be a pointer to object or
     incomplete type.  Note that the use of POINTER_TYPE_P also allows
     REFERENCE_TYPEs, which is appropriate for C++.  */
  എങ്കിൽ ((type_quals & TYPE_QUAL_RESTRICT)
      && (!POINTER_TYPE_P (type)
	  || !C_TYPE_OBJECT_OR_INCOMPLETE_P (വൃക്ഷം_TYPE (type))))
    {
      error ("invalid use of %<restrict%>");
      type_quals &= ~TYPE_QUAL_RESTRICT;
    }

  വൃക്ഷം var_type = (orig_qual_type && orig_qual_indirect == 0
		   ? orig_qual_type
		   : build_qualified_type (type, type_quals));

  gcc_checking_assert (C_TYPE_VARIABLE_SIZE (var_type)
		       == C_TYPE_VARIABLE_SIZE (type));
  gcc_checking_assert (c_type_variably_modified_p (var_type)
		       == c_type_variably_modified_p (type));

  /* A variant type does not inherit the list of incomplete vars from the
     type main variant.  */
  എങ്കിൽ ((RECORD_OR_UNION_TYPE_P (var_type)
       || വൃക്ഷം_CODE (var_type) == ENUMERAL_TYPE)
      && TYPE_MAIN_VARIANT (var_type) != var_type)
    C_TYPE_INCOMPLETE_VARS (var_type) = 0;
  തിരികെ var_type;
}

/* Build a VA_ARG_EXPR for the C parser.  */

വൃക്ഷം
c_build_va_arg (location_t loc1, വൃക്ഷം വ്യഞ്ജകം, location_t loc2, വൃക്ഷം type,
		വൃക്ഷം type_വ്യഞ്ജകം)
{
  എങ്കിൽ (error_operand_p (type))
    തിരികെ error_mark_കണ്ണി;
  /* VA_ARG_EXPR cannot be used for a scalar va_list with reverse storage
     order because it takes the address of the expression.  */
  അല്ലെങ്കിൽ എങ്കിൽ (handled_component_p (വ്യഞ്ജകം)
	   && reverse_storage_order_for_component_p (വ്യഞ്ജകം))
    {
      error_at (loc1, "cannot use %<va_arg%> with reverse storage order");
      തിരികെ error_mark_കണ്ണി;
    }
  അല്ലെങ്കിൽ എങ്കിൽ (!COMPLETE_TYPE_P (type))
    {
      error_at (loc2, "second argument to %<va_arg%> is of incomplete "
		"type %qT", type);
      തിരികെ error_mark_കണ്ണി;
    }
  അല്ലെങ്കിൽ എങ്കിൽ (വൃക്ഷം_CODE (type) == FUNCTION_TYPE)
    {
      error_at (loc2, "second argument to %<va_arg%> is a function type %qT",
		type);
      തിരികെ error_mark_കണ്ണി;
    }
  അല്ലെങ്കിൽ എങ്കിൽ (വൃക്ഷം_CODE (type) == ARRAY_TYPE && C_TYPE_VARIABLE_SIZE (type)
	   && !flag_isoc99)
    {
      error_at (loc2, "second argument to %<va_arg%> is an array type %qT",
		type);
      തിരികെ error_mark_കണ്ണി;
    }
  അല്ലെങ്കിൽ എങ്കിൽ (warn_cxx_compat && വൃക്ഷം_CODE (type) == ENUMERAL_TYPE)
    warning_at (loc2, OPT_Wc___compat,
		"C++ requires promoted type, not enum type, in %<va_arg%>");

  എങ്കിൽ (flag_isoc99 && വൃക്ഷം_CODE (type) == ARRAY_TYPE)
    {
      warning_at (loc2, 0, "second argument to %<va_arg%> is an array type %qT",
		  type);
      /* We create a trap but evaluate side effects first.  */
      വൃക്ഷം trapfn = builtin_decl_explicit (BUILT_IN_TRAP);
      trapfn = build_call_വ്യഞ്ജകം_loc (loc2, trapfn, 0);
      വൃക്ഷം e2 = build2 (COMPOUND_വ്യഞ്ജകം, void_type_കണ്ണി, വ്യഞ്ജകം, trapfn);
      /* Return a compound literal of the right type.  */
      വൃക്ഷം e1 = build_compound_literal (loc2, type, ശൂന്യ, സത്യം, 0, ശൂന്യ);
      വ്യഞ്ജകം = build2 (COMPOUND_വ്യഞ്ജകം, type, e2, e1);
    }
  അല്ലെങ്കിൽ
    വ്യഞ്ജകം = build_va_arg (loc2, വ്യഞ്ജകം, type);

  എങ്കിൽ (type_വ്യഞ്ജകം)
    വ്യഞ്ജകം = build2 (COMPOUND_വ്യഞ്ജകം, വൃക്ഷം_TYPE (വ്യഞ്ജകം), type_വ്യഞ്ജകം, വ്യഞ്ജകം);

  തിരികെ വ്യഞ്ജകം;
}

/* Return truthvalue of whether T1 is the same tree structure as T2.
   Return 1 if they are the same. Return false if they are different.  */

തർക്കം
c_വൃക്ഷം_equal (വൃക്ഷം t1, വൃക്ഷം t2)
{
  എണ്ണൽ വൃക്ഷം_code code1, code2;

  എങ്കിൽ (t1 == t2)
    തിരികെ സത്യം;
  എങ്കിൽ (!t1 || !t2)
    തിരികെ അസത്യം;

  വേണ്ടി (code1 = വൃക്ഷം_CODE (t1); code1 == NON_LVALUE_വ്യഞ്ജകം;
       code1 = വൃക്ഷം_CODE (t1))
    t1 = വൃക്ഷം_OPERAND (t1, 0);
  വേണ്ടി (code2 = വൃക്ഷം_CODE (t2); code2 == NON_LVALUE_വ്യഞ്ജകം;
       code2 = വൃക്ഷം_CODE (t2))
    t2 = വൃക്ഷം_OPERAND (t2, 0);

  /* They might have become equal now.  */
  എങ്കിൽ (t1 == t2)
    തിരികെ സത്യം;

  എങ്കിൽ (code1 != code2)
    തിരികെ അസത്യം;

  എങ്കിൽ (CONSTANT_CLASS_P (t1) && !comptypes (വൃക്ഷം_TYPE (t1), വൃക്ഷം_TYPE (t2)))
    തിരികെ അസത്യം;

  തിരഞ്ഞെടുപ്പ് (code1)
    {
    അവസ്ഥ INTEGER_CST:
      തിരികെ wi::to_wide (t1) == wi::to_wide (t2);

    അവസ്ഥ REAL_CST:
      തിരികെ real_equal (&വൃക്ഷം_REAL_CST (t1), &വൃക്ഷം_REAL_CST (t2));

    അവസ്ഥ STRING_CST:
      തിരികെ വൃക്ഷം_STRING_LENGTH (t1) == വൃക്ഷം_STRING_LENGTH (t2)
	&& !memcmp (വൃക്ഷം_STRING_POINTER (t1), വൃക്ഷം_STRING_POINTER (t2),
		    വൃക്ഷം_STRING_LENGTH (t1));

    അവസ്ഥ FIXED_CST:
      തിരികെ FIXED_മൂല്യങ്ങൾ_IDENTICAL (വൃക്ഷം_FIXED_CST (t1),
				     വൃക്ഷം_FIXED_CST (t2));

    അവസ്ഥ COMPLEX_CST:
      തിരികെ c_വൃക്ഷം_equal (വൃക്ഷം_REALPART (t1), വൃക്ഷം_REALPART (t2))
	     && c_വൃക്ഷം_equal (വൃക്ഷം_IMAGPART (t1), വൃക്ഷം_IMAGPART (t2));

    അവസ്ഥ VECTOR_CST:
      തിരികെ operand_equal_p (t1, t2, OEP_ONLY_CONST);

    അവസ്ഥ CONSTRUCTOR:
      /* We need to do this when determining whether or not two
	 non-type pointer to member function template arguments
	 are the same.  */
      എങ്കിൽ (!comptypes (വൃക്ഷം_TYPE (t1), വൃക്ഷം_TYPE (t2))
	  || CONSTRUCTOR_NELTS (t1) != CONSTRUCTOR_NELTS (t2))
	തിരികെ അസത്യം;
      {
	വൃക്ഷം field, മൂല്യം;
	unsigned പൂർണ്ണസംഖ്യ i;
	FOR_EACH_CONSTRUCTOR_ELT (CONSTRUCTOR_ELTS (t1), i, field, മൂല്യം)
	  {
	    constructor_elt *elt2 = CONSTRUCTOR_ELT (t2, i);
	    എങ്കിൽ (!c_വൃക്ഷം_equal (field, elt2->index)
		|| !c_വൃക്ഷം_equal (മൂല്യം, elt2->മൂല്യം))
	      തിരികെ അസത്യം;
	  }
      }
      തിരികെ സത്യം;

    അവസ്ഥ വൃക്ഷം_LIST:
      എങ്കിൽ (!c_വൃക്ഷം_equal (വൃക്ഷം_PURPOSE (t1), വൃക്ഷം_PURPOSE (t2)))
	തിരികെ അസത്യം;
      എങ്കിൽ (!c_വൃക്ഷം_equal (വൃക്ഷം_മൂല്യം (t1), വൃക്ഷം_മൂല്യം (t2)))
	തിരികെ അസത്യം;
      തിരികെ c_വൃക്ഷം_equal (വൃക്ഷം_CHAIN (t1), വൃക്ഷം_CHAIN (t2));

    അവസ്ഥ SAVE_വ്യഞ്ജകം:
      തിരികെ c_വൃക്ഷം_equal (വൃക്ഷം_OPERAND (t1, 0), വൃക്ഷം_OPERAND (t2, 0));

    അവസ്ഥ CALL_വ്യഞ്ജകം:
      {
	വൃക്ഷം arg1, arg2;
	call_വ്യഞ്ജകം_arg_iterator iter1, iter2;
	എങ്കിൽ (!c_വൃക്ഷം_equal (CALL_വ്യഞ്ജകം_FN (t1), CALL_വ്യഞ്ജകം_FN (t2)))
	  തിരികെ അസത്യം;
	വേണ്ടി (arg1 = first_call_വ്യഞ്ജകം_arg (t1, &iter1),
	       arg2 = first_call_വ്യഞ്ജകം_arg (t2, &iter2);
	     arg1 && arg2;
	     arg1 = next_call_വ്യഞ്ജകം_arg (&iter1),
	       arg2 = next_call_വ്യഞ്ജകം_arg (&iter2))
	  എങ്കിൽ (!c_വൃക്ഷം_equal (arg1, arg2))
	    തിരികെ അസത്യം;
	എങ്കിൽ (arg1 || arg2)
	  തിരികെ അസത്യം;
	തിരികെ സത്യം;
      }

    അവസ്ഥ TARGET_വ്യഞ്ജകം:
      {
	വൃക്ഷം o1 = വൃക്ഷം_OPERAND (t1, 0);
	വൃക്ഷം o2 = വൃക്ഷം_OPERAND (t2, 0);

	/* Special case: if either target is an unallocated VAR_DECL,
	   it means that it's going to be unified with whatever the
	   TARGET_EXPR is really supposed to initialize, so treat it
	   as being equivalent to anything.  */
	എങ്കിൽ (VAR_P (o1) && DECL_NAME (o1) == NULL_വൃക്ഷം
	    && !DECL_RTL_SET_P (o1))
	  /*Nop*/;
	അല്ലെങ്കിൽ എങ്കിൽ (VAR_P (o2) && DECL_NAME (o2) == NULL_വൃക്ഷം
		 && !DECL_RTL_SET_P (o2))
	  /*Nop*/;
	അല്ലെങ്കിൽ എങ്കിൽ (!c_വൃക്ഷം_equal (o1, o2))
	  തിരികെ അസത്യം;

	തിരികെ c_വൃക്ഷം_equal (വൃക്ഷം_OPERAND (t1, 1), വൃക്ഷം_OPERAND (t2, 1));
      }

    അവസ്ഥ COMPONENT_REF:
      എങ്കിൽ (വൃക്ഷം_OPERAND (t1, 1) != വൃക്ഷം_OPERAND (t2, 1))
	തിരികെ അസത്യം;
      തിരികെ c_വൃക്ഷം_equal (വൃക്ഷം_OPERAND (t1, 0), വൃക്ഷം_OPERAND (t2, 0));

    അവസ്ഥ PARM_DECL:
    അവസ്ഥ VAR_DECL:
    അവസ്ഥ CONST_DECL:
    അവസ്ഥ FIELD_DECL:
    അവസ്ഥ FUNCTION_DECL:
    അവസ്ഥ IDENTIFIER_കണ്ണി:
    അവസ്ഥ SSA_NAME:
      തിരികെ അസത്യം;

    അവസ്ഥ വൃക്ഷം_VEC:
      {
	unsigned ix;
	എങ്കിൽ (വൃക്ഷം_VEC_LENGTH (t1) != വൃക്ഷം_VEC_LENGTH (t2))
	  തിരികെ അസത്യം;
	വേണ്ടി (ix = വൃക്ഷം_VEC_LENGTH (t1); ix--;)
	  എങ്കിൽ (!c_വൃക്ഷം_equal (വൃക്ഷം_VEC_ELT (t1, ix),
			     വൃക്ഷം_VEC_ELT (t2, ix)))
	    തിരികെ അസത്യം;
	തിരികെ സത്യം;
      }

    CASE_CONVERT:
      എങ്കിൽ (!comptypes (വൃക്ഷം_TYPE (t1), വൃക്ഷം_TYPE (t2)))
	തിരികെ അസത്യം;
      നിർത്തുക;

    സ്ഥിരസ്ഥിതി:
      നിർത്തുക;
    }

  തിരഞ്ഞെടുപ്പ് (വൃക്ഷം_CODE_CLASS (code1))
    {
    അവസ്ഥ tcc_unary:
    അവസ്ഥ tcc_ദ്വിമാന:
    അവസ്ഥ tcc_comparison:
    അവസ്ഥ tcc_expression:
    അവസ്ഥ tcc_vl_exp:
    അവസ്ഥ tcc_reference:
    അവസ്ഥ tcc_statement:
      {
	പൂർണ്ണസംഖ്യ i, n = വൃക്ഷം_OPERAND_LENGTH (t1);

	തിരഞ്ഞെടുപ്പ് (code1)
	  {
	  അവസ്ഥ PREINCREMENT_വ്യഞ്ജകം:
	  അവസ്ഥ PREDECREMENT_വ്യഞ്ജകം:
	  അവസ്ഥ POSTINCREMENT_വ്യഞ്ജകം:
	  അവസ്ഥ POSTDECREMENT_വ്യഞ്ജകം:
	    n = 1;
	    നിർത്തുക;
	  അവസ്ഥ ARRAY_REF:
	    n = 2;
	    നിർത്തുക;
	  സ്ഥിരസ്ഥിതി:
	    നിർത്തുക;
	  }

	എങ്കിൽ (വൃക്ഷം_CODE_CLASS (code1) == tcc_vl_exp
	    && n != വൃക്ഷം_OPERAND_LENGTH (t2))
	  തിരികെ അസത്യം;

	വേണ്ടി (i = 0; i < n; ++i)
	  എങ്കിൽ (!c_വൃക്ഷം_equal (വൃക്ഷം_OPERAND (t1, i), വൃക്ഷം_OPERAND (t2, i)))
	    തിരികെ അസത്യം;

	തിരികെ സത്യം;
      }

    അവസ്ഥ tcc_type:
      തിരികെ comptypes (t1, t2);
    സ്ഥിരസ്ഥിതി:
      gcc_unreachable ();
    }
}

/* Returns true when the function declaration FNDECL is implicit,
   introduced as a result of a call to an otherwise undeclared
   function, and false otherwise.  */

തർക്കം
c_decl_implicit (const_വൃക്ഷം fndecl)
{
  തിരികെ C_DECL_IMPLICIT (fndecl);
}
