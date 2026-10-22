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

#ضمن "config.h"
#ضمن "system.h"
#ضمن "coretypes.h"
#ضمن "memmodel.h"
#ضمن "target.h"
#ضمن "function.h"
#ضمن "bitmap.h"
#ضمن "c-tree.h"
#ضمن "gimple-expr.h"
#ضمن "predict.h"
#ضمن "stor-layout.h"
#ضمن "trans-mem.h"
#ضمن "varasm.h"
#ضمن "stmt.h"
#ضمن "langhooks.h"
#ضمن "c-lang.h"
#ضمن "intl.h"
#ضمن "tree-iterator.h"
#ضمن "gimplify.h"
#ضمن "tree-inline.h"
#ضمن "omp-general.h"
#ضمن "c-family/c-objc.h"
#ضمن "c-family/c-ubsan.h"
#ضمن "gomp-constants.h"
#ضمن "spellcheck-tree.h"
#ضمن "c-family/c-type-mismatch.h"
#ضمن "stringpool.h"
#ضمن "attribs.h"
#ضمن "asan.h"
#ضمن "realmpfr.h"
#ضمن "tree-pretty-print-markup.h"
#ضمن "gcc-urlifier.h"

/* Possible cases of implicit conversions.  Used to select diagnostic messages
   and control folding initializers in convert_for_assignment.  */
تعداد impl_conv {
  ic_argpass,
  ic_assign,
  ic_init,
  ic_init_const,
  ic_return
};

/* The level of nesting inside "__alignof__".  */
صحيح in_alignof;

/* The level of nesting inside "sizeof".  */
صحيح in_sizeof;

/* The level of nesting inside "countof".  */
صحيح in_countof;

/* The level of nesting inside "typeof".  */
صحيح in_typeof;

/* The level of nesting inside "_Generic".  */
صحيح in_generic;

/* True when parsing OpenMP loop expressions.  */
منطقي c_in_omp_for;

/* True when parsing OpenMP map clause.  */
منطقي c_omp_array_section_p;

/* The argument of last parsed sizeof expression, only to be tested
   if expr.original_code == SIZEOF_EXPR.  */
tree c_last_sizeof_arg;
location_t c_last_sizeof_loc;

/* Nonzero if we might need to print a "missing braces around
   initializer" message within this initializer.  */
ساكن صحيح found_missing_braces;

ساكن منطقي require_constant_value;
ساكن منطقي require_constant_elements;
ساكن منطقي require_constexpr_value;

ساكن tree qualify_type (tree, tree);
بنية comptypes_data;
ساكن منطقي tagged_types_tu_compatible_p (const_tree, const_tree,
					  بنية comptypes_data *);
ساكن منطقي comp_target_types (location_t, tree, tree);
ساكن منطقي function_types_compatible_p (const_tree, const_tree,
					 بنية comptypes_data *);
ساكن منطقي type_lists_compatible_p (const_tree, const_tree,
				     بنية comptypes_data *);
ساكن صحيح convert_arguments (location_t, vec<location_t>, tree,
			      vec<tree, va_gc> *, vec<tree, va_gc> *, tree,
			      tree);
ساكن tree pointer_diff (location_t, tree, tree, tree *);
ساكن tree convert_for_assignment (location_t, location_t, tree, tree, tree,
				    تعداد impl_conv, منطقي, tree, tree, صحيح,
				    صحيح = 0);
ساكن tree valid_compound_expr_initializer (tree, tree);
ساكن فراغ push_string (ثابت حرف *);
ساكن فراغ push_member_name (tree);
ساكن صحيح spelling_length (فراغ);
ساكن حرف *print_spelling (حرف *);
ساكن فراغ warning_init (location_t, صحيح, ثابت حرف *);
ساكن tree digest_init (location_t, tree, tree, tree, tree, منطقي, منطقي, منطقي,
			 منطقي, منطقي, منطقي);
ساكن فراغ output_init_element (location_t, tree, tree, منطقي, tree, tree, منطقي,
				 منطقي, بنية obstack *);
ساكن فراغ output_pending_init_elements (صحيح, بنية obstack *);
ساكن منطقي set_designator (location_t, منطقي, بنية obstack *);
ساكن فراغ push_range_stack (tree, بنية obstack *);
ساكن فراغ add_pending_init (location_t, tree, tree, tree, منطقي,
			      بنية obstack *);
ساكن فراغ set_nonincremental_init (بنية obstack *);
ساكن فراغ set_nonincremental_init_from_string (tree, بنية obstack *);
ساكن tree find_init_member (tree, بنية obstack *);
ساكن فراغ readonly_warning (tree, تعداد lvalue_use);
ساكن صحيح lvalue_or_else (location_t, const_tree, تعداد lvalue_use);
ساكن فراغ record_maybe_used_decl (tree, منطقي address);
ساكن منطقي comptypes_internal (const_tree, const_tree,
				بنية comptypes_data *data);
ساكن منطقي comptypes_check_for_composite (tree t1, tree t2);
ساكن منطقي handle_counted_by_p (tree);
ساكن منطقي top_array_vla_p (const_tree type);


/* Return true if EXP is a null pointer constant, false otherwise.  */

منطقي
null_pointer_constant_p (const_tree expr)
{
  /* This should really operate on c_expr structures, but they aren't
     yet available everywhere required.  */
  tree type = TREE_TYPE (expr);

  /* An integer constant expression with the value 0, such an expression
     cast to type void*, or the predefined constant nullptr, are a null
     pointer constant.  */
  𐤀𐤌 (expr == nullptr_node)
    أرجع true;

  أرجع (TREE_CODE (expr) == INTEGER_CST
	  && !TREE_OVERFLOW (expr)
	  && integer_zerop (expr)
	  && (INTEGRAL_TYPE_P (type)
	      || (TREE_CODE (type) == POINTER_TYPE
		  && VOID_TYPE_P (TREE_TYPE (type))
		  && TYPE_QUALS (TREE_TYPE (type)) == TYPE_UNQUALIFIED)));
}

/* EXPR may appear in an unevaluated part of an integer constant
   expression, but not in an evaluated part.  Wrap it in a
   C_MAYBE_CONST_EXPR, or mark it with TREE_OVERFLOW if it is just an
   INTEGER_CST and we cannot create a C_MAYBE_CONST_EXPR.  */

ساكن tree
note_integer_operands (tree expr)
{
  tree ret;
  𐤀𐤌 (TREE_CODE (expr) == INTEGER_CST && in_late_binary_op)
    {
      ret = copy_node (expr);
      TREE_OVERFLOW (ret) = 1;
    }
  وإلا
    {
      ret = build2 (C_MAYBE_CONST_EXPR, TREE_TYPE (expr), NULL_TREE, expr);
      C_MAYBE_CONST_EXPR_INT_OPERANDS (ret) = 1;
    }
  أرجع ret;
}

/* Having checked whether EXPR may appear in an unevaluated part of an
   integer constant expression and found that it may, remove any
   C_MAYBE_CONST_EXPR noting this fact and return the resulting
   expression.  */

ساكن مضمن tree
remove_c_maybe_const_expr (tree expr)
{
  𐤀𐤌 (TREE_CODE (expr) == C_MAYBE_CONST_EXPR)
    أرجع C_MAYBE_CONST_EXPR_EXPR (expr);
  وإلا
    أرجع expr;
}

/* This is a cache to hold if two types are seen.  */

بنية tagged_tu_seen_cache {
  ثابت بنية tagged_tu_seen_cache * next;
  const_tree t1;
  const_tree t2;
};

/* Do `exp = require_complete_type (loc, exp);' to make sure exp
   does not have an incomplete type.  (That includes void types.)
   LOC is the location of the use.  */

tree
require_complete_type (location_t loc, tree value)
{
  tree type = TREE_TYPE (value);

  𐤀𐤌 (error_operand_p (value))
    أرجع error_mark_node;

  /* First, detect a valid value with a complete type.  */
  𐤀𐤌 (COMPLETE_TYPE_P (type))
    أرجع value;

  c_incomplete_type_error (loc, value, type);
  أرجع error_mark_node;
}

/* Print an error message for invalid use of an incomplete type.
   VALUE is the expression that was used (or 0 if that isn't known)
   and TYPE is the type that was invalid.  LOC is the location for
   the error.  */

فراغ
c_incomplete_type_error (location_t loc, const_tree value, const_tree type)
{
  /* Avoid duplicate error message.  */
  𐤀𐤌 (TREE_CODE (type) == ERROR_MARK)
    أرجع;

  𐤀𐤌 (value != NULL_TREE && (VAR_P (value) || TREE_CODE (value) == PARM_DECL))
    error_at (loc, "%qD has an incomplete type %qT", value, type);
  وإلا
    {
    retry:
      /* We must print an error message.  Be clever about what it says.  */

      بدل (TREE_CODE (type))
	{
	حالة RECORD_TYPE:
	حالة UNION_TYPE:
	حالة ENUMERAL_TYPE:
	  اكسر;

	حالة VOID_TYPE:
	  error_at (loc, "invalid use of void expression");
	  أرجع;

	حالة ARRAY_TYPE:
	  𐤀𐤌 (TYPE_DOMAIN (type))
	    {
	      𐤀𐤌 (flexible_array_member_type_p (type))
		{
		  error_at (loc, "invalid use of flexible array member");
		  أرجع;
		}
	      type = TREE_TYPE (type);
	      اذهب retry;
	    }
	  error_at (loc, "invalid use of array with unspecified bounds");
	  أرجع;

	افتراضي:
	  gcc_unreachable ();
	}

      𐤀𐤌 (TREE_CODE (TYPE_NAME (type)) == IDENTIFIER_NODE)
	error_at (loc, "invalid use of undefined type %qT", type);
      وإلا
	/* If this type has a typedef-name, the TYPE_NAME is a TYPE_DECL.  */
	error_at (loc, "invalid use of incomplete typedef %qT", type);
    }
}

/* Given a type, apply default promotions wrt unnamed function
   arguments and return the new type.  */

tree
c_type_promotes_to (tree type)
{
  tree ret = NULL_TREE;

  𐤀𐤌 (TYPE_MAIN_VARIANT (type) == float_type_node)
    ret = double_type_node;
  وإلا 𐤀𐤌 (c_promoting_integer_type_p (type))
    {
      /* Preserve unsignedness if not really getting any wider.  */
      𐤀𐤌 (TYPE_UNSIGNED (type)
	  && (TYPE_PRECISION (type) == TYPE_PRECISION (integer_type_node)))
	ret = unsigned_type_node;
      وإلا
	ret = integer_type_node;
    }

  𐤀𐤌 (ret != NULL_TREE)
    أرجع (TYPE_ATOMIC (type)
	    ? c_build_qualified_type (ret, TYPE_QUAL_ATOMIC)
	    : ret);

  أرجع type;
}

/* Return true if between two named address spaces, whether there is a superset
   named address space that encompasses both address spaces.  If there is a
   superset, return which address space is the superset.  */

ساكن منطقي
addr_space_superset (addr_space_t as1, addr_space_t as2, addr_space_t *common)
{
  𐤀𐤌 (as1 == as2)
    {
      *common = as1;
      أرجع true;
    }
  وإلا 𐤀𐤌 (targetm.addr_space.subset_p (as1, as2))
    {
      *common = as2;
      أرجع true;
    }
  وإلا 𐤀𐤌 (targetm.addr_space.subset_p (as2, as1))
    {
      *common = as1;
      أرجع true;
    }
  وإلا
    أرجع خطأ;
}

/* Return a variant of TYPE which has all the type qualifiers of LIKE
   as well as those of TYPE.  */

ساكن tree
qualify_type (tree type, tree like)
{
  addr_space_t as_type = TYPE_ADDR_SPACE (type);
  addr_space_t as_like = TYPE_ADDR_SPACE (like);
  addr_space_t as_common;

  /* If the two named address spaces are different, determine the common
     superset address space.  If there isn't one, raise an error.  */
  𐤀𐤌 (!addr_space_superset (as_type, as_like, &as_common))
    {
      as_common = as_type;
      error ("%qT and %qT are in disjoint named address spaces",
	     type, like);
    }

  أرجع c_build_qualified_type (type,
				 TYPE_QUALS_NO_ADDR_SPACE (type)
				 | TYPE_QUALS_NO_ADDR_SPACE_NO_ATOMIC (like)
				 | ENCODE_QUAL_ADDR_SPACE (as_common));
}


/* Check consistency of type TYPE.  For derived types, we test that
   C_TYPE_VARIABLE_SIZE and C_TYPE_VARIABLY_MODIFIED are consistent with
   the requirements of the base type.  We also check that arrays with a
   non-constant length are marked with C_TYPE_VARIABLE_SIZE. If any
   inconsistency is detected false is returned and true otherwise.  */

ساكن منطقي
c_verify_type (tree type)
{
  بدل (TREE_CODE (type))
    {
    حالة POINTER_TYPE:
    حالة FUNCTION_TYPE:
    حالة ARRAY_TYPE:
      /* Pointer, array, functions are variably modified if and only if the
	 target, element, return type is variably modified.  */
      𐤀𐤌 (!TYPE_STRUCTURAL_EQUALITY_P (type)
	  && (C_TYPE_VARIABLY_MODIFIED (type)
	      != C_TYPE_VARIABLY_MODIFIED (TREE_TYPE (type))))
	أرجع خطأ;
      /* If the target type is structural equality, the type should also. */
      𐤀𐤌 (!TYPE_STRUCTURAL_EQUALITY_P (type)
	  && TYPE_STRUCTURAL_EQUALITY_P (TREE_TYPE (type)))
	أرجع خطأ;
    افتراضي:
       اكسر;
    }

  بدل (TREE_CODE (type))
    {
    حالة POINTER_TYPE:
    حالة FUNCTION_TYPE:
      /* Pointer and functions can not have variable size.  */
      𐤀𐤌 (C_TYPE_VARIABLE_SIZE (type))
	أرجع خطأ;
      اكسر;
    حالة ARRAY_TYPE:
      /* An array has variable size if and only if it has a non-constant
	 dimensions or its element type has variable size.  */
      𐤀𐤌 ((C_TYPE_VARIABLE_SIZE (TREE_TYPE (type))
	   || top_array_vla_p (type))
	  != C_TYPE_VARIABLE_SIZE (type))
	أرجع خطأ;
      /* If the element type or the array has variable size, then the
	 array has variable size and is variably modified.  */
      𐤀𐤌 (C_TYPE_VARIABLE_SIZE (TREE_TYPE (type))
	  || C_TYPE_VARIABLE_SIZE (type))
	{
	  𐤀𐤌 (!C_TYPE_VARIABLE_SIZE (type))
	    أرجع خطأ;
	  𐤀𐤌 (!C_TYPE_VARIABLY_MODIFIED (type))
	    أرجع خطأ;
	}

      /* va_list violates this, accept such types here.  */
      𐤀𐤌 (!COMPLETE_TYPE_P (TREE_TYPE (type)))
	أرجع true;

      𐤀𐤌 (COMPLETE_TYPE_P (type))
	{
	  /* If the size is unknown, it can not be complete.  */
	  𐤀𐤌 (NULL_TREE == TYPE_DOMAIN (type))
	    أرجع خطأ;

	  /* Zero-length arrays must have size zero.  */
	  𐤀𐤌 (zero_length_array_type_p (type)
	      && !integer_zerop (TYPE_SIZE (type)))
	    أرجع خطأ;
	}
      وإلا
	{
	  /* If not complete but has a domain, it must be a FAM.  */
	  𐤀𐤌 (NULL_TREE != TYPE_DOMAIN (type)
	      && !flexible_array_member_type_p (type))
	    أرجع خطأ;
	}
    افتراضي:
      اكسر;
    }
  أرجع true;
}

/* Propagate C_TYPE_VARIABLY_MODIFIED and C_TYPE_VARIABLE_SIZE
   from a base type to a newly built derived or qualified type.  */

ساكن tree
c_set_type_bits (tree new_type, tree old_type)
{
  gcc_checking_assert (c_verify_type (old_type));

  𐤀𐤌 (c_type_variably_modified_p (old_type))
    C_TYPE_VARIABLY_MODIFIED (new_type) = true;

  𐤀𐤌 (TREE_CODE (new_type) == ARRAY_TYPE && C_TYPE_VARIABLE_SIZE (old_type))
    {
      C_TYPE_VARIABLY_MODIFIED (new_type) = true;
      C_TYPE_VARIABLE_SIZE (new_type) = true;
    }
  أرجع new_type;
}

/* Build a pointer type using the default pointer mode.  */

tree
c_build_pointer_type (tree to_type)
{
  addr_space_t as = to_type == error_mark_node ? ADDR_SPACE_GENERIC
					       : TYPE_ADDR_SPACE (to_type);
  machine_mode pointer_mode;

  𐤀𐤌 (as != ADDR_SPACE_GENERIC || c_default_pointer_mode == VOIDmode)
    pointer_mode = targetm.addr_space.pointer_mode (as);
  وإلا
    pointer_mode = c_default_pointer_mode;

  أرجع c_build_pointer_type_for_mode (to_type, pointer_mode, خطأ);
}

/* Build a pointer type using the given mode.  */

tree
c_build_pointer_type_for_mode (tree type, machine_mode mode, منطقي m)
{
  tree ret = build_pointer_type_for_mode (type, mode, m);
  أرجع c_set_type_bits (ret, type);
}

/* Build a function type.  */

tree
c_build_function_type (tree type, tree args, منطقي no)
{
  tree ret = build_function_type (type, args, no);
  أرجع c_set_type_bits (ret, type);
}

/* Build an array type.  This sets typeless storage as required
   by C2Y and C_TYPE_VARIABLY_MODIFIED and C_TYPE_VARIABLE_SIZE
   based on the element type and domain.  */

tree
c_build_array_type (tree type, tree domain)
{
  صحيح type_quals = TYPE_QUALS (type);

  /* Identify typeless storage as introduced in C2Y
     and supported also in earlier language modes.  */
  منطقي typeless = (char_type_p (type) && !(type_quals & TYPE_QUAL_ATOMIC))
		  || (AGGREGATE_TYPE_P (type) && TYPE_TYPELESS_STORAGE (type));

  tree ret = build_array_type (type, domain, typeless);

  𐤀𐤌 (top_array_vla_p (ret))
    {
      C_TYPE_VARIABLE_SIZE (ret) = 1;
      C_TYPE_VARIABLY_MODIFIED (ret) = 1;
    }

  أرجع c_set_type_bits (ret, type);
}

/* Build an array type of unspecified size.  */
tree
c_build_array_type_unspecified (tree type)
{
  tree upper = build2 (COMPOUND_EXPR, TREE_TYPE (size_zero_node),
		       integer_zero_node, size_zero_node);
  أرجع c_build_array_type (type, build_index_type (upper));
}

/* Build an array type of zero size.  */
tree
c_build_array_type_zero_size (tree type)
{
  /* The GCC extension for zero-length arrays differs from
     ISO flexible array members in that sizeof yields
     zero.  */
  type = c_build_array_type (type, build_index_type (NULL_TREE));
  type = build_distinct_type_copy (TYPE_MAIN_VARIANT (type));
  TYPE_SIZE (type) = bitsize_zero_node;
  TYPE_SIZE_UNIT (type) = size_zero_node;
  SET_TYPE_STRUCTURAL_EQUALITY (type);
  أرجع type;
}

tree
c_build_type_attribute_qual_variant (tree type, tree attrs, صحيح quals)
{
  tree ret = build_type_attribute_qual_variant (type, attrs, quals);
  أرجع c_set_type_bits (ret, type);
}

tree
c_build_type_attribute_variant (tree type, tree attrs)
{
  أرجع c_build_type_attribute_qual_variant (type, attrs, TYPE_QUALS (type));
}

/* Reconstruct a complex derived type.  This is used to re-construct types
   with the vector attribute.  It is called via a langhook.  */

tree
c_reconstruct_complex_type (tree type, tree bottom)
{
  tree inner, outer;

  𐤀𐤌 (TREE_CODE (type) == POINTER_TYPE)
    {
      inner = c_reconstruct_complex_type (TREE_TYPE (type), bottom);
      outer = c_build_pointer_type_for_mode (inner, TYPE_MODE (type),
					     TYPE_REF_CAN_ALIAS_ALL (type));
    }
  وإلا 𐤀𐤌 (TREE_CODE (type) == ARRAY_TYPE)
    {
      منطقي rso = TYPE_REVERSE_STORAGE_ORDER (type);
      inner = c_reconstruct_complex_type (TREE_TYPE (type), bottom);
      outer = c_build_array_type (inner, TYPE_DOMAIN (type));
      𐤀𐤌 (rso)
	{
	  outer = build_distinct_type_copy (outer);
	  TYPE_REVERSE_STORAGE_ORDER (outer) = 1;
	}

      gcc_checking_assert (C_TYPE_VARIABLE_SIZE (type)
			   == C_TYPE_VARIABLE_SIZE (outer));
    }
  وإلا 𐤀𐤌 (TREE_CODE (type) == FUNCTION_TYPE)
    {
      inner = c_reconstruct_complex_type (TREE_TYPE (type), bottom);
      outer = c_build_function_type (inner, TYPE_ARG_TYPES (type),
				     TYPE_NO_NAMED_ARGS_STDARG_P (type));
    }
  وإلا 𐤀𐤌 (TREE_CODE (type) == REFERENCE_TYPE
	   || TREE_CODE (type) == OFFSET_TYPE)
    gcc_unreachable ();
  وإلا
    أرجع bottom;

  أرجع c_build_type_attribute_qual_variant (outer, TYPE_ATTRIBUTES (type),
					      TYPE_QUALS (type));
}


/* Helper function for c_canonical_type.  Check whether FIELD
   contains a pointer to a structure or union with tag,
   possibly nested in other type derivations, and return the
   type of this nested structure or union.  */
ساكن tree
ptr_to_tagged_member (tree field)
{
  gcc_assert (FIELD_DECL == TREE_CODE (field));
  tree type = TREE_TYPE (field);
  منطقي ptr_seen = خطأ;
  طالما (TREE_CODE (type) == ARRAY_TYPE
	 || TREE_CODE (type) == FUNCTION_TYPE
	 || TREE_CODE (type) == POINTER_TYPE)
    {
      𐤀𐤌 (TREE_CODE (type) == POINTER_TYPE)
	ptr_seen = true;
      type = TREE_TYPE (type);
    }

  𐤀𐤌 (ptr_seen
      && RECORD_OR_UNION_TYPE_P (type)
      && NULL_TREE != c_type_tag (type))
    أرجع type;

  أرجع NULL_TREE;
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
tree
c_type_canonical (tree type)
{
  gcc_assert (RECORD_OR_UNION_TYPE_P (type));

  منطقي needs_mod = خطأ;
  لكل (tree x = TYPE_FIELDS (type); x; x = DECL_CHAIN (x))
    {
      𐤀𐤌 (!ptr_to_tagged_member (x))
	استمر;
      needs_mod = true;
      اكسر;
    }
  𐤀𐤌 (!needs_mod)
    أرجع type;

  /* Construct new version with such members replaced.  */
  tree n = build_distinct_type_copy (type);
  tree *fields = &TYPE_FIELDS (n);
  لكل (tree x = TYPE_FIELDS (type); x; x = DECL_CHAIN (x))
    {
      tree f = copy_node (x);
      𐤀𐤌 (tree m = ptr_to_tagged_member (x))
	{
	  tree new_node = make_node (TREE_CODE (m));
	  TYPE_NAME (new_node) = TYPE_NAME (m);
	  SET_TYPE_STRUCTURAL_EQUALITY (new_node);
	  new_node = qualify_type (new_node, m);
	  TREE_TYPE (f) = c_reconstruct_complex_type (TREE_TYPE (x),
						      new_node);
	}
      *fields = f;
      fields = &DECL_CHAIN (f);
    }
  TYPE_CANONICAL (n) = n;
  أرجع n;
}


/* If NTYPE is a type of a non-variadic function with a prototype
   and OTYPE is a type of a function without a prototype and ATTRS
   contains attribute format, diagnosess and removes it from ATTRS.
   Returns the result of build_type_attribute_variant of NTYPE and
   the (possibly) modified ATTRS.  */

ساكن tree
c_build_functype_attribute_variant (tree ntype, tree otype, tree attrs)
{
  𐤀𐤌 (!prototype_p (otype)
      && prototype_p (ntype)
      && lookup_attribute ("format", attrs))
    {
      warning_at (input_location, OPT_Wattributes,
		  "%qs attribute can only be applied to variadic functions",
		  "format");
      attrs = remove_attribute ("format", attrs);
    }
  أرجع c_build_type_attribute_variant (ntype, attrs);

}

/* Given a type which could be a typedef name, make sure to return the
   original type.  See set_underlying_type. */
ساكن const_tree
c_type_original (const_tree t)
{
  /* It may even be a typedef of a typedef...
     In the case of compiler-created builtin structs the TYPE_DECL
     may be a dummy, with no DECL_ORIGINAL_TYPE.  Don't fault.  */
  طالما (TYPE_NAME (t)
	 && TREE_CODE (TYPE_NAME (t)) == TYPE_DECL
	 && DECL_ORIGINAL_TYPE (TYPE_NAME (t)))
    t = DECL_ORIGINAL_TYPE (TYPE_NAME (t));
  أرجع t;
}

/* Return the tag for a tagged type.  */
tree
c_type_tag (const_tree t)
{
  gcc_assert (RECORD_OR_UNION_TYPE_P (t) || TREE_CODE (t) == ENUMERAL_TYPE);
  const_tree orig = c_type_original (t);
  tree name = TYPE_NAME (orig);
  𐤀𐤌 (!name)
    أرجع NULL_TREE;
  𐤀𐤌 (TREE_CODE (name) == TYPE_DECL)
    {
      𐤀𐤌 (!DECL_NAME (name))
	أرجع NULL_TREE;
      name = DECL_NAME (name);
    }
  gcc_checking_assert (TREE_CODE (name) == IDENTIFIER_NODE);
  أرجع name;
}

/* Remove qualifiers but not atomic.  For arrays remove qualifiers
   on the element type but also do not remove atomic.  */
ساكن tree
remove_qualifiers (tree t)
{
  𐤀𐤌 (!t || t == error_mark_node)
    أرجع t;
  أرجع TYPE_ATOMIC (strip_array_types (t))
	 ? c_build_qualified_type (TYPE_MAIN_VARIANT (t), TYPE_QUAL_ATOMIC)
	 : TYPE_MAIN_VARIANT (t);
}


/* Helper function for composite_type_internal.  Find a compatible type
   in a (transparent) union U compatible to T.  If found, return the
   type of the corresponding member.  Otherwise, return the union type U.  */
ساكن tree
transparent_union_replacement (tree u, tree t)
{
  𐤀𐤌 (u == error_mark_node || t == error_mark_node
      || TREE_CODE (u) != UNION_TYPE
      || !(TYPE_TRANSPARENT_AGGR (u) || TYPE_NAME (u) == NULL_TREE)
      || comptypes (u, t))
    أرجع u;

  لكل (tree memb = TYPE_FIELDS (u); memb; memb = DECL_CHAIN (memb))
    {
      tree m = remove_qualifiers (TREE_TYPE (memb));
      𐤀𐤌 (comptypes (m, t))
	{
	  pedwarn (input_location, OPT_Wpedantic,
		    "function types not truly compatible in ISO C");
	  أرجع m;
	}
    }

  أرجع u;
}



/* Return the composite type of two compatible types.

   We assume that comptypes has already been done and returned
   nonzero; if that isn't so, this may crash.  In particular, we
   assume that qualifiers match.  */

بنية composite_cache {
  tree t1;
  tree t2;
  tree composite;
  بنية composite_cache* next;
};

tree
composite_type_internal (tree t1, tree t2, tree cond,
			 بنية composite_cache* cache)
{
  تعداد tree_code code1;
  تعداد tree_code code2;
  tree attributes;

  /* Save time if the two types are the same.  */

  𐤀𐤌 (t1 == t2) أرجع t1;

  /* If one type is nonsense, use the other.  */
  𐤀𐤌 (t1 == error_mark_node)
    أرجع t2;
  𐤀𐤌 (t2 == error_mark_node)
    أرجع t1;

  code1 = TREE_CODE (t1);
  code2 = TREE_CODE (t2);

  /* Merge the attributes.  */
  attributes = targetm.merge_type_attributes (t1, t2);

  /* If one is an enumerated type and the other is the compatible
     integer type, the composite type might be either of the two
     (DR#013 question 3).  For consistency, use the enumerated type as
     the composite type.  */

  𐤀𐤌 (code1 == ENUMERAL_TYPE
      && (code2 == INTEGER_TYPE
	  || code2 == BOOLEAN_TYPE))
    أرجع t1;
  𐤀𐤌 (code2 == ENUMERAL_TYPE
      && (code1 == INTEGER_TYPE
	  || code1 == BOOLEAN_TYPE))
    أرجع t2;

  gcc_assert (code1 == code2);

  بدل (code1)
    {
    حالة POINTER_TYPE:
      /* For two pointers, do this recursively on the target type.  */
      {
	gcc_checking_assert (TYPE_QUALS (t1) == TYPE_QUALS (t2));
	tree target = composite_type_internal (TREE_TYPE (t1), TREE_TYPE (t2),
					       cond, cache);
	tree n = c_build_pointer_type_for_mode (target, TYPE_MODE (t1), خطأ);
	أرجع c_build_type_attribute_qual_variant (n, attributes,
						    TYPE_QUALS (t2));
      }

    حالة ARRAY_TYPE:
      {
	tree d1 = TYPE_DOMAIN (t1);
	tree d2 = TYPE_DOMAIN (t2);

	/* We should not have any type quals on arrays at all.  */
	gcc_assert (!TYPE_QUALS_NO_ADDR_SPACE (t1)
		    && !TYPE_QUALS_NO_ADDR_SPACE (t2));

	منطقي d1_zero = zero_length_array_type_p (t1)
		       || flexible_array_member_type_p (t1);
	منطقي d2_zero = zero_length_array_type_p (t2)
		       || flexible_array_member_type_p (t2);

	منطقي d1_variable = top_array_vla_p (t1);
	منطقي d2_variable = top_array_vla_p (t2);

	منطقي use1 = d1 && (d2_variable || !d2 || d2_zero || !d1_variable);
	منطقي use2 = d2 && (d1_variable || !d1 || d1_zero || !d2_variable);

	/* If the first is an unspecified size pick the other one.  */
	𐤀𐤌 (d2_variable && c_type_unspecified_p (t1))
	  {
	    gcc_assert (use1 && use2);
	    use1 = خطأ;
	  }

	/* If both are VLAs but not unspecified and we are in the
	   conditional operator, we create a conditional to select
	   the size of the active branch.  */
	منطقي use0 = cond && d1_variable && !c_type_unspecified_p (t1)
			 && d2_variable && !c_type_unspecified_p (t2);

	tree td;
	tree elt = composite_type_internal (TREE_TYPE (t1), TREE_TYPE (t2),
					    cond, cache);

	𐤀𐤌 (!use0)
	  {
	    /* Save space: see if the result is identical to one of the args.  */
	    𐤀𐤌 (elt == TREE_TYPE (t1) && use1)
	      أرجع c_build_type_attribute_variant (t1, attributes);
	    𐤀𐤌 (elt == TREE_TYPE (t2) && use2)
	      أرجع c_build_type_attribute_variant (t2, attributes);

	    𐤀𐤌 (elt == TREE_TYPE (t1) && !TYPE_DOMAIN (t2) && !TYPE_DOMAIN (t1))
	      أرجع c_build_type_attribute_variant (t1, attributes);
	    𐤀𐤌 (elt == TREE_TYPE (t2) && !TYPE_DOMAIN (t2) && !TYPE_DOMAIN (t1))
	      أرجع c_build_type_attribute_variant (t2, attributes);

	    td = TYPE_DOMAIN (use1 ? t1 : t2);
	  }
	وإلا
	  {
	    /* Not used in C.  */
	    gcc_assert (size_zero_node == TYPE_MIN_VALUE (d1));
	    gcc_assert (size_zero_node == TYPE_MIN_VALUE (d2));

	    tree d = fold_build3_loc (UNKNOWN_LOCATION, COND_EXPR, sizetype,
				      cond, TYPE_MAX_VALUE (d1),
				      TYPE_MAX_VALUE (d2));

	    td = build_index_type (d);
	  }

	/* Merge the element types, and have a size if either arg has
	   one.  We may have qualifiers on the element types.  To set
	   up TYPE_MAIN_VARIANT correctly, we need to form the
	   composite of the unqualified types and add the qualifiers
	   back at the end.  */
	صحيح quals = TYPE_QUALS (strip_array_types (elt));
	tree unqual_elt = c_build_qualified_type (elt, TYPE_UNQUALIFIED);

	𐤀𐤌 ((!d1 || d1_zero) && (!d2 || d2_zero) && (d1 || d2))
	  t1 = c_build_array_type_zero_size (unqual_elt);
	وإلا
	  t1 = c_build_array_type (unqual_elt, td);

	/* Check that a type which has a varying outermost dimension
	   got marked as having a variable size.  */
	منطقي varsize = (d1_variable && d2_variable)
		       || (d1_variable && !d2)
		       || (d2_variable && !d1);
	gcc_checking_assert (!varsize || C_TYPE_VARIABLE_SIZE (t1));

	t1 = c_build_qualified_type (t1, quals);
	أرجع c_build_type_attribute_variant (t1, attributes);
      }

    حالة RECORD_TYPE:
    حالة UNION_TYPE:
      𐤀𐤌 (flag_isoc23 && !comptypes_same_p (t1, t2))
	{
	  /* Go to the original type to get the right tag.  */
	  tree tag = c_type_tag (t1);

	  gcc_checking_assert (COMPLETE_TYPE_P (t1) && COMPLETE_TYPE_P (t2));
	  gcc_checking_assert (!tag || comptypes (t1, t2));

	  /* If a composite type for these two types is already under
	     construction, return it.  */

	  لكل (بنية composite_cache *c = cache; c != عدم; c = c->next)
	    𐤀𐤌 ((c->t1 == t1 && c->t2 == t2) || (c->t1 == t2 && c->t2 == t1))
	       أرجع c->composite;

	  /* Otherwise, create a new type node and link it into the cache.  */

	  tree n = make_node (code1);
	  SET_TYPE_STRUCTURAL_EQUALITY (n);
	  TYPE_NAME (n) = tag;

	  بنية composite_cache cache2 = { t1, t2, n, cache };
	  cache = &cache2;

	  tree f1 = TYPE_FIELDS (t1);
	  tree f2 = TYPE_FIELDS (t2);
	  tree fields = NULL_TREE;

	  لكل (tree a = f1, b = f2; a && b;
	       a = DECL_CHAIN (a), b = DECL_CHAIN (b))
	    {
	      tree ta = TREE_TYPE (a);
	      tree tb = TREE_TYPE (b);

	      𐤀𐤌 (DECL_C_BIT_FIELD (a))
		{
		  ta = DECL_BIT_FIELD_TYPE (a);
		  tb = DECL_BIT_FIELD_TYPE (b);
		}

	      gcc_assert (DECL_NAME (a) == DECL_NAME (b));
	      gcc_checking_assert (!DECL_NAME (a) || comptypes (ta, tb));

	      tree t = composite_type_internal (ta, tb, cond, cache);
	      tree f = build_decl (input_location, FIELD_DECL, DECL_NAME (a), t);

	      DECL_PACKED (f) = DECL_PACKED (a);
	      SET_DECL_ALIGN (f, DECL_ALIGN (a));
	      DECL_ATTRIBUTES (f) = DECL_ATTRIBUTES (a);
	      C_DECL_VARIABLE_SIZE (f) = C_TYPE_VARIABLE_SIZE (t);

	      decl_attributes (&f, DECL_ATTRIBUTES (f), 0);

	      finish_decl (f, input_location, عدم, عدم, عدم);

	      𐤀𐤌 (DECL_C_BIT_FIELD (a))
		{
		  /* This will be processed by finish_struct.  */
		  SET_DECL_C_BIT_FIELD (f);
		  DECL_INITIAL (f) = build_int_cst (integer_type_node,
						    tree_to_uhwi (DECL_SIZE (a)));
		  DECL_NONADDRESSABLE_P (f) = true;
		  DECL_PADDING_P (f) = !DECL_NAME (a);
		}

	      DECL_CHAIN (f) = fields;
	      fields = f;
	    }

	  fields = nreverse (fields);

	  /* Setup the struct/union type.  Because we inherit all variably
	     modified components, we can ignore the size expression.  */
	  tree expr = NULL_TREE;

	  /* Set TYPE_STUB_DECL for debugging symbols.  */
	  TYPE_STUB_DECL (n) = pushdecl (build_decl (input_location, TYPE_DECL,
						     NULL_TREE, n));

	  n = finish_struct (input_location, n, fields, attributes, عدم,
			     &expr);

	  أرجع qualify_type (n, t1);
	}
      /* FALLTHRU */
    حالة ENUMERAL_TYPE:
      𐤀𐤌 (attributes != عدم)
	{
	  /* Try harder not to create a new aggregate type.  */
	  𐤀𐤌 (attribute_list_equal (TYPE_ATTRIBUTES (t1), attributes))
	    أرجع t1;
	  𐤀𐤌 (attribute_list_equal (TYPE_ATTRIBUTES (t2), attributes))
	    أرجع t2;
	}
      أرجع c_build_type_attribute_variant (t1, attributes);

    حالة FUNCTION_TYPE:
      /* Function types: prefer the one that specified arg types.
	 If both do, merge the arg types.  Also merge the return types.  */
      {
	tree valtype = composite_type_internal (TREE_TYPE (t1), TREE_TYPE (t2),
						cond, cache);
	tree p1 = TYPE_ARG_TYPES (t1);
	tree p2 = TYPE_ARG_TYPES (t2);

	/* Save space: see if the result is identical to one of the args.  */
	𐤀𐤌 (valtype == TREE_TYPE (t1) && !TYPE_ARG_TYPES (t2))
	  أرجع c_build_functype_attribute_variant (t1, t2, attributes);
	𐤀𐤌 (valtype == TREE_TYPE (t2) && !TYPE_ARG_TYPES (t1))
	  أرجع c_build_functype_attribute_variant (t2, t1, attributes);

	/* Simple way if one arg fails to specify argument types.  */
	𐤀𐤌 (TYPE_ARG_TYPES (t1) == NULL_TREE)
	  {
	    t1 = c_build_function_type (valtype, TYPE_ARG_TYPES (t2),
					TYPE_NO_NAMED_ARGS_STDARG_P (t2));
	    t1 = c_build_type_attribute_variant (t1, attributes);
	    أرجع qualify_type (t1, t2);
	 }
	𐤀𐤌 (TYPE_ARG_TYPES (t2) == NULL_TREE)
	  {
	    t1 = c_build_function_type (valtype, TYPE_ARG_TYPES (t1),
					TYPE_NO_NAMED_ARGS_STDARG_P (t1));
	    t1 = c_build_type_attribute_variant (t1, attributes);
	    أرجع qualify_type (t1, t2);
	  }

	/* If both args specify argument types, we must merge the two
	   lists, argument by argument.  */
	tree newargs = NULL_TREE;
	tree *endp = &newargs;

	لكل (; p1; p1 = TREE_CHAIN (p1), p2 = TREE_CHAIN (p2))
	  {
	    𐤀𐤌 (p1 == void_list_node)
	      {
		*endp = void_list_node;
		اكسر;
	      }
	    tree mv1 = remove_qualifiers (TREE_VALUE (p1));
	    tree mv2 = remove_qualifiers (TREE_VALUE (p2));

	    gcc_assert (mv1);
	    gcc_assert (mv2);

	    mv1 = transparent_union_replacement (mv1, mv2);
	    mv2 = transparent_union_replacement (mv2, mv1);

	    *endp = tree_cons (NULL_TREE,
			       composite_type_internal (mv1, mv2, cond, cache),
			       NULL_TREE);

	    endp = &TREE_CHAIN (*endp);
	  }

	t1 = c_build_function_type (valtype, newargs);
	t1 = qualify_type (t1, t2);
      }
      /* FALLTHRU */

    افتراضي:
      أرجع c_build_type_attribute_variant (t1, attributes);
    }
}

tree
composite_type_cond (tree t1, tree t2, tree cond)
{
  gcc_checking_assert (comptypes_check_for_composite (t1, t2));

  بنية composite_cache cache = { };
  tree n = composite_type_internal (t1, t2, cond, &cache);

  gcc_checking_assert (comptypes_check_for_composite (n, t1));
  gcc_checking_assert (comptypes_check_for_composite (n, t2));
  أرجع n;
}


tree
composite_type (tree t1, tree t2)
{
  أرجع composite_type_cond (t1, t2, NULL_TREE);
}

/* Return the type of a conditional expression between pointers to
   possibly differently qualified versions of compatible types.

   We assume that comp_target_types has already been done and returned
   true; if that isn't so, this may crash.  */

ساكن tree
common_pointer_type (tree t1, tree t2, tree cond)
{
  tree attributes;
  unsigned target_quals;
  addr_space_t as1, as2, as_common;
  صحيح quals1, quals2;

  /* Save time if the two types are the same.  */

  𐤀𐤌 (t1 == t2) أرجع t1;

  /* If one type is nonsense, use the other.  */
  𐤀𐤌 (t1 == error_mark_node)
    أرجع t2;
  𐤀𐤌 (t2 == error_mark_node)
    أرجع t1;

  gcc_assert (TREE_CODE (t1) == POINTER_TYPE
	      && TREE_CODE (t2) == POINTER_TYPE);

  /* Merge the attributes.  */
  attributes = targetm.merge_type_attributes (t1, t2);

  /* Find the composite type of the target types, and combine the
     qualifiers of the two types' targets.  */
  tree pointed_to_1 = TREE_TYPE (t1);
  tree pointed_to_2 = TREE_TYPE (t2);
  tree target = composite_type_cond (TYPE_MAIN_VARIANT (pointed_to_1),
				     TYPE_MAIN_VARIANT (pointed_to_2), cond);

  /* Strip array types to get correct qualifier for pointers to arrays */
  quals1 = TYPE_QUALS_NO_ADDR_SPACE (strip_array_types (pointed_to_1));
  quals2 = TYPE_QUALS_NO_ADDR_SPACE (strip_array_types (pointed_to_2));

  /* For function types do not merge const qualifiers, but drop them
     if used inconsistently.  The middle-end uses these to mark const
     and noreturn functions.  */
  𐤀𐤌 (TREE_CODE (pointed_to_1) == FUNCTION_TYPE)
    target_quals = (quals1 & quals2);
  وإلا
    target_quals = (quals1 | quals2);

  /* If the two named address spaces are different, determine the common
     superset address space.  This is guaranteed to exist due to the
     assumption that comp_target_type returned true.  */
  as1 = TYPE_ADDR_SPACE (pointed_to_1);
  as2 = TYPE_ADDR_SPACE (pointed_to_2);
  𐤀𐤌 (!addr_space_superset (as1, as2, &as_common))
    gcc_unreachable ();

  target_quals |= ENCODE_QUAL_ADDR_SPACE (as_common);

  t1 = c_build_pointer_type (c_build_qualified_type (target, target_quals));
  أرجع c_build_type_attribute_variant (t1, attributes);
}

/* Return the common type for two arithmetic types under the usual
   arithmetic conversions.  The default conversions have already been
   applied, and enumerated types converted to their compatible integer
   types.  The resulting type is unqualified and has no attributes.

   This is the type for the result of most arithmetic operations
   if the operands have the given two types.  */

ساكن tree
c_common_type (tree t1, tree t2)
{
  تعداد tree_code code1;
  تعداد tree_code code2;

  /* If one type is nonsense, use the other.  */
  𐤀𐤌 (t1 == error_mark_node)
    أرجع t2;
  𐤀𐤌 (t2 == error_mark_node)
    أرجع t1;

  𐤀𐤌 (TYPE_QUALS (t1) != TYPE_UNQUALIFIED)
    t1 = TYPE_MAIN_VARIANT (t1);

  𐤀𐤌 (TYPE_QUALS (t2) != TYPE_UNQUALIFIED)
    t2 = TYPE_MAIN_VARIANT (t2);

  𐤀𐤌 (TYPE_ATTRIBUTES (t1) != NULL_TREE)
    {
      tree attrs = affects_type_identity_attributes (TYPE_ATTRIBUTES (t1));
      t1 = c_build_type_attribute_variant (t1, attrs);
    }

  𐤀𐤌 (TYPE_ATTRIBUTES (t2) != NULL_TREE)
    {
      tree attrs = affects_type_identity_attributes (TYPE_ATTRIBUTES (t2));
      t2 = c_build_type_attribute_variant (t2, attrs);
    }

  /* Save time if the two types are the same.  */

  𐤀𐤌 (t1 == t2) أرجع t1;

  code1 = TREE_CODE (t1);
  code2 = TREE_CODE (t2);

  gcc_assert (code1 == VECTOR_TYPE || code1 == COMPLEX_TYPE
	      || code1 == FIXED_POINT_TYPE || code1 == REAL_TYPE
	      || code1 == INTEGER_TYPE || code1 == BITINT_TYPE);
  gcc_assert (code2 == VECTOR_TYPE || code2 == COMPLEX_TYPE
	      || code2 == FIXED_POINT_TYPE || code2 == REAL_TYPE
	      || code2 == INTEGER_TYPE || code2 == BITINT_TYPE);

  /* When one operand is a decimal float type, the other operand cannot be
     a generic float type or a complex type.  We also disallow vector types
     here.  */
  𐤀𐤌 ((DECIMAL_FLOAT_TYPE_P (t1) || DECIMAL_FLOAT_TYPE_P (t2))
      && !(DECIMAL_FLOAT_TYPE_P (t1) && DECIMAL_FLOAT_TYPE_P (t2)))
    {
      𐤀𐤌 (code1 == VECTOR_TYPE || code2 == VECTOR_TYPE)
	{
	  error ("cannot mix operands of decimal floating and vector types");
	  أرجع error_mark_node;
	}
      𐤀𐤌 (code1 == COMPLEX_TYPE || code2 == COMPLEX_TYPE)
	{
	  error ("cannot mix operands of decimal floating and complex types");
	  أرجع error_mark_node;
	}
      𐤀𐤌 (code1 == REAL_TYPE && code2 == REAL_TYPE)
	{
	  error ("cannot mix operands of decimal floating "
		 "and other floating types");
	  أرجع error_mark_node;
	}
    }

  /* If one type is a vector type, return that type.  (How the usual
     arithmetic conversions apply to the vector types extension is not
     precisely specified.)  */
  𐤀𐤌 (code1 == VECTOR_TYPE)
    أرجع t1;

  𐤀𐤌 (code2 == VECTOR_TYPE)
    أرجع t2;

  /* If one type is complex, form the common type of the non-complex
     components, then make that complex.  Use T1 or T2 if it is the
     required type.  */
  𐤀𐤌 (code1 == COMPLEX_TYPE || code2 == COMPLEX_TYPE)
    {
      tree subtype1 = code1 == COMPLEX_TYPE ? TREE_TYPE (t1) : t1;
      tree subtype2 = code2 == COMPLEX_TYPE ? TREE_TYPE (t2) : t2;
      tree subtype = c_common_type (subtype1, subtype2);

      𐤀𐤌 (code1 == COMPLEX_TYPE && TREE_TYPE (t1) == subtype)
	أرجع t1;
      وإلا 𐤀𐤌 (code2 == COMPLEX_TYPE && TREE_TYPE (t2) == subtype)
	أرجع t2;
      وإلا 𐤀𐤌 (TREE_CODE (subtype) == BITINT_TYPE)
	{
	  sorry ("%<_Complex _BitInt(%d)%> unsupported",
		 TYPE_PRECISION (subtype));
	  أرجع code1 == COMPLEX_TYPE ? t1 : t2;
	}
      وإلا
	أرجع build_complex_type (subtype);
    }

  /* If only one is real, use it as the result.  */

  𐤀𐤌 (code1 == REAL_TYPE && code2 != REAL_TYPE)
    أرجع t1;

  𐤀𐤌 (code2 == REAL_TYPE && code1 != REAL_TYPE)
    أرجع t2;

  /* If both are real and either are decimal floating point types, use
     the decimal floating point type with the greater precision. */

  𐤀𐤌 (code1 == REAL_TYPE && code2 == REAL_TYPE)
    {
      𐤀𐤌 (TYPE_MAIN_VARIANT (t1) == dfloat128_type_node
	  || TYPE_MAIN_VARIANT (t2) == dfloat128_type_node)
	أرجع dfloat128_type_node;
      /* And prefer _Decimal128 over _Decimal64x which has in GCC's
	 implementation the same mode.  */
      وإلا 𐤀𐤌 (TYPE_MAIN_VARIANT (t1) == dfloat64x_type_node
	       || TYPE_MAIN_VARIANT (t2) == dfloat64x_type_node)
	أرجع dfloat64x_type_node;
      وإلا 𐤀𐤌 (TYPE_MAIN_VARIANT (t1) == dfloat64_type_node
	       || TYPE_MAIN_VARIANT (t2) == dfloat64_type_node)
	أرجع dfloat64_type_node;
      وإلا 𐤀𐤌 (TYPE_MAIN_VARIANT (t1) == dfloat32_type_node
	       || TYPE_MAIN_VARIANT (t2) == dfloat32_type_node)
	أرجع dfloat32_type_node;
    }

  /* Deal with fixed-point types.  */
  𐤀𐤌 (code1 == FIXED_POINT_TYPE || code2 == FIXED_POINT_TYPE)
    {
      unsigned صحيح unsignedp = 0, satp = 0;
      scalar_mode m1, m2;
      unsigned صحيح fbit1, ibit1, fbit2, ibit2, max_fbit, max_ibit;

      m1 = SCALAR_TYPE_MODE (t1);
      m2 = SCALAR_TYPE_MODE (t2);

      /* If one input type is saturating, the result type is saturating.  */
      𐤀𐤌 (TYPE_SATURATING (t1) || TYPE_SATURATING (t2))
	satp = 1;

      /* If both fixed-point types are unsigned, the result type is unsigned.
	 When mixing fixed-point and integer types, follow the sign of the
	 fixed-point type.
	 Otherwise, the result type is signed.  */
      𐤀𐤌 ((TYPE_UNSIGNED (t1) && TYPE_UNSIGNED (t2)
	   && code1 == FIXED_POINT_TYPE && code2 == FIXED_POINT_TYPE)
	  || (code1 == FIXED_POINT_TYPE && code2 != FIXED_POINT_TYPE
	      && TYPE_UNSIGNED (t1))
	  || (code1 != FIXED_POINT_TYPE && code2 == FIXED_POINT_TYPE
	      && TYPE_UNSIGNED (t2)))
	unsignedp = 1;

      /* The result type is signed.  */
      𐤀𐤌 (unsignedp == 0)
	{
	  /* If the input type is unsigned, we need to convert to the
	     signed type.  */
	  𐤀𐤌 (code1 == FIXED_POINT_TYPE && TYPE_UNSIGNED (t1))
	    {
	      تعداد mode_class mclass = (تعداد mode_class) 0;
	      𐤀𐤌 (GET_MODE_CLASS (m1) == MODE_UFRACT)
		mclass = MODE_FRACT;
	      وإلا 𐤀𐤌 (GET_MODE_CLASS (m1) == MODE_UACCUM)
		mclass = MODE_ACCUM;
	      وإلا
		gcc_unreachable ();
	      m1 = as_a <scalar_mode>
		(mode_for_size (GET_MODE_PRECISION (m1), mclass, 0));
	    }
	  𐤀𐤌 (code2 == FIXED_POINT_TYPE && TYPE_UNSIGNED (t2))
	    {
	      تعداد mode_class mclass = (تعداد mode_class) 0;
	      𐤀𐤌 (GET_MODE_CLASS (m2) == MODE_UFRACT)
		mclass = MODE_FRACT;
	      وإلا 𐤀𐤌 (GET_MODE_CLASS (m2) == MODE_UACCUM)
		mclass = MODE_ACCUM;
	      وإلا
		gcc_unreachable ();
	      m2 = as_a <scalar_mode>
		(mode_for_size (GET_MODE_PRECISION (m2), mclass, 0));
	    }
	}

      𐤀𐤌 (code1 == FIXED_POINT_TYPE)
	{
	  fbit1 = GET_MODE_FBIT (m1);
	  ibit1 = GET_MODE_IBIT (m1);
	}
      وإلا
	{
	  fbit1 = 0;
	  /* Signed integers need to subtract one sign bit.  */
	  ibit1 = TYPE_PRECISION (t1) - (!TYPE_UNSIGNED (t1));
	}

      𐤀𐤌 (code2 == FIXED_POINT_TYPE)
	{
	  fbit2 = GET_MODE_FBIT (m2);
	  ibit2 = GET_MODE_IBIT (m2);
	}
      وإلا
	{
	  fbit2 = 0;
	  /* Signed integers need to subtract one sign bit.  */
	  ibit2 = TYPE_PRECISION (t2) - (!TYPE_UNSIGNED (t2));
	}

      max_ibit = ibit1 >= ibit2 ?  ibit1 : ibit2;
      max_fbit = fbit1 >= fbit2 ?  fbit1 : fbit2;
      أرجع c_common_fixed_point_type_for_size (max_ibit, max_fbit, unsignedp,
						 satp);
    }

  /* Both real or both integers; use the one with greater precision.  */

  𐤀𐤌 (TYPE_PRECISION (t1) > TYPE_PRECISION (t2))
    أرجع t1;
  وإلا 𐤀𐤌 (TYPE_PRECISION (t2) > TYPE_PRECISION (t1))
    أرجع t2;

  /* Same precision.  Prefer long longs to longs to ints when the
     same precision, following the C99 rules on integer type rank
     (which are equivalent to the C90 rules for C90 types).  */

  𐤀𐤌 (TYPE_MAIN_VARIANT (t1) == long_long_unsigned_type_node
      || TYPE_MAIN_VARIANT (t2) == long_long_unsigned_type_node)
    أرجع long_long_unsigned_type_node;

  𐤀𐤌 (TYPE_MAIN_VARIANT (t1) == long_long_integer_type_node
      || TYPE_MAIN_VARIANT (t2) == long_long_integer_type_node)
    {
      𐤀𐤌 (TYPE_UNSIGNED (t1) || TYPE_UNSIGNED (t2))
	أرجع long_long_unsigned_type_node;
      وإلا
	أرجع long_long_integer_type_node;
    }

  𐤀𐤌 (TYPE_MAIN_VARIANT (t1) == long_unsigned_type_node
      || TYPE_MAIN_VARIANT (t2) == long_unsigned_type_node)
    أرجع long_unsigned_type_node;

  𐤀𐤌 (TYPE_MAIN_VARIANT (t1) == long_integer_type_node
      || TYPE_MAIN_VARIANT (t2) == long_integer_type_node)
    {
      /* But preserve unsignedness from the other type,
	 since long cannot hold all the values of an unsigned int.  */
      𐤀𐤌 (TYPE_UNSIGNED (t1) || TYPE_UNSIGNED (t2))
	أرجع long_unsigned_type_node;
      وإلا
	أرجع long_integer_type_node;
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
  tree mv1 = TYPE_MAIN_VARIANT (t1);
  tree mv2 = TYPE_MAIN_VARIANT (t2);

  لكل (صحيح i = NUM_FLOATN_TYPES - 1; i >= 0; i--)
    𐤀𐤌 (mv1 == FLOATN_TYPE_NODE (i) || mv2 == FLOATN_TYPE_NODE (i))
      أرجع FLOATN_TYPE_NODE (i);

  /* Likewise, prefer long double to double even if same size.  */
  𐤀𐤌 (mv1 == long_double_type_node || mv2 == long_double_type_node)
    أرجع long_double_type_node;

  /* Likewise, prefer double to float even if same size.
     We got a couple of embedded targets with 32 bit doubles, and the
     pdp11 might have 64 bit floats.  */
  𐤀𐤌 (mv1 == double_type_node || mv2 == double_type_node)
    أرجع double_type_node;

  𐤀𐤌 (mv1 == float_type_node || mv2 == float_type_node)
    أرجع float_type_node;

  لكل (صحيح i = NUM_FLOATNX_TYPES - 1; i >= 0; i--)
    𐤀𐤌 (mv1 == FLOATNX_TYPE_NODE (i) || mv2 == FLOATNX_TYPE_NODE (i))
      أرجع FLOATNX_TYPE_NODE (i);

  𐤀𐤌 ((code1 == BITINT_TYPE || code2 == BITINT_TYPE) && code1 != code2)
    {
      /* Prefer any other integral types over bit-precise integer types.  */
      𐤀𐤌 (TYPE_UNSIGNED (t1) == TYPE_UNSIGNED (t2))
	أرجع code1 == BITINT_TYPE ? t2 : t1;
      /* If BITINT_TYPE is unsigned and the other type is signed
	 non-BITINT_TYPE with the same precision, the latter has higher rank.
	 In that case:
	 Otherwise, both operands are converted to the unsigned integer type
	 corresponding to the type of the operand with signed integer type.  */
      𐤀𐤌 (TYPE_UNSIGNED (code1 == BITINT_TYPE ? t1 : t2))
	أرجع c_common_unsigned_type (code1 == BITINT_TYPE ? t2 : t1);
    }

  /* Otherwise prefer the unsigned one.  */

  𐤀𐤌 (TYPE_UNSIGNED (t1))
    أرجع t1;
  وإلا
    أرجع t2;
}

/* Wrapper around c_common_type that is used by c-common.cc and other
   front end optimizations that remove promotions.  ENUMERAL_TYPEs
   are allowed here and are converted to their compatible integer types.
   BOOLEAN_TYPEs are allowed here and return either boolean_type_node or
   preferably a non-Boolean type as the common type.  */
tree
common_type (tree t1, tree t2)
{
  𐤀𐤌 (TREE_CODE (t1) == ENUMERAL_TYPE)
    t1 = ENUM_UNDERLYING_TYPE (t1);
  𐤀𐤌 (TREE_CODE (t2) == ENUMERAL_TYPE)
    t2 = ENUM_UNDERLYING_TYPE (t2);

  /* If both types are BOOLEAN_TYPE, then return boolean_type_node.  */
  𐤀𐤌 (TREE_CODE (t1) == BOOLEAN_TYPE
      && TREE_CODE (t2) == BOOLEAN_TYPE)
    أرجع boolean_type_node;

  /* If either type is BOOLEAN_TYPE, then return the other.  */
  𐤀𐤌 (TREE_CODE (t1) == BOOLEAN_TYPE)
    أرجع t2;
  𐤀𐤌 (TREE_CODE (t2) == BOOLEAN_TYPE)
    أرجع t1;

  أرجع c_common_type (t1, t2);
}



/* Helper function for comptypes.  For two compatible types, return 1
   if they pass consistency checks.  In particular we test that
   TYPE_CANONICAL is set correctly, i.e. the two types can alias.  */

ساكن منطقي
comptypes_verify (tree type1, tree type2)
{
  𐤀𐤌 (type1 == type2 || !type1 || !type2
      || TREE_CODE (type1) == ERROR_MARK || TREE_CODE (type2) == ERROR_MARK)
    أرجع true;

  gcc_checking_assert (c_verify_type (type1));
  gcc_checking_assert (c_verify_type (type2));

  𐤀𐤌 (TYPE_CANONICAL (type1) != TYPE_CANONICAL (type2)
      && !TYPE_STRUCTURAL_EQUALITY_P (type1)
      && !TYPE_STRUCTURAL_EQUALITY_P (type2))
    {
      /* FIXME: check other types. */
      𐤀𐤌 (RECORD_OR_UNION_TYPE_P (type1)
	  || TREE_CODE (type1) == ENUMERAL_TYPE
	  || TREE_CODE (type2) == ENUMERAL_TYPE)
	أرجع خطأ;
    }
  أرجع true;
}

بنية comptypes_data {

  /* output */
  منطقي enum_and_int_p;
  منطقي different_types_p;
  منطقي warning_needed;

  /* context */
  منطقي anon_field;
  منطقي pointedto;

  /* configuration */
  منطقي equiv;
  منطقي ignore_promoting_args;

  ثابت بنية tagged_tu_seen_cache* cache;
};


/* Helper function for composite_type.  This function ignores when the
   function type of an old-style declaration is incompatible with a type
   of a declaration with prototype because some are arguments are not
   self-promoting.  This is ignored only for function types but not
   ignored in a nested context.  */

ساكن منطقي
comptypes_check_for_composite (tree t1, tree t2)
{
  بنية comptypes_data data = { };
  data.ignore_promoting_args = FUNCTION_TYPE == TREE_CODE (t1);
  أرجع comptypes_internal (t1, t2, &data);
}


/* C implementation of compatible_types_for_indirection_note_p.  */

منطقي
compatible_types_for_indirection_note_p (tree type1, tree type2)
{
  أرجع comptypes (type1, type2);
}

/* Return true if TYPE1 and TYPE2 are compatible types for assignment
   or various other operations.  */

منطقي
comptypes (tree type1, tree type2)
{
  بنية comptypes_data data = { };
  منطقي ret = comptypes_internal (type1, type2, &data);

  gcc_checking_assert (!ret || comptypes_verify (type1, type2));

  أرجع ret;
}


/* Like comptypes, but it returns non-zero only for identical
   types.  */

منطقي
comptypes_same_p (tree type1, tree type2)
{
  بنية comptypes_data data = { };
  منطقي ret = comptypes_internal (type1, type2, &data);

  gcc_checking_assert (!ret || comptypes_verify (type1, type2));

  𐤀𐤌 (data.different_types_p)
    أرجع خطأ;

  أرجع ret;
}


/* Like comptypes, but if it returns true because enum and int are
   compatible, it sets *ENUM_AND_INT_P to true.  */

منطقي
comptypes_check_enum_int (tree type1, tree type2, منطقي *enum_and_int_p)
{
  بنية comptypes_data data = { };
  منطقي ret = comptypes_internal (type1, type2, &data);
  *enum_and_int_p = data.enum_and_int_p;

  gcc_checking_assert (!ret || comptypes_verify (type1, type2));

  أرجع ret;
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

منطقي
comptypes_equiv_p (tree type1, tree type2)
{
  بنية comptypes_data data = { };
  data.equiv = true;
  منطقي ret = comptypes_internal (type1, type2, &data);

  /* check that different equivance classes are assigned only
     to types that are not compatible.  */
  gcc_checking_assert (ret || !comptypes (type1, type2));

  أرجع ret;
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

ساكن منطقي
comptypes_internal (const_tree type1, const_tree type2,
		    بنية comptypes_data *data)
{
  const_tree t1 = type1;
  const_tree t2 = type2;

  /* Suppress errors caused by previously reported errors.  */

  𐤀𐤌 (t1 == t2 || !t1 || !t2
      || TREE_CODE (t1) == ERROR_MARK || TREE_CODE (t2) == ERROR_MARK)
    أرجع true;

  /* Qualifiers must match. C99 6.7.3p9 */

  𐤀𐤌 (TYPE_QUALS (t1) != TYPE_QUALS (t2))
    أرجع خطأ;

  /* Enumerated types are compatible with integer types, but this is
     not transitive: two enumerated types in the same translation unit
     are compatible with each other only if they are the same type.  */

  𐤀𐤌 (TREE_CODE (t1) == ENUMERAL_TYPE
      && COMPLETE_TYPE_P (t1)
      && TREE_CODE (t2) != ENUMERAL_TYPE)
    {
      t1 = ENUM_UNDERLYING_TYPE (t1);
      𐤀𐤌 (TREE_CODE (t2) != VOID_TYPE)
	{
	  data->enum_and_int_p = true;
	  data->different_types_p = true;
	}
    }
  وإلا 𐤀𐤌 (TREE_CODE (t2) == ENUMERAL_TYPE
	   && COMPLETE_TYPE_P (t2)
	   && TREE_CODE (t1) != ENUMERAL_TYPE)
    {
      t2 = ENUM_UNDERLYING_TYPE (t2);
      𐤀𐤌 (TREE_CODE (t1) != VOID_TYPE)
	{
	  data->enum_and_int_p = true;
	  data->different_types_p = true;
	}
    }

  𐤀𐤌 (t1 == t2)
    أرجع true;

  /* Different classes of types can't be compatible.  */

  𐤀𐤌 (TREE_CODE (t1) != TREE_CODE (t2))
    أرجع خطأ;

  /* Allow for two different type nodes which have essentially the same
     definition.  Note that we already checked for equality of the type
     qualifiers (just above).  */

  𐤀𐤌 (TREE_CODE (t1) != ARRAY_TYPE
      && TYPE_MAIN_VARIANT (t1) == TYPE_MAIN_VARIANT (t2))
    أرجع true;

  صحيح attrval;

  /* 1 if no need for warning yet, 2 if warning cause has been seen.  */
  𐤀𐤌 (!(attrval = comp_type_attributes (t1, t2)))
    أرجع خطأ;

  𐤀𐤌 (2 == attrval)
    data->warning_needed = true;

  بدل (TREE_CODE (t1))
    {
    حالة INTEGER_TYPE:
    حالة FIXED_POINT_TYPE:
    حالة REAL_TYPE:
    حالة BITINT_TYPE:
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
      أرجع TYPE_CANONICAL (t1) == TYPE_CANONICAL (t2);

    حالة POINTER_TYPE:
      /* Do not remove mode information.  */
      𐤀𐤌 (TYPE_MODE (t1) != TYPE_MODE (t2))
	أرجع خطأ;
      data->pointedto = true;
      أرجع comptypes_internal (TREE_TYPE (t1), TREE_TYPE (t2), data);

    حالة FUNCTION_TYPE:
      أرجع function_types_compatible_p (t1, t2, data);

    حالة ARRAY_TYPE:
      {
	tree d1 = TYPE_DOMAIN (t1);
	tree d2 = TYPE_DOMAIN (t2);

	/* Target types must match incl. qualifiers.  */
	𐤀𐤌 (!comptypes_internal (TREE_TYPE (t1), TREE_TYPE (t2), data))
	  أرجع خطأ;

	𐤀𐤌 ((d1 == NULL_TREE) != (d2 == NULL_TREE))
	  data->different_types_p = true;
	/* Ignore size mismatches when forming equivalence classes.  */
	𐤀𐤌 (data->equiv)
	  أرجع true;
	/* Sizes must match unless one is missing or variable.  */
	𐤀𐤌 (d1 == NULL_TREE || d2 == NULL_TREE || d1 == d2)
	  أرجع true;

	منطقي d1_variable = top_array_vla_p (t1);
	منطقي d2_variable = top_array_vla_p (t2);

	𐤀𐤌 (d1_variable != d2_variable)
	  data->different_types_p = true;
	𐤀𐤌 (d1_variable || d2_variable)
	  أرجع true;

	منطقي d1_zero = zero_length_array_type_p (t1)
		       || flexible_array_member_type_p (t1);

	منطقي d2_zero = zero_length_array_type_p (t2)
		       || flexible_array_member_type_p (t2);

	𐤀𐤌 (d1_zero && d2_zero)
	  أرجع true;
	𐤀𐤌 (d1_zero || d2_zero)
	  أرجع خطأ;

	𐤀𐤌 (!tree_int_cst_equal (TYPE_MIN_VALUE (d1), TYPE_MIN_VALUE (d2))
	    || !tree_int_cst_equal (TYPE_MAX_VALUE (d1), TYPE_MAX_VALUE (d2)))
	  أرجع خطأ;

	أرجع true;
      }

    حالة ENUMERAL_TYPE:
    حالة RECORD_TYPE:
    حالة UNION_TYPE:

      𐤀𐤌 (!flag_isoc23)
	أرجع خطأ;

      أرجع tagged_types_tu_compatible_p (t1, t2, data);

    حالة VECTOR_TYPE:
      أرجع known_eq (TYPE_VECTOR_SUBPARTS (t1), TYPE_VECTOR_SUBPARTS (t2))
	     && comptypes_internal (TREE_TYPE (t1), TREE_TYPE (t2), data);

    افتراضي:
      أرجع خطأ;
    }
  gcc_unreachable ();
}

/* Return true if TTL and TTR are pointers to types that are equivalent, ignoring
   their qualifiers, except for named address spaces.  If the pointers point to
   different named addresses, then we must determine if one address space is a
   subset of the other.  */

ساكن منطقي
comp_target_types (location_t location, tree ttl, tree ttr)
{
  tree mvl = TREE_TYPE (ttl);
  tree mvr = TREE_TYPE (ttr);
  addr_space_t asl = TYPE_ADDR_SPACE (mvl);
  addr_space_t asr = TYPE_ADDR_SPACE (mvr);
  addr_space_t as_common;

  /* Fail if pointers point to incompatible address spaces.  */
  𐤀𐤌 (!addr_space_superset (asl, asr, &as_common))
    أرجع 0;

  /* Qualifiers on element types of array types that are
     pointer targets are also removed.  */
  بنية comptypes_data data = { };
  𐤀𐤌 (!comptypes_internal (remove_qualifiers (mvl),
			   remove_qualifiers (mvr), &data))
    أرجع خطأ;

  /* For pedantic use comptypes on arrays before removing
     qualifiers on the element type. */
  𐤀𐤌 (TREE_CODE (mvl) == ARRAY_TYPE
      && TREE_CODE (mvr) == ARRAY_TYPE
      && !comptypes (mvl, mvr))
    pedwarn_c11 (location, OPT_Wpedantic, "invalid use of pointers to arrays "
					  "with different qualifiers in ISO C "
					  "before C23");

  𐤀𐤌 (data.warning_needed)
    pedwarn (location, OPT_Wpedantic, "types are not quite compatible");

  𐤀𐤌 (data.enum_and_int_p && warn_cxx_compat)
    warning_at (location, OPT_Wc___compat,
		"pointer target types incompatible in C++");

  أرجع true;
}

/* Subroutines of `comptypes'.  */

/* Return true if two 'struct', 'union', or 'enum' types T1 and T2 are
   compatible.  The two types are not the same (which has been
   checked earlier in comptypes_internal).  */

ساكن منطقي
tagged_types_tu_compatible_p (const_tree t1, const_tree t2,
			      بنية comptypes_data *data)
{
  tree s1, s2;

  𐤀𐤌 (c_type_tag (t1) != c_type_tag (t2))
    أرجع خطأ;

  /* When forming equivalence classes for TYPE_CANONICAL in C23, we treat
     structs with the same tag as equivalent, but only when they are targets
     of pointers inside other structs.  */
  𐤀𐤌 (data->equiv && data->pointedto && NULL_TREE != c_type_tag (t1))
    أرجع true;

  /* Different types without tag are incompatible except as an anonymous
     field or when forming equivalence classes for TYPE_CANONICAL.  */
  𐤀𐤌 (!data->anon_field && !data->equiv && NULL_TREE == c_type_tag (t1))
    أرجع خطأ;

  𐤀𐤌 (!data->anon_field && TYPE_STUB_DECL (t1) != TYPE_STUB_DECL (t2))
    data->different_types_p = true;

  /* Incomplete types are incompatible inside a TU.  */
  𐤀𐤌 (TYPE_SIZE (t1) == عدم || TYPE_SIZE (t2) == عدم)
    أرجع خطأ;

  𐤀𐤌 (ENUMERAL_TYPE != TREE_CODE (t1)
      && (TYPE_REVERSE_STORAGE_ORDER (t1)
	  != TYPE_REVERSE_STORAGE_ORDER (t2)))
    أرجع خطأ;

  𐤀𐤌 (TYPE_USER_ALIGN (t1) != TYPE_USER_ALIGN (t2))
    data->different_types_p = true;

  /* For types already being looked at in some active
     invocation of this function, assume compatibility.
     The cache is built as a linked list on the stack
     with the head of the list passed downwards.  */
  لكل (ثابت بنية tagged_tu_seen_cache *t = data->cache;
       t != عدم; t = t->next)
    𐤀𐤌 (t->t1 == t1 && t->t2 == t2)
      أرجع true;

  ثابت بنية tagged_tu_seen_cache entry = { data->cache, t1, t2 };

  بدل (TREE_CODE (t1))
    {
    حالة ENUMERAL_TYPE:
      {
	𐤀𐤌 (!comptypes (ENUM_UNDERLYING_TYPE (t1), ENUM_UNDERLYING_TYPE (t2)))
	  أرجع خطأ;

	/* Speed up the case where the type values are in the same order.  */
	tree tv1 = TYPE_VALUES (t1);
	tree tv2 = TYPE_VALUES (t2);

	𐤀𐤌 (tv1 == tv2)
	  أرجع true;

	لكل (;tv1 && tv2; tv1 = TREE_CHAIN (tv1), tv2 = TREE_CHAIN (tv2))
	  {
	    𐤀𐤌 (TREE_PURPOSE (tv1) != TREE_PURPOSE (tv2))
	      اكسر;

	    𐤀𐤌 (simple_cst_equal (DECL_INITIAL (TREE_VALUE (tv1)),
				  DECL_INITIAL (TREE_VALUE (tv2))) != 1)
	      اكسر;
	  }

	𐤀𐤌 (tv1 == NULL_TREE && tv2 == NULL_TREE)
	  أرجع true;

	𐤀𐤌 (tv1 == NULL_TREE || tv2 == NULL_TREE)
	  أرجع خطأ;

	𐤀𐤌 (list_length (TYPE_VALUES (t1)) != list_length (TYPE_VALUES (t2)))
	  أرجع خطأ;

	لكل (s1 = TYPE_VALUES (t1); s1; s1 = TREE_CHAIN (s1))
	  {
	    s2 = purpose_member (TREE_PURPOSE (s1), TYPE_VALUES (t2));

	    𐤀𐤌 (s2 == عدم
		|| simple_cst_equal (DECL_INITIAL (TREE_VALUE (s1)),
				     DECL_INITIAL (TREE_VALUE (s2))) != 1)
	      أرجع خطأ;
	  }

	أرجع true;
      }

    حالة UNION_TYPE:
    حالة RECORD_TYPE:

	𐤀𐤌 (list_length (TYPE_FIELDS (t1)) != list_length (TYPE_FIELDS (t2)))
	  أرجع خطأ;

	لكل (s1 = TYPE_FIELDS (t1), s2 = TYPE_FIELDS (t2);
	     s1 && s2;
	     s1 = DECL_CHAIN (s1), s2 = DECL_CHAIN (s2))
	  {
	    gcc_assert (TREE_CODE (s1) == FIELD_DECL);
	    gcc_assert (TREE_CODE (s2) == FIELD_DECL);

	    tree ft1 = TREE_TYPE (s1);
	    tree ft2 = TREE_TYPE (s2);

	    𐤀𐤌 (DECL_NAME (s1) != DECL_NAME (s2))
	      أرجع خطأ;

	    𐤀𐤌 (DECL_ALIGN (s1) != DECL_ALIGN (s2))
	      أرجع خطأ;

	    𐤀𐤌 (DECL_C_BIT_FIELD (s1) != DECL_C_BIT_FIELD (s2))
	       أرجع خطأ;

	    𐤀𐤌 (DECL_C_BIT_FIELD (s1))
	      {
		𐤀𐤌 (!tree_int_cst_equal (DECL_SIZE (s1), DECL_SIZE (s2)))
		  أرجع خطأ;

		ft1 = DECL_BIT_FIELD_TYPE (s1);
		ft2 = DECL_BIT_FIELD_TYPE (s2);
	      }

	    𐤀𐤌 (!ft1 || !ft2)
	      أرجع خطأ;

	    𐤀𐤌 (TREE_CODE (ft1) == ERROR_MARK || TREE_CODE (ft2) == ERROR_MARK)
	      أرجع خطأ;

	    data->anon_field = !DECL_NAME (s1);
	    data->pointedto = خطأ;

	    ثابت بنية tagged_tu_seen_cache *cache = data->cache;
	    data->cache = &entry;
	    منطقي ret = comptypes_internal (ft1, ft2, data);
	    data->cache = cache;
	    𐤀𐤌 (!ret)
	      أرجع خطأ;

	    tree st1 = TYPE_SIZE (TREE_TYPE (s1));
	    tree st2 = TYPE_SIZE (TREE_TYPE (s2));

	    𐤀𐤌 (data->equiv
		&& st1 && TREE_CODE (st1) == INTEGER_CST
		&& st2 && TREE_CODE (st2) == INTEGER_CST
		&& !tree_int_cst_equal (st1, st2))
	     أرجع خطأ;

	    tree counted_by1 = lookup_attribute ("counted_by",
						 DECL_ATTRIBUTES (s1));
	    tree counted_by2 = lookup_attribute ("counted_by",
						 DECL_ATTRIBUTES (s2));
	    /* If there is no counted_by attribute for both fields.  */
	    𐤀𐤌 (!counted_by1 && !counted_by2)
	      استمر;

	    /* If only one field has counted_by attribute.  */
	    𐤀𐤌 ((counted_by1 && !counted_by2)
		|| (!counted_by1 && counted_by2))
	      أرجع خطأ;

	    /* Now both s1 and s2 have counted_by attributes, check
	       whether they are the same.  */

	    tree counted_by_field1
	      = lookup_field (t1, TREE_VALUE (TREE_VALUE (counted_by1)));
	    tree counted_by_field2
	      = lookup_field (t2, TREE_VALUE (TREE_VALUE (counted_by2)));

	    gcc_assert (counted_by_field1 && counted_by_field2);

	    طالما (TREE_CHAIN (counted_by_field1))
	      counted_by_field1 = TREE_CHAIN (counted_by_field1);
	    طالما (TREE_CHAIN (counted_by_field2))
	      counted_by_field2 = TREE_CHAIN (counted_by_field2);

	    𐤀𐤌 (DECL_NAME (TREE_VALUE (counted_by_field1))
		!= DECL_NAME (TREE_VALUE (counted_by_field2)))
	      أرجع خطأ;
	  }
	أرجع true;

    افتراضي:
      gcc_unreachable ();
    }
}

/* Return true if two function types F1 and F2 are compatible.
   If either type specifies no argument types,
   the other must specify a fixed number of self-promoting arg types.
   Otherwise, if one type specifies only the number of arguments,
   the other must specify that number of self-promoting arg types.
   Otherwise, the argument types must match.  */

ساكن منطقي
function_types_compatible_p (const_tree f1, const_tree f2,
			     بنية comptypes_data *data)
{
  tree ret1 = TREE_TYPE (f1);
  tree ret2 = TREE_TYPE (f2);

  /* 'volatile' qualifiers on a function's return type used to mean
     the function is noreturn.  */
  𐤀𐤌 (TYPE_VOLATILE (ret1) != TYPE_VOLATILE (ret2))
    pedwarn (input_location, 0, "function return types not compatible due to %<volatile%>");
  𐤀𐤌 (TYPE_VOLATILE (ret1))
    ret1 = build_qualified_type (TYPE_MAIN_VARIANT (ret1),
				 TYPE_QUALS (ret1) & ~TYPE_QUAL_VOLATILE);
  𐤀𐤌 (TYPE_VOLATILE (ret2))
    ret2 = build_qualified_type (TYPE_MAIN_VARIANT (ret2),
				 TYPE_QUALS (ret2) & ~TYPE_QUAL_VOLATILE);

  منطقي ignore_pargs = data->ignore_promoting_args;
  data->ignore_promoting_args = خطأ;

  𐤀𐤌 (!comptypes_internal (ret1, ret2, data))
    أرجع خطأ;

  data->ignore_promoting_args = ignore_pargs;

  tree args1 = TYPE_ARG_TYPES (f1);
  tree args2 = TYPE_ARG_TYPES (f2);

  𐤀𐤌 ((args1 == NULL_TREE) != (args2 == NULL_TREE))
    data->different_types_p = true;

  /* An unspecified parmlist matches any specified parmlist
     whose argument types don't need default promotions.  */

  𐤀𐤌 (args1 == NULL_TREE)
    {
      𐤀𐤌 (TYPE_NO_NAMED_ARGS_STDARG_P (f1) != TYPE_NO_NAMED_ARGS_STDARG_P (f2))
	أرجع خطأ;
      𐤀𐤌 (!(data->ignore_promoting_args || self_promoting_args_p (args2)))
	أرجع خطأ;
      data->ignore_promoting_args = خطأ;
      /* If one of these types comes from a non-prototype fn definition,
	 compare that with the other type's arglist.
	 If they don't match, ask for a warning (but no error).  */
      𐤀𐤌 (TYPE_ACTUAL_ARG_TYPES (f1)
	  && !type_lists_compatible_p (args2, TYPE_ACTUAL_ARG_TYPES (f1), data))
	 data->warning_needed = true;
      أرجع true;
    }
  𐤀𐤌 (args2 == NULL_TREE)
    {
      𐤀𐤌 (TYPE_NO_NAMED_ARGS_STDARG_P (f1) != TYPE_NO_NAMED_ARGS_STDARG_P (f2))
	أرجع خطأ;
      𐤀𐤌 (!(data->ignore_promoting_args || self_promoting_args_p (args1)))
	أرجع خطأ;
      data->ignore_promoting_args = خطأ;
      𐤀𐤌 (TYPE_ACTUAL_ARG_TYPES (f2)
	  && !type_lists_compatible_p (args1, TYPE_ACTUAL_ARG_TYPES (f2), data))
	data->warning_needed = true;
      أرجع true;
    }

  /* Both types have argument lists: compare them and propagate results.  */
  أرجع type_lists_compatible_p (args1, args2, data);
}

/* Check two lists of types for compatibility, returning false for
   incompatible, true for compatible.  */

ساكن منطقي
type_lists_compatible_p (const_tree args1, const_tree args2,
			 بنية comptypes_data *data)
{
  طالما (1)
    {
      𐤀𐤌 (args1 == NULL_TREE && args2 == NULL_TREE)
	أرجع true;
      /* If one list is shorter than the other,
	 they fail to match.  */
      𐤀𐤌 (args1 == NULL_TREE || args2 == NULL_TREE)
	أرجع خطأ;
      tree a1 = TREE_VALUE (args1);
      tree a2 = TREE_VALUE (args2);
      tree mv1 = remove_qualifiers (a1);
      tree mv2 = remove_qualifiers (a2);

      gcc_assert (mv2);
      gcc_assert (mv2);

      /* If one of the lists has an error marker, ignore this arg.  */
      𐤀𐤌 (TREE_CODE (a1) == ERROR_MARK
	       || TREE_CODE (a2) == ERROR_MARK)
	;
      وإلا 𐤀𐤌 (!comptypes_internal (mv1, mv2, data))
	{
	  data->different_types_p = true;
	  /* Allow  wait (union {union wait *u; int *i} *)
	     and  wait (union wait *)  to be compatible.  */
	  𐤀𐤌 (TREE_CODE (a1) == UNION_TYPE
	      && (TYPE_NAME (a1) == NULL_TREE
		  || TYPE_TRANSPARENT_AGGR (a1))
	      && TREE_CODE (TYPE_SIZE (a1)) == INTEGER_CST
	      && tree_int_cst_equal (TYPE_SIZE (a1),
				     TYPE_SIZE (a2)))
	    {
	      tree memb;
	      لكل (memb = TYPE_FIELDS (a1);
		   memb; memb = DECL_CHAIN (memb))
		{
		  tree mv3 = remove_qualifiers (TREE_TYPE (memb));
		  𐤀𐤌 (comptypes_internal (mv3, mv2, data))
		    اكسر;
		}
	      𐤀𐤌 (memb == NULL_TREE)
		أرجع خطأ;
	    }
	  وإلا 𐤀𐤌 (TREE_CODE (a2) == UNION_TYPE
		   && (TYPE_NAME (a2) == NULL_TREE
		       || TYPE_TRANSPARENT_AGGR (a2))
		   && TREE_CODE (TYPE_SIZE (a2)) == INTEGER_CST
		   && tree_int_cst_equal (TYPE_SIZE (a2),
					  TYPE_SIZE (a1)))
	    {
	      tree memb;
	      لكل (memb = TYPE_FIELDS (a2);
		   memb; memb = DECL_CHAIN (memb))
		{
		  tree mv3 = remove_qualifiers (TREE_TYPE (memb));
		  𐤀𐤌 (comptypes_internal (mv3, mv1, data))
		    اكسر;
		}
	      𐤀𐤌 (memb == NULL_TREE)
		أرجع خطأ;
	    }
	  وإلا
	    أرجع خطأ;
	}

      args1 = TREE_CHAIN (args1);
      args2 = TREE_CHAIN (args2);
    }
}

/* Compute the size to increment a pointer by.  When a function type or void
   type or incomplete type is passed, size_one_node is returned.
   This function does not emit any diagnostics; the caller is responsible
   for that.  */

ساكن tree
c_size_in_bytes (const_tree type)
{
  تعداد tree_code code = TREE_CODE (type);

  𐤀𐤌 (code == FUNCTION_TYPE || code == VOID_TYPE || code == ERROR_MARK
      || !COMPLETE_TYPE_P (type))
    أرجع size_one_node;

  /* Convert in case a char is more than one unit.  */
  أرجع size_binop_loc (input_location, CEIL_DIV_EXPR, TYPE_SIZE_UNIT (type),
			 size_int (TYPE_PRECISION (char_type_node)
				   / BITS_PER_UNIT));
}

/* Return either DECL or its known constant value (if it has one).  */

tree
decl_constant_value_1 (tree decl, منطقي in_init)
{
  𐤀𐤌 (/* Note that DECL_INITIAL isn't valid for a PARM_DECL.  */
      TREE_CODE (decl) != PARM_DECL
      && !TREE_THIS_VOLATILE (decl)
      && TREE_READONLY (decl)
      && DECL_INITIAL (decl) != NULL_TREE
      && !error_operand_p (DECL_INITIAL (decl))
      /* This is invalid if initial value is not constant.
	 If it has either a function call, a memory reference,
	 or a variable, then re-evaluating it could give different results.  */
      && TREE_CONSTANT (DECL_INITIAL (decl))
      /* Check for cases where this is sub-optimal, even though valid.  */
      && (in_init || TREE_CODE (DECL_INITIAL (decl)) != CONSTRUCTOR))
    أرجع DECL_INITIAL (decl);
  أرجع decl;
}

/* Return either DECL or its known constant value (if it has one).
   Like the above, but always return decl outside of functions.  */

tree
decl_constant_value (tree decl)
{
  /* Don't change a variable array bound or initial value to a constant
     in a place where a variable is invalid.  */
  أرجع current_function_decl ? decl_constant_value_1 (decl, خطأ) : decl;
}

/* Convert the array expression EXP to a pointer.  */
ساكن tree
array_to_pointer_conversion (location_t loc, tree exp)
{
  tree orig_exp = exp;
  tree type = TREE_TYPE (exp);
  tree adr;
  tree restype = TREE_TYPE (type);
  tree ptrtype;

  gcc_assert (TREE_CODE (type) == ARRAY_TYPE);

  STRIP_TYPE_NOPS (exp);

  copy_warning (exp, orig_exp);

  ptrtype = c_build_pointer_type (restype);

  𐤀𐤌 (INDIRECT_REF_P (exp))
    أرجع convert (ptrtype, TREE_OPERAND (exp, 0));

  /* In C++ array compound literals are temporary objects unless they are
     const or appear in namespace scope, so they are destroyed too soon
     to use them for much of anything  (c++/53220).  */
  𐤀𐤌 (warn_cxx_compat && TREE_CODE (exp) == COMPOUND_LITERAL_EXPR)
    {
      tree decl = TREE_OPERAND (TREE_OPERAND (exp, 0), 0);
      𐤀𐤌 (!TREE_READONLY (decl) && !TREE_STATIC (decl))
	warning_at (DECL_SOURCE_LOCATION (decl), OPT_Wc___compat,
		    "converting an array compound literal to a pointer "
		    "leads to a dangling pointer in C++");
    }

  adr = build_unary_op (loc, ADDR_EXPR, exp, true);
  أرجع convert (ptrtype, adr);
}

/* Convert the function expression EXP to a pointer.  */
ساكن tree
function_to_pointer_conversion (location_t loc, tree exp)
{
  tree orig_exp = exp;

  gcc_assert (TREE_CODE (TREE_TYPE (exp)) == FUNCTION_TYPE);

  STRIP_TYPE_NOPS (exp);

  copy_warning (exp, orig_exp);

  tree exp2 = build_unary_op (loc, ADDR_EXPR, exp, خطأ);

  /* If the function is defined and known to not require a non-local
     context, make sure no trampoline is generated.  */
  𐤀𐤌 (TREE_CODE (exp) == FUNCTION_DECL
      && DECL_INITIAL (exp) && !C_FUNC_NONLOCAL_CONTEXT (exp))
   TREE_NO_TRAMPOLINE (exp2) = 1;

  أرجع exp2;
}

/* Mark EXP as read, not just set, for set but not used -Wunused
   warning purposes.  */

فراغ
mark_exp_read (tree exp)
{
  بدل (TREE_CODE (exp))
    {
    حالة VAR_DECL:
    حالة PARM_DECL:
      DECL_READ_P (exp) = 1;
      اكسر;
    CASE_CONVERT:
      𐤀𐤌 (VOID_TYPE_P (TREE_TYPE (exp)))
	بدل (TREE_CODE (TREE_OPERAND (exp, 0)))
	  {
	  حالة PREINCREMENT_EXPR:
	  حالة PREDECREMENT_EXPR:
	  حالة POSTINCREMENT_EXPR:
	  حالة POSTDECREMENT_EXPR:
	    أرجع;
	  افتراضي:
	    اكسر;
	  }
      /* FALLTHRU */
    حالة ARRAY_REF:
    حالة COMPONENT_REF:
    حالة MODIFY_EXPR:
    حالة REALPART_EXPR:
    حالة IMAGPART_EXPR:
    حالة ADDR_EXPR:
    حالة VIEW_CONVERT_EXPR:
    حالة PREINCREMENT_EXPR:
    حالة PREDECREMENT_EXPR:
    حالة POSTINCREMENT_EXPR:
    حالة POSTDECREMENT_EXPR:
      mark_exp_read (TREE_OPERAND (exp, 0));
      اكسر;
    حالة COMPOUND_EXPR:
      /* Pattern match what build_atomic_assign produces with modifycode
	 NOP_EXPR.  */
      𐤀𐤌 (VAR_P (TREE_OPERAND (exp, 1))
	  && DECL_ARTIFICIAL (TREE_OPERAND (exp, 1))
	  && TREE_CODE (TREE_OPERAND (exp, 0)) == COMPOUND_EXPR)
	{
	  tree t1 = TREE_OPERAND (TREE_OPERAND (exp, 0), 0);
	  tree t2 = TREE_OPERAND (TREE_OPERAND (exp, 0), 1);
	  𐤀𐤌 (TREE_CODE (t1) == TARGET_EXPR
	      && TARGET_EXPR_SLOT (t1) == TREE_OPERAND (exp, 1)
	      && TREE_CODE (t2) == CALL_EXPR)
	    {
	      tree fndecl = get_callee_fndecl (t2);
	      tree arg = NULL_TREE;
	      𐤀𐤌 (fndecl
		  && TREE_CODE (fndecl) == FUNCTION_DECL
		  && fndecl_built_in_p (fndecl, BUILT_IN_NORMAL)
		  && call_expr_nargs (t2) >= 2)
		بدل (DECL_FUNCTION_CODE (fndecl))
		  {
		  حالة BUILT_IN_ATOMIC_STORE:
		    arg = CALL_EXPR_ARG (t2, 1);
		    اكسر;
		  حالة BUILT_IN_ATOMIC_STORE_1:
		  حالة BUILT_IN_ATOMIC_STORE_2:
		  حالة BUILT_IN_ATOMIC_STORE_4:
		  حالة BUILT_IN_ATOMIC_STORE_8:
		  حالة BUILT_IN_ATOMIC_STORE_16:
		    arg = CALL_EXPR_ARG (t2, 0);
		    اكسر;
		  افتراضي:
		    اكسر;
		  }
	      𐤀𐤌 (arg)
		{
		  STRIP_NOPS (arg);
		  𐤀𐤌 (TREE_CODE (arg) == ADDR_EXPR
		      && DECL_P (TREE_OPERAND (arg, 0))
		      && TYPE_ATOMIC (TREE_TYPE (TREE_OPERAND (arg, 0))))
		    mark_exp_read (TREE_OPERAND (arg, 0));
		}
	    }
	}
      /* FALLTHRU */
    حالة C_MAYBE_CONST_EXPR:
      mark_exp_read (TREE_OPERAND (exp, 1));
      اكسر;
    حالة OMP_ARRAY_SECTION:
      mark_exp_read (TREE_OPERAND (exp, 0));
      𐤀𐤌 (TREE_OPERAND (exp, 1))
	mark_exp_read (TREE_OPERAND (exp, 1));
      𐤀𐤌 (TREE_OPERAND (exp, 2))
	mark_exp_read (TREE_OPERAND (exp, 2));
      اكسر;
    افتراضي:
      اكسر;
    }
}

/* Perform the default conversion of arrays and functions to pointers.
   Return the result of converting EXP.  For any other expression, just
   return EXP.

   LOC is the location of the expression.  */

بنية c_expr
default_function_array_conversion (location_t loc, بنية c_expr exp)
{
  tree orig_exp = exp.value;
  tree type = TREE_TYPE (exp.value);
  تعداد tree_code code = TREE_CODE (type);

  بدل (code)
    {
    حالة ARRAY_TYPE:
      {
	منطقي not_lvalue = خطأ;
	منطقي lvalue_array_p;

	طالما ((TREE_CODE (exp.value) == NON_LVALUE_EXPR
		|| CONVERT_EXPR_P (exp.value))
	       && TREE_TYPE (TREE_OPERAND (exp.value, 0)) == type)
	  {
	    𐤀𐤌 (TREE_CODE (exp.value) == NON_LVALUE_EXPR)
	      not_lvalue = true;
	    exp.value = TREE_OPERAND (exp.value, 0);
	  }

	copy_warning (exp.value, orig_exp);

	lvalue_array_p = !not_lvalue && lvalue_p (exp.value);
	𐤀𐤌 (!flag_isoc99 && !lvalue_array_p)
	  {
	    /* Before C99, non-lvalue arrays do not decay to pointers.
	       Normally, using such an array would be invalid; but it can
	       be used correctly inside sizeof or as a statement expression.
	       Thus, do not give an error here; an error will result later.  */
	    أرجع exp;
	  }

	exp.value = array_to_pointer_conversion (loc, exp.value);
      }
      اكسر;
    حالة FUNCTION_TYPE:
      exp.value = function_to_pointer_conversion (loc, exp.value);
      اكسر;
    افتراضي:
      اكسر;
    }

  أرجع exp;
}

بنية c_expr
default_function_array_read_conversion (location_t loc, بنية c_expr exp)
{
  mark_exp_read (exp.value);
  /* We only generate a call to .ACCESS_WITH_SIZE when it is a read.  */
  𐤀𐤌 (TREE_CODE (exp.value) == COMPONENT_REF
      && handle_counted_by_p (exp.value))
    exp.value = handle_counted_by_for_component_ref (loc, exp.value);
  أرجع default_function_array_conversion (loc, exp);
}

/* Return whether EXPR should be treated as an atomic lvalue for the
   purposes of load and store handling.  */

ساكن منطقي
really_atomic_lvalue (tree expr)
{
  𐤀𐤌 (error_operand_p (expr))
    أرجع خطأ;
  𐤀𐤌 (!TYPE_ATOMIC (TREE_TYPE (expr)))
    أرجع خطأ;
  𐤀𐤌 (!COMPLETE_TYPE_P (TREE_TYPE (expr)))
    أرجع خطأ;
  𐤀𐤌 (!lvalue_p (expr))
    أرجع خطأ;

  /* Ignore _Atomic on register variables, since their addresses can't
     be taken so (a) atomicity is irrelevant and (b) the normal atomic
     sequences wouldn't work.  Ignore _Atomic on structures containing
     bit-fields, since accessing elements of atomic structures or
     unions is undefined behavior (C11 6.5.2.3#5), but it's unclear if
     it's undefined at translation time or execution time, and the
     normal atomic sequences again wouldn't work.  */
  طالما (handled_component_p (expr))
    {
      𐤀𐤌 (TREE_CODE (expr) == COMPONENT_REF
	  && DECL_C_BIT_FIELD (TREE_OPERAND (expr, 1)))
	أرجع خطأ;
      expr = TREE_OPERAND (expr, 0);
    }
  𐤀𐤌 (TREE_CODE (expr) == COMPOUND_LITERAL_EXPR)
    expr = COMPOUND_LITERAL_EXPR_DECL (expr);
  𐤀𐤌 (DECL_P (expr) && C_DECL_REGISTER (expr))
    أرجع خطأ;
  أرجع true;
}

/* If EXPR is a named constant (C23) derived from a constexpr variable
   - that is, a reference to such a variable, or a member extracted by
   a sequence of structure and union (but not array) member accesses
   (where union member accesses must access the same member as
   initialized) - then return the corresponding initializer;
   otherwise, return NULL_TREE.  */

ساكن tree
maybe_get_constexpr_init (tree expr)
{
  tree decl = NULL_TREE;
  𐤀𐤌 (TREE_CODE (expr) == VAR_DECL)
    decl = expr;
  وإلا 𐤀𐤌 (TREE_CODE (expr) == COMPOUND_LITERAL_EXPR)
    decl = COMPOUND_LITERAL_EXPR_DECL (expr);
  𐤀𐤌 (decl
      && C_DECL_DECLARED_CONSTEXPR (decl)
      && DECL_INITIAL (decl) != NULL_TREE
      && !error_operand_p (DECL_INITIAL (decl)))
    أرجع DECL_INITIAL (decl);
  𐤀𐤌 (TREE_CODE (expr) != COMPONENT_REF)
    أرجع NULL_TREE;
  tree inner = maybe_get_constexpr_init (TREE_OPERAND (expr, 0));
  𐤀𐤌 (inner == NULL_TREE)
    أرجع NULL_TREE;
  طالما ((CONVERT_EXPR_P (inner) || TREE_CODE (inner) == NON_LVALUE_EXPR)
	 && !error_operand_p (inner)
	 && (TYPE_MAIN_VARIANT (TREE_TYPE (inner))
	     == TYPE_MAIN_VARIANT (TREE_TYPE (TREE_OPERAND (inner, 0)))))
    inner = TREE_OPERAND (inner, 0);
  𐤀𐤌 (TREE_CODE (inner) != CONSTRUCTOR)
    أرجع NULL_TREE;
  tree field = TREE_OPERAND (expr, 1);
  unsigned HOST_WIDE_INT cidx;
  tree cfield, cvalue;
  منطقي have_other_init = خطأ;
  FOR_EACH_CONSTRUCTOR_ELT (CONSTRUCTOR_ELTS (inner), cidx, cfield, cvalue)
    {
      𐤀𐤌 (cfield == field)
	أرجع cvalue;
      have_other_init = true;
    }
  𐤀𐤌 (TREE_CODE (TREE_TYPE (inner)) == UNION_TYPE
      && (have_other_init || field != TYPE_FIELDS (TREE_TYPE (inner))))
    أرجع NULL_TREE;
  /* Return a default initializer.  */
  𐤀𐤌 (RECORD_OR_UNION_TYPE_P (TREE_TYPE (expr)))
    أرجع build_constructor (TREE_TYPE (expr), عدم);
  أرجع build_zero_cst (TREE_TYPE (expr));
}

/* Helper function for convert_lvalue_to_rvalue called via
   walk_tree_without_duplicates.  Find DATA inside of the expression.  */

ساكن tree
c_find_var_r (tree *tp, صحيح *walk_subtrees, فراغ *data)
{
  𐤀𐤌 (TYPE_P (*tp))
    *walk_subtrees = 0;
  وإلا 𐤀𐤌 (*tp == (tree) data)
    أرجع *tp;
  أرجع NULL_TREE;
}

/* Convert expression EXP (location LOC) from lvalue to rvalue,
   including converting functions and arrays to pointers if CONVERT_P.
   If READ_P, also mark the expression as having been read.  If
   FOR_INIT, constexpr expressions of structure and union type should
   be replaced by the corresponding CONSTRUCTOR; otherwise, only
   constexpr scalars (including elements of structures and unions) are
   replaced by their initializers.  */

بنية c_expr
convert_lvalue_to_rvalue (location_t loc, بنية c_expr exp,
			  منطقي convert_p, منطقي read_p, منطقي for_init)
{
  منطقي force_non_npc = خطأ;
  𐤀𐤌 (read_p)
    mark_exp_read (exp.value);
  /* We only generate a call to .ACCESS_WITH_SIZE when it is a read.  */
  𐤀𐤌 (read_p && TREE_CODE (exp.value) == COMPONENT_REF
      && handle_counted_by_p (exp.value))
    exp.value = handle_counted_by_for_component_ref (loc, exp.value);

  𐤀𐤌 (convert_p)
    exp = default_function_array_conversion (loc, exp);
  𐤀𐤌 (!VOID_TYPE_P (TREE_TYPE (exp.value))
      || (flag_isoc2y
	  && TYPE_QUALS (TREE_TYPE (exp.value)) != TYPE_UNQUALIFIED))
    exp.value = require_complete_type (loc, exp.value);
  𐤀𐤌 (for_init || !RECORD_OR_UNION_TYPE_P (TREE_TYPE (exp.value)))
    {
      tree init = maybe_get_constexpr_init (exp.value);
      𐤀𐤌 (init != NULL_TREE)
	{
	  /* A named constant of pointer type or type nullptr_t is not
	     a null pointer constant even if the initializer is
	     one.  */
	  𐤀𐤌 (TREE_CODE (init) == INTEGER_CST
	      && !INTEGRAL_TYPE_P (TREE_TYPE (init))
	      && integer_zerop (init))
	    force_non_npc = true;
	  exp.value = init;
	}
    }
  𐤀𐤌 (really_atomic_lvalue (exp.value))
    {
      vec<tree, va_gc> *params;
      tree nonatomic_type, tmp, tmp_addr, fndecl, func_call;
      tree expr_type = TREE_TYPE (exp.value);
      tree expr_addr = build_unary_op (loc, ADDR_EXPR, exp.value, خطأ);
      tree seq_cst = build_int_cst (integer_type_node, MEMMODEL_SEQ_CST);

      gcc_assert (TYPE_ATOMIC (expr_type));

      /* Expansion of a generic atomic load may require an addition
	 element, so allocate enough to prevent a resize.  */
      vec_alloc (params, 4);

      /* Remove the qualifiers for the rest of the expressions and
	 create the VAL temp variable to hold the RHS.  */
      nonatomic_type = build_qualified_type (expr_type, TYPE_UNQUALIFIED);
      tmp = create_tmp_var_raw (nonatomic_type);
      tmp_addr = build_unary_op (loc, ADDR_EXPR, tmp, خطأ);
      TREE_ADDRESSABLE (tmp) = 1;
      /* Do not disable warnings for TMP even though it's artificial.
	 -Winvalid-memory-model depends on it.  */

      /* Issue __atomic_load (&expr, &tmp, SEQ_CST);  */
      fndecl = builtin_decl_explicit (BUILT_IN_ATOMIC_LOAD);
      params->quick_push (expr_addr);
      params->quick_push (tmp_addr);
      params->quick_push (seq_cst);
      func_call = c_build_function_call_vec (loc, vNULL, fndecl, params, عدم);

      /* EXPR is always read.  */
      mark_exp_read (exp.value);

      /* Optimize the common case where c_build_function_call_vec
	 immediately folds __atomic_load (&expr, &tmp, SEQ_CST); into
	 tmp = __atomic_load_<N> (&expr, SEQ_CST);
	 In that case tmp is not addressable and can be initialized
	 fully by the rhs of the MODIFY_EXPR.  */
      tree tem = func_call;
      𐤀𐤌 (CONVERT_EXPR_P (tem) && VOID_TYPE_P (TREE_TYPE (tem)))
	{
	  tem = TREE_OPERAND (tem, 0);
	  𐤀𐤌 (TREE_CODE (tem) == MODIFY_EXPR
	      && TREE_OPERAND (tem, 0) == tmp
	      && !walk_tree_without_duplicates (&TREE_OPERAND (tem, 1),
						c_find_var_r, tmp))
	    {
	      TREE_ADDRESSABLE (tmp) = 0;
	      func_call = TREE_OPERAND (tem, 1);
	    }
	}

      /* Return tmp which contains the value loaded.  */
      exp.value = build4 (TARGET_EXPR, nonatomic_type, tmp, func_call,
			  NULL_TREE, NULL_TREE);
    }
  𐤀𐤌 (convert_p && !error_operand_p (exp.value)
      && (TREE_CODE (TREE_TYPE (exp.value)) != ARRAY_TYPE))
    exp.value = convert (build_qualified_type (TREE_TYPE (exp.value), TYPE_UNQUALIFIED), exp.value);
  𐤀𐤌 (force_non_npc)
    exp.value = build1 (NOP_EXPR, TREE_TYPE (exp.value), exp.value);

  {
    tree false_value, true_value;
    𐤀𐤌 (convert_p && !error_operand_p (exp.value)
	&& c_hardbool_type_attr (TREE_TYPE (exp.value),
				 &false_value, &true_value))
      {
	tree t = save_expr (exp.value);

	mark_exp_read (exp.value);

	tree trapfn = builtin_decl_explicit (BUILT_IN_TRAP);
	tree expr = build_call_expr_loc (loc, trapfn, 0);
	expr = build_compound_expr (loc, expr, boolean_true_node);
	expr = fold_build3_loc (loc, COND_EXPR, boolean_type_node,
				fold_build2_loc (loc, NE_EXPR,
						 boolean_type_node,
						 t, true_value),
				expr, boolean_true_node);
	expr = fold_build3_loc (loc, COND_EXPR, boolean_type_node,
				fold_build2_loc (loc, NE_EXPR,
						 boolean_type_node,
						 t, false_value),
				expr, boolean_false_node);

	exp.value = expr;
      }
  }

  أرجع exp;
}

/* Wrapper for the overload above, same arguments but for tree rather than
   c_expr.  This is important for hardbools to decay to bools.  */

ساكن مضمن tree
convert_lvalue_to_rvalue (location_t loc, tree val,
			  منطقي convert_p, منطقي read_p, منطقي for_init = خطأ)
{
  بنية c_expr expr;
  memset (&expr, 0, حجم (expr));
  expr.value = val;
  expr = convert_lvalue_to_rvalue (loc, expr, convert_p, read_p, for_init);
  أرجع expr.value;
}

/* EXP is an expression of integer type.  Apply the integer promotions
   to it and return the promoted value.  */

tree
perform_integral_promotions (tree exp)
{
  tree type = TREE_TYPE (exp);
  تعداد tree_code code = TREE_CODE (type);

  gcc_assert (INTEGRAL_TYPE_P (type));

  /* Convert enums to the result of applying the integer promotions to
     their underlying type.  */
  𐤀𐤌 (code == ENUMERAL_TYPE)
    {
      type = ENUM_UNDERLYING_TYPE (type);
      𐤀𐤌 (c_promoting_integer_type_p (type))
	{
	  𐤀𐤌 (TYPE_UNSIGNED (type)
	      && TYPE_PRECISION (type) == TYPE_PRECISION (integer_type_node))
	    type = unsigned_type_node;
	  وإلا
	    type = integer_type_node;
	}

      أرجع convert (type, exp);
    }

  /* ??? This should no longer be needed now bit-fields have their
     proper types.  */
  𐤀𐤌 (TREE_CODE (exp) == COMPONENT_REF
      && DECL_C_BIT_FIELD (TREE_OPERAND (exp, 1)))
    {
      𐤀𐤌 (BITINT_TYPE_P (DECL_BIT_FIELD_TYPE (TREE_OPERAND (exp, 1))))
	{
	  tree btype = DECL_BIT_FIELD_TYPE (TREE_OPERAND (exp, 1));
	  𐤀𐤌 (TREE_CODE (btype) == BITINT_TYPE)
	    أرجع convert (btype, exp);
	  وإلا
	    أرجع convert (ENUM_UNDERLYING_TYPE (btype), exp);
	}
      /* If it's thinner than an int, promote it like a
	 c_promoting_integer_type_p, otherwise leave it alone.  */
      𐤀𐤌 (compare_tree_int (DECL_SIZE (TREE_OPERAND (exp, 1)),
			    TYPE_PRECISION (integer_type_node)) < 0)
	أرجع convert (integer_type_node, exp);
    }

  𐤀𐤌 (c_promoting_integer_type_p (type))
    {
      /* Preserve unsignedness if not really getting any wider.  */
      𐤀𐤌 (TYPE_UNSIGNED (type)
	  && TYPE_PRECISION (type) == TYPE_PRECISION (integer_type_node))
	أرجع convert (unsigned_type_node, exp);

      أرجع convert (integer_type_node, exp);
    }

  أرجع exp;
}


/* Perform default promotions for C data used in expressions.
   Enumeral types or short or char are converted to int.
   In addition, manifest constants symbols are replaced by their values.  */

tree
default_conversion (tree exp)
{
  tree orig_exp;
  tree type = TREE_TYPE (exp);
  تعداد tree_code code = TREE_CODE (type);
  tree promoted_type;

  mark_exp_read (exp);
  /* We only generate a call to .ACCESS_WITH_SIZE when it is a read.  */
  𐤀𐤌 (TREE_CODE (exp) == COMPONENT_REF
      && handle_counted_by_p (exp))
    exp = handle_counted_by_for_component_ref (EXPR_LOCATION (exp), exp);

  /* Functions and arrays have been converted during parsing.  */
  gcc_assert (code != FUNCTION_TYPE);
  𐤀𐤌 (code == ARRAY_TYPE)
    أرجع exp;

  /* Constants can be used directly unless they're not loadable.  */
  𐤀𐤌 (TREE_CODE (exp) == CONST_DECL)
    exp = DECL_INITIAL (exp);

  /* Strip no-op conversions.  */
  orig_exp = exp;
  STRIP_TYPE_NOPS (exp);

  copy_warning (exp, orig_exp);

  𐤀𐤌 (code == VOID_TYPE)
    {
      error_at (EXPR_LOC_OR_LOC (exp, input_location),
		"void value not ignored as it ought to be");
      أرجع error_mark_node;
    }

  exp = require_complete_type (EXPR_LOC_OR_LOC (exp, input_location), exp);
  𐤀𐤌 (exp == error_mark_node)
    أرجع error_mark_node;

  promoted_type = targetm.promoted_type (type);
  𐤀𐤌 (promoted_type)
    أرجع convert (promoted_type, exp);

  𐤀𐤌 (INTEGRAL_TYPE_P (type))
    {
      /* Avoid performing integral promotion of bit-precise integer
	 type bit-field to its corresponding bit-precise integer if
	 orig_exp is a cast to it to its underlying type.  */
      𐤀𐤌 (orig_exp != exp
	  && TREE_CODE (exp) == COMPONENT_REF
	  && DECL_C_BIT_FIELD (TREE_OPERAND (exp, 1))
	  && BITINT_TYPE_P (DECL_BIT_FIELD_TYPE (TREE_OPERAND (exp, 1))))
	أرجع perform_integral_promotions (orig_exp);
      أرجع perform_integral_promotions (exp);
    }

  أرجع exp;
}

/* Look up COMPONENT in a structure or union TYPE.

   If the component name is not found, returns NULL_TREE.  Otherwise,
   the return value is a TREE_LIST, with each TREE_VALUE a FIELD_DECL
   stepping down the chain to the component, which is in the last
   TREE_VALUE of the list.  Normally the list is of length one, but if
   the component is embedded within (nested) anonymous structures or
   unions, the list steps down the chain to the component.  */

tree
lookup_field (const_tree type, tree component)
{
  tree field;

  /* If TYPE_LANG_SPECIFIC is set, then it is a sorted array of pointers
     to the field elements.  Use a binary search on this array to quickly
     find the element.  Otherwise, do a linear search.  TYPE_LANG_SPECIFIC
     will always be set for structures which have many elements.

     Duplicate field checking replaces duplicates with NULL_TREE so
     TYPE_LANG_SPECIFIC arrays are potentially no longer sorted.  In that
     case just iterate using DECL_CHAIN.  */

  𐤀𐤌 (TYPE_LANG_SPECIFIC (type) && TYPE_LANG_SPECIFIC (type)->s
      && !seen_error ())
    {
      صحيح bot, top, half;
      tree *field_array = &TYPE_LANG_SPECIFIC (type)->s->elts[0];

      field = TYPE_FIELDS (type);
      bot = 0;
      top = TYPE_LANG_SPECIFIC (type)->s->len;
      طالما (top - bot > 1)
	{
	  half = (top - bot + 1) >> 1;
	  field = field_array[bot+half];

	  𐤀𐤌 (DECL_NAME (field) == NULL_TREE)
	    {
	      /* Step through all anon unions in linear fashion.  */
	      طالما (DECL_NAME (field_array[bot]) == NULL_TREE)
		{
		  field = field_array[bot++];
		  𐤀𐤌 (RECORD_OR_UNION_TYPE_P (TREE_TYPE (field)))
		    {
		      tree anon = lookup_field (TREE_TYPE (field), component);

		      𐤀𐤌 (anon)
			أرجع tree_cons (NULL_TREE, field, anon);

		      /* The Plan 9 compiler permits referring
			 directly to an anonymous struct/union field
			 using a typedef name.  */
		      𐤀𐤌 (flag_plan9_extensions
			  && TYPE_NAME (TREE_TYPE (field)) != NULL_TREE
			  && (TREE_CODE (TYPE_NAME (TREE_TYPE (field)))
			      == TYPE_DECL)
			  && (DECL_NAME (TYPE_NAME (TREE_TYPE (field)))
			      == component))
			اكسر;
		    }
		}

	      /* Entire record is only anon unions.  */
	      𐤀𐤌 (bot > top)
		أرجع NULL_TREE;

	      /* Restart the binary search, with new lower bound.  */
	      استمر;
	    }

	  𐤀𐤌 (DECL_NAME (field) == component)
	    اكسر;
	  𐤀𐤌 (DECL_NAME (field) < component)
	    bot += half;
	  وإلا
	    top = bot + half;
	}

      𐤀𐤌 (DECL_NAME (field_array[bot]) == component)
	field = field_array[bot];
      وإلا 𐤀𐤌 (DECL_NAME (field) != component)
	أرجع NULL_TREE;
    }
  وإلا
    {
      لكل (field = TYPE_FIELDS (type); field; field = DECL_CHAIN (field))
	{
	  𐤀𐤌 (DECL_NAME (field) == NULL_TREE
	      && RECORD_OR_UNION_TYPE_P (TREE_TYPE (field)))
	    {
	      tree anon = lookup_field (TREE_TYPE (field), component);

	      𐤀𐤌 (anon)
		أرجع tree_cons (NULL_TREE, field, anon);

	      /* The Plan 9 compiler permits referring directly to an
		 anonymous struct/union field using a typedef
		 name.  */
	      𐤀𐤌 (flag_plan9_extensions
		  && TYPE_NAME (TREE_TYPE (field)) != NULL_TREE
		  && TREE_CODE (TYPE_NAME (TREE_TYPE (field))) == TYPE_DECL
		  && (DECL_NAME (TYPE_NAME (TREE_TYPE (field)))
		      == component))
		اكسر;
	    }

	  𐤀𐤌 (DECL_NAME (field) == component)
	    اكسر;
	}

      𐤀𐤌 (field == NULL_TREE)
	أرجع NULL_TREE;
    }

  أرجع tree_cons (NULL_TREE, field, NULL_TREE);
}

/* Recursively append candidate IDENTIFIER_NODEs to CANDIDATES.  */

ساكن فراغ
lookup_field_fuzzy_find_candidates (tree type, tree component,
				    vec<tree> *candidates)
{
  tree field;
  لكل (field = TYPE_FIELDS (type); field; field = DECL_CHAIN (field))
    {
      𐤀𐤌 (DECL_NAME (field) == NULL_TREE
	  && RECORD_OR_UNION_TYPE_P (TREE_TYPE (field)))
	lookup_field_fuzzy_find_candidates (TREE_TYPE (field), component,
					    candidates);

      𐤀𐤌 (DECL_NAME (field))
	candidates->safe_push (DECL_NAME (field));
    }
}

/* Like "lookup_field", but find the closest matching IDENTIFIER_NODE,
   rather than returning a TREE_LIST for an exact match.  */

ساكن tree
lookup_field_fuzzy (tree type, tree component)
{
  gcc_assert (TREE_CODE (component) == IDENTIFIER_NODE);

  /* First, gather a list of candidates.  */
  auto_vec <tree> candidates;

  lookup_field_fuzzy_find_candidates (type, component,
				      &candidates);

  أرجع find_closest_identifier (component, &candidates);
}

/* Support function for build_component_ref's error-handling.

   Given DATUM_TYPE, and "DATUM.COMPONENT", where DATUM is *not* a
   struct or union, should we suggest "DATUM->COMPONENT" as a hint?  */

ساكن منطقي
should_suggest_deref_p (tree datum_type)
{
  /* We don't do it for Objective-C, since Objective-C 2.0 dot-syntax
     allows "." for ptrs; we could be handling a failed attempt
     to access a property.  */
  𐤀𐤌 (c_dialect_objc ())
    أرجع خطأ;

  /* Only suggest it for pointers...  */
  𐤀𐤌 (TREE_CODE (datum_type) != POINTER_TYPE)
    أرجع خطأ;

  /* ...to structs/unions.  */
  tree underlying_type = TREE_TYPE (datum_type);
  تعداد tree_code code = TREE_CODE (underlying_type);
  𐤀𐤌 (code == RECORD_TYPE || code == UNION_TYPE)
    أرجع true;
  وإلا
    أرجع خطأ;
}

/* Give a component ref REF, decide whether we should handle its counted_by
   attribute based on its context:
   Do not handle counted_by when in offsetof, typeof and alignof operator.  */

ساكن منطقي
handle_counted_by_p (tree ref)
{
  gcc_assert (TREE_CODE (ref) == COMPONENT_REF);
  tree datum = TREE_OPERAND (ref, 0);
  /* If the component_ref is build for a offsetof, i.e., the datum
     of the component_ref is a indirect_ref of null_pointer_node,
     we should not generate call to .ACCESS_WITH_SIZE.  */
  𐤀𐤌 (TREE_CODE (datum) == INDIRECT_REF
      && TREE_OPERAND (datum, 0) == null_pointer_node)
    أرجع خطأ;
  𐤀𐤌 (in_typeof || in_alignof)
    أرجع خطأ;
  أرجع true;
}

/* Given a component ref REF, if there is a counted_by attribute attached,
   issue error when the element_type is a structure or union including a
   flexible array member.  */

ساكن فراغ
check_counted_by_attribute (location_t loc, tree ref)
{
  tree subdatum = TREE_OPERAND (ref, 1);
  tree sub_type = TREE_TYPE (subdatum);

  𐤀𐤌 (!flexible_array_member_type_p (sub_type)
      && TREE_CODE (sub_type) != POINTER_TYPE)
    أرجع;

  tree element_type = TREE_TYPE (sub_type);

  tree attr_counted_by = lookup_attribute ("counted_by",
					   DECL_ATTRIBUTES (subdatum));
  𐤀𐤌 (attr_counted_by)
    {
      /* Issue error when the element_type is a structure or
	union including a flexible array member.  */
      𐤀𐤌 (RECORD_OR_UNION_TYPE_P (element_type)
	  && TYPE_INCLUDES_FLEXARRAY (element_type))
	{
	  error_at (loc,
		    "%<counted_by%> attribute is not allowed for a pointer to"
		    " structure or union with flexible array member");
	  أرجع;
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

ساكن tree
build_counted_by_ref (tree datum, tree subdatum,
		      tree *counted_by_type)
{
  tree sub_type = TREE_TYPE (subdatum);
  𐤀𐤌 (!flexible_array_member_type_p (sub_type)
      && TREE_CODE (sub_type) != POINTER_TYPE)
    أرجع NULL_TREE;

  tree attr_counted_by = lookup_attribute ("counted_by",
					   DECL_ATTRIBUTES (subdatum));
  𐤀𐤌 (!attr_counted_by)
    أرجع NULL_TREE;

  tree counted_by_ref = NULL_TREE;
  *counted_by_type = NULL_TREE;

  tree type = TREE_TYPE (datum);

  /* If the type of the containing structure is an anonymous struct/union,
     and this anonymous struct/union is not a root type, get the first
     outer named structure/union type.  */
  طالما (TREE_CODE (datum) == COMPONENT_REF
	 && c_type_tag (type) == NULL_TREE
	 && DECL_NAME (TREE_OPERAND (datum, 1)) == NULL_TREE)
    {
      datum = TREE_OPERAND (datum, 0);
      type = TREE_TYPE (datum);
    }

  tree field_id = TREE_VALUE (TREE_VALUE (attr_counted_by));
  tree counted_by_field = lookup_field (type, field_id);
  gcc_assert (counted_by_field);

  tree counted_by_subdatum;
  𐤐𐤏𐤋
    {
      counted_by_subdatum = TREE_VALUE (counted_by_field);
      /* Get the TYPE of the counted_by field.  */
      *counted_by_type = TREE_TYPE (counted_by_subdatum);

      counted_by_ref
	= build3 (COMPONENT_REF, TREE_TYPE (counted_by_subdatum),
		  datum, counted_by_subdatum, NULL_TREE);

      datum = counted_by_ref;
      counted_by_field = TREE_CHAIN (counted_by_field);
    }
  طالما (counted_by_field);

  counted_by_ref = build_fold_addr_expr (counted_by_ref);
  أرجع counted_by_ref;
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
ساكن tree
build_access_with_size_for_counted_by (location_t loc, tree ref,
				       tree counted_by_ref,
				       tree counted_by_type)
{
  gcc_assert (flexible_array_member_type_p (TREE_TYPE (ref))
	      || TREE_CODE (TREE_TYPE (ref)) == POINTER_TYPE);

  منطقي is_fam = flexible_array_member_type_p (TREE_TYPE (ref));

  /* The result type of the call is a pointer to the flexible array type;
     or is the original pointer type to the pointer field with counted_by.  */
  tree result_type = is_fam ? c_build_pointer_type (TREE_TYPE (ref))
		     : TREE_TYPE (ref);

  tree element_type = TREE_TYPE (TREE_TYPE (ref));
  tree element_size = VOID_TYPE_P (element_type)
		      ? size_one_node
		      : TYPE_SIZE_UNIT (element_type);
  𐤀𐤌 (element_size == NULL_TREE)
    أرجع ref;

  tree first_param = is_fam
		     ? c_fully_fold (array_to_pointer_conversion (loc, ref),
				     خطأ, عدم)
		     : c_fully_fold (ref, خطأ, عدم);
  tree second_param
    = c_fully_fold (counted_by_ref, خطأ, عدم);
  tree third_param = build_int_cst (c_build_pointer_type (counted_by_type), 0);

  tree call
    = build_call_expr_internal_loc (loc, IFN_ACCESS_WITH_SIZE,
				    result_type, 4,
				    first_param,
				    second_param,
				    third_param,
				    element_size);

  /* Wrap the call with an INDIRECT_REF with the flexible array type.  */
  𐤀𐤌 (is_fam)
    call = build1 (INDIRECT_REF, TREE_TYPE (ref), call);
  SET_EXPR_LOCATION (call, loc);
  أرجع call;
}

/* For the COMPONENT_REF ref, check whether it has a counted_by attribute,
   if so, wrap this COMPONENT_REF with the corresponding CALL to the
   function .ACCESS_WITH_SIZE.
   Otherwise, return the ref itself.  */

tree
handle_counted_by_for_component_ref (location_t loc, tree ref)
{
  gcc_assert (TREE_CODE (ref) == COMPONENT_REF);
  tree datum = TREE_OPERAND (ref, 0);
  tree subdatum = TREE_OPERAND (ref, 1);
  tree counted_by_type = NULL_TREE;

  𐤀𐤌 (!(flexible_array_member_type_p (TREE_TYPE (ref))
	|| TREE_CODE (TREE_TYPE (ref)) == POINTER_TYPE))
    أرجع ref;

  tree counted_by_ref = build_counted_by_ref (datum, subdatum,
					      &counted_by_type);
  𐤀𐤌 (counted_by_ref)
    ref = build_access_with_size_for_counted_by (loc, ref,
						 counted_by_ref,
						 counted_by_type);
  أرجع ref;
}

/* Make an expression to refer to the COMPONENT field of structure or
   union value DATUM.  COMPONENT is an IDENTIFIER_NODE.  LOC is the
   location of the COMPONENT_REF.  COMPONENT_LOC is the location
   of COMPONENT.  ARROW_LOC is the location of the first -> operand if
   it is from -> operator.
   If HANDLE_COUNTED_BY is true, check the counted_by attribute and generate
   a call to .ACCESS_WITH_SIZE.  Otherwise, ignore the attribute.  */

tree
build_component_ref (location_t loc, tree datum, tree component,
		     location_t component_loc, location_t arrow_loc)
{
  tree type = TREE_TYPE (datum);
  تعداد tree_code code = TREE_CODE (type);
  tree field = عدم;
  tree ref;
  منطقي datum_lvalue = lvalue_p (datum);

  𐤀𐤌 (!objc_is_public (datum, component))
    أرجع error_mark_node;

  /* Detect Objective-C property syntax object.property.  */
  𐤀𐤌 (c_dialect_objc ()
      && (ref = objc_maybe_build_component_ref (datum, component)))
    أرجع ref;

  /* See if there is a field or component with name COMPONENT.  */

  𐤀𐤌 (code == RECORD_TYPE || code == UNION_TYPE)
    {
      𐤀𐤌 (!COMPLETE_TYPE_P (type))
	{
	  c_incomplete_type_error (loc, NULL_TREE, type);
	  أرجع error_mark_node;
	}

      field = lookup_field (type, component);

      𐤀𐤌 (!field)
	{
	  tree guessed_id = lookup_field_fuzzy (type, component);
	  𐤀𐤌 (guessed_id)
	    {
	      /* Attempt to provide a fixit replacement hint, if
		 we have a valid range for the component.  */
	      location_t reported_loc
		= (component_loc != UNKNOWN_LOCATION) ? component_loc : loc;
	      gcc_rich_location rich_loc (reported_loc);
	      𐤀𐤌 (component_loc != UNKNOWN_LOCATION)
		rich_loc.add_fixit_misspelled_id (component_loc, guessed_id);
	      error_at (&rich_loc,
			"%qT has no member named %qE; did you mean %qE?",
			type, component, guessed_id);
	    }
	  وإلا
	    error_at (loc, "%qT has no member named %qE", type, component);
	  أرجع error_mark_node;
	}

      /* Accessing elements of atomic structures or unions is undefined
	 behavior (C11 6.5.2.3#5).  */
      𐤀𐤌 (TYPE_ATOMIC (type) && c_inhibit_evaluation_warnings == 0)
	{
	  𐤀𐤌 (code == RECORD_TYPE)
	    warning_at (loc, 0, "accessing a member %qE of an atomic "
			"structure %qE", component, datum);
	  وإلا
	    warning_at (loc, 0, "accessing a member %qE of an atomic "
			"union %qE", component, datum);
	}

      /* Chain the COMPONENT_REFs if necessary down to the FIELD.
	 This might be better solved in future the way the C++ front
	 end does it - by giving the anonymous entities each a
	 separate name and type, and then have build_component_ref
	 recursively call itself.  We can't do that here.  */
      𐤐𐤏𐤋
	{
	  tree subdatum = TREE_VALUE (field);
	  صحيح quals;
	  tree subtype;
	  منطقي use_datum_quals;

	  𐤀𐤌 (TREE_TYPE (subdatum) == error_mark_node)
	    أرجع error_mark_node;

	  /* If this is an rvalue, it does not have qualifiers in C
	     standard terms and we must avoid propagating such
	     qualifiers down to a non-lvalue array that is then
	     converted to a pointer.  */
	  use_datum_quals = (datum_lvalue
			     || TREE_CODE (TREE_TYPE (subdatum)) != ARRAY_TYPE);

	  quals = TYPE_QUALS (strip_array_types (TREE_TYPE (subdatum)));
	  𐤀𐤌 (use_datum_quals)
	    quals |= TYPE_QUALS (TREE_TYPE (datum));
	  subtype = c_build_qualified_type (TREE_TYPE (subdatum), quals);

	  ref = build3 (COMPONENT_REF, subtype, datum, subdatum,
			NULL_TREE);
	  SET_EXPR_LOCATION (ref, loc);

	  check_counted_by_attribute (loc, ref);

	  𐤀𐤌 (TREE_READONLY (subdatum)
	      || (use_datum_quals && TREE_READONLY (datum)))
	    TREE_READONLY (ref) = 1;
	  𐤀𐤌 (TREE_THIS_VOLATILE (subdatum)
	      || (use_datum_quals && TREE_THIS_VOLATILE (datum)))
	    TREE_THIS_VOLATILE (ref) = 1;

	  𐤀𐤌 (TREE_UNAVAILABLE (subdatum))
	    error_unavailable_use (subdatum, NULL_TREE);
	  وإلا 𐤀𐤌 (TREE_DEPRECATED (subdatum))
	    warn_deprecated_use (subdatum, NULL_TREE);

	  datum = ref;

	  field = TREE_CHAIN (field);
	}
      طالما (field);

      أرجع ref;
    }
  وإلا 𐤀𐤌 (should_suggest_deref_p (type))
    {
      /* Special-case the error message for "ptr.field" for the case
	 where the user has confused "." vs "->".  */
      rich_location richloc (line_table, loc);
      𐤀𐤌 (INDIRECT_REF_P (datum) && arrow_loc != UNKNOWN_LOCATION)
	{
	  richloc.add_fixit_insert_before (arrow_loc, "(*");
	  richloc.add_fixit_insert_after (arrow_loc, ")");
	  error_at (&richloc,
		    "%qE is a pointer to pointer; did you mean to dereference "
		    "it before applying %<->%> to it?",
		    TREE_OPERAND (datum, 0));
	}
      وإلا
	{
	  /* "loc" should be the "." token.  */
	  richloc.add_fixit_replace ("->");
	  error_at (&richloc,
		    "%qE is a pointer; did you mean to use %<->%>?",
		    datum);
	}
      أرجع error_mark_node;
    }
  وإلا 𐤀𐤌 (code != ERROR_MARK)
    error_at (loc,
	      "request for member %qE in something not a structure or union",
	      component);

  أرجع error_mark_node;
}

/* Given an expression PTR for a pointer, return an expression
   for the value pointed to.
   ERRORSTRING is the name of the operator to appear in error messages.

   LOC is the location to use for the generated tree.  */

tree
build_indirect_ref (location_t loc, tree ptr, ref_operator errstring)
{
  tree pointer = default_conversion (ptr);
  tree type = TREE_TYPE (pointer);
  tree ref;

  𐤀𐤌 (TREE_CODE (type) == POINTER_TYPE)
    {
      𐤀𐤌 (CONVERT_EXPR_P (pointer)
          || TREE_CODE (pointer) == VIEW_CONVERT_EXPR)
	{
	  /* If a warning is issued, mark it to avoid duplicates from
	     the backend.  This only needs to be done at
	     warn_strict_aliasing > 2.  */
	  𐤀𐤌 (warn_strict_aliasing > 2)
	    𐤀𐤌 (strict_aliasing_warning (EXPR_LOCATION (pointer),
					 type, TREE_OPERAND (pointer, 0)))
	      suppress_warning (pointer, OPT_Wstrict_aliasing_);
	}

      𐤀𐤌 (TREE_CODE (pointer) == ADDR_EXPR
	  && (TREE_TYPE (TREE_OPERAND (pointer, 0))
	      == TREE_TYPE (type)))
	{
	  ref = TREE_OPERAND (pointer, 0);
	  protected_set_expr_location (ref, loc);
	  أرجع ref;
	}
      وإلا
	{
	  tree t = TREE_TYPE (type);

	  ref = build1 (INDIRECT_REF, t, pointer);

	  𐤀𐤌 (VOID_TYPE_P (t) && c_inhibit_evaluation_warnings == 0)
	    warning_at (loc, 0, "dereferencing %<void *%> pointer");

	  /* We *must* set TREE_READONLY when dereferencing a pointer to const,
	     so that we get the proper error message if the result is used
	     to assign to.  Also, &* is supposed to be a no-op.
	     And ANSI C seems to specify that the type of the result
	     should be the const type.  */
	  /* A de-reference of a pointer to const is not a const.  It is valid
	     to change it via some other pointer.  */
	  TREE_READONLY (ref) = TYPE_READONLY (t);
	  TREE_SIDE_EFFECTS (ref)
	    = TYPE_VOLATILE (t) || TREE_SIDE_EFFECTS (pointer);
	  TREE_THIS_VOLATILE (ref) = TYPE_VOLATILE (t);
	  protected_set_expr_location (ref, loc);
	  أرجع ref;
	}
    }
  وإلا 𐤀𐤌 (TREE_CODE (pointer) != ERROR_MARK)
    invalid_indirection_error (loc, type, errstring);

  أرجع error_mark_node;
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

tree
build_array_ref (location_t loc, tree array, tree index)
{
  tree ret;
  منطقي swapped = خطأ;
  𐤀𐤌 (TREE_TYPE (array) == error_mark_node
      || TREE_TYPE (index) == error_mark_node)
    أرجع error_mark_node;

  𐤀𐤌 (TREE_CODE (TREE_TYPE (array)) != ARRAY_TYPE
      && TREE_CODE (TREE_TYPE (array)) != POINTER_TYPE
      /* Allow vector[index] but not index[vector].  */
      && !gnu_vector_type_p (TREE_TYPE (array)))
    {
      𐤀𐤌 (TREE_CODE (TREE_TYPE (index)) != ARRAY_TYPE
	  && TREE_CODE (TREE_TYPE (index)) != POINTER_TYPE)
	{
          error_at (loc,
            "subscripted value is neither array nor pointer nor vector");

	  أرجع error_mark_node;
	}
      std::swap (array, index);
      swapped = true;
    }

  𐤀𐤌 (!INTEGRAL_TYPE_P (TREE_TYPE (index)))
    {
      error_at (loc, "array subscript is not an integer");
      أرجع error_mark_node;
    }

  𐤀𐤌 (TREE_CODE (TREE_TYPE (TREE_TYPE (array))) == FUNCTION_TYPE)
    {
      error_at (loc, "subscripted value is pointer to function");
      أرجع error_mark_node;
    }

  /* ??? Existing practice has been to warn only when the char
     index is syntactically the index, not for char[array].  */
  𐤀𐤌 (!swapped)
     warn_array_subscript_with_type_char (loc, index);

  /* Apply default promotions *after* noticing character types.  */
  index = default_conversion (index);
  𐤀𐤌 (index == error_mark_node)
    أرجع error_mark_node;

  gcc_assert (TREE_CODE (TREE_TYPE (index)) == INTEGER_TYPE
	      || TREE_CODE (TREE_TYPE (index)) == BITINT_TYPE);

  منطقي was_vector = VECTOR_TYPE_P (TREE_TYPE (array));
  منطقي non_lvalue = convert_vector_to_array_for_subscript (loc, &array, index);

  /* We only generate a call to .ACCESS_WITH_SIZE when it is a read.  */
  𐤀𐤌 (TREE_CODE (array) == COMPONENT_REF
      && handle_counted_by_p (array))
    array = handle_counted_by_for_component_ref (loc, array);

  𐤀𐤌 (TREE_CODE (TREE_TYPE (array)) == ARRAY_TYPE)
    {
      tree rval, type;

      /* An array that is indexed by a non-constant
	 cannot be stored in a register; we must be able to do
	 address arithmetic on its address.
	 Likewise an array of elements of variable size.  */
      𐤀𐤌 (TREE_CODE (index) != INTEGER_CST
	  || (COMPLETE_TYPE_P (TREE_TYPE (TREE_TYPE (array)))
	      && TREE_CODE (TYPE_SIZE (TREE_TYPE (TREE_TYPE (array)))) != INTEGER_CST))
	{
	  𐤀𐤌 (!c_mark_addressable (array, true, true))
	    أرجع error_mark_node;
	}
      /* An array that is indexed by a constant value which is not within
	 the array bounds cannot be stored in a register either; because we
	 would get a crash in store_bit_field/extract_bit_field when trying
	 to access a non-existent part of the register.  */
      𐤀𐤌 (TREE_CODE (index) == INTEGER_CST
	  && TYPE_DOMAIN (TREE_TYPE (array))
	  && !int_fits_type_p (index, TYPE_DOMAIN (TREE_TYPE (array))))
	{
	  𐤀𐤌 (!c_mark_addressable (array, خطأ, true))
	    أرجع error_mark_node;
	  /* ISO C2Y disallows a negative integer constant expression index
	     when array subscripting has an operand of array type.  */
	  𐤀𐤌 (flag_isoc2y
	      && !TREE_OVERFLOW (index)
	      && tree_int_cst_sgn (index) < 0)
	    error_at (loc, "array subscript is negative");
	}

      𐤀𐤌 ((pedantic || warn_c90_c99_compat || warn_c23_c2y_compat)
	  && ! was_vector)
	{
	  tree foo = array;
	  طالما (TREE_CODE (foo) == COMPONENT_REF)
	    foo = TREE_OPERAND (foo, 0);
	  𐤀𐤌 ((VAR_P (foo) && C_DECL_REGISTER (foo))
	      || (TREE_CODE (foo) == COMPOUND_LITERAL_EXPR
		  && C_DECL_REGISTER (COMPOUND_LITERAL_EXPR_DECL (foo))))
	    pedwarn_c23 (loc, OPT_Wpedantic,
			 "ISO C forbids subscripting %<register%> array "
			 "before C2Y");
	  وإلا 𐤀𐤌 (!lvalue_p (foo))
	    pedwarn_c90 (loc, OPT_Wpedantic,
			 "ISO C90 forbids subscripting non-lvalue "
			 "array");
	}

      𐤀𐤌 (TREE_CODE (TREE_TYPE (index)) == BITINT_TYPE
	  && TYPE_PRECISION (TREE_TYPE (index)) > TYPE_PRECISION (sizetype))
	index = fold_convert (sizetype, index);

      type = TREE_TYPE (TREE_TYPE (array));
      rval = build4 (ARRAY_REF, type, array, index, NULL_TREE, NULL_TREE);
      /* Array ref is const/volatile if the array elements are
	 or if the array is.  */
      TREE_READONLY (rval)
	|= (TYPE_READONLY (TREE_TYPE (TREE_TYPE (array)))
	    | TREE_READONLY (array));
      TREE_SIDE_EFFECTS (rval)
	|= (TYPE_VOLATILE (TREE_TYPE (TREE_TYPE (array)))
	    | TREE_SIDE_EFFECTS (array));
      TREE_THIS_VOLATILE (rval)
	|= (TYPE_VOLATILE (TREE_TYPE (TREE_TYPE (array)))
	    /* This was added by rms on 16 Nov 91.
	       It fixes  vol struct foo *a;  a->elts[1]
	       in an inline function.
	       Hope it doesn't break something else.  */
	    | TREE_THIS_VOLATILE (array));
      ret = require_complete_type (loc, rval);
      protected_set_expr_location (ret, loc);
      𐤀𐤌 (non_lvalue)
	ret = non_lvalue_loc (loc, ret);
      أرجع ret;
    }
  وإلا
    {
      tree ar = default_conversion (array);

      𐤀𐤌 (ar == error_mark_node)
	أرجع ar;

      gcc_assert (TREE_CODE (TREE_TYPE (ar)) == POINTER_TYPE);
      gcc_assert (TREE_CODE (TREE_TYPE (TREE_TYPE (ar))) != FUNCTION_TYPE);

      ret = build_indirect_ref (loc, build_binary_op (loc, PLUS_EXPR, ar,
						      index, خطأ),
				RO_ARRAY_INDEXING);
      𐤀𐤌 (non_lvalue)
	ret = non_lvalue_loc (loc, ret);
      أرجع ret;
    }
}

/* Build an OpenMP array section reference, creating an exact type for the
   resulting expression based on the element type and bounds if possible.  If
   we have variable bounds, create an incomplete array type for the result
   instead.  */

tree
build_omp_array_section (location_t loc, tree array, tree index, tree length)
{
  tree type = TREE_TYPE (array);
  gcc_assert (type);

  tree sectype, eltype = TREE_TYPE (type);

  /* It's not an array or pointer type.  Just reuse the type of the original
     expression as the type of the array section (an error will be raised
     anyway, later).  */
  𐤀𐤌 (eltype == NULL_TREE || error_operand_p (eltype))
    sectype = TREE_TYPE (array);
  وإلا
    {
      tree idxtype = NULL_TREE;

      𐤀𐤌 (index != NULL_TREE
	  && length != NULL_TREE
	  && INTEGRAL_TYPE_P (TREE_TYPE (index))
	  && INTEGRAL_TYPE_P (TREE_TYPE (length)))
	{
	  tree low = fold_convert (sizetype, index);
	  tree high = fold_convert (sizetype, length);
	  high = size_binop (PLUS_EXPR, low, high);
	  high = size_binop (MINUS_EXPR, high, size_one_node);
	  idxtype = build_range_type (sizetype, low, high);
	}
      وإلا 𐤀𐤌 ((index == NULL_TREE || integer_zerop (index))
	       && length != NULL_TREE
	       && INTEGRAL_TYPE_P (TREE_TYPE (length)))
	idxtype = build_index_type (length);

      gcc_assert (!error_operand_p (idxtype));

      sectype = c_build_array_type (eltype, idxtype);
    }

  أرجع build3_loc (loc, OMP_ARRAY_SECTION, sectype, array, index, length);
}


/* Record that REF is used.  This is relevant for undeclared static
   function and declarations referenced from a non-local context.
   ADDRESS indicates whether the address is taken.  */

فراغ
mark_decl_used (tree ref, منطقي address)
{
  𐤀𐤌 (!ref || !DECL_P (ref) || in_alignof)
    أرجع;

  /* Non-file-scope and non-local reference in nested function.  */
  منطقي nonloc_p = current_function_decl && DECL_CONTEXT (ref)
		  && DECL_CONTEXT (current_function_decl)
		  && DECL_CONTEXT (ref) != current_function_decl;

  /* An undeclared static function.  */
  منطقي static_p = TREE_CODE (ref) == FUNCTION_DECL
		  && DECL_INITIAL (ref) == NULL_TREE
		  && DECL_EXTERNAL (ref)
		  && !TREE_PUBLIC (ref);

  𐤀𐤌 (!static_p && !nonloc_p)
    أرجع;

  /* If we may be in an unevaluated context, delay the decision.  */
  𐤀𐤌 (in_sizeof || in_typeof || in_countof || in_generic)
    أرجع record_maybe_used_decl (ref, address);

  𐤀𐤌 (static_p)
    C_DECL_USED (ref) = 1;

  𐤀𐤌 (nonloc_p && (VAR_OR_FUNCTION_DECL_P (ref)
		   || TREE_CODE (ref) == PARM_DECL))
    DECL_NONLOCAL (ref) = 1;

  /* Nothing to do anymore.  */
  𐤀𐤌 (!nonloc_p || C_FUNC_NONLOCAL_CONTEXT (current_function_decl))
    أرجع;

  /* Filter out the cases where referencing a non-local variable does not
     require a non-local context passed via the static chain.  */
  𐤀𐤌 (!c_type_variably_modified_p (TREE_TYPE (ref)))
    بدل (TREE_CODE (ref))
      {
      حالة FUNCTION_DECL:
	/* Use of another local function that requires no context is ok.  */
	𐤀𐤌 (!C_FUNC_NONLOCAL_CONTEXT (ref) && DECL_INITIAL (ref))
	  أرجع;
	اكسر;
      حالة VAR_DECL:
	/* Static variables and constexpr are ok, but for the later only
	   when the address is not taken.  */
	𐤀𐤌 (TREE_STATIC (ref) || (C_DECL_DECLARED_CONSTEXPR (ref) && !address))
	  أرجع;
	اكسر;
      حالة TYPE_DECL:
	/* A typedef is ok when not for a variably-modified type. */
	أرجع;
      حالة CONST_DECL:
	/* An enumeration constant is ok. */
	أرجع;
      حالة PARM_DECL:
	اكسر;
      حالة LABEL_DECL:
	اكسر;
      افتراضي:
	gcc_unreachable ();
    }

  /* Mark all parent functions up to the nesting level of the variable as
     as needing the non-local context.  */
  لكل (tree cont = current_function_decl; cont; cont = DECL_CONTEXT (cont))
    {
      𐤀𐤌 (cont == DECL_CONTEXT (ref))
	اكسر;

      /* There should not be any other type of context used for function
	 except TRANSLATION_UNIT_DECL which we should be able to reach.  */
      gcc_checking_assert (TREE_CODE (cont) == FUNCTION_DECL);

      𐤀𐤌 (TREE_CODE (cont) == FUNCTION_DECL)
	C_FUNC_NONLOCAL_CONTEXT (cont) = 1;
    }
}


/* Build an external reference to identifier ID.  FUN indicates
   whether this will be used for a function call.  LOC is the source
   location of the identifier.  This sets *TYPE to the type of the
   identifier, which is not the same as the type of the returned value
   for CONST_DECLs defined as enum constants.  If the type of the
   identifier is not available, *TYPE is set to NULL.  */
tree
build_external_ref (location_t loc, tree id, منطقي fun, tree *type)
{
  tree ref;
  tree decl = lookup_name (id);

  /* In Objective-C, an instance variable (ivar) may be preferred to
     whatever lookup_name() found.  */
  decl = objc_lookup_ivar (decl, id);

  *type = عدم;
  𐤀𐤌 (decl && decl != error_mark_node)
    {
      ref = decl;
      *type = TREE_TYPE (ref);
      𐤀𐤌 (DECL_P (decl) && C_DECL_UNDERSPECIFIED (decl))
	error_at (loc, "underspecified %qD referenced in its initializer",
		  decl);
    }
  وإلا 𐤀𐤌 (fun)
    /* Implicit function declaration.  */
    ref = implicitly_declare (loc, id);
  وإلا 𐤀𐤌 (decl == error_mark_node)
    /* Don't complain about something that's already been
       complained about.  */
    أرجع error_mark_node;
  وإلا
    {
      undeclared_variable (loc, id);
      أرجع error_mark_node;
    }

  /* For an OpenMP map clause, we can get better diagnostics for decls with
     unmappable types if we return the decl with an error_mark_node type,
     rather than returning error_mark_node for the decl itself.  */
  𐤀𐤌 (TREE_TYPE (ref) == error_mark_node
      && !c_omp_array_section_p)
    أرجع error_mark_node;

  𐤀𐤌 (TREE_UNAVAILABLE (ref))
    error_unavailable_use (ref, NULL_TREE);
  وإلا 𐤀𐤌 (TREE_DEPRECATED (ref))
    warn_deprecated_use (ref, NULL_TREE);

  /* Recursive call does not count as usage.  */
  𐤀𐤌 (ref != current_function_decl)
    {
      TREE_USED (ref) = 1;
    }

  mark_decl_used (ref, خطأ);

  𐤀𐤌 (TREE_CODE (ref) == CONST_DECL)
    {
      used_types_insert (TREE_TYPE (ref));

      𐤀𐤌 (warn_cxx_compat
	  && TREE_CODE (TREE_TYPE (ref)) == ENUMERAL_TYPE
	  && C_TYPE_DEFINED_IN_STRUCT (TREE_TYPE (ref)))
	{
	  warning_at (loc, OPT_Wc___compat,
		      "enum constant defined in struct or union "
		      "is not visible in C++");
	  inform (DECL_SOURCE_LOCATION (ref), "enum constant defined here");
	}

      ref = DECL_INITIAL (ref);
      TREE_CONSTANT (ref) = 1;
    }
  /* C99 6.7.4p3: An inline definition of a function with external
     linkage ... shall not contain a reference to an identifier with
     internal linkage.  */
  وإلا 𐤀𐤌 (current_function_decl != NULL_TREE
	   && DECL_DECLARED_INLINE_P (current_function_decl)
	   && DECL_EXTERNAL (current_function_decl)
	   && VAR_OR_FUNCTION_DECL_P (ref)
	   && (!VAR_P (ref) || TREE_STATIC (ref))
	   && ! TREE_PUBLIC (ref)
	   && DECL_CONTEXT (ref) != current_function_decl)
    record_inline_static (loc, current_function_decl, ref,
			  csi_internal);

  أرجع ref;
}

ساكن بنية maybe_used_decl *maybe_used_decls;

/* Record that DECL, a reference seen inside sizeof or typeof or _Countof or
   _Generic, might be used if the operand of sizeof is a VLA type or the
   operand of typeof is a variably modified type or the operand of _Countof has
   a variable number of elements or the operand of _Generic is the one selected
   as the result.  */

ساكن فراغ
record_maybe_used_decl (tree decl, منطقي address)
{
  بنية maybe_used_decl *t = XOBNEW (&parser_obstack, بنية maybe_used_decl);
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

فراغ
pop_maybe_used (منطقي used)
{
  بنية maybe_used_decl *p = maybe_used_decls;
  صحيح cur_level = in_sizeof + in_typeof + in_countof + in_generic;
  طالما (p && p->level > cur_level)
    {
      𐤀𐤌 (used)
	{
	  𐤀𐤌 (cur_level == 0)
	    mark_decl_used (p->decl, p->address);
	  وإلا
	    p->level = cur_level;
	}
      p = p->next;
    }
  𐤀𐤌 (!used || cur_level == 0)
    maybe_used_decls = p;
}

/* Pop the stack of decls possibly used inside sizeof or typeof or _Countof or
   _Generic, without acting on them, and return the pointer to the previous top
   of the stack.  This for use at the end of a default generic association when
   it is not yet known whether the expression is used.  If it later turns out
   the expression is used (or treated as used before C23), restore_maybe_used
   should be called on the return value followed by pop_maybe_used (true);
   otherwise, the return value can be discarded.  */

بنية maybe_used_decl *
save_maybe_used ()
{
  بنية maybe_used_decl *p = maybe_used_decls, *orig = p;
  صحيح cur_level = in_sizeof + in_typeof + in_countof + in_generic;
  طالما (p && p->level > cur_level)
    p = p->next;
  maybe_used_decls = p;
  أرجع orig;
}

/* Restore the stack of decls possibly used inside sizeof or typeof or _Countof
   or _Generic returned by save_maybe_used.  It is required that the stack is
   at exactly the point where it was left by save_maybe_used.  */

فراغ
restore_maybe_used (بنية maybe_used_decl *stack)
{
  maybe_used_decls = stack;
}

/* Return the result of sizeof applied to EXPR.  */

بنية c_expr
c_expr_sizeof_expr (location_t loc, بنية c_expr expr)
{
  بنية c_expr ret;
  𐤀𐤌 (expr.value == error_mark_node)
    {
      ret.value = error_mark_node;
      ret.original_code = ERROR_MARK;
      ret.original_type = عدم;
      ret.m_decimal = 0;
      pop_maybe_used (خطأ);
    }
  وإلا
    {
      منطقي expr_const_operands = true;

      𐤀𐤌 (TREE_CODE (expr.value) == PARM_DECL
	  && C_ARRAY_PARAMETER (expr.value))
	{
	  auto_diagnostic_group d;
	  𐤀𐤌 (warning_at (loc, OPT_Wsizeof_array_argument,
			  "%<sizeof%> on array function parameter %qE will "
			  "return size of %qT", expr.value,
			  TREE_TYPE (expr.value)))
	    inform (DECL_SOURCE_LOCATION (expr.value), "declared here");
	}
      tree folded_expr = c_fully_fold (expr.value, require_constant_value,
				       &expr_const_operands);
      ret.value = c_sizeof (loc, TREE_TYPE (folded_expr));
      c_last_sizeof_arg = expr.value;
      c_last_sizeof_loc = loc;
      ret.original_code = SIZEOF_EXPR;
      ret.original_type = عدم;
      ret.m_decimal = 0;
      𐤀𐤌 (C_TYPE_VARIABLE_SIZE (TREE_TYPE (folded_expr)))
	{
	  /* sizeof is evaluated when given a vla (C99 6.5.3.4p2).  */
	  ret.value = build2 (C_MAYBE_CONST_EXPR, TREE_TYPE (ret.value),
			      folded_expr, ret.value);
	  C_MAYBE_CONST_EXPR_NON_CONST (ret.value) = !expr_const_operands;
	  SET_EXPR_LOCATION (ret.value, loc);
	}
      pop_maybe_used (C_TYPE_VARIABLE_SIZE (TREE_TYPE (folded_expr)));
    }
  أرجع ret;
}

/* Return the result of sizeof applied to T, a structure for the type
   name passed to sizeof (rather than the type itself).  LOC is the
   location of the original expression.  */

بنية c_expr
c_expr_sizeof_type (location_t loc, بنية c_type_name *t)
{
  tree type;
  بنية c_expr ret;
  tree type_expr = NULL_TREE;
  منطقي type_expr_const = true;
  type = groktypename (t, &type_expr, &type_expr_const);
  ret.value = c_sizeof (loc, type);
  c_last_sizeof_arg = type;
  c_last_sizeof_loc = loc;
  ret.original_code = SIZEOF_EXPR;
  ret.original_type = عدم;
  ret.m_decimal = 0;
  𐤀𐤌 (type == error_mark_node)
    {
      ret.value = error_mark_node;
      ret.original_code = ERROR_MARK;
    }
  وإلا
  𐤀𐤌 ((type_expr || TREE_CODE (ret.value) == INTEGER_CST)
      && C_TYPE_VARIABLE_SIZE (type))
    {
      /* If the type is a [*] array, it is a VLA but is represented as
	 having a size of zero.  In such a case we must ensure that
	 the result of sizeof does not get folded to a constant by
	 c_fully_fold, because if the size is evaluated the result is
	 not constant and so constraints on zero or negative size
	 arrays must not be applied when this sizeof call is inside
	 another array declarator.  */
      𐤀𐤌 (!type_expr)
	type_expr = integer_zero_node;
      ret.value = build2 (C_MAYBE_CONST_EXPR, TREE_TYPE (ret.value),
			  type_expr, ret.value);
      C_MAYBE_CONST_EXPR_NON_CONST (ret.value) = !type_expr_const;
    }
  pop_maybe_used (type != error_mark_node
		  ? C_TYPE_VARIABLE_SIZE (type) : خطأ);
  أرجع ret;
}

ساكن منطقي
top_array_vla_p (const_tree type)
{
  𐤀𐤌 (TREE_CODE (type) != ARRAY_TYPE)
    أرجع خطأ;

  tree d = TYPE_DOMAIN (type);

  𐤀𐤌 (!d)
    أرجع خطأ;
  𐤀𐤌 (!TYPE_MAX_VALUE (d))
    أرجع خطأ;

  أرجع TREE_CODE (TYPE_MAX_VALUE (d)) != INTEGER_CST
	 || TREE_CODE (TYPE_MIN_VALUE (d)) != INTEGER_CST;
}

/* Return the result of countof applied to EXPR.  */

بنية c_expr
c_expr_countof_expr (location_t loc, بنية c_expr expr)
{
  بنية c_expr ret;
  𐤀𐤌 (expr.value == error_mark_node)
    {
      ret.value = error_mark_node;
      ret.original_code = ERROR_MARK;
      ret.original_type = عدم;
      ret.m_decimal = 0;
      pop_maybe_used (خطأ);
    }
  وإلا
    {
      منطقي expr_const_operands = true;

      tree folded_expr = c_fully_fold (expr.value, require_constant_value,
				       &expr_const_operands);
      ret.value = c_countof_type (loc, TREE_TYPE (folded_expr));
      c_last_sizeof_arg = expr.value;
      c_last_sizeof_loc = loc;
      ret.original_code = COUNTOF_EXPR;
      ret.original_type = عدم;
      ret.m_decimal = 0;
      𐤀𐤌 (top_array_vla_p (TREE_TYPE (folded_expr)))
	{
	  /* countof is evaluated when given a vla.  */
	  ret.value = build2 (C_MAYBE_CONST_EXPR, TREE_TYPE (ret.value),
			      folded_expr, ret.value);
	  C_MAYBE_CONST_EXPR_NON_CONST (ret.value) = !expr_const_operands;
	  SET_EXPR_LOCATION (ret.value, loc);
	}
      pop_maybe_used (top_array_vla_p (TREE_TYPE (folded_expr)));
    }
  أرجع ret;
}

/* Return the result of countof applied to T, a structure for the type
   name passed to countof (rather than the type itself).  LOC is the
   location of the original expression.  */

بنية c_expr
c_expr_countof_type (location_t loc, بنية c_type_name *t)
{
  tree type;
  بنية c_expr ret;
  tree type_expr = NULL_TREE;
  منطقي type_expr_const = true;
  type = groktypename (t, &type_expr, &type_expr_const);
  ret.value = c_countof_type (loc, type);
  c_last_sizeof_arg = type;
  c_last_sizeof_loc = loc;
  ret.original_code = COUNTOF_EXPR;
  ret.original_type = عدم;
  ret.m_decimal = 0;
  𐤀𐤌 (type == error_mark_node)
    {
      ret.value = error_mark_node;
      ret.original_code = ERROR_MARK;
    }
  وإلا
  𐤀𐤌 ((type_expr || TREE_CODE (ret.value) == INTEGER_CST)
      && top_array_vla_p (type))
    {
      /* If the type is a [*] array, it is a VLA but is represented as
	 having a size of zero.  In such a case we must ensure that
	 the result of countof does not get folded to a constant by
	 c_fully_fold, because if the number of elements is evaluated
	 the result is not constant and so
	 constraints on zero or negative size arrays must not be applied
	 when this countof call is inside another array declarator.  */
      𐤀𐤌 (!type_expr)
	type_expr = integer_zero_node;
      ret.value = build2 (C_MAYBE_CONST_EXPR, TREE_TYPE (ret.value),
			  type_expr, ret.value);
      C_MAYBE_CONST_EXPR_NON_CONST (ret.value) = !type_expr_const;
    }
  pop_maybe_used (type != error_mark_node ? top_array_vla_p (type) : خطأ);
  أرجع ret;
}

/* Return the result of maxof applied to T, a structure for the type
   name passed to maxof (rather than the type itself).  LOC is the
   location of the original expression.  */

بنية c_expr
c_expr_maxof_type (location_t loc, بنية c_type_name *t)
{
  tree type;
  بنية c_expr ret;
  tree type_expr = NULL_TREE;
  منطقي type_expr_const = true;
  type = groktypename (t, &type_expr, &type_expr_const);
  ret.value = c_maxof_type (loc, type);
  c_last_sizeof_arg = type;
  c_last_sizeof_loc = loc;
  ret.original_code = MAXOF_EXPR;
  ret.original_type = عدم;
  ret.m_decimal = 0;
  𐤀𐤌 (type == error_mark_node)
    {
      ret.value = error_mark_node;
      ret.original_code = ERROR_MARK;
    }
  pop_maybe_used (type != error_mark_node);
  أرجع ret;
}

/* Return the result of minof applied to T, a structure for the type
   name passed to minof (rather than the type itself).  LOC is the
   location of the original expression.  */

بنية c_expr
c_expr_minof_type (location_t loc, بنية c_type_name *t)
{
  tree type;
  بنية c_expr ret;
  tree type_expr = NULL_TREE;
  منطقي type_expr_const = true;
  type = groktypename (t, &type_expr, &type_expr_const);
  ret.value = c_minof_type (loc, type);
  c_last_sizeof_arg = type;
  c_last_sizeof_loc = loc;
  ret.original_code = MINOF_EXPR;
  ret.original_type = عدم;
  ret.m_decimal = 0;
  𐤀𐤌 (type == error_mark_node)
    {
      ret.value = error_mark_node;
      ret.original_code = ERROR_MARK;
    }
  pop_maybe_used (type != error_mark_node);
  أرجع ret;
}

/* Build a function call to function FUNCTION with parameters PARAMS.
   The function call is at LOC.
   PARAMS is a list--a chain of TREE_LIST nodes--in which the
   TREE_VALUE of each node is a parameter-expression.
   FUNCTION's data type may be a function type or a pointer-to-function.  */

tree
build_function_call (location_t loc, tree function, tree params)
{
  vec<tree, va_gc> *v;
  tree ret;

  vec_alloc (v, list_length (params));
  لكل (; params; params = TREE_CHAIN (params))
    v->quick_push (TREE_VALUE (params));
  ret = c_build_function_call_vec (loc, vNULL, function, v, عدم);
  vec_free (v);
  أرجع ret;
}

/* Give a note about the location of the declaration of DECL,
   or, failing that, a pertinent declaration for FUNCTION_EXPR.  */

ساكن فراغ
inform_declaration (tree decl, tree function_expr)
{
  𐤀𐤌 (decl && (TREE_CODE (decl) != FUNCTION_DECL
	       || !DECL_IS_UNDECLARED_BUILTIN (decl)))
    inform (DECL_SOURCE_LOCATION (decl), "declared here");
  وإلا 𐤀𐤌 (function_expr)
    بدل (TREE_CODE (function_expr))
      {
      افتراضي:
	اكسر;
      حالة COMPONENT_REF:
	/* Show the decl of the pertinent field (e.g. for callback
	   fields in a struct.  */
	{
	  tree field_decl = TREE_OPERAND (function_expr, 1);
	  𐤀𐤌 (location_t loc = DECL_SOURCE_LOCATION (field_decl))
	    inform (loc, "declared here");
	}
	اكسر;
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

tree
build_function_call_vec (location_t loc, vec<location_t> arg_loc,
			 tree function, vec<tree, va_gc> *params,
			 vec<tree, va_gc> *origtypes, tree orig_fundecl)
{
  tree fntype, fundecl = NULL_TREE;
  tree name = NULL_TREE, result;
  tree tem;
  صحيح nargs;
  tree *argarray;


  /* Strip NON_LVALUE_EXPRs, etc., since we aren't using as an lvalue.  */
  STRIP_TYPE_NOPS (function);

  /* Convert anything with function type to a pointer-to-function.  */
  𐤀𐤌 (TREE_CODE (function) == FUNCTION_DECL)
    {
      name = DECL_NAME (function);

      𐤀𐤌 (flag_tm)
	tm_malloc_replacement (function);
      fundecl = function;
      𐤀𐤌 (!orig_fundecl)
	orig_fundecl = fundecl;
      /* Atomic functions have type checking/casting already done.  They are
	 often rewritten and don't match the original parameter list.  */
      𐤀𐤌 (name && startswith (IDENTIFIER_POINTER (name), "__atomic_"))
        origtypes = عدم;
    }
  𐤀𐤌 (TREE_CODE (TREE_TYPE (function)) == FUNCTION_TYPE)
    function = function_to_pointer_conversion (loc, function);

  /* For Objective-C, convert any calls via a cast to OBJC_TYPE_REF
     expressions, like those used for ObjC messenger dispatches.  */
  𐤀𐤌 (params && !params->is_empty ())
    function = objc_rewrite_function_call (function, (*params)[0]);

  function = c_fully_fold (function, خطأ, عدم);

  fntype = TREE_TYPE (function);

  𐤀𐤌 (TREE_CODE (fntype) == ERROR_MARK)
    أرجع error_mark_node;

  𐤀𐤌 (!(TREE_CODE (fntype) == POINTER_TYPE
	&& TREE_CODE (TREE_TYPE (fntype)) == FUNCTION_TYPE))
    {
      𐤀𐤌 (!flag_diagnostics_show_caret && !STATEMENT_CLASS_P (function))
	error_at (loc,
		  "called object %qE is not a function or function pointer",
		  function);
      وإلا 𐤀𐤌 (DECL_P (function))
	{
	  auto_diagnostic_group d;
	  error_at (loc,
		    "called object %qD is not a function or function pointer",
		    function);
	  inform_declaration (function, NULL_TREE);
	}
      وإلا
	error_at (loc,
		  "called object is not a function or function pointer");
      أرجع error_mark_node;
    }

  𐤀𐤌 (fundecl && TREE_THIS_VOLATILE (fundecl))
    current_function_returns_abnormally = 1;

  /* fntype now gets the type of function pointed to.  */
  fntype = TREE_TYPE (fntype);
  tree return_type = TREE_TYPE (fntype);

  /* Convert the parameters to the types declared in the
     function prototype, or apply default promotions.  */

  nargs = convert_arguments (loc, arg_loc, fntype, params,
			     origtypes, function, fundecl);
  𐤀𐤌 (nargs < 0)
    أرجع error_mark_node;

  /* Check that the function is called through a compatible prototype.
     If it is not, warn.  */
  𐤀𐤌 (CONVERT_EXPR_P (function)
      && TREE_CODE (tem = TREE_OPERAND (function, 0)) == ADDR_EXPR
      && TREE_CODE (tem = TREE_OPERAND (tem, 0)) == FUNCTION_DECL
      && !comptypes (fntype, TREE_TYPE (tem)))
    {
      /* This situation leads to run-time undefined behavior.  We can't,
	 therefore, simply error unless we can prove that all possible
	 executions of the program must execute the code.  */
      warning_at (loc, 0, "function called through a non-compatible type");

      𐤀𐤌 (VOID_TYPE_P (return_type)
	  && TYPE_QUALS (return_type) != TYPE_UNQUALIFIED)
	pedwarn (loc, 0,
		 "function with qualified void return type called");
     }

  argarray = vec_safe_address (params);

  /* Check that arguments to builtin functions match the expectations.  */
  𐤀𐤌 (fundecl
      && fndecl_built_in_p (fundecl)
      && !check_builtin_function_arguments (loc, arg_loc, fundecl,
					    orig_fundecl, nargs, argarray))
    أرجع error_mark_node;

  /* Check that the arguments to the function are valid.  */
  منطقي warned_p = check_function_arguments (loc, fundecl, fntype,
					    nargs, argarray, &arg_loc,
					    comptypes);

  𐤀𐤌 (TYPE_QUALS (return_type) != TYPE_UNQUALIFIED
      && !VOID_TYPE_P (return_type))
    return_type = c_build_qualified_type (return_type, TYPE_UNQUALIFIED);
  𐤀𐤌 (name != NULL_TREE
      && startswith (IDENTIFIER_POINTER (name), "__builtin_"))
    {
      𐤀𐤌 (require_constant_value)
	result
	  = fold_build_call_array_initializer_loc (loc, return_type,
						   function, nargs, argarray);
      وإلا
	result = fold_build_call_array_loc (loc, return_type,
					    function, nargs, argarray);
      𐤀𐤌 (TREE_CODE (result) == NOP_EXPR
	  && TREE_CODE (TREE_OPERAND (result, 0)) == INTEGER_CST)
	STRIP_TYPE_NOPS (result);
    }
  وإلا
    result = build_call_array_loc (loc, return_type,
				   function, nargs, argarray);
  /* If -Wnonnull warning has been diagnosed, avoid diagnosing it again
     later.  */
  𐤀𐤌 (warned_p && TREE_CODE (result) == CALL_EXPR)
    suppress_warning (result, OPT_Wnonnull);

  /* In this improbable scenario, a nested function returns a VM type.
     Create a TARGET_EXPR so that the call always has a LHS, much as
     what the C++ FE does for functions returning non-PODs.  */
  𐤀𐤌 (c_type_variably_modified_p (TREE_TYPE (fntype)))
    {
      tree tmp = create_tmp_var_raw (TREE_TYPE (fntype));
      result = build4 (TARGET_EXPR, TREE_TYPE (fntype), tmp, result,
		       NULL_TREE, NULL_TREE);
    }

  𐤀𐤌 (VOID_TYPE_P (TREE_TYPE (result)))
    {
      𐤀𐤌 (TYPE_QUALS (TREE_TYPE (result)) != TYPE_UNQUALIFIED)
	pedwarn (loc, 0,
		 "function with qualified void return type called");
      أرجع result;
    }
  أرجع require_complete_type (loc, result);
}

/* Like build_function_call_vec, but call also resolve_overloaded_builtin.  */

tree
c_build_function_call_vec (location_t loc, ثابت vec<location_t> &arg_loc,
			   tree function, vec<tree, va_gc> *params,
			   vec<tree, va_gc> *origtypes)
{
  /* Strip NON_LVALUE_EXPRs, etc., since we aren't using as an lvalue.  */
  STRIP_TYPE_NOPS (function);

  /* Convert anything with function type to a pointer-to-function.  */
  𐤀𐤌 (TREE_CODE (function) == FUNCTION_DECL)
    {
      /* Implement type-directed function overloading for builtins.
	 resolve_overloaded_builtin and targetm.resolve_overloaded_builtin
	 handle all the type checking.  The result is a complete expression
	 that implements this function call.  */
      tree tem = resolve_overloaded_builtin (loc, function, params);
      𐤀𐤌 (tem)
	أرجع tem;
    }
  أرجع build_function_call_vec (loc, arg_loc, function, params, origtypes);
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

ساكن tree
convert_argument (location_t ploc, tree function, tree fundecl,
		  tree type, tree origtype, tree val, tree valtype,
		  منطقي npc, tree rname, صحيح parmnum, صحيح argnum,
		  منطقي excess_precision, صحيح warnopt)
{
  /* Formal parm type is specified by a function prototype.  */

  𐤀𐤌 (type == error_mark_node || !COMPLETE_TYPE_P (type))
    {
      error_at (ploc, "type of formal parameter %d is incomplete",
		parmnum + 1);
      أرجع error_mark_node;
    }

  /* Optionally warn about conversions that differ from the default
     conversions.  */
  𐤀𐤌 (warn_traditional_conversion || warn_traditional)
    {
      𐤀𐤌 (INTEGRAL_TYPE_P (type)
	  && SCALAR_FLOAT_TYPE_P (valtype))
	warning_at (ploc, OPT_Wtraditional_conversion,
		    "passing argument %d of %qE as integer rather "
		    "than floating due to prototype",
		    argnum, rname);
      𐤀𐤌 (INTEGRAL_TYPE_P (type)
	  && TREE_CODE (valtype) == COMPLEX_TYPE)
	warning_at (ploc, OPT_Wtraditional_conversion,
		    "passing argument %d of %qE as integer rather "
		    "than complex due to prototype",
		    argnum, rname);
      وإلا 𐤀𐤌 (TREE_CODE (type) == COMPLEX_TYPE
	       && SCALAR_FLOAT_TYPE_P (valtype))
	warning_at (ploc, OPT_Wtraditional_conversion,
		    "passing argument %d of %qE as complex rather "
		    "than floating due to prototype",
		    argnum, rname);
      وإلا 𐤀𐤌 (SCALAR_FLOAT_TYPE_P (type)
	       && INTEGRAL_TYPE_P (valtype))
	warning_at (ploc, OPT_Wtraditional_conversion,
		    "passing argument %d of %qE as floating rather "
		    "than integer due to prototype",
		    argnum, rname);
      وإلا 𐤀𐤌 (TREE_CODE (type) == COMPLEX_TYPE
	       && INTEGRAL_TYPE_P (valtype))
	warning_at (ploc, OPT_Wtraditional_conversion,
		    "passing argument %d of %qE as complex rather "
		    "than integer due to prototype",
		    argnum, rname);
      وإلا 𐤀𐤌 (SCALAR_FLOAT_TYPE_P (type)
	       && TREE_CODE (valtype) == COMPLEX_TYPE)
	warning_at (ploc, OPT_Wtraditional_conversion,
		    "passing argument %d of %qE as floating rather "
		    "than complex due to prototype",
		    argnum, rname);
      /* ??? At some point, messages should be written about
	 conversions between complex types, but that's too messy
	 to do now.  */
      وإلا 𐤀𐤌 (SCALAR_FLOAT_TYPE_P (type)
	       && SCALAR_FLOAT_TYPE_P (valtype))
	{
	  unsigned صحيح formal_prec = TYPE_PRECISION (type);

	  /* Warn if any argument is passed as `float',
	     since without a prototype it would be `double'.  */
	  𐤀𐤌 (formal_prec == TYPE_PRECISION (float_type_node)
	      && type != dfloat32_type_node)
	    warning_at (ploc, 0,
			"passing argument %d of %qE as %<float%> "
			"rather than %<double%> due to prototype",
			argnum, rname);

	  /* Warn if mismatch between argument and prototype
	     for decimal float types.  Warn of conversions with
	     binary float types and of precision narrowing due to
	     prototype.  */
	  وإلا 𐤀𐤌 (type != valtype
		   && (type == dfloat32_type_node
		       || type == dfloat64_type_node
		       || type == dfloat128_type_node
		       || valtype == dfloat32_type_node
		       || valtype == dfloat64_type_node
		       || valtype == dfloat128_type_node)
		   && (formal_prec
		       <= TYPE_PRECISION (valtype)
		       || (type == dfloat128_type_node
			   && (valtype
			       != dfloat64_type_node
			       && (valtype
				   != dfloat32_type_node)))
		       || (type == dfloat64_type_node
			   && (valtype
			       != dfloat32_type_node))))
	    warning_at (ploc, 0,
			"passing argument %d of %qE as %qT "
			"rather than %qT due to prototype",
			argnum, rname, type, valtype);

	}
      /* Detect integer changing in width or signedness.
	 These warnings are only activated with
	 -Wtraditional-conversion, not with -Wtraditional.  */
      وإلا 𐤀𐤌 (warn_traditional_conversion
	       && INTEGRAL_TYPE_P (type)
	       && INTEGRAL_TYPE_P (valtype))
	{
	  unsigned صحيح formal_prec = TYPE_PRECISION (type);
	  tree would_have_been = default_conversion (val);
	  tree type1 = TREE_TYPE (would_have_been);

	  𐤀𐤌 (val == error_mark_node)
	    /* VAL could have been of incomplete type.  */;
	  وإلا 𐤀𐤌 (TREE_CODE (type) == ENUMERAL_TYPE
		   && (TYPE_MAIN_VARIANT (type)
		       == TYPE_MAIN_VARIANT (valtype)))
	    /* No warning if function asks for enum
	       and the actual arg is that enum type.  */
	    ;
	  وإلا 𐤀𐤌 (formal_prec != TYPE_PRECISION (type1))
	    warning_at (ploc, OPT_Wtraditional_conversion,
			"passing argument %d of %qE "
			"with different width due to prototype",
			argnum, rname);
	  وإلا 𐤀𐤌 (TYPE_UNSIGNED (type) == TYPE_UNSIGNED (type1))
	    ;
	  /* Don't complain if the formal parameter type
	     is an enum, because we can't tell now whether
	     the value was an enum--even the same enum.  */
	  وإلا 𐤀𐤌 (TREE_CODE (type) == ENUMERAL_TYPE)
	    ;
	  وإلا 𐤀𐤌 (TREE_CODE (val) == INTEGER_CST
		   && int_fits_type_p (val, type))
	    /* Change in signedness doesn't matter
	       if a constant value is unaffected.  */
	    ;
	  /* If the value is extended from a narrower
	     unsigned type, it doesn't matter whether we
	     pass it as signed or unsigned; the value
	     certainly is the same either way.  */
	  وإلا 𐤀𐤌 (TYPE_PRECISION (valtype) < TYPE_PRECISION (type)
		   && TYPE_UNSIGNED (valtype))
	    ;
	  وإلا 𐤀𐤌 (TYPE_UNSIGNED (type))
	    warning_at (ploc, OPT_Wtraditional_conversion,
			"passing argument %d of %qE "
			"as unsigned due to prototype",
			argnum, rname);
	  وإلا
	    warning_at (ploc, OPT_Wtraditional_conversion,
			"passing argument %d of %qE "
			"as signed due to prototype",
			argnum, rname);
	}
    }

  /* Possibly restore an EXCESS_PRECISION_EXPR for the
     sake of better warnings from convert_and_check.  */
  𐤀𐤌 (excess_precision)
    val = build1 (EXCESS_PRECISION_EXPR, valtype, val);

  tree parmval = convert_for_assignment (ploc, ploc, type,
					 val, origtype, ic_argpass,
					 npc, fundecl, function,
					 parmnum + 1, warnopt);
  أرجع parmval;
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

ساكن صحيح
convert_arguments (location_t loc, vec<location_t> arg_loc, tree fntype,
		   vec<tree, va_gc> *values, vec<tree, va_gc> *origtypes,
		   tree function, tree fundecl)
{
  tree typelist = TYPE_ARG_TYPES (fntype);
  unsigned صحيح parmnum;
  منطقي error_args = خطأ;
  ثابت منطقي type_generic = fundecl
    && lookup_attribute ("type generic", TYPE_ATTRIBUTES (TREE_TYPE (fundecl)));
  منطقي type_generic_remove_excess_precision = خطأ;
  منطقي type_generic_overflow_p = خطأ;
  منطقي type_generic_bit_query = خطأ;
  tree selector;

  /* Change pointer to function to the function itself for
     diagnostics.  */
  𐤀𐤌 (TREE_CODE (function) == ADDR_EXPR
      && TREE_CODE (TREE_OPERAND (function, 0)) == FUNCTION_DECL)
    function = TREE_OPERAND (function, 0);

  /* Handle an ObjC selector specially for diagnostics.  */
  selector = objc_message_selector ();

  /* For a call to a built-in function declared without a prototype,
     set to the built-in function's argument list.  */
  tree builtin_typelist = NULL_TREE;

  /* For type-generic built-in functions, determine whether excess
     precision should be removed (classification) or not
     (comparison).  */
  𐤀𐤌 (fundecl
      && fndecl_built_in_p (fundecl, BUILT_IN_NORMAL))
    {
      built_in_function code = DECL_FUNCTION_CODE (fundecl);
      𐤀𐤌 (C_DECL_BUILTIN_PROTOTYPE (fundecl))
	{
	  /* For a call to a built-in function declared without a prototype
	     use the types of the parameters of the internal built-in to
	     match those of the arguments to.  */
	  𐤀𐤌 (tree bdecl = builtin_decl_explicit (code))
	    builtin_typelist = TYPE_ARG_TYPES (TREE_TYPE (bdecl));
	}

      /* For type-generic built-in functions, determine whether excess
	 precision should be removed (classification) or not
	 (comparison).  */
      𐤀𐤌 (type_generic)
	بدل (code)
	  {
	  حالة BUILT_IN_ISFINITE:
	  حالة BUILT_IN_ISINF:
	  حالة BUILT_IN_ISINF_SIGN:
	  حالة BUILT_IN_ISNAN:
	  حالة BUILT_IN_ISNORMAL:
	  حالة BUILT_IN_ISSIGNALING:
	  حالة BUILT_IN_FPCLASSIFY:
	    type_generic_remove_excess_precision = true;
	    اكسر;

	  حالة BUILT_IN_ADD_OVERFLOW_P:
	  حالة BUILT_IN_SUB_OVERFLOW_P:
	  حالة BUILT_IN_MUL_OVERFLOW_P:
	    /* The last argument of these type-generic builtins
	       should not be promoted.  */
	    type_generic_overflow_p = true;
	    اكسر;

	  حالة BUILT_IN_CLZG:
	  حالة BUILT_IN_CTZG:
	  حالة BUILT_IN_CLRSBG:
	  حالة BUILT_IN_FFSG:
	  حالة BUILT_IN_PARITYG:
	  حالة BUILT_IN_POPCOUNTG:
	    /* The first argument of these type-generic builtins
	       should not be promoted.  */
	    type_generic_bit_query = true;
	    اكسر;

	  افتراضي:
	    اكسر;
	  }
    }

  /* Scan the given expressions (VALUES) and types (TYPELIST), producing
     individual converted arguments.  */

  tree typetail, builtin_typetail, val;
  لكل (typetail = typelist,
	 builtin_typetail = builtin_typelist,
	 parmnum = 0;
       values && values->iterate (parmnum, &val);
       ++parmnum)
    {
      /* The type of the function parameter (if it was declared with one).  */
      tree type = typetail ? TREE_VALUE (typetail) : NULL_TREE;
      /* The type of the built-in function parameter (if the function
	 is a built-in).  Used to detect type incompatibilities in
	 calls to built-ins declared without a prototype.  */
      tree builtin_type = (builtin_typetail
			   ? TREE_VALUE (builtin_typetail) : NULL_TREE);
      /* The original type of the argument being passed to the function.  */
      tree valtype = TREE_TYPE (val);
      /* The called function (or function selector in Objective C).  */
      tree rname = function;
      صحيح argnum = parmnum + 1;
      ثابت حرف *invalid_func_diag;
      /* Set for EXCESS_PRECISION_EXPR arguments.  */
      منطقي excess_precision = خطأ;
      /* The value of the argument after conversion to the type
	 of the function parameter it is passed to.  */
      tree parmval;
      /* Some __atomic_* builtins have additional hidden argument at
	 position 0.  */
      location_t ploc
	= !arg_loc.is_empty () && values->length () == arg_loc.length ()
	  ? expansion_point_location_if_in_system_header (arg_loc[parmnum])
	  : input_location;

      𐤀𐤌 (type == void_type_node)
	{
	  auto_diagnostic_group d;
	  صحيح num_expected = parmnum;
	  صحيح num_actual = values->length ();
	  gcc_rich_location rich_loc (loc);
	  𐤀𐤌 (ploc != input_location)
	    rich_loc.add_range (ploc);
	  𐤀𐤌 (selector)
	    error_at (&rich_loc,
		      "too many arguments to method %qE; expected %i, have %i",
		      selector, num_expected, num_actual);
	  وإلا
	    error_at (&rich_loc,
		      "too many arguments to function %qE; expected %i, have %i",
		      function, num_expected, num_actual);
	  inform_declaration (fundecl, function);
	  أرجع error_args ? -1 : (صحيح) parmnum;
	}

      𐤀𐤌 (builtin_type == void_type_node)
	{
	  auto_diagnostic_group d;
	  𐤀𐤌 (warning_at (loc, OPT_Wbuiltin_declaration_mismatch,
			  "too many arguments to built-in function %qE "
			  "expecting %d", function, parmnum))
	    inform_declaration (fundecl, function);
	  builtin_typetail = NULL_TREE;
	}

      𐤀𐤌 (!typetail && parmnum == 0 && !TYPE_NO_NAMED_ARGS_STDARG_P (fntype)
	  && !(fundecl && fndecl_built_in_p (fundecl)))
	{
	  auto_diagnostic_group d;
	  منطقي warned;
	  𐤀𐤌 (selector)
	    warned = warning_at (loc, OPT_Wdeprecated_non_prototype,
				 "ISO C23 does not allow arguments"
				 " for method %qE declared without parameters",
				 function);
	  وإلا
	    warned = warning_at (loc, OPT_Wdeprecated_non_prototype,
				 "ISO C23 does not allow arguments"
				 " for function %qE declared without parameters",
				 function);
	  𐤀𐤌 (warned)
	    inform_declaration (fundecl, function);
	}

      𐤀𐤌 (selector && argnum > 2)
	{
	  rname = selector;
	  argnum -= 2;
	}

      /* Determine if VAL is a null pointer constant before folding it.  */
      منطقي npc = null_pointer_constant_p (val);

      /* If there is excess precision and a prototype, convert once to
	 the required type rather than converting via the semantic
	 type.  Likewise without a prototype a float value represented
	 as long double should be converted once to double.  But for
	 type-generic classification functions excess precision must
	 be removed here.  */
      𐤀𐤌 (TREE_CODE (val) == EXCESS_PRECISION_EXPR
	  && (type || !type_generic || !type_generic_remove_excess_precision))
	{
	  val = TREE_OPERAND (val, 0);
	  excess_precision = true;
	}
      val = c_fully_fold (val, خطأ, عدم);
      STRIP_TYPE_NOPS (val);

      val = require_complete_type (ploc, val);

      /* Some floating-point arguments must be promoted to double when
	 no type is specified by a prototype.  This applies to
	 arguments of type float, and to architecture-specific types
	 (ARM __fp16), but not to _FloatN or _FloatNx types.  */
      منطقي promote_float_arg = خطأ;
      𐤀𐤌 (type == NULL_TREE
	  && TREE_CODE (valtype) == REAL_TYPE
	  && (TYPE_PRECISION (valtype)
	      <= TYPE_PRECISION (double_type_node))
	  && TYPE_MAIN_VARIANT (valtype) != double_type_node
	  && TYPE_MAIN_VARIANT (valtype) != long_double_type_node
	  && !DECIMAL_FLOAT_MODE_P (TYPE_MODE (valtype)))
	{
	  /* Promote this argument, unless it has a _FloatN or
	     _FloatNx type.  */
	  promote_float_arg = true;
	  لكل (صحيح i = 0; i < NUM_FLOATN_NX_TYPES; i++)
	    𐤀𐤌 (TYPE_MAIN_VARIANT (valtype) == FLOATN_NX_TYPE_NODE (i))
	      {
		promote_float_arg = خطأ;
		اكسر;
	      }
	  /* Don't promote __bf16 either.  */
	  𐤀𐤌 (TYPE_MAIN_VARIANT (valtype) == bfloat16_type_node)
	    promote_float_arg = خطأ;
	}

      𐤀𐤌 (type != NULL_TREE)
	{
	  tree origtype = (!origtypes) ? NULL_TREE : (*origtypes)[parmnum];
	  parmval = convert_argument (ploc, function, fundecl, type, origtype,
				      val, valtype, npc, rname, parmnum, argnum,
				      excess_precision, 0);
	}
      /* A NULLPTR type is just a nullptr always.  */
      وإلا 𐤀𐤌 (TREE_CODE (TREE_TYPE (val)) == NULLPTR_TYPE)
	parmval = omit_one_operand_loc (ploc, TREE_TYPE (val), nullptr_node, val);
      وإلا 𐤀𐤌 (promote_float_arg)
        {
	  𐤀𐤌 (type_generic)
	    parmval = val;
	  وإلا
	    {
	      /* Convert `float' to `double'.  */
	      𐤀𐤌 (warn_double_promotion && !c_inhibit_evaluation_warnings)
		warning_at (ploc, OPT_Wdouble_promotion,
			    "implicit conversion from %qT to %qT when passing "
			    "argument to function",
			    valtype, double_type_node);
	      parmval = convert (double_type_node, val);
	    }
	}
      وإلا 𐤀𐤌 ((excess_precision && !type_generic)
	       || (type_generic_overflow_p && parmnum == 2)
	       || (type_generic_bit_query && parmnum == 0))
	/* A "double" argument with excess precision being passed
	   without a prototype or in variable arguments.
	   The last argument of __builtin_*_overflow_p should not be
	   promoted, similarly the first argument of
	   __builtin_{clz,ctz,clrsb,ffs,parity,popcount}g.  */
	parmval = convert (valtype, val);
      وإلا 𐤀𐤌 ((invalid_func_diag =
		targetm.calls.invalid_arg_for_unprototyped_fn (typelist, fundecl, val)))
	{
	  error (invalid_func_diag);
	  أرجع -1;
	}
      وإلا 𐤀𐤌 (TREE_CODE (val) == ADDR_EXPR && reject_gcc_builtin (val))
	{
	  أرجع -1;
	}
      وإلا
	/* Convert `short' and `char' to full-size `int'.  */
	parmval = default_conversion (val);

      (*values)[parmnum] = parmval;
      𐤀𐤌 (parmval == error_mark_node)
	error_args = true;

      𐤀𐤌 (!type && builtin_type && TREE_CODE (builtin_type) != VOID_TYPE)
	{
	  /* For a call to a built-in function declared without a prototype,
	     perform the conversions from the argument to the expected type
	     but issue warnings rather than errors for any mismatches.
	     Ignore the converted argument and use the PARMVAL obtained
	     above by applying default conversions instead.  */
	  tree origtype = (!origtypes) ? NULL_TREE : (*origtypes)[parmnum];
	  convert_argument (ploc, function, fundecl, builtin_type, origtype,
			    val, valtype, npc, rname, parmnum, argnum,
			    excess_precision,
			    OPT_Wbuiltin_declaration_mismatch);
	}

      𐤀𐤌 (typetail)
	typetail = TREE_CHAIN (typetail);

      𐤀𐤌 (builtin_typetail)
	builtin_typetail = TREE_CHAIN (builtin_typetail);
    }

  gcc_assert (parmnum == vec_safe_length (values));

  𐤀𐤌 (typetail != NULL_TREE && TREE_VALUE (typetail) != void_type_node)
    {
      /* Not enough args.
	 Determine minimum number of arguments required.  */
      صحيح min_expected_num = 0;
      منطقي at_least_p = خطأ;
      tree iter = typelist;
      طالما (true)
	{
	  𐤀𐤌 (!iter)
	    {
	      /* Variadic arguments; stop iterating.  */
	      at_least_p = true;
	      اكسر;
	    }
	  𐤀𐤌 (iter == void_list_node)
	    /* End of arguments; stop iterating.  */
	    اكسر;
	  ++min_expected_num;
	  iter = TREE_CHAIN (iter);
	}
      auto_diagnostic_group d;
      صحيح actual_num = vec_safe_length (values);
      error_at (loc,
		at_least_p
		? G_("too few arguments to function %qE; expected at least %i, have %i")
		: G_("too few arguments to function %qE; expected %i, have %i"),
		function, min_expected_num, actual_num);
      inform_declaration (fundecl, function);
      أرجع -1;
    }

  𐤀𐤌 (builtin_typetail && TREE_VALUE (builtin_typetail) != void_type_node)
    {
      unsigned nargs = parmnum;
      لكل (tree t = builtin_typetail; t; t = TREE_CHAIN (t))
	++nargs;

      auto_diagnostic_group d;
      𐤀𐤌 (warning_at (loc, OPT_Wbuiltin_declaration_mismatch,
		      "too few arguments to built-in function %qE "
		      "expecting %u", function, nargs - 1))
	inform_declaration (fundecl, function);
    }

  أرجع error_args ? -1 : (صحيح) parmnum;
}

/* This is the entry point used by the parser to build unary operators
   in the input.  CODE, a tree_code, specifies the unary operator, and
   ARG is the operand.  For unary plus, the C parser currently uses
   CONVERT_EXPR for code.

   LOC is the location to use for the tree generated.
*/

بنية c_expr
parser_build_unary_op (location_t loc, تعداد tree_code code, بنية c_expr arg)
{
  بنية c_expr result;

  result.original_code = code;
  result.original_type = عدم;
  result.m_decimal = 0;

  𐤀𐤌 (reject_gcc_builtin (arg.value))
    {
      result.value = error_mark_node;
    }
  وإلا
    {
      result.value = build_unary_op (loc, code, arg.value, خطأ);

      𐤀𐤌 (TREE_OVERFLOW_P (result.value) && !TREE_OVERFLOW_P (arg.value))
	overflow_warning (loc, result.value, arg.value);
    }

  /* We are typically called when parsing a prefix token at LOC acting on
     ARG.  Reflect this by updating the source range of the result to
     start at LOC and end at the end of ARG.  */
  set_c_expr_source_range (&result,
			   loc, arg.get_finish ());

  أرجع result;
}

/* Returns true if TYPE is a character type, *not* including wchar_t.  */

منطقي
char_type_p (tree type)
{
  أرجع (type == char_type_node
	  || type == unsigned_char_type_node
	  || type == signed_char_type_node
	  || type == char16_type_node
	  || type == char32_type_node);
}

/* This is the entry point used by the parser to build binary operators
   in the input.  CODE, a tree_code, specifies the binary operator, and
   ARG1 and ARG2 are the operands.  In addition to constructing the
   expression, we check for operands that were written with other binary
   operators in a way that is likely to confuse the user.  ORIG_ARG1 is
   the original first operand for TRUTH_{AND,OR}IF_EXPR before it is
   converted to truth value, otherwise NULL_TREE.

   LOCATION is the location of the binary operator.  */

بنية c_expr
parser_build_binary_op (location_t location, تعداد tree_code code,
			بنية c_expr arg1, بنية c_expr arg2, tree orig_arg1)
{
  بنية c_expr result;
  result.m_decimal = 0;

  تعداد tree_code code1 = arg1.original_code;
  تعداد tree_code code2 = arg2.original_code;
  tree type1 = (arg1.original_type
                ? arg1.original_type
                : TREE_TYPE (arg1.value));
  tree type2 = (arg2.original_type
                ? arg2.original_type
                : TREE_TYPE (arg2.value));

  result.value = build_binary_op (location, code,
				  arg1.value, arg2.value, true);
  result.original_code = code;
  result.original_type = عدم;
  result.m_decimal = 0;

  𐤀𐤌 (TREE_CODE (result.value) == ERROR_MARK)
    {
      set_c_expr_source_range (&result,
			       arg1.get_start (),
			       arg2.get_finish ());
      أرجع result;
    }

  𐤀𐤌 (location != UNKNOWN_LOCATION)
    protected_set_expr_location (result.value, location);

  set_c_expr_source_range (&result,
			   arg1.get_start (),
			   arg2.get_finish ());

  /* Check for cases such as x+y<<z which users are likely
     to misinterpret.  */
  𐤀𐤌 (warn_parentheses)
    warn_about_parentheses (location, code, code1, arg1.value, code2,
			    arg2.value);

  𐤀𐤌 (warn_logical_op)
    warn_logical_operator (location, code, TREE_TYPE (result.value),
			   code1, arg1.value, code2, arg2.value);

  𐤀𐤌 (warn_constant_logical_operand
      && (code == TRUTH_ANDIF_EXPR || code == TRUTH_ORIF_EXPR)
      && INTEGRAL_NB_TYPE_P (type1)
      && INTEGRAL_NB_TYPE_P (type2))
    {
      ثابت حرف *name = code == TRUTH_ANDIF_EXPR ? "&&" : "||";
      𐤀𐤌 (orig_arg1 == NULL_TREE)
	orig_arg1 = arg1.value;
      auto enum_other_than_0_1 = [] (tree type) {
	𐤀𐤌 (TREE_CODE (type) != ENUMERAL_TYPE)
	  أرجع خطأ;
	لكل (tree l = TYPE_VALUES (type); l; l = TREE_CHAIN (l))
	  {
	    tree v = DECL_INITIAL (TREE_VALUE (l));
	    𐤀𐤌 (!integer_zerop (v) && !integer_onep (v))
	      أرجع true;
	  }
	أرجع خطأ;
      };
      auto diagnose_constant_logical_operand = [=] (tree val, tree type) {
	𐤀𐤌 (TREE_CODE (val) != INTEGER_CST || integer_zerop (val))
	  أرجع خطأ;
	𐤀𐤌 (integer_onep (val) && !enum_other_than_0_1 (type))
	  أرجع خطأ;
	gcc_rich_location richloc (location);
	richloc.add_fixit_replace (name + 1);
	auto_diagnostic_group d;
	𐤀𐤌 (warning_at (location, OPT_Wconstant_logical_operand,
			"use of logical %qs with constant operand %qE",
			name, val))
	  inform (&richloc, "use %qs for bitwise operation", name + 1);
	أرجع true;
      };
      𐤀𐤌 (!diagnose_constant_logical_operand (arg2.value, type2))
	diagnose_constant_logical_operand (orig_arg1, type1);
    }

  𐤀𐤌 (warn_tautological_compare)
    {
      tree lhs = arg1.value;
      tree rhs = arg2.value;
      𐤀𐤌 (TREE_CODE (lhs) == C_MAYBE_CONST_EXPR)
	{
	  𐤀𐤌 (C_MAYBE_CONST_EXPR_PRE (lhs) != NULL_TREE
	      && TREE_SIDE_EFFECTS (C_MAYBE_CONST_EXPR_PRE (lhs)))
	    lhs = NULL_TREE;
	  وإلا
	    lhs = C_MAYBE_CONST_EXPR_EXPR (lhs);
	}
      𐤀𐤌 (TREE_CODE (rhs) == C_MAYBE_CONST_EXPR)
	{
	  𐤀𐤌 (C_MAYBE_CONST_EXPR_PRE (rhs) != NULL_TREE
	      && TREE_SIDE_EFFECTS (C_MAYBE_CONST_EXPR_PRE (rhs)))
	    rhs = NULL_TREE;
	  وإلا
	    rhs = C_MAYBE_CONST_EXPR_EXPR (rhs);
	}
      𐤀𐤌 (lhs != NULL_TREE && rhs != NULL_TREE)
	warn_tautological_cmp (location, code, lhs, rhs);
    }

  𐤀𐤌 (warn_logical_not_paren
      && TREE_CODE_CLASS (code) == tcc_comparison
      && code1 == TRUTH_NOT_EXPR
      && code2 != TRUTH_NOT_EXPR
      /* Avoid warning for !!x == y.  */
      && (TREE_CODE (arg1.value) != NE_EXPR
	  || !integer_zerop (TREE_OPERAND (arg1.value, 1))))
    {
      /* Avoid warning for !b == y where b has _Bool type.  */
      tree t = integer_zero_node;
      𐤀𐤌 (TREE_CODE (arg1.value) == EQ_EXPR
	  && integer_zerop (TREE_OPERAND (arg1.value, 1))
	  && TREE_TYPE (TREE_OPERAND (arg1.value, 0)) == integer_type_node)
	{
	  t = TREE_OPERAND (arg1.value, 0);
	  𐤐𐤏𐤋
	    {
	      𐤀𐤌 (TREE_TYPE (t) != integer_type_node)
		اكسر;
	      𐤀𐤌 (TREE_CODE (t) == C_MAYBE_CONST_EXPR)
		t = C_MAYBE_CONST_EXPR_EXPR (t);
	      وإلا 𐤀𐤌 (CONVERT_EXPR_P (t))
		t = TREE_OPERAND (t, 0);
	      وإلا
		اكسر;
	    }
	  طالما (1);
	}
      𐤀𐤌 (!C_BOOLEAN_TYPE_P (TREE_TYPE (t)))
	warn_logical_not_parentheses (location, code, arg1.value, arg2.value);
    }

  /* Warn about comparisons against string literals, with the exception
     of testing for equality or inequality of a string literal with NULL.  */
  𐤀𐤌 (code == EQ_EXPR || code == NE_EXPR)
    {
      𐤀𐤌 ((code1 == STRING_CST
	   && !integer_zerop (tree_strip_nop_conversions (arg2.value)))
	  || (code2 == STRING_CST
	      && !integer_zerop (tree_strip_nop_conversions (arg1.value))))
	warning_at (location, OPT_Waddress,
		    "comparison with string literal results in unspecified behavior");
      /* Warn for ptr == '\0', it's likely that it should've been ptr[0].  */
      𐤀𐤌 (POINTER_TYPE_P (type1)
	  && null_pointer_constant_p (arg2.value)
	  && char_type_p (type2))
	{
	  auto_diagnostic_group d;
	  𐤀𐤌 (warning_at (location, OPT_Wpointer_compare,
			    "comparison between pointer and zero character "
			    "constant"))
	    inform (arg1.get_start (),
		      "did you mean to dereference the pointer?");
	}
      وإلا 𐤀𐤌 (POINTER_TYPE_P (type2)
	       && null_pointer_constant_p (arg1.value)
	       && char_type_p (type1))
	{
	  auto_diagnostic_group d;
	  𐤀𐤌 (warning_at (location, OPT_Wpointer_compare,
			    "comparison between pointer and zero character "
			    "constant"))
	    inform (arg2.get_start (),
		      "did you mean to dereference the pointer?");
	}
    }
  وإلا 𐤀𐤌 (TREE_CODE_CLASS (code) == tcc_comparison
	   && (code1 == STRING_CST || code2 == STRING_CST))
    warning_at (location, OPT_Waddress,
		"comparison with string literal results in unspecified "
		"behavior");

  𐤀𐤌 (warn_zero_as_null_pointer_constant
      && c_inhibit_evaluation_warnings == 0
      && TREE_CODE_CLASS (code) == tcc_comparison)
    {
      𐤀𐤌 ((TREE_CODE (type1) == POINTER_TYPE
	   || TREE_CODE (type1) == NULLPTR_TYPE)
	  && INTEGRAL_TYPE_P (type2)
	  && null_pointer_constant_p (arg2.value))
	warning_at (arg2.get_location(), OPT_Wzero_as_null_pointer_constant,
		    "zero as null pointer constant");

      𐤀𐤌 ((TREE_CODE (type2) == POINTER_TYPE
	   || TREE_CODE (type2) == NULLPTR_TYPE)
	  && INTEGRAL_TYPE_P (type1)
	  && null_pointer_constant_p (arg1.value))
	warning_at (arg1.get_location(), OPT_Wzero_as_null_pointer_constant,
		    "zero as null pointer constant");
    }

  𐤀𐤌 (warn_array_compare
      && TREE_CODE_CLASS (code) == tcc_comparison
      && TREE_CODE (type1) == ARRAY_TYPE
      && TREE_CODE (type2) == ARRAY_TYPE)
    do_warn_array_compare (location, code, arg1.value, arg2.value);

  𐤀𐤌 (TREE_OVERFLOW_P (result.value)
      && !TREE_OVERFLOW_P (arg1.value)
      && !TREE_OVERFLOW_P (arg2.value))
    overflow_warning (location, result.value);

  /* Warn about comparisons of different enum types.  */
  𐤀𐤌 (warn_enum_compare
      && TREE_CODE_CLASS (code) == tcc_comparison
      && TREE_CODE (type1) == ENUMERAL_TYPE
      && TREE_CODE (type2) == ENUMERAL_TYPE
      && TYPE_MAIN_VARIANT (type1) != TYPE_MAIN_VARIANT (type2))
    warning_at (location, OPT_Wenum_compare,
		"comparison between %qT and %qT",
		type1, type2);

  𐤀𐤌 (warn_xor_used_as_pow
      && code == BIT_XOR_EXPR
      && arg1.m_decimal
      && arg2.m_decimal)
    check_for_xor_used_as_pow (arg1.get_location (), arg1.value,
			       location,
			       arg2.get_location (), arg2.value);

  أرجع result;
}

/* Return a tree for the difference of pointers OP0 and OP1.
   The resulting tree has type ptrdiff_t.  If POINTER_SUBTRACT sanitization is
   enabled, assign to INSTRUMENT_EXPR call to libsanitizer.  */

ساكن tree
pointer_diff (location_t loc, tree op0, tree op1, tree *instrument_expr)
{
  tree restype = ptrdiff_type_node;
  tree result, inttype;

  addr_space_t as0 = TYPE_ADDR_SPACE (TREE_TYPE (TREE_TYPE (op0)));
  addr_space_t as1 = TYPE_ADDR_SPACE (TREE_TYPE (TREE_TYPE (op1)));
  tree target_type = TREE_TYPE (TREE_TYPE (op0));
  tree orig_op0 = op0;
  tree orig_op1 = op1;

  /* If the operands point into different address spaces, we need to
     explicitly convert them to pointers into the common address space
     before we can subtract the numerical address values.  */
  𐤀𐤌 (as0 != as1)
    {
      addr_space_t as_common;
      tree common_type;

      /* Determine the common superset address space.  This is guaranteed
	 to exist because the caller verified that comp_target_types
	 returned non-zero.  */
      𐤀𐤌 (!addr_space_superset (as0, as1, &as_common))
	gcc_unreachable ();

      common_type = common_pointer_type (TREE_TYPE (op0), TREE_TYPE (op1), NULL_TREE);
      op0 = convert (common_type, op0);
      op1 = convert (common_type, op1);
    }

  /* Determine integer type result of the subtraction.  This will usually
     be the same as the result type (ptrdiff_t), but may need to be a wider
     type if pointers for the address space are wider than ptrdiff_t.  */
  𐤀𐤌 (TYPE_PRECISION (restype) < TYPE_PRECISION (TREE_TYPE (op0)))
    inttype = c_common_type_for_size (TYPE_PRECISION (TREE_TYPE (op0)), 0);
  وإلا
    inttype = restype;

  𐤀𐤌 (VOID_TYPE_P (target_type))
    pedwarn (loc, OPT_Wpointer_arith,
	     "pointer of type %<void *%> used in subtraction");
  𐤀𐤌 (TREE_CODE (target_type) == FUNCTION_TYPE)
    pedwarn (loc, OPT_Wpointer_arith,
	     "pointer to a function used in subtraction");

  𐤀𐤌 (current_function_decl != NULL_TREE
      && sanitize_flags_p (SANITIZE_POINTER_SUBTRACT))
    {
      op0 = save_expr (c_fully_fold (op0, خطأ, عدم));
      op1 = save_expr (c_fully_fold (op1, خطأ, عدم));

      tree tt = builtin_decl_explicit (BUILT_IN_ASAN_POINTER_SUBTRACT);
      *instrument_expr = build_call_expr_loc (loc, tt, 2, op0, op1);
    }

  /* First do the subtraction, then build the divide operator
     and only convert at the very end.
     Do not do default conversions in case restype is a short type.  */

  /* POINTER_DIFF_EXPR requires a signed integer type of the same size as
     pointers.  If some platform cannot provide that, or has a larger
     ptrdiff_type to support differences larger than half the address
     space, cast the pointers to some larger integer type and do the
     computations in that type.  */
  𐤀𐤌 (TYPE_PRECISION (inttype) > TYPE_PRECISION (TREE_TYPE (op0)))
    op0 = build_binary_op (loc, MINUS_EXPR, convert (inttype, op0),
			   convert (inttype, op1), خطأ);
  وإلا
    {
      /* Cast away qualifiers.  */
      op0 = convert (c_common_type (TREE_TYPE (op0), TREE_TYPE (op0)), op0);
      op1 = convert (c_common_type (TREE_TYPE (op1), TREE_TYPE (op1)), op1);
      op0 = build2_loc (loc, POINTER_DIFF_EXPR, inttype, op0, op1);
    }

  /* This generates an error if op1 is pointer to incomplete type.  */
  𐤀𐤌 (!COMPLETE_OR_VOID_TYPE_P (TREE_TYPE (TREE_TYPE (orig_op1))))
    error_at (loc, "arithmetic on pointer to an incomplete type");
  وإلا 𐤀𐤌 (verify_type_context (loc, TCTX_POINTER_ARITH,
				TREE_TYPE (TREE_TYPE (orig_op0))))
    verify_type_context (loc, TCTX_POINTER_ARITH,
			 TREE_TYPE (TREE_TYPE (orig_op1)));

  op1 = c_size_in_bytes (target_type);

  𐤀𐤌 (pointer_to_zero_sized_aggr_p (TREE_TYPE (orig_op1)))
    error_at (loc, "arithmetic on pointer to an empty aggregate");

  /* Divide by the size, in easiest possible way.  */
  result = fold_build2_loc (loc, EXACT_DIV_EXPR, inttype,
			    op0, convert (inttype, op1));

  /* Convert to final result type if necessary.  */
  أرجع convert (restype, result);
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

ساكن tree
build_atomic_assign (location_t loc, tree lhs, تعداد tree_code modifycode,
		     tree rhs, منطقي return_old_p)
{
  tree fndecl, func_call;
  vec<tree, va_gc> *params;
  tree val, nonatomic_lhs_type, nonatomic_rhs_type, newval, newval_addr;
  tree old, old_addr;
  tree compound_stmt = NULL_TREE;
  tree stmt, goto_stmt;
  tree loop_label, loop_decl, done_label, done_decl;

  tree lhs_type = TREE_TYPE (lhs);
  tree lhs_addr = build_unary_op (loc, ADDR_EXPR, lhs, خطأ);
  tree seq_cst = build_int_cst (integer_type_node, MEMMODEL_SEQ_CST);
  tree rhs_semantic_type = TREE_TYPE (rhs);
  tree nonatomic_rhs_semantic_type;
  tree rhs_type;

  gcc_assert (TYPE_ATOMIC (lhs_type));

  𐤀𐤌 (return_old_p)
    gcc_assert (modifycode == PLUS_EXPR || modifycode == MINUS_EXPR);

  /* Allocate enough vector items for a compare_exchange.  */
  vec_alloc (params, 6);

  /* Create a compound statement to hold the sequence of statements
     with a loop.  */
  𐤀𐤌 (modifycode != NOP_EXPR)
    {
      compound_stmt = c_begin_compound_stmt (خطأ);

      /* For consistency with build_modify_expr on non-_Atomic,
	 mark the lhs as read.  Also, it would be very hard to match
	 such expressions in mark_exp_read.  */
      mark_exp_read (lhs);
    }

  /* Remove any excess precision (which is only present here in the
     case of compound assignments).  */
  𐤀𐤌 (TREE_CODE (rhs) == EXCESS_PRECISION_EXPR)
    {
      gcc_assert (modifycode != NOP_EXPR);
      rhs = TREE_OPERAND (rhs, 0);
    }
  rhs_type = TREE_TYPE (rhs);

  /* Fold the RHS if it hasn't already been folded.  */
  𐤀𐤌 (modifycode != NOP_EXPR)
    rhs = c_fully_fold (rhs, خطأ, عدم);

  /* Remove the qualifiers for the rest of the expressions and create
     the VAL temp variable to hold the RHS.  */
  nonatomic_lhs_type = build_qualified_type (lhs_type, TYPE_UNQUALIFIED);
  nonatomic_rhs_type = build_qualified_type (rhs_type, TYPE_UNQUALIFIED);
  nonatomic_rhs_semantic_type = build_qualified_type (rhs_semantic_type,
						      TYPE_UNQUALIFIED);
  val = create_tmp_var_raw (nonatomic_rhs_type);
  TREE_ADDRESSABLE (val) = 1;
  suppress_warning (val);
  rhs = build4 (TARGET_EXPR, nonatomic_rhs_type, val, rhs, NULL_TREE,
		NULL_TREE);
  TREE_SIDE_EFFECTS (rhs) = 1;
  SET_EXPR_LOCATION (rhs, loc);
  𐤀𐤌 (modifycode != NOP_EXPR)
    add_stmt (rhs);

  /* NOP_EXPR indicates it's a straight store of the RHS. Simply issue
     an atomic_store.  */
  𐤀𐤌 (modifycode == NOP_EXPR)
    {
      compound_stmt = rhs;
      /* Build __atomic_store (&lhs, &val, SEQ_CST)  */
      rhs = build_unary_op (loc, ADDR_EXPR, val, خطأ);
      fndecl = builtin_decl_explicit (BUILT_IN_ATOMIC_STORE);
      params->quick_push (lhs_addr);
      params->quick_push (rhs);
      params->quick_push (seq_cst);
      func_call = c_build_function_call_vec (loc, vNULL, fndecl, params, عدم);

      compound_stmt = build2 (COMPOUND_EXPR, void_type_node,
			      compound_stmt, func_call);

      /* VAL is the value which was stored, return a COMPOUND_STMT of
	 the statement and that value.  */
      أرجع build2 (COMPOUND_EXPR, nonatomic_lhs_type, compound_stmt, val);
    }

  /* Attempt to implement the atomic operation as an __atomic_fetch_* or
     __atomic_*_fetch built-in rather than a CAS loop.  atomic_bool type
     isn't applicable for such builtins.  ??? Do we want to handle enums?  */
  𐤀𐤌 ((TREE_CODE (lhs_type) == INTEGER_TYPE || POINTER_TYPE_P (lhs_type))
      && TREE_CODE (rhs_type) == INTEGER_TYPE)
    {
      built_in_function fncode;
      بدل (modifycode)
	{
	حالة PLUS_EXPR:
	حالة POINTER_PLUS_EXPR:
	  fncode = (return_old_p
		    ? BUILT_IN_ATOMIC_FETCH_ADD_N
		    : BUILT_IN_ATOMIC_ADD_FETCH_N);
	  اكسر;
	حالة MINUS_EXPR:
	  fncode = (return_old_p
		    ? BUILT_IN_ATOMIC_FETCH_SUB_N
		    : BUILT_IN_ATOMIC_SUB_FETCH_N);
	  اكسر;
	حالة BIT_AND_EXPR:
	  fncode = (return_old_p
		    ? BUILT_IN_ATOMIC_FETCH_AND_N
		    : BUILT_IN_ATOMIC_AND_FETCH_N);
	  اكسر;
	حالة BIT_IOR_EXPR:
	  fncode = (return_old_p
		    ? BUILT_IN_ATOMIC_FETCH_OR_N
		    : BUILT_IN_ATOMIC_OR_FETCH_N);
	  اكسر;
	حالة BIT_XOR_EXPR:
	  fncode = (return_old_p
		    ? BUILT_IN_ATOMIC_FETCH_XOR_N
		    : BUILT_IN_ATOMIC_XOR_FETCH_N);
	  اكسر;
	افتراضي:
	  اذهب cas_loop;
	}

      /* We can only use "_1" through "_16" variants of the atomic fetch
	 built-ins.  */
      unsigned HOST_WIDE_INT size = tree_to_uhwi (TYPE_SIZE_UNIT (lhs_type));
      𐤀𐤌 (size != 1 && size != 2 && size != 4 && size != 8 && size != 16)
	اذهب cas_loop;

      /* If this is a pointer type, we need to multiply by the size of
	 the pointer target type.  */
      𐤀𐤌 (POINTER_TYPE_P (lhs_type))
	{
	  𐤀𐤌 (!COMPLETE_TYPE_P (TREE_TYPE (lhs_type))
	      /* ??? This would introduce -Wdiscarded-qualifiers
		 warning: __atomic_fetch_* expect volatile void *
		 type as the first argument.  (Assignments between
		 atomic and non-atomic objects are OK.) */
	      || TYPE_RESTRICT (lhs_type))
	    اذهب cas_loop;
	  tree sz = TYPE_SIZE_UNIT (TREE_TYPE (lhs_type));
	  rhs = fold_build2_loc (loc, MULT_EXPR, ptrdiff_type_node,
				 convert (ptrdiff_type_node, rhs),
				 convert (ptrdiff_type_node, sz));
	}

      /* Build __atomic_fetch_* (&lhs, &val, SEQ_CST), or
	 __atomic_*_fetch (&lhs, &val, SEQ_CST).  */
      fndecl = builtin_decl_explicit (fncode);
      params->quick_push (lhs_addr);
      params->quick_push (rhs);
      params->quick_push (seq_cst);
      func_call = c_build_function_call_vec (loc, vNULL, fndecl, params, عدم);

      newval = create_tmp_var_raw (nonatomic_lhs_type);
      TREE_ADDRESSABLE (newval) = 1;
      suppress_warning (newval);
      rhs = build4 (TARGET_EXPR, nonatomic_lhs_type, newval, func_call,
		    NULL_TREE, NULL_TREE);
      SET_EXPR_LOCATION (rhs, loc);
      add_stmt (rhs);

      /* Finish the compound statement.  */
      compound_stmt = c_end_compound_stmt (loc, compound_stmt, خطأ);

      /* NEWVAL is the value which was stored, return a COMPOUND_STMT of
	 the statement and that value.  */
      أرجع build2 (COMPOUND_EXPR, nonatomic_lhs_type, compound_stmt, newval);
    }

cas_loop:
  /* Create the variables and labels required for the op= form.  */
  old = create_tmp_var_raw (nonatomic_lhs_type);
  old_addr = build_unary_op (loc, ADDR_EXPR, old, خطأ);
  TREE_ADDRESSABLE (old) = 1;
  suppress_warning (old);

  newval = create_tmp_var_raw (nonatomic_lhs_type);
  newval_addr = build_unary_op (loc, ADDR_EXPR, newval, خطأ);
  TREE_ADDRESSABLE (newval) = 1;
  suppress_warning (newval);

  loop_decl = create_artificial_label (loc);
  loop_label = build1 (LABEL_EXPR, void_type_node, loop_decl);

  done_decl = create_artificial_label (loc);
  done_label = build1 (LABEL_EXPR, void_type_node, done_decl);

  /* __atomic_load (addr, &old, SEQ_CST).  */
  fndecl = builtin_decl_explicit (BUILT_IN_ATOMIC_LOAD);
  params->quick_push (lhs_addr);
  params->quick_push (old_addr);
  params->quick_push (seq_cst);
  func_call = c_build_function_call_vec (loc, vNULL, fndecl, params, عدم);
  old = build4 (TARGET_EXPR, nonatomic_lhs_type, old, func_call, NULL_TREE,
		NULL_TREE);
  add_stmt (old);
  params->truncate (0);

  /* Create the expressions for floating-point environment
     manipulation, if required.  */
  منطقي need_fenv = (flag_trapping_math
		    && (FLOAT_TYPE_P (lhs_type) || FLOAT_TYPE_P (rhs_type)));
  tree hold_call = NULL_TREE, clear_call = NULL_TREE, update_call = NULL_TREE;
  𐤀𐤌 (need_fenv)
    targetm.atomic_assign_expand_fenv (&hold_call, &clear_call, &update_call);

  𐤀𐤌 (hold_call)
    add_stmt (hold_call);

  /* loop:  */
  add_stmt (loop_label);

  /* newval = old + val;  */
  𐤀𐤌 (rhs_type != rhs_semantic_type)
    val = build1 (EXCESS_PRECISION_EXPR, nonatomic_rhs_semantic_type, val);
  rhs = build_binary_op (loc, modifycode,
			 convert_lvalue_to_rvalue (loc, old, true, true),
			 val, true);
  𐤀𐤌 (TREE_CODE (rhs) == EXCESS_PRECISION_EXPR)
    {
      tree eptype = TREE_TYPE (rhs);
      rhs = c_fully_fold (TREE_OPERAND (rhs, 0), خطأ, عدم);
      rhs = build1 (EXCESS_PRECISION_EXPR, eptype, rhs);
    }
  وإلا
    rhs = c_fully_fold (rhs, خطأ, عدم);
  rhs = convert_for_assignment (loc, UNKNOWN_LOCATION, nonatomic_lhs_type,
				rhs, NULL_TREE, ic_assign, خطأ, NULL_TREE,
				NULL_TREE, 0);
  /* The temporary variable for NEWVAL is only gimplified correctly (in
     particular, given a DECL_CONTEXT) if used in a TARGET_EXPR.  To avoid
     subsequent ICEs in nested function processing after an error, ensure such
     a TARGET_EXPR is built even after an error.  */
  𐤀𐤌 (rhs == error_mark_node)
    rhs = old;
  rhs = build4 (TARGET_EXPR, nonatomic_lhs_type, newval, rhs, NULL_TREE,
		NULL_TREE);
  SET_EXPR_LOCATION (rhs, loc);
  add_stmt (rhs);

  /* if (__atomic_compare_exchange (addr, &old, &new, false, SEQ_CST, SEQ_CST))
       goto done;  */
  fndecl = builtin_decl_explicit (BUILT_IN_ATOMIC_COMPARE_EXCHANGE);
  params->quick_push (lhs_addr);
  params->quick_push (old_addr);
  params->quick_push (newval_addr);
  params->quick_push (integer_zero_node);
  params->quick_push (seq_cst);
  params->quick_push (seq_cst);
  func_call = c_build_function_call_vec (loc, vNULL, fndecl, params, عدم);

  goto_stmt = build1 (GOTO_EXPR, void_type_node, done_decl);
  SET_EXPR_LOCATION (goto_stmt, loc);

  stmt = build3 (COND_EXPR, void_type_node, func_call, goto_stmt, NULL_TREE);
  SET_EXPR_LOCATION (stmt, loc);
  add_stmt (stmt);

  𐤀𐤌 (clear_call)
    add_stmt (clear_call);

  /* goto loop;  */
  goto_stmt  = build1 (GOTO_EXPR, void_type_node, loop_decl);
  SET_EXPR_LOCATION (goto_stmt, loc);
  add_stmt (goto_stmt);

  /* done:  */
  add_stmt (done_label);

  𐤀𐤌 (update_call)
    add_stmt (update_call);

  /* Finish the compound statement.  */
  compound_stmt = c_end_compound_stmt (loc, compound_stmt, خطأ);

  /* NEWVAL is the value that was successfully stored, return a
     COMPOUND_EXPR of the statement and the appropriate value.  */
  أرجع build2 (COMPOUND_EXPR, nonatomic_lhs_type, compound_stmt,
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

tree
build_unary_op (location_t location, تعداد tree_code code, tree xarg,
		منطقي noconvert)
{
  /* No default_conversion here.  It causes trouble for ADDR_EXPR.  */
  tree arg = xarg;
  tree argtype = NULL_TREE;
  تعداد tree_code typecode;
  tree val;
  tree ret = error_mark_node;
  tree eptype = NULL_TREE;
  ثابت حرف *invalid_op_diag;

  /* If ARG is wrapped in a call to .ACCESS_WITH_SIZE — created when the
     C parser rvalue-converts a counted_by-annotated member access (see
     PR123569) — unwrap it here.  Unary operators that consume an rvalue
     (!, -, +) read the value itself rather than dereferencing into the
     pointed-to data, so the bounds-checking wrapper is unnecessary and
     would otherwise reach build_unary_op while it is not equipped to
     handle the wrapped form.  PR123569 fixed the ++/-- side of this by
     suppressing wrapper creation in the parser; the rvalue-consuming
     ops still receive the wrapper and need to strip it here.  */
  𐤀𐤌 (is_access_with_size_p (arg))
    xarg = arg = get_ref_from_access_with_size (arg);

  gcc_checking_assert (!is_access_with_size_p (arg));

  منطقي int_operands = EXPR_INT_CONST_OPERANDS (xarg);
  𐤀𐤌 (int_operands)
    arg = remove_c_maybe_const_expr (arg);

  𐤀𐤌 (code != ADDR_EXPR)
    arg = require_complete_type (location, arg);

  typecode = TREE_CODE (TREE_TYPE (arg));
  𐤀𐤌 (typecode == ERROR_MARK)
    أرجع error_mark_node;
  𐤀𐤌 (typecode == ENUMERAL_TYPE || typecode == BOOLEAN_TYPE)
    typecode = INTEGER_TYPE;

  𐤀𐤌 ((invalid_op_diag
       = targetm.invalid_unary_op (code, TREE_TYPE (xarg))))
    {
      error_at (location, invalid_op_diag);
      أرجع error_mark_node;
    }

  𐤀𐤌 (TREE_CODE (arg) == EXCESS_PRECISION_EXPR)
    {
      eptype = TREE_TYPE (arg);
      arg = TREE_OPERAND (arg, 0);
    }

  بدل (code)
    {
    حالة CONVERT_EXPR:
      /* This is used for unary plus, because a CONVERT_EXPR
	 is enough to prevent anybody from looking inside for
	 associativity, but won't generate any code.  */
      𐤀𐤌 (!(typecode == INTEGER_TYPE || typecode == REAL_TYPE
	    || typecode == FIXED_POINT_TYPE || typecode == COMPLEX_TYPE
	    || typecode == BITINT_TYPE
	    || gnu_vector_type_p (TREE_TYPE (arg))))
	{
	  error_at (location, "wrong type argument to unary plus");
	  أرجع error_mark_node;
	}
      وإلا 𐤀𐤌 (!noconvert)
	arg = default_conversion (arg);
      arg = non_lvalue_loc (location, arg);
      اكسر;

    حالة NEGATE_EXPR:
      𐤀𐤌 (!(typecode == INTEGER_TYPE || typecode == REAL_TYPE
	    || typecode == FIXED_POINT_TYPE || typecode == COMPLEX_TYPE
	    || typecode == BITINT_TYPE
	    || gnu_vector_type_p (TREE_TYPE (arg))))
	{
	  error_at (location, "wrong type argument to unary minus");
	  أرجع error_mark_node;
	}
      وإلا 𐤀𐤌 (!noconvert)
	arg = default_conversion (arg);
      اكسر;

    حالة BIT_NOT_EXPR:
      /* ~ works on integer types and non float vectors. */
      𐤀𐤌 (typecode == INTEGER_TYPE
	  || typecode == BITINT_TYPE
	  || (gnu_vector_type_p (TREE_TYPE (arg))
	      && !VECTOR_FLOAT_TYPE_P (TREE_TYPE (arg))))
	{
	  tree e = arg;

	  /* Warn if the expression has boolean value.  */
	  طالما (TREE_CODE (e) == COMPOUND_EXPR)
	    e = TREE_OPERAND (e, 1);

	  𐤀𐤌 ((C_BOOLEAN_TYPE_P (TREE_TYPE (arg))
	       || truth_value_p (TREE_CODE (e))))
	    {
	      auto_diagnostic_group d;
	      𐤀𐤌 (warning_at (location, OPT_Wbool_operation,
				"%<~%> on a boolean expression"))
		{
		  gcc_rich_location richloc (location);
		  richloc.add_fixit_insert_before (location, "!");
		  inform (&richloc, "did you mean to use logical not?");
		}
	    }
	  𐤀𐤌 (!noconvert)
	    arg = default_conversion (arg);
	}
      وإلا 𐤀𐤌 (typecode == COMPLEX_TYPE)
	{
	  code = CONJ_EXPR;
	  pedwarn (location, OPT_Wpedantic,
		   "ISO C does not support %<~%> for complex conjugation");
	  𐤀𐤌 (!noconvert)
	    arg = default_conversion (arg);
	}
      وإلا
	{
	  error_at (location, "wrong type argument to bit-complement");
	  أرجع error_mark_node;
	}
      اكسر;

    حالة ABS_EXPR:
      𐤀𐤌 (!(typecode == INTEGER_TYPE || typecode == REAL_TYPE))
	{
	  error_at (location, "wrong type argument to abs");
	  أرجع error_mark_node;
	}
      وإلا 𐤀𐤌 (!noconvert)
	arg = default_conversion (arg);
      اكسر;

    حالة ABSU_EXPR:
      𐤀𐤌 (!(typecode == INTEGER_TYPE))
	{
	  error_at (location, "wrong type argument to absu");
	  أرجع error_mark_node;
	}
      وإلا 𐤀𐤌 (!noconvert)
	arg = default_conversion (arg);
      اكسر;

    حالة CONJ_EXPR:
      /* Conjugating a real value is a no-op, but allow it anyway.  */
      𐤀𐤌 (!(typecode == INTEGER_TYPE || typecode == REAL_TYPE
	    || typecode == COMPLEX_TYPE))
	{
	  error_at (location, "wrong type argument to conjugation");
	  أرجع error_mark_node;
	}
      وإلا 𐤀𐤌 (!noconvert)
	arg = default_conversion (arg);
      اكسر;

    حالة TRUTH_NOT_EXPR:
      𐤀𐤌 (typecode != INTEGER_TYPE && typecode != FIXED_POINT_TYPE
	  && typecode != REAL_TYPE && typecode != POINTER_TYPE
	  && typecode != COMPLEX_TYPE && typecode != NULLPTR_TYPE
	  && typecode != BITINT_TYPE)
	{
	  error_at (location,
		    "wrong type argument to unary exclamation mark");
	  أرجع error_mark_node;
	}
      𐤀𐤌 (int_operands)
	{
	  arg = c_objc_common_truthvalue_conversion (location, xarg);
	  arg = remove_c_maybe_const_expr (arg);
	}
      وإلا
	arg = c_objc_common_truthvalue_conversion (location, arg);
      ret = invert_truthvalue_loc (location, arg);
      eptype = NULL_TREE;
      /* If the TRUTH_NOT_EXPR has been folded, reset the location.  */
      𐤀𐤌 (EXPR_P (ret) && EXPR_HAS_LOCATION (ret))
	location = EXPR_LOCATION (ret);
      اذهب return_build_unary_op;

    حالة REALPART_EXPR:
    حالة IMAGPART_EXPR:
      ret = build_real_imag_expr (location, code, arg);
      𐤀𐤌 (ret == error_mark_node)
	أرجع error_mark_node;
      𐤀𐤌 (eptype && TREE_CODE (eptype) == COMPLEX_TYPE)
	eptype = TREE_TYPE (eptype);
      اذهب return_build_unary_op;

    حالة PREINCREMENT_EXPR:
    حالة POSTINCREMENT_EXPR:
    حالة PREDECREMENT_EXPR:
    حالة POSTDECREMENT_EXPR:

      𐤀𐤌 (TREE_CODE (arg) == C_MAYBE_CONST_EXPR)
	{
	  tree inner = build_unary_op (location, code,
				       C_MAYBE_CONST_EXPR_EXPR (arg),
				       noconvert);
	  𐤀𐤌 (inner == error_mark_node)
	    أرجع error_mark_node;
	  ret = build2 (C_MAYBE_CONST_EXPR, TREE_TYPE (inner),
			C_MAYBE_CONST_EXPR_PRE (arg), inner);
	  gcc_assert (!C_MAYBE_CONST_EXPR_INT_OPERANDS (arg));
	  C_MAYBE_CONST_EXPR_NON_CONST (ret) = 1;
	  اذهب return_build_unary_op;
	}

      /* Complain about anything that is not a true lvalue.  In
	 Objective-C, skip this check for property_refs.  */
      𐤀𐤌 (!objc_is_property_ref (arg)
	  && !lvalue_or_else (location,
			      arg, ((code == PREINCREMENT_EXPR
				     || code == POSTINCREMENT_EXPR)
				    ? lv_increment
				    : lv_decrement)))
	أرجع error_mark_node;

      𐤀𐤌 (warn_cxx_compat && TREE_CODE (TREE_TYPE (arg)) == ENUMERAL_TYPE)
	{
	  𐤀𐤌 (code == PREINCREMENT_EXPR || code == POSTINCREMENT_EXPR)
	    warning_at (location, OPT_Wc___compat,
			"increment of enumeration value is invalid in C++");
	  وإلا
	    warning_at (location, OPT_Wc___compat,
			"decrement of enumeration value is invalid in C++");
	}

      𐤀𐤌 (C_BOOLEAN_TYPE_P (TREE_TYPE (arg)))
	{
	  𐤀𐤌 (code == PREINCREMENT_EXPR || code == POSTINCREMENT_EXPR)
	    warning_at (location, OPT_Wbool_operation,
			"increment of a boolean expression");
	  وإلا
	    warning_at (location, OPT_Wbool_operation,
			"decrement of a boolean expression");
	}

      /* Ensure the argument is fully folded inside any SAVE_EXPR.  */
      arg = c_fully_fold (arg, خطأ, عدم, true);

      منطقي atomic_op;
      atomic_op = really_atomic_lvalue (arg);

      /* Increment or decrement the real part of the value,
	 and don't change the imaginary part.  */
      𐤀𐤌 (typecode == COMPLEX_TYPE)
	{
	  tree real, imag;

	  pedwarn_c23 (location, OPT_Wpedantic,
		       "ISO C does not support %<++%> and %<--%> on complex "
		       "types before C2Y");

	  𐤀𐤌 (!atomic_op)
	    {
	      arg = stabilize_reference (arg);
	      real = build_unary_op (EXPR_LOCATION (arg), REALPART_EXPR, arg,
				     true);
	      imag = build_unary_op (EXPR_LOCATION (arg), IMAGPART_EXPR, arg,
				     true);
	      real = build_unary_op (EXPR_LOCATION (arg), code, real, true);
	      𐤀𐤌 (real == error_mark_node || imag == error_mark_node)
		أرجع error_mark_node;
	      ret = build2 (COMPLEX_EXPR, TREE_TYPE (arg),
			    real, imag);
	      اذهب return_build_unary_op;
	    }
	}

      /* Report invalid types.  */

      𐤀𐤌 (typecode != POINTER_TYPE && typecode != FIXED_POINT_TYPE
	  && typecode != INTEGER_TYPE && typecode != REAL_TYPE
	  && typecode != COMPLEX_TYPE && typecode != BITINT_TYPE
	  && !gnu_vector_type_p (TREE_TYPE (arg)))
	{
	  𐤀𐤌 (code == PREINCREMENT_EXPR || code == POSTINCREMENT_EXPR)
	    error_at (location, "wrong type argument to increment");
	  وإلا
	    error_at (location, "wrong type argument to decrement");

	  أرجع error_mark_node;
	}

      {
	tree inc;

	argtype = TREE_TYPE (arg);

	/* Compute the increment.  */

	𐤀𐤌 (typecode == POINTER_TYPE)
	  {
	    /* If pointer target is an incomplete type,
	       we just cannot know how to do the arithmetic.  */
	    𐤀𐤌 (!COMPLETE_OR_VOID_TYPE_P (TREE_TYPE (argtype)))
	      {
		𐤀𐤌 (code == PREINCREMENT_EXPR || code == POSTINCREMENT_EXPR)
		  error_at (location,
			    "increment of pointer to an incomplete type %qT",
			    TREE_TYPE (argtype));
		وإلا
		  error_at (location,
			    "decrement of pointer to an incomplete type %qT",
			    TREE_TYPE (argtype));
	      }
	    وإلا 𐤀𐤌 (TREE_CODE (TREE_TYPE (argtype)) == FUNCTION_TYPE
		     || VOID_TYPE_P (TREE_TYPE (argtype)))
	      {
		𐤀𐤌 (code == PREINCREMENT_EXPR || code == POSTINCREMENT_EXPR)
		  pedwarn (location, OPT_Wpointer_arith,
			   "wrong type argument to increment");
		وإلا
		  pedwarn (location, OPT_Wpointer_arith,
			   "wrong type argument to decrement");
	      }
	    وإلا
	      verify_type_context (location, TCTX_POINTER_ARITH,
				   TREE_TYPE (argtype));

	    inc = c_size_in_bytes (TREE_TYPE (argtype));
	    inc = convert_to_ptrofftype_loc (location, inc);
	  }
	وإلا 𐤀𐤌 (FRACT_MODE_P (TYPE_MODE (argtype)))
	  {
	    /* For signed fract types, we invert ++ to -- or
	       -- to ++, and change inc from 1 to -1, because
	       it is not possible to represent 1 in signed fract constants.
	       For unsigned fract types, the result always overflows and
	       we get an undefined (original) or the maximum value.  */
	    𐤀𐤌 (code == PREINCREMENT_EXPR)
	      code = PREDECREMENT_EXPR;
	    وإلا 𐤀𐤌 (code == PREDECREMENT_EXPR)
	      code = PREINCREMENT_EXPR;
	    وإلا 𐤀𐤌 (code == POSTINCREMENT_EXPR)
	      code = POSTDECREMENT_EXPR;
	    وإلا /* code == POSTDECREMENT_EXPR  */
	      code = POSTINCREMENT_EXPR;

	    inc = integer_minus_one_node;
	    inc = convert (argtype, inc);
	  }
	وإلا
	  {
	    inc = VECTOR_TYPE_P (argtype)
	      ? build_one_cst (argtype)
	      : integer_one_node;
	    inc = convert (argtype, inc);
	  }

	/* If 'arg' is an Objective-C PROPERTY_REF expression, then we
	   need to ask Objective-C to build the increment or decrement
	   expression for it.  */
	𐤀𐤌 (objc_is_property_ref (arg))
	  أرجع objc_build_incr_expr_for_property_ref (location, code,
							arg, inc);

	/* Report a read-only lvalue.  */
	𐤀𐤌 (TYPE_READONLY (argtype))
	  {
	    readonly_error (location, arg,
			    ((code == PREINCREMENT_EXPR
			      || code == POSTINCREMENT_EXPR)
			     ? lv_increment : lv_decrement));
	    أرجع error_mark_node;
	  }
	وإلا 𐤀𐤌 (TREE_READONLY (arg))
	  readonly_warning (arg,
			    ((code == PREINCREMENT_EXPR
			      || code == POSTINCREMENT_EXPR)
			     ? lv_increment : lv_decrement));

	/* If the argument is atomic, use the special code sequences for
	   atomic compound assignment.  */
	𐤀𐤌 (atomic_op)
	  {
	    arg = stabilize_reference (arg);
	    ret = build_atomic_assign (location, arg,
				       ((code == PREINCREMENT_EXPR
					 || code == POSTINCREMENT_EXPR)
					? PLUS_EXPR
					: MINUS_EXPR),
				       (FRACT_MODE_P (TYPE_MODE (argtype))
					? inc
					: integer_one_node),
				       (code == POSTINCREMENT_EXPR
					|| code == POSTDECREMENT_EXPR));
	    اذهب return_build_unary_op;
	  }

	tree true_res;
	𐤀𐤌 (c_hardbool_type_attr (TREE_TYPE (arg), عدم, &true_res))
	  {
	    tree larg = stabilize_reference (arg);
	    tree sarg = save_expr (larg);
	    بدل (code)
	      {
	      حالة PREINCREMENT_EXPR:
		val = build2 (MODIFY_EXPR, TREE_TYPE (larg), larg, true_res);
		val = build2 (COMPOUND_EXPR, TREE_TYPE (larg), sarg, val);
		اكسر;
	      حالة POSTINCREMENT_EXPR:
		val = build2 (MODIFY_EXPR, TREE_TYPE (larg), larg, true_res);
		val = build2 (COMPOUND_EXPR, TREE_TYPE (larg), val, sarg);
		val = build2 (COMPOUND_EXPR, TREE_TYPE (larg), sarg, val);
		اكسر;
	      حالة PREDECREMENT_EXPR:
		{
		  tree rarg = convert_lvalue_to_rvalue (location, sarg,
							true, true);
		  rarg = invert_truthvalue_loc (location, rarg);
		  rarg = convert (TREE_TYPE (sarg), rarg);
		  val = build2 (MODIFY_EXPR, TREE_TYPE (larg), larg, rarg);
		}
		اكسر;
	      حالة POSTDECREMENT_EXPR:
		{
		  tree rarg = convert_lvalue_to_rvalue (location, sarg,
							true, true);
		  rarg = invert_truthvalue_loc (location, rarg);
		  tree iarg = convert (TREE_TYPE (larg), rarg);
		  val = build2 (MODIFY_EXPR, TREE_TYPE (larg), larg, iarg);
		  val = build2 (COMPOUND_EXPR, TREE_TYPE (larg), val, sarg);
		  val = build2 (COMPOUND_EXPR, TREE_TYPE (larg), sarg, val);
		}
		اكسر;
	      افتراضي:
		gcc_unreachable ();
	      }
	    TREE_SIDE_EFFECTS (val) = 1;
	  }
	وإلا 𐤀𐤌 (C_BOOLEAN_TYPE_P (TREE_TYPE (arg)))
	  val = boolean_increment (code, arg);
	وإلا
	  val = build2 (code, TREE_TYPE (arg), arg, inc);
	TREE_SIDE_EFFECTS (val) = 1;
	𐤀𐤌 (TYPE_QUALS (TREE_TYPE (val)) != TYPE_UNQUALIFIED)
	  TREE_TYPE (val) = c_build_qualified_type (TREE_TYPE (val),
						    TYPE_UNQUALIFIED);
	ret = val;
	اذهب return_build_unary_op;
      }

    حالة ADDR_EXPR:
      /* Note that this operation never does default_conversion.  */

      /* The operand of unary '&' must be an lvalue (which excludes
	 expressions of type void), or, in C99, the result of a [] or
	 unary '*' operator.  */
      𐤀𐤌 (VOID_TYPE_P (TREE_TYPE (arg))
	  && TYPE_QUALS (TREE_TYPE (arg)) == TYPE_UNQUALIFIED
	  && (!INDIRECT_REF_P (arg) || !flag_isoc99))
	pedwarn (location, 0, "taking address of expression of type %<void%>");

      /* Let &* cancel out to simplify resulting code.  */
      𐤀𐤌 (INDIRECT_REF_P (arg))
	{
	  /* Don't let this be an lvalue.  */
	  𐤀𐤌 (lvalue_p (TREE_OPERAND (arg, 0)))
	    أرجع non_lvalue_loc (location, TREE_OPERAND (arg, 0));
	  ret = TREE_OPERAND (arg, 0);
	  اذهب return_build_unary_op;
	}

      /* Anything not already handled and not a true memory reference
	 or a non-lvalue array is an error.  */
      𐤀𐤌 (typecode != FUNCTION_TYPE && !noconvert
	  && !lvalue_or_else (location, arg, lv_addressof))
	أرجع error_mark_node;

      /* Move address operations inside C_MAYBE_CONST_EXPR to simplify
	 folding later.  */
      𐤀𐤌 (TREE_CODE (arg) == C_MAYBE_CONST_EXPR)
	{
	  tree inner = build_unary_op (location, code,
				       C_MAYBE_CONST_EXPR_EXPR (arg),
				       noconvert);
	  ret = build2 (C_MAYBE_CONST_EXPR, TREE_TYPE (inner),
			C_MAYBE_CONST_EXPR_PRE (arg), inner);
	  gcc_assert (!C_MAYBE_CONST_EXPR_INT_OPERANDS (arg));
	  C_MAYBE_CONST_EXPR_NON_CONST (ret)
	    = C_MAYBE_CONST_EXPR_NON_CONST (arg);
	  اذهب return_build_unary_op;
	}

      /* Ordinary case; arg is a COMPONENT_REF or a decl.  */

      argtype = TREE_TYPE (arg);

      /* If the lvalue is const or volatile, merge that into the type
	 to which the address will point.  This is only needed
	 for function types.  */
      𐤀𐤌 ((DECL_P (arg) || REFERENCE_CLASS_P (arg))
	  && (TREE_READONLY (arg) || TREE_THIS_VOLATILE (arg))
	  && TREE_CODE (argtype) == FUNCTION_TYPE)
	{
	  صحيح orig_quals = TYPE_QUALS (strip_array_types (argtype));
	  صحيح quals = orig_quals;

	  𐤀𐤌 (TREE_READONLY (arg))
	    quals |= TYPE_QUAL_CONST;
	  𐤀𐤌 (TREE_THIS_VOLATILE (arg))
	    quals |= TYPE_QUAL_VOLATILE;

	  argtype = c_build_qualified_type (argtype, quals);
	}

      بدل (TREE_CODE (arg))
	{
	حالة COMPONENT_REF:
	  𐤀𐤌 (DECL_C_BIT_FIELD (TREE_OPERAND (arg, 1)))
	    {
	      error_at (location, "cannot take address of bit-field %qD",
			TREE_OPERAND (arg, 1));
	      أرجع error_mark_node;
	    }

	  /* fall through */

	حالة ARRAY_REF:
	  𐤀𐤌 (TYPE_REVERSE_STORAGE_ORDER (TREE_TYPE (TREE_OPERAND (arg, 0))))
	    {
	      𐤀𐤌 (!AGGREGATE_TYPE_P (TREE_TYPE (arg))
		  && !POINTER_TYPE_P (TREE_TYPE (arg))
		  && !VECTOR_TYPE_P (TREE_TYPE (arg)))
		{
		  error_at (location, "cannot take address of scalar with "
			    "reverse storage order");
		  أرجع error_mark_node;
		}

	      𐤀𐤌 (TREE_CODE (TREE_TYPE (arg)) == ARRAY_TYPE
		  && TYPE_REVERSE_STORAGE_ORDER (TREE_TYPE (arg)))
		warning_at (location, OPT_Wscalar_storage_order,
			    "address of array with reverse scalar storage "
			    "order requested");
	    }

	افتراضي:
	  اكسر;
	}

      𐤀𐤌 (!c_mark_addressable (arg))
	أرجع error_mark_node;

      gcc_assert (TREE_CODE (arg) != COMPONENT_REF
		  || !DECL_C_BIT_FIELD (TREE_OPERAND (arg, 1)));

      argtype = c_build_pointer_type (argtype);

      /* ??? Cope with user tricks that amount to offsetof.  Delete this
	 when we have proper support for integer constant expressions.  */
      val = get_base_address (arg);
      𐤀𐤌 (val && INDIRECT_REF_P (val)
          && TREE_CONSTANT (TREE_OPERAND (val, 0)))
	{
	  ret = fold_offsetof (arg, argtype);
	  اذهب return_build_unary_op;
	}

      val = build1 (ADDR_EXPR, argtype, arg);

      ret = val;
      اذهب return_build_unary_op;

    حالة PAREN_EXPR:
      ret = build1 (code, TREE_TYPE (arg), arg);
      اذهب return_build_unary_op;

    افتراضي:
      gcc_unreachable ();
    }

  𐤀𐤌 (argtype == NULL_TREE)
    argtype = TREE_TYPE (arg);
  𐤀𐤌 (TREE_CODE (arg) == INTEGER_CST)
    ret = (require_constant_value
	   ? fold_build1_initializer_loc (location, code, argtype, arg)
	   : fold_build1_loc (location, code, argtype, arg));
  وإلا
    ret = build1 (code, argtype, arg);
 return_build_unary_op:
  gcc_assert (ret != error_mark_node);
  𐤀𐤌 (TREE_CODE (ret) == INTEGER_CST && !TREE_OVERFLOW (ret)
      && !(TREE_CODE (xarg) == INTEGER_CST && !TREE_OVERFLOW (xarg)))
    ret = build1 (NOP_EXPR, TREE_TYPE (ret), ret);
  وإلا 𐤀𐤌 (TREE_CODE (ret) != INTEGER_CST && int_operands)
    ret = note_integer_operands (ret);
  𐤀𐤌 (eptype)
    ret = build1 (EXCESS_PRECISION_EXPR, eptype, ret);
  protected_set_expr_location (ret, location);
  أرجع ret;
}

/* Return nonzero if REF is an lvalue valid for this language.
   Lvalues can be assigned, unless their type has TYPE_READONLY.
   Lvalues can have their address taken, unless they have C_DECL_REGISTER.  */

منطقي
lvalue_p (const_tree ref)
{
  ثابت تعداد tree_code code = TREE_CODE (ref);

  بدل (code)
    {
    حالة REALPART_EXPR:
    حالة IMAGPART_EXPR:
    حالة COMPONENT_REF:
      أرجع lvalue_p (TREE_OPERAND (ref, 0));

    حالة C_MAYBE_CONST_EXPR:
      أرجع lvalue_p (TREE_OPERAND (ref, 1));

    حالة COMPOUND_LITERAL_EXPR:
    حالة STRING_CST:
      أرجع true;

    حالة MEM_REF:
    حالة TARGET_MEM_REF:
      /* MEM_REFs can appear from -fgimple parsing or folding, so allow them
	 here as well.  */
    حالة INDIRECT_REF:
    حالة ARRAY_REF:
    حالة VAR_DECL:
    حالة PARM_DECL:
    حالة RESULT_DECL:
    حالة ERROR_MARK:
      أرجع (TREE_CODE (TREE_TYPE (ref)) != FUNCTION_TYPE
	      && TREE_CODE (TREE_TYPE (ref)) != METHOD_TYPE);

    حالة BIND_EXPR:
      أرجع TREE_CODE (TREE_TYPE (ref)) == ARRAY_TYPE;

    حالة CALL_EXPR:
      أرجع is_access_with_size_p (ref);

    افتراضي:
      أرجع خطأ;
    }
}

/* Give a warning for storing in something that is read-only in GCC
   terms but not const in ISO C terms.  */

ساكن فراغ
readonly_warning (tree arg, تعداد lvalue_use use)
{
  بدل (use)
    {
    حالة lv_assign:
      warning (0, "assignment of read-only location %qE", arg);
      اكسر;
    حالة lv_increment:
      warning (0, "increment of read-only location %qE", arg);
      اكسر;
    حالة lv_decrement:
      warning (0, "decrement of read-only location %qE", arg);
      اكسر;
    افتراضي:
      gcc_unreachable ();
    }
  أرجع;
}


/* Return nonzero if REF is an lvalue valid for this language;
   otherwise, print an error message and return zero.  USE says
   how the lvalue is being used and so selects the error message.
   LOCATION is the location at which any error should be reported.  */

ساكن صحيح
lvalue_or_else (location_t loc, const_tree ref, تعداد lvalue_use use)
{
  صحيح win = lvalue_p (ref);

  𐤀𐤌 (!win)
    lvalue_error (loc, use);

  أرجع win;
}

/* Mark EXP saying that we need to be able to take the
   address of it; it should not be allocated in a register.
   Returns true if successful.  ARRAY_REF_P is true if this
   is for ARRAY_REF construction - in that case we don't want
   to look through VIEW_CONVERT_EXPR from VECTOR_TYPE to ARRAY_TYPE,
   it is fine to use ARRAY_REFs for vector subscripts on vector
   register variables.  If OVERRIDE_REGISTER, clear DECL_REGISTER rather
   than producing an error for taking the address of a register.  */

منطقي
c_mark_addressable (tree exp, منطقي array_ref_p, منطقي override_register)
{
  tree x = exp;

  طالما (1)
    بدل (TREE_CODE (x))
      {
      حالة VIEW_CONVERT_EXPR:
	𐤀𐤌 (array_ref_p
	    && TREE_CODE (TREE_TYPE (x)) == ARRAY_TYPE
	    && VECTOR_TYPE_P (TREE_TYPE (TREE_OPERAND (x, 0))))
	  أرجع true;
	x = TREE_OPERAND (x, 0);
	اكسر;

      حالة COMPONENT_REF:
	𐤀𐤌 (DECL_C_BIT_FIELD (TREE_OPERAND (x, 1)))
	  {
	    error ("cannot take address of bit-field %qD",
		   TREE_OPERAND (x, 1));
	    أرجع خطأ;
	  }
	/* FALLTHRU */
      حالة ADDR_EXPR:
      حالة ARRAY_REF:
      حالة REALPART_EXPR:
      حالة IMAGPART_EXPR:
	x = TREE_OPERAND (x, 0);
	اكسر;

      حالة COMPOUND_LITERAL_EXPR:
	𐤀𐤌 (C_DECL_REGISTER (COMPOUND_LITERAL_EXPR_DECL (x)))
	  {
	    𐤀𐤌 (override_register)
	      DECL_REGISTER (COMPOUND_LITERAL_EXPR_DECL (x)) = 0;
	    وإلا
	      {
		error ("address of register compound literal requested");
		أرجع خطأ;
	      }
	  }
	TREE_ADDRESSABLE (x) = 1;
	TREE_ADDRESSABLE (COMPOUND_LITERAL_EXPR_DECL (x)) = 1;
	أرجع true;

      حالة CONSTRUCTOR:
	TREE_ADDRESSABLE (x) = 1;
	أرجع true;

      حالة VAR_DECL:
      حالة CONST_DECL:
      حالة PARM_DECL:
      حالة RESULT_DECL:
	𐤀𐤌 (C_DECL_REGISTER (x)
	    && DECL_NONLOCAL (x))
	  {
	    𐤀𐤌 (TREE_PUBLIC (x) || is_global_var (x))
	      {
		error
		  ("global register variable %qD used in nested function", x);
		أرجع خطأ;
	      }
	    pedwarn (input_location, 0, "register variable %qD used in nested function", x);
	  }
	وإلا 𐤀𐤌 (C_DECL_REGISTER (x))
	  {
	    𐤀𐤌 (TREE_PUBLIC (x) || is_global_var (x))
	      error ("address of global register variable %qD requested", x);
	    وإلا 𐤀𐤌 (override_register && !DECL_HARD_REGISTER (x))
	      {
		DECL_REGISTER (x) = 0;
		TREE_ADDRESSABLE (x) = 1;
		mark_decl_used (x, true);
		أرجع true;
	      }
	    وإلا
	      error ("address of register variable %qD requested", x);
	    أرجع خطأ;
	  }

	/* FALLTHRU */
      حالة FUNCTION_DECL:
	TREE_ADDRESSABLE (x) = 1;
	mark_decl_used (x, true);
	/* FALLTHRU */
      افتراضي:
	أرجع true;
    }
}

/* Convert EXPR to TYPE, warning about conversion problems with
   constants.  SEMANTIC_TYPE is the type this conversion would use
   without excess precision. If SEMANTIC_TYPE is NULL, this function
   is equivalent to convert_and_check. This function is a wrapper that
   handles conversions that may be different than
   the usual ones because of excess precision.  */

ساكن tree
ep_convert_and_check (location_t loc, tree type, tree expr,
		      tree semantic_type)
{
  𐤀𐤌 (TREE_TYPE (expr) == type)
    أرجع expr;

  /* For C11, integer conversions may have results with excess
     precision.  */
  𐤀𐤌 (flag_isoc11 || !semantic_type)
    أرجع convert_and_check (loc, type, expr);

  𐤀𐤌 (TREE_CODE (TREE_TYPE (expr)) == INTEGER_TYPE
      && TREE_TYPE (expr) != semantic_type)
    {
      /* For integers, we need to check the real conversion, not
	 the conversion to the excess precision type.  */
      expr = convert_and_check (loc, semantic_type, expr);
    }
  /* Result type is the excess precision type, which should be
     large enough, so do not check.  */
  أرجع convert (type, expr);
}

/* If EXPR refers to a built-in declared without a prototype returns
   the actual type of the built-in and, if non-null, set *BLTIN to
   a pointer to the built-in.  Otherwise return the type of EXPR
   and clear *BLTIN if non-null.  */

ساكن tree
type_or_builtin_type (tree expr, tree *bltin = عدم)
{
  tree dummy;
  𐤀𐤌 (!bltin)
    bltin = &dummy;

  *bltin = NULL_TREE;

  tree type = TREE_TYPE (expr);
  𐤀𐤌 (TREE_CODE (expr) != ADDR_EXPR)
    أرجع type;

  tree oper = TREE_OPERAND (expr, 0);
  𐤀𐤌 (!DECL_P (oper)
      || TREE_CODE (oper) != FUNCTION_DECL
      || !fndecl_built_in_p (oper, BUILT_IN_NORMAL))
    أرجع type;

  built_in_function code = DECL_FUNCTION_CODE (oper);
  𐤀𐤌 (!C_DECL_BUILTIN_PROTOTYPE (oper))
    أرجع type;

  𐤀𐤌 ((*bltin = builtin_decl_implicit (code)))
    type = c_build_pointer_type (TREE_TYPE (*bltin));

  أرجع type;
}

/* Build and return a conditional expression IFEXP ? OP1 : OP2.  If
   IFEXP_BCP then the condition is a call to __builtin_constant_p, and
   if folded to an integer constant then the unselected half may
   contain arbitrary operations not normally permitted in constant
   expressions.  Set the location of the expression to LOC.  */

tree
build_conditional_expr (location_t colon_loc, tree ifexp, منطقي ifexp_bcp,
			tree op1, tree op1_original_type, location_t op1_loc,
			tree op2, tree op2_original_type, location_t op2_loc)
{
  tree type1;
  tree type2;
  tree result_type = عدم;
  tree semantic_result_type = عدم;
  tree orig_op1 = op1, orig_op2 = op2;
  منطقي int_const, op1_int_operands, op2_int_operands, int_operands;
  منطقي ifexp_int_operands;
  tree ret;

  op1_int_operands = EXPR_INT_CONST_OPERANDS (orig_op1);
  𐤀𐤌 (op1_int_operands)
    op1 = remove_c_maybe_const_expr (op1);
  op2_int_operands = EXPR_INT_CONST_OPERANDS (orig_op2);
  𐤀𐤌 (op2_int_operands)
    op2 = remove_c_maybe_const_expr (op2);
  ifexp_int_operands = EXPR_INT_CONST_OPERANDS (ifexp);
  𐤀𐤌 (ifexp_int_operands)
    ifexp = remove_c_maybe_const_expr (ifexp);

  /* Promote both alternatives.  */

  𐤀𐤌 (TREE_CODE (TREE_TYPE (op1)) != VOID_TYPE)
    op1 = default_conversion (op1);
  𐤀𐤌 (TREE_CODE (TREE_TYPE (op2)) != VOID_TYPE)
    op2 = default_conversion (op2);

  𐤀𐤌 (TREE_CODE (ifexp) == ERROR_MARK
      || TREE_CODE (TREE_TYPE (op1)) == ERROR_MARK
      || TREE_CODE (TREE_TYPE (op2)) == ERROR_MARK)
    أرجع error_mark_node;

  tree bltin1 = NULL_TREE;
  tree bltin2 = NULL_TREE;
  type1 = type_or_builtin_type (op1, &bltin1);
  ثابت تعداد tree_code code1 = TREE_CODE (type1);
  type2 = type_or_builtin_type (op2, &bltin2);
  ثابت تعداد tree_code code2 = TREE_CODE (type2);

  𐤀𐤌 (code1 == POINTER_TYPE && reject_gcc_builtin (op1))
    أرجع error_mark_node;

  𐤀𐤌 (code2 == POINTER_TYPE && reject_gcc_builtin (op2))
    أرجع error_mark_node;

  /* C90 does not permit non-lvalue arrays in conditional expressions.
     In C99 they will be pointers by now.  */
  𐤀𐤌 (code1 == ARRAY_TYPE || code2 == ARRAY_TYPE)
    {
      error_at (colon_loc, "non-lvalue array in conditional expression");
      أرجع error_mark_node;
    }

  𐤀𐤌 ((TREE_CODE (op1) == EXCESS_PRECISION_EXPR
       || TREE_CODE (op2) == EXCESS_PRECISION_EXPR)
      && (code1 == INTEGER_TYPE || code1 == REAL_TYPE
	  || code1 == COMPLEX_TYPE || code1 == BITINT_TYPE)
      && (code2 == INTEGER_TYPE || code2 == REAL_TYPE
	  || code2 == COMPLEX_TYPE || code2 == BITINT_TYPE))
    {
      semantic_result_type = c_common_type (type1, type2);
      𐤀𐤌 (TREE_CODE (op1) == EXCESS_PRECISION_EXPR)
	{
	  op1 = TREE_OPERAND (op1, 0);
	  type1 = TREE_TYPE (op1);
	  gcc_assert (TREE_CODE (type1) == code1);
	}
      𐤀𐤌 (TREE_CODE (op2) == EXCESS_PRECISION_EXPR)
	{
	  op2 = TREE_OPERAND (op2, 0);
	  type2 = TREE_TYPE (op2);
	  gcc_assert (TREE_CODE (type2) == code2);
	}
    }

  𐤀𐤌 (warn_cxx_compat)
    {
      tree t1 = op1_original_type ? op1_original_type : TREE_TYPE (orig_op1);
      tree t2 = op2_original_type ? op2_original_type : TREE_TYPE (orig_op2);

      𐤀𐤌 (TREE_CODE (t1) == ENUMERAL_TYPE
	  && TREE_CODE (t2) == ENUMERAL_TYPE
	  && TYPE_MAIN_VARIANT (t1) != TYPE_MAIN_VARIANT (t2))
	warning_at (colon_loc, OPT_Wc___compat,
		    "different enum types in conditional is "
		    "invalid in C++: %qT vs %qT", t1, t2);
    }

  𐤀𐤌 (warn_zero_as_null_pointer_constant
      && c_inhibit_evaluation_warnings == 0)
    {
      𐤀𐤌 ((code1 == POINTER_TYPE || code1 == NULLPTR_TYPE)
	  && INTEGRAL_TYPE_P (type2) && null_pointer_constant_p (orig_op2))
	warning_at (op2_loc, OPT_Wzero_as_null_pointer_constant,
		    "zero as null pointer constant");

      𐤀𐤌 ((code2 == POINTER_TYPE || code2 == NULLPTR_TYPE)
	  && INTEGRAL_TYPE_P (type1) && null_pointer_constant_p (orig_op1))
	warning_at (op1_loc, OPT_Wzero_as_null_pointer_constant,
		    "zero as null pointer constant");
    }

  /* Quickly detect the usual case where op1 and op2 have the same type
     after promotion.  */
  𐤀𐤌 (TYPE_MAIN_VARIANT (type1) == TYPE_MAIN_VARIANT (type2))
    {
      𐤀𐤌 (type1 == type2)
	result_type = type1;
      وإلا
	result_type = TYPE_MAIN_VARIANT (type1);
    }
  وإلا 𐤀𐤌 ((code1 == INTEGER_TYPE || code1 == REAL_TYPE
	    || code1 == COMPLEX_TYPE || code1 == BITINT_TYPE)
	   && (code2 == INTEGER_TYPE || code2 == REAL_TYPE
	       || code2 == COMPLEX_TYPE || code2 == BITINT_TYPE))
    {
      /* In C11, a conditional expression between a floating-point
	 type and an integer type should convert the integer type to
	 the evaluation format of the floating-point type, with
	 possible excess precision.  */
      tree eptype1 = type1;
      tree eptype2 = type2;
      𐤀𐤌 (flag_isoc11)
	{
	  tree eptype;
	  𐤀𐤌 (ANY_INTEGRAL_TYPE_P (type1)
	      && (eptype = excess_precision_type (type2)) != NULL_TREE)
	    {
	      eptype2 = eptype;
	      𐤀𐤌 (!semantic_result_type)
		semantic_result_type = c_common_type (type1, type2);
	    }
	  وإلا 𐤀𐤌 (ANY_INTEGRAL_TYPE_P (type2)
		   && (eptype = excess_precision_type (type1)) != NULL_TREE)
	    {
	      eptype1 = eptype;
	      𐤀𐤌 (!semantic_result_type)
		semantic_result_type = c_common_type (type1, type2);
	    }
	}
      result_type = c_common_type (eptype1, eptype2);
      𐤀𐤌 (result_type == error_mark_node)
	أرجع error_mark_node;
      do_warn_double_promotion (result_type, type1, type2,
				"implicit conversion from %qT to %qT to "
				"match other result of conditional",
				colon_loc);

      /* If -Wsign-compare, warn here if type1 and type2 have
	 different signedness.  We'll promote the signed to unsigned
	 and later code won't know it used to be different.
	 Do this check on the original types, so that explicit casts
	 will be considered, but default promotions won't.  */
      𐤀𐤌 (c_inhibit_evaluation_warnings == 0)
	{
	  صحيح unsigned_op1 = TYPE_UNSIGNED (TREE_TYPE (orig_op1));
	  صحيح unsigned_op2 = TYPE_UNSIGNED (TREE_TYPE (orig_op2));

	  𐤀𐤌 (unsigned_op1 ^ unsigned_op2)
	    {
	      /* Do not warn if the result type is signed, since the
		 signed type will only be chosen if it can represent
		 all the values of the unsigned type.  */
	      𐤀𐤌 (!TYPE_UNSIGNED (result_type))
		/* OK */;
	      وإلا
		{
		  منطقي op1_maybe_const = true;
		  منطقي op2_maybe_const = true;

		  /* Do not warn if the signed quantity is an
		     unsuffixed integer literal (or some static
		     constant expression involving such literals) and
		     it is non-negative.  This warning requires the
		     operands to be folded for best results, so do
		     that folding in this case even without
		     warn_sign_compare to avoid warning options
		     possibly affecting code generation.  */
		  c_inhibit_evaluation_warnings
		    += (ifexp == truthvalue_false_node);
		  op1 = c_fully_fold (op1, require_constant_value,
				      &op1_maybe_const);
		  c_inhibit_evaluation_warnings
		    -= (ifexp == truthvalue_false_node);

		  c_inhibit_evaluation_warnings
		    += (ifexp == truthvalue_true_node);
		  op2 = c_fully_fold (op2, require_constant_value,
				      &op2_maybe_const);
		  c_inhibit_evaluation_warnings
		    -= (ifexp == truthvalue_true_node);

		  𐤀𐤌 (warn_sign_compare)
		    {
		      𐤀𐤌 ((unsigned_op2
			   && tree_expr_nonnegative_p (op1))
			  || (unsigned_op1
			      && tree_expr_nonnegative_p (op2)))
			/* OK */;
		      وإلا 𐤀𐤌 (unsigned_op2)
			warning_at (op1_loc, OPT_Wsign_compare,
				    "operand of %<?:%> changes signedness from "
				    "%qT to %qT due to unsignedness of other "
				    "operand", TREE_TYPE (orig_op1),
				    TREE_TYPE (orig_op2));
		      وإلا
			warning_at (op2_loc, OPT_Wsign_compare,
				    "operand of %<?:%> changes signedness from "
				    "%qT to %qT due to unsignedness of other "
				    "operand", TREE_TYPE (orig_op2),
				    TREE_TYPE (orig_op1));
		    }
		  𐤀𐤌 (!op1_maybe_const || TREE_CODE (op1) != INTEGER_CST)
		    op1 = c_wrap_maybe_const (op1, !op1_maybe_const);
		  𐤀𐤌 (!op2_maybe_const || TREE_CODE (op2) != INTEGER_CST)
		    op2 = c_wrap_maybe_const (op2, !op2_maybe_const);
		}
	    }
	}
    }
  وإلا 𐤀𐤌 (code1 == VOID_TYPE || code2 == VOID_TYPE)
    {
      𐤀𐤌 (code1 != VOID_TYPE || code2 != VOID_TYPE)
	pedwarn (colon_loc, OPT_Wpedantic,
		 "ISO C forbids conditional expr with only one void side");
      result_type = void_type_node;
    }
  وإلا 𐤀𐤌 (code1 == POINTER_TYPE && code2 == POINTER_TYPE)
    {
      addr_space_t as1 = TYPE_ADDR_SPACE (TREE_TYPE (type1));
      addr_space_t as2 = TYPE_ADDR_SPACE (TREE_TYPE (type2));
      addr_space_t as_common;

      𐤀𐤌 (comp_target_types (colon_loc, type1, type2))
	{
	  ifexp = save_expr (ifexp);
	  result_type = common_pointer_type (type1, type2, ifexp);
	}
      وإلا 𐤀𐤌 (null_pointer_constant_p (orig_op1))
	result_type = type2;
      وإلا 𐤀𐤌 (null_pointer_constant_p (orig_op2))
	result_type = type1;
      وإلا 𐤀𐤌 (!addr_space_superset (as1, as2, &as_common))
	{
	  error_at (colon_loc, "pointers to disjoint address spaces "
		    "used in conditional expression");
	  أرجع error_mark_node;
	}
      وإلا 𐤀𐤌 ((VOID_TYPE_P (TREE_TYPE (type1))
		&& !TYPE_ATOMIC (TREE_TYPE (type1)))
	       || (VOID_TYPE_P (TREE_TYPE (type2))
		   && !TYPE_ATOMIC (TREE_TYPE (type2))))
	{
	  tree t1 = TREE_TYPE (type1);
	  tree t2 = TREE_TYPE (type2);
	  𐤀𐤌 (!(VOID_TYPE_P (t1)
		&& !TYPE_ATOMIC (t1)))
	   {
	     /* roles are swapped */
	     t1 = t2;
	     t2 = TREE_TYPE (type1);
	   }
	  tree t2_stripped = strip_array_types (t2);
	  𐤀𐤌 ((TREE_CODE (t2) == ARRAY_TYPE)
	      && (TYPE_QUALS (t2_stripped) & ~TYPE_QUALS (t1)))
	    {
	      𐤀𐤌 (!flag_isoc23)
		warning_at (colon_loc, OPT_Wdiscarded_array_qualifiers,
			    "pointer to array loses qualifier "
			    "in conditional expression");
	      وإلا 𐤀𐤌 (warn_c11_c23_compat > 0)
		warning_at (colon_loc, OPT_Wc11_c23_compat,
			    "pointer to array loses qualifier "
			    "in conditional expression in ISO C before C23");
	    }
	  𐤀𐤌 (TREE_CODE (t2) == FUNCTION_TYPE)
	    pedwarn (colon_loc, OPT_Wpedantic,
		     "ISO C forbids conditional expr between "
		     "%<void *%> and function pointer");
	  /* for array, use qualifiers of element type */
	  𐤀𐤌 (flag_isoc23)
	    t2 = t2_stripped;
	  result_type = c_build_pointer_type (qualify_type (t1, t2));
	}
      /* Objective-C pointer comparisons are a bit more lenient.  */
      وإلا 𐤀𐤌 (objc_have_common_type (type1, type2, -3, NULL_TREE))
	result_type = objc_common_type (type1, type2);
      وإلا
	{
	  صحيح qual = ENCODE_QUAL_ADDR_SPACE (as_common);
	  تعداد diagnostics::kind kind = diagnostics::kind::permerror;
	  𐤀𐤌 (!flag_isoc99)
	    /* This downgrade to a warning ensures that -std=gnu89
	       -pedantic-errors does not flag these mismatches between
	       builtins as errors (as diagnostics::kind::permerror would)
	       ISO C99 and later do not have implicit function declarations,
	       so the mismatch cannot occur naturally there.  */
	    kind = (bltin1 && bltin2
		    ? diagnostics::kind::warning
		    : diagnostics::kind::pedwarn);
	  𐤀𐤌 (emit_diagnostic (kind, colon_loc, OPT_Wincompatible_pointer_types,
			       "pointer type mismatch "
			       "in conditional expression"))
	    {
	      inform (op1_loc, "first expression has type %qT", type1);
	      inform (op2_loc, "second expression has type %qT", type2);
	    }
	  result_type = c_build_pointer_type
			  (c_build_qualified_type (void_type_node, qual));
	}
    }
  وإلا 𐤀𐤌 (code1 == POINTER_TYPE
	   && (code2 == INTEGER_TYPE || code2 == BITINT_TYPE))
    {
      𐤀𐤌 (!null_pointer_constant_p (orig_op2))
	permerror_opt (colon_loc, OPT_Wint_conversion,
		       "pointer/integer type mismatch "
		       "in conditional expression");
      وإلا
	{
	  op2 = null_pointer_node;
	}
      result_type = type1;
    }
  وإلا 𐤀𐤌 (code2 == POINTER_TYPE
	   && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
    {
      𐤀𐤌 (!null_pointer_constant_p (orig_op1))
	permerror_opt (colon_loc, OPT_Wint_conversion,
		       "pointer/integer type mismatch "
		       "in conditional expression");
      وإلا
	{
	  op1 = null_pointer_node;
	}
      result_type = type2;
    }
  /* 6.5.15: "if one is a null pointer constant (other than a pointer) or has
     type nullptr_t and the other is a pointer, the result type is the pointer
     type."  */
  وإلا 𐤀𐤌 (code1 == NULLPTR_TYPE && code2 == POINTER_TYPE)
    result_type = type2;
  وإلا 𐤀𐤌 (code1 == POINTER_TYPE && code2 == NULLPTR_TYPE)
    result_type = type1;
  وإلا 𐤀𐤌 (RECORD_OR_UNION_TYPE_P (type1) && RECORD_OR_UNION_TYPE_P (type2)
	   && comptypes (TYPE_MAIN_VARIANT (type1),
			 TYPE_MAIN_VARIANT (type2)))
    result_type = composite_type (TYPE_MAIN_VARIANT (type1),
				  TYPE_MAIN_VARIANT (type2));

  𐤀𐤌 (!result_type)
    {
      𐤀𐤌 (flag_cond_mismatch)
	result_type = void_type_node;
      وإلا
	{
	  error_at (colon_loc, "type mismatch in conditional expression");
	  أرجع error_mark_node;
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

  𐤀𐤌 (ifexp_bcp && ifexp == truthvalue_true_node)
    {
      op2_int_operands = true;
      op1 = c_fully_fold (op1, require_constant_value, عدم);
    }
  𐤀𐤌 (ifexp_bcp && ifexp == truthvalue_false_node)
    {
      op1_int_operands = true;
      op2 = c_fully_fold (op2, require_constant_value, عدم);
    }
  int_const = int_operands = (ifexp_int_operands
			      && op1_int_operands
			      && op2_int_operands);
  𐤀𐤌 (int_operands)
    {
      int_const = ((ifexp == truthvalue_true_node
		    && TREE_CODE (orig_op1) == INTEGER_CST
		    && !TREE_OVERFLOW (orig_op1))
		   || (ifexp == truthvalue_false_node
		       && TREE_CODE (orig_op2) == INTEGER_CST
		       && !TREE_OVERFLOW (orig_op2)));
    }

  /* Need to convert condition operand into a vector mask.  */
  𐤀𐤌 (VECTOR_TYPE_P (TREE_TYPE (ifexp)))
    {
      tree vectype = TREE_TYPE (ifexp);
      tree elem_type = TREE_TYPE (vectype);
      tree zero = build_int_cst (elem_type, 0);
      tree zero_vec = build_vector_from_val (vectype, zero);
      tree cmp_type = truth_type_for (vectype);
      ifexp = build2 (NE_EXPR, cmp_type, ifexp, zero_vec);
    }

  𐤀𐤌 (int_const || (ifexp_bcp && TREE_CODE (ifexp) == INTEGER_CST))
    ret = fold_build3_loc (colon_loc, COND_EXPR, result_type, ifexp, op1, op2);
  وإلا
    {
      𐤀𐤌 (int_operands)
	{
	  /* Use c_fully_fold here, since C_MAYBE_CONST_EXPR might be
	     nested inside of the expression.  */
	  op1 = c_fully_fold (op1, خطأ, عدم);
	  op2 = c_fully_fold (op2, خطأ, عدم);
	}
      ret = build3 (COND_EXPR, result_type, ifexp, op1, op2);
      𐤀𐤌 (int_operands)
	ret = note_integer_operands (ret);
    }
  𐤀𐤌 (semantic_result_type)
    ret = build1 (EXCESS_PRECISION_EXPR, semantic_result_type, ret);

  protected_set_expr_location (ret, colon_loc);

  /* If the OP1 and OP2 are the same and don't have side-effects,
     warn here, because the COND_EXPR will be turned into OP1.  */
  𐤀𐤌 (warn_duplicated_branches
      && TREE_CODE (ret) == COND_EXPR
      && (op1 == op2 || operand_equal_p (op1, op2, OEP_ADDRESS_OF_SAME_FIELD)))
    warning_at (EXPR_LOCATION (ret), OPT_Wduplicated_branches,
		"this condition has identical branches");

  أرجع ret;
}

/* EXPR is an expression, location LOC, whose result is discarded.
   Warn if it is a call to a nodiscard function (or a COMPOUND_EXPR
   whose right-hand operand is such a call, possibly recursively).  */

ساكن فراغ
maybe_warn_nodiscard (location_t loc, tree expr)
{
  𐤀𐤌 (VOID_TYPE_P (TREE_TYPE (expr)))
    أرجع;
  طالما (TREE_CODE (expr) == COMPOUND_EXPR)
    {
      expr = TREE_OPERAND (expr, 1);
      𐤀𐤌 (EXPR_HAS_LOCATION (expr))
	loc = EXPR_LOCATION (expr);
    }
  𐤀𐤌 (TREE_CODE (expr) != CALL_EXPR)
    أرجع;
  tree fn = CALL_EXPR_FN (expr);
  𐤀𐤌 (!fn)
    أرجع;
  tree attr;
  𐤀𐤌 (TREE_CODE (fn) == ADDR_EXPR
      && TREE_CODE (TREE_OPERAND (fn, 0)) == FUNCTION_DECL
      && (attr = lookup_attribute ("nodiscard",
				   DECL_ATTRIBUTES (TREE_OPERAND (fn, 0)))))
    {
      fn = TREE_OPERAND (fn, 0);
      tree args = TREE_VALUE (attr);
      𐤀𐤌 (args)
	args = TREE_VALUE (args);
      auto_diagnostic_group d;
      auto_urlify_attributes sentinel;
      صحيح warned;
      𐤀𐤌 (args)
	warned = warning_at (loc, OPT_Wunused_result,
			     "ignoring return value of %qD, declared with "
			     "attribute %<nodiscard%>: %E", fn, args);
      وإلا
	warned = warning_at (loc, OPT_Wunused_result,
			     "ignoring return value of %qD, declared with "
			     "attribute %<nodiscard%>", fn);
      𐤀𐤌 (warned)
	inform (DECL_SOURCE_LOCATION (fn), "declared here");
    }
  وإلا
    {
      tree rettype = TREE_TYPE (TREE_TYPE (TREE_TYPE (fn)));
      attr = lookup_attribute ("nodiscard", TYPE_ATTRIBUTES (rettype));
      𐤀𐤌 (!attr)
	أرجع;
      tree args = TREE_VALUE (attr);
      𐤀𐤌 (args)
	args = TREE_VALUE (args);
      auto_diagnostic_group d;
      auto_urlify_attributes sentinel;
      صحيح warned;
      𐤀𐤌 (args)
	warned = warning_at (loc, OPT_Wunused_result,
			     "ignoring return value of type %qT, declared "
			     "with attribute %<nodiscard%>: %E",
			     rettype, args);
      وإلا
	warned = warning_at (loc, OPT_Wunused_result,
			     "ignoring return value of type %qT, declared "
			     "with attribute %<nodiscard%>", rettype);
      𐤀𐤌 (warned)
	{
	  𐤀𐤌 (TREE_CODE (fn) == ADDR_EXPR)
	    {
	      fn = TREE_OPERAND (fn, 0);
	      𐤀𐤌 (TREE_CODE (fn) == FUNCTION_DECL)
		inform (DECL_SOURCE_LOCATION (fn),
			"in call to %qD, declared here", fn);
	    }
	}
    }
}

/* Return a compound expression that performs two expressions and
   returns the value of the second of them.

   LOC is the location of the COMPOUND_EXPR.  */

tree
build_compound_expr (location_t loc, tree expr1, tree expr2)
{
  منطقي expr1_int_operands, expr2_int_operands;
  tree eptype = NULL_TREE;
  tree ret;

  expr1_int_operands = EXPR_INT_CONST_OPERANDS (expr1);
  𐤀𐤌 (expr1_int_operands)
    expr1 = remove_c_maybe_const_expr (expr1);
  expr2_int_operands = EXPR_INT_CONST_OPERANDS (expr2);
  𐤀𐤌 (expr2_int_operands)
    expr2 = remove_c_maybe_const_expr (expr2);

  𐤀𐤌 (TREE_CODE (expr1) == EXCESS_PRECISION_EXPR)
    expr1 = TREE_OPERAND (expr1, 0);
  𐤀𐤌 (TREE_CODE (expr2) == EXCESS_PRECISION_EXPR)
    {
      eptype = TREE_TYPE (expr2);
      expr2 = TREE_OPERAND (expr2, 0);
    }

  𐤀𐤌 (!TREE_SIDE_EFFECTS (expr1))
    {
      /* The left-hand operand of a comma expression is like an expression
	 statement: with -Wunused, we should warn if it doesn't have
	 any side-effects, unless it was explicitly cast to (void).  */
      𐤀𐤌 (warn_unused_value)
	{
	  𐤀𐤌 (VOID_TYPE_P (TREE_TYPE (expr1))
	      && CONVERT_EXPR_P (expr1))
	    ; /* (void) a, b */
	  وإلا 𐤀𐤌 (VOID_TYPE_P (TREE_TYPE (expr1))
		   && TREE_CODE (expr1) == COMPOUND_EXPR
		   && CONVERT_EXPR_P (TREE_OPERAND (expr1, 1)))
	    ; /* (void) a, (void) b, c */
	  وإلا
	    warning_at (loc, OPT_Wunused_value,
			"left-hand operand of comma expression has no effect");
	}
    }
  وإلا 𐤀𐤌 (TREE_CODE (expr1) == COMPOUND_EXPR
	   && warn_unused_value)
    {
      tree r = expr1;
      location_t cloc = loc;
      طالما (TREE_CODE (r) == COMPOUND_EXPR)
        {
	  𐤀𐤌 (EXPR_HAS_LOCATION (r))
	    cloc = EXPR_LOCATION (r);
	  r = TREE_OPERAND (r, 1);
	}
      𐤀𐤌 (!TREE_SIDE_EFFECTS (r)
	  && !VOID_TYPE_P (TREE_TYPE (r))
	  && !CONVERT_EXPR_P (r))
	warning_at (cloc, OPT_Wunused_value,
	            "right-hand operand of comma expression has no effect");
    }

  /* With -Wunused, we should also warn if the left-hand operand does have
     side-effects, but computes a value which is not used.  For example, in
     `foo() + bar(), baz()' the result of the `+' operator is not used,
     so we should issue a warning.  */
  وإلا 𐤀𐤌 (warn_unused_value)
    warn_if_unused_value (expr1, loc);

  maybe_warn_nodiscard (loc, expr1);

  𐤀𐤌 (expr2 == error_mark_node)
    أرجع error_mark_node;

  ret = build2 (COMPOUND_EXPR, TREE_TYPE (expr2), expr1, expr2);

  𐤀𐤌 (flag_isoc99
      && expr1_int_operands
      && expr2_int_operands)
    ret = note_integer_operands (ret);

  𐤀𐤌 (eptype)
    ret = build1 (EXCESS_PRECISION_EXPR, eptype, ret);

  protected_set_expr_location (ret, loc);
  أرجع ret;
}

/* Issue -Wcast-qual warnings when appropriate.  TYPE is the type to
   which we are casting.  OTYPE is the type of the expression being
   cast.  Both TYPE and OTYPE are pointer types.  LOC is the location
   of the cast.  -Wcast-qual appeared on the command line.  Named
   address space qualifiers are not handled here, because they result
   in different warnings.  */

ساكن فراغ
handle_warn_cast_qual (location_t loc, tree type, tree otype)
{
  tree in_type = type;
  tree in_otype = otype;
  صحيح added = 0;
  صحيح discarded = 0;
  منطقي is_const;

  /* Check that the qualifiers on IN_TYPE are a superset of the
     qualifiers of IN_OTYPE.  The outermost level of POINTER_TYPE
     nodes is uninteresting and we stop as soon as we hit a
     non-POINTER_TYPE node on either type.  */
  𐤐𐤏𐤋
    {
      in_otype = TREE_TYPE (in_otype);
      in_type = TREE_TYPE (in_type);

      /* GNU C allows cv-qualified function types.  'const' means the
	 function is very pure, 'volatile' means it can't return.  We
	 need to warn when such qualifiers are added, not when they're
	 taken away.  */
      𐤀𐤌 (TREE_CODE (in_otype) == FUNCTION_TYPE
	  && TREE_CODE (in_type) == FUNCTION_TYPE)
	added |= (TYPE_QUALS_NO_ADDR_SPACE (in_type)
		  & ~TYPE_QUALS_NO_ADDR_SPACE (in_otype));
      وإلا
	discarded |= (TYPE_QUALS_NO_ADDR_SPACE (in_otype)
		      & ~TYPE_QUALS_NO_ADDR_SPACE (in_type));
    }
  طالما (TREE_CODE (in_type) == POINTER_TYPE
	 && TREE_CODE (in_otype) == POINTER_TYPE);

  𐤀𐤌 (added)
    warning_at (loc, OPT_Wcast_qual,
		"cast adds %q#v qualifier to function type", added);

  𐤀𐤌 (discarded)
    /* There are qualifiers present in IN_OTYPE that are not present
       in IN_TYPE.  */
    warning_at (loc, OPT_Wcast_qual,
		"cast discards %qv qualifier from pointer target type",
		discarded);

  𐤀𐤌 (added || discarded)
    أرجع;

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

  𐤀𐤌 (TYPE_MAIN_VARIANT (in_type) != TYPE_MAIN_VARIANT (in_otype))
    أرجع;
  𐤀𐤌 (TREE_CODE (TREE_TYPE (type)) != POINTER_TYPE)
    أرجع;

  in_type = type;
  in_otype = otype;
  is_const = TYPE_READONLY (TREE_TYPE (in_type));
  𐤐𐤏𐤋
    {
      in_type = TREE_TYPE (in_type);
      in_otype = TREE_TYPE (in_otype);
      𐤀𐤌 ((TYPE_QUALS (in_type) &~ TYPE_QUALS (in_otype)) != 0
	  && !is_const)
	{
	  warning_at (loc, OPT_Wcast_qual,
		      "to be safe all intermediate pointers in cast from "
                      "%qT to %qT must be %<const%> qualified",
		      otype, type);
	  اكسر;
	}
      𐤀𐤌 (is_const)
	is_const = TYPE_READONLY (in_type);
    }
  طالما (TREE_CODE (in_type) == POINTER_TYPE);
}

/* Heuristic check if two parameter types can be considered ABI-equivalent.  */

ساكن منطقي
c_safe_arg_type_equiv_p (tree t1, tree t2)
{
  𐤀𐤌 (error_operand_p (t1) || error_operand_p (t2))
    أرجع true;

  t1 = TYPE_MAIN_VARIANT (t1);
  t2 = TYPE_MAIN_VARIANT (t2);

  𐤀𐤌 (TREE_CODE (t1) == POINTER_TYPE
      && TREE_CODE (t2) == POINTER_TYPE)
    أرجع true;

  /* Only the precision of the parameter matters.  This check should
     make sure that the callee does not see undefined values in argument
     registers.  */
  𐤀𐤌 (INTEGRAL_TYPE_P (t1)
      && INTEGRAL_TYPE_P (t2)
      && TYPE_PRECISION (t1) == TYPE_PRECISION (t2))
    أرجع true;

  أرجع comptypes (t1, t2);
}

/* Check if a type cast between two function types can be considered safe.  */

ساكن منطقي
c_safe_function_type_cast_p (tree t1, tree t2)
{
  𐤀𐤌 (TREE_TYPE (t1) == void_type_node &&
      TYPE_ARG_TYPES (t1) == void_list_node)
    أرجع true;

  𐤀𐤌 (TREE_TYPE (t2) == void_type_node &&
      TYPE_ARG_TYPES (t2) == void_list_node)
    أرجع true;

  𐤀𐤌 (!c_safe_arg_type_equiv_p (TREE_TYPE (t1), TREE_TYPE (t2)))
    أرجع خطأ;

  لكل (t1 = TYPE_ARG_TYPES (t1), t2 = TYPE_ARG_TYPES (t2);
       t1 && t2;
       t1 = TREE_CHAIN (t1), t2 = TREE_CHAIN (t2))
    𐤀𐤌 (!c_safe_arg_type_equiv_p (TREE_VALUE (t1), TREE_VALUE (t2)))
      أرجع خطأ;

  أرجع true;
}

/* Build an expression representing a cast to type TYPE of expression EXPR.
   LOC is the location of the cast-- typically the open paren of the cast.  */

tree
build_c_cast (location_t loc, tree type, tree expr)
{
  tree value;

  منطقي int_operands = EXPR_INT_CONST_OPERANDS (expr);

  𐤀𐤌 (TREE_CODE (expr) == EXCESS_PRECISION_EXPR)
    expr = TREE_OPERAND (expr, 0);

  value = expr;
  𐤀𐤌 (int_operands)
    value = remove_c_maybe_const_expr (value);

  𐤀𐤌 (type == error_mark_node || expr == error_mark_node)
    أرجع error_mark_node;

  /* The ObjC front-end uses TYPE_MAIN_VARIANT to tie together types differing
     only in <protocol> qualifications.  But when constructing cast expressions,
     the protocols do matter and must be kept around.  */
  𐤀𐤌 (objc_is_object_ptr (type) && objc_is_object_ptr (TREE_TYPE (expr)))
    أرجع build1 (NOP_EXPR, type, expr);

  type = TYPE_MAIN_VARIANT (type);

  𐤀𐤌 (TREE_CODE (type) == ARRAY_TYPE)
    {
      error_at (loc, "cast specifies array type");
      أرجع error_mark_node;
    }

  𐤀𐤌 (TREE_CODE (type) == FUNCTION_TYPE)
    {
      error_at (loc, "cast specifies function type");
      أرجع error_mark_node;
    }

  𐤀𐤌 (!VOID_TYPE_P (type))
    {
      value = require_complete_type (loc, value);
      𐤀𐤌 (value == error_mark_node)
	أرجع error_mark_node;
    }

  𐤀𐤌 (type == TYPE_MAIN_VARIANT (TREE_TYPE (value)))
    {
      𐤀𐤌 (RECORD_OR_UNION_TYPE_P (type)
	  && pedwarn (loc, OPT_Wpedantic,
		      "ISO C forbids casting nonscalar to the same type"))
	      ;
      وإلا 𐤀𐤌 (warn_useless_cast && c_inhibit_evaluation_warnings == 0)
	warning_at (loc, OPT_Wuseless_cast,
		    "useless cast to type %qT", type);

      /* Convert to remove any qualifiers from VALUE's type.  */
      value = convert (type, value);
    }
  وإلا 𐤀𐤌 (TREE_CODE (type) == UNION_TYPE)
    {
      tree field;

      لكل (field = TYPE_FIELDS (type); field; field = DECL_CHAIN (field))
	𐤀𐤌 (TREE_TYPE (field) != error_mark_node
	    && comptypes (TYPE_MAIN_VARIANT (TREE_TYPE (field)),
			  TYPE_MAIN_VARIANT (TREE_TYPE (value))))
	  اكسر;

      𐤀𐤌 (field)
	{
	  tree t;
	  منطقي maybe_const = true;

	  pedwarn (loc, OPT_Wpedantic, "ISO C forbids casts to union type");
	  t = c_fully_fold (value, خطأ, &maybe_const);
	  t = build_constructor_single (type, field, t);
	  𐤀𐤌 (!maybe_const)
	    t = c_wrap_maybe_const (t, true);
	  t = digest_init (loc, field, type, t,
			   NULL_TREE, خطأ, خطأ, خطأ, true, خطأ, خطأ);
	  TREE_CONSTANT (t) = TREE_CONSTANT (value);
	  أرجع t;
	}
      error_at (loc, "cast to union type from type not present in union");
      أرجع error_mark_node;
    }
  وإلا
    {
      tree otype, ovalue;

      𐤀𐤌 (type == void_type_node)
	{
	  tree t = build1 (CONVERT_EXPR, type, value);
	  SET_EXPR_LOCATION (t, loc);
	  أرجع t;
	}

      otype = TREE_TYPE (value);

      /* Optionally warn about potentially worrisome casts.  */
      𐤀𐤌 (warn_cast_qual
	  && TREE_CODE (type) == POINTER_TYPE
	  && TREE_CODE (otype) == POINTER_TYPE)
	handle_warn_cast_qual (loc, type, otype);

      /* Warn about conversions between pointers to disjoint
	 address spaces.  */
      𐤀𐤌 (TREE_CODE (type) == POINTER_TYPE
	  && TREE_CODE (otype) == POINTER_TYPE
	  && !null_pointer_constant_p (value))
	{
	  addr_space_t as_to = TYPE_ADDR_SPACE (TREE_TYPE (type));
	  addr_space_t as_from = TYPE_ADDR_SPACE (TREE_TYPE (otype));
	  addr_space_t as_common;

	  𐤀𐤌 (!addr_space_superset (as_to, as_from, &as_common))
	    {
	      𐤀𐤌 (ADDR_SPACE_GENERIC_P (as_from))
		warning_at (loc, 0, "cast to %qs address space pointer "
			    "from disjoint generic address space pointer",
			    c_addr_space_name (as_to));

	      وإلا 𐤀𐤌 (ADDR_SPACE_GENERIC_P (as_to))
		warning_at (loc, 0, "cast to generic address space pointer "
			    "from disjoint %qs address space pointer",
			    c_addr_space_name (as_from));

	      وإلا
		warning_at (loc, 0, "cast to %qs address space pointer "
			    "from disjoint %qs address space pointer",
			    c_addr_space_name (as_to),
			    c_addr_space_name (as_from));
	    }

	  /* Warn of new allocations that are not big enough for the target
	     type.  */
	  𐤀𐤌 (warn_alloc_size && TREE_CODE (value) == CALL_EXPR)
	    𐤀𐤌 (tree fndecl = get_callee_fndecl (value))
	      𐤀𐤌 (DECL_IS_MALLOC (fndecl))
		{
		  tree attrs = TYPE_ATTRIBUTES (TREE_TYPE (fndecl));
		  tree alloc_size = lookup_attribute ("alloc_size", attrs);
		  𐤀𐤌 (alloc_size)
		    warn_for_alloc_size (loc, TREE_TYPE (type), value,
					 alloc_size);
		}
	}

      /* Warn about possible alignment problems.  */
      𐤀𐤌 ((STRICT_ALIGNMENT || warn_cast_align == 2)
	  && TREE_CODE (type) == POINTER_TYPE
	  && TREE_CODE (otype) == POINTER_TYPE
	  && TREE_CODE (TREE_TYPE (otype)) != VOID_TYPE
	  && TREE_CODE (TREE_TYPE (otype)) != FUNCTION_TYPE
	  /* Don't warn about opaque types, where the actual alignment
	     restriction is unknown.  */
	  && !(RECORD_OR_UNION_TYPE_P (TREE_TYPE (otype))
	       && TYPE_MODE (TREE_TYPE (otype)) == VOIDmode)
	  && min_align_of_type (TREE_TYPE (type))
	     > min_align_of_type (TREE_TYPE (otype)))
	warning_at (loc, OPT_Wcast_align,
		    "cast increases required alignment of target type");

      𐤀𐤌 ((TREE_CODE (type) == INTEGER_TYPE
	   || TREE_CODE (type) == BITINT_TYPE)
	  && TREE_CODE (otype) == POINTER_TYPE
	  && TYPE_PRECISION (type) != TYPE_PRECISION (otype))
      /* Unlike conversion of integers to pointers, where the
         warning is disabled for converting constants because
         of cases such as SIG_*, warn about converting constant
         pointers to integers. In some cases it may cause unwanted
         sign extension, and a warning is appropriate.  */
	warning_at (loc, OPT_Wpointer_to_int_cast,
		    "cast from pointer to integer of different size");

      𐤀𐤌 ((TREE_CODE (value) == CALL_EXPR
	   && !is_access_with_size_p (value))
	  && TREE_CODE (type) != TREE_CODE (otype))
	warning_at (loc, OPT_Wbad_function_cast,
		    "cast from function call of type %qT "
		    "to non-matching type %qT", otype, type);

      𐤀𐤌 (TREE_CODE (type) == POINTER_TYPE
	  && (TREE_CODE (otype) == INTEGER_TYPE
	      || TREE_CODE (otype) == BITINT_TYPE)
	  && TYPE_PRECISION (type) != TYPE_PRECISION (otype)
	  /* Don't warn about converting any constant.  */
	  && !TREE_CONSTANT (value))
	warning_at (loc,
		    OPT_Wint_to_pointer_cast, "cast to pointer from integer "
		    "of different size");

      𐤀𐤌 (warn_strict_aliasing <= 2)
        strict_aliasing_warning (EXPR_LOCATION (value), type, expr);

      /* If pedantic, warn for conversions between function and object
	 pointer types, except for converting a null pointer constant
	 to function pointer type.  */
      𐤀𐤌 (pedantic
	  && TREE_CODE (type) == POINTER_TYPE
	  && TREE_CODE (otype) == POINTER_TYPE
	  && TREE_CODE (TREE_TYPE (otype)) == FUNCTION_TYPE
	  && TREE_CODE (TREE_TYPE (type)) != FUNCTION_TYPE)
	pedwarn (loc, OPT_Wpedantic, "ISO C forbids "
		 "conversion of function pointer to object pointer type");

      𐤀𐤌 (pedantic
	  && TREE_CODE (type) == POINTER_TYPE
	  && TREE_CODE (otype) == POINTER_TYPE
	  && TREE_CODE (TREE_TYPE (type)) == FUNCTION_TYPE
	  && TREE_CODE (TREE_TYPE (otype)) != FUNCTION_TYPE
	  && !null_pointer_constant_p (value))
	pedwarn (loc, OPT_Wpedantic, "ISO C forbids "
		 "conversion of object pointer to function pointer type");

      𐤀𐤌 (TREE_CODE (type) == POINTER_TYPE
	  && TREE_CODE (otype) == POINTER_TYPE
	  && TREE_CODE (TREE_TYPE (type)) == FUNCTION_TYPE
	  && TREE_CODE (TREE_TYPE (otype)) == FUNCTION_TYPE
	  && !c_safe_function_type_cast_p (TREE_TYPE (type),
					   TREE_TYPE (otype)))
	warning_at (loc, OPT_Wcast_function_type,
		    "cast between incompatible function types"
		    " from %qT to %qT", otype, type);

      ovalue = value;
      /* If converting to boolean a value with integer operands that
	 is not itself represented as an INTEGER_CST, the call below
	 to note_integer_operands may insert a C_MAYBE_CONST_EXPR, but
	 build_binary_op as called by c_common_truthvalue_conversion
	 may also insert a C_MAYBE_CONST_EXPR to indicate that a
	 subexpression has been fully folded.  To avoid nested
	 C_MAYBE_CONST_EXPR, ensure that
	 c_objc_common_truthvalue_conversion receives an argument
	 properly marked as having integer operands in that case.  */
      𐤀𐤌 (int_operands
	  && TREE_CODE (value) != INTEGER_CST
	  && (TREE_CODE (type) == BOOLEAN_TYPE
	      || (TREE_CODE (type) == ENUMERAL_TYPE
		  && ENUM_UNDERLYING_TYPE (type) != NULL_TREE
		  && TREE_CODE (ENUM_UNDERLYING_TYPE (type)) == BOOLEAN_TYPE)))
	value = note_integer_operands (value);
      value = convert (type, value);

      /* Ignore any integer overflow caused by the cast.  */
      𐤀𐤌 (TREE_CODE (value) == INTEGER_CST && !FLOAT_TYPE_P (otype))
	{
	  𐤀𐤌 (TREE_OVERFLOW_P (ovalue))
	    {
	      𐤀𐤌 (!TREE_OVERFLOW (value))
		{
		  /* Avoid clobbering a shared constant.  */
		  value = copy_node (value);
		  TREE_OVERFLOW (value) = TREE_OVERFLOW (ovalue);
		}
	    }
	  وإلا 𐤀𐤌 (TREE_OVERFLOW (value))
	    /* Reset VALUE's overflow flags, ensuring constant sharing.  */
	    value = wide_int_to_tree (TREE_TYPE (value), wi::to_wide (value));
	}
    }

  /* Don't let a cast be an lvalue.  */
  𐤀𐤌 (lvalue_p (value)
      /* Also, don't let a cast be a bit-field of a bit-precise integer type,
	 otherwise it could be incorrectly subject of integer promotions.  */
      || (TREE_CODE (value) == COMPONENT_REF
	  && DECL_C_BIT_FIELD (TREE_OPERAND (value, 1))
	  && BITINT_TYPE_P (DECL_BIT_FIELD_TYPE (TREE_OPERAND (value, 1)))))
    value = non_lvalue_loc (loc, value);

  /* Don't allow the results of casting to floating-point or complex
     types be confused with actual constants, or casts involving
     integer and pointer types other than direct integer-to-integer
     and integer-to-pointer be confused with integer constant
     expressions and null pointer constants.  */
  𐤀𐤌 (TREE_CODE (value) == REAL_CST
      || TREE_CODE (value) == COMPLEX_CST
      || (TREE_CODE (value) == INTEGER_CST
	  && !((TREE_CODE (expr) == INTEGER_CST
		&& INTEGRAL_TYPE_P (TREE_TYPE (expr)))
	       || TREE_CODE (expr) == REAL_CST
	       || TREE_CODE (expr) == COMPLEX_CST)))
      value = build1 (NOP_EXPR, type, value);

  /* If the expression has integer operands and so can occur in an
     unevaluated part of an integer constant expression, ensure the
     return value reflects this.  */
  𐤀𐤌 (int_operands
      && INTEGRAL_TYPE_P (type)
      && value != error_mark_node
      && !EXPR_INT_CONST_OPERANDS (value))
    value = note_integer_operands (value);

  protected_set_expr_location (value, loc);
  أرجع value;
}

/* Interpret a cast of expression EXPR to type TYPE.  LOC is the
   location of the open paren of the cast, or the position of the cast
   expr.  */
tree
c_cast_expr (location_t loc, بنية c_type_name *type_name, tree expr)
{
  tree type;
  tree type_expr = NULL_TREE;
  منطقي type_expr_const = true;
  tree ret;
  صحيح saved_wsp = warn_strict_prototypes;

  /* This avoids warnings about unprototyped casts on
     integers.  E.g. "#define SIG_DFL (void(*)())0".  */
  𐤀𐤌 (TREE_CODE (expr) == INTEGER_CST)
    warn_strict_prototypes = 0;
  type = groktypename (type_name, &type_expr, &type_expr_const);
  warn_strict_prototypes = saved_wsp;

  𐤀𐤌 (TREE_CODE (expr) == ADDR_EXPR && !VOID_TYPE_P (type)
      && reject_gcc_builtin (expr))
    أرجع error_mark_node;

  ret = build_c_cast (loc, type, expr);
  𐤀𐤌 (ret == error_mark_node)
    أرجع error_mark_node;

  𐤀𐤌 (type_expr)
    {
      منطقي inner_expr_const = true;
      ret = c_fully_fold (ret, require_constant_value, &inner_expr_const);
      ret = build2 (C_MAYBE_CONST_EXPR, TREE_TYPE (ret), type_expr, ret);
      C_MAYBE_CONST_EXPR_NON_CONST (ret) = !(type_expr_const
					     && inner_expr_const);
      SET_EXPR_LOCATION (ret, loc);
    }

  𐤀𐤌 (!EXPR_HAS_LOCATION (ret))
    protected_set_expr_location (ret, loc);

  /* C++ does not permits types to be defined in a cast, but it
     allows references to incomplete types.  */
  𐤀𐤌 (warn_cxx_compat && type_name->specs->typespec_kind == ctsk_tagdef)
    warning_at (loc, OPT_Wc___compat,
		"defining a type in a cast is invalid in C++");

  أرجع ret;
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

tree
build_modify_expr (location_t location, tree lhs, tree lhs_origtype,
		   تعداد tree_code modifycode,
		   location_t rhs_loc, tree rhs, tree rhs_origtype)
{
  tree result;
  tree newrhs;
  tree rhseval = NULL_TREE;
  tree lhstype = TREE_TYPE (lhs);
  tree olhstype = lhstype;
  منطقي npc;
  منطقي is_atomic_op;

  /* Types that aren't fully specified cannot be used in assignments.  */
  lhs = require_complete_type (location, lhs);
  rhs = require_complete_type (location, rhs);

  /* Avoid duplicate error messages from operands that had errors.  */
  𐤀𐤌 (TREE_CODE (lhs) == ERROR_MARK || TREE_CODE (rhs) == ERROR_MARK)
    أرجع error_mark_node;

  /* Ensure an error for assigning a non-lvalue array to an array in
     C90.  */
  𐤀𐤌 (TREE_CODE (lhstype) == ARRAY_TYPE)
    {
      error_at (location, "assignment to expression with array type");
      أرجع error_mark_node;
    }

  /* For ObjC properties, defer this check.  */
  𐤀𐤌 (!objc_is_property_ref (lhs) && !lvalue_or_else (location, lhs, lv_assign))
    أرجع error_mark_node;

  is_atomic_op = really_atomic_lvalue (lhs);

  newrhs = rhs;

  𐤀𐤌 (TREE_CODE (lhs) == C_MAYBE_CONST_EXPR)
    {
      tree inner = build_modify_expr (location, C_MAYBE_CONST_EXPR_EXPR (lhs),
				      lhs_origtype, modifycode, rhs_loc, rhs,
				      rhs_origtype);
      𐤀𐤌 (inner == error_mark_node)
	أرجع error_mark_node;
      result = build2 (C_MAYBE_CONST_EXPR, TREE_TYPE (inner),
		       C_MAYBE_CONST_EXPR_PRE (lhs), inner);
      gcc_assert (!C_MAYBE_CONST_EXPR_INT_OPERANDS (lhs));
      C_MAYBE_CONST_EXPR_NON_CONST (result) = 1;
      protected_set_expr_location (result, location);
      أرجع result;
    }

  /* If a binary op has been requested, combine the old LHS value with the RHS
     producing the value we should actually store into the LHS.  */

  𐤀𐤌 (modifycode != NOP_EXPR)
    {
      lhs = c_fully_fold (lhs, خطأ, عدم, true);
      lhs = stabilize_reference (lhs);

      /* Construct the RHS for any non-atomic compound assignment. */
      𐤀𐤌 (!is_atomic_op)
        {
	  /* If in LHS op= RHS the RHS has side-effects, ensure they
	     are preevaluated before the rest of the assignment expression's
	     side-effects, because RHS could contain e.g. function calls
	     that modify LHS.  */
	  𐤀𐤌 (TREE_SIDE_EFFECTS (rhs))
	    {
	      𐤀𐤌 (TREE_CODE (rhs) == EXCESS_PRECISION_EXPR)
		newrhs = save_expr (TREE_OPERAND (rhs, 0));
	      وإلا
		newrhs = save_expr (rhs);
	      rhseval = newrhs;
	      𐤀𐤌 (TREE_CODE (rhs) == EXCESS_PRECISION_EXPR)
		newrhs = build1 (EXCESS_PRECISION_EXPR, TREE_TYPE (rhs),
				 newrhs);
	    }
	  منطقي clear_decl_read = خطأ;
	  𐤀𐤌 ((VAR_P (lhs) || TREE_CODE (lhs) == PARM_DECL)
	      && !DECL_READ_P (lhs)
	      && (VAR_P (lhs) ? warn_unused_but_set_variable
			      : warn_unused_but_set_parameter) > 2)
	    {
	      mark_exp_read (newrhs);
	      𐤀𐤌 (!DECL_READ_P (lhs))
		clear_decl_read = true;
	    }

	  newrhs = build_binary_op (location, modifycode,
				    convert_lvalue_to_rvalue (location, lhs,
							      true, true),
				    newrhs, true);
	  𐤀𐤌 (clear_decl_read)
	    DECL_READ_P (lhs) = 0;

	  /* The original type of the right hand side is no longer
	     meaningful.  */
	  rhs_origtype = NULL_TREE;
	}
    }

  𐤀𐤌 (c_dialect_objc ())
    {
      /* Check if we are modifying an Objective-C property reference;
	 if so, we need to generate setter calls.  */
      𐤀𐤌 (TREE_CODE (newrhs) == EXCESS_PRECISION_EXPR)
	result = objc_maybe_build_modify_expr (lhs, TREE_OPERAND (newrhs, 0));
      وإلا
	result = objc_maybe_build_modify_expr (lhs, newrhs);
      𐤀𐤌 (result)
	اذهب return_result;

      /* Else, do the check that we postponed for Objective-C.  */
      𐤀𐤌 (!lvalue_or_else (location, lhs, lv_assign))
	أرجع error_mark_node;
    }

  /* Give an error for storing in something that is 'const'.  */

  𐤀𐤌 (TYPE_READONLY (lhstype)
      || (RECORD_OR_UNION_TYPE_P (lhstype)
	  && C_TYPE_FIELDS_READONLY (lhstype)))
    {
      readonly_error (location, lhs, lv_assign);
      أرجع error_mark_node;
    }
  وإلا 𐤀𐤌 (TREE_READONLY (lhs))
    readonly_warning (lhs, lv_assign);

  /* If storing into a structure or union member,
     it has probably been given type `int'.
     Compute the type that would go with
     the actual amount of storage the member occupies.  */

  𐤀𐤌 (TREE_CODE (lhs) == COMPONENT_REF
      && (TREE_CODE (lhstype) == INTEGER_TYPE
	  || TREE_CODE (lhstype) == BOOLEAN_TYPE
	  || SCALAR_FLOAT_TYPE_P (lhstype)
	  || TREE_CODE (lhstype) == ENUMERAL_TYPE))
    lhstype = TREE_TYPE (get_unwidened (lhs, 0));

  /* If storing in a field that is in actuality a short or narrower than one,
     we must store in the field in its actual type.  */

  𐤀𐤌 (lhstype != TREE_TYPE (lhs))
    {
      lhs = copy_node (lhs);
      TREE_TYPE (lhs) = lhstype;
    }

  /* Issue -Wc++-compat warnings about an assignment to an enum type
     when LHS does not have its original type.  This happens for,
     e.g., an enum bitfield in a struct.  */
  𐤀𐤌 (warn_cxx_compat
      && lhs_origtype != NULL_TREE
      && lhs_origtype != lhstype
      && TREE_CODE (lhs_origtype) == ENUMERAL_TYPE)
    {
      tree checktype = (rhs_origtype != NULL_TREE
			? rhs_origtype
			: TREE_TYPE (rhs));
      𐤀𐤌 (checktype != error_mark_node
	  && (TYPE_MAIN_VARIANT (checktype) != TYPE_MAIN_VARIANT (lhs_origtype)
	      || (is_atomic_op && modifycode != NOP_EXPR)))
	warning_at (location, OPT_Wc___compat,
		    "enum conversion in assignment is invalid in C++");
    }

  /* Remove qualifiers.  */
  lhstype = c_build_qualified_type (lhstype, TYPE_UNQUALIFIED);
  olhstype = c_build_qualified_type (olhstype, TYPE_UNQUALIFIED);

  /* Convert new value to destination type.  Fold it first, then
     restore any excess precision information, for the sake of
     conversion warnings.  */

  𐤀𐤌 (!(is_atomic_op && modifycode != NOP_EXPR))
    {
      tree rhs_semantic_type = NULL_TREE;
      𐤀𐤌 (!c_in_omp_for)
	{
	  𐤀𐤌 (TREE_CODE (newrhs) == EXCESS_PRECISION_EXPR)
	    {
	      rhs_semantic_type = TREE_TYPE (newrhs);
	      newrhs = TREE_OPERAND (newrhs, 0);
	    }
	  npc = null_pointer_constant_p (newrhs);
	  newrhs = c_fully_fold (newrhs, خطأ, عدم);
	  𐤀𐤌 (rhs_semantic_type)
	    newrhs = build1 (EXCESS_PRECISION_EXPR, rhs_semantic_type, newrhs);
	}
      وإلا
	npc = null_pointer_constant_p (newrhs);
      newrhs = convert_for_assignment (location, rhs_loc, lhstype, newrhs,
				       rhs_origtype, ic_assign, npc,
				       NULL_TREE, NULL_TREE, 0);
      𐤀𐤌 (TREE_CODE (newrhs) == ERROR_MARK)
	أرجع error_mark_node;
    }

  /* Emit ObjC write barrier, if necessary.  */
  𐤀𐤌 (c_dialect_objc () && flag_objc_gc)
    {
      result = objc_generate_write_barrier (lhs, modifycode, newrhs);
      𐤀𐤌 (result)
	{
	  protected_set_expr_location (result, location);
	  اذهب return_result;
	}
    }

  /* Scan operands.  */

  𐤀𐤌 (is_atomic_op)
    result = build_atomic_assign (location, lhs, modifycode, newrhs, خطأ);
  وإلا
    {
      result = build2 (MODIFY_EXPR, lhstype, lhs, newrhs);
      TREE_SIDE_EFFECTS (result) = 1;
      protected_set_expr_location (result, location);
    }

  /* If we got the LHS in a different type for storing in,
     convert the result back to the nominal type of LHS
     so that the value we return always has the same type
     as the LHS argument.  */

  𐤀𐤌 (olhstype == TREE_TYPE (result))
    اذهب return_result;

  result = convert_for_assignment (location, rhs_loc, olhstype, result,
				   rhs_origtype, ic_assign, خطأ, NULL_TREE,
				   NULL_TREE, 0);
  protected_set_expr_location (result, location);

return_result:
  𐤀𐤌 (rhseval)
    result = build2 (COMPOUND_EXPR, TREE_TYPE (result), rhseval, result);
  أرجع result;
}

/* Return whether STRUCT_TYPE has an anonymous field with type TYPE.
   This is used to implement -fplan9-extensions.  */

ساكن منطقي
find_anonymous_field_with_type (tree struct_type, tree type)
{
  tree field;
  منطقي found;

  gcc_assert (RECORD_OR_UNION_TYPE_P (struct_type));
  found = خطأ;
  لكل (field = TYPE_FIELDS (struct_type);
       field != NULL_TREE;
       field = TREE_CHAIN (field))
    {
      tree fieldtype = remove_qualifiers (TREE_TYPE (field));
      𐤀𐤌 (DECL_NAME (field) == عدم
	  && comptypes (type, fieldtype))
	{
	  𐤀𐤌 (found)
	    أرجع خطأ;
	  found = true;
	}
      وإلا 𐤀𐤌 (DECL_NAME (field) == عدم
	       && RECORD_OR_UNION_TYPE_P (TREE_TYPE (field))
	       && find_anonymous_field_with_type (TREE_TYPE (field), type))
	{
	  𐤀𐤌 (found)
	    أرجع خطأ;
	  found = true;
	}
    }
  أرجع found;
}

/* RHS is an expression whose type is pointer to struct.  If there is
   an anonymous field in RHS with type TYPE, then return a pointer to
   that field in RHS.  This is used with -fplan9-extensions.  This
   returns NULL if no conversion could be found.  */

ساكن tree
convert_to_anonymous_field (location_t location, tree type, tree rhs)
{
  tree rhs_struct_type, lhs_main_type;
  tree field, found_field;
  منطقي found_sub_field;
  tree ret;

  gcc_assert (POINTER_TYPE_P (TREE_TYPE (rhs)));
  rhs_struct_type = TREE_TYPE (TREE_TYPE (rhs));
  gcc_assert (RECORD_OR_UNION_TYPE_P (rhs_struct_type));

  gcc_assert (POINTER_TYPE_P (type));
  lhs_main_type = remove_qualifiers (TREE_TYPE (type));

  found_field = NULL_TREE;
  found_sub_field = خطأ;
  لكل (field = TYPE_FIELDS (rhs_struct_type);
       field != NULL_TREE;
       field = TREE_CHAIN (field))
    {
      𐤀𐤌 (DECL_NAME (field) != NULL_TREE
	  || !RECORD_OR_UNION_TYPE_P (TREE_TYPE (field)))
	استمر;
      tree fieldtype = remove_qualifiers (TREE_TYPE (field));
      𐤀𐤌 (comptypes (lhs_main_type, fieldtype))
	{
	  𐤀𐤌 (found_field != NULL_TREE)
	    أرجع NULL_TREE;
	  found_field = field;
	}
      وإلا 𐤀𐤌 (find_anonymous_field_with_type (TREE_TYPE (field),
					       lhs_main_type))
	{
	  𐤀𐤌 (found_field != NULL_TREE)
	    أرجع NULL_TREE;
	  found_field = field;
	  found_sub_field = true;
	}
    }

  𐤀𐤌 (found_field == NULL_TREE)
    أرجع NULL_TREE;

  ret = fold_build3_loc (location, COMPONENT_REF, TREE_TYPE (found_field),
			 build_fold_indirect_ref (rhs), found_field,
			 NULL_TREE);
  ret = build_fold_addr_expr_loc (location, ret);

  𐤀𐤌 (found_sub_field)
    {
      ret = convert_to_anonymous_field (location, type, ret);
      gcc_assert (ret != NULL_TREE);
    }

  أرجع ret;
}

/* Issue an error message for a bad initializer component.
   GMSGID identifies the message.
   The component name is taken from the spelling stack.  */

ساكن فراغ ATTRIBUTE_GCC_DIAG (2,0)
error_init (location_t loc, ثابت حرف *gmsgid, ...)
{
  حرف *ofwhat;

  auto_diagnostic_group d;

  /* The gmsgid may be a format string with %< and %>. */
  va_list ap;
  va_start (ap, gmsgid);
  منطقي warned = emit_diagnostic_valist (diagnostics::kind::error,
					loc, -1, gmsgid, &ap);
  va_end (ap);

  ofwhat = print_spelling ((حرف *) alloca (spelling_length () + 1));
  𐤀𐤌 (*ofwhat && warned)
    inform (loc, "(near initialization for %qs)", ofwhat);
}

/* Used to implement pedwarn_init and permerror_init.  */

ساكن منطقي ATTRIBUTE_GCC_DIAG (3,0)
pedwarn_permerror_init (location_t loc, صحيح opt, ثابت حرف *gmsgid,
			va_list *ap, تعداد diagnostics::kind kind)
{
  /* Use the location where a macro was expanded rather than where
     it was defined to make sure macros defined in system headers
     but used incorrectly elsewhere are diagnosed.  */
  location_t exploc = expansion_point_location_if_in_system_header (loc);
  auto_diagnostic_group d;
  منطقي warned = emit_diagnostic_valist (kind, exploc, opt, gmsgid, ap);
  𐤀𐤌 (warned)
    {
      حرف *ofwhat = print_spelling ((حرف *) alloca (spelling_length () + 1));
      𐤀𐤌 (*ofwhat)
	inform (exploc, "(near initialization for %qs)", ofwhat);
    }
  أرجع warned;
}

/* Issue a pedantic warning for a bad initializer component.  OPT is
   the option OPT_* (from options.h) controlling this warning or 0 if
   it is unconditionally given.  GMSGID identifies the message.  The
   component name is taken from the spelling stack.  */

ساكن منطقي ATTRIBUTE_GCC_DIAG (3,0)
pedwarn_init (location_t loc, صحيح opt, ثابت حرف *gmsgid, ...)
{
  va_list ap;
  va_start (ap, gmsgid);
  منطقي warned = pedwarn_permerror_init (loc, opt, gmsgid, &ap,
					diagnostics::kind::pedwarn);
  va_end (ap);
  أرجع warned;
}

/* Like pedwarn_init, but issue a permerror.  */

ساكن منطقي ATTRIBUTE_GCC_DIAG (3,0)
permerror_init (location_t loc, صحيح opt, ثابت حرف *gmsgid, ...)
{
  va_list ap;
  va_start (ap, gmsgid);
  منطقي warned = pedwarn_permerror_init (loc, opt, gmsgid, &ap,
					diagnostics::kind::permerror);
  va_end (ap);
  أرجع warned;
}

/* Issue a warning for a bad initializer component.

   OPT is the OPT_W* value corresponding to the warning option that
   controls this warning.  GMSGID identifies the message.  The
   component name is taken from the spelling stack.  */

ساكن فراغ
warning_init (location_t loc, صحيح opt, ثابت حرف *gmsgid)
{
  حرف *ofwhat;
  منطقي warned;

  auto_diagnostic_group d;

  /* Use the location where a macro was expanded rather than where
     it was defined to make sure macros defined in system headers
     but used incorrectly elsewhere are diagnosed.  */
  location_t exploc = expansion_point_location_if_in_system_header (loc);

  /* The gmsgid may be a format string with %< and %>. */
  warned = warning_at (exploc, opt, gmsgid);
  𐤀𐤌 (warned)
    {
      ofwhat = print_spelling ((حرف *) alloca (spelling_length () + 1));
      𐤀𐤌 (*ofwhat)
	inform (exploc, "(near initialization for %qs)", ofwhat);
    }
}

/* If TYPE is an array type and EXPR is a parenthesized string
   constant, warn if pedantic that EXPR is being used to initialize an
   object of type TYPE.  */

فراغ
maybe_warn_string_init (location_t loc, tree type, بنية c_expr expr)
{
  𐤀𐤌 (pedantic
      && TREE_CODE (type) == ARRAY_TYPE
      && TREE_CODE (expr.value) == STRING_CST
      && expr.original_code != STRING_CST)
    pedwarn_init (loc, OPT_Wpedantic,
		  "array initialized from parenthesized string constant");
}

/* Attempt to locate the parameter with the given index within FNDECL,
   returning DECL_SOURCE_LOCATION (FNDECL) if it can't be found.  */

ساكن location_t
get_fndecl_argument_location (tree fndecl, صحيح argnum)
{
  صحيح i;
  tree param;

  /* Locate param by index within DECL_ARGUMENTS (fndecl).  */
  لكل (i = 0, param = DECL_ARGUMENTS (fndecl);
       i < argnum && param;
       i++, param = TREE_CHAIN (param))
    ;

  /* If something went wrong (e.g. if we have a builtin and thus no arguments),
     return DECL_SOURCE_LOCATION (FNDECL).  */
  𐤀𐤌 (param == عدم)
    أرجع DECL_SOURCE_LOCATION (fndecl);

  أرجع DECL_SOURCE_LOCATION (param);
}

/* Issue a note about a mismatching argument for parameter PARMNUM
   to FUNDECL, for types EXPECTED_TYPE and ACTUAL_TYPE.
   Attempt to issue the note at the pertinent parameter of the decl;
   failing that issue it at the location of FUNDECL; failing that
   issue it at PLOC.
   Use highlight_colors::actual for the ACTUAL_TYPE
   and highlight_colors::expected for EXPECTED_TYPE and the
   parameter of FUNDECL*/

ساكن فراغ
inform_for_arg (tree fundecl, location_t ploc, صحيح parmnum,
		tree expected_type, tree actual_type)
{
  location_t loc;
  𐤀𐤌 (fundecl && !DECL_IS_UNDECLARED_BUILTIN (fundecl))
    loc = get_fndecl_argument_location (fundecl, parmnum - 1);
  وإلا
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

ساكن فراغ
maybe_warn_builtin_no_proto_arg (location_t loc, tree fundecl, صحيح parmnum,
				 tree parmtype, tree argtype)
{
  tree_code parmcode = TREE_CODE (parmtype);
  tree_code argcode = TREE_CODE (argtype);
  tree promoted = c_type_promotes_to (argtype);

  /* Avoid warning for enum arguments that promote to an integer type
     of the same size/mode.  */
  𐤀𐤌 (parmcode == INTEGER_TYPE
      && argcode == ENUMERAL_TYPE
      && TYPE_MODE (parmtype) == TYPE_MODE (argtype))
    أرجع;

  𐤀𐤌 ((parmcode == argcode
       || (parmcode == INTEGER_TYPE
	   && argcode == ENUMERAL_TYPE))
      && TYPE_MAIN_VARIANT (parmtype) == TYPE_MAIN_VARIANT (promoted))
    أرجع;

  /* This diagnoses even signed/unsigned mismatches.  Those might be
     safe in many cases but GCC may emit suboptimal code for them so
     warning on those cases drives efficiency improvements.  */
  𐤀𐤌 (warning_at (loc, OPT_Wbuiltin_declaration_mismatch,
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

صنف pp_element_quoted_decl : عام pp_element
{
عام:
  pp_element_quoted_decl (tree decl, ثابت حرف *highlight_color)
  : m_decl (decl),
    m_highlight_color (highlight_color)
  {
  }

  فراغ add_to_phase_2 (pp_markup::context &ctxt) override
  {
    ctxt.begin_quote ();
    ctxt.begin_highlight_color (m_highlight_color);

    print_decl (ctxt);

    ctxt.end_highlight_color ();
    ctxt.end_quote ();
  }

  فراغ print_decl (pp_markup::context &ctxt)
  {
    pretty_printer *ثابت pp = &ctxt.m_pp;
    pp->set_padding (pp_none);
    𐤀𐤌 (DECL_NAME (m_decl))
      pp_identifier (pp, lang_hooks.decl_printable_name (m_decl, 2));
    وإلا
      pp_string (pp, _("({anonymous})"));
  }

خاص:
  tree m_decl;
  ثابت حرف *m_highlight_color;
};

/* If TYPE is from a typedef, issue a note showing the location
   to the user.
   Use HIGHLIGHT_COLOR as the highlight color.  */

ساكن فراغ
maybe_inform_typedef_location (tree type, ثابت حرف *highlight_color)
{
  𐤀𐤌 (!typedef_variant_p (type))
    أرجع;

  tree typedef_decl = TYPE_NAME (type);
  gcc_assert (TREE_CODE (typedef_decl) == TYPE_DECL);
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

ساكن tree
convert_for_assignment (location_t location, location_t expr_loc, tree type,
			tree rhs, tree origtype, تعداد impl_conv errtype,
			منطقي null_pointer_constant, tree fundecl,
			tree function, صحيح parmnum, صحيح warnopt /* = 0 */)
{
  تعداد tree_code codel = TREE_CODE (type);
  tree orig_rhs = rhs;
  tree rhstype;
  تعداد tree_code coder;
  tree rname = NULL_TREE;
  منطقي objc_ok = خطأ;

  /* Use the expansion point location to handle cases such as user's
     function returning a wrong-type macro defined in a system header.  */
  location = expansion_point_location_if_in_system_header (location);

  𐤀𐤌 (errtype == ic_argpass)
    {
      tree selector;
      /* Change pointer to function to the function itself for
	 diagnostics.  */
      𐤀𐤌 (TREE_CODE (function) == ADDR_EXPR
	  && TREE_CODE (TREE_OPERAND (function, 0)) == FUNCTION_DECL)
	function = TREE_OPERAND (function, 0);

      /* Handle an ObjC selector specially for diagnostics.  */
      selector = objc_message_selector ();
      rname = function;
      𐤀𐤌 (selector && parmnum > 2)
	{
	  rname = selector;
	  parmnum -= 2;
	}
    }

  /* This macro is used to emit diagnostics to ensure that all format
     strings are complete sentences, visible to gettext and checked at
     compile time.  */
#define PEDWARN_FOR_ASSIGNMENT(LOCATION, PLOC, OPT, AR, AS, IN, RE)	 \
  𐤐𐤏𐤋 {                                                                   \
    بدل (errtype)                                                     \
      {                                                                  \
      حالة ic_argpass:                                                   \
	{								\
	  auto_diagnostic_group d;						\
	  𐤀𐤌 (pedwarn (PLOC, OPT, AR, parmnum, rname))		\
	    inform_for_arg (fundecl, (PLOC), parmnum, type, rhstype); \
	}								\
        اكسر;                                                           \
      حالة ic_assign:                                                    \
        pedwarn (LOCATION, OPT, AS);                                     \
        اكسر;                                                           \
      حالة ic_init:                                                      \
      حالة ic_init_const:                                                \
        pedwarn_init (LOCATION, OPT, IN);                                \
        اكسر;                                                           \
      حالة ic_return:                                                    \
        pedwarn (LOCATION, OPT, RE);					 \
        اكسر;                                                           \
      افتراضي:                                                           \
        gcc_unreachable ();                                              \
      }                                                                  \
  } طالما (0)

  /* This macro is used to emit diagnostics to ensure that all format
     strings are complete sentences, visible to gettext and checked at
     compile time.  It can be called with 'pedwarn' or 'warning_at'.  */
#define WARNING_FOR_QUALIFIERS(PEDWARN, LOCATION, PLOC, OPT, AR, AS, IN, RE, QUALS) \
  𐤐𐤏𐤋 {                                                                   \
    بدل (errtype)                                                     \
      {                                                                  \
      حالة ic_argpass:                                                   \
	{								 \
	  auto_diagnostic_group d;					 \
	  𐤀𐤌 (PEDWARN) {						 \
	    𐤀𐤌 (pedwarn (PLOC, OPT, AR, parmnum, rname, QUALS))          \
	      inform_for_arg (fundecl, (PLOC), parmnum, type, rhstype);  \
	  } وإلا {							 \
	    𐤀𐤌 (warning_at (PLOC, OPT, AR, parmnum, rname, QUALS))	 \
	      inform_for_arg (fundecl, (PLOC), parmnum, type, rhstype);  \
	  }								 \
	}								 \
        اكسر;                                                           \
      حالة ic_assign:                                                    \
	𐤀𐤌 (PEDWARN)							 \
	  pedwarn (LOCATION, OPT, AS, QUALS);                            \
	وإلا								 \
	  warning_at (LOCATION, OPT, AS, QUALS);                         \
        اكسر;                                                           \
      حالة ic_init:                                                      \
      حالة ic_init_const:                                                \
	𐤀𐤌 (PEDWARN)							 \
	  pedwarn (LOCATION, OPT, IN, QUALS);                            \
	وإلا								 \
	  warning_at (LOCATION, OPT, IN, QUALS);                         \
        اكسر;                                                           \
      حالة ic_return:                                                    \
	𐤀𐤌 (PEDWARN)							 \
	  pedwarn (LOCATION, OPT, RE, QUALS);                            \
	وإلا								 \
	  warning_at (LOCATION, OPT, RE, QUALS);                         \
        اكسر;                                                           \
      افتراضي:                                                           \
        gcc_unreachable ();                                              \
      }                                                                  \
  } طالما (0)

  /* This macro is used to emit diagnostics to ensure that all format
     strings are complete sentences, visible to gettext and checked at
     compile time.  It is the same as PEDWARN_FOR_ASSIGNMENT but with an
     extra parameter to enumerate qualifiers.  */
#define PEDWARN_FOR_QUALIFIERS(LOCATION, PLOC, OPT, AR, AS, IN, RE, QUALS) \
   WARNING_FOR_QUALIFIERS (true, LOCATION, PLOC, OPT, AR, AS, IN, RE, QUALS)


  𐤀𐤌 (TREE_CODE (rhs) == EXCESS_PRECISION_EXPR)
    rhs = TREE_OPERAND (rhs, 0);

  rhstype = TREE_TYPE (rhs);
  coder = TREE_CODE (rhstype);

  𐤀𐤌 (coder == ERROR_MARK)
    أرجع error_mark_node;

  𐤀𐤌 (c_dialect_objc ())
    {
      صحيح parmno;

      بدل (errtype)
	{
	حالة ic_return:
	  parmno = 0;
	  اكسر;

	حالة ic_assign:
	  parmno = -1;
	  اكسر;

	حالة ic_init:
	حالة ic_init_const:
	  parmno = -2;
	  اكسر;

	افتراضي:
	  parmno = parmnum;
	  اكسر;
	}

      objc_ok = objc_compare_types (type, rhstype, parmno, rname);
    }

  𐤀𐤌 (warn_cxx_compat)
    {
      tree checktype = origtype != NULL_TREE ? origtype : rhstype;
      𐤀𐤌 (checktype != error_mark_node
	  && TREE_CODE (type) == ENUMERAL_TYPE
	  && TYPE_MAIN_VARIANT (checktype) != TYPE_MAIN_VARIANT (type))
	بدل (errtype)
	  {
	  حالة ic_argpass:
	    𐤀𐤌 (pedwarn (expr_loc, OPT_Wc___compat, "enum conversion when "
			 "passing argument %d of %qE is invalid in C++",
			 parmnum, rname))
	      inform ((fundecl && !DECL_IS_UNDECLARED_BUILTIN (fundecl))
		      ? DECL_SOURCE_LOCATION (fundecl) : expr_loc,
		      "expected %qT but argument is of type %qT",
		      type, rhstype);
	    اكسر;
	  حالة ic_assign:
	    pedwarn (location, OPT_Wc___compat, "enum conversion from %qT to "
		     "%qT in assignment is invalid in C++", rhstype, type);
	    اكسر;
	  حالة ic_init:
	  حالة ic_init_const:
	    pedwarn_init (location, OPT_Wc___compat, "enum conversion from "
			  "%qT to %qT in initialization is invalid in C++",
			  rhstype, type);
	    اكسر;
	  حالة ic_return:
	    pedwarn (location, OPT_Wc___compat, "enum conversion from %qT to "
		     "%qT in return is invalid in C++", rhstype, type);
	    اكسر;
	  افتراضي:
	    gcc_unreachable ();
	  }
    }

  𐤀𐤌 (warn_enum_conversion)
    {
      tree checktype = origtype != NULL_TREE ? origtype : rhstype;
      𐤀𐤌 (checktype != error_mark_node
	  && TREE_CODE (checktype) == ENUMERAL_TYPE
	  && TREE_CODE (type) == ENUMERAL_TYPE
	  && !comptypes (TYPE_MAIN_VARIANT (checktype), TYPE_MAIN_VARIANT (type)))
       {
	  gcc_rich_location loc (location);
	  warning_at (&loc, OPT_Wenum_conversion,
		      "implicit conversion from %qT to %qT",
		      checktype, type);
       }
    }

  𐤀𐤌 (TYPE_MAIN_VARIANT (type) == TYPE_MAIN_VARIANT (rhstype))
    {
      warn_for_address_of_packed_member (type, orig_rhs);
      𐤀𐤌 (type != rhstype)
	/* Convert RHS to TYPE in order to not lose TYPE in diagnostics.  */
	rhs = convert (type, rhs);
      أرجع rhs;
    }

  𐤀𐤌 (coder == VOID_TYPE)
    {
      /* Except for passing an argument to an unprototyped function,
	 this is a constraint violation.  When passing an argument to
	 an unprototyped function, it is compile-time undefined;
	 making it a constraint in that case was rejected in
	 DR#252.  */
      ثابت حرف msg[] = "void value not ignored as it ought to be";
      𐤀𐤌 (warnopt)
	warning_at (location, warnopt, msg);
      وإلا
	error_at (location, msg);
      أرجع error_mark_node;
    }
  rhs = require_complete_type (location, rhs);
  𐤀𐤌 (rhs == error_mark_node)
    أرجع error_mark_node;

  𐤀𐤌 (coder == POINTER_TYPE && reject_gcc_builtin (rhs))
    أرجع error_mark_node;

  /* A non-reference type can convert to a reference.  This handles
     va_start, va_copy and possibly port built-ins.  */
  𐤀𐤌 (codel == REFERENCE_TYPE && coder != REFERENCE_TYPE)
    {
      𐤀𐤌 (!lvalue_p (rhs))
	{
	  ثابت حرف msg[] = "cannot pass rvalue to reference parameter";
	  𐤀𐤌 (warnopt)
	    warning_at (location, warnopt, msg);
	  وإلا
	    error_at (location, msg);
	  أرجع error_mark_node;
	}
      𐤀𐤌 (!c_mark_addressable (rhs))
	أرجع error_mark_node;
      rhs = build1 (ADDR_EXPR, c_build_pointer_type (TREE_TYPE (rhs)), rhs);
      SET_EXPR_LOCATION (rhs, location);

      rhs = convert_for_assignment (location, expr_loc,
				    c_build_pointer_type (TREE_TYPE (type)),
				    rhs, origtype, errtype,
				    null_pointer_constant, fundecl, function,
				    parmnum, warnopt);
      𐤀𐤌 (rhs == error_mark_node)
	أرجع error_mark_node;

      rhs = build1 (NOP_EXPR, type, rhs);
      SET_EXPR_LOCATION (rhs, location);
      أرجع rhs;
    }
  /* Some types can interconvert without explicit casts.  */
  وإلا 𐤀𐤌 (codel == VECTOR_TYPE && coder == VECTOR_TYPE
	   && vector_types_convertible_p (type, TREE_TYPE (rhs), true))
    أرجع convert (type, rhs);
  /* Arithmetic types all interconvert, and enum is treated like int.  */
  وإلا 𐤀𐤌 ((codel == INTEGER_TYPE || codel == REAL_TYPE
	    || codel == FIXED_POINT_TYPE
	    || codel == ENUMERAL_TYPE || codel == COMPLEX_TYPE
	    || codel == BOOLEAN_TYPE || codel == BITINT_TYPE)
	   && (coder == INTEGER_TYPE || coder == REAL_TYPE
	       || coder == FIXED_POINT_TYPE
	       || coder == ENUMERAL_TYPE || coder == COMPLEX_TYPE
	       || coder == BOOLEAN_TYPE || coder == BITINT_TYPE))
    {
      𐤀𐤌 (warnopt && errtype == ic_argpass)
	maybe_warn_builtin_no_proto_arg (expr_loc, fundecl, parmnum, type,
					 rhstype);

      منطقي save = in_late_binary_op;
      𐤀𐤌 (C_BOOLEAN_TYPE_P (type) || codel == COMPLEX_TYPE
	  || (coder == REAL_TYPE
	      && (codel == INTEGER_TYPE || codel == ENUMERAL_TYPE)
	      && sanitize_flags_p (SANITIZE_FLOAT_CAST)))
	in_late_binary_op = true;
      tree ret = convert_and_check (expr_loc != UNKNOWN_LOCATION
				    ? expr_loc : location, type, orig_rhs,
				    errtype == ic_init_const);
      in_late_binary_op = save;
      أرجع ret;
    }

  /* Aggregates in different TUs might need conversion.  */
  𐤀𐤌 ((codel == RECORD_TYPE || codel == UNION_TYPE)
      && codel == coder
      && comptypes (TYPE_MAIN_VARIANT (type), TYPE_MAIN_VARIANT (rhstype)))
    أرجع convert_and_check (expr_loc != UNKNOWN_LOCATION
			      ? expr_loc : location, type, rhs);

  /* Conversion to a transparent union or record from its member types.
     This applies only to function arguments.  */
  𐤀𐤌 (((codel == UNION_TYPE || codel == RECORD_TYPE)
      && TYPE_TRANSPARENT_AGGR (type))
      && errtype == ic_argpass)
    {
      tree memb, marginal_memb = NULL_TREE;

      لكل (memb = TYPE_FIELDS (type); memb ; memb = DECL_CHAIN (memb))
	{
	  tree memb_type = TREE_TYPE (memb);

	  𐤀𐤌 (comptypes (TYPE_MAIN_VARIANT (memb_type),
			 TYPE_MAIN_VARIANT (rhstype)))
	    اكسر;

	  𐤀𐤌 (TREE_CODE (memb_type) != POINTER_TYPE)
	    استمر;

	  𐤀𐤌 (coder == POINTER_TYPE)
	    {
	      tree ttl = TREE_TYPE (memb_type);
	      tree ttr = TREE_TYPE (rhstype);

	      /* Any non-function converts to a [const][volatile] void *
		 and vice versa; otherwise, targets must be the same.
		 Meanwhile, the lhs target must have all the qualifiers of
		 the rhs.  */
	      𐤀𐤌 ((VOID_TYPE_P (ttl) && !TYPE_ATOMIC (ttl))
		  || (VOID_TYPE_P (ttr) && !TYPE_ATOMIC (ttr))
		  || comp_target_types (location, memb_type, rhstype))
		{
		  صحيح lquals = TYPE_QUALS (ttl) & ~TYPE_QUAL_ATOMIC;
		  صحيح rquals = TYPE_QUALS (ttr) & ~TYPE_QUAL_ATOMIC;
		  /* If this type won't generate any warnings, use it.  */
		  𐤀𐤌 (lquals == rquals
		      || ((TREE_CODE (ttr) == FUNCTION_TYPE
			   && TREE_CODE (ttl) == FUNCTION_TYPE)
			  ? ((lquals | rquals) == rquals)
			  : ((lquals | rquals) == lquals)))
		    اكسر;

		  /* Keep looking for a better type, but remember this one.  */
		  𐤀𐤌 (!marginal_memb)
		    marginal_memb = memb;
		}
	    }

	  /* Can convert integer zero to any pointer type.  */
	  𐤀𐤌 (null_pointer_constant)
	    {
	      rhs = null_pointer_node;
	      اكسر;
	    }
	}

      𐤀𐤌 (memb || marginal_memb)
	{
	  𐤀𐤌 (!memb)
	    {
	      /* We have only a marginally acceptable member type;
		 it needs a warning.  */
	      tree ttl = TREE_TYPE (TREE_TYPE (marginal_memb));
	      tree ttr = TREE_TYPE (rhstype);

	      /* Const and volatile mean something different for function
		 types, so the usual warnings are not appropriate.  */
	      𐤀𐤌 (TREE_CODE (ttr) == FUNCTION_TYPE
		  && TREE_CODE (ttl) == FUNCTION_TYPE)
		{
		  /* Because const and volatile on functions are
		     restrictions that say the function will not do
		     certain things, it is okay to use a const or volatile
		     function where an ordinary one is wanted, but not
		     vice-versa.  */
		  𐤀𐤌 (TYPE_QUALS_NO_ADDR_SPACE (ttl)
		      & ~TYPE_QUALS_NO_ADDR_SPACE (ttr))
		    PEDWARN_FOR_QUALIFIERS (location, expr_loc,
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
	      وإلا 𐤀𐤌 (TYPE_QUALS_NO_ADDR_SPACE (ttr)
		       & ~TYPE_QUALS_NO_ADDR_SPACE (ttl))
		PEDWARN_FOR_QUALIFIERS (location, expr_loc,
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

	  𐤀𐤌 (!fundecl || !DECL_IN_SYSTEM_HEADER (fundecl))
	    pedwarn (location, OPT_Wpedantic,
		     "ISO C prohibits argument conversion to union type");

	  rhs = fold_convert_loc (location, TREE_TYPE (memb), rhs);
	  أرجع build_constructor_single (type, memb, rhs);
	}
    }

  /* Conversions among pointers */
  وإلا 𐤀𐤌 ((codel == POINTER_TYPE || codel == REFERENCE_TYPE)
	   && (coder == codel))
    {
      /* If RHS refers to a built-in declared without a prototype
	 BLTIN is the declaration of the built-in with a prototype
	 and RHSTYPE is set to the actual type of the built-in.  */
      tree bltin;
      rhstype = type_or_builtin_type (rhs, &bltin);

      tree ttl = TREE_TYPE (type);
      tree ttr = TREE_TYPE (rhstype);
      منطقي is_opaque_pointer;
      منطقي target_cmp = خطأ;   /* Cache comp_target_types () result.  */
      addr_space_t asl;
      addr_space_t asr;

      tree mvl = remove_qualifiers (ttl);
      tree mvr = remove_qualifiers (ttr);

      /* Opaque pointers are treated like void pointers.  */
      is_opaque_pointer = vector_targets_convertible_p (ttl, ttr);

      /* The Plan 9 compiler permits a pointer to a struct to be
	 automatically converted into a pointer to an anonymous field
	 within the struct.  */
      𐤀𐤌 (flag_plan9_extensions
	  && RECORD_OR_UNION_TYPE_P (mvl)
	  && RECORD_OR_UNION_TYPE_P (mvr)
	  && mvl != mvr)
	{
	  tree new_rhs = convert_to_anonymous_field (location, type, rhs);
	  𐤀𐤌 (new_rhs != NULL_TREE)
	    {
	      rhs = new_rhs;
	      rhstype = TREE_TYPE (rhs);
	      coder = TREE_CODE (rhstype);
	      ttr = TREE_TYPE (rhstype);
	      mvr = TYPE_MAIN_VARIANT (ttr);
	    }
	}

      /* C++ does not allow the implicit conversion void* -> T*.  However,
	 for the purpose of reducing the number of false positives, we
	 tolerate the special case of

		int *p = NULL;

	 where NULL is typically defined in C to be '(void *) 0'.  */
      𐤀𐤌 (VOID_TYPE_P (ttr) && rhs != null_pointer_node && !VOID_TYPE_P (ttl))
	warning_at (errtype == ic_argpass ? expr_loc : location,
		    OPT_Wc___compat,
		    "request for implicit conversion "
		    "from %qT to %qT not permitted in C++", rhstype, type);

      /* Warn of new allocations that are not big enough for the target
	 type.  */
      𐤀𐤌 (warn_alloc_size && TREE_CODE (rhs) == CALL_EXPR)
	𐤀𐤌 (tree fndecl = get_callee_fndecl (rhs))
	  𐤀𐤌 (DECL_IS_MALLOC (fndecl))
	    {
	      tree attrs = TYPE_ATTRIBUTES (TREE_TYPE (fndecl));
	      tree alloc_size = lookup_attribute ("alloc_size", attrs);
	      𐤀𐤌 (alloc_size)
		warn_for_alloc_size (location, ttl, rhs, alloc_size);
	    }

      /* See if the pointers point to incompatible address spaces.  */
      asl = TYPE_ADDR_SPACE (ttl);
      asr = TYPE_ADDR_SPACE (ttr);
      𐤀𐤌 (!null_pointer_constant_p (rhs)
	  && asr != asl && !targetm.addr_space.subset_p (asr, asl))
	{
	  auto_diagnostic_group d;
	  منطقي diagnosed = true;
	  بدل (errtype)
	    {
	    حالة ic_argpass:
	      {
		ثابت حرف msg[] = G_("passing argument %d of %qE from "
				      "pointer to non-enclosed address space");
		𐤀𐤌 (warnopt)
		  diagnosed
		    = warning_at (expr_loc, warnopt, msg, parmnum, rname);
		وإلا
		  error_at (expr_loc, msg, parmnum, rname);
	      اكسر;
	      }
	    حالة ic_assign:
	      {
		ثابت حرف msg[] = G_("assignment from pointer to "
				      "non-enclosed address space");
		𐤀𐤌 (warnopt)
		  diagnosed = warning_at (location, warnopt, msg);
		وإلا
		  error_at (location, msg);
		اكسر;
	      }
	    حالة ic_init:
	    حالة ic_init_const:
	      {
		ثابت حرف msg[] = G_("initialization from pointer to "
				      "non-enclosed address space");
		𐤀𐤌 (warnopt)
		  diagnosed = warning_at (location, warnopt, msg);
		وإلا
		  error_at (location, msg);
		اكسر;
	      }
	    حالة ic_return:
	      {
		ثابت حرف msg[] = G_("return from pointer to "
				      "non-enclosed address space");
		𐤀𐤌 (warnopt)
		  diagnosed = warning_at (location, warnopt, msg);
		وإلا
		  error_at (location, msg);
		اكسر;
	      }
	    افتراضي:
	      gcc_unreachable ();
	    }
	  𐤀𐤌 (diagnosed)
	    {
	      𐤀𐤌 (errtype == ic_argpass)
		inform_for_arg (fundecl, expr_loc, parmnum, type, rhstype);
	      وإلا
		inform (location, "expected %qT but pointer is of type %qT",
			type, rhstype);
	    }
	  أرجع error_mark_node;
	}

      /* Check if the right-hand side has a format attribute but the
	 left-hand side doesn't.  */
      𐤀𐤌 (warn_suggest_attribute_format
	  && check_missing_format_attribute (type, rhstype))
	{
	  بدل (errtype)
	  {
	  حالة ic_argpass:
	    warning_at (expr_loc, OPT_Wsuggest_attribute_format,
			"argument %d of %qE might be "
			"a candidate for a format attribute",
			parmnum, rname);
	    اكسر;
	  حالة ic_assign:
	    warning_at (location, OPT_Wsuggest_attribute_format,
			"assignment left-hand side might be "
			"a candidate for a format attribute");
	    اكسر;
	  حالة ic_init:
	  حالة ic_init_const:
	    warning_at (location, OPT_Wsuggest_attribute_format,
			"initialization left-hand side might be "
			"a candidate for a format attribute");
	    اكسر;
	  حالة ic_return:
	    warning_at (location, OPT_Wsuggest_attribute_format,
			"return type might be "
			"a candidate for a format attribute");
	    اكسر;
	  افتراضي:
	    gcc_unreachable ();
	  }
	}

      /* See if the pointers point to incompatible scalar storage orders.  */
      𐤀𐤌 (warn_scalar_storage_order
	  && !null_pointer_constant_p (rhs)
	  && (AGGREGATE_TYPE_P (ttl) && TYPE_REVERSE_STORAGE_ORDER (ttl))
	     != (AGGREGATE_TYPE_P (ttr) && TYPE_REVERSE_STORAGE_ORDER (ttr)))
	{
	  tree t;

	  بدل (errtype)
	  {
	  حالة ic_argpass:
	    /* Do not warn for built-in functions, for example memcpy, since we
	       control how they behave and they can be useful in this area.  */
	    𐤀𐤌 (TREE_CODE (rname) != FUNCTION_DECL
		|| !fndecl_built_in_p (rname))
	      warning_at (location, OPT_Wscalar_storage_order,
			  "passing argument %d of %qE from incompatible "
			  "scalar storage order", parmnum, rname);
	    اكسر;
	  حالة ic_assign:
	    /* Do not warn if the RHS is a call to a function that returns a
	       pointer that is not an alias.  */
	    𐤀𐤌 (TREE_CODE (rhs) != CALL_EXPR
		|| (t = get_callee_fndecl (rhs)) == NULL_TREE
		|| !DECL_IS_MALLOC (t))
	      warning_at (location, OPT_Wscalar_storage_order,
			  "assignment to %qT from pointer type %qT with "
			  "incompatible scalar storage order", type, rhstype);
	    اكسر;
	  حالة ic_init:
	  حالة ic_init_const:
	    /* Likewise.  */
	    𐤀𐤌 (TREE_CODE (rhs) != CALL_EXPR
		|| (t = get_callee_fndecl (rhs)) == NULL_TREE
		|| !DECL_IS_MALLOC (t))
	      warning_at (location, OPT_Wscalar_storage_order,
			  "initialization of %qT from pointer type %qT with "
			  "incompatible scalar storage order", type, rhstype);
	    اكسر;
	  حالة ic_return:
	    warning_at (location, OPT_Wscalar_storage_order,
			"returning %qT from pointer type with incompatible "
			"scalar storage order %qT", rhstype, type);
	    اكسر;
	  افتراضي:
	    gcc_unreachable ();
	  }
	}

      /* Any non-function converts to a [const][volatile] void *
	 and vice versa; otherwise, targets must be the same.
	 Meanwhile, the lhs target must have all the qualifiers of the rhs.  */
      𐤀𐤌 ((VOID_TYPE_P (ttl) && !TYPE_ATOMIC (ttl))
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
	  𐤀𐤌 (TREE_CODE (ttr) == ARRAY_TYPE)
	    {
	      ttr = strip_array_types (ttr);
	      ttl = strip_array_types (ttl);

	      𐤀𐤌 (TYPE_QUALS_NO_ADDR_SPACE_NO_ATOMIC (ttr)
		  & ~TYPE_QUALS_NO_ADDR_SPACE_NO_ATOMIC (ttl))
		WARNING_FOR_QUALIFIERS (flag_isoc23,
					location, expr_loc,
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
          وإلا 𐤀𐤌 (pedantic
	      && ((VOID_TYPE_P (ttl) && TREE_CODE (ttr) == FUNCTION_TYPE)
		  ||
		  (VOID_TYPE_P (ttr)
		   && !null_pointer_constant
		   && TREE_CODE (ttl) == FUNCTION_TYPE)))
	    PEDWARN_FOR_ASSIGNMENT (location, expr_loc, OPT_Wpedantic,
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
	  وإلا 𐤀𐤌 (TREE_CODE (ttr) != FUNCTION_TYPE
		   && TREE_CODE (ttl) != FUNCTION_TYPE)
	    {
	       /* Assignments between atomic and non-atomic objects are OK.  */
	       منطقي warn_quals_ped = TYPE_QUALS_NO_ADDR_SPACE_NO_ATOMIC (ttr)
				     & ~TYPE_QUALS_NO_ADDR_SPACE_NO_ATOMIC (ttl);
	       منطقي warn_quals = TYPE_QUALS_NO_ADDR_SPACE_NO_ATOMIC (ttr)
				 & ~TYPE_QUALS_NO_ADDR_SPACE_NO_ATOMIC (strip_array_types (ttl));

	      /* Don't warn about loss of qualifier for conversions from
		 qualified void* to pointers to arrays with corresponding
		 qualifier on the element type (except for pedantic before C23). */
	      𐤀𐤌 (warn_quals || (warn_quals_ped && pedantic && !flag_isoc23))
		PEDWARN_FOR_QUALIFIERS (location, expr_loc,
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
	      وإلا 𐤀𐤌 (warn_quals_ped)
		pedwarn_c11 (location, OPT_Wc11_c23_compat,
			     "array with qualifier on the element is not qualified before C23");

	      /* If this is not a case of ignoring a mismatch in signedness,
		 no warning.  */
	      وإلا 𐤀𐤌 (VOID_TYPE_P (ttl) || VOID_TYPE_P (ttr)
		       || target_cmp)
		;
	      /* If there is a mismatch, do warn.  */
	      وإلا 𐤀𐤌 (warn_pointer_sign)
		بدل (errtype)
		  {
		  حالة ic_argpass:
		    {
		      auto_diagnostic_group d;
		      range_label_for_type_mismatch rhs_label (rhstype, type);
		      gcc_rich_location richloc (expr_loc, &rhs_label,
						 highlight_colors::actual);
		      𐤀𐤌 (pedwarn (&richloc, OPT_Wpointer_sign,
				   "pointer targets in passing argument %d of "
				   "%qE differ in signedness", parmnum, rname))
			inform_for_arg (fundecl, expr_loc, parmnum, type,
					rhstype);
		    }
		    اكسر;
		  حالة ic_assign:
		    pedwarn (location, OPT_Wpointer_sign,
			     "pointer targets in assignment from %qT to %qT "
			     "differ in signedness", rhstype, type);
		    اكسر;
		  حالة ic_init:
		  حالة ic_init_const:
		    pedwarn_init (location, OPT_Wpointer_sign,
				  "pointer targets in initialization of %qT "
				  "from %qT differ in signedness", type,
				  rhstype);
		    اكسر;
		  حالة ic_return:
		    pedwarn (location, OPT_Wpointer_sign, "pointer targets in "
			     "returning %qT from a function with return type "
			     "%qT differ in signedness", rhstype, type);
		    اكسر;
		  افتراضي:
		    gcc_unreachable ();
		  }
	    }
	  وإلا 𐤀𐤌 (TREE_CODE (ttl) == FUNCTION_TYPE
		   && TREE_CODE (ttr) == FUNCTION_TYPE)
	    {
	      /* Because const and volatile on functions are restrictions
		 that say the function will not do certain things,
		 it is okay to use a const or volatile function
		 where an ordinary one is wanted, but not vice-versa.  */
	      𐤀𐤌 (TYPE_QUALS_NO_ADDR_SPACE (ttl)
		  & ~TYPE_QUALS_NO_ADDR_SPACE (ttr))
		PEDWARN_FOR_QUALIFIERS (location, expr_loc,
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
      وإلا 𐤀𐤌 (!objc_ok)
	{
	  auto_diagnostic_group d;
	  منطقي warned = خطأ;
	  pp_markup::element_expected_type e_type (type);
	  pp_markup::element_actual_type e_rhstype (rhstype);
	  بدل (errtype)
	    {
	    حالة ic_argpass:
	      {
		range_label_for_type_mismatch rhs_label (rhstype, type);
		gcc_rich_location richloc (expr_loc, &rhs_label,
					   highlight_colors::actual);
		warned
		  = permerror_opt (&richloc, OPT_Wincompatible_pointer_types,
				   "passing argument %d of %qE from "
				   "incompatible pointer type",
				   parmnum, rname);
		𐤀𐤌 (warned)
		  inform_for_arg (fundecl, expr_loc, parmnum, type, rhstype);
	      }
	      اكسر;
	    حالة ic_assign:
	      𐤀𐤌 (bltin)
		warned
		  = permerror_opt (location, OPT_Wincompatible_pointer_types,
				   "assignment to %e from pointer to "
				   "%qD with incompatible type %e",
				   &e_type, bltin, &e_rhstype);
	      وإلا
		warned
		  = permerror_opt (location, OPT_Wincompatible_pointer_types,
				   "assignment to %e from incompatible "
				   "pointer type %e",
				   &e_type, &e_rhstype);
	      اكسر;
	    حالة ic_init:
	    حالة ic_init_const:
	      𐤀𐤌 (bltin)
		warned
		  = permerror_init (location, OPT_Wincompatible_pointer_types,
				    "initialization of %e from pointer to "
				    "%qD with incompatible type %e",
				    &e_type, bltin, &e_rhstype);
	      وإلا
		warned
		  = permerror_init (location, OPT_Wincompatible_pointer_types,
				    "initialization of %e from incompatible "
				    "pointer type %e",
				    &e_type, &e_rhstype);
	      اكسر;
	    حالة ic_return:
	      𐤀𐤌 (bltin)
		warned
		  = permerror_opt (location, OPT_Wincompatible_pointer_types,
				   "returning pointer to %qD of type %e from "
				   "a function with incompatible type %e",
				   bltin, &e_rhstype, &e_type);
	      وإلا
		warned
		  = permerror_opt (location, OPT_Wincompatible_pointer_types,
				   "returning %e from a function with "
				   "incompatible return type %e",
				   &e_rhstype, &e_type);
	      اكسر;
	    افتراضي:
	      gcc_unreachable ();
	    }
	  𐤀𐤌 (warned)
	    {
	      /* If the mismatching function type is a pointer to a function,
		 try to show the decl of the function.  */
	      𐤀𐤌 (TREE_CODE (rhs) == ADDR_EXPR
		  && TREE_CODE (TREE_OPERAND (rhs, 0)) == FUNCTION_DECL)
		{
		  tree rhs_fndecl = TREE_OPERAND (rhs, 0);
		  𐤀𐤌 (!DECL_IS_UNDECLARED_BUILTIN (rhs_fndecl))
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

      أرجع convert (type, rhs);
    }
  وإلا 𐤀𐤌 (codel == POINTER_TYPE && coder == ARRAY_TYPE)
    {
      /* ??? This should not be an error when inlining calls to
	 unprototyped functions.  */
      ثابت حرف msg[] = "invalid use of non-lvalue array";
      𐤀𐤌 (warnopt)
	warning_at (location, warnopt, msg);
      وإلا
	error_at (location, msg);
      أرجع error_mark_node;
    }
  وإلا 𐤀𐤌 (codel == POINTER_TYPE
	   && (coder == INTEGER_TYPE
	       || coder == ENUMERAL_TYPE
	       || coder == BOOLEAN_TYPE
	       || coder == NULLPTR_TYPE
	       || coder == BITINT_TYPE))
    {
      𐤀𐤌 (null_pointer_constant && c_inhibit_evaluation_warnings == 0
	  && coder != NULLPTR_TYPE)
	warning_at (location, OPT_Wzero_as_null_pointer_constant,
		    "zero as null pointer constant");
      /* A NULLPTR type is just a nullptr always.  */
      𐤀𐤌 (coder == NULLPTR_TYPE)
	أرجع omit_one_operand_loc (expr_loc, type, nullptr_node, rhs);
      /* An explicit constant 0 or type nullptr_t can convert to a pointer,
	 or one that results from arithmetic, even including a cast to
	 integer type.  */
      وإلا 𐤀𐤌 (!null_pointer_constant)
	بدل (errtype)
	  {
	  حالة ic_argpass:
	    {
	      auto_diagnostic_group d;
	      range_label_for_type_mismatch rhs_label (rhstype, type);
	      gcc_rich_location richloc (expr_loc, &rhs_label,
					 highlight_colors::actual);
	      𐤀𐤌 (permerror_opt (&richloc, OPT_Wint_conversion,
				 "passing argument %d of %qE makes pointer "
				 "from integer without a cast", parmnum, rname))
		{
		  maybe_emit_indirection_note (expr_loc, rhs, type);
		  inform_for_arg (fundecl, expr_loc, parmnum, type, rhstype);
		}
	    }
	    اكسر;
	  حالة ic_assign:
	    permerror_opt (location, OPT_Wint_conversion,
			   "assignment to %qT from %qT makes pointer from "
			   "integer without a cast", type, rhstype);
	    اكسر;
	  حالة ic_init:
	  حالة ic_init_const:
	    permerror_init (location, OPT_Wint_conversion,
			    "initialization of %qT from %qT makes pointer "
			    "from integer without a cast", type, rhstype);
	    اكسر;
	  حالة ic_return:
	    permerror_init (location, OPT_Wint_conversion,
			    "returning %qT from a function with return type "
			    "%qT makes pointer from integer without a cast",
			    rhstype, type);
	    اكسر;
	  افتراضي:
	    gcc_unreachable ();
	  }

      أرجع convert (type, rhs);
    }
  وإلا 𐤀𐤌 ((codel == INTEGER_TYPE || codel == BITINT_TYPE)
	   && coder == POINTER_TYPE)
    {
      بدل (errtype)
	{
	حالة ic_argpass:
	  {
	    auto_diagnostic_group d;
	    range_label_for_type_mismatch rhs_label (rhstype, type);
	    gcc_rich_location richloc (expr_loc, &rhs_label,
				       highlight_colors::actual);
	    𐤀𐤌 (permerror_opt (&richloc, OPT_Wint_conversion,
			       "passing argument %d of %qE makes integer from "
			       "pointer without a cast", parmnum, rname))
	      {
		maybe_emit_indirection_note (expr_loc, rhs, type);
		inform_for_arg (fundecl, expr_loc, parmnum, type, rhstype);
	      }
	  }
	  اكسر;
	حالة ic_assign:
	  permerror_opt (location, OPT_Wint_conversion,
			 "assignment to %qT from %qT makes integer from "
			 "pointer without a cast", type, rhstype);
	  اكسر;
	حالة ic_init:
	حالة ic_init_const:
	  permerror_init (location, OPT_Wint_conversion,
			  "initialization of %qT from %qT makes integer "
			  "from pointer without a cast", type, rhstype);
	  اكسر;
	حالة ic_return:
	  permerror_opt (location, OPT_Wint_conversion, "returning %qT from a "
			 "function with return type %qT makes integer from "
			 "pointer without a cast", rhstype, type);
	  اكسر;
	افتراضي:
	  gcc_unreachable ();
	}

      أرجع convert (type, rhs);
    }
  وإلا 𐤀𐤌 (C_BOOLEAN_TYPE_P (type)
	   /* The type nullptr_t may be converted to bool.  The
	      result is false.  */
	   && (coder == POINTER_TYPE || coder == NULLPTR_TYPE))
    {
      tree ret;
      منطقي save = in_late_binary_op;
      in_late_binary_op = true;
      ret = convert (type, rhs);
      in_late_binary_op = save;
      أرجع ret;
    }
  وإلا 𐤀𐤌 (codel == NULLPTR_TYPE && null_pointer_constant)
    أرجع convert (type, rhs);

  بدل (errtype)
    {
    حالة ic_argpass:
      {
	auto_diagnostic_group d;
	range_label_for_type_mismatch rhs_label (rhstype, type);
	gcc_rich_location richloc (expr_loc, &rhs_label,
				   highlight_colors::actual);
	ثابت حرف msg[] = G_("incompatible type for argument %d of %qE");
	𐤀𐤌 (warnopt)
	  warning_at (expr_loc, warnopt, msg, parmnum, rname);
	وإلا
	  error_at (&richloc, msg, parmnum, rname);
	inform_for_arg (fundecl, expr_loc, parmnum, type, rhstype);
      }
      اكسر;
    حالة ic_assign:
      {
	ثابت حرف msg[]
	  = G_("incompatible types when assigning to type %qT from type %qT");
	𐤀𐤌 (warnopt)
	  warning_at (expr_loc, 0, msg, type, rhstype);
	وإلا
	  error_at (expr_loc, msg, type, rhstype);
	اكسر;
      }
    حالة ic_init:
    حالة ic_init_const:
      {
	ثابت حرف msg[]
	  = G_("incompatible types when initializing type %qT using type %qT");
	𐤀𐤌 (warnopt)
	  warning_at (location, 0, msg, type, rhstype);
	وإلا
	  error_at (location, msg, type, rhstype);
	اكسر;
      }
    حالة ic_return:
      {
	ثابت حرف msg[]
	  = G_("incompatible types when returning type %qT but %qT was expected");
	𐤀𐤌 (warnopt)
	  warning_at (location, 0, msg, rhstype, type);
	وإلا
	  error_at (location, msg, rhstype, type);
	اكسر;
      }
    افتراضي:
      gcc_unreachable ();
    }

  أرجع error_mark_node;
}

/* If VALUE is a compound expr all of whose expressions are constant, then
   return its value.  Otherwise, return error_mark_node.

   This is for handling COMPOUND_EXPRs as initializer elements
   which is allowed with a warning when -pedantic is specified.  */

ساكن tree
valid_compound_expr_initializer (tree value, tree endtype)
{
  𐤀𐤌 (TREE_CODE (value) == COMPOUND_EXPR)
    {
      𐤀𐤌 (valid_compound_expr_initializer (TREE_OPERAND (value, 0), endtype)
	  == error_mark_node)
	أرجع error_mark_node;
      أرجع valid_compound_expr_initializer (TREE_OPERAND (value, 1),
					      endtype);
    }
  وإلا 𐤀𐤌 (!initializer_constant_valid_p (value, endtype))
    أرجع error_mark_node;
  وإلا
    أرجع value;
}

/* Perform appropriate conversions on the initial value of a variable,
   store it in the declaration DECL,
   and print any error messages that are appropriate.
   If ORIGTYPE is not NULL_TREE, it is the original type of INIT.
   If the init is invalid, store an ERROR_MARK.

   INIT_LOC is the location of the initial value.  */

فراغ
store_init_value (location_t init_loc, tree decl, tree init, tree origtype)
{
  tree value, type;
  منطقي npc = خطأ;
  منطقي int_const_expr = خطأ;
  منطقي arith_const_expr = خطأ;

  /* If variable's type was invalidly declared, just ignore it.  */

  type = TREE_TYPE (decl);
  𐤀𐤌 (TREE_CODE (type) == ERROR_MARK)
    أرجع;

  /* Digest the specified initializer into an expression.  */

  𐤀𐤌 (init)
    {
      npc = null_pointer_constant_p (init);
      int_const_expr = (TREE_CODE (init) == INTEGER_CST
			&& !TREE_OVERFLOW (init)
			&& INTEGRAL_TYPE_P (TREE_TYPE (init)));
      /* Not fully determined before folding.  */
      arith_const_expr = true;
    }
  منطقي constexpr_p = (VAR_P (decl)
		      && C_DECL_DECLARED_CONSTEXPR (decl));
  value = digest_init (init_loc, decl, type, init, origtype, npc,
		       int_const_expr, arith_const_expr, true,
		       TREE_STATIC (decl) || constexpr_p, constexpr_p);

  /* Store the expression if valid; else report error.  */

  𐤀𐤌 (!in_system_header_at (input_location)
      && AGGREGATE_TYPE_P (TREE_TYPE (decl)) && !TREE_STATIC (decl))
    warning (OPT_Wtraditional, "traditional C rejects automatic "
	     "aggregate initialization");

  𐤀𐤌 (value != error_mark_node || TREE_CODE (decl) != FUNCTION_DECL)
    DECL_INITIAL (decl) = value;

  /* ANSI wants warnings about out-of-range constant initializers.  */
  STRIP_TYPE_NOPS (value);
  𐤀𐤌 (TREE_STATIC (decl))
    constant_expression_warning (value);

  /* Check if we need to set array size from compound literal size.  */
  𐤀𐤌 (TREE_CODE (type) == ARRAY_TYPE
      && TYPE_DOMAIN (type) == NULL_TREE
      && value != error_mark_node)
    {
      tree inside_init = init;

      STRIP_TYPE_NOPS (inside_init);
      inside_init = fold (inside_init);

      𐤀𐤌 (TREE_CODE (inside_init) == COMPOUND_LITERAL_EXPR)
	{
	  tree cldecl = COMPOUND_LITERAL_EXPR_DECL (inside_init);

	  𐤀𐤌 (TYPE_DOMAIN (TREE_TYPE (cldecl)))
	    {
	      /* For int foo[] = (int [3]){1}; we need to set array size
		 now since later on array initializer will be just the
		 brace enclosed list of the compound literal.  */
	      tree etype = strip_array_types (TREE_TYPE (decl));
	      type = build_distinct_type_copy (TYPE_MAIN_VARIANT (type));
	      TYPE_DOMAIN (type) = TYPE_DOMAIN (TREE_TYPE (cldecl));
	      layout_type (type);
	      layout_decl (cldecl, 0);
	      TREE_TYPE (decl)
		= c_build_qualified_type (type, TYPE_QUALS (etype));
	    }
	}
    }
}

/* Methods for storing and printing names for error messages.  */

/* Implement a spelling stack that allows components of a name to be pushed
   and popped.  Each element on the stack is this structure.  */

بنية spelling
{
  صحيح kind;
  اتحاد
    {
      unsigned HOST_WIDE_INT i;
      ثابت حرف *s;
    } u;
};

#define SPELLING_STRING 1
#define SPELLING_MEMBER 2
#define SPELLING_BOUNDS 3

ساكن بنية spelling *spelling;	/* Next stack element (unused).  */
ساكن بنية spelling *spelling_base;	/* Spelling stack base.  */
ساكن صحيح spelling_size;		/* Size of the spelling stack.  */

/* Macros to save and restore the spelling stack around push_... functions.
   Alternative to SAVE_SPELLING_STACK.  */

#define SPELLING_DEPTH() (spelling - spelling_base)
#define RESTORE_SPELLING_DEPTH(DEPTH) (spelling = spelling_base + (DEPTH))

/* Push an element on the spelling stack with type KIND and assign VALUE
   to MEMBER.  */

#define PUSH_SPELLING(KIND, VALUE, MEMBER)				\
{									\
  صحيح depth = SPELLING_DEPTH ();					\
									\
  𐤀𐤌 (depth >= spelling_size)						\
    {									\
      spelling_size += 10;						\
      spelling_base = XRESIZEVEC (بنية spelling, spelling_base,	\
				  spelling_size);			\
      RESTORE_SPELLING_DEPTH (depth);					\
    }									\
									\
  spelling->kind = (KIND);						\
  spelling->MEMBER = (VALUE);						\
  spelling++;								\
}

/* Push STRING on the stack.  Printed literally.  */

ساكن فراغ
push_string (ثابت حرف *string)
{
  PUSH_SPELLING (SPELLING_STRING, string, u.s);
}

/* Push a member name on the stack.  Printed as '.' STRING.  */

ساكن فراغ
push_member_name (tree decl)
{
  ثابت حرف *ثابت string
    = (DECL_NAME (decl)
       ? identifier_to_locale (IDENTIFIER_POINTER (DECL_NAME (decl)))
       : _("<anonymous>"));
  PUSH_SPELLING (SPELLING_MEMBER, string, u.s);
}

/* Push an array bounds on the stack.  Printed as [BOUNDS].  */

ساكن فراغ
push_array_bounds (unsigned HOST_WIDE_INT bounds)
{
  PUSH_SPELLING (SPELLING_BOUNDS, bounds, u.i);
}

/* Compute the maximum size in bytes of the printed spelling.  */

ساكن صحيح
spelling_length (فراغ)
{
  صحيح size = 0;
  بنية spelling *p;

  لكل (p = spelling_base; p < spelling; p++)
    {
      𐤀𐤌 (p->kind == SPELLING_BOUNDS)
	size += 25;
      وإلا
	size += strlen (p->u.s) + 1;
    }

  أرجع size;
}

/* Print the spelling to BUFFER and return it.  */

ساكن حرف *
print_spelling (حرف *buffer)
{
  حرف *d = buffer;
  بنية spelling *p;

  لكل (p = spelling_base; p < spelling; p++)
    𐤀𐤌 (p->kind == SPELLING_BOUNDS)
      {
	sprintf (d, "[" HOST_WIDE_INT_PRINT_UNSIGNED "]", p->u.i);
	d += strlen (d);
      }
    وإلا
      {
	ثابت حرف *s;
	𐤀𐤌 (p->kind == SPELLING_MEMBER)
	  *d++ = '.';
	لكل (s = p->u.s; (*d = *s++); d++)
	  ;
      }
  *d++ = '\0';
  أرجع buffer;
}

/* Check whether INIT, a floating or integer constant, is
   representable in TYPE, a real floating type with the same radix or
   a decimal floating type initialized with a binary floating
   constant.  Return true if OK, false if not.  */
ساكن منطقي
constexpr_init_fits_real_type (tree type, tree init)
{
  gcc_assert (SCALAR_FLOAT_TYPE_P (type));
  gcc_assert (TREE_CODE (init) == INTEGER_CST || TREE_CODE (init) == REAL_CST);
  𐤀𐤌 (TREE_CODE (init) == REAL_CST
      && TYPE_MODE (TREE_TYPE (init)) == TYPE_MODE (type))
    {
      /* Same mode, no conversion required except for the case of
	 signaling NaNs if the types are incompatible (e.g. double and
	 long double with the same mode).  */
      𐤀𐤌 (REAL_VALUE_ISSIGNALING_NAN (TREE_REAL_CST (init))
	  && !comptypes (TYPE_MAIN_VARIANT (type),
			 TYPE_MAIN_VARIANT (TREE_TYPE (init))))
	أرجع خطأ;
      أرجع true;
    }
  𐤀𐤌 (TREE_CODE (init) == INTEGER_CST)
    {
      tree converted = build_real_from_int_cst (type, init);
      منطقي fail = خطأ;
      wide_int w = real_to_integer (&TREE_REAL_CST (converted), &fail,
				    TYPE_PRECISION (TREE_TYPE (init)));
      أرجع !fail && wi::eq_p (w, wi::to_wide (init));
    }
  𐤀𐤌 (REAL_VALUE_ISSIGNALING_NAN (TREE_REAL_CST (init)))
    أرجع خطأ;
  𐤀𐤌 ((REAL_VALUE_ISINF (TREE_REAL_CST (init))
       && MODE_HAS_INFINITIES (TYPE_MODE (type)))
      || (REAL_VALUE_ISNAN (TREE_REAL_CST (init))
	  && MODE_HAS_NANS (TYPE_MODE (type))))
    أرجع true;
  𐤀𐤌 (DECIMAL_FLOAT_TYPE_P (type)
      && !DECIMAL_FLOAT_TYPE_P (TREE_TYPE (init)))
    {
      /* This is valid if the real number represented by the
	 initializer can be exactly represented in the decimal
	 type.  Compare the values using MPFR.  */
      REAL_VALUE_TYPE t;
      real_convert (&t, TYPE_MODE (type), &TREE_REAL_CST (init));
      mpfr_t bin_val, dec_val;
      mpfr_init2 (bin_val, REAL_MODE_FORMAT (TYPE_MODE (TREE_TYPE (init)))->p);
      mpfr_init2 (dec_val, REAL_MODE_FORMAT (TYPE_MODE (TREE_TYPE (init)))->p);
      mpfr_from_real (bin_val, &TREE_REAL_CST (init), MPFR_RNDN);
      حرف string[256];
      real_to_decimal (string, &t, حجم string, 0, 1);
      منطقي res = (mpfr_strtofr (dec_val, string, عدم, 10, MPFR_RNDN) == 0
		  && mpfr_equal_p (bin_val, dec_val));
      mpfr_clear (bin_val);
      mpfr_clear (dec_val);
      أرجع res;
    }
  /* exact_real_truncate is not quite right here, since it doesn't
     allow even an exact conversion to subnormal values.  */
  REAL_VALUE_TYPE t;
  real_convert (&t, TYPE_MODE (type), &TREE_REAL_CST (init));
  أرجع real_identical (&t, &TREE_REAL_CST (init));
}

/* Check whether INIT (location LOC) is valid as a 'constexpr'
   initializer for type TYPE, and give an error if not.  INIT has
   already been folded and verified to be constant.  INT_CONST_EXPR
   and ARITH_CONST_EXPR say whether it is an integer constant
   expression or arithmetic constant expression, respectively.  If
   TYPE is not a scalar type, this function does nothing.  */

ساكن فراغ
check_constexpr_init (location_t loc, tree type, tree init,
		      منطقي int_const_expr, منطقي arith_const_expr)
{
  𐤀𐤌 (POINTER_TYPE_P (type))
    {
      /* The initializer must be null.  */
      𐤀𐤌 (TREE_CODE (init) != INTEGER_CST || !integer_zerop (init))
	error_at (loc, "%<constexpr%> pointer initializer is not null");
      أرجع;
    }
  𐤀𐤌 (INTEGRAL_TYPE_P (type))
    {
      /* The initializer must be an integer constant expression,
	 representable in the target type.  */
      𐤀𐤌 (!int_const_expr)
	{
	  𐤀𐤌 (TREE_CODE (init) == RAW_DATA_CST
	      && TYPE_PRECISION (type) == CHAR_BIT)
	    {
	      𐤀𐤌 (!TYPE_UNSIGNED (type))
		لكل (unsigned صحيح i = 0;
		     i < (unsigned) RAW_DATA_LENGTH (init); ++i)
		  𐤀𐤌 (RAW_DATA_SCHAR_ELT (init, i) < 0)
		    {
		      error_at (loc, "%<constexpr%> initializer not "
				"representable in type of object");
		      اكسر;
		    }
	    }
	  وإلا
	    error_at (loc, "%<constexpr%> integer initializer is not an "
		      "integer constant expression");
	}
      وإلا 𐤀𐤌 (!int_fits_type_p (init, type))
	error_at (loc, "%<constexpr%> initializer not representable in "
		  "type of object");
      أرجع;
    }
  /* We don't apply any extra checks to extension types such as vector
     or fixed-point types.  */
  𐤀𐤌 (TREE_CODE (type) != REAL_TYPE && TREE_CODE (type) != COMPLEX_TYPE)
    أرجع;
  𐤀𐤌 (!arith_const_expr)
    {
      error_at (loc, "%<constexpr%> initializer is not an arithmetic "
		"constant expression");
      أرجع;
    }
  /* We don't apply any extra checks to complex integers.  */
  𐤀𐤌 (TREE_CODE (type) == COMPLEX_TYPE
      && TREE_CODE (TREE_TYPE (type)) != REAL_TYPE)
    أرجع;
  /* Following N3082, a real type cannot be initialized from a complex
     type and a binary type cannot be initialized from a decimal type
     (but initializing a decimal type from a binary type is OK).
     Signaling NaN initializers are OK only if the types are
     compatible (not just the same mode); all quiet NaN and infinity
     initializations are considered to preserve the value.  */
  𐤀𐤌 (TREE_CODE (TREE_TYPE (init)) == COMPLEX_TYPE
      && SCALAR_FLOAT_TYPE_P (type))
    {
      error_at (loc, "%<constexpr%> initializer for a real type is of "
		"complex type");
      أرجع;
    }
  𐤀𐤌 (SCALAR_FLOAT_TYPE_P (type)
      && SCALAR_FLOAT_TYPE_P (TREE_TYPE (init))
      && DECIMAL_FLOAT_TYPE_P (TREE_TYPE (init))
      && !DECIMAL_FLOAT_TYPE_P (type))
    {
      error_at (loc, "%<constexpr%> initializer for a binary "
		"floating-point type is of decimal type");
      أرجع;
    }
  منطقي fits;
  𐤀𐤌 (TREE_CODE (type) == COMPLEX_TYPE)
    {
      بدل (TREE_CODE (init))
	{
	حالة INTEGER_CST:
	حالة REAL_CST:
	  fits = constexpr_init_fits_real_type (TREE_TYPE (type), init);
	  اكسر;
	حالة COMPLEX_CST:
	  fits = (constexpr_init_fits_real_type (TREE_TYPE (type),
						 TREE_REALPART (init))
		  && constexpr_init_fits_real_type (TREE_TYPE (type),
						    TREE_IMAGPART (init)));
	  اكسر;
	افتراضي:
	  gcc_unreachable ();
	}
    }
  وإلا
    fits = constexpr_init_fits_real_type (type, init);
  𐤀𐤌 (!fits)
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

ساكن tree
digest_init (location_t init_loc, tree decl, tree type, tree init,
	     tree origtype, منطقي null_pointer_constant, منطقي int_const_expr,
	     منطقي arith_const_expr, منطقي strict_string,
	     منطقي require_constant, منطقي require_constexpr)
{
  تعداد tree_code code = TREE_CODE (type);
  tree inside_init = init;
  tree semantic_type = NULL_TREE;
  منطقي maybe_const = true;

  𐤀𐤌 (type == error_mark_node
      || !init
      || error_operand_p (init))
    أرجع error_mark_node;

  STRIP_TYPE_NOPS (inside_init);

  /* If require_constant is TRUE,  when the initializer is a call to
     .ACCESS_WITH_SIZE, use the first argument as the initializer.
     For example:
     y = (char *) .ACCESS_WITH_SIZE ((char *) &static_annotated.c,...)
     will be converted to
     y = &static_annotated.c.  */

  𐤀𐤌 (require_constant
      && TREE_CODE (inside_init) == NOP_EXPR
      && TREE_CODE (TREE_OPERAND (inside_init, 0)) == CALL_EXPR
      && is_access_with_size_p (TREE_OPERAND (inside_init, 0)))
    inside_init
      = get_ref_from_access_with_size (TREE_OPERAND (inside_init, 0));

  𐤀𐤌 (!c_in_omp_for)
    {
      𐤀𐤌 (TREE_CODE (inside_init) == EXCESS_PRECISION_EXPR)
	{
	  semantic_type = TREE_TYPE (inside_init);
	  inside_init = TREE_OPERAND (inside_init, 0);
	}
      inside_init = c_fully_fold (inside_init, require_constant, &maybe_const);
    }
  /* TODO: this may not detect all cases of expressions folding to
     constants that are not arithmetic constant expressions.  */
  𐤀𐤌 (!maybe_const)
    arith_const_expr = خطأ;
  وإلا 𐤀𐤌 (!INTEGRAL_TYPE_P (TREE_TYPE (inside_init))
	   && TREE_CODE (TREE_TYPE (inside_init)) != REAL_TYPE
	   && TREE_CODE (TREE_TYPE (inside_init)) != COMPLEX_TYPE)
    arith_const_expr = خطأ;
  وإلا 𐤀𐤌 (TREE_CODE (inside_init) != INTEGER_CST
	   && TREE_CODE (inside_init) != REAL_CST
	   && TREE_CODE (inside_init) != COMPLEX_CST
	   && TREE_CODE (inside_init) != RAW_DATA_CST)
    arith_const_expr = خطأ;
  وإلا 𐤀𐤌 (TREE_OVERFLOW (inside_init))
    arith_const_expr = خطأ;

  /* Initialization of an array of chars from a string constant
     optionally enclosed in braces.  */

  𐤀𐤌 (code == ARRAY_TYPE && inside_init
      && TREE_CODE (inside_init) == STRING_CST)
    {
      tree typ1
	= (TYPE_ATOMIC (TREE_TYPE (type))
	   ? c_build_qualified_type (TYPE_MAIN_VARIANT (TREE_TYPE (type)),
				     TYPE_QUAL_ATOMIC)
	   : TYPE_MAIN_VARIANT (TREE_TYPE (type)));
      /* Note that an array could be both an array of character type
	 and an array of wchar_t if wchar_t is signed char or unsigned
	 char.  */
      منطقي char_array = (typ1 == char_type_node
			 || typ1 == signed_char_type_node
			 || typ1 == unsigned_char_type_node);
      منطقي wchar_array = comptypes (typ1, wchar_type_node);
      منطقي char16_array = comptypes (typ1, char16_type_node);
      منطقي char32_array = comptypes (typ1, char32_type_node);

      𐤀𐤌 (char_array || wchar_array || char16_array || char32_array)
	{
	  بنية c_expr expr;
	  tree typ2 = TYPE_MAIN_VARIANT (TREE_TYPE (TREE_TYPE (inside_init)));
	  منطقي incompat_string_cst = خطأ;
	  expr.value = inside_init;
	  expr.original_code = (strict_string ? STRING_CST : ERROR_MARK);
	  expr.original_type = عدم;
	  expr.m_decimal = 0;
	  maybe_warn_string_init (init_loc, type, expr);

	  𐤀𐤌 (flexible_array_member_type_p (type))
	    pedwarn_init (init_loc, OPT_Wpedantic,
			  "initialization of a flexible array member");

	  𐤀𐤌 (comptypes (TYPE_MAIN_VARIANT (TREE_TYPE (inside_init)),
			 TYPE_MAIN_VARIANT (type)))
	    أرجع inside_init;

	  𐤀𐤌 (char_array)
	    {
	      𐤀𐤌 (typ2 != char_type_node && typ2 != char8_type_node)
		incompat_string_cst = true;
	    }
	  وإلا 𐤀𐤌 (!comptypes (typ1, typ2))
	    incompat_string_cst = true;

          𐤀𐤌 (incompat_string_cst)
            {
	      error_init (init_loc, "cannot initialize array of %qT from "
			  "a string literal with type array of %qT",
			  typ1, typ2);
	      أرجع error_mark_node;
            }

	  𐤀𐤌 (require_constexpr
	      && TYPE_UNSIGNED (typ1) != TYPE_UNSIGNED (typ2))
	    {
	      /* Check if all characters of the string can be
		 represented in the type of the constexpr object being
		 initialized.  */
	      unsigned HOST_WIDE_INT len = TREE_STRING_LENGTH (inside_init);
	      ثابت unsigned حرف *p =
		(ثابت unsigned حرف *) TREE_STRING_POINTER (inside_init);
	      gcc_assert (CHAR_TYPE_SIZE == 8 && CHAR_BIT == 8);
	      لكل (unsigned i = 0; i < len; i++)
		𐤀𐤌 (p[i] > 127)
		  {
		    error_init (init_loc, "%<constexpr%> initializer not "
				"representable in type of object");
		    اكسر;
		  }
	    }

	  𐤀𐤌 (TYPE_DOMAIN (type) != NULL_TREE
	      && TYPE_SIZE (type) != NULL_TREE
	      && TREE_CODE (TYPE_SIZE (type)) == INTEGER_CST)
	    {
	      unsigned HOST_WIDE_INT len = TREE_STRING_LENGTH (inside_init);

	      𐤀𐤌 (compare_tree_int (TYPE_SIZE_UNIT (type), len) < 0)
		{
		  unsigned HOST_WIDE_INT avail
		    = tree_to_uhwi (TYPE_SIZE_UNIT (type));
		  unsigned unit = TYPE_PRECISION (typ1) / BITS_PER_UNIT;
		  ثابت حرف *p = TREE_STRING_POINTER (inside_init);

		  /* Construct truncated string.  */
		  inside_init = build_string (avail, p);

		  /* Subtract the size of a single (possibly wide) character
		     because it may be ok to ignore the terminating NUL char
		     that is counted in the length of the constant.  */
		  𐤀𐤌 (len - unit > avail)
		    pedwarn_init (init_loc, 0,
				  "initializer-string for array of %qT "
				  "is too long (%wu chars into %wu "
				  "available)", typ1, len, avail);
		  وإلا 𐤀𐤌 (warn_cxx_compat)
		    warning_at (init_loc, OPT_Wc___compat,
				"initializer-string for array of %qT "
				"is too long for C++ (%wu chars into %wu "
				"available)", typ1, len, avail);
		  وإلا 𐤀𐤌 (warn_unterminated_string_initialization
			   && get_attr_nonstring_decl (decl) == NULL_TREE)
		    warning_at (init_loc,
				OPT_Wunterminated_string_initialization,
				"initializer-string for array of %qT "
				"truncates NUL terminator but destination "
				"lacks %qs attribute (%wu chars into %wu "
				"available)", typ1, "nonstring", len, avail);
		}
	    }

	  TREE_TYPE (inside_init) = type;
	  أرجع inside_init;
	}
      وإلا 𐤀𐤌 (INTEGRAL_TYPE_P (typ1))
	{
	  error_init (init_loc, "array of inappropriate type initialized "
		      "from string constant");
	  أرجع error_mark_node;
	}
    }

  /* Build a VECTOR_CST from a *constant* vector constructor.  If the
     vector constructor is not constant (e.g. {1,2,3,foo()}) then punt
     below and handle as a constructor.  */
  𐤀𐤌 (code == VECTOR_TYPE
      && VECTOR_TYPE_P (TREE_TYPE (inside_init))
      && vector_types_convertible_p (TREE_TYPE (inside_init), type, true)
      && TREE_CONSTANT (inside_init))
    {
      𐤀𐤌 (TREE_CODE (inside_init) == VECTOR_CST
	  && comptypes (TYPE_MAIN_VARIANT (TREE_TYPE (inside_init)),
			TYPE_MAIN_VARIANT (type)))
	أرجع inside_init;

      𐤀𐤌 (TREE_CODE (inside_init) == CONSTRUCTOR)
	{
	  unsigned HOST_WIDE_INT ix;
	  tree value;
	  منطقي constant_p = true;

	  /* Iterate through elements and check if all constructor
	     elements are *_CSTs.  */
	  FOR_EACH_CONSTRUCTOR_VALUE (CONSTRUCTOR_ELTS (inside_init), ix, value)
	    𐤀𐤌 (!CONSTANT_CLASS_P (value))
	      {
		constant_p = خطأ;
		اكسر;
	      }

	  𐤀𐤌 (constant_p)
	    أرجع build_vector_from_ctor (type,
					   CONSTRUCTOR_ELTS (inside_init));
	}
    }

  𐤀𐤌 (warn_sequence_point)
    verify_sequence_points (inside_init);

  /* Any type can be initialized
     from an expression of the same type, optionally with braces.  */

  𐤀𐤌 (inside_init && TREE_TYPE (inside_init) != NULL_TREE
      && (comptypes (TYPE_MAIN_VARIANT (TREE_TYPE (inside_init)),
		     TYPE_MAIN_VARIANT (type))
	  || (code == ARRAY_TYPE
	      && comptypes (TREE_TYPE (inside_init), type))
	  || (gnu_vector_type_p (type)
	      && comptypes (TREE_TYPE (inside_init), type))
	  || (code == POINTER_TYPE
	      && TREE_CODE (TREE_TYPE (inside_init)) == ARRAY_TYPE
	      && comptypes (TREE_TYPE (TREE_TYPE (inside_init)),
			    TREE_TYPE (type)))))
    {
      𐤀𐤌 (code == POINTER_TYPE)
	{
	  𐤀𐤌 (TREE_CODE (TREE_TYPE (inside_init)) == ARRAY_TYPE)
	    {
	      𐤀𐤌 (TREE_CODE (inside_init) == STRING_CST
		  || TREE_CODE (inside_init) == COMPOUND_LITERAL_EXPR)
		inside_init = array_to_pointer_conversion
		  (init_loc, inside_init);
	      وإلا
		{
		  error_init (init_loc, "invalid use of non-lvalue array");
		  أرجع error_mark_node;
		}
	    }
	}

      𐤀𐤌 (code == VECTOR_TYPE || c_hardbool_type_attr (type))
	/* Although the types are compatible, we may require a
	   conversion.  */
	inside_init = convert (type, inside_init);

      𐤀𐤌 ((code == RECORD_TYPE || code == UNION_TYPE)
	  && !comptypes (TYPE_MAIN_VARIANT (type), TYPE_MAIN_VARIANT (TREE_TYPE (inside_init))))
	{
	  error_init (init_loc, "invalid initializer");
	  أرجع error_mark_node;
	}

      𐤀𐤌 (require_constant
	  && TREE_CODE (inside_init) == COMPOUND_LITERAL_EXPR)
	{
	  /* As an extension, allow initializing objects with static storage
	     duration with compound literals (which are then treated just as
	     the brace enclosed list they contain).  Also allow this for
	     vectors, as we can only assign them with compound literals.  */
	  𐤀𐤌 (flag_isoc99 && code != VECTOR_TYPE)
	    pedwarn_init (init_loc, OPT_Wpedantic, "initializer element "
			  "is not constant");
	  tree decl = COMPOUND_LITERAL_EXPR_DECL (inside_init);
	  inside_init = DECL_INITIAL (decl);
	}

      𐤀𐤌 (code == ARRAY_TYPE && TREE_CODE (inside_init) != STRING_CST
	  && TREE_CODE (inside_init) != CONSTRUCTOR)
	{
	  error_init (init_loc, "array initialized from non-constant array "
		      "expression");
	  أرجع error_mark_node;
	}

      /* Compound expressions can only occur here if -Wpedantic or
	 -pedantic-errors is specified.  In the later case, we always want
	 an error.  In the former case, we simply want a warning.  */
      𐤀𐤌 (require_constant && pedantic
	  && TREE_CODE (inside_init) == COMPOUND_EXPR)
	{
	  inside_init
	    = valid_compound_expr_initializer (inside_init,
					       TREE_TYPE (inside_init));
	  𐤀𐤌 (inside_init == error_mark_node)
	    error_init (init_loc, "initializer element is not constant");
	  وإلا
	    pedwarn_init (init_loc, OPT_Wpedantic,
			  "initializer element is not constant");
	  𐤀𐤌 (flag_pedantic_errors)
	    inside_init = error_mark_node;
	}
      وإلا 𐤀𐤌 (require_constant
	       && !initializer_constant_valid_p (inside_init,
						 TREE_TYPE (inside_init)))
	{
	  error_init (init_loc, "initializer element is not constant");
	  inside_init = error_mark_node;
	}
      وإلا 𐤀𐤌 (require_constant && !maybe_const)
	pedwarn_init (init_loc, OPT_Wpedantic,
		      "initializer element is not a constant expression");
      وإلا 𐤀𐤌 (require_constexpr)
	check_constexpr_init (init_loc, type, inside_init,
			      int_const_expr, arith_const_expr);

      /* Added to enable additional -Wsuggest-attribute=format warnings.  */
      𐤀𐤌 (TREE_CODE (TREE_TYPE (inside_init)) == POINTER_TYPE)
	inside_init = convert_for_assignment (init_loc, UNKNOWN_LOCATION,
					      type, inside_init, origtype,
					      (require_constant
					       ? ic_init_const
					       : ic_init), null_pointer_constant,
					      NULL_TREE, NULL_TREE, 0);
      𐤀𐤌 (TREE_CODE (inside_init) == RAW_DATA_CST
	  && c_inhibit_evaluation_warnings == 0
	  && warn_conversion
	  && !TYPE_UNSIGNED (type)
	  && TYPE_PRECISION (type) == CHAR_BIT)
	لكل (unsigned صحيح i = 0;
	     i < (unsigned) RAW_DATA_LENGTH (inside_init); ++i)
	  𐤀𐤌 (RAW_DATA_SCHAR_ELT (inside_init, i) < 0)
	    warning_at (init_loc, OPT_Wconversion,
			"conversion from %qT to %qT changes value from "
			"%qd to %qd",
			integer_type_node, type,
			RAW_DATA_UCHAR_ELT (inside_init, i),
			RAW_DATA_SCHAR_ELT (inside_init, i));
      أرجع inside_init;
    }

  /* Handle scalar types, including conversions.  */

  𐤀𐤌 (code == INTEGER_TYPE || code == REAL_TYPE || code == FIXED_POINT_TYPE
      || code == POINTER_TYPE || code == ENUMERAL_TYPE || code == BOOLEAN_TYPE
      || code == COMPLEX_TYPE || code == VECTOR_TYPE || code == NULLPTR_TYPE
      || code == BITINT_TYPE)
    {
      tree unconverted_init = inside_init;
      𐤀𐤌 (TREE_CODE (TREE_TYPE (init)) == ARRAY_TYPE
	  && (TREE_CODE (init) == STRING_CST
	      || TREE_CODE (init) == COMPOUND_LITERAL_EXPR))
	inside_init = init = array_to_pointer_conversion (init_loc, init);
      𐤀𐤌 (semantic_type)
	inside_init = build1 (EXCESS_PRECISION_EXPR, semantic_type,
			      inside_init);
      inside_init
	= convert_for_assignment (init_loc, UNKNOWN_LOCATION, type,
				  inside_init, origtype,
				  require_constant ? ic_init_const : ic_init,
				  null_pointer_constant, NULL_TREE, NULL_TREE,
				  0);

      /* Check to see if we have already given an error message.  */
      𐤀𐤌 (inside_init == error_mark_node)
	;
      وإلا 𐤀𐤌 (require_constant && !TREE_CONSTANT (inside_init))
	{
	  error_init (init_loc, "initializer element is not constant");
	  inside_init = error_mark_node;
	}
      وإلا 𐤀𐤌 (require_constant
	       && !initializer_constant_valid_p (inside_init,
						 TREE_TYPE (inside_init)))
	{
	  error_init (init_loc, "initializer element is not computable at "
		      "load time");
	  inside_init = error_mark_node;
	}
      وإلا 𐤀𐤌 (require_constant && !maybe_const)
	pedwarn_init (init_loc, OPT_Wpedantic,
		      "initializer element is not a constant expression");
      وإلا 𐤀𐤌 (require_constexpr)
	check_constexpr_init (init_loc, type, unconverted_init,
			      int_const_expr, arith_const_expr);

      أرجع inside_init;
    }

  /* Come here only for records and arrays.  */

  𐤀𐤌 (COMPLETE_TYPE_P (type) && TREE_CODE (TYPE_SIZE (type)) != INTEGER_CST)
    {
      error_init (init_loc,
		  "variable-sized object may not be initialized except "
		  "with an empty initializer");
      أرجع error_mark_node;
    }

  error_init (init_loc, "invalid initializer");
  أرجع error_mark_node;
}

/* Handle initializers that use braces.  */

/* Type of object we are accumulating a constructor for.
   This type is always a RECORD_TYPE, UNION_TYPE or ARRAY_TYPE.  */
ساكن tree constructor_type;

/* For a RECORD_TYPE or UNION_TYPE, this is the chain of fields
   left to fill.  */
ساكن tree constructor_fields;

/* For an ARRAY_TYPE, this is the specified index
   at which to store the next element we get.  */
ساكن tree constructor_index;

/* For an ARRAY_TYPE, this is the maximum index.  */
ساكن tree constructor_max_index;

/* For a RECORD_TYPE, this is the first field not yet written out.  */
ساكن tree constructor_unfilled_fields;

/* For an ARRAY_TYPE, this is the index of the first element
   not yet written out.  */
ساكن tree constructor_unfilled_index;

/* In a RECORD_TYPE, the byte index of the next consecutive field.
   This is so we can generate gaps between fields, when appropriate.  */
ساكن tree constructor_bit_index;

/* If we are saving up the elements rather than allocating them,
   this is the list of elements so far (in reverse order,
   most recent first).  */
ساكن vec<constructor_elt, va_gc> *constructor_elements;

/* 1 if constructor should be incrementally stored into a constructor chain,
   0 if all the elements should be kept in AVL tree.  */
ساكن صحيح constructor_incremental;

/* 1 if so far this constructor's elements are all compile-time constants.  */
ساكن صحيح constructor_constant;

/* 1 if so far this constructor's elements are all valid address constants.  */
ساكن صحيح constructor_simple;

/* 1 if this constructor has an element that cannot be part of a
   constant expression.  */
ساكن صحيح constructor_nonconst;

/* 1 if this constructor is erroneous so far.  */
ساكن صحيح constructor_erroneous;

/* 1 if this constructor is the universal zero initializer { 0 }.  */
ساكن صحيح constructor_zeroinit;

/* 1 if this constructor should have padding bits zeroed (C23 {}.  */
ساكن منطقي constructor_zero_padding_bits;

/* 1 if this constructor is a braced scalar initializer (further nested levels
   of braces are an error).  */
ساكن منطقي constructor_braced_scalar;

/* Structure for managing pending initializer elements, organized as an
   AVL tree.  */

بنية init_node
{
  بنية init_node *left, *right;
  بنية init_node *parent;
  صحيح balance;
  tree purpose;
  tree value;
  tree origtype;
};

/* Tree of pending elements at this constructor level.
   These are elements encountered out of order
   which belong at places we haven't reached yet in actually
   writing the output.
   Will never hold tree nodes across GC runs.  */
ساكن بنية init_node *constructor_pending_elts;

/* The SPELLING_DEPTH of this constructor.  */
ساكن صحيح constructor_depth;

/* DECL node for which an initializer is being read.
   0 means we are reading a constructor expression
   such as (struct foo) {...}.  */
ساكن tree constructor_decl;

/* Nonzero if there were any member designators in this initializer.  */
ساكن صحيح constructor_designated;

/* Nesting depth of designator list.  */
ساكن صحيح designator_depth;

/* Nonzero if there were diagnosed errors in this designator list.  */
ساكن صحيح designator_erroneous;


/* This stack has a level for each implicit or explicit level of
   structuring in the initializer, including the outermost one.  It
   saves the values of most of the variables above.  */

بنية constructor_range_stack;

بنية constructor_stack
{
  بنية constructor_stack *next;
  tree type;
  tree fields;
  tree index;
  tree max_index;
  tree unfilled_index;
  tree unfilled_fields;
  tree bit_index;
  vec<constructor_elt, va_gc> *elements;
  بنية init_node *pending_elts;
  صحيح offset;
  صحيح depth;
  /* If value nonzero, this value should replace the entire
     constructor at this level.  */
  بنية c_expr replacement_value;
  بنية constructor_range_stack *range_stack;
  حرف constant;
  حرف simple;
  حرف nonconst;
  حرف implicit;
  حرف erroneous;
  حرف outer;
  حرف incremental;
  حرف designated;
  منطقي zero_padding_bits;
  منطقي braced_scalar;
  صحيح designator_depth;
};

ساكن بنية constructor_stack *constructor_stack;

/* This stack represents designators from some range designator up to
   the last designator in the list.  */

بنية constructor_range_stack
{
  بنية constructor_range_stack *next, *prev;
  بنية constructor_stack *stack;
  tree range_start;
  tree index;
  tree range_end;
  tree fields;
};

ساكن بنية constructor_range_stack *constructor_range_stack;

/* This stack records separate initializers that are nested.
   Nested initializers can't happen in ANSI C, but GNU C allows them
   in cases like { ... (struct foo) { ... } ... }.  */

بنية initializer_stack
{
  بنية initializer_stack *next;
  tree decl;
  بنية constructor_stack *constructor_stack;
  بنية constructor_range_stack *constructor_range_stack;
  vec<constructor_elt, va_gc> *elements;
  بنية spelling *spelling;
  بنية spelling *spelling_base;
  صحيح spelling_size;
  حرف require_constant_value;
  حرف require_constant_elements;
  حرف require_constexpr_value;
  حرف designated;
  rich_location *missing_brace_richloc;
};

ساكن بنية initializer_stack *initializer_stack;

/* Prepare to parse and output the initializer for variable DECL.  */

فراغ
start_init (tree decl, tree asmspec_tree ATTRIBUTE_UNUSED,
	    منطقي init_require_constant, منطقي init_require_constexpr,
	    rich_location *richloc)
{
  ثابت حرف *locus;
  بنية initializer_stack *p = XNEW (بنية initializer_stack);

  p->decl = constructor_decl;
  p->require_constant_value = require_constant_value;
  p->require_constant_elements = require_constant_elements;
  p->require_constexpr_value = require_constexpr_value;
  p->constructor_stack = constructor_stack;
  p->constructor_range_stack = constructor_range_stack;
  p->elements = constructor_elements;
  p->spelling = spelling;
  p->spelling_base = spelling_base;
  p->spelling_size = spelling_size;
  p->next = initializer_stack;
  p->missing_brace_richloc = richloc;
  p->designated = constructor_designated;
  initializer_stack = p;

  constructor_decl = decl;
  constructor_designated = 0;

  require_constant_value = init_require_constant;
  require_constexpr_value = init_require_constexpr;
  𐤀𐤌 (decl != NULL_TREE && decl != error_mark_node)
    {
      require_constant_elements
	= ((init_require_constant || (pedantic && !flag_isoc99))
	   /* For a scalar, you can always use any value to initialize,
	      even within braces.  */
	   && AGGREGATE_TYPE_P (TREE_TYPE (decl)));
      locus = identifier_to_locale (IDENTIFIER_POINTER (DECL_NAME (decl)));
    }
  وإلا
    {
      require_constant_elements = خطأ;
      locus = _("(anonymous)");
    }

  constructor_stack = 0;
  constructor_range_stack = 0;

  found_missing_braces = 0;

  spelling_base = 0;
  spelling_size = 0;
  RESTORE_SPELLING_DEPTH (0);

  𐤀𐤌 (locus)
    push_string (locus);
}

فراغ
finish_init (فراغ)
{
  بنية initializer_stack *p = initializer_stack;

  /* Free the whole constructor stack of this initializer.  */
  طالما (constructor_stack)
    {
      بنية constructor_stack *q = constructor_stack;
      constructor_stack = q->next;
      XDELETE (q);
    }

  gcc_assert (!constructor_range_stack);

  /* Pop back to the data of the outer initializer (if any).  */
  XDELETE (spelling_base);

  constructor_decl = p->decl;
  require_constant_value = p->require_constant_value;
  require_constant_elements = p->require_constant_elements;
  require_constexpr_value = p->require_constexpr_value;
  constructor_stack = p->constructor_stack;
  constructor_designated = p->designated;
  constructor_range_stack = p->constructor_range_stack;
  constructor_elements = p->elements;
  spelling = p->spelling;
  spelling_base = p->spelling_base;
  spelling_size = p->spelling_size;
  initializer_stack = p->next;
  XDELETE (p);
}

/* Call here when we see the initializer is surrounded by braces.
   This is instead of a call to push_init_level;
   it is matched by a call to pop_init_level.

   TYPE is the type to initialize, for a constructor expression.
   For an initializer for a decl, TYPE is zero.  */

فراغ
really_start_incremental_init (tree type)
{
  بنية constructor_stack *p = XNEW (بنية constructor_stack);

  𐤀𐤌 (type == NULL_TREE)
    type = TREE_TYPE (constructor_decl);

  𐤀𐤌 (VECTOR_TYPE_P (type)
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
  p->replacement_value.value = 0;
  p->replacement_value.original_code = ERROR_MARK;
  p->replacement_value.original_type = عدم;
  p->implicit = 0;
  p->range_stack = 0;
  p->outer = 0;
  p->incremental = constructor_incremental;
  p->designated = constructor_designated;
  p->zero_padding_bits = constructor_zero_padding_bits;
  p->braced_scalar = constructor_braced_scalar;
  p->designator_depth = designator_depth;
  p->next = 0;
  constructor_stack = p;

  constructor_constant = 1;
  constructor_simple = 1;
  constructor_nonconst = 0;
  constructor_depth = SPELLING_DEPTH ();
  constructor_elements = عدم;
  constructor_pending_elts = 0;
  constructor_type = type;
  constructor_incremental = 1;
  constructor_designated = 0;
  constructor_zero_padding_bits = خطأ;
  constructor_zeroinit = 1;
  constructor_braced_scalar = خطأ;
  designator_depth = 0;
  designator_erroneous = 0;

  𐤀𐤌 (RECORD_OR_UNION_TYPE_P (constructor_type))
    {
      constructor_fields = TYPE_FIELDS (constructor_type);
      /* Skip any nameless bit fields at the beginning.  */
      طالما (constructor_fields != NULL_TREE
	     && DECL_UNNAMED_BIT_FIELD (constructor_fields))
	constructor_fields = DECL_CHAIN (constructor_fields);

      constructor_unfilled_fields = constructor_fields;
      constructor_bit_index = bitsize_zero_node;
    }
  وإلا 𐤀𐤌 (TREE_CODE (constructor_type) == ARRAY_TYPE)
    {
      𐤀𐤌 (TYPE_DOMAIN (constructor_type))
	{
	  constructor_max_index
	    = TYPE_MAX_VALUE (TYPE_DOMAIN (constructor_type));

	  /* Detect non-empty initializations of zero-length arrays.  */
	  𐤀𐤌 (constructor_max_index == NULL_TREE
	      && TYPE_SIZE (constructor_type))
	    constructor_max_index = integer_minus_one_node;

	  /* constructor_max_index needs to be an INTEGER_CST.  Attempts
	     to initialize VLAs with a nonempty initializer will cause a
	     proper error; avoid tree checking errors as well by setting a
	     safe value.  */
	  𐤀𐤌 (constructor_max_index
	      && TREE_CODE (constructor_max_index) != INTEGER_CST)
	    constructor_max_index = integer_minus_one_node;

	  constructor_index
	    = convert (bitsizetype,
		       TYPE_MIN_VALUE (TYPE_DOMAIN (constructor_type)));
	}
      وإلا
	{
	  constructor_index = bitsize_zero_node;
	  constructor_max_index = NULL_TREE;
	}

      constructor_unfilled_index = constructor_index;
    }
  وإلا 𐤀𐤌 (gnu_vector_type_p (constructor_type))
    {
      /* Vectors are like simple fixed-size arrays.  */
      constructor_max_index =
	bitsize_int (TYPE_VECTOR_SUBPARTS (constructor_type) - 1);
      constructor_index = bitsize_zero_node;
      constructor_unfilled_index = constructor_index;
    }
  وإلا
    {
      /* Handle the case of int x = {5}; */
      constructor_fields = constructor_type;
      constructor_unfilled_fields = constructor_type;
      constructor_braced_scalar = true;
    }
}

خارجي location_t last_init_list_comma;

/* Called when we see an open brace for a nested initializer.  Finish
   off any pending levels with implicit braces.  */
فراغ
finish_implicit_inits (location_t loc, بنية obstack *braced_init_obstack)
{
  طالما (constructor_stack->implicit)
    {
      𐤀𐤌 (RECORD_OR_UNION_TYPE_P (constructor_type)
	  && constructor_fields == NULL_TREE)
	process_init_element (input_location,
			      pop_init_level (loc, 1, braced_init_obstack,
					      last_init_list_comma),
			      true, braced_init_obstack);
      وإلا 𐤀𐤌 (TREE_CODE (constructor_type) == ARRAY_TYPE
	       && constructor_max_index
	       && tree_int_cst_lt (constructor_max_index,
				   constructor_index))
	process_init_element (input_location,
			      pop_init_level (loc, 1, braced_init_obstack,
					      last_init_list_comma),
			      true, braced_init_obstack);
      وإلا
	اكسر;
    }
}

/* Push down into a subobject, for initialization.
   If this is for an explicit set of braces, IMPLICIT is 0.
   If it is because the next element belongs at a lower level,
   IMPLICIT is 1 (or 2 if the push is because of designator list).  */

فراغ
push_init_level (location_t loc, صحيح implicit,
		 بنية obstack *braced_init_obstack)
{
  بنية constructor_stack *p;
  tree value = NULL_TREE;

  /* Unless this is an explicit brace, we need to preserve previous
     content if any.  */
  𐤀𐤌 (implicit)
    {
      𐤀𐤌 (RECORD_OR_UNION_TYPE_P (constructor_type) && constructor_fields)
	value = find_init_member (constructor_fields, braced_init_obstack);
      وإلا 𐤀𐤌 (TREE_CODE (constructor_type) == ARRAY_TYPE)
	value = find_init_member (constructor_index, braced_init_obstack);
    }

  p = XNEW (بنية constructor_stack);
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
  p->replacement_value.value = NULL_TREE;
  p->replacement_value.original_code = ERROR_MARK;
  p->replacement_value.original_type = عدم;
  p->implicit = implicit;
  p->outer = 0;
  p->incremental = constructor_incremental;
  p->designated = constructor_designated;
  p->zero_padding_bits = constructor_zero_padding_bits;
  p->braced_scalar = constructor_braced_scalar;
  p->designator_depth = designator_depth;
  p->next = constructor_stack;
  p->range_stack = 0;
  constructor_stack = p;

  constructor_constant = 1;
  constructor_simple = 1;
  constructor_nonconst = 0;
  constructor_depth = SPELLING_DEPTH ();
  constructor_elements = عدم;
  constructor_incremental = 1;
  /* If the upper initializer is designated, then mark this as
     designated too to prevent bogus warnings.  */
  constructor_designated = p->designated;
  /* If the upper initializer has padding bits zeroed, that includes
     all nested initializers as well.  */
  constructor_zero_padding_bits = p->zero_padding_bits;
  constructor_braced_scalar = خطأ;
  constructor_pending_elts = 0;
  𐤀𐤌 (!implicit)
    {
      p->range_stack = constructor_range_stack;
      constructor_range_stack = 0;
      designator_depth = 0;
      designator_erroneous = 0;
    }

  /* Don't die if an entire brace-pair level is superfluous
     in the containing level.  */
  𐤀𐤌 (constructor_type == NULL_TREE)
    ;
  وإلا 𐤀𐤌 (RECORD_OR_UNION_TYPE_P (constructor_type))
    {
      /* Don't die if there are extra init elts at the end.  */
      𐤀𐤌 (constructor_fields == NULL_TREE)
	constructor_type = NULL_TREE;
      وإلا
	{
	  constructor_type = TREE_TYPE (constructor_fields);
	  push_member_name (constructor_fields);
	  constructor_depth++;
	}
    }
  وإلا 𐤀𐤌 (TREE_CODE (constructor_type) == ARRAY_TYPE)
    {
      constructor_type = TREE_TYPE (constructor_type);
      push_array_bounds (tree_to_uhwi (constructor_index));
      constructor_depth++;
    }

  𐤀𐤌 (constructor_type == NULL_TREE)
    {
      error_init (loc, "extra brace group at end of initializer");
      constructor_fields = NULL_TREE;
      constructor_unfilled_fields = NULL_TREE;
      أرجع;
    }

  𐤀𐤌 (value && TREE_CODE (value) == CONSTRUCTOR)
    {
      constructor_constant = TREE_CONSTANT (value);
      constructor_simple = TREE_STATIC (value);
      constructor_nonconst = CONSTRUCTOR_NON_CONST (value);
      constructor_elements = CONSTRUCTOR_ELTS (value);
      constructor_zero_padding_bits |= CONSTRUCTOR_ZERO_PADDING_BITS (value);
      𐤀𐤌 (!vec_safe_is_empty (constructor_elements)
	  && (TREE_CODE (constructor_type) == RECORD_TYPE
	      || TREE_CODE (constructor_type) == ARRAY_TYPE))
	set_nonincremental_init (braced_init_obstack);
    }

  𐤀𐤌 (implicit == 1)
    {
      found_missing_braces = 1;
      𐤀𐤌 (initializer_stack->missing_brace_richloc)
	initializer_stack->missing_brace_richloc->add_fixit_insert_before
	  (loc, "{");
    }

  𐤀𐤌 (RECORD_OR_UNION_TYPE_P (constructor_type))
    {
      constructor_fields = TYPE_FIELDS (constructor_type);
      /* Skip any nameless bit fields at the beginning.  */
      طالما (constructor_fields != NULL_TREE
	     && DECL_UNNAMED_BIT_FIELD (constructor_fields))
	constructor_fields = DECL_CHAIN (constructor_fields);

      constructor_unfilled_fields = constructor_fields;
      constructor_bit_index = bitsize_zero_node;
    }
  وإلا 𐤀𐤌 (gnu_vector_type_p (constructor_type))
    {
      /* Vectors are like simple fixed-size arrays.  */
      constructor_max_index =
	bitsize_int (TYPE_VECTOR_SUBPARTS (constructor_type) - 1);
      constructor_index = bitsize_int (0);
      constructor_unfilled_index = constructor_index;
    }
  وإلا 𐤀𐤌 (TREE_CODE (constructor_type) == ARRAY_TYPE)
    {
      𐤀𐤌 (TYPE_DOMAIN (constructor_type))
	{
	  constructor_max_index
	    = TYPE_MAX_VALUE (TYPE_DOMAIN (constructor_type));

	  /* Detect non-empty initializations of zero-length arrays.  */
	  𐤀𐤌 (constructor_max_index == NULL_TREE
	      && TYPE_SIZE (constructor_type))
	    constructor_max_index = integer_minus_one_node;

	  /* constructor_max_index needs to be an INTEGER_CST.  Attempts
	     to initialize VLAs will cause a proper error; avoid tree
	     checking errors as well by setting a safe value.  */
	  𐤀𐤌 (constructor_max_index
	      && TREE_CODE (constructor_max_index) != INTEGER_CST)
	    constructor_max_index = integer_minus_one_node;

	  constructor_index
	    = convert (bitsizetype,
		       TYPE_MIN_VALUE (TYPE_DOMAIN (constructor_type)));
	}
      وإلا
	constructor_index = bitsize_zero_node;

      constructor_unfilled_index = constructor_index;
      𐤀𐤌 (value && TREE_CODE (value) == STRING_CST)
	{
	  /* We need to split the char/wchar array into individual
	     characters, so that we don't have to special case it
	     everywhere.  */
	  set_nonincremental_init_from_string (value, braced_init_obstack);
	}
    }
  وإلا
    {
      𐤀𐤌 (constructor_type != error_mark_node)
	{
	  𐤀𐤌 (p->braced_scalar)
	    permerror_init (input_location, 0,
			    "braces around scalar initializer");
	  وإلا
	    warning_init (input_location, 0,
			  "braces around scalar initializer");
	  constructor_braced_scalar = true;
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

بنية c_expr
pop_init_level (location_t loc, صحيح implicit,
		بنية obstack *braced_init_obstack,
		location_t insert_before)
{
  بنية constructor_stack *p;
  بنية c_expr ret;
  ret.value = NULL_TREE;
  ret.original_code = ERROR_MARK;
  ret.original_type = عدم;
  ret.m_decimal = 0;

  𐤀𐤌 (implicit == 0)
    {
      /* When we come to an explicit close brace,
	 pop any inner levels that didn't have explicit braces.  */
      طالما (constructor_stack->implicit)
	process_init_element (input_location,
			      pop_init_level (loc, 1, braced_init_obstack,
					      insert_before),
			      true, braced_init_obstack);
      gcc_assert (!constructor_range_stack);
    }
  وإلا
    𐤀𐤌 (initializer_stack->missing_brace_richloc)
      initializer_stack->missing_brace_richloc->add_fixit_insert_before
	(insert_before, "}");

  /* Now output all pending elements.  */
  constructor_incremental = 1;
  output_pending_init_elements (1, braced_init_obstack);

  p = constructor_stack;

  /* Error for initializing a flexible array member.  */
  𐤀𐤌 (constructor_type && constructor_fields
      && flexible_array_member_type_p (constructor_type))
    {
      /* Silently discard empty initializations.  The parser will
	 already have pedwarned for empty brackets for C17 and earlier.  */
      𐤀𐤌 (integer_zerop (constructor_unfilled_index))
	constructor_type = NULL_TREE;
      𐤀𐤌 (constructor_type || flag_isoc23)
	{
	  gcc_assert (!constructor_type || !TYPE_SIZE (constructor_type));

	  𐤀𐤌 (constructor_depth <= 2)
	    pedwarn_init (loc, OPT_Wpedantic,
			  "initialization of a flexible array member");
	  وإلا 𐤀𐤌 (constructor_type)
	    error_init (loc, "initialization of flexible array member "
			     "in a nested context");
	  وإلا
	    pedwarn_init (loc, OPT_Wpedantic,
			  "initialization of flexible array member "
			  "in a nested context");

	  /* We have already issued an error message for the existence
	     of a flexible array member not at the end of the structure.
	     Discard the initializer so that we do not die later.  */
	  𐤀𐤌 (constructor_type
	      && DECL_CHAIN (constructor_fields) != NULL_TREE
	      && (!p->type || TREE_CODE (p->type) != UNION_TYPE))
	    constructor_type = NULL_TREE;
	}
    }

  بدل (vec_safe_length (constructor_elements))
    {
    حالة 0:
      /* Initialization with { } counts as zeroinit.  */
      constructor_zeroinit = 1;
      اكسر;
    حالة 1:
      /* This might be zeroinit as well.  */
      𐤀𐤌 (integer_zerop ((*constructor_elements)[0].value))
	constructor_zeroinit = 1;
      اكسر;
    افتراضي:
      /* If the constructor has more than one element, it can't be { 0 }.  */
      constructor_zeroinit = 0;
      اكسر;
    }

  /* Warn when some structs are initialized with direct aggregation.  */
  𐤀𐤌 (!implicit && found_missing_braces && warn_missing_braces
      && !constructor_zeroinit)
    {
      gcc_assert (initializer_stack->missing_brace_richloc);
      warning_at (initializer_stack->missing_brace_richloc,
		  OPT_Wmissing_braces,
		  "missing braces around initializer");
    }

  /* Warn when some struct elements are implicitly initialized to zero.  */
  𐤀𐤌 (warn_missing_field_initializers
      && constructor_type
      && TREE_CODE (constructor_type) == RECORD_TYPE
      && constructor_unfilled_fields)
    {
	/* Do not warn for flexible array members or zero-length arrays.  */
	طالما (constructor_unfilled_fields
	       && (!DECL_SIZE (constructor_unfilled_fields)
		   || integer_zerop (DECL_SIZE (constructor_unfilled_fields))))
	  constructor_unfilled_fields = DECL_CHAIN (constructor_unfilled_fields);

	𐤀𐤌 (constructor_unfilled_fields
	    /* Do not warn if this level of the initializer uses member
	       designators; it is likely to be deliberate.  */
	    && !constructor_designated
	    /* Do not warn about initializing with { 0 } or with { }.  */
	    && !constructor_zeroinit)
	  {
	    𐤀𐤌 (warning_at (input_location, OPT_Wmissing_field_initializers,
			    "missing initializer for field %qD of %qT",
			    constructor_unfilled_fields,
			    constructor_type))
	      inform (DECL_SOURCE_LOCATION (constructor_unfilled_fields),
		      "%qD declared here", constructor_unfilled_fields);
	  }
    }

  /* Pad out the end of the structure.  */
  𐤀𐤌 (p->replacement_value.value)
    /* If this closes a superfluous brace pair,
       just pass out the element between them.  */
    ret = p->replacement_value;
  وإلا 𐤀𐤌 (constructor_type == NULL_TREE)
    ;
  وإلا 𐤀𐤌 (!RECORD_OR_UNION_TYPE_P (constructor_type)
	   && TREE_CODE (constructor_type) != ARRAY_TYPE
	   && !gnu_vector_type_p (constructor_type))
    {
      /* A nonincremental scalar initializer--just return
	 the element, after verifying there is just one.
         Empty scalar initializers are supported in C23.  */
      𐤀𐤌 (vec_safe_is_empty (constructor_elements))
	{
	  𐤀𐤌 (constructor_erroneous || constructor_type == error_mark_node)
	    ret.value = error_mark_node;
	  وإلا 𐤀𐤌 (TREE_CODE (constructor_type) == FUNCTION_TYPE)
	    {
	      error_init (loc, "invalid initializer");
	      ret.value = error_mark_node;
	    }
	  وإلا 𐤀𐤌 (TREE_CODE (constructor_type) == POINTER_TYPE)
	    /* Ensure this is a null pointer constant in the case of a
	       'constexpr' object initialized with {}.  */
	    ret.value = build_zero_cst (ptr_type_node);
	  وإلا
	    ret.value = build_zero_cst (constructor_type);
	}
      وإلا 𐤀𐤌 (vec_safe_length (constructor_elements) != 1)
	{
	  error_init (loc, "extra elements in scalar initializer");
	  ret.value = (*constructor_elements)[0].value;
	}
      وإلا
	ret.value = (*constructor_elements)[0].value;
    }
  وإلا
    {
      𐤀𐤌 (constructor_erroneous)
	ret.value = error_mark_node;
      وإلا
	{
	  ret.value = build_constructor (constructor_type,
					 constructor_elements);
	  𐤀𐤌 (constructor_constant)
	    TREE_CONSTANT (ret.value) = 1;
	  𐤀𐤌 (constructor_constant && constructor_simple)
	    TREE_STATIC (ret.value) = 1;
	  𐤀𐤌 (constructor_nonconst)
	    CONSTRUCTOR_NON_CONST (ret.value) = 1;
	  𐤀𐤌 (constructor_zero_padding_bits)
	    CONSTRUCTOR_ZERO_PADDING_BITS (ret.value) = 1;
	}
    }

  𐤀𐤌 (ret.value && TREE_CODE (ret.value) != CONSTRUCTOR)
    {
      𐤀𐤌 (constructor_nonconst)
	ret.original_code = C_MAYBE_CONST_EXPR;
      وإلا 𐤀𐤌 (ret.original_code == C_MAYBE_CONST_EXPR)
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
  𐤀𐤌 (!p->implicit)
    constructor_range_stack = p->range_stack;
  RESTORE_SPELLING_DEPTH (constructor_depth);

  constructor_stack = p->next;
  XDELETE (p);

  𐤀𐤌 (ret.value == NULL_TREE && constructor_stack == 0)
    ret.value = error_mark_node;
  أرجع ret;
}

/* Common handling for both array range and field name designators.
   ARRAY argument is nonzero for array ranges.  Returns false for success.  */

ساكن منطقي
set_designator (location_t loc, منطقي array,
		بنية obstack *braced_init_obstack)
{
  tree subtype;
  تعداد tree_code subcode;

  /* Don't die if an entire brace-pair level is superfluous
     in the containing level, or for an erroneous type.  */
  𐤀𐤌 (constructor_type == NULL_TREE || constructor_type == error_mark_node)
    أرجع true;

  /* If there were errors in this designator list already, bail out
     silently.  */
  𐤀𐤌 (designator_erroneous)
    أرجع true;

  /* Likewise for an initializer for a variable-size type.  Those are
     diagnosed in the parser, except for empty initializer braces.  */
  𐤀𐤌 (COMPLETE_TYPE_P (constructor_type)
      && TREE_CODE (TYPE_SIZE (constructor_type)) != INTEGER_CST)
    أرجع true;

  𐤀𐤌 (!designator_depth)
    {
      gcc_assert (!constructor_range_stack);

      /* Designator list starts at the level of closest explicit
	 braces.  */
      طالما (constructor_stack->implicit)
	process_init_element (input_location,
			      pop_init_level (loc, 1, braced_init_obstack,
					      last_init_list_comma),
			      true, braced_init_obstack);
      constructor_designated = 1;
      أرجع خطأ;
    }

  بدل (TREE_CODE (constructor_type))
    {
    حالة  RECORD_TYPE:
    حالة  UNION_TYPE:
      subtype = TREE_TYPE (constructor_fields);
      𐤀𐤌 (subtype != error_mark_node)
	subtype = TYPE_MAIN_VARIANT (subtype);
      اكسر;
    حالة ARRAY_TYPE:
      subtype = TYPE_MAIN_VARIANT (TREE_TYPE (constructor_type));
      اكسر;
    افتراضي:
      gcc_unreachable ();
    }

  subcode = TREE_CODE (subtype);
  𐤀𐤌 (array && subcode != ARRAY_TYPE)
    {
      error_init (loc, "array index in non-array initializer");
      أرجع true;
    }
  وإلا 𐤀𐤌 (!array && subcode != RECORD_TYPE && subcode != UNION_TYPE)
    {
      error_init (loc, "field name not in record or union initializer");
      أرجع true;
    }

  constructor_designated = 1;
  finish_implicit_inits (loc, braced_init_obstack);
  push_init_level (loc, 2, braced_init_obstack);
  أرجع خطأ;
}

/* If there are range designators in designator list, push a new designator
   to constructor_range_stack.  RANGE_END is end of such stack range or
   NULL_TREE if there is no range designator at this level.  */

ساكن فراغ
push_range_stack (tree range_end, بنية obstack * braced_init_obstack)
{
  بنية constructor_range_stack *p;

  p = (بنية constructor_range_stack *)
    obstack_alloc (braced_init_obstack,
		   حجم (بنية constructor_range_stack));
  p->prev = constructor_range_stack;
  p->next = 0;
  p->fields = constructor_fields;
  p->range_start = constructor_index;
  p->index = constructor_index;
  p->stack = constructor_stack;
  p->range_end = range_end;
  𐤀𐤌 (constructor_range_stack)
    constructor_range_stack->next = p;
  constructor_range_stack = p;
}

/* Within an array initializer, specify the next index to be initialized.
   FIRST is that index.  If LAST is nonzero, then initialize a range
   of indices, running from FIRST through LAST.  */

فراغ
set_init_index (location_t loc, tree first, tree last,
		بنية obstack *braced_init_obstack)
{
  𐤀𐤌 (set_designator (loc, true, braced_init_obstack))
    أرجع;

  designator_erroneous = 1;

  𐤀𐤌 (!INTEGRAL_TYPE_P (TREE_TYPE (first))
      || (last && !INTEGRAL_TYPE_P (TREE_TYPE (last))))
    {
      error_init (loc, "array index in initializer not of integer type");
      أرجع;
    }

  𐤀𐤌 (TREE_CODE (first) != INTEGER_CST)
    {
      first = c_fully_fold (first, خطأ, عدم);
      𐤀𐤌 (TREE_CODE (first) == INTEGER_CST)
	pedwarn_init (loc, OPT_Wpedantic,
		      "array index in initializer is not "
		      "an integer constant expression");
    }

  𐤀𐤌 (last && TREE_CODE (last) != INTEGER_CST)
    {
      last = c_fully_fold (last, خطأ, عدم);
      𐤀𐤌 (TREE_CODE (last) == INTEGER_CST)
	pedwarn_init (loc, OPT_Wpedantic,
		      "array index in initializer is not "
		      "an integer constant expression");
    }

  𐤀𐤌 (TREE_CODE (first) != INTEGER_CST)
    error_init (loc, "nonconstant array index in initializer");
  وإلا 𐤀𐤌 (last != NULL_TREE && TREE_CODE (last) != INTEGER_CST)
    error_init (loc, "nonconstant array index in initializer");
  وإلا 𐤀𐤌 (TREE_CODE (constructor_type) != ARRAY_TYPE)
    error_init (loc, "array index in non-array initializer");
  وإلا 𐤀𐤌 (tree_int_cst_sgn (first) == -1)
    error_init (loc, "array index in initializer exceeds array bounds");
  وإلا 𐤀𐤌 (constructor_max_index
	   && tree_int_cst_lt (constructor_max_index, first))
    error_init (loc, "array index in initializer exceeds array bounds");
  وإلا
    {
      constant_expression_warning (first);
      𐤀𐤌 (last)
	constant_expression_warning (last);
      constructor_index = convert (bitsizetype, first);
      𐤀𐤌 (tree_int_cst_lt (constructor_index, first))
	{
	  constructor_index = copy_node (constructor_index);
	  TREE_OVERFLOW (constructor_index) = 1;
	}

      𐤀𐤌 (last)
	{
	  𐤀𐤌 (tree_int_cst_equal (first, last))
	    last = NULL_TREE;
	  وإلا 𐤀𐤌 (tree_int_cst_lt (last, first))
	    {
	      error_init (loc, "empty index range in initializer");
	      last = NULL_TREE;
	    }
	  وإلا
	    {
	      last = convert (bitsizetype, last);
	      𐤀𐤌 (constructor_max_index != NULL_TREE
		  && tree_int_cst_lt (constructor_max_index, last))
		{
		  error_init (loc, "array index range in initializer exceeds "
			      "array bounds");
		  last = NULL_TREE;
		}
	    }
	}

      designator_depth++;
      designator_erroneous = 0;
      𐤀𐤌 (constructor_range_stack || last)
	push_range_stack (last, braced_init_obstack);
    }
}

/* Within a struct initializer, specify the next field to be initialized.  */

فراغ
set_init_label (location_t loc, tree fieldname, location_t fieldname_loc,
		بنية obstack *braced_init_obstack)
{
  tree field;

  𐤀𐤌 (set_designator (loc, خطأ, braced_init_obstack))
    أرجع;

  designator_erroneous = 1;

  𐤀𐤌 (!RECORD_OR_UNION_TYPE_P (constructor_type))
    {
      error_init (loc, "field name not in record or union initializer");
      أرجع;
    }

  field = lookup_field (constructor_type, fieldname);

  𐤀𐤌 (field == NULL_TREE)
    {
      tree guessed_id = lookup_field_fuzzy (constructor_type, fieldname);
      𐤀𐤌 (guessed_id)
	{
	  gcc_rich_location rich_loc (fieldname_loc);
	  rich_loc.add_fixit_misspelled_id (fieldname_loc, guessed_id);
	  error_at (&rich_loc,
		    "%qT has no member named %qE; did you mean %qE?",
		    constructor_type, fieldname, guessed_id);
	}
      وإلا
	error_at (fieldname_loc, "%qT has no member named %qE",
		  constructor_type, fieldname);
    }
  وإلا
    𐤐𐤏𐤋
      {
	constructor_fields = TREE_VALUE (field);
	designator_depth++;
	designator_erroneous = 0;
	𐤀𐤌 (constructor_range_stack)
	  push_range_stack (NULL_TREE, braced_init_obstack);
	field = TREE_CHAIN (field);
	𐤀𐤌 (field)
	  {
	    𐤀𐤌 (set_designator (loc, خطأ, braced_init_obstack))
	      أرجع;
	  }
      }
    طالما (field != NULL_TREE);
}

/* Helper function for add_pending_init.  Find inorder successor of P
   in AVL tree.  */
ساكن بنية init_node *
init_node_successor (بنية init_node *p)
{
  بنية init_node *r;
  𐤀𐤌 (p->right)
    {
      r = p->right;
      طالما (r->left)
	r = r->left;
      أرجع r;
    }
  r = p->parent;
  طالما (r && p == r->right)
    {
      p = r;
      r = r->parent;
    }
  أرجع r;
}

/* Add a new initializer to the tree of pending initializers.  PURPOSE
   identifies the initializer, either array index or field in a structure.
   VALUE is the value of that index or field.  If ORIGTYPE is not
   NULL_TREE, it is the original type of VALUE.

   IMPLICIT is true if value comes from pop_init_level (1),
   the new initializer has been merged with the existing one
   and thus no warnings should be emitted about overriding an
   existing initializer.  */

ساكن فراغ
add_pending_init (location_t loc, tree purpose, tree value, tree origtype,
		  منطقي implicit, بنية obstack *braced_init_obstack)
{
  بنية init_node *p, **q, *r;

  q = &constructor_pending_elts;
  p = 0;

  𐤀𐤌 (TREE_CODE (constructor_type) == ARRAY_TYPE)
    {
      طالما (*q != 0)
	{
	  p = *q;
	  𐤀𐤌 (tree_int_cst_lt (purpose, p->purpose))
	    q = &p->left;
	  وإلا 𐤀𐤌 (tree_int_cst_lt (p->purpose, purpose))
	    {
	      𐤀𐤌 (TREE_CODE (p->value) != RAW_DATA_CST
		  || (p->right
		      && tree_int_cst_le (p->right->purpose, purpose)))
		q = &p->right;
	      وإلا
		{
		  widest_int pp = wi::to_widest (p->purpose);
		  widest_int pw = wi::to_widest (purpose);
		  𐤀𐤌 (pp + RAW_DATA_LENGTH (p->value) <= pw)
		    q = &p->right;
		  وإلا
		    {
		      /* Override which should split the old RAW_DATA_CST
			 into 2 or 3 pieces.  */
		      𐤀𐤌 (!implicit && warn_override_init)
			warning_init (loc, OPT_Woverride_init,
				      "initialized field overwritten");
		      unsigned HOST_WIDE_INT start = (pw - pp).to_uhwi ();
		      unsigned HOST_WIDE_INT len = 1;
		      𐤀𐤌 (TREE_CODE (value) == RAW_DATA_CST)
			len = RAW_DATA_LENGTH (value);
		      unsigned HOST_WIDE_INT end = 0;
		      unsigned plen = RAW_DATA_LENGTH (p->value);
		      gcc_checking_assert (start < plen && start);
		      𐤀𐤌 (plen - start > len)
			end = plen - start - len;
		      tree v = p->value;
		      tree origtype = p->origtype;
		      𐤀𐤌 (start == 1)
			p->value = build_int_cst (TREE_TYPE (v),
						  RAW_DATA_UCHAR_ELT (v, 0));
		      وإلا
			{
			  p->value = v;
			  𐤀𐤌 (end > 1)
			    v = copy_node (v);
			  RAW_DATA_LENGTH (p->value) = start;
			}
		      𐤀𐤌 (end)
			{
			  tree epurpose
			    = size_binop (PLUS_EXPR, purpose,
					  bitsize_int (len));
			  𐤀𐤌 (end > 1)
			    {
			      RAW_DATA_LENGTH (v) -= plen - end;
			      RAW_DATA_POINTER (v) += plen - end;
			    }
			  وإلا
			    v = build_int_cst (TREE_TYPE (v),
					       RAW_DATA_UCHAR_ELT (v, plen
								      - end));
			  add_pending_init (loc, epurpose, v, origtype,
					    implicit, braced_init_obstack);
			}
		      q = &constructor_pending_elts;
		      استمر;
		    }
		}
	    }
	  وإلا
	    {
	      𐤀𐤌 (TREE_CODE (p->value) == RAW_DATA_CST
		  && (RAW_DATA_LENGTH (p->value)
		      > (TREE_CODE (value) == RAW_DATA_CST
			 ? RAW_DATA_LENGTH (value) : 1)))
		{
		  /* Override which should split the old RAW_DATA_CST
		     into 2 pieces.  */
		  𐤀𐤌 (!implicit && warn_override_init)
		    warning_init (loc, OPT_Woverride_init,
				  "initialized field overwritten");
		  unsigned HOST_WIDE_INT len = 1;
		  𐤀𐤌 (TREE_CODE (value) == RAW_DATA_CST)
		    len = RAW_DATA_LENGTH (value);
		  𐤀𐤌 ((unsigned) RAW_DATA_LENGTH (p->value) > len + 1)
		    {
		      RAW_DATA_LENGTH (p->value) -= len;
		      RAW_DATA_POINTER (p->value) += len;
		    }
		  وإلا
		    {
		      unsigned صحيح l = RAW_DATA_LENGTH (p->value) - 1;
		      p->value
			= build_int_cst (TREE_TYPE (p->value),
					 RAW_DATA_UCHAR_ELT (p->value, l));
		    }
		  p->purpose = size_binop (PLUS_EXPR, p->purpose,
					   bitsize_int (len));
		  استمر;
		}
	      𐤀𐤌 (TREE_CODE (value) == RAW_DATA_CST)
		{
		handle_raw_data:
		  /* RAW_DATA_CST value might overlap various further
		     prior initval entries.  Find out how many.  */
		  unsigned cnt = 0;
		  widest_int w
		    = wi::to_widest (purpose) + RAW_DATA_LENGTH (value);
		  بنية init_node *r = p, *last = عدم;
		  منطقي override_init = warn_override_init;
		  طالما ((r = init_node_successor (r))
			 && wi::to_widest (r->purpose) < w)
		    {
		      ++cnt;
		      𐤀𐤌 (TREE_SIDE_EFFECTS (r->value))
			warning_init (loc, OPT_Woverride_init_side_effects,
				      "initialized field with side-effects "
				      "overwritten");
		      وإلا 𐤀𐤌 (override_init)
			{
			  warning_init (loc, OPT_Woverride_init,
					"initialized field overwritten");
			  override_init = خطأ;
			}
		      last = r;
		    }
		  𐤀𐤌 (cnt)
		    {
		      𐤀𐤌 (TREE_CODE (last->value) == RAW_DATA_CST
			  && (wi::to_widest (last->purpose)
			      + RAW_DATA_LENGTH (last->value) > w))
			{
			  /* The last overlapping prior initval overlaps
			     only partially.  Shrink it and decrease cnt.  */
			  unsigned صحيح l = (wi::to_widest (last->purpose)
					    + RAW_DATA_LENGTH (last->value)
					    - w).to_uhwi ();
			  --cnt;
			  RAW_DATA_LENGTH (last->value) -= l;
			  RAW_DATA_POINTER (last->value) += l;
			  𐤀𐤌 (RAW_DATA_LENGTH (last->value) == 1)
			    last->value
			      = build_int_cst (TREE_TYPE (last->value),
					       RAW_DATA_UCHAR_ELT (last->value,
								   0));
			  last->purpose
			    = size_binop (PLUS_EXPR, last->purpose,
					  bitsize_int (l));
			}
		      /* Instead of deleting cnt nodes from the AVL tree
			 and rebalancing, peel of last cnt bytes from the
			 RAW_DATA_CST.  Overriding thousands of previously
			 initialized array elements with #embed needs to work,
			 but doesn't need to be super efficient.  */
		      gcc_checking_assert ((unsigned) RAW_DATA_LENGTH (value)
					   > cnt);
		      RAW_DATA_LENGTH (value) -= cnt;
		      ثابت unsigned حرف *s
			= &RAW_DATA_UCHAR_ELT (value, RAW_DATA_LENGTH (value));
		      unsigned صحيح o = RAW_DATA_LENGTH (value);
		      لكل (r = p; cnt--; ++o, ++s)
			{
			  r = init_node_successor (r);
			  r->purpose = size_binop (PLUS_EXPR, purpose,
						   bitsize_int (o));
			  r->value = build_int_cst (TREE_TYPE (value), *s);
			  r->origtype = origtype;
			}
		      𐤀𐤌 (RAW_DATA_LENGTH (value) == 1)
			value = build_int_cst (TREE_TYPE (value),
					       RAW_DATA_UCHAR_ELT (value, 0));
		    }
		}
	      𐤀𐤌 (!implicit)
		{
		  𐤀𐤌 (TREE_SIDE_EFFECTS (p->value))
		    warning_init (loc, OPT_Woverride_init_side_effects,
				  "initialized field with side-effects "
				  "overwritten");
		  وإلا 𐤀𐤌 (warn_override_init)
		    warning_init (loc, OPT_Woverride_init,
				  "initialized field overwritten");
		}
	      p->value = value;
	      p->origtype = origtype;
	      أرجع;
	    }
	}
      𐤀𐤌 (TREE_CODE (value) == RAW_DATA_CST && p)
	{
	  بنية init_node *r;
	  𐤀𐤌 (q == &p->left)
	    r = p;
	  وإلا
	    r = init_node_successor (p);
	  𐤀𐤌 (r && wi::to_widest (r->purpose) < (wi::to_widest (purpose)
						 + RAW_DATA_LENGTH (value)))
	    {
	      /* Overlap with at least one prior initval in the range but
		 not at the start.  */
	      p = r;
	      p->purpose = purpose;
	      اذهب handle_raw_data;
	    }
	}
    }
  وإلا
    {
      tree bitpos;

      bitpos = bit_position (purpose);
      طالما (*q != عدم)
	{
	  p = *q;
	  𐤀𐤌 (tree_int_cst_lt (bitpos, bit_position (p->purpose)))
	    q = &p->left;
	  وإلا 𐤀𐤌 (p->purpose != purpose)
	    q = &p->right;
	  وإلا
	    {
	      𐤀𐤌 (!implicit)
		{
		  𐤀𐤌 (TREE_SIDE_EFFECTS (p->value))
		    warning_init (loc, OPT_Woverride_init_side_effects,
				  "initialized field with side-effects "
				  "overwritten");
		  وإلا 𐤀𐤌 (warn_override_init)
		    warning_init (loc, OPT_Woverride_init,
				  "initialized field overwritten");
		}
	      p->value = value;
	      p->origtype = origtype;
	      أرجع;
	    }
	}
    }

  r = (بنية init_node *) obstack_alloc (braced_init_obstack,
					  حجم (بنية init_node));
  r->purpose = purpose;
  r->value = value;
  r->origtype = origtype;

  *q = r;
  r->parent = p;
  r->left = 0;
  r->right = 0;
  r->balance = 0;

  طالما (p)
    {
      بنية init_node *s;

      𐤀𐤌 (r == p->left)
	{
	  𐤀𐤌 (p->balance == 0)
	    p->balance = -1;
	  وإلا 𐤀𐤌 (p->balance < 0)
	    {
	      𐤀𐤌 (r->balance < 0)
		{
		  /* L rotation.  */
		  p->left = r->right;
		  𐤀𐤌 (p->left)
		    p->left->parent = p;
		  r->right = p;

		  p->balance = 0;
		  r->balance = 0;

		  s = p->parent;
		  p->parent = r;
		  r->parent = s;
		  𐤀𐤌 (s)
		    {
		      𐤀𐤌 (s->left == p)
			s->left = r;
		      وإلا
			s->right = r;
		    }
		  وإلا
		    constructor_pending_elts = r;
		}
	      وإلا
		{
		  /* LR rotation.  */
		  بنية init_node *t = r->right;

		  r->right = t->left;
		  𐤀𐤌 (r->right)
		    r->right->parent = r;
		  t->left = r;

		  p->left = t->right;
		  𐤀𐤌 (p->left)
		    p->left->parent = p;
		  t->right = p;

		  p->balance = t->balance < 0;
		  r->balance = -(t->balance > 0);
		  t->balance = 0;

		  s = p->parent;
		  p->parent = t;
		  r->parent = t;
		  t->parent = s;
		  𐤀𐤌 (s)
		    {
		      𐤀𐤌 (s->left == p)
			s->left = t;
		      وإلا
			s->right = t;
		    }
		  وإلا
		    constructor_pending_elts = t;
		}
	      اكسر;
	    }
	  وإلا
	    {
	      /* p->balance == +1; growth of left side balances the node.  */
	      p->balance = 0;
	      اكسر;
	    }
	}
      وإلا /* r == p->right */
	{
	  𐤀𐤌 (p->balance == 0)
	    /* Growth propagation from right side.  */
	    p->balance++;
	  وإلا 𐤀𐤌 (p->balance > 0)
	    {
	      𐤀𐤌 (r->balance > 0)
		{
		  /* R rotation.  */
		  p->right = r->left;
		  𐤀𐤌 (p->right)
		    p->right->parent = p;
		  r->left = p;

		  p->balance = 0;
		  r->balance = 0;

		  s = p->parent;
		  p->parent = r;
		  r->parent = s;
		  𐤀𐤌 (s)
		    {
		      𐤀𐤌 (s->left == p)
			s->left = r;
		      وإلا
			s->right = r;
		    }
		  وإلا
		    constructor_pending_elts = r;
		}
	      وإلا /* r->balance == -1 */
		{
		  /* RL rotation */
		  بنية init_node *t = r->left;

		  r->left = t->right;
		  𐤀𐤌 (r->left)
		    r->left->parent = r;
		  t->right = r;

		  p->right = t->left;
		  𐤀𐤌 (p->right)
		    p->right->parent = p;
		  t->left = p;

		  r->balance = (t->balance < 0);
		  p->balance = -(t->balance > 0);
		  t->balance = 0;

		  s = p->parent;
		  p->parent = t;
		  r->parent = t;
		  t->parent = s;
		  𐤀𐤌 (s)
		    {
		      𐤀𐤌 (s->left == p)
			s->left = t;
		      وإلا
			s->right = t;
		    }
		  وإلا
		    constructor_pending_elts = t;
		}
	      اكسر;
	    }
	  وإلا
	    {
	      /* p->balance == -1; growth of right side balances the node.  */
	      p->balance = 0;
	      اكسر;
	    }
	}

      r = p;
      p = p->parent;
    }
}

/* Build AVL tree from a sorted chain.  */

ساكن فراغ
set_nonincremental_init (بنية obstack * braced_init_obstack)
{
  unsigned HOST_WIDE_INT ix;
  tree index, value;

  𐤀𐤌 (TREE_CODE (constructor_type) != RECORD_TYPE
      && TREE_CODE (constructor_type) != ARRAY_TYPE)
    أرجع;

  FOR_EACH_CONSTRUCTOR_ELT (constructor_elements, ix, index, value)
    add_pending_init (input_location, index, value, NULL_TREE, true,
		      braced_init_obstack);
  constructor_elements = عدم;
  𐤀𐤌 (TREE_CODE (constructor_type) == RECORD_TYPE)
    {
      constructor_unfilled_fields = TYPE_FIELDS (constructor_type);
      /* Skip any nameless bit fields at the beginning.  */
      طالما (constructor_unfilled_fields != NULL_TREE
	     && DECL_UNNAMED_BIT_FIELD (constructor_unfilled_fields))
	constructor_unfilled_fields = TREE_CHAIN (constructor_unfilled_fields);

    }
  وإلا 𐤀𐤌 (TREE_CODE (constructor_type) == ARRAY_TYPE)
    {
      𐤀𐤌 (TYPE_DOMAIN (constructor_type))
	constructor_unfilled_index
	  = convert (bitsizetype,
		     TYPE_MIN_VALUE (TYPE_DOMAIN (constructor_type)));
      وإلا
	constructor_unfilled_index = bitsize_zero_node;
    }
  constructor_incremental = 0;
}

/* Build AVL tree from a string constant.  */

ساكن فراغ
set_nonincremental_init_from_string (tree str,
				     بنية obstack * braced_init_obstack)
{
  tree value, purpose, type;
  HOST_WIDE_INT val[2];
  ثابت حرف *p, *end;
  صحيح byte, wchar_bytes, charwidth, bitpos;

  gcc_assert (TREE_CODE (constructor_type) == ARRAY_TYPE);

  wchar_bytes = TYPE_PRECISION (TREE_TYPE (TREE_TYPE (str))) / BITS_PER_UNIT;
  charwidth = TYPE_PRECISION (char_type_node);
  gcc_assert ((size_t) wchar_bytes * charwidth
	      <= ARRAY_SIZE (val) * HOST_BITS_PER_WIDE_INT);
  type = TREE_TYPE (constructor_type);
  p = TREE_STRING_POINTER (str);
  end = p + TREE_STRING_LENGTH (str);

  لكل (purpose = bitsize_zero_node;
       p < end
       && !(constructor_max_index
	    && tree_int_cst_lt (constructor_max_index, purpose));
       purpose = size_binop (PLUS_EXPR, purpose, bitsize_one_node))
    {
      𐤀𐤌 (wchar_bytes == 1)
	{
	  val[0] = (unsigned حرف) *p++;
	  val[1] = 0;
	}
      وإلا
	{
	  val[1] = 0;
	  val[0] = 0;
	  لكل (byte = 0; byte < wchar_bytes; byte++)
	    {
	      𐤀𐤌 (BYTES_BIG_ENDIAN)
		bitpos = (wchar_bytes - byte - 1) * charwidth;
	      وإلا
		bitpos = byte * charwidth;
	      val[bitpos / HOST_BITS_PER_WIDE_INT]
		|= ((unsigned HOST_WIDE_INT) ((unsigned حرف) *p++))
		   << (bitpos % HOST_BITS_PER_WIDE_INT);
	    }
	}

      𐤀𐤌 (!TYPE_UNSIGNED (type))
	{
	  bitpos = ((wchar_bytes - 1) * charwidth) + HOST_BITS_PER_CHAR;
	  𐤀𐤌 (bitpos < HOST_BITS_PER_WIDE_INT)
	    {
	      𐤀𐤌 (val[0] & (HOST_WIDE_INT_1 << (bitpos - 1)))
		{
		  val[0] |= HOST_WIDE_INT_M1U << bitpos;
		  val[1] = -1;
		}
	    }
	  وإلا 𐤀𐤌 (bitpos == HOST_BITS_PER_WIDE_INT)
	    {
	      𐤀𐤌 (val[0] < 0)
		val[1] = -1;
	    }
	  وإلا 𐤀𐤌 (val[1] & (HOST_WIDE_INT_1
			     << (bitpos - 1 - HOST_BITS_PER_WIDE_INT)))
	    val[1] |= HOST_WIDE_INT_M1U << (bitpos - HOST_BITS_PER_WIDE_INT);
	}

      value = wide_int_to_tree (type,
				wide_int::from_array (val, 2,
						      HOST_BITS_PER_WIDE_INT * 2));
      add_pending_init (input_location, purpose, value, NULL_TREE, true,
                        braced_init_obstack);
    }

  constructor_incremental = 0;
}

/* Return value of FIELD in pending initializer or NULL_TREE if the field was
   not initialized yet.  */

ساكن tree
find_init_member (tree field, بنية obstack * braced_init_obstack)
{
  بنية init_node *p;

  𐤀𐤌 (TREE_CODE (constructor_type) == ARRAY_TYPE)
    {
      𐤀𐤌 (constructor_incremental
	  && tree_int_cst_lt (field, constructor_unfilled_index))
	set_nonincremental_init (braced_init_obstack);

      p = constructor_pending_elts;
      طالما (p)
	{
	  𐤀𐤌 (tree_int_cst_lt (field, p->purpose))
	    p = p->left;
	  وإلا 𐤀𐤌 (tree_int_cst_lt (p->purpose, field))
	    p = p->right;
	  وإلا
	    أرجع p->value;
	}
    }
  وإلا 𐤀𐤌 (TREE_CODE (constructor_type) == RECORD_TYPE)
    {
      tree bitpos = bit_position (field);

      𐤀𐤌 (constructor_incremental
	  && (!constructor_unfilled_fields
	      || tree_int_cst_lt (bitpos,
				  bit_position (constructor_unfilled_fields))))
	set_nonincremental_init (braced_init_obstack);

      p = constructor_pending_elts;
      طالما (p)
	{
	  𐤀𐤌 (field == p->purpose)
	    أرجع p->value;
	  وإلا 𐤀𐤌 (tree_int_cst_lt (bitpos, bit_position (p->purpose)))
	    p = p->left;
	  وإلا
	    p = p->right;
	}
    }
  وإلا 𐤀𐤌 (TREE_CODE (constructor_type) == UNION_TYPE)
    {
      𐤀𐤌 (!vec_safe_is_empty (constructor_elements)
	  && (constructor_elements->last ().index == field))
	أرجع constructor_elements->last ().value;
    }
  أرجع NULL_TREE;
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

ساكن فراغ
output_init_element (location_t loc, tree value, tree origtype,
		     منطقي strict_string, tree type, tree field, منطقي pending,
		     منطقي implicit, بنية obstack * braced_init_obstack)
{
  tree semantic_type = NULL_TREE;
  منطقي maybe_const = true;
  منطقي npc, int_const_expr, arith_const_expr;

  𐤀𐤌 (type == error_mark_node || value == error_mark_node)
    {
      constructor_erroneous = 1;
      أرجع;
    }
  𐤀𐤌 (TREE_CODE (TREE_TYPE (value)) == ARRAY_TYPE
      && (TREE_CODE (value) == STRING_CST
	  || TREE_CODE (value) == COMPOUND_LITERAL_EXPR)
      && !(TREE_CODE (value) == STRING_CST
	   && TREE_CODE (type) == ARRAY_TYPE
	   && INTEGRAL_TYPE_P (TREE_TYPE (type)))
      && !comptypes (TYPE_MAIN_VARIANT (TREE_TYPE (value)),
		     TYPE_MAIN_VARIANT (type)))
    value = array_to_pointer_conversion (input_location, value);

  𐤀𐤌 (TREE_CODE (value) == COMPOUND_LITERAL_EXPR
      && require_constant_value && pending)
    {
      /* As an extension, allow initializing objects with static storage
	 duration with compound literals (which are then treated just as
	 the brace enclosed list they contain).  */
      𐤀𐤌 (flag_isoc99)
	pedwarn_init (loc, OPT_Wpedantic, "initializer element is not "
		      "constant");
      tree decl = COMPOUND_LITERAL_EXPR_DECL (value);
      value = DECL_INITIAL (decl);
    }

  npc = null_pointer_constant_p (value);
  int_const_expr = (TREE_CODE (value) == INTEGER_CST
		    && !TREE_OVERFLOW (value)
		    && INTEGRAL_TYPE_P (TREE_TYPE (value)));
  /* Not fully determined before folding.  */
  arith_const_expr = true;
  𐤀𐤌 (TREE_CODE (value) == EXCESS_PRECISION_EXPR)
    {
      semantic_type = TREE_TYPE (value);
      value = TREE_OPERAND (value, 0);
    }
  value = c_fully_fold (value, require_constant_value, &maybe_const);
  /* TODO: this may not detect all cases of expressions folding to
     constants that are not arithmetic constant expressions.  */
  𐤀𐤌 (!maybe_const)
    arith_const_expr = خطأ;
  وإلا 𐤀𐤌 (!INTEGRAL_TYPE_P (TREE_TYPE (value))
	   && TREE_CODE (TREE_TYPE (value)) != REAL_TYPE
	   && TREE_CODE (TREE_TYPE (value)) != COMPLEX_TYPE)
    arith_const_expr = خطأ;
  وإلا 𐤀𐤌 (TREE_CODE (value) != INTEGER_CST
	   && TREE_CODE (value) != REAL_CST
	   && TREE_CODE (value) != COMPLEX_CST
	   && TREE_CODE (value) != RAW_DATA_CST)
    arith_const_expr = خطأ;
  وإلا 𐤀𐤌 (TREE_OVERFLOW (value))
    arith_const_expr = خطأ;

  𐤀𐤌 (value == error_mark_node)
    constructor_erroneous = 1;
  وإلا 𐤀𐤌 (!TREE_CONSTANT (value))
    constructor_constant = 0;
  وإلا 𐤀𐤌 (!initializer_constant_valid_p (value,
					  TREE_TYPE (value),
					  AGGREGATE_TYPE_P (constructor_type)
					  && TYPE_REVERSE_STORAGE_ORDER
					     (constructor_type))
	   || (RECORD_OR_UNION_TYPE_P (constructor_type)
	       && DECL_C_BIT_FIELD (field)
	       && TREE_CODE (value) != INTEGER_CST))
    constructor_simple = 0;
  𐤀𐤌 (!maybe_const)
    constructor_nonconst = 1;

  /* Digest the initializer and issue any errors about incompatible
     types before issuing errors about non-constant initializers.  */
  tree new_value = value;
  𐤀𐤌 (semantic_type)
    new_value = build1 (EXCESS_PRECISION_EXPR, semantic_type, value);
  /* In the case of braces around a scalar initializer, the result of
     this initializer processing goes through digest_init again at the
     outer level.  In the case of a constexpr initializer for a
     pointer, avoid converting a null pointer constant to something
     that is not a null pointer constant to avoid a spurious error
     from that second processing.  */
  𐤀𐤌 (!require_constexpr_value
      || !npc
      || TREE_CODE (constructor_type) != POINTER_TYPE)
    new_value = digest_init (loc,
			     RECORD_OR_UNION_TYPE_P (constructor_type)
			     ? field : constructor_fields
			     ? constructor_fields : constructor_decl,
			     type, new_value, origtype, npc,
			     int_const_expr, arith_const_expr, strict_string,
			     require_constant_value, require_constexpr_value);
  𐤀𐤌 (new_value == error_mark_node)
    {
      constructor_erroneous = 1;
      أرجع;
    }
  𐤀𐤌 (require_constant_value || require_constant_elements)
    constant_expression_warning (new_value);

  /* Proceed to check the constness of the original initializer.  */
  𐤀𐤌 (!initializer_constant_valid_p (value, TREE_TYPE (value)))
    {
      𐤀𐤌 (require_constant_value)
	{
	  error_init (loc, "initializer element is not constant");
	  value = error_mark_node;
	}
      وإلا 𐤀𐤌 (require_constant_elements)
	pedwarn (loc, OPT_Wpedantic,
		 "initializer element is not computable at load time");
    }
  وإلا 𐤀𐤌 (!maybe_const
	   && (require_constant_value || require_constant_elements))
    pedwarn_init (loc, OPT_Wpedantic,
		  "initializer element is not a constant expression");
  /* digest_init has already carried out the additional checks
     required for 'constexpr' initializers (using the information
     passed to it about whether the original initializer was certain
     kinds of constant expression), so that check does not need to be
     repeated here.  */

  /* Issue -Wc++-compat warnings about initializing a bitfield with
     enum type.  */
  𐤀𐤌 (warn_cxx_compat
      && field != NULL_TREE
      && TREE_CODE (field) == FIELD_DECL
      && DECL_BIT_FIELD_TYPE (field) != NULL_TREE
      && (TYPE_MAIN_VARIANT (DECL_BIT_FIELD_TYPE (field))
	  != TYPE_MAIN_VARIANT (type))
      && TREE_CODE (DECL_BIT_FIELD_TYPE (field)) == ENUMERAL_TYPE)
    {
      tree checktype = origtype != NULL_TREE ? origtype : TREE_TYPE (value);
      𐤀𐤌 (checktype != error_mark_node
	  && (TYPE_MAIN_VARIANT (checktype)
	      != TYPE_MAIN_VARIANT (DECL_BIT_FIELD_TYPE (field))))
	warning_init (loc, OPT_Wc___compat,
		      "enum conversion in initialization is invalid in C++");
    }

  /* If this field is empty and does not have side effects (and is not at
     the end of structure), don't do anything other than checking the
     initializer.  */
  𐤀𐤌 (field
      && (TREE_TYPE (field) == error_mark_node
	  || (COMPLETE_TYPE_P (TREE_TYPE (field))
	      && integer_zerop (TYPE_SIZE (TREE_TYPE (field)))
	      && !TREE_SIDE_EFFECTS (new_value)
	      && (TREE_CODE (constructor_type) == ARRAY_TYPE
		  || DECL_CHAIN (field)))))
    أرجع;

  /* Finally, set VALUE to the initializer value digested above.  */
  value = new_value;

  /* If this element doesn't come next in sequence,
     put it on constructor_pending_elts.  */
  𐤀𐤌 (TREE_CODE (constructor_type) == ARRAY_TYPE
      && (!constructor_incremental
	  || !tree_int_cst_equal (field, constructor_unfilled_index)
	  || (TREE_CODE (value) == RAW_DATA_CST
	      && constructor_pending_elts
	      && pending)))
    {
      𐤀𐤌 (constructor_incremental
	  && (tree_int_cst_lt (field, constructor_unfilled_index)
	      || (TREE_CODE (value) == RAW_DATA_CST
		  && constructor_pending_elts
		  && pending)))
	set_nonincremental_init (braced_init_obstack);

      add_pending_init (loc, field, value, origtype, implicit,
			braced_init_obstack);
      أرجع;
    }
  وإلا 𐤀𐤌 (TREE_CODE (constructor_type) == RECORD_TYPE
	   && (!constructor_incremental
	       || field != constructor_unfilled_fields))
    {
      /* We do this for records but not for unions.  In a union,
	 no matter which field is specified, it can be initialized
	 right away since it starts at the beginning of the union.  */
      𐤀𐤌 (constructor_incremental)
	{
	  𐤀𐤌 (!constructor_unfilled_fields)
	    set_nonincremental_init (braced_init_obstack);
	  وإلا
	    {
	      tree bitpos, unfillpos;

	      bitpos = bit_position (field);
	      unfillpos = bit_position (constructor_unfilled_fields);

	      𐤀𐤌 (tree_int_cst_lt (bitpos, unfillpos))
		set_nonincremental_init (braced_init_obstack);
	    }
	}

      add_pending_init (loc, field, value, origtype, implicit,
			braced_init_obstack);
      أرجع;
    }
  وإلا 𐤀𐤌 (TREE_CODE (constructor_type) == UNION_TYPE
	   && !vec_safe_is_empty (constructor_elements))
    {
      𐤀𐤌 (!implicit)
	{
	  𐤀𐤌 (TREE_SIDE_EFFECTS (constructor_elements->last ().value))
	    warning_init (loc, OPT_Woverride_init_side_effects,
			  "initialized field with side-effects overwritten");
	  وإلا 𐤀𐤌 (warn_override_init)
	    warning_init (loc, OPT_Woverride_init,
			  "initialized field overwritten");
	}

      /* We can have just one union field set.  */
      constructor_elements = عدم;
    }

  /* Otherwise, output this element either to
     constructor_elements or to the assembler file.  */

  constructor_elt celt = {field, value};
  vec_safe_push (constructor_elements, celt);

  /* Advance the variable that indicates sequential elements output.  */
  𐤀𐤌 (TREE_CODE (constructor_type) == ARRAY_TYPE)
    {
      tree inc = bitsize_one_node;
      𐤀𐤌 (value && TREE_CODE (value) == RAW_DATA_CST)
	inc = bitsize_int (RAW_DATA_LENGTH (value));
      constructor_unfilled_index
	= size_binop_loc (input_location, PLUS_EXPR,
			  constructor_unfilled_index, inc);
    }
  وإلا 𐤀𐤌 (TREE_CODE (constructor_type) == RECORD_TYPE)
    {
      constructor_unfilled_fields
	= DECL_CHAIN (constructor_unfilled_fields);

      /* Skip any nameless bit fields.  */
      طالما (constructor_unfilled_fields != NULL_TREE
	     && DECL_UNNAMED_BIT_FIELD (constructor_unfilled_fields))
	constructor_unfilled_fields
	  = DECL_CHAIN (constructor_unfilled_fields);
    }
  وإلا 𐤀𐤌 (TREE_CODE (constructor_type) == UNION_TYPE)
    constructor_unfilled_fields = NULL_TREE;

  /* Now output any pending elements which have become next.  */
  𐤀𐤌 (pending)
    output_pending_init_elements (0, braced_init_obstack);
}

/* For two FIELD_DECLs in the same chain, return -1 if field1
   comes before field2, 1 if field1 comes after field2 and
   0 if field1 == field2.  */

ساكن صحيح
init_field_decl_cmp (tree field1, tree field2)
{
  𐤀𐤌 (field1 == field2)
    أرجع 0;

  tree bitpos1 = bit_position (field1);
  tree bitpos2 = bit_position (field2);
  𐤀𐤌 (tree_int_cst_equal (bitpos1, bitpos2))
    {
      /* If one of the fields has non-zero bitsize, then that
	 field must be the last one in a sequence of zero
	 sized fields, fields after it will have bigger
	 bit_position.  */
      𐤀𐤌 (TREE_TYPE (field1) != error_mark_node
	  && COMPLETE_TYPE_P (TREE_TYPE (field1))
	  && integer_nonzerop (TREE_TYPE (field1)))
	أرجع 1;
      𐤀𐤌 (TREE_TYPE (field2) != error_mark_node
	  && COMPLETE_TYPE_P (TREE_TYPE (field2))
	  && integer_nonzerop (TREE_TYPE (field2)))
	أرجع -1;
      /* Otherwise, fallback to DECL_CHAIN walk to find out
	 which field comes earlier.  Walk chains of both
	 fields, so that if field1 and field2 are close to each
	 other in either order, it is found soon even for large
	 sequences of zero sized fields.  */
      tree f1 = field1, f2 = field2;
      طالما (1)
	{
	  f1 = DECL_CHAIN (f1);
	  f2 = DECL_CHAIN (f2);
	  𐤀𐤌 (f1 == NULL_TREE)
	    {
	      gcc_assert (f2);
	      أرجع 1;
	    }
	  𐤀𐤌 (f2 == NULL_TREE)
	    أرجع -1;
	  𐤀𐤌 (f1 == field2)
	    أرجع -1;
	  𐤀𐤌 (f2 == field1)
	    أرجع 1;
	  𐤀𐤌 (!tree_int_cst_equal (bit_position (f1), bitpos1))
	    أرجع 1;
	  𐤀𐤌 (!tree_int_cst_equal (bit_position (f2), bitpos1))
	    أرجع -1;
	}
    }
  وإلا 𐤀𐤌 (tree_int_cst_lt (bitpos1, bitpos2))
    أرجع -1;
  وإلا
    أرجع 1;
}

/* Output any pending elements which have become next.
   As we output elements, constructor_unfilled_{fields,index}
   advances, which may cause other elements to become next;
   if so, they too are output.

   If ALL is 0, we return when there are
   no more pending elements to output now.

   If ALL is 1, we output space as necessary so that
   we can output all the pending elements.  */
ساكن فراغ
output_pending_init_elements (صحيح all, بنية obstack * braced_init_obstack)
{
  بنية init_node *elt = constructor_pending_elts;
  tree next;

 retry:

  /* Look through the whole pending tree.
     If we find an element that should be output now,
     output it.  Otherwise, set NEXT to the element
     that comes first among those still pending.  */

  next = NULL_TREE;
  طالما (elt)
    {
      𐤀𐤌 (TREE_CODE (constructor_type) == ARRAY_TYPE)
	{
	  𐤀𐤌 (tree_int_cst_equal (elt->purpose,
				  constructor_unfilled_index))
	    output_init_element (input_location, elt->value, elt->origtype,
				 true, TREE_TYPE (constructor_type),
				 constructor_unfilled_index, خطأ, خطأ,
				 braced_init_obstack);
	  وإلا 𐤀𐤌 (tree_int_cst_lt (constructor_unfilled_index,
				    elt->purpose))
	    {
	      /* Advance to the next smaller node.  */
	      𐤀𐤌 (elt->left)
		elt = elt->left;
	      وإلا
		{
		  /* We have reached the smallest node bigger than the
		     current unfilled index.  Fill the space first.  */
		  next = elt->purpose;
		  اكسر;
		}
	    }
	  وإلا
	    {
	      /* Advance to the next bigger node.  */
	      𐤀𐤌 (elt->right)
		elt = elt->right;
	      وإلا
		{
		  /* We have reached the biggest node in a subtree.  Find
		     the parent of it, which is the next bigger node.  */
		  طالما (elt->parent && elt->parent->right == elt)
		    elt = elt->parent;
		  elt = elt->parent;
		  𐤀𐤌 (elt && tree_int_cst_lt (constructor_unfilled_index,
					      elt->purpose))
		    {
		      next = elt->purpose;
		      اكسر;
		    }
		}
	    }
	}
      وإلا 𐤀𐤌 (RECORD_OR_UNION_TYPE_P (constructor_type))
	{
	  /* If the current record is complete we are done.  */
	  𐤀𐤌 (constructor_unfilled_fields == NULL_TREE)
	    اكسر;

	  صحيح cmp = init_field_decl_cmp (constructor_unfilled_fields,
					 elt->purpose);
	  𐤀𐤌 (cmp == 0)
	    output_init_element (input_location, elt->value, elt->origtype,
				 true, TREE_TYPE (elt->purpose),
				 elt->purpose, خطأ, خطأ,
				 braced_init_obstack);
	  وإلا 𐤀𐤌 (cmp < 0)
	    {
	      /* Advance to the next smaller node.  */
	      𐤀𐤌 (elt->left)
		elt = elt->left;
	      وإلا
		{
		  /* We have reached the smallest node bigger than the
		     current unfilled field.  Fill the space first.  */
		  next = elt->purpose;
		  اكسر;
		}
	    }
	  وإلا
	    {
	      /* Advance to the next bigger node.  */
	      𐤀𐤌 (elt->right)
		elt = elt->right;
	      وإلا
		{
		  /* We have reached the biggest node in a subtree.  Find
		     the parent of it, which is the next bigger node.  */
		  طالما (elt->parent && elt->parent->right == elt)
		    elt = elt->parent;
		  elt = elt->parent;
		  𐤀𐤌 (elt
		      && init_field_decl_cmp (constructor_unfilled_fields,
					      elt->purpose) < 0)
		    {
		      next = elt->purpose;
		      اكسر;
		    }
		}
	    }
	}
    }

  /* Ordinarily return, but not if we want to output all
     and there are elements left.  */
  𐤀𐤌 (!(all && next != NULL_TREE))
    أرجع;

  /* If it's not incremental, just skip over the gap, so that after
     jumping to retry we will output the next successive element.  */
  𐤀𐤌 (RECORD_OR_UNION_TYPE_P (constructor_type))
    constructor_unfilled_fields = next;
  وإلا 𐤀𐤌 (TREE_CODE (constructor_type) == ARRAY_TYPE)
    constructor_unfilled_index = next;

  /* ELT now points to the node in the pending tree with the next
     initializer to output.  */
  اذهب retry;
}

/* Expression VALUE coincides with the start of type TYPE in a braced
   initializer.  Return true if we should treat VALUE as initializing
   the first element of TYPE, false if we should treat it as initializing
   TYPE as a whole.

   If the initializer is clearly invalid, the question becomes:
   which choice gives the best error message?  */

ساكن منطقي
initialize_elementwise_p (tree type, tree value)
{
  𐤀𐤌 (type == error_mark_node || value == error_mark_node)
    أرجع خطأ;

  gcc_checking_assert (TYPE_MAIN_VARIANT (type) == type);

  tree value_type = TREE_TYPE (value);
  𐤀𐤌 (value_type == error_mark_node)
    أرجع خطأ;

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
  𐤀𐤌 (gnu_vector_type_p (type))
    أرجع !VECTOR_TYPE_P (value_type);

  𐤀𐤌 (AGGREGATE_TYPE_P (type))
    أرجع !comptypes (type, TYPE_MAIN_VARIANT (value_type));

  أرجع خطأ;
}

/* Helper function for process_init_element.  Split first element of
   RAW_DATA_CST and save the rest to *RAW_DATA.  */

ساكن مضمن tree
maybe_split_raw_data (tree value, tree *raw_data)
{
  𐤀𐤌 (value == NULL_TREE || TREE_CODE (value) != RAW_DATA_CST)
    أرجع value;
  *raw_data = value;
  value = build_int_cst (integer_type_node,
			 RAW_DATA_UCHAR_ELT (*raw_data, 0));
  ++RAW_DATA_POINTER (*raw_data);
  --RAW_DATA_LENGTH (*raw_data);
  أرجع value;
}

/* Return non-zero if c_parser_initval should attempt to optimize
   large initializers into RAW_DATA_CST.  In that case return how
   many elements to optimize at most.  */

unsigned
c_maybe_optimize_large_byte_initializer (فراغ)
{
  𐤀𐤌 (!constructor_type
      || TREE_CODE (constructor_type) != ARRAY_TYPE
      || constructor_stack->implicit)
    أرجع 0;
  tree elttype = TYPE_MAIN_VARIANT (TREE_TYPE (constructor_type));
  𐤀𐤌 (TREE_CODE (elttype) != INTEGER_TYPE
      && TREE_CODE (elttype) != BITINT_TYPE)
    أرجع 0;
  𐤀𐤌 (TYPE_PRECISION (elttype) != CHAR_BIT
      || constructor_stack->replacement_value.value
      || (COMPLETE_TYPE_P (constructor_type)
	  && !poly_int_tree_p (TYPE_SIZE (constructor_type)))
      || constructor_range_stack)
    أرجع 0;
  𐤀𐤌 (constructor_max_index == NULL_TREE)
    أرجع INT_MAX;
  𐤀𐤌 (tree_int_cst_le (constructor_max_index, constructor_index)
      || integer_all_onesp (constructor_max_index))
    أرجع 0;
  widest_int w = wi::to_widest (constructor_max_index);
  w -= wi::to_widest (constructor_index);
  w += 1;
  𐤀𐤌 (w < 64)
    أرجع 0;
  𐤀𐤌 (w > INT_MAX)
    أرجع INT_MAX;
  أرجع w.to_uhwi ();
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

فراغ
process_init_element (location_t loc, بنية c_expr value, منطقي implicit,
		      بنية obstack * braced_init_obstack)
{
  tree orig_value = value.value;
  صحيح string_flag
    = (orig_value != NULL_TREE && TREE_CODE (orig_value) == STRING_CST);
  منطقي strict_string = value.original_code == STRING_CST;
  منطقي was_designated = designator_depth != 0;
  tree raw_data = NULL_TREE;

retry:
  designator_depth = 0;
  designator_erroneous = 0;

  𐤀𐤌 (!implicit && value.value && !integer_zerop (value.value))
    constructor_zeroinit = 0;

  /* Handle superfluous braces around string cst as in
     char x[] = {"foo"}; */
  𐤀𐤌 (constructor_type
      && !was_designated
      && TREE_CODE (constructor_type) == ARRAY_TYPE
      && INTEGRAL_TYPE_P (TREE_TYPE (constructor_type))
      && integer_zerop (constructor_unfilled_index))
    {
      𐤀𐤌 (constructor_stack->replacement_value.value)
	{
	  error_init (loc, "excess elements in %qT initializer", constructor_type);
	  أرجع;
	}
      وإلا 𐤀𐤌 (string_flag)
	{
	  constructor_stack->replacement_value = value;
	  أرجع;
	}
    }

  𐤀𐤌 (constructor_stack->replacement_value.value != NULL_TREE)
    {
      error_init (loc, "excess elements in struct initializer");
      أرجع;
    }

  /* Ignore elements of a brace group if it is entirely superfluous
     and has already been diagnosed, or if the type is erroneous.  */
  𐤀𐤌 (constructor_type == NULL_TREE || constructor_type == error_mark_node)
    أرجع;

  /* Ignore elements of an initializer for a variable-size type.
     Those are diagnosed in the parser (empty initializer braces are OK).  */
  𐤀𐤌 (COMPLETE_TYPE_P (constructor_type)
      && !poly_int_tree_p (TYPE_SIZE (constructor_type)))
    أرجع;

  𐤀𐤌 (!implicit && warn_designated_init && !was_designated
      && TREE_CODE (constructor_type) == RECORD_TYPE
      && lookup_attribute ("designated_init",
			   TYPE_ATTRIBUTES (constructor_type)))
    warning_init (loc,
		  OPT_Wdesignated_init,
		  "positional initialization of field "
		  "in %<struct%> declared with %<designated_init%> attribute");

  /* If we've exhausted any levels that didn't have braces,
     pop them now.  */
  طالما (constructor_stack->implicit)
    {
      𐤀𐤌 (RECORD_OR_UNION_TYPE_P (constructor_type)
	  && constructor_fields == NULL_TREE)
	process_init_element (loc,
			      pop_init_level (loc, 1, braced_init_obstack,
					      last_init_list_comma),
			      true, braced_init_obstack);
      وإلا 𐤀𐤌 ((TREE_CODE (constructor_type) == ARRAY_TYPE
		|| gnu_vector_type_p (constructor_type))
	       && constructor_max_index
	       && tree_int_cst_lt (constructor_max_index,
				   constructor_index))
	process_init_element (loc,
			      pop_init_level (loc, 1, braced_init_obstack,
					      last_init_list_comma),
			      true, braced_init_obstack);
      وإلا
	اكسر;
    }

  /* In the case of [LO ... HI] = VALUE, only evaluate VALUE once.  */
  𐤀𐤌 (constructor_range_stack)
    {
      /* If value is a compound literal and we'll be just using its
	 content, don't put it into a SAVE_EXPR.  */
      𐤀𐤌 (TREE_CODE (value.value) != COMPOUND_LITERAL_EXPR
	  || !require_constant_value)
	{
	  tree semantic_type = NULL_TREE;
	  𐤀𐤌 (TREE_CODE (value.value) == EXCESS_PRECISION_EXPR)
	    {
	      semantic_type = TREE_TYPE (value.value);
	      value.value = TREE_OPERAND (value.value, 0);
	    }
	  value.value = save_expr (value.value);
	  𐤀𐤌 (semantic_type)
	    value.value = build1 (EXCESS_PRECISION_EXPR, semantic_type,
				  value.value);
	}
    }

  طالما (1)
    {
      𐤀𐤌 (TREE_CODE (constructor_type) == RECORD_TYPE)
	{
	  tree fieldtype;
	  تعداد tree_code fieldcode;

	  𐤀𐤌 (constructor_fields == NULL_TREE)
	    {
	      pedwarn_init (loc, 0, "excess elements in struct initializer");
	      اكسر;
	    }

	  fieldtype = TREE_TYPE (constructor_fields);
	  𐤀𐤌 (fieldtype != error_mark_node)
	    fieldtype = TYPE_MAIN_VARIANT (fieldtype);
	  fieldcode = TREE_CODE (fieldtype);

	  /* Error for non-static initialization of a flexible array member.  */
	  𐤀𐤌 (fieldcode == ARRAY_TYPE
	      && !require_constant_value
	      && TYPE_SIZE (fieldtype) == NULL_TREE
	      && DECL_CHAIN (constructor_fields) == NULL_TREE)
	    {
	      error_init (loc, "non-static initialization of a flexible "
			  "array member");
	      اكسر;
	    }

	  /* Error for initialization of a flexible array member with
	     a string constant if the structure is in an array.  E.g.:
	     struct S { int x; char y[]; };
	     struct S s[] = { { 1, "foo" } };
	     is invalid.  */
	  𐤀𐤌 (string_flag
	      && fieldcode == ARRAY_TYPE
	      && constructor_depth > 1
	      && TYPE_SIZE (fieldtype) == NULL_TREE
	      && DECL_CHAIN (constructor_fields) == NULL_TREE)
	    {
	      منطقي in_array_p = خطأ;
	      لكل (بنية constructor_stack *p = constructor_stack;
		   p && p->type; p = p->next)
		𐤀𐤌 (TREE_CODE (p->type) == ARRAY_TYPE)
		  {
		    in_array_p = true;
		    اكسر;
		  }
	      𐤀𐤌 (in_array_p)
		{
		  error_init (loc, "initialization of flexible array "
			      "member in a nested context");
		  اكسر;
		}
	    }

	  /* Accept a string constant to initialize a subarray.  */
	  𐤀𐤌 (value.value != NULL_TREE
	      && fieldcode == ARRAY_TYPE
	      && INTEGRAL_TYPE_P (TREE_TYPE (fieldtype))
	      && string_flag)
	    value.value = orig_value;
	  /* Otherwise, if we have come to a subaggregate,
	     and we don't have an element of its type, push into it.  */
	  وإلا 𐤀𐤌 (value.value != NULL_TREE
		   && initialize_elementwise_p (fieldtype, value.value))
	    {
	      push_init_level (loc, 1, braced_init_obstack);
	      استمر;
	    }

	  value.value = maybe_split_raw_data (value.value, &raw_data);
	  𐤀𐤌 (value.value)
	    {
	      push_member_name (constructor_fields);
	      output_init_element (loc, value.value, value.original_type,
				   strict_string, fieldtype,
				   constructor_fields, true, implicit,
				   braced_init_obstack);
	      RESTORE_SPELLING_DEPTH (constructor_depth);
	    }
	  وإلا
	    /* Do the bookkeeping for an element that was
	       directly output as a constructor.  */
	    {
	      /* For a record, keep track of end position of last field.  */
	      𐤀𐤌 (DECL_SIZE (constructor_fields))
		constructor_bit_index
		  = size_binop_loc (input_location, PLUS_EXPR,
				    bit_position (constructor_fields),
				    DECL_SIZE (constructor_fields));

	      /* If the current field was the first one not yet written out,
		 it isn't now, so update.  */
	      𐤀𐤌 (constructor_unfilled_fields == constructor_fields)
		{
		  constructor_unfilled_fields = DECL_CHAIN (constructor_fields);
		  /* Skip any nameless bit fields.  */
		  طالما (constructor_unfilled_fields != 0
			 && (DECL_UNNAMED_BIT_FIELD
			     (constructor_unfilled_fields)))
		    constructor_unfilled_fields =
		      DECL_CHAIN (constructor_unfilled_fields);
		}
	    }

	  constructor_fields = DECL_CHAIN (constructor_fields);
	  /* Skip any nameless bit fields at the beginning.  */
	  طالما (constructor_fields != NULL_TREE
		 && DECL_UNNAMED_BIT_FIELD (constructor_fields))
	    constructor_fields = DECL_CHAIN (constructor_fields);
	}
      وإلا 𐤀𐤌 (TREE_CODE (constructor_type) == UNION_TYPE)
	{
	  tree fieldtype;
	  تعداد tree_code fieldcode;

	  𐤀𐤌 (constructor_fields == NULL_TREE)
	    {
	      pedwarn_init (loc, 0,
			    "excess elements in union initializer");
	      اكسر;
	    }

	  fieldtype = TREE_TYPE (constructor_fields);
	  𐤀𐤌 (fieldtype != error_mark_node)
	    fieldtype = TYPE_MAIN_VARIANT (fieldtype);
	  fieldcode = TREE_CODE (fieldtype);

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
	  𐤀𐤌 (!in_system_header_at (input_location) && !constructor_designated
	      && !(value.value && (integer_zerop (value.value)
				   || real_zerop (value.value))))
	    warning (OPT_Wtraditional, "traditional C rejects initialization "
		     "of unions");

	  /* Error for non-static initialization of a flexible array member.  */
	  𐤀𐤌 (fieldcode == ARRAY_TYPE
	      && !require_constant_value
	      && TYPE_SIZE (fieldtype) == NULL_TREE)
	    {
	      error_init (loc, "non-static initialization of a flexible "
			  "array member");
	      اكسر;
	    }

	  /* Error for initialization of a flexible array member with
	     a string constant if the structure is in an array.  E.g.:
	     union U { int x; char y[]; };
	     union U s[] = { { 1, "foo" } };
	     is invalid.  */
	  𐤀𐤌 (string_flag
	      && fieldcode == ARRAY_TYPE
	      && constructor_depth > 1
	      && TYPE_SIZE (fieldtype) == NULL_TREE)
	    {
	      منطقي in_array_p = خطأ;
	      لكل (بنية constructor_stack *p = constructor_stack;
		   p && p->type; p = p->next)
		𐤀𐤌 (TREE_CODE (p->type) == ARRAY_TYPE)
		  {
		    in_array_p = true;
		    اكسر;
		  }
	      𐤀𐤌 (in_array_p)
		{
		  error_init (loc, "initialization of flexible array "
			      "member in a nested context");
		  اكسر;
		}
	    }

	  /* Accept a string constant to initialize a subarray.  */
	  𐤀𐤌 (value.value != NULL_TREE
	      && fieldcode == ARRAY_TYPE
	      && INTEGRAL_TYPE_P (TREE_TYPE (fieldtype))
	      && string_flag)
	    value.value = orig_value;
	  /* Otherwise, if we have come to a subaggregate,
	     and we don't have an element of its type, push into it.  */
	  وإلا 𐤀𐤌 (value.value != NULL_TREE
		   && initialize_elementwise_p (fieldtype, value.value))
	    {
	      push_init_level (loc, 1, braced_init_obstack);
	      استمر;
	    }

	  value.value = maybe_split_raw_data (value.value, &raw_data);
	  𐤀𐤌 (value.value)
	    {
	      push_member_name (constructor_fields);
	      output_init_element (loc, value.value, value.original_type,
				   strict_string, fieldtype,
				   constructor_fields, true, implicit,
				   braced_init_obstack);
	      RESTORE_SPELLING_DEPTH (constructor_depth);
	    }
	  وإلا
	    /* Do the bookkeeping for an element that was
	       directly output as a constructor.  */
	    {
	      constructor_bit_index = DECL_SIZE (constructor_fields);
	      constructor_unfilled_fields = DECL_CHAIN (constructor_fields);
	    }

	  constructor_fields = NULL_TREE;
	}
      وإلا 𐤀𐤌 (TREE_CODE (constructor_type) == ARRAY_TYPE)
	{
	  tree elttype = TYPE_MAIN_VARIANT (TREE_TYPE (constructor_type));
	  تعداد tree_code eltcode = TREE_CODE (elttype);

	  /* Accept a string constant to initialize a subarray.  */
	  𐤀𐤌 (value.value != NULL_TREE
	      && eltcode == ARRAY_TYPE
	      && INTEGRAL_TYPE_P (TREE_TYPE (elttype))
	      && string_flag)
	    value.value = orig_value;
	  /* Otherwise, if we have come to a subaggregate,
	     and we don't have an element of its type, push into it.  */
	  وإلا 𐤀𐤌 (value.value != NULL_TREE
		   && initialize_elementwise_p (elttype, value.value))
	    {
	      push_init_level (loc, 1, braced_init_obstack);
	      استمر;
	    }

	  𐤀𐤌 (constructor_max_index != NULL_TREE
	      && (tree_int_cst_lt (constructor_max_index, constructor_index)
		  || integer_all_onesp (constructor_max_index))
	      /* For VLA we got an error already.  */
	      && !C_TYPE_VARIABLE_SIZE (constructor_type))
	    {
	      pedwarn_init (loc, 0,
			    "excess elements in array initializer");
	      اكسر;
	    }

	  𐤀𐤌 (value.value
	      && TREE_CODE (value.value) == RAW_DATA_CST
	      && RAW_DATA_LENGTH (value.value) > 1
	      && (TREE_CODE (elttype) == INTEGER_TYPE
		  || TREE_CODE (elttype) == BITINT_TYPE)
	      && TYPE_PRECISION (elttype) == CHAR_BIT
	      && (constructor_max_index == NULL_TREE
		  || tree_int_cst_lt (constructor_index,
				      constructor_max_index)))
	    {
	      unsigned صحيح len = RAW_DATA_LENGTH (value.value);
	      𐤀𐤌 (constructor_max_index)
		{
		  widest_int w = wi::to_widest (constructor_max_index);
		  w -= wi::to_widest (constructor_index);
		  w += 1;
		  𐤀𐤌 (w < len)
		    len = w.to_uhwi ();
		}
	      𐤀𐤌 (len < (unsigned) RAW_DATA_LENGTH (value.value))
		{
		  raw_data = copy_node (value.value);
		  RAW_DATA_LENGTH (raw_data) -= len;
		  RAW_DATA_POINTER (raw_data) += len;
		  RAW_DATA_LENGTH (value.value) = len;
		}
	      TREE_TYPE (value.value) = elttype;
	      push_array_bounds (tree_to_uhwi (constructor_index));
	      output_init_element (loc, value.value, value.original_type,
				   خطأ, elttype, constructor_index, true,
				   implicit, braced_init_obstack);
	      RESTORE_SPELLING_DEPTH (constructor_depth);
	      constructor_index
		= size_binop_loc (input_location, PLUS_EXPR,
				  constructor_index, bitsize_int (len));
	    }
	  وإلا
	    {
	      value.value = maybe_split_raw_data (value.value, &raw_data);
	      /* Now output the actual element.  */
	      𐤀𐤌 (value.value)
		{
		  push_array_bounds (tree_to_uhwi (constructor_index));
		  output_init_element (loc, value.value, value.original_type,
				       strict_string, elttype,
				       constructor_index, true, implicit,
				       braced_init_obstack);
		  RESTORE_SPELLING_DEPTH (constructor_depth);
		}

	      constructor_index
		= size_binop_loc (input_location, PLUS_EXPR,
				  constructor_index, bitsize_one_node);

	      𐤀𐤌 (!value.value)
		/* If we are doing the bookkeeping for an element that was
		   directly output as a constructor, we must update
		   constructor_unfilled_index.  */
		constructor_unfilled_index = constructor_index;
	    }
	}
      وإلا 𐤀𐤌 (gnu_vector_type_p (constructor_type))
	{
	  tree elttype = TYPE_MAIN_VARIANT (TREE_TYPE (constructor_type));

	  /* Do a basic check of initializer size.  Note that vectors
	     may not always have a fixed size derived from their type.  */
	  𐤀𐤌 (maybe_lt (tree_to_poly_uint64 (constructor_max_index),
			tree_to_poly_uint64 (constructor_index)))
	    {
	      /* Diagose VLA out-of-bounds as errors.  */
	      𐤀𐤌 (tree_to_poly_uint64 (constructor_max_index).is_constant())
		pedwarn_init (loc, 0,
			      "excess elements in vector initializer");
	      وإلا
		error_init (loc, "excess elements in vector initializer");

	      اكسر;
	    }

	  value.value = maybe_split_raw_data (value.value, &raw_data);
	  /* Now output the actual element.  */
	  𐤀𐤌 (value.value)
	    {
	      𐤀𐤌 (TREE_CODE (value.value) == VECTOR_CST)
		elttype = TYPE_MAIN_VARIANT (constructor_type);
	      output_init_element (loc, value.value, value.original_type,
				   strict_string, elttype,
				   constructor_index, true, implicit,
				   braced_init_obstack);
	    }

	  constructor_index
	    = size_binop_loc (input_location,
			      PLUS_EXPR, constructor_index, bitsize_one_node);

	  𐤀𐤌 (!value.value)
	    /* If we are doing the bookkeeping for an element that was
	       directly output as a constructor, we must update
	       constructor_unfilled_index.  */
	    constructor_unfilled_index = constructor_index;
	}

      /* Handle the sole element allowed in a braced initializer
	 for a scalar variable.  */
      وإلا 𐤀𐤌 (constructor_type != error_mark_node
	       && constructor_fields == NULL_TREE)
	{
	  pedwarn_init (loc, 0,
			"excess elements in scalar initializer");
	  اكسر;
	}
      وإلا
	{
	  value.value = maybe_split_raw_data (value.value, &raw_data);
	  𐤀𐤌 (value.value)
	    output_init_element (loc, value.value, value.original_type,
				 strict_string, constructor_type,
				 NULL_TREE, true, implicit,
				 braced_init_obstack);
	  constructor_fields = NULL_TREE;
	}

      /* Handle range initializers either at this level or anywhere higher
	 in the designator stack.  */
      𐤀𐤌 (constructor_range_stack)
	{
	  بنية constructor_range_stack *p, *range_stack;
	  صحيح finish = 0;

	  range_stack = constructor_range_stack;
	  constructor_range_stack = 0;
	  طالما (constructor_stack != range_stack->stack)
	    {
	      gcc_assert (constructor_stack->implicit);
	      process_init_element (loc,
				    pop_init_level (loc, 1,
						    braced_init_obstack,
						    last_init_list_comma),
				    true, braced_init_obstack);
	    }
	  لكل (p = range_stack;
	       !p->range_end || tree_int_cst_equal (p->index, p->range_end);
	       p = p->prev)
	    {
	      gcc_assert (constructor_stack->implicit);
	      process_init_element (loc,
				    pop_init_level (loc, 1,
						    braced_init_obstack,
						    last_init_list_comma),
				    true, braced_init_obstack);
	    }

	  p->index = size_binop_loc (input_location,
				     PLUS_EXPR, p->index, bitsize_one_node);
	  𐤀𐤌 (tree_int_cst_equal (p->index, p->range_end) && !p->prev)
	    finish = 1;

	  طالما (1)
	    {
	      constructor_index = p->index;
	      constructor_fields = p->fields;
	      𐤀𐤌 (finish && p->range_end && p->index == p->range_start)
		{
		  finish = 0;
		  p->prev = 0;
		}
	      p = p->next;
	      𐤀𐤌 (!p)
		اكسر;
	      finish_implicit_inits (loc, braced_init_obstack);
	      push_init_level (loc, 2, braced_init_obstack);
	      p->stack = constructor_stack;
	      𐤀𐤌 (p->range_end && tree_int_cst_equal (p->index, p->range_end))
		p->index = p->range_start;
	    }

	  𐤀𐤌 (!finish)
	    constructor_range_stack = range_stack;
	  استمر;
	}

      اكسر;
    }

  constructor_range_stack = 0;

  𐤀𐤌 (raw_data && RAW_DATA_LENGTH (raw_data))
    {
      gcc_assert (!string_flag && !was_designated);
      value.value = raw_data;
      raw_data = NULL_TREE;
      اذهب retry;
    }
}

/* Build a complete asm-statement, whose components are a CV_QUALIFIER
   (guaranteed to be 'volatile' or null) and ARGS (represented using
   an ASM_EXPR node).  */
tree
build_asm_stmt (منطقي is_volatile, tree args)
{
  𐤀𐤌 (is_volatile)
    ASM_VOLATILE_P (args) = 1;
  أرجع add_stmt (args);
}

/* Build an asm-expr, whose components are a STRING, some OUTPUTS,
   some INPUTS, and some CLOBBERS.  The latter three may be NULL.
   SIMPLE indicates whether there was anything at all after the
   string in the asm expression -- asm("blah") and asm("blah" : )
   are subtly different.  We use a ASM_EXPR node to represent this.
   LOC is the location of the asm, and IS_INLINE says whether this
   is asm inline.  */
tree
build_asm_expr (location_t loc, tree string, tree outputs, tree inputs,
		tree clobbers, tree labels, منطقي simple, منطقي is_inline)
{
  tree tail;
  tree args;
  صحيح i;
  ثابت حرف *constraint;
  ثابت حرف **oconstraints;
  منطقي allows_mem, allows_reg, is_inout;
  صحيح ninputs, noutputs;

  ninputs = list_length (inputs);
  noutputs = list_length (outputs);
  oconstraints = (ثابت حرف **) alloca (noutputs * حجم (ثابت حرف *));

  string = resolve_asm_operand_names (string, outputs, inputs, labels);

  /* Remove output conversions that change the type but not the mode.  */
  لكل (i = 0, tail = outputs; tail; ++i, tail = TREE_CHAIN (tail))
    {
      tree output = TREE_VALUE (tail);

      output = c_fully_fold (output, خطأ, عدم, true);

      /* ??? Really, this should not be here.  Users should be using a
	 proper lvalue, dammit.  But there's a long history of using casts
	 in the output operands.  In cases like longlong.h, this becomes a
	 primitive form of typechecking -- if the cast can be removed, then
	 the output operand had a type of the proper width; otherwise we'll
	 get an error.  Gross, but ...  */
      STRIP_NOPS (output);

      𐤀𐤌 (!lvalue_or_else (loc, output, lv_asm))
	output = error_mark_node;

      𐤀𐤌 (output != error_mark_node
	  && (TREE_READONLY (output)
	      || TYPE_READONLY (TREE_TYPE (output))
	      || (RECORD_OR_UNION_TYPE_P (TREE_TYPE (output))
		  && C_TYPE_FIELDS_READONLY (TREE_TYPE (output)))))
	readonly_error (loc, output, lv_asm);

      constraint = TREE_STRING_POINTER (TREE_VALUE (TREE_PURPOSE (tail)));
      oconstraints[i] = constraint;

      𐤀𐤌 (parse_output_constraint (&constraint, i, ninputs, noutputs,
				   &allows_mem, &allows_reg, &is_inout,
				   nullptr))
	{
	  /* If the operand is going to end up in memory,
	     mark it addressable.  */
	  𐤀𐤌 (!allows_reg && !c_mark_addressable (output))
	    output = error_mark_node;
	  𐤀𐤌 (!(!allows_reg && allows_mem)
	      && output != error_mark_node
	      && VOID_TYPE_P (TREE_TYPE (output)))
	    {
	      error_at (loc, "invalid use of void expression");
	      output = error_mark_node;
	    }
	  𐤀𐤌 (allows_reg && current_function_decl == NULL_TREE)
	    {
	      error_at (loc, "constraint allows registers outside of "
			     "a function");
	      output = error_mark_node;
	    }
	}
      وإلا
	output = error_mark_node;

      𐤀𐤌 (current_function_decl == NULL_TREE && output != error_mark_node)
	{
	  𐤀𐤌 (TREE_SIDE_EFFECTS (output))
	    {
	      error_at (loc, "side-effects in output operand outside "
			     "of a function");
	      output = error_mark_node;
	    }
	  وإلا
	    {
	      tree addr = build_unary_op (loc, ADDR_EXPR, output, خطأ);
	      𐤀𐤌 (addr == error_mark_node)
		output = error_mark_node;
	      وإلا 𐤀𐤌 (!initializer_constant_valid_p (addr, TREE_TYPE (addr)))
		{
		  error_at (loc, "output operand outside of a function is not "
				 "constant");
		  output = error_mark_node;
		}
	    }
	}
      وإلا 𐤀𐤌 (output != error_mark_node && strstr (constraint, "-"))
	{
	  error_at (loc, "%<-%> modifier used inside of a function");
	  output = error_mark_node;
	}

      TREE_VALUE (tail) = output;
    }

  لكل (i = 0, tail = inputs; tail; ++i, tail = TREE_CHAIN (tail))
    {
      tree input;

      constraint = TREE_STRING_POINTER (TREE_VALUE (TREE_PURPOSE (tail)));
      input = TREE_VALUE (tail);

      𐤀𐤌 (parse_input_constraint (&constraint, i, ninputs, noutputs, 0,
				  oconstraints, &allows_mem, &allows_reg,
				  nullptr))
	{
	  /* If the operand is going to end up in memory,
	     mark it addressable.  */
	  𐤀𐤌 (!allows_reg && allows_mem)
	    {
	      input = c_fully_fold (input, خطأ, عدم, true);

	      /* Strip the nops as we allow this case.  FIXME, this really
		 should be rejected or made deprecated.  */
	      STRIP_NOPS (input);
	      𐤀𐤌 (!c_mark_addressable (input))
		input = error_mark_node;
	    }
	  وإلا
	    {
	      input = c_fully_fold (convert_lvalue_to_rvalue (loc, input,
							      true, خطأ),
				    خطأ, عدم);

	      𐤀𐤌 (input != error_mark_node && VOID_TYPE_P (TREE_TYPE (input)))
		{
		  error_at (loc, "invalid use of void expression");
		  input = error_mark_node;
		}
	    }
	  𐤀𐤌 (allows_reg && current_function_decl == NULL_TREE)
	    {
	      error_at (loc, "constraint allows registers outside of "
			     "a function");
	      input = error_mark_node;
	    }
	  𐤀𐤌 (constraint[0] == ':' && input != error_mark_node)
	    {
	      tree t = input;
	      STRIP_NOPS (t);
	      𐤀𐤌 (TREE_CODE (t) != ADDR_EXPR
		  || !(TREE_CODE (TREE_OPERAND (t, 0)) == FUNCTION_DECL
		       || (VAR_P (TREE_OPERAND (t, 0))
			   && is_global_var (TREE_OPERAND (t, 0)))))
		{
		  error_at (loc, "%<:%> constraint operand is not address "
				 "of a function or non-automatic variable");
		  input = error_mark_node;
		}
	      وإلا 𐤀𐤌 (TREE_CODE (TREE_OPERAND (t, 0)) == FUNCTION_DECL)
		suppress_warning (TREE_OPERAND (t, 0), OPT_Wunused);
	    }
	}
      وإلا
	input = error_mark_node;

      𐤀𐤌 (current_function_decl == NULL_TREE && input != error_mark_node)
	{
	  𐤀𐤌 (TREE_SIDE_EFFECTS (input))
	    {
	      error_at (loc, "side-effects in input operand outside "
			     "of a function");
	      input = error_mark_node;
	    }
	  وإلا
	    {
	      tree tem = input;
	      𐤀𐤌 (allows_mem && lvalue_p (input))
		tem = build_unary_op (loc, ADDR_EXPR, input, خطأ);
	      𐤀𐤌 (!initializer_constant_valid_p (tem, TREE_TYPE (tem)))
		{
		  error_at (loc, "input operand outside of a function is not "
				 "constant");
		  input = error_mark_node;
		}
	    }
	}
      وإلا 𐤀𐤌 (input != error_mark_node && strstr (constraint, "-"))
	{
	  error_at (loc, "%<-%> modifier used inside of a function");
	  input = error_mark_node;
	}

      TREE_VALUE (tail) = input;
    }

  args = build_stmt (loc, ASM_EXPR, string, outputs, inputs, clobbers, labels);

  /* asm statements without outputs, including simple ones, are treated
     as volatile.  */
  ASM_BASIC_P (args) = simple;
  ASM_VOLATILE_P (args) = (noutputs == 0);
  ASM_INLINE_P (args) = is_inline;

  أرجع args;
}

/* Generate a goto statement to LABEL.  LOC is the location of the
   GOTO.  */

tree
c_finish_goto_label (location_t loc, tree label)
{
  tree decl = lookup_label_for_goto (loc, label);
  𐤀𐤌 (!decl)
    أرجع NULL_TREE;
  TREE_USED (decl) = 1;
  mark_decl_used (decl, خطأ);
  {
    add_stmt (build_predict_expr (PRED_GOTO, NOT_TAKEN));
    tree t = build1 (GOTO_EXPR, void_type_node, decl);
    SET_EXPR_LOCATION (t, loc);
    أرجع add_stmt (t);
  }
}

/* Generate a computed goto statement to EXPR.  LOC is the location of
   the GOTO.  */

tree
c_finish_goto_ptr (location_t loc, c_expr val)
{
  tree expr = val.value;
  tree t;
  pedwarn (loc, OPT_Wpedantic, "ISO C forbids %<goto *expr;%>");
  𐤀𐤌 (expr != error_mark_node
      && !POINTER_TYPE_P (TREE_TYPE (expr))
      && !null_pointer_constant_p (expr))
    {
      error_at (val.get_location (),
		"computed goto must be pointer type");
      expr = build_zero_cst (ptr_type_node);
    }
  expr = c_fully_fold (expr, خطأ, عدم);
  expr = convert (ptr_type_node, expr);
  t = build1 (GOTO_EXPR, void_type_node, expr);
  SET_EXPR_LOCATION (t, loc);
  أرجع add_stmt (t);
}

/* Generate a C `return' statement.  RETVAL is the expression for what
   to return, or a null pointer for `return;' with no value.  LOC is
   the location of the return statement, or the location of the expression,
   if the statement has any.  If ORIGTYPE is not NULL_TREE, it
   is the original type of RETVAL.  MUSTTAIL_P indicates a musttail
   attribute.  */

tree
c_finish_return (location_t loc, tree retval, tree origtype, منطقي musttail_p)
{
  tree valtype = TREE_TYPE (TREE_TYPE (current_function_decl)), ret_stmt;
  منطقي no_warning = خطأ;
  منطقي npc = خطأ;

  /* Use the expansion point to handle cases such as returning NULL
     in a function returning void.  */
  location_t xloc = expansion_point_location_if_in_system_header (loc);

  𐤀𐤌 (TREE_THIS_VOLATILE (current_function_decl))
    warning_at (xloc, 0,
		"function declared %<noreturn%> has a %<return%> statement");

  set_musttail_on_return (retval, xloc, musttail_p);

  𐤀𐤌 (retval)
    {
      tree semantic_type = NULL_TREE;
      npc = null_pointer_constant_p (retval);
      𐤀𐤌 (TREE_CODE (retval) == EXCESS_PRECISION_EXPR)
	{
	  semantic_type = TREE_TYPE (retval);
	  retval = TREE_OPERAND (retval, 0);
	}
      retval = c_fully_fold (retval, خطأ, عدم);
      𐤀𐤌 (semantic_type
	  && valtype != NULL_TREE
	  && TREE_CODE (valtype) != VOID_TYPE)
	retval = build1 (EXCESS_PRECISION_EXPR, semantic_type, retval);
    }

  𐤀𐤌 (!retval)
    {
      current_function_returns_null = 1;
      𐤀𐤌 ((warn_return_type >= 0 || flag_isoc99)
	  && valtype != NULL_TREE && TREE_CODE (valtype) != VOID_TYPE)
	{
	  no_warning = true;
	  𐤀𐤌 (emit_diagnostic (flag_isoc99
			       ? diagnostics::kind::permerror
			       : diagnostics::kind::warning,
			       loc, OPT_Wreturn_mismatch,
			       "%<return%> with no value,"
			       " in function returning non-void"))
	    inform (DECL_SOURCE_LOCATION (current_function_decl),
		    "declared here");
	}
    }
  وإلا 𐤀𐤌 (valtype == NULL_TREE || VOID_TYPE_P (valtype))
    {
      current_function_returns_null = 1;
      منطقي warned_here;
      𐤀𐤌 (TREE_CODE (TREE_TYPE (retval)) != VOID_TYPE)
	warned_here = permerror_opt
	  (xloc, OPT_Wreturn_mismatch,
	   "%<return%> with a value, in function returning void");
      وإلا
	warned_here = pedwarn
	  (xloc, OPT_Wpedantic, "ISO C forbids "
	   "%<return%> with expression, in function returning void");
      𐤀𐤌 (warned_here)
	inform (DECL_SOURCE_LOCATION (current_function_decl),
		"declared here");
    }
  وإلا
    {
      tree t = convert_for_assignment (loc, UNKNOWN_LOCATION, valtype,
				       retval, origtype, ic_return,
				       npc, NULL_TREE, NULL_TREE, 0);
      tree res = DECL_RESULT (current_function_decl);
      tree inner;
      منطقي save;

      current_function_returns_value = 1;
      𐤀𐤌 (t == error_mark_node)
	{
	  /* Suppress -Wreturn-type for this function.  */
	  𐤀𐤌 (warn_return_type)
	    suppress_warning (current_function_decl, OPT_Wreturn_type);
	  أرجع NULL_TREE;
	}

      save = in_late_binary_op;
      𐤀𐤌 (C_BOOLEAN_TYPE_P (TREE_TYPE (res))
	  || TREE_CODE (TREE_TYPE (res)) == COMPLEX_TYPE
	  || (SCALAR_FLOAT_TYPE_P (TREE_TYPE (t))
	      && (TREE_CODE (TREE_TYPE (res)) == INTEGER_TYPE
		  || TREE_CODE (TREE_TYPE (res)) == ENUMERAL_TYPE)
	      && sanitize_flags_p (SANITIZE_FLOAT_CAST)))
        in_late_binary_op = true;
      inner = t = convert (TREE_TYPE (res), t);
      in_late_binary_op = save;

      /* Strip any conversions, additions, and subtractions, and see if
	 we are returning the address of a local variable.  Warn if so.  */
      طالما (1)
	{
	  بدل (TREE_CODE (inner))
	    {
	    CASE_CONVERT:
	    حالة NON_LVALUE_EXPR:
	    حالة PLUS_EXPR:
	    حالة POINTER_PLUS_EXPR:
	      inner = TREE_OPERAND (inner, 0);
	      استمر;

	    حالة MINUS_EXPR:
	      /* If the second operand of the MINUS_EXPR has a pointer
		 type (or is converted from it), this may be valid, so
		 don't give a warning.  */
	      {
		tree op1 = TREE_OPERAND (inner, 1);

		طالما (!POINTER_TYPE_P (TREE_TYPE (op1))
		       && (CONVERT_EXPR_P (op1)
			   || TREE_CODE (op1) == NON_LVALUE_EXPR))
		  op1 = TREE_OPERAND (op1, 0);

		𐤀𐤌 (POINTER_TYPE_P (TREE_TYPE (op1)))
		  اكسر;

		inner = TREE_OPERAND (inner, 0);
		استمر;
	      }

	    حالة ADDR_EXPR:
	      inner = TREE_OPERAND (inner, 0);

	      طالما (REFERENCE_CLASS_P (inner)
		     && !INDIRECT_REF_P (inner))
		inner = TREE_OPERAND (inner, 0);

	      𐤀𐤌 (DECL_P (inner)
		  && !DECL_EXTERNAL (inner)
		  && DECL_CONTEXT (inner) == current_function_decl
		  && POINTER_TYPE_P (TREE_TYPE (TREE_TYPE (current_function_decl))))
		{
		  𐤀𐤌 (TREE_CODE (inner) == LABEL_DECL)
		    warning_at (loc, OPT_Wreturn_local_addr,
				"function returns address of label");
		  وإلا 𐤀𐤌 (TREE_CODE (inner) == FUNCTION_DECL
			   && (C_FUNC_NONLOCAL_CONTEXT (inner)
			       || !DECL_INITIAL (inner)))
		    warning_at (loc, OPT_Wreturn_local_addr,
				"function returns address of nested function "
				"referencing local context");
		  وإلا 𐤀𐤌 (TREE_CODE (inner) != FUNCTION_DECL
			   && !TREE_STATIC (inner))
		    {
		      warning_at (loc, OPT_Wreturn_local_addr,
				  "function returns address of local variable");
		      tree zero = build_zero_cst (TREE_TYPE (res));
		      t = build2 (COMPOUND_EXPR, TREE_TYPE (res), t, zero);
		    }
		}
	      اكسر;

	    افتراضي:
	      اكسر;
	    }

	  اكسر;
	}

      retval = build2 (MODIFY_EXPR, TREE_TYPE (res), res, t);
      SET_EXPR_LOCATION (retval, loc);

      𐤀𐤌 (warn_sequence_point)
	verify_sequence_points (retval);
    }

  ret_stmt = build_stmt (loc, RETURN_EXPR, retval);
  𐤀𐤌 (no_warning)
    suppress_warning (ret_stmt, OPT_Wreturn_type);
  أرجع add_stmt (ret_stmt);
}

بنية c_switch {
  /* The SWITCH_STMT being built.  */
  tree switch_stmt;

  /* The original type of the testing expression, i.e. before the
     default conversion is applied.  */
  tree orig_type;

  /* A splay-tree mapping the low element of a case range to the high
     element, or NULL_TREE if there is no high element.  Used to
     determine whether or not a new case label duplicates an old case
     label.  We need a tree, rather than simply a hash table, because
     of the GNU case range extension.  */
  splay_tree cases;

  /* The bindings at the point of the switch.  This is used for
     warnings crossing decls when branching to a case label.  */
  بنية c_spot_bindings *bindings;

  /* Whether the switch includes any break statements.  */
  منطقي break_stmt_seen_p;

  /* The next node on the stack.  */
  بنية c_switch *next;

  /* Remember whether the controlling expression had boolean type
     before integer promotions for the sake of -Wswitch-bool.  */
  منطقي bool_cond_p;
};

/* A stack of the currently active switch statements.  The innermost
   switch statement is on the top of the stack.  There is no need to
   mark the stack for garbage collection because it is only active
   during the processing of the body of a function, and we never
   collect at that point.  */

بنية c_switch *c_switch_stack;

/* Start a C switch statement, testing expression EXP.  Return the new
   SWITCH_STMT.  SWITCH_LOC is the location of the `switch'.
   SWITCH_COND_LOC is the location of the switch's condition.
   EXPLICIT_CAST_P is true if the expression EXP has an explicit cast.  */

tree
c_start_switch (location_t switch_loc,
		location_t switch_cond_loc,
		tree exp, منطقي explicit_cast_p, tree switch_name)
{
  tree orig_type = error_mark_node;
  منطقي bool_cond_p = خطأ;
  بنية c_switch *cs;

  𐤀𐤌 (exp != error_mark_node)
    {
      orig_type = TREE_TYPE (exp);

      𐤀𐤌 (!INTEGRAL_TYPE_P (orig_type))
	{
	  𐤀𐤌 (orig_type != error_mark_node)
	    {
	      error_at (switch_cond_loc, "switch quantity not an integer");
	      orig_type = error_mark_node;
	    }
	  exp = integer_zero_node;
	}
      وإلا
	{
	  tree type = TYPE_MAIN_VARIANT (orig_type);
	  tree e = exp;

	  /* Warn if the condition has boolean value.  */
	  طالما (TREE_CODE (e) == COMPOUND_EXPR)
	    e = TREE_OPERAND (e, 1);

	  𐤀𐤌 ((C_BOOLEAN_TYPE_P (type)
	       || truth_value_p (TREE_CODE (e)))
	      /* Explicit cast to int suppresses this warning.  */
	      && !(TREE_CODE (type) == INTEGER_TYPE
		   && explicit_cast_p))
	    bool_cond_p = true;

	  𐤀𐤌 (!in_system_header_at (input_location)
	      && (type == long_integer_type_node
		  || type == long_unsigned_type_node))
	    warning_at (switch_cond_loc,
			OPT_Wtraditional, "%<long%> switch expression not "
			"converted to %<int%> in ISO C");

	  exp = c_fully_fold (exp, خطأ, عدم);
	  exp = default_conversion (exp);

	  𐤀𐤌 (warn_sequence_point)
	    verify_sequence_points (exp);
	}
    }

  /* Add this new SWITCH_STMT to the stack.  */
  cs = XNEW (بنية c_switch);
  cs->switch_stmt = build_stmt (switch_loc, SWITCH_STMT, exp,
				NULL_TREE, orig_type, NULL_TREE, switch_name);
  cs->orig_type = orig_type;
  cs->cases = splay_tree_new (case_compare, عدم, عدم);
  cs->bindings = c_get_switch_bindings ();
  cs->break_stmt_seen_p = خطأ;
  cs->bool_cond_p = bool_cond_p;
  cs->next = c_switch_stack;
  c_switch_stack = cs;

  أرجع add_stmt (cs->switch_stmt);
}

/* Process a case label at location LOC, with attributes ATTRS.  */

tree
do_case (location_t loc, tree low_value, tree high_value, tree attrs)
{
  tree label = NULL_TREE;

  𐤀𐤌 (low_value && TREE_CODE (low_value) != INTEGER_CST)
    {
      low_value = c_fully_fold (low_value, خطأ, عدم);
      𐤀𐤌 (TREE_CODE (low_value) == INTEGER_CST)
	pedwarn (loc, OPT_Wpedantic,
		 "case label is not an integer constant expression");
    }

  𐤀𐤌 (high_value && TREE_CODE (high_value) != INTEGER_CST)
    {
      high_value = c_fully_fold (high_value, خطأ, عدم);
      𐤀𐤌 (TREE_CODE (high_value) == INTEGER_CST)
	pedwarn (input_location, OPT_Wpedantic,
		 "case label is not an integer constant expression");
    }

  𐤀𐤌 (c_switch_stack == عدم)
    {
      𐤀𐤌 (low_value)
	error_at (loc, "case label not within a switch statement");
      وإلا
	error_at (loc, "%<default%> label not within a switch statement");
      أرجع NULL_TREE;
    }

  𐤀𐤌 (c_check_switch_jump_warnings (c_switch_stack->bindings,
				    EXPR_LOCATION (c_switch_stack->switch_stmt),
				    loc))
    أرجع NULL_TREE;

  label = c_add_case_label (loc, c_switch_stack->cases,
			    SWITCH_STMT_COND (c_switch_stack->switch_stmt),
			    low_value, high_value, attrs);
  𐤀𐤌 (label == error_mark_node)
    label = NULL_TREE;
  أرجع label;
}

/* Finish the switch statement.  TYPE is the original type of the
   controlling expression of the switch, or NULL_TREE.  */

فراغ
c_finish_switch (tree body, tree type)
{
  بنية c_switch *cs = c_switch_stack;
  location_t switch_location;

  SWITCH_STMT_BODY (cs->switch_stmt) = body;

  /* Emit warnings as needed.  */
  switch_location = EXPR_LOCATION (cs->switch_stmt);
  c_do_switch_warnings (cs->cases, switch_location,
			type ? type : SWITCH_STMT_TYPE (cs->switch_stmt),
			SWITCH_STMT_COND (cs->switch_stmt), cs->bool_cond_p);
  𐤀𐤌 (c_switch_covers_all_cases_p (cs->cases,
				   SWITCH_STMT_TYPE (cs->switch_stmt)))
    SWITCH_STMT_ALL_CASES_P (cs->switch_stmt) = 1;
  SWITCH_STMT_NO_BREAK_P (cs->switch_stmt) = !cs->break_stmt_seen_p;

  /* Pop the stack.  */
  c_switch_stack = cs->next;
  splay_tree_delete (cs->cases);
  c_release_switch_bindings (cs->bindings);
  XDELETE (cs);
}

/* Emit an if statement.  IF_LOCUS is the location of the 'if'.  COND,
   THEN_BLOCK and ELSE_BLOCK are expressions to be used; ELSE_BLOCK
   may be null.  */

فراغ
c_finish_if_stmt (location_t if_locus, tree cond, tree then_block,
		  tree else_block)
{
  tree stmt;

  stmt = build3 (COND_EXPR, void_type_node, cond, then_block, else_block);
  SET_EXPR_LOCATION (stmt, if_locus);
  add_stmt (stmt);
}

tree
c_finish_bc_stmt (location_t loc, tree label, منطقي is_break, tree name)
{
  /* In switch statements break is sometimes stylistically used after
     a return statement.  This can lead to spurious warnings about
     control reaching the end of a non-void function when it is
     inlined.  Note that we are calling block_may_fallthru with
     language specific tree nodes; this works because
     block_may_fallthru returns true when given something it does not
     understand.  */
  منطقي skip = !block_may_fallthru (cur_stmt_list);

  𐤀𐤌 (is_break)
    بدل (in_statement & ~IN_NAMED_STMT)
      {
      حالة 0:
	error_at (loc, "break statement not within loop or switch");
	أرجع NULL_TREE;
      حالة IN_OMP_BLOCK:
	error_at (loc, "invalid exit from OpenMP structured block");
	أرجع NULL_TREE;
      حالة IN_OMP_FOR:
	error_at (loc, "break statement used with OpenMP for loop");
	أرجع NULL_TREE;
      حالة IN_ITERATION_STMT:
      حالة IN_OBJC_FOREACH:
	اكسر;
      افتراضي:
	gcc_assert (in_statement & IN_SWITCH_STMT);
	c_switch_stack->break_stmt_seen_p = true;
	اكسر;
      }
  وإلا
    بدل (in_statement & ~(IN_SWITCH_STMT | IN_NAMED_STMT))
      {
      حالة 0:
	error_at (loc, "continue statement not within a loop");
	أرجع NULL_TREE;
      حالة IN_OMP_BLOCK:
	error_at (loc, "invalid exit from OpenMP structured block");
	أرجع NULL_TREE;
      حالة IN_ITERATION_STMT:
      حالة IN_OMP_FOR:
      حالة IN_OBJC_FOREACH:
	اكسر;
      افتراضي:
	gcc_unreachable ();
      }

  𐤀𐤌 (skip)
    أرجع NULL_TREE;
  وإلا 𐤀𐤌 ((in_statement & IN_OBJC_FOREACH)
	   && !(is_break && (in_statement & IN_SWITCH_STMT))
	   && name == NULL_TREE)
    {
      /* The foreach expander produces low-level code using gotos instead
	 of a structured loop construct.  */
      gcc_assert (label);
      أرجع add_stmt (build_stmt (loc, GOTO_EXPR, label));
    }
  وإلا 𐤀𐤌 (name && C_DECL_LOOP_NAME (name) && C_DECL_SWITCH_NAME (name))
    {
      label = DECL_CHAIN (name);
      𐤀𐤌 (!is_break)
	label = DECL_CHAIN (label);
      /* Foreach expander from some outer level.  */
      أرجع add_stmt (build_stmt (loc, GOTO_EXPR, label));
    }
  أرجع add_stmt (build_stmt (loc, is_break ? BREAK_STMT : CONTINUE_STMT,
			       name));
}

/* A helper routine for c_process_expr_stmt and c_finish_stmt_expr.  */

ساكن فراغ
emit_side_effect_warnings (location_t loc, tree expr)
{
  maybe_warn_nodiscard (loc, expr);
  𐤀𐤌 (!warn_unused_value)
    أرجع;
  𐤀𐤌 (expr == error_mark_node)
    ;
  وإلا 𐤀𐤌 (!TREE_SIDE_EFFECTS (expr))
    {
      𐤀𐤌 (!VOID_TYPE_P (TREE_TYPE (expr))
	  && !warning_suppressed_p (expr, OPT_Wunused_value))
	warning_at (loc, OPT_Wunused_value, "statement with no effect");
    }
  وإلا 𐤀𐤌 (TREE_CODE (expr) == COMPOUND_EXPR)
    {
      tree r = expr;
      location_t cloc = loc;
      طالما (TREE_CODE (r) == COMPOUND_EXPR)
	{
	  𐤀𐤌 (EXPR_HAS_LOCATION (r))
	    cloc = EXPR_LOCATION (r);
	  r = TREE_OPERAND (r, 1);
	}
      𐤀𐤌 (!TREE_SIDE_EFFECTS (r)
	  && !VOID_TYPE_P (TREE_TYPE (r))
	  && !CONVERT_EXPR_P (r)
	  && !warning_suppressed_p (r, OPT_Wunused_value)
	  && !warning_suppressed_p (expr, OPT_Wunused_value))
	warning_at (cloc, OPT_Wunused_value,
		    "right-hand operand of comma expression has no effect");
    }
  وإلا
    warn_if_unused_value (expr, loc);
}

/* Process an expression as if it were a complete statement.  Emit
   diagnostics, but do not call ADD_STMT.  LOC is the location of the
   statement.  */

tree
c_process_expr_stmt (location_t loc, tree expr)
{
  tree exprv;

  𐤀𐤌 (!expr)
    أرجع NULL_TREE;

  expr = c_fully_fold (expr, خطأ, عدم);

  𐤀𐤌 (warn_sequence_point)
    verify_sequence_points (expr);

  𐤀𐤌 (TREE_TYPE (expr) != error_mark_node
      && !COMPLETE_OR_VOID_TYPE_P (TREE_TYPE (expr))
      && TREE_CODE (TREE_TYPE (expr)) != ARRAY_TYPE)
    error_at (loc, "expression statement has incomplete type");

  /* If we're not processing a statement expression, warn about unused values.
     Warnings for statement expressions will be emitted later, once we figure
     out which is the result.  */
  𐤀𐤌 (!STATEMENT_LIST_STMT_EXPR (cur_stmt_list)
      && (warn_unused_value || warn_unused_result))
    emit_side_effect_warnings (EXPR_LOC_OR_LOC (expr, loc), expr);

  exprv = expr;
  طالما (TREE_CODE (exprv) == COMPOUND_EXPR)
    exprv = TREE_OPERAND (exprv, 1);
  طالما (CONVERT_EXPR_P (exprv))
    exprv = TREE_OPERAND (exprv, 0);
  𐤀𐤌 (DECL_P (exprv)
      || handled_component_p (exprv)
      || TREE_CODE (exprv) == ADDR_EXPR)
    mark_exp_read (exprv);

  /* If the expression is not of a type to which we cannot assign a line
     number, wrap the thing in a no-op NOP_EXPR.  */
  𐤀𐤌 (DECL_P (expr) || CONSTANT_CLASS_P (expr))
    {
      expr = build1 (NOP_EXPR, TREE_TYPE (expr), expr);
      SET_EXPR_LOCATION (expr, loc);
    }

  أرجع expr;
}

/* Emit an expression as a statement.  LOC is the location of the
   expression.  */

tree
c_finish_expr_stmt (location_t loc, tree expr)
{
  𐤀𐤌 (expr)
    أرجع add_stmt (c_process_expr_stmt (loc, expr));
  وإلا
    أرجع عدم;
}

/* Do the opposite and emit a statement as an expression.  To begin,
   create a new binding level and return it.  */

tree
c_begin_stmt_expr (فراغ)
{
  tree ret;

  /* We must force a BLOCK for this level so that, if it is not expanded
     later, there is a way to turn off the entire subtree of blocks that
     are contained in it.  */
  keep_next_level ();
  ret = c_begin_compound_stmt (true);

  c_bindings_start_stmt_expr (c_switch_stack == عدم
			      ? عدم
			      : c_switch_stack->bindings);

  /* Mark the current statement list as belonging to a statement list.  */
  STATEMENT_LIST_STMT_EXPR (ret) = 1;

  أرجع ret;
}

/* LOC is the location of the compound statement to which this body
   belongs.  */

tree
c_finish_stmt_expr (location_t loc, tree body)
{
  tree last, type, tmp, val;
  tree *last_p;

  body = c_end_compound_stmt (loc, body, true);

  c_bindings_end_stmt_expr (c_switch_stack == عدم
			    ? عدم
			    : c_switch_stack->bindings);

  /* Locate the last statement in BODY.  See c_end_compound_stmt
     about always returning a BIND_EXPR.  */
  last_p = &BIND_EXPR_BODY (body);
  last = BIND_EXPR_BODY (body);

 continue_searching:
  𐤀𐤌 (TREE_CODE (last) == STATEMENT_LIST)
    {
      tree_stmt_iterator l = tsi_last (last);

      طالما (!tsi_end_p (l) && TREE_CODE (tsi_stmt (l)) == DEBUG_BEGIN_STMT)
	tsi_prev (&l);

      /* This can happen with degenerate cases like ({ }).  No value.  */
      𐤀𐤌 (tsi_end_p (l))
	أرجع body;

      /* If we're supposed to generate side effects warnings, process
	 all of the statements except the last.  */
      𐤀𐤌 (warn_unused_value || warn_unused_result)
	{
	  لكل (tree_stmt_iterator i = tsi_start (last);
	       tsi_stmt (i) != tsi_stmt (l); tsi_next (&i))
	    {
	      location_t tloc;
	      tree t = tsi_stmt (i);

	      tloc = EXPR_HAS_LOCATION (t) ? EXPR_LOCATION (t) : loc;
	      emit_side_effect_warnings (tloc, t);
	    }
	}
      last_p = tsi_stmt_ptr (l);
      last = *last_p;
    }

  /* If the end of the list is exception related, then the list was split
     by a call to push_cleanup.  Continue searching.  */
  𐤀𐤌 (TREE_CODE (last) == TRY_FINALLY_EXPR
      || TREE_CODE (last) == TRY_CATCH_EXPR)
    {
      last_p = &TREE_OPERAND (last, 0);
      last = *last_p;
      اذهب continue_searching;
    }

  𐤀𐤌 (last == error_mark_node)
    أرجع last;

  /* In the case that the BIND_EXPR is not necessary, return the
     expression out from inside it.  */
  𐤀𐤌 ((last == BIND_EXPR_BODY (body)
       /* Skip nested debug stmts.  */
       || last == expr_first (BIND_EXPR_BODY (body)))
      && BIND_EXPR_VARS (body) == عدم)
    {
      /* Even if this looks constant, do not allow it in a constant
	 expression.  */
      last = c_wrap_maybe_const (last, true);
      /* Do not warn if the return value of a statement expression is
	 unused.  */
      suppress_warning (last, OPT_Wunused);
      أرجع last;
    }

  /* Extract the type of said expression.  */
  type = TREE_TYPE (last);

  /* If we're not returning a value at all, then the BIND_EXPR that
     we already have is a fine expression to return.  */
  𐤀𐤌 (!type || VOID_TYPE_P (type))
    أرجع body;

  /* Now that we've located the expression containing the value, it seems
     silly to make voidify_wrapper_expr repeat the process.  Create a
     temporary of the appropriate type and stick it in a TARGET_EXPR.  */
  tmp = create_tmp_var_raw (type);

  /* Unwrap a no-op NOP_EXPR as added by c_finish_expr_stmt.  This avoids
     tree_expr_nonnegative_p giving up immediately.  */
  val = last;
  𐤀𐤌 (TREE_CODE (val) == NOP_EXPR
      && TREE_TYPE (val) == TREE_TYPE (TREE_OPERAND (val, 0)))
    val = TREE_OPERAND (val, 0);

  *last_p = build2 (MODIFY_EXPR, void_type_node, tmp, val);
  SET_EXPR_LOCATION (*last_p, EXPR_LOCATION (last));

  {
    tree t = build4 (TARGET_EXPR, type, tmp, body, NULL_TREE, NULL_TREE);
    SET_EXPR_LOCATION (t, loc);
    أرجع t;
  }
}

/* Begin and end compound statements.  This is as simple as pushing
   and popping new statement lists from the tree.  */

tree
c_begin_compound_stmt (منطقي do_scope)
{
  tree stmt = push_stmt_list ();
  𐤀𐤌 (do_scope)
    push_scope ();
  أرجع stmt;
}

/* End a compound statement.  STMT is the statement.  LOC is the
   location of the compound statement-- this is usually the location
   of the opening brace.  */

tree
c_end_compound_stmt (location_t loc, tree stmt, منطقي do_scope)
{
  tree block = عدم;

  𐤀𐤌 (do_scope)
    {
      𐤀𐤌 (c_dialect_objc ())
	objc_clear_super_receiver ();
      block = pop_scope ();
    }

  stmt = pop_stmt_list (stmt);
  stmt = c_build_bind_expr (loc, block, stmt);

  /* If this compound statement is nested immediately inside a statement
     expression, then force a BIND_EXPR to be created.  Otherwise we'll
     do the wrong thing for ({ { 1; } }) or ({ 1; { } }).  In particular,
     STATEMENT_LISTs merge, and thus we can lose track of what statement
     was really last.  */
  𐤀𐤌 (building_stmt_list_p ()
      && STATEMENT_LIST_STMT_EXPR (cur_stmt_list)
      && TREE_CODE (stmt) != BIND_EXPR)
    {
      stmt = build3 (BIND_EXPR, void_type_node, عدم, stmt, عدم);
      TREE_SIDE_EFFECTS (stmt) = 1;
      SET_EXPR_LOCATION (stmt, loc);
    }

  أرجع stmt;
}

/* Queue a cleanup.  CLEANUP is an expression/statement to be executed
   when the current scope is exited.  EH_ONLY is true when this is not
   meant to apply to normal control flow transfer.  */

فراغ
push_cleanup (tree decl, tree cleanup, منطقي eh_only)
{
  تعداد tree_code code;
  tree stmt, list;
  منطقي stmt_expr;

  code = eh_only ? TRY_CATCH_EXPR : TRY_FINALLY_EXPR;
  stmt = build_stmt (DECL_SOURCE_LOCATION (decl), code, عدم, cleanup);
  add_stmt (stmt);
  stmt_expr = STATEMENT_LIST_STMT_EXPR (cur_stmt_list);
  list = push_stmt_list ();
  TREE_OPERAND (stmt, 0) = list;
  STATEMENT_LIST_STMT_EXPR (list) = stmt_expr;
}

/* Build a vector comparison of ARG0 and ARG1 using CODE opcode
   into a value of TYPE type.  Comparison is done via VEC_COND_EXPR.  */

ساكن tree
build_vec_cmp (tree_code code, tree type,
	       tree arg0, tree arg1)
{
  tree zero_vec = build_zero_cst (type);
  tree minus_one_vec = build_minus_one_cst (type);
  tree cmp_type = truth_type_for (TREE_TYPE (arg0));
  tree cmp = build2 (code, cmp_type, arg0, arg1);
  أرجع build3 (VEC_COND_EXPR, type, cmp, minus_one_vec, zero_vec);
}

/* Possibly warn about an address of OP never being NULL in a comparison
   operation CODE involving null.  */

ساكن فراغ
maybe_warn_for_null_address (location_t loc, tree op, tree_code code)
{
  /* Prevent warnings issued for macro expansion.  */
  𐤀𐤌 (!warn_address
      || warning_suppressed_p (op, OPT_Waddress)
      || from_macro_expansion_at (loc))
    أرجع;

  𐤀𐤌 (TREE_CODE (op) == NOP_EXPR)
    {
      /* Allow casts to intptr_t to suppress the warning.  */
      tree type = TREE_TYPE (op);
      𐤀𐤌 (TREE_CODE (type) == INTEGER_TYPE)
	أرجع;
      op = TREE_OPERAND (op, 0);
    }

  𐤀𐤌 (TREE_CODE (op) == POINTER_PLUS_EXPR)
    {
      /* Allow a cast to void* to suppress the warning.  */
      tree type = TREE_TYPE (TREE_TYPE (op));
      𐤀𐤌 (VOID_TYPE_P (type))
	أرجع;

      /* Adding any value to a null pointer, including zero, is undefined
	 in C.  This includes the expression &p[0] where p is the null
	 pointer, although &p[0] will have been folded to p by this point
	 and so not diagnosed.  */
      𐤀𐤌 (code == EQ_EXPR)
	warning_at (loc, OPT_Waddress,
		    "the comparison will always evaluate as %<false%> "
		    "for the pointer operand in %qE must not be NULL",
		    op);
      وإلا
	warning_at (loc, OPT_Waddress,
		    "the comparison will always evaluate as %<true%> "
		    "for the pointer operand in %qE must not be NULL",
		    op);

      أرجع;
    }

  𐤀𐤌 (TREE_CODE (op) != ADDR_EXPR)
    أرجع;

  op = TREE_OPERAND (op, 0);

  𐤀𐤌 (TREE_CODE (op) == IMAGPART_EXPR
      || TREE_CODE (op) == REALPART_EXPR)
    {
      /* The address of either complex part may not be null.  */
      𐤀𐤌 (code == EQ_EXPR)
	warning_at (loc, OPT_Waddress,
		    "the comparison will always evaluate as %<false%> "
		    "for the address of %qE will never be NULL",
		    op);
      وإلا
	warning_at (loc, OPT_Waddress,
		    "the comparison will always evaluate as %<true%> "
		    "for the address of %qE will never be NULL",
		    op);
      أرجع;
    }

  /* Set to true in the loop below if OP dereferences is operand.
     In such a case the ultimate target need not be a decl for
     the null [in]equality test to be constant.  */
  منطقي deref = خطأ;

  /* Get the outermost array or object, or member.  */
  طالما (handled_component_p (op))
    {
      𐤀𐤌 (TREE_CODE (op) == COMPONENT_REF)
	{
	  /* Get the member (its address is never null).  */
	  op = TREE_OPERAND (op, 1);
	  اكسر;
	}

      /* Get the outer array/object to refer to in the warning.  */
      op = TREE_OPERAND (op, 0);
      deref = true;
    }

  𐤀𐤌 ((!deref && !decl_with_nonnull_addr_p (op))
      || from_macro_expansion_at (loc))
    أرجع;

  منطقي w;
  𐤀𐤌 (code == EQ_EXPR)
    w = warning_at (loc, OPT_Waddress,
		    "the comparison will always evaluate as %<false%> "
		    "for the address of %qE will never be NULL",
		    op);
  وإلا
    w = warning_at (loc, OPT_Waddress,
		    "the comparison will always evaluate as %<true%> "
		    "for the address of %qE will never be NULL",
		    op);

  𐤀𐤌 (w && DECL_P (op))
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

tree
build_binary_op (location_t location, تعداد tree_code code,
		 tree orig_op0, tree orig_op1, منطقي convert_p)
{
  tree type0, type1, orig_type0, orig_type1;
  tree eptype;
  تعداد tree_code code0, code1;
  tree op0, op1;
  tree ret = error_mark_node;
  ثابت حرف *invalid_op_diag;
  منطقي op0_int_operands, op1_int_operands;
  منطقي int_const, int_const_or_overflow, int_operands;

  /* Expression code to give to the expression when it is built.
     Normally this is CODE, which is what the caller asked for,
     but in some special cases we change it.  */
  تعداد tree_code resultcode = code;

  /* Data type in which the computation is to be performed.
     In the simplest cases this is the common type of the arguments.  */
  tree result_type = عدم;

  /* When the computation is in excess precision, the type of the
     final EXCESS_PRECISION_EXPR.  */
  tree semantic_result_type = عدم;

  /* Nonzero means operands have already been type-converted
     in whatever way is necessary.
     Zero means they need to be converted to RESULT_TYPE.  */
  صحيح converted = 0;

  /* Nonzero means create the expression with this type, rather than
     RESULT_TYPE.  */
  tree build_type = NULL_TREE;

  /* Nonzero means after finally constructing the expression
     convert it to this type.  */
  tree final_type = NULL_TREE;

  /* Nonzero if this is an operation like MIN or MAX which can
     safely be computed in short if both args are promoted shorts.
     Also implies COMMON.
     -1 indicates a bitwise operation; this makes a difference
     in the exact conditions for when it is safe to do the operation
     in a narrower mode.  */
  صحيح shorten = 0;

  /* Nonzero if this is a comparison operation;
     if both args are promoted shorts, compare the original shorts.
     Also implies COMMON.  */
  صحيح short_compare = 0;

  /* Nonzero if this is a right-shift operation, which can be computed on the
     original short and then promoted if the operand is a promoted short.  */
  صحيح short_shift = 0;

  /* Nonzero means set RESULT_TYPE to the common type of the args.  */
  صحيح common = 0;

  /* True means types are compatible as far as ObjC is concerned.  */
  منطقي objc_ok;

  /* True means this is an arithmetic operation that may need excess
     precision.  */
  منطقي may_need_excess_precision;

  /* True means this is a boolean operation that converts both its
     operands to truth-values.  */
  منطقي boolean_op = خطأ;

  /* Remember whether we're doing / or %.  */
  منطقي doing_div_or_mod = خطأ;

  /* Remember whether we're doing << or >>.  */
  منطقي doing_shift = خطأ;

  /* Tree holding instrumentation expression.  */
  tree instrument_expr = عدم;

  𐤀𐤌 (location == UNKNOWN_LOCATION)
    location = input_location;

  op0 = orig_op0;
  op1 = orig_op1;

  op0_int_operands = EXPR_INT_CONST_OPERANDS (orig_op0);
  𐤀𐤌 (op0_int_operands)
    op0 = remove_c_maybe_const_expr (op0);
  op1_int_operands = EXPR_INT_CONST_OPERANDS (orig_op1);
  𐤀𐤌 (op1_int_operands)
    op1 = remove_c_maybe_const_expr (op1);
  int_operands = (op0_int_operands && op1_int_operands);
  𐤀𐤌 (int_operands)
    {
      int_const_or_overflow = (TREE_CODE (orig_op0) == INTEGER_CST
			       && TREE_CODE (orig_op1) == INTEGER_CST);
      int_const = (int_const_or_overflow
		   && !TREE_OVERFLOW (orig_op0)
		   && !TREE_OVERFLOW (orig_op1));
    }
  وإلا
    int_const = int_const_or_overflow = خطأ;

  /* Do not apply default conversion in mixed vector/scalar expression.  */
  𐤀𐤌 (convert_p
      && VECTOR_TYPE_P (TREE_TYPE (op0)) == VECTOR_TYPE_P (TREE_TYPE (op1)))
    {
      op0 = default_conversion (op0);
      op1 = default_conversion (op1);
    }

  orig_type0 = type0 = TREE_TYPE (op0);

  orig_type1 = type1 = TREE_TYPE (op1);

  /* The expression codes of the data types of the arguments tell us
     whether the arguments are integers, floating, pointers, etc.  */
  code0 = TREE_CODE (type0);
  code1 = TREE_CODE (type1);

  /* Strip NON_LVALUE_EXPRs, etc., since we aren't using as an lvalue.  */
  STRIP_TYPE_NOPS (op0);
  STRIP_TYPE_NOPS (op1);

  /* If an error was already reported for one of the arguments,
     avoid reporting another error.  */

  𐤀𐤌 (code0 == ERROR_MARK || code1 == ERROR_MARK)
    أرجع error_mark_node;

  𐤀𐤌 (code0 == POINTER_TYPE
      && reject_gcc_builtin (op0, EXPR_LOCATION (orig_op0)))
    أرجع error_mark_node;

  𐤀𐤌 (code1 == POINTER_TYPE
      && reject_gcc_builtin (op1, EXPR_LOCATION (orig_op1)))
    أرجع error_mark_node;

  𐤀𐤌 ((invalid_op_diag
       = targetm.invalid_binary_op (code, type0, type1)))
    {
      error_at (location, invalid_op_diag);
      أرجع error_mark_node;
    }

  بدل (code)
    {
    حالة PLUS_EXPR:
    حالة MINUS_EXPR:
    حالة MULT_EXPR:
    حالة TRUNC_DIV_EXPR:
    حالة CEIL_DIV_EXPR:
    حالة FLOOR_DIV_EXPR:
    حالة ROUND_DIV_EXPR:
    حالة EXACT_DIV_EXPR:
      may_need_excess_precision = true;
      اكسر;

    حالة EQ_EXPR:
    حالة NE_EXPR:
    حالة LE_EXPR:
    حالة GE_EXPR:
    حالة LT_EXPR:
    حالة GT_EXPR:
      /* Excess precision for implicit conversions of integers to
	 floating point in C11 and later.  */
      may_need_excess_precision = (flag_isoc11
				   && (ANY_INTEGRAL_TYPE_P (type0)
				       || ANY_INTEGRAL_TYPE_P (type1)));
      اكسر;

    افتراضي:
      may_need_excess_precision = خطأ;
      اكسر;
    }
  𐤀𐤌 (TREE_CODE (op0) == EXCESS_PRECISION_EXPR)
    {
      op0 = TREE_OPERAND (op0, 0);
      type0 = TREE_TYPE (op0);
    }
  وإلا 𐤀𐤌 (may_need_excess_precision
	   && (eptype = excess_precision_type (type0)) != NULL_TREE)
    {
      type0 = eptype;
      op0 = convert (eptype, op0);
    }
  𐤀𐤌 (TREE_CODE (op1) == EXCESS_PRECISION_EXPR)
    {
      op1 = TREE_OPERAND (op1, 0);
      type1 = TREE_TYPE (op1);
    }
  وإلا 𐤀𐤌 (may_need_excess_precision
	   && (eptype = excess_precision_type (type1)) != NULL_TREE)
    {
      type1 = eptype;
      op1 = convert (eptype, op1);
    }

  objc_ok = objc_compare_types (type0, type1, -3, NULL_TREE);

  /* In case when one of the operands of the binary operation is
     a vector and another is a scalar -- convert scalar to vector.  */
  𐤀𐤌 ((gnu_vector_type_p (type0) && code1 != VECTOR_TYPE)
      || (gnu_vector_type_p (type1) && code0 != VECTOR_TYPE))
    {
      تعداد stv_conv convert_flag = scalar_to_vector (location, code, orig_op0,
						     orig_op1, true);

      بدل (convert_flag)
	{
	  حالة stv_error:
	    أرجع error_mark_node;
	  حالة stv_firstarg:
	    {
              منطقي maybe_const = true;
              tree sc;
              sc = c_fully_fold (op0, خطأ, &maybe_const);
              sc = save_expr (sc);
              sc = convert (TREE_TYPE (type1), sc);
              op0 = build_vector_from_val (type1, sc);
              𐤀𐤌 (!maybe_const)
                op0 = c_wrap_maybe_const (op0, true);
              orig_type0 = type0 = TREE_TYPE (op0);
              code0 = TREE_CODE (type0);
              converted = 1;
              اكسر;
	    }
	  حالة stv_secondarg:
	    {
	      منطقي maybe_const = true;
	      tree sc;
	      sc = c_fully_fold (op1, خطأ, &maybe_const);
	      sc = save_expr (sc);
	      sc = convert (TREE_TYPE (type0), sc);
	      op1 = build_vector_from_val (type0, sc);
	      𐤀𐤌 (!maybe_const)
		op1 = c_wrap_maybe_const (op1, true);
	      orig_type1 = type1 = TREE_TYPE (op1);
	      code1 = TREE_CODE (type1);
	      converted = 1;
	      اكسر;
	    }
	  افتراضي:
	    اكسر;
	}
    }

  بدل (code)
    {
    حالة PLUS_EXPR:
      /* Handle the pointer + int case.  */
      𐤀𐤌 (code0 == POINTER_TYPE
	  && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  ret = pointer_int_sum (location, PLUS_EXPR, op0, op1);
	  اذهب return_build_binary_op;
	}
      وإلا 𐤀𐤌 (code1 == POINTER_TYPE
	       && (code0 == INTEGER_TYPE || code0 == BITINT_TYPE))
	{
	  ret = pointer_int_sum (location, PLUS_EXPR, op1, op0);
	  اذهب return_build_binary_op;
	}
      وإلا
	common = 1;
      اكسر;

    حالة MINUS_EXPR:
      /* Subtraction of two similar pointers.
	 We must subtract them as integers, then divide by object size.  */
      𐤀𐤌 (code0 == POINTER_TYPE && code1 == POINTER_TYPE
	  && comp_target_types (location, type0, type1))
	{
	  ret = pointer_diff (location, op0, op1, &instrument_expr);
	  اذهب return_build_binary_op;
	}
      /* Handle pointer minus int.  Just like pointer plus int.  */
      وإلا 𐤀𐤌 (code0 == POINTER_TYPE
	       && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  ret = pointer_int_sum (location, MINUS_EXPR, op0, op1);
	  اذهب return_build_binary_op;
	}
      وإلا
	common = 1;
      اكسر;

    حالة MULT_EXPR:
      common = 1;
      اكسر;

    حالة TRUNC_DIV_EXPR:
    حالة CEIL_DIV_EXPR:
    حالة FLOOR_DIV_EXPR:
    حالة ROUND_DIV_EXPR:
    حالة EXACT_DIV_EXPR:
      doing_div_or_mod = true;
      warn_for_div_by_zero (location, op1);

      𐤀𐤌 ((code0 == INTEGER_TYPE || code0 == REAL_TYPE
	   || code0 == FIXED_POINT_TYPE || code0 == BITINT_TYPE
	   || code0 == COMPLEX_TYPE
	   || gnu_vector_type_p (type0))
	  && (code1 == INTEGER_TYPE || code1 == REAL_TYPE
	      || code1 == FIXED_POINT_TYPE || code1 == BITINT_TYPE
	      || code1 == COMPLEX_TYPE
	      || gnu_vector_type_p (type1)))
	{
	  تعداد tree_code tcode0 = code0, tcode1 = code1;

	  𐤀𐤌 (code0 == COMPLEX_TYPE || code0 == VECTOR_TYPE)
	    tcode0 = TREE_CODE (TREE_TYPE (TREE_TYPE (op0)));
	  𐤀𐤌 (code1 == COMPLEX_TYPE || code1 == VECTOR_TYPE)
	    tcode1 = TREE_CODE (TREE_TYPE (TREE_TYPE (op1)));

	  𐤀𐤌 (!(((tcode0 == INTEGER_TYPE || tcode0 == BITINT_TYPE
		  || (tcode0 == ENUMERAL_TYPE && code0 == VECTOR_TYPE))
		 && (tcode1 == INTEGER_TYPE || tcode1 == BITINT_TYPE
		     || (tcode1 == ENUMERAL_TYPE && code1 == VECTOR_TYPE)))
		|| (tcode0 == FIXED_POINT_TYPE && tcode1 == FIXED_POINT_TYPE)))
	    resultcode = RDIV_EXPR;
	  وإلا
	    /* Although it would be tempting to shorten always here, that
	       loses on some targets, since the modulo instruction is
	       undefined if the quotient can't be represented in the
	       computation mode.  We shorten only if unsigned or if
	       dividing by something we know != -1.  */
	    shorten = may_shorten_divmod (op0, op1);
	  common = 1;
	}
      اكسر;

    حالة BIT_AND_EXPR:
    حالة BIT_IOR_EXPR:
    حالة BIT_XOR_EXPR:
      𐤀𐤌 ((code0 == INTEGER_TYPE || code0 == BITINT_TYPE)
	  && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	shorten = -1;
      /* Allow vector types which are not floating point types.   */
      وإلا 𐤀𐤌 (gnu_vector_type_p (type0)
	       && gnu_vector_type_p (type1)
	       && !VECTOR_FLOAT_TYPE_P (type0)
	       && !VECTOR_FLOAT_TYPE_P (type1))
	common = 1;
      اكسر;

    حالة TRUNC_MOD_EXPR:
    حالة FLOOR_MOD_EXPR:
      doing_div_or_mod = true;
      warn_for_div_by_zero (location, op1);

      𐤀𐤌 (gnu_vector_type_p (type0)
	  && gnu_vector_type_p (type1)
	  && TREE_CODE (TREE_TYPE (type0)) == INTEGER_TYPE
	  && TREE_CODE (TREE_TYPE (type1)) == INTEGER_TYPE)
	common = 1;
      وإلا 𐤀𐤌 ((code0 == INTEGER_TYPE || code0 == BITINT_TYPE)
	       && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  /* Although it would be tempting to shorten always here, that loses
	     on some targets, since the modulo instruction is undefined if the
	     quotient can't be represented in the computation mode.  We shorten
	     only if unsigned or if dividing by something we know != -1.  */
	  shorten = may_shorten_divmod (op0, op1);
	  common = 1;
	}
      اكسر;

    حالة TRUTH_ANDIF_EXPR:
    حالة TRUTH_ORIF_EXPR:
    حالة TRUTH_AND_EXPR:
    حالة TRUTH_OR_EXPR:
    حالة TRUTH_XOR_EXPR:
      𐤀𐤌 ((code0 == INTEGER_TYPE || code0 == POINTER_TYPE
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
	  result_type = integer_type_node;
	  𐤀𐤌 (op0_int_operands)
	    {
	      op0 = c_objc_common_truthvalue_conversion (location, orig_op0);
	      op0 = remove_c_maybe_const_expr (op0);
	    }
	  وإلا
	    op0 = c_objc_common_truthvalue_conversion (location, op0);
	  𐤀𐤌 (op1_int_operands)
	    {
	      op1 = c_objc_common_truthvalue_conversion (location, orig_op1);
	      op1 = remove_c_maybe_const_expr (op1);
	    }
	  وإلا
	    op1 = c_objc_common_truthvalue_conversion (location, op1);
	  converted = 1;
	  boolean_op = true;
	}
      𐤀𐤌 (code == TRUTH_ANDIF_EXPR)
	{
	  int_const_or_overflow = (int_operands
				   && TREE_CODE (orig_op0) == INTEGER_CST
				   && (op0 == truthvalue_false_node
				       || TREE_CODE (orig_op1) == INTEGER_CST));
	  int_const = (int_const_or_overflow
		       && !TREE_OVERFLOW (orig_op0)
		       && (op0 == truthvalue_false_node
			   || !TREE_OVERFLOW (orig_op1)));
	}
      وإلا 𐤀𐤌 (code == TRUTH_ORIF_EXPR)
	{
	  int_const_or_overflow = (int_operands
				   && TREE_CODE (orig_op0) == INTEGER_CST
				   && (op0 == truthvalue_true_node
				       || TREE_CODE (orig_op1) == INTEGER_CST));
	  int_const = (int_const_or_overflow
		       && !TREE_OVERFLOW (orig_op0)
		       && (op0 == truthvalue_true_node
			   || !TREE_OVERFLOW (orig_op1)));
	}
      اكسر;

      /* Shift operations: result has same type as first operand;
	 always convert second operand to int.
	 Also set SHORT_SHIFT if shifting rightward.  */

    حالة RSHIFT_EXPR:
      𐤀𐤌 (gnu_vector_type_p (type0)
	  && gnu_vector_type_p (type1)
	  && TREE_CODE (TREE_TYPE (type0)) == INTEGER_TYPE
	  && TREE_CODE (TREE_TYPE (type1)) == INTEGER_TYPE
	  && known_eq (TYPE_VECTOR_SUBPARTS (type0),
		       TYPE_VECTOR_SUBPARTS (type1)))
	{
	  result_type = type0;
	  converted = 1;
	}
      وإلا 𐤀𐤌 ((code0 == INTEGER_TYPE || code0 == FIXED_POINT_TYPE
		|| code0 == BITINT_TYPE
		|| (gnu_vector_type_p (type0)
		    && TREE_CODE (TREE_TYPE (type0)) == INTEGER_TYPE))
	       && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  doing_shift = true;
	  𐤀𐤌 (TREE_CODE (op1) == INTEGER_CST)
	    {
	      𐤀𐤌 (tree_int_cst_sgn (op1) < 0)
		{
		  int_const = خطأ;
		  𐤀𐤌 (c_inhibit_evaluation_warnings == 0)
		    warning_at (location, OPT_Wshift_count_negative,
				"right shift count is negative");
		}
	      وإلا 𐤀𐤌 (code0 == VECTOR_TYPE)
		{
		  𐤀𐤌 (compare_tree_int (op1,
					TYPE_PRECISION (TREE_TYPE (type0)))
		      >= 0)
		    {
		      int_const = خطأ;
		      𐤀𐤌 (c_inhibit_evaluation_warnings == 0)
			warning_at (location, OPT_Wshift_count_overflow,
				    "right shift count >= width of vector element");
		    }
		}
	      وإلا
		{
		  𐤀𐤌 (!integer_zerop (op1))
		    short_shift = 1;

		  𐤀𐤌 (compare_tree_int (op1, TYPE_PRECISION (type0)) >= 0)
		    {
		      int_const = خطأ;
		      𐤀𐤌 (c_inhibit_evaluation_warnings == 0)
			warning_at (location, OPT_Wshift_count_overflow,
				    "right shift count >= width of type");
		    }
		}
	    }

	  /* Use the type of the value to be shifted.  */
	  result_type = type0;
	  /* Avoid converting op1 to result_type later.  */
	  converted = 1;
	}
      اكسر;

    حالة LSHIFT_EXPR:
      𐤀𐤌 (gnu_vector_type_p (type0)
	  && gnu_vector_type_p (type1)
	  && TREE_CODE (TREE_TYPE (type0)) == INTEGER_TYPE
	  && TREE_CODE (TREE_TYPE (type1)) == INTEGER_TYPE
	  && known_eq (TYPE_VECTOR_SUBPARTS (type0),
		       TYPE_VECTOR_SUBPARTS (type1)))
	{
	  result_type = type0;
	  converted = 1;
	}
      وإلا 𐤀𐤌 ((code0 == INTEGER_TYPE || code0 == FIXED_POINT_TYPE
		|| code0 == BITINT_TYPE
		|| (gnu_vector_type_p (type0)
		    && TREE_CODE (TREE_TYPE (type0)) == INTEGER_TYPE))
	       && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  doing_shift = true;
	  𐤀𐤌 (TREE_CODE (op0) == INTEGER_CST
	      && tree_int_cst_sgn (op0) < 0
	      && !TYPE_OVERFLOW_WRAPS (type0))
	    {
	      /* Don't reject a left shift of a negative value in a context
		 where a constant expression is needed in C90.  */
	      𐤀𐤌 (flag_isoc99)
		int_const = خطأ;
	      𐤀𐤌 (c_inhibit_evaluation_warnings == 0)
		warning_at (location, OPT_Wshift_negative_value,
			    "left shift of negative value");
	    }
	  𐤀𐤌 (TREE_CODE (op1) == INTEGER_CST)
	    {
	      𐤀𐤌 (tree_int_cst_sgn (op1) < 0)
		{
		  int_const = خطأ;
		  𐤀𐤌 (c_inhibit_evaluation_warnings == 0)
		    warning_at (location, OPT_Wshift_count_negative,
				"left shift count is negative");
		}
	      وإلا 𐤀𐤌 (code0 == VECTOR_TYPE)
		{
		  𐤀𐤌 (compare_tree_int (op1,
					TYPE_PRECISION (TREE_TYPE (type0)))
		      >= 0)
		    {
		      int_const = خطأ;
		      𐤀𐤌 (c_inhibit_evaluation_warnings == 0)
			warning_at (location, OPT_Wshift_count_overflow,
				    "left shift count >= width of vector element");
		    }
		}
	      وإلا 𐤀𐤌 (compare_tree_int (op1, TYPE_PRECISION (type0)) >= 0)
		{
		  int_const = خطأ;
		  𐤀𐤌 (c_inhibit_evaluation_warnings == 0)
		    warning_at (location, OPT_Wshift_count_overflow,
				"left shift count >= width of type");
		}
	      وإلا 𐤀𐤌 (TREE_CODE (op0) == INTEGER_CST
		       && maybe_warn_shift_overflow (location, op0, op1)
		       && flag_isoc99)
		int_const = خطأ;
	    }

	  /* Use the type of the value to be shifted.  */
	  result_type = type0;
	  /* Avoid converting op1 to result_type later.  */
	  converted = 1;
	}
      اكسر;

    حالة EQ_EXPR:
    حالة NE_EXPR:
      𐤀𐤌 (gnu_vector_type_p (type0) && gnu_vector_type_p (type1))
        {
          tree intt;
	  𐤀𐤌 (!vector_types_compatible_elements_p (type0, type1))
            {
              error_at (location, "comparing vectors with different "
                                  "element types");
              أرجع error_mark_node;
            }

	  𐤀𐤌 (maybe_ne (TYPE_VECTOR_SUBPARTS (type0),
			TYPE_VECTOR_SUBPARTS (type1)))
            {
              error_at (location, "comparing vectors with different "
                                  "number of elements");
              أرجع error_mark_node;
            }

	  /* It's not precisely specified how the usual arithmetic
	     conversions apply to the vector types.  Here, we use
	     the unsigned type if one of the operands is signed and
	     the other one is unsigned.  */
	  𐤀𐤌 (TYPE_UNSIGNED (type0) != TYPE_UNSIGNED (type1))
	    {
	      𐤀𐤌 (!TYPE_UNSIGNED (type0))
		op0 = build1 (VIEW_CONVERT_EXPR, type1, op0);
	      وإلا
		op1 = build1 (VIEW_CONVERT_EXPR, type0, op1);
	      warning_at (location, OPT_Wsign_compare, "comparison between "
			  "types %qT and %qT", type0, type1);
	    }

          /* Always construct signed integer vector type.  */
	  𐤀𐤌 (VECTOR_BOOLEAN_TYPE_P (type0) && VECTOR_BOOLEAN_TYPE_P (type1))
	    result_type = type0;
	  وإلا
	    {
	      auto nelts = TYPE_VECTOR_SUBPARTS (type0);

	      intt = c_common_type_for_size (GET_MODE_BITSIZE
					     (SCALAR_TYPE_MODE
						(TREE_TYPE (type0))), 0);
	      𐤀𐤌 (!intt)
		{
		  error_at (location, "could not find an integer type "
				      "of the same size as %qT",
			    TREE_TYPE (type0));
		  أرجع error_mark_node;
		}
	      result_type = build_opaque_vector_type (intt, nelts);
	    }
          converted = 1;
	  ret = build_vec_cmp (resultcode, result_type, op0, op1);
	  اذهب return_build_binary_op;
        }
      𐤀𐤌 (FLOAT_TYPE_P (type0) || FLOAT_TYPE_P (type1))
	warning_at (location,
		    OPT_Wfloat_equal,
		    "comparing floating-point with %<==%> or %<!=%> is unsafe");
      /* Result of comparison is always int,
	 but don't convert the args to int!  */
      build_type = integer_type_node;
      𐤀𐤌 ((code0 == INTEGER_TYPE || code0 == REAL_TYPE || code0 == BITINT_TYPE
	   || code0 == FIXED_POINT_TYPE || code0 == COMPLEX_TYPE)
	  && (code1 == INTEGER_TYPE || code1 == REAL_TYPE
	      || code1 == BITINT_TYPE
	      || code1 == FIXED_POINT_TYPE || code1 == COMPLEX_TYPE))
	short_compare = 1;
      وإلا 𐤀𐤌 (code0 == POINTER_TYPE
	       && (code1 == NULLPTR_TYPE
		   || null_pointer_constant_p (orig_op1)))
	{
	  maybe_warn_for_null_address (location, op0, code);
	  result_type = type0;
	}
      وإلا 𐤀𐤌 (code1 == POINTER_TYPE
	       && (code0 == NULLPTR_TYPE
		   || null_pointer_constant_p (orig_op0)))
	{
	  maybe_warn_for_null_address (location, op1, code);
	  result_type = type1;
	}
      وإلا 𐤀𐤌 (code0 == POINTER_TYPE && code1 == POINTER_TYPE)
	{
	  tree tt0 = TREE_TYPE (type0);
	  tree tt1 = TREE_TYPE (type1);
	  addr_space_t as0 = TYPE_ADDR_SPACE (tt0);
	  addr_space_t as1 = TYPE_ADDR_SPACE (tt1);
	  addr_space_t as_common = ADDR_SPACE_GENERIC;

	  /* Anything compares with void *.  void * compares with anything.
	     Otherwise, the targets must be compatible
	     and both must be object or both incomplete.  */
	  𐤀𐤌 (comp_target_types (location, type0, type1))
	    result_type = common_pointer_type (type0, type1, NULL_TREE);
	  وإلا 𐤀𐤌 (!addr_space_superset (as0, as1, &as_common))
	    {
	      error_at (location, "comparison of pointers to "
			"disjoint address spaces");
	      أرجع error_mark_node;
	    }
	  وإلا 𐤀𐤌 (VOID_TYPE_P (tt0) && !TYPE_ATOMIC (tt0))
	    {
	      𐤀𐤌 (pedantic && TREE_CODE (tt1) == FUNCTION_TYPE)
		pedwarn (location, OPT_Wpedantic, "ISO C forbids "
			 "comparison of %<void *%> with function pointer");
	    }
	  وإلا 𐤀𐤌 (VOID_TYPE_P (tt1) && !TYPE_ATOMIC (tt1))
	    {
	      𐤀𐤌 (pedantic && TREE_CODE (tt0) == FUNCTION_TYPE)
		pedwarn (location, OPT_Wpedantic, "ISO C forbids "
			 "comparison of %<void *%> with function pointer");
	    }
	  وإلا
	    /* Avoid warning about the volatile ObjC EH puts on decls.  */
	    𐤀𐤌 (!objc_ok)
	      pedwarn (location, OPT_Wcompare_distinct_pointer_types,
		       "comparison of distinct pointer types lacks a cast");

	  𐤀𐤌 (result_type == NULL_TREE)
	    {
	      صحيح qual = ENCODE_QUAL_ADDR_SPACE (as_common);
	      result_type = c_build_pointer_type
			      (c_build_qualified_type (void_type_node, qual));
	    }
	}
      وإلا 𐤀𐤌 (code0 == POINTER_TYPE
	       && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  result_type = type0;
	  pedwarn (location, 0, "comparison between pointer and integer");
	}
      وإلا 𐤀𐤌 ((code0 == INTEGER_TYPE || code0 == BITINT_TYPE)
	       && code1 == POINTER_TYPE)
	{
	  result_type = type1;
	  pedwarn (location, 0, "comparison between pointer and integer");
	}
      /* 6.5.9: One of the following shall hold:
	 -- both operands have type nullptr_t;  */
      وإلا 𐤀𐤌 (code0 == NULLPTR_TYPE && code1 == NULLPTR_TYPE)
	{
	  result_type = nullptr_type_node;
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
      وإلا 𐤀𐤌 (code0 == NULLPTR_TYPE && null_pointer_constant_p (orig_op1))
	result_type = (INTEGRAL_TYPE_P (type1)
		       ? c_build_pointer_type (type1) : type1);
      وإلا 𐤀𐤌 (code1 == NULLPTR_TYPE && null_pointer_constant_p (orig_op0))
	result_type = (INTEGRAL_TYPE_P (type0)
		       ? c_build_pointer_type (type0) : type0);
      𐤀𐤌 ((C_BOOLEAN_TYPE_P (TREE_TYPE (orig_op0))
	   || truth_value_p (TREE_CODE (orig_op0)))
	  ^ (C_BOOLEAN_TYPE_P (TREE_TYPE (orig_op1))
	     || truth_value_p (TREE_CODE (orig_op1))))
	maybe_warn_bool_compare (location, code, orig_op0, orig_op1);
      اكسر;

    حالة LE_EXPR:
    حالة GE_EXPR:
    حالة LT_EXPR:
    حالة GT_EXPR:
      𐤀𐤌 (gnu_vector_type_p (type0) && gnu_vector_type_p (type1))
        {
          tree intt;
	  𐤀𐤌 (!vector_types_compatible_elements_p (type0, type1))
            {
              error_at (location, "comparing vectors with different "
                                  "element types");
              أرجع error_mark_node;
            }

	  𐤀𐤌 (maybe_ne (TYPE_VECTOR_SUBPARTS (type0),
			TYPE_VECTOR_SUBPARTS (type1)))
            {
              error_at (location, "comparing vectors with different "
                                  "number of elements");
              أرجع error_mark_node;
            }

	  /* It's not precisely specified how the usual arithmetic
	     conversions apply to the vector types.  Here, we use
	     the unsigned type if one of the operands is signed and
	     the other one is unsigned.  */
	  𐤀𐤌 (TYPE_UNSIGNED (type0) != TYPE_UNSIGNED (type1))
	    {
	      𐤀𐤌 (!TYPE_UNSIGNED (type0))
		op0 = build1 (VIEW_CONVERT_EXPR, type1, op0);
	      وإلا
		op1 = build1 (VIEW_CONVERT_EXPR, type0, op1);
	      warning_at (location, OPT_Wsign_compare, "comparison between "
			  "types %qT and %qT", type0, type1);
	    }

          /* Always construct signed integer vector type.  */
          intt = c_common_type_for_size (GET_MODE_BITSIZE
					 (SCALAR_TYPE_MODE
					  (TREE_TYPE (type0))), 0);
	  𐤀𐤌 (!intt)
	    {
	      error_at (location, "could not find an integer type "
				  "of the same size as %qT",
			TREE_TYPE (type0));
	      أرجع error_mark_node;
	    }
          result_type = build_opaque_vector_type (intt,
						  TYPE_VECTOR_SUBPARTS (type0));
          converted = 1;
	  ret = build_vec_cmp (resultcode, result_type, op0, op1);
	  اذهب return_build_binary_op;
        }
      build_type = integer_type_node;
      𐤀𐤌 ((code0 == INTEGER_TYPE || code0 == REAL_TYPE
	   || code0 == BITINT_TYPE || code0 == FIXED_POINT_TYPE)
	  && (code1 == INTEGER_TYPE || code1 == REAL_TYPE
	      || code1 == BITINT_TYPE || code1 == FIXED_POINT_TYPE))
	short_compare = 1;
      وإلا 𐤀𐤌 (code0 == POINTER_TYPE && code1 == POINTER_TYPE)
	{
	  addr_space_t as0 = TYPE_ADDR_SPACE (TREE_TYPE (type0));
	  addr_space_t as1 = TYPE_ADDR_SPACE (TREE_TYPE (type1));
	  addr_space_t as_common;

	  𐤀𐤌 (comp_target_types (location, type0, type1))
	    {
	      result_type = common_pointer_type (type0, type1, NULL_TREE);
	      𐤀𐤌 (!COMPLETE_TYPE_P (TREE_TYPE (type0))
		  != !COMPLETE_TYPE_P (TREE_TYPE (type1)))
		pedwarn_c99 (location, OPT_Wpedantic,
			     "comparison of complete and incomplete pointers");
	      وإلا 𐤀𐤌 (TREE_CODE (TREE_TYPE (type0)) == FUNCTION_TYPE)
		pedwarn (location, OPT_Wpedantic, "ISO C forbids "
			 "ordered comparisons of pointers to functions");
	      وإلا 𐤀𐤌 (null_pointer_constant_p (orig_op0)
		       || null_pointer_constant_p (orig_op1))
		warning_at (location, OPT_Wextra,
			    "ordered comparison of pointer with null pointer");

	    }
	  وإلا 𐤀𐤌 (!addr_space_superset (as0, as1, &as_common))
	    {
	      error_at (location, "comparison of pointers to "
			"disjoint address spaces");
	      أرجع error_mark_node;
	    }
	  وإلا
	    {
	      صحيح qual = ENCODE_QUAL_ADDR_SPACE (as_common);
	      result_type = c_build_pointer_type
			      (c_build_qualified_type (void_type_node, qual));
              pedwarn (location, OPT_Wcompare_distinct_pointer_types,
                       "comparison of distinct pointer types lacks a cast");
	    }
	}
      وإلا 𐤀𐤌 (code0 == POINTER_TYPE && null_pointer_constant_p (orig_op1))
	{
	  result_type = type0;
	  𐤀𐤌 (pedantic)
	    pedwarn (location, OPT_Wpedantic,
		     "ordered comparison of pointer with integer zero");
	  وإلا 𐤀𐤌 (extra_warnings)
	    warning_at (location, OPT_Wextra,
			"ordered comparison of pointer with integer zero");
	}
      وإلا 𐤀𐤌 (code1 == POINTER_TYPE && null_pointer_constant_p (orig_op0))
	{
	  result_type = type1;
	  𐤀𐤌 (pedantic)
	    pedwarn (location, OPT_Wpedantic,
		     "ordered comparison of pointer with integer zero");
	  وإلا 𐤀𐤌 (extra_warnings)
	    warning_at (location, OPT_Wextra,
			"ordered comparison of pointer with integer zero");
	}
      وإلا 𐤀𐤌 (code0 == POINTER_TYPE
	       && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  result_type = type0;
	  pedwarn (location, 0, "comparison between pointer and integer");
	}
      وإلا 𐤀𐤌 ((code0 == INTEGER_TYPE || code0 == BITINT_TYPE)
	       && code1 == POINTER_TYPE)
	{
	  result_type = type1;
	  pedwarn (location, 0, "comparison between pointer and integer");
	}

      𐤀𐤌 ((code0 == POINTER_TYPE || code1 == POINTER_TYPE)
	  && current_function_decl != NULL_TREE
	  && sanitize_flags_p (SANITIZE_POINTER_COMPARE))
	{
	  op0 = save_expr (c_fully_fold (op0, خطأ, عدم));
	  op1 = save_expr (c_fully_fold (op1, خطأ, عدم));

	  tree tt = builtin_decl_explicit (BUILT_IN_ASAN_POINTER_COMPARE);
	  instrument_expr = build_call_expr_loc (location, tt, 2, op0, op1);
	}

      𐤀𐤌 ((C_BOOLEAN_TYPE_P (TREE_TYPE (orig_op0))
	   || truth_value_p (TREE_CODE (orig_op0)))
	  ^ (C_BOOLEAN_TYPE_P (TREE_TYPE (orig_op1))
	     || truth_value_p (TREE_CODE (orig_op1))))
	maybe_warn_bool_compare (location, code, orig_op0, orig_op1);
      اكسر;

    حالة MIN_EXPR:
    حالة MAX_EXPR:
      /* Used for OpenMP atomics.  */
      gcc_assert (flag_openmp);
      common = 1;
      اكسر;

    افتراضي:
      gcc_unreachable ();
    }

  𐤀𐤌 (code0 == ERROR_MARK || code1 == ERROR_MARK)
    أرجع error_mark_node;

  𐤀𐤌 (gnu_vector_type_p (type0)
      && gnu_vector_type_p (type1)
      && (!tree_int_cst_equal (TYPE_SIZE (type0), TYPE_SIZE (type1))
	  || !vector_types_compatible_elements_p (type0, type1)))
    {
      gcc_rich_location richloc (location);
      maybe_range_label_for_tree_type_mismatch
	label_for_op0 (orig_op0, orig_op1),
	label_for_op1 (orig_op1, orig_op0);
      richloc.maybe_add_expr (orig_op0, &label_for_op0, highlight_colors::lhs);
      richloc.maybe_add_expr (orig_op1, &label_for_op1, highlight_colors::rhs);
      binary_op_error (&richloc, code, type0, type1);
      أرجع error_mark_node;
    }

  𐤀𐤌 ((code0 == INTEGER_TYPE || code0 == REAL_TYPE || code0 == COMPLEX_TYPE
       || code0 == FIXED_POINT_TYPE || code0 == BITINT_TYPE
       || gnu_vector_type_p (type0))
      && (code1 == INTEGER_TYPE || code1 == REAL_TYPE || code1 == COMPLEX_TYPE
	  || code1 == FIXED_POINT_TYPE || code1 == BITINT_TYPE
	  || gnu_vector_type_p (type1)))
    {
      منطقي first_complex = (code0 == COMPLEX_TYPE);
      منطقي second_complex = (code1 == COMPLEX_TYPE);
      صحيح none_complex = (!first_complex && !second_complex);

      𐤀𐤌 (shorten || common || short_compare)
	{
	  result_type = c_common_type (type0, type1);
	  do_warn_double_promotion (result_type, type0, type1,
				    "implicit conversion from %qT to %qT "
				    "to match other operand of binary "
				    "expression",
				    location);
	  𐤀𐤌 (result_type == error_mark_node)
	    أرجع error_mark_node;
	}

      𐤀𐤌 (first_complex != second_complex
	  && (code == PLUS_EXPR
	      || code == MINUS_EXPR
	      || code == MULT_EXPR
	      || (code == TRUNC_DIV_EXPR && first_complex))
	  && TREE_CODE (TREE_TYPE (result_type)) == REAL_TYPE
	  && flag_signed_zeros)
	{
	  /* An operation on mixed real/complex operands must be
	     handled specially, but the language-independent code can
	     more easily optimize the plain complex arithmetic if
	     -fno-signed-zeros.  */
	  tree real_type = TREE_TYPE (result_type);
	  tree real, imag;
	  𐤀𐤌 (type0 != orig_type0 || type1 != orig_type1)
	    {
	      gcc_assert (may_need_excess_precision && common);
	      semantic_result_type = c_common_type (orig_type0, orig_type1);
	    }
	  𐤀𐤌 (first_complex)
	    {
	      𐤀𐤌 (TREE_TYPE (op0) != result_type)
		op0 = convert_and_check (location, result_type, op0);
	      𐤀𐤌 (TREE_TYPE (op1) != real_type)
		op1 = convert_and_check (location, real_type, op1);
	    }
	  وإلا
	    {
	      𐤀𐤌 (TREE_TYPE (op0) != real_type)
		op0 = convert_and_check (location, real_type, op0);
	      𐤀𐤌 (TREE_TYPE (op1) != result_type)
		op1 = convert_and_check (location, result_type, op1);
	    }
	  𐤀𐤌 (TREE_CODE (op0) == ERROR_MARK || TREE_CODE (op1) == ERROR_MARK)
	    أرجع error_mark_node;
	  𐤀𐤌 (first_complex)
	    {
	      op0 = save_expr (op0);
	      real = build_unary_op (EXPR_LOCATION (orig_op0), REALPART_EXPR,
				     op0, true);
	      imag = build_unary_op (EXPR_LOCATION (orig_op0), IMAGPART_EXPR,
				     op0, true);
	      بدل (code)
		{
		حالة MULT_EXPR:
		حالة TRUNC_DIV_EXPR:
		  op1 = save_expr (op1);
		  imag = build2 (resultcode, real_type, imag, op1);
		  /* Fall through.  */
		حالة PLUS_EXPR:
		حالة MINUS_EXPR:
		  real = build2 (resultcode, real_type, real, op1);
		  اكسر;
		افتراضي:
		  gcc_unreachable();
		}
	    }
	  وإلا
	    {
	      op1 = save_expr (op1);
	      real = build_unary_op (EXPR_LOCATION (orig_op1), REALPART_EXPR,
				     op1, true);
	      imag = build_unary_op (EXPR_LOCATION (orig_op1), IMAGPART_EXPR,
				     op1, true);
	      بدل (code)
		{
		حالة MULT_EXPR:
		  op0 = save_expr (op0);
		  imag = build2 (resultcode, real_type, op0, imag);
		  /* Fall through.  */
		حالة PLUS_EXPR:
		  real = build2 (resultcode, real_type, op0, real);
		  اكسر;
		حالة MINUS_EXPR:
		  real = build2 (resultcode, real_type, op0, real);
		  imag = build1 (NEGATE_EXPR, real_type, imag);
		  اكسر;
		افتراضي:
		  gcc_unreachable();
		}
	    }
	  ret = build2 (COMPLEX_EXPR, result_type, real, imag);
	  اذهب return_build_binary_op;
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

      𐤀𐤌 (shorten && none_complex)
	{
	  final_type = result_type;
	  result_type = shorten_binary_op (result_type, op0, op1,
					   shorten == -1);
	}

      /* Shifts can be shortened if shifting right.  */

      𐤀𐤌 (short_shift)
	{
	  صحيح unsigned_arg;
	  tree arg0 = get_narrower (op0, &unsigned_arg);

	  final_type = result_type;

	  𐤀𐤌 (arg0 == op0 && final_type == TREE_TYPE (op0))
	    unsigned_arg = TYPE_UNSIGNED (TREE_TYPE (op0));

	  𐤀𐤌 (TYPE_PRECISION (TREE_TYPE (arg0)) < TYPE_PRECISION (result_type)
	      && tree_int_cst_sgn (op1) > 0
	      /* We can shorten only if the shift count is less than the
		 number of bits in the smaller type size.  */
	      && compare_tree_int (op1, TYPE_PRECISION (TREE_TYPE (arg0))) < 0
	      /* We cannot drop an unsigned shift after sign-extension.  */
	      && (!TYPE_UNSIGNED (final_type) || unsigned_arg))
	    {
	      /* Do an unsigned shift if the operand was zero-extended.  */
	      result_type
		= c_common_signed_or_unsigned_type (unsigned_arg,
						    TREE_TYPE (arg0));
	      /* Convert value-to-be-shifted to that type.  */
	      𐤀𐤌 (TREE_TYPE (op0) != result_type)
		op0 = convert (result_type, op0);
	      converted = 1;
	    }
	}

      /* Comparison operations are shortened too but differently.
	 They identify themselves by setting short_compare = 1.  */

      𐤀𐤌 (short_compare)
	{
	  /* Don't write &op0, etc., because that would prevent op0
	     from being kept in a register.
	     Instead, make copies of the our local variables and
	     pass the copies by reference, then copy them back afterward.  */
	  tree xop0 = op0, xop1 = op1, xresult_type = result_type;
	  تعداد tree_code xresultcode = resultcode;
	  tree val
	    = shorten_compare (location, &xop0, &xop1, &xresult_type,
			       &xresultcode);

	  𐤀𐤌 (val != NULL_TREE)
	    {
	      ret = val;
	      اذهب return_build_binary_op;
	    }

	  op0 = xop0, op1 = xop1;
	  converted = 1;
	  resultcode = xresultcode;

	  𐤀𐤌 (c_inhibit_evaluation_warnings == 0 && !c_in_omp_for)
	    {
	      منطقي op0_maybe_const = true;
	      منطقي op1_maybe_const = true;
	      tree orig_op0_folded, orig_op1_folded;

	      𐤀𐤌 (in_late_binary_op)
		{
		  orig_op0_folded = orig_op0;
		  orig_op1_folded = orig_op1;
		}
	      وإلا
		{
		  /* Fold for the sake of possible warnings, as in
		     build_conditional_expr.  This requires the
		     "original" values to be folded, not just op0 and
		     op1.  */
		  c_inhibit_evaluation_warnings++;
		  op0 = c_fully_fold (op0, require_constant_value,
				      &op0_maybe_const);
		  op1 = c_fully_fold (op1, require_constant_value,
				      &op1_maybe_const);
		  c_inhibit_evaluation_warnings--;
		  orig_op0_folded = c_fully_fold (orig_op0,
						  require_constant_value,
						  عدم);
		  orig_op1_folded = c_fully_fold (orig_op1,
						  require_constant_value,
						  عدم);
		}

	      𐤀𐤌 (warn_sign_compare)
		warn_for_sign_compare (location, orig_op0_folded,
				       orig_op1_folded, op0, op1,
				       result_type, resultcode);
	      𐤀𐤌 (!in_late_binary_op && !int_operands)
		{
		  𐤀𐤌 (!op0_maybe_const || TREE_CODE (op0) != INTEGER_CST)
		    op0 = c_wrap_maybe_const (op0, !op0_maybe_const);
		  𐤀𐤌 (!op1_maybe_const || TREE_CODE (op1) != INTEGER_CST)
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

  𐤀𐤌 (!result_type)
    {
      /* Favor showing any expression locations that are available. */
      op_location_t oploc (location, UNKNOWN_LOCATION);
      binary_op_rich_location richloc (oploc, orig_op0, orig_op1, true);
      binary_op_error (&richloc, code, TREE_TYPE (op0), TREE_TYPE (op1));
      أرجع error_mark_node;
    }

  𐤀𐤌 (build_type == NULL_TREE)
    {
      build_type = result_type;
      𐤀𐤌 ((type0 != orig_type0 || type1 != orig_type1)
	  && !boolean_op)
	{
	  gcc_assert (may_need_excess_precision && common);
	  semantic_result_type = c_common_type (orig_type0, orig_type1);
	}
    }

  𐤀𐤌 (!converted)
    {
      op0 = ep_convert_and_check (location, result_type, op0,
				  semantic_result_type);
      op1 = ep_convert_and_check (location, result_type, op1,
				  semantic_result_type);

      /* This can happen if one operand has a vector type, and the other
	 has a different type.  */
      𐤀𐤌 (TREE_CODE (op0) == ERROR_MARK || TREE_CODE (op1) == ERROR_MARK)
	أرجع error_mark_node;
    }

  𐤀𐤌 (sanitize_flags_p ((SANITIZE_SHIFT
			 | SANITIZE_DIVIDE
			 | SANITIZE_FLOAT_DIVIDE
			 | SANITIZE_SI_OVERFLOW))
      && current_function_decl != NULL_TREE
      && (doing_div_or_mod || doing_shift)
      && !require_constant_value)
    {
      /* OP0 and/or OP1 might have side-effects.  */
      op0 = save_expr (op0);
      op1 = save_expr (op1);
      op0 = c_fully_fold (op0, خطأ, عدم);
      op1 = c_fully_fold (op1, خطأ, عدم);
      𐤀𐤌 (doing_div_or_mod && (sanitize_flags_p ((SANITIZE_DIVIDE
						  | SANITIZE_FLOAT_DIVIDE
						  | SANITIZE_SI_OVERFLOW))))
	instrument_expr = ubsan_instrument_division (location, op0, op1);
      وإلا 𐤀𐤌 (doing_shift && sanitize_flags_p (SANITIZE_SHIFT))
	instrument_expr = ubsan_instrument_shift (location, code, op0, op1);
    }

  /* Treat expressions in initializers specially as they can't trap.  */
  𐤀𐤌 (int_const_or_overflow)
    ret = (require_constant_value
	   ? fold_build2_initializer_loc (location, resultcode, build_type,
					  op0, op1)
	   : fold_build2_loc (location, resultcode, build_type, op0, op1));
  وإلا
    ret = build2 (resultcode, build_type, op0, op1);
  𐤀𐤌 (final_type != NULL_TREE)
    ret = convert (final_type, ret);

 return_build_binary_op:
  gcc_assert (ret != error_mark_node);
  𐤀𐤌 (TREE_CODE (ret) == INTEGER_CST && !TREE_OVERFLOW (ret) && !int_const)
    ret = (int_operands
	   ? note_integer_operands (ret)
	   : build1 (NOP_EXPR, TREE_TYPE (ret), ret));
  وإلا 𐤀𐤌 (TREE_CODE (ret) != INTEGER_CST && int_operands
	   && !in_late_binary_op)
    ret = note_integer_operands (ret);
  protected_set_expr_location (ret, location);

  𐤀𐤌 (instrument_expr != عدم)
    ret = fold_build2 (COMPOUND_EXPR, TREE_TYPE (ret),
		       instrument_expr, ret);

  𐤀𐤌 (semantic_result_type)
    ret = build1_loc (location, EXCESS_PRECISION_EXPR,
		      semantic_result_type, ret);

  أرجع ret;
}


/* Convert EXPR to be a truth-value (type TYPE), validating its type for this
   purpose.  LOCATION is the source location for the expression.  */

tree
c_objc_common_truthvalue_conversion (location_t location, tree expr, tree type)
{
  منطقي int_const, int_operands;

  بدل (TREE_CODE (TREE_TYPE (expr)))
    {
    حالة ARRAY_TYPE:
      error_at (location, "used array that cannot be converted to pointer where scalar is required");
      أرجع error_mark_node;

    حالة RECORD_TYPE:
      error_at (location, "used struct type value where scalar is required");
      أرجع error_mark_node;

    حالة UNION_TYPE:
      error_at (location, "used union type value where scalar is required");
      أرجع error_mark_node;

    حالة VOID_TYPE:
      error_at (location, "void value not ignored as it ought to be");
      أرجع error_mark_node;

    حالة POINTER_TYPE:
      𐤀𐤌 (reject_gcc_builtin (expr))
	أرجع error_mark_node;
      اكسر;

    حالة FUNCTION_TYPE:
      gcc_unreachable ();

    حالة VECTOR_TYPE:
      error_at (location, "used vector type where scalar is required");
      أرجع error_mark_node;

    افتراضي:
      اكسر;
    }

  /* Conversion of a floating constant to boolean goes through here
     and yields an integer constant expression.  Otherwise, the result
     is only an integer constant expression if the argument is.  */
  int_const = ((TREE_CODE (expr) == INTEGER_CST && !TREE_OVERFLOW (expr))
	       || ((TREE_CODE (expr) == REAL_CST
		    || TREE_CODE (expr) == COMPLEX_CST)
		   && (TREE_CODE (type) == BOOLEAN_TYPE
		       || (TREE_CODE (type) == ENUMERAL_TYPE
			   && ENUM_UNDERLYING_TYPE (type) != NULL_TREE
			   && (TREE_CODE (ENUM_UNDERLYING_TYPE (type))
			       == BOOLEAN_TYPE)))));
  int_operands = EXPR_INT_CONST_OPERANDS (expr);
  𐤀𐤌 (int_operands && TREE_CODE (expr) != INTEGER_CST)
    {
      expr = remove_c_maybe_const_expr (expr);
      expr = build2 (NE_EXPR, type, expr,
		     convert (TREE_TYPE (expr), integer_zero_node));
      expr = note_integer_operands (expr);
    }
  وإلا
    {
      /* ??? Should we also give an error for vectors rather than leaving
	 those to give errors later?  */
      expr = c_common_truthvalue_conversion (location, expr);
      expr = fold_convert_loc (location, type, expr);
    }

  𐤀𐤌 (TREE_CODE (expr) == INTEGER_CST && int_operands && !int_const)
    {
      𐤀𐤌 (TREE_OVERFLOW (expr))
	أرجع expr;
      وإلا
	أرجع note_integer_operands (expr);
    }
  𐤀𐤌 (TREE_CODE (expr) == INTEGER_CST && !int_const)
    أرجع build1 (NOP_EXPR, TREE_TYPE (expr), expr);
  أرجع expr;
}


/* Convert EXPR to a contained DECL, updating *TC, *TI and *SE as
   required.  */

tree
c_expr_to_decl (tree expr, منطقي *tc ATTRIBUTE_UNUSED, منطقي *se)
{
  𐤀𐤌 (TREE_CODE (expr) == COMPOUND_LITERAL_EXPR)
    {
      tree decl = COMPOUND_LITERAL_EXPR_DECL (expr);
      /* Executing a compound literal inside a function reinitializes
	 it.  */
      𐤀𐤌 (!TREE_STATIC (decl))
	*se = true;
      أرجع decl;
    }
  وإلا
    أرجع expr;
}

/* Generate OMP construct CODE, with BODY and CLAUSES as its compound
   statement.  LOC is the location of the construct.  */

tree
c_finish_omp_construct (location_t loc, تعداد tree_code code, tree body,
			tree clauses)
{
  body = c_end_compound_stmt (loc, body, true);

  tree stmt = make_node (code);
  TREE_TYPE (stmt) = void_type_node;
  OMP_BODY (stmt) = body;
  OMP_CLAUSES (stmt) = clauses;
  SET_EXPR_LOCATION (stmt, loc);

  أرجع add_stmt (stmt);
}

/* Generate OACC_DATA, with CLAUSES and BLOCK as its compound
   statement.  LOC is the location of the OACC_DATA.  */

tree
c_finish_oacc_data (location_t loc, tree clauses, tree block)
{
  tree stmt;

  block = c_end_compound_stmt (loc, block, true);

  stmt = make_node (OACC_DATA);
  TREE_TYPE (stmt) = void_type_node;
  OACC_DATA_CLAUSES (stmt) = clauses;
  OACC_DATA_BODY (stmt) = block;
  SET_EXPR_LOCATION (stmt, loc);

  أرجع add_stmt (stmt);
}

/* Generate OACC_HOST_DATA, with CLAUSES and BLOCK as its compound
   statement.  LOC is the location of the OACC_HOST_DATA.  */

tree
c_finish_oacc_host_data (location_t loc, tree clauses, tree block)
{
  tree stmt;

  block = c_end_compound_stmt (loc, block, true);

  stmt = make_node (OACC_HOST_DATA);
  TREE_TYPE (stmt) = void_type_node;
  OACC_HOST_DATA_CLAUSES (stmt) = clauses;
  OACC_HOST_DATA_BODY (stmt) = block;
  SET_EXPR_LOCATION (stmt, loc);

  أرجع add_stmt (stmt);
}

/* Like c_begin_compound_stmt, except force the retention of the BLOCK.  */

tree
c_begin_omp_parallel (فراغ)
{
  tree block;

  keep_next_level ();
  block = c_begin_compound_stmt (true);

  أرجع block;
}

/* Generate OMP_PARALLEL, with CLAUSES and BLOCK as its compound
   statement.  LOC is the location of the OMP_PARALLEL.  */

tree
c_finish_omp_parallel (location_t loc, tree clauses, tree block)
{
  tree stmt;

  block = c_end_compound_stmt (loc, block, true);

  stmt = make_node (OMP_PARALLEL);
  TREE_TYPE (stmt) = void_type_node;
  OMP_PARALLEL_CLAUSES (stmt) = clauses;
  OMP_PARALLEL_BODY (stmt) = block;
  SET_EXPR_LOCATION (stmt, loc);

  أرجع add_stmt (stmt);
}

/* Like c_begin_compound_stmt, except force the retention of the BLOCK.  */

tree
c_begin_omp_task (فراغ)
{
  tree block;

  keep_next_level ();
  block = c_begin_compound_stmt (true);

  أرجع block;
}

/* Generate OMP_TASK, with CLAUSES and BLOCK as its compound
   statement.  LOC is the location of the #pragma.  */

tree
c_finish_omp_task (location_t loc, tree clauses, tree block)
{
  tree stmt;

  block = c_end_compound_stmt (loc, block, true);

  stmt = make_node (OMP_TASK);
  TREE_TYPE (stmt) = void_type_node;
  OMP_TASK_CLAUSES (stmt) = clauses;
  OMP_TASK_BODY (stmt) = block;
  SET_EXPR_LOCATION (stmt, loc);

  أرجع add_stmt (stmt);
}

/* Generate GOMP_cancel call for #pragma omp cancel.  */

فراغ
c_finish_omp_cancel (location_t loc, tree clauses)
{
  tree fn = builtin_decl_explicit (BUILT_IN_GOMP_CANCEL);
  صحيح mask = 0;
  𐤀𐤌 (omp_find_clause (clauses, OMP_CLAUSE_PARALLEL))
    mask = 1;
  وإلا 𐤀𐤌 (omp_find_clause (clauses, OMP_CLAUSE_FOR))
    mask = 2;
  وإلا 𐤀𐤌 (omp_find_clause (clauses, OMP_CLAUSE_SECTIONS))
    mask = 4;
  وإلا 𐤀𐤌 (omp_find_clause (clauses, OMP_CLAUSE_TASKGROUP))
    mask = 8;
  وإلا
    {
      error_at (loc, "%<#pragma omp cancel%> must specify one of "
		     "%<parallel%>, %<for%>, %<sections%> or %<taskgroup%> "
		     "clauses");
      أرجع;
    }
  tree ifc = omp_find_clause (clauses, OMP_CLAUSE_IF);
  𐤀𐤌 (ifc != NULL_TREE)
    {
      𐤀𐤌 (OMP_CLAUSE_IF_MODIFIER (ifc) != ERROR_MARK
	  && OMP_CLAUSE_IF_MODIFIER (ifc) != VOID_CST)
	error_at (OMP_CLAUSE_LOCATION (ifc),
		  "expected %<cancel%> %<if%> clause modifier");
      وإلا
	{
	  tree ifc2 = omp_find_clause (OMP_CLAUSE_CHAIN (ifc), OMP_CLAUSE_IF);
	  𐤀𐤌 (ifc2 != NULL_TREE)
	    {
	      gcc_assert (OMP_CLAUSE_IF_MODIFIER (ifc) == VOID_CST
			  && OMP_CLAUSE_IF_MODIFIER (ifc2) != ERROR_MARK
			  && OMP_CLAUSE_IF_MODIFIER (ifc2) != VOID_CST);
	      error_at (OMP_CLAUSE_LOCATION (ifc2),
			"expected %<cancel%> %<if%> clause modifier");
	    }
	}

      tree type = TREE_TYPE (OMP_CLAUSE_IF_EXPR (ifc));
      ifc = fold_build2_loc (OMP_CLAUSE_LOCATION (ifc), NE_EXPR,
			     boolean_type_node, OMP_CLAUSE_IF_EXPR (ifc),
			     build_zero_cst (type));
    }
  وإلا
    ifc = boolean_true_node;
  tree stmt = build_call_expr_loc (loc, fn, 2,
				   build_int_cst (integer_type_node, mask),
				   ifc);
  add_stmt (stmt);
}

/* Generate GOMP_cancellation_point call for
   #pragma omp cancellation point.  */

فراغ
c_finish_omp_cancellation_point (location_t loc, tree clauses)
{
  tree fn = builtin_decl_explicit (BUILT_IN_GOMP_CANCELLATION_POINT);
  صحيح mask = 0;
  𐤀𐤌 (omp_find_clause (clauses, OMP_CLAUSE_PARALLEL))
    mask = 1;
  وإلا 𐤀𐤌 (omp_find_clause (clauses, OMP_CLAUSE_FOR))
    mask = 2;
  وإلا 𐤀𐤌 (omp_find_clause (clauses, OMP_CLAUSE_SECTIONS))
    mask = 4;
  وإلا 𐤀𐤌 (omp_find_clause (clauses, OMP_CLAUSE_TASKGROUP))
    mask = 8;
  وإلا
    {
      error_at (loc, "%<#pragma omp cancellation point%> must specify one of "
		     "%<parallel%>, %<for%>, %<sections%> or %<taskgroup%> "
		     "clauses");
      أرجع;
    }
  tree stmt = build_call_expr_loc (loc, fn, 1,
				   build_int_cst (integer_type_node, mask));
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

ساكن tree
handle_omp_array_sections_1 (tree c, tree t, vec<tree> &types,
			     منطقي &maybe_zero_len, unsigned صحيح &first_non_one,
			     تعداد c_omp_region_type ort)
{
  tree ret, low_bound, length, type;
  منطقي openacc = (ort & C_ORT_ACC) != 0;
  𐤀𐤌 (TREE_CODE (t) != OMP_ARRAY_SECTION)
    {
      𐤀𐤌 (error_operand_p (t))
	أرجع error_mark_node;
      c_omp_address_inspector ai (OMP_CLAUSE_LOCATION (c), t);
      ret = t;
      𐤀𐤌 (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_AFFINITY
	  && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_DEPEND
	  && TYPE_ATOMIC (strip_array_types (TREE_TYPE (t))))
	{
	  error_at (OMP_CLAUSE_LOCATION (c), "%<_Atomic%> %qE in %qs clause",
		    t, omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	  أرجع error_mark_node;
	}
      𐤀𐤌 (!ai.check_clause (c))
	أرجع error_mark_node;
      وإلا 𐤀𐤌 (ai.component_access_p ()
	       && (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP
		   || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_TO
		   || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_FROM))
	t = ai.get_root_term (true);
      وإلا
	t = ai.unconverted_ref_origin ();
      𐤀𐤌 (t == error_mark_node)
	أرجع error_mark_node;
      𐤀𐤌 (!VAR_P (t)
	  && (ort == C_ORT_ACC || !EXPR_P (t))
	  && TREE_CODE (t) != PARM_DECL)
	{
	  𐤀𐤌 (DECL_P (t))
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%qD is not a variable in %qs clause", t,
		      omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	  وإلا
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%qE is not a variable in %qs clause", t,
		      omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	  أرجع error_mark_node;
	}
      وإلا 𐤀𐤌 (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_AFFINITY
	       && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_DEPEND
	       && TYPE_ATOMIC (TREE_TYPE (t)))
	{
	  error_at (OMP_CLAUSE_LOCATION (c), "%<_Atomic%> %qD in %qs clause",
		    t, omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	  أرجع error_mark_node;
	}
      وإلا 𐤀𐤌 (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_AFFINITY
	       && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_DEPEND
	       && VAR_P (t)
	       && DECL_THREAD_LOCAL_P (t))
	{
	  error_at (OMP_CLAUSE_LOCATION (c),
		    "%qD is threadprivate variable in %qs clause", t,
		    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	  أرجع error_mark_node;
	}
      𐤀𐤌 ((OMP_CLAUSE_CODE (c) == OMP_CLAUSE_AFFINITY
	   || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND)
	  && TYPE_ATOMIC (TREE_TYPE (t))
	  && POINTER_TYPE_P (TREE_TYPE (t)))
	{
	  /* If the array section is pointer based and the pointer
	     itself is _Atomic qualified, we need to atomically load
	     the pointer.  */
	  ret = convert_lvalue_to_rvalue (OMP_CLAUSE_LOCATION (c),
					  ret, خطأ, خطأ);
	}
      أرجع ret;
    }

  ret = handle_omp_array_sections_1 (c, TREE_OPERAND (t, 0), types,
				     maybe_zero_len, first_non_one, ort);
  𐤀𐤌 (ret == error_mark_node || ret == NULL_TREE)
    أرجع ret;

  type = TREE_TYPE (ret);
  low_bound = TREE_OPERAND (t, 1);
  length = TREE_OPERAND (t, 2);

  𐤀𐤌 (low_bound == error_mark_node || length == error_mark_node)
    أرجع error_mark_node;

  𐤀𐤌 (low_bound && !INTEGRAL_TYPE_P (TREE_TYPE (low_bound)))
    {
      error_at (OMP_CLAUSE_LOCATION (c),
		"low bound %qE of array section does not have integral type",
		low_bound);
      أرجع error_mark_node;
    }
  𐤀𐤌 (length && !INTEGRAL_TYPE_P (TREE_TYPE (length)))
    {
      error_at (OMP_CLAUSE_LOCATION (c),
		"length %qE of array section does not have integral type",
		length);
      أرجع error_mark_node;
    }
  𐤀𐤌 (low_bound
      && TREE_CODE (low_bound) == INTEGER_CST
      && TYPE_PRECISION (TREE_TYPE (low_bound))
	 > TYPE_PRECISION (sizetype))
    low_bound = fold_convert (sizetype, low_bound);
  𐤀𐤌 (length
      && TREE_CODE (length) == INTEGER_CST
      && TYPE_PRECISION (TREE_TYPE (length))
	 > TYPE_PRECISION (sizetype))
    length = fold_convert (sizetype, length);
  𐤀𐤌 (low_bound == NULL_TREE)
    low_bound = integer_zero_node;
  𐤀𐤌 (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP
      && (OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_ATTACH
	  || OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_DETACH))
    {
      𐤀𐤌 (length != integer_one_node)
	{
	  error_at (OMP_CLAUSE_LOCATION (c),
		    "expected single pointer in %qs clause",
		    user_omp_clause_code_name (c, openacc));
	  أرجع error_mark_node;
	}
    }
  𐤀𐤌 (length != NULL_TREE)
    {
      𐤀𐤌 (!integer_nonzerop (length))
	{
	  𐤀𐤌 (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_AFFINITY
	      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND
	      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_REDUCTION
	      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IN_REDUCTION
	      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_TASK_REDUCTION)
	    {
	      𐤀𐤌 (integer_zerop (length))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "zero length array section in %qs clause",
			    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		  أرجع error_mark_node;
		}
	    }
	  وإلا
	    maybe_zero_len = true;
	}
      𐤀𐤌 (first_non_one == types.length ()
	  && (TREE_CODE (length) != INTEGER_CST || integer_onep (length)))
	first_non_one++;
    }
  𐤀𐤌 (TREE_CODE (type) == ARRAY_TYPE)
    {
      𐤀𐤌 (length == NULL_TREE
	  && (TYPE_DOMAIN (type) == NULL_TREE
	      || TYPE_MAX_VALUE (TYPE_DOMAIN (type)) == NULL_TREE))
	{
	  error_at (OMP_CLAUSE_LOCATION (c),
		    "for unknown bound array type length expression must "
		    "be specified");
	  أرجع error_mark_node;
	}
      𐤀𐤌 (TREE_CODE (low_bound) == INTEGER_CST
	  && tree_int_cst_sgn (low_bound) == -1)
	{
	  error_at (OMP_CLAUSE_LOCATION (c),
		    "negative low bound in array section in %qs clause",
		    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	  أرجع error_mark_node;
	}
      𐤀𐤌 (length != NULL_TREE
	  && TREE_CODE (length) == INTEGER_CST
	  && tree_int_cst_sgn (length) == -1)
	{
	  error_at (OMP_CLAUSE_LOCATION (c),
		    "negative length in array section in %qs clause",
		    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	  أرجع error_mark_node;
	}
      𐤀𐤌 (TYPE_DOMAIN (type)
	  && TYPE_MAX_VALUE (TYPE_DOMAIN (type))
	  && TREE_CODE (TYPE_MAX_VALUE (TYPE_DOMAIN (type)))
			== INTEGER_CST)
	{
	  tree size
	    = fold_convert (sizetype, TYPE_MAX_VALUE (TYPE_DOMAIN (type)));
	  size = size_binop (PLUS_EXPR, size, size_one_node);
	  𐤀𐤌 (TREE_CODE (low_bound) == INTEGER_CST)
	    {
	      𐤀𐤌 (tree_int_cst_lt (size, low_bound))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "low bound %qE above array section size "
			    "in %qs clause", low_bound,
			    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		  أرجع error_mark_node;
		}
	      𐤀𐤌 (tree_int_cst_equal (size, low_bound))
		{
		  𐤀𐤌 (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_AFFINITY
		      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND
		      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_REDUCTION
		      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IN_REDUCTION
		      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_TASK_REDUCTION)
		    {
		      error_at (OMP_CLAUSE_LOCATION (c),
				"zero length array section in %qs clause",
				omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		      أرجع error_mark_node;
		    }
		  maybe_zero_len = true;
		}
	      وإلا 𐤀𐤌 (length == NULL_TREE
		       && first_non_one == types.length ()
		       && tree_int_cst_equal
			    (TYPE_MAX_VALUE (TYPE_DOMAIN (type)),
			     low_bound))
		first_non_one++;
	    }
	  وإلا 𐤀𐤌 (length == NULL_TREE)
	    {
	      𐤀𐤌 (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_AFFINITY
		  && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_DEPEND
		  && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_REDUCTION
		  && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_IN_REDUCTION
		  && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_TASK_REDUCTION)
		maybe_zero_len = true;
	      𐤀𐤌 (first_non_one == types.length ())
		first_non_one++;
	    }
	  𐤀𐤌 (length && TREE_CODE (length) == INTEGER_CST)
	    {
	      𐤀𐤌 (tree_int_cst_lt (size, length))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "length %qE above array section size "
			    "in %qs clause", length,
			    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		  أرجع error_mark_node;
		}
	      𐤀𐤌 (TREE_CODE (low_bound) == INTEGER_CST)
		{
		  tree lbpluslen
		    = size_binop (PLUS_EXPR,
				  fold_convert (sizetype, low_bound),
				  fold_convert (sizetype, length));
		  𐤀𐤌 (TREE_CODE (lbpluslen) == INTEGER_CST
		      && tree_int_cst_lt (size, lbpluslen))
		    {
		      error_at (OMP_CLAUSE_LOCATION (c),
				"high bound %qE above array section size "
				"in %qs clause", lbpluslen,
				omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		      أرجع error_mark_node;
		    }
		}
	    }
	}
      وإلا 𐤀𐤌 (length == NULL_TREE)
	{
	  𐤀𐤌 (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_AFFINITY
	      && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_DEPEND
	      && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_REDUCTION
	      && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_IN_REDUCTION
	      && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_TASK_REDUCTION)
	    maybe_zero_len = true;
	  𐤀𐤌 (first_non_one == types.length ())
	    first_non_one++;
	}

      /* For [lb:] we will need to evaluate lb more than once.  */
      𐤀𐤌 (length == NULL_TREE && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_DEPEND)
	{
	  tree lb = save_expr (low_bound);
	  𐤀𐤌 (lb != low_bound)
	    {
	      TREE_OPERAND (t, 1) = lb;
	      low_bound = lb;
	    }
	}
    }
  وإلا 𐤀𐤌 (TREE_CODE (type) == POINTER_TYPE)
    {
      𐤀𐤌 (length == NULL_TREE)
	{
	  𐤀𐤌 (TREE_CODE (ret) == PARM_DECL && C_ARRAY_PARAMETER (ret))
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "for array function parameter length expression "
		      "must be specified");
	  وإلا
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "for pointer type length expression must be specified");
	  أرجع error_mark_node;
	}
      𐤀𐤌 (length != NULL_TREE
	  && TREE_CODE (length) == INTEGER_CST
	  && tree_int_cst_sgn (length) == -1)
	{
	  error_at (OMP_CLAUSE_LOCATION (c),
		    "negative length in array section in %qs clause",
		    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	  أرجع error_mark_node;
	}
      /* If there is a pointer type anywhere but in the very first
	 array-section-subscript, the array section could be non-contiguous.  */
      𐤀𐤌 (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_DEPEND
	  && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_AFFINITY
	  && TREE_CODE (TREE_OPERAND (t, 0)) == OMP_ARRAY_SECTION)
	{
	  /* If any prior dimension has a non-one length, then deem this
	     array section as non-contiguous.  */
	  لكل (tree d = TREE_OPERAND (t, 0);
	       TREE_CODE (d) == OMP_ARRAY_SECTION;
	       d = TREE_OPERAND (d, 0))
	    {
	      tree d_length = TREE_OPERAND (d, 2);
	      𐤀𐤌 (d_length == NULL_TREE || !integer_onep (d_length))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "array section is not contiguous in %qs clause",
			    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		  أرجع error_mark_node;
		}
	    }
	}
    }
  وإلا
    {
      error_at (OMP_CLAUSE_LOCATION (c),
		"%qE does not have pointer or array type", ret);
      أرجع error_mark_node;
    }
  𐤀𐤌 (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_DEPEND)
    types.safe_push (TREE_TYPE (ret));
  /* We will need to evaluate lb more than once.  */
  tree lb = save_expr (low_bound);
  𐤀𐤌 (lb != low_bound)
    {
      TREE_OPERAND (t, 1) = lb;
      low_bound = lb;
    }
  ret = build_array_ref (OMP_CLAUSE_LOCATION (c), ret, low_bound);
  أرجع ret;
}

/* Handle array sections for clause C.  */

ساكن منطقي
handle_omp_array_sections (tree &c, تعداد c_omp_region_type ort)
{
  منطقي maybe_zero_len = خطأ;
  unsigned صحيح first_non_one = 0;
  auto_vec<tree, 10> types;
  tree *tp = &OMP_CLAUSE_DECL (c);
  𐤀𐤌 ((OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND
       || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_AFFINITY)
      && OMP_ITERATOR_DECL_P (*tp))
    tp = &TREE_VALUE (*tp);
  tree first = handle_omp_array_sections_1 (c, *tp, types,
					    maybe_zero_len, first_non_one,
					    ort);
  𐤀𐤌 (first == error_mark_node)
    أرجع true;
  𐤀𐤌 (first == NULL_TREE)
    أرجع خطأ;
  𐤀𐤌 (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND
      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_AFFINITY)
    {
      tree t = *tp;
      tree tem = NULL_TREE;
      /* Need to evaluate side effects in the length expressions
	 if any.  */
      طالما (TREE_CODE (t) == TREE_LIST)
	{
	  𐤀𐤌 (TREE_VALUE (t) && TREE_SIDE_EFFECTS (TREE_VALUE (t)))
	    {
	      𐤀𐤌 (tem == NULL_TREE)
		tem = TREE_VALUE (t);
	      وإلا
		tem = build2 (COMPOUND_EXPR, TREE_TYPE (tem),
			      TREE_VALUE (t), tem);
	    }
	  t = TREE_CHAIN (t);
	}
      𐤀𐤌 (tem)
	first = build2 (COMPOUND_EXPR, TREE_TYPE (first), tem, first);
      first = c_fully_fold (first, خطأ, عدم, true);
      *tp = first;
    }
  وإلا
    {
      unsigned صحيح num = types.length (), i;
      tree t, side_effects = NULL_TREE, size = NULL_TREE;
      tree condition = NULL_TREE;

      𐤀𐤌 (int_size_in_bytes (TREE_TYPE (first)) <= 0)
	maybe_zero_len = true;

      لكل (i = num, t = OMP_CLAUSE_DECL (c); i > 0;
	   t = TREE_OPERAND (t, 0))
	{
	  tree low_bound = TREE_OPERAND (t, 1);
	  tree length = TREE_OPERAND (t, 2);

	  i--;
	  𐤀𐤌 (low_bound
	      && TREE_CODE (low_bound) == INTEGER_CST
	      && TYPE_PRECISION (TREE_TYPE (low_bound))
		 > TYPE_PRECISION (sizetype))
	    low_bound = fold_convert (sizetype, low_bound);
	  𐤀𐤌 (length
	      && TREE_CODE (length) == INTEGER_CST
	      && TYPE_PRECISION (TREE_TYPE (length))
		 > TYPE_PRECISION (sizetype))
	    length = fold_convert (sizetype, length);
	  𐤀𐤌 (low_bound == NULL_TREE)
	    low_bound = integer_zero_node;
	  𐤀𐤌 (!maybe_zero_len && i > first_non_one)
	    {
	      𐤀𐤌 (integer_nonzerop (low_bound))
		اذهب do_warn_noncontiguous;
	      𐤀𐤌 (length != NULL_TREE
		  && TREE_CODE (length) == INTEGER_CST
		  && TYPE_DOMAIN (types[i])
		  && TYPE_MAX_VALUE (TYPE_DOMAIN (types[i]))
		  && TREE_CODE (TYPE_MAX_VALUE (TYPE_DOMAIN (types[i])))
		     == INTEGER_CST)
		{
		  tree size;
		  size = size_binop (PLUS_EXPR,
				     TYPE_MAX_VALUE (TYPE_DOMAIN (types[i])),
				     size_one_node);
		  𐤀𐤌 (!tree_int_cst_equal (length, size))
		    {
		     do_warn_noncontiguous:
		      error_at (OMP_CLAUSE_LOCATION (c),
				"array section is not contiguous in %qs "
				"clause",
				omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		      أرجع true;
		    }
		}
	      𐤀𐤌 (length != NULL_TREE
		  && TREE_SIDE_EFFECTS (length))
		{
		  𐤀𐤌 (side_effects == NULL_TREE)
		    side_effects = length;
		  وإلا
		    side_effects = build2 (COMPOUND_EXPR,
					   TREE_TYPE (side_effects),
					   length, side_effects);
		}
	    }
	  وإلا
	    {
	      tree l;

	      𐤀𐤌 (i > first_non_one
		  && ((length && integer_nonzerop (length))
		      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_REDUCTION
		      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IN_REDUCTION
		      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_TASK_REDUCTION))
		استمر;
	      𐤀𐤌 (length)
		l = fold_convert (sizetype, length);
	      وإلا
		{
		  l = size_binop (PLUS_EXPR,
				  TYPE_MAX_VALUE (TYPE_DOMAIN (types[i])),
				  size_one_node);
		  l = size_binop (MINUS_EXPR, l,
				  fold_convert (sizetype, low_bound));
		}
	      𐤀𐤌 (i > first_non_one)
		{
		  l = fold_build2 (NE_EXPR, boolean_type_node, l,
				   size_zero_node);
		  𐤀𐤌 (condition == NULL_TREE)
		    condition = l;
		  وإلا
		    condition = fold_build2 (BIT_AND_EXPR, boolean_type_node,
					     l, condition);
		}
	      وإلا 𐤀𐤌 (size == NULL_TREE)
		{
		  size = size_in_bytes (TREE_TYPE (types[i]));
		  tree eltype = TREE_TYPE (types[num - 1]);
		  طالما (TREE_CODE (eltype) == ARRAY_TYPE)
		    eltype = TREE_TYPE (eltype);
		  𐤀𐤌 (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_REDUCTION
		      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IN_REDUCTION
		      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_TASK_REDUCTION)
		    {
		      𐤀𐤌 (integer_zerop (size)
			  || integer_zerop (size_in_bytes (eltype)))
			{
			  error_at (OMP_CLAUSE_LOCATION (c),
				    "zero length array section in %qs clause",
				    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
			  أرجع error_mark_node;
			}
		      size = size_binop (EXACT_DIV_EXPR, size,
					 size_in_bytes (eltype));
		    }
		  size = size_binop (MULT_EXPR, size, l);
		  𐤀𐤌 (condition)
		    size = fold_build3 (COND_EXPR, sizetype, condition,
					size, size_zero_node);
		}
	      وإلا
		size = size_binop (MULT_EXPR, size, l);
	    }
	}
      𐤀𐤌 (side_effects)
	size = build2 (COMPOUND_EXPR, sizetype, side_effects, size);
      𐤀𐤌 (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_REDUCTION
	  || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IN_REDUCTION
	  || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_TASK_REDUCTION)
	{
	  size = size_binop (MINUS_EXPR, size, size_one_node);
	  size = c_fully_fold (size, خطأ, عدم);
	  size = save_expr (size);
	  tree index_type = build_index_type (size);
	  tree eltype = TREE_TYPE (first);
	  طالما (TREE_CODE (eltype) == ARRAY_TYPE)
	    eltype = TREE_TYPE (eltype);
	  tree type = c_build_array_type (eltype, index_type);
	  tree ptype = c_build_pointer_type (eltype);
	  𐤀𐤌 (TREE_CODE (TREE_TYPE (t)) == ARRAY_TYPE)
	    t = build_fold_addr_expr (t);
	  tree t2 = build_fold_addr_expr (first);
	  t2 = fold_convert_loc (OMP_CLAUSE_LOCATION (c),
				 ptrdiff_type_node, t2);
	  t2 = fold_build2_loc (OMP_CLAUSE_LOCATION (c), MINUS_EXPR,
				ptrdiff_type_node, t2,
				fold_convert_loc (OMP_CLAUSE_LOCATION (c),
						  ptrdiff_type_node, t));
	  t2 = c_fully_fold (t2, خطأ, عدم);
	  𐤀𐤌 (tree_fits_shwi_p (t2))
	    t = build2 (MEM_REF, type, t,
			build_int_cst (ptype, tree_to_shwi (t2)));
	  وإلا
	    {
	      t2 = fold_convert_loc (OMP_CLAUSE_LOCATION (c), sizetype, t2);
	      t = build2_loc (OMP_CLAUSE_LOCATION (c), POINTER_PLUS_EXPR,
			      TREE_TYPE (t), t, t2);
	      t = build2 (MEM_REF, type, t, build_int_cst (ptype, 0));
	    }
	  OMP_CLAUSE_DECL (c) = t;
	  أرجع خطأ;
	}
      first = c_fully_fold (first, خطأ, عدم);
      OMP_CLAUSE_DECL (c) = first;
      𐤀𐤌 (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_HAS_DEVICE_ADDR)
	أرجع خطأ;
      /* Don't set OMP_CLAUSE_SIZE for bare attach/detach clauses.  */
      𐤀𐤌 (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_MAP
	  || (OMP_CLAUSE_MAP_KIND (c) != GOMP_MAP_ATTACH
	      && OMP_CLAUSE_MAP_KIND (c) != GOMP_MAP_DETACH
	      && OMP_CLAUSE_MAP_KIND (c) != GOMP_MAP_FORCE_DETACH))
	{
	  𐤀𐤌 (size)
	    size = c_fully_fold (size, خطأ, عدم);
	  OMP_CLAUSE_SIZE (c) = size;
	}

      𐤀𐤌 (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_MAP)
	أرجع خطأ;

      auto_vec<omp_addr_token *, 10> addr_tokens;

      𐤀𐤌 (!omp_parse_expr (addr_tokens, first))
	أرجع true;

      c_omp_address_inspector ai (OMP_CLAUSE_LOCATION (c), t);

      tree nc = ai.expand_map_clause (c, first, addr_tokens, ort);
      𐤀𐤌 (nc != error_mark_node)
	{
	  using نطاق omp_addr_tokenizer;

	  𐤀𐤌 (ai.maybe_zero_length_array_section (c))
	    OMP_CLAUSE_MAP_MAYBE_ZERO_LENGTH_ARRAY_SECTION (c) = 1;

	  /* !!! If we're accessing a base decl via chained access
	     methods (e.g. multiple indirections), duplicate clause
	     detection won't work properly.  Skip it in that case.  */
	  𐤀𐤌 ((addr_tokens[0]->type == STRUCTURE_BASE
	       || addr_tokens[0]->type == ARRAY_BASE)
	      && addr_tokens[0]->u.structure_base_kind == BASE_DECL
	      && addr_tokens[1]->type == ACCESS_METHOD
	      && omp_access_chain_p (addr_tokens, 1))
	    c = nc;

	  أرجع خطأ;
	}
    }
  أرجع خطأ;
}

/* Helper function of finish_omp_clauses.  Clone STMT as if we were making
   an inline call.  But, remap
   the OMP_DECL1 VAR_DECL (omp_out resp. omp_orig) to PLACEHOLDER
   and OMP_DECL2 VAR_DECL (omp_in resp. omp_priv) to DECL.  */

ساكن tree
c_clone_omp_udr (tree stmt, tree omp_decl1, tree omp_decl2,
		 tree decl, tree placeholder)
{
  copy_body_data id;
  hash_map<tree, tree> decl_map;

  decl_map.put (omp_decl1, placeholder);
  decl_map.put (omp_decl2, decl);
  memset (&id, 0, حجم (id));
  id.src_fn = DECL_CONTEXT (omp_decl1);
  id.dst_fn = current_function_decl;
  id.src_cfun = DECL_STRUCT_FUNCTION (id.src_fn);
  id.decl_map = &decl_map;

  id.copy_decl = copy_decl_no_change;
  id.transform_call_graph_edges = CB_CGE_DUPLICATE;
  id.transform_new_cfg = true;
  id.transform_return_to_modify = خطأ;
  id.eh_lp_nr = 0;
  walk_tree (&stmt, copy_tree_body_r, &id, عدم);
  أرجع stmt;
}

/* Helper function of c_finish_omp_clauses, called via walk_tree.
   Find OMP_CLAUSE_PLACEHOLDER (passed in DATA) in *TP.  */

ساكن tree
c_find_omp_placeholder_r (tree *tp, صحيح *, فراغ *data)
{
  𐤀𐤌 (*tp == (tree) data)
    أرجع *tp;
  أرجع NULL_TREE;
}

/* Similarly, but also walk aggregate fields.  */

بنية c_find_omp_var_s { tree var; hash_set<tree> *pset; };

ساكن tree
c_find_omp_var_r (tree *tp, صحيح *, فراغ *data)
{
  𐤀𐤌 (*tp == ((بنية c_find_omp_var_s *) data)->var)
    أرجع *tp;
  𐤀𐤌 (RECORD_OR_UNION_TYPE_P (*tp))
    {
      tree field;
      hash_set<tree> *pset = ((بنية c_find_omp_var_s *) data)->pset;

      لكل (field = TYPE_FIELDS (*tp); field;
	   field = DECL_CHAIN (field))
	𐤀𐤌 (TREE_CODE (field) == FIELD_DECL)
	  {
	    tree ret = walk_tree (&DECL_FIELD_OFFSET (field),
				  c_find_omp_var_r, data, pset);
	    𐤀𐤌 (ret)
	      أرجع ret;
	    ret = walk_tree (&DECL_SIZE (field), c_find_omp_var_r, data, pset);
	    𐤀𐤌 (ret)
	      أرجع ret;
	    ret = walk_tree (&DECL_SIZE_UNIT (field), c_find_omp_var_r, data,
			     pset);
	    𐤀𐤌 (ret)
	      أرجع ret;
	    ret = walk_tree (&TREE_TYPE (field), c_find_omp_var_r, data, pset);
	    𐤀𐤌 (ret)
	      أرجع ret;
	  }
    }
  وإلا 𐤀𐤌 (INTEGRAL_TYPE_P (*tp))
    أرجع walk_tree (&TYPE_MAX_VALUE (*tp), c_find_omp_var_r, data,
		      ((بنية c_find_omp_var_s *) data)->pset);
  أرجع NULL_TREE;
}

/* Finish OpenMP iterators ITER.  Return true if they are erroneous
   and clauses containing them should be removed.  */

ساكن منطقي
c_omp_finish_iterators (tree iter)
{
  منطقي ret = خطأ;
  لكل (tree it = iter; it; it = TREE_CHAIN (it))
    {
      tree var = OMP_ITERATOR_VAR (it);
      tree begin = OMP_ITERATOR_BEGIN (it);
      tree end = OMP_ITERATOR_END (it);
      tree step = OMP_ITERATOR_STEP (it);
      tree orig_step;
      tree type = TREE_TYPE (var);
      location_t loc = DECL_SOURCE_LOCATION (var);
      𐤀𐤌 (type == error_mark_node)
	{
	  ret = true;
	  استمر;
	}
      𐤀𐤌 (!INTEGRAL_TYPE_P (type) && !POINTER_TYPE_P (type))
	{
	  error_at (loc, "iterator %qD has neither integral nor pointer type",
		    var);
	  ret = true;
	  استمر;
	}
      وإلا 𐤀𐤌 (TYPE_ATOMIC (type))
	{
	  error_at (loc, "iterator %qD has %<_Atomic%> qualified type", var);
	  ret = true;
	  استمر;
	}
      وإلا 𐤀𐤌 (TYPE_READONLY (type))
	{
	  error_at (loc, "iterator %qD has const qualified type", var);
	  ret = true;
	  استمر;
	}
      وإلا 𐤀𐤌 (step == error_mark_node
	       || TREE_TYPE (step) == error_mark_node)
	{
	  ret = true;
	  استمر;
	}
      وإلا 𐤀𐤌 (!INTEGRAL_TYPE_P (TREE_TYPE (step)))
	{
	  error_at (EXPR_LOC_OR_LOC (step, loc),
		    "iterator step with non-integral type");
	  ret = true;
	  استمر;
	}
      begin = c_fully_fold (build_c_cast (loc, type, begin), خطأ, عدم);
      end = c_fully_fold (build_c_cast (loc, type, end), خطأ, عدم);
      orig_step = save_expr (c_fully_fold (step, خطأ, عدم));
      tree stype = POINTER_TYPE_P (type) ? sizetype : type;
      step = c_fully_fold (build_c_cast (loc, stype, orig_step), خطأ, عدم);
      𐤀𐤌 (POINTER_TYPE_P (type))
	{
	  begin = save_expr (begin);
	  step = pointer_int_sum (loc, PLUS_EXPR, begin, step);
	  step = fold_build2_loc (loc, MINUS_EXPR, sizetype,
				  fold_convert (sizetype, step),
				  fold_convert (sizetype, begin));
	  step = fold_convert (ssizetype, step);
	}
      𐤀𐤌 (integer_zerop (step))
	{
	  error_at (loc, "iterator %qD has zero step", var);
	  ret = true;
	  استمر;
	}

      𐤀𐤌 (begin == error_mark_node
	  || end == error_mark_node
	  || step == error_mark_node
	  || orig_step == error_mark_node)
	{
	  ret = true;
	  استمر;
	}
      hash_set<tree> pset;
      tree it2;
      لكل (it2 = TREE_CHAIN (it); it2; it2 = TREE_CHAIN (it2))
	{
	  tree var2 = OMP_ITERATOR_VAR (it2);
	  tree begin2 = OMP_ITERATOR_BEGIN (it2);
	  tree end2 = OMP_ITERATOR_END (it2);
	  tree step2 = OMP_ITERATOR_STEP (it2);
	  tree type2 = TREE_TYPE (var2);
	  location_t loc2 = DECL_SOURCE_LOCATION (var2);
	  بنية c_find_omp_var_s data = { var, &pset };
	  𐤀𐤌 (walk_tree (&type2, c_find_omp_var_r, &data, &pset))
	    {
	      error_at (loc2,
			"type of iterator %qD refers to outer iterator %qD",
			var2, var);
	      اكسر;
	    }
	  وإلا 𐤀𐤌 (walk_tree (&begin2, c_find_omp_var_r, &data, &pset))
	    {
	      error_at (EXPR_LOC_OR_LOC (begin2, loc2),
			"begin expression refers to outer iterator %qD", var);
	      اكسر;
	    }
	  وإلا 𐤀𐤌 (walk_tree (&end2, c_find_omp_var_r, &data, &pset))
	    {
	      error_at (EXPR_LOC_OR_LOC (end2, loc2),
			"end expression refers to outer iterator %qD", var);
	      اكسر;
	    }
	  وإلا 𐤀𐤌 (walk_tree (&step2, c_find_omp_var_r, &data, &pset))
	    {
	      error_at (EXPR_LOC_OR_LOC (step2, loc2),
			"step expression refers to outer iterator %qD", var);
	      اكسر;
	    }
	}
      𐤀𐤌 (it2)
	{
	  ret = true;
	  استمر;
	}
      OMP_ITERATOR_BEGIN (it) = begin;
      OMP_ITERATOR_END (it) = end;
      OMP_ITERATOR_STEP (it) = step;
      OMP_ITERATOR_ORIG_STEP (it) = orig_step;
    }
  أرجع ret;
}

/* Ensure that pointers are used in OpenACC attach and detach clauses.
   Return true if an error has been detected.  */

ساكن منطقي
c_oacc_check_attachments (tree c)
{
  𐤀𐤌 (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_MAP)
    أرجع خطأ;

  /* OpenACC attach / detach clauses must be pointers.  */
  𐤀𐤌 (OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_ATTACH
      || OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_DETACH)
    {
      tree t = OMP_CLAUSE_DECL (c);

      طالما (TREE_CODE (t) == OMP_ARRAY_SECTION)
	t = TREE_OPERAND (t, 0);

      𐤀𐤌 (TREE_CODE (TREE_TYPE (t)) != POINTER_TYPE)
	{
	  error_at (OMP_CLAUSE_LOCATION (c), "expected pointer in %qs clause",
		    user_omp_clause_code_name (c, true));
	  أرجع true;
	}
    }

  أرجع خطأ;
}

/* For all elements of CLAUSES, validate them against their constraints.
   Remove any elements from the list that are invalid.  */

tree
c_finish_omp_clauses (tree clauses, تعداد c_omp_region_type ort)
{
  bitmap_head generic_head, firstprivate_head, lastprivate_head;
  bitmap_head aligned_head, map_head, map_field_head, map_firstprivate_head;
  bitmap_head oacc_reduction_head, is_on_device_head;
  tree c, t, type, *pc;
  tree simdlen = NULL_TREE, safelen = NULL_TREE;
  منطقي branch_seen = خطأ;
  منطقي copyprivate_seen = خطأ;
  منطقي mergeable_seen = خطأ;
  tree *detach_seen = عدم;
  منطقي linear_variable_step_check = خطأ;
  tree *nowait_clause = عدم;
  tree *grainsize_seen = عدم;
  منطقي num_tasks_seen = خطأ;
  tree ordered_clause = NULL_TREE;
  tree schedule_clause = NULL_TREE;
  منطقي oacc_async = خطأ;
  tree last_iterators = NULL_TREE;
  منطقي last_iterators_remove = خطأ;
  tree *nogroup_seen = عدم;
  tree *order_clause = عدم;
  /* 1 if normal/task reduction has been seen, -1 if inscan reduction
     has been seen, -2 if mixed inscan/normal reduction diagnosed.  */
  صحيح reduction_seen = 0;
  منطقي allocate_seen = خطأ;
  منطقي implicit_moved = خطأ;
  منطقي target_in_reduction_seen = خطأ;
  tree *full_seen = عدم;
  منطقي partial_seen = خطأ;
  منطقي openacc = (ort & C_ORT_ACC) != 0;
  منطقي init_seen = خطأ;
  منطقي init_use_destroy_seen = خطأ;
  tree init_no_targetsync_clause = NULL_TREE;
  tree depend_clause = NULL_TREE;

  𐤀𐤌 (!openacc)
    clauses = omp_remove_duplicate_maps (clauses, true);

  bitmap_obstack_initialize (عدم);
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

  𐤀𐤌 (openacc)
    لكل (c = clauses; c; c = OMP_CLAUSE_CHAIN (c))
      𐤀𐤌 (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_ASYNC)
	{
	  oacc_async = true;
	  اكسر;
	}

  tree *grp_start_p = عدم, grp_sentinel = NULL_TREE;

  لكل (pc = &clauses, c = clauses; c ; c = *pc)
    {
      منطقي remove = خطأ;
      منطقي need_complete = خطأ;
      منطقي need_implicitly_determined = خطأ;

      /* We've reached the end of a list of expanded nodes.  Reset the group
	 start pointer.  */
      𐤀𐤌 (c == grp_sentinel)
	{
	  𐤀𐤌 (grp_start_p
	      && OMP_CLAUSE_HAS_ITERATORS (*grp_start_p))
	    لكل (tree gc = *grp_start_p; gc != grp_sentinel;
		 gc = OMP_CLAUSE_CHAIN (gc))
	      OMP_CLAUSE_ITERATORS (gc) = OMP_CLAUSE_ITERATORS (*grp_start_p);
	  grp_start_p = عدم;
	}

      بدل (OMP_CLAUSE_CODE (c))
	{
	حالة OMP_CLAUSE_SHARED:
	  need_implicitly_determined = true;
	  اذهب check_dup_generic;

	حالة OMP_CLAUSE_PRIVATE:
	  need_complete = true;
	  need_implicitly_determined = true;
	  اذهب check_dup_generic;

	حالة OMP_CLAUSE_REDUCTION:
	  𐤀𐤌 (reduction_seen == 0)
	    reduction_seen = OMP_CLAUSE_REDUCTION_INSCAN (c) ? -1 : 1;
	  وإلا 𐤀𐤌 (reduction_seen != -2
		   && reduction_seen != (OMP_CLAUSE_REDUCTION_INSCAN (c)
					 ? -1 : 1))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<inscan%> and non-%<inscan%> %<reduction%> clauses "
			"on the same construct");
	      reduction_seen = -2;
	    }
	  /* FALLTHRU */
	حالة OMP_CLAUSE_IN_REDUCTION:
	حالة OMP_CLAUSE_TASK_REDUCTION:
	  need_implicitly_determined = true;
	  t = OMP_CLAUSE_DECL (c);
	  𐤀𐤌 (TREE_CODE (t) == OMP_ARRAY_SECTION)
	    {
	      𐤀𐤌 (handle_omp_array_sections (c, ort))
		{
		  remove = true;
		  اكسر;
		}

	      t = OMP_CLAUSE_DECL (c);
	      𐤀𐤌 (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_REDUCTION
		  && OMP_CLAUSE_REDUCTION_INSCAN (c))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%<inscan%> %<reduction%> clause with array "
			    "section");
		  remove = true;
		  اكسر;
		}
	    }
	  t = require_complete_type (OMP_CLAUSE_LOCATION (c), t);
	  𐤀𐤌 (t == error_mark_node)
	    {
	      remove = true;
	      اكسر;
	    }
	  𐤀𐤌 (oacc_async)
	    c_mark_addressable (t);
	  type = TREE_TYPE (t);
	  𐤀𐤌 (TREE_CODE (t) == MEM_REF)
	    type = TREE_TYPE (type);
	  𐤀𐤌 (TREE_CODE (type) == ARRAY_TYPE)
	    {
	      tree oatype = type;
	      gcc_assert (TREE_CODE (t) != MEM_REF);
	      طالما (TREE_CODE (type) == ARRAY_TYPE)
		type = TREE_TYPE (type);
	      𐤀𐤌 (integer_zerop (TYPE_SIZE_UNIT (type)))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD in %<reduction%> clause is a zero size array",
			    t);
		  remove = true;
		  اكسر;
		}
	      tree size = size_binop (EXACT_DIV_EXPR, TYPE_SIZE_UNIT (oatype),
				      TYPE_SIZE_UNIT (type));
	      𐤀𐤌 (integer_zerop (size))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD in %<reduction%> clause is a zero size array",
			    t);
		  remove = true;
		  اكسر;
		}
	      size = size_binop (MINUS_EXPR, size, size_one_node);
	      size = save_expr (size);
	      tree index_type = build_index_type (size);
	      tree atype = c_build_array_type (TYPE_MAIN_VARIANT (type),
					       index_type);
	      atype = c_build_qualified_type (atype, TYPE_QUALS (type));
	      tree ptype = c_build_pointer_type (type);
	      𐤀𐤌 (TREE_CODE (TREE_TYPE (t)) == ARRAY_TYPE)
		t = build_fold_addr_expr (t);
	      t = build2 (MEM_REF, atype, t, build_int_cst (ptype, 0));
	      OMP_CLAUSE_DECL (c) = t;
	    }
	  𐤀𐤌 (TYPE_ATOMIC (type))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<_Atomic%> %qE in %<reduction%> clause", t);
	      remove = true;
	      اكسر;
	    }
	  𐤀𐤌 (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_REDUCTION
	      || OMP_CLAUSE_REDUCTION_TASK (c))
	    {
	      /* Disallow zero sized or potentially zero sized task
		 reductions.  */
	      𐤀𐤌 (integer_zerop (TYPE_SIZE_UNIT (type)))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "zero sized type %qT in %qs clause", type,
			    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		  remove = true;
		  اكسر;
		}
	      وإلا 𐤀𐤌 (TREE_CODE (TYPE_SIZE_UNIT (type)) != INTEGER_CST)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "variable sized type %qT in %qs clause", type,
			    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		  remove = true;
		  اكسر;
		}
	    }
	  𐤀𐤌 (OMP_CLAUSE_REDUCTION_PLACEHOLDER (c) == NULL_TREE
	      && (FLOAT_TYPE_P (type)
		  || TREE_CODE (type) == COMPLEX_TYPE))
	    {
	      تعداد tree_code r_code = OMP_CLAUSE_REDUCTION_CODE (c);
	      ثابت حرف *r_name = عدم;

	      بدل (r_code)
		{
		حالة PLUS_EXPR:
		حالة MULT_EXPR:
		حالة MINUS_EXPR:
		حالة TRUTH_ANDIF_EXPR:
		حالة TRUTH_ORIF_EXPR:
		  اكسر;
		حالة MIN_EXPR:
		  𐤀𐤌 (TREE_CODE (type) == COMPLEX_TYPE)
		    r_name = "min";
		  اكسر;
		حالة MAX_EXPR:
		  𐤀𐤌 (TREE_CODE (type) == COMPLEX_TYPE)
		    r_name = "max";
		  اكسر;
		حالة BIT_AND_EXPR:
		  r_name = "&";
		  اكسر;
		حالة BIT_XOR_EXPR:
		  r_name = "^";
		  اكسر;
		حالة BIT_IOR_EXPR:
		  r_name = "|";
		  اكسر;
		افتراضي:
		  gcc_unreachable ();
		}
	      𐤀𐤌 (r_name)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qE has invalid type for %<reduction(%s)%>",
			    t, r_name);
		  remove = true;
		  اكسر;
		}
	    }
	  وإلا 𐤀𐤌 (OMP_CLAUSE_REDUCTION_PLACEHOLDER (c) == error_mark_node)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"user defined reduction not found for %qE", t);
	      remove = true;
	      اكسر;
	    }
	  وإلا 𐤀𐤌 (OMP_CLAUSE_REDUCTION_PLACEHOLDER (c))
	    {
	      tree list = OMP_CLAUSE_REDUCTION_PLACEHOLDER (c);
	      type = TYPE_MAIN_VARIANT (type);
	      tree placeholder = build_decl (OMP_CLAUSE_LOCATION (c),
					     VAR_DECL, NULL_TREE, type);
	      tree decl_placeholder = NULL_TREE;
	      OMP_CLAUSE_REDUCTION_PLACEHOLDER (c) = placeholder;
	      DECL_ARTIFICIAL (placeholder) = 1;
	      DECL_IGNORED_P (placeholder) = 1;
	      𐤀𐤌 (TREE_CODE (t) == MEM_REF)
		{
		  decl_placeholder = build_decl (OMP_CLAUSE_LOCATION (c),
						 VAR_DECL, NULL_TREE, type);
		  OMP_CLAUSE_REDUCTION_DECL_PLACEHOLDER (c) = decl_placeholder;
		  DECL_ARTIFICIAL (decl_placeholder) = 1;
		  DECL_IGNORED_P (decl_placeholder) = 1;
		}
	      𐤀𐤌 (TREE_ADDRESSABLE (TREE_VEC_ELT (list, 0)))
		c_mark_addressable (placeholder);
	      𐤀𐤌 (TREE_ADDRESSABLE (TREE_VEC_ELT (list, 1)))
		c_mark_addressable (decl_placeholder ? decl_placeholder
				    : OMP_CLAUSE_DECL (c));
	      OMP_CLAUSE_REDUCTION_MERGE (c)
		= c_clone_omp_udr (TREE_VEC_ELT (list, 2),
				   TREE_VEC_ELT (list, 0),
				   TREE_VEC_ELT (list, 1),
				   decl_placeholder ? decl_placeholder
				   : OMP_CLAUSE_DECL (c), placeholder);
	      OMP_CLAUSE_REDUCTION_MERGE (c)
		= build3_loc (OMP_CLAUSE_LOCATION (c), BIND_EXPR,
			      void_type_node, NULL_TREE,
			      OMP_CLAUSE_REDUCTION_MERGE (c), NULL_TREE);
	      TREE_SIDE_EFFECTS (OMP_CLAUSE_REDUCTION_MERGE (c)) = 1;
	      𐤀𐤌 (TREE_VEC_LENGTH (list) == 6)
		{
		  𐤀𐤌 (TREE_ADDRESSABLE (TREE_VEC_ELT (list, 3)))
		    c_mark_addressable (decl_placeholder ? decl_placeholder
					: OMP_CLAUSE_DECL (c));
		  𐤀𐤌 (TREE_ADDRESSABLE (TREE_VEC_ELT (list, 4)))
		    c_mark_addressable (placeholder);
		  tree init = TREE_VEC_ELT (list, 5);
		  𐤀𐤌 (init == error_mark_node)
		    init = DECL_INITIAL (TREE_VEC_ELT (list, 3));
		  OMP_CLAUSE_REDUCTION_INIT (c)
		    = c_clone_omp_udr (init, TREE_VEC_ELT (list, 4),
				       TREE_VEC_ELT (list, 3),
				       decl_placeholder ? decl_placeholder
				       : OMP_CLAUSE_DECL (c), placeholder);
		  𐤀𐤌 (TREE_VEC_ELT (list, 5) == error_mark_node)
		    {
		      tree v = decl_placeholder ? decl_placeholder : t;
		      OMP_CLAUSE_REDUCTION_INIT (c)
			= build2 (INIT_EXPR, TREE_TYPE (v), v,
				  OMP_CLAUSE_REDUCTION_INIT (c));
		    }
		  𐤀𐤌 (walk_tree (&OMP_CLAUSE_REDUCTION_INIT (c),
				 c_find_omp_placeholder_r,
				 placeholder, عدم))
		    OMP_CLAUSE_REDUCTION_OMP_ORIG_REF (c) = 1;
		}
	      وإلا
		{
		  tree init;
		  tree v = decl_placeholder ? decl_placeholder : t;
		  𐤀𐤌 (AGGREGATE_TYPE_P (TREE_TYPE (v)))
		    init = build_constructor (TREE_TYPE (v), عدم);
		  وإلا
		    init = fold_convert (TREE_TYPE (v), integer_zero_node);
		  OMP_CLAUSE_REDUCTION_INIT (c)
		    = build2 (INIT_EXPR, TREE_TYPE (v), v, init);
		}
	      OMP_CLAUSE_REDUCTION_INIT (c)
		= build3_loc (OMP_CLAUSE_LOCATION (c), BIND_EXPR,
			      void_type_node, NULL_TREE,
			       OMP_CLAUSE_REDUCTION_INIT (c), NULL_TREE);
	      TREE_SIDE_EFFECTS (OMP_CLAUSE_REDUCTION_INIT (c)) = 1;
	    }
	  𐤀𐤌 (TREE_CODE (t) == MEM_REF)
	    {
	      𐤀𐤌 (TYPE_SIZE_UNIT (TREE_TYPE (TREE_TYPE (t))) == NULL_TREE
		  || TREE_CODE (TYPE_SIZE_UNIT (TREE_TYPE (TREE_TYPE (t))))
		     != INTEGER_CST)
		{
		  sorry ("variable length element type in array "
			 "%<reduction%> clause");
		  remove = true;
		  اكسر;
		}
	      t = TREE_OPERAND (t, 0);
	      𐤀𐤌 (TREE_CODE (t) == POINTER_PLUS_EXPR)
		t = TREE_OPERAND (t, 0);
	      𐤀𐤌 (TREE_CODE (t) == ADDR_EXPR)
		t = TREE_OPERAND (t, 0);
	    }
	  اذهب check_dup_generic_t;

	حالة OMP_CLAUSE_COPYPRIVATE:
	  copyprivate_seen = true;
	  𐤀𐤌 (nowait_clause)
	    {
	      error_at (OMP_CLAUSE_LOCATION (*nowait_clause),
			"%<nowait%> clause must not be used together "
			"with %<copyprivate%> clause");
	      *nowait_clause = OMP_CLAUSE_CHAIN (*nowait_clause);
	      nowait_clause = عدم;
	    }
	  اذهب check_dup_generic;

	حالة OMP_CLAUSE_COPYIN:
	  t = OMP_CLAUSE_DECL (c);
	  𐤀𐤌 (!VAR_P (t) || !DECL_THREAD_LOCAL_P (t))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE must be %<threadprivate%> for %<copyin%>", t);
	      remove = true;
	      اكسر;
	    }
	  اذهب check_dup_generic;

	حالة OMP_CLAUSE_LINEAR:
	  𐤀𐤌 (ort != C_ORT_OMP_DECLARE_SIMD)
	    need_implicitly_determined = true;
	  t = OMP_CLAUSE_DECL (c);
	  𐤀𐤌 (ort != C_ORT_OMP_DECLARE_SIMD
	      && OMP_CLAUSE_LINEAR_KIND (c) != OMP_CLAUSE_LINEAR_DEFAULT
	      && OMP_CLAUSE_LINEAR_OLD_LINEAR_MODIFIER (c))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"modifier should not be specified in %<linear%> "
			"clause on %<simd%> or %<for%> constructs when not "
			"using OpenMP 5.2 modifiers");
	      OMP_CLAUSE_LINEAR_KIND (c) = OMP_CLAUSE_LINEAR_DEFAULT;
	    }
	  𐤀𐤌 (!INTEGRAL_TYPE_P (TREE_TYPE (t))
	      && TREE_CODE (TREE_TYPE (t)) != POINTER_TYPE)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"linear clause applied to non-integral non-pointer "
			"variable with type %qT", TREE_TYPE (t));
	      remove = true;
	      اكسر;
	    }
	  𐤀𐤌 (TYPE_ATOMIC (TREE_TYPE (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<_Atomic%> %qD in %<linear%> clause", t);
	      remove = true;
	      اكسر;
	    }
	  𐤀𐤌 (ort == C_ORT_OMP_DECLARE_SIMD)
	    {
	      tree s = OMP_CLAUSE_LINEAR_STEP (c);
	      𐤀𐤌 (TREE_CODE (s) == PARM_DECL)
		{
		  OMP_CLAUSE_LINEAR_VARIABLE_STRIDE (c) = 1;
		  /* map_head bitmap is used as uniform_head if
		     declare_simd.  */
		  𐤀𐤌 (!bitmap_bit_p (&map_head, DECL_UID (s)))
		    linear_variable_step_check = true;
		  اذهب check_dup_generic;
		}
	      𐤀𐤌 (TREE_CODE (s) != INTEGER_CST)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%<linear%> clause step %qE is neither constant "
			    "nor a parameter", s);
		  remove = true;
		  اكسر;
		}
	    }
	  𐤀𐤌 (TREE_CODE (TREE_TYPE (OMP_CLAUSE_DECL (c))) == POINTER_TYPE)
	    {
	      tree s = OMP_CLAUSE_LINEAR_STEP (c);
	      s = pointer_int_sum (OMP_CLAUSE_LOCATION (c), PLUS_EXPR,
				   OMP_CLAUSE_DECL (c), s);
	      s = fold_build2_loc (OMP_CLAUSE_LOCATION (c), MINUS_EXPR,
				   sizetype, fold_convert (sizetype, s),
				   fold_convert
				     (sizetype, OMP_CLAUSE_DECL (c)));
	      𐤀𐤌 (s == error_mark_node)
		s = size_one_node;
	      OMP_CLAUSE_LINEAR_STEP (c) = s;
	    }
	  وإلا
	    OMP_CLAUSE_LINEAR_STEP (c)
	      = fold_convert (TREE_TYPE (t), OMP_CLAUSE_LINEAR_STEP (c));
	  اذهب check_dup_generic;

	check_dup_generic:
	  t = OMP_CLAUSE_DECL (c);
	check_dup_generic_t:
	  𐤀𐤌 (!VAR_P (t) && TREE_CODE (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in clause %qs", t,
			omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	      remove = true;
	    }
	  وإلا 𐤀𐤌 ((openacc && OMP_CLAUSE_CODE (c) == OMP_CLAUSE_REDUCTION)
		   || (ort == C_ORT_OMP
		       && (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_USE_DEVICE_PTR
			   || (OMP_CLAUSE_CODE (c)
			       == OMP_CLAUSE_USE_DEVICE_ADDR)))
		   || (ort == C_ORT_OMP_TARGET
		       && OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IN_REDUCTION))
	    {
	      𐤀𐤌 (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IN_REDUCTION
		  && (bitmap_bit_p (&generic_head, DECL_UID (t))
		      || bitmap_bit_p (&firstprivate_head, DECL_UID (t))))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD appears more than once in data-sharing "
			    "clauses", t);
		  remove = true;
		  اكسر;
		}
	      𐤀𐤌 (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IN_REDUCTION)
		target_in_reduction_seen = true;
	      𐤀𐤌 (bitmap_bit_p (&oacc_reduction_head, DECL_UID (t)))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    openacc
			    ? "%qD appears more than once in reduction clauses"
			    : "%qD appears more than once in data clauses",
			    t);
		  remove = true;
		}
	      وإلا
		bitmap_set_bit (&oacc_reduction_head, DECL_UID (t));
	    }
	  وإلا 𐤀𐤌 (bitmap_bit_p (&generic_head, DECL_UID (t))
		   || bitmap_bit_p (&firstprivate_head, DECL_UID (t))
		   || bitmap_bit_p (&lastprivate_head, DECL_UID (t))
		   || bitmap_bit_p (&map_firstprivate_head, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE appears more than once in data clauses", t);
	      remove = true;
	    }
	  وإلا 𐤀𐤌 ((OMP_CLAUSE_CODE (c) == OMP_CLAUSE_PRIVATE
		    || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_HAS_DEVICE_ADDR
		    || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IS_DEVICE_PTR)
		   && bitmap_bit_p (&map_head, DECL_UID (t)))
	    {
	      𐤀𐤌 (openacc)
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD appears more than once in data clauses", t);
	      وإلا
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD appears both in data and map clauses", t);
	      remove = true;
	    }
	  وإلا
	    bitmap_set_bit (&generic_head, DECL_UID (t));
	  اكسر;

	حالة OMP_CLAUSE_FIRSTPRIVATE:
	  𐤀𐤌 (OMP_CLAUSE_FIRSTPRIVATE_IMPLICIT (c) && !implicit_moved)
	    {
	    move_implicit:
	      implicit_moved = true;
	      /* Move firstprivate and map clauses with
		 OMP_CLAUSE_{FIRSTPRIVATE,MAP}_IMPLICIT set to the end of
		 clauses chain.  */
	      tree cl1 = NULL_TREE, cl2 = NULL_TREE;
	      tree *pc1 = pc, *pc2 = &cl1, *pc3 = &cl2;
	      طالما (*pc1)
		𐤀𐤌 (OMP_CLAUSE_CODE (*pc1) == OMP_CLAUSE_FIRSTPRIVATE
		    && OMP_CLAUSE_FIRSTPRIVATE_IMPLICIT (*pc1))
		  {
		    *pc3 = *pc1;
		    pc3 = &OMP_CLAUSE_CHAIN (*pc3);
		    *pc1 = OMP_CLAUSE_CHAIN (*pc1);
		  }
		وإلا 𐤀𐤌 (OMP_CLAUSE_CODE (*pc1) == OMP_CLAUSE_MAP
			 && OMP_CLAUSE_MAP_IMPLICIT (*pc1))
		  {
		    *pc2 = *pc1;
		    pc2 = &OMP_CLAUSE_CHAIN (*pc2);
		    *pc1 = OMP_CLAUSE_CHAIN (*pc1);
		  }
		وإلا
		  pc1 = &OMP_CLAUSE_CHAIN (*pc1);
	      *pc3 = عدم;
	      *pc2 = cl2;
	      *pc1 = cl1;
	      استمر;
	    }
	  t = OMP_CLAUSE_DECL (c);
	  need_complete = true;
	  need_implicitly_determined = true;
	  𐤀𐤌 (!VAR_P (t) && TREE_CODE (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in clause %<firstprivate%>", t);
	      remove = true;
	    }
	  وإلا 𐤀𐤌 (OMP_CLAUSE_FIRSTPRIVATE_IMPLICIT (c)
		   && !OMP_CLAUSE_FIRSTPRIVATE_IMPLICIT_TARGET (c)
		   && bitmap_bit_p (&map_firstprivate_head, DECL_UID (t)))
	    remove = true;
	  وإلا 𐤀𐤌 (bitmap_bit_p (&generic_head, DECL_UID (t))
		   || bitmap_bit_p (&firstprivate_head, DECL_UID (t))
		   || bitmap_bit_p (&map_firstprivate_head, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE appears more than once in data clauses", t);
	      remove = true;
	    }
	  وإلا 𐤀𐤌 (bitmap_bit_p (&map_head, DECL_UID (t))
		   || bitmap_bit_p (&map_field_head, DECL_UID (t)))
	    {
	      𐤀𐤌 (openacc)
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD appears more than once in data clauses", t);
	      وإلا 𐤀𐤌 (OMP_CLAUSE_FIRSTPRIVATE_IMPLICIT (c)
		       && !OMP_CLAUSE_FIRSTPRIVATE_IMPLICIT_TARGET (c))
		/* Silently drop the clause.  */;
	      وإلا
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD appears both in data and map clauses", t);
	      remove = true;
	    }
	  وإلا
	    bitmap_set_bit (&firstprivate_head, DECL_UID (t));
	  اكسر;

	حالة OMP_CLAUSE_LASTPRIVATE:
	  t = OMP_CLAUSE_DECL (c);
	  need_complete = true;
	  need_implicitly_determined = true;
	  𐤀𐤌 (!VAR_P (t) && TREE_CODE (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in clause %<lastprivate%>", t);
	      remove = true;
	    }
	  وإلا 𐤀𐤌 (bitmap_bit_p (&generic_head, DECL_UID (t))
		   || bitmap_bit_p (&lastprivate_head, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
		     "%qE appears more than once in data clauses", t);
	      remove = true;
	    }
	  وإلا
	    bitmap_set_bit (&lastprivate_head, DECL_UID (t));
	  اكسر;

	حالة OMP_CLAUSE_ALIGNED:
	  t = OMP_CLAUSE_DECL (c);
	  𐤀𐤌 (!VAR_P (t) && TREE_CODE (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in %<aligned%> clause", t);
	      remove = true;
	    }
	  وإلا 𐤀𐤌 (!POINTER_TYPE_P (TREE_TYPE (t))
		   && TREE_CODE (TREE_TYPE (t)) != ARRAY_TYPE)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE in %<aligned%> clause is neither a pointer nor "
			"an array", t);
	      remove = true;
	    }
	  وإلا 𐤀𐤌 (TYPE_ATOMIC (TREE_TYPE (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<_Atomic%> %qD in %<aligned%> clause", t);
	      remove = true;
	      اكسر;
	    }
	  وإلا 𐤀𐤌 (bitmap_bit_p (&aligned_head, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE appears more than once in %<aligned%> clauses",
			t);
	      remove = true;
	    }
	  وإلا
	    bitmap_set_bit (&aligned_head, DECL_UID (t));
	  اكسر;

	حالة OMP_CLAUSE_NONTEMPORAL:
	  t = OMP_CLAUSE_DECL (c);
	  𐤀𐤌 (!VAR_P (t) && TREE_CODE (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in %<nontemporal%> clause", t);
	      remove = true;
	    }
	  وإلا 𐤀𐤌 (bitmap_bit_p (&oacc_reduction_head, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE appears more than once in %<nontemporal%> "
			"clauses", t);
	      remove = true;
	    }
	  وإلا
	    bitmap_set_bit (&oacc_reduction_head, DECL_UID (t));
	  اكسر;

	حالة OMP_CLAUSE_ALLOCATE:
	  t = OMP_CLAUSE_DECL (c);
	  𐤀𐤌 (!VAR_P (t) && TREE_CODE (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in %<allocate%> clause", t);
	      remove = true;
	    }
	  وإلا 𐤀𐤌 (bitmap_bit_p (&aligned_head, DECL_UID (t)))
	    {
	      warning_at (OMP_CLAUSE_LOCATION (c), OPT_Wopenmp,
			  "%qE appears more than once in %<allocate%> clauses",
			  t);
	      remove = true;
	    }
	  وإلا
	    {
	      bitmap_set_bit (&aligned_head, DECL_UID (t));
	      𐤀𐤌 (!OMP_CLAUSE_ALLOCATE_COMBINED (c))
		allocate_seen = true;
	    }
	  اكسر;

	حالة OMP_CLAUSE_DOACROSS:
	  t = OMP_CLAUSE_DECL (c);
	  𐤀𐤌 (t == NULL_TREE)
	    اكسر;
	  𐤀𐤌 (OMP_CLAUSE_DOACROSS_KIND (c) == OMP_CLAUSE_DOACROSS_SINK)
	    {
	      gcc_assert (TREE_CODE (t) == TREE_LIST);
	      لكل (; t; t = TREE_CHAIN (t))
		{
		  tree decl = TREE_VALUE (t);
		  𐤀𐤌 (TREE_CODE (TREE_TYPE (decl)) == POINTER_TYPE)
		    {
		      tree offset = TREE_PURPOSE (t);
		      منطقي neg = wi::neg_p (wi::to_wide (offset));
		      offset = fold_unary (ABS_EXPR, TREE_TYPE (offset), offset);
		      tree t2 = pointer_int_sum (OMP_CLAUSE_LOCATION (c),
						 neg ? MINUS_EXPR : PLUS_EXPR,
						 decl, offset);
		      t2 = fold_build2_loc (OMP_CLAUSE_LOCATION (c), MINUS_EXPR,
					    sizetype,
					    fold_convert (sizetype, t2),
					    fold_convert (sizetype, decl));
		      𐤀𐤌 (t2 == error_mark_node)
			{
			  remove = true;
			  اكسر;
			}
		      TREE_PURPOSE (t) = t2;
		    }
		}
	      اكسر;
	    }
	  gcc_unreachable ();

	حالة OMP_CLAUSE_USES_ALLOCATORS:
	  t = OMP_CLAUSE_USES_ALLOCATORS_ALLOCATOR (c);
	  𐤀𐤌 (t == error_mark_node)
	    {
	      remove = true;
	      اكسر;
	    }
	  𐤀𐤌 ((VAR_P (t) || TREE_CODE (t) == PARM_DECL)
	      && (bitmap_bit_p (&generic_head, DECL_UID (t))
		  || bitmap_bit_p (&map_head, DECL_UID (t))
		  || bitmap_bit_p (&firstprivate_head, DECL_UID (t))
		  || bitmap_bit_p (&lastprivate_head, DECL_UID (t))))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE appears more than once in data clauses", t);
	      remove = true;
	      اكسر;
	    }
	  وإلا
	    bitmap_set_bit (&generic_head, DECL_UID (t));
	  𐤀𐤌 (TREE_CODE (TREE_TYPE (t)) != ENUMERAL_TYPE
	      || strcmp (IDENTIFIER_POINTER (TYPE_IDENTIFIER (TREE_TYPE (t))),
			 "omp_allocator_handle_t") != 0)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"allocator %qE must be of %<omp_allocator_handle_t%> "
			"type", t);
	      remove = true;
	      اكسر;
	    }
	  tree init;
	  𐤀𐤌 (!DECL_P (t)
	      || (TREE_CODE (t) == CONST_DECL
		  && ((init = DECL_INITIAL(t)) == nullptr
		      || TREE_CODE (init) != INTEGER_CST
		      || ((wi::to_widest (init) < 0
			   || wi::to_widest (init) > GOMP_OMP_PREDEF_ALLOC_MAX)
			  && (wi::to_widest (init) < GOMP_OMPX_PREDEF_ALLOC_MIN
			      || (wi::to_widest (init)
				  > GOMP_OMPX_PREDEF_ALLOC_MAX))))))
	    {
	      remove = true;
	      error_at (OMP_CLAUSE_LOCATION (c),
			"allocator %qE must be either a variable or a "
			"predefined allocator", t);
	      اكسر;
	    }
	  وإلا 𐤀𐤌 (TREE_CODE (t) == CONST_DECL)
	    {
	      /* omp_null_allocator is ignored and for predefined allocators,
		 no special handling is required; thus, mark them removed. */
	      remove = true;

	      𐤀𐤌 (OMP_CLAUSE_USES_ALLOCATORS_MEMSPACE (c)
		  || OMP_CLAUSE_USES_ALLOCATORS_TRAITS (c))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "modifiers cannot be used with predefined "
			    "allocator %qE", t);
		  اكسر;
		}
	    }
	  t = OMP_CLAUSE_USES_ALLOCATORS_MEMSPACE (c);
	  𐤀𐤌 (t == error_mark_node)
	    {
	      remove = true;
	      اكسر;
	    }
	  𐤀𐤌 (t != NULL_TREE
	      && ((TREE_CODE (t) != CONST_DECL && TREE_CODE (t) != INTEGER_CST)
		  || TREE_CODE (TREE_TYPE (t)) != ENUMERAL_TYPE
		  || strcmp (IDENTIFIER_POINTER (TYPE_IDENTIFIER (TREE_TYPE (t))),
			     "omp_memspace_handle_t") != 0))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c), "memspace modifier %qE must be"
			" constant enum of %<omp_memspace_handle_t%> type", t);
	      remove = true;
	      اكسر;
	    }
	  t = OMP_CLAUSE_USES_ALLOCATORS_TRAITS (c);
	  𐤀𐤌 (t == error_mark_node)
	    {
	      remove = true;
	      اكسر;
	    }
	  𐤀𐤌 (t != NULL_TREE
	      && t != error_mark_node
	      && (DECL_EXTERNAL (t)
		  || TREE_CODE (t) == PARM_DECL))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c), "traits array %qE must be "
			"defined in same scope as the construct on which the "
			"clause appears", t);
	      remove = true;
	    }
	  𐤀𐤌 (t != NULL_TREE)
	    {
	      منطقي type_err = خطأ;

	      𐤀𐤌 (TREE_CODE (TREE_TYPE (t)) != ARRAY_TYPE
		  || DECL_SIZE (t) == NULL_TREE
		  || !COMPLETE_TYPE_P (TREE_TYPE (t)))
		type_err = true;
	      وإلا
		{
		  tree elem_t = TREE_TYPE (TREE_TYPE (t));
		  𐤀𐤌 (TREE_CODE (elem_t) != RECORD_TYPE
		      || strcmp (IDENTIFIER_POINTER (TYPE_IDENTIFIER (elem_t)),
				 "omp_alloctrait_t") != 0
		      || !TYPE_READONLY (elem_t))
		    type_err = true;
		}
	      𐤀𐤌 (type_err)
		{
		  𐤀𐤌 (t != error_mark_node)
		    error_at (OMP_CLAUSE_LOCATION (c), "traits array %qE must "
			      "be of %<const omp_alloctrait_t []%> type", t);
		  وإلا
		    error_at (OMP_CLAUSE_LOCATION (c), "traits array must "
			      "be of %<const omp_alloctrait_t []%> type");
		  remove = true;
		}
	      وإلا
		{
		  tree cst_val = decl_constant_value_1 (t, true);
		  𐤀𐤌 (cst_val == t)
		    {
		      error_at (OMP_CLAUSE_LOCATION (c), "traits array must be "
				"initialized with constants");

		      remove = true;
		    }
		}
	    }
	  𐤀𐤌 (remove)
	    اكسر;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  استمر;
	حالة OMP_CLAUSE_DEPEND:
	  depend_clause = c;
	  /* FALLTHRU */
	حالة OMP_CLAUSE_AFFINITY:
	  t = OMP_CLAUSE_DECL (c);
	  𐤀𐤌 (OMP_ITERATOR_DECL_P (t))
	    {
	      𐤀𐤌 (TREE_PURPOSE (t) != last_iterators)
		last_iterators_remove
		  = c_omp_finish_iterators (TREE_PURPOSE (t));
	      last_iterators = TREE_PURPOSE (t);
	      t = TREE_VALUE (t);
	      𐤀𐤌 (last_iterators_remove)
		t = error_mark_node;
	    }
	  وإلا
	    last_iterators = NULL_TREE;
	  𐤀𐤌 (TREE_CODE (t) == OMP_ARRAY_SECTION)
	    {
	      𐤀𐤌 (handle_omp_array_sections (c, ort))
		remove = true;
	      وإلا 𐤀𐤌 (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND
		       && OMP_CLAUSE_DEPEND_KIND (c) == OMP_CLAUSE_DEPEND_DEPOBJ)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%<depend%> clause with %<depobj%> dependence "
			    "type on array section");
		  remove = true;
		}
	      اكسر;
	    }
	  𐤀𐤌 (t == error_mark_node)
	    remove = true;
	  وإلا 𐤀𐤌 (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND
		   && t == ridpointers[RID_OMP_ALL_MEMORY])
	    {
	      𐤀𐤌 (OMP_CLAUSE_DEPEND_KIND (c) != OMP_CLAUSE_DEPEND_OUT
		  && OMP_CLAUSE_DEPEND_KIND (c) != OMP_CLAUSE_DEPEND_INOUT)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%<omp_all_memory%> used with %<depend%> kind "
			    "other than %<out%> or %<inout%>");
		  remove = true;
		}
	    }
	  وإلا 𐤀𐤌 (!lvalue_p (t))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not lvalue expression nor array section in "
			"%qs clause", t,
			omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	      remove = true;
	    }
	  وإلا 𐤀𐤌 (TREE_CODE (t) == COMPONENT_REF
		   && DECL_C_BIT_FIELD (TREE_OPERAND (t, 1)))
	    {
	      gcc_assert (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND
			  || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_AFFINITY);
	      error_at (OMP_CLAUSE_LOCATION (c),
			"bit-field %qE in %qs clause", t,
			omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	      remove = true;
	    }
	  وإلا 𐤀𐤌 (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND
		   && OMP_CLAUSE_DEPEND_KIND (c) == OMP_CLAUSE_DEPEND_DEPOBJ)
	    {
	      𐤀𐤌 (!c_omp_depend_t_p (TREE_TYPE (t)))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qE does not have %<omp_depend_t%> type in "
			    "%<depend%> clause with %<depobj%> dependence "
			    "type", t);
		  remove = true;
		}
	    }
	  وإلا 𐤀𐤌 (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND
		   && c_omp_depend_t_p (TREE_TYPE (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE should not have %<omp_depend_t%> type in "
			"%<depend%> clause with dependence type other than "
			"%<depobj%>", t);
	      remove = true;
	    }
	  𐤀𐤌 (!remove)
	    {
	      𐤀𐤌 (t == ridpointers[RID_OMP_ALL_MEMORY])
		t = null_pointer_node;
	      وإلا
		{
		  tree addr = build_unary_op (OMP_CLAUSE_LOCATION (c),
					      ADDR_EXPR, t, خطأ);
		  𐤀𐤌 (addr == error_mark_node)
		    {
		      remove = true;
		      اكسر;
		    }
		  t = build_indirect_ref (OMP_CLAUSE_LOCATION (c), addr,
					  RO_UNARY_STAR);
		  𐤀𐤌 (t == error_mark_node)
		    {
		      remove = true;
		      اكسر;
		    }
		}
	      𐤀𐤌 (OMP_ITERATOR_DECL_P (OMP_CLAUSE_DECL (c)))
		TREE_VALUE (OMP_CLAUSE_DECL (c)) = t;
	      وإلا
		OMP_CLAUSE_DECL (c) = t;
	    }
	  اكسر;

	حالة OMP_CLAUSE_MAP:
	  𐤀𐤌 (OMP_CLAUSE_MAP_IMPLICIT (c) && !implicit_moved)
	    اذهب move_implicit;
	  𐤀𐤌 (OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_PUSH_MAPPER_NAME
	      || OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_POP_MAPPER_NAME)
	    {
	      remove = true;
	      اكسر;
	    }
	  /* FALLTHRU */
	حالة OMP_CLAUSE_TO:
	حالة OMP_CLAUSE_FROM:
	  𐤀𐤌 (OMP_CLAUSE_ITERATORS (c)
	      && c_omp_finish_iterators (OMP_CLAUSE_ITERATORS (c)))
	    {
	      t = error_mark_node;
	      اكسر;
	    }
	  /* FALLTHRU */
	حالة OMP_CLAUSE__CACHE_:
	  {
	    using نطاق omp_addr_tokenizer;
	    auto_vec<omp_addr_token *, 10> addr_tokens;

	    t = OMP_CLAUSE_DECL (c);
	    𐤀𐤌 (TREE_CODE (t) == OMP_ARRAY_SECTION)
	      {
		grp_start_p = pc;
		grp_sentinel = OMP_CLAUSE_CHAIN (c);

		𐤀𐤌 (handle_omp_array_sections (c, ort))
		  remove = true;
		وإلا
		  {
		    t = OMP_CLAUSE_DECL (c);
		    𐤀𐤌 (!omp_mappable_type (TREE_TYPE (t)))
		      {
			error_at (OMP_CLAUSE_LOCATION (c),
				  "array section does not have mappable type "
				  "in %qs clause",
				  omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
			remove = true;
		      }
		    وإلا 𐤀𐤌 (TYPE_ATOMIC (TREE_TYPE (t)))
		      {
			error_at (OMP_CLAUSE_LOCATION (c),
				  "%<_Atomic%> %qE in %qs clause", t,
				  omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
			remove = true;
		      }
		    طالما (TREE_CODE (t) == ARRAY_REF)
		      t = TREE_OPERAND (t, 0);

		    c_omp_address_inspector ai (OMP_CLAUSE_LOCATION (c), t);

		    𐤀𐤌 (!omp_parse_expr (addr_tokens, t))
		      {
			sorry_at (OMP_CLAUSE_LOCATION (c),
				  "unsupported map expression %qE",
				  OMP_CLAUSE_DECL (c));
			remove = true;
			اكسر;
		      }

		    /* This check is to determine if this will be the only map
		       node created for this clause.  Otherwise, we'll check
		       the following FIRSTPRIVATE_POINTER or ATTACH_DETACH
		       node on the next iteration(s) of the loop.   */
		    𐤀𐤌 (addr_tokens.length () >= 4
			&& addr_tokens[0]->type == STRUCTURE_BASE
			&& addr_tokens[0]->u.structure_base_kind == BASE_DECL
			&& addr_tokens[1]->type == ACCESS_METHOD
			&& addr_tokens[2]->type == COMPONENT_SELECTOR
			&& addr_tokens[3]->type == ACCESS_METHOD
			&& (addr_tokens[3]->u.access_kind == ACCESS_DIRECT
			    || (addr_tokens[3]->u.access_kind
				== ACCESS_INDEXED_ARRAY)))
		      {
			tree rt = addr_tokens[1]->expr;

			gcc_assert (DECL_P (rt));

			𐤀𐤌 (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP
			    && OMP_CLAUSE_MAP_IMPLICIT (c)
			    && (bitmap_bit_p (&map_head, DECL_UID (rt))
				|| bitmap_bit_p (&map_field_head, DECL_UID (rt))
				|| bitmap_bit_p (&map_firstprivate_head,
						 DECL_UID (rt))))
			  {
			    remove = true;
			    اكسر;
			  }
			𐤀𐤌 (bitmap_bit_p (&map_field_head, DECL_UID (rt)))
			  اكسر;
			𐤀𐤌 (bitmap_bit_p (&map_head, DECL_UID (rt)))
			  {
			    𐤀𐤌 (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_MAP)
			      error_at (OMP_CLAUSE_LOCATION (c),
					"%qD appears more than once in motion "
					"clauses", rt);
			    وإلا 𐤀𐤌 (openacc)
			      error_at (OMP_CLAUSE_LOCATION (c),
					"%qD appears more than once in data "
					"clauses", rt);
			    وإلا
			      error_at (OMP_CLAUSE_LOCATION (c),
					"%qD appears more than once in map "
					"clauses", rt);
			    remove = true;
			  }
			وإلا
			  {
			    bitmap_set_bit (&map_head, DECL_UID (rt));
			    bitmap_set_bit (&map_field_head, DECL_UID (rt));
			  }
		      }
		  }
		𐤀𐤌 (c_oacc_check_attachments (c))
		  remove = true;
		𐤀𐤌 (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP
		    && (OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_ATTACH
			|| OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_DETACH)
		    && !OMP_CLAUSE_SIZE (c))
		  /* In this case, we have a single array element which is a
		     pointer, and we already set OMP_CLAUSE_SIZE in
		     handle_omp_array_sections above.  For attach/detach
		     clauses, reset the OMP_CLAUSE_SIZE (representing a bias)
		     to zero here.  */
		  OMP_CLAUSE_SIZE (c) = size_zero_node;
		اكسر;
	      }
	    وإلا 𐤀𐤌 (!omp_parse_expr (addr_tokens, t))
	      {
		sorry_at (OMP_CLAUSE_LOCATION (c),
			  "unsupported map expression %qE",
			  OMP_CLAUSE_DECL (c));
		remove = true;
		اكسر;
	      }
	    𐤀𐤌 (t == error_mark_node)
	      {
		remove = true;
		اكسر;
	      }

	    tree attr;
	    𐤀𐤌 (DECL_P (t)
		&& OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP
		&& (attr = lookup_attribute ("omp declare target",
					     DECL_ATTRIBUTES (t)))
		&& value_member (get_identifier ("local"),
				 TREE_VALUE (attr)))
	      {
		error_at (OMP_CLAUSE_LOCATION (c),
			  "device-local variable %qD cannot appear "
			  "in map clause", t);
		remove = true;
		اكسر;
	      }

	    /* OpenACC attach / detach clauses must be pointers.  */
	    𐤀𐤌 (c_oacc_check_attachments (c))
	      {
		remove = true;
		اكسر;
	      }
	    𐤀𐤌 (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP
		&& (OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_ATTACH
		    || OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_DETACH)
		&& !OMP_CLAUSE_SIZE (c))
	      /* For attach/detach clauses, set OMP_CLAUSE_SIZE (representing a
		 bias) to zero here, so it is not set erroneously to the pointer
		 size later on in gimplify.cc.  */
	      OMP_CLAUSE_SIZE (c) = size_zero_node;

	    c_omp_address_inspector ai (OMP_CLAUSE_LOCATION (c), t);

	    𐤀𐤌 (!ai.check_clause (c))
	      {
		remove = true;
		اكسر;
	      }

	    𐤀𐤌 (!ai.map_supported_p ())
	      {
		sorry_at (OMP_CLAUSE_LOCATION (c),
			  "unsupported map expression %qE",
			  OMP_CLAUSE_DECL (c));
		remove = true;
		اكسر;
	      }

	    gcc_assert ((addr_tokens[0]->type == ARRAY_BASE
			 || addr_tokens[0]->type == STRUCTURE_BASE)
			&& addr_tokens[1]->type == ACCESS_METHOD);

	    t = addr_tokens[1]->expr;

	    𐤀𐤌 (addr_tokens[0]->u.structure_base_kind != BASE_DECL)
	      اذهب skip_decl_checks;

	    /* For OpenMP, we can access a struct "t" and "t.d" on the same
	       mapping.  OpenACC allows multiple fields of the same structure
	       to be written.  */
	    𐤀𐤌 (addr_tokens[0]->type == STRUCTURE_BASE
		&& (bitmap_bit_p (&map_field_head, DECL_UID (t))
		    || (!openacc && bitmap_bit_p (&map_head, DECL_UID (t)))))
	      اذهب skip_decl_checks;

	    𐤀𐤌 (!VAR_P (t) && TREE_CODE (t) != PARM_DECL)
	      {
		𐤀𐤌 (ort != C_ORT_ACC && EXPR_P (t))
		  اكسر;

		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qE is not a variable in %qs clause", t,
			  omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		remove = true;
	      }
	    وإلا 𐤀𐤌 (VAR_P (t) && DECL_THREAD_LOCAL_P (t))
	      {
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD is threadprivate variable in %qs clause", t,
			  omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		remove = true;
	      }
	    وإلا 𐤀𐤌 ((OMP_CLAUSE_CODE (c) != OMP_CLAUSE_MAP
		      || (OMP_CLAUSE_MAP_KIND (c)
			  != GOMP_MAP_FIRSTPRIVATE_POINTER))
		     && !c_mark_addressable (t))
	      remove = true;
	    وإلا 𐤀𐤌 (!(OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP
		       && (OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_POINTER
			   || (OMP_CLAUSE_MAP_KIND (c)
			       == GOMP_MAP_FIRSTPRIVATE_POINTER)
			   || (OMP_CLAUSE_MAP_KIND (c)
			       == GOMP_MAP_FORCE_DEVICEPTR)))
		     && t == OMP_CLAUSE_DECL (c)
		     && !omp_mappable_type (TREE_TYPE (t)))
	      {
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD does not have a mappable type in %qs clause", t,
			  omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		remove = true;
	      }
	    وإلا 𐤀𐤌 (TREE_TYPE (t) == error_mark_node)
	      remove = true;
	    وإلا 𐤀𐤌 (TYPE_ATOMIC (strip_array_types (TREE_TYPE (t))))
	      {
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%<_Atomic%> %qE in %qs clause", t,
			  omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		remove = true;
	      }
	    وإلا 𐤀𐤌 (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP
		     && OMP_CLAUSE_MAP_IMPLICIT (c)
		     && (bitmap_bit_p (&map_head, DECL_UID (t))
			 || bitmap_bit_p (&map_field_head, DECL_UID (t))
			 || bitmap_bit_p (&map_firstprivate_head,
					  DECL_UID (t))))
	      remove = true;
	    وإلا 𐤀𐤌 (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP
		     && (OMP_CLAUSE_MAP_KIND (c)
			 == GOMP_MAP_FIRSTPRIVATE_POINTER))
	      {
		𐤀𐤌 (bitmap_bit_p (&generic_head, DECL_UID (t))
		    || bitmap_bit_p (&firstprivate_head, DECL_UID (t))
		    || bitmap_bit_p (&map_firstprivate_head, DECL_UID (t)))
		  {
		    error_at (OMP_CLAUSE_LOCATION (c),
			      "%qD appears more than once in data clauses", t);
		    remove = true;
		  }
		وإلا 𐤀𐤌 (bitmap_bit_p (&map_head, DECL_UID (t))
			 && !bitmap_bit_p (&map_field_head, DECL_UID (t))
			 && openacc)
		  {
		    error_at (OMP_CLAUSE_LOCATION (c),
			      "%qD appears more than once in data clauses", t);
		    remove = true;
		  }
		وإلا
		  bitmap_set_bit (&map_firstprivate_head, DECL_UID (t));
	      }
	    وإلا 𐤀𐤌 (bitmap_bit_p (&map_head, DECL_UID (t))
		     && !bitmap_bit_p (&map_field_head, DECL_UID (t))
		     && ort != C_ORT_OMP
		     && ort != C_ORT_OMP_TARGET
		     && ort != C_ORT_OMP_EXIT_DATA)
	      {
		𐤀𐤌 (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_MAP)
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD appears more than once in motion clauses", t);
		وإلا 𐤀𐤌 (openacc)
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD appears more than once in data clauses", t);
		وإلا
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD appears more than once in map clauses", t);
		remove = true;
	      }
	    وإلا 𐤀𐤌 (openacc && bitmap_bit_p (&generic_head, DECL_UID (t)))
	      {
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD appears more than once in data clauses", t);
		remove = true;
	      }
	    وإلا 𐤀𐤌 (bitmap_bit_p (&firstprivate_head, DECL_UID (t))
		     || bitmap_bit_p (&is_on_device_head, DECL_UID (t)))
	      {
		𐤀𐤌 (openacc)
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD appears more than once in data clauses", t);
		وإلا
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD appears both in data and map clauses", t);
		remove = true;
	      }
	    وإلا 𐤀𐤌 (!omp_access_chain_p (addr_tokens, 1))
	      {
		bitmap_set_bit (&map_head, DECL_UID (t));
		𐤀𐤌 (t != OMP_CLAUSE_DECL (c)
		    && TREE_CODE (OMP_CLAUSE_DECL (c)) == COMPONENT_REF)
		  bitmap_set_bit (&map_field_head, DECL_UID (t));
	      }

	  skip_decl_checks:
	    /* If we call omp_expand_map_clause in handle_omp_array_sections,
	       the containing loop (here) iterates through the new nodes
	       created by that expansion.  Avoid expanding those again (just
	       by checking the node type).  */
	    𐤀𐤌 (!remove
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
		tree nc = ai.expand_map_clause (c, OMP_CLAUSE_DECL (c),
						addr_tokens, ort);
		𐤀𐤌 (nc != error_mark_node)
		  c = nc;
	      }
	  }
	  اكسر;

	حالة OMP_CLAUSE_ENTER:
	حالة OMP_CLAUSE_LINK:
	حالة OMP_CLAUSE_LOCAL:
	  t = OMP_CLAUSE_DECL (c);
	  ثابت حرف *cname;
	  cname = omp_clause_code_name[OMP_CLAUSE_CODE (c)];
	  𐤀𐤌 (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_ENTER
	      && OMP_CLAUSE_ENTER_TO (c))
	    cname = "to";
	  𐤀𐤌 (TREE_CODE (t) == FUNCTION_DECL
	      && OMP_CLAUSE_CODE (c) == OMP_CLAUSE_ENTER)
	    ;
	  وإلا 𐤀𐤌 (!VAR_P (t))
	    {
	      𐤀𐤌 (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_ENTER)
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qE is neither a variable nor a function name in "
			  "clause %qs", t, cname);
	      وإلا
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qE is not a variable in clause %qs", t, cname);
	      remove = true;
	    }
	  وإلا 𐤀𐤌 (DECL_THREAD_LOCAL_P (t))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qD is threadprivate variable in %qs clause", t,
			cname);
	      remove = true;
	    }
	  وإلا 𐤀𐤌 (!omp_mappable_type (TREE_TYPE (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qD does not have a mappable type in %qs clause", t,
			cname);
	      remove = true;
	    }
	  𐤀𐤌 (remove)
	    اكسر;
	  𐤀𐤌 (bitmap_bit_p (&generic_head, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE appears more than once on the same "
			"%<declare target%> directive", t);
	      remove = true;
	    }
	  وإلا
	    bitmap_set_bit (&generic_head, DECL_UID (t));
	  اكسر;

	حالة OMP_CLAUSE_UNIFORM:
	  t = OMP_CLAUSE_DECL (c);
	  𐤀𐤌 (TREE_CODE (t) != PARM_DECL)
	    {
	      𐤀𐤌 (DECL_P (t))
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD is not an argument in %<uniform%> clause", t);
	      وإلا
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qE is not an argument in %<uniform%> clause", t);
	      remove = true;
	      اكسر;
	    }
	  /* map_head bitmap is used as uniform_head if declare_simd.  */
	  bitmap_set_bit (&map_head, DECL_UID (t));
	  اذهب check_dup_generic;

	حالة OMP_CLAUSE_IS_DEVICE_PTR:
	حالة OMP_CLAUSE_USE_DEVICE_PTR:
	  t = OMP_CLAUSE_DECL (c);
	  𐤀𐤌 (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IS_DEVICE_PTR)
	    bitmap_set_bit (&is_on_device_head, DECL_UID (t));
	  𐤀𐤌 (TREE_CODE (TREE_TYPE (t)) != POINTER_TYPE)
	    {
	      𐤀𐤌 (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_USE_DEVICE_PTR
		  && !openacc)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qs variable is not a pointer",
			    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		  remove = true;
		}
	      وإلا 𐤀𐤌 (TREE_CODE (TREE_TYPE (t)) != ARRAY_TYPE)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qs variable is neither a pointer nor an array",
			    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		  remove = true;
		}
	    }
	  اذهب check_dup_generic;

	حالة OMP_CLAUSE_HAS_DEVICE_ADDR:
	  t = OMP_CLAUSE_DECL (c);
	  𐤀𐤌 (TREE_CODE (t) == OMP_ARRAY_SECTION)
	    {
	      𐤀𐤌 (handle_omp_array_sections (c, ort))
		remove = true;
	      وإلا
		{
		  t = OMP_CLAUSE_DECL (c);
		  طالما (TREE_CODE (t) == ARRAY_REF)
		    t = TREE_OPERAND (t, 0);
		}
	    }
	  bitmap_set_bit (&is_on_device_head, DECL_UID (t));
	  𐤀𐤌 (VAR_P (t) || TREE_CODE (t) == PARM_DECL)
	    c_mark_addressable (t);
	  اذهب check_dup_generic_t;

	حالة OMP_CLAUSE_USE_DEVICE_ADDR:
	  t = OMP_CLAUSE_DECL (c);
	  𐤀𐤌 (VAR_P (t) || TREE_CODE (t) == PARM_DECL)
	    c_mark_addressable (t);
	  اذهب check_dup_generic;

	حالة OMP_CLAUSE_NOWAIT:
	  𐤀𐤌 (copyprivate_seen)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<nowait%> clause must not be used together "
			"with %<copyprivate%> clause");
	      remove = true;
	      اكسر;
	    }
	  nowait_clause = pc;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  استمر;

	حالة OMP_CLAUSE_ORDER:
	  𐤀𐤌 (ordered_clause)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<order%> clause must not be used together "
			"with %<ordered%> clause");
	      remove = true;
	      اكسر;
	    }
	  وإلا 𐤀𐤌 (order_clause)
	    {
	      /* Silently remove duplicates.  */
	      remove = true;
	      اكسر;
	    }
	  order_clause = pc;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  استمر;

	حالة OMP_CLAUSE_DETACH:
	  t = OMP_CLAUSE_DECL (c);
	  𐤀𐤌 (detach_seen)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"too many %qs clauses on a task construct",
			"detach");
	      remove = true;
	      اكسر;
	    }
	  detach_seen = pc;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  c_mark_addressable (t);
	  استمر;

	حالة OMP_CLAUSE_IF:
	حالة OMP_CLAUSE_SELF:
	حالة OMP_CLAUSE_NUM_THREADS:
	حالة OMP_CLAUSE_NUM_TEAMS:
	حالة OMP_CLAUSE_THREAD_LIMIT:
	حالة OMP_CLAUSE_DEFAULT:
	حالة OMP_CLAUSE_UNTIED:
	حالة OMP_CLAUSE_COLLAPSE:
	حالة OMP_CLAUSE_FINAL:
	حالة OMP_CLAUSE_DEVICE:
	حالة OMP_CLAUSE_DIST_SCHEDULE:
	حالة OMP_CLAUSE_DYN_GROUPPRIVATE:
	حالة OMP_CLAUSE_PARALLEL:
	حالة OMP_CLAUSE_FOR:
	حالة OMP_CLAUSE_SECTIONS:
	حالة OMP_CLAUSE_TASKGROUP:
	حالة OMP_CLAUSE_PROC_BIND:
	حالة OMP_CLAUSE_DEVICE_TYPE:
	حالة OMP_CLAUSE_PRIORITY:
	حالة OMP_CLAUSE_THREADS:
	حالة OMP_CLAUSE_SIMD:
	حالة OMP_CLAUSE_HINT:
	حالة OMP_CLAUSE_FILTER:
	حالة OMP_CLAUSE_DEFAULTMAP:
	حالة OMP_CLAUSE_BIND:
	حالة OMP_CLAUSE_NUM_GANGS:
	حالة OMP_CLAUSE_NUM_WORKERS:
	حالة OMP_CLAUSE_VECTOR_LENGTH:
	حالة OMP_CLAUSE_ASYNC:
	حالة OMP_CLAUSE_WAIT:
	حالة OMP_CLAUSE_AUTO:
	حالة OMP_CLAUSE_INDEPENDENT:
	حالة OMP_CLAUSE_SEQ:
	حالة OMP_CLAUSE_GANG:
	حالة OMP_CLAUSE_WORKER:
	حالة OMP_CLAUSE_VECTOR:
	حالة OMP_CLAUSE_TILE:
	حالة OMP_CLAUSE_IF_PRESENT:
	حالة OMP_CLAUSE_FINALIZE:
	حالة OMP_CLAUSE_NOHOST:
	حالة OMP_CLAUSE_INDIRECT:
	حالة OMP_CLAUSE_NOVARIANTS:
	حالة OMP_CLAUSE_NOCONTEXT:
	  pc = &OMP_CLAUSE_CHAIN (c);
	  استمر;

	حالة OMP_CLAUSE_GRAINSIZE:
	  grainsize_seen = pc;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  استمر;

	حالة OMP_CLAUSE_NUM_TASKS:
	  num_tasks_seen = true;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  استمر;

	حالة OMP_CLAUSE_MERGEABLE:
	  mergeable_seen = true;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  استمر;

	حالة OMP_CLAUSE_NOGROUP:
	  nogroup_seen = pc;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  استمر;

	حالة OMP_CLAUSE_SCHEDULE:
	  schedule_clause = c;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  استمر;

	حالة OMP_CLAUSE_ORDERED:
	  ordered_clause = c;
	  𐤀𐤌 (order_clause)
	    {
	      error_at (OMP_CLAUSE_LOCATION (*order_clause),
			"%<order%> clause must not be used together "
			"with %<ordered%> clause");
	      *order_clause = OMP_CLAUSE_CHAIN (*order_clause);
	      order_clause = عدم;
	    }
	  pc = &OMP_CLAUSE_CHAIN (c);
	  استمر;

	حالة OMP_CLAUSE_SAFELEN:
	  safelen = c;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  استمر;
	حالة OMP_CLAUSE_SIMDLEN:
	  simdlen = c;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  استمر;

	حالة OMP_CLAUSE_FULL:
	  full_seen = pc;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  استمر;

	حالة OMP_CLAUSE_PARTIAL:
	  partial_seen = true;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  استمر;

	حالة OMP_CLAUSE_SIZES:
	  pc = &OMP_CLAUSE_CHAIN (c);
	  استمر;

	حالة OMP_CLAUSE_INBRANCH:
	حالة OMP_CLAUSE_NOTINBRANCH:
	  𐤀𐤌 (branch_seen)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<inbranch%> clause is incompatible with "
			"%<notinbranch%>");
	      remove = true;
	      اكسر;
	    }
	  branch_seen = true;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  استمر;

	حالة OMP_CLAUSE_INCLUSIVE:
	حالة OMP_CLAUSE_EXCLUSIVE:
	  need_complete = true;
	  need_implicitly_determined = true;
	  t = OMP_CLAUSE_DECL (c);
	  𐤀𐤌 (!VAR_P (t) && TREE_CODE (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in clause %qs", t,
			omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	      remove = true;
	    }
	  اكسر;

	حالة OMP_CLAUSE_INIT:
	  init_seen = true;
	  𐤀𐤌 (!OMP_CLAUSE_INIT_TARGETSYNC (c))
	    init_no_targetsync_clause = c;
	  /* FALLTHRU */
	حالة OMP_CLAUSE_DESTROY:
	حالة OMP_CLAUSE_USE:
	  init_use_destroy_seen = true;
	  t = OMP_CLAUSE_DECL (c);
	  𐤀𐤌 (bitmap_bit_p (&generic_head, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qD appears more than once in action clauses", t);
	      remove = true;
	      اكسر;
	    }
	  bitmap_set_bit (&generic_head, DECL_UID (t));
	  /* FALLTHRU */
	حالة OMP_CLAUSE_INTEROP:
	  𐤀𐤌 (/* ort == C_ORT_OMP_INTEROP [uncomment for depobj init]  */
		   !c_omp_interop_t_p (TREE_TYPE (OMP_CLAUSE_DECL (c))))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qD must be of %<omp_interop_t%>",
			OMP_CLAUSE_DECL (c));
	      remove = true;
	    }
	  وإلا 𐤀𐤌 ((OMP_CLAUSE_CODE (c) == OMP_CLAUSE_INIT
		    || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DESTROY)
		   && TREE_READONLY (OMP_CLAUSE_DECL (c)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
		      "%qD shall not be const", OMP_CLAUSE_DECL (c));
	      remove = true;
	    }
	  pc = &OMP_CLAUSE_CHAIN (c);
	  اكسر;
	افتراضي:
	  gcc_unreachable ();
	}

      𐤀𐤌 (!remove)
	{
	  t = OMP_CLAUSE_DECL (c);

	  𐤀𐤌 (need_complete)
	    {
	      t = require_complete_type (OMP_CLAUSE_LOCATION (c), t);
	      𐤀𐤌 (t == error_mark_node)
		remove = true;
	    }

	  𐤀𐤌 (need_implicitly_determined)
	    {
	      ثابت حرف *share_name = عدم;

	      𐤀𐤌 (VAR_P (t) && DECL_THREAD_LOCAL_P (t))
		share_name = "threadprivate";
	      وإلا بدل (c_omp_predetermined_sharing (t))
		{
		حالة OMP_CLAUSE_DEFAULT_UNSPECIFIED:
		  اكسر;
		حالة OMP_CLAUSE_DEFAULT_SHARED:
		  𐤀𐤌 ((OMP_CLAUSE_CODE (c) == OMP_CLAUSE_SHARED
		       || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_FIRSTPRIVATE)
		      && c_omp_predefined_variable (t))
		    /* The __func__ variable and similar function-local
		       predefined variables may be listed in a shared or
		       firstprivate clause.  */
		    اكسر;
		  share_name = "shared";
		  اكسر;
		حالة OMP_CLAUSE_DEFAULT_PRIVATE:
		  share_name = "private";
		  اكسر;
		افتراضي:
		  gcc_unreachable ();
		}
	      𐤀𐤌 (share_name)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qE is predetermined %qs for %qs",
			    t, share_name,
			    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		  remove = true;
		}
	      وإلا 𐤀𐤌 (TREE_READONLY (t)
		       && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_SHARED
		       && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_FIRSTPRIVATE)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%<const%> qualified %qE may appear only in "
			    "%<shared%> or %<firstprivate%> clauses", t);
		  remove = true;
		}
	    }
	}

      𐤀𐤌 (remove)
	{
	  𐤀𐤌 (grp_start_p)
	    {
	      /* If we found a clause to remove, we want to remove the whole
		 expanded group, otherwise gimplify
		 (omp_resolve_clause_dependencies) can get confused.  */
	      *grp_start_p = grp_sentinel;
	      pc = grp_start_p;
	      grp_start_p = عدم;
	    }
	  وإلا
	    *pc = OMP_CLAUSE_CHAIN (c);
	}
      وإلا
	pc = &OMP_CLAUSE_CHAIN (c);
    }

  𐤀𐤌 (grp_start_p
      && OMP_CLAUSE_HAS_ITERATORS (*grp_start_p))
    لكل (tree gc = *grp_start_p; gc; gc = OMP_CLAUSE_CHAIN (gc))
      OMP_CLAUSE_ITERATORS (gc) = OMP_CLAUSE_ITERATORS (*grp_start_p);

  𐤀𐤌 (simdlen
      && safelen
      && tree_int_cst_lt (OMP_CLAUSE_SAFELEN_EXPR (safelen),
			  OMP_CLAUSE_SIMDLEN_EXPR (simdlen)))
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
      OMP_CLAUSE_SIMDLEN_EXPR (simdlen)
	= OMP_CLAUSE_SAFELEN_EXPR (safelen);
    }

  𐤀𐤌 (ordered_clause
      && schedule_clause
      && (OMP_CLAUSE_SCHEDULE_KIND (schedule_clause)
	  & OMP_CLAUSE_SCHEDULE_NONMONOTONIC))
    {
      error_at (OMP_CLAUSE_LOCATION (schedule_clause),
		"%<nonmonotonic%> schedule modifier specified together "
		"with %<ordered%> clause");
      OMP_CLAUSE_SCHEDULE_KIND (schedule_clause)
	= (تعداد omp_clause_schedule_kind)
	  (OMP_CLAUSE_SCHEDULE_KIND (schedule_clause)
	   & ~OMP_CLAUSE_SCHEDULE_NONMONOTONIC);
    }

  𐤀𐤌 (reduction_seen < 0 && ordered_clause)
    {
      error_at (OMP_CLAUSE_LOCATION (ordered_clause),
		"%qs clause specified together with %<inscan%> "
		"%<reduction%> clause", "ordered");
      reduction_seen = -2;
    }

  𐤀𐤌 (reduction_seen < 0 && schedule_clause)
    {
      error_at (OMP_CLAUSE_LOCATION (schedule_clause),
		"%qs clause specified together with %<inscan%> "
		"%<reduction%> clause", "schedule");
      reduction_seen = -2;
    }

  𐤀𐤌 (linear_variable_step_check
      || reduction_seen == -2
      || allocate_seen
      || target_in_reduction_seen)
    لكل (pc = &clauses, c = clauses; c ; c = *pc)
      {
	منطقي remove = خطأ;
	𐤀𐤌 (allocate_seen)
	  بدل (OMP_CLAUSE_CODE (c))
	    {
	    حالة OMP_CLAUSE_REDUCTION:
	    حالة OMP_CLAUSE_IN_REDUCTION:
	    حالة OMP_CLAUSE_TASK_REDUCTION:
	      𐤀𐤌 (TREE_CODE (OMP_CLAUSE_DECL (c)) == MEM_REF)
		{
		  t = TREE_OPERAND (OMP_CLAUSE_DECL (c), 0);
		  𐤀𐤌 (TREE_CODE (t) == POINTER_PLUS_EXPR)
		    t = TREE_OPERAND (t, 0);
		  𐤀𐤌 (TREE_CODE (t) == ADDR_EXPR
		      || INDIRECT_REF_P (t))
		    t = TREE_OPERAND (t, 0);
		  𐤀𐤌 (DECL_P (t))
		    bitmap_clear_bit (&aligned_head, DECL_UID (t));
		  اكسر;
		}
	      /* FALLTHRU */
	    حالة OMP_CLAUSE_PRIVATE:
	    حالة OMP_CLAUSE_FIRSTPRIVATE:
	    حالة OMP_CLAUSE_LASTPRIVATE:
	    حالة OMP_CLAUSE_LINEAR:
	      𐤀𐤌 (DECL_P (OMP_CLAUSE_DECL (c)))
		bitmap_clear_bit (&aligned_head,
				  DECL_UID (OMP_CLAUSE_DECL (c)));
	      اكسر;
	    افتراضي:
	      اكسر;
	    }
	𐤀𐤌 (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_LINEAR
	    && OMP_CLAUSE_LINEAR_VARIABLE_STRIDE (c)
	    && !bitmap_bit_p (&map_head,
			      DECL_UID (OMP_CLAUSE_LINEAR_STEP (c))))
	  {
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%<linear%> clause step is a parameter %qD not "
		      "specified in %<uniform%> clause",
		      OMP_CLAUSE_LINEAR_STEP (c));
	    remove = true;
	  }
	وإلا 𐤀𐤌 (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_REDUCTION
		 && reduction_seen == -2)
	  OMP_CLAUSE_REDUCTION_INSCAN (c) = 0;
	𐤀𐤌 (target_in_reduction_seen
	    && OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP)
	  {
	    tree t = OMP_CLAUSE_DECL (c);
	    طالما (handled_component_p (t)
		   || INDIRECT_REF_P (t)
		   || TREE_CODE (t) == ADDR_EXPR
		   || TREE_CODE (t) == MEM_REF
		   || TREE_CODE (t) == NON_LVALUE_EXPR)
	      t = TREE_OPERAND (t, 0);
	    𐤀𐤌 (DECL_P (t)
		&& bitmap_bit_p (&oacc_reduction_head, DECL_UID (t)))
	      OMP_CLAUSE_MAP_IN_REDUCTION (c) = 1;
	  }

	𐤀𐤌 (remove)
	  *pc = OMP_CLAUSE_CHAIN (c);
	وإلا
	  pc = &OMP_CLAUSE_CHAIN (c);
      }

  𐤀𐤌 (allocate_seen)
    لكل (pc = &clauses, c = clauses; c ; c = *pc)
      {
	منطقي remove = خطأ;
	𐤀𐤌 (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_ALLOCATE
	    && !OMP_CLAUSE_ALLOCATE_COMBINED (c)
	    && bitmap_bit_p (&aligned_head, DECL_UID (OMP_CLAUSE_DECL (c))))
	  {
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%qD specified in %<allocate%> clause but not in "
		      "an explicit privatization clause", OMP_CLAUSE_DECL (c));
	    remove = true;
	  }
	𐤀𐤌 (remove)
	  *pc = OMP_CLAUSE_CHAIN (c);
	وإلا
	  pc = &OMP_CLAUSE_CHAIN (c);
      }

  𐤀𐤌 (nogroup_seen && reduction_seen)
    {
      error_at (OMP_CLAUSE_LOCATION (*nogroup_seen),
		"%<nogroup%> clause must not be used together with "
		"%<reduction%> clause");
      *nogroup_seen = OMP_CLAUSE_CHAIN (*nogroup_seen);
    }

  𐤀𐤌 (grainsize_seen && num_tasks_seen)
    {
      error_at (OMP_CLAUSE_LOCATION (*grainsize_seen),
		"%<grainsize%> clause must not be used together with "
		"%<num_tasks%> clause");
      *grainsize_seen = OMP_CLAUSE_CHAIN (*grainsize_seen);
    }

  𐤀𐤌 (full_seen && partial_seen)
    {
      error_at (OMP_CLAUSE_LOCATION (*full_seen),
		"%<full%> clause must not be used together with "
		"%<partial%> clause");
      *full_seen = OMP_CLAUSE_CHAIN (*full_seen);
    }

  𐤀𐤌 (detach_seen)
    {
      𐤀𐤌 (mergeable_seen)
	{
	  error_at (OMP_CLAUSE_LOCATION (*detach_seen),
		    "%<detach%> clause must not be used together with "
		    "%<mergeable%> clause");
	  *detach_seen = OMP_CLAUSE_CHAIN (*detach_seen);
	}
      وإلا
	{
	  tree detach_decl = OMP_CLAUSE_DECL (*detach_seen);

	  لكل (pc = &clauses, c = clauses; c ; c = *pc)
	    {
	      منطقي remove = خطأ;
	      𐤀𐤌 ((OMP_CLAUSE_CODE (c) == OMP_CLAUSE_SHARED
		   || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_PRIVATE
		   || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_FIRSTPRIVATE
		   || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_LASTPRIVATE)
		  && OMP_CLAUSE_DECL (c) == detach_decl)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "the event handle of a %<detach%> clause "
			    "should not be in a data-sharing clause");
		  remove = true;
		}
	      𐤀𐤌 (remove)
		*pc = OMP_CLAUSE_CHAIN (c);
	      وإلا
		pc = &OMP_CLAUSE_CHAIN (c);
	    }
	}
    }

  𐤀𐤌 (ort == C_ORT_OMP_INTEROP
      && depend_clause
      && (!init_use_destroy_seen
	  || (init_seen && init_no_targetsync_clause)))
    {
      error_at (OMP_CLAUSE_LOCATION (depend_clause),
		"%<depend%> clause requires action clauses with "
		"%<targetsync%> interop-type");
      𐤀𐤌 (init_no_targetsync_clause)
	inform (OMP_CLAUSE_LOCATION (init_no_targetsync_clause),
		"%<init%> clause lacks the %<targetsync%> modifier");
    }

  bitmap_obstack_release (عدم);
  أرجع clauses;
}

/* Do processing necessary to make CLAUSES well-formed, where CLAUSES result
   from implicit instantiation of user-defined mappers (in gimplify.cc).  */

tree
c_omp_finish_mapper_clauses (tree clauses)
{
  أرجع c_finish_omp_clauses (clauses, C_ORT_OMP);
}

/* Return code to initialize DST with a copy constructor from SRC.
   C doesn't have copy constructors nor assignment operators, only for
   _Atomic vars we need to perform __atomic_load from src into a temporary
   followed by __atomic_store of the temporary to dst.  */

tree
c_omp_clause_copy_ctor (tree clause, tree dst, tree src)
{
  𐤀𐤌 (!really_atomic_lvalue (dst) && !really_atomic_lvalue (src))
    أرجع build2 (MODIFY_EXPR, TREE_TYPE (dst), dst, src);

  location_t loc = OMP_CLAUSE_LOCATION (clause);
  tree type = TREE_TYPE (dst);
  tree nonatomic_type = build_qualified_type (type, TYPE_UNQUALIFIED);
  tree tmp = create_tmp_var (nonatomic_type);
  tree tmp_addr = build_fold_addr_expr (tmp);
  TREE_ADDRESSABLE (tmp) = 1;
  suppress_warning (tmp);
  tree src_addr = build_fold_addr_expr (src);
  tree dst_addr = build_fold_addr_expr (dst);
  tree seq_cst = build_int_cst (integer_type_node, MEMMODEL_SEQ_CST);
  vec<tree, va_gc> *params;
  /* Expansion of a generic atomic load may require an addition
     element, so allocate enough to prevent a resize.  */
  vec_alloc (params, 4);

  /* Build __atomic_load (&src, &tmp, SEQ_CST);  */
  tree fndecl = builtin_decl_explicit (BUILT_IN_ATOMIC_LOAD);
  params->quick_push (src_addr);
  params->quick_push (tmp_addr);
  params->quick_push (seq_cst);
  tree load = c_build_function_call_vec (loc, vNULL, fndecl, params, عدم);

  vec_alloc (params, 4);

  /* Build __atomic_store (&dst, &tmp, SEQ_CST);  */
  fndecl = builtin_decl_explicit (BUILT_IN_ATOMIC_STORE);
  params->quick_push (dst_addr);
  params->quick_push (tmp_addr);
  params->quick_push (seq_cst);
  tree store = c_build_function_call_vec (loc, vNULL, fndecl, params, عدم);
  أرجع build2 (COMPOUND_EXPR, void_type_node, load, store);
}

/* Create a transaction node.  */

tree
c_finish_transaction (location_t loc, tree block, صحيح flags)
{
  tree stmt = build_stmt (loc, TRANSACTION_EXPR, block);
  𐤀𐤌 (flags & TM_STMT_ATTR_OUTER)
    TRANSACTION_EXPR_OUTER (stmt) = 1;
  𐤀𐤌 (flags & TM_STMT_ATTR_RELAXED)
    TRANSACTION_EXPR_RELAXED (stmt) = 1;
  أرجع add_stmt (stmt);
}

/* Make a variant type in the proper way for C/C++, propagating qualifiers
   down to the element type of an array.  If ORIG_QUAL_TYPE is not
   NULL, then it should be used as the qualified type
   ORIG_QUAL_INDIRECT levels down in array type derivation (to
   preserve information about the typedef name from which an array
   type was derived).  */

tree
c_build_qualified_type (tree type, صحيح type_quals, tree orig_qual_type,
			size_t orig_qual_indirect)
{
  𐤀𐤌 (type == error_mark_node)
    أرجع type;

  𐤀𐤌 (TREE_CODE (type) == ARRAY_TYPE)
    {
      tree t;
      tree element_type = c_build_qualified_type (TREE_TYPE (type),
						  type_quals, orig_qual_type,
						  orig_qual_indirect - 1);

      /* See if we already have an identically qualified type.  */
      𐤀𐤌 (orig_qual_type && orig_qual_indirect == 0)
	t = orig_qual_type;
      وإلا
	لكل (t = TYPE_MAIN_VARIANT (type); t; t = TYPE_NEXT_VARIANT (t))
	  {
	    𐤀𐤌 (TYPE_QUALS (strip_array_types (t)) == type_quals
		&& TYPE_NAME (t) == TYPE_NAME (type)
		&& TYPE_CONTEXT (t) == TYPE_CONTEXT (type)
		&& attribute_list_equal (TYPE_ATTRIBUTES (t),
					 TYPE_ATTRIBUTES (type)))
	      اكسر;
	  }
      𐤀𐤌 (!t)
	{
          tree domain = TYPE_DOMAIN (type);

	  t = build_variant_type_copy (type);
	  TREE_TYPE (t) = element_type;
	  TYPE_ADDR_SPACE (t) = TYPE_ADDR_SPACE (element_type);

          𐤀𐤌 (TYPE_STRUCTURAL_EQUALITY_P (element_type)
              || (domain && TYPE_STRUCTURAL_EQUALITY_P (domain)))
            SET_TYPE_STRUCTURAL_EQUALITY (t);
          وإلا 𐤀𐤌 (TYPE_CANONICAL (element_type) != element_type
                   || (domain && TYPE_CANONICAL (domain) != domain))
            {
              tree unqualified_canon
		= c_build_array_type (TYPE_CANONICAL (element_type),
				      domain ? TYPE_CANONICAL (domain)
					     : NULL_TREE);
              𐤀𐤌 (TYPE_REVERSE_STORAGE_ORDER (type))
                {
                  unqualified_canon
		    = build_distinct_type_copy (unqualified_canon);
                  TYPE_REVERSE_STORAGE_ORDER (unqualified_canon) = 1;
                }
              TYPE_CANONICAL (t)
		= c_build_qualified_type (unqualified_canon, type_quals);
            }
          وإلا
            TYPE_CANONICAL (t) = t;
	}
      أرجع t;
    }

  /* A restrict-qualified pointer type must be a pointer to object or
     incomplete type.  Note that the use of POINTER_TYPE_P also allows
     REFERENCE_TYPEs, which is appropriate for C++.  */
  𐤀𐤌 ((type_quals & TYPE_QUAL_RESTRICT)
      && (!POINTER_TYPE_P (type)
	  || !C_TYPE_OBJECT_OR_INCOMPLETE_P (TREE_TYPE (type))))
    {
      error ("invalid use of %<restrict%>");
      type_quals &= ~TYPE_QUAL_RESTRICT;
    }

  tree var_type = (orig_qual_type && orig_qual_indirect == 0
		   ? orig_qual_type
		   : build_qualified_type (type, type_quals));

  gcc_checking_assert (C_TYPE_VARIABLE_SIZE (var_type)
		       == C_TYPE_VARIABLE_SIZE (type));
  gcc_checking_assert (c_type_variably_modified_p (var_type)
		       == c_type_variably_modified_p (type));

  /* A variant type does not inherit the list of incomplete vars from the
     type main variant.  */
  𐤀𐤌 ((RECORD_OR_UNION_TYPE_P (var_type)
       || TREE_CODE (var_type) == ENUMERAL_TYPE)
      && TYPE_MAIN_VARIANT (var_type) != var_type)
    C_TYPE_INCOMPLETE_VARS (var_type) = 0;
  أرجع var_type;
}

/* Build a VA_ARG_EXPR for the C parser.  */

tree
c_build_va_arg (location_t loc1, tree expr, location_t loc2, tree type,
		tree type_expr)
{
  𐤀𐤌 (error_operand_p (type))
    أرجع error_mark_node;
  /* VA_ARG_EXPR cannot be used for a scalar va_list with reverse storage
     order because it takes the address of the expression.  */
  وإلا 𐤀𐤌 (handled_component_p (expr)
	   && reverse_storage_order_for_component_p (expr))
    {
      error_at (loc1, "cannot use %<va_arg%> with reverse storage order");
      أرجع error_mark_node;
    }
  وإلا 𐤀𐤌 (!COMPLETE_TYPE_P (type))
    {
      error_at (loc2, "second argument to %<va_arg%> is of incomplete "
		"type %qT", type);
      أرجع error_mark_node;
    }
  وإلا 𐤀𐤌 (TREE_CODE (type) == FUNCTION_TYPE)
    {
      error_at (loc2, "second argument to %<va_arg%> is a function type %qT",
		type);
      أرجع error_mark_node;
    }
  وإلا 𐤀𐤌 (TREE_CODE (type) == ARRAY_TYPE && C_TYPE_VARIABLE_SIZE (type)
	   && !flag_isoc99)
    {
      error_at (loc2, "second argument to %<va_arg%> is an array type %qT",
		type);
      أرجع error_mark_node;
    }
  وإلا 𐤀𐤌 (warn_cxx_compat && TREE_CODE (type) == ENUMERAL_TYPE)
    warning_at (loc2, OPT_Wc___compat,
		"C++ requires promoted type, not enum type, in %<va_arg%>");

  𐤀𐤌 (flag_isoc99 && TREE_CODE (type) == ARRAY_TYPE)
    {
      warning_at (loc2, 0, "second argument to %<va_arg%> is an array type %qT",
		  type);
      /* We create a trap but evaluate side effects first.  */
      tree trapfn = builtin_decl_explicit (BUILT_IN_TRAP);
      trapfn = build_call_expr_loc (loc2, trapfn, 0);
      tree e2 = build2 (COMPOUND_EXPR, void_type_node, expr, trapfn);
      /* Return a compound literal of the right type.  */
      tree e1 = build_compound_literal (loc2, type, عدم, true, 0, عدم);
      expr = build2 (COMPOUND_EXPR, type, e2, e1);
    }
  وإلا
    expr = build_va_arg (loc2, expr, type);

  𐤀𐤌 (type_expr)
    expr = build2 (COMPOUND_EXPR, TREE_TYPE (expr), type_expr, expr);

  أرجع expr;
}

/* Return truthvalue of whether T1 is the same tree structure as T2.
   Return 1 if they are the same. Return false if they are different.  */

منطقي
c_tree_equal (tree t1, tree t2)
{
  تعداد tree_code code1, code2;

  𐤀𐤌 (t1 == t2)
    أرجع true;
  𐤀𐤌 (!t1 || !t2)
    أرجع خطأ;

  لكل (code1 = TREE_CODE (t1); code1 == NON_LVALUE_EXPR;
       code1 = TREE_CODE (t1))
    t1 = TREE_OPERAND (t1, 0);
  لكل (code2 = TREE_CODE (t2); code2 == NON_LVALUE_EXPR;
       code2 = TREE_CODE (t2))
    t2 = TREE_OPERAND (t2, 0);

  /* They might have become equal now.  */
  𐤀𐤌 (t1 == t2)
    أرجع true;

  𐤀𐤌 (code1 != code2)
    أرجع خطأ;

  𐤀𐤌 (CONSTANT_CLASS_P (t1) && !comptypes (TREE_TYPE (t1), TREE_TYPE (t2)))
    أرجع خطأ;

  بدل (code1)
    {
    حالة INTEGER_CST:
      أرجع wi::to_wide (t1) == wi::to_wide (t2);

    حالة REAL_CST:
      أرجع real_equal (&TREE_REAL_CST (t1), &TREE_REAL_CST (t2));

    حالة STRING_CST:
      أرجع TREE_STRING_LENGTH (t1) == TREE_STRING_LENGTH (t2)
	&& !memcmp (TREE_STRING_POINTER (t1), TREE_STRING_POINTER (t2),
		    TREE_STRING_LENGTH (t1));

    حالة FIXED_CST:
      أرجع FIXED_VALUES_IDENTICAL (TREE_FIXED_CST (t1),
				     TREE_FIXED_CST (t2));

    حالة COMPLEX_CST:
      أرجع c_tree_equal (TREE_REALPART (t1), TREE_REALPART (t2))
	     && c_tree_equal (TREE_IMAGPART (t1), TREE_IMAGPART (t2));

    حالة VECTOR_CST:
      أرجع operand_equal_p (t1, t2, OEP_ONLY_CONST);

    حالة CONSTRUCTOR:
      /* We need to do this when determining whether or not two
	 non-type pointer to member function template arguments
	 are the same.  */
      𐤀𐤌 (!comptypes (TREE_TYPE (t1), TREE_TYPE (t2))
	  || CONSTRUCTOR_NELTS (t1) != CONSTRUCTOR_NELTS (t2))
	أرجع خطأ;
      {
	tree field, value;
	unsigned صحيح i;
	FOR_EACH_CONSTRUCTOR_ELT (CONSTRUCTOR_ELTS (t1), i, field, value)
	  {
	    constructor_elt *elt2 = CONSTRUCTOR_ELT (t2, i);
	    𐤀𐤌 (!c_tree_equal (field, elt2->index)
		|| !c_tree_equal (value, elt2->value))
	      أرجع خطأ;
	  }
      }
      أرجع true;

    حالة TREE_LIST:
      𐤀𐤌 (!c_tree_equal (TREE_PURPOSE (t1), TREE_PURPOSE (t2)))
	أرجع خطأ;
      𐤀𐤌 (!c_tree_equal (TREE_VALUE (t1), TREE_VALUE (t2)))
	أرجع خطأ;
      أرجع c_tree_equal (TREE_CHAIN (t1), TREE_CHAIN (t2));

    حالة SAVE_EXPR:
      أرجع c_tree_equal (TREE_OPERAND (t1, 0), TREE_OPERAND (t2, 0));

    حالة CALL_EXPR:
      {
	tree arg1, arg2;
	call_expr_arg_iterator iter1, iter2;
	𐤀𐤌 (!c_tree_equal (CALL_EXPR_FN (t1), CALL_EXPR_FN (t2)))
	  أرجع خطأ;
	لكل (arg1 = first_call_expr_arg (t1, &iter1),
	       arg2 = first_call_expr_arg (t2, &iter2);
	     arg1 && arg2;
	     arg1 = next_call_expr_arg (&iter1),
	       arg2 = next_call_expr_arg (&iter2))
	  𐤀𐤌 (!c_tree_equal (arg1, arg2))
	    أرجع خطأ;
	𐤀𐤌 (arg1 || arg2)
	  أرجع خطأ;
	أرجع true;
      }

    حالة TARGET_EXPR:
      {
	tree o1 = TREE_OPERAND (t1, 0);
	tree o2 = TREE_OPERAND (t2, 0);

	/* Special case: if either target is an unallocated VAR_DECL,
	   it means that it's going to be unified with whatever the
	   TARGET_EXPR is really supposed to initialize, so treat it
	   as being equivalent to anything.  */
	𐤀𐤌 (VAR_P (o1) && DECL_NAME (o1) == NULL_TREE
	    && !DECL_RTL_SET_P (o1))
	  /*Nop*/;
	وإلا 𐤀𐤌 (VAR_P (o2) && DECL_NAME (o2) == NULL_TREE
		 && !DECL_RTL_SET_P (o2))
	  /*Nop*/;
	وإلا 𐤀𐤌 (!c_tree_equal (o1, o2))
	  أرجع خطأ;

	أرجع c_tree_equal (TREE_OPERAND (t1, 1), TREE_OPERAND (t2, 1));
      }

    حالة COMPONENT_REF:
      𐤀𐤌 (TREE_OPERAND (t1, 1) != TREE_OPERAND (t2, 1))
	أرجع خطأ;
      أرجع c_tree_equal (TREE_OPERAND (t1, 0), TREE_OPERAND (t2, 0));

    حالة PARM_DECL:
    حالة VAR_DECL:
    حالة CONST_DECL:
    حالة FIELD_DECL:
    حالة FUNCTION_DECL:
    حالة IDENTIFIER_NODE:
    حالة SSA_NAME:
      أرجع خطأ;

    حالة TREE_VEC:
      {
	unsigned ix;
	𐤀𐤌 (TREE_VEC_LENGTH (t1) != TREE_VEC_LENGTH (t2))
	  أرجع خطأ;
	لكل (ix = TREE_VEC_LENGTH (t1); ix--;)
	  𐤀𐤌 (!c_tree_equal (TREE_VEC_ELT (t1, ix),
			     TREE_VEC_ELT (t2, ix)))
	    أرجع خطأ;
	أرجع true;
      }

    CASE_CONVERT:
      𐤀𐤌 (!comptypes (TREE_TYPE (t1), TREE_TYPE (t2)))
	أرجع خطأ;
      اكسر;

    افتراضي:
      اكسر;
    }

  بدل (TREE_CODE_CLASS (code1))
    {
    حالة tcc_unary:
    حالة tcc_binary:
    حالة tcc_comparison:
    حالة tcc_expression:
    حالة tcc_vl_exp:
    حالة tcc_reference:
    حالة tcc_statement:
      {
	صحيح i, n = TREE_OPERAND_LENGTH (t1);

	بدل (code1)
	  {
	  حالة PREINCREMENT_EXPR:
	  حالة PREDECREMENT_EXPR:
	  حالة POSTINCREMENT_EXPR:
	  حالة POSTDECREMENT_EXPR:
	    n = 1;
	    اكسر;
	  حالة ARRAY_REF:
	    n = 2;
	    اكسر;
	  افتراضي:
	    اكسر;
	  }

	𐤀𐤌 (TREE_CODE_CLASS (code1) == tcc_vl_exp
	    && n != TREE_OPERAND_LENGTH (t2))
	  أرجع خطأ;

	لكل (i = 0; i < n; ++i)
	  𐤀𐤌 (!c_tree_equal (TREE_OPERAND (t1, i), TREE_OPERAND (t2, i)))
	    أرجع خطأ;

	أرجع true;
      }

    حالة tcc_type:
      أرجع comptypes (t1, t2);
    افتراضي:
      gcc_unreachable ();
    }
}

/* Returns true when the function declaration FNDECL is implicit,
   introduced as a result of a call to an otherwise undeclared
   function, and false otherwise.  */

منطقي
c_decl_implicit (const_tree fndecl)
{
  أرجع C_DECL_IMPLICIT (fndecl);
}
