/* Process declarations and variables for C compiler.
   Copyright (C) 1988-2026 Free Software Foundation, Inc.

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

/* Process declarations and symbol lookup for C front end.
   Also constructs types; the standard scalar types at initialization,
   and structure, union, array and enum types when they are declared.  */

/* ??? not all decl nodes are given the most useful possible
   line numbers.  For example, the CONST_DECLs for enum values.  */

#ಅನ್ತರ್ಭಾವ "config.h"
#ವ್ಯಾಖ್ಯಾನಿಸು INCLUDE_STRING
#ಅನ್ತರ್ಭಾವ "system.h"
#ಅನ್ತರ್ಭಾವ "coretypes.h"
#ಅನ್ತರ್ಭಾವ "target.h"
#ಅನ್ತರ್ಭಾವ "function.h"
#ಅನ್ತರ್ಭಾವ "c-tree.h"
#ಅನ್ತರ್ಭಾವ "timevar.h"
#ಅನ್ತರ್ಭಾವ "stringpool.h"
#ಅನ್ತರ್ಭಾವ "cgraph.h"
#ಅನ್ತರ್ಭಾವ "intl.h"
#ಅನ್ತರ್ಭಾವ "print-tree.h"
#ಅನ್ತರ್ಭಾವ "stor-layout.h"
#ಅನ್ತರ್ಭಾವ "varasm.h"
#ಅನ್ತರ್ಭಾವ "attribs.h"
#ಅನ್ತರ್ಭಾವ "toplev.h"
#ಅನ್ತರ್ಭಾವ "debug.h"
#ಅನ್ತರ್ಭಾವ "c-family/c-objc.h"
#ಅನ್ತರ್ಭಾವ "c-family/c-pragma.h"
#ಅನ್ತರ್ಭಾವ "c-family/c-ubsan.h"
#ಅನ್ತರ್ಭಾವ "c-lang.h"
#ಅನ್ತರ್ಭಾವ "langhooks.h"
#ಅನ್ತರ್ಭಾವ "tree-iterator.h"
#ಅನ್ತರ್ಭಾವ "dumpfile.h"
#ಅನ್ತರ್ಭಾವ "plugin.h"
#ಅನ್ತರ್ಭಾವ "c-family/c-ada-spec.h"
#ಅನ್ತರ್ಭಾವ "builtins.h"
#ಅನ್ತರ್ಭಾವ "spellcheck-tree.h"
#ಅನ್ತರ್ಭಾವ "gcc-rich-location.h"
#ಅನ್ತರ್ಭಾವ "asan.h"
#ಅನ್ತರ್ಭಾವ "c-family/name-hint.h"
#ಅನ್ತರ್ಭಾವ "c-family/known-headers.h"
#ಅನ್ತರ್ಭಾವ "c-family/c-spellcheck.h"
#ಅನ್ತರ್ಭಾವ "context.h"  /* For 'g'.  */
#ಅನ್ತರ್ಭಾವ "omp-general.h"
#ಅನ್ತರ್ಭಾವ "omp-offload.h"  /* For offload_vars.  */
#ಅನ್ತರ್ಭಾವ "c-parser.h"
#ಅನ್ತರ್ಭಾವ "gcc-urlifier.h"

#ಅನ್ತರ್ಭಾವ "tree-pretty-print.h"

/* In grokdeclarator, distinguish syntactic contexts of declarators.  */
ಎಣಿಕೆ decl_context
{ ಸಾಮಾನ್ಯ,			/* Ordinary declaration */
  FUNCDEF,			/* Function definition */
  PARM,				/* Declaration of parm before function body */
  ಕ್ಷೇತ್ರ,			/* Declaration inside struct or union */
  TYPENAME,			/* Typename (inside cast or sizeof)  */
  GENERIC_ASSOC };		/* Typename in generic association  */

/* States indicating how grokdeclarator() should handle declspecs marked
   with __attribute__((deprecated)) or __attribute__((unavailable)).
   An object declared as __attribute__((unavailable)) should suppress
   any reports of being declared  with unavailable or deprecated items.
   An object declared as __attribute__((deprecated)) should suppress
   warnings of uses of other deprecated items.  */

ಎಣಿಕೆ deprecated_ಸ್ಥಿತಿಗಳು {
  DEPRECATED_ಸಾಮಾನ್ಯ,
  DEPRECATED_SUPPRESS,
  UNAVAILABLE_DEPRECATED_SUPPRESS
};


/* Nonzero if we have seen an invalid cross reference
   to a struct, union, or enum, but not yet printed the message.  */
ವೃಕ್ಷ pending_invalid_xref;

/* File and line to appear in the eventual error message.  */
location_t pending_invalid_xref_location;

/* The file and line that the prototype came from if this is an
   old-style definition; used for diagnostics in
   store_parm_decls_oldstyle.  */

ಸ್ಥಿರ location_t current_function_prototype_locus;

/* Whether this prototype was built-in.  */

ಸ್ಥಿರ ತಾರ್ಕಿಕ current_function_prototype_built_ಒಳ;

/* The argument type information of this prototype.  */

ಸ್ಥಿರ ವೃಕ್ಷ current_function_prototype_arg_types;

/* The argument information structure for the function currently being
   defined.  */

ಸ್ಥಿರ ರಚನೆ c_arg_info *current_function_arg_info;

/* The obstack on which parser and related data structures, which are
   not live beyond their top-level declaration or definition, are
   allocated.  */
ರಚನೆ obstack parser_obstack;

/* The current statement tree.  */

ಸ್ಥಿರ GTY(()) ರಚನೆ stmt_ವೃಕ್ಷ_s c_stmt_ವೃಕ್ಷ;

/* Zero if we are not in an iteration or switch statement, otherwise
   a bitmask.  See bitmask definitions in c-tree.h.  */
ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ ಒಳ_statement;

/* A list of decls to be made automatically visible in each file scope.  */
ಸ್ಥಿರ GTY(()) ವೃಕ್ಷ visible_builtins;

/* Set to 0 at beginning of a function definition, set to 1 if
   a return statement that specifies a return value is seen.  */

ಪೂರ್ಣಾಂಕ current_function_returns_ಮೌಲ್ಯ;

/* Set to 0 at beginning of a function definition, set to 1 if
   a return statement with no argument is seen.  */

ಪೂರ್ಣಾಂಕ current_function_returns_null;

/* Set to 0 at beginning of a function definition, set to 1 if
   a call to a noreturn function is seen.  */

ಪೂರ್ಣಾಂಕ current_function_returns_abnormally;

/* Set to nonzero by `grokdeclarator' for a function
   whose return type is defaulted, if warnings for this are desired.  */

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ warn_about_return_type;

/* Nonzero when the current toplevel function contains a declaration
   of a nested function which is never defined.  */

ಸ್ಥಿರ ತಾರ್ಕಿಕ undef_nested_function;

/* Vector of implicit "omp declare target" attributes to be added into
   the attribute lists.  */
vec<c_omp_declare_ಗುರಿ_attr, va_gc> *current_omp_declare_ಗುರಿ_attribute;

/* Vector of
   #pragma omp begin assumes ... #pragma omp end assumes regions
   we are in.  */
vec<c_omp_begin_assumes_ದತ್ತಾಂಶ, va_gc> *current_omp_begin_assumes;

/* Vector of "omp begin/end declare variant" blocks we are in.  */
vec<c_omp_declare_variant_attr, va_gc> *current_omp_declare_variant_attribute;

/* Vector of loop names with C_DECL_LOOP_NAME or C_DECL_SWITCH_NAME marked
   LABEL_DECL as the last and canonical for each loop or switch.  */
ಸ್ಥಿರ vec<ವೃಕ್ಷ> loop_ಹೆಸರುಗಳು;

/* Hash table mapping LABEL_DECLs to the canonical LABEL_DECLs if LOOP_NAMES
   vector becomes too long.  */
ಸ್ಥಿರ decl_ವೃಕ್ಷ_map *loop_ಹೆಸರುಗಳು_hash;

/* Each c_binding structure describes one binding of an identifier to
   a decl.  All the decls in a scope - irrespective of namespace - are
   chained together by the ->prev field, which (as the name implies)
   runs in reverse order.  All the decls in a given namespace bound to
   a given identifier are chained by the ->shadowed field, which runs
   from inner to outer scopes.

   The ->decl field usually points to a DECL node, but there are two
   exceptions.  In the namespace of type tags, the bound entity is a
   RECORD_TYPE, UNION_TYPE, or ENUMERAL_TYPE node.  If an undeclared
   identifier is encountered, it is bound to error_mark_node to
   suppress further errors about that identifier in the current
   function.

   The ->u.type field stores the type of the declaration in this scope;
   if NULL, the type is the type of the ->decl field.  This is only of
   relevance for objects with external or internal linkage which may
   be redeclared in inner scopes, forming composite types that only
   persist for the duration of those scopes.  In the external scope,
   this stores the composite of all the types declared for this
   object, visible or not.  The ->inner_comp field (used only at file
   scope) stores whether an incomplete array type at file scope was
   completed at an inner scope to an array size other than 1.

   The ->u.label field is used for labels.  It points to a structure
   which stores additional information used for warnings.

   The depth field is copied from the scope structure that holds this
   decl.  It is used to preserve the proper ordering of the ->shadowed
   field (see bind()) and also for a handful of special-case checks.
   Finally, the invisible bit is true for a decl which should be
   ignored for purposes of normal name lookup, and the nested bit is
   true for a decl that's been bound a second time in an inner scope;
   in all such cases, the binding in the outer scope will have its
   invisible bit true.  */

ರಚನೆ GTY((chain_ಮುಂದಿನ ("%h.prev"))) c_binding {
  ಒಕ್ಕೂಟ GTY(()) {		/* first so GTY desc can use decl */
    ವೃಕ್ಷ GTY((ಟ್ಯಾಗ್ ("0"))) type; /* the type in this scope */
    ರಚನೆ c_label_vars * GTY((ಟ್ಯಾಗ್ ("1"))) label; /* for warnings */
  } GTY((desc ("TREE_CODE (%0.decl) == LABEL_DECL"))) u;
  ವೃಕ್ಷ decl;			/* the decl bound */
  ವೃಕ್ಷ id;			/* the identifier it's bound to */
  ರಚನೆ c_binding *prev;	/* the previous decl in this scope */
  ರಚನೆ c_binding *shadowed;	/* the innermost decl shadowed by this one */
  ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ ಆಳ : 28;      /* depth of this scope */
  ತಾರ್ಕಿಕ invisible : 1;  /* normal lookup should ignore this binding */
  ತಾರ್ಕಿಕ nested : 1;     /* do not set DECL_CONTEXT when popping */
  ತಾರ್ಕಿಕ inner_comp : 1; /* incomplete array completed in inner scope */
  ತಾರ್ಕಿಕ ಒಳ_struct : 1;	/* currently defined as struct field */
  location_t locus;		/* location for nested bindings */
};
#ವ್ಯಾಖ್ಯಾನಿಸು B_ಒಳ_SCOPE(b1, b2) ((b1)->ಆಳ == (b2)->ಆಳ)
#ವ್ಯಾಖ್ಯಾನಿಸು B_ಒಳ_CURRENT_SCOPE(b) ((b)->ಆಳ == current_scope->ಆಳ)
#ವ್ಯಾಖ್ಯಾನಿಸು B_ಒಳ_FILE_SCOPE(b) ((b)->ಆಳ == 1 /*file_scope->depth*/)
#ವ್ಯಾಖ್ಯಾನಿಸು B_ಒಳ_EXTERNAL_SCOPE(b) ((b)->ಆಳ == 0 /*external_scope->depth*/)

/* Each C symbol points to three linked lists of c_binding structures.
   These describe the values of the identifier in the three different
   namespaces defined by the language.  */

ರಚನೆ GTY(()) lang_identifier {
  ರಚನೆ c_common_identifier common_id;
  ರಚನೆ c_binding *ಚಿಹ್ನೆ_binding; /* vars, funcs, constants, typedefs */
  ರಚನೆ c_binding *ಟ್ಯಾಗ್_binding;    /* struct/union/enum tags */
  ರಚನೆ c_binding *label_binding;  /* labels */
};

/* Validate c-lang.cc's assumptions.  */
ಬಾಹ್ಯ ಅಕ್ಷರ C_SIZEOF_STRUCT_LANG_IDENTIFIER_isnt_accurate
[(ಗಾತ್ರ(ರಚನೆ lang_identifier) == C_SIZEOF_STRUCT_LANG_IDENTIFIER) ? 1 : -1];

/* The binding oracle; see c-tree.h.  */
ಶೂನ್ಯ (*c_binding_oracle) (ಎಣಿಕೆ c_oracle_request, ವೃಕ್ಷ identifier);

/* This flag is set on an identifier if we have previously asked the
   binding oracle for this identifier's symbol binding.  */
#ವ್ಯಾಖ್ಯಾನಿಸು I_ಚಿಹ್ನೆ_CHECKED(ಗಂಟು) \
  (ವೃಕ್ಷ_LANG_FLAG_4 (IDENTIFIER_ಗಂಟು_CHECK (ಗಂಟು)))

ಸ್ಥಿರ ಸಾಲೊಳಗೆ ರಚನೆ c_binding* *
i_ಚಿಹ್ನೆ_binding (ವೃಕ್ಷ ಗಂಟು)
{
  ರಚನೆ lang_identifier *lid
    = (ರಚನೆ lang_identifier *) IDENTIFIER_ಗಂಟು_CHECK (ಗಂಟು);

  ಆದರೆ (lid->ಚಿಹ್ನೆ_binding == ಖಾಲಿ
      && c_binding_oracle != ಖಾಲಿ
      && !I_ಚಿಹ್ನೆ_CHECKED (ಗಂಟು))
    {
      /* Set the "checked" flag first, to avoid infinite recursion
	 when the binding oracle calls back into gcc.  */
      I_ಚಿಹ್ನೆ_CHECKED (ಗಂಟು) = 1;
      c_binding_oracle (C_ORACLE_ಚಿಹ್ನೆ, ಗಂಟು);
    }

  ಹಿಂತಿರುಗಿ &lid->ಚಿಹ್ನೆ_binding;
}

#ವ್ಯಾಖ್ಯಾನಿಸು I_ಚಿಹ್ನೆ_BINDING(ಗಂಟು) (*i_ಚಿಹ್ನೆ_binding (ಗಂಟು))

#ವ್ಯಾಖ್ಯಾನಿಸು I_ಚಿಹ್ನೆ_DECL(ಗಂಟು) \
 (I_ಚಿಹ್ನೆ_BINDING(ಗಂಟು) ? I_ಚಿಹ್ನೆ_BINDING(ಗಂಟು)->decl : 0)

/* This flag is set on an identifier if we have previously asked the
   binding oracle for this identifier's tag binding.  */
#ವ್ಯಾಖ್ಯಾನಿಸು I_ಟ್ಯಾಗ್_CHECKED(ಗಂಟು) \
  (ವೃಕ್ಷ_LANG_FLAG_5 (IDENTIFIER_ಗಂಟು_CHECK (ಗಂಟು)))

ಸ್ಥಿರ ಸಾಲೊಳಗೆ ರಚನೆ c_binding **
i_ಟ್ಯಾಗ್_binding (ವೃಕ್ಷ ಗಂಟು)
{
  ರಚನೆ lang_identifier *lid
    = (ರಚನೆ lang_identifier *) IDENTIFIER_ಗಂಟು_CHECK (ಗಂಟು);

  ಆದರೆ (lid->ಟ್ಯಾಗ್_binding == ಖಾಲಿ
      && c_binding_oracle != ಖಾಲಿ
      && !I_ಟ್ಯಾಗ್_CHECKED (ಗಂಟು))
    {
      /* Set the "checked" flag first, to avoid infinite recursion
	 when the binding oracle calls back into gcc.  */
      I_ಟ್ಯಾಗ್_CHECKED (ಗಂಟು) = 1;
      c_binding_oracle (C_ORACLE_ಟ್ಯಾಗ್, ಗಂಟು);
    }

  ಹಿಂತಿರುಗಿ &lid->ಟ್ಯಾಗ್_binding;
}

#ವ್ಯಾಖ್ಯಾನಿಸು I_ಟ್ಯಾಗ್_BINDING(ಗಂಟು) (*i_ಟ್ಯಾಗ್_binding (ಗಂಟು))

#ವ್ಯಾಖ್ಯಾನಿಸು I_ಟ್ಯಾಗ್_DECL(ಗಂಟು) \
 (I_ಟ್ಯಾಗ್_BINDING(ಗಂಟು) ? I_ಟ್ಯಾಗ್_BINDING(ಗಂಟು)->decl : 0)

/* This flag is set on an identifier if we have previously asked the
   binding oracle for this identifier's label binding.  */
#ವ್ಯಾಖ್ಯಾನಿಸು I_LABEL_CHECKED(ಗಂಟು) \
  (ವೃಕ್ಷ_LANG_FLAG_6 (IDENTIFIER_ಗಂಟು_CHECK (ಗಂಟು)))

ಸ್ಥಿರ ಸಾಲೊಳಗೆ ರಚನೆ c_binding **
i_label_binding (ವೃಕ್ಷ ಗಂಟು)
{
  ರಚನೆ lang_identifier *lid
    = (ರಚನೆ lang_identifier *) IDENTIFIER_ಗಂಟು_CHECK (ಗಂಟು);

  ಆದರೆ (lid->label_binding == ಖಾಲಿ
      && c_binding_oracle != ಖಾಲಿ
      && !I_LABEL_CHECKED (ಗಂಟು))
    {
      /* Set the "checked" flag first, to avoid infinite recursion
	 when the binding oracle calls back into gcc.  */
      I_LABEL_CHECKED (ಗಂಟು) = 1;
      c_binding_oracle (C_ORACLE_LABEL, ಗಂಟು);
    }

  ಹಿಂತಿರುಗಿ &lid->label_binding;
}

#ವ್ಯಾಖ್ಯಾನಿಸು I_LABEL_BINDING(ಗಂಟು) (*i_label_binding (ಗಂಟು))

#ವ್ಯಾಖ್ಯಾನಿಸು I_LABEL_DECL(ಗಂಟು) \
 (I_LABEL_BINDING(ಗಂಟು) ? I_LABEL_BINDING(ಗಂಟು)->decl : 0)

/* Used by C_TOKEN_VEC tree.  */
ರಚನೆ GTY (()) c_ವೃಕ್ಷ_token_vec {
  ರಚನೆ ವೃಕ್ಷ_ತಳ ತಳ;
  vec<c_token, va_gc> *ಟೋಕನುಗಳು;
};

STATIC_ASSERT (ಗಾತ್ರ (c_ವೃಕ್ಷ_token_vec) == ಗಾತ್ರ (c_ವೃಕ್ಷ_token_vec_struct));
STATIC_ASSERT (offsetof (c_ವೃಕ್ಷ_token_vec, ಟೋಕನುಗಳು)
	       == offsetof (c_ವೃಕ್ಷ_token_vec_struct, ಟೋಕನುಗಳು));

/* The resulting tree type.  */

ಒಕ್ಕೂಟ GTY((desc ("TREE_CODE (&%h.generic) == IDENTIFIER_NODE + 2 * (TREE_CODE (&%h.generic) == C_TOKEN_VEC)"),
       chain_ಮುಂದಿನ ("(union lang_tree_node *) c_tree_chain_next (&%h.generic)"))) lang_ವೃಕ್ಷ_ಗಂಟು
 {
  ಒಕ್ಕೂಟ ವೃಕ್ಷ_ಗಂಟು GTY ((ಟ್ಯಾಗ್ ("0"),
			desc ("tree_node_structure (&%h)")))
    generic;
  ರಚನೆ lang_identifier GTY ((ಟ್ಯಾಗ್ ("1"))) identifier;
  ರಚನೆ c_ವೃಕ್ಷ_token_vec GTY ((ಟ್ಯಾಗ್ ("2"))) c_token_vec;
};

/* Langhook for tree_size.  */
ಗಾತ್ರ_t
c_ವೃಕ್ಷ_ಗಾತ್ರ (ಎಣಿಕೆ ವೃಕ್ಷ_ಸಂಕೇತ_2 ಸಂಕೇತ_2)
{
  gcc_checking_assert (ಸಂಕೇತ_2 >= ಅಂಕೆ_ವೃಕ್ಷ_CODES);
  ಆಯ್ಕೆ (ಸಂಕೇತ_2)
    {
    ಸ್ಥಿತಿ C_TOKEN_VEC: ಹಿಂತಿರುಗಿ ಗಾತ್ರ (c_ವೃಕ್ಷ_token_vec);
    ಪೂರ್ವನಿಯೋಜಿತ:
      ಆಯ್ಕೆ (ವೃಕ್ಷ_ಸಂಕೇತ_CLASS (ಸಂಕೇತ_2))
	{
	ಸ್ಥಿತಿ tcc_declaration: ಹಿಂತಿರುಗಿ ಗಾತ್ರ (ವೃಕ್ಷ_decl_non_common);
	ಸ್ಥಿತಿ tcc_type: ಹಿಂತಿರುಗಿ ಗಾತ್ರ (ವೃಕ್ಷ_type_non_common);
	ಪೂರ್ವನಿಯೋಜಿತ: gcc_unreachable ();
	}
    }
}

/* Track bindings and other things that matter for goto warnings.  For
   efficiency, we do not gather all the decls at the point of
   definition.  Instead, we point into the bindings structure.  As
   scopes are popped, we update these structures and gather the decls
   that matter at that time.  */

ರಚನೆ GTY(()) c_spot_bindings {
  /* The currently open scope which holds bindings defined when the
     label was defined or the goto statement was found.  */
  ರಚನೆ c_scope *scope;
  /* The bindings in the scope field which were defined at the point
     of the label or goto.  This lets us look at older or newer
     bindings in the scope, as appropriate.  */
  ರಚನೆ c_binding *bindings_ಒಳ_scope;
  /* The number of statement expressions that have started since this
     label or goto statement was defined.  This is zero if we are at
     the same statement expression level.  It is positive if we are in
     a statement expression started since this spot.  It is negative
     if this spot was in a statement expression and we have left
     it.  */
  ಪೂರ್ಣಾಂಕ stmt_exprs;
  /* Whether we started in a statement expression but are no longer in
     it.  This is set to true if stmt_exprs ever goes negative.  */
  ತಾರ್ಕಿಕ ಎಡ_stmt_ಅಭಿವ್ಯಕ್ತಿ;
};

/* This structure is used to keep track of bindings seen when a goto
   statement is defined.  This is only used if we see the goto
   statement before we see the label.  */

ರಚನೆ GTY(()) c_goto_bindings {
  /* The location of the goto statement.  */
  location_t loc;
  /* The bindings of the goto statement.  */
  ರಚನೆ c_spot_bindings goto_bindings;
};

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ c_goto_bindings *c_goto_bindings_p;

/* The additional information we keep track of for a label binding.
   These fields are updated as scopes are popped.  */

ರಚನೆ GTY(()) c_label_vars {
  /* The shadowed c_label_vars, when one label shadows another (which
     can only happen using a __label__ declaration).  */
  ರಚನೆ c_label_vars *shadowed;
  /* The bindings when the label was defined.  */
  ರಚನೆ c_spot_bindings label_bindings;
  /* A list of decls that we care about: decls about which we should
     warn if a goto branches to this label from later in the function.
     Decls are added to this list as scopes are popped.  We only add
     the decls that matter.  */
  vec<ವೃಕ್ಷ, va_gc> *decls_ಒಳ_scope;
  /* A list of goto statements to this label.  This is only used for
     goto statements seen before the label was defined, so that we can
     issue appropriate warnings for them.  */
  vec<c_goto_bindings_p, va_gc> *gotos;
};

/* Each c_scope structure describes the complete contents of one
   scope.  Four scopes are distinguished specially: the innermost or
   current scope, the innermost function scope, the file scope (always
   the second to outermost) and the outermost or external scope.

   Most declarations are recorded in the current scope.

   All normal label declarations are recorded in the innermost
   function scope, as are bindings of undeclared identifiers to
   error_mark_node.  (GCC permits nested functions as an extension,
   hence the 'innermost' qualifier.)  Explicitly declared labels
   (using the __label__ extension) appear in the current scope.

   Being in the file scope (current_scope == file_scope) causes
   special behavior in several places below.  Also, under some
   conditions the Objective-C front end records declarations in the
   file scope even though that isn't the current scope.

   All declarations with external linkage are recorded in the external
   scope, even if they aren't visible there; this models the fact that
   such declarations are visible to the entire program, and (with a
   bit of cleverness, see pushdecl) allows diagnosis of some violations
   of C99 6.2.2p7 and 6.2.7p2:

     If, within the same translation unit, the same identifier appears
     with both internal and external linkage, the behavior is
     undefined.

     All declarations that refer to the same object or function shall
     have compatible type; otherwise, the behavior is undefined.

   Initially only the built-in declarations, which describe compiler
   intrinsic functions plus a subset of the standard library, are in
   this scope.

   The order of the blocks list matters, and it is frequently appended
   to.  To avoid having to walk all the way to the end of the list on
   each insertion, or reverse the list later, we maintain a pointer to
   the last list entry.  (FIXME: It should be feasible to use a reversed
   list here.)

   The bindings list is strictly in reverse order of declarations;
   pop_scope relies on this.  */


ರಚನೆ GTY((chain_ಮುಂದಿನ ("%h.outer"))) c_scope {
  /* The scope containing this one.  */
  ರಚನೆ c_scope *outer;

  /* The next outermost function scope.  */
  ರಚನೆ c_scope *outer_function;

  /* All bindings in this scope.  */
  ರಚನೆ c_binding *bindings;

  /* For each scope (except the global one), a chain of BLOCK nodes
     for all the scopes that were entered and exited one level down.  */
  ವೃಕ್ಷ ಖಂಡಗಳು;
  ವೃಕ್ಷ ಖಂಡಗಳು_ಕೊನೆಯ;

  /* The depth of this scope.  Used to keep the ->shadowed chain of
     bindings sorted innermost to outermost.  */
  ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ ಆಳ : 28;

  /* True if we are currently filling this scope with parameter
     declarations.  */
  ತಾರ್ಕಿಕ parm_flag : 1;

  /* True if we saw [*] in this scope.  Used to give an error messages
     if these appears in a function definition.  */
  ತಾರ್ಕಿಕ had_vla_unspec : 1;

  /* True if we parsed a list of forward parameter decls in this scope.  */
  ತಾರ್ಕಿಕ had_forward_parm_decls : 1;

  /* True if this is the outermost block scope of a function body.
     This scope contains the parameters, the local variables declared
     in the outermost block, and all the labels (except those in
     nested functions, or declared at block scope with __label__).  */
  ತಾರ್ಕಿಕ function_body : 1;

  /* True means make a BLOCK for this scope no matter what.  */
  ತಾರ್ಕಿಕ keep : 1;

  /* True means that an unsuffixed float constant is _Decimal64.  */
  ತಾರ್ಕಿಕ float_const_decimal64 : 1;

  /* True if this scope has any label bindings.  This is used to speed
     up searching for labels when popping scopes, particularly since
     labels are normally only found at function scope.  */
  ತಾರ್ಕಿಕ has_label_bindings : 1;

  /* True if we should issue a warning if a goto statement crosses any
     of the bindings.  We still need to check the list of bindings to
     find the specific ones we need to warn about.  This is true if
     decl_jump_unsafe would return true for any of the bindings.  This
     is used to avoid looping over all the bindings unnecessarily.  */
  ತಾರ್ಕಿಕ has_jump_unsafe_decl : 1;
};

/* The scope currently in effect.  */

ಸ್ಥಿರ GTY(()) ರಚನೆ c_scope *current_scope;

/* The innermost function scope.  Ordinary (not explicitly declared)
   labels, bindings to error_mark_node, and the lazily-created
   bindings of __func__ and its friends get this scope.  */

ಸ್ಥಿರ GTY(()) ರಚನೆ c_scope *current_function_scope;

/* The C file scope.  This is reset for each input translation unit.  */

ಸ್ಥಿರ GTY(()) ರಚನೆ c_scope *file_scope;

/* The outermost scope.  This is used for all declarations with
   external linkage, and only these, hence the name.  */

ಸ್ಥಿರ GTY(()) ರಚನೆ c_scope *external_scope;

/* A chain of c_scope structures awaiting reuse.  */

ಸ್ಥಿರ GTY((deletable)) ರಚನೆ c_scope *scope_freelist;

/* A chain of c_binding structures awaiting reuse.  */

ಸ್ಥಿರ GTY((deletable)) ರಚನೆ c_binding *binding_freelist;

/* Append VAR to LIST in scope SCOPE.  */
#ವ್ಯಾಖ್ಯಾನಿಸು SCOPE_LIST_APPEND(scope, list, decl) ಮಾಡು {	\
  ರಚನೆ c_scope *s_ = (scope);				\
  ವೃಕ್ಷ d_ = (decl);					\
  ಆದರೆ (s_->list##_last)					\
    ಖಂಡ_CHAIN (s_->list##_last) = d_;			\
  ಇಲ್ಲದಿದ್ದರೆ							\
    s_->list = d_;					\
  s_->list##_last = d_;					\
} ಆಗ (0)

/* Concatenate FROM in scope FSCOPE onto TO in scope TSCOPE.  */
#ವ್ಯಾಖ್ಯಾನಿಸು SCOPE_LIST_CONCAT(tscope, ಗಮ್ಯ, fscope, from) ಮಾಡು {	\
  ರಚನೆ c_scope *t_ = (tscope);				\
  ರಚನೆ c_scope *f_ = (fscope);				\
  ಆದರೆ (t_->ಗಮ್ಯ##_last)						\
    ಖಂಡ_CHAIN (t_->ಗಮ್ಯ##_last) = f_->from;			\
  ಇಲ್ಲದಿದ್ದರೆ								\
    t_->ಗಮ್ಯ = f_->from;						\
  t_->ಗಮ್ಯ##_last = f_->from##_last;				\
} ಆಗ (0)

/* A c_inline_static structure stores details of a static identifier
   referenced in a definition of a function that may be an inline
   definition if no subsequent declaration of that function uses
   "extern" or does not use "inline".  */

ರಚನೆ GTY((chain_ಮುಂದಿನ ("%h.next"))) c_inline_static {
  /* The location for a diagnostic.  */
  location_t location;

  /* The function that may be an inline definition.  */
  ವೃಕ್ಷ function;

  /* The object or function referenced.  */
  ವೃಕ್ಷ static_decl;

  /* What sort of reference this is.  */
  ಎಣಿಕೆ c_inline_static_type type;

  /* The next such structure or NULL.  */
  ರಚನೆ c_inline_static *ಮುಂದಿನ;
};

/* List of static identifiers used or referenced in functions that may
   be inline definitions.  */
ಸ್ಥಿರ GTY(()) ರಚನೆ c_inline_static *c_inline_statics;

/* True means unconditionally make a BLOCK for the next scope pushed.  */

ಸ್ಥಿರ ತಾರ್ಕಿಕ keep_ಮುಂದಿನ_level_flag;

/* True means the next call to push_scope will be the outermost scope
   of a function body, so do not push a new scope, merely cease
   expecting parameter decls.  */

ಸ್ಥಿರ ತಾರ್ಕಿಕ ಮುಂದಿನ_is_function_body;

/* A vector of pointers to c_binding structures.  */

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ c_binding *c_binding_ptr;

/* Information that we keep for a struct or union while it is being
   parsed.  */

ವರ್ಗ c_struct_parse_info
{
ಸಾರ್ವಜನಿಕ:
  /* If warn_cxx_compat, a list of types defined within this
     struct.  */
  auto_vec<ವೃಕ್ಷ> struct_types;
  /* If warn_cxx_compat, a list of field names which have bindings,
     and which are defined in this struct, but which are not defined
     in any enclosing struct.  This is used to clear the in_struct
     field of the c_bindings structure.  */
  auto_vec<c_binding_ptr> fields;
  /* If warn_cxx_compat, a list of typedef names used when defining
     fields in this struct.  */
  auto_vec<ವೃಕ್ಷ> typedefs_ನೋಡಿದ;
  /* The location of a previous definition of this struct.  */
  location_t refloc;
};


/* Hash table for structs and unions.  */
ರಚನೆ c_struct_hasher : ggc_ptr_hash<ವೃಕ್ಷ_ಗಂಟು>
{
  ಸ್ಥಿರ hashval_t hash (ವೃಕ್ಷ t);
  ಸ್ಥಿರ ತಾರ್ಕಿಕ equal (ವೃಕ್ಷ, ವೃಕ್ಷ);
};

/* Hash an RECORD OR UNION.  */
hashval_t
c_struct_hasher::hash (ವೃಕ್ಷ type)
{
  inchash::hash hstate;

  hstate.ಕೂಡಿಸು_int (ವೃಕ್ಷ_ಸಂಕೇತ (type));
  ವೃಕ್ಷ ಟ್ಯಾಗ್ = c_type_ಟ್ಯಾಗ್ (type);
  hstate.ಕೂಡಿಸು_object (ಟ್ಯಾಗ್);

  ಹಿಂತಿರುಗಿ hstate.ಕೊನೆ ();
}

/* Compare two RECORD or UNION types.  */
ತಾರ್ಕಿಕ
c_struct_hasher::equal (ವೃಕ್ಷ t1,  ವೃಕ್ಷ t2)
{
  ಹಿಂತಿರುಗಿ comptypes_equiv_p (t1, t2);
}

/* All tagged typed so that TYPE_CANONICAL can be set correctly.  */
ಸ್ಥಿರ GTY (()) hash_ಕೋಷ್ಟಕ<c_struct_hasher> *c_struct_htab;

/* Information for the struct or union currently being parsed, or
   NULL if not parsing a struct or union.  */
ಸ್ಥಿರ ವರ್ಗ c_struct_parse_info *struct_parse_info;

/* Forward declarations.  */
ಸ್ಥಿರ ವೃಕ್ಷ lookup_name_ಒಳ_scope (ವೃಕ್ಷ, ರಚನೆ c_scope *);
ಸ್ಥಿರ ವೃಕ್ಷ c_make_fname_decl (location_t, ವೃಕ್ಷ, ಪೂರ್ಣಾಂಕ);
ಸ್ಥಿರ ವೃಕ್ಷ grokdeclarator (ಸ್ಥಿರಾಂಕ ರಚನೆ c_declarator *,
			    ರಚನೆ c_declspecs *,
			    ಎಣಿಕೆ decl_context, ತಾರ್ಕಿಕ, ವೃಕ್ಷ *, ವೃಕ್ಷ *, ವೃಕ್ಷ *,
			    ತಾರ್ಕಿಕ *, ಎಣಿಕೆ deprecated_ಸ್ಥಿತಿಗಳು);
ಸ್ಥಿರ ವೃಕ್ಷ grokparms (ರಚನೆ c_arg_info *, ತಾರ್ಕಿಕ);
ಸ್ಥಿರ ಶೂನ್ಯ layout_array_type (ವೃಕ್ಷ);
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಶೀರ್ಷಿಕೆ_for_builtin_fn (ವೃಕ್ಷ);

/* T is a statement.  Add it to the statement-tree.  This is the
   C/ObjC version--C++ has a slightly different version of this
   function.  */

ವೃಕ್ಷ
ಕೂಡಿಸು_stmt (ವೃಕ್ಷ t)
{
  ಎಣಿಕೆ ವೃಕ್ಷ_ಸಂಕೇತ_2 ಸಂಕೇತ_2 = ವೃಕ್ಷ_ಸಂಕೇತ (t);

  ಆದರೆ (CAN_HAVE_LOCATION_P (t) && ಸಂಕೇತ_2 != LABEL_ಅಭಿವ್ಯಕ್ತಿ)
    {
      ಆದರೆ (!ಅಭಿವ್ಯಕ್ತಿ_HAS_LOCATION (t))
	ಗಣ_ಅಭಿವ್ಯಕ್ತಿ_LOCATION (t, ಒಳಹರಿವು_location);
    }

  /* Add T to the statement-tree.  Non-side-effect statements need to be
     recorded during statement expressions.  */
  ಆದರೆ (!building_stmt_list_p ())
    ತಳ್ಳು_stmt_list ();

  ಆದರೆ (ಸಂಕೇತ_2 == LABEL_ಅಭಿವ್ಯಕ್ತಿ || ಸಂಕೇತ_2 == CASE_LABEL_ಅಭಿವ್ಯಕ್ತಿ)
    STATEMENT_LIST_HAS_LABEL (cur_stmt_list) = 1;

  append_ಗಮ್ಯ_statement_list_force (t, &cur_stmt_list);

  ಹಿಂತಿರುಗಿ t;
}





/* Return true if we will want to say something if a goto statement
   crosses DECL.  */

ಸ್ಥಿರ ತಾರ್ಕಿಕ
decl_jump_unsafe (ವೃಕ್ಷ decl)
{
  ಆದರೆ (error_ಕಾರ್ಯಾಂಶ_p (decl))
    ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;

  /* Don't warn for compound literals.  If a goto statement crosses
     their initialization, it should cross also all the places where
     the complit is used or where the complit address might be saved
     into some variable, so code after the label to which goto jumps
     should not be able to refer to the compound literal.  */
  ಆದರೆ (VAR_P (decl) && C_DECL_COMPOUND_LITERAL_P (decl))
    ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;

  ಆದರೆ (flag_openmp
      && VAR_P (decl)
      && lookup_attribute ("omp allocate", DECL_ಗುಣಲಕ್ಷಣಗಳು (decl)))
    ಹಿಂತಿರುಗಿ ನಿಜ;

  /* Always warn about crossing variably modified types.  */
  ಆದರೆ ((VAR_P (decl) || ವೃಕ್ಷ_ಸಂಕೇತ (decl) == TYPE_DECL)
      && c_type_variably_modified_p (ವೃಕ್ಷ_TYPE (decl)))
    ಹಿಂತಿರುಗಿ ನಿಜ;

  /* Otherwise, only warn if -Wgoto-misses-init and this is an
     initialized automatic decl.  */
  ಆದರೆ (warn_jump_ತಪ್ಪಿದವು_init
      && VAR_P (decl)
      && !ವೃಕ್ಷ_STATIC (decl)
      && DECL_INITIAL (decl) != NULL_ವೃಕ್ಷ)
    ಹಿಂತಿರುಗಿ ನಿಜ;

  ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
}


ಶೂನ್ಯ
c_print_identifier (FILE *file, ವೃಕ್ಷ ಗಂಟು, ಪೂರ್ಣಾಂಕ indent)
{
  ಶೂನ್ಯ (*save) (ಎಣಿಕೆ c_oracle_request, ವೃಕ್ಷ identifier);

  /* Temporarily hide any binding oracle.  Without this, calls to
     debug_tree from the debugger will end up calling into the oracle,
     making for a confusing debug session.  As the oracle isn't needed
     here for normal operation, it's simplest to suppress it.  */
  save = c_binding_oracle;
  c_binding_oracle = ಖಾಲಿ;

  print_ಗಂಟು (file, "symbol", I_ಚಿಹ್ನೆ_DECL (ಗಂಟು), indent + 4);
  print_ಗಂಟು (file, "tag", I_ಟ್ಯಾಗ್_DECL (ಗಂಟು), indent + 4);
  print_ಗಂಟು (file, "label", I_LABEL_DECL (ಗಂಟು), indent + 4);
  ಆದರೆ (C_IS_RESERVED_ಶಬ್ದ (ಗಂಟು) && C_RID_ಸಂಕೇತ (ಗಂಟು) != RID_CXX_COMPAT_WARN)
    {
      ವೃಕ್ಷ rid = ridpointers[C_RID_ಸಂಕೇತ (ಗಂಟು)];
      indent_ಗಮ್ಯ (file, indent + 4);
      fprintf (file, "rid " HOST_PTR_PRINTF " \"%s\"",
	       (ಶೂನ್ಯ *) rid, IDENTIFIER_ಸೂಚಕ (rid));
    }

  c_binding_oracle = save;
}

/* Establish that the scope contains declarations that are sensitive to
   jumps that cross a binding.  Together with decl_jump_unsafe, this is
   used to diagnose such jumps.  */
ಶೂನ್ಯ
c_mark_decl_jump_unsafe_ಒಳ_current_scope ()
{
  current_scope->has_jump_unsafe_decl = 1;
}

/* Establish a binding between NAME, an IDENTIFIER_NODE, and DECL,
   which may be any of several kinds of DECL or TYPE or error_mark_node,
   in the scope SCOPE.  */
ಸ್ಥಿರ ಶೂನ್ಯ
bind (ವೃಕ್ಷ name, ವೃಕ್ಷ decl, ರಚನೆ c_scope *scope, ತಾರ್ಕಿಕ invisible,
      ತಾರ್ಕಿಕ nested, location_t locus)
{
  ರಚನೆ c_binding *b, **ಇಲ್ಲಿ;

  ಆದರೆ (binding_freelist)
    {
      b = binding_freelist;
      binding_freelist = b->prev;
    }
  ಇಲ್ಲದಿದ್ದರೆ
    b = ggc_alloc<c_binding> ();

  b->shadowed = 0;
  b->decl = decl;
  b->id = name;
  b->ಆಳ = scope->ಆಳ;
  b->invisible = invisible;
  b->nested = nested;
  b->inner_comp = 0;
  b->ಒಳ_struct = 0;
  b->locus = locus;

  b->u.type = ಖಾಲಿ;

  b->prev = scope->bindings;
  scope->bindings = b;

  ಆದರೆ (decl_jump_unsafe (decl))
    scope->has_jump_unsafe_decl = 1;

  ಆದರೆ (!name)
    ಹಿಂತಿರುಗಿ;

  ಆಯ್ಕೆ (ವೃಕ್ಷ_ಸಂಕೇತ (decl))
    {
    ಸ್ಥಿತಿ LABEL_DECL:     ಇಲ್ಲಿ = &I_LABEL_BINDING (name);   ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ ENUMERAL_TYPE:
    ಸ್ಥಿತಿ UNION_TYPE:
    ಸ್ಥಿತಿ ದಾಖಲೆ_TYPE:    ಇಲ್ಲಿ = &I_ಟ್ಯಾಗ್_BINDING (name);     ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ VAR_DECL:
    ಸ್ಥಿತಿ FUNCTION_DECL:
    ಸ್ಥಿತಿ TYPE_DECL:
    ಸ್ಥಿತಿ CONST_DECL:
    ಸ್ಥಿತಿ PARM_DECL:
    ಸ್ಥಿತಿ ERROR_MARK:     ಇಲ್ಲಿ = &I_ಚಿಹ್ನೆ_BINDING (name);  ನಿಲ್ಲಿಸು;

    ಪೂರ್ವನಿಯೋಜಿತ:
      gcc_unreachable ();
    }

  /* Locate the appropriate place in the chain of shadowed decls
     to insert this binding.  Normally, scope == current_scope and
     this does nothing.  */
  ಆಗ (*ಇಲ್ಲಿ && (*ಇಲ್ಲಿ)->ಆಳ > scope->ಆಳ)
    ಇಲ್ಲಿ = &(*ಇಲ್ಲಿ)->shadowed;

  b->shadowed = *ಇಲ್ಲಿ;
  *ಇಲ್ಲಿ = b;
}

/* Clear the binding structure B, stick it on the binding_freelist,
   and return the former value of b->prev.  This is used by pop_scope
   and get_parm_info to iterate destructively over all the bindings
   from a given scope.  */
ಸ್ಥಿರ ರಚನೆ c_binding *
free_binding_and_advance (ರಚನೆ c_binding *b)
{
  ರಚನೆ c_binding *prev = b->prev;

  memset (b, 0, ಗಾತ್ರ (ರಚನೆ c_binding));
  b->prev = binding_freelist;
  binding_freelist = b;

  ಹಿಂತಿರುಗಿ prev;
}

/* Bind a label.  Like bind, but skip fields which aren't used for
   labels, and add the LABEL_VARS value.  */
ಸ್ಥಿರ ಶೂನ್ಯ
bind_label (ವೃಕ್ಷ name, ವೃಕ್ಷ label, ರಚನೆ c_scope *scope,
	    ರಚನೆ c_label_vars *label_vars)
{
  ರಚನೆ c_binding *b;

  bind (name, label, scope, /*invisible=*/ಸುಳ್ಳು, /*nested=*/ಸುಳ್ಳು,
	UNKNOWN_LOCATION);

  scope->has_label_bindings = ನಿಜ;

  b = scope->bindings;
  gcc_assert (b->decl == label);
  label_vars->shadowed = b->u.label;
  b->u.label = label_vars;
}

/* Hook called at end of compilation to assume 1 elt
   for a file-scope tentative array defn that wasn't complete before.  */

ಶೂನ್ಯ
c_ಮುಕ್ತಾಯ_incomplete_decl (ವೃಕ್ಷ decl)
{
  ಆದರೆ (VAR_P (decl))
    {
      ವೃಕ್ಷ type = ವೃಕ್ಷ_TYPE (decl);
      ಆದರೆ (type != error_mark_ಗಂಟು
	  && ವೃಕ್ಷ_ಸಂಕೇತ (type) == ARRAY_TYPE
	  && !DECL_EXTERNAL (decl)
	  && TYPE_DOMAIN (type) == NULL_ವೃಕ್ಷ)
	{
	  ಆದರೆ (flag_isoc2y && !ವೃಕ್ಷ_ಬಹಿರಂಗ (decl))
	    error_at (DECL_ಮೂಲ_LOCATION (decl),
		      "array size missing in %q+D", decl);
	  ಇಲ್ಲದಿದ್ದರೆ
	    warning_at (DECL_ಮೂಲ_LOCATION (decl),
			0, "array %q+D assumed to have one element", decl);

	  complete_array_type (&ವೃಕ್ಷ_TYPE (decl), NULL_ವೃಕ್ಷ, ನಿಜ);

	  relayout_decl (decl);
	}
    }
}

/* Record that inline function FUNC contains a reference (location
   LOC) to static DECL (file-scope or function-local according to
   TYPE).  */

ಶೂನ್ಯ
ದಾಖಲೆ_inline_static (location_t loc, ವೃಕ್ಷ func, ವೃಕ್ಷ decl,
		      ಎಣಿಕೆ c_inline_static_type type)
{
  c_inline_static *csi = ggc_alloc<c_inline_static> ();
  csi->location = loc;
  csi->function = func;
  csi->static_decl = decl;
  csi->type = type;
  csi->ಮುಂದಿನ = c_inline_statics;
  c_inline_statics = csi;
}

/* Check for references to static declarations in inline functions at
   the end of the translation unit and diagnose them if the functions
   are still inline definitions.  */

ಸ್ಥಿರ ಶೂನ್ಯ
check_inline_statics (ಶೂನ್ಯ)
{
  ರಚನೆ c_inline_static *csi;
  ಗಾಗಿ (csi = c_inline_statics; csi; csi = csi->ಮುಂದಿನ)
    {
      ಆದರೆ (DECL_EXTERNAL (csi->function))
	ಆಯ್ಕೆ (csi->type)
	  {
	  ಸ್ಥಿತಿ csi_ಆಂತರಿಕ:
	    pedwarn (csi->location, 0,
		     "%qD is static but used in inline function %qD "
		     "which is not static", csi->static_decl, csi->function);
	    ನಿಲ್ಲಿಸು;
	  ಸ್ಥಿತಿ csi_modifiable:
	    pedwarn (csi->location, 0,
		     "%q+D is static but declared in inline function %qD "
		     "which is not static", csi->static_decl, csi->function);
	    ನಿಲ್ಲಿಸು;
	  ಪೂರ್ವನಿಯೋಜಿತ:
	    gcc_unreachable ();
	  }
    }
  c_inline_statics = ಖಾಲಿ;
}

/* Fill in a c_spot_bindings structure.  If DEFINING is true, set it
   for the current state, otherwise set it to uninitialized.  */

ಸ್ಥಿರ ಶೂನ್ಯ
ಗಣ_spot_bindings (ರಚನೆ c_spot_bindings *p, ತಾರ್ಕಿಕ defining)
{
  ಆದರೆ (defining)
    {
      p->scope = current_scope;
      p->bindings_ಒಳ_scope = current_scope->bindings;
    }
  ಇಲ್ಲದಿದ್ದರೆ
    {
      p->scope = ಖಾಲಿ;
      p->bindings_ಒಳ_scope = ಖಾಲಿ;
    }
  p->stmt_exprs = 0;
  p->ಎಡ_stmt_ಅಭಿವ್ಯಕ್ತಿ = ಸುಳ್ಳು;
}

/* Update spot bindings P as we pop out of SCOPE.  Return true if we
   should push decls for a label.  */

ಸ್ಥಿರ ತಾರ್ಕಿಕ
update_spot_bindings (ರಚನೆ c_scope *scope, ರಚನೆ c_spot_bindings *p)
{
  ಆದರೆ (p->scope != scope)
    {
      /* This label or goto is defined in some other scope, or it is a
	 label which is not yet defined.  There is nothing to
	 update.  */
      ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
    }

  /* Adjust the spot bindings to refer to the bindings already defined
     in the enclosing scope.  */
  p->scope = scope->outer;
  p->bindings_ಒಳ_scope = p->scope->bindings;

  ಹಿಂತಿರುಗಿ ನಿಜ;
}

/* The Objective-C front-end often needs to determine the current scope.  */

ಶೂನ್ಯ *
objc_get_current_scope (ಶೂನ್ಯ)
{
  ಹಿಂತಿರುಗಿ current_scope;
}

/* The following function is used only by Objective-C.  It needs to live here
   because it accesses the innards of c_scope.  */

ಶೂನ್ಯ
objc_mark_locals_volatile (ಶೂನ್ಯ *enclosing_blk)
{
  ರಚನೆ c_scope *scope;
  ರಚನೆ c_binding *b;

  ಗಾಗಿ (scope = current_scope;
       scope && scope != enclosing_blk;
       scope = scope->outer)
    {
      ಗಾಗಿ (b = scope->bindings; b; b = b->prev)
	objc_volatilize_decl (b->decl);

      /* Do not climb up past the current function.  */
      ಆದರೆ (scope->function_body)
	ನಿಲ್ಲಿಸು;
    }
}

/* Return true if we are in the global binding level.  */

ತಾರ್ಕಿಕ
global_bindings_p (ಶೂನ್ಯ)
{
  ಹಿಂತಿರುಗಿ current_scope == file_scope;
}

/* Return true if we're declaring parameters in an old-style function
   declaration.  */

ತಾರ್ಕಿಕ
old_style_parameter_scope (ಶೂನ್ಯ)
{
  /* If processing parameters and there is no function statement list, we
   * have an old-style function declaration.  */
  ಹಿಂತಿರುಗಿ (current_scope->parm_flag && !DECL_SAVED_ವೃಕ್ಷ (current_function_decl));
}

ಶೂನ್ಯ
keep_ಮುಂದಿನ_level (ಶೂನ್ಯ)
{
  keep_ಮುಂದಿನ_level_flag = ನಿಜ;
}

/* Set the flag for the FLOAT_CONST_DECIMAL64 pragma being ON.  */

ಶೂನ್ಯ
ಗಣ_float_const_decimal64 (ಶೂನ್ಯ)
{
  current_scope->float_const_decimal64 = ನಿಜ;
}

/* Clear the flag for the FLOAT_CONST_DECIMAL64 pragma.  */

ಶೂನ್ಯ
clear_float_const_decimal64 (ಶೂನ್ಯ)
{
  current_scope->float_const_decimal64 = ಸುಳ್ಳು;
}

/* Return nonzero if an unsuffixed float constant is _Decimal64.  */

ತಾರ್ಕಿಕ
float_const_decimal64_p (ಶೂನ್ಯ)
{
  ಹಿಂತಿರುಗಿ current_scope->float_const_decimal64;
}

/* Identify this scope as currently being filled with parameters.  */

ಶೂನ್ಯ
declare_parm_level (ಶೂನ್ಯ)
{
  current_scope->parm_flag = ನಿಜ;
}

ಶೂನ್ಯ
ತಳ್ಳು_scope (ಶೂನ್ಯ)
{
  ಆದರೆ (ಮುಂದಿನ_is_function_body)
    {
      /* This is the transition from the parameters to the top level
	 of the function body.  These are the same scope
	 (C99 6.2.1p4,6) so we do not push another scope structure.
	 next_is_function_body is set only by store_parm_decls, which
	 in turn is called when and only when we are about to
	 encounter the opening curly brace for the function body.

	 The outermost block of a function always gets a BLOCK node,
	 because the debugging output routines expect that each
	 function has at least one BLOCK.  */
      current_scope->parm_flag         = ಸುಳ್ಳು;
      current_scope->function_body     = ನಿಜ;
      current_scope->keep              = ನಿಜ;
      current_scope->outer_function    = current_function_scope;
      current_function_scope           = current_scope;

      keep_ಮುಂದಿನ_level_flag = ಸುಳ್ಳು;
      ಮುಂದಿನ_is_function_body = ಸುಳ್ಳು;

      /* The FLOAT_CONST_DECIMAL64 pragma applies to nested scopes.  */
      ಆದರೆ (current_scope->outer)
	current_scope->float_const_decimal64
	  = current_scope->outer->float_const_decimal64;
      ಇಲ್ಲದಿದ್ದರೆ
	current_scope->float_const_decimal64 = ಸುಳ್ಳು;
    }
  ಇಲ್ಲದಿದ್ದರೆ
    {
      ರಚನೆ c_scope *scope;
      ಆದರೆ (scope_freelist)
	{
	  scope = scope_freelist;
	  scope_freelist = scope->outer;
	}
      ಇಲ್ಲದಿದ್ದರೆ
	scope = ggc_cleared_alloc<c_scope> ();

      /* The FLOAT_CONST_DECIMAL64 pragma applies to nested scopes.  */
      ಆದರೆ (current_scope)
	scope->float_const_decimal64 = current_scope->float_const_decimal64;
      ಇಲ್ಲದಿದ್ದರೆ
	scope->float_const_decimal64 = ಸುಳ್ಳು;

      scope->keep          = keep_ಮುಂದಿನ_level_flag;
      scope->outer         = current_scope;
      scope->ಆಳ	   = current_scope ? (current_scope->ಆಳ + 1) : 0;

      /* Check for scope depth overflow.  Unlikely (2^28 == 268,435,456) but
	 possible.  */
      ಆದರೆ (current_scope && scope->ಆಳ == 0)
	{
	  scope->ಆಳ--;
	  sorry ("GCC supports only %u nested scopes", scope->ಆಳ);
	}

      current_scope        = scope;
      keep_ಮುಂದಿನ_level_flag = ಸುಳ್ಳು;
    }
}

/* This is called when we are leaving SCOPE.  For each label defined
   in SCOPE, add any appropriate decls to its decls_in_scope fields.
   These are the decls whose initialization will be skipped by a goto
   later in the function.  */

ಸ್ಥಿರ ಶೂನ್ಯ
update_label_decls (ರಚನೆ c_scope *scope)
{
  ರಚನೆ c_scope *s;

  s = scope;
  ಆಗ (s != ಖಾಲಿ)
    {
      ಆದರೆ (s->has_label_bindings)
	{
	  ರಚನೆ c_binding *b;

	  ಗಾಗಿ (b = s->bindings; b != ಖಾಲಿ; b = b->prev)
	    {
	      ರಚನೆ c_label_vars *label_vars;
	      ರಚನೆ c_binding *b1;
	      ತಾರ್ಕಿಕ hjud;
	      ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ ix;
	      ರಚನೆ c_goto_bindings *g;

	      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (b->decl) != LABEL_DECL)
		ಮುಂದುವರಿ;
	      label_vars = b->u.label;

	      b1 = label_vars->label_bindings.bindings_ಒಳ_scope;
	      ಆದರೆ (label_vars->label_bindings.scope == ಖಾಲಿ)
		hjud = ಸುಳ್ಳು;
	      ಇಲ್ಲದಿದ್ದರೆ
		hjud = label_vars->label_bindings.scope->has_jump_unsafe_decl;
	      ಆದರೆ (update_spot_bindings (scope, &label_vars->label_bindings))
		{
		  /* This label is defined in this scope.  */
		  ಆದರೆ (hjud)
		    {
		      ಗಾಗಿ (; b1 != ಖಾಲಿ; b1 = b1->prev)
			{
			  /* A goto from later in the function to this
			     label will never see the initialization
			     of B1, if any.  Save it to issue a
			     warning if needed.  */
			  ಆದರೆ (decl_jump_unsafe (b1->decl))
			    vec_ಸುರಕ್ಷಿತ_ತಳ್ಳು(label_vars->decls_ಒಳ_scope, b1->decl);
			}
		    }
		}

	      /* Update the bindings of any goto statements associated
		 with this label.  */
	      FOR_EACH_VEC_ಸುರಕ್ಷಿತ_ELT (label_vars->gotos, ix, g)
		update_spot_bindings (scope, &g->goto_bindings);
	    }
	}

      /* Don't search beyond the current function.  */
      ಆದರೆ (s == current_function_scope)
	ನಿಲ್ಲಿಸು;

      s = s->outer;
    }
}

/* Exit a scope.  Restore the state of the identifier-decl mappings
   that were in effect when this scope was entered.  Return a BLOCK
   node containing all the DECLs in this scope that are of interest
   to debug info generation.  */

ವೃಕ್ಷ
ತೆಗೆ_scope (ಶೂನ್ಯ)
{
  ರಚನೆ c_scope *scope = current_scope;
  ವೃಕ್ಷ ಖಂಡ, context, p;
  ರಚನೆ c_binding *b;

  ತಾರ್ಕಿಕ functionbody = scope->function_body;
  ತಾರ್ಕಿಕ keep = functionbody || scope->keep || scope->bindings;

  update_label_decls (scope);

  /* If appropriate, create a BLOCK to record the decls for the life
     of this function.  */
  ಖಂಡ = NULL_ವೃಕ್ಷ;
  ಆದರೆ (keep)
    {
      ಖಂಡ = make_ಗಂಟು (ಖಂಡ_2);
      ಖಂಡ_SUBBLOCKS (ಖಂಡ) = scope->ಖಂಡಗಳು;
      ವೃಕ್ಷ_ಬಳಸಿದ (ಖಂಡ) = 1;

      /* In each subblock, record that this is its superior.  */
      ಗಾಗಿ (p = scope->ಖಂಡಗಳು; p; p = ಖಂಡ_CHAIN (p))
	ಖಂಡ_SUPERCONTEXT (p) = ಖಂಡ;

      ಖಂಡ_VARS (ಖಂಡ) = NULL_ವೃಕ್ಷ;
    }

  /* The TYPE_CONTEXTs for all of the tagged types belonging to this
     scope must be set so that they point to the appropriate
     construct, i.e.  either to the current FUNCTION_DECL node, or
     else to the BLOCK node we just constructed.

     Note that for tagged types whose scope is just the formal
     parameter list for some function type specification, we can't
     properly set their TYPE_CONTEXTs here, because we don't have a
     pointer to the appropriate FUNCTION_TYPE node readily available
     to us.  For those cases, the TYPE_CONTEXTs of the relevant tagged
     type nodes get set in `grokdeclarator' as soon as we have created
     the FUNCTION_TYPE node which will represent the "scope" for these
     "parameter list local" tagged types.  */
  ಆದರೆ (scope->function_body)
    context = current_function_decl;
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (scope == file_scope)
    {
      ವೃಕ್ಷ file_decl
	= build_translation_unit_decl (get_identifier (main_ಒಳಹರಿವು_filename));
      context = file_decl;
      debug_hooks->ರಿಜಿಸ್ಟರ್_main_translation_unit (file_decl);
    }
  ಇಲ್ಲದಿದ್ದರೆ
    context = ಖಂಡ;

  /* Clear all bindings in this scope.  */
  ಗಾಗಿ (b = scope->bindings; b; b = free_binding_and_advance (b))
    {
      p = b->decl;
      ಆಯ್ಕೆ (ವೃಕ್ಷ_ಸಂಕೇತ (p))
	{
	ಸ್ಥಿತಿ LABEL_DECL:
	  /* Warnings for unused labels, errors for undefined labels.  */
	  ಆದರೆ (ವೃಕ್ಷ_ಬಳಸಿದ (p) && !DECL_INITIAL (p))
	    {
	      error ("label %q+D used but not defined", p);
	      DECL_INITIAL (p) = error_mark_ಗಂಟು;
	    }
	  ಇಲ್ಲದಿದ್ದರೆ
	    warn_for_ಬಳಸದ_label (p);

	  /* Labels go in BLOCK_VARS.  */
	  DECL_CHAIN (p) = ಖಂಡ_VARS (ಖಂಡ);
	  ಖಂಡ_VARS (ಖಂಡ) = p;
	  gcc_assert (I_LABEL_BINDING (b->id) == b);
	  I_LABEL_BINDING (b->id) = b->shadowed;

	  /* Also pop back to the shadowed label_vars.  */
	  release_ವೃಕ್ಷ_ಸದಿಶ (b->u.label->decls_ಒಳ_scope);
	  b->u.label = b->u.label->shadowed;
	  ನಿಲ್ಲಿಸು;

	ಸ್ಥಿತಿ ENUMERAL_TYPE:
	ಸ್ಥಿತಿ UNION_TYPE:
	ಸ್ಥಿತಿ ದಾಖಲೆ_TYPE:

	  /* Types may not have tag-names, in which case the type
	     appears in the bindings list with b->id NULL.  */
	  ಆದರೆ (b->id)
	    {
	      gcc_assert (I_ಟ್ಯಾಗ್_BINDING (b->id) == b);
	      I_ಟ್ಯಾಗ್_BINDING (b->id) = b->shadowed;
	    }
	  ನಿಲ್ಲಿಸು;

	ಸ್ಥಿತಿ FUNCTION_DECL:
	  /* Propagate TREE_ADDRESSABLE from nested functions to their
	     containing functions.  */
	  ಆದರೆ (!ವೃಕ್ಷ_ASM_WRITTEN (p)
	      && DECL_INITIAL (p) != NULL_ವೃಕ್ಷ
	      && ವೃಕ್ಷ_ADDRESSABLE (p)
	      && DECL_ABSTRACT_ORIGIN (p) != NULL_ವೃಕ್ಷ
	      && DECL_ABSTRACT_ORIGIN (p) != p)
	    ವೃಕ್ಷ_ADDRESSABLE (DECL_ABSTRACT_ORIGIN (p)) = 1;
	  ಆದರೆ (!ವೃಕ್ಷ_ಬಹಿರಂಗ (p)
	      && !DECL_INITIAL (p)
	      && !b->nested
	      && scope != file_scope
	      && scope != external_scope)
	    {
	      error ("nested function %q+D declared but never defined", p);
	      undef_nested_function = ನಿಜ;
	    }
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (DECL_DECLARED_INLINE_P (p)
		   && ವೃಕ್ಷ_ಬಹಿರಂಗ (p)
		   && !DECL_INITIAL (p))
	    {
	      /* C99 6.7.4p6: "a function with external linkage... declared
		 with an inline function specifier ... shall also be defined
		 in the same translation unit."  */
	      ಆದರೆ (!flag_gnu89_inline
		  && !lookup_attribute ("gnu_inline", DECL_ಗುಣಲಕ್ಷಣಗಳು (p))
		  && scope == external_scope)
		pedwarn (ಒಳಹರಿವು_location, 0,
			 "inline function %q+D declared but never defined", p);
	      DECL_EXTERNAL (p) = 1;
	    }

	  ಹೋಗು common_ಚಿಹ್ನೆ;

	ಸ್ಥಿತಿ VAR_DECL:
	  /* Warnings for unused variables.  */
	  ಆದರೆ ((!ವೃಕ್ಷ_ಬಳಸಿದ (p) || !DECL_READ_P (p))
	      && !warning_suppressed_p (p, OPT_Wunused_but_ಗಣ_variable)
	      && !DECL_ಒಳ_SYSTEM_ಶೀರ್ಷಿಕೆ (p)
	      && DECL_NAME (p)
	      && !DECL_ARTIFICIAL (p)
	      && scope != file_scope
	      && scope != external_scope)
	    {
	      ಆದರೆ (!ವೃಕ್ಷ_ಬಳಸಿದ (p))
		{
		  warning (OPT_Wunused_variable, "unused variable %q+D", p);
		  suppress_warning (p, OPT_Wunused_variable);
		}
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (DECL_CONTEXT (p) == current_function_decl)
		warning_at (DECL_ಮೂಲ_LOCATION (p),
			    OPT_Wunused_but_ಗಣ_variable,
			    "variable %qD set but not used", p);
	    }

	  ಆದರೆ (b->inner_comp)
	    {
	      error ("type of array %q+D completed incompatibly with"
		     " implicit initialization", p);
	    }

	  /* Fall through.  */
	ಸ್ಥಿತಿ TYPE_DECL:
	ಸ್ಥಿತಿ CONST_DECL:
	common_ಚಿಹ್ನೆ:
	  /* All of these go in BLOCK_VARS, but only if this is the
	     binding in the home scope.  */
	  ಆದರೆ (!b->nested)
	    {
	      DECL_CHAIN (p) = ಖಂಡ_VARS (ಖಂಡ);
	      ಖಂಡ_VARS (ಖಂಡ) = p;
	    }
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (VAR_OR_FUNCTION_DECL_P (p) && scope != file_scope)
	    {
	      /* For block local externs add a special
		 DECL_EXTERNAL decl for debug info generation.  */
	      ವೃಕ್ಷ extp = copy_ಗಂಟು (p);

	      DECL_EXTERNAL (extp) = 1;
	      ವೃಕ್ಷ_STATIC (extp) = 0;
	      ವೃಕ್ಷ_ಬಹಿರಂಗ (extp) = 1;
	      DECL_INITIAL (extp) = NULL_ವೃಕ್ಷ;
	      DECL_LANG_SPECIFIC (extp) = ಖಾಲಿ;
	      DECL_CONTEXT (extp) = current_function_decl;
	      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (p) == FUNCTION_DECL)
		{
		  DECL_ಫಲಿತಾಂಶ (extp) = NULL_ವೃಕ್ಷ;
		  DECL_SAVED_ವೃಕ್ಷ (extp) = NULL_ವೃಕ್ಷ;
		  DECL_STRUCT_FUNCTION (extp) = ಖಾಲಿ;
		}
	      ಆದರೆ (b->locus != UNKNOWN_LOCATION)
		DECL_ಮೂಲ_LOCATION (extp) = b->locus;
	      DECL_CHAIN (extp) = ಖಂಡ_VARS (ಖಂಡ);
	      ಖಂಡ_VARS (ಖಂಡ) = extp;
	    }
	  /* If this is the file scope set DECL_CONTEXT of each decl to
	     the TRANSLATION_UNIT_DECL.  This makes same_translation_unit_p
	     work.  */
	  ಆದರೆ (scope == file_scope)
	      DECL_CONTEXT (p) = context;

	  gcc_fallthrough ();
	  /* Parameters go in DECL_ARGUMENTS, not BLOCK_VARS, and have
	     already been put there by store_parm_decls.  Unused-
	     parameter warnings are handled by function.cc.
	     error_mark_node obviously does not go in BLOCK_VARS and
	     does not get unused-variable warnings.  */
	ಸ್ಥಿತಿ PARM_DECL:
	ಸ್ಥಿತಿ ERROR_MARK:
	  /* It is possible for a decl not to have a name.  We get
	     here with b->id NULL in this case.  */
	  ಆದರೆ (b->id)
	    {
	      gcc_assert (I_ಚಿಹ್ನೆ_BINDING (b->id) == b);
	      I_ಚಿಹ್ನೆ_BINDING (b->id) = b->shadowed;
	      ಆದರೆ (b->shadowed && b->shadowed->u.type)
		ವೃಕ್ಷ_TYPE (b->shadowed->decl) = b->shadowed->u.type;
	    }
	  ನಿಲ್ಲಿಸು;

	ಪೂರ್ವನಿಯೋಜಿತ:
	  gcc_unreachable ();
	}
    }


  /* Dispose of the block that we just made inside some higher level.  */
  ಆದರೆ ((scope->function_body || scope == file_scope) && context)
    {
      DECL_INITIAL (context) = ಖಂಡ;
      ಖಂಡ_SUPERCONTEXT (ಖಂಡ) = context;
    }
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (scope->outer)
    {
      ಆದರೆ (ಖಂಡ)
	SCOPE_LIST_APPEND (scope->outer, ಖಂಡಗಳು, ಖಂಡ);
      /* If we did not make a block for the scope just exited, any
	 blocks made for inner scopes must be carried forward so they
	 will later become subblocks of something else.  */
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (scope->ಖಂಡಗಳು)
	SCOPE_LIST_CONCAT (scope->outer, ಖಂಡಗಳು, scope, ಖಂಡಗಳು);
    }

  /* Pop the current scope, and free the structure for reuse.  */
  current_scope = scope->outer;
  ಆದರೆ (scope->function_body)
    current_function_scope = scope->outer_function;

  memset (scope, 0, ಗಾತ್ರ (ರಚನೆ c_scope));
  scope->outer = scope_freelist;
  scope_freelist = scope;

  ಹಿಂತಿರುಗಿ ಖಂಡ;
}

ಶೂನ್ಯ
ತಳ್ಳು_file_scope (ಶೂನ್ಯ)
{
  ವೃಕ್ಷ decl;

  ಆದರೆ (file_scope)
    ಹಿಂತಿರುಗಿ;

  /* Call the target stack_protect_guard hook if the stack protection
     guard is declared as a global symbol.  */
  ಆದರೆ (targetm.ರಾಶಿ_protect_guard_ಚಿಹ್ನೆ_p ())
    {
      ವೃಕ್ಷ decl = targetm.ರಾಶಿ_protect_guard ();
      DECL_CHAIN (decl) = visible_builtins;
      visible_builtins = decl;
    }

  ತಳ್ಳು_scope ();
  file_scope = current_scope;

  ಆರಂಭ_fname_decls ();

  ಗಾಗಿ (decl = visible_builtins; decl; decl = DECL_CHAIN (decl))
    bind (DECL_NAME (decl), decl, file_scope,
	  /*invisible=*/ಸುಳ್ಳು, /*nested=*/ನಿಜ, DECL_ಮೂಲ_LOCATION (decl));
}

ಶೂನ್ಯ
ತೆಗೆ_file_scope (ಶೂನ್ಯ)
{
  /* In case there were missing closebraces, get us back to the global
     binding level.  */
  ಆಗ (current_scope != file_scope)
    ತೆಗೆ_scope ();

  /* __FUNCTION__ is defined at file scope ("").  This
     call may not be necessary as my tests indicate it
     still works without it.  */
  ಮುಕ್ತಾಯ_fname_decls ();

  check_inline_statics ();

  /* This is the point to write out a PCH if we're doing that.
     In that case we do not want to do anything else.  */
  ಆದರೆ (pch_file)
    {
      c_common_write_pch ();
      /* Ensure even the callers don't try to finalize the CU.  */
      flag_syntax_only = 1;
      ಹಿಂತಿರುಗಿ;
    }

  /* Pop off the file scope and close this translation unit.  */
  ತೆಗೆ_scope ();
  file_scope = 0;

  maybe_apply_pending_pragma_weaks ();
}

/* Whether we are currently inside the initializer for an
   underspecified object definition (C23 auto or constexpr).  */
ಸ್ಥಿರ ತಾರ್ಕಿಕ ಒಳ_underspecified_init;

/* Start an underspecified object definition for NAME at LOC.  This
   means that NAME is shadowed inside its initializer, so neither the
   definition being initialized, nor any definition from an outer
   scope, may be referenced during that initializer.  Return state to
   be passed to finish_underspecified_init.  If NAME is NULL_TREE, the
   underspecified object is a (constexpr) compound literal; there is
   no shadowing in that case, but all the other restrictions on
   underspecified object definitions still apply.  */
ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ
ಆರಂಭ_underspecified_init (location_t loc, ವೃಕ್ಷ name)
{
  ತಾರ್ಕಿಕ prev = ಒಳ_underspecified_init;
  ತಾರ್ಕಿಕ ok;
  ಆದರೆ (name == NULL_ವೃಕ್ಷ)
    ok = ನಿಜ;
  ಇಲ್ಲದಿದ್ದರೆ
    {
      ವೃಕ್ಷ decl = build_decl (loc, VAR_DECL, name, error_mark_ಗಂಟು);
      C_DECL_UNDERSPECIFIED (decl) = 1;
      ರಚನೆ c_scope *scope = current_scope;
      ರಚನೆ c_binding *b = I_ಚಿಹ್ನೆ_BINDING (name);
      ಆದರೆ (b && B_ಒಳ_SCOPE (b, scope))
	{
	  error_at (loc, "underspecified declaration of %qE, which is already "
		    "declared in this scope", name);
	  ok = ಸುಳ್ಳು;
	}
      ಇಲ್ಲದಿದ್ದರೆ
	{
	  bind (name, decl, scope, ಸುಳ್ಳು, ಸುಳ್ಳು, loc);
	  ok = ನಿಜ;
	}
    }
  ಒಳ_underspecified_init = ನಿಜ;
  ಹಿಂತಿರುಗಿ ok | (prev << 1);
}

/* Finish an underspecified object definition for NAME, before that
   name is bound to the real declaration instead of a placeholder.
   PREV_STATE is the value returned by the call to
   start_underspecified_init.  If NAME is NULL_TREE, this means a
   compound literal, as for start_underspecified_init.  */
ಶೂನ್ಯ
ಮುಕ್ತಾಯ_underspecified_init (ವೃಕ್ಷ name, ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ prev_state)
{
  ಆದರೆ (name != NULL_ವೃಕ್ಷ && (prev_state & 1))
    {
      /* A VAR_DECL was bound to the name to shadow any previous
	 declarations for the name; remove that binding now.  */
      ರಚನೆ c_scope *scope = current_scope;
      ರಚನೆ c_binding *b = I_ಚಿಹ್ನೆ_BINDING (name);
      gcc_assert (b);
      gcc_assert (B_ಒಳ_SCOPE (b, scope));
      gcc_assert (VAR_P (b->decl));
      gcc_assert (C_DECL_UNDERSPECIFIED (b->decl));
      I_ಚಿಹ್ನೆ_BINDING (name) = b->shadowed;
      /* In erroneous cases there may be other bindings added to this
	 scope during the initializer.  */
      ರಚನೆ c_binding **p = &scope->bindings;
      ಆಗ (*p != b)
	p = &((*p)->prev);
      *p = free_binding_and_advance (*p);
    }
  ಒಳ_underspecified_init = (prev_state & (1u << 1)) >> 1;
}

/* Adjust the bindings for the start of a statement expression.  */

ಶೂನ್ಯ
c_bindings_ಆರಂಭ_stmt_ಅಭಿವ್ಯಕ್ತಿ (ರಚನೆ c_spot_bindings* switch_bindings)
{
  ರಚನೆ c_scope *scope;

  ಗಾಗಿ (scope = current_scope; scope != ಖಾಲಿ; scope = scope->outer)
    {
      ರಚನೆ c_binding *b;

      ಆದರೆ (!scope->has_label_bindings)
	ಮುಂದುವರಿ;

      ಗಾಗಿ (b = scope->bindings; b != ಖಾಲಿ; b = b->prev)
	{
	  ರಚನೆ c_label_vars *label_vars;
	  ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ ix;
	  ರಚನೆ c_goto_bindings *g;

	  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (b->decl) != LABEL_DECL)
	    ಮುಂದುವರಿ;
	  label_vars = b->u.label;
	  ++label_vars->label_bindings.stmt_exprs;
	  FOR_EACH_VEC_ಸುರಕ್ಷಿತ_ELT (label_vars->gotos, ix, g)
	    ++g->goto_bindings.stmt_exprs;
	}
    }

  ಆದರೆ (switch_bindings != ಖಾಲಿ)
    ++switch_bindings->stmt_exprs;
}

/* Adjust the bindings for the end of a statement expression.  */

ಶೂನ್ಯ
c_bindings_ಕೊನೆ_stmt_ಅಭಿವ್ಯಕ್ತಿ (ರಚನೆ c_spot_bindings *switch_bindings)
{
  ರಚನೆ c_scope *scope;

  ಗಾಗಿ (scope = current_scope; scope != ಖಾಲಿ; scope = scope->outer)
    {
      ರಚನೆ c_binding *b;

      ಆದರೆ (!scope->has_label_bindings)
	ಮುಂದುವರಿ;

      ಗಾಗಿ (b = scope->bindings; b != ಖಾಲಿ; b = b->prev)
	{
	  ರಚನೆ c_label_vars *label_vars;
	  ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ ix;
	  ರಚನೆ c_goto_bindings *g;

	  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (b->decl) != LABEL_DECL)
	    ಮುಂದುವರಿ;
	  label_vars = b->u.label;
	  --label_vars->label_bindings.stmt_exprs;
	  ಆದರೆ (label_vars->label_bindings.stmt_exprs < 0)
	    {
	      label_vars->label_bindings.ಎಡ_stmt_ಅಭಿವ್ಯಕ್ತಿ = ನಿಜ;
	      label_vars->label_bindings.stmt_exprs = 0;
	    }
	  FOR_EACH_VEC_ಸುರಕ್ಷಿತ_ELT (label_vars->gotos, ix, g)
	    {
	      --g->goto_bindings.stmt_exprs;
	      ಆದರೆ (g->goto_bindings.stmt_exprs < 0)
		{
		  g->goto_bindings.ಎಡ_stmt_ಅಭಿವ್ಯಕ್ತಿ = ನಿಜ;
		  g->goto_bindings.stmt_exprs = 0;
		}
	    }
	}
    }

  ಆದರೆ (switch_bindings != ಖಾಲಿ)
    {
      --switch_bindings->stmt_exprs;
      gcc_assert (switch_bindings->stmt_exprs >= 0);
    }
}

/* Push a definition or a declaration of struct, union or enum tag "name".
   "type" should be the type node.
   We assume that the tag "name" is not already defined, and has a location
   of LOC.

   Note that the definition may really be just a forward reference.
   In that case, the TYPE_SIZE will be zero.  */

ಸ್ಥಿರ ಶೂನ್ಯ
pushtag (location_t loc, ವೃಕ್ಷ name, ವೃಕ್ಷ type)
{
  /* Record the identifier as the type's name if it has none.  */
  ಆದರೆ (name && !TYPE_NAME (type))
    TYPE_NAME (type) = name;
  bind (name, type, current_scope, /*invisible=*/ಸುಳ್ಳು, /*nested=*/ಸುಳ್ಳು, loc);

  /* Create a fake NULL-named TYPE_DECL node whose TREE_TYPE will be the
     tagged type we just added to the current scope.  This fake
     NULL-named TYPE_DECL node helps dwarfout.c to know when it needs
     to output a representation of a tagged type, and it also gives
     us a convenient place to record the "scope start" address for the
     tagged type, and it is used to track whether the type is used
     in a non-local context via mark_decl_used.  */

  TYPE_STUB_DECL (type) = pushdecl (build_decl (loc,
						TYPE_DECL, NULL_ವೃಕ್ಷ, type));

  /* An approximation for now, so we can tell this is a function-scope tag.
     This will be updated in pop_scope.  */
  TYPE_CONTEXT (type) = DECL_CONTEXT (TYPE_STUB_DECL (type));

  ಆದರೆ (warn_cxx_compat && name != NULL_ವೃಕ್ಷ)
    {
      ರಚನೆ c_binding *b = I_ಚಿಹ್ನೆ_BINDING (name);

      ಆದರೆ (b != ಖಾಲಿ
	  && b->decl != NULL_ವೃಕ್ಷ
	  && ವೃಕ್ಷ_ಸಂಕೇತ (b->decl) == TYPE_DECL
	  && (B_ಒಳ_CURRENT_SCOPE (b)
	      || (current_scope == file_scope && B_ಒಳ_EXTERNAL_SCOPE (b)))
	  && (TYPE_MAIN_VARIANT (ವೃಕ್ಷ_TYPE (b->decl))
	      != TYPE_MAIN_VARIANT (type)))
	{
	  auto_diagnostic_ಗುಂಪು d;
	  ಆದರೆ (warning_at (loc, OPT_Wc___compat,
			  "using %qD as both a typedef and a tag is "
			  "invalid in C++", b->decl)
	      && b->locus != UNKNOWN_LOCATION)
	    inform (b->locus, "originally defined here");
	}
    }
}

/* An exported interface to pushtag.  This is used by the gdb plugin's
   binding oracle to introduce a new tag binding.  */

ಶೂನ್ಯ
c_pushtag (location_t loc, ವೃಕ್ಷ name, ವೃಕ್ಷ type)
{
  pushtag (loc, name, type);
}

/* An exported interface to bind a declaration.  LOC is the location
   to use.  DECL is the declaration to bind.  The decl's name is used
   to determine how it is bound.  If DECL is a VAR_DECL, then
   IS_GLOBAL determines whether the decl is put into the global (file
   and external) scope or the current function's scope; if DECL is not
   a VAR_DECL then it is always put into the file scope.  */

ಶೂನ್ಯ
c_bind (location_t loc, ವೃಕ್ಷ decl, ತಾರ್ಕಿಕ is_global)
{
  ರಚನೆ c_scope *scope;
  ತಾರ್ಕಿಕ nested = ಸುಳ್ಳು;

  ಆದರೆ (!VAR_P (decl) || current_function_scope == ಖಾಲಿ)
    {
      /* Types and functions are always considered to be global.  */
      scope = file_scope;
      DECL_EXTERNAL (decl) = 1;
      ವೃಕ್ಷ_ಬಹಿರಂಗ (decl) = 1;
    }
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (is_global)
    {
      /* Also bind it into the external scope.  */
      bind (DECL_NAME (decl), decl, external_scope, ನಿಜ, ಸುಳ್ಳು, loc);
      nested = ನಿಜ;
      scope = file_scope;
      DECL_EXTERNAL (decl) = 1;
      ವೃಕ್ಷ_ಬಹಿರಂಗ (decl) = 1;
    }
  ಇಲ್ಲದಿದ್ದರೆ
    {
      DECL_CONTEXT (decl) = current_function_decl;
      ವೃಕ್ಷ_ಬಹಿರಂಗ (decl) = 0;
      scope = current_function_scope;
    }

  bind (DECL_NAME (decl), decl, scope, ಸುಳ್ಳು, nested, loc);
}


/* Stores the first FILE*, const struct tm* etc. argument type (whatever
   it is) seen in a declaration of a file I/O etc. built-in, corresponding
   to the builtin_structptr_types array.  Subsequent declarations of such
   built-ins are expected to refer to it rather than to fileptr_type_node,
   etc. which is just void* (or to any other type).
   Used only by match_builtin_function_types.  */

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ builtin_structptr_type_ಎಣಿಕೆ
  = ARRAY_ಗಾತ್ರ (builtin_structptr_types);

ಸ್ಥಿರ GTY(()) ವೃಕ್ಷ ಕೊನೆಯ_structptr_types[builtin_structptr_type_ಎಣಿಕೆ];

/* Returns true if types T1 and T2 representing return types or types
   of function arguments are close enough to be considered interchangeable
   in redeclarations of built-in functions.  */

ಸ್ಥಿರ ತಾರ್ಕಿಕ
types_close_enough_ಗಮ್ಯ_ಹೊಂದಿಕೆ (ವೃಕ್ಷ t1, ವೃಕ್ಷ t2)
{
  ಹಿಂತಿರುಗಿ (TYPE_ಬಹುಲಕ (t1) == TYPE_ಬಹುಲಕ (t2)
	  && ಸೂಚಕ_TYPE_P (t1) == ಸೂಚಕ_TYPE_P (t2)
	  && FUNCTION_ಸೂಚಕ_TYPE_P (t1) == FUNCTION_ಸೂಚಕ_TYPE_P (t2));
}

/* Subroutine of compare_decls.  Allow harmless mismatches in return
   and argument types provided that the type modes match.  Set *STRICT
   and *ARGNO to the expected argument type and number in case of
   an argument type mismatch or null and zero otherwise.  Return
   a unified type given a suitable match, and 0 otherwise.  */

ಸ್ಥಿರ ವೃಕ್ಷ
ಹೊಂದಿಕೆ_builtin_function_types (ವೃಕ್ಷ newtype, ವೃಕ್ಷ oldtype,
			      ವೃಕ್ಷ *strict, ಚಿಹ್ನೆರಹಿತ *argno)
{
  *argno = 0;
  *strict = NULL_ವೃಕ್ಷ;

  /* Accept the return type of the new declaration if it has the same
     mode and if they're both pointers or if neither is.  */
  ವೃಕ್ಷ oldrettype = ವೃಕ್ಷ_TYPE (oldtype);
  ವೃಕ್ಷ newrettype = ವೃಕ್ಷ_TYPE (newtype);

  ಆದರೆ (!types_close_enough_ಗಮ್ಯ_ಹೊಂದಿಕೆ (oldrettype, newrettype))
    ಹಿಂತಿರುಗಿ NULL_ವೃಕ್ಷ;

  /* Check that the return types are compatible but don't fail if they
     are not (e.g., int vs long in ILP32) and just let the caller know.  */
  ಆದರೆ (!comptypes (TYPE_MAIN_VARIANT (oldrettype),
		  TYPE_MAIN_VARIANT (newrettype)))
    *strict = oldrettype;

  ವೃಕ್ಷ oldargs = TYPE_ARG_TYPES (oldtype);
  ವೃಕ್ಷ newargs = TYPE_ARG_TYPES (newtype);
  ವೃಕ್ಷ tryargs = newargs;

  ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ nlst = ARRAY_ಗಾತ್ರ (ಕೊನೆಯ_structptr_types);
  ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ nbst = ARRAY_ಗಾತ್ರ (builtin_structptr_types);

  gcc_checking_assert (nlst == nbst);

  ಗಾಗಿ (ಚಿಹ್ನೆರಹಿತ i = 1; oldargs || newargs; ++i)
    {
      ಆದರೆ (!oldargs
	  || !newargs
	  || !ವೃಕ್ಷ_ಮೌಲ್ಯ (oldargs)
	  || !ವೃಕ್ಷ_ಮೌಲ್ಯ (newargs))
	ಹಿಂತಿರುಗಿ NULL_ವೃಕ್ಷ;

      ವೃಕ್ಷ oldtype = TYPE_MAIN_VARIANT (ವೃಕ್ಷ_ಮೌಲ್ಯ (oldargs));
      ವೃಕ್ಷ newtype = ವೃಕ್ಷ_ಮೌಲ್ಯ (newargs);
      ಆದರೆ (newtype == error_mark_ಗಂಟು)
       ಹಿಂತಿರುಗಿ NULL_ವೃಕ್ಷ;
      newtype = TYPE_MAIN_VARIANT (newtype);

      ಆದರೆ (!types_close_enough_ಗಮ್ಯ_ಹೊಂದಿಕೆ (oldtype, newtype))
	ಹಿಂತಿರುಗಿ NULL_ವೃಕ್ಷ;

      ಚಿಹ್ನೆರಹಿತ j = nbst;
      ಆದರೆ (ಸೂಚಕ_TYPE_P (oldtype))
	/* Iterate over well-known struct types like FILE (whose types
	   aren't known to us) and compare the pointer to each to
	   the pointer argument.  */
	ಗಾಗಿ (j = 0; j < nbst; ++j)
	  {
	    ಆದರೆ (ವೃಕ್ಷ_ಮೌಲ್ಯ (oldargs) != builtin_structptr_types[j].ಗಂಟು)
	      ಮುಂದುವರಿ;
	    /* Store the first FILE* etc. argument type (whatever it is), and
	       expect any subsequent declarations of file I/O etc. built-ins
	       to refer to it rather than to fileptr_type_node etc. which is
	       just void* (or const void*).  */
	    ಆದರೆ (ಕೊನೆಯ_structptr_types[j])
	      {
		ಆದರೆ (!comptypes (ಕೊನೆಯ_structptr_types[j], newtype))
		  {
		    *argno = i;
		    *strict = ಕೊನೆಯ_structptr_types[j];
		  }
	      }
	    ಇಲ್ಲದಿದ್ದರೆ
	      ಕೊನೆಯ_structptr_types[j] = newtype;
	    ನಿಲ್ಲಿಸು;
	  }

      ಆದರೆ (j == nbst && !comptypes (oldtype, newtype))
	{
	  ಆದರೆ (ಸೂಚಕ_TYPE_P (oldtype))
	    {
	      /* For incompatible pointers, only reject differences in
		 the unqualified variants of the referenced types but
		 consider differences in qualifiers as benign (report
		 those to caller via *STRICT below).  */
	      ವೃಕ್ಷ oldref = TYPE_MAIN_VARIANT (ವೃಕ್ಷ_TYPE (oldtype));
	      ವೃಕ್ಷ newref = TYPE_MAIN_VARIANT (ವೃಕ್ಷ_TYPE (newtype));
	      ಆದರೆ (!comptypes (oldref, newref))
		ಹಿಂತಿರುಗಿ NULL_ವೃಕ್ಷ;
	    }

	  ಆದರೆ (!*strict)
	    {
	      *argno = i;
	      *strict = oldtype;
	    }
	}

      oldargs = ವೃಕ್ಷ_CHAIN (oldargs);
      newargs = ವೃಕ್ಷ_CHAIN (newargs);
    }

  ವೃಕ್ಷ trytype = c_build_function_type (newrettype, tryargs);

  /* Allow declaration to change transaction_safe attribute.  */
  ವೃಕ್ಷ oldattrs = TYPE_ಗುಣಲಕ್ಷಣಗಳು (oldtype);
  ವೃಕ್ಷ oldtsafe = lookup_attribute ("transaction_safe", oldattrs);
  ವೃಕ್ಷ newattrs = TYPE_ಗುಣಲಕ್ಷಣಗಳು (newtype);
  ವೃಕ್ಷ newtsafe = lookup_attribute ("transaction_safe", newattrs);
  ಆದರೆ (oldtsafe && !newtsafe)
    oldattrs = remove_attribute ("transaction_safe", oldattrs);
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (newtsafe && !oldtsafe)
    oldattrs = ವೃಕ್ಷ_cons (get_identifier ("transaction_safe"),
			  NULL_ವೃಕ್ಷ, oldattrs);

  ಹಿಂತಿರುಗಿ c_build_type_attribute_variant (trytype, oldattrs);
}

/* Subroutine of diagnose_mismatched_decls.  Check for function type
   mismatch involving an empty arglist vs a nonempty one and give clearer
   diagnostics.  */
ಸ್ಥಿರ ಶೂನ್ಯ
diagnose_arglist_conflict (ವೃಕ್ಷ newdecl, ವೃಕ್ಷ olddecl,
			   ವೃಕ್ಷ newtype, ವೃಕ್ಷ oldtype)
{
  ವೃಕ್ಷ t;

  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (olddecl) != FUNCTION_DECL
      || !comptypes (ವೃಕ್ಷ_TYPE (oldtype), ವೃಕ್ಷ_TYPE (newtype))
      || !((!prototype_p (oldtype) && DECL_INITIAL (olddecl) == NULL_ವೃಕ್ಷ)
	   || (!prototype_p (newtype) && DECL_INITIAL (newdecl) == NULL_ವೃಕ್ಷ)))
    ಹಿಂತಿರುಗಿ;

  t = TYPE_ARG_TYPES (oldtype);
  ಆದರೆ (t == NULL_ವೃಕ್ಷ)
    t = TYPE_ARG_TYPES (newtype);
  ಗಾಗಿ (; t; t = ವೃಕ್ಷ_CHAIN (t))
    {
      ವೃಕ್ಷ type = ವೃಕ್ಷ_ಮೌಲ್ಯ (t);

      ಆದರೆ (ವೃಕ್ಷ_CHAIN (t) == NULL_ವೃಕ್ಷ
	  && TYPE_MAIN_VARIANT (type) != void_type_ಗಂಟು)
	{
	  inform (ಒಳಹರಿವು_location, "a parameter list with an ellipsis "
		  "cannot match an empty parameter name list declaration");
	  ನಿಲ್ಲಿಸು;
	}

      ಆದರೆ (!error_ಕಾರ್ಯಾಂಶ_p (type)
	  && c_type_promotes_ಗಮ್ಯ (type) != type)
	{
	  inform (ಒಳಹರಿವು_location, "an argument type that has a default "
		  "promotion cannot match an empty parameter name list "
		  "declaration");
	  ನಿಲ್ಲಿಸು;
	}
    }
}

/* Another subroutine of diagnose_mismatched_decls.  OLDDECL is an
   old-style function definition, NEWDECL is a prototype declaration.
   Diagnose inconsistencies in the argument list.  Returns TRUE if
   the prototype is compatible, FALSE if not.  */
ಸ್ಥಿರ ತಾರ್ಕಿಕ
validate_proto_after_old_defn (ವೃಕ್ಷ newdecl, ವೃಕ್ಷ newtype, ವೃಕ್ಷ oldtype)
{
  ವೃಕ್ಷ newargs, oldargs;
  ಪೂರ್ಣಾಂಕ i;

#ವ್ಯಾಖ್ಯಾನಿಸು ಕೊನೆ_ದ_ARGLIST(t) ((t) == void_type_ಗಂಟು)

  oldargs = TYPE_ACTUAL_ARG_TYPES (oldtype);
  newargs = TYPE_ARG_TYPES (newtype);
  i = 1;

  ಗಾಗಿ (;;)
    {
      ವೃಕ್ಷ oldargtype = ವೃಕ್ಷ_ಮೌಲ್ಯ (oldargs);
      ವೃಕ್ಷ newargtype = ವೃಕ್ಷ_ಮೌಲ್ಯ (newargs);

      ಆದರೆ (oldargtype == error_mark_ಗಂಟು || newargtype == error_mark_ಗಂಟು)
	ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;

      oldargtype = (TYPE_ATOMIC (oldargtype)
		    ? c_build_qualified_type (TYPE_MAIN_VARIANT (oldargtype),
					      TYPE_QUAL_ATOMIC)
		    : TYPE_MAIN_VARIANT (oldargtype));
      newargtype = (TYPE_ATOMIC (newargtype)
		    ? c_build_qualified_type (TYPE_MAIN_VARIANT (newargtype),
					      TYPE_QUAL_ATOMIC)
		    : TYPE_MAIN_VARIANT (newargtype));

      ಆದರೆ (ಕೊನೆ_ದ_ARGLIST (oldargtype) && ಕೊನೆ_ದ_ARGLIST (newargtype))
	ನಿಲ್ಲಿಸು;

      /* Reaching the end of just one list means the two decls don't
	 agree on the number of arguments.  */
      ಆದರೆ (ಕೊನೆ_ದ_ARGLIST (oldargtype))
	{
	  error ("prototype for %q+D declares more arguments "
		 "than previous old-style definition", newdecl);
	  ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
	}
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ಕೊನೆ_ದ_ARGLIST (newargtype))
	{
	  error ("prototype for %q+D declares fewer arguments "
		 "than previous old-style definition", newdecl);
	  ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
	}

      /* Type for passing arg must be consistent with that declared
	 for the arg.  */
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!comptypes (oldargtype, newargtype))
	{
	  error ("prototype for %q+D declares argument %d"
		 " with incompatible type",
		 newdecl, i);
	  ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
	}

      oldargs = ವೃಕ್ಷ_CHAIN (oldargs);
      newargs = ವೃಕ್ಷ_CHAIN (newargs);
      i++;
    }

  /* If we get here, no errors were found, but do issue a warning
     for this poor-style construct.  */
  warning (0, "prototype for %q+D follows non-prototype definition",
	   newdecl);
  ಹಿಂತಿರುಗಿ ನಿಜ;
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು ಕೊನೆ_ದ_ARGLIST
}

/* Subroutine of diagnose_mismatched_decls.  Report the location of DECL,
   first in a pair of mismatched declarations, using the diagnostic
   function DIAG.  */
ಸ್ಥಿರ ಶೂನ್ಯ
locate_old_decl (ವೃಕ್ಷ decl)
{
  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (decl) == FUNCTION_DECL
      && fndecl_built_ಒಳ_p (decl)
      && !C_DECL_DECLARED_BUILTIN (decl))
    ;
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (DECL_INITIAL (decl))
    inform (ಒಳಹರಿವು_location,
	    "previous definition of %q+D with type %qT",
	    decl, ವೃಕ್ಷ_TYPE (decl));
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (C_DECL_IMPLICIT (decl))
    inform (ಒಳಹರಿವು_location,
	    "previous implicit declaration of %q+D with type %qT",
	    decl, ವೃಕ್ಷ_TYPE (decl));
  ಇಲ್ಲದಿದ್ದರೆ
    inform (ಒಳಹರಿವು_location,
	    "previous declaration of %q+D with type %qT",
	    decl, ವೃಕ್ಷ_TYPE (decl));
}


/* Helper function.  For a tagged type, it finds the declaration
   for a visible tag declared in the same scope if such a
   declaration exists.  */
ಸ್ಥಿರ ವೃಕ್ಷ
ಹಿಂದಿನ_ಟ್ಯಾಗ್ (ವೃಕ್ಷ type)
{
  ರಚನೆ c_binding *b = ಖಾಲಿ;
  ವೃಕ್ಷ name = c_type_ಟ್ಯಾಗ್ (type);

  ಆದರೆ (name)
    b = I_ಟ್ಯಾಗ್_BINDING (name);

  ಆದರೆ (b)
    b = b->shadowed;

  ಆದರೆ (b && B_ಒಳ_CURRENT_SCOPE (b))
    ಹಿಂತಿರುಗಿ b->decl;

  ಹಿಂತಿರುಗಿ NULL_ವೃಕ್ಷ;
}

/* Subroutine to mark functions as versioned when using the attribute
   'target_version'.  */

ಸ್ಥಿರ ಶೂನ್ಯ
maybe_mark_function_versioned (ವೃಕ್ಷ decl)
{
  ಆದರೆ (!DECL_FUNCTION_VERSIONED (decl))
    {
      /* Check if the name of the function has been overridden.  */
      ಆದರೆ (DECL_ASSEMBLER_NAME_ಗಣ_P (decl)
	  && IDENTIFIER_ಸೂಚಕ (DECL_ASSEMBLER_NAME (decl))[0] == '*')
	error_at (DECL_ಮೂಲ_LOCATION (decl),
		  "cannot use function multiversioning on a renamed function");

      /* We need to insert function version now to make sure the correct
	 pre-mangled assembler name is recorded.  */
      cgraph_ಗಂಟು *ಗಂಟು = cgraph_ಗಂಟು::get_create (decl);

      ಆದರೆ (!ಗಂಟು->function_ಆವೃತ್ತಿ ())
	ಗಂಟು->ಸೇರಿಸು_new_function_ಆವೃತ್ತಿ ();

      DECL_FUNCTION_VERSIONED (decl) = 1;

      ವೃಕ್ಷ mangled_name
	= targetm.mangle_decl_assembler_name (decl, DECL_NAME (decl));
      ಗಣ_DECL_ASSEMBLER_NAME (decl, mangled_name);
    }
}

/* Subroutine of duplicate_decls.  Compare NEWDECL to OLDDECL.
   Returns true if the caller should proceed to merge the two, false
   if OLDDECL should simply be discarded.  As a side effect, issues
   all necessary diagnostics for invalid or poor-style combinations.
   If it returns true, writes the types of NEWDECL and OLDDECL to
   *NEWTYPEP and *OLDTYPEP - these may have been adjusted from
   TREE_TYPE (NEWDECL, OLDDECL) respectively.  */

ಸ್ಥಿರ ತಾರ್ಕಿಕ
diagnose_mismatched_decls (ವೃಕ್ಷ newdecl, ವೃಕ್ಷ olddecl,
			   ವೃಕ್ಷ *newtypep, ವೃಕ್ಷ *oldtypep)
{
  ವೃಕ್ಷ newtype, oldtype;
  ತಾರ್ಕಿಕ retval = ನಿಜ;

#ವ್ಯಾಖ್ಯಾನಿಸು DECL_EXTERN_INLINE(DECL) (DECL_DECLARED_INLINE_P (DECL)  \
				  && DECL_EXTERNAL (DECL))

  /* If we have error_mark_node for either decl or type, just discard
     the previous decl - we're in an error cascade already.  */
  ಆದರೆ (olddecl == error_mark_ಗಂಟು || newdecl == error_mark_ಗಂಟು)
    ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
  *oldtypep = oldtype = ವೃಕ್ಷ_TYPE (olddecl);
  *newtypep = newtype = ವೃಕ್ಷ_TYPE (newdecl);
  ಆದರೆ (oldtype == error_mark_ಗಂಟು || newtype == error_mark_ಗಂಟು)
    ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;

  /* Two different categories of symbol altogether.  This is an error
     unless OLDDECL is a builtin.  OLDDECL will be discarded in any case.  */
  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (olddecl) != ವೃಕ್ಷ_ಸಂಕೇತ (newdecl))
    {
      ಆದರೆ (!(ವೃಕ್ಷ_ಸಂಕೇತ (olddecl) == FUNCTION_DECL
	    && fndecl_built_ಒಳ_p (olddecl)
	    && !C_DECL_DECLARED_BUILTIN (olddecl)))
	{
	  auto_diagnostic_ಗುಂಪು d;
	  error ("%q+D redeclared as different kind of symbol", newdecl);
	  locate_old_decl (olddecl);
	}
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ವೃಕ್ಷ_ಬಹಿರಂಗ (newdecl))
	warning (OPT_Wbuiltin_declaration_mismatch,
		 "built-in function %q+D declared as non-function",
		 newdecl);
      ಇಲ್ಲದಿದ್ದರೆ
	warning (OPT_Wshadow, "declaration of %q+D shadows "
		 "a built-in function", newdecl);
      ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
    }

  /* Enumerators have no linkage, so may only be declared once in a
     given scope.  */
  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (olddecl) == CONST_DECL)
    {
      ಆದರೆ (flag_isoc23
	  && TYPE_NAME (DECL_CONTEXT (newdecl))
	  && DECL_CONTEXT (newdecl) != DECL_CONTEXT (olddecl)
	  && TYPE_NAME (DECL_CONTEXT (newdecl)) == TYPE_NAME (DECL_CONTEXT (olddecl)))
	{
	  ಆದರೆ (!simple_cst_equal (DECL_INITIAL (olddecl), DECL_INITIAL (newdecl)))
	    {
	      auto_diagnostic_ಗುಂಪು d;
	      error ("conflicting redeclaration of enumerator %q+D", newdecl);
	      locate_old_decl (olddecl);
	    }
	}
      ಇಲ್ಲದಿದ್ದರೆ
	{
	  auto_diagnostic_ಗುಂಪು d;
	  error ("redeclaration of enumerator %q+D", newdecl);
	  locate_old_decl (olddecl);
	}
      ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
    }

  ತಾರ್ಕಿಕ pedwarned = ಸುಳ್ಳು;
  ತಾರ್ಕಿಕ warned = ಸುಳ್ಳು;
  ತಾರ್ಕಿಕ enum_and_int_p = ಸುಳ್ಳು;
  auto_diagnostic_ಗುಂಪು d;

  ತಾರ್ಕಿಕ comptypes_ಫಲಿತಾಂಶ = comptypes_check_enum_int (oldtype, newtype,
						    &enum_and_int_p);
  ಆದರೆ (!comptypes_ಫಲಿತಾಂಶ)
    {
      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (olddecl) == FUNCTION_DECL
	  && fndecl_built_ಒಳ_p (olddecl, BUILT_ಒಳ_ಸಾಮಾನ್ಯ)
	  && !C_DECL_DECLARED_BUILTIN (olddecl))
	{
	  /* Accept "harmless" mismatches in function types such
	     as missing qualifiers or int vs long when they're the same
	     size.  However, diagnose return and argument types that are
	     incompatible according to language rules.  */
	  ವೃಕ್ಷ mismatch_expect;
	  ಚಿಹ್ನೆರಹಿತ mismatch_argno;

	  ವೃಕ್ಷ trytype = ಹೊಂದಿಕೆ_builtin_function_types (newtype, oldtype,
						       &mismatch_expect,
						       &mismatch_argno);

	  ಆದರೆ (trytype && comptypes (newtype, trytype))
	    *oldtypep = oldtype = trytype;
	  ಇಲ್ಲದಿದ್ದರೆ
	    {
	      /* If types don't match for a built-in, throw away the
		 built-in.  No point in calling locate_old_decl here, it
		 won't print anything.  */
	      ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಶೀರ್ಷಿಕೆ = ಶೀರ್ಷಿಕೆ_for_builtin_fn (olddecl);
	      location_t loc = DECL_ಮೂಲ_LOCATION (newdecl);
	      ಆದರೆ (warning_at (loc, OPT_Wbuiltin_declaration_mismatch,
			      "conflicting types for built-in function %q+D; "
			      "expected %qT",
			      newdecl, oldtype)
		  && ಶೀರ್ಷಿಕೆ)
		{
		  /* Suggest the right header to include as the preferred
		     solution rather than the spelling of the declaration.  */
		  rich_location richloc (ಸಾಲು_ಕೋಷ್ಟಕ, loc);
		  maybe_ಕೂಡಿಸು_include_fixit (&richloc, ಶೀರ್ಷಿಕೆ, ನಿಜ);
		  inform (&richloc,
			  "%qD is declared in header %qs", olddecl, ಶೀರ್ಷಿಕೆ);
		}
	      ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
	    }

	  ಆದರೆ (mismatch_expect && extra_warnings)
	    {
	      location_t newloc = DECL_ಮೂಲ_LOCATION (newdecl);
	      ತಾರ್ಕಿಕ warned = ಸುಳ್ಳು;
	      ಆದರೆ (mismatch_argno)
		warned = warning_at (newloc, OPT_Wbuiltin_declaration_mismatch,
				     "mismatch in argument %u type of built-in "
				     "function %qD; expected %qT",
				     mismatch_argno, newdecl, mismatch_expect);
	      ಇಲ್ಲದಿದ್ದರೆ
		warned = warning_at (newloc, OPT_Wbuiltin_declaration_mismatch,
				     "mismatch in return type of built-in "
				     "function %qD; expected %qT",
				     newdecl, mismatch_expect);
	      ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಶೀರ್ಷಿಕೆ = ಶೀರ್ಷಿಕೆ_for_builtin_fn (olddecl);
	      ಆದರೆ (warned && ಶೀರ್ಷಿಕೆ)
		{
		  rich_location richloc (ಸಾಲು_ಕೋಷ್ಟಕ, newloc);
		  maybe_ಕೂಡಿಸು_include_fixit (&richloc, ಶೀರ್ಷಿಕೆ, ನಿಜ);
		  inform (&richloc,
			  "%qD is declared in header %qs", olddecl, ಶೀರ್ಷಿಕೆ);
		}
	    }
	}
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (olddecl) == FUNCTION_DECL
	       && DECL_IS_UNDECLARED_BUILTIN (olddecl))
	{
	  /* A conflicting function declaration for a predeclared
	     function that isn't actually built in.  Objective C uses
	     these.  The new declaration silently overrides everything
	     but the volatility (i.e. noreturn) indication.  See also
	     below.  FIXME: Make Objective C use normal builtins.  */
	  ವೃಕ್ಷ_THIS_VOLATILE (newdecl) |= ವೃಕ್ಷ_THIS_VOLATILE (olddecl);
	  ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
	}
      /* Permit void foo (...) to match int foo (...) if the latter is
	 the definition and implicit int was used.  See
	 c-torture/compile/920625-2.c.  */
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (newdecl) == FUNCTION_DECL && DECL_INITIAL (newdecl)
	       && TYPE_MAIN_VARIANT (ವೃಕ್ಷ_TYPE (oldtype)) == void_type_ಗಂಟು
	       && TYPE_MAIN_VARIANT (ವೃಕ್ಷ_TYPE (newtype)) == integer_type_ಗಂಟು
	       && C_FUNCTION_IMPLICIT_INT (newdecl) && !DECL_INITIAL (olddecl))
	{
	  pedwarned = pedwarn (ಒಳಹರಿವು_location, 0,
			       "conflicting types for %q+D", newdecl);
	  /* Make sure we keep void as the return type.  */
	  ವೃಕ್ಷ_TYPE (newdecl) = *newtypep = newtype = oldtype;
	  C_FUNCTION_IMPLICIT_INT (newdecl) = 0;
	}
      /* Permit void foo (...) to match an earlier call to foo (...) with
	 no declared type (thus, implicitly int).  */
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (newdecl) == FUNCTION_DECL
	       && TYPE_MAIN_VARIANT (ವೃಕ್ಷ_TYPE (newtype)) == void_type_ಗಂಟು
	       && TYPE_MAIN_VARIANT (ವೃಕ್ಷ_TYPE (oldtype)) == integer_type_ಗಂಟು
	       && C_DECL_IMPLICIT (olddecl) && !DECL_INITIAL (olddecl))
	{
	  pedwarned = pedwarn (ಒಳಹರಿವು_location, 0,
			       "conflicting types for %q+D; have %qT",
			       newdecl, newtype);
	  /* Make sure we keep void as the return type.  */
	  ವೃಕ್ಷ_TYPE (olddecl) = *oldtypep = oldtype = newtype;
	}
      ಇಲ್ಲದಿದ್ದರೆ
	{
	  ಪೂರ್ಣಾಂಕ new_quals = TYPE_QUALS (newtype);
	  ಪೂರ್ಣಾಂಕ old_quals = TYPE_QUALS (oldtype);

	  ಆದರೆ (new_quals != old_quals)
	    {
	      addr_space_t new_addr = DECODE_QUAL_ADDR_SPACE (new_quals);
	      addr_space_t old_addr = DECODE_QUAL_ADDR_SPACE (old_quals);
	      ಆದರೆ (new_addr != old_addr)
		{
		  ಆದರೆ (ADDR_SPACE_GENERIC_P (new_addr))
		    error ("conflicting named address spaces (generic vs %s) "
			   "for %q+D",
			   c_addr_space_name (old_addr), newdecl);
		  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ADDR_SPACE_GENERIC_P (old_addr))
		    error ("conflicting named address spaces (%s vs generic) "
			   "for %q+D",
			   c_addr_space_name (new_addr), newdecl);
		  ಇಲ್ಲದಿದ್ದರೆ
		    error ("conflicting named address spaces (%s vs %s) "
			   "for %q+D",
			   c_addr_space_name (new_addr),
			   c_addr_space_name (old_addr),
			   newdecl);
		}

	      ಆದರೆ (CLEAR_QUAL_ADDR_SPACE (new_quals)
		  != CLEAR_QUAL_ADDR_SPACE (old_quals))
		error ("conflicting type qualifiers for %q+D", newdecl);
	    }
	  ಇಲ್ಲದಿದ್ದರೆ
	    {
	      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (olddecl) == FUNCTION_DECL)
		{
		  ವೃಕ್ಷ attrs = TYPE_ಗುಣಲಕ್ಷಣಗಳು (ವೃಕ್ಷ_TYPE (olddecl));
		  ಆದರೆ (attrs && !TYPE_ಗುಣಲಕ್ಷಣಗಳು (ವೃಕ್ಷ_TYPE (newdecl)))
		    {
		      /* Similar to the C++ front-end, for FUNCTION_DECL,
			 if OLDDECL has attributes and NEWDECL doesn't,
			 try the type with OLDDECL attributes.  */
		      ವೃಕ್ಷ rettype = ವೃಕ್ಷ_TYPE (newtype);
		      ವೃಕ್ಷ tryargs = TYPE_ARG_TYPES (newtype);
		      ವೃಕ್ಷ trytype = c_build_function_type (rettype,
							    tryargs);
		      trytype = c_build_type_attribute_variant (trytype,
								attrs);
		      ಆದರೆ (comptypes (oldtype, trytype))
			{
			  *newtypep = newtype = trytype;
			  comptypes_ಫಲಿತಾಂಶ = ನಿಜ;
			}
		    }
		}

	      ಆದರೆ (!comptypes_ಫಲಿತಾಂಶ)
		error ("conflicting types for %q+D; have %qT", newdecl,
		       newtype);
	    }
	  ಆದರೆ (!comptypes_ಫಲಿತಾಂಶ)
	    {
	      diagnose_arglist_conflict (newdecl, olddecl, newtype,
					 oldtype);
	      locate_old_decl (olddecl);
	      ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
	    }
	}
    }
  /* Warn about enum/integer type mismatches.  They are compatible types
     (C23 6.7.2.2/5), but may pose portability problems.  */
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (enum_and_int_p
	   && ವೃಕ್ಷ_ಸಂಕೇತ (newdecl) != TYPE_DECL
	   /* Don't warn about acc_on_device built-in redeclaration,
	      the built-in is declared with int rather than enum because
	      the enum isn't intrinsic.  */
	   && !(ವೃಕ್ಷ_ಸಂಕೇತ (olddecl) == FUNCTION_DECL
		&& fndecl_built_ಒಳ_p (olddecl, BUILT_ಒಳ_ACC_ON_DEVICE)
		&& !C_DECL_DECLARED_BUILTIN (olddecl)))
    warned = warning_at (DECL_ಮೂಲ_LOCATION (newdecl),
			 OPT_Wenum_int_mismatch,
			 "conflicting types for %q+D due to enum/integer "
			 "mismatch; have %qT", newdecl, newtype);

  /* Redeclaration of a type is a constraint violation (6.7.2.3p1),
     but silently ignore the redeclaration if either is in a system
     header.  (Conflicting redeclarations were handled above.)  This
     is allowed for C11 if the types are the same, not just
     compatible.  */
  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (newdecl) == TYPE_DECL)
    {
      ಆದರೆ (!comptypes_same_p (oldtype, newtype))
	{
	  error ("redefinition of typedef %q+D with different type", newdecl);
	  locate_old_decl (olddecl);
	  ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
	}

      ಆದರೆ (DECL_ಒಳ_SYSTEM_ಶೀರ್ಷಿಕೆ (newdecl)
	  || DECL_ಒಳ_SYSTEM_ಶೀರ್ಷಿಕೆ (olddecl)
	  || warning_suppressed_p (newdecl, OPT_Wpedantic)
	  || warning_suppressed_p (olddecl, OPT_Wpedantic))
	ಹಿಂತಿರುಗಿ ನಿಜ;  /* Allow OLDDECL to continue in use.  */

      ಆದರೆ (c_type_variably_modified_p (newtype))
	{
	  error ("redefinition of typedef %q+D with variably modified type",
		 newdecl);
	  locate_old_decl (olddecl);
	}
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (pedwarn_c99 (ಒಳಹರಿವು_location, OPT_Wpedantic,
			    "redefinition of typedef %q+D", newdecl))
	locate_old_decl (olddecl);

      ಹಿಂತಿರುಗಿ ನಿಜ;
    }

  /* Function declarations can either be 'static' or 'extern' (no
     qualifier is equivalent to 'extern' - C99 6.2.2p5) and therefore
     can never conflict with each other on account of linkage
     (6.2.2p4).  Multiple definitions are not allowed (6.9p3,5) but
     gnu89 mode permits two definitions if one is 'extern inline' and
     one is not.  The non- extern-inline definition supersedes the
     extern-inline definition.  */

  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (newdecl) == FUNCTION_DECL)
    {
      /* If you declare a built-in function name as static, or
	 define the built-in with an old-style definition (so we
	 can't validate the argument list) the built-in definition is
	 overridden, but optionally warn this was a bad choice of name.  */
      ಆದರೆ (fndecl_built_ಒಳ_p (olddecl)
	  && !C_DECL_DECLARED_BUILTIN (olddecl))
	{
	  ಆದರೆ (!ವೃಕ್ಷ_ಬಹಿರಂಗ (newdecl)
	      || (DECL_INITIAL (newdecl)
		  && !prototype_p (ವೃಕ್ಷ_TYPE (newdecl))))
	    {
	      warning_at (DECL_ಮೂಲ_LOCATION (newdecl),
			  OPT_Wshadow, "declaration of %qD shadows "
			  "a built-in function", newdecl);
	      /* Discard the old built-in function.  */
	      ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
	    }

	  ಆದರೆ (!prototype_p (ವೃಕ್ಷ_TYPE (newdecl)))
	    {
	      /* Set for built-ins that take no arguments.  */
	      ತಾರ್ಕಿಕ func_void_ವಾದಗಳು = ಸುಳ್ಳು;
	      ಆದರೆ (ವೃಕ್ಷ at = TYPE_ARG_TYPES (oldtype))
		func_void_ವಾದಗಳು = VOID_TYPE_P (ವೃಕ್ಷ_ಮೌಲ್ಯ (at));

	      ಆದರೆ (extra_warnings && !func_void_ವಾದಗಳು)
		warning_at (DECL_ಮೂಲ_LOCATION (newdecl),
			    OPT_Wbuiltin_declaration_mismatch,
			    "declaration of built-in function %qD without "
			    "a prototype; expected %qT",
			    newdecl, ವೃಕ್ಷ_TYPE (olddecl));
	    }
	}

      ಆದರೆ (DECL_INITIAL (newdecl))
	{
	  ಆದರೆ (DECL_INITIAL (olddecl))
	    {
	      /* If the new declaration isn't overriding an extern inline
		 reject the new decl. In c99, no overriding is allowed
		 in the same translation unit.  */
	      ಆದರೆ (!DECL_EXTERN_INLINE (olddecl)
		  || DECL_EXTERN_INLINE (newdecl)
		  || (!flag_gnu89_inline
		      && (!DECL_DECLARED_INLINE_P (olddecl)
			  || !lookup_attribute ("gnu_inline",
						DECL_ಗುಣಲಕ್ಷಣಗಳು (olddecl)))
		      && (!DECL_DECLARED_INLINE_P (newdecl)
			  || !lookup_attribute ("gnu_inline",
						DECL_ಗುಣಲಕ್ಷಣಗಳು (newdecl)))))
		{
		  auto_diagnostic_ಗುಂಪು d;
		  error ("redefinition of %q+D", newdecl);
		  locate_old_decl (olddecl);
		  ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
		}
	    }
	}
      /* If we have a prototype after an old-style function definition,
	 the argument types must be checked specially.  */
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (DECL_INITIAL (olddecl)
	       && !prototype_p (oldtype) && prototype_p (newtype)
	       && TYPE_ACTUAL_ARG_TYPES (oldtype))
	{
	  auto_diagnostic_ಗುಂಪು d;
	  ಆದರೆ (!validate_proto_after_old_defn (newdecl, newtype, oldtype))
	    {
	      locate_old_decl (olddecl);
	      ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
	    }
	}
      /* A non-static declaration (even an "extern") followed by a
	 static declaration is undefined behavior per C99 6.2.2p3-5,7.
	 The same is true for a static forward declaration at block
	 scope followed by a non-static declaration/definition at file
	 scope.  Static followed by non-static at the same scope is
	 not undefined behavior, and is the most convenient way to get
	 some effects (see e.g.  what unwind-dw2-fde-glibc.c does to
	 the definition of _Unwind_Find_FDE in unwind-dw2-fde.c), but
	 we do diagnose it if -Wtraditional.  */
      ಆದರೆ (ವೃಕ್ಷ_ಬಹಿರಂಗ (olddecl) && !ವೃಕ್ಷ_ಬಹಿರಂಗ (newdecl))
	{
	  /* Two exceptions to the rule.  If olddecl is an extern
	     inline, or a predeclared function that isn't actually
	     built in, newdecl silently overrides olddecl.  The latter
	     occur only in Objective C; see also above.  (FIXME: Make
	     Objective C use normal builtins.)  */
	  ಆದರೆ (!DECL_IS_UNDECLARED_BUILTIN (olddecl)
	      && !DECL_EXTERN_INLINE (olddecl))
	    {
	      auto_diagnostic_ಗುಂಪು d;
	      error ("static declaration of %q+D follows "
		     "non-static declaration", newdecl);
	      locate_old_decl (olddecl);
	    }
	  ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
	}
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ವೃಕ್ಷ_ಬಹಿರಂಗ (newdecl) && !ವೃಕ್ಷ_ಬಹಿರಂಗ (olddecl))
	{
	  ಆದರೆ (DECL_CONTEXT (olddecl))
	    {
	      auto_diagnostic_ಗುಂಪು d;
	      error ("non-static declaration of %q+D follows "
		     "static declaration", newdecl);
	      locate_old_decl (olddecl);
	      ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
	    }
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (warn_traditional)
	    {
	      warned |= warning (OPT_Wtraditional,
				 "non-static declaration of %q+D "
				 "follows static declaration", newdecl);
	    }
	}

      /* Make sure gnu_inline attribute is either not present, or
	 present on all inline decls.  */
      ಆದರೆ (DECL_DECLARED_INLINE_P (olddecl)
	  && DECL_DECLARED_INLINE_P (newdecl))
	{
	  ತಾರ್ಕಿಕ newa = lookup_attribute ("gnu_inline",
					DECL_ಗುಣಲಕ್ಷಣಗಳು (newdecl)) != ಖಾಲಿ;
	  ತಾರ್ಕಿಕ olda = lookup_attribute ("gnu_inline",
					DECL_ಗುಣಲಕ್ಷಣಗಳು (olddecl)) != ಖಾಲಿ;
	  ಆದರೆ (newa != olda)
	    {
	      auto_diagnostic_ಗುಂಪು d;
	      error_at (ಒಳಹರಿವು_location, "%<gnu_inline%> attribute present on %q+D",
			newa ? newdecl : olddecl);
	      error_at (DECL_ಮೂಲ_LOCATION (newa ? olddecl : newdecl),
			"but not here");
	    }
	}
      /* Check if these are unmergeable overlapping FMV declarations.  */
      ಆದರೆ (!ಗುರಿ_HAS_FMV_ಗುರಿ_ATTRIBUTE
	  && diagnose_versioned_decls (olddecl, newdecl))
	ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
    }
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (VAR_P (newdecl))
    {
      /* Only variables can be thread-local, and all declarations must
	 agree on this property.  */
      ಆದರೆ (C_DECL_THREADPRIVATE_P (olddecl) && !DECL_THREAD_LOCAL_P (newdecl))
	{
	  /* Nothing to check.  Since OLDDECL is marked threadprivate
	     and NEWDECL does not have a thread-local attribute, we
	     will merge the threadprivate attribute into NEWDECL.  */
	  ;
	}
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (DECL_THREAD_LOCAL_P (newdecl) != DECL_THREAD_LOCAL_P (olddecl))
	{
	  auto_diagnostic_ಗುಂಪು d;
	  ಆದರೆ (DECL_THREAD_LOCAL_P (newdecl))
	    error ("thread-local declaration of %q+D follows "
		   "non-thread-local declaration", newdecl);
	  ಇಲ್ಲದಿದ್ದರೆ
	    error ("non-thread-local declaration of %q+D follows "
		   "thread-local declaration", newdecl);

	  locate_old_decl (olddecl);
	  ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
	}

      /* Multiple initialized definitions are not allowed (6.9p3,5).
	 For this purpose, C23 makes it clear that thread-local
	 declarations without extern are definitions, not tentative
	 definitions, whether or not they have initializers.  The
	 wording before C23 was unclear; literally it would have made
	 uninitialized thread-local declarations into tentative
	 definitions only if they also used static, but without saying
	 explicitly whether or not other cases count as
	 definitions at all.  */
      ಆದರೆ ((DECL_INITIAL (newdecl) && DECL_INITIAL (olddecl))
	  || (flag_isoc23
	      && DECL_THREAD_LOCAL_P (newdecl)
	      && !DECL_EXTERNAL (newdecl)
	      && !DECL_EXTERNAL (olddecl)))
	{
	  auto_diagnostic_ಗುಂಪು d;
	  error ("redefinition of %q+D", newdecl);
	  locate_old_decl (olddecl);
	  ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
	}

      /* Objects declared at file scope: if the first declaration had
	 external linkage (even if it was an external reference) the
	 second must have external linkage as well, or the behavior is
	 undefined.  If the first declaration had internal linkage, then
	 the second must too, or else be an external reference (in which
	 case the composite declaration still has internal linkage).
	 As for function declarations, we warn about the static-then-
	 extern case only for -Wtraditional.  See generally 6.2.2p3-5,7.  */
      ಆದರೆ (DECL_FILE_SCOPE_P (newdecl)
	  && ವೃಕ್ಷ_ಬಹಿರಂಗ (newdecl) != ವೃಕ್ಷ_ಬಹಿರಂಗ (olddecl))
	{
	  ಆದರೆ (DECL_EXTERNAL (newdecl))
	    {
	      ಆದರೆ (!DECL_FILE_SCOPE_P (olddecl))
		{
		  auto_diagnostic_ಗುಂಪು d;
		  error ("extern declaration of %q+D follows "
			 "declaration with no linkage", newdecl);
		  locate_old_decl (olddecl);
		  ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
		}
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (warn_traditional)
		{
		  warned |= warning (OPT_Wtraditional,
				     "non-static declaration of %q+D "
				     "follows static declaration", newdecl);
		}
	    }
	  ಇಲ್ಲದಿದ್ದರೆ
	    {
	      auto_diagnostic_ಗುಂಪು d;
	      ಆದರೆ (ವೃಕ್ಷ_ಬಹಿರಂಗ (newdecl))
		error ("non-static declaration of %q+D follows "
		       "static declaration", newdecl);
	      ಇಲ್ಲದಿದ್ದರೆ
		error ("static declaration of %q+D follows "
		       "non-static declaration", newdecl);

	      locate_old_decl (olddecl);
	      ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
	    }
	}
      /* Two objects with the same name declared at the same block
	 scope must both be external references (6.7p3).  */
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!DECL_FILE_SCOPE_P (newdecl))
	{
	  ಆದರೆ (DECL_EXTERNAL (newdecl))
	    {
	      /* Extern with initializer at block scope, which will
		 already have received an error.  */
	    }
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (DECL_EXTERNAL (olddecl))
	    {
	      auto_diagnostic_ಗುಂಪು d;
	      error ("declaration of %q+D with no linkage follows "
		     "extern declaration", newdecl);
	      locate_old_decl (olddecl);
	    }
	  ಇಲ್ಲದಿದ್ದರೆ
	    {
	      auto_diagnostic_ಗುಂಪು d;
	      error ("redeclaration of %q+D with no linkage", newdecl);
	      locate_old_decl (olddecl);
	    }

	  ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
	}

      /* C++ does not permit a decl to appear multiple times at file
	 scope.  */
      ಆದರೆ (warn_cxx_compat
	  && DECL_FILE_SCOPE_P (newdecl)
	  && !DECL_EXTERNAL (newdecl)
	  && !DECL_EXTERNAL (olddecl))
	warned |= warning_at (DECL_ಮೂಲ_LOCATION (newdecl),
			      OPT_Wc___compat,
			      "duplicate declaration of %qD is "
			      "invalid in C++", newdecl);
    }

  /* warnings */
  /* All decls must agree on a visibility.  */
  ಆದರೆ (ಸಂಕೇತ_ಒಳಗೊಂಡಿದೆ_STRUCT (ವೃಕ್ಷ_ಸಂಕೇತ (newdecl), TS_DECL_WITH_VIS)
      && DECL_VISIBILITY_SPECIFIED (newdecl) && DECL_VISIBILITY_SPECIFIED (olddecl)
      && DECL_VISIBILITY (newdecl) != DECL_VISIBILITY (olddecl))
    {
      warned |= warning (0, "redeclaration of %q+D with different visibility "
			 "(old visibility preserved)", newdecl);
    }

  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (newdecl) == FUNCTION_DECL)
    warned |= diagnose_mismatched_ಗುಣಲಕ್ಷಣಗಳು (olddecl, newdecl);
  ಇಲ್ಲದಿದ್ದರೆ /* PARM_DECL, VAR_DECL */
    {
      /* Redeclaration of a parameter is a constraint violation (this is
	 not explicitly stated, but follows from C99 6.7p3 [no more than
	 one declaration of the same identifier with no linkage in the
	 same scope, except type tags] and 6.2.2p6 [parameters have no
	 linkage]).  We must check for a forward parameter declaration,
	 indicated by TREE_ASM_WRITTEN on the old declaration - this is
	 an extension, the mandatory diagnostic for which is handled by
	 mark_forward_parm_decls.  */

      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (newdecl) == PARM_DECL
	  && (!ವೃಕ್ಷ_ASM_WRITTEN (olddecl) || ವೃಕ್ಷ_ASM_WRITTEN (newdecl)))
	{
	  auto_diagnostic_ಗುಂಪು d;
	  error ("redefinition of parameter %q+D", newdecl);
	  locate_old_decl (olddecl);
	  ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
	}
    }

  /* Optional warning for completely redundant decls.  */
  ಆದರೆ (!warned && !pedwarned
      && warn_redundant_decls
      /* Don't warn about a function declaration followed by a
	 definition.  */
      && !(ವೃಕ್ಷ_ಸಂಕೇತ (newdecl) == FUNCTION_DECL
	   && DECL_INITIAL (newdecl) && !DECL_INITIAL (olddecl))
      /* Don't warn about redundant redeclarations of builtins.  */
      && !(ವೃಕ್ಷ_ಸಂಕೇತ (newdecl) == FUNCTION_DECL
	   && !fndecl_built_ಒಳ_p (newdecl)
	   && fndecl_built_ಒಳ_p (olddecl)
	   && !C_DECL_DECLARED_BUILTIN (olddecl))
      /* Don't warn about an extern followed by a definition.  */
      && !(DECL_EXTERNAL (olddecl) && !DECL_EXTERNAL (newdecl))
      /* Don't warn about forward parameter decls.  */
      && !(ವೃಕ್ಷ_ಸಂಕೇತ (newdecl) == PARM_DECL
	   && ವೃಕ್ಷ_ASM_WRITTEN (olddecl) && !ವೃಕ್ಷ_ASM_WRITTEN (newdecl))
      /* Don't warn about a variable definition following a declaration.  */
      && !(VAR_P (newdecl)
	   && DECL_INITIAL (newdecl) && !DECL_INITIAL (olddecl)))
    {
      warned = warning (OPT_Wredundant_decls, "redundant redeclaration of %q+D",
			newdecl);
    }

  /* Report location of previous decl/defn.  */
  ಆದರೆ (warned || pedwarned)
    locate_old_decl (olddecl);

#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು DECL_EXTERN_INLINE

  ಹಿಂತಿರುಗಿ retval;
}

/* Subroutine of duplicate_decls.  NEWDECL has been found to be
   consistent with OLDDECL, but carries new information.  Merge the
   new information into OLDDECL.  This function issues no
   diagnostics.  */

ಸ್ಥಿರ ಶೂನ್ಯ
ವಿಲೀನ_decls (ವೃಕ್ಷ newdecl, ವೃಕ್ಷ olddecl, ವೃಕ್ಷ newtype, ವೃಕ್ಷ oldtype)
{
  ತಾರ್ಕಿಕ new_is_definition = (ವೃಕ್ಷ_ಸಂಕೇತ (newdecl) == FUNCTION_DECL
			    && DECL_INITIAL (newdecl) != NULL_ವೃಕ್ಷ);
  ತಾರ್ಕಿಕ new_is_prototype = (ವೃಕ್ಷ_ಸಂಕೇತ (newdecl) == FUNCTION_DECL
			   && prototype_p (ವೃಕ್ಷ_TYPE (newdecl)));
  ತಾರ್ಕಿಕ old_is_prototype = (ವೃಕ್ಷ_ಸಂಕೇತ (olddecl) == FUNCTION_DECL
			   && prototype_p (ವೃಕ್ಷ_TYPE (olddecl)));

  /* For real parm decl following a forward decl, rechain the old decl
     in its new location and clear TREE_ASM_WRITTEN (it's not a
     forward decl anymore).  */
  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (newdecl) == PARM_DECL
      && ವೃಕ್ಷ_ASM_WRITTEN (olddecl) && !ವೃಕ್ಷ_ASM_WRITTEN (newdecl))
    {
      ರಚನೆ c_binding *b, **ಇಲ್ಲಿ;

      ಗಾಗಿ (ಇಲ್ಲಿ = &current_scope->bindings; *ಇಲ್ಲಿ; ಇಲ್ಲಿ = &(*ಇಲ್ಲಿ)->prev)
	ಆದರೆ ((*ಇಲ್ಲಿ)->decl == olddecl)
	  ಹೋಗು ಸಿಕ್ಕಿತು;
      gcc_unreachable ();

    ಸಿಕ್ಕಿತು:
      b = *ಇಲ್ಲಿ;
      *ಇಲ್ಲಿ = b->prev;
      b->prev = current_scope->bindings;
      current_scope->bindings = b;

      ವೃಕ್ಷ_ASM_WRITTEN (olddecl) = 0;
    }

  DECL_ಗುಣಲಕ್ಷಣಗಳು (newdecl)
    = targetm.ವಿಲೀನ_decl_ಗುಣಲಕ್ಷಣಗಳು (olddecl, newdecl);

  /* For typedefs use the old type, as the new type's DECL_NAME points
     at newdecl, which will be ggc_freed.  */
  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (newdecl) == TYPE_DECL)
    {
      /* But NEWTYPE might have an attribute, honor that.  */
      ವೃಕ್ಷ tem = newtype;
      newtype = oldtype;

      ಆದರೆ (TYPE_USER_ALIGN (tem))
	{
	  ಆದರೆ (TYPE_ALIGN (tem) > TYPE_ALIGN (newtype))
	    ಗಣ_TYPE_ALIGN (newtype, TYPE_ALIGN (tem));
	  TYPE_USER_ALIGN (newtype) = ನಿಜ;
	}

      /* And remove the new type from the variants list.  */
      ಆದರೆ (TYPE_NAME (ವೃಕ್ಷ_TYPE (newdecl)) == newdecl)
	{
	  ವೃಕ್ಷ remove = ವೃಕ್ಷ_TYPE (newdecl);
	  ಆದರೆ (TYPE_MAIN_VARIANT (remove) == remove)
	    {
	      gcc_assert (TYPE_ಮುಂದಿನ_VARIANT (remove) == NULL_ವೃಕ್ಷ);
	      /* If remove is the main variant, no need to remove that
		 from the list.  One of the DECL_ORIGINAL_TYPE
		 variants, e.g. created for aligned attribute, might still
		 refer to the newdecl TYPE_DECL though, so remove that one
		 in that case.  */
	      ಆದರೆ (DECL_ORIGINAL_TYPE (newdecl)
		  && DECL_ORIGINAL_TYPE (newdecl) != remove)
		ಗಾಗಿ (ವೃಕ್ಷ t = TYPE_MAIN_VARIANT (DECL_ORIGINAL_TYPE (newdecl));
		     t; t = TYPE_MAIN_VARIANT (t))
		  ಆದರೆ (TYPE_NAME (TYPE_ಮುಂದಿನ_VARIANT (t)) == newdecl)
		    {
		      TYPE_ಮುಂದಿನ_VARIANT (t)
			= TYPE_ಮುಂದಿನ_VARIANT (TYPE_ಮುಂದಿನ_VARIANT (t));
		      ನಿಲ್ಲಿಸು;
		    }
	    }
	  ಇಲ್ಲದಿದ್ದರೆ
	    ಗಾಗಿ (ವೃಕ್ಷ t = TYPE_MAIN_VARIANT (remove); ;
		 t = TYPE_ಮುಂದಿನ_VARIANT (t))
	      ಆದರೆ (TYPE_ಮುಂದಿನ_VARIANT (t) == remove)
		{
		  TYPE_ಮುಂದಿನ_VARIANT (t) = TYPE_ಮುಂದಿನ_VARIANT (remove);
		  ನಿಲ್ಲಿಸು;
		}
	}

      /* Make sure we refer to the same type as the olddecl.  */
      DECL_ORIGINAL_TYPE (newdecl) = DECL_ORIGINAL_TYPE (olddecl);
    }

  /* Merge the data types specified in the two decls.  */
  ವೃಕ್ಷ_TYPE (newdecl)
    = ವೃಕ್ಷ_TYPE (olddecl)
    = ಸಂಯುಕ್ತ_type (newtype, oldtype);

  /* Lay the type out, unless already done.  */
  ಆದರೆ (!comptypes (oldtype, ವೃಕ್ಷ_TYPE (newdecl)))
    {
      ಆದರೆ (ವೃಕ್ಷ_TYPE (newdecl) != error_mark_ಗಂಟು)
	layout_type (ವೃಕ್ಷ_TYPE (newdecl));
      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (newdecl) != FUNCTION_DECL
	  && ವೃಕ್ಷ_ಸಂಕೇತ (newdecl) != TYPE_DECL
	  && ವೃಕ್ಷ_ಸಂಕೇತ (newdecl) != CONST_DECL)
	layout_decl (newdecl, 0);
    }
  ಇಲ್ಲದಿದ್ದರೆ
    {
      /* Since the type is OLDDECL's, make OLDDECL's size go with.  */
      DECL_ಗಾತ್ರ (newdecl) = DECL_ಗಾತ್ರ (olddecl);
      DECL_ಗಾತ್ರ_UNIT (newdecl) = DECL_ಗಾತ್ರ_UNIT (olddecl);
      ಗಣ_DECL_ಬಹುಲಕ (newdecl, DECL_ಬಹುಲಕ (olddecl));
      ಆದರೆ (DECL_ALIGN (olddecl) > DECL_ALIGN (newdecl))
	{
	  ಗಣ_DECL_ALIGN (newdecl, DECL_ALIGN (olddecl));
	  DECL_USER_ALIGN (newdecl) |= DECL_USER_ALIGN (olddecl);
	}
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (DECL_ALIGN (olddecl) == DECL_ALIGN (newdecl)
	       && DECL_USER_ALIGN (olddecl) != DECL_USER_ALIGN (newdecl))
	DECL_USER_ALIGN (newdecl) = 1;
      ಆದರೆ (DECL_WARN_IF_NOT_ALIGN (olddecl)
	  > DECL_WARN_IF_NOT_ALIGN (newdecl))
	ಗಣ_DECL_WARN_IF_NOT_ALIGN (newdecl,
				    DECL_WARN_IF_NOT_ALIGN (olddecl));
    }

  /* Keep the old rtl since we can safely use it.  */
  ಆದರೆ (HAS_RTL_P (olddecl))
    COPY_DECL_RTL (olddecl, newdecl);

  /* Merge the type qualifiers.  */
  ಆದರೆ (ವೃಕ್ಷ_READONLY (newdecl))
    ವೃಕ್ಷ_READONLY (olddecl) = 1;

  ಆದರೆ (ವೃಕ್ಷ_THIS_VOLATILE (newdecl))
    ವೃಕ್ಷ_THIS_VOLATILE (olddecl) = 1;

  /* Merge deprecatedness.  */
  ಆದರೆ (ವೃಕ್ಷ_DEPRECATED (newdecl))
    ವೃಕ್ಷ_DEPRECATED (olddecl) = 1;

  /* Merge unavailability.  */
  ಆದರೆ (ವೃಕ್ಷ_UNAVAILABLE (newdecl))
    ವೃಕ್ಷ_UNAVAILABLE (olddecl) = 1;

  /* If a decl is in a system header and the other isn't, keep the one on the
     system header. Otherwise, keep source location of definition rather than
     declaration and of prototype rather than non-prototype unless that
     prototype is built-in.  */
  ಆದರೆ (HAS_DECL_ASSEMBLER_NAME_P (olddecl)
      && DECL_ಒಳ_SYSTEM_ಶೀರ್ಷಿಕೆ (olddecl)
      && !DECL_ಒಳ_SYSTEM_ಶೀರ್ಷಿಕೆ (newdecl) )
    DECL_ಮೂಲ_LOCATION (newdecl) = DECL_ಮೂಲ_LOCATION (olddecl);
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (HAS_DECL_ASSEMBLER_NAME_P (olddecl)
	   && DECL_ಒಳ_SYSTEM_ಶೀರ್ಷಿಕೆ (newdecl)
	   && !DECL_ಒಳ_SYSTEM_ಶೀರ್ಷಿಕೆ (olddecl))
    DECL_ಮೂಲ_LOCATION (olddecl) = DECL_ಮೂಲ_LOCATION (newdecl);
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ ((DECL_INITIAL (newdecl) == NULL_ವೃಕ್ಷ
	    && DECL_INITIAL (olddecl) != NULL_ವೃಕ್ಷ)
	   || (old_is_prototype && !new_is_prototype
	       && !C_DECL_BUILTIN_PROTOTYPE (olddecl)))
    DECL_ಮೂಲ_LOCATION (newdecl) = DECL_ಮೂಲ_LOCATION (olddecl);

  /* Merge the initialization information.  */
   ಆದರೆ (DECL_INITIAL (newdecl) == NULL_ವೃಕ್ಷ)
    DECL_INITIAL (newdecl) = DECL_INITIAL (olddecl);

  /* Merge 'constexpr' information.  */
  ಆದರೆ (VAR_P (olddecl) && VAR_P (newdecl))
    {
      ಆದರೆ (C_DECL_DECLARED_CONSTEXPR (olddecl))
	C_DECL_DECLARED_CONSTEXPR (newdecl) = 1;
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (C_DECL_DECLARED_CONSTEXPR (newdecl))
	C_DECL_DECLARED_CONSTEXPR (olddecl) = 1;
    }

  /* Merge the threadprivate attribute.  */
  ಆದರೆ (VAR_P (olddecl) && C_DECL_THREADPRIVATE_P (olddecl))
    C_DECL_THREADPRIVATE_P (newdecl) = 1;

  ಆದರೆ (HAS_DECL_ASSEMBLER_NAME_P (olddecl))
    {
      /* Copy the assembler name.
	 Currently, it can only be defined in the prototype.  */
      COPY_DECL_ASSEMBLER_NAME (olddecl, newdecl);

      /* Use visibility of whichever declaration had it specified */
      ಆದರೆ (DECL_VISIBILITY_SPECIFIED (olddecl))
	{
	  DECL_VISIBILITY (newdecl) = DECL_VISIBILITY (olddecl);
	  DECL_VISIBILITY_SPECIFIED (newdecl) = 1;
	}

      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (newdecl) == FUNCTION_DECL)
	{
	  DECL_STATIC_CONSTRUCTOR(newdecl) |= DECL_STATIC_CONSTRUCTOR(olddecl);
	  DECL_STATIC_DESTRUCTOR (newdecl) |= DECL_STATIC_DESTRUCTOR (olddecl);
	  DECL_NO_ಎಲ್ಲೆ_ರಾಶಿ (newdecl) |= DECL_NO_ಎಲ್ಲೆ_ರಾಶಿ (olddecl);
	  DECL_NO_INSTRUMENT_FUNCTION_ನಮೂದು_EXIT (newdecl)
	    |= DECL_NO_INSTRUMENT_FUNCTION_ನಮೂದು_EXIT (olddecl);
	  ವೃಕ್ಷ_THIS_VOLATILE (newdecl) |= ವೃಕ್ಷ_THIS_VOLATILE (olddecl);
	  DECL_IS_MALLOC (newdecl) |= DECL_IS_MALLOC (olddecl);
	  ಆದರೆ (DECL_IS_OPERATOR_NEW_P (olddecl))
	    DECL_ಗಣ_IS_OPERATOR_NEW (newdecl, ನಿಜ);
	  ಆದರೆ (DECL_IS_OPERATOR_DELETE_P (olddecl))
	    DECL_ಗಣ_IS_OPERATOR_DELETE (newdecl, ನಿಜ);
	  ವೃಕ್ಷ_READONLY (newdecl) |= ವೃಕ್ಷ_READONLY (olddecl);
	  DECL_ಶುದ್ಧ_P (newdecl) |= DECL_ಶುದ್ಧ_P (olddecl);
	  DECL_IS_NOVOPS (newdecl) |= DECL_IS_NOVOPS (olddecl);
	}

      /* Merge the storage class information.  */
      ವಿಲೀನ_weak (newdecl, olddecl);

      /* For functions, static overrides non-static.  */
      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (newdecl) == FUNCTION_DECL)
	{
	  ವೃಕ್ಷ_ಬಹಿರಂಗ (newdecl) &= ವೃಕ್ಷ_ಬಹಿರಂಗ (olddecl);
	  /* This is since we don't automatically
	     copy the attributes of NEWDECL into OLDDECL.  */
	  ವೃಕ್ಷ_ಬಹಿರಂಗ (olddecl) = ವೃಕ್ಷ_ಬಹಿರಂಗ (newdecl);
	  /* If this clears `static', clear it in the identifier too.  */
	  ಆದರೆ (!ವೃಕ್ಷ_ಬಹಿರಂಗ (olddecl))
	    ವೃಕ್ಷ_ಬಹಿರಂಗ (DECL_NAME (olddecl)) = 0;
	}
    }

  /* In c99, 'extern' declaration before (or after) 'inline' means this
     function is not DECL_EXTERNAL, unless 'gnu_inline' attribute
     is present.  */
  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (newdecl) == FUNCTION_DECL
      && !flag_gnu89_inline
      && (DECL_DECLARED_INLINE_P (newdecl)
	  || DECL_DECLARED_INLINE_P (olddecl))
      && (!DECL_DECLARED_INLINE_P (newdecl)
	  || !DECL_DECLARED_INLINE_P (olddecl)
	  || !DECL_EXTERNAL (olddecl))
      && DECL_EXTERNAL (newdecl)
      && !lookup_attribute ("gnu_inline", DECL_ಗುಣಲಕ್ಷಣಗಳು (newdecl))
      && !current_function_decl)
    DECL_EXTERNAL (newdecl) = 0;

  /* An inline definition following a static declaration is not
     DECL_EXTERNAL.  */
  ಆದರೆ (new_is_definition
      && (DECL_DECLARED_INLINE_P (newdecl)
	  || DECL_DECLARED_INLINE_P (olddecl))
      && !ವೃಕ್ಷ_ಬಹಿರಂಗ (olddecl))
    DECL_EXTERNAL (newdecl) = 0;

  ಆದರೆ (DECL_EXTERNAL (newdecl))
    {
      ವೃಕ್ಷ_STATIC (newdecl) = ವೃಕ್ಷ_STATIC (olddecl);
      DECL_EXTERNAL (newdecl) = DECL_EXTERNAL (olddecl);

      /* An extern decl does not override previous storage class.  */
      ವೃಕ್ಷ_ಬಹಿರಂಗ (newdecl) = ವೃಕ್ಷ_ಬಹಿರಂಗ (olddecl);
      ಆದರೆ (!DECL_EXTERNAL (newdecl))
	{
	  DECL_CONTEXT (newdecl) = DECL_CONTEXT (olddecl);
	  DECL_COMMON (newdecl) = DECL_COMMON (olddecl);
	}
    }
  ಇಲ್ಲದಿದ್ದರೆ
    {
      ವೃಕ್ಷ_STATIC (olddecl) = ವೃಕ್ಷ_STATIC (newdecl);
      ವೃಕ್ಷ_ಬಹಿರಂಗ (olddecl) = ವೃಕ್ಷ_ಬಹಿರಂಗ (newdecl);
    }

  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (newdecl) == FUNCTION_DECL)
    {
      ಆದರೆ (DECL_FUNCTION_VERSIONED (olddecl)
	  || DECL_FUNCTION_VERSIONED (newdecl))
	{
	  maybe_mark_function_versioned (olddecl);
	  maybe_mark_function_versioned (newdecl);
	}
      /* If we're redefining a function previously defined as extern
	 inline, make sure we emit debug info for the inline before we
	 throw it away, in case it was inlined into a function that
	 hasn't been written out yet.  */
      ಆದರೆ (new_is_definition && DECL_INITIAL (olddecl))
	/* The new defn must not be inline.  */
	DECL_UNINLINABLE (newdecl) = 1;
      ಇಲ್ಲದಿದ್ದರೆ
	{
	  /* If either decl says `inline', this fn is inline, unless
	     its definition was passed already.  */
	  ಆದರೆ (DECL_DECLARED_INLINE_P (newdecl)
	      || DECL_DECLARED_INLINE_P (olddecl))
	    DECL_DECLARED_INLINE_P (newdecl) = 1;

	  DECL_UNINLINABLE (newdecl) = DECL_UNINLINABLE (olddecl)
	    = (DECL_UNINLINABLE (newdecl) || DECL_UNINLINABLE (olddecl));

	  DECL_DISREGARD_INLINE_LIMITS (newdecl)
	    = DECL_DISREGARD_INLINE_LIMITS (olddecl)
	    = (DECL_DISREGARD_INLINE_LIMITS (newdecl)
	       || DECL_DISREGARD_INLINE_LIMITS (olddecl));
	}

      ಆದರೆ (fndecl_built_ಒಳ_p (olddecl))
	{
	  /* If redeclaring a builtin function, it stays built in.
	     But it gets tagged as having been declared.  */
	  copy_decl_built_ಒಳ_function (newdecl, olddecl);
	  C_DECL_DECLARED_BUILTIN (newdecl) = 1;
	  ಆದರೆ (new_is_prototype)
	    {
	      C_DECL_BUILTIN_PROTOTYPE (newdecl) = 0;
	      ಆದರೆ (DECL_BUILT_ಒಳ_CLASS (newdecl) == BUILT_ಒಳ_ಸಾಮಾನ್ಯ)
		{
		  ಎಣಿಕೆ built_ಒಳ_function fncode = DECL_FUNCTION_ಸಂಕೇತ (newdecl);
		  ಆಯ್ಕೆ (fncode)
		    {
		      /* If a compatible prototype of these builtin functions
			 is seen, assume the runtime implements it with the
			 expected semantics.  */
		    ಸ್ಥಿತಿ BUILT_ಒಳ_STPCPY:
		      ಆದರೆ (builtin_decl_explicit_p (fncode))
			ಗಣ_builtin_decl_implicit_p (fncode, ನಿಜ);
		      ನಿಲ್ಲಿಸು;
		    ಪೂರ್ವನಿಯೋಜಿತ:
		      ಆದರೆ (builtin_decl_explicit_p (fncode))
			ಗಣ_builtin_decl_declared_p (fncode, ನಿಜ);
		      ನಿಲ್ಲಿಸು;
		    }

		  copy_ಗುಣಲಕ್ಷಣಗಳು_ಗಮ್ಯ_builtin (newdecl);
		}
	    }
	  ಇಲ್ಲದಿದ್ದರೆ
	    C_DECL_BUILTIN_PROTOTYPE (newdecl)
	      = C_DECL_BUILTIN_PROTOTYPE (olddecl);
	}

      /* Preserve function specific target and optimization options */
      ಆದರೆ (DECL_FUNCTION_SPECIFIC_ಗುರಿ (olddecl)
	  && !DECL_FUNCTION_SPECIFIC_ಗುರಿ (newdecl))
	DECL_FUNCTION_SPECIFIC_ಗುರಿ (newdecl)
	  = DECL_FUNCTION_SPECIFIC_ಗುರಿ (olddecl);

      ಆದರೆ (DECL_FUNCTION_SPECIFIC_OPTIMIZATION (olddecl)
	  && !DECL_FUNCTION_SPECIFIC_OPTIMIZATION (newdecl))
	DECL_FUNCTION_SPECIFIC_OPTIMIZATION (newdecl)
	  = DECL_FUNCTION_SPECIFIC_OPTIMIZATION (olddecl);

      /* Also preserve various other info from the definition.  */
      ಆದರೆ (!new_is_definition)
	{
	  ವೃಕ್ಷ t;
	  DECL_ಫಲಿತಾಂಶ (newdecl) = DECL_ಫಲಿತಾಂಶ (olddecl);
	  DECL_INITIAL (newdecl) = DECL_INITIAL (olddecl);
	  DECL_STRUCT_FUNCTION (newdecl) = DECL_STRUCT_FUNCTION (olddecl);
	  DECL_SAVED_ವೃಕ್ಷ (newdecl) = DECL_SAVED_ವೃಕ್ಷ (olddecl);
	  DECL_ARGUMENTS (newdecl) = copy_list (DECL_ARGUMENTS (olddecl));
	  ಗಾಗಿ (t = DECL_ARGUMENTS (newdecl); t ; t = DECL_CHAIN (t))
	    DECL_CONTEXT (t) = newdecl;

	  /* See if we've got a function to instantiate from.  */
	  ಆದರೆ (DECL_SAVED_ವೃಕ್ಷ (olddecl))
	    DECL_ABSTRACT_ORIGIN (newdecl)
	      = DECL_ABSTRACT_ORIGIN (olddecl);
	}
    }

  /* Merge the USED information.  */
  ಆದರೆ (ವೃಕ್ಷ_ಬಳಸಿದ (olddecl))
    ವೃಕ್ಷ_ಬಳಸಿದ (newdecl) = 1;
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ವೃಕ್ಷ_ಬಳಸಿದ (newdecl))
    ವೃಕ್ಷ_ಬಳಸಿದ (olddecl) = 1;
  ಆದರೆ (VAR_P (olddecl) || ವೃಕ್ಷ_ಸಂಕೇತ (olddecl) == PARM_DECL)
    DECL_READ_P (newdecl) |= DECL_READ_P (olddecl);
  ಆದರೆ (DECL_PRESERVE_P (olddecl))
    DECL_PRESERVE_P (newdecl) = 1;
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (DECL_PRESERVE_P (newdecl))
    DECL_PRESERVE_P (olddecl) = 1;

  /* Merge DECL_COMMON */
  ಆದರೆ (VAR_P (olddecl) && VAR_P (newdecl)
      && !lookup_attribute ("common", DECL_ಗುಣಲಕ್ಷಣಗಳು (newdecl))
      && !lookup_attribute ("nocommon", DECL_ಗುಣಲಕ್ಷಣಗಳು (newdecl)))
    DECL_COMMON (newdecl) = DECL_COMMON (newdecl) && DECL_COMMON (olddecl);

  /* Copy most of the decl-specific fields of NEWDECL into OLDDECL.
     But preserve OLDDECL's DECL_UID, DECL_CONTEXT and
     DECL_ARGUMENTS (if appropriate).  */
  {
    ಚಿಹ್ನೆರಹಿತ olddecl_uid = DECL_UID (olddecl);
    ವೃಕ್ಷ olddecl_context = DECL_CONTEXT (olddecl);
    ವೃಕ್ಷ olddecl_arguments = ಖಾಲಿ;
    ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (olddecl) == FUNCTION_DECL)
      olddecl_arguments = DECL_ARGUMENTS (olddecl);

    ಸ್ಮರಣೆ_ನಕಲು ((ಅಕ್ಷರ *) olddecl + ಗಾತ್ರ (ರಚನೆ ವೃಕ್ಷ_common),
	    (ಅಕ್ಷರ *) newdecl + ಗಾತ್ರ (ರಚನೆ ವೃಕ್ಷ_common),
	    ಗಾತ್ರ (ರಚನೆ ವೃಕ್ಷ_decl_common) - ಗಾತ್ರ (ರಚನೆ ವೃಕ್ಷ_common));
    DECL_USER_ALIGN (olddecl) = DECL_USER_ALIGN (newdecl);
    ಆಯ್ಕೆ (ವೃಕ್ಷ_ಸಂಕೇತ (olddecl))
      {
      ಸ್ಥಿತಿ FUNCTION_DECL:
      ಸ್ಥಿತಿ VAR_DECL:
	{
	  ರಚನೆ symtab_ಗಂಟು *snode = olddecl->decl_with_vis.symtab_ಗಂಟು;

	  ಸ್ಮರಣೆ_ನಕಲು ((ಅಕ್ಷರ *) olddecl + ಗಾತ್ರ (ರಚನೆ ವೃಕ್ಷ_decl_common),
		  (ಅಕ್ಷರ *) newdecl + ಗಾತ್ರ (ರಚನೆ ವೃಕ್ಷ_decl_common),
		  ವೃಕ್ಷ_ಸಂಕೇತ_ಗಾತ್ರ (ವೃಕ್ಷ_ಸಂಕೇತ (olddecl)) - ಗಾತ್ರ (ರಚನೆ ವೃಕ್ಷ_decl_common));
	  olddecl->decl_with_vis.symtab_ಗಂಟು = snode;

	  ಆದರೆ ((DECL_EXTERNAL (olddecl)
	       || ವೃಕ್ಷ_ಬಹಿರಂಗ (olddecl)
	       || ವೃಕ್ಷ_STATIC (olddecl))
	      && DECL_SECTION_NAME (newdecl) != ಖಾಲಿ)
	    ಗಣ_decl_section_name (olddecl, newdecl);

	  /* This isn't quite correct for something like
		int __thread x attribute ((tls_model ("local-exec")));
		extern int __thread x;
	     as we'll lose the "local-exec" model.  */
	  ಆದರೆ (VAR_P (olddecl) && DECL_THREAD_LOCAL_P (newdecl))
	    ಗಣ_decl_tls_model (olddecl, DECL_TLS_MODEL (newdecl));
	  ನಿಲ್ಲಿಸು;
	}

      ಸ್ಥಿತಿ ಕ್ಷೇತ್ರ_DECL:
      ಸ್ಥಿತಿ PARM_DECL:
      ಸ್ಥಿತಿ LABEL_DECL:
      ಸ್ಥಿತಿ ಫಲಿತಾಂಶ_DECL:
      ಸ್ಥಿತಿ CONST_DECL:
      ಸ್ಥಿತಿ TYPE_DECL:
	ಸ್ಮರಣೆ_ನಕಲು ((ಅಕ್ಷರ *) olddecl + ಗಾತ್ರ (ರಚನೆ ವೃಕ್ಷ_decl_common),
		(ಅಕ್ಷರ *) newdecl + ಗಾತ್ರ (ರಚನೆ ವೃಕ್ಷ_decl_common),
		ವೃಕ್ಷ_ಸಂಕೇತ_ಗಾತ್ರ (ವೃಕ್ಷ_ಸಂಕೇತ (olddecl)) - ಗಾತ್ರ (ರಚನೆ ವೃಕ್ಷ_decl_common));
	ನಿಲ್ಲಿಸು;

      ಪೂರ್ವನಿಯೋಜಿತ:

	ಸ್ಮರಣೆ_ನಕಲು ((ಅಕ್ಷರ *) olddecl + ಗಾತ್ರ (ರಚನೆ ವೃಕ್ಷ_decl_common),
		(ಅಕ್ಷರ *) newdecl + ಗಾತ್ರ (ರಚನೆ ವೃಕ್ಷ_decl_common),
		ಗಾತ್ರ (ರಚನೆ ವೃಕ್ಷ_decl_non_common) - ಗಾತ್ರ (ರಚನೆ ವೃಕ್ಷ_decl_common));
      }
    DECL_UID (olddecl) = olddecl_uid;
    DECL_CONTEXT (olddecl) = olddecl_context;
    ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (olddecl) == FUNCTION_DECL)
      DECL_ARGUMENTS (olddecl) = olddecl_arguments;
  }

  /* If OLDDECL had its DECL_RTL instantiated, re-invoke make_decl_rtl
     so that encode_section_info has a chance to look at the new decl
     flags and attributes.  */
  ಆದರೆ (DECL_RTL_ಗಣ_P (olddecl)
      && (ವೃಕ್ಷ_ಸಂಕೇತ (olddecl) == FUNCTION_DECL
	  || (VAR_P (olddecl) && ವೃಕ್ಷ_STATIC (olddecl))))
    make_decl_rtl (olddecl);
}

/* Handle when a new declaration NEWDECL has the same name as an old
   one OLDDECL in the same binding contour.  Prints an error message
   if appropriate.

   If safely possible, alter OLDDECL to look like NEWDECL, and return
   true.  Otherwise, return false.  */

ಸ್ಥಿರ ತಾರ್ಕಿಕ
duplicate_decls (ವೃಕ್ಷ newdecl, ವೃಕ್ಷ olddecl)
{
  ವೃಕ್ಷ newtype = ಖಾಲಿ, oldtype = ಖಾಲಿ;

  ಆದರೆ (!diagnose_mismatched_decls (newdecl, olddecl, &newtype, &oldtype))
    {
      /* Avoid `unused variable' and other warnings for OLDDECL.  */
      suppress_warning (olddecl, OPT_Wunused);
      /* If the types are completely different, poison them both with
 	 error_mark_node.  */
      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (newdecl)) != ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (olddecl))
	  && olddecl != error_mark_ಗಂಟು
	  && ನೋಡಿದ_error ())
	{
	  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (olddecl) != FUNCTION_DECL)
	    ವೃಕ್ಷ_TYPE (olddecl) = error_mark_ಗಂಟು;
	  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (newdecl) != FUNCTION_DECL)
	    ವೃಕ್ಷ_TYPE (newdecl) = error_mark_ಗಂಟು;
	}
      ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
    }

  ವಿಲೀನ_decls (newdecl, olddecl, newtype, oldtype);

  /* The NEWDECL will no longer be needed.

     Before releasing the node, be sure to remove function from symbol
     table that might have been inserted there to record comdat group.
     Be sure to however do not free DECL_STRUCT_FUNCTION because this
     structure is shared in between NEWDECL and OLDECL.  */
  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (newdecl) == FUNCTION_DECL)
    DECL_STRUCT_FUNCTION (newdecl) = ಖಾಲಿ;
  ಆದರೆ (VAR_OR_FUNCTION_DECL_P (newdecl))
    {
      ರಚನೆ symtab_ಗಂಟು *snode = symtab_ಗಂಟು::get (newdecl);
      ಆದರೆ (snode)
	snode->remove ();
    }
  ggc_free (newdecl);
  ಹಿಂತಿರುಗಿ ನಿಜ;
}


/* Check whether decl-node NEW_DECL shadows an existing declaration.  */
ಸ್ಥಿರ ಶೂನ್ಯ
warn_if_shadowing (ವೃಕ್ಷ new_decl)
{
  ರಚನೆ c_binding *b;

  /* Shadow warnings wanted?  */
  ಆದರೆ (!(warn_shadow
        || warn_shadow_local
        || warn_shadow_compatible_local)
      /* No shadow warnings for internally generated vars.  */
      || DECL_IS_UNDECLARED_BUILTIN (new_decl))
    ಹಿಂತಿರುಗಿ;

  /* Is anything being shadowed?  Invisible decls do not count.  */
  ಗಾಗಿ (b = I_ಚಿಹ್ನೆ_BINDING (DECL_NAME (new_decl)); b; b = b->shadowed)
    ಆದರೆ (b->decl && b->decl != new_decl && !b->invisible
	&& (b->decl == error_mark_ಗಂಟು
	    || diagnostic_report_warnings_p (global_dc,
					     DECL_ಮೂಲ_LOCATION (b->decl))))
      {
	ವೃಕ್ಷ old_decl = b->decl;

	ಆದರೆ (old_decl == error_mark_ಗಂಟು)
	  {
	    warning (OPT_Wshadow, "declaration of %q+D shadows previous "
		     "non-variable", new_decl);
	    ನಿಲ್ಲಿಸು;
	  }

	ತಾರ್ಕಿಕ warned = ಸುಳ್ಳು;
	auto_diagnostic_ಗುಂಪು d;
	ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (old_decl) == PARM_DECL)
	  {
	    ಎಣಿಕೆ opt_ಸಂಕೇತ warning_ಸಂಕೇತ;

	    /* If '-Wshadow=compatible-local' is specified without other
	       -Wshadow= flags, we will warn only when the types of the
	       shadowing variable (i.e. new_decl) and the shadowed variable
	       (old_decl) are compatible.  */
	    ಆದರೆ (warn_shadow)
	      warning_ಸಂಕೇತ = OPT_Wshadow;
	    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (comptypes (ವೃಕ್ಷ_TYPE (old_decl), ವೃಕ್ಷ_TYPE (new_decl)))
	      warning_ಸಂಕೇತ = OPT_Wshadow_compatible_local;
	    ಇಲ್ಲದಿದ್ದರೆ
	      warning_ಸಂಕೇತ = OPT_Wshadow_local;
	    warned = warning_at (DECL_ಮೂಲ_LOCATION (new_decl), warning_ಸಂಕೇತ,
				 "declaration of %qD shadows a parameter",
				 new_decl);
	  }
	ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (DECL_FILE_SCOPE_P (old_decl))
	  {
	    /* Do not warn if a variable shadows a function, unless
	       the variable is a function or a pointer-to-function.  */
	    ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (old_decl) == FUNCTION_DECL
		&& ವೃಕ್ಷ_ಸಂಕೇತ (new_decl) != FUNCTION_DECL
		&& !FUNCTION_ಸೂಚಕ_TYPE_P (ವೃಕ್ಷ_TYPE (new_decl)))
		ಮುಂದುವರಿ;

	    warned = warning_at (DECL_ಮೂಲ_LOCATION (new_decl), OPT_Wshadow,
				 "declaration of %qD shadows a global "
				 "declaration",
				 new_decl);
	  }
	ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (old_decl) == FUNCTION_DECL
		 && fndecl_built_ಒಳ_p (old_decl))
	  {
	    warning (OPT_Wshadow, "declaration of %q+D shadows "
		     "a built-in function", new_decl);
	    ನಿಲ್ಲಿಸು;
	  }
	ಇಲ್ಲದಿದ್ದರೆ
	  {
	    ಎಣಿಕೆ opt_ಸಂಕೇತ warning_ಸಂಕೇತ;

	    /* If '-Wshadow=compatible-local' is specified without other
	       -Wshadow= flags, we will warn only when the types of the
	       shadowing variable (i.e. new_decl) and the shadowed variable
	       (old_decl) are compatible.  */
	    ಆದರೆ (warn_shadow)
	      warning_ಸಂಕೇತ = OPT_Wshadow;
	    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (comptypes (ವೃಕ್ಷ_TYPE (old_decl), ವೃಕ್ಷ_TYPE (new_decl)))
	      warning_ಸಂಕೇತ = OPT_Wshadow_compatible_local;
	    ಇಲ್ಲದಿದ್ದರೆ
	      warning_ಸಂಕೇತ = OPT_Wshadow_local;
	    warned = warning_at (DECL_ಮೂಲ_LOCATION (new_decl), warning_ಸಂಕೇತ,
				 "declaration of %qD shadows a previous local",
				 new_decl);
	  }

	ಆದರೆ (warned)
	  inform (DECL_ಮೂಲ_LOCATION (old_decl),
		  "shadowed declaration is here");

	ನಿಲ್ಲಿಸು;
      }
}

/* Record a decl-node X as belonging to the current lexical scope.
   Check for errors (such as an incompatible declaration for the same
   name already seen in the same scope).

   Returns either X or an old decl for the same name.
   If an old decl is returned, it may have been smashed
   to agree with what X says.  */

ವೃಕ್ಷ
pushdecl (ವೃಕ್ಷ x)
{
  ವೃಕ್ಷ name = DECL_NAME (x);
  ರಚನೆ c_scope *scope = current_scope;
  ರಚನೆ c_binding *b;
  ತಾರ್ಕಿಕ nested = ಸುಳ್ಳು;
  location_t locus = DECL_ಮೂಲ_LOCATION (x);

  /* Must set DECL_CONTEXT for everything not at file scope or
     DECL_FILE_SCOPE_P won't work.  Local externs don't count
     unless they have initializers (which generate code).  We
     also exclude CONST_DECLs because enumerators will get the
     type of the enum as context.  */
  ಆದರೆ (current_function_decl
      && ವೃಕ್ಷ_ಸಂಕೇತ (x) != CONST_DECL
      && (!VAR_OR_FUNCTION_DECL_P (x)
	  || DECL_INITIAL (x) || !ವೃಕ್ಷ_ಬಹಿರಂಗ (x)))
    DECL_CONTEXT (x) = current_function_decl;

  /* Anonymous decls are just inserted in the scope.  */
  ಆದರೆ (!name)
    {
      bind (name, x, scope, /*invisible=*/ಸುಳ್ಳು, /*nested=*/ಸುಳ್ಳು,
	    locus);
      ಹಿಂತಿರುಗಿ x;
    }

  /* First, see if there is another declaration with the same name in
     the current scope.  If there is, duplicate_decls may do all the
     work for us.  If duplicate_decls returns false, that indicates
     two incompatible decls in the same scope; we are to silently
     replace the old one (duplicate_decls has issued all appropriate
     diagnostics).  In particular, we should not consider possible
     duplicates in the external scope, or shadowing.  */
  b = I_ಚಿಹ್ನೆ_BINDING (name);
  ಆದರೆ (b && B_ಒಳ_SCOPE (b, scope))
    {
      ರಚನೆ c_binding *b_ext, *b_use;
      ವೃಕ್ಷ type = ವೃಕ್ಷ_TYPE (x);
      ವೃಕ್ಷ visdecl = b->decl;
      ವೃಕ್ಷ vistype = ವೃಕ್ಷ_TYPE (visdecl);
      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (x)) == ARRAY_TYPE
	  && COMPLETE_TYPE_P (ವೃಕ್ಷ_TYPE (x)))
	b->inner_comp = ಸುಳ್ಳು;
      b_use = b;
      b_ext = b;
      /* If this is an external linkage declaration, we should check
	 for compatibility with the type in the external scope before
	 setting the type at this scope based on the visible
	 information only.  */
      ಆದರೆ (ವೃಕ್ಷ_ಬಹಿರಂಗ (x) && ವೃಕ್ಷ_ಬಹಿರಂಗ (visdecl))
	{
	  ಆಗ (b_ext && !B_ಒಳ_EXTERNAL_SCOPE (b_ext))
	    b_ext = b_ext->shadowed;
	  ಆದರೆ (b_ext)
	    {
	      b_use = b_ext;
	      ಆದರೆ (b_use->u.type)
		ವೃಕ್ಷ_TYPE (b_use->decl) = b_use->u.type;
	    }
	}

      /* Check if x is part of a FMV set with b_use.
	 FMV is only supported in c for targets with target_version
	 attributes.  */
      ಆದರೆ (!ಗುರಿ_HAS_FMV_ಗುರಿ_ATTRIBUTE
	  && b_use && ವೃಕ್ಷ_ಸಂಕೇತ (b_use->decl) == FUNCTION_DECL
	  && ವೃಕ್ಷ_ಸಂಕೇತ (x) == FUNCTION_DECL && DECL_FILE_SCOPE_P (b_use->decl)
	  && DECL_FILE_SCOPE_P (x)
	  && disjoint_ಆವೃತ್ತಿ_decls (x, b_use->decl)
	  && comptypes (vistype, type))
	{
	  maybe_mark_function_versioned (b_use->decl);
	  maybe_mark_function_versioned (b->decl);
	  maybe_mark_function_versioned (x);

	  cgraph_ಗಂಟು *b_ಗಂಟು = cgraph_ಗಂಟು::get_create (b_use->decl);
	  cgraph_function_ಆವೃತ್ತಿ_info *b_v = b_ಗಂಟು->function_ಆವೃತ್ತಿ ();
	  ಆದರೆ (!b_v)
	    b_v = b_ಗಂಟು->ಸೇರಿಸು_new_function_ಆವೃತ್ತಿ ();

	  /* Check if this new node conflicts with any previous functions
	     in the set.  */
	  cgraph_function_ಆವೃತ್ತಿ_info *ಆವೃತ್ತಿ = b_v;
	  ಗಾಗಿ (; ಆವೃತ್ತಿ; ಆವೃತ್ತಿ = ಆವೃತ್ತಿ->ಮುಂದಿನ)
	    ಆದರೆ (!disjoint_ಆವೃತ್ತಿ_decls (ಆವೃತ್ತಿ->this_ಗಂಟು->decl, x))
	      {
		/* The decls define overlapping version, so attempt to merge
		   or diagnose the conflict.  */
		ಆದರೆ (duplicate_decls (x, ಆವೃತ್ತಿ->this_ಗಂಟು->decl))
		  ಹಿಂತಿರುಗಿ ಆವೃತ್ತಿ->this_ಗಂಟು->decl;
		ಇಲ್ಲದಿದ್ದರೆ
		  ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
	      }

	  /* This is a new version to be added to FMV structure.  */
	  cgraph_ಗಂಟು::ಕೂಡಿಸು_function_ಆವೃತ್ತಿ (b_v, x);

	  /* Get the first node from the structure.  */
	  cgraph_function_ಆವೃತ್ತಿ_info *default_v = b_v;
	  ಆಗ (default_v->prev)
	    default_v = default_v->prev;
	  /* Always use the default node for the bindings.  */
	  b_use->decl = default_v->this_ಗಂಟು->decl;
	  b->decl = default_v->this_ಗಂಟು->decl;

	  /* Node is not a duplicate, so no need to do the rest of the
	     checks.  */
	  ಹಿಂತಿರುಗಿ x;
	}

      ಆದರೆ (duplicate_decls (x, b_use->decl))
	{
	  ಆದರೆ (b_use != b)
	    {
	      /* Save the updated type in the external scope and
		 restore the proper type for this scope.  */
	      ವೃಕ್ಷ thistype;
	      ಆದರೆ (comptypes (vistype, type))
		thistype = ಸಂಯುಕ್ತ_type (vistype, type);
	      ಇಲ್ಲದಿದ್ದರೆ
		thistype = ವೃಕ್ಷ_TYPE (b_use->decl);
	      b_use->u.type = ವೃಕ್ಷ_TYPE (b_use->decl);
	      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (b_use->decl) == FUNCTION_DECL
		  && fndecl_built_ಒಳ_p (b_use->decl))
		thistype
		  = c_build_type_attribute_variant (thistype,
						    TYPE_ಗುಣಲಕ್ಷಣಗಳು
						    (b_use->u.type));
	      ವೃಕ್ಷ_TYPE (b_use->decl) = thistype;
	    }
	  ಹಿಂತಿರುಗಿ b_use->decl;
	}
      ಇಲ್ಲದಿದ್ದರೆ
	ಹೋಗು skip_external_and_shadow_checks;
    }

  /* All declarations with external linkage, and all external
     references, go in the external scope, no matter what scope is
     current.  However, the binding in that scope is ignored for
     purposes of normal name lookup.  A separate binding structure is
     created in the requested scope; this governs the normal
     visibility of the symbol.

     The binding in the externals scope is used exclusively for
     detecting duplicate declarations of the same object, no matter
     what scope they are in; this is what we do here.  (C99 6.2.7p2:
     All declarations that refer to the same object or function shall
     have compatible type; otherwise, the behavior is undefined.)
     However, in Objective-C, we also want to detect declarations
     conflicting with those of the basic types.  */
  ಆದರೆ ((DECL_EXTERNAL (x) || scope == file_scope)
      && (VAR_OR_FUNCTION_DECL_P (x) || c_dialect_objc ()))
    {
      ವೃಕ್ಷ type = ವೃಕ್ಷ_TYPE (x);
      ವೃಕ್ಷ vistype = NULL_ವೃಕ್ಷ;
      ವೃಕ್ಷ visdecl = NULL_ವೃಕ್ಷ;
      ತಾರ್ಕಿಕ type_saved = ಸುಳ್ಳು;
      ಆದರೆ (b && !B_ಒಳ_EXTERNAL_SCOPE (b)
	  && VAR_OR_FUNCTION_DECL_P (b->decl)
	  && DECL_FILE_SCOPE_P (b->decl))
	{
	  visdecl = b->decl;
	  vistype = ವೃಕ್ಷ_TYPE (visdecl);
	}
      ಆದರೆ (scope != file_scope
	  && !DECL_ಒಳ_SYSTEM_ಶೀರ್ಷಿಕೆ (x))
	warning_at (locus, OPT_Wnested_externs,
		    "nested extern declaration of %qD", x);

      ಆಗ (b && !B_ಒಳ_EXTERNAL_SCOPE (b))
	{
	  /* If this decl might be modified, save its type.  This is
	     done here rather than when the decl is first bound
	     because the type may change after first binding, through
	     being completed or through attributes being added.  If we
	     encounter multiple such decls, only the first should have
	     its type saved; the others will already have had their
	     proper types saved and the types will not have changed as
	     their scopes will not have been re-entered.  */
	  ಆದರೆ (DECL_P (b->decl) && DECL_FILE_SCOPE_P (b->decl) && !type_saved)
	    {
	      b->u.type = ವೃಕ್ಷ_TYPE (b->decl);
	      type_saved = ನಿಜ;
	    }
	  ಆದರೆ (B_ಒಳ_FILE_SCOPE (b)
	      && VAR_P (b->decl)
	      && ವೃಕ್ಷ_STATIC (b->decl)
	      && ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (b->decl)) == ARRAY_TYPE
	      && !TYPE_DOMAIN (ವೃಕ್ಷ_TYPE (b->decl))
	      && ವೃಕ್ಷ_ಸಂಕೇತ (type) == ARRAY_TYPE
	      && TYPE_DOMAIN (type)
	      && TYPE_MAX_ಮೌಲ್ಯ (TYPE_DOMAIN (type))
	      && !integer_zerop (TYPE_MAX_ಮೌಲ್ಯ (TYPE_DOMAIN (type))))
	    {
	      /* Array type completed in inner scope, which should be
		 diagnosed if the completion does not have size 1 and
		 it does not get completed in the file scope.  */
	      b->inner_comp = ನಿಜ;
	    }
	  b = b->shadowed;
	}

      /* If a matching external declaration has been found, set its
	 type to the composite of all the types of that declaration.
	 After the consistency checks, it will be reset to the
	 composite of the visible types only.  */
      ಆದರೆ (b && b->u.type)
	ವೃಕ್ಷ_TYPE (b->decl) = b->u.type;

      /* the static does not go in the externals scope.  */
      ಆದರೆ (b && duplicate_decls (x, b->decl))
	{
	  ವೃಕ್ಷ thistype;
	  ಆದರೆ (vistype)
	    {
	      ಆದರೆ (comptypes (vistype, type))
		thistype = ಸಂಯುಕ್ತ_type (vistype, type);
	      ಇಲ್ಲದಿದ್ದರೆ
		thistype = ವೃಕ್ಷ_TYPE (b->decl);
	    }
	  ಇಲ್ಲದಿದ್ದರೆ
	    thistype = type;
	  b->u.type = ವೃಕ್ಷ_TYPE (b->decl);
	  /* Propagate the type attributes to the decl.  */
	  thistype
	    = c_build_type_attribute_variant (thistype,
					      TYPE_ಗುಣಲಕ್ಷಣಗಳು (b->u.type));
	  ವೃಕ್ಷ_TYPE (b->decl) = thistype;
	  bind (name, b->decl, scope, /*invisible=*/ಸುಳ್ಳು, /*nested=*/ನಿಜ,
		locus);
	  ಹಿಂತಿರುಗಿ b->decl;
	}
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ವೃಕ್ಷ_ಬಹಿರಂಗ (x))
	{
	  ಆದರೆ (visdecl && !b && duplicate_decls (x, visdecl))
	    {
	      /* An external declaration at block scope referring to a
		 visible entity with internal linkage.  The composite
		 type will already be correct for this scope, so we
		 just need to fall through to make the declaration in
		 this scope.  */
	      nested = ನಿಜ;
	      x = visdecl;
	    }
	  ಇಲ್ಲದಿದ್ದರೆ
	    {
	      bind (name, x, external_scope, /*invisible=*/ನಿಜ,
		    /*nested=*/ಸುಳ್ಳು, locus);
	      nested = ನಿಜ;
	    }
	}
    }

  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (x) != PARM_DECL)
    warn_if_shadowing (x);

 skip_external_and_shadow_checks:
  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (x) == TYPE_DECL)
    {
      /* So this is a typedef, set its underlying type.  */
      ಗಣ_underlying_type (x);

      /* If X is a typedef defined in the current function, record it
	 for the purpose of implementing the -Wunused-local-typedefs
	 warning.  */
      ದಾಖಲೆ_locally_defined_typedef (x);
    }

  bind (name, x, scope, /*invisible=*/ಸುಳ್ಳು, nested, locus);

  /* If x's type is incomplete because it's based on a
     structure or union which has not yet been fully declared,
     attach it to that structure or union type, so we can go
     back and complete the variable declaration later, if the
     structure or union gets fully declared.

     If the input is erroneous, we can have error_mark in the type
     slot (e.g. "f(void a, ...)") - that doesn't count as an
     incomplete type.  */
  ಆದರೆ (ವೃಕ್ಷ_TYPE (x) != error_mark_ಗಂಟು
      && !COMPLETE_TYPE_P (ವೃಕ್ಷ_TYPE (x)))
    {
      ವೃಕ್ಷ element = ವೃಕ್ಷ_TYPE (x);

      ಆಗ (ವೃಕ್ಷ_ಸಂಕೇತ (element) == ARRAY_TYPE)
	element = ವೃಕ್ಷ_TYPE (element);
      element = TYPE_MAIN_VARIANT (element);

      ಆದರೆ ((ದಾಖಲೆ_OR_UNION_TYPE_P (element)
	   || ವೃಕ್ಷ_ಸಂಕೇತ (element) == ENUMERAL_TYPE)
	  && (ವೃಕ್ಷ_ಸಂಕೇತ (x) != TYPE_DECL
	      || ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (x)) == ARRAY_TYPE)
	  && !COMPLETE_TYPE_P (element))
	C_TYPE_INCOMPLETE_VARS (element)
	  = ವೃಕ್ಷ_cons (NULL_ವೃಕ್ಷ, x, C_TYPE_INCOMPLETE_VARS (element));
    }
  ಹಿಂತಿರುಗಿ x;
}


/* Issue a permerror about implicit function declaration.  ID is the function
   identifier, OLDDECL is a declaration of the function in a different scope,
   or NULL_TREE.  */

ಸ್ಥಿರ ಶೂನ್ಯ
implicit_decl_permerror (location_t loc, ವೃಕ್ಷ id, ವೃಕ್ಷ olddecl)
{
  ಆದರೆ (!warn_implicit_function_declaration)
    ಹಿಂತಿರುಗಿ;

  ತಾರ್ಕಿಕ warned;
  auto_diagnostic_ಗುಂಪು d;
  name_hint hint;
  ಆದರೆ (!olddecl)
    hint = lookup_name_fuzzy (id, FUZZY_LOOKUP_FUNCTION_NAME, loc);

  ಆದರೆ (flag_isoc99)
    {
      ಆದರೆ (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *suggestion = hint.suggestion ())
	{
	  gcc_rich_location richloc (loc);
	  richloc.ಕೂಡಿಸು_fixit_replace (suggestion);
	  warned = permerror_opt (&richloc, OPT_Wimplicit_function_declaration,
				  "implicit declaration of function %qE;"
				  " did you mean %qs?",
				  id, suggestion);
	}
      ಇಲ್ಲದಿದ್ದರೆ
	warned = permerror_opt (loc, OPT_Wimplicit_function_declaration,
				"implicit declaration of function %qE", id);
    }
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *suggestion = hint.suggestion ())
    {
      gcc_rich_location richloc (loc);
      richloc.ಕೂಡಿಸು_fixit_replace (suggestion);
      warned = warning_at
	(&richloc, OPT_Wimplicit_function_declaration,
	 G_("implicit declaration of function %qE; did you mean %qs?"),
	 id, suggestion);
    }
  ಇಲ್ಲದಿದ್ದರೆ
    warned = warning_at (loc, OPT_Wimplicit_function_declaration,
			 G_("implicit declaration of function %qE"), id);

  ಆದರೆ (warned)
    {
      /* Whether the olddecl is an undeclared builtin function.
	 locate_old_decl will not generate a diagnostic for those,
	 so in that case we want to look elsewhere.  */
      ತಾರ್ಕಿಕ undeclared_builtin = (olddecl
				 && ವೃಕ್ಷ_ಸಂಕೇತ (olddecl) == FUNCTION_DECL
				 && fndecl_built_ಒಳ_p (olddecl)
				 && !C_DECL_DECLARED_BUILTIN (olddecl));
      ಆದರೆ (undeclared_builtin)
	{
	  ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಶೀರ್ಷಿಕೆ = ಶೀರ್ಷಿಕೆ_for_builtin_fn (olddecl);
	  ಆದರೆ (ಶೀರ್ಷಿಕೆ)
	    {
	      rich_location richloc (ಸಾಲು_ಕೋಷ್ಟಕ, loc);
	      maybe_ಕೂಡಿಸು_include_fixit (&richloc, ಶೀರ್ಷಿಕೆ, ನಿಜ);
	      inform (&richloc,
		      "include %qs or provide a declaration of %qE",
		      ಶೀರ್ಷಿಕೆ, id);
	    }
	}
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (olddecl)
	locate_old_decl (olddecl);
    }

  ಆದರೆ (!warned)
    hint.suppress ();
}

/* Return the name of the header file that declares built-in function
   FNDECL, or null if either we don't know or don't expect to see an
   explicit declaration.  */

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *
ಶೀರ್ಷಿಕೆ_for_builtin_fn (ವೃಕ್ಷ fndecl)
{
  ಆದರೆ (DECL_BUILT_ಒಳ_CLASS (fndecl) != BUILT_ಒಳ_ಸಾಮಾನ್ಯ)
    ಹಿಂತಿರುಗಿ ಖಾಲಿ;

  ಆಯ್ಕೆ (DECL_FUNCTION_ಸಂಕೇತ (fndecl))
    {
    CASE_FLT_FN (BUILT_ಒಳ_ACOS):
    CASE_FLT_FN (BUILT_ಒಳ_ACOSH):
    CASE_FLT_FN (BUILT_ಒಳ_ASIN):
    CASE_FLT_FN (BUILT_ಒಳ_ASINH):
    CASE_FLT_FN (BUILT_ಒಳ_ATAN):
    CASE_FLT_FN (BUILT_ಒಳ_ATANH):
    CASE_FLT_FN (BUILT_ಒಳ_ATAN2):
    CASE_FLT_FN (BUILT_ಒಳ_CBRT):
    CASE_FLT_FN (BUILT_ಒಳ_CEIL):
    CASE_FLT_FN_FLOATN_NX (BUILT_ಒಳ_CEIL):
    CASE_FLT_FN (BUILT_ಒಳ_COPYSIGN):
    CASE_FLT_FN_FLOATN_NX (BUILT_ಒಳ_COPYSIGN):
    CASE_FLT_FN (BUILT_ಒಳ_COS):
    CASE_FLT_FN (BUILT_ಒಳ_COSH):
    CASE_FLT_FN (BUILT_ಒಳ_ERF):
    CASE_FLT_FN (BUILT_ಒಳ_ERFC):
    CASE_FLT_FN (BUILT_ಒಳ_EXP):
    CASE_FLT_FN (BUILT_ಒಳ_EXP2):
    CASE_FLT_FN (BUILT_ಒಳ_EXPM1):
    CASE_FLT_FN (BUILT_ಒಳ_FABS):
    CASE_FLT_FN_FLOATN_NX (BUILT_ಒಳ_FABS):
    CASE_FLT_FN (BUILT_ಒಳ_FDIM):
    CASE_FLT_FN (BUILT_ಒಳ_FLOOR):
    CASE_FLT_FN_FLOATN_NX (BUILT_ಒಳ_FLOOR):
    CASE_FLT_FN (BUILT_ಒಳ_FMA):
    CASE_FLT_FN_FLOATN_NX (BUILT_ಒಳ_FMA):
    CASE_FLT_FN (BUILT_ಒಳ_FMAX):
    CASE_FLT_FN_FLOATN_NX (BUILT_ಒಳ_FMAX):
    CASE_FLT_FN (BUILT_ಒಳ_FMIN):
    CASE_FLT_FN_FLOATN_NX (BUILT_ಒಳ_FMIN):
    CASE_FLT_FN (BUILT_ಒಳ_FMOD):
    CASE_FLT_FN (BUILT_ಒಳ_FREXP):
    CASE_FLT_FN (BUILT_ಒಳ_HYPOT):
    CASE_FLT_FN (BUILT_ಒಳ_ILOGB):
    CASE_FLT_FN (BUILT_ಒಳ_LDEXP):
    CASE_FLT_FN (BUILT_ಒಳ_LGAMMA):
    CASE_FLT_FN (BUILT_ಒಳ_LLRINT):
    CASE_FLT_FN (BUILT_ಒಳ_LLROUND):
    CASE_FLT_FN (BUILT_ಒಳ_LOG):
    CASE_FLT_FN (BUILT_ಒಳ_LOG10):
    CASE_FLT_FN (BUILT_ಒಳ_LOG1_P):
    CASE_FLT_FN (BUILT_ಒಳ_LOG2):
    CASE_FLT_FN (BUILT_ಒಳ_LOGB):
    CASE_FLT_FN (BUILT_ಒಳ_LRINT):
    CASE_FLT_FN (BUILT_ಒಳ_LROUND):
    CASE_FLT_FN (BUILT_ಒಳ_MODF):
    CASE_FLT_FN (BUILT_ಒಳ_NAN):
    CASE_FLT_FN (BUILT_ಒಳ_NEARBYINT):
    CASE_FLT_FN_FLOATN_NX (BUILT_ಒಳ_NEARBYINT):
    CASE_FLT_FN (BUILT_ಒಳ_NEXTAFTER):
    CASE_FLT_FN (BUILT_ಒಳ_NEXTTOWARD):
    CASE_FLT_FN (BUILT_ಒಳ_POW):
    CASE_FLT_FN (BUILT_ಒಳ_REMAINDER):
    CASE_FLT_FN (BUILT_ಒಳ_REMQUO):
    CASE_FLT_FN (BUILT_ಒಳ_RINT):
    CASE_FLT_FN_FLOATN_NX (BUILT_ಒಳ_RINT):
    CASE_FLT_FN (BUILT_ಒಳ_ಸುತ್ತು):
    CASE_FLT_FN_FLOATN_NX (BUILT_ಒಳ_ಸುತ್ತು):
    CASE_FLT_FN (BUILT_ಒಳ_SCALBLN):
    CASE_FLT_FN (BUILT_ಒಳ_SCALBN):
    CASE_FLT_FN (BUILT_ಒಳ_SIN):
    CASE_FLT_FN (BUILT_ಒಳ_SINH):
    CASE_FLT_FN (BUILT_ಒಳ_SINCOS):
    CASE_FLT_FN (BUILT_ಒಳ_SQRT):
    CASE_FLT_FN_FLOATN_NX (BUILT_ಒಳ_SQRT):
    CASE_FLT_FN (BUILT_ಒಳ_TAN):
    CASE_FLT_FN (BUILT_ಒಳ_TANH):
    CASE_FLT_FN (BUILT_ಒಳ_TGAMMA):
    CASE_FLT_FN (BUILT_ಒಳ_TRUNC):
    CASE_FLT_FN_FLOATN_NX (BUILT_ಒಳ_TRUNC):
    ಸ್ಥಿತಿ BUILT_ಒಳ_ISINF:
    ಸ್ಥಿತಿ BUILT_ಒಳ_ISNAN:
      ಹಿಂತಿರುಗಿ "<math.h>";
    CASE_FLT_FN (BUILT_ಒಳ_CABS):
    CASE_FLT_FN (BUILT_ಒಳ_CACOS):
    CASE_FLT_FN (BUILT_ಒಳ_CACOSH):
    CASE_FLT_FN (BUILT_ಒಳ_CARG):
    CASE_FLT_FN (BUILT_ಒಳ_CASIN):
    CASE_FLT_FN (BUILT_ಒಳ_CASINH):
    CASE_FLT_FN (BUILT_ಒಳ_CATAN):
    CASE_FLT_FN (BUILT_ಒಳ_CATANH):
    CASE_FLT_FN (BUILT_ಒಳ_CCOS):
    CASE_FLT_FN (BUILT_ಒಳ_CCOSH):
    CASE_FLT_FN (BUILT_ಒಳ_CEXP):
    CASE_FLT_FN (BUILT_ಒಳ_CIMAG):
    CASE_FLT_FN (BUILT_ಒಳ_CLOG):
    CASE_FLT_FN (BUILT_ಒಳ_CONJ):
    CASE_FLT_FN (BUILT_ಒಳ_CPOW):
    CASE_FLT_FN (BUILT_ಒಳ_CPROJ):
    CASE_FLT_FN (BUILT_ಒಳ_CREAL):
    CASE_FLT_FN (BUILT_ಒಳ_CSIN):
    CASE_FLT_FN (BUILT_ಒಳ_CSINH):
    CASE_FLT_FN (BUILT_ಒಳ_CSQRT):
    CASE_FLT_FN (BUILT_ಒಳ_CTAN):
    CASE_FLT_FN (BUILT_ಒಳ_CTANH):
      ಹಿಂತಿರುಗಿ "<complex.h>";
    ಸ್ಥಿತಿ BUILT_ಒಳ_MEMCHR:
    ಸ್ಥಿತಿ BUILT_ಒಳ_MEMCMP:
    ಸ್ಥಿತಿ BUILT_ಒಳ_MEMCPY:
    ಸ್ಥಿತಿ BUILT_ಒಳ_MEMMOVE:
    ಸ್ಥಿತಿ BUILT_ಒಳ_MEMSET:
    ಸ್ಥಿತಿ BUILT_ಒಳ_STRCAT:
    ಸ್ಥಿತಿ BUILT_ಒಳ_STRCHR:
    ಸ್ಥಿತಿ BUILT_ಒಳ_STRCMP:
    ಸ್ಥಿತಿ BUILT_ಒಳ_STRCPY:
    ಸ್ಥಿತಿ BUILT_ಒಳ_STRCSPN:
    ಸ್ಥಿತಿ BUILT_ಒಳ_STRLEN:
    ಸ್ಥಿತಿ BUILT_ಒಳ_STRNCAT:
    ಸ್ಥಿತಿ BUILT_ಒಳ_STRNCMP:
    ಸ್ಥಿತಿ BUILT_ಒಳ_STRNCPY:
    ಸ್ಥಿತಿ BUILT_ಒಳ_STRPBRK:
    ಸ್ಥಿತಿ BUILT_ಒಳ_STRRCHR:
    ಸ್ಥಿತಿ BUILT_ಒಳ_STRSPN:
    ಸ್ಥಿತಿ BUILT_ಒಳ_STRSTR:
      ಹಿಂತಿರುಗಿ "<string.h>";
    ಸ್ಥಿತಿ BUILT_ಒಳ_FPRINTF:
    ಸ್ಥಿತಿ BUILT_ಒಳ_PUTC:
    ಸ್ಥಿತಿ BUILT_ಒಳ_FPUTC:
    ಸ್ಥಿತಿ BUILT_ಒಳ_FPUTS:
    ಸ್ಥಿತಿ BUILT_ಒಳ_FSCANF:
    ಸ್ಥಿತಿ BUILT_ಒಳ_FWRITE:
    ಸ್ಥಿತಿ BUILT_ಒಳ_PRINTF:
    ಸ್ಥಿತಿ BUILT_ಒಳ_PUTCHAR:
    ಸ್ಥಿತಿ BUILT_ಒಳ_PUTS:
    ಸ್ಥಿತಿ BUILT_ಒಳ_SCANF:
    ಸ್ಥಿತಿ BUILT_ಒಳ_SNPRINTF:
    ಸ್ಥಿತಿ BUILT_ಒಳ_SPRINTF:
    ಸ್ಥಿತಿ BUILT_ಒಳ_SSCANF:
    ಸ್ಥಿತಿ BUILT_ಒಳ_VFPRINTF:
    ಸ್ಥಿತಿ BUILT_ಒಳ_VFSCANF:
    ಸ್ಥಿತಿ BUILT_ಒಳ_VPRINTF:
    ಸ್ಥಿತಿ BUILT_ಒಳ_VSCANF:
    ಸ್ಥಿತಿ BUILT_ಒಳ_VSNPRINTF:
    ಸ್ಥಿತಿ BUILT_ಒಳ_VSPRINTF:
    ಸ್ಥಿತಿ BUILT_ಒಳ_VSSCANF:
      ಹಿಂತಿರುಗಿ "<stdio.h>";
    ಸ್ಥಿತಿ BUILT_ಒಳ_ISALNUM:
    ಸ್ಥಿತಿ BUILT_ಒಳ_ISALPHA:
    ಸ್ಥಿತಿ BUILT_ಒಳ_ISBLANK:
    ಸ್ಥಿತಿ BUILT_ಒಳ_ISCNTRL:
    ಸ್ಥಿತಿ BUILT_ಒಳ_ISDIGIT:
    ಸ್ಥಿತಿ BUILT_ಒಳ_ISGRAPH:
    ಸ್ಥಿತಿ BUILT_ಒಳ_ISLOWER:
    ಸ್ಥಿತಿ BUILT_ಒಳ_ISPRINT:
    ಸ್ಥಿತಿ BUILT_ಒಳ_ISPUNCT:
    ಸ್ಥಿತಿ BUILT_ಒಳ_ISSPACE:
    ಸ್ಥಿತಿ BUILT_ಒಳ_ISUPPER:
    ಸ್ಥಿತಿ BUILT_ಒಳ_ISXDIGIT:
    ಸ್ಥಿತಿ BUILT_ಒಳ_TOLOWER:
    ಸ್ಥಿತಿ BUILT_ಒಳ_TOUPPER:
      ಹಿಂತಿರುಗಿ "<ctype.h>";
    ಸ್ಥಿತಿ BUILT_ಒಳ_ISWALNUM:
    ಸ್ಥಿತಿ BUILT_ಒಳ_ISWALPHA:
    ಸ್ಥಿತಿ BUILT_ಒಳ_ISWBLANK:
    ಸ್ಥಿತಿ BUILT_ಒಳ_ISWCNTRL:
    ಸ್ಥಿತಿ BUILT_ಒಳ_ISWDIGIT:
    ಸ್ಥಿತಿ BUILT_ಒಳ_ISWGRAPH:
    ಸ್ಥಿತಿ BUILT_ಒಳ_ISWLOWER:
    ಸ್ಥಿತಿ BUILT_ಒಳ_ISWPRINT:
    ಸ್ಥಿತಿ BUILT_ಒಳ_ISWPUNCT:
    ಸ್ಥಿತಿ BUILT_ಒಳ_ISWSPACE:
    ಸ್ಥಿತಿ BUILT_ಒಳ_ISWUPPER:
    ಸ್ಥಿತಿ BUILT_ಒಳ_ISWXDIGIT:
    ಸ್ಥಿತಿ BUILT_ಒಳ_TOWLOWER:
    ಸ್ಥಿತಿ BUILT_ಒಳ_TOWUPPER:
      ಹಿಂತಿರುಗಿ "<wctype.h>";
    ಸ್ಥಿತಿ BUILT_ಒಳ_ABORT:
    ಸ್ಥಿತಿ BUILT_ಒಳ_ABS:
    ಸ್ಥಿತಿ BUILT_ಒಳ_CALLOC:
    ಸ್ಥಿತಿ BUILT_ಒಳ_EXIT:
    ಸ್ಥಿತಿ BUILT_ಒಳ_FREE:
    ಸ್ಥಿತಿ BUILT_ಒಳ_LABS:
    ಸ್ಥಿತಿ BUILT_ಒಳ_LLABS:
    ಸ್ಥಿತಿ BUILT_ಒಳ_MALLOC:
    ಸ್ಥಿತಿ BUILT_ಒಳ_REALLOC:
    ಸ್ಥಿತಿ BUILT_ಒಳ_EXIT2:
    ಸ್ಥಿತಿ BUILT_ಒಳ_ALIGNED_ALLOC:
      ಹಿಂತಿರುಗಿ "<stdlib.h>";
    ಸ್ಥಿತಿ BUILT_ಒಳ_IMAXABS:
      ಹಿಂತಿರುಗಿ "<inttypes.h>";
    ಸ್ಥಿತಿ BUILT_ಒಳ_STRFTIME:
      ಹಿಂತಿರುಗಿ "<time.h>";
    ಪೂರ್ವನಿಯೋಜಿತ:
      ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }
}

/* Generate an implicit declaration for identifier FUNCTIONID at LOC as a
   function of type int ().  */

ವೃಕ್ಷ
implicitly_declare (location_t loc, ವೃಕ್ಷ functionid)
{
  ರಚನೆ c_binding *b;
  ವೃಕ್ಷ decl = NULL_ವೃಕ್ಷ;
  ವೃಕ್ಷ asmspec_ವೃಕ್ಷ;

  ಗಾಗಿ (b = I_ಚಿಹ್ನೆ_BINDING (functionid); b; b = b->shadowed)
    {
      ಆದರೆ (B_ಒಳ_SCOPE (b, external_scope))
	{
	  decl = b->decl;
	  ನಿಲ್ಲಿಸು;
	}
    }

  ಆದರೆ (decl)
    {
      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (decl) != FUNCTION_DECL)
	ಹಿಂತಿರುಗಿ decl;

      /* FIXME: Objective-C has weird not-really-builtin functions
	 which are supposed to be visible automatically.  They wind up
	 in the external scope because they're pushed before the file
	 scope gets created.  Catch this here and rebind them into the
	 file scope.  */
      ಆದರೆ (!fndecl_built_ಒಳ_p (decl) && DECL_IS_UNDECLARED_BUILTIN (decl))
	{
	  bind (functionid, decl, file_scope,
		/*invisible=*/ಸುಳ್ಳು, /*nested=*/ನಿಜ,
		DECL_ಮೂಲ_LOCATION (decl));
	  ಹಿಂತಿರುಗಿ decl;
	}
      ಇಲ್ಲದಿದ್ದರೆ
	{
	  ವೃಕ್ಷ newtype = default_function_type;
	  ಆದರೆ (b->u.type)
	    ವೃಕ್ಷ_TYPE (decl) = b->u.type;
	  /* Implicit declaration of a function already declared
	     (somehow) in a different scope, or as a built-in.
	     If this is the first time this has happened, warn;
	     then recycle the old declaration but with the new type.  */
	  ಆದರೆ (!C_DECL_IMPLICIT (decl))
	    {
	      implicit_decl_permerror (loc, functionid, decl);
	      C_DECL_IMPLICIT (decl) = 1;
	    }
	  ಆದರೆ (fndecl_built_ಒಳ_p (decl))
	    {
	      newtype = c_build_type_attribute_variant (newtype,
							TYPE_ಗುಣಲಕ್ಷಣಗಳು
							(ವೃಕ್ಷ_TYPE (decl)));
	      ಆದರೆ (!comptypes (newtype, ವೃಕ್ಷ_TYPE (decl)))
		{
		  auto_diagnostic_ಗುಂಪು d;
		  ತಾರ್ಕಿಕ warned = warning_at (loc,
					    OPT_Wbuiltin_declaration_mismatch,
					    "incompatible implicit "
					    "declaration of built-in "
					    "function %qD", decl);
		  /* See if we can hint which header to include.  */
		  ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಶೀರ್ಷಿಕೆ = ಶೀರ್ಷಿಕೆ_for_builtin_fn (decl);
		  ಆದರೆ (ಶೀರ್ಷಿಕೆ != ಖಾಲಿ && warned)
		    {
		      rich_location richloc (ಸಾಲು_ಕೋಷ್ಟಕ, loc);
		      maybe_ಕೂಡಿಸು_include_fixit (&richloc, ಶೀರ್ಷಿಕೆ, ನಿಜ);
		      inform (&richloc,
			      "include %qs or provide a declaration of %qD",
			      ಶೀರ್ಷಿಕೆ, decl);
		    }
		  newtype = ವೃಕ್ಷ_TYPE (decl);
		}
	    }
	  ಇಲ್ಲದಿದ್ದರೆ
	    {
	      ಆದರೆ (!comptypes (newtype, ವೃಕ್ಷ_TYPE (decl)))
		{
		  auto_diagnostic_ಗುಂಪು d;
		  error_at (loc, "incompatible implicit declaration of "
			    "function %qD", decl);
		  locate_old_decl (decl);
		}
	    }
	  b->u.type = ವೃಕ್ಷ_TYPE (decl);
	  ವೃಕ್ಷ_TYPE (decl) = newtype;
	  bind (functionid, decl, current_scope,
		/*invisible=*/ಸುಳ್ಳು, /*nested=*/ನಿಜ,
		DECL_ಮೂಲ_LOCATION (decl));
	  ಹಿಂತಿರುಗಿ decl;
	}
    }

  /* Not seen before.  */
  decl = build_decl (loc, FUNCTION_DECL, functionid, default_function_type);
  DECL_EXTERNAL (decl) = 1;
  ವೃಕ್ಷ_ಬಹಿರಂಗ (decl) = 1;
  C_DECL_IMPLICIT (decl) = 1;
  implicit_decl_permerror (loc, functionid, 0);
  asmspec_ವೃಕ್ಷ = maybe_apply_renaming_pragma (decl, /*asmname=*/ಖಾಲಿ);
  ಆದರೆ (asmspec_ವೃಕ್ಷ)
    ಗಣ_user_assembler_name (decl, ವೃಕ್ಷ_STRING_ಸೂಚಕ (asmspec_ವೃಕ್ಷ));

  /* C89 says implicit declarations are in the innermost block.
     So we record the decl in the standard fashion.  */
  decl = pushdecl (decl);

  /* No need to call objc_check_decl here - it's a function type.  */
  rest_ದ_decl_compilation (decl, 0, 0);

  /* Write a record describing this implicit function declaration
     to the prototypes file (if requested).  */
  gen_aux_info_ದಾಖಲೆ (decl, 0, 1, 0);

  /* Possibly apply some default attributes to this implicit declaration.  */
  decl_ಗುಣಲಕ್ಷಣಗಳು (&decl, NULL_ವೃಕ್ಷ, 0);

  ಹಿಂತಿರುಗಿ decl;
}

/* Issue an error message for a reference to an undeclared variable
   ID, including a reference to a builtin outside of function-call
   context.  Establish a binding of the identifier to error_mark_node
   in an appropriate scope, which will suppress further errors for the
   same identifier.  The error message should be given location LOC.  */
ಶೂನ್ಯ
undeclared_variable (location_t loc, ವೃಕ್ಷ id)
{
  ಸ್ಥಿರ ತಾರ್ಕಿಕ already = ಸುಳ್ಳು;
  ರಚನೆ c_scope *scope;

  auto_diagnostic_ಗುಂಪು d;
  ಆದರೆ (current_function_decl == NULL_ವೃಕ್ಷ)
    {
      name_hint guessed_id = lookup_name_fuzzy (id, FUZZY_LOOKUP_NAME, loc);
      ಆದರೆ (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *suggestion = guessed_id.suggestion ())
	{
	  gcc_rich_location richloc (loc);
	  richloc.ಕೂಡಿಸು_fixit_replace (suggestion);
	  error_at (&richloc,
		    "%qE undeclared here (not in a function);"
		    " did you mean %qs?",
		    id, suggestion);
	}
      ಇಲ್ಲದಿದ್ದರೆ
	error_at (loc, "%qE undeclared here (not in a function)", id);
      scope = current_scope;
    }
  ಇಲ್ಲದಿದ್ದರೆ
    {
      ಆದರೆ (!objc_diagnose_ಖಾಸಗಿ_ivar (id))
	{
	  name_hint guessed_id = lookup_name_fuzzy (id, FUZZY_LOOKUP_NAME, loc);
	  ಆದರೆ (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *suggestion = guessed_id.suggestion ())
	    {
	      gcc_rich_location richloc (loc);
	      richloc.ಕೂಡಿಸು_fixit_replace (suggestion);
	      error_at (&richloc,
			"%qE undeclared (first use in this function);"
			" did you mean %qs?",
			id, suggestion);
	    }
	  ಇಲ್ಲದಿದ್ದರೆ
	    error_at (loc, "%qE undeclared (first use in this function)", id);
	}
      ಆದರೆ (!already)
	{
          inform (loc, "each undeclared identifier is reported only"
                  " once for each function it appears in");
	  already = ನಿಜ;
	}

      /* If we are parsing old-style parameter decls, current_function_decl
	 will be nonnull but current_function_scope will be null.  */
      scope = current_function_scope ? current_function_scope : current_scope;
    }
  bind (id, error_mark_ಗಂಟು, scope, /*invisible=*/ಸುಳ್ಳು, /*nested=*/ಸುಳ್ಳು,
	UNKNOWN_LOCATION);
}

/* Subroutine of lookup_label, declare_label, define_label: construct a
   LABEL_DECL with all the proper frills.  Also create a struct
   c_label_vars initialized for the current scope.  */

ಸ್ಥಿರ ವೃಕ್ಷ
make_label (location_t location, ವೃಕ್ಷ name, ತಾರ್ಕಿಕ defining,
	    ರಚನೆ c_label_vars **p_label_vars)
{
  ವೃಕ್ಷ label = build_decl (location, LABEL_DECL, name, void_type_ಗಂಟು);
  DECL_CONTEXT (label) = current_function_decl;
  ಗಣ_DECL_ಬಹುಲಕ (label, VOIDmode);

  c_label_vars *label_vars = ggc_alloc<c_label_vars> ();
  label_vars->shadowed = ಖಾಲಿ;
  ಗಣ_spot_bindings (&label_vars->label_bindings, defining);
  label_vars->decls_ಒಳ_scope = make_ವೃಕ್ಷ_ಸದಿಶ ();
  label_vars->gotos = ಖಾಲಿ;
  *p_label_vars = label_vars;

  ಹಿಂತಿರುಗಿ label;
}

/* Get the LABEL_DECL corresponding to identifier NAME as a label.
   Create one if none exists so far for the current function.
   This is called when a label is used in a goto expression or
   has its address taken.  */

ವೃಕ್ಷ
lookup_label (ವೃಕ್ಷ name)
{
  ವೃಕ್ಷ label;
  ರಚನೆ c_label_vars *label_vars;

  ಆದರೆ (current_function_scope == 0)
    {
      error ("label %qE referenced outside of any function", name);
      ಹಿಂತಿರುಗಿ NULL_ವೃಕ್ಷ;
    }

  /* Use a label already defined or ref'd with this name, but not if
     it is inherited from a containing function and wasn't declared
     using __label__.  */
  label = I_LABEL_DECL (name);
  ಆದರೆ (label && (DECL_CONTEXT (label) == current_function_decl
		|| C_DECLARED_LABEL_FLAG (label)))
    {
      /* If the label has only been declared, update its apparent
	 location to point here, for better diagnostics if it
	 turns out not to have been defined.  */
      ಆದರೆ (DECL_INITIAL (label) == NULL_ವೃಕ್ಷ)
	DECL_ಮೂಲ_LOCATION (label) = ಒಳಹರಿವು_location;
      ಹಿಂತಿರುಗಿ label;
    }

  /* No label binding for that identifier; make one.  */
  label = make_label (ಒಳಹರಿವು_location, name, ಸುಳ್ಳು, &label_vars);

  /* Ordinary labels go in the current function scope.  */
  bind_label (name, label, current_function_scope, label_vars);

  ಹಿಂತಿರುಗಿ label;
}

/* Issue a warning about DECL for a goto statement at GOTO_LOC going
   to LABEL.  */

ಸ್ಥಿರ ಶೂನ್ಯ
warn_about_goto (location_t goto_loc, ವೃಕ್ಷ label, ವೃಕ್ಷ decl)
{
  auto_diagnostic_ಗುಂಪು d;
  ಆದರೆ (c_type_variably_modified_p (ವೃಕ್ಷ_TYPE (decl)))
    error_at (goto_loc,
	      "jump into scope of identifier with variably modified type");
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (flag_openmp
	   && lookup_attribute ("omp allocate", DECL_ಗುಣಲಕ್ಷಣಗಳು (decl)))
    error_at (goto_loc, "jump skips OpenMP %<allocate%> allocation");
  ಇಲ್ಲದಿದ್ದರೆ
    ಆದರೆ (!warning_at (goto_loc, OPT_Wjump_ತಪ್ಪಿದವು_init,
		     "jump skips variable initialization"))
      ಹಿಂತಿರುಗಿ;
  inform (DECL_ಮೂಲ_LOCATION (label), "label %qD defined here", label);
  inform (DECL_ಮೂಲ_LOCATION (decl), "%qD declared here", decl);
}

/* Look up a label because of a goto statement.  This is like
   lookup_label, but also issues any appropriate warnings.  */

ವೃಕ್ಷ
lookup_label_for_goto (location_t loc, ವೃಕ್ಷ name)
{
  ವೃಕ್ಷ label;
  ರಚನೆ c_label_vars *label_vars;
  ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ ix;
  ವೃಕ್ಷ decl;

  label = lookup_label (name);
  ಆದರೆ (label == NULL_ವೃಕ್ಷ)
    ಹಿಂತಿರುಗಿ NULL_ವೃಕ್ಷ;

  /* If we are jumping to a different function, we can't issue any
     useful warnings.  */
  ಆದರೆ (DECL_CONTEXT (label) != current_function_decl)
    {
      gcc_assert (C_DECLARED_LABEL_FLAG (label));
      ಹಿಂತಿರುಗಿ label;
    }

  label_vars = I_LABEL_BINDING (name)->u.label;

  /* If the label has not yet been defined, then push this goto on a
     list for possible later warnings.  */
  ಆದರೆ (label_vars->label_bindings.scope == ಖಾಲಿ)
    {
      c_goto_bindings *g = ggc_alloc<c_goto_bindings> ();

      g->loc = loc;
      ಗಣ_spot_bindings (&g->goto_bindings, ನಿಜ);
      vec_ಸುರಕ್ಷಿತ_ತಳ್ಳು (label_vars->gotos, g);
      ಹಿಂತಿರುಗಿ label;
    }

  /* If there are any decls in label_vars->decls_in_scope, then this
     goto has missed the declaration of the decl.  This happens for a
     case like
       int i = 1;
      lab:
       ...
       goto lab;
     Issue a warning or error.  */
  FOR_EACH_VEC_ಸುರಕ್ಷಿತ_ELT (label_vars->decls_ಒಳ_scope, ix, decl)
    warn_about_goto (loc, label, decl);

  ಆದರೆ (label_vars->label_bindings.ಎಡ_stmt_ಅಭಿವ್ಯಕ್ತಿ)
    {
      auto_diagnostic_ಗುಂಪು d;
      error_at (loc, "jump into statement expression");
      inform (DECL_ಮೂಲ_LOCATION (label), "label %qD defined here", label);
    }

  ಹಿಂತಿರುಗಿ label;
}

/* Make a label named NAME in the current function, shadowing silently
   any that may be inherited from containing functions or containing
   scopes.  This is called for __label__ declarations.  */

ವೃಕ್ಷ
declare_label (ವೃಕ್ಷ name)
{
  ರಚನೆ c_binding *b = I_LABEL_BINDING (name);
  ವೃಕ್ಷ label;
  ರಚನೆ c_label_vars *label_vars;

  /* Check to make sure that the label hasn't already been declared
     at this scope */
  ಆದರೆ (b && B_ಒಳ_CURRENT_SCOPE (b))
    {
      auto_diagnostic_ಗುಂಪು d;
      error ("duplicate label declaration %qE", name);
      locate_old_decl (b->decl);

      /* Just use the previous declaration.  */
      ಹಿಂತಿರುಗಿ b->decl;
    }

  label = make_label (ಒಳಹರಿವು_location, name, ಸುಳ್ಳು, &label_vars);
  C_DECLARED_LABEL_FLAG (label) = 1;

  /* Declared labels go in the current scope.  */
  bind_label (name, label, current_scope, label_vars);

  ಹಿಂತಿರುಗಿ label;
}

/* When we define a label, issue any appropriate warnings if there are
   any gotos earlier in the function which jump to this label.  */

ಸ್ಥಿರ ಶೂನ್ಯ
check_earlier_gotos (ವೃಕ್ಷ label, ರಚನೆ c_label_vars* label_vars)
{
  ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ ix;
  ರಚನೆ c_goto_bindings *g;

  FOR_EACH_VEC_ಸುರಕ್ಷಿತ_ELT (label_vars->gotos, ix, g)
    {
      ರಚನೆ c_binding *b;
      ರಚನೆ c_scope *scope;

      /* We have a goto to this label.  The goto is going forward.  In
	 g->scope, the goto is going to skip any binding which was
	 defined after g->bindings_in_scope.  */
      ಆದರೆ (g->goto_bindings.scope->has_jump_unsafe_decl)
	{
	  ಗಾಗಿ (b = g->goto_bindings.scope->bindings;
	       b != g->goto_bindings.bindings_ಒಳ_scope;
	       b = b->prev)
	    {
	      ಆದರೆ (decl_jump_unsafe (b->decl))
		warn_about_goto (g->loc, label, b->decl);
	    }
	}

      /* We also need to warn about decls defined in any scopes
	 between the scope of the label and the scope of the goto.  */
      ಗಾಗಿ (scope = label_vars->label_bindings.scope;
	   scope != g->goto_bindings.scope;
	   scope = scope->outer)
	{
	  gcc_assert (scope != ಖಾಲಿ);
	  ಆದರೆ (scope->has_jump_unsafe_decl)
	    {
	      ಆದರೆ (scope == label_vars->label_bindings.scope)
		b = label_vars->label_bindings.bindings_ಒಳ_scope;
	      ಇಲ್ಲದಿದ್ದರೆ
		b = scope->bindings;
	      ಗಾಗಿ (; b != ಖಾಲಿ; b = b->prev)
		{
		  ಆದರೆ (decl_jump_unsafe (b->decl))
		    warn_about_goto (g->loc, label, b->decl);
		}
	    }
	}

      ಆದರೆ (g->goto_bindings.stmt_exprs > 0)
	{
	  auto_diagnostic_ಗುಂಪು d;
	  error_at (g->loc, "jump into statement expression");
	  inform (DECL_ಮೂಲ_LOCATION (label), "label %qD defined here",
		  label);
	}
    }

  /* Now that the label is defined, we will issue warnings about
     subsequent gotos to this label when we see them.  */
  vec_ಸುರಕ್ಷಿತ_truncate (label_vars->gotos, 0);
  label_vars->gotos = ಖಾಲಿ;
}

/* Define a label, specifying the location in the source file.
   Return the LABEL_DECL node for the label, if the definition is valid.
   Otherwise return NULL_TREE.  */

ವೃಕ್ಷ
define_label (location_t location, ವೃಕ್ಷ name)
{
  /* Find any preexisting label with this name.  It is an error
     if that label has already been defined in this function, or
     if there is a containing function with a declared label with
     the same name.  */
  ವೃಕ್ಷ label = I_LABEL_DECL (name);

  ಆದರೆ (label
      && ((DECL_CONTEXT (label) == current_function_decl
	   && DECL_INITIAL (label) != NULL_ವೃಕ್ಷ)
	  || (DECL_CONTEXT (label) != current_function_decl
	      && C_DECLARED_LABEL_FLAG (label))))
    {
      auto_diagnostic_ಗುಂಪು d;
      error_at (location, "duplicate label %qD", label);
      locate_old_decl (label);
      ಹಿಂತಿರುಗಿ NULL_ವೃಕ್ಷ;
    }
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (label && DECL_CONTEXT (label) == current_function_decl)
    {
      ರಚನೆ c_label_vars *label_vars = I_LABEL_BINDING (name)->u.label;

      /* The label has been used or declared already in this function,
	 but not defined.  Update its location to point to this
	 definition.  */
      DECL_ಮೂಲ_LOCATION (label) = location;
      ಗಣ_spot_bindings (&label_vars->label_bindings, ನಿಜ);

      /* Issue warnings as required about any goto statements from
	 earlier in the function.  */
      check_earlier_gotos (label, label_vars);
    }
  ಇಲ್ಲದಿದ್ದರೆ
    {
      ರಚನೆ c_label_vars *label_vars;

      /* No label binding for that identifier; make one.  */
      label = make_label (location, name, ನಿಜ, &label_vars);

      /* Ordinary labels go in the current function scope.  */
      bind_label (name, label, current_function_scope, label_vars);
    }

  ಆದರೆ (!ಒಳ_system_ಶೀರ್ಷಿಕೆ_at (ಒಳಹರಿವು_location) && lookup_name (name))
    warning_at (location, OPT_Wtraditional,
		"traditional C lacks a separate namespace "
		"for labels, identifier %qE conflicts", name);

  /* Mark label as having been defined.  */
  DECL_INITIAL (label) = error_mark_ಗಂಟು;
  ಹಿಂತಿರುಗಿ label;
}

/* Get the bindings for a new switch statement.  This is used to issue
   warnings as appropriate for jumps from the switch to case or
   default labels.  */

ರಚನೆ c_spot_bindings *
c_get_switch_bindings (ಶೂನ್ಯ)
{
  ರಚನೆ c_spot_bindings *switch_bindings;

  switch_bindings = XNEW (ರಚನೆ c_spot_bindings);
  ಗಣ_spot_bindings (switch_bindings, ನಿಜ);
  ಹಿಂತಿರುಗಿ switch_bindings;
}

ಶೂನ್ಯ
c_release_switch_bindings (ರಚನೆ c_spot_bindings *bindings)
{
  gcc_assert (bindings->stmt_exprs == 0 && !bindings->ಎಡ_stmt_ಅಭಿವ್ಯಕ್ತಿ);
  XDELETE (bindings);
}

/* This is called at the point of a case or default label to issue
   warnings about decls as needed.  It returns true if it found an
   error, not just a warning.  */

ತಾರ್ಕಿಕ
c_check_switch_jump_warnings (ರಚನೆ c_spot_bindings *switch_bindings,
			      location_t switch_loc, location_t case_loc)
{
  ತಾರ್ಕಿಕ saw_error;
  ರಚನೆ c_scope *scope;

  saw_error = ಸುಳ್ಳು;
  ಗಾಗಿ (scope = current_scope;
       scope != switch_bindings->scope;
       scope = scope->outer)
    {
      ರಚನೆ c_binding *b;

      gcc_assert (scope != ಖಾಲಿ);

      ಆದರೆ (!scope->has_jump_unsafe_decl)
	ಮುಂದುವರಿ;

      ಗಾಗಿ (b = scope->bindings; b != ಖಾಲಿ; b = b->prev)
	{
	  ಆದರೆ (decl_jump_unsafe (b->decl))
	    {
	      auto_diagnostic_ಗುಂಪು d;
	      ತಾರ್ಕಿಕ emitted;
	      ಆದರೆ (c_type_variably_modified_p (ವೃಕ್ಷ_TYPE (b->decl)))
		{
		  saw_error = ನಿಜ;
		  error_at (case_loc,
			    "switch jumps into scope of identifier with "
			    "variably modified type");
		  emitted = ನಿಜ;
		}
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (flag_openmp
		       && lookup_attribute ("omp allocate",
					    DECL_ಗುಣಲಕ್ಷಣಗಳು (b->decl)))
		{
		  saw_error = ನಿಜ;
		  error_at (case_loc,
			    "switch jumps over OpenMP %<allocate%> allocation");
		  emitted = ನಿಜ;
		}
	      ಇಲ್ಲದಿದ್ದರೆ
		emitted
		  = warning_at (case_loc, OPT_Wjump_ತಪ್ಪಿದವು_init,
				"switch jumps over variable initialization");
	      ಆದರೆ (emitted)
		{
		  inform (switch_loc, "switch starts here");
		  inform (DECL_ಮೂಲ_LOCATION (b->decl), "%qD declared here",
			  b->decl);
		}
	    }
	}
    }

  ಆದರೆ (switch_bindings->stmt_exprs > 0)
    {
      saw_error = ನಿಜ;
      auto_diagnostic_ಗುಂಪು d;
      error_at (case_loc, "switch jumps into statement expression");
      inform (switch_loc, "switch starts here");
    }

  ಹಿಂತಿರುಗಿ saw_error;
}

/* Given NAME, an IDENTIFIER_NODE,
   return the structure (or union or enum) definition for that name.
   If THISLEVEL_ONLY is nonzero, searches only the current_scope.
   CODE says which kind of type the caller wants;
   it is RECORD_TYPE or UNION_TYPE or ENUMERAL_TYPE.
   If PLOC is not NULL and this returns non-null, it sets *PLOC to the
   location where the tag was defined.
   If the wrong kind of type is found, an error is reported.  */

ಸ್ಥಿರ ವೃಕ್ಷ
lookup_ಟ್ಯಾಗ್ (ಎಣಿಕೆ ವೃಕ್ಷ_ಸಂಕೇತ_2 ಸಂಕೇತ_2, ವೃಕ್ಷ name, ತಾರ್ಕಿಕ thislevel_only,
	    location_t *ploc)
{
  ರಚನೆ c_binding *b = I_ಟ್ಯಾಗ್_BINDING (name);
  ತಾರ್ಕಿಕ thislevel = ಸುಳ್ಳು;

  ಆದರೆ (!b || !b->decl)
    ಹಿಂತಿರುಗಿ NULL_ವೃಕ್ಷ;

  /* We only care about whether it's in this level if
     thislevel_only was set or it might be a type clash.  */
  ಆದರೆ (thislevel_only || ವೃಕ್ಷ_ಸಂಕೇತ (b->decl) != ಸಂಕೇತ_2)
    {
      /* For our purposes, a tag in the external scope is the same as
	 a tag in the file scope.  (Primarily relevant to Objective-C
	 and its builtin structure tags, which get pushed before the
	 file scope is created.)  */
      ಆದರೆ (B_ಒಳ_CURRENT_SCOPE (b)
	  || (current_scope == file_scope && B_ಒಳ_EXTERNAL_SCOPE (b)))
	thislevel = ನಿಜ;
    }

  ಆದರೆ (thislevel_only && !thislevel)
    ಹಿಂತಿರುಗಿ NULL_ವೃಕ್ಷ;

  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (b->decl) != ಸಂಕೇತ_2)
    {
      /* Definition isn't the kind we were looking for.  */
      pending_invalid_xref = name;
      pending_invalid_xref_location = ಒಳಹರಿವು_location;

      /* If in the same binding level as a declaration as a tag
	 of a different type, this must not be allowed to
	 shadow that tag, so give the error immediately.
	 (For example, "struct foo; union foo;" is invalid.)  */
      ಆದರೆ (thislevel)
	pending_xref_error ();
    }

  ಆದರೆ (ploc != ಖಾಲಿ)
    *ploc = b->locus;

  ಹಿಂತಿರುಗಿ b->decl;
}

/* Return true if a definition exists for NAME with code CODE.  */

ತಾರ್ಕಿಕ
ಟ್ಯಾಗ್_exists_p (ಎಣಿಕೆ ವೃಕ್ಷ_ಸಂಕೇತ_2 ಸಂಕೇತ_2, ವೃಕ್ಷ name)
{
  ರಚನೆ c_binding *b = I_ಟ್ಯಾಗ್_BINDING (name);

  ಆದರೆ (b == ಖಾಲಿ || b->decl == NULL_ವೃಕ್ಷ)
    ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
  ಹಿಂತಿರುಗಿ ವೃಕ್ಷ_ಸಂಕೇತ (b->decl) == ಸಂಕೇತ_2;
}

/* Print an error message now
   for a recent invalid struct, union or enum cross reference.
   We don't print them immediately because they are not invalid
   when used in the `struct foo;' construct for shadowing.  */

ಶೂನ್ಯ
pending_xref_error (ಶೂನ್ಯ)
{
  ಆದರೆ (pending_invalid_xref != NULL_ವೃಕ್ಷ)
    error_at (pending_invalid_xref_location, "%qE defined as wrong kind of tag",
	      pending_invalid_xref);
  pending_invalid_xref = NULL_ವೃಕ್ಷ;
}


/* Look up NAME in the current scope and its superiors
   in the namespace of variables, functions and typedefs.
   Return a ..._DECL node of some kind representing its definition,
   or return NULL_TREE if it is undefined.  */

ವೃಕ್ಷ
lookup_name (ವೃಕ್ಷ name)
{
  ರಚನೆ c_binding *b = I_ಚಿಹ್ನೆ_BINDING (name);
  /* Do not resolve non-default function versions.  */
  ಆದರೆ (b
      && ವೃಕ್ಷ_ಸಂಕೇತ (b->decl) == FUNCTION_DECL
      && DECL_FUNCTION_VERSIONED (b->decl)
      && !is_function_default_ಆವೃತ್ತಿ (b->decl))
    ಹಿಂತಿರುಗಿ NULL_ವೃಕ್ಷ;
  ಆದರೆ (b && !b->invisible)
    {
      maybe_ದಾಖಲೆ_typedef_use (b->decl);
      ಹಿಂತಿರುಗಿ b->decl;
    }
  ಹಿಂತಿರುಗಿ NULL_ವೃಕ್ಷ;
}

/* Similar to `lookup_name' but look only at the indicated scope.  */

ಸ್ಥಿರ ವೃಕ್ಷ
lookup_name_ಒಳ_scope (ವೃಕ್ಷ name, ರಚನೆ c_scope *scope)
{
  ರಚನೆ c_binding *b;

  ಗಾಗಿ (b = I_ಚಿಹ್ನೆ_BINDING (name); b; b = b->shadowed)
    ಆದರೆ (B_ಒಳ_SCOPE (b, scope))
      ಹಿಂತಿರುಗಿ b->decl;
  ಹಿಂತಿರುಗಿ NULL_ವೃಕ್ಷ;
}

/* Look for the closest match for NAME within the currently valid
   scopes.

   This finds the identifier with the lowest Levenshtein distance to
   NAME.  If there are multiple candidates with equal minimal distance,
   the first one found is returned.  Scopes are searched from innermost
   outwards, and within a scope in reverse order of declaration, thus
   benefiting candidates "near" to the current scope.

   The function also looks for similar macro names to NAME, since a
   misspelled macro name will not be expanded, and hence looks like an
   identifier to the C frontend.

   It also looks for start_typename keywords, to detect "singed" vs "signed"
   typos.

   Use LOC for any deferred diagnostics.  */

name_hint
lookup_name_fuzzy (ವೃಕ್ಷ name, ಎಣಿಕೆ lookup_name_fuzzy_ಬಗೆ ಬಗೆ, location_t loc)
{
  gcc_assert (ವೃಕ್ಷ_ಸಂಕೇತ (name) == IDENTIFIER_ಗಂಟು);

  /* Look up function-like macros first; maybe misusing them. */
  ಸ್ವಯಂಚಾಲಿತ cpp_ಗಂಟು = cpp_lookup (parse_ಒಳ,
			      (ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ*)IDENTIFIER_ಸೂಚಕ (name),
			      IDENTIFIER_ಉದ್ದಳತೆ (name));
  ಆದರೆ (cpp_ಗಂಟು && cpp_fun_like_macro_p (cpp_ಗಂಟು))
    ಹಿಂತಿರುಗಿ name_hint
      (ಶೂನ್ಯಸೂಚಕ,
       std::make_unique<macro_like_function_ಬಳಸಿದ> (loc,
						   IDENTIFIER_ಸೂಚಕ (name)));

  /* Next, try some well-known names in the C standard library, in case
     the user forgot a #include.  */
  ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಶೀರ್ಷಿಕೆ_hint
    = get_c_stdlib_ಶೀರ್ಷಿಕೆ_for_name (IDENTIFIER_ಸೂಚಕ (name));

  ಆದರೆ (ಶೀರ್ಷಿಕೆ_hint)
    ಹಿಂತಿರುಗಿ name_hint
      (ಶೂನ್ಯಸೂಚಕ,
       std::make_unique<suggest_missing_ಶೀರ್ಷಿಕೆ> (loc,
						 IDENTIFIER_ಸೂಚಕ (name),
						 ಶೀರ್ಷಿಕೆ_hint));

  /* Next, look for exact matches for builtin defines that would have been
     defined if the user had passed a command-line option (e.g. -fopenmp
     for "_OPENMP").  */
  diagnostics::option_id option_id
    = get_option_for_builtin_define (IDENTIFIER_ಸೂಚಕ (name));
  ಆದರೆ (option_id.m_idx > 0)
    ಹಿಂತಿರುಗಿ name_hint
      (ಶೂನ್ಯಸೂಚಕ,
       std::make_unique<suggest_missing_option> (loc,
						 IDENTIFIER_ಸೂಚಕ (name),
						 option_id));

  /* Only suggest names reserved for the implementation if NAME begins
     with an underscore.  */
  ತಾರ್ಕಿಕ consider_implementation_ಹೆಸರುಗಳು = (IDENTIFIER_ಸೂಚಕ (name)[0] == '_');

  ಉತ್ತಮ_ಹೊಂದಿಕೆ<ವೃಕ್ಷ, ವೃಕ್ಷ> bm (name);

  /* Look within currently valid scopes.  */
  ಗಾಗಿ (c_scope *scope = current_scope; scope; scope = scope->outer)
    ಗಾಗಿ (c_binding *binding = scope->bindings; binding; binding = binding->prev)
      {
	ಆದರೆ (!binding->id || binding->invisible)
	  ಮುಂದುವರಿ;
	ಆದರೆ (binding->decl == error_mark_ಗಂಟು)
	  ಮುಂದುವರಿ;
	/* Don't use bindings from implicitly declared functions,
	   as they were likely misspellings themselves.  */
	ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (binding->decl) == FUNCTION_DECL)
	  ಆದರೆ (C_DECL_IMPLICIT (binding->decl))
	    ಮುಂದುವರಿ;
	/* Don't suggest names that are reserved for use by the
	   implementation, unless NAME began with an underscore.  */
	ಆದರೆ (!consider_implementation_ಹೆಸರುಗಳು)
	  {
	    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *suggestion_str = IDENTIFIER_ಸೂಚಕ (binding->id);
	    ಆದರೆ (name_reserved_for_implementation_p (suggestion_str))
	      ಮುಂದುವರಿ;
	  }
	ಆಯ್ಕೆ (ಬಗೆ)
	  {
	  ಸ್ಥಿತಿ FUZZY_LOOKUP_TYPENAME:
	    ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (binding->decl) != TYPE_DECL)
	      ಮುಂದುವರಿ;
	    ನಿಲ್ಲಿಸು;

	  ಸ್ಥಿತಿ FUZZY_LOOKUP_FUNCTION_NAME:
	    ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (binding->decl) != FUNCTION_DECL)
	      {
		/* Allow function pointers.  */
		ಆದರೆ ((VAR_P (binding->decl)
		     || ವೃಕ್ಷ_ಸಂಕೇತ (binding->decl) == PARM_DECL)
		    && ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (binding->decl)) == ಸೂಚಕ_TYPE
		    && (ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_TYPE (binding->decl)))
			== FUNCTION_TYPE))
		  ನಿಲ್ಲಿಸು;
		ಮುಂದುವರಿ;
	      }
	    ನಿಲ್ಲಿಸು;

	  ಪೂರ್ವನಿಯೋಜಿತ:
	    ನಿಲ್ಲಿಸು;
	  }
	bm.consider (binding->id);
      }

  /* Consider macros: if the user misspelled a macro name e.g. "SOME_MACRO"
     as:
       x = SOME_OTHER_MACRO (y);
     then "SOME_OTHER_MACRO" will survive to the frontend and show up
     as a misspelled identifier.

     Use the best distance so far so that a candidate is only set if
     a macro is better than anything so far.  This allows early rejection
     (without calculating the edit distance) of macro names that must have
     distance >= bm.get_best_distance (), and means that we only get a
     non-NULL result for best_macro_match if it's better than any of
     the identifiers already checked, which avoids needless creation
     of identifiers for macro hashnodes.  */
  ಉತ್ತಮ_macro_ಹೊಂದಿಕೆ bmm (name, bm.get_ಉತ್ತಮ_ದೂರ (), parse_ಒಳ);
  cpp_hashnode *ಉತ್ತಮ_macro = bmm.get_ಉತ್ತಮ_meaningful_candidate ();
  /* If a macro is the closest so far to NAME, use it, creating an
     identifier tree node for it.  */
  ಆದರೆ (ಉತ್ತಮ_macro)
    {
      ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *id = (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *)ಉತ್ತಮ_macro->ident.str;
      ವೃಕ್ಷ macro_as_identifier
	= get_identifier_with_ಉದ್ದಳತೆ (id, ಉತ್ತಮ_macro->ident.len);
      bm.ಗಣ_ಉತ್ತಮ_so_far (macro_as_identifier,
			  bmm.get_ಉತ್ತಮ_ದೂರ (),
			  bmm.get_ಉತ್ತಮ_candidate_ಉದ್ದಳತೆ ());
    }

  /* Try the "start_typename" keywords to detect
     "singed" vs "signed" typos.  */
  ಆದರೆ (ಬಗೆ == FUZZY_LOOKUP_TYPENAME)
    {
      ಗಾಗಿ (ಚಿಹ್ನೆರಹಿತ i = 0; i < ಅಂಕೆ_c_common_reswords; i++)
	{
	  ಸ್ಥಿರಾಂಕ c_common_resword *resword = &c_common_reswords[i];
	  ಆದರೆ (!c_keyword_starts_typename (resword->rid))
	    ಮುಂದುವರಿ;
	  ವೃಕ್ಷ resword_identifier = ridpointers [resword->rid];
	  ಆದರೆ (!resword_identifier)
	    ಮುಂದುವರಿ;
	  gcc_assert (ವೃಕ್ಷ_ಸಂಕೇತ (resword_identifier) == IDENTIFIER_ಗಂಟು);
	  bm.consider (resword_identifier);
	}
    }

  ವೃಕ್ಷ ಉತ್ತಮ = bm.get_ಉತ್ತಮ_meaningful_candidate ();
  ಆದರೆ (ಉತ್ತಮ)
    ಹಿಂತಿರುಗಿ name_hint (IDENTIFIER_ಸೂಚಕ (ಉತ್ತಮ), ಖಾಲಿ);
  ಇಲ್ಲದಿದ್ದರೆ
    ಹಿಂತಿರುಗಿ name_hint (ಖಾಲಿ, ಖಾಲಿ);
}


/* Handle the standard [[nodiscard]] attribute.  */

ಸ್ಥಿರ ವೃಕ್ಷ
handle_nodiscard_attribute (ವೃಕ್ಷ *ಗಂಟು, ವೃಕ್ಷ name, ವೃಕ್ಷ /*ವಾದಗಳು*/,
			    ಪೂರ್ಣಾಂಕ /*flags*/, ತಾರ್ಕಿಕ *no_ಕೂಡಿಸು_attrs)
{
  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (*ಗಂಟು) == FUNCTION_DECL)
    {
      ಆದರೆ (VOID_TYPE_P (ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_TYPE (*ಗಂಟು))))
	warning_at (DECL_ಮೂಲ_LOCATION (*ಗಂಟು),
		    OPT_Wattributes, "%qE attribute applied to %qD with void "
		    "return type", name, *ಗಂಟು);
    }
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ದಾಖಲೆ_OR_UNION_TYPE_P (*ಗಂಟು)
	   || ವೃಕ್ಷ_ಸಂಕೇತ (*ಗಂಟು) == ENUMERAL_TYPE)
    /* OK */;
  ಇಲ್ಲದಿದ್ದರೆ
    {
      pedwarn (ಒಳಹರಿವು_location,
	       OPT_Wattributes, "%qE attribute can only be applied to "
	       "functions or to structure, union or enumeration types", name);
      *no_ಕೂಡಿಸು_attrs = ನಿಜ;
    }
  ಹಿಂತಿರುಗಿ NULL_ವೃಕ್ಷ;
}

/* Handle the standard [[noreturn]] attribute.  */

ಸ್ಥಿರ ವೃಕ್ಷ
handle_std_noreturn_attribute (ವೃಕ್ಷ *ಗಂಟು, ವೃಕ್ಷ name, ವೃಕ್ಷ ವಾದಗಳು,
			       ಪೂರ್ಣಾಂಕ flags, ತಾರ್ಕಿಕ *no_ಕೂಡಿಸು_attrs)
{
  /* Unlike GNU __attribute__ ((noreturn)), the standard [[noreturn]]
     only applies to functions, not function pointers.  */
  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (*ಗಂಟು) == FUNCTION_DECL)
    ಹಿಂತಿರುಗಿ handle_noreturn_attribute (ಗಂಟು, name, ವಾದಗಳು, flags, no_ಕೂಡಿಸು_attrs);
  ಇಲ್ಲದಿದ್ದರೆ
    {
      pedwarn (ಒಳಹರಿವು_location, OPT_Wattributes,
	       "standard %qE attribute can only be applied to functions",
	       name);
      *no_ಕೂಡಿಸು_attrs = ನಿಜ;
      ಹಿಂತಿರುಗಿ NULL_ವೃಕ್ಷ;
    }
}

/* Handle the standard [[unsequenced]] attribute.  */

ಸ್ಥಿರ ವೃಕ್ಷ
handle_std_unsequenced_attribute (ವೃಕ್ಷ *ಗಂಟು, ವೃಕ್ಷ name, ವೃಕ್ಷ ವಾದಗಳು,
				  ಪೂರ್ಣಾಂಕ flags, ತಾರ್ಕಿಕ *no_ಕೂಡಿಸು_attrs)
{
  /* Unlike GNU __attribute__ ((unsequenced)), the standard [[unsequenced]]
     should be only applied to function declarators or type specifiers which
     have function type.  */
  ಆದರೆ (ಗಂಟು[2])
    {
      auto_diagnostic_ಗುಂಪು d;
      ಆದರೆ (pedwarn (ಒಳಹರಿವು_location, OPT_Wattributes,
		   "standard %qE attribute can only be applied to function "
		   "declarators or type specifiers with function type", name))
	inform (ಒಳಹರಿವು_location, "did you mean to specify it after %<)%> "
				"following function parameters?");
      *no_ಕೂಡಿಸು_attrs = ನಿಜ;
      ಹಿಂತಿರುಗಿ NULL_ವೃಕ್ಷ;
    }
  ಹಿಂತಿರುಗಿ handle_unsequenced_attribute (ಗಂಟು, name, ವಾದಗಳು, flags, no_ಕೂಡಿಸು_attrs);
}

/* Handle the standard [[reproducible]] attribute.  */

ಸ್ಥಿರ ವೃಕ್ಷ
handle_std_reproducible_attribute (ವೃಕ್ಷ *ಗಂಟು, ವೃಕ್ಷ name, ವೃಕ್ಷ ವಾದಗಳು,
				   ಪೂರ್ಣಾಂಕ flags, ತಾರ್ಕಿಕ *no_ಕೂಡಿಸು_attrs)
{
  ಹಿಂತಿರುಗಿ handle_std_unsequenced_attribute (ಗಂಟು, name, ವಾದಗಳು, flags,
					   no_ಕೂಡಿಸು_attrs);
}

/* Table of supported standard (C23) attributes.  */
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ attribute_spec std_ಗುಣಲಕ್ಷಣಗಳು[] =
{
  /* { name, min_len, max_len, decl_req, type_req, fn_type_req,
       affects_type_identity, handler, exclude } */
  { "_Noreturn", 0, 0, ಸುಳ್ಳು, ಸುಳ್ಳು, ಸುಳ್ಳು, ಸುಳ್ಳು,
    handle_std_noreturn_attribute, ಖಾಲಿ },
  { "deprecated", 0, 1, ಸುಳ್ಳು, ಸುಳ್ಳು, ಸುಳ್ಳು, ಸುಳ್ಳು,
    handle_deprecated_attribute, ಖಾಲಿ },
  { "fallthrough", 0, 0, ಸುಳ್ಳು, ಸುಳ್ಳು, ಸುಳ್ಳು, ಸುಳ್ಳು,
    handle_fallthrough_attribute, ಖಾಲಿ },
  { "maybe_unused", 0, 0, ಸುಳ್ಳು, ಸುಳ್ಳು, ಸುಳ್ಳು, ಸುಳ್ಳು,
    handle_ಬಳಸದ_attribute, ಖಾಲಿ },
  { "nodiscard", 0, 1, ಸುಳ್ಳು, ಸುಳ್ಳು, ಸುಳ್ಳು, ಸುಳ್ಳು,
    handle_nodiscard_attribute, ಖಾಲಿ },
  { "noreturn", 0, 0, ಸುಳ್ಳು, ಸುಳ್ಳು, ಸುಳ್ಳು, ಸುಳ್ಳು,
    handle_std_noreturn_attribute, ಖಾಲಿ },
  { "reproducible", 0, 0, ಸುಳ್ಳು, ನಿಜ, ನಿಜ, ಸುಳ್ಳು,
    handle_std_reproducible_attribute, ಖಾಲಿ },
  { "unsequenced", 0, 0, ಸುಳ್ಳು, ನಿಜ, ನಿಜ, ಸುಳ್ಳು,
    handle_std_unsequenced_attribute, ಖಾಲಿ }
};

ಸ್ಥಿರಾಂಕ scoped_attribute_specs std_attribute_ಕೋಷ್ಟಕ =
{
  ಶೂನ್ಯಸೂಚಕ, { std_ಗುಣಲಕ್ಷಣಗಳು }
};

/* Create the predefined scalar types of C,
   and some nodes representing standard constants (0, 1, (void *) 0).
   Initialize the global scope.
   Make definitions for built-in primitive functions.  */

ಶೂನ್ಯ
c_init_decl_processing (ಶೂನ್ಯ)
{
  location_t save_loc = ಒಳಹರಿವು_location;

  /* Initialize reserved words for parser.  */
  c_parse_init ();

  current_function_decl = NULL_ವೃಕ್ಷ;

  gcc_obstack_init (&parser_obstack);

  /* Make the externals scope.  */
  ತಳ್ಳು_scope ();
  external_scope = current_scope;

  /* Declarations from c_common_nodes_and_builtins must not be associated
     with this input file, lest we get differences between using and not
     using preprocessed headers.  */
  ಒಳಹರಿವು_location = BUILTINS_LOCATION;

  c_common_nodes_and_builtins ();

  /* In C, comparisons and TRUTH_* expressions have type int.  */
  truthvalue_type_ಗಂಟು = integer_type_ಗಂಟು;
  truthvalue_true_ಗಂಟು = integer_one_ಗಂಟು;
  truthvalue_false_ಗಂಟು = integer_zero_ಗಂಟು;

  /* Even in C99, which has a real boolean type.  */
  pushdecl (build_decl (UNKNOWN_LOCATION, TYPE_DECL,
			get_identifier (flag_isoc23 ? "bool" : "_Bool"),
			boolean_type_ಗಂಟು));

  /* C-specific nullptr initialization.  */
  ದಾಖಲೆ_builtin_type (RID_MAX, "typeof (nullptr)", nullptr_type_ಗಂಟು);
  /* The size and alignment of nullptr_t is the same as for a pointer to
     character type.  */
  ಗಣ_TYPE_ALIGN (nullptr_type_ಗಂಟು, GET_ಬಹುಲಕ_ALIGNMENT (ptr_ಬಹುಲಕ));

  ಒಳಹರಿವು_location = save_loc;

  make_fname_decl = c_make_fname_decl;
  ಆರಂಭ_fname_decls ();

  ಆದರೆ (warn_keyword_macro)
    {
      ಗಾಗಿ (ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ i = 0; i < ಅಂಕೆ_c_common_reswords; ++i)
	/* For C register keywords which don't start with underscore
	   or start with just single underscore.  Don't complain about
	   ObjC or Transactional Memory keywords.  */
	ಆದರೆ (c_common_reswords[i].ಶಬ್ದ[0] == '_'
	    && c_common_reswords[i].ಶಬ್ದ[1] == '_')
	  ಮುಂದುವರಿ;
	ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (c_common_reswords[i].disable
		 & (D_TRANSMEM | D_OBJC | D_CXX_OBJC))
	  ಮುಂದುವರಿ;
	ಇಲ್ಲದಿದ್ದರೆ
	  {
	    ವೃಕ್ಷ id = get_identifier (c_common_reswords[i].ಶಬ್ದ);
	    ಆದರೆ (C_IS_RESERVED_ಶಬ್ದ (id)
		&& C_RID_ಸಂಕೇತ (id) != RID_CXX_COMPAT_WARN)
	      cpp_warn (parse_ಒಳ, IDENTIFIER_ಸೂಚಕ (id),
			IDENTIFIER_ಉದ್ದಳತೆ (id));
	  }
    }
}

/* Create the VAR_DECL at LOC for __FUNCTION__ etc. ID is the name to
   give the decl, NAME is the initialization string and TYPE_DEP
   indicates whether NAME depended on the type of the function.  As we
   don't yet implement delayed emission of static data, we mark the
   decl as emitted so it is not placed in the output.  Anything using
   it must therefore pull out the STRING_CST initializer directly.
   FIXME.  */

ಸ್ಥಿರ ವೃಕ್ಷ
c_make_fname_decl (location_t loc, ವೃಕ್ಷ id, ಪೂರ್ಣಾಂಕ type_dep)
{
  ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name = fname_as_string (type_dep);
  ವೃಕ್ಷ decl, type, init;
  ಗಾತ್ರ_t ಉದ್ದಳತೆ = ಅಕ್ಷರಸರಣಿ_ಉದ್ದ (name);

  type = c_build_array_type (char_type_ಗಂಟು,
			     build_ಸೂಚ್ಯಂಕ_type (ಗಾತ್ರ_int (ಉದ್ದಳತೆ)));
  type = c_build_qualified_type (type, TYPE_QUAL_CONST);

  decl = build_decl (loc, VAR_DECL, id, type);

  ವೃಕ್ಷ_STATIC (decl) = 1;
  ವೃಕ್ಷ_READONLY (decl) = 1;
  DECL_ARTIFICIAL (decl) = 1;

  init = build_string (ಉದ್ದಳತೆ + 1, name);
  ಬಿಡುಗಡೆ (const_cast<ಅಕ್ಷರ *> (name));
  ವೃಕ್ಷ_TYPE (init) = type;
  DECL_INITIAL (decl) = init;

  ವೃಕ್ಷ_ಬಳಸಿದ (decl) = 1;

  ಆದರೆ (current_function_decl
      /* For invalid programs like this:

         void foo()
         const char* p = __FUNCTION__;

	 the __FUNCTION__ is believed to appear in K&R style function
	 parameter declarator.  In that case we still don't have
	 function_scope.  */
      && current_function_scope)
    {
      DECL_CONTEXT (decl) = current_function_decl;
      bind (id, decl, current_function_scope,
	    /*invisible=*/ಸುಳ್ಳು, /*nested=*/ಸುಳ್ಳು, UNKNOWN_LOCATION);
    }

  ಮುಕ್ತಾಯ_decl (decl, loc, init, NULL_ವೃಕ್ಷ, NULL_ವೃಕ್ಷ);

  ಹಿಂತಿರುಗಿ decl;
}

ವೃಕ್ಷ
c_builtin_function (ವೃಕ್ಷ decl)
{
  ವೃಕ್ಷ type = ವೃಕ್ಷ_TYPE (decl);
  ವೃಕ್ಷ   id = DECL_NAME (decl);

  ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name = IDENTIFIER_ಸೂಚಕ (id);
  C_DECL_BUILTIN_PROTOTYPE (decl) = prototype_p (type);

  /* Should never be called on a symbol with a preexisting meaning.  */
  gcc_assert (!I_ಚಿಹ್ನೆ_BINDING (id));

  bind (id, decl, external_scope, /*invisible=*/ನಿಜ, /*nested=*/ಸುಳ್ಳು,
	UNKNOWN_LOCATION);

  /* Builtins in the implementation namespace are made visible without
     needing to be explicitly declared.  See push_file_scope.  */
  ಆದರೆ (name[0] == '_' && (name[1] == '_' || ISUPPER (name[1])))
    {
      DECL_CHAIN (decl) = visible_builtins;
      visible_builtins = decl;
    }

  ಹಿಂತಿರುಗಿ decl;
}

ವೃಕ್ಷ
c_builtin_function_ext_scope (ವೃಕ್ಷ decl)
{
  ವೃಕ್ಷ type = ವೃಕ್ಷ_TYPE (decl);
  ವೃಕ್ಷ   id = DECL_NAME (decl);

  ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name = IDENTIFIER_ಸೂಚಕ (id);
  C_DECL_BUILTIN_PROTOTYPE (decl) = prototype_p (type);

  ಆದರೆ (external_scope)
    bind (id, decl, external_scope, /*invisible=*/ಸುಳ್ಳು, /*nested=*/ಸುಳ್ಳು,
	  UNKNOWN_LOCATION);

  /* Builtins in the implementation namespace are made visible without
     needing to be explicitly declared.  See push_file_scope.  */
  ಆದರೆ (name[0] == '_' && (name[1] == '_' || ISUPPER (name[1])))
    {
      DECL_CHAIN (decl) = visible_builtins;
      visible_builtins = decl;
    }

  ಹಿಂತಿರುಗಿ decl;
}

/* Implement LANG_HOOKS_SIMULATE_BUILTIN_FUNCTION_DECL.  */

ವೃಕ್ಷ
c_simulate_builtin_function_decl (ವೃಕ್ಷ decl)
{
  ವೃಕ್ಷ type = ವೃಕ್ಷ_TYPE (decl);
  C_DECL_BUILTIN_PROTOTYPE (decl) = prototype_p (type);
  ಹಿಂತಿರುಗಿ pushdecl (decl);
}

/* Warn about attributes in a context where they are unused
   (attribute-declarations, except for the "fallthrough" case, and
   attributes on statements).  */

ಶೂನ್ಯ
c_warn_ಬಳಸದ_ಗುಣಲಕ್ಷಣಗಳು (ವೃಕ್ಷ attrs)
{
  ಗಾಗಿ (ವೃಕ್ಷ t = attrs; t != NULL_ವೃಕ್ಷ; t = ವೃಕ್ಷ_CHAIN (t))
    ಆದರೆ (get_attribute_namespace (t) == NULL_ವೃಕ್ಷ)
      /* The specifications of standard attributes mean this is a
	 constraint violation.  */
      pedwarn (ಒಳಹರಿವು_location, OPT_Wattributes, "%qE attribute ignored",
	       get_attribute_name (t));
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!attribute_ignored_p (t))
      warning (OPT_Wattributes, "%qE attribute ignored",
	       get_attribute_name (t));
}

/* Warn for standard attributes being applied to a type that is not
   being defined, where that is a constraint violation, and return a
   list of attributes with them removed.  */

ವೃಕ್ಷ
c_warn_type_ಗುಣಲಕ್ಷಣಗಳು (ವೃಕ್ಷ type, ವೃಕ್ಷ attrs)
{
  ವೃಕ್ಷ *attr_ptr = &attrs;
  ಆಗ (*attr_ptr)
    ಆದರೆ (get_attribute_namespace (*attr_ptr) == NULL_ವೃಕ್ಷ)
      {
	ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (type) == FUNCTION_TYPE)
	  {
	    ವೃಕ್ಷ name = get_attribute_name (*attr_ptr);
	    /* [[unsequenced]] and [[reproducible]] is fine on function
	       types that aren't being defined.  */
	    ಆದರೆ (is_attribute_p ("unsequenced", name)
		|| is_attribute_p ("reproducible", name))
	      {
		attr_ptr = &ವೃಕ್ಷ_CHAIN (*attr_ptr);
		ಮುಂದುವರಿ;
	      }
	  }
	pedwarn (ಒಳಹರಿವು_location, OPT_Wattributes, "%qE attribute ignored",
		 get_attribute_name (*attr_ptr));
	*attr_ptr = ವೃಕ್ಷ_CHAIN (*attr_ptr);
      }
    ಇಲ್ಲದಿದ್ದರೆ
      attr_ptr = &ವೃಕ್ಷ_CHAIN (*attr_ptr);
  ಹಿಂತಿರುಗಿ attrs;
}

/* Called when a declaration is seen that contains no names to declare.
   If its type is a reference to a structure, union or enum inherited
   from a containing scope, shadow that tag name for the current scope
   with a forward reference.
   If its type defines a new named structure or union
   or defines an enum, it is valid but we need not do anything here.
   Otherwise, it is an error.  */

ಶೂನ್ಯ
shadow_ಟ್ಯಾಗ್ (ಸ್ಥಿರಾಂಕ ರಚನೆ c_declspecs *declspecs)
{
  shadow_ಟ್ಯಾಗ್_warned (declspecs, 0);
}

/* WARNED is 1 if we have done a pedwarn, 2 if we have done a warning,
   but no pedwarn.  */
ಶೂನ್ಯ
shadow_ಟ್ಯಾಗ್_warned (ಸ್ಥಿರಾಂಕ ರಚನೆ c_declspecs *declspecs, ಪೂರ್ಣಾಂಕ warned)
{
  ತಾರ್ಕಿಕ ಸಿಕ್ಕಿತು_ಟ್ಯಾಗ್ = ಸುಳ್ಳು;

  ಆದರೆ (declspecs->type && !declspecs->default_int_p && !declspecs->typedef_p)
    {
      ವೃಕ್ಷ ಮೌಲ್ಯ = declspecs->type;
      ಎಣಿಕೆ ವೃಕ್ಷ_ಸಂಕೇತ_2 ಸಂಕೇತ_2 = ವೃಕ್ಷ_ಸಂಕೇತ (ಮೌಲ್ಯ);

      ಆದರೆ (ಸಂಕೇತ_2 == ದಾಖಲೆ_TYPE || ಸಂಕೇತ_2 == UNION_TYPE || ಸಂಕೇತ_2 == ENUMERAL_TYPE)
	/* Used to test also that TYPE_SIZE (value) != 0.
	   That caused warning for `struct foo;' at top level in the file.  */
	{
	  ವೃಕ್ಷ name = TYPE_NAME (ಮೌಲ್ಯ);
	  ವೃಕ್ಷ t;

	  ಸಿಕ್ಕಿತು_ಟ್ಯಾಗ್ = ನಿಜ;

	  ಆದರೆ (declspecs->restrict_p)
	    {
	      error ("invalid use of %<restrict%>");
	      warned = 1;
	    }

	  ಆದರೆ (ಒಳ_underspecified_init)
	    {
	      /* This can only occur with extensions such as statement
		 expressions, but is still appropriate as an error to
		 avoid types declared in such a context escaping to
		 the type of an auto variable.  */
	      error ("%qT declared in underspecified object initializer",
		     ಮೌಲ್ಯ);
	      warned = 1;
	    }

	  ಆದರೆ (name == NULL_ವೃಕ್ಷ)
	    {
	      ಆದರೆ (warned != 1 && ಸಂಕೇತ_2 != ENUMERAL_TYPE)
		/* Empty unnamed enum OK */
		{
		  pedwarn (ಒಳಹರಿವು_location, 0,
			   "unnamed struct/union that defines no instances");
		  warned = 1;
		}
	    }
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (declspecs->typespec_ಬಗೆ != ctsk_tagdef
                   && declspecs->typespec_ಬಗೆ != ctsk_tagfirstref
		   && declspecs->typespec_ಬಗೆ != ctsk_tagfirstref_attrs
		   && declspecs->storage_class != csc_none)
	    {
	      ಆದರೆ (warned != 1)
		pedwarn (ಒಳಹರಿವು_location, 0,
			 "empty declaration with storage class specifier "
			 "does not redeclare tag");
	      warned = 1;
	      pending_xref_error ();
	    }
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (declspecs->typespec_ಬಗೆ != ctsk_tagdef
                   && declspecs->typespec_ಬಗೆ != ctsk_tagfirstref
                   && declspecs->typespec_ಬಗೆ != ctsk_tagfirstref_attrs
		   && (declspecs->const_p
		       || declspecs->volatile_p
		       || declspecs->atomic_p
		       || declspecs->restrict_p
		       || declspecs->ವಿಳಾಸ_space))
	    {
	      ಆದರೆ (warned != 1)
		pedwarn (ಒಳಹರಿವು_location, 0,
			 "empty declaration with type qualifier "
			  "does not redeclare tag");
	      warned = 1;
	      pending_xref_error ();
	    }
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (declspecs->typespec_ಬಗೆ != ctsk_tagdef
                   && declspecs->typespec_ಬಗೆ != ctsk_tagfirstref
                   && declspecs->typespec_ಬಗೆ != ctsk_tagfirstref_attrs
		   && declspecs->alignas_p)
	    {
	      ಆದರೆ (warned != 1)
		pedwarn (ಒಳಹರಿವು_location, 0,
			 "empty declaration with %<_Alignas%> "
			  "does not redeclare tag");
	      warned = 1;
	      pending_xref_error ();
	    }
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (declspecs->typespec_ಬಗೆ != ctsk_tagdef
		   && declspecs->typespec_ಬಗೆ != ctsk_tagfirstref
		   && declspecs->typespec_ಬಗೆ != ctsk_tagfirstref_attrs
		   && ಸಂಕೇತ_2 == ENUMERAL_TYPE
		   && !declspecs->enum_type_specifier_ref_p)
	    {
	      ತಾರ್ಕಿಕ warned_enum = ಸುಳ್ಳು;
	      ಆದರೆ (warned != 1)
		warned_enum = pedwarn (ಒಳಹರಿವು_location, OPT_Wpedantic,
				       "empty declaration of %<enum%> type "
				       "does not redeclare tag");
	      ಆದರೆ (warned_enum)
		warned = 1;
	      pending_xref_error ();
	    }
	  ಇಲ್ಲದಿದ್ದರೆ
	    {
	      pending_invalid_xref = NULL_ವೃಕ್ಷ;
	      t = lookup_ಟ್ಯಾಗ್ (ಸಂಕೇತ_2, name, ನಿಜ, ಖಾಲಿ);

	      ಆದರೆ (t == NULL_ವೃಕ್ಷ)
		{
		  t = make_ಗಂಟು (ಸಂಕೇತ_2);
		  ಆದರೆ (flag_isoc23 || ಸಂಕೇತ_2 == ENUMERAL_TYPE)
		    ಗಣ_TYPE_STRUCTURAL_EQUALITY (t);
		  pushtag (ಒಳಹರಿವು_location, name, t);
		}
	    }
	}
      ಇಲ್ಲದಿದ್ದರೆ
	{
	  ಆದರೆ (warned != 1 && !ಒಳ_system_ಶೀರ್ಷಿಕೆ_at (ಒಳಹರಿವು_location))
	    {
	      pedwarn (ಒಳಹರಿವು_location, 0,
		       "useless type name in empty declaration");
	      warned = 1;
	    }
	}
    }
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (warned != 1 && !ಒಳ_system_ಶೀರ್ಷಿಕೆ_at (ಒಳಹರಿವು_location)
	   && declspecs->typedef_p)
    {
      pedwarn (ಒಳಹರಿವು_location, 0, "useless type name in empty declaration");
      warned = 1;
    }

  pending_invalid_xref = NULL_ವೃಕ್ಷ;

  ಆದರೆ (declspecs->inline_p)
    {
      error ("%<inline%> in empty declaration");
      warned = 1;
    }

  ಆದರೆ (declspecs->noreturn_p)
    {
      error ("%<_Noreturn%> in empty declaration");
      warned = 1;
    }

  ಆದರೆ (declspecs->constexpr_p)
    {
      error ("%<constexpr%> in empty declaration");
      warned = 1;
    }

  ಆದರೆ (current_scope == file_scope && declspecs->storage_class == csc_auto)
    {
      error ("%<auto%> in file-scope empty declaration");
      warned = 1;
    }

  ಆದರೆ (current_scope == file_scope && declspecs->storage_class == csc_ರಿಜಿಸ್ಟರ್)
    {
      error ("%<register%> in file-scope empty declaration");
      warned = 1;
    }

  ಆದರೆ (declspecs->enum_type_specifier_ref_p && !warned)
    {
      ಆದರೆ (declspecs->storage_class != csc_none)
	{
	  error ("storage class specifier in empty declaration with %<enum%> "
		 "underlying type");
	  warned = 1;
	}
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (declspecs->thread_p)
	{
	  error ("%qs in empty declaration with %<enum%> underlying type",
		 declspecs->thread_gnu_p ? "__thread" : "_Thread_local");
	  warned = 1;
	}
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (declspecs->const_p
	       || declspecs->volatile_p
	       || declspecs->atomic_p
	       || declspecs->restrict_p
	       || declspecs->ವಿಳಾಸ_space)
	{
	  error ("type qualifier in empty declaration with %<enum%> "
		 "underlying type");
	  warned = 1;
	}
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (declspecs->alignas_p)
	{
	  error ("%<alignas%> in empty declaration with %<enum%> "
		 "underlying type");
	  warned = 1;
	}
    }

  ಆದರೆ (!warned && !ಒಳ_system_ಶೀರ್ಷಿಕೆ_at (ಒಳಹರಿವು_location)
      && declspecs->storage_class != csc_none)
    {
      warning (0, "useless storage class specifier in empty declaration");
      warned = 2;
    }

  ಆದರೆ (!warned && !ಒಳ_system_ಶೀರ್ಷಿಕೆ_at (ಒಳಹರಿವು_location) && declspecs->thread_p)
    {
      warning (0, "useless %qs in empty declaration",
	       declspecs->thread_gnu_p ? "__thread" : "_Thread_local");
      warned = 2;
    }

  ಆದರೆ (!warned
      && !ಒಳ_system_ಶೀರ್ಷಿಕೆ_at (ಒಳಹರಿವು_location)
      && (declspecs->const_p
	  || declspecs->volatile_p
	  || declspecs->atomic_p
	  || declspecs->restrict_p
	  || declspecs->ವಿಳಾಸ_space))
    {
      warning (0, "useless type qualifier in empty declaration");
      warned = 2;
    }

  ಆದರೆ (!warned && !ಒಳ_system_ಶೀರ್ಷಿಕೆ_at (ಒಳಹರಿವು_location)
      && declspecs->alignas_p)
    {
      warning (0, "useless %<_Alignas%> in empty declaration");
      warned = 2;
    }

  ಆದರೆ (ಸಿಕ್ಕಿತು_ಟ್ಯಾಗ್
      && warned == 2
      && (declspecs->typespec_ಬಗೆ == ctsk_tagref_attrs
	  || declspecs->typespec_ಬಗೆ == ctsk_tagfirstref_attrs))
    {
      /* Standard attributes after the "struct" or "union" keyword are
	 only permitted when the contents of the type are defined, or
	 in the form "struct-or-union attribute-specifier-sequence
	 identifier;".  If the ';' was not present, attributes were
	 diagnosed in the parser.  Here, ensure that any other useless
	 elements of the declaration result in a pedwarn, not just a
	 warning.  Forward declarations of enum types are not part of
	 standard C, but handle them the same.  */
      pedwarn (ಒಳಹರಿವು_location, 0,
	       "invalid use of attributes in empty declaration");
      warned = 1;
    }

  ಆದರೆ (warned != 1)
    {
      ಆದರೆ (declspecs->declspecs_ನೋಡಿದ_p
	  && !declspecs->non_std_attrs_ನೋಡಿದ_p)
	/* An attribute declaration (but not a fallthrough attribute
	   declaration, which was handled separately); warn if there
	   are any attributes being ignored (but not if the attributes
	   were empty).  */
	c_warn_ಬಳಸದ_ಗುಣಲಕ್ಷಣಗಳು (declspecs->attrs);
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!ಸಿಕ್ಕಿತು_ಟ್ಯಾಗ್)
	pedwarn (ಒಳಹರಿವು_location, 0, "empty declaration");
    }
}


/* Return the qualifiers from SPECS as a bitwise OR of TYPE_QUAL_*
   bits.  SPECS represents declaration specifiers that the grammar
   only permits to contain type qualifiers and attributes.  */

ಪೂರ್ಣಾಂಕ
quals_from_declspecs (ಸ್ಥಿರಾಂಕ ರಚನೆ c_declspecs *specs)
{
  ಪೂರ್ಣಾಂಕ quals = ((specs->const_p ? TYPE_QUAL_CONST : 0)
	       | (specs->volatile_p ? TYPE_QUAL_VOLATILE : 0)
	       | (specs->restrict_p ? TYPE_QUAL_RESTRICT : 0)
	       | (specs->atomic_p ? TYPE_QUAL_ATOMIC : 0)
	       | (ENCODE_QUAL_ADDR_SPACE (specs->ವಿಳಾಸ_space)));
  gcc_assert (!specs->type
	      && !specs->decl_attr
	      && specs->typespec_ಶಬ್ದ == cts_none
	      && specs->storage_class == csc_none
	      && !specs->typedef_p
	      && !specs->explicit_signed_p
	      && !specs->deprecated_p
	      && !specs->unavailable_p
	      && !specs->long_p
	      && !specs->long_long_p
	      && !specs->short_p
	      && !specs->signed_p
	      && !specs->unsigned_p
	      && !specs->complex_p
	      && !specs->inline_p
	      && !specs->noreturn_p
	      && !specs->thread_p);
  ಹಿಂತಿರುಗಿ quals;
}

/* Construct an array declarator.  LOC is the location of the
   beginning of the array (usually the opening brace).  EXPR is the
   expression inside [], or NULL_TREE.  QUALS are the type qualifiers
   inside the [] (to be applied to the pointer to which a parameter
   array is converted).  STATIC_P is true if "static" is inside the
   [], false otherwise.  VLA_UNSPEC_P is true if the array is [*], a
   VLA of unspecified length which is nevertheless a complete type,
   false otherwise.  The field for the contained declarator is left to
   be filled in by set_array_declarator_inner.  */

ರಚನೆ c_declarator *
build_array_declarator (location_t loc,
			ವೃಕ್ಷ ಅಭಿವ್ಯಕ್ತಿ, ರಚನೆ c_declspecs *quals, ತಾರ್ಕಿಕ static_p,
			ತಾರ್ಕಿಕ vla_unspec_p)
{
  ರಚನೆ c_declarator *declarator = XOBNEW (&parser_obstack,
					    ರಚನೆ c_declarator);
  declarator->id_loc = loc;
  declarator->ಬಗೆ = cdk_array;
  declarator->declarator = 0;
  declarator->u.array.dimen = ಅಭಿವ್ಯಕ್ತಿ;
  ಆದರೆ (quals)
    {
      declarator->u.array.attrs = quals->attrs;
      declarator->u.array.quals = quals_from_declspecs (quals);
    }
  ಇಲ್ಲದಿದ್ದರೆ
    {
      declarator->u.array.attrs = NULL_ವೃಕ್ಷ;
      declarator->u.array.quals = 0;
    }
  declarator->u.array.static_p = static_p;
  declarator->u.array.vla_unspec_p = vla_unspec_p;
  ಆದರೆ (static_p || quals != ಖಾಲಿ)
    pedwarn_c90 (loc, OPT_Wpedantic,
		 "ISO C90 does not support %<static%> or type "
		 "qualifiers in parameter array declarators");
  ಆದರೆ (vla_unspec_p)
    {
      pedwarn_c90 (loc, OPT_Wpedantic,
		   "ISO C90 does not support %<[*]%> array declarators");
      ಆದರೆ (current_scope->parm_flag)
	current_scope->had_vla_unspec = ನಿಜ;
    }
  ಹಿಂತಿರುಗಿ declarator;
}

/* Set the contained declarator of an array declarator.  DECL is the
   declarator, as constructed by build_array_declarator; INNER is what
   appears on the left of the [].  */

ರಚನೆ c_declarator *
ಗಣ_array_declarator_inner (ರಚನೆ c_declarator *decl,
			    ರಚನೆ c_declarator *inner)
{
  decl->declarator = inner;
  ಹಿಂತಿರುಗಿ decl;
}

/* Determine whether TYPE is a one-element array type "[1]".  */
ಸ್ಥಿರ ತಾರ್ಕಿಕ
one_element_array_type_p (const_ವೃಕ್ಷ type)
{
  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (type) != ARRAY_TYPE)
    ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
  ಹಿಂತಿರುಗಿ integer_zerop (array_type_nelts_minus_one (type));
}

/* Determine whether TYPE is a zero-length array type "[0]".  */
ತಾರ್ಕಿಕ
zero_ಉದ್ದಳತೆ_array_type_p (const_ವೃಕ್ಷ type)
{
  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (type) == ARRAY_TYPE
      && COMPLETE_TYPE_P (type)
      && TYPE_DOMAIN (type) != NULL_ವೃಕ್ಷ
      && (TYPE_MAX_ಮೌಲ್ಯ (TYPE_DOMAIN (type)) == NULL_ವೃಕ್ಷ
	  || integer_all_onesp (TYPE_MAX_ಮೌಲ್ಯ (TYPE_DOMAIN (type)))))
    ಹಿಂತಿರುಗಿ ನಿಜ;
  ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
}

/* INIT is a constructor that forms DECL's initializer.  If the final
   element initializes a flexible array field, adjust the size of the
   DECL with the initializer based on whether the DECL is a union or
   a structure.  */

ಸ್ಥಿರ ಶೂನ್ಯ
ಕೂಡಿಸು_flexible_array_elts_ಗಮ್ಯ_ಗಾತ್ರ (ವೃಕ್ಷ decl, ವೃಕ್ಷ init)
{
  ವೃಕ್ಷ elt, type;

  ಆದರೆ (vec_ಸುರಕ್ಷಿತ_is_ಖಾಲಿಗಳು (CONSTRUCTOR_ELTS (init)))
    ಹಿಂತಿರುಗಿ;

  elt = CONSTRUCTOR_ELTS (init)->ಕೊನೆಯ ().ಮೌಲ್ಯ;
  type = ವೃಕ್ಷ_TYPE (elt);
  ಆದರೆ (flexible_array_member_type_p (type))
    {
      complete_array_type (&type, elt, ಸುಳ್ಳು);
      /* For a structure, add the size of the initializer to the DECL's
	 size.  */
      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (decl)) == ದಾಖಲೆ_TYPE)
	{
	  DECL_ಗಾತ್ರ (decl)
	    = ಗಾತ್ರ_binop (PLUS_ಅಭಿವ್ಯಕ್ತಿ, DECL_ಗಾತ್ರ (decl), TYPE_ಗಾತ್ರ (type));
	  DECL_ಗಾತ್ರ_UNIT (decl)
	    = ಗಾತ್ರ_binop (PLUS_ಅಭಿವ್ಯಕ್ತಿ, DECL_ಗಾತ್ರ_UNIT (decl),
			  TYPE_ಗಾತ್ರ_UNIT (type));
	}
      /* For a union, the DECL's size is the maximum of the current size
	 and the size of the initializer.  */
      ಇಲ್ಲದಿದ್ದರೆ
	{
	  DECL_ಗಾತ್ರ (decl)
	    = ಗಾತ್ರ_binop (MAX_ಅಭಿವ್ಯಕ್ತಿ, DECL_ಗಾತ್ರ (decl), TYPE_ಗಾತ್ರ (type));
	  DECL_ಗಾತ್ರ_UNIT (decl)
	    = ಗಾತ್ರ_binop (MAX_ಅಭಿವ್ಯಕ್ತಿ, DECL_ಗಾತ್ರ_UNIT (decl),
			  TYPE_ಗಾತ್ರ_UNIT (type));
	}
    }
}

/* Decode a "typename", such as "int **", returning a ..._TYPE node.
   Set *EXPR, if EXPR not NULL, to any expression to be evaluated
   before the type name, and set *EXPR_CONST_OPERANDS, if
   EXPR_CONST_OPERANDS not NULL, to indicate whether the type name may
   appear in a constant expression.  */

ವೃಕ್ಷ
groktypename (ರಚನೆ c_type_name *type_name, ವೃಕ್ಷ *ಅಭಿವ್ಯಕ್ತಿ,
	      ತಾರ್ಕಿಕ *ಅಭಿವ್ಯಕ್ತಿ_const_operands)
{
  ವೃಕ್ಷ type;
  ವೃಕ್ಷ attrs = type_name->specs->attrs;

  type_name->specs->attrs = NULL_ವೃಕ್ಷ;

  type = grokdeclarator (type_name->declarator, type_name->specs, TYPENAME,
			 ಸುಳ್ಳು, ಖಾಲಿ, &attrs, ಅಭಿವ್ಯಕ್ತಿ, ಅಭಿವ್ಯಕ್ತಿ_const_operands,
			 DEPRECATED_ಸಾಮಾನ್ಯ);

  /* Apply attributes.  */
  attrs = c_warn_type_ಗುಣಲಕ್ಷಣಗಳು (type, attrs);
  decl_ಗುಣಲಕ್ಷಣಗಳು (&type, attrs, 0);

  ಹಿಂತಿರುಗಿ type;
}


/* Decode a "typename", such as "int **", returning a ..._TYPE node,
   as for groktypename but setting the context to GENERIC_ASSOC.  */

ವೃಕ್ಷ
grokgenassoc (ರಚನೆ c_type_name *type_name)
{
  ವೃಕ್ಷ type;
  ವೃಕ್ಷ attrs = type_name->specs->attrs;

  type_name->specs->attrs = NULL_ವೃಕ್ಷ;

  type = grokdeclarator (type_name->declarator, type_name->specs, GENERIC_ASSOC,
			 ಸುಳ್ಳು, ಖಾಲಿ, &attrs, ಖಾಲಿ, ಖಾಲಿ, DEPRECATED_ಸಾಮಾನ್ಯ);

  /* Apply attributes.  */
  attrs = c_warn_type_ಗುಣಲಕ್ಷಣಗಳು (type, attrs);
  decl_ಗುಣಲಕ್ಷಣಗಳು (&type, attrs, 0);

  ಹಿಂತಿರುಗಿ type;
}


/* Looks up the most recent pushed declaration corresponding to DECL.  */

ಸ್ಥಿರ ವೃಕ್ಷ
lookup_ಕೊನೆಯ_decl (ವೃಕ್ಷ decl)
{
  ವೃಕ್ಷ ಕೊನೆಯ_decl = lookup_name (DECL_NAME (decl));
  ಆದರೆ (!ಕೊನೆಯ_decl)
    ಕೊನೆಯ_decl = lookup_name_ಒಳ_scope (DECL_NAME (decl), external_scope);
  ಹಿಂತಿರುಗಿ ಕೊನೆಯ_decl;
}

/* Wrapper for decl_attributes that adds some implicit attributes
   to VAR_DECLs or FUNCTION_DECLs.  */

ಸ್ಥಿರ ವೃಕ್ಷ
c_decl_ಗುಣಲಕ್ಷಣಗಳು (ವೃಕ್ಷ *ಗಂಟು, ವೃಕ್ಷ ಗುಣಲಕ್ಷಣಗಳು, ಪೂರ್ಣಾಂಕ flags)
{
  /* Add implicit "omp declare target" attribute if requested.  */
  ಆದರೆ (vec_ಸುರಕ್ಷಿತ_ಉದ್ದಳತೆ (current_omp_declare_ಗುರಿ_attribute)
      && ((VAR_P (*ಗಂಟು) && is_global_var (*ಗಂಟು))
	  || ವೃಕ್ಷ_ಸಂಕೇತ (*ಗಂಟು) == FUNCTION_DECL))
    {
      ಆದರೆ (VAR_P (*ಗಂಟು) && !omp_mappable_type (ವೃಕ್ಷ_TYPE (*ಗಂಟು)))
	ಗುಣಲಕ್ಷಣಗಳು = ವೃಕ್ಷ_cons (get_identifier ("omp declare target implicit"),
				NULL_ವೃಕ್ಷ, ಗುಣಲಕ್ಷಣಗಳು);
      ಇಲ್ಲದಿದ್ದರೆ
	ಗುಣಲಕ್ಷಣಗಳು = ವೃಕ್ಷ_cons (get_identifier ("omp declare target"),
				NULL_ವೃಕ್ಷ, ಗುಣಲಕ್ಷಣಗಳು);
      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (*ಗಂಟು) == FUNCTION_DECL)
	{
	  ಪೂರ್ಣಾಂಕ device_type
	    = current_omp_declare_ಗುರಿ_attribute->ಕೊನೆಯ ().device_type;
	  device_type = MAX (device_type, 0);
	  ಆದರೆ ((device_type & OMP_CLAUSE_DEVICE_TYPE_HOST) != 0
	      && !lookup_attribute ("omp declare target host", ಗುಣಲಕ್ಷಣಗಳು))
	    ಗುಣಲಕ್ಷಣಗಳು
	      = ವೃಕ್ಷ_cons (get_identifier ("omp declare target host"),
			   NULL_ವೃಕ್ಷ, ಗುಣಲಕ್ಷಣಗಳು);
	  ಆದರೆ ((device_type & OMP_CLAUSE_DEVICE_TYPE_NOHOST) != 0
	      && !lookup_attribute ("omp declare target nohost", ಗುಣಲಕ್ಷಣಗಳು))
	    ಗುಣಲಕ್ಷಣಗಳು
	      = ವೃಕ್ಷ_cons (get_identifier ("omp declare target nohost"),
			   NULL_ವೃಕ್ಷ, ಗುಣಲಕ್ಷಣಗಳು);

	  ಪೂರ್ಣಾಂಕ ಪರೋಕ್ಷ
	    = current_omp_declare_ಗುರಿ_attribute->ಕೊನೆಯ ().ಪರೋಕ್ಷ;
	  ಆದರೆ (ಪರೋಕ್ಷ && !lookup_attribute ("omp declare target indirect",
					     ಗುಣಲಕ್ಷಣಗಳು))
	    ಗುಣಲಕ್ಷಣಗಳು
	      = ವೃಕ್ಷ_cons (get_identifier ("omp declare target indirect"),
			   NULL_ವೃಕ್ಷ, ಗುಣಲಕ್ಷಣಗಳು);
	}
    }

  ಆದರೆ (flag_openmp || flag_openmp_simd)
    {
      ತಾರ್ಕಿಕ diagnosed = ಸುಳ್ಳು;
      ಗಾಗಿ (ವೃಕ್ಷ *pa = &ಗುಣಲಕ್ಷಣಗಳು; *pa; )
	{
	  ಆದರೆ (is_attribute_namespace_p ("omp", *pa))
	    {
	      ವೃಕ್ಷ name = get_attribute_name (*pa);
	      ಆದರೆ (is_attribute_p ("directive", name)
		  || is_attribute_p ("sequence", name)
		  || is_attribute_p ("decl", name))
		{
		  ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *p = ಖಾಲಿ;
		  ಆದರೆ (ವೃಕ್ಷ_ಮೌಲ್ಯ (*pa) == NULL_ವೃಕ್ಷ)
		    p = IDENTIFIER_ಸೂಚಕ (name);
		  ಗಾಗಿ (ವೃಕ್ಷ a = ವೃಕ್ಷ_ಮೌಲ್ಯ (*pa); a; a = ವೃಕ್ಷ_CHAIN (a))
		    {
		      ವೃಕ್ಷ d = ವೃಕ್ಷ_ಮೌಲ್ಯ (a);
		      gcc_assert (ವೃಕ್ಷ_ಸಂಕೇತ (d) == C_TOKEN_VEC);
		      ಆದರೆ (ವೃಕ್ಷ_ಬಹಿರಂಗ (d)
			  && (VAR_P (*ಗಂಟು)
			      || ವೃಕ್ಷ_ಸಂಕೇತ (*ಗಂಟು) == FUNCTION_DECL)
			  && c_maybe_parse_omp_decl (*ಗಂಟು, d))
			ಮುಂದುವರಿ;
		      p = ವೃಕ್ಷ_ಬಹಿರಂಗ (d) ? "decl" : "directive";
		    }
		  ಆದರೆ (p && !diagnosed)
		    {
		      error ("%<omp::%s%> not allowed to be specified in "
			     "this context", p);
		      diagnosed = ನಿಜ;
		    }
		  ಆದರೆ (p)
		    {
		      *pa = ವೃಕ್ಷ_CHAIN (*pa);
		      ಮುಂದುವರಿ;
		    }
		}
	    }
	  pa = &ವೃಕ್ಷ_CHAIN (*pa);
	}
    }

  /* Look up the current declaration with all the attributes merged
     so far so that attributes on the current declaration that's
     about to be pushed that conflict with the former can be detected,
     diagnosed, and rejected as appropriate.  To match the C++ FE, do
     not pass an error_mark_node when we found an undeclared variable.  */
  ವೃಕ್ಷ ಕೊನೆಯ_decl = lookup_ಕೊನೆಯ_decl (*ಗಂಟು);
  ಆದರೆ (ಕೊನೆಯ_decl == error_mark_ಗಂಟು)
    ಕೊನೆಯ_decl = NULL_ವೃಕ್ಷ;
  ವೃಕ್ಷ attr = decl_ಗುಣಲಕ್ಷಣಗಳು (ಗಂಟು, ಗುಣಲಕ್ಷಣಗಳು, flags, ಕೊನೆಯ_decl);
  ಆದರೆ (VAR_P (*ಗಂಟು) && DECL_THREAD_LOCAL_P (*ಗಂಟು))
    {
      // tls_model attribute can set a stronger TLS access model.
      tls_model model = DECL_TLS_MODEL (*ಗಂಟು);
      tls_model default_model = decl_default_tls_model (*ಗಂಟು);
      ಆದರೆ (default_model > model)
	ಗಣ_decl_tls_model (*ಗಂಟು, default_model);
    }
  ಹಿಂತಿರುಗಿ attr;
}


/* Decode a declarator in an ordinary declaration or data definition.
   This is called as soon as the type information and variable name
   have been parsed, before parsing the initializer if any.
   Here we create the ..._DECL node, fill in its type,
   and (if DO_PUSH) put it on the list of decls for the current context.
   When nonnull, set *LASTLOC to the location of the prior declaration
   of the same entity if one exists.
   The ..._DECL node is returned as the value.

   Exception: for arrays where the length is not specified,
   the type is left null, to be filled in by `finish_decl'.

   Function definitions do not come here; they go to start_function
   instead.  However, external and forward declarations of functions
   do go through here.  Structure field declarations are done by
   grokfield and not through here.  */

ವೃಕ್ಷ
ಆರಂಭ_decl (ರಚನೆ c_declarator *declarator, ರಚನೆ c_declspecs *declspecs,
	    ತಾರ್ಕಿಕ initialized, ವೃಕ್ಷ ಗುಣಲಕ್ಷಣಗಳು, ತಾರ್ಕಿಕ do_ತಳ್ಳು /* = true */,
	    location_t *lastloc /* = NULL */)
{
  ವೃಕ್ಷ decl;
  ವೃಕ್ಷ old_decl;
  ವೃಕ್ಷ tem;
  ವೃಕ್ಷ ಅಭಿವ್ಯಕ್ತಿ = NULL_ವೃಕ್ಷ;
  ಎಣಿಕೆ deprecated_ಸ್ಥಿತಿಗಳು deprecated_state = DEPRECATED_ಸಾಮಾನ್ಯ;

  /* An object declared as __attribute__((unavailable)) suppresses
     warnings and errors from __attribute__((deprecated/unavailable))
     components.
     An object declared as __attribute__((deprecated)) suppresses
     warnings of uses of other deprecated items.  */
  ಆದರೆ (lookup_attribute ("unavailable", ಗುಣಲಕ್ಷಣಗಳು))
    deprecated_state = UNAVAILABLE_DEPRECATED_SUPPRESS;
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (lookup_attribute ("deprecated", ಗುಣಲಕ್ಷಣಗಳು))
    deprecated_state = DEPRECATED_SUPPRESS;

  decl = grokdeclarator (declarator, declspecs,
			 ಸಾಮಾನ್ಯ, initialized, ಖಾಲಿ, &ಗುಣಲಕ್ಷಣಗಳು, &ಅಭಿವ್ಯಕ್ತಿ, ಖಾಲಿ,
			 deprecated_state);
  ಆದರೆ (!decl || decl == error_mark_ಗಂಟು)
    ಹಿಂತಿರುಗಿ NULL_ವೃಕ್ಷ;

  old_decl = lookup_ಕೊನೆಯ_decl (decl);

  ಆದರೆ (ವೃಕ್ಷ lastdecl = lastloc ? old_decl : NULL_ವೃಕ್ಷ)
    ಆದರೆ (lastdecl != error_mark_ಗಂಟು)
      *lastloc = DECL_ಮೂಲ_LOCATION (lastdecl);

  /* Make sure the size expression is evaluated at this point.  */
  ಆದರೆ (ಅಭಿವ್ಯಕ್ತಿ && !current_scope->parm_flag)
    ಕೂಡಿಸು_stmt (fold_convert (void_type_ಗಂಟು, ಅಭಿವ್ಯಕ್ತಿ));

  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (decl) != FUNCTION_DECL && MAIN_NAME_P (DECL_NAME (decl))
      && ವೃಕ್ಷ_ಬಹಿರಂಗ (decl))
    warning (OPT_Wmain, "%q+D is usually a function", decl);

  ಆದರೆ (warn_missing_variable_declarations && VAR_P (decl)
      && !DECL_EXTERNAL (decl) && ವೃಕ್ಷ_ಬಹಿರಂಗ (decl) && old_decl == NULL_ವೃಕ್ಷ)
    warning_at (DECL_ಮೂಲ_LOCATION (decl), OPT_Wmissing_variable_declarations,
		"no previous declaration for %qD", decl);

  ಆದರೆ (initialized)
    /* Is it valid for this decl to have an initializer at all?
       If not, set INITIALIZED to zero, which will indirectly
       tell 'finish_decl' to ignore the initializer once it is parsed.  */
    ಆಯ್ಕೆ (ವೃಕ್ಷ_ಸಂಕೇತ (decl))
      {
      ಸ್ಥಿತಿ TYPE_DECL:
	error ("typedef %qD is initialized (use %<__typeof__%> instead)", decl);
	initialized = ಸುಳ್ಳು;
	ನಿಲ್ಲಿಸು;

      ಸ್ಥಿತಿ FUNCTION_DECL:
	error ("function %qD is initialized like a variable", decl);
	initialized = ಸುಳ್ಳು;
	ನಿಲ್ಲಿಸು;

      ಸ್ಥಿತಿ PARM_DECL:
	/* DECL_INITIAL in a PARM_DECL is really DECL_ARG_TYPE.  */
	error ("parameter %qD is initialized", decl);
	initialized = ಸುಳ್ಳು;
	ನಿಲ್ಲಿಸು;

      ಪೂರ್ವನಿಯೋಜಿತ:
	/* Don't allow initializations for incomplete types except for
	   arrays which might be completed by the initialization.  */

	/* This can happen if the array size is an undefined macro.
	   We already gave a warning, so we don't need another one.  */
	ಆದರೆ (ವೃಕ್ಷ_TYPE (decl) == error_mark_ಗಂಟು)
	  initialized = ಸುಳ್ಳು;
	ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (COMPLETE_TYPE_P (ವೃಕ್ಷ_TYPE (decl)))
	  {
	    /* A complete type is ok if size is fixed.  If the size is
	       variable, an empty initializer is OK and nonempty
	       initializers will be diagnosed in the parser.  */
	  }
	ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (decl)) != ARRAY_TYPE)
	  {
	    error ("variable %qD has initializer but incomplete type", decl);
	    initialized = ಸುಳ್ಳು;
	  }
      }

  ಆದರೆ (initialized)
    {
      ಆದರೆ (current_scope == file_scope)
	ವೃಕ್ಷ_STATIC (decl) = 1;

      /* Tell 'pushdecl' this is an initialized decl
	 even though we don't yet have the initializer expression.
	 Also tell 'finish_decl' it may store the real initializer.  */
      DECL_INITIAL (decl) = error_mark_ಗಂಟು;
    }

  /* If this is a function declaration, write a record describing it to the
     prototypes file (if requested).  */

  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (decl) == FUNCTION_DECL)
    gen_aux_info_ದಾಖಲೆ (decl, 0, 0, prototype_p (ವೃಕ್ಷ_TYPE (decl)));

  /* ANSI specifies that a tentative definition which is not merged with
     a non-tentative definition behaves exactly like a definition with an
     initializer equal to zero.  (Section 3.7.2)

     -fno-common gives strict ANSI behavior, though this tends to break
     a large body of code that grew up without this rule.

     Thread-local variables are never common, since there's no entrenched
     body of code to break, and it allows more efficient variable references
     in the presence of dynamic linking.  */

  ಆದರೆ (VAR_P (decl)
      && !initialized
      && ವೃಕ್ಷ_ಬಹಿರಂಗ (decl)
      && !DECL_THREAD_LOCAL_P (decl)
      && !flag_no_common)
    DECL_COMMON (decl) = 1;

  /* Set attributes here so if duplicate decl, will have proper attributes.  */
  c_decl_ಗುಣಲಕ್ಷಣಗಳು (&decl, ಗುಣಲಕ್ಷಣಗಳು, 0);

  /* Handle gnu_inline attribute.  */
  ಆದರೆ (declspecs->inline_p
      && !flag_gnu89_inline
      && ವೃಕ್ಷ_ಸಂಕೇತ (decl) == FUNCTION_DECL
      && (lookup_attribute ("gnu_inline", DECL_ಗುಣಲಕ್ಷಣಗಳು (decl))
	  || current_function_decl))
    {
      ಆದರೆ (declspecs->storage_class == csc_auto && current_scope != file_scope)
	;
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (declspecs->storage_class != csc_static)
	DECL_EXTERNAL (decl) = !DECL_EXTERNAL (decl);
    }

  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (decl) == FUNCTION_DECL
      && DECL_DECLARED_INLINE_P (decl)
      && DECL_UNINLINABLE (decl)
      && lookup_attribute ("noinline", DECL_ಗುಣಲಕ್ಷಣಗಳು (decl)))
    {
      auto_urlify_ಗುಣಲಕ್ಷಣಗಳು sentinel;
      warning (OPT_Wattributes, "inline function %q+D given attribute %qs",
	       decl, "noinline");
    }

  /* C99 6.7.4p3: An inline definition of a function with external
     linkage shall not contain a definition of a modifiable object
     with static storage duration...  */
  ಆದರೆ (VAR_P (decl)
      && current_scope != file_scope
      && ವೃಕ್ಷ_STATIC (decl)
      && !ವೃಕ್ಷ_READONLY (decl)
      && DECL_DECLARED_INLINE_P (current_function_decl)
      && DECL_EXTERNAL (current_function_decl))
    ದಾಖಲೆ_inline_static (ಒಳಹರಿವು_location, current_function_decl,
			  decl, csi_modifiable);

  ಆದರೆ (c_dialect_objc ()
      && VAR_OR_FUNCTION_DECL_P (decl))
      objc_check_global_decl (decl);

  /* To enable versions to be created across TU's we mark and mangle all
     non-default versioned functions.  */
  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (decl) == FUNCTION_DECL
      && !ಗುರಿ_HAS_FMV_ಗುರಿ_ATTRIBUTE
      && get_ಗುರಿ_ಆವೃತ್ತಿ (decl).is_valid ())
    {
      maybe_mark_function_versioned (decl);
      ಆದರೆ (current_scope != file_scope)
	error ("versioned declarations are only allowed at file scope");
    }

  /* Add this decl to the current scope.
     TEM may equal DECL or it may be a previous decl of the same name.  */
  ಆದರೆ (do_ತಳ್ಳು)
    {
      tem = pushdecl (decl);

      ಆದರೆ (initialized && DECL_EXTERNAL (tem))
	{
	  DECL_EXTERNAL (tem) = 0;
	  ವೃಕ್ಷ_STATIC (tem) = 1;
	}

      ಹಿಂತಿರುಗಿ tem;
    }
  ಇಲ್ಲದಿದ್ದರೆ
    ಹಿಂತಿರುಗಿ decl;
}

/* Subroutine of finish_decl. TYPE is the type of an uninitialized object
   DECL or the non-array element type if DECL is an uninitialized array.
   If that type has a const member, diagnose this. */

ಸ್ಥಿರ ಶೂನ್ಯ
diagnose_uninitialized_cst_member (ವೃಕ್ಷ decl, ವೃಕ್ಷ type)
{
  ವೃಕ್ಷ ಕ್ಷೇತ್ರ_2;
  ಗಾಗಿ (ಕ್ಷೇತ್ರ_2 = TYPE_FIELDS (type); ಕ್ಷೇತ್ರ_2; ಕ್ಷೇತ್ರ_2 = ವೃಕ್ಷ_CHAIN (ಕ್ಷೇತ್ರ_2))
    {
      ವೃಕ್ಷ ಕ್ಷೇತ್ರ_type;
      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ಕ್ಷೇತ್ರ_2) != ಕ್ಷೇತ್ರ_DECL)
	ಮುಂದುವರಿ;
      ಕ್ಷೇತ್ರ_type = strip_array_types (ವೃಕ್ಷ_TYPE (ಕ್ಷೇತ್ರ_2));

      ಆದರೆ (TYPE_QUALS (ಕ್ಷೇತ್ರ_type) & TYPE_QUAL_CONST)
      	{
	  auto_diagnostic_ಗುಂಪು d;
	  ಆದರೆ (warning_at (DECL_ಮೂಲ_LOCATION (decl), OPT_Wc___compat,
			  "uninitialized const member in %qT is invalid in C++",
			  strip_array_types (ವೃಕ್ಷ_TYPE (decl))))
	    inform (DECL_ಮೂಲ_LOCATION (ಕ್ಷೇತ್ರ_2), "%qD should be initialized", ಕ್ಷೇತ್ರ_2);
	}

      ಆದರೆ (ದಾಖಲೆ_OR_UNION_TYPE_P (ಕ್ಷೇತ್ರ_type))
	diagnose_uninitialized_cst_member (decl, ಕ್ಷೇತ್ರ_type);
    }
}

/* Finish processing of a declaration;
   install its initial value.
   If ORIGTYPE is not NULL_TREE, it is the original type of INIT.
   If the length of an array type is not known before,
   it must be determined now, from the initial value, or it is an error.

   INIT_LOC is the location of the initial value.  */

ಶೂನ್ಯ
ಮುಕ್ತಾಯ_decl (ವೃಕ್ಷ decl, location_t init_loc, ವೃಕ್ಷ init,
	     ವೃಕ್ಷ origtype, ವೃಕ್ಷ asmspec_ವೃಕ್ಷ)
{
  ವೃಕ್ಷ type;
  ತಾರ್ಕಿಕ was_incomplete = (DECL_ಗಾತ್ರ (decl) == NULL_ವೃಕ್ಷ);
  ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *asmspec = 0;

  /* If a name was specified, get the string.  */
  ಆದರೆ (VAR_OR_FUNCTION_DECL_P (decl)
      && DECL_FILE_SCOPE_P (decl))
    asmspec_ವೃಕ್ಷ = maybe_apply_renaming_pragma (decl, asmspec_ವೃಕ್ಷ);
  ಆದರೆ (asmspec_ವೃಕ್ಷ)
    asmspec = ವೃಕ್ಷ_STRING_ಸೂಚಕ (asmspec_ವೃಕ್ಷ);

  ಆದರೆ (VAR_P (decl)
      && ವೃಕ್ಷ_STATIC (decl)
      && global_bindings_p ())
    /* So decl is a global variable. Record the types it uses
       so that we can decide later to emit debug info for them.  */
    ದಾಖಲೆ_types_ಬಳಸಿದ_by_current_var_decl (decl);

  /* If `start_decl' didn't like having an initialization, ignore it now.  */
  ಆದರೆ (init != NULL_ವೃಕ್ಷ && DECL_INITIAL (decl) == NULL_ವೃಕ್ಷ)
    init = NULL_ವೃಕ್ಷ;

  /* Don't crash if parm is initialized.  */
  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (decl) == PARM_DECL)
    init = NULL_ವೃಕ್ಷ;

  ಆದರೆ (init)
    store_init_ಮೌಲ್ಯ (init_loc, decl, init, origtype);

  ಆದರೆ (c_dialect_objc () && (VAR_OR_FUNCTION_DECL_P (decl)
			    || ವೃಕ್ಷ_ಸಂಕೇತ (decl) == ಕ್ಷೇತ್ರ_DECL))
    objc_check_decl (decl);

  type = ವೃಕ್ಷ_TYPE (decl);

  /* Deduce size of array from initialization, if not already known.
     This is only needed for an initialization in the current scope;
     it must not be done for a file-scope initialization of a
     declaration with external linkage, redeclared in an inner scope
     with the outer declaration shadowed in an intermediate scope.  */
  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (type) == ARRAY_TYPE
      && TYPE_DOMAIN (type) == NULL_ವೃಕ್ಷ
      && ವೃಕ್ಷ_ಸಂಕೇತ (decl) != TYPE_DECL
      && !(ವೃಕ್ಷ_ಬಹಿರಂಗ (decl) && current_scope != file_scope))
    {
      ತಾರ್ಕಿಕ do_default
	= !ವೃಕ್ಷ_STATIC (decl) && !DECL_EXTERNAL (decl);
      ಪೂರ್ಣಾಂಕ failure
	= complete_array_type (&ವೃಕ್ಷ_TYPE (decl), DECL_INITIAL (decl),
			       do_default);

      /* Get the completed type made by complete_array_type.  */
      type = ವೃಕ್ಷ_TYPE (decl);

      ಆಯ್ಕೆ (failure)
	{
	ಸ್ಥಿತಿ 1:
	  error ("initializer fails to determine size of %q+D", decl);
	  ನಿಲ್ಲಿಸು;

	ಸ್ಥಿತಿ 2:
	  ಆದರೆ (do_default)
	    error ("array size missing in %q+D", decl);
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!ವೃಕ್ಷ_ಬಹಿರಂಗ (decl))
	    pedwarn_c23 (DECL_ಮೂಲ_LOCATION (decl), OPT_Wpedantic,
			 "array size missing in %q+D", decl);
	  ನಿಲ್ಲಿಸು;

	ಸ್ಥಿತಿ 3:
	  error ("zero or negative size array %q+D", decl);
	  ನಿಲ್ಲಿಸು;

	ಸ್ಥಿತಿ 0:
	  /* For global variables, update the copy of the type that
	     exists in the binding.  */
	  ಆದರೆ (ವೃಕ್ಷ_ಬಹಿರಂಗ (decl))
	    {
	      ರಚನೆ c_binding *b_ext = I_ಚಿಹ್ನೆ_BINDING (DECL_NAME (decl));
	      ಆಗ (b_ext && !B_ಒಳ_EXTERNAL_SCOPE (b_ext))
		b_ext = b_ext->shadowed;
	      ಆದರೆ (b_ext && ವೃಕ್ಷ_ಸಂಕೇತ (decl) == ವೃಕ್ಷ_ಸಂಕೇತ (b_ext->decl))
		{
		  ಆದರೆ (b_ext->u.type && comptypes (b_ext->u.type, type))
		    b_ext->u.type = ಸಂಯುಕ್ತ_type (b_ext->u.type, type);
		  ಇಲ್ಲದಿದ್ದರೆ
		    b_ext->u.type = type;
		}
	    }
	  ನಿಲ್ಲಿಸು;

	ಪೂರ್ವನಿಯೋಜಿತ:
	  gcc_unreachable ();
	}

      ಆದರೆ (DECL_INITIAL (decl) && DECL_INITIAL (decl) != error_mark_ಗಂಟು)
	ವೃಕ್ಷ_TYPE (DECL_INITIAL (decl)) = type;

      relayout_decl (decl);
    }

  /* Look for braced array initializers for character arrays and
     recursively convert them into STRING_CSTs.  */
  ಆದರೆ (ವೃಕ್ಷ init = DECL_INITIAL (decl))
    DECL_INITIAL (decl) = braced_lists_ಗಮ್ಯ_ಅಕ್ಷರಸರಣಿಗಳು (type, init);

  ಆದರೆ (VAR_P (decl))
    {
      ಆದರೆ (init && ವೃಕ್ಷ_ಸಂಕೇತ (init) == CONSTRUCTOR)
	ಕೂಡಿಸು_flexible_array_elts_ಗಮ್ಯ_ಗಾತ್ರ (decl, init);

      complete_flexible_array_elts (DECL_INITIAL (decl));

      ಆದರೆ (is_global_var (decl))
	{
	  type_context_ಬಗೆ context = (DECL_THREAD_LOCAL_P (decl)
				       ? TCTX_THREAD_STORAGE
				       : TCTX_STATIC_STORAGE);
	  ಆದರೆ (!verify_type_context (ಒಳಹರಿವು_location, context, ವೃಕ್ಷ_TYPE (decl)))
	    ವೃಕ್ಷ_TYPE (decl) = error_mark_ಗಂಟು;
	}

      ಆದರೆ (DECL_ಗಾತ್ರ (decl) == NULL_ವೃಕ್ಷ && ವೃಕ್ಷ_TYPE (decl) != error_mark_ಗಂಟು
	  && COMPLETE_TYPE_P (ವೃಕ್ಷ_TYPE (decl)))
	layout_decl (decl, 0);

      ಆದರೆ (DECL_ಗಾತ್ರ (decl) == NULL_ವೃಕ್ಷ
	  /* Don't give an error if we already gave one earlier.  */
	  && ವೃಕ್ಷ_TYPE (decl) != error_mark_ಗಂಟು
	  && (ವೃಕ್ಷ_STATIC (decl)
	      /* A static variable with an incomplete type
		 is an error if it is initialized.
		 Also if it is not file scope.
		 Also if it is thread-local (in C23).
		 Otherwise, let it through, but if it is not `extern'
		 then it may cause an error message later.  */
	      ? (DECL_INITIAL (decl) != NULL_ವೃಕ್ಷ
		 || !DECL_FILE_SCOPE_P (decl)
		 || (flag_isoc23 && DECL_THREAD_LOCAL_P (decl)))
	      /* An automatic variable with an incomplete type
		 is an error.  */
	      : !DECL_EXTERNAL (decl)))
	 {
	   error ("storage size of %q+D isn%'t known", decl);
	   ವೃಕ್ಷ_TYPE (decl) = error_mark_ಗಂಟು;
	 }

      ಆದರೆ ((ದಾಖಲೆ_OR_UNION_TYPE_P (ವೃಕ್ಷ_TYPE (decl))
	  || ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (decl)) == ENUMERAL_TYPE)
	  && DECL_ಗಾತ್ರ (decl) == NULL_ವೃಕ್ಷ
	  && ವೃಕ್ಷ_STATIC (decl))
	incomplete_ದಾಖಲೆ_decls.ಸುರಕ್ಷಿತ_ತಳ್ಳು (decl);

      ಆದರೆ (is_global_var (decl)
	  && DECL_ಗಾತ್ರ (decl) != NULL_ವೃಕ್ಷ
	  && ವೃಕ್ಷ_TYPE (decl) != error_mark_ಗಂಟು)
	{
	  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (DECL_ಗಾತ್ರ (decl)) == INTEGER_CST)
	    constant_ಅಭಿವ್ಯಕ್ತಿ_warning (DECL_ಗಾತ್ರ (decl));
	  ಇಲ್ಲದಿದ್ದರೆ
	    {
	      error ("storage size of %q+D isn%'t constant", decl);
	      ವೃಕ್ಷ_TYPE (decl) = error_mark_ಗಂಟು;
	    }
	}

      ಆದರೆ (ವೃಕ್ಷ_ಬಳಸಿದ (type))
	{
	  ವೃಕ್ಷ_ಬಳಸಿದ (decl) = 1;
	  DECL_READ_P (decl) = 1;
	}
    }

  /* If this is a function and an assembler name is specified, reset DECL_RTL
     so we can give it its new name.  Also, update builtin_decl if it
     was a normal built-in.  */
  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (decl) == FUNCTION_DECL && asmspec)
    {
      ಆದರೆ (DECL_BUILT_ಒಳ_CLASS (decl) == BUILT_ಒಳ_ಸಾಮಾನ್ಯ)
	ಗಣ_builtin_user_assembler_name (decl, asmspec);
      ಗಣ_user_assembler_name (decl, asmspec);
    }

  /* If #pragma weak was used, mark the decl weak now.  */
  maybe_apply_pragma_weak (decl);

  /* Output the assembler code and/or RTL code for variables and functions,
     unless the type is an undefined structure or union.
     If not, it will get done when the type is completed.  */

  ಆದರೆ (VAR_OR_FUNCTION_DECL_P (decl))
    {
      /* Determine the ELF visibility.  */
      ಆದರೆ (ವೃಕ್ಷ_ಬಹಿರಂಗ (decl))
	c_determine_visibility (decl);

      /* This is a no-op in c-lang.cc or something real in objc-act.cc.  */
      ಆದರೆ (c_dialect_objc ())
	objc_check_decl (decl);

      ಆದರೆ (asmspec)
	{
	  /* If this is not a static variable, issue a warning.
	     It doesn't make any sense to give an ASMSPEC for an
	     ordinary, non-register local variable.  Historically,
	     GCC has accepted -- but ignored -- the ASMSPEC in
	     this case.  */
	  ಆದರೆ (!DECL_FILE_SCOPE_P (decl)
	      && VAR_P (decl)
	      && !C_DECL_ರಿಜಿಸ್ಟರ್ (decl)
	      && !ವೃಕ್ಷ_STATIC (decl))
	    warning (0, "ignoring %<asm%> specifier for non-static local "
		     "variable %q+D", decl);
	  ಇಲ್ಲದಿದ್ದರೆ
	    ಗಣ_user_assembler_name (decl, asmspec);
	}

      ಆದರೆ (DECL_FILE_SCOPE_P (decl))
	{
	  ಆದರೆ (DECL_INITIAL (decl) == NULL_ವೃಕ್ಷ
	      || DECL_INITIAL (decl) == error_mark_ಗಂಟು)
	    /* Don't output anything
	       when a tentative file-scope definition is seen.
	       But at end of compilation, do output code for them.  */
	    DECL_DEFER_OUTPUT (decl) = 1;
	  ಆದರೆ (asmspec && VAR_P (decl) && C_DECL_ರಿಜಿಸ್ಟರ್ (decl))
	    DECL_HARD_ರಿಜಿಸ್ಟರ್ (decl) = 1;
	  rest_ದ_decl_compilation (decl, ನಿಜ, 0);

	  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (decl) == FUNCTION_DECL)
	    {
	      ವೃಕ್ಷ parms = DECL_ARGUMENTS (decl);
	      ಸ್ಥಿರಾಂಕ ತಾರ್ಕಿಕ builtin = fndecl_built_ಒಳ_p (decl);
	      ಆದರೆ (ವೃಕ್ಷ access = build_attr_access_from_parms (parms, !builtin))
		decl_ಗುಣಲಕ್ಷಣಗಳು (&decl, access, 0);
	    }
	}
      ಇಲ್ಲದಿದ್ದರೆ
	{
	  /* In conjunction with an ASMSPEC, the `register'
	     keyword indicates that we should place the variable
	     in a particular register.  */
	  ಆದರೆ (asmspec && C_DECL_ರಿಜಿಸ್ಟರ್ (decl))
	    {
	      DECL_HARD_ರಿಜಿಸ್ಟರ್ (decl) = 1;
	      /* This cannot be done for a structure with volatile
		 fields, on which DECL_REGISTER will have been
		 reset.  */
	      ಆದರೆ (!DECL_ರಿಜಿಸ್ಟರ್ (decl))
		error ("cannot put object with volatile field into register");
	    }

	  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (decl) != FUNCTION_DECL)
	    {
	      /* If we're building a variable sized type, and we might be
		 reachable other than via the top of the current binding
		 level, then create a new BIND_EXPR so that we deallocate
		 the object at the right time.  */
	      /* Note that DECL_SIZE can be null due to errors.  */
	      ಆದರೆ (DECL_ಗಾತ್ರ (decl)
		  && !ವೃಕ್ಷ_CONSTANT (DECL_ಗಾತ್ರ (decl))
		  && STATEMENT_LIST_HAS_LABEL (cur_stmt_list))
		{
		  ವೃಕ್ಷ bind;
		  bind = build3 (BIND_ಅಭಿವ್ಯಕ್ತಿ, void_type_ಗಂಟು, ಖಾಲಿ, ಖಾಲಿ, ಖಾಲಿ);
		  ವೃಕ್ಷ_SIDE_EFFECTS (bind) = 1;
		  ಕೂಡಿಸು_stmt (bind);
		  BIND_ಅಭಿವ್ಯಕ್ತಿ_BODY (bind) = ತಳ್ಳು_stmt_list ();
		}
	      ಕೂಡಿಸು_stmt (build_stmt (DECL_ಮೂಲ_LOCATION (decl),
				    DECL_ಅಭಿವ್ಯಕ್ತಿ, decl));
	    }
	}


      ಆದರೆ (!DECL_FILE_SCOPE_P (decl))
	{
	  /* Recompute the RTL of a local array now
	     if it used to be an incomplete type.  */
	  ಆದರೆ (was_incomplete && !is_global_var (decl))
	    {
	      /* If we used it already as memory, it must stay in memory.  */
	      ವೃಕ್ಷ_ADDRESSABLE (decl) = ವೃಕ್ಷ_ಬಳಸಿದ (decl);
	      /* If it's still incomplete now, no init will save it.  */
	      ಆದರೆ (DECL_ಗಾತ್ರ (decl) == NULL_ವೃಕ್ಷ)
		DECL_INITIAL (decl) = NULL_ವೃಕ್ಷ;
	    }
	}
    }

  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (decl) == TYPE_DECL)
    {
      ಆದರೆ (!DECL_FILE_SCOPE_P (decl)
	  && c_type_variably_modified_p (ವೃಕ್ಷ_TYPE (decl)))
	ಕೂಡಿಸು_stmt (build_stmt (DECL_ಮೂಲ_LOCATION (decl), DECL_ಅಭಿವ್ಯಕ್ತಿ, decl));

      rest_ದ_decl_compilation (decl, DECL_FILE_SCOPE_P (decl), 0);
    }

  /* Install a cleanup (aka destructor) if one was given.  */
  ಆದರೆ (VAR_P (decl) && !ವೃಕ್ಷ_STATIC (decl))
    {
      ವೃಕ್ಷ attr = lookup_attribute ("cleanup", DECL_ಗುಣಲಕ್ಷಣಗಳು (decl));
      ಆದರೆ (attr)
	{
	  ವೃಕ್ಷ cleanup_id = ವೃಕ್ಷ_ಮೌಲ್ಯ (ವೃಕ್ಷ_ಮೌಲ್ಯ (attr));
	  ವೃಕ್ಷ cleanup_decl = lookup_name (cleanup_id);
	  ವೃಕ್ಷ cleanup;
	  vec<ವೃಕ್ಷ, va_gc> *v;

	  /* Build "cleanup(&decl)" for the destructor.  */
	  cleanup = build_unary_op (ಒಳಹರಿವು_location, ADDR_ಅಭಿವ್ಯಕ್ತಿ, decl, ಸುಳ್ಳು);
	  vec_alloc (v, 1);
	  v->ಶೀಘ್ರ_ತಳ್ಳು (cleanup);
	  cleanup = c_build_function_call_vec (DECL_ಮೂಲ_LOCATION (decl),
					       vNULL, cleanup_decl, v, ಖಾಲಿ);
	  vec_free (v);

	  /* Don't warn about decl unused; the cleanup uses it.  */
	  ವೃಕ್ಷ_ಬಳಸಿದ (decl) = 1;
	  ವೃಕ್ಷ_ಬಳಸಿದ (cleanup_decl) = 1;
	  DECL_READ_P (decl) = 1;

	  ತಳ್ಳು_cleanup (decl, cleanup, ಸುಳ್ಳು);
	}
    }

  ಆದರೆ (warn_cxx_compat
      && VAR_P (decl)
      && !DECL_EXTERNAL (decl)
      && DECL_INITIAL (decl) == NULL_ವೃಕ್ಷ)
    {
      type = strip_array_types (type);
      ಆದರೆ (ವೃಕ್ಷ_READONLY (decl))
	warning_at (DECL_ಮೂಲ_LOCATION (decl), OPT_Wc___compat,
		    "uninitialized %<const %D%> is invalid in C++", decl);
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ದಾಖಲೆ_OR_UNION_TYPE_P (type)
	       && C_TYPE_FIELDS_READONLY (type))
	diagnose_uninitialized_cst_member (decl, type);
    }

  ಆದರೆ (flag_openmp
      && VAR_P (decl)
      && lookup_attribute ("omp declare target implicit",
			   DECL_ಗುಣಲಕ್ಷಣಗಳು (decl)))
    {
      DECL_ಗುಣಲಕ್ಷಣಗಳು (decl)
	= remove_attribute ("omp declare target implicit",
			    DECL_ಗುಣಲಕ್ಷಣಗಳು (decl));
      ಆದರೆ (!omp_mappable_type (ವೃಕ್ಷ_TYPE (decl)))
	error ("%q+D in declare target directive does not have mappable type",
	       decl);
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!lookup_attribute ("omp declare target",
				  DECL_ಗುಣಲಕ್ಷಣಗಳು (decl))
	       && !lookup_attribute ("omp declare target link",
				     DECL_ಗುಣಲಕ್ಷಣಗಳು (decl)))
	{
	  DECL_ಗುಣಲಕ್ಷಣಗಳು (decl)
	    = ವೃಕ್ಷ_cons (get_identifier ("omp declare target"),
			 NULL_ವೃಕ್ಷ, DECL_ಗುಣಲಕ್ಷಣಗಳು (decl));
	    symtab_ಗಂಟು *ಗಂಟು = symtab_ಗಂಟು::get (decl);
	    ಆದರೆ (ಗಂಟು != ಖಾಲಿ)
	      {
		ಗಂಟು->offloadable = 1;
		ಆದರೆ (ENABLE_OFFLOADING)
		  {
		    g->have_offload = ನಿಜ;
		    ಆದರೆ (is_a <varpool_ಗಂಟು *> (ಗಂಟು))
		      vec_ಸುರಕ್ಷಿತ_ತಳ್ಳು (offload_vars, decl);
		  }
	      }
	}
    }

  /* This is the last point we can lower alignment so give the target the
     chance to do so.  */
  ಆದರೆ (VAR_P (decl)
      && !is_global_var (decl)
      && !DECL_HARD_ರಿಜಿಸ್ಟರ್ (decl))
    targetm.ಅಧೋ_local_decl_alignment (decl);

  invoke_plugin_callbacks (PLUGIN_ಮುಕ್ತಾಯ_DECL, decl);
}

/* Given a parsed parameter declaration, decode it into a PARM_DECL.
   EXPR is NULL or a pointer to an expression that needs to be
   evaluated for the side effects of array size expressions in the
   parameters.  */

ವೃಕ್ಷ
grokparm (ಸ್ಥಿರಾಂಕ ರಚನೆ c_parm *parm, ವೃಕ್ಷ *ಅಭಿವ್ಯಕ್ತಿ)
{
  ವೃಕ್ಷ attrs = parm->attrs;
  ವೃಕ್ಷ decl = grokdeclarator (parm->declarator, parm->specs, PARM, ಸುಳ್ಳು,
			      ಖಾಲಿ, &attrs, ಅಭಿವ್ಯಕ್ತಿ, ಖಾಲಿ, DEPRECATED_ಸಾಮಾನ್ಯ);

  decl_ಗುಣಲಕ್ಷಣಗಳು (&decl, attrs, 0);

  ಹಿಂತಿರುಗಿ decl;
}



/* Given a parsed parameter declaration, decode it into a PARM_DECL
   and push that on the current scope.  EXPR is a pointer to an
   expression that needs to be evaluated for the side effects of array
   size expressions in the parameters.  */

ಶೂನ್ಯ
ತಳ್ಳು_parm_decl (ಸ್ಥಿರಾಂಕ ರಚನೆ c_parm *parm, ವೃಕ್ಷ *ಅಭಿವ್ಯಕ್ತಿ)
{
  ವೃಕ್ಷ attrs = parm->attrs;
  ವೃಕ್ಷ decl = grokdeclarator (parm->declarator, parm->specs, PARM, ಸುಳ್ಳು, ಖಾಲಿ,
			      &attrs, ಅಭಿವ್ಯಕ್ತಿ, ಖಾಲಿ, DEPRECATED_ಸಾಮಾನ್ಯ);
  ಆದರೆ (decl && DECL_P (decl))
    DECL_ಮೂಲ_LOCATION (decl) = parm->loc;

  decl_ಗುಣಲಕ್ಷಣಗಳು (&decl, attrs, 0);

  decl = pushdecl (decl);

  ಮುಕ್ತಾಯ_decl (decl, ಒಳಹರಿವು_location, NULL_ವೃಕ್ಷ, NULL_ವೃಕ್ಷ, NULL_ವೃಕ್ಷ);
}

/* Mark all the parameter declarations to date as forward decls.
   Also diagnose use of this extension.  */

ಶೂನ್ಯ
mark_forward_parm_decls (ಶೂನ್ಯ)
{
  ರಚನೆ c_binding *b;

  ಆದರೆ (current_scope->had_forward_parm_decls)
    warning_at (ಒಳಹರಿವು_location, OPT_Wmultiple_parameter_fwd_decl_lists,
		"more than one list of forward declarations of parameters");
  ಆದರೆ (pedantic && !current_scope->had_forward_parm_decls)
    pedwarn (ಒಳಹರಿವು_location, OPT_Wpedantic,
	     "ISO C forbids forward parameter declarations");

  current_scope->had_forward_parm_decls = ನಿಜ;

  ಗಾಗಿ (b = current_scope->bindings; b; b = b->prev)
    ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (b->decl) == PARM_DECL)
      ವೃಕ್ಷ_ASM_WRITTEN (b->decl) = 1;
}

/* Build a COMPOUND_LITERAL_EXPR.  TYPE is the type given in the compound
   literal, which may be an incomplete array type completed by the
   initializer; INIT is a CONSTRUCTOR at LOC that initializes the compound
   literal.  NON_CONST is true if the initializers contain something
   that cannot occur in a constant expression.  If ALIGNAS_ALIGN is nonzero,
   it is the (valid) alignment for this compound literal, as specified
   with _Alignas.  SCSPECS are the storage class specifiers (C23) from the
   compound literal.  */

ವೃಕ್ಷ
build_compound_literal (location_t loc, ವೃಕ್ಷ type, ವೃಕ್ಷ init, ತಾರ್ಕಿಕ non_const,
			ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ alignas_align,
			ರಚನೆ c_declspecs *scspecs)
{
  /* We do not use start_decl here because we have a type, not a declarator;
     and do not use finish_decl because the decl should be stored inside
     the COMPOUND_LITERAL_EXPR rather than added elsewhere as a DECL_EXPR.  */
  ವೃಕ್ಷ decl;
  ವೃಕ್ಷ complit;
  ವೃಕ್ಷ stmt;
  ತಾರ್ಕಿಕ threadp = scspecs ? scspecs->thread_p : ಸುಳ್ಳು;
  ಎಣಿಕೆ c_storage_class storage_class = (scspecs
					? scspecs->storage_class
					: csc_none);

  ಆದರೆ (type == error_mark_ಗಂಟು
      || init == error_mark_ಗಂಟು)
    ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;

  ಆದರೆ (current_scope == file_scope && storage_class == csc_ರಿಜಿಸ್ಟರ್)
    {
      error_at (loc, "file-scope compound literal specifies %<register%>");
      storage_class = csc_none;
    }

  ಆದರೆ (current_scope != file_scope && threadp && storage_class == csc_none)
    {
      error_at (loc, "compound literal implicitly auto and declared %qs",
		scspecs->thread_gnu_p ? "__thread" : "_Thread_local");
      threadp = ಸುಳ್ಳು;
    }

  decl = build_decl (loc, VAR_DECL, NULL_ವೃಕ್ಷ, type);
  DECL_EXTERNAL (decl) = 0;
  ವೃಕ್ಷ_ಬಹಿರಂಗ (decl) = 0;
  ವೃಕ್ಷ_STATIC (decl) = (current_scope == file_scope
			|| storage_class == csc_static);
  DECL_CONTEXT (decl) = current_function_decl;
  ವೃಕ್ಷ_ಬಳಸಿದ (decl) = 1;
  DECL_READ_P (decl) = 1;
  DECL_ARTIFICIAL (decl) = 1;
  DECL_IGNORED_P (decl) = 1;
  C_DECL_COMPOUND_LITERAL_P (decl) = 1;
  C_DECL_DECLARED_CONSTEXPR (decl) = scspecs && scspecs->constexpr_p;
  ವೃಕ್ಷ_TYPE (decl) = type;
  ಆದರೆ (threadp)
    ಗಣ_decl_tls_model (decl, decl_default_tls_model (decl));
  ಆದರೆ (storage_class == csc_ರಿಜಿಸ್ಟರ್)
    {
      C_DECL_ರಿಜಿಸ್ಟರ್ (decl) = 1;
      DECL_ರಿಜಿಸ್ಟರ್ (decl) = 1;
    }
  c_apply_type_quals_ಗಮ್ಯ_decl (TYPE_QUALS (strip_array_types (type)), decl);
  ಆದರೆ (alignas_align)
    {
      ಗಣ_DECL_ALIGN (decl, alignas_align * ಬಿಟ್ಟುಗಳು_ಪ್ರತಿ_UNIT);
      DECL_USER_ALIGN (decl) = 1;
    }
  store_init_ಮೌಲ್ಯ (loc, decl, init, NULL_ವೃಕ್ಷ);
  ಆದರೆ (current_scope != file_scope
      && ವೃಕ್ಷ_STATIC (decl)
      && !ವೃಕ್ಷ_READONLY (decl)
      && DECL_DECLARED_INLINE_P (current_function_decl)
      && DECL_EXTERNAL (current_function_decl))
    ದಾಖಲೆ_inline_static (ಒಳಹರಿವು_location, current_function_decl,
			  decl, csi_modifiable);

  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (type) == ARRAY_TYPE && !COMPLETE_TYPE_P (type))
    {
      ಪೂರ್ಣಾಂಕ failure = complete_array_type (&ವೃಕ್ಷ_TYPE (decl),
					 DECL_INITIAL (decl), ನಿಜ);
      /* If complete_array_type returns 3, it means that the initial value of
         the compound literal is empty.  Allow it with a pedwarn; in pre-C23
         modes, the empty initializer itself has been diagnosed if pedantic so
         does not need to be diagnosed again here.  */
      gcc_assert (failure == 0 || failure == 3);
      ಆದರೆ (failure == 3 && flag_isoc23)
	pedwarn (loc, OPT_Wpedantic,
		 "array of unknown size with empty initializer");

      type = ವೃಕ್ಷ_TYPE (decl);
      ವೃಕ್ಷ_TYPE (DECL_INITIAL (decl)) = type;
      relayout_decl (decl);
    }

  ಆದರೆ (type == error_mark_ಗಂಟು || !COMPLETE_TYPE_P (type))
    {
      c_incomplete_type_error (loc, NULL_ವೃಕ್ಷ, type);
      ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
    }

  ಆದರೆ ((ವೃಕ್ಷ_STATIC (decl) || C_DECL_DECLARED_CONSTEXPR (decl))
      && C_TYPE_VARIABLE_ಗಾತ್ರ (type))
    error_at (loc, "storage size isn%'t constant");

  ಆದರೆ (ವೃಕ್ಷ_STATIC (decl)
      && !verify_type_context (loc, TCTX_STATIC_STORAGE, type))
    ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;

  stmt = build_stmt (DECL_ಮೂಲ_LOCATION (decl), DECL_ಅಭಿವ್ಯಕ್ತಿ, decl);
  complit = build1 (COMPOUND_LITERAL_ಅಭಿವ್ಯಕ್ತಿ, type, stmt);
  ವೃಕ್ಷ_SIDE_EFFECTS (complit) = 1;

  layout_decl (decl, 0);

  ಆದರೆ (ವೃಕ್ಷ_STATIC (decl))
    {
      /* This decl needs a name for the assembler output.  */
      ಗಣ_compound_literal_name (decl);
      DECL_DEFER_OUTPUT (decl) = 1;
      DECL_COMDAT (decl) = 1;
      pushdecl (decl);
      rest_ದ_decl_compilation (decl, 1, 0);
    }
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (current_function_decl && !current_scope->parm_flag)
    pushdecl (decl);

  ಆದರೆ (non_const)
    {
      complit = build2 (C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ, type, ಖಾಲಿ, complit);
      C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ_NON_CONST (complit) = 1;
    }

  ಹಿಂತಿರುಗಿ complit;
}

/* Check the type of a compound literal.  Here we just check that it
   is valid for C++.  */

ಶೂನ್ಯ
check_compound_literal_type (location_t loc, ರಚನೆ c_type_name *type_name)
{
  ಆದರೆ (warn_cxx_compat
      && (type_name->specs->typespec_ಬಗೆ == ctsk_tagdef
          || type_name->specs->typespec_ಬಗೆ == ctsk_tagfirstref
	  || type_name->specs->typespec_ಬಗೆ == ctsk_tagfirstref_attrs))
    warning_at (loc, OPT_Wc___compat,
		"defining a type in a compound literal is invalid in C++");
}

/* Performs sanity checks on the TYPE and WIDTH of the bit-field NAME,
   replacing with appropriate values if they are invalid.  */

ಸ್ಥಿರ ಶೂನ್ಯ
check_bitfield_type_and_ಅಗಲ (location_t loc, ವೃಕ್ಷ *type, ವೃಕ್ಷ *ಅಗಲ,
			       ವೃಕ್ಷ orig_name)
{
  ವೃಕ್ಷ type_mv;
  ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ max_ಅಗಲ;
  ಚಿಹ್ನೆರಹಿತ HOST_WIDE_INT w;
  ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name = (orig_name
		      ? identifier_ಗಮ್ಯ_locale (IDENTIFIER_ಸೂಚಕ (orig_name))
		      : _("<anonymous>"));

  /* Detect and ignore out of range field width and process valid
     field widths.  */
  ಆದರೆ (!INTEGRAL_TYPE_P (ವೃಕ್ಷ_TYPE (*ಅಗಲ)))
    {
      error_at (loc, "bit-field %qs width not an integer constant", name);
      *ಅಗಲ = integer_one_ಗಂಟು;
    }
  ಇಲ್ಲದಿದ್ದರೆ
    {
      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (*ಅಗಲ) != INTEGER_CST)
	{
	  *ಅಗಲ = c_fully_fold (*ಅಗಲ, ಸುಳ್ಳು, ಖಾಲಿ);
	  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (*ಅಗಲ) == INTEGER_CST)
	    pedwarn (loc, OPT_Wpedantic,
		     "bit-field %qs width not an integer constant expression",
		     name);
	}
      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (*ಅಗಲ) != INTEGER_CST)
	{
	  error_at (loc, "bit-field %qs width not an integer constant", name);
	  *ಅಗಲ = integer_one_ಗಂಟು;
	}
      constant_ಅಭಿವ್ಯಕ್ತಿ_warning (*ಅಗಲ);
      ಆದರೆ (ವೃಕ್ಷ_int_cst_sgn (*ಅಗಲ) < 0)
	{
	  error_at (loc, "negative width in bit-field %qs", name);
	  *ಅಗಲ = integer_one_ಗಂಟು;
	}
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (integer_zerop (*ಅಗಲ) && orig_name)
	{
	  error_at (loc, "zero width for bit-field %qs", name);
	  *ಅಗಲ = integer_one_ಗಂಟು;
	}
    }

  /* Detect invalid bit-field type.  */
  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (*type) != INTEGER_TYPE
      && ವೃಕ್ಷ_ಸಂಕೇತ (*type) != BOOLEAN_TYPE
      && ವೃಕ್ಷ_ಸಂಕೇತ (*type) != ENUMERAL_TYPE
      && ವೃಕ್ಷ_ಸಂಕೇತ (*type) != BITINT_TYPE)
    {
      error_at (loc, "bit-field %qs has invalid type", name);
      *type = unsigned_type_ಗಂಟು;
    }

  ಆದರೆ (TYPE_WARN_IF_NOT_ALIGN (*type))
    {
      error_at (loc, "cannot declare bit-field %qs with %<warn_if_not_aligned%> type",
		name);
      *type = unsigned_type_ಗಂಟು;
    }

  type_mv = TYPE_MAIN_VARIANT (*type);
  ಆದರೆ (!ಒಳ_system_ಶೀರ್ಷಿಕೆ_at (ಒಳಹರಿವು_location)
      && type_mv != integer_type_ಗಂಟು
      && type_mv != unsigned_type_ಗಂಟು
      && type_mv != boolean_type_ಗಂಟು)
    pedwarn_c90 (loc, OPT_Wpedantic,
		 "type of bit-field %qs is a GCC extension", name);

  max_ಅಗಲ = TYPE_PRECISION (*type);

  ಆದರೆ (compare_ವೃಕ್ಷ_int (*ಅಗಲ, max_ಅಗಲ) > 0)
    {
      error_at (loc, "width of %qs exceeds its type", name);
      w = max_ಅಗಲ;
      *ಅಗಲ = build_int_cst (integer_type_ಗಂಟು, w);
    }
  ಇಲ್ಲದಿದ್ದರೆ
    w = ವೃಕ್ಷ_ಗಮ್ಯ_uhwi (*ಅಗಲ);

  /* Truncation of hardbool false and true representation values is always safe:
     either the values remain different, or we'll report a problem when creating
     the narrower type.  */
  ಆದರೆ (c_hardbool_type_attr (*type))
    ಹಿಂತಿರುಗಿ;

  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (*type) == ENUMERAL_TYPE)
    {
      ರಚನೆ lang_type *lt = TYPE_LANG_SPECIFIC (*type);
      ಆದರೆ (!lt
	  || w < ವೃಕ್ಷ_int_cst_min_precision (lt->enum_min, TYPE_SIGN (*type))
	  || w < ವೃಕ್ಷ_int_cst_min_precision (lt->enum_max, TYPE_SIGN (*type)))
	warning_at (loc, 0, "%qs is narrower than values of its type", name);
    }
}



/* Print warning about variable length array if necessary.  */

ಸ್ಥಿರ ಶೂನ್ಯ
warn_variable_ಉದ್ದಳತೆ_array (ವೃಕ್ಷ name, ವೃಕ್ಷ ಗಾತ್ರ_2)
{
  ಆದರೆ (ವೃಕ್ಷ_CONSTANT (ಗಾತ್ರ_2))
    {
      ಆದರೆ (name)
	pedwarn_c90 (ಒಳಹರಿವು_location, OPT_Wvla,
		     "ISO C90 forbids array %qE whose size "
		     "cannot be evaluated", name);
      ಇಲ್ಲದಿದ್ದರೆ
	pedwarn_c90 (ಒಳಹರಿವು_location, OPT_Wvla, "ISO C90 forbids array "
		     "whose size cannot be evaluated");
    }
  ಇಲ್ಲದಿದ್ದರೆ
    {
      ಆದರೆ (name)
	pedwarn_c90 (ಒಳಹರಿವು_location, OPT_Wvla,
		     "ISO C90 forbids variable length array %qE", name);
      ಇಲ್ಲದಿದ್ದರೆ
	pedwarn_c90 (ಒಳಹರಿವು_location, OPT_Wvla, "ISO C90 forbids variable "
		     "length array");
    }
}

/* Returns the smallest location != UNKNOWN_LOCATION in LOCATIONS,
   considering only those c_declspec_words found in LIST, which
   must be terminated by cdw_number_of_elements.  */

ಸ್ಥಿರ location_t
ಅತಿಚಿಕ್ಕ_type_quals_location (ಸ್ಥಿರಾಂಕ location_t *locations,
			      ಸ್ಥಿರಾಂಕ c_declspec_ಶಬ್ದ *list)
{
  location_t loc = UNKNOWN_LOCATION;
  ಆಗ (*list != cdw_ಸಂಖ್ಯೆ_ದ_elements)
    {
      location_t newloc = locations[*list];
      ಆದರೆ (loc == UNKNOWN_LOCATION
	  || (newloc != UNKNOWN_LOCATION && newloc < loc))
	loc = newloc;
      list++;
    }

  ಹಿಂತಿರುಗಿ loc;
}


/* We attach an artificial TYPE_DECL to pointed-to type
   and arrange for it to be included in a DECL_EXPR.  This
   forces the sizes evaluation at a safe point and ensures it
   is not deferred until e.g. within a deeper conditional context.

   PARM contexts have no enclosing statement list that
   can hold the DECL_EXPR, so we need to use a BIND_EXPR
   instead, and add it to the list of expressions that
   need to be evaluated.

   TYPENAME contexts do have an enclosing statement list,
   but it would be incorrect to use it, as the size should
   only be evaluated if the containing expression is
   evaluated.  We might also be in the middle of an
   expression with side effects on the pointed-to type size
   "arguments" prior to the pointer declaration point and
   the fake TYPE_DECL in the enclosing context would force
   the size evaluation prior to the side effects.  We therefore
   use BIND_EXPRs in TYPENAME contexts too.  */
ಸ್ಥಿರ ಶೂನ್ಯ
ಕೂಡಿಸು_decl_ಅಭಿವ್ಯಕ್ತಿ (location_t loc, ವೃಕ್ಷ type, ವೃಕ್ಷ *ಅಭಿವ್ಯಕ್ತಿ, ತಾರ್ಕಿಕ ಗಣ_name_p)
{
  ವೃಕ್ಷ bind = NULL_ವೃಕ್ಷ;
  ಆದರೆ (ಅಭಿವ್ಯಕ್ತಿ)
    {
      bind = build3 (BIND_ಅಭಿವ್ಯಕ್ತಿ, void_type_ಗಂಟು, NULL_ವೃಕ್ಷ, NULL_ವೃಕ್ಷ,
		     NULL_ವೃಕ್ಷ);
      ವೃಕ್ಷ_SIDE_EFFECTS (bind) = 1;
      BIND_ಅಭಿವ್ಯಕ್ತಿ_BODY (bind) = ತಳ್ಳು_stmt_list ();
      ತಳ್ಳು_scope ();
    }

  ವೃಕ್ಷ decl = build_decl (loc, TYPE_DECL, NULL_ವೃಕ್ಷ, type);
  pushdecl (decl);
  DECL_ARTIFICIAL (decl) = 1;
  ಕೂಡಿಸು_stmt (build_stmt (DECL_ಮೂಲ_LOCATION (decl), DECL_ಅಭಿವ್ಯಕ್ತಿ, decl));
  ಆದರೆ (ಗಣ_name_p)
    TYPE_NAME (type) = decl;

  ಆದರೆ (bind)
    {
      ತೆಗೆ_scope ();
      BIND_ಅಭಿವ್ಯಕ್ತಿ_BODY (bind) = ತೆಗೆ_stmt_list (BIND_ಅಭಿವ್ಯಕ್ತಿ_BODY (bind));
      ಆದರೆ (*ಅಭಿವ್ಯಕ್ತಿ)
	*ಅಭಿವ್ಯಕ್ತಿ = build2 (COMPOUND_ಅಭಿವ್ಯಕ್ತಿ, void_type_ಗಂಟು, *ಅಭಿವ್ಯಕ್ತಿ, bind);
      ಇಲ್ಲದಿದ್ದರೆ
	*ಅಭಿವ್ಯಕ್ತಿ = bind;
    }
}


/* Add attribute "arg spec" to ATTRS corresponding to an array/VLA parameter
   declared with type TYPE.  The attribute has two arguments.  The first is
   a string that encodes the presence of the static keyword.  The second is
   the declared type of the array before adjustment, i.e. as an array type
   including the outermost bound.  */

ಸ್ಥಿರ ವೃಕ್ಷ
build_arg_spec_attribute (ವೃಕ್ಷ type, ತಾರ್ಕಿಕ static_p, ವೃಕ್ಷ attrs)
{
  ವೃಕ್ಷ vbchain = ವೃಕ್ಷ_cons (NULL_ವೃಕ್ಷ, type, NULL_ವೃಕ್ಷ);
  ವೃಕ್ಷ acsstr = static_p ? build_string (7, "static") :
			   build_string (1, "");
  ವೃಕ್ಷ ವಾದಗಳು = ವೃಕ್ಷ_cons (NULL_ವೃಕ್ಷ, acsstr, vbchain);
  ವೃಕ್ಷ name = get_identifier ("arg spec");
  ಹಿಂತಿರುಗಿ ವೃಕ್ಷ_cons (name, ವಾದಗಳು, attrs);
}


/* Given declspecs and a declarator,
   determine the name and type of the object declared
   and construct a ..._DECL node for it.
   (In one case we can return a ..._TYPE node instead.
    For invalid input we sometimes return NULL_TREE.)

   DECLSPECS is a c_declspecs structure for the declaration specifiers.

   DECL_CONTEXT says which syntactic context this declaration is in:
     NORMAL for most contexts.  Make a VAR_DECL or FUNCTION_DECL or TYPE_DECL.
     FUNCDEF for a function definition.  Like NORMAL but a few different
      error messages in each case.  Return value may be zero meaning
      this definition is too screwy to try to parse.
     PARM for a parameter declaration (either within a function prototype
      or before a function body).  Make a PARM_DECL, or return void_type_node.
     TYPENAME if for a typename (in a cast or sizeof).
      Don't make a DECL node; just return the ..._TYPE node.
     GENERIC_ASSOC for typenames in a generic association.
     FIELD for a struct or union field; make a FIELD_DECL.
   INITIALIZED is true if the decl has an initializer.
   WIDTH is non-NULL for bit-fields, and is a pointer to an INTEGER_CST node
   representing the width of the bit-field.
   DECL_ATTRS points to the list of attributes that should be added to this
     decl.  Any nested attributes that belong on the decl itself will be
     added to this list.
   If EXPR is not NULL, any expressions that need to be evaluated as
     part of evaluating variably modified types will be stored in *EXPR.
   If EXPR_CONST_OPERANDS is not NULL, *EXPR_CONST_OPERANDS will be
     set to indicate whether operands in *EXPR can be used in constant
     expressions.
   DEPRECATED_STATE is a deprecated_states value indicating whether
   deprecation/unavailability warnings should be suppressed.

   In the TYPENAME case, DECLARATOR is really an absolute declarator.
   It may also be so in the PARM case, for a prototype where the
   argument type is specified but not the name.

   This function is where the complicated C meanings of `static'
   and `extern' are interpreted.  */

ಸ್ಥಿರ ವೃಕ್ಷ
grokdeclarator (ಸ್ಥಿರಾಂಕ ರಚನೆ c_declarator *declarator,
		ರಚನೆ c_declspecs *declspecs,
		ಎಣಿಕೆ decl_context decl_context, ತಾರ್ಕಿಕ initialized, ವೃಕ್ಷ *ಅಗಲ,
		ವೃಕ್ಷ *decl_attrs, ವೃಕ್ಷ *ಅಭಿವ್ಯಕ್ತಿ, ತಾರ್ಕಿಕ *ಅಭಿವ್ಯಕ್ತಿ_const_operands,
		ಎಣಿಕೆ deprecated_ಸ್ಥಿತಿಗಳು deprecated_state)
{
  ವೃಕ್ಷ type = declspecs->type;
  ತಾರ್ಕಿಕ threadp = declspecs->thread_p;
  ತಾರ್ಕಿಕ constexprp = declspecs->constexpr_p;
  ಎಣಿಕೆ c_storage_class storage_class = declspecs->storage_class;
  ಪೂರ್ಣಾಂಕ constp;
  ಪೂರ್ಣಾಂಕ restrictp;
  ಪೂರ್ಣಾಂಕ volatilep;
  ಪೂರ್ಣಾಂಕ atomicp;
  ಪೂರ್ಣಾಂಕ type_quals = TYPE_UNQUALIFIED;
  ವೃಕ್ಷ name = NULL_ವೃಕ್ಷ;
  ತಾರ್ಕಿಕ funcdef_flag = ಸುಳ್ಳು;
  ತಾರ್ಕಿಕ funcdef_syntax = ಸುಳ್ಳು;
  ತಾರ್ಕಿಕ ಗಾತ್ರ_varies = ಸುಳ್ಳು;
  ತಾರ್ಕಿಕ ಗಾತ್ರ_error = ಸುಳ್ಳು;
  ವೃಕ್ಷ decl_attr = declspecs->decl_attr;
  ಪೂರ್ಣಾಂಕ array_ptr_quals = TYPE_UNQUALIFIED;
  ವೃಕ್ಷ array_ptr_attrs = NULL_ವೃಕ್ಷ;
  ತಾರ್ಕಿಕ array_parm_static = ಸುಳ್ಳು;
  ತಾರ್ಕಿಕ array_parm_vla_unspec_p = ಸುಳ್ಳು;
  ವೃಕ್ಷ returned_attrs = NULL_ವೃಕ್ಷ;
  ವೃಕ್ಷ decl_id_attrs = NULL_ವೃಕ್ಷ;
  ತಾರ್ಕಿಕ bitfield = ಅಗಲ != ಖಾಲಿ;
  ವೃಕ್ಷ element_type;
  ವೃಕ್ಷ orig_qual_type = ಖಾಲಿ;
  ಗಾತ್ರ_t orig_qual_ಪರೋಕ್ಷ = 0;
  ರಚನೆ c_arg_info *arg_info = 0;
  addr_space_t as1, as2, ವಿಳಾಸ_space;
  location_t loc = UNKNOWN_LOCATION;
  ವೃಕ್ಷ ಅಭಿವ್ಯಕ್ತಿ_dummy;
  ತಾರ್ಕಿಕ ಅಭಿವ್ಯಕ್ತಿ_const_operands_dummy;
  ಎಣಿಕೆ c_declarator_ಬಗೆ ಮೊದಲ_non_attr_ಬಗೆ;
  ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ alignas_align = 0;

  ಆದರೆ (type == NULL_ವೃಕ್ಷ)
    {
      /* This can occur for auto on a parameter in C23 mode.  Set a
	 dummy type here so subsequent code can give diagnostics for
	 this case.  */
      gcc_assert (declspecs->c23_auto_p);
      gcc_assert (decl_context == PARM);
      type = declspecs->type = integer_type_ಗಂಟು;
    }
  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (type) == ERROR_MARK)
    ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
  ಆದರೆ (ಅಭಿವ್ಯಕ್ತಿ == ಖಾಲಿ)
    {
      ಅಭಿವ್ಯಕ್ತಿ = &ಅಭಿವ್ಯಕ್ತಿ_dummy;
      ಅಭಿವ್ಯಕ್ತಿ_dummy = NULL_ವೃಕ್ಷ;
    }
  ಆದರೆ (ಅಭಿವ್ಯಕ್ತಿ_const_operands == ಖಾಲಿ)
    ಅಭಿವ್ಯಕ್ತಿ_const_operands = &ಅಭಿವ್ಯಕ್ತಿ_const_operands_dummy;

  ಆದರೆ (declspecs->ಅಭಿವ್ಯಕ್ತಿ)
    {
      ಆದರೆ (*ಅಭಿವ್ಯಕ್ತಿ)
	*ಅಭಿವ್ಯಕ್ತಿ = build2 (COMPOUND_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (declspecs->ಅಭಿವ್ಯಕ್ತಿ), *ಅಭಿವ್ಯಕ್ತಿ,
			declspecs->ಅಭಿವ್ಯಕ್ತಿ);
      ಇಲ್ಲದಿದ್ದರೆ
	*ಅಭಿವ್ಯಕ್ತಿ = declspecs->ಅಭಿವ್ಯಕ್ತಿ;
    }
  *ಅಭಿವ್ಯಕ್ತಿ_const_operands = declspecs->ಅಭಿವ್ಯಕ್ತಿ_const_operands;

  ಆದರೆ (decl_context == FUNCDEF)
    funcdef_flag = ನಿಜ, decl_context = ಸಾಮಾನ್ಯ;

  /* Look inside a declarator for the name being declared
     and get it as an IDENTIFIER_NODE, for an error message.  */
  {
    ಸ್ಥಿರಾಂಕ ರಚನೆ c_declarator *decl = declarator;

    ಮೊದಲ_non_attr_ಬಗೆ = cdk_attrs;
    ಆಗ (decl)
      ಆಯ್ಕೆ (decl->ಬಗೆ)
	{
	ಸ್ಥಿತಿ cdk_array:
	  loc = decl->id_loc;
	  /* FALL THRU.  */

	ಸ್ಥಿತಿ cdk_function:
	ಸ್ಥಿತಿ cdk_ಸೂಚಕ:
	  funcdef_syntax = (decl->ಬಗೆ == cdk_function);
	  ಆದರೆ (ಮೊದಲ_non_attr_ಬಗೆ == cdk_attrs)
	    ಮೊದಲ_non_attr_ಬಗೆ = decl->ಬಗೆ;
	  decl = decl->declarator;
	  ನಿಲ್ಲಿಸು;

	ಸ್ಥಿತಿ cdk_attrs:
	  decl = decl->declarator;
	  ನಿಲ್ಲಿಸು;

	ಸ್ಥಿತಿ cdk_id:
	  loc = decl->id_loc;
	  ಆದರೆ (decl->u.id.id)
	    name = decl->u.id.id;
	  decl_id_attrs = decl->u.id.attrs;
	  ಆದರೆ (ಮೊದಲ_non_attr_ಬಗೆ == cdk_attrs)
	    ಮೊದಲ_non_attr_ಬಗೆ = decl->ಬಗೆ;
	  decl = 0;
	  ನಿಲ್ಲಿಸು;

	ಪೂರ್ವನಿಯೋಜಿತ:
	  gcc_unreachable ();
	}
    ಆದರೆ (name == NULL_ವೃಕ್ಷ)
      {
	gcc_assert (decl_context == PARM
		    || decl_context == TYPENAME
		    || decl_context == GENERIC_ASSOC
		    || (decl_context == ಕ್ಷೇತ್ರ
			&& declarator->ಬಗೆ == cdk_id));
	gcc_assert (!initialized);
      }
  }

  /* An enum type specifier (": specifier-qualifier-list") may only be
     specified when the enum is being defined or in an empty
     declaration of the form "enum identifier enum-type-specifier;".
     Except for the case of an empty declaration that has additional
     declaration specifiers, all invalid contexts (declarations that
     aren't empty, type names, parameter declarations, member
     declarations) pass through grokdeclarator.  */
  ಆದರೆ (declspecs->enum_type_specifier_ref_p)
    error_at (loc, "%<enum%> underlying type may not be specified here");

  /* A function definition's declarator must have the form of
     a function declarator.  */

  ಆದರೆ (funcdef_flag && !funcdef_syntax)
    ಹಿಂತಿರುಗಿ NULL_ವೃಕ್ಷ;

  /* If this looks like a function definition, make it one,
     even if it occurs where parms are expected.
     Then store_parm_decls will reject it and not use it as a parm.  */
  ಆದರೆ (decl_context == ಸಾಮಾನ್ಯ && !funcdef_flag && current_scope->parm_flag)
    decl_context = PARM;

  ಆದರೆ (deprecated_state != UNAVAILABLE_DEPRECATED_SUPPRESS)
    {
      ಆದರೆ (declspecs->unavailable_p)
	error_unavailable_use (declspecs->type, declspecs->decl_attr);
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (declspecs->deprecated_p
		&& deprecated_state != DEPRECATED_SUPPRESS)
	warn_deprecated_use (declspecs->type, declspecs->decl_attr);
    }

  ಆದರೆ ((decl_context == ಸಾಮಾನ್ಯ || decl_context == ಕ್ಷೇತ್ರ)
      && current_scope == file_scope
      && c_type_variably_modified_p (type))
    {
      ಆದರೆ (name)
	error_at (loc, "variably modified %qE at file scope", name);
      ಇಲ್ಲದಿದ್ದರೆ
	error_at (loc, "variably modified field at file scope");
      type = integer_type_ಗಂಟು;
    }

  ಗಾತ್ರ_varies = C_TYPE_VARIABLE_ಗಾತ್ರ (type) != 0;

  /* Diagnose defaulting to "int".  */

  ಆದರೆ (declspecs->default_int_p)
    {
      /* Issue a warning if this is an ISO C 99 program or if
	 -Wreturn-type and this is a function, or if -Wimplicit;
	 prefer the former warning since it is more explicit.  */
      ಆದರೆ ((warn_implicit_int || warn_return_type > 0 || flag_isoc99)
	  && funcdef_flag)
	warn_about_return_type = 1;
      ಇಲ್ಲದಿದ್ದರೆ
	{
	  ಆದರೆ (name)
	    permerror_opt (loc, OPT_Wimplicit_int,
			   "type defaults to %<int%> in declaration "
			   "of %qE", name);
	  ಇಲ್ಲದಿದ್ದರೆ
	    permerror_opt (loc, OPT_Wimplicit_int,
			   "type defaults to %<int%> in type name");
	}
    }

  /* Adjust the type if a bit-field is being declared,
     -funsigned-bitfields applied and the type is not explicitly
     "signed".  */
  ಆದರೆ (bitfield && !flag_signed_bitfields && !declspecs->explicit_signed_p
      && ವೃಕ್ಷ_ಸಂಕೇತ (type) == INTEGER_TYPE)
    type = c_common_unsigned_type (type);

  /* Figure out the type qualifiers for the declaration.  There are
     two ways a declaration can become qualified.  One is something
     like `const int i' where the `const' is explicit.  Another is
     something like `typedef const int CI; CI i' where the type of the
     declaration contains the `const'.  A third possibility is that
     there is a type qualifier on the element type of a typedefed
     array type, in which case we should extract that qualifier so
     that c_apply_type_quals_to_decl receives the full list of
     qualifiers to work with (C90 is not entirely clear about whether
     duplicate qualifiers should be diagnosed in this case, but it
     seems most appropriate to do so).  */
  element_type = strip_array_types (type);
  constp = declspecs->const_p + TYPE_READONLY (element_type);
  restrictp = declspecs->restrict_p + TYPE_RESTRICT (element_type);
  volatilep = declspecs->volatile_p + TYPE_VOLATILE (element_type);
  atomicp = declspecs->atomic_p + TYPE_ATOMIC (element_type);
  as1 = declspecs->ವಿಳಾಸ_space;
  as2 = TYPE_ADDR_SPACE (element_type);
  ವಿಳಾಸ_space = ADDR_SPACE_GENERIC_P (as1)? as2 : as1;

  ಆದರೆ (constp > 1)
    pedwarn_c90 (loc, OPT_Wpedantic, "duplicate %<const%>");
  ಆದರೆ (restrictp > 1)
    pedwarn_c90 (loc, OPT_Wpedantic, "duplicate %<restrict%>");
  ಆದರೆ (volatilep > 1)
    pedwarn_c90 (loc, OPT_Wpedantic, "duplicate %<volatile%>");
  ಆದರೆ (atomicp > 1)
    pedwarn_c90 (loc, OPT_Wpedantic, "duplicate %<_Atomic%>");

  ಆದರೆ (!ADDR_SPACE_GENERIC_P (as1) && !ADDR_SPACE_GENERIC_P (as2) && as1 != as2)
    error_at (loc, "conflicting named address spaces (%s vs %s)",
	      c_addr_space_name (as1), c_addr_space_name (as2));

  ಆದರೆ ((ವೃಕ್ಷ_ಸಂಕೇತ (type) == ARRAY_TYPE
       || ಮೊದಲ_non_attr_ಬಗೆ == cdk_array)
      && TYPE_QUALS (element_type))
    {
      orig_qual_type = type;
      type = c_build_qualified_type (type, TYPE_UNQUALIFIED);
    }
  type_quals = ((constp ? TYPE_QUAL_CONST : 0)
		| (restrictp ? TYPE_QUAL_RESTRICT : 0)
		| (volatilep ? TYPE_QUAL_VOLATILE : 0)
		| (atomicp ? TYPE_QUAL_ATOMIC : 0)
		| ENCODE_QUAL_ADDR_SPACE (ವಿಳಾಸ_space));
  ಆದರೆ (type_quals != TYPE_QUALS (element_type))
    orig_qual_type = NULL_ವೃಕ್ಷ;

  /* Applying the _Atomic qualifier to an array type (through the use
     of typedefs or typeof) must be detected here.  If the qualifier
     is introduced later, any appearance of applying it to an array is
     actually applying it to an element of that array.  */
  ಆದರೆ (declspecs->atomic_p && ವೃಕ್ಷ_ಸಂಕೇತ (type) == ARRAY_TYPE)
    error_at (loc, "%<_Atomic%>-qualified array type");

  /* Warn about storage classes that are invalid for certain
     kinds of declarations (parameters, typenames, etc.).  */

  ಆದರೆ (funcdef_flag
      && (threadp
	  || constexprp
	  || storage_class == csc_auto
	  || storage_class == csc_ರಿಜಿಸ್ಟರ್
	  || storage_class == csc_typedef))
    {
      ಆದರೆ (storage_class == csc_auto)
	pedwarn (loc,
		 (current_scope == file_scope) ? 0 : OPT_Wpedantic,
		 "function definition declared %<auto%>");
      ಆದರೆ (storage_class == csc_ರಿಜಿಸ್ಟರ್)
	error_at (loc, "function definition declared %<register%>");
      ಆದರೆ (storage_class == csc_typedef)
	error_at (loc, "function definition declared %<typedef%>");
      ಆದರೆ (threadp)
	error_at (loc, "function definition declared %qs",
		  declspecs->thread_gnu_p ? "__thread" : "_Thread_local");
      threadp = ಸುಳ್ಳು;
      /* The parser ensures a constexpr function definition never
	 reaches here.  */
      gcc_assert (!constexprp);
      ಆದರೆ (storage_class == csc_auto
	  || storage_class == csc_ರಿಜಿಸ್ಟರ್
	  || storage_class == csc_typedef)
	storage_class = csc_none;
    }
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (decl_context != ಸಾಮಾನ್ಯ && (storage_class != csc_none
				      || threadp
				      || constexprp
				      || declspecs->c23_auto_p))
    {
      ಆದರೆ (decl_context == PARM
	  && storage_class == csc_ರಿಜಿಸ್ಟರ್
	  && !constexprp
	  && !declspecs->c23_auto_p)
	;
      ಇಲ್ಲದಿದ್ದರೆ
	{
	  ಆಯ್ಕೆ (decl_context)
	    {
	    ಸ್ಥಿತಿ ಕ್ಷೇತ್ರ:
	      ಆದರೆ (name)
		error_at (loc, "storage class specified for structure "
		    	  "field %qE", name);
	      ಇಲ್ಲದಿದ್ದರೆ
		error_at (loc, "storage class specified for structure field");
	      ನಿಲ್ಲಿಸು;
	    ಸ್ಥಿತಿ PARM:
	      ಆದರೆ (name)
		error_at (loc, "storage class specified for parameter %qE",
		    	  name);
	      ಇಲ್ಲದಿದ್ದರೆ
		error_at (loc, "storage class specified for unnamed parameter");
	      ನಿಲ್ಲಿಸು;
	    ಪೂರ್ವನಿಯೋಜಿತ:
	      error_at (loc, "storage class specified for typename");
	      ನಿಲ್ಲಿಸು;
	    }
	  storage_class = csc_none;
	  threadp = ಸುಳ್ಳು;
	  constexprp = ಸುಳ್ಳು;
	}
    }
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (storage_class == csc_extern
	   && initialized
	   && !funcdef_flag)
    {
      /* 'extern' with initialization is invalid if not at file scope.  */
       ಆದರೆ (current_scope == file_scope)
         {
           /* It is fine to have 'extern const' when compiling at C
              and C++ intersection.  */
           ಆದರೆ (!(warn_cxx_compat && constp))
             warning_at (loc, 0, "%qE initialized and declared %<extern%>",
		 	 name);
         }
      ಇಲ್ಲದಿದ್ದರೆ
	error_at (loc, "%qE has both %<extern%> and initializer", name);
    }
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (current_scope == file_scope)
    {
      ಆದರೆ (storage_class == csc_auto)
	error_at (loc, "file-scope declaration of %qE specifies %<auto%>",
	    	  name);
      ಆದರೆ (pedantic && storage_class == csc_ರಿಜಿಸ್ಟರ್)
	pedwarn (ಒಳಹರಿವು_location, OPT_Wpedantic,
		 "file-scope declaration of %qE specifies %<register%>", name);
    }
  ಇಲ್ಲದಿದ್ದರೆ
    {
      ಆದರೆ (storage_class == csc_extern && funcdef_flag)
	error_at (loc, "nested function %qE declared %<extern%>", name);
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (threadp && storage_class == csc_none)
	{
	  error_at (loc, "function-scope %qE implicitly auto and declared "
		    "%qs", name,
		    declspecs->thread_gnu_p ? "__thread" : "_Thread_local");
	  threadp = ಸುಳ್ಳು;
	}
    }

  /* Now figure out the structure of the declarator proper.
     Descend through it, creating more complex types, until we reach
     the declared identifier (or NULL_TREE, in an absolute declarator).
     At each stage we maintain an unqualified version of the type
     together with any qualifiers that should be applied to it with
     c_build_qualified_type; this way, array types including
     multidimensional array types are first built up in unqualified
     form and then the qualified form is created with
     TYPE_MAIN_VARIANT pointing to the unqualified form.  */

  ಆಗ (declarator && declarator->ಬಗೆ != cdk_id)
    {
      ಆದರೆ (type == error_mark_ಗಂಟು)
	{
	  declarator = declarator->declarator;
	  ಮುಂದುವರಿ;
	}

      /* Each level of DECLARATOR is either a cdk_array (for ...[..]),
	 a cdk_pointer (for *...),
	 a cdk_function (for ...(...)),
	 a cdk_attrs (for nested attributes),
	 or a cdk_id (for the name being declared
	 or the place in an absolute declarator
	 where the name was omitted).
	 For the last case, we have just exited the loop.

	 At this point, TYPE is the type of elements of an array,
	 or for a function to return, or for a pointer to point to.
	 After this sequence of ifs, TYPE is the type of the
	 array or function or pointer, and DECLARATOR has had its
	 outermost layer removed.  */

      ಆದರೆ (array_ptr_quals != TYPE_UNQUALIFIED
	  || array_ptr_attrs != NULL_ವೃಕ್ಷ
	  || array_parm_static)
	{
	  /* Only the innermost declarator (making a parameter be of
	     array type which is converted to pointer type)
	     may have static or type qualifiers.  */
	  error_at (loc, "static or type qualifiers in non-parameter array declarator");
	  array_ptr_quals = TYPE_UNQUALIFIED;
	  array_ptr_attrs = NULL_ವೃಕ್ಷ;
	  array_parm_static = ಸುಳ್ಳು;
	}

      ಆಯ್ಕೆ (declarator->ಬಗೆ)
	{
	ಸ್ಥಿತಿ cdk_attrs:
	  {
	    /* A declarator with embedded attributes.  */
	    ವೃಕ್ಷ attrs = declarator->u.attrs;
	    ಸ್ಥಿರಾಂಕ ರಚನೆ c_declarator *inner_decl;
	    ಪೂರ್ಣಾಂಕ attr_flags = 0;
	    declarator = declarator->declarator;
	    /* Standard attribute syntax precisely defines what entity
	       an attribute in each position appertains to, so only
	       apply laxity about positioning to GNU attribute syntax.
	       Standard attributes applied to a function or array
	       declarator apply exactly to that type; standard
	       attributes applied to the identifier apply to the
	       declaration rather than to the type, and are specified
	       using a cdk_id declarator rather than using
	       cdk_attrs.  */
	    inner_decl = declarator;
	    ಆಗ (inner_decl->ಬಗೆ == cdk_attrs)
	      inner_decl = inner_decl->declarator;
	    ಆದರೆ (!cxx11_attribute_p (attrs))
	      {
		ಆದರೆ (inner_decl->ಬಗೆ == cdk_id)
		  attr_flags |= (ಪೂರ್ಣಾಂಕ) ATTR_FLAG_DECL_ಮುಂದಿನ;
		ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (inner_decl->ಬಗೆ == cdk_function)
		  attr_flags |= (ಪೂರ್ಣಾಂಕ) ATTR_FLAG_FUNCTION_ಮುಂದಿನ;
		ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (inner_decl->ಬಗೆ == cdk_array)
		  attr_flags |= (ಪೂರ್ಣಾಂಕ) ATTR_FLAG_ARRAY_ಮುಂದಿನ;
	      }
	    attrs = c_warn_type_ಗುಣಲಕ್ಷಣಗಳು (type, attrs);
	    returned_attrs = decl_ಗುಣಲಕ್ಷಣಗಳು (&type,
					      chainon (returned_attrs, attrs),
					      attr_flags);
	    ನಿಲ್ಲಿಸು;
	  }
	ಸ್ಥಿತಿ cdk_array:
	  {
	    ವೃಕ್ಷ itype = NULL_ವೃಕ್ಷ;
	    ವೃಕ್ಷ ಗಾತ್ರ_2 = declarator->u.array.dimen;
	    /* The index is a signed object `sizetype' bits wide.  */
	    ವೃಕ್ಷ ಸೂಚ್ಯಂಕ_type = c_common_signed_type (sizetype);

	    array_ptr_quals = declarator->u.array.quals;
	    array_ptr_attrs = declarator->u.array.attrs;
	    array_parm_static = declarator->u.array.static_p;
	    array_parm_vla_unspec_p = declarator->u.array.vla_unspec_p;

	    declarator = declarator->declarator;

	    ತಾರ್ಕಿಕ flexible_array_member = ಸುಳ್ಳು;

	    /* Check for some types that there cannot be arrays of.  */

	    ಆದರೆ (VOID_TYPE_P (type))
	      {
		ಆದರೆ (name)
		  error_at (loc, "declaration of %qE as array of voids", name);
		ಇಲ್ಲದಿದ್ದರೆ
		  error_at (loc, "declaration of type name as array of voids");
		type = error_mark_ಗಂಟು;
	      }

	    ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (type) == FUNCTION_TYPE)
	      {
		ಆದರೆ (name)
		  error_at (loc, "declaration of %qE as array of functions",
		      	    name);
		ಇಲ್ಲದಿದ್ದರೆ
		  error_at (loc, "declaration of type name as array of "
		            "functions");
		type = error_mark_ಗಂಟು;
	      }

	    ಆದರೆ (pedantic && !ಒಳ_system_ಶೀರ್ಷಿಕೆ_at (ಒಳಹರಿವು_location)
		&& flexible_array_type_p (type))
	      pedwarn (loc, OPT_Wpedantic,
		       "invalid use of structure with flexible array member");

	    ಆದರೆ (ಗಾತ್ರ_2 == error_mark_ಗಂಟು)
	      type = error_mark_ಗಂಟು;

	    ಆದರೆ (type == error_mark_ಗಂಟು)
	      ಮುಂದುವರಿ;

	    ಆದರೆ (!verify_type_context (loc, TCTX_ARRAY_ELEMENT, type))
	      {
		type = error_mark_ಗಂಟು;
		ಮುಂದುವರಿ;
	      }

	    /* If size was specified, set ITYPE to a range-type for
	       that size.  Otherwise, ITYPE remains null.  finish_decl
	       may figure it out from an initial value.  */

	    ಆದರೆ (ಗಾತ್ರ_2)
	      {
		ತಾರ್ಕಿಕ ಗಾತ್ರ_maybe_const = ನಿಜ;
		ತಾರ್ಕಿಕ ಗಾತ್ರ_int_const = (ವೃಕ್ಷ_ಸಂಕೇತ (ಗಾತ್ರ_2) == INTEGER_CST
				       && !ವೃಕ್ಷ_ಅತಿಪ್ರವಾಹ (ಗಾತ್ರ_2));
		ತಾರ್ಕಿಕ this_ಗಾತ್ರ_varies = ಸುಳ್ಳು;

		/* Strip NON_LVALUE_EXPRs since we aren't using as an
		   lvalue.  */
		STRIP_TYPE_NOPS (ಗಾತ್ರ_2);

		ಆದರೆ (!INTEGRAL_TYPE_P (ವೃಕ್ಷ_TYPE (ಗಾತ್ರ_2)))
		  {
		    ಆದರೆ (name)
		      error_at (loc, "size of array %qE has non-integer type",
				name);
		    ಇಲ್ಲದಿದ್ದರೆ
		      error_at (loc,
				"size of unnamed array has non-integer type");
		    ಗಾತ್ರ_2 = integer_one_ಗಂಟು;
		    ಗಾತ್ರ_int_const = ನಿಜ;
		    ಗಾತ್ರ_error = ನಿಜ;
		  }
		/* This can happen with enum forward declaration.  */
		ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!COMPLETE_TYPE_P (ವೃಕ್ಷ_TYPE (ಗಾತ್ರ_2)))
		  {
		    ಆದರೆ (name)
		      error_at (loc, "size of array %qE has incomplete type",
				name);
		    ಇಲ್ಲದಿದ್ದರೆ
		      error_at (loc, "size of unnamed array has incomplete "
				"type");
		    ಗಾತ್ರ_2 = integer_one_ಗಂಟು;
		    ಗಾತ್ರ_int_const = ನಿಜ;
		    ಗಾತ್ರ_error = ನಿಜ;
		  }

		ಗಾತ್ರ_2 = c_fully_fold (ಗಾತ್ರ_2, ಸುಳ್ಳು, &ಗಾತ್ರ_maybe_const);

		ಆದರೆ (pedantic && ಗಾತ್ರ_maybe_const && integer_zerop (ಗಾತ್ರ_2))
		  {
		    ಆದರೆ (name)
		      pedwarn (loc, OPT_Wpedantic,
			       "ISO C forbids zero-size array %qE", name);
		    ಇಲ್ಲದಿದ್ದರೆ
		      pedwarn (loc, OPT_Wpedantic,
			       "ISO C forbids zero-size array");
		  }

		ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ಗಾತ್ರ_2) == INTEGER_CST && ಗಾತ್ರ_maybe_const)
		  {
		    constant_ಅಭಿವ್ಯಕ್ತಿ_warning (ಗಾತ್ರ_2);
		    ಆದರೆ (ವೃಕ್ಷ_int_cst_sgn (ಗಾತ್ರ_2) < 0)
		      {
			ಆದರೆ (name)
			  error_at (loc, "size of array %qE is negative", name);
			ಇಲ್ಲದಿದ್ದರೆ
			  error_at (loc, "size of unnamed array is negative");
			ಗಾತ್ರ_2 = integer_one_ಗಂಟು;
			ಗಾತ್ರ_int_const = ನಿಜ;
			ಗಾತ್ರ_error = ನಿಜ;
		      }
		    /* Handle a size folded to an integer constant but
		       not an integer constant expression.  */
		    ಆದರೆ (!ಗಾತ್ರ_int_const)
		      {
			/* If this is a file scope declaration of an
			   ordinary identifier, this is invalid code;
			   diagnosing it here and not subsequently
			   treating the type as variable-length avoids
			   more confusing diagnostics later.  */
			ಆದರೆ ((decl_context == ಸಾಮಾನ್ಯ || decl_context == ಕ್ಷೇತ್ರ)
			    && current_scope == file_scope)
			  pedwarn (ಒಳಹರಿವು_location, 0,
				   "variably modified %qE at file scope",
				   name);
			ಇಲ್ಲದಿದ್ದರೆ
			  this_ಗಾತ್ರ_varies = ಗಾತ್ರ_varies = ನಿಜ;
			warn_variable_ಉದ್ದಳತೆ_array (name, ಗಾತ್ರ_2);
		      }
		  }
		ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ ((decl_context == ಸಾಮಾನ್ಯ || decl_context == ಕ್ಷೇತ್ರ)
			 && current_scope == file_scope)
		  {
		    error_at (loc, "variably modified %qE at file scope", name);
		    ಗಾತ್ರ_2 = integer_one_ಗಂಟು;
		  }
		ಇಲ್ಲದಿದ್ದರೆ
		  {
		    /* Make sure the array size remains visibly
		       nonconstant even if it is (eg) a const variable
		       with known value.  */
		    this_ಗಾತ್ರ_varies = ಗಾತ್ರ_varies = ನಿಜ;
		    warn_variable_ಉದ್ದಳತೆ_array (name, ಗಾತ್ರ_2);
		    ಆದರೆ (sanitize_flags_p (SANITIZE_VLA)
			&& current_function_decl != NULL_ವೃಕ್ಷ
			&& decl_context == ಸಾಮಾನ್ಯ)
		      {
			/* Evaluate the array size only once.  */
			ಗಾತ್ರ_2 = save_ಅಭಿವ್ಯಕ್ತಿ (ಗಾತ್ರ_2);
			ಗಾತ್ರ_2 = c_fully_fold (ಗಾತ್ರ_2, ಸುಳ್ಳು, ಖಾಲಿ);
		        ಗಾತ್ರ_2 = fold_build2 (COMPOUND_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (ಗಾತ್ರ_2),
					    ubsan_instrument_vla (loc, ಗಾತ್ರ_2),
					    ಗಾತ್ರ_2);
		      }
		  }

		ಆದರೆ (integer_zerop (ಗಾತ್ರ_2) && !this_ಗಾತ್ರ_varies)
		  {
		    /* A zero-length array cannot be represented with
		       an unsigned index type, which is what we'll
		       get with build_index_type.  Create an
		       open-ended range instead.  */
		    itype = build_ಸೂಚ್ಯಂಕ_type (NULL_ವೃಕ್ಷ);
		  }
		ಇಲ್ಲದಿದ್ದರೆ
		  {
		    /* Arrange for the SAVE_EXPR on the inside of the
		       MINUS_EXPR, which allows the -1 to get folded
		       with the +1 that happens when building TYPE_SIZE.  */
		    ಆದರೆ (ಗಾತ್ರ_varies)
		      ಗಾತ್ರ_2 = save_ಅಭಿವ್ಯಕ್ತಿ (ಗಾತ್ರ_2);
		    ಆದರೆ (this_ಗಾತ್ರ_varies && ವೃಕ್ಷ_ಸಂಕೇತ (ಗಾತ್ರ_2) == INTEGER_CST)
		      ಗಾತ್ರ_2 = build2 (COMPOUND_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (ಗಾತ್ರ_2),
				     integer_zero_ಗಂಟು, ಗಾತ್ರ_2);

		    /* Compute the maximum valid index, that is, size
		       - 1.  Do the calculation in index_type, so that
		       if it is a variable the computations will be
		       done in the proper mode.  */
		    itype = fold_build2_loc (loc, MINUS_ಅಭಿವ್ಯಕ್ತಿ, ಸೂಚ್ಯಂಕ_type,
					     convert (ಸೂಚ್ಯಂಕ_type, ಗಾತ್ರ_2),
					     convert (ಸೂಚ್ಯಂಕ_type,
						      ಗಾತ್ರ_one_ಗಂಟು));

		    /* The above overflows when size does not fit
		       in index_type.
		       ???  While a size of INT_MAX+1 technically shouldn't
		       cause an overflow (because we subtract 1), handling
		       this case seems like an unnecessary complication.  */
		    ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ಗಾತ್ರ_2) == INTEGER_CST
			&& !int_ಹೊಂದುತ್ತದೆ_type_p (ಗಾತ್ರ_2, ಸೂಚ್ಯಂಕ_type))
		      {
			ಆದರೆ (name)
			  error_at (loc, "size of array %qE is too large",
			            name);
			ಇಲ್ಲದಿದ್ದರೆ
			  error_at (loc, "size of unnamed array is too large");
			type = error_mark_ಗಂಟು;
			ಮುಂದುವರಿ;
		      }

		    itype = build_ಸೂಚ್ಯಂಕ_type (itype);
		  }
		ಆದರೆ (this_ಗಾತ್ರ_varies)
		  {
		    ಆದರೆ (ವೃಕ್ಷ_SIDE_EFFECTS (ಗಾತ್ರ_2))
		      {
			ಆದರೆ (*ಅಭಿವ್ಯಕ್ತಿ)
			  *ಅಭಿವ್ಯಕ್ತಿ = build2 (COMPOUND_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (ಗಾತ್ರ_2),
					  *ಅಭಿವ್ಯಕ್ತಿ, ಗಾತ್ರ_2);
			ಇಲ್ಲದಿದ್ದರೆ
			  *ಅಭಿವ್ಯಕ್ತಿ = ಗಾತ್ರ_2;
		      }
		    *ಅಭಿವ್ಯಕ್ತಿ_const_operands &= ಗಾತ್ರ_maybe_const;
		  }
	      }
	    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (decl_context == ಕ್ಷೇತ್ರ)
	      {
		ಆದರೆ (array_parm_vla_unspec_p)
		  /* Field names can in fact have function prototype
		     scope so [*] is disallowed here through making
		     the field variably modified, not through being
		     something other than a declaration with function
		     prototype scope.  */
		  ಗಾತ್ರ_varies = ನಿಜ;
		ಇಲ್ಲದಿದ್ದರೆ
		  {
		    ಸ್ಥಿರಾಂಕ ರಚನೆ c_declarator *t = declarator;
		    ಆಗ (t->ಬಗೆ == cdk_attrs)
		      t = t->declarator;
		    flexible_array_member = (t->ಬಗೆ == cdk_id);
		  }
		ಆದರೆ (flexible_array_member
		    && !ಒಳ_system_ಶೀರ್ಷಿಕೆ_at (ಒಳಹರಿವು_location))
		  pedwarn_c90 (loc, OPT_Wpedantic, "ISO C90 does not "
			       "support flexible array members");

		/* ISO C99 Flexible array members are effectively
		   identical to GCC's zero-length array extension.  */
		ಆದರೆ (flexible_array_member)
		  itype = build_ಸೂಚ್ಯಂಕ_type (NULL_ವೃಕ್ಷ);
	      }

	    /* Complain about arrays of incomplete types.  */
	    ಆದರೆ (!COMPLETE_TYPE_P (type))
	      {
		auto_diagnostic_ಗುಂಪು d;
		error_at (loc, "array type has incomplete element type %qT",
			  type);
		/* See if we can be more helpful.  */
		ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (type) == ARRAY_TYPE)
		  {
		    ಆದರೆ (name)
		      inform (loc, "declaration of %qE as multidimensional "
			      "array must have bounds for all dimensions "
			      "except the first", name);
		    ಇಲ್ಲದಿದ್ದರೆ
		      inform (loc, "declaration of multidimensional array "
			      "must have bounds for all dimensions except "
			      "the first");
		  }
		type = error_mark_ಗಂಟು;
	      }
	    ಇಲ್ಲದಿದ್ದರೆ
	    /* When itype is NULL, a shared incomplete array type is
	       returned for all array of a given type.  Elsewhere we
	       make sure we don't complete that type before copying
	       it, but here we want to make sure we don't ever
	       modify the shared type, so we gcc_assert (itype)
	       below.  */
	      {
		addr_space_t as = DECODE_QUAL_ADDR_SPACE (type_quals);
		ಆದರೆ (!ADDR_SPACE_GENERIC_P (as) && as != TYPE_ADDR_SPACE (type))
		  type = c_build_qualified_type (type,
						 ENCODE_QUAL_ADDR_SPACE (as));
		ಆದರೆ (array_parm_vla_unspec_p)
		  type = c_build_array_type_unspecified (type);
		/* The GCC extension for zero-length arrays differs from
		   ISO flexible array members in that sizeof yields
		   zero.  */
		ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ಗಾತ್ರ_2 && integer_zerop (ಗಾತ್ರ_2))
		  type = c_build_array_type_zero_ಗಾತ್ರ (type);
		ಇಲ್ಲದಿದ್ದರೆ
		  type = c_build_array_type (type, itype);

		ಆದರೆ (!valid_array_ಗಾತ್ರ_p (loc, type, name))
		  type = error_mark_ಗಂಟು;
	      }

	    ಆದರೆ (array_parm_vla_unspec_p)
	      {
		/* C99 6.7.5.2p4 */
		ಆದರೆ (decl_context == TYPENAME)
		  warning (0, "%<[*]%> not in a declaration");
		ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (decl_context != GENERIC_ASSOC
			 && decl_context != PARM
			 && decl_context != ಕ್ಷೇತ್ರ)
		  {
		    error ("%<[*]%> not allowed in other than function prototype scope "
			   "or generic association");
		    type = error_mark_ಗಂಟು;
		  }
		ಗಾತ್ರ_varies = ನಿಜ;
	      }


	    gcc_assert (type == error_mark_ಗಂಟು
			|| flexible_array_member
			   == flexible_array_member_type_p (type));

	    ಆದರೆ (decl_context != PARM
		&& (array_ptr_quals != TYPE_UNQUALIFIED
		    || array_ptr_attrs != NULL_ವೃಕ್ಷ
		    || array_parm_static))
	      {
		error_at (loc, "static or type qualifiers in non-parameter "
			  "array declarator");
		array_ptr_quals = TYPE_UNQUALIFIED;
		array_ptr_attrs = NULL_ವೃಕ್ಷ;
		array_parm_static = ಸುಳ್ಳು;
	      }
	    orig_qual_ಪರೋಕ್ಷ++;
	    ನಿಲ್ಲಿಸು;
	  }
	ಸ್ಥಿತಿ cdk_function:
	  {
	    /* Say it's a definition only for the declarator closest
	       to the identifier, apart possibly from some
	       attributes.  */
	    ತಾರ್ಕಿಕ really_funcdef = ಸುಳ್ಳು;
	    ವೃಕ್ಷ arg_types;
	    orig_qual_type = NULL_ವೃಕ್ಷ;
	    ಆದರೆ (funcdef_flag)
	      {
		ಸ್ಥಿರಾಂಕ ರಚನೆ c_declarator *t = declarator->declarator;
		ಆಗ (t->ಬಗೆ == cdk_attrs)
		  t = t->declarator;
		really_funcdef = (t->ಬಗೆ == cdk_id);
	      }

	    /* Declaring a function type.  Make sure we have a valid
	       type for the function to return.  */
	    ಆದರೆ (type == error_mark_ಗಂಟು)
	      ಮುಂದುವರಿ;

	    ಗಾತ್ರ_varies = ಸುಳ್ಳು;

	    /* Warn about some types functions can't return.  */
	    ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (type) == FUNCTION_TYPE)
	      {
		ಆದರೆ (name)
		  error_at (loc, "%qE declared as function returning a "
		      		 "function", name);
		ಇಲ್ಲದಿದ್ದರೆ
		  error_at (loc, "type name declared as function "
			    "returning a function");
		type = integer_type_ಗಂಟು;
	      }
	    ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (type) == ARRAY_TYPE)
	      {
		ಆದರೆ (name)
		  error_at (loc, "%qE declared as function returning an array",
		      	    name);
		ಇಲ್ಲದಿದ್ದರೆ
		  error_at (loc, "type name declared as function returning "
		      	    "an array");
		type = integer_type_ಗಂಟು;
	      }

	    /* Construct the function type and go to the next
	       inner layer of declarator.  */
	    arg_info = declarator->u.arg_info;
	    arg_types = grokparms (arg_info, really_funcdef);

	    /* Type qualifiers before the return type of the function
	       qualify the return type, not the function type.  */
	    ಆದರೆ (type_quals)
	      {
		ಸ್ಥಿರಾಂಕ ಎಣಿಕೆ c_declspec_ಶಬ್ದ ignored_quals_list[] =
		  {
		    cdw_const, cdw_volatile, cdw_restrict, cdw_ವಿಳಾಸ_space,
		    cdw_atomic, cdw_ಸಂಖ್ಯೆ_ದ_elements
		  };
		location_t specs_loc
		  = ಅತಿಚಿಕ್ಕ_type_quals_location (declspecs->locations,
						  ignored_quals_list);
		ಆದರೆ (specs_loc == UNKNOWN_LOCATION)
		  specs_loc = declspecs->locations[cdw_typedef];
		ಆದರೆ (specs_loc == UNKNOWN_LOCATION)
		  specs_loc = loc;

		/* Type qualifiers on a function return type are
		   normally permitted by the standard but have no
		   effect, so give a warning at -Wreturn-type.
		   Qualifiers on a void return type are banned on
		   function definitions in ISO C; GCC used to used
		   them for noreturn functions.  The resolution of C11
		   DR#423 means qualifiers (other than _Atomic) are
		   actually removed from the return type when
		   determining the function type.  For C23, _Atomic is
		   removed as well.  */
		ಪೂರ್ಣಾಂಕ quals_ಬಳಸಿದ = type_quals;
		ಆದರೆ (flag_isoc23)
		  quals_ಬಳಸಿದ = 0;
		ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (flag_isoc11)
		  quals_ಬಳಸಿದ &= TYPE_QUAL_ATOMIC;
		ಆದರೆ (quals_ಬಳಸಿದ && VOID_TYPE_P (type) && really_funcdef)
		  pedwarn (specs_loc, 0,
			   "function definition has qualified void "
			   "return type");
		ಇಲ್ಲದಿದ್ದರೆ
		  warning_at (specs_loc, OPT_Wignored_qualifiers,
			      "type qualifiers ignored on function "
			      "return type");

		/* Ensure an error for restrict on invalid types; the
		   DR#423 resolution is not entirely clear about
		   this.  */
		ಆದರೆ (flag_isoc11
		    && (type_quals & TYPE_QUAL_RESTRICT)
		    && (!ಸೂಚಕ_TYPE_P (type)
			|| !C_TYPE_OBJECT_OR_INCOMPLETE_P (ವೃಕ್ಷ_TYPE (type))))
		  error_at (loc, "invalid use of %<restrict%>");
		type = c_build_qualified_type (type, quals_ಬಳಸಿದ);
	      }
	    type_quals = TYPE_UNQUALIFIED;

	    type = c_build_function_type (type, arg_types,
					  arg_info->no_named_ವಾದಗಳು_stdarg_p);
	    declarator = declarator->declarator;

	    /* Set the TYPE_CONTEXTs for each tagged type which is local to
	       the formal parameter list of this FUNCTION_TYPE to point to
	       the FUNCTION_TYPE node itself.  */
	    {
	      c_arg_ಟ್ಯಾಗ್ *ಟ್ಯಾಗ್;
	      ಚಿಹ್ನೆರಹಿತ ix;

	      FOR_EACH_VEC_ಸುರಕ್ಷಿತ_ELT_ಹಿಮ್ಮುಖ (arg_info->ಟ್ಯಾಗುಗಳು, ix, ಟ್ಯಾಗ್)
		TYPE_CONTEXT (ಟ್ಯಾಗ್->type) = type;
	    }
	    ನಿಲ್ಲಿಸು;
	  }
	ಸ್ಥಿತಿ cdk_ಸೂಚಕ:
	  {
	    /* Merge any constancy or volatility into the target type
	       for the pointer.  */
	    ಆದರೆ ((type_quals & TYPE_QUAL_ATOMIC)
		&& ವೃಕ್ಷ_ಸಂಕೇತ (type) == FUNCTION_TYPE)
	      {
		error_at (loc,
			  "%<_Atomic%>-qualified function type");
		type_quals &= ~TYPE_QUAL_ATOMIC;
	      }
	    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (pedantic && ವೃಕ್ಷ_ಸಂಕೇತ (type) == FUNCTION_TYPE
		     && type_quals)
	      pedwarn (loc, OPT_Wpedantic,
		       "ISO C forbids qualified function types");
	    ಆದರೆ (type_quals)
	      type = c_build_qualified_type (type, type_quals, orig_qual_type,
					     orig_qual_ಪರೋಕ್ಷ);
	    orig_qual_type = NULL_ವೃಕ್ಷ;
	    ಗಾತ್ರ_varies = ಸುಳ್ಳು;

	    /* When the pointed-to type involves components of variable size,
	       care must be taken to ensure that the size evaluation code is
	       emitted early enough to dominate all the possible later uses
	       and late enough for the variables on which it depends to have
	       been assigned.

	       This is expected to happen automatically when the pointed-to
	       type has a name/declaration of it's own, but special attention
	       is required if the type is anonymous. */
	    ಆದರೆ (!TYPE_NAME (type) && c_type_variably_modified_p (type))
	      {
		ತಾರ್ಕಿಕ bind_p = decl_context == TYPENAME
			      || decl_context == ಕ್ಷೇತ್ರ
			      || decl_context == PARM;
		ಕೂಡಿಸು_decl_ಅಭಿವ್ಯಕ್ತಿ (loc, type, bind_p ? ಅಭಿವ್ಯಕ್ತಿ : ಖಾಲಿ, ನಿಜ);
	      }

	    type = c_build_ಸೂಚಕ_type (type);

	    /* Process type qualifiers (such as const or volatile)
	       that were given inside the `*'.  */
	    type_quals = declarator->u.ಸೂಚಕ_quals;

	    declarator = declarator->declarator;
	    ನಿಲ್ಲಿಸು;
	  }
	ಪೂರ್ವನಿಯೋಜಿತ:
	  gcc_unreachable ();
	}
    }
  *decl_attrs = chainon (returned_attrs, *decl_attrs);
  *decl_attrs = chainon (decl_id_attrs, *decl_attrs);

  /* Now TYPE has the actual type, apart from any qualifiers in
     TYPE_QUALS.  */

  /* Warn about address space used for things other than static memory or
     pointers.  */
  ವಿಳಾಸ_space = DECODE_QUAL_ADDR_SPACE (type_quals);
  ಆದರೆ (!ADDR_SPACE_GENERIC_P (ವಿಳಾಸ_space))
    {
      ಆದರೆ (decl_context == ಸಾಮಾನ್ಯ)
	{
	  ಆಯ್ಕೆ (storage_class)
	    {
	    ಸ್ಥಿತಿ csc_auto:
	      error ("%qs combined with %<auto%> qualifier for %qE",
		     c_addr_space_name (ವಿಳಾಸ_space), name);
	      ನಿಲ್ಲಿಸು;
	    ಸ್ಥಿತಿ csc_ರಿಜಿಸ್ಟರ್:
	      error ("%qs combined with %<register%> qualifier for %qE",
		     c_addr_space_name (ವಿಳಾಸ_space), name);
	      ನಿಲ್ಲಿಸು;
	    ಸ್ಥಿತಿ csc_none:
	      ಆದರೆ (current_function_scope)
		{
		  error ("%qs specified for auto variable %qE",
			 c_addr_space_name (ವಿಳಾಸ_space), name);
		  ನಿಲ್ಲಿಸು;
		}
	      ನಿಲ್ಲಿಸು;
	    ಸ್ಥಿತಿ csc_static:
	    ಸ್ಥಿತಿ csc_extern:
	    ಸ್ಥಿತಿ csc_typedef:
	      ನಿಲ್ಲಿಸು;
	    ಪೂರ್ವನಿಯೋಜಿತ:
	      gcc_unreachable ();
	    }
	}
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (decl_context == PARM && ವೃಕ್ಷ_ಸಂಕೇತ (type) != ARRAY_TYPE)
	{
	  ಆದರೆ (name)
	    error ("%qs specified for parameter %qE",
		   c_addr_space_name (ವಿಳಾಸ_space), name);
	  ಇಲ್ಲದಿದ್ದರೆ
	    error ("%qs specified for unnamed parameter",
		   c_addr_space_name (ವಿಳಾಸ_space));
	}
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (decl_context == ಕ್ಷೇತ್ರ)
	{
	  ಆದರೆ (name)
	    error ("%qs specified for structure field %qE",
		   c_addr_space_name (ವಿಳಾಸ_space), name);
	  ಇಲ್ಲದಿದ್ದರೆ
	    error ("%qs specified for structure field",
		   c_addr_space_name (ವಿಳಾಸ_space));
	}
    }

  /* Check the type and width of a bit-field.  */
  ಆದರೆ (bitfield)
    {
      check_bitfield_type_and_ಅಗಲ (loc, &type, ಅಗಲ, name);
      /* C11 makes it implementation-defined (6.7.2.1#5) whether
	 atomic types are permitted for bit-fields; we have no code to
	 make bit-field accesses atomic, so disallow them.  */
      ಆದರೆ (type_quals & TYPE_QUAL_ATOMIC)
	{
	  ಆದರೆ (name)
	    error_at (loc, "bit-field %qE has atomic type", name);
	  ಇಲ್ಲದಿದ್ದರೆ
	    error_at (loc, "bit-field has atomic type");
	  type_quals &= ~TYPE_QUAL_ATOMIC;
	}
    }

  /* Reject invalid uses of _Alignas.  */
  ಆದರೆ (declspecs->alignas_p)
    {
      ಆದರೆ (storage_class == csc_typedef)
	error_at (loc, "alignment specified for typedef %qE", name);
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (storage_class == csc_ರಿಜಿಸ್ಟರ್)
	error_at (loc, "alignment specified for %<register%> object %qE",
		  name);
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (decl_context == PARM)
	{
	  ಆದರೆ (name)
	    error_at (loc, "alignment specified for parameter %qE", name);
	  ಇಲ್ಲದಿದ್ದರೆ
	    error_at (loc, "alignment specified for unnamed parameter");
	}
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (bitfield)
	{
	  ಆದರೆ (name)
	    error_at (loc, "alignment specified for bit-field %qE", name);
	  ಇಲ್ಲದಿದ್ದರೆ
	    error_at (loc, "alignment specified for unnamed bit-field");
	}
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (type) == FUNCTION_TYPE)
	error_at (loc, "alignment specified for function %qE", name);
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (declspecs->align_log != -1 && TYPE_P (type))
	{
	  alignas_align = 1U << declspecs->align_log;
	  ಆದರೆ (alignas_align < min_align_ದ_type (type))
	    {
	      ಆದರೆ (name)
		error_at (loc, "%<_Alignas%> specifiers cannot reduce "
			  "alignment of %qE", name);
	      ಇಲ್ಲದಿದ್ದರೆ
		error_at (loc, "%<_Alignas%> specifiers cannot reduce "
			  "alignment of unnamed field");
	      alignas_align = 0;
	    }
	}
    }

  /* If this is declaring a typedef name, return a TYPE_DECL.  */

  ಆದರೆ (storage_class == csc_typedef)
    {
      ವೃಕ್ಷ decl;
      ಆದರೆ ((type_quals & TYPE_QUAL_ATOMIC)
	  && ವೃಕ್ಷ_ಸಂಕೇತ (type) == FUNCTION_TYPE)
	{
	  error_at (loc,
		    "%<_Atomic%>-qualified function type");
	  type_quals &= ~TYPE_QUAL_ATOMIC;
	}
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (pedantic && ವೃಕ್ಷ_ಸಂಕೇತ (type) == FUNCTION_TYPE
	       && type_quals)
	pedwarn (loc, OPT_Wpedantic,
		 "ISO C forbids qualified function types");
      ಆದರೆ (type_quals)
	type = c_build_qualified_type (type, type_quals, orig_qual_type,
				       orig_qual_ಪರೋಕ್ಷ);
      decl = build_decl (declarator->id_loc,
			 TYPE_DECL, declarator->u.id.id, type);
      ಆದರೆ (declspecs->explicit_signed_p)
	C_TYPEDEF_EXPLICITLY_SIGNED (decl) = 1;
      ಆದರೆ (declspecs->inline_p)
	pedwarn (loc, 0,"typedef %q+D declared %<inline%>", decl);
      ಆದರೆ (declspecs->noreturn_p)
	pedwarn (loc, 0,"typedef %q+D declared %<_Noreturn%>", decl);

      ಆದರೆ (warn_cxx_compat && declarator->u.id.id != NULL_ವೃಕ್ಷ)
	{
	  ರಚನೆ c_binding *b = I_ಟ್ಯಾಗ್_BINDING (declarator->u.id.id);

	  ಆದರೆ (b != ಖಾಲಿ
	      && b->decl != NULL_ವೃಕ್ಷ
	      && (B_ಒಳ_CURRENT_SCOPE (b)
		  || (current_scope == file_scope && B_ಒಳ_EXTERNAL_SCOPE (b)))
	      && TYPE_MAIN_VARIANT (b->decl) != TYPE_MAIN_VARIANT (type))
	    {
	      auto_diagnostic_ಗುಂಪು d;
	      ಆದರೆ (warning_at (declarator->id_loc, OPT_Wc___compat,
			      "using %qD as both a typedef and a tag is "
			      "invalid in C++", decl)
		  && b->locus != UNKNOWN_LOCATION)
		inform (b->locus, "originally defined here");
	    }
	}

      ಹಿಂತಿರುಗಿ decl;
    }

  /* If this is a type name (such as, in a cast or sizeof),
     compute the type and return it now.  */

  ಆದರೆ (decl_context == TYPENAME || decl_context == GENERIC_ASSOC)
    {
      /* Note that the grammar rejects storage classes in typenames
	 and fields.  */
      gcc_assert (storage_class == csc_none && !threadp
		  && !declspecs->inline_p && !declspecs->noreturn_p);
      ಆದರೆ ((type_quals & TYPE_QUAL_ATOMIC)
	  && ವೃಕ್ಷ_ಸಂಕೇತ (type) == FUNCTION_TYPE)
	{
	  error_at (loc,
		    "%<_Atomic%>-qualified function type");
	  type_quals &= ~TYPE_QUAL_ATOMIC;
	}
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (pedantic && ವೃಕ್ಷ_ಸಂಕೇತ (type) == FUNCTION_TYPE
	       && type_quals)
	pedwarn (loc, OPT_Wpedantic,
		 "ISO C forbids const or volatile function types");
      ಆದರೆ (type_quals)
	type = c_build_qualified_type (type, type_quals, orig_qual_type,
				       orig_qual_ಪರೋಕ್ಷ);
      ಹಿಂತಿರುಗಿ type;
    }

  ಆದರೆ (pedantic && decl_context == ಕ್ಷೇತ್ರ
      && c_type_variably_modified_p (type))
    {
      /* C99 6.7.2.1p8 */
      pedwarn (loc, OPT_Wpedantic, "a member of a structure or union cannot "
	       "have a variably modified type");
    }

  /* Aside from typedefs and type names (handle above),
     `void' at top level (not within pointer)
     is allowed only in public variables.
     We don't complain about parms either, but that is because
     a better error message can be made later.  */

  ಆದರೆ (VOID_TYPE_P (type) && decl_context != PARM
      && !((decl_context != ಕ್ಷೇತ್ರ && ವೃಕ್ಷ_ಸಂಕೇತ (type) != FUNCTION_TYPE)
	    && (storage_class == csc_extern
		|| (current_scope == file_scope
		    && !(storage_class == csc_static
			 || storage_class == csc_ರಿಜಿಸ್ಟರ್)))))
    {
      error_at (loc, "variable or field %qE declared void", name);
      type = integer_type_ಗಂಟು;
    }

  /* Now create the decl, which may be a VAR_DECL, a PARM_DECL
     or a FUNCTION_DECL, depending on DECL_CONTEXT and TYPE.  */

  {
    ವೃಕ್ಷ decl;

    ಆದರೆ (decl_context == PARM)
      {
	ವೃಕ್ಷ promoted_type;
	ತಾರ್ಕಿಕ array_parameter_p = ಸುಳ್ಳು;

	/* A parameter declared as an array of T is really a pointer to T.
	   One declared as a function is really a pointer to a function.  */

	ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (type) == ARRAY_TYPE)
	  {
	    ಆದರೆ (!ಗಾತ್ರ_error)
	      *decl_attrs = build_arg_spec_attribute (type, array_parm_static,
						      *decl_attrs);

	    /* Transfer const-ness of array into that of type pointed to.  */
	    type = ವೃಕ್ಷ_TYPE (type);
	    ಆದರೆ (orig_qual_type != NULL_ವೃಕ್ಷ)
	      {
		ಆದರೆ (orig_qual_ಪರೋಕ್ಷ == 0)
		  orig_qual_type = ವೃಕ್ಷ_TYPE (orig_qual_type);
		ಇಲ್ಲದಿದ್ದರೆ
		  orig_qual_ಪರೋಕ್ಷ--;
	      }
	    ಆದರೆ (type_quals)
	      type = c_build_qualified_type (type, type_quals, orig_qual_type,
					     orig_qual_ಪರೋಕ್ಷ);

	    /* The pointed-to type may need a decl expr (see above).  */
	    ಆದರೆ (!TYPE_NAME (type) && c_type_variably_modified_p (type))
	      {
		ತಾರ್ಕಿಕ bind_p = decl_context == TYPENAME
			      || decl_context == ಕ್ಷೇತ್ರ
			      || decl_context == PARM;
		ಕೂಡಿಸು_decl_ಅಭಿವ್ಯಕ್ತಿ (loc, type, bind_p ? ಅಭಿವ್ಯಕ್ತಿ : ಖಾಲಿ, ನಿಜ);
	      }

	    type = c_build_ಸೂಚಕ_type (type);
	    type_quals = array_ptr_quals;
	    ಆದರೆ (type_quals)
	      type = c_build_qualified_type (type, type_quals);

	    /* We don't yet implement attributes in this context.  */
	    ಆದರೆ (array_ptr_attrs != NULL_ವೃಕ್ಷ)
	      warning_at (loc, OPT_Wattributes,
			  "attributes in parameter array declarator ignored");

	    ಗಾತ್ರ_varies = ಸುಳ್ಳು;
	    array_parameter_p = ನಿಜ;
	  }
	ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (type) == FUNCTION_TYPE)
	  {
	    ಆದರೆ (type_quals & TYPE_QUAL_ATOMIC)
	      {
		error_at (loc,
			  "%<_Atomic%>-qualified function type");
		type_quals &= ~TYPE_QUAL_ATOMIC;
	      }
	    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (type_quals)
	      pedwarn (loc, OPT_Wpedantic,
		       "ISO C forbids qualified function types");
	    ಆದರೆ (type_quals)
	      type = c_build_qualified_type (type, type_quals);
	    type = c_build_ಸೂಚಕ_type (type);
	    type_quals = TYPE_UNQUALIFIED;
	  }
	ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (type_quals)
	  type = c_build_qualified_type (type, type_quals);

	decl = build_decl (declarator->id_loc,
			   PARM_DECL, declarator->u.id.id, type);
	ಆದರೆ (ಗಾತ್ರ_varies)
	  C_DECL_VARIABLE_ಗಾತ್ರ (decl) = 1;
	C_ARRAY_PARAMETER (decl) = array_parameter_p;

	/* Compute the type actually passed in the parmlist,
	   for the case where there is no prototype.
	   (For example, shorts and chars are passed as ints.)
	   When there is a prototype, this is overridden later.  */

	ಆದರೆ (type == error_mark_ಗಂಟು)
	  promoted_type = type;
	ಇಲ್ಲದಿದ್ದರೆ
	  promoted_type = c_type_promotes_ಗಮ್ಯ (type);

	DECL_ARG_TYPE (decl) = promoted_type;
	ಆದರೆ (declspecs->inline_p)
	  pedwarn (loc, 0, "parameter %q+D declared %<inline%>", decl);
	ಆದರೆ (declspecs->noreturn_p)
	  pedwarn (loc, 0, "parameter %q+D declared %<_Noreturn%>", decl);
      }
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (decl_context == ಕ್ಷೇತ್ರ)
      {
	/* Note that the grammar rejects storage classes in typenames
	   and fields.  */
	gcc_assert (storage_class == csc_none && !threadp
		    && !declspecs->inline_p && !declspecs->noreturn_p);

	/* Structure field.  It may not be a function.  */

	ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (type) == FUNCTION_TYPE)
	  {
	    error_at (loc, "field %qE declared as a function", name);
	    type = c_build_ಸೂಚಕ_type (type);
	  }
	ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (type) != ERROR_MARK
		 && !COMPLETE_OR_UNBOUND_ARRAY_TYPE_P (type))
	  {
	    ಆದರೆ (name)
	      error_at (loc, "field %qE has incomplete type", name);
	    ಇಲ್ಲದಿದ್ದರೆ
	      error_at (loc, "unnamed field has incomplete type");
	    type = error_mark_ಗಂಟು;
	  }
	ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (type) == ARRAY_TYPE
		 && TYPE_DOMAIN (type) == NULL_ವೃಕ್ಷ)
	  {
	    /* We have a flexible array member through a typedef.
	       Set suitable range.  Whether this is a correct position
	       for a flexible array member will be determined elsewhere.  */
	    ಆದರೆ (!ಒಳ_system_ಶೀರ್ಷಿಕೆ_at (ಒಳಹರಿವು_location))
	      pedwarn_c90 (loc, OPT_Wpedantic, "ISO C90 does not "
			   "support flexible array members");
	    type = build_distinct_type_copy (TYPE_MAIN_VARIANT (type));
	    TYPE_DOMAIN (type) = build_ಸೂಚ್ಯಂಕ_type (NULL_ವೃಕ್ಷ);
	    ಆದರೆ (orig_qual_ಪರೋಕ್ಷ == 0)
	      orig_qual_type = NULL_ವೃಕ್ಷ;
	  }
	ಆದರೆ (type != error_mark_ಗಂಟು
	    && !verify_type_context (loc, TCTX_ಕ್ಷೇತ್ರ, type))
	  type = error_mark_ಗಂಟು;

	type = c_build_qualified_type (type, type_quals, orig_qual_type,
				       orig_qual_ಪರೋಕ್ಷ);
	decl = build_decl (declarator->id_loc,
			   ಕ್ಷೇತ್ರ_DECL, declarator->u.id.id, type);
	DECL_NONADDRESSABLE_P (decl) = bitfield;
	ಆದರೆ (bitfield && !declarator->u.id.id)
	  DECL_PADDING_P (decl) = 1;

	ಆದರೆ (ಗಾತ್ರ_varies)
	  C_DECL_VARIABLE_ಗಾತ್ರ (decl) = 1;
      }
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (type) == FUNCTION_TYPE)
      {
	ಆದರೆ (storage_class == csc_ರಿಜಿಸ್ಟರ್ || threadp || constexprp)
	  {
	    error_at (loc, "invalid storage class for function %qE", name);
	  }
	ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (current_scope != file_scope)
	  {
	    /* Function declaration not at file scope.  Storage
	       classes other than `extern' are not allowed, C99
	       6.7.1p5, and `extern' makes no difference.  However,
	       GCC allows 'auto', perhaps with 'inline', to support
	       nested functions.  */
	    ಆದರೆ (storage_class == csc_auto)
		pedwarn (loc, OPT_Wpedantic,
			 "invalid storage class for function %qE", name);
	    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (storage_class == csc_static)
	      {
		error_at (loc, "invalid storage class for function %qE", name);
		ಆದರೆ (funcdef_flag)
		  storage_class = declspecs->storage_class = csc_none;
		ಇಲ್ಲದಿದ್ದರೆ
		  ಹಿಂತಿರುಗಿ NULL_ವೃಕ್ಷ;
	      }
	  }

	decl = build_decl (declarator->id_loc,
			   FUNCTION_DECL, declarator->u.id.id, type);
	decl = build_decl_attribute_variant (decl, decl_attr);

	ಆದರೆ (type_quals & TYPE_QUAL_ATOMIC)
	  {
	    error_at (loc,
		      "%<_Atomic%>-qualified function type");
	    type_quals &= ~TYPE_QUAL_ATOMIC;
	  }
	ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (pedantic && type_quals && !DECL_ಒಳ_SYSTEM_ಶೀರ್ಷಿಕೆ (decl))
	  pedwarn (loc, OPT_Wpedantic,
		   "ISO C forbids qualified function types");

	/* Every function declaration is an external reference
	   (DECL_EXTERNAL) except for those which are not at file
	   scope and are explicitly declared "auto".  This is
	   forbidden by standard C (C99 6.7.1p5) and is interpreted by
	   GCC to signify a forward declaration of a nested function.  */
	ಆದರೆ (storage_class == csc_auto && current_scope != file_scope)
	  DECL_EXTERNAL (decl) = 0;
	/* In C99, a function which is declared 'inline' with 'extern'
	   is not an external reference (which is confusing).  It
	   means that the later definition of the function must be output
	   in this file, C99 6.7.4p6.  In GNU C89, a function declared
	   'extern inline' is an external reference.  */
	ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (declspecs->inline_p && storage_class != csc_static)
	  DECL_EXTERNAL (decl) = ((storage_class == csc_extern)
				  == flag_gnu89_inline);
	ಇಲ್ಲದಿದ್ದರೆ
	  DECL_EXTERNAL (decl) = !initialized;

	/* Record absence of global scope for `static' or `auto'.  */
	ವೃಕ್ಷ_ಬಹಿರಂಗ (decl)
	  = !(storage_class == csc_static || storage_class == csc_auto);

	/* For a function definition, record the argument information
	   block where store_parm_decls will look for it.  */
	ಆದರೆ (funcdef_flag)
	  current_function_arg_info = arg_info;

	ಆದರೆ (declspecs->default_int_p)
	  C_FUNCTION_IMPLICIT_INT (decl) = 1;

	/* Record presence of `inline' and `_Noreturn', if it is
	   reasonable.  */
	ಆದರೆ (flag_hosted && MAIN_NAME_P (declarator->u.id.id))
	  {
	    ಆದರೆ (declspecs->inline_p)
	      pedwarn (loc, 0, "cannot inline function %<main%>");
	    ಆದರೆ (declspecs->noreturn_p)
	      pedwarn (loc, 0, "%<main%> declared %<_Noreturn%>");
	  }
	ಇಲ್ಲದಿದ್ದರೆ
	  {
	    ಆದರೆ (declspecs->inline_p)
	      /* Record that the function is declared `inline'.  */
	      DECL_DECLARED_INLINE_P (decl) = 1;
	    ಆದರೆ (declspecs->noreturn_p)
	      {
		ಆದರೆ (flag_isoc99)
		  pedwarn_c99 (loc, OPT_Wpedantic,
			       "ISO C99 does not support %<_Noreturn%>");
		ಇಲ್ಲದಿದ್ದರೆ
		  pedwarn_c99 (loc, OPT_Wpedantic,
			       "ISO C90 does not support %<_Noreturn%>");
		ವೃಕ್ಷ_THIS_VOLATILE (decl) = 1;
	      }
	  }

	/* C99 6.2.2p7: It is invalid (compile-time undefined
	   behavior) to create an 'extern' declaration for a
	   function if there is a global declaration that is
	   'static' and the global declaration is not visible.
	   (If the static declaration _is_ currently visible,
	   the 'extern' declaration is taken to refer to that decl.) */
	ಆದರೆ (!initialized
	    && ವೃಕ್ಷ_ಬಹಿರಂಗ (decl)
	    && current_scope != file_scope)
	  {
	    ವೃಕ್ಷ global_decl  = identifier_global_ಮೌಲ್ಯ (declarator->u.id.id);
	    ವೃಕ್ಷ visible_decl = lookup_name (declarator->u.id.id);

	    ಆದರೆ (global_decl
		&& global_decl != visible_decl
		&& VAR_OR_FUNCTION_DECL_P (global_decl)
		&& !ವೃಕ್ಷ_ಬಹಿರಂಗ (global_decl))
	      error_at (loc, "function previously declared %<static%> "
			"redeclared %<extern%>");
	  }
      }
    ಇಲ್ಲದಿದ್ದರೆ
      {
	/* It's a variable.  */
	/* An uninitialized decl with `extern' is a reference.  */
	ಪೂರ್ಣಾಂಕ extern_ref = !initialized && storage_class == csc_extern;

	ಆದರೆ (constexprp)
	  {
	    /* The type of a constexpr variable must not be variably
	       modified, volatile, atomic or restrict qualified or
	       have a member with such a qualifier.  const
	       qualification is implicitly added, and, at file scope,
	       has internal linkage.  */
	    ಆದರೆ (c_type_variably_modified_p (type))
	      error_at (loc, "%<constexpr%> object has variably modified "
			"type");
	    ಆದರೆ (type_quals
		& (TYPE_QUAL_VOLATILE | TYPE_QUAL_RESTRICT | TYPE_QUAL_ATOMIC))
	      error_at (loc, "invalid qualifiers for %<constexpr%> object");
	    ಇಲ್ಲದಿದ್ದರೆ
	      {
		ವೃಕ್ಷ type_no_array = strip_array_types (type);
		ಆದರೆ (ದಾಖಲೆ_OR_UNION_TYPE_P (type_no_array)
		    && C_TYPE_FIELDS_NON_CONSTEXPR (type_no_array))
		  error_at (loc, "invalid qualifiers for field of "
			    "%<constexpr%> object");
	      }
	    type_quals |= TYPE_QUAL_CONST;
	    ಆದರೆ (current_scope == file_scope)
	      storage_class = csc_static;
	  }

	type = c_build_qualified_type (type, type_quals, orig_qual_type,
				       orig_qual_ಪರೋಕ್ಷ);

	/* C99 6.2.2p7: It is invalid (compile-time undefined
	   behavior) to create an 'extern' declaration for a
	   variable if there is a global declaration that is
	   'static' and the global declaration is not visible.
	   (If the static declaration _is_ currently visible,
	   the 'extern' declaration is taken to refer to that decl.) */
	ಆದರೆ (extern_ref && current_scope != file_scope)
	  {
	    ವೃಕ್ಷ global_decl  = identifier_global_ಮೌಲ್ಯ (declarator->u.id.id);
	    ವೃಕ್ಷ visible_decl = lookup_name (declarator->u.id.id);

	    ಆದರೆ (global_decl
		&& global_decl != visible_decl
		&& VAR_P (global_decl)
		&& !ವೃಕ್ಷ_ಬಹಿರಂಗ (global_decl))
	      error_at (loc, "variable previously declared %<static%> "
			"redeclared %<extern%>");
	  }

	decl = build_decl (declarator->id_loc,
			   VAR_DECL, declarator->u.id.id, type);
	ಆದರೆ (ಗಾತ್ರ_varies)
	  C_DECL_VARIABLE_ಗಾತ್ರ (decl) = 1;
	ಆದರೆ (constexprp)
	  C_DECL_DECLARED_CONSTEXPR (decl) = 1;

	ಆದರೆ (declspecs->inline_p)
	  pedwarn (loc, 0, "variable %q+D declared %<inline%>", decl);
	ಆದರೆ (declspecs->noreturn_p)
	  pedwarn (loc, 0, "variable %q+D declared %<_Noreturn%>", decl);

	/* At file scope, an initialized extern declaration may follow
	   a static declaration.  In that case, DECL_EXTERNAL will be
	   reset later in start_decl.  */
	DECL_EXTERNAL (decl) = (storage_class == csc_extern);

	/* At file scope, the presence of a `static' or `register' storage
	   class specifier, or the absence of all storage class specifiers
	   makes this declaration a definition (perhaps tentative).  Also,
	   the absence of `static' makes it public.  */
	ಆದರೆ (current_scope == file_scope)
	  {
	    ವೃಕ್ಷ_ಬಹಿರಂಗ (decl) = storage_class != csc_static;
	    ವೃಕ್ಷ_STATIC (decl) = !extern_ref;
	  }
	/* Not at file scope, only `static' makes a static definition.  */
	ಇಲ್ಲದಿದ್ದರೆ
	  {
	    ವೃಕ್ಷ_STATIC (decl) = (storage_class == csc_static);
	    ವೃಕ್ಷ_ಬಹಿರಂಗ (decl) = extern_ref;
	  }

	// NB: Set a tentative TLS model to avoid tls_model attribute
	// warnings due to lack of thread storage duration.  It will
	// be updated by c_decl_attributes later.
	ಆದರೆ (threadp)
	  ಗಣ_decl_tls_model (decl, TLS_MODEL_REAL);
      }

    ಆದರೆ ((storage_class == csc_extern
	 || (storage_class == csc_none
	     && ವೃಕ್ಷ_ಸಂಕೇತ (type) == FUNCTION_TYPE
	     && !funcdef_flag))
	&& c_type_variably_modified_p (type))
      {
	/* C99 6.7.5.2p2 */
	ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (type) == FUNCTION_TYPE)
	  error_at (loc, "non-nested function with variably modified type");
	ಇಲ್ಲದಿದ್ದರೆ
	  error_at (loc, "object with variably modified type must have "
	      	    "no linkage");
      }

    /* For nested functions disqualify ones taking VLAs by value
       from inlining since the middle-end cannot deal with this.
       ???  We should arrange for those to be passed by reference
       with emitting the copy on the caller side in the frontend.  */
    ಆದರೆ (storage_class == csc_none
	&& ವೃಕ್ಷ_ಸಂಕೇತ (type) == FUNCTION_TYPE)
      ಗಾಗಿ (ವೃಕ್ಷ al = TYPE_ARG_TYPES (type); al; al = ವೃಕ್ಷ_CHAIN (al))
	{
	  ವೃಕ್ಷ arg = ವೃಕ್ಷ_ಮೌಲ್ಯ (al);
	  ಆದರೆ (arg != error_mark_ಗಂಟು
	      && C_TYPE_VARIABLE_ಗಾತ್ರ (arg))
	    {
	      DECL_UNINLINABLE (decl) = 1;
	      ನಿಲ್ಲಿಸು;
	    }
	}

    /* Record `register' declaration for warnings on &
       and in case doing stupid register allocation.  */

    ಆದರೆ (storage_class == csc_ರಿಜಿಸ್ಟರ್
	&& ವೃಕ್ಷ_ಸಂಕೇತ (type) != FUNCTION_TYPE)
      {
	C_DECL_ರಿಜಿಸ್ಟರ್ (decl) = 1;
	DECL_ರಿಜಿಸ್ಟರ್ (decl) = 1;
      }

    /* Record constancy and volatility.  */
    c_apply_type_quals_ಗಮ್ಯ_decl (type_quals, decl);

    /* Apply _Alignas specifiers.  */
    ಆದರೆ (alignas_align)
      {
	ಗಣ_DECL_ALIGN (decl, alignas_align * ಬಿಟ್ಟುಗಳು_ಪ್ರತಿ_UNIT);
	DECL_USER_ALIGN (decl) = 1;
      }

    /* If a type has volatile components, it should be stored in memory.
       Otherwise, the fact that those components are volatile
       will be ignored, and would even crash the compiler.
       Of course, this only makes sense on  VAR,PARM, and RESULT decl's.   */
    ಆದರೆ (C_TYPE_FIELDS_VOLATILE (ವೃಕ್ಷ_TYPE (decl))
	&& (VAR_P (decl) ||  ವೃಕ್ಷ_ಸಂಕೇತ (decl) == PARM_DECL
	  || ವೃಕ್ಷ_ಸಂಕೇತ (decl) == ಫಲಿತಾಂಶ_DECL))
      {
	/* It is not an error for a structure with volatile fields to
	   be declared register, but reset DECL_REGISTER since it
	   cannot actually go in a register.  */
	ಪೂರ್ಣಾಂಕ was_reg = C_DECL_ರಿಜಿಸ್ಟರ್ (decl);
	C_DECL_ರಿಜಿಸ್ಟರ್ (decl) = 0;
	DECL_ರಿಜಿಸ್ಟರ್ (decl) = 0;
	c_mark_addressable (decl);
	C_DECL_ರಿಜಿಸ್ಟರ್ (decl) = was_reg;
      }

  /* This is the earliest point at which we might know the assembler
     name of a variable.  Thus, if it's known before this, die horribly.  */
    gcc_assert (!HAS_DECL_ASSEMBLER_NAME_P (decl)
		|| !DECL_ASSEMBLER_NAME_ಗಣ_P (decl));

    ಆದರೆ (warn_cxx_compat
	&& VAR_P (decl)
	&& ವೃಕ್ಷ_ಬಹಿರಂಗ (decl)
	&& ವೃಕ್ಷ_STATIC (decl)
	&& (ದಾಖಲೆ_OR_UNION_TYPE_P (ವೃಕ್ಷ_TYPE (decl))
	    || ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (decl)) == ENUMERAL_TYPE)
	&& TYPE_NAME (ವೃಕ್ಷ_TYPE (decl)) == NULL_ವೃಕ್ಷ)
      warning_at (DECL_ಮೂಲ_LOCATION (decl), OPT_Wc___compat,
		  "non-local variable %qD with anonymous type is "
		  "questionable in C++", decl);

    ಹಿಂತಿರುಗಿ decl;
  }
}

/* Decode the parameter-list info for a function type or function definition.
   The argument is the value returned by `get_parm_info' (or made in c-parse.c
   if there is an identifier list instead of a parameter decl list).
   These two functions are separate because when a function returns
   or receives functions then each is called multiple times but the order
   of calls is different.  The last call to `grokparms' is always the one
   that contains the formal parameter names of a function definition.

   Return a list of arg types to use in the FUNCTION_TYPE for this function.

   FUNCDEF_FLAG is true for a function definition, false for
   a mere declaration.  A nonempty identifier-list gets an error message
   when FUNCDEF_FLAG is false.  */

ಸ್ಥಿರ ವೃಕ್ಷ
grokparms (ರಚನೆ c_arg_info *arg_info, ತಾರ್ಕಿಕ funcdef_flag)
{
  ವೃಕ್ಷ arg_types = arg_info->types;

  ಆದರೆ (funcdef_flag && arg_info->had_vla_unspec)
    {
      /* A function definition isn't function prototype scope C99 6.2.1p4.  */
      /* C99 6.7.5.2p4 */
      error ("%<[*]%> not allowed in other than function prototype scope");
    }

  ಆದರೆ (arg_types == NULL_ವೃಕ್ಷ && !funcdef_flag && !flag_isoc23
      && !ಒಳ_system_ಶೀರ್ಷಿಕೆ_at (ಒಳಹರಿವು_location))
    warning (OPT_Wstrict_prototypes,
	     "function declaration isn%'t a prototype");

  ಆದರೆ (arg_types == error_mark_ಗಂಟು)
    /* Don't set TYPE_ARG_TYPES in this case.  */
    ಹಿಂತಿರುಗಿ NULL_ವೃಕ್ಷ;

  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (arg_types && ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_ಮೌಲ್ಯ (arg_types)) == IDENTIFIER_ಗಂಟು)
    {
      ಆದರೆ (!funcdef_flag)
	{
	  permerror_opt (ಒಳಹರಿವು_location,
			 OPT_Wdeclaration_missing_parameter_type,
			 "parameter names (without types) in "
			 "function declaration");
	  arg_info->parms = NULL_ವೃಕ್ಷ;
	}
      ಇಲ್ಲದಿದ್ದರೆ
	arg_info->parms = arg_info->types;

      arg_info->types = NULL_ವೃಕ್ಷ;
      ಹಿಂತಿರುಗಿ NULL_ವೃಕ್ಷ;
    }
  ಇಲ್ಲದಿದ್ದರೆ
    {
      ವೃಕ್ಷ parm, type, typelt;
      ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ parmno;

      /* In C23, convert () to (void).  */
      ಆದರೆ (flag_isoc23
	  && !arg_types
	  && !arg_info->parms
	  && !arg_info->no_named_ವಾದಗಳು_stdarg_p)
	{
	  arg_types = arg_info->types = void_list_ಗಂಟು;
	  arg_info->c23_ಖಾಲಿಗಳು_parens = 1;
	}

      /* If there is a parameter of incomplete type in a definition,
	 this is an error.  In a declaration this is valid, and a
	 struct or union type may be completed later, before any calls
	 or definition of the function.  In the case where the tag was
	 first declared within the parameter list, a warning has
	 already been given.  If a parameter has void type, then
	 this has already received an error (constraint violation in C2Y,
	 previously implicitly undefined behavior).  */

      ಗಾಗಿ (parm = arg_info->parms, typelt = arg_types, parmno = 1;
	   parm;
	   parm = DECL_CHAIN (parm), typelt = ವೃಕ್ಷ_CHAIN (typelt), parmno++)
	{
	  type = ವೃಕ್ಷ_ಮೌಲ್ಯ (typelt);
	  ಆದರೆ (type == error_mark_ಗಂಟು)
	    ಮುಂದುವರಿ;

	  ಆದರೆ (!COMPLETE_TYPE_P (type))
	    {
	      ಆದರೆ (funcdef_flag)
		{
		  ಆದರೆ (DECL_NAME (parm))
		    error_at (ಒಳಹರಿವು_location,
			      "parameter %u (%q+D) has incomplete type",
			      parmno, parm);
		  ಇಲ್ಲದಿದ್ದರೆ
		    error_at (DECL_ಮೂಲ_LOCATION (parm),
			      "parameter %u has incomplete type",
			      parmno);

		  ವೃಕ್ಷ_ಮೌಲ್ಯ (typelt) = error_mark_ಗಂಟು;
		  ವೃಕ್ಷ_TYPE (parm) = error_mark_ಗಂಟು;
		  arg_types = NULL_ವೃಕ್ಷ;
		}
	    }

	  ಆದರೆ (DECL_NAME (parm) && ವೃಕ್ಷ_ಬಳಸಿದ (parm))
	    warn_if_shadowing (parm);
	}
      ಹಿಂತಿರುಗಿ arg_types;
    }
}

/* Allocate and initialize a c_arg_info structure from the parser's
   obstack.  */

ರಚನೆ c_arg_info *
build_arg_info (ಶೂನ್ಯ)
{
  ರಚನೆ c_arg_info *ret = XOBNEW (&parser_obstack, ರಚನೆ c_arg_info);
  ret->parms = NULL_ವೃಕ್ಷ;
  ret->ಟ್ಯಾಗುಗಳು = ಖಾಲಿ;
  ret->types = NULL_ವೃಕ್ಷ;
  ret->others = NULL_ವೃಕ್ಷ;
  ret->pending_sizes = ಖಾಲಿ;
  ret->had_vla_unspec = 0;
  ret->no_named_ವಾದಗಳು_stdarg_p = 0;
  ret->c23_ಖಾಲಿಗಳು_parens = 0;
  ಹಿಂತಿರುಗಿ ret;
}

/* Take apart the current scope and return a c_arg_info structure with
   info on a parameter list just parsed.

   This structure is later fed to 'grokparms' and 'store_parm_decls'.

   ELLIPSIS being true means the argument list ended in '...' so don't
   append a sentinel (void_list_node) to the end of the type-list.

   EXPR is NULL or an expression that needs to be evaluated for the
   side effects of array size expressions in the parameters.  */

ರಚನೆ c_arg_info *
get_parm_info (ತಾರ್ಕಿಕ ellipsis, ವೃಕ್ಷ ಅಭಿವ್ಯಕ್ತಿ)
{
  ರಚನೆ c_binding *b = current_scope->bindings;
  ರಚನೆ c_arg_info *arg_info = build_arg_info ();

  ವೃಕ್ಷ parms = NULL_ವೃಕ್ಷ;
  vec<c_arg_ಟ್ಯಾಗ್, va_gc> *ಟ್ಯಾಗುಗಳು = ಖಾಲಿ;
  ವೃಕ್ಷ types = NULL_ವೃಕ್ಷ;
  ವೃಕ್ಷ others = NULL_ವೃಕ್ಷ;

  ತಾರ್ಕಿಕ gave_void_only_once_err = ಸುಳ್ಳು;

  arg_info->had_vla_unspec = current_scope->had_vla_unspec;

  /* The bindings in this scope must not get put into a block.
     We will take care of deleting the binding nodes.  */
  current_scope->bindings = 0;

  /* This function is only called if there was *something* on the
     parameter list.  */
  gcc_assert (b);

  /* A parameter list consisting solely of 'void' indicates that the
     function takes no arguments.  But if the 'void' is qualified
     (by 'const' or 'volatile'), or has a storage class specifier
     ('register'), then the behavior is undefined; issue an error.
     Typedefs for 'void' are OK (see DR#157).  */
  ಆದರೆ (b->prev == 0			    /* one binding */
      && ವೃಕ್ಷ_ಸಂಕೇತ (b->decl) == PARM_DECL   /* which is a parameter */
      && !DECL_NAME (b->decl)               /* anonymous */
      && VOID_TYPE_P (ವೃಕ್ಷ_TYPE (b->decl))) /* of void type */
    {
      ಆದರೆ (TYPE_QUALS (ವೃಕ್ಷ_TYPE (b->decl)) != TYPE_UNQUALIFIED
	  || C_DECL_ರಿಜಿಸ್ಟರ್ (b->decl))
	error_at (b->locus, "%<void%> as only parameter may not be qualified");

      /* There cannot be an ellipsis.  */
      ಆದರೆ (ellipsis)
	error_at (b->locus, "%<void%> must be the only parameter");

      arg_info->types = void_list_ಗಂಟು;
      ಹಿಂತಿರುಗಿ arg_info;
    }

  ಆದರೆ (!ellipsis)
    types = void_list_ಗಂಟು;

  /* Break up the bindings list into parms, tags, types, and others;
     apply sanity checks; purge the name-to-decl bindings.  */
  ಆಗ (b)
    {
      ವೃಕ್ಷ decl = b->decl;
      ವೃಕ್ಷ type = ವೃಕ್ಷ_TYPE (decl);
      c_arg_ಟ್ಯಾಗ್ ಟ್ಯಾಗ್;
      ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *keyword;

      ಆಯ್ಕೆ (ವೃಕ್ಷ_ಸಂಕೇತ (decl))
	{
	ಸ್ಥಿತಿ PARM_DECL:
	  ಆದರೆ (b->id)
	    {
	      gcc_assert (I_ಚಿಹ್ನೆ_BINDING (b->id) == b);
	      I_ಚಿಹ್ನೆ_BINDING (b->id) = b->shadowed;
	    }

	  /* Check for forward decls that never got their actual decl.  */
	  ಆದರೆ (ವೃಕ್ಷ_ASM_WRITTEN (decl))
	    error_at (b->locus,
		      "parameter %q+D has just a forward declaration", decl);
	  /* Check for (..., void, ...) and named void parameters and issue an
	     error.  */
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (VOID_TYPE_P (type))
	    {
	      ಆದರೆ (!gave_void_only_once_err)
		{
		  error_at (b->locus,
			    "%<void%> must be the only parameter and unnamed");
		  gave_void_only_once_err = ನಿಜ;
		}
	    }
	  ಇಲ್ಲದಿದ್ದರೆ
	    {
	      /* Valid parameter, add it to the list.  */
	      DECL_CHAIN (decl) = parms;
	      parms = decl;

	      /* Since there is a prototype, args are passed in their
		 declared types.  The back end may override this later.  */
	      DECL_ARG_TYPE (decl) = type;
	      types = ವೃಕ್ಷ_cons (0, type, types);
	    }
	  ನಿಲ್ಲಿಸು;

	ಸ್ಥಿತಿ ENUMERAL_TYPE: keyword = "enum"; ಹೋಗು ಟ್ಯಾಗ್;
	ಸ್ಥಿತಿ UNION_TYPE:    keyword = "union"; ಹೋಗು ಟ್ಯಾಗ್;
	ಸ್ಥಿತಿ ದಾಖಲೆ_TYPE:   keyword = "struct"; ಹೋಗು ಟ್ಯಾಗ್;
	ಟ್ಯಾಗ್:
	  /* Types may not have tag-names, in which case the type
	     appears in the bindings list with b->id NULL.  */
	  ಆದರೆ (b->id)
	    {
	      gcc_assert (I_ಟ್ಯಾಗ್_BINDING (b->id) == b);
	      I_ಟ್ಯಾಗ್_BINDING (b->id) = b->shadowed;
	    }

	  /* Warn about any struct, union or enum tags defined in a
	     parameter list.  The scope of such types is limited to
	     the parameter list, which is rarely if ever desirable
	     (it's impossible to call such a function with type-
	     correct arguments).  An anonymous union parm type is
	     meaningful as a GNU extension, so don't warn for that.  */
	  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (decl) != UNION_TYPE || b->id != NULL_ವೃಕ್ಷ)
	    {
	      ಆದರೆ (b->id)
		{
		  /* The %s will be one of 'struct', 'union', or 'enum'.  */
		  ಆದರೆ (!flag_isoc23 || !COMPLETE_TYPE_P (decl))
		    warning_at (b->locus, 0,
				"%<%s %E%> declared inside parameter list"
				" will not be visible outside of this definition or"
				" declaration", keyword, b->id);
		}
	      ಇಲ್ಲದಿದ್ದರೆ
		/* The %s will be one of 'struct', 'union', or 'enum'.  */
		warning_at (b->locus, 0,
			    "anonymous %s declared inside parameter list"
			    " will not be visible outside of this definition or"
			    " declaration", keyword);
	    }

	  ಟ್ಯಾಗ್.id = b->id;
	  ಟ್ಯಾಗ್.type = decl;
	  vec_ಸುರಕ್ಷಿತ_ತಳ್ಳು (ಟ್ಯಾಗುಗಳು, ಟ್ಯಾಗ್);
	  ನಿಲ್ಲಿಸು;

	ಸ್ಥಿತಿ FUNCTION_DECL:
	  /* FUNCTION_DECLs appear when there is an implicit function
	     declaration in the parameter list.  */
	  gcc_assert (b->nested || ನೋಡಿದ_error ());
	  ಹೋಗು ಗಣ_shadowed;

	ಸ್ಥಿತಿ CONST_DECL:
	ಸ್ಥಿತಿ TYPE_DECL:
	  /* CONST_DECLs appear here when we have an embedded enum,
	     and TYPE_DECLs appear here when we have an embedded struct
	     or union.  No warnings for this - we already warned about the
	     type itself.  */

	  /* When we reinsert this decl in the function body, we need
	     to reconstruct whether it was marked as nested.  */
	  gcc_assert (!b->nested);
	  DECL_CHAIN (decl) = others;
	  others = decl;
	  /* fall through */

	ಸ್ಥಿತಿ ERROR_MARK:
	ಗಣ_shadowed:
	  /* error_mark_node appears here when we have an undeclared
	     variable.  Just throw it away.  */
	  ಆದರೆ (b->id)
	    {
	      gcc_assert (I_ಚಿಹ್ನೆ_BINDING (b->id) == b);
	      I_ಚಿಹ್ನೆ_BINDING (b->id) = b->shadowed;
	    }
	  ನಿಲ್ಲಿಸು;

	  /* Other things that might be encountered.  */
	ಸ್ಥಿತಿ LABEL_DECL:
	ಸ್ಥಿತಿ VAR_DECL:
	ಪೂರ್ವನಿಯೋಜಿತ:
	  gcc_unreachable ();
	}

      b = free_binding_and_advance (b);
    }

  arg_info->parms = parms;
  arg_info->ಟ್ಯಾಗುಗಳು = ಟ್ಯಾಗುಗಳು;
  arg_info->types = types;
  arg_info->others = others;
  arg_info->pending_sizes = ಅಭಿವ್ಯಕ್ತಿ;
  arg_info->no_named_ವಾದಗಳು_stdarg_p = ellipsis && !types;
  ಹಿಂತಿರುಗಿ arg_info;
}

/* Get the struct, enum or union (CODE says which) with tag NAME.
   Define the tag as a forward-reference with location LOC if it is
   not defined.  HAVE_STD_ATTRS says whether any standard attributes
   were present after the struct, union or enum keyword; ATTRS are the
   standard attributes present there.  HAS_ENUM_TYPE_SPECIFIER says
   whether an enum type specifier (": specifier-qualifier-list") is
   present; if so, this is called before that specifier is parsed, so
   that the tag is in scope for that specifier.  Return a c_typespec
   structure for the type specifier.  */

ರಚನೆ c_typespec
parser_xref_ಟ್ಯಾಗ್ (location_t loc, ಎಣಿಕೆ ವೃಕ್ಷ_ಸಂಕೇತ_2 ಸಂಕೇತ_2, ವೃಕ್ಷ name,
		 ತಾರ್ಕಿಕ have_std_attrs, ವೃಕ್ಷ attrs, ತಾರ್ಕಿಕ has_enum_type_specifier)
{
  ರಚನೆ c_typespec ret;
  ವೃಕ್ಷ ref;
  location_t refloc;

  ret.ಅಭಿವ್ಯಕ್ತಿ = NULL_ವೃಕ್ಷ;
  ret.ಅಭಿವ್ಯಕ್ತಿ_const_operands = ನಿಜ;
  ret.has_enum_type_specifier = has_enum_type_specifier;

  /* If a cross reference is requested, look up the type already
     defined for this tag and return it.  If an enum type specifier is
     present, only a definition in the current scope is relevant.  */

  ref = lookup_ಟ್ಯಾಗ್ (ಸಂಕೇತ_2, name, has_enum_type_specifier, &refloc);

  /* If the visible type is still being defined, see if there is
     an earlier definition (which may be complete).  We do not
     have to loop because nested redefinitions are not allowed.  */
  ಆದರೆ (flag_isoc23 && ref && C_TYPE_BEING_DEFINED (ref))
    {
      ವೃಕ್ಷ vis = ಹಿಂದಿನ_ಟ್ಯಾಗ್ (ref);
      ಆದರೆ (vis)
	ref = vis;
    }

  /* If this is the right type of tag, return what we found.
     (This reference will be shadowed by shadow_tag later if appropriate.)
     If this is the wrong type of tag, do not return it.  If it was the
     wrong type in the same scope, we will have had an error
     message already; if in a different scope and declaring
     a name, pending_xref_error will give an error message; but if in a
     different scope and not declaring a name, this tag should
     shadow the previous declaration of a different type of tag, and
     this would not work properly if we return the reference found.
     (For example, with "struct foo" in an outer scope, "union foo;"
     must shadow that tag with a new one of union type.)  */
  ret.ಬಗೆ = (ref
	      ? (have_std_attrs ? ctsk_tagref_attrs : ctsk_tagref)
	      : (have_std_attrs ? ctsk_tagfirstref_attrs : ctsk_tagfirstref));
  ಆದರೆ (ref && ವೃಕ್ಷ_ಸಂಕೇತ (ref) == ಸಂಕೇತ_2)
    {
      decl_ಗುಣಲಕ್ಷಣಗಳು (&ref, attrs, (ಪೂರ್ಣಾಂಕ) ATTR_FLAG_TYPE_ಒಳ_ಇರಿಸು);
      ಆದರೆ (C_TYPE_DEFINED_ಒಳ_STRUCT (ref)
	  && loc != UNKNOWN_LOCATION
	  && warn_cxx_compat)
	{
	  auto_diagnostic_ಗುಂಪು d;
	  ಆಯ್ಕೆ (ಸಂಕೇತ_2)
	    {
	    ಸ್ಥಿತಿ ENUMERAL_TYPE:
	      ಆದರೆ (warning_at (loc, OPT_Wc___compat,
			      ("enum type defined in struct or union "
			       "is not visible in C++")))
		  inform (refloc, "enum type defined here");
	      ನಿಲ್ಲಿಸು;
	    ಸ್ಥಿತಿ ದಾಖಲೆ_TYPE:
	      ಆದರೆ (warning_at (loc, OPT_Wc___compat,
			      ("struct defined in struct or union "
			       "is not visible in C++")))
		inform (refloc, "struct defined here");
	      ನಿಲ್ಲಿಸು;
	    ಸ್ಥಿತಿ UNION_TYPE:
	      ಆದರೆ (warning_at (loc, OPT_Wc___compat,
			      ("union defined in struct or union "
			       "is not visible in C++")))
		inform (refloc, "union defined here");
	      ನಿಲ್ಲಿಸು;
	    ಪೂರ್ವನಿಯೋಜಿತ:
	      gcc_unreachable();
	    }
	}

      ret.spec = ref;
      ಹಿಂತಿರುಗಿ ret;
    }

  /* If no such tag is yet defined, create a forward-reference node
     and record it as the "definition".
     When a real declaration of this type is found,
     the forward-reference will be altered into a real type.  */

  ref = make_ಗಂಟು (ಸಂಕೇತ_2);
  ಆದರೆ (flag_isoc23 || ಸಂಕೇತ_2 == ENUMERAL_TYPE)
    ಗಣ_TYPE_STRUCTURAL_EQUALITY (ref);
  ಆದರೆ (ಸಂಕೇತ_2 == ENUMERAL_TYPE)
    {
      /* Give the type a default layout like unsigned int
	 to avoid crashing if it does not get defined.  */
      ಗಣ_TYPE_ಬಹುಲಕ (ref, TYPE_ಬಹುಲಕ (unsigned_type_ಗಂಟು));
      ಗಣ_TYPE_ALIGN (ref, TYPE_ALIGN (unsigned_type_ಗಂಟು));
      TYPE_USER_ALIGN (ref) = 0;
      TYPE_UNSIGNED (ref) = 1;
      TYPE_PRECISION (ref) = TYPE_PRECISION (unsigned_type_ಗಂಟು);
      TYPE_MIN_ಮೌಲ್ಯ (ref) = TYPE_MIN_ಮೌಲ್ಯ (unsigned_type_ಗಂಟು);
      TYPE_MAX_ಮೌಲ್ಯ (ref) = TYPE_MAX_ಮೌಲ್ಯ (unsigned_type_ಗಂಟು);
      ENUM_FIXED_UNDERLYING_TYPE_P (ref) = has_enum_type_specifier;
    }

  pushtag (loc, name, ref);
  decl_ಗುಣಲಕ್ಷಣಗಳು (&ref, attrs, (ಪೂರ್ಣಾಂಕ) ATTR_FLAG_TYPE_ಒಳ_ಇರಿಸು);
  ಆದರೆ (ಒಳ_underspecified_init)
    error_at (loc, "%qT declared in underspecified object initializer",
	      ref);

  ret.spec = ref;
  ಹಿಂತಿರುಗಿ ret;
}

/* Get the struct, enum or union (CODE says which) with tag NAME.
   Define the tag as a forward-reference if it is not defined.
   Return a tree for the type.  */

ವೃಕ್ಷ
xref_ಟ್ಯಾಗ್ (ಎಣಿಕೆ ವೃಕ್ಷ_ಸಂಕೇತ_2 ಸಂಕೇತ_2, ವೃಕ್ಷ name)
{
  ಹಿಂತಿರುಗಿ parser_xref_ಟ್ಯಾಗ್ (ಒಳಹರಿವು_location, ಸಂಕೇತ_2, name, ಸುಳ್ಳು, NULL_ವೃಕ್ಷ,
			  ಸುಳ್ಳು).spec;
}

/* Make sure that the tag NAME is defined *in the current scope*
   at least as a forward reference.
   LOC is the location of the struct's definition.
   CODE says which kind of tag NAME ought to be.

   This stores the current value of the file static STRUCT_PARSE_INFO
   in *ENCLOSING_STRUCT_PARSE_INFO, and points STRUCT_PARSE_INFO at a
   new c_struct_parse_info structure.  The old value of
   STRUCT_PARSE_INFO is restored in finish_struct.  */

ವೃಕ್ಷ
ಆರಂಭ_struct (location_t loc, ಎಣಿಕೆ ವೃಕ್ಷ_ಸಂಕೇತ_2 ಸಂಕೇತ_2, ವೃಕ್ಷ name,
	      ವರ್ಗ c_struct_parse_info **enclosing_struct_parse_info)
{
  /* If there is already a tag defined at this scope
     (as a forward reference), just return it.  */

  ವೃಕ್ಷ ref = NULL_ವೃಕ್ಷ;
  location_t refloc = UNKNOWN_LOCATION;

  ಆದರೆ (name != NULL_ವೃಕ್ಷ)
    ref = lookup_ಟ್ಯಾಗ್ (ಸಂಕೇತ_2, name, ನಿಜ, &refloc);

  /* For C23, even if we already have a completed definition,
     we do not use it. We will check for consistency later.
     If we are in a nested redefinition the type is not
     complete. We will then detect this below.  */
  ಆದರೆ (flag_isoc23 && ref && TYPE_ಗಾತ್ರ (ref))
    ref = NULL_ವೃಕ್ಷ;

  ಆದರೆ (ref && ವೃಕ್ಷ_ಸಂಕೇತ (ref) == ಸಂಕೇತ_2)
    {
      ಆದರೆ (TYPE_STUB_DECL (ref))
	refloc = DECL_ಮೂಲ_LOCATION (TYPE_STUB_DECL (ref));

      ಆದರೆ (TYPE_ಗಾತ್ರ (ref))
	{
	  auto_diagnostic_ಗುಂಪು d;
	  ಆದರೆ (ಸಂಕೇತ_2 == UNION_TYPE)
	    error_at (loc, "redefinition of %<union %E%>", name);
	  ಇಲ್ಲದಿದ್ದರೆ
	    error_at (loc, "redefinition of %<struct %E%>", name);
	  ಆದರೆ (refloc != UNKNOWN_LOCATION)
	    inform (refloc, "originally defined here");
	  /* Don't create structures using a name already in use.  */
	  ref = NULL_ವೃಕ್ಷ;
	}
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (C_TYPE_BEING_DEFINED (ref))
	{
	  ಆದರೆ (ಸಂಕೇತ_2 == UNION_TYPE)
	    error_at (loc, "nested redefinition of %<union %E%>", name);
	  ಇಲ್ಲದಿದ್ದರೆ
	    error_at (loc, "nested redefinition of %<struct %E%>", name);
	  /* Don't bother to report "originally defined here" for a
	     nested redefinition; the original definition should be
	     obvious.  */
	  /* Don't create structures that contain themselves.  */
	  ref = NULL_ವೃಕ್ಷ;
	}
    }

  /* Otherwise create a forward-reference just so the tag is in scope.  */

  ಆದರೆ (ref == NULL_ವೃಕ್ಷ || ವೃಕ್ಷ_ಸಂಕೇತ (ref) != ಸಂಕೇತ_2)
    {
      ref = make_ಗಂಟು (ಸಂಕೇತ_2);
      ಆದರೆ (flag_isoc23)
	ಗಣ_TYPE_STRUCTURAL_EQUALITY (ref);
      pushtag (loc, name, ref);
    }

  C_TYPE_BEING_DEFINED (ref) = 1;
  ಗಾಗಿ (ವೃಕ್ಷ v = TYPE_MAIN_VARIANT (ref); v; v = TYPE_ಮುಂದಿನ_VARIANT (v))
    TYPE_PACKED (v) = flag_pack_struct;

  *enclosing_struct_parse_info = struct_parse_info;
  struct_parse_info = ಹೊಸ c_struct_parse_info ();
  struct_parse_info->refloc = refloc;

  /* FIXME: This will issue a warning for a use of a type defined
     within a statement expr used within sizeof, et. al.  This is not
     terribly serious as C++ doesn't permit statement exprs within
     sizeof anyhow.  */
  ಆದರೆ (warn_cxx_compat
      && (ಒಳ_sizeof || ಒಳ_typeof || ಒಳ_alignof || ಒಳ_countof))
    warning_at (loc, OPT_Wc___compat,
		"defining type in %qs expression is invalid in C++",
		(ಒಳ_sizeof ? "sizeof"
		 : ಒಳ_typeof ? "typeof"
		 : ಒಳ_alignof ? "alignof"
		 : "_Countof"));

  ಆದರೆ (ಒಳ_underspecified_init)
    error_at (loc, "%qT defined in underspecified object initializer", ref);

  ಹಿಂತಿರುಗಿ ref;
}

/* Process the specs, declarator and width (NULL if omitted)
   of a structure component, returning a FIELD_DECL node.
   WIDTH is non-NULL for bit-fields only, and is an INTEGER_CST node.
   DECL_ATTRS is as for grokdeclarator.

   LOC is the location of the structure component.

   This is done during the parsing of the struct declaration.
   The FIELD_DECL nodes are chained together and the lot of them
   are ultimately passed to `build_struct' to make the RECORD_TYPE node.  */

ವೃಕ್ಷ
grokfield (location_t loc,
	   ರಚನೆ c_declarator *declarator, ರಚನೆ c_declspecs *declspecs,
	   ವೃಕ್ಷ ಅಗಲ, ವೃಕ್ಷ *decl_attrs, ವೃಕ್ಷ *ಅಭಿವ್ಯಕ್ತಿ)
{
  ವೃಕ್ಷ ಮೌಲ್ಯ;

  ಆದರೆ (declarator->ಬಗೆ == cdk_id && declarator->u.id.id == NULL_ವೃಕ್ಷ
      && ಅಗಲ == NULL_ವೃಕ್ಷ)
    {
      /* This is an unnamed decl.

	 If we have something of the form "union { list } ;" then this
	 is the anonymous union extension.  Similarly for struct.

	 If this is something of the form "struct foo;", then
	   If MS or Plan 9 extensions are enabled, this is handled as
	     an anonymous struct.
	   Otherwise this is a forward declaration of a structure tag.

	 If this is something of the form "foo;" and foo is a TYPE_DECL, then
	   If foo names a structure or union without a tag, then this
	     is an anonymous struct (this is permitted by C11).
	   If MS or Plan 9 extensions are enabled and foo names a
	     structure, then again this is an anonymous struct.
	   Otherwise this is an error.

	 Oh what a horrid tangled web we weave.  I wonder if MS consciously
	 took this from Plan 9 or if it was an accident of implementation
	 that took root before someone noticed the bug...  */

      ವೃಕ್ಷ type = declspecs->type;
      ತಾರ್ಕಿಕ ok = ಸುಳ್ಳು;

      ಆದರೆ (ದಾಖಲೆ_OR_UNION_TYPE_P (type)
	  && (flag_ms_extensions
	      || flag_plan9_extensions
	      || !declspecs->typedef_p))
	{
	  ಆದರೆ (flag_ms_extensions || flag_plan9_extensions)
	    ok = ನಿಜ;
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (TYPE_NAME (type) == ಖಾಲಿ)
	    ok = ನಿಜ;
	  ಇಲ್ಲದಿದ್ದರೆ
	    ok = ಸುಳ್ಳು;
	}
      ಆದರೆ (!ok)
	{
	  pedwarn (loc, 0, "declaration does not declare anything");
	  ಹಿಂತಿರುಗಿ NULL_ವೃಕ್ಷ;
	}
      ಆದರೆ (flag_isoc99)
	pedwarn_c99 (loc, OPT_Wpedantic,
		     "ISO C99 doesn%'t support unnamed structs/unions");
      ಇಲ್ಲದಿದ್ದರೆ
	pedwarn_c99 (loc, OPT_Wpedantic,
		     "ISO C90 doesn%'t support unnamed structs/unions");
    }

  ಮೌಲ್ಯ = grokdeclarator (declarator, declspecs, ಕ್ಷೇತ್ರ, ಸುಳ್ಳು,
			  ಅಗಲ ? &ಅಗಲ : ಖಾಲಿ, decl_attrs, ಅಭಿವ್ಯಕ್ತಿ, ಖಾಲಿ,
			  DEPRECATED_ಸಾಮಾನ್ಯ);

  /* When this field has name, its type is a top level type, we should
     call verify_counted_by_for_top_anonymous_type.  */
  ಆದರೆ (DECL_NAME (ಮೌಲ್ಯ) != NULL_ವೃಕ್ಷ
      && declspecs->typespec_ಬಗೆ == ctsk_tagdef)
    verify_counted_by_for_ತುದಿ_anonymous_type (declspecs->type);

  ಮುಕ್ತಾಯ_decl (ಮೌಲ್ಯ, loc, NULL_ವೃಕ್ಷ, NULL_ವೃಕ್ಷ, NULL_ವೃಕ್ಷ);
  DECL_INITIAL (ಮೌಲ್ಯ) = ಅಗಲ;
  ಆದರೆ (ಅಗಲ)
    ಗಣ_DECL_C_ಬಿಟ್_ಕ್ಷೇತ್ರ (ಮೌಲ್ಯ);

  ಆದರೆ (warn_cxx_compat && DECL_NAME (ಮೌಲ್ಯ) != NULL_ವೃಕ್ಷ)
    {
      /* If we currently have a binding for this field, set the
	 in_struct field in the binding, so that we warn about lookups
	 which find it.  */
      ರಚನೆ c_binding *b = I_ಚಿಹ್ನೆ_BINDING (DECL_NAME (ಮೌಲ್ಯ));
      ಆದರೆ (b != ಖಾಲಿ)
	{
	  /* If the in_struct field is not yet set, push it on a list
	     to be cleared when this struct is finished.  */
	  ಆದರೆ (!b->ಒಳ_struct)
	    {
	      struct_parse_info->fields.ಸುರಕ್ಷಿತ_ತಳ್ಳು (b);
	      b->ಒಳ_struct = 1;
	    }
	}
    }

  ಹಿಂತಿರುಗಿ ಮೌಲ್ಯ;
}

/* Subroutine of detect_field_duplicates: return whether X and Y,
   which are both fields in the same struct, have duplicate field
   names.  */

ಸ್ಥಿರ ತಾರ್ಕಿಕ
is_duplicate_ಕ್ಷೇತ್ರ (ವೃಕ್ಷ x, ವೃಕ್ಷ y)
{
  ಆದರೆ (DECL_NAME (x) != NULL_ವೃಕ್ಷ && DECL_NAME (x) == DECL_NAME (y))
    ಹಿಂತಿರುಗಿ ನಿಜ;

  /* When using -fplan9-extensions, an anonymous field whose name is a
     typedef can duplicate a field name.  */
  ಆದರೆ (flag_plan9_extensions
      && (DECL_NAME (x) == NULL_ವೃಕ್ಷ || DECL_NAME (y) == NULL_ವೃಕ್ಷ))
    {
      ವೃಕ್ಷ xt, xn, yt, yn;

      xt = ವೃಕ್ಷ_TYPE (x);
      ಆದರೆ (DECL_NAME (x) != NULL_ವೃಕ್ಷ)
	xn = DECL_NAME (x);
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ದಾಖಲೆ_OR_UNION_TYPE_P (xt)
	       && TYPE_NAME (xt) != NULL_ವೃಕ್ಷ
	       && ವೃಕ್ಷ_ಸಂಕೇತ (TYPE_NAME (xt)) == TYPE_DECL)
	xn = DECL_NAME (TYPE_NAME (xt));
      ಇಲ್ಲದಿದ್ದರೆ
	xn = NULL_ವೃಕ್ಷ;

      yt = ವೃಕ್ಷ_TYPE (y);
      ಆದರೆ (DECL_NAME (y) != NULL_ವೃಕ್ಷ)
	yn = DECL_NAME (y);
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ದಾಖಲೆ_OR_UNION_TYPE_P (yt)
	       && TYPE_NAME (yt) != NULL_ವೃಕ್ಷ
	       && ವೃಕ್ಷ_ಸಂಕೇತ (TYPE_NAME (yt)) == TYPE_DECL)
	yn = DECL_NAME (TYPE_NAME (yt));
      ಇಲ್ಲದಿದ್ದರೆ
	yn = NULL_ವೃಕ್ಷ;

      ಆದರೆ (xn != NULL_ವೃಕ್ಷ && xn == yn)
	ಹಿಂತಿರುಗಿ ನಿಜ;
    }

  ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
}

/* Subroutine of detect_field_duplicates: add the fields of FIELDLIST
   to HTAB, giving errors for any duplicates.  */

ಸ್ಥಿರ ಶೂನ್ಯ
detect_ಕ್ಷೇತ್ರ_duplicates_hash (ವೃಕ್ಷ fieldlist,
			      hash_ಕೋಷ್ಟಕ<nofree_ptr_hash <ವೃಕ್ಷ_ಗಂಟು> > *htab)
{
  ವೃಕ್ಷ x, y;
  ವೃಕ್ಷ_ಗಂಟು **ಸ್ಥಾನ;

  ಗಾಗಿ (x = fieldlist; x ; x = DECL_CHAIN (x))
    ಆದರೆ ((y = DECL_NAME (x)) != NULL_ವೃಕ್ಷ)
      {
	ಸ್ಥಾನ = htab->ಕಂಡುಹಿಡಿ_ಸ್ಥಾನ (y, ಸೇರಿಸು);
	ಆದರೆ (*ಸ್ಥಾನ)
	  {
	    error ("duplicate member %q+D", x);
	    DECL_NAME (x) = NULL_ವೃಕ್ಷ;
	  }
	*ಸ್ಥಾನ = y;
      }
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ದಾಖಲೆ_OR_UNION_TYPE_P (ವೃಕ್ಷ_TYPE (x)))
      {
	detect_ಕ್ಷೇತ್ರ_duplicates_hash (TYPE_FIELDS (ವೃಕ್ಷ_TYPE (x)), htab);

	/* When using -fplan9-extensions, an anonymous field whose
	   name is a typedef can duplicate a field name.  */
	ಆದರೆ (flag_plan9_extensions
	    && TYPE_NAME (ವೃಕ್ಷ_TYPE (x)) != NULL_ವೃಕ್ಷ
	    && ವೃಕ್ಷ_ಸಂಕೇತ (TYPE_NAME (ವೃಕ್ಷ_TYPE (x))) == TYPE_DECL)
	  {
	    ವೃಕ್ಷ xn = DECL_NAME (TYPE_NAME (ವೃಕ್ಷ_TYPE (x)));
	    ಸ್ಥಾನ = htab->ಕಂಡುಹಿಡಿ_ಸ್ಥಾನ (xn, ಸೇರಿಸು);
	    ಆದರೆ (*ಸ್ಥಾನ)
	      error ("duplicate member %q+D", TYPE_NAME (ವೃಕ್ಷ_TYPE (x)));
	    *ಸ್ಥಾನ = xn;
	  }
      }
}

/* Generate an error for any duplicate field names in FIELDLIST.  Munge
   the list such that this does not present a problem later.  */

ಸ್ಥಿರ ಶೂನ್ಯ
detect_ಕ್ಷೇತ್ರ_duplicates (ವೃಕ್ಷ fieldlist)
{
  ವೃಕ್ಷ x, y;
  ಪೂರ್ಣಾಂಕ timeout = 10;

  /* If the struct is the list of instance variables of an Objective-C
     class, then we need to check all the instance variables of
     superclasses when checking for duplicates (since you can't have
     an instance variable in a subclass with the same name as an
     instance variable in a superclass).  We pass on this job to the
     Objective-C compiler.  objc_detect_field_duplicates() will return
     false if we are not checking the list of instance variables and
     the C frontend should proceed with the standard field duplicate
     checks.  If we are checking the list of instance variables, the
     ObjC frontend will do the check, emit the errors if needed, and
     then return true.  */
  ಆದರೆ (c_dialect_objc ())
    ಆದರೆ (objc_detect_ಕ್ಷೇತ್ರ_duplicates (ಸುಳ್ಳು))
      ಹಿಂತಿರುಗಿ;

  /* First, see if there are more than "a few" fields.
     This is trivially true if there are zero or one fields.  */
  ಆದರೆ (!fieldlist || !DECL_CHAIN (fieldlist))
    ಹಿಂತಿರುಗಿ;
  x = fieldlist;
  ಮಾಡು {
    timeout--;
    ಆದರೆ (DECL_NAME (x) == NULL_ವೃಕ್ಷ
	&& ದಾಖಲೆ_OR_UNION_TYPE_P (ವೃಕ್ಷ_TYPE (x)))
      timeout = 0;
    x = DECL_CHAIN (x);
  } ಆಗ (timeout > 0 && x);

  /* If there were "few" fields and no anonymous structures or unions,
     avoid the overhead of allocating a hash table.  Instead just do
     the nested traversal thing.  */
  ಆದರೆ (timeout > 0)
    {
      ಗಾಗಿ (x = DECL_CHAIN (fieldlist); x; x = DECL_CHAIN (x))
	/* When using -fplan9-extensions, we can have duplicates
	   between typedef names and fields.  */
	ಆದರೆ (DECL_NAME (x)
	    || (flag_plan9_extensions
		&& DECL_NAME (x) == NULL_ವೃಕ್ಷ
		&& ದಾಖಲೆ_OR_UNION_TYPE_P (ವೃಕ್ಷ_TYPE (x))
		&& TYPE_NAME (ವೃಕ್ಷ_TYPE (x)) != NULL_ವೃಕ್ಷ
		&& ವೃಕ್ಷ_ಸಂಕೇತ (TYPE_NAME (ವೃಕ್ಷ_TYPE (x))) == TYPE_DECL))
	  {
	    ಗಾಗಿ (y = fieldlist; y != x; y = ವೃಕ್ಷ_CHAIN (y))
	      ಆದರೆ (is_duplicate_ಕ್ಷೇತ್ರ (y, x))
		{
		  error ("duplicate member %q+D", x);
		  DECL_NAME (x) = NULL_ವೃಕ್ಷ;
		}
	  }
    }
  ಇಲ್ಲದಿದ್ದರೆ
    {
      hash_ಕೋಷ್ಟಕ<nofree_ptr_hash <ವೃಕ್ಷ_ಗಂಟು> > htab (37);
      detect_ಕ್ಷೇತ್ರ_duplicates_hash (fieldlist, &htab);
    }
}

/* Finish up struct info used by -Wc++-compat.  */

ಸ್ಥಿರ ಶೂನ್ಯ
warn_cxx_compat_ಮುಕ್ತಾಯ_struct (ವೃಕ್ಷ fieldlist, ಎಣಿಕೆ ವೃಕ್ಷ_ಸಂಕೇತ_2 ಸಂಕೇತ_2,
			       location_t ದಾಖಲೆ_loc)
{
  ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ ix;
  ವೃಕ್ಷ x;
  ರಚನೆ c_binding *b;

  ಆದರೆ (fieldlist == NULL_ವೃಕ್ಷ)
    {
      ಆದರೆ (ಸಂಕೇತ_2 == ದಾಖಲೆ_TYPE)
	warning_at (ದಾಖಲೆ_loc, OPT_Wc___compat,
		    "empty struct has size 0 in C, size 1 in C++");
      ಇಲ್ಲದಿದ್ದರೆ
	warning_at (ದಾಖಲೆ_loc, OPT_Wc___compat,
		    "empty union has size 0 in C, size 1 in C++");
    }

  /* Set the C_TYPE_DEFINED_IN_STRUCT flag for each type defined in
     the current struct.  We do this now at the end of the struct
     because the flag is used to issue visibility warnings, and we
     only want to issue those warnings if the type is referenced
     outside of the struct declaration.  */
  FOR_EACH_VEC_ELT (struct_parse_info->struct_types, ix, x)
    C_TYPE_DEFINED_ಒಳ_STRUCT (x) = 1;

  /* The TYPEDEFS_SEEN field of STRUCT_PARSE_INFO is a list of
     typedefs used when declaring fields in this struct.  If the name
     of any of the fields is also a typedef name then the struct would
     not parse in C++, because the C++ lookup rules say that the
     typedef name would be looked up in the context of the struct, and
     would thus be the field rather than the typedef.  */
  ಆದರೆ (!struct_parse_info->typedefs_ನೋಡಿದ.is_ಖಾಲಿಗಳು ()
      && fieldlist != NULL_ವೃಕ್ಷ)
    {
      /* Use a hash_set<tree> using the name of the typedef.  We can use
	 a hash_set<tree> because identifiers are interned.  */
      hash_ಗಣ<ವೃಕ್ಷ> tset;

      FOR_EACH_VEC_ELT (struct_parse_info->typedefs_ನೋಡಿದ, ix, x)
	tset.ಕೂಡಿಸು (DECL_NAME (x));

      ಗಾಗಿ (x = fieldlist; x != NULL_ವೃಕ್ಷ; x = DECL_CHAIN (x))
	{
	  ಆದರೆ (DECL_NAME (x) != NULL_ವೃಕ್ಷ
	      && tset.ಒಳಗೊಂಡಿದೆ (DECL_NAME (x)))
	    {
	      warning_at (DECL_ಮೂಲ_LOCATION (x), OPT_Wc___compat,
			  "using %qD as both field and typedef name is "
			  "invalid in C++", x);
	      /* FIXME: It would be nice to report the location where
		 the typedef name is used.  */
	    }
	}
    }

  /* For each field which has a binding and which was not defined in
     an enclosing struct, clear the in_struct field.  */
  FOR_EACH_VEC_ELT (struct_parse_info->fields, ix, b)
    b->ಒಳ_struct = 0;
}

/* Function to help qsort sort FIELD_DECLs by name order.  */

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ
ಕ್ಷೇತ್ರ_decl_cmp (ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *x_p, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *y_p)
{
  ಸ್ಥಿರಾಂಕ ವೃಕ್ಷ *ಸ್ಥಿರಾಂಕ x = (ಸ್ಥಿರಾಂಕ ವೃಕ್ಷ *) x_p;
  ಸ್ಥಿರಾಂಕ ವೃಕ್ಷ *ಸ್ಥಿರಾಂಕ y = (ಸ್ಥಿರಾಂಕ ವೃಕ್ಷ *) y_p;

  ಆದರೆ (DECL_NAME (*x) == DECL_NAME (*y))
    /* A nontype is "greater" than a type.  */
    ಹಿಂತಿರುಗಿ (ವೃಕ್ಷ_ಸಂಕೇತ (*y) == TYPE_DECL) - (ವೃಕ್ಷ_ಸಂಕೇತ (*x) == TYPE_DECL);
  ಆದರೆ (DECL_NAME (*x) == NULL_ವೃಕ್ಷ)
    ಹಿಂತಿರುಗಿ -1;
  ಆದರೆ (DECL_NAME (*y) == NULL_ವೃಕ್ಷ)
    ಹಿಂತಿರುಗಿ 1;
  ಆದರೆ (DECL_NAME (*x) < DECL_NAME (*y))
    ಹಿಂತಿರುಗಿ -1;
  ಹಿಂತಿರುಗಿ 1;
}

/* If this structure or union completes the type of any previous
   variable declaration, lay it out and output its rtl.  */
ಸ್ಥಿರ ಶೂನ್ಯ
ಮುಕ್ತಾಯ_incomplete_vars (ವೃಕ್ಷ incomplete_vars, ತಾರ್ಕಿಕ toplevel)
{
  ಗಾಗಿ (ವೃಕ್ಷ x = incomplete_vars; x; x = ವೃಕ್ಷ_CHAIN (x))
    {
      ವೃಕ್ಷ decl = ವೃಕ್ಷ_ಮೌಲ್ಯ (x);
      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (decl)) == ARRAY_TYPE)
	layout_array_type (ವೃಕ್ಷ_TYPE (decl));
      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (decl) != TYPE_DECL)
	{
	  relayout_decl (decl);
	  ಆದರೆ (c_dialect_objc ())
	    objc_check_decl (decl);
	  rest_ದ_decl_compilation (decl, toplevel, 0);
	}
    }
}

/* Determine whether the FIELD_DECL X is a flexible array member according to
   the following info:
  A. whether the FIELD_DECL X is the last field of the DECL_CONTEXT;
  B. whether the FIELD_DECL is an array that is declared as "[]", "[0]",
     or "[1]";
  C. flag_strict_flex_arrays;
  D. the attribute strict_flex_array that is attached to the field
     if presenting.
  Return TRUE when it's a flexible array member, FALSE otherwise.  */

ಸ್ಥಿರ ತಾರ್ಕಿಕ
is_flexible_array_member_p (ತಾರ್ಕಿಕ is_ಕೊನೆಯ_ಕ್ಷೇತ್ರ,
			    ವೃಕ್ಷ x)
{
  /* If not the last field, return false.  */
  ಆದರೆ (!is_ಕೊನೆಯ_ಕ್ಷೇತ್ರ)
    ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;

  /* If not an array field, return false.  */
  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (x)) != ARRAY_TYPE)
    ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;

  ತಾರ್ಕಿಕ is_zero_ಉದ್ದಳತೆ_array = zero_ಉದ್ದಳತೆ_array_type_p (ವೃಕ್ಷ_TYPE (x));
  ತಾರ್ಕಿಕ is_one_element_array = one_element_array_type_p (ವೃಕ್ಷ_TYPE (x));
  ತಾರ್ಕಿಕ is_flexible_array = flexible_array_member_type_p (ವೃಕ್ಷ_TYPE (x));

  ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ strict_flex_array_level = c_strict_flex_array_level_ದ (x);

  ಆಯ್ಕೆ (strict_flex_array_level)
    {
      ಸ್ಥಿತಿ 0:
	/* Default, all trailing arrays are flexible array members.  */
	ಹಿಂತಿರುಗಿ ನಿಜ;
      ಸ್ಥಿತಿ 1:
	/* Level 1: all "[1]", "[0]", and "[]" are flexible array members.  */
	ಆದರೆ (is_one_element_array)
	  ಹಿಂತಿರುಗಿ ನಿಜ;
	/* FALLTHROUGH.  */
      ಸ್ಥಿತಿ 2:
	/* Level 2: all "[0]", and "[]" are flexible array members.  */
	ಆದರೆ (is_zero_ಉದ್ದಳತೆ_array)
	  ಹಿಂತಿರುಗಿ ನಿಜ;
	/* FALLTHROUGH.  */
      ಸ್ಥಿತಿ 3:
	/* Level 3: Only "[]" are flexible array members.  */
	ಆದರೆ (is_flexible_array)
	  ಹಿಂತಿರುಗಿ ನಿಜ;
	ನಿಲ್ಲಿಸು;
      ಪೂರ್ವನಿಯೋಜಿತ:
	gcc_unreachable ();
    }
  ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
}

/* Recompute TYPE_CANONICAL for variants of the type including qualified
   versions of the type and related pointer types after an aggregate type
   has been finalized.
   Will not update array types, pointers to array types, function
   types and other derived types created while the type was still
   incomplete, those will remain TYPE_STRUCTURAL_EQUALITY_P.  */

ಸ್ಥಿರ ಶೂನ್ಯ
c_update_type_canonical (ವೃಕ್ಷ t)
{
  gcc_checking_assert (TYPE_MAIN_VARIANT (t) == t && !TYPE_QUALS (t));
  ಗಾಗಿ (ವೃಕ್ಷ x = t, l = NULL_ವೃಕ್ಷ; x; l = x, x = TYPE_ಮುಂದಿನ_VARIANT (x))
    {
      ಆದರೆ (x != t && TYPE_STRUCTURAL_EQUALITY_P (x))
	{
	  ಆದರೆ (!TYPE_QUALS (x))
	    TYPE_CANONICAL (x) = TYPE_CANONICAL (t);
	  ಇಲ್ಲದಿದ್ದರೆ
	    {
	      ವೃಕ್ಷ
		c = c_build_qualified_type (TYPE_CANONICAL (t), TYPE_QUALS (x));
	      ಆದರೆ (TYPE_STRUCTURAL_EQUALITY_P (c))
		{
		  gcc_checking_assert (TYPE_CANONICAL (t) == t);
		  ಆದರೆ (c == x)
		    TYPE_CANONICAL (x) = x;
		  ಇಲ್ಲದಿದ್ದರೆ
		    {
		      /* build_qualified_type for this function unhelpfully
			 moved c from some later spot in TYPE_MAIN_VARIANT (t)
			 chain to right after t (or created it there).  Move
			 it right before x and process c and then x.  */
		      gcc_checking_assert (TYPE_ಮುಂದಿನ_VARIANT (t) == c);
		      ಆದರೆ (l != t)
			{
			  TYPE_ಮುಂದಿನ_VARIANT (t) = TYPE_ಮುಂದಿನ_VARIANT (c);
			  TYPE_ಮುಂದಿನ_VARIANT (l) = c;
			  TYPE_ಮುಂದಿನ_VARIANT (c) = x;
			}
		      TYPE_CANONICAL (c) = c;
		      x = c;
		    }
		}
	      ಇಲ್ಲದಿದ್ದರೆ
		TYPE_CANONICAL (x) = TYPE_CANONICAL (c);
	    }
	}
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (x != t)
	ಮುಂದುವರಿ;
      ಗಾಗಿ (ವೃಕ್ಷ p = TYPE_ಸೂಚಕ_ಗಮ್ಯ (x); p; p = TYPE_ಮುಂದಿನ_PTR_ಗಮ್ಯ (p))
	{
	  ಆದರೆ (!TYPE_STRUCTURAL_EQUALITY_P (p))
	    ಮುಂದುವರಿ;
	  ಆದರೆ (TYPE_CANONICAL (x) != x || TYPE_REF_CAN_ALIAS_ALL (p))
	    TYPE_CANONICAL (p)
	      = c_build_ಸೂಚಕ_type_for_ಬಹುಲಕ (TYPE_CANONICAL (x), TYPE_ಬಹುಲಕ (p),
					       ಸುಳ್ಳು);
	  ಇಲ್ಲದಿದ್ದರೆ
	    TYPE_CANONICAL (p) = p;
	  c_update_type_canonical (p);
	}
    }
}


/* We set C_TYPE_VARIABLY_MODIFIED for derived types.  We will not update
   array types, pointers to array types, function types and other derived
   types created while the type was still incomplete.  We need to update
   at least all types for which TYPE_CANONICAL will bet set, because for
   those we later assume (in c_variably_modified_p) that the bit is
   up-to-date.  */

ಸ್ಥಿರ ಶೂನ್ಯ
c_update_variably_modified (ವೃಕ್ಷ t)
{
  ಗಾಗಿ (ವೃಕ್ಷ x = t; x; x = TYPE_ಮುಂದಿನ_VARIANT (x))
    {
      C_TYPE_VARIABLY_MODIFIED (x) = 1;
      ಗಾಗಿ (ವೃಕ್ಷ p = TYPE_ಸೂಚಕ_ಗಮ್ಯ (x); p; p = TYPE_ಮುಂದಿನ_PTR_ಗಮ್ಯ (p))
	c_update_variably_modified (p);
    }
}


/* Verify the argument of the counted_by attribute of each field of
   the containing structure, OUTMOST_STRUCT_TYPE, including its inner
   anonymous struct/union, Report error and remove the corresponding
   attribute when it's not.  */

ಸ್ಥಿರ ಶೂನ್ಯ
verify_counted_by_attribute (ವೃಕ್ಷ outmost_struct_type,
			     ವೃಕ್ಷ cur_struct_type)
{
  ಗಾಗಿ (ವೃಕ್ಷ ಕ್ಷೇತ್ರ_2 = TYPE_FIELDS (cur_struct_type); ಕ್ಷೇತ್ರ_2;
       ಕ್ಷೇತ್ರ_2 = ವೃಕ್ಷ_CHAIN (ಕ್ಷೇತ್ರ_2))
    {
      ಆದರೆ (flexible_array_member_type_p (ವೃಕ್ಷ_TYPE (ಕ್ಷೇತ್ರ_2))
	   || ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (ಕ್ಷೇತ್ರ_2)) == ಸೂಚಕ_TYPE)
	{
	  ವೃಕ್ಷ attr_counted_by = lookup_attribute ("counted_by",
						   DECL_ಗುಣಲಕ್ಷಣಗಳು (ಕ್ಷೇತ್ರ_2));

	  ಆದರೆ (!attr_counted_by)
	    ಮುಂದುವರಿ;

	  /* If there is an counted_by attribute attached to the field,
	     verify it.  */

	  ವೃಕ್ಷ fieldname = ವೃಕ್ಷ_ಮೌಲ್ಯ (ವೃಕ್ಷ_ಮೌಲ್ಯ (attr_counted_by));

	  /* Verify the argument of the attribute is a valid field of the
	     containing structure.  */

	  ವೃಕ್ಷ counted_by_ಕ್ಷೇತ್ರ = lookup_ಕ್ಷೇತ್ರ (outmost_struct_type,
						fieldname);

	  /* Error when the field is not found in the containing structure
	     and remove the corresponding counted_by attribute from the
	     field_decl.  */
	  ಆದರೆ (!counted_by_ಕ್ಷೇತ್ರ)
	    {
	      error_at (DECL_ಮೂಲ_LOCATION (ಕ್ಷೇತ್ರ_2),
		    "argument %qE to the %<counted_by%> attribute"
		    " is not a field declaration in the same structure"
		    " as %qD", fieldname, ಕ್ಷೇತ್ರ_2);
	      DECL_ಗುಣಲಕ್ಷಣಗಳು (ಕ್ಷೇತ್ರ_2)
		= remove_attribute ("counted_by", DECL_ಗುಣಲಕ್ಷಣಗಳು (ಕ್ಷೇತ್ರ_2));
	    }
	  ಇಲ್ಲದಿದ್ದರೆ
	  /* Error when the field is not with an integer type.  */
	    {
	      ಆಗ (ವೃಕ್ಷ_CHAIN (counted_by_ಕ್ಷೇತ್ರ))
		counted_by_ಕ್ಷೇತ್ರ = ವೃಕ್ಷ_CHAIN (counted_by_ಕ್ಷೇತ್ರ);
	      ವೃಕ್ಷ real_ಕ್ಷೇತ್ರ = ವೃಕ್ಷ_ಮೌಲ್ಯ (counted_by_ಕ್ಷೇತ್ರ);

	      ಆದರೆ (!INTEGRAL_TYPE_P (ವೃಕ್ಷ_TYPE (real_ಕ್ಷೇತ್ರ)))
		{
		  error_at (DECL_ಮೂಲ_LOCATION (ಕ್ಷೇತ್ರ_2),
			"argument %qE to the %<counted_by%> attribute"
			" is not a field declaration with an integer type",
			fieldname);
		  DECL_ಗುಣಲಕ್ಷಣಗಳು (ಕ್ಷೇತ್ರ_2)
		    = remove_attribute ("counted_by",
				    DECL_ಗುಣಲಕ್ಷಣಗಳು (ಕ್ಷೇತ್ರ_2));
		}
	    }
	}
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ದಾಖಲೆ_OR_UNION_TYPE_P (ವೃಕ್ಷ_TYPE (ಕ್ಷೇತ್ರ_2))
	       && (DECL_NAME (ಕ್ಷೇತ್ರ_2) == NULL_ವೃಕ್ಷ))
	verify_counted_by_attribute (outmost_struct_type, ವೃಕ್ಷ_TYPE (ಕ್ಷೇತ್ರ_2));
    }
}

/* Caller should make sure the TYPE is a top-level type (i.e. not being
   nested in other structure/uniona). For such type, verify its counted_by
   if it is an anonymous structure/union.  */

ಶೂನ್ಯ
verify_counted_by_for_ತುದಿ_anonymous_type (ವೃಕ್ಷ type)
{
  ಆದರೆ (!ದಾಖಲೆ_OR_UNION_TYPE_P (type))
    ಹಿಂತಿರುಗಿ;

  ಆದರೆ (C_TYPE_FIELDS_HAS_COUNTED_BY (type)
      && c_type_ಟ್ಯಾಗ್ (type) == NULL_ವೃಕ್ಷ)
    verify_counted_by_attribute (type, type);
}

/* TYPE is a struct or union that we're applying may_alias to after the body is
   parsed.  Fixup any POINTER_TO types.  */

ಸ್ಥಿರ ಶೂನ್ಯ
c_fixup_may_alias (ವೃಕ್ಷ type)
{
  ಗಾಗಿ (ವೃಕ್ಷ t = TYPE_ಸೂಚಕ_ಗಮ್ಯ (type); t; t = TYPE_ಮುಂದಿನ_PTR_ಗಮ್ಯ (t))
    ಗಾಗಿ (ವೃಕ್ಷ v = TYPE_MAIN_VARIANT (t); v; v = TYPE_ಮುಂದಿನ_VARIANT (v))
      TYPE_REF_CAN_ALIAS_ALL (v) = ನಿಜ;
}

/* Fill in the fields of a RECORD_TYPE or UNION_TYPE node, T.
   LOC is the location of the RECORD_TYPE or UNION_TYPE's definition.
   FIELDLIST is a chain of FIELD_DECL nodes for the fields.
   ATTRIBUTES are attributes to be applied to the structure.

   ENCLOSING_STRUCT_PARSE_INFO is the value of STRUCT_PARSE_INFO when
   the struct was started.  */

ವೃಕ್ಷ
ಮುಕ್ತಾಯ_struct (location_t loc, ವೃಕ್ಷ t, ವೃಕ್ಷ fieldlist, ವೃಕ್ಷ ಗುಣಲಕ್ಷಣಗಳು,
	       ವರ್ಗ c_struct_parse_info *enclosing_struct_parse_info,
	       ವೃಕ್ಷ *ಅಭಿವ್ಯಕ್ತಿ)
{
  ವೃಕ್ಷ x;
  ತಾರ್ಕಿಕ toplevel = file_scope == current_scope;

  /* If this type was previously laid out as a forward reference,
     make sure we lay it out again.  */

  TYPE_ಗಾತ್ರ (t) = NULL_ವೃಕ್ಷ;

  decl_ಗುಣಲಕ್ಷಣಗಳು (&t, ಗುಣಲಕ್ಷಣಗಳು, (ಪೂರ್ಣಾಂಕ) ATTR_FLAG_TYPE_ಒಳ_ಇರಿಸು);

  ಆದರೆ (pedantic)
    {
      ಗಾಗಿ (x = fieldlist; x; x = DECL_CHAIN (x))
	{
	  ಆದರೆ (DECL_NAME (x) != NULL_ವೃಕ್ಷ)
	    ನಿಲ್ಲಿಸು;
	  ಆದರೆ (flag_isoc11 && ದಾಖಲೆ_OR_UNION_TYPE_P (ವೃಕ್ಷ_TYPE (x)))
	    ನಿಲ್ಲಿಸು;
	}

      ಆದರೆ (x == NULL_ವೃಕ್ಷ)
	{
	  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (t) == UNION_TYPE)
	    {
	      ಆದರೆ (fieldlist)
		pedwarn (loc, OPT_Wpedantic, "union has no named members");
	      ಇಲ್ಲದಿದ್ದರೆ
		pedwarn (loc, OPT_Wpedantic, "union has no members");
	    }
	  ಇಲ್ಲದಿದ್ದರೆ
	    {
	      ಆದರೆ (fieldlist)
		pedwarn (loc, OPT_Wpedantic, "struct has no named members");
	      ಇಲ್ಲದಿದ್ದರೆ
		pedwarn (loc, OPT_Wpedantic, "struct has no members");
	    }
	}
    }

  /* Install struct as DECL_CONTEXT of each field decl.
     Also process specified field sizes, found in the DECL_INITIAL,
     storing 0 there after the type has been changed to precision equal
     to its width, rather than the precision of the specified standard
     type.  (Correct layout requires the original type to have been preserved
     until now.)  */

  ತಾರ್ಕಿಕ saw_named_ಕ್ಷೇತ್ರ = ಸುಳ್ಳು;
  ಗಾಗಿ (x = fieldlist; x; x = DECL_CHAIN (x))
    {
      /* Whether this field is the last field of the structure or union.
	 for UNION, any field is the last field of it.  */
      ತಾರ್ಕಿಕ is_ಕೊನೆಯ_ಕ್ಷೇತ್ರ = (DECL_CHAIN (x) == NULL_ವೃಕ್ಷ)
			    || (ವೃಕ್ಷ_ಸಂಕೇತ (t) == UNION_TYPE);

      ಆದರೆ (ವೃಕ್ಷ_TYPE (x) == error_mark_ಗಂಟು)
	ಮುಂದುವರಿ;

      DECL_CONTEXT (x) = t;

      ವೃಕ್ಷ t1 = strip_array_types (ವೃಕ್ಷ_TYPE (x));
      /* If any field is const, the structure type is pseudo-const.  */
      ಆದರೆ (ವೃಕ್ಷ_READONLY (x))
	C_TYPE_FIELDS_READONLY (t) = 1;
      ಇಲ್ಲದಿದ್ದರೆ
	{
	  /* A field that is pseudo-const makes the structure likewise.  */
	  ಆದರೆ (ದಾಖಲೆ_OR_UNION_TYPE_P (t1) && C_TYPE_FIELDS_READONLY (t1))
	    C_TYPE_FIELDS_READONLY (t) = 1;
	}

      /* Any field that is volatile means variables of this type must be
	 treated in some ways as volatile.  */
      ಆದರೆ (ವೃಕ್ಷ_THIS_VOLATILE (x))
	{
	  C_TYPE_FIELDS_VOLATILE (t) = 1;
	  C_TYPE_FIELDS_NON_CONSTEXPR (t) = 1;
	}

      /* Any field that is volatile, restrict-qualified or atomic
	 means the type cannot be used for a constexpr object.  */
      ಆದರೆ (TYPE_QUALS (t1)
	  & (TYPE_QUAL_VOLATILE | TYPE_QUAL_RESTRICT | TYPE_QUAL_ATOMIC))
	C_TYPE_FIELDS_NON_CONSTEXPR (t) = 1;
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ದಾಖಲೆ_OR_UNION_TYPE_P (t1) && C_TYPE_FIELDS_NON_CONSTEXPR (t1))
	    C_TYPE_FIELDS_NON_CONSTEXPR (t) = 1;

      /* Any field of nominal variable size implies structure is too.  */
      ಆದರೆ (C_DECL_VARIABLE_ಗಾತ್ರ (x))
	C_TYPE_VARIABLE_ಗಾತ್ರ (t) = 1;

      /* If any field is variably modified, record this fact. */
      ಆದರೆ (c_type_variably_modified_p (ವೃಕ್ಷ_TYPE (x)))
	C_TYPE_VARIABLY_MODIFIED (t) = 1;

      ಆದರೆ (DECL_C_ಬಿಟ್_ಕ್ಷೇತ್ರ (x))
	{
	  ಚಿಹ್ನೆರಹಿತ HOST_WIDE_INT ಅಗಲ = ವೃಕ್ಷ_ಗಮ್ಯ_uhwi (DECL_INITIAL (x));
	  DECL_ಗಾತ್ರ (x) = bitsize_int (ಅಗಲ);
	  DECL_ಬಿಟ್_ಕ್ಷೇತ್ರ (x) = 1;
	}

      ಆದರೆ (TYPE_PACKED (t)
	  && (DECL_ಬಿಟ್_ಕ್ಷೇತ್ರ (x)
	      || TYPE_ALIGN (ವೃಕ್ಷ_TYPE (x)) > ಬಿಟ್ಟುಗಳು_ಪ್ರತಿ_UNIT))
	DECL_PACKED (x) = 1;

      /* Detect flexible array member in an invalid context.  */
      ಆದರೆ (flexible_array_member_type_p (ವೃಕ್ಷ_TYPE (x)))
	{
	  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (t) == UNION_TYPE)
	    pedwarn (DECL_ಮೂಲ_LOCATION (x), OPT_Wpedantic,
		     "flexible array member in union is a GCC extension");
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!is_ಕೊನೆಯ_ಕ್ಷೇತ್ರ)
	    {
	      error_at (DECL_ಮೂಲ_LOCATION (x),
			"flexible array member not at end of struct");
	      ವೃಕ್ಷ_TYPE (x) = error_mark_ಗಂಟು;
	    }
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!saw_named_ಕ್ಷೇತ್ರ)
	    pedwarn (DECL_ಮೂಲ_LOCATION (x), OPT_Wpedantic,
		     "flexible array member in a struct with no named "
		     "members is a GCC extension");
	  ಆದರೆ (lookup_attribute ("counted_by", DECL_ಗುಣಲಕ್ಷಣಗಳು (x)))
	    C_TYPE_FIELDS_HAS_COUNTED_BY (t) = 1;
	}

      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (x)) == ಸೂಚಕ_TYPE
	  && lookup_attribute ("counted_by", DECL_ಗುಣಲಕ್ಷಣಗಳು (x)))
	C_TYPE_FIELDS_HAS_COUNTED_BY (t) = 1;

      /* If the field is an anonymous structure that includes a field
	 with counted_by attribute, this structure should also be marked
	 too.  */
      ಆದರೆ (ದಾಖಲೆ_OR_UNION_TYPE_P (ವೃಕ್ಷ_TYPE (x))
	  && C_TYPE_FIELDS_HAS_COUNTED_BY (ವೃಕ್ಷ_TYPE (x))
	  && DECL_NAME (x) == NULL_ವೃಕ್ಷ
	  && c_type_ಟ್ಯಾಗ್ (ವೃಕ್ಷ_TYPE (x)) == NULL_ವೃಕ್ಷ)
	C_TYPE_FIELDS_HAS_COUNTED_BY (t) = 1;

      ಆದರೆ (pedantic && ವೃಕ್ಷ_ಸಂಕೇತ (t) == ದಾಖಲೆ_TYPE
	  && flexible_array_type_p (ವೃಕ್ಷ_TYPE (x)))
	pedwarn (DECL_ಮೂಲ_LOCATION (x), OPT_Wpedantic,
		 "invalid use of structure with flexible array member");

      /* Set DECL_NOT_FLEXARRAY flag for FIELD_DECL x.  */
      DECL_NOT_FLEXARRAY (x) = !is_flexible_array_member_p (is_ಕೊನೆಯ_ಕ್ಷೇತ್ರ, x);

      /* Set TYPE_INCLUDES_FLEXARRAY for the context of x, t.
	 when x is an array and is the last field.
	 There is only one last_field for a structure type, but there might
	 be multiple last_fields for a union type, therefore we should ORed
	 the result for multiple last_fields.  */
      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (x)) == ARRAY_TYPE)
	TYPE_INCLUDES_FLEXARRAY (t)
	  |= is_ಕೊನೆಯ_ಕ್ಷೇತ್ರ && flexible_array_member_type_p (ವೃಕ್ಷ_TYPE (x));
      /* Recursively set TYPE_INCLUDES_FLEXARRAY for the context of x, t
	 when x is an union or record and is the last field.  */
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ದಾಖಲೆ_OR_UNION_TYPE_P (ವೃಕ್ಷ_TYPE (x)))
	TYPE_INCLUDES_FLEXARRAY (t)
	  |= is_ಕೊನೆಯ_ಕ್ಷೇತ್ರ && TYPE_INCLUDES_FLEXARRAY (ವೃಕ್ಷ_TYPE (x));

      ಆದರೆ (warn_flex_array_member_not_at_ಕೊನೆ
	  && !is_ಕೊನೆಯ_ಕ್ಷೇತ್ರ
	  && ದಾಖಲೆ_OR_UNION_TYPE_P (ವೃಕ್ಷ_TYPE (x))
	  && TYPE_INCLUDES_FLEXARRAY (ವೃಕ್ಷ_TYPE (x)))
	warning_at (DECL_ಮೂಲ_LOCATION (x),
		    OPT_Wflex_array_member_not_at_ಕೊನೆ,
		    "structure containing a flexible array member"
		    " is not at the end of another structure");

      ಆದರೆ (DECL_NAME (x)
	  || ದಾಖಲೆ_OR_UNION_TYPE_P (ವೃಕ್ಷ_TYPE (x)))
	saw_named_ಕ್ಷೇತ್ರ = ನಿಜ;

      ಆದರೆ (AGGREGATE_TYPE_P (ವೃಕ್ಷ_TYPE (x))
	  && TYPE_TYPELESS_STORAGE (ವೃಕ್ಷ_TYPE (x)))
	TYPE_TYPELESS_STORAGE (t) = ನಿಜ;
    }

  detect_ಕ್ಷೇತ್ರ_duplicates (fieldlist);

  /* Now we have the nearly final fieldlist.  Record it,
     then lay out the structure or union (including the fields).  */

  TYPE_FIELDS (t) = fieldlist;

  maybe_apply_pragma_scalar_storage_ಕ್ರಮ (t);

  layout_type (t);

  ಆದರೆ (TYPE_ಗಾತ್ರ_UNIT (t)
      && ವೃಕ್ಷ_ಸಂಕೇತ (TYPE_ಗಾತ್ರ_UNIT (t)) == INTEGER_CST
      && !ವೃಕ್ಷ_ಅತಿಪ್ರವಾಹ (TYPE_ಗಾತ್ರ_UNIT (t))
      && !valid_constant_ಗಾತ್ರ_p (TYPE_ಗಾತ್ರ_UNIT (t)))
    error ("type %qT is too large", t);

  /* Give bit-fields their proper types and rewrite the type of array fields
     with scalar component if the enclosing type has reverse storage order.  */
  ಗಾಗಿ (ವೃಕ್ಷ ಕ್ಷೇತ್ರ_2 = fieldlist; ಕ್ಷೇತ್ರ_2; ಕ್ಷೇತ್ರ_2 = DECL_CHAIN (ಕ್ಷೇತ್ರ_2))
    {
      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ಕ್ಷೇತ್ರ_2) == ಕ್ಷೇತ್ರ_DECL
	  && DECL_INITIAL (ಕ್ಷೇತ್ರ_2)
	  && ವೃಕ್ಷ_TYPE (ಕ್ಷೇತ್ರ_2) != error_mark_ಗಂಟು)
	{
	  ಚಿಹ್ನೆರಹಿತ HOST_WIDE_INT ಅಗಲ
	    = ವೃಕ್ಷ_ಗಮ್ಯ_uhwi (DECL_INITIAL (ಕ್ಷೇತ್ರ_2));
	  ವೃಕ್ಷ type = ವೃಕ್ಷ_TYPE (ಕ್ಷೇತ್ರ_2);
	  ಆದರೆ (ಸದಿಶ_TYPE_P (type))
	    {
	      error_at (DECL_ಮೂಲ_LOCATION (ಕ್ಷೇತ್ರ_2),
			"bit-field %qD has invalid type", ಕ್ಷೇತ್ರ_2);
	      type = ವೃಕ್ಷ_TYPE (type);
	      ವೃಕ್ಷ_TYPE (ಕ್ಷೇತ್ರ_2) = type;
	    }
	  ಆದರೆ (ಅಗಲ != TYPE_PRECISION (type))
	    {
	      ಆದರೆ (BITINT_TYPE_P (type)
		  && ಅಗಲ >= ((TYPE_UNSIGNED (type) || flag_isoc2y) ? 1 : 2))
		ವೃಕ್ಷ_TYPE (ಕ್ಷೇತ್ರ_2)
		  = build_bitint_type (ಅಗಲ, TYPE_UNSIGNED (type));
	      ಇಲ್ಲದಿದ್ದರೆ
		ವೃಕ್ಷ_TYPE (ಕ್ಷೇತ್ರ_2)
		  = c_build_bitfield_integer_type (ಅಗಲ,
						   TYPE_UNSIGNED (type));
	      ಆದರೆ (ವೃಕ್ಷ attr = c_hardbool_type_attr (type))
		decl_ಗುಣಲಕ್ಷಣಗಳು (&ವೃಕ್ಷ_TYPE (ಕ್ಷೇತ್ರ_2),
				 copy_list (attr),
				 0, NULL_ವೃಕ್ಷ);
	      ಗಣ_DECL_ಬಹುಲಕ (ಕ್ಷೇತ್ರ_2, TYPE_ಬಹುಲಕ (ವೃಕ್ಷ_TYPE (ಕ್ಷೇತ್ರ_2)));
	    }
	  DECL_INITIAL (ಕ್ಷೇತ್ರ_2) = NULL_ವೃಕ್ಷ;
	}
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (TYPE_ಹಿಮ್ಮುಖ_STORAGE_ಕ್ರಮ (t)
	       && ವೃಕ್ಷ_ಸಂಕೇತ (ಕ್ಷೇತ್ರ_2) == ಕ್ಷೇತ್ರ_DECL
	       && ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (ಕ್ಷೇತ್ರ_2)) == ARRAY_TYPE)
	{
	  ವೃಕ್ಷ ftype = ವೃಕ್ಷ_TYPE (ಕ್ಷೇತ್ರ_2);
	  ವೃಕ್ಷ ctype = strip_array_types (ftype);
	  ಆದರೆ (!ದಾಖಲೆ_OR_UNION_TYPE_P (ctype) && TYPE_ಬಹುಲಕ (ctype) != QImode)
	    {
	      ವೃಕ್ಷ fmain_type = TYPE_MAIN_VARIANT (ftype);
	      ವೃಕ್ಷ *typep = &fmain_type;
	      ಮಾಡು {
		*typep = build_distinct_type_copy (*typep);
		TYPE_ಹಿಮ್ಮುಖ_STORAGE_ಕ್ರಮ (*typep) = 1;
		typep = &ವೃಕ್ಷ_TYPE (*typep);
	      } ಆಗ (ವೃಕ್ಷ_ಸಂಕೇತ (*typep) == ARRAY_TYPE);
	      ವೃಕ್ಷ_TYPE (ಕ್ಷೇತ್ರ_2)
		= c_build_qualified_type (fmain_type, TYPE_QUALS (ftype));
	    }
	}

      /* Warn on problematic type punning for storage order purposes.  */
      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (t) == UNION_TYPE
	  && ವೃಕ್ಷ_ಸಂಕೇತ (ಕ್ಷೇತ್ರ_2) == ಕ್ಷೇತ್ರ_DECL
	  && AGGREGATE_TYPE_P (ವೃಕ್ಷ_TYPE (ಕ್ಷೇತ್ರ_2)))
	{
	  ವೃಕ್ಷ ftype = ವೃಕ್ಷ_TYPE (ಕ್ಷೇತ್ರ_2);
	  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ftype) == ARRAY_TYPE)
	    ftype = strip_array_types (ftype);
	  ಆದರೆ (ದಾಖಲೆ_OR_UNION_TYPE_P (ftype)
	      && TYPE_ಹಿಮ್ಮುಖ_STORAGE_ಕ್ರಮ (ftype)
		 != TYPE_ಹಿಮ್ಮುಖ_STORAGE_ಕ್ರಮ (t))
	    warning_at (DECL_ಮೂಲ_LOCATION (ಕ್ಷೇತ್ರ_2),
			OPT_Wscalar_storage_ಕ್ರಮ,
			"type punning toggles scalar storage order");
	}
    }

  /* Now we have the truly final field list.
     Store it in this type and in the variants.  */

  TYPE_FIELDS (t) = fieldlist;

  /* If there are lots of fields, sort so we can look through them fast.
     We arbitrarily consider 16 or more elts to be "a lot".  */

  {
    ಪೂರ್ಣಾಂಕ len = 0;

    ಗಾಗಿ (x = fieldlist; x; x = DECL_CHAIN (x))
      {
	ಆದರೆ (len > 15 || DECL_NAME (x) == ಖಾಲಿ)
	  ನಿಲ್ಲಿಸು;
	len += 1;
      }

    ಆದರೆ (len > 15)
      {
	ವೃಕ್ಷ *ಕ್ಷೇತ್ರ_array;
	ರಚನೆ lang_type *space;
	ರಚನೆ sorted_fields_type *space2;

	len += list_ಉದ್ದಳತೆ (x);

	/* Use the same allocation policy here that make_node uses, to
	   ensure that this lives as long as the rest of the struct decl.
	   All decls in an inline function need to be saved.  */

	space = ((ರಚನೆ lang_type *)
		 ggc_ಆಂತರಿಕ_cleared_alloc (c_dialect_objc ()
					     ? ಗಾತ್ರ (ರಚನೆ lang_type)
					     : offsetof (ರಚನೆ lang_type,
							 info)));
	space2 = ((sorted_fields_type *)
		  ggc_ಆಂತರಿಕ_alloc (ಗಾತ್ರ (ರಚನೆ sorted_fields_type)
				      + len * ಗಾತ್ರ (ವೃಕ್ಷ)));

	len = 0;
	space->s = space2;
	ಕ್ಷೇತ್ರ_array = &space2->elts[0];
	ಗಾಗಿ (x = fieldlist; x; x = DECL_CHAIN (x))
	  {
	    ಕ್ಷೇತ್ರ_array[len++] = x;

	    /* If there is anonymous struct or union, break out of the loop.  */
	    ಆದರೆ (DECL_NAME (x) == ಖಾಲಿ)
	      ನಿಲ್ಲಿಸು;
	  }
	/* Found no anonymous struct/union.  Add the TYPE_LANG_SPECIFIC.  */
	ಆದರೆ (x == ಖಾಲಿ)
	  {
	    TYPE_LANG_SPECIFIC (t) = space;
	    TYPE_LANG_SPECIFIC (t)->s->len = len;
	    ಕ್ಷೇತ್ರ_array = TYPE_LANG_SPECIFIC (t)->s->elts;
	    qsort (ಕ್ಷೇತ್ರ_array, len, ಗಾತ್ರ (ವೃಕ್ಷ), ಕ್ಷೇತ್ರ_decl_cmp);
	  }
      }
  }

  /* If this was supposed to be a transparent union, but we can't
     make it one, warn and turn off the flag.  */
  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (t) == UNION_TYPE
      && TYPE_TRANSPARENT_AGGR (t)
      && (!TYPE_FIELDS (t) || TYPE_ಬಹುಲಕ (t) != DECL_ಬಹುಲಕ (TYPE_FIELDS (t))))
    {
      TYPE_TRANSPARENT_AGGR (t) = 0;
      warning_at (loc, 0, "union cannot be made transparent");
    }

  ವೃಕ್ಷ incomplete_vars = C_TYPE_INCOMPLETE_VARS (TYPE_MAIN_VARIANT (t));
  ಗಾಗಿ (x = TYPE_MAIN_VARIANT (t); x; x = TYPE_ಮುಂದಿನ_VARIANT (x))
    {
      TYPE_FIELDS (x) = TYPE_FIELDS (t);
      TYPE_LANG_SPECIFIC (x) = TYPE_LANG_SPECIFIC (t);
      TYPE_TRANSPARENT_AGGR (x) = TYPE_TRANSPARENT_AGGR (t);
      TYPE_TYPELESS_STORAGE (x) = TYPE_TYPELESS_STORAGE (t);
      C_TYPE_FIELDS_READONLY (x) = C_TYPE_FIELDS_READONLY (t);
      C_TYPE_FIELDS_VOLATILE (x) = C_TYPE_FIELDS_VOLATILE (t);
      C_TYPE_FIELDS_NON_CONSTEXPR (x) = C_TYPE_FIELDS_NON_CONSTEXPR (t);
      C_TYPE_FIELDS_HAS_COUNTED_BY (x) = C_TYPE_FIELDS_HAS_COUNTED_BY (t);
      C_TYPE_VARIABLE_ಗಾತ್ರ (x) = C_TYPE_VARIABLE_ಗಾತ್ರ (t);
      C_TYPE_VARIABLY_MODIFIED (x) = C_TYPE_VARIABLY_MODIFIED (t);
      C_TYPE_INCOMPLETE_VARS (x) = NULL_ವೃಕ್ಷ;
      TYPE_INCLUDES_FLEXARRAY (x) = TYPE_INCLUDES_FLEXARRAY (t);
    }

  /* Check for consistency with previous definition.  */
  ಆದರೆ (flag_isoc23 && ಖಾಲಿ != enclosing_struct_parse_info)
    {
      ವೃಕ್ಷ vistype = ಹಿಂದಿನ_ಟ್ಯಾಗ್ (t);
      ಆದರೆ (vistype
	  && ವೃಕ್ಷ_ಸಂಕೇತ (vistype) == ವೃಕ್ಷ_ಸಂಕೇತ (t)
	  && !C_TYPE_BEING_DEFINED (vistype))
	{
	  TYPE_STUB_DECL (t) = TYPE_STUB_DECL (vistype);
	  ಆದರೆ (c_type_variably_modified_p (t))
	    {
	      error ("redefinition of struct or union %qT with variably "
		     "modified type", t);
	      ಆದರೆ (struct_parse_info->refloc != UNKNOWN_LOCATION)
		inform (struct_parse_info->refloc, "originally defined here");
	    }
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!comptypes_same_p (t, vistype))
	    {
	      error ("redefinition of struct or union %qT", t);
	      ಆದರೆ (struct_parse_info->refloc != UNKNOWN_LOCATION)
		inform (struct_parse_info->refloc, "originally defined here");
	    }
	}
    }

  C_TYPE_BEING_DEFINED (t) = 0;

  ಆದರೆ (lookup_attribute ("may_alias", TYPE_ಗುಣಲಕ್ಷಣಗಳು (t)))
    ಗಾಗಿ (x = TYPE_MAIN_VARIANT (t); x; x = TYPE_ಮುಂದಿನ_VARIANT (x))
      c_fixup_may_alias (x);

  /* Set type canonical based on equivalence class.  */
  ಆದರೆ (flag_isoc23 && !C_TYPE_VARIABLE_ಗಾತ್ರ (t))
    {
      ಆದರೆ (c_struct_htab == ಖಾಲಿ)
	c_struct_htab = hash_ಕೋಷ್ಟಕ<c_struct_hasher>::create_ggc (61);

      hashval_t hash = c_struct_hasher::hash (t);

      gcc_checking_assert (TYPE_STRUCTURAL_EQUALITY_P (t));
      gcc_checking_assert (!TYPE_NAME (t)
			   || ವೃಕ್ಷ_ಸಂಕೇತ (TYPE_NAME (t)) == IDENTIFIER_ಗಂಟು);

      ವೃಕ್ಷ *e = c_struct_htab->ಕಂಡುಹಿಡಿ_ಸ್ಥಾನ_with_hash (t, hash, ಸೇರಿಸು);
      ಆದರೆ (*e)
	TYPE_CANONICAL (t) = TYPE_CANONICAL (*e);
      ಇಲ್ಲದಿದ್ದರೆ
	{
	  TYPE_CANONICAL (t) = c_type_canonical (t);
	  *e = t;
	}
      c_update_type_canonical (t);
    }

  /* Update type location to the one of the definition, instead of e.g.
     a forward declaration.  */
  ಆದರೆ (TYPE_STUB_DECL (t))
    DECL_ಮೂಲ_LOCATION (TYPE_STUB_DECL (t)) = loc;

  /* Finish debugging output for this type.  */
  rest_ದ_type_compilation (t, toplevel);

  ಮುಕ್ತಾಯ_incomplete_vars (incomplete_vars, toplevel);


  ಆದರೆ (c_type_variably_modified_p (t))
    {
      c_update_variably_modified (t);
      /* Make sure a DECL_EXPR is created for structs with VLA members.
	 Because we do not know the context, we always pass expr
	 to force creation of a BIND_EXPR which is required in some
	 contexts.  */
      ಕೂಡಿಸು_decl_ಅಭಿವ್ಯಕ್ತಿ (loc, t, ಅಭಿವ್ಯಕ್ತಿ, ಸುಳ್ಳು);
    }

  ಆದರೆ (warn_cxx_compat)
    warn_cxx_compat_ಮುಕ್ತಾಯ_struct (fieldlist, ವೃಕ್ಷ_ಸಂಕೇತ (t), loc);

  ಆದರೆ (ಖಾಲಿ != enclosing_struct_parse_info)
    {
      ಅಳಿಸು struct_parse_info;

      struct_parse_info = enclosing_struct_parse_info;

      /* If this struct is defined inside a struct, add it to
	 struct_types.  */
      ಆದರೆ (warn_cxx_compat
	  && struct_parse_info != ಖಾಲಿ
	  && !ಒಳ_sizeof && !ಒಳ_typeof && !ಒಳ_alignof && !ಒಳ_countof)
	struct_parse_info->struct_types.ಸುರಕ್ಷಿತ_ತಳ್ಳು (t);
     }

  /* Only when the enclosing struct/union type is not anonymous, do more
     verification on the fields with counted_by attributes.  */
  ಆದರೆ (C_TYPE_FIELDS_HAS_COUNTED_BY (t) && c_type_ಟ್ಯಾಗ್ (t) != NULL_ವೃಕ್ಷ)
    verify_counted_by_attribute (t, t);

  ಹಿಂತಿರುಗಿ t;
}

ಸ್ಥಿರ ರಚನೆ {
  gt_ಸೂಚಕ_operator new_ಮೌಲ್ಯ;
  ಶೂನ್ಯ *cookie;
} resort_ದತ್ತಾಂಶ;

/* This routine compares two fields like field_decl_cmp but using the
pointer operator in resort_data.  */

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ
resort_ಕ್ಷೇತ್ರ_decl_cmp (ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *x_p, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *y_p)
{
  ಸ್ಥಿರಾಂಕ ವೃಕ್ಷ *ಸ್ಥಿರಾಂಕ x = (ಸ್ಥಿರಾಂಕ ವೃಕ್ಷ *) x_p;
  ಸ್ಥಿರಾಂಕ ವೃಕ್ಷ *ಸ್ಥಿರಾಂಕ y = (ಸ್ಥಿರಾಂಕ ವೃಕ್ಷ *) y_p;

  ಆದರೆ (DECL_NAME (*x) == DECL_NAME (*y))
    /* A nontype is "greater" than a type.  */
    ಹಿಂತಿರುಗಿ (ವೃಕ್ಷ_ಸಂಕೇತ (*y) == TYPE_DECL) - (ವೃಕ್ಷ_ಸಂಕೇತ (*x) == TYPE_DECL);
  ಆದರೆ (DECL_NAME (*x) == NULL_ವೃಕ್ಷ)
    ಹಿಂತಿರುಗಿ -1;
  ಆದರೆ (DECL_NAME (*y) == NULL_ವೃಕ್ಷ)
    ಹಿಂತಿರುಗಿ 1;
  {
    ವೃಕ್ಷ d1 = DECL_NAME (*x);
    ವೃಕ್ಷ d2 = DECL_NAME (*y);
    resort_ದತ್ತಾಂಶ.new_ಮೌಲ್ಯ (&d1, &d1, resort_ದತ್ತಾಂಶ.cookie);
    resort_ದತ್ತಾಂಶ.new_ಮೌಲ್ಯ (&d2, &d2, resort_ದತ್ತಾಂಶ.cookie);
    ಆದರೆ (d1 < d2)
      ಹಿಂತಿರುಗಿ -1;
  }
  ಹಿಂತಿರುಗಿ 1;
}

/* Resort DECL_SORTED_FIELDS because pointers have been reordered.  */

ಶೂನ್ಯ
resort_sorted_fields (ಶೂನ್ಯ *obj,
		      ಶೂನ್ಯ * ARG_ಬಳಸದ (orig_obj),
		      gt_ಸೂಚಕ_operator new_ಮೌಲ್ಯ,
		      ಶೂನ್ಯ *cookie)
{
  ರಚನೆ sorted_fields_type *sf = (ರಚನೆ sorted_fields_type *) obj;
  resort_ದತ್ತಾಂಶ.new_ಮೌಲ್ಯ = new_ಮೌಲ್ಯ;
  resort_ದತ್ತಾಂಶ.cookie = cookie;
  qsort (&sf->elts[0], sf->len, ಗಾತ್ರ (ವೃಕ್ಷ),
	 resort_ಕ್ಷೇತ್ರ_decl_cmp);
}

/* Lay out the type T, and its element type, and so on.  */

ಸ್ಥಿರ ಶೂನ್ಯ
layout_array_type (ವೃಕ್ಷ t)
{
  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (t)) == ARRAY_TYPE)
    layout_array_type (ವೃಕ್ಷ_TYPE (t));
  layout_type (t);
}

/* Begin compiling the definition of an enumeration type.
   NAME is its name (or null if anonymous).
   LOC is the enum's location.
   FIXED_UNDERLYING_TYPE is the (C23) underlying type specified in the
   definition.
   Returns the type object, as yet incomplete.
   Also records info about it so that build_enumerator
   may be used to declare the individual values as they are read.  */

ವೃಕ್ಷ
ಆರಂಭ_enum (location_t loc, ರಚನೆ c_enum_contents *the_enum, ವೃಕ್ಷ name,
	    ವೃಕ್ಷ fixed_underlying_type, ತಾರ್ಕಿಕ potential_nesting_p)
{
  ವೃಕ್ಷ enumtype = NULL_ವೃಕ್ಷ;
  location_t enumloc = UNKNOWN_LOCATION;

  /* If this is the real definition for a previous forward reference,
     fill in the contents in the same object that used to be the
     forward reference.  */

  ಆದರೆ (name != NULL_ವೃಕ್ಷ)
    enumtype = lookup_ಟ್ಯಾಗ್ (ENUMERAL_TYPE, name, ನಿಜ, &enumloc);

  ಆದರೆ (enumtype != NULL_ವೃಕ್ಷ && ವೃಕ್ಷ_ಸಂಕೇತ (enumtype) == ENUMERAL_TYPE)
    {
      /* If the type is currently being defined or if we have seen an
	 incomplete version which is now complete, this is a nested
	 redefinition.  The later happens if the redefinition occurs
	 inside the enum specifier itself.  */
      ಆದರೆ (C_TYPE_BEING_DEFINED (enumtype)
	  || (potential_nesting_p && TYPE_ಮೌಲ್ಯಗಳು (enumtype) != NULL_ವೃಕ್ಷ))
	error_at (loc, "nested redefinition of %<enum %E%>", name);

      /* For C23 we allow redefinitions.  We set to zero and check for
	 consistency later.  */
      ಆದರೆ (flag_isoc23 && TYPE_ಮೌಲ್ಯಗಳು (enumtype) != NULL_ವೃಕ್ಷ)
	enumtype = NULL_ವೃಕ್ಷ;
    }

  ಆದರೆ (enumtype == NULL_ವೃಕ್ಷ || ವೃಕ್ಷ_ಸಂಕೇತ (enumtype) != ENUMERAL_TYPE)
    {
      enumtype = make_ಗಂಟು (ENUMERAL_TYPE);
      TYPE_ಗಾತ್ರ (enumtype) = NULL_ವೃಕ್ಷ;
      ಗಣ_TYPE_STRUCTURAL_EQUALITY (enumtype);
      pushtag (loc, name, enumtype);
      ಆದರೆ (fixed_underlying_type != NULL_ವೃಕ್ಷ)
	{
	  /* For an enum definition with a fixed underlying type, the
	     type is complete during the definition and the
	     enumeration constants have that type.  If there was a
	     tag, the type was completed in c_parser_enum_specifier.
	     If not, it must be completed here.  */
	  ENUM_FIXED_UNDERLYING_TYPE_P (enumtype) = ನಿಜ;
	  TYPE_MIN_ಮೌಲ್ಯ (enumtype) = TYPE_MIN_ಮೌಲ್ಯ (fixed_underlying_type);
	  TYPE_MAX_ಮೌಲ್ಯ (enumtype) = TYPE_MAX_ಮೌಲ್ಯ (fixed_underlying_type);
	  TYPE_UNSIGNED (enumtype) = TYPE_UNSIGNED (fixed_underlying_type);
	  ಗಣ_TYPE_ALIGN (enumtype, TYPE_ALIGN (fixed_underlying_type));
	  TYPE_ಗಾತ್ರ (enumtype) = NULL_ವೃಕ್ಷ;
	  TYPE_PRECISION (enumtype) = TYPE_PRECISION (fixed_underlying_type);
	  ENUM_UNDERLYING_TYPE (enumtype) = fixed_underlying_type;
	  TYPE_CANONICAL (enumtype) = TYPE_CANONICAL (fixed_underlying_type);
	  c_update_type_canonical (enumtype);
	  layout_type (enumtype);
	}
    }
  /* Update type location to the one of the definition, instead of e.g.
     a forward declaration.  */
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (TYPE_STUB_DECL (enumtype))
    {
      enumloc = DECL_ಮೂಲ_LOCATION (TYPE_STUB_DECL (enumtype));
      DECL_ಮೂಲ_LOCATION (TYPE_STUB_DECL (enumtype)) = loc;
    }

  C_TYPE_BEING_DEFINED (enumtype) = 1;

  ಆದರೆ (TYPE_ಮೌಲ್ಯಗಳು (enumtype) != NULL_ವೃಕ್ಷ)
    {
      /* This enum is a named one that has been declared already.  */
      auto_diagnostic_ಗುಂಪು d;
      error_at (loc, "redeclaration of %<enum %E%>", name);
      ಆದರೆ (enumloc != UNKNOWN_LOCATION)
	inform (enumloc, "originally defined here");

      /* Completely replace its old definition.
	 The old enumerators remain defined, however.  */
      TYPE_ಮೌಲ್ಯಗಳು (enumtype) = NULL_ವೃಕ್ಷ;
    }

  ಆದರೆ (ENUM_FIXED_UNDERLYING_TYPE_P (enumtype)
      && fixed_underlying_type == NULL_ವೃಕ್ಷ)
    {
      error_at (loc, "%<enum%> declared with but defined without "
		"fixed underlying type");
      ENUM_FIXED_UNDERLYING_TYPE_P (enumtype) = ಸುಳ್ಳು;
    }

  the_enum->enum_ಮುಂದಿನ_ಮೌಲ್ಯ = integer_zero_ಗಂಟು;
  the_enum->enum_type = enumtype;
  the_enum->enum_ಅತಿಪ್ರವಾಹ = 0;

  ಆದರೆ (flag_short_enums && !ENUM_FIXED_UNDERLYING_TYPE_P (enumtype))
    ಗಾಗಿ (ವೃಕ್ಷ v = TYPE_MAIN_VARIANT (enumtype); v; v = TYPE_ಮುಂದಿನ_VARIANT (v))
      TYPE_PACKED (v) = 1;

  /* FIXME: This will issue a warning for a use of a type defined
     within sizeof in a statement expr.  This is not terribly serious
     as C++ doesn't permit statement exprs within sizeof anyhow.  */
  ಆದರೆ (warn_cxx_compat
      && (ಒಳ_sizeof || ಒಳ_typeof || ಒಳ_alignof || ಒಳ_countof))
    warning_at (loc, OPT_Wc___compat,
		"defining type in %qs expression is invalid in C++",
		(ಒಳ_sizeof ? "sizeof"
		 : ಒಳ_typeof ? "typeof"
		 : ಒಳ_alignof ? "alignof"
		 : "_Countof"));

  ಆದರೆ (ಒಳ_underspecified_init)
    error_at (loc, "%qT defined in underspecified object initializer",
	      enumtype);

  ಹಿಂತಿರುಗಿ enumtype;
}

/* After processing and defining all the values of an enumeration type,
   install their decls in the enumeration type and finish it off.
   ENUMTYPE is the type object, VALUES a list of decl-value pairs,
   and ATTRIBUTES are the specified attributes.
   Returns ENUMTYPE.  */

ವೃಕ್ಷ
ಮುಕ್ತಾಯ_enum (ವೃಕ್ಷ enumtype, ವೃಕ್ಷ ಮೌಲ್ಯಗಳು, ವೃಕ್ಷ ಗುಣಲಕ್ಷಣಗಳು)
{
  ವೃಕ್ಷ pair, tem;
  ವೃಕ್ಷ minnode = NULL_ವೃಕ್ಷ, maxnode = NULL_ವೃಕ್ಷ;
  ಪೂರ್ಣಾಂಕ precision;
  signop sign;
  ತಾರ್ಕಿಕ toplevel = (file_scope == current_scope);
  ರಚನೆ lang_type *lt;

  decl_ಗುಣಲಕ್ಷಣಗಳು (&enumtype, ಗುಣಲಕ್ಷಣಗಳು, (ಪೂರ್ಣಾಂಕ) ATTR_FLAG_TYPE_ಒಳ_ಇರಿಸು);

  /* Calculate the maximum value of any enumerator in this type.  */

  ಆದರೆ (ಮೌಲ್ಯಗಳು == error_mark_ಗಂಟು)
    minnode = maxnode = integer_zero_ಗಂಟು;
  ಇಲ್ಲದಿದ್ದರೆ
    {
      minnode = maxnode = ವೃಕ್ಷ_ಮೌಲ್ಯ (ಮೌಲ್ಯಗಳು);
      ಗಾಗಿ (pair = ವೃಕ್ಷ_CHAIN (ಮೌಲ್ಯಗಳು); pair; pair = ವೃಕ್ಷ_CHAIN (pair))
	{
	  ವೃಕ್ಷ ಮೌಲ್ಯ = ವೃಕ್ಷ_ಮೌಲ್ಯ (pair);
	  ಆದರೆ (ವೃಕ್ಷ_int_cst_lt (maxnode, ಮೌಲ್ಯ))
	    maxnode = ಮೌಲ್ಯ;
	  ಆದರೆ (ವೃಕ್ಷ_int_cst_lt (ಮೌಲ್ಯ, minnode))
	    minnode = ಮೌಲ್ಯ;
	}
    }

  /* Construct the final type of this enumeration.  It is the same
     as one of the integral types - the narrowest one that fits, except
     that normally we only go as narrow as int - and signed iff any of
     the values are negative.  */
  sign = (ವೃಕ್ಷ_int_cst_sgn (minnode) >= 0) ? UNSIGNED : SIGNED;
  precision = MAX (ವೃಕ್ಷ_int_cst_min_precision (minnode, sign),
		   ವೃಕ್ಷ_int_cst_min_precision (maxnode, sign));

  ತಾರ್ಕಿಕ wider_than_int =
    (ವೃಕ್ಷ_int_cst_lt (minnode, TYPE_MIN_ಮೌಲ್ಯ (integer_type_ಗಂಟು))
     || ವೃಕ್ಷ_int_cst_lt (TYPE_MAX_ಮೌಲ್ಯ (integer_type_ಗಂಟು), maxnode));


  ಆದರೆ (!ENUM_FIXED_UNDERLYING_TYPE_P (enumtype))
    {
      /* If the precision of the type was specified with an attribute and it
	 was too small, give an error.  Otherwise, use it.  */
      ಆದರೆ (TYPE_PRECISION (enumtype) && lookup_attribute ("mode", ಗುಣಲಕ್ಷಣಗಳು))
	{
	  ಆದರೆ (precision > TYPE_PRECISION (enumtype))
	    {
	      TYPE_PRECISION (enumtype) = 0;
	      error ("specified mode too small for enumerated values");
	    }
	  ಇಲ್ಲದಿದ್ದರೆ
	    precision = TYPE_PRECISION (enumtype);
	}
      ಇಲ್ಲದಿದ್ದರೆ
	TYPE_PRECISION (enumtype) = 0;

      ಆದರೆ (TYPE_PACKED (enumtype)
	  || precision > TYPE_PRECISION (integer_type_ಗಂಟು)
	  || TYPE_PRECISION (enumtype))
	{
	  tem = c_common_type_for_ಗಾತ್ರ (precision, sign == UNSIGNED ? 1 : 0);
	  ಆದರೆ (tem == ಖಾಲಿ)
	    {
	      /* This should only occur when both signed and unsigned
		 values of maximum precision occur among the
		 enumerators.  */
	      pedwarn (ಒಳಹರಿವು_location, 0,
		       "enumeration values exceed range of largest integer");
	      tem = widest_integer_literal_type_ಗಂಟು;
	    }
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (precision > TYPE_PRECISION (intmax_type_ಗಂಟು)
		   && !ವೃಕ್ಷ_int_cst_lt (minnode,
					TYPE_MIN_ಮೌಲ್ಯ (intmax_type_ಗಂಟು))
		   && !ವೃಕ್ಷ_int_cst_lt (TYPE_MAX_ಮೌಲ್ಯ (uintmax_type_ಗಂಟು),
					maxnode))
	    pedwarn (ಒಳಹರಿವು_location, OPT_Wpedantic,
		     "enumeration values exceed range of %qs",
		     sign == UNSIGNED ? "uintmax_t" : "intmax_t");
	}
      ಇಲ್ಲದಿದ್ದರೆ
	tem = sign == UNSIGNED ? unsigned_type_ಗಂಟು : integer_type_ಗಂಟು;

      TYPE_MIN_ಮೌಲ್ಯ (enumtype) = TYPE_MIN_ಮೌಲ್ಯ (tem);
      TYPE_MAX_ಮೌಲ್ಯ (enumtype) = TYPE_MAX_ಮೌಲ್ಯ (tem);
      TYPE_UNSIGNED (enumtype) = TYPE_UNSIGNED (tem);
      ಗಣ_TYPE_ALIGN (enumtype, TYPE_ALIGN (tem));
      TYPE_ಗಾತ್ರ (enumtype) = NULL_ವೃಕ್ಷ;
      TYPE_PRECISION (enumtype) = TYPE_PRECISION (tem);
      ENUM_UNDERLYING_TYPE (enumtype) =
	c_common_type_for_ಗಾತ್ರ (TYPE_PRECISION (tem), TYPE_UNSIGNED (tem));

      TYPE_CANONICAL (enumtype) =
	TYPE_CANONICAL (ENUM_UNDERLYING_TYPE (enumtype));
      c_update_type_canonical (enumtype);

      layout_type (enumtype);
    }

  ಆದರೆ (ಮೌಲ್ಯಗಳು != error_mark_ಗಂಟು)
    {
      /* Change the type of the enumerators to be the enum type.  We
	 need to do this irrespective of the size of the enum, for
	 proper type checking.  Replace the DECL_INITIALs of the
	 enumerators, and the value slots of the list, with copies
	 that have the enum type; they cannot be modified in place
	 because they may be shared (e.g.  integer_zero_node) Finally,
	 change the purpose slots to point to the names of the decls.  */
      ಗಾಗಿ (pair = ಮೌಲ್ಯಗಳು; pair; pair = ವೃಕ್ಷ_CHAIN (pair))
	{
	  ವೃಕ್ಷ enu = ವೃಕ್ಷ_PURPOSE (pair);
	  ವೃಕ್ಷ ini = DECL_INITIAL (enu);

	  ವೃಕ್ಷ_TYPE (enu) = enumtype;

	  /* Before C23, the ISO C Standard mandates enumerators to
	     have type int, even though the underlying type of an enum
	     type is unspecified.  However, C23 allows enumerators of
	     any integer type, and if an enumeration has any
	     enumerators wider than int, all enumerators have the
	     enumerated type after it is parsed.  Any enumerators that
	     fit in int are given type int in build_enumerator (which
	     is the correct type while the enumeration is being
	     parsed), so no conversions are needed here if all
	     enumerators fit in int.  If the enum has a fixed
	     underlying type, the correct type was also given in
	     build_enumerator.  */
	  ಆದರೆ (!ENUM_FIXED_UNDERLYING_TYPE_P (enumtype) && wider_than_int)
	    ini = convert (enumtype, ini);

	  DECL_INITIAL (enu) = ini;
	  ವೃಕ್ಷ_PURPOSE (pair) = DECL_NAME (enu);
	  /* To match the C++ FE, store the CONST_DECL rather than just its
	     value.  */
	  ವೃಕ್ಷ_ಮೌಲ್ಯ (pair) = enu;
	}

      TYPE_ಮೌಲ್ಯಗಳು (enumtype) = ಮೌಲ್ಯಗಳು;
    }

  /* Record the min/max values so that we can warn about bit-field
     enumerations that are too small for the values.  */
  lt = ((ರಚನೆ lang_type *)
	ggc_ಆಂತರಿಕ_cleared_alloc (c_dialect_objc ()
				    ? ಗಾತ್ರ (ರಚನೆ lang_type)
				    : offsetof (ರಚನೆ lang_type, info)));
  lt->enum_min = minnode;
  lt->enum_max = maxnode;
  TYPE_LANG_SPECIFIC (enumtype) = lt;

  /* Fix up all variant types of this enum type.  */
  ವೃಕ್ಷ incomplete_vars = C_TYPE_INCOMPLETE_VARS (TYPE_MAIN_VARIANT (enumtype));
  ಗಾಗಿ (tem = TYPE_MAIN_VARIANT (enumtype); tem; tem = TYPE_ಮುಂದಿನ_VARIANT (tem))
    {
      C_TYPE_INCOMPLETE_VARS (tem) = NULL_ವೃಕ್ಷ;
      ಆದರೆ (tem == enumtype)
	ಮುಂದುವರಿ;
      TYPE_ಮೌಲ್ಯಗಳು (tem) = TYPE_ಮೌಲ್ಯಗಳು (enumtype);
      TYPE_MIN_ಮೌಲ್ಯ (tem) = TYPE_MIN_ಮೌಲ್ಯ (enumtype);
      TYPE_MAX_ಮೌಲ್ಯ (tem) = TYPE_MAX_ಮೌಲ್ಯ (enumtype);
      TYPE_ಗಾತ್ರ (tem) = TYPE_ಗಾತ್ರ (enumtype);
      TYPE_ಗಾತ್ರ_UNIT (tem) = TYPE_ಗಾತ್ರ_UNIT (enumtype);
      ಗಣ_TYPE_ಬಹುಲಕ (tem, TYPE_ಬಹುಲಕ (enumtype));
      TYPE_PRECISION (tem) = TYPE_PRECISION (enumtype);
      ಗಣ_TYPE_ALIGN (tem, TYPE_ALIGN (enumtype));
      TYPE_USER_ALIGN (tem) = TYPE_USER_ALIGN (enumtype);
      TYPE_UNSIGNED (tem) = TYPE_UNSIGNED (enumtype);
      TYPE_LANG_SPECIFIC (tem) = TYPE_LANG_SPECIFIC (enumtype);
      ENUM_UNDERLYING_TYPE (tem) = ENUM_UNDERLYING_TYPE (enumtype);
      TYPE_PACKED (tem) = TYPE_PACKED (enumtype);
    }

  /* Finish debugging output for this type.  */
  rest_ದ_type_compilation (enumtype, toplevel);

  ಮುಕ್ತಾಯ_incomplete_vars (incomplete_vars, toplevel);

  /* If this enum is defined inside a struct, add it to
     struct_types.  */
  ಆದರೆ (warn_cxx_compat
      && struct_parse_info != ಖಾಲಿ
      && !ಒಳ_sizeof && !ಒಳ_typeof && !ಒಳ_alignof && !ಒಳ_countof)
    struct_parse_info->struct_types.ಸುರಕ್ಷಿತ_ತಳ್ಳು (enumtype);

  /* Check for consistency with previous definition */
  ಆದರೆ (flag_isoc23)
    {
      ವೃಕ್ಷ vistype = ಹಿಂದಿನ_ಟ್ಯಾಗ್ (enumtype);
      ಆದರೆ (vistype
	  && ವೃಕ್ಷ_ಸಂಕೇತ (vistype) == ವೃಕ್ಷ_ಸಂಕೇತ (enumtype)
	  && !C_TYPE_BEING_DEFINED (vistype))
	{
	  TYPE_STUB_DECL (enumtype) = TYPE_STUB_DECL (vistype);
	  ಆದರೆ (!comptypes_same_p (enumtype, vistype))
	    error("conflicting redefinition of enum %qT", enumtype);
	}
    }

  C_TYPE_BEING_DEFINED (enumtype) = 0;

  ಹಿಂತಿರುಗಿ enumtype;
}

/* Build and install a CONST_DECL for one value of the
   current enumeration type (one that was begun with start_enum).
   DECL_LOC is the location of the enumerator.
   LOC is the location of the '=' operator if any, DECL_LOC otherwise.
   Return a tree-list containing the CONST_DECL and its value.
   Assignment of sequential values by default is handled here.  */

ವೃಕ್ಷ
build_enumerator (location_t decl_loc, location_t loc,
		  ರಚನೆ c_enum_contents *the_enum, ವೃಕ್ಷ name, ವೃಕ್ಷ ಮೌಲ್ಯ)
{
  ವೃಕ್ಷ decl;
  ವೃಕ್ಷ old_decl;

  /* Validate and default VALUE.  */

  ಆದರೆ (ಮೌಲ್ಯ != NULL_ವೃಕ್ಷ)
    {
      /* Don't issue more errors for error_mark_node (i.e. an
	 undeclared identifier) - just ignore the value expression.  */
      ಆದರೆ (ಮೌಲ್ಯ == error_mark_ಗಂಟು)
	ಮೌಲ್ಯ = NULL_ವೃಕ್ಷ;
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!INTEGRAL_TYPE_P (ವೃಕ್ಷ_TYPE (ಮೌಲ್ಯ)))
	{
	  error_at (loc, "enumerator value for %qE is not an integer constant",
		    name);
	  ಮೌಲ್ಯ = NULL_ವೃಕ್ಷ;
	}
      ಇಲ್ಲದಿದ್ದರೆ
	{
	  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ಮೌಲ್ಯ) != INTEGER_CST)
	    {
	      ಮೌಲ್ಯ = c_fully_fold (ಮೌಲ್ಯ, ಸುಳ್ಳು, ಖಾಲಿ);
	      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ಮೌಲ್ಯ) == INTEGER_CST)
		pedwarn (loc, OPT_Wpedantic,
			 "enumerator value for %qE is not an integer "
			 "constant expression", name);
	    }
	  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ಮೌಲ್ಯ) != INTEGER_CST)
	    {
	      error ("enumerator value for %qE is not an integer constant",
		     name);
	      ಮೌಲ್ಯ = NULL_ವೃಕ್ಷ;
	    }
	  ಇಲ್ಲದಿದ್ದರೆ
	    {
	      ಮೌಲ್ಯ = default_conversion (ಮೌಲ್ಯ);
	      constant_ಅಭಿವ್ಯಕ್ತಿ_warning (ಮೌಲ್ಯ);
	    }
	}
    }

  /* Default based on previous value.  */
  /* It should no longer be possible to have NON_LVALUE_EXPR
     in the default.  */
  ಆದರೆ (ಮೌಲ್ಯ == NULL_ವೃಕ್ಷ)
    {
      ಮೌಲ್ಯ = the_enum->enum_ಮುಂದಿನ_ಮೌಲ್ಯ;
      ಆದರೆ (the_enum->enum_ಅತಿಪ್ರವಾಹ)
	error_at (loc, "overflow in enumeration values");
    }
  ಆದರೆ (ENUM_FIXED_UNDERLYING_TYPE_P (the_enum->enum_type))
    {
      /* Enumeration constants must fit in the fixed underlying type.  */
      ಆದರೆ (!int_ಹೊಂದುತ್ತದೆ_type_p (ಮೌಲ್ಯ, ENUM_UNDERLYING_TYPE (the_enum->enum_type)))
	error_at (loc,
		  "enumerator value outside the range of underlying type");
      /* Enumeration constants for an enum with fixed underlying type
	 have the enum type, both inside and outside the
	 definition.  */
      ಮೌಲ್ಯ = convert (the_enum->enum_type, ಮೌಲ್ಯ);
    }
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (flag_isoc23
	   && (old_decl = lookup_name_ಒಳ_scope (name, current_scope))
	   && old_decl != error_mark_ಗಂಟು
	   && ವೃಕ್ಷ_TYPE (old_decl)
	   && ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_TYPE (old_decl))
	   && ವೃಕ್ಷ_ಸಂಕೇತ (old_decl) == CONST_DECL)
    {
      /* Enumeration constants in a redeclaration have the previous type.  */
      ವೃಕ್ಷ ಹಿಂದಿನ_type = ವೃಕ್ಷ_TYPE (DECL_INITIAL (old_decl));
      ಆದರೆ (!int_ಹೊಂದುತ್ತದೆ_type_p (ಮೌಲ್ಯ, ಹಿಂದಿನ_type))
	{
	  error_at (loc, "value of redeclared enumerator outside the range "
			 "of %qT", ಹಿಂದಿನ_type);
	  locate_old_decl (old_decl);
	}
      ಮೌಲ್ಯ = convert (ಹಿಂದಿನ_type, ಮೌಲ್ಯ);
    }
  ಇಲ್ಲದಿದ್ದರೆ
    {
      /* Even though the underlying type of an enum is unspecified, the
	 type of enumeration constants is explicitly defined as int
	 (6.4.4.3/2 in the C99 Standard).  C23 allows any integer type, and
	 GCC allows such types for older standards as an extension.  */
      ತಾರ್ಕಿಕ warned_range = ಸುಳ್ಳು;
      ಆದರೆ (!int_ಹೊಂದುತ್ತದೆ_type_p (ಮೌಲ್ಯ,
			    (TYPE_UNSIGNED (ವೃಕ್ಷ_TYPE (ಮೌಲ್ಯ))
			     ? uintmax_type_ಗಂಟು
			     : intmax_type_ಗಂಟು)))
	/* GCC does not consider its types larger than intmax_t to be
	   extended integer types (although C23 would permit such types to
	   be considered extended integer types if all the features
	   required by <stdint.h> and <inttypes.h> macros, such as support
	   for integer constants and I/O, were present), so diagnose if
	   such a wider type is used.  (If the wider type arose from a
	   constant of such a type, that will also have been diagnosed,
	   but this is the only diagnostic in the case where it arises
	   from choosing a wider type automatically when adding 1
	   overflows.)  */
	warned_range = pedwarn (loc, OPT_Wpedantic,
				"enumerator value outside the range of %qs",
				TYPE_UNSIGNED (ವೃಕ್ಷ_TYPE (ಮೌಲ್ಯ))
				? "uintmax_t"
				: "intmax_t");
      ಆದರೆ (!warned_range && !int_ಹೊಂದುತ್ತದೆ_type_p (ಮೌಲ್ಯ, integer_type_ಗಂಟು))
	pedwarn_c11 (loc, OPT_Wpedantic,
		     "ISO C restricts enumerator values to range of %<int%> "
		     "before C23");

      /* The ISO C Standard mandates enumerators to have type int before
	 C23, even though the underlying type of an enum type is
	 unspecified.  C23 allows enumerators of any integer type.  During
	 the parsing of the enumeration, C23 specifies that constants
	 representable in int have type int, constants not representable
	 in int have the type of the given expression if any, and
	 constants not representable in int and derived by adding 1 to the
	 previous constant have the type of that constant unless the
	 addition would overflow or wraparound, in which case a wider type
	 of the same signedness is chosen automatically; after the
	 enumeration is parsed, all the constants have the type of the
	 enumeration if any do not fit in int.  */
      ಆದರೆ (int_ಹೊಂದುತ್ತದೆ_type_p (ಮೌಲ್ಯ, integer_type_ಗಂಟು))
	ಮೌಲ್ಯ = convert (integer_type_ಗಂಟು, ಮೌಲ್ಯ);
    }

  /* Set basis for default for next value.  */
  ಆದರೆ (ENUM_FIXED_UNDERLYING_TYPE_P (the_enum->enum_type))
    {
      ವೃಕ್ಷ underlying_type = ENUM_UNDERLYING_TYPE (the_enum->enum_type);
      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (underlying_type) == BOOLEAN_TYPE)
	/* A value of 2 following a value of 1 overflows bool, but we
	   cannot carry out addition directly on bool without
	   promotion, and converting the result of arithmetic in a
	   wider type back to bool would not produce the right result
	   for this overflow check.  */
	the_enum->enum_ಮುಂದಿನ_ಮೌಲ್ಯ = invert_truthvalue_loc (loc, ಮೌಲ್ಯ);
      ಇಲ್ಲದಿದ್ದರೆ
	the_enum->enum_ಮುಂದಿನ_ಮೌಲ್ಯ
	  = build_ದ್ವಿಮಾನ_op (ಅಭಿವ್ಯಕ್ತಿ_LOC_OR_LOC (ಮೌಲ್ಯ, ಒಳಹರಿವು_location),
			     PLUS_ಅಭಿವ್ಯಕ್ತಿ, convert (underlying_type, ಮೌಲ್ಯ),
			     convert (underlying_type, integer_one_ಗಂಟು),
			     ಸುಳ್ಳು);
    }
  ಇಲ್ಲದಿದ್ದರೆ
    {
      /* In a redeclaration the type can already be the enumeral type.  */
      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (ಮೌಲ್ಯ)) == ENUMERAL_TYPE)
	ಮೌಲ್ಯ = convert (ENUM_UNDERLYING_TYPE (ವೃಕ್ಷ_TYPE (ಮೌಲ್ಯ)), ಮೌಲ್ಯ);
      the_enum->enum_ಮುಂದಿನ_ಮೌಲ್ಯ
	= build_ದ್ವಿಮಾನ_op (ಅಭಿವ್ಯಕ್ತಿ_LOC_OR_LOC (ಮೌಲ್ಯ, ಒಳಹರಿವು_location),
			   PLUS_ಅಭಿವ್ಯಕ್ತಿ, ಮೌಲ್ಯ, integer_one_ಗಂಟು, ಸುಳ್ಳು);
    }
  the_enum->enum_ಅತಿಪ್ರವಾಹ = ವೃಕ್ಷ_int_cst_lt (the_enum->enum_ಮುಂದಿನ_ಮೌಲ್ಯ, ಮೌಲ್ಯ);
  ಆದರೆ (the_enum->enum_ಅತಿಪ್ರವಾಹ
      && !ENUM_FIXED_UNDERLYING_TYPE_P (the_enum->enum_type))
    {
      /* Choose a wider type with the same signedness if
	 available.  */
      ಪೂರ್ಣಾಂಕ prec = TYPE_PRECISION (ವೃಕ್ಷ_TYPE (ಮೌಲ್ಯ)) + 1;
      ತಾರ್ಕಿಕ unsignedp = TYPE_UNSIGNED (ವೃಕ್ಷ_TYPE (ಮೌಲ್ಯ));
      ವೃಕ್ಷ new_type = (unsignedp
		       ? long_unsigned_type_ಗಂಟು
		       : long_integer_type_ಗಂಟು);
      ಆದರೆ (prec > TYPE_PRECISION (new_type))
	new_type = (unsignedp
		    ? long_long_unsigned_type_ಗಂಟು
		    : long_long_integer_type_ಗಂಟು);
      ಆದರೆ (prec > TYPE_PRECISION (new_type))
	new_type = (unsignedp
		    ? widest_unsigned_literal_type_ಗಂಟು
		    : widest_integer_literal_type_ಗಂಟು);
      ಆದರೆ (prec <= TYPE_PRECISION (new_type))
	{
	  the_enum->enum_ಅತಿಪ್ರವಾಹ = ಸುಳ್ಳು;
	  the_enum->enum_ಮುಂದಿನ_ಮೌಲ್ಯ
	    = build_ದ್ವಿಮಾನ_op (ಅಭಿವ್ಯಕ್ತಿ_LOC_OR_LOC (ಮೌಲ್ಯ, ಒಳಹರಿವು_location),
			       PLUS_ಅಭಿವ್ಯಕ್ತಿ, convert (new_type, ಮೌಲ್ಯ),
			       integer_one_ಗಂಟು, ಸುಳ್ಳು);
	  gcc_assert (!ವೃಕ್ಷ_int_cst_lt (the_enum->enum_ಮುಂದಿನ_ಮೌಲ್ಯ, ಮೌಲ್ಯ));
	}
    }

  /* Now create a declaration for the enum value name.  */

  decl = build_decl (decl_loc, CONST_DECL, name, ವೃಕ್ಷ_TYPE (ಮೌಲ್ಯ));
  DECL_INITIAL (decl) = ಮೌಲ್ಯ;
  DECL_CONTEXT (decl) = the_enum->enum_type;
  pushdecl (decl);

  ಹಿಂತಿರುಗಿ ವೃಕ್ಷ_cons (decl, ಮೌಲ್ಯ, NULL_ವೃಕ್ಷ);
}

/* Implement LANG_HOOKS_SIMULATE_ENUM_DECL.  */

ವೃಕ್ಷ
c_simulate_enum_decl (location_t loc, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name,
		      vec<string_int_pair> *ಮೌಲ್ಯಗಳು_ptr)
{
  location_t saved_loc = ಒಳಹರಿವು_location;
  ಒಳಹರಿವು_location = loc;

  ರಚನೆ c_enum_contents the_enum;
  ವೃಕ್ಷ enumtype = ಆರಂಭ_enum (loc, &the_enum, get_identifier (name),
			      NULL_ವೃಕ್ಷ, ಸುಳ್ಳು);

  ವೃಕ್ಷ ಮೌಲ್ಯ_chain = NULL_ವೃಕ್ಷ;
  string_int_pair *ಮೌಲ್ಯ;
  vec<string_int_pair> ಮೌಲ್ಯಗಳು = *ಮೌಲ್ಯಗಳು_ptr;
  ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ i;
  FOR_EACH_VEC_ELT (ಮೌಲ್ಯಗಳು, i, ಮೌಲ್ಯ)
    {
      ವೃಕ್ಷ decl = build_enumerator (loc, loc, &the_enum,
				    get_identifier (ಮೌಲ್ಯ->ಮೊದಲ),
				    build_int_cst (integer_type_ಗಂಟು,
						   ಮೌಲ್ಯ->ಎರಡನೇ));
      ವೃಕ್ಷ_CHAIN (decl) = ಮೌಲ್ಯ_chain;
      ಮೌಲ್ಯ_chain = decl;
    }

  ಮುಕ್ತಾಯ_enum (enumtype, nreverse (ಮೌಲ್ಯ_chain), NULL_ವೃಕ್ಷ);

  ಒಳಹರಿವು_location = saved_loc;
  ಹಿಂತಿರುಗಿ enumtype;
}

/* Implement LANG_HOOKS_SIMULATE_RECORD_DECL.  */

ವೃಕ್ಷ
c_simulate_ದಾಖಲೆ_decl (location_t loc, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name,
			array_ತುಂಡು<ಸ್ಥಿರಾಂಕ ವೃಕ್ಷ> fields)
{
  location_t saved_loc = ಒಳಹರಿವು_location;
  ಒಳಹರಿವು_location = loc;

  ವರ್ಗ c_struct_parse_info *struct_info;
  ವೃಕ್ಷ ident = get_identifier (name);
  ವೃಕ್ಷ type = ಆರಂಭ_struct (loc, ದಾಖಲೆ_TYPE, ident, &struct_info);

  ಗಾಗಿ (ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ i = 0; i < fields.ಗಾತ್ರ_2 (); ++i)
    {
      DECL_ಕ್ಷೇತ್ರ_CONTEXT (fields[i]) = type;
      ಆದರೆ (i > 0)
	DECL_CHAIN (fields[i - 1]) = fields[i];
    }

  ಮುಕ್ತಾಯ_struct (loc, type, fields[0], NULL_ವೃಕ್ಷ, struct_info);

  ವೃಕ್ಷ decl = build_decl (loc, TYPE_DECL, ident, type);
  ಗಣ_underlying_type (decl);
  lang_hooks.decls.pushdecl (decl);

  ಒಳಹರಿವು_location = saved_loc;
  ಹಿಂತಿರುಗಿ type;
}

/* Create the FUNCTION_DECL for a function definition.
   DECLSPECS, DECLARATOR and ATTRIBUTES are the parts of
   the declaration; they describe the function's name and the type it returns,
   but twisted together in a fashion that parallels the syntax of C.

   This function creates a binding context for the function body
   as well as setting up the FUNCTION_DECL in current_function_decl.

   Returns true on success.  If the DECLARATOR is not suitable for a function
   (it defines a datum instead), we return false to report a parse error.  */

ತಾರ್ಕಿಕ
ಆರಂಭ_function (ರಚನೆ c_declspecs *declspecs, ರಚನೆ c_declarator *declarator,
		ವೃಕ್ಷ ಗುಣಲಕ್ಷಣಗಳು)
{
  ವೃಕ್ಷ decl1, old_decl;
  ವೃಕ್ಷ restype, resdecl;
  location_t loc;
  location_t ಫಲಿತಾಂಶ_loc;
  ವೃಕ್ಷ ಅಭಿವ್ಯಕ್ತಿ = ಖಾಲಿ;

  current_function_returns_ಮೌಲ್ಯ = 0;  /* Assume, until we see it does.  */
  current_function_returns_null = 0;
  current_function_returns_abnormally = 0;
  warn_about_return_type = 0;
  c_switch_ರಾಶಿ = ಖಾಲಿ;

  /* Indicate no valid break/continue context.  */
  ಒಳ_statement = 0;

  decl1 = grokdeclarator (declarator, declspecs, FUNCDEF, ನಿಜ, ಖಾಲಿ,
			  &ಗುಣಲಕ್ಷಣಗಳು, &ಅಭಿವ್ಯಕ್ತಿ, ಖಾಲಿ, DEPRECATED_ಸಾಮಾನ್ಯ);
  invoke_plugin_callbacks (PLUGIN_ಆರಂಭ_PARSE_FUNCTION, decl1);

  /* If the declarator is not suitable for a function definition,
     cause a syntax error.  */
  ಆದರೆ (decl1 == NULL_ವೃಕ್ಷ
      || ವೃಕ್ಷ_ಸಂಕೇತ (decl1) != FUNCTION_DECL)
    ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;

  /* Nested functions may have variably modified (return) type.
     Make sure the size expression is evaluated at this point.  */
  ಆದರೆ (ಅಭಿವ್ಯಕ್ತಿ && !current_scope->parm_flag)
    ಕೂಡಿಸು_stmt (fold_convert (void_type_ಗಂಟು, ಅಭಿವ್ಯಕ್ತಿ));

  loc = DECL_ಮೂಲ_LOCATION (decl1);

  /* A nested function is not global.  */
  ಆದರೆ (current_function_decl != NULL_ವೃಕ್ಷ)
    ವೃಕ್ಷ_ಬಹಿರಂಗ (decl1) = 0;

  c_decl_ಗುಣಲಕ್ಷಣಗಳು (&decl1, ಗುಣಲಕ್ಷಣಗಳು, 0);

  ಆದರೆ (DECL_DECLARED_INLINE_P (decl1)
      && DECL_UNINLINABLE (decl1)
      && lookup_attribute ("noinline", DECL_ಗುಣಲಕ್ಷಣಗಳು (decl1)))
    {
      auto_urlify_ಗುಣಲಕ್ಷಣಗಳು sentinel;
      warning_at (loc, OPT_Wattributes,
		  "inline function %qD given attribute %qs",
		  decl1, "noinline");
    }

  /* Handle gnu_inline attribute.  */
  ಆದರೆ (declspecs->inline_p
      && !flag_gnu89_inline
      && ವೃಕ್ಷ_ಸಂಕೇತ (decl1) == FUNCTION_DECL
      && (lookup_attribute ("gnu_inline", DECL_ಗುಣಲಕ್ಷಣಗಳು (decl1))
	  || current_function_decl))
    {
      ಆದರೆ (declspecs->storage_class != csc_static)
	DECL_EXTERNAL (decl1) = !DECL_EXTERNAL (decl1);
    }

  announce_function (decl1);

  ಆದರೆ (!COMPLETE_OR_VOID_TYPE_P (ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_TYPE (decl1))))
    {
      error_at (loc, "return type is an incomplete type");
      /* Make it return void instead.  */
      ವೃಕ್ಷ_TYPE (decl1)
	= c_build_function_type (void_type_ಗಂಟು,
				 TYPE_ARG_TYPES (ವೃಕ್ಷ_TYPE (decl1)),
				 TYPE_NO_NAMED_ವಾದಗಳು_STDARG_P (ವೃಕ್ಷ_TYPE (decl1)));
    }

  ಆದರೆ (warn_about_return_type)
    permerror_opt (loc, flag_isoc99 ? OPT_Wimplicit_int
		   : (warn_return_type > 0 ? OPT_Wreturn_type
		      : OPT_Wimplicit_int),
		   "return type defaults to %<int%>");

  /* Make the init_value nonzero so pushdecl knows this is not tentative.
     error_mark_node is replaced below (in pop_scope) with the BLOCK.  */
  DECL_INITIAL (decl1) = error_mark_ಗಂಟು;

  /* If this definition isn't a prototype and we had a prototype declaration
     before, copy the arg type info from that prototype.  */
  old_decl = lookup_name_ಒಳ_scope (DECL_NAME (decl1), current_scope);
  ಆದರೆ (old_decl && ವೃಕ್ಷ_ಸಂಕೇತ (old_decl) != FUNCTION_DECL)
    old_decl = NULL_ವೃಕ್ಷ;

  current_function_prototype_locus = UNKNOWN_LOCATION;
  current_function_prototype_built_ಒಳ = ಸುಳ್ಳು;
  current_function_prototype_arg_types = NULL_ವೃಕ್ಷ;
  ವೃಕ್ಷ newtype = ವೃಕ್ಷ_TYPE (decl1);
  ವೃಕ್ಷ oldtype = old_decl ? ವೃಕ್ಷ_TYPE (old_decl) : newtype;
  ಆದರೆ (!prototype_p (newtype))
    {
      ವೃಕ್ಷ oldrt = ವೃಕ್ಷ_TYPE (oldtype);
      ವೃಕ್ಷ newrt = ವೃಕ್ಷ_TYPE (newtype);
      ಆದರೆ (old_decl != NULL_ವೃಕ್ಷ
	  && ವೃಕ್ಷ_ಸಂಕೇತ (oldtype) == FUNCTION_TYPE
	  && comptypes (oldrt, newrt)
	  && !TYPE_NO_NAMED_ವಾದಗಳು_STDARG_P (oldtype))
	{
	  ಆದರೆ (stdarg_p (oldtype))
	    {
	      auto_diagnostic_ಗುಂಪು d;
	      warning_at (loc, 0, "%q+D defined as variadic function "
			  "without prototype", decl1);
	      locate_old_decl (old_decl);
	    }
	  ವೃಕ್ಷ_TYPE (decl1) = ಸಂಯುಕ್ತ_type (oldtype, newtype);
	  current_function_prototype_locus = DECL_ಮೂಲ_LOCATION (old_decl);
	  current_function_prototype_built_ಒಳ
	    = C_DECL_BUILTIN_PROTOTYPE (old_decl);
	  current_function_prototype_arg_types
	    = TYPE_ARG_TYPES (newtype);
	}
      ಆದರೆ (ವೃಕ್ಷ_ಬಹಿರಂಗ (decl1))
	{
	  /* If there is an external prototype declaration of this
	     function, record its location but do not copy information
	     to this decl.  This may be an invisible declaration
	     (built-in or in a scope which has finished) or simply
	     have more refined argument types than any declaration
	     found above.  */
	  ರಚನೆ c_binding *b;
	  ಗಾಗಿ (b = I_ಚಿಹ್ನೆ_BINDING (DECL_NAME (decl1)); b; b = b->shadowed)
	    ಆದರೆ (B_ಒಳ_SCOPE (b, external_scope))
	      ನಿಲ್ಲಿಸು;
	  ಆದರೆ (b)
	    {
	      ವೃಕ್ಷ ext_decl, ext_type;
	      ext_decl = b->decl;
	      ext_type = b->u.type ? b->u.type : ವೃಕ್ಷ_TYPE (ext_decl);
	      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ext_type) == FUNCTION_TYPE
		  && comptypes (ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_TYPE (decl1)),
				ವೃಕ್ಷ_TYPE (ext_type)))
		{
		  current_function_prototype_locus
		    = DECL_ಮೂಲ_LOCATION (ext_decl);
		  current_function_prototype_built_ಒಳ
		    = C_DECL_BUILTIN_PROTOTYPE (ext_decl);
		  current_function_prototype_arg_types
		    = TYPE_ARG_TYPES (ext_type);
		}
	    }
	}
    }

  /* Optionally warn about C23 compatibility.  */
  ಆದರೆ (warn_deprecated_non_prototype
      && old_decl != NULL_ವೃಕ್ಷ
      && ವೃಕ್ಷ_ಸಂಕೇತ (oldtype) == FUNCTION_TYPE
      && !TYPE_ARG_TYPES (oldtype)
      && !TYPE_NO_NAMED_ವಾದಗಳು_STDARG_P (oldtype)
      && (TYPE_ARG_TYPES (newtype)
	  && ವೃಕ್ಷ_ಮೌಲ್ಯ (TYPE_ARG_TYPES (newtype)) != void_type_ಗಂಟು))
    {
      ತಾರ್ಕಿಕ warned = warning_at (loc, OPT_Wdeprecated_non_prototype,
				"ISO C23 does not allow defining"
				" parameters for function %qE declared"
				" without parameters",
				decl1);
      ಆದರೆ (warned)
	inform (DECL_ಮೂಲ_LOCATION (old_decl), "declared here");
    }

  /* Optionally warn of old-fashioned def with no previous prototype.  */
  ಆದರೆ (warn_strict_prototypes
      && old_decl != error_mark_ಗಂಟು
      && !prototype_p (ವೃಕ್ಷ_TYPE (decl1))
      && C_DECL_ISNT_PROTOTYPE (old_decl))
    warning_at (loc, OPT_Wstrict_prototypes,
		"function declaration isn%'t a prototype");
  /* Optionally warn of any global def with no previous prototype.  */
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (warn_missing_prototypes
	   && old_decl != error_mark_ಗಂಟು
	   && ವೃಕ್ಷ_ಬಹಿರಂಗ (decl1)
	   && !MAIN_NAME_P (DECL_NAME (decl1))
	   && C_DECL_ISNT_PROTOTYPE (old_decl)
	   && !DECL_DECLARED_INLINE_P (decl1))
    warning_at (loc, OPT_Wmissing_prototypes,
		"no previous prototype for %qD", decl1);
  /* Optionally warn of any def with no previous prototype
     if the function has already been used.  */
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (warn_missing_prototypes
	   && old_decl != NULL_ವೃಕ್ಷ
	   && old_decl != error_mark_ಗಂಟು
	   && ವೃಕ್ಷ_ಬಳಸಿದ (old_decl)
	   && !prototype_p (ವೃಕ್ಷ_TYPE (old_decl)))
    warning_at (loc, OPT_Wmissing_prototypes,
		"%qD was used with no prototype before its definition", decl1);
  /* Optionally warn of any global def with no previous declaration.  */
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (warn_missing_declarations
	   && ವೃಕ್ಷ_ಬಹಿರಂಗ (decl1)
	   && old_decl == NULL_ವೃಕ್ಷ
	   && !MAIN_NAME_P (DECL_NAME (decl1))
	   && !DECL_DECLARED_INLINE_P (decl1))
    warning_at (loc, OPT_Wmissing_declarations,
		"no previous declaration for %qD",
		decl1);
  /* Optionally warn of any def with no previous declaration
     if the function has already been used.  */
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (warn_missing_declarations
	   && old_decl != NULL_ವೃಕ್ಷ
	   && old_decl != error_mark_ಗಂಟು
	   && ವೃಕ್ಷ_ಬಳಸಿದ (old_decl)
	   && C_DECL_IMPLICIT (old_decl))
    warning_at (loc, OPT_Wmissing_declarations,
		"%qD was used with no declaration before its definition", decl1);

  /* This function exists in static storage.
     (This does not mean `static' in the C sense!)  */
  ವೃಕ್ಷ_STATIC (decl1) = 1;

  /* This is the earliest point at which we might know the assembler
     name of the function.  Thus, if it's set before this, die horribly.  */
  gcc_assert (!DECL_ASSEMBLER_NAME_ಗಣ_P (decl1));

  /* If #pragma weak was used, mark the decl weak now.  */
  ಆದರೆ (current_scope == file_scope)
    maybe_apply_pragma_weak (decl1);

  /* Warn for unlikely, improbable, or stupid declarations of `main'.  */
  ಆದರೆ (warn_main && MAIN_NAME_P (DECL_NAME (decl1)))
    {
      ಆದರೆ (TYPE_MAIN_VARIANT (ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_TYPE (decl1)))
	  != integer_type_ಗಂಟು)
	pedwarn (loc, OPT_Wmain, "return type of %qD is not %<int%>", decl1);
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (TYPE_ATOMIC (ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_TYPE (decl1))))
	pedwarn (loc, OPT_Wmain, "%<_Atomic%>-qualified return type of %qD",
		 decl1);

      check_main_parameter_types (decl1);

      ಆದರೆ (!ವೃಕ್ಷ_ಬಹಿರಂಗ (decl1))
	pedwarn (loc, OPT_Wmain,
		 "%qD is normally a non-static function", decl1);
    }

  ವೃಕ್ಷ parms = current_function_arg_info->parms;
  ಆದರೆ (old_decl)
    {
      location_t origloc = DECL_ಮೂಲ_LOCATION (old_decl);
      warn_parms_array_mismatch (origloc, old_decl, parms);
    }

  /* To enable versions to be created across TU's we mark and mangle all
     non-default versioned functions.  */
  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (decl1) == FUNCTION_DECL
      && !ಗುರಿ_HAS_FMV_ಗುರಿ_ATTRIBUTE
      && get_ಗುರಿ_ಆವೃತ್ತಿ (decl1).is_valid ())
    {
      maybe_mark_function_versioned (decl1);
      ಆದರೆ (current_scope != file_scope)
	error ("versioned definitions are only allowed at file scope");
    }

  /* Record the decl so that the function name is defined.
     If we already have a decl for this name, and it is a FUNCTION_DECL,
     use the old decl.  */

  current_function_decl = pushdecl (decl1);

  ಆದರೆ (ವೃಕ್ಷ access = build_attr_access_from_parms (parms, ಸುಳ್ಳು))
    decl_ಗುಣಲಕ್ಷಣಗಳು (&current_function_decl, access, ATTR_FLAG_ಆಂತರಿಕ,
		     old_decl);

  ತಳ್ಳು_scope ();
  declare_parm_level ();

  /* Set the result decl source location to the location of the typespec.  */
  ಫಲಿತಾಂಶ_loc = (declspecs->locations[cdw_typespec] == UNKNOWN_LOCATION
		? loc : declspecs->locations[cdw_typespec]);
  restype = ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_TYPE (current_function_decl));
  resdecl = build_decl (ಫಲಿತಾಂಶ_loc, ಫಲಿತಾಂಶ_DECL, NULL_ವೃಕ್ಷ, restype);
  DECL_ARTIFICIAL (resdecl) = 1;
  DECL_IGNORED_P (resdecl) = 1;
  DECL_ಫಲಿತಾಂಶ (current_function_decl) = resdecl;

  ಆರಂಭ_fname_decls ();

  ಹಿಂತಿರುಗಿ ನಿಜ;
}

/* Subroutine of store_parm_decls which handles new-style function
   definitions (prototype format). The parms already have decls, so we
   need only record them as in effect and complain if any redundant
   old-style parm decls were written.  */
ಸ್ಥಿರ ಶೂನ್ಯ
store_parm_decls_newstyle (ವೃಕ್ಷ fndecl, ಸ್ಥಿರಾಂಕ ರಚನೆ c_arg_info *arg_info)
{
  ವೃಕ್ಷ decl;
  c_arg_ಟ್ಯಾಗ್ *ಟ್ಯಾಗ್;
  ಚಿಹ್ನೆರಹಿತ ix;

  ಆದರೆ (current_scope->bindings)
    {
      error_at (DECL_ಮೂಲ_LOCATION (fndecl),
		"old-style parameter declarations in prototyped "
		"function definition");

      /* Get rid of the old-style declarations.  */
      ತೆಗೆ_scope ();
      ತಳ್ಳು_scope ();
    }
  /* Don't issue this warning for nested functions, and don't issue this
     warning if we got here because ARG_INFO_TYPES was error_mark_node
     (this happens when a function definition has just an ellipsis in
     its parameter list).  */
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!ಒಳ_system_ಶೀರ್ಷಿಕೆ_at (ಒಳಹರಿವು_location)
	   && !current_function_scope
	   && arg_info->types != error_mark_ಗಂಟು
	   && !arg_info->c23_ಖಾಲಿಗಳು_parens)
    warning_at (DECL_ಮೂಲ_LOCATION (fndecl), OPT_Wtraditional,
		"traditional C rejects ISO C style function definitions");

  /* Now make all the parameter declarations visible in the function body.
     We can bypass most of the grunt work of pushdecl.  */
  ಗಾಗಿ (decl = arg_info->parms; decl; decl = DECL_CHAIN (decl))
    {
      DECL_CONTEXT (decl) = current_function_decl;
      ಆದರೆ (DECL_NAME (decl))
	{
	  bind (DECL_NAME (decl), decl, current_scope,
		/*invisible=*/ಸುಳ್ಳು, /*nested=*/ಸುಳ್ಳು,
		UNKNOWN_LOCATION);
	  ಆದರೆ (!ವೃಕ್ಷ_ಬಳಸಿದ (decl))
	    warn_if_shadowing (decl);
	}
      ಇಲ್ಲದಿದ್ದರೆ
	pedwarn_c11 (DECL_ಮೂಲ_LOCATION (decl), OPT_Wmissing_parameter_name,
		     "ISO C does not support omitting parameter names in "
		     "function definitions before C23");
    }

  /* Record the parameter list in the function declaration.  */
  DECL_ARGUMENTS (fndecl) = arg_info->parms;

  /* Now make all the ancillary declarations visible, likewise.  */
  ಗಾಗಿ (decl = arg_info->others; decl; decl = DECL_CHAIN (decl))
    {
      DECL_CONTEXT (decl) = current_function_decl;
      ಆದರೆ (DECL_NAME (decl))
	bind (DECL_NAME (decl), decl, current_scope,
	      /*invisible=*/ಸುಳ್ಳು,
	      /*nested=*/(ವೃಕ್ಷ_ಸಂಕೇತ (decl) == FUNCTION_DECL),
	      UNKNOWN_LOCATION);
    }

  /* And all the tag declarations.  */
  FOR_EACH_VEC_ಸುರಕ್ಷಿತ_ELT_ಹಿಮ್ಮುಖ (arg_info->ಟ್ಯಾಗುಗಳು, ix, ಟ್ಯಾಗ್)
    ಆದರೆ (ಟ್ಯಾಗ್->id)
      bind (ಟ್ಯಾಗ್->id, ಟ್ಯಾಗ್->type, current_scope,
	    /*invisible=*/ಸುಳ್ಳು, /*nested=*/ಸುಳ್ಳು, UNKNOWN_LOCATION);
}

/* Subroutine of store_parm_decls which handles old-style function
   definitions (separate parameter list and declarations).  */

ಸ್ಥಿರ ಶೂನ್ಯ
store_parm_decls_oldstyle (ವೃಕ್ಷ fndecl, ಸ್ಥಿರಾಂಕ ರಚನೆ c_arg_info *arg_info)
{
  ರಚನೆ c_binding *b;
  ವೃಕ್ಷ parm, decl, ಕೊನೆಯ;
  ವೃಕ್ಷ parmids = arg_info->parms;
  hash_ಗಣ<ವೃಕ್ಷ> ನೋಡಿದ_ವಾದಗಳು;

  ಆದರೆ (!ಒಳ_system_ಶೀರ್ಷಿಕೆ_at (ಒಳಹರಿವು_location))
    {
      ಆದರೆ (flag_isoc23)
	pedwarn (DECL_ಮೂಲ_LOCATION (fndecl),
		 OPT_Wold_style_definition, "old-style function definition");
      ಇಲ್ಲದಿದ್ದರೆ
	warning_at (DECL_ಮೂಲ_LOCATION (fndecl),
		    OPT_Wold_style_definition,
		    "old-style function definition");
    }

  ಆದರೆ (current_scope->had_vla_unspec)
    error ("%<[*]%> not allowed in other than function prototype scope");

  /* Match each formal parameter name with its declaration.  Save each
     decl in the appropriate TREE_PURPOSE slot of the parmids chain.  */
  ಗಾಗಿ (parm = parmids; parm; parm = ವೃಕ್ಷ_CHAIN (parm))
    {
      ಆದರೆ (ವೃಕ್ಷ_ಮೌಲ್ಯ (parm) == NULL_ವೃಕ್ಷ)
	{
	  error_at (DECL_ಮೂಲ_LOCATION (fndecl),
		    "parameter name missing from parameter list");
	  ವೃಕ್ಷ_PURPOSE (parm) = NULL_ವೃಕ್ಷ;
	  ಮುಂದುವರಿ;
	}

      b = I_ಚಿಹ್ನೆ_BINDING (ವೃಕ್ಷ_ಮೌಲ್ಯ (parm));
      ಆದರೆ (b && B_ಒಳ_CURRENT_SCOPE (b))
	{
	  decl = b->decl;
	  /* Skip erroneous parameters.  */
	  ಆದರೆ (decl == error_mark_ಗಂಟು)
	    ಮುಂದುವರಿ;
	  /* If we got something other than a PARM_DECL it is an error.  */
	  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (decl) != PARM_DECL)
	    {
	      error_at (DECL_ಮೂಲ_LOCATION (decl),
			"%qD declared as a non-parameter", decl);
	      ಮುಂದುವರಿ;
	    }
	  /* If the declaration is already marked, we have a duplicate
	     name.  Complain and ignore the duplicate.  */
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ನೋಡಿದ_ವಾದಗಳು.ಒಳಗೊಂಡಿದೆ (decl))
	    {
	      error_at (DECL_ಮೂಲ_LOCATION (decl),
			"multiple parameters named %qD", decl);
	      ವೃಕ್ಷ_PURPOSE (parm) = NULL_ವೃಕ್ಷ;
	      ಮುಂದುವರಿ;
	    }
	  /* If the declaration says "void", complain and turn it into
	     an int.  */
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (VOID_TYPE_P (ವೃಕ್ಷ_TYPE (decl)))
	    {
	      error_at (DECL_ಮೂಲ_LOCATION (decl),
			"parameter %qD declared with void type", decl);
	      ವೃಕ್ಷ_TYPE (decl) = integer_type_ಗಂಟು;
	      DECL_ARG_TYPE (decl) = integer_type_ಗಂಟು;
	      layout_decl (decl, 0);
	    }
	  warn_if_shadowing (decl);
	}
      /* If no declaration found, default to int.  */
      ಇಲ್ಲದಿದ್ದರೆ
	{
	  /* FIXME diagnostics: This should be the location of the argument,
	     not the FNDECL.  E.g., for an old-style declaration

	       int f10(v) { blah; }

	     We should use the location of the V, not the F10.
	     Unfortunately, the V is an IDENTIFIER_NODE which has no
	     location.  In the future we need locations for c_arg_info
	     entries.

	     See gcc.dg/Wshadow-3.c for an example of this problem. */
	  decl = build_decl (DECL_ಮೂಲ_LOCATION (fndecl),
			     PARM_DECL, ವೃಕ್ಷ_ಮೌಲ್ಯ (parm), integer_type_ಗಂಟು);
	  DECL_ARG_TYPE (decl) = ವೃಕ್ಷ_TYPE (decl);
	  pushdecl (decl);
	  warn_if_shadowing (decl);

	  ಆದರೆ (flag_isoc99)
	    permerror_opt (DECL_ಮೂಲ_LOCATION (decl),
			   OPT_Wimplicit_int, "type of %qD defaults to %<int%>",
			   decl);
	  ಇಲ್ಲದಿದ್ದರೆ
	    warning_at (DECL_ಮೂಲ_LOCATION (decl),
			OPT_Wmissing_parameter_type,
			"type of %qD defaults to %<int%>", decl);
	}

      ವೃಕ್ಷ_PURPOSE (parm) = decl;
      ನೋಡಿದ_ವಾದಗಳು.ಕೂಡಿಸು (decl);
    }

  /* Now examine the parms chain for incomplete declarations
     and declarations with no corresponding names.  */

  ಗಾಗಿ (b = current_scope->bindings; b; b = b->prev)
    {
      parm = b->decl;
      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (parm) != PARM_DECL)
	ಮುಂದುವರಿ;

      ಆದರೆ (ವೃಕ್ಷ_TYPE (parm) != error_mark_ಗಂಟು
	  && !COMPLETE_TYPE_P (ವೃಕ್ಷ_TYPE (parm)))
	{
	  error_at (DECL_ಮೂಲ_LOCATION (parm),
		    "parameter %qD has incomplete type", parm);
	  ವೃಕ್ಷ_TYPE (parm) = error_mark_ಗಂಟು;
	}

      ಆದರೆ (!ನೋಡಿದ_ವಾದಗಳು.ಒಳಗೊಂಡಿದೆ (parm))
	{
	  error_at (DECL_ಮೂಲ_LOCATION (parm),
		    "declaration for parameter %qD but no such parameter",
		    parm);

	  /* Pretend the parameter was not missing.
	     This gets us to a standard state and minimizes
	     further error messages.  */
	  parmids = chainon (parmids, ವೃಕ್ಷ_cons (parm, 0, 0));
	}
    }

  /* Chain the declarations together in the order of the list of
     names.  Store that chain in the function decl, replacing the
     list of names.  Update the current scope to match.  */
  DECL_ARGUMENTS (fndecl) = NULL_ವೃಕ್ಷ;

  ಗಾಗಿ (parm = parmids; parm; parm = ವೃಕ್ಷ_CHAIN (parm))
    ಆದರೆ (ವೃಕ್ಷ_PURPOSE (parm))
      ನಿಲ್ಲಿಸು;
  ಆದರೆ (parm && ವೃಕ್ಷ_PURPOSE (parm))
    {
      ಕೊನೆಯ = ವೃಕ್ಷ_PURPOSE (parm);
      DECL_ARGUMENTS (fndecl) = ಕೊನೆಯ;

      ಗಾಗಿ (parm = ವೃಕ್ಷ_CHAIN (parm); parm; parm = ವೃಕ್ಷ_CHAIN (parm))
	ಆದರೆ (ವೃಕ್ಷ_PURPOSE (parm))
	  {
	    DECL_CHAIN (ಕೊನೆಯ) = ವೃಕ್ಷ_PURPOSE (parm);
	    ಕೊನೆಯ = ವೃಕ್ಷ_PURPOSE (parm);
	  }
      DECL_CHAIN (ಕೊನೆಯ) = NULL_ವೃಕ್ಷ;
    }

  /* If there was a previous prototype,
     set the DECL_ARG_TYPE of each argument according to
     the type previously specified, and report any mismatches.  */

  ಆದರೆ (current_function_prototype_arg_types)
    {
      ವೃಕ್ಷ type;
      ಗಾಗಿ (parm = DECL_ARGUMENTS (fndecl),
	     type = current_function_prototype_arg_types;
	   parm || (type != NULL_ವೃಕ್ಷ
		    && ವೃಕ್ಷ_ಮೌಲ್ಯ (type) != error_mark_ಗಂಟು
		    && TYPE_MAIN_VARIANT (ವೃಕ್ಷ_ಮೌಲ್ಯ (type)) != void_type_ಗಂಟು);
	   parm = DECL_CHAIN (parm), type = ವೃಕ್ಷ_CHAIN (type))
	{
	  ಆದರೆ (parm == NULL_ವೃಕ್ಷ
	      || type == NULL_ವೃಕ್ಷ
	      || (ವೃಕ್ಷ_ಮೌಲ್ಯ (type) != error_mark_ಗಂಟು
		  && TYPE_MAIN_VARIANT (ವೃಕ್ಷ_ಮೌಲ್ಯ (type)) == void_type_ಗಂಟು))
	    {
	      ಆದರೆ (current_function_prototype_built_ಒಳ)
		warning_at (DECL_ಮೂಲ_LOCATION (fndecl),
			    0, "number of arguments doesn%'t match "
			    "built-in prototype");
	      ಇಲ್ಲದಿದ್ದರೆ
		{
		  /* FIXME diagnostics: This should be the location of
		     FNDECL, but there is bug when a prototype is
		     declared inside function context, but defined
		     outside of it (e.g., gcc.dg/pr15698-2.c).  In
		     which case FNDECL gets the location of the
		     prototype, not the definition.  */
		  error_at (ಒಳಹರಿವು_location,
			    "number of arguments doesn%'t match prototype");

		  error_at (current_function_prototype_locus,
			    "prototype declaration");
		}
	      ನಿಲ್ಲಿಸು;
	    }
	  /* Type for passing arg must be consistent with that
	     declared for the arg.  ISO C says we take the unqualified
	     type for parameters declared with qualified type.  */
	  ಆದರೆ (ವೃಕ್ಷ_TYPE (parm) != error_mark_ಗಂಟು
	      && ವೃಕ್ಷ_ಮೌಲ್ಯ (type) != error_mark_ಗಂಟು
	      && ((TYPE_ATOMIC (DECL_ARG_TYPE (parm))
		   != TYPE_ATOMIC (ವೃಕ್ಷ_ಮೌಲ್ಯ (type)))
		  || !comptypes (TYPE_MAIN_VARIANT (DECL_ARG_TYPE (parm)),
				 TYPE_MAIN_VARIANT (ವೃಕ್ಷ_ಮೌಲ್ಯ (type)))))
	    {
	      ಆದರೆ ((TYPE_ATOMIC (DECL_ARG_TYPE (parm))
		   == TYPE_ATOMIC (ವೃಕ್ಷ_ಮೌಲ್ಯ (type)))
		  && (TYPE_MAIN_VARIANT (ವೃಕ್ಷ_TYPE (parm))
		      == TYPE_MAIN_VARIANT (ವೃಕ್ಷ_ಮೌಲ್ಯ (type))))
		{
		  /* Adjust argument to match prototype.  E.g. a previous
		     `int foo(float);' prototype causes
		     `int foo(x) float x; {...}' to be treated like
		     `int foo(float x) {...}'.  This is particularly
		     useful for argument types like uid_t.  */
		  DECL_ARG_TYPE (parm) = ವೃಕ್ಷ_TYPE (parm);

		  /* ??? Is it possible to get here with a
		     built-in prototype or will it always have
		     been diagnosed as conflicting with an
		     old-style definition and discarded?  */
		  ಆದರೆ (current_function_prototype_built_ಒಳ)
		    warning_at (DECL_ಮೂಲ_LOCATION (parm),
				OPT_Wpedantic, "promoted argument %qD "
				"doesn%'t match built-in prototype", parm);
		  ಇಲ್ಲದಿದ್ದರೆ
		    {
		      pedwarn (DECL_ಮೂಲ_LOCATION (parm),
			       OPT_Wpedantic, "promoted argument %qD "
			       "doesn%'t match prototype", parm);
		      pedwarn (current_function_prototype_locus, OPT_Wpedantic,
			       "prototype declaration");
		    }
		}
	      ಇಲ್ಲದಿದ್ದರೆ
		{
		  ಆದರೆ (current_function_prototype_built_ಒಳ)
		    warning_at (DECL_ಮೂಲ_LOCATION (parm),
				0, "argument %qD doesn%'t match "
				"built-in prototype", parm);
		  ಇಲ್ಲದಿದ್ದರೆ
		    {
		      error_at (DECL_ಮೂಲ_LOCATION (parm),
				"argument %qD doesn%'t match prototype", parm);
		      error_at (current_function_prototype_locus,
				"prototype declaration");
		    }
		}
	    }
	}
      TYPE_ACTUAL_ARG_TYPES (ವೃಕ್ಷ_TYPE (fndecl)) = NULL_ವೃಕ್ಷ;
    }

  /* Otherwise, create a prototype that would match.  */

  ಇಲ್ಲದಿದ್ದರೆ
    {
      ವೃಕ್ಷ actual = NULL_ವೃಕ್ಷ, ಕೊನೆಯ = NULL_ವೃಕ್ಷ, type;

      ಗಾಗಿ (parm = DECL_ARGUMENTS (fndecl); parm; parm = DECL_CHAIN (parm))
	{
	  type = ವೃಕ್ಷ_cons (NULL_ವೃಕ್ಷ, DECL_ARG_TYPE (parm), NULL_ವೃಕ್ಷ);
	  ಆದರೆ (ಕೊನೆಯ)
	    ವೃಕ್ಷ_CHAIN (ಕೊನೆಯ) = type;
	  ಇಲ್ಲದಿದ್ದರೆ
	    actual = type;
	  ಕೊನೆಯ = type;
	}
      type = ವೃಕ್ಷ_cons (NULL_ವೃಕ್ಷ, void_type_ಗಂಟು, NULL_ವೃಕ್ಷ);
      ಆದರೆ (ಕೊನೆಯ)
	ವೃಕ್ಷ_CHAIN (ಕೊನೆಯ) = type;
      ಇಲ್ಲದಿದ್ದರೆ
	actual = type;

      /* We are going to assign a new value for the TYPE_ACTUAL_ARG_TYPES
	 of the type of this function, but we need to avoid having this
	 affect the types of other similarly-typed functions, so we must
	 first force the generation of an identical (but separate) type
	 node for the relevant function type.  The new node we create
	 will be a variant of the main variant of the original function
	 type.  */

      ವೃಕ್ಷ_TYPE (fndecl) = build_variant_type_copy (ವೃಕ್ಷ_TYPE (fndecl));

      TYPE_ACTUAL_ARG_TYPES (ವೃಕ್ಷ_TYPE (fndecl)) = actual;
    }
}

/* Store parameter declarations passed in ARG_INFO into the current
   function declaration.  */

ಶೂನ್ಯ
store_parm_decls_from (ರಚನೆ c_arg_info *arg_info)
{
  current_function_arg_info = arg_info;
  store_parm_decls ();
}

/* Called by walk_tree to look for and update context-less labels
   or labels with context in the parent function.  */

ಸ್ಥಿರ ವೃಕ್ಷ
ಗಣ_labels_context_r (ವೃಕ್ಷ *tp, ಪೂರ್ಣಾಂಕ *walk_subtrees, ಶೂನ್ಯ *ದತ್ತಾಂಶ)
{
  ವೃಕ್ಷ ctx = static_cast<ವೃಕ್ಷ>(ದತ್ತಾಂಶ);
  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (*tp) == LABEL_ಅಭಿವ್ಯಕ್ತಿ
      && (DECL_CONTEXT (LABEL_ಅಭಿವ್ಯಕ್ತಿ_LABEL (*tp)) == NULL_ವೃಕ್ಷ
	  || DECL_CONTEXT (LABEL_ಅಭಿವ್ಯಕ್ತಿ_LABEL (*tp)) == DECL_CONTEXT (ctx)))
    {
      DECL_CONTEXT (LABEL_ಅಭಿವ್ಯಕ್ತಿ_LABEL (*tp)) = ctx;
      *walk_subtrees = 0;
    }

  ಹಿಂತಿರುಗಿ NULL_ವೃಕ್ಷ;
}

/* Store the parameter declarations into the current function declaration.
   This is called after parsing the parameter declarations, before
   digesting the body of the function.

   For an old-style definition, construct a prototype out of the old-style
   parameter declarations and inject it into the function's type.  */

ಶೂನ್ಯ
store_parm_decls (ಶೂನ್ಯ)
{
  ವೃಕ್ಷ fndecl = current_function_decl;
  ತಾರ್ಕಿಕ proto;

  /* The argument information block for FNDECL.  */
  ರಚನೆ c_arg_info *arg_info = current_function_arg_info;
  current_function_arg_info = 0;

  /* True if this definition is written with a prototype.  In C23, an
     empty argument list was converted to (void) in grokparms; in
     older C standard versions, it does not give the function a type
     with a prototype for future calls.  */
  proto = arg_info->types != 0 || arg_info->no_named_ವಾದಗಳು_stdarg_p;

  ಆದರೆ (proto)
    store_parm_decls_newstyle (fndecl, arg_info);
  ಇಲ್ಲದಿದ್ದರೆ
    store_parm_decls_oldstyle (fndecl, arg_info);

  /* The next call to push_scope will be a function body.  */

  ಮುಂದಿನ_is_function_body = ನಿಜ;

  /* Write a record describing this function definition to the prototypes
     file (if requested).  */

  gen_aux_info_ದಾಖಲೆ (fndecl, 1, 0, proto);

  /* Initialize the RTL code for the function.  */
  allocate_struct_function (fndecl, ಸುಳ್ಳು);

  ಆದರೆ (warn_ಬಳಸದ_local_typedefs)
    cfun->language = ggc_cleared_alloc<language_function> ();

  /* Begin the statement tree for this function.  */
  DECL_SAVED_ವೃಕ್ಷ (fndecl) = ತಳ್ಳು_stmt_list ();

  /* ??? Insert the contents of the pending sizes list into the function
     to be evaluated.  The only reason left to have this is
	void foo(int n, int array[n++])
     because we throw away the array type in favor of a pointer type, and
     thus won't naturally see the SAVE_EXPR containing the increment.  All
     other pending sizes would be handled by gimplify_parameters.  */
  ಆದರೆ (arg_info->pending_sizes)
    {
      /* In very special circumstances, e.g. for code like
	   _Atomic int i = 5;
	   void f (int a[i += 2]) {}
	 we need to execute the atomic assignment on function entry.
	 But in this case, it is not just a straight store, it has the
	 op= form, which means that build_atomic_assign has generated
	 gotos, labels, etc.  Because at that time the function decl
	 for F has not been created yet, those labels do not have any
	 function context.  But we have the fndecl now, so update the
	 labels accordingly.  gimplify_expr would crash otherwise.
	 Or with nested functions the labels could be created with parent
	 function's context, while when the statement is emitted at the
	 start of the nested function, it needs the nested function's
	 context.  */
      walk_ವೃಕ್ಷ_without_duplicates (&arg_info->pending_sizes,
				    ಗಣ_labels_context_r, fndecl);
      ಕೂಡಿಸು_stmt (arg_info->pending_sizes);
    }
}

/* Store PARM_DECLs in PARMS into scope temporarily.  Used for
   c_finish_omp_declare_simd for function prototypes.  No diagnostics
   should be done.  */

ಶೂನ್ಯ
ತಾತ್ಕಾಲಿಕ_store_parm_decls (ವೃಕ್ಷ fndecl, ವೃಕ್ಷ parms)
{
  ತಳ್ಳು_scope ();
  ಗಾಗಿ (ವೃಕ್ಷ p = parms; p; p = DECL_CHAIN (p))
    {
      DECL_CONTEXT (p) = fndecl;
      ಆದರೆ (DECL_NAME (p))
	bind (DECL_NAME (p), p, current_scope,
	      /*invisible=*/ಸುಳ್ಳು, /*nested=*/ಸುಳ್ಳು,
	      UNKNOWN_LOCATION);
    }
}

/* Undo what temp_store_parm_decls did.  */

ಶೂನ್ಯ
ತಾತ್ಕಾಲಿಕ_ತೆಗೆ_parm_decls (ಶೂನ್ಯ)
{
  /* Clear all bindings in this temporary scope, so that
     pop_scope doesn't create a BLOCK.  */
  ರಚನೆ c_binding *b = current_scope->bindings;
  current_scope->bindings = ಖಾಲಿ;
  ಗಾಗಿ (; b; b = free_binding_and_advance (b))
    {
      gcc_assert (ವೃಕ್ಷ_ಸಂಕೇತ (b->decl) == PARM_DECL
		  || b->decl == error_mark_ಗಂಟು);
      gcc_assert (I_ಚಿಹ್ನೆ_BINDING (b->id) == b);
      I_ಚಿಹ್ನೆ_BINDING (b->id) = b->shadowed;
      ಆದರೆ (b->shadowed && b->shadowed->u.type)
	ವೃಕ್ಷ_TYPE (b->shadowed->decl) = b->shadowed->u.type;
    }
  ತೆಗೆ_scope ();
}


/* Finish up a function declaration and compile that function
   all the way to assembler language output.  Then free the storage
   for the function definition.

   This is called after parsing the body of the function definition.  */

ಶೂನ್ಯ
ಮುಕ್ತಾಯ_function (location_t ಕೊನೆ_loc)
{
  ವೃಕ್ಷ fndecl = current_function_decl;

  ಆದರೆ (c_dialect_objc ())
    objc_ಮುಕ್ತಾಯ_function ();

  ಆದರೆ (DECL_INITIAL (fndecl) && DECL_INITIAL (fndecl) != error_mark_ಗಂಟು)
    ಖಂಡ_SUPERCONTEXT (DECL_INITIAL (fndecl)) = fndecl;

  /* Must mark the RESULT_DECL as being in this function.  */

  ಆದರೆ (DECL_ಫಲಿತಾಂಶ (fndecl) && DECL_ಫಲಿತಾಂಶ (fndecl) != error_mark_ಗಂಟು)
    DECL_CONTEXT (DECL_ಫಲಿತಾಂಶ (fndecl)) = fndecl;

  ಆದರೆ (MAIN_NAME_P (DECL_NAME (fndecl)) && !ವೃಕ್ಷ_THIS_VOLATILE (fndecl)
      && TYPE_MAIN_VARIANT (ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_TYPE (fndecl)))
      == integer_type_ಗಂಟು && flag_isoc99)
    {
      /* Hack.  We don't want the middle-end to warn that this return
	 is unreachable, so we mark its location as special.  Using
	 UNKNOWN_LOCATION has the problem that it gets clobbered in
	 annotate_one_with_locus.  A cleaner solution might be to
	 ensure ! should_carry_locus_p (stmt), but that needs a flag.
      */
      c_ಮುಕ್ತಾಯ_return (BUILTINS_LOCATION, integer_zero_ಗಂಟು, NULL_ವೃಕ್ಷ);
    }

  /* Tie off the statement tree for this function.  */
  DECL_SAVED_ವೃಕ್ಷ (fndecl) = ತೆಗೆ_stmt_list (DECL_SAVED_ವೃಕ್ಷ (fndecl));

  ಮುಕ್ತಾಯ_fname_decls ();

  /* Complain if there's no return statement only if option specified on
     command line.  */
  ಆದರೆ (warn_return_type > 0
      && ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_TYPE (fndecl))) != VOID_TYPE
      && !current_function_returns_ಮೌಲ್ಯ && !current_function_returns_null
      /* Don't complain if we are no-return.  */
      && !current_function_returns_abnormally
      /* Don't complain if we are declared noreturn.  */
      && !ವೃಕ್ಷ_THIS_VOLATILE (fndecl)
      /* Don't warn for main().  */
      && !MAIN_NAME_P (DECL_NAME (fndecl))
      /* Or if they didn't actually specify a return type.  */
      && !C_FUNCTION_IMPLICIT_INT (fndecl)
      /* Normally, with -Wreturn-type, flow will complain, but we might
         optimize out static functions.  */
      && !ವೃಕ್ಷ_ಬಹಿರಂಗ (fndecl)
      && targetm.warn_func_return (fndecl)
      && warning (OPT_Wreturn_type,
		  "no return statement in function returning non-void"))
    suppress_warning (fndecl, OPT_Wreturn_type);

  /* Complain about parameters that are only set, but never otherwise used.  */
  ಆದರೆ (warn_ಬಳಸದ_but_ಗಣ_parameter)
    {
      ವೃಕ್ಷ decl;

      ಗಾಗಿ (decl = DECL_ARGUMENTS (fndecl);
	   decl;
	   decl = DECL_CHAIN (decl))
	ಆದರೆ (ವೃಕ್ಷ_ಬಳಸಿದ (decl)
	    && ವೃಕ್ಷ_ಸಂಕೇತ (decl) == PARM_DECL
	    && !DECL_READ_P (decl)
	    && DECL_NAME (decl)
	    && !DECL_ARTIFICIAL (decl)
	    && !warning_suppressed_p (decl, OPT_Wunused_but_ಗಣ_parameter))
	  warning_at (DECL_ಮೂಲ_LOCATION (decl),
		      OPT_Wunused_but_ಗಣ_parameter,
		      "parameter %qD set but not used", decl);
    }

  /* Complain about locally defined typedefs that are not used in this
     function.  */
  maybe_warn_ಬಳಸದ_local_typedefs ();

  /* Possibly warn about unused parameters.  */
  ಆದರೆ (warn_ಬಳಸದ_parameter)
    do_warn_ಬಳಸದ_parameter (fndecl);

  /* Store the end of the function, so that we get good line number
     info for the epilogue.  */
  cfun->function_ಕೊನೆ_locus = ಕೊನೆ_loc;

  /* Finalize the ELF visibility for the function.  */
  c_determine_visibility (fndecl);

  /* For GNU C extern inline functions disregard inline limits.  */
  ಆದರೆ (DECL_EXTERNAL (fndecl)
      && DECL_DECLARED_INLINE_P (fndecl)
      && (flag_gnu89_inline
	  || lookup_attribute ("gnu_inline", DECL_ಗುಣಲಕ್ಷಣಗಳು (fndecl))))
    DECL_DISREGARD_INLINE_LIMITS (fndecl) = 1;

  /* Genericize before inlining.  Delay genericizing nested functions
     until their parent function is genericized.  Since finalizing
     requires GENERIC, delay that as well.  */

  ಆದರೆ (DECL_INITIAL (fndecl) && DECL_INITIAL (fndecl) != error_mark_ಗಂಟು
      && !undef_nested_function)
    {
      ಆದರೆ (!decl_function_context (fndecl))
	{
	  invoke_plugin_callbacks (PLUGIN_PRE_GENERICIZE, fndecl);
	  c_genericize (fndecl);

	  /* ??? Objc emits functions after finalizing the compilation unit.
	     This should be cleaned up later and this conditional removed.  */
	  ಆದರೆ (symtab->global_info_ready)
	    {
	      cgraph_ಗಂಟು::ಕೂಡಿಸು_new_function (fndecl, ಸುಳ್ಳು);
	      ಹಿಂತಿರುಗಿ;
	    }
	  cgraph_ಗಂಟು::finalize_function (fndecl, ಸುಳ್ಳು);
	}
      ಇಲ್ಲದಿದ್ದರೆ
	{
	  /* Register this function with cgraph just far enough to get it
	    added to our parent's nested function list.  Handy, since the
	    C front end doesn't have such a list.  */
	  (ಶೂನ್ಯ) cgraph_ಗಂಟು::get_create (fndecl);
	}
    }

  ಆದರೆ (!decl_function_context (fndecl))
    undef_nested_function = ಸುಳ್ಳು;

  ಆದರೆ (cfun->language != ಖಾಲಿ)
    {
      ggc_free (cfun->language);
      cfun->language = ಖಾಲಿ;
    }

  /* We're leaving the context of this function, so zap cfun.
     It's still in DECL_STRUCT_FUNCTION, and we'll restore it in
     tree_rest_of_compilation.  */
  ಗಣ_cfun (ಖಾಲಿ);
  invoke_plugin_callbacks (PLUGIN_ಮುಕ್ತಾಯ_PARSE_FUNCTION, current_function_decl);
  current_function_decl = ಖಾಲಿ;
}

/* Check the declarations given in a for-loop for satisfying the C99
   constraints.  If exactly one such decl is found, return it.  LOC is
   the location of the opening parenthesis of the for loop.  The last
   parameter allows you to control the "for loop initial declarations
   are only allowed in C99 mode".  Normally, you should pass
   flag_isoc99 as that parameter.  But in some cases (Objective-C
   foreach loop, for example) we want to run the checks in this
   function even if not in C99 mode, so we allow the caller to turn
   off the error about not being in C99 mode.
*/

ವೃಕ್ಷ
check_for_loop_decls (location_t loc, ತಾರ್ಕಿಕ turn_off_iso_c99_error)
{
  ರಚನೆ c_binding *b;
  ವೃಕ್ಷ one_decl = NULL_ವೃಕ್ಷ;
  ಪೂರ್ಣಾಂಕ n_decls = 0;

  ಆದರೆ (!turn_off_iso_c99_error)
    {
      ಸ್ಥಿರ ತಾರ್ಕಿಕ hint = ನಿಜ;
      /* If we get here, declarations have been used in a for loop without
	 the C99 for loop scope.  This doesn't make much sense, so don't
	 allow it.  */
      auto_diagnostic_ಗುಂಪು d;
      error_at (loc, "%<for%> loop initial declarations "
		"are only allowed in C99 or C11 mode");
      ಆದರೆ (hint)
	{
	  inform (loc,
		  "use option %<-std=c99%>, %<-std=gnu99%>, %<-std=c11%> or "
		  "%<-std=gnu11%> to compile your code");
	  hint = ಸುಳ್ಳು;
	}
      ಹಿಂತಿರುಗಿ NULL_ವೃಕ್ಷ;
    }
  ಇಲ್ಲದಿದ್ದರೆ
    pedwarn_c90 (loc, OPT_Wpedantic, "ISO C90 does not support %<for%> loop "
		 "initial declarations");

  /* C99 subclause 6.8.5 paragraph 3:

       [#3]  The  declaration  part  of  a for statement shall only
       declare identifiers for objects having storage class auto or
       register.

     It isn't clear whether, in this sentence, "identifiers" binds to
     "shall only declare" or to "objects" - that is, whether all identifiers
     declared must be identifiers for objects, or whether the restriction
     only applies to those that are.  (A question on this in comp.std.c
     in November 2000 received no answer.)  We implement the strictest
     interpretation, to avoid creating an extension which later causes
     problems.

     This constraint was removed in C23.  */

  ಗಾಗಿ (b = current_scope->bindings; b; b = b->prev)
    {
      ವೃಕ್ಷ id = b->id;
      ವೃಕ್ಷ decl = b->decl;

      ಆದರೆ (!id)
	ಮುಂದುವರಿ;

      ಆಯ್ಕೆ (ವೃಕ್ಷ_ಸಂಕೇತ (decl))
	{
	ಸ್ಥಿತಿ VAR_DECL:
	  {
	    location_t decl_loc = DECL_ಮೂಲ_LOCATION (decl);
	    ಆದರೆ (ವೃಕ್ಷ_STATIC (decl))
	      pedwarn_c11 (decl_loc, OPT_Wpedantic,
			   "declaration of static variable %qD in %<for%> "
			   "loop initial declaration", decl);
	    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (DECL_EXTERNAL (decl))
	      pedwarn_c11 (decl_loc, OPT_Wpedantic,
			   "declaration of %<extern%> variable %qD in %<for%> "
			   "loop initial declaration", decl);
	  }
	  ನಿಲ್ಲಿಸು;

	ಸ್ಥಿತಿ ದಾಖಲೆ_TYPE:
	  pedwarn_c11 (loc, OPT_Wpedantic,
		       "%<struct %E%> declared in %<for%> loop initial "
		       "declaration", id);
	  ನಿಲ್ಲಿಸು;
	ಸ್ಥಿತಿ UNION_TYPE:
	  pedwarn_c11 (loc, OPT_Wpedantic,
		       "%<union %E%> declared in %<for%> loop initial "
		       "declaration",
		       id);
	  ನಿಲ್ಲಿಸು;
	ಸ್ಥಿತಿ ENUMERAL_TYPE:
	  pedwarn_c11 (loc, OPT_Wpedantic,
		       "%<enum %E%> declared in %<for%> loop "
		       "initial declaration", id);
	  ನಿಲ್ಲಿಸು;
	ಪೂರ್ವನಿಯೋಜಿತ:
	  pedwarn_c11 (loc, OPT_Wpedantic, "declaration of non-variable "
		       "%qD in %<for%> loop initial declaration", decl);
	}

      n_decls++;
      one_decl = decl;
    }

  ಹಿಂತಿರುಗಿ n_decls == 1 ? one_decl : NULL_ವೃಕ್ಷ;
}

/* Save and reinitialize the variables
   used during compilation of a C function.  */

ಶೂನ್ಯ
c_ತಳ್ಳು_function_context (ಶೂನ್ಯ)
{
  ರಚನೆ language_function *p = cfun->language;
  /* cfun->language might have been already allocated by the use of
     -Wunused-local-typedefs.  In that case, just re-use it.  */
  ಆದರೆ (p == ಖಾಲಿ)
    cfun->language = p = ggc_cleared_alloc<language_function> ();

  p->ತಳ.x_stmt_ವೃಕ್ಷ = c_stmt_ವೃಕ್ಷ;
  c_stmt_ವೃಕ್ಷ.x_cur_stmt_list = vec_ಸುರಕ್ಷಿತ_copy (c_stmt_ವೃಕ್ಷ.x_cur_stmt_list);
  p->x_ಒಳ_statement = ಒಳ_statement;
  p->x_switch_ರಾಶಿ = c_switch_ರಾಶಿ;
  p->loop_ಹೆಸರುಗಳು = loop_ಹೆಸರುಗಳು;
  loop_ಹೆಸರುಗಳು = vNULL;
  p->loop_ಹೆಸರುಗಳು_hash = loop_ಹೆಸರುಗಳು_hash;
  loop_ಹೆಸರುಗಳು_hash = ಖಾಲಿ;
  p->arg_info = current_function_arg_info;
  p->returns_ಮೌಲ್ಯ = current_function_returns_ಮೌಲ್ಯ;
  p->returns_null = current_function_returns_null;
  p->returns_abnormally = current_function_returns_abnormally;
  p->warn_about_return_type = warn_about_return_type;

  ತಳ್ಳು_function_context ();
}

/* Restore the variables used during compilation of a C function.  */

ಶೂನ್ಯ
c_ತೆಗೆ_function_context (ಶೂನ್ಯ)
{
  ರಚನೆ language_function *p;

  ತೆಗೆ_function_context ();
  p = cfun->language;

  /* When -Wunused-local-typedefs is in effect, cfun->languages is
     used to store data throughout the life time of the current cfun,
     So don't deallocate it.  */
  ಆದರೆ (!warn_ಬಳಸದ_local_typedefs)
    cfun->language = ಖಾಲಿ;

  ಆದರೆ (DECL_STRUCT_FUNCTION (current_function_decl) == 0
      && DECL_SAVED_ವೃಕ್ಷ (current_function_decl) == NULL_ವೃಕ್ಷ)
    {
      /* Stop pointing to the local nodes about to be freed.  */
      /* But DECL_INITIAL must remain nonzero so we know this
	 was an actual function definition.  */
      DECL_INITIAL (current_function_decl) = error_mark_ಗಂಟು;
      DECL_ARGUMENTS (current_function_decl) = NULL_ವೃಕ್ಷ;
    }

  c_stmt_ವೃಕ್ಷ = p->ತಳ.x_stmt_ವೃಕ್ಷ;
  p->ತಳ.x_stmt_ವೃಕ್ಷ.x_cur_stmt_list = ಖಾಲಿ;
  ಒಳ_statement = p->x_ಒಳ_statement;
  c_switch_ರಾಶಿ = p->x_switch_ರಾಶಿ;
  loop_ಹೆಸರುಗಳು.release ();
  loop_ಹೆಸರುಗಳು = p->loop_ಹೆಸರುಗಳು;
  p->loop_ಹೆಸರುಗಳು = vNULL;
  ಅಳಿಸು loop_ಹೆಸರುಗಳು_hash;
  loop_ಹೆಸರುಗಳು_hash = p->loop_ಹೆಸರುಗಳು_hash;
  p->loop_ಹೆಸರುಗಳು_hash = ಖಾಲಿ;
  current_function_arg_info = p->arg_info;
  current_function_returns_ಮೌಲ್ಯ = p->returns_ಮೌಲ್ಯ;
  current_function_returns_null = p->returns_null;
  current_function_returns_abnormally = p->returns_abnormally;
  warn_about_return_type = p->warn_about_return_type;
}

/* The functions below are required for functionality of doing
   function at once processing in the C front end. Currently these
   functions are not called from anywhere in the C front end, but as
   these changes continue, that will change.  */

/* Returns the stmt_tree (if any) to which statements are currently
   being added.  If there is no active statement-tree, NULL is
   returned.  */

stmt_ವೃಕ್ಷ
current_stmt_ವೃಕ್ಷ (ಶೂನ್ಯ)
{
  ಹಿಂತಿರುಗಿ &c_stmt_ವೃಕ್ಷ;
}

/* Return the global value of T as a symbol.  */

ವೃಕ್ಷ
identifier_global_ಮೌಲ್ಯ	(ವೃಕ್ಷ t)
{
  ರಚನೆ c_binding *b;

  ಗಾಗಿ (b = I_ಚಿಹ್ನೆ_BINDING (t); b; b = b->shadowed)
    ಆದರೆ (B_ಒಳ_FILE_SCOPE (b) || B_ಒಳ_EXTERNAL_SCOPE (b))
      ಹಿಂತಿರುಗಿ b->decl;

  ಹಿಂತಿರುಗಿ NULL_ವೃಕ್ಷ;
}

/* Return the global value of tag T as a symbol.  */

ವೃಕ್ಷ
identifier_global_ಟ್ಯಾಗ್ (ವೃಕ್ಷ t)
{
  ರಚನೆ c_binding *b;

  ಗಾಗಿ (b = I_ಟ್ಯಾಗ್_BINDING (t); b; b = b->shadowed)
    ಆದರೆ (B_ಒಳ_FILE_SCOPE (b) || B_ಒಳ_EXTERNAL_SCOPE (b))
      ಹಿಂತಿರುಗಿ b->decl;

  ಹಿಂತಿರುಗಿ NULL_ವೃಕ್ಷ;
}

/* Returns non-zero (result of __has_builtin) if NAME refers to a built-in
   function or function-like operator.  */

ಪೂರ್ಣಾಂಕ
ಹೆಸರುಗಳು_builtin_p (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name)
{
  ವೃಕ್ಷ id = get_identifier (name);
  ಆದರೆ (ವೃಕ್ಷ decl = identifier_global_ಮೌಲ್ಯ (id))
    ಹಿಂತಿರುಗಿ ವೃಕ್ಷ_ಸಂಕೇತ (decl) == FUNCTION_DECL && DECL_IS_UNDECLARED_BUILTIN (decl);

  /* Also detect common reserved C words that aren't strictly built-in
     functions.  */
  ಆಯ್ಕೆ (C_RID_ಸಂಕೇತ (id))
    {
    ಸ್ಥಿತಿ RID_BUILTIN_ASSOC_BARRIER:
    ಸ್ಥಿತಿ RID_BUILTIN_BITREVERSEG:
    ಸ್ಥಿತಿ RID_BUILTIN_BSWAPG:
    ಸ್ಥಿತಿ RID_BUILTIN_CONVERTVECTOR:
    ಸ್ಥಿತಿ RID_BUILTIN_HAS_ATTRIBUTE:
    ಸ್ಥಿತಿ RID_BUILTIN_SHUFFLE:
    ಸ್ಥಿತಿ RID_BUILTIN_SHUFFLEVECTOR:
    ಸ್ಥಿತಿ RID_BUILTIN_STDC:
    ಸ್ಥಿತಿ RID_BUILTIN_COUNTED_BY_REF:
    ಸ್ಥಿತಿ RID_ಆರಿಸು_ಅಭಿವ್ಯಕ್ತಿ:
    ಸ್ಥಿತಿ RID_OFFSETOF:
    ಸ್ಥಿತಿ RID_TYPES_COMPATIBLE_P:
    ಸ್ಥಿತಿ RID_C23_VA_ಆರಂಭ:
    ಸ್ಥಿತಿ RID_VA_ARG:
      ಹಿಂತಿರುಗಿ 1;
    ಪೂರ್ವನಿಯೋಜಿತ:
      ನಿಲ್ಲಿಸು;
    }

  ಹಿಂತಿರುಗಿ 0;
}

/* In C, the only C-linkage public declaration is at file scope.  */

ವೃಕ್ಷ
c_linkage_bindings (ವೃಕ್ಷ name)
{
  ಹಿಂತಿರುಗಿ identifier_global_ಮೌಲ್ಯ (name);
}

/* Record a builtin type for C.  If NAME is non-NULL, it is the name used;
   otherwise the name is found in ridpointers from RID_INDEX.  */

ಶೂನ್ಯ
ದಾಖಲೆ_builtin_type (ಎಣಿಕೆ rid rid_ಸೂಚ್ಯಂಕ, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name, ವೃಕ್ಷ type)
{
  ವೃಕ್ಷ id, decl;
  ಆದರೆ (name == 0)
    id = ridpointers[(ಪೂರ್ಣಾಂಕ) rid_ಸೂಚ್ಯಂಕ];
  ಇಲ್ಲದಿದ್ದರೆ
    id = get_identifier (name);
  decl = build_decl (UNKNOWN_LOCATION, TYPE_DECL, id, type);
  pushdecl (decl);
  ಆದರೆ (debug_hooks->type_decl)
    debug_hooks->type_decl (decl, ಸುಳ್ಳು);
}

/* Return a c_parm structure with the given SPECS, ATTRS and DECLARATOR.  */

ರಚನೆ c_parm *
build_c_parm (ರಚನೆ c_declspecs *specs, ವೃಕ್ಷ attrs,
	      ರಚನೆ c_declarator *declarator,
	      location_t loc)
{
  ರಚನೆ c_parm *ret = XOBNEW (&parser_obstack, ರಚನೆ c_parm);
  ret->specs = specs;
  ret->attrs = attrs;
  ret->declarator = declarator;
  ret->loc = loc;
  ಹಿಂತಿರುಗಿ ret;
}

/* Return a declarator with nested attributes.  TARGET is the inner
   declarator to which these attributes apply.  ATTRS are the
   attributes.  */

ರಚನೆ c_declarator *
build_attrs_declarator (ವೃಕ್ಷ attrs, ರಚನೆ c_declarator *ಗುರಿ)
{
  ರಚನೆ c_declarator *ret = XOBNEW (&parser_obstack, ರಚನೆ c_declarator);
  ret->ಬಗೆ = cdk_attrs;
  ret->declarator = ಗುರಿ;
  ret->u.attrs = attrs;
  ಹಿಂತಿರುಗಿ ret;
}

/* Return a declarator for a function with arguments specified by ARGS
   and return type specified by TARGET.  */

ರಚನೆ c_declarator *
build_function_declarator (ರಚನೆ c_arg_info *ವಾದಗಳು,
			   ರಚನೆ c_declarator *ಗುರಿ)
{
  ರಚನೆ c_declarator *ret = XOBNEW (&parser_obstack, ರಚನೆ c_declarator);
  ret->ಬಗೆ = cdk_function;
  ret->declarator = ಗುರಿ;
  ret->u.arg_info = ವಾದಗಳು;
  ಹಿಂತಿರುಗಿ ret;
}

/* Return a declarator for the identifier IDENT (which may be
   NULL_TREE for an abstract declarator).  */

ರಚನೆ c_declarator *
build_id_declarator (ವೃಕ್ಷ ident)
{
  ರಚನೆ c_declarator *ret = XOBNEW (&parser_obstack, ರಚನೆ c_declarator);
  ret->ಬಗೆ = cdk_id;
  ret->declarator = 0;
  ret->u.id.id = ident;
  ret->u.id.attrs = NULL_ವೃಕ್ಷ;
  /* Default value - may get reset to a more precise location. */
  ret->id_loc = ಒಳಹರಿವು_location;
  ಹಿಂತಿರುಗಿ ret;
}

/* Return something to represent absolute declarators containing a *.
   TARGET is the absolute declarator that the * contains.
   TYPE_QUALS_ATTRS is a structure for type qualifiers and attributes
   to apply to the pointer type.  */

ರಚನೆ c_declarator *
make_ಸೂಚಕ_declarator (ರಚನೆ c_declspecs *type_quals_attrs,
			 ರಚನೆ c_declarator *ಗುರಿ)
{
  ವೃಕ್ಷ attrs;
  ಪೂರ್ಣಾಂಕ quals = 0;
  ರಚನೆ c_declarator *itarget = ಗುರಿ;
  ರಚನೆ c_declarator *ret = XOBNEW (&parser_obstack, ರಚನೆ c_declarator);
  ಆದರೆ (type_quals_attrs)
    {
      attrs = type_quals_attrs->attrs;
      quals = quals_from_declspecs (type_quals_attrs);
      ಆದರೆ (attrs != NULL_ವೃಕ್ಷ)
	itarget = build_attrs_declarator (attrs, ಗುರಿ);
    }
  ret->ಬಗೆ = cdk_ಸೂಚಕ;
  ret->declarator = itarget;
  ret->u.ಸೂಚಕ_quals = quals;
  ಹಿಂತಿರುಗಿ ret;
}

/* Return a pointer to a structure for an empty list of declaration
   specifiers.  */

ರಚನೆ c_declspecs *
build_null_declspecs (ಶೂನ್ಯ)
{
  ರಚನೆ c_declspecs *ret = XOBNEW (&parser_obstack, ರಚನೆ c_declspecs);
  memset (ret, 0, ಗಾತ್ರ *ret);
  ret->align_log = -1;
  ret->typespec_ಶಬ್ದ = cts_none;
  ret->storage_class = csc_none;
  ret->ಅಭಿವ್ಯಕ್ತಿ_const_operands = ನಿಜ;
  ret->typespec_ಬಗೆ = ctsk_none;
  ret->ವಿಳಾಸ_space = ADDR_SPACE_GENERIC;
  ಹಿಂತಿರುಗಿ ret;
}

/* Add the address space ADDRSPACE to the declaration specifiers
   SPECS, returning SPECS.  */

ರಚನೆ c_declspecs *
declspecs_ಕೂಡಿಸು_addrspace (location_t location,
			 ರಚನೆ c_declspecs *specs, addr_space_t as)
{
  specs->non_sc_ನೋಡಿದ_p = ನಿಜ;
  specs->declspecs_ನೋಡಿದ_p = ನಿಜ;
  specs->non_std_attrs_ನೋಡಿದ_p = ನಿಜ;

  ಆದರೆ (!ADDR_SPACE_GENERIC_P (specs->ವಿಳಾಸ_space)
      && specs->ವಿಳಾಸ_space != as)
    error ("incompatible address space qualifiers %qs and %qs",
	   c_addr_space_name (as),
	   c_addr_space_name (specs->ವಿಳಾಸ_space));
  ಇಲ್ಲದಿದ್ದರೆ
    {
      specs->ವಿಳಾಸ_space = as;
      specs->locations[cdw_ವಿಳಾಸ_space] = location;
    }
  ಹಿಂತಿರುಗಿ specs;
}

/* Add the type qualifier QUAL to the declaration specifiers SPECS,
   returning SPECS.  */

ರಚನೆ c_declspecs *
declspecs_ಕೂಡಿಸು_qual (location_t loc,
		    ರಚನೆ c_declspecs *specs, ವೃಕ್ಷ qual)
{
  ಎಣಿಕೆ rid i;
  ತಾರ್ಕಿಕ dupe = ಸುಳ್ಳು;
  specs->non_sc_ನೋಡಿದ_p = ನಿಜ;
  specs->declspecs_ನೋಡಿದ_p = ನಿಜ;
  specs->non_std_attrs_ನೋಡಿದ_p = ನಿಜ;
  gcc_assert (ವೃಕ್ಷ_ಸಂಕೇತ (qual) == IDENTIFIER_ಗಂಟು
	      && C_IS_RESERVED_ಶಬ್ದ (qual));
  i = C_RID_ಸಂಕೇತ (qual);
  location_t prev_loc = UNKNOWN_LOCATION;
  ಆಯ್ಕೆ (i)
    {
    ಸ್ಥಿತಿ RID_CONST:
      dupe = specs->const_p;
      specs->const_p = ನಿಜ;
      prev_loc = specs->locations[cdw_const];
      specs->locations[cdw_const] = loc;
      ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ RID_VOLATILE:
      dupe = specs->volatile_p;
      specs->volatile_p = ನಿಜ;
      prev_loc = specs->locations[cdw_volatile];
      specs->locations[cdw_volatile] = loc;
      ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ RID_RESTRICT:
      dupe = specs->restrict_p;
      specs->restrict_p = ನಿಜ;
      prev_loc = specs->locations[cdw_restrict];
      specs->locations[cdw_restrict] = loc;
      ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ RID_ATOMIC:
      dupe = specs->atomic_p;
      specs->atomic_p = ನಿಜ;
      prev_loc = specs->locations[cdw_atomic];
      specs->locations[cdw_atomic] = loc;
      ನಿಲ್ಲಿಸು;
    ಪೂರ್ವನಿಯೋಜಿತ:
      gcc_unreachable ();
    }
  ಆದರೆ (dupe)
    {
      ತಾರ್ಕಿಕ warned = pedwarn_c90 (loc, OPT_Wpedantic,
				 "duplicate %qE declaration specifier", qual);
      ಆದರೆ (!warned
	  && warn_duplicate_decl_specifier
	  && prev_loc >= RESERVED_LOCATION_ಎಣಿಕೆ
	  && !from_macro_expansion_at (prev_loc)
	  && !from_macro_expansion_at (loc))
	warning_at (loc, OPT_Wduplicate_decl_specifier,
		    "duplicate %qE declaration specifier", qual);
    }
  ಹಿಂತಿರುಗಿ specs;
}

/* Add the type specifier TYPE to the declaration specifiers SPECS,
   returning SPECS.  */

ರಚನೆ c_declspecs *
declspecs_ಕೂಡಿಸು_type (location_t loc, ರಚನೆ c_declspecs *specs,
		    ರಚನೆ c_typespec spec)
{
  ವೃಕ್ಷ type = spec.spec;
  specs->non_sc_ನೋಡಿದ_p = ನಿಜ;
  specs->declspecs_ನೋಡಿದ_p = ನಿಜ;
  specs->non_std_attrs_ನೋಡಿದ_p = ನಿಜ;
  specs->typespec_ಬಗೆ = spec.ಬಗೆ;
  ಆದರೆ (ವೃಕ್ಷ_DEPRECATED (type))
    specs->deprecated_p = ನಿಜ;
  ಆದರೆ (ವೃಕ್ಷ_UNAVAILABLE (type))
    specs->unavailable_p = ನಿಜ;

  /* As a type specifier is present, "auto" must be used as a storage
     class specifier, not for type deduction.  */
  ಆದರೆ (specs->c23_auto_p)
    {
      specs->c23_auto_p = ಸುಳ್ಳು;
      ಆದರೆ (specs->storage_class != csc_none)
	error ("multiple storage classes in declaration specifiers");
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->thread_p)
	error ("%qs used with %<auto%>",
	       specs->thread_gnu_p ? "__thread" : "_Thread_local");
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->constexpr_p)
	/* auto may only be used with another storage class specifier,
	   such as constexpr, if the type is inferred.  */
	error ("%<auto%> used with %<constexpr%>");
      ಇಲ್ಲದಿದ್ದರೆ
	specs->storage_class = csc_auto;
    }

  /* Handle type specifier keywords.  */
  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (type) == IDENTIFIER_ಗಂಟು
      && C_IS_RESERVED_ಶಬ್ದ (type)
      && C_RID_ಸಂಕೇತ (type) != RID_CXX_COMPAT_WARN)
    {
      ಎಣಿಕೆ rid i = C_RID_ಸಂಕೇತ (type);
      ಆದರೆ (specs->type)
	{
	  error_at (loc, "two or more data types in declaration specifiers");
	  ಹಿಂತಿರುಗಿ specs;
	}
      ಆದರೆ ((ಪೂರ್ಣಾಂಕ) i <= (ಪೂರ್ಣಾಂಕ) RID_ಕೊನೆಯ_MODIFIER)
	{
	  /* "long", "short", "signed", "unsigned", "_Complex" or "_Sat".  */
	  ತಾರ್ಕಿಕ dupe = ಸುಳ್ಳು;
	  ಆಯ್ಕೆ (i)
	    {
	    ಸ್ಥಿತಿ RID_LONG:
	      ಆದರೆ (specs->long_long_p)
		{
		  error_at (loc, "%<long long long%> is too long for GCC");
		  ನಿಲ್ಲಿಸು;
		}
	      ಆದರೆ (specs->long_p)
		{
		  ಆದರೆ (specs->typespec_ಶಬ್ದ == cts_double)
		    {
		      error_at (loc,
				"both %qs and %qs in declaration specifiers",
				"long long", "double");
		      ನಿಲ್ಲಿಸು;
		    }
		  pedwarn_c90 (loc, OPT_Wlong_long,
			       "ISO C90 does not support %<long long%>");
		  specs->long_long_p = 1;
		  specs->locations[cdw_long_long] = loc;
		  ನಿಲ್ಲಿಸು;
		}
	      ಆದರೆ (specs->short_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "short");
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->typespec_ಶಬ್ದ == cts_auto_type)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "__auto_type");
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->typespec_ಶಬ್ದ == cts_void)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "void");
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->typespec_ಶಬ್ದ == cts_int_n)
		error_at (loc,
			  "both %qs and %<__int%d%> in declaration specifiers",
			  "long", int_n_ದತ್ತಾಂಶ[specs->u.int_n_idx].bitsize);
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->typespec_ಶಬ್ದ == cts_bool)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "_Bool");
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->typespec_ಶಬ್ದ == cts_bitint)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "_BitInt");
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->typespec_ಶಬ್ದ == cts_char)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "char");
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->typespec_ಶಬ್ದ == cts_float)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "float");
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->typespec_ಶಬ್ದ == cts_floatn_nx)
		error_at (loc,
			  "both %qs and %<_Float%d%s%> in declaration "
			  "specifiers", "long",
			  floatn_nx_types[specs->u.floatn_nx_idx].n,
			  floatn_nx_types[specs->u.floatn_nx_idx].extended
			  ? "x"
			  : "");
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->typespec_ಶಬ್ದ == cts_dfloat32)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "_Decimal32");
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->typespec_ಶಬ್ದ == cts_dfloat64)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "_Decimal64");
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->typespec_ಶಬ್ದ == cts_dfloat128)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "_Decimal128");
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->typespec_ಶಬ್ದ == cts_dfloat64x)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "_Decimal64x");
	      ಇಲ್ಲದಿದ್ದರೆ
		{
		  specs->long_p = ನಿಜ;
		  specs->locations[cdw_long] = loc;
		}
	      ನಿಲ್ಲಿಸು;
	    ಸ್ಥಿತಿ RID_SHORT:
	      dupe = specs->short_p;
	      ಆದರೆ (specs->long_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "short");
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->typespec_ಶಬ್ದ == cts_auto_type)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "__auto_type");
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->typespec_ಶಬ್ದ == cts_void)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "void");
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->typespec_ಶಬ್ದ == cts_int_n)
		error_at (loc,
			  "both %qs and %<__int%d%> in declaration specifiers",
			  "short", int_n_ದತ್ತಾಂಶ[specs->u.int_n_idx].bitsize);
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->typespec_ಶಬ್ದ == cts_bool)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "_Bool");
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->typespec_ಶಬ್ದ == cts_bitint)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "_BitInt");
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->typespec_ಶಬ್ದ == cts_char)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "char");
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->typespec_ಶಬ್ದ == cts_float)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "float");
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->typespec_ಶಬ್ದ == cts_double)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "double");
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->typespec_ಶಬ್ದ == cts_floatn_nx)
		error_at (loc,
			  "both %qs and %<_Float%d%s%> in declaration "
			  "specifiers", "short",
			  floatn_nx_types[specs->u.floatn_nx_idx].n,
			  floatn_nx_types[specs->u.floatn_nx_idx].extended
			  ? "x"
			  : "");
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->typespec_ಶಬ್ದ == cts_dfloat32)
                error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "_Decimal32");
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->typespec_ಶಬ್ದ == cts_dfloat64)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "_Decimal64");
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->typespec_ಶಬ್ದ == cts_dfloat128)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "_Decimal128");
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->typespec_ಶಬ್ದ == cts_dfloat64x)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "_Decimal64x");
	      ಇಲ್ಲದಿದ್ದರೆ
		{
		  specs->short_p = ನಿಜ;
		  specs->locations[cdw_short] = loc;
		}
	      ನಿಲ್ಲಿಸು;
	    ಸ್ಥಿತಿ RID_SIGNED:
	      dupe = specs->signed_p;
	      ಆದರೆ (specs->unsigned_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "unsigned");
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->typespec_ಶಬ್ದ == cts_auto_type)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "__auto_type");
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->typespec_ಶಬ್ದ == cts_void)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "void");
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->typespec_ಶಬ್ದ == cts_bool)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "_Bool");
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->typespec_ಶಬ್ದ == cts_float)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "float");
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->typespec_ಶಬ್ದ == cts_double)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "double");
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->typespec_ಶಬ್ದ == cts_floatn_nx)
		error_at (loc,
			  "both %qs and %<_Float%d%s%> in declaration "
			  "specifiers", "signed",
			  floatn_nx_types[specs->u.floatn_nx_idx].n,
			  floatn_nx_types[specs->u.floatn_nx_idx].extended
			  ? "x"
			  : "");
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->typespec_ಶಬ್ದ == cts_dfloat32)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "_Decimal32");
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->typespec_ಶಬ್ದ == cts_dfloat64)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "_Decimal64");
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->typespec_ಶಬ್ದ == cts_dfloat128)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "_Decimal128");
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->typespec_ಶಬ್ದ == cts_dfloat64x)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "_Decimal64x");
	      ಇಲ್ಲದಿದ್ದರೆ
		{
		  specs->signed_p = ನಿಜ;
		  specs->locations[cdw_signed] = loc;
		}
	      ನಿಲ್ಲಿಸು;
	    ಸ್ಥಿತಿ RID_UNSIGNED:
	      dupe = specs->unsigned_p;
	      ಆದರೆ (specs->signed_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "unsigned");
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->typespec_ಶಬ್ದ == cts_auto_type)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "__auto_type");
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->typespec_ಶಬ್ದ == cts_void)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "void");
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->typespec_ಶಬ್ದ == cts_bool)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "_Bool");
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->typespec_ಶಬ್ದ == cts_float)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "float");
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->typespec_ಶಬ್ದ == cts_double)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "double");
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->typespec_ಶಬ್ದ == cts_floatn_nx)
		error_at (loc,
			  "both %qs and %<_Float%d%s%> in declaration "
			  "specifiers", "unsigned",
			  floatn_nx_types[specs->u.floatn_nx_idx].n,
			  floatn_nx_types[specs->u.floatn_nx_idx].extended
			  ? "x"
			  : "");
              ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->typespec_ಶಬ್ದ == cts_dfloat32)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "_Decimal32");
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->typespec_ಶಬ್ದ == cts_dfloat64)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "_Decimal64");
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->typespec_ಶಬ್ದ == cts_dfloat128)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "_Decimal128");
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->typespec_ಶಬ್ದ == cts_dfloat64x)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "_Decimal64x");
	      ಇಲ್ಲದಿದ್ದರೆ
		{
		  specs->unsigned_p = ನಿಜ;
		  specs->locations[cdw_unsigned] = loc;
		}
	      ನಿಲ್ಲಿಸು;
	    ಸ್ಥಿತಿ RID_COMPLEX:
	      dupe = specs->complex_p;
	      ಆದರೆ (!ಒಳ_system_ಶೀರ್ಷಿಕೆ_at (loc))
		pedwarn_c90 (loc, OPT_Wpedantic,
			     "ISO C90 does not support complex types");
	      ಆದರೆ (specs->typespec_ಶಬ್ದ == cts_auto_type)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "__auto_type");
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->typespec_ಶಬ್ದ == cts_void)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "void");
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->typespec_ಶಬ್ದ == cts_bool)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "_Bool");
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->typespec_ಶಬ್ದ == cts_bitint)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "_BitInt");
              ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->typespec_ಶಬ್ದ == cts_dfloat32)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "_Decimal32");
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->typespec_ಶಬ್ದ == cts_dfloat64)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "_Decimal64");
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->typespec_ಶಬ್ದ == cts_dfloat128)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "_Decimal128");
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->typespec_ಶಬ್ದ == cts_dfloat64x)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "_Decimal64x");
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->typespec_ಶಬ್ದ == cts_fract)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "_Fract");
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->typespec_ಶಬ್ದ == cts_accum)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "_Accum");
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->saturating_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "_Sat");
	      ಇಲ್ಲದಿದ್ದರೆ
		{
		  specs->complex_p = ನಿಜ;
		  specs->locations[cdw_complex] = loc;
		}
	      ನಿಲ್ಲಿಸು;
	    ಸ್ಥಿತಿ RID_SAT:
	      dupe = specs->saturating_p;
	      pedwarn (loc, OPT_Wpedantic,
		       "ISO C does not support saturating types");
	      ಆದರೆ (specs->typespec_ಶಬ್ದ == cts_int_n)
		error_at (loc,
			  "both %qs and %<__int%d%> in declaration specifiers",
			  "_Sat", int_n_ದತ್ತಾಂಶ[specs->u.int_n_idx].bitsize);
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->typespec_ಶಬ್ದ == cts_auto_type)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "__auto_type");
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->typespec_ಶಬ್ದ == cts_void)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "void");
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->typespec_ಶಬ್ದ == cts_bool)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "_Bool");
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->typespec_ಶಬ್ದ == cts_bitint)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "_BitInt");
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->typespec_ಶಬ್ದ == cts_char)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "char");
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->typespec_ಶಬ್ದ == cts_int)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "int");
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->typespec_ಶಬ್ದ == cts_float)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "float");
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->typespec_ಶಬ್ದ == cts_double)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "double");
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->typespec_ಶಬ್ದ == cts_floatn_nx)
		error_at (loc,
			  "both %qs and %<_Float%d%s%> in declaration "
			  "specifiers", "_Sat",
			  floatn_nx_types[specs->u.floatn_nx_idx].n,
			  floatn_nx_types[specs->u.floatn_nx_idx].extended
			  ? "x"
			  : "");
              ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->typespec_ಶಬ್ದ == cts_dfloat32)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "_Decimal32");
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->typespec_ಶಬ್ದ == cts_dfloat64)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "_Decimal64");
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->typespec_ಶಬ್ದ == cts_dfloat128)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "_Decimal128");
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->typespec_ಶಬ್ದ == cts_dfloat64x)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "_Decimal64x");
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->complex_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "complex");
	      ಇಲ್ಲದಿದ್ದರೆ
		{
		  specs->saturating_p = ನಿಜ;
		  specs->locations[cdw_saturating] = loc;
		}
	      ನಿಲ್ಲಿಸು;
	    ಪೂರ್ವನಿಯೋಜಿತ:
	      gcc_unreachable ();
	    }

	  ಆದರೆ (dupe)
	    error_at (loc, "duplicate %qE", type);

	  ಹಿಂತಿರುಗಿ specs;
	}
      ಇಲ್ಲದಿದ್ದರೆ
	{
	  /* "void", "_Bool", "char", "int", "float", "double",
	     "_FloatN", "_FloatNx", "_Decimal32", "__intN",
	     "_Decimal64", "_Decimal128", "_Fract", "_Accum", "_BitInt(N)" or
	     "__auto_type".  */
	  ಆದರೆ (specs->typespec_ಶಬ್ದ != cts_none)
	    {
	      ಆದರೆ (i == RID_BOOL)
		{
		  auto_diagnostic_ಗುಂಪು d;
		  ಆದರೆ (specs->storage_class == csc_typedef)
		    error_at (loc,
			      "%qs cannot be defined via %<typedef%>",
			      IDENTIFIER_ಸೂಚಕ (type));
		  ಇಲ್ಲದಿದ್ದರೆ
		    error_at (loc,
			      "%qs cannot be used here",
			      IDENTIFIER_ಸೂಚಕ (type));
		  ಕೂಡಿಸು_note_about_new_keyword (loc, type);
		}
	      ಇಲ್ಲದಿದ್ದರೆ
		error_at (loc,
			  "two or more data types in declaration specifiers");
	      ಹಿಂತಿರುಗಿ specs;
	    }
	  ಆಯ್ಕೆ (i)
	    {
	    ಸ್ಥಿತಿ RID_AUTO_TYPE:
	      ಆದರೆ (specs->long_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "__auto_type");
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->short_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "__auto_type");
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->signed_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "__auto_type");
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->unsigned_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "__auto_type");
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->complex_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "__auto_type");
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->saturating_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "__auto_type");
	      ಇಲ್ಲದಿದ್ದರೆ
		{
		  specs->typespec_ಶಬ್ದ = cts_auto_type;
		  specs->locations[cdw_typespec] = loc;
		}
	      ಹಿಂತಿರುಗಿ specs;
	    ಸ್ಥಿತಿ RID_INT_N_0:
	    ಸ್ಥಿತಿ RID_INT_N_1:
	    ಸ್ಥಿತಿ RID_INT_N_2:
	    ಸ್ಥಿತಿ RID_INT_N_3:
	      specs->u.int_n_idx = i - RID_INT_N_0;
	      ಆದರೆ (!ಒಳ_system_ಶೀರ್ಷಿಕೆ_at (ಒಳಹರಿವು_location)
		  /* If the INT_N type ends in "__", and so is of the format
		     "__intN__", don't pedwarn.  */
		  && (ಅಕ್ಷರಸರಣಿ_ಹೋಲಿಕೆ (IDENTIFIER_ಸೂಚಕ (type)
			       + (IDENTIFIER_ಉದ್ದಳತೆ (type) - 2), "__", 2) != 0))
		pedwarn (loc, OPT_Wpedantic,
			 "ISO C does not support %<__int%d%> types",
			 int_n_ದತ್ತಾಂಶ[specs->u.int_n_idx].bitsize);

	      ಆದರೆ (specs->long_p)
		error_at (loc,
			  "both %<__int%d%> and %qs in declaration specifiers",
			  int_n_ದತ್ತಾಂಶ[specs->u.int_n_idx].bitsize, "long");
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->saturating_p)
		error_at (loc,
			  "both %qs and %<__int%d%> in declaration specifiers",
			  "_Sat", int_n_ದತ್ತಾಂಶ[specs->u.int_n_idx].bitsize);
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->short_p)
		error_at (loc,
			  "both %<__int%d%> and %qs in declaration specifiers",
			  int_n_ದತ್ತಾಂಶ[specs->u.int_n_idx].bitsize, "short");
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (! int_n_enabled_p[specs->u.int_n_idx])
		{
		  specs->typespec_ಶಬ್ದ = cts_int_n;
		  error_at (loc,
			    "%<__int%d%> is not supported on this target",
			    int_n_ದತ್ತಾಂಶ[specs->u.int_n_idx].bitsize);
		}
	      ಇಲ್ಲದಿದ್ದರೆ
		{
		  specs->typespec_ಶಬ್ದ = cts_int_n;
		  specs->locations[cdw_typespec] = loc;
		}
	      ಹಿಂತಿರುಗಿ specs;
	    ಸ್ಥಿತಿ RID_VOID:
	      ಆದರೆ (specs->long_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "void");
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->short_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "void");
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->signed_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "void");
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->unsigned_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "void");
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->complex_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "void");
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->saturating_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "void");
	      ಇಲ್ಲದಿದ್ದರೆ
		{
		  specs->typespec_ಶಬ್ದ = cts_void;
		  specs->locations[cdw_typespec] = loc;
		}
	      ಹಿಂತಿರುಗಿ specs;
	    ಸ್ಥಿತಿ RID_BOOL:
	      ಆದರೆ (!ಒಳ_system_ಶೀರ್ಷಿಕೆ_at (loc))
		pedwarn_c90 (loc, OPT_Wpedantic,
			     "ISO C90 does not support boolean types");
	      ಆದರೆ (specs->long_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "_Bool");
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->short_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "_Bool");
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->signed_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "_Bool");
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->unsigned_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "_Bool");
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->complex_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "_Bool");
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->saturating_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "_Bool");
	      ಇಲ್ಲದಿದ್ದರೆ
		{
		  specs->typespec_ಶಬ್ದ = cts_bool;
		  specs->locations[cdw_typespec] = loc;
		}
	      ಹಿಂತಿರುಗಿ specs;
	    ಸ್ಥಿತಿ RID_CHAR:
	      ಆದರೆ (specs->long_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "char");
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->short_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "char");
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->saturating_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "char");
	      ಇಲ್ಲದಿದ್ದರೆ
		{
		  specs->typespec_ಶಬ್ದ = cts_char;
		  specs->locations[cdw_typespec] = loc;
		}
	      ಹಿಂತಿರುಗಿ specs;
	    ಸ್ಥಿತಿ RID_INT:
	      ಆದರೆ (specs->saturating_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "int");
	      ಇಲ್ಲದಿದ್ದರೆ
		{
		  specs->typespec_ಶಬ್ದ = cts_int;
		  specs->locations[cdw_typespec] = loc;
		}
	      ಹಿಂತಿರುಗಿ specs;
	    ಸ್ಥಿತಿ RID_FLOAT:
	      ಆದರೆ (specs->long_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "float");
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->short_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "float");
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->signed_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "float");
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->unsigned_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "float");
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->saturating_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "float");
	      ಇಲ್ಲದಿದ್ದರೆ
		{
		  specs->typespec_ಶಬ್ದ = cts_float;
		  specs->locations[cdw_typespec] = loc;
		}
	      ಹಿಂತಿರುಗಿ specs;
	    ಸ್ಥಿತಿ RID_DOUBLE:
	      ಆದರೆ (specs->long_long_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long long", "double");
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->short_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "double");
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->signed_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "double");
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->unsigned_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "double");
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->saturating_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "double");
	      ಇಲ್ಲದಿದ್ದರೆ
		{
		  specs->typespec_ಶಬ್ದ = cts_double;
		  specs->locations[cdw_typespec] = loc;
		}
	      ಹಿಂತಿರುಗಿ specs;
	    CASE_RID_FLOATN_NX:
	      specs->u.floatn_nx_idx = i - RID_FLOATN_NX_ಮೊದಲ;
	      ಆದರೆ (!ಒಳ_system_ಶೀರ್ಷಿಕೆ_at (ಒಳಹರಿವು_location))
		pedwarn_c11 (loc, OPT_Wpedantic,
			     "ISO C does not support the %<_Float%d%s%> type"
			     " before C23",
			     floatn_nx_types[specs->u.floatn_nx_idx].n,
			     floatn_nx_types[specs->u.floatn_nx_idx].extended
			     ? "x"
			     : "");

	      ಆದರೆ (specs->long_p)
		error_at (loc,
			  "both %qs and %<_Float%d%s%> in declaration "
			  "specifiers", "long",
			  floatn_nx_types[specs->u.floatn_nx_idx].n,
			  floatn_nx_types[specs->u.floatn_nx_idx].extended
			  ? "x"
			  : "");
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->short_p)
		error_at (loc,
			  "both %qs and %<_Float%d%s%> in declaration "
			  "specifiers", "short",
			  floatn_nx_types[specs->u.floatn_nx_idx].n,
			  floatn_nx_types[specs->u.floatn_nx_idx].extended
			  ? "x"
			  : "");
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->signed_p)
		error_at (loc,
			  "both %qs and %<_Float%d%s%> in declaration "
			  "specifiers", "signed",
			  floatn_nx_types[specs->u.floatn_nx_idx].n,
			  floatn_nx_types[specs->u.floatn_nx_idx].extended
			  ? "x"
			  : "");
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->unsigned_p)
		error_at (loc,
			  "both %qs and %<_Float%d%s%> in declaration "
			  "specifiers", "unsigned",
			  floatn_nx_types[specs->u.floatn_nx_idx].n,
			  floatn_nx_types[specs->u.floatn_nx_idx].extended
			  ? "x"
			  : "");
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->saturating_p)
		error_at (loc,
			  "both %qs and %<_Float%d%s%> in declaration "
			  "specifiers", "_Sat",
			  floatn_nx_types[specs->u.floatn_nx_idx].n,
			  floatn_nx_types[specs->u.floatn_nx_idx].extended
			  ? "x"
			  : "");
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (FLOATN_NX_TYPE_ಗಂಟು (specs->u.floatn_nx_idx) == NULL_ವೃಕ್ಷ)
		{
		  specs->typespec_ಶಬ್ದ = cts_floatn_nx;
		  error_at (loc,
			    "%<_Float%d%s%> is not supported on this target",
			    floatn_nx_types[specs->u.floatn_nx_idx].n,
			    floatn_nx_types[specs->u.floatn_nx_idx].extended
			    ? "x"
			    : "");
		}
	      ಇಲ್ಲದಿದ್ದರೆ
		{
		  specs->typespec_ಶಬ್ದ = cts_floatn_nx;
		  specs->locations[cdw_typespec] = loc;
		}
	      ಹಿಂತಿರುಗಿ specs;
	    ಸ್ಥಿತಿ RID_DFLOAT32:
	    ಸ್ಥಿತಿ RID_DFLOAT64:
	    ಸ್ಥಿತಿ RID_DFLOAT128:
	    ಸ್ಥಿತಿ RID_DFLOAT64X:
	      {
		ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *str;
		ಆದರೆ (i == RID_DFLOAT32)
		  str = "_Decimal32";
		ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (i == RID_DFLOAT64)
		  str = "_Decimal64";
		ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (i == RID_DFLOAT128)
		  str = "_Decimal128";
		ಇಲ್ಲದಿದ್ದರೆ
		  str = "_Decimal64x";
		ಆದರೆ (specs->long_long_p)
		  error_at (loc,
			    "both %qs and %qs in declaration specifiers",
			    "long long", str);
		ಆದರೆ (specs->long_p)
		  error_at (loc,
			    "both %qs and %qs in declaration specifiers",
			    "long", str);
		ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->short_p)
		  error_at (loc,
			    "both %qs and %qs in declaration specifiers",
			    "short", str);
		ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->signed_p)
		  error_at (loc,
			    "both %qs and %qs in declaration specifiers",
			    "signed", str);
		ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->unsigned_p)
		  error_at (loc,
			    "both %qs and %qs in declaration specifiers",
			    "unsigned", str);
                ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->complex_p)
                  error_at (loc,
			    "both %qs and %qs in declaration specifiers",
			    "complex", str);
                ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->saturating_p)
                  error_at (loc,
			    "both %qs and %qs in declaration specifiers",
			    "_Sat", str);
		ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (i == RID_DFLOAT32)
		  specs->typespec_ಶಬ್ದ = cts_dfloat32;
		ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (i == RID_DFLOAT64)
		  specs->typespec_ಶಬ್ದ = cts_dfloat64;
		ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (i == RID_DFLOAT128)
		  specs->typespec_ಶಬ್ದ = cts_dfloat128;
		ಇಲ್ಲದಿದ್ದರೆ
		  specs->typespec_ಶಬ್ದ = cts_dfloat64x;
		specs->locations[cdw_typespec] = loc;
	      }
	      ಆದರೆ (!targetm.decimal_float_supported_p ())
		error_at (loc,
			  "decimal floating-point not supported "
			  "for this target");
	      pedwarn_c11 (loc, OPT_Wpedantic,
			   "ISO C does not support decimal floating-point "
			   "before C23");
	      ಹಿಂತಿರುಗಿ specs;
	    ಸ್ಥಿತಿ RID_FRACT:
	    ಸ್ಥಿತಿ RID_ACCUM:
	      {
		ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *str;
		ಆದರೆ (i == RID_FRACT)
		  str = "_Fract";
		ಇಲ್ಲದಿದ್ದರೆ
		  str = "_Accum";
                ಆದರೆ (specs->complex_p)
                  error_at (loc,
			    "both %qs and %qs in declaration specifiers",
			    "complex", str);
		ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (i == RID_FRACT)
		    specs->typespec_ಶಬ್ದ = cts_fract;
		ಇಲ್ಲದಿದ್ದರೆ
		    specs->typespec_ಶಬ್ದ = cts_accum;
		specs->locations[cdw_typespec] = loc;
	      }
	      ಆದರೆ (!targetm.fixed_ಬಿಂದು_supported_p ())
		error_at (loc,
			  "fixed-point types not supported for this target");
	      pedwarn (loc, OPT_Wpedantic,
		       "ISO C does not support fixed-point types");
	      ಹಿಂತಿರುಗಿ specs;
	    ಸ್ಥಿತಿ RID_BITINT:
	      ಆದರೆ (specs->long_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "_BitInt");
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->short_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "_BitInt");
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->complex_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "_BitInt");
	      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->saturating_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "_BitInt");
	      ಇಲ್ಲದಿದ್ದರೆ
		{
		  specs->typespec_ಶಬ್ದ = cts_bitint;
		  specs->locations[cdw_typespec] = loc;
		  specs->u.bitint_prec = -1;
		  ಆದರೆ (error_ಕಾರ್ಯಾಂಶ_p (spec.ಅಭಿವ್ಯಕ್ತಿ))
		    ಹಿಂತಿರುಗಿ specs;
		  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (spec.ಅಭಿವ್ಯಕ್ತಿ) != INTEGER_CST
		      || !INTEGRAL_TYPE_P (ವೃಕ್ಷ_TYPE (spec.ಅಭಿವ್ಯಕ್ತಿ)))
		    {
		      error_at (loc, "%<_BitInt%> argument is not an integer "
				     "constant expression");
		      ಹಿಂತಿರುಗಿ specs;
		    }
		  ಆದರೆ (ವೃಕ್ಷ_int_cst_sgn (spec.ಅಭಿವ್ಯಕ್ತಿ) <= 0)
		    {
		      error_at (loc, "%<_BitInt%> argument %qE is not a "
				     "positive integer constant expression",
				spec.ಅಭಿವ್ಯಕ್ತಿ);
		      ಹಿಂತಿರುಗಿ specs;
		    }
		  ಆದರೆ (wi::ಗಮ್ಯ_widest (spec.ಅಭಿವ್ಯಕ್ತಿ) > WIDE_INT_MAX_PRECISION - 1)
		    {
		      error_at (loc, "%<_BitInt%> argument %qE is larger than "
				     "%<BITINT_MAXWIDTH%> %qd",
				spec.ಅಭಿವ್ಯಕ್ತಿ, (ಪೂರ್ಣಾಂಕ) WIDE_INT_MAX_PRECISION - 1);
		      ಹಿಂತಿರುಗಿ specs;
		    }
		  specs->u.bitint_prec = ವೃಕ್ಷ_ಗಮ್ಯ_uhwi (spec.ಅಭಿವ್ಯಕ್ತಿ);
		  ರಚನೆ bitint_info info;
		  ಆದರೆ (!targetm.c.bitint_type_info (specs->u.bitint_prec,
						   &info))
		    {
		      sorry_at (loc, "%<_BitInt(%d)%> is not supported on "
				     "this target", specs->u.bitint_prec);
		      specs->u.bitint_prec = -1;
		      ಹಿಂತಿರುಗಿ specs;
		    }
		}
	      ಹಿಂತಿರುಗಿ specs;
	    ಪೂರ್ವನಿಯೋಜಿತ:
	      /* ObjC reserved word "id", handled below.  */
	      ನಿಲ್ಲಿಸು;
	    }
	}
    }

  /* Now we have a typedef (a TYPE_DECL node), an identifier (some
     form of ObjC type, cases such as "int" and "long" being handled
     above), a TYPE (struct, union, enum and typeof specifiers) or an
     ERROR_MARK.  In none of these cases may there have previously
     been any type specifiers.  */
  ಆದರೆ (specs->type || specs->typespec_ಶಬ್ದ != cts_none
      || specs->long_p || specs->short_p || specs->signed_p
      || specs->unsigned_p || specs->complex_p)
    error_at (loc, "two or more data types in declaration specifiers");
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (type) == TYPE_DECL)
    {
      specs->type = ವೃಕ್ಷ_TYPE (type);
      ಆದರೆ (ವೃಕ್ಷ_TYPE (type) != error_mark_ಗಂಟು)
	{
	  mark_decl_ಬಳಸಿದ (type, ಸುಳ್ಳು);
	  specs->decl_attr = DECL_ಗುಣಲಕ್ಷಣಗಳು (type);
	  specs->typedef_p = ನಿಜ;
	  specs->explicit_signed_p = C_TYPEDEF_EXPLICITLY_SIGNED (type);
	  specs->locations[cdw_typedef] = loc;

	  /* If this typedef name is defined in a struct, then a C++
	     lookup would return a different value.  */
	  ಆದರೆ (warn_cxx_compat
	      && I_ಚಿಹ್ನೆ_BINDING (DECL_NAME (type))->ಒಳ_struct)
	    warning_at (loc, OPT_Wc___compat,
			"C++ lookup of %qD would return a field, not a type",
			type);

	  /* If we are parsing a struct, record that a struct field
	     used a typedef.  */
	  ಆದರೆ (warn_cxx_compat && struct_parse_info != ಖಾಲಿ)
	    struct_parse_info->typedefs_ನೋಡಿದ.ಸುರಕ್ಷಿತ_ತಳ್ಳು (type);
	}
    }
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (type) == IDENTIFIER_ಗಂಟು)
    {
      ವೃಕ್ಷ t = lookup_name (type);
      ಆದರೆ (!t || ವೃಕ್ಷ_ಸಂಕೇತ (t) != TYPE_DECL)
	error_at (loc, "%qE fails to be a typedef or built in type", type);
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ವೃಕ್ಷ_TYPE (t) == error_mark_ಗಂಟು)
	;
      ಇಲ್ಲದಿದ್ದರೆ
	{
	  specs->type = ವೃಕ್ಷ_TYPE (t);
	  specs->locations[cdw_typespec] = loc;
	}
    }
  ಇಲ್ಲದಿದ್ದರೆ
    {
      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (type) != ERROR_MARK)
	{
	  ಆದರೆ (spec.ಬಗೆ == ctsk_typeof)
	    {
	      specs->typedef_p = ನಿಜ;
	      specs->locations[cdw_typedef] = loc;
	    }

	  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (type) == ದಾಖಲೆ_TYPE || ವೃಕ್ಷ_ಸಂಕೇತ (type) == UNION_TYPE
	      || ವೃಕ್ಷ_ಸಂಕೇತ (type) == ENUMERAL_TYPE)
	    mark_decl_ಬಳಸಿದ (TYPE_STUB_DECL (type), ಸುಳ್ಳು);

	  ಆದರೆ (spec.ಅಭಿವ್ಯಕ್ತಿ)
	    {
	      ವೃಕ್ಷ ಅಭಿವ್ಯಕ್ತಿ = save_ಅಭಿವ್ಯಕ್ತಿ (fold_convert (void_type_ಗಂಟು, spec.ಅಭಿವ್ಯಕ್ತಿ));
	      ಆದರೆ (specs->ಅಭಿವ್ಯಕ್ತಿ)
		specs->ಅಭಿವ್ಯಕ್ತಿ = build2 (COMPOUND_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ),
				      specs->ಅಭಿವ್ಯಕ್ತಿ, ಅಭಿವ್ಯಕ್ತಿ);
	      ಇಲ್ಲದಿದ್ದರೆ
		specs->ಅಭಿವ್ಯಕ್ತಿ = ಅಭಿವ್ಯಕ್ತಿ;
	      specs->ಅಭಿವ್ಯಕ್ತಿ_const_operands &= spec.ಅಭಿವ್ಯಕ್ತಿ_const_operands;
	    }
	}
      specs->type = type;
      ಆದರೆ (spec.has_enum_type_specifier
	  && spec.ಬಗೆ != ctsk_tagdef)
	specs->enum_type_specifier_ref_p = ನಿಜ;
    }

  ಹಿಂತಿರುಗಿ specs;
}

/* Add the storage class specifier or function specifier SCSPEC to the
   declaration specifiers SPECS, returning SPECS.  */

ರಚನೆ c_declspecs *
declspecs_ಕೂಡಿಸು_scspec (location_t loc,
		      ರಚನೆ c_declspecs *specs,
		      ವೃಕ್ಷ scspec)
{
  ಎಣಿಕೆ rid i;
  ಎಣಿಕೆ c_storage_class n = csc_none;
  ತಾರ್ಕಿಕ dupe = ಸುಳ್ಳು;
  specs->declspecs_ನೋಡಿದ_p = ನಿಜ;
  specs->non_std_attrs_ನೋಡಿದ_p = ನಿಜ;
  gcc_assert (ವೃಕ್ಷ_ಸಂಕೇತ (scspec) == IDENTIFIER_ಗಂಟು
	      && C_IS_RESERVED_ಶಬ್ದ (scspec));
  i = C_RID_ಸಂಕೇತ (scspec);
  ಆದರೆ (specs->non_sc_ನೋಡಿದ_p)
    warning (OPT_Wold_style_declaration,
             "%qE is not at beginning of declaration", scspec);
  ಆಯ್ಕೆ (i)
    {
    ಸ್ಥಿತಿ RID_INLINE:
      /* C99 permits duplicate inline.  Although of doubtful utility,
	 it seems simplest to permit it in gnu89 mode as well, as
	 there is also little utility in maintaining this as a
	 difference between gnu89 and C99 inline.  */
      dupe = ಸುಳ್ಳು;
      specs->inline_p = ನಿಜ;
      specs->locations[cdw_inline] = loc;
      ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ RID_NORETURN:
      /* Duplicate _Noreturn is permitted.  */
      dupe = ಸುಳ್ಳು;
      specs->noreturn_p = ನಿಜ;
      specs->locations[cdw_noreturn] = loc;
      ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ RID_THREAD:
      dupe = specs->thread_p;
      ಆದರೆ (specs->storage_class == csc_auto)
	error ("%qE used with %<auto%>", scspec);
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->storage_class == csc_ರಿಜಿಸ್ಟರ್)
	error ("%qE used with %<register%>", scspec);
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->storage_class == csc_typedef)
	error ("%qE used with %<typedef%>", scspec);
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->constexpr_p)
	error ("%qE used with %<constexpr%>", scspec);
      ಇಲ್ಲದಿದ್ದರೆ
	{
	  specs->thread_p = ನಿಜ;
	  specs->thread_gnu_p = (strcmp (IDENTIFIER_ಸೂಚಕ (scspec),
					 "__thread") == 0);
	  /* A diagnostic is not required for the use of this
	     identifier in the implementation namespace; only diagnose
	     it for the C11 spelling because of existing code using
	     the other spelling.  */
	  ಆದರೆ (!specs->thread_gnu_p)
	    {
	      ಆದರೆ (flag_isoc99)
		pedwarn_c99 (loc, OPT_Wpedantic,
			     "ISO C99 does not support %qE", scspec);
	      ಇಲ್ಲದಿದ್ದರೆ
		pedwarn_c99 (loc, OPT_Wpedantic,
			     "ISO C90 does not support %qE", scspec);
	    }
	  specs->locations[cdw_thread] = loc;
	}
      ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ RID_AUTO:
      ಆದರೆ (flag_isoc23
	  && specs->typespec_ಬಗೆ == ctsk_none
	  && specs->storage_class != csc_typedef)
	{
	  /* "auto" potentially used for type deduction.  */
	  ಆದರೆ (specs->c23_auto_p)
	    error ("duplicate %qE", scspec);
	  specs->c23_auto_p = ನಿಜ;
	  ಹಿಂತಿರುಗಿ specs;
	}
      n = csc_auto;
      /* auto may only be used with another storage class specifier,
	 such as constexpr, if the type is inferred.  */
      ಆದರೆ (specs->constexpr_p)
	error ("%qE used with %<constexpr%>", scspec);
      ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ RID_EXTERN:
      n = csc_extern;
      /* Diagnose "__thread extern".  */
      ಆದರೆ (specs->thread_p && specs->thread_gnu_p)
	error ("%<__thread%> before %<extern%>");
      ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ RID_ರಿಜಿಸ್ಟರ್:
      n = csc_ರಿಜಿಸ್ಟರ್;
      ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ RID_STATIC:
      n = csc_static;
      /* Diagnose "__thread static".  */
      ಆದರೆ (specs->thread_p && specs->thread_gnu_p)
	error ("%<__thread%> before %<static%>");
      ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ RID_TYPEDEF:
      n = csc_typedef;
      ಆದರೆ (specs->c23_auto_p)
	{
	  error ("%<typedef%> used with %<auto%>");
	  specs->c23_auto_p = ಸುಳ್ಳು;
	}
      ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ RID_CONSTEXPR:
      dupe = specs->constexpr_p;
      ಆದರೆ (specs->storage_class == csc_extern)
	error ("%qE used with %<extern%>", scspec);
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->storage_class == csc_typedef)
	error ("%qE used with %<typedef%>", scspec);
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->storage_class == csc_auto)
	/* auto may only be used with another storage class specifier,
	   such as constexpr, if the type is inferred.  */
	error ("%qE used with %<auto%>", scspec);
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->thread_p)
	error ("%qE used with %qs", scspec,
	       specs->thread_gnu_p ? "__thread" : "_Thread_local");
      ಇಲ್ಲದಿದ್ದರೆ
	specs->constexpr_p = ನಿಜ;
      ನಿಲ್ಲಿಸು;
    ಪೂರ್ವನಿಯೋಜಿತ:
      gcc_unreachable ();
    }
  ಆದರೆ (n != csc_none && n == specs->storage_class)
    dupe = ನಿಜ;
  ಆದರೆ (dupe)
    {
      ಆದರೆ (i == RID_THREAD)
	error ("duplicate %<_Thread_local%> or %<__thread%>");
      ಇಲ್ಲದಿದ್ದರೆ
	error ("duplicate %qE", scspec);
    }
  ಆದರೆ (n != csc_none)
    {
      ಆದರೆ (specs->storage_class != csc_none && n != specs->storage_class)
	{
	  error ("multiple storage classes in declaration specifiers");
	}
      ಇಲ್ಲದಿದ್ದರೆ
	{
	  specs->storage_class = n;
	  specs->locations[cdw_storage_class] = loc;
	  ಆದರೆ (n != csc_extern && n != csc_static && specs->thread_p)
	    {
	      error ("%qs used with %qE",
		     specs->thread_gnu_p ? "__thread" : "_Thread_local",
		     scspec);
	      specs->thread_p = ಸುಳ್ಳು;
	    }
	  ಆದರೆ (n != csc_auto && n != csc_ರಿಜಿಸ್ಟರ್ && n != csc_static
	      && specs->constexpr_p)
	    {
	      error ("%<constexpr%> used with %qE", scspec);
	      specs->constexpr_p = ಸುಳ್ಳು;
	    }
	}
    }
  ಹಿಂತಿರುಗಿ specs;
}

/* Add the attributes ATTRS to the declaration specifiers SPECS,
   returning SPECS.  */

ರಚನೆ c_declspecs *
declspecs_ಕೂಡಿಸು_attrs (location_t loc, ರಚನೆ c_declspecs *specs, ವೃಕ್ಷ attrs)
{
  specs->attrs = chainon (attrs, specs->attrs);
  specs->locations[cdw_ಗುಣಲಕ್ಷಣಗಳು] = loc;
  specs->declspecs_ನೋಡಿದ_p = ನಿಜ;
  /* In the case of standard attributes at the start of the
     declaration, the caller will reset this.  */
  specs->non_std_attrs_ನೋಡಿದ_p = ನಿಜ;
  ಹಿಂತಿರುಗಿ specs;
}

/* Add an _Alignas specifier (expression ALIGN, or type whose
   alignment is ALIGN) to the declaration specifiers SPECS, returning
   SPECS.  */
ರಚನೆ c_declspecs *
declspecs_ಕೂಡಿಸು_alignas (location_t loc,
		       ರಚನೆ c_declspecs *specs, ವೃಕ್ಷ align)
{
  specs->alignas_p = ನಿಜ;
  specs->locations[cdw_alignas] = loc;
  ಆದರೆ (align == error_mark_ಗಂಟು)
    ಹಿಂತಿರುಗಿ specs;

  /* Only accept the alignment if it's valid and greater than
     the current one.  Zero is invalid but by C11 required to
     be silently ignored.  */
  ಪೂರ್ಣಾಂಕ align_log = check_user_alignment (align, ಸುಳ್ಳು, /* warn_zero = */ಸುಳ್ಳು);
  ಆದರೆ (align_log > specs->align_log)
    specs->align_log = align_log;
  ಹಿಂತಿರುಗಿ specs;
}

/* Combine "long", "short", "signed", "unsigned" and "_Complex" type
   specifiers with any other type specifier to determine the resulting
   type.  This is where ISO C checks on complex types are made, since
   "_Complex long" is a prefix of the valid ISO C type "_Complex long
   double".  Also apply postfix standard attributes to modify the type.  */

ರಚನೆ c_declspecs *
ಮುಕ್ತಾಯ_declspecs (ರಚನೆ c_declspecs *specs)
{
  /* If a type was specified as a whole, we have no modifiers and are
     done.  */
  ಆದರೆ (specs->type != NULL_ವೃಕ್ಷ)
    {
      gcc_assert (!specs->long_p && !specs->long_long_p && !specs->short_p
		  && !specs->signed_p && !specs->unsigned_p
		  && !specs->complex_p && !specs->c23_auto_p);

      /* Set a dummy type.  */
      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (specs->type) == ERROR_MARK)
        specs->type = integer_type_ಗಂಟು;
      ಹೋಗು handle_postfix_attrs;
    }

  /* If none of "void", "_Bool", "char", "int", "float" or "double"
     has been specified, treat it as "int" unless "_Complex" is
     present and there are no other specifiers.  If we just have
     "_Complex", it is equivalent to "_Complex double", but e.g.
     "_Complex short" is equivalent to "_Complex short int".  */
  ಆದರೆ (specs->typespec_ಶಬ್ದ == cts_none)
    {
      ಆದರೆ (specs->saturating_p)
	{
	  error_at (specs->locations[cdw_saturating],
		    "%<_Sat%> is used without %<_Fract%> or %<_Accum%>");
	  ಆದರೆ (!targetm.fixed_ಬಿಂದು_supported_p ())
	    error_at (specs->locations[cdw_saturating],
		      "fixed-point types not supported for this target");
	  specs->typespec_ಶಬ್ದ = cts_fract;
	}
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->long_p || specs->short_p
	       || specs->signed_p || specs->unsigned_p)
	{
	  specs->typespec_ಶಬ್ದ = cts_int;
	}
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->complex_p)
	{
	  specs->typespec_ಶಬ್ದ = cts_double;
	  pedwarn (specs->locations[cdw_complex], OPT_Wpedantic,
		   "ISO C does not support plain %<complex%> meaning "
		   "%<double complex%>");
	}
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->c23_auto_p)
	{
	  /* Type to be filled in later, including applying postfix
	     attributes.  This warning only actually appears for
	     -Wc11-c23-compat in C23 mode; in older modes, there may
	     be a warning or pedwarn for implicit "int" instead, or
	     other errors for use of auto at file scope.  */
	  pedwarn_c11 (ಒಳಹರಿವು_location, OPT_Wpedantic,
		       "ISO C does not support %<auto%> type deduction "
		       "before C23");
	  ಹಿಂತಿರುಗಿ specs;
	}
      ಇಲ್ಲದಿದ್ದರೆ
	{
	  specs->typespec_ಶಬ್ದ = cts_int;
	  specs->default_int_p = ನಿಜ;
	  /* We don't diagnose this here because grokdeclarator will
	     give more specific diagnostics according to whether it is
	     a function definition.  */
	}
    }

  /* If "signed" was specified, record this to distinguish "int" and
     "signed int" in the case of a bit-field with
     -funsigned-bitfields.  */
  specs->explicit_signed_p = specs->signed_p;

  /* Now compute the actual type.  */
  gcc_assert (!specs->c23_auto_p);
  ಆಯ್ಕೆ (specs->typespec_ಶಬ್ದ)
    {
    ಸ್ಥಿತಿ cts_auto_type:
      gcc_assert (!specs->long_p && !specs->short_p
		  && !specs->signed_p && !specs->unsigned_p
		  && !specs->complex_p);
      /* Type to be filled in later.  */
      ಆದರೆ (specs->postfix_attrs)
	error ("%<__auto_type%> followed by %<[[]]%> attributes");
      ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ cts_void:
      gcc_assert (!specs->long_p && !specs->short_p
		  && !specs->signed_p && !specs->unsigned_p
		  && !specs->complex_p);
      specs->type = void_type_ಗಂಟು;
      ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ cts_bool:
      gcc_assert (!specs->long_p && !specs->short_p
		  && !specs->signed_p && !specs->unsigned_p
		  && !specs->complex_p);
      specs->type = boolean_type_ಗಂಟು;
      ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ cts_char:
      gcc_assert (!specs->long_p && !specs->short_p);
      gcc_assert (!(specs->signed_p && specs->unsigned_p));
      ಆದರೆ (specs->signed_p)
	specs->type = signed_char_type_ಗಂಟು;
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->unsigned_p)
	specs->type = unsigned_char_type_ಗಂಟು;
      ಇಲ್ಲದಿದ್ದರೆ
	specs->type = char_type_ಗಂಟು;
      ಆದರೆ (specs->complex_p)
	{
	  pedwarn (specs->locations[cdw_complex], OPT_Wpedantic,
		   "ISO C does not support complex integer types");
	  specs->type = build_complex_type (specs->type);
	}
      ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ cts_int_n:
      gcc_assert (!specs->long_p && !specs->short_p && !specs->long_long_p);
      gcc_assert (!(specs->signed_p && specs->unsigned_p));
      ಆದರೆ (! int_n_enabled_p[specs->u.int_n_idx])
	specs->type = integer_type_ಗಂಟು;
      ಇಲ್ಲದಿದ್ದರೆ
	specs->type = (specs->unsigned_p
		       ? int_n_trees[specs->u.int_n_idx].unsigned_type
		       : int_n_trees[specs->u.int_n_idx].signed_type);
      ಆದರೆ (specs->complex_p)
	{
	  pedwarn (specs->locations[cdw_complex], OPT_Wpedantic,
		   "ISO C does not support complex integer types");
	  specs->type = build_complex_type (specs->type);
	}
      ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ cts_int:
      gcc_assert (!(specs->long_p && specs->short_p));
      gcc_assert (!(specs->signed_p && specs->unsigned_p));
      ಆದರೆ (specs->long_long_p)
	specs->type = (specs->unsigned_p
		       ? long_long_unsigned_type_ಗಂಟು
		       : long_long_integer_type_ಗಂಟು);
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->long_p)
	specs->type = (specs->unsigned_p
		       ? long_unsigned_type_ಗಂಟು
		       : long_integer_type_ಗಂಟು);
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->short_p)
	specs->type = (specs->unsigned_p
		       ? short_unsigned_type_ಗಂಟು
		       : short_integer_type_ಗಂಟು);
      ಇಲ್ಲದಿದ್ದರೆ
	specs->type = (specs->unsigned_p
		       ? unsigned_type_ಗಂಟು
		       : integer_type_ಗಂಟು);
      ಆದರೆ (specs->complex_p)
	{
	  pedwarn (specs->locations[cdw_complex], OPT_Wpedantic,
		   "ISO C does not support complex integer types");
	  specs->type = build_complex_type (specs->type);
	}
      ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ cts_float:
      gcc_assert (!specs->long_p && !specs->short_p
		  && !specs->signed_p && !specs->unsigned_p);
      specs->type = (specs->complex_p
		     ? complex_float_type_ಗಂಟು
		     : float_type_ಗಂಟು);
      ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ cts_double:
      gcc_assert (!specs->long_long_p && !specs->short_p
		  && !specs->signed_p && !specs->unsigned_p);
      ಆದರೆ (specs->long_p)
	{
	  specs->type = (specs->complex_p
			 ? complex_long_double_type_ಗಂಟು
			 : long_double_type_ಗಂಟು);
	}
      ಇಲ್ಲದಿದ್ದರೆ
	{
	  specs->type = (specs->complex_p
			 ? complex_double_type_ಗಂಟು
			 : double_type_ಗಂಟು);
	}
      ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ cts_floatn_nx:
      gcc_assert (!specs->long_p && !specs->short_p
		  && !specs->signed_p && !specs->unsigned_p);
      ಆದರೆ (FLOATN_NX_TYPE_ಗಂಟು (specs->u.floatn_nx_idx) == NULL_ವೃಕ್ಷ)
	specs->type = integer_type_ಗಂಟು;
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->complex_p)
	specs->type = COMPLEX_FLOATN_NX_TYPE_ಗಂಟು (specs->u.floatn_nx_idx);
      ಇಲ್ಲದಿದ್ದರೆ
	specs->type = FLOATN_NX_TYPE_ಗಂಟು (specs->u.floatn_nx_idx);
      ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ cts_dfloat32:
    ಸ್ಥಿತಿ cts_dfloat64:
    ಸ್ಥಿತಿ cts_dfloat128:
    ಸ್ಥಿತಿ cts_dfloat64x:
      gcc_assert (!specs->long_p && !specs->long_long_p && !specs->short_p
		  && !specs->signed_p && !specs->unsigned_p && !specs->complex_p);
      ಆದರೆ (!targetm.decimal_float_supported_p ())
	specs->type = integer_type_ಗಂಟು;
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->typespec_ಶಬ್ದ == cts_dfloat32)
	specs->type = dfloat32_type_ಗಂಟು;
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->typespec_ಶಬ್ದ == cts_dfloat64)
	specs->type = dfloat64_type_ಗಂಟು;
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->typespec_ಶಬ್ದ == cts_dfloat128)
	specs->type = dfloat128_type_ಗಂಟು;
      ಇಲ್ಲದಿದ್ದರೆ
	specs->type = dfloat64x_type_ಗಂಟು;
      ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ cts_fract:
      gcc_assert (!specs->complex_p);
      ಆದರೆ (!targetm.fixed_ಬಿಂದು_supported_p ())
	specs->type = integer_type_ಗಂಟು;
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->saturating_p)
	{
	  ಆದರೆ (specs->long_long_p)
	    specs->type = specs->unsigned_p
			  ? sat_unsigned_long_long_fract_type_ಗಂಟು
			  : sat_long_long_fract_type_ಗಂಟು;
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->long_p)
	    specs->type = specs->unsigned_p
			  ? sat_unsigned_long_fract_type_ಗಂಟು
			  : sat_long_fract_type_ಗಂಟು;
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->short_p)
	    specs->type = specs->unsigned_p
			  ? sat_unsigned_short_fract_type_ಗಂಟು
			  : sat_short_fract_type_ಗಂಟು;
	  ಇಲ್ಲದಿದ್ದರೆ
	    specs->type = specs->unsigned_p
			  ? sat_unsigned_fract_type_ಗಂಟು
			  : sat_fract_type_ಗಂಟು;
	}
      ಇಲ್ಲದಿದ್ದರೆ
	{
	  ಆದರೆ (specs->long_long_p)
	    specs->type = specs->unsigned_p
			  ? unsigned_long_long_fract_type_ಗಂಟು
			  : long_long_fract_type_ಗಂಟು;
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->long_p)
	    specs->type = specs->unsigned_p
			  ? unsigned_long_fract_type_ಗಂಟು
			  : long_fract_type_ಗಂಟು;
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->short_p)
	    specs->type = specs->unsigned_p
			  ? unsigned_short_fract_type_ಗಂಟು
			  : short_fract_type_ಗಂಟು;
	  ಇಲ್ಲದಿದ್ದರೆ
	    specs->type = specs->unsigned_p
			  ? unsigned_fract_type_ಗಂಟು
			  : fract_type_ಗಂಟು;
	}
      ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ cts_accum:
      gcc_assert (!specs->complex_p);
      ಆದರೆ (!targetm.fixed_ಬಿಂದು_supported_p ())
	specs->type = integer_type_ಗಂಟು;
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->saturating_p)
	{
	  ಆದರೆ (specs->long_long_p)
	    specs->type = specs->unsigned_p
			  ? sat_unsigned_long_long_accum_type_ಗಂಟು
			  : sat_long_long_accum_type_ಗಂಟು;
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->long_p)
	    specs->type = specs->unsigned_p
			  ? sat_unsigned_long_accum_type_ಗಂಟು
			  : sat_long_accum_type_ಗಂಟು;
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->short_p)
	    specs->type = specs->unsigned_p
			  ? sat_unsigned_short_accum_type_ಗಂಟು
			  : sat_short_accum_type_ಗಂಟು;
	  ಇಲ್ಲದಿದ್ದರೆ
	    specs->type = specs->unsigned_p
			  ? sat_unsigned_accum_type_ಗಂಟು
			  : sat_accum_type_ಗಂಟು;
	}
      ಇಲ್ಲದಿದ್ದರೆ
	{
	  ಆದರೆ (specs->long_long_p)
	    specs->type = specs->unsigned_p
			  ? unsigned_long_long_accum_type_ಗಂಟು
			  : long_long_accum_type_ಗಂಟು;
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->long_p)
	    specs->type = specs->unsigned_p
			  ? unsigned_long_accum_type_ಗಂಟು
			  : long_accum_type_ಗಂಟು;
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->short_p)
	    specs->type = specs->unsigned_p
			  ? unsigned_short_accum_type_ಗಂಟು
			  : short_accum_type_ಗಂಟು;
	  ಇಲ್ಲದಿದ್ದರೆ
	    specs->type = specs->unsigned_p
			  ? unsigned_accum_type_ಗಂಟು
			  : accum_type_ಗಂಟು;
	}
      ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ cts_bitint:
      gcc_assert (!specs->long_p && !specs->short_p
		  && !specs->complex_p);
      ಆದರೆ (!specs->unsigned_p && specs->u.bitint_prec == 1 && !flag_isoc2y)
	{
	  error_at (specs->locations[cdw_typespec],
		    "%<signed _BitInt%> argument must be at least 2 "
		    "before C2Y");
	  specs->type = integer_type_ಗಂಟು;
	  ನಿಲ್ಲಿಸು;
	}
      ಆದರೆ (specs->u.bitint_prec == -1)
	specs->type = integer_type_ಗಂಟು;
      ಇಲ್ಲದಿದ್ದರೆ
	{
	  pedwarn_c11 (specs->locations[cdw_typespec], OPT_Wpedantic,
		       "ISO C does not support %<%s_BitInt(%d)%> before C23",
		       specs->unsigned_p ? "unsigned "
		       : specs->signed_p ? "signed " : "",
		       specs->u.bitint_prec);
	  specs->type = build_bitint_type (specs->u.bitint_prec,
					   specs->unsigned_p);
	}
      ನಿಲ್ಲಿಸು;
    ಪೂರ್ವನಿಯೋಜಿತ:
      gcc_unreachable ();
    }
 handle_postfix_attrs:
  ಆದರೆ (specs->type != ಖಾಲಿ)
    {
      specs->postfix_attrs
	= c_warn_type_ಗುಣಲಕ್ಷಣಗಳು (specs->type, specs->postfix_attrs);
      decl_ಗುಣಲಕ್ಷಣಗಳು (&specs->type, specs->postfix_attrs, 0);
      specs->postfix_attrs = NULL_ವೃಕ್ಷ;
    }

  ಹಿಂತಿರುಗಿ specs;
}

/* Perform final processing on one file scope's declarations (or the
   external scope's declarations), GLOBALS.  */

ಸ್ಥಿರ ಶೂನ್ಯ
c_write_global_declarations_1 (ವೃಕ್ಷ globals)
{
  ವೃಕ್ಷ decl;
  ತಾರ್ಕಿಕ reconsider;

  /* Process the decls in the order they were written.  */
  ಗಾಗಿ (decl = globals; decl; decl = DECL_CHAIN (decl))
    {
      /* Check for used but undefined static functions using the C
	 standard's definition of "used", and set TREE_NO_WARNING so
	 that check_global_declaration doesn't repeat the check.  */
      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (decl) == FUNCTION_DECL
	  && DECL_INITIAL (decl) == NULL_ವೃಕ್ಷ
	  && DECL_EXTERNAL (decl)
	  && !ವೃಕ್ಷ_ಬಹಿರಂಗ (decl)
	  && !warning_suppressed_p (decl, OPT_Wunused))
	{
	  ಆದರೆ (C_DECL_ಬಳಸಿದ (decl))
	    {
	      ಆದರೆ (pedwarn (ಒಳಹರಿವು_location, 0, "%q+F used but never defined",
			   decl))
		suppress_warning (decl, OPT_Wunused);
	    }
	  /* For -Wunused-function warn about unused static prototypes.  */
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (warn_ಬಳಸದ_function
		   && ! DECL_ARTIFICIAL (decl)
		   && warning (OPT_Wunused_function,
			       "%q+F declared %<static%> but never defined",
			       decl))
	    suppress_warning (decl, OPT_Wunused);
	}

      wrapup_global_declaration_1 (decl);
    }

  ಮಾಡು
    {
      reconsider = ಸುಳ್ಳು;
      ಗಾಗಿ (decl = globals; decl; decl = DECL_CHAIN (decl))
	reconsider |= wrapup_global_declaration_2 (decl);
    }
  ಆಗ (reconsider);
}

/* Preserve the external declarations scope across a garbage collect.  */
ಸ್ಥಿರ GTY(()) ವೃಕ್ಷ ext_ಖಂಡ;

/* Collect all references relevant to SOURCE_FILE.  */

ಸ್ಥಿರ ಶೂನ್ಯ
collect_all_refs (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಮೂಲ_file)
{
  ವೃಕ್ಷ t;
  ಚಿಹ್ನೆರಹಿತ i;

  FOR_EACH_VEC_ELT (*all_translation_units, i, t)
    collect_ada_nodes (ಖಂಡ_VARS (DECL_INITIAL (t)), ಮೂಲ_file);

  collect_ada_nodes (ಖಂಡ_VARS (ext_ಖಂಡ), ಮೂಲ_file);
}

/* Collect source file references at global level.  */

ಸ್ಥಿರ ಶೂನ್ಯ
collect_ಮೂಲ_refs (ಶೂನ್ಯ)
{
  ವೃಕ್ಷ t;
  ವೃಕ್ಷ decls;
  ವೃಕ್ಷ decl;
  ಚಿಹ್ನೆರಹಿತ i;

  FOR_EACH_VEC_ELT (*all_translation_units, i, t)
    {
      decls = DECL_INITIAL (t);
      ಗಾಗಿ (decl = ಖಂಡ_VARS (decls); decl; decl = ವೃಕ್ಷ_CHAIN (decl))
	ಆದರೆ (!DECL_IS_UNDECLARED_BUILTIN (decl))
	  collect_ಮೂಲ_ref (DECL_ಮೂಲ_FILE (decl));
    }

  ಗಾಗಿ (decl = ಖಂಡ_VARS (ext_ಖಂಡ); decl; decl = ವೃಕ್ಷ_CHAIN (decl))
    ಆದರೆ (!DECL_IS_UNDECLARED_BUILTIN (decl))
      collect_ಮೂಲ_ref (DECL_ಮೂಲ_FILE (decl));
}

/* Free attribute access data that are not needed by the middle end. */

ಸ್ಥಿರ ಶೂನ್ಯ
free_attr_access_ದತ್ತಾಂಶ ()
{
  ರಚನೆ cgraph_ಗಂಟು *n;

  /* Iterate over all functions declared in the translation unit.  */
  FOR_EACH_FUNCTION (n)
    {
      ಗಾಗಿ (ವೃಕ್ಷ parm = DECL_ARGUMENTS (n->decl); parm; parm = ವೃಕ್ಷ_CHAIN (parm))
	ಆದರೆ (ವೃಕ್ಷ attrs = DECL_ಗುಣಲಕ್ಷಣಗಳು (parm))
	  attr_access::free_lang_ದತ್ತಾಂಶ (attrs);

      ವೃಕ್ಷ fntype = ವೃಕ್ಷ_TYPE (n->decl);
      ಆದರೆ (!fntype || fntype == error_mark_ಗಂಟು)
	ಮುಂದುವರಿ;
      ವೃಕ್ಷ attrs = TYPE_ಗುಣಲಕ್ಷಣಗಳು (fntype);
      ಆದರೆ (!attrs)
	ಮುಂದುವರಿ;

      attr_access::free_lang_ದತ್ತಾಂಶ (attrs);
    }
}

/* Perform any final parser cleanups and generate initial debugging
   information.  */

ಶೂನ್ಯ
c_parse_final_cleanups (ಶೂನ್ಯ)
{
  ವೃಕ್ಷ t;
  ಚಿಹ್ನೆರಹಿತ i;

  /* We don't want to do this if generating a PCH.  */
  ಆದರೆ (pch_file)
    ಹಿಂತಿರುಗಿ;

  timevar_stop (TV_PHASE_PARSING);
  timevar_ಆರಂಭ (TV_PHASE_DEFERRED);

  /* Do the Objective-C stuff.  This is where all the Objective-C
     module stuff gets generated (symtab, class/protocol/selector
     lists etc).  */
  ಆದರೆ (c_dialect_objc ())
    objc_write_global_declarations ();

  /* Close the external scope.  */
  ext_ಖಂಡ = ತೆಗೆ_scope ();
  external_scope = 0;
  gcc_assert (!current_scope);

  /* Handle -fdump-ada-spec[-slim]. */
  ಆದರೆ (flag_dump_ada_spec || flag_dump_ada_spec_slim)
    {
      /* Build a table of files to generate specs for */
      collect_ಮೂಲ_ref (main_ಒಳಹರಿವು_filename);
      ಆದರೆ (!flag_dump_ada_spec_slim)
	collect_ಮೂಲ_refs ();

      dump_ada_specs (collect_all_refs, ಖಾಲಿ);
    }

  /* Process all file scopes in this compilation, and the external_scope,
     through wrapup_global_declarations.  */
  FOR_EACH_VEC_ELT (*all_translation_units, i, t)
    c_write_global_declarations_1 (ಖಂಡ_VARS (DECL_INITIAL (t)));
  c_write_global_declarations_1 (ಖಂಡ_VARS (ext_ಖಂಡ));

  /* Call this to set cpp_implicit_aliases_done on all nodes.  This is
     important for function multiversioning aliases to get resolved.  */
  symtab->process_same_body_aliases ();

  ಆದರೆ (!ಒಳ_lto_p)
    free_attr_access_ದತ್ತಾಂಶ ();

  timevar_stop (TV_PHASE_DEFERRED);
  timevar_ಆರಂಭ (TV_PHASE_PARSING);

  ext_ಖಂಡ = ಖಾಲಿ;
}

/* Register reserved keyword WORD as qualifier for address space AS.  */

ಶೂನ್ಯ
c_ರಿಜಿಸ್ಟರ್_addr_space (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಶಬ್ದ, addr_space_t as)
{
  ಪೂರ್ಣಾಂಕ rid = RID_ಮೊದಲ_ADDR_SPACE + as;
  ವೃಕ್ಷ id;

  /* Address space qualifiers are only supported
     in C with GNU extensions enabled.  */
  ಆದರೆ (c_dialect_objc () || flag_no_asm)
    ಹಿಂತಿರುಗಿ;

  id = get_identifier (ಶಬ್ದ);
  C_ಗಣ_RID_ಸಂಕೇತ (id, rid);
  C_IS_RESERVED_ಶಬ್ದ (id) = 1;
  ridpointers [rid] = id;
}

/* Return identifier to look up for omp declare reduction.  */

ವೃಕ್ಷ
c_omp_reduction_id (ಎಣಿಕೆ ವೃಕ್ಷ_ಸಂಕೇತ_2 reduction_ಸಂಕೇತ, ವೃಕ್ಷ reduction_id)
{
  ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *p = ಖಾಲಿ;
  ಆಯ್ಕೆ (reduction_ಸಂಕೇತ)
    {
    ಸ್ಥಿತಿ PLUS_ಅಭಿವ್ಯಕ್ತಿ: p = "+"; ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ MULT_ಅಭಿವ್ಯಕ್ತಿ: p = "*"; ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ MINUS_ಅಭಿವ್ಯಕ್ತಿ: p = "-"; ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ ಬಿಟ್_AND_ಅಭಿವ್ಯಕ್ತಿ: p = "&"; ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ ಬಿಟ್_XOR_ಅಭಿವ್ಯಕ್ತಿ: p = "^"; ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ ಬಿಟ್_IOR_ಅಭಿವ್ಯಕ್ತಿ: p = "|"; ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ TRUTH_ANDIF_ಅಭಿವ್ಯಕ್ತಿ: p = "&&"; ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ TRUTH_ORIF_ಅಭಿವ್ಯಕ್ತಿ: p = "||"; ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ MIN_ಅಭಿವ್ಯಕ್ತಿ: p = "min"; ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ MAX_ಅಭಿವ್ಯಕ್ತಿ: p = "max"; ನಿಲ್ಲಿಸು;
    ಪೂರ್ವನಿಯೋಜಿತ:
      ನಿಲ್ಲಿಸು;
    }

  ಆದರೆ (p == ಖಾಲಿ)
    {
      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (reduction_id) != IDENTIFIER_ಗಂಟು)
	ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
      p = IDENTIFIER_ಸೂಚಕ (reduction_id);
    }

  ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ ಪೂರ್ವಪ್ರತ್ಯಯ[] = "omp declare reduction ";
  ಗಾತ್ರ_t lenp = ಗಾತ್ರ (ಪೂರ್ವಪ್ರತ್ಯಯ);
  ಗಾತ್ರ_t len = ಅಕ್ಷರಸರಣಿ_ಉದ್ದ (p);
  ಅಕ್ಷರ *name = XALLOCAVEC (ಅಕ್ಷರ, lenp + len);
  ಸ್ಮರಣೆ_ನಕಲು (name, ಪೂರ್ವಪ್ರತ್ಯಯ, lenp - 1);
  ಸ್ಮರಣೆ_ನಕಲು (name + lenp - 1, p, len + 1);
  ಹಿಂತಿರುಗಿ get_identifier (name);
}

/* Lookup REDUCTION_ID in the current scope, or create an artificial
   VAR_DECL, bind it into the current scope and return it.  */

ವೃಕ್ಷ
c_omp_reduction_decl (ವೃಕ್ಷ reduction_id)
{
  ರಚನೆ c_binding *b = I_ಚಿಹ್ನೆ_BINDING (reduction_id);
  ಆದರೆ (b != ಖಾಲಿ && B_ಒಳ_CURRENT_SCOPE (b))
    ಹಿಂತಿರುಗಿ b->decl;

  ವೃಕ್ಷ decl = build_decl (BUILTINS_LOCATION, VAR_DECL,
			  reduction_id, integer_type_ಗಂಟು);
  DECL_ARTIFICIAL (decl) = 1;
  DECL_EXTERNAL (decl) = 1;
  ವೃಕ್ಷ_STATIC (decl) = 1;
  ವೃಕ್ಷ_ಬಹಿರಂಗ (decl) = 0;
  bind (reduction_id, decl, current_scope, ನಿಜ, ಸುಳ್ಳು, BUILTINS_LOCATION);
  ಹಿಂತಿರುಗಿ decl;
}

/* Lookup REDUCTION_ID in the first scope where it has entry for TYPE.  */

ವೃಕ್ಷ
c_omp_reduction_lookup (ವೃಕ್ಷ reduction_id, ವೃಕ್ಷ type)
{
  ರಚನೆ c_binding *b = I_ಚಿಹ್ನೆ_BINDING (reduction_id);
  ಆಗ (b)
    {
      ವೃಕ್ಷ t;
      ಗಾಗಿ (t = DECL_INITIAL (b->decl); t; t = ವೃಕ್ಷ_CHAIN (t))
	ಆದರೆ (comptypes (ವೃಕ್ಷ_PURPOSE (t), type))
	  ಹಿಂತಿರುಗಿ ವೃಕ್ಷ_ಮೌಲ್ಯ (t);
      b = b->shadowed;
    }
  ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
}

/* Helper function called via walk_tree, to diagnose invalid
   #pragma omp declare reduction combiners or initializers.  */

ವೃಕ್ಷ
c_check_omp_declare_reduction_r (ವೃಕ್ಷ *tp, ಪೂರ್ಣಾಂಕ *, ಶೂನ್ಯ *ದತ್ತಾಂಶ)
{
  ವೃಕ್ಷ *vars = (ವೃಕ್ಷ *) ದತ್ತಾಂಶ;
  ಆದರೆ (SSA_VAR_P (*tp)
      && !DECL_ARTIFICIAL (*tp)
      && *tp != vars[0]
      && *tp != vars[1])
    {
      location_t loc = DECL_ಮೂಲ_LOCATION (vars[0]);
      ಆದರೆ (strcmp (IDENTIFIER_ಸೂಚಕ (DECL_NAME (vars[0])), "omp_out") == 0)
	error_at (loc, "%<#pragma omp declare reduction%> combiner refers to "
		       "variable %qD which is not %<omp_out%> nor %<omp_in%>",
		  *tp);
      ಇಲ್ಲದಿದ್ದರೆ
	error_at (loc, "%<#pragma omp declare reduction%> initializer refers "
		       "to variable %qD which is not %<omp_priv%> nor "
		       "%<omp_orig%>",
		  *tp);
      ಹಿಂತಿರುಗಿ *tp;
    }
  ಹಿಂತಿರುಗಿ NULL_ವೃಕ್ಷ;
}

/* Return identifier to look up for omp declare mapper.  */

ವೃಕ್ಷ
c_omp_mapper_id (ವೃಕ್ಷ mapper_id)
{
  ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *p = ಖಾಲಿ;

  ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ ಪೂರ್ವಪ್ರತ್ಯಯ[] = "omp declare mapper ";

  ಆದರೆ (mapper_id == NULL_ವೃಕ್ಷ)
    p = "<default>";
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (mapper_id) == IDENTIFIER_ಗಂಟು)
    p = IDENTIFIER_ಸೂಚಕ (mapper_id);
  ಇಲ್ಲದಿದ್ದರೆ
    ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;

  ಗಾತ್ರ_t lenp = ಗಾತ್ರ (ಪೂರ್ವಪ್ರತ್ಯಯ);
  ಗಾತ್ರ_t len = ಅಕ್ಷರಸರಣಿ_ಉದ್ದ (p);
  ಅಕ್ಷರ *name = XALLOCAVEC (ಅಕ್ಷರ, lenp + len);
  ಸ್ಮರಣೆ_ನಕಲು (name, ಪೂರ್ವಪ್ರತ್ಯಯ, lenp - 1);
  ಸ್ಮರಣೆ_ನಕಲು (name + lenp - 1, p, len + 1);
  ಹಿಂತಿರುಗಿ get_identifier (name);
}

/* Lookup MAPPER_ID in the current scope, or create an artificial
   VAR_DECL, bind it into the current scope and return it.  */

ವೃಕ್ಷ
c_omp_mapper_decl (ವೃಕ್ಷ mapper_id)
{
  ರಚನೆ c_binding *b = I_ಚಿಹ್ನೆ_BINDING (mapper_id);
  ಆದರೆ (b != ಖಾಲಿ && B_ಒಳ_CURRENT_SCOPE (b))
    ಹಿಂತಿರುಗಿ b->decl;

  ವೃಕ್ಷ decl = build_decl (BUILTINS_LOCATION, VAR_DECL,
			  mapper_id, integer_type_ಗಂಟು);
  DECL_ARTIFICIAL (decl) = 1;
  DECL_EXTERNAL (decl) = 1;
  ವೃಕ್ಷ_STATIC (decl) = 1;
  ವೃಕ್ಷ_ಬಹಿರಂಗ (decl) = 0;
  bind (mapper_id, decl, current_scope, ನಿಜ, ಸುಳ್ಳು, BUILTINS_LOCATION);
  ಹಿಂತಿರುಗಿ decl;
}

/* Lookup MAPPER_ID in the first scope where it has entry for TYPE.  */

ವೃಕ್ಷ
c_omp_mapper_lookup (ವೃಕ್ಷ mapper_id, ವೃಕ್ಷ type)
{
  ಆದರೆ (!ದಾಖಲೆ_OR_UNION_TYPE_P (type))
    ಹಿಂತಿರುಗಿ NULL_ವೃಕ್ಷ;

  mapper_id = c_omp_mapper_id (mapper_id);

  ರಚನೆ c_binding *b = I_ಚಿಹ್ನೆ_BINDING (mapper_id);
  ಆಗ (b)
    {
      ವೃಕ್ಷ t;
      ಗಾಗಿ (t = DECL_INITIAL (b->decl); t; t = ವೃಕ್ಷ_CHAIN (t))
	ಆದರೆ (comptypes (ವೃಕ್ಷ_PURPOSE (t), type))
	  ಹಿಂತಿರುಗಿ ವೃಕ್ಷ_ಮೌಲ್ಯ (t);
      b = b->shadowed;
    }
  ಹಿಂತಿರುಗಿ NULL_ವೃಕ್ಷ;
}

/* For C, we record a pointer to the mapper itself without wrapping it in an
   artificial function or similar.  So, just return it.  */

ವೃಕ್ಷ
c_omp_ಹೊರತೆಗೆ_mapper_directive (ವೃಕ್ಷ mapper)
{
  ಹಿಂತಿರುಗಿ mapper;
}

/* For now we can handle singleton OMP_ARRAY_SECTIONs with custom mappers, but
   nothing more complicated.  */

ವೃಕ್ಷ
c_omp_map_array_section (location_t loc, ವೃಕ್ಷ t)
{
  ವೃಕ್ಷ ಕೆಳಗಿನ = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (t, 1);
  ವೃಕ್ಷ len = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (t, 2);

  ಆದರೆ (len && integer_onep (len))
    {
      t = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (t, 0);

      ಆದರೆ (!ಕೆಳಗಿನ)
	ಕೆಳಗಿನ = integer_zero_ಗಂಟು;

      t = build_array_ref (loc, t, ಕೆಳಗಿನ);
    }

  ಹಿಂತಿರುಗಿ t;
}

/* Helper function for below function.  */

ಸ್ಥಿರ ವೃಕ್ಷ
c_omp_ಪರಿಶೀಲನೆ_mapper_bindings_r (ವೃಕ್ಷ *tp, ಪೂರ್ಣಾಂಕ *walk_subtrees, ಶೂನ್ಯ *ptr)
{
  ವೃಕ್ಷ t = *tp;
  omp_mapper_list<ವೃಕ್ಷ> *mlist = (omp_mapper_list<ವೃಕ್ಷ> *) ptr;
  ವೃಕ್ಷ aggr_type = NULL_ವೃಕ್ಷ;

  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (t) == SIZEOF_ಅಭಿವ್ಯಕ್ತಿ
      || ವೃಕ್ಷ_ಸಂಕೇತ (t) == ALIGNOF_ಅಭಿವ್ಯಕ್ತಿ)
    {
      *walk_subtrees = 0;
      ಹಿಂತಿರುಗಿ NULL_ವೃಕ್ಷ;
    }

  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (t) == OMP_CLAUSE)
    ಹಿಂತಿರುಗಿ NULL_ವೃಕ್ಷ;

  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (t) == COMPONENT_REF
      && ದಾಖಲೆ_OR_UNION_TYPE_P (ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (t, 0))))
    aggr_type = ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (t, 0));
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ ((ವೃಕ್ಷ_ಸಂಕೇತ (t) == VAR_DECL
	    || ವೃಕ್ಷ_ಸಂಕೇತ (t) == PARM_DECL
	    || ವೃಕ್ಷ_ಸಂಕೇತ (t) == ಫಲಿತಾಂಶ_DECL)
	   && ದಾಖಲೆ_OR_UNION_TYPE_P (ವೃಕ್ಷ_TYPE (t)))
    aggr_type = ವೃಕ್ಷ_TYPE (t);

  ಆದರೆ (aggr_type)
    {
      ವೃಕ್ಷ mapper_fn = c_omp_mapper_lookup (NULL_ವೃಕ್ಷ, aggr_type);
      ಆದರೆ (mapper_fn)
	mlist->ಕೂಡಿಸು_mapper (NULL_ವೃಕ್ಷ, aggr_type, mapper_fn);
    }

  ಹಿಂತಿರುಗಿ NULL_ವೃಕ್ಷ;
}

/* Scan an offload region's body, and record uses of struct- or union-typed
   variables.  Add _mapper_binding_ fake clauses to *CLAUSES_PTR.  */

ಶೂನ್ಯ
c_omp_ಪರಿಶೀಲನೆ_mapper_bindings (location_t loc, ವೃಕ್ಷ *clauses_ptr, ವೃಕ್ಷ body)
{
  hash_ಗಣ<omp_name_type<ವೃಕ್ಷ>> ನೋಡಿದ_types;
  auto_vec<ವೃಕ್ಷ> mappers;
  omp_mapper_list<ವೃಕ್ಷ> mlist (&ನೋಡಿದ_types, &mappers);

  walk_ವೃಕ್ಷ_without_duplicates (&body, c_omp_ಪರಿಶೀಲನೆ_mapper_bindings_r, &mlist);

  ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ i;
  ವೃಕ್ಷ mapper;
  FOR_EACH_VEC_ELT (mappers, i, mapper)
    c_omp_ಕಂಡುಹಿಡಿ_nested_mappers (&mlist, mapper);

  FOR_EACH_VEC_ELT (mappers, i, mapper)
    {
      ಆದರೆ (mapper == error_mark_ಗಂಟು)
	ಮುಂದುವರಿ;
      ವೃಕ್ಷ mapper_name = OMP_DECLARE_MAPPER_ID (mapper);
      ವೃಕ್ಷ decl = OMP_DECLARE_MAPPER_DECL (mapper);

      ವೃಕ್ಷ c = build_omp_clause (loc, OMP_CLAUSE__MAPPER_BINDING_);
      OMP_CLAUSE__MAPPER_BINDING__ID (c) = mapper_name;
      OMP_CLAUSE__MAPPER_BINDING__DECL (c) = decl;
      OMP_CLAUSE__MAPPER_BINDING__MAPPER (c) = mapper;

      OMP_CLAUSE_CHAIN (c) = *clauses_ptr;
      *clauses_ptr = c;
    }
}

ತಾರ್ಕಿಕ
c_check_ಒಳ_current_scope (ವೃಕ್ಷ decl)
{
  ರಚನೆ c_binding *b = I_ಚಿಹ್ನೆ_BINDING (DECL_NAME (decl));
  ಹಿಂತಿರುಗಿ b != ಖಾಲಿ && B_ಒಳ_CURRENT_SCOPE (b);
}

/* Search for loop or switch names.  BEFORE_LABELS is last statement before
   possible labels and SWITCH_P true for a switch, false for loops.
   Searches through last statements in cur_stmt_list, stops when seeing
   BEFORE_LABELs, or statement other than LABEL_EXPR or CASE_LABEL_EXPR.
   Returns number of loop/switch names found and if any are found, sets
   *LAST_P to the canonical loop/switch name LABEL_DECL.  */

ಪೂರ್ಣಾಂಕ
c_get_loop_ಹೆಸರುಗಳು (ವೃಕ್ಷ before_labels, ತಾರ್ಕಿಕ switch_p, ವೃಕ್ಷ *ಕೊನೆಯ_p)
{
  *ಕೊನೆಯ_p = NULL_ವೃಕ್ಷ;
  ಆದರೆ (!building_stmt_list_p ()
      || !STATEMENT_LIST_HAS_LABEL (cur_stmt_list)
      || before_labels == void_list_ಗಂಟು)
    ಹಿಂತಿರುಗಿ 0;

  ಪೂರ್ಣಾಂಕ ret = 0;
  ವೃಕ್ಷ ಕೊನೆಯ = NULL_ವೃಕ್ಷ;
  ಗಾಗಿ (ವೃಕ್ಷ_stmt_iterator tsi = tsi_ಕೊನೆಯ (cur_stmt_list);
       !tsi_ಕೊನೆ_p (tsi); tsi_prev (&tsi))
    {
      ವೃಕ್ಷ stmt = tsi_stmt (tsi);
      ಆದರೆ (stmt == before_labels)
	ನಿಲ್ಲಿಸು;
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (stmt) == LABEL_ಅಭಿವ್ಯಕ್ತಿ)
	{
	  ಆದರೆ (ಕೊನೆಯ == NULL_ವೃಕ್ಷ)
	    ಕೊನೆಯ = LABEL_ಅಭಿವ್ಯಕ್ತಿ_LABEL (stmt);
	  ಇಲ್ಲದಿದ್ದರೆ
	    {
	      loop_ಹೆಸರುಗಳು.ಸುರಕ್ಷಿತ_ತಳ್ಳು (LABEL_ಅಭಿವ್ಯಕ್ತಿ_LABEL (stmt));
	      ++ret;
	    }
	}
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (stmt) != CASE_LABEL_ಅಭಿವ್ಯಕ್ತಿ
	       && ವೃಕ್ಷ_ಸಂಕೇತ (stmt) != DEBUG_BEGIN_STMT)
	ನಿಲ್ಲಿಸು;
    }
  ಆದರೆ (ಕೊನೆಯ)
    {
      ಆದರೆ (switch_p)
	C_DECL_SWITCH_NAME (ಕೊನೆಯ) = 1;
      ಇಲ್ಲದಿದ್ದರೆ
	C_DECL_LOOP_NAME (ಕೊನೆಯ) = 1;
      loop_ಹೆಸರುಗಳು.ಸುರಕ್ಷಿತ_ತಳ್ಳು (ಕೊನೆಯ);
      ++ret;
      ಆದರೆ (loop_ಹೆಸರುಗಳು.ಉದ್ದಳತೆ () > 16)
	{
	  ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ ಮೊದಲ = 0, i;
	  ವೃಕ್ಷ l, c = NULL_ವೃಕ್ಷ;
	  ಆದರೆ (loop_ಹೆಸರುಗಳು_hash == ಖಾಲಿ)
	    loop_ಹೆಸರುಗಳು_hash = ಹೊಸ decl_ವೃಕ್ಷ_map (ret);
	  ಇಲ್ಲದಿದ್ದರೆ
	    ಮೊದಲ = loop_ಹೆಸರುಗಳು.ಉದ್ದಳತೆ () - ret;
	  FOR_EACH_VEC_ELT_ಹಿಮ್ಮುಖ (loop_ಹೆಸರುಗಳು, i, l)
	    {
	      ಆದರೆ (C_DECL_LOOP_NAME (l) || C_DECL_SWITCH_NAME (l))
		c = l;
	      gcc_checking_assert (c);
	      loop_ಹೆಸರುಗಳು_hash->put (l, c);
	      ಆದರೆ (i == ಮೊದಲ)
		ನಿಲ್ಲಿಸು;
	    }
	}
      *ಕೊನೆಯ_p = ಕೊನೆಯ;
    }
  ಹಿಂತಿರುಗಿ ret;
}

/* Undoes what get_loop_names did when it returned NUM_NAMES.  */

ಶೂನ್ಯ
c_release_loop_ಹೆಸರುಗಳು (ಪೂರ್ಣಾಂಕ ಅಂಕೆ_ಹೆಸರುಗಳು)
{
  ಚಿಹ್ನೆರಹಿತ len = loop_ಹೆಸರುಗಳು.ಉದ್ದಳತೆ () - ಅಂಕೆ_ಹೆಸರುಗಳು;
  ಆದರೆ (loop_ಹೆಸರುಗಳು_hash)
    {
      ಆದರೆ (len <= 16)
	{
	  ಅಳಿಸು loop_ಹೆಸರುಗಳು_hash;
	  loop_ಹೆಸರುಗಳು_hash = ಖಾಲಿ;
	}
      ಇಲ್ಲದಿದ್ದರೆ
	{
	  ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ i;
	  ವೃಕ್ಷ l;
	  FOR_EACH_VEC_ELT_ಹಿಮ್ಮುಖ (loop_ಹೆಸರುಗಳು, i, l)
	    {
	      loop_ಹೆಸರುಗಳು_hash->remove (l);
	      ಆದರೆ (i == len)
		ನಿಲ್ಲಿಸು;
	    }
	}
    }
  loop_ಹೆಸರುಗಳು.truncate (len);
}

/* Finish processing of break or continue identifier operand.
   NAME is the identifier operand of break or continue and
   IS_BREAK is true iff it is break stmt.  Returns the operand
   to use for BREAK_STMT or CONTINUE_STMT, either NULL_TREE or
   canonical loop/switch name LABEL_DECL.  */

ವೃಕ್ಷ
c_ಮುಕ್ತಾಯ_bc_name (location_t loc, ವೃಕ್ಷ name, ತಾರ್ಕಿಕ is_break)
{
  ವೃಕ್ಷ label = NULL_ವೃಕ್ಷ, lab;
  pedwarn_c23 (loc, OPT_Wpedantic,
	       "ISO C does not support %qs statement with an identifier "
	       "operand before C2Y", is_break ? "break" : "continue");

  /* If I_LABEL_DECL is NULL or not from current function, don't waste time
     trying to find it among loop_names, it can't be there.  */
  ಆದರೆ (!loop_ಹೆಸರುಗಳು.is_ಖಾಲಿಗಳು ()
      && current_function_scope
      && (lab = I_LABEL_DECL (name))
      && DECL_CONTEXT (lab) == current_function_decl)
    {
      ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ i;
      ವೃಕ್ಷ l, c = NULL_ವೃಕ್ಷ;
      ಆದರೆ (loop_ಹೆಸರುಗಳು_hash)
	{
	  ಆದರೆ (ವೃಕ್ಷ *val = loop_ಹೆಸರುಗಳು_hash->get (lab))
	    label = *val;
	}
      ಇಲ್ಲದಿದ್ದರೆ
	FOR_EACH_VEC_ELT_ಹಿಮ್ಮುಖ (loop_ಹೆಸರುಗಳು, i, l)
	  {
	    ಆದರೆ (C_DECL_LOOP_NAME (l) || C_DECL_SWITCH_NAME (l))
	      c = l;
	    gcc_checking_assert (c);
	    ಆದರೆ (l == lab)
	      {
		label = c;
		ನಿಲ್ಲಿಸು;
	      }
	  }
      ಆದರೆ (label)
	ವೃಕ್ಷ_ಬಳಸಿದ (lab) = 1;
    }
  ಆದರೆ (label == NULL_ವೃಕ್ಷ)
    {
      auto_vec<ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *> candidates;
      ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ i;
      ವೃಕ್ಷ l, c = NULL_ವೃಕ್ಷ;
      FOR_EACH_VEC_ELT_ಹಿಮ್ಮುಖ (loop_ಹೆಸರುಗಳು, i, l)
	{
	  ಆದರೆ (C_DECL_LOOP_NAME (l) || C_DECL_SWITCH_NAME (l))
	    c = l;
	  gcc_checking_assert (c);
	  ಆದರೆ (is_break || C_DECL_LOOP_NAME (c))
	    candidates.ಸುರಕ್ಷಿತ_ತಳ್ಳು (IDENTIFIER_ಸೂಚಕ (DECL_NAME (l)));
	}
      ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *hint = ಕಂಡುಹಿಡಿ_closest_string (IDENTIFIER_ಸೂಚಕ (name),
					      &candidates);
      ಆದರೆ (hint)
	{
	  gcc_rich_location richloc (loc);
	  richloc.ಕೂಡಿಸು_fixit_replace (hint);
	  ಆದರೆ (is_break)
	    error_at (&richloc, "%<break%> statement operand %qE does not "
				"refer to a named loop or %<switch%>; "
				"did you mean %qs?", name, hint);
	  ಇಲ್ಲದಿದ್ದರೆ
	    error_at (&richloc, "%<continue%> statement operand %qE does not "
				"refer to a named loop; did you mean %qs?",
		      name, hint);
	}
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (is_break)
	error_at (loc, "%<break%> statement operand %qE does not refer to a "
		       "named loop or %<switch%>", name);
      ಇಲ್ಲದಿದ್ದರೆ
	error_at (loc, "%<continue%> statement operand %qE does not refer to "
		       "a named loop", name);
    }
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!C_DECL_LOOP_NAME (label) && !is_break)
    {
      auto_diagnostic_ಗುಂಪು d;
      error_at (loc, "%<continue%> statement operand %qE refers to a named "
		     "%<switch%>", name);
      inform (DECL_ಮೂಲ_LOCATION (label), "%<switch%> name defined here");
      label = NULL_ವೃಕ್ಷ;
    }
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!C_DECL_LOOP_SWITCH_NAME_VALID (label))
    {
      auto_diagnostic_ಗುಂಪು d;
      ಆದರೆ (C_DECL_LOOP_NAME (label))
	{
	  error_at (loc, "%qs statement operand %qE refers to a loop outside "
			 "of its body", is_break ? "break" : "continue", name);
	  inform (DECL_ಮೂಲ_LOCATION (label), "loop name defined here");
	}
      ಇಲ್ಲದಿದ್ದರೆ
	{
	  error_at (loc, "%<break%> statement operand %qE refers to a "
			 "%<switch%> outside of its body", name);
	  inform (DECL_ಮೂಲ_LOCATION (label),
		  "%<switch%> name defined here");
	}
      label = NULL_ವೃಕ್ಷ;
    }
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (label == loop_ಹೆಸರುಗಳು.ಕೊನೆಯ () && (ಒಳ_statement & ಒಳ_NAMED_STMT) != 0)
    /* If it is just a fancy reference to the innermost construct, handle it
       just like break; or continue; though tracking cheaply what is the
       innermost loop for continue when nested in switches would require
       another global variable and updating it.  */
    label = NULL_ವೃಕ್ಷ;
  ಇಲ್ಲದಿದ್ದರೆ
    C_DECL_LOOP_SWITCH_NAME_ಬಳಸಿದ (label) = 1;
  ಹಿಂತಿರುಗಿ label;
}

#ಅನ್ತರ್ಭಾವ "gt-c-c-decl.h"
