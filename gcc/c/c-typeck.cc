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

#అన్తర్భావ "config.h"
#అన్తర్భావ "system.h"
#అన్తర్భావ "coretypes.h"
#అన్తర్భావ "memmodel.h"
#అన్తర్భావ "target.h"
#అన్తర్భావ "function.h"
#అన్తర్భావ "bitmap.h"
#అన్తర్భావ "c-tree.h"
#అన్తర్భావ "gimple-expr.h"
#అన్తర్భావ "predict.h"
#అన్తర్భావ "stor-layout.h"
#అన్తర్భావ "trans-mem.h"
#అన్తర్భావ "varasm.h"
#అన్తర్భావ "stmt.h"
#అన్తర్భావ "langhooks.h"
#అన్తర్భావ "c-lang.h"
#అన్తర్భావ "intl.h"
#అన్తర్భావ "tree-iterator.h"
#అన్తర్భావ "gimplify.h"
#అన్తర్భావ "tree-inline.h"
#అన్తర్భావ "omp-general.h"
#అన్తర్భావ "c-family/c-objc.h"
#అన్తర్భావ "c-family/c-ubsan.h"
#అన్తర్భావ "gomp-constants.h"
#అన్తర్భావ "spellcheck-tree.h"
#అన్తర్భావ "c-family/c-type-mismatch.h"
#అన్తర్భావ "stringpool.h"
#అన్తర్భావ "attribs.h"
#అన్తర్భావ "asan.h"
#అన్తర్భావ "realmpfr.h"
#అన్తర్భావ "tree-pretty-print-markup.h"
#అన్తర్భావ "gcc-urlifier.h"

/* Possible cases of implicit conversions.  Used to select diagnostic messages
   and control folding initializers in convert_for_assignment.  */
గణన impl_conv {
  ic_argpass,
  ic_కేటాయించు,
  ic_init,
  ic_init_const,
  ic_return
};

/* The level of nesting inside "__alignof__".  */
పూర్ణాంకం లోపల_alignof;

/* The level of nesting inside "sizeof".  */
పూర్ణాంకం లోపల_sizeof;

/* The level of nesting inside "countof".  */
పూర్ణాంకం లోపల_countof;

/* The level of nesting inside "typeof".  */
పూర్ణాంకం లోపల_typeof;

/* The level of nesting inside "_Generic".  */
పూర్ణాంకం లోపల_generic;

/* True when parsing OpenMP loop expressions.  */
తార్కిక c_లోపల_omp_for;

/* True when parsing OpenMP map clause.  */
తార్కిక c_omp_array_section_p;

/* The argument of last parsed sizeof expression, only to be tested
   if expr.original_code == SIZEOF_EXPR.  */
వృక్షం c_చివరి_sizeof_arg;
location_t c_చివరి_sizeof_loc;

/* Nonzero if we might need to print a "missing braces around
   initializer" message within this initializer.  */
స్థిర పూర్ణాంకం దొరికింది_missing_braces;

స్థిర తార్కిక require_constant_విలువ;
స్థిర తార్కిక require_constant_elements;
స్థిర తార్కిక require_constexpr_విలువ;

స్థిర వృక్షం qualify_type (వృక్షం, వృక్షం);
నిర్మాణం comptypes_దత్తాంశం;
స్థిర తార్కిక tagged_types_tu_compatible_p (const_వృక్షం, const_వృక్షం,
					  నిర్మాణం comptypes_దత్తాంశం *);
స్థిర తార్కిక comp_లక్ష్యం_types (location_t, వృక్షం, వృక్షం);
స్థిర తార్కిక function_types_compatible_p (const_వృక్షం, const_వృక్షం,
					 నిర్మాణం comptypes_దత్తాంశం *);
స్థిర తార్కిక type_lists_compatible_p (const_వృక్షం, const_వృక్షం,
				     నిర్మాణం comptypes_దత్తాంశం *);
స్థిర పూర్ణాంకం convert_arguments (location_t, vec<location_t>, వృక్షం,
			      vec<వృక్షం, va_gc> *, vec<వృక్షం, va_gc> *, వృక్షం,
			      వృక్షం);
స్థిర వృక్షం సూచిక_diff (location_t, వృక్షం, వృక్షం, వృక్షం *);
స్థిర వృక్షం convert_for_assignment (location_t, location_t, వృక్షం, వృక్షం, వృక్షం,
				    గణన impl_conv, తార్కిక, వృక్షం, వృక్షం, పూర్ణాంకం,
				    పూర్ణాంకం = 0);
స్థిర వృక్షం valid_compound_సమాసం_initializer (వృక్షం, వృక్షం);
స్థిర శూన్య నెట్టు_string (స్థిరరాశి అక్షరం *);
స్థిర శూన్య నెట్టు_member_name (వృక్షం);
స్థిర పూర్ణాంకం spelling_నిడివి (శూన్య);
స్థిర అక్షరం *print_spelling (అక్షరం *);
స్థిర శూన్య warning_init (location_t, పూర్ణాంకం, స్థిరరాశి అక్షరం *);
స్థిర వృక్షం digest_init (location_t, వృక్షం, వృక్షం, వృక్షం, వృక్షం, తార్కిక, తార్కిక, తార్కిక,
			 తార్కిక, తార్కిక, తార్కిక);
స్థిర శూన్య output_init_element (location_t, వృక్షం, వృక్షం, తార్కిక, వృక్షం, వృక్షం, తార్కిక,
				 తార్కిక, నిర్మాణం obstack *);
స్థిర శూన్య output_pending_init_elements (పూర్ణాంకం, నిర్మాణం obstack *);
స్థిర తార్కిక సమితి_designator (location_t, తార్కిక, నిర్మాణం obstack *);
స్థిర శూన్య నెట్టు_range_దొంతర (వృక్షం, నిర్మాణం obstack *);
స్థిర శూన్య కూడు_pending_init (location_t, వృక్షం, వృక్షం, వృక్షం, తార్కిక,
			      నిర్మాణం obstack *);
స్థిర శూన్య సమితి_nonincremental_init (నిర్మాణం obstack *);
స్థిర శూన్య సమితి_nonincremental_init_from_string (వృక్షం, నిర్మాణం obstack *);
స్థిర వృక్షం కనుగొను_init_member (వృక్షం, నిర్మాణం obstack *);
స్థిర శూన్య readonly_warning (వృక్షం, గణన lvalue_use);
స్థిర పూర్ణాంకం lvalue_or_else (location_t, const_వృక్షం, గణన lvalue_use);
స్థిర శూన్య రికార్డు_maybe_వాడిన_decl (వృక్షం, తార్కిక చిరునామా);
స్థిర తార్కిక comptypes_అంతర్గత (const_వృక్షం, const_వృక్షం,
				నిర్మాణం comptypes_దత్తాంశం *దత్తాంశం);
స్థిర తార్కిక comptypes_check_for_సంయుక్త (వృక్షం t1, వృక్షం t2);
స్థిర తార్కిక handle_counted_by_p (వృక్షం);
స్థిర తార్కిక శిఖరం_array_vla_p (const_వృక్షం type);


/* Return true if EXP is a null pointer constant, false otherwise.  */

తార్కిక
null_సూచిక_constant_p (const_వృక్షం సమాసం)
{
  /* This should really operate on c_expr structures, but they aren't
     yet available everywhere required.  */
  వృక్షం type = వృక్షం_TYPE (సమాసం);

  /* An integer constant expression with the value 0, such an expression
     cast to type void*, or the predefined constant nullptr, are a null
     pointer constant.  */
  ఒకవేళ (సమాసం == nullptr_కణుపు)
    తిరిగి నిజం;

  తిరిగి (వృక్షం_సంకేతం (సమాసం) == INTEGER_CST
	  && !వృక్షం_అధికప్రవాహం (సమాసం)
	  && integer_zerop (సమాసం)
	  && (INTEGRAL_TYPE_P (type)
	      || (వృక్షం_సంకేతం (type) == సూచిక_TYPE
		  && VOID_TYPE_P (వృక్షం_TYPE (type))
		  && TYPE_QUALS (వృక్షం_TYPE (type)) == TYPE_UNQUALIFIED)));
}

/* EXPR may appear in an unevaluated part of an integer constant
   expression, but not in an evaluated part.  Wrap it in a
   C_MAYBE_CONST_EXPR, or mark it with TREE_OVERFLOW if it is just an
   INTEGER_CST and we cannot create a C_MAYBE_CONST_EXPR.  */

స్థిర వృక్షం
note_integer_operands (వృక్షం సమాసం)
{
  వృక్షం ret;
  ఒకవేళ (వృక్షం_సంకేతం (సమాసం) == INTEGER_CST && లోపల_late_ద్విమాన_op)
    {
      ret = copy_కణుపు (సమాసం);
      వృక్షం_అధికప్రవాహం (ret) = 1;
    }
  లేకపోతే
    {
      ret = build2 (C_MAYBE_CONST_సమాసం, వృక్షం_TYPE (సమాసం), NULL_వృక్షం, సమాసం);
      C_MAYBE_CONST_సమాసం_INT_OPERANDS (ret) = 1;
    }
  తిరిగి ret;
}

/* Having checked whether EXPR may appear in an unevaluated part of an
   integer constant expression and found that it may, remove any
   C_MAYBE_CONST_EXPR noting this fact and return the resulting
   expression.  */

స్థిర అంతఃవరుస వృక్షం
remove_c_maybe_const_సమాసం (వృక్షం సమాసం)
{
  ఒకవేళ (వృక్షం_సంకేతం (సమాసం) == C_MAYBE_CONST_సమాసం)
    తిరిగి C_MAYBE_CONST_సమాసం_సమాసం (సమాసం);
  లేకపోతే
    తిరిగి సమాసం;
}

/* This is a cache to hold if two types are seen.  */

నిర్మాణం tagged_tu_చూసిన_cache {
  స్థిరరాశి నిర్మాణం tagged_tu_చూసిన_cache * తదుపరి;
  const_వృక్షం t1;
  const_వృక్షం t2;
};

/* Do `exp = require_complete_type (loc, exp);' to make sure exp
   does not have an incomplete type.  (That includes void types.)
   LOC is the location of the use.  */

వృక్షం
require_complete_type (location_t loc, వృక్షం విలువ)
{
  వృక్షం type = వృక్షం_TYPE (విలువ);

  ఒకవేళ (error_నిర్వాహ్యం_p (విలువ))
    తిరిగి error_mark_కణుపు;

  /* First, detect a valid value with a complete type.  */
  ఒకవేళ (COMPLETE_TYPE_P (type))
    తిరిగి విలువ;

  c_incomplete_type_error (loc, విలువ, type);
  తిరిగి error_mark_కణుపు;
}

/* Print an error message for invalid use of an incomplete type.
   VALUE is the expression that was used (or 0 if that isn't known)
   and TYPE is the type that was invalid.  LOC is the location for
   the error.  */

శూన్య
c_incomplete_type_error (location_t loc, const_వృక్షం విలువ, const_వృక్షం type)
{
  /* Avoid duplicate error message.  */
  ఒకవేళ (వృక్షం_సంకేతం (type) == ERROR_MARK)
    తిరిగి;

  ఒకవేళ (విలువ != NULL_వృక్షం && (VAR_P (విలువ) || వృక్షం_సంకేతం (విలువ) == PARM_DECL))
    error_at (loc, "%qD has an incomplete type %qT", విలువ, type);
  లేకపోతే
    {
    retry:
      /* We must print an error message.  Be clever about what it says.  */

      ఎంపిక (వృక్షం_సంకేతం (type))
	{
	స్థితి రికార్డు_TYPE:
	స్థితి UNION_TYPE:
	స్థితి ENUMERAL_TYPE:
	  ఆపు;

	స్థితి VOID_TYPE:
	  error_at (loc, "invalid use of void expression");
	  తిరిగి;

	స్థితి ARRAY_TYPE:
	  ఒకవేళ (TYPE_DOMAIN (type))
	    {
	      ఒకవేళ (flexible_array_member_type_p (type))
		{
		  error_at (loc, "invalid use of flexible array member");
		  తిరిగి;
		}
	      type = వృక్షం_TYPE (type);
	      వెళ్ళు retry;
	    }
	  error_at (loc, "invalid use of array with unspecified bounds");
	  తిరిగి;

	అప్రమేయ:
	  gcc_unreachable ();
	}

      ఒకవేళ (వృక్షం_సంకేతం (TYPE_NAME (type)) == IDENTIFIER_కణుపు)
	error_at (loc, "invalid use of undefined type %qT", type);
      లేకపోతే
	/* If this type has a typedef-name, the TYPE_NAME is a TYPE_DECL.  */
	error_at (loc, "invalid use of incomplete typedef %qT", type);
    }
}

/* Given a type, apply default promotions wrt unnamed function
   arguments and return the new type.  */

వృక్షం
c_type_promotes_గమ్యం (వృక్షం type)
{
  వృక్షం ret = NULL_వృక్షం;

  ఒకవేళ (TYPE_MAIN_VARIANT (type) == float_type_కణుపు)
    ret = double_type_కణుపు;
  లేకపోతే ఒకవేళ (c_promoting_integer_type_p (type))
    {
      /* Preserve unsignedness if not really getting any wider.  */
      ఒకవేళ (TYPE_UNSIGNED (type)
	  && (TYPE_PRECISION (type) == TYPE_PRECISION (integer_type_కణుపు)))
	ret = unsigned_type_కణుపు;
      లేకపోతే
	ret = integer_type_కణుపు;
    }

  ఒకవేళ (ret != NULL_వృక్షం)
    తిరిగి (TYPE_ATOMIC (type)
	    ? c_build_qualified_type (ret, TYPE_QUAL_ATOMIC)
	    : ret);

  తిరిగి type;
}

/* Return true if between two named address spaces, whether there is a superset
   named address space that encompasses both address spaces.  If there is a
   superset, return which address space is the superset.  */

స్థిర తార్కిక
addr_space_superset (addr_space_t as1, addr_space_t as2, addr_space_t *common)
{
  ఒకవేళ (as1 == as2)
    {
      *common = as1;
      తిరిగి నిజం;
    }
  లేకపోతే ఒకవేళ (targetm.addr_space.subset_p (as1, as2))
    {
      *common = as2;
      తిరిగి నిజం;
    }
  లేకపోతే ఒకవేళ (targetm.addr_space.subset_p (as2, as1))
    {
      *common = as1;
      తిరిగి నిజం;
    }
  లేకపోతే
    తిరిగి అబద్ధం;
}

/* Return a variant of TYPE which has all the type qualifiers of LIKE
   as well as those of TYPE.  */

స్థిర వృక్షం
qualify_type (వృక్షం type, వృక్షం like)
{
  addr_space_t as_type = TYPE_ADDR_SPACE (type);
  addr_space_t as_like = TYPE_ADDR_SPACE (like);
  addr_space_t as_common;

  /* If the two named address spaces are different, determine the common
     superset address space.  If there isn't one, raise an error.  */
  ఒకవేళ (!addr_space_superset (as_type, as_like, &as_common))
    {
      as_common = as_type;
      error ("%qT and %qT are in disjoint named address spaces",
	     type, like);
    }

  తిరిగి c_build_qualified_type (type,
				 TYPE_QUALS_NO_ADDR_SPACE (type)
				 | TYPE_QUALS_NO_ADDR_SPACE_NO_ATOMIC (like)
				 | ENCODE_QUAL_ADDR_SPACE (as_common));
}


/* Check consistency of type TYPE.  For derived types, we test that
   C_TYPE_VARIABLE_SIZE and C_TYPE_VARIABLY_MODIFIED are consistent with
   the requirements of the base type.  We also check that arrays with a
   non-constant length are marked with C_TYPE_VARIABLE_SIZE. If any
   inconsistency is detected false is returned and true otherwise.  */

స్థిర తార్కిక
c_verify_type (వృక్షం type)
{
  ఎంపిక (వృక్షం_సంకేతం (type))
    {
    స్థితి సూచిక_TYPE:
    స్థితి FUNCTION_TYPE:
    స్థితి ARRAY_TYPE:
      /* Pointer, array, functions are variably modified if and only if the
	 target, element, return type is variably modified.  */
      ఒకవేళ (!TYPE_STRUCTURAL_EQUALITY_P (type)
	  && (C_TYPE_VARIABLY_MODIFIED (type)
	      != C_TYPE_VARIABLY_MODIFIED (వృక్షం_TYPE (type))))
	తిరిగి అబద్ధం;
      /* If the target type is structural equality, the type should also. */
      ఒకవేళ (!TYPE_STRUCTURAL_EQUALITY_P (type)
	  && TYPE_STRUCTURAL_EQUALITY_P (వృక్షం_TYPE (type)))
	తిరిగి అబద్ధం;
    అప్రమేయ:
       ఆపు;
    }

  ఎంపిక (వృక్షం_సంకేతం (type))
    {
    స్థితి సూచిక_TYPE:
    స్థితి FUNCTION_TYPE:
      /* Pointer and functions can not have variable size.  */
      ఒకవేళ (C_TYPE_VARIABLE_కొలత (type))
	తిరిగి అబద్ధం;
      ఆపు;
    స్థితి ARRAY_TYPE:
      /* An array has variable size if and only if it has a non-constant
	 dimensions or its element type has variable size.  */
      ఒకవేళ ((C_TYPE_VARIABLE_కొలత (వృక్షం_TYPE (type))
	   || శిఖరం_array_vla_p (type))
	  != C_TYPE_VARIABLE_కొలత (type))
	తిరిగి అబద్ధం;
      /* If the element type or the array has variable size, then the
	 array has variable size and is variably modified.  */
      ఒకవేళ (C_TYPE_VARIABLE_కొలత (వృక్షం_TYPE (type))
	  || C_TYPE_VARIABLE_కొలత (type))
	{
	  ఒకవేళ (!C_TYPE_VARIABLE_కొలత (type))
	    తిరిగి అబద్ధం;
	  ఒకవేళ (!C_TYPE_VARIABLY_MODIFIED (type))
	    తిరిగి అబద్ధం;
	}

      /* va_list violates this, accept such types here.  */
      ఒకవేళ (!COMPLETE_TYPE_P (వృక్షం_TYPE (type)))
	తిరిగి నిజం;

      ఒకవేళ (COMPLETE_TYPE_P (type))
	{
	  /* If the size is unknown, it can not be complete.  */
	  ఒకవేళ (NULL_వృక్షం == TYPE_DOMAIN (type))
	    తిరిగి అబద్ధం;

	  /* Zero-length arrays must have size zero.  */
	  ఒకవేళ (zero_నిడివి_array_type_p (type)
	      && !integer_zerop (TYPE_కొలత (type)))
	    తిరిగి అబద్ధం;
	}
      లేకపోతే
	{
	  /* If not complete but has a domain, it must be a FAM.  */
	  ఒకవేళ (NULL_వృక్షం != TYPE_DOMAIN (type)
	      && !flexible_array_member_type_p (type))
	    తిరిగి అబద్ధం;
	}
    అప్రమేయ:
      ఆపు;
    }
  తిరిగి నిజం;
}

/* Propagate C_TYPE_VARIABLY_MODIFIED and C_TYPE_VARIABLE_SIZE
   from a base type to a newly built derived or qualified type.  */

స్థిర వృక్షం
c_సమితి_type_బిట్లు (వృక్షం new_type, వృక్షం old_type)
{
  gcc_checking_assert (c_verify_type (old_type));

  ఒకవేళ (c_type_variably_modified_p (old_type))
    C_TYPE_VARIABLY_MODIFIED (new_type) = నిజం;

  ఒకవేళ (వృక్షం_సంకేతం (new_type) == ARRAY_TYPE && C_TYPE_VARIABLE_కొలత (old_type))
    {
      C_TYPE_VARIABLY_MODIFIED (new_type) = నిజం;
      C_TYPE_VARIABLE_కొలత (new_type) = నిజం;
    }
  తిరిగి new_type;
}

/* Build a pointer type using the default pointer mode.  */

వృక్షం
c_build_సూచిక_type (వృక్షం గమ్యం_type)
{
  addr_space_t as = గమ్యం_type == error_mark_కణుపు ? ADDR_SPACE_GENERIC
					       : TYPE_ADDR_SPACE (గమ్యం_type);
  machine_బహుళకం సూచిక_బహుళకం;

  ఒకవేళ (as != ADDR_SPACE_GENERIC || c_default_సూచిక_బహుళకం == VOIDmode)
    సూచిక_బహుళకం = targetm.addr_space.సూచిక_బహుళకం (as);
  లేకపోతే
    సూచిక_బహుళకం = c_default_సూచిక_బహుళకం;

  తిరిగి c_build_సూచిక_type_for_బహుళకం (గమ్యం_type, సూచిక_బహుళకం, అబద్ధం);
}

/* Build a pointer type using the given mode.  */

వృక్షం
c_build_సూచిక_type_for_బహుళకం (వృక్షం type, machine_బహుళకం బహుళకం, తార్కిక m)
{
  వృక్షం ret = build_సూచిక_type_for_బహుళకం (type, బహుళకం, m);
  తిరిగి c_సమితి_type_బిట్లు (ret, type);
}

/* Build a function type.  */

వృక్షం
c_build_function_type (వృక్షం type, వృక్షం వాదనలు, తార్కిక no)
{
  వృక్షం ret = build_function_type (type, వాదనలు, no);
  తిరిగి c_సమితి_type_బిట్లు (ret, type);
}

/* Build an array type.  This sets typeless storage as required
   by C2Y and C_TYPE_VARIABLY_MODIFIED and C_TYPE_VARIABLE_SIZE
   based on the element type and domain.  */

వృక్షం
c_build_array_type (వృక్షం type, వృక్షం domain)
{
  పూర్ణాంకం type_quals = TYPE_QUALS (type);

  /* Identify typeless storage as introduced in C2Y
     and supported also in earlier language modes.  */
  తార్కిక typeless = (char_type_p (type) && !(type_quals & TYPE_QUAL_ATOMIC))
		  || (AGGREGATE_TYPE_P (type) && TYPE_TYPELESS_STORAGE (type));

  వృక్షం ret = build_array_type (type, domain, typeless);

  ఒకవేళ (శిఖరం_array_vla_p (ret))
    {
      C_TYPE_VARIABLE_కొలత (ret) = 1;
      C_TYPE_VARIABLY_MODIFIED (ret) = 1;
    }

  తిరిగి c_సమితి_type_బిట్లు (ret, type);
}

/* Build an array type of unspecified size.  */
వృక్షం
c_build_array_type_unspecified (వృక్షం type)
{
  వృక్షం పై = build2 (COMPOUND_సమాసం, వృక్షం_TYPE (కొలత_zero_కణుపు),
		       integer_zero_కణుపు, కొలత_zero_కణుపు);
  తిరిగి c_build_array_type (type, build_సూచీ_type (పై));
}

/* Build an array type of zero size.  */
వృక్షం
c_build_array_type_zero_కొలత (వృక్షం type)
{
  /* The GCC extension for zero-length arrays differs from
     ISO flexible array members in that sizeof yields
     zero.  */
  type = c_build_array_type (type, build_సూచీ_type (NULL_వృక్షం));
  type = build_distinct_type_copy (TYPE_MAIN_VARIANT (type));
  TYPE_కొలత (type) = bitsize_zero_కణుపు;
  TYPE_కొలత_UNIT (type) = కొలత_zero_కణుపు;
  సమితి_TYPE_STRUCTURAL_EQUALITY (type);
  తిరిగి type;
}

వృక్షం
c_build_type_attribute_qual_variant (వృక్షం type, వృక్షం attrs, పూర్ణాంకం quals)
{
  వృక్షం ret = build_type_attribute_qual_variant (type, attrs, quals);
  తిరిగి c_సమితి_type_బిట్లు (ret, type);
}

వృక్షం
c_build_type_attribute_variant (వృక్షం type, వృక్షం attrs)
{
  తిరిగి c_build_type_attribute_qual_variant (type, attrs, TYPE_QUALS (type));
}

/* Reconstruct a complex derived type.  This is used to re-construct types
   with the vector attribute.  It is called via a langhook.  */

వృక్షం
c_reconstruct_complex_type (వృక్షం type, వృక్షం bottom)
{
  వృక్షం inner, outer;

  ఒకవేళ (వృక్షం_సంకేతం (type) == సూచిక_TYPE)
    {
      inner = c_reconstruct_complex_type (వృక్షం_TYPE (type), bottom);
      outer = c_build_సూచిక_type_for_బహుళకం (inner, TYPE_బహుళకం (type),
					     TYPE_REF_CAN_ALIAS_ALL (type));
    }
  లేకపోతే ఒకవేళ (వృక్షం_సంకేతం (type) == ARRAY_TYPE)
    {
      తార్కిక rso = TYPE_తిరగేయి_STORAGE_క్రమం (type);
      inner = c_reconstruct_complex_type (వృక్షం_TYPE (type), bottom);
      outer = c_build_array_type (inner, TYPE_DOMAIN (type));
      ఒకవేళ (rso)
	{
	  outer = build_distinct_type_copy (outer);
	  TYPE_తిరగేయి_STORAGE_క్రమం (outer) = 1;
	}

      gcc_checking_assert (C_TYPE_VARIABLE_కొలత (type)
			   == C_TYPE_VARIABLE_కొలత (outer));
    }
  లేకపోతే ఒకవేళ (వృక్షం_సంకేతం (type) == FUNCTION_TYPE)
    {
      inner = c_reconstruct_complex_type (వృక్షం_TYPE (type), bottom);
      outer = c_build_function_type (inner, TYPE_ARG_TYPES (type),
				     TYPE_NO_NAMED_వాదనలు_STDARG_P (type));
    }
  లేకపోతే ఒకవేళ (వృక్షం_సంకేతం (type) == REFERENCE_TYPE
	   || వృక్షం_సంకేతం (type) == స్థానభ్రంశం_TYPE)
    gcc_unreachable ();
  లేకపోతే
    తిరిగి bottom;

  తిరిగి c_build_type_attribute_qual_variant (outer, TYPE_లక్షణాలు (type),
					      TYPE_QUALS (type));
}


/* Helper function for c_canonical_type.  Check whether FIELD
   contains a pointer to a structure or union with tag,
   possibly nested in other type derivations, and return the
   type of this nested structure or union.  */
స్థిర వృక్షం
ptr_గమ్యం_tagged_member (వృక్షం క్షేత్రం_2)
{
  gcc_assert (క్షేత్రం_DECL == వృక్షం_సంకేతం (క్షేత్రం_2));
  వృక్షం type = వృక్షం_TYPE (క్షేత్రం_2);
  తార్కిక ptr_చూసిన = అబద్ధం;
  అయితే (వృక్షం_సంకేతం (type) == ARRAY_TYPE
	 || వృక్షం_సంకేతం (type) == FUNCTION_TYPE
	 || వృక్షం_సంకేతం (type) == సూచిక_TYPE)
    {
      ఒకవేళ (వృక్షం_సంకేతం (type) == సూచిక_TYPE)
	ptr_చూసిన = నిజం;
      type = వృక్షం_TYPE (type);
    }

  ఒకవేళ (ptr_చూసిన
      && రికార్డు_OR_UNION_TYPE_P (type)
      && NULL_వృక్షం != c_type_ట్యాగ్ (type))
    తిరిగి type;

  తిరిగి NULL_వృక్షం;
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
వృక్షం
c_type_canonical (వృక్షం type)
{
  gcc_assert (రికార్డు_OR_UNION_TYPE_P (type));

  తార్కిక needs_mod = అబద్ధం;
  కొరకు (వృక్షం x = TYPE_FIELDS (type); x; x = DECL_CHAIN (x))
    {
      ఒకవేళ (!ptr_గమ్యం_tagged_member (x))
	కొనసాగు;
      needs_mod = నిజం;
      ఆపు;
    }
  ఒకవేళ (!needs_mod)
    తిరిగి type;

  /* Construct new version with such members replaced.  */
  వృక్షం n = build_distinct_type_copy (type);
  వృక్షం *fields = &TYPE_FIELDS (n);
  కొరకు (వృక్షం x = TYPE_FIELDS (type); x; x = DECL_CHAIN (x))
    {
      వృక్షం f = copy_కణుపు (x);
      ఒకవేళ (వృక్షం m = ptr_గమ్యం_tagged_member (x))
	{
	  వృక్షం new_కణుపు = make_కణుపు (వృక్షం_సంకేతం (m));
	  TYPE_NAME (new_కణుపు) = TYPE_NAME (m);
	  సమితి_TYPE_STRUCTURAL_EQUALITY (new_కణుపు);
	  new_కణుపు = qualify_type (new_కణుపు, m);
	  వృక్షం_TYPE (f) = c_reconstruct_complex_type (వృక్షం_TYPE (x),
						      new_కణుపు);
	}
      *fields = f;
      fields = &DECL_CHAIN (f);
    }
  TYPE_CANONICAL (n) = n;
  తిరిగి n;
}


/* If NTYPE is a type of a non-variadic function with a prototype
   and OTYPE is a type of a function without a prototype and ATTRS
   contains attribute format, diagnosess and removes it from ATTRS.
   Returns the result of build_type_attribute_variant of NTYPE and
   the (possibly) modified ATTRS.  */

స్థిర వృక్షం
c_build_functype_attribute_variant (వృక్షం ntype, వృక్షం otype, వృక్షం attrs)
{
  ఒకవేళ (!prototype_p (otype)
      && prototype_p (ntype)
      && lookup_attribute ("format", attrs))
    {
      warning_at (ఆదానం_location, OPT_Wattributes,
		  "%qs attribute can only be applied to variadic functions",
		  "format");
      attrs = remove_attribute ("format", attrs);
    }
  తిరిగి c_build_type_attribute_variant (ntype, attrs);

}

/* Given a type which could be a typedef name, make sure to return the
   original type.  See set_underlying_type. */
స్థిర const_వృక్షం
c_type_original (const_వృక్షం t)
{
  /* It may even be a typedef of a typedef...
     In the case of compiler-created builtin structs the TYPE_DECL
     may be a dummy, with no DECL_ORIGINAL_TYPE.  Don't fault.  */
  అయితే (TYPE_NAME (t)
	 && వృక్షం_సంకేతం (TYPE_NAME (t)) == TYPE_DECL
	 && DECL_ORIGINAL_TYPE (TYPE_NAME (t)))
    t = DECL_ORIGINAL_TYPE (TYPE_NAME (t));
  తిరిగి t;
}

/* Return the tag for a tagged type.  */
వృక్షం
c_type_ట్యాగ్ (const_వృక్షం t)
{
  gcc_assert (రికార్డు_OR_UNION_TYPE_P (t) || వృక్షం_సంకేతం (t) == ENUMERAL_TYPE);
  const_వృక్షం orig = c_type_original (t);
  వృక్షం name = TYPE_NAME (orig);
  ఒకవేళ (!name)
    తిరిగి NULL_వృక్షం;
  ఒకవేళ (వృక్షం_సంకేతం (name) == TYPE_DECL)
    {
      ఒకవేళ (!DECL_NAME (name))
	తిరిగి NULL_వృక్షం;
      name = DECL_NAME (name);
    }
  gcc_checking_assert (వృక్షం_సంకేతం (name) == IDENTIFIER_కణుపు);
  తిరిగి name;
}

/* Remove qualifiers but not atomic.  For arrays remove qualifiers
   on the element type but also do not remove atomic.  */
స్థిర వృక్షం
remove_qualifiers (వృక్షం t)
{
  ఒకవేళ (!t || t == error_mark_కణుపు)
    తిరిగి t;
  తిరిగి TYPE_ATOMIC (strip_array_types (t))
	 ? c_build_qualified_type (TYPE_MAIN_VARIANT (t), TYPE_QUAL_ATOMIC)
	 : TYPE_MAIN_VARIANT (t);
}


/* Helper function for composite_type_internal.  Find a compatible type
   in a (transparent) union U compatible to T.  If found, return the
   type of the corresponding member.  Otherwise, return the union type U.  */
స్థిర వృక్షం
transparent_union_replacement (వృక్షం u, వృక్షం t)
{
  ఒకవేళ (u == error_mark_కణుపు || t == error_mark_కణుపు
      || వృక్షం_సంకేతం (u) != UNION_TYPE
      || !(TYPE_TRANSPARENT_AGGR (u) || TYPE_NAME (u) == NULL_వృక్షం)
      || comptypes (u, t))
    తిరిగి u;

  కొరకు (వృక్షం memb = TYPE_FIELDS (u); memb; memb = DECL_CHAIN (memb))
    {
      వృక్షం m = remove_qualifiers (వృక్షం_TYPE (memb));
      ఒకవేళ (comptypes (m, t))
	{
	  pedwarn (ఆదానం_location, OPT_Wpedantic,
		    "function types not truly compatible in ISO C");
	  తిరిగి m;
	}
    }

  తిరిగి u;
}



/* Return the composite type of two compatible types.

   We assume that comptypes has already been done and returned
   nonzero; if that isn't so, this may crash.  In particular, we
   assume that qualifiers match.  */

నిర్మాణం సంయుక్త_cache {
  వృక్షం t1;
  వృక్షం t2;
  వృక్షం సంయుక్త;
  నిర్మాణం సంయుక్త_cache* తదుపరి;
};

వృక్షం
సంయుక్త_type_అంతర్గత (వృక్షం t1, వృక్షం t2, వృక్షం cond,
			 నిర్మాణం సంయుక్త_cache* cache)
{
  గణన వృక్షం_సంకేతం_2 code1;
  గణన వృక్షం_సంకేతం_2 code2;
  వృక్షం లక్షణాలు;

  /* Save time if the two types are the same.  */

  ఒకవేళ (t1 == t2) తిరిగి t1;

  /* If one type is nonsense, use the other.  */
  ఒకవేళ (t1 == error_mark_కణుపు)
    తిరిగి t2;
  ఒకవేళ (t2 == error_mark_కణుపు)
    తిరిగి t1;

  code1 = వృక్షం_సంకేతం (t1);
  code2 = వృక్షం_సంకేతం (t2);

  /* Merge the attributes.  */
  లక్షణాలు = targetm.విలీనం_type_లక్షణాలు (t1, t2);

  /* If one is an enumerated type and the other is the compatible
     integer type, the composite type might be either of the two
     (DR#013 question 3).  For consistency, use the enumerated type as
     the composite type.  */

  ఒకవేళ (code1 == ENUMERAL_TYPE
      && (code2 == INTEGER_TYPE
	  || code2 == BOOLEAN_TYPE))
    తిరిగి t1;
  ఒకవేళ (code2 == ENUMERAL_TYPE
      && (code1 == INTEGER_TYPE
	  || code1 == BOOLEAN_TYPE))
    తిరిగి t2;

  gcc_assert (code1 == code2);

  ఎంపిక (code1)
    {
    స్థితి సూచిక_TYPE:
      /* For two pointers, do this recursively on the target type.  */
      {
	gcc_checking_assert (TYPE_QUALS (t1) == TYPE_QUALS (t2));
	వృక్షం లక్ష్యం = సంయుక్త_type_అంతర్గత (వృక్షం_TYPE (t1), వృక్షం_TYPE (t2),
					       cond, cache);
	వృక్షం n = c_build_సూచిక_type_for_బహుళకం (లక్ష్యం, TYPE_బహుళకం (t1), అబద్ధం);
	తిరిగి c_build_type_attribute_qual_variant (n, లక్షణాలు,
						    TYPE_QUALS (t2));
      }

    స్థితి ARRAY_TYPE:
      {
	వృక్షం d1 = TYPE_DOMAIN (t1);
	వృక్షం d2 = TYPE_DOMAIN (t2);

	/* We should not have any type quals on arrays at all.  */
	gcc_assert (!TYPE_QUALS_NO_ADDR_SPACE (t1)
		    && !TYPE_QUALS_NO_ADDR_SPACE (t2));

	తార్కిక d1_zero = zero_నిడివి_array_type_p (t1)
		       || flexible_array_member_type_p (t1);
	తార్కిక d2_zero = zero_నిడివి_array_type_p (t2)
		       || flexible_array_member_type_p (t2);

	తార్కిక d1_variable = శిఖరం_array_vla_p (t1);
	తార్కిక d2_variable = శిఖరం_array_vla_p (t2);

	తార్కిక use1 = d1 && (d2_variable || !d2 || d2_zero || !d1_variable);
	తార్కిక use2 = d2 && (d1_variable || !d1 || d1_zero || !d2_variable);

	/* If the first is an unspecified size pick the other one.  */
	ఒకవేళ (d2_variable && c_type_unspecified_p (t1))
	  {
	    gcc_assert (use1 && use2);
	    use1 = అబద్ధం;
	  }

	/* If both are VLAs but not unspecified and we are in the
	   conditional operator, we create a conditional to select
	   the size of the active branch.  */
	తార్కిక use0 = cond && d1_variable && !c_type_unspecified_p (t1)
			 && d2_variable && !c_type_unspecified_p (t2);

	వృక్షం td;
	వృక్షం elt = సంయుక్త_type_అంతర్గత (వృక్షం_TYPE (t1), వృక్షం_TYPE (t2),
					    cond, cache);

	ఒకవేళ (!use0)
	  {
	    /* Save space: see if the result is identical to one of the args.  */
	    ఒకవేళ (elt == వృక్షం_TYPE (t1) && use1)
	      తిరిగి c_build_type_attribute_variant (t1, లక్షణాలు);
	    ఒకవేళ (elt == వృక్షం_TYPE (t2) && use2)
	      తిరిగి c_build_type_attribute_variant (t2, లక్షణాలు);

	    ఒకవేళ (elt == వృక్షం_TYPE (t1) && !TYPE_DOMAIN (t2) && !TYPE_DOMAIN (t1))
	      తిరిగి c_build_type_attribute_variant (t1, లక్షణాలు);
	    ఒకవేళ (elt == వృక్షం_TYPE (t2) && !TYPE_DOMAIN (t2) && !TYPE_DOMAIN (t1))
	      తిరిగి c_build_type_attribute_variant (t2, లక్షణాలు);

	    td = TYPE_DOMAIN (use1 ? t1 : t2);
	  }
	లేకపోతే
	  {
	    /* Not used in C.  */
	    gcc_assert (కొలత_zero_కణుపు == TYPE_MIN_విలువ (d1));
	    gcc_assert (కొలత_zero_కణుపు == TYPE_MIN_విలువ (d2));

	    వృక్షం d = fold_build3_loc (UNKNOWN_LOCATION, COND_సమాసం, sizetype,
				      cond, TYPE_MAX_విలువ (d1),
				      TYPE_MAX_విలువ (d2));

	    td = build_సూచీ_type (d);
	  }

	/* Merge the element types, and have a size if either arg has
	   one.  We may have qualifiers on the element types.  To set
	   up TYPE_MAIN_VARIANT correctly, we need to form the
	   composite of the unqualified types and add the qualifiers
	   back at the end.  */
	పూర్ణాంకం quals = TYPE_QUALS (strip_array_types (elt));
	వృక్షం unqual_elt = c_build_qualified_type (elt, TYPE_UNQUALIFIED);

	ఒకవేళ ((!d1 || d1_zero) && (!d2 || d2_zero) && (d1 || d2))
	  t1 = c_build_array_type_zero_కొలత (unqual_elt);
	లేకపోతే
	  t1 = c_build_array_type (unqual_elt, td);

	/* Check that a type which has a varying outermost dimension
	   got marked as having a variable size.  */
	తార్కిక varsize = (d1_variable && d2_variable)
		       || (d1_variable && !d2)
		       || (d2_variable && !d1);
	gcc_checking_assert (!varsize || C_TYPE_VARIABLE_కొలత (t1));

	t1 = c_build_qualified_type (t1, quals);
	తిరిగి c_build_type_attribute_variant (t1, లక్షణాలు);
      }

    స్థితి రికార్డు_TYPE:
    స్థితి UNION_TYPE:
      ఒకవేళ (flag_isoc23 && !comptypes_same_p (t1, t2))
	{
	  /* Go to the original type to get the right tag.  */
	  వృక్షం ట్యాగ్ = c_type_ట్యాగ్ (t1);

	  gcc_checking_assert (COMPLETE_TYPE_P (t1) && COMPLETE_TYPE_P (t2));
	  gcc_checking_assert (!ట్యాగ్ || comptypes (t1, t2));

	  /* If a composite type for these two types is already under
	     construction, return it.  */

	  కొరకు (నిర్మాణం సంయుక్త_cache *c = cache; c != ఖాళీ; c = c->తదుపరి)
	    ఒకవేళ ((c->t1 == t1 && c->t2 == t2) || (c->t1 == t2 && c->t2 == t1))
	       తిరిగి c->సంయుక్త;

	  /* Otherwise, create a new type node and link it into the cache.  */

	  వృక్షం n = make_కణుపు (code1);
	  సమితి_TYPE_STRUCTURAL_EQUALITY (n);
	  TYPE_NAME (n) = ట్యాగ్;

	  నిర్మాణం సంయుక్త_cache cache2 = { t1, t2, n, cache };
	  cache = &cache2;

	  వృక్షం f1 = TYPE_FIELDS (t1);
	  వృక్షం f2 = TYPE_FIELDS (t2);
	  వృక్షం fields = NULL_వృక్షం;

	  కొరకు (వృక్షం a = f1, b = f2; a && b;
	       a = DECL_CHAIN (a), b = DECL_CHAIN (b))
	    {
	      వృక్షం ta = వృక్షం_TYPE (a);
	      వృక్షం tb = వృక్షం_TYPE (b);

	      ఒకవేళ (DECL_C_బిట్టు_క్షేత్రం (a))
		{
		  ta = DECL_బిట్టు_క్షేత్రం_TYPE (a);
		  tb = DECL_బిట్టు_క్షేత్రం_TYPE (b);
		}

	      gcc_assert (DECL_NAME (a) == DECL_NAME (b));
	      gcc_checking_assert (!DECL_NAME (a) || comptypes (ta, tb));

	      వృక్షం t = సంయుక్త_type_అంతర్గత (ta, tb, cond, cache);
	      వృక్షం f = build_decl (ఆదానం_location, క్షేత్రం_DECL, DECL_NAME (a), t);

	      DECL_PACKED (f) = DECL_PACKED (a);
	      సమితి_DECL_ALIGN (f, DECL_ALIGN (a));
	      DECL_లక్షణాలు (f) = DECL_లక్షణాలు (a);
	      C_DECL_VARIABLE_కొలత (f) = C_TYPE_VARIABLE_కొలత (t);

	      decl_లక్షణాలు (&f, DECL_లక్షణాలు (f), 0);

	      ముగింపు_decl (f, ఆదానం_location, ఖాళీ, ఖాళీ, ఖాళీ);

	      ఒకవేళ (DECL_C_బిట్టు_క్షేత్రం (a))
		{
		  /* This will be processed by finish_struct.  */
		  సమితి_DECL_C_బిట్టు_క్షేత్రం (f);
		  DECL_INITIAL (f) = build_int_cst (integer_type_కణుపు,
						    వృక్షం_గమ్యం_uhwi (DECL_కొలత (a)));
		  DECL_NONADDRESSABLE_P (f) = నిజం;
		  DECL_PADDING_P (f) = !DECL_NAME (a);
		}

	      DECL_CHAIN (f) = fields;
	      fields = f;
	    }

	  fields = nreverse (fields);

	  /* Setup the struct/union type.  Because we inherit all variably
	     modified components, we can ignore the size expression.  */
	  వృక్షం సమాసం = NULL_వృక్షం;

	  /* Set TYPE_STUB_DECL for debugging symbols.  */
	  TYPE_STUB_DECL (n) = pushdecl (build_decl (ఆదానం_location, TYPE_DECL,
						     NULL_వృక్షం, n));

	  n = ముగింపు_struct (ఆదానం_location, n, fields, లక్షణాలు, ఖాళీ,
			     &సమాసం);

	  తిరిగి qualify_type (n, t1);
	}
      /* FALLTHRU */
    స్థితి ENUMERAL_TYPE:
      ఒకవేళ (లక్షణాలు != ఖాళీ)
	{
	  /* Try harder not to create a new aggregate type.  */
	  ఒకవేళ (attribute_list_equal (TYPE_లక్షణాలు (t1), లక్షణాలు))
	    తిరిగి t1;
	  ఒకవేళ (attribute_list_equal (TYPE_లక్షణాలు (t2), లక్షణాలు))
	    తిరిగి t2;
	}
      తిరిగి c_build_type_attribute_variant (t1, లక్షణాలు);

    స్థితి FUNCTION_TYPE:
      /* Function types: prefer the one that specified arg types.
	 If both do, merge the arg types.  Also merge the return types.  */
      {
	వృక్షం valtype = సంయుక్త_type_అంతర్గత (వృక్షం_TYPE (t1), వృక్షం_TYPE (t2),
						cond, cache);
	వృక్షం p1 = TYPE_ARG_TYPES (t1);
	వృక్షం p2 = TYPE_ARG_TYPES (t2);

	/* Save space: see if the result is identical to one of the args.  */
	ఒకవేళ (valtype == వృక్షం_TYPE (t1) && !TYPE_ARG_TYPES (t2))
	  తిరిగి c_build_functype_attribute_variant (t1, t2, లక్షణాలు);
	ఒకవేళ (valtype == వృక్షం_TYPE (t2) && !TYPE_ARG_TYPES (t1))
	  తిరిగి c_build_functype_attribute_variant (t2, t1, లక్షణాలు);

	/* Simple way if one arg fails to specify argument types.  */
	ఒకవేళ (TYPE_ARG_TYPES (t1) == NULL_వృక్షం)
	  {
	    t1 = c_build_function_type (valtype, TYPE_ARG_TYPES (t2),
					TYPE_NO_NAMED_వాదనలు_STDARG_P (t2));
	    t1 = c_build_type_attribute_variant (t1, లక్షణాలు);
	    తిరిగి qualify_type (t1, t2);
	 }
	ఒకవేళ (TYPE_ARG_TYPES (t2) == NULL_వృక్షం)
	  {
	    t1 = c_build_function_type (valtype, TYPE_ARG_TYPES (t1),
					TYPE_NO_NAMED_వాదనలు_STDARG_P (t1));
	    t1 = c_build_type_attribute_variant (t1, లక్షణాలు);
	    తిరిగి qualify_type (t1, t2);
	  }

	/* If both args specify argument types, we must merge the two
	   lists, argument by argument.  */
	వృక్షం newargs = NULL_వృక్షం;
	వృక్షం *endp = &newargs;

	కొరకు (; p1; p1 = వృక్షం_CHAIN (p1), p2 = వృక్షం_CHAIN (p2))
	  {
	    ఒకవేళ (p1 == void_list_కణుపు)
	      {
		*endp = void_list_కణుపు;
		ఆపు;
	      }
	    వృక్షం mv1 = remove_qualifiers (వృక్షం_విలువ (p1));
	    వృక్షం mv2 = remove_qualifiers (వృక్షం_విలువ (p2));

	    gcc_assert (mv1);
	    gcc_assert (mv2);

	    mv1 = transparent_union_replacement (mv1, mv2);
	    mv2 = transparent_union_replacement (mv2, mv1);

	    *endp = వృక్షం_cons (NULL_వృక్షం,
			       సంయుక్త_type_అంతర్గత (mv1, mv2, cond, cache),
			       NULL_వృక్షం);

	    endp = &వృక్షం_CHAIN (*endp);
	  }

	t1 = c_build_function_type (valtype, newargs);
	t1 = qualify_type (t1, t2);
      }
      /* FALLTHRU */

    అప్రమేయ:
      తిరిగి c_build_type_attribute_variant (t1, లక్షణాలు);
    }
}

వృక్షం
సంయుక్త_type_cond (వృక్షం t1, వృక్షం t2, వృక్షం cond)
{
  gcc_checking_assert (comptypes_check_for_సంయుక్త (t1, t2));

  నిర్మాణం సంయుక్త_cache cache = { };
  వృక్షం n = సంయుక్త_type_అంతర్గత (t1, t2, cond, &cache);

  gcc_checking_assert (comptypes_check_for_సంయుక్త (n, t1));
  gcc_checking_assert (comptypes_check_for_సంయుక్త (n, t2));
  తిరిగి n;
}


వృక్షం
సంయుక్త_type (వృక్షం t1, వృక్షం t2)
{
  తిరిగి సంయుక్త_type_cond (t1, t2, NULL_వృక్షం);
}

/* Return the type of a conditional expression between pointers to
   possibly differently qualified versions of compatible types.

   We assume that comp_target_types has already been done and returned
   true; if that isn't so, this may crash.  */

స్థిర వృక్షం
common_సూచిక_type (వృక్షం t1, వృక్షం t2, వృక్షం cond)
{
  వృక్షం లక్షణాలు;
  గుర్తులేని లక్ష్యం_quals;
  addr_space_t as1, as2, as_common;
  పూర్ణాంకం quals1, quals2;

  /* Save time if the two types are the same.  */

  ఒకవేళ (t1 == t2) తిరిగి t1;

  /* If one type is nonsense, use the other.  */
  ఒకవేళ (t1 == error_mark_కణుపు)
    తిరిగి t2;
  ఒకవేళ (t2 == error_mark_కణుపు)
    తిరిగి t1;

  gcc_assert (వృక్షం_సంకేతం (t1) == సూచిక_TYPE
	      && వృక్షం_సంకేతం (t2) == సూచిక_TYPE);

  /* Merge the attributes.  */
  లక్షణాలు = targetm.విలీనం_type_లక్షణాలు (t1, t2);

  /* Find the composite type of the target types, and combine the
     qualifiers of the two types' targets.  */
  వృక్షం pointed_గమ్యం_1 = వృక్షం_TYPE (t1);
  వృక్షం pointed_గమ్యం_2 = వృక్షం_TYPE (t2);
  వృక్షం లక్ష్యం = సంయుక్త_type_cond (TYPE_MAIN_VARIANT (pointed_గమ్యం_1),
				     TYPE_MAIN_VARIANT (pointed_గమ్యం_2), cond);

  /* Strip array types to get correct qualifier for pointers to arrays */
  quals1 = TYPE_QUALS_NO_ADDR_SPACE (strip_array_types (pointed_గమ్యం_1));
  quals2 = TYPE_QUALS_NO_ADDR_SPACE (strip_array_types (pointed_గమ్యం_2));

  /* For function types do not merge const qualifiers, but drop them
     if used inconsistently.  The middle-end uses these to mark const
     and noreturn functions.  */
  ఒకవేళ (వృక్షం_సంకేతం (pointed_గమ్యం_1) == FUNCTION_TYPE)
    లక్ష్యం_quals = (quals1 & quals2);
  లేకపోతే
    లక్ష్యం_quals = (quals1 | quals2);

  /* If the two named address spaces are different, determine the common
     superset address space.  This is guaranteed to exist due to the
     assumption that comp_target_type returned true.  */
  as1 = TYPE_ADDR_SPACE (pointed_గమ్యం_1);
  as2 = TYPE_ADDR_SPACE (pointed_గమ్యం_2);
  ఒకవేళ (!addr_space_superset (as1, as2, &as_common))
    gcc_unreachable ();

  లక్ష్యం_quals |= ENCODE_QUAL_ADDR_SPACE (as_common);

  t1 = c_build_సూచిక_type (c_build_qualified_type (లక్ష్యం, లక్ష్యం_quals));
  తిరిగి c_build_type_attribute_variant (t1, లక్షణాలు);
}

/* Return the common type for two arithmetic types under the usual
   arithmetic conversions.  The default conversions have already been
   applied, and enumerated types converted to their compatible integer
   types.  The resulting type is unqualified and has no attributes.

   This is the type for the result of most arithmetic operations
   if the operands have the given two types.  */

స్థిర వృక్షం
c_common_type (వృక్షం t1, వృక్షం t2)
{
  గణన వృక్షం_సంకేతం_2 code1;
  గణన వృక్షం_సంకేతం_2 code2;

  /* If one type is nonsense, use the other.  */
  ఒకవేళ (t1 == error_mark_కణుపు)
    తిరిగి t2;
  ఒకవేళ (t2 == error_mark_కణుపు)
    తిరిగి t1;

  ఒకవేళ (TYPE_QUALS (t1) != TYPE_UNQUALIFIED)
    t1 = TYPE_MAIN_VARIANT (t1);

  ఒకవేళ (TYPE_QUALS (t2) != TYPE_UNQUALIFIED)
    t2 = TYPE_MAIN_VARIANT (t2);

  ఒకవేళ (TYPE_లక్షణాలు (t1) != NULL_వృక్షం)
    {
      వృక్షం attrs = affects_type_తటస్థం_లక్షణాలు (TYPE_లక్షణాలు (t1));
      t1 = c_build_type_attribute_variant (t1, attrs);
    }

  ఒకవేళ (TYPE_లక్షణాలు (t2) != NULL_వృక్షం)
    {
      వృక్షం attrs = affects_type_తటస్థం_లక్షణాలు (TYPE_లక్షణాలు (t2));
      t2 = c_build_type_attribute_variant (t2, attrs);
    }

  /* Save time if the two types are the same.  */

  ఒకవేళ (t1 == t2) తిరిగి t1;

  code1 = వృక్షం_సంకేతం (t1);
  code2 = వృక్షం_సంకేతం (t2);

  gcc_assert (code1 == సదిశ_TYPE || code1 == COMPLEX_TYPE
	      || code1 == FIXED_బిందువు_TYPE || code1 == REAL_TYPE
	      || code1 == INTEGER_TYPE || code1 == BITINT_TYPE);
  gcc_assert (code2 == సదిశ_TYPE || code2 == COMPLEX_TYPE
	      || code2 == FIXED_బిందువు_TYPE || code2 == REAL_TYPE
	      || code2 == INTEGER_TYPE || code2 == BITINT_TYPE);

  /* When one operand is a decimal float type, the other operand cannot be
     a generic float type or a complex type.  We also disallow vector types
     here.  */
  ఒకవేళ ((DECIMAL_FLOAT_TYPE_P (t1) || DECIMAL_FLOAT_TYPE_P (t2))
      && !(DECIMAL_FLOAT_TYPE_P (t1) && DECIMAL_FLOAT_TYPE_P (t2)))
    {
      ఒకవేళ (code1 == సదిశ_TYPE || code2 == సదిశ_TYPE)
	{
	  error ("cannot mix operands of decimal floating and vector types");
	  తిరిగి error_mark_కణుపు;
	}
      ఒకవేళ (code1 == COMPLEX_TYPE || code2 == COMPLEX_TYPE)
	{
	  error ("cannot mix operands of decimal floating and complex types");
	  తిరిగి error_mark_కణుపు;
	}
      ఒకవేళ (code1 == REAL_TYPE && code2 == REAL_TYPE)
	{
	  error ("cannot mix operands of decimal floating "
		 "and other floating types");
	  తిరిగి error_mark_కణుపు;
	}
    }

  /* If one type is a vector type, return that type.  (How the usual
     arithmetic conversions apply to the vector types extension is not
     precisely specified.)  */
  ఒకవేళ (code1 == సదిశ_TYPE)
    తిరిగి t1;

  ఒకవేళ (code2 == సదిశ_TYPE)
    తిరిగి t2;

  /* If one type is complex, form the common type of the non-complex
     components, then make that complex.  Use T1 or T2 if it is the
     required type.  */
  ఒకవేళ (code1 == COMPLEX_TYPE || code2 == COMPLEX_TYPE)
    {
      వృక్షం subtype1 = code1 == COMPLEX_TYPE ? వృక్షం_TYPE (t1) : t1;
      వృక్షం subtype2 = code2 == COMPLEX_TYPE ? వృక్షం_TYPE (t2) : t2;
      వృక్షం subtype = c_common_type (subtype1, subtype2);

      ఒకవేళ (code1 == COMPLEX_TYPE && వృక్షం_TYPE (t1) == subtype)
	తిరిగి t1;
      లేకపోతే ఒకవేళ (code2 == COMPLEX_TYPE && వృక్షం_TYPE (t2) == subtype)
	తిరిగి t2;
      లేకపోతే ఒకవేళ (వృక్షం_సంకేతం (subtype) == BITINT_TYPE)
	{
	  sorry ("%<_Complex _BitInt(%d)%> unsupported",
		 TYPE_PRECISION (subtype));
	  తిరిగి code1 == COMPLEX_TYPE ? t1 : t2;
	}
      లేకపోతే
	తిరిగి build_complex_type (subtype);
    }

  /* If only one is real, use it as the result.  */

  ఒకవేళ (code1 == REAL_TYPE && code2 != REAL_TYPE)
    తిరిగి t1;

  ఒకవేళ (code2 == REAL_TYPE && code1 != REAL_TYPE)
    తిరిగి t2;

  /* If both are real and either are decimal floating point types, use
     the decimal floating point type with the greater precision. */

  ఒకవేళ (code1 == REAL_TYPE && code2 == REAL_TYPE)
    {
      ఒకవేళ (TYPE_MAIN_VARIANT (t1) == dfloat128_type_కణుపు
	  || TYPE_MAIN_VARIANT (t2) == dfloat128_type_కణుపు)
	తిరిగి dfloat128_type_కణుపు;
      /* And prefer _Decimal128 over _Decimal64x which has in GCC's
	 implementation the same mode.  */
      లేకపోతే ఒకవేళ (TYPE_MAIN_VARIANT (t1) == dfloat64x_type_కణుపు
	       || TYPE_MAIN_VARIANT (t2) == dfloat64x_type_కణుపు)
	తిరిగి dfloat64x_type_కణుపు;
      లేకపోతే ఒకవేళ (TYPE_MAIN_VARIANT (t1) == dfloat64_type_కణుపు
	       || TYPE_MAIN_VARIANT (t2) == dfloat64_type_కణుపు)
	తిరిగి dfloat64_type_కణుపు;
      లేకపోతే ఒకవేళ (TYPE_MAIN_VARIANT (t1) == dfloat32_type_కణుపు
	       || TYPE_MAIN_VARIANT (t2) == dfloat32_type_కణుపు)
	తిరిగి dfloat32_type_కణుపు;
    }

  /* Deal with fixed-point types.  */
  ఒకవేళ (code1 == FIXED_బిందువు_TYPE || code2 == FIXED_బిందువు_TYPE)
    {
      గుర్తులేని పూర్ణాంకం unsignedp = 0, satp = 0;
      scalar_బహుళకం m1, m2;
      గుర్తులేని పూర్ణాంకం fbit1, ibit1, fbit2, ibit2, max_fbit, max_ibit;

      m1 = SCALAR_TYPE_బహుళకం (t1);
      m2 = SCALAR_TYPE_బహుళకం (t2);

      /* If one input type is saturating, the result type is saturating.  */
      ఒకవేళ (TYPE_SATURATING (t1) || TYPE_SATURATING (t2))
	satp = 1;

      /* If both fixed-point types are unsigned, the result type is unsigned.
	 When mixing fixed-point and integer types, follow the sign of the
	 fixed-point type.
	 Otherwise, the result type is signed.  */
      ఒకవేళ ((TYPE_UNSIGNED (t1) && TYPE_UNSIGNED (t2)
	   && code1 == FIXED_బిందువు_TYPE && code2 == FIXED_బిందువు_TYPE)
	  || (code1 == FIXED_బిందువు_TYPE && code2 != FIXED_బిందువు_TYPE
	      && TYPE_UNSIGNED (t1))
	  || (code1 != FIXED_బిందువు_TYPE && code2 == FIXED_బిందువు_TYPE
	      && TYPE_UNSIGNED (t2)))
	unsignedp = 1;

      /* The result type is signed.  */
      ఒకవేళ (unsignedp == 0)
	{
	  /* If the input type is unsigned, we need to convert to the
	     signed type.  */
	  ఒకవేళ (code1 == FIXED_బిందువు_TYPE && TYPE_UNSIGNED (t1))
	    {
	      గణన బహుళకం_class mclass = (గణన బహుళకం_class) 0;
	      ఒకవేళ (GET_బహుళకం_CLASS (m1) == బహుళకం_UFRACT)
		mclass = బహుళకం_FRACT;
	      లేకపోతే ఒకవేళ (GET_బహుళకం_CLASS (m1) == బహుళకం_UACCUM)
		mclass = బహుళకం_ACCUM;
	      లేకపోతే
		gcc_unreachable ();
	      m1 = as_a <scalar_బహుళకం>
		(బహుళకం_for_కొలత (GET_బహుళకం_PRECISION (m1), mclass, 0));
	    }
	  ఒకవేళ (code2 == FIXED_బిందువు_TYPE && TYPE_UNSIGNED (t2))
	    {
	      గణన బహుళకం_class mclass = (గణన బహుళకం_class) 0;
	      ఒకవేళ (GET_బహుళకం_CLASS (m2) == బహుళకం_UFRACT)
		mclass = బహుళకం_FRACT;
	      లేకపోతే ఒకవేళ (GET_బహుళకం_CLASS (m2) == బహుళకం_UACCUM)
		mclass = బహుళకం_ACCUM;
	      లేకపోతే
		gcc_unreachable ();
	      m2 = as_a <scalar_బహుళకం>
		(బహుళకం_for_కొలత (GET_బహుళకం_PRECISION (m2), mclass, 0));
	    }
	}

      ఒకవేళ (code1 == FIXED_బిందువు_TYPE)
	{
	  fbit1 = GET_బహుళకం_FBIT (m1);
	  ibit1 = GET_బహుళకం_IBIT (m1);
	}
      లేకపోతే
	{
	  fbit1 = 0;
	  /* Signed integers need to subtract one sign bit.  */
	  ibit1 = TYPE_PRECISION (t1) - (!TYPE_UNSIGNED (t1));
	}

      ఒకవేళ (code2 == FIXED_బిందువు_TYPE)
	{
	  fbit2 = GET_బహుళకం_FBIT (m2);
	  ibit2 = GET_బహుళకం_IBIT (m2);
	}
      లేకపోతే
	{
	  fbit2 = 0;
	  /* Signed integers need to subtract one sign bit.  */
	  ibit2 = TYPE_PRECISION (t2) - (!TYPE_UNSIGNED (t2));
	}

      max_ibit = ibit1 >= ibit2 ?  ibit1 : ibit2;
      max_fbit = fbit1 >= fbit2 ?  fbit1 : fbit2;
      తిరిగి c_common_fixed_బిందువు_type_for_కొలత (max_ibit, max_fbit, unsignedp,
						 satp);
    }

  /* Both real or both integers; use the one with greater precision.  */

  ఒకవేళ (TYPE_PRECISION (t1) > TYPE_PRECISION (t2))
    తిరిగి t1;
  లేకపోతే ఒకవేళ (TYPE_PRECISION (t2) > TYPE_PRECISION (t1))
    తిరిగి t2;

  /* Same precision.  Prefer long longs to longs to ints when the
     same precision, following the C99 rules on integer type rank
     (which are equivalent to the C90 rules for C90 types).  */

  ఒకవేళ (TYPE_MAIN_VARIANT (t1) == long_long_unsigned_type_కణుపు
      || TYPE_MAIN_VARIANT (t2) == long_long_unsigned_type_కణుపు)
    తిరిగి long_long_unsigned_type_కణుపు;

  ఒకవేళ (TYPE_MAIN_VARIANT (t1) == long_long_integer_type_కణుపు
      || TYPE_MAIN_VARIANT (t2) == long_long_integer_type_కణుపు)
    {
      ఒకవేళ (TYPE_UNSIGNED (t1) || TYPE_UNSIGNED (t2))
	తిరిగి long_long_unsigned_type_కణుపు;
      లేకపోతే
	తిరిగి long_long_integer_type_కణుపు;
    }

  ఒకవేళ (TYPE_MAIN_VARIANT (t1) == long_unsigned_type_కణుపు
      || TYPE_MAIN_VARIANT (t2) == long_unsigned_type_కణుపు)
    తిరిగి long_unsigned_type_కణుపు;

  ఒకవేళ (TYPE_MAIN_VARIANT (t1) == long_integer_type_కణుపు
      || TYPE_MAIN_VARIANT (t2) == long_integer_type_కణుపు)
    {
      /* But preserve unsignedness from the other type,
	 since long cannot hold all the values of an unsigned int.  */
      ఒకవేళ (TYPE_UNSIGNED (t1) || TYPE_UNSIGNED (t2))
	తిరిగి long_unsigned_type_కణుపు;
      లేకపోతే
	తిరిగి long_integer_type_కణుపు;
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
  వృక్షం mv1 = TYPE_MAIN_VARIANT (t1);
  వృక్షం mv2 = TYPE_MAIN_VARIANT (t2);

  కొరకు (పూర్ణాంకం i = అంకె_FLOATN_TYPES - 1; i >= 0; i--)
    ఒకవేళ (mv1 == FLOATN_TYPE_కణుపు (i) || mv2 == FLOATN_TYPE_కణుపు (i))
      తిరిగి FLOATN_TYPE_కణుపు (i);

  /* Likewise, prefer long double to double even if same size.  */
  ఒకవేళ (mv1 == long_double_type_కణుపు || mv2 == long_double_type_కణుపు)
    తిరిగి long_double_type_కణుపు;

  /* Likewise, prefer double to float even if same size.
     We got a couple of embedded targets with 32 bit doubles, and the
     pdp11 might have 64 bit floats.  */
  ఒకవేళ (mv1 == double_type_కణుపు || mv2 == double_type_కణుపు)
    తిరిగి double_type_కణుపు;

  ఒకవేళ (mv1 == float_type_కణుపు || mv2 == float_type_కణుపు)
    తిరిగి float_type_కణుపు;

  కొరకు (పూర్ణాంకం i = అంకె_FLOATNX_TYPES - 1; i >= 0; i--)
    ఒకవేళ (mv1 == FLOATNX_TYPE_కణుపు (i) || mv2 == FLOATNX_TYPE_కణుపు (i))
      తిరిగి FLOATNX_TYPE_కణుపు (i);

  ఒకవేళ ((code1 == BITINT_TYPE || code2 == BITINT_TYPE) && code1 != code2)
    {
      /* Prefer any other integral types over bit-precise integer types.  */
      ఒకవేళ (TYPE_UNSIGNED (t1) == TYPE_UNSIGNED (t2))
	తిరిగి code1 == BITINT_TYPE ? t2 : t1;
      /* If BITINT_TYPE is unsigned and the other type is signed
	 non-BITINT_TYPE with the same precision, the latter has higher rank.
	 In that case:
	 Otherwise, both operands are converted to the unsigned integer type
	 corresponding to the type of the operand with signed integer type.  */
      ఒకవేళ (TYPE_UNSIGNED (code1 == BITINT_TYPE ? t1 : t2))
	తిరిగి c_common_unsigned_type (code1 == BITINT_TYPE ? t2 : t1);
    }

  /* Otherwise prefer the unsigned one.  */

  ఒకవేళ (TYPE_UNSIGNED (t1))
    తిరిగి t1;
  లేకపోతే
    తిరిగి t2;
}

/* Wrapper around c_common_type that is used by c-common.cc and other
   front end optimizations that remove promotions.  ENUMERAL_TYPEs
   are allowed here and are converted to their compatible integer types.
   BOOLEAN_TYPEs are allowed here and return either boolean_type_node or
   preferably a non-Boolean type as the common type.  */
వృక్షం
common_type (వృక్షం t1, వృక్షం t2)
{
  ఒకవేళ (వృక్షం_సంకేతం (t1) == ENUMERAL_TYPE)
    t1 = ENUM_UNDERLYING_TYPE (t1);
  ఒకవేళ (వృక్షం_సంకేతం (t2) == ENUMERAL_TYPE)
    t2 = ENUM_UNDERLYING_TYPE (t2);

  /* If both types are BOOLEAN_TYPE, then return boolean_type_node.  */
  ఒకవేళ (వృక్షం_సంకేతం (t1) == BOOLEAN_TYPE
      && వృక్షం_సంకేతం (t2) == BOOLEAN_TYPE)
    తిరిగి boolean_type_కణుపు;

  /* If either type is BOOLEAN_TYPE, then return the other.  */
  ఒకవేళ (వృక్షం_సంకేతం (t1) == BOOLEAN_TYPE)
    తిరిగి t2;
  ఒకవేళ (వృక్షం_సంకేతం (t2) == BOOLEAN_TYPE)
    తిరిగి t1;

  తిరిగి c_common_type (t1, t2);
}



/* Helper function for comptypes.  For two compatible types, return 1
   if they pass consistency checks.  In particular we test that
   TYPE_CANONICAL is set correctly, i.e. the two types can alias.  */

స్థిర తార్కిక
comptypes_verify (వృక్షం type1, వృక్షం type2)
{
  ఒకవేళ (type1 == type2 || !type1 || !type2
      || వృక్షం_సంకేతం (type1) == ERROR_MARK || వృక్షం_సంకేతం (type2) == ERROR_MARK)
    తిరిగి నిజం;

  gcc_checking_assert (c_verify_type (type1));
  gcc_checking_assert (c_verify_type (type2));

  ఒకవేళ (TYPE_CANONICAL (type1) != TYPE_CANONICAL (type2)
      && !TYPE_STRUCTURAL_EQUALITY_P (type1)
      && !TYPE_STRUCTURAL_EQUALITY_P (type2))
    {
      /* FIXME: check other types. */
      ఒకవేళ (రికార్డు_OR_UNION_TYPE_P (type1)
	  || వృక్షం_సంకేతం (type1) == ENUMERAL_TYPE
	  || వృక్షం_సంకేతం (type2) == ENUMERAL_TYPE)
	తిరిగి అబద్ధం;
    }
  తిరిగి నిజం;
}

నిర్మాణం comptypes_దత్తాంశం {

  /* output */
  తార్కిక enum_and_int_p;
  తార్కిక different_types_p;
  తార్కిక warning_needed;

  /* context */
  తార్కిక anon_క్షేత్రం;
  తార్కిక pointedto;

  /* configuration */
  తార్కిక equiv;
  తార్కిక ignore_promoting_వాదనలు;

  స్థిరరాశి నిర్మాణం tagged_tu_చూసిన_cache* cache;
};


/* Helper function for composite_type.  This function ignores when the
   function type of an old-style declaration is incompatible with a type
   of a declaration with prototype because some are arguments are not
   self-promoting.  This is ignored only for function types but not
   ignored in a nested context.  */

స్థిర తార్కిక
comptypes_check_for_సంయుక్త (వృక్షం t1, వృక్షం t2)
{
  నిర్మాణం comptypes_దత్తాంశం దత్తాంశం = { };
  దత్తాంశం.ignore_promoting_వాదనలు = FUNCTION_TYPE == వృక్షం_సంకేతం (t1);
  తిరిగి comptypes_అంతర్గత (t1, t2, &దత్తాంశం);
}


/* C implementation of compatible_types_for_indirection_note_p.  */

తార్కిక
compatible_types_for_indirection_note_p (వృక్షం type1, వృక్షం type2)
{
  తిరిగి comptypes (type1, type2);
}

/* Return true if TYPE1 and TYPE2 are compatible types for assignment
   or various other operations.  */

తార్కిక
comptypes (వృక్షం type1, వృక్షం type2)
{
  నిర్మాణం comptypes_దత్తాంశం దత్తాంశం = { };
  తార్కిక ret = comptypes_అంతర్గత (type1, type2, &దత్తాంశం);

  gcc_checking_assert (!ret || comptypes_verify (type1, type2));

  తిరిగి ret;
}


/* Like comptypes, but it returns non-zero only for identical
   types.  */

తార్కిక
comptypes_same_p (వృక్షం type1, వృక్షం type2)
{
  నిర్మాణం comptypes_దత్తాంశం దత్తాంశం = { };
  తార్కిక ret = comptypes_అంతర్గత (type1, type2, &దత్తాంశం);

  gcc_checking_assert (!ret || comptypes_verify (type1, type2));

  ఒకవేళ (దత్తాంశం.different_types_p)
    తిరిగి అబద్ధం;

  తిరిగి ret;
}


/* Like comptypes, but if it returns true because enum and int are
   compatible, it sets *ENUM_AND_INT_P to true.  */

తార్కిక
comptypes_check_enum_int (వృక్షం type1, వృక్షం type2, తార్కిక *enum_and_int_p)
{
  నిర్మాణం comptypes_దత్తాంశం దత్తాంశం = { };
  తార్కిక ret = comptypes_అంతర్గత (type1, type2, &దత్తాంశం);
  *enum_and_int_p = దత్తాంశం.enum_and_int_p;

  gcc_checking_assert (!ret || comptypes_verify (type1, type2));

  తిరిగి ret;
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

తార్కిక
comptypes_equiv_p (వృక్షం type1, వృక్షం type2)
{
  నిర్మాణం comptypes_దత్తాంశం దత్తాంశం = { };
  దత్తాంశం.equiv = నిజం;
  తార్కిక ret = comptypes_అంతర్గత (type1, type2, &దత్తాంశం);

  /* check that different equivance classes are assigned only
     to types that are not compatible.  */
  gcc_checking_assert (ret || !comptypes (type1, type2));

  తిరిగి ret;
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

స్థిర తార్కిక
comptypes_అంతర్గత (const_వృక్షం type1, const_వృక్షం type2,
		    నిర్మాణం comptypes_దత్తాంశం *దత్తాంశం)
{
  const_వృక్షం t1 = type1;
  const_వృక్షం t2 = type2;

  /* Suppress errors caused by previously reported errors.  */

  ఒకవేళ (t1 == t2 || !t1 || !t2
      || వృక్షం_సంకేతం (t1) == ERROR_MARK || వృక్షం_సంకేతం (t2) == ERROR_MARK)
    తిరిగి నిజం;

  /* Qualifiers must match. C99 6.7.3p9 */

  ఒకవేళ (TYPE_QUALS (t1) != TYPE_QUALS (t2))
    తిరిగి అబద్ధం;

  /* Enumerated types are compatible with integer types, but this is
     not transitive: two enumerated types in the same translation unit
     are compatible with each other only if they are the same type.  */

  ఒకవేళ (వృక్షం_సంకేతం (t1) == ENUMERAL_TYPE
      && COMPLETE_TYPE_P (t1)
      && వృక్షం_సంకేతం (t2) != ENUMERAL_TYPE)
    {
      t1 = ENUM_UNDERLYING_TYPE (t1);
      ఒకవేళ (వృక్షం_సంకేతం (t2) != VOID_TYPE)
	{
	  దత్తాంశం->enum_and_int_p = నిజం;
	  దత్తాంశం->different_types_p = నిజం;
	}
    }
  లేకపోతే ఒకవేళ (వృక్షం_సంకేతం (t2) == ENUMERAL_TYPE
	   && COMPLETE_TYPE_P (t2)
	   && వృక్షం_సంకేతం (t1) != ENUMERAL_TYPE)
    {
      t2 = ENUM_UNDERLYING_TYPE (t2);
      ఒకవేళ (వృక్షం_సంకేతం (t1) != VOID_TYPE)
	{
	  దత్తాంశం->enum_and_int_p = నిజం;
	  దత్తాంశం->different_types_p = నిజం;
	}
    }

  ఒకవేళ (t1 == t2)
    తిరిగి నిజం;

  /* Different classes of types can't be compatible.  */

  ఒకవేళ (వృక్షం_సంకేతం (t1) != వృక్షం_సంకేతం (t2))
    తిరిగి అబద్ధం;

  /* Allow for two different type nodes which have essentially the same
     definition.  Note that we already checked for equality of the type
     qualifiers (just above).  */

  ఒకవేళ (వృక్షం_సంకేతం (t1) != ARRAY_TYPE
      && TYPE_MAIN_VARIANT (t1) == TYPE_MAIN_VARIANT (t2))
    తిరిగి నిజం;

  పూర్ణాంకం attrval;

  /* 1 if no need for warning yet, 2 if warning cause has been seen.  */
  ఒకవేళ (!(attrval = comp_type_లక్షణాలు (t1, t2)))
    తిరిగి అబద్ధం;

  ఒకవేళ (2 == attrval)
    దత్తాంశం->warning_needed = నిజం;

  ఎంపిక (వృక్షం_సంకేతం (t1))
    {
    స్థితి INTEGER_TYPE:
    స్థితి FIXED_బిందువు_TYPE:
    స్థితి REAL_TYPE:
    స్థితి BITINT_TYPE:
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
      తిరిగి TYPE_CANONICAL (t1) == TYPE_CANONICAL (t2);

    స్థితి సూచిక_TYPE:
      /* Do not remove mode information.  */
      ఒకవేళ (TYPE_బహుళకం (t1) != TYPE_బహుళకం (t2))
	తిరిగి అబద్ధం;
      దత్తాంశం->pointedto = నిజం;
      తిరిగి comptypes_అంతర్గత (వృక్షం_TYPE (t1), వృక్షం_TYPE (t2), దత్తాంశం);

    స్థితి FUNCTION_TYPE:
      తిరిగి function_types_compatible_p (t1, t2, దత్తాంశం);

    స్థితి ARRAY_TYPE:
      {
	వృక్షం d1 = TYPE_DOMAIN (t1);
	వృక్షం d2 = TYPE_DOMAIN (t2);

	/* Target types must match incl. qualifiers.  */
	ఒకవేళ (!comptypes_అంతర్గత (వృక్షం_TYPE (t1), వృక్షం_TYPE (t2), దత్తాంశం))
	  తిరిగి అబద్ధం;

	ఒకవేళ ((d1 == NULL_వృక్షం) != (d2 == NULL_వృక్షం))
	  దత్తాంశం->different_types_p = నిజం;
	/* Ignore size mismatches when forming equivalence classes.  */
	ఒకవేళ (దత్తాంశం->equiv)
	  తిరిగి నిజం;
	/* Sizes must match unless one is missing or variable.  */
	ఒకవేళ (d1 == NULL_వృక్షం || d2 == NULL_వృక్షం || d1 == d2)
	  తిరిగి నిజం;

	తార్కిక d1_variable = శిఖరం_array_vla_p (t1);
	తార్కిక d2_variable = శిఖరం_array_vla_p (t2);

	ఒకవేళ (d1_variable != d2_variable)
	  దత్తాంశం->different_types_p = నిజం;
	ఒకవేళ (d1_variable || d2_variable)
	  తిరిగి నిజం;

	తార్కిక d1_zero = zero_నిడివి_array_type_p (t1)
		       || flexible_array_member_type_p (t1);

	తార్కిక d2_zero = zero_నిడివి_array_type_p (t2)
		       || flexible_array_member_type_p (t2);

	ఒకవేళ (d1_zero && d2_zero)
	  తిరిగి నిజం;
	ఒకవేళ (d1_zero || d2_zero)
	  తిరిగి అబద్ధం;

	ఒకవేళ (!వృక్షం_int_cst_equal (TYPE_MIN_విలువ (d1), TYPE_MIN_విలువ (d2))
	    || !వృక్షం_int_cst_equal (TYPE_MAX_విలువ (d1), TYPE_MAX_విలువ (d2)))
	  తిరిగి అబద్ధం;

	తిరిగి నిజం;
      }

    స్థితి ENUMERAL_TYPE:
    స్థితి రికార్డు_TYPE:
    స్థితి UNION_TYPE:

      ఒకవేళ (!flag_isoc23)
	తిరిగి అబద్ధం;

      తిరిగి tagged_types_tu_compatible_p (t1, t2, దత్తాంశం);

    స్థితి సదిశ_TYPE:
      తిరిగి తెలిసిన_eq (TYPE_సదిశ_SUBPARTS (t1), TYPE_సదిశ_SUBPARTS (t2))
	     && comptypes_అంతర్గత (వృక్షం_TYPE (t1), వృక్షం_TYPE (t2), దత్తాంశం);

    అప్రమేయ:
      తిరిగి అబద్ధం;
    }
  gcc_unreachable ();
}

/* Return true if TTL and TTR are pointers to types that are equivalent, ignoring
   their qualifiers, except for named address spaces.  If the pointers point to
   different named addresses, then we must determine if one address space is a
   subset of the other.  */

స్థిర తార్కిక
comp_లక్ష్యం_types (location_t location, వృక్షం ttl, వృక్షం ttr)
{
  వృక్షం mvl = వృక్షం_TYPE (ttl);
  వృక్షం mvr = వృక్షం_TYPE (ttr);
  addr_space_t asl = TYPE_ADDR_SPACE (mvl);
  addr_space_t asr = TYPE_ADDR_SPACE (mvr);
  addr_space_t as_common;

  /* Fail if pointers point to incompatible address spaces.  */
  ఒకవేళ (!addr_space_superset (asl, asr, &as_common))
    తిరిగి 0;

  /* Qualifiers on element types of array types that are
     pointer targets are also removed.  */
  నిర్మాణం comptypes_దత్తాంశం దత్తాంశం = { };
  ఒకవేళ (!comptypes_అంతర్గత (remove_qualifiers (mvl),
			   remove_qualifiers (mvr), &దత్తాంశం))
    తిరిగి అబద్ధం;

  /* For pedantic use comptypes on arrays before removing
     qualifiers on the element type. */
  ఒకవేళ (వృక్షం_సంకేతం (mvl) == ARRAY_TYPE
      && వృక్షం_సంకేతం (mvr) == ARRAY_TYPE
      && !comptypes (mvl, mvr))
    pedwarn_c11 (location, OPT_Wpedantic, "invalid use of pointers to arrays "
					  "with different qualifiers in ISO C "
					  "before C23");

  ఒకవేళ (దత్తాంశం.warning_needed)
    pedwarn (location, OPT_Wpedantic, "types are not quite compatible");

  ఒకవేళ (దత్తాంశం.enum_and_int_p && warn_cxx_compat)
    warning_at (location, OPT_Wc___compat,
		"pointer target types incompatible in C++");

  తిరిగి నిజం;
}

/* Subroutines of `comptypes'.  */

/* Return true if two 'struct', 'union', or 'enum' types T1 and T2 are
   compatible.  The two types are not the same (which has been
   checked earlier in comptypes_internal).  */

స్థిర తార్కిక
tagged_types_tu_compatible_p (const_వృక్షం t1, const_వృక్షం t2,
			      నిర్మాణం comptypes_దత్తాంశం *దత్తాంశం)
{
  వృక్షం s1, s2;

  ఒకవేళ (c_type_ట్యాగ్ (t1) != c_type_ట్యాగ్ (t2))
    తిరిగి అబద్ధం;

  /* When forming equivalence classes for TYPE_CANONICAL in C23, we treat
     structs with the same tag as equivalent, but only when they are targets
     of pointers inside other structs.  */
  ఒకవేళ (దత్తాంశం->equiv && దత్తాంశం->pointedto && NULL_వృక్షం != c_type_ట్యాగ్ (t1))
    తిరిగి నిజం;

  /* Different types without tag are incompatible except as an anonymous
     field or when forming equivalence classes for TYPE_CANONICAL.  */
  ఒకవేళ (!దత్తాంశం->anon_క్షేత్రం && !దత్తాంశం->equiv && NULL_వృక్షం == c_type_ట్యాగ్ (t1))
    తిరిగి అబద్ధం;

  ఒకవేళ (!దత్తాంశం->anon_క్షేత్రం && TYPE_STUB_DECL (t1) != TYPE_STUB_DECL (t2))
    దత్తాంశం->different_types_p = నిజం;

  /* Incomplete types are incompatible inside a TU.  */
  ఒకవేళ (TYPE_కొలత (t1) == ఖాళీ || TYPE_కొలత (t2) == ఖాళీ)
    తిరిగి అబద్ధం;

  ఒకవేళ (ENUMERAL_TYPE != వృక్షం_సంకేతం (t1)
      && (TYPE_తిరగేయి_STORAGE_క్రమం (t1)
	  != TYPE_తిరగేయి_STORAGE_క్రమం (t2)))
    తిరిగి అబద్ధం;

  ఒకవేళ (TYPE_USER_ALIGN (t1) != TYPE_USER_ALIGN (t2))
    దత్తాంశం->different_types_p = నిజం;

  /* For types already being looked at in some active
     invocation of this function, assume compatibility.
     The cache is built as a linked list on the stack
     with the head of the list passed downwards.  */
  కొరకు (స్థిరరాశి నిర్మాణం tagged_tu_చూసిన_cache *t = దత్తాంశం->cache;
       t != ఖాళీ; t = t->తదుపరి)
    ఒకవేళ (t->t1 == t1 && t->t2 == t2)
      తిరిగి నిజం;

  స్థిరరాశి నిర్మాణం tagged_tu_చూసిన_cache నమోదు_2 = { దత్తాంశం->cache, t1, t2 };

  ఎంపిక (వృక్షం_సంకేతం (t1))
    {
    స్థితి ENUMERAL_TYPE:
      {
	ఒకవేళ (!comptypes (ENUM_UNDERLYING_TYPE (t1), ENUM_UNDERLYING_TYPE (t2)))
	  తిరిగి అబద్ధం;

	/* Speed up the case where the type values are in the same order.  */
	వృక్షం tv1 = TYPE_విలువలు (t1);
	వృక్షం tv2 = TYPE_విలువలు (t2);

	ఒకవేళ (tv1 == tv2)
	  తిరిగి నిజం;

	కొరకు (;tv1 && tv2; tv1 = వృక్షం_CHAIN (tv1), tv2 = వృక్షం_CHAIN (tv2))
	  {
	    ఒకవేళ (వృక్షం_PURPOSE (tv1) != వృక్షం_PURPOSE (tv2))
	      ఆపు;

	    ఒకవేళ (simple_cst_equal (DECL_INITIAL (వృక్షం_విలువ (tv1)),
				  DECL_INITIAL (వృక్షం_విలువ (tv2))) != 1)
	      ఆపు;
	  }

	ఒకవేళ (tv1 == NULL_వృక్షం && tv2 == NULL_వృక్షం)
	  తిరిగి నిజం;

	ఒకవేళ (tv1 == NULL_వృక్షం || tv2 == NULL_వృక్షం)
	  తిరిగి అబద్ధం;

	ఒకవేళ (list_నిడివి (TYPE_విలువలు (t1)) != list_నిడివి (TYPE_విలువలు (t2)))
	  తిరిగి అబద్ధం;

	కొరకు (s1 = TYPE_విలువలు (t1); s1; s1 = వృక్షం_CHAIN (s1))
	  {
	    s2 = purpose_member (వృక్షం_PURPOSE (s1), TYPE_విలువలు (t2));

	    ఒకవేళ (s2 == ఖాళీ
		|| simple_cst_equal (DECL_INITIAL (వృక్షం_విలువ (s1)),
				     DECL_INITIAL (వృక్షం_విలువ (s2))) != 1)
	      తిరిగి అబద్ధం;
	  }

	తిరిగి నిజం;
      }

    స్థితి UNION_TYPE:
    స్థితి రికార్డు_TYPE:

	ఒకవేళ (list_నిడివి (TYPE_FIELDS (t1)) != list_నిడివి (TYPE_FIELDS (t2)))
	  తిరిగి అబద్ధం;

	కొరకు (s1 = TYPE_FIELDS (t1), s2 = TYPE_FIELDS (t2);
	     s1 && s2;
	     s1 = DECL_CHAIN (s1), s2 = DECL_CHAIN (s2))
	  {
	    gcc_assert (వృక్షం_సంకేతం (s1) == క్షేత్రం_DECL);
	    gcc_assert (వృక్షం_సంకేతం (s2) == క్షేత్రం_DECL);

	    వృక్షం ft1 = వృక్షం_TYPE (s1);
	    వృక్షం ft2 = వృక్షం_TYPE (s2);

	    ఒకవేళ (DECL_NAME (s1) != DECL_NAME (s2))
	      తిరిగి అబద్ధం;

	    ఒకవేళ (DECL_ALIGN (s1) != DECL_ALIGN (s2))
	      తిరిగి అబద్ధం;

	    ఒకవేళ (DECL_C_బిట్టు_క్షేత్రం (s1) != DECL_C_బిట్టు_క్షేత్రం (s2))
	       తిరిగి అబద్ధం;

	    ఒకవేళ (DECL_C_బిట్టు_క్షేత్రం (s1))
	      {
		ఒకవేళ (!వృక్షం_int_cst_equal (DECL_కొలత (s1), DECL_కొలత (s2)))
		  తిరిగి అబద్ధం;

		ft1 = DECL_బిట్టు_క్షేత్రం_TYPE (s1);
		ft2 = DECL_బిట్టు_క్షేత్రం_TYPE (s2);
	      }

	    ఒకవేళ (!ft1 || !ft2)
	      తిరిగి అబద్ధం;

	    ఒకవేళ (వృక్షం_సంకేతం (ft1) == ERROR_MARK || వృక్షం_సంకేతం (ft2) == ERROR_MARK)
	      తిరిగి అబద్ధం;

	    దత్తాంశం->anon_క్షేత్రం = !DECL_NAME (s1);
	    దత్తాంశం->pointedto = అబద్ధం;

	    స్థిరరాశి నిర్మాణం tagged_tu_చూసిన_cache *cache = దత్తాంశం->cache;
	    దత్తాంశం->cache = &నమోదు_2;
	    తార్కిక ret = comptypes_అంతర్గత (ft1, ft2, దత్తాంశం);
	    దత్తాంశం->cache = cache;
	    ఒకవేళ (!ret)
	      తిరిగి అబద్ధం;

	    వృక్షం st1 = TYPE_కొలత (వృక్షం_TYPE (s1));
	    వృక్షం st2 = TYPE_కొలత (వృక్షం_TYPE (s2));

	    ఒకవేళ (దత్తాంశం->equiv
		&& st1 && వృక్షం_సంకేతం (st1) == INTEGER_CST
		&& st2 && వృక్షం_సంకేతం (st2) == INTEGER_CST
		&& !వృక్షం_int_cst_equal (st1, st2))
	     తిరిగి అబద్ధం;

	    వృక్షం counted_by1 = lookup_attribute ("counted_by",
						 DECL_లక్షణాలు (s1));
	    వృక్షం counted_by2 = lookup_attribute ("counted_by",
						 DECL_లక్షణాలు (s2));
	    /* If there is no counted_by attribute for both fields.  */
	    ఒకవేళ (!counted_by1 && !counted_by2)
	      కొనసాగు;

	    /* If only one field has counted_by attribute.  */
	    ఒకవేళ ((counted_by1 && !counted_by2)
		|| (!counted_by1 && counted_by2))
	      తిరిగి అబద్ధం;

	    /* Now both s1 and s2 have counted_by attributes, check
	       whether they are the same.  */

	    వృక్షం counted_by_field1
	      = lookup_క్షేత్రం (t1, వృక్షం_విలువ (వృక్షం_విలువ (counted_by1)));
	    వృక్షం counted_by_field2
	      = lookup_క్షేత్రం (t2, వృక్షం_విలువ (వృక్షం_విలువ (counted_by2)));

	    gcc_assert (counted_by_field1 && counted_by_field2);

	    అయితే (వృక్షం_CHAIN (counted_by_field1))
	      counted_by_field1 = వృక్షం_CHAIN (counted_by_field1);
	    అయితే (వృక్షం_CHAIN (counted_by_field2))
	      counted_by_field2 = వృక్షం_CHAIN (counted_by_field2);

	    ఒకవేళ (DECL_NAME (వృక్షం_విలువ (counted_by_field1))
		!= DECL_NAME (వృక్షం_విలువ (counted_by_field2)))
	      తిరిగి అబద్ధం;
	  }
	తిరిగి నిజం;

    అప్రమేయ:
      gcc_unreachable ();
    }
}

/* Return true if two function types F1 and F2 are compatible.
   If either type specifies no argument types,
   the other must specify a fixed number of self-promoting arg types.
   Otherwise, if one type specifies only the number of arguments,
   the other must specify that number of self-promoting arg types.
   Otherwise, the argument types must match.  */

స్థిర తార్కిక
function_types_compatible_p (const_వృక్షం f1, const_వృక్షం f2,
			     నిర్మాణం comptypes_దత్తాంశం *దత్తాంశం)
{
  వృక్షం ret1 = వృక్షం_TYPE (f1);
  వృక్షం ret2 = వృక్షం_TYPE (f2);

  /* 'volatile' qualifiers on a function's return type used to mean
     the function is noreturn.  */
  ఒకవేళ (TYPE_VOLATILE (ret1) != TYPE_VOLATILE (ret2))
    pedwarn (ఆదానం_location, 0, "function return types not compatible due to %<volatile%>");
  ఒకవేళ (TYPE_VOLATILE (ret1))
    ret1 = build_qualified_type (TYPE_MAIN_VARIANT (ret1),
				 TYPE_QUALS (ret1) & ~TYPE_QUAL_VOLATILE);
  ఒకవేళ (TYPE_VOLATILE (ret2))
    ret2 = build_qualified_type (TYPE_MAIN_VARIANT (ret2),
				 TYPE_QUALS (ret2) & ~TYPE_QUAL_VOLATILE);

  తార్కిక ignore_pargs = దత్తాంశం->ignore_promoting_వాదనలు;
  దత్తాంశం->ignore_promoting_వాదనలు = అబద్ధం;

  ఒకవేళ (!comptypes_అంతర్గత (ret1, ret2, దత్తాంశం))
    తిరిగి అబద్ధం;

  దత్తాంశం->ignore_promoting_వాదనలు = ignore_pargs;

  వృక్షం args1 = TYPE_ARG_TYPES (f1);
  వృక్షం args2 = TYPE_ARG_TYPES (f2);

  ఒకవేళ ((args1 == NULL_వృక్షం) != (args2 == NULL_వృక్షం))
    దత్తాంశం->different_types_p = నిజం;

  /* An unspecified parmlist matches any specified parmlist
     whose argument types don't need default promotions.  */

  ఒకవేళ (args1 == NULL_వృక్షం)
    {
      ఒకవేళ (TYPE_NO_NAMED_వాదనలు_STDARG_P (f1) != TYPE_NO_NAMED_వాదనలు_STDARG_P (f2))
	తిరిగి అబద్ధం;
      ఒకవేళ (!(దత్తాంశం->ignore_promoting_వాదనలు || self_promoting_వాదనలు_p (args2)))
	తిరిగి అబద్ధం;
      దత్తాంశం->ignore_promoting_వాదనలు = అబద్ధం;
      /* If one of these types comes from a non-prototype fn definition,
	 compare that with the other type's arglist.
	 If they don't match, ask for a warning (but no error).  */
      ఒకవేళ (TYPE_ACTUAL_ARG_TYPES (f1)
	  && !type_lists_compatible_p (args2, TYPE_ACTUAL_ARG_TYPES (f1), దత్తాంశం))
	 దత్తాంశం->warning_needed = నిజం;
      తిరిగి నిజం;
    }
  ఒకవేళ (args2 == NULL_వృక్షం)
    {
      ఒకవేళ (TYPE_NO_NAMED_వాదనలు_STDARG_P (f1) != TYPE_NO_NAMED_వాదనలు_STDARG_P (f2))
	తిరిగి అబద్ధం;
      ఒకవేళ (!(దత్తాంశం->ignore_promoting_వాదనలు || self_promoting_వాదనలు_p (args1)))
	తిరిగి అబద్ధం;
      దత్తాంశం->ignore_promoting_వాదనలు = అబద్ధం;
      ఒకవేళ (TYPE_ACTUAL_ARG_TYPES (f2)
	  && !type_lists_compatible_p (args1, TYPE_ACTUAL_ARG_TYPES (f2), దత్తాంశం))
	దత్తాంశం->warning_needed = నిజం;
      తిరిగి నిజం;
    }

  /* Both types have argument lists: compare them and propagate results.  */
  తిరిగి type_lists_compatible_p (args1, args2, దత్తాంశం);
}

/* Check two lists of types for compatibility, returning false for
   incompatible, true for compatible.  */

స్థిర తార్కిక
type_lists_compatible_p (const_వృక్షం args1, const_వృక్షం args2,
			 నిర్మాణం comptypes_దత్తాంశం *దత్తాంశం)
{
  అయితే (1)
    {
      ఒకవేళ (args1 == NULL_వృక్షం && args2 == NULL_వృక్షం)
	తిరిగి నిజం;
      /* If one list is shorter than the other,
	 they fail to match.  */
      ఒకవేళ (args1 == NULL_వృక్షం || args2 == NULL_వృక్షం)
	తిరిగి అబద్ధం;
      వృక్షం a1 = వృక్షం_విలువ (args1);
      వృక్షం a2 = వృక్షం_విలువ (args2);
      వృక్షం mv1 = remove_qualifiers (a1);
      వృక్షం mv2 = remove_qualifiers (a2);

      gcc_assert (mv2);
      gcc_assert (mv2);

      /* If one of the lists has an error marker, ignore this arg.  */
      ఒకవేళ (వృక్షం_సంకేతం (a1) == ERROR_MARK
	       || వృక్షం_సంకేతం (a2) == ERROR_MARK)
	;
      లేకపోతే ఒకవేళ (!comptypes_అంతర్గత (mv1, mv2, దత్తాంశం))
	{
	  దత్తాంశం->different_types_p = నిజం;
	  /* Allow  wait (union {union wait *u; int *i} *)
	     and  wait (union wait *)  to be compatible.  */
	  ఒకవేళ (వృక్షం_సంకేతం (a1) == UNION_TYPE
	      && (TYPE_NAME (a1) == NULL_వృక్షం
		  || TYPE_TRANSPARENT_AGGR (a1))
	      && వృక్షం_సంకేతం (TYPE_కొలత (a1)) == INTEGER_CST
	      && వృక్షం_int_cst_equal (TYPE_కొలత (a1),
				     TYPE_కొలత (a2)))
	    {
	      వృక్షం memb;
	      కొరకు (memb = TYPE_FIELDS (a1);
		   memb; memb = DECL_CHAIN (memb))
		{
		  వృక్షం mv3 = remove_qualifiers (వృక్షం_TYPE (memb));
		  ఒకవేళ (comptypes_అంతర్గత (mv3, mv2, దత్తాంశం))
		    ఆపు;
		}
	      ఒకవేళ (memb == NULL_వృక్షం)
		తిరిగి అబద్ధం;
	    }
	  లేకపోతే ఒకవేళ (వృక్షం_సంకేతం (a2) == UNION_TYPE
		   && (TYPE_NAME (a2) == NULL_వృక్షం
		       || TYPE_TRANSPARENT_AGGR (a2))
		   && వృక్షం_సంకేతం (TYPE_కొలత (a2)) == INTEGER_CST
		   && వృక్షం_int_cst_equal (TYPE_కొలత (a2),
					  TYPE_కొలత (a1)))
	    {
	      వృక్షం memb;
	      కొరకు (memb = TYPE_FIELDS (a2);
		   memb; memb = DECL_CHAIN (memb))
		{
		  వృక్షం mv3 = remove_qualifiers (వృక్షం_TYPE (memb));
		  ఒకవేళ (comptypes_అంతర్గత (mv3, mv1, దత్తాంశం))
		    ఆపు;
		}
	      ఒకవేళ (memb == NULL_వృక్షం)
		తిరిగి అబద్ధం;
	    }
	  లేకపోతే
	    తిరిగి అబద్ధం;
	}

      args1 = వృక్షం_CHAIN (args1);
      args2 = వృక్షం_CHAIN (args2);
    }
}

/* Compute the size to increment a pointer by.  When a function type or void
   type or incomplete type is passed, size_one_node is returned.
   This function does not emit any diagnostics; the caller is responsible
   for that.  */

స్థిర వృక్షం
c_కొలత_లోపల_బైట్లు (const_వృక్షం type)
{
  గణన వృక్షం_సంకేతం_2 సంకేతం_2 = వృక్షం_సంకేతం (type);

  ఒకవేళ (సంకేతం_2 == FUNCTION_TYPE || సంకేతం_2 == VOID_TYPE || సంకేతం_2 == ERROR_MARK
      || !COMPLETE_TYPE_P (type))
    తిరిగి కొలత_one_కణుపు;

  /* Convert in case a char is more than one unit.  */
  తిరిగి కొలత_binop_loc (ఆదానం_location, CEIL_DIV_సమాసం, TYPE_కొలత_UNIT (type),
			 కొలత_int (TYPE_PRECISION (char_type_కణుపు)
				   / బిట్లు_చొప్పున_UNIT));
}

/* Return either DECL or its known constant value (if it has one).  */

వృక్షం
decl_constant_విలువ_1 (వృక్షం decl, తార్కిక లోపల_init)
{
  ఒకవేళ (/* Note that DECL_INITIAL isn't valid for a PARM_DECL.  */
      వృక్షం_సంకేతం (decl) != PARM_DECL
      && !వృక్షం_THIS_VOLATILE (decl)
      && వృక్షం_READONLY (decl)
      && DECL_INITIAL (decl) != NULL_వృక్షం
      && !error_నిర్వాహ్యం_p (DECL_INITIAL (decl))
      /* This is invalid if initial value is not constant.
	 If it has either a function call, a memory reference,
	 or a variable, then re-evaluating it could give different results.  */
      && వృక్షం_CONSTANT (DECL_INITIAL (decl))
      /* Check for cases where this is sub-optimal, even though valid.  */
      && (లోపల_init || వృక్షం_సంకేతం (DECL_INITIAL (decl)) != CONSTRUCTOR))
    తిరిగి DECL_INITIAL (decl);
  తిరిగి decl;
}

/* Return either DECL or its known constant value (if it has one).
   Like the above, but always return decl outside of functions.  */

వృక్షం
decl_constant_విలువ (వృక్షం decl)
{
  /* Don't change a variable array bound or initial value to a constant
     in a place where a variable is invalid.  */
  తిరిగి current_function_decl ? decl_constant_విలువ_1 (decl, అబద్ధం) : decl;
}

/* Convert the array expression EXP to a pointer.  */
స్థిర వృక్షం
array_గమ్యం_సూచిక_conversion (location_t loc, వృక్షం ఘాతాంకం)
{
  వృక్షం orig_exp = ఘాతాంకం;
  వృక్షం type = వృక్షం_TYPE (ఘాతాంకం);
  వృక్షం adr;
  వృక్షం restype = వృక్షం_TYPE (type);
  వృక్షం ptrtype;

  gcc_assert (వృక్షం_సంకేతం (type) == ARRAY_TYPE);

  STRIP_TYPE_NOPS (ఘాతాంకం);

  copy_warning (ఘాతాంకం, orig_exp);

  ptrtype = c_build_సూచిక_type (restype);

  ఒకవేళ (పరోక్ష_REF_P (ఘాతాంకం))
    తిరిగి convert (ptrtype, వృక్షం_నిర్వాహ్యం (ఘాతాంకం, 0));

  /* In C++ array compound literals are temporary objects unless they are
     const or appear in namespace scope, so they are destroyed too soon
     to use them for much of anything  (c++/53220).  */
  ఒకవేళ (warn_cxx_compat && వృక్షం_సంకేతం (ఘాతాంకం) == COMPOUND_LITERAL_సమాసం)
    {
      వృక్షం decl = వృక్షం_నిర్వాహ్యం (వృక్షం_నిర్వాహ్యం (ఘాతాంకం, 0), 0);
      ఒకవేళ (!వృక్షం_READONLY (decl) && !వృక్షం_STATIC (decl))
	warning_at (DECL_ఆధారం_LOCATION (decl), OPT_Wc___compat,
		    "converting an array compound literal to a pointer "
		    "leads to a dangling pointer in C++");
    }

  adr = build_unary_op (loc, ADDR_సమాసం, ఘాతాంకం, నిజం);
  తిరిగి convert (ptrtype, adr);
}

/* Convert the function expression EXP to a pointer.  */
స్థిర వృక్షం
function_గమ్యం_సూచిక_conversion (location_t loc, వృక్షం ఘాతాంకం)
{
  వృక్షం orig_exp = ఘాతాంకం;

  gcc_assert (వృక్షం_సంకేతం (వృక్షం_TYPE (ఘాతాంకం)) == FUNCTION_TYPE);

  STRIP_TYPE_NOPS (ఘాతాంకం);

  copy_warning (ఘాతాంకం, orig_exp);

  వృక్షం exp2 = build_unary_op (loc, ADDR_సమాసం, ఘాతాంకం, అబద్ధం);

  /* If the function is defined and known to not require a non-local
     context, make sure no trampoline is generated.  */
  ఒకవేళ (వృక్షం_సంకేతం (ఘాతాంకం) == FUNCTION_DECL
      && DECL_INITIAL (ఘాతాంకం) && !C_FUNC_NONLOCAL_CONTEXT (ఘాతాంకం))
   వృక్షం_NO_TRAMPOLINE (exp2) = 1;

  తిరిగి exp2;
}

/* Mark EXP as read, not just set, for set but not used -Wunused
   warning purposes.  */

శూన్య
mark_exp_read (వృక్షం ఘాతాంకం)
{
  ఎంపిక (వృక్షం_సంకేతం (ఘాతాంకం))
    {
    స్థితి VAR_DECL:
    స్థితి PARM_DECL:
      DECL_READ_P (ఘాతాంకం) = 1;
      ఆపు;
    CASE_CONVERT:
      ఒకవేళ (VOID_TYPE_P (వృక్షం_TYPE (ఘాతాంకం)))
	ఎంపిక (వృక్షం_సంకేతం (వృక్షం_నిర్వాహ్యం (ఘాతాంకం, 0)))
	  {
	  స్థితి PREINCREMENT_సమాసం:
	  స్థితి PREDECREMENT_సమాసం:
	  స్థితి POSTINCREMENT_సమాసం:
	  స్థితి POSTDECREMENT_సమాసం:
	    తిరిగి;
	  అప్రమేయ:
	    ఆపు;
	  }
      /* FALLTHRU */
    స్థితి ARRAY_REF:
    స్థితి COMPONENT_REF:
    స్థితి MODIFY_సమాసం:
    స్థితి REALPART_సమాసం:
    స్థితి IMAGPART_సమాసం:
    స్థితి ADDR_సమాసం:
    స్థితి VIEW_CONVERT_సమాసం:
    స్థితి PREINCREMENT_సమాసం:
    స్థితి PREDECREMENT_సమాసం:
    స్థితి POSTINCREMENT_సమాసం:
    స్థితి POSTDECREMENT_సమాసం:
      mark_exp_read (వృక్షం_నిర్వాహ్యం (ఘాతాంకం, 0));
      ఆపు;
    స్థితి COMPOUND_సమాసం:
      /* Pattern match what build_atomic_assign produces with modifycode
	 NOP_EXPR.  */
      ఒకవేళ (VAR_P (వృక్షం_నిర్వాహ్యం (ఘాతాంకం, 1))
	  && DECL_ARTIFICIAL (వృక్షం_నిర్వాహ్యం (ఘాతాంకం, 1))
	  && వృక్షం_సంకేతం (వృక్షం_నిర్వాహ్యం (ఘాతాంకం, 0)) == COMPOUND_సమాసం)
	{
	  వృక్షం t1 = వృక్షం_నిర్వాహ్యం (వృక్షం_నిర్వాహ్యం (ఘాతాంకం, 0), 0);
	  వృక్షం t2 = వృక్షం_నిర్వాహ్యం (వృక్షం_నిర్వాహ్యం (ఘాతాంకం, 0), 1);
	  ఒకవేళ (వృక్షం_సంకేతం (t1) == లక్ష్యం_సమాసం
	      && లక్ష్యం_సమాసం_స్థానం (t1) == వృక్షం_నిర్వాహ్యం (ఘాతాంకం, 1)
	      && వృక్షం_సంకేతం (t2) == CALL_సమాసం)
	    {
	      వృక్షం fndecl = get_callee_fndecl (t2);
	      వృక్షం arg = NULL_వృక్షం;
	      ఒకవేళ (fndecl
		  && వృక్షం_సంకేతం (fndecl) == FUNCTION_DECL
		  && fndecl_built_లోపల_p (fndecl, BUILT_లోపల_సాధారణ)
		  && call_సమాసం_nargs (t2) >= 2)
		ఎంపిక (DECL_FUNCTION_సంకేతం (fndecl))
		  {
		  స్థితి BUILT_లోపల_ATOMIC_STORE:
		    arg = CALL_సమాసం_ARG (t2, 1);
		    ఆపు;
		  స్థితి BUILT_లోపల_ATOMIC_STORE_1:
		  స్థితి BUILT_లోపల_ATOMIC_STORE_2:
		  స్థితి BUILT_లోపల_ATOMIC_STORE_4:
		  స్థితి BUILT_లోపల_ATOMIC_STORE_8:
		  స్థితి BUILT_లోపల_ATOMIC_STORE_16:
		    arg = CALL_సమాసం_ARG (t2, 0);
		    ఆపు;
		  అప్రమేయ:
		    ఆపు;
		  }
	      ఒకవేళ (arg)
		{
		  STRIP_NOPS (arg);
		  ఒకవేళ (వృక్షం_సంకేతం (arg) == ADDR_సమాసం
		      && DECL_P (వృక్షం_నిర్వాహ్యం (arg, 0))
		      && TYPE_ATOMIC (వృక్షం_TYPE (వృక్షం_నిర్వాహ్యం (arg, 0))))
		    mark_exp_read (వృక్షం_నిర్వాహ్యం (arg, 0));
		}
	    }
	}
      /* FALLTHRU */
    స్థితి C_MAYBE_CONST_సమాసం:
      mark_exp_read (వృక్షం_నిర్వాహ్యం (ఘాతాంకం, 1));
      ఆపు;
    స్థితి OMP_ARRAY_SECTION:
      mark_exp_read (వృక్షం_నిర్వాహ్యం (ఘాతాంకం, 0));
      ఒకవేళ (వృక్షం_నిర్వాహ్యం (ఘాతాంకం, 1))
	mark_exp_read (వృక్షం_నిర్వాహ్యం (ఘాతాంకం, 1));
      ఒకవేళ (వృక్షం_నిర్వాహ్యం (ఘాతాంకం, 2))
	mark_exp_read (వృక్షం_నిర్వాహ్యం (ఘాతాంకం, 2));
      ఆపు;
    అప్రమేయ:
      ఆపు;
    }
}

/* Perform the default conversion of arrays and functions to pointers.
   Return the result of converting EXP.  For any other expression, just
   return EXP.

   LOC is the location of the expression.  */

నిర్మాణం c_సమాసం
default_function_array_conversion (location_t loc, నిర్మాణం c_సమాసం ఘాతాంకం)
{
  వృక్షం orig_exp = ఘాతాంకం.విలువ;
  వృక్షం type = వృక్షం_TYPE (ఘాతాంకం.విలువ);
  గణన వృక్షం_సంకేతం_2 సంకేతం_2 = వృక్షం_సంకేతం (type);

  ఎంపిక (సంకేతం_2)
    {
    స్థితి ARRAY_TYPE:
      {
	తార్కిక not_lvalue = అబద్ధం;
	తార్కిక lvalue_array_p;

	అయితే ((వృక్షం_సంకేతం (ఘాతాంకం.విలువ) == NON_LVALUE_సమాసం
		|| CONVERT_సమాసం_P (ఘాతాంకం.విలువ))
	       && వృక్షం_TYPE (వృక్షం_నిర్వాహ్యం (ఘాతాంకం.విలువ, 0)) == type)
	  {
	    ఒకవేళ (వృక్షం_సంకేతం (ఘాతాంకం.విలువ) == NON_LVALUE_సమాసం)
	      not_lvalue = నిజం;
	    ఘాతాంకం.విలువ = వృక్షం_నిర్వాహ్యం (ఘాతాంకం.విలువ, 0);
	  }

	copy_warning (ఘాతాంకం.విలువ, orig_exp);

	lvalue_array_p = !not_lvalue && lvalue_p (ఘాతాంకం.విలువ);
	ఒకవేళ (!flag_isoc99 && !lvalue_array_p)
	  {
	    /* Before C99, non-lvalue arrays do not decay to pointers.
	       Normally, using such an array would be invalid; but it can
	       be used correctly inside sizeof or as a statement expression.
	       Thus, do not give an error here; an error will result later.  */
	    తిరిగి ఘాతాంకం;
	  }

	ఘాతాంకం.విలువ = array_గమ్యం_సూచిక_conversion (loc, ఘాతాంకం.విలువ);
      }
      ఆపు;
    స్థితి FUNCTION_TYPE:
      ఘాతాంకం.విలువ = function_గమ్యం_సూచిక_conversion (loc, ఘాతాంకం.విలువ);
      ఆపు;
    అప్రమేయ:
      ఆపు;
    }

  తిరిగి ఘాతాంకం;
}

నిర్మాణం c_సమాసం
default_function_array_read_conversion (location_t loc, నిర్మాణం c_సమాసం ఘాతాంకం)
{
  mark_exp_read (ఘాతాంకం.విలువ);
  /* We only generate a call to .ACCESS_WITH_SIZE when it is a read.  */
  ఒకవేళ (వృక్షం_సంకేతం (ఘాతాంకం.విలువ) == COMPONENT_REF
      && handle_counted_by_p (ఘాతాంకం.విలువ))
    ఘాతాంకం.విలువ = handle_counted_by_for_component_ref (loc, ఘాతాంకం.విలువ);
  తిరిగి default_function_array_conversion (loc, ఘాతాంకం);
}

/* Return whether EXPR should be treated as an atomic lvalue for the
   purposes of load and store handling.  */

స్థిర తార్కిక
really_atomic_lvalue (వృక్షం సమాసం)
{
  ఒకవేళ (error_నిర్వాహ్యం_p (సమాసం))
    తిరిగి అబద్ధం;
  ఒకవేళ (!TYPE_ATOMIC (వృక్షం_TYPE (సమాసం)))
    తిరిగి అబద్ధం;
  ఒకవేళ (!COMPLETE_TYPE_P (వృక్షం_TYPE (సమాసం)))
    తిరిగి అబద్ధం;
  ఒకవేళ (!lvalue_p (సమాసం))
    తిరిగి అబద్ధం;

  /* Ignore _Atomic on register variables, since their addresses can't
     be taken so (a) atomicity is irrelevant and (b) the normal atomic
     sequences wouldn't work.  Ignore _Atomic on structures containing
     bit-fields, since accessing elements of atomic structures or
     unions is undefined behavior (C11 6.5.2.3#5), but it's unclear if
     it's undefined at translation time or execution time, and the
     normal atomic sequences again wouldn't work.  */
  అయితే (handled_component_p (సమాసం))
    {
      ఒకవేళ (వృక్షం_సంకేతం (సమాసం) == COMPONENT_REF
	  && DECL_C_బిట్టు_క్షేత్రం (వృక్షం_నిర్వాహ్యం (సమాసం, 1)))
	తిరిగి అబద్ధం;
      సమాసం = వృక్షం_నిర్వాహ్యం (సమాసం, 0);
    }
  ఒకవేళ (వృక్షం_సంకేతం (సమాసం) == COMPOUND_LITERAL_సమాసం)
    సమాసం = COMPOUND_LITERAL_సమాసం_DECL (సమాసం);
  ఒకవేళ (DECL_P (సమాసం) && C_DECL_రిజిస్టరు (సమాసం))
    తిరిగి అబద్ధం;
  తిరిగి నిజం;
}

/* If EXPR is a named constant (C23) derived from a constexpr variable
   - that is, a reference to such a variable, or a member extracted by
   a sequence of structure and union (but not array) member accesses
   (where union member accesses must access the same member as
   initialized) - then return the corresponding initializer;
   otherwise, return NULL_TREE.  */

స్థిర వృక్షం
maybe_get_constexpr_init (వృక్షం సమాసం)
{
  వృక్షం decl = NULL_వృక్షం;
  ఒకవేళ (వృక్షం_సంకేతం (సమాసం) == VAR_DECL)
    decl = సమాసం;
  లేకపోతే ఒకవేళ (వృక్షం_సంకేతం (సమాసం) == COMPOUND_LITERAL_సమాసం)
    decl = COMPOUND_LITERAL_సమాసం_DECL (సమాసం);
  ఒకవేళ (decl
      && C_DECL_DECLARED_CONSTEXPR (decl)
      && DECL_INITIAL (decl) != NULL_వృక్షం
      && !error_నిర్వాహ్యం_p (DECL_INITIAL (decl)))
    తిరిగి DECL_INITIAL (decl);
  ఒకవేళ (వృక్షం_సంకేతం (సమాసం) != COMPONENT_REF)
    తిరిగి NULL_వృక్షం;
  వృక్షం inner = maybe_get_constexpr_init (వృక్షం_నిర్వాహ్యం (సమాసం, 0));
  ఒకవేళ (inner == NULL_వృక్షం)
    తిరిగి NULL_వృక్షం;
  అయితే ((CONVERT_సమాసం_P (inner) || వృక్షం_సంకేతం (inner) == NON_LVALUE_సమాసం)
	 && !error_నిర్వాహ్యం_p (inner)
	 && (TYPE_MAIN_VARIANT (వృక్షం_TYPE (inner))
	     == TYPE_MAIN_VARIANT (వృక్షం_TYPE (వృక్షం_నిర్వాహ్యం (inner, 0)))))
    inner = వృక్షం_నిర్వాహ్యం (inner, 0);
  ఒకవేళ (వృక్షం_సంకేతం (inner) != CONSTRUCTOR)
    తిరిగి NULL_వృక్షం;
  వృక్షం క్షేత్రం_2 = వృక్షం_నిర్వాహ్యం (సమాసం, 1);
  గుర్తులేని HOST_WIDE_INT cidx;
  వృక్షం cfield, cvalue;
  తార్కిక have_other_init = అబద్ధం;
  FOR_EACH_CONSTRUCTOR_ELT (CONSTRUCTOR_ELTS (inner), cidx, cfield, cvalue)
    {
      ఒకవేళ (cfield == క్షేత్రం_2)
	తిరిగి cvalue;
      have_other_init = నిజం;
    }
  ఒకవేళ (వృక్షం_సంకేతం (వృక్షం_TYPE (inner)) == UNION_TYPE
      && (have_other_init || క్షేత్రం_2 != TYPE_FIELDS (వృక్షం_TYPE (inner))))
    తిరిగి NULL_వృక్షం;
  /* Return a default initializer.  */
  ఒకవేళ (రికార్డు_OR_UNION_TYPE_P (వృక్షం_TYPE (సమాసం)))
    తిరిగి build_constructor (వృక్షం_TYPE (సమాసం), ఖాళీ);
  తిరిగి build_zero_cst (వృక్షం_TYPE (సమాసం));
}

/* Helper function for convert_lvalue_to_rvalue called via
   walk_tree_without_duplicates.  Find DATA inside of the expression.  */

స్థిర వృక్షం
c_కనుగొను_var_r (వృక్షం *tp, పూర్ణాంకం *walk_subtrees, శూన్య *దత్తాంశం)
{
  ఒకవేళ (TYPE_P (*tp))
    *walk_subtrees = 0;
  లేకపోతే ఒకవేళ (*tp == (వృక్షం) దత్తాంశం)
    తిరిగి *tp;
  తిరిగి NULL_వృక్షం;
}

/* Convert expression EXP (location LOC) from lvalue to rvalue,
   including converting functions and arrays to pointers if CONVERT_P.
   If READ_P, also mark the expression as having been read.  If
   FOR_INIT, constexpr expressions of structure and union type should
   be replaced by the corresponding CONSTRUCTOR; otherwise, only
   constexpr scalars (including elements of structures and unions) are
   replaced by their initializers.  */

నిర్మాణం c_సమాసం
convert_lvalue_గమ్యం_rvalue (location_t loc, నిర్మాణం c_సమాసం ఘాతాంకం,
			  తార్కిక convert_p, తార్కిక read_p, తార్కిక for_init)
{
  తార్కిక force_non_npc = అబద్ధం;
  ఒకవేళ (read_p)
    mark_exp_read (ఘాతాంకం.విలువ);
  /* We only generate a call to .ACCESS_WITH_SIZE when it is a read.  */
  ఒకవేళ (read_p && వృక్షం_సంకేతం (ఘాతాంకం.విలువ) == COMPONENT_REF
      && handle_counted_by_p (ఘాతాంకం.విలువ))
    ఘాతాంకం.విలువ = handle_counted_by_for_component_ref (loc, ఘాతాంకం.విలువ);

  ఒకవేళ (convert_p)
    ఘాతాంకం = default_function_array_conversion (loc, ఘాతాంకం);
  ఒకవేళ (!VOID_TYPE_P (వృక్షం_TYPE (ఘాతాంకం.విలువ))
      || (flag_isoc2y
	  && TYPE_QUALS (వృక్షం_TYPE (ఘాతాంకం.విలువ)) != TYPE_UNQUALIFIED))
    ఘాతాంకం.విలువ = require_complete_type (loc, ఘాతాంకం.విలువ);
  ఒకవేళ (for_init || !రికార్డు_OR_UNION_TYPE_P (వృక్షం_TYPE (ఘాతాంకం.విలువ)))
    {
      వృక్షం init = maybe_get_constexpr_init (ఘాతాంకం.విలువ);
      ఒకవేళ (init != NULL_వృక్షం)
	{
	  /* A named constant of pointer type or type nullptr_t is not
	     a null pointer constant even if the initializer is
	     one.  */
	  ఒకవేళ (వృక్షం_సంకేతం (init) == INTEGER_CST
	      && !INTEGRAL_TYPE_P (వృక్షం_TYPE (init))
	      && integer_zerop (init))
	    force_non_npc = నిజం;
	  ఘాతాంకం.విలువ = init;
	}
    }
  ఒకవేళ (really_atomic_lvalue (ఘాతాంకం.విలువ))
    {
      vec<వృక్షం, va_gc> *params;
      వృక్షం nonatomic_type, tmp, tmp_addr, fndecl, func_call;
      వృక్షం సమాసం_type = వృక్షం_TYPE (ఘాతాంకం.విలువ);
      వృక్షం సమాసం_addr = build_unary_op (loc, ADDR_సమాసం, ఘాతాంకం.విలువ, అబద్ధం);
      వృక్షం seq_cst = build_int_cst (integer_type_కణుపు, MEMMODEL_SEQ_CST);

      gcc_assert (TYPE_ATOMIC (సమాసం_type));

      /* Expansion of a generic atomic load may require an addition
	 element, so allocate enough to prevent a resize.  */
      vec_alloc (params, 4);

      /* Remove the qualifiers for the rest of the expressions and
	 create the VAL temp variable to hold the RHS.  */
      nonatomic_type = build_qualified_type (సమాసం_type, TYPE_UNQUALIFIED);
      tmp = create_tmp_var_raw (nonatomic_type);
      tmp_addr = build_unary_op (loc, ADDR_సమాసం, tmp, అబద్ధం);
      వృక్షం_ADDRESSABLE (tmp) = 1;
      /* Do not disable warnings for TMP even though it's artificial.
	 -Winvalid-memory-model depends on it.  */

      /* Issue __atomic_load (&expr, &tmp, SEQ_CST);  */
      fndecl = builtin_decl_explicit (BUILT_లోపల_ATOMIC_ఎక్కించు);
      params->శీఘ్ర_నెట్టు (సమాసం_addr);
      params->శీఘ్ర_నెట్టు (tmp_addr);
      params->శీఘ్ర_నెట్టు (seq_cst);
      func_call = c_build_function_call_vec (loc, vNULL, fndecl, params, ఖాళీ);

      /* EXPR is always read.  */
      mark_exp_read (ఘాతాంకం.విలువ);

      /* Optimize the common case where c_build_function_call_vec
	 immediately folds __atomic_load (&expr, &tmp, SEQ_CST); into
	 tmp = __atomic_load_<N> (&expr, SEQ_CST);
	 In that case tmp is not addressable and can be initialized
	 fully by the rhs of the MODIFY_EXPR.  */
      వృక్షం tem = func_call;
      ఒకవేళ (CONVERT_సమాసం_P (tem) && VOID_TYPE_P (వృక్షం_TYPE (tem)))
	{
	  tem = వృక్షం_నిర్వాహ్యం (tem, 0);
	  ఒకవేళ (వృక్షం_సంకేతం (tem) == MODIFY_సమాసం
	      && వృక్షం_నిర్వాహ్యం (tem, 0) == tmp
	      && !walk_వృక్షం_without_duplicates (&వృక్షం_నిర్వాహ్యం (tem, 1),
						c_కనుగొను_var_r, tmp))
	    {
	      వృక్షం_ADDRESSABLE (tmp) = 0;
	      func_call = వృక్షం_నిర్వాహ్యం (tem, 1);
	    }
	}

      /* Return tmp which contains the value loaded.  */
      ఘాతాంకం.విలువ = build4 (లక్ష్యం_సమాసం, nonatomic_type, tmp, func_call,
			  NULL_వృక్షం, NULL_వృక్షం);
    }
  ఒకవేళ (convert_p && !error_నిర్వాహ్యం_p (ఘాతాంకం.విలువ)
      && (వృక్షం_సంకేతం (వృక్షం_TYPE (ఘాతాంకం.విలువ)) != ARRAY_TYPE))
    ఘాతాంకం.విలువ = convert (build_qualified_type (వృక్షం_TYPE (ఘాతాంకం.విలువ), TYPE_UNQUALIFIED), ఘాతాంకం.విలువ);
  ఒకవేళ (force_non_npc)
    ఘాతాంకం.విలువ = build1 (NOP_సమాసం, వృక్షం_TYPE (ఘాతాంకం.విలువ), ఘాతాంకం.విలువ);

  {
    వృక్షం false_విలువ, true_విలువ;
    ఒకవేళ (convert_p && !error_నిర్వాహ్యం_p (ఘాతాంకం.విలువ)
	&& c_hardbool_type_attr (వృక్షం_TYPE (ఘాతాంకం.విలువ),
				 &false_విలువ, &true_విలువ))
      {
	వృక్షం t = save_సమాసం (ఘాతాంకం.విలువ);

	mark_exp_read (ఘాతాంకం.విలువ);

	వృక్షం trapfn = builtin_decl_explicit (BUILT_లోపల_TRAP);
	వృక్షం సమాసం = build_call_సమాసం_loc (loc, trapfn, 0);
	సమాసం = build_compound_సమాసం (loc, సమాసం, boolean_true_కణుపు);
	సమాసం = fold_build3_loc (loc, COND_సమాసం, boolean_type_కణుపు,
				fold_build2_loc (loc, NE_సమాసం,
						 boolean_type_కణుపు,
						 t, true_విలువ),
				సమాసం, boolean_true_కణుపు);
	సమాసం = fold_build3_loc (loc, COND_సమాసం, boolean_type_కణుపు,
				fold_build2_loc (loc, NE_సమాసం,
						 boolean_type_కణుపు,
						 t, false_విలువ),
				సమాసం, boolean_false_కణుపు);

	ఘాతాంకం.విలువ = సమాసం;
      }
  }

  తిరిగి ఘాతాంకం;
}

/* Wrapper for the overload above, same arguments but for tree rather than
   c_expr.  This is important for hardbools to decay to bools.  */

స్థిర అంతఃవరుస వృక్షం
convert_lvalue_గమ్యం_rvalue (location_t loc, వృక్షం val,
			  తార్కిక convert_p, తార్కిక read_p, తార్కిక for_init = అబద్ధం)
{
  నిర్మాణం c_సమాసం సమాసం;
  memset (&సమాసం, 0, పరిమాణం (సమాసం));
  సమాసం.విలువ = val;
  సమాసం = convert_lvalue_గమ్యం_rvalue (loc, సమాసం, convert_p, read_p, for_init);
  తిరిగి సమాసం.విలువ;
}

/* EXP is an expression of integer type.  Apply the integer promotions
   to it and return the promoted value.  */

వృక్షం
perform_integral_promotions (వృక్షం ఘాతాంకం)
{
  వృక్షం type = వృక్షం_TYPE (ఘాతాంకం);
  గణన వృక్షం_సంకేతం_2 సంకేతం_2 = వృక్షం_సంకేతం (type);

  gcc_assert (INTEGRAL_TYPE_P (type));

  /* Convert enums to the result of applying the integer promotions to
     their underlying type.  */
  ఒకవేళ (సంకేతం_2 == ENUMERAL_TYPE)
    {
      type = ENUM_UNDERLYING_TYPE (type);
      ఒకవేళ (c_promoting_integer_type_p (type))
	{
	  ఒకవేళ (TYPE_UNSIGNED (type)
	      && TYPE_PRECISION (type) == TYPE_PRECISION (integer_type_కణుపు))
	    type = unsigned_type_కణుపు;
	  లేకపోతే
	    type = integer_type_కణుపు;
	}

      తిరిగి convert (type, ఘాతాంకం);
    }

  /* ??? This should no longer be needed now bit-fields have their
     proper types.  */
  ఒకవేళ (వృక్షం_సంకేతం (ఘాతాంకం) == COMPONENT_REF
      && DECL_C_బిట్టు_క్షేత్రం (వృక్షం_నిర్వాహ్యం (ఘాతాంకం, 1)))
    {
      ఒకవేళ (BITINT_TYPE_P (DECL_బిట్టు_క్షేత్రం_TYPE (వృక్షం_నిర్వాహ్యం (ఘాతాంకం, 1))))
	{
	  వృక్షం btype = DECL_బిట్టు_క్షేత్రం_TYPE (వృక్షం_నిర్వాహ్యం (ఘాతాంకం, 1));
	  ఒకవేళ (వృక్షం_సంకేతం (btype) == BITINT_TYPE)
	    తిరిగి convert (btype, ఘాతాంకం);
	  లేకపోతే
	    తిరిగి convert (ENUM_UNDERLYING_TYPE (btype), ఘాతాంకం);
	}
      /* If it's thinner than an int, promote it like a
	 c_promoting_integer_type_p, otherwise leave it alone.  */
      ఒకవేళ (compare_వృక్షం_int (DECL_కొలత (వృక్షం_నిర్వాహ్యం (ఘాతాంకం, 1)),
			    TYPE_PRECISION (integer_type_కణుపు)) < 0)
	తిరిగి convert (integer_type_కణుపు, ఘాతాంకం);
    }

  ఒకవేళ (c_promoting_integer_type_p (type))
    {
      /* Preserve unsignedness if not really getting any wider.  */
      ఒకవేళ (TYPE_UNSIGNED (type)
	  && TYPE_PRECISION (type) == TYPE_PRECISION (integer_type_కణుపు))
	తిరిగి convert (unsigned_type_కణుపు, ఘాతాంకం);

      తిరిగి convert (integer_type_కణుపు, ఘాతాంకం);
    }

  తిరిగి ఘాతాంకం;
}


/* Perform default promotions for C data used in expressions.
   Enumeral types or short or char are converted to int.
   In addition, manifest constants symbols are replaced by their values.  */

వృక్షం
default_conversion (వృక్షం ఘాతాంకం)
{
  వృక్షం orig_exp;
  వృక్షం type = వృక్షం_TYPE (ఘాతాంకం);
  గణన వృక్షం_సంకేతం_2 సంకేతం_2 = వృక్షం_సంకేతం (type);
  వృక్షం promoted_type;

  mark_exp_read (ఘాతాంకం);
  /* We only generate a call to .ACCESS_WITH_SIZE when it is a read.  */
  ఒకవేళ (వృక్షం_సంకేతం (ఘాతాంకం) == COMPONENT_REF
      && handle_counted_by_p (ఘాతాంకం))
    ఘాతాంకం = handle_counted_by_for_component_ref (సమాసం_LOCATION (ఘాతాంకం), ఘాతాంకం);

  /* Functions and arrays have been converted during parsing.  */
  gcc_assert (సంకేతం_2 != FUNCTION_TYPE);
  ఒకవేళ (సంకేతం_2 == ARRAY_TYPE)
    తిరిగి ఘాతాంకం;

  /* Constants can be used directly unless they're not loadable.  */
  ఒకవేళ (వృక్షం_సంకేతం (ఘాతాంకం) == CONST_DECL)
    ఘాతాంకం = DECL_INITIAL (ఘాతాంకం);

  /* Strip no-op conversions.  */
  orig_exp = ఘాతాంకం;
  STRIP_TYPE_NOPS (ఘాతాంకం);

  copy_warning (ఘాతాంకం, orig_exp);

  ఒకవేళ (సంకేతం_2 == VOID_TYPE)
    {
      error_at (సమాసం_LOC_OR_LOC (ఘాతాంకం, ఆదానం_location),
		"void value not ignored as it ought to be");
      తిరిగి error_mark_కణుపు;
    }

  ఘాతాంకం = require_complete_type (సమాసం_LOC_OR_LOC (ఘాతాంకం, ఆదానం_location), ఘాతాంకం);
  ఒకవేళ (ఘాతాంకం == error_mark_కణుపు)
    తిరిగి error_mark_కణుపు;

  promoted_type = targetm.promoted_type (type);
  ఒకవేళ (promoted_type)
    తిరిగి convert (promoted_type, ఘాతాంకం);

  ఒకవేళ (INTEGRAL_TYPE_P (type))
    {
      /* Avoid performing integral promotion of bit-precise integer
	 type bit-field to its corresponding bit-precise integer if
	 orig_exp is a cast to it to its underlying type.  */
      ఒకవేళ (orig_exp != ఘాతాంకం
	  && వృక్షం_సంకేతం (ఘాతాంకం) == COMPONENT_REF
	  && DECL_C_బిట్టు_క్షేత్రం (వృక్షం_నిర్వాహ్యం (ఘాతాంకం, 1))
	  && BITINT_TYPE_P (DECL_బిట్టు_క్షేత్రం_TYPE (వృక్షం_నిర్వాహ్యం (ఘాతాంకం, 1))))
	తిరిగి perform_integral_promotions (orig_exp);
      తిరిగి perform_integral_promotions (ఘాతాంకం);
    }

  తిరిగి ఘాతాంకం;
}

/* Look up COMPONENT in a structure or union TYPE.

   If the component name is not found, returns NULL_TREE.  Otherwise,
   the return value is a TREE_LIST, with each TREE_VALUE a FIELD_DECL
   stepping down the chain to the component, which is in the last
   TREE_VALUE of the list.  Normally the list is of length one, but if
   the component is embedded within (nested) anonymous structures or
   unions, the list steps down the chain to the component.  */

వృక్షం
lookup_క్షేత్రం (const_వృక్షం type, వృక్షం component)
{
  వృక్షం క్షేత్రం_2;

  /* If TYPE_LANG_SPECIFIC is set, then it is a sorted array of pointers
     to the field elements.  Use a binary search on this array to quickly
     find the element.  Otherwise, do a linear search.  TYPE_LANG_SPECIFIC
     will always be set for structures which have many elements.

     Duplicate field checking replaces duplicates with NULL_TREE so
     TYPE_LANG_SPECIFIC arrays are potentially no longer sorted.  In that
     case just iterate using DECL_CHAIN.  */

  ఒకవేళ (TYPE_LANG_SPECIFIC (type) && TYPE_LANG_SPECIFIC (type)->s
      && !చూసిన_error ())
    {
      పూర్ణాంకం bot, శిఖరం, half;
      వృక్షం *క్షేత్రం_array = &TYPE_LANG_SPECIFIC (type)->s->elts[0];

      క్షేత్రం_2 = TYPE_FIELDS (type);
      bot = 0;
      శిఖరం = TYPE_LANG_SPECIFIC (type)->s->len;
      అయితే (శిఖరం - bot > 1)
	{
	  half = (శిఖరం - bot + 1) >> 1;
	  క్షేత్రం_2 = క్షేత్రం_array[bot+half];

	  ఒకవేళ (DECL_NAME (క్షేత్రం_2) == NULL_వృక్షం)
	    {
	      /* Step through all anon unions in linear fashion.  */
	      అయితే (DECL_NAME (క్షేత్రం_array[bot]) == NULL_వృక్షం)
		{
		  క్షేత్రం_2 = క్షేత్రం_array[bot++];
		  ఒకవేళ (రికార్డు_OR_UNION_TYPE_P (వృక్షం_TYPE (క్షేత్రం_2)))
		    {
		      వృక్షం anon = lookup_క్షేత్రం (వృక్షం_TYPE (క్షేత్రం_2), component);

		      ఒకవేళ (anon)
			తిరిగి వృక్షం_cons (NULL_వృక్షం, క్షేత్రం_2, anon);

		      /* The Plan 9 compiler permits referring
			 directly to an anonymous struct/union field
			 using a typedef name.  */
		      ఒకవేళ (flag_plan9_extensions
			  && TYPE_NAME (వృక్షం_TYPE (క్షేత్రం_2)) != NULL_వృక్షం
			  && (వృక్షం_సంకేతం (TYPE_NAME (వృక్షం_TYPE (క్షేత్రం_2)))
			      == TYPE_DECL)
			  && (DECL_NAME (TYPE_NAME (వృక్షం_TYPE (క్షేత్రం_2)))
			      == component))
			ఆపు;
		    }
		}

	      /* Entire record is only anon unions.  */
	      ఒకవేళ (bot > శిఖరం)
		తిరిగి NULL_వృక్షం;

	      /* Restart the binary search, with new lower bound.  */
	      కొనసాగు;
	    }

	  ఒకవేళ (DECL_NAME (క్షేత్రం_2) == component)
	    ఆపు;
	  ఒకవేళ (DECL_NAME (క్షేత్రం_2) < component)
	    bot += half;
	  లేకపోతే
	    శిఖరం = bot + half;
	}

      ఒకవేళ (DECL_NAME (క్షేత్రం_array[bot]) == component)
	క్షేత్రం_2 = క్షేత్రం_array[bot];
      లేకపోతే ఒకవేళ (DECL_NAME (క్షేత్రం_2) != component)
	తిరిగి NULL_వృక్షం;
    }
  లేకపోతే
    {
      కొరకు (క్షేత్రం_2 = TYPE_FIELDS (type); క్షేత్రం_2; క్షేత్రం_2 = DECL_CHAIN (క్షేత్రం_2))
	{
	  ఒకవేళ (DECL_NAME (క్షేత్రం_2) == NULL_వృక్షం
	      && రికార్డు_OR_UNION_TYPE_P (వృక్షం_TYPE (క్షేత్రం_2)))
	    {
	      వృక్షం anon = lookup_క్షేత్రం (వృక్షం_TYPE (క్షేత్రం_2), component);

	      ఒకవేళ (anon)
		తిరిగి వృక్షం_cons (NULL_వృక్షం, క్షేత్రం_2, anon);

	      /* The Plan 9 compiler permits referring directly to an
		 anonymous struct/union field using a typedef
		 name.  */
	      ఒకవేళ (flag_plan9_extensions
		  && TYPE_NAME (వృక్షం_TYPE (క్షేత్రం_2)) != NULL_వృక్షం
		  && వృక్షం_సంకేతం (TYPE_NAME (వృక్షం_TYPE (క్షేత్రం_2))) == TYPE_DECL
		  && (DECL_NAME (TYPE_NAME (వృక్షం_TYPE (క్షేత్రం_2)))
		      == component))
		ఆపు;
	    }

	  ఒకవేళ (DECL_NAME (క్షేత్రం_2) == component)
	    ఆపు;
	}

      ఒకవేళ (క్షేత్రం_2 == NULL_వృక్షం)
	తిరిగి NULL_వృక్షం;
    }

  తిరిగి వృక్షం_cons (NULL_వృక్షం, క్షేత్రం_2, NULL_వృక్షం);
}

/* Recursively append candidate IDENTIFIER_NODEs to CANDIDATES.  */

స్థిర శూన్య
lookup_క్షేత్రం_fuzzy_కనుగొను_candidates (వృక్షం type, వృక్షం component,
				    vec<వృక్షం> *candidates)
{
  వృక్షం క్షేత్రం_2;
  కొరకు (క్షేత్రం_2 = TYPE_FIELDS (type); క్షేత్రం_2; క్షేత్రం_2 = DECL_CHAIN (క్షేత్రం_2))
    {
      ఒకవేళ (DECL_NAME (క్షేత్రం_2) == NULL_వృక్షం
	  && రికార్డు_OR_UNION_TYPE_P (వృక్షం_TYPE (క్షేత్రం_2)))
	lookup_క్షేత్రం_fuzzy_కనుగొను_candidates (వృక్షం_TYPE (క్షేత్రం_2), component,
					    candidates);

      ఒకవేళ (DECL_NAME (క్షేత్రం_2))
	candidates->సురక్షిత_నెట్టు (DECL_NAME (క్షేత్రం_2));
    }
}

/* Like "lookup_field", but find the closest matching IDENTIFIER_NODE,
   rather than returning a TREE_LIST for an exact match.  */

స్థిర వృక్షం
lookup_క్షేత్రం_fuzzy (వృక్షం type, వృక్షం component)
{
  gcc_assert (వృక్షం_సంకేతం (component) == IDENTIFIER_కణుపు);

  /* First, gather a list of candidates.  */
  auto_vec <వృక్షం> candidates;

  lookup_క్షేత్రం_fuzzy_కనుగొను_candidates (type, component,
				      &candidates);

  తిరిగి కనుగొను_closest_identifier (component, &candidates);
}

/* Support function for build_component_ref's error-handling.

   Given DATUM_TYPE, and "DATUM.COMPONENT", where DATUM is *not* a
   struct or union, should we suggest "DATUM->COMPONENT" as a hint?  */

స్థిర తార్కిక
should_suggest_deref_p (వృక్షం datum_type)
{
  /* We don't do it for Objective-C, since Objective-C 2.0 dot-syntax
     allows "." for ptrs; we could be handling a failed attempt
     to access a property.  */
  ఒకవేళ (c_dialect_objc ())
    తిరిగి అబద్ధం;

  /* Only suggest it for pointers...  */
  ఒకవేళ (వృక్షం_సంకేతం (datum_type) != సూచిక_TYPE)
    తిరిగి అబద్ధం;

  /* ...to structs/unions.  */
  వృక్షం underlying_type = వృక్షం_TYPE (datum_type);
  గణన వృక్షం_సంకేతం_2 సంకేతం_2 = వృక్షం_సంకేతం (underlying_type);
  ఒకవేళ (సంకేతం_2 == రికార్డు_TYPE || సంకేతం_2 == UNION_TYPE)
    తిరిగి నిజం;
  లేకపోతే
    తిరిగి అబద్ధం;
}

/* Give a component ref REF, decide whether we should handle its counted_by
   attribute based on its context:
   Do not handle counted_by when in offsetof, typeof and alignof operator.  */

స్థిర తార్కిక
handle_counted_by_p (వృక్షం ref)
{
  gcc_assert (వృక్షం_సంకేతం (ref) == COMPONENT_REF);
  వృక్షం datum = వృక్షం_నిర్వాహ్యం (ref, 0);
  /* If the component_ref is build for a offsetof, i.e., the datum
     of the component_ref is a indirect_ref of null_pointer_node,
     we should not generate call to .ACCESS_WITH_SIZE.  */
  ఒకవేళ (వృక్షం_సంకేతం (datum) == పరోక్ష_REF
      && వృక్షం_నిర్వాహ్యం (datum, 0) == null_సూచిక_కణుపు)
    తిరిగి అబద్ధం;
  ఒకవేళ (లోపల_typeof || లోపల_alignof)
    తిరిగి అబద్ధం;
  తిరిగి నిజం;
}

/* Given a component ref REF, if there is a counted_by attribute attached,
   issue error when the element_type is a structure or union including a
   flexible array member.  */

స్థిర శూన్య
check_counted_by_attribute (location_t loc, వృక్షం ref)
{
  వృక్షం subdatum = వృక్షం_నిర్వాహ్యం (ref, 1);
  వృక్షం sub_type = వృక్షం_TYPE (subdatum);

  ఒకవేళ (!flexible_array_member_type_p (sub_type)
      && వృక్షం_సంకేతం (sub_type) != సూచిక_TYPE)
    తిరిగి;

  వృక్షం element_type = వృక్షం_TYPE (sub_type);

  వృక్షం attr_counted_by = lookup_attribute ("counted_by",
					   DECL_లక్షణాలు (subdatum));
  ఒకవేళ (attr_counted_by)
    {
      /* Issue error when the element_type is a structure or
	union including a flexible array member.  */
      ఒకవేళ (రికార్డు_OR_UNION_TYPE_P (element_type)
	  && TYPE_INCLUDES_FLEXARRAY (element_type))
	{
	  error_at (loc,
		    "%<counted_by%> attribute is not allowed for a pointer to"
		    " structure or union with flexible array member");
	  తిరిగి;
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

స్థిర వృక్షం
build_counted_by_ref (వృక్షం datum, వృక్షం subdatum,
		      వృక్షం *counted_by_type)
{
  వృక్షం sub_type = వృక్షం_TYPE (subdatum);
  ఒకవేళ (!flexible_array_member_type_p (sub_type)
      && వృక్షం_సంకేతం (sub_type) != సూచిక_TYPE)
    తిరిగి NULL_వృక్షం;

  వృక్షం attr_counted_by = lookup_attribute ("counted_by",
					   DECL_లక్షణాలు (subdatum));
  ఒకవేళ (!attr_counted_by)
    తిరిగి NULL_వృక్షం;

  వృక్షం counted_by_ref = NULL_వృక్షం;
  *counted_by_type = NULL_వృక్షం;

  వృక్షం type = వృక్షం_TYPE (datum);

  /* If the type of the containing structure is an anonymous struct/union,
     and this anonymous struct/union is not a root type, get the first
     outer named structure/union type.  */
  అయితే (వృక్షం_సంకేతం (datum) == COMPONENT_REF
	 && c_type_ట్యాగ్ (type) == NULL_వృక్షం
	 && DECL_NAME (వృక్షం_నిర్వాహ్యం (datum, 1)) == NULL_వృక్షం)
    {
      datum = వృక్షం_నిర్వాహ్యం (datum, 0);
      type = వృక్షం_TYPE (datum);
    }

  వృక్షం క్షేత్రం_id = వృక్షం_విలువ (వృక్షం_విలువ (attr_counted_by));
  వృక్షం counted_by_క్షేత్రం = lookup_క్షేత్రం (type, క్షేత్రం_id);
  gcc_assert (counted_by_క్షేత్రం);

  వృక్షం counted_by_subdatum;
  చేయి
    {
      counted_by_subdatum = వృక్షం_విలువ (counted_by_క్షేత్రం);
      /* Get the TYPE of the counted_by field.  */
      *counted_by_type = వృక్షం_TYPE (counted_by_subdatum);

      counted_by_ref
	= build3 (COMPONENT_REF, వృక్షం_TYPE (counted_by_subdatum),
		  datum, counted_by_subdatum, NULL_వృక్షం);

      datum = counted_by_ref;
      counted_by_క్షేత్రం = వృక్షం_CHAIN (counted_by_క్షేత్రం);
    }
  అయితే (counted_by_క్షేత్రం);

  counted_by_ref = build_fold_addr_సమాసం (counted_by_ref);
  తిరిగి counted_by_ref;
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
స్థిర వృక్షం
build_access_with_కొలత_for_counted_by (location_t loc, వృక్షం ref,
				       వృక్షం counted_by_ref,
				       వృక్షం counted_by_type)
{
  gcc_assert (flexible_array_member_type_p (వృక్షం_TYPE (ref))
	      || వృక్షం_సంకేతం (వృక్షం_TYPE (ref)) == సూచిక_TYPE);

  తార్కిక is_fam = flexible_array_member_type_p (వృక్షం_TYPE (ref));

  /* The result type of the call is a pointer to the flexible array type;
     or is the original pointer type to the pointer field with counted_by.  */
  వృక్షం ఫలితం_type = is_fam ? c_build_సూచిక_type (వృక్షం_TYPE (ref))
		     : వృక్షం_TYPE (ref);

  వృక్షం element_type = వృక్షం_TYPE (వృక్షం_TYPE (ref));
  వృక్షం element_కొలత = VOID_TYPE_P (element_type)
		      ? కొలత_one_కణుపు
		      : TYPE_కొలత_UNIT (element_type);
  ఒకవేళ (element_కొలత == NULL_వృక్షం)
    తిరిగి ref;

  వృక్షం మొదటి_param = is_fam
		     ? c_fully_fold (array_గమ్యం_సూచిక_conversion (loc, ref),
				     అబద్ధం, ఖాళీ)
		     : c_fully_fold (ref, అబద్ధం, ఖాళీ);
  వృక్షం రెండవ_param
    = c_fully_fold (counted_by_ref, అబద్ధం, ఖాళీ);
  వృక్షం మూడవ_param = build_int_cst (c_build_సూచిక_type (counted_by_type), 0);

  వృక్షం call
    = build_call_సమాసం_అంతర్గత_loc (loc, IFN_ACCESS_WITH_కొలత,
				    ఫలితం_type, 4,
				    మొదటి_param,
				    రెండవ_param,
				    మూడవ_param,
				    element_కొలత);

  /* Wrap the call with an INDIRECT_REF with the flexible array type.  */
  ఒకవేళ (is_fam)
    call = build1 (పరోక్ష_REF, వృక్షం_TYPE (ref), call);
  సమితి_సమాసం_LOCATION (call, loc);
  తిరిగి call;
}

/* For the COMPONENT_REF ref, check whether it has a counted_by attribute,
   if so, wrap this COMPONENT_REF with the corresponding CALL to the
   function .ACCESS_WITH_SIZE.
   Otherwise, return the ref itself.  */

వృక్షం
handle_counted_by_for_component_ref (location_t loc, వృక్షం ref)
{
  gcc_assert (వృక్షం_సంకేతం (ref) == COMPONENT_REF);
  వృక్షం datum = వృక్షం_నిర్వాహ్యం (ref, 0);
  వృక్షం subdatum = వృక్షం_నిర్వాహ్యం (ref, 1);
  వృక్షం counted_by_type = NULL_వృక్షం;

  ఒకవేళ (!(flexible_array_member_type_p (వృక్షం_TYPE (ref))
	|| వృక్షం_సంకేతం (వృక్షం_TYPE (ref)) == సూచిక_TYPE))
    తిరిగి ref;

  వృక్షం counted_by_ref = build_counted_by_ref (datum, subdatum,
					      &counted_by_type);
  ఒకవేళ (counted_by_ref)
    ref = build_access_with_కొలత_for_counted_by (loc, ref,
						 counted_by_ref,
						 counted_by_type);
  తిరిగి ref;
}

/* Make an expression to refer to the COMPONENT field of structure or
   union value DATUM.  COMPONENT is an IDENTIFIER_NODE.  LOC is the
   location of the COMPONENT_REF.  COMPONENT_LOC is the location
   of COMPONENT.  ARROW_LOC is the location of the first -> operand if
   it is from -> operator.
   If HANDLE_COUNTED_BY is true, check the counted_by attribute and generate
   a call to .ACCESS_WITH_SIZE.  Otherwise, ignore the attribute.  */

వృక్షం
build_component_ref (location_t loc, వృక్షం datum, వృక్షం component,
		     location_t component_loc, location_t arrow_loc)
{
  వృక్షం type = వృక్షం_TYPE (datum);
  గణన వృక్షం_సంకేతం_2 సంకేతం_2 = వృక్షం_సంకేతం (type);
  వృక్షం క్షేత్రం_2 = ఖాళీ;
  వృక్షం ref;
  తార్కిక datum_lvalue = lvalue_p (datum);

  ఒకవేళ (!objc_is_ప్రజా (datum, component))
    తిరిగి error_mark_కణుపు;

  /* Detect Objective-C property syntax object.property.  */
  ఒకవేళ (c_dialect_objc ()
      && (ref = objc_maybe_build_component_ref (datum, component)))
    తిరిగి ref;

  /* See if there is a field or component with name COMPONENT.  */

  ఒకవేళ (సంకేతం_2 == రికార్డు_TYPE || సంకేతం_2 == UNION_TYPE)
    {
      ఒకవేళ (!COMPLETE_TYPE_P (type))
	{
	  c_incomplete_type_error (loc, NULL_వృక్షం, type);
	  తిరిగి error_mark_కణుపు;
	}

      క్షేత్రం_2 = lookup_క్షేత్రం (type, component);

      ఒకవేళ (!క్షేత్రం_2)
	{
	  వృక్షం guessed_id = lookup_క్షేత్రం_fuzzy (type, component);
	  ఒకవేళ (guessed_id)
	    {
	      /* Attempt to provide a fixit replacement hint, if
		 we have a valid range for the component.  */
	      location_t reported_loc
		= (component_loc != UNKNOWN_LOCATION) ? component_loc : loc;
	      gcc_rich_location rich_loc (reported_loc);
	      ఒకవేళ (component_loc != UNKNOWN_LOCATION)
		rich_loc.కూడు_fixit_misspelled_id (component_loc, guessed_id);
	      error_at (&rich_loc,
			"%qT has no member named %qE; did you mean %qE?",
			type, component, guessed_id);
	    }
	  లేకపోతే
	    error_at (loc, "%qT has no member named %qE", type, component);
	  తిరిగి error_mark_కణుపు;
	}

      /* Accessing elements of atomic structures or unions is undefined
	 behavior (C11 6.5.2.3#5).  */
      ఒకవేళ (TYPE_ATOMIC (type) && c_inhibit_evaluation_warnings == 0)
	{
	  ఒకవేళ (సంకేతం_2 == రికార్డు_TYPE)
	    warning_at (loc, 0, "accessing a member %qE of an atomic "
			"structure %qE", component, datum);
	  లేకపోతే
	    warning_at (loc, 0, "accessing a member %qE of an atomic "
			"union %qE", component, datum);
	}

      /* Chain the COMPONENT_REFs if necessary down to the FIELD.
	 This might be better solved in future the way the C++ front
	 end does it - by giving the anonymous entities each a
	 separate name and type, and then have build_component_ref
	 recursively call itself.  We can't do that here.  */
      చేయి
	{
	  వృక్షం subdatum = వృక్షం_విలువ (క్షేత్రం_2);
	  పూర్ణాంకం quals;
	  వృక్షం subtype;
	  తార్కిక use_datum_quals;

	  ఒకవేళ (వృక్షం_TYPE (subdatum) == error_mark_కణుపు)
	    తిరిగి error_mark_కణుపు;

	  /* If this is an rvalue, it does not have qualifiers in C
	     standard terms and we must avoid propagating such
	     qualifiers down to a non-lvalue array that is then
	     converted to a pointer.  */
	  use_datum_quals = (datum_lvalue
			     || వృక్షం_సంకేతం (వృక్షం_TYPE (subdatum)) != ARRAY_TYPE);

	  quals = TYPE_QUALS (strip_array_types (వృక్షం_TYPE (subdatum)));
	  ఒకవేళ (use_datum_quals)
	    quals |= TYPE_QUALS (వృక్షం_TYPE (datum));
	  subtype = c_build_qualified_type (వృక్షం_TYPE (subdatum), quals);

	  ref = build3 (COMPONENT_REF, subtype, datum, subdatum,
			NULL_వృక్షం);
	  సమితి_సమాసం_LOCATION (ref, loc);

	  check_counted_by_attribute (loc, ref);

	  ఒకవేళ (వృక్షం_READONLY (subdatum)
	      || (use_datum_quals && వృక్షం_READONLY (datum)))
	    వృక్షం_READONLY (ref) = 1;
	  ఒకవేళ (వృక్షం_THIS_VOLATILE (subdatum)
	      || (use_datum_quals && వృక్షం_THIS_VOLATILE (datum)))
	    వృక్షం_THIS_VOLATILE (ref) = 1;

	  ఒకవేళ (వృక్షం_UNAVAILABLE (subdatum))
	    error_unavailable_use (subdatum, NULL_వృక్షం);
	  లేకపోతే ఒకవేళ (వృక్షం_DEPRECATED (subdatum))
	    warn_deprecated_use (subdatum, NULL_వృక్షం);

	  datum = ref;

	  క్షేత్రం_2 = వృక్షం_CHAIN (క్షేత్రం_2);
	}
      అయితే (క్షేత్రం_2);

      తిరిగి ref;
    }
  లేకపోతే ఒకవేళ (should_suggest_deref_p (type))
    {
      /* Special-case the error message for "ptr.field" for the case
	 where the user has confused "." vs "->".  */
      rich_location richloc (పంక్తి_పట్టిక, loc);
      ఒకవేళ (పరోక్ష_REF_P (datum) && arrow_loc != UNKNOWN_LOCATION)
	{
	  richloc.కూడు_fixit_చొప్పించు_before (arrow_loc, "(*");
	  richloc.కూడు_fixit_చొప్పించు_after (arrow_loc, ")");
	  error_at (&richloc,
		    "%qE is a pointer to pointer; did you mean to dereference "
		    "it before applying %<->%> to it?",
		    వృక్షం_నిర్వాహ్యం (datum, 0));
	}
      లేకపోతే
	{
	  /* "loc" should be the "." token.  */
	  richloc.కూడు_fixit_replace ("->");
	  error_at (&richloc,
		    "%qE is a pointer; did you mean to use %<->%>?",
		    datum);
	}
      తిరిగి error_mark_కణుపు;
    }
  లేకపోతే ఒకవేళ (సంకేతం_2 != ERROR_MARK)
    error_at (loc,
	      "request for member %qE in something not a structure or union",
	      component);

  తిరిగి error_mark_కణుపు;
}

/* Given an expression PTR for a pointer, return an expression
   for the value pointed to.
   ERRORSTRING is the name of the operator to appear in error messages.

   LOC is the location to use for the generated tree.  */

వృక్షం
build_పరోక్ష_ref (location_t loc, వృక్షం ptr, ref_operator errstring)
{
  వృక్షం సూచిక = default_conversion (ptr);
  వృక్షం type = వృక్షం_TYPE (సూచిక);
  వృక్షం ref;

  ఒకవేళ (వృక్షం_సంకేతం (type) == సూచిక_TYPE)
    {
      ఒకవేళ (CONVERT_సమాసం_P (సూచిక)
          || వృక్షం_సంకేతం (సూచిక) == VIEW_CONVERT_సమాసం)
	{
	  /* If a warning is issued, mark it to avoid duplicates from
	     the backend.  This only needs to be done at
	     warn_strict_aliasing > 2.  */
	  ఒకవేళ (warn_strict_aliasing > 2)
	    ఒకవేళ (strict_aliasing_warning (సమాసం_LOCATION (సూచిక),
					 type, వృక్షం_నిర్వాహ్యం (సూచిక, 0)))
	      suppress_warning (సూచిక, OPT_Wstrict_aliasing_);
	}

      ఒకవేళ (వృక్షం_సంకేతం (సూచిక) == ADDR_సమాసం
	  && (వృక్షం_TYPE (వృక్షం_నిర్వాహ్యం (సూచిక, 0))
	      == వృక్షం_TYPE (type)))
	{
	  ref = వృక్షం_నిర్వాహ్యం (సూచిక, 0);
	  protected_సమితి_సమాసం_location (ref, loc);
	  తిరిగి ref;
	}
      లేకపోతే
	{
	  వృక్షం t = వృక్షం_TYPE (type);

	  ref = build1 (పరోక్ష_REF, t, సూచిక);

	  ఒకవేళ (VOID_TYPE_P (t) && c_inhibit_evaluation_warnings == 0)
	    warning_at (loc, 0, "dereferencing %<void *%> pointer");

	  /* We *must* set TREE_READONLY when dereferencing a pointer to const,
	     so that we get the proper error message if the result is used
	     to assign to.  Also, &* is supposed to be a no-op.
	     And ANSI C seems to specify that the type of the result
	     should be the const type.  */
	  /* A de-reference of a pointer to const is not a const.  It is valid
	     to change it via some other pointer.  */
	  వృక్షం_READONLY (ref) = TYPE_READONLY (t);
	  వృక్షం_SIDE_EFFECTS (ref)
	    = TYPE_VOLATILE (t) || వృక్షం_SIDE_EFFECTS (సూచిక);
	  వృక్షం_THIS_VOLATILE (ref) = TYPE_VOLATILE (t);
	  protected_సమితి_సమాసం_location (ref, loc);
	  తిరిగి ref;
	}
    }
  లేకపోతే ఒకవేళ (వృక్షం_సంకేతం (సూచిక) != ERROR_MARK)
    invalid_indirection_error (loc, type, errstring);

  తిరిగి error_mark_కణుపు;
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

వృక్షం
build_array_ref (location_t loc, వృక్షం array, వృక్షం సూచీ)
{
  వృక్షం ret;
  తార్కిక swapped = అబద్ధం;
  ఒకవేళ (వృక్షం_TYPE (array) == error_mark_కణుపు
      || వృక్షం_TYPE (సూచీ) == error_mark_కణుపు)
    తిరిగి error_mark_కణుపు;

  ఒకవేళ (వృక్షం_సంకేతం (వృక్షం_TYPE (array)) != ARRAY_TYPE
      && వృక్షం_సంకేతం (వృక్షం_TYPE (array)) != సూచిక_TYPE
      /* Allow vector[index] but not index[vector].  */
      && !gnu_సదిశ_type_p (వృక్షం_TYPE (array)))
    {
      ఒకవేళ (వృక్షం_సంకేతం (వృక్షం_TYPE (సూచీ)) != ARRAY_TYPE
	  && వృక్షం_సంకేతం (వృక్షం_TYPE (సూచీ)) != సూచిక_TYPE)
	{
          error_at (loc,
            "subscripted value is neither array nor pointer nor vector");

	  తిరిగి error_mark_కణుపు;
	}
      std::మార్పిడి (array, సూచీ);
      swapped = నిజం;
    }

  ఒకవేళ (!INTEGRAL_TYPE_P (వృక్షం_TYPE (సూచీ)))
    {
      error_at (loc, "array subscript is not an integer");
      తిరిగి error_mark_కణుపు;
    }

  ఒకవేళ (వృక్షం_సంకేతం (వృక్షం_TYPE (వృక్షం_TYPE (array))) == FUNCTION_TYPE)
    {
      error_at (loc, "subscripted value is pointer to function");
      తిరిగి error_mark_కణుపు;
    }

  /* ??? Existing practice has been to warn only when the char
     index is syntactically the index, not for char[array].  */
  ఒకవేళ (!swapped)
     warn_array_subscript_with_type_char (loc, సూచీ);

  /* Apply default promotions *after* noticing character types.  */
  సూచీ = default_conversion (సూచీ);
  ఒకవేళ (సూచీ == error_mark_కణుపు)
    తిరిగి error_mark_కణుపు;

  gcc_assert (వృక్షం_సంకేతం (వృక్షం_TYPE (సూచీ)) == INTEGER_TYPE
	      || వృక్షం_సంకేతం (వృక్షం_TYPE (సూచీ)) == BITINT_TYPE);

  తార్కిక was_సదిశ = సదిశ_TYPE_P (వృక్షం_TYPE (array));
  తార్కిక non_lvalue = convert_సదిశ_గమ్యం_array_for_subscript (loc, &array, సూచీ);

  /* We only generate a call to .ACCESS_WITH_SIZE when it is a read.  */
  ఒకవేళ (వృక్షం_సంకేతం (array) == COMPONENT_REF
      && handle_counted_by_p (array))
    array = handle_counted_by_for_component_ref (loc, array);

  ఒకవేళ (వృక్షం_సంకేతం (వృక్షం_TYPE (array)) == ARRAY_TYPE)
    {
      వృక్షం rval, type;

      /* An array that is indexed by a non-constant
	 cannot be stored in a register; we must be able to do
	 address arithmetic on its address.
	 Likewise an array of elements of variable size.  */
      ఒకవేళ (వృక్షం_సంకేతం (సూచీ) != INTEGER_CST
	  || (COMPLETE_TYPE_P (వృక్షం_TYPE (వృక్షం_TYPE (array)))
	      && వృక్షం_సంకేతం (TYPE_కొలత (వృక్షం_TYPE (వృక్షం_TYPE (array)))) != INTEGER_CST))
	{
	  ఒకవేళ (!c_mark_addressable (array, నిజం, నిజం))
	    తిరిగి error_mark_కణుపు;
	}
      /* An array that is indexed by a constant value which is not within
	 the array bounds cannot be stored in a register either; because we
	 would get a crash in store_bit_field/extract_bit_field when trying
	 to access a non-existent part of the register.  */
      ఒకవేళ (వృక్షం_సంకేతం (సూచీ) == INTEGER_CST
	  && TYPE_DOMAIN (వృక్షం_TYPE (array))
	  && !int_సరిపోతుంది_type_p (సూచీ, TYPE_DOMAIN (వృక్షం_TYPE (array))))
	{
	  ఒకవేళ (!c_mark_addressable (array, అబద్ధం, నిజం))
	    తిరిగి error_mark_కణుపు;
	  /* ISO C2Y disallows a negative integer constant expression index
	     when array subscripting has an operand of array type.  */
	  ఒకవేళ (flag_isoc2y
	      && !వృక్షం_అధికప్రవాహం (సూచీ)
	      && వృక్షం_int_cst_sgn (సూచీ) < 0)
	    error_at (loc, "array subscript is negative");
	}

      ఒకవేళ ((pedantic || warn_c90_c99_compat || warn_c23_c2y_compat)
	  && ! was_సదిశ)
	{
	  వృక్షం foo = array;
	  అయితే (వృక్షం_సంకేతం (foo) == COMPONENT_REF)
	    foo = వృక్షం_నిర్వాహ్యం (foo, 0);
	  ఒకవేళ ((VAR_P (foo) && C_DECL_రిజిస్టరు (foo))
	      || (వృక్షం_సంకేతం (foo) == COMPOUND_LITERAL_సమాసం
		  && C_DECL_రిజిస్టరు (COMPOUND_LITERAL_సమాసం_DECL (foo))))
	    pedwarn_c23 (loc, OPT_Wpedantic,
			 "ISO C forbids subscripting %<register%> array "
			 "before C2Y");
	  లేకపోతే ఒకవేళ (!lvalue_p (foo))
	    pedwarn_c90 (loc, OPT_Wpedantic,
			 "ISO C90 forbids subscripting non-lvalue "
			 "array");
	}

      ఒకవేళ (వృక్షం_సంకేతం (వృక్షం_TYPE (సూచీ)) == BITINT_TYPE
	  && TYPE_PRECISION (వృక్షం_TYPE (సూచీ)) > TYPE_PRECISION (sizetype))
	సూచీ = fold_convert (sizetype, సూచీ);

      type = వృక్షం_TYPE (వృక్షం_TYPE (array));
      rval = build4 (ARRAY_REF, type, array, సూచీ, NULL_వృక్షం, NULL_వృక్షం);
      /* Array ref is const/volatile if the array elements are
	 or if the array is.  */
      వృక్షం_READONLY (rval)
	|= (TYPE_READONLY (వృక్షం_TYPE (వృక్షం_TYPE (array)))
	    | వృక్షం_READONLY (array));
      వృక్షం_SIDE_EFFECTS (rval)
	|= (TYPE_VOLATILE (వృక్షం_TYPE (వృక్షం_TYPE (array)))
	    | వృక్షం_SIDE_EFFECTS (array));
      వృక్షం_THIS_VOLATILE (rval)
	|= (TYPE_VOLATILE (వృక్షం_TYPE (వృక్షం_TYPE (array)))
	    /* This was added by rms on 16 Nov 91.
	       It fixes  vol struct foo *a;  a->elts[1]
	       in an inline function.
	       Hope it doesn't break something else.  */
	    | వృక్షం_THIS_VOLATILE (array));
      ret = require_complete_type (loc, rval);
      protected_సమితి_సమాసం_location (ret, loc);
      ఒకవేళ (non_lvalue)
	ret = non_lvalue_loc (loc, ret);
      తిరిగి ret;
    }
  లేకపోతే
    {
      వృక్షం ar = default_conversion (array);

      ఒకవేళ (ar == error_mark_కణుపు)
	తిరిగి ar;

      gcc_assert (వృక్షం_సంకేతం (వృక్షం_TYPE (ar)) == సూచిక_TYPE);
      gcc_assert (వృక్షం_సంకేతం (వృక్షం_TYPE (వృక్షం_TYPE (ar))) != FUNCTION_TYPE);

      ret = build_పరోక్ష_ref (loc, build_ద్విమాన_op (loc, PLUS_సమాసం, ar,
						      సూచీ, అబద్ధం),
				RO_ARRAY_INDEXING);
      ఒకవేళ (non_lvalue)
	ret = non_lvalue_loc (loc, ret);
      తిరిగి ret;
    }
}

/* Build an OpenMP array section reference, creating an exact type for the
   resulting expression based on the element type and bounds if possible.  If
   we have variable bounds, create an incomplete array type for the result
   instead.  */

వృక్షం
build_omp_array_section (location_t loc, వృక్షం array, వృక్షం సూచీ, వృక్షం నిడివి)
{
  వృక్షం type = వృక్షం_TYPE (array);
  gcc_assert (type);

  వృక్షం sectype, eltype = వృక్షం_TYPE (type);

  /* It's not an array or pointer type.  Just reuse the type of the original
     expression as the type of the array section (an error will be raised
     anyway, later).  */
  ఒకవేళ (eltype == NULL_వృక్షం || error_నిర్వాహ్యం_p (eltype))
    sectype = వృక్షం_TYPE (array);
  లేకపోతే
    {
      వృక్షం idxtype = NULL_వృక్షం;

      ఒకవేళ (సూచీ != NULL_వృక్షం
	  && నిడివి != NULL_వృక్షం
	  && INTEGRAL_TYPE_P (వృక్షం_TYPE (సూచీ))
	  && INTEGRAL_TYPE_P (వృక్షం_TYPE (నిడివి)))
	{
	  వృక్షం దిగువ = fold_convert (sizetype, సూచీ);
	  వృక్షం ఎగువ = fold_convert (sizetype, నిడివి);
	  ఎగువ = కొలత_binop (PLUS_సమాసం, దిగువ, ఎగువ);
	  ఎగువ = కొలత_binop (MINUS_సమాసం, ఎగువ, కొలత_one_కణుపు);
	  idxtype = build_range_type (sizetype, దిగువ, ఎగువ);
	}
      లేకపోతే ఒకవేళ ((సూచీ == NULL_వృక్షం || integer_zerop (సూచీ))
	       && నిడివి != NULL_వృక్షం
	       && INTEGRAL_TYPE_P (వృక్షం_TYPE (నిడివి)))
	idxtype = build_సూచీ_type (నిడివి);

      gcc_assert (!error_నిర్వాహ్యం_p (idxtype));

      sectype = c_build_array_type (eltype, idxtype);
    }

  తిరిగి build3_loc (loc, OMP_ARRAY_SECTION, sectype, array, సూచీ, నిడివి);
}


/* Record that REF is used.  This is relevant for undeclared static
   function and declarations referenced from a non-local context.
   ADDRESS indicates whether the address is taken.  */

శూన్య
mark_decl_వాడిన (వృక్షం ref, తార్కిక చిరునామా)
{
  ఒకవేళ (!ref || !DECL_P (ref) || లోపల_alignof)
    తిరిగి;

  /* Non-file-scope and non-local reference in nested function.  */
  తార్కిక nonloc_p = current_function_decl && DECL_CONTEXT (ref)
		  && DECL_CONTEXT (current_function_decl)
		  && DECL_CONTEXT (ref) != current_function_decl;

  /* An undeclared static function.  */
  తార్కిక static_p = వృక్షం_సంకేతం (ref) == FUNCTION_DECL
		  && DECL_INITIAL (ref) == NULL_వృక్షం
		  && DECL_EXTERNAL (ref)
		  && !వృక్షం_ప్రజా (ref);

  ఒకవేళ (!static_p && !nonloc_p)
    తిరిగి;

  /* If we may be in an unevaluated context, delay the decision.  */
  ఒకవేళ (లోపల_sizeof || లోపల_typeof || లోపల_countof || లోపల_generic)
    తిరిగి రికార్డు_maybe_వాడిన_decl (ref, చిరునామా);

  ఒకవేళ (static_p)
    C_DECL_వాడిన (ref) = 1;

  ఒకవేళ (nonloc_p && (VAR_OR_FUNCTION_DECL_P (ref)
		   || వృక్షం_సంకేతం (ref) == PARM_DECL))
    DECL_NONLOCAL (ref) = 1;

  /* Nothing to do anymore.  */
  ఒకవేళ (!nonloc_p || C_FUNC_NONLOCAL_CONTEXT (current_function_decl))
    తిరిగి;

  /* Filter out the cases where referencing a non-local variable does not
     require a non-local context passed via the static chain.  */
  ఒకవేళ (!c_type_variably_modified_p (వృక్షం_TYPE (ref)))
    ఎంపిక (వృక్షం_సంకేతం (ref))
      {
      స్థితి FUNCTION_DECL:
	/* Use of another local function that requires no context is ok.  */
	ఒకవేళ (!C_FUNC_NONLOCAL_CONTEXT (ref) && DECL_INITIAL (ref))
	  తిరిగి;
	ఆపు;
      స్థితి VAR_DECL:
	/* Static variables and constexpr are ok, but for the later only
	   when the address is not taken.  */
	ఒకవేళ (వృక్షం_STATIC (ref) || (C_DECL_DECLARED_CONSTEXPR (ref) && !చిరునామా))
	  తిరిగి;
	ఆపు;
      స్థితి TYPE_DECL:
	/* A typedef is ok when not for a variably-modified type. */
	తిరిగి;
      స్థితి CONST_DECL:
	/* An enumeration constant is ok. */
	తిరిగి;
      స్థితి PARM_DECL:
	ఆపు;
      స్థితి LABEL_DECL:
	ఆపు;
      అప్రమేయ:
	gcc_unreachable ();
    }

  /* Mark all parent functions up to the nesting level of the variable as
     as needing the non-local context.  */
  కొరకు (వృక్షం cont = current_function_decl; cont; cont = DECL_CONTEXT (cont))
    {
      ఒకవేళ (cont == DECL_CONTEXT (ref))
	ఆపు;

      /* There should not be any other type of context used for function
	 except TRANSLATION_UNIT_DECL which we should be able to reach.  */
      gcc_checking_assert (వృక్షం_సంకేతం (cont) == FUNCTION_DECL);

      ఒకవేళ (వృక్షం_సంకేతం (cont) == FUNCTION_DECL)
	C_FUNC_NONLOCAL_CONTEXT (cont) = 1;
    }
}


/* Build an external reference to identifier ID.  FUN indicates
   whether this will be used for a function call.  LOC is the source
   location of the identifier.  This sets *TYPE to the type of the
   identifier, which is not the same as the type of the returned value
   for CONST_DECLs defined as enum constants.  If the type of the
   identifier is not available, *TYPE is set to NULL.  */
వృక్షం
build_external_ref (location_t loc, వృక్షం id, తార్కిక fun, వృక్షం *type)
{
  వృక్షం ref;
  వృక్షం decl = lookup_name (id);

  /* In Objective-C, an instance variable (ivar) may be preferred to
     whatever lookup_name() found.  */
  decl = objc_lookup_ivar (decl, id);

  *type = ఖాళీ;
  ఒకవేళ (decl && decl != error_mark_కణుపు)
    {
      ref = decl;
      *type = వృక్షం_TYPE (ref);
      ఒకవేళ (DECL_P (decl) && C_DECL_UNDERSPECIFIED (decl))
	error_at (loc, "underspecified %qD referenced in its initializer",
		  decl);
    }
  లేకపోతే ఒకవేళ (fun)
    /* Implicit function declaration.  */
    ref = implicitly_declare (loc, id);
  లేకపోతే ఒకవేళ (decl == error_mark_కణుపు)
    /* Don't complain about something that's already been
       complained about.  */
    తిరిగి error_mark_కణుపు;
  లేకపోతే
    {
      undeclared_variable (loc, id);
      తిరిగి error_mark_కణుపు;
    }

  /* For an OpenMP map clause, we can get better diagnostics for decls with
     unmappable types if we return the decl with an error_mark_node type,
     rather than returning error_mark_node for the decl itself.  */
  ఒకవేళ (వృక్షం_TYPE (ref) == error_mark_కణుపు
      && !c_omp_array_section_p)
    తిరిగి error_mark_కణుపు;

  ఒకవేళ (వృక్షం_UNAVAILABLE (ref))
    error_unavailable_use (ref, NULL_వృక్షం);
  లేకపోతే ఒకవేళ (వృక్షం_DEPRECATED (ref))
    warn_deprecated_use (ref, NULL_వృక్షం);

  /* Recursive call does not count as usage.  */
  ఒకవేళ (ref != current_function_decl)
    {
      వృక్షం_వాడిన (ref) = 1;
    }

  mark_decl_వాడిన (ref, అబద్ధం);

  ఒకవేళ (వృక్షం_సంకేతం (ref) == CONST_DECL)
    {
      వాడిన_types_చొప్పించు (వృక్షం_TYPE (ref));

      ఒకవేళ (warn_cxx_compat
	  && వృక్షం_సంకేతం (వృక్షం_TYPE (ref)) == ENUMERAL_TYPE
	  && C_TYPE_DEFINED_లోపల_STRUCT (వృక్షం_TYPE (ref)))
	{
	  warning_at (loc, OPT_Wc___compat,
		      "enum constant defined in struct or union "
		      "is not visible in C++");
	  inform (DECL_ఆధారం_LOCATION (ref), "enum constant defined here");
	}

      ref = DECL_INITIAL (ref);
      వృక్షం_CONSTANT (ref) = 1;
    }
  /* C99 6.7.4p3: An inline definition of a function with external
     linkage ... shall not contain a reference to an identifier with
     internal linkage.  */
  లేకపోతే ఒకవేళ (current_function_decl != NULL_వృక్షం
	   && DECL_DECLARED_INLINE_P (current_function_decl)
	   && DECL_EXTERNAL (current_function_decl)
	   && VAR_OR_FUNCTION_DECL_P (ref)
	   && (!VAR_P (ref) || వృక్షం_STATIC (ref))
	   && ! వృక్షం_ప్రజా (ref)
	   && DECL_CONTEXT (ref) != current_function_decl)
    రికార్డు_inline_static (loc, current_function_decl, ref,
			  csi_అంతర్గత);

  తిరిగి ref;
}

స్థిర నిర్మాణం maybe_వాడిన_decl *maybe_వాడిన_decls;

/* Record that DECL, a reference seen inside sizeof or typeof or _Countof or
   _Generic, might be used if the operand of sizeof is a VLA type or the
   operand of typeof is a variably modified type or the operand of _Countof has
   a variable number of elements or the operand of _Generic is the one selected
   as the result.  */

స్థిర శూన్య
రికార్డు_maybe_వాడిన_decl (వృక్షం decl, తార్కిక చిరునామా)
{
  నిర్మాణం maybe_వాడిన_decl *t = XOBNEW (&parser_obstack, నిర్మాణం maybe_వాడిన_decl);
  t->decl = decl;
  t->level = లోపల_sizeof + లోపల_typeof + లోపల_countof + లోపల_generic;
  t->చిరునామా = చిరునామా;
  t->తదుపరి = maybe_వాడిన_decls;
  maybe_వాడిన_decls = t;
}

/* Pop the stack of decls possibly used inside sizeof or typeof or _Countof or
   _Generic.  If USED is false, just discard them.  If it is true, mark them
   used (if no longer inside sizeof or typeof or _Countof or _Generic) or move
   them to the next level up (if still inside sizeof or typeof or _Countof or
   _Generic).  */

శూన్య
తీయి_maybe_వాడిన (తార్కిక వాడిన)
{
  నిర్మాణం maybe_వాడిన_decl *p = maybe_వాడిన_decls;
  పూర్ణాంకం cur_level = లోపల_sizeof + లోపల_typeof + లోపల_countof + లోపల_generic;
  అయితే (p && p->level > cur_level)
    {
      ఒకవేళ (వాడిన)
	{
	  ఒకవేళ (cur_level == 0)
	    mark_decl_వాడిన (p->decl, p->చిరునామా);
	  లేకపోతే
	    p->level = cur_level;
	}
      p = p->తదుపరి;
    }
  ఒకవేళ (!వాడిన || cur_level == 0)
    maybe_వాడిన_decls = p;
}

/* Pop the stack of decls possibly used inside sizeof or typeof or _Countof or
   _Generic, without acting on them, and return the pointer to the previous top
   of the stack.  This for use at the end of a default generic association when
   it is not yet known whether the expression is used.  If it later turns out
   the expression is used (or treated as used before C23), restore_maybe_used
   should be called on the return value followed by pop_maybe_used (true);
   otherwise, the return value can be discarded.  */

నిర్మాణం maybe_వాడిన_decl *
save_maybe_వాడిన ()
{
  నిర్మాణం maybe_వాడిన_decl *p = maybe_వాడిన_decls, *orig = p;
  పూర్ణాంకం cur_level = లోపల_sizeof + లోపల_typeof + లోపల_countof + లోపల_generic;
  అయితే (p && p->level > cur_level)
    p = p->తదుపరి;
  maybe_వాడిన_decls = p;
  తిరిగి orig;
}

/* Restore the stack of decls possibly used inside sizeof or typeof or _Countof
   or _Generic returned by save_maybe_used.  It is required that the stack is
   at exactly the point where it was left by save_maybe_used.  */

శూన్య
restore_maybe_వాడిన (నిర్మాణం maybe_వాడిన_decl *దొంతర)
{
  maybe_వాడిన_decls = దొంతర;
}

/* Return the result of sizeof applied to EXPR.  */

నిర్మాణం c_సమాసం
c_సమాసం_sizeof_సమాసం (location_t loc, నిర్మాణం c_సమాసం సమాసం)
{
  నిర్మాణం c_సమాసం ret;
  ఒకవేళ (సమాసం.విలువ == error_mark_కణుపు)
    {
      ret.విలువ = error_mark_కణుపు;
      ret.original_సంకేతం = ERROR_MARK;
      ret.original_type = ఖాళీ;
      ret.m_decimal = 0;
      తీయి_maybe_వాడిన (అబద్ధం);
    }
  లేకపోతే
    {
      తార్కిక సమాసం_const_operands = నిజం;

      ఒకవేళ (వృక్షం_సంకేతం (సమాసం.విలువ) == PARM_DECL
	  && C_ARRAY_PARAMETER (సమాసం.విలువ))
	{
	  auto_diagnostic_సమూహం d;
	  ఒకవేళ (warning_at (loc, OPT_Wsizeof_array_వాదం,
			  "%<sizeof%> on array function parameter %qE will "
			  "return size of %qT", సమాసం.విలువ,
			  వృక్షం_TYPE (సమాసం.విలువ)))
	    inform (DECL_ఆధారం_LOCATION (సమాసం.విలువ), "declared here");
	}
      వృక్షం folded_సమాసం = c_fully_fold (సమాసం.విలువ, require_constant_విలువ,
				       &సమాసం_const_operands);
      ret.విలువ = c_sizeof (loc, వృక్షం_TYPE (folded_సమాసం));
      c_చివరి_sizeof_arg = సమాసం.విలువ;
      c_చివరి_sizeof_loc = loc;
      ret.original_సంకేతం = SIZEOF_సమాసం;
      ret.original_type = ఖాళీ;
      ret.m_decimal = 0;
      ఒకవేళ (C_TYPE_VARIABLE_కొలత (వృక్షం_TYPE (folded_సమాసం)))
	{
	  /* sizeof is evaluated when given a vla (C99 6.5.3.4p2).  */
	  ret.విలువ = build2 (C_MAYBE_CONST_సమాసం, వృక్షం_TYPE (ret.విలువ),
			      folded_సమాసం, ret.విలువ);
	  C_MAYBE_CONST_సమాసం_NON_CONST (ret.విలువ) = !సమాసం_const_operands;
	  సమితి_సమాసం_LOCATION (ret.విలువ, loc);
	}
      తీయి_maybe_వాడిన (C_TYPE_VARIABLE_కొలత (వృక్షం_TYPE (folded_సమాసం)));
    }
  తిరిగి ret;
}

/* Return the result of sizeof applied to T, a structure for the type
   name passed to sizeof (rather than the type itself).  LOC is the
   location of the original expression.  */

నిర్మాణం c_సమాసం
c_సమాసం_sizeof_type (location_t loc, నిర్మాణం c_type_name *t)
{
  వృక్షం type;
  నిర్మాణం c_సమాసం ret;
  వృక్షం type_సమాసం = NULL_వృక్షం;
  తార్కిక type_సమాసం_const = నిజం;
  type = groktypename (t, &type_సమాసం, &type_సమాసం_const);
  ret.విలువ = c_sizeof (loc, type);
  c_చివరి_sizeof_arg = type;
  c_చివరి_sizeof_loc = loc;
  ret.original_సంకేతం = SIZEOF_సమాసం;
  ret.original_type = ఖాళీ;
  ret.m_decimal = 0;
  ఒకవేళ (type == error_mark_కణుపు)
    {
      ret.విలువ = error_mark_కణుపు;
      ret.original_సంకేతం = ERROR_MARK;
    }
  లేకపోతే
  ఒకవేళ ((type_సమాసం || వృక్షం_సంకేతం (ret.విలువ) == INTEGER_CST)
      && C_TYPE_VARIABLE_కొలత (type))
    {
      /* If the type is a [*] array, it is a VLA but is represented as
	 having a size of zero.  In such a case we must ensure that
	 the result of sizeof does not get folded to a constant by
	 c_fully_fold, because if the size is evaluated the result is
	 not constant and so constraints on zero or negative size
	 arrays must not be applied when this sizeof call is inside
	 another array declarator.  */
      ఒకవేళ (!type_సమాసం)
	type_సమాసం = integer_zero_కణుపు;
      ret.విలువ = build2 (C_MAYBE_CONST_సమాసం, వృక్షం_TYPE (ret.విలువ),
			  type_సమాసం, ret.విలువ);
      C_MAYBE_CONST_సమాసం_NON_CONST (ret.విలువ) = !type_సమాసం_const;
    }
  తీయి_maybe_వాడిన (type != error_mark_కణుపు
		  ? C_TYPE_VARIABLE_కొలత (type) : అబద్ధం);
  తిరిగి ret;
}

స్థిర తార్కిక
శిఖరం_array_vla_p (const_వృక్షం type)
{
  ఒకవేళ (వృక్షం_సంకేతం (type) != ARRAY_TYPE)
    తిరిగి అబద్ధం;

  వృక్షం d = TYPE_DOMAIN (type);

  ఒకవేళ (!d)
    తిరిగి అబద్ధం;
  ఒకవేళ (!TYPE_MAX_విలువ (d))
    తిరిగి అబద్ధం;

  తిరిగి వృక్షం_సంకేతం (TYPE_MAX_విలువ (d)) != INTEGER_CST
	 || వృక్షం_సంకేతం (TYPE_MIN_విలువ (d)) != INTEGER_CST;
}

/* Return the result of countof applied to EXPR.  */

నిర్మాణం c_సమాసం
c_సమాసం_countof_సమాసం (location_t loc, నిర్మాణం c_సమాసం సమాసం)
{
  నిర్మాణం c_సమాసం ret;
  ఒకవేళ (సమాసం.విలువ == error_mark_కణుపు)
    {
      ret.విలువ = error_mark_కణుపు;
      ret.original_సంకేతం = ERROR_MARK;
      ret.original_type = ఖాళీ;
      ret.m_decimal = 0;
      తీయి_maybe_వాడిన (అబద్ధం);
    }
  లేకపోతే
    {
      తార్కిక సమాసం_const_operands = నిజం;

      వృక్షం folded_సమాసం = c_fully_fold (సమాసం.విలువ, require_constant_విలువ,
				       &సమాసం_const_operands);
      ret.విలువ = c_countof_type (loc, వృక్షం_TYPE (folded_సమాసం));
      c_చివరి_sizeof_arg = సమాసం.విలువ;
      c_చివరి_sizeof_loc = loc;
      ret.original_సంకేతం = COUNTOF_సమాసం;
      ret.original_type = ఖాళీ;
      ret.m_decimal = 0;
      ఒకవేళ (శిఖరం_array_vla_p (వృక్షం_TYPE (folded_సమాసం)))
	{
	  /* countof is evaluated when given a vla.  */
	  ret.విలువ = build2 (C_MAYBE_CONST_సమాసం, వృక్షం_TYPE (ret.విలువ),
			      folded_సమాసం, ret.విలువ);
	  C_MAYBE_CONST_సమాసం_NON_CONST (ret.విలువ) = !సమాసం_const_operands;
	  సమితి_సమాసం_LOCATION (ret.విలువ, loc);
	}
      తీయి_maybe_వాడిన (శిఖరం_array_vla_p (వృక్షం_TYPE (folded_సమాసం)));
    }
  తిరిగి ret;
}

/* Return the result of countof applied to T, a structure for the type
   name passed to countof (rather than the type itself).  LOC is the
   location of the original expression.  */

నిర్మాణం c_సమాసం
c_సమాసం_countof_type (location_t loc, నిర్మాణం c_type_name *t)
{
  వృక్షం type;
  నిర్మాణం c_సమాసం ret;
  వృక్షం type_సమాసం = NULL_వృక్షం;
  తార్కిక type_సమాసం_const = నిజం;
  type = groktypename (t, &type_సమాసం, &type_సమాసం_const);
  ret.విలువ = c_countof_type (loc, type);
  c_చివరి_sizeof_arg = type;
  c_చివరి_sizeof_loc = loc;
  ret.original_సంకేతం = COUNTOF_సమాసం;
  ret.original_type = ఖాళీ;
  ret.m_decimal = 0;
  ఒకవేళ (type == error_mark_కణుపు)
    {
      ret.విలువ = error_mark_కణుపు;
      ret.original_సంకేతం = ERROR_MARK;
    }
  లేకపోతే
  ఒకవేళ ((type_సమాసం || వృక్షం_సంకేతం (ret.విలువ) == INTEGER_CST)
      && శిఖరం_array_vla_p (type))
    {
      /* If the type is a [*] array, it is a VLA but is represented as
	 having a size of zero.  In such a case we must ensure that
	 the result of countof does not get folded to a constant by
	 c_fully_fold, because if the number of elements is evaluated
	 the result is not constant and so
	 constraints on zero or negative size arrays must not be applied
	 when this countof call is inside another array declarator.  */
      ఒకవేళ (!type_సమాసం)
	type_సమాసం = integer_zero_కణుపు;
      ret.విలువ = build2 (C_MAYBE_CONST_సమాసం, వృక్షం_TYPE (ret.విలువ),
			  type_సమాసం, ret.విలువ);
      C_MAYBE_CONST_సమాసం_NON_CONST (ret.విలువ) = !type_సమాసం_const;
    }
  తీయి_maybe_వాడిన (type != error_mark_కణుపు ? శిఖరం_array_vla_p (type) : అబద్ధం);
  తిరిగి ret;
}

/* Return the result of maxof applied to T, a structure for the type
   name passed to maxof (rather than the type itself).  LOC is the
   location of the original expression.  */

నిర్మాణం c_సమాసం
c_సమాసం_maxof_type (location_t loc, నిర్మాణం c_type_name *t)
{
  వృక్షం type;
  నిర్మాణం c_సమాసం ret;
  వృక్షం type_సమాసం = NULL_వృక్షం;
  తార్కిక type_సమాసం_const = నిజం;
  type = groktypename (t, &type_సమాసం, &type_సమాసం_const);
  ret.విలువ = c_maxof_type (loc, type);
  c_చివరి_sizeof_arg = type;
  c_చివరి_sizeof_loc = loc;
  ret.original_సంకేతం = MAXOF_సమాసం;
  ret.original_type = ఖాళీ;
  ret.m_decimal = 0;
  ఒకవేళ (type == error_mark_కణుపు)
    {
      ret.విలువ = error_mark_కణుపు;
      ret.original_సంకేతం = ERROR_MARK;
    }
  తీయి_maybe_వాడిన (type != error_mark_కణుపు);
  తిరిగి ret;
}

/* Return the result of minof applied to T, a structure for the type
   name passed to minof (rather than the type itself).  LOC is the
   location of the original expression.  */

నిర్మాణం c_సమాసం
c_సమాసం_minof_type (location_t loc, నిర్మాణం c_type_name *t)
{
  వృక్షం type;
  నిర్మాణం c_సమాసం ret;
  వృక్షం type_సమాసం = NULL_వృక్షం;
  తార్కిక type_సమాసం_const = నిజం;
  type = groktypename (t, &type_సమాసం, &type_సమాసం_const);
  ret.విలువ = c_minof_type (loc, type);
  c_చివరి_sizeof_arg = type;
  c_చివరి_sizeof_loc = loc;
  ret.original_సంకేతం = MINOF_సమాసం;
  ret.original_type = ఖాళీ;
  ret.m_decimal = 0;
  ఒకవేళ (type == error_mark_కణుపు)
    {
      ret.విలువ = error_mark_కణుపు;
      ret.original_సంకేతం = ERROR_MARK;
    }
  తీయి_maybe_వాడిన (type != error_mark_కణుపు);
  తిరిగి ret;
}

/* Build a function call to function FUNCTION with parameters PARAMS.
   The function call is at LOC.
   PARAMS is a list--a chain of TREE_LIST nodes--in which the
   TREE_VALUE of each node is a parameter-expression.
   FUNCTION's data type may be a function type or a pointer-to-function.  */

వృక్షం
build_function_call (location_t loc, వృక్షం function, వృక్షం params)
{
  vec<వృక్షం, va_gc> *v;
  వృక్షం ret;

  vec_alloc (v, list_నిడివి (params));
  కొరకు (; params; params = వృక్షం_CHAIN (params))
    v->శీఘ్ర_నెట్టు (వృక్షం_విలువ (params));
  ret = c_build_function_call_vec (loc, vNULL, function, v, ఖాళీ);
  vec_free (v);
  తిరిగి ret;
}

/* Give a note about the location of the declaration of DECL,
   or, failing that, a pertinent declaration for FUNCTION_EXPR.  */

స్థిర శూన్య
inform_declaration (వృక్షం decl, వృక్షం function_సమాసం)
{
  ఒకవేళ (decl && (వృక్షం_సంకేతం (decl) != FUNCTION_DECL
	       || !DECL_IS_UNDECLARED_BUILTIN (decl)))
    inform (DECL_ఆధారం_LOCATION (decl), "declared here");
  లేకపోతే ఒకవేళ (function_సమాసం)
    ఎంపిక (వృక్షం_సంకేతం (function_సమాసం))
      {
      అప్రమేయ:
	ఆపు;
      స్థితి COMPONENT_REF:
	/* Show the decl of the pertinent field (e.g. for callback
	   fields in a struct.  */
	{
	  వృక్షం క్షేత్రం_decl = వృక్షం_నిర్వాహ్యం (function_సమాసం, 1);
	  ఒకవేళ (location_t loc = DECL_ఆధారం_LOCATION (క్షేత్రం_decl))
	    inform (loc, "declared here");
	}
	ఆపు;
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

వృక్షం
build_function_call_vec (location_t loc, vec<location_t> arg_loc,
			 వృక్షం function, vec<వృక్షం, va_gc> *params,
			 vec<వృక్షం, va_gc> *origtypes, వృక్షం orig_fundecl)
{
  వృక్షం fntype, fundecl = NULL_వృక్షం;
  వృక్షం name = NULL_వృక్షం, ఫలితం;
  వృక్షం tem;
  పూర్ణాంకం nargs;
  వృక్షం *argarray;


  /* Strip NON_LVALUE_EXPRs, etc., since we aren't using as an lvalue.  */
  STRIP_TYPE_NOPS (function);

  /* Convert anything with function type to a pointer-to-function.  */
  ఒకవేళ (వృక్షం_సంకేతం (function) == FUNCTION_DECL)
    {
      name = DECL_NAME (function);

      ఒకవేళ (flag_tm)
	tm_malloc_replacement (function);
      fundecl = function;
      ఒకవేళ (!orig_fundecl)
	orig_fundecl = fundecl;
      /* Atomic functions have type checking/casting already done.  They are
	 often rewritten and don't match the original parameter list.  */
      ఒకవేళ (name && startswith (IDENTIFIER_సూచిక (name), "__atomic_"))
        origtypes = ఖాళీ;
    }
  ఒకవేళ (వృక్షం_సంకేతం (వృక్షం_TYPE (function)) == FUNCTION_TYPE)
    function = function_గమ్యం_సూచిక_conversion (loc, function);

  /* For Objective-C, convert any calls via a cast to OBJC_TYPE_REF
     expressions, like those used for ObjC messenger dispatches.  */
  ఒకవేళ (params && !params->is_ఖాళీలు ())
    function = objc_rewrite_function_call (function, (*params)[0]);

  function = c_fully_fold (function, అబద్ధం, ఖాళీ);

  fntype = వృక్షం_TYPE (function);

  ఒకవేళ (వృక్షం_సంకేతం (fntype) == ERROR_MARK)
    తిరిగి error_mark_కణుపు;

  ఒకవేళ (!(వృక్షం_సంకేతం (fntype) == సూచిక_TYPE
	&& వృక్షం_సంకేతం (వృక్షం_TYPE (fntype)) == FUNCTION_TYPE))
    {
      ఒకవేళ (!flag_diagnostics_show_caret && !STATEMENT_CLASS_P (function))
	error_at (loc,
		  "called object %qE is not a function or function pointer",
		  function);
      లేకపోతే ఒకవేళ (DECL_P (function))
	{
	  auto_diagnostic_సమూహం d;
	  error_at (loc,
		    "called object %qD is not a function or function pointer",
		    function);
	  inform_declaration (function, NULL_వృక్షం);
	}
      లేకపోతే
	error_at (loc,
		  "called object is not a function or function pointer");
      తిరిగి error_mark_కణుపు;
    }

  ఒకవేళ (fundecl && వృక్షం_THIS_VOLATILE (fundecl))
    current_function_returns_abnormally = 1;

  /* fntype now gets the type of function pointed to.  */
  fntype = వృక్షం_TYPE (fntype);
  వృక్షం return_type = వృక్షం_TYPE (fntype);

  /* Convert the parameters to the types declared in the
     function prototype, or apply default promotions.  */

  nargs = convert_arguments (loc, arg_loc, fntype, params,
			     origtypes, function, fundecl);
  ఒకవేళ (nargs < 0)
    తిరిగి error_mark_కణుపు;

  /* Check that the function is called through a compatible prototype.
     If it is not, warn.  */
  ఒకవేళ (CONVERT_సమాసం_P (function)
      && వృక్షం_సంకేతం (tem = వృక్షం_నిర్వాహ్యం (function, 0)) == ADDR_సమాసం
      && వృక్షం_సంకేతం (tem = వృక్షం_నిర్వాహ్యం (tem, 0)) == FUNCTION_DECL
      && !comptypes (fntype, వృక్షం_TYPE (tem)))
    {
      /* This situation leads to run-time undefined behavior.  We can't,
	 therefore, simply error unless we can prove that all possible
	 executions of the program must execute the code.  */
      warning_at (loc, 0, "function called through a non-compatible type");

      ఒకవేళ (VOID_TYPE_P (return_type)
	  && TYPE_QUALS (return_type) != TYPE_UNQUALIFIED)
	pedwarn (loc, 0,
		 "function with qualified void return type called");
     }

  argarray = vec_సురక్షిత_చిరునామా (params);

  /* Check that arguments to builtin functions match the expectations.  */
  ఒకవేళ (fundecl
      && fndecl_built_లోపల_p (fundecl)
      && !check_builtin_function_arguments (loc, arg_loc, fundecl,
					    orig_fundecl, nargs, argarray))
    తిరిగి error_mark_కణుపు;

  /* Check that the arguments to the function are valid.  */
  తార్కిక warned_p = check_function_arguments (loc, fundecl, fntype,
					    nargs, argarray, &arg_loc,
					    comptypes);

  ఒకవేళ (TYPE_QUALS (return_type) != TYPE_UNQUALIFIED
      && !VOID_TYPE_P (return_type))
    return_type = c_build_qualified_type (return_type, TYPE_UNQUALIFIED);
  ఒకవేళ (name != NULL_వృక్షం
      && startswith (IDENTIFIER_సూచిక (name), "__builtin_"))
    {
      ఒకవేళ (require_constant_విలువ)
	ఫలితం
	  = fold_build_call_array_initializer_loc (loc, return_type,
						   function, nargs, argarray);
      లేకపోతే
	ఫలితం = fold_build_call_array_loc (loc, return_type,
					    function, nargs, argarray);
      ఒకవేళ (వృక్షం_సంకేతం (ఫలితం) == NOP_సమాసం
	  && వృక్షం_సంకేతం (వృక్షం_నిర్వాహ్యం (ఫలితం, 0)) == INTEGER_CST)
	STRIP_TYPE_NOPS (ఫలితం);
    }
  లేకపోతే
    ఫలితం = build_call_array_loc (loc, return_type,
				   function, nargs, argarray);
  /* If -Wnonnull warning has been diagnosed, avoid diagnosing it again
     later.  */
  ఒకవేళ (warned_p && వృక్షం_సంకేతం (ఫలితం) == CALL_సమాసం)
    suppress_warning (ఫలితం, OPT_Wnonnull);

  /* In this improbable scenario, a nested function returns a VM type.
     Create a TARGET_EXPR so that the call always has a LHS, much as
     what the C++ FE does for functions returning non-PODs.  */
  ఒకవేళ (c_type_variably_modified_p (వృక్షం_TYPE (fntype)))
    {
      వృక్షం tmp = create_tmp_var_raw (వృక్షం_TYPE (fntype));
      ఫలితం = build4 (లక్ష్యం_సమాసం, వృక్షం_TYPE (fntype), tmp, ఫలితం,
		       NULL_వృక్షం, NULL_వృక్షం);
    }

  ఒకవేళ (VOID_TYPE_P (వృక్షం_TYPE (ఫలితం)))
    {
      ఒకవేళ (TYPE_QUALS (వృక్షం_TYPE (ఫలితం)) != TYPE_UNQUALIFIED)
	pedwarn (loc, 0,
		 "function with qualified void return type called");
      తిరిగి ఫలితం;
    }
  తిరిగి require_complete_type (loc, ఫలితం);
}

/* Like build_function_call_vec, but call also resolve_overloaded_builtin.  */

వృక్షం
c_build_function_call_vec (location_t loc, స్థిరరాశి vec<location_t> &arg_loc,
			   వృక్షం function, vec<వృక్షం, va_gc> *params,
			   vec<వృక్షం, va_gc> *origtypes)
{
  /* Strip NON_LVALUE_EXPRs, etc., since we aren't using as an lvalue.  */
  STRIP_TYPE_NOPS (function);

  /* Convert anything with function type to a pointer-to-function.  */
  ఒకవేళ (వృక్షం_సంకేతం (function) == FUNCTION_DECL)
    {
      /* Implement type-directed function overloading for builtins.
	 resolve_overloaded_builtin and targetm.resolve_overloaded_builtin
	 handle all the type checking.  The result is a complete expression
	 that implements this function call.  */
      వృక్షం tem = resolve_overloaded_builtin (loc, function, params);
      ఒకవేళ (tem)
	తిరిగి tem;
    }
  తిరిగి build_function_call_vec (loc, arg_loc, function, params, origtypes);
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

స్థిర వృక్షం
convert_వాదం (location_t ploc, వృక్షం function, వృక్షం fundecl,
		  వృక్షం type, వృక్షం origtype, వృక్షం val, వృక్షం valtype,
		  తార్కిక npc, వృక్షం rname, పూర్ణాంకం parmnum, పూర్ణాంకం argnum,
		  తార్కిక excess_precision, పూర్ణాంకం warnopt)
{
  /* Formal parm type is specified by a function prototype.  */

  ఒకవేళ (type == error_mark_కణుపు || !COMPLETE_TYPE_P (type))
    {
      error_at (ploc, "type of formal parameter %d is incomplete",
		parmnum + 1);
      తిరిగి error_mark_కణుపు;
    }

  /* Optionally warn about conversions that differ from the default
     conversions.  */
  ఒకవేళ (warn_traditional_conversion || warn_traditional)
    {
      ఒకవేళ (INTEGRAL_TYPE_P (type)
	  && SCALAR_FLOAT_TYPE_P (valtype))
	warning_at (ploc, OPT_Wtraditional_conversion,
		    "passing argument %d of %qE as integer rather "
		    "than floating due to prototype",
		    argnum, rname);
      ఒకవేళ (INTEGRAL_TYPE_P (type)
	  && వృక్షం_సంకేతం (valtype) == COMPLEX_TYPE)
	warning_at (ploc, OPT_Wtraditional_conversion,
		    "passing argument %d of %qE as integer rather "
		    "than complex due to prototype",
		    argnum, rname);
      లేకపోతే ఒకవేళ (వృక్షం_సంకేతం (type) == COMPLEX_TYPE
	       && SCALAR_FLOAT_TYPE_P (valtype))
	warning_at (ploc, OPT_Wtraditional_conversion,
		    "passing argument %d of %qE as complex rather "
		    "than floating due to prototype",
		    argnum, rname);
      లేకపోతే ఒకవేళ (SCALAR_FLOAT_TYPE_P (type)
	       && INTEGRAL_TYPE_P (valtype))
	warning_at (ploc, OPT_Wtraditional_conversion,
		    "passing argument %d of %qE as floating rather "
		    "than integer due to prototype",
		    argnum, rname);
      లేకపోతే ఒకవేళ (వృక్షం_సంకేతం (type) == COMPLEX_TYPE
	       && INTEGRAL_TYPE_P (valtype))
	warning_at (ploc, OPT_Wtraditional_conversion,
		    "passing argument %d of %qE as complex rather "
		    "than integer due to prototype",
		    argnum, rname);
      లేకపోతే ఒకవేళ (SCALAR_FLOAT_TYPE_P (type)
	       && వృక్షం_సంకేతం (valtype) == COMPLEX_TYPE)
	warning_at (ploc, OPT_Wtraditional_conversion,
		    "passing argument %d of %qE as floating rather "
		    "than complex due to prototype",
		    argnum, rname);
      /* ??? At some point, messages should be written about
	 conversions between complex types, but that's too messy
	 to do now.  */
      లేకపోతే ఒకవేళ (SCALAR_FLOAT_TYPE_P (type)
	       && SCALAR_FLOAT_TYPE_P (valtype))
	{
	  గుర్తులేని పూర్ణాంకం formal_prec = TYPE_PRECISION (type);

	  /* Warn if any argument is passed as `float',
	     since without a prototype it would be `double'.  */
	  ఒకవేళ (formal_prec == TYPE_PRECISION (float_type_కణుపు)
	      && type != dfloat32_type_కణుపు)
	    warning_at (ploc, 0,
			"passing argument %d of %qE as %<float%> "
			"rather than %<double%> due to prototype",
			argnum, rname);

	  /* Warn if mismatch between argument and prototype
	     for decimal float types.  Warn of conversions with
	     binary float types and of precision narrowing due to
	     prototype.  */
	  లేకపోతే ఒకవేళ (type != valtype
		   && (type == dfloat32_type_కణుపు
		       || type == dfloat64_type_కణుపు
		       || type == dfloat128_type_కణుపు
		       || valtype == dfloat32_type_కణుపు
		       || valtype == dfloat64_type_కణుపు
		       || valtype == dfloat128_type_కణుపు)
		   && (formal_prec
		       <= TYPE_PRECISION (valtype)
		       || (type == dfloat128_type_కణుపు
			   && (valtype
			       != dfloat64_type_కణుపు
			       && (valtype
				   != dfloat32_type_కణుపు)))
		       || (type == dfloat64_type_కణుపు
			   && (valtype
			       != dfloat32_type_కణుపు))))
	    warning_at (ploc, 0,
			"passing argument %d of %qE as %qT "
			"rather than %qT due to prototype",
			argnum, rname, type, valtype);

	}
      /* Detect integer changing in width or signedness.
	 These warnings are only activated with
	 -Wtraditional-conversion, not with -Wtraditional.  */
      లేకపోతే ఒకవేళ (warn_traditional_conversion
	       && INTEGRAL_TYPE_P (type)
	       && INTEGRAL_TYPE_P (valtype))
	{
	  గుర్తులేని పూర్ణాంకం formal_prec = TYPE_PRECISION (type);
	  వృక్షం would_have_been = default_conversion (val);
	  వృక్షం type1 = వృక్షం_TYPE (would_have_been);

	  ఒకవేళ (val == error_mark_కణుపు)
	    /* VAL could have been of incomplete type.  */;
	  లేకపోతే ఒకవేళ (వృక్షం_సంకేతం (type) == ENUMERAL_TYPE
		   && (TYPE_MAIN_VARIANT (type)
		       == TYPE_MAIN_VARIANT (valtype)))
	    /* No warning if function asks for enum
	       and the actual arg is that enum type.  */
	    ;
	  లేకపోతే ఒకవేళ (formal_prec != TYPE_PRECISION (type1))
	    warning_at (ploc, OPT_Wtraditional_conversion,
			"passing argument %d of %qE "
			"with different width due to prototype",
			argnum, rname);
	  లేకపోతే ఒకవేళ (TYPE_UNSIGNED (type) == TYPE_UNSIGNED (type1))
	    ;
	  /* Don't complain if the formal parameter type
	     is an enum, because we can't tell now whether
	     the value was an enum--even the same enum.  */
	  లేకపోతే ఒకవేళ (వృక్షం_సంకేతం (type) == ENUMERAL_TYPE)
	    ;
	  లేకపోతే ఒకవేళ (వృక్షం_సంకేతం (val) == INTEGER_CST
		   && int_సరిపోతుంది_type_p (val, type))
	    /* Change in signedness doesn't matter
	       if a constant value is unaffected.  */
	    ;
	  /* If the value is extended from a narrower
	     unsigned type, it doesn't matter whether we
	     pass it as signed or unsigned; the value
	     certainly is the same either way.  */
	  లేకపోతే ఒకవేళ (TYPE_PRECISION (valtype) < TYPE_PRECISION (type)
		   && TYPE_UNSIGNED (valtype))
	    ;
	  లేకపోతే ఒకవేళ (TYPE_UNSIGNED (type))
	    warning_at (ploc, OPT_Wtraditional_conversion,
			"passing argument %d of %qE "
			"as unsigned due to prototype",
			argnum, rname);
	  లేకపోతే
	    warning_at (ploc, OPT_Wtraditional_conversion,
			"passing argument %d of %qE "
			"as signed due to prototype",
			argnum, rname);
	}
    }

  /* Possibly restore an EXCESS_PRECISION_EXPR for the
     sake of better warnings from convert_and_check.  */
  ఒకవేళ (excess_precision)
    val = build1 (EXCESS_PRECISION_సమాసం, valtype, val);

  వృక్షం parmval = convert_for_assignment (ploc, ploc, type,
					 val, origtype, ic_argpass,
					 npc, fundecl, function,
					 parmnum + 1, warnopt);
  తిరిగి parmval;
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

స్థిర పూర్ణాంకం
convert_arguments (location_t loc, vec<location_t> arg_loc, వృక్షం fntype,
		   vec<వృక్షం, va_gc> *విలువలు, vec<వృక్షం, va_gc> *origtypes,
		   వృక్షం function, వృక్షం fundecl)
{
  వృక్షం typelist = TYPE_ARG_TYPES (fntype);
  గుర్తులేని పూర్ణాంకం parmnum;
  తార్కిక error_వాదనలు = అబద్ధం;
  స్థిరరాశి తార్కిక type_generic = fundecl
    && lookup_attribute ("type generic", TYPE_లక్షణాలు (వృక్షం_TYPE (fundecl)));
  తార్కిక type_generic_remove_excess_precision = అబద్ధం;
  తార్కిక type_generic_అధికప్రవాహం_p = అబద్ధం;
  తార్కిక type_generic_బిట్టు_query = అబద్ధం;
  వృక్షం selector;

  /* Change pointer to function to the function itself for
     diagnostics.  */
  ఒకవేళ (వృక్షం_సంకేతం (function) == ADDR_సమాసం
      && వృక్షం_సంకేతం (వృక్షం_నిర్వాహ్యం (function, 0)) == FUNCTION_DECL)
    function = వృక్షం_నిర్వాహ్యం (function, 0);

  /* Handle an ObjC selector specially for diagnostics.  */
  selector = objc_సందేశం_selector ();

  /* For a call to a built-in function declared without a prototype,
     set to the built-in function's argument list.  */
  వృక్షం builtin_typelist = NULL_వృక్షం;

  /* For type-generic built-in functions, determine whether excess
     precision should be removed (classification) or not
     (comparison).  */
  ఒకవేళ (fundecl
      && fndecl_built_లోపల_p (fundecl, BUILT_లోపల_సాధారణ))
    {
      built_లోపల_function సంకేతం_2 = DECL_FUNCTION_సంకేతం (fundecl);
      ఒకవేళ (C_DECL_BUILTIN_PROTOTYPE (fundecl))
	{
	  /* For a call to a built-in function declared without a prototype
	     use the types of the parameters of the internal built-in to
	     match those of the arguments to.  */
	  ఒకవేళ (వృక్షం bdecl = builtin_decl_explicit (సంకేతం_2))
	    builtin_typelist = TYPE_ARG_TYPES (వృక్షం_TYPE (bdecl));
	}

      /* For type-generic built-in functions, determine whether excess
	 precision should be removed (classification) or not
	 (comparison).  */
      ఒకవేళ (type_generic)
	ఎంపిక (సంకేతం_2)
	  {
	  స్థితి BUILT_లోపల_ISFINITE:
	  స్థితి BUILT_లోపల_ISINF:
	  స్థితి BUILT_లోపల_ISINF_SIGN:
	  స్థితి BUILT_లోపల_ISNAN:
	  స్థితి BUILT_లోపల_ISNORMAL:
	  స్థితి BUILT_లోపల_ISSIGNALING:
	  స్థితి BUILT_లోపల_FPCLASSIFY:
	    type_generic_remove_excess_precision = నిజం;
	    ఆపు;

	  స్థితి BUILT_లోపల_కూడు_అధికప్రవాహం_P:
	  స్థితి BUILT_లోపల_SUB_అధికప్రవాహం_P:
	  స్థితి BUILT_లోపల_MUL_అధికప్రవాహం_P:
	    /* The last argument of these type-generic builtins
	       should not be promoted.  */
	    type_generic_అధికప్రవాహం_p = నిజం;
	    ఆపు;

	  స్థితి BUILT_లోపల_CLZG:
	  స్థితి BUILT_లోపల_CTZG:
	  స్థితి BUILT_లోపల_CLRSBG:
	  స్థితి BUILT_లోపల_FFSG:
	  స్థితి BUILT_లోపల_PARITYG:
	  స్థితి BUILT_లోపల_POPCOUNTG:
	    /* The first argument of these type-generic builtins
	       should not be promoted.  */
	    type_generic_బిట్టు_query = నిజం;
	    ఆపు;

	  అప్రమేయ:
	    ఆపు;
	  }
    }

  /* Scan the given expressions (VALUES) and types (TYPELIST), producing
     individual converted arguments.  */

  వృక్షం typetail, builtin_typetail, val;
  కొరకు (typetail = typelist,
	 builtin_typetail = builtin_typelist,
	 parmnum = 0;
       విలువలు && విలువలు->iterate (parmnum, &val);
       ++parmnum)
    {
      /* The type of the function parameter (if it was declared with one).  */
      వృక్షం type = typetail ? వృక్షం_విలువ (typetail) : NULL_వృక్షం;
      /* The type of the built-in function parameter (if the function
	 is a built-in).  Used to detect type incompatibilities in
	 calls to built-ins declared without a prototype.  */
      వృక్షం builtin_type = (builtin_typetail
			   ? వృక్షం_విలువ (builtin_typetail) : NULL_వృక్షం);
      /* The original type of the argument being passed to the function.  */
      వృక్షం valtype = వృక్షం_TYPE (val);
      /* The called function (or function selector in Objective C).  */
      వృక్షం rname = function;
      పూర్ణాంకం argnum = parmnum + 1;
      స్థిరరాశి అక్షరం *invalid_func_diag;
      /* Set for EXCESS_PRECISION_EXPR arguments.  */
      తార్కిక excess_precision = అబద్ధం;
      /* The value of the argument after conversion to the type
	 of the function parameter it is passed to.  */
      వృక్షం parmval;
      /* Some __atomic_* builtins have additional hidden argument at
	 position 0.  */
      location_t ploc
	= !arg_loc.is_ఖాళీలు () && విలువలు->నిడివి () == arg_loc.నిడివి ()
	  ? expansion_బిందువు_location_if_లోపల_system_శీర్షిక (arg_loc[parmnum])
	  : ఆదానం_location;

      ఒకవేళ (type == void_type_కణుపు)
	{
	  auto_diagnostic_సమూహం d;
	  పూర్ణాంకం అంకె_expected = parmnum;
	  పూర్ణాంకం అంకె_actual = విలువలు->నిడివి ();
	  gcc_rich_location rich_loc (loc);
	  ఒకవేళ (ploc != ఆదానం_location)
	    rich_loc.కూడు_range (ploc);
	  ఒకవేళ (selector)
	    error_at (&rich_loc,
		      "too many arguments to method %qE; expected %i, have %i",
		      selector, అంకె_expected, అంకె_actual);
	  లేకపోతే
	    error_at (&rich_loc,
		      "too many arguments to function %qE; expected %i, have %i",
		      function, అంకె_expected, అంకె_actual);
	  inform_declaration (fundecl, function);
	  తిరిగి error_వాదనలు ? -1 : (పూర్ణాంకం) parmnum;
	}

      ఒకవేళ (builtin_type == void_type_కణుపు)
	{
	  auto_diagnostic_సమూహం d;
	  ఒకవేళ (warning_at (loc, OPT_Wbuiltin_declaration_mismatch,
			  "too many arguments to built-in function %qE "
			  "expecting %d", function, parmnum))
	    inform_declaration (fundecl, function);
	  builtin_typetail = NULL_వృక్షం;
	}

      ఒకవేళ (!typetail && parmnum == 0 && !TYPE_NO_NAMED_వాదనలు_STDARG_P (fntype)
	  && !(fundecl && fndecl_built_లోపల_p (fundecl)))
	{
	  auto_diagnostic_సమూహం d;
	  తార్కిక warned;
	  ఒకవేళ (selector)
	    warned = warning_at (loc, OPT_Wdeprecated_non_prototype,
				 "ISO C23 does not allow arguments"
				 " for method %qE declared without parameters",
				 function);
	  లేకపోతే
	    warned = warning_at (loc, OPT_Wdeprecated_non_prototype,
				 "ISO C23 does not allow arguments"
				 " for function %qE declared without parameters",
				 function);
	  ఒకవేళ (warned)
	    inform_declaration (fundecl, function);
	}

      ఒకవేళ (selector && argnum > 2)
	{
	  rname = selector;
	  argnum -= 2;
	}

      /* Determine if VAL is a null pointer constant before folding it.  */
      తార్కిక npc = null_సూచిక_constant_p (val);

      /* If there is excess precision and a prototype, convert once to
	 the required type rather than converting via the semantic
	 type.  Likewise without a prototype a float value represented
	 as long double should be converted once to double.  But for
	 type-generic classification functions excess precision must
	 be removed here.  */
      ఒకవేళ (వృక్షం_సంకేతం (val) == EXCESS_PRECISION_సమాసం
	  && (type || !type_generic || !type_generic_remove_excess_precision))
	{
	  val = వృక్షం_నిర్వాహ్యం (val, 0);
	  excess_precision = నిజం;
	}
      val = c_fully_fold (val, అబద్ధం, ఖాళీ);
      STRIP_TYPE_NOPS (val);

      val = require_complete_type (ploc, val);

      /* Some floating-point arguments must be promoted to double when
	 no type is specified by a prototype.  This applies to
	 arguments of type float, and to architecture-specific types
	 (ARM __fp16), but not to _FloatN or _FloatNx types.  */
      తార్కిక promote_float_arg = అబద్ధం;
      ఒకవేళ (type == NULL_వృక్షం
	  && వృక్షం_సంకేతం (valtype) == REAL_TYPE
	  && (TYPE_PRECISION (valtype)
	      <= TYPE_PRECISION (double_type_కణుపు))
	  && TYPE_MAIN_VARIANT (valtype) != double_type_కణుపు
	  && TYPE_MAIN_VARIANT (valtype) != long_double_type_కణుపు
	  && !DECIMAL_FLOAT_బహుళకం_P (TYPE_బహుళకం (valtype)))
	{
	  /* Promote this argument, unless it has a _FloatN or
	     _FloatNx type.  */
	  promote_float_arg = నిజం;
	  కొరకు (పూర్ణాంకం i = 0; i < అంకె_FLOATN_NX_TYPES; i++)
	    ఒకవేళ (TYPE_MAIN_VARIANT (valtype) == FLOATN_NX_TYPE_కణుపు (i))
	      {
		promote_float_arg = అబద్ధం;
		ఆపు;
	      }
	  /* Don't promote __bf16 either.  */
	  ఒకవేళ (TYPE_MAIN_VARIANT (valtype) == bfloat16_type_కణుపు)
	    promote_float_arg = అబద్ధం;
	}

      ఒకవేళ (type != NULL_వృక్షం)
	{
	  వృక్షం origtype = (!origtypes) ? NULL_వృక్షం : (*origtypes)[parmnum];
	  parmval = convert_వాదం (ploc, function, fundecl, type, origtype,
				      val, valtype, npc, rname, parmnum, argnum,
				      excess_precision, 0);
	}
      /* A NULLPTR type is just a nullptr always.  */
      లేకపోతే ఒకవేళ (వృక్షం_సంకేతం (వృక్షం_TYPE (val)) == NULLPTR_TYPE)
	parmval = omit_one_నిర్వాహ్యం_loc (ploc, వృక్షం_TYPE (val), nullptr_కణుపు, val);
      లేకపోతే ఒకవేళ (promote_float_arg)
        {
	  ఒకవేళ (type_generic)
	    parmval = val;
	  లేకపోతే
	    {
	      /* Convert `float' to `double'.  */
	      ఒకవేళ (warn_double_promotion && !c_inhibit_evaluation_warnings)
		warning_at (ploc, OPT_Wdouble_promotion,
			    "implicit conversion from %qT to %qT when passing "
			    "argument to function",
			    valtype, double_type_కణుపు);
	      parmval = convert (double_type_కణుపు, val);
	    }
	}
      లేకపోతే ఒకవేళ ((excess_precision && !type_generic)
	       || (type_generic_అధికప్రవాహం_p && parmnum == 2)
	       || (type_generic_బిట్టు_query && parmnum == 0))
	/* A "double" argument with excess precision being passed
	   without a prototype or in variable arguments.
	   The last argument of __builtin_*_overflow_p should not be
	   promoted, similarly the first argument of
	   __builtin_{clz,ctz,clrsb,ffs,parity,popcount}g.  */
	parmval = convert (valtype, val);
      లేకపోతే ఒకవేళ ((invalid_func_diag =
		targetm.calls.invalid_arg_for_unprototyped_fn (typelist, fundecl, val)))
	{
	  error (invalid_func_diag);
	  తిరిగి -1;
	}
      లేకపోతే ఒకవేళ (వృక్షం_సంకేతం (val) == ADDR_సమాసం && reject_gcc_builtin (val))
	{
	  తిరిగి -1;
	}
      లేకపోతే
	/* Convert `short' and `char' to full-size `int'.  */
	parmval = default_conversion (val);

      (*విలువలు)[parmnum] = parmval;
      ఒకవేళ (parmval == error_mark_కణుపు)
	error_వాదనలు = నిజం;

      ఒకవేళ (!type && builtin_type && వృక్షం_సంకేతం (builtin_type) != VOID_TYPE)
	{
	  /* For a call to a built-in function declared without a prototype,
	     perform the conversions from the argument to the expected type
	     but issue warnings rather than errors for any mismatches.
	     Ignore the converted argument and use the PARMVAL obtained
	     above by applying default conversions instead.  */
	  వృక్షం origtype = (!origtypes) ? NULL_వృక్షం : (*origtypes)[parmnum];
	  convert_వాదం (ploc, function, fundecl, builtin_type, origtype,
			    val, valtype, npc, rname, parmnum, argnum,
			    excess_precision,
			    OPT_Wbuiltin_declaration_mismatch);
	}

      ఒకవేళ (typetail)
	typetail = వృక్షం_CHAIN (typetail);

      ఒకవేళ (builtin_typetail)
	builtin_typetail = వృక్షం_CHAIN (builtin_typetail);
    }

  gcc_assert (parmnum == vec_సురక్షిత_నిడివి (విలువలు));

  ఒకవేళ (typetail != NULL_వృక్షం && వృక్షం_విలువ (typetail) != void_type_కణుపు)
    {
      /* Not enough args.
	 Determine minimum number of arguments required.  */
      పూర్ణాంకం min_expected_అంకె = 0;
      తార్కిక at_కనిష్ఠ_p = అబద్ధం;
      వృక్షం iter = typelist;
      అయితే (నిజం)
	{
	  ఒకవేళ (!iter)
	    {
	      /* Variadic arguments; stop iterating.  */
	      at_కనిష్ఠ_p = నిజం;
	      ఆపు;
	    }
	  ఒకవేళ (iter == void_list_కణుపు)
	    /* End of arguments; stop iterating.  */
	    ఆపు;
	  ++min_expected_అంకె;
	  iter = వృక్షం_CHAIN (iter);
	}
      auto_diagnostic_సమూహం d;
      పూర్ణాంకం actual_అంకె = vec_సురక్షిత_నిడివి (విలువలు);
      error_at (loc,
		at_కనిష్ఠ_p
		? G_("too few arguments to function %qE; expected at least %i, have %i")
		: G_("too few arguments to function %qE; expected %i, have %i"),
		function, min_expected_అంకె, actual_అంకె);
      inform_declaration (fundecl, function);
      తిరిగి -1;
    }

  ఒకవేళ (builtin_typetail && వృక్షం_విలువ (builtin_typetail) != void_type_కణుపు)
    {
      గుర్తులేని nargs = parmnum;
      కొరకు (వృక్షం t = builtin_typetail; t; t = వృక్షం_CHAIN (t))
	++nargs;

      auto_diagnostic_సమూహం d;
      ఒకవేళ (warning_at (loc, OPT_Wbuiltin_declaration_mismatch,
		      "too few arguments to built-in function %qE "
		      "expecting %u", function, nargs - 1))
	inform_declaration (fundecl, function);
    }

  తిరిగి error_వాదనలు ? -1 : (పూర్ణాంకం) parmnum;
}

/* This is the entry point used by the parser to build unary operators
   in the input.  CODE, a tree_code, specifies the unary operator, and
   ARG is the operand.  For unary plus, the C parser currently uses
   CONVERT_EXPR for code.

   LOC is the location to use for the tree generated.
*/

నిర్మాణం c_సమాసం
parser_build_unary_op (location_t loc, గణన వృక్షం_సంకేతం_2 సంకేతం_2, నిర్మాణం c_సమాసం arg)
{
  నిర్మాణం c_సమాసం ఫలితం;

  ఫలితం.original_సంకేతం = సంకేతం_2;
  ఫలితం.original_type = ఖాళీ;
  ఫలితం.m_decimal = 0;

  ఒకవేళ (reject_gcc_builtin (arg.విలువ))
    {
      ఫలితం.విలువ = error_mark_కణుపు;
    }
  లేకపోతే
    {
      ఫలితం.విలువ = build_unary_op (loc, సంకేతం_2, arg.విలువ, అబద్ధం);

      ఒకవేళ (వృక్షం_అధికప్రవాహం_P (ఫలితం.విలువ) && !వృక్షం_అధికప్రవాహం_P (arg.విలువ))
	అధికప్రవాహం_warning (loc, ఫలితం.విలువ, arg.విలువ);
    }

  /* We are typically called when parsing a prefix token at LOC acting on
     ARG.  Reflect this by updating the source range of the result to
     start at LOC and end at the end of ARG.  */
  సమితి_c_సమాసం_ఆధారం_range (&ఫలితం,
			   loc, arg.get_ముగింపు ());

  తిరిగి ఫలితం;
}

/* Returns true if TYPE is a character type, *not* including wchar_t.  */

తార్కిక
char_type_p (వృక్షం type)
{
  తిరిగి (type == char_type_కణుపు
	  || type == unsigned_char_type_కణుపు
	  || type == signed_char_type_కణుపు
	  || type == char16_type_కణుపు
	  || type == char32_type_కణుపు);
}

/* This is the entry point used by the parser to build binary operators
   in the input.  CODE, a tree_code, specifies the binary operator, and
   ARG1 and ARG2 are the operands.  In addition to constructing the
   expression, we check for operands that were written with other binary
   operators in a way that is likely to confuse the user.  ORIG_ARG1 is
   the original first operand for TRUTH_{AND,OR}IF_EXPR before it is
   converted to truth value, otherwise NULL_TREE.

   LOCATION is the location of the binary operator.  */

నిర్మాణం c_సమాసం
parser_build_ద్విమాన_op (location_t location, గణన వృక్షం_సంకేతం_2 సంకేతం_2,
			నిర్మాణం c_సమాసం arg1, నిర్మాణం c_సమాసం arg2, వృక్షం orig_arg1)
{
  నిర్మాణం c_సమాసం ఫలితం;
  ఫలితం.m_decimal = 0;

  గణన వృక్షం_సంకేతం_2 code1 = arg1.original_సంకేతం;
  గణన వృక్షం_సంకేతం_2 code2 = arg2.original_సంకేతం;
  వృక్షం type1 = (arg1.original_type
                ? arg1.original_type
                : వృక్షం_TYPE (arg1.విలువ));
  వృక్షం type2 = (arg2.original_type
                ? arg2.original_type
                : వృక్షం_TYPE (arg2.విలువ));

  ఫలితం.విలువ = build_ద్విమాన_op (location, సంకేతం_2,
				  arg1.విలువ, arg2.విలువ, నిజం);
  ఫలితం.original_సంకేతం = సంకేతం_2;
  ఫలితం.original_type = ఖాళీ;
  ఫలితం.m_decimal = 0;

  ఒకవేళ (వృక్షం_సంకేతం (ఫలితం.విలువ) == ERROR_MARK)
    {
      సమితి_c_సమాసం_ఆధారం_range (&ఫలితం,
			       arg1.get_ప్రారంభం (),
			       arg2.get_ముగింపు ());
      తిరిగి ఫలితం;
    }

  ఒకవేళ (location != UNKNOWN_LOCATION)
    protected_సమితి_సమాసం_location (ఫలితం.విలువ, location);

  సమితి_c_సమాసం_ఆధారం_range (&ఫలితం,
			   arg1.get_ప్రారంభం (),
			   arg2.get_ముగింపు ());

  /* Check for cases such as x+y<<z which users are likely
     to misinterpret.  */
  ఒకవేళ (warn_parentheses)
    warn_about_parentheses (location, సంకేతం_2, code1, arg1.విలువ, code2,
			    arg2.విలువ);

  ఒకవేళ (warn_logical_op)
    warn_logical_operator (location, సంకేతం_2, వృక్షం_TYPE (ఫలితం.విలువ),
			   code1, arg1.విలువ, code2, arg2.విలువ);

  ఒకవేళ (warn_constant_logical_నిర్వాహ్యం
      && (సంకేతం_2 == TRUTH_ANDIF_సమాసం || సంకేతం_2 == TRUTH_ORIF_సమాసం)
      && INTEGRAL_NB_TYPE_P (type1)
      && INTEGRAL_NB_TYPE_P (type2))
    {
      స్థిరరాశి అక్షరం *name = సంకేతం_2 == TRUTH_ANDIF_సమాసం ? "&&" : "||";
      ఒకవేళ (orig_arg1 == NULL_వృక్షం)
	orig_arg1 = arg1.విలువ;
      స్వయంచాలక enum_other_than_0_1 = [] (వృక్షం type) {
	ఒకవేళ (వృక్షం_సంకేతం (type) != ENUMERAL_TYPE)
	  తిరిగి అబద్ధం;
	కొరకు (వృక్షం l = TYPE_విలువలు (type); l; l = వృక్షం_CHAIN (l))
	  {
	    వృక్షం v = DECL_INITIAL (వృక్షం_విలువ (l));
	    ఒకవేళ (!integer_zerop (v) && !integer_onep (v))
	      తిరిగి నిజం;
	  }
	తిరిగి అబద్ధం;
      };
      స్వయంచాలక diagnose_constant_logical_నిర్వాహ్యం = [=] (వృక్షం val, వృక్షం type) {
	ఒకవేళ (వృక్షం_సంకేతం (val) != INTEGER_CST || integer_zerop (val))
	  తిరిగి అబద్ధం;
	ఒకవేళ (integer_onep (val) && !enum_other_than_0_1 (type))
	  తిరిగి అబద్ధం;
	gcc_rich_location richloc (location);
	richloc.కూడు_fixit_replace (name + 1);
	auto_diagnostic_సమూహం d;
	ఒకవేళ (warning_at (location, OPT_Wconstant_logical_నిర్వాహ్యం,
			"use of logical %qs with constant operand %qE",
			name, val))
	  inform (&richloc, "use %qs for bitwise operation", name + 1);
	తిరిగి నిజం;
      };
      ఒకవేళ (!diagnose_constant_logical_నిర్వాహ్యం (arg2.విలువ, type2))
	diagnose_constant_logical_నిర్వాహ్యం (orig_arg1, type1);
    }

  ఒకవేళ (warn_tautological_compare)
    {
      వృక్షం lhs = arg1.విలువ;
      వృక్షం rhs = arg2.విలువ;
      ఒకవేళ (వృక్షం_సంకేతం (lhs) == C_MAYBE_CONST_సమాసం)
	{
	  ఒకవేళ (C_MAYBE_CONST_సమాసం_PRE (lhs) != NULL_వృక్షం
	      && వృక్షం_SIDE_EFFECTS (C_MAYBE_CONST_సమాసం_PRE (lhs)))
	    lhs = NULL_వృక్షం;
	  లేకపోతే
	    lhs = C_MAYBE_CONST_సమాసం_సమాసం (lhs);
	}
      ఒకవేళ (వృక్షం_సంకేతం (rhs) == C_MAYBE_CONST_సమాసం)
	{
	  ఒకవేళ (C_MAYBE_CONST_సమాసం_PRE (rhs) != NULL_వృక్షం
	      && వృక్షం_SIDE_EFFECTS (C_MAYBE_CONST_సమాసం_PRE (rhs)))
	    rhs = NULL_వృక్షం;
	  లేకపోతే
	    rhs = C_MAYBE_CONST_సమాసం_సమాసం (rhs);
	}
      ఒకవేళ (lhs != NULL_వృక్షం && rhs != NULL_వృక్షం)
	warn_tautological_cmp (location, సంకేతం_2, lhs, rhs);
    }

  ఒకవేళ (warn_logical_not_paren
      && వృక్షం_సంకేతం_CLASS (సంకేతం_2) == tcc_comparison
      && code1 == TRUTH_NOT_సమాసం
      && code2 != TRUTH_NOT_సమాసం
      /* Avoid warning for !!x == y.  */
      && (వృక్షం_సంకేతం (arg1.విలువ) != NE_సమాసం
	  || !integer_zerop (వృక్షం_నిర్వాహ్యం (arg1.విలువ, 1))))
    {
      /* Avoid warning for !b == y where b has _Bool type.  */
      వృక్షం t = integer_zero_కణుపు;
      ఒకవేళ (వృక్షం_సంకేతం (arg1.విలువ) == EQ_సమాసం
	  && integer_zerop (వృక్షం_నిర్వాహ్యం (arg1.విలువ, 1))
	  && వృక్షం_TYPE (వృక్షం_నిర్వాహ్యం (arg1.విలువ, 0)) == integer_type_కణుపు)
	{
	  t = వృక్షం_నిర్వాహ్యం (arg1.విలువ, 0);
	  చేయి
	    {
	      ఒకవేళ (వృక్షం_TYPE (t) != integer_type_కణుపు)
		ఆపు;
	      ఒకవేళ (వృక్షం_సంకేతం (t) == C_MAYBE_CONST_సమాసం)
		t = C_MAYBE_CONST_సమాసం_సమాసం (t);
	      లేకపోతే ఒకవేళ (CONVERT_సమాసం_P (t))
		t = వృక్షం_నిర్వాహ్యం (t, 0);
	      లేకపోతే
		ఆపు;
	    }
	  అయితే (1);
	}
      ఒకవేళ (!C_BOOLEAN_TYPE_P (వృక్షం_TYPE (t)))
	warn_logical_not_parentheses (location, సంకేతం_2, arg1.విలువ, arg2.విలువ);
    }

  /* Warn about comparisons against string literals, with the exception
     of testing for equality or inequality of a string literal with NULL.  */
  ఒకవేళ (సంకేతం_2 == EQ_సమాసం || సంకేతం_2 == NE_సమాసం)
    {
      ఒకవేళ ((code1 == STRING_CST
	   && !integer_zerop (వృక్షం_strip_nop_conversions (arg2.విలువ)))
	  || (code2 == STRING_CST
	      && !integer_zerop (వృక్షం_strip_nop_conversions (arg1.విలువ))))
	warning_at (location, OPT_Waddress,
		    "comparison with string literal results in unspecified behavior");
      /* Warn for ptr == '\0', it's likely that it should've been ptr[0].  */
      ఒకవేళ (సూచిక_TYPE_P (type1)
	  && null_సూచిక_constant_p (arg2.విలువ)
	  && char_type_p (type2))
	{
	  auto_diagnostic_సమూహం d;
	  ఒకవేళ (warning_at (location, OPT_Wpointer_compare,
			    "comparison between pointer and zero character "
			    "constant"))
	    inform (arg1.get_ప్రారంభం (),
		      "did you mean to dereference the pointer?");
	}
      లేకపోతే ఒకవేళ (సూచిక_TYPE_P (type2)
	       && null_సూచిక_constant_p (arg1.విలువ)
	       && char_type_p (type1))
	{
	  auto_diagnostic_సమూహం d;
	  ఒకవేళ (warning_at (location, OPT_Wpointer_compare,
			    "comparison between pointer and zero character "
			    "constant"))
	    inform (arg2.get_ప్రారంభం (),
		      "did you mean to dereference the pointer?");
	}
    }
  లేకపోతే ఒకవేళ (వృక్షం_సంకేతం_CLASS (సంకేతం_2) == tcc_comparison
	   && (code1 == STRING_CST || code2 == STRING_CST))
    warning_at (location, OPT_Waddress,
		"comparison with string literal results in unspecified "
		"behavior");

  ఒకవేళ (warn_zero_as_null_సూచిక_constant
      && c_inhibit_evaluation_warnings == 0
      && వృక్షం_సంకేతం_CLASS (సంకేతం_2) == tcc_comparison)
    {
      ఒకవేళ ((వృక్షం_సంకేతం (type1) == సూచిక_TYPE
	   || వృక్షం_సంకేతం (type1) == NULLPTR_TYPE)
	  && INTEGRAL_TYPE_P (type2)
	  && null_సూచిక_constant_p (arg2.విలువ))
	warning_at (arg2.get_location(), OPT_Wzero_as_null_సూచిక_constant,
		    "zero as null pointer constant");

      ఒకవేళ ((వృక్షం_సంకేతం (type2) == సూచిక_TYPE
	   || వృక్షం_సంకేతం (type2) == NULLPTR_TYPE)
	  && INTEGRAL_TYPE_P (type1)
	  && null_సూచిక_constant_p (arg1.విలువ))
	warning_at (arg1.get_location(), OPT_Wzero_as_null_సూచిక_constant,
		    "zero as null pointer constant");
    }

  ఒకవేళ (warn_array_compare
      && వృక్షం_సంకేతం_CLASS (సంకేతం_2) == tcc_comparison
      && వృక్షం_సంకేతం (type1) == ARRAY_TYPE
      && వృక్షం_సంకేతం (type2) == ARRAY_TYPE)
    do_warn_array_compare (location, సంకేతం_2, arg1.విలువ, arg2.విలువ);

  ఒకవేళ (వృక్షం_అధికప్రవాహం_P (ఫలితం.విలువ)
      && !వృక్షం_అధికప్రవాహం_P (arg1.విలువ)
      && !వృక్షం_అధికప్రవాహం_P (arg2.విలువ))
    అధికప్రవాహం_warning (location, ఫలితం.విలువ);

  /* Warn about comparisons of different enum types.  */
  ఒకవేళ (warn_enum_compare
      && వృక్షం_సంకేతం_CLASS (సంకేతం_2) == tcc_comparison
      && వృక్షం_సంకేతం (type1) == ENUMERAL_TYPE
      && వృక్షం_సంకేతం (type2) == ENUMERAL_TYPE
      && TYPE_MAIN_VARIANT (type1) != TYPE_MAIN_VARIANT (type2))
    warning_at (location, OPT_Wenum_compare,
		"comparison between %qT and %qT",
		type1, type2);

  ఒకవేళ (warn_xor_వాడిన_as_pow
      && సంకేతం_2 == బిట్టు_XOR_సమాసం
      && arg1.m_decimal
      && arg2.m_decimal)
    check_for_xor_వాడిన_as_pow (arg1.get_location (), arg1.విలువ,
			       location,
			       arg2.get_location (), arg2.విలువ);

  తిరిగి ఫలితం;
}

/* Return a tree for the difference of pointers OP0 and OP1.
   The resulting tree has type ptrdiff_t.  If POINTER_SUBTRACT sanitization is
   enabled, assign to INSTRUMENT_EXPR call to libsanitizer.  */

స్థిర వృక్షం
సూచిక_diff (location_t loc, వృక్షం op0, వృక్షం op1, వృక్షం *instrument_సమాసం)
{
  వృక్షం restype = ptrdiff_type_కణుపు;
  వృక్షం ఫలితం, inttype;

  addr_space_t as0 = TYPE_ADDR_SPACE (వృక్షం_TYPE (వృక్షం_TYPE (op0)));
  addr_space_t as1 = TYPE_ADDR_SPACE (వృక్షం_TYPE (వృక్షం_TYPE (op1)));
  వృక్షం లక్ష్యం_type = వృక్షం_TYPE (వృక్షం_TYPE (op0));
  వృక్షం orig_op0 = op0;
  వృక్షం orig_op1 = op1;

  /* If the operands point into different address spaces, we need to
     explicitly convert them to pointers into the common address space
     before we can subtract the numerical address values.  */
  ఒకవేళ (as0 != as1)
    {
      addr_space_t as_common;
      వృక్షం common_type;

      /* Determine the common superset address space.  This is guaranteed
	 to exist because the caller verified that comp_target_types
	 returned non-zero.  */
      ఒకవేళ (!addr_space_superset (as0, as1, &as_common))
	gcc_unreachable ();

      common_type = common_సూచిక_type (వృక్షం_TYPE (op0), వృక్షం_TYPE (op1), NULL_వృక్షం);
      op0 = convert (common_type, op0);
      op1 = convert (common_type, op1);
    }

  /* Determine integer type result of the subtraction.  This will usually
     be the same as the result type (ptrdiff_t), but may need to be a wider
     type if pointers for the address space are wider than ptrdiff_t.  */
  ఒకవేళ (TYPE_PRECISION (restype) < TYPE_PRECISION (వృక్షం_TYPE (op0)))
    inttype = c_common_type_for_కొలత (TYPE_PRECISION (వృక్షం_TYPE (op0)), 0);
  లేకపోతే
    inttype = restype;

  ఒకవేళ (VOID_TYPE_P (లక్ష్యం_type))
    pedwarn (loc, OPT_Wpointer_arith,
	     "pointer of type %<void *%> used in subtraction");
  ఒకవేళ (వృక్షం_సంకేతం (లక్ష్యం_type) == FUNCTION_TYPE)
    pedwarn (loc, OPT_Wpointer_arith,
	     "pointer to a function used in subtraction");

  ఒకవేళ (current_function_decl != NULL_వృక్షం
      && sanitize_flags_p (SANITIZE_సూచిక_వ్యవకలనం))
    {
      op0 = save_సమాసం (c_fully_fold (op0, అబద్ధం, ఖాళీ));
      op1 = save_సమాసం (c_fully_fold (op1, అబద్ధం, ఖాళీ));

      వృక్షం tt = builtin_decl_explicit (BUILT_లోపల_ASAN_సూచిక_వ్యవకలనం);
      *instrument_సమాసం = build_call_సమాసం_loc (loc, tt, 2, op0, op1);
    }

  /* First do the subtraction, then build the divide operator
     and only convert at the very end.
     Do not do default conversions in case restype is a short type.  */

  /* POINTER_DIFF_EXPR requires a signed integer type of the same size as
     pointers.  If some platform cannot provide that, or has a larger
     ptrdiff_type to support differences larger than half the address
     space, cast the pointers to some larger integer type and do the
     computations in that type.  */
  ఒకవేళ (TYPE_PRECISION (inttype) > TYPE_PRECISION (వృక్షం_TYPE (op0)))
    op0 = build_ద్విమాన_op (loc, MINUS_సమాసం, convert (inttype, op0),
			   convert (inttype, op1), అబద్ధం);
  లేకపోతే
    {
      /* Cast away qualifiers.  */
      op0 = convert (c_common_type (వృక్షం_TYPE (op0), వృక్షం_TYPE (op0)), op0);
      op1 = convert (c_common_type (వృక్షం_TYPE (op1), వృక్షం_TYPE (op1)), op1);
      op0 = build2_loc (loc, సూచిక_DIFF_సమాసం, inttype, op0, op1);
    }

  /* This generates an error if op1 is pointer to incomplete type.  */
  ఒకవేళ (!COMPLETE_OR_VOID_TYPE_P (వృక్షం_TYPE (వృక్షం_TYPE (orig_op1))))
    error_at (loc, "arithmetic on pointer to an incomplete type");
  లేకపోతే ఒకవేళ (verify_type_context (loc, TCTX_సూచిక_ARITH,
				వృక్షం_TYPE (వృక్షం_TYPE (orig_op0))))
    verify_type_context (loc, TCTX_సూచిక_ARITH,
			 వృక్షం_TYPE (వృక్షం_TYPE (orig_op1)));

  op1 = c_కొలత_లోపల_బైట్లు (లక్ష్యం_type);

  ఒకవేళ (సూచిక_గమ్యం_zero_sized_aggr_p (వృక్షం_TYPE (orig_op1)))
    error_at (loc, "arithmetic on pointer to an empty aggregate");

  /* Divide by the size, in easiest possible way.  */
  ఫలితం = fold_build2_loc (loc, EXACT_DIV_సమాసం, inttype,
			    op0, convert (inttype, op1));

  /* Convert to final result type if necessary.  */
  తిరిగి convert (restype, ఫలితం);
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

స్థిర వృక్షం
build_atomic_కేటాయించు (location_t loc, వృక్షం lhs, గణన వృక్షం_సంకేతం_2 modifycode,
		     వృక్షం rhs, తార్కిక return_old_p)
{
  వృక్షం fndecl, func_call;
  vec<వృక్షం, va_gc> *params;
  వృక్షం val, nonatomic_lhs_type, nonatomic_rhs_type, newval, newval_addr;
  వృక్షం old, old_addr;
  వృక్షం compound_stmt = NULL_వృక్షం;
  వృక్షం stmt, goto_stmt;
  వృక్షం loop_label, loop_decl, పూర్తి_label, పూర్తి_decl;

  వృక్షం lhs_type = వృక్షం_TYPE (lhs);
  వృక్షం lhs_addr = build_unary_op (loc, ADDR_సమాసం, lhs, అబద్ధం);
  వృక్షం seq_cst = build_int_cst (integer_type_కణుపు, MEMMODEL_SEQ_CST);
  వృక్షం rhs_semantic_type = వృక్షం_TYPE (rhs);
  వృక్షం nonatomic_rhs_semantic_type;
  వృక్షం rhs_type;

  gcc_assert (TYPE_ATOMIC (lhs_type));

  ఒకవేళ (return_old_p)
    gcc_assert (modifycode == PLUS_సమాసం || modifycode == MINUS_సమాసం);

  /* Allocate enough vector items for a compare_exchange.  */
  vec_alloc (params, 6);

  /* Create a compound statement to hold the sequence of statements
     with a loop.  */
  ఒకవేళ (modifycode != NOP_సమాసం)
    {
      compound_stmt = c_begin_compound_stmt (అబద్ధం);

      /* For consistency with build_modify_expr on non-_Atomic,
	 mark the lhs as read.  Also, it would be very hard to match
	 such expressions in mark_exp_read.  */
      mark_exp_read (lhs);
    }

  /* Remove any excess precision (which is only present here in the
     case of compound assignments).  */
  ఒకవేళ (వృక్షం_సంకేతం (rhs) == EXCESS_PRECISION_సమాసం)
    {
      gcc_assert (modifycode != NOP_సమాసం);
      rhs = వృక్షం_నిర్వాహ్యం (rhs, 0);
    }
  rhs_type = వృక్షం_TYPE (rhs);

  /* Fold the RHS if it hasn't already been folded.  */
  ఒకవేళ (modifycode != NOP_సమాసం)
    rhs = c_fully_fold (rhs, అబద్ధం, ఖాళీ);

  /* Remove the qualifiers for the rest of the expressions and create
     the VAL temp variable to hold the RHS.  */
  nonatomic_lhs_type = build_qualified_type (lhs_type, TYPE_UNQUALIFIED);
  nonatomic_rhs_type = build_qualified_type (rhs_type, TYPE_UNQUALIFIED);
  nonatomic_rhs_semantic_type = build_qualified_type (rhs_semantic_type,
						      TYPE_UNQUALIFIED);
  val = create_tmp_var_raw (nonatomic_rhs_type);
  వృక్షం_ADDRESSABLE (val) = 1;
  suppress_warning (val);
  rhs = build4 (లక్ష్యం_సమాసం, nonatomic_rhs_type, val, rhs, NULL_వృక్షం,
		NULL_వృక్షం);
  వృక్షం_SIDE_EFFECTS (rhs) = 1;
  సమితి_సమాసం_LOCATION (rhs, loc);
  ఒకవేళ (modifycode != NOP_సమాసం)
    కూడు_stmt (rhs);

  /* NOP_EXPR indicates it's a straight store of the RHS. Simply issue
     an atomic_store.  */
  ఒకవేళ (modifycode == NOP_సమాసం)
    {
      compound_stmt = rhs;
      /* Build __atomic_store (&lhs, &val, SEQ_CST)  */
      rhs = build_unary_op (loc, ADDR_సమాసం, val, అబద్ధం);
      fndecl = builtin_decl_explicit (BUILT_లోపల_ATOMIC_STORE);
      params->శీఘ్ర_నెట్టు (lhs_addr);
      params->శీఘ్ర_నెట్టు (rhs);
      params->శీఘ్ర_నెట్టు (seq_cst);
      func_call = c_build_function_call_vec (loc, vNULL, fndecl, params, ఖాళీ);

      compound_stmt = build2 (COMPOUND_సమాసం, void_type_కణుపు,
			      compound_stmt, func_call);

      /* VAL is the value which was stored, return a COMPOUND_STMT of
	 the statement and that value.  */
      తిరిగి build2 (COMPOUND_సమాసం, nonatomic_lhs_type, compound_stmt, val);
    }

  /* Attempt to implement the atomic operation as an __atomic_fetch_* or
     __atomic_*_fetch built-in rather than a CAS loop.  atomic_bool type
     isn't applicable for such builtins.  ??? Do we want to handle enums?  */
  ఒకవేళ ((వృక్షం_సంకేతం (lhs_type) == INTEGER_TYPE || సూచిక_TYPE_P (lhs_type))
      && వృక్షం_సంకేతం (rhs_type) == INTEGER_TYPE)
    {
      built_లోపల_function fncode;
      ఎంపిక (modifycode)
	{
	స్థితి PLUS_సమాసం:
	స్థితి సూచిక_PLUS_సమాసం:
	  fncode = (return_old_p
		    ? BUILT_లోపల_ATOMIC_FETCH_కూడు_N
		    : BUILT_లోపల_ATOMIC_కూడు_FETCH_N);
	  ఆపు;
	స్థితి MINUS_సమాసం:
	  fncode = (return_old_p
		    ? BUILT_లోపల_ATOMIC_FETCH_SUB_N
		    : BUILT_లోపల_ATOMIC_SUB_FETCH_N);
	  ఆపు;
	స్థితి బిట్టు_AND_సమాసం:
	  fncode = (return_old_p
		    ? BUILT_లోపల_ATOMIC_FETCH_AND_N
		    : BUILT_లోపల_ATOMIC_AND_FETCH_N);
	  ఆపు;
	స్థితి బిట్టు_IOR_సమాసం:
	  fncode = (return_old_p
		    ? BUILT_లోపల_ATOMIC_FETCH_OR_N
		    : BUILT_లోపల_ATOMIC_OR_FETCH_N);
	  ఆపు;
	స్థితి బిట్టు_XOR_సమాసం:
	  fncode = (return_old_p
		    ? BUILT_లోపల_ATOMIC_FETCH_XOR_N
		    : BUILT_లోపల_ATOMIC_XOR_FETCH_N);
	  ఆపు;
	అప్రమేయ:
	  వెళ్ళు cas_loop;
	}

      /* We can only use "_1" through "_16" variants of the atomic fetch
	 built-ins.  */
      గుర్తులేని HOST_WIDE_INT కొలత = వృక్షం_గమ్యం_uhwi (TYPE_కొలత_UNIT (lhs_type));
      ఒకవేళ (కొలత != 1 && కొలత != 2 && కొలత != 4 && కొలత != 8 && కొలత != 16)
	వెళ్ళు cas_loop;

      /* If this is a pointer type, we need to multiply by the size of
	 the pointer target type.  */
      ఒకవేళ (సూచిక_TYPE_P (lhs_type))
	{
	  ఒకవేళ (!COMPLETE_TYPE_P (వృక్షం_TYPE (lhs_type))
	      /* ??? This would introduce -Wdiscarded-qualifiers
		 warning: __atomic_fetch_* expect volatile void *
		 type as the first argument.  (Assignments between
		 atomic and non-atomic objects are OK.) */
	      || TYPE_RESTRICT (lhs_type))
	    వెళ్ళు cas_loop;
	  వృక్షం sz = TYPE_కొలత_UNIT (వృక్షం_TYPE (lhs_type));
	  rhs = fold_build2_loc (loc, MULT_సమాసం, ptrdiff_type_కణుపు,
				 convert (ptrdiff_type_కణుపు, rhs),
				 convert (ptrdiff_type_కణుపు, sz));
	}

      /* Build __atomic_fetch_* (&lhs, &val, SEQ_CST), or
	 __atomic_*_fetch (&lhs, &val, SEQ_CST).  */
      fndecl = builtin_decl_explicit (fncode);
      params->శీఘ్ర_నెట్టు (lhs_addr);
      params->శీఘ్ర_నెట్టు (rhs);
      params->శీఘ్ర_నెట్టు (seq_cst);
      func_call = c_build_function_call_vec (loc, vNULL, fndecl, params, ఖాళీ);

      newval = create_tmp_var_raw (nonatomic_lhs_type);
      వృక్షం_ADDRESSABLE (newval) = 1;
      suppress_warning (newval);
      rhs = build4 (లక్ష్యం_సమాసం, nonatomic_lhs_type, newval, func_call,
		    NULL_వృక్షం, NULL_వృక్షం);
      సమితి_సమాసం_LOCATION (rhs, loc);
      కూడు_stmt (rhs);

      /* Finish the compound statement.  */
      compound_stmt = c_చివర_compound_stmt (loc, compound_stmt, అబద్ధం);

      /* NEWVAL is the value which was stored, return a COMPOUND_STMT of
	 the statement and that value.  */
      తిరిగి build2 (COMPOUND_సమాసం, nonatomic_lhs_type, compound_stmt, newval);
    }

cas_loop:
  /* Create the variables and labels required for the op= form.  */
  old = create_tmp_var_raw (nonatomic_lhs_type);
  old_addr = build_unary_op (loc, ADDR_సమాసం, old, అబద్ధం);
  వృక్షం_ADDRESSABLE (old) = 1;
  suppress_warning (old);

  newval = create_tmp_var_raw (nonatomic_lhs_type);
  newval_addr = build_unary_op (loc, ADDR_సమాసం, newval, అబద్ధం);
  వృక్షం_ADDRESSABLE (newval) = 1;
  suppress_warning (newval);

  loop_decl = create_artificial_label (loc);
  loop_label = build1 (LABEL_సమాసం, void_type_కణుపు, loop_decl);

  పూర్తి_decl = create_artificial_label (loc);
  పూర్తి_label = build1 (LABEL_సమాసం, void_type_కణుపు, పూర్తి_decl);

  /* __atomic_load (addr, &old, SEQ_CST).  */
  fndecl = builtin_decl_explicit (BUILT_లోపల_ATOMIC_ఎక్కించు);
  params->శీఘ్ర_నెట్టు (lhs_addr);
  params->శీఘ్ర_నెట్టు (old_addr);
  params->శీఘ్ర_నెట్టు (seq_cst);
  func_call = c_build_function_call_vec (loc, vNULL, fndecl, params, ఖాళీ);
  old = build4 (లక్ష్యం_సమాసం, nonatomic_lhs_type, old, func_call, NULL_వృక్షం,
		NULL_వృక్షం);
  కూడు_stmt (old);
  params->truncate (0);

  /* Create the expressions for floating-point environment
     manipulation, if required.  */
  తార్కిక need_fenv = (flag_trapping_math
		    && (FLOAT_TYPE_P (lhs_type) || FLOAT_TYPE_P (rhs_type)));
  వృక్షం hold_call = NULL_వృక్షం, clear_call = NULL_వృక్షం, update_call = NULL_వృక్షం;
  ఒకవేళ (need_fenv)
    targetm.atomic_కేటాయించు_expand_fenv (&hold_call, &clear_call, &update_call);

  ఒకవేళ (hold_call)
    కూడు_stmt (hold_call);

  /* loop:  */
  కూడు_stmt (loop_label);

  /* newval = old + val;  */
  ఒకవేళ (rhs_type != rhs_semantic_type)
    val = build1 (EXCESS_PRECISION_సమాసం, nonatomic_rhs_semantic_type, val);
  rhs = build_ద్విమాన_op (loc, modifycode,
			 convert_lvalue_గమ్యం_rvalue (loc, old, నిజం, నిజం),
			 val, నిజం);
  ఒకవేళ (వృక్షం_సంకేతం (rhs) == EXCESS_PRECISION_సమాసం)
    {
      వృక్షం eptype = వృక్షం_TYPE (rhs);
      rhs = c_fully_fold (వృక్షం_నిర్వాహ్యం (rhs, 0), అబద్ధం, ఖాళీ);
      rhs = build1 (EXCESS_PRECISION_సమాసం, eptype, rhs);
    }
  లేకపోతే
    rhs = c_fully_fold (rhs, అబద్ధం, ఖాళీ);
  rhs = convert_for_assignment (loc, UNKNOWN_LOCATION, nonatomic_lhs_type,
				rhs, NULL_వృక్షం, ic_కేటాయించు, అబద్ధం, NULL_వృక్షం,
				NULL_వృక్షం, 0);
  /* The temporary variable for NEWVAL is only gimplified correctly (in
     particular, given a DECL_CONTEXT) if used in a TARGET_EXPR.  To avoid
     subsequent ICEs in nested function processing after an error, ensure such
     a TARGET_EXPR is built even after an error.  */
  ఒకవేళ (rhs == error_mark_కణుపు)
    rhs = old;
  rhs = build4 (లక్ష్యం_సమాసం, nonatomic_lhs_type, newval, rhs, NULL_వృక్షం,
		NULL_వృక్షం);
  సమితి_సమాసం_LOCATION (rhs, loc);
  కూడు_stmt (rhs);

  /* if (__atomic_compare_exchange (addr, &old, &new, false, SEQ_CST, SEQ_CST))
       goto done;  */
  fndecl = builtin_decl_explicit (BUILT_లోపల_ATOMIC_COMPARE_EXCHANGE);
  params->శీఘ్ర_నెట్టు (lhs_addr);
  params->శీఘ్ర_నెట్టు (old_addr);
  params->శీఘ్ర_నెట్టు (newval_addr);
  params->శీఘ్ర_నెట్టు (integer_zero_కణుపు);
  params->శీఘ్ర_నెట్టు (seq_cst);
  params->శీఘ్ర_నెట్టు (seq_cst);
  func_call = c_build_function_call_vec (loc, vNULL, fndecl, params, ఖాళీ);

  goto_stmt = build1 (GOTO_సమాసం, void_type_కణుపు, పూర్తి_decl);
  సమితి_సమాసం_LOCATION (goto_stmt, loc);

  stmt = build3 (COND_సమాసం, void_type_కణుపు, func_call, goto_stmt, NULL_వృక్షం);
  సమితి_సమాసం_LOCATION (stmt, loc);
  కూడు_stmt (stmt);

  ఒకవేళ (clear_call)
    కూడు_stmt (clear_call);

  /* goto loop;  */
  goto_stmt  = build1 (GOTO_సమాసం, void_type_కణుపు, loop_decl);
  సమితి_సమాసం_LOCATION (goto_stmt, loc);
  కూడు_stmt (goto_stmt);

  /* done:  */
  కూడు_stmt (పూర్తి_label);

  ఒకవేళ (update_call)
    కూడు_stmt (update_call);

  /* Finish the compound statement.  */
  compound_stmt = c_చివర_compound_stmt (loc, compound_stmt, అబద్ధం);

  /* NEWVAL is the value that was successfully stored, return a
     COMPOUND_EXPR of the statement and the appropriate value.  */
  తిరిగి build2 (COMPOUND_సమాసం, nonatomic_lhs_type, compound_stmt,
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

వృక్షం
build_unary_op (location_t location, గణన వృక్షం_సంకేతం_2 సంకేతం_2, వృక్షం xarg,
		తార్కిక noconvert)
{
  /* No default_conversion here.  It causes trouble for ADDR_EXPR.  */
  వృక్షం arg = xarg;
  వృక్షం argtype = NULL_వృక్షం;
  గణన వృక్షం_సంకేతం_2 typecode;
  వృక్షం val;
  వృక్షం ret = error_mark_కణుపు;
  వృక్షం eptype = NULL_వృక్షం;
  స్థిరరాశి అక్షరం *invalid_op_diag;

  /* If ARG is wrapped in a call to .ACCESS_WITH_SIZE — created when the
     C parser rvalue-converts a counted_by-annotated member access (see
     PR123569) — unwrap it here.  Unary operators that consume an rvalue
     (!, -, +) read the value itself rather than dereferencing into the
     pointed-to data, so the bounds-checking wrapper is unnecessary and
     would otherwise reach build_unary_op while it is not equipped to
     handle the wrapped form.  PR123569 fixed the ++/-- side of this by
     suppressing wrapper creation in the parser; the rvalue-consuming
     ops still receive the wrapper and need to strip it here.  */
  ఒకవేళ (is_access_with_కొలత_p (arg))
    xarg = arg = get_ref_from_access_with_కొలత (arg);

  gcc_checking_assert (!is_access_with_కొలత_p (arg));

  తార్కిక int_operands = సమాసం_INT_CONST_OPERANDS (xarg);
  ఒకవేళ (int_operands)
    arg = remove_c_maybe_const_సమాసం (arg);

  ఒకవేళ (సంకేతం_2 != ADDR_సమాసం)
    arg = require_complete_type (location, arg);

  typecode = వృక్షం_సంకేతం (వృక్షం_TYPE (arg));
  ఒకవేళ (typecode == ERROR_MARK)
    తిరిగి error_mark_కణుపు;
  ఒకవేళ (typecode == ENUMERAL_TYPE || typecode == BOOLEAN_TYPE)
    typecode = INTEGER_TYPE;

  ఒకవేళ ((invalid_op_diag
       = targetm.invalid_unary_op (సంకేతం_2, వృక్షం_TYPE (xarg))))
    {
      error_at (location, invalid_op_diag);
      తిరిగి error_mark_కణుపు;
    }

  ఒకవేళ (వృక్షం_సంకేతం (arg) == EXCESS_PRECISION_సమాసం)
    {
      eptype = వృక్షం_TYPE (arg);
      arg = వృక్షం_నిర్వాహ్యం (arg, 0);
    }

  ఎంపిక (సంకేతం_2)
    {
    స్థితి CONVERT_సమాసం:
      /* This is used for unary plus, because a CONVERT_EXPR
	 is enough to prevent anybody from looking inside for
	 associativity, but won't generate any code.  */
      ఒకవేళ (!(typecode == INTEGER_TYPE || typecode == REAL_TYPE
	    || typecode == FIXED_బిందువు_TYPE || typecode == COMPLEX_TYPE
	    || typecode == BITINT_TYPE
	    || gnu_సదిశ_type_p (వృక్షం_TYPE (arg))))
	{
	  error_at (location, "wrong type argument to unary plus");
	  తిరిగి error_mark_కణుపు;
	}
      లేకపోతే ఒకవేళ (!noconvert)
	arg = default_conversion (arg);
      arg = non_lvalue_loc (location, arg);
      ఆపు;

    స్థితి NEGATE_సమాసం:
      ఒకవేళ (!(typecode == INTEGER_TYPE || typecode == REAL_TYPE
	    || typecode == FIXED_బిందువు_TYPE || typecode == COMPLEX_TYPE
	    || typecode == BITINT_TYPE
	    || gnu_సదిశ_type_p (వృక్షం_TYPE (arg))))
	{
	  error_at (location, "wrong type argument to unary minus");
	  తిరిగి error_mark_కణుపు;
	}
      లేకపోతే ఒకవేళ (!noconvert)
	arg = default_conversion (arg);
      ఆపు;

    స్థితి బిట్టు_NOT_సమాసం:
      /* ~ works on integer types and non float vectors. */
      ఒకవేళ (typecode == INTEGER_TYPE
	  || typecode == BITINT_TYPE
	  || (gnu_సదిశ_type_p (వృక్షం_TYPE (arg))
	      && !సదిశ_FLOAT_TYPE_P (వృక్షం_TYPE (arg))))
	{
	  వృక్షం e = arg;

	  /* Warn if the expression has boolean value.  */
	  అయితే (వృక్షం_సంకేతం (e) == COMPOUND_సమాసం)
	    e = వృక్షం_నిర్వాహ్యం (e, 1);

	  ఒకవేళ ((C_BOOLEAN_TYPE_P (వృక్షం_TYPE (arg))
	       || truth_విలువ_p (వృక్షం_సంకేతం (e))))
	    {
	      auto_diagnostic_సమూహం d;
	      ఒకవేళ (warning_at (location, OPT_Wbool_operation,
				"%<~%> on a boolean expression"))
		{
		  gcc_rich_location richloc (location);
		  richloc.కూడు_fixit_చొప్పించు_before (location, "!");
		  inform (&richloc, "did you mean to use logical not?");
		}
	    }
	  ఒకవేళ (!noconvert)
	    arg = default_conversion (arg);
	}
      లేకపోతే ఒకవేళ (typecode == COMPLEX_TYPE)
	{
	  సంకేతం_2 = CONJ_సమాసం;
	  pedwarn (location, OPT_Wpedantic,
		   "ISO C does not support %<~%> for complex conjugation");
	  ఒకవేళ (!noconvert)
	    arg = default_conversion (arg);
	}
      లేకపోతే
	{
	  error_at (location, "wrong type argument to bit-complement");
	  తిరిగి error_mark_కణుపు;
	}
      ఆపు;

    స్థితి ABS_సమాసం:
      ఒకవేళ (!(typecode == INTEGER_TYPE || typecode == REAL_TYPE))
	{
	  error_at (location, "wrong type argument to abs");
	  తిరిగి error_mark_కణుపు;
	}
      లేకపోతే ఒకవేళ (!noconvert)
	arg = default_conversion (arg);
      ఆపు;

    స్థితి ABSU_సమాసం:
      ఒకవేళ (!(typecode == INTEGER_TYPE))
	{
	  error_at (location, "wrong type argument to absu");
	  తిరిగి error_mark_కణుపు;
	}
      లేకపోతే ఒకవేళ (!noconvert)
	arg = default_conversion (arg);
      ఆపు;

    స్థితి CONJ_సమాసం:
      /* Conjugating a real value is a no-op, but allow it anyway.  */
      ఒకవేళ (!(typecode == INTEGER_TYPE || typecode == REAL_TYPE
	    || typecode == COMPLEX_TYPE))
	{
	  error_at (location, "wrong type argument to conjugation");
	  తిరిగి error_mark_కణుపు;
	}
      లేకపోతే ఒకవేళ (!noconvert)
	arg = default_conversion (arg);
      ఆపు;

    స్థితి TRUTH_NOT_సమాసం:
      ఒకవేళ (typecode != INTEGER_TYPE && typecode != FIXED_బిందువు_TYPE
	  && typecode != REAL_TYPE && typecode != సూచిక_TYPE
	  && typecode != COMPLEX_TYPE && typecode != NULLPTR_TYPE
	  && typecode != BITINT_TYPE)
	{
	  error_at (location,
		    "wrong type argument to unary exclamation mark");
	  తిరిగి error_mark_కణుపు;
	}
      ఒకవేళ (int_operands)
	{
	  arg = c_objc_common_truthvalue_conversion (location, xarg);
	  arg = remove_c_maybe_const_సమాసం (arg);
	}
      లేకపోతే
	arg = c_objc_common_truthvalue_conversion (location, arg);
      ret = invert_truthvalue_loc (location, arg);
      eptype = NULL_వృక్షం;
      /* If the TRUTH_NOT_EXPR has been folded, reset the location.  */
      ఒకవేళ (సమాసం_P (ret) && సమాసం_HAS_LOCATION (ret))
	location = సమాసం_LOCATION (ret);
      వెళ్ళు return_build_unary_op;

    స్థితి REALPART_సమాసం:
    స్థితి IMAGPART_సమాసం:
      ret = build_real_imag_సమాసం (location, సంకేతం_2, arg);
      ఒకవేళ (ret == error_mark_కణుపు)
	తిరిగి error_mark_కణుపు;
      ఒకవేళ (eptype && వృక్షం_సంకేతం (eptype) == COMPLEX_TYPE)
	eptype = వృక్షం_TYPE (eptype);
      వెళ్ళు return_build_unary_op;

    స్థితి PREINCREMENT_సమాసం:
    స్థితి POSTINCREMENT_సమాసం:
    స్థితి PREDECREMENT_సమాసం:
    స్థితి POSTDECREMENT_సమాసం:

      ఒకవేళ (వృక్షం_సంకేతం (arg) == C_MAYBE_CONST_సమాసం)
	{
	  వృక్షం inner = build_unary_op (location, సంకేతం_2,
				       C_MAYBE_CONST_సమాసం_సమాసం (arg),
				       noconvert);
	  ఒకవేళ (inner == error_mark_కణుపు)
	    తిరిగి error_mark_కణుపు;
	  ret = build2 (C_MAYBE_CONST_సమాసం, వృక్షం_TYPE (inner),
			C_MAYBE_CONST_సమాసం_PRE (arg), inner);
	  gcc_assert (!C_MAYBE_CONST_సమాసం_INT_OPERANDS (arg));
	  C_MAYBE_CONST_సమాసం_NON_CONST (ret) = 1;
	  వెళ్ళు return_build_unary_op;
	}

      /* Complain about anything that is not a true lvalue.  In
	 Objective-C, skip this check for property_refs.  */
      ఒకవేళ (!objc_is_property_ref (arg)
	  && !lvalue_or_else (location,
			      arg, ((సంకేతం_2 == PREINCREMENT_సమాసం
				     || సంకేతం_2 == POSTINCREMENT_సమాసం)
				    ? lv_increment
				    : lv_decrement)))
	తిరిగి error_mark_కణుపు;

      ఒకవేళ (warn_cxx_compat && వృక్షం_సంకేతం (వృక్షం_TYPE (arg)) == ENUMERAL_TYPE)
	{
	  ఒకవేళ (సంకేతం_2 == PREINCREMENT_సమాసం || సంకేతం_2 == POSTINCREMENT_సమాసం)
	    warning_at (location, OPT_Wc___compat,
			"increment of enumeration value is invalid in C++");
	  లేకపోతే
	    warning_at (location, OPT_Wc___compat,
			"decrement of enumeration value is invalid in C++");
	}

      ఒకవేళ (C_BOOLEAN_TYPE_P (వృక్షం_TYPE (arg)))
	{
	  ఒకవేళ (సంకేతం_2 == PREINCREMENT_సమాసం || సంకేతం_2 == POSTINCREMENT_సమాసం)
	    warning_at (location, OPT_Wbool_operation,
			"increment of a boolean expression");
	  లేకపోతే
	    warning_at (location, OPT_Wbool_operation,
			"decrement of a boolean expression");
	}

      /* Ensure the argument is fully folded inside any SAVE_EXPR.  */
      arg = c_fully_fold (arg, అబద్ధం, ఖాళీ, నిజం);

      తార్కిక atomic_op;
      atomic_op = really_atomic_lvalue (arg);

      /* Increment or decrement the real part of the value,
	 and don't change the imaginary part.  */
      ఒకవేళ (typecode == COMPLEX_TYPE)
	{
	  వృక్షం real, imag;

	  pedwarn_c23 (location, OPT_Wpedantic,
		       "ISO C does not support %<++%> and %<--%> on complex "
		       "types before C2Y");

	  ఒకవేళ (!atomic_op)
	    {
	      arg = stabilize_reference (arg);
	      real = build_unary_op (సమాసం_LOCATION (arg), REALPART_సమాసం, arg,
				     నిజం);
	      imag = build_unary_op (సమాసం_LOCATION (arg), IMAGPART_సమాసం, arg,
				     నిజం);
	      real = build_unary_op (సమాసం_LOCATION (arg), సంకేతం_2, real, నిజం);
	      ఒకవేళ (real == error_mark_కణుపు || imag == error_mark_కణుపు)
		తిరిగి error_mark_కణుపు;
	      ret = build2 (COMPLEX_సమాసం, వృక్షం_TYPE (arg),
			    real, imag);
	      వెళ్ళు return_build_unary_op;
	    }
	}

      /* Report invalid types.  */

      ఒకవేళ (typecode != సూచిక_TYPE && typecode != FIXED_బిందువు_TYPE
	  && typecode != INTEGER_TYPE && typecode != REAL_TYPE
	  && typecode != COMPLEX_TYPE && typecode != BITINT_TYPE
	  && !gnu_సదిశ_type_p (వృక్షం_TYPE (arg)))
	{
	  ఒకవేళ (సంకేతం_2 == PREINCREMENT_సమాసం || సంకేతం_2 == POSTINCREMENT_సమాసం)
	    error_at (location, "wrong type argument to increment");
	  లేకపోతే
	    error_at (location, "wrong type argument to decrement");

	  తిరిగి error_mark_కణుపు;
	}

      {
	వృక్షం inc;

	argtype = వృక్షం_TYPE (arg);

	/* Compute the increment.  */

	ఒకవేళ (typecode == సూచిక_TYPE)
	  {
	    /* If pointer target is an incomplete type,
	       we just cannot know how to do the arithmetic.  */
	    ఒకవేళ (!COMPLETE_OR_VOID_TYPE_P (వృక్షం_TYPE (argtype)))
	      {
		ఒకవేళ (సంకేతం_2 == PREINCREMENT_సమాసం || సంకేతం_2 == POSTINCREMENT_సమాసం)
		  error_at (location,
			    "increment of pointer to an incomplete type %qT",
			    వృక్షం_TYPE (argtype));
		లేకపోతే
		  error_at (location,
			    "decrement of pointer to an incomplete type %qT",
			    వృక్షం_TYPE (argtype));
	      }
	    లేకపోతే ఒకవేళ (వృక్షం_సంకేతం (వృక్షం_TYPE (argtype)) == FUNCTION_TYPE
		     || VOID_TYPE_P (వృక్షం_TYPE (argtype)))
	      {
		ఒకవేళ (సంకేతం_2 == PREINCREMENT_సమాసం || సంకేతం_2 == POSTINCREMENT_సమాసం)
		  pedwarn (location, OPT_Wpointer_arith,
			   "wrong type argument to increment");
		లేకపోతే
		  pedwarn (location, OPT_Wpointer_arith,
			   "wrong type argument to decrement");
	      }
	    లేకపోతే
	      verify_type_context (location, TCTX_సూచిక_ARITH,
				   వృక్షం_TYPE (argtype));

	    inc = c_కొలత_లోపల_బైట్లు (వృక్షం_TYPE (argtype));
	    inc = convert_గమ్యం_ptrofftype_loc (location, inc);
	  }
	లేకపోతే ఒకవేళ (FRACT_బహుళకం_P (TYPE_బహుళకం (argtype)))
	  {
	    /* For signed fract types, we invert ++ to -- or
	       -- to ++, and change inc from 1 to -1, because
	       it is not possible to represent 1 in signed fract constants.
	       For unsigned fract types, the result always overflows and
	       we get an undefined (original) or the maximum value.  */
	    ఒకవేళ (సంకేతం_2 == PREINCREMENT_సమాసం)
	      సంకేతం_2 = PREDECREMENT_సమాసం;
	    లేకపోతే ఒకవేళ (సంకేతం_2 == PREDECREMENT_సమాసం)
	      సంకేతం_2 = PREINCREMENT_సమాసం;
	    లేకపోతే ఒకవేళ (సంకేతం_2 == POSTINCREMENT_సమాసం)
	      సంకేతం_2 = POSTDECREMENT_సమాసం;
	    లేకపోతే /* code == POSTDECREMENT_EXPR  */
	      సంకేతం_2 = POSTINCREMENT_సమాసం;

	    inc = integer_minus_one_కణుపు;
	    inc = convert (argtype, inc);
	  }
	లేకపోతే
	  {
	    inc = సదిశ_TYPE_P (argtype)
	      ? build_one_cst (argtype)
	      : integer_one_కణుపు;
	    inc = convert (argtype, inc);
	  }

	/* If 'arg' is an Objective-C PROPERTY_REF expression, then we
	   need to ask Objective-C to build the increment or decrement
	   expression for it.  */
	ఒకవేళ (objc_is_property_ref (arg))
	  తిరిగి objc_build_incr_సమాసం_for_property_ref (location, సంకేతం_2,
							arg, inc);

	/* Report a read-only lvalue.  */
	ఒకవేళ (TYPE_READONLY (argtype))
	  {
	    readonly_error (location, arg,
			    ((సంకేతం_2 == PREINCREMENT_సమాసం
			      || సంకేతం_2 == POSTINCREMENT_సమాసం)
			     ? lv_increment : lv_decrement));
	    తిరిగి error_mark_కణుపు;
	  }
	లేకపోతే ఒకవేళ (వృక్షం_READONLY (arg))
	  readonly_warning (arg,
			    ((సంకేతం_2 == PREINCREMENT_సమాసం
			      || సంకేతం_2 == POSTINCREMENT_సమాసం)
			     ? lv_increment : lv_decrement));

	/* If the argument is atomic, use the special code sequences for
	   atomic compound assignment.  */
	ఒకవేళ (atomic_op)
	  {
	    arg = stabilize_reference (arg);
	    ret = build_atomic_కేటాయించు (location, arg,
				       ((సంకేతం_2 == PREINCREMENT_సమాసం
					 || సంకేతం_2 == POSTINCREMENT_సమాసం)
					? PLUS_సమాసం
					: MINUS_సమాసం),
				       (FRACT_బహుళకం_P (TYPE_బహుళకం (argtype))
					? inc
					: integer_one_కణుపు),
				       (సంకేతం_2 == POSTINCREMENT_సమాసం
					|| సంకేతం_2 == POSTDECREMENT_సమాసం));
	    వెళ్ళు return_build_unary_op;
	  }

	వృక్షం true_res;
	ఒకవేళ (c_hardbool_type_attr (వృక్షం_TYPE (arg), ఖాళీ, &true_res))
	  {
	    వృక్షం larg = stabilize_reference (arg);
	    వృక్షం sarg = save_సమాసం (larg);
	    ఎంపిక (సంకేతం_2)
	      {
	      స్థితి PREINCREMENT_సమాసం:
		val = build2 (MODIFY_సమాసం, వృక్షం_TYPE (larg), larg, true_res);
		val = build2 (COMPOUND_సమాసం, వృక్షం_TYPE (larg), sarg, val);
		ఆపు;
	      స్థితి POSTINCREMENT_సమాసం:
		val = build2 (MODIFY_సమాసం, వృక్షం_TYPE (larg), larg, true_res);
		val = build2 (COMPOUND_సమాసం, వృక్షం_TYPE (larg), val, sarg);
		val = build2 (COMPOUND_సమాసం, వృక్షం_TYPE (larg), sarg, val);
		ఆపు;
	      స్థితి PREDECREMENT_సమాసం:
		{
		  వృక్షం rarg = convert_lvalue_గమ్యం_rvalue (location, sarg,
							నిజం, నిజం);
		  rarg = invert_truthvalue_loc (location, rarg);
		  rarg = convert (వృక్షం_TYPE (sarg), rarg);
		  val = build2 (MODIFY_సమాసం, వృక్షం_TYPE (larg), larg, rarg);
		}
		ఆపు;
	      స్థితి POSTDECREMENT_సమాసం:
		{
		  వృక్షం rarg = convert_lvalue_గమ్యం_rvalue (location, sarg,
							నిజం, నిజం);
		  rarg = invert_truthvalue_loc (location, rarg);
		  వృక్షం iarg = convert (వృక్షం_TYPE (larg), rarg);
		  val = build2 (MODIFY_సమాసం, వృక్షం_TYPE (larg), larg, iarg);
		  val = build2 (COMPOUND_సమాసం, వృక్షం_TYPE (larg), val, sarg);
		  val = build2 (COMPOUND_సమాసం, వృక్షం_TYPE (larg), sarg, val);
		}
		ఆపు;
	      అప్రమేయ:
		gcc_unreachable ();
	      }
	    వృక్షం_SIDE_EFFECTS (val) = 1;
	  }
	లేకపోతే ఒకవేళ (C_BOOLEAN_TYPE_P (వృక్షం_TYPE (arg)))
	  val = boolean_increment (సంకేతం_2, arg);
	లేకపోతే
	  val = build2 (సంకేతం_2, వృక్షం_TYPE (arg), arg, inc);
	వృక్షం_SIDE_EFFECTS (val) = 1;
	ఒకవేళ (TYPE_QUALS (వృక్షం_TYPE (val)) != TYPE_UNQUALIFIED)
	  వృక్షం_TYPE (val) = c_build_qualified_type (వృక్షం_TYPE (val),
						    TYPE_UNQUALIFIED);
	ret = val;
	వెళ్ళు return_build_unary_op;
      }

    స్థితి ADDR_సమాసం:
      /* Note that this operation never does default_conversion.  */

      /* The operand of unary '&' must be an lvalue (which excludes
	 expressions of type void), or, in C99, the result of a [] or
	 unary '*' operator.  */
      ఒకవేళ (VOID_TYPE_P (వృక్షం_TYPE (arg))
	  && TYPE_QUALS (వృక్షం_TYPE (arg)) == TYPE_UNQUALIFIED
	  && (!పరోక్ష_REF_P (arg) || !flag_isoc99))
	pedwarn (location, 0, "taking address of expression of type %<void%>");

      /* Let &* cancel out to simplify resulting code.  */
      ఒకవేళ (పరోక్ష_REF_P (arg))
	{
	  /* Don't let this be an lvalue.  */
	  ఒకవేళ (lvalue_p (వృక్షం_నిర్వాహ్యం (arg, 0)))
	    తిరిగి non_lvalue_loc (location, వృక్షం_నిర్వాహ్యం (arg, 0));
	  ret = వృక్షం_నిర్వాహ్యం (arg, 0);
	  వెళ్ళు return_build_unary_op;
	}

      /* Anything not already handled and not a true memory reference
	 or a non-lvalue array is an error.  */
      ఒకవేళ (typecode != FUNCTION_TYPE && !noconvert
	  && !lvalue_or_else (location, arg, lv_addressof))
	తిరిగి error_mark_కణుపు;

      /* Move address operations inside C_MAYBE_CONST_EXPR to simplify
	 folding later.  */
      ఒకవేళ (వృక్షం_సంకేతం (arg) == C_MAYBE_CONST_సమాసం)
	{
	  వృక్షం inner = build_unary_op (location, సంకేతం_2,
				       C_MAYBE_CONST_సమాసం_సమాసం (arg),
				       noconvert);
	  ret = build2 (C_MAYBE_CONST_సమాసం, వృక్షం_TYPE (inner),
			C_MAYBE_CONST_సమాసం_PRE (arg), inner);
	  gcc_assert (!C_MAYBE_CONST_సమాసం_INT_OPERANDS (arg));
	  C_MAYBE_CONST_సమాసం_NON_CONST (ret)
	    = C_MAYBE_CONST_సమాసం_NON_CONST (arg);
	  వెళ్ళు return_build_unary_op;
	}

      /* Ordinary case; arg is a COMPONENT_REF or a decl.  */

      argtype = వృక్షం_TYPE (arg);

      /* If the lvalue is const or volatile, merge that into the type
	 to which the address will point.  This is only needed
	 for function types.  */
      ఒకవేళ ((DECL_P (arg) || REFERENCE_CLASS_P (arg))
	  && (వృక్షం_READONLY (arg) || వృక్షం_THIS_VOLATILE (arg))
	  && వృక్షం_సంకేతం (argtype) == FUNCTION_TYPE)
	{
	  పూర్ణాంకం orig_quals = TYPE_QUALS (strip_array_types (argtype));
	  పూర్ణాంకం quals = orig_quals;

	  ఒకవేళ (వృక్షం_READONLY (arg))
	    quals |= TYPE_QUAL_CONST;
	  ఒకవేళ (వృక్షం_THIS_VOLATILE (arg))
	    quals |= TYPE_QUAL_VOLATILE;

	  argtype = c_build_qualified_type (argtype, quals);
	}

      ఎంపిక (వృక్షం_సంకేతం (arg))
	{
	స్థితి COMPONENT_REF:
	  ఒకవేళ (DECL_C_బిట్టు_క్షేత్రం (వృక్షం_నిర్వాహ్యం (arg, 1)))
	    {
	      error_at (location, "cannot take address of bit-field %qD",
			వృక్షం_నిర్వాహ్యం (arg, 1));
	      తిరిగి error_mark_కణుపు;
	    }

	  /* fall through */

	స్థితి ARRAY_REF:
	  ఒకవేళ (TYPE_తిరగేయి_STORAGE_క్రమం (వృక్షం_TYPE (వృక్షం_నిర్వాహ్యం (arg, 0))))
	    {
	      ఒకవేళ (!AGGREGATE_TYPE_P (వృక్షం_TYPE (arg))
		  && !సూచిక_TYPE_P (వృక్షం_TYPE (arg))
		  && !సదిశ_TYPE_P (వృక్షం_TYPE (arg)))
		{
		  error_at (location, "cannot take address of scalar with "
			    "reverse storage order");
		  తిరిగి error_mark_కణుపు;
		}

	      ఒకవేళ (వృక్షం_సంకేతం (వృక్షం_TYPE (arg)) == ARRAY_TYPE
		  && TYPE_తిరగేయి_STORAGE_క్రమం (వృక్షం_TYPE (arg)))
		warning_at (location, OPT_Wscalar_storage_క్రమం,
			    "address of array with reverse scalar storage "
			    "order requested");
	    }

	అప్రమేయ:
	  ఆపు;
	}

      ఒకవేళ (!c_mark_addressable (arg))
	తిరిగి error_mark_కణుపు;

      gcc_assert (వృక్షం_సంకేతం (arg) != COMPONENT_REF
		  || !DECL_C_బిట్టు_క్షేత్రం (వృక్షం_నిర్వాహ్యం (arg, 1)));

      argtype = c_build_సూచిక_type (argtype);

      /* ??? Cope with user tricks that amount to offsetof.  Delete this
	 when we have proper support for integer constant expressions.  */
      val = get_పునాది_చిరునామా (arg);
      ఒకవేళ (val && పరోక్ష_REF_P (val)
          && వృక్షం_CONSTANT (వృక్షం_నిర్వాహ్యం (val, 0)))
	{
	  ret = fold_offsetof (arg, argtype);
	  వెళ్ళు return_build_unary_op;
	}

      val = build1 (ADDR_సమాసం, argtype, arg);

      ret = val;
      వెళ్ళు return_build_unary_op;

    స్థితి PAREN_సమాసం:
      ret = build1 (సంకేతం_2, వృక్షం_TYPE (arg), arg);
      వెళ్ళు return_build_unary_op;

    అప్రమేయ:
      gcc_unreachable ();
    }

  ఒకవేళ (argtype == NULL_వృక్షం)
    argtype = వృక్షం_TYPE (arg);
  ఒకవేళ (వృక్షం_సంకేతం (arg) == INTEGER_CST)
    ret = (require_constant_విలువ
	   ? fold_build1_initializer_loc (location, సంకేతం_2, argtype, arg)
	   : fold_build1_loc (location, సంకేతం_2, argtype, arg));
  లేకపోతే
    ret = build1 (సంకేతం_2, argtype, arg);
 return_build_unary_op:
  gcc_assert (ret != error_mark_కణుపు);
  ఒకవేళ (వృక్షం_సంకేతం (ret) == INTEGER_CST && !వృక్షం_అధికప్రవాహం (ret)
      && !(వృక్షం_సంకేతం (xarg) == INTEGER_CST && !వృక్షం_అధికప్రవాహం (xarg)))
    ret = build1 (NOP_సమాసం, వృక్షం_TYPE (ret), ret);
  లేకపోతే ఒకవేళ (వృక్షం_సంకేతం (ret) != INTEGER_CST && int_operands)
    ret = note_integer_operands (ret);
  ఒకవేళ (eptype)
    ret = build1 (EXCESS_PRECISION_సమాసం, eptype, ret);
  protected_సమితి_సమాసం_location (ret, location);
  తిరిగి ret;
}

/* Return nonzero if REF is an lvalue valid for this language.
   Lvalues can be assigned, unless their type has TYPE_READONLY.
   Lvalues can have their address taken, unless they have C_DECL_REGISTER.  */

తార్కిక
lvalue_p (const_వృక్షం ref)
{
  స్థిరరాశి గణన వృక్షం_సంకేతం_2 సంకేతం_2 = వృక్షం_సంకేతం (ref);

  ఎంపిక (సంకేతం_2)
    {
    స్థితి REALPART_సమాసం:
    స్థితి IMAGPART_సమాసం:
    స్థితి COMPONENT_REF:
      తిరిగి lvalue_p (వృక్షం_నిర్వాహ్యం (ref, 0));

    స్థితి C_MAYBE_CONST_సమాసం:
      తిరిగి lvalue_p (వృక్షం_నిర్వాహ్యం (ref, 1));

    స్థితి COMPOUND_LITERAL_సమాసం:
    స్థితి STRING_CST:
      తిరిగి నిజం;

    స్థితి MEM_REF:
    స్థితి లక్ష్యం_MEM_REF:
      /* MEM_REFs can appear from -fgimple parsing or folding, so allow them
	 here as well.  */
    స్థితి పరోక్ష_REF:
    స్థితి ARRAY_REF:
    స్థితి VAR_DECL:
    స్థితి PARM_DECL:
    స్థితి ఫలితం_DECL:
    స్థితి ERROR_MARK:
      తిరిగి (వృక్షం_సంకేతం (వృక్షం_TYPE (ref)) != FUNCTION_TYPE
	      && వృక్షం_సంకేతం (వృక్షం_TYPE (ref)) != పద్ధతి_TYPE);

    స్థితి BIND_సమాసం:
      తిరిగి వృక్షం_సంకేతం (వృక్షం_TYPE (ref)) == ARRAY_TYPE;

    స్థితి CALL_సమాసం:
      తిరిగి is_access_with_కొలత_p (ref);

    అప్రమేయ:
      తిరిగి అబద్ధం;
    }
}

/* Give a warning for storing in something that is read-only in GCC
   terms but not const in ISO C terms.  */

స్థిర శూన్య
readonly_warning (వృక్షం arg, గణన lvalue_use use)
{
  ఎంపిక (use)
    {
    స్థితి lv_కేటాయించు:
      warning (0, "assignment of read-only location %qE", arg);
      ఆపు;
    స్థితి lv_increment:
      warning (0, "increment of read-only location %qE", arg);
      ఆపు;
    స్థితి lv_decrement:
      warning (0, "decrement of read-only location %qE", arg);
      ఆపు;
    అప్రమేయ:
      gcc_unreachable ();
    }
  తిరిగి;
}


/* Return nonzero if REF is an lvalue valid for this language;
   otherwise, print an error message and return zero.  USE says
   how the lvalue is being used and so selects the error message.
   LOCATION is the location at which any error should be reported.  */

స్థిర పూర్ణాంకం
lvalue_or_else (location_t loc, const_వృక్షం ref, గణన lvalue_use use)
{
  పూర్ణాంకం win = lvalue_p (ref);

  ఒకవేళ (!win)
    lvalue_error (loc, use);

  తిరిగి win;
}

/* Mark EXP saying that we need to be able to take the
   address of it; it should not be allocated in a register.
   Returns true if successful.  ARRAY_REF_P is true if this
   is for ARRAY_REF construction - in that case we don't want
   to look through VIEW_CONVERT_EXPR from VECTOR_TYPE to ARRAY_TYPE,
   it is fine to use ARRAY_REFs for vector subscripts on vector
   register variables.  If OVERRIDE_REGISTER, clear DECL_REGISTER rather
   than producing an error for taking the address of a register.  */

తార్కిక
c_mark_addressable (వృక్షం ఘాతాంకం, తార్కిక array_ref_p, తార్కిక override_రిజిస్టరు)
{
  వృక్షం x = ఘాతాంకం;

  అయితే (1)
    ఎంపిక (వృక్షం_సంకేతం (x))
      {
      స్థితి VIEW_CONVERT_సమాసం:
	ఒకవేళ (array_ref_p
	    && వృక్షం_సంకేతం (వృక్షం_TYPE (x)) == ARRAY_TYPE
	    && సదిశ_TYPE_P (వృక్షం_TYPE (వృక్షం_నిర్వాహ్యం (x, 0))))
	  తిరిగి నిజం;
	x = వృక్షం_నిర్వాహ్యం (x, 0);
	ఆపు;

      స్థితి COMPONENT_REF:
	ఒకవేళ (DECL_C_బిట్టు_క్షేత్రం (వృక్షం_నిర్వాహ్యం (x, 1)))
	  {
	    error ("cannot take address of bit-field %qD",
		   వృక్షం_నిర్వాహ్యం (x, 1));
	    తిరిగి అబద్ధం;
	  }
	/* FALLTHRU */
      స్థితి ADDR_సమాసం:
      స్థితి ARRAY_REF:
      స్థితి REALPART_సమాసం:
      స్థితి IMAGPART_సమాసం:
	x = వృక్షం_నిర్వాహ్యం (x, 0);
	ఆపు;

      స్థితి COMPOUND_LITERAL_సమాసం:
	ఒకవేళ (C_DECL_రిజిస్టరు (COMPOUND_LITERAL_సమాసం_DECL (x)))
	  {
	    ఒకవేళ (override_రిజిస్టరు)
	      DECL_రిజిస్టరు (COMPOUND_LITERAL_సమాసం_DECL (x)) = 0;
	    లేకపోతే
	      {
		error ("address of register compound literal requested");
		తిరిగి అబద్ధం;
	      }
	  }
	వృక్షం_ADDRESSABLE (x) = 1;
	వృక్షం_ADDRESSABLE (COMPOUND_LITERAL_సమాసం_DECL (x)) = 1;
	తిరిగి నిజం;

      స్థితి CONSTRUCTOR:
	వృక్షం_ADDRESSABLE (x) = 1;
	తిరిగి నిజం;

      స్థితి VAR_DECL:
      స్థితి CONST_DECL:
      స్థితి PARM_DECL:
      స్థితి ఫలితం_DECL:
	ఒకవేళ (C_DECL_రిజిస్టరు (x)
	    && DECL_NONLOCAL (x))
	  {
	    ఒకవేళ (వృక్షం_ప్రజా (x) || is_global_var (x))
	      {
		error
		  ("global register variable %qD used in nested function", x);
		తిరిగి అబద్ధం;
	      }
	    pedwarn (ఆదానం_location, 0, "register variable %qD used in nested function", x);
	  }
	లేకపోతే ఒకవేళ (C_DECL_రిజిస్టరు (x))
	  {
	    ఒకవేళ (వృక్షం_ప్రజా (x) || is_global_var (x))
	      error ("address of global register variable %qD requested", x);
	    లేకపోతే ఒకవేళ (override_రిజిస్టరు && !DECL_HARD_రిజిస్టరు (x))
	      {
		DECL_రిజిస్టరు (x) = 0;
		వృక్షం_ADDRESSABLE (x) = 1;
		mark_decl_వాడిన (x, నిజం);
		తిరిగి నిజం;
	      }
	    లేకపోతే
	      error ("address of register variable %qD requested", x);
	    తిరిగి అబద్ధం;
	  }

	/* FALLTHRU */
      స్థితి FUNCTION_DECL:
	వృక్షం_ADDRESSABLE (x) = 1;
	mark_decl_వాడిన (x, నిజం);
	/* FALLTHRU */
      అప్రమేయ:
	తిరిగి నిజం;
    }
}

/* Convert EXPR to TYPE, warning about conversion problems with
   constants.  SEMANTIC_TYPE is the type this conversion would use
   without excess precision. If SEMANTIC_TYPE is NULL, this function
   is equivalent to convert_and_check. This function is a wrapper that
   handles conversions that may be different than
   the usual ones because of excess precision.  */

స్థిర వృక్షం
ep_convert_and_check (location_t loc, వృక్షం type, వృక్షం సమాసం,
		      వృక్షం semantic_type)
{
  ఒకవేళ (వృక్షం_TYPE (సమాసం) == type)
    తిరిగి సమాసం;

  /* For C11, integer conversions may have results with excess
     precision.  */
  ఒకవేళ (flag_isoc11 || !semantic_type)
    తిరిగి convert_and_check (loc, type, సమాసం);

  ఒకవేళ (వృక్షం_సంకేతం (వృక్షం_TYPE (సమాసం)) == INTEGER_TYPE
      && వృక్షం_TYPE (సమాసం) != semantic_type)
    {
      /* For integers, we need to check the real conversion, not
	 the conversion to the excess precision type.  */
      సమాసం = convert_and_check (loc, semantic_type, సమాసం);
    }
  /* Result type is the excess precision type, which should be
     large enough, so do not check.  */
  తిరిగి convert (type, సమాసం);
}

/* If EXPR refers to a built-in declared without a prototype returns
   the actual type of the built-in and, if non-null, set *BLTIN to
   a pointer to the built-in.  Otherwise return the type of EXPR
   and clear *BLTIN if non-null.  */

స్థిర వృక్షం
type_or_builtin_type (వృక్షం సమాసం, వృక్షం *bltin = ఖాళీ)
{
  వృక్షం dummy;
  ఒకవేళ (!bltin)
    bltin = &dummy;

  *bltin = NULL_వృక్షం;

  వృక్షం type = వృక్షం_TYPE (సమాసం);
  ఒకవేళ (వృక్షం_సంకేతం (సమాసం) != ADDR_సమాసం)
    తిరిగి type;

  వృక్షం oper = వృక్షం_నిర్వాహ్యం (సమాసం, 0);
  ఒకవేళ (!DECL_P (oper)
      || వృక్షం_సంకేతం (oper) != FUNCTION_DECL
      || !fndecl_built_లోపల_p (oper, BUILT_లోపల_సాధారణ))
    తిరిగి type;

  built_లోపల_function సంకేతం_2 = DECL_FUNCTION_సంకేతం (oper);
  ఒకవేళ (!C_DECL_BUILTIN_PROTOTYPE (oper))
    తిరిగి type;

  ఒకవేళ ((*bltin = builtin_decl_implicit (సంకేతం_2)))
    type = c_build_సూచిక_type (వృక్షం_TYPE (*bltin));

  తిరిగి type;
}

/* Build and return a conditional expression IFEXP ? OP1 : OP2.  If
   IFEXP_BCP then the condition is a call to __builtin_constant_p, and
   if folded to an integer constant then the unselected half may
   contain arbitrary operations not normally permitted in constant
   expressions.  Set the location of the expression to LOC.  */

వృక్షం
build_conditional_సమాసం (location_t colon_loc, వృక్షం ifexp, తార్కిక ifexp_bcp,
			వృక్షం op1, వృక్షం op1_original_type, location_t op1_loc,
			వృక్షం op2, వృక్షం op2_original_type, location_t op2_loc)
{
  వృక్షం type1;
  వృక్షం type2;
  వృక్షం ఫలితం_type = ఖాళీ;
  వృక్షం semantic_ఫలితం_type = ఖాళీ;
  వృక్షం orig_op1 = op1, orig_op2 = op2;
  తార్కిక int_const, op1_int_operands, op2_int_operands, int_operands;
  తార్కిక ifexp_int_operands;
  వృక్షం ret;

  op1_int_operands = సమాసం_INT_CONST_OPERANDS (orig_op1);
  ఒకవేళ (op1_int_operands)
    op1 = remove_c_maybe_const_సమాసం (op1);
  op2_int_operands = సమాసం_INT_CONST_OPERANDS (orig_op2);
  ఒకవేళ (op2_int_operands)
    op2 = remove_c_maybe_const_సమాసం (op2);
  ifexp_int_operands = సమాసం_INT_CONST_OPERANDS (ifexp);
  ఒకవేళ (ifexp_int_operands)
    ifexp = remove_c_maybe_const_సమాసం (ifexp);

  /* Promote both alternatives.  */

  ఒకవేళ (వృక్షం_సంకేతం (వృక్షం_TYPE (op1)) != VOID_TYPE)
    op1 = default_conversion (op1);
  ఒకవేళ (వృక్షం_సంకేతం (వృక్షం_TYPE (op2)) != VOID_TYPE)
    op2 = default_conversion (op2);

  ఒకవేళ (వృక్షం_సంకేతం (ifexp) == ERROR_MARK
      || వృక్షం_సంకేతం (వృక్షం_TYPE (op1)) == ERROR_MARK
      || వృక్షం_సంకేతం (వృక్షం_TYPE (op2)) == ERROR_MARK)
    తిరిగి error_mark_కణుపు;

  వృక్షం bltin1 = NULL_వృక్షం;
  వృక్షం bltin2 = NULL_వృక్షం;
  type1 = type_or_builtin_type (op1, &bltin1);
  స్థిరరాశి గణన వృక్షం_సంకేతం_2 code1 = వృక్షం_సంకేతం (type1);
  type2 = type_or_builtin_type (op2, &bltin2);
  స్థిరరాశి గణన వృక్షం_సంకేతం_2 code2 = వృక్షం_సంకేతం (type2);

  ఒకవేళ (code1 == సూచిక_TYPE && reject_gcc_builtin (op1))
    తిరిగి error_mark_కణుపు;

  ఒకవేళ (code2 == సూచిక_TYPE && reject_gcc_builtin (op2))
    తిరిగి error_mark_కణుపు;

  /* C90 does not permit non-lvalue arrays in conditional expressions.
     In C99 they will be pointers by now.  */
  ఒకవేళ (code1 == ARRAY_TYPE || code2 == ARRAY_TYPE)
    {
      error_at (colon_loc, "non-lvalue array in conditional expression");
      తిరిగి error_mark_కణుపు;
    }

  ఒకవేళ ((వృక్షం_సంకేతం (op1) == EXCESS_PRECISION_సమాసం
       || వృక్షం_సంకేతం (op2) == EXCESS_PRECISION_సమాసం)
      && (code1 == INTEGER_TYPE || code1 == REAL_TYPE
	  || code1 == COMPLEX_TYPE || code1 == BITINT_TYPE)
      && (code2 == INTEGER_TYPE || code2 == REAL_TYPE
	  || code2 == COMPLEX_TYPE || code2 == BITINT_TYPE))
    {
      semantic_ఫలితం_type = c_common_type (type1, type2);
      ఒకవేళ (వృక్షం_సంకేతం (op1) == EXCESS_PRECISION_సమాసం)
	{
	  op1 = వృక్షం_నిర్వాహ్యం (op1, 0);
	  type1 = వృక్షం_TYPE (op1);
	  gcc_assert (వృక్షం_సంకేతం (type1) == code1);
	}
      ఒకవేళ (వృక్షం_సంకేతం (op2) == EXCESS_PRECISION_సమాసం)
	{
	  op2 = వృక్షం_నిర్వాహ్యం (op2, 0);
	  type2 = వృక్షం_TYPE (op2);
	  gcc_assert (వృక్షం_సంకేతం (type2) == code2);
	}
    }

  ఒకవేళ (warn_cxx_compat)
    {
      వృక్షం t1 = op1_original_type ? op1_original_type : వృక్షం_TYPE (orig_op1);
      వృక్షం t2 = op2_original_type ? op2_original_type : వృక్షం_TYPE (orig_op2);

      ఒకవేళ (వృక్షం_సంకేతం (t1) == ENUMERAL_TYPE
	  && వృక్షం_సంకేతం (t2) == ENUMERAL_TYPE
	  && TYPE_MAIN_VARIANT (t1) != TYPE_MAIN_VARIANT (t2))
	warning_at (colon_loc, OPT_Wc___compat,
		    "different enum types in conditional is "
		    "invalid in C++: %qT vs %qT", t1, t2);
    }

  ఒకవేళ (warn_zero_as_null_సూచిక_constant
      && c_inhibit_evaluation_warnings == 0)
    {
      ఒకవేళ ((code1 == సూచిక_TYPE || code1 == NULLPTR_TYPE)
	  && INTEGRAL_TYPE_P (type2) && null_సూచిక_constant_p (orig_op2))
	warning_at (op2_loc, OPT_Wzero_as_null_సూచిక_constant,
		    "zero as null pointer constant");

      ఒకవేళ ((code2 == సూచిక_TYPE || code2 == NULLPTR_TYPE)
	  && INTEGRAL_TYPE_P (type1) && null_సూచిక_constant_p (orig_op1))
	warning_at (op1_loc, OPT_Wzero_as_null_సూచిక_constant,
		    "zero as null pointer constant");
    }

  /* Quickly detect the usual case where op1 and op2 have the same type
     after promotion.  */
  ఒకవేళ (TYPE_MAIN_VARIANT (type1) == TYPE_MAIN_VARIANT (type2))
    {
      ఒకవేళ (type1 == type2)
	ఫలితం_type = type1;
      లేకపోతే
	ఫలితం_type = TYPE_MAIN_VARIANT (type1);
    }
  లేకపోతే ఒకవేళ ((code1 == INTEGER_TYPE || code1 == REAL_TYPE
	    || code1 == COMPLEX_TYPE || code1 == BITINT_TYPE)
	   && (code2 == INTEGER_TYPE || code2 == REAL_TYPE
	       || code2 == COMPLEX_TYPE || code2 == BITINT_TYPE))
    {
      /* In C11, a conditional expression between a floating-point
	 type and an integer type should convert the integer type to
	 the evaluation format of the floating-point type, with
	 possible excess precision.  */
      వృక్షం eptype1 = type1;
      వృక్షం eptype2 = type2;
      ఒకవేళ (flag_isoc11)
	{
	  వృక్షం eptype;
	  ఒకవేళ (ANY_INTEGRAL_TYPE_P (type1)
	      && (eptype = excess_precision_type (type2)) != NULL_వృక్షం)
	    {
	      eptype2 = eptype;
	      ఒకవేళ (!semantic_ఫలితం_type)
		semantic_ఫలితం_type = c_common_type (type1, type2);
	    }
	  లేకపోతే ఒకవేళ (ANY_INTEGRAL_TYPE_P (type2)
		   && (eptype = excess_precision_type (type1)) != NULL_వృక్షం)
	    {
	      eptype1 = eptype;
	      ఒకవేళ (!semantic_ఫలితం_type)
		semantic_ఫలితం_type = c_common_type (type1, type2);
	    }
	}
      ఫలితం_type = c_common_type (eptype1, eptype2);
      ఒకవేళ (ఫలితం_type == error_mark_కణుపు)
	తిరిగి error_mark_కణుపు;
      do_warn_double_promotion (ఫలితం_type, type1, type2,
				"implicit conversion from %qT to %qT to "
				"match other result of conditional",
				colon_loc);

      /* If -Wsign-compare, warn here if type1 and type2 have
	 different signedness.  We'll promote the signed to unsigned
	 and later code won't know it used to be different.
	 Do this check on the original types, so that explicit casts
	 will be considered, but default promotions won't.  */
      ఒకవేళ (c_inhibit_evaluation_warnings == 0)
	{
	  పూర్ణాంకం unsigned_op1 = TYPE_UNSIGNED (వృక్షం_TYPE (orig_op1));
	  పూర్ణాంకం unsigned_op2 = TYPE_UNSIGNED (వృక్షం_TYPE (orig_op2));

	  ఒకవేళ (unsigned_op1 ^ unsigned_op2)
	    {
	      /* Do not warn if the result type is signed, since the
		 signed type will only be chosen if it can represent
		 all the values of the unsigned type.  */
	      ఒకవేళ (!TYPE_UNSIGNED (ఫలితం_type))
		/* OK */;
	      లేకపోతే
		{
		  తార్కిక op1_maybe_const = నిజం;
		  తార్కిక op2_maybe_const = నిజం;

		  /* Do not warn if the signed quantity is an
		     unsuffixed integer literal (or some static
		     constant expression involving such literals) and
		     it is non-negative.  This warning requires the
		     operands to be folded for best results, so do
		     that folding in this case even without
		     warn_sign_compare to avoid warning options
		     possibly affecting code generation.  */
		  c_inhibit_evaluation_warnings
		    += (ifexp == truthvalue_false_కణుపు);
		  op1 = c_fully_fold (op1, require_constant_విలువ,
				      &op1_maybe_const);
		  c_inhibit_evaluation_warnings
		    -= (ifexp == truthvalue_false_కణుపు);

		  c_inhibit_evaluation_warnings
		    += (ifexp == truthvalue_true_కణుపు);
		  op2 = c_fully_fold (op2, require_constant_విలువ,
				      &op2_maybe_const);
		  c_inhibit_evaluation_warnings
		    -= (ifexp == truthvalue_true_కణుపు);

		  ఒకవేళ (warn_sign_compare)
		    {
		      ఒకవేళ ((unsigned_op2
			   && వృక్షం_సమాసం_nonnegative_p (op1))
			  || (unsigned_op1
			      && వృక్షం_సమాసం_nonnegative_p (op2)))
			/* OK */;
		      లేకపోతే ఒకవేళ (unsigned_op2)
			warning_at (op1_loc, OPT_Wsign_compare,
				    "operand of %<?:%> changes signedness from "
				    "%qT to %qT due to unsignedness of other "
				    "operand", వృక్షం_TYPE (orig_op1),
				    వృక్షం_TYPE (orig_op2));
		      లేకపోతే
			warning_at (op2_loc, OPT_Wsign_compare,
				    "operand of %<?:%> changes signedness from "
				    "%qT to %qT due to unsignedness of other "
				    "operand", వృక్షం_TYPE (orig_op2),
				    వృక్షం_TYPE (orig_op1));
		    }
		  ఒకవేళ (!op1_maybe_const || వృక్షం_సంకేతం (op1) != INTEGER_CST)
		    op1 = c_wrap_maybe_const (op1, !op1_maybe_const);
		  ఒకవేళ (!op2_maybe_const || వృక్షం_సంకేతం (op2) != INTEGER_CST)
		    op2 = c_wrap_maybe_const (op2, !op2_maybe_const);
		}
	    }
	}
    }
  లేకపోతే ఒకవేళ (code1 == VOID_TYPE || code2 == VOID_TYPE)
    {
      ఒకవేళ (code1 != VOID_TYPE || code2 != VOID_TYPE)
	pedwarn (colon_loc, OPT_Wpedantic,
		 "ISO C forbids conditional expr with only one void side");
      ఫలితం_type = void_type_కణుపు;
    }
  లేకపోతే ఒకవేళ (code1 == సూచిక_TYPE && code2 == సూచిక_TYPE)
    {
      addr_space_t as1 = TYPE_ADDR_SPACE (వృక్షం_TYPE (type1));
      addr_space_t as2 = TYPE_ADDR_SPACE (వృక్షం_TYPE (type2));
      addr_space_t as_common;

      ఒకవేళ (comp_లక్ష్యం_types (colon_loc, type1, type2))
	{
	  ifexp = save_సమాసం (ifexp);
	  ఫలితం_type = common_సూచిక_type (type1, type2, ifexp);
	}
      లేకపోతే ఒకవేళ (null_సూచిక_constant_p (orig_op1))
	ఫలితం_type = type2;
      లేకపోతే ఒకవేళ (null_సూచిక_constant_p (orig_op2))
	ఫలితం_type = type1;
      లేకపోతే ఒకవేళ (!addr_space_superset (as1, as2, &as_common))
	{
	  error_at (colon_loc, "pointers to disjoint address spaces "
		    "used in conditional expression");
	  తిరిగి error_mark_కణుపు;
	}
      లేకపోతే ఒకవేళ ((VOID_TYPE_P (వృక్షం_TYPE (type1))
		&& !TYPE_ATOMIC (వృక్షం_TYPE (type1)))
	       || (VOID_TYPE_P (వృక్షం_TYPE (type2))
		   && !TYPE_ATOMIC (వృక్షం_TYPE (type2))))
	{
	  వృక్షం t1 = వృక్షం_TYPE (type1);
	  వృక్షం t2 = వృక్షం_TYPE (type2);
	  ఒకవేళ (!(VOID_TYPE_P (t1)
		&& !TYPE_ATOMIC (t1)))
	   {
	     /* roles are swapped */
	     t1 = t2;
	     t2 = వృక్షం_TYPE (type1);
	   }
	  వృక్షం t2_stripped = strip_array_types (t2);
	  ఒకవేళ ((వృక్షం_సంకేతం (t2) == ARRAY_TYPE)
	      && (TYPE_QUALS (t2_stripped) & ~TYPE_QUALS (t1)))
	    {
	      ఒకవేళ (!flag_isoc23)
		warning_at (colon_loc, OPT_Wdiscarded_array_qualifiers,
			    "pointer to array loses qualifier "
			    "in conditional expression");
	      లేకపోతే ఒకవేళ (warn_c11_c23_compat > 0)
		warning_at (colon_loc, OPT_Wc11_c23_compat,
			    "pointer to array loses qualifier "
			    "in conditional expression in ISO C before C23");
	    }
	  ఒకవేళ (వృక్షం_సంకేతం (t2) == FUNCTION_TYPE)
	    pedwarn (colon_loc, OPT_Wpedantic,
		     "ISO C forbids conditional expr between "
		     "%<void *%> and function pointer");
	  /* for array, use qualifiers of element type */
	  ఒకవేళ (flag_isoc23)
	    t2 = t2_stripped;
	  ఫలితం_type = c_build_సూచిక_type (qualify_type (t1, t2));
	}
      /* Objective-C pointer comparisons are a bit more lenient.  */
      లేకపోతే ఒకవేళ (objc_have_common_type (type1, type2, -3, NULL_వృక్షం))
	ఫలితం_type = objc_common_type (type1, type2);
      లేకపోతే
	{
	  పూర్ణాంకం qual = ENCODE_QUAL_ADDR_SPACE (as_common);
	  గణన diagnostics::రకం రకం = diagnostics::రకం::permerror;
	  ఒకవేళ (!flag_isoc99)
	    /* This downgrade to a warning ensures that -std=gnu89
	       -pedantic-errors does not flag these mismatches between
	       builtins as errors (as diagnostics::kind::permerror would)
	       ISO C99 and later do not have implicit function declarations,
	       so the mismatch cannot occur naturally there.  */
	    రకం = (bltin1 && bltin2
		    ? diagnostics::రకం::warning
		    : diagnostics::రకం::pedwarn);
	  ఒకవేళ (emit_diagnostic (రకం, colon_loc, OPT_Wincompatible_సూచిక_types,
			       "pointer type mismatch "
			       "in conditional expression"))
	    {
	      inform (op1_loc, "first expression has type %qT", type1);
	      inform (op2_loc, "second expression has type %qT", type2);
	    }
	  ఫలితం_type = c_build_సూచిక_type
			  (c_build_qualified_type (void_type_కణుపు, qual));
	}
    }
  లేకపోతే ఒకవేళ (code1 == సూచిక_TYPE
	   && (code2 == INTEGER_TYPE || code2 == BITINT_TYPE))
    {
      ఒకవేళ (!null_సూచిక_constant_p (orig_op2))
	permerror_opt (colon_loc, OPT_Wint_conversion,
		       "pointer/integer type mismatch "
		       "in conditional expression");
      లేకపోతే
	{
	  op2 = null_సూచిక_కణుపు;
	}
      ఫలితం_type = type1;
    }
  లేకపోతే ఒకవేళ (code2 == సూచిక_TYPE
	   && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
    {
      ఒకవేళ (!null_సూచిక_constant_p (orig_op1))
	permerror_opt (colon_loc, OPT_Wint_conversion,
		       "pointer/integer type mismatch "
		       "in conditional expression");
      లేకపోతే
	{
	  op1 = null_సూచిక_కణుపు;
	}
      ఫలితం_type = type2;
    }
  /* 6.5.15: "if one is a null pointer constant (other than a pointer) or has
     type nullptr_t and the other is a pointer, the result type is the pointer
     type."  */
  లేకపోతే ఒకవేళ (code1 == NULLPTR_TYPE && code2 == సూచిక_TYPE)
    ఫలితం_type = type2;
  లేకపోతే ఒకవేళ (code1 == సూచిక_TYPE && code2 == NULLPTR_TYPE)
    ఫలితం_type = type1;
  లేకపోతే ఒకవేళ (రికార్డు_OR_UNION_TYPE_P (type1) && రికార్డు_OR_UNION_TYPE_P (type2)
	   && comptypes (TYPE_MAIN_VARIANT (type1),
			 TYPE_MAIN_VARIANT (type2)))
    ఫలితం_type = సంయుక్త_type (TYPE_MAIN_VARIANT (type1),
				  TYPE_MAIN_VARIANT (type2));

  ఒకవేళ (!ఫలితం_type)
    {
      ఒకవేళ (flag_cond_mismatch)
	ఫలితం_type = void_type_కణుపు;
      లేకపోతే
	{
	  error_at (colon_loc, "type mismatch in conditional expression");
	  తిరిగి error_mark_కణుపు;
	}
    }

  /* Merge const and volatile flags of the incoming types.  */
  ఫలితం_type
    = build_type_variant (ఫలితం_type,
			  TYPE_READONLY (type1) || TYPE_READONLY (type2),
			  TYPE_VOLATILE (type1) || TYPE_VOLATILE (type2));

  op1 = ep_convert_and_check (colon_loc, ఫలితం_type, op1,
			      semantic_ఫలితం_type);
  op2 = ep_convert_and_check (colon_loc, ఫలితం_type, op2,
			      semantic_ఫలితం_type);

  ఒకవేళ (ifexp_bcp && ifexp == truthvalue_true_కణుపు)
    {
      op2_int_operands = నిజం;
      op1 = c_fully_fold (op1, require_constant_విలువ, ఖాళీ);
    }
  ఒకవేళ (ifexp_bcp && ifexp == truthvalue_false_కణుపు)
    {
      op1_int_operands = నిజం;
      op2 = c_fully_fold (op2, require_constant_విలువ, ఖాళీ);
    }
  int_const = int_operands = (ifexp_int_operands
			      && op1_int_operands
			      && op2_int_operands);
  ఒకవేళ (int_operands)
    {
      int_const = ((ifexp == truthvalue_true_కణుపు
		    && వృక్షం_సంకేతం (orig_op1) == INTEGER_CST
		    && !వృక్షం_అధికప్రవాహం (orig_op1))
		   || (ifexp == truthvalue_false_కణుపు
		       && వృక్షం_సంకేతం (orig_op2) == INTEGER_CST
		       && !వృక్షం_అధికప్రవాహం (orig_op2)));
    }

  /* Need to convert condition operand into a vector mask.  */
  ఒకవేళ (సదిశ_TYPE_P (వృక్షం_TYPE (ifexp)))
    {
      వృక్షం vectype = వృక్షం_TYPE (ifexp);
      వృక్షం elem_type = వృక్షం_TYPE (vectype);
      వృక్షం zero = build_int_cst (elem_type, 0);
      వృక్షం zero_vec = build_సదిశ_from_val (vectype, zero);
      వృక్షం cmp_type = truth_type_for (vectype);
      ifexp = build2 (NE_సమాసం, cmp_type, ifexp, zero_vec);
    }

  ఒకవేళ (int_const || (ifexp_bcp && వృక్షం_సంకేతం (ifexp) == INTEGER_CST))
    ret = fold_build3_loc (colon_loc, COND_సమాసం, ఫలితం_type, ifexp, op1, op2);
  లేకపోతే
    {
      ఒకవేళ (int_operands)
	{
	  /* Use c_fully_fold here, since C_MAYBE_CONST_EXPR might be
	     nested inside of the expression.  */
	  op1 = c_fully_fold (op1, అబద్ధం, ఖాళీ);
	  op2 = c_fully_fold (op2, అబద్ధం, ఖాళీ);
	}
      ret = build3 (COND_సమాసం, ఫలితం_type, ifexp, op1, op2);
      ఒకవేళ (int_operands)
	ret = note_integer_operands (ret);
    }
  ఒకవేళ (semantic_ఫలితం_type)
    ret = build1 (EXCESS_PRECISION_సమాసం, semantic_ఫలితం_type, ret);

  protected_సమితి_సమాసం_location (ret, colon_loc);

  /* If the OP1 and OP2 are the same and don't have side-effects,
     warn here, because the COND_EXPR will be turned into OP1.  */
  ఒకవేళ (warn_duplicated_branches
      && వృక్షం_సంకేతం (ret) == COND_సమాసం
      && (op1 == op2 || నిర్వాహ్యం_equal_p (op1, op2, OEP_చిరునామా_యొక్క_SAME_క్షేత్రం)))
    warning_at (సమాసం_LOCATION (ret), OPT_Wduplicated_branches,
		"this condition has identical branches");

  తిరిగి ret;
}

/* EXPR is an expression, location LOC, whose result is discarded.
   Warn if it is a call to a nodiscard function (or a COMPOUND_EXPR
   whose right-hand operand is such a call, possibly recursively).  */

స్థిర శూన్య
maybe_warn_nodiscard (location_t loc, వృక్షం సమాసం)
{
  ఒకవేళ (VOID_TYPE_P (వృక్షం_TYPE (సమాసం)))
    తిరిగి;
  అయితే (వృక్షం_సంకేతం (సమాసం) == COMPOUND_సమాసం)
    {
      సమాసం = వృక్షం_నిర్వాహ్యం (సమాసం, 1);
      ఒకవేళ (సమాసం_HAS_LOCATION (సమాసం))
	loc = సమాసం_LOCATION (సమాసం);
    }
  ఒకవేళ (వృక్షం_సంకేతం (సమాసం) != CALL_సమాసం)
    తిరిగి;
  వృక్షం fn = CALL_సమాసం_FN (సమాసం);
  ఒకవేళ (!fn)
    తిరిగి;
  వృక్షం attr;
  ఒకవేళ (వృక్షం_సంకేతం (fn) == ADDR_సమాసం
      && వృక్షం_సంకేతం (వృక్షం_నిర్వాహ్యం (fn, 0)) == FUNCTION_DECL
      && (attr = lookup_attribute ("nodiscard",
				   DECL_లక్షణాలు (వృక్షం_నిర్వాహ్యం (fn, 0)))))
    {
      fn = వృక్షం_నిర్వాహ్యం (fn, 0);
      వృక్షం వాదనలు = వృక్షం_విలువ (attr);
      ఒకవేళ (వాదనలు)
	వాదనలు = వృక్షం_విలువ (వాదనలు);
      auto_diagnostic_సమూహం d;
      auto_urlify_లక్షణాలు sentinel;
      పూర్ణాంకం warned;
      ఒకవేళ (వాదనలు)
	warned = warning_at (loc, OPT_Wunused_ఫలితం,
			     "ignoring return value of %qD, declared with "
			     "attribute %<nodiscard%>: %E", fn, వాదనలు);
      లేకపోతే
	warned = warning_at (loc, OPT_Wunused_ఫలితం,
			     "ignoring return value of %qD, declared with "
			     "attribute %<nodiscard%>", fn);
      ఒకవేళ (warned)
	inform (DECL_ఆధారం_LOCATION (fn), "declared here");
    }
  లేకపోతే
    {
      వృక్షం rettype = వృక్షం_TYPE (వృక్షం_TYPE (వృక్షం_TYPE (fn)));
      attr = lookup_attribute ("nodiscard", TYPE_లక్షణాలు (rettype));
      ఒకవేళ (!attr)
	తిరిగి;
      వృక్షం వాదనలు = వృక్షం_విలువ (attr);
      ఒకవేళ (వాదనలు)
	వాదనలు = వృక్షం_విలువ (వాదనలు);
      auto_diagnostic_సమూహం d;
      auto_urlify_లక్షణాలు sentinel;
      పూర్ణాంకం warned;
      ఒకవేళ (వాదనలు)
	warned = warning_at (loc, OPT_Wunused_ఫలితం,
			     "ignoring return value of type %qT, declared "
			     "with attribute %<nodiscard%>: %E",
			     rettype, వాదనలు);
      లేకపోతే
	warned = warning_at (loc, OPT_Wunused_ఫలితం,
			     "ignoring return value of type %qT, declared "
			     "with attribute %<nodiscard%>", rettype);
      ఒకవేళ (warned)
	{
	  ఒకవేళ (వృక్షం_సంకేతం (fn) == ADDR_సమాసం)
	    {
	      fn = వృక్షం_నిర్వాహ్యం (fn, 0);
	      ఒకవేళ (వృక్షం_సంకేతం (fn) == FUNCTION_DECL)
		inform (DECL_ఆధారం_LOCATION (fn),
			"in call to %qD, declared here", fn);
	    }
	}
    }
}

/* Return a compound expression that performs two expressions and
   returns the value of the second of them.

   LOC is the location of the COMPOUND_EXPR.  */

వృక్షం
build_compound_సమాసం (location_t loc, వృక్షం expr1, వృక్షం expr2)
{
  తార్కిక expr1_int_operands, expr2_int_operands;
  వృక్షం eptype = NULL_వృక్షం;
  వృక్షం ret;

  expr1_int_operands = సమాసం_INT_CONST_OPERANDS (expr1);
  ఒకవేళ (expr1_int_operands)
    expr1 = remove_c_maybe_const_సమాసం (expr1);
  expr2_int_operands = సమాసం_INT_CONST_OPERANDS (expr2);
  ఒకవేళ (expr2_int_operands)
    expr2 = remove_c_maybe_const_సమాసం (expr2);

  ఒకవేళ (వృక్షం_సంకేతం (expr1) == EXCESS_PRECISION_సమాసం)
    expr1 = వృక్షం_నిర్వాహ్యం (expr1, 0);
  ఒకవేళ (వృక్షం_సంకేతం (expr2) == EXCESS_PRECISION_సమాసం)
    {
      eptype = వృక్షం_TYPE (expr2);
      expr2 = వృక్షం_నిర్వాహ్యం (expr2, 0);
    }

  ఒకవేళ (!వృక్షం_SIDE_EFFECTS (expr1))
    {
      /* The left-hand operand of a comma expression is like an expression
	 statement: with -Wunused, we should warn if it doesn't have
	 any side-effects, unless it was explicitly cast to (void).  */
      ఒకవేళ (warn_వాడని_విలువ)
	{
	  ఒకవేళ (VOID_TYPE_P (వృక్షం_TYPE (expr1))
	      && CONVERT_సమాసం_P (expr1))
	    ; /* (void) a, b */
	  లేకపోతే ఒకవేళ (VOID_TYPE_P (వృక్షం_TYPE (expr1))
		   && వృక్షం_సంకేతం (expr1) == COMPOUND_సమాసం
		   && CONVERT_సమాసం_P (వృక్షం_నిర్వాహ్యం (expr1, 1)))
	    ; /* (void) a, (void) b, c */
	  లేకపోతే
	    warning_at (loc, OPT_Wunused_విలువ,
			"left-hand operand of comma expression has no effect");
	}
    }
  లేకపోతే ఒకవేళ (వృక్షం_సంకేతం (expr1) == COMPOUND_సమాసం
	   && warn_వాడని_విలువ)
    {
      వృక్షం r = expr1;
      location_t cloc = loc;
      అయితే (వృక్షం_సంకేతం (r) == COMPOUND_సమాసం)
        {
	  ఒకవేళ (సమాసం_HAS_LOCATION (r))
	    cloc = సమాసం_LOCATION (r);
	  r = వృక్షం_నిర్వాహ్యం (r, 1);
	}
      ఒకవేళ (!వృక్షం_SIDE_EFFECTS (r)
	  && !VOID_TYPE_P (వృక్షం_TYPE (r))
	  && !CONVERT_సమాసం_P (r))
	warning_at (cloc, OPT_Wunused_విలువ,
	            "right-hand operand of comma expression has no effect");
    }

  /* With -Wunused, we should also warn if the left-hand operand does have
     side-effects, but computes a value which is not used.  For example, in
     `foo() + bar(), baz()' the result of the `+' operator is not used,
     so we should issue a warning.  */
  లేకపోతే ఒకవేళ (warn_వాడని_విలువ)
    warn_if_వాడని_విలువ (expr1, loc);

  maybe_warn_nodiscard (loc, expr1);

  ఒకవేళ (expr2 == error_mark_కణుపు)
    తిరిగి error_mark_కణుపు;

  ret = build2 (COMPOUND_సమాసం, వృక్షం_TYPE (expr2), expr1, expr2);

  ఒకవేళ (flag_isoc99
      && expr1_int_operands
      && expr2_int_operands)
    ret = note_integer_operands (ret);

  ఒకవేళ (eptype)
    ret = build1 (EXCESS_PRECISION_సమాసం, eptype, ret);

  protected_సమితి_సమాసం_location (ret, loc);
  తిరిగి ret;
}

/* Issue -Wcast-qual warnings when appropriate.  TYPE is the type to
   which we are casting.  OTYPE is the type of the expression being
   cast.  Both TYPE and OTYPE are pointer types.  LOC is the location
   of the cast.  -Wcast-qual appeared on the command line.  Named
   address space qualifiers are not handled here, because they result
   in different warnings.  */

స్థిర శూన్య
handle_warn_cast_qual (location_t loc, వృక్షం type, వృక్షం otype)
{
  వృక్షం లోపల_type = type;
  వృక్షం లోపల_otype = otype;
  పూర్ణాంకం added = 0;
  పూర్ణాంకం discarded = 0;
  తార్కిక is_const;

  /* Check that the qualifiers on IN_TYPE are a superset of the
     qualifiers of IN_OTYPE.  The outermost level of POINTER_TYPE
     nodes is uninteresting and we stop as soon as we hit a
     non-POINTER_TYPE node on either type.  */
  చేయి
    {
      లోపల_otype = వృక్షం_TYPE (లోపల_otype);
      లోపల_type = వృక్షం_TYPE (లోపల_type);

      /* GNU C allows cv-qualified function types.  'const' means the
	 function is very pure, 'volatile' means it can't return.  We
	 need to warn when such qualifiers are added, not when they're
	 taken away.  */
      ఒకవేళ (వృక్షం_సంకేతం (లోపల_otype) == FUNCTION_TYPE
	  && వృక్షం_సంకేతం (లోపల_type) == FUNCTION_TYPE)
	added |= (TYPE_QUALS_NO_ADDR_SPACE (లోపల_type)
		  & ~TYPE_QUALS_NO_ADDR_SPACE (లోపల_otype));
      లేకపోతే
	discarded |= (TYPE_QUALS_NO_ADDR_SPACE (లోపల_otype)
		      & ~TYPE_QUALS_NO_ADDR_SPACE (లోపల_type));
    }
  అయితే (వృక్షం_సంకేతం (లోపల_type) == సూచిక_TYPE
	 && వృక్షం_సంకేతం (లోపల_otype) == సూచిక_TYPE);

  ఒకవేళ (added)
    warning_at (loc, OPT_Wcast_qual,
		"cast adds %q#v qualifier to function type", added);

  ఒకవేళ (discarded)
    /* There are qualifiers present in IN_OTYPE that are not present
       in IN_TYPE.  */
    warning_at (loc, OPT_Wcast_qual,
		"cast discards %qv qualifier from pointer target type",
		discarded);

  ఒకవేళ (added || discarded)
    తిరిగి;

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

  ఒకవేళ (TYPE_MAIN_VARIANT (లోపల_type) != TYPE_MAIN_VARIANT (లోపల_otype))
    తిరిగి;
  ఒకవేళ (వృక్షం_సంకేతం (వృక్షం_TYPE (type)) != సూచిక_TYPE)
    తిరిగి;

  లోపల_type = type;
  లోపల_otype = otype;
  is_const = TYPE_READONLY (వృక్షం_TYPE (లోపల_type));
  చేయి
    {
      లోపల_type = వృక్షం_TYPE (లోపల_type);
      లోపల_otype = వృక్షం_TYPE (లోపల_otype);
      ఒకవేళ ((TYPE_QUALS (లోపల_type) &~ TYPE_QUALS (లోపల_otype)) != 0
	  && !is_const)
	{
	  warning_at (loc, OPT_Wcast_qual,
		      "to be safe all intermediate pointers in cast from "
                      "%qT to %qT must be %<const%> qualified",
		      otype, type);
	  ఆపు;
	}
      ఒకవేళ (is_const)
	is_const = TYPE_READONLY (లోపల_type);
    }
  అయితే (వృక్షం_సంకేతం (లోపల_type) == సూచిక_TYPE);
}

/* Heuristic check if two parameter types can be considered ABI-equivalent.  */

స్థిర తార్కిక
c_సురక్షిత_arg_type_equiv_p (వృక్షం t1, వృక్షం t2)
{
  ఒకవేళ (error_నిర్వాహ్యం_p (t1) || error_నిర్వాహ్యం_p (t2))
    తిరిగి నిజం;

  t1 = TYPE_MAIN_VARIANT (t1);
  t2 = TYPE_MAIN_VARIANT (t2);

  ఒకవేళ (వృక్షం_సంకేతం (t1) == సూచిక_TYPE
      && వృక్షం_సంకేతం (t2) == సూచిక_TYPE)
    తిరిగి నిజం;

  /* Only the precision of the parameter matters.  This check should
     make sure that the callee does not see undefined values in argument
     registers.  */
  ఒకవేళ (INTEGRAL_TYPE_P (t1)
      && INTEGRAL_TYPE_P (t2)
      && TYPE_PRECISION (t1) == TYPE_PRECISION (t2))
    తిరిగి నిజం;

  తిరిగి comptypes (t1, t2);
}

/* Check if a type cast between two function types can be considered safe.  */

స్థిర తార్కిక
c_సురక్షిత_function_type_cast_p (వృక్షం t1, వృక్షం t2)
{
  ఒకవేళ (వృక్షం_TYPE (t1) == void_type_కణుపు &&
      TYPE_ARG_TYPES (t1) == void_list_కణుపు)
    తిరిగి నిజం;

  ఒకవేళ (వృక్షం_TYPE (t2) == void_type_కణుపు &&
      TYPE_ARG_TYPES (t2) == void_list_కణుపు)
    తిరిగి నిజం;

  ఒకవేళ (!c_సురక్షిత_arg_type_equiv_p (వృక్షం_TYPE (t1), వృక్షం_TYPE (t2)))
    తిరిగి అబద్ధం;

  కొరకు (t1 = TYPE_ARG_TYPES (t1), t2 = TYPE_ARG_TYPES (t2);
       t1 && t2;
       t1 = వృక్షం_CHAIN (t1), t2 = వృక్షం_CHAIN (t2))
    ఒకవేళ (!c_సురక్షిత_arg_type_equiv_p (వృక్షం_విలువ (t1), వృక్షం_విలువ (t2)))
      తిరిగి అబద్ధం;

  తిరిగి నిజం;
}

/* Build an expression representing a cast to type TYPE of expression EXPR.
   LOC is the location of the cast-- typically the open paren of the cast.  */

వృక్షం
build_c_cast (location_t loc, వృక్షం type, వృక్షం సమాసం)
{
  వృక్షం విలువ;

  తార్కిక int_operands = సమాసం_INT_CONST_OPERANDS (సమాసం);

  ఒకవేళ (వృక్షం_సంకేతం (సమాసం) == EXCESS_PRECISION_సమాసం)
    సమాసం = వృక్షం_నిర్వాహ్యం (సమాసం, 0);

  విలువ = సమాసం;
  ఒకవేళ (int_operands)
    విలువ = remove_c_maybe_const_సమాసం (విలువ);

  ఒకవేళ (type == error_mark_కణుపు || సమాసం == error_mark_కణుపు)
    తిరిగి error_mark_కణుపు;

  /* The ObjC front-end uses TYPE_MAIN_VARIANT to tie together types differing
     only in <protocol> qualifications.  But when constructing cast expressions,
     the protocols do matter and must be kept around.  */
  ఒకవేళ (objc_is_object_ptr (type) && objc_is_object_ptr (వృక్షం_TYPE (సమాసం)))
    తిరిగి build1 (NOP_సమాసం, type, సమాసం);

  type = TYPE_MAIN_VARIANT (type);

  ఒకవేళ (వృక్షం_సంకేతం (type) == ARRAY_TYPE)
    {
      error_at (loc, "cast specifies array type");
      తిరిగి error_mark_కణుపు;
    }

  ఒకవేళ (వృక్షం_సంకేతం (type) == FUNCTION_TYPE)
    {
      error_at (loc, "cast specifies function type");
      తిరిగి error_mark_కణుపు;
    }

  ఒకవేళ (!VOID_TYPE_P (type))
    {
      విలువ = require_complete_type (loc, విలువ);
      ఒకవేళ (విలువ == error_mark_కణుపు)
	తిరిగి error_mark_కణుపు;
    }

  ఒకవేళ (type == TYPE_MAIN_VARIANT (వృక్షం_TYPE (విలువ)))
    {
      ఒకవేళ (రికార్డు_OR_UNION_TYPE_P (type)
	  && pedwarn (loc, OPT_Wpedantic,
		      "ISO C forbids casting nonscalar to the same type"))
	      ;
      లేకపోతే ఒకవేళ (warn_useless_cast && c_inhibit_evaluation_warnings == 0)
	warning_at (loc, OPT_Wuseless_cast,
		    "useless cast to type %qT", type);

      /* Convert to remove any qualifiers from VALUE's type.  */
      విలువ = convert (type, విలువ);
    }
  లేకపోతే ఒకవేళ (వృక్షం_సంకేతం (type) == UNION_TYPE)
    {
      వృక్షం క్షేత్రం_2;

      కొరకు (క్షేత్రం_2 = TYPE_FIELDS (type); క్షేత్రం_2; క్షేత్రం_2 = DECL_CHAIN (క్షేత్రం_2))
	ఒకవేళ (వృక్షం_TYPE (క్షేత్రం_2) != error_mark_కణుపు
	    && comptypes (TYPE_MAIN_VARIANT (వృక్షం_TYPE (క్షేత్రం_2)),
			  TYPE_MAIN_VARIANT (వృక్షం_TYPE (విలువ))))
	  ఆపు;

      ఒకవేళ (క్షేత్రం_2)
	{
	  వృక్షం t;
	  తార్కిక maybe_const = నిజం;

	  pedwarn (loc, OPT_Wpedantic, "ISO C forbids casts to union type");
	  t = c_fully_fold (విలువ, అబద్ధం, &maybe_const);
	  t = build_constructor_single (type, క్షేత్రం_2, t);
	  ఒకవేళ (!maybe_const)
	    t = c_wrap_maybe_const (t, నిజం);
	  t = digest_init (loc, క్షేత్రం_2, type, t,
			   NULL_వృక్షం, అబద్ధం, అబద్ధం, అబద్ధం, నిజం, అబద్ధం, అబద్ధం);
	  వృక్షం_CONSTANT (t) = వృక్షం_CONSTANT (విలువ);
	  తిరిగి t;
	}
      error_at (loc, "cast to union type from type not present in union");
      తిరిగి error_mark_కణుపు;
    }
  లేకపోతే
    {
      వృక్షం otype, ovalue;

      ఒకవేళ (type == void_type_కణుపు)
	{
	  వృక్షం t = build1 (CONVERT_సమాసం, type, విలువ);
	  సమితి_సమాసం_LOCATION (t, loc);
	  తిరిగి t;
	}

      otype = వృక్షం_TYPE (విలువ);

      /* Optionally warn about potentially worrisome casts.  */
      ఒకవేళ (warn_cast_qual
	  && వృక్షం_సంకేతం (type) == సూచిక_TYPE
	  && వృక్షం_సంకేతం (otype) == సూచిక_TYPE)
	handle_warn_cast_qual (loc, type, otype);

      /* Warn about conversions between pointers to disjoint
	 address spaces.  */
      ఒకవేళ (వృక్షం_సంకేతం (type) == సూచిక_TYPE
	  && వృక్షం_సంకేతం (otype) == సూచిక_TYPE
	  && !null_సూచిక_constant_p (విలువ))
	{
	  addr_space_t as_గమ్యం = TYPE_ADDR_SPACE (వృక్షం_TYPE (type));
	  addr_space_t as_from = TYPE_ADDR_SPACE (వృక్షం_TYPE (otype));
	  addr_space_t as_common;

	  ఒకవేళ (!addr_space_superset (as_గమ్యం, as_from, &as_common))
	    {
	      ఒకవేళ (ADDR_SPACE_GENERIC_P (as_from))
		warning_at (loc, 0, "cast to %qs address space pointer "
			    "from disjoint generic address space pointer",
			    c_addr_space_name (as_గమ్యం));

	      లేకపోతే ఒకవేళ (ADDR_SPACE_GENERIC_P (as_గమ్యం))
		warning_at (loc, 0, "cast to generic address space pointer "
			    "from disjoint %qs address space pointer",
			    c_addr_space_name (as_from));

	      లేకపోతే
		warning_at (loc, 0, "cast to %qs address space pointer "
			    "from disjoint %qs address space pointer",
			    c_addr_space_name (as_గమ్యం),
			    c_addr_space_name (as_from));
	    }

	  /* Warn of new allocations that are not big enough for the target
	     type.  */
	  ఒకవేళ (warn_alloc_కొలత && వృక్షం_సంకేతం (విలువ) == CALL_సమాసం)
	    ఒకవేళ (వృక్షం fndecl = get_callee_fndecl (విలువ))
	      ఒకవేళ (DECL_IS_MALLOC (fndecl))
		{
		  వృక్షం attrs = TYPE_లక్షణాలు (వృక్షం_TYPE (fndecl));
		  వృక్షం alloc_కొలత = lookup_attribute ("alloc_size", attrs);
		  ఒకవేళ (alloc_కొలత)
		    warn_for_alloc_కొలత (loc, వృక్షం_TYPE (type), విలువ,
					 alloc_కొలత);
		}
	}

      /* Warn about possible alignment problems.  */
      ఒకవేళ ((STRICT_ALIGNMENT || warn_cast_align == 2)
	  && వృక్షం_సంకేతం (type) == సూచిక_TYPE
	  && వృక్షం_సంకేతం (otype) == సూచిక_TYPE
	  && వృక్షం_సంకేతం (వృక్షం_TYPE (otype)) != VOID_TYPE
	  && వృక్షం_సంకేతం (వృక్షం_TYPE (otype)) != FUNCTION_TYPE
	  /* Don't warn about opaque types, where the actual alignment
	     restriction is unknown.  */
	  && !(రికార్డు_OR_UNION_TYPE_P (వృక్షం_TYPE (otype))
	       && TYPE_బహుళకం (వృక్షం_TYPE (otype)) == VOIDmode)
	  && min_align_యొక్క_type (వృక్షం_TYPE (type))
	     > min_align_యొక్క_type (వృక్షం_TYPE (otype)))
	warning_at (loc, OPT_Wcast_align,
		    "cast increases required alignment of target type");

      ఒకవేళ ((వృక్షం_సంకేతం (type) == INTEGER_TYPE
	   || వృక్షం_సంకేతం (type) == BITINT_TYPE)
	  && వృక్షం_సంకేతం (otype) == సూచిక_TYPE
	  && TYPE_PRECISION (type) != TYPE_PRECISION (otype))
      /* Unlike conversion of integers to pointers, where the
         warning is disabled for converting constants because
         of cases such as SIG_*, warn about converting constant
         pointers to integers. In some cases it may cause unwanted
         sign extension, and a warning is appropriate.  */
	warning_at (loc, OPT_Wpointer_గమ్యం_int_cast,
		    "cast from pointer to integer of different size");

      ఒకవేళ ((వృక్షం_సంకేతం (విలువ) == CALL_సమాసం
	   && !is_access_with_కొలత_p (విలువ))
	  && వృక్షం_సంకేతం (type) != వృక్షం_సంకేతం (otype))
	warning_at (loc, OPT_Wbad_function_cast,
		    "cast from function call of type %qT "
		    "to non-matching type %qT", otype, type);

      ఒకవేళ (వృక్షం_సంకేతం (type) == సూచిక_TYPE
	  && (వృక్షం_సంకేతం (otype) == INTEGER_TYPE
	      || వృక్షం_సంకేతం (otype) == BITINT_TYPE)
	  && TYPE_PRECISION (type) != TYPE_PRECISION (otype)
	  /* Don't warn about converting any constant.  */
	  && !వృక్షం_CONSTANT (విలువ))
	warning_at (loc,
		    OPT_Wint_గమ్యం_సూచిక_cast, "cast to pointer from integer "
		    "of different size");

      ఒకవేళ (warn_strict_aliasing <= 2)
        strict_aliasing_warning (సమాసం_LOCATION (విలువ), type, సమాసం);

      /* If pedantic, warn for conversions between function and object
	 pointer types, except for converting a null pointer constant
	 to function pointer type.  */
      ఒకవేళ (pedantic
	  && వృక్షం_సంకేతం (type) == సూచిక_TYPE
	  && వృక్షం_సంకేతం (otype) == సూచిక_TYPE
	  && వృక్షం_సంకేతం (వృక్షం_TYPE (otype)) == FUNCTION_TYPE
	  && వృక్షం_సంకేతం (వృక్షం_TYPE (type)) != FUNCTION_TYPE)
	pedwarn (loc, OPT_Wpedantic, "ISO C forbids "
		 "conversion of function pointer to object pointer type");

      ఒకవేళ (pedantic
	  && వృక్షం_సంకేతం (type) == సూచిక_TYPE
	  && వృక్షం_సంకేతం (otype) == సూచిక_TYPE
	  && వృక్షం_సంకేతం (వృక్షం_TYPE (type)) == FUNCTION_TYPE
	  && వృక్షం_సంకేతం (వృక్షం_TYPE (otype)) != FUNCTION_TYPE
	  && !null_సూచిక_constant_p (విలువ))
	pedwarn (loc, OPT_Wpedantic, "ISO C forbids "
		 "conversion of object pointer to function pointer type");

      ఒకవేళ (వృక్షం_సంకేతం (type) == సూచిక_TYPE
	  && వృక్షం_సంకేతం (otype) == సూచిక_TYPE
	  && వృక్షం_సంకేతం (వృక్షం_TYPE (type)) == FUNCTION_TYPE
	  && వృక్షం_సంకేతం (వృక్షం_TYPE (otype)) == FUNCTION_TYPE
	  && !c_సురక్షిత_function_type_cast_p (వృక్షం_TYPE (type),
					   వృక్షం_TYPE (otype)))
	warning_at (loc, OPT_Wcast_function_type,
		    "cast between incompatible function types"
		    " from %qT to %qT", otype, type);

      ovalue = విలువ;
      /* If converting to boolean a value with integer operands that
	 is not itself represented as an INTEGER_CST, the call below
	 to note_integer_operands may insert a C_MAYBE_CONST_EXPR, but
	 build_binary_op as called by c_common_truthvalue_conversion
	 may also insert a C_MAYBE_CONST_EXPR to indicate that a
	 subexpression has been fully folded.  To avoid nested
	 C_MAYBE_CONST_EXPR, ensure that
	 c_objc_common_truthvalue_conversion receives an argument
	 properly marked as having integer operands in that case.  */
      ఒకవేళ (int_operands
	  && వృక్షం_సంకేతం (విలువ) != INTEGER_CST
	  && (వృక్షం_సంకేతం (type) == BOOLEAN_TYPE
	      || (వృక్షం_సంకేతం (type) == ENUMERAL_TYPE
		  && ENUM_UNDERLYING_TYPE (type) != NULL_వృక్షం
		  && వృక్షం_సంకేతం (ENUM_UNDERLYING_TYPE (type)) == BOOLEAN_TYPE)))
	విలువ = note_integer_operands (విలువ);
      విలువ = convert (type, విలువ);

      /* Ignore any integer overflow caused by the cast.  */
      ఒకవేళ (వృక్షం_సంకేతం (విలువ) == INTEGER_CST && !FLOAT_TYPE_P (otype))
	{
	  ఒకవేళ (వృక్షం_అధికప్రవాహం_P (ovalue))
	    {
	      ఒకవేళ (!వృక్షం_అధికప్రవాహం (విలువ))
		{
		  /* Avoid clobbering a shared constant.  */
		  విలువ = copy_కణుపు (విలువ);
		  వృక్షం_అధికప్రవాహం (విలువ) = వృక్షం_అధికప్రవాహం (ovalue);
		}
	    }
	  లేకపోతే ఒకవేళ (వృక్షం_అధికప్రవాహం (విలువ))
	    /* Reset VALUE's overflow flags, ensuring constant sharing.  */
	    విలువ = wide_int_గమ్యం_వృక్షం (వృక్షం_TYPE (విలువ), wi::గమ్యం_wide (విలువ));
	}
    }

  /* Don't let a cast be an lvalue.  */
  ఒకవేళ (lvalue_p (విలువ)
      /* Also, don't let a cast be a bit-field of a bit-precise integer type,
	 otherwise it could be incorrectly subject of integer promotions.  */
      || (వృక్షం_సంకేతం (విలువ) == COMPONENT_REF
	  && DECL_C_బిట్టు_క్షేత్రం (వృక్షం_నిర్వాహ్యం (విలువ, 1))
	  && BITINT_TYPE_P (DECL_బిట్టు_క్షేత్రం_TYPE (వృక్షం_నిర్వాహ్యం (విలువ, 1)))))
    విలువ = non_lvalue_loc (loc, విలువ);

  /* Don't allow the results of casting to floating-point or complex
     types be confused with actual constants, or casts involving
     integer and pointer types other than direct integer-to-integer
     and integer-to-pointer be confused with integer constant
     expressions and null pointer constants.  */
  ఒకవేళ (వృక్షం_సంకేతం (విలువ) == REAL_CST
      || వృక్షం_సంకేతం (విలువ) == COMPLEX_CST
      || (వృక్షం_సంకేతం (విలువ) == INTEGER_CST
	  && !((వృక్షం_సంకేతం (సమాసం) == INTEGER_CST
		&& INTEGRAL_TYPE_P (వృక్షం_TYPE (సమాసం)))
	       || వృక్షం_సంకేతం (సమాసం) == REAL_CST
	       || వృక్షం_సంకేతం (సమాసం) == COMPLEX_CST)))
      విలువ = build1 (NOP_సమాసం, type, విలువ);

  /* If the expression has integer operands and so can occur in an
     unevaluated part of an integer constant expression, ensure the
     return value reflects this.  */
  ఒకవేళ (int_operands
      && INTEGRAL_TYPE_P (type)
      && విలువ != error_mark_కణుపు
      && !సమాసం_INT_CONST_OPERANDS (విలువ))
    విలువ = note_integer_operands (విలువ);

  protected_సమితి_సమాసం_location (విలువ, loc);
  తిరిగి విలువ;
}

/* Interpret a cast of expression EXPR to type TYPE.  LOC is the
   location of the open paren of the cast, or the position of the cast
   expr.  */
వృక్షం
c_cast_సమాసం (location_t loc, నిర్మాణం c_type_name *type_name, వృక్షం సమాసం)
{
  వృక్షం type;
  వృక్షం type_సమాసం = NULL_వృక్షం;
  తార్కిక type_సమాసం_const = నిజం;
  వృక్షం ret;
  పూర్ణాంకం saved_wsp = warn_strict_prototypes;

  /* This avoids warnings about unprototyped casts on
     integers.  E.g. "#define SIG_DFL (void(*)())0".  */
  ఒకవేళ (వృక్షం_సంకేతం (సమాసం) == INTEGER_CST)
    warn_strict_prototypes = 0;
  type = groktypename (type_name, &type_సమాసం, &type_సమాసం_const);
  warn_strict_prototypes = saved_wsp;

  ఒకవేళ (వృక్షం_సంకేతం (సమాసం) == ADDR_సమాసం && !VOID_TYPE_P (type)
      && reject_gcc_builtin (సమాసం))
    తిరిగి error_mark_కణుపు;

  ret = build_c_cast (loc, type, సమాసం);
  ఒకవేళ (ret == error_mark_కణుపు)
    తిరిగి error_mark_కణుపు;

  ఒకవేళ (type_సమాసం)
    {
      తార్కిక inner_సమాసం_const = నిజం;
      ret = c_fully_fold (ret, require_constant_విలువ, &inner_సమాసం_const);
      ret = build2 (C_MAYBE_CONST_సమాసం, వృక్షం_TYPE (ret), type_సమాసం, ret);
      C_MAYBE_CONST_సమాసం_NON_CONST (ret) = !(type_సమాసం_const
					     && inner_సమాసం_const);
      సమితి_సమాసం_LOCATION (ret, loc);
    }

  ఒకవేళ (!సమాసం_HAS_LOCATION (ret))
    protected_సమితి_సమాసం_location (ret, loc);

  /* C++ does not permits types to be defined in a cast, but it
     allows references to incomplete types.  */
  ఒకవేళ (warn_cxx_compat && type_name->specs->typespec_రకం == ctsk_tagdef)
    warning_at (loc, OPT_Wc___compat,
		"defining a type in a cast is invalid in C++");

  తిరిగి ret;
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

వృక్షం
build_modify_సమాసం (location_t location, వృక్షం lhs, వృక్షం lhs_origtype,
		   గణన వృక్షం_సంకేతం_2 modifycode,
		   location_t rhs_loc, వృక్షం rhs, వృక్షం rhs_origtype)
{
  వృక్షం ఫలితం;
  వృక్షం newrhs;
  వృక్షం rhseval = NULL_వృక్షం;
  వృక్షం lhstype = వృక్షం_TYPE (lhs);
  వృక్షం olhstype = lhstype;
  తార్కిక npc;
  తార్కిక is_atomic_op;

  /* Types that aren't fully specified cannot be used in assignments.  */
  lhs = require_complete_type (location, lhs);
  rhs = require_complete_type (location, rhs);

  /* Avoid duplicate error messages from operands that had errors.  */
  ఒకవేళ (వృక్షం_సంకేతం (lhs) == ERROR_MARK || వృక్షం_సంకేతం (rhs) == ERROR_MARK)
    తిరిగి error_mark_కణుపు;

  /* Ensure an error for assigning a non-lvalue array to an array in
     C90.  */
  ఒకవేళ (వృక్షం_సంకేతం (lhstype) == ARRAY_TYPE)
    {
      error_at (location, "assignment to expression with array type");
      తిరిగి error_mark_కణుపు;
    }

  /* For ObjC properties, defer this check.  */
  ఒకవేళ (!objc_is_property_ref (lhs) && !lvalue_or_else (location, lhs, lv_కేటాయించు))
    తిరిగి error_mark_కణుపు;

  is_atomic_op = really_atomic_lvalue (lhs);

  newrhs = rhs;

  ఒకవేళ (వృక్షం_సంకేతం (lhs) == C_MAYBE_CONST_సమాసం)
    {
      వృక్షం inner = build_modify_సమాసం (location, C_MAYBE_CONST_సమాసం_సమాసం (lhs),
				      lhs_origtype, modifycode, rhs_loc, rhs,
				      rhs_origtype);
      ఒకవేళ (inner == error_mark_కణుపు)
	తిరిగి error_mark_కణుపు;
      ఫలితం = build2 (C_MAYBE_CONST_సమాసం, వృక్షం_TYPE (inner),
		       C_MAYBE_CONST_సమాసం_PRE (lhs), inner);
      gcc_assert (!C_MAYBE_CONST_సమాసం_INT_OPERANDS (lhs));
      C_MAYBE_CONST_సమాసం_NON_CONST (ఫలితం) = 1;
      protected_సమితి_సమాసం_location (ఫలితం, location);
      తిరిగి ఫలితం;
    }

  /* If a binary op has been requested, combine the old LHS value with the RHS
     producing the value we should actually store into the LHS.  */

  ఒకవేళ (modifycode != NOP_సమాసం)
    {
      lhs = c_fully_fold (lhs, అబద్ధం, ఖాళీ, నిజం);
      lhs = stabilize_reference (lhs);

      /* Construct the RHS for any non-atomic compound assignment. */
      ఒకవేళ (!is_atomic_op)
        {
	  /* If in LHS op= RHS the RHS has side-effects, ensure they
	     are preevaluated before the rest of the assignment expression's
	     side-effects, because RHS could contain e.g. function calls
	     that modify LHS.  */
	  ఒకవేళ (వృక్షం_SIDE_EFFECTS (rhs))
	    {
	      ఒకవేళ (వృక్షం_సంకేతం (rhs) == EXCESS_PRECISION_సమాసం)
		newrhs = save_సమాసం (వృక్షం_నిర్వాహ్యం (rhs, 0));
	      లేకపోతే
		newrhs = save_సమాసం (rhs);
	      rhseval = newrhs;
	      ఒకవేళ (వృక్షం_సంకేతం (rhs) == EXCESS_PRECISION_సమాసం)
		newrhs = build1 (EXCESS_PRECISION_సమాసం, వృక్షం_TYPE (rhs),
				 newrhs);
	    }
	  తార్కిక clear_decl_read = అబద్ధం;
	  ఒకవేళ ((VAR_P (lhs) || వృక్షం_సంకేతం (lhs) == PARM_DECL)
	      && !DECL_READ_P (lhs)
	      && (VAR_P (lhs) ? warn_వాడని_but_సమితి_variable
			      : warn_వాడని_but_సమితి_parameter) > 2)
	    {
	      mark_exp_read (newrhs);
	      ఒకవేళ (!DECL_READ_P (lhs))
		clear_decl_read = నిజం;
	    }

	  newrhs = build_ద్విమాన_op (location, modifycode,
				    convert_lvalue_గమ్యం_rvalue (location, lhs,
							      నిజం, నిజం),
				    newrhs, నిజం);
	  ఒకవేళ (clear_decl_read)
	    DECL_READ_P (lhs) = 0;

	  /* The original type of the right hand side is no longer
	     meaningful.  */
	  rhs_origtype = NULL_వృక్షం;
	}
    }

  ఒకవేళ (c_dialect_objc ())
    {
      /* Check if we are modifying an Objective-C property reference;
	 if so, we need to generate setter calls.  */
      ఒకవేళ (వృక్షం_సంకేతం (newrhs) == EXCESS_PRECISION_సమాసం)
	ఫలితం = objc_maybe_build_modify_సమాసం (lhs, వృక్షం_నిర్వాహ్యం (newrhs, 0));
      లేకపోతే
	ఫలితం = objc_maybe_build_modify_సమాసం (lhs, newrhs);
      ఒకవేళ (ఫలితం)
	వెళ్ళు return_ఫలితం;

      /* Else, do the check that we postponed for Objective-C.  */
      ఒకవేళ (!lvalue_or_else (location, lhs, lv_కేటాయించు))
	తిరిగి error_mark_కణుపు;
    }

  /* Give an error for storing in something that is 'const'.  */

  ఒకవేళ (TYPE_READONLY (lhstype)
      || (రికార్డు_OR_UNION_TYPE_P (lhstype)
	  && C_TYPE_FIELDS_READONLY (lhstype)))
    {
      readonly_error (location, lhs, lv_కేటాయించు);
      తిరిగి error_mark_కణుపు;
    }
  లేకపోతే ఒకవేళ (వృక్షం_READONLY (lhs))
    readonly_warning (lhs, lv_కేటాయించు);

  /* If storing into a structure or union member,
     it has probably been given type `int'.
     Compute the type that would go with
     the actual amount of storage the member occupies.  */

  ఒకవేళ (వృక్షం_సంకేతం (lhs) == COMPONENT_REF
      && (వృక్షం_సంకేతం (lhstype) == INTEGER_TYPE
	  || వృక్షం_సంకేతం (lhstype) == BOOLEAN_TYPE
	  || SCALAR_FLOAT_TYPE_P (lhstype)
	  || వృక్షం_సంకేతం (lhstype) == ENUMERAL_TYPE))
    lhstype = వృక్షం_TYPE (get_unwidened (lhs, 0));

  /* If storing in a field that is in actuality a short or narrower than one,
     we must store in the field in its actual type.  */

  ఒకవేళ (lhstype != వృక్షం_TYPE (lhs))
    {
      lhs = copy_కణుపు (lhs);
      వృక్షం_TYPE (lhs) = lhstype;
    }

  /* Issue -Wc++-compat warnings about an assignment to an enum type
     when LHS does not have its original type.  This happens for,
     e.g., an enum bitfield in a struct.  */
  ఒకవేళ (warn_cxx_compat
      && lhs_origtype != NULL_వృక్షం
      && lhs_origtype != lhstype
      && వృక్షం_సంకేతం (lhs_origtype) == ENUMERAL_TYPE)
    {
      వృక్షం checktype = (rhs_origtype != NULL_వృక్షం
			? rhs_origtype
			: వృక్షం_TYPE (rhs));
      ఒకవేళ (checktype != error_mark_కణుపు
	  && (TYPE_MAIN_VARIANT (checktype) != TYPE_MAIN_VARIANT (lhs_origtype)
	      || (is_atomic_op && modifycode != NOP_సమాసం)))
	warning_at (location, OPT_Wc___compat,
		    "enum conversion in assignment is invalid in C++");
    }

  /* Remove qualifiers.  */
  lhstype = c_build_qualified_type (lhstype, TYPE_UNQUALIFIED);
  olhstype = c_build_qualified_type (olhstype, TYPE_UNQUALIFIED);

  /* Convert new value to destination type.  Fold it first, then
     restore any excess precision information, for the sake of
     conversion warnings.  */

  ఒకవేళ (!(is_atomic_op && modifycode != NOP_సమాసం))
    {
      వృక్షం rhs_semantic_type = NULL_వృక్షం;
      ఒకవేళ (!c_లోపల_omp_for)
	{
	  ఒకవేళ (వృక్షం_సంకేతం (newrhs) == EXCESS_PRECISION_సమాసం)
	    {
	      rhs_semantic_type = వృక్షం_TYPE (newrhs);
	      newrhs = వృక్షం_నిర్వాహ్యం (newrhs, 0);
	    }
	  npc = null_సూచిక_constant_p (newrhs);
	  newrhs = c_fully_fold (newrhs, అబద్ధం, ఖాళీ);
	  ఒకవేళ (rhs_semantic_type)
	    newrhs = build1 (EXCESS_PRECISION_సమాసం, rhs_semantic_type, newrhs);
	}
      లేకపోతే
	npc = null_సూచిక_constant_p (newrhs);
      newrhs = convert_for_assignment (location, rhs_loc, lhstype, newrhs,
				       rhs_origtype, ic_కేటాయించు, npc,
				       NULL_వృక్షం, NULL_వృక్షం, 0);
      ఒకవేళ (వృక్షం_సంకేతం (newrhs) == ERROR_MARK)
	తిరిగి error_mark_కణుపు;
    }

  /* Emit ObjC write barrier, if necessary.  */
  ఒకవేళ (c_dialect_objc () && flag_objc_gc)
    {
      ఫలితం = objc_generate_write_barrier (lhs, modifycode, newrhs);
      ఒకవేళ (ఫలితం)
	{
	  protected_సమితి_సమాసం_location (ఫలితం, location);
	  వెళ్ళు return_ఫలితం;
	}
    }

  /* Scan operands.  */

  ఒకవేళ (is_atomic_op)
    ఫలితం = build_atomic_కేటాయించు (location, lhs, modifycode, newrhs, అబద్ధం);
  లేకపోతే
    {
      ఫలితం = build2 (MODIFY_సమాసం, lhstype, lhs, newrhs);
      వృక్షం_SIDE_EFFECTS (ఫలితం) = 1;
      protected_సమితి_సమాసం_location (ఫలితం, location);
    }

  /* If we got the LHS in a different type for storing in,
     convert the result back to the nominal type of LHS
     so that the value we return always has the same type
     as the LHS argument.  */

  ఒకవేళ (olhstype == వృక్షం_TYPE (ఫలితం))
    వెళ్ళు return_ఫలితం;

  ఫలితం = convert_for_assignment (location, rhs_loc, olhstype, ఫలితం,
				   rhs_origtype, ic_కేటాయించు, అబద్ధం, NULL_వృక్షం,
				   NULL_వృక్షం, 0);
  protected_సమితి_సమాసం_location (ఫలితం, location);

return_ఫలితం:
  ఒకవేళ (rhseval)
    ఫలితం = build2 (COMPOUND_సమాసం, వృక్షం_TYPE (ఫలితం), rhseval, ఫలితం);
  తిరిగి ఫలితం;
}

/* Return whether STRUCT_TYPE has an anonymous field with type TYPE.
   This is used to implement -fplan9-extensions.  */

స్థిర తార్కిక
కనుగొను_anonymous_క్షేత్రం_with_type (వృక్షం struct_type, వృక్షం type)
{
  వృక్షం క్షేత్రం_2;
  తార్కిక దొరికింది;

  gcc_assert (రికార్డు_OR_UNION_TYPE_P (struct_type));
  దొరికింది = అబద్ధం;
  కొరకు (క్షేత్రం_2 = TYPE_FIELDS (struct_type);
       క్షేత్రం_2 != NULL_వృక్షం;
       క్షేత్రం_2 = వృక్షం_CHAIN (క్షేత్రం_2))
    {
      వృక్షం fieldtype = remove_qualifiers (వృక్షం_TYPE (క్షేత్రం_2));
      ఒకవేళ (DECL_NAME (క్షేత్రం_2) == ఖాళీ
	  && comptypes (type, fieldtype))
	{
	  ఒకవేళ (దొరికింది)
	    తిరిగి అబద్ధం;
	  దొరికింది = నిజం;
	}
      లేకపోతే ఒకవేళ (DECL_NAME (క్షేత్రం_2) == ఖాళీ
	       && రికార్డు_OR_UNION_TYPE_P (వృక్షం_TYPE (క్షేత్రం_2))
	       && కనుగొను_anonymous_క్షేత్రం_with_type (వృక్షం_TYPE (క్షేత్రం_2), type))
	{
	  ఒకవేళ (దొరికింది)
	    తిరిగి అబద్ధం;
	  దొరికింది = నిజం;
	}
    }
  తిరిగి దొరికింది;
}

/* RHS is an expression whose type is pointer to struct.  If there is
   an anonymous field in RHS with type TYPE, then return a pointer to
   that field in RHS.  This is used with -fplan9-extensions.  This
   returns NULL if no conversion could be found.  */

స్థిర వృక్షం
convert_గమ్యం_anonymous_క్షేత్రం (location_t location, వృక్షం type, వృక్షం rhs)
{
  వృక్షం rhs_struct_type, lhs_main_type;
  వృక్షం క్షేత్రం_2, దొరికింది_క్షేత్రం;
  తార్కిక దొరికింది_sub_క్షేత్రం;
  వృక్షం ret;

  gcc_assert (సూచిక_TYPE_P (వృక్షం_TYPE (rhs)));
  rhs_struct_type = వృక్షం_TYPE (వృక్షం_TYPE (rhs));
  gcc_assert (రికార్డు_OR_UNION_TYPE_P (rhs_struct_type));

  gcc_assert (సూచిక_TYPE_P (type));
  lhs_main_type = remove_qualifiers (వృక్షం_TYPE (type));

  దొరికింది_క్షేత్రం = NULL_వృక్షం;
  దొరికింది_sub_క్షేత్రం = అబద్ధం;
  కొరకు (క్షేత్రం_2 = TYPE_FIELDS (rhs_struct_type);
       క్షేత్రం_2 != NULL_వృక్షం;
       క్షేత్రం_2 = వృక్షం_CHAIN (క్షేత్రం_2))
    {
      ఒకవేళ (DECL_NAME (క్షేత్రం_2) != NULL_వృక్షం
	  || !రికార్డు_OR_UNION_TYPE_P (వృక్షం_TYPE (క్షేత్రం_2)))
	కొనసాగు;
      వృక్షం fieldtype = remove_qualifiers (వృక్షం_TYPE (క్షేత్రం_2));
      ఒకవేళ (comptypes (lhs_main_type, fieldtype))
	{
	  ఒకవేళ (దొరికింది_క్షేత్రం != NULL_వృక్షం)
	    తిరిగి NULL_వృక్షం;
	  దొరికింది_క్షేత్రం = క్షేత్రం_2;
	}
      లేకపోతే ఒకవేళ (కనుగొను_anonymous_క్షేత్రం_with_type (వృక్షం_TYPE (క్షేత్రం_2),
					       lhs_main_type))
	{
	  ఒకవేళ (దొరికింది_క్షేత్రం != NULL_వృక్షం)
	    తిరిగి NULL_వృక్షం;
	  దొరికింది_క్షేత్రం = క్షేత్రం_2;
	  దొరికింది_sub_క్షేత్రం = నిజం;
	}
    }

  ఒకవేళ (దొరికింది_క్షేత్రం == NULL_వృక్షం)
    తిరిగి NULL_వృక్షం;

  ret = fold_build3_loc (location, COMPONENT_REF, వృక్షం_TYPE (దొరికింది_క్షేత్రం),
			 build_fold_పరోక్ష_ref (rhs), దొరికింది_క్షేత్రం,
			 NULL_వృక్షం);
  ret = build_fold_addr_సమాసం_loc (location, ret);

  ఒకవేళ (దొరికింది_sub_క్షేత్రం)
    {
      ret = convert_గమ్యం_anonymous_క్షేత్రం (location, type, ret);
      gcc_assert (ret != NULL_వృక్షం);
    }

  తిరిగి ret;
}

/* Issue an error message for a bad initializer component.
   GMSGID identifies the message.
   The component name is taken from the spelling stack.  */

స్థిర శూన్య ATTRIBUTE_GCC_DIAG (2,0)
error_init (location_t loc, స్థిరరాశి అక్షరం *gmsgid, ...)
{
  అక్షరం *ofwhat;

  auto_diagnostic_సమూహం d;

  /* The gmsgid may be a format string with %< and %>. */
  va_list ap;
  va_ప్రారంభం (ap, gmsgid);
  తార్కిక warned = emit_diagnostic_valist (diagnostics::రకం::error,
					loc, -1, gmsgid, &ap);
  va_చివర (ap);

  ofwhat = print_spelling ((అక్షరం *) alloca (spelling_నిడివి () + 1));
  ఒకవేళ (*ofwhat && warned)
    inform (loc, "(near initialization for %qs)", ofwhat);
}

/* Used to implement pedwarn_init and permerror_init.  */

స్థిర తార్కిక ATTRIBUTE_GCC_DIAG (3,0)
pedwarn_permerror_init (location_t loc, పూర్ణాంకం opt, స్థిరరాశి అక్షరం *gmsgid,
			va_list *ap, గణన diagnostics::రకం రకం)
{
  /* Use the location where a macro was expanded rather than where
     it was defined to make sure macros defined in system headers
     but used incorrectly elsewhere are diagnosed.  */
  location_t exploc = expansion_బిందువు_location_if_లోపల_system_శీర్షిక (loc);
  auto_diagnostic_సమూహం d;
  తార్కిక warned = emit_diagnostic_valist (రకం, exploc, opt, gmsgid, ap);
  ఒకవేళ (warned)
    {
      అక్షరం *ofwhat = print_spelling ((అక్షరం *) alloca (spelling_నిడివి () + 1));
      ఒకవేళ (*ofwhat)
	inform (exploc, "(near initialization for %qs)", ofwhat);
    }
  తిరిగి warned;
}

/* Issue a pedantic warning for a bad initializer component.  OPT is
   the option OPT_* (from options.h) controlling this warning or 0 if
   it is unconditionally given.  GMSGID identifies the message.  The
   component name is taken from the spelling stack.  */

స్థిర తార్కిక ATTRIBUTE_GCC_DIAG (3,0)
pedwarn_init (location_t loc, పూర్ణాంకం opt, స్థిరరాశి అక్షరం *gmsgid, ...)
{
  va_list ap;
  va_ప్రారంభం (ap, gmsgid);
  తార్కిక warned = pedwarn_permerror_init (loc, opt, gmsgid, &ap,
					diagnostics::రకం::pedwarn);
  va_చివర (ap);
  తిరిగి warned;
}

/* Like pedwarn_init, but issue a permerror.  */

స్థిర తార్కిక ATTRIBUTE_GCC_DIAG (3,0)
permerror_init (location_t loc, పూర్ణాంకం opt, స్థిరరాశి అక్షరం *gmsgid, ...)
{
  va_list ap;
  va_ప్రారంభం (ap, gmsgid);
  తార్కిక warned = pedwarn_permerror_init (loc, opt, gmsgid, &ap,
					diagnostics::రకం::permerror);
  va_చివర (ap);
  తిరిగి warned;
}

/* Issue a warning for a bad initializer component.

   OPT is the OPT_W* value corresponding to the warning option that
   controls this warning.  GMSGID identifies the message.  The
   component name is taken from the spelling stack.  */

స్థిర శూన్య
warning_init (location_t loc, పూర్ణాంకం opt, స్థిరరాశి అక్షరం *gmsgid)
{
  అక్షరం *ofwhat;
  తార్కిక warned;

  auto_diagnostic_సమూహం d;

  /* Use the location where a macro was expanded rather than where
     it was defined to make sure macros defined in system headers
     but used incorrectly elsewhere are diagnosed.  */
  location_t exploc = expansion_బిందువు_location_if_లోపల_system_శీర్షిక (loc);

  /* The gmsgid may be a format string with %< and %>. */
  warned = warning_at (exploc, opt, gmsgid);
  ఒకవేళ (warned)
    {
      ofwhat = print_spelling ((అక్షరం *) alloca (spelling_నిడివి () + 1));
      ఒకవేళ (*ofwhat)
	inform (exploc, "(near initialization for %qs)", ofwhat);
    }
}

/* If TYPE is an array type and EXPR is a parenthesized string
   constant, warn if pedantic that EXPR is being used to initialize an
   object of type TYPE.  */

శూన్య
maybe_warn_string_init (location_t loc, వృక్షం type, నిర్మాణం c_సమాసం సమాసం)
{
  ఒకవేళ (pedantic
      && వృక్షం_సంకేతం (type) == ARRAY_TYPE
      && వృక్షం_సంకేతం (సమాసం.విలువ) == STRING_CST
      && సమాసం.original_సంకేతం != STRING_CST)
    pedwarn_init (loc, OPT_Wpedantic,
		  "array initialized from parenthesized string constant");
}

/* Attempt to locate the parameter with the given index within FNDECL,
   returning DECL_SOURCE_LOCATION (FNDECL) if it can't be found.  */

స్థిర location_t
get_fndecl_వాదం_location (వృక్షం fndecl, పూర్ణాంకం argnum)
{
  పూర్ణాంకం i;
  వృక్షం param;

  /* Locate param by index within DECL_ARGUMENTS (fndecl).  */
  కొరకు (i = 0, param = DECL_ARGUMENTS (fndecl);
       i < argnum && param;
       i++, param = వృక్షం_CHAIN (param))
    ;

  /* If something went wrong (e.g. if we have a builtin and thus no arguments),
     return DECL_SOURCE_LOCATION (FNDECL).  */
  ఒకవేళ (param == ఖాళీ)
    తిరిగి DECL_ఆధారం_LOCATION (fndecl);

  తిరిగి DECL_ఆధారం_LOCATION (param);
}

/* Issue a note about a mismatching argument for parameter PARMNUM
   to FUNDECL, for types EXPECTED_TYPE and ACTUAL_TYPE.
   Attempt to issue the note at the pertinent parameter of the decl;
   failing that issue it at the location of FUNDECL; failing that
   issue it at PLOC.
   Use highlight_colors::actual for the ACTUAL_TYPE
   and highlight_colors::expected for EXPECTED_TYPE and the
   parameter of FUNDECL*/

స్థిర శూన్య
inform_for_arg (వృక్షం fundecl, location_t ploc, పూర్ణాంకం parmnum,
		వృక్షం expected_type, వృక్షం actual_type)
{
  location_t loc;
  ఒకవేళ (fundecl && !DECL_IS_UNDECLARED_BUILTIN (fundecl))
    loc = get_fndecl_వాదం_location (fundecl, parmnum - 1);
  లేకపోతే
    loc = ploc;

  gcc_rich_location richloc (loc, శూన్యసూచిక, highlight_colors::expected);

  pp_markup::element_expected_type elem_expected_type (expected_type);
  pp_markup::element_actual_type elem_actual_type (actual_type);
  inform (&richloc,
	  "expected %e but argument is of type %e",
	  &elem_expected_type, &elem_actual_type);
}

/* Issue a warning when an argument of ARGTYPE is passed to a built-in
   function FUNDECL declared without prototype to parameter PARMNUM of
   PARMTYPE when ARGTYPE does not promote to PARMTYPE.  */

స్థిర శూన్య
maybe_warn_builtin_no_proto_arg (location_t loc, వృక్షం fundecl, పూర్ణాంకం parmnum,
				 వృక్షం parmtype, వృక్షం argtype)
{
  వృక్షం_సంకేతం_2 parmcode = వృక్షం_సంకేతం (parmtype);
  వృక్షం_సంకేతం_2 argcode = వృక్షం_సంకేతం (argtype);
  వృక్షం promoted = c_type_promotes_గమ్యం (argtype);

  /* Avoid warning for enum arguments that promote to an integer type
     of the same size/mode.  */
  ఒకవేళ (parmcode == INTEGER_TYPE
      && argcode == ENUMERAL_TYPE
      && TYPE_బహుళకం (parmtype) == TYPE_బహుళకం (argtype))
    తిరిగి;

  ఒకవేళ ((parmcode == argcode
       || (parmcode == INTEGER_TYPE
	   && argcode == ENUMERAL_TYPE))
      && TYPE_MAIN_VARIANT (parmtype) == TYPE_MAIN_VARIANT (promoted))
    తిరిగి;

  /* This diagnoses even signed/unsigned mismatches.  Those might be
     safe in many cases but GCC may emit suboptimal code for them so
     warning on those cases drives efficiency improvements.  */
  ఒకవేళ (warning_at (loc, OPT_Wbuiltin_declaration_mismatch,
		  TYPE_MAIN_VARIANT (promoted) == argtype
		  ? G_("%qD argument %d type is %qT where %qT is expected "
		       "in a call to built-in function declared without "
		       "prototype")
		  : G_("%qD argument %d promotes to %qT where %qT is expected "
		       "in a call to built-in function declared without "
		       "prototype"),
		  fundecl, parmnum, promoted, parmtype))
    inform (DECL_ఆధారం_LOCATION (fundecl),
	    "built-in %qD declared here",
	    fundecl);
}

/* Print a declaration in quotes, with the given highlight_color.
   Analogous to handler for %qD, but with a specific highlight color.  */

తరగతి pp_element_quoted_decl : బహిరంగ pp_element
{
బహిరంగ:
  pp_element_quoted_decl (వృక్షం decl, స్థిరరాశి అక్షరం *highlight_color)
  : m_decl (decl),
    m_highlight_color (highlight_color)
  {
  }

  శూన్య కూడు_గమ్యం_phase_2 (pp_markup::context &ctxt) override
  {
    ctxt.begin_quote ();
    ctxt.begin_highlight_color (m_highlight_color);

    print_decl (ctxt);

    ctxt.చివర_highlight_color ();
    ctxt.చివర_quote ();
  }

  శూన్య print_decl (pp_markup::context &ctxt)
  {
    pretty_printer *స్థిరరాశి pp = &ctxt.m_pp;
    pp->సమితి_padding (pp_none);
    ఒకవేళ (DECL_NAME (m_decl))
      pp_identifier (pp, lang_hooks.decl_printable_name (m_decl, 2));
    లేకపోతే
      pp_string (pp, _("({anonymous})"));
  }

అంతరంగ:
  వృక్షం m_decl;
  స్థిరరాశి అక్షరం *m_highlight_color;
};

/* If TYPE is from a typedef, issue a note showing the location
   to the user.
   Use HIGHLIGHT_COLOR as the highlight color.  */

స్థిర శూన్య
maybe_inform_typedef_location (వృక్షం type, స్థిరరాశి అక్షరం *highlight_color)
{
  ఒకవేళ (!typedef_variant_p (type))
    తిరిగి;

  వృక్షం typedef_decl = TYPE_NAME (type);
  gcc_assert (వృక్షం_సంకేతం (typedef_decl) == TYPE_DECL);
  gcc_rich_location richloc (DECL_ఆధారం_LOCATION (typedef_decl),
			     శూన్యసూచిక, highlight_color);
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

స్థిర వృక్షం
convert_for_assignment (location_t location, location_t సమాసం_loc, వృక్షం type,
			వృక్షం rhs, వృక్షం origtype, గణన impl_conv errtype,
			తార్కిక null_సూచిక_constant, వృక్షం fundecl,
			వృక్షం function, పూర్ణాంకం parmnum, పూర్ణాంకం warnopt /* = 0 */)
{
  గణన వృక్షం_సంకేతం_2 codel = వృక్షం_సంకేతం (type);
  వృక్షం orig_rhs = rhs;
  వృక్షం rhstype;
  గణన వృక్షం_సంకేతం_2 coder;
  వృక్షం rname = NULL_వృక్షం;
  తార్కిక objc_ok = అబద్ధం;

  /* Use the expansion point location to handle cases such as user's
     function returning a wrong-type macro defined in a system header.  */
  location = expansion_బిందువు_location_if_లోపల_system_శీర్షిక (location);

  ఒకవేళ (errtype == ic_argpass)
    {
      వృక్షం selector;
      /* Change pointer to function to the function itself for
	 diagnostics.  */
      ఒకవేళ (వృక్షం_సంకేతం (function) == ADDR_సమాసం
	  && వృక్షం_సంకేతం (వృక్షం_నిర్వాహ్యం (function, 0)) == FUNCTION_DECL)
	function = వృక్షం_నిర్వాహ్యం (function, 0);

      /* Handle an ObjC selector specially for diagnostics.  */
      selector = objc_సందేశం_selector ();
      rname = function;
      ఒకవేళ (selector && parmnum > 2)
	{
	  rname = selector;
	  parmnum -= 2;
	}
    }

  /* This macro is used to emit diagnostics to ensure that all format
     strings are complete sentences, visible to gettext and checked at
     compile time.  */
#నిర్వచించు PEDWARN_FOR_ASSIGNMENT(LOCATION, PLOC, OPT, AR, AS, లోపల, RE)	 \
  చేయి {                                                                   \
    ఎంపిక (errtype)                                                     \
      {                                                                  \
      స్థితి ic_argpass:                                                   \
	{								\
	  auto_diagnostic_సమూహం d;						\
	  ఒకవేళ (pedwarn (PLOC, OPT, AR, parmnum, rname))		\
	    inform_for_arg (fundecl, (PLOC), parmnum, type, rhstype); \
	}								\
        ఆపు;                                                           \
      స్థితి ic_కేటాయించు:                                                    \
        pedwarn (LOCATION, OPT, AS);                                     \
        ఆపు;                                                           \
      స్థితి ic_init:                                                      \
      స్థితి ic_init_const:                                                \
        pedwarn_init (LOCATION, OPT, లోపల);                                \
        ఆపు;                                                           \
      స్థితి ic_return:                                                    \
        pedwarn (LOCATION, OPT, RE);					 \
        ఆపు;                                                           \
      అప్రమేయ:                                                           \
        gcc_unreachable ();                                              \
      }                                                                  \
  } అయితే (0)

  /* This macro is used to emit diagnostics to ensure that all format
     strings are complete sentences, visible to gettext and checked at
     compile time.  It can be called with 'pedwarn' or 'warning_at'.  */
#నిర్వచించు WARNING_FOR_QUALIFIERS(PEDWARN, LOCATION, PLOC, OPT, AR, AS, లోపల, RE, QUALS) \
  చేయి {                                                                   \
    ఎంపిక (errtype)                                                     \
      {                                                                  \
      స్థితి ic_argpass:                                                   \
	{								 \
	  auto_diagnostic_సమూహం d;					 \
	  ఒకవేళ (PEDWARN) {						 \
	    ఒకవేళ (pedwarn (PLOC, OPT, AR, parmnum, rname, QUALS))          \
	      inform_for_arg (fundecl, (PLOC), parmnum, type, rhstype);  \
	  } లేకపోతే {							 \
	    ఒకవేళ (warning_at (PLOC, OPT, AR, parmnum, rname, QUALS))	 \
	      inform_for_arg (fundecl, (PLOC), parmnum, type, rhstype);  \
	  }								 \
	}								 \
        ఆపు;                                                           \
      స్థితి ic_కేటాయించు:                                                    \
	ఒకవేళ (PEDWARN)							 \
	  pedwarn (LOCATION, OPT, AS, QUALS);                            \
	లేకపోతే								 \
	  warning_at (LOCATION, OPT, AS, QUALS);                         \
        ఆపు;                                                           \
      స్థితి ic_init:                                                      \
      స్థితి ic_init_const:                                                \
	ఒకవేళ (PEDWARN)							 \
	  pedwarn (LOCATION, OPT, లోపల, QUALS);                            \
	లేకపోతే								 \
	  warning_at (LOCATION, OPT, లోపల, QUALS);                         \
        ఆపు;                                                           \
      స్థితి ic_return:                                                    \
	ఒకవేళ (PEDWARN)							 \
	  pedwarn (LOCATION, OPT, RE, QUALS);                            \
	లేకపోతే								 \
	  warning_at (LOCATION, OPT, RE, QUALS);                         \
        ఆపు;                                                           \
      అప్రమేయ:                                                           \
        gcc_unreachable ();                                              \
      }                                                                  \
  } అయితే (0)

  /* This macro is used to emit diagnostics to ensure that all format
     strings are complete sentences, visible to gettext and checked at
     compile time.  It is the same as PEDWARN_FOR_ASSIGNMENT but with an
     extra parameter to enumerate qualifiers.  */
#నిర్వచించు PEDWARN_FOR_QUALIFIERS(LOCATION, PLOC, OPT, AR, AS, లోపల, RE, QUALS) \
   WARNING_FOR_QUALIFIERS (నిజం, LOCATION, PLOC, OPT, AR, AS, లోపల, RE, QUALS)


  ఒకవేళ (వృక్షం_సంకేతం (rhs) == EXCESS_PRECISION_సమాసం)
    rhs = వృక్షం_నిర్వాహ్యం (rhs, 0);

  rhstype = వృక్షం_TYPE (rhs);
  coder = వృక్షం_సంకేతం (rhstype);

  ఒకవేళ (coder == ERROR_MARK)
    తిరిగి error_mark_కణుపు;

  ఒకవేళ (c_dialect_objc ())
    {
      పూర్ణాంకం parmno;

      ఎంపిక (errtype)
	{
	స్థితి ic_return:
	  parmno = 0;
	  ఆపు;

	స్థితి ic_కేటాయించు:
	  parmno = -1;
	  ఆపు;

	స్థితి ic_init:
	స్థితి ic_init_const:
	  parmno = -2;
	  ఆపు;

	అప్రమేయ:
	  parmno = parmnum;
	  ఆపు;
	}

      objc_ok = objc_compare_types (type, rhstype, parmno, rname);
    }

  ఒకవేళ (warn_cxx_compat)
    {
      వృక్షం checktype = origtype != NULL_వృక్షం ? origtype : rhstype;
      ఒకవేళ (checktype != error_mark_కణుపు
	  && వృక్షం_సంకేతం (type) == ENUMERAL_TYPE
	  && TYPE_MAIN_VARIANT (checktype) != TYPE_MAIN_VARIANT (type))
	ఎంపిక (errtype)
	  {
	  స్థితి ic_argpass:
	    ఒకవేళ (pedwarn (సమాసం_loc, OPT_Wc___compat, "enum conversion when "
			 "passing argument %d of %qE is invalid in C++",
			 parmnum, rname))
	      inform ((fundecl && !DECL_IS_UNDECLARED_BUILTIN (fundecl))
		      ? DECL_ఆధారం_LOCATION (fundecl) : సమాసం_loc,
		      "expected %qT but argument is of type %qT",
		      type, rhstype);
	    ఆపు;
	  స్థితి ic_కేటాయించు:
	    pedwarn (location, OPT_Wc___compat, "enum conversion from %qT to "
		     "%qT in assignment is invalid in C++", rhstype, type);
	    ఆపు;
	  స్థితి ic_init:
	  స్థితి ic_init_const:
	    pedwarn_init (location, OPT_Wc___compat, "enum conversion from "
			  "%qT to %qT in initialization is invalid in C++",
			  rhstype, type);
	    ఆపు;
	  స్థితి ic_return:
	    pedwarn (location, OPT_Wc___compat, "enum conversion from %qT to "
		     "%qT in return is invalid in C++", rhstype, type);
	    ఆపు;
	  అప్రమేయ:
	    gcc_unreachable ();
	  }
    }

  ఒకవేళ (warn_enum_conversion)
    {
      వృక్షం checktype = origtype != NULL_వృక్షం ? origtype : rhstype;
      ఒకవేళ (checktype != error_mark_కణుపు
	  && వృక్షం_సంకేతం (checktype) == ENUMERAL_TYPE
	  && వృక్షం_సంకేతం (type) == ENUMERAL_TYPE
	  && !comptypes (TYPE_MAIN_VARIANT (checktype), TYPE_MAIN_VARIANT (type)))
       {
	  gcc_rich_location loc (location);
	  warning_at (&loc, OPT_Wenum_conversion,
		      "implicit conversion from %qT to %qT",
		      checktype, type);
       }
    }

  ఒకవేళ (TYPE_MAIN_VARIANT (type) == TYPE_MAIN_VARIANT (rhstype))
    {
      warn_for_చిరునామా_యొక్క_packed_member (type, orig_rhs);
      ఒకవేళ (type != rhstype)
	/* Convert RHS to TYPE in order to not lose TYPE in diagnostics.  */
	rhs = convert (type, rhs);
      తిరిగి rhs;
    }

  ఒకవేళ (coder == VOID_TYPE)
    {
      /* Except for passing an argument to an unprototyped function,
	 this is a constraint violation.  When passing an argument to
	 an unprototyped function, it is compile-time undefined;
	 making it a constraint in that case was rejected in
	 DR#252.  */
      స్థిరరాశి అక్షరం సందేశం_2[] = "void value not ignored as it ought to be";
      ఒకవేళ (warnopt)
	warning_at (location, warnopt, సందేశం_2);
      లేకపోతే
	error_at (location, సందేశం_2);
      తిరిగి error_mark_కణుపు;
    }
  rhs = require_complete_type (location, rhs);
  ఒకవేళ (rhs == error_mark_కణుపు)
    తిరిగి error_mark_కణుపు;

  ఒకవేళ (coder == సూచిక_TYPE && reject_gcc_builtin (rhs))
    తిరిగి error_mark_కణుపు;

  /* A non-reference type can convert to a reference.  This handles
     va_start, va_copy and possibly port built-ins.  */
  ఒకవేళ (codel == REFERENCE_TYPE && coder != REFERENCE_TYPE)
    {
      ఒకవేళ (!lvalue_p (rhs))
	{
	  స్థిరరాశి అక్షరం సందేశం_2[] = "cannot pass rvalue to reference parameter";
	  ఒకవేళ (warnopt)
	    warning_at (location, warnopt, సందేశం_2);
	  లేకపోతే
	    error_at (location, సందేశం_2);
	  తిరిగి error_mark_కణుపు;
	}
      ఒకవేళ (!c_mark_addressable (rhs))
	తిరిగి error_mark_కణుపు;
      rhs = build1 (ADDR_సమాసం, c_build_సూచిక_type (వృక్షం_TYPE (rhs)), rhs);
      సమితి_సమాసం_LOCATION (rhs, location);

      rhs = convert_for_assignment (location, సమాసం_loc,
				    c_build_సూచిక_type (వృక్షం_TYPE (type)),
				    rhs, origtype, errtype,
				    null_సూచిక_constant, fundecl, function,
				    parmnum, warnopt);
      ఒకవేళ (rhs == error_mark_కణుపు)
	తిరిగి error_mark_కణుపు;

      rhs = build1 (NOP_సమాసం, type, rhs);
      సమితి_సమాసం_LOCATION (rhs, location);
      తిరిగి rhs;
    }
  /* Some types can interconvert without explicit casts.  */
  లేకపోతే ఒకవేళ (codel == సదిశ_TYPE && coder == సదిశ_TYPE
	   && సదిశ_types_convertible_p (type, వృక్షం_TYPE (rhs), నిజం))
    తిరిగి convert (type, rhs);
  /* Arithmetic types all interconvert, and enum is treated like int.  */
  లేకపోతే ఒకవేళ ((codel == INTEGER_TYPE || codel == REAL_TYPE
	    || codel == FIXED_బిందువు_TYPE
	    || codel == ENUMERAL_TYPE || codel == COMPLEX_TYPE
	    || codel == BOOLEAN_TYPE || codel == BITINT_TYPE)
	   && (coder == INTEGER_TYPE || coder == REAL_TYPE
	       || coder == FIXED_బిందువు_TYPE
	       || coder == ENUMERAL_TYPE || coder == COMPLEX_TYPE
	       || coder == BOOLEAN_TYPE || coder == BITINT_TYPE))
    {
      ఒకవేళ (warnopt && errtype == ic_argpass)
	maybe_warn_builtin_no_proto_arg (సమాసం_loc, fundecl, parmnum, type,
					 rhstype);

      తార్కిక save = లోపల_late_ద్విమాన_op;
      ఒకవేళ (C_BOOLEAN_TYPE_P (type) || codel == COMPLEX_TYPE
	  || (coder == REAL_TYPE
	      && (codel == INTEGER_TYPE || codel == ENUMERAL_TYPE)
	      && sanitize_flags_p (SANITIZE_FLOAT_CAST)))
	లోపల_late_ద్విమాన_op = నిజం;
      వృక్షం ret = convert_and_check (సమాసం_loc != UNKNOWN_LOCATION
				    ? సమాసం_loc : location, type, orig_rhs,
				    errtype == ic_init_const);
      లోపల_late_ద్విమాన_op = save;
      తిరిగి ret;
    }

  /* Aggregates in different TUs might need conversion.  */
  ఒకవేళ ((codel == రికార్డు_TYPE || codel == UNION_TYPE)
      && codel == coder
      && comptypes (TYPE_MAIN_VARIANT (type), TYPE_MAIN_VARIANT (rhstype)))
    తిరిగి convert_and_check (సమాసం_loc != UNKNOWN_LOCATION
			      ? సమాసం_loc : location, type, rhs);

  /* Conversion to a transparent union or record from its member types.
     This applies only to function arguments.  */
  ఒకవేళ (((codel == UNION_TYPE || codel == రికార్డు_TYPE)
      && TYPE_TRANSPARENT_AGGR (type))
      && errtype == ic_argpass)
    {
      వృక్షం memb, marginal_memb = NULL_వృక్షం;

      కొరకు (memb = TYPE_FIELDS (type); memb ; memb = DECL_CHAIN (memb))
	{
	  వృక్షం memb_type = వృక్షం_TYPE (memb);

	  ఒకవేళ (comptypes (TYPE_MAIN_VARIANT (memb_type),
			 TYPE_MAIN_VARIANT (rhstype)))
	    ఆపు;

	  ఒకవేళ (వృక్షం_సంకేతం (memb_type) != సూచిక_TYPE)
	    కొనసాగు;

	  ఒకవేళ (coder == సూచిక_TYPE)
	    {
	      వృక్షం ttl = వృక్షం_TYPE (memb_type);
	      వృక్షం ttr = వృక్షం_TYPE (rhstype);

	      /* Any non-function converts to a [const][volatile] void *
		 and vice versa; otherwise, targets must be the same.
		 Meanwhile, the lhs target must have all the qualifiers of
		 the rhs.  */
	      ఒకవేళ ((VOID_TYPE_P (ttl) && !TYPE_ATOMIC (ttl))
		  || (VOID_TYPE_P (ttr) && !TYPE_ATOMIC (ttr))
		  || comp_లక్ష్యం_types (location, memb_type, rhstype))
		{
		  పూర్ణాంకం lquals = TYPE_QUALS (ttl) & ~TYPE_QUAL_ATOMIC;
		  పూర్ణాంకం rquals = TYPE_QUALS (ttr) & ~TYPE_QUAL_ATOMIC;
		  /* If this type won't generate any warnings, use it.  */
		  ఒకవేళ (lquals == rquals
		      || ((వృక్షం_సంకేతం (ttr) == FUNCTION_TYPE
			   && వృక్షం_సంకేతం (ttl) == FUNCTION_TYPE)
			  ? ((lquals | rquals) == rquals)
			  : ((lquals | rquals) == lquals)))
		    ఆపు;

		  /* Keep looking for a better type, but remember this one.  */
		  ఒకవేళ (!marginal_memb)
		    marginal_memb = memb;
		}
	    }

	  /* Can convert integer zero to any pointer type.  */
	  ఒకవేళ (null_సూచిక_constant)
	    {
	      rhs = null_సూచిక_కణుపు;
	      ఆపు;
	    }
	}

      ఒకవేళ (memb || marginal_memb)
	{
	  ఒకవేళ (!memb)
	    {
	      /* We have only a marginally acceptable member type;
		 it needs a warning.  */
	      వృక్షం ttl = వృక్షం_TYPE (వృక్షం_TYPE (marginal_memb));
	      వృక్షం ttr = వృక్షం_TYPE (rhstype);

	      /* Const and volatile mean something different for function
		 types, so the usual warnings are not appropriate.  */
	      ఒకవేళ (వృక్షం_సంకేతం (ttr) == FUNCTION_TYPE
		  && వృక్షం_సంకేతం (ttl) == FUNCTION_TYPE)
		{
		  /* Because const and volatile on functions are
		     restrictions that say the function will not do
		     certain things, it is okay to use a const or volatile
		     function where an ordinary one is wanted, but not
		     vice-versa.  */
		  ఒకవేళ (TYPE_QUALS_NO_ADDR_SPACE (ttl)
		      & ~TYPE_QUALS_NO_ADDR_SPACE (ttr))
		    PEDWARN_FOR_QUALIFIERS (location, సమాసం_loc,
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
	      లేకపోతే ఒకవేళ (TYPE_QUALS_NO_ADDR_SPACE (ttr)
		       & ~TYPE_QUALS_NO_ADDR_SPACE (ttl))
		PEDWARN_FOR_QUALIFIERS (location, సమాసం_loc,
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

	  ఒకవేళ (!fundecl || !DECL_లోపల_SYSTEM_శీర్షిక (fundecl))
	    pedwarn (location, OPT_Wpedantic,
		     "ISO C prohibits argument conversion to union type");

	  rhs = fold_convert_loc (location, వృక్షం_TYPE (memb), rhs);
	  తిరిగి build_constructor_single (type, memb, rhs);
	}
    }

  /* Conversions among pointers */
  లేకపోతే ఒకవేళ ((codel == సూచిక_TYPE || codel == REFERENCE_TYPE)
	   && (coder == codel))
    {
      /* If RHS refers to a built-in declared without a prototype
	 BLTIN is the declaration of the built-in with a prototype
	 and RHSTYPE is set to the actual type of the built-in.  */
      వృక్షం bltin;
      rhstype = type_or_builtin_type (rhs, &bltin);

      వృక్షం ttl = వృక్షం_TYPE (type);
      వృక్షం ttr = వృక్షం_TYPE (rhstype);
      తార్కిక is_opaque_సూచిక;
      తార్కిక లక్ష్యం_cmp = అబద్ధం;   /* Cache comp_target_types () result.  */
      addr_space_t asl;
      addr_space_t asr;

      వృక్షం mvl = remove_qualifiers (ttl);
      వృక్షం mvr = remove_qualifiers (ttr);

      /* Opaque pointers are treated like void pointers.  */
      is_opaque_సూచిక = సదిశ_targets_convertible_p (ttl, ttr);

      /* The Plan 9 compiler permits a pointer to a struct to be
	 automatically converted into a pointer to an anonymous field
	 within the struct.  */
      ఒకవేళ (flag_plan9_extensions
	  && రికార్డు_OR_UNION_TYPE_P (mvl)
	  && రికార్డు_OR_UNION_TYPE_P (mvr)
	  && mvl != mvr)
	{
	  వృక్షం new_rhs = convert_గమ్యం_anonymous_క్షేత్రం (location, type, rhs);
	  ఒకవేళ (new_rhs != NULL_వృక్షం)
	    {
	      rhs = new_rhs;
	      rhstype = వృక్షం_TYPE (rhs);
	      coder = వృక్షం_సంకేతం (rhstype);
	      ttr = వృక్షం_TYPE (rhstype);
	      mvr = TYPE_MAIN_VARIANT (ttr);
	    }
	}

      /* C++ does not allow the implicit conversion void* -> T*.  However,
	 for the purpose of reducing the number of false positives, we
	 tolerate the special case of

		int *p = NULL;

	 where NULL is typically defined in C to be '(void *) 0'.  */
      ఒకవేళ (VOID_TYPE_P (ttr) && rhs != null_సూచిక_కణుపు && !VOID_TYPE_P (ttl))
	warning_at (errtype == ic_argpass ? సమాసం_loc : location,
		    OPT_Wc___compat,
		    "request for implicit conversion "
		    "from %qT to %qT not permitted in C++", rhstype, type);

      /* Warn of new allocations that are not big enough for the target
	 type.  */
      ఒకవేళ (warn_alloc_కొలత && వృక్షం_సంకేతం (rhs) == CALL_సమాసం)
	ఒకవేళ (వృక్షం fndecl = get_callee_fndecl (rhs))
	  ఒకవేళ (DECL_IS_MALLOC (fndecl))
	    {
	      వృక్షం attrs = TYPE_లక్షణాలు (వృక్షం_TYPE (fndecl));
	      వృక్షం alloc_కొలత = lookup_attribute ("alloc_size", attrs);
	      ఒకవేళ (alloc_కొలత)
		warn_for_alloc_కొలత (location, ttl, rhs, alloc_కొలత);
	    }

      /* See if the pointers point to incompatible address spaces.  */
      asl = TYPE_ADDR_SPACE (ttl);
      asr = TYPE_ADDR_SPACE (ttr);
      ఒకవేళ (!null_సూచిక_constant_p (rhs)
	  && asr != asl && !targetm.addr_space.subset_p (asr, asl))
	{
	  auto_diagnostic_సమూహం d;
	  తార్కిక diagnosed = నిజం;
	  ఎంపిక (errtype)
	    {
	    స్థితి ic_argpass:
	      {
		స్థిరరాశి అక్షరం సందేశం_2[] = G_("passing argument %d of %qE from "
				      "pointer to non-enclosed address space");
		ఒకవేళ (warnopt)
		  diagnosed
		    = warning_at (సమాసం_loc, warnopt, సందేశం_2, parmnum, rname);
		లేకపోతే
		  error_at (సమాసం_loc, సందేశం_2, parmnum, rname);
	      ఆపు;
	      }
	    స్థితి ic_కేటాయించు:
	      {
		స్థిరరాశి అక్షరం సందేశం_2[] = G_("assignment from pointer to "
				      "non-enclosed address space");
		ఒకవేళ (warnopt)
		  diagnosed = warning_at (location, warnopt, సందేశం_2);
		లేకపోతే
		  error_at (location, సందేశం_2);
		ఆపు;
	      }
	    స్థితి ic_init:
	    స్థితి ic_init_const:
	      {
		స్థిరరాశి అక్షరం సందేశం_2[] = G_("initialization from pointer to "
				      "non-enclosed address space");
		ఒకవేళ (warnopt)
		  diagnosed = warning_at (location, warnopt, సందేశం_2);
		లేకపోతే
		  error_at (location, సందేశం_2);
		ఆపు;
	      }
	    స్థితి ic_return:
	      {
		స్థిరరాశి అక్షరం సందేశం_2[] = G_("return from pointer to "
				      "non-enclosed address space");
		ఒకవేళ (warnopt)
		  diagnosed = warning_at (location, warnopt, సందేశం_2);
		లేకపోతే
		  error_at (location, సందేశం_2);
		ఆపు;
	      }
	    అప్రమేయ:
	      gcc_unreachable ();
	    }
	  ఒకవేళ (diagnosed)
	    {
	      ఒకవేళ (errtype == ic_argpass)
		inform_for_arg (fundecl, సమాసం_loc, parmnum, type, rhstype);
	      లేకపోతే
		inform (location, "expected %qT but pointer is of type %qT",
			type, rhstype);
	    }
	  తిరిగి error_mark_కణుపు;
	}

      /* Check if the right-hand side has a format attribute but the
	 left-hand side doesn't.  */
      ఒకవేళ (warn_suggest_attribute_format
	  && check_missing_format_attribute (type, rhstype))
	{
	  ఎంపిక (errtype)
	  {
	  స్థితి ic_argpass:
	    warning_at (సమాసం_loc, OPT_Wsuggest_attribute_format,
			"argument %d of %qE might be "
			"a candidate for a format attribute",
			parmnum, rname);
	    ఆపు;
	  స్థితి ic_కేటాయించు:
	    warning_at (location, OPT_Wsuggest_attribute_format,
			"assignment left-hand side might be "
			"a candidate for a format attribute");
	    ఆపు;
	  స్థితి ic_init:
	  స్థితి ic_init_const:
	    warning_at (location, OPT_Wsuggest_attribute_format,
			"initialization left-hand side might be "
			"a candidate for a format attribute");
	    ఆపు;
	  స్థితి ic_return:
	    warning_at (location, OPT_Wsuggest_attribute_format,
			"return type might be "
			"a candidate for a format attribute");
	    ఆపు;
	  అప్రమేయ:
	    gcc_unreachable ();
	  }
	}

      /* See if the pointers point to incompatible scalar storage orders.  */
      ఒకవేళ (warn_scalar_storage_క్రమం
	  && !null_సూచిక_constant_p (rhs)
	  && (AGGREGATE_TYPE_P (ttl) && TYPE_తిరగేయి_STORAGE_క్రమం (ttl))
	     != (AGGREGATE_TYPE_P (ttr) && TYPE_తిరగేయి_STORAGE_క్రమం (ttr)))
	{
	  వృక్షం t;

	  ఎంపిక (errtype)
	  {
	  స్థితి ic_argpass:
	    /* Do not warn for built-in functions, for example memcpy, since we
	       control how they behave and they can be useful in this area.  */
	    ఒకవేళ (వృక్షం_సంకేతం (rname) != FUNCTION_DECL
		|| !fndecl_built_లోపల_p (rname))
	      warning_at (location, OPT_Wscalar_storage_క్రమం,
			  "passing argument %d of %qE from incompatible "
			  "scalar storage order", parmnum, rname);
	    ఆపు;
	  స్థితి ic_కేటాయించు:
	    /* Do not warn if the RHS is a call to a function that returns a
	       pointer that is not an alias.  */
	    ఒకవేళ (వృక్షం_సంకేతం (rhs) != CALL_సమాసం
		|| (t = get_callee_fndecl (rhs)) == NULL_వృక్షం
		|| !DECL_IS_MALLOC (t))
	      warning_at (location, OPT_Wscalar_storage_క్రమం,
			  "assignment to %qT from pointer type %qT with "
			  "incompatible scalar storage order", type, rhstype);
	    ఆపు;
	  స్థితి ic_init:
	  స్థితి ic_init_const:
	    /* Likewise.  */
	    ఒకవేళ (వృక్షం_సంకేతం (rhs) != CALL_సమాసం
		|| (t = get_callee_fndecl (rhs)) == NULL_వృక్షం
		|| !DECL_IS_MALLOC (t))
	      warning_at (location, OPT_Wscalar_storage_క్రమం,
			  "initialization of %qT from pointer type %qT with "
			  "incompatible scalar storage order", type, rhstype);
	    ఆపు;
	  స్థితి ic_return:
	    warning_at (location, OPT_Wscalar_storage_క్రమం,
			"returning %qT from pointer type with incompatible "
			"scalar storage order %qT", rhstype, type);
	    ఆపు;
	  అప్రమేయ:
	    gcc_unreachable ();
	  }
	}

      /* Any non-function converts to a [const][volatile] void *
	 and vice versa; otherwise, targets must be the same.
	 Meanwhile, the lhs target must have all the qualifiers of the rhs.  */
      ఒకవేళ ((VOID_TYPE_P (ttl) && !TYPE_ATOMIC (ttl))
	  || (VOID_TYPE_P (ttr) && !TYPE_ATOMIC (ttr))
	  || (లక్ష్యం_cmp = comp_లక్ష్యం_types (location, type, rhstype))
	  || is_opaque_సూచిక
	  || ((c_common_unsigned_type (mvl)
	       == c_common_unsigned_type (mvr))
	      && (c_common_signed_type (mvl)
		  == c_common_signed_type (mvr))
	      && TYPE_ATOMIC (mvl) == TYPE_ATOMIC (mvr)))
	{
	  /* Warn about loss of qualifers from pointers to arrays with
	     qualifiers on the element type. */
	  ఒకవేళ (వృక్షం_సంకేతం (ttr) == ARRAY_TYPE)
	    {
	      ttr = strip_array_types (ttr);
	      ttl = strip_array_types (ttl);

	      ఒకవేళ (TYPE_QUALS_NO_ADDR_SPACE_NO_ATOMIC (ttr)
		  & ~TYPE_QUALS_NO_ADDR_SPACE_NO_ATOMIC (ttl))
		WARNING_FOR_QUALIFIERS (flag_isoc23,
					location, సమాసం_loc,
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
          లేకపోతే ఒకవేళ (pedantic
	      && ((VOID_TYPE_P (ttl) && వృక్షం_సంకేతం (ttr) == FUNCTION_TYPE)
		  ||
		  (VOID_TYPE_P (ttr)
		   && !null_సూచిక_constant
		   && వృక్షం_సంకేతం (ttl) == FUNCTION_TYPE)))
	    PEDWARN_FOR_ASSIGNMENT (location, సమాసం_loc, OPT_Wpedantic,
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
	  లేకపోతే ఒకవేళ (వృక్షం_సంకేతం (ttr) != FUNCTION_TYPE
		   && వృక్షం_సంకేతం (ttl) != FUNCTION_TYPE)
	    {
	       /* Assignments between atomic and non-atomic objects are OK.  */
	       తార్కిక warn_quals_ped = TYPE_QUALS_NO_ADDR_SPACE_NO_ATOMIC (ttr)
				     & ~TYPE_QUALS_NO_ADDR_SPACE_NO_ATOMIC (ttl);
	       తార్కిక warn_quals = TYPE_QUALS_NO_ADDR_SPACE_NO_ATOMIC (ttr)
				 & ~TYPE_QUALS_NO_ADDR_SPACE_NO_ATOMIC (strip_array_types (ttl));

	      /* Don't warn about loss of qualifier for conversions from
		 qualified void* to pointers to arrays with corresponding
		 qualifier on the element type (except for pedantic before C23). */
	      ఒకవేళ (warn_quals || (warn_quals_ped && pedantic && !flag_isoc23))
		PEDWARN_FOR_QUALIFIERS (location, సమాసం_loc,
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
	      లేకపోతే ఒకవేళ (warn_quals_ped)
		pedwarn_c11 (location, OPT_Wc11_c23_compat,
			     "array with qualifier on the element is not qualified before C23");

	      /* If this is not a case of ignoring a mismatch in signedness,
		 no warning.  */
	      లేకపోతే ఒకవేళ (VOID_TYPE_P (ttl) || VOID_TYPE_P (ttr)
		       || లక్ష్యం_cmp)
		;
	      /* If there is a mismatch, do warn.  */
	      లేకపోతే ఒకవేళ (warn_సూచిక_sign)
		ఎంపిక (errtype)
		  {
		  స్థితి ic_argpass:
		    {
		      auto_diagnostic_సమూహం d;
		      range_label_for_type_mismatch rhs_label (rhstype, type);
		      gcc_rich_location richloc (సమాసం_loc, &rhs_label,
						 highlight_colors::actual);
		      ఒకవేళ (pedwarn (&richloc, OPT_Wpointer_sign,
				   "pointer targets in passing argument %d of "
				   "%qE differ in signedness", parmnum, rname))
			inform_for_arg (fundecl, సమాసం_loc, parmnum, type,
					rhstype);
		    }
		    ఆపు;
		  స్థితి ic_కేటాయించు:
		    pedwarn (location, OPT_Wpointer_sign,
			     "pointer targets in assignment from %qT to %qT "
			     "differ in signedness", rhstype, type);
		    ఆపు;
		  స్థితి ic_init:
		  స్థితి ic_init_const:
		    pedwarn_init (location, OPT_Wpointer_sign,
				  "pointer targets in initialization of %qT "
				  "from %qT differ in signedness", type,
				  rhstype);
		    ఆపు;
		  స్థితి ic_return:
		    pedwarn (location, OPT_Wpointer_sign, "pointer targets in "
			     "returning %qT from a function with return type "
			     "%qT differ in signedness", rhstype, type);
		    ఆపు;
		  అప్రమేయ:
		    gcc_unreachable ();
		  }
	    }
	  లేకపోతే ఒకవేళ (వృక్షం_సంకేతం (ttl) == FUNCTION_TYPE
		   && వృక్షం_సంకేతం (ttr) == FUNCTION_TYPE)
	    {
	      /* Because const and volatile on functions are restrictions
		 that say the function will not do certain things,
		 it is okay to use a const or volatile function
		 where an ordinary one is wanted, but not vice-versa.  */
	      ఒకవేళ (TYPE_QUALS_NO_ADDR_SPACE (ttl)
		  & ~TYPE_QUALS_NO_ADDR_SPACE (ttr))
		PEDWARN_FOR_QUALIFIERS (location, సమాసం_loc,
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
      లేకపోతే ఒకవేళ (!objc_ok)
	{
	  auto_diagnostic_సమూహం d;
	  తార్కిక warned = అబద్ధం;
	  pp_markup::element_expected_type e_type (type);
	  pp_markup::element_actual_type e_rhstype (rhstype);
	  ఎంపిక (errtype)
	    {
	    స్థితి ic_argpass:
	      {
		range_label_for_type_mismatch rhs_label (rhstype, type);
		gcc_rich_location richloc (సమాసం_loc, &rhs_label,
					   highlight_colors::actual);
		warned
		  = permerror_opt (&richloc, OPT_Wincompatible_సూచిక_types,
				   "passing argument %d of %qE from "
				   "incompatible pointer type",
				   parmnum, rname);
		ఒకవేళ (warned)
		  inform_for_arg (fundecl, సమాసం_loc, parmnum, type, rhstype);
	      }
	      ఆపు;
	    స్థితి ic_కేటాయించు:
	      ఒకవేళ (bltin)
		warned
		  = permerror_opt (location, OPT_Wincompatible_సూచిక_types,
				   "assignment to %e from pointer to "
				   "%qD with incompatible type %e",
				   &e_type, bltin, &e_rhstype);
	      లేకపోతే
		warned
		  = permerror_opt (location, OPT_Wincompatible_సూచిక_types,
				   "assignment to %e from incompatible "
				   "pointer type %e",
				   &e_type, &e_rhstype);
	      ఆపు;
	    స్థితి ic_init:
	    స్థితి ic_init_const:
	      ఒకవేళ (bltin)
		warned
		  = permerror_init (location, OPT_Wincompatible_సూచిక_types,
				    "initialization of %e from pointer to "
				    "%qD with incompatible type %e",
				    &e_type, bltin, &e_rhstype);
	      లేకపోతే
		warned
		  = permerror_init (location, OPT_Wincompatible_సూచిక_types,
				    "initialization of %e from incompatible "
				    "pointer type %e",
				    &e_type, &e_rhstype);
	      ఆపు;
	    స్థితి ic_return:
	      ఒకవేళ (bltin)
		warned
		  = permerror_opt (location, OPT_Wincompatible_సూచిక_types,
				   "returning pointer to %qD of type %e from "
				   "a function with incompatible type %e",
				   bltin, &e_rhstype, &e_type);
	      లేకపోతే
		warned
		  = permerror_opt (location, OPT_Wincompatible_సూచిక_types,
				   "returning %e from a function with "
				   "incompatible return type %e",
				   &e_rhstype, &e_type);
	      ఆపు;
	    అప్రమేయ:
	      gcc_unreachable ();
	    }
	  ఒకవేళ (warned)
	    {
	      /* If the mismatching function type is a pointer to a function,
		 try to show the decl of the function.  */
	      ఒకవేళ (వృక్షం_సంకేతం (rhs) == ADDR_సమాసం
		  && వృక్షం_సంకేతం (వృక్షం_నిర్వాహ్యం (rhs, 0)) == FUNCTION_DECL)
		{
		  వృక్షం rhs_fndecl = వృక్షం_నిర్వాహ్యం (rhs, 0);
		  ఒకవేళ (!DECL_IS_UNDECLARED_BUILTIN (rhs_fndecl))
		    {
		      gcc_rich_location richloc
			(DECL_ఆధారం_LOCATION (rhs_fndecl), శూన్యసూచిక,
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
      warn_for_చిరునామా_యొక్క_packed_member (type, orig_rhs);

      తిరిగి convert (type, rhs);
    }
  లేకపోతే ఒకవేళ (codel == సూచిక_TYPE && coder == ARRAY_TYPE)
    {
      /* ??? This should not be an error when inlining calls to
	 unprototyped functions.  */
      స్థిరరాశి అక్షరం సందేశం_2[] = "invalid use of non-lvalue array";
      ఒకవేళ (warnopt)
	warning_at (location, warnopt, సందేశం_2);
      లేకపోతే
	error_at (location, సందేశం_2);
      తిరిగి error_mark_కణుపు;
    }
  లేకపోతే ఒకవేళ (codel == సూచిక_TYPE
	   && (coder == INTEGER_TYPE
	       || coder == ENUMERAL_TYPE
	       || coder == BOOLEAN_TYPE
	       || coder == NULLPTR_TYPE
	       || coder == BITINT_TYPE))
    {
      ఒకవేళ (null_సూచిక_constant && c_inhibit_evaluation_warnings == 0
	  && coder != NULLPTR_TYPE)
	warning_at (location, OPT_Wzero_as_null_సూచిక_constant,
		    "zero as null pointer constant");
      /* A NULLPTR type is just a nullptr always.  */
      ఒకవేళ (coder == NULLPTR_TYPE)
	తిరిగి omit_one_నిర్వాహ్యం_loc (సమాసం_loc, type, nullptr_కణుపు, rhs);
      /* An explicit constant 0 or type nullptr_t can convert to a pointer,
	 or one that results from arithmetic, even including a cast to
	 integer type.  */
      లేకపోతే ఒకవేళ (!null_సూచిక_constant)
	ఎంపిక (errtype)
	  {
	  స్థితి ic_argpass:
	    {
	      auto_diagnostic_సమూహం d;
	      range_label_for_type_mismatch rhs_label (rhstype, type);
	      gcc_rich_location richloc (సమాసం_loc, &rhs_label,
					 highlight_colors::actual);
	      ఒకవేళ (permerror_opt (&richloc, OPT_Wint_conversion,
				 "passing argument %d of %qE makes pointer "
				 "from integer without a cast", parmnum, rname))
		{
		  maybe_emit_indirection_note (సమాసం_loc, rhs, type);
		  inform_for_arg (fundecl, సమాసం_loc, parmnum, type, rhstype);
		}
	    }
	    ఆపు;
	  స్థితి ic_కేటాయించు:
	    permerror_opt (location, OPT_Wint_conversion,
			   "assignment to %qT from %qT makes pointer from "
			   "integer without a cast", type, rhstype);
	    ఆపు;
	  స్థితి ic_init:
	  స్థితి ic_init_const:
	    permerror_init (location, OPT_Wint_conversion,
			    "initialization of %qT from %qT makes pointer "
			    "from integer without a cast", type, rhstype);
	    ఆపు;
	  స్థితి ic_return:
	    permerror_init (location, OPT_Wint_conversion,
			    "returning %qT from a function with return type "
			    "%qT makes pointer from integer without a cast",
			    rhstype, type);
	    ఆపు;
	  అప్రమేయ:
	    gcc_unreachable ();
	  }

      తిరిగి convert (type, rhs);
    }
  లేకపోతే ఒకవేళ ((codel == INTEGER_TYPE || codel == BITINT_TYPE)
	   && coder == సూచిక_TYPE)
    {
      ఎంపిక (errtype)
	{
	స్థితి ic_argpass:
	  {
	    auto_diagnostic_సమూహం d;
	    range_label_for_type_mismatch rhs_label (rhstype, type);
	    gcc_rich_location richloc (సమాసం_loc, &rhs_label,
				       highlight_colors::actual);
	    ఒకవేళ (permerror_opt (&richloc, OPT_Wint_conversion,
			       "passing argument %d of %qE makes integer from "
			       "pointer without a cast", parmnum, rname))
	      {
		maybe_emit_indirection_note (సమాసం_loc, rhs, type);
		inform_for_arg (fundecl, సమాసం_loc, parmnum, type, rhstype);
	      }
	  }
	  ఆపు;
	స్థితి ic_కేటాయించు:
	  permerror_opt (location, OPT_Wint_conversion,
			 "assignment to %qT from %qT makes integer from "
			 "pointer without a cast", type, rhstype);
	  ఆపు;
	స్థితి ic_init:
	స్థితి ic_init_const:
	  permerror_init (location, OPT_Wint_conversion,
			  "initialization of %qT from %qT makes integer "
			  "from pointer without a cast", type, rhstype);
	  ఆపు;
	స్థితి ic_return:
	  permerror_opt (location, OPT_Wint_conversion, "returning %qT from a "
			 "function with return type %qT makes integer from "
			 "pointer without a cast", rhstype, type);
	  ఆపు;
	అప్రమేయ:
	  gcc_unreachable ();
	}

      తిరిగి convert (type, rhs);
    }
  లేకపోతే ఒకవేళ (C_BOOLEAN_TYPE_P (type)
	   /* The type nullptr_t may be converted to bool.  The
	      result is false.  */
	   && (coder == సూచిక_TYPE || coder == NULLPTR_TYPE))
    {
      వృక్షం ret;
      తార్కిక save = లోపల_late_ద్విమాన_op;
      లోపల_late_ద్విమాన_op = నిజం;
      ret = convert (type, rhs);
      లోపల_late_ద్విమాన_op = save;
      తిరిగి ret;
    }
  లేకపోతే ఒకవేళ (codel == NULLPTR_TYPE && null_సూచిక_constant)
    తిరిగి convert (type, rhs);

  ఎంపిక (errtype)
    {
    స్థితి ic_argpass:
      {
	auto_diagnostic_సమూహం d;
	range_label_for_type_mismatch rhs_label (rhstype, type);
	gcc_rich_location richloc (సమాసం_loc, &rhs_label,
				   highlight_colors::actual);
	స్థిరరాశి అక్షరం సందేశం_2[] = G_("incompatible type for argument %d of %qE");
	ఒకవేళ (warnopt)
	  warning_at (సమాసం_loc, warnopt, సందేశం_2, parmnum, rname);
	లేకపోతే
	  error_at (&richloc, సందేశం_2, parmnum, rname);
	inform_for_arg (fundecl, సమాసం_loc, parmnum, type, rhstype);
      }
      ఆపు;
    స్థితి ic_కేటాయించు:
      {
	స్థిరరాశి అక్షరం సందేశం_2[]
	  = G_("incompatible types when assigning to type %qT from type %qT");
	ఒకవేళ (warnopt)
	  warning_at (సమాసం_loc, 0, సందేశం_2, type, rhstype);
	లేకపోతే
	  error_at (సమాసం_loc, సందేశం_2, type, rhstype);
	ఆపు;
      }
    స్థితి ic_init:
    స్థితి ic_init_const:
      {
	స్థిరరాశి అక్షరం సందేశం_2[]
	  = G_("incompatible types when initializing type %qT using type %qT");
	ఒకవేళ (warnopt)
	  warning_at (location, 0, సందేశం_2, type, rhstype);
	లేకపోతే
	  error_at (location, సందేశం_2, type, rhstype);
	ఆపు;
      }
    స్థితి ic_return:
      {
	స్థిరరాశి అక్షరం సందేశం_2[]
	  = G_("incompatible types when returning type %qT but %qT was expected");
	ఒకవేళ (warnopt)
	  warning_at (location, 0, సందేశం_2, rhstype, type);
	లేకపోతే
	  error_at (location, సందేశం_2, rhstype, type);
	ఆపు;
      }
    అప్రమేయ:
      gcc_unreachable ();
    }

  తిరిగి error_mark_కణుపు;
}

/* If VALUE is a compound expr all of whose expressions are constant, then
   return its value.  Otherwise, return error_mark_node.

   This is for handling COMPOUND_EXPRs as initializer elements
   which is allowed with a warning when -pedantic is specified.  */

స్థిర వృక్షం
valid_compound_సమాసం_initializer (వృక్షం విలువ, వృక్షం endtype)
{
  ఒకవేళ (వృక్షం_సంకేతం (విలువ) == COMPOUND_సమాసం)
    {
      ఒకవేళ (valid_compound_సమాసం_initializer (వృక్షం_నిర్వాహ్యం (విలువ, 0), endtype)
	  == error_mark_కణుపు)
	తిరిగి error_mark_కణుపు;
      తిరిగి valid_compound_సమాసం_initializer (వృక్షం_నిర్వాహ్యం (విలువ, 1),
					      endtype);
    }
  లేకపోతే ఒకవేళ (!initializer_constant_valid_p (విలువ, endtype))
    తిరిగి error_mark_కణుపు;
  లేకపోతే
    తిరిగి విలువ;
}

/* Perform appropriate conversions on the initial value of a variable,
   store it in the declaration DECL,
   and print any error messages that are appropriate.
   If ORIGTYPE is not NULL_TREE, it is the original type of INIT.
   If the init is invalid, store an ERROR_MARK.

   INIT_LOC is the location of the initial value.  */

శూన్య
store_init_విలువ (location_t init_loc, వృక్షం decl, వృక్షం init, వృక్షం origtype)
{
  వృక్షం విలువ, type;
  తార్కిక npc = అబద్ధం;
  తార్కిక int_const_సమాసం = అబద్ధం;
  తార్కిక arith_const_సమాసం = అబద్ధం;

  /* If variable's type was invalidly declared, just ignore it.  */

  type = వృక్షం_TYPE (decl);
  ఒకవేళ (వృక్షం_సంకేతం (type) == ERROR_MARK)
    తిరిగి;

  /* Digest the specified initializer into an expression.  */

  ఒకవేళ (init)
    {
      npc = null_సూచిక_constant_p (init);
      int_const_సమాసం = (వృక్షం_సంకేతం (init) == INTEGER_CST
			&& !వృక్షం_అధికప్రవాహం (init)
			&& INTEGRAL_TYPE_P (వృక్షం_TYPE (init)));
      /* Not fully determined before folding.  */
      arith_const_సమాసం = నిజం;
    }
  తార్కిక constexpr_p = (VAR_P (decl)
		      && C_DECL_DECLARED_CONSTEXPR (decl));
  విలువ = digest_init (init_loc, decl, type, init, origtype, npc,
		       int_const_సమాసం, arith_const_సమాసం, నిజం,
		       వృక్షం_STATIC (decl) || constexpr_p, constexpr_p);

  /* Store the expression if valid; else report error.  */

  ఒకవేళ (!లోపల_system_శీర్షిక_at (ఆదానం_location)
      && AGGREGATE_TYPE_P (వృక్షం_TYPE (decl)) && !వృక్షం_STATIC (decl))
    warning (OPT_Wtraditional, "traditional C rejects automatic "
	     "aggregate initialization");

  ఒకవేళ (విలువ != error_mark_కణుపు || వృక్షం_సంకేతం (decl) != FUNCTION_DECL)
    DECL_INITIAL (decl) = విలువ;

  /* ANSI wants warnings about out-of-range constant initializers.  */
  STRIP_TYPE_NOPS (విలువ);
  ఒకవేళ (వృక్షం_STATIC (decl))
    constant_వ్యక్తీకరణ_warning (విలువ);

  /* Check if we need to set array size from compound literal size.  */
  ఒకవేళ (వృక్షం_సంకేతం (type) == ARRAY_TYPE
      && TYPE_DOMAIN (type) == NULL_వృక్షం
      && విలువ != error_mark_కణుపు)
    {
      వృక్షం inside_init = init;

      STRIP_TYPE_NOPS (inside_init);
      inside_init = fold (inside_init);

      ఒకవేళ (వృక్షం_సంకేతం (inside_init) == COMPOUND_LITERAL_సమాసం)
	{
	  వృక్షం cldecl = COMPOUND_LITERAL_సమాసం_DECL (inside_init);

	  ఒకవేళ (TYPE_DOMAIN (వృక్షం_TYPE (cldecl)))
	    {
	      /* For int foo[] = (int [3]){1}; we need to set array size
		 now since later on array initializer will be just the
		 brace enclosed list of the compound literal.  */
	      వృక్షం etype = strip_array_types (వృక్షం_TYPE (decl));
	      type = build_distinct_type_copy (TYPE_MAIN_VARIANT (type));
	      TYPE_DOMAIN (type) = TYPE_DOMAIN (వృక్షం_TYPE (cldecl));
	      layout_type (type);
	      layout_decl (cldecl, 0);
	      వృక్షం_TYPE (decl)
		= c_build_qualified_type (type, TYPE_QUALS (etype));
	    }
	}
    }
}

/* Methods for storing and printing names for error messages.  */

/* Implement a spelling stack that allows components of a name to be pushed
   and popped.  Each element on the stack is this structure.  */

నిర్మాణం spelling
{
  పూర్ణాంకం రకం;
  సంఘం
    {
      గుర్తులేని HOST_WIDE_INT i;
      స్థిరరాశి అక్షరం *s;
    } u;
};

#నిర్వచించు SPELLING_STRING 1
#నిర్వచించు SPELLING_MEMBER 2
#నిర్వచించు SPELLING_BOUNDS 3

స్థిర నిర్మాణం spelling *spelling;	/* Next stack element (unused).  */
స్థిర నిర్మాణం spelling *spelling_పునాది;	/* Spelling stack base.  */
స్థిర పూర్ణాంకం spelling_కొలత;		/* Size of the spelling stack.  */

/* Macros to save and restore the spelling stack around push_... functions.
   Alternative to SAVE_SPELLING_STACK.  */

#నిర్వచించు SPELLING_లోతు() (spelling - spelling_పునాది)
#నిర్వచించు RESTORE_SPELLING_లోతు(లోతు_2) (spelling = spelling_పునాది + (లోతు_2))

/* Push an element on the spelling stack with type KIND and assign VALUE
   to MEMBER.  */

#నిర్వచించు నెట్టు_SPELLING(రకం_2, విలువ_2, MEMBER)				\
{									\
  పూర్ణాంకం లోతు = SPELLING_లోతు ();					\
									\
  ఒకవేళ (లోతు >= spelling_కొలత)						\
    {									\
      spelling_కొలత += 10;						\
      spelling_పునాది = XRESIZEVEC (నిర్మాణం spelling, spelling_పునాది,	\
				  spelling_కొలత);			\
      RESTORE_SPELLING_లోతు (లోతు);					\
    }									\
									\
  spelling->రకం = (రకం_2);						\
  spelling->MEMBER = (విలువ_2);						\
  spelling++;								\
}

/* Push STRING on the stack.  Printed literally.  */

స్థిర శూన్య
నెట్టు_string (స్థిరరాశి అక్షరం *string)
{
  నెట్టు_SPELLING (SPELLING_STRING, string, u.s);
}

/* Push a member name on the stack.  Printed as '.' STRING.  */

స్థిర శూన్య
నెట్టు_member_name (వృక్షం decl)
{
  స్థిరరాశి అక్షరం *స్థిరరాశి string
    = (DECL_NAME (decl)
       ? identifier_గమ్యం_locale (IDENTIFIER_సూచిక (DECL_NAME (decl)))
       : _("<anonymous>"));
  నెట్టు_SPELLING (SPELLING_MEMBER, string, u.s);
}

/* Push an array bounds on the stack.  Printed as [BOUNDS].  */

స్థిర శూన్య
నెట్టు_array_bounds (గుర్తులేని HOST_WIDE_INT bounds)
{
  నెట్టు_SPELLING (SPELLING_BOUNDS, bounds, u.i);
}

/* Compute the maximum size in bytes of the printed spelling.  */

స్థిర పూర్ణాంకం
spelling_నిడివి (శూన్య)
{
  పూర్ణాంకం కొలత = 0;
  నిర్మాణం spelling *p;

  కొరకు (p = spelling_పునాది; p < spelling; p++)
    {
      ఒకవేళ (p->రకం == SPELLING_BOUNDS)
	కొలత += 25;
      లేకపోతే
	కొలత += అక్షరశ్రేణి_పొడవు (p->u.s) + 1;
    }

  తిరిగి కొలత;
}

/* Print the spelling to BUFFER and return it.  */

స్థిర అక్షరం *
print_spelling (అక్షరం *బఫరు)
{
  అక్షరం *d = బఫరు;
  నిర్మాణం spelling *p;

  కొరకు (p = spelling_పునాది; p < spelling; p++)
    ఒకవేళ (p->రకం == SPELLING_BOUNDS)
      {
	sprintf (d, "[" HOST_WIDE_INT_PRINT_UNSIGNED "]", p->u.i);
	d += అక్షరశ్రేణి_పొడవు (d);
      }
    లేకపోతే
      {
	స్థిరరాశి అక్షరం *s;
	ఒకవేళ (p->రకం == SPELLING_MEMBER)
	  *d++ = '.';
	కొరకు (s = p->u.s; (*d = *s++); d++)
	  ;
      }
  *d++ = '\0';
  తిరిగి బఫరు;
}

/* Check whether INIT, a floating or integer constant, is
   representable in TYPE, a real floating type with the same radix or
   a decimal floating type initialized with a binary floating
   constant.  Return true if OK, false if not.  */
స్థిర తార్కిక
constexpr_init_సరిపోతుంది_real_type (వృక్షం type, వృక్షం init)
{
  gcc_assert (SCALAR_FLOAT_TYPE_P (type));
  gcc_assert (వృక్షం_సంకేతం (init) == INTEGER_CST || వృక్షం_సంకేతం (init) == REAL_CST);
  ఒకవేళ (వృక్షం_సంకేతం (init) == REAL_CST
      && TYPE_బహుళకం (వృక్షం_TYPE (init)) == TYPE_బహుళకం (type))
    {
      /* Same mode, no conversion required except for the case of
	 signaling NaNs if the types are incompatible (e.g. double and
	 long double with the same mode).  */
      ఒకవేళ (REAL_విలువ_ISSIGNALING_NAN (వృక్షం_REAL_CST (init))
	  && !comptypes (TYPE_MAIN_VARIANT (type),
			 TYPE_MAIN_VARIANT (వృక్షం_TYPE (init))))
	తిరిగి అబద్ధం;
      తిరిగి నిజం;
    }
  ఒకవేళ (వృక్షం_సంకేతం (init) == INTEGER_CST)
    {
      వృక్షం converted = build_real_from_int_cst (type, init);
      తార్కిక fail = అబద్ధం;
      wide_int w = real_గమ్యం_integer (&వృక్షం_REAL_CST (converted), &fail,
				    TYPE_PRECISION (వృక్షం_TYPE (init)));
      తిరిగి !fail && wi::eq_p (w, wi::గమ్యం_wide (init));
    }
  ఒకవేళ (REAL_విలువ_ISSIGNALING_NAN (వృక్షం_REAL_CST (init)))
    తిరిగి అబద్ధం;
  ఒకవేళ ((REAL_విలువ_ISINF (వృక్షం_REAL_CST (init))
       && బహుళకం_HAS_INFINITIES (TYPE_బహుళకం (type)))
      || (REAL_విలువ_ISNAN (వృక్షం_REAL_CST (init))
	  && బహుళకం_HAS_NANS (TYPE_బహుళకం (type))))
    తిరిగి నిజం;
  ఒకవేళ (DECIMAL_FLOAT_TYPE_P (type)
      && !DECIMAL_FLOAT_TYPE_P (వృక్షం_TYPE (init)))
    {
      /* This is valid if the real number represented by the
	 initializer can be exactly represented in the decimal
	 type.  Compare the values using MPFR.  */
      REAL_విలువ_TYPE t;
      real_convert (&t, TYPE_బహుళకం (type), &వృక్షం_REAL_CST (init));
      mpfr_t bin_val, dec_val;
      mpfr_init2 (bin_val, REAL_బహుళకం_FORMAT (TYPE_బహుళకం (వృక్షం_TYPE (init)))->p);
      mpfr_init2 (dec_val, REAL_బహుళకం_FORMAT (TYPE_బహుళకం (వృక్షం_TYPE (init)))->p);
      mpfr_from_real (bin_val, &వృక్షం_REAL_CST (init), MPFR_RNDN);
      అక్షరం string[256];
      real_గమ్యం_decimal (string, &t, పరిమాణం string, 0, 1);
      తార్కిక res = (mpfr_strtofr (dec_val, string, ఖాళీ, 10, MPFR_RNDN) == 0
		  && mpfr_equal_p (bin_val, dec_val));
      mpfr_clear (bin_val);
      mpfr_clear (dec_val);
      తిరిగి res;
    }
  /* exact_real_truncate is not quite right here, since it doesn't
     allow even an exact conversion to subnormal values.  */
  REAL_విలువ_TYPE t;
  real_convert (&t, TYPE_బహుళకం (type), &వృక్షం_REAL_CST (init));
  తిరిగి real_identical (&t, &వృక్షం_REAL_CST (init));
}

/* Check whether INIT (location LOC) is valid as a 'constexpr'
   initializer for type TYPE, and give an error if not.  INIT has
   already been folded and verified to be constant.  INT_CONST_EXPR
   and ARITH_CONST_EXPR say whether it is an integer constant
   expression or arithmetic constant expression, respectively.  If
   TYPE is not a scalar type, this function does nothing.  */

స్థిర శూన్య
check_constexpr_init (location_t loc, వృక్షం type, వృక్షం init,
		      తార్కిక int_const_సమాసం, తార్కిక arith_const_సమాసం)
{
  ఒకవేళ (సూచిక_TYPE_P (type))
    {
      /* The initializer must be null.  */
      ఒకవేళ (వృక్షం_సంకేతం (init) != INTEGER_CST || !integer_zerop (init))
	error_at (loc, "%<constexpr%> pointer initializer is not null");
      తిరిగి;
    }
  ఒకవేళ (INTEGRAL_TYPE_P (type))
    {
      /* The initializer must be an integer constant expression,
	 representable in the target type.  */
      ఒకవేళ (!int_const_సమాసం)
	{
	  ఒకవేళ (వృక్షం_సంకేతం (init) == RAW_దత్తాంశం_CST
	      && TYPE_PRECISION (type) == CHAR_బిట్టు)
	    {
	      ఒకవేళ (!TYPE_UNSIGNED (type))
		కొరకు (గుర్తులేని పూర్ణాంకం i = 0;
		     i < (గుర్తులేని) RAW_దత్తాంశం_నిడివి (init); ++i)
		  ఒకవేళ (RAW_దత్తాంశం_SCHAR_ELT (init, i) < 0)
		    {
		      error_at (loc, "%<constexpr%> initializer not "
				"representable in type of object");
		      ఆపు;
		    }
	    }
	  లేకపోతే
	    error_at (loc, "%<constexpr%> integer initializer is not an "
		      "integer constant expression");
	}
      లేకపోతే ఒకవేళ (!int_సరిపోతుంది_type_p (init, type))
	error_at (loc, "%<constexpr%> initializer not representable in "
		  "type of object");
      తిరిగి;
    }
  /* We don't apply any extra checks to extension types such as vector
     or fixed-point types.  */
  ఒకవేళ (వృక్షం_సంకేతం (type) != REAL_TYPE && వృక్షం_సంకేతం (type) != COMPLEX_TYPE)
    తిరిగి;
  ఒకవేళ (!arith_const_సమాసం)
    {
      error_at (loc, "%<constexpr%> initializer is not an arithmetic "
		"constant expression");
      తిరిగి;
    }
  /* We don't apply any extra checks to complex integers.  */
  ఒకవేళ (వృక్షం_సంకేతం (type) == COMPLEX_TYPE
      && వృక్షం_సంకేతం (వృక్షం_TYPE (type)) != REAL_TYPE)
    తిరిగి;
  /* Following N3082, a real type cannot be initialized from a complex
     type and a binary type cannot be initialized from a decimal type
     (but initializing a decimal type from a binary type is OK).
     Signaling NaN initializers are OK only if the types are
     compatible (not just the same mode); all quiet NaN and infinity
     initializations are considered to preserve the value.  */
  ఒకవేళ (వృక్షం_సంకేతం (వృక్షం_TYPE (init)) == COMPLEX_TYPE
      && SCALAR_FLOAT_TYPE_P (type))
    {
      error_at (loc, "%<constexpr%> initializer for a real type is of "
		"complex type");
      తిరిగి;
    }
  ఒకవేళ (SCALAR_FLOAT_TYPE_P (type)
      && SCALAR_FLOAT_TYPE_P (వృక్షం_TYPE (init))
      && DECIMAL_FLOAT_TYPE_P (వృక్షం_TYPE (init))
      && !DECIMAL_FLOAT_TYPE_P (type))
    {
      error_at (loc, "%<constexpr%> initializer for a binary "
		"floating-point type is of decimal type");
      తిరిగి;
    }
  తార్కిక సరిపోతుంది;
  ఒకవేళ (వృక్షం_సంకేతం (type) == COMPLEX_TYPE)
    {
      ఎంపిక (వృక్షం_సంకేతం (init))
	{
	స్థితి INTEGER_CST:
	స్థితి REAL_CST:
	  సరిపోతుంది = constexpr_init_సరిపోతుంది_real_type (వృక్షం_TYPE (type), init);
	  ఆపు;
	స్థితి COMPLEX_CST:
	  సరిపోతుంది = (constexpr_init_సరిపోతుంది_real_type (వృక్షం_TYPE (type),
						 వృక్షం_REALPART (init))
		  && constexpr_init_సరిపోతుంది_real_type (వృక్షం_TYPE (type),
						    వృక్షం_IMAGPART (init)));
	  ఆపు;
	అప్రమేయ:
	  gcc_unreachable ();
	}
    }
  లేకపోతే
    సరిపోతుంది = constexpr_init_సరిపోతుంది_real_type (type, init);
  ఒకవేళ (!సరిపోతుంది)
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

స్థిర వృక్షం
digest_init (location_t init_loc, వృక్షం decl, వృక్షం type, వృక్షం init,
	     వృక్షం origtype, తార్కిక null_సూచిక_constant, తార్కిక int_const_సమాసం,
	     తార్కిక arith_const_సమాసం, తార్కిక strict_string,
	     తార్కిక require_constant, తార్కిక require_constexpr)
{
  గణన వృక్షం_సంకేతం_2 సంకేతం_2 = వృక్షం_సంకేతం (type);
  వృక్షం inside_init = init;
  వృక్షం semantic_type = NULL_వృక్షం;
  తార్కిక maybe_const = నిజం;

  ఒకవేళ (type == error_mark_కణుపు
      || !init
      || error_నిర్వాహ్యం_p (init))
    తిరిగి error_mark_కణుపు;

  STRIP_TYPE_NOPS (inside_init);

  /* If require_constant is TRUE,  when the initializer is a call to
     .ACCESS_WITH_SIZE, use the first argument as the initializer.
     For example:
     y = (char *) .ACCESS_WITH_SIZE ((char *) &static_annotated.c,...)
     will be converted to
     y = &static_annotated.c.  */

  ఒకవేళ (require_constant
      && వృక్షం_సంకేతం (inside_init) == NOP_సమాసం
      && వృక్షం_సంకేతం (వృక్షం_నిర్వాహ్యం (inside_init, 0)) == CALL_సమాసం
      && is_access_with_కొలత_p (వృక్షం_నిర్వాహ్యం (inside_init, 0)))
    inside_init
      = get_ref_from_access_with_కొలత (వృక్షం_నిర్వాహ్యం (inside_init, 0));

  ఒకవేళ (!c_లోపల_omp_for)
    {
      ఒకవేళ (వృక్షం_సంకేతం (inside_init) == EXCESS_PRECISION_సమాసం)
	{
	  semantic_type = వృక్షం_TYPE (inside_init);
	  inside_init = వృక్షం_నిర్వాహ్యం (inside_init, 0);
	}
      inside_init = c_fully_fold (inside_init, require_constant, &maybe_const);
    }
  /* TODO: this may not detect all cases of expressions folding to
     constants that are not arithmetic constant expressions.  */
  ఒకవేళ (!maybe_const)
    arith_const_సమాసం = అబద్ధం;
  లేకపోతే ఒకవేళ (!INTEGRAL_TYPE_P (వృక్షం_TYPE (inside_init))
	   && వృక్షం_సంకేతం (వృక్షం_TYPE (inside_init)) != REAL_TYPE
	   && వృక్షం_సంకేతం (వృక్షం_TYPE (inside_init)) != COMPLEX_TYPE)
    arith_const_సమాసం = అబద్ధం;
  లేకపోతే ఒకవేళ (వృక్షం_సంకేతం (inside_init) != INTEGER_CST
	   && వృక్షం_సంకేతం (inside_init) != REAL_CST
	   && వృక్షం_సంకేతం (inside_init) != COMPLEX_CST
	   && వృక్షం_సంకేతం (inside_init) != RAW_దత్తాంశం_CST)
    arith_const_సమాసం = అబద్ధం;
  లేకపోతే ఒకవేళ (వృక్షం_అధికప్రవాహం (inside_init))
    arith_const_సమాసం = అబద్ధం;

  /* Initialization of an array of chars from a string constant
     optionally enclosed in braces.  */

  ఒకవేళ (సంకేతం_2 == ARRAY_TYPE && inside_init
      && వృక్షం_సంకేతం (inside_init) == STRING_CST)
    {
      వృక్షం typ1
	= (TYPE_ATOMIC (వృక్షం_TYPE (type))
	   ? c_build_qualified_type (TYPE_MAIN_VARIANT (వృక్షం_TYPE (type)),
				     TYPE_QUAL_ATOMIC)
	   : TYPE_MAIN_VARIANT (వృక్షం_TYPE (type)));
      /* Note that an array could be both an array of character type
	 and an array of wchar_t if wchar_t is signed char or unsigned
	 char.  */
      తార్కిక char_array = (typ1 == char_type_కణుపు
			 || typ1 == signed_char_type_కణుపు
			 || typ1 == unsigned_char_type_కణుపు);
      తార్కిక wchar_array = comptypes (typ1, wchar_type_కణుపు);
      తార్కిక char16_array = comptypes (typ1, char16_type_కణుపు);
      తార్కిక char32_array = comptypes (typ1, char32_type_కణుపు);

      ఒకవేళ (char_array || wchar_array || char16_array || char32_array)
	{
	  నిర్మాణం c_సమాసం సమాసం;
	  వృక్షం typ2 = TYPE_MAIN_VARIANT (వృక్షం_TYPE (వృక్షం_TYPE (inside_init)));
	  తార్కిక incompat_string_cst = అబద్ధం;
	  సమాసం.విలువ = inside_init;
	  సమాసం.original_సంకేతం = (strict_string ? STRING_CST : ERROR_MARK);
	  సమాసం.original_type = ఖాళీ;
	  సమాసం.m_decimal = 0;
	  maybe_warn_string_init (init_loc, type, సమాసం);

	  ఒకవేళ (flexible_array_member_type_p (type))
	    pedwarn_init (init_loc, OPT_Wpedantic,
			  "initialization of a flexible array member");

	  ఒకవేళ (comptypes (TYPE_MAIN_VARIANT (వృక్షం_TYPE (inside_init)),
			 TYPE_MAIN_VARIANT (type)))
	    తిరిగి inside_init;

	  ఒకవేళ (char_array)
	    {
	      ఒకవేళ (typ2 != char_type_కణుపు && typ2 != char8_type_కణుపు)
		incompat_string_cst = నిజం;
	    }
	  లేకపోతే ఒకవేళ (!comptypes (typ1, typ2))
	    incompat_string_cst = నిజం;

          ఒకవేళ (incompat_string_cst)
            {
	      error_init (init_loc, "cannot initialize array of %qT from "
			  "a string literal with type array of %qT",
			  typ1, typ2);
	      తిరిగి error_mark_కణుపు;
            }

	  ఒకవేళ (require_constexpr
	      && TYPE_UNSIGNED (typ1) != TYPE_UNSIGNED (typ2))
	    {
	      /* Check if all characters of the string can be
		 represented in the type of the constexpr object being
		 initialized.  */
	      గుర్తులేని HOST_WIDE_INT len = వృక్షం_STRING_నిడివి (inside_init);
	      స్థిరరాశి గుర్తులేని అక్షరం *p =
		(స్థిరరాశి గుర్తులేని అక్షరం *) వృక్షం_STRING_సూచిక (inside_init);
	      gcc_assert (CHAR_TYPE_కొలత == 8 && CHAR_బిట్టు == 8);
	      కొరకు (గుర్తులేని i = 0; i < len; i++)
		ఒకవేళ (p[i] > 127)
		  {
		    error_init (init_loc, "%<constexpr%> initializer not "
				"representable in type of object");
		    ఆపు;
		  }
	    }

	  ఒకవేళ (TYPE_DOMAIN (type) != NULL_వృక్షం
	      && TYPE_కొలత (type) != NULL_వృక్షం
	      && వృక్షం_సంకేతం (TYPE_కొలత (type)) == INTEGER_CST)
	    {
	      గుర్తులేని HOST_WIDE_INT len = వృక్షం_STRING_నిడివి (inside_init);

	      ఒకవేళ (compare_వృక్షం_int (TYPE_కొలత_UNIT (type), len) < 0)
		{
		  గుర్తులేని HOST_WIDE_INT avail
		    = వృక్షం_గమ్యం_uhwi (TYPE_కొలత_UNIT (type));
		  గుర్తులేని unit = TYPE_PRECISION (typ1) / బిట్లు_చొప్పున_UNIT;
		  స్థిరరాశి అక్షరం *p = వృక్షం_STRING_సూచిక (inside_init);

		  /* Construct truncated string.  */
		  inside_init = build_string (avail, p);

		  /* Subtract the size of a single (possibly wide) character
		     because it may be ok to ignore the terminating NUL char
		     that is counted in the length of the constant.  */
		  ఒకవేళ (len - unit > avail)
		    pedwarn_init (init_loc, 0,
				  "initializer-string for array of %qT "
				  "is too long (%wu chars into %wu "
				  "available)", typ1, len, avail);
		  లేకపోతే ఒకవేళ (warn_cxx_compat)
		    warning_at (init_loc, OPT_Wc___compat,
				"initializer-string for array of %qT "
				"is too long for C++ (%wu chars into %wu "
				"available)", typ1, len, avail);
		  లేకపోతే ఒకవేళ (warn_unterminated_string_initialization
			   && get_attr_nonstring_decl (decl) == NULL_వృక్షం)
		    warning_at (init_loc,
				OPT_Wunterminated_string_initialization,
				"initializer-string for array of %qT "
				"truncates NUL terminator but destination "
				"lacks %qs attribute (%wu chars into %wu "
				"available)", typ1, "nonstring", len, avail);
		}
	    }

	  వృక్షం_TYPE (inside_init) = type;
	  తిరిగి inside_init;
	}
      లేకపోతే ఒకవేళ (INTEGRAL_TYPE_P (typ1))
	{
	  error_init (init_loc, "array of inappropriate type initialized "
		      "from string constant");
	  తిరిగి error_mark_కణుపు;
	}
    }

  /* Build a VECTOR_CST from a *constant* vector constructor.  If the
     vector constructor is not constant (e.g. {1,2,3,foo()}) then punt
     below and handle as a constructor.  */
  ఒకవేళ (సంకేతం_2 == సదిశ_TYPE
      && సదిశ_TYPE_P (వృక్షం_TYPE (inside_init))
      && సదిశ_types_convertible_p (వృక్షం_TYPE (inside_init), type, నిజం)
      && వృక్షం_CONSTANT (inside_init))
    {
      ఒకవేళ (వృక్షం_సంకేతం (inside_init) == సదిశ_CST
	  && comptypes (TYPE_MAIN_VARIANT (వృక్షం_TYPE (inside_init)),
			TYPE_MAIN_VARIANT (type)))
	తిరిగి inside_init;

      ఒకవేళ (వృక్షం_సంకేతం (inside_init) == CONSTRUCTOR)
	{
	  గుర్తులేని HOST_WIDE_INT ix;
	  వృక్షం విలువ;
	  తార్కిక constant_p = నిజం;

	  /* Iterate through elements and check if all constructor
	     elements are *_CSTs.  */
	  FOR_EACH_CONSTRUCTOR_విలువ (CONSTRUCTOR_ELTS (inside_init), ix, విలువ)
	    ఒకవేళ (!CONSTANT_CLASS_P (విలువ))
	      {
		constant_p = అబద్ధం;
		ఆపు;
	      }

	  ఒకవేళ (constant_p)
	    తిరిగి build_సదిశ_from_ctor (type,
					   CONSTRUCTOR_ELTS (inside_init));
	}
    }

  ఒకవేళ (warn_sequence_బిందువు)
    verify_sequence_points (inside_init);

  /* Any type can be initialized
     from an expression of the same type, optionally with braces.  */

  ఒకవేళ (inside_init && వృక్షం_TYPE (inside_init) != NULL_వృక్షం
      && (comptypes (TYPE_MAIN_VARIANT (వృక్షం_TYPE (inside_init)),
		     TYPE_MAIN_VARIANT (type))
	  || (సంకేతం_2 == ARRAY_TYPE
	      && comptypes (వృక్షం_TYPE (inside_init), type))
	  || (gnu_సదిశ_type_p (type)
	      && comptypes (వృక్షం_TYPE (inside_init), type))
	  || (సంకేతం_2 == సూచిక_TYPE
	      && వృక్షం_సంకేతం (వృక్షం_TYPE (inside_init)) == ARRAY_TYPE
	      && comptypes (వృక్షం_TYPE (వృక్షం_TYPE (inside_init)),
			    వృక్షం_TYPE (type)))))
    {
      ఒకవేళ (సంకేతం_2 == సూచిక_TYPE)
	{
	  ఒకవేళ (వృక్షం_సంకేతం (వృక్షం_TYPE (inside_init)) == ARRAY_TYPE)
	    {
	      ఒకవేళ (వృక్షం_సంకేతం (inside_init) == STRING_CST
		  || వృక్షం_సంకేతం (inside_init) == COMPOUND_LITERAL_సమాసం)
		inside_init = array_గమ్యం_సూచిక_conversion
		  (init_loc, inside_init);
	      లేకపోతే
		{
		  error_init (init_loc, "invalid use of non-lvalue array");
		  తిరిగి error_mark_కణుపు;
		}
	    }
	}

      ఒకవేళ (సంకేతం_2 == సదిశ_TYPE || c_hardbool_type_attr (type))
	/* Although the types are compatible, we may require a
	   conversion.  */
	inside_init = convert (type, inside_init);

      ఒకవేళ ((సంకేతం_2 == రికార్డు_TYPE || సంకేతం_2 == UNION_TYPE)
	  && !comptypes (TYPE_MAIN_VARIANT (type), TYPE_MAIN_VARIANT (వృక్షం_TYPE (inside_init))))
	{
	  error_init (init_loc, "invalid initializer");
	  తిరిగి error_mark_కణుపు;
	}

      ఒకవేళ (require_constant
	  && వృక్షం_సంకేతం (inside_init) == COMPOUND_LITERAL_సమాసం)
	{
	  /* As an extension, allow initializing objects with static storage
	     duration with compound literals (which are then treated just as
	     the brace enclosed list they contain).  Also allow this for
	     vectors, as we can only assign them with compound literals.  */
	  ఒకవేళ (flag_isoc99 && సంకేతం_2 != సదిశ_TYPE)
	    pedwarn_init (init_loc, OPT_Wpedantic, "initializer element "
			  "is not constant");
	  వృక్షం decl = COMPOUND_LITERAL_సమాసం_DECL (inside_init);
	  inside_init = DECL_INITIAL (decl);
	}

      ఒకవేళ (సంకేతం_2 == ARRAY_TYPE && వృక్షం_సంకేతం (inside_init) != STRING_CST
	  && వృక్షం_సంకేతం (inside_init) != CONSTRUCTOR)
	{
	  error_init (init_loc, "array initialized from non-constant array "
		      "expression");
	  తిరిగి error_mark_కణుపు;
	}

      /* Compound expressions can only occur here if -Wpedantic or
	 -pedantic-errors is specified.  In the later case, we always want
	 an error.  In the former case, we simply want a warning.  */
      ఒకవేళ (require_constant && pedantic
	  && వృక్షం_సంకేతం (inside_init) == COMPOUND_సమాసం)
	{
	  inside_init
	    = valid_compound_సమాసం_initializer (inside_init,
					       వృక్షం_TYPE (inside_init));
	  ఒకవేళ (inside_init == error_mark_కణుపు)
	    error_init (init_loc, "initializer element is not constant");
	  లేకపోతే
	    pedwarn_init (init_loc, OPT_Wpedantic,
			  "initializer element is not constant");
	  ఒకవేళ (flag_pedantic_errors)
	    inside_init = error_mark_కణుపు;
	}
      లేకపోతే ఒకవేళ (require_constant
	       && !initializer_constant_valid_p (inside_init,
						 వృక్షం_TYPE (inside_init)))
	{
	  error_init (init_loc, "initializer element is not constant");
	  inside_init = error_mark_కణుపు;
	}
      లేకపోతే ఒకవేళ (require_constant && !maybe_const)
	pedwarn_init (init_loc, OPT_Wpedantic,
		      "initializer element is not a constant expression");
      లేకపోతే ఒకవేళ (require_constexpr)
	check_constexpr_init (init_loc, type, inside_init,
			      int_const_సమాసం, arith_const_సమాసం);

      /* Added to enable additional -Wsuggest-attribute=format warnings.  */
      ఒకవేళ (వృక్షం_సంకేతం (వృక్షం_TYPE (inside_init)) == సూచిక_TYPE)
	inside_init = convert_for_assignment (init_loc, UNKNOWN_LOCATION,
					      type, inside_init, origtype,
					      (require_constant
					       ? ic_init_const
					       : ic_init), null_సూచిక_constant,
					      NULL_వృక్షం, NULL_వృక్షం, 0);
      ఒకవేళ (వృక్షం_సంకేతం (inside_init) == RAW_దత్తాంశం_CST
	  && c_inhibit_evaluation_warnings == 0
	  && warn_conversion
	  && !TYPE_UNSIGNED (type)
	  && TYPE_PRECISION (type) == CHAR_బిట్టు)
	కొరకు (గుర్తులేని పూర్ణాంకం i = 0;
	     i < (గుర్తులేని) RAW_దత్తాంశం_నిడివి (inside_init); ++i)
	  ఒకవేళ (RAW_దత్తాంశం_SCHAR_ELT (inside_init, i) < 0)
	    warning_at (init_loc, OPT_Wconversion,
			"conversion from %qT to %qT changes value from "
			"%qd to %qd",
			integer_type_కణుపు, type,
			RAW_దత్తాంశం_UCHAR_ELT (inside_init, i),
			RAW_దత్తాంశం_SCHAR_ELT (inside_init, i));
      తిరిగి inside_init;
    }

  /* Handle scalar types, including conversions.  */

  ఒకవేళ (సంకేతం_2 == INTEGER_TYPE || సంకేతం_2 == REAL_TYPE || సంకేతం_2 == FIXED_బిందువు_TYPE
      || సంకేతం_2 == సూచిక_TYPE || సంకేతం_2 == ENUMERAL_TYPE || సంకేతం_2 == BOOLEAN_TYPE
      || సంకేతం_2 == COMPLEX_TYPE || సంకేతం_2 == సదిశ_TYPE || సంకేతం_2 == NULLPTR_TYPE
      || సంకేతం_2 == BITINT_TYPE)
    {
      వృక్షం unconverted_init = inside_init;
      ఒకవేళ (వృక్షం_సంకేతం (వృక్షం_TYPE (init)) == ARRAY_TYPE
	  && (వృక్షం_సంకేతం (init) == STRING_CST
	      || వృక్షం_సంకేతం (init) == COMPOUND_LITERAL_సమాసం))
	inside_init = init = array_గమ్యం_సూచిక_conversion (init_loc, init);
      ఒకవేళ (semantic_type)
	inside_init = build1 (EXCESS_PRECISION_సమాసం, semantic_type,
			      inside_init);
      inside_init
	= convert_for_assignment (init_loc, UNKNOWN_LOCATION, type,
				  inside_init, origtype,
				  require_constant ? ic_init_const : ic_init,
				  null_సూచిక_constant, NULL_వృక్షం, NULL_వృక్షం,
				  0);

      /* Check to see if we have already given an error message.  */
      ఒకవేళ (inside_init == error_mark_కణుపు)
	;
      లేకపోతే ఒకవేళ (require_constant && !వృక్షం_CONSTANT (inside_init))
	{
	  error_init (init_loc, "initializer element is not constant");
	  inside_init = error_mark_కణుపు;
	}
      లేకపోతే ఒకవేళ (require_constant
	       && !initializer_constant_valid_p (inside_init,
						 వృక్షం_TYPE (inside_init)))
	{
	  error_init (init_loc, "initializer element is not computable at "
		      "load time");
	  inside_init = error_mark_కణుపు;
	}
      లేకపోతే ఒకవేళ (require_constant && !maybe_const)
	pedwarn_init (init_loc, OPT_Wpedantic,
		      "initializer element is not a constant expression");
      లేకపోతే ఒకవేళ (require_constexpr)
	check_constexpr_init (init_loc, type, unconverted_init,
			      int_const_సమాసం, arith_const_సమాసం);

      తిరిగి inside_init;
    }

  /* Come here only for records and arrays.  */

  ఒకవేళ (COMPLETE_TYPE_P (type) && వృక్షం_సంకేతం (TYPE_కొలత (type)) != INTEGER_CST)
    {
      error_init (init_loc,
		  "variable-sized object may not be initialized except "
		  "with an empty initializer");
      తిరిగి error_mark_కణుపు;
    }

  error_init (init_loc, "invalid initializer");
  తిరిగి error_mark_కణుపు;
}

/* Handle initializers that use braces.  */

/* Type of object we are accumulating a constructor for.
   This type is always a RECORD_TYPE, UNION_TYPE or ARRAY_TYPE.  */
స్థిర వృక్షం constructor_type;

/* For a RECORD_TYPE or UNION_TYPE, this is the chain of fields
   left to fill.  */
స్థిర వృక్షం constructor_fields;

/* For an ARRAY_TYPE, this is the specified index
   at which to store the next element we get.  */
స్థిర వృక్షం constructor_సూచీ;

/* For an ARRAY_TYPE, this is the maximum index.  */
స్థిర వృక్షం constructor_max_సూచీ;

/* For a RECORD_TYPE, this is the first field not yet written out.  */
స్థిర వృక్షం constructor_unfilled_fields;

/* For an ARRAY_TYPE, this is the index of the first element
   not yet written out.  */
స్థిర వృక్షం constructor_unfilled_సూచీ;

/* In a RECORD_TYPE, the byte index of the next consecutive field.
   This is so we can generate gaps between fields, when appropriate.  */
స్థిర వృక్షం constructor_బిట్టు_సూచీ;

/* If we are saving up the elements rather than allocating them,
   this is the list of elements so far (in reverse order,
   most recent first).  */
స్థిర vec<constructor_elt, va_gc> *constructor_elements;

/* 1 if constructor should be incrementally stored into a constructor chain,
   0 if all the elements should be kept in AVL tree.  */
స్థిర పూర్ణాంకం constructor_incremental;

/* 1 if so far this constructor's elements are all compile-time constants.  */
స్థిర పూర్ణాంకం constructor_constant;

/* 1 if so far this constructor's elements are all valid address constants.  */
స్థిర పూర్ణాంకం constructor_simple;

/* 1 if this constructor has an element that cannot be part of a
   constant expression.  */
స్థిర పూర్ణాంకం constructor_nonconst;

/* 1 if this constructor is erroneous so far.  */
స్థిర పూర్ణాంకం constructor_erroneous;

/* 1 if this constructor is the universal zero initializer { 0 }.  */
స్థిర పూర్ణాంకం constructor_zeroinit;

/* 1 if this constructor should have padding bits zeroed (C23 {}.  */
స్థిర తార్కిక constructor_zero_padding_బిట్లు;

/* 1 if this constructor is a braced scalar initializer (further nested levels
   of braces are an error).  */
స్థిర తార్కిక constructor_braced_scalar;

/* Structure for managing pending initializer elements, organized as an
   AVL tree.  */

నిర్మాణం init_కణుపు
{
  నిర్మాణం init_కణుపు *ఎడమ, *కుడి;
  నిర్మాణం init_కణుపు *మాతృ;
  పూర్ణాంకం balance;
  వృక్షం purpose;
  వృక్షం విలువ;
  వృక్షం origtype;
};

/* Tree of pending elements at this constructor level.
   These are elements encountered out of order
   which belong at places we haven't reached yet in actually
   writing the output.
   Will never hold tree nodes across GC runs.  */
స్థిర నిర్మాణం init_కణుపు *constructor_pending_elts;

/* The SPELLING_DEPTH of this constructor.  */
స్థిర పూర్ణాంకం constructor_లోతు;

/* DECL node for which an initializer is being read.
   0 means we are reading a constructor expression
   such as (struct foo) {...}.  */
స్థిర వృక్షం constructor_decl;

/* Nonzero if there were any member designators in this initializer.  */
స్థిర పూర్ణాంకం constructor_designated;

/* Nesting depth of designator list.  */
స్థిర పూర్ణాంకం designator_లోతు;

/* Nonzero if there were diagnosed errors in this designator list.  */
స్థిర పూర్ణాంకం designator_erroneous;


/* This stack has a level for each implicit or explicit level of
   structuring in the initializer, including the outermost one.  It
   saves the values of most of the variables above.  */

నిర్మాణం constructor_range_దొంతర;

నిర్మాణం constructor_దొంతర
{
  నిర్మాణం constructor_దొంతర *తదుపరి;
  వృక్షం type;
  వృక్షం fields;
  వృక్షం సూచీ;
  వృక్షం max_సూచీ;
  వృక్షం unfilled_సూచీ;
  వృక్షం unfilled_fields;
  వృక్షం బిట్టు_సూచీ;
  vec<constructor_elt, va_gc> *elements;
  నిర్మాణం init_కణుపు *pending_elts;
  పూర్ణాంకం స్థానభ్రంశం;
  పూర్ణాంకం లోతు;
  /* If value nonzero, this value should replace the entire
     constructor at this level.  */
  నిర్మాణం c_సమాసం replacement_విలువ;
  నిర్మాణం constructor_range_దొంతర *range_దొంతర;
  అక్షరం constant;
  అక్షరం simple;
  అక్షరం nonconst;
  అక్షరం implicit;
  అక్షరం erroneous;
  అక్షరం outer;
  అక్షరం incremental;
  అక్షరం designated;
  తార్కిక zero_padding_బిట్లు;
  తార్కిక braced_scalar;
  పూర్ణాంకం designator_లోతు;
};

స్థిర నిర్మాణం constructor_దొంతర *constructor_దొంతర;

/* This stack represents designators from some range designator up to
   the last designator in the list.  */

నిర్మాణం constructor_range_దొంతర
{
  నిర్మాణం constructor_range_దొంతర *తదుపరి, *prev;
  నిర్మాణం constructor_దొంతర *దొంతర;
  వృక్షం range_ప్రారంభం;
  వృక్షం సూచీ;
  వృక్షం range_చివర;
  వృక్షం fields;
};

స్థిర నిర్మాణం constructor_range_దొంతర *constructor_range_దొంతర;

/* This stack records separate initializers that are nested.
   Nested initializers can't happen in ANSI C, but GNU C allows them
   in cases like { ... (struct foo) { ... } ... }.  */

నిర్మాణం initializer_దొంతర
{
  నిర్మాణం initializer_దొంతర *తదుపరి;
  వృక్షం decl;
  నిర్మాణం constructor_దొంతర *constructor_దొంతర;
  నిర్మాణం constructor_range_దొంతర *constructor_range_దొంతర;
  vec<constructor_elt, va_gc> *elements;
  నిర్మాణం spelling *spelling;
  నిర్మాణం spelling *spelling_పునాది;
  పూర్ణాంకం spelling_కొలత;
  అక్షరం require_constant_విలువ;
  అక్షరం require_constant_elements;
  అక్షరం require_constexpr_విలువ;
  అక్షరం designated;
  rich_location *missing_brace_richloc;
};

స్థిర నిర్మాణం initializer_దొంతర *initializer_దొంతర;

/* Prepare to parse and output the initializer for variable DECL.  */

శూన్య
ప్రారంభం_init (వృక్షం decl, వృక్షం asmspec_వృక్షం ATTRIBUTE_వాడని,
	    తార్కిక init_require_constant, తార్కిక init_require_constexpr,
	    rich_location *richloc)
{
  స్థిరరాశి అక్షరం *locus;
  నిర్మాణం initializer_దొంతర *p = XNEW (నిర్మాణం initializer_దొంతర);

  p->decl = constructor_decl;
  p->require_constant_విలువ = require_constant_విలువ;
  p->require_constant_elements = require_constant_elements;
  p->require_constexpr_విలువ = require_constexpr_విలువ;
  p->constructor_దొంతర = constructor_దొంతర;
  p->constructor_range_దొంతర = constructor_range_దొంతర;
  p->elements = constructor_elements;
  p->spelling = spelling;
  p->spelling_పునాది = spelling_పునాది;
  p->spelling_కొలత = spelling_కొలత;
  p->తదుపరి = initializer_దొంతర;
  p->missing_brace_richloc = richloc;
  p->designated = constructor_designated;
  initializer_దొంతర = p;

  constructor_decl = decl;
  constructor_designated = 0;

  require_constant_విలువ = init_require_constant;
  require_constexpr_విలువ = init_require_constexpr;
  ఒకవేళ (decl != NULL_వృక్షం && decl != error_mark_కణుపు)
    {
      require_constant_elements
	= ((init_require_constant || (pedantic && !flag_isoc99))
	   /* For a scalar, you can always use any value to initialize,
	      even within braces.  */
	   && AGGREGATE_TYPE_P (వృక్షం_TYPE (decl)));
      locus = identifier_గమ్యం_locale (IDENTIFIER_సూచిక (DECL_NAME (decl)));
    }
  లేకపోతే
    {
      require_constant_elements = అబద్ధం;
      locus = _("(anonymous)");
    }

  constructor_దొంతర = 0;
  constructor_range_దొంతర = 0;

  దొరికింది_missing_braces = 0;

  spelling_పునాది = 0;
  spelling_కొలత = 0;
  RESTORE_SPELLING_లోతు (0);

  ఒకవేళ (locus)
    నెట్టు_string (locus);
}

శూన్య
ముగింపు_init (శూన్య)
{
  నిర్మాణం initializer_దొంతర *p = initializer_దొంతర;

  /* Free the whole constructor stack of this initializer.  */
  అయితే (constructor_దొంతర)
    {
      నిర్మాణం constructor_దొంతర *q = constructor_దొంతర;
      constructor_దొంతర = q->తదుపరి;
      XDELETE (q);
    }

  gcc_assert (!constructor_range_దొంతర);

  /* Pop back to the data of the outer initializer (if any).  */
  XDELETE (spelling_పునాది);

  constructor_decl = p->decl;
  require_constant_విలువ = p->require_constant_విలువ;
  require_constant_elements = p->require_constant_elements;
  require_constexpr_విలువ = p->require_constexpr_విలువ;
  constructor_దొంతర = p->constructor_దొంతర;
  constructor_designated = p->designated;
  constructor_range_దొంతర = p->constructor_range_దొంతర;
  constructor_elements = p->elements;
  spelling = p->spelling;
  spelling_పునాది = p->spelling_పునాది;
  spelling_కొలత = p->spelling_కొలత;
  initializer_దొంతర = p->తదుపరి;
  XDELETE (p);
}

/* Call here when we see the initializer is surrounded by braces.
   This is instead of a call to push_init_level;
   it is matched by a call to pop_init_level.

   TYPE is the type to initialize, for a constructor expression.
   For an initializer for a decl, TYPE is zero.  */

శూన్య
really_ప్రారంభం_incremental_init (వృక్షం type)
{
  నిర్మాణం constructor_దొంతర *p = XNEW (నిర్మాణం constructor_దొంతర);

  ఒకవేళ (type == NULL_వృక్షం)
    type = వృక్షం_TYPE (constructor_decl);

  ఒకవేళ (సదిశ_TYPE_P (type)
      && TYPE_సదిశ_OPAQUE (type))
    error ("opaque vector types cannot be initialized");

  p->type = constructor_type;
  p->fields = constructor_fields;
  p->సూచీ = constructor_సూచీ;
  p->max_సూచీ = constructor_max_సూచీ;
  p->unfilled_సూచీ = constructor_unfilled_సూచీ;
  p->unfilled_fields = constructor_unfilled_fields;
  p->బిట్టు_సూచీ = constructor_బిట్టు_సూచీ;
  p->elements = constructor_elements;
  p->constant = constructor_constant;
  p->simple = constructor_simple;
  p->nonconst = constructor_nonconst;
  p->erroneous = constructor_erroneous;
  p->pending_elts = constructor_pending_elts;
  p->లోతు = constructor_లోతు;
  p->replacement_విలువ.విలువ = 0;
  p->replacement_విలువ.original_సంకేతం = ERROR_MARK;
  p->replacement_విలువ.original_type = ఖాళీ;
  p->implicit = 0;
  p->range_దొంతర = 0;
  p->outer = 0;
  p->incremental = constructor_incremental;
  p->designated = constructor_designated;
  p->zero_padding_బిట్లు = constructor_zero_padding_బిట్లు;
  p->braced_scalar = constructor_braced_scalar;
  p->designator_లోతు = designator_లోతు;
  p->తదుపరి = 0;
  constructor_దొంతర = p;

  constructor_constant = 1;
  constructor_simple = 1;
  constructor_nonconst = 0;
  constructor_లోతు = SPELLING_లోతు ();
  constructor_elements = ఖాళీ;
  constructor_pending_elts = 0;
  constructor_type = type;
  constructor_incremental = 1;
  constructor_designated = 0;
  constructor_zero_padding_బిట్లు = అబద్ధం;
  constructor_zeroinit = 1;
  constructor_braced_scalar = అబద్ధం;
  designator_లోతు = 0;
  designator_erroneous = 0;

  ఒకవేళ (రికార్డు_OR_UNION_TYPE_P (constructor_type))
    {
      constructor_fields = TYPE_FIELDS (constructor_type);
      /* Skip any nameless bit fields at the beginning.  */
      అయితే (constructor_fields != NULL_వృక్షం
	     && DECL_UNNAMED_బిట్టు_క్షేత్రం (constructor_fields))
	constructor_fields = DECL_CHAIN (constructor_fields);

      constructor_unfilled_fields = constructor_fields;
      constructor_బిట్టు_సూచీ = bitsize_zero_కణుపు;
    }
  లేకపోతే ఒకవేళ (వృక్షం_సంకేతం (constructor_type) == ARRAY_TYPE)
    {
      ఒకవేళ (TYPE_DOMAIN (constructor_type))
	{
	  constructor_max_సూచీ
	    = TYPE_MAX_విలువ (TYPE_DOMAIN (constructor_type));

	  /* Detect non-empty initializations of zero-length arrays.  */
	  ఒకవేళ (constructor_max_సూచీ == NULL_వృక్షం
	      && TYPE_కొలత (constructor_type))
	    constructor_max_సూచీ = integer_minus_one_కణుపు;

	  /* constructor_max_index needs to be an INTEGER_CST.  Attempts
	     to initialize VLAs with a nonempty initializer will cause a
	     proper error; avoid tree checking errors as well by setting a
	     safe value.  */
	  ఒకవేళ (constructor_max_సూచీ
	      && వృక్షం_సంకేతం (constructor_max_సూచీ) != INTEGER_CST)
	    constructor_max_సూచీ = integer_minus_one_కణుపు;

	  constructor_సూచీ
	    = convert (bitsizetype,
		       TYPE_MIN_విలువ (TYPE_DOMAIN (constructor_type)));
	}
      లేకపోతే
	{
	  constructor_సూచీ = bitsize_zero_కణుపు;
	  constructor_max_సూచీ = NULL_వృక్షం;
	}

      constructor_unfilled_సూచీ = constructor_సూచీ;
    }
  లేకపోతే ఒకవేళ (gnu_సదిశ_type_p (constructor_type))
    {
      /* Vectors are like simple fixed-size arrays.  */
      constructor_max_సూచీ =
	bitsize_int (TYPE_సదిశ_SUBPARTS (constructor_type) - 1);
      constructor_సూచీ = bitsize_zero_కణుపు;
      constructor_unfilled_సూచీ = constructor_సూచీ;
    }
  లేకపోతే
    {
      /* Handle the case of int x = {5}; */
      constructor_fields = constructor_type;
      constructor_unfilled_fields = constructor_type;
      constructor_braced_scalar = నిజం;
    }
}

బాహ్య location_t చివరి_init_list_comma;

/* Called when we see an open brace for a nested initializer.  Finish
   off any pending levels with implicit braces.  */
శూన్య
ముగింపు_implicit_inits (location_t loc, నిర్మాణం obstack *braced_init_obstack)
{
  అయితే (constructor_దొంతర->implicit)
    {
      ఒకవేళ (రికార్డు_OR_UNION_TYPE_P (constructor_type)
	  && constructor_fields == NULL_వృక్షం)
	process_init_element (ఆదానం_location,
			      తీయి_init_level (loc, 1, braced_init_obstack,
					      చివరి_init_list_comma),
			      నిజం, braced_init_obstack);
      లేకపోతే ఒకవేళ (వృక్షం_సంకేతం (constructor_type) == ARRAY_TYPE
	       && constructor_max_సూచీ
	       && వృక్షం_int_cst_lt (constructor_max_సూచీ,
				   constructor_సూచీ))
	process_init_element (ఆదానం_location,
			      తీయి_init_level (loc, 1, braced_init_obstack,
					      చివరి_init_list_comma),
			      నిజం, braced_init_obstack);
      లేకపోతే
	ఆపు;
    }
}

/* Push down into a subobject, for initialization.
   If this is for an explicit set of braces, IMPLICIT is 0.
   If it is because the next element belongs at a lower level,
   IMPLICIT is 1 (or 2 if the push is because of designator list).  */

శూన్య
నెట్టు_init_level (location_t loc, పూర్ణాంకం implicit,
		 నిర్మాణం obstack *braced_init_obstack)
{
  నిర్మాణం constructor_దొంతర *p;
  వృక్షం విలువ = NULL_వృక్షం;

  /* Unless this is an explicit brace, we need to preserve previous
     content if any.  */
  ఒకవేళ (implicit)
    {
      ఒకవేళ (రికార్డు_OR_UNION_TYPE_P (constructor_type) && constructor_fields)
	విలువ = కనుగొను_init_member (constructor_fields, braced_init_obstack);
      లేకపోతే ఒకవేళ (వృక్షం_సంకేతం (constructor_type) == ARRAY_TYPE)
	విలువ = కనుగొను_init_member (constructor_సూచీ, braced_init_obstack);
    }

  p = XNEW (నిర్మాణం constructor_దొంతర);
  p->type = constructor_type;
  p->fields = constructor_fields;
  p->సూచీ = constructor_సూచీ;
  p->max_సూచీ = constructor_max_సూచీ;
  p->unfilled_సూచీ = constructor_unfilled_సూచీ;
  p->unfilled_fields = constructor_unfilled_fields;
  p->బిట్టు_సూచీ = constructor_బిట్టు_సూచీ;
  p->elements = constructor_elements;
  p->constant = constructor_constant;
  p->simple = constructor_simple;
  p->nonconst = constructor_nonconst;
  p->erroneous = constructor_erroneous;
  p->pending_elts = constructor_pending_elts;
  p->లోతు = constructor_లోతు;
  p->replacement_విలువ.విలువ = NULL_వృక్షం;
  p->replacement_విలువ.original_సంకేతం = ERROR_MARK;
  p->replacement_విలువ.original_type = ఖాళీ;
  p->implicit = implicit;
  p->outer = 0;
  p->incremental = constructor_incremental;
  p->designated = constructor_designated;
  p->zero_padding_బిట్లు = constructor_zero_padding_బిట్లు;
  p->braced_scalar = constructor_braced_scalar;
  p->designator_లోతు = designator_లోతు;
  p->తదుపరి = constructor_దొంతర;
  p->range_దొంతర = 0;
  constructor_దొంతర = p;

  constructor_constant = 1;
  constructor_simple = 1;
  constructor_nonconst = 0;
  constructor_లోతు = SPELLING_లోతు ();
  constructor_elements = ఖాళీ;
  constructor_incremental = 1;
  /* If the upper initializer is designated, then mark this as
     designated too to prevent bogus warnings.  */
  constructor_designated = p->designated;
  /* If the upper initializer has padding bits zeroed, that includes
     all nested initializers as well.  */
  constructor_zero_padding_బిట్లు = p->zero_padding_బిట్లు;
  constructor_braced_scalar = అబద్ధం;
  constructor_pending_elts = 0;
  ఒకవేళ (!implicit)
    {
      p->range_దొంతర = constructor_range_దొంతర;
      constructor_range_దొంతర = 0;
      designator_లోతు = 0;
      designator_erroneous = 0;
    }

  /* Don't die if an entire brace-pair level is superfluous
     in the containing level.  */
  ఒకవేళ (constructor_type == NULL_వృక్షం)
    ;
  లేకపోతే ఒకవేళ (రికార్డు_OR_UNION_TYPE_P (constructor_type))
    {
      /* Don't die if there are extra init elts at the end.  */
      ఒకవేళ (constructor_fields == NULL_వృక్షం)
	constructor_type = NULL_వృక్షం;
      లేకపోతే
	{
	  constructor_type = వృక్షం_TYPE (constructor_fields);
	  నెట్టు_member_name (constructor_fields);
	  constructor_లోతు++;
	}
    }
  లేకపోతే ఒకవేళ (వృక్షం_సంకేతం (constructor_type) == ARRAY_TYPE)
    {
      constructor_type = వృక్షం_TYPE (constructor_type);
      నెట్టు_array_bounds (వృక్షం_గమ్యం_uhwi (constructor_సూచీ));
      constructor_లోతు++;
    }

  ఒకవేళ (constructor_type == NULL_వృక్షం)
    {
      error_init (loc, "extra brace group at end of initializer");
      constructor_fields = NULL_వృక్షం;
      constructor_unfilled_fields = NULL_వృక్షం;
      తిరిగి;
    }

  ఒకవేళ (విలువ && వృక్షం_సంకేతం (విలువ) == CONSTRUCTOR)
    {
      constructor_constant = వృక్షం_CONSTANT (విలువ);
      constructor_simple = వృక్షం_STATIC (విలువ);
      constructor_nonconst = CONSTRUCTOR_NON_CONST (విలువ);
      constructor_elements = CONSTRUCTOR_ELTS (విలువ);
      constructor_zero_padding_బిట్లు |= CONSTRUCTOR_ZERO_PADDING_బిట్లు (విలువ);
      ఒకవేళ (!vec_సురక్షిత_is_ఖాళీలు (constructor_elements)
	  && (వృక్షం_సంకేతం (constructor_type) == రికార్డు_TYPE
	      || వృక్షం_సంకేతం (constructor_type) == ARRAY_TYPE))
	సమితి_nonincremental_init (braced_init_obstack);
    }

  ఒకవేళ (implicit == 1)
    {
      దొరికింది_missing_braces = 1;
      ఒకవేళ (initializer_దొంతర->missing_brace_richloc)
	initializer_దొంతర->missing_brace_richloc->కూడు_fixit_చొప్పించు_before
	  (loc, "{");
    }

  ఒకవేళ (రికార్డు_OR_UNION_TYPE_P (constructor_type))
    {
      constructor_fields = TYPE_FIELDS (constructor_type);
      /* Skip any nameless bit fields at the beginning.  */
      అయితే (constructor_fields != NULL_వృక్షం
	     && DECL_UNNAMED_బిట్టు_క్షేత్రం (constructor_fields))
	constructor_fields = DECL_CHAIN (constructor_fields);

      constructor_unfilled_fields = constructor_fields;
      constructor_బిట్టు_సూచీ = bitsize_zero_కణుపు;
    }
  లేకపోతే ఒకవేళ (gnu_సదిశ_type_p (constructor_type))
    {
      /* Vectors are like simple fixed-size arrays.  */
      constructor_max_సూచీ =
	bitsize_int (TYPE_సదిశ_SUBPARTS (constructor_type) - 1);
      constructor_సూచీ = bitsize_int (0);
      constructor_unfilled_సూచీ = constructor_సూచీ;
    }
  లేకపోతే ఒకవేళ (వృక్షం_సంకేతం (constructor_type) == ARRAY_TYPE)
    {
      ఒకవేళ (TYPE_DOMAIN (constructor_type))
	{
	  constructor_max_సూచీ
	    = TYPE_MAX_విలువ (TYPE_DOMAIN (constructor_type));

	  /* Detect non-empty initializations of zero-length arrays.  */
	  ఒకవేళ (constructor_max_సూచీ == NULL_వృక్షం
	      && TYPE_కొలత (constructor_type))
	    constructor_max_సూచీ = integer_minus_one_కణుపు;

	  /* constructor_max_index needs to be an INTEGER_CST.  Attempts
	     to initialize VLAs will cause a proper error; avoid tree
	     checking errors as well by setting a safe value.  */
	  ఒకవేళ (constructor_max_సూచీ
	      && వృక్షం_సంకేతం (constructor_max_సూచీ) != INTEGER_CST)
	    constructor_max_సూచీ = integer_minus_one_కణుపు;

	  constructor_సూచీ
	    = convert (bitsizetype,
		       TYPE_MIN_విలువ (TYPE_DOMAIN (constructor_type)));
	}
      లేకపోతే
	constructor_సూచీ = bitsize_zero_కణుపు;

      constructor_unfilled_సూచీ = constructor_సూచీ;
      ఒకవేళ (విలువ && వృక్షం_సంకేతం (విలువ) == STRING_CST)
	{
	  /* We need to split the char/wchar array into individual
	     characters, so that we don't have to special case it
	     everywhere.  */
	  సమితి_nonincremental_init_from_string (విలువ, braced_init_obstack);
	}
    }
  లేకపోతే
    {
      ఒకవేళ (constructor_type != error_mark_కణుపు)
	{
	  ఒకవేళ (p->braced_scalar)
	    permerror_init (ఆదానం_location, 0,
			    "braces around scalar initializer");
	  లేకపోతే
	    warning_init (ఆదానం_location, 0,
			  "braces around scalar initializer");
	  constructor_braced_scalar = నిజం;
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

నిర్మాణం c_సమాసం
తీయి_init_level (location_t loc, పూర్ణాంకం implicit,
		నిర్మాణం obstack *braced_init_obstack,
		location_t చొప్పించు_before)
{
  నిర్మాణం constructor_దొంతర *p;
  నిర్మాణం c_సమాసం ret;
  ret.విలువ = NULL_వృక్షం;
  ret.original_సంకేతం = ERROR_MARK;
  ret.original_type = ఖాళీ;
  ret.m_decimal = 0;

  ఒకవేళ (implicit == 0)
    {
      /* When we come to an explicit close brace,
	 pop any inner levels that didn't have explicit braces.  */
      అయితే (constructor_దొంతర->implicit)
	process_init_element (ఆదానం_location,
			      తీయి_init_level (loc, 1, braced_init_obstack,
					      చొప్పించు_before),
			      నిజం, braced_init_obstack);
      gcc_assert (!constructor_range_దొంతర);
    }
  లేకపోతే
    ఒకవేళ (initializer_దొంతర->missing_brace_richloc)
      initializer_దొంతర->missing_brace_richloc->కూడు_fixit_చొప్పించు_before
	(చొప్పించు_before, "}");

  /* Now output all pending elements.  */
  constructor_incremental = 1;
  output_pending_init_elements (1, braced_init_obstack);

  p = constructor_దొంతర;

  /* Error for initializing a flexible array member.  */
  ఒకవేళ (constructor_type && constructor_fields
      && flexible_array_member_type_p (constructor_type))
    {
      /* Silently discard empty initializations.  The parser will
	 already have pedwarned for empty brackets for C17 and earlier.  */
      ఒకవేళ (integer_zerop (constructor_unfilled_సూచీ))
	constructor_type = NULL_వృక్షం;
      ఒకవేళ (constructor_type || flag_isoc23)
	{
	  gcc_assert (!constructor_type || !TYPE_కొలత (constructor_type));

	  ఒకవేళ (constructor_లోతు <= 2)
	    pedwarn_init (loc, OPT_Wpedantic,
			  "initialization of a flexible array member");
	  లేకపోతే ఒకవేళ (constructor_type)
	    error_init (loc, "initialization of flexible array member "
			     "in a nested context");
	  లేకపోతే
	    pedwarn_init (loc, OPT_Wpedantic,
			  "initialization of flexible array member "
			  "in a nested context");

	  /* We have already issued an error message for the existence
	     of a flexible array member not at the end of the structure.
	     Discard the initializer so that we do not die later.  */
	  ఒకవేళ (constructor_type
	      && DECL_CHAIN (constructor_fields) != NULL_వృక్షం
	      && (!p->type || వృక్షం_సంకేతం (p->type) != UNION_TYPE))
	    constructor_type = NULL_వృక్షం;
	}
    }

  ఎంపిక (vec_సురక్షిత_నిడివి (constructor_elements))
    {
    స్థితి 0:
      /* Initialization with { } counts as zeroinit.  */
      constructor_zeroinit = 1;
      ఆపు;
    స్థితి 1:
      /* This might be zeroinit as well.  */
      ఒకవేళ (integer_zerop ((*constructor_elements)[0].విలువ))
	constructor_zeroinit = 1;
      ఆపు;
    అప్రమేయ:
      /* If the constructor has more than one element, it can't be { 0 }.  */
      constructor_zeroinit = 0;
      ఆపు;
    }

  /* Warn when some structs are initialized with direct aggregation.  */
  ఒకవేళ (!implicit && దొరికింది_missing_braces && warn_missing_braces
      && !constructor_zeroinit)
    {
      gcc_assert (initializer_దొంతర->missing_brace_richloc);
      warning_at (initializer_దొంతర->missing_brace_richloc,
		  OPT_Wmissing_braces,
		  "missing braces around initializer");
    }

  /* Warn when some struct elements are implicitly initialized to zero.  */
  ఒకవేళ (warn_missing_క్షేత్రం_initializers
      && constructor_type
      && వృక్షం_సంకేతం (constructor_type) == రికార్డు_TYPE
      && constructor_unfilled_fields)
    {
	/* Do not warn for flexible array members or zero-length arrays.  */
	అయితే (constructor_unfilled_fields
	       && (!DECL_కొలత (constructor_unfilled_fields)
		   || integer_zerop (DECL_కొలత (constructor_unfilled_fields))))
	  constructor_unfilled_fields = DECL_CHAIN (constructor_unfilled_fields);

	ఒకవేళ (constructor_unfilled_fields
	    /* Do not warn if this level of the initializer uses member
	       designators; it is likely to be deliberate.  */
	    && !constructor_designated
	    /* Do not warn about initializing with { 0 } or with { }.  */
	    && !constructor_zeroinit)
	  {
	    ఒకవేళ (warning_at (ఆదానం_location, OPT_Wmissing_క్షేత్రం_initializers,
			    "missing initializer for field %qD of %qT",
			    constructor_unfilled_fields,
			    constructor_type))
	      inform (DECL_ఆధారం_LOCATION (constructor_unfilled_fields),
		      "%qD declared here", constructor_unfilled_fields);
	  }
    }

  /* Pad out the end of the structure.  */
  ఒకవేళ (p->replacement_విలువ.విలువ)
    /* If this closes a superfluous brace pair,
       just pass out the element between them.  */
    ret = p->replacement_విలువ;
  లేకపోతే ఒకవేళ (constructor_type == NULL_వృక్షం)
    ;
  లేకపోతే ఒకవేళ (!రికార్డు_OR_UNION_TYPE_P (constructor_type)
	   && వృక్షం_సంకేతం (constructor_type) != ARRAY_TYPE
	   && !gnu_సదిశ_type_p (constructor_type))
    {
      /* A nonincremental scalar initializer--just return
	 the element, after verifying there is just one.
         Empty scalar initializers are supported in C23.  */
      ఒకవేళ (vec_సురక్షిత_is_ఖాళీలు (constructor_elements))
	{
	  ఒకవేళ (constructor_erroneous || constructor_type == error_mark_కణుపు)
	    ret.విలువ = error_mark_కణుపు;
	  లేకపోతే ఒకవేళ (వృక్షం_సంకేతం (constructor_type) == FUNCTION_TYPE)
	    {
	      error_init (loc, "invalid initializer");
	      ret.విలువ = error_mark_కణుపు;
	    }
	  లేకపోతే ఒకవేళ (వృక్షం_సంకేతం (constructor_type) == సూచిక_TYPE)
	    /* Ensure this is a null pointer constant in the case of a
	       'constexpr' object initialized with {}.  */
	    ret.విలువ = build_zero_cst (ptr_type_కణుపు);
	  లేకపోతే
	    ret.విలువ = build_zero_cst (constructor_type);
	}
      లేకపోతే ఒకవేళ (vec_సురక్షిత_నిడివి (constructor_elements) != 1)
	{
	  error_init (loc, "extra elements in scalar initializer");
	  ret.విలువ = (*constructor_elements)[0].విలువ;
	}
      లేకపోతే
	ret.విలువ = (*constructor_elements)[0].విలువ;
    }
  లేకపోతే
    {
      ఒకవేళ (constructor_erroneous)
	ret.విలువ = error_mark_కణుపు;
      లేకపోతే
	{
	  ret.విలువ = build_constructor (constructor_type,
					 constructor_elements);
	  ఒకవేళ (constructor_constant)
	    వృక్షం_CONSTANT (ret.విలువ) = 1;
	  ఒకవేళ (constructor_constant && constructor_simple)
	    వృక్షం_STATIC (ret.విలువ) = 1;
	  ఒకవేళ (constructor_nonconst)
	    CONSTRUCTOR_NON_CONST (ret.విలువ) = 1;
	  ఒకవేళ (constructor_zero_padding_బిట్లు)
	    CONSTRUCTOR_ZERO_PADDING_బిట్లు (ret.విలువ) = 1;
	}
    }

  ఒకవేళ (ret.విలువ && వృక్షం_సంకేతం (ret.విలువ) != CONSTRUCTOR)
    {
      ఒకవేళ (constructor_nonconst)
	ret.original_సంకేతం = C_MAYBE_CONST_సమాసం;
      లేకపోతే ఒకవేళ (ret.original_సంకేతం == C_MAYBE_CONST_సమాసం)
	ret.original_సంకేతం = ERROR_MARK;
    }

  constructor_type = p->type;
  constructor_fields = p->fields;
  constructor_సూచీ = p->సూచీ;
  constructor_max_సూచీ = p->max_సూచీ;
  constructor_unfilled_సూచీ = p->unfilled_సూచీ;
  constructor_unfilled_fields = p->unfilled_fields;
  constructor_బిట్టు_సూచీ = p->బిట్టు_సూచీ;
  constructor_elements = p->elements;
  constructor_constant = p->constant;
  constructor_simple = p->simple;
  constructor_nonconst = p->nonconst;
  constructor_erroneous = p->erroneous;
  constructor_incremental = p->incremental;
  constructor_designated = p->designated;
  constructor_zero_padding_బిట్లు = p->zero_padding_బిట్లు;
  constructor_braced_scalar = p->braced_scalar;
  designator_లోతు = p->designator_లోతు;
  constructor_pending_elts = p->pending_elts;
  constructor_లోతు = p->లోతు;
  ఒకవేళ (!p->implicit)
    constructor_range_దొంతర = p->range_దొంతర;
  RESTORE_SPELLING_లోతు (constructor_లోతు);

  constructor_దొంతర = p->తదుపరి;
  XDELETE (p);

  ఒకవేళ (ret.విలువ == NULL_వృక్షం && constructor_దొంతర == 0)
    ret.విలువ = error_mark_కణుపు;
  తిరిగి ret;
}

/* Common handling for both array range and field name designators.
   ARRAY argument is nonzero for array ranges.  Returns false for success.  */

స్థిర తార్కిక
సమితి_designator (location_t loc, తార్కిక array,
		నిర్మాణం obstack *braced_init_obstack)
{
  వృక్షం subtype;
  గణన వృక్షం_సంకేతం_2 subcode;

  /* Don't die if an entire brace-pair level is superfluous
     in the containing level, or for an erroneous type.  */
  ఒకవేళ (constructor_type == NULL_వృక్షం || constructor_type == error_mark_కణుపు)
    తిరిగి నిజం;

  /* If there were errors in this designator list already, bail out
     silently.  */
  ఒకవేళ (designator_erroneous)
    తిరిగి నిజం;

  /* Likewise for an initializer for a variable-size type.  Those are
     diagnosed in the parser, except for empty initializer braces.  */
  ఒకవేళ (COMPLETE_TYPE_P (constructor_type)
      && వృక్షం_సంకేతం (TYPE_కొలత (constructor_type)) != INTEGER_CST)
    తిరిగి నిజం;

  ఒకవేళ (!designator_లోతు)
    {
      gcc_assert (!constructor_range_దొంతర);

      /* Designator list starts at the level of closest explicit
	 braces.  */
      అయితే (constructor_దొంతర->implicit)
	process_init_element (ఆదానం_location,
			      తీయి_init_level (loc, 1, braced_init_obstack,
					      చివరి_init_list_comma),
			      నిజం, braced_init_obstack);
      constructor_designated = 1;
      తిరిగి అబద్ధం;
    }

  ఎంపిక (వృక్షం_సంకేతం (constructor_type))
    {
    స్థితి  రికార్డు_TYPE:
    స్థితి  UNION_TYPE:
      subtype = వృక్షం_TYPE (constructor_fields);
      ఒకవేళ (subtype != error_mark_కణుపు)
	subtype = TYPE_MAIN_VARIANT (subtype);
      ఆపు;
    స్థితి ARRAY_TYPE:
      subtype = TYPE_MAIN_VARIANT (వృక్షం_TYPE (constructor_type));
      ఆపు;
    అప్రమేయ:
      gcc_unreachable ();
    }

  subcode = వృక్షం_సంకేతం (subtype);
  ఒకవేళ (array && subcode != ARRAY_TYPE)
    {
      error_init (loc, "array index in non-array initializer");
      తిరిగి నిజం;
    }
  లేకపోతే ఒకవేళ (!array && subcode != రికార్డు_TYPE && subcode != UNION_TYPE)
    {
      error_init (loc, "field name not in record or union initializer");
      తిరిగి నిజం;
    }

  constructor_designated = 1;
  ముగింపు_implicit_inits (loc, braced_init_obstack);
  నెట్టు_init_level (loc, 2, braced_init_obstack);
  తిరిగి అబద్ధం;
}

/* If there are range designators in designator list, push a new designator
   to constructor_range_stack.  RANGE_END is end of such stack range or
   NULL_TREE if there is no range designator at this level.  */

స్థిర శూన్య
నెట్టు_range_దొంతర (వృక్షం range_చివర, నిర్మాణం obstack * braced_init_obstack)
{
  నిర్మాణం constructor_range_దొంతర *p;

  p = (నిర్మాణం constructor_range_దొంతర *)
    obstack_alloc (braced_init_obstack,
		   పరిమాణం (నిర్మాణం constructor_range_దొంతర));
  p->prev = constructor_range_దొంతర;
  p->తదుపరి = 0;
  p->fields = constructor_fields;
  p->range_ప్రారంభం = constructor_సూచీ;
  p->సూచీ = constructor_సూచీ;
  p->దొంతర = constructor_దొంతర;
  p->range_చివర = range_చివర;
  ఒకవేళ (constructor_range_దొంతర)
    constructor_range_దొంతర->తదుపరి = p;
  constructor_range_దొంతర = p;
}

/* Within an array initializer, specify the next index to be initialized.
   FIRST is that index.  If LAST is nonzero, then initialize a range
   of indices, running from FIRST through LAST.  */

శూన్య
సమితి_init_సూచీ (location_t loc, వృక్షం మొదటి, వృక్షం చివరి,
		నిర్మాణం obstack *braced_init_obstack)
{
  ఒకవేళ (సమితి_designator (loc, నిజం, braced_init_obstack))
    తిరిగి;

  designator_erroneous = 1;

  ఒకవేళ (!INTEGRAL_TYPE_P (వృక్షం_TYPE (మొదటి))
      || (చివరి && !INTEGRAL_TYPE_P (వృక్షం_TYPE (చివరి))))
    {
      error_init (loc, "array index in initializer not of integer type");
      తిరిగి;
    }

  ఒకవేళ (వృక్షం_సంకేతం (మొదటి) != INTEGER_CST)
    {
      మొదటి = c_fully_fold (మొదటి, అబద్ధం, ఖాళీ);
      ఒకవేళ (వృక్షం_సంకేతం (మొదటి) == INTEGER_CST)
	pedwarn_init (loc, OPT_Wpedantic,
		      "array index in initializer is not "
		      "an integer constant expression");
    }

  ఒకవేళ (చివరి && వృక్షం_సంకేతం (చివరి) != INTEGER_CST)
    {
      చివరి = c_fully_fold (చివరి, అబద్ధం, ఖాళీ);
      ఒకవేళ (వృక్షం_సంకేతం (చివరి) == INTEGER_CST)
	pedwarn_init (loc, OPT_Wpedantic,
		      "array index in initializer is not "
		      "an integer constant expression");
    }

  ఒకవేళ (వృక్షం_సంకేతం (మొదటి) != INTEGER_CST)
    error_init (loc, "nonconstant array index in initializer");
  లేకపోతే ఒకవేళ (చివరి != NULL_వృక్షం && వృక్షం_సంకేతం (చివరి) != INTEGER_CST)
    error_init (loc, "nonconstant array index in initializer");
  లేకపోతే ఒకవేళ (వృక్షం_సంకేతం (constructor_type) != ARRAY_TYPE)
    error_init (loc, "array index in non-array initializer");
  లేకపోతే ఒకవేళ (వృక్షం_int_cst_sgn (మొదటి) == -1)
    error_init (loc, "array index in initializer exceeds array bounds");
  లేకపోతే ఒకవేళ (constructor_max_సూచీ
	   && వృక్షం_int_cst_lt (constructor_max_సూచీ, మొదటి))
    error_init (loc, "array index in initializer exceeds array bounds");
  లేకపోతే
    {
      constant_వ్యక్తీకరణ_warning (మొదటి);
      ఒకవేళ (చివరి)
	constant_వ్యక్తీకరణ_warning (చివరి);
      constructor_సూచీ = convert (bitsizetype, మొదటి);
      ఒకవేళ (వృక్షం_int_cst_lt (constructor_సూచీ, మొదటి))
	{
	  constructor_సూచీ = copy_కణుపు (constructor_సూచీ);
	  వృక్షం_అధికప్రవాహం (constructor_సూచీ) = 1;
	}

      ఒకవేళ (చివరి)
	{
	  ఒకవేళ (వృక్షం_int_cst_equal (మొదటి, చివరి))
	    చివరి = NULL_వృక్షం;
	  లేకపోతే ఒకవేళ (వృక్షం_int_cst_lt (చివరి, మొదటి))
	    {
	      error_init (loc, "empty index range in initializer");
	      చివరి = NULL_వృక్షం;
	    }
	  లేకపోతే
	    {
	      చివరి = convert (bitsizetype, చివరి);
	      ఒకవేళ (constructor_max_సూచీ != NULL_వృక్షం
		  && వృక్షం_int_cst_lt (constructor_max_సూచీ, చివరి))
		{
		  error_init (loc, "array index range in initializer exceeds "
			      "array bounds");
		  చివరి = NULL_వృక్షం;
		}
	    }
	}

      designator_లోతు++;
      designator_erroneous = 0;
      ఒకవేళ (constructor_range_దొంతర || చివరి)
	నెట్టు_range_దొంతర (చివరి, braced_init_obstack);
    }
}

/* Within a struct initializer, specify the next field to be initialized.  */

శూన్య
సమితి_init_label (location_t loc, వృక్షం fieldname, location_t fieldname_loc,
		నిర్మాణం obstack *braced_init_obstack)
{
  వృక్షం క్షేత్రం_2;

  ఒకవేళ (సమితి_designator (loc, అబద్ధం, braced_init_obstack))
    తిరిగి;

  designator_erroneous = 1;

  ఒకవేళ (!రికార్డు_OR_UNION_TYPE_P (constructor_type))
    {
      error_init (loc, "field name not in record or union initializer");
      తిరిగి;
    }

  క్షేత్రం_2 = lookup_క్షేత్రం (constructor_type, fieldname);

  ఒకవేళ (క్షేత్రం_2 == NULL_వృక్షం)
    {
      వృక్షం guessed_id = lookup_క్షేత్రం_fuzzy (constructor_type, fieldname);
      ఒకవేళ (guessed_id)
	{
	  gcc_rich_location rich_loc (fieldname_loc);
	  rich_loc.కూడు_fixit_misspelled_id (fieldname_loc, guessed_id);
	  error_at (&rich_loc,
		    "%qT has no member named %qE; did you mean %qE?",
		    constructor_type, fieldname, guessed_id);
	}
      లేకపోతే
	error_at (fieldname_loc, "%qT has no member named %qE",
		  constructor_type, fieldname);
    }
  లేకపోతే
    చేయి
      {
	constructor_fields = వృక్షం_విలువ (క్షేత్రం_2);
	designator_లోతు++;
	designator_erroneous = 0;
	ఒకవేళ (constructor_range_దొంతర)
	  నెట్టు_range_దొంతర (NULL_వృక్షం, braced_init_obstack);
	క్షేత్రం_2 = వృక్షం_CHAIN (క్షేత్రం_2);
	ఒకవేళ (క్షేత్రం_2)
	  {
	    ఒకవేళ (సమితి_designator (loc, అబద్ధం, braced_init_obstack))
	      తిరిగి;
	  }
      }
    అయితే (క్షేత్రం_2 != NULL_వృక్షం);
}

/* Helper function for add_pending_init.  Find inorder successor of P
   in AVL tree.  */
స్థిర నిర్మాణం init_కణుపు *
init_కణుపు_successor (నిర్మాణం init_కణుపు *p)
{
  నిర్మాణం init_కణుపు *r;
  ఒకవేళ (p->కుడి)
    {
      r = p->కుడి;
      అయితే (r->ఎడమ)
	r = r->ఎడమ;
      తిరిగి r;
    }
  r = p->మాతృ;
  అయితే (r && p == r->కుడి)
    {
      p = r;
      r = r->మాతృ;
    }
  తిరిగి r;
}

/* Add a new initializer to the tree of pending initializers.  PURPOSE
   identifies the initializer, either array index or field in a structure.
   VALUE is the value of that index or field.  If ORIGTYPE is not
   NULL_TREE, it is the original type of VALUE.

   IMPLICIT is true if value comes from pop_init_level (1),
   the new initializer has been merged with the existing one
   and thus no warnings should be emitted about overriding an
   existing initializer.  */

స్థిర శూన్య
కూడు_pending_init (location_t loc, వృక్షం purpose, వృక్షం విలువ, వృక్షం origtype,
		  తార్కిక implicit, నిర్మాణం obstack *braced_init_obstack)
{
  నిర్మాణం init_కణుపు *p, **q, *r;

  q = &constructor_pending_elts;
  p = 0;

  ఒకవేళ (వృక్షం_సంకేతం (constructor_type) == ARRAY_TYPE)
    {
      అయితే (*q != 0)
	{
	  p = *q;
	  ఒకవేళ (వృక్షం_int_cst_lt (purpose, p->purpose))
	    q = &p->ఎడమ;
	  లేకపోతే ఒకవేళ (వృక్షం_int_cst_lt (p->purpose, purpose))
	    {
	      ఒకవేళ (వృక్షం_సంకేతం (p->విలువ) != RAW_దత్తాంశం_CST
		  || (p->కుడి
		      && వృక్షం_int_cst_le (p->కుడి->purpose, purpose)))
		q = &p->కుడి;
	      లేకపోతే
		{
		  widest_int pp = wi::గమ్యం_widest (p->purpose);
		  widest_int pw = wi::గమ్యం_widest (purpose);
		  ఒకవేళ (pp + RAW_దత్తాంశం_నిడివి (p->విలువ) <= pw)
		    q = &p->కుడి;
		  లేకపోతే
		    {
		      /* Override which should split the old RAW_DATA_CST
			 into 2 or 3 pieces.  */
		      ఒకవేళ (!implicit && warn_override_init)
			warning_init (loc, OPT_Woverride_init,
				      "initialized field overwritten");
		      గుర్తులేని HOST_WIDE_INT ప్రారంభం = (pw - pp).గమ్యం_uhwi ();
		      గుర్తులేని HOST_WIDE_INT len = 1;
		      ఒకవేళ (వృక్షం_సంకేతం (విలువ) == RAW_దత్తాంశం_CST)
			len = RAW_దత్తాంశం_నిడివి (విలువ);
		      గుర్తులేని HOST_WIDE_INT చివర = 0;
		      గుర్తులేని plen = RAW_దత్తాంశం_నిడివి (p->విలువ);
		      gcc_checking_assert (ప్రారంభం < plen && ప్రారంభం);
		      ఒకవేళ (plen - ప్రారంభం > len)
			చివర = plen - ప్రారంభం - len;
		      వృక్షం v = p->విలువ;
		      వృక్షం origtype = p->origtype;
		      ఒకవేళ (ప్రారంభం == 1)
			p->విలువ = build_int_cst (వృక్షం_TYPE (v),
						  RAW_దత్తాంశం_UCHAR_ELT (v, 0));
		      లేకపోతే
			{
			  p->విలువ = v;
			  ఒకవేళ (చివర > 1)
			    v = copy_కణుపు (v);
			  RAW_దత్తాంశం_నిడివి (p->విలువ) = ప్రారంభం;
			}
		      ఒకవేళ (చివర)
			{
			  వృక్షం epurpose
			    = కొలత_binop (PLUS_సమాసం, purpose,
					  bitsize_int (len));
			  ఒకవేళ (చివర > 1)
			    {
			      RAW_దత్తాంశం_నిడివి (v) -= plen - చివర;
			      RAW_దత్తాంశం_సూచిక (v) += plen - చివర;
			    }
			  లేకపోతే
			    v = build_int_cst (వృక్షం_TYPE (v),
					       RAW_దత్తాంశం_UCHAR_ELT (v, plen
								      - చివర));
			  కూడు_pending_init (loc, epurpose, v, origtype,
					    implicit, braced_init_obstack);
			}
		      q = &constructor_pending_elts;
		      కొనసాగు;
		    }
		}
	    }
	  లేకపోతే
	    {
	      ఒకవేళ (వృక్షం_సంకేతం (p->విలువ) == RAW_దత్తాంశం_CST
		  && (RAW_దత్తాంశం_నిడివి (p->విలువ)
		      > (వృక్షం_సంకేతం (విలువ) == RAW_దత్తాంశం_CST
			 ? RAW_దత్తాంశం_నిడివి (విలువ) : 1)))
		{
		  /* Override which should split the old RAW_DATA_CST
		     into 2 pieces.  */
		  ఒకవేళ (!implicit && warn_override_init)
		    warning_init (loc, OPT_Woverride_init,
				  "initialized field overwritten");
		  గుర్తులేని HOST_WIDE_INT len = 1;
		  ఒకవేళ (వృక్షం_సంకేతం (విలువ) == RAW_దత్తాంశం_CST)
		    len = RAW_దత్తాంశం_నిడివి (విలువ);
		  ఒకవేళ ((గుర్తులేని) RAW_దత్తాంశం_నిడివి (p->విలువ) > len + 1)
		    {
		      RAW_దత్తాంశం_నిడివి (p->విలువ) -= len;
		      RAW_దత్తాంశం_సూచిక (p->విలువ) += len;
		    }
		  లేకపోతే
		    {
		      గుర్తులేని పూర్ణాంకం l = RAW_దత్తాంశం_నిడివి (p->విలువ) - 1;
		      p->విలువ
			= build_int_cst (వృక్షం_TYPE (p->విలువ),
					 RAW_దత్తాంశం_UCHAR_ELT (p->విలువ, l));
		    }
		  p->purpose = కొలత_binop (PLUS_సమాసం, p->purpose,
					   bitsize_int (len));
		  కొనసాగు;
		}
	      ఒకవేళ (వృక్షం_సంకేతం (విలువ) == RAW_దత్తాంశం_CST)
		{
		handle_raw_దత్తాంశం:
		  /* RAW_DATA_CST value might overlap various further
		     prior initval entries.  Find out how many.  */
		  గుర్తులేని cnt = 0;
		  widest_int w
		    = wi::గమ్యం_widest (purpose) + RAW_దత్తాంశం_నిడివి (విలువ);
		  నిర్మాణం init_కణుపు *r = p, *చివరి = ఖాళీ;
		  తార్కిక override_init = warn_override_init;
		  అయితే ((r = init_కణుపు_successor (r))
			 && wi::గమ్యం_widest (r->purpose) < w)
		    {
		      ++cnt;
		      ఒకవేళ (వృక్షం_SIDE_EFFECTS (r->విలువ))
			warning_init (loc, OPT_Woverride_init_side_effects,
				      "initialized field with side-effects "
				      "overwritten");
		      లేకపోతే ఒకవేళ (override_init)
			{
			  warning_init (loc, OPT_Woverride_init,
					"initialized field overwritten");
			  override_init = అబద్ధం;
			}
		      చివరి = r;
		    }
		  ఒకవేళ (cnt)
		    {
		      ఒకవేళ (వృక్షం_సంకేతం (చివరి->విలువ) == RAW_దత్తాంశం_CST
			  && (wi::గమ్యం_widest (చివరి->purpose)
			      + RAW_దత్తాంశం_నిడివి (చివరి->విలువ) > w))
			{
			  /* The last overlapping prior initval overlaps
			     only partially.  Shrink it and decrease cnt.  */
			  గుర్తులేని పూర్ణాంకం l = (wi::గమ్యం_widest (చివరి->purpose)
					    + RAW_దత్తాంశం_నిడివి (చివరి->విలువ)
					    - w).గమ్యం_uhwi ();
			  --cnt;
			  RAW_దత్తాంశం_నిడివి (చివరి->విలువ) -= l;
			  RAW_దత్తాంశం_సూచిక (చివరి->విలువ) += l;
			  ఒకవేళ (RAW_దత్తాంశం_నిడివి (చివరి->విలువ) == 1)
			    చివరి->విలువ
			      = build_int_cst (వృక్షం_TYPE (చివరి->విలువ),
					       RAW_దత్తాంశం_UCHAR_ELT (చివరి->విలువ,
								   0));
			  చివరి->purpose
			    = కొలత_binop (PLUS_సమాసం, చివరి->purpose,
					  bitsize_int (l));
			}
		      /* Instead of deleting cnt nodes from the AVL tree
			 and rebalancing, peel of last cnt bytes from the
			 RAW_DATA_CST.  Overriding thousands of previously
			 initialized array elements with #embed needs to work,
			 but doesn't need to be super efficient.  */
		      gcc_checking_assert ((గుర్తులేని) RAW_దత్తాంశం_నిడివి (విలువ)
					   > cnt);
		      RAW_దత్తాంశం_నిడివి (విలువ) -= cnt;
		      స్థిరరాశి గుర్తులేని అక్షరం *s
			= &RAW_దత్తాంశం_UCHAR_ELT (విలువ, RAW_దత్తాంశం_నిడివి (విలువ));
		      గుర్తులేని పూర్ణాంకం o = RAW_దత్తాంశం_నిడివి (విలువ);
		      కొరకు (r = p; cnt--; ++o, ++s)
			{
			  r = init_కణుపు_successor (r);
			  r->purpose = కొలత_binop (PLUS_సమాసం, purpose,
						   bitsize_int (o));
			  r->విలువ = build_int_cst (వృక్షం_TYPE (విలువ), *s);
			  r->origtype = origtype;
			}
		      ఒకవేళ (RAW_దత్తాంశం_నిడివి (విలువ) == 1)
			విలువ = build_int_cst (వృక్షం_TYPE (విలువ),
					       RAW_దత్తాంశం_UCHAR_ELT (విలువ, 0));
		    }
		}
	      ఒకవేళ (!implicit)
		{
		  ఒకవేళ (వృక్షం_SIDE_EFFECTS (p->విలువ))
		    warning_init (loc, OPT_Woverride_init_side_effects,
				  "initialized field with side-effects "
				  "overwritten");
		  లేకపోతే ఒకవేళ (warn_override_init)
		    warning_init (loc, OPT_Woverride_init,
				  "initialized field overwritten");
		}
	      p->విలువ = విలువ;
	      p->origtype = origtype;
	      తిరిగి;
	    }
	}
      ఒకవేళ (వృక్షం_సంకేతం (విలువ) == RAW_దత్తాంశం_CST && p)
	{
	  నిర్మాణం init_కణుపు *r;
	  ఒకవేళ (q == &p->ఎడమ)
	    r = p;
	  లేకపోతే
	    r = init_కణుపు_successor (p);
	  ఒకవేళ (r && wi::గమ్యం_widest (r->purpose) < (wi::గమ్యం_widest (purpose)
						 + RAW_దత్తాంశం_నిడివి (విలువ)))
	    {
	      /* Overlap with at least one prior initval in the range but
		 not at the start.  */
	      p = r;
	      p->purpose = purpose;
	      వెళ్ళు handle_raw_దత్తాంశం;
	    }
	}
    }
  లేకపోతే
    {
      వృక్షం bitpos;

      bitpos = బిట్టు_position (purpose);
      అయితే (*q != ఖాళీ)
	{
	  p = *q;
	  ఒకవేళ (వృక్షం_int_cst_lt (bitpos, బిట్టు_position (p->purpose)))
	    q = &p->ఎడమ;
	  లేకపోతే ఒకవేళ (p->purpose != purpose)
	    q = &p->కుడి;
	  లేకపోతే
	    {
	      ఒకవేళ (!implicit)
		{
		  ఒకవేళ (వృక్షం_SIDE_EFFECTS (p->విలువ))
		    warning_init (loc, OPT_Woverride_init_side_effects,
				  "initialized field with side-effects "
				  "overwritten");
		  లేకపోతే ఒకవేళ (warn_override_init)
		    warning_init (loc, OPT_Woverride_init,
				  "initialized field overwritten");
		}
	      p->విలువ = విలువ;
	      p->origtype = origtype;
	      తిరిగి;
	    }
	}
    }

  r = (నిర్మాణం init_కణుపు *) obstack_alloc (braced_init_obstack,
					  పరిమాణం (నిర్మాణం init_కణుపు));
  r->purpose = purpose;
  r->విలువ = విలువ;
  r->origtype = origtype;

  *q = r;
  r->మాతృ = p;
  r->ఎడమ = 0;
  r->కుడి = 0;
  r->balance = 0;

  అయితే (p)
    {
      నిర్మాణం init_కణుపు *s;

      ఒకవేళ (r == p->ఎడమ)
	{
	  ఒకవేళ (p->balance == 0)
	    p->balance = -1;
	  లేకపోతే ఒకవేళ (p->balance < 0)
	    {
	      ఒకవేళ (r->balance < 0)
		{
		  /* L rotation.  */
		  p->ఎడమ = r->కుడి;
		  ఒకవేళ (p->ఎడమ)
		    p->ఎడమ->మాతృ = p;
		  r->కుడి = p;

		  p->balance = 0;
		  r->balance = 0;

		  s = p->మాతృ;
		  p->మాతృ = r;
		  r->మాతృ = s;
		  ఒకవేళ (s)
		    {
		      ఒకవేళ (s->ఎడమ == p)
			s->ఎడమ = r;
		      లేకపోతే
			s->కుడి = r;
		    }
		  లేకపోతే
		    constructor_pending_elts = r;
		}
	      లేకపోతే
		{
		  /* LR rotation.  */
		  నిర్మాణం init_కణుపు *t = r->కుడి;

		  r->కుడి = t->ఎడమ;
		  ఒకవేళ (r->కుడి)
		    r->కుడి->మాతృ = r;
		  t->ఎడమ = r;

		  p->ఎడమ = t->కుడి;
		  ఒకవేళ (p->ఎడమ)
		    p->ఎడమ->మాతృ = p;
		  t->కుడి = p;

		  p->balance = t->balance < 0;
		  r->balance = -(t->balance > 0);
		  t->balance = 0;

		  s = p->మాతృ;
		  p->మాతృ = t;
		  r->మాతృ = t;
		  t->మాతృ = s;
		  ఒకవేళ (s)
		    {
		      ఒకవేళ (s->ఎడమ == p)
			s->ఎడమ = t;
		      లేకపోతే
			s->కుడి = t;
		    }
		  లేకపోతే
		    constructor_pending_elts = t;
		}
	      ఆపు;
	    }
	  లేకపోతే
	    {
	      /* p->balance == +1; growth of left side balances the node.  */
	      p->balance = 0;
	      ఆపు;
	    }
	}
      లేకపోతే /* r == p->right */
	{
	  ఒకవేళ (p->balance == 0)
	    /* Growth propagation from right side.  */
	    p->balance++;
	  లేకపోతే ఒకవేళ (p->balance > 0)
	    {
	      ఒకవేళ (r->balance > 0)
		{
		  /* R rotation.  */
		  p->కుడి = r->ఎడమ;
		  ఒకవేళ (p->కుడి)
		    p->కుడి->మాతృ = p;
		  r->ఎడమ = p;

		  p->balance = 0;
		  r->balance = 0;

		  s = p->మాతృ;
		  p->మాతృ = r;
		  r->మాతృ = s;
		  ఒకవేళ (s)
		    {
		      ఒకవేళ (s->ఎడమ == p)
			s->ఎడమ = r;
		      లేకపోతే
			s->కుడి = r;
		    }
		  లేకపోతే
		    constructor_pending_elts = r;
		}
	      లేకపోతే /* r->balance == -1 */
		{
		  /* RL rotation */
		  నిర్మాణం init_కణుపు *t = r->ఎడమ;

		  r->ఎడమ = t->కుడి;
		  ఒకవేళ (r->ఎడమ)
		    r->ఎడమ->మాతృ = r;
		  t->కుడి = r;

		  p->కుడి = t->ఎడమ;
		  ఒకవేళ (p->కుడి)
		    p->కుడి->మాతృ = p;
		  t->ఎడమ = p;

		  r->balance = (t->balance < 0);
		  p->balance = -(t->balance > 0);
		  t->balance = 0;

		  s = p->మాతృ;
		  p->మాతృ = t;
		  r->మాతృ = t;
		  t->మాతృ = s;
		  ఒకవేళ (s)
		    {
		      ఒకవేళ (s->ఎడమ == p)
			s->ఎడమ = t;
		      లేకపోతే
			s->కుడి = t;
		    }
		  లేకపోతే
		    constructor_pending_elts = t;
		}
	      ఆపు;
	    }
	  లేకపోతే
	    {
	      /* p->balance == -1; growth of right side balances the node.  */
	      p->balance = 0;
	      ఆపు;
	    }
	}

      r = p;
      p = p->మాతృ;
    }
}

/* Build AVL tree from a sorted chain.  */

స్థిర శూన్య
సమితి_nonincremental_init (నిర్మాణం obstack * braced_init_obstack)
{
  గుర్తులేని HOST_WIDE_INT ix;
  వృక్షం సూచీ, విలువ;

  ఒకవేళ (వృక్షం_సంకేతం (constructor_type) != రికార్డు_TYPE
      && వృక్షం_సంకేతం (constructor_type) != ARRAY_TYPE)
    తిరిగి;

  FOR_EACH_CONSTRUCTOR_ELT (constructor_elements, ix, సూచీ, విలువ)
    కూడు_pending_init (ఆదానం_location, సూచీ, విలువ, NULL_వృక్షం, నిజం,
		      braced_init_obstack);
  constructor_elements = ఖాళీ;
  ఒకవేళ (వృక్షం_సంకేతం (constructor_type) == రికార్డు_TYPE)
    {
      constructor_unfilled_fields = TYPE_FIELDS (constructor_type);
      /* Skip any nameless bit fields at the beginning.  */
      అయితే (constructor_unfilled_fields != NULL_వృక్షం
	     && DECL_UNNAMED_బిట్టు_క్షేత్రం (constructor_unfilled_fields))
	constructor_unfilled_fields = వృక్షం_CHAIN (constructor_unfilled_fields);

    }
  లేకపోతే ఒకవేళ (వృక్షం_సంకేతం (constructor_type) == ARRAY_TYPE)
    {
      ఒకవేళ (TYPE_DOMAIN (constructor_type))
	constructor_unfilled_సూచీ
	  = convert (bitsizetype,
		     TYPE_MIN_విలువ (TYPE_DOMAIN (constructor_type)));
      లేకపోతే
	constructor_unfilled_సూచీ = bitsize_zero_కణుపు;
    }
  constructor_incremental = 0;
}

/* Build AVL tree from a string constant.  */

స్థిర శూన్య
సమితి_nonincremental_init_from_string (వృక్షం str,
				     నిర్మాణం obstack * braced_init_obstack)
{
  వృక్షం విలువ, purpose, type;
  HOST_WIDE_INT val[2];
  స్థిరరాశి అక్షరం *p, *చివర;
  పూర్ణాంకం byte, wchar_బైట్లు, charwidth, bitpos;

  gcc_assert (వృక్షం_సంకేతం (constructor_type) == ARRAY_TYPE);

  wchar_బైట్లు = TYPE_PRECISION (వృక్షం_TYPE (వృక్షం_TYPE (str))) / బిట్లు_చొప్పున_UNIT;
  charwidth = TYPE_PRECISION (char_type_కణుపు);
  gcc_assert ((కొలత_t) wchar_బైట్లు * charwidth
	      <= ARRAY_కొలత (val) * HOST_బిట్లు_చొప్పున_WIDE_INT);
  type = వృక్షం_TYPE (constructor_type);
  p = వృక్షం_STRING_సూచిక (str);
  చివర = p + వృక్షం_STRING_నిడివి (str);

  కొరకు (purpose = bitsize_zero_కణుపు;
       p < చివర
       && !(constructor_max_సూచీ
	    && వృక్షం_int_cst_lt (constructor_max_సూచీ, purpose));
       purpose = కొలత_binop (PLUS_సమాసం, purpose, bitsize_one_కణుపు))
    {
      ఒకవేళ (wchar_బైట్లు == 1)
	{
	  val[0] = (గుర్తులేని అక్షరం) *p++;
	  val[1] = 0;
	}
      లేకపోతే
	{
	  val[1] = 0;
	  val[0] = 0;
	  కొరకు (byte = 0; byte < wchar_బైట్లు; byte++)
	    {
	      ఒకవేళ (బైట్లు_BIG_ENDIAN)
		bitpos = (wchar_బైట్లు - byte - 1) * charwidth;
	      లేకపోతే
		bitpos = byte * charwidth;
	      val[bitpos / HOST_బిట్లు_చొప్పున_WIDE_INT]
		|= ((గుర్తులేని HOST_WIDE_INT) ((గుర్తులేని అక్షరం) *p++))
		   << (bitpos % HOST_బిట్లు_చొప్పున_WIDE_INT);
	    }
	}

      ఒకవేళ (!TYPE_UNSIGNED (type))
	{
	  bitpos = ((wchar_బైట్లు - 1) * charwidth) + HOST_బిట్లు_చొప్పున_CHAR;
	  ఒకవేళ (bitpos < HOST_బిట్లు_చొప్పున_WIDE_INT)
	    {
	      ఒకవేళ (val[0] & (HOST_WIDE_INT_1 << (bitpos - 1)))
		{
		  val[0] |= HOST_WIDE_INT_M1U << bitpos;
		  val[1] = -1;
		}
	    }
	  లేకపోతే ఒకవేళ (bitpos == HOST_బిట్లు_చొప్పున_WIDE_INT)
	    {
	      ఒకవేళ (val[0] < 0)
		val[1] = -1;
	    }
	  లేకపోతే ఒకవేళ (val[1] & (HOST_WIDE_INT_1
			     << (bitpos - 1 - HOST_బిట్లు_చొప్పున_WIDE_INT)))
	    val[1] |= HOST_WIDE_INT_M1U << (bitpos - HOST_బిట్లు_చొప్పున_WIDE_INT);
	}

      విలువ = wide_int_గమ్యం_వృక్షం (type,
				wide_int::from_array (val, 2,
						      HOST_బిట్లు_చొప్పున_WIDE_INT * 2));
      కూడు_pending_init (ఆదానం_location, purpose, విలువ, NULL_వృక్షం, నిజం,
                        braced_init_obstack);
    }

  constructor_incremental = 0;
}

/* Return value of FIELD in pending initializer or NULL_TREE if the field was
   not initialized yet.  */

స్థిర వృక్షం
కనుగొను_init_member (వృక్షం క్షేత్రం_2, నిర్మాణం obstack * braced_init_obstack)
{
  నిర్మాణం init_కణుపు *p;

  ఒకవేళ (వృక్షం_సంకేతం (constructor_type) == ARRAY_TYPE)
    {
      ఒకవేళ (constructor_incremental
	  && వృక్షం_int_cst_lt (క్షేత్రం_2, constructor_unfilled_సూచీ))
	సమితి_nonincremental_init (braced_init_obstack);

      p = constructor_pending_elts;
      అయితే (p)
	{
	  ఒకవేళ (వృక్షం_int_cst_lt (క్షేత్రం_2, p->purpose))
	    p = p->ఎడమ;
	  లేకపోతే ఒకవేళ (వృక్షం_int_cst_lt (p->purpose, క్షేత్రం_2))
	    p = p->కుడి;
	  లేకపోతే
	    తిరిగి p->విలువ;
	}
    }
  లేకపోతే ఒకవేళ (వృక్షం_సంకేతం (constructor_type) == రికార్డు_TYPE)
    {
      వృక్షం bitpos = బిట్టు_position (క్షేత్రం_2);

      ఒకవేళ (constructor_incremental
	  && (!constructor_unfilled_fields
	      || వృక్షం_int_cst_lt (bitpos,
				  బిట్టు_position (constructor_unfilled_fields))))
	సమితి_nonincremental_init (braced_init_obstack);

      p = constructor_pending_elts;
      అయితే (p)
	{
	  ఒకవేళ (క్షేత్రం_2 == p->purpose)
	    తిరిగి p->విలువ;
	  లేకపోతే ఒకవేళ (వృక్షం_int_cst_lt (bitpos, బిట్టు_position (p->purpose)))
	    p = p->ఎడమ;
	  లేకపోతే
	    p = p->కుడి;
	}
    }
  లేకపోతే ఒకవేళ (వృక్షం_సంకేతం (constructor_type) == UNION_TYPE)
    {
      ఒకవేళ (!vec_సురక్షిత_is_ఖాళీలు (constructor_elements)
	  && (constructor_elements->చివరి ().సూచీ == క్షేత్రం_2))
	తిరిగి constructor_elements->చివరి ().విలువ;
    }
  తిరిగి NULL_వృక్షం;
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

స్థిర శూన్య
output_init_element (location_t loc, వృక్షం విలువ, వృక్షం origtype,
		     తార్కిక strict_string, వృక్షం type, వృక్షం క్షేత్రం_2, తార్కిక pending,
		     తార్కిక implicit, నిర్మాణం obstack * braced_init_obstack)
{
  వృక్షం semantic_type = NULL_వృక్షం;
  తార్కిక maybe_const = నిజం;
  తార్కిక npc, int_const_సమాసం, arith_const_సమాసం;

  ఒకవేళ (type == error_mark_కణుపు || విలువ == error_mark_కణుపు)
    {
      constructor_erroneous = 1;
      తిరిగి;
    }
  ఒకవేళ (వృక్షం_సంకేతం (వృక్షం_TYPE (విలువ)) == ARRAY_TYPE
      && (వృక్షం_సంకేతం (విలువ) == STRING_CST
	  || వృక్షం_సంకేతం (విలువ) == COMPOUND_LITERAL_సమాసం)
      && !(వృక్షం_సంకేతం (విలువ) == STRING_CST
	   && వృక్షం_సంకేతం (type) == ARRAY_TYPE
	   && INTEGRAL_TYPE_P (వృక్షం_TYPE (type)))
      && !comptypes (TYPE_MAIN_VARIANT (వృక్షం_TYPE (విలువ)),
		     TYPE_MAIN_VARIANT (type)))
    విలువ = array_గమ్యం_సూచిక_conversion (ఆదానం_location, విలువ);

  ఒకవేళ (వృక్షం_సంకేతం (విలువ) == COMPOUND_LITERAL_సమాసం
      && require_constant_విలువ && pending)
    {
      /* As an extension, allow initializing objects with static storage
	 duration with compound literals (which are then treated just as
	 the brace enclosed list they contain).  */
      ఒకవేళ (flag_isoc99)
	pedwarn_init (loc, OPT_Wpedantic, "initializer element is not "
		      "constant");
      వృక్షం decl = COMPOUND_LITERAL_సమాసం_DECL (విలువ);
      విలువ = DECL_INITIAL (decl);
    }

  npc = null_సూచిక_constant_p (విలువ);
  int_const_సమాసం = (వృక్షం_సంకేతం (విలువ) == INTEGER_CST
		    && !వృక్షం_అధికప్రవాహం (విలువ)
		    && INTEGRAL_TYPE_P (వృక్షం_TYPE (విలువ)));
  /* Not fully determined before folding.  */
  arith_const_సమాసం = నిజం;
  ఒకవేళ (వృక్షం_సంకేతం (విలువ) == EXCESS_PRECISION_సమాసం)
    {
      semantic_type = వృక్షం_TYPE (విలువ);
      విలువ = వృక్షం_నిర్వాహ్యం (విలువ, 0);
    }
  విలువ = c_fully_fold (విలువ, require_constant_విలువ, &maybe_const);
  /* TODO: this may not detect all cases of expressions folding to
     constants that are not arithmetic constant expressions.  */
  ఒకవేళ (!maybe_const)
    arith_const_సమాసం = అబద్ధం;
  లేకపోతే ఒకవేళ (!INTEGRAL_TYPE_P (వృక్షం_TYPE (విలువ))
	   && వృక్షం_సంకేతం (వృక్షం_TYPE (విలువ)) != REAL_TYPE
	   && వృక్షం_సంకేతం (వృక్షం_TYPE (విలువ)) != COMPLEX_TYPE)
    arith_const_సమాసం = అబద్ధం;
  లేకపోతే ఒకవేళ (వృక్షం_సంకేతం (విలువ) != INTEGER_CST
	   && వృక్షం_సంకేతం (విలువ) != REAL_CST
	   && వృక్షం_సంకేతం (విలువ) != COMPLEX_CST
	   && వృక్షం_సంకేతం (విలువ) != RAW_దత్తాంశం_CST)
    arith_const_సమాసం = అబద్ధం;
  లేకపోతే ఒకవేళ (వృక్షం_అధికప్రవాహం (విలువ))
    arith_const_సమాసం = అబద్ధం;

  ఒకవేళ (విలువ == error_mark_కణుపు)
    constructor_erroneous = 1;
  లేకపోతే ఒకవేళ (!వృక్షం_CONSTANT (విలువ))
    constructor_constant = 0;
  లేకపోతే ఒకవేళ (!initializer_constant_valid_p (విలువ,
					  వృక్షం_TYPE (విలువ),
					  AGGREGATE_TYPE_P (constructor_type)
					  && TYPE_తిరగేయి_STORAGE_క్రమం
					     (constructor_type))
	   || (రికార్డు_OR_UNION_TYPE_P (constructor_type)
	       && DECL_C_బిట్టు_క్షేత్రం (క్షేత్రం_2)
	       && వృక్షం_సంకేతం (విలువ) != INTEGER_CST))
    constructor_simple = 0;
  ఒకవేళ (!maybe_const)
    constructor_nonconst = 1;

  /* Digest the initializer and issue any errors about incompatible
     types before issuing errors about non-constant initializers.  */
  వృక్షం new_విలువ = విలువ;
  ఒకవేళ (semantic_type)
    new_విలువ = build1 (EXCESS_PRECISION_సమాసం, semantic_type, విలువ);
  /* In the case of braces around a scalar initializer, the result of
     this initializer processing goes through digest_init again at the
     outer level.  In the case of a constexpr initializer for a
     pointer, avoid converting a null pointer constant to something
     that is not a null pointer constant to avoid a spurious error
     from that second processing.  */
  ఒకవేళ (!require_constexpr_విలువ
      || !npc
      || వృక్షం_సంకేతం (constructor_type) != సూచిక_TYPE)
    new_విలువ = digest_init (loc,
			     రికార్డు_OR_UNION_TYPE_P (constructor_type)
			     ? క్షేత్రం_2 : constructor_fields
			     ? constructor_fields : constructor_decl,
			     type, new_విలువ, origtype, npc,
			     int_const_సమాసం, arith_const_సమాసం, strict_string,
			     require_constant_విలువ, require_constexpr_విలువ);
  ఒకవేళ (new_విలువ == error_mark_కణుపు)
    {
      constructor_erroneous = 1;
      తిరిగి;
    }
  ఒకవేళ (require_constant_విలువ || require_constant_elements)
    constant_వ్యక్తీకరణ_warning (new_విలువ);

  /* Proceed to check the constness of the original initializer.  */
  ఒకవేళ (!initializer_constant_valid_p (విలువ, వృక్షం_TYPE (విలువ)))
    {
      ఒకవేళ (require_constant_విలువ)
	{
	  error_init (loc, "initializer element is not constant");
	  విలువ = error_mark_కణుపు;
	}
      లేకపోతే ఒకవేళ (require_constant_elements)
	pedwarn (loc, OPT_Wpedantic,
		 "initializer element is not computable at load time");
    }
  లేకపోతే ఒకవేళ (!maybe_const
	   && (require_constant_విలువ || require_constant_elements))
    pedwarn_init (loc, OPT_Wpedantic,
		  "initializer element is not a constant expression");
  /* digest_init has already carried out the additional checks
     required for 'constexpr' initializers (using the information
     passed to it about whether the original initializer was certain
     kinds of constant expression), so that check does not need to be
     repeated here.  */

  /* Issue -Wc++-compat warnings about initializing a bitfield with
     enum type.  */
  ఒకవేళ (warn_cxx_compat
      && క్షేత్రం_2 != NULL_వృక్షం
      && వృక్షం_సంకేతం (క్షేత్రం_2) == క్షేత్రం_DECL
      && DECL_బిట్టు_క్షేత్రం_TYPE (క్షేత్రం_2) != NULL_వృక్షం
      && (TYPE_MAIN_VARIANT (DECL_బిట్టు_క్షేత్రం_TYPE (క్షేత్రం_2))
	  != TYPE_MAIN_VARIANT (type))
      && వృక్షం_సంకేతం (DECL_బిట్టు_క్షేత్రం_TYPE (క్షేత్రం_2)) == ENUMERAL_TYPE)
    {
      వృక్షం checktype = origtype != NULL_వృక్షం ? origtype : వృక్షం_TYPE (విలువ);
      ఒకవేళ (checktype != error_mark_కణుపు
	  && (TYPE_MAIN_VARIANT (checktype)
	      != TYPE_MAIN_VARIANT (DECL_బిట్టు_క్షేత్రం_TYPE (క్షేత్రం_2))))
	warning_init (loc, OPT_Wc___compat,
		      "enum conversion in initialization is invalid in C++");
    }

  /* If this field is empty and does not have side effects (and is not at
     the end of structure), don't do anything other than checking the
     initializer.  */
  ఒకవేళ (క్షేత్రం_2
      && (వృక్షం_TYPE (క్షేత్రం_2) == error_mark_కణుపు
	  || (COMPLETE_TYPE_P (వృక్షం_TYPE (క్షేత్రం_2))
	      && integer_zerop (TYPE_కొలత (వృక్షం_TYPE (క్షేత్రం_2)))
	      && !వృక్షం_SIDE_EFFECTS (new_విలువ)
	      && (వృక్షం_సంకేతం (constructor_type) == ARRAY_TYPE
		  || DECL_CHAIN (క్షేత్రం_2)))))
    తిరిగి;

  /* Finally, set VALUE to the initializer value digested above.  */
  విలువ = new_విలువ;

  /* If this element doesn't come next in sequence,
     put it on constructor_pending_elts.  */
  ఒకవేళ (వృక్షం_సంకేతం (constructor_type) == ARRAY_TYPE
      && (!constructor_incremental
	  || !వృక్షం_int_cst_equal (క్షేత్రం_2, constructor_unfilled_సూచీ)
	  || (వృక్షం_సంకేతం (విలువ) == RAW_దత్తాంశం_CST
	      && constructor_pending_elts
	      && pending)))
    {
      ఒకవేళ (constructor_incremental
	  && (వృక్షం_int_cst_lt (క్షేత్రం_2, constructor_unfilled_సూచీ)
	      || (వృక్షం_సంకేతం (విలువ) == RAW_దత్తాంశం_CST
		  && constructor_pending_elts
		  && pending)))
	సమితి_nonincremental_init (braced_init_obstack);

      కూడు_pending_init (loc, క్షేత్రం_2, విలువ, origtype, implicit,
			braced_init_obstack);
      తిరిగి;
    }
  లేకపోతే ఒకవేళ (వృక్షం_సంకేతం (constructor_type) == రికార్డు_TYPE
	   && (!constructor_incremental
	       || క్షేత్రం_2 != constructor_unfilled_fields))
    {
      /* We do this for records but not for unions.  In a union,
	 no matter which field is specified, it can be initialized
	 right away since it starts at the beginning of the union.  */
      ఒకవేళ (constructor_incremental)
	{
	  ఒకవేళ (!constructor_unfilled_fields)
	    సమితి_nonincremental_init (braced_init_obstack);
	  లేకపోతే
	    {
	      వృక్షం bitpos, unfillpos;

	      bitpos = బిట్టు_position (క్షేత్రం_2);
	      unfillpos = బిట్టు_position (constructor_unfilled_fields);

	      ఒకవేళ (వృక్షం_int_cst_lt (bitpos, unfillpos))
		సమితి_nonincremental_init (braced_init_obstack);
	    }
	}

      కూడు_pending_init (loc, క్షేత్రం_2, విలువ, origtype, implicit,
			braced_init_obstack);
      తిరిగి;
    }
  లేకపోతే ఒకవేళ (వృక్షం_సంకేతం (constructor_type) == UNION_TYPE
	   && !vec_సురక్షిత_is_ఖాళీలు (constructor_elements))
    {
      ఒకవేళ (!implicit)
	{
	  ఒకవేళ (వృక్షం_SIDE_EFFECTS (constructor_elements->చివరి ().విలువ))
	    warning_init (loc, OPT_Woverride_init_side_effects,
			  "initialized field with side-effects overwritten");
	  లేకపోతే ఒకవేళ (warn_override_init)
	    warning_init (loc, OPT_Woverride_init,
			  "initialized field overwritten");
	}

      /* We can have just one union field set.  */
      constructor_elements = ఖాళీ;
    }

  /* Otherwise, output this element either to
     constructor_elements or to the assembler file.  */

  constructor_elt celt = {క్షేత్రం_2, విలువ};
  vec_సురక్షిత_నెట్టు (constructor_elements, celt);

  /* Advance the variable that indicates sequential elements output.  */
  ఒకవేళ (వృక్షం_సంకేతం (constructor_type) == ARRAY_TYPE)
    {
      వృక్షం inc = bitsize_one_కణుపు;
      ఒకవేళ (విలువ && వృక్షం_సంకేతం (విలువ) == RAW_దత్తాంశం_CST)
	inc = bitsize_int (RAW_దత్తాంశం_నిడివి (విలువ));
      constructor_unfilled_సూచీ
	= కొలత_binop_loc (ఆదానం_location, PLUS_సమాసం,
			  constructor_unfilled_సూచీ, inc);
    }
  లేకపోతే ఒకవేళ (వృక్షం_సంకేతం (constructor_type) == రికార్డు_TYPE)
    {
      constructor_unfilled_fields
	= DECL_CHAIN (constructor_unfilled_fields);

      /* Skip any nameless bit fields.  */
      అయితే (constructor_unfilled_fields != NULL_వృక్షం
	     && DECL_UNNAMED_బిట్టు_క్షేత్రం (constructor_unfilled_fields))
	constructor_unfilled_fields
	  = DECL_CHAIN (constructor_unfilled_fields);
    }
  లేకపోతే ఒకవేళ (వృక్షం_సంకేతం (constructor_type) == UNION_TYPE)
    constructor_unfilled_fields = NULL_వృక్షం;

  /* Now output any pending elements which have become next.  */
  ఒకవేళ (pending)
    output_pending_init_elements (0, braced_init_obstack);
}

/* For two FIELD_DECLs in the same chain, return -1 if field1
   comes before field2, 1 if field1 comes after field2 and
   0 if field1 == field2.  */

స్థిర పూర్ణాంకం
init_క్షేత్రం_decl_cmp (వృక్షం field1, వృక్షం field2)
{
  ఒకవేళ (field1 == field2)
    తిరిగి 0;

  వృక్షం bitpos1 = బిట్టు_position (field1);
  వృక్షం bitpos2 = బిట్టు_position (field2);
  ఒకవేళ (వృక్షం_int_cst_equal (bitpos1, bitpos2))
    {
      /* If one of the fields has non-zero bitsize, then that
	 field must be the last one in a sequence of zero
	 sized fields, fields after it will have bigger
	 bit_position.  */
      ఒకవేళ (వృక్షం_TYPE (field1) != error_mark_కణుపు
	  && COMPLETE_TYPE_P (వృక్షం_TYPE (field1))
	  && integer_nonzerop (వృక్షం_TYPE (field1)))
	తిరిగి 1;
      ఒకవేళ (వృక్షం_TYPE (field2) != error_mark_కణుపు
	  && COMPLETE_TYPE_P (వృక్షం_TYPE (field2))
	  && integer_nonzerop (వృక్షం_TYPE (field2)))
	తిరిగి -1;
      /* Otherwise, fallback to DECL_CHAIN walk to find out
	 which field comes earlier.  Walk chains of both
	 fields, so that if field1 and field2 are close to each
	 other in either order, it is found soon even for large
	 sequences of zero sized fields.  */
      వృక్షం f1 = field1, f2 = field2;
      అయితే (1)
	{
	  f1 = DECL_CHAIN (f1);
	  f2 = DECL_CHAIN (f2);
	  ఒకవేళ (f1 == NULL_వృక్షం)
	    {
	      gcc_assert (f2);
	      తిరిగి 1;
	    }
	  ఒకవేళ (f2 == NULL_వృక్షం)
	    తిరిగి -1;
	  ఒకవేళ (f1 == field2)
	    తిరిగి -1;
	  ఒకవేళ (f2 == field1)
	    తిరిగి 1;
	  ఒకవేళ (!వృక్షం_int_cst_equal (బిట్టు_position (f1), bitpos1))
	    తిరిగి 1;
	  ఒకవేళ (!వృక్షం_int_cst_equal (బిట్టు_position (f2), bitpos1))
	    తిరిగి -1;
	}
    }
  లేకపోతే ఒకవేళ (వృక్షం_int_cst_lt (bitpos1, bitpos2))
    తిరిగి -1;
  లేకపోతే
    తిరిగి 1;
}

/* Output any pending elements which have become next.
   As we output elements, constructor_unfilled_{fields,index}
   advances, which may cause other elements to become next;
   if so, they too are output.

   If ALL is 0, we return when there are
   no more pending elements to output now.

   If ALL is 1, we output space as necessary so that
   we can output all the pending elements.  */
స్థిర శూన్య
output_pending_init_elements (పూర్ణాంకం all, నిర్మాణం obstack * braced_init_obstack)
{
  నిర్మాణం init_కణుపు *elt = constructor_pending_elts;
  వృక్షం తదుపరి;

 retry:

  /* Look through the whole pending tree.
     If we find an element that should be output now,
     output it.  Otherwise, set NEXT to the element
     that comes first among those still pending.  */

  తదుపరి = NULL_వృక్షం;
  అయితే (elt)
    {
      ఒకవేళ (వృక్షం_సంకేతం (constructor_type) == ARRAY_TYPE)
	{
	  ఒకవేళ (వృక్షం_int_cst_equal (elt->purpose,
				  constructor_unfilled_సూచీ))
	    output_init_element (ఆదానం_location, elt->విలువ, elt->origtype,
				 నిజం, వృక్షం_TYPE (constructor_type),
				 constructor_unfilled_సూచీ, అబద్ధం, అబద్ధం,
				 braced_init_obstack);
	  లేకపోతే ఒకవేళ (వృక్షం_int_cst_lt (constructor_unfilled_సూచీ,
				    elt->purpose))
	    {
	      /* Advance to the next smaller node.  */
	      ఒకవేళ (elt->ఎడమ)
		elt = elt->ఎడమ;
	      లేకపోతే
		{
		  /* We have reached the smallest node bigger than the
		     current unfilled index.  Fill the space first.  */
		  తదుపరి = elt->purpose;
		  ఆపు;
		}
	    }
	  లేకపోతే
	    {
	      /* Advance to the next bigger node.  */
	      ఒకవేళ (elt->కుడి)
		elt = elt->కుడి;
	      లేకపోతే
		{
		  /* We have reached the biggest node in a subtree.  Find
		     the parent of it, which is the next bigger node.  */
		  అయితే (elt->మాతృ && elt->మాతృ->కుడి == elt)
		    elt = elt->మాతృ;
		  elt = elt->మాతృ;
		  ఒకవేళ (elt && వృక్షం_int_cst_lt (constructor_unfilled_సూచీ,
					      elt->purpose))
		    {
		      తదుపరి = elt->purpose;
		      ఆపు;
		    }
		}
	    }
	}
      లేకపోతే ఒకవేళ (రికార్డు_OR_UNION_TYPE_P (constructor_type))
	{
	  /* If the current record is complete we are done.  */
	  ఒకవేళ (constructor_unfilled_fields == NULL_వృక్షం)
	    ఆపు;

	  పూర్ణాంకం cmp = init_క్షేత్రం_decl_cmp (constructor_unfilled_fields,
					 elt->purpose);
	  ఒకవేళ (cmp == 0)
	    output_init_element (ఆదానం_location, elt->విలువ, elt->origtype,
				 నిజం, వృక్షం_TYPE (elt->purpose),
				 elt->purpose, అబద్ధం, అబద్ధం,
				 braced_init_obstack);
	  లేకపోతే ఒకవేళ (cmp < 0)
	    {
	      /* Advance to the next smaller node.  */
	      ఒకవేళ (elt->ఎడమ)
		elt = elt->ఎడమ;
	      లేకపోతే
		{
		  /* We have reached the smallest node bigger than the
		     current unfilled field.  Fill the space first.  */
		  తదుపరి = elt->purpose;
		  ఆపు;
		}
	    }
	  లేకపోతే
	    {
	      /* Advance to the next bigger node.  */
	      ఒకవేళ (elt->కుడి)
		elt = elt->కుడి;
	      లేకపోతే
		{
		  /* We have reached the biggest node in a subtree.  Find
		     the parent of it, which is the next bigger node.  */
		  అయితే (elt->మాతృ && elt->మాతృ->కుడి == elt)
		    elt = elt->మాతృ;
		  elt = elt->మాతృ;
		  ఒకవేళ (elt
		      && init_క్షేత్రం_decl_cmp (constructor_unfilled_fields,
					      elt->purpose) < 0)
		    {
		      తదుపరి = elt->purpose;
		      ఆపు;
		    }
		}
	    }
	}
    }

  /* Ordinarily return, but not if we want to output all
     and there are elements left.  */
  ఒకవేళ (!(all && తదుపరి != NULL_వృక్షం))
    తిరిగి;

  /* If it's not incremental, just skip over the gap, so that after
     jumping to retry we will output the next successive element.  */
  ఒకవేళ (రికార్డు_OR_UNION_TYPE_P (constructor_type))
    constructor_unfilled_fields = తదుపరి;
  లేకపోతే ఒకవేళ (వృక్షం_సంకేతం (constructor_type) == ARRAY_TYPE)
    constructor_unfilled_సూచీ = తదుపరి;

  /* ELT now points to the node in the pending tree with the next
     initializer to output.  */
  వెళ్ళు retry;
}

/* Expression VALUE coincides with the start of type TYPE in a braced
   initializer.  Return true if we should treat VALUE as initializing
   the first element of TYPE, false if we should treat it as initializing
   TYPE as a whole.

   If the initializer is clearly invalid, the question becomes:
   which choice gives the best error message?  */

స్థిర తార్కిక
initialize_elementwise_p (వృక్షం type, వృక్షం విలువ)
{
  ఒకవేళ (type == error_mark_కణుపు || విలువ == error_mark_కణుపు)
    తిరిగి అబద్ధం;

  gcc_checking_assert (TYPE_MAIN_VARIANT (type) == type);

  వృక్షం విలువ_type = వృక్షం_TYPE (విలువ);
  ఒకవేళ (విలువ_type == error_mark_కణుపు)
    తిరిగి అబద్ధం;

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
  ఒకవేళ (gnu_సదిశ_type_p (type))
    తిరిగి !సదిశ_TYPE_P (విలువ_type);

  ఒకవేళ (AGGREGATE_TYPE_P (type))
    తిరిగి !comptypes (type, TYPE_MAIN_VARIANT (విలువ_type));

  తిరిగి అబద్ధం;
}

/* Helper function for process_init_element.  Split first element of
   RAW_DATA_CST and save the rest to *RAW_DATA.  */

స్థిర అంతఃవరుస వృక్షం
maybe_విభజించు_raw_దత్తాంశం (వృక్షం విలువ, వృక్షం *raw_దత్తాంశం)
{
  ఒకవేళ (విలువ == NULL_వృక్షం || వృక్షం_సంకేతం (విలువ) != RAW_దత్తాంశం_CST)
    తిరిగి విలువ;
  *raw_దత్తాంశం = విలువ;
  విలువ = build_int_cst (integer_type_కణుపు,
			 RAW_దత్తాంశం_UCHAR_ELT (*raw_దత్తాంశం, 0));
  ++RAW_దత్తాంశం_సూచిక (*raw_దత్తాంశం);
  --RAW_దత్తాంశం_నిడివి (*raw_దత్తాంశం);
  తిరిగి విలువ;
}

/* Return non-zero if c_parser_initval should attempt to optimize
   large initializers into RAW_DATA_CST.  In that case return how
   many elements to optimize at most.  */

గుర్తులేని
c_maybe_optimize_large_byte_initializer (శూన్య)
{
  ఒకవేళ (!constructor_type
      || వృక్షం_సంకేతం (constructor_type) != ARRAY_TYPE
      || constructor_దొంతర->implicit)
    తిరిగి 0;
  వృక్షం elttype = TYPE_MAIN_VARIANT (వృక్షం_TYPE (constructor_type));
  ఒకవేళ (వృక్షం_సంకేతం (elttype) != INTEGER_TYPE
      && వృక్షం_సంకేతం (elttype) != BITINT_TYPE)
    తిరిగి 0;
  ఒకవేళ (TYPE_PRECISION (elttype) != CHAR_బిట్టు
      || constructor_దొంతర->replacement_విలువ.విలువ
      || (COMPLETE_TYPE_P (constructor_type)
	  && !poly_int_వృక్షం_p (TYPE_కొలత (constructor_type)))
      || constructor_range_దొంతర)
    తిరిగి 0;
  ఒకవేళ (constructor_max_సూచీ == NULL_వృక్షం)
    తిరిగి గరిష్ఠ_పూర్ణాంకం;
  ఒకవేళ (వృక్షం_int_cst_le (constructor_max_సూచీ, constructor_సూచీ)
      || integer_all_onesp (constructor_max_సూచీ))
    తిరిగి 0;
  widest_int w = wi::గమ్యం_widest (constructor_max_సూచీ);
  w -= wi::గమ్యం_widest (constructor_సూచీ);
  w += 1;
  ఒకవేళ (w < 64)
    తిరిగి 0;
  ఒకవేళ (w > గరిష్ఠ_పూర్ణాంకం)
    తిరిగి గరిష్ఠ_పూర్ణాంకం;
  తిరిగి w.గమ్యం_uhwi ();
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

శూన్య
process_init_element (location_t loc, నిర్మాణం c_సమాసం విలువ, తార్కిక implicit,
		      నిర్మాణం obstack * braced_init_obstack)
{
  వృక్షం orig_విలువ = విలువ.విలువ;
  పూర్ణాంకం string_flag
    = (orig_విలువ != NULL_వృక్షం && వృక్షం_సంకేతం (orig_విలువ) == STRING_CST);
  తార్కిక strict_string = విలువ.original_సంకేతం == STRING_CST;
  తార్కిక was_designated = designator_లోతు != 0;
  వృక్షం raw_దత్తాంశం = NULL_వృక్షం;

retry:
  designator_లోతు = 0;
  designator_erroneous = 0;

  ఒకవేళ (!implicit && విలువ.విలువ && !integer_zerop (విలువ.విలువ))
    constructor_zeroinit = 0;

  /* Handle superfluous braces around string cst as in
     char x[] = {"foo"}; */
  ఒకవేళ (constructor_type
      && !was_designated
      && వృక్షం_సంకేతం (constructor_type) == ARRAY_TYPE
      && INTEGRAL_TYPE_P (వృక్షం_TYPE (constructor_type))
      && integer_zerop (constructor_unfilled_సూచీ))
    {
      ఒకవేళ (constructor_దొంతర->replacement_విలువ.విలువ)
	{
	  error_init (loc, "excess elements in %qT initializer", constructor_type);
	  తిరిగి;
	}
      లేకపోతే ఒకవేళ (string_flag)
	{
	  constructor_దొంతర->replacement_విలువ = విలువ;
	  తిరిగి;
	}
    }

  ఒకవేళ (constructor_దొంతర->replacement_విలువ.విలువ != NULL_వృక్షం)
    {
      error_init (loc, "excess elements in struct initializer");
      తిరిగి;
    }

  /* Ignore elements of a brace group if it is entirely superfluous
     and has already been diagnosed, or if the type is erroneous.  */
  ఒకవేళ (constructor_type == NULL_వృక్షం || constructor_type == error_mark_కణుపు)
    తిరిగి;

  /* Ignore elements of an initializer for a variable-size type.
     Those are diagnosed in the parser (empty initializer braces are OK).  */
  ఒకవేళ (COMPLETE_TYPE_P (constructor_type)
      && !poly_int_వృక్షం_p (TYPE_కొలత (constructor_type)))
    తిరిగి;

  ఒకవేళ (!implicit && warn_designated_init && !was_designated
      && వృక్షం_సంకేతం (constructor_type) == రికార్డు_TYPE
      && lookup_attribute ("designated_init",
			   TYPE_లక్షణాలు (constructor_type)))
    warning_init (loc,
		  OPT_Wdesignated_init,
		  "positional initialization of field "
		  "in %<struct%> declared with %<designated_init%> attribute");

  /* If we've exhausted any levels that didn't have braces,
     pop them now.  */
  అయితే (constructor_దొంతర->implicit)
    {
      ఒకవేళ (రికార్డు_OR_UNION_TYPE_P (constructor_type)
	  && constructor_fields == NULL_వృక్షం)
	process_init_element (loc,
			      తీయి_init_level (loc, 1, braced_init_obstack,
					      చివరి_init_list_comma),
			      నిజం, braced_init_obstack);
      లేకపోతే ఒకవేళ ((వృక్షం_సంకేతం (constructor_type) == ARRAY_TYPE
		|| gnu_సదిశ_type_p (constructor_type))
	       && constructor_max_సూచీ
	       && వృక్షం_int_cst_lt (constructor_max_సూచీ,
				   constructor_సూచీ))
	process_init_element (loc,
			      తీయి_init_level (loc, 1, braced_init_obstack,
					      చివరి_init_list_comma),
			      నిజం, braced_init_obstack);
      లేకపోతే
	ఆపు;
    }

  /* In the case of [LO ... HI] = VALUE, only evaluate VALUE once.  */
  ఒకవేళ (constructor_range_దొంతర)
    {
      /* If value is a compound literal and we'll be just using its
	 content, don't put it into a SAVE_EXPR.  */
      ఒకవేళ (వృక్షం_సంకేతం (విలువ.విలువ) != COMPOUND_LITERAL_సమాసం
	  || !require_constant_విలువ)
	{
	  వృక్షం semantic_type = NULL_వృక్షం;
	  ఒకవేళ (వృక్షం_సంకేతం (విలువ.విలువ) == EXCESS_PRECISION_సమాసం)
	    {
	      semantic_type = వృక్షం_TYPE (విలువ.విలువ);
	      విలువ.విలువ = వృక్షం_నిర్వాహ్యం (విలువ.విలువ, 0);
	    }
	  విలువ.విలువ = save_సమాసం (విలువ.విలువ);
	  ఒకవేళ (semantic_type)
	    విలువ.విలువ = build1 (EXCESS_PRECISION_సమాసం, semantic_type,
				  విలువ.విలువ);
	}
    }

  అయితే (1)
    {
      ఒకవేళ (వృక్షం_సంకేతం (constructor_type) == రికార్డు_TYPE)
	{
	  వృక్షం fieldtype;
	  గణన వృక్షం_సంకేతం_2 fieldcode;

	  ఒకవేళ (constructor_fields == NULL_వృక్షం)
	    {
	      pedwarn_init (loc, 0, "excess elements in struct initializer");
	      ఆపు;
	    }

	  fieldtype = వృక్షం_TYPE (constructor_fields);
	  ఒకవేళ (fieldtype != error_mark_కణుపు)
	    fieldtype = TYPE_MAIN_VARIANT (fieldtype);
	  fieldcode = వృక్షం_సంకేతం (fieldtype);

	  /* Error for non-static initialization of a flexible array member.  */
	  ఒకవేళ (fieldcode == ARRAY_TYPE
	      && !require_constant_విలువ
	      && TYPE_కొలత (fieldtype) == NULL_వృక్షం
	      && DECL_CHAIN (constructor_fields) == NULL_వృక్షం)
	    {
	      error_init (loc, "non-static initialization of a flexible "
			  "array member");
	      ఆపు;
	    }

	  /* Error for initialization of a flexible array member with
	     a string constant if the structure is in an array.  E.g.:
	     struct S { int x; char y[]; };
	     struct S s[] = { { 1, "foo" } };
	     is invalid.  */
	  ఒకవేళ (string_flag
	      && fieldcode == ARRAY_TYPE
	      && constructor_లోతు > 1
	      && TYPE_కొలత (fieldtype) == NULL_వృక్షం
	      && DECL_CHAIN (constructor_fields) == NULL_వృక్షం)
	    {
	      తార్కిక లోపల_array_p = అబద్ధం;
	      కొరకు (నిర్మాణం constructor_దొంతర *p = constructor_దొంతర;
		   p && p->type; p = p->తదుపరి)
		ఒకవేళ (వృక్షం_సంకేతం (p->type) == ARRAY_TYPE)
		  {
		    లోపల_array_p = నిజం;
		    ఆపు;
		  }
	      ఒకవేళ (లోపల_array_p)
		{
		  error_init (loc, "initialization of flexible array "
			      "member in a nested context");
		  ఆపు;
		}
	    }

	  /* Accept a string constant to initialize a subarray.  */
	  ఒకవేళ (విలువ.విలువ != NULL_వృక్షం
	      && fieldcode == ARRAY_TYPE
	      && INTEGRAL_TYPE_P (వృక్షం_TYPE (fieldtype))
	      && string_flag)
	    విలువ.విలువ = orig_విలువ;
	  /* Otherwise, if we have come to a subaggregate,
	     and we don't have an element of its type, push into it.  */
	  లేకపోతే ఒకవేళ (విలువ.విలువ != NULL_వృక్షం
		   && initialize_elementwise_p (fieldtype, విలువ.విలువ))
	    {
	      నెట్టు_init_level (loc, 1, braced_init_obstack);
	      కొనసాగు;
	    }

	  విలువ.విలువ = maybe_విభజించు_raw_దత్తాంశం (విలువ.విలువ, &raw_దత్తాంశం);
	  ఒకవేళ (విలువ.విలువ)
	    {
	      నెట్టు_member_name (constructor_fields);
	      output_init_element (loc, విలువ.విలువ, విలువ.original_type,
				   strict_string, fieldtype,
				   constructor_fields, నిజం, implicit,
				   braced_init_obstack);
	      RESTORE_SPELLING_లోతు (constructor_లోతు);
	    }
	  లేకపోతే
	    /* Do the bookkeeping for an element that was
	       directly output as a constructor.  */
	    {
	      /* For a record, keep track of end position of last field.  */
	      ఒకవేళ (DECL_కొలత (constructor_fields))
		constructor_బిట్టు_సూచీ
		  = కొలత_binop_loc (ఆదానం_location, PLUS_సమాసం,
				    బిట్టు_position (constructor_fields),
				    DECL_కొలత (constructor_fields));

	      /* If the current field was the first one not yet written out,
		 it isn't now, so update.  */
	      ఒకవేళ (constructor_unfilled_fields == constructor_fields)
		{
		  constructor_unfilled_fields = DECL_CHAIN (constructor_fields);
		  /* Skip any nameless bit fields.  */
		  అయితే (constructor_unfilled_fields != 0
			 && (DECL_UNNAMED_బిట్టు_క్షేత్రం
			     (constructor_unfilled_fields)))
		    constructor_unfilled_fields =
		      DECL_CHAIN (constructor_unfilled_fields);
		}
	    }

	  constructor_fields = DECL_CHAIN (constructor_fields);
	  /* Skip any nameless bit fields at the beginning.  */
	  అయితే (constructor_fields != NULL_వృక్షం
		 && DECL_UNNAMED_బిట్టు_క్షేత్రం (constructor_fields))
	    constructor_fields = DECL_CHAIN (constructor_fields);
	}
      లేకపోతే ఒకవేళ (వృక్షం_సంకేతం (constructor_type) == UNION_TYPE)
	{
	  వృక్షం fieldtype;
	  గణన వృక్షం_సంకేతం_2 fieldcode;

	  ఒకవేళ (constructor_fields == NULL_వృక్షం)
	    {
	      pedwarn_init (loc, 0,
			    "excess elements in union initializer");
	      ఆపు;
	    }

	  fieldtype = వృక్షం_TYPE (constructor_fields);
	  ఒకవేళ (fieldtype != error_mark_కణుపు)
	    fieldtype = TYPE_MAIN_VARIANT (fieldtype);
	  fieldcode = వృక్షం_సంకేతం (fieldtype);

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
	  ఒకవేళ (!లోపల_system_శీర్షిక_at (ఆదానం_location) && !constructor_designated
	      && !(విలువ.విలువ && (integer_zerop (విలువ.విలువ)
				   || real_zerop (విలువ.విలువ))))
	    warning (OPT_Wtraditional, "traditional C rejects initialization "
		     "of unions");

	  /* Error for non-static initialization of a flexible array member.  */
	  ఒకవేళ (fieldcode == ARRAY_TYPE
	      && !require_constant_విలువ
	      && TYPE_కొలత (fieldtype) == NULL_వృక్షం)
	    {
	      error_init (loc, "non-static initialization of a flexible "
			  "array member");
	      ఆపు;
	    }

	  /* Error for initialization of a flexible array member with
	     a string constant if the structure is in an array.  E.g.:
	     union U { int x; char y[]; };
	     union U s[] = { { 1, "foo" } };
	     is invalid.  */
	  ఒకవేళ (string_flag
	      && fieldcode == ARRAY_TYPE
	      && constructor_లోతు > 1
	      && TYPE_కొలత (fieldtype) == NULL_వృక్షం)
	    {
	      తార్కిక లోపల_array_p = అబద్ధం;
	      కొరకు (నిర్మాణం constructor_దొంతర *p = constructor_దొంతర;
		   p && p->type; p = p->తదుపరి)
		ఒకవేళ (వృక్షం_సంకేతం (p->type) == ARRAY_TYPE)
		  {
		    లోపల_array_p = నిజం;
		    ఆపు;
		  }
	      ఒకవేళ (లోపల_array_p)
		{
		  error_init (loc, "initialization of flexible array "
			      "member in a nested context");
		  ఆపు;
		}
	    }

	  /* Accept a string constant to initialize a subarray.  */
	  ఒకవేళ (విలువ.విలువ != NULL_వృక్షం
	      && fieldcode == ARRAY_TYPE
	      && INTEGRAL_TYPE_P (వృక్షం_TYPE (fieldtype))
	      && string_flag)
	    విలువ.విలువ = orig_విలువ;
	  /* Otherwise, if we have come to a subaggregate,
	     and we don't have an element of its type, push into it.  */
	  లేకపోతే ఒకవేళ (విలువ.విలువ != NULL_వృక్షం
		   && initialize_elementwise_p (fieldtype, విలువ.విలువ))
	    {
	      నెట్టు_init_level (loc, 1, braced_init_obstack);
	      కొనసాగు;
	    }

	  విలువ.విలువ = maybe_విభజించు_raw_దత్తాంశం (విలువ.విలువ, &raw_దత్తాంశం);
	  ఒకవేళ (విలువ.విలువ)
	    {
	      నెట్టు_member_name (constructor_fields);
	      output_init_element (loc, విలువ.విలువ, విలువ.original_type,
				   strict_string, fieldtype,
				   constructor_fields, నిజం, implicit,
				   braced_init_obstack);
	      RESTORE_SPELLING_లోతు (constructor_లోతు);
	    }
	  లేకపోతే
	    /* Do the bookkeeping for an element that was
	       directly output as a constructor.  */
	    {
	      constructor_బిట్టు_సూచీ = DECL_కొలత (constructor_fields);
	      constructor_unfilled_fields = DECL_CHAIN (constructor_fields);
	    }

	  constructor_fields = NULL_వృక్షం;
	}
      లేకపోతే ఒకవేళ (వృక్షం_సంకేతం (constructor_type) == ARRAY_TYPE)
	{
	  వృక్షం elttype = TYPE_MAIN_VARIANT (వృక్షం_TYPE (constructor_type));
	  గణన వృక్షం_సంకేతం_2 eltcode = వృక్షం_సంకేతం (elttype);

	  /* Accept a string constant to initialize a subarray.  */
	  ఒకవేళ (విలువ.విలువ != NULL_వృక్షం
	      && eltcode == ARRAY_TYPE
	      && INTEGRAL_TYPE_P (వృక్షం_TYPE (elttype))
	      && string_flag)
	    విలువ.విలువ = orig_విలువ;
	  /* Otherwise, if we have come to a subaggregate,
	     and we don't have an element of its type, push into it.  */
	  లేకపోతే ఒకవేళ (విలువ.విలువ != NULL_వృక్షం
		   && initialize_elementwise_p (elttype, విలువ.విలువ))
	    {
	      నెట్టు_init_level (loc, 1, braced_init_obstack);
	      కొనసాగు;
	    }

	  ఒకవేళ (constructor_max_సూచీ != NULL_వృక్షం
	      && (వృక్షం_int_cst_lt (constructor_max_సూచీ, constructor_సూచీ)
		  || integer_all_onesp (constructor_max_సూచీ))
	      /* For VLA we got an error already.  */
	      && !C_TYPE_VARIABLE_కొలత (constructor_type))
	    {
	      pedwarn_init (loc, 0,
			    "excess elements in array initializer");
	      ఆపు;
	    }

	  ఒకవేళ (విలువ.విలువ
	      && వృక్షం_సంకేతం (విలువ.విలువ) == RAW_దత్తాంశం_CST
	      && RAW_దత్తాంశం_నిడివి (విలువ.విలువ) > 1
	      && (వృక్షం_సంకేతం (elttype) == INTEGER_TYPE
		  || వృక్షం_సంకేతం (elttype) == BITINT_TYPE)
	      && TYPE_PRECISION (elttype) == CHAR_బిట్టు
	      && (constructor_max_సూచీ == NULL_వృక్షం
		  || వృక్షం_int_cst_lt (constructor_సూచీ,
				      constructor_max_సూచీ)))
	    {
	      గుర్తులేని పూర్ణాంకం len = RAW_దత్తాంశం_నిడివి (విలువ.విలువ);
	      ఒకవేళ (constructor_max_సూచీ)
		{
		  widest_int w = wi::గమ్యం_widest (constructor_max_సూచీ);
		  w -= wi::గమ్యం_widest (constructor_సూచీ);
		  w += 1;
		  ఒకవేళ (w < len)
		    len = w.గమ్యం_uhwi ();
		}
	      ఒకవేళ (len < (గుర్తులేని) RAW_దత్తాంశం_నిడివి (విలువ.విలువ))
		{
		  raw_దత్తాంశం = copy_కణుపు (విలువ.విలువ);
		  RAW_దత్తాంశం_నిడివి (raw_దత్తాంశం) -= len;
		  RAW_దత్తాంశం_సూచిక (raw_దత్తాంశం) += len;
		  RAW_దత్తాంశం_నిడివి (విలువ.విలువ) = len;
		}
	      వృక్షం_TYPE (విలువ.విలువ) = elttype;
	      నెట్టు_array_bounds (వృక్షం_గమ్యం_uhwi (constructor_సూచీ));
	      output_init_element (loc, విలువ.విలువ, విలువ.original_type,
				   అబద్ధం, elttype, constructor_సూచీ, నిజం,
				   implicit, braced_init_obstack);
	      RESTORE_SPELLING_లోతు (constructor_లోతు);
	      constructor_సూచీ
		= కొలత_binop_loc (ఆదానం_location, PLUS_సమాసం,
				  constructor_సూచీ, bitsize_int (len));
	    }
	  లేకపోతే
	    {
	      విలువ.విలువ = maybe_విభజించు_raw_దత్తాంశం (విలువ.విలువ, &raw_దత్తాంశం);
	      /* Now output the actual element.  */
	      ఒకవేళ (విలువ.విలువ)
		{
		  నెట్టు_array_bounds (వృక్షం_గమ్యం_uhwi (constructor_సూచీ));
		  output_init_element (loc, విలువ.విలువ, విలువ.original_type,
				       strict_string, elttype,
				       constructor_సూచీ, నిజం, implicit,
				       braced_init_obstack);
		  RESTORE_SPELLING_లోతు (constructor_లోతు);
		}

	      constructor_సూచీ
		= కొలత_binop_loc (ఆదానం_location, PLUS_సమాసం,
				  constructor_సూచీ, bitsize_one_కణుపు);

	      ఒకవేళ (!విలువ.విలువ)
		/* If we are doing the bookkeeping for an element that was
		   directly output as a constructor, we must update
		   constructor_unfilled_index.  */
		constructor_unfilled_సూచీ = constructor_సూచీ;
	    }
	}
      లేకపోతే ఒకవేళ (gnu_సదిశ_type_p (constructor_type))
	{
	  వృక్షం elttype = TYPE_MAIN_VARIANT (వృక్షం_TYPE (constructor_type));

	  /* Do a basic check of initializer size.  Note that vectors
	     may not always have a fixed size derived from their type.  */
	  ఒకవేళ (maybe_lt (వృక్షం_గమ్యం_poly_uint64 (constructor_max_సూచీ),
			వృక్షం_గమ్యం_poly_uint64 (constructor_సూచీ)))
	    {
	      /* Diagose VLA out-of-bounds as errors.  */
	      ఒకవేళ (వృక్షం_గమ్యం_poly_uint64 (constructor_max_సూచీ).is_constant())
		pedwarn_init (loc, 0,
			      "excess elements in vector initializer");
	      లేకపోతే
		error_init (loc, "excess elements in vector initializer");

	      ఆపు;
	    }

	  విలువ.విలువ = maybe_విభజించు_raw_దత్తాంశం (విలువ.విలువ, &raw_దత్తాంశం);
	  /* Now output the actual element.  */
	  ఒకవేళ (విలువ.విలువ)
	    {
	      ఒకవేళ (వృక్షం_సంకేతం (విలువ.విలువ) == సదిశ_CST)
		elttype = TYPE_MAIN_VARIANT (constructor_type);
	      output_init_element (loc, విలువ.విలువ, విలువ.original_type,
				   strict_string, elttype,
				   constructor_సూచీ, నిజం, implicit,
				   braced_init_obstack);
	    }

	  constructor_సూచీ
	    = కొలత_binop_loc (ఆదానం_location,
			      PLUS_సమాసం, constructor_సూచీ, bitsize_one_కణుపు);

	  ఒకవేళ (!విలువ.విలువ)
	    /* If we are doing the bookkeeping for an element that was
	       directly output as a constructor, we must update
	       constructor_unfilled_index.  */
	    constructor_unfilled_సూచీ = constructor_సూచీ;
	}

      /* Handle the sole element allowed in a braced initializer
	 for a scalar variable.  */
      లేకపోతే ఒకవేళ (constructor_type != error_mark_కణుపు
	       && constructor_fields == NULL_వృక్షం)
	{
	  pedwarn_init (loc, 0,
			"excess elements in scalar initializer");
	  ఆపు;
	}
      లేకపోతే
	{
	  విలువ.విలువ = maybe_విభజించు_raw_దత్తాంశం (విలువ.విలువ, &raw_దత్తాంశం);
	  ఒకవేళ (విలువ.విలువ)
	    output_init_element (loc, విలువ.విలువ, విలువ.original_type,
				 strict_string, constructor_type,
				 NULL_వృక్షం, నిజం, implicit,
				 braced_init_obstack);
	  constructor_fields = NULL_వృక్షం;
	}

      /* Handle range initializers either at this level or anywhere higher
	 in the designator stack.  */
      ఒకవేళ (constructor_range_దొంతర)
	{
	  నిర్మాణం constructor_range_దొంతర *p, *range_దొంతర;
	  పూర్ణాంకం ముగింపు = 0;

	  range_దొంతర = constructor_range_దొంతర;
	  constructor_range_దొంతర = 0;
	  అయితే (constructor_దొంతర != range_దొంతర->దొంతర)
	    {
	      gcc_assert (constructor_దొంతర->implicit);
	      process_init_element (loc,
				    తీయి_init_level (loc, 1,
						    braced_init_obstack,
						    చివరి_init_list_comma),
				    నిజం, braced_init_obstack);
	    }
	  కొరకు (p = range_దొంతర;
	       !p->range_చివర || వృక్షం_int_cst_equal (p->సూచీ, p->range_చివర);
	       p = p->prev)
	    {
	      gcc_assert (constructor_దొంతర->implicit);
	      process_init_element (loc,
				    తీయి_init_level (loc, 1,
						    braced_init_obstack,
						    చివరి_init_list_comma),
				    నిజం, braced_init_obstack);
	    }

	  p->సూచీ = కొలత_binop_loc (ఆదానం_location,
				     PLUS_సమాసం, p->సూచీ, bitsize_one_కణుపు);
	  ఒకవేళ (వృక్షం_int_cst_equal (p->సూచీ, p->range_చివర) && !p->prev)
	    ముగింపు = 1;

	  అయితే (1)
	    {
	      constructor_సూచీ = p->సూచీ;
	      constructor_fields = p->fields;
	      ఒకవేళ (ముగింపు && p->range_చివర && p->సూచీ == p->range_ప్రారంభం)
		{
		  ముగింపు = 0;
		  p->prev = 0;
		}
	      p = p->తదుపరి;
	      ఒకవేళ (!p)
		ఆపు;
	      ముగింపు_implicit_inits (loc, braced_init_obstack);
	      నెట్టు_init_level (loc, 2, braced_init_obstack);
	      p->దొంతర = constructor_దొంతర;
	      ఒకవేళ (p->range_చివర && వృక్షం_int_cst_equal (p->సూచీ, p->range_చివర))
		p->సూచీ = p->range_ప్రారంభం;
	    }

	  ఒకవేళ (!ముగింపు)
	    constructor_range_దొంతర = range_దొంతర;
	  కొనసాగు;
	}

      ఆపు;
    }

  constructor_range_దొంతర = 0;

  ఒకవేళ (raw_దత్తాంశం && RAW_దత్తాంశం_నిడివి (raw_దత్తాంశం))
    {
      gcc_assert (!string_flag && !was_designated);
      విలువ.విలువ = raw_దత్తాంశం;
      raw_దత్తాంశం = NULL_వృక్షం;
      వెళ్ళు retry;
    }
}

/* Build a complete asm-statement, whose components are a CV_QUALIFIER
   (guaranteed to be 'volatile' or null) and ARGS (represented using
   an ASM_EXPR node).  */
వృక్షం
build_asm_stmt (తార్కిక is_volatile, వృక్షం వాదనలు)
{
  ఒకవేళ (is_volatile)
    ASM_VOLATILE_P (వాదనలు) = 1;
  తిరిగి కూడు_stmt (వాదనలు);
}

/* Build an asm-expr, whose components are a STRING, some OUTPUTS,
   some INPUTS, and some CLOBBERS.  The latter three may be NULL.
   SIMPLE indicates whether there was anything at all after the
   string in the asm expression -- asm("blah") and asm("blah" : )
   are subtly different.  We use a ASM_EXPR node to represent this.
   LOC is the location of the asm, and IS_INLINE says whether this
   is asm inline.  */
వృక్షం
build_asm_సమాసం (location_t loc, వృక్షం string, వృక్షం outputs, వృక్షం inputs,
		వృక్షం clobbers, వృక్షం labels, తార్కిక simple, తార్కిక is_inline)
{
  వృక్షం తోక;
  వృక్షం వాదనలు;
  పూర్ణాంకం i;
  స్థిరరాశి అక్షరం *constraint;
  స్థిరరాశి అక్షరం **oconstraints;
  తార్కిక allows_mem, allows_reg, is_inout;
  పూర్ణాంకం ninputs, noutputs;

  ninputs = list_నిడివి (inputs);
  noutputs = list_నిడివి (outputs);
  oconstraints = (స్థిరరాశి అక్షరం **) alloca (noutputs * పరిమాణం (స్థిరరాశి అక్షరం *));

  string = resolve_asm_నిర్వాహ్యం_పేర్లు (string, outputs, inputs, labels);

  /* Remove output conversions that change the type but not the mode.  */
  కొరకు (i = 0, తోక = outputs; తోక; ++i, తోక = వృక్షం_CHAIN (తోక))
    {
      వృక్షం output = వృక్షం_విలువ (తోక);

      output = c_fully_fold (output, అబద్ధం, ఖాళీ, నిజం);

      /* ??? Really, this should not be here.  Users should be using a
	 proper lvalue, dammit.  But there's a long history of using casts
	 in the output operands.  In cases like longlong.h, this becomes a
	 primitive form of typechecking -- if the cast can be removed, then
	 the output operand had a type of the proper width; otherwise we'll
	 get an error.  Gross, but ...  */
      STRIP_NOPS (output);

      ఒకవేళ (!lvalue_or_else (loc, output, lv_asm))
	output = error_mark_కణుపు;

      ఒకవేళ (output != error_mark_కణుపు
	  && (వృక్షం_READONLY (output)
	      || TYPE_READONLY (వృక్షం_TYPE (output))
	      || (రికార్డు_OR_UNION_TYPE_P (వృక్షం_TYPE (output))
		  && C_TYPE_FIELDS_READONLY (వృక్షం_TYPE (output)))))
	readonly_error (loc, output, lv_asm);

      constraint = వృక్షం_STRING_సూచిక (వృక్షం_విలువ (వృక్షం_PURPOSE (తోక)));
      oconstraints[i] = constraint;

      ఒకవేళ (parse_output_constraint (&constraint, i, ninputs, noutputs,
				   &allows_mem, &allows_reg, &is_inout,
				   శూన్యసూచిక))
	{
	  /* If the operand is going to end up in memory,
	     mark it addressable.  */
	  ఒకవేళ (!allows_reg && !c_mark_addressable (output))
	    output = error_mark_కణుపు;
	  ఒకవేళ (!(!allows_reg && allows_mem)
	      && output != error_mark_కణుపు
	      && VOID_TYPE_P (వృక్షం_TYPE (output)))
	    {
	      error_at (loc, "invalid use of void expression");
	      output = error_mark_కణుపు;
	    }
	  ఒకవేళ (allows_reg && current_function_decl == NULL_వృక్షం)
	    {
	      error_at (loc, "constraint allows registers outside of "
			     "a function");
	      output = error_mark_కణుపు;
	    }
	}
      లేకపోతే
	output = error_mark_కణుపు;

      ఒకవేళ (current_function_decl == NULL_వృక్షం && output != error_mark_కణుపు)
	{
	  ఒకవేళ (వృక్షం_SIDE_EFFECTS (output))
	    {
	      error_at (loc, "side-effects in output operand outside "
			     "of a function");
	      output = error_mark_కణుపు;
	    }
	  లేకపోతే
	    {
	      వృక్షం addr = build_unary_op (loc, ADDR_సమాసం, output, అబద్ధం);
	      ఒకవేళ (addr == error_mark_కణుపు)
		output = error_mark_కణుపు;
	      లేకపోతే ఒకవేళ (!initializer_constant_valid_p (addr, వృక్షం_TYPE (addr)))
		{
		  error_at (loc, "output operand outside of a function is not "
				 "constant");
		  output = error_mark_కణుపు;
		}
	    }
	}
      లేకపోతే ఒకవేళ (output != error_mark_కణుపు && అక్షరశ్రేణి_శోధన (constraint, "-"))
	{
	  error_at (loc, "%<-%> modifier used inside of a function");
	  output = error_mark_కణుపు;
	}

      వృక్షం_విలువ (తోక) = output;
    }

  కొరకు (i = 0, తోక = inputs; తోక; ++i, తోక = వృక్షం_CHAIN (తోక))
    {
      వృక్షం ఆదానం;

      constraint = వృక్షం_STRING_సూచిక (వృక్షం_విలువ (వృక్షం_PURPOSE (తోక)));
      ఆదానం = వృక్షం_విలువ (తోక);

      ఒకవేళ (parse_ఆదానం_constraint (&constraint, i, ninputs, noutputs, 0,
				  oconstraints, &allows_mem, &allows_reg,
				  శూన్యసూచిక))
	{
	  /* If the operand is going to end up in memory,
	     mark it addressable.  */
	  ఒకవేళ (!allows_reg && allows_mem)
	    {
	      ఆదానం = c_fully_fold (ఆదానం, అబద్ధం, ఖాళీ, నిజం);

	      /* Strip the nops as we allow this case.  FIXME, this really
		 should be rejected or made deprecated.  */
	      STRIP_NOPS (ఆదానం);
	      ఒకవేళ (!c_mark_addressable (ఆదానం))
		ఆదానం = error_mark_కణుపు;
	    }
	  లేకపోతే
	    {
	      ఆదానం = c_fully_fold (convert_lvalue_గమ్యం_rvalue (loc, ఆదానం,
							      నిజం, అబద్ధం),
				    అబద్ధం, ఖాళీ);

	      ఒకవేళ (ఆదానం != error_mark_కణుపు && VOID_TYPE_P (వృక్షం_TYPE (ఆదానం)))
		{
		  error_at (loc, "invalid use of void expression");
		  ఆదానం = error_mark_కణుపు;
		}
	    }
	  ఒకవేళ (allows_reg && current_function_decl == NULL_వృక్షం)
	    {
	      error_at (loc, "constraint allows registers outside of "
			     "a function");
	      ఆదానం = error_mark_కణుపు;
	    }
	  ఒకవేళ (constraint[0] == ':' && ఆదానం != error_mark_కణుపు)
	    {
	      వృక్షం t = ఆదానం;
	      STRIP_NOPS (t);
	      ఒకవేళ (వృక్షం_సంకేతం (t) != ADDR_సమాసం
		  || !(వృక్షం_సంకేతం (వృక్షం_నిర్వాహ్యం (t, 0)) == FUNCTION_DECL
		       || (VAR_P (వృక్షం_నిర్వాహ్యం (t, 0))
			   && is_global_var (వృక్షం_నిర్వాహ్యం (t, 0)))))
		{
		  error_at (loc, "%<:%> constraint operand is not address "
				 "of a function or non-automatic variable");
		  ఆదానం = error_mark_కణుపు;
		}
	      లేకపోతే ఒకవేళ (వృక్షం_సంకేతం (వృక్షం_నిర్వాహ్యం (t, 0)) == FUNCTION_DECL)
		suppress_warning (వృక్షం_నిర్వాహ్యం (t, 0), OPT_Wunused);
	    }
	}
      లేకపోతే
	ఆదానం = error_mark_కణుపు;

      ఒకవేళ (current_function_decl == NULL_వృక్షం && ఆదానం != error_mark_కణుపు)
	{
	  ఒకవేళ (వృక్షం_SIDE_EFFECTS (ఆదానం))
	    {
	      error_at (loc, "side-effects in input operand outside "
			     "of a function");
	      ఆదానం = error_mark_కణుపు;
	    }
	  లేకపోతే
	    {
	      వృక్షం tem = ఆదానం;
	      ఒకవేళ (allows_mem && lvalue_p (ఆదానం))
		tem = build_unary_op (loc, ADDR_సమాసం, ఆదానం, అబద్ధం);
	      ఒకవేళ (!initializer_constant_valid_p (tem, వృక్షం_TYPE (tem)))
		{
		  error_at (loc, "input operand outside of a function is not "
				 "constant");
		  ఆదానం = error_mark_కణుపు;
		}
	    }
	}
      లేకపోతే ఒకవేళ (ఆదానం != error_mark_కణుపు && అక్షరశ్రేణి_శోధన (constraint, "-"))
	{
	  error_at (loc, "%<-%> modifier used inside of a function");
	  ఆదానం = error_mark_కణుపు;
	}

      వృక్షం_విలువ (తోక) = ఆదానం;
    }

  వాదనలు = build_stmt (loc, ASM_సమాసం, string, outputs, inputs, clobbers, labels);

  /* asm statements without outputs, including simple ones, are treated
     as volatile.  */
  ASM_BASIC_P (వాదనలు) = simple;
  ASM_VOLATILE_P (వాదనలు) = (noutputs == 0);
  ASM_INLINE_P (వాదనలు) = is_inline;

  తిరిగి వాదనలు;
}

/* Generate a goto statement to LABEL.  LOC is the location of the
   GOTO.  */

వృక్షం
c_ముగింపు_goto_label (location_t loc, వృక్షం label)
{
  వృక్షం decl = lookup_label_for_goto (loc, label);
  ఒకవేళ (!decl)
    తిరిగి NULL_వృక్షం;
  వృక్షం_వాడిన (decl) = 1;
  mark_decl_వాడిన (decl, అబద్ధం);
  {
    కూడు_stmt (build_predict_సమాసం (PRED_GOTO, NOT_తీసుకున్న));
    వృక్షం t = build1 (GOTO_సమాసం, void_type_కణుపు, decl);
    సమితి_సమాసం_LOCATION (t, loc);
    తిరిగి కూడు_stmt (t);
  }
}

/* Generate a computed goto statement to EXPR.  LOC is the location of
   the GOTO.  */

వృక్షం
c_ముగింపు_goto_ptr (location_t loc, c_సమాసం val)
{
  వృక్షం సమాసం = val.విలువ;
  వృక్షం t;
  pedwarn (loc, OPT_Wpedantic, "ISO C forbids %<goto *expr;%>");
  ఒకవేళ (సమాసం != error_mark_కణుపు
      && !సూచిక_TYPE_P (వృక్షం_TYPE (సమాసం))
      && !null_సూచిక_constant_p (సమాసం))
    {
      error_at (val.get_location (),
		"computed goto must be pointer type");
      సమాసం = build_zero_cst (ptr_type_కణుపు);
    }
  సమాసం = c_fully_fold (సమాసం, అబద్ధం, ఖాళీ);
  సమాసం = convert (ptr_type_కణుపు, సమాసం);
  t = build1 (GOTO_సమాసం, void_type_కణుపు, సమాసం);
  సమితి_సమాసం_LOCATION (t, loc);
  తిరిగి కూడు_stmt (t);
}

/* Generate a C `return' statement.  RETVAL is the expression for what
   to return, or a null pointer for `return;' with no value.  LOC is
   the location of the return statement, or the location of the expression,
   if the statement has any.  If ORIGTYPE is not NULL_TREE, it
   is the original type of RETVAL.  MUSTTAIL_P indicates a musttail
   attribute.  */

వృక్షం
c_ముగింపు_return (location_t loc, వృక్షం retval, వృక్షం origtype, తార్కిక musttail_p)
{
  వృక్షం valtype = వృక్షం_TYPE (వృక్షం_TYPE (current_function_decl)), ret_stmt;
  తార్కిక no_warning = అబద్ధం;
  తార్కిక npc = అబద్ధం;

  /* Use the expansion point to handle cases such as returning NULL
     in a function returning void.  */
  location_t xloc = expansion_బిందువు_location_if_లోపల_system_శీర్షిక (loc);

  ఒకవేళ (వృక్షం_THIS_VOLATILE (current_function_decl))
    warning_at (xloc, 0,
		"function declared %<noreturn%> has a %<return%> statement");

  సమితి_musttail_on_return (retval, xloc, musttail_p);

  ఒకవేళ (retval)
    {
      వృక్షం semantic_type = NULL_వృక్షం;
      npc = null_సూచిక_constant_p (retval);
      ఒకవేళ (వృక్షం_సంకేతం (retval) == EXCESS_PRECISION_సమాసం)
	{
	  semantic_type = వృక్షం_TYPE (retval);
	  retval = వృక్షం_నిర్వాహ్యం (retval, 0);
	}
      retval = c_fully_fold (retval, అబద్ధం, ఖాళీ);
      ఒకవేళ (semantic_type
	  && valtype != NULL_వృక్షం
	  && వృక్షం_సంకేతం (valtype) != VOID_TYPE)
	retval = build1 (EXCESS_PRECISION_సమాసం, semantic_type, retval);
    }

  ఒకవేళ (!retval)
    {
      current_function_returns_null = 1;
      ఒకవేళ ((warn_return_type >= 0 || flag_isoc99)
	  && valtype != NULL_వృక్షం && వృక్షం_సంకేతం (valtype) != VOID_TYPE)
	{
	  no_warning = నిజం;
	  ఒకవేళ (emit_diagnostic (flag_isoc99
			       ? diagnostics::రకం::permerror
			       : diagnostics::రకం::warning,
			       loc, OPT_Wreturn_mismatch,
			       "%<return%> with no value,"
			       " in function returning non-void"))
	    inform (DECL_ఆధారం_LOCATION (current_function_decl),
		    "declared here");
	}
    }
  లేకపోతే ఒకవేళ (valtype == NULL_వృక్షం || VOID_TYPE_P (valtype))
    {
      current_function_returns_null = 1;
      తార్కిక warned_ఇక్కడ;
      ఒకవేళ (వృక్షం_సంకేతం (వృక్షం_TYPE (retval)) != VOID_TYPE)
	warned_ఇక్కడ = permerror_opt
	  (xloc, OPT_Wreturn_mismatch,
	   "%<return%> with a value, in function returning void");
      లేకపోతే
	warned_ఇక్కడ = pedwarn
	  (xloc, OPT_Wpedantic, "ISO C forbids "
	   "%<return%> with expression, in function returning void");
      ఒకవేళ (warned_ఇక్కడ)
	inform (DECL_ఆధారం_LOCATION (current_function_decl),
		"declared here");
    }
  లేకపోతే
    {
      వృక్షం t = convert_for_assignment (loc, UNKNOWN_LOCATION, valtype,
				       retval, origtype, ic_return,
				       npc, NULL_వృక్షం, NULL_వృక్షం, 0);
      వృక్షం res = DECL_ఫలితం (current_function_decl);
      వృక్షం inner;
      తార్కిక save;

      current_function_returns_విలువ = 1;
      ఒకవేళ (t == error_mark_కణుపు)
	{
	  /* Suppress -Wreturn-type for this function.  */
	  ఒకవేళ (warn_return_type)
	    suppress_warning (current_function_decl, OPT_Wreturn_type);
	  తిరిగి NULL_వృక్షం;
	}

      save = లోపల_late_ద్విమాన_op;
      ఒకవేళ (C_BOOLEAN_TYPE_P (వృక్షం_TYPE (res))
	  || వృక్షం_సంకేతం (వృక్షం_TYPE (res)) == COMPLEX_TYPE
	  || (SCALAR_FLOAT_TYPE_P (వృక్షం_TYPE (t))
	      && (వృక్షం_సంకేతం (వృక్షం_TYPE (res)) == INTEGER_TYPE
		  || వృక్షం_సంకేతం (వృక్షం_TYPE (res)) == ENUMERAL_TYPE)
	      && sanitize_flags_p (SANITIZE_FLOAT_CAST)))
        లోపల_late_ద్విమాన_op = నిజం;
      inner = t = convert (వృక్షం_TYPE (res), t);
      లోపల_late_ద్విమాన_op = save;

      /* Strip any conversions, additions, and subtractions, and see if
	 we are returning the address of a local variable.  Warn if so.  */
      అయితే (1)
	{
	  ఎంపిక (వృక్షం_సంకేతం (inner))
	    {
	    CASE_CONVERT:
	    స్థితి NON_LVALUE_సమాసం:
	    స్థితి PLUS_సమాసం:
	    స్థితి సూచిక_PLUS_సమాసం:
	      inner = వృక్షం_నిర్వాహ్యం (inner, 0);
	      కొనసాగు;

	    స్థితి MINUS_సమాసం:
	      /* If the second operand of the MINUS_EXPR has a pointer
		 type (or is converted from it), this may be valid, so
		 don't give a warning.  */
	      {
		వృక్షం op1 = వృక్షం_నిర్వాహ్యం (inner, 1);

		అయితే (!సూచిక_TYPE_P (వృక్షం_TYPE (op1))
		       && (CONVERT_సమాసం_P (op1)
			   || వృక్షం_సంకేతం (op1) == NON_LVALUE_సమాసం))
		  op1 = వృక్షం_నిర్వాహ్యం (op1, 0);

		ఒకవేళ (సూచిక_TYPE_P (వృక్షం_TYPE (op1)))
		  ఆపు;

		inner = వృక్షం_నిర్వాహ్యం (inner, 0);
		కొనసాగు;
	      }

	    స్థితి ADDR_సమాసం:
	      inner = వృక్షం_నిర్వాహ్యం (inner, 0);

	      అయితే (REFERENCE_CLASS_P (inner)
		     && !పరోక్ష_REF_P (inner))
		inner = వృక్షం_నిర్వాహ్యం (inner, 0);

	      ఒకవేళ (DECL_P (inner)
		  && !DECL_EXTERNAL (inner)
		  && DECL_CONTEXT (inner) == current_function_decl
		  && సూచిక_TYPE_P (వృక్షం_TYPE (వృక్షం_TYPE (current_function_decl))))
		{
		  ఒకవేళ (వృక్షం_సంకేతం (inner) == LABEL_DECL)
		    warning_at (loc, OPT_Wreturn_local_addr,
				"function returns address of label");
		  లేకపోతే ఒకవేళ (వృక్షం_సంకేతం (inner) == FUNCTION_DECL
			   && (C_FUNC_NONLOCAL_CONTEXT (inner)
			       || !DECL_INITIAL (inner)))
		    warning_at (loc, OPT_Wreturn_local_addr,
				"function returns address of nested function "
				"referencing local context");
		  లేకపోతే ఒకవేళ (వృక్షం_సంకేతం (inner) != FUNCTION_DECL
			   && !వృక్షం_STATIC (inner))
		    {
		      warning_at (loc, OPT_Wreturn_local_addr,
				  "function returns address of local variable");
		      వృక్షం zero = build_zero_cst (వృక్షం_TYPE (res));
		      t = build2 (COMPOUND_సమాసం, వృక్షం_TYPE (res), t, zero);
		    }
		}
	      ఆపు;

	    అప్రమేయ:
	      ఆపు;
	    }

	  ఆపు;
	}

      retval = build2 (MODIFY_సమాసం, వృక్షం_TYPE (res), res, t);
      సమితి_సమాసం_LOCATION (retval, loc);

      ఒకవేళ (warn_sequence_బిందువు)
	verify_sequence_points (retval);
    }

  ret_stmt = build_stmt (loc, RETURN_సమాసం, retval);
  ఒకవేళ (no_warning)
    suppress_warning (ret_stmt, OPT_Wreturn_type);
  తిరిగి కూడు_stmt (ret_stmt);
}

నిర్మాణం c_switch {
  /* The SWITCH_STMT being built.  */
  వృక్షం switch_stmt;

  /* The original type of the testing expression, i.e. before the
     default conversion is applied.  */
  వృక్షం orig_type;

  /* A splay-tree mapping the low element of a case range to the high
     element, or NULL_TREE if there is no high element.  Used to
     determine whether or not a new case label duplicates an old case
     label.  We need a tree, rather than simply a hash table, because
     of the GNU case range extension.  */
  splay_వృక్షం cases;

  /* The bindings at the point of the switch.  This is used for
     warnings crossing decls when branching to a case label.  */
  నిర్మాణం c_spot_bindings *bindings;

  /* Whether the switch includes any break statements.  */
  తార్కిక break_stmt_చూసిన_p;

  /* The next node on the stack.  */
  నిర్మాణం c_switch *తదుపరి;

  /* Remember whether the controlling expression had boolean type
     before integer promotions for the sake of -Wswitch-bool.  */
  తార్కిక bool_cond_p;
};

/* A stack of the currently active switch statements.  The innermost
   switch statement is on the top of the stack.  There is no need to
   mark the stack for garbage collection because it is only active
   during the processing of the body of a function, and we never
   collect at that point.  */

నిర్మాణం c_switch *c_switch_దొంతర;

/* Start a C switch statement, testing expression EXP.  Return the new
   SWITCH_STMT.  SWITCH_LOC is the location of the `switch'.
   SWITCH_COND_LOC is the location of the switch's condition.
   EXPLICIT_CAST_P is true if the expression EXP has an explicit cast.  */

వృక్షం
c_ప్రారంభం_switch (location_t switch_loc,
		location_t switch_cond_loc,
		వృక్షం ఘాతాంకం, తార్కిక explicit_cast_p, వృక్షం switch_name)
{
  వృక్షం orig_type = error_mark_కణుపు;
  తార్కిక bool_cond_p = అబద్ధం;
  నిర్మాణం c_switch *cs;

  ఒకవేళ (ఘాతాంకం != error_mark_కణుపు)
    {
      orig_type = వృక్షం_TYPE (ఘాతాంకం);

      ఒకవేళ (!INTEGRAL_TYPE_P (orig_type))
	{
	  ఒకవేళ (orig_type != error_mark_కణుపు)
	    {
	      error_at (switch_cond_loc, "switch quantity not an integer");
	      orig_type = error_mark_కణుపు;
	    }
	  ఘాతాంకం = integer_zero_కణుపు;
	}
      లేకపోతే
	{
	  వృక్షం type = TYPE_MAIN_VARIANT (orig_type);
	  వృక్షం e = ఘాతాంకం;

	  /* Warn if the condition has boolean value.  */
	  అయితే (వృక్షం_సంకేతం (e) == COMPOUND_సమాసం)
	    e = వృక్షం_నిర్వాహ్యం (e, 1);

	  ఒకవేళ ((C_BOOLEAN_TYPE_P (type)
	       || truth_విలువ_p (వృక్షం_సంకేతం (e)))
	      /* Explicit cast to int suppresses this warning.  */
	      && !(వృక్షం_సంకేతం (type) == INTEGER_TYPE
		   && explicit_cast_p))
	    bool_cond_p = నిజం;

	  ఒకవేళ (!లోపల_system_శీర్షిక_at (ఆదానం_location)
	      && (type == long_integer_type_కణుపు
		  || type == long_unsigned_type_కణుపు))
	    warning_at (switch_cond_loc,
			OPT_Wtraditional, "%<long%> switch expression not "
			"converted to %<int%> in ISO C");

	  ఘాతాంకం = c_fully_fold (ఘాతాంకం, అబద్ధం, ఖాళీ);
	  ఘాతాంకం = default_conversion (ఘాతాంకం);

	  ఒకవేళ (warn_sequence_బిందువు)
	    verify_sequence_points (ఘాతాంకం);
	}
    }

  /* Add this new SWITCH_STMT to the stack.  */
  cs = XNEW (నిర్మాణం c_switch);
  cs->switch_stmt = build_stmt (switch_loc, SWITCH_STMT, ఘాతాంకం,
				NULL_వృక్షం, orig_type, NULL_వృక్షం, switch_name);
  cs->orig_type = orig_type;
  cs->cases = splay_వృక్షం_new (case_compare, ఖాళీ, ఖాళీ);
  cs->bindings = c_get_switch_bindings ();
  cs->break_stmt_చూసిన_p = అబద్ధం;
  cs->bool_cond_p = bool_cond_p;
  cs->తదుపరి = c_switch_దొంతర;
  c_switch_దొంతర = cs;

  తిరిగి కూడు_stmt (cs->switch_stmt);
}

/* Process a case label at location LOC, with attributes ATTRS.  */

వృక్షం
do_case (location_t loc, వృక్షం దిగువ_విలువ, వృక్షం ఎగువ_విలువ, వృక్షం attrs)
{
  వృక్షం label = NULL_వృక్షం;

  ఒకవేళ (దిగువ_విలువ && వృక్షం_సంకేతం (దిగువ_విలువ) != INTEGER_CST)
    {
      దిగువ_విలువ = c_fully_fold (దిగువ_విలువ, అబద్ధం, ఖాళీ);
      ఒకవేళ (వృక్షం_సంకేతం (దిగువ_విలువ) == INTEGER_CST)
	pedwarn (loc, OPT_Wpedantic,
		 "case label is not an integer constant expression");
    }

  ఒకవేళ (ఎగువ_విలువ && వృక్షం_సంకేతం (ఎగువ_విలువ) != INTEGER_CST)
    {
      ఎగువ_విలువ = c_fully_fold (ఎగువ_విలువ, అబద్ధం, ఖాళీ);
      ఒకవేళ (వృక్షం_సంకేతం (ఎగువ_విలువ) == INTEGER_CST)
	pedwarn (ఆదానం_location, OPT_Wpedantic,
		 "case label is not an integer constant expression");
    }

  ఒకవేళ (c_switch_దొంతర == ఖాళీ)
    {
      ఒకవేళ (దిగువ_విలువ)
	error_at (loc, "case label not within a switch statement");
      లేకపోతే
	error_at (loc, "%<default%> label not within a switch statement");
      తిరిగి NULL_వృక్షం;
    }

  ఒకవేళ (c_check_switch_jump_warnings (c_switch_దొంతర->bindings,
				    సమాసం_LOCATION (c_switch_దొంతర->switch_stmt),
				    loc))
    తిరిగి NULL_వృక్షం;

  label = c_కూడు_case_label (loc, c_switch_దొంతర->cases,
			    SWITCH_STMT_COND (c_switch_దొంతర->switch_stmt),
			    దిగువ_విలువ, ఎగువ_విలువ, attrs);
  ఒకవేళ (label == error_mark_కణుపు)
    label = NULL_వృక్షం;
  తిరిగి label;
}

/* Finish the switch statement.  TYPE is the original type of the
   controlling expression of the switch, or NULL_TREE.  */

శూన్య
c_ముగింపు_switch (వృక్షం body, వృక్షం type)
{
  నిర్మాణం c_switch *cs = c_switch_దొంతర;
  location_t switch_location;

  SWITCH_STMT_BODY (cs->switch_stmt) = body;

  /* Emit warnings as needed.  */
  switch_location = సమాసం_LOCATION (cs->switch_stmt);
  c_do_switch_warnings (cs->cases, switch_location,
			type ? type : SWITCH_STMT_TYPE (cs->switch_stmt),
			SWITCH_STMT_COND (cs->switch_stmt), cs->bool_cond_p);
  ఒకవేళ (c_switch_covers_all_cases_p (cs->cases,
				   SWITCH_STMT_TYPE (cs->switch_stmt)))
    SWITCH_STMT_ALL_CASES_P (cs->switch_stmt) = 1;
  SWITCH_STMT_NO_BREAK_P (cs->switch_stmt) = !cs->break_stmt_చూసిన_p;

  /* Pop the stack.  */
  c_switch_దొంతర = cs->తదుపరి;
  splay_వృక్షం_delete (cs->cases);
  c_release_switch_bindings (cs->bindings);
  XDELETE (cs);
}

/* Emit an if statement.  IF_LOCUS is the location of the 'if'.  COND,
   THEN_BLOCK and ELSE_BLOCK are expressions to be used; ELSE_BLOCK
   may be null.  */

శూన్య
c_ముగింపు_if_stmt (location_t if_locus, వృక్షం cond, వృక్షం then_ఖండం,
		  వృక్షం else_ఖండం)
{
  వృక్షం stmt;

  stmt = build3 (COND_సమాసం, void_type_కణుపు, cond, then_ఖండం, else_ఖండం);
  సమితి_సమాసం_LOCATION (stmt, if_locus);
  కూడు_stmt (stmt);
}

వృక్షం
c_ముగింపు_bc_stmt (location_t loc, వృక్షం label, తార్కిక is_break, వృక్షం name)
{
  /* In switch statements break is sometimes stylistically used after
     a return statement.  This can lead to spurious warnings about
     control reaching the end of a non-void function when it is
     inlined.  Note that we are calling block_may_fallthru with
     language specific tree nodes; this works because
     block_may_fallthru returns true when given something it does not
     understand.  */
  తార్కిక skip = !ఖండం_may_fallthru (cur_stmt_list);

  ఒకవేళ (is_break)
    ఎంపిక (లోపల_statement & ~లోపల_NAMED_STMT)
      {
      స్థితి 0:
	error_at (loc, "break statement not within loop or switch");
	తిరిగి NULL_వృక్షం;
      స్థితి లోపల_OMP_ఖండం:
	error_at (loc, "invalid exit from OpenMP structured block");
	తిరిగి NULL_వృక్షం;
      స్థితి లోపల_OMP_FOR:
	error_at (loc, "break statement used with OpenMP for loop");
	తిరిగి NULL_వృక్షం;
      స్థితి లోపల_ITERATION_STMT:
      స్థితి లోపల_OBJC_FOREACH:
	ఆపు;
      అప్రమేయ:
	gcc_assert (లోపల_statement & లోపల_SWITCH_STMT);
	c_switch_దొంతర->break_stmt_చూసిన_p = నిజం;
	ఆపు;
      }
  లేకపోతే
    ఎంపిక (లోపల_statement & ~(లోపల_SWITCH_STMT | లోపల_NAMED_STMT))
      {
      స్థితి 0:
	error_at (loc, "continue statement not within a loop");
	తిరిగి NULL_వృక్షం;
      స్థితి లోపల_OMP_ఖండం:
	error_at (loc, "invalid exit from OpenMP structured block");
	తిరిగి NULL_వృక్షం;
      స్థితి లోపల_ITERATION_STMT:
      స్థితి లోపల_OMP_FOR:
      స్థితి లోపల_OBJC_FOREACH:
	ఆపు;
      అప్రమేయ:
	gcc_unreachable ();
      }

  ఒకవేళ (skip)
    తిరిగి NULL_వృక్షం;
  లేకపోతే ఒకవేళ ((లోపల_statement & లోపల_OBJC_FOREACH)
	   && !(is_break && (లోపల_statement & లోపల_SWITCH_STMT))
	   && name == NULL_వృక్షం)
    {
      /* The foreach expander produces low-level code using gotos instead
	 of a structured loop construct.  */
      gcc_assert (label);
      తిరిగి కూడు_stmt (build_stmt (loc, GOTO_సమాసం, label));
    }
  లేకపోతే ఒకవేళ (name && C_DECL_LOOP_NAME (name) && C_DECL_SWITCH_NAME (name))
    {
      label = DECL_CHAIN (name);
      ఒకవేళ (!is_break)
	label = DECL_CHAIN (label);
      /* Foreach expander from some outer level.  */
      తిరిగి కూడు_stmt (build_stmt (loc, GOTO_సమాసం, label));
    }
  తిరిగి కూడు_stmt (build_stmt (loc, is_break ? BREAK_STMT : CONTINUE_STMT,
			       name));
}

/* A helper routine for c_process_expr_stmt and c_finish_stmt_expr.  */

స్థిర శూన్య
emit_side_effect_warnings (location_t loc, వృక్షం సమాసం)
{
  maybe_warn_nodiscard (loc, సమాసం);
  ఒకవేళ (!warn_వాడని_విలువ)
    తిరిగి;
  ఒకవేళ (సమాసం == error_mark_కణుపు)
    ;
  లేకపోతే ఒకవేళ (!వృక్షం_SIDE_EFFECTS (సమాసం))
    {
      ఒకవేళ (!VOID_TYPE_P (వృక్షం_TYPE (సమాసం))
	  && !warning_suppressed_p (సమాసం, OPT_Wunused_విలువ))
	warning_at (loc, OPT_Wunused_విలువ, "statement with no effect");
    }
  లేకపోతే ఒకవేళ (వృక్షం_సంకేతం (సమాసం) == COMPOUND_సమాసం)
    {
      వృక్షం r = సమాసం;
      location_t cloc = loc;
      అయితే (వృక్షం_సంకేతం (r) == COMPOUND_సమాసం)
	{
	  ఒకవేళ (సమాసం_HAS_LOCATION (r))
	    cloc = సమాసం_LOCATION (r);
	  r = వృక్షం_నిర్వాహ్యం (r, 1);
	}
      ఒకవేళ (!వృక్షం_SIDE_EFFECTS (r)
	  && !VOID_TYPE_P (వృక్షం_TYPE (r))
	  && !CONVERT_సమాసం_P (r)
	  && !warning_suppressed_p (r, OPT_Wunused_విలువ)
	  && !warning_suppressed_p (సమాసం, OPT_Wunused_విలువ))
	warning_at (cloc, OPT_Wunused_విలువ,
		    "right-hand operand of comma expression has no effect");
    }
  లేకపోతే
    warn_if_వాడని_విలువ (సమాసం, loc);
}

/* Process an expression as if it were a complete statement.  Emit
   diagnostics, but do not call ADD_STMT.  LOC is the location of the
   statement.  */

వృక్షం
c_process_సమాసం_stmt (location_t loc, వృక్షం సమాసం)
{
  వృక్షం exprv;

  ఒకవేళ (!సమాసం)
    తిరిగి NULL_వృక్షం;

  సమాసం = c_fully_fold (సమాసం, అబద్ధం, ఖాళీ);

  ఒకవేళ (warn_sequence_బిందువు)
    verify_sequence_points (సమాసం);

  ఒకవేళ (వృక్షం_TYPE (సమాసం) != error_mark_కణుపు
      && !COMPLETE_OR_VOID_TYPE_P (వృక్షం_TYPE (సమాసం))
      && వృక్షం_సంకేతం (వృక్షం_TYPE (సమాసం)) != ARRAY_TYPE)
    error_at (loc, "expression statement has incomplete type");

  /* If we're not processing a statement expression, warn about unused values.
     Warnings for statement expressions will be emitted later, once we figure
     out which is the result.  */
  ఒకవేళ (!STATEMENT_LIST_STMT_సమాసం (cur_stmt_list)
      && (warn_వాడని_విలువ || warn_వాడని_ఫలితం))
    emit_side_effect_warnings (సమాసం_LOC_OR_LOC (సమాసం, loc), సమాసం);

  exprv = సమాసం;
  అయితే (వృక్షం_సంకేతం (exprv) == COMPOUND_సమాసం)
    exprv = వృక్షం_నిర్వాహ్యం (exprv, 1);
  అయితే (CONVERT_సమాసం_P (exprv))
    exprv = వృక్షం_నిర్వాహ్యం (exprv, 0);
  ఒకవేళ (DECL_P (exprv)
      || handled_component_p (exprv)
      || వృక్షం_సంకేతం (exprv) == ADDR_సమాసం)
    mark_exp_read (exprv);

  /* If the expression is not of a type to which we cannot assign a line
     number, wrap the thing in a no-op NOP_EXPR.  */
  ఒకవేళ (DECL_P (సమాసం) || CONSTANT_CLASS_P (సమాసం))
    {
      సమాసం = build1 (NOP_సమాసం, వృక్షం_TYPE (సమాసం), సమాసం);
      సమితి_సమాసం_LOCATION (సమాసం, loc);
    }

  తిరిగి సమాసం;
}

/* Emit an expression as a statement.  LOC is the location of the
   expression.  */

వృక్షం
c_ముగింపు_సమాసం_stmt (location_t loc, వృక్షం సమాసం)
{
  ఒకవేళ (సమాసం)
    తిరిగి కూడు_stmt (c_process_సమాసం_stmt (loc, సమాసం));
  లేకపోతే
    తిరిగి ఖాళీ;
}

/* Do the opposite and emit a statement as an expression.  To begin,
   create a new binding level and return it.  */

వృక్షం
c_begin_stmt_సమాసం (శూన్య)
{
  వృక్షం ret;

  /* We must force a BLOCK for this level so that, if it is not expanded
     later, there is a way to turn off the entire subtree of blocks that
     are contained in it.  */
  keep_తదుపరి_level ();
  ret = c_begin_compound_stmt (నిజం);

  c_bindings_ప్రారంభం_stmt_సమాసం (c_switch_దొంతర == ఖాళీ
			      ? ఖాళీ
			      : c_switch_దొంతర->bindings);

  /* Mark the current statement list as belonging to a statement list.  */
  STATEMENT_LIST_STMT_సమాసం (ret) = 1;

  తిరిగి ret;
}

/* LOC is the location of the compound statement to which this body
   belongs.  */

వృక్షం
c_ముగింపు_stmt_సమాసం (location_t loc, వృక్షం body)
{
  వృక్షం చివరి, type, tmp, val;
  వృక్షం *చివరి_p;

  body = c_చివర_compound_stmt (loc, body, నిజం);

  c_bindings_చివర_stmt_సమాసం (c_switch_దొంతర == ఖాళీ
			    ? ఖాళీ
			    : c_switch_దొంతర->bindings);

  /* Locate the last statement in BODY.  See c_end_compound_stmt
     about always returning a BIND_EXPR.  */
  చివరి_p = &BIND_సమాసం_BODY (body);
  చివరి = BIND_సమాసం_BODY (body);

 continue_searching:
  ఒకవేళ (వృక్షం_సంకేతం (చివరి) == STATEMENT_LIST)
    {
      వృక్షం_stmt_iterator l = tsi_చివరి (చివరి);

      అయితే (!tsi_చివర_p (l) && వృక్షం_సంకేతం (tsi_stmt (l)) == DEBUG_BEGIN_STMT)
	tsi_prev (&l);

      /* This can happen with degenerate cases like ({ }).  No value.  */
      ఒకవేళ (tsi_చివర_p (l))
	తిరిగి body;

      /* If we're supposed to generate side effects warnings, process
	 all of the statements except the last.  */
      ఒకవేళ (warn_వాడని_విలువ || warn_వాడని_ఫలితం)
	{
	  కొరకు (వృక్షం_stmt_iterator i = tsi_ప్రారంభం (చివరి);
	       tsi_stmt (i) != tsi_stmt (l); tsi_తదుపరి (&i))
	    {
	      location_t tloc;
	      వృక్షం t = tsi_stmt (i);

	      tloc = సమాసం_HAS_LOCATION (t) ? సమాసం_LOCATION (t) : loc;
	      emit_side_effect_warnings (tloc, t);
	    }
	}
      చివరి_p = tsi_stmt_ptr (l);
      చివరి = *చివరి_p;
    }

  /* If the end of the list is exception related, then the list was split
     by a call to push_cleanup.  Continue searching.  */
  ఒకవేళ (వృక్షం_సంకేతం (చివరి) == TRY_FINALLY_సమాసం
      || వృక్షం_సంకేతం (చివరి) == TRY_CATCH_సమాసం)
    {
      చివరి_p = &వృక్షం_నిర్వాహ్యం (చివరి, 0);
      చివరి = *చివరి_p;
      వెళ్ళు continue_searching;
    }

  ఒకవేళ (చివరి == error_mark_కణుపు)
    తిరిగి చివరి;

  /* In the case that the BIND_EXPR is not necessary, return the
     expression out from inside it.  */
  ఒకవేళ ((చివరి == BIND_సమాసం_BODY (body)
       /* Skip nested debug stmts.  */
       || చివరి == సమాసం_మొదటి (BIND_సమాసం_BODY (body)))
      && BIND_సమాసం_VARS (body) == ఖాళీ)
    {
      /* Even if this looks constant, do not allow it in a constant
	 expression.  */
      చివరి = c_wrap_maybe_const (చివరి, నిజం);
      /* Do not warn if the return value of a statement expression is
	 unused.  */
      suppress_warning (చివరి, OPT_Wunused);
      తిరిగి చివరి;
    }

  /* Extract the type of said expression.  */
  type = వృక్షం_TYPE (చివరి);

  /* If we're not returning a value at all, then the BIND_EXPR that
     we already have is a fine expression to return.  */
  ఒకవేళ (!type || VOID_TYPE_P (type))
    తిరిగి body;

  /* Now that we've located the expression containing the value, it seems
     silly to make voidify_wrapper_expr repeat the process.  Create a
     temporary of the appropriate type and stick it in a TARGET_EXPR.  */
  tmp = create_tmp_var_raw (type);

  /* Unwrap a no-op NOP_EXPR as added by c_finish_expr_stmt.  This avoids
     tree_expr_nonnegative_p giving up immediately.  */
  val = చివరి;
  ఒకవేళ (వృక్షం_సంకేతం (val) == NOP_సమాసం
      && వృక్షం_TYPE (val) == వృక్షం_TYPE (వృక్షం_నిర్వాహ్యం (val, 0)))
    val = వృక్షం_నిర్వాహ్యం (val, 0);

  *చివరి_p = build2 (MODIFY_సమాసం, void_type_కణుపు, tmp, val);
  సమితి_సమాసం_LOCATION (*చివరి_p, సమాసం_LOCATION (చివరి));

  {
    వృక్షం t = build4 (లక్ష్యం_సమాసం, type, tmp, body, NULL_వృక్షం, NULL_వృక్షం);
    సమితి_సమాసం_LOCATION (t, loc);
    తిరిగి t;
  }
}

/* Begin and end compound statements.  This is as simple as pushing
   and popping new statement lists from the tree.  */

వృక్షం
c_begin_compound_stmt (తార్కిక do_scope)
{
  వృక్షం stmt = నెట్టు_stmt_list ();
  ఒకవేళ (do_scope)
    నెట్టు_scope ();
  తిరిగి stmt;
}

/* End a compound statement.  STMT is the statement.  LOC is the
   location of the compound statement-- this is usually the location
   of the opening brace.  */

వృక్షం
c_చివర_compound_stmt (location_t loc, వృక్షం stmt, తార్కిక do_scope)
{
  వృక్షం ఖండం = ఖాళీ;

  ఒకవేళ (do_scope)
    {
      ఒకవేళ (c_dialect_objc ())
	objc_clear_super_receiver ();
      ఖండం = తీయి_scope ();
    }

  stmt = తీయి_stmt_list (stmt);
  stmt = c_build_bind_సమాసం (loc, ఖండం, stmt);

  /* If this compound statement is nested immediately inside a statement
     expression, then force a BIND_EXPR to be created.  Otherwise we'll
     do the wrong thing for ({ { 1; } }) or ({ 1; { } }).  In particular,
     STATEMENT_LISTs merge, and thus we can lose track of what statement
     was really last.  */
  ఒకవేళ (building_stmt_list_p ()
      && STATEMENT_LIST_STMT_సమాసం (cur_stmt_list)
      && వృక్షం_సంకేతం (stmt) != BIND_సమాసం)
    {
      stmt = build3 (BIND_సమాసం, void_type_కణుపు, ఖాళీ, stmt, ఖాళీ);
      వృక్షం_SIDE_EFFECTS (stmt) = 1;
      సమితి_సమాసం_LOCATION (stmt, loc);
    }

  తిరిగి stmt;
}

/* Queue a cleanup.  CLEANUP is an expression/statement to be executed
   when the current scope is exited.  EH_ONLY is true when this is not
   meant to apply to normal control flow transfer.  */

శూన్య
నెట్టు_cleanup (వృక్షం decl, వృక్షం cleanup, తార్కిక eh_only)
{
  గణన వృక్షం_సంకేతం_2 సంకేతం_2;
  వృక్షం stmt, list;
  తార్కిక stmt_సమాసం;

  సంకేతం_2 = eh_only ? TRY_CATCH_సమాసం : TRY_FINALLY_సమాసం;
  stmt = build_stmt (DECL_ఆధారం_LOCATION (decl), సంకేతం_2, ఖాళీ, cleanup);
  కూడు_stmt (stmt);
  stmt_సమాసం = STATEMENT_LIST_STMT_సమాసం (cur_stmt_list);
  list = నెట్టు_stmt_list ();
  వృక్షం_నిర్వాహ్యం (stmt, 0) = list;
  STATEMENT_LIST_STMT_సమాసం (list) = stmt_సమాసం;
}

/* Build a vector comparison of ARG0 and ARG1 using CODE opcode
   into a value of TYPE type.  Comparison is done via VEC_COND_EXPR.  */

స్థిర వృక్షం
build_vec_cmp (వృక్షం_సంకేతం_2 సంకేతం_2, వృక్షం type,
	       వృక్షం arg0, వృక్షం arg1)
{
  వృక్షం zero_vec = build_zero_cst (type);
  వృక్షం minus_one_vec = build_minus_one_cst (type);
  వృక్షం cmp_type = truth_type_for (వృక్షం_TYPE (arg0));
  వృక్షం cmp = build2 (సంకేతం_2, cmp_type, arg0, arg1);
  తిరిగి build3 (VEC_COND_సమాసం, type, cmp, minus_one_vec, zero_vec);
}

/* Possibly warn about an address of OP never being NULL in a comparison
   operation CODE involving null.  */

స్థిర శూన్య
maybe_warn_for_null_చిరునామా (location_t loc, వృక్షం op, వృక్షం_సంకేతం_2 సంకేతం_2)
{
  /* Prevent warnings issued for macro expansion.  */
  ఒకవేళ (!warn_చిరునామా
      || warning_suppressed_p (op, OPT_Waddress)
      || from_macro_expansion_at (loc))
    తిరిగి;

  ఒకవేళ (వృక్షం_సంకేతం (op) == NOP_సమాసం)
    {
      /* Allow casts to intptr_t to suppress the warning.  */
      వృక్షం type = వృక్షం_TYPE (op);
      ఒకవేళ (వృక్షం_సంకేతం (type) == INTEGER_TYPE)
	తిరిగి;
      op = వృక్షం_నిర్వాహ్యం (op, 0);
    }

  ఒకవేళ (వృక్షం_సంకేతం (op) == సూచిక_PLUS_సమాసం)
    {
      /* Allow a cast to void* to suppress the warning.  */
      వృక్షం type = వృక్షం_TYPE (వృక్షం_TYPE (op));
      ఒకవేళ (VOID_TYPE_P (type))
	తిరిగి;

      /* Adding any value to a null pointer, including zero, is undefined
	 in C.  This includes the expression &p[0] where p is the null
	 pointer, although &p[0] will have been folded to p by this point
	 and so not diagnosed.  */
      ఒకవేళ (సంకేతం_2 == EQ_సమాసం)
	warning_at (loc, OPT_Waddress,
		    "the comparison will always evaluate as %<false%> "
		    "for the pointer operand in %qE must not be NULL",
		    op);
      లేకపోతే
	warning_at (loc, OPT_Waddress,
		    "the comparison will always evaluate as %<true%> "
		    "for the pointer operand in %qE must not be NULL",
		    op);

      తిరిగి;
    }

  ఒకవేళ (వృక్షం_సంకేతం (op) != ADDR_సమాసం)
    తిరిగి;

  op = వృక్షం_నిర్వాహ్యం (op, 0);

  ఒకవేళ (వృక్షం_సంకేతం (op) == IMAGPART_సమాసం
      || వృక్షం_సంకేతం (op) == REALPART_సమాసం)
    {
      /* The address of either complex part may not be null.  */
      ఒకవేళ (సంకేతం_2 == EQ_సమాసం)
	warning_at (loc, OPT_Waddress,
		    "the comparison will always evaluate as %<false%> "
		    "for the address of %qE will never be NULL",
		    op);
      లేకపోతే
	warning_at (loc, OPT_Waddress,
		    "the comparison will always evaluate as %<true%> "
		    "for the address of %qE will never be NULL",
		    op);
      తిరిగి;
    }

  /* Set to true in the loop below if OP dereferences is operand.
     In such a case the ultimate target need not be a decl for
     the null [in]equality test to be constant.  */
  తార్కిక deref = అబద్ధం;

  /* Get the outermost array or object, or member.  */
  అయితే (handled_component_p (op))
    {
      ఒకవేళ (వృక్షం_సంకేతం (op) == COMPONENT_REF)
	{
	  /* Get the member (its address is never null).  */
	  op = వృక్షం_నిర్వాహ్యం (op, 1);
	  ఆపు;
	}

      /* Get the outer array/object to refer to in the warning.  */
      op = వృక్షం_నిర్వాహ్యం (op, 0);
      deref = నిజం;
    }

  ఒకవేళ ((!deref && !decl_with_nonnull_addr_p (op))
      || from_macro_expansion_at (loc))
    తిరిగి;

  తార్కిక w;
  ఒకవేళ (సంకేతం_2 == EQ_సమాసం)
    w = warning_at (loc, OPT_Waddress,
		    "the comparison will always evaluate as %<false%> "
		    "for the address of %qE will never be NULL",
		    op);
  లేకపోతే
    w = warning_at (loc, OPT_Waddress,
		    "the comparison will always evaluate as %<true%> "
		    "for the address of %qE will never be NULL",
		    op);

  ఒకవేళ (w && DECL_P (op))
    inform (DECL_ఆధారం_LOCATION (op), "%qD declared here", op);
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

వృక్షం
build_ద్విమాన_op (location_t location, గణన వృక్షం_సంకేతం_2 సంకేతం_2,
		 వృక్షం orig_op0, వృక్షం orig_op1, తార్కిక convert_p)
{
  వృక్షం type0, type1, orig_type0, orig_type1;
  వృక్షం eptype;
  గణన వృక్షం_సంకేతం_2 code0, code1;
  వృక్షం op0, op1;
  వృక్షం ret = error_mark_కణుపు;
  స్థిరరాశి అక్షరం *invalid_op_diag;
  తార్కిక op0_int_operands, op1_int_operands;
  తార్కిక int_const, int_const_or_అధికప్రవాహం, int_operands;

  /* Expression code to give to the expression when it is built.
     Normally this is CODE, which is what the caller asked for,
     but in some special cases we change it.  */
  గణన వృక్షం_సంకేతం_2 resultcode = సంకేతం_2;

  /* Data type in which the computation is to be performed.
     In the simplest cases this is the common type of the arguments.  */
  వృక్షం ఫలితం_type = ఖాళీ;

  /* When the computation is in excess precision, the type of the
     final EXCESS_PRECISION_EXPR.  */
  వృక్షం semantic_ఫలితం_type = ఖాళీ;

  /* Nonzero means operands have already been type-converted
     in whatever way is necessary.
     Zero means they need to be converted to RESULT_TYPE.  */
  పూర్ణాంకం converted = 0;

  /* Nonzero means create the expression with this type, rather than
     RESULT_TYPE.  */
  వృక్షం build_type = NULL_వృక్షం;

  /* Nonzero means after finally constructing the expression
     convert it to this type.  */
  వృక్షం final_type = NULL_వృక్షం;

  /* Nonzero if this is an operation like MIN or MAX which can
     safely be computed in short if both args are promoted shorts.
     Also implies COMMON.
     -1 indicates a bitwise operation; this makes a difference
     in the exact conditions for when it is safe to do the operation
     in a narrower mode.  */
  పూర్ణాంకం shorten = 0;

  /* Nonzero if this is a comparison operation;
     if both args are promoted shorts, compare the original shorts.
     Also implies COMMON.  */
  పూర్ణాంకం short_compare = 0;

  /* Nonzero if this is a right-shift operation, which can be computed on the
     original short and then promoted if the operand is a promoted short.  */
  పూర్ణాంకం short_జరుపు = 0;

  /* Nonzero means set RESULT_TYPE to the common type of the args.  */
  పూర్ణాంకం common = 0;

  /* True means types are compatible as far as ObjC is concerned.  */
  తార్కిక objc_ok;

  /* True means this is an arithmetic operation that may need excess
     precision.  */
  తార్కిక may_need_excess_precision;

  /* True means this is a boolean operation that converts both its
     operands to truth-values.  */
  తార్కిక boolean_op = అబద్ధం;

  /* Remember whether we're doing / or %.  */
  తార్కిక doing_div_or_mod = అబద్ధం;

  /* Remember whether we're doing << or >>.  */
  తార్కిక doing_జరుపు = అబద్ధం;

  /* Tree holding instrumentation expression.  */
  వృక్షం instrument_సమాసం = ఖాళీ;

  ఒకవేళ (location == UNKNOWN_LOCATION)
    location = ఆదానం_location;

  op0 = orig_op0;
  op1 = orig_op1;

  op0_int_operands = సమాసం_INT_CONST_OPERANDS (orig_op0);
  ఒకవేళ (op0_int_operands)
    op0 = remove_c_maybe_const_సమాసం (op0);
  op1_int_operands = సమాసం_INT_CONST_OPERANDS (orig_op1);
  ఒకవేళ (op1_int_operands)
    op1 = remove_c_maybe_const_సమాసం (op1);
  int_operands = (op0_int_operands && op1_int_operands);
  ఒకవేళ (int_operands)
    {
      int_const_or_అధికప్రవాహం = (వృక్షం_సంకేతం (orig_op0) == INTEGER_CST
			       && వృక్షం_సంకేతం (orig_op1) == INTEGER_CST);
      int_const = (int_const_or_అధికప్రవాహం
		   && !వృక్షం_అధికప్రవాహం (orig_op0)
		   && !వృక్షం_అధికప్రవాహం (orig_op1));
    }
  లేకపోతే
    int_const = int_const_or_అధికప్రవాహం = అబద్ధం;

  /* Do not apply default conversion in mixed vector/scalar expression.  */
  ఒకవేళ (convert_p
      && సదిశ_TYPE_P (వృక్షం_TYPE (op0)) == సదిశ_TYPE_P (వృక్షం_TYPE (op1)))
    {
      op0 = default_conversion (op0);
      op1 = default_conversion (op1);
    }

  orig_type0 = type0 = వృక్షం_TYPE (op0);

  orig_type1 = type1 = వృక్షం_TYPE (op1);

  /* The expression codes of the data types of the arguments tell us
     whether the arguments are integers, floating, pointers, etc.  */
  code0 = వృక్షం_సంకేతం (type0);
  code1 = వృక్షం_సంకేతం (type1);

  /* Strip NON_LVALUE_EXPRs, etc., since we aren't using as an lvalue.  */
  STRIP_TYPE_NOPS (op0);
  STRIP_TYPE_NOPS (op1);

  /* If an error was already reported for one of the arguments,
     avoid reporting another error.  */

  ఒకవేళ (code0 == ERROR_MARK || code1 == ERROR_MARK)
    తిరిగి error_mark_కణుపు;

  ఒకవేళ (code0 == సూచిక_TYPE
      && reject_gcc_builtin (op0, సమాసం_LOCATION (orig_op0)))
    తిరిగి error_mark_కణుపు;

  ఒకవేళ (code1 == సూచిక_TYPE
      && reject_gcc_builtin (op1, సమాసం_LOCATION (orig_op1)))
    తిరిగి error_mark_కణుపు;

  ఒకవేళ ((invalid_op_diag
       = targetm.invalid_ద్విమాన_op (సంకేతం_2, type0, type1)))
    {
      error_at (location, invalid_op_diag);
      తిరిగి error_mark_కణుపు;
    }

  ఎంపిక (సంకేతం_2)
    {
    స్థితి PLUS_సమాసం:
    స్థితి MINUS_సమాసం:
    స్థితి MULT_సమాసం:
    స్థితి TRUNC_DIV_సమాసం:
    స్థితి CEIL_DIV_సమాసం:
    స్థితి FLOOR_DIV_సమాసం:
    స్థితి విడత_DIV_సమాసం:
    స్థితి EXACT_DIV_సమాసం:
      may_need_excess_precision = నిజం;
      ఆపు;

    స్థితి EQ_సమాసం:
    స్థితి NE_సమాసం:
    స్థితి LE_సమాసం:
    స్థితి GE_సమాసం:
    స్థితి LT_సమాసం:
    స్థితి GT_సమాసం:
      /* Excess precision for implicit conversions of integers to
	 floating point in C11 and later.  */
      may_need_excess_precision = (flag_isoc11
				   && (ANY_INTEGRAL_TYPE_P (type0)
				       || ANY_INTEGRAL_TYPE_P (type1)));
      ఆపు;

    అప్రమేయ:
      may_need_excess_precision = అబద్ధం;
      ఆపు;
    }
  ఒకవేళ (వృక్షం_సంకేతం (op0) == EXCESS_PRECISION_సమాసం)
    {
      op0 = వృక్షం_నిర్వాహ్యం (op0, 0);
      type0 = వృక్షం_TYPE (op0);
    }
  లేకపోతే ఒకవేళ (may_need_excess_precision
	   && (eptype = excess_precision_type (type0)) != NULL_వృక్షం)
    {
      type0 = eptype;
      op0 = convert (eptype, op0);
    }
  ఒకవేళ (వృక్షం_సంకేతం (op1) == EXCESS_PRECISION_సమాసం)
    {
      op1 = వృక్షం_నిర్వాహ్యం (op1, 0);
      type1 = వృక్షం_TYPE (op1);
    }
  లేకపోతే ఒకవేళ (may_need_excess_precision
	   && (eptype = excess_precision_type (type1)) != NULL_వృక్షం)
    {
      type1 = eptype;
      op1 = convert (eptype, op1);
    }

  objc_ok = objc_compare_types (type0, type1, -3, NULL_వృక్షం);

  /* In case when one of the operands of the binary operation is
     a vector and another is a scalar -- convert scalar to vector.  */
  ఒకవేళ ((gnu_సదిశ_type_p (type0) && code1 != సదిశ_TYPE)
      || (gnu_సదిశ_type_p (type1) && code0 != సదిశ_TYPE))
    {
      గణన stv_conv convert_flag = scalar_గమ్యం_సదిశ (location, సంకేతం_2, orig_op0,
						     orig_op1, నిజం);

      ఎంపిక (convert_flag)
	{
	  స్థితి stv_error:
	    తిరిగి error_mark_కణుపు;
	  స్థితి stv_firstarg:
	    {
              తార్కిక maybe_const = నిజం;
              వృక్షం sc;
              sc = c_fully_fold (op0, అబద్ధం, &maybe_const);
              sc = save_సమాసం (sc);
              sc = convert (వృక్షం_TYPE (type1), sc);
              op0 = build_సదిశ_from_val (type1, sc);
              ఒకవేళ (!maybe_const)
                op0 = c_wrap_maybe_const (op0, నిజం);
              orig_type0 = type0 = వృక్షం_TYPE (op0);
              code0 = వృక్షం_సంకేతం (type0);
              converted = 1;
              ఆపు;
	    }
	  స్థితి stv_secondarg:
	    {
	      తార్కిక maybe_const = నిజం;
	      వృక్షం sc;
	      sc = c_fully_fold (op1, అబద్ధం, &maybe_const);
	      sc = save_సమాసం (sc);
	      sc = convert (వృక్షం_TYPE (type0), sc);
	      op1 = build_సదిశ_from_val (type0, sc);
	      ఒకవేళ (!maybe_const)
		op1 = c_wrap_maybe_const (op1, నిజం);
	      orig_type1 = type1 = వృక్షం_TYPE (op1);
	      code1 = వృక్షం_సంకేతం (type1);
	      converted = 1;
	      ఆపు;
	    }
	  అప్రమేయ:
	    ఆపు;
	}
    }

  ఎంపిక (సంకేతం_2)
    {
    స్థితి PLUS_సమాసం:
      /* Handle the pointer + int case.  */
      ఒకవేళ (code0 == సూచిక_TYPE
	  && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  ret = సూచిక_int_కూడిక (location, PLUS_సమాసం, op0, op1);
	  వెళ్ళు return_build_ద్విమాన_op;
	}
      లేకపోతే ఒకవేళ (code1 == సూచిక_TYPE
	       && (code0 == INTEGER_TYPE || code0 == BITINT_TYPE))
	{
	  ret = సూచిక_int_కూడిక (location, PLUS_సమాసం, op1, op0);
	  వెళ్ళు return_build_ద్విమాన_op;
	}
      లేకపోతే
	common = 1;
      ఆపు;

    స్థితి MINUS_సమాసం:
      /* Subtraction of two similar pointers.
	 We must subtract them as integers, then divide by object size.  */
      ఒకవేళ (code0 == సూచిక_TYPE && code1 == సూచిక_TYPE
	  && comp_లక్ష్యం_types (location, type0, type1))
	{
	  ret = సూచిక_diff (location, op0, op1, &instrument_సమాసం);
	  వెళ్ళు return_build_ద్విమాన_op;
	}
      /* Handle pointer minus int.  Just like pointer plus int.  */
      లేకపోతే ఒకవేళ (code0 == సూచిక_TYPE
	       && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  ret = సూచిక_int_కూడిక (location, MINUS_సమాసం, op0, op1);
	  వెళ్ళు return_build_ద్విమాన_op;
	}
      లేకపోతే
	common = 1;
      ఆపు;

    స్థితి MULT_సమాసం:
      common = 1;
      ఆపు;

    స్థితి TRUNC_DIV_సమాసం:
    స్థితి CEIL_DIV_సమాసం:
    స్థితి FLOOR_DIV_సమాసం:
    స్థితి విడత_DIV_సమాసం:
    స్థితి EXACT_DIV_సమాసం:
      doing_div_or_mod = నిజం;
      warn_for_div_by_zero (location, op1);

      ఒకవేళ ((code0 == INTEGER_TYPE || code0 == REAL_TYPE
	   || code0 == FIXED_బిందువు_TYPE || code0 == BITINT_TYPE
	   || code0 == COMPLEX_TYPE
	   || gnu_సదిశ_type_p (type0))
	  && (code1 == INTEGER_TYPE || code1 == REAL_TYPE
	      || code1 == FIXED_బిందువు_TYPE || code1 == BITINT_TYPE
	      || code1 == COMPLEX_TYPE
	      || gnu_సదిశ_type_p (type1)))
	{
	  గణన వృక్షం_సంకేతం_2 tcode0 = code0, tcode1 = code1;

	  ఒకవేళ (code0 == COMPLEX_TYPE || code0 == సదిశ_TYPE)
	    tcode0 = వృక్షం_సంకేతం (వృక్షం_TYPE (వృక్షం_TYPE (op0)));
	  ఒకవేళ (code1 == COMPLEX_TYPE || code1 == సదిశ_TYPE)
	    tcode1 = వృక్షం_సంకేతం (వృక్షం_TYPE (వృక్షం_TYPE (op1)));

	  ఒకవేళ (!(((tcode0 == INTEGER_TYPE || tcode0 == BITINT_TYPE
		  || (tcode0 == ENUMERAL_TYPE && code0 == సదిశ_TYPE))
		 && (tcode1 == INTEGER_TYPE || tcode1 == BITINT_TYPE
		     || (tcode1 == ENUMERAL_TYPE && code1 == సదిశ_TYPE)))
		|| (tcode0 == FIXED_బిందువు_TYPE && tcode1 == FIXED_బిందువు_TYPE)))
	    resultcode = RDIV_సమాసం;
	  లేకపోతే
	    /* Although it would be tempting to shorten always here, that
	       loses on some targets, since the modulo instruction is
	       undefined if the quotient can't be represented in the
	       computation mode.  We shorten only if unsigned or if
	       dividing by something we know != -1.  */
	    shorten = may_shorten_divmod (op0, op1);
	  common = 1;
	}
      ఆపు;

    స్థితి బిట్టు_AND_సమాసం:
    స్థితి బిట్టు_IOR_సమాసం:
    స్థితి బిట్టు_XOR_సమాసం:
      ఒకవేళ ((code0 == INTEGER_TYPE || code0 == BITINT_TYPE)
	  && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	shorten = -1;
      /* Allow vector types which are not floating point types.   */
      లేకపోతే ఒకవేళ (gnu_సదిశ_type_p (type0)
	       && gnu_సదిశ_type_p (type1)
	       && !సదిశ_FLOAT_TYPE_P (type0)
	       && !సదిశ_FLOAT_TYPE_P (type1))
	common = 1;
      ఆపు;

    స్థితి TRUNC_MOD_సమాసం:
    స్థితి FLOOR_MOD_సమాసం:
      doing_div_or_mod = నిజం;
      warn_for_div_by_zero (location, op1);

      ఒకవేళ (gnu_సదిశ_type_p (type0)
	  && gnu_సదిశ_type_p (type1)
	  && వృక్షం_సంకేతం (వృక్షం_TYPE (type0)) == INTEGER_TYPE
	  && వృక్షం_సంకేతం (వృక్షం_TYPE (type1)) == INTEGER_TYPE)
	common = 1;
      లేకపోతే ఒకవేళ ((code0 == INTEGER_TYPE || code0 == BITINT_TYPE)
	       && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  /* Although it would be tempting to shorten always here, that loses
	     on some targets, since the modulo instruction is undefined if the
	     quotient can't be represented in the computation mode.  We shorten
	     only if unsigned or if dividing by something we know != -1.  */
	  shorten = may_shorten_divmod (op0, op1);
	  common = 1;
	}
      ఆపు;

    స్థితి TRUTH_ANDIF_సమాసం:
    స్థితి TRUTH_ORIF_సమాసం:
    స్థితి TRUTH_AND_సమాసం:
    స్థితి TRUTH_OR_సమాసం:
    స్థితి TRUTH_XOR_సమాసం:
      ఒకవేళ ((code0 == INTEGER_TYPE || code0 == సూచిక_TYPE
	   || code0 == REAL_TYPE || code0 == COMPLEX_TYPE
	   || code0 == FIXED_బిందువు_TYPE || code0 == NULLPTR_TYPE
	   || code0 == BITINT_TYPE)
	  && (code1 == INTEGER_TYPE || code1 == సూచిక_TYPE
	      || code1 == REAL_TYPE || code1 == COMPLEX_TYPE
	      || code1 == FIXED_బిందువు_TYPE || code1 == NULLPTR_TYPE
	      || code1 == BITINT_TYPE))
	{
	  /* Result of these operations is always an int,
	     but that does not mean the operands should be
	     converted to ints!  */
	  ఫలితం_type = integer_type_కణుపు;
	  ఒకవేళ (op0_int_operands)
	    {
	      op0 = c_objc_common_truthvalue_conversion (location, orig_op0);
	      op0 = remove_c_maybe_const_సమాసం (op0);
	    }
	  లేకపోతే
	    op0 = c_objc_common_truthvalue_conversion (location, op0);
	  ఒకవేళ (op1_int_operands)
	    {
	      op1 = c_objc_common_truthvalue_conversion (location, orig_op1);
	      op1 = remove_c_maybe_const_సమాసం (op1);
	    }
	  లేకపోతే
	    op1 = c_objc_common_truthvalue_conversion (location, op1);
	  converted = 1;
	  boolean_op = నిజం;
	}
      ఒకవేళ (సంకేతం_2 == TRUTH_ANDIF_సమాసం)
	{
	  int_const_or_అధికప్రవాహం = (int_operands
				   && వృక్షం_సంకేతం (orig_op0) == INTEGER_CST
				   && (op0 == truthvalue_false_కణుపు
				       || వృక్షం_సంకేతం (orig_op1) == INTEGER_CST));
	  int_const = (int_const_or_అధికప్రవాహం
		       && !వృక్షం_అధికప్రవాహం (orig_op0)
		       && (op0 == truthvalue_false_కణుపు
			   || !వృక్షం_అధికప్రవాహం (orig_op1)));
	}
      లేకపోతే ఒకవేళ (సంకేతం_2 == TRUTH_ORIF_సమాసం)
	{
	  int_const_or_అధికప్రవాహం = (int_operands
				   && వృక్షం_సంకేతం (orig_op0) == INTEGER_CST
				   && (op0 == truthvalue_true_కణుపు
				       || వృక్షం_సంకేతం (orig_op1) == INTEGER_CST));
	  int_const = (int_const_or_అధికప్రవాహం
		       && !వృక్షం_అధికప్రవాహం (orig_op0)
		       && (op0 == truthvalue_true_కణుపు
			   || !వృక్షం_అధికప్రవాహం (orig_op1)));
	}
      ఆపు;

      /* Shift operations: result has same type as first operand;
	 always convert second operand to int.
	 Also set SHORT_SHIFT if shifting rightward.  */

    స్థితి RSHIFT_సమాసం:
      ఒకవేళ (gnu_సదిశ_type_p (type0)
	  && gnu_సదిశ_type_p (type1)
	  && వృక్షం_సంకేతం (వృక్షం_TYPE (type0)) == INTEGER_TYPE
	  && వృక్షం_సంకేతం (వృక్షం_TYPE (type1)) == INTEGER_TYPE
	  && తెలిసిన_eq (TYPE_సదిశ_SUBPARTS (type0),
		       TYPE_సదిశ_SUBPARTS (type1)))
	{
	  ఫలితం_type = type0;
	  converted = 1;
	}
      లేకపోతే ఒకవేళ ((code0 == INTEGER_TYPE || code0 == FIXED_బిందువు_TYPE
		|| code0 == BITINT_TYPE
		|| (gnu_సదిశ_type_p (type0)
		    && వృక్షం_సంకేతం (వృక్షం_TYPE (type0)) == INTEGER_TYPE))
	       && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  doing_జరుపు = నిజం;
	  ఒకవేళ (వృక్షం_సంకేతం (op1) == INTEGER_CST)
	    {
	      ఒకవేళ (వృక్షం_int_cst_sgn (op1) < 0)
		{
		  int_const = అబద్ధం;
		  ఒకవేళ (c_inhibit_evaluation_warnings == 0)
		    warning_at (location, OPT_Wshift_లెక్క_negative,
				"right shift count is negative");
		}
	      లేకపోతే ఒకవేళ (code0 == సదిశ_TYPE)
		{
		  ఒకవేళ (compare_వృక్షం_int (op1,
					TYPE_PRECISION (వృక్షం_TYPE (type0)))
		      >= 0)
		    {
		      int_const = అబద్ధం;
		      ఒకవేళ (c_inhibit_evaluation_warnings == 0)
			warning_at (location, OPT_Wshift_లెక్క_అధికప్రవాహం,
				    "right shift count >= width of vector element");
		    }
		}
	      లేకపోతే
		{
		  ఒకవేళ (!integer_zerop (op1))
		    short_జరుపు = 1;

		  ఒకవేళ (compare_వృక్షం_int (op1, TYPE_PRECISION (type0)) >= 0)
		    {
		      int_const = అబద్ధం;
		      ఒకవేళ (c_inhibit_evaluation_warnings == 0)
			warning_at (location, OPT_Wshift_లెక్క_అధికప్రవాహం,
				    "right shift count >= width of type");
		    }
		}
	    }

	  /* Use the type of the value to be shifted.  */
	  ఫలితం_type = type0;
	  /* Avoid converting op1 to result_type later.  */
	  converted = 1;
	}
      ఆపు;

    స్థితి LSHIFT_సమాసం:
      ఒకవేళ (gnu_సదిశ_type_p (type0)
	  && gnu_సదిశ_type_p (type1)
	  && వృక్షం_సంకేతం (వృక్షం_TYPE (type0)) == INTEGER_TYPE
	  && వృక్షం_సంకేతం (వృక్షం_TYPE (type1)) == INTEGER_TYPE
	  && తెలిసిన_eq (TYPE_సదిశ_SUBPARTS (type0),
		       TYPE_సదిశ_SUBPARTS (type1)))
	{
	  ఫలితం_type = type0;
	  converted = 1;
	}
      లేకపోతే ఒకవేళ ((code0 == INTEGER_TYPE || code0 == FIXED_బిందువు_TYPE
		|| code0 == BITINT_TYPE
		|| (gnu_సదిశ_type_p (type0)
		    && వృక్షం_సంకేతం (వృక్షం_TYPE (type0)) == INTEGER_TYPE))
	       && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  doing_జరుపు = నిజం;
	  ఒకవేళ (వృక్షం_సంకేతం (op0) == INTEGER_CST
	      && వృక్షం_int_cst_sgn (op0) < 0
	      && !TYPE_అధికప్రవాహం_WRAPS (type0))
	    {
	      /* Don't reject a left shift of a negative value in a context
		 where a constant expression is needed in C90.  */
	      ఒకవేళ (flag_isoc99)
		int_const = అబద్ధం;
	      ఒకవేళ (c_inhibit_evaluation_warnings == 0)
		warning_at (location, OPT_Wshift_negative_విలువ,
			    "left shift of negative value");
	    }
	  ఒకవేళ (వృక్షం_సంకేతం (op1) == INTEGER_CST)
	    {
	      ఒకవేళ (వృక్షం_int_cst_sgn (op1) < 0)
		{
		  int_const = అబద్ధం;
		  ఒకవేళ (c_inhibit_evaluation_warnings == 0)
		    warning_at (location, OPT_Wshift_లెక్క_negative,
				"left shift count is negative");
		}
	      లేకపోతే ఒకవేళ (code0 == సదిశ_TYPE)
		{
		  ఒకవేళ (compare_వృక్షం_int (op1,
					TYPE_PRECISION (వృక్షం_TYPE (type0)))
		      >= 0)
		    {
		      int_const = అబద్ధం;
		      ఒకవేళ (c_inhibit_evaluation_warnings == 0)
			warning_at (location, OPT_Wshift_లెక్క_అధికప్రవాహం,
				    "left shift count >= width of vector element");
		    }
		}
	      లేకపోతే ఒకవేళ (compare_వృక్షం_int (op1, TYPE_PRECISION (type0)) >= 0)
		{
		  int_const = అబద్ధం;
		  ఒకవేళ (c_inhibit_evaluation_warnings == 0)
		    warning_at (location, OPT_Wshift_లెక్క_అధికప్రవాహం,
				"left shift count >= width of type");
		}
	      లేకపోతే ఒకవేళ (వృక్షం_సంకేతం (op0) == INTEGER_CST
		       && maybe_warn_జరుపు_అధికప్రవాహం (location, op0, op1)
		       && flag_isoc99)
		int_const = అబద్ధం;
	    }

	  /* Use the type of the value to be shifted.  */
	  ఫలితం_type = type0;
	  /* Avoid converting op1 to result_type later.  */
	  converted = 1;
	}
      ఆపు;

    స్థితి EQ_సమాసం:
    స్థితి NE_సమాసం:
      ఒకవేళ (gnu_సదిశ_type_p (type0) && gnu_సదిశ_type_p (type1))
        {
          వృక్షం intt;
	  ఒకవేళ (!సదిశ_types_compatible_elements_p (type0, type1))
            {
              error_at (location, "comparing vectors with different "
                                  "element types");
              తిరిగి error_mark_కణుపు;
            }

	  ఒకవేళ (maybe_ne (TYPE_సదిశ_SUBPARTS (type0),
			TYPE_సదిశ_SUBPARTS (type1)))
            {
              error_at (location, "comparing vectors with different "
                                  "number of elements");
              తిరిగి error_mark_కణుపు;
            }

	  /* It's not precisely specified how the usual arithmetic
	     conversions apply to the vector types.  Here, we use
	     the unsigned type if one of the operands is signed and
	     the other one is unsigned.  */
	  ఒకవేళ (TYPE_UNSIGNED (type0) != TYPE_UNSIGNED (type1))
	    {
	      ఒకవేళ (!TYPE_UNSIGNED (type0))
		op0 = build1 (VIEW_CONVERT_సమాసం, type1, op0);
	      లేకపోతే
		op1 = build1 (VIEW_CONVERT_సమాసం, type0, op1);
	      warning_at (location, OPT_Wsign_compare, "comparison between "
			  "types %qT and %qT", type0, type1);
	    }

          /* Always construct signed integer vector type.  */
	  ఒకవేళ (సదిశ_BOOLEAN_TYPE_P (type0) && సదిశ_BOOLEAN_TYPE_P (type1))
	    ఫలితం_type = type0;
	  లేకపోతే
	    {
	      స్వయంచాలక nelts = TYPE_సదిశ_SUBPARTS (type0);

	      intt = c_common_type_for_కొలత (GET_బహుళకం_BITSIZE
					     (SCALAR_TYPE_బహుళకం
						(వృక్షం_TYPE (type0))), 0);
	      ఒకవేళ (!intt)
		{
		  error_at (location, "could not find an integer type "
				      "of the same size as %qT",
			    వృక్షం_TYPE (type0));
		  తిరిగి error_mark_కణుపు;
		}
	      ఫలితం_type = build_opaque_సదిశ_type (intt, nelts);
	    }
          converted = 1;
	  ret = build_vec_cmp (resultcode, ఫలితం_type, op0, op1);
	  వెళ్ళు return_build_ద్విమాన_op;
        }
      ఒకవేళ (FLOAT_TYPE_P (type0) || FLOAT_TYPE_P (type1))
	warning_at (location,
		    OPT_Wfloat_equal,
		    "comparing floating-point with %<==%> or %<!=%> is unsafe");
      /* Result of comparison is always int,
	 but don't convert the args to int!  */
      build_type = integer_type_కణుపు;
      ఒకవేళ ((code0 == INTEGER_TYPE || code0 == REAL_TYPE || code0 == BITINT_TYPE
	   || code0 == FIXED_బిందువు_TYPE || code0 == COMPLEX_TYPE)
	  && (code1 == INTEGER_TYPE || code1 == REAL_TYPE
	      || code1 == BITINT_TYPE
	      || code1 == FIXED_బిందువు_TYPE || code1 == COMPLEX_TYPE))
	short_compare = 1;
      లేకపోతే ఒకవేళ (code0 == సూచిక_TYPE
	       && (code1 == NULLPTR_TYPE
		   || null_సూచిక_constant_p (orig_op1)))
	{
	  maybe_warn_for_null_చిరునామా (location, op0, సంకేతం_2);
	  ఫలితం_type = type0;
	}
      లేకపోతే ఒకవేళ (code1 == సూచిక_TYPE
	       && (code0 == NULLPTR_TYPE
		   || null_సూచిక_constant_p (orig_op0)))
	{
	  maybe_warn_for_null_చిరునామా (location, op1, సంకేతం_2);
	  ఫలితం_type = type1;
	}
      లేకపోతే ఒకవేళ (code0 == సూచిక_TYPE && code1 == సూచిక_TYPE)
	{
	  వృక్షం tt0 = వృక్షం_TYPE (type0);
	  వృక్షం tt1 = వృక్షం_TYPE (type1);
	  addr_space_t as0 = TYPE_ADDR_SPACE (tt0);
	  addr_space_t as1 = TYPE_ADDR_SPACE (tt1);
	  addr_space_t as_common = ADDR_SPACE_GENERIC;

	  /* Anything compares with void *.  void * compares with anything.
	     Otherwise, the targets must be compatible
	     and both must be object or both incomplete.  */
	  ఒకవేళ (comp_లక్ష్యం_types (location, type0, type1))
	    ఫలితం_type = common_సూచిక_type (type0, type1, NULL_వృక్షం);
	  లేకపోతే ఒకవేళ (!addr_space_superset (as0, as1, &as_common))
	    {
	      error_at (location, "comparison of pointers to "
			"disjoint address spaces");
	      తిరిగి error_mark_కణుపు;
	    }
	  లేకపోతే ఒకవేళ (VOID_TYPE_P (tt0) && !TYPE_ATOMIC (tt0))
	    {
	      ఒకవేళ (pedantic && వృక్షం_సంకేతం (tt1) == FUNCTION_TYPE)
		pedwarn (location, OPT_Wpedantic, "ISO C forbids "
			 "comparison of %<void *%> with function pointer");
	    }
	  లేకపోతే ఒకవేళ (VOID_TYPE_P (tt1) && !TYPE_ATOMIC (tt1))
	    {
	      ఒకవేళ (pedantic && వృక్షం_సంకేతం (tt0) == FUNCTION_TYPE)
		pedwarn (location, OPT_Wpedantic, "ISO C forbids "
			 "comparison of %<void *%> with function pointer");
	    }
	  లేకపోతే
	    /* Avoid warning about the volatile ObjC EH puts on decls.  */
	    ఒకవేళ (!objc_ok)
	      pedwarn (location, OPT_Wcompare_distinct_సూచిక_types,
		       "comparison of distinct pointer types lacks a cast");

	  ఒకవేళ (ఫలితం_type == NULL_వృక్షం)
	    {
	      పూర్ణాంకం qual = ENCODE_QUAL_ADDR_SPACE (as_common);
	      ఫలితం_type = c_build_సూచిక_type
			      (c_build_qualified_type (void_type_కణుపు, qual));
	    }
	}
      లేకపోతే ఒకవేళ (code0 == సూచిక_TYPE
	       && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  ఫలితం_type = type0;
	  pedwarn (location, 0, "comparison between pointer and integer");
	}
      లేకపోతే ఒకవేళ ((code0 == INTEGER_TYPE || code0 == BITINT_TYPE)
	       && code1 == సూచిక_TYPE)
	{
	  ఫలితం_type = type1;
	  pedwarn (location, 0, "comparison between pointer and integer");
	}
      /* 6.5.9: One of the following shall hold:
	 -- both operands have type nullptr_t;  */
      లేకపోతే ఒకవేళ (code0 == NULLPTR_TYPE && code1 == NULLPTR_TYPE)
	{
	  ఫలితం_type = nullptr_type_కణుపు;
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
      లేకపోతే ఒకవేళ (code0 == NULLPTR_TYPE && null_సూచిక_constant_p (orig_op1))
	ఫలితం_type = (INTEGRAL_TYPE_P (type1)
		       ? c_build_సూచిక_type (type1) : type1);
      లేకపోతే ఒకవేళ (code1 == NULLPTR_TYPE && null_సూచిక_constant_p (orig_op0))
	ఫలితం_type = (INTEGRAL_TYPE_P (type0)
		       ? c_build_సూచిక_type (type0) : type0);
      ఒకవేళ ((C_BOOLEAN_TYPE_P (వృక్షం_TYPE (orig_op0))
	   || truth_విలువ_p (వృక్షం_సంకేతం (orig_op0)))
	  ^ (C_BOOLEAN_TYPE_P (వృక్షం_TYPE (orig_op1))
	     || truth_విలువ_p (వృక్షం_సంకేతం (orig_op1))))
	maybe_warn_bool_compare (location, సంకేతం_2, orig_op0, orig_op1);
      ఆపు;

    స్థితి LE_సమాసం:
    స్థితి GE_సమాసం:
    స్థితి LT_సమాసం:
    స్థితి GT_సమాసం:
      ఒకవేళ (gnu_సదిశ_type_p (type0) && gnu_సదిశ_type_p (type1))
        {
          వృక్షం intt;
	  ఒకవేళ (!సదిశ_types_compatible_elements_p (type0, type1))
            {
              error_at (location, "comparing vectors with different "
                                  "element types");
              తిరిగి error_mark_కణుపు;
            }

	  ఒకవేళ (maybe_ne (TYPE_సదిశ_SUBPARTS (type0),
			TYPE_సదిశ_SUBPARTS (type1)))
            {
              error_at (location, "comparing vectors with different "
                                  "number of elements");
              తిరిగి error_mark_కణుపు;
            }

	  /* It's not precisely specified how the usual arithmetic
	     conversions apply to the vector types.  Here, we use
	     the unsigned type if one of the operands is signed and
	     the other one is unsigned.  */
	  ఒకవేళ (TYPE_UNSIGNED (type0) != TYPE_UNSIGNED (type1))
	    {
	      ఒకవేళ (!TYPE_UNSIGNED (type0))
		op0 = build1 (VIEW_CONVERT_సమాసం, type1, op0);
	      లేకపోతే
		op1 = build1 (VIEW_CONVERT_సమాసం, type0, op1);
	      warning_at (location, OPT_Wsign_compare, "comparison between "
			  "types %qT and %qT", type0, type1);
	    }

          /* Always construct signed integer vector type.  */
          intt = c_common_type_for_కొలత (GET_బహుళకం_BITSIZE
					 (SCALAR_TYPE_బహుళకం
					  (వృక్షం_TYPE (type0))), 0);
	  ఒకవేళ (!intt)
	    {
	      error_at (location, "could not find an integer type "
				  "of the same size as %qT",
			వృక్షం_TYPE (type0));
	      తిరిగి error_mark_కణుపు;
	    }
          ఫలితం_type = build_opaque_సదిశ_type (intt,
						  TYPE_సదిశ_SUBPARTS (type0));
          converted = 1;
	  ret = build_vec_cmp (resultcode, ఫలితం_type, op0, op1);
	  వెళ్ళు return_build_ద్విమాన_op;
        }
      build_type = integer_type_కణుపు;
      ఒకవేళ ((code0 == INTEGER_TYPE || code0 == REAL_TYPE
	   || code0 == BITINT_TYPE || code0 == FIXED_బిందువు_TYPE)
	  && (code1 == INTEGER_TYPE || code1 == REAL_TYPE
	      || code1 == BITINT_TYPE || code1 == FIXED_బిందువు_TYPE))
	short_compare = 1;
      లేకపోతే ఒకవేళ (code0 == సూచిక_TYPE && code1 == సూచిక_TYPE)
	{
	  addr_space_t as0 = TYPE_ADDR_SPACE (వృక్షం_TYPE (type0));
	  addr_space_t as1 = TYPE_ADDR_SPACE (వృక్షం_TYPE (type1));
	  addr_space_t as_common;

	  ఒకవేళ (comp_లక్ష్యం_types (location, type0, type1))
	    {
	      ఫలితం_type = common_సూచిక_type (type0, type1, NULL_వృక్షం);
	      ఒకవేళ (!COMPLETE_TYPE_P (వృక్షం_TYPE (type0))
		  != !COMPLETE_TYPE_P (వృక్షం_TYPE (type1)))
		pedwarn_c99 (location, OPT_Wpedantic,
			     "comparison of complete and incomplete pointers");
	      లేకపోతే ఒకవేళ (వృక్షం_సంకేతం (వృక్షం_TYPE (type0)) == FUNCTION_TYPE)
		pedwarn (location, OPT_Wpedantic, "ISO C forbids "
			 "ordered comparisons of pointers to functions");
	      లేకపోతే ఒకవేళ (null_సూచిక_constant_p (orig_op0)
		       || null_సూచిక_constant_p (orig_op1))
		warning_at (location, OPT_Wextra,
			    "ordered comparison of pointer with null pointer");

	    }
	  లేకపోతే ఒకవేళ (!addr_space_superset (as0, as1, &as_common))
	    {
	      error_at (location, "comparison of pointers to "
			"disjoint address spaces");
	      తిరిగి error_mark_కణుపు;
	    }
	  లేకపోతే
	    {
	      పూర్ణాంకం qual = ENCODE_QUAL_ADDR_SPACE (as_common);
	      ఫలితం_type = c_build_సూచిక_type
			      (c_build_qualified_type (void_type_కణుపు, qual));
              pedwarn (location, OPT_Wcompare_distinct_సూచిక_types,
                       "comparison of distinct pointer types lacks a cast");
	    }
	}
      లేకపోతే ఒకవేళ (code0 == సూచిక_TYPE && null_సూచిక_constant_p (orig_op1))
	{
	  ఫలితం_type = type0;
	  ఒకవేళ (pedantic)
	    pedwarn (location, OPT_Wpedantic,
		     "ordered comparison of pointer with integer zero");
	  లేకపోతే ఒకవేళ (extra_warnings)
	    warning_at (location, OPT_Wextra,
			"ordered comparison of pointer with integer zero");
	}
      లేకపోతే ఒకవేళ (code1 == సూచిక_TYPE && null_సూచిక_constant_p (orig_op0))
	{
	  ఫలితం_type = type1;
	  ఒకవేళ (pedantic)
	    pedwarn (location, OPT_Wpedantic,
		     "ordered comparison of pointer with integer zero");
	  లేకపోతే ఒకవేళ (extra_warnings)
	    warning_at (location, OPT_Wextra,
			"ordered comparison of pointer with integer zero");
	}
      లేకపోతే ఒకవేళ (code0 == సూచిక_TYPE
	       && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  ఫలితం_type = type0;
	  pedwarn (location, 0, "comparison between pointer and integer");
	}
      లేకపోతే ఒకవేళ ((code0 == INTEGER_TYPE || code0 == BITINT_TYPE)
	       && code1 == సూచిక_TYPE)
	{
	  ఫలితం_type = type1;
	  pedwarn (location, 0, "comparison between pointer and integer");
	}

      ఒకవేళ ((code0 == సూచిక_TYPE || code1 == సూచిక_TYPE)
	  && current_function_decl != NULL_వృక్షం
	  && sanitize_flags_p (SANITIZE_సూచిక_COMPARE))
	{
	  op0 = save_సమాసం (c_fully_fold (op0, అబద్ధం, ఖాళీ));
	  op1 = save_సమాసం (c_fully_fold (op1, అబద్ధం, ఖాళీ));

	  వృక్షం tt = builtin_decl_explicit (BUILT_లోపల_ASAN_సూచిక_COMPARE);
	  instrument_సమాసం = build_call_సమాసం_loc (location, tt, 2, op0, op1);
	}

      ఒకవేళ ((C_BOOLEAN_TYPE_P (వృక్షం_TYPE (orig_op0))
	   || truth_విలువ_p (వృక్షం_సంకేతం (orig_op0)))
	  ^ (C_BOOLEAN_TYPE_P (వృక్షం_TYPE (orig_op1))
	     || truth_విలువ_p (వృక్షం_సంకేతం (orig_op1))))
	maybe_warn_bool_compare (location, సంకేతం_2, orig_op0, orig_op1);
      ఆపు;

    స్థితి MIN_సమాసం:
    స్థితి MAX_సమాసం:
      /* Used for OpenMP atomics.  */
      gcc_assert (flag_openmp);
      common = 1;
      ఆపు;

    అప్రమేయ:
      gcc_unreachable ();
    }

  ఒకవేళ (code0 == ERROR_MARK || code1 == ERROR_MARK)
    తిరిగి error_mark_కణుపు;

  ఒకవేళ (gnu_సదిశ_type_p (type0)
      && gnu_సదిశ_type_p (type1)
      && (!వృక్షం_int_cst_equal (TYPE_కొలత (type0), TYPE_కొలత (type1))
	  || !సదిశ_types_compatible_elements_p (type0, type1)))
    {
      gcc_rich_location richloc (location);
      maybe_range_label_for_వృక్షం_type_mismatch
	label_for_op0 (orig_op0, orig_op1),
	label_for_op1 (orig_op1, orig_op0);
      richloc.maybe_కూడు_సమాసం (orig_op0, &label_for_op0, highlight_colors::lhs);
      richloc.maybe_కూడు_సమాసం (orig_op1, &label_for_op1, highlight_colors::rhs);
      ద్విమాన_op_error (&richloc, సంకేతం_2, type0, type1);
      తిరిగి error_mark_కణుపు;
    }

  ఒకవేళ ((code0 == INTEGER_TYPE || code0 == REAL_TYPE || code0 == COMPLEX_TYPE
       || code0 == FIXED_బిందువు_TYPE || code0 == BITINT_TYPE
       || gnu_సదిశ_type_p (type0))
      && (code1 == INTEGER_TYPE || code1 == REAL_TYPE || code1 == COMPLEX_TYPE
	  || code1 == FIXED_బిందువు_TYPE || code1 == BITINT_TYPE
	  || gnu_సదిశ_type_p (type1)))
    {
      తార్కిక మొదటి_complex = (code0 == COMPLEX_TYPE);
      తార్కిక రెండవ_complex = (code1 == COMPLEX_TYPE);
      పూర్ణాంకం none_complex = (!మొదటి_complex && !రెండవ_complex);

      ఒకవేళ (shorten || common || short_compare)
	{
	  ఫలితం_type = c_common_type (type0, type1);
	  do_warn_double_promotion (ఫలితం_type, type0, type1,
				    "implicit conversion from %qT to %qT "
				    "to match other operand of binary "
				    "expression",
				    location);
	  ఒకవేళ (ఫలితం_type == error_mark_కణుపు)
	    తిరిగి error_mark_కణుపు;
	}

      ఒకవేళ (మొదటి_complex != రెండవ_complex
	  && (సంకేతం_2 == PLUS_సమాసం
	      || సంకేతం_2 == MINUS_సమాసం
	      || సంకేతం_2 == MULT_సమాసం
	      || (సంకేతం_2 == TRUNC_DIV_సమాసం && మొదటి_complex))
	  && వృక్షం_సంకేతం (వృక్షం_TYPE (ఫలితం_type)) == REAL_TYPE
	  && flag_signed_zeros)
	{
	  /* An operation on mixed real/complex operands must be
	     handled specially, but the language-independent code can
	     more easily optimize the plain complex arithmetic if
	     -fno-signed-zeros.  */
	  వృక్షం real_type = వృక్షం_TYPE (ఫలితం_type);
	  వృక్షం real, imag;
	  ఒకవేళ (type0 != orig_type0 || type1 != orig_type1)
	    {
	      gcc_assert (may_need_excess_precision && common);
	      semantic_ఫలితం_type = c_common_type (orig_type0, orig_type1);
	    }
	  ఒకవేళ (మొదటి_complex)
	    {
	      ఒకవేళ (వృక్షం_TYPE (op0) != ఫలితం_type)
		op0 = convert_and_check (location, ఫలితం_type, op0);
	      ఒకవేళ (వృక్షం_TYPE (op1) != real_type)
		op1 = convert_and_check (location, real_type, op1);
	    }
	  లేకపోతే
	    {
	      ఒకవేళ (వృక్షం_TYPE (op0) != real_type)
		op0 = convert_and_check (location, real_type, op0);
	      ఒకవేళ (వృక్షం_TYPE (op1) != ఫలితం_type)
		op1 = convert_and_check (location, ఫలితం_type, op1);
	    }
	  ఒకవేళ (వృక్షం_సంకేతం (op0) == ERROR_MARK || వృక్షం_సంకేతం (op1) == ERROR_MARK)
	    తిరిగి error_mark_కణుపు;
	  ఒకవేళ (మొదటి_complex)
	    {
	      op0 = save_సమాసం (op0);
	      real = build_unary_op (సమాసం_LOCATION (orig_op0), REALPART_సమాసం,
				     op0, నిజం);
	      imag = build_unary_op (సమాసం_LOCATION (orig_op0), IMAGPART_సమాసం,
				     op0, నిజం);
	      ఎంపిక (సంకేతం_2)
		{
		స్థితి MULT_సమాసం:
		స్థితి TRUNC_DIV_సమాసం:
		  op1 = save_సమాసం (op1);
		  imag = build2 (resultcode, real_type, imag, op1);
		  /* Fall through.  */
		స్థితి PLUS_సమాసం:
		స్థితి MINUS_సమాసం:
		  real = build2 (resultcode, real_type, real, op1);
		  ఆపు;
		అప్రమేయ:
		  gcc_unreachable();
		}
	    }
	  లేకపోతే
	    {
	      op1 = save_సమాసం (op1);
	      real = build_unary_op (సమాసం_LOCATION (orig_op1), REALPART_సమాసం,
				     op1, నిజం);
	      imag = build_unary_op (సమాసం_LOCATION (orig_op1), IMAGPART_సమాసం,
				     op1, నిజం);
	      ఎంపిక (సంకేతం_2)
		{
		స్థితి MULT_సమాసం:
		  op0 = save_సమాసం (op0);
		  imag = build2 (resultcode, real_type, op0, imag);
		  /* Fall through.  */
		స్థితి PLUS_సమాసం:
		  real = build2 (resultcode, real_type, op0, real);
		  ఆపు;
		స్థితి MINUS_సమాసం:
		  real = build2 (resultcode, real_type, op0, real);
		  imag = build1 (NEGATE_సమాసం, real_type, imag);
		  ఆపు;
		అప్రమేయ:
		  gcc_unreachable();
		}
	    }
	  ret = build2 (COMPLEX_సమాసం, ఫలితం_type, real, imag);
	  వెళ్ళు return_build_ద్విమాన_op;
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

      ఒకవేళ (shorten && none_complex)
	{
	  final_type = ఫలితం_type;
	  ఫలితం_type = shorten_ద్విమాన_op (ఫలితం_type, op0, op1,
					   shorten == -1);
	}

      /* Shifts can be shortened if shifting right.  */

      ఒకవేళ (short_జరుపు)
	{
	  పూర్ణాంకం unsigned_arg;
	  వృక్షం arg0 = get_narrower (op0, &unsigned_arg);

	  final_type = ఫలితం_type;

	  ఒకవేళ (arg0 == op0 && final_type == వృక్షం_TYPE (op0))
	    unsigned_arg = TYPE_UNSIGNED (వృక్షం_TYPE (op0));

	  ఒకవేళ (TYPE_PRECISION (వృక్షం_TYPE (arg0)) < TYPE_PRECISION (ఫలితం_type)
	      && వృక్షం_int_cst_sgn (op1) > 0
	      /* We can shorten only if the shift count is less than the
		 number of bits in the smaller type size.  */
	      && compare_వృక్షం_int (op1, TYPE_PRECISION (వృక్షం_TYPE (arg0))) < 0
	      /* We cannot drop an unsigned shift after sign-extension.  */
	      && (!TYPE_UNSIGNED (final_type) || unsigned_arg))
	    {
	      /* Do an unsigned shift if the operand was zero-extended.  */
	      ఫలితం_type
		= c_common_signed_or_unsigned_type (unsigned_arg,
						    వృక్షం_TYPE (arg0));
	      /* Convert value-to-be-shifted to that type.  */
	      ఒకవేళ (వృక్షం_TYPE (op0) != ఫలితం_type)
		op0 = convert (ఫలితం_type, op0);
	      converted = 1;
	    }
	}

      /* Comparison operations are shortened too but differently.
	 They identify themselves by setting short_compare = 1.  */

      ఒకవేళ (short_compare)
	{
	  /* Don't write &op0, etc., because that would prevent op0
	     from being kept in a register.
	     Instead, make copies of the our local variables and
	     pass the copies by reference, then copy them back afterward.  */
	  వృక్షం xop0 = op0, xop1 = op1, xresult_type = ఫలితం_type;
	  గణన వృక్షం_సంకేతం_2 xresultcode = resultcode;
	  వృక్షం val
	    = shorten_compare (location, &xop0, &xop1, &xresult_type,
			       &xresultcode);

	  ఒకవేళ (val != NULL_వృక్షం)
	    {
	      ret = val;
	      వెళ్ళు return_build_ద్విమాన_op;
	    }

	  op0 = xop0, op1 = xop1;
	  converted = 1;
	  resultcode = xresultcode;

	  ఒకవేళ (c_inhibit_evaluation_warnings == 0 && !c_లోపల_omp_for)
	    {
	      తార్కిక op0_maybe_const = నిజం;
	      తార్కిక op1_maybe_const = నిజం;
	      వృక్షం orig_op0_folded, orig_op1_folded;

	      ఒకవేళ (లోపల_late_ద్విమాన_op)
		{
		  orig_op0_folded = orig_op0;
		  orig_op1_folded = orig_op1;
		}
	      లేకపోతే
		{
		  /* Fold for the sake of possible warnings, as in
		     build_conditional_expr.  This requires the
		     "original" values to be folded, not just op0 and
		     op1.  */
		  c_inhibit_evaluation_warnings++;
		  op0 = c_fully_fold (op0, require_constant_విలువ,
				      &op0_maybe_const);
		  op1 = c_fully_fold (op1, require_constant_విలువ,
				      &op1_maybe_const);
		  c_inhibit_evaluation_warnings--;
		  orig_op0_folded = c_fully_fold (orig_op0,
						  require_constant_విలువ,
						  ఖాళీ);
		  orig_op1_folded = c_fully_fold (orig_op1,
						  require_constant_విలువ,
						  ఖాళీ);
		}

	      ఒకవేళ (warn_sign_compare)
		warn_for_sign_compare (location, orig_op0_folded,
				       orig_op1_folded, op0, op1,
				       ఫలితం_type, resultcode);
	      ఒకవేళ (!లోపల_late_ద్విమాన_op && !int_operands)
		{
		  ఒకవేళ (!op0_maybe_const || వృక్షం_సంకేతం (op0) != INTEGER_CST)
		    op0 = c_wrap_maybe_const (op0, !op0_maybe_const);
		  ఒకవేళ (!op1_maybe_const || వృక్షం_సంకేతం (op1) != INTEGER_CST)
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

  ఒకవేళ (!ఫలితం_type)
    {
      /* Favor showing any expression locations that are available. */
      op_location_t oploc (location, UNKNOWN_LOCATION);
      ద్విమాన_op_rich_location richloc (oploc, orig_op0, orig_op1, నిజం);
      ద్విమాన_op_error (&richloc, సంకేతం_2, వృక్షం_TYPE (op0), వృక్షం_TYPE (op1));
      తిరిగి error_mark_కణుపు;
    }

  ఒకవేళ (build_type == NULL_వృక్షం)
    {
      build_type = ఫలితం_type;
      ఒకవేళ ((type0 != orig_type0 || type1 != orig_type1)
	  && !boolean_op)
	{
	  gcc_assert (may_need_excess_precision && common);
	  semantic_ఫలితం_type = c_common_type (orig_type0, orig_type1);
	}
    }

  ఒకవేళ (!converted)
    {
      op0 = ep_convert_and_check (location, ఫలితం_type, op0,
				  semantic_ఫలితం_type);
      op1 = ep_convert_and_check (location, ఫలితం_type, op1,
				  semantic_ఫలితం_type);

      /* This can happen if one operand has a vector type, and the other
	 has a different type.  */
      ఒకవేళ (వృక్షం_సంకేతం (op0) == ERROR_MARK || వృక్షం_సంకేతం (op1) == ERROR_MARK)
	తిరిగి error_mark_కణుపు;
    }

  ఒకవేళ (sanitize_flags_p ((SANITIZE_జరుపు
			 | SANITIZE_DIVIDE
			 | SANITIZE_FLOAT_DIVIDE
			 | SANITIZE_SI_అధికప్రవాహం))
      && current_function_decl != NULL_వృక్షం
      && (doing_div_or_mod || doing_జరుపు)
      && !require_constant_విలువ)
    {
      /* OP0 and/or OP1 might have side-effects.  */
      op0 = save_సమాసం (op0);
      op1 = save_సమాసం (op1);
      op0 = c_fully_fold (op0, అబద్ధం, ఖాళీ);
      op1 = c_fully_fold (op1, అబద్ధం, ఖాళీ);
      ఒకవేళ (doing_div_or_mod && (sanitize_flags_p ((SANITIZE_DIVIDE
						  | SANITIZE_FLOAT_DIVIDE
						  | SANITIZE_SI_అధికప్రవాహం))))
	instrument_సమాసం = ubsan_instrument_division (location, op0, op1);
      లేకపోతే ఒకవేళ (doing_జరుపు && sanitize_flags_p (SANITIZE_జరుపు))
	instrument_సమాసం = ubsan_instrument_జరుపు (location, సంకేతం_2, op0, op1);
    }

  /* Treat expressions in initializers specially as they can't trap.  */
  ఒకవేళ (int_const_or_అధికప్రవాహం)
    ret = (require_constant_విలువ
	   ? fold_build2_initializer_loc (location, resultcode, build_type,
					  op0, op1)
	   : fold_build2_loc (location, resultcode, build_type, op0, op1));
  లేకపోతే
    ret = build2 (resultcode, build_type, op0, op1);
  ఒకవేళ (final_type != NULL_వృక్షం)
    ret = convert (final_type, ret);

 return_build_ద్విమాన_op:
  gcc_assert (ret != error_mark_కణుపు);
  ఒకవేళ (వృక్షం_సంకేతం (ret) == INTEGER_CST && !వృక్షం_అధికప్రవాహం (ret) && !int_const)
    ret = (int_operands
	   ? note_integer_operands (ret)
	   : build1 (NOP_సమాసం, వృక్షం_TYPE (ret), ret));
  లేకపోతే ఒకవేళ (వృక్షం_సంకేతం (ret) != INTEGER_CST && int_operands
	   && !లోపల_late_ద్విమాన_op)
    ret = note_integer_operands (ret);
  protected_సమితి_సమాసం_location (ret, location);

  ఒకవేళ (instrument_సమాసం != ఖాళీ)
    ret = fold_build2 (COMPOUND_సమాసం, వృక్షం_TYPE (ret),
		       instrument_సమాసం, ret);

  ఒకవేళ (semantic_ఫలితం_type)
    ret = build1_loc (location, EXCESS_PRECISION_సమాసం,
		      semantic_ఫలితం_type, ret);

  తిరిగి ret;
}


/* Convert EXPR to be a truth-value (type TYPE), validating its type for this
   purpose.  LOCATION is the source location for the expression.  */

వృక్షం
c_objc_common_truthvalue_conversion (location_t location, వృక్షం సమాసం, వృక్షం type)
{
  తార్కిక int_const, int_operands;

  ఎంపిక (వృక్షం_సంకేతం (వృక్షం_TYPE (సమాసం)))
    {
    స్థితి ARRAY_TYPE:
      error_at (location, "used array that cannot be converted to pointer where scalar is required");
      తిరిగి error_mark_కణుపు;

    స్థితి రికార్డు_TYPE:
      error_at (location, "used struct type value where scalar is required");
      తిరిగి error_mark_కణుపు;

    స్థితి UNION_TYPE:
      error_at (location, "used union type value where scalar is required");
      తిరిగి error_mark_కణుపు;

    స్థితి VOID_TYPE:
      error_at (location, "void value not ignored as it ought to be");
      తిరిగి error_mark_కణుపు;

    స్థితి సూచిక_TYPE:
      ఒకవేళ (reject_gcc_builtin (సమాసం))
	తిరిగి error_mark_కణుపు;
      ఆపు;

    స్థితి FUNCTION_TYPE:
      gcc_unreachable ();

    స్థితి సదిశ_TYPE:
      error_at (location, "used vector type where scalar is required");
      తిరిగి error_mark_కణుపు;

    అప్రమేయ:
      ఆపు;
    }

  /* Conversion of a floating constant to boolean goes through here
     and yields an integer constant expression.  Otherwise, the result
     is only an integer constant expression if the argument is.  */
  int_const = ((వృక్షం_సంకేతం (సమాసం) == INTEGER_CST && !వృక్షం_అధికప్రవాహం (సమాసం))
	       || ((వృక్షం_సంకేతం (సమాసం) == REAL_CST
		    || వృక్షం_సంకేతం (సమాసం) == COMPLEX_CST)
		   && (వృక్షం_సంకేతం (type) == BOOLEAN_TYPE
		       || (వృక్షం_సంకేతం (type) == ENUMERAL_TYPE
			   && ENUM_UNDERLYING_TYPE (type) != NULL_వృక్షం
			   && (వృక్షం_సంకేతం (ENUM_UNDERLYING_TYPE (type))
			       == BOOLEAN_TYPE)))));
  int_operands = సమాసం_INT_CONST_OPERANDS (సమాసం);
  ఒకవేళ (int_operands && వృక్షం_సంకేతం (సమాసం) != INTEGER_CST)
    {
      సమాసం = remove_c_maybe_const_సమాసం (సమాసం);
      సమాసం = build2 (NE_సమాసం, type, సమాసం,
		     convert (వృక్షం_TYPE (సమాసం), integer_zero_కణుపు));
      సమాసం = note_integer_operands (సమాసం);
    }
  లేకపోతే
    {
      /* ??? Should we also give an error for vectors rather than leaving
	 those to give errors later?  */
      సమాసం = c_common_truthvalue_conversion (location, సమాసం);
      సమాసం = fold_convert_loc (location, type, సమాసం);
    }

  ఒకవేళ (వృక్షం_సంకేతం (సమాసం) == INTEGER_CST && int_operands && !int_const)
    {
      ఒకవేళ (వృక్షం_అధికప్రవాహం (సమాసం))
	తిరిగి సమాసం;
      లేకపోతే
	తిరిగి note_integer_operands (సమాసం);
    }
  ఒకవేళ (వృక్షం_సంకేతం (సమాసం) == INTEGER_CST && !int_const)
    తిరిగి build1 (NOP_సమాసం, వృక్షం_TYPE (సమాసం), సమాసం);
  తిరిగి సమాసం;
}


/* Convert EXPR to a contained DECL, updating *TC, *TI and *SE as
   required.  */

వృక్షం
c_సమాసం_గమ్యం_decl (వృక్షం సమాసం, తార్కిక *tc ATTRIBUTE_వాడని, తార్కిక *se)
{
  ఒకవేళ (వృక్షం_సంకేతం (సమాసం) == COMPOUND_LITERAL_సమాసం)
    {
      వృక్షం decl = COMPOUND_LITERAL_సమాసం_DECL (సమాసం);
      /* Executing a compound literal inside a function reinitializes
	 it.  */
      ఒకవేళ (!వృక్షం_STATIC (decl))
	*se = నిజం;
      తిరిగి decl;
    }
  లేకపోతే
    తిరిగి సమాసం;
}

/* Generate OMP construct CODE, with BODY and CLAUSES as its compound
   statement.  LOC is the location of the construct.  */

వృక్షం
c_ముగింపు_omp_construct (location_t loc, గణన వృక్షం_సంకేతం_2 సంకేతం_2, వృక్షం body,
			వృక్షం clauses)
{
  body = c_చివర_compound_stmt (loc, body, నిజం);

  వృక్షం stmt = make_కణుపు (సంకేతం_2);
  వృక్షం_TYPE (stmt) = void_type_కణుపు;
  OMP_BODY (stmt) = body;
  OMP_CLAUSES (stmt) = clauses;
  సమితి_సమాసం_LOCATION (stmt, loc);

  తిరిగి కూడు_stmt (stmt);
}

/* Generate OACC_DATA, with CLAUSES and BLOCK as its compound
   statement.  LOC is the location of the OACC_DATA.  */

వృక్షం
c_ముగింపు_oacc_దత్తాంశం (location_t loc, వృక్షం clauses, వృక్షం ఖండం)
{
  వృక్షం stmt;

  ఖండం = c_చివర_compound_stmt (loc, ఖండం, నిజం);

  stmt = make_కణుపు (OACC_దత్తాంశం);
  వృక్షం_TYPE (stmt) = void_type_కణుపు;
  OACC_దత్తాంశం_CLAUSES (stmt) = clauses;
  OACC_దత్తాంశం_BODY (stmt) = ఖండం;
  సమితి_సమాసం_LOCATION (stmt, loc);

  తిరిగి కూడు_stmt (stmt);
}

/* Generate OACC_HOST_DATA, with CLAUSES and BLOCK as its compound
   statement.  LOC is the location of the OACC_HOST_DATA.  */

వృక్షం
c_ముగింపు_oacc_host_దత్తాంశం (location_t loc, వృక్షం clauses, వృక్షం ఖండం)
{
  వృక్షం stmt;

  ఖండం = c_చివర_compound_stmt (loc, ఖండం, నిజం);

  stmt = make_కణుపు (OACC_HOST_దత్తాంశం);
  వృక్షం_TYPE (stmt) = void_type_కణుపు;
  OACC_HOST_దత్తాంశం_CLAUSES (stmt) = clauses;
  OACC_HOST_దత్తాంశం_BODY (stmt) = ఖండం;
  సమితి_సమాసం_LOCATION (stmt, loc);

  తిరిగి కూడు_stmt (stmt);
}

/* Like c_begin_compound_stmt, except force the retention of the BLOCK.  */

వృక్షం
c_begin_omp_parallel (శూన్య)
{
  వృక్షం ఖండం;

  keep_తదుపరి_level ();
  ఖండం = c_begin_compound_stmt (నిజం);

  తిరిగి ఖండం;
}

/* Generate OMP_PARALLEL, with CLAUSES and BLOCK as its compound
   statement.  LOC is the location of the OMP_PARALLEL.  */

వృక్షం
c_ముగింపు_omp_parallel (location_t loc, వృక్షం clauses, వృక్షం ఖండం)
{
  వృక్షం stmt;

  ఖండం = c_చివర_compound_stmt (loc, ఖండం, నిజం);

  stmt = make_కణుపు (OMP_PARALLEL);
  వృక్షం_TYPE (stmt) = void_type_కణుపు;
  OMP_PARALLEL_CLAUSES (stmt) = clauses;
  OMP_PARALLEL_BODY (stmt) = ఖండం;
  సమితి_సమాసం_LOCATION (stmt, loc);

  తిరిగి కూడు_stmt (stmt);
}

/* Like c_begin_compound_stmt, except force the retention of the BLOCK.  */

వృక్షం
c_begin_omp_task (శూన్య)
{
  వృక్షం ఖండం;

  keep_తదుపరి_level ();
  ఖండం = c_begin_compound_stmt (నిజం);

  తిరిగి ఖండం;
}

/* Generate OMP_TASK, with CLAUSES and BLOCK as its compound
   statement.  LOC is the location of the #pragma.  */

వృక్షం
c_ముగింపు_omp_task (location_t loc, వృక్షం clauses, వృక్షం ఖండం)
{
  వృక్షం stmt;

  ఖండం = c_చివర_compound_stmt (loc, ఖండం, నిజం);

  stmt = make_కణుపు (OMP_TASK);
  వృక్షం_TYPE (stmt) = void_type_కణుపు;
  OMP_TASK_CLAUSES (stmt) = clauses;
  OMP_TASK_BODY (stmt) = ఖండం;
  సమితి_సమాసం_LOCATION (stmt, loc);

  తిరిగి కూడు_stmt (stmt);
}

/* Generate GOMP_cancel call for #pragma omp cancel.  */

శూన్య
c_ముగింపు_omp_cancel (location_t loc, వృక్షం clauses)
{
  వృక్షం fn = builtin_decl_explicit (BUILT_లోపల_GOMP_CANCEL);
  పూర్ణాంకం ముసుగు = 0;
  ఒకవేళ (omp_కనుగొను_clause (clauses, OMP_CLAUSE_PARALLEL))
    ముసుగు = 1;
  లేకపోతే ఒకవేళ (omp_కనుగొను_clause (clauses, OMP_CLAUSE_FOR))
    ముసుగు = 2;
  లేకపోతే ఒకవేళ (omp_కనుగొను_clause (clauses, OMP_CLAUSE_SECTIONS))
    ముసుగు = 4;
  లేకపోతే ఒకవేళ (omp_కనుగొను_clause (clauses, OMP_CLAUSE_TASKGROUP))
    ముసుగు = 8;
  లేకపోతే
    {
      error_at (loc, "%<#pragma omp cancel%> must specify one of "
		     "%<parallel%>, %<for%>, %<sections%> or %<taskgroup%> "
		     "clauses");
      తిరిగి;
    }
  వృక్షం ifc = omp_కనుగొను_clause (clauses, OMP_CLAUSE_IF);
  ఒకవేళ (ifc != NULL_వృక్షం)
    {
      ఒకవేళ (OMP_CLAUSE_IF_MODIFIER (ifc) != ERROR_MARK
	  && OMP_CLAUSE_IF_MODIFIER (ifc) != VOID_CST)
	error_at (OMP_CLAUSE_LOCATION (ifc),
		  "expected %<cancel%> %<if%> clause modifier");
      లేకపోతే
	{
	  వృక్షం ifc2 = omp_కనుగొను_clause (OMP_CLAUSE_CHAIN (ifc), OMP_CLAUSE_IF);
	  ఒకవేళ (ifc2 != NULL_వృక్షం)
	    {
	      gcc_assert (OMP_CLAUSE_IF_MODIFIER (ifc) == VOID_CST
			  && OMP_CLAUSE_IF_MODIFIER (ifc2) != ERROR_MARK
			  && OMP_CLAUSE_IF_MODIFIER (ifc2) != VOID_CST);
	      error_at (OMP_CLAUSE_LOCATION (ifc2),
			"expected %<cancel%> %<if%> clause modifier");
	    }
	}

      వృక్షం type = వృక్షం_TYPE (OMP_CLAUSE_IF_సమాసం (ifc));
      ifc = fold_build2_loc (OMP_CLAUSE_LOCATION (ifc), NE_సమాసం,
			     boolean_type_కణుపు, OMP_CLAUSE_IF_సమాసం (ifc),
			     build_zero_cst (type));
    }
  లేకపోతే
    ifc = boolean_true_కణుపు;
  వృక్షం stmt = build_call_సమాసం_loc (loc, fn, 2,
				   build_int_cst (integer_type_కణుపు, ముసుగు),
				   ifc);
  కూడు_stmt (stmt);
}

/* Generate GOMP_cancellation_point call for
   #pragma omp cancellation point.  */

శూన్య
c_ముగింపు_omp_cancellation_బిందువు (location_t loc, వృక్షం clauses)
{
  వృక్షం fn = builtin_decl_explicit (BUILT_లోపల_GOMP_CANCELLATION_బిందువు);
  పూర్ణాంకం ముసుగు = 0;
  ఒకవేళ (omp_కనుగొను_clause (clauses, OMP_CLAUSE_PARALLEL))
    ముసుగు = 1;
  లేకపోతే ఒకవేళ (omp_కనుగొను_clause (clauses, OMP_CLAUSE_FOR))
    ముసుగు = 2;
  లేకపోతే ఒకవేళ (omp_కనుగొను_clause (clauses, OMP_CLAUSE_SECTIONS))
    ముసుగు = 4;
  లేకపోతే ఒకవేళ (omp_కనుగొను_clause (clauses, OMP_CLAUSE_TASKGROUP))
    ముసుగు = 8;
  లేకపోతే
    {
      error_at (loc, "%<#pragma omp cancellation point%> must specify one of "
		     "%<parallel%>, %<for%>, %<sections%> or %<taskgroup%> "
		     "clauses");
      తిరిగి;
    }
  వృక్షం stmt = build_call_సమాసం_loc (loc, fn, 1,
				   build_int_cst (integer_type_కణుపు, ముసుగు));
  కూడు_stmt (stmt);
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

స్థిర వృక్షం
handle_omp_array_sections_1 (వృక్షం c, వృక్షం t, vec<వృక్షం> &types,
			     తార్కిక &maybe_zero_len, గుర్తులేని పూర్ణాంకం &మొదటి_non_one,
			     గణన c_omp_region_type ort)
{
  వృక్షం ret, దిగువ_bound, నిడివి, type;
  తార్కిక openacc = (ort & C_ORT_ACC) != 0;
  ఒకవేళ (వృక్షం_సంకేతం (t) != OMP_ARRAY_SECTION)
    {
      ఒకవేళ (error_నిర్వాహ్యం_p (t))
	తిరిగి error_mark_కణుపు;
      c_omp_చిరునామా_inspector ai (OMP_CLAUSE_LOCATION (c), t);
      ret = t;
      ఒకవేళ (OMP_CLAUSE_సంకేతం (c) != OMP_CLAUSE_AFFINITY
	  && OMP_CLAUSE_సంకేతం (c) != OMP_CLAUSE_DEPEND
	  && TYPE_ATOMIC (strip_array_types (వృక్షం_TYPE (t))))
	{
	  error_at (OMP_CLAUSE_LOCATION (c), "%<_Atomic%> %qE in %qs clause",
		    t, omp_clause_సంకేతం_name[OMP_CLAUSE_సంకేతం (c)]);
	  తిరిగి error_mark_కణుపు;
	}
      ఒకవేళ (!ai.check_clause (c))
	తిరిగి error_mark_కణుపు;
      లేకపోతే ఒకవేళ (ai.component_access_p ()
	       && (OMP_CLAUSE_సంకేతం (c) == OMP_CLAUSE_MAP
		   || OMP_CLAUSE_సంకేతం (c) == OMP_CLAUSE_గమ్యం
		   || OMP_CLAUSE_సంకేతం (c) == OMP_CLAUSE_FROM))
	t = ai.get_మూలం_పదం (నిజం);
      లేకపోతే
	t = ai.unconverted_ref_origin ();
      ఒకవేళ (t == error_mark_కణుపు)
	తిరిగి error_mark_కణుపు;
      ఒకవేళ (!VAR_P (t)
	  && (ort == C_ORT_ACC || !సమాసం_P (t))
	  && వృక్షం_సంకేతం (t) != PARM_DECL)
	{
	  ఒకవేళ (DECL_P (t))
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%qD is not a variable in %qs clause", t,
		      omp_clause_సంకేతం_name[OMP_CLAUSE_సంకేతం (c)]);
	  లేకపోతే
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%qE is not a variable in %qs clause", t,
		      omp_clause_సంకేతం_name[OMP_CLAUSE_సంకేతం (c)]);
	  తిరిగి error_mark_కణుపు;
	}
      లేకపోతే ఒకవేళ (OMP_CLAUSE_సంకేతం (c) != OMP_CLAUSE_AFFINITY
	       && OMP_CLAUSE_సంకేతం (c) != OMP_CLAUSE_DEPEND
	       && TYPE_ATOMIC (వృక్షం_TYPE (t)))
	{
	  error_at (OMP_CLAUSE_LOCATION (c), "%<_Atomic%> %qD in %qs clause",
		    t, omp_clause_సంకేతం_name[OMP_CLAUSE_సంకేతం (c)]);
	  తిరిగి error_mark_కణుపు;
	}
      లేకపోతే ఒకవేళ (OMP_CLAUSE_సంకేతం (c) != OMP_CLAUSE_AFFINITY
	       && OMP_CLAUSE_సంకేతం (c) != OMP_CLAUSE_DEPEND
	       && VAR_P (t)
	       && DECL_THREAD_LOCAL_P (t))
	{
	  error_at (OMP_CLAUSE_LOCATION (c),
		    "%qD is threadprivate variable in %qs clause", t,
		    omp_clause_సంకేతం_name[OMP_CLAUSE_సంకేతం (c)]);
	  తిరిగి error_mark_కణుపు;
	}
      ఒకవేళ ((OMP_CLAUSE_సంకేతం (c) == OMP_CLAUSE_AFFINITY
	   || OMP_CLAUSE_సంకేతం (c) == OMP_CLAUSE_DEPEND)
	  && TYPE_ATOMIC (వృక్షం_TYPE (t))
	  && సూచిక_TYPE_P (వృక్షం_TYPE (t)))
	{
	  /* If the array section is pointer based and the pointer
	     itself is _Atomic qualified, we need to atomically load
	     the pointer.  */
	  ret = convert_lvalue_గమ్యం_rvalue (OMP_CLAUSE_LOCATION (c),
					  ret, అబద్ధం, అబద్ధం);
	}
      తిరిగి ret;
    }

  ret = handle_omp_array_sections_1 (c, వృక్షం_నిర్వాహ్యం (t, 0), types,
				     maybe_zero_len, మొదటి_non_one, ort);
  ఒకవేళ (ret == error_mark_కణుపు || ret == NULL_వృక్షం)
    తిరిగి ret;

  type = వృక్షం_TYPE (ret);
  దిగువ_bound = వృక్షం_నిర్వాహ్యం (t, 1);
  నిడివి = వృక్షం_నిర్వాహ్యం (t, 2);

  ఒకవేళ (దిగువ_bound == error_mark_కణుపు || నిడివి == error_mark_కణుపు)
    తిరిగి error_mark_కణుపు;

  ఒకవేళ (దిగువ_bound && !INTEGRAL_TYPE_P (వృక్షం_TYPE (దిగువ_bound)))
    {
      error_at (OMP_CLAUSE_LOCATION (c),
		"low bound %qE of array section does not have integral type",
		దిగువ_bound);
      తిరిగి error_mark_కణుపు;
    }
  ఒకవేళ (నిడివి && !INTEGRAL_TYPE_P (వృక్షం_TYPE (నిడివి)))
    {
      error_at (OMP_CLAUSE_LOCATION (c),
		"length %qE of array section does not have integral type",
		నిడివి);
      తిరిగి error_mark_కణుపు;
    }
  ఒకవేళ (దిగువ_bound
      && వృక్షం_సంకేతం (దిగువ_bound) == INTEGER_CST
      && TYPE_PRECISION (వృక్షం_TYPE (దిగువ_bound))
	 > TYPE_PRECISION (sizetype))
    దిగువ_bound = fold_convert (sizetype, దిగువ_bound);
  ఒకవేళ (నిడివి
      && వృక్షం_సంకేతం (నిడివి) == INTEGER_CST
      && TYPE_PRECISION (వృక్షం_TYPE (నిడివి))
	 > TYPE_PRECISION (sizetype))
    నిడివి = fold_convert (sizetype, నిడివి);
  ఒకవేళ (దిగువ_bound == NULL_వృక్షం)
    దిగువ_bound = integer_zero_కణుపు;
  ఒకవేళ (OMP_CLAUSE_సంకేతం (c) == OMP_CLAUSE_MAP
      && (OMP_CLAUSE_MAP_రకం (c) == GOMP_MAP_ATTACH
	  || OMP_CLAUSE_MAP_రకం (c) == GOMP_MAP_DETACH))
    {
      ఒకవేళ (నిడివి != integer_one_కణుపు)
	{
	  error_at (OMP_CLAUSE_LOCATION (c),
		    "expected single pointer in %qs clause",
		    user_omp_clause_సంకేతం_name (c, openacc));
	  తిరిగి error_mark_కణుపు;
	}
    }
  ఒకవేళ (నిడివి != NULL_వృక్షం)
    {
      ఒకవేళ (!integer_nonzerop (నిడివి))
	{
	  ఒకవేళ (OMP_CLAUSE_సంకేతం (c) == OMP_CLAUSE_AFFINITY
	      || OMP_CLAUSE_సంకేతం (c) == OMP_CLAUSE_DEPEND
	      || OMP_CLAUSE_సంకేతం (c) == OMP_CLAUSE_REDUCTION
	      || OMP_CLAUSE_సంకేతం (c) == OMP_CLAUSE_లోపల_REDUCTION
	      || OMP_CLAUSE_సంకేతం (c) == OMP_CLAUSE_TASK_REDUCTION)
	    {
	      ఒకవేళ (integer_zerop (నిడివి))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "zero length array section in %qs clause",
			    omp_clause_సంకేతం_name[OMP_CLAUSE_సంకేతం (c)]);
		  తిరిగి error_mark_కణుపు;
		}
	    }
	  లేకపోతే
	    maybe_zero_len = నిజం;
	}
      ఒకవేళ (మొదటి_non_one == types.నిడివి ()
	  && (వృక్షం_సంకేతం (నిడివి) != INTEGER_CST || integer_onep (నిడివి)))
	మొదటి_non_one++;
    }
  ఒకవేళ (వృక్షం_సంకేతం (type) == ARRAY_TYPE)
    {
      ఒకవేళ (నిడివి == NULL_వృక్షం
	  && (TYPE_DOMAIN (type) == NULL_వృక్షం
	      || TYPE_MAX_విలువ (TYPE_DOMAIN (type)) == NULL_వృక్షం))
	{
	  error_at (OMP_CLAUSE_LOCATION (c),
		    "for unknown bound array type length expression must "
		    "be specified");
	  తిరిగి error_mark_కణుపు;
	}
      ఒకవేళ (వృక్షం_సంకేతం (దిగువ_bound) == INTEGER_CST
	  && వృక్షం_int_cst_sgn (దిగువ_bound) == -1)
	{
	  error_at (OMP_CLAUSE_LOCATION (c),
		    "negative low bound in array section in %qs clause",
		    omp_clause_సంకేతం_name[OMP_CLAUSE_సంకేతం (c)]);
	  తిరిగి error_mark_కణుపు;
	}
      ఒకవేళ (నిడివి != NULL_వృక్షం
	  && వృక్షం_సంకేతం (నిడివి) == INTEGER_CST
	  && వృక్షం_int_cst_sgn (నిడివి) == -1)
	{
	  error_at (OMP_CLAUSE_LOCATION (c),
		    "negative length in array section in %qs clause",
		    omp_clause_సంకేతం_name[OMP_CLAUSE_సంకేతం (c)]);
	  తిరిగి error_mark_కణుపు;
	}
      ఒకవేళ (TYPE_DOMAIN (type)
	  && TYPE_MAX_విలువ (TYPE_DOMAIN (type))
	  && వృక్షం_సంకేతం (TYPE_MAX_విలువ (TYPE_DOMAIN (type)))
			== INTEGER_CST)
	{
	  వృక్షం కొలత
	    = fold_convert (sizetype, TYPE_MAX_విలువ (TYPE_DOMAIN (type)));
	  కొలత = కొలత_binop (PLUS_సమాసం, కొలత, కొలత_one_కణుపు);
	  ఒకవేళ (వృక్షం_సంకేతం (దిగువ_bound) == INTEGER_CST)
	    {
	      ఒకవేళ (వృక్షం_int_cst_lt (కొలత, దిగువ_bound))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "low bound %qE above array section size "
			    "in %qs clause", దిగువ_bound,
			    omp_clause_సంకేతం_name[OMP_CLAUSE_సంకేతం (c)]);
		  తిరిగి error_mark_కణుపు;
		}
	      ఒకవేళ (వృక్షం_int_cst_equal (కొలత, దిగువ_bound))
		{
		  ఒకవేళ (OMP_CLAUSE_సంకేతం (c) == OMP_CLAUSE_AFFINITY
		      || OMP_CLAUSE_సంకేతం (c) == OMP_CLAUSE_DEPEND
		      || OMP_CLAUSE_సంకేతం (c) == OMP_CLAUSE_REDUCTION
		      || OMP_CLAUSE_సంకేతం (c) == OMP_CLAUSE_లోపల_REDUCTION
		      || OMP_CLAUSE_సంకేతం (c) == OMP_CLAUSE_TASK_REDUCTION)
		    {
		      error_at (OMP_CLAUSE_LOCATION (c),
				"zero length array section in %qs clause",
				omp_clause_సంకేతం_name[OMP_CLAUSE_సంకేతం (c)]);
		      తిరిగి error_mark_కణుపు;
		    }
		  maybe_zero_len = నిజం;
		}
	      లేకపోతే ఒకవేళ (నిడివి == NULL_వృక్షం
		       && మొదటి_non_one == types.నిడివి ()
		       && వృక్షం_int_cst_equal
			    (TYPE_MAX_విలువ (TYPE_DOMAIN (type)),
			     దిగువ_bound))
		మొదటి_non_one++;
	    }
	  లేకపోతే ఒకవేళ (నిడివి == NULL_వృక్షం)
	    {
	      ఒకవేళ (OMP_CLAUSE_సంకేతం (c) != OMP_CLAUSE_AFFINITY
		  && OMP_CLAUSE_సంకేతం (c) != OMP_CLAUSE_DEPEND
		  && OMP_CLAUSE_సంకేతం (c) != OMP_CLAUSE_REDUCTION
		  && OMP_CLAUSE_సంకేతం (c) != OMP_CLAUSE_లోపల_REDUCTION
		  && OMP_CLAUSE_సంకేతం (c) != OMP_CLAUSE_TASK_REDUCTION)
		maybe_zero_len = నిజం;
	      ఒకవేళ (మొదటి_non_one == types.నిడివి ())
		మొదటి_non_one++;
	    }
	  ఒకవేళ (నిడివి && వృక్షం_సంకేతం (నిడివి) == INTEGER_CST)
	    {
	      ఒకవేళ (వృక్షం_int_cst_lt (కొలత, నిడివి))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "length %qE above array section size "
			    "in %qs clause", నిడివి,
			    omp_clause_సంకేతం_name[OMP_CLAUSE_సంకేతం (c)]);
		  తిరిగి error_mark_కణుపు;
		}
	      ఒకవేళ (వృక్షం_సంకేతం (దిగువ_bound) == INTEGER_CST)
		{
		  వృక్షం lbpluslen
		    = కొలత_binop (PLUS_సమాసం,
				  fold_convert (sizetype, దిగువ_bound),
				  fold_convert (sizetype, నిడివి));
		  ఒకవేళ (వృక్షం_సంకేతం (lbpluslen) == INTEGER_CST
		      && వృక్షం_int_cst_lt (కొలత, lbpluslen))
		    {
		      error_at (OMP_CLAUSE_LOCATION (c),
				"high bound %qE above array section size "
				"in %qs clause", lbpluslen,
				omp_clause_సంకేతం_name[OMP_CLAUSE_సంకేతం (c)]);
		      తిరిగి error_mark_కణుపు;
		    }
		}
	    }
	}
      లేకపోతే ఒకవేళ (నిడివి == NULL_వృక్షం)
	{
	  ఒకవేళ (OMP_CLAUSE_సంకేతం (c) != OMP_CLAUSE_AFFINITY
	      && OMP_CLAUSE_సంకేతం (c) != OMP_CLAUSE_DEPEND
	      && OMP_CLAUSE_సంకేతం (c) != OMP_CLAUSE_REDUCTION
	      && OMP_CLAUSE_సంకేతం (c) != OMP_CLAUSE_లోపల_REDUCTION
	      && OMP_CLAUSE_సంకేతం (c) != OMP_CLAUSE_TASK_REDUCTION)
	    maybe_zero_len = నిజం;
	  ఒకవేళ (మొదటి_non_one == types.నిడివి ())
	    మొదటి_non_one++;
	}

      /* For [lb:] we will need to evaluate lb more than once.  */
      ఒకవేళ (నిడివి == NULL_వృక్షం && OMP_CLAUSE_సంకేతం (c) != OMP_CLAUSE_DEPEND)
	{
	  వృక్షం lb = save_సమాసం (దిగువ_bound);
	  ఒకవేళ (lb != దిగువ_bound)
	    {
	      వృక్షం_నిర్వాహ్యం (t, 1) = lb;
	      దిగువ_bound = lb;
	    }
	}
    }
  లేకపోతే ఒకవేళ (వృక్షం_సంకేతం (type) == సూచిక_TYPE)
    {
      ఒకవేళ (నిడివి == NULL_వృక్షం)
	{
	  ఒకవేళ (వృక్షం_సంకేతం (ret) == PARM_DECL && C_ARRAY_PARAMETER (ret))
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "for array function parameter length expression "
		      "must be specified");
	  లేకపోతే
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "for pointer type length expression must be specified");
	  తిరిగి error_mark_కణుపు;
	}
      ఒకవేళ (నిడివి != NULL_వృక్షం
	  && వృక్షం_సంకేతం (నిడివి) == INTEGER_CST
	  && వృక్షం_int_cst_sgn (నిడివి) == -1)
	{
	  error_at (OMP_CLAUSE_LOCATION (c),
		    "negative length in array section in %qs clause",
		    omp_clause_సంకేతం_name[OMP_CLAUSE_సంకేతం (c)]);
	  తిరిగి error_mark_కణుపు;
	}
      /* If there is a pointer type anywhere but in the very first
	 array-section-subscript, the array section could be non-contiguous.  */
      ఒకవేళ (OMP_CLAUSE_సంకేతం (c) != OMP_CLAUSE_DEPEND
	  && OMP_CLAUSE_సంకేతం (c) != OMP_CLAUSE_AFFINITY
	  && వృక్షం_సంకేతం (వృక్షం_నిర్వాహ్యం (t, 0)) == OMP_ARRAY_SECTION)
	{
	  /* If any prior dimension has a non-one length, then deem this
	     array section as non-contiguous.  */
	  కొరకు (వృక్షం d = వృక్షం_నిర్వాహ్యం (t, 0);
	       వృక్షం_సంకేతం (d) == OMP_ARRAY_SECTION;
	       d = వృక్షం_నిర్వాహ్యం (d, 0))
	    {
	      వృక్షం d_నిడివి = వృక్షం_నిర్వాహ్యం (d, 2);
	      ఒకవేళ (d_నిడివి == NULL_వృక్షం || !integer_onep (d_నిడివి))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "array section is not contiguous in %qs clause",
			    omp_clause_సంకేతం_name[OMP_CLAUSE_సంకేతం (c)]);
		  తిరిగి error_mark_కణుపు;
		}
	    }
	}
    }
  లేకపోతే
    {
      error_at (OMP_CLAUSE_LOCATION (c),
		"%qE does not have pointer or array type", ret);
      తిరిగి error_mark_కణుపు;
    }
  ఒకవేళ (OMP_CLAUSE_సంకేతం (c) != OMP_CLAUSE_DEPEND)
    types.సురక్షిత_నెట్టు (వృక్షం_TYPE (ret));
  /* We will need to evaluate lb more than once.  */
  వృక్షం lb = save_సమాసం (దిగువ_bound);
  ఒకవేళ (lb != దిగువ_bound)
    {
      వృక్షం_నిర్వాహ్యం (t, 1) = lb;
      దిగువ_bound = lb;
    }
  ret = build_array_ref (OMP_CLAUSE_LOCATION (c), ret, దిగువ_bound);
  తిరిగి ret;
}

/* Handle array sections for clause C.  */

స్థిర తార్కిక
handle_omp_array_sections (వృక్షం &c, గణన c_omp_region_type ort)
{
  తార్కిక maybe_zero_len = అబద్ధం;
  గుర్తులేని పూర్ణాంకం మొదటి_non_one = 0;
  auto_vec<వృక్షం, 10> types;
  వృక్షం *tp = &OMP_CLAUSE_DECL (c);
  ఒకవేళ ((OMP_CLAUSE_సంకేతం (c) == OMP_CLAUSE_DEPEND
       || OMP_CLAUSE_సంకేతం (c) == OMP_CLAUSE_AFFINITY)
      && OMP_ITERATOR_DECL_P (*tp))
    tp = &వృక్షం_విలువ (*tp);
  వృక్షం మొదటి = handle_omp_array_sections_1 (c, *tp, types,
					    maybe_zero_len, మొదటి_non_one,
					    ort);
  ఒకవేళ (మొదటి == error_mark_కణుపు)
    తిరిగి నిజం;
  ఒకవేళ (మొదటి == NULL_వృక్షం)
    తిరిగి అబద్ధం;
  ఒకవేళ (OMP_CLAUSE_సంకేతం (c) == OMP_CLAUSE_DEPEND
      || OMP_CLAUSE_సంకేతం (c) == OMP_CLAUSE_AFFINITY)
    {
      వృక్షం t = *tp;
      వృక్షం tem = NULL_వృక్షం;
      /* Need to evaluate side effects in the length expressions
	 if any.  */
      అయితే (వృక్షం_సంకేతం (t) == వృక్షం_LIST)
	{
	  ఒకవేళ (వృక్షం_విలువ (t) && వృక్షం_SIDE_EFFECTS (వృక్షం_విలువ (t)))
	    {
	      ఒకవేళ (tem == NULL_వృక్షం)
		tem = వృక్షం_విలువ (t);
	      లేకపోతే
		tem = build2 (COMPOUND_సమాసం, వృక్షం_TYPE (tem),
			      వృక్షం_విలువ (t), tem);
	    }
	  t = వృక్షం_CHAIN (t);
	}
      ఒకవేళ (tem)
	మొదటి = build2 (COMPOUND_సమాసం, వృక్షం_TYPE (మొదటి), tem, మొదటి);
      మొదటి = c_fully_fold (మొదటి, అబద్ధం, ఖాళీ, నిజం);
      *tp = మొదటి;
    }
  లేకపోతే
    {
      గుర్తులేని పూర్ణాంకం అంకె = types.నిడివి (), i;
      వృక్షం t, side_effects = NULL_వృక్షం, కొలత = NULL_వృక్షం;
      వృక్షం condition = NULL_వృక్షం;

      ఒకవేళ (int_కొలత_లోపల_బైట్లు (వృక్షం_TYPE (మొదటి)) <= 0)
	maybe_zero_len = నిజం;

      కొరకు (i = అంకె, t = OMP_CLAUSE_DECL (c); i > 0;
	   t = వృక్షం_నిర్వాహ్యం (t, 0))
	{
	  వృక్షం దిగువ_bound = వృక్షం_నిర్వాహ్యం (t, 1);
	  వృక్షం నిడివి = వృక్షం_నిర్వాహ్యం (t, 2);

	  i--;
	  ఒకవేళ (దిగువ_bound
	      && వృక్షం_సంకేతం (దిగువ_bound) == INTEGER_CST
	      && TYPE_PRECISION (వృక్షం_TYPE (దిగువ_bound))
		 > TYPE_PRECISION (sizetype))
	    దిగువ_bound = fold_convert (sizetype, దిగువ_bound);
	  ఒకవేళ (నిడివి
	      && వృక్షం_సంకేతం (నిడివి) == INTEGER_CST
	      && TYPE_PRECISION (వృక్షం_TYPE (నిడివి))
		 > TYPE_PRECISION (sizetype))
	    నిడివి = fold_convert (sizetype, నిడివి);
	  ఒకవేళ (దిగువ_bound == NULL_వృక్షం)
	    దిగువ_bound = integer_zero_కణుపు;
	  ఒకవేళ (!maybe_zero_len && i > మొదటి_non_one)
	    {
	      ఒకవేళ (integer_nonzerop (దిగువ_bound))
		వెళ్ళు do_warn_noncontiguous;
	      ఒకవేళ (నిడివి != NULL_వృక్షం
		  && వృక్షం_సంకేతం (నిడివి) == INTEGER_CST
		  && TYPE_DOMAIN (types[i])
		  && TYPE_MAX_విలువ (TYPE_DOMAIN (types[i]))
		  && వృక్షం_సంకేతం (TYPE_MAX_విలువ (TYPE_DOMAIN (types[i])))
		     == INTEGER_CST)
		{
		  వృక్షం కొలత;
		  కొలత = కొలత_binop (PLUS_సమాసం,
				     TYPE_MAX_విలువ (TYPE_DOMAIN (types[i])),
				     కొలత_one_కణుపు);
		  ఒకవేళ (!వృక్షం_int_cst_equal (నిడివి, కొలత))
		    {
		     do_warn_noncontiguous:
		      error_at (OMP_CLAUSE_LOCATION (c),
				"array section is not contiguous in %qs "
				"clause",
				omp_clause_సంకేతం_name[OMP_CLAUSE_సంకేతం (c)]);
		      తిరిగి నిజం;
		    }
		}
	      ఒకవేళ (నిడివి != NULL_వృక్షం
		  && వృక్షం_SIDE_EFFECTS (నిడివి))
		{
		  ఒకవేళ (side_effects == NULL_వృక్షం)
		    side_effects = నిడివి;
		  లేకపోతే
		    side_effects = build2 (COMPOUND_సమాసం,
					   వృక్షం_TYPE (side_effects),
					   నిడివి, side_effects);
		}
	    }
	  లేకపోతే
	    {
	      వృక్షం l;

	      ఒకవేళ (i > మొదటి_non_one
		  && ((నిడివి && integer_nonzerop (నిడివి))
		      || OMP_CLAUSE_సంకేతం (c) == OMP_CLAUSE_REDUCTION
		      || OMP_CLAUSE_సంకేతం (c) == OMP_CLAUSE_లోపల_REDUCTION
		      || OMP_CLAUSE_సంకేతం (c) == OMP_CLAUSE_TASK_REDUCTION))
		కొనసాగు;
	      ఒకవేళ (నిడివి)
		l = fold_convert (sizetype, నిడివి);
	      లేకపోతే
		{
		  l = కొలత_binop (PLUS_సమాసం,
				  TYPE_MAX_విలువ (TYPE_DOMAIN (types[i])),
				  కొలత_one_కణుపు);
		  l = కొలత_binop (MINUS_సమాసం, l,
				  fold_convert (sizetype, దిగువ_bound));
		}
	      ఒకవేళ (i > మొదటి_non_one)
		{
		  l = fold_build2 (NE_సమాసం, boolean_type_కణుపు, l,
				   కొలత_zero_కణుపు);
		  ఒకవేళ (condition == NULL_వృక్షం)
		    condition = l;
		  లేకపోతే
		    condition = fold_build2 (బిట్టు_AND_సమాసం, boolean_type_కణుపు,
					     l, condition);
		}
	      లేకపోతే ఒకవేళ (కొలత == NULL_వృక్షం)
		{
		  కొలత = కొలత_లోపల_బైట్లు (వృక్షం_TYPE (types[i]));
		  వృక్షం eltype = వృక్షం_TYPE (types[అంకె - 1]);
		  అయితే (వృక్షం_సంకేతం (eltype) == ARRAY_TYPE)
		    eltype = వృక్షం_TYPE (eltype);
		  ఒకవేళ (OMP_CLAUSE_సంకేతం (c) == OMP_CLAUSE_REDUCTION
		      || OMP_CLAUSE_సంకేతం (c) == OMP_CLAUSE_లోపల_REDUCTION
		      || OMP_CLAUSE_సంకేతం (c) == OMP_CLAUSE_TASK_REDUCTION)
		    {
		      ఒకవేళ (integer_zerop (కొలత)
			  || integer_zerop (కొలత_లోపల_బైట్లు (eltype)))
			{
			  error_at (OMP_CLAUSE_LOCATION (c),
				    "zero length array section in %qs clause",
				    omp_clause_సంకేతం_name[OMP_CLAUSE_సంకేతం (c)]);
			  తిరిగి error_mark_కణుపు;
			}
		      కొలత = కొలత_binop (EXACT_DIV_సమాసం, కొలత,
					 కొలత_లోపల_బైట్లు (eltype));
		    }
		  కొలత = కొలత_binop (MULT_సమాసం, కొలత, l);
		  ఒకవేళ (condition)
		    కొలత = fold_build3 (COND_సమాసం, sizetype, condition,
					కొలత, కొలత_zero_కణుపు);
		}
	      లేకపోతే
		కొలత = కొలత_binop (MULT_సమాసం, కొలత, l);
	    }
	}
      ఒకవేళ (side_effects)
	కొలత = build2 (COMPOUND_సమాసం, sizetype, side_effects, కొలత);
      ఒకవేళ (OMP_CLAUSE_సంకేతం (c) == OMP_CLAUSE_REDUCTION
	  || OMP_CLAUSE_సంకేతం (c) == OMP_CLAUSE_లోపల_REDUCTION
	  || OMP_CLAUSE_సంకేతం (c) == OMP_CLAUSE_TASK_REDUCTION)
	{
	  కొలత = కొలత_binop (MINUS_సమాసం, కొలత, కొలత_one_కణుపు);
	  కొలత = c_fully_fold (కొలత, అబద్ధం, ఖాళీ);
	  కొలత = save_సమాసం (కొలత);
	  వృక్షం సూచీ_type = build_సూచీ_type (కొలత);
	  వృక్షం eltype = వృక్షం_TYPE (మొదటి);
	  అయితే (వృక్షం_సంకేతం (eltype) == ARRAY_TYPE)
	    eltype = వృక్షం_TYPE (eltype);
	  వృక్షం type = c_build_array_type (eltype, సూచీ_type);
	  వృక్షం ptype = c_build_సూచిక_type (eltype);
	  ఒకవేళ (వృక్షం_సంకేతం (వృక్షం_TYPE (t)) == ARRAY_TYPE)
	    t = build_fold_addr_సమాసం (t);
	  వృక్షం t2 = build_fold_addr_సమాసం (మొదటి);
	  t2 = fold_convert_loc (OMP_CLAUSE_LOCATION (c),
				 ptrdiff_type_కణుపు, t2);
	  t2 = fold_build2_loc (OMP_CLAUSE_LOCATION (c), MINUS_సమాసం,
				ptrdiff_type_కణుపు, t2,
				fold_convert_loc (OMP_CLAUSE_LOCATION (c),
						  ptrdiff_type_కణుపు, t));
	  t2 = c_fully_fold (t2, అబద్ధం, ఖాళీ);
	  ఒకవేళ (వృక్షం_సరిపోతుంది_shwi_p (t2))
	    t = build2 (MEM_REF, type, t,
			build_int_cst (ptype, వృక్షం_గమ్యం_shwi (t2)));
	  లేకపోతే
	    {
	      t2 = fold_convert_loc (OMP_CLAUSE_LOCATION (c), sizetype, t2);
	      t = build2_loc (OMP_CLAUSE_LOCATION (c), సూచిక_PLUS_సమాసం,
			      వృక్షం_TYPE (t), t, t2);
	      t = build2 (MEM_REF, type, t, build_int_cst (ptype, 0));
	    }
	  OMP_CLAUSE_DECL (c) = t;
	  తిరిగి అబద్ధం;
	}
      మొదటి = c_fully_fold (మొదటి, అబద్ధం, ఖాళీ);
      OMP_CLAUSE_DECL (c) = మొదటి;
      ఒకవేళ (OMP_CLAUSE_సంకేతం (c) == OMP_CLAUSE_HAS_DEVICE_ADDR)
	తిరిగి అబద్ధం;
      /* Don't set OMP_CLAUSE_SIZE for bare attach/detach clauses.  */
      ఒకవేళ (OMP_CLAUSE_సంకేతం (c) != OMP_CLAUSE_MAP
	  || (OMP_CLAUSE_MAP_రకం (c) != GOMP_MAP_ATTACH
	      && OMP_CLAUSE_MAP_రకం (c) != GOMP_MAP_DETACH
	      && OMP_CLAUSE_MAP_రకం (c) != GOMP_MAP_FORCE_DETACH))
	{
	  ఒకవేళ (కొలత)
	    కొలత = c_fully_fold (కొలత, అబద్ధం, ఖాళీ);
	  OMP_CLAUSE_కొలత (c) = కొలత;
	}

      ఒకవేళ (OMP_CLAUSE_సంకేతం (c) != OMP_CLAUSE_MAP)
	తిరిగి అబద్ధం;

      auto_vec<omp_addr_token *, 10> addr_టోకెన్లు;

      ఒకవేళ (!omp_parse_సమాసం (addr_టోకెన్లు, మొదటి))
	తిరిగి నిజం;

      c_omp_చిరునామా_inspector ai (OMP_CLAUSE_LOCATION (c), t);

      వృక్షం nc = ai.expand_map_clause (c, మొదటి, addr_టోకెన్లు, ort);
      ఒకవేళ (nc != error_mark_కణుపు)
	{
	  ఉపయోగించి నామాకాశ omp_addr_tokenizer;

	  ఒకవేళ (ai.maybe_zero_నిడివి_array_section (c))
	    OMP_CLAUSE_MAP_MAYBE_ZERO_నిడివి_ARRAY_SECTION (c) = 1;

	  /* !!! If we're accessing a base decl via chained access
	     methods (e.g. multiple indirections), duplicate clause
	     detection won't work properly.  Skip it in that case.  */
	  ఒకవేళ ((addr_టోకెన్లు[0]->type == STRUCTURE_పునాది
	       || addr_టోకెన్లు[0]->type == ARRAY_పునాది)
	      && addr_టోకెన్లు[0]->u.structure_పునాది_రకం == పునాది_DECL
	      && addr_టోకెన్లు[1]->type == ACCESS_పద్ధతి
	      && omp_access_chain_p (addr_టోకెన్లు, 1))
	    c = nc;

	  తిరిగి అబద్ధం;
	}
    }
  తిరిగి అబద్ధం;
}

/* Helper function of finish_omp_clauses.  Clone STMT as if we were making
   an inline call.  But, remap
   the OMP_DECL1 VAR_DECL (omp_out resp. omp_orig) to PLACEHOLDER
   and OMP_DECL2 VAR_DECL (omp_in resp. omp_priv) to DECL.  */

స్థిర వృక్షం
c_clone_omp_udr (వృక్షం stmt, వృక్షం omp_decl1, వృక్షం omp_decl2,
		 వృక్షం decl, వృక్షం placeholder)
{
  copy_body_దత్తాంశం id;
  hash_map<వృక్షం, వృక్షం> decl_map;

  decl_map.put (omp_decl1, placeholder);
  decl_map.put (omp_decl2, decl);
  memset (&id, 0, పరిమాణం (id));
  id.src_fn = DECL_CONTEXT (omp_decl1);
  id.dst_fn = current_function_decl;
  id.src_cfun = DECL_STRUCT_FUNCTION (id.src_fn);
  id.decl_map = &decl_map;

  id.copy_decl = copy_decl_no_change;
  id.transform_call_లేఖాచిత్రం_అంచులు = CB_CGE_DUPLICATE;
  id.transform_new_cfg = నిజం;
  id.transform_return_గమ్యం_modify = అబద్ధం;
  id.eh_lp_nr = 0;
  walk_వృక్షం (&stmt, copy_వృక్షం_body_r, &id, ఖాళీ);
  తిరిగి stmt;
}

/* Helper function of c_finish_omp_clauses, called via walk_tree.
   Find OMP_CLAUSE_PLACEHOLDER (passed in DATA) in *TP.  */

స్థిర వృక్షం
c_కనుగొను_omp_placeholder_r (వృక్షం *tp, పూర్ణాంకం *, శూన్య *దత్తాంశం)
{
  ఒకవేళ (*tp == (వృక్షం) దత్తాంశం)
    తిరిగి *tp;
  తిరిగి NULL_వృక్షం;
}

/* Similarly, but also walk aggregate fields.  */

నిర్మాణం c_కనుగొను_omp_var_s { వృక్షం var; hash_సమితి<వృక్షం> *pset; };

స్థిర వృక్షం
c_కనుగొను_omp_var_r (వృక్షం *tp, పూర్ణాంకం *, శూన్య *దత్తాంశం)
{
  ఒకవేళ (*tp == ((నిర్మాణం c_కనుగొను_omp_var_s *) దత్తాంశం)->var)
    తిరిగి *tp;
  ఒకవేళ (రికార్డు_OR_UNION_TYPE_P (*tp))
    {
      వృక్షం క్షేత్రం_2;
      hash_సమితి<వృక్షం> *pset = ((నిర్మాణం c_కనుగొను_omp_var_s *) దత్తాంశం)->pset;

      కొరకు (క్షేత్రం_2 = TYPE_FIELDS (*tp); క్షేత్రం_2;
	   క్షేత్రం_2 = DECL_CHAIN (క్షేత్రం_2))
	ఒకవేళ (వృక్షం_సంకేతం (క్షేత్రం_2) == క్షేత్రం_DECL)
	  {
	    వృక్షం ret = walk_వృక్షం (&DECL_క్షేత్రం_స్థానభ్రంశం (క్షేత్రం_2),
				  c_కనుగొను_omp_var_r, దత్తాంశం, pset);
	    ఒకవేళ (ret)
	      తిరిగి ret;
	    ret = walk_వృక్షం (&DECL_కొలత (క్షేత్రం_2), c_కనుగొను_omp_var_r, దత్తాంశం, pset);
	    ఒకవేళ (ret)
	      తిరిగి ret;
	    ret = walk_వృక్షం (&DECL_కొలత_UNIT (క్షేత్రం_2), c_కనుగొను_omp_var_r, దత్తాంశం,
			     pset);
	    ఒకవేళ (ret)
	      తిరిగి ret;
	    ret = walk_వృక్షం (&వృక్షం_TYPE (క్షేత్రం_2), c_కనుగొను_omp_var_r, దత్తాంశం, pset);
	    ఒకవేళ (ret)
	      తిరిగి ret;
	  }
    }
  లేకపోతే ఒకవేళ (INTEGRAL_TYPE_P (*tp))
    తిరిగి walk_వృక్షం (&TYPE_MAX_విలువ (*tp), c_కనుగొను_omp_var_r, దత్తాంశం,
		      ((నిర్మాణం c_కనుగొను_omp_var_s *) దత్తాంశం)->pset);
  తిరిగి NULL_వృక్షం;
}

/* Finish OpenMP iterators ITER.  Return true if they are erroneous
   and clauses containing them should be removed.  */

స్థిర తార్కిక
c_omp_ముగింపు_iterators (వృక్షం iter)
{
  తార్కిక ret = అబద్ధం;
  కొరకు (వృక్షం it = iter; it; it = వృక్షం_CHAIN (it))
    {
      వృక్షం var = OMP_ITERATOR_VAR (it);
      వృక్షం begin = OMP_ITERATOR_BEGIN (it);
      వృక్షం చివర = OMP_ITERATOR_చివర (it);
      వృక్షం అడుగు = OMP_ITERATOR_అడుగు (it);
      వృక్షం orig_అడుగు;
      వృక్షం type = వృక్షం_TYPE (var);
      location_t loc = DECL_ఆధారం_LOCATION (var);
      ఒకవేళ (type == error_mark_కణుపు)
	{
	  ret = నిజం;
	  కొనసాగు;
	}
      ఒకవేళ (!INTEGRAL_TYPE_P (type) && !సూచిక_TYPE_P (type))
	{
	  error_at (loc, "iterator %qD has neither integral nor pointer type",
		    var);
	  ret = నిజం;
	  కొనసాగు;
	}
      లేకపోతే ఒకవేళ (TYPE_ATOMIC (type))
	{
	  error_at (loc, "iterator %qD has %<_Atomic%> qualified type", var);
	  ret = నిజం;
	  కొనసాగు;
	}
      లేకపోతే ఒకవేళ (TYPE_READONLY (type))
	{
	  error_at (loc, "iterator %qD has const qualified type", var);
	  ret = నిజం;
	  కొనసాగు;
	}
      లేకపోతే ఒకవేళ (అడుగు == error_mark_కణుపు
	       || వృక్షం_TYPE (అడుగు) == error_mark_కణుపు)
	{
	  ret = నిజం;
	  కొనసాగు;
	}
      లేకపోతే ఒకవేళ (!INTEGRAL_TYPE_P (వృక్షం_TYPE (అడుగు)))
	{
	  error_at (సమాసం_LOC_OR_LOC (అడుగు, loc),
		    "iterator step with non-integral type");
	  ret = నిజం;
	  కొనసాగు;
	}
      begin = c_fully_fold (build_c_cast (loc, type, begin), అబద్ధం, ఖాళీ);
      చివర = c_fully_fold (build_c_cast (loc, type, చివర), అబద్ధం, ఖాళీ);
      orig_అడుగు = save_సమాసం (c_fully_fold (అడుగు, అబద్ధం, ఖాళీ));
      వృక్షం stype = సూచిక_TYPE_P (type) ? sizetype : type;
      అడుగు = c_fully_fold (build_c_cast (loc, stype, orig_అడుగు), అబద్ధం, ఖాళీ);
      ఒకవేళ (సూచిక_TYPE_P (type))
	{
	  begin = save_సమాసం (begin);
	  అడుగు = సూచిక_int_కూడిక (loc, PLUS_సమాసం, begin, అడుగు);
	  అడుగు = fold_build2_loc (loc, MINUS_సమాసం, sizetype,
				  fold_convert (sizetype, అడుగు),
				  fold_convert (sizetype, begin));
	  అడుగు = fold_convert (ssizetype, అడుగు);
	}
      ఒకవేళ (integer_zerop (అడుగు))
	{
	  error_at (loc, "iterator %qD has zero step", var);
	  ret = నిజం;
	  కొనసాగు;
	}

      ఒకవేళ (begin == error_mark_కణుపు
	  || చివర == error_mark_కణుపు
	  || అడుగు == error_mark_కణుపు
	  || orig_అడుగు == error_mark_కణుపు)
	{
	  ret = నిజం;
	  కొనసాగు;
	}
      hash_సమితి<వృక్షం> pset;
      వృక్షం it2;
      కొరకు (it2 = వృక్షం_CHAIN (it); it2; it2 = వృక్షం_CHAIN (it2))
	{
	  వృక్షం var2 = OMP_ITERATOR_VAR (it2);
	  వృక్షం begin2 = OMP_ITERATOR_BEGIN (it2);
	  వృక్షం end2 = OMP_ITERATOR_చివర (it2);
	  వృక్షం step2 = OMP_ITERATOR_అడుగు (it2);
	  వృక్షం type2 = వృక్షం_TYPE (var2);
	  location_t loc2 = DECL_ఆధారం_LOCATION (var2);
	  నిర్మాణం c_కనుగొను_omp_var_s దత్తాంశం = { var, &pset };
	  ఒకవేళ (walk_వృక్షం (&type2, c_కనుగొను_omp_var_r, &దత్తాంశం, &pset))
	    {
	      error_at (loc2,
			"type of iterator %qD refers to outer iterator %qD",
			var2, var);
	      ఆపు;
	    }
	  లేకపోతే ఒకవేళ (walk_వృక్షం (&begin2, c_కనుగొను_omp_var_r, &దత్తాంశం, &pset))
	    {
	      error_at (సమాసం_LOC_OR_LOC (begin2, loc2),
			"begin expression refers to outer iterator %qD", var);
	      ఆపు;
	    }
	  లేకపోతే ఒకవేళ (walk_వృక్షం (&end2, c_కనుగొను_omp_var_r, &దత్తాంశం, &pset))
	    {
	      error_at (సమాసం_LOC_OR_LOC (end2, loc2),
			"end expression refers to outer iterator %qD", var);
	      ఆపు;
	    }
	  లేకపోతే ఒకవేళ (walk_వృక్షం (&step2, c_కనుగొను_omp_var_r, &దత్తాంశం, &pset))
	    {
	      error_at (సమాసం_LOC_OR_LOC (step2, loc2),
			"step expression refers to outer iterator %qD", var);
	      ఆపు;
	    }
	}
      ఒకవేళ (it2)
	{
	  ret = నిజం;
	  కొనసాగు;
	}
      OMP_ITERATOR_BEGIN (it) = begin;
      OMP_ITERATOR_చివర (it) = చివర;
      OMP_ITERATOR_అడుగు (it) = అడుగు;
      OMP_ITERATOR_ORIG_అడుగు (it) = orig_అడుగు;
    }
  తిరిగి ret;
}

/* Ensure that pointers are used in OpenACC attach and detach clauses.
   Return true if an error has been detected.  */

స్థిర తార్కిక
c_oacc_check_attachments (వృక్షం c)
{
  ఒకవేళ (OMP_CLAUSE_సంకేతం (c) != OMP_CLAUSE_MAP)
    తిరిగి అబద్ధం;

  /* OpenACC attach / detach clauses must be pointers.  */
  ఒకవేళ (OMP_CLAUSE_MAP_రకం (c) == GOMP_MAP_ATTACH
      || OMP_CLAUSE_MAP_రకం (c) == GOMP_MAP_DETACH)
    {
      వృక్షం t = OMP_CLAUSE_DECL (c);

      అయితే (వృక్షం_సంకేతం (t) == OMP_ARRAY_SECTION)
	t = వృక్షం_నిర్వాహ్యం (t, 0);

      ఒకవేళ (వృక్షం_సంకేతం (వృక్షం_TYPE (t)) != సూచిక_TYPE)
	{
	  error_at (OMP_CLAUSE_LOCATION (c), "expected pointer in %qs clause",
		    user_omp_clause_సంకేతం_name (c, నిజం));
	  తిరిగి నిజం;
	}
    }

  తిరిగి అబద్ధం;
}

/* For all elements of CLAUSES, validate them against their constraints.
   Remove any elements from the list that are invalid.  */

వృక్షం
c_ముగింపు_omp_clauses (వృక్షం clauses, గణన c_omp_region_type ort)
{
  bitmap_తల generic_తల, firstprivate_తల, lastprivate_తల;
  bitmap_తల aligned_తల, map_తల, map_క్షేత్రం_తల, map_firstprivate_తల;
  bitmap_తల oacc_reduction_తల, is_on_device_తల;
  వృక్షం c, t, type, *pc;
  వృక్షం simdlen = NULL_వృక్షం, safelen = NULL_వృక్షం;
  తార్కిక branch_చూసిన = అబద్ధం;
  తార్కిక copyprivate_చూసిన = అబద్ధం;
  తార్కిక mergeable_చూసిన = అబద్ధం;
  వృక్షం *detach_చూసిన = ఖాళీ;
  తార్కిక రేఖీయ_variable_అడుగు_check = అబద్ధం;
  వృక్షం *nowait_clause = ఖాళీ;
  వృక్షం *grainsize_చూసిన = ఖాళీ;
  తార్కిక అంకె_tasks_చూసిన = అబద్ధం;
  వృక్షం ordered_clause = NULL_వృక్షం;
  వృక్షం కాలపట్టిక_clause = NULL_వృక్షం;
  తార్కిక oacc_async = అబద్ధం;
  వృక్షం చివరి_iterators = NULL_వృక్షం;
  తార్కిక చివరి_iterators_remove = అబద్ధం;
  వృక్షం *nogroup_చూసిన = ఖాళీ;
  వృక్షం *క్రమం_clause = ఖాళీ;
  /* 1 if normal/task reduction has been seen, -1 if inscan reduction
     has been seen, -2 if mixed inscan/normal reduction diagnosed.  */
  పూర్ణాంకం reduction_చూసిన = 0;
  తార్కిక allocate_చూసిన = అబద్ధం;
  తార్కిక implicit_moved = అబద్ధం;
  తార్కిక లక్ష్యం_లోపల_reduction_చూసిన = అబద్ధం;
  వృక్షం *నిండిన_చూసిన = ఖాళీ;
  తార్కిక partial_చూసిన = అబద్ధం;
  తార్కిక openacc = (ort & C_ORT_ACC) != 0;
  తార్కిక init_చూసిన = అబద్ధం;
  తార్కిక init_use_destroy_చూసిన = అబద్ధం;
  వృక్షం init_no_targetsync_clause = NULL_వృక్షం;
  వృక్షం depend_clause = NULL_వృక్షం;

  ఒకవేళ (!openacc)
    clauses = omp_remove_duplicate_maps (clauses, నిజం);

  bitmap_obstack_initialize (ఖాళీ);
  bitmap_initialize (&generic_తల, &bitmap_default_obstack);
  bitmap_initialize (&firstprivate_తల, &bitmap_default_obstack);
  bitmap_initialize (&lastprivate_తల, &bitmap_default_obstack);
  bitmap_initialize (&aligned_తల, &bitmap_default_obstack);
  /* If ort == C_ORT_OMP_DECLARE_SIMD used as uniform_head instead.  */
  bitmap_initialize (&map_తల, &bitmap_default_obstack);
  bitmap_initialize (&map_క్షేత్రం_తల, &bitmap_default_obstack);
  bitmap_initialize (&map_firstprivate_తల, &bitmap_default_obstack);
  /* If ort == C_ORT_OMP used as nontemporal_head or use_device_xxx_head
     instead and for ort == C_ORT_OMP_TARGET used as in_reduction_head.  */
  bitmap_initialize (&oacc_reduction_తల, &bitmap_default_obstack);
  bitmap_initialize (&is_on_device_తల, &bitmap_default_obstack);

  ఒకవేళ (openacc)
    కొరకు (c = clauses; c; c = OMP_CLAUSE_CHAIN (c))
      ఒకవేళ (OMP_CLAUSE_సంకేతం (c) == OMP_CLAUSE_ASYNC)
	{
	  oacc_async = నిజం;
	  ఆపు;
	}

  వృక్షం *grp_ప్రారంభం_p = ఖాళీ, grp_sentinel = NULL_వృక్షం;

  కొరకు (pc = &clauses, c = clauses; c ; c = *pc)
    {
      తార్కిక remove = అబద్ధం;
      తార్కిక need_complete = అబద్ధం;
      తార్కిక need_implicitly_determined = అబద్ధం;

      /* We've reached the end of a list of expanded nodes.  Reset the group
	 start pointer.  */
      ఒకవేళ (c == grp_sentinel)
	{
	  ఒకవేళ (grp_ప్రారంభం_p
	      && OMP_CLAUSE_HAS_ITERATORS (*grp_ప్రారంభం_p))
	    కొరకు (వృక్షం gc = *grp_ప్రారంభం_p; gc != grp_sentinel;
		 gc = OMP_CLAUSE_CHAIN (gc))
	      OMP_CLAUSE_ITERATORS (gc) = OMP_CLAUSE_ITERATORS (*grp_ప్రారంభం_p);
	  grp_ప్రారంభం_p = ఖాళీ;
	}

      ఎంపిక (OMP_CLAUSE_సంకేతం (c))
	{
	స్థితి OMP_CLAUSE_SHARED:
	  need_implicitly_determined = నిజం;
	  వెళ్ళు check_dup_generic;

	స్థితి OMP_CLAUSE_వ్యక్తిగత:
	  need_complete = నిజం;
	  need_implicitly_determined = నిజం;
	  వెళ్ళు check_dup_generic;

	స్థితి OMP_CLAUSE_REDUCTION:
	  ఒకవేళ (reduction_చూసిన == 0)
	    reduction_చూసిన = OMP_CLAUSE_REDUCTION_INSCAN (c) ? -1 : 1;
	  లేకపోతే ఒకవేళ (reduction_చూసిన != -2
		   && reduction_చూసిన != (OMP_CLAUSE_REDUCTION_INSCAN (c)
					 ? -1 : 1))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<inscan%> and non-%<inscan%> %<reduction%> clauses "
			"on the same construct");
	      reduction_చూసిన = -2;
	    }
	  /* FALLTHRU */
	స్థితి OMP_CLAUSE_లోపల_REDUCTION:
	స్థితి OMP_CLAUSE_TASK_REDUCTION:
	  need_implicitly_determined = నిజం;
	  t = OMP_CLAUSE_DECL (c);
	  ఒకవేళ (వృక్షం_సంకేతం (t) == OMP_ARRAY_SECTION)
	    {
	      ఒకవేళ (handle_omp_array_sections (c, ort))
		{
		  remove = నిజం;
		  ఆపు;
		}

	      t = OMP_CLAUSE_DECL (c);
	      ఒకవేళ (OMP_CLAUSE_సంకేతం (c) == OMP_CLAUSE_REDUCTION
		  && OMP_CLAUSE_REDUCTION_INSCAN (c))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%<inscan%> %<reduction%> clause with array "
			    "section");
		  remove = నిజం;
		  ఆపు;
		}
	    }
	  t = require_complete_type (OMP_CLAUSE_LOCATION (c), t);
	  ఒకవేళ (t == error_mark_కణుపు)
	    {
	      remove = నిజం;
	      ఆపు;
	    }
	  ఒకవేళ (oacc_async)
	    c_mark_addressable (t);
	  type = వృక్షం_TYPE (t);
	  ఒకవేళ (వృక్షం_సంకేతం (t) == MEM_REF)
	    type = వృక్షం_TYPE (type);
	  ఒకవేళ (వృక్షం_సంకేతం (type) == ARRAY_TYPE)
	    {
	      వృక్షం oatype = type;
	      gcc_assert (వృక్షం_సంకేతం (t) != MEM_REF);
	      అయితే (వృక్షం_సంకేతం (type) == ARRAY_TYPE)
		type = వృక్షం_TYPE (type);
	      ఒకవేళ (integer_zerop (TYPE_కొలత_UNIT (type)))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD in %<reduction%> clause is a zero size array",
			    t);
		  remove = నిజం;
		  ఆపు;
		}
	      వృక్షం కొలత = కొలత_binop (EXACT_DIV_సమాసం, TYPE_కొలత_UNIT (oatype),
				      TYPE_కొలత_UNIT (type));
	      ఒకవేళ (integer_zerop (కొలత))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD in %<reduction%> clause is a zero size array",
			    t);
		  remove = నిజం;
		  ఆపు;
		}
	      కొలత = కొలత_binop (MINUS_సమాసం, కొలత, కొలత_one_కణుపు);
	      కొలత = save_సమాసం (కొలత);
	      వృక్షం సూచీ_type = build_సూచీ_type (కొలత);
	      వృక్షం atype = c_build_array_type (TYPE_MAIN_VARIANT (type),
					       సూచీ_type);
	      atype = c_build_qualified_type (atype, TYPE_QUALS (type));
	      వృక్షం ptype = c_build_సూచిక_type (type);
	      ఒకవేళ (వృక్షం_సంకేతం (వృక్షం_TYPE (t)) == ARRAY_TYPE)
		t = build_fold_addr_సమాసం (t);
	      t = build2 (MEM_REF, atype, t, build_int_cst (ptype, 0));
	      OMP_CLAUSE_DECL (c) = t;
	    }
	  ఒకవేళ (TYPE_ATOMIC (type))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<_Atomic%> %qE in %<reduction%> clause", t);
	      remove = నిజం;
	      ఆపు;
	    }
	  ఒకవేళ (OMP_CLAUSE_సంకేతం (c) != OMP_CLAUSE_REDUCTION
	      || OMP_CLAUSE_REDUCTION_TASK (c))
	    {
	      /* Disallow zero sized or potentially zero sized task
		 reductions.  */
	      ఒకవేళ (integer_zerop (TYPE_కొలత_UNIT (type)))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "zero sized type %qT in %qs clause", type,
			    omp_clause_సంకేతం_name[OMP_CLAUSE_సంకేతం (c)]);
		  remove = నిజం;
		  ఆపు;
		}
	      లేకపోతే ఒకవేళ (వృక్షం_సంకేతం (TYPE_కొలత_UNIT (type)) != INTEGER_CST)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "variable sized type %qT in %qs clause", type,
			    omp_clause_సంకేతం_name[OMP_CLAUSE_సంకేతం (c)]);
		  remove = నిజం;
		  ఆపు;
		}
	    }
	  ఒకవేళ (OMP_CLAUSE_REDUCTION_PLACEHOLDER (c) == NULL_వృక్షం
	      && (FLOAT_TYPE_P (type)
		  || వృక్షం_సంకేతం (type) == COMPLEX_TYPE))
	    {
	      గణన వృక్షం_సంకేతం_2 r_సంకేతం = OMP_CLAUSE_REDUCTION_సంకేతం (c);
	      స్థిరరాశి అక్షరం *r_name = ఖాళీ;

	      ఎంపిక (r_సంకేతం)
		{
		స్థితి PLUS_సమాసం:
		స్థితి MULT_సమాసం:
		స్థితి MINUS_సమాసం:
		స్థితి TRUTH_ANDIF_సమాసం:
		స్థితి TRUTH_ORIF_సమాసం:
		  ఆపు;
		స్థితి MIN_సమాసం:
		  ఒకవేళ (వృక్షం_సంకేతం (type) == COMPLEX_TYPE)
		    r_name = "min";
		  ఆపు;
		స్థితి MAX_సమాసం:
		  ఒకవేళ (వృక్షం_సంకేతం (type) == COMPLEX_TYPE)
		    r_name = "max";
		  ఆపు;
		స్థితి బిట్టు_AND_సమాసం:
		  r_name = "&";
		  ఆపు;
		స్థితి బిట్టు_XOR_సమాసం:
		  r_name = "^";
		  ఆపు;
		స్థితి బిట్టు_IOR_సమాసం:
		  r_name = "|";
		  ఆపు;
		అప్రమేయ:
		  gcc_unreachable ();
		}
	      ఒకవేళ (r_name)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qE has invalid type for %<reduction(%s)%>",
			    t, r_name);
		  remove = నిజం;
		  ఆపు;
		}
	    }
	  లేకపోతే ఒకవేళ (OMP_CLAUSE_REDUCTION_PLACEHOLDER (c) == error_mark_కణుపు)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"user defined reduction not found for %qE", t);
	      remove = నిజం;
	      ఆపు;
	    }
	  లేకపోతే ఒకవేళ (OMP_CLAUSE_REDUCTION_PLACEHOLDER (c))
	    {
	      వృక్షం list = OMP_CLAUSE_REDUCTION_PLACEHOLDER (c);
	      type = TYPE_MAIN_VARIANT (type);
	      వృక్షం placeholder = build_decl (OMP_CLAUSE_LOCATION (c),
					     VAR_DECL, NULL_వృక్షం, type);
	      వృక్షం decl_placeholder = NULL_వృక్షం;
	      OMP_CLAUSE_REDUCTION_PLACEHOLDER (c) = placeholder;
	      DECL_ARTIFICIAL (placeholder) = 1;
	      DECL_IGNORED_P (placeholder) = 1;
	      ఒకవేళ (వృక్షం_సంకేతం (t) == MEM_REF)
		{
		  decl_placeholder = build_decl (OMP_CLAUSE_LOCATION (c),
						 VAR_DECL, NULL_వృక్షం, type);
		  OMP_CLAUSE_REDUCTION_DECL_PLACEHOLDER (c) = decl_placeholder;
		  DECL_ARTIFICIAL (decl_placeholder) = 1;
		  DECL_IGNORED_P (decl_placeholder) = 1;
		}
	      ఒకవేళ (వృక్షం_ADDRESSABLE (వృక్షం_VEC_ELT (list, 0)))
		c_mark_addressable (placeholder);
	      ఒకవేళ (వృక్షం_ADDRESSABLE (వృక్షం_VEC_ELT (list, 1)))
		c_mark_addressable (decl_placeholder ? decl_placeholder
				    : OMP_CLAUSE_DECL (c));
	      OMP_CLAUSE_REDUCTION_విలీనం (c)
		= c_clone_omp_udr (వృక్షం_VEC_ELT (list, 2),
				   వృక్షం_VEC_ELT (list, 0),
				   వృక్షం_VEC_ELT (list, 1),
				   decl_placeholder ? decl_placeholder
				   : OMP_CLAUSE_DECL (c), placeholder);
	      OMP_CLAUSE_REDUCTION_విలీనం (c)
		= build3_loc (OMP_CLAUSE_LOCATION (c), BIND_సమాసం,
			      void_type_కణుపు, NULL_వృక్షం,
			      OMP_CLAUSE_REDUCTION_విలీనం (c), NULL_వృక్షం);
	      వృక్షం_SIDE_EFFECTS (OMP_CLAUSE_REDUCTION_విలీనం (c)) = 1;
	      ఒకవేళ (వృక్షం_VEC_నిడివి (list) == 6)
		{
		  ఒకవేళ (వృక్షం_ADDRESSABLE (వృక్షం_VEC_ELT (list, 3)))
		    c_mark_addressable (decl_placeholder ? decl_placeholder
					: OMP_CLAUSE_DECL (c));
		  ఒకవేళ (వృక్షం_ADDRESSABLE (వృక్షం_VEC_ELT (list, 4)))
		    c_mark_addressable (placeholder);
		  వృక్షం init = వృక్షం_VEC_ELT (list, 5);
		  ఒకవేళ (init == error_mark_కణుపు)
		    init = DECL_INITIAL (వృక్షం_VEC_ELT (list, 3));
		  OMP_CLAUSE_REDUCTION_INIT (c)
		    = c_clone_omp_udr (init, వృక్షం_VEC_ELT (list, 4),
				       వృక్షం_VEC_ELT (list, 3),
				       decl_placeholder ? decl_placeholder
				       : OMP_CLAUSE_DECL (c), placeholder);
		  ఒకవేళ (వృక్షం_VEC_ELT (list, 5) == error_mark_కణుపు)
		    {
		      వృక్షం v = decl_placeholder ? decl_placeholder : t;
		      OMP_CLAUSE_REDUCTION_INIT (c)
			= build2 (INIT_సమాసం, వృక్షం_TYPE (v), v,
				  OMP_CLAUSE_REDUCTION_INIT (c));
		    }
		  ఒకవేళ (walk_వృక్షం (&OMP_CLAUSE_REDUCTION_INIT (c),
				 c_కనుగొను_omp_placeholder_r,
				 placeholder, ఖాళీ))
		    OMP_CLAUSE_REDUCTION_OMP_ORIG_REF (c) = 1;
		}
	      లేకపోతే
		{
		  వృక్షం init;
		  వృక్షం v = decl_placeholder ? decl_placeholder : t;
		  ఒకవేళ (AGGREGATE_TYPE_P (వృక్షం_TYPE (v)))
		    init = build_constructor (వృక్షం_TYPE (v), ఖాళీ);
		  లేకపోతే
		    init = fold_convert (వృక్షం_TYPE (v), integer_zero_కణుపు);
		  OMP_CLAUSE_REDUCTION_INIT (c)
		    = build2 (INIT_సమాసం, వృక్షం_TYPE (v), v, init);
		}
	      OMP_CLAUSE_REDUCTION_INIT (c)
		= build3_loc (OMP_CLAUSE_LOCATION (c), BIND_సమాసం,
			      void_type_కణుపు, NULL_వృక్షం,
			       OMP_CLAUSE_REDUCTION_INIT (c), NULL_వృక్షం);
	      వృక్షం_SIDE_EFFECTS (OMP_CLAUSE_REDUCTION_INIT (c)) = 1;
	    }
	  ఒకవేళ (వృక్షం_సంకేతం (t) == MEM_REF)
	    {
	      ఒకవేళ (TYPE_కొలత_UNIT (వృక్షం_TYPE (వృక్షం_TYPE (t))) == NULL_వృక్షం
		  || వృక్షం_సంకేతం (TYPE_కొలత_UNIT (వృక్షం_TYPE (వృక్షం_TYPE (t))))
		     != INTEGER_CST)
		{
		  sorry ("variable length element type in array "
			 "%<reduction%> clause");
		  remove = నిజం;
		  ఆపు;
		}
	      t = వృక్షం_నిర్వాహ్యం (t, 0);
	      ఒకవేళ (వృక్షం_సంకేతం (t) == సూచిక_PLUS_సమాసం)
		t = వృక్షం_నిర్వాహ్యం (t, 0);
	      ఒకవేళ (వృక్షం_సంకేతం (t) == ADDR_సమాసం)
		t = వృక్షం_నిర్వాహ్యం (t, 0);
	    }
	  వెళ్ళు check_dup_generic_t;

	స్థితి OMP_CLAUSE_COPYPRIVATE:
	  copyprivate_చూసిన = నిజం;
	  ఒకవేళ (nowait_clause)
	    {
	      error_at (OMP_CLAUSE_LOCATION (*nowait_clause),
			"%<nowait%> clause must not be used together "
			"with %<copyprivate%> clause");
	      *nowait_clause = OMP_CLAUSE_CHAIN (*nowait_clause);
	      nowait_clause = ఖాళీ;
	    }
	  వెళ్ళు check_dup_generic;

	స్థితి OMP_CLAUSE_COPYIN:
	  t = OMP_CLAUSE_DECL (c);
	  ఒకవేళ (!VAR_P (t) || !DECL_THREAD_LOCAL_P (t))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE must be %<threadprivate%> for %<copyin%>", t);
	      remove = నిజం;
	      ఆపు;
	    }
	  వెళ్ళు check_dup_generic;

	స్థితి OMP_CLAUSE_రేఖీయ:
	  ఒకవేళ (ort != C_ORT_OMP_DECLARE_SIMD)
	    need_implicitly_determined = నిజం;
	  t = OMP_CLAUSE_DECL (c);
	  ఒకవేళ (ort != C_ORT_OMP_DECLARE_SIMD
	      && OMP_CLAUSE_రేఖీయ_రకం (c) != OMP_CLAUSE_రేఖీయ_DEFAULT
	      && OMP_CLAUSE_రేఖీయ_OLD_రేఖీయ_MODIFIER (c))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"modifier should not be specified in %<linear%> "
			"clause on %<simd%> or %<for%> constructs when not "
			"using OpenMP 5.2 modifiers");
	      OMP_CLAUSE_రేఖీయ_రకం (c) = OMP_CLAUSE_రేఖీయ_DEFAULT;
	    }
	  ఒకవేళ (!INTEGRAL_TYPE_P (వృక్షం_TYPE (t))
	      && వృక్షం_సంకేతం (వృక్షం_TYPE (t)) != సూచిక_TYPE)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"linear clause applied to non-integral non-pointer "
			"variable with type %qT", వృక్షం_TYPE (t));
	      remove = నిజం;
	      ఆపు;
	    }
	  ఒకవేళ (TYPE_ATOMIC (వృక్షం_TYPE (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<_Atomic%> %qD in %<linear%> clause", t);
	      remove = నిజం;
	      ఆపు;
	    }
	  ఒకవేళ (ort == C_ORT_OMP_DECLARE_SIMD)
	    {
	      వృక్షం s = OMP_CLAUSE_రేఖీయ_అడుగు (c);
	      ఒకవేళ (వృక్షం_సంకేతం (s) == PARM_DECL)
		{
		  OMP_CLAUSE_రేఖీయ_VARIABLE_STRIDE (c) = 1;
		  /* map_head bitmap is used as uniform_head if
		     declare_simd.  */
		  ఒకవేళ (!bitmap_బిట్టు_p (&map_తల, DECL_UID (s)))
		    రేఖీయ_variable_అడుగు_check = నిజం;
		  వెళ్ళు check_dup_generic;
		}
	      ఒకవేళ (వృక్షం_సంకేతం (s) != INTEGER_CST)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%<linear%> clause step %qE is neither constant "
			    "nor a parameter", s);
		  remove = నిజం;
		  ఆపు;
		}
	    }
	  ఒకవేళ (వృక్షం_సంకేతం (వృక్షం_TYPE (OMP_CLAUSE_DECL (c))) == సూచిక_TYPE)
	    {
	      వృక్షం s = OMP_CLAUSE_రేఖీయ_అడుగు (c);
	      s = సూచిక_int_కూడిక (OMP_CLAUSE_LOCATION (c), PLUS_సమాసం,
				   OMP_CLAUSE_DECL (c), s);
	      s = fold_build2_loc (OMP_CLAUSE_LOCATION (c), MINUS_సమాసం,
				   sizetype, fold_convert (sizetype, s),
				   fold_convert
				     (sizetype, OMP_CLAUSE_DECL (c)));
	      ఒకవేళ (s == error_mark_కణుపు)
		s = కొలత_one_కణుపు;
	      OMP_CLAUSE_రేఖీయ_అడుగు (c) = s;
	    }
	  లేకపోతే
	    OMP_CLAUSE_రేఖీయ_అడుగు (c)
	      = fold_convert (వృక్షం_TYPE (t), OMP_CLAUSE_రేఖీయ_అడుగు (c));
	  వెళ్ళు check_dup_generic;

	check_dup_generic:
	  t = OMP_CLAUSE_DECL (c);
	check_dup_generic_t:
	  ఒకవేళ (!VAR_P (t) && వృక్షం_సంకేతం (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in clause %qs", t,
			omp_clause_సంకేతం_name[OMP_CLAUSE_సంకేతం (c)]);
	      remove = నిజం;
	    }
	  లేకపోతే ఒకవేళ ((openacc && OMP_CLAUSE_సంకేతం (c) == OMP_CLAUSE_REDUCTION)
		   || (ort == C_ORT_OMP
		       && (OMP_CLAUSE_సంకేతం (c) == OMP_CLAUSE_USE_DEVICE_PTR
			   || (OMP_CLAUSE_సంకేతం (c)
			       == OMP_CLAUSE_USE_DEVICE_ADDR)))
		   || (ort == C_ORT_OMP_లక్ష్యం
		       && OMP_CLAUSE_సంకేతం (c) == OMP_CLAUSE_లోపల_REDUCTION))
	    {
	      ఒకవేళ (OMP_CLAUSE_సంకేతం (c) == OMP_CLAUSE_లోపల_REDUCTION
		  && (bitmap_బిట్టు_p (&generic_తల, DECL_UID (t))
		      || bitmap_బిట్టు_p (&firstprivate_తల, DECL_UID (t))))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD appears more than once in data-sharing "
			    "clauses", t);
		  remove = నిజం;
		  ఆపు;
		}
	      ఒకవేళ (OMP_CLAUSE_సంకేతం (c) == OMP_CLAUSE_లోపల_REDUCTION)
		లక్ష్యం_లోపల_reduction_చూసిన = నిజం;
	      ఒకవేళ (bitmap_బిట్టు_p (&oacc_reduction_తల, DECL_UID (t)))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    openacc
			    ? "%qD appears more than once in reduction clauses"
			    : "%qD appears more than once in data clauses",
			    t);
		  remove = నిజం;
		}
	      లేకపోతే
		bitmap_సమితి_బిట్టు (&oacc_reduction_తల, DECL_UID (t));
	    }
	  లేకపోతే ఒకవేళ (bitmap_బిట్టు_p (&generic_తల, DECL_UID (t))
		   || bitmap_బిట్టు_p (&firstprivate_తల, DECL_UID (t))
		   || bitmap_బిట్టు_p (&lastprivate_తల, DECL_UID (t))
		   || bitmap_బిట్టు_p (&map_firstprivate_తల, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE appears more than once in data clauses", t);
	      remove = నిజం;
	    }
	  లేకపోతే ఒకవేళ ((OMP_CLAUSE_సంకేతం (c) == OMP_CLAUSE_వ్యక్తిగత
		    || OMP_CLAUSE_సంకేతం (c) == OMP_CLAUSE_HAS_DEVICE_ADDR
		    || OMP_CLAUSE_సంకేతం (c) == OMP_CLAUSE_IS_DEVICE_PTR)
		   && bitmap_బిట్టు_p (&map_తల, DECL_UID (t)))
	    {
	      ఒకవేళ (openacc)
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD appears more than once in data clauses", t);
	      లేకపోతే
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD appears both in data and map clauses", t);
	      remove = నిజం;
	    }
	  లేకపోతే
	    bitmap_సమితి_బిట్టు (&generic_తల, DECL_UID (t));
	  ఆపు;

	స్థితి OMP_CLAUSE_FIRSTPRIVATE:
	  ఒకవేళ (OMP_CLAUSE_FIRSTPRIVATE_IMPLICIT (c) && !implicit_moved)
	    {
	    move_implicit:
	      implicit_moved = నిజం;
	      /* Move firstprivate and map clauses with
		 OMP_CLAUSE_{FIRSTPRIVATE,MAP}_IMPLICIT set to the end of
		 clauses chain.  */
	      వృక్షం cl1 = NULL_వృక్షం, cl2 = NULL_వృక్షం;
	      వృక్షం *pc1 = pc, *pc2 = &cl1, *pc3 = &cl2;
	      అయితే (*pc1)
		ఒకవేళ (OMP_CLAUSE_సంకేతం (*pc1) == OMP_CLAUSE_FIRSTPRIVATE
		    && OMP_CLAUSE_FIRSTPRIVATE_IMPLICIT (*pc1))
		  {
		    *pc3 = *pc1;
		    pc3 = &OMP_CLAUSE_CHAIN (*pc3);
		    *pc1 = OMP_CLAUSE_CHAIN (*pc1);
		  }
		లేకపోతే ఒకవేళ (OMP_CLAUSE_సంకేతం (*pc1) == OMP_CLAUSE_MAP
			 && OMP_CLAUSE_MAP_IMPLICIT (*pc1))
		  {
		    *pc2 = *pc1;
		    pc2 = &OMP_CLAUSE_CHAIN (*pc2);
		    *pc1 = OMP_CLAUSE_CHAIN (*pc1);
		  }
		లేకపోతే
		  pc1 = &OMP_CLAUSE_CHAIN (*pc1);
	      *pc3 = ఖాళీ;
	      *pc2 = cl2;
	      *pc1 = cl1;
	      కొనసాగు;
	    }
	  t = OMP_CLAUSE_DECL (c);
	  need_complete = నిజం;
	  need_implicitly_determined = నిజం;
	  ఒకవేళ (!VAR_P (t) && వృక్షం_సంకేతం (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in clause %<firstprivate%>", t);
	      remove = నిజం;
	    }
	  లేకపోతే ఒకవేళ (OMP_CLAUSE_FIRSTPRIVATE_IMPLICIT (c)
		   && !OMP_CLAUSE_FIRSTPRIVATE_IMPLICIT_లక్ష్యం (c)
		   && bitmap_బిట్టు_p (&map_firstprivate_తల, DECL_UID (t)))
	    remove = నిజం;
	  లేకపోతే ఒకవేళ (bitmap_బిట్టు_p (&generic_తల, DECL_UID (t))
		   || bitmap_బిట్టు_p (&firstprivate_తల, DECL_UID (t))
		   || bitmap_బిట్టు_p (&map_firstprivate_తల, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE appears more than once in data clauses", t);
	      remove = నిజం;
	    }
	  లేకపోతే ఒకవేళ (bitmap_బిట్టు_p (&map_తల, DECL_UID (t))
		   || bitmap_బిట్టు_p (&map_క్షేత్రం_తల, DECL_UID (t)))
	    {
	      ఒకవేళ (openacc)
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD appears more than once in data clauses", t);
	      లేకపోతే ఒకవేళ (OMP_CLAUSE_FIRSTPRIVATE_IMPLICIT (c)
		       && !OMP_CLAUSE_FIRSTPRIVATE_IMPLICIT_లక్ష్యం (c))
		/* Silently drop the clause.  */;
	      లేకపోతే
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD appears both in data and map clauses", t);
	      remove = నిజం;
	    }
	  లేకపోతే
	    bitmap_సమితి_బిట్టు (&firstprivate_తల, DECL_UID (t));
	  ఆపు;

	స్థితి OMP_CLAUSE_LASTPRIVATE:
	  t = OMP_CLAUSE_DECL (c);
	  need_complete = నిజం;
	  need_implicitly_determined = నిజం;
	  ఒకవేళ (!VAR_P (t) && వృక్షం_సంకేతం (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in clause %<lastprivate%>", t);
	      remove = నిజం;
	    }
	  లేకపోతే ఒకవేళ (bitmap_బిట్టు_p (&generic_తల, DECL_UID (t))
		   || bitmap_బిట్టు_p (&lastprivate_తల, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
		     "%qE appears more than once in data clauses", t);
	      remove = నిజం;
	    }
	  లేకపోతే
	    bitmap_సమితి_బిట్టు (&lastprivate_తల, DECL_UID (t));
	  ఆపు;

	స్థితి OMP_CLAUSE_ALIGNED:
	  t = OMP_CLAUSE_DECL (c);
	  ఒకవేళ (!VAR_P (t) && వృక్షం_సంకేతం (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in %<aligned%> clause", t);
	      remove = నిజం;
	    }
	  లేకపోతే ఒకవేళ (!సూచిక_TYPE_P (వృక్షం_TYPE (t))
		   && వృక్షం_సంకేతం (వృక్షం_TYPE (t)) != ARRAY_TYPE)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE in %<aligned%> clause is neither a pointer nor "
			"an array", t);
	      remove = నిజం;
	    }
	  లేకపోతే ఒకవేళ (TYPE_ATOMIC (వృక్షం_TYPE (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<_Atomic%> %qD in %<aligned%> clause", t);
	      remove = నిజం;
	      ఆపు;
	    }
	  లేకపోతే ఒకవేళ (bitmap_బిట్టు_p (&aligned_తల, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE appears more than once in %<aligned%> clauses",
			t);
	      remove = నిజం;
	    }
	  లేకపోతే
	    bitmap_సమితి_బిట్టు (&aligned_తల, DECL_UID (t));
	  ఆపు;

	స్థితి OMP_CLAUSE_NONTEMPORAL:
	  t = OMP_CLAUSE_DECL (c);
	  ఒకవేళ (!VAR_P (t) && వృక్షం_సంకేతం (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in %<nontemporal%> clause", t);
	      remove = నిజం;
	    }
	  లేకపోతే ఒకవేళ (bitmap_బిట్టు_p (&oacc_reduction_తల, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE appears more than once in %<nontemporal%> "
			"clauses", t);
	      remove = నిజం;
	    }
	  లేకపోతే
	    bitmap_సమితి_బిట్టు (&oacc_reduction_తల, DECL_UID (t));
	  ఆపు;

	స్థితి OMP_CLAUSE_ALLOCATE:
	  t = OMP_CLAUSE_DECL (c);
	  ఒకవేళ (!VAR_P (t) && వృక్షం_సంకేతం (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in %<allocate%> clause", t);
	      remove = నిజం;
	    }
	  లేకపోతే ఒకవేళ (bitmap_బిట్టు_p (&aligned_తల, DECL_UID (t)))
	    {
	      warning_at (OMP_CLAUSE_LOCATION (c), OPT_Wopenmp,
			  "%qE appears more than once in %<allocate%> clauses",
			  t);
	      remove = నిజం;
	    }
	  లేకపోతే
	    {
	      bitmap_సమితి_బిట్టు (&aligned_తల, DECL_UID (t));
	      ఒకవేళ (!OMP_CLAUSE_ALLOCATE_COMBINED (c))
		allocate_చూసిన = నిజం;
	    }
	  ఆపు;

	స్థితి OMP_CLAUSE_DOACROSS:
	  t = OMP_CLAUSE_DECL (c);
	  ఒకవేళ (t == NULL_వృక్షం)
	    ఆపు;
	  ఒకవేళ (OMP_CLAUSE_DOACROSS_రకం (c) == OMP_CLAUSE_DOACROSS_SINK)
	    {
	      gcc_assert (వృక్షం_సంకేతం (t) == వృక్షం_LIST);
	      కొరకు (; t; t = వృక్షం_CHAIN (t))
		{
		  వృక్షం decl = వృక్షం_విలువ (t);
		  ఒకవేళ (వృక్షం_సంకేతం (వృక్షం_TYPE (decl)) == సూచిక_TYPE)
		    {
		      వృక్షం స్థానభ్రంశం = వృక్షం_PURPOSE (t);
		      తార్కిక neg = wi::neg_p (wi::గమ్యం_wide (స్థానభ్రంశం));
		      స్థానభ్రంశం = fold_unary (ABS_సమాసం, వృక్షం_TYPE (స్థానభ్రంశం), స్థానభ్రంశం);
		      వృక్షం t2 = సూచిక_int_కూడిక (OMP_CLAUSE_LOCATION (c),
						 neg ? MINUS_సమాసం : PLUS_సమాసం,
						 decl, స్థానభ్రంశం);
		      t2 = fold_build2_loc (OMP_CLAUSE_LOCATION (c), MINUS_సమాసం,
					    sizetype,
					    fold_convert (sizetype, t2),
					    fold_convert (sizetype, decl));
		      ఒకవేళ (t2 == error_mark_కణుపు)
			{
			  remove = నిజం;
			  ఆపు;
			}
		      వృక్షం_PURPOSE (t) = t2;
		    }
		}
	      ఆపు;
	    }
	  gcc_unreachable ();

	స్థితి OMP_CLAUSE_ఉపయోగిస్తుంది_ALLOCATORS:
	  t = OMP_CLAUSE_ఉపయోగిస్తుంది_ALLOCATORS_ALLOCATOR (c);
	  ఒకవేళ (t == error_mark_కణుపు)
	    {
	      remove = నిజం;
	      ఆపు;
	    }
	  ఒకవేళ ((VAR_P (t) || వృక్షం_సంకేతం (t) == PARM_DECL)
	      && (bitmap_బిట్టు_p (&generic_తల, DECL_UID (t))
		  || bitmap_బిట్టు_p (&map_తల, DECL_UID (t))
		  || bitmap_బిట్టు_p (&firstprivate_తల, DECL_UID (t))
		  || bitmap_బిట్టు_p (&lastprivate_తల, DECL_UID (t))))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE appears more than once in data clauses", t);
	      remove = నిజం;
	      ఆపు;
	    }
	  లేకపోతే
	    bitmap_సమితి_బిట్టు (&generic_తల, DECL_UID (t));
	  ఒకవేళ (వృక్షం_సంకేతం (వృక్షం_TYPE (t)) != ENUMERAL_TYPE
	      || strcmp (IDENTIFIER_సూచిక (TYPE_IDENTIFIER (వృక్షం_TYPE (t))),
			 "omp_allocator_handle_t") != 0)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"allocator %qE must be of %<omp_allocator_handle_t%> "
			"type", t);
	      remove = నిజం;
	      ఆపు;
	    }
	  వృక్షం init;
	  ఒకవేళ (!DECL_P (t)
	      || (వృక్షం_సంకేతం (t) == CONST_DECL
		  && ((init = DECL_INITIAL(t)) == శూన్యసూచిక
		      || వృక్షం_సంకేతం (init) != INTEGER_CST
		      || ((wi::గమ్యం_widest (init) < 0
			   || wi::గమ్యం_widest (init) > GOMP_OMP_PREDEF_ALLOC_MAX)
			  && (wi::గమ్యం_widest (init) < GOMP_OMPX_PREDEF_ALLOC_MIN
			      || (wi::గమ్యం_widest (init)
				  > GOMP_OMPX_PREDEF_ALLOC_MAX))))))
	    {
	      remove = నిజం;
	      error_at (OMP_CLAUSE_LOCATION (c),
			"allocator %qE must be either a variable or a "
			"predefined allocator", t);
	      ఆపు;
	    }
	  లేకపోతే ఒకవేళ (వృక్షం_సంకేతం (t) == CONST_DECL)
	    {
	      /* omp_null_allocator is ignored and for predefined allocators,
		 no special handling is required; thus, mark them removed. */
	      remove = నిజం;

	      ఒకవేళ (OMP_CLAUSE_ఉపయోగిస్తుంది_ALLOCATORS_MEMSPACE (c)
		  || OMP_CLAUSE_ఉపయోగిస్తుంది_ALLOCATORS_TRAITS (c))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "modifiers cannot be used with predefined "
			    "allocator %qE", t);
		  ఆపు;
		}
	    }
	  t = OMP_CLAUSE_ఉపయోగిస్తుంది_ALLOCATORS_MEMSPACE (c);
	  ఒకవేళ (t == error_mark_కణుపు)
	    {
	      remove = నిజం;
	      ఆపు;
	    }
	  ఒకవేళ (t != NULL_వృక్షం
	      && ((వృక్షం_సంకేతం (t) != CONST_DECL && వృక్షం_సంకేతం (t) != INTEGER_CST)
		  || వృక్షం_సంకేతం (వృక్షం_TYPE (t)) != ENUMERAL_TYPE
		  || strcmp (IDENTIFIER_సూచిక (TYPE_IDENTIFIER (వృక్షం_TYPE (t))),
			     "omp_memspace_handle_t") != 0))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c), "memspace modifier %qE must be"
			" constant enum of %<omp_memspace_handle_t%> type", t);
	      remove = నిజం;
	      ఆపు;
	    }
	  t = OMP_CLAUSE_ఉపయోగిస్తుంది_ALLOCATORS_TRAITS (c);
	  ఒకవేళ (t == error_mark_కణుపు)
	    {
	      remove = నిజం;
	      ఆపు;
	    }
	  ఒకవేళ (t != NULL_వృక్షం
	      && t != error_mark_కణుపు
	      && (DECL_EXTERNAL (t)
		  || వృక్షం_సంకేతం (t) == PARM_DECL))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c), "traits array %qE must be "
			"defined in same scope as the construct on which the "
			"clause appears", t);
	      remove = నిజం;
	    }
	  ఒకవేళ (t != NULL_వృక్షం)
	    {
	      తార్కిక type_err = అబద్ధం;

	      ఒకవేళ (వృక్షం_సంకేతం (వృక్షం_TYPE (t)) != ARRAY_TYPE
		  || DECL_కొలత (t) == NULL_వృక్షం
		  || !COMPLETE_TYPE_P (వృక్షం_TYPE (t)))
		type_err = నిజం;
	      లేకపోతే
		{
		  వృక్షం elem_t = వృక్షం_TYPE (వృక్షం_TYPE (t));
		  ఒకవేళ (వృక్షం_సంకేతం (elem_t) != రికార్డు_TYPE
		      || strcmp (IDENTIFIER_సూచిక (TYPE_IDENTIFIER (elem_t)),
				 "omp_alloctrait_t") != 0
		      || !TYPE_READONLY (elem_t))
		    type_err = నిజం;
		}
	      ఒకవేళ (type_err)
		{
		  ఒకవేళ (t != error_mark_కణుపు)
		    error_at (OMP_CLAUSE_LOCATION (c), "traits array %qE must "
			      "be of %<const omp_alloctrait_t []%> type", t);
		  లేకపోతే
		    error_at (OMP_CLAUSE_LOCATION (c), "traits array must "
			      "be of %<const omp_alloctrait_t []%> type");
		  remove = నిజం;
		}
	      లేకపోతే
		{
		  వృక్షం cst_val = decl_constant_విలువ_1 (t, నిజం);
		  ఒకవేళ (cst_val == t)
		    {
		      error_at (OMP_CLAUSE_LOCATION (c), "traits array must be "
				"initialized with constants");

		      remove = నిజం;
		    }
		}
	    }
	  ఒకవేళ (remove)
	    ఆపు;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  కొనసాగు;
	స్థితి OMP_CLAUSE_DEPEND:
	  depend_clause = c;
	  /* FALLTHRU */
	స్థితి OMP_CLAUSE_AFFINITY:
	  t = OMP_CLAUSE_DECL (c);
	  ఒకవేళ (OMP_ITERATOR_DECL_P (t))
	    {
	      ఒకవేళ (వృక్షం_PURPOSE (t) != చివరి_iterators)
		చివరి_iterators_remove
		  = c_omp_ముగింపు_iterators (వృక్షం_PURPOSE (t));
	      చివరి_iterators = వృక్షం_PURPOSE (t);
	      t = వృక్షం_విలువ (t);
	      ఒకవేళ (చివరి_iterators_remove)
		t = error_mark_కణుపు;
	    }
	  లేకపోతే
	    చివరి_iterators = NULL_వృక్షం;
	  ఒకవేళ (వృక్షం_సంకేతం (t) == OMP_ARRAY_SECTION)
	    {
	      ఒకవేళ (handle_omp_array_sections (c, ort))
		remove = నిజం;
	      లేకపోతే ఒకవేళ (OMP_CLAUSE_సంకేతం (c) == OMP_CLAUSE_DEPEND
		       && OMP_CLAUSE_DEPEND_రకం (c) == OMP_CLAUSE_DEPEND_DEPOBJ)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%<depend%> clause with %<depobj%> dependence "
			    "type on array section");
		  remove = నిజం;
		}
	      ఆపు;
	    }
	  ఒకవేళ (t == error_mark_కణుపు)
	    remove = నిజం;
	  లేకపోతే ఒకవేళ (OMP_CLAUSE_సంకేతం (c) == OMP_CLAUSE_DEPEND
		   && t == ridpointers[RID_OMP_ALL_జ్ఞాపకం])
	    {
	      ఒకవేళ (OMP_CLAUSE_DEPEND_రకం (c) != OMP_CLAUSE_DEPEND_బహిర్గతం
		  && OMP_CLAUSE_DEPEND_రకం (c) != OMP_CLAUSE_DEPEND_INOUT)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%<omp_all_memory%> used with %<depend%> kind "
			    "other than %<out%> or %<inout%>");
		  remove = నిజం;
		}
	    }
	  లేకపోతే ఒకవేళ (!lvalue_p (t))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not lvalue expression nor array section in "
			"%qs clause", t,
			omp_clause_సంకేతం_name[OMP_CLAUSE_సంకేతం (c)]);
	      remove = నిజం;
	    }
	  లేకపోతే ఒకవేళ (వృక్షం_సంకేతం (t) == COMPONENT_REF
		   && DECL_C_బిట్టు_క్షేత్రం (వృక్షం_నిర్వాహ్యం (t, 1)))
	    {
	      gcc_assert (OMP_CLAUSE_సంకేతం (c) == OMP_CLAUSE_DEPEND
			  || OMP_CLAUSE_సంకేతం (c) == OMP_CLAUSE_AFFINITY);
	      error_at (OMP_CLAUSE_LOCATION (c),
			"bit-field %qE in %qs clause", t,
			omp_clause_సంకేతం_name[OMP_CLAUSE_సంకేతం (c)]);
	      remove = నిజం;
	    }
	  లేకపోతే ఒకవేళ (OMP_CLAUSE_సంకేతం (c) == OMP_CLAUSE_DEPEND
		   && OMP_CLAUSE_DEPEND_రకం (c) == OMP_CLAUSE_DEPEND_DEPOBJ)
	    {
	      ఒకవేళ (!c_omp_depend_t_p (వృక్షం_TYPE (t)))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qE does not have %<omp_depend_t%> type in "
			    "%<depend%> clause with %<depobj%> dependence "
			    "type", t);
		  remove = నిజం;
		}
	    }
	  లేకపోతే ఒకవేళ (OMP_CLAUSE_సంకేతం (c) == OMP_CLAUSE_DEPEND
		   && c_omp_depend_t_p (వృక్షం_TYPE (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE should not have %<omp_depend_t%> type in "
			"%<depend%> clause with dependence type other than "
			"%<depobj%>", t);
	      remove = నిజం;
	    }
	  ఒకవేళ (!remove)
	    {
	      ఒకవేళ (t == ridpointers[RID_OMP_ALL_జ్ఞాపకం])
		t = null_సూచిక_కణుపు;
	      లేకపోతే
		{
		  వృక్షం addr = build_unary_op (OMP_CLAUSE_LOCATION (c),
					      ADDR_సమాసం, t, అబద్ధం);
		  ఒకవేళ (addr == error_mark_కణుపు)
		    {
		      remove = నిజం;
		      ఆపు;
		    }
		  t = build_పరోక్ష_ref (OMP_CLAUSE_LOCATION (c), addr,
					  RO_UNARY_నక్షత్రం);
		  ఒకవేళ (t == error_mark_కణుపు)
		    {
		      remove = నిజం;
		      ఆపు;
		    }
		}
	      ఒకవేళ (OMP_ITERATOR_DECL_P (OMP_CLAUSE_DECL (c)))
		వృక్షం_విలువ (OMP_CLAUSE_DECL (c)) = t;
	      లేకపోతే
		OMP_CLAUSE_DECL (c) = t;
	    }
	  ఆపు;

	స్థితి OMP_CLAUSE_MAP:
	  ఒకవేళ (OMP_CLAUSE_MAP_IMPLICIT (c) && !implicit_moved)
	    వెళ్ళు move_implicit;
	  ఒకవేళ (OMP_CLAUSE_MAP_రకం (c) == GOMP_MAP_నెట్టు_MAPPER_NAME
	      || OMP_CLAUSE_MAP_రకం (c) == GOMP_MAP_తీయి_MAPPER_NAME)
	    {
	      remove = నిజం;
	      ఆపు;
	    }
	  /* FALLTHRU */
	స్థితి OMP_CLAUSE_గమ్యం:
	స్థితి OMP_CLAUSE_FROM:
	  ఒకవేళ (OMP_CLAUSE_ITERATORS (c)
	      && c_omp_ముగింపు_iterators (OMP_CLAUSE_ITERATORS (c)))
	    {
	      t = error_mark_కణుపు;
	      ఆపు;
	    }
	  /* FALLTHRU */
	స్థితి OMP_CLAUSE__CACHE_:
	  {
	    ఉపయోగించి నామాకాశ omp_addr_tokenizer;
	    auto_vec<omp_addr_token *, 10> addr_టోకెన్లు;

	    t = OMP_CLAUSE_DECL (c);
	    ఒకవేళ (వృక్షం_సంకేతం (t) == OMP_ARRAY_SECTION)
	      {
		grp_ప్రారంభం_p = pc;
		grp_sentinel = OMP_CLAUSE_CHAIN (c);

		ఒకవేళ (handle_omp_array_sections (c, ort))
		  remove = నిజం;
		లేకపోతే
		  {
		    t = OMP_CLAUSE_DECL (c);
		    ఒకవేళ (!omp_mappable_type (వృక్షం_TYPE (t)))
		      {
			error_at (OMP_CLAUSE_LOCATION (c),
				  "array section does not have mappable type "
				  "in %qs clause",
				  omp_clause_సంకేతం_name[OMP_CLAUSE_సంకేతం (c)]);
			remove = నిజం;
		      }
		    లేకపోతే ఒకవేళ (TYPE_ATOMIC (వృక్షం_TYPE (t)))
		      {
			error_at (OMP_CLAUSE_LOCATION (c),
				  "%<_Atomic%> %qE in %qs clause", t,
				  omp_clause_సంకేతం_name[OMP_CLAUSE_సంకేతం (c)]);
			remove = నిజం;
		      }
		    అయితే (వృక్షం_సంకేతం (t) == ARRAY_REF)
		      t = వృక్షం_నిర్వాహ్యం (t, 0);

		    c_omp_చిరునామా_inspector ai (OMP_CLAUSE_LOCATION (c), t);

		    ఒకవేళ (!omp_parse_సమాసం (addr_టోకెన్లు, t))
		      {
			sorry_at (OMP_CLAUSE_LOCATION (c),
				  "unsupported map expression %qE",
				  OMP_CLAUSE_DECL (c));
			remove = నిజం;
			ఆపు;
		      }

		    /* This check is to determine if this will be the only map
		       node created for this clause.  Otherwise, we'll check
		       the following FIRSTPRIVATE_POINTER or ATTACH_DETACH
		       node on the next iteration(s) of the loop.   */
		    ఒకవేళ (addr_టోకెన్లు.నిడివి () >= 4
			&& addr_టోకెన్లు[0]->type == STRUCTURE_పునాది
			&& addr_టోకెన్లు[0]->u.structure_పునాది_రకం == పునాది_DECL
			&& addr_టోకెన్లు[1]->type == ACCESS_పద్ధతి
			&& addr_టోకెన్లు[2]->type == COMPONENT_SELECTOR
			&& addr_టోకెన్లు[3]->type == ACCESS_పద్ధతి
			&& (addr_టోకెన్లు[3]->u.access_రకం == ACCESS_ప్రత్యక్ష
			    || (addr_టోకెన్లు[3]->u.access_రకం
				== ACCESS_సూచీకృత_ARRAY)))
		      {
			వృక్షం rt = addr_టోకెన్లు[1]->సమాసం;

			gcc_assert (DECL_P (rt));

			ఒకవేళ (OMP_CLAUSE_సంకేతం (c) == OMP_CLAUSE_MAP
			    && OMP_CLAUSE_MAP_IMPLICIT (c)
			    && (bitmap_బిట్టు_p (&map_తల, DECL_UID (rt))
				|| bitmap_బిట్టు_p (&map_క్షేత్రం_తల, DECL_UID (rt))
				|| bitmap_బిట్టు_p (&map_firstprivate_తల,
						 DECL_UID (rt))))
			  {
			    remove = నిజం;
			    ఆపు;
			  }
			ఒకవేళ (bitmap_బిట్టు_p (&map_క్షేత్రం_తల, DECL_UID (rt)))
			  ఆపు;
			ఒకవేళ (bitmap_బిట్టు_p (&map_తల, DECL_UID (rt)))
			  {
			    ఒకవేళ (OMP_CLAUSE_సంకేతం (c) != OMP_CLAUSE_MAP)
			      error_at (OMP_CLAUSE_LOCATION (c),
					"%qD appears more than once in motion "
					"clauses", rt);
			    లేకపోతే ఒకవేళ (openacc)
			      error_at (OMP_CLAUSE_LOCATION (c),
					"%qD appears more than once in data "
					"clauses", rt);
			    లేకపోతే
			      error_at (OMP_CLAUSE_LOCATION (c),
					"%qD appears more than once in map "
					"clauses", rt);
			    remove = నిజం;
			  }
			లేకపోతే
			  {
			    bitmap_సమితి_బిట్టు (&map_తల, DECL_UID (rt));
			    bitmap_సమితి_బిట్టు (&map_క్షేత్రం_తల, DECL_UID (rt));
			  }
		      }
		  }
		ఒకవేళ (c_oacc_check_attachments (c))
		  remove = నిజం;
		ఒకవేళ (OMP_CLAUSE_సంకేతం (c) == OMP_CLAUSE_MAP
		    && (OMP_CLAUSE_MAP_రకం (c) == GOMP_MAP_ATTACH
			|| OMP_CLAUSE_MAP_రకం (c) == GOMP_MAP_DETACH)
		    && !OMP_CLAUSE_కొలత (c))
		  /* In this case, we have a single array element which is a
		     pointer, and we already set OMP_CLAUSE_SIZE in
		     handle_omp_array_sections above.  For attach/detach
		     clauses, reset the OMP_CLAUSE_SIZE (representing a bias)
		     to zero here.  */
		  OMP_CLAUSE_కొలత (c) = కొలత_zero_కణుపు;
		ఆపు;
	      }
	    లేకపోతే ఒకవేళ (!omp_parse_సమాసం (addr_టోకెన్లు, t))
	      {
		sorry_at (OMP_CLAUSE_LOCATION (c),
			  "unsupported map expression %qE",
			  OMP_CLAUSE_DECL (c));
		remove = నిజం;
		ఆపు;
	      }
	    ఒకవేళ (t == error_mark_కణుపు)
	      {
		remove = నిజం;
		ఆపు;
	      }

	    వృక్షం attr;
	    ఒకవేళ (DECL_P (t)
		&& OMP_CLAUSE_సంకేతం (c) == OMP_CLAUSE_MAP
		&& (attr = lookup_attribute ("omp declare target",
					     DECL_లక్షణాలు (t)))
		&& విలువ_member (get_identifier ("local"),
				 వృక్షం_విలువ (attr)))
	      {
		error_at (OMP_CLAUSE_LOCATION (c),
			  "device-local variable %qD cannot appear "
			  "in map clause", t);
		remove = నిజం;
		ఆపు;
	      }

	    /* OpenACC attach / detach clauses must be pointers.  */
	    ఒకవేళ (c_oacc_check_attachments (c))
	      {
		remove = నిజం;
		ఆపు;
	      }
	    ఒకవేళ (OMP_CLAUSE_సంకేతం (c) == OMP_CLAUSE_MAP
		&& (OMP_CLAUSE_MAP_రకం (c) == GOMP_MAP_ATTACH
		    || OMP_CLAUSE_MAP_రకం (c) == GOMP_MAP_DETACH)
		&& !OMP_CLAUSE_కొలత (c))
	      /* For attach/detach clauses, set OMP_CLAUSE_SIZE (representing a
		 bias) to zero here, so it is not set erroneously to the pointer
		 size later on in gimplify.cc.  */
	      OMP_CLAUSE_కొలత (c) = కొలత_zero_కణుపు;

	    c_omp_చిరునామా_inspector ai (OMP_CLAUSE_LOCATION (c), t);

	    ఒకవేళ (!ai.check_clause (c))
	      {
		remove = నిజం;
		ఆపు;
	      }

	    ఒకవేళ (!ai.map_supported_p ())
	      {
		sorry_at (OMP_CLAUSE_LOCATION (c),
			  "unsupported map expression %qE",
			  OMP_CLAUSE_DECL (c));
		remove = నిజం;
		ఆపు;
	      }

	    gcc_assert ((addr_టోకెన్లు[0]->type == ARRAY_పునాది
			 || addr_టోకెన్లు[0]->type == STRUCTURE_పునాది)
			&& addr_టోకెన్లు[1]->type == ACCESS_పద్ధతి);

	    t = addr_టోకెన్లు[1]->సమాసం;

	    ఒకవేళ (addr_టోకెన్లు[0]->u.structure_పునాది_రకం != పునాది_DECL)
	      వెళ్ళు skip_decl_checks;

	    /* For OpenMP, we can access a struct "t" and "t.d" on the same
	       mapping.  OpenACC allows multiple fields of the same structure
	       to be written.  */
	    ఒకవేళ (addr_టోకెన్లు[0]->type == STRUCTURE_పునాది
		&& (bitmap_బిట్టు_p (&map_క్షేత్రం_తల, DECL_UID (t))
		    || (!openacc && bitmap_బిట్టు_p (&map_తల, DECL_UID (t)))))
	      వెళ్ళు skip_decl_checks;

	    ఒకవేళ (!VAR_P (t) && వృక్షం_సంకేతం (t) != PARM_DECL)
	      {
		ఒకవేళ (ort != C_ORT_ACC && సమాసం_P (t))
		  ఆపు;

		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qE is not a variable in %qs clause", t,
			  omp_clause_సంకేతం_name[OMP_CLAUSE_సంకేతం (c)]);
		remove = నిజం;
	      }
	    లేకపోతే ఒకవేళ (VAR_P (t) && DECL_THREAD_LOCAL_P (t))
	      {
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD is threadprivate variable in %qs clause", t,
			  omp_clause_సంకేతం_name[OMP_CLAUSE_సంకేతం (c)]);
		remove = నిజం;
	      }
	    లేకపోతే ఒకవేళ ((OMP_CLAUSE_సంకేతం (c) != OMP_CLAUSE_MAP
		      || (OMP_CLAUSE_MAP_రకం (c)
			  != GOMP_MAP_FIRSTPRIVATE_సూచిక))
		     && !c_mark_addressable (t))
	      remove = నిజం;
	    లేకపోతే ఒకవేళ (!(OMP_CLAUSE_సంకేతం (c) == OMP_CLAUSE_MAP
		       && (OMP_CLAUSE_MAP_రకం (c) == GOMP_MAP_సూచిక
			   || (OMP_CLAUSE_MAP_రకం (c)
			       == GOMP_MAP_FIRSTPRIVATE_సూచిక)
			   || (OMP_CLAUSE_MAP_రకం (c)
			       == GOMP_MAP_FORCE_DEVICEPTR)))
		     && t == OMP_CLAUSE_DECL (c)
		     && !omp_mappable_type (వృక్షం_TYPE (t)))
	      {
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD does not have a mappable type in %qs clause", t,
			  omp_clause_సంకేతం_name[OMP_CLAUSE_సంకేతం (c)]);
		remove = నిజం;
	      }
	    లేకపోతే ఒకవేళ (వృక్షం_TYPE (t) == error_mark_కణుపు)
	      remove = నిజం;
	    లేకపోతే ఒకవేళ (TYPE_ATOMIC (strip_array_types (వృక్షం_TYPE (t))))
	      {
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%<_Atomic%> %qE in %qs clause", t,
			  omp_clause_సంకేతం_name[OMP_CLAUSE_సంకేతం (c)]);
		remove = నిజం;
	      }
	    లేకపోతే ఒకవేళ (OMP_CLAUSE_సంకేతం (c) == OMP_CLAUSE_MAP
		     && OMP_CLAUSE_MAP_IMPLICIT (c)
		     && (bitmap_బిట్టు_p (&map_తల, DECL_UID (t))
			 || bitmap_బిట్టు_p (&map_క్షేత్రం_తల, DECL_UID (t))
			 || bitmap_బిట్టు_p (&map_firstprivate_తల,
					  DECL_UID (t))))
	      remove = నిజం;
	    లేకపోతే ఒకవేళ (OMP_CLAUSE_సంకేతం (c) == OMP_CLAUSE_MAP
		     && (OMP_CLAUSE_MAP_రకం (c)
			 == GOMP_MAP_FIRSTPRIVATE_సూచిక))
	      {
		ఒకవేళ (bitmap_బిట్టు_p (&generic_తల, DECL_UID (t))
		    || bitmap_బిట్టు_p (&firstprivate_తల, DECL_UID (t))
		    || bitmap_బిట్టు_p (&map_firstprivate_తల, DECL_UID (t)))
		  {
		    error_at (OMP_CLAUSE_LOCATION (c),
			      "%qD appears more than once in data clauses", t);
		    remove = నిజం;
		  }
		లేకపోతే ఒకవేళ (bitmap_బిట్టు_p (&map_తల, DECL_UID (t))
			 && !bitmap_బిట్టు_p (&map_క్షేత్రం_తల, DECL_UID (t))
			 && openacc)
		  {
		    error_at (OMP_CLAUSE_LOCATION (c),
			      "%qD appears more than once in data clauses", t);
		    remove = నిజం;
		  }
		లేకపోతే
		  bitmap_సమితి_బిట్టు (&map_firstprivate_తల, DECL_UID (t));
	      }
	    లేకపోతే ఒకవేళ (bitmap_బిట్టు_p (&map_తల, DECL_UID (t))
		     && !bitmap_బిట్టు_p (&map_క్షేత్రం_తల, DECL_UID (t))
		     && ort != C_ORT_OMP
		     && ort != C_ORT_OMP_లక్ష్యం
		     && ort != C_ORT_OMP_EXIT_దత్తాంశం)
	      {
		ఒకవేళ (OMP_CLAUSE_సంకేతం (c) != OMP_CLAUSE_MAP)
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD appears more than once in motion clauses", t);
		లేకపోతే ఒకవేళ (openacc)
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD appears more than once in data clauses", t);
		లేకపోతే
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD appears more than once in map clauses", t);
		remove = నిజం;
	      }
	    లేకపోతే ఒకవేళ (openacc && bitmap_బిట్టు_p (&generic_తల, DECL_UID (t)))
	      {
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD appears more than once in data clauses", t);
		remove = నిజం;
	      }
	    లేకపోతే ఒకవేళ (bitmap_బిట్టు_p (&firstprivate_తల, DECL_UID (t))
		     || bitmap_బిట్టు_p (&is_on_device_తల, DECL_UID (t)))
	      {
		ఒకవేళ (openacc)
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD appears more than once in data clauses", t);
		లేకపోతే
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD appears both in data and map clauses", t);
		remove = నిజం;
	      }
	    లేకపోతే ఒకవేళ (!omp_access_chain_p (addr_టోకెన్లు, 1))
	      {
		bitmap_సమితి_బిట్టు (&map_తల, DECL_UID (t));
		ఒకవేళ (t != OMP_CLAUSE_DECL (c)
		    && వృక్షం_సంకేతం (OMP_CLAUSE_DECL (c)) == COMPONENT_REF)
		  bitmap_సమితి_బిట్టు (&map_క్షేత్రం_తల, DECL_UID (t));
	      }

	  skip_decl_checks:
	    /* If we call omp_expand_map_clause in handle_omp_array_sections,
	       the containing loop (here) iterates through the new nodes
	       created by that expansion.  Avoid expanding those again (just
	       by checking the node type).  */
	    ఒకవేళ (!remove
		&& ort != C_ORT_DECLARE_SIMD
		&& (OMP_CLAUSE_సంకేతం (c) != OMP_CLAUSE_MAP
		    || (OMP_CLAUSE_MAP_రకం (c) != GOMP_MAP_FIRSTPRIVATE_సూచిక
			&& (OMP_CLAUSE_MAP_రకం (c)
			    != GOMP_MAP_FIRSTPRIVATE_REFERENCE)
			&& OMP_CLAUSE_MAP_రకం (c) != GOMP_MAP_ALWAYS_సూచిక
			&& OMP_CLAUSE_MAP_రకం (c) != GOMP_MAP_ATTACH_DETACH
			&& OMP_CLAUSE_MAP_రకం (c) != GOMP_MAP_ATTACH
			&& OMP_CLAUSE_MAP_రకం (c) != GOMP_MAP_DETACH)))
	      {
		grp_ప్రారంభం_p = pc;
		grp_sentinel = OMP_CLAUSE_CHAIN (c);
		వృక్షం nc = ai.expand_map_clause (c, OMP_CLAUSE_DECL (c),
						addr_టోకెన్లు, ort);
		ఒకవేళ (nc != error_mark_కణుపు)
		  c = nc;
	      }
	  }
	  ఆపు;

	స్థితి OMP_CLAUSE_ENTER:
	స్థితి OMP_CLAUSE_LINK:
	స్థితి OMP_CLAUSE_LOCAL:
	  t = OMP_CLAUSE_DECL (c);
	  స్థిరరాశి అక్షరం *cname;
	  cname = omp_clause_సంకేతం_name[OMP_CLAUSE_సంకేతం (c)];
	  ఒకవేళ (OMP_CLAUSE_సంకేతం (c) == OMP_CLAUSE_ENTER
	      && OMP_CLAUSE_ENTER_గమ్యం (c))
	    cname = "to";
	  ఒకవేళ (వృక్షం_సంకేతం (t) == FUNCTION_DECL
	      && OMP_CLAUSE_సంకేతం (c) == OMP_CLAUSE_ENTER)
	    ;
	  లేకపోతే ఒకవేళ (!VAR_P (t))
	    {
	      ఒకవేళ (OMP_CLAUSE_సంకేతం (c) == OMP_CLAUSE_ENTER)
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qE is neither a variable nor a function name in "
			  "clause %qs", t, cname);
	      లేకపోతే
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qE is not a variable in clause %qs", t, cname);
	      remove = నిజం;
	    }
	  లేకపోతే ఒకవేళ (DECL_THREAD_LOCAL_P (t))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qD is threadprivate variable in %qs clause", t,
			cname);
	      remove = నిజం;
	    }
	  లేకపోతే ఒకవేళ (!omp_mappable_type (వృక్షం_TYPE (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qD does not have a mappable type in %qs clause", t,
			cname);
	      remove = నిజం;
	    }
	  ఒకవేళ (remove)
	    ఆపు;
	  ఒకవేళ (bitmap_బిట్టు_p (&generic_తల, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE appears more than once on the same "
			"%<declare target%> directive", t);
	      remove = నిజం;
	    }
	  లేకపోతే
	    bitmap_సమితి_బిట్టు (&generic_తల, DECL_UID (t));
	  ఆపు;

	స్థితి OMP_CLAUSE_ఏకరీతి:
	  t = OMP_CLAUSE_DECL (c);
	  ఒకవేళ (వృక్షం_సంకేతం (t) != PARM_DECL)
	    {
	      ఒకవేళ (DECL_P (t))
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD is not an argument in %<uniform%> clause", t);
	      లేకపోతే
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qE is not an argument in %<uniform%> clause", t);
	      remove = నిజం;
	      ఆపు;
	    }
	  /* map_head bitmap is used as uniform_head if declare_simd.  */
	  bitmap_సమితి_బిట్టు (&map_తల, DECL_UID (t));
	  వెళ్ళు check_dup_generic;

	స్థితి OMP_CLAUSE_IS_DEVICE_PTR:
	స్థితి OMP_CLAUSE_USE_DEVICE_PTR:
	  t = OMP_CLAUSE_DECL (c);
	  ఒకవేళ (OMP_CLAUSE_సంకేతం (c) == OMP_CLAUSE_IS_DEVICE_PTR)
	    bitmap_సమితి_బిట్టు (&is_on_device_తల, DECL_UID (t));
	  ఒకవేళ (వృక్షం_సంకేతం (వృక్షం_TYPE (t)) != సూచిక_TYPE)
	    {
	      ఒకవేళ (OMP_CLAUSE_సంకేతం (c) == OMP_CLAUSE_USE_DEVICE_PTR
		  && !openacc)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qs variable is not a pointer",
			    omp_clause_సంకేతం_name[OMP_CLAUSE_సంకేతం (c)]);
		  remove = నిజం;
		}
	      లేకపోతే ఒకవేళ (వృక్షం_సంకేతం (వృక్షం_TYPE (t)) != ARRAY_TYPE)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qs variable is neither a pointer nor an array",
			    omp_clause_సంకేతం_name[OMP_CLAUSE_సంకేతం (c)]);
		  remove = నిజం;
		}
	    }
	  వెళ్ళు check_dup_generic;

	స్థితి OMP_CLAUSE_HAS_DEVICE_ADDR:
	  t = OMP_CLAUSE_DECL (c);
	  ఒకవేళ (వృక్షం_సంకేతం (t) == OMP_ARRAY_SECTION)
	    {
	      ఒకవేళ (handle_omp_array_sections (c, ort))
		remove = నిజం;
	      లేకపోతే
		{
		  t = OMP_CLAUSE_DECL (c);
		  అయితే (వృక్షం_సంకేతం (t) == ARRAY_REF)
		    t = వృక్షం_నిర్వాహ్యం (t, 0);
		}
	    }
	  bitmap_సమితి_బిట్టు (&is_on_device_తల, DECL_UID (t));
	  ఒకవేళ (VAR_P (t) || వృక్షం_సంకేతం (t) == PARM_DECL)
	    c_mark_addressable (t);
	  వెళ్ళు check_dup_generic_t;

	స్థితి OMP_CLAUSE_USE_DEVICE_ADDR:
	  t = OMP_CLAUSE_DECL (c);
	  ఒకవేళ (VAR_P (t) || వృక్షం_సంకేతం (t) == PARM_DECL)
	    c_mark_addressable (t);
	  వెళ్ళు check_dup_generic;

	స్థితి OMP_CLAUSE_NOWAIT:
	  ఒకవేళ (copyprivate_చూసిన)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<nowait%> clause must not be used together "
			"with %<copyprivate%> clause");
	      remove = నిజం;
	      ఆపు;
	    }
	  nowait_clause = pc;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  కొనసాగు;

	స్థితి OMP_CLAUSE_క్రమం:
	  ఒకవేళ (ordered_clause)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<order%> clause must not be used together "
			"with %<ordered%> clause");
	      remove = నిజం;
	      ఆపు;
	    }
	  లేకపోతే ఒకవేళ (క్రమం_clause)
	    {
	      /* Silently remove duplicates.  */
	      remove = నిజం;
	      ఆపు;
	    }
	  క్రమం_clause = pc;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  కొనసాగు;

	స్థితి OMP_CLAUSE_DETACH:
	  t = OMP_CLAUSE_DECL (c);
	  ఒకవేళ (detach_చూసిన)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"too many %qs clauses on a task construct",
			"detach");
	      remove = నిజం;
	      ఆపు;
	    }
	  detach_చూసిన = pc;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  c_mark_addressable (t);
	  కొనసాగు;

	స్థితి OMP_CLAUSE_IF:
	స్థితి OMP_CLAUSE_SELF:
	స్థితి OMP_CLAUSE_అంకె_దారాలు:
	స్థితి OMP_CLAUSE_అంకె_TEAMS:
	స్థితి OMP_CLAUSE_THREAD_హద్దు:
	స్థితి OMP_CLAUSE_DEFAULT:
	స్థితి OMP_CLAUSE_UNTIED:
	స్థితి OMP_CLAUSE_COLLAPSE:
	స్థితి OMP_CLAUSE_FINAL:
	స్థితి OMP_CLAUSE_DEVICE:
	స్థితి OMP_CLAUSE_DIST_కాలపట్టిక:
	స్థితి OMP_CLAUSE_DYN_GROUPPRIVATE:
	స్థితి OMP_CLAUSE_PARALLEL:
	స్థితి OMP_CLAUSE_FOR:
	స్థితి OMP_CLAUSE_SECTIONS:
	స్థితి OMP_CLAUSE_TASKGROUP:
	స్థితి OMP_CLAUSE_PROC_BIND:
	స్థితి OMP_CLAUSE_DEVICE_TYPE:
	స్థితి OMP_CLAUSE_ప్రాధాన్యత:
	స్థితి OMP_CLAUSE_దారాలు:
	స్థితి OMP_CLAUSE_SIMD:
	స్థితి OMP_CLAUSE_HINT:
	స్థితి OMP_CLAUSE_FILTER:
	స్థితి OMP_CLAUSE_DEFAULTMAP:
	స్థితి OMP_CLAUSE_BIND:
	స్థితి OMP_CLAUSE_అంకె_GANGS:
	స్థితి OMP_CLAUSE_అంకె_WORKERS:
	స్థితి OMP_CLAUSE_సదిశ_నిడివి:
	స్థితి OMP_CLAUSE_ASYNC:
	స్థితి OMP_CLAUSE_WAIT:
	స్థితి OMP_CLAUSE_AUTO:
	స్థితి OMP_CLAUSE_INDEPENDENT:
	స్థితి OMP_CLAUSE_SEQ:
	స్థితి OMP_CLAUSE_GANG:
	స్థితి OMP_CLAUSE_కార్మికుడు:
	స్థితి OMP_CLAUSE_సదిశ:
	స్థితి OMP_CLAUSE_TILE:
	స్థితి OMP_CLAUSE_IF_PRESENT:
	స్థితి OMP_CLAUSE_FINALIZE:
	స్థితి OMP_CLAUSE_NOHOST:
	స్థితి OMP_CLAUSE_పరోక్ష:
	స్థితి OMP_CLAUSE_NOVARIANTS:
	స్థితి OMP_CLAUSE_NOCONTEXT:
	  pc = &OMP_CLAUSE_CHAIN (c);
	  కొనసాగు;

	స్థితి OMP_CLAUSE_GRAINSIZE:
	  grainsize_చూసిన = pc;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  కొనసాగు;

	స్థితి OMP_CLAUSE_అంకె_TASKS:
	  అంకె_tasks_చూసిన = నిజం;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  కొనసాగు;

	స్థితి OMP_CLAUSE_MERGEABLE:
	  mergeable_చూసిన = నిజం;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  కొనసాగు;

	స్థితి OMP_CLAUSE_NOGROUP:
	  nogroup_చూసిన = pc;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  కొనసాగు;

	స్థితి OMP_CLAUSE_కాలపట్టిక:
	  కాలపట్టిక_clause = c;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  కొనసాగు;

	స్థితి OMP_CLAUSE_ORDERED:
	  ordered_clause = c;
	  ఒకవేళ (క్రమం_clause)
	    {
	      error_at (OMP_CLAUSE_LOCATION (*క్రమం_clause),
			"%<order%> clause must not be used together "
			"with %<ordered%> clause");
	      *క్రమం_clause = OMP_CLAUSE_CHAIN (*క్రమం_clause);
	      క్రమం_clause = ఖాళీ;
	    }
	  pc = &OMP_CLAUSE_CHAIN (c);
	  కొనసాగు;

	స్థితి OMP_CLAUSE_SAFELEN:
	  safelen = c;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  కొనసాగు;
	స్థితి OMP_CLAUSE_SIMDLEN:
	  simdlen = c;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  కొనసాగు;

	స్థితి OMP_CLAUSE_నిండిన:
	  నిండిన_చూసిన = pc;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  కొనసాగు;

	స్థితి OMP_CLAUSE_PARTIAL:
	  partial_చూసిన = నిజం;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  కొనసాగు;

	స్థితి OMP_CLAUSE_SIZES:
	  pc = &OMP_CLAUSE_CHAIN (c);
	  కొనసాగు;

	స్థితి OMP_CLAUSE_INBRANCH:
	స్థితి OMP_CLAUSE_NOTINBRANCH:
	  ఒకవేళ (branch_చూసిన)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<inbranch%> clause is incompatible with "
			"%<notinbranch%>");
	      remove = నిజం;
	      ఆపు;
	    }
	  branch_చూసిన = నిజం;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  కొనసాగు;

	స్థితి OMP_CLAUSE_INCLUSIVE:
	స్థితి OMP_CLAUSE_EXCLUSIVE:
	  need_complete = నిజం;
	  need_implicitly_determined = నిజం;
	  t = OMP_CLAUSE_DECL (c);
	  ఒకవేళ (!VAR_P (t) && వృక్షం_సంకేతం (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in clause %qs", t,
			omp_clause_సంకేతం_name[OMP_CLAUSE_సంకేతం (c)]);
	      remove = నిజం;
	    }
	  ఆపు;

	స్థితి OMP_CLAUSE_INIT:
	  init_చూసిన = నిజం;
	  ఒకవేళ (!OMP_CLAUSE_INIT_TARGETSYNC (c))
	    init_no_targetsync_clause = c;
	  /* FALLTHRU */
	స్థితి OMP_CLAUSE_DESTROY:
	స్థితి OMP_CLAUSE_USE:
	  init_use_destroy_చూసిన = నిజం;
	  t = OMP_CLAUSE_DECL (c);
	  ఒకవేళ (bitmap_బిట్టు_p (&generic_తల, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qD appears more than once in action clauses", t);
	      remove = నిజం;
	      ఆపు;
	    }
	  bitmap_సమితి_బిట్టు (&generic_తల, DECL_UID (t));
	  /* FALLTHRU */
	స్థితి OMP_CLAUSE_INTEROP:
	  ఒకవేళ (/* ort == C_ORT_OMP_INTEROP [uncomment for depobj init]  */
		   !c_omp_interop_t_p (వృక్షం_TYPE (OMP_CLAUSE_DECL (c))))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qD must be of %<omp_interop_t%>",
			OMP_CLAUSE_DECL (c));
	      remove = నిజం;
	    }
	  లేకపోతే ఒకవేళ ((OMP_CLAUSE_సంకేతం (c) == OMP_CLAUSE_INIT
		    || OMP_CLAUSE_సంకేతం (c) == OMP_CLAUSE_DESTROY)
		   && వృక్షం_READONLY (OMP_CLAUSE_DECL (c)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
		      "%qD shall not be const", OMP_CLAUSE_DECL (c));
	      remove = నిజం;
	    }
	  pc = &OMP_CLAUSE_CHAIN (c);
	  ఆపు;
	అప్రమేయ:
	  gcc_unreachable ();
	}

      ఒకవేళ (!remove)
	{
	  t = OMP_CLAUSE_DECL (c);

	  ఒకవేళ (need_complete)
	    {
	      t = require_complete_type (OMP_CLAUSE_LOCATION (c), t);
	      ఒకవేళ (t == error_mark_కణుపు)
		remove = నిజం;
	    }

	  ఒకవేళ (need_implicitly_determined)
	    {
	      స్థిరరాశి అక్షరం *share_name = ఖాళీ;

	      ఒకవేళ (VAR_P (t) && DECL_THREAD_LOCAL_P (t))
		share_name = "threadprivate";
	      లేకపోతే ఎంపిక (c_omp_predetermined_sharing (t))
		{
		స్థితి OMP_CLAUSE_DEFAULT_UNSPECIFIED:
		  ఆపు;
		స్థితి OMP_CLAUSE_DEFAULT_SHARED:
		  ఒకవేళ ((OMP_CLAUSE_సంకేతం (c) == OMP_CLAUSE_SHARED
		       || OMP_CLAUSE_సంకేతం (c) == OMP_CLAUSE_FIRSTPRIVATE)
		      && c_omp_predefined_variable (t))
		    /* The __func__ variable and similar function-local
		       predefined variables may be listed in a shared or
		       firstprivate clause.  */
		    ఆపు;
		  share_name = "shared";
		  ఆపు;
		స్థితి OMP_CLAUSE_DEFAULT_వ్యక్తిగత:
		  share_name = "private";
		  ఆపు;
		అప్రమేయ:
		  gcc_unreachable ();
		}
	      ఒకవేళ (share_name)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qE is predetermined %qs for %qs",
			    t, share_name,
			    omp_clause_సంకేతం_name[OMP_CLAUSE_సంకేతం (c)]);
		  remove = నిజం;
		}
	      లేకపోతే ఒకవేళ (వృక్షం_READONLY (t)
		       && OMP_CLAUSE_సంకేతం (c) != OMP_CLAUSE_SHARED
		       && OMP_CLAUSE_సంకేతం (c) != OMP_CLAUSE_FIRSTPRIVATE)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%<const%> qualified %qE may appear only in "
			    "%<shared%> or %<firstprivate%> clauses", t);
		  remove = నిజం;
		}
	    }
	}

      ఒకవేళ (remove)
	{
	  ఒకవేళ (grp_ప్రారంభం_p)
	    {
	      /* If we found a clause to remove, we want to remove the whole
		 expanded group, otherwise gimplify
		 (omp_resolve_clause_dependencies) can get confused.  */
	      *grp_ప్రారంభం_p = grp_sentinel;
	      pc = grp_ప్రారంభం_p;
	      grp_ప్రారంభం_p = ఖాళీ;
	    }
	  లేకపోతే
	    *pc = OMP_CLAUSE_CHAIN (c);
	}
      లేకపోతే
	pc = &OMP_CLAUSE_CHAIN (c);
    }

  ఒకవేళ (grp_ప్రారంభం_p
      && OMP_CLAUSE_HAS_ITERATORS (*grp_ప్రారంభం_p))
    కొరకు (వృక్షం gc = *grp_ప్రారంభం_p; gc; gc = OMP_CLAUSE_CHAIN (gc))
      OMP_CLAUSE_ITERATORS (gc) = OMP_CLAUSE_ITERATORS (*grp_ప్రారంభం_p);

  ఒకవేళ (simdlen
      && safelen
      && వృక్షం_int_cst_lt (OMP_CLAUSE_SAFELEN_సమాసం (safelen),
			  OMP_CLAUSE_SIMDLEN_సమాసం (simdlen)))
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
      OMP_CLAUSE_SIMDLEN_సమాసం (simdlen)
	= OMP_CLAUSE_SAFELEN_సమాసం (safelen);
    }

  ఒకవేళ (ordered_clause
      && కాలపట్టిక_clause
      && (OMP_CLAUSE_కాలపట్టిక_రకం (కాలపట్టిక_clause)
	  & OMP_CLAUSE_కాలపట్టిక_NONMONOTONIC))
    {
      error_at (OMP_CLAUSE_LOCATION (కాలపట్టిక_clause),
		"%<nonmonotonic%> schedule modifier specified together "
		"with %<ordered%> clause");
      OMP_CLAUSE_కాలపట్టిక_రకం (కాలపట్టిక_clause)
	= (గణన omp_clause_కాలపట్టిక_రకం)
	  (OMP_CLAUSE_కాలపట్టిక_రకం (కాలపట్టిక_clause)
	   & ~OMP_CLAUSE_కాలపట్టిక_NONMONOTONIC);
    }

  ఒకవేళ (reduction_చూసిన < 0 && ordered_clause)
    {
      error_at (OMP_CLAUSE_LOCATION (ordered_clause),
		"%qs clause specified together with %<inscan%> "
		"%<reduction%> clause", "ordered");
      reduction_చూసిన = -2;
    }

  ఒకవేళ (reduction_చూసిన < 0 && కాలపట్టిక_clause)
    {
      error_at (OMP_CLAUSE_LOCATION (కాలపట్టిక_clause),
		"%qs clause specified together with %<inscan%> "
		"%<reduction%> clause", "schedule");
      reduction_చూసిన = -2;
    }

  ఒకవేళ (రేఖీయ_variable_అడుగు_check
      || reduction_చూసిన == -2
      || allocate_చూసిన
      || లక్ష్యం_లోపల_reduction_చూసిన)
    కొరకు (pc = &clauses, c = clauses; c ; c = *pc)
      {
	తార్కిక remove = అబద్ధం;
	ఒకవేళ (allocate_చూసిన)
	  ఎంపిక (OMP_CLAUSE_సంకేతం (c))
	    {
	    స్థితి OMP_CLAUSE_REDUCTION:
	    స్థితి OMP_CLAUSE_లోపల_REDUCTION:
	    స్థితి OMP_CLAUSE_TASK_REDUCTION:
	      ఒకవేళ (వృక్షం_సంకేతం (OMP_CLAUSE_DECL (c)) == MEM_REF)
		{
		  t = వృక్షం_నిర్వాహ్యం (OMP_CLAUSE_DECL (c), 0);
		  ఒకవేళ (వృక్షం_సంకేతం (t) == సూచిక_PLUS_సమాసం)
		    t = వృక్షం_నిర్వాహ్యం (t, 0);
		  ఒకవేళ (వృక్షం_సంకేతం (t) == ADDR_సమాసం
		      || పరోక్ష_REF_P (t))
		    t = వృక్షం_నిర్వాహ్యం (t, 0);
		  ఒకవేళ (DECL_P (t))
		    bitmap_clear_బిట్టు (&aligned_తల, DECL_UID (t));
		  ఆపు;
		}
	      /* FALLTHRU */
	    స్థితి OMP_CLAUSE_వ్యక్తిగత:
	    స్థితి OMP_CLAUSE_FIRSTPRIVATE:
	    స్థితి OMP_CLAUSE_LASTPRIVATE:
	    స్థితి OMP_CLAUSE_రేఖీయ:
	      ఒకవేళ (DECL_P (OMP_CLAUSE_DECL (c)))
		bitmap_clear_బిట్టు (&aligned_తల,
				  DECL_UID (OMP_CLAUSE_DECL (c)));
	      ఆపు;
	    అప్రమేయ:
	      ఆపు;
	    }
	ఒకవేళ (OMP_CLAUSE_సంకేతం (c) == OMP_CLAUSE_రేఖీయ
	    && OMP_CLAUSE_రేఖీయ_VARIABLE_STRIDE (c)
	    && !bitmap_బిట్టు_p (&map_తల,
			      DECL_UID (OMP_CLAUSE_రేఖీయ_అడుగు (c))))
	  {
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%<linear%> clause step is a parameter %qD not "
		      "specified in %<uniform%> clause",
		      OMP_CLAUSE_రేఖీయ_అడుగు (c));
	    remove = నిజం;
	  }
	లేకపోతే ఒకవేళ (OMP_CLAUSE_సంకేతం (c) == OMP_CLAUSE_REDUCTION
		 && reduction_చూసిన == -2)
	  OMP_CLAUSE_REDUCTION_INSCAN (c) = 0;
	ఒకవేళ (లక్ష్యం_లోపల_reduction_చూసిన
	    && OMP_CLAUSE_సంకేతం (c) == OMP_CLAUSE_MAP)
	  {
	    వృక్షం t = OMP_CLAUSE_DECL (c);
	    అయితే (handled_component_p (t)
		   || పరోక్ష_REF_P (t)
		   || వృక్షం_సంకేతం (t) == ADDR_సమాసం
		   || వృక్షం_సంకేతం (t) == MEM_REF
		   || వృక్షం_సంకేతం (t) == NON_LVALUE_సమాసం)
	      t = వృక్షం_నిర్వాహ్యం (t, 0);
	    ఒకవేళ (DECL_P (t)
		&& bitmap_బిట్టు_p (&oacc_reduction_తల, DECL_UID (t)))
	      OMP_CLAUSE_MAP_లోపల_REDUCTION (c) = 1;
	  }

	ఒకవేళ (remove)
	  *pc = OMP_CLAUSE_CHAIN (c);
	లేకపోతే
	  pc = &OMP_CLAUSE_CHAIN (c);
      }

  ఒకవేళ (allocate_చూసిన)
    కొరకు (pc = &clauses, c = clauses; c ; c = *pc)
      {
	తార్కిక remove = అబద్ధం;
	ఒకవేళ (OMP_CLAUSE_సంకేతం (c) == OMP_CLAUSE_ALLOCATE
	    && !OMP_CLAUSE_ALLOCATE_COMBINED (c)
	    && bitmap_బిట్టు_p (&aligned_తల, DECL_UID (OMP_CLAUSE_DECL (c))))
	  {
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%qD specified in %<allocate%> clause but not in "
		      "an explicit privatization clause", OMP_CLAUSE_DECL (c));
	    remove = నిజం;
	  }
	ఒకవేళ (remove)
	  *pc = OMP_CLAUSE_CHAIN (c);
	లేకపోతే
	  pc = &OMP_CLAUSE_CHAIN (c);
      }

  ఒకవేళ (nogroup_చూసిన && reduction_చూసిన)
    {
      error_at (OMP_CLAUSE_LOCATION (*nogroup_చూసిన),
		"%<nogroup%> clause must not be used together with "
		"%<reduction%> clause");
      *nogroup_చూసిన = OMP_CLAUSE_CHAIN (*nogroup_చూసిన);
    }

  ఒకవేళ (grainsize_చూసిన && అంకె_tasks_చూసిన)
    {
      error_at (OMP_CLAUSE_LOCATION (*grainsize_చూసిన),
		"%<grainsize%> clause must not be used together with "
		"%<num_tasks%> clause");
      *grainsize_చూసిన = OMP_CLAUSE_CHAIN (*grainsize_చూసిన);
    }

  ఒకవేళ (నిండిన_చూసిన && partial_చూసిన)
    {
      error_at (OMP_CLAUSE_LOCATION (*నిండిన_చూసిన),
		"%<full%> clause must not be used together with "
		"%<partial%> clause");
      *నిండిన_చూసిన = OMP_CLAUSE_CHAIN (*నిండిన_చూసిన);
    }

  ఒకవేళ (detach_చూసిన)
    {
      ఒకవేళ (mergeable_చూసిన)
	{
	  error_at (OMP_CLAUSE_LOCATION (*detach_చూసిన),
		    "%<detach%> clause must not be used together with "
		    "%<mergeable%> clause");
	  *detach_చూసిన = OMP_CLAUSE_CHAIN (*detach_చూసిన);
	}
      లేకపోతే
	{
	  వృక్షం detach_decl = OMP_CLAUSE_DECL (*detach_చూసిన);

	  కొరకు (pc = &clauses, c = clauses; c ; c = *pc)
	    {
	      తార్కిక remove = అబద్ధం;
	      ఒకవేళ ((OMP_CLAUSE_సంకేతం (c) == OMP_CLAUSE_SHARED
		   || OMP_CLAUSE_సంకేతం (c) == OMP_CLAUSE_వ్యక్తిగత
		   || OMP_CLAUSE_సంకేతం (c) == OMP_CLAUSE_FIRSTPRIVATE
		   || OMP_CLAUSE_సంకేతం (c) == OMP_CLAUSE_LASTPRIVATE)
		  && OMP_CLAUSE_DECL (c) == detach_decl)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "the event handle of a %<detach%> clause "
			    "should not be in a data-sharing clause");
		  remove = నిజం;
		}
	      ఒకవేళ (remove)
		*pc = OMP_CLAUSE_CHAIN (c);
	      లేకపోతే
		pc = &OMP_CLAUSE_CHAIN (c);
	    }
	}
    }

  ఒకవేళ (ort == C_ORT_OMP_INTEROP
      && depend_clause
      && (!init_use_destroy_చూసిన
	  || (init_చూసిన && init_no_targetsync_clause)))
    {
      error_at (OMP_CLAUSE_LOCATION (depend_clause),
		"%<depend%> clause requires action clauses with "
		"%<targetsync%> interop-type");
      ఒకవేళ (init_no_targetsync_clause)
	inform (OMP_CLAUSE_LOCATION (init_no_targetsync_clause),
		"%<init%> clause lacks the %<targetsync%> modifier");
    }

  bitmap_obstack_release (ఖాళీ);
  తిరిగి clauses;
}

/* Do processing necessary to make CLAUSES well-formed, where CLAUSES result
   from implicit instantiation of user-defined mappers (in gimplify.cc).  */

వృక్షం
c_omp_ముగింపు_mapper_clauses (వృక్షం clauses)
{
  తిరిగి c_ముగింపు_omp_clauses (clauses, C_ORT_OMP);
}

/* Return code to initialize DST with a copy constructor from SRC.
   C doesn't have copy constructors nor assignment operators, only for
   _Atomic vars we need to perform __atomic_load from src into a temporary
   followed by __atomic_store of the temporary to dst.  */

వృక్షం
c_omp_clause_copy_ctor (వృక్షం clause, వృక్షం dst, వృక్షం src)
{
  ఒకవేళ (!really_atomic_lvalue (dst) && !really_atomic_lvalue (src))
    తిరిగి build2 (MODIFY_సమాసం, వృక్షం_TYPE (dst), dst, src);

  location_t loc = OMP_CLAUSE_LOCATION (clause);
  వృక్షం type = వృక్షం_TYPE (dst);
  వృక్షం nonatomic_type = build_qualified_type (type, TYPE_UNQUALIFIED);
  వృక్షం tmp = create_tmp_var (nonatomic_type);
  వృక్షం tmp_addr = build_fold_addr_సమాసం (tmp);
  వృక్షం_ADDRESSABLE (tmp) = 1;
  suppress_warning (tmp);
  వృక్షం src_addr = build_fold_addr_సమాసం (src);
  వృక్షం dst_addr = build_fold_addr_సమాసం (dst);
  వృక్షం seq_cst = build_int_cst (integer_type_కణుపు, MEMMODEL_SEQ_CST);
  vec<వృక్షం, va_gc> *params;
  /* Expansion of a generic atomic load may require an addition
     element, so allocate enough to prevent a resize.  */
  vec_alloc (params, 4);

  /* Build __atomic_load (&src, &tmp, SEQ_CST);  */
  వృక్షం fndecl = builtin_decl_explicit (BUILT_లోపల_ATOMIC_ఎక్కించు);
  params->శీఘ్ర_నెట్టు (src_addr);
  params->శీఘ్ర_నెట్టు (tmp_addr);
  params->శీఘ్ర_నెట్టు (seq_cst);
  వృక్షం ఎక్కించు = c_build_function_call_vec (loc, vNULL, fndecl, params, ఖాళీ);

  vec_alloc (params, 4);

  /* Build __atomic_store (&dst, &tmp, SEQ_CST);  */
  fndecl = builtin_decl_explicit (BUILT_లోపల_ATOMIC_STORE);
  params->శీఘ్ర_నెట్టు (dst_addr);
  params->శీఘ్ర_నెట్టు (tmp_addr);
  params->శీఘ్ర_నెట్టు (seq_cst);
  వృక్షం store = c_build_function_call_vec (loc, vNULL, fndecl, params, ఖాళీ);
  తిరిగి build2 (COMPOUND_సమాసం, void_type_కణుపు, ఎక్కించు, store);
}

/* Create a transaction node.  */

వృక్షం
c_ముగింపు_transaction (location_t loc, వృక్షం ఖండం, పూర్ణాంకం flags)
{
  వృక్షం stmt = build_stmt (loc, TRANSACTION_సమాసం, ఖండం);
  ఒకవేళ (flags & TM_STMT_ATTR_OUTER)
    TRANSACTION_సమాసం_OUTER (stmt) = 1;
  ఒకవేళ (flags & TM_STMT_ATTR_RELAXED)
    TRANSACTION_సమాసం_RELAXED (stmt) = 1;
  తిరిగి కూడు_stmt (stmt);
}

/* Make a variant type in the proper way for C/C++, propagating qualifiers
   down to the element type of an array.  If ORIG_QUAL_TYPE is not
   NULL, then it should be used as the qualified type
   ORIG_QUAL_INDIRECT levels down in array type derivation (to
   preserve information about the typedef name from which an array
   type was derived).  */

వృక్షం
c_build_qualified_type (వృక్షం type, పూర్ణాంకం type_quals, వృక్షం orig_qual_type,
			కొలత_t orig_qual_పరోక్ష)
{
  ఒకవేళ (type == error_mark_కణుపు)
    తిరిగి type;

  ఒకవేళ (వృక్షం_సంకేతం (type) == ARRAY_TYPE)
    {
      వృక్షం t;
      వృక్షం element_type = c_build_qualified_type (వృక్షం_TYPE (type),
						  type_quals, orig_qual_type,
						  orig_qual_పరోక్ష - 1);

      /* See if we already have an identically qualified type.  */
      ఒకవేళ (orig_qual_type && orig_qual_పరోక్ష == 0)
	t = orig_qual_type;
      లేకపోతే
	కొరకు (t = TYPE_MAIN_VARIANT (type); t; t = TYPE_తదుపరి_VARIANT (t))
	  {
	    ఒకవేళ (TYPE_QUALS (strip_array_types (t)) == type_quals
		&& TYPE_NAME (t) == TYPE_NAME (type)
		&& TYPE_CONTEXT (t) == TYPE_CONTEXT (type)
		&& attribute_list_equal (TYPE_లక్షణాలు (t),
					 TYPE_లక్షణాలు (type)))
	      ఆపు;
	  }
      ఒకవేళ (!t)
	{
          వృక్షం domain = TYPE_DOMAIN (type);

	  t = build_variant_type_copy (type);
	  వృక్షం_TYPE (t) = element_type;
	  TYPE_ADDR_SPACE (t) = TYPE_ADDR_SPACE (element_type);

          ఒకవేళ (TYPE_STRUCTURAL_EQUALITY_P (element_type)
              || (domain && TYPE_STRUCTURAL_EQUALITY_P (domain)))
            సమితి_TYPE_STRUCTURAL_EQUALITY (t);
          లేకపోతే ఒకవేళ (TYPE_CANONICAL (element_type) != element_type
                   || (domain && TYPE_CANONICAL (domain) != domain))
            {
              వృక్షం unqualified_canon
		= c_build_array_type (TYPE_CANONICAL (element_type),
				      domain ? TYPE_CANONICAL (domain)
					     : NULL_వృక్షం);
              ఒకవేళ (TYPE_తిరగేయి_STORAGE_క్రమం (type))
                {
                  unqualified_canon
		    = build_distinct_type_copy (unqualified_canon);
                  TYPE_తిరగేయి_STORAGE_క్రమం (unqualified_canon) = 1;
                }
              TYPE_CANONICAL (t)
		= c_build_qualified_type (unqualified_canon, type_quals);
            }
          లేకపోతే
            TYPE_CANONICAL (t) = t;
	}
      తిరిగి t;
    }

  /* A restrict-qualified pointer type must be a pointer to object or
     incomplete type.  Note that the use of POINTER_TYPE_P also allows
     REFERENCE_TYPEs, which is appropriate for C++.  */
  ఒకవేళ ((type_quals & TYPE_QUAL_RESTRICT)
      && (!సూచిక_TYPE_P (type)
	  || !C_TYPE_OBJECT_OR_INCOMPLETE_P (వృక్షం_TYPE (type))))
    {
      error ("invalid use of %<restrict%>");
      type_quals &= ~TYPE_QUAL_RESTRICT;
    }

  వృక్షం var_type = (orig_qual_type && orig_qual_పరోక్ష == 0
		   ? orig_qual_type
		   : build_qualified_type (type, type_quals));

  gcc_checking_assert (C_TYPE_VARIABLE_కొలత (var_type)
		       == C_TYPE_VARIABLE_కొలత (type));
  gcc_checking_assert (c_type_variably_modified_p (var_type)
		       == c_type_variably_modified_p (type));

  /* A variant type does not inherit the list of incomplete vars from the
     type main variant.  */
  ఒకవేళ ((రికార్డు_OR_UNION_TYPE_P (var_type)
       || వృక్షం_సంకేతం (var_type) == ENUMERAL_TYPE)
      && TYPE_MAIN_VARIANT (var_type) != var_type)
    C_TYPE_INCOMPLETE_VARS (var_type) = 0;
  తిరిగి var_type;
}

/* Build a VA_ARG_EXPR for the C parser.  */

వృక్షం
c_build_va_arg (location_t loc1, వృక్షం సమాసం, location_t loc2, వృక్షం type,
		వృక్షం type_సమాసం)
{
  ఒకవేళ (error_నిర్వాహ్యం_p (type))
    తిరిగి error_mark_కణుపు;
  /* VA_ARG_EXPR cannot be used for a scalar va_list with reverse storage
     order because it takes the address of the expression.  */
  లేకపోతే ఒకవేళ (handled_component_p (సమాసం)
	   && తిరగేయి_storage_క్రమం_for_component_p (సమాసం))
    {
      error_at (loc1, "cannot use %<va_arg%> with reverse storage order");
      తిరిగి error_mark_కణుపు;
    }
  లేకపోతే ఒకవేళ (!COMPLETE_TYPE_P (type))
    {
      error_at (loc2, "second argument to %<va_arg%> is of incomplete "
		"type %qT", type);
      తిరిగి error_mark_కణుపు;
    }
  లేకపోతే ఒకవేళ (వృక్షం_సంకేతం (type) == FUNCTION_TYPE)
    {
      error_at (loc2, "second argument to %<va_arg%> is a function type %qT",
		type);
      తిరిగి error_mark_కణుపు;
    }
  లేకపోతే ఒకవేళ (వృక్షం_సంకేతం (type) == ARRAY_TYPE && C_TYPE_VARIABLE_కొలత (type)
	   && !flag_isoc99)
    {
      error_at (loc2, "second argument to %<va_arg%> is an array type %qT",
		type);
      తిరిగి error_mark_కణుపు;
    }
  లేకపోతే ఒకవేళ (warn_cxx_compat && వృక్షం_సంకేతం (type) == ENUMERAL_TYPE)
    warning_at (loc2, OPT_Wc___compat,
		"C++ requires promoted type, not enum type, in %<va_arg%>");

  ఒకవేళ (flag_isoc99 && వృక్షం_సంకేతం (type) == ARRAY_TYPE)
    {
      warning_at (loc2, 0, "second argument to %<va_arg%> is an array type %qT",
		  type);
      /* We create a trap but evaluate side effects first.  */
      వృక్షం trapfn = builtin_decl_explicit (BUILT_లోపల_TRAP);
      trapfn = build_call_సమాసం_loc (loc2, trapfn, 0);
      వృక్షం e2 = build2 (COMPOUND_సమాసం, void_type_కణుపు, సమాసం, trapfn);
      /* Return a compound literal of the right type.  */
      వృక్షం e1 = build_compound_literal (loc2, type, ఖాళీ, నిజం, 0, ఖాళీ);
      సమాసం = build2 (COMPOUND_సమాసం, type, e2, e1);
    }
  లేకపోతే
    సమాసం = build_va_arg (loc2, సమాసం, type);

  ఒకవేళ (type_సమాసం)
    సమాసం = build2 (COMPOUND_సమాసం, వృక్షం_TYPE (సమాసం), type_సమాసం, సమాసం);

  తిరిగి సమాసం;
}

/* Return truthvalue of whether T1 is the same tree structure as T2.
   Return 1 if they are the same. Return false if they are different.  */

తార్కిక
c_వృక్షం_equal (వృక్షం t1, వృక్షం t2)
{
  గణన వృక్షం_సంకేతం_2 code1, code2;

  ఒకవేళ (t1 == t2)
    తిరిగి నిజం;
  ఒకవేళ (!t1 || !t2)
    తిరిగి అబద్ధం;

  కొరకు (code1 = వృక్షం_సంకేతం (t1); code1 == NON_LVALUE_సమాసం;
       code1 = వృక్షం_సంకేతం (t1))
    t1 = వృక్షం_నిర్వాహ్యం (t1, 0);
  కొరకు (code2 = వృక్షం_సంకేతం (t2); code2 == NON_LVALUE_సమాసం;
       code2 = వృక్షం_సంకేతం (t2))
    t2 = వృక్షం_నిర్వాహ్యం (t2, 0);

  /* They might have become equal now.  */
  ఒకవేళ (t1 == t2)
    తిరిగి నిజం;

  ఒకవేళ (code1 != code2)
    తిరిగి అబద్ధం;

  ఒకవేళ (CONSTANT_CLASS_P (t1) && !comptypes (వృక్షం_TYPE (t1), వృక్షం_TYPE (t2)))
    తిరిగి అబద్ధం;

  ఎంపిక (code1)
    {
    స్థితి INTEGER_CST:
      తిరిగి wi::గమ్యం_wide (t1) == wi::గమ్యం_wide (t2);

    స్థితి REAL_CST:
      తిరిగి real_equal (&వృక్షం_REAL_CST (t1), &వృక్షం_REAL_CST (t2));

    స్థితి STRING_CST:
      తిరిగి వృక్షం_STRING_నిడివి (t1) == వృక్షం_STRING_నిడివి (t2)
	&& !memcmp (వృక్షం_STRING_సూచిక (t1), వృక్షం_STRING_సూచిక (t2),
		    వృక్షం_STRING_నిడివి (t1));

    స్థితి FIXED_CST:
      తిరిగి FIXED_విలువలు_IDENTICAL (వృక్షం_FIXED_CST (t1),
				     వృక్షం_FIXED_CST (t2));

    స్థితి COMPLEX_CST:
      తిరిగి c_వృక్షం_equal (వృక్షం_REALPART (t1), వృక్షం_REALPART (t2))
	     && c_వృక్షం_equal (వృక్షం_IMAGPART (t1), వృక్షం_IMAGPART (t2));

    స్థితి సదిశ_CST:
      తిరిగి నిర్వాహ్యం_equal_p (t1, t2, OEP_ONLY_CONST);

    స్థితి CONSTRUCTOR:
      /* We need to do this when determining whether or not two
	 non-type pointer to member function template arguments
	 are the same.  */
      ఒకవేళ (!comptypes (వృక్షం_TYPE (t1), వృక్షం_TYPE (t2))
	  || CONSTRUCTOR_NELTS (t1) != CONSTRUCTOR_NELTS (t2))
	తిరిగి అబద్ధం;
      {
	వృక్షం క్షేత్రం_2, విలువ;
	గుర్తులేని పూర్ణాంకం i;
	FOR_EACH_CONSTRUCTOR_ELT (CONSTRUCTOR_ELTS (t1), i, క్షేత్రం_2, విలువ)
	  {
	    constructor_elt *elt2 = CONSTRUCTOR_ELT (t2, i);
	    ఒకవేళ (!c_వృక్షం_equal (క్షేత్రం_2, elt2->సూచీ)
		|| !c_వృక్షం_equal (విలువ, elt2->విలువ))
	      తిరిగి అబద్ధం;
	  }
      }
      తిరిగి నిజం;

    స్థితి వృక్షం_LIST:
      ఒకవేళ (!c_వృక్షం_equal (వృక్షం_PURPOSE (t1), వృక్షం_PURPOSE (t2)))
	తిరిగి అబద్ధం;
      ఒకవేళ (!c_వృక్షం_equal (వృక్షం_విలువ (t1), వృక్షం_విలువ (t2)))
	తిరిగి అబద్ధం;
      తిరిగి c_వృక్షం_equal (వృక్షం_CHAIN (t1), వృక్షం_CHAIN (t2));

    స్థితి SAVE_సమాసం:
      తిరిగి c_వృక్షం_equal (వృక్షం_నిర్వాహ్యం (t1, 0), వృక్షం_నిర్వాహ్యం (t2, 0));

    స్థితి CALL_సమాసం:
      {
	వృక్షం arg1, arg2;
	call_సమాసం_arg_iterator iter1, iter2;
	ఒకవేళ (!c_వృక్షం_equal (CALL_సమాసం_FN (t1), CALL_సమాసం_FN (t2)))
	  తిరిగి అబద్ధం;
	కొరకు (arg1 = మొదటి_call_సమాసం_arg (t1, &iter1),
	       arg2 = మొదటి_call_సమాసం_arg (t2, &iter2);
	     arg1 && arg2;
	     arg1 = తదుపరి_call_సమాసం_arg (&iter1),
	       arg2 = తదుపరి_call_సమాసం_arg (&iter2))
	  ఒకవేళ (!c_వృక్షం_equal (arg1, arg2))
	    తిరిగి అబద్ధం;
	ఒకవేళ (arg1 || arg2)
	  తిరిగి అబద్ధం;
	తిరిగి నిజం;
      }

    స్థితి లక్ష్యం_సమాసం:
      {
	వృక్షం o1 = వృక్షం_నిర్వాహ్యం (t1, 0);
	వృక్షం o2 = వృక్షం_నిర్వాహ్యం (t2, 0);

	/* Special case: if either target is an unallocated VAR_DECL,
	   it means that it's going to be unified with whatever the
	   TARGET_EXPR is really supposed to initialize, so treat it
	   as being equivalent to anything.  */
	ఒకవేళ (VAR_P (o1) && DECL_NAME (o1) == NULL_వృక్షం
	    && !DECL_RTL_సమితి_P (o1))
	  /*Nop*/;
	లేకపోతే ఒకవేళ (VAR_P (o2) && DECL_NAME (o2) == NULL_వృక్షం
		 && !DECL_RTL_సమితి_P (o2))
	  /*Nop*/;
	లేకపోతే ఒకవేళ (!c_వృక్షం_equal (o1, o2))
	  తిరిగి అబద్ధం;

	తిరిగి c_వృక్షం_equal (వృక్షం_నిర్వాహ్యం (t1, 1), వృక్షం_నిర్వాహ్యం (t2, 1));
      }

    స్థితి COMPONENT_REF:
      ఒకవేళ (వృక్షం_నిర్వాహ్యం (t1, 1) != వృక్షం_నిర్వాహ్యం (t2, 1))
	తిరిగి అబద్ధం;
      తిరిగి c_వృక్షం_equal (వృక్షం_నిర్వాహ్యం (t1, 0), వృక్షం_నిర్వాహ్యం (t2, 0));

    స్థితి PARM_DECL:
    స్థితి VAR_DECL:
    స్థితి CONST_DECL:
    స్థితి క్షేత్రం_DECL:
    స్థితి FUNCTION_DECL:
    స్థితి IDENTIFIER_కణుపు:
    స్థితి SSA_NAME:
      తిరిగి అబద్ధం;

    స్థితి వృక్షం_VEC:
      {
	గుర్తులేని ix;
	ఒకవేళ (వృక్షం_VEC_నిడివి (t1) != వృక్షం_VEC_నిడివి (t2))
	  తిరిగి అబద్ధం;
	కొరకు (ix = వృక్షం_VEC_నిడివి (t1); ix--;)
	  ఒకవేళ (!c_వృక్షం_equal (వృక్షం_VEC_ELT (t1, ix),
			     వృక్షం_VEC_ELT (t2, ix)))
	    తిరిగి అబద్ధం;
	తిరిగి నిజం;
      }

    CASE_CONVERT:
      ఒకవేళ (!comptypes (వృక్షం_TYPE (t1), వృక్షం_TYPE (t2)))
	తిరిగి అబద్ధం;
      ఆపు;

    అప్రమేయ:
      ఆపు;
    }

  ఎంపిక (వృక్షం_సంకేతం_CLASS (code1))
    {
    స్థితి tcc_unary:
    స్థితి tcc_ద్విమాన:
    స్థితి tcc_comparison:
    స్థితి tcc_వ్యక్తీకరణ:
    స్థితి tcc_vl_exp:
    స్థితి tcc_reference:
    స్థితి tcc_statement:
      {
	పూర్ణాంకం i, n = వృక్షం_నిర్వాహ్యం_నిడివి (t1);

	ఎంపిక (code1)
	  {
	  స్థితి PREINCREMENT_సమాసం:
	  స్థితి PREDECREMENT_సమాసం:
	  స్థితి POSTINCREMENT_సమాసం:
	  స్థితి POSTDECREMENT_సమాసం:
	    n = 1;
	    ఆపు;
	  స్థితి ARRAY_REF:
	    n = 2;
	    ఆపు;
	  అప్రమేయ:
	    ఆపు;
	  }

	ఒకవేళ (వృక్షం_సంకేతం_CLASS (code1) == tcc_vl_exp
	    && n != వృక్షం_నిర్వాహ్యం_నిడివి (t2))
	  తిరిగి అబద్ధం;

	కొరకు (i = 0; i < n; ++i)
	  ఒకవేళ (!c_వృక్షం_equal (వృక్షం_నిర్వాహ్యం (t1, i), వృక్షం_నిర్వాహ్యం (t2, i)))
	    తిరిగి అబద్ధం;

	తిరిగి నిజం;
      }

    స్థితి tcc_type:
      తిరిగి comptypes (t1, t2);
    అప్రమేయ:
      gcc_unreachable ();
    }
}

/* Returns true when the function declaration FNDECL is implicit,
   introduced as a result of a call to an otherwise undeclared
   function, and false otherwise.  */

తార్కిక
c_decl_implicit (const_వృక్షం fndecl)
{
  తిరిగి C_DECL_IMPLICIT (fndecl);
}
