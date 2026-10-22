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
#define INCLUDE_STRING
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
ಗಣನಾ decl_context
{ NORMAL,			/* Ordinary declaration */
  FUNCDEF,			/* Function definition */
  PARM,				/* Declaration of parm before function body */
  FIELD,			/* Declaration inside struct or union */
  TYPENAME,			/* Typename (inside cast or sizeof)  */
  GENERIC_ASSOC };		/* Typename in generic association  */

/* States indicating how grokdeclarator() should handle declspecs marked
   with __attribute__((deprecated)) or __attribute__((unavailable)).
   An object declared as __attribute__((unavailable)) should suppress
   any reports of being declared  with unavailable or deprecated items.
   An object declared as __attribute__((deprecated)) should suppress
   warnings of uses of other deprecated items.  */

ಗಣನಾ deprecated_states {
  DEPRECATED_NORMAL,
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

ಸ್ಥಿರ ತಾರ್ಕಿಕ current_function_prototype_built_in;

/* The argument type information of this prototype.  */

ಸ್ಥಿರ ವೃಕ್ಷ current_function_prototype_arg_types;

/* The argument information structure for the function currently being
   defined.  */

ಸ್ಥಿರ ಸಂರಚನಾ c_arg_info *current_function_arg_info;

/* The obstack on which parser and related data structures, which are
   not live beyond their top-level declaration or definition, are
   allocated.  */
ಸಂರಚನಾ obstack parser_obstack;

/* The current statement tree.  */

ಸ್ಥಿರ GTY(()) ಸಂರಚನಾ stmt_ವೃಕ್ಷ_s c_stmt_ವೃಕ್ಷ;

/* Zero if we are not in an iteration or switch statement, otherwise
   a bitmask.  See bitmask definitions in c-tree.h.  */
unsigned ವರ್ಣ in_statement;

/* A list of decls to be made automatically visible in each file scope.  */
ಸ್ಥಿರ GTY(()) ವೃಕ್ಷ visible_builtins;

/* Set to 0 at beginning of a function definition, set to 1 if
   a return statement that specifies a return value is seen.  */

ಪೂರ್ಣಾಙ್ಕ current_function_returns_ಮೌಲ್ಯ;

/* Set to 0 at beginning of a function definition, set to 1 if
   a return statement with no argument is seen.  */

ಪೂರ್ಣಾಙ್ಕ current_function_returns_null;

/* Set to 0 at beginning of a function definition, set to 1 if
   a call to a noreturn function is seen.  */

ಪೂರ್ಣಾಙ್ಕ current_function_returns_abnormally;

/* Set to nonzero by `grokdeclarator' for a function
   whose return type is defaulted, if warnings for this are desired.  */

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ warn_about_return_type;

/* Nonzero when the current toplevel function contains a declaration
   of a nested function which is never defined.  */

ಸ್ಥಿರ ತಾರ್ಕಿಕ undef_nested_function;

/* Vector of implicit "omp declare target" attributes to be added into
   the attribute lists.  */
vec<c_omp_declare_target_attr, va_gc> *current_omp_declare_target_attribute;

/* Vector of
   #pragma omp begin assumes ... #pragma omp end assumes regions
   we are in.  */
vec<c_omp_begin_assumes_data, va_gc> *current_omp_begin_assumes;

/* Vector of "omp begin/end declare variant" blocks we are in.  */
vec<c_omp_declare_variant_attr, va_gc> *current_omp_declare_variant_attribute;

/* Vector of loop names with C_DECL_LOOP_NAME or C_DECL_SWITCH_NAME marked
   LABEL_DECL as the last and canonical for each loop or switch.  */
ಸ್ಥಿರ vec<ವೃಕ್ಷ> loop_names;

/* Hash table mapping LABEL_DECLs to the canonical LABEL_DECLs if LOOP_NAMES
   vector becomes too long.  */
ಸ್ಥಿರ decl_ವೃಕ್ಷ_map *loop_names_hash;

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

ಸಂರಚನಾ GTY((chain_next ("%h.prev"))) c_binding {
  ಸಙ್ಘ GTY(()) {		/* first so GTY desc can use decl */
    ವೃಕ್ಷ GTY((tag ("0"))) type; /* the type in this scope */
    ಸಂರಚನಾ c_label_vars * GTY((tag ("1"))) label; /* for warnings */
  } GTY((desc ("TREE_CODE (%0.decl) == LABEL_DECL"))) u;
  ವೃಕ್ಷ decl;			/* the decl bound */
  ವೃಕ್ಷ id;			/* the identifier it's bound to */
  ಸಂರಚನಾ c_binding *prev;	/* the previous decl in this scope */
  ಸಂರಚನಾ c_binding *shadowed;	/* the innermost decl shadowed by this one */
  unsigned ಪೂರ್ಣಾಙ್ಕ depth : 28;      /* depth of this scope */
  ತಾರ್ಕಿಕ invisible : 1;  /* normal lookup should ignore this binding */
  ತಾರ್ಕಿಕ nested : 1;     /* do not set DECL_CONTEXT when popping */
  ತಾರ್ಕಿಕ inner_comp : 1; /* incomplete array completed in inner scope */
  ತಾರ್ಕಿಕ in_struct : 1;	/* currently defined as struct field */
  location_t locus;		/* location for nested bindings */
};
#define B_IN_SCOPE(b1, b2) ((b1)->depth == (b2)->depth)
#define B_IN_CURRENT_SCOPE(b) ((b)->depth == current_scope->depth)
#define B_IN_FILE_SCOPE(b) ((b)->depth == 1 /*file_scope->depth*/)
#define B_IN_EXTERNAL_SCOPE(b) ((b)->depth == 0 /*external_scope->depth*/)

/* Each C symbol points to three linked lists of c_binding structures.
   These describe the values of the identifier in the three different
   namespaces defined by the language.  */

ಸಂರಚನಾ GTY(()) lang_identifier {
  ಸಂರಚನಾ c_common_identifier common_id;
  ಸಂರಚನಾ c_binding *ಚಿಹ್ನೆ_binding; /* vars, funcs, constants, typedefs */
  ಸಂರಚನಾ c_binding *tag_binding;    /* struct/union/enum tags */
  ಸಂರಚನಾ c_binding *label_binding;  /* labels */
};

/* Validate c-lang.cc's assumptions.  */
ಬಾಹ್ಯ ವರ್ಣ C_SIZEOF_STRUCT_LANG_IDENTIFIER_isnt_accurate
[(ಪರಿಮಾಣ(ಸಂರಚನಾ lang_identifier) == C_SIZEOF_STRUCT_LANG_IDENTIFIER) ? 1 : -1];

/* The binding oracle; see c-tree.h.  */
ಶೂನ್ಯ (*c_binding_oracle) (ಗಣನಾ c_oracle_request, ವೃಕ್ಷ identifier);

/* This flag is set on an identifier if we have previously asked the
   binding oracle for this identifier's symbol binding.  */
#define I_ಚಿಹ್ನೆ_CHECKED(ಗಂಟು) \
  (ವೃಕ್ಷ_LANG_FLAG_4 (IDENTIFIER_ಗಂಟು_CHECK (ಗಂಟು)))

ಸ್ಥಿರ ಅನ್ತಃಸ್ಥ ಸಂರಚನಾ c_binding* *
i_ಚಿಹ್ನೆ_binding (ವೃಕ್ಷ ಗಂಟು)
{
  ಸಂರಚನಾ lang_identifier *lid
    = (ಸಂರಚನಾ lang_identifier *) IDENTIFIER_ಗಂಟು_CHECK (ಗಂಟು);

  ಯದಿ (lid->ಚಿಹ್ನೆ_binding == ರಿಕ್ತ
      && c_binding_oracle != ರಿಕ್ತ
      && !I_ಚಿಹ್ನೆ_CHECKED (ಗಂಟು))
    {
      /* Set the "checked" flag first, to avoid infinite recursion
	 when the binding oracle calls back into gcc.  */
      I_ಚಿಹ್ನೆ_CHECKED (ಗಂಟು) = 1;
      c_binding_oracle (C_ORACLE_ಚಿಹ್ನೆ, ಗಂಟು);
    }

  ಪ್ರತ್ಯಾಗಮ &lid->ಚಿಹ್ನೆ_binding;
}

#define I_ಚಿಹ್ನೆ_BINDING(ಗಂಟು) (*i_ಚಿಹ್ನೆ_binding (ಗಂಟು))

#define I_ಚಿಹ್ನೆ_DECL(ಗಂಟು) \
 (I_ಚಿಹ್ನೆ_BINDING(ಗಂಟು) ? I_ಚಿಹ್ನೆ_BINDING(ಗಂಟು)->decl : 0)

/* This flag is set on an identifier if we have previously asked the
   binding oracle for this identifier's tag binding.  */
#define I_TAG_CHECKED(ಗಂಟು) \
  (ವೃಕ್ಷ_LANG_FLAG_5 (IDENTIFIER_ಗಂಟು_CHECK (ಗಂಟು)))

ಸ್ಥಿರ ಅನ್ತಃಸ್ಥ ಸಂರಚನಾ c_binding **
i_tag_binding (ವೃಕ್ಷ ಗಂಟು)
{
  ಸಂರಚನಾ lang_identifier *lid
    = (ಸಂರಚನಾ lang_identifier *) IDENTIFIER_ಗಂಟು_CHECK (ಗಂಟು);

  ಯದಿ (lid->tag_binding == ರಿಕ್ತ
      && c_binding_oracle != ರಿಕ್ತ
      && !I_TAG_CHECKED (ಗಂಟು))
    {
      /* Set the "checked" flag first, to avoid infinite recursion
	 when the binding oracle calls back into gcc.  */
      I_TAG_CHECKED (ಗಂಟು) = 1;
      c_binding_oracle (C_ORACLE_TAG, ಗಂಟು);
    }

  ಪ್ರತ್ಯಾಗಮ &lid->tag_binding;
}

#define I_TAG_BINDING(ಗಂಟು) (*i_tag_binding (ಗಂಟು))

#define I_TAG_DECL(ಗಂಟು) \
 (I_TAG_BINDING(ಗಂಟು) ? I_TAG_BINDING(ಗಂಟು)->decl : 0)

/* This flag is set on an identifier if we have previously asked the
   binding oracle for this identifier's label binding.  */
#define I_LABEL_CHECKED(ಗಂಟು) \
  (ವೃಕ್ಷ_LANG_FLAG_6 (IDENTIFIER_ಗಂಟು_CHECK (ಗಂಟು)))

ಸ್ಥಿರ ಅನ್ತಃಸ್ಥ ಸಂರಚನಾ c_binding **
i_label_binding (ವೃಕ್ಷ ಗಂಟು)
{
  ಸಂರಚನಾ lang_identifier *lid
    = (ಸಂರಚನಾ lang_identifier *) IDENTIFIER_ಗಂಟು_CHECK (ಗಂಟು);

  ಯದಿ (lid->label_binding == ರಿಕ್ತ
      && c_binding_oracle != ರಿಕ್ತ
      && !I_LABEL_CHECKED (ಗಂಟು))
    {
      /* Set the "checked" flag first, to avoid infinite recursion
	 when the binding oracle calls back into gcc.  */
      I_LABEL_CHECKED (ಗಂಟು) = 1;
      c_binding_oracle (C_ORACLE_LABEL, ಗಂಟು);
    }

  ಪ್ರತ್ಯಾಗಮ &lid->label_binding;
}

#define I_LABEL_BINDING(ಗಂಟು) (*i_label_binding (ಗಂಟು))

#define I_LABEL_DECL(ಗಂಟು) \
 (I_LABEL_BINDING(ಗಂಟು) ? I_LABEL_BINDING(ಗಂಟು)->decl : 0)

/* Used by C_TOKEN_VEC tree.  */
ಸಂರಚನಾ GTY (()) c_ವೃಕ್ಷ_token_vec {
  ಸಂರಚನಾ ವೃಕ್ಷ_base base;
  vec<c_token, va_gc> *tokens;
};

STATIC_ASSERT (ಪರಿಮಾಣ (c_ವೃಕ್ಷ_token_vec) == ಪರಿಮಾಣ (c_ವೃಕ್ಷ_token_vec_struct));
STATIC_ASSERT (offsetof (c_ವೃಕ್ಷ_token_vec, tokens)
	       == offsetof (c_ವೃಕ್ಷ_token_vec_struct, tokens));

/* The resulting tree type.  */

ಸಙ್ಘ GTY((desc ("TREE_CODE (&%h.generic) == IDENTIFIER_NODE + 2 * (TREE_CODE (&%h.generic) == C_TOKEN_VEC)"),
       chain_next ("(union lang_tree_node *) c_tree_chain_next (&%h.generic)"))) lang_ವೃಕ್ಷ_ಗಂಟು
 {
  ಸಙ್ಘ ವೃಕ್ಷ_ಗಂಟು GTY ((tag ("0"),
			desc ("tree_node_structure (&%h)")))
    generic;
  ಸಂರಚನಾ lang_identifier GTY ((tag ("1"))) identifier;
  ಸಂರಚನಾ c_ವೃಕ್ಷ_token_vec GTY ((tag ("2"))) c_token_vec;
};

/* Langhook for tree_size.  */
size_t
c_ವೃಕ್ಷ_size (ಗಣನಾ ವೃಕ್ಷ_code code)
{
  gcc_checking_assert (code >= ಅಂಕೆ_ವೃಕ್ಷ_CODES);
  ವಿಕಲ್ಪ (code)
    {
    ಪಕ್ಷ C_TOKEN_VEC: ಪ್ರತ್ಯಾಗಮ ಪರಿಮಾಣ (c_ವೃಕ್ಷ_token_vec);
    ಸ್ವಭಾವ:
      ವಿಕಲ್ಪ (ವೃಕ್ಷ_CODE_CLASS (code))
	{
	ಪಕ್ಷ tcc_declaration: ಪ್ರತ್ಯಾಗಮ ಪರಿಮಾಣ (ವೃಕ್ಷ_decl_non_common);
	ಪಕ್ಷ tcc_type: ಪ್ರತ್ಯಾಗಮ ಪರಿಮಾಣ (ವೃಕ್ಷ_type_non_common);
	ಸ್ವಭಾವ: gcc_unreachable ();
	}
    }
}

/* Track bindings and other things that matter for goto warnings.  For
   efficiency, we do not gather all the decls at the point of
   definition.  Instead, we point into the bindings structure.  As
   scopes are popped, we update these structures and gather the decls
   that matter at that time.  */

ಸಂರಚನಾ GTY(()) c_spot_bindings {
  /* The currently open scope which holds bindings defined when the
     label was defined or the goto statement was found.  */
  ಸಂರಚನಾ c_scope *scope;
  /* The bindings in the scope field which were defined at the point
     of the label or goto.  This lets us look at older or newer
     bindings in the scope, as appropriate.  */
  ಸಂರಚನಾ c_binding *bindings_in_scope;
  /* The number of statement expressions that have started since this
     label or goto statement was defined.  This is zero if we are at
     the same statement expression level.  It is positive if we are in
     a statement expression started since this spot.  It is negative
     if this spot was in a statement expression and we have left
     it.  */
  ಪೂರ್ಣಾಙ್ಕ stmt_exprs;
  /* Whether we started in a statement expression but are no longer in
     it.  This is set to true if stmt_exprs ever goes negative.  */
  ತಾರ್ಕಿಕ ಎಡ_stmt_ಅಭಿವ್ಯಕ್ತಿ;
};

/* This structure is used to keep track of bindings seen when a goto
   statement is defined.  This is only used if we see the goto
   statement before we see the label.  */

ಸಂರಚನಾ GTY(()) c_goto_bindings {
  /* The location of the goto statement.  */
  location_t loc;
  /* The bindings of the goto statement.  */
  ಸಂರಚನಾ c_spot_bindings goto_bindings;
};

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ c_goto_bindings *c_goto_bindings_p;

/* The additional information we keep track of for a label binding.
   These fields are updated as scopes are popped.  */

ಸಂರಚನಾ GTY(()) c_label_vars {
  /* The shadowed c_label_vars, when one label shadows another (which
     can only happen using a __label__ declaration).  */
  ಸಂರಚನಾ c_label_vars *shadowed;
  /* The bindings when the label was defined.  */
  ಸಂರಚನಾ c_spot_bindings label_bindings;
  /* A list of decls that we care about: decls about which we should
     warn if a goto branches to this label from later in the function.
     Decls are added to this list as scopes are popped.  We only add
     the decls that matter.  */
  vec<ವೃಕ್ಷ, va_gc> *decls_in_scope;
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


ಸಂರಚನಾ GTY((chain_next ("%h.outer"))) c_scope {
  /* The scope containing this one.  */
  ಸಂರಚನಾ c_scope *outer;

  /* The next outermost function scope.  */
  ಸಂರಚನಾ c_scope *outer_function;

  /* All bindings in this scope.  */
  ಸಂರಚನಾ c_binding *bindings;

  /* For each scope (except the global one), a chain of BLOCK nodes
     for all the scopes that were entered and exited one level down.  */
  ವೃಕ್ಷ blocks;
  ವೃಕ್ಷ blocks_last;

  /* The depth of this scope.  Used to keep the ->shadowed chain of
     bindings sorted innermost to outermost.  */
  unsigned ಪೂರ್ಣಾಙ್ಕ depth : 28;

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

ಸ್ಥಿರ GTY(()) ಸಂರಚನಾ c_scope *current_scope;

/* The innermost function scope.  Ordinary (not explicitly declared)
   labels, bindings to error_mark_node, and the lazily-created
   bindings of __func__ and its friends get this scope.  */

ಸ್ಥಿರ GTY(()) ಸಂರಚನಾ c_scope *current_function_scope;

/* The C file scope.  This is reset for each input translation unit.  */

ಸ್ಥಿರ GTY(()) ಸಂರಚನಾ c_scope *file_scope;

/* The outermost scope.  This is used for all declarations with
   external linkage, and only these, hence the name.  */

ಸ್ಥಿರ GTY(()) ಸಂರಚನಾ c_scope *external_scope;

/* A chain of c_scope structures awaiting reuse.  */

ಸ್ಥಿರ GTY((deletable)) ಸಂರಚನಾ c_scope *scope_freelist;

/* A chain of c_binding structures awaiting reuse.  */

ಸ್ಥಿರ GTY((deletable)) ಸಂರಚನಾ c_binding *binding_freelist;

/* Append VAR to LIST in scope SCOPE.  */
#define SCOPE_LIST_APPEND(scope, list, decl) ಕುರು {	\
  ಸಂರಚನಾ c_scope *s_ = (scope);				\
  ವೃಕ್ಷ d_ = (decl);					\
  ಯದಿ (s_->list##_last)					\
    BLOCK_CHAIN (s_->list##_last) = d_;			\
  ಅನ್ಯಥಾ							\
    s_->list = d_;					\
  s_->list##_last = d_;					\
} ಯಾವತ್ (0)

/* Concatenate FROM in scope FSCOPE onto TO in scope TSCOPE.  */
#define SCOPE_LIST_CONCAT(tscope, to, fscope, from) ಕುರು {	\
  ಸಂರಚನಾ c_scope *t_ = (tscope);				\
  ಸಂರಚನಾ c_scope *f_ = (fscope);				\
  ಯದಿ (t_->to##_last)						\
    BLOCK_CHAIN (t_->to##_last) = f_->from;			\
  ಅನ್ಯಥಾ								\
    t_->to = f_->from;						\
  t_->to##_last = f_->from##_last;				\
} ಯಾವತ್ (0)

/* A c_inline_static structure stores details of a static identifier
   referenced in a definition of a function that may be an inline
   definition if no subsequent declaration of that function uses
   "extern" or does not use "inline".  */

ಸಂರಚನಾ GTY((chain_next ("%h.next"))) c_inline_static {
  /* The location for a diagnostic.  */
  location_t location;

  /* The function that may be an inline definition.  */
  ವೃಕ್ಷ function;

  /* The object or function referenced.  */
  ವೃಕ್ಷ static_decl;

  /* What sort of reference this is.  */
  ಗಣನಾ c_inline_static_type type;

  /* The next such structure or NULL.  */
  ಸಂರಚನಾ c_inline_static *next;
};

/* List of static identifiers used or referenced in functions that may
   be inline definitions.  */
ಸ್ಥಿರ GTY(()) ಸಂರಚನಾ c_inline_static *c_inline_statics;

/* True means unconditionally make a BLOCK for the next scope pushed.  */

ಸ್ಥಿರ ತಾರ್ಕಿಕ keep_next_level_flag;

/* True means the next call to push_scope will be the outermost scope
   of a function body, so do not push a new scope, merely cease
   expecting parameter decls.  */

ಸ್ಥಿರ ತಾರ್ಕಿಕ next_is_function_body;

/* A vector of pointers to c_binding structures.  */

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ c_binding *c_binding_ptr;

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
  auto_vec<ವೃಕ್ಷ> typedefs_seen;
  /* The location of a previous definition of this struct.  */
  location_t refloc;
};


/* Hash table for structs and unions.  */
ಸಂರಚನಾ c_struct_hasher : ggc_ptr_hash<ವೃಕ್ಷ_ಗಂಟು>
{
  ಸ್ಥಿರ hashval_t hash (ವೃಕ್ಷ t);
  ಸ್ಥಿರ ತಾರ್ಕಿಕ equal (ವೃಕ್ಷ, ವೃಕ್ಷ);
};

/* Hash an RECORD OR UNION.  */
hashval_t
c_struct_hasher::hash (ವೃಕ್ಷ type)
{
  inchash::hash hstate;

  hstate.add_int (ವೃಕ್ಷ_CODE (type));
  ವೃಕ್ಷ tag = c_type_tag (type);
  hstate.add_object (tag);

  ಪ್ರತ್ಯಾಗಮ hstate.end ();
}

/* Compare two RECORD or UNION types.  */
ತಾರ್ಕಿಕ
c_struct_hasher::equal (ವೃಕ್ಷ t1,  ವೃಕ್ಷ t2)
{
  ಪ್ರತ್ಯಾಗಮ comptypes_equiv_p (t1, t2);
}

/* All tagged typed so that TYPE_CANONICAL can be set correctly.  */
ಸ್ಥಿರ GTY (()) hash_table<c_struct_hasher> *c_struct_htab;

/* Information for the struct or union currently being parsed, or
   NULL if not parsing a struct or union.  */
ಸ್ಥಿರ ವರ್ಗ c_struct_parse_info *struct_parse_info;

/* Forward declarations.  */
ಸ್ಥಿರ ವೃಕ್ಷ lookup_name_in_scope (ವೃಕ್ಷ, ಸಂರಚನಾ c_scope *);
ಸ್ಥಿರ ವೃಕ್ಷ c_make_fname_decl (location_t, ವೃಕ್ಷ, ಪೂರ್ಣಾಙ್ಕ);
ಸ್ಥಿರ ವೃಕ್ಷ grokdeclarator (ಧ್ರುವ ಸಂರಚನಾ c_declarator *,
			    ಸಂರಚನಾ c_declspecs *,
			    ಗಣನಾ decl_context, ತಾರ್ಕಿಕ, ವೃಕ್ಷ *, ವೃಕ್ಷ *, ವೃಕ್ಷ *,
			    ತಾರ್ಕಿಕ *, ಗಣನಾ deprecated_states);
ಸ್ಥಿರ ವೃಕ್ಷ grokparms (ಸಂರಚನಾ c_arg_info *, ತಾರ್ಕಿಕ);
ಸ್ಥಿರ ಶೂನ್ಯ layout_array_type (ವೃಕ್ಷ);
ಸ್ಥಿರ ಧ್ರುವ ವರ್ಣ *header_for_builtin_fn (ವೃಕ್ಷ);

/* T is a statement.  Add it to the statement-tree.  This is the
   C/ObjC version--C++ has a slightly different version of this
   function.  */

ವೃಕ್ಷ
add_stmt (ವೃಕ್ಷ t)
{
  ಗಣನಾ ವೃಕ್ಷ_code code = ವೃಕ್ಷ_CODE (t);

  ಯದಿ (CAN_HAVE_LOCATION_P (t) && code != LABEL_ಅಭಿವ್ಯಕ್ತಿ)
    {
      ಯದಿ (!ಅಭಿವ್ಯಕ್ತಿ_HAS_LOCATION (t))
	SET_ಅಭಿವ್ಯಕ್ತಿ_LOCATION (t, ಒಳಹರಿವು_location);
    }

  /* Add T to the statement-tree.  Non-side-effect statements need to be
     recorded during statement expressions.  */
  ಯದಿ (!building_stmt_list_p ())
    ತಳ್ಳು_stmt_list ();

  ಯದಿ (code == LABEL_ಅಭಿವ್ಯಕ್ತಿ || code == CASE_LABEL_ಅಭಿವ್ಯಕ್ತಿ)
    STATEMENT_LIST_HAS_LABEL (cur_stmt_list) = 1;

  append_to_statement_list_force (t, &cur_stmt_list);

  ಪ್ರತ್ಯಾಗಮ t;
}





/* Return true if we will want to say something if a goto statement
   crosses DECL.  */

ಸ್ಥಿರ ತಾರ್ಕಿಕ
decl_jump_unsafe (ವೃಕ್ಷ decl)
{
  ಯದಿ (error_operand_p (decl))
    ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;

  /* Don't warn for compound literals.  If a goto statement crosses
     their initialization, it should cross also all the places where
     the complit is used or where the complit address might be saved
     into some variable, so code after the label to which goto jumps
     should not be able to refer to the compound literal.  */
  ಯದಿ (VAR_P (decl) && C_DECL_COMPOUND_LITERAL_P (decl))
    ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;

  ಯದಿ (flag_openmp
      && VAR_P (decl)
      && lookup_attribute ("omp allocate", DECL_ATTRIBUTES (decl)))
    ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;

  /* Always warn about crossing variably modified types.  */
  ಯದಿ ((VAR_P (decl) || ವೃಕ್ಷ_CODE (decl) == TYPE_DECL)
      && c_type_variably_modified_p (ವೃಕ್ಷ_TYPE (decl)))
    ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;

  /* Otherwise, only warn if -Wgoto-misses-init and this is an
     initialized automatic decl.  */
  ಯದಿ (warn_jump_misses_init
      && VAR_P (decl)
      && !ವೃಕ್ಷ_STATIC (decl)
      && DECL_INITIAL (decl) != NULL_ವೃಕ್ಷ)
    ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;

  ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
}


ಶೂನ್ಯ
c_print_identifier (FILE *file, ವೃಕ್ಷ ಗಂಟು, ಪೂರ್ಣಾಙ್ಕ indent)
{
  ಶೂನ್ಯ (*save) (ಗಣನಾ c_oracle_request, ವೃಕ್ಷ identifier);

  /* Temporarily hide any binding oracle.  Without this, calls to
     debug_tree from the debugger will end up calling into the oracle,
     making for a confusing debug session.  As the oracle isn't needed
     here for normal operation, it's simplest to suppress it.  */
  save = c_binding_oracle;
  c_binding_oracle = ರಿಕ್ತ;

  print_ಗಂಟು (file, "symbol", I_ಚಿಹ್ನೆ_DECL (ಗಂಟು), indent + 4);
  print_ಗಂಟು (file, "tag", I_TAG_DECL (ಗಂಟು), indent + 4);
  print_ಗಂಟು (file, "label", I_LABEL_DECL (ಗಂಟು), indent + 4);
  ಯದಿ (C_IS_RESERVED_WORD (ಗಂಟು) && C_RID_CODE (ಗಂಟು) != RID_CXX_COMPAT_WARN)
    {
      ವೃಕ್ಷ rid = ridpointers[C_RID_CODE (ಗಂಟು)];
      indent_to (file, indent + 4);
      fprintf (file, "rid " HOST_PTR_PRINTF " \"%s\"",
	       (ಶೂನ್ಯ *) rid, IDENTIFIER_POINTER (rid));
    }

  c_binding_oracle = save;
}

/* Establish that the scope contains declarations that are sensitive to
   jumps that cross a binding.  Together with decl_jump_unsafe, this is
   used to diagnose such jumps.  */
ಶೂನ್ಯ
c_mark_decl_jump_unsafe_in_current_scope ()
{
  current_scope->has_jump_unsafe_decl = 1;
}

/* Establish a binding between NAME, an IDENTIFIER_NODE, and DECL,
   which may be any of several kinds of DECL or TYPE or error_mark_node,
   in the scope SCOPE.  */
ಸ್ಥಿರ ಶೂನ್ಯ
bind (ವೃಕ್ಷ name, ವೃಕ್ಷ decl, ಸಂರಚನಾ c_scope *scope, ತಾರ್ಕಿಕ invisible,
      ತಾರ್ಕಿಕ nested, location_t locus)
{
  ಸಂರಚನಾ c_binding *b, **here;

  ಯದಿ (binding_freelist)
    {
      b = binding_freelist;
      binding_freelist = b->prev;
    }
  ಅನ್ಯಥಾ
    b = ggc_alloc<c_binding> ();

  b->shadowed = 0;
  b->decl = decl;
  b->id = name;
  b->depth = scope->depth;
  b->invisible = invisible;
  b->nested = nested;
  b->inner_comp = 0;
  b->in_struct = 0;
  b->locus = locus;

  b->u.type = ರಿಕ್ತ;

  b->prev = scope->bindings;
  scope->bindings = b;

  ಯದಿ (decl_jump_unsafe (decl))
    scope->has_jump_unsafe_decl = 1;

  ಯದಿ (!name)
    ಪ್ರತ್ಯಾಗಮ;

  ವಿಕಲ್ಪ (ವೃಕ್ಷ_CODE (decl))
    {
    ಪಕ್ಷ LABEL_DECL:     here = &I_LABEL_BINDING (name);   ಭಙ್ಗ;
    ಪಕ್ಷ ENUMERAL_TYPE:
    ಪಕ್ಷ UNION_TYPE:
    ಪಕ್ಷ RECORD_TYPE:    here = &I_TAG_BINDING (name);     ಭಙ್ಗ;
    ಪಕ್ಷ VAR_DECL:
    ಪಕ್ಷ FUNCTION_DECL:
    ಪಕ್ಷ TYPE_DECL:
    ಪಕ್ಷ CONST_DECL:
    ಪಕ್ಷ PARM_DECL:
    ಪಕ್ಷ ERROR_MARK:     here = &I_ಚಿಹ್ನೆ_BINDING (name);  ಭಙ್ಗ;

    ಸ್ವಭಾವ:
      gcc_unreachable ();
    }

  /* Locate the appropriate place in the chain of shadowed decls
     to insert this binding.  Normally, scope == current_scope and
     this does nothing.  */
  ಯಾವತ್ (*here && (*here)->depth > scope->depth)
    here = &(*here)->shadowed;

  b->shadowed = *here;
  *here = b;
}

/* Clear the binding structure B, stick it on the binding_freelist,
   and return the former value of b->prev.  This is used by pop_scope
   and get_parm_info to iterate destructively over all the bindings
   from a given scope.  */
ಸ್ಥಿರ ಸಂರಚನಾ c_binding *
free_binding_and_advance (ಸಂರಚನಾ c_binding *b)
{
  ಸಂರಚನಾ c_binding *prev = b->prev;

  memset (b, 0, ಪರಿಮಾಣ (ಸಂರಚನಾ c_binding));
  b->prev = binding_freelist;
  binding_freelist = b;

  ಪ್ರತ್ಯಾಗಮ prev;
}

/* Bind a label.  Like bind, but skip fields which aren't used for
   labels, and add the LABEL_VARS value.  */
ಸ್ಥಿರ ಶೂನ್ಯ
bind_label (ವೃಕ್ಷ name, ವೃಕ್ಷ label, ಸಂರಚನಾ c_scope *scope,
	    ಸಂರಚನಾ c_label_vars *label_vars)
{
  ಸಂರಚನಾ c_binding *b;

  bind (name, label, scope, /*invisible=*/ಅಸತ್ಯ, /*nested=*/ಅಸತ್ಯ,
	UNKNOWN_LOCATION);

  scope->has_label_bindings = ಸತ್ಯ;

  b = scope->bindings;
  gcc_assert (b->decl == label);
  label_vars->shadowed = b->u.label;
  b->u.label = label_vars;
}

/* Hook called at end of compilation to assume 1 elt
   for a file-scope tentative array defn that wasn't complete before.  */

ಶೂನ್ಯ
c_finish_incomplete_decl (ವೃಕ್ಷ decl)
{
  ಯದಿ (VAR_P (decl))
    {
      ವೃಕ್ಷ type = ವೃಕ್ಷ_TYPE (decl);
      ಯದಿ (type != error_mark_ಗಂಟು
	  && ವೃಕ್ಷ_CODE (type) == ARRAY_TYPE
	  && !DECL_EXTERNAL (decl)
	  && TYPE_DOMAIN (type) == NULL_ವೃಕ್ಷ)
	{
	  ಯದಿ (flag_isoc2y && !ವೃಕ್ಷ_PUBLIC (decl))
	    error_at (DECL_SOURCE_LOCATION (decl),
		      "array size missing in %q+D", decl);
	  ಅನ್ಯಥಾ
	    warning_at (DECL_SOURCE_LOCATION (decl),
			0, "array %q+D assumed to have one element", decl);

	  complete_array_type (&ವೃಕ್ಷ_TYPE (decl), NULL_ವೃಕ್ಷ, ಸತ್ಯ);

	  relayout_decl (decl);
	}
    }
}

/* Record that inline function FUNC contains a reference (location
   LOC) to static DECL (file-scope or function-local according to
   TYPE).  */

ಶೂನ್ಯ
record_inline_static (location_t loc, ವೃಕ್ಷ func, ವೃಕ್ಷ decl,
		      ಗಣನಾ c_inline_static_type type)
{
  c_inline_static *csi = ggc_alloc<c_inline_static> ();
  csi->location = loc;
  csi->function = func;
  csi->static_decl = decl;
  csi->type = type;
  csi->next = c_inline_statics;
  c_inline_statics = csi;
}

/* Check for references to static declarations in inline functions at
   the end of the translation unit and diagnose them if the functions
   are still inline definitions.  */

ಸ್ಥಿರ ಶೂನ್ಯ
check_inline_statics (ಶೂನ್ಯ)
{
  ಸಂರಚನಾ c_inline_static *csi;
  ಪ್ರತಿ (csi = c_inline_statics; csi; csi = csi->next)
    {
      ಯದಿ (DECL_EXTERNAL (csi->function))
	ವಿಕಲ್ಪ (csi->type)
	  {
	  ಪಕ್ಷ csi_internal:
	    pedwarn (csi->location, 0,
		     "%qD is static but used in inline function %qD "
		     "which is not static", csi->static_decl, csi->function);
	    ಭಙ್ಗ;
	  ಪಕ್ಷ csi_modifiable:
	    pedwarn (csi->location, 0,
		     "%q+D is static but declared in inline function %qD "
		     "which is not static", csi->static_decl, csi->function);
	    ಭಙ್ಗ;
	  ಸ್ವಭಾವ:
	    gcc_unreachable ();
	  }
    }
  c_inline_statics = ರಿಕ್ತ;
}

/* Fill in a c_spot_bindings structure.  If DEFINING is true, set it
   for the current state, otherwise set it to uninitialized.  */

ಸ್ಥಿರ ಶೂನ್ಯ
set_spot_bindings (ಸಂರಚನಾ c_spot_bindings *p, ತಾರ್ಕಿಕ defining)
{
  ಯದಿ (defining)
    {
      p->scope = current_scope;
      p->bindings_in_scope = current_scope->bindings;
    }
  ಅನ್ಯಥಾ
    {
      p->scope = ರಿಕ್ತ;
      p->bindings_in_scope = ರಿಕ್ತ;
    }
  p->stmt_exprs = 0;
  p->ಎಡ_stmt_ಅಭಿವ್ಯಕ್ತಿ = ಅಸತ್ಯ;
}

/* Update spot bindings P as we pop out of SCOPE.  Return true if we
   should push decls for a label.  */

ಸ್ಥಿರ ತಾರ್ಕಿಕ
update_spot_bindings (ಸಂರಚನಾ c_scope *scope, ಸಂರಚನಾ c_spot_bindings *p)
{
  ಯದಿ (p->scope != scope)
    {
      /* This label or goto is defined in some other scope, or it is a
	 label which is not yet defined.  There is nothing to
	 update.  */
      ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
    }

  /* Adjust the spot bindings to refer to the bindings already defined
     in the enclosing scope.  */
  p->scope = scope->outer;
  p->bindings_in_scope = p->scope->bindings;

  ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
}

/* The Objective-C front-end often needs to determine the current scope.  */

ಶೂನ್ಯ *
objc_get_current_scope (ಶೂನ್ಯ)
{
  ಪ್ರತ್ಯಾಗಮ current_scope;
}

/* The following function is used only by Objective-C.  It needs to live here
   because it accesses the innards of c_scope.  */

ಶೂನ್ಯ
objc_mark_locals_volatile (ಶೂನ್ಯ *enclosing_blk)
{
  ಸಂರಚನಾ c_scope *scope;
  ಸಂರಚನಾ c_binding *b;

  ಪ್ರತಿ (scope = current_scope;
       scope && scope != enclosing_blk;
       scope = scope->outer)
    {
      ಪ್ರತಿ (b = scope->bindings; b; b = b->prev)
	objc_volatilize_decl (b->decl);

      /* Do not climb up past the current function.  */
      ಯದಿ (scope->function_body)
	ಭಙ್ಗ;
    }
}

/* Return true if we are in the global binding level.  */

ತಾರ್ಕಿಕ
global_bindings_p (ಶೂನ್ಯ)
{
  ಪ್ರತ್ಯಾಗಮ current_scope == file_scope;
}

/* Return true if we're declaring parameters in an old-style function
   declaration.  */

ತಾರ್ಕಿಕ
old_style_parameter_scope (ಶೂನ್ಯ)
{
  /* If processing parameters and there is no function statement list, we
   * have an old-style function declaration.  */
  ಪ್ರತ್ಯಾಗಮ (current_scope->parm_flag && !DECL_SAVED_ವೃಕ್ಷ (current_function_decl));
}

ಶೂನ್ಯ
keep_next_level (ಶೂನ್ಯ)
{
  keep_next_level_flag = ಸತ್ಯ;
}

/* Set the flag for the FLOAT_CONST_DECIMAL64 pragma being ON.  */

ಶೂನ್ಯ
set_float_const_decimal64 (ಶೂನ್ಯ)
{
  current_scope->float_const_decimal64 = ಸತ್ಯ;
}

/* Clear the flag for the FLOAT_CONST_DECIMAL64 pragma.  */

ಶೂನ್ಯ
clear_float_const_decimal64 (ಶೂನ್ಯ)
{
  current_scope->float_const_decimal64 = ಅಸತ್ಯ;
}

/* Return nonzero if an unsuffixed float constant is _Decimal64.  */

ತಾರ್ಕಿಕ
float_const_decimal64_p (ಶೂನ್ಯ)
{
  ಪ್ರತ್ಯಾಗಮ current_scope->float_const_decimal64;
}

/* Identify this scope as currently being filled with parameters.  */

ಶೂನ್ಯ
declare_parm_level (ಶೂನ್ಯ)
{
  current_scope->parm_flag = ಸತ್ಯ;
}

ಶೂನ್ಯ
ತಳ್ಳು_scope (ಶೂನ್ಯ)
{
  ಯದಿ (next_is_function_body)
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
      current_scope->parm_flag         = ಅಸತ್ಯ;
      current_scope->function_body     = ಸತ್ಯ;
      current_scope->keep              = ಸತ್ಯ;
      current_scope->outer_function    = current_function_scope;
      current_function_scope           = current_scope;

      keep_next_level_flag = ಅಸತ್ಯ;
      next_is_function_body = ಅಸತ್ಯ;

      /* The FLOAT_CONST_DECIMAL64 pragma applies to nested scopes.  */
      ಯದಿ (current_scope->outer)
	current_scope->float_const_decimal64
	  = current_scope->outer->float_const_decimal64;
      ಅನ್ಯಥಾ
	current_scope->float_const_decimal64 = ಅಸತ್ಯ;
    }
  ಅನ್ಯಥಾ
    {
      ಸಂರಚನಾ c_scope *scope;
      ಯದಿ (scope_freelist)
	{
	  scope = scope_freelist;
	  scope_freelist = scope->outer;
	}
      ಅನ್ಯಥಾ
	scope = ggc_cleared_alloc<c_scope> ();

      /* The FLOAT_CONST_DECIMAL64 pragma applies to nested scopes.  */
      ಯದಿ (current_scope)
	scope->float_const_decimal64 = current_scope->float_const_decimal64;
      ಅನ್ಯಥಾ
	scope->float_const_decimal64 = ಅಸತ್ಯ;

      scope->keep          = keep_next_level_flag;
      scope->outer         = current_scope;
      scope->depth	   = current_scope ? (current_scope->depth + 1) : 0;

      /* Check for scope depth overflow.  Unlikely (2^28 == 268,435,456) but
	 possible.  */
      ಯದಿ (current_scope && scope->depth == 0)
	{
	  scope->depth--;
	  sorry ("GCC supports only %u nested scopes", scope->depth);
	}

      current_scope        = scope;
      keep_next_level_flag = ಅಸತ್ಯ;
    }
}

/* This is called when we are leaving SCOPE.  For each label defined
   in SCOPE, add any appropriate decls to its decls_in_scope fields.
   These are the decls whose initialization will be skipped by a goto
   later in the function.  */

ಸ್ಥಿರ ಶೂನ್ಯ
update_label_decls (ಸಂರಚನಾ c_scope *scope)
{
  ಸಂರಚನಾ c_scope *s;

  s = scope;
  ಯಾವತ್ (s != ರಿಕ್ತ)
    {
      ಯದಿ (s->has_label_bindings)
	{
	  ಸಂರಚನಾ c_binding *b;

	  ಪ್ರತಿ (b = s->bindings; b != ರಿಕ್ತ; b = b->prev)
	    {
	      ಸಂರಚನಾ c_label_vars *label_vars;
	      ಸಂರಚನಾ c_binding *b1;
	      ತಾರ್ಕಿಕ hjud;
	      unsigned ಪೂರ್ಣಾಙ್ಕ ix;
	      ಸಂರಚನಾ c_goto_bindings *g;

	      ಯದಿ (ವೃಕ್ಷ_CODE (b->decl) != LABEL_DECL)
		ಅನುವರ್ತ;
	      label_vars = b->u.label;

	      b1 = label_vars->label_bindings.bindings_in_scope;
	      ಯದಿ (label_vars->label_bindings.scope == ರಿಕ್ತ)
		hjud = ಅಸತ್ಯ;
	      ಅನ್ಯಥಾ
		hjud = label_vars->label_bindings.scope->has_jump_unsafe_decl;
	      ಯದಿ (update_spot_bindings (scope, &label_vars->label_bindings))
		{
		  /* This label is defined in this scope.  */
		  ಯದಿ (hjud)
		    {
		      ಪ್ರತಿ (; b1 != ರಿಕ್ತ; b1 = b1->prev)
			{
			  /* A goto from later in the function to this
			     label will never see the initialization
			     of B1, if any.  Save it to issue a
			     warning if needed.  */
			  ಯದಿ (decl_jump_unsafe (b1->decl))
			    vec_safe_ತಳ್ಳು(label_vars->decls_in_scope, b1->decl);
			}
		    }
		}

	      /* Update the bindings of any goto statements associated
		 with this label.  */
	      FOR_EACH_VEC_SAFE_ELT (label_vars->gotos, ix, g)
		update_spot_bindings (scope, &g->goto_bindings);
	    }
	}

      /* Don't search beyond the current function.  */
      ಯದಿ (s == current_function_scope)
	ಭಙ್ಗ;

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
  ಸಂರಚನಾ c_scope *scope = current_scope;
  ವೃಕ್ಷ block, context, p;
  ಸಂರಚನಾ c_binding *b;

  ತಾರ್ಕಿಕ functionbody = scope->function_body;
  ತಾರ್ಕಿಕ keep = functionbody || scope->keep || scope->bindings;

  update_label_decls (scope);

  /* If appropriate, create a BLOCK to record the decls for the life
     of this function.  */
  block = NULL_ವೃಕ್ಷ;
  ಯದಿ (keep)
    {
      block = make_ಗಂಟು (BLOCK);
      BLOCK_SUBBLOCKS (block) = scope->blocks;
      ವೃಕ್ಷ_USED (block) = 1;

      /* In each subblock, record that this is its superior.  */
      ಪ್ರತಿ (p = scope->blocks; p; p = BLOCK_CHAIN (p))
	BLOCK_SUPERCONTEXT (p) = block;

      BLOCK_VARS (block) = NULL_ವೃಕ್ಷ;
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
  ಯದಿ (scope->function_body)
    context = current_function_decl;
  ಅನ್ಯಥಾ ಯದಿ (scope == file_scope)
    {
      ವೃಕ್ಷ file_decl
	= build_translation_unit_decl (get_identifier (main_ಒಳಹರಿವು_filename));
      context = file_decl;
      debug_hooks->register_main_translation_unit (file_decl);
    }
  ಅನ್ಯಥಾ
    context = block;

  /* Clear all bindings in this scope.  */
  ಪ್ರತಿ (b = scope->bindings; b; b = free_binding_and_advance (b))
    {
      p = b->decl;
      ವಿಕಲ್ಪ (ವೃಕ್ಷ_CODE (p))
	{
	ಪಕ್ಷ LABEL_DECL:
	  /* Warnings for unused labels, errors for undefined labels.  */
	  ಯದಿ (ವೃಕ್ಷ_USED (p) && !DECL_INITIAL (p))
	    {
	      error ("label %q+D used but not defined", p);
	      DECL_INITIAL (p) = error_mark_ಗಂಟು;
	    }
	  ಅನ್ಯಥಾ
	    warn_for_unused_label (p);

	  /* Labels go in BLOCK_VARS.  */
	  DECL_CHAIN (p) = BLOCK_VARS (block);
	  BLOCK_VARS (block) = p;
	  gcc_assert (I_LABEL_BINDING (b->id) == b);
	  I_LABEL_BINDING (b->id) = b->shadowed;

	  /* Also pop back to the shadowed label_vars.  */
	  release_ವೃಕ್ಷ_vector (b->u.label->decls_in_scope);
	  b->u.label = b->u.label->shadowed;
	  ಭಙ್ಗ;

	ಪಕ್ಷ ENUMERAL_TYPE:
	ಪಕ್ಷ UNION_TYPE:
	ಪಕ್ಷ RECORD_TYPE:

	  /* Types may not have tag-names, in which case the type
	     appears in the bindings list with b->id NULL.  */
	  ಯದಿ (b->id)
	    {
	      gcc_assert (I_TAG_BINDING (b->id) == b);
	      I_TAG_BINDING (b->id) = b->shadowed;
	    }
	  ಭಙ್ಗ;

	ಪಕ್ಷ FUNCTION_DECL:
	  /* Propagate TREE_ADDRESSABLE from nested functions to their
	     containing functions.  */
	  ಯದಿ (!ವೃಕ್ಷ_ASM_WRITTEN (p)
	      && DECL_INITIAL (p) != NULL_ವೃಕ್ಷ
	      && ವೃಕ್ಷ_ADDRESSABLE (p)
	      && DECL_ABSTRACT_ORIGIN (p) != NULL_ವೃಕ್ಷ
	      && DECL_ABSTRACT_ORIGIN (p) != p)
	    ವೃಕ್ಷ_ADDRESSABLE (DECL_ABSTRACT_ORIGIN (p)) = 1;
	  ಯದಿ (!ವೃಕ್ಷ_PUBLIC (p)
	      && !DECL_INITIAL (p)
	      && !b->nested
	      && scope != file_scope
	      && scope != external_scope)
	    {
	      error ("nested function %q+D declared but never defined", p);
	      undef_nested_function = ಸತ್ಯ;
	    }
	  ಅನ್ಯಥಾ ಯದಿ (DECL_DECLARED_INLINE_P (p)
		   && ವೃಕ್ಷ_PUBLIC (p)
		   && !DECL_INITIAL (p))
	    {
	      /* C99 6.7.4p6: "a function with external linkage... declared
		 with an inline function specifier ... shall also be defined
		 in the same translation unit."  */
	      ಯದಿ (!flag_gnu89_inline
		  && !lookup_attribute ("gnu_inline", DECL_ATTRIBUTES (p))
		  && scope == external_scope)
		pedwarn (ಒಳಹರಿವು_location, 0,
			 "inline function %q+D declared but never defined", p);
	      DECL_EXTERNAL (p) = 1;
	    }

	  ಗಚ್ಛ common_ಚಿಹ್ನೆ;

	ಪಕ್ಷ VAR_DECL:
	  /* Warnings for unused variables.  */
	  ಯದಿ ((!ವೃಕ್ಷ_USED (p) || !DECL_READ_P (p))
	      && !warning_suppressed_p (p, OPT_Wunused_but_set_variable_)
	      && !DECL_IN_SYSTEM_HEADER (p)
	      && DECL_NAME (p)
	      && !DECL_ARTIFICIAL (p)
	      && scope != file_scope
	      && scope != external_scope)
	    {
	      ಯದಿ (!ವೃಕ್ಷ_USED (p))
		{
		  warning (OPT_Wunused_variable, "unused variable %q+D", p);
		  suppress_warning (p, OPT_Wunused_variable);
		}
	      ಅನ್ಯಥಾ ಯದಿ (DECL_CONTEXT (p) == current_function_decl)
		warning_at (DECL_SOURCE_LOCATION (p),
			    OPT_Wunused_but_set_variable_,
			    "variable %qD set but not used", p);
	    }

	  ಯದಿ (b->inner_comp)
	    {
	      error ("type of array %q+D completed incompatibly with"
		     " implicit initialization", p);
	    }

	  /* Fall through.  */
	ಪಕ್ಷ TYPE_DECL:
	ಪಕ್ಷ CONST_DECL:
	common_ಚಿಹ್ನೆ:
	  /* All of these go in BLOCK_VARS, but only if this is the
	     binding in the home scope.  */
	  ಯದಿ (!b->nested)
	    {
	      DECL_CHAIN (p) = BLOCK_VARS (block);
	      BLOCK_VARS (block) = p;
	    }
	  ಅನ್ಯಥಾ ಯದಿ (VAR_OR_FUNCTION_DECL_P (p) && scope != file_scope)
	    {
	      /* For block local externs add a special
		 DECL_EXTERNAL decl for debug info generation.  */
	      ವೃಕ್ಷ extp = copy_ಗಂಟು (p);

	      DECL_EXTERNAL (extp) = 1;
	      ವೃಕ್ಷ_STATIC (extp) = 0;
	      ವೃಕ್ಷ_PUBLIC (extp) = 1;
	      DECL_INITIAL (extp) = NULL_ವೃಕ್ಷ;
	      DECL_LANG_SPECIFIC (extp) = ರಿಕ್ತ;
	      DECL_CONTEXT (extp) = current_function_decl;
	      ಯದಿ (ವೃಕ್ಷ_CODE (p) == FUNCTION_DECL)
		{
		  DECL_RESULT (extp) = NULL_ವೃಕ್ಷ;
		  DECL_SAVED_ವೃಕ್ಷ (extp) = NULL_ವೃಕ್ಷ;
		  DECL_STRUCT_FUNCTION (extp) = ರಿಕ್ತ;
		}
	      ಯದಿ (b->locus != UNKNOWN_LOCATION)
		DECL_SOURCE_LOCATION (extp) = b->locus;
	      DECL_CHAIN (extp) = BLOCK_VARS (block);
	      BLOCK_VARS (block) = extp;
	    }
	  /* If this is the file scope set DECL_CONTEXT of each decl to
	     the TRANSLATION_UNIT_DECL.  This makes same_translation_unit_p
	     work.  */
	  ಯದಿ (scope == file_scope)
	      DECL_CONTEXT (p) = context;

	  gcc_fallthrough ();
	  /* Parameters go in DECL_ARGUMENTS, not BLOCK_VARS, and have
	     already been put there by store_parm_decls.  Unused-
	     parameter warnings are handled by function.cc.
	     error_mark_node obviously does not go in BLOCK_VARS and
	     does not get unused-variable warnings.  */
	ಪಕ್ಷ PARM_DECL:
	ಪಕ್ಷ ERROR_MARK:
	  /* It is possible for a decl not to have a name.  We get
	     here with b->id NULL in this case.  */
	  ಯದಿ (b->id)
	    {
	      gcc_assert (I_ಚಿಹ್ನೆ_BINDING (b->id) == b);
	      I_ಚಿಹ್ನೆ_BINDING (b->id) = b->shadowed;
	      ಯದಿ (b->shadowed && b->shadowed->u.type)
		ವೃಕ್ಷ_TYPE (b->shadowed->decl) = b->shadowed->u.type;
	    }
	  ಭಙ್ಗ;

	ಸ್ವಭಾವ:
	  gcc_unreachable ();
	}
    }


  /* Dispose of the block that we just made inside some higher level.  */
  ಯದಿ ((scope->function_body || scope == file_scope) && context)
    {
      DECL_INITIAL (context) = block;
      BLOCK_SUPERCONTEXT (block) = context;
    }
  ಅನ್ಯಥಾ ಯದಿ (scope->outer)
    {
      ಯದಿ (block)
	SCOPE_LIST_APPEND (scope->outer, blocks, block);
      /* If we did not make a block for the scope just exited, any
	 blocks made for inner scopes must be carried forward so they
	 will later become subblocks of something else.  */
      ಅನ್ಯಥಾ ಯದಿ (scope->blocks)
	SCOPE_LIST_CONCAT (scope->outer, blocks, scope, blocks);
    }

  /* Pop the current scope, and free the structure for reuse.  */
  current_scope = scope->outer;
  ಯದಿ (scope->function_body)
    current_function_scope = scope->outer_function;

  memset (scope, 0, ಪರಿಮಾಣ (ಸಂರಚನಾ c_scope));
  scope->outer = scope_freelist;
  scope_freelist = scope;

  ಪ್ರತ್ಯಾಗಮ block;
}

ಶೂನ್ಯ
ತಳ್ಳು_file_scope (ಶೂನ್ಯ)
{
  ವೃಕ್ಷ decl;

  ಯದಿ (file_scope)
    ಪ್ರತ್ಯಾಗಮ;

  /* Call the target stack_protect_guard hook if the stack protection
     guard is declared as a global symbol.  */
  ಯದಿ (targetm.ರಾಶಿ_protect_guard_ಚಿಹ್ನೆ_p ())
    {
      ವೃಕ್ಷ decl = targetm.ರಾಶಿ_protect_guard ();
      DECL_CHAIN (decl) = visible_builtins;
      visible_builtins = decl;
    }

  ತಳ್ಳು_scope ();
  file_scope = current_scope;

  start_fname_decls ();

  ಪ್ರತಿ (decl = visible_builtins; decl; decl = DECL_CHAIN (decl))
    bind (DECL_NAME (decl), decl, file_scope,
	  /*invisible=*/ಅಸತ್ಯ, /*nested=*/ಸತ್ಯ, DECL_SOURCE_LOCATION (decl));
}

ಶೂನ್ಯ
ತೆಗೆ_file_scope (ಶೂನ್ಯ)
{
  /* In case there were missing closebraces, get us back to the global
     binding level.  */
  ಯಾವತ್ (current_scope != file_scope)
    ತೆಗೆ_scope ();

  /* __FUNCTION__ is defined at file scope ("").  This
     call may not be necessary as my tests indicate it
     still works without it.  */
  finish_fname_decls ();

  check_inline_statics ();

  /* This is the point to write out a PCH if we're doing that.
     In that case we do not want to do anything else.  */
  ಯದಿ (pch_file)
    {
      c_common_write_pch ();
      /* Ensure even the callers don't try to finalize the CU.  */
      flag_syntax_only = 1;
      ಪ್ರತ್ಯಾಗಮ;
    }

  /* Pop off the file scope and close this translation unit.  */
  ತೆಗೆ_scope ();
  file_scope = 0;

  maybe_apply_pending_pragma_weaks ();
}

/* Whether we are currently inside the initializer for an
   underspecified object definition (C23 auto or constexpr).  */
ಸ್ಥಿರ ತಾರ್ಕಿಕ in_underspecified_init;

/* Start an underspecified object definition for NAME at LOC.  This
   means that NAME is shadowed inside its initializer, so neither the
   definition being initialized, nor any definition from an outer
   scope, may be referenced during that initializer.  Return state to
   be passed to finish_underspecified_init.  If NAME is NULL_TREE, the
   underspecified object is a (constexpr) compound literal; there is
   no shadowing in that case, but all the other restrictions on
   underspecified object definitions still apply.  */
unsigned ಪೂರ್ಣಾಙ್ಕ
start_underspecified_init (location_t loc, ವೃಕ್ಷ name)
{
  ತಾರ್ಕಿಕ prev = in_underspecified_init;
  ತಾರ್ಕಿಕ ok;
  ಯದಿ (name == NULL_ವೃಕ್ಷ)
    ok = ಸತ್ಯ;
  ಅನ್ಯಥಾ
    {
      ವೃಕ್ಷ decl = build_decl (loc, VAR_DECL, name, error_mark_ಗಂಟು);
      C_DECL_UNDERSPECIFIED (decl) = 1;
      ಸಂರಚನಾ c_scope *scope = current_scope;
      ಸಂರಚನಾ c_binding *b = I_ಚಿಹ್ನೆ_BINDING (name);
      ಯದಿ (b && B_IN_SCOPE (b, scope))
	{
	  error_at (loc, "underspecified declaration of %qE, which is already "
		    "declared in this scope", name);
	  ok = ಅಸತ್ಯ;
	}
      ಅನ್ಯಥಾ
	{
	  bind (name, decl, scope, ಅಸತ್ಯ, ಅಸತ್ಯ, loc);
	  ok = ಸತ್ಯ;
	}
    }
  in_underspecified_init = ಸತ್ಯ;
  ಪ್ರತ್ಯಾಗಮ ok | (prev << 1);
}

/* Finish an underspecified object definition for NAME, before that
   name is bound to the real declaration instead of a placeholder.
   PREV_STATE is the value returned by the call to
   start_underspecified_init.  If NAME is NULL_TREE, this means a
   compound literal, as for start_underspecified_init.  */
ಶೂನ್ಯ
finish_underspecified_init (ವೃಕ್ಷ name, unsigned ಪೂರ್ಣಾಙ್ಕ prev_state)
{
  ಯದಿ (name != NULL_ವೃಕ್ಷ && (prev_state & 1))
    {
      /* A VAR_DECL was bound to the name to shadow any previous
	 declarations for the name; remove that binding now.  */
      ಸಂರಚನಾ c_scope *scope = current_scope;
      ಸಂರಚನಾ c_binding *b = I_ಚಿಹ್ನೆ_BINDING (name);
      gcc_assert (b);
      gcc_assert (B_IN_SCOPE (b, scope));
      gcc_assert (VAR_P (b->decl));
      gcc_assert (C_DECL_UNDERSPECIFIED (b->decl));
      I_ಚಿಹ್ನೆ_BINDING (name) = b->shadowed;
      /* In erroneous cases there may be other bindings added to this
	 scope during the initializer.  */
      ಸಂರಚನಾ c_binding **p = &scope->bindings;
      ಯಾವತ್ (*p != b)
	p = &((*p)->prev);
      *p = free_binding_and_advance (*p);
    }
  in_underspecified_init = (prev_state & (1u << 1)) >> 1;
}

/* Adjust the bindings for the start of a statement expression.  */

ಶೂನ್ಯ
c_bindings_start_stmt_ಅಭಿವ್ಯಕ್ತಿ (ಸಂರಚನಾ c_spot_bindings* switch_bindings)
{
  ಸಂರಚನಾ c_scope *scope;

  ಪ್ರತಿ (scope = current_scope; scope != ರಿಕ್ತ; scope = scope->outer)
    {
      ಸಂರಚನಾ c_binding *b;

      ಯದಿ (!scope->has_label_bindings)
	ಅನುವರ್ತ;

      ಪ್ರತಿ (b = scope->bindings; b != ರಿಕ್ತ; b = b->prev)
	{
	  ಸಂರಚನಾ c_label_vars *label_vars;
	  unsigned ಪೂರ್ಣಾಙ್ಕ ix;
	  ಸಂರಚನಾ c_goto_bindings *g;

	  ಯದಿ (ವೃಕ್ಷ_CODE (b->decl) != LABEL_DECL)
	    ಅನುವರ್ತ;
	  label_vars = b->u.label;
	  ++label_vars->label_bindings.stmt_exprs;
	  FOR_EACH_VEC_SAFE_ELT (label_vars->gotos, ix, g)
	    ++g->goto_bindings.stmt_exprs;
	}
    }

  ಯದಿ (switch_bindings != ರಿಕ್ತ)
    ++switch_bindings->stmt_exprs;
}

/* Adjust the bindings for the end of a statement expression.  */

ಶೂನ್ಯ
c_bindings_end_stmt_ಅಭಿವ್ಯಕ್ತಿ (ಸಂರಚನಾ c_spot_bindings *switch_bindings)
{
  ಸಂರಚನಾ c_scope *scope;

  ಪ್ರತಿ (scope = current_scope; scope != ರಿಕ್ತ; scope = scope->outer)
    {
      ಸಂರಚನಾ c_binding *b;

      ಯದಿ (!scope->has_label_bindings)
	ಅನುವರ್ತ;

      ಪ್ರತಿ (b = scope->bindings; b != ರಿಕ್ತ; b = b->prev)
	{
	  ಸಂರಚನಾ c_label_vars *label_vars;
	  unsigned ಪೂರ್ಣಾಙ್ಕ ix;
	  ಸಂರಚನಾ c_goto_bindings *g;

	  ಯದಿ (ವೃಕ್ಷ_CODE (b->decl) != LABEL_DECL)
	    ಅನುವರ್ತ;
	  label_vars = b->u.label;
	  --label_vars->label_bindings.stmt_exprs;
	  ಯದಿ (label_vars->label_bindings.stmt_exprs < 0)
	    {
	      label_vars->label_bindings.ಎಡ_stmt_ಅಭಿವ್ಯಕ್ತಿ = ಸತ್ಯ;
	      label_vars->label_bindings.stmt_exprs = 0;
	    }
	  FOR_EACH_VEC_SAFE_ELT (label_vars->gotos, ix, g)
	    {
	      --g->goto_bindings.stmt_exprs;
	      ಯದಿ (g->goto_bindings.stmt_exprs < 0)
		{
		  g->goto_bindings.ಎಡ_stmt_ಅಭಿವ್ಯಕ್ತಿ = ಸತ್ಯ;
		  g->goto_bindings.stmt_exprs = 0;
		}
	    }
	}
    }

  ಯದಿ (switch_bindings != ರಿಕ್ತ)
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
  ಯದಿ (name && !TYPE_NAME (type))
    TYPE_NAME (type) = name;
  bind (name, type, current_scope, /*invisible=*/ಅಸತ್ಯ, /*nested=*/ಅಸತ್ಯ, loc);

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

  ಯದಿ (warn_cxx_compat && name != NULL_ವೃಕ್ಷ)
    {
      ಸಂರಚನಾ c_binding *b = I_ಚಿಹ್ನೆ_BINDING (name);

      ಯದಿ (b != ರಿಕ್ತ
	  && b->decl != NULL_ವೃಕ್ಷ
	  && ವೃಕ್ಷ_CODE (b->decl) == TYPE_DECL
	  && (B_IN_CURRENT_SCOPE (b)
	      || (current_scope == file_scope && B_IN_EXTERNAL_SCOPE (b)))
	  && (TYPE_MAIN_VARIANT (ವೃಕ್ಷ_TYPE (b->decl))
	      != TYPE_MAIN_VARIANT (type)))
	{
	  auto_diagnostic_group d;
	  ಯದಿ (warning_at (loc, OPT_Wc___compat,
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
  ಸಂರಚನಾ c_scope *scope;
  ತಾರ್ಕಿಕ nested = ಅಸತ್ಯ;

  ಯದಿ (!VAR_P (decl) || current_function_scope == ರಿಕ್ತ)
    {
      /* Types and functions are always considered to be global.  */
      scope = file_scope;
      DECL_EXTERNAL (decl) = 1;
      ವೃಕ್ಷ_PUBLIC (decl) = 1;
    }
  ಅನ್ಯಥಾ ಯದಿ (is_global)
    {
      /* Also bind it into the external scope.  */
      bind (DECL_NAME (decl), decl, external_scope, ಸತ್ಯ, ಅಸತ್ಯ, loc);
      nested = ಸತ್ಯ;
      scope = file_scope;
      DECL_EXTERNAL (decl) = 1;
      ವೃಕ್ಷ_PUBLIC (decl) = 1;
    }
  ಅನ್ಯಥಾ
    {
      DECL_CONTEXT (decl) = current_function_decl;
      ವೃಕ್ಷ_PUBLIC (decl) = 0;
      scope = current_function_scope;
    }

  bind (DECL_NAME (decl), decl, scope, ಅಸತ್ಯ, nested, loc);
}


/* Stores the first FILE*, const struct tm* etc. argument type (whatever
   it is) seen in a declaration of a file I/O etc. built-in, corresponding
   to the builtin_structptr_types array.  Subsequent declarations of such
   built-ins are expected to refer to it rather than to fileptr_type_node,
   etc. which is just void* (or to any other type).
   Used only by match_builtin_function_types.  */

ಸ್ಥಿರ ಧ್ರುವ unsigned builtin_structptr_type_ಎಣಿಕೆ
  = ARRAY_SIZE (builtin_structptr_types);

ಸ್ಥಿರ GTY(()) ವೃಕ್ಷ last_structptr_types[builtin_structptr_type_ಎಣಿಕೆ];

/* Returns true if types T1 and T2 representing return types or types
   of function arguments are close enough to be considered interchangeable
   in redeclarations of built-in functions.  */

ಸ್ಥಿರ ತಾರ್ಕಿಕ
types_close_enough_to_match (ವೃಕ್ಷ t1, ವೃಕ್ಷ t2)
{
  ಪ್ರತ್ಯಾಗಮ (TYPE_MODE (t1) == TYPE_MODE (t2)
	  && POINTER_TYPE_P (t1) == POINTER_TYPE_P (t2)
	  && FUNCTION_POINTER_TYPE_P (t1) == FUNCTION_POINTER_TYPE_P (t2));
}

/* Subroutine of compare_decls.  Allow harmless mismatches in return
   and argument types provided that the type modes match.  Set *STRICT
   and *ARGNO to the expected argument type and number in case of
   an argument type mismatch or null and zero otherwise.  Return
   a unified type given a suitable match, and 0 otherwise.  */

ಸ್ಥಿರ ವೃಕ್ಷ
match_builtin_function_types (ವೃಕ್ಷ newtype, ವೃಕ್ಷ oldtype,
			      ವೃಕ್ಷ *strict, unsigned *argno)
{
  *argno = 0;
  *strict = NULL_ವೃಕ್ಷ;

  /* Accept the return type of the new declaration if it has the same
     mode and if they're both pointers or if neither is.  */
  ವೃಕ್ಷ oldrettype = ವೃಕ್ಷ_TYPE (oldtype);
  ವೃಕ್ಷ newrettype = ವೃಕ್ಷ_TYPE (newtype);

  ಯದಿ (!types_close_enough_to_match (oldrettype, newrettype))
    ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;

  /* Check that the return types are compatible but don't fail if they
     are not (e.g., int vs long in ILP32) and just let the caller know.  */
  ಯದಿ (!comptypes (TYPE_MAIN_VARIANT (oldrettype),
		  TYPE_MAIN_VARIANT (newrettype)))
    *strict = oldrettype;

  ವೃಕ್ಷ oldargs = TYPE_ARG_TYPES (oldtype);
  ವೃಕ್ಷ newargs = TYPE_ARG_TYPES (newtype);
  ವೃಕ್ಷ tryargs = newargs;

  ಧ್ರುವ unsigned nlst = ARRAY_SIZE (last_structptr_types);
  ಧ್ರುವ unsigned nbst = ARRAY_SIZE (builtin_structptr_types);

  gcc_checking_assert (nlst == nbst);

  ಪ್ರತಿ (unsigned i = 1; oldargs || newargs; ++i)
    {
      ಯದಿ (!oldargs
	  || !newargs
	  || !ವೃಕ್ಷ_ಮೌಲ್ಯ (oldargs)
	  || !ವೃಕ್ಷ_ಮೌಲ್ಯ (newargs))
	ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;

      ವೃಕ್ಷ oldtype = TYPE_MAIN_VARIANT (ವೃಕ್ಷ_ಮೌಲ್ಯ (oldargs));
      ವೃಕ್ಷ newtype = ವೃಕ್ಷ_ಮೌಲ್ಯ (newargs);
      ಯದಿ (newtype == error_mark_ಗಂಟು)
       ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;
      newtype = TYPE_MAIN_VARIANT (newtype);

      ಯದಿ (!types_close_enough_to_match (oldtype, newtype))
	ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;

      unsigned j = nbst;
      ಯದಿ (POINTER_TYPE_P (oldtype))
	/* Iterate over well-known struct types like FILE (whose types
	   aren't known to us) and compare the pointer to each to
	   the pointer argument.  */
	ಪ್ರತಿ (j = 0; j < nbst; ++j)
	  {
	    ಯದಿ (ವೃಕ್ಷ_ಮೌಲ್ಯ (oldargs) != builtin_structptr_types[j].ಗಂಟು)
	      ಅನುವರ್ತ;
	    /* Store the first FILE* etc. argument type (whatever it is), and
	       expect any subsequent declarations of file I/O etc. built-ins
	       to refer to it rather than to fileptr_type_node etc. which is
	       just void* (or const void*).  */
	    ಯದಿ (last_structptr_types[j])
	      {
		ಯದಿ (!comptypes (last_structptr_types[j], newtype))
		  {
		    *argno = i;
		    *strict = last_structptr_types[j];
		  }
	      }
	    ಅನ್ಯಥಾ
	      last_structptr_types[j] = newtype;
	    ಭಙ್ಗ;
	  }

      ಯದಿ (j == nbst && !comptypes (oldtype, newtype))
	{
	  ಯದಿ (POINTER_TYPE_P (oldtype))
	    {
	      /* For incompatible pointers, only reject differences in
		 the unqualified variants of the referenced types but
		 consider differences in qualifiers as benign (report
		 those to caller via *STRICT below).  */
	      ವೃಕ್ಷ oldref = TYPE_MAIN_VARIANT (ವೃಕ್ಷ_TYPE (oldtype));
	      ವೃಕ್ಷ newref = TYPE_MAIN_VARIANT (ವೃಕ್ಷ_TYPE (newtype));
	      ಯದಿ (!comptypes (oldref, newref))
		ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;
	    }

	  ಯದಿ (!*strict)
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
  ವೃಕ್ಷ oldattrs = TYPE_ATTRIBUTES (oldtype);
  ವೃಕ್ಷ oldtsafe = lookup_attribute ("transaction_safe", oldattrs);
  ವೃಕ್ಷ newattrs = TYPE_ATTRIBUTES (newtype);
  ವೃಕ್ಷ newtsafe = lookup_attribute ("transaction_safe", newattrs);
  ಯದಿ (oldtsafe && !newtsafe)
    oldattrs = remove_attribute ("transaction_safe", oldattrs);
  ಅನ್ಯಥಾ ಯದಿ (newtsafe && !oldtsafe)
    oldattrs = ವೃಕ್ಷ_cons (get_identifier ("transaction_safe"),
			  NULL_ವೃಕ್ಷ, oldattrs);

  ಪ್ರತ್ಯಾಗಮ c_build_type_attribute_variant (trytype, oldattrs);
}

/* Subroutine of diagnose_mismatched_decls.  Check for function type
   mismatch involving an empty arglist vs a nonempty one and give clearer
   diagnostics.  */
ಸ್ಥಿರ ಶೂನ್ಯ
diagnose_arglist_conflict (ವೃಕ್ಷ newdecl, ವೃಕ್ಷ olddecl,
			   ವೃಕ್ಷ newtype, ವೃಕ್ಷ oldtype)
{
  ವೃಕ್ಷ t;

  ಯದಿ (ವೃಕ್ಷ_CODE (olddecl) != FUNCTION_DECL
      || !comptypes (ವೃಕ್ಷ_TYPE (oldtype), ವೃಕ್ಷ_TYPE (newtype))
      || !((!prototype_p (oldtype) && DECL_INITIAL (olddecl) == NULL_ವೃಕ್ಷ)
	   || (!prototype_p (newtype) && DECL_INITIAL (newdecl) == NULL_ವೃಕ್ಷ)))
    ಪ್ರತ್ಯಾಗಮ;

  t = TYPE_ARG_TYPES (oldtype);
  ಯದಿ (t == NULL_ವೃಕ್ಷ)
    t = TYPE_ARG_TYPES (newtype);
  ಪ್ರತಿ (; t; t = ವೃಕ್ಷ_CHAIN (t))
    {
      ವೃಕ್ಷ type = ವೃಕ್ಷ_ಮೌಲ್ಯ (t);

      ಯದಿ (ವೃಕ್ಷ_CHAIN (t) == NULL_ವೃಕ್ಷ
	  && TYPE_MAIN_VARIANT (type) != void_type_ಗಂಟು)
	{
	  inform (ಒಳಹರಿವು_location, "a parameter list with an ellipsis "
		  "cannot match an empty parameter name list declaration");
	  ಭಙ್ಗ;
	}

      ಯದಿ (!error_operand_p (type)
	  && c_type_promotes_to (type) != type)
	{
	  inform (ಒಳಹರಿವು_location, "an argument type that has a default "
		  "promotion cannot match an empty parameter name list "
		  "declaration");
	  ಭಙ್ಗ;
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
  ಪೂರ್ಣಾಙ್ಕ i;

#define END_OF_ARGLIST(t) ((t) == void_type_ಗಂಟು)

  oldargs = TYPE_ACTUAL_ARG_TYPES (oldtype);
  newargs = TYPE_ARG_TYPES (newtype);
  i = 1;

  ಪ್ರತಿ (;;)
    {
      ವೃಕ್ಷ oldargtype = ವೃಕ್ಷ_ಮೌಲ್ಯ (oldargs);
      ವೃಕ್ಷ newargtype = ವೃಕ್ಷ_ಮೌಲ್ಯ (newargs);

      ಯದಿ (oldargtype == error_mark_ಗಂಟು || newargtype == error_mark_ಗಂಟು)
	ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;

      oldargtype = (TYPE_ATOMIC (oldargtype)
		    ? c_build_qualified_type (TYPE_MAIN_VARIANT (oldargtype),
					      TYPE_QUAL_ATOMIC)
		    : TYPE_MAIN_VARIANT (oldargtype));
      newargtype = (TYPE_ATOMIC (newargtype)
		    ? c_build_qualified_type (TYPE_MAIN_VARIANT (newargtype),
					      TYPE_QUAL_ATOMIC)
		    : TYPE_MAIN_VARIANT (newargtype));

      ಯದಿ (END_OF_ARGLIST (oldargtype) && END_OF_ARGLIST (newargtype))
	ಭಙ್ಗ;

      /* Reaching the end of just one list means the two decls don't
	 agree on the number of arguments.  */
      ಯದಿ (END_OF_ARGLIST (oldargtype))
	{
	  error ("prototype for %q+D declares more arguments "
		 "than previous old-style definition", newdecl);
	  ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
	}
      ಅನ್ಯಥಾ ಯದಿ (END_OF_ARGLIST (newargtype))
	{
	  error ("prototype for %q+D declares fewer arguments "
		 "than previous old-style definition", newdecl);
	  ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
	}

      /* Type for passing arg must be consistent with that declared
	 for the arg.  */
      ಅನ್ಯಥಾ ಯದಿ (!comptypes (oldargtype, newargtype))
	{
	  error ("prototype for %q+D declares argument %d"
		 " with incompatible type",
		 newdecl, i);
	  ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
	}

      oldargs = ವೃಕ್ಷ_CHAIN (oldargs);
      newargs = ವೃಕ್ಷ_CHAIN (newargs);
      i++;
    }

  /* If we get here, no errors were found, but do issue a warning
     for this poor-style construct.  */
  warning (0, "prototype for %q+D follows non-prototype definition",
	   newdecl);
  ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
#undef END_OF_ARGLIST
}

/* Subroutine of diagnose_mismatched_decls.  Report the location of DECL,
   first in a pair of mismatched declarations, using the diagnostic
   function DIAG.  */
ಸ್ಥಿರ ಶೂನ್ಯ
locate_old_decl (ವೃಕ್ಷ decl)
{
  ಯದಿ (ವೃಕ್ಷ_CODE (decl) == FUNCTION_DECL
      && fndecl_built_in_p (decl)
      && !C_DECL_DECLARED_BUILTIN (decl))
    ;
  ಅನ್ಯಥಾ ಯದಿ (DECL_INITIAL (decl))
    inform (ಒಳಹರಿವು_location,
	    "previous definition of %q+D with type %qT",
	    decl, ವೃಕ್ಷ_TYPE (decl));
  ಅನ್ಯಥಾ ಯದಿ (C_DECL_IMPLICIT (decl))
    inform (ಒಳಹರಿವು_location,
	    "previous implicit declaration of %q+D with type %qT",
	    decl, ವೃಕ್ಷ_TYPE (decl));
  ಅನ್ಯಥಾ
    inform (ಒಳಹರಿವು_location,
	    "previous declaration of %q+D with type %qT",
	    decl, ವೃಕ್ಷ_TYPE (decl));
}


/* Helper function.  For a tagged type, it finds the declaration
   for a visible tag declared in the same scope if such a
   declaration exists.  */
ಸ್ಥಿರ ವೃಕ್ಷ
previous_tag (ವೃಕ್ಷ type)
{
  ಸಂರಚನಾ c_binding *b = ರಿಕ್ತ;
  ವೃಕ್ಷ name = c_type_tag (type);

  ಯದಿ (name)
    b = I_TAG_BINDING (name);

  ಯದಿ (b)
    b = b->shadowed;

  ಯದಿ (b && B_IN_CURRENT_SCOPE (b))
    ಪ್ರತ್ಯಾಗಮ b->decl;

  ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;
}

/* Subroutine to mark functions as versioned when using the attribute
   'target_version'.  */

ಸ್ಥಿರ ಶೂನ್ಯ
maybe_mark_function_versioned (ವೃಕ್ಷ decl)
{
  ಯದಿ (!DECL_FUNCTION_VERSIONED (decl))
    {
      /* Check if the name of the function has been overridden.  */
      ಯದಿ (DECL_ASSEMBLER_NAME_SET_P (decl)
	  && IDENTIFIER_POINTER (DECL_ASSEMBLER_NAME (decl))[0] == '*')
	error_at (DECL_SOURCE_LOCATION (decl),
		  "cannot use function multiversioning on a renamed function");

      /* We need to insert function version now to make sure the correct
	 pre-mangled assembler name is recorded.  */
      cgraph_ಗಂಟು *ಗಂಟು = cgraph_ಗಂಟು::get_create (decl);

      ಯದಿ (!ಗಂಟು->function_version ())
	ಗಂಟು->ಸೇರಿಸು_new_function_version ();

      DECL_FUNCTION_VERSIONED (decl) = 1;

      ವೃಕ್ಷ mangled_name
	= targetm.mangle_decl_assembler_name (decl, DECL_NAME (decl));
      SET_DECL_ASSEMBLER_NAME (decl, mangled_name);
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
  ತಾರ್ಕಿಕ retval = ಸತ್ಯ;

#define DECL_EXTERN_INLINE(DECL) (DECL_DECLARED_INLINE_P (DECL)  \
				  && DECL_EXTERNAL (DECL))

  /* If we have error_mark_node for either decl or type, just discard
     the previous decl - we're in an error cascade already.  */
  ಯದಿ (olddecl == error_mark_ಗಂಟು || newdecl == error_mark_ಗಂಟು)
    ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
  *oldtypep = oldtype = ವೃಕ್ಷ_TYPE (olddecl);
  *newtypep = newtype = ವೃಕ್ಷ_TYPE (newdecl);
  ಯದಿ (oldtype == error_mark_ಗಂಟು || newtype == error_mark_ಗಂಟು)
    ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;

  /* Two different categories of symbol altogether.  This is an error
     unless OLDDECL is a builtin.  OLDDECL will be discarded in any case.  */
  ಯದಿ (ವೃಕ್ಷ_CODE (olddecl) != ವೃಕ್ಷ_CODE (newdecl))
    {
      ಯದಿ (!(ವೃಕ್ಷ_CODE (olddecl) == FUNCTION_DECL
	    && fndecl_built_in_p (olddecl)
	    && !C_DECL_DECLARED_BUILTIN (olddecl)))
	{
	  auto_diagnostic_group d;
	  error ("%q+D redeclared as different kind of symbol", newdecl);
	  locate_old_decl (olddecl);
	}
      ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_PUBLIC (newdecl))
	warning (OPT_Wbuiltin_declaration_mismatch,
		 "built-in function %q+D declared as non-function",
		 newdecl);
      ಅನ್ಯಥಾ
	warning (OPT_Wshadow, "declaration of %q+D shadows "
		 "a built-in function", newdecl);
      ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
    }

  /* Enumerators have no linkage, so may only be declared once in a
     given scope.  */
  ಯದಿ (ವೃಕ್ಷ_CODE (olddecl) == CONST_DECL)
    {
      ಯದಿ (flag_isoc23
	  && TYPE_NAME (DECL_CONTEXT (newdecl))
	  && DECL_CONTEXT (newdecl) != DECL_CONTEXT (olddecl)
	  && TYPE_NAME (DECL_CONTEXT (newdecl)) == TYPE_NAME (DECL_CONTEXT (olddecl)))
	{
	  ಯದಿ (!simple_cst_equal (DECL_INITIAL (olddecl), DECL_INITIAL (newdecl)))
	    {
	      auto_diagnostic_group d;
	      error ("conflicting redeclaration of enumerator %q+D", newdecl);
	      locate_old_decl (olddecl);
	    }
	}
      ಅನ್ಯಥಾ
	{
	  auto_diagnostic_group d;
	  error ("redeclaration of enumerator %q+D", newdecl);
	  locate_old_decl (olddecl);
	}
      ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
    }

  ತಾರ್ಕಿಕ pedwarned = ಅಸತ್ಯ;
  ತಾರ್ಕಿಕ warned = ಅಸತ್ಯ;
  ತಾರ್ಕಿಕ enum_and_int_p = ಅಸತ್ಯ;
  auto_diagnostic_group d;

  ತಾರ್ಕಿಕ comptypes_result = comptypes_check_enum_int (oldtype, newtype,
						    &enum_and_int_p);
  ಯದಿ (!comptypes_result)
    {
      ಯದಿ (ವೃಕ್ಷ_CODE (olddecl) == FUNCTION_DECL
	  && fndecl_built_in_p (olddecl, BUILT_IN_NORMAL)
	  && !C_DECL_DECLARED_BUILTIN (olddecl))
	{
	  /* Accept "harmless" mismatches in function types such
	     as missing qualifiers or int vs long when they're the same
	     size.  However, diagnose return and argument types that are
	     incompatible according to language rules.  */
	  ವೃಕ್ಷ mismatch_expect;
	  unsigned mismatch_argno;

	  ವೃಕ್ಷ trytype = match_builtin_function_types (newtype, oldtype,
						       &mismatch_expect,
						       &mismatch_argno);

	  ಯದಿ (trytype && comptypes (newtype, trytype))
	    *oldtypep = oldtype = trytype;
	  ಅನ್ಯಥಾ
	    {
	      /* If types don't match for a built-in, throw away the
		 built-in.  No point in calling locate_old_decl here, it
		 won't print anything.  */
	      ಧ್ರುವ ವರ್ಣ *header = header_for_builtin_fn (olddecl);
	      location_t loc = DECL_SOURCE_LOCATION (newdecl);
	      ಯದಿ (warning_at (loc, OPT_Wbuiltin_declaration_mismatch,
			      "conflicting types for built-in function %q+D; "
			      "expected %qT",
			      newdecl, oldtype)
		  && header)
		{
		  /* Suggest the right header to include as the preferred
		     solution rather than the spelling of the declaration.  */
		  rich_location richloc (ಸಾಲು_table, loc);
		  maybe_add_include_fixit (&richloc, header, ಸತ್ಯ);
		  inform (&richloc,
			  "%qD is declared in header %qs", olddecl, header);
		}
	      ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
	    }

	  ಯದಿ (mismatch_expect && extra_warnings)
	    {
	      location_t newloc = DECL_SOURCE_LOCATION (newdecl);
	      ತಾರ್ಕಿಕ warned = ಅಸತ್ಯ;
	      ಯದಿ (mismatch_argno)
		warned = warning_at (newloc, OPT_Wbuiltin_declaration_mismatch,
				     "mismatch in argument %u type of built-in "
				     "function %qD; expected %qT",
				     mismatch_argno, newdecl, mismatch_expect);
	      ಅನ್ಯಥಾ
		warned = warning_at (newloc, OPT_Wbuiltin_declaration_mismatch,
				     "mismatch in return type of built-in "
				     "function %qD; expected %qT",
				     newdecl, mismatch_expect);
	      ಧ್ರುವ ವರ್ಣ *header = header_for_builtin_fn (olddecl);
	      ಯದಿ (warned && header)
		{
		  rich_location richloc (ಸಾಲು_table, newloc);
		  maybe_add_include_fixit (&richloc, header, ಸತ್ಯ);
		  inform (&richloc,
			  "%qD is declared in header %qs", olddecl, header);
		}
	    }
	}
      ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_CODE (olddecl) == FUNCTION_DECL
	       && DECL_IS_UNDECLARED_BUILTIN (olddecl))
	{
	  /* A conflicting function declaration for a predeclared
	     function that isn't actually built in.  Objective C uses
	     these.  The new declaration silently overrides everything
	     but the volatility (i.e. noreturn) indication.  See also
	     below.  FIXME: Make Objective C use normal builtins.  */
	  ವೃಕ್ಷ_THIS_VOLATILE (newdecl) |= ವೃಕ್ಷ_THIS_VOLATILE (olddecl);
	  ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
	}
      /* Permit void foo (...) to match int foo (...) if the latter is
	 the definition and implicit int was used.  See
	 c-torture/compile/920625-2.c.  */
      ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_CODE (newdecl) == FUNCTION_DECL && DECL_INITIAL (newdecl)
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
      ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_CODE (newdecl) == FUNCTION_DECL
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
      ಅನ್ಯಥಾ
	{
	  ಪೂರ್ಣಾಙ್ಕ new_quals = TYPE_QUALS (newtype);
	  ಪೂರ್ಣಾಙ್ಕ old_quals = TYPE_QUALS (oldtype);

	  ಯದಿ (new_quals != old_quals)
	    {
	      addr_space_t new_addr = DECODE_QUAL_ADDR_SPACE (new_quals);
	      addr_space_t old_addr = DECODE_QUAL_ADDR_SPACE (old_quals);
	      ಯದಿ (new_addr != old_addr)
		{
		  ಯದಿ (ADDR_SPACE_GENERIC_P (new_addr))
		    error ("conflicting named address spaces (generic vs %s) "
			   "for %q+D",
			   c_addr_space_name (old_addr), newdecl);
		  ಅನ್ಯಥಾ ಯದಿ (ADDR_SPACE_GENERIC_P (old_addr))
		    error ("conflicting named address spaces (%s vs generic) "
			   "for %q+D",
			   c_addr_space_name (new_addr), newdecl);
		  ಅನ್ಯಥಾ
		    error ("conflicting named address spaces (%s vs %s) "
			   "for %q+D",
			   c_addr_space_name (new_addr),
			   c_addr_space_name (old_addr),
			   newdecl);
		}

	      ಯದಿ (CLEAR_QUAL_ADDR_SPACE (new_quals)
		  != CLEAR_QUAL_ADDR_SPACE (old_quals))
		error ("conflicting type qualifiers for %q+D", newdecl);
	    }
	  ಅನ್ಯಥಾ
	    {
	      ಯದಿ (ವೃಕ್ಷ_CODE (olddecl) == FUNCTION_DECL)
		{
		  ವೃಕ್ಷ attrs = TYPE_ATTRIBUTES (ವೃಕ್ಷ_TYPE (olddecl));
		  ಯದಿ (attrs && !TYPE_ATTRIBUTES (ವೃಕ್ಷ_TYPE (newdecl)))
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
		      ಯದಿ (comptypes (oldtype, trytype))
			{
			  *newtypep = newtype = trytype;
			  comptypes_result = ಸತ್ಯ;
			}
		    }
		}

	      ಯದಿ (!comptypes_result)
		error ("conflicting types for %q+D; have %qT", newdecl,
		       newtype);
	    }
	  ಯದಿ (!comptypes_result)
	    {
	      diagnose_arglist_conflict (newdecl, olddecl, newtype,
					 oldtype);
	      locate_old_decl (olddecl);
	      ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
	    }
	}
    }
  /* Warn about enum/integer type mismatches.  They are compatible types
     (C23 6.7.2.2/5), but may pose portability problems.  */
  ಅನ್ಯಥಾ ಯದಿ (enum_and_int_p
	   && ವೃಕ್ಷ_CODE (newdecl) != TYPE_DECL
	   /* Don't warn about acc_on_device built-in redeclaration,
	      the built-in is declared with int rather than enum because
	      the enum isn't intrinsic.  */
	   && !(ವೃಕ್ಷ_CODE (olddecl) == FUNCTION_DECL
		&& fndecl_built_in_p (olddecl, BUILT_IN_ACC_ON_DEVICE)
		&& !C_DECL_DECLARED_BUILTIN (olddecl)))
    warned = warning_at (DECL_SOURCE_LOCATION (newdecl),
			 OPT_Wenum_int_mismatch,
			 "conflicting types for %q+D due to enum/integer "
			 "mismatch; have %qT", newdecl, newtype);

  /* Redeclaration of a type is a constraint violation (6.7.2.3p1),
     but silently ignore the redeclaration if either is in a system
     header.  (Conflicting redeclarations were handled above.)  This
     is allowed for C11 if the types are the same, not just
     compatible.  */
  ಯದಿ (ವೃಕ್ಷ_CODE (newdecl) == TYPE_DECL)
    {
      ಯದಿ (!comptypes_same_p (oldtype, newtype))
	{
	  error ("redefinition of typedef %q+D with different type", newdecl);
	  locate_old_decl (olddecl);
	  ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
	}

      ಯದಿ (DECL_IN_SYSTEM_HEADER (newdecl)
	  || DECL_IN_SYSTEM_HEADER (olddecl)
	  || warning_suppressed_p (newdecl, OPT_Wpedantic)
	  || warning_suppressed_p (olddecl, OPT_Wpedantic))
	ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;  /* Allow OLDDECL to continue in use.  */

      ಯದಿ (c_type_variably_modified_p (newtype))
	{
	  error ("redefinition of typedef %q+D with variably modified type",
		 newdecl);
	  locate_old_decl (olddecl);
	}
      ಅನ್ಯಥಾ ಯದಿ (pedwarn_c99 (ಒಳಹರಿವು_location, OPT_Wpedantic,
			    "redefinition of typedef %q+D", newdecl))
	locate_old_decl (olddecl);

      ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
    }

  /* Function declarations can either be 'static' or 'extern' (no
     qualifier is equivalent to 'extern' - C99 6.2.2p5) and therefore
     can never conflict with each other on account of linkage
     (6.2.2p4).  Multiple definitions are not allowed (6.9p3,5) but
     gnu89 mode permits two definitions if one is 'extern inline' and
     one is not.  The non- extern-inline definition supersedes the
     extern-inline definition.  */

  ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_CODE (newdecl) == FUNCTION_DECL)
    {
      /* If you declare a built-in function name as static, or
	 define the built-in with an old-style definition (so we
	 can't validate the argument list) the built-in definition is
	 overridden, but optionally warn this was a bad choice of name.  */
      ಯದಿ (fndecl_built_in_p (olddecl)
	  && !C_DECL_DECLARED_BUILTIN (olddecl))
	{
	  ಯದಿ (!ವೃಕ್ಷ_PUBLIC (newdecl)
	      || (DECL_INITIAL (newdecl)
		  && !prototype_p (ವೃಕ್ಷ_TYPE (newdecl))))
	    {
	      warning_at (DECL_SOURCE_LOCATION (newdecl),
			  OPT_Wshadow, "declaration of %qD shadows "
			  "a built-in function", newdecl);
	      /* Discard the old built-in function.  */
	      ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
	    }

	  ಯದಿ (!prototype_p (ವೃಕ್ಷ_TYPE (newdecl)))
	    {
	      /* Set for built-ins that take no arguments.  */
	      ತಾರ್ಕಿಕ func_void_args = ಅಸತ್ಯ;
	      ಯದಿ (ವೃಕ್ಷ at = TYPE_ARG_TYPES (oldtype))
		func_void_args = VOID_TYPE_P (ವೃಕ್ಷ_ಮೌಲ್ಯ (at));

	      ಯದಿ (extra_warnings && !func_void_args)
		warning_at (DECL_SOURCE_LOCATION (newdecl),
			    OPT_Wbuiltin_declaration_mismatch,
			    "declaration of built-in function %qD without "
			    "a prototype; expected %qT",
			    newdecl, ವೃಕ್ಷ_TYPE (olddecl));
	    }
	}

      ಯದಿ (DECL_INITIAL (newdecl))
	{
	  ಯದಿ (DECL_INITIAL (olddecl))
	    {
	      /* If the new declaration isn't overriding an extern inline
		 reject the new decl. In c99, no overriding is allowed
		 in the same translation unit.  */
	      ಯದಿ (!DECL_EXTERN_INLINE (olddecl)
		  || DECL_EXTERN_INLINE (newdecl)
		  || (!flag_gnu89_inline
		      && (!DECL_DECLARED_INLINE_P (olddecl)
			  || !lookup_attribute ("gnu_inline",
						DECL_ATTRIBUTES (olddecl)))
		      && (!DECL_DECLARED_INLINE_P (newdecl)
			  || !lookup_attribute ("gnu_inline",
						DECL_ATTRIBUTES (newdecl)))))
		{
		  auto_diagnostic_group d;
		  error ("redefinition of %q+D", newdecl);
		  locate_old_decl (olddecl);
		  ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
		}
	    }
	}
      /* If we have a prototype after an old-style function definition,
	 the argument types must be checked specially.  */
      ಅನ್ಯಥಾ ಯದಿ (DECL_INITIAL (olddecl)
	       && !prototype_p (oldtype) && prototype_p (newtype)
	       && TYPE_ACTUAL_ARG_TYPES (oldtype))
	{
	  auto_diagnostic_group d;
	  ಯದಿ (!validate_proto_after_old_defn (newdecl, newtype, oldtype))
	    {
	      locate_old_decl (olddecl);
	      ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
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
      ಯದಿ (ವೃಕ್ಷ_PUBLIC (olddecl) && !ವೃಕ್ಷ_PUBLIC (newdecl))
	{
	  /* Two exceptions to the rule.  If olddecl is an extern
	     inline, or a predeclared function that isn't actually
	     built in, newdecl silently overrides olddecl.  The latter
	     occur only in Objective C; see also above.  (FIXME: Make
	     Objective C use normal builtins.)  */
	  ಯದಿ (!DECL_IS_UNDECLARED_BUILTIN (olddecl)
	      && !DECL_EXTERN_INLINE (olddecl))
	    {
	      auto_diagnostic_group d;
	      error ("static declaration of %q+D follows "
		     "non-static declaration", newdecl);
	      locate_old_decl (olddecl);
	    }
	  ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
	}
      ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_PUBLIC (newdecl) && !ವೃಕ್ಷ_PUBLIC (olddecl))
	{
	  ಯದಿ (DECL_CONTEXT (olddecl))
	    {
	      auto_diagnostic_group d;
	      error ("non-static declaration of %q+D follows "
		     "static declaration", newdecl);
	      locate_old_decl (olddecl);
	      ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
	    }
	  ಅನ್ಯಥಾ ಯದಿ (warn_traditional)
	    {
	      warned |= warning (OPT_Wtraditional,
				 "non-static declaration of %q+D "
				 "follows static declaration", newdecl);
	    }
	}

      /* Make sure gnu_inline attribute is either not present, or
	 present on all inline decls.  */
      ಯದಿ (DECL_DECLARED_INLINE_P (olddecl)
	  && DECL_DECLARED_INLINE_P (newdecl))
	{
	  ತಾರ್ಕಿಕ newa = lookup_attribute ("gnu_inline",
					DECL_ATTRIBUTES (newdecl)) != ರಿಕ್ತ;
	  ತಾರ್ಕಿಕ olda = lookup_attribute ("gnu_inline",
					DECL_ATTRIBUTES (olddecl)) != ರಿಕ್ತ;
	  ಯದಿ (newa != olda)
	    {
	      auto_diagnostic_group d;
	      error_at (ಒಳಹರಿವು_location, "%<gnu_inline%> attribute present on %q+D",
			newa ? newdecl : olddecl);
	      error_at (DECL_SOURCE_LOCATION (newa ? olddecl : newdecl),
			"but not here");
	    }
	}
      /* Check if these are unmergeable overlapping FMV declarations.  */
      ಯದಿ (!TARGET_HAS_FMV_TARGET_ATTRIBUTE
	  && diagnose_versioned_decls (olddecl, newdecl))
	ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
    }
  ಅನ್ಯಥಾ ಯದಿ (VAR_P (newdecl))
    {
      /* Only variables can be thread-local, and all declarations must
	 agree on this property.  */
      ಯದಿ (C_DECL_THREADPRIVATE_P (olddecl) && !DECL_THREAD_LOCAL_P (newdecl))
	{
	  /* Nothing to check.  Since OLDDECL is marked threadprivate
	     and NEWDECL does not have a thread-local attribute, we
	     will merge the threadprivate attribute into NEWDECL.  */
	  ;
	}
      ಅನ್ಯಥಾ ಯದಿ (DECL_THREAD_LOCAL_P (newdecl) != DECL_THREAD_LOCAL_P (olddecl))
	{
	  auto_diagnostic_group d;
	  ಯದಿ (DECL_THREAD_LOCAL_P (newdecl))
	    error ("thread-local declaration of %q+D follows "
		   "non-thread-local declaration", newdecl);
	  ಅನ್ಯಥಾ
	    error ("non-thread-local declaration of %q+D follows "
		   "thread-local declaration", newdecl);

	  locate_old_decl (olddecl);
	  ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
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
      ಯದಿ ((DECL_INITIAL (newdecl) && DECL_INITIAL (olddecl))
	  || (flag_isoc23
	      && DECL_THREAD_LOCAL_P (newdecl)
	      && !DECL_EXTERNAL (newdecl)
	      && !DECL_EXTERNAL (olddecl)))
	{
	  auto_diagnostic_group d;
	  error ("redefinition of %q+D", newdecl);
	  locate_old_decl (olddecl);
	  ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
	}

      /* Objects declared at file scope: if the first declaration had
	 external linkage (even if it was an external reference) the
	 second must have external linkage as well, or the behavior is
	 undefined.  If the first declaration had internal linkage, then
	 the second must too, or else be an external reference (in which
	 case the composite declaration still has internal linkage).
	 As for function declarations, we warn about the static-then-
	 extern case only for -Wtraditional.  See generally 6.2.2p3-5,7.  */
      ಯದಿ (DECL_FILE_SCOPE_P (newdecl)
	  && ವೃಕ್ಷ_PUBLIC (newdecl) != ವೃಕ್ಷ_PUBLIC (olddecl))
	{
	  ಯದಿ (DECL_EXTERNAL (newdecl))
	    {
	      ಯದಿ (!DECL_FILE_SCOPE_P (olddecl))
		{
		  auto_diagnostic_group d;
		  error ("extern declaration of %q+D follows "
			 "declaration with no linkage", newdecl);
		  locate_old_decl (olddecl);
		  ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
		}
	      ಅನ್ಯಥಾ ಯದಿ (warn_traditional)
		{
		  warned |= warning (OPT_Wtraditional,
				     "non-static declaration of %q+D "
				     "follows static declaration", newdecl);
		}
	    }
	  ಅನ್ಯಥಾ
	    {
	      auto_diagnostic_group d;
	      ಯದಿ (ವೃಕ್ಷ_PUBLIC (newdecl))
		error ("non-static declaration of %q+D follows "
		       "static declaration", newdecl);
	      ಅನ್ಯಥಾ
		error ("static declaration of %q+D follows "
		       "non-static declaration", newdecl);

	      locate_old_decl (olddecl);
	      ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
	    }
	}
      /* Two objects with the same name declared at the same block
	 scope must both be external references (6.7p3).  */
      ಅನ್ಯಥಾ ಯದಿ (!DECL_FILE_SCOPE_P (newdecl))
	{
	  ಯದಿ (DECL_EXTERNAL (newdecl))
	    {
	      /* Extern with initializer at block scope, which will
		 already have received an error.  */
	    }
	  ಅನ್ಯಥಾ ಯದಿ (DECL_EXTERNAL (olddecl))
	    {
	      auto_diagnostic_group d;
	      error ("declaration of %q+D with no linkage follows "
		     "extern declaration", newdecl);
	      locate_old_decl (olddecl);
	    }
	  ಅನ್ಯಥಾ
	    {
	      auto_diagnostic_group d;
	      error ("redeclaration of %q+D with no linkage", newdecl);
	      locate_old_decl (olddecl);
	    }

	  ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
	}

      /* C++ does not permit a decl to appear multiple times at file
	 scope.  */
      ಯದಿ (warn_cxx_compat
	  && DECL_FILE_SCOPE_P (newdecl)
	  && !DECL_EXTERNAL (newdecl)
	  && !DECL_EXTERNAL (olddecl))
	warned |= warning_at (DECL_SOURCE_LOCATION (newdecl),
			      OPT_Wc___compat,
			      "duplicate declaration of %qD is "
			      "invalid in C++", newdecl);
    }

  /* warnings */
  /* All decls must agree on a visibility.  */
  ಯದಿ (CODE_CONTAINS_STRUCT (ವೃಕ್ಷ_CODE (newdecl), TS_DECL_WITH_VIS)
      && DECL_VISIBILITY_SPECIFIED (newdecl) && DECL_VISIBILITY_SPECIFIED (olddecl)
      && DECL_VISIBILITY (newdecl) != DECL_VISIBILITY (olddecl))
    {
      warned |= warning (0, "redeclaration of %q+D with different visibility "
			 "(old visibility preserved)", newdecl);
    }

  ಯದಿ (ವೃಕ್ಷ_CODE (newdecl) == FUNCTION_DECL)
    warned |= diagnose_mismatched_attributes (olddecl, newdecl);
  ಅನ್ಯಥಾ /* PARM_DECL, VAR_DECL */
    {
      /* Redeclaration of a parameter is a constraint violation (this is
	 not explicitly stated, but follows from C99 6.7p3 [no more than
	 one declaration of the same identifier with no linkage in the
	 same scope, except type tags] and 6.2.2p6 [parameters have no
	 linkage]).  We must check for a forward parameter declaration,
	 indicated by TREE_ASM_WRITTEN on the old declaration - this is
	 an extension, the mandatory diagnostic for which is handled by
	 mark_forward_parm_decls.  */

      ಯದಿ (ವೃಕ್ಷ_CODE (newdecl) == PARM_DECL
	  && (!ವೃಕ್ಷ_ASM_WRITTEN (olddecl) || ವೃಕ್ಷ_ASM_WRITTEN (newdecl)))
	{
	  auto_diagnostic_group d;
	  error ("redefinition of parameter %q+D", newdecl);
	  locate_old_decl (olddecl);
	  ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
	}
    }

  /* Optional warning for completely redundant decls.  */
  ಯದಿ (!warned && !pedwarned
      && warn_redundant_decls
      /* Don't warn about a function declaration followed by a
	 definition.  */
      && !(ವೃಕ್ಷ_CODE (newdecl) == FUNCTION_DECL
	   && DECL_INITIAL (newdecl) && !DECL_INITIAL (olddecl))
      /* Don't warn about redundant redeclarations of builtins.  */
      && !(ವೃಕ್ಷ_CODE (newdecl) == FUNCTION_DECL
	   && !fndecl_built_in_p (newdecl)
	   && fndecl_built_in_p (olddecl)
	   && !C_DECL_DECLARED_BUILTIN (olddecl))
      /* Don't warn about an extern followed by a definition.  */
      && !(DECL_EXTERNAL (olddecl) && !DECL_EXTERNAL (newdecl))
      /* Don't warn about forward parameter decls.  */
      && !(ವೃಕ್ಷ_CODE (newdecl) == PARM_DECL
	   && ವೃಕ್ಷ_ASM_WRITTEN (olddecl) && !ವೃಕ್ಷ_ASM_WRITTEN (newdecl))
      /* Don't warn about a variable definition following a declaration.  */
      && !(VAR_P (newdecl)
	   && DECL_INITIAL (newdecl) && !DECL_INITIAL (olddecl)))
    {
      warned = warning (OPT_Wredundant_decls, "redundant redeclaration of %q+D",
			newdecl);
    }

  /* Report location of previous decl/defn.  */
  ಯದಿ (warned || pedwarned)
    locate_old_decl (olddecl);

#undef DECL_EXTERN_INLINE

  ಪ್ರತ್ಯಾಗಮ retval;
}

/* Subroutine of duplicate_decls.  NEWDECL has been found to be
   consistent with OLDDECL, but carries new information.  Merge the
   new information into OLDDECL.  This function issues no
   diagnostics.  */

ಸ್ಥಿರ ಶೂನ್ಯ
merge_decls (ವೃಕ್ಷ newdecl, ವೃಕ್ಷ olddecl, ವೃಕ್ಷ newtype, ವೃಕ್ಷ oldtype)
{
  ತಾರ್ಕಿಕ new_is_definition = (ವೃಕ್ಷ_CODE (newdecl) == FUNCTION_DECL
			    && DECL_INITIAL (newdecl) != NULL_ವೃಕ್ಷ);
  ತಾರ್ಕಿಕ new_is_prototype = (ವೃಕ್ಷ_CODE (newdecl) == FUNCTION_DECL
			   && prototype_p (ವೃಕ್ಷ_TYPE (newdecl)));
  ತಾರ್ಕಿಕ old_is_prototype = (ವೃಕ್ಷ_CODE (olddecl) == FUNCTION_DECL
			   && prototype_p (ವೃಕ್ಷ_TYPE (olddecl)));

  /* For real parm decl following a forward decl, rechain the old decl
     in its new location and clear TREE_ASM_WRITTEN (it's not a
     forward decl anymore).  */
  ಯದಿ (ವೃಕ್ಷ_CODE (newdecl) == PARM_DECL
      && ವೃಕ್ಷ_ASM_WRITTEN (olddecl) && !ವೃಕ್ಷ_ASM_WRITTEN (newdecl))
    {
      ಸಂರಚನಾ c_binding *b, **here;

      ಪ್ರತಿ (here = &current_scope->bindings; *here; here = &(*here)->prev)
	ಯದಿ ((*here)->decl == olddecl)
	  ಗಚ್ಛ found;
      gcc_unreachable ();

    found:
      b = *here;
      *here = b->prev;
      b->prev = current_scope->bindings;
      current_scope->bindings = b;

      ವೃಕ್ಷ_ASM_WRITTEN (olddecl) = 0;
    }

  DECL_ATTRIBUTES (newdecl)
    = targetm.merge_decl_attributes (olddecl, newdecl);

  /* For typedefs use the old type, as the new type's DECL_NAME points
     at newdecl, which will be ggc_freed.  */
  ಯದಿ (ವೃಕ್ಷ_CODE (newdecl) == TYPE_DECL)
    {
      /* But NEWTYPE might have an attribute, honor that.  */
      ವೃಕ್ಷ tem = newtype;
      newtype = oldtype;

      ಯದಿ (TYPE_USER_ALIGN (tem))
	{
	  ಯದಿ (TYPE_ALIGN (tem) > TYPE_ALIGN (newtype))
	    SET_TYPE_ALIGN (newtype, TYPE_ALIGN (tem));
	  TYPE_USER_ALIGN (newtype) = ಸತ್ಯ;
	}

      /* And remove the new type from the variants list.  */
      ಯದಿ (TYPE_NAME (ವೃಕ್ಷ_TYPE (newdecl)) == newdecl)
	{
	  ವೃಕ್ಷ remove = ವೃಕ್ಷ_TYPE (newdecl);
	  ಯದಿ (TYPE_MAIN_VARIANT (remove) == remove)
	    {
	      gcc_assert (TYPE_NEXT_VARIANT (remove) == NULL_ವೃಕ್ಷ);
	      /* If remove is the main variant, no need to remove that
		 from the list.  One of the DECL_ORIGINAL_TYPE
		 variants, e.g. created for aligned attribute, might still
		 refer to the newdecl TYPE_DECL though, so remove that one
		 in that case.  */
	      ಯದಿ (DECL_ORIGINAL_TYPE (newdecl)
		  && DECL_ORIGINAL_TYPE (newdecl) != remove)
		ಪ್ರತಿ (ವೃಕ್ಷ t = TYPE_MAIN_VARIANT (DECL_ORIGINAL_TYPE (newdecl));
		     t; t = TYPE_MAIN_VARIANT (t))
		  ಯದಿ (TYPE_NAME (TYPE_NEXT_VARIANT (t)) == newdecl)
		    {
		      TYPE_NEXT_VARIANT (t)
			= TYPE_NEXT_VARIANT (TYPE_NEXT_VARIANT (t));
		      ಭಙ್ಗ;
		    }
	    }
	  ಅನ್ಯಥಾ
	    ಪ್ರತಿ (ವೃಕ್ಷ t = TYPE_MAIN_VARIANT (remove); ;
		 t = TYPE_NEXT_VARIANT (t))
	      ಯದಿ (TYPE_NEXT_VARIANT (t) == remove)
		{
		  TYPE_NEXT_VARIANT (t) = TYPE_NEXT_VARIANT (remove);
		  ಭಙ್ಗ;
		}
	}

      /* Make sure we refer to the same type as the olddecl.  */
      DECL_ORIGINAL_TYPE (newdecl) = DECL_ORIGINAL_TYPE (olddecl);
    }

  /* Merge the data types specified in the two decls.  */
  ವೃಕ್ಷ_TYPE (newdecl)
    = ವೃಕ್ಷ_TYPE (olddecl)
    = composite_type (newtype, oldtype);

  /* Lay the type out, unless already done.  */
  ಯದಿ (!comptypes (oldtype, ವೃಕ್ಷ_TYPE (newdecl)))
    {
      ಯದಿ (ವೃಕ್ಷ_TYPE (newdecl) != error_mark_ಗಂಟು)
	layout_type (ವೃಕ್ಷ_TYPE (newdecl));
      ಯದಿ (ವೃಕ್ಷ_CODE (newdecl) != FUNCTION_DECL
	  && ವೃಕ್ಷ_CODE (newdecl) != TYPE_DECL
	  && ವೃಕ್ಷ_CODE (newdecl) != CONST_DECL)
	layout_decl (newdecl, 0);
    }
  ಅನ್ಯಥಾ
    {
      /* Since the type is OLDDECL's, make OLDDECL's size go with.  */
      DECL_SIZE (newdecl) = DECL_SIZE (olddecl);
      DECL_SIZE_UNIT (newdecl) = DECL_SIZE_UNIT (olddecl);
      SET_DECL_MODE (newdecl, DECL_MODE (olddecl));
      ಯದಿ (DECL_ALIGN (olddecl) > DECL_ALIGN (newdecl))
	{
	  SET_DECL_ALIGN (newdecl, DECL_ALIGN (olddecl));
	  DECL_USER_ALIGN (newdecl) |= DECL_USER_ALIGN (olddecl);
	}
      ಅನ್ಯಥಾ ಯದಿ (DECL_ALIGN (olddecl) == DECL_ALIGN (newdecl)
	       && DECL_USER_ALIGN (olddecl) != DECL_USER_ALIGN (newdecl))
	DECL_USER_ALIGN (newdecl) = 1;
      ಯದಿ (DECL_WARN_IF_NOT_ALIGN (olddecl)
	  > DECL_WARN_IF_NOT_ALIGN (newdecl))
	SET_DECL_WARN_IF_NOT_ALIGN (newdecl,
				    DECL_WARN_IF_NOT_ALIGN (olddecl));
    }

  /* Keep the old rtl since we can safely use it.  */
  ಯದಿ (HAS_RTL_P (olddecl))
    COPY_DECL_RTL (olddecl, newdecl);

  /* Merge the type qualifiers.  */
  ಯದಿ (ವೃಕ್ಷ_READONLY (newdecl))
    ವೃಕ್ಷ_READONLY (olddecl) = 1;

  ಯದಿ (ವೃಕ್ಷ_THIS_VOLATILE (newdecl))
    ವೃಕ್ಷ_THIS_VOLATILE (olddecl) = 1;

  /* Merge deprecatedness.  */
  ಯದಿ (ವೃಕ್ಷ_DEPRECATED (newdecl))
    ವೃಕ್ಷ_DEPRECATED (olddecl) = 1;

  /* Merge unavailability.  */
  ಯದಿ (ವೃಕ್ಷ_UNAVAILABLE (newdecl))
    ವೃಕ್ಷ_UNAVAILABLE (olddecl) = 1;

  /* If a decl is in a system header and the other isn't, keep the one on the
     system header. Otherwise, keep source location of definition rather than
     declaration and of prototype rather than non-prototype unless that
     prototype is built-in.  */
  ಯದಿ (HAS_DECL_ASSEMBLER_NAME_P (olddecl)
      && DECL_IN_SYSTEM_HEADER (olddecl)
      && !DECL_IN_SYSTEM_HEADER (newdecl) )
    DECL_SOURCE_LOCATION (newdecl) = DECL_SOURCE_LOCATION (olddecl);
  ಅನ್ಯಥಾ ಯದಿ (HAS_DECL_ASSEMBLER_NAME_P (olddecl)
	   && DECL_IN_SYSTEM_HEADER (newdecl)
	   && !DECL_IN_SYSTEM_HEADER (olddecl))
    DECL_SOURCE_LOCATION (olddecl) = DECL_SOURCE_LOCATION (newdecl);
  ಅನ್ಯಥಾ ಯದಿ ((DECL_INITIAL (newdecl) == NULL_ವೃಕ್ಷ
	    && DECL_INITIAL (olddecl) != NULL_ವೃಕ್ಷ)
	   || (old_is_prototype && !new_is_prototype
	       && !C_DECL_BUILTIN_PROTOTYPE (olddecl)))
    DECL_SOURCE_LOCATION (newdecl) = DECL_SOURCE_LOCATION (olddecl);

  /* Merge the initialization information.  */
   ಯದಿ (DECL_INITIAL (newdecl) == NULL_ವೃಕ್ಷ)
    DECL_INITIAL (newdecl) = DECL_INITIAL (olddecl);

  /* Merge 'constexpr' information.  */
  ಯದಿ (VAR_P (olddecl) && VAR_P (newdecl))
    {
      ಯದಿ (C_DECL_DECLARED_CONSTEXPR (olddecl))
	C_DECL_DECLARED_CONSTEXPR (newdecl) = 1;
      ಅನ್ಯಥಾ ಯದಿ (C_DECL_DECLARED_CONSTEXPR (newdecl))
	C_DECL_DECLARED_CONSTEXPR (olddecl) = 1;
    }

  /* Merge the threadprivate attribute.  */
  ಯದಿ (VAR_P (olddecl) && C_DECL_THREADPRIVATE_P (olddecl))
    C_DECL_THREADPRIVATE_P (newdecl) = 1;

  ಯದಿ (HAS_DECL_ASSEMBLER_NAME_P (olddecl))
    {
      /* Copy the assembler name.
	 Currently, it can only be defined in the prototype.  */
      COPY_DECL_ASSEMBLER_NAME (olddecl, newdecl);

      /* Use visibility of whichever declaration had it specified */
      ಯದಿ (DECL_VISIBILITY_SPECIFIED (olddecl))
	{
	  DECL_VISIBILITY (newdecl) = DECL_VISIBILITY (olddecl);
	  DECL_VISIBILITY_SPECIFIED (newdecl) = 1;
	}

      ಯದಿ (ವೃಕ್ಷ_CODE (newdecl) == FUNCTION_DECL)
	{
	  DECL_STATIC_CONSTRUCTOR(newdecl) |= DECL_STATIC_CONSTRUCTOR(olddecl);
	  DECL_STATIC_DESTRUCTOR (newdecl) |= DECL_STATIC_DESTRUCTOR (olddecl);
	  DECL_NO_LIMIT_ರಾಶಿ (newdecl) |= DECL_NO_LIMIT_ರಾಶಿ (olddecl);
	  DECL_NO_INSTRUMENT_FUNCTION_ENTRY_EXIT (newdecl)
	    |= DECL_NO_INSTRUMENT_FUNCTION_ENTRY_EXIT (olddecl);
	  ವೃಕ್ಷ_THIS_VOLATILE (newdecl) |= ವೃಕ್ಷ_THIS_VOLATILE (olddecl);
	  DECL_IS_MALLOC (newdecl) |= DECL_IS_MALLOC (olddecl);
	  ಯದಿ (DECL_IS_OPERATOR_NEW_P (olddecl))
	    DECL_SET_IS_OPERATOR_NEW (newdecl, ಸತ್ಯ);
	  ಯದಿ (DECL_IS_OPERATOR_DELETE_P (olddecl))
	    DECL_SET_IS_OPERATOR_DELETE (newdecl, ಸತ್ಯ);
	  ವೃಕ್ಷ_READONLY (newdecl) |= ವೃಕ್ಷ_READONLY (olddecl);
	  DECL_PURE_P (newdecl) |= DECL_PURE_P (olddecl);
	  DECL_IS_NOVOPS (newdecl) |= DECL_IS_NOVOPS (olddecl);
	}

      /* Merge the storage class information.  */
      merge_weak (newdecl, olddecl);

      /* For functions, static overrides non-static.  */
      ಯದಿ (ವೃಕ್ಷ_CODE (newdecl) == FUNCTION_DECL)
	{
	  ವೃಕ್ಷ_PUBLIC (newdecl) &= ವೃಕ್ಷ_PUBLIC (olddecl);
	  /* This is since we don't automatically
	     copy the attributes of NEWDECL into OLDDECL.  */
	  ವೃಕ್ಷ_PUBLIC (olddecl) = ವೃಕ್ಷ_PUBLIC (newdecl);
	  /* If this clears `static', clear it in the identifier too.  */
	  ಯದಿ (!ವೃಕ್ಷ_PUBLIC (olddecl))
	    ವೃಕ್ಷ_PUBLIC (DECL_NAME (olddecl)) = 0;
	}
    }

  /* In c99, 'extern' declaration before (or after) 'inline' means this
     function is not DECL_EXTERNAL, unless 'gnu_inline' attribute
     is present.  */
  ಯದಿ (ವೃಕ್ಷ_CODE (newdecl) == FUNCTION_DECL
      && !flag_gnu89_inline
      && (DECL_DECLARED_INLINE_P (newdecl)
	  || DECL_DECLARED_INLINE_P (olddecl))
      && (!DECL_DECLARED_INLINE_P (newdecl)
	  || !DECL_DECLARED_INLINE_P (olddecl)
	  || !DECL_EXTERNAL (olddecl))
      && DECL_EXTERNAL (newdecl)
      && !lookup_attribute ("gnu_inline", DECL_ATTRIBUTES (newdecl))
      && !current_function_decl)
    DECL_EXTERNAL (newdecl) = 0;

  /* An inline definition following a static declaration is not
     DECL_EXTERNAL.  */
  ಯದಿ (new_is_definition
      && (DECL_DECLARED_INLINE_P (newdecl)
	  || DECL_DECLARED_INLINE_P (olddecl))
      && !ವೃಕ್ಷ_PUBLIC (olddecl))
    DECL_EXTERNAL (newdecl) = 0;

  ಯದಿ (DECL_EXTERNAL (newdecl))
    {
      ವೃಕ್ಷ_STATIC (newdecl) = ವೃಕ್ಷ_STATIC (olddecl);
      DECL_EXTERNAL (newdecl) = DECL_EXTERNAL (olddecl);

      /* An extern decl does not override previous storage class.  */
      ವೃಕ್ಷ_PUBLIC (newdecl) = ವೃಕ್ಷ_PUBLIC (olddecl);
      ಯದಿ (!DECL_EXTERNAL (newdecl))
	{
	  DECL_CONTEXT (newdecl) = DECL_CONTEXT (olddecl);
	  DECL_COMMON (newdecl) = DECL_COMMON (olddecl);
	}
    }
  ಅನ್ಯಥಾ
    {
      ವೃಕ್ಷ_STATIC (olddecl) = ವೃಕ್ಷ_STATIC (newdecl);
      ವೃಕ್ಷ_PUBLIC (olddecl) = ವೃಕ್ಷ_PUBLIC (newdecl);
    }

  ಯದಿ (ವೃಕ್ಷ_CODE (newdecl) == FUNCTION_DECL)
    {
      ಯದಿ (DECL_FUNCTION_VERSIONED (olddecl)
	  || DECL_FUNCTION_VERSIONED (newdecl))
	{
	  maybe_mark_function_versioned (olddecl);
	  maybe_mark_function_versioned (newdecl);
	}
      /* If we're redefining a function previously defined as extern
	 inline, make sure we emit debug info for the inline before we
	 throw it away, in case it was inlined into a function that
	 hasn't been written out yet.  */
      ಯದಿ (new_is_definition && DECL_INITIAL (olddecl))
	/* The new defn must not be inline.  */
	DECL_UNINLINABLE (newdecl) = 1;
      ಅನ್ಯಥಾ
	{
	  /* If either decl says `inline', this fn is inline, unless
	     its definition was passed already.  */
	  ಯದಿ (DECL_DECLARED_INLINE_P (newdecl)
	      || DECL_DECLARED_INLINE_P (olddecl))
	    DECL_DECLARED_INLINE_P (newdecl) = 1;

	  DECL_UNINLINABLE (newdecl) = DECL_UNINLINABLE (olddecl)
	    = (DECL_UNINLINABLE (newdecl) || DECL_UNINLINABLE (olddecl));

	  DECL_DISREGARD_INLINE_LIMITS (newdecl)
	    = DECL_DISREGARD_INLINE_LIMITS (olddecl)
	    = (DECL_DISREGARD_INLINE_LIMITS (newdecl)
	       || DECL_DISREGARD_INLINE_LIMITS (olddecl));
	}

      ಯದಿ (fndecl_built_in_p (olddecl))
	{
	  /* If redeclaring a builtin function, it stays built in.
	     But it gets tagged as having been declared.  */
	  copy_decl_built_in_function (newdecl, olddecl);
	  C_DECL_DECLARED_BUILTIN (newdecl) = 1;
	  ಯದಿ (new_is_prototype)
	    {
	      C_DECL_BUILTIN_PROTOTYPE (newdecl) = 0;
	      ಯದಿ (DECL_BUILT_IN_CLASS (newdecl) == BUILT_IN_NORMAL)
		{
		  ಗಣನಾ built_in_function fncode = DECL_FUNCTION_CODE (newdecl);
		  ವಿಕಲ್ಪ (fncode)
		    {
		      /* If a compatible prototype of these builtin functions
			 is seen, assume the runtime implements it with the
			 expected semantics.  */
		    ಪಕ್ಷ BUILT_IN_STPCPY:
		      ಯದಿ (builtin_decl_explicit_p (fncode))
			set_builtin_decl_implicit_p (fncode, ಸತ್ಯ);
		      ಭಙ್ಗ;
		    ಸ್ವಭಾವ:
		      ಯದಿ (builtin_decl_explicit_p (fncode))
			set_builtin_decl_declared_p (fncode, ಸತ್ಯ);
		      ಭಙ್ಗ;
		    }

		  copy_attributes_to_builtin (newdecl);
		}
	    }
	  ಅನ್ಯಥಾ
	    C_DECL_BUILTIN_PROTOTYPE (newdecl)
	      = C_DECL_BUILTIN_PROTOTYPE (olddecl);
	}

      /* Preserve function specific target and optimization options */
      ಯದಿ (DECL_FUNCTION_SPECIFIC_TARGET (olddecl)
	  && !DECL_FUNCTION_SPECIFIC_TARGET (newdecl))
	DECL_FUNCTION_SPECIFIC_TARGET (newdecl)
	  = DECL_FUNCTION_SPECIFIC_TARGET (olddecl);

      ಯದಿ (DECL_FUNCTION_SPECIFIC_OPTIMIZATION (olddecl)
	  && !DECL_FUNCTION_SPECIFIC_OPTIMIZATION (newdecl))
	DECL_FUNCTION_SPECIFIC_OPTIMIZATION (newdecl)
	  = DECL_FUNCTION_SPECIFIC_OPTIMIZATION (olddecl);

      /* Also preserve various other info from the definition.  */
      ಯದಿ (!new_is_definition)
	{
	  ವೃಕ್ಷ t;
	  DECL_RESULT (newdecl) = DECL_RESULT (olddecl);
	  DECL_INITIAL (newdecl) = DECL_INITIAL (olddecl);
	  DECL_STRUCT_FUNCTION (newdecl) = DECL_STRUCT_FUNCTION (olddecl);
	  DECL_SAVED_ವೃಕ್ಷ (newdecl) = DECL_SAVED_ವೃಕ್ಷ (olddecl);
	  DECL_ARGUMENTS (newdecl) = copy_list (DECL_ARGUMENTS (olddecl));
	  ಪ್ರತಿ (t = DECL_ARGUMENTS (newdecl); t ; t = DECL_CHAIN (t))
	    DECL_CONTEXT (t) = newdecl;

	  /* See if we've got a function to instantiate from.  */
	  ಯದಿ (DECL_SAVED_ವೃಕ್ಷ (olddecl))
	    DECL_ABSTRACT_ORIGIN (newdecl)
	      = DECL_ABSTRACT_ORIGIN (olddecl);
	}
    }

  /* Merge the USED information.  */
  ಯದಿ (ವೃಕ್ಷ_USED (olddecl))
    ವೃಕ್ಷ_USED (newdecl) = 1;
  ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_USED (newdecl))
    ವೃಕ್ಷ_USED (olddecl) = 1;
  ಯದಿ (VAR_P (olddecl) || ವೃಕ್ಷ_CODE (olddecl) == PARM_DECL)
    DECL_READ_P (newdecl) |= DECL_READ_P (olddecl);
  ಯದಿ (DECL_PRESERVE_P (olddecl))
    DECL_PRESERVE_P (newdecl) = 1;
  ಅನ್ಯಥಾ ಯದಿ (DECL_PRESERVE_P (newdecl))
    DECL_PRESERVE_P (olddecl) = 1;

  /* Merge DECL_COMMON */
  ಯದಿ (VAR_P (olddecl) && VAR_P (newdecl)
      && !lookup_attribute ("common", DECL_ATTRIBUTES (newdecl))
      && !lookup_attribute ("nocommon", DECL_ATTRIBUTES (newdecl)))
    DECL_COMMON (newdecl) = DECL_COMMON (newdecl) && DECL_COMMON (olddecl);

  /* Copy most of the decl-specific fields of NEWDECL into OLDDECL.
     But preserve OLDDECL's DECL_UID, DECL_CONTEXT and
     DECL_ARGUMENTS (if appropriate).  */
  {
    unsigned olddecl_uid = DECL_UID (olddecl);
    ವೃಕ್ಷ olddecl_context = DECL_CONTEXT (olddecl);
    ವೃಕ್ಷ olddecl_arguments = ರಿಕ್ತ;
    ಯದಿ (ವೃಕ್ಷ_CODE (olddecl) == FUNCTION_DECL)
      olddecl_arguments = DECL_ARGUMENTS (olddecl);

    memcpy ((ವರ್ಣ *) olddecl + ಪರಿಮಾಣ (ಸಂರಚನಾ ವೃಕ್ಷ_common),
	    (ವರ್ಣ *) newdecl + ಪರಿಮಾಣ (ಸಂರಚನಾ ವೃಕ್ಷ_common),
	    ಪರಿಮಾಣ (ಸಂರಚನಾ ವೃಕ್ಷ_decl_common) - ಪರಿಮಾಣ (ಸಂರಚನಾ ವೃಕ್ಷ_common));
    DECL_USER_ALIGN (olddecl) = DECL_USER_ALIGN (newdecl);
    ವಿಕಲ್ಪ (ವೃಕ್ಷ_CODE (olddecl))
      {
      ಪಕ್ಷ FUNCTION_DECL:
      ಪಕ್ಷ VAR_DECL:
	{
	  ಸಂರಚನಾ symtab_ಗಂಟು *snode = olddecl->decl_with_vis.symtab_ಗಂಟು;

	  memcpy ((ವರ್ಣ *) olddecl + ಪರಿಮಾಣ (ಸಂರಚನಾ ವೃಕ್ಷ_decl_common),
		  (ವರ್ಣ *) newdecl + ಪರಿಮಾಣ (ಸಂರಚನಾ ವೃಕ್ಷ_decl_common),
		  ವೃಕ್ಷ_code_size (ವೃಕ್ಷ_CODE (olddecl)) - ಪರಿಮಾಣ (ಸಂರಚನಾ ವೃಕ್ಷ_decl_common));
	  olddecl->decl_with_vis.symtab_ಗಂಟು = snode;

	  ಯದಿ ((DECL_EXTERNAL (olddecl)
	       || ವೃಕ್ಷ_PUBLIC (olddecl)
	       || ವೃಕ್ಷ_STATIC (olddecl))
	      && DECL_SECTION_NAME (newdecl) != ರಿಕ್ತ)
	    set_decl_section_name (olddecl, newdecl);

	  /* This isn't quite correct for something like
		int __thread x attribute ((tls_model ("local-exec")));
		extern int __thread x;
	     as we'll lose the "local-exec" model.  */
	  ಯದಿ (VAR_P (olddecl) && DECL_THREAD_LOCAL_P (newdecl))
	    set_decl_tls_model (olddecl, DECL_TLS_MODEL (newdecl));
	  ಭಙ್ಗ;
	}

      ಪಕ್ಷ FIELD_DECL:
      ಪಕ್ಷ PARM_DECL:
      ಪಕ್ಷ LABEL_DECL:
      ಪಕ್ಷ RESULT_DECL:
      ಪಕ್ಷ CONST_DECL:
      ಪಕ್ಷ TYPE_DECL:
	memcpy ((ವರ್ಣ *) olddecl + ಪರಿಮಾಣ (ಸಂರಚನಾ ವೃಕ್ಷ_decl_common),
		(ವರ್ಣ *) newdecl + ಪರಿಮಾಣ (ಸಂರಚನಾ ವೃಕ್ಷ_decl_common),
		ವೃಕ್ಷ_code_size (ವೃಕ್ಷ_CODE (olddecl)) - ಪರಿಮಾಣ (ಸಂರಚನಾ ವೃಕ್ಷ_decl_common));
	ಭಙ್ಗ;

      ಸ್ವಭಾವ:

	memcpy ((ವರ್ಣ *) olddecl + ಪರಿಮಾಣ (ಸಂರಚನಾ ವೃಕ್ಷ_decl_common),
		(ವರ್ಣ *) newdecl + ಪರಿಮಾಣ (ಸಂರಚನಾ ವೃಕ್ಷ_decl_common),
		ಪರಿಮಾಣ (ಸಂರಚನಾ ವೃಕ್ಷ_decl_non_common) - ಪರಿಮಾಣ (ಸಂರಚನಾ ವೃಕ್ಷ_decl_common));
      }
    DECL_UID (olddecl) = olddecl_uid;
    DECL_CONTEXT (olddecl) = olddecl_context;
    ಯದಿ (ವೃಕ್ಷ_CODE (olddecl) == FUNCTION_DECL)
      DECL_ARGUMENTS (olddecl) = olddecl_arguments;
  }

  /* If OLDDECL had its DECL_RTL instantiated, re-invoke make_decl_rtl
     so that encode_section_info has a chance to look at the new decl
     flags and attributes.  */
  ಯದಿ (DECL_RTL_SET_P (olddecl)
      && (ವೃಕ್ಷ_CODE (olddecl) == FUNCTION_DECL
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
  ವೃಕ್ಷ newtype = ರಿಕ್ತ, oldtype = ರಿಕ್ತ;

  ಯದಿ (!diagnose_mismatched_decls (newdecl, olddecl, &newtype, &oldtype))
    {
      /* Avoid `unused variable' and other warnings for OLDDECL.  */
      suppress_warning (olddecl, OPT_Wunused);
      /* If the types are completely different, poison them both with
 	 error_mark_node.  */
      ಯದಿ (ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (newdecl)) != ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (olddecl))
	  && olddecl != error_mark_ಗಂಟು
	  && seen_error ())
	{
	  ಯದಿ (ವೃಕ್ಷ_CODE (olddecl) != FUNCTION_DECL)
	    ವೃಕ್ಷ_TYPE (olddecl) = error_mark_ಗಂಟು;
	  ಯದಿ (ವೃಕ್ಷ_CODE (newdecl) != FUNCTION_DECL)
	    ವೃಕ್ಷ_TYPE (newdecl) = error_mark_ಗಂಟು;
	}
      ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
    }

  merge_decls (newdecl, olddecl, newtype, oldtype);

  /* The NEWDECL will no longer be needed.

     Before releasing the node, be sure to remove function from symbol
     table that might have been inserted there to record comdat group.
     Be sure to however do not free DECL_STRUCT_FUNCTION because this
     structure is shared in between NEWDECL and OLDECL.  */
  ಯದಿ (ವೃಕ್ಷ_CODE (newdecl) == FUNCTION_DECL)
    DECL_STRUCT_FUNCTION (newdecl) = ರಿಕ್ತ;
  ಯದಿ (VAR_OR_FUNCTION_DECL_P (newdecl))
    {
      ಸಂರಚನಾ symtab_ಗಂಟು *snode = symtab_ಗಂಟು::get (newdecl);
      ಯದಿ (snode)
	snode->remove ();
    }
  ggc_free (newdecl);
  ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
}


/* Check whether decl-node NEW_DECL shadows an existing declaration.  */
ಸ್ಥಿರ ಶೂನ್ಯ
warn_if_shadowing (ವೃಕ್ಷ new_decl)
{
  ಸಂರಚನಾ c_binding *b;

  /* Shadow warnings wanted?  */
  ಯದಿ (!(warn_shadow
        || warn_shadow_local
        || warn_shadow_compatible_local)
      /* No shadow warnings for internally generated vars.  */
      || DECL_IS_UNDECLARED_BUILTIN (new_decl))
    ಪ್ರತ್ಯಾಗಮ;

  /* Is anything being shadowed?  Invisible decls do not count.  */
  ಪ್ರತಿ (b = I_ಚಿಹ್ನೆ_BINDING (DECL_NAME (new_decl)); b; b = b->shadowed)
    ಯದಿ (b->decl && b->decl != new_decl && !b->invisible
	&& (b->decl == error_mark_ಗಂಟು
	    || diagnostic_report_warnings_p (global_dc,
					     DECL_SOURCE_LOCATION (b->decl))))
      {
	ವೃಕ್ಷ old_decl = b->decl;

	ಯದಿ (old_decl == error_mark_ಗಂಟು)
	  {
	    warning (OPT_Wshadow, "declaration of %q+D shadows previous "
		     "non-variable", new_decl);
	    ಭಙ್ಗ;
	  }

	ತಾರ್ಕಿಕ warned = ಅಸತ್ಯ;
	auto_diagnostic_group d;
	ಯದಿ (ವೃಕ್ಷ_CODE (old_decl) == PARM_DECL)
	  {
	    ಗಣನಾ opt_code warning_code;

	    /* If '-Wshadow=compatible-local' is specified without other
	       -Wshadow= flags, we will warn only when the types of the
	       shadowing variable (i.e. new_decl) and the shadowed variable
	       (old_decl) are compatible.  */
	    ಯದಿ (warn_shadow)
	      warning_code = OPT_Wshadow;
	    ಅನ್ಯಥಾ ಯದಿ (comptypes (ವೃಕ್ಷ_TYPE (old_decl), ವೃಕ್ಷ_TYPE (new_decl)))
	      warning_code = OPT_Wshadow_compatible_local;
	    ಅನ್ಯಥಾ
	      warning_code = OPT_Wshadow_local;
	    warned = warning_at (DECL_SOURCE_LOCATION (new_decl), warning_code,
				 "declaration of %qD shadows a parameter",
				 new_decl);
	  }
	ಅನ್ಯಥಾ ಯದಿ (DECL_FILE_SCOPE_P (old_decl))
	  {
	    /* Do not warn if a variable shadows a function, unless
	       the variable is a function or a pointer-to-function.  */
	    ಯದಿ (ವೃಕ್ಷ_CODE (old_decl) == FUNCTION_DECL
		&& ವೃಕ್ಷ_CODE (new_decl) != FUNCTION_DECL
		&& !FUNCTION_POINTER_TYPE_P (ವೃಕ್ಷ_TYPE (new_decl)))
		ಅನುವರ್ತ;

	    warned = warning_at (DECL_SOURCE_LOCATION (new_decl), OPT_Wshadow,
				 "declaration of %qD shadows a global "
				 "declaration",
				 new_decl);
	  }
	ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_CODE (old_decl) == FUNCTION_DECL
		 && fndecl_built_in_p (old_decl))
	  {
	    warning (OPT_Wshadow, "declaration of %q+D shadows "
		     "a built-in function", new_decl);
	    ಭಙ್ಗ;
	  }
	ಅನ್ಯಥಾ
	  {
	    ಗಣನಾ opt_code warning_code;

	    /* If '-Wshadow=compatible-local' is specified without other
	       -Wshadow= flags, we will warn only when the types of the
	       shadowing variable (i.e. new_decl) and the shadowed variable
	       (old_decl) are compatible.  */
	    ಯದಿ (warn_shadow)
	      warning_code = OPT_Wshadow;
	    ಅನ್ಯಥಾ ಯದಿ (comptypes (ವೃಕ್ಷ_TYPE (old_decl), ವೃಕ್ಷ_TYPE (new_decl)))
	      warning_code = OPT_Wshadow_compatible_local;
	    ಅನ್ಯಥಾ
	      warning_code = OPT_Wshadow_local;
	    warned = warning_at (DECL_SOURCE_LOCATION (new_decl), warning_code,
				 "declaration of %qD shadows a previous local",
				 new_decl);
	  }

	ಯದಿ (warned)
	  inform (DECL_SOURCE_LOCATION (old_decl),
		  "shadowed declaration is here");

	ಭಙ್ಗ;
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
  ಸಂರಚನಾ c_scope *scope = current_scope;
  ಸಂರಚನಾ c_binding *b;
  ತಾರ್ಕಿಕ nested = ಅಸತ್ಯ;
  location_t locus = DECL_SOURCE_LOCATION (x);

  /* Must set DECL_CONTEXT for everything not at file scope or
     DECL_FILE_SCOPE_P won't work.  Local externs don't count
     unless they have initializers (which generate code).  We
     also exclude CONST_DECLs because enumerators will get the
     type of the enum as context.  */
  ಯದಿ (current_function_decl
      && ವೃಕ್ಷ_CODE (x) != CONST_DECL
      && (!VAR_OR_FUNCTION_DECL_P (x)
	  || DECL_INITIAL (x) || !ವೃಕ್ಷ_PUBLIC (x)))
    DECL_CONTEXT (x) = current_function_decl;

  /* Anonymous decls are just inserted in the scope.  */
  ಯದಿ (!name)
    {
      bind (name, x, scope, /*invisible=*/ಅಸತ್ಯ, /*nested=*/ಅಸತ್ಯ,
	    locus);
      ಪ್ರತ್ಯಾಗಮ x;
    }

  /* First, see if there is another declaration with the same name in
     the current scope.  If there is, duplicate_decls may do all the
     work for us.  If duplicate_decls returns false, that indicates
     two incompatible decls in the same scope; we are to silently
     replace the old one (duplicate_decls has issued all appropriate
     diagnostics).  In particular, we should not consider possible
     duplicates in the external scope, or shadowing.  */
  b = I_ಚಿಹ್ನೆ_BINDING (name);
  ಯದಿ (b && B_IN_SCOPE (b, scope))
    {
      ಸಂರಚನಾ c_binding *b_ext, *b_use;
      ವೃಕ್ಷ type = ವೃಕ್ಷ_TYPE (x);
      ವೃಕ್ಷ visdecl = b->decl;
      ವೃಕ್ಷ vistype = ವೃಕ್ಷ_TYPE (visdecl);
      ಯದಿ (ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (x)) == ARRAY_TYPE
	  && COMPLETE_TYPE_P (ವೃಕ್ಷ_TYPE (x)))
	b->inner_comp = ಅಸತ್ಯ;
      b_use = b;
      b_ext = b;
      /* If this is an external linkage declaration, we should check
	 for compatibility with the type in the external scope before
	 setting the type at this scope based on the visible
	 information only.  */
      ಯದಿ (ವೃಕ್ಷ_PUBLIC (x) && ವೃಕ್ಷ_PUBLIC (visdecl))
	{
	  ಯಾವತ್ (b_ext && !B_IN_EXTERNAL_SCOPE (b_ext))
	    b_ext = b_ext->shadowed;
	  ಯದಿ (b_ext)
	    {
	      b_use = b_ext;
	      ಯದಿ (b_use->u.type)
		ವೃಕ್ಷ_TYPE (b_use->decl) = b_use->u.type;
	    }
	}

      /* Check if x is part of a FMV set with b_use.
	 FMV is only supported in c for targets with target_version
	 attributes.  */
      ಯದಿ (!TARGET_HAS_FMV_TARGET_ATTRIBUTE
	  && b_use && ವೃಕ್ಷ_CODE (b_use->decl) == FUNCTION_DECL
	  && ವೃಕ್ಷ_CODE (x) == FUNCTION_DECL && DECL_FILE_SCOPE_P (b_use->decl)
	  && DECL_FILE_SCOPE_P (x)
	  && disjoint_version_decls (x, b_use->decl)
	  && comptypes (vistype, type))
	{
	  maybe_mark_function_versioned (b_use->decl);
	  maybe_mark_function_versioned (b->decl);
	  maybe_mark_function_versioned (x);

	  cgraph_ಗಂಟು *b_ಗಂಟು = cgraph_ಗಂಟು::get_create (b_use->decl);
	  cgraph_function_version_info *b_v = b_ಗಂಟು->function_version ();
	  ಯದಿ (!b_v)
	    b_v = b_ಗಂಟು->ಸೇರಿಸು_new_function_version ();

	  /* Check if this new node conflicts with any previous functions
	     in the set.  */
	  cgraph_function_version_info *version = b_v;
	  ಪ್ರತಿ (; version; version = version->next)
	    ಯದಿ (!disjoint_version_decls (version->this_ಗಂಟು->decl, x))
	      {
		/* The decls define overlapping version, so attempt to merge
		   or diagnose the conflict.  */
		ಯದಿ (duplicate_decls (x, version->this_ಗಂಟು->decl))
		  ಪ್ರತ್ಯಾಗಮ version->this_ಗಂಟು->decl;
		ಅನ್ಯಥಾ
		  ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
	      }

	  /* This is a new version to be added to FMV structure.  */
	  cgraph_ಗಂಟು::add_function_version (b_v, x);

	  /* Get the first node from the structure.  */
	  cgraph_function_version_info *default_v = b_v;
	  ಯಾವತ್ (default_v->prev)
	    default_v = default_v->prev;
	  /* Always use the default node for the bindings.  */
	  b_use->decl = default_v->this_ಗಂಟು->decl;
	  b->decl = default_v->this_ಗಂಟು->decl;

	  /* Node is not a duplicate, so no need to do the rest of the
	     checks.  */
	  ಪ್ರತ್ಯಾಗಮ x;
	}

      ಯದಿ (duplicate_decls (x, b_use->decl))
	{
	  ಯದಿ (b_use != b)
	    {
	      /* Save the updated type in the external scope and
		 restore the proper type for this scope.  */
	      ವೃಕ್ಷ thistype;
	      ಯದಿ (comptypes (vistype, type))
		thistype = composite_type (vistype, type);
	      ಅನ್ಯಥಾ
		thistype = ವೃಕ್ಷ_TYPE (b_use->decl);
	      b_use->u.type = ವೃಕ್ಷ_TYPE (b_use->decl);
	      ಯದಿ (ವೃಕ್ಷ_CODE (b_use->decl) == FUNCTION_DECL
		  && fndecl_built_in_p (b_use->decl))
		thistype
		  = c_build_type_attribute_variant (thistype,
						    TYPE_ATTRIBUTES
						    (b_use->u.type));
	      ವೃಕ್ಷ_TYPE (b_use->decl) = thistype;
	    }
	  ಪ್ರತ್ಯಾಗಮ b_use->decl;
	}
      ಅನ್ಯಥಾ
	ಗಚ್ಛ skip_external_and_shadow_checks;
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
  ಯದಿ ((DECL_EXTERNAL (x) || scope == file_scope)
      && (VAR_OR_FUNCTION_DECL_P (x) || c_dialect_objc ()))
    {
      ವೃಕ್ಷ type = ವೃಕ್ಷ_TYPE (x);
      ವೃಕ್ಷ vistype = NULL_ವೃಕ್ಷ;
      ವೃಕ್ಷ visdecl = NULL_ವೃಕ್ಷ;
      ತಾರ್ಕಿಕ type_saved = ಅಸತ್ಯ;
      ಯದಿ (b && !B_IN_EXTERNAL_SCOPE (b)
	  && VAR_OR_FUNCTION_DECL_P (b->decl)
	  && DECL_FILE_SCOPE_P (b->decl))
	{
	  visdecl = b->decl;
	  vistype = ವೃಕ್ಷ_TYPE (visdecl);
	}
      ಯದಿ (scope != file_scope
	  && !DECL_IN_SYSTEM_HEADER (x))
	warning_at (locus, OPT_Wnested_externs,
		    "nested extern declaration of %qD", x);

      ಯಾವತ್ (b && !B_IN_EXTERNAL_SCOPE (b))
	{
	  /* If this decl might be modified, save its type.  This is
	     done here rather than when the decl is first bound
	     because the type may change after first binding, through
	     being completed or through attributes being added.  If we
	     encounter multiple such decls, only the first should have
	     its type saved; the others will already have had their
	     proper types saved and the types will not have changed as
	     their scopes will not have been re-entered.  */
	  ಯದಿ (DECL_P (b->decl) && DECL_FILE_SCOPE_P (b->decl) && !type_saved)
	    {
	      b->u.type = ವೃಕ್ಷ_TYPE (b->decl);
	      type_saved = ಸತ್ಯ;
	    }
	  ಯದಿ (B_IN_FILE_SCOPE (b)
	      && VAR_P (b->decl)
	      && ವೃಕ್ಷ_STATIC (b->decl)
	      && ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (b->decl)) == ARRAY_TYPE
	      && !TYPE_DOMAIN (ವೃಕ್ಷ_TYPE (b->decl))
	      && ವೃಕ್ಷ_CODE (type) == ARRAY_TYPE
	      && TYPE_DOMAIN (type)
	      && TYPE_MAX_ಮೌಲ್ಯ (TYPE_DOMAIN (type))
	      && !integer_zerop (TYPE_MAX_ಮೌಲ್ಯ (TYPE_DOMAIN (type))))
	    {
	      /* Array type completed in inner scope, which should be
		 diagnosed if the completion does not have size 1 and
		 it does not get completed in the file scope.  */
	      b->inner_comp = ಸತ್ಯ;
	    }
	  b = b->shadowed;
	}

      /* If a matching external declaration has been found, set its
	 type to the composite of all the types of that declaration.
	 After the consistency checks, it will be reset to the
	 composite of the visible types only.  */
      ಯದಿ (b && b->u.type)
	ವೃಕ್ಷ_TYPE (b->decl) = b->u.type;

      /* the static does not go in the externals scope.  */
      ಯದಿ (b && duplicate_decls (x, b->decl))
	{
	  ವೃಕ್ಷ thistype;
	  ಯದಿ (vistype)
	    {
	      ಯದಿ (comptypes (vistype, type))
		thistype = composite_type (vistype, type);
	      ಅನ್ಯಥಾ
		thistype = ವೃಕ್ಷ_TYPE (b->decl);
	    }
	  ಅನ್ಯಥಾ
	    thistype = type;
	  b->u.type = ವೃಕ್ಷ_TYPE (b->decl);
	  /* Propagate the type attributes to the decl.  */
	  thistype
	    = c_build_type_attribute_variant (thistype,
					      TYPE_ATTRIBUTES (b->u.type));
	  ವೃಕ್ಷ_TYPE (b->decl) = thistype;
	  bind (name, b->decl, scope, /*invisible=*/ಅಸತ್ಯ, /*nested=*/ಸತ್ಯ,
		locus);
	  ಪ್ರತ್ಯಾಗಮ b->decl;
	}
      ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_PUBLIC (x))
	{
	  ಯದಿ (visdecl && !b && duplicate_decls (x, visdecl))
	    {
	      /* An external declaration at block scope referring to a
		 visible entity with internal linkage.  The composite
		 type will already be correct for this scope, so we
		 just need to fall through to make the declaration in
		 this scope.  */
	      nested = ಸತ್ಯ;
	      x = visdecl;
	    }
	  ಅನ್ಯಥಾ
	    {
	      bind (name, x, external_scope, /*invisible=*/ಸತ್ಯ,
		    /*nested=*/ಅಸತ್ಯ, locus);
	      nested = ಸತ್ಯ;
	    }
	}
    }

  ಯದಿ (ವೃಕ್ಷ_CODE (x) != PARM_DECL)
    warn_if_shadowing (x);

 skip_external_and_shadow_checks:
  ಯದಿ (ವೃಕ್ಷ_CODE (x) == TYPE_DECL)
    {
      /* So this is a typedef, set its underlying type.  */
      set_underlying_type (x);

      /* If X is a typedef defined in the current function, record it
	 for the purpose of implementing the -Wunused-local-typedefs
	 warning.  */
      record_locally_defined_typedef (x);
    }

  bind (name, x, scope, /*invisible=*/ಅಸತ್ಯ, nested, locus);

  /* If x's type is incomplete because it's based on a
     structure or union which has not yet been fully declared,
     attach it to that structure or union type, so we can go
     back and complete the variable declaration later, if the
     structure or union gets fully declared.

     If the input is erroneous, we can have error_mark in the type
     slot (e.g. "f(void a, ...)") - that doesn't count as an
     incomplete type.  */
  ಯದಿ (ವೃಕ್ಷ_TYPE (x) != error_mark_ಗಂಟು
      && !COMPLETE_TYPE_P (ವೃಕ್ಷ_TYPE (x)))
    {
      ವೃಕ್ಷ element = ವೃಕ್ಷ_TYPE (x);

      ಯಾವತ್ (ವೃಕ್ಷ_CODE (element) == ARRAY_TYPE)
	element = ವೃಕ್ಷ_TYPE (element);
      element = TYPE_MAIN_VARIANT (element);

      ಯದಿ ((RECORD_OR_UNION_TYPE_P (element)
	   || ವೃಕ್ಷ_CODE (element) == ENUMERAL_TYPE)
	  && (ವೃಕ್ಷ_CODE (x) != TYPE_DECL
	      || ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (x)) == ARRAY_TYPE)
	  && !COMPLETE_TYPE_P (element))
	C_TYPE_INCOMPLETE_VARS (element)
	  = ವೃಕ್ಷ_cons (NULL_ವೃಕ್ಷ, x, C_TYPE_INCOMPLETE_VARS (element));
    }
  ಪ್ರತ್ಯಾಗಮ x;
}


/* Issue a permerror about implicit function declaration.  ID is the function
   identifier, OLDDECL is a declaration of the function in a different scope,
   or NULL_TREE.  */

ಸ್ಥಿರ ಶೂನ್ಯ
implicit_decl_permerror (location_t loc, ವೃಕ್ಷ id, ವೃಕ್ಷ olddecl)
{
  ಯದಿ (!warn_implicit_function_declaration)
    ಪ್ರತ್ಯಾಗಮ;

  ತಾರ್ಕಿಕ warned;
  auto_diagnostic_group d;
  name_hint hint;
  ಯದಿ (!olddecl)
    hint = lookup_name_fuzzy (id, FUZZY_LOOKUP_FUNCTION_NAME, loc);

  ಯದಿ (flag_isoc99)
    {
      ಯದಿ (ಧ್ರುವ ವರ್ಣ *suggestion = hint.suggestion ())
	{
	  gcc_rich_location richloc (loc);
	  richloc.add_fixit_replace (suggestion);
	  warned = permerror_opt (&richloc, OPT_Wimplicit_function_declaration,
				  "implicit declaration of function %qE;"
				  " did you mean %qs?",
				  id, suggestion);
	}
      ಅನ್ಯಥಾ
	warned = permerror_opt (loc, OPT_Wimplicit_function_declaration,
				"implicit declaration of function %qE", id);
    }
  ಅನ್ಯಥಾ ಯದಿ (ಧ್ರುವ ವರ್ಣ *suggestion = hint.suggestion ())
    {
      gcc_rich_location richloc (loc);
      richloc.add_fixit_replace (suggestion);
      warned = warning_at
	(&richloc, OPT_Wimplicit_function_declaration,
	 G_("implicit declaration of function %qE; did you mean %qs?"),
	 id, suggestion);
    }
  ಅನ್ಯಥಾ
    warned = warning_at (loc, OPT_Wimplicit_function_declaration,
			 G_("implicit declaration of function %qE"), id);

  ಯದಿ (warned)
    {
      /* Whether the olddecl is an undeclared builtin function.
	 locate_old_decl will not generate a diagnostic for those,
	 so in that case we want to look elsewhere.  */
      ತಾರ್ಕಿಕ undeclared_builtin = (olddecl
				 && ವೃಕ್ಷ_CODE (olddecl) == FUNCTION_DECL
				 && fndecl_built_in_p (olddecl)
				 && !C_DECL_DECLARED_BUILTIN (olddecl));
      ಯದಿ (undeclared_builtin)
	{
	  ಧ್ರುವ ವರ್ಣ *header = header_for_builtin_fn (olddecl);
	  ಯದಿ (header)
	    {
	      rich_location richloc (ಸಾಲು_table, loc);
	      maybe_add_include_fixit (&richloc, header, ಸತ್ಯ);
	      inform (&richloc,
		      "include %qs or provide a declaration of %qE",
		      header, id);
	    }
	}
      ಅನ್ಯಥಾ ಯದಿ (olddecl)
	locate_old_decl (olddecl);
    }

  ಯದಿ (!warned)
    hint.suppress ();
}

/* Return the name of the header file that declares built-in function
   FNDECL, or null if either we don't know or don't expect to see an
   explicit declaration.  */

ಸ್ಥಿರ ಧ್ರುವ ವರ್ಣ *
header_for_builtin_fn (ವೃಕ್ಷ fndecl)
{
  ಯದಿ (DECL_BUILT_IN_CLASS (fndecl) != BUILT_IN_NORMAL)
    ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;

  ವಿಕಲ್ಪ (DECL_FUNCTION_CODE (fndecl))
    {
    CASE_FLT_FN (BUILT_IN_ACOS):
    CASE_FLT_FN (BUILT_IN_ACOSH):
    CASE_FLT_FN (BUILT_IN_ASIN):
    CASE_FLT_FN (BUILT_IN_ASINH):
    CASE_FLT_FN (BUILT_IN_ATAN):
    CASE_FLT_FN (BUILT_IN_ATANH):
    CASE_FLT_FN (BUILT_IN_ATAN2):
    CASE_FLT_FN (BUILT_IN_CBRT):
    CASE_FLT_FN (BUILT_IN_CEIL):
    CASE_FLT_FN_FLOATN_NX (BUILT_IN_CEIL):
    CASE_FLT_FN (BUILT_IN_COPYSIGN):
    CASE_FLT_FN_FLOATN_NX (BUILT_IN_COPYSIGN):
    CASE_FLT_FN (BUILT_IN_COS):
    CASE_FLT_FN (BUILT_IN_COSH):
    CASE_FLT_FN (BUILT_IN_ERF):
    CASE_FLT_FN (BUILT_IN_ERFC):
    CASE_FLT_FN (BUILT_IN_EXP):
    CASE_FLT_FN (BUILT_IN_EXP2):
    CASE_FLT_FN (BUILT_IN_EXPM1):
    CASE_FLT_FN (BUILT_IN_FABS):
    CASE_FLT_FN_FLOATN_NX (BUILT_IN_FABS):
    CASE_FLT_FN (BUILT_IN_FDIM):
    CASE_FLT_FN (BUILT_IN_FLOOR):
    CASE_FLT_FN_FLOATN_NX (BUILT_IN_FLOOR):
    CASE_FLT_FN (BUILT_IN_FMA):
    CASE_FLT_FN_FLOATN_NX (BUILT_IN_FMA):
    CASE_FLT_FN (BUILT_IN_FMAX):
    CASE_FLT_FN_FLOATN_NX (BUILT_IN_FMAX):
    CASE_FLT_FN (BUILT_IN_FMIN):
    CASE_FLT_FN_FLOATN_NX (BUILT_IN_FMIN):
    CASE_FLT_FN (BUILT_IN_FMOD):
    CASE_FLT_FN (BUILT_IN_FREXP):
    CASE_FLT_FN (BUILT_IN_HYPOT):
    CASE_FLT_FN (BUILT_IN_ILOGB):
    CASE_FLT_FN (BUILT_IN_LDEXP):
    CASE_FLT_FN (BUILT_IN_LGAMMA):
    CASE_FLT_FN (BUILT_IN_LLRINT):
    CASE_FLT_FN (BUILT_IN_LLROUND):
    CASE_FLT_FN (BUILT_IN_LOG):
    CASE_FLT_FN (BUILT_IN_LOG10):
    CASE_FLT_FN (BUILT_IN_LOG1P):
    CASE_FLT_FN (BUILT_IN_LOG2):
    CASE_FLT_FN (BUILT_IN_LOGB):
    CASE_FLT_FN (BUILT_IN_LRINT):
    CASE_FLT_FN (BUILT_IN_LROUND):
    CASE_FLT_FN (BUILT_IN_MODF):
    CASE_FLT_FN (BUILT_IN_NAN):
    CASE_FLT_FN (BUILT_IN_NEARBYINT):
    CASE_FLT_FN_FLOATN_NX (BUILT_IN_NEARBYINT):
    CASE_FLT_FN (BUILT_IN_NEXTAFTER):
    CASE_FLT_FN (BUILT_IN_NEXTTOWARD):
    CASE_FLT_FN (BUILT_IN_POW):
    CASE_FLT_FN (BUILT_IN_REMAINDER):
    CASE_FLT_FN (BUILT_IN_REMQUO):
    CASE_FLT_FN (BUILT_IN_RINT):
    CASE_FLT_FN_FLOATN_NX (BUILT_IN_RINT):
    CASE_FLT_FN (BUILT_IN_ROUND):
    CASE_FLT_FN_FLOATN_NX (BUILT_IN_ROUND):
    CASE_FLT_FN (BUILT_IN_SCALBLN):
    CASE_FLT_FN (BUILT_IN_SCALBN):
    CASE_FLT_FN (BUILT_IN_SIN):
    CASE_FLT_FN (BUILT_IN_SINH):
    CASE_FLT_FN (BUILT_IN_SINCOS):
    CASE_FLT_FN (BUILT_IN_SQRT):
    CASE_FLT_FN_FLOATN_NX (BUILT_IN_SQRT):
    CASE_FLT_FN (BUILT_IN_TAN):
    CASE_FLT_FN (BUILT_IN_TANH):
    CASE_FLT_FN (BUILT_IN_TGAMMA):
    CASE_FLT_FN (BUILT_IN_TRUNC):
    CASE_FLT_FN_FLOATN_NX (BUILT_IN_TRUNC):
    ಪಕ್ಷ BUILT_IN_ISINF:
    ಪಕ್ಷ BUILT_IN_ISNAN:
      ಪ್ರತ್ಯಾಗಮ "<math.h>";
    CASE_FLT_FN (BUILT_IN_CABS):
    CASE_FLT_FN (BUILT_IN_CACOS):
    CASE_FLT_FN (BUILT_IN_CACOSH):
    CASE_FLT_FN (BUILT_IN_CARG):
    CASE_FLT_FN (BUILT_IN_CASIN):
    CASE_FLT_FN (BUILT_IN_CASINH):
    CASE_FLT_FN (BUILT_IN_CATAN):
    CASE_FLT_FN (BUILT_IN_CATANH):
    CASE_FLT_FN (BUILT_IN_CCOS):
    CASE_FLT_FN (BUILT_IN_CCOSH):
    CASE_FLT_FN (BUILT_IN_CEXP):
    CASE_FLT_FN (BUILT_IN_CIMAG):
    CASE_FLT_FN (BUILT_IN_CLOG):
    CASE_FLT_FN (BUILT_IN_CONJ):
    CASE_FLT_FN (BUILT_IN_CPOW):
    CASE_FLT_FN (BUILT_IN_CPROJ):
    CASE_FLT_FN (BUILT_IN_CREAL):
    CASE_FLT_FN (BUILT_IN_CSIN):
    CASE_FLT_FN (BUILT_IN_CSINH):
    CASE_FLT_FN (BUILT_IN_CSQRT):
    CASE_FLT_FN (BUILT_IN_CTAN):
    CASE_FLT_FN (BUILT_IN_CTANH):
      ಪ್ರತ್ಯಾಗಮ "<complex.h>";
    ಪಕ್ಷ BUILT_IN_MEMCHR:
    ಪಕ್ಷ BUILT_IN_MEMCMP:
    ಪಕ್ಷ BUILT_IN_MEMCPY:
    ಪಕ್ಷ BUILT_IN_MEMMOVE:
    ಪಕ್ಷ BUILT_IN_MEMSET:
    ಪಕ್ಷ BUILT_IN_STRCAT:
    ಪಕ್ಷ BUILT_IN_STRCHR:
    ಪಕ್ಷ BUILT_IN_STRCMP:
    ಪಕ್ಷ BUILT_IN_STRCPY:
    ಪಕ್ಷ BUILT_IN_STRCSPN:
    ಪಕ್ಷ BUILT_IN_STRLEN:
    ಪಕ್ಷ BUILT_IN_STRNCAT:
    ಪಕ್ಷ BUILT_IN_STRNCMP:
    ಪಕ್ಷ BUILT_IN_STRNCPY:
    ಪಕ್ಷ BUILT_IN_STRPBRK:
    ಪಕ್ಷ BUILT_IN_STRRCHR:
    ಪಕ್ಷ BUILT_IN_STRSPN:
    ಪಕ್ಷ BUILT_IN_STRSTR:
      ಪ್ರತ್ಯಾಗಮ "<string.h>";
    ಪಕ್ಷ BUILT_IN_FPRINTF:
    ಪಕ್ಷ BUILT_IN_PUTC:
    ಪಕ್ಷ BUILT_IN_FPUTC:
    ಪಕ್ಷ BUILT_IN_FPUTS:
    ಪಕ್ಷ BUILT_IN_FSCANF:
    ಪಕ್ಷ BUILT_IN_FWRITE:
    ಪಕ್ಷ BUILT_IN_PRINTF:
    ಪಕ್ಷ BUILT_IN_PUTCHAR:
    ಪಕ್ಷ BUILT_IN_PUTS:
    ಪಕ್ಷ BUILT_IN_SCANF:
    ಪಕ್ಷ BUILT_IN_SNPRINTF:
    ಪಕ್ಷ BUILT_IN_SPRINTF:
    ಪಕ್ಷ BUILT_IN_SSCANF:
    ಪಕ್ಷ BUILT_IN_VFPRINTF:
    ಪಕ್ಷ BUILT_IN_VFSCANF:
    ಪಕ್ಷ BUILT_IN_VPRINTF:
    ಪಕ್ಷ BUILT_IN_VSCANF:
    ಪಕ್ಷ BUILT_IN_VSNPRINTF:
    ಪಕ್ಷ BUILT_IN_VSPRINTF:
    ಪಕ್ಷ BUILT_IN_VSSCANF:
      ಪ್ರತ್ಯಾಗಮ "<stdio.h>";
    ಪಕ್ಷ BUILT_IN_ISALNUM:
    ಪಕ್ಷ BUILT_IN_ISALPHA:
    ಪಕ್ಷ BUILT_IN_ISBLANK:
    ಪಕ್ಷ BUILT_IN_ISCNTRL:
    ಪಕ್ಷ BUILT_IN_ISDIGIT:
    ಪಕ್ಷ BUILT_IN_ISGRAPH:
    ಪಕ್ಷ BUILT_IN_ISLOWER:
    ಪಕ್ಷ BUILT_IN_ISPRINT:
    ಪಕ್ಷ BUILT_IN_ISPUNCT:
    ಪಕ್ಷ BUILT_IN_ISSPACE:
    ಪಕ್ಷ BUILT_IN_ISUPPER:
    ಪಕ್ಷ BUILT_IN_ISXDIGIT:
    ಪಕ್ಷ BUILT_IN_TOLOWER:
    ಪಕ್ಷ BUILT_IN_TOUPPER:
      ಪ್ರತ್ಯಾಗಮ "<ctype.h>";
    ಪಕ್ಷ BUILT_IN_ISWALNUM:
    ಪಕ್ಷ BUILT_IN_ISWALPHA:
    ಪಕ್ಷ BUILT_IN_ISWBLANK:
    ಪಕ್ಷ BUILT_IN_ISWCNTRL:
    ಪಕ್ಷ BUILT_IN_ISWDIGIT:
    ಪಕ್ಷ BUILT_IN_ISWGRAPH:
    ಪಕ್ಷ BUILT_IN_ISWLOWER:
    ಪಕ್ಷ BUILT_IN_ISWPRINT:
    ಪಕ್ಷ BUILT_IN_ISWPUNCT:
    ಪಕ್ಷ BUILT_IN_ISWSPACE:
    ಪಕ್ಷ BUILT_IN_ISWUPPER:
    ಪಕ್ಷ BUILT_IN_ISWXDIGIT:
    ಪಕ್ಷ BUILT_IN_TOWLOWER:
    ಪಕ್ಷ BUILT_IN_TOWUPPER:
      ಪ್ರತ್ಯಾಗಮ "<wctype.h>";
    ಪಕ್ಷ BUILT_IN_ABORT:
    ಪಕ್ಷ BUILT_IN_ABS:
    ಪಕ್ಷ BUILT_IN_CALLOC:
    ಪಕ್ಷ BUILT_IN_EXIT:
    ಪಕ್ಷ BUILT_IN_FREE:
    ಪಕ್ಷ BUILT_IN_LABS:
    ಪಕ್ಷ BUILT_IN_LLABS:
    ಪಕ್ಷ BUILT_IN_MALLOC:
    ಪಕ್ಷ BUILT_IN_REALLOC:
    ಪಕ್ಷ BUILT_IN__EXIT2:
    ಪಕ್ಷ BUILT_IN_ALIGNED_ALLOC:
      ಪ್ರತ್ಯಾಗಮ "<stdlib.h>";
    ಪಕ್ಷ BUILT_IN_IMAXABS:
      ಪ್ರತ್ಯಾಗಮ "<inttypes.h>";
    ಪಕ್ಷ BUILT_IN_STRFTIME:
      ಪ್ರತ್ಯಾಗಮ "<time.h>";
    ಸ್ವಭಾವ:
      ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }
}

/* Generate an implicit declaration for identifier FUNCTIONID at LOC as a
   function of type int ().  */

ವೃಕ್ಷ
implicitly_declare (location_t loc, ವೃಕ್ಷ functionid)
{
  ಸಂರಚನಾ c_binding *b;
  ವೃಕ್ಷ decl = NULL_ವೃಕ್ಷ;
  ವೃಕ್ಷ asmspec_ವೃಕ್ಷ;

  ಪ್ರತಿ (b = I_ಚಿಹ್ನೆ_BINDING (functionid); b; b = b->shadowed)
    {
      ಯದಿ (B_IN_SCOPE (b, external_scope))
	{
	  decl = b->decl;
	  ಭಙ್ಗ;
	}
    }

  ಯದಿ (decl)
    {
      ಯದಿ (ವೃಕ್ಷ_CODE (decl) != FUNCTION_DECL)
	ಪ್ರತ್ಯಾಗಮ decl;

      /* FIXME: Objective-C has weird not-really-builtin functions
	 which are supposed to be visible automatically.  They wind up
	 in the external scope because they're pushed before the file
	 scope gets created.  Catch this here and rebind them into the
	 file scope.  */
      ಯದಿ (!fndecl_built_in_p (decl) && DECL_IS_UNDECLARED_BUILTIN (decl))
	{
	  bind (functionid, decl, file_scope,
		/*invisible=*/ಅಸತ್ಯ, /*nested=*/ಸತ್ಯ,
		DECL_SOURCE_LOCATION (decl));
	  ಪ್ರತ್ಯಾಗಮ decl;
	}
      ಅನ್ಯಥಾ
	{
	  ವೃಕ್ಷ newtype = default_function_type;
	  ಯದಿ (b->u.type)
	    ವೃಕ್ಷ_TYPE (decl) = b->u.type;
	  /* Implicit declaration of a function already declared
	     (somehow) in a different scope, or as a built-in.
	     If this is the first time this has happened, warn;
	     then recycle the old declaration but with the new type.  */
	  ಯದಿ (!C_DECL_IMPLICIT (decl))
	    {
	      implicit_decl_permerror (loc, functionid, decl);
	      C_DECL_IMPLICIT (decl) = 1;
	    }
	  ಯದಿ (fndecl_built_in_p (decl))
	    {
	      newtype = c_build_type_attribute_variant (newtype,
							TYPE_ATTRIBUTES
							(ವೃಕ್ಷ_TYPE (decl)));
	      ಯದಿ (!comptypes (newtype, ವೃಕ್ಷ_TYPE (decl)))
		{
		  auto_diagnostic_group d;
		  ತಾರ್ಕಿಕ warned = warning_at (loc,
					    OPT_Wbuiltin_declaration_mismatch,
					    "incompatible implicit "
					    "declaration of built-in "
					    "function %qD", decl);
		  /* See if we can hint which header to include.  */
		  ಧ್ರುವ ವರ್ಣ *header = header_for_builtin_fn (decl);
		  ಯದಿ (header != ರಿಕ್ತ && warned)
		    {
		      rich_location richloc (ಸಾಲು_table, loc);
		      maybe_add_include_fixit (&richloc, header, ಸತ್ಯ);
		      inform (&richloc,
			      "include %qs or provide a declaration of %qD",
			      header, decl);
		    }
		  newtype = ವೃಕ್ಷ_TYPE (decl);
		}
	    }
	  ಅನ್ಯಥಾ
	    {
	      ಯದಿ (!comptypes (newtype, ವೃಕ್ಷ_TYPE (decl)))
		{
		  auto_diagnostic_group d;
		  error_at (loc, "incompatible implicit declaration of "
			    "function %qD", decl);
		  locate_old_decl (decl);
		}
	    }
	  b->u.type = ವೃಕ್ಷ_TYPE (decl);
	  ವೃಕ್ಷ_TYPE (decl) = newtype;
	  bind (functionid, decl, current_scope,
		/*invisible=*/ಅಸತ್ಯ, /*nested=*/ಸತ್ಯ,
		DECL_SOURCE_LOCATION (decl));
	  ಪ್ರತ್ಯಾಗಮ decl;
	}
    }

  /* Not seen before.  */
  decl = build_decl (loc, FUNCTION_DECL, functionid, default_function_type);
  DECL_EXTERNAL (decl) = 1;
  ವೃಕ್ಷ_PUBLIC (decl) = 1;
  C_DECL_IMPLICIT (decl) = 1;
  implicit_decl_permerror (loc, functionid, 0);
  asmspec_ವೃಕ್ಷ = maybe_apply_renaming_pragma (decl, /*asmname=*/ರಿಕ್ತ);
  ಯದಿ (asmspec_ವೃಕ್ಷ)
    set_user_assembler_name (decl, ವೃಕ್ಷ_STRING_POINTER (asmspec_ವೃಕ್ಷ));

  /* C89 says implicit declarations are in the innermost block.
     So we record the decl in the standard fashion.  */
  decl = pushdecl (decl);

  /* No need to call objc_check_decl here - it's a function type.  */
  rest_of_decl_compilation (decl, 0, 0);

  /* Write a record describing this implicit function declaration
     to the prototypes file (if requested).  */
  gen_aux_info_record (decl, 0, 1, 0);

  /* Possibly apply some default attributes to this implicit declaration.  */
  decl_attributes (&decl, NULL_ವೃಕ್ಷ, 0);

  ಪ್ರತ್ಯಾಗಮ decl;
}

/* Issue an error message for a reference to an undeclared variable
   ID, including a reference to a builtin outside of function-call
   context.  Establish a binding of the identifier to error_mark_node
   in an appropriate scope, which will suppress further errors for the
   same identifier.  The error message should be given location LOC.  */
ಶೂನ್ಯ
undeclared_variable (location_t loc, ವೃಕ್ಷ id)
{
  ಸ್ಥಿರ ತಾರ್ಕಿಕ already = ಅಸತ್ಯ;
  ಸಂರಚನಾ c_scope *scope;

  auto_diagnostic_group d;
  ಯದಿ (current_function_decl == NULL_ವೃಕ್ಷ)
    {
      name_hint guessed_id = lookup_name_fuzzy (id, FUZZY_LOOKUP_NAME, loc);
      ಯದಿ (ಧ್ರುವ ವರ್ಣ *suggestion = guessed_id.suggestion ())
	{
	  gcc_rich_location richloc (loc);
	  richloc.add_fixit_replace (suggestion);
	  error_at (&richloc,
		    "%qE undeclared here (not in a function);"
		    " did you mean %qs?",
		    id, suggestion);
	}
      ಅನ್ಯಥಾ
	error_at (loc, "%qE undeclared here (not in a function)", id);
      scope = current_scope;
    }
  ಅನ್ಯಥಾ
    {
      ಯದಿ (!objc_diagnose_private_ivar (id))
	{
	  name_hint guessed_id = lookup_name_fuzzy (id, FUZZY_LOOKUP_NAME, loc);
	  ಯದಿ (ಧ್ರುವ ವರ್ಣ *suggestion = guessed_id.suggestion ())
	    {
	      gcc_rich_location richloc (loc);
	      richloc.add_fixit_replace (suggestion);
	      error_at (&richloc,
			"%qE undeclared (first use in this function);"
			" did you mean %qs?",
			id, suggestion);
	    }
	  ಅನ್ಯಥಾ
	    error_at (loc, "%qE undeclared (first use in this function)", id);
	}
      ಯದಿ (!already)
	{
          inform (loc, "each undeclared identifier is reported only"
                  " once for each function it appears in");
	  already = ಸತ್ಯ;
	}

      /* If we are parsing old-style parameter decls, current_function_decl
	 will be nonnull but current_function_scope will be null.  */
      scope = current_function_scope ? current_function_scope : current_scope;
    }
  bind (id, error_mark_ಗಂಟು, scope, /*invisible=*/ಅಸತ್ಯ, /*nested=*/ಅಸತ್ಯ,
	UNKNOWN_LOCATION);
}

/* Subroutine of lookup_label, declare_label, define_label: construct a
   LABEL_DECL with all the proper frills.  Also create a struct
   c_label_vars initialized for the current scope.  */

ಸ್ಥಿರ ವೃಕ್ಷ
make_label (location_t location, ವೃಕ್ಷ name, ತಾರ್ಕಿಕ defining,
	    ಸಂರಚನಾ c_label_vars **p_label_vars)
{
  ವೃಕ್ಷ label = build_decl (location, LABEL_DECL, name, void_type_ಗಂಟು);
  DECL_CONTEXT (label) = current_function_decl;
  SET_DECL_MODE (label, VOIDmode);

  c_label_vars *label_vars = ggc_alloc<c_label_vars> ();
  label_vars->shadowed = ರಿಕ್ತ;
  set_spot_bindings (&label_vars->label_bindings, defining);
  label_vars->decls_in_scope = make_ವೃಕ್ಷ_vector ();
  label_vars->gotos = ರಿಕ್ತ;
  *p_label_vars = label_vars;

  ಪ್ರತ್ಯಾಗಮ label;
}

/* Get the LABEL_DECL corresponding to identifier NAME as a label.
   Create one if none exists so far for the current function.
   This is called when a label is used in a goto expression or
   has its address taken.  */

ವೃಕ್ಷ
lookup_label (ವೃಕ್ಷ name)
{
  ವೃಕ್ಷ label;
  ಸಂರಚನಾ c_label_vars *label_vars;

  ಯದಿ (current_function_scope == 0)
    {
      error ("label %qE referenced outside of any function", name);
      ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;
    }

  /* Use a label already defined or ref'd with this name, but not if
     it is inherited from a containing function and wasn't declared
     using __label__.  */
  label = I_LABEL_DECL (name);
  ಯದಿ (label && (DECL_CONTEXT (label) == current_function_decl
		|| C_DECLARED_LABEL_FLAG (label)))
    {
      /* If the label has only been declared, update its apparent
	 location to point here, for better diagnostics if it
	 turns out not to have been defined.  */
      ಯದಿ (DECL_INITIAL (label) == NULL_ವೃಕ್ಷ)
	DECL_SOURCE_LOCATION (label) = ಒಳಹರಿವು_location;
      ಪ್ರತ್ಯಾಗಮ label;
    }

  /* No label binding for that identifier; make one.  */
  label = make_label (ಒಳಹರಿವು_location, name, ಅಸತ್ಯ, &label_vars);

  /* Ordinary labels go in the current function scope.  */
  bind_label (name, label, current_function_scope, label_vars);

  ಪ್ರತ್ಯಾಗಮ label;
}

/* Issue a warning about DECL for a goto statement at GOTO_LOC going
   to LABEL.  */

ಸ್ಥಿರ ಶೂನ್ಯ
warn_about_goto (location_t goto_loc, ವೃಕ್ಷ label, ವೃಕ್ಷ decl)
{
  auto_diagnostic_group d;
  ಯದಿ (c_type_variably_modified_p (ವೃಕ್ಷ_TYPE (decl)))
    error_at (goto_loc,
	      "jump into scope of identifier with variably modified type");
  ಅನ್ಯಥಾ ಯದಿ (flag_openmp
	   && lookup_attribute ("omp allocate", DECL_ATTRIBUTES (decl)))
    error_at (goto_loc, "jump skips OpenMP %<allocate%> allocation");
  ಅನ್ಯಥಾ
    ಯದಿ (!warning_at (goto_loc, OPT_Wjump_misses_init,
		     "jump skips variable initialization"))
      ಪ್ರತ್ಯಾಗಮ;
  inform (DECL_SOURCE_LOCATION (label), "label %qD defined here", label);
  inform (DECL_SOURCE_LOCATION (decl), "%qD declared here", decl);
}

/* Look up a label because of a goto statement.  This is like
   lookup_label, but also issues any appropriate warnings.  */

ವೃಕ್ಷ
lookup_label_for_goto (location_t loc, ವೃಕ್ಷ name)
{
  ವೃಕ್ಷ label;
  ಸಂರಚನಾ c_label_vars *label_vars;
  unsigned ಪೂರ್ಣಾಙ್ಕ ix;
  ವೃಕ್ಷ decl;

  label = lookup_label (name);
  ಯದಿ (label == NULL_ವೃಕ್ಷ)
    ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;

  /* If we are jumping to a different function, we can't issue any
     useful warnings.  */
  ಯದಿ (DECL_CONTEXT (label) != current_function_decl)
    {
      gcc_assert (C_DECLARED_LABEL_FLAG (label));
      ಪ್ರತ್ಯಾಗಮ label;
    }

  label_vars = I_LABEL_BINDING (name)->u.label;

  /* If the label has not yet been defined, then push this goto on a
     list for possible later warnings.  */
  ಯದಿ (label_vars->label_bindings.scope == ರಿಕ್ತ)
    {
      c_goto_bindings *g = ggc_alloc<c_goto_bindings> ();

      g->loc = loc;
      set_spot_bindings (&g->goto_bindings, ಸತ್ಯ);
      vec_safe_ತಳ್ಳು (label_vars->gotos, g);
      ಪ್ರತ್ಯಾಗಮ label;
    }

  /* If there are any decls in label_vars->decls_in_scope, then this
     goto has missed the declaration of the decl.  This happens for a
     case like
       int i = 1;
      lab:
       ...
       goto lab;
     Issue a warning or error.  */
  FOR_EACH_VEC_SAFE_ELT (label_vars->decls_in_scope, ix, decl)
    warn_about_goto (loc, label, decl);

  ಯದಿ (label_vars->label_bindings.ಎಡ_stmt_ಅಭಿವ್ಯಕ್ತಿ)
    {
      auto_diagnostic_group d;
      error_at (loc, "jump into statement expression");
      inform (DECL_SOURCE_LOCATION (label), "label %qD defined here", label);
    }

  ಪ್ರತ್ಯಾಗಮ label;
}

/* Make a label named NAME in the current function, shadowing silently
   any that may be inherited from containing functions or containing
   scopes.  This is called for __label__ declarations.  */

ವೃಕ್ಷ
declare_label (ವೃಕ್ಷ name)
{
  ಸಂರಚನಾ c_binding *b = I_LABEL_BINDING (name);
  ವೃಕ್ಷ label;
  ಸಂರಚನಾ c_label_vars *label_vars;

  /* Check to make sure that the label hasn't already been declared
     at this scope */
  ಯದಿ (b && B_IN_CURRENT_SCOPE (b))
    {
      auto_diagnostic_group d;
      error ("duplicate label declaration %qE", name);
      locate_old_decl (b->decl);

      /* Just use the previous declaration.  */
      ಪ್ರತ್ಯಾಗಮ b->decl;
    }

  label = make_label (ಒಳಹರಿವು_location, name, ಅಸತ್ಯ, &label_vars);
  C_DECLARED_LABEL_FLAG (label) = 1;

  /* Declared labels go in the current scope.  */
  bind_label (name, label, current_scope, label_vars);

  ಪ್ರತ್ಯಾಗಮ label;
}

/* When we define a label, issue any appropriate warnings if there are
   any gotos earlier in the function which jump to this label.  */

ಸ್ಥಿರ ಶೂನ್ಯ
check_earlier_gotos (ವೃಕ್ಷ label, ಸಂರಚನಾ c_label_vars* label_vars)
{
  unsigned ಪೂರ್ಣಾಙ್ಕ ix;
  ಸಂರಚನಾ c_goto_bindings *g;

  FOR_EACH_VEC_SAFE_ELT (label_vars->gotos, ix, g)
    {
      ಸಂರಚನಾ c_binding *b;
      ಸಂರಚನಾ c_scope *scope;

      /* We have a goto to this label.  The goto is going forward.  In
	 g->scope, the goto is going to skip any binding which was
	 defined after g->bindings_in_scope.  */
      ಯದಿ (g->goto_bindings.scope->has_jump_unsafe_decl)
	{
	  ಪ್ರತಿ (b = g->goto_bindings.scope->bindings;
	       b != g->goto_bindings.bindings_in_scope;
	       b = b->prev)
	    {
	      ಯದಿ (decl_jump_unsafe (b->decl))
		warn_about_goto (g->loc, label, b->decl);
	    }
	}

      /* We also need to warn about decls defined in any scopes
	 between the scope of the label and the scope of the goto.  */
      ಪ್ರತಿ (scope = label_vars->label_bindings.scope;
	   scope != g->goto_bindings.scope;
	   scope = scope->outer)
	{
	  gcc_assert (scope != ರಿಕ್ತ);
	  ಯದಿ (scope->has_jump_unsafe_decl)
	    {
	      ಯದಿ (scope == label_vars->label_bindings.scope)
		b = label_vars->label_bindings.bindings_in_scope;
	      ಅನ್ಯಥಾ
		b = scope->bindings;
	      ಪ್ರತಿ (; b != ರಿಕ್ತ; b = b->prev)
		{
		  ಯದಿ (decl_jump_unsafe (b->decl))
		    warn_about_goto (g->loc, label, b->decl);
		}
	    }
	}

      ಯದಿ (g->goto_bindings.stmt_exprs > 0)
	{
	  auto_diagnostic_group d;
	  error_at (g->loc, "jump into statement expression");
	  inform (DECL_SOURCE_LOCATION (label), "label %qD defined here",
		  label);
	}
    }

  /* Now that the label is defined, we will issue warnings about
     subsequent gotos to this label when we see them.  */
  vec_safe_truncate (label_vars->gotos, 0);
  label_vars->gotos = ರಿಕ್ತ;
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

  ಯದಿ (label
      && ((DECL_CONTEXT (label) == current_function_decl
	   && DECL_INITIAL (label) != NULL_ವೃಕ್ಷ)
	  || (DECL_CONTEXT (label) != current_function_decl
	      && C_DECLARED_LABEL_FLAG (label))))
    {
      auto_diagnostic_group d;
      error_at (location, "duplicate label %qD", label);
      locate_old_decl (label);
      ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;
    }
  ಅನ್ಯಥಾ ಯದಿ (label && DECL_CONTEXT (label) == current_function_decl)
    {
      ಸಂರಚನಾ c_label_vars *label_vars = I_LABEL_BINDING (name)->u.label;

      /* The label has been used or declared already in this function,
	 but not defined.  Update its location to point to this
	 definition.  */
      DECL_SOURCE_LOCATION (label) = location;
      set_spot_bindings (&label_vars->label_bindings, ಸತ್ಯ);

      /* Issue warnings as required about any goto statements from
	 earlier in the function.  */
      check_earlier_gotos (label, label_vars);
    }
  ಅನ್ಯಥಾ
    {
      ಸಂರಚನಾ c_label_vars *label_vars;

      /* No label binding for that identifier; make one.  */
      label = make_label (location, name, ಸತ್ಯ, &label_vars);

      /* Ordinary labels go in the current function scope.  */
      bind_label (name, label, current_function_scope, label_vars);
    }

  ಯದಿ (!in_system_header_at (ಒಳಹರಿವು_location) && lookup_name (name))
    warning_at (location, OPT_Wtraditional,
		"traditional C lacks a separate namespace "
		"for labels, identifier %qE conflicts", name);

  /* Mark label as having been defined.  */
  DECL_INITIAL (label) = error_mark_ಗಂಟು;
  ಪ್ರತ್ಯಾಗಮ label;
}

/* Get the bindings for a new switch statement.  This is used to issue
   warnings as appropriate for jumps from the switch to case or
   default labels.  */

ಸಂರಚನಾ c_spot_bindings *
c_get_switch_bindings (ಶೂನ್ಯ)
{
  ಸಂರಚನಾ c_spot_bindings *switch_bindings;

  switch_bindings = XNEW (ಸಂರಚನಾ c_spot_bindings);
  set_spot_bindings (switch_bindings, ಸತ್ಯ);
  ಪ್ರತ್ಯಾಗಮ switch_bindings;
}

ಶೂನ್ಯ
c_release_switch_bindings (ಸಂರಚನಾ c_spot_bindings *bindings)
{
  gcc_assert (bindings->stmt_exprs == 0 && !bindings->ಎಡ_stmt_ಅಭಿವ್ಯಕ್ತಿ);
  XDELETE (bindings);
}

/* This is called at the point of a case or default label to issue
   warnings about decls as needed.  It returns true if it found an
   error, not just a warning.  */

ತಾರ್ಕಿಕ
c_check_switch_jump_warnings (ಸಂರಚನಾ c_spot_bindings *switch_bindings,
			      location_t switch_loc, location_t case_loc)
{
  ತಾರ್ಕಿಕ saw_error;
  ಸಂರಚನಾ c_scope *scope;

  saw_error = ಅಸತ್ಯ;
  ಪ್ರತಿ (scope = current_scope;
       scope != switch_bindings->scope;
       scope = scope->outer)
    {
      ಸಂರಚನಾ c_binding *b;

      gcc_assert (scope != ರಿಕ್ತ);

      ಯದಿ (!scope->has_jump_unsafe_decl)
	ಅನುವರ್ತ;

      ಪ್ರತಿ (b = scope->bindings; b != ರಿಕ್ತ; b = b->prev)
	{
	  ಯದಿ (decl_jump_unsafe (b->decl))
	    {
	      auto_diagnostic_group d;
	      ತಾರ್ಕಿಕ emitted;
	      ಯದಿ (c_type_variably_modified_p (ವೃಕ್ಷ_TYPE (b->decl)))
		{
		  saw_error = ಸತ್ಯ;
		  error_at (case_loc,
			    "switch jumps into scope of identifier with "
			    "variably modified type");
		  emitted = ಸತ್ಯ;
		}
	      ಅನ್ಯಥಾ ಯದಿ (flag_openmp
		       && lookup_attribute ("omp allocate",
					    DECL_ATTRIBUTES (b->decl)))
		{
		  saw_error = ಸತ್ಯ;
		  error_at (case_loc,
			    "switch jumps over OpenMP %<allocate%> allocation");
		  emitted = ಸತ್ಯ;
		}
	      ಅನ್ಯಥಾ
		emitted
		  = warning_at (case_loc, OPT_Wjump_misses_init,
				"switch jumps over variable initialization");
	      ಯದಿ (emitted)
		{
		  inform (switch_loc, "switch starts here");
		  inform (DECL_SOURCE_LOCATION (b->decl), "%qD declared here",
			  b->decl);
		}
	    }
	}
    }

  ಯದಿ (switch_bindings->stmt_exprs > 0)
    {
      saw_error = ಸತ್ಯ;
      auto_diagnostic_group d;
      error_at (case_loc, "switch jumps into statement expression");
      inform (switch_loc, "switch starts here");
    }

  ಪ್ರತ್ಯಾಗಮ saw_error;
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
lookup_tag (ಗಣನಾ ವೃಕ್ಷ_code code, ವೃಕ್ಷ name, ತಾರ್ಕಿಕ thislevel_only,
	    location_t *ploc)
{
  ಸಂರಚನಾ c_binding *b = I_TAG_BINDING (name);
  ತಾರ್ಕಿಕ thislevel = ಅಸತ್ಯ;

  ಯದಿ (!b || !b->decl)
    ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;

  /* We only care about whether it's in this level if
     thislevel_only was set or it might be a type clash.  */
  ಯದಿ (thislevel_only || ವೃಕ್ಷ_CODE (b->decl) != code)
    {
      /* For our purposes, a tag in the external scope is the same as
	 a tag in the file scope.  (Primarily relevant to Objective-C
	 and its builtin structure tags, which get pushed before the
	 file scope is created.)  */
      ಯದಿ (B_IN_CURRENT_SCOPE (b)
	  || (current_scope == file_scope && B_IN_EXTERNAL_SCOPE (b)))
	thislevel = ಸತ್ಯ;
    }

  ಯದಿ (thislevel_only && !thislevel)
    ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;

  ಯದಿ (ವೃಕ್ಷ_CODE (b->decl) != code)
    {
      /* Definition isn't the kind we were looking for.  */
      pending_invalid_xref = name;
      pending_invalid_xref_location = ಒಳಹರಿವು_location;

      /* If in the same binding level as a declaration as a tag
	 of a different type, this must not be allowed to
	 shadow that tag, so give the error immediately.
	 (For example, "struct foo; union foo;" is invalid.)  */
      ಯದಿ (thislevel)
	pending_xref_error ();
    }

  ಯದಿ (ploc != ರಿಕ್ತ)
    *ploc = b->locus;

  ಪ್ರತ್ಯಾಗಮ b->decl;
}

/* Return true if a definition exists for NAME with code CODE.  */

ತಾರ್ಕಿಕ
tag_exists_p (ಗಣನಾ ವೃಕ್ಷ_code code, ವೃಕ್ಷ name)
{
  ಸಂರಚನಾ c_binding *b = I_TAG_BINDING (name);

  ಯದಿ (b == ರಿಕ್ತ || b->decl == NULL_ವೃಕ್ಷ)
    ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
  ಪ್ರತ್ಯಾಗಮ ವೃಕ್ಷ_CODE (b->decl) == code;
}

/* Print an error message now
   for a recent invalid struct, union or enum cross reference.
   We don't print them immediately because they are not invalid
   when used in the `struct foo;' construct for shadowing.  */

ಶೂನ್ಯ
pending_xref_error (ಶೂನ್ಯ)
{
  ಯದಿ (pending_invalid_xref != NULL_ವೃಕ್ಷ)
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
  ಸಂರಚನಾ c_binding *b = I_ಚಿಹ್ನೆ_BINDING (name);
  /* Do not resolve non-default function versions.  */
  ಯದಿ (b
      && ವೃಕ್ಷ_CODE (b->decl) == FUNCTION_DECL
      && DECL_FUNCTION_VERSIONED (b->decl)
      && !is_function_default_version (b->decl))
    ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;
  ಯದಿ (b && !b->invisible)
    {
      maybe_record_typedef_use (b->decl);
      ಪ್ರತ್ಯಾಗಮ b->decl;
    }
  ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;
}

/* Similar to `lookup_name' but look only at the indicated scope.  */

ಸ್ಥಿರ ವೃಕ್ಷ
lookup_name_in_scope (ವೃಕ್ಷ name, ಸಂರಚನಾ c_scope *scope)
{
  ಸಂರಚನಾ c_binding *b;

  ಪ್ರತಿ (b = I_ಚಿಹ್ನೆ_BINDING (name); b; b = b->shadowed)
    ಯದಿ (B_IN_SCOPE (b, scope))
      ಪ್ರತ್ಯಾಗಮ b->decl;
  ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;
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
lookup_name_fuzzy (ವೃಕ್ಷ name, ಗಣನಾ lookup_name_fuzzy_kind kind, location_t loc)
{
  gcc_assert (ವೃಕ್ಷ_CODE (name) == IDENTIFIER_ಗಂಟು);

  /* Look up function-like macros first; maybe misusing them. */
  auto cpp_ಗಂಟು = cpp_lookup (parse_in,
			      (ಧ್ರುವ unsigned ವರ್ಣ*)IDENTIFIER_POINTER (name),
			      IDENTIFIER_LENGTH (name));
  ಯದಿ (cpp_ಗಂಟು && cpp_fun_like_macro_p (cpp_ಗಂಟು))
    ಪ್ರತ್ಯಾಗಮ name_hint
      (nullptr,
       std::make_unique<macro_like_function_used> (loc,
						   IDENTIFIER_POINTER (name)));

  /* Next, try some well-known names in the C standard library, in case
     the user forgot a #include.  */
  ಧ್ರುವ ವರ್ಣ *header_hint
    = get_c_stdlib_header_for_name (IDENTIFIER_POINTER (name));

  ಯದಿ (header_hint)
    ಪ್ರತ್ಯಾಗಮ name_hint
      (nullptr,
       std::make_unique<suggest_missing_header> (loc,
						 IDENTIFIER_POINTER (name),
						 header_hint));

  /* Next, look for exact matches for builtin defines that would have been
     defined if the user had passed a command-line option (e.g. -fopenmp
     for "_OPENMP").  */
  diagnostics::option_id option_id
    = get_option_for_builtin_define (IDENTIFIER_POINTER (name));
  ಯದಿ (option_id.m_idx > 0)
    ಪ್ರತ್ಯಾಗಮ name_hint
      (nullptr,
       std::make_unique<suggest_missing_option> (loc,
						 IDENTIFIER_POINTER (name),
						 option_id));

  /* Only suggest names reserved for the implementation if NAME begins
     with an underscore.  */
  ತಾರ್ಕಿಕ consider_implementation_names = (IDENTIFIER_POINTER (name)[0] == '_');

  best_match<ವೃಕ್ಷ, ವೃಕ್ಷ> bm (name);

  /* Look within currently valid scopes.  */
  ಪ್ರತಿ (c_scope *scope = current_scope; scope; scope = scope->outer)
    ಪ್ರತಿ (c_binding *binding = scope->bindings; binding; binding = binding->prev)
      {
	ಯದಿ (!binding->id || binding->invisible)
	  ಅನುವರ್ತ;
	ಯದಿ (binding->decl == error_mark_ಗಂಟು)
	  ಅನುವರ್ತ;
	/* Don't use bindings from implicitly declared functions,
	   as they were likely misspellings themselves.  */
	ಯದಿ (ವೃಕ್ಷ_CODE (binding->decl) == FUNCTION_DECL)
	  ಯದಿ (C_DECL_IMPLICIT (binding->decl))
	    ಅನುವರ್ತ;
	/* Don't suggest names that are reserved for use by the
	   implementation, unless NAME began with an underscore.  */
	ಯದಿ (!consider_implementation_names)
	  {
	    ಧ್ರುವ ವರ್ಣ *suggestion_str = IDENTIFIER_POINTER (binding->id);
	    ಯದಿ (name_reserved_for_implementation_p (suggestion_str))
	      ಅನುವರ್ತ;
	  }
	ವಿಕಲ್ಪ (kind)
	  {
	  ಪಕ್ಷ FUZZY_LOOKUP_TYPENAME:
	    ಯದಿ (ವೃಕ್ಷ_CODE (binding->decl) != TYPE_DECL)
	      ಅನುವರ್ತ;
	    ಭಙ್ಗ;

	  ಪಕ್ಷ FUZZY_LOOKUP_FUNCTION_NAME:
	    ಯದಿ (ವೃಕ್ಷ_CODE (binding->decl) != FUNCTION_DECL)
	      {
		/* Allow function pointers.  */
		ಯದಿ ((VAR_P (binding->decl)
		     || ವೃಕ್ಷ_CODE (binding->decl) == PARM_DECL)
		    && ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (binding->decl)) == POINTER_TYPE
		    && (ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_TYPE (binding->decl)))
			== FUNCTION_TYPE))
		  ಭಙ್ಗ;
		ಅನುವರ್ತ;
	      }
	    ಭಙ್ಗ;

	  ಸ್ವಭಾವ:
	    ಭಙ್ಗ;
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
  best_macro_match bmm (name, bm.get_best_distance (), parse_in);
  cpp_hashnode *best_macro = bmm.get_best_meaningful_candidate ();
  /* If a macro is the closest so far to NAME, use it, creating an
     identifier tree node for it.  */
  ಯದಿ (best_macro)
    {
      ಧ್ರುವ ವರ್ಣ *id = (ಧ್ರುವ ವರ್ಣ *)best_macro->ident.str;
      ವೃಕ್ಷ macro_as_identifier
	= get_identifier_with_length (id, best_macro->ident.len);
      bm.set_best_so_far (macro_as_identifier,
			  bmm.get_best_distance (),
			  bmm.get_best_candidate_length ());
    }

  /* Try the "start_typename" keywords to detect
     "singed" vs "signed" typos.  */
  ಯದಿ (kind == FUZZY_LOOKUP_TYPENAME)
    {
      ಪ್ರತಿ (unsigned i = 0; i < ಅಂಕೆ_c_common_reswords; i++)
	{
	  ಧ್ರುವ c_common_resword *resword = &c_common_reswords[i];
	  ಯದಿ (!c_keyword_starts_typename (resword->rid))
	    ಅನುವರ್ತ;
	  ವೃಕ್ಷ resword_identifier = ridpointers [resword->rid];
	  ಯದಿ (!resword_identifier)
	    ಅನುವರ್ತ;
	  gcc_assert (ವೃಕ್ಷ_CODE (resword_identifier) == IDENTIFIER_ಗಂಟು);
	  bm.consider (resword_identifier);
	}
    }

  ವೃಕ್ಷ best = bm.get_best_meaningful_candidate ();
  ಯದಿ (best)
    ಪ್ರತ್ಯಾಗಮ name_hint (IDENTIFIER_POINTER (best), ರಿಕ್ತ);
  ಅನ್ಯಥಾ
    ಪ್ರತ್ಯಾಗಮ name_hint (ರಿಕ್ತ, ರಿಕ್ತ);
}


/* Handle the standard [[nodiscard]] attribute.  */

ಸ್ಥಿರ ವೃಕ್ಷ
handle_nodiscard_attribute (ವೃಕ್ಷ *ಗಂಟು, ವೃಕ್ಷ name, ವೃಕ್ಷ /*args*/,
			    ಪೂರ್ಣಾಙ್ಕ /*flags*/, ತಾರ್ಕಿಕ *no_add_attrs)
{
  ಯದಿ (ವೃಕ್ಷ_CODE (*ಗಂಟು) == FUNCTION_DECL)
    {
      ಯದಿ (VOID_TYPE_P (ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_TYPE (*ಗಂಟು))))
	warning_at (DECL_SOURCE_LOCATION (*ಗಂಟು),
		    OPT_Wattributes, "%qE attribute applied to %qD with void "
		    "return type", name, *ಗಂಟು);
    }
  ಅನ್ಯಥಾ ಯದಿ (RECORD_OR_UNION_TYPE_P (*ಗಂಟು)
	   || ವೃಕ್ಷ_CODE (*ಗಂಟು) == ENUMERAL_TYPE)
    /* OK */;
  ಅನ್ಯಥಾ
    {
      pedwarn (ಒಳಹರಿವು_location,
	       OPT_Wattributes, "%qE attribute can only be applied to "
	       "functions or to structure, union or enumeration types", name);
      *no_add_attrs = ಸತ್ಯ;
    }
  ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;
}

/* Handle the standard [[noreturn]] attribute.  */

ಸ್ಥಿರ ವೃಕ್ಷ
handle_std_noreturn_attribute (ವೃಕ್ಷ *ಗಂಟು, ವೃಕ್ಷ name, ವೃಕ್ಷ args,
			       ಪೂರ್ಣಾಙ್ಕ flags, ತಾರ್ಕಿಕ *no_add_attrs)
{
  /* Unlike GNU __attribute__ ((noreturn)), the standard [[noreturn]]
     only applies to functions, not function pointers.  */
  ಯದಿ (ವೃಕ್ಷ_CODE (*ಗಂಟು) == FUNCTION_DECL)
    ಪ್ರತ್ಯಾಗಮ handle_noreturn_attribute (ಗಂಟು, name, args, flags, no_add_attrs);
  ಅನ್ಯಥಾ
    {
      pedwarn (ಒಳಹರಿವು_location, OPT_Wattributes,
	       "standard %qE attribute can only be applied to functions",
	       name);
      *no_add_attrs = ಸತ್ಯ;
      ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;
    }
}

/* Handle the standard [[unsequenced]] attribute.  */

ಸ್ಥಿರ ವೃಕ್ಷ
handle_std_unsequenced_attribute (ವೃಕ್ಷ *ಗಂಟು, ವೃಕ್ಷ name, ವೃಕ್ಷ args,
				  ಪೂರ್ಣಾಙ್ಕ flags, ತಾರ್ಕಿಕ *no_add_attrs)
{
  /* Unlike GNU __attribute__ ((unsequenced)), the standard [[unsequenced]]
     should be only applied to function declarators or type specifiers which
     have function type.  */
  ಯದಿ (ಗಂಟು[2])
    {
      auto_diagnostic_group d;
      ಯದಿ (pedwarn (ಒಳಹರಿವು_location, OPT_Wattributes,
		   "standard %qE attribute can only be applied to function "
		   "declarators or type specifiers with function type", name))
	inform (ಒಳಹರಿವು_location, "did you mean to specify it after %<)%> "
				"following function parameters?");
      *no_add_attrs = ಸತ್ಯ;
      ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;
    }
  ಪ್ರತ್ಯಾಗಮ handle_unsequenced_attribute (ಗಂಟು, name, args, flags, no_add_attrs);
}

/* Handle the standard [[reproducible]] attribute.  */

ಸ್ಥಿರ ವೃಕ್ಷ
handle_std_reproducible_attribute (ವೃಕ್ಷ *ಗಂಟು, ವೃಕ್ಷ name, ವೃಕ್ಷ args,
				   ಪೂರ್ಣಾಙ್ಕ flags, ತಾರ್ಕಿಕ *no_add_attrs)
{
  ಪ್ರತ್ಯಾಗಮ handle_std_unsequenced_attribute (ಗಂಟು, name, args, flags,
					   no_add_attrs);
}

/* Table of supported standard (C23) attributes.  */
ಸ್ಥಿರ ಧ್ರುವ attribute_spec std_attributes[] =
{
  /* { name, min_len, max_len, decl_req, type_req, fn_type_req,
       affects_type_identity, handler, exclude } */
  { "_Noreturn", 0, 0, ಅಸತ್ಯ, ಅಸತ್ಯ, ಅಸತ್ಯ, ಅಸತ್ಯ,
    handle_std_noreturn_attribute, ರಿಕ್ತ },
  { "deprecated", 0, 1, ಅಸತ್ಯ, ಅಸತ್ಯ, ಅಸತ್ಯ, ಅಸತ್ಯ,
    handle_deprecated_attribute, ರಿಕ್ತ },
  { "fallthrough", 0, 0, ಅಸತ್ಯ, ಅಸತ್ಯ, ಅಸತ್ಯ, ಅಸತ್ಯ,
    handle_fallthrough_attribute, ರಿಕ್ತ },
  { "maybe_unused", 0, 0, ಅಸತ್ಯ, ಅಸತ್ಯ, ಅಸತ್ಯ, ಅಸತ್ಯ,
    handle_unused_attribute, ರಿಕ್ತ },
  { "nodiscard", 0, 1, ಅಸತ್ಯ, ಅಸತ್ಯ, ಅಸತ್ಯ, ಅಸತ್ಯ,
    handle_nodiscard_attribute, ರಿಕ್ತ },
  { "noreturn", 0, 0, ಅಸತ್ಯ, ಅಸತ್ಯ, ಅಸತ್ಯ, ಅಸತ್ಯ,
    handle_std_noreturn_attribute, ರಿಕ್ತ },
  { "reproducible", 0, 0, ಅಸತ್ಯ, ಸತ್ಯ, ಸತ್ಯ, ಅಸತ್ಯ,
    handle_std_reproducible_attribute, ರಿಕ್ತ },
  { "unsequenced", 0, 0, ಅಸತ್ಯ, ಸತ್ಯ, ಸತ್ಯ, ಅಸತ್ಯ,
    handle_std_unsequenced_attribute, ರಿಕ್ತ }
};

ಧ್ರುವ scoped_attribute_specs std_attribute_table =
{
  nullptr, { std_attributes }
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
  record_builtin_type (RID_MAX, "typeof (nullptr)", nullptr_type_ಗಂಟು);
  /* The size and alignment of nullptr_t is the same as for a pointer to
     character type.  */
  SET_TYPE_ALIGN (nullptr_type_ಗಂಟು, GET_MODE_ALIGNMENT (ptr_mode));

  ಒಳಹರಿವು_location = save_loc;

  make_fname_decl = c_make_fname_decl;
  start_fname_decls ();

  ಯದಿ (warn_keyword_macro)
    {
      ಪ್ರತಿ (unsigned ಪೂರ್ಣಾಙ್ಕ i = 0; i < ಅಂಕೆ_c_common_reswords; ++i)
	/* For C register keywords which don't start with underscore
	   or start with just single underscore.  Don't complain about
	   ObjC or Transactional Memory keywords.  */
	ಯದಿ (c_common_reswords[i].word[0] == '_'
	    && c_common_reswords[i].word[1] == '_')
	  ಅನುವರ್ತ;
	ಅನ್ಯಥಾ ಯದಿ (c_common_reswords[i].disable
		 & (D_TRANSMEM | D_OBJC | D_CXX_OBJC))
	  ಅನುವರ್ತ;
	ಅನ್ಯಥಾ
	  {
	    ವೃಕ್ಷ id = get_identifier (c_common_reswords[i].word);
	    ಯದಿ (C_IS_RESERVED_WORD (id)
		&& C_RID_CODE (id) != RID_CXX_COMPAT_WARN)
	      cpp_warn (parse_in, IDENTIFIER_POINTER (id),
			IDENTIFIER_LENGTH (id));
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
c_make_fname_decl (location_t loc, ವೃಕ್ಷ id, ಪೂರ್ಣಾಙ್ಕ type_dep)
{
  ಧ್ರುವ ವರ್ಣ *name = fname_as_string (type_dep);
  ವೃಕ್ಷ decl, type, init;
  size_t length = strlen (name);

  type = c_build_array_type (char_type_ಗಂಟು,
			     build_index_type (size_int (length)));
  type = c_build_qualified_type (type, TYPE_QUAL_CONST);

  decl = build_decl (loc, VAR_DECL, id, type);

  ವೃಕ್ಷ_STATIC (decl) = 1;
  ವೃಕ್ಷ_READONLY (decl) = 1;
  DECL_ARTIFICIAL (decl) = 1;

  init = build_string (length + 1, name);
  ಮುಕ್ತ (const_cast<ವರ್ಣ *> (name));
  ವೃಕ್ಷ_TYPE (init) = type;
  DECL_INITIAL (decl) = init;

  ವೃಕ್ಷ_USED (decl) = 1;

  ಯದಿ (current_function_decl
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
	    /*invisible=*/ಅಸತ್ಯ, /*nested=*/ಅಸತ್ಯ, UNKNOWN_LOCATION);
    }

  finish_decl (decl, loc, init, NULL_ವೃಕ್ಷ, NULL_ವೃಕ್ಷ);

  ಪ್ರತ್ಯಾಗಮ decl;
}

ವೃಕ್ಷ
c_builtin_function (ವೃಕ್ಷ decl)
{
  ವೃಕ್ಷ type = ವೃಕ್ಷ_TYPE (decl);
  ವೃಕ್ಷ   id = DECL_NAME (decl);

  ಧ್ರುವ ವರ್ಣ *name = IDENTIFIER_POINTER (id);
  C_DECL_BUILTIN_PROTOTYPE (decl) = prototype_p (type);

  /* Should never be called on a symbol with a preexisting meaning.  */
  gcc_assert (!I_ಚಿಹ್ನೆ_BINDING (id));

  bind (id, decl, external_scope, /*invisible=*/ಸತ್ಯ, /*nested=*/ಅಸತ್ಯ,
	UNKNOWN_LOCATION);

  /* Builtins in the implementation namespace are made visible without
     needing to be explicitly declared.  See push_file_scope.  */
  ಯದಿ (name[0] == '_' && (name[1] == '_' || ISUPPER (name[1])))
    {
      DECL_CHAIN (decl) = visible_builtins;
      visible_builtins = decl;
    }

  ಪ್ರತ್ಯಾಗಮ decl;
}

ವೃಕ್ಷ
c_builtin_function_ext_scope (ವೃಕ್ಷ decl)
{
  ವೃಕ್ಷ type = ವೃಕ್ಷ_TYPE (decl);
  ವೃಕ್ಷ   id = DECL_NAME (decl);

  ಧ್ರುವ ವರ್ಣ *name = IDENTIFIER_POINTER (id);
  C_DECL_BUILTIN_PROTOTYPE (decl) = prototype_p (type);

  ಯದಿ (external_scope)
    bind (id, decl, external_scope, /*invisible=*/ಅಸತ್ಯ, /*nested=*/ಅಸತ್ಯ,
	  UNKNOWN_LOCATION);

  /* Builtins in the implementation namespace are made visible without
     needing to be explicitly declared.  See push_file_scope.  */
  ಯದಿ (name[0] == '_' && (name[1] == '_' || ISUPPER (name[1])))
    {
      DECL_CHAIN (decl) = visible_builtins;
      visible_builtins = decl;
    }

  ಪ್ರತ್ಯಾಗಮ decl;
}

/* Implement LANG_HOOKS_SIMULATE_BUILTIN_FUNCTION_DECL.  */

ವೃಕ್ಷ
c_simulate_builtin_function_decl (ವೃಕ್ಷ decl)
{
  ವೃಕ್ಷ type = ವೃಕ್ಷ_TYPE (decl);
  C_DECL_BUILTIN_PROTOTYPE (decl) = prototype_p (type);
  ಪ್ರತ್ಯಾಗಮ pushdecl (decl);
}

/* Warn about attributes in a context where they are unused
   (attribute-declarations, except for the "fallthrough" case, and
   attributes on statements).  */

ಶೂನ್ಯ
c_warn_unused_attributes (ವೃಕ್ಷ attrs)
{
  ಪ್ರತಿ (ವೃಕ್ಷ t = attrs; t != NULL_ವೃಕ್ಷ; t = ವೃಕ್ಷ_CHAIN (t))
    ಯದಿ (get_attribute_namespace (t) == NULL_ವೃಕ್ಷ)
      /* The specifications of standard attributes mean this is a
	 constraint violation.  */
      pedwarn (ಒಳಹರಿವು_location, OPT_Wattributes, "%qE attribute ignored",
	       get_attribute_name (t));
    ಅನ್ಯಥಾ ಯದಿ (!attribute_ignored_p (t))
      warning (OPT_Wattributes, "%qE attribute ignored",
	       get_attribute_name (t));
}

/* Warn for standard attributes being applied to a type that is not
   being defined, where that is a constraint violation, and return a
   list of attributes with them removed.  */

ವೃಕ್ಷ
c_warn_type_attributes (ವೃಕ್ಷ type, ವೃಕ್ಷ attrs)
{
  ವೃಕ್ಷ *attr_ptr = &attrs;
  ಯಾವತ್ (*attr_ptr)
    ಯದಿ (get_attribute_namespace (*attr_ptr) == NULL_ವೃಕ್ಷ)
      {
	ಯದಿ (ವೃಕ್ಷ_CODE (type) == FUNCTION_TYPE)
	  {
	    ವೃಕ್ಷ name = get_attribute_name (*attr_ptr);
	    /* [[unsequenced]] and [[reproducible]] is fine on function
	       types that aren't being defined.  */
	    ಯದಿ (is_attribute_p ("unsequenced", name)
		|| is_attribute_p ("reproducible", name))
	      {
		attr_ptr = &ವೃಕ್ಷ_CHAIN (*attr_ptr);
		ಅನುವರ್ತ;
	      }
	  }
	pedwarn (ಒಳಹರಿವು_location, OPT_Wattributes, "%qE attribute ignored",
		 get_attribute_name (*attr_ptr));
	*attr_ptr = ವೃಕ್ಷ_CHAIN (*attr_ptr);
      }
    ಅನ್ಯಥಾ
      attr_ptr = &ವೃಕ್ಷ_CHAIN (*attr_ptr);
  ಪ್ರತ್ಯಾಗಮ attrs;
}

/* Called when a declaration is seen that contains no names to declare.
   If its type is a reference to a structure, union or enum inherited
   from a containing scope, shadow that tag name for the current scope
   with a forward reference.
   If its type defines a new named structure or union
   or defines an enum, it is valid but we need not do anything here.
   Otherwise, it is an error.  */

ಶೂನ್ಯ
shadow_tag (ಧ್ರುವ ಸಂರಚನಾ c_declspecs *declspecs)
{
  shadow_tag_warned (declspecs, 0);
}

/* WARNED is 1 if we have done a pedwarn, 2 if we have done a warning,
   but no pedwarn.  */
ಶೂನ್ಯ
shadow_tag_warned (ಧ್ರುವ ಸಂರಚನಾ c_declspecs *declspecs, ಪೂರ್ಣಾಙ್ಕ warned)
{
  ತಾರ್ಕಿಕ found_tag = ಅಸತ್ಯ;

  ಯದಿ (declspecs->type && !declspecs->default_int_p && !declspecs->typedef_p)
    {
      ವೃಕ್ಷ ಮೌಲ್ಯ = declspecs->type;
      ಗಣನಾ ವೃಕ್ಷ_code code = ವೃಕ್ಷ_CODE (ಮೌಲ್ಯ);

      ಯದಿ (code == RECORD_TYPE || code == UNION_TYPE || code == ENUMERAL_TYPE)
	/* Used to test also that TYPE_SIZE (value) != 0.
	   That caused warning for `struct foo;' at top level in the file.  */
	{
	  ವೃಕ್ಷ name = TYPE_NAME (ಮೌಲ್ಯ);
	  ವೃಕ್ಷ t;

	  found_tag = ಸತ್ಯ;

	  ಯದಿ (declspecs->restrict_p)
	    {
	      error ("invalid use of %<restrict%>");
	      warned = 1;
	    }

	  ಯದಿ (in_underspecified_init)
	    {
	      /* This can only occur with extensions such as statement
		 expressions, but is still appropriate as an error to
		 avoid types declared in such a context escaping to
		 the type of an auto variable.  */
	      error ("%qT declared in underspecified object initializer",
		     ಮೌಲ್ಯ);
	      warned = 1;
	    }

	  ಯದಿ (name == NULL_ವೃಕ್ಷ)
	    {
	      ಯದಿ (warned != 1 && code != ENUMERAL_TYPE)
		/* Empty unnamed enum OK */
		{
		  pedwarn (ಒಳಹರಿವು_location, 0,
			   "unnamed struct/union that defines no instances");
		  warned = 1;
		}
	    }
	  ಅನ್ಯಥಾ ಯದಿ (declspecs->typespec_kind != ctsk_tagdef
                   && declspecs->typespec_kind != ctsk_tagfirstref
		   && declspecs->typespec_kind != ctsk_tagfirstref_attrs
		   && declspecs->storage_class != csc_none)
	    {
	      ಯದಿ (warned != 1)
		pedwarn (ಒಳಹರಿವು_location, 0,
			 "empty declaration with storage class specifier "
			 "does not redeclare tag");
	      warned = 1;
	      pending_xref_error ();
	    }
	  ಅನ್ಯಥಾ ಯದಿ (declspecs->typespec_kind != ctsk_tagdef
                   && declspecs->typespec_kind != ctsk_tagfirstref
                   && declspecs->typespec_kind != ctsk_tagfirstref_attrs
		   && (declspecs->const_p
		       || declspecs->volatile_p
		       || declspecs->atomic_p
		       || declspecs->restrict_p
		       || declspecs->address_space))
	    {
	      ಯದಿ (warned != 1)
		pedwarn (ಒಳಹರಿವು_location, 0,
			 "empty declaration with type qualifier "
			  "does not redeclare tag");
	      warned = 1;
	      pending_xref_error ();
	    }
	  ಅನ್ಯಥಾ ಯದಿ (declspecs->typespec_kind != ctsk_tagdef
                   && declspecs->typespec_kind != ctsk_tagfirstref
                   && declspecs->typespec_kind != ctsk_tagfirstref_attrs
		   && declspecs->alignas_p)
	    {
	      ಯದಿ (warned != 1)
		pedwarn (ಒಳಹರಿವು_location, 0,
			 "empty declaration with %<_Alignas%> "
			  "does not redeclare tag");
	      warned = 1;
	      pending_xref_error ();
	    }
	  ಅನ್ಯಥಾ ಯದಿ (declspecs->typespec_kind != ctsk_tagdef
		   && declspecs->typespec_kind != ctsk_tagfirstref
		   && declspecs->typespec_kind != ctsk_tagfirstref_attrs
		   && code == ENUMERAL_TYPE
		   && !declspecs->enum_type_specifier_ref_p)
	    {
	      ತಾರ್ಕಿಕ warned_enum = ಅಸತ್ಯ;
	      ಯದಿ (warned != 1)
		warned_enum = pedwarn (ಒಳಹರಿವು_location, OPT_Wpedantic,
				       "empty declaration of %<enum%> type "
				       "does not redeclare tag");
	      ಯದಿ (warned_enum)
		warned = 1;
	      pending_xref_error ();
	    }
	  ಅನ್ಯಥಾ
	    {
	      pending_invalid_xref = NULL_ವೃಕ್ಷ;
	      t = lookup_tag (code, name, ಸತ್ಯ, ರಿಕ್ತ);

	      ಯದಿ (t == NULL_ವೃಕ್ಷ)
		{
		  t = make_ಗಂಟು (code);
		  ಯದಿ (flag_isoc23 || code == ENUMERAL_TYPE)
		    SET_TYPE_STRUCTURAL_EQUALITY (t);
		  pushtag (ಒಳಹರಿವು_location, name, t);
		}
	    }
	}
      ಅನ್ಯಥಾ
	{
	  ಯದಿ (warned != 1 && !in_system_header_at (ಒಳಹರಿವು_location))
	    {
	      pedwarn (ಒಳಹರಿವು_location, 0,
		       "useless type name in empty declaration");
	      warned = 1;
	    }
	}
    }
  ಅನ್ಯಥಾ ಯದಿ (warned != 1 && !in_system_header_at (ಒಳಹರಿವು_location)
	   && declspecs->typedef_p)
    {
      pedwarn (ಒಳಹರಿವು_location, 0, "useless type name in empty declaration");
      warned = 1;
    }

  pending_invalid_xref = NULL_ವೃಕ್ಷ;

  ಯದಿ (declspecs->inline_p)
    {
      error ("%<inline%> in empty declaration");
      warned = 1;
    }

  ಯದಿ (declspecs->noreturn_p)
    {
      error ("%<_Noreturn%> in empty declaration");
      warned = 1;
    }

  ಯದಿ (declspecs->constexpr_p)
    {
      error ("%<constexpr%> in empty declaration");
      warned = 1;
    }

  ಯದಿ (current_scope == file_scope && declspecs->storage_class == csc_auto)
    {
      error ("%<auto%> in file-scope empty declaration");
      warned = 1;
    }

  ಯದಿ (current_scope == file_scope && declspecs->storage_class == csc_register)
    {
      error ("%<register%> in file-scope empty declaration");
      warned = 1;
    }

  ಯದಿ (declspecs->enum_type_specifier_ref_p && !warned)
    {
      ಯದಿ (declspecs->storage_class != csc_none)
	{
	  error ("storage class specifier in empty declaration with %<enum%> "
		 "underlying type");
	  warned = 1;
	}
      ಅನ್ಯಥಾ ಯದಿ (declspecs->thread_p)
	{
	  error ("%qs in empty declaration with %<enum%> underlying type",
		 declspecs->thread_gnu_p ? "__thread" : "_Thread_local");
	  warned = 1;
	}
      ಅನ್ಯಥಾ ಯದಿ (declspecs->const_p
	       || declspecs->volatile_p
	       || declspecs->atomic_p
	       || declspecs->restrict_p
	       || declspecs->address_space)
	{
	  error ("type qualifier in empty declaration with %<enum%> "
		 "underlying type");
	  warned = 1;
	}
      ಅನ್ಯಥಾ ಯದಿ (declspecs->alignas_p)
	{
	  error ("%<alignas%> in empty declaration with %<enum%> "
		 "underlying type");
	  warned = 1;
	}
    }

  ಯದಿ (!warned && !in_system_header_at (ಒಳಹರಿವು_location)
      && declspecs->storage_class != csc_none)
    {
      warning (0, "useless storage class specifier in empty declaration");
      warned = 2;
    }

  ಯದಿ (!warned && !in_system_header_at (ಒಳಹರಿವು_location) && declspecs->thread_p)
    {
      warning (0, "useless %qs in empty declaration",
	       declspecs->thread_gnu_p ? "__thread" : "_Thread_local");
      warned = 2;
    }

  ಯದಿ (!warned
      && !in_system_header_at (ಒಳಹರಿವು_location)
      && (declspecs->const_p
	  || declspecs->volatile_p
	  || declspecs->atomic_p
	  || declspecs->restrict_p
	  || declspecs->address_space))
    {
      warning (0, "useless type qualifier in empty declaration");
      warned = 2;
    }

  ಯದಿ (!warned && !in_system_header_at (ಒಳಹರಿವು_location)
      && declspecs->alignas_p)
    {
      warning (0, "useless %<_Alignas%> in empty declaration");
      warned = 2;
    }

  ಯದಿ (found_tag
      && warned == 2
      && (declspecs->typespec_kind == ctsk_tagref_attrs
	  || declspecs->typespec_kind == ctsk_tagfirstref_attrs))
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

  ಯದಿ (warned != 1)
    {
      ಯದಿ (declspecs->declspecs_seen_p
	  && !declspecs->non_std_attrs_seen_p)
	/* An attribute declaration (but not a fallthrough attribute
	   declaration, which was handled separately); warn if there
	   are any attributes being ignored (but not if the attributes
	   were empty).  */
	c_warn_unused_attributes (declspecs->attrs);
      ಅನ್ಯಥಾ ಯದಿ (!found_tag)
	pedwarn (ಒಳಹರಿವು_location, 0, "empty declaration");
    }
}


/* Return the qualifiers from SPECS as a bitwise OR of TYPE_QUAL_*
   bits.  SPECS represents declaration specifiers that the grammar
   only permits to contain type qualifiers and attributes.  */

ಪೂರ್ಣಾಙ್ಕ
quals_from_declspecs (ಧ್ರುವ ಸಂರಚನಾ c_declspecs *specs)
{
  ಪೂರ್ಣಾಙ್ಕ quals = ((specs->const_p ? TYPE_QUAL_CONST : 0)
	       | (specs->volatile_p ? TYPE_QUAL_VOLATILE : 0)
	       | (specs->restrict_p ? TYPE_QUAL_RESTRICT : 0)
	       | (specs->atomic_p ? TYPE_QUAL_ATOMIC : 0)
	       | (ENCODE_QUAL_ADDR_SPACE (specs->address_space)));
  gcc_assert (!specs->type
	      && !specs->decl_attr
	      && specs->typespec_word == cts_none
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
  ಪ್ರತ್ಯಾಗಮ quals;
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

ಸಂರಚನಾ c_declarator *
build_array_declarator (location_t loc,
			ವೃಕ್ಷ ಅಭಿವ್ಯಕ್ತಿ, ಸಂರಚನಾ c_declspecs *quals, ತಾರ್ಕಿಕ static_p,
			ತಾರ್ಕಿಕ vla_unspec_p)
{
  ಸಂರಚನಾ c_declarator *declarator = XOBNEW (&parser_obstack,
					    ಸಂರಚನಾ c_declarator);
  declarator->id_loc = loc;
  declarator->kind = cdk_array;
  declarator->declarator = 0;
  declarator->u.array.dimen = ಅಭಿವ್ಯಕ್ತಿ;
  ಯದಿ (quals)
    {
      declarator->u.array.attrs = quals->attrs;
      declarator->u.array.quals = quals_from_declspecs (quals);
    }
  ಅನ್ಯಥಾ
    {
      declarator->u.array.attrs = NULL_ವೃಕ್ಷ;
      declarator->u.array.quals = 0;
    }
  declarator->u.array.static_p = static_p;
  declarator->u.array.vla_unspec_p = vla_unspec_p;
  ಯದಿ (static_p || quals != ರಿಕ್ತ)
    pedwarn_c90 (loc, OPT_Wpedantic,
		 "ISO C90 does not support %<static%> or type "
		 "qualifiers in parameter array declarators");
  ಯದಿ (vla_unspec_p)
    {
      pedwarn_c90 (loc, OPT_Wpedantic,
		   "ISO C90 does not support %<[*]%> array declarators");
      ಯದಿ (current_scope->parm_flag)
	current_scope->had_vla_unspec = ಸತ್ಯ;
    }
  ಪ್ರತ್ಯಾಗಮ declarator;
}

/* Set the contained declarator of an array declarator.  DECL is the
   declarator, as constructed by build_array_declarator; INNER is what
   appears on the left of the [].  */

ಸಂರಚನಾ c_declarator *
set_array_declarator_inner (ಸಂರಚನಾ c_declarator *decl,
			    ಸಂರಚನಾ c_declarator *inner)
{
  decl->declarator = inner;
  ಪ್ರತ್ಯಾಗಮ decl;
}

/* Determine whether TYPE is a one-element array type "[1]".  */
ಸ್ಥಿರ ತಾರ್ಕಿಕ
one_element_array_type_p (const_ವೃಕ್ಷ type)
{
  ಯದಿ (ವೃಕ್ಷ_CODE (type) != ARRAY_TYPE)
    ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
  ಪ್ರತ್ಯಾಗಮ integer_zerop (array_type_nelts_minus_one (type));
}

/* Determine whether TYPE is a zero-length array type "[0]".  */
ತಾರ್ಕಿಕ
zero_length_array_type_p (const_ವೃಕ್ಷ type)
{
  ಯದಿ (ವೃಕ್ಷ_CODE (type) == ARRAY_TYPE
      && COMPLETE_TYPE_P (type)
      && TYPE_DOMAIN (type) != NULL_ವೃಕ್ಷ
      && (TYPE_MAX_ಮೌಲ್ಯ (TYPE_DOMAIN (type)) == NULL_ವೃಕ್ಷ
	  || integer_all_onesp (TYPE_MAX_ಮೌಲ್ಯ (TYPE_DOMAIN (type)))))
    ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
  ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
}

/* INIT is a constructor that forms DECL's initializer.  If the final
   element initializes a flexible array field, adjust the size of the
   DECL with the initializer based on whether the DECL is a union or
   a structure.  */

ಸ್ಥಿರ ಶೂನ್ಯ
add_flexible_array_elts_to_size (ವೃಕ್ಷ decl, ವೃಕ್ಷ init)
{
  ವೃಕ್ಷ elt, type;

  ಯದಿ (vec_safe_is_empty (CONSTRUCTOR_ELTS (init)))
    ಪ್ರತ್ಯಾಗಮ;

  elt = CONSTRUCTOR_ELTS (init)->last ().ಮೌಲ್ಯ;
  type = ವೃಕ್ಷ_TYPE (elt);
  ಯದಿ (flexible_array_member_type_p (type))
    {
      complete_array_type (&type, elt, ಅಸತ್ಯ);
      /* For a structure, add the size of the initializer to the DECL's
	 size.  */
      ಯದಿ (ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (decl)) == RECORD_TYPE)
	{
	  DECL_SIZE (decl)
	    = size_binop (PLUS_ಅಭಿವ್ಯಕ್ತಿ, DECL_SIZE (decl), TYPE_SIZE (type));
	  DECL_SIZE_UNIT (decl)
	    = size_binop (PLUS_ಅಭಿವ್ಯಕ್ತಿ, DECL_SIZE_UNIT (decl),
			  TYPE_SIZE_UNIT (type));
	}
      /* For a union, the DECL's size is the maximum of the current size
	 and the size of the initializer.  */
      ಅನ್ಯಥಾ
	{
	  DECL_SIZE (decl)
	    = size_binop (MAX_ಅಭಿವ್ಯಕ್ತಿ, DECL_SIZE (decl), TYPE_SIZE (type));
	  DECL_SIZE_UNIT (decl)
	    = size_binop (MAX_ಅಭಿವ್ಯಕ್ತಿ, DECL_SIZE_UNIT (decl),
			  TYPE_SIZE_UNIT (type));
	}
    }
}

/* Decode a "typename", such as "int **", returning a ..._TYPE node.
   Set *EXPR, if EXPR not NULL, to any expression to be evaluated
   before the type name, and set *EXPR_CONST_OPERANDS, if
   EXPR_CONST_OPERANDS not NULL, to indicate whether the type name may
   appear in a constant expression.  */

ವೃಕ್ಷ
groktypename (ಸಂರಚನಾ c_type_name *type_name, ವೃಕ್ಷ *ಅಭಿವ್ಯಕ್ತಿ,
	      ತಾರ್ಕಿಕ *ಅಭಿವ್ಯಕ್ತಿ_const_operands)
{
  ವೃಕ್ಷ type;
  ವೃಕ್ಷ attrs = type_name->specs->attrs;

  type_name->specs->attrs = NULL_ವೃಕ್ಷ;

  type = grokdeclarator (type_name->declarator, type_name->specs, TYPENAME,
			 ಅಸತ್ಯ, ರಿಕ್ತ, &attrs, ಅಭಿವ್ಯಕ್ತಿ, ಅಭಿವ್ಯಕ್ತಿ_const_operands,
			 DEPRECATED_NORMAL);

  /* Apply attributes.  */
  attrs = c_warn_type_attributes (type, attrs);
  decl_attributes (&type, attrs, 0);

  ಪ್ರತ್ಯಾಗಮ type;
}


/* Decode a "typename", such as "int **", returning a ..._TYPE node,
   as for groktypename but setting the context to GENERIC_ASSOC.  */

ವೃಕ್ಷ
grokgenassoc (ಸಂರಚನಾ c_type_name *type_name)
{
  ವೃಕ್ಷ type;
  ವೃಕ್ಷ attrs = type_name->specs->attrs;

  type_name->specs->attrs = NULL_ವೃಕ್ಷ;

  type = grokdeclarator (type_name->declarator, type_name->specs, GENERIC_ASSOC,
			 ಅಸತ್ಯ, ರಿಕ್ತ, &attrs, ರಿಕ್ತ, ರಿಕ್ತ, DEPRECATED_NORMAL);

  /* Apply attributes.  */
  attrs = c_warn_type_attributes (type, attrs);
  decl_attributes (&type, attrs, 0);

  ಪ್ರತ್ಯಾಗಮ type;
}


/* Looks up the most recent pushed declaration corresponding to DECL.  */

ಸ್ಥಿರ ವೃಕ್ಷ
lookup_last_decl (ವೃಕ್ಷ decl)
{
  ವೃಕ್ಷ last_decl = lookup_name (DECL_NAME (decl));
  ಯದಿ (!last_decl)
    last_decl = lookup_name_in_scope (DECL_NAME (decl), external_scope);
  ಪ್ರತ್ಯಾಗಮ last_decl;
}

/* Wrapper for decl_attributes that adds some implicit attributes
   to VAR_DECLs or FUNCTION_DECLs.  */

ಸ್ಥಿರ ವೃಕ್ಷ
c_decl_attributes (ವೃಕ್ಷ *ಗಂಟು, ವೃಕ್ಷ attributes, ಪೂರ್ಣಾಙ್ಕ flags)
{
  /* Add implicit "omp declare target" attribute if requested.  */
  ಯದಿ (vec_safe_length (current_omp_declare_target_attribute)
      && ((VAR_P (*ಗಂಟು) && is_global_var (*ಗಂಟು))
	  || ವೃಕ್ಷ_CODE (*ಗಂಟು) == FUNCTION_DECL))
    {
      ಯದಿ (VAR_P (*ಗಂಟು) && !omp_mappable_type (ವೃಕ್ಷ_TYPE (*ಗಂಟು)))
	attributes = ವೃಕ್ಷ_cons (get_identifier ("omp declare target implicit"),
				NULL_ವೃಕ್ಷ, attributes);
      ಅನ್ಯಥಾ
	attributes = ವೃಕ್ಷ_cons (get_identifier ("omp declare target"),
				NULL_ವೃಕ್ಷ, attributes);
      ಯದಿ (ವೃಕ್ಷ_CODE (*ಗಂಟು) == FUNCTION_DECL)
	{
	  ಪೂರ್ಣಾಙ್ಕ device_type
	    = current_omp_declare_target_attribute->last ().device_type;
	  device_type = MAX (device_type, 0);
	  ಯದಿ ((device_type & OMP_CLAUSE_DEVICE_TYPE_HOST) != 0
	      && !lookup_attribute ("omp declare target host", attributes))
	    attributes
	      = ವೃಕ್ಷ_cons (get_identifier ("omp declare target host"),
			   NULL_ವೃಕ್ಷ, attributes);
	  ಯದಿ ((device_type & OMP_CLAUSE_DEVICE_TYPE_NOHOST) != 0
	      && !lookup_attribute ("omp declare target nohost", attributes))
	    attributes
	      = ವೃಕ್ಷ_cons (get_identifier ("omp declare target nohost"),
			   NULL_ವೃಕ್ಷ, attributes);

	  ಪೂರ್ಣಾಙ್ಕ indirect
	    = current_omp_declare_target_attribute->last ().indirect;
	  ಯದಿ (indirect && !lookup_attribute ("omp declare target indirect",
					     attributes))
	    attributes
	      = ವೃಕ್ಷ_cons (get_identifier ("omp declare target indirect"),
			   NULL_ವೃಕ್ಷ, attributes);
	}
    }

  ಯದಿ (flag_openmp || flag_openmp_simd)
    {
      ತಾರ್ಕಿಕ diagnosed = ಅಸತ್ಯ;
      ಪ್ರತಿ (ವೃಕ್ಷ *pa = &attributes; *pa; )
	{
	  ಯದಿ (is_attribute_namespace_p ("omp", *pa))
	    {
	      ವೃಕ್ಷ name = get_attribute_name (*pa);
	      ಯದಿ (is_attribute_p ("directive", name)
		  || is_attribute_p ("sequence", name)
		  || is_attribute_p ("decl", name))
		{
		  ಧ್ರುವ ವರ್ಣ *p = ರಿಕ್ತ;
		  ಯದಿ (ವೃಕ್ಷ_ಮೌಲ್ಯ (*pa) == NULL_ವೃಕ್ಷ)
		    p = IDENTIFIER_POINTER (name);
		  ಪ್ರತಿ (ವೃಕ್ಷ a = ವೃಕ್ಷ_ಮೌಲ್ಯ (*pa); a; a = ವೃಕ್ಷ_CHAIN (a))
		    {
		      ವೃಕ್ಷ d = ವೃಕ್ಷ_ಮೌಲ್ಯ (a);
		      gcc_assert (ವೃಕ್ಷ_CODE (d) == C_TOKEN_VEC);
		      ಯದಿ (ವೃಕ್ಷ_PUBLIC (d)
			  && (VAR_P (*ಗಂಟು)
			      || ವೃಕ್ಷ_CODE (*ಗಂಟು) == FUNCTION_DECL)
			  && c_maybe_parse_omp_decl (*ಗಂಟು, d))
			ಅನುವರ್ತ;
		      p = ವೃಕ್ಷ_PUBLIC (d) ? "decl" : "directive";
		    }
		  ಯದಿ (p && !diagnosed)
		    {
		      error ("%<omp::%s%> not allowed to be specified in "
			     "this context", p);
		      diagnosed = ಸತ್ಯ;
		    }
		  ಯದಿ (p)
		    {
		      *pa = ವೃಕ್ಷ_CHAIN (*pa);
		      ಅನುವರ್ತ;
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
  ವೃಕ್ಷ last_decl = lookup_last_decl (*ಗಂಟು);
  ಯದಿ (last_decl == error_mark_ಗಂಟು)
    last_decl = NULL_ವೃಕ್ಷ;
  ವೃಕ್ಷ attr = decl_attributes (ಗಂಟು, attributes, flags, last_decl);
  ಯದಿ (VAR_P (*ಗಂಟು) && DECL_THREAD_LOCAL_P (*ಗಂಟು))
    {
      // tls_model attribute can set a stronger TLS access model.
      tls_model model = DECL_TLS_MODEL (*ಗಂಟು);
      tls_model default_model = decl_default_tls_model (*ಗಂಟು);
      ಯದಿ (default_model > model)
	set_decl_tls_model (*ಗಂಟು, default_model);
    }
  ಪ್ರತ್ಯಾಗಮ attr;
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
start_decl (ಸಂರಚನಾ c_declarator *declarator, ಸಂರಚನಾ c_declspecs *declspecs,
	    ತಾರ್ಕಿಕ initialized, ವೃಕ್ಷ attributes, ತಾರ್ಕಿಕ do_ತಳ್ಳು /* = true */,
	    location_t *lastloc /* = NULL */)
{
  ವೃಕ್ಷ decl;
  ವೃಕ್ಷ old_decl;
  ವೃಕ್ಷ tem;
  ವೃಕ್ಷ ಅಭಿವ್ಯಕ್ತಿ = NULL_ವೃಕ್ಷ;
  ಗಣನಾ deprecated_states deprecated_state = DEPRECATED_NORMAL;

  /* An object declared as __attribute__((unavailable)) suppresses
     warnings and errors from __attribute__((deprecated/unavailable))
     components.
     An object declared as __attribute__((deprecated)) suppresses
     warnings of uses of other deprecated items.  */
  ಯದಿ (lookup_attribute ("unavailable", attributes))
    deprecated_state = UNAVAILABLE_DEPRECATED_SUPPRESS;
  ಅನ್ಯಥಾ ಯದಿ (lookup_attribute ("deprecated", attributes))
    deprecated_state = DEPRECATED_SUPPRESS;

  decl = grokdeclarator (declarator, declspecs,
			 NORMAL, initialized, ರಿಕ್ತ, &attributes, &ಅಭಿವ್ಯಕ್ತಿ, ರಿಕ್ತ,
			 deprecated_state);
  ಯದಿ (!decl || decl == error_mark_ಗಂಟು)
    ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;

  old_decl = lookup_last_decl (decl);

  ಯದಿ (ವೃಕ್ಷ lastdecl = lastloc ? old_decl : NULL_ವೃಕ್ಷ)
    ಯದಿ (lastdecl != error_mark_ಗಂಟು)
      *lastloc = DECL_SOURCE_LOCATION (lastdecl);

  /* Make sure the size expression is evaluated at this point.  */
  ಯದಿ (ಅಭಿವ್ಯಕ್ತಿ && !current_scope->parm_flag)
    add_stmt (fold_convert (void_type_ಗಂಟು, ಅಭಿವ್ಯಕ್ತಿ));

  ಯದಿ (ವೃಕ್ಷ_CODE (decl) != FUNCTION_DECL && MAIN_NAME_P (DECL_NAME (decl))
      && ವೃಕ್ಷ_PUBLIC (decl))
    warning (OPT_Wmain, "%q+D is usually a function", decl);

  ಯದಿ (warn_missing_variable_declarations && VAR_P (decl)
      && !DECL_EXTERNAL (decl) && ವೃಕ್ಷ_PUBLIC (decl) && old_decl == NULL_ವೃಕ್ಷ)
    warning_at (DECL_SOURCE_LOCATION (decl), OPT_Wmissing_variable_declarations,
		"no previous declaration for %qD", decl);

  ಯದಿ (initialized)
    /* Is it valid for this decl to have an initializer at all?
       If not, set INITIALIZED to zero, which will indirectly
       tell 'finish_decl' to ignore the initializer once it is parsed.  */
    ವಿಕಲ್ಪ (ವೃಕ್ಷ_CODE (decl))
      {
      ಪಕ್ಷ TYPE_DECL:
	error ("typedef %qD is initialized (use %<__typeof__%> instead)", decl);
	initialized = ಅಸತ್ಯ;
	ಭಙ್ಗ;

      ಪಕ್ಷ FUNCTION_DECL:
	error ("function %qD is initialized like a variable", decl);
	initialized = ಅಸತ್ಯ;
	ಭಙ್ಗ;

      ಪಕ್ಷ PARM_DECL:
	/* DECL_INITIAL in a PARM_DECL is really DECL_ARG_TYPE.  */
	error ("parameter %qD is initialized", decl);
	initialized = ಅಸತ್ಯ;
	ಭಙ್ಗ;

      ಸ್ವಭಾವ:
	/* Don't allow initializations for incomplete types except for
	   arrays which might be completed by the initialization.  */

	/* This can happen if the array size is an undefined macro.
	   We already gave a warning, so we don't need another one.  */
	ಯದಿ (ವೃಕ್ಷ_TYPE (decl) == error_mark_ಗಂಟು)
	  initialized = ಅಸತ್ಯ;
	ಅನ್ಯಥಾ ಯದಿ (COMPLETE_TYPE_P (ವೃಕ್ಷ_TYPE (decl)))
	  {
	    /* A complete type is ok if size is fixed.  If the size is
	       variable, an empty initializer is OK and nonempty
	       initializers will be diagnosed in the parser.  */
	  }
	ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (decl)) != ARRAY_TYPE)
	  {
	    error ("variable %qD has initializer but incomplete type", decl);
	    initialized = ಅಸತ್ಯ;
	  }
      }

  ಯದಿ (initialized)
    {
      ಯದಿ (current_scope == file_scope)
	ವೃಕ್ಷ_STATIC (decl) = 1;

      /* Tell 'pushdecl' this is an initialized decl
	 even though we don't yet have the initializer expression.
	 Also tell 'finish_decl' it may store the real initializer.  */
      DECL_INITIAL (decl) = error_mark_ಗಂಟು;
    }

  /* If this is a function declaration, write a record describing it to the
     prototypes file (if requested).  */

  ಯದಿ (ವೃಕ್ಷ_CODE (decl) == FUNCTION_DECL)
    gen_aux_info_record (decl, 0, 0, prototype_p (ವೃಕ್ಷ_TYPE (decl)));

  /* ANSI specifies that a tentative definition which is not merged with
     a non-tentative definition behaves exactly like a definition with an
     initializer equal to zero.  (Section 3.7.2)

     -fno-common gives strict ANSI behavior, though this tends to break
     a large body of code that grew up without this rule.

     Thread-local variables are never common, since there's no entrenched
     body of code to break, and it allows more efficient variable references
     in the presence of dynamic linking.  */

  ಯದಿ (VAR_P (decl)
      && !initialized
      && ವೃಕ್ಷ_PUBLIC (decl)
      && !DECL_THREAD_LOCAL_P (decl)
      && !flag_no_common)
    DECL_COMMON (decl) = 1;

  /* Set attributes here so if duplicate decl, will have proper attributes.  */
  c_decl_attributes (&decl, attributes, 0);

  /* Handle gnu_inline attribute.  */
  ಯದಿ (declspecs->inline_p
      && !flag_gnu89_inline
      && ವೃಕ್ಷ_CODE (decl) == FUNCTION_DECL
      && (lookup_attribute ("gnu_inline", DECL_ATTRIBUTES (decl))
	  || current_function_decl))
    {
      ಯದಿ (declspecs->storage_class == csc_auto && current_scope != file_scope)
	;
      ಅನ್ಯಥಾ ಯದಿ (declspecs->storage_class != csc_static)
	DECL_EXTERNAL (decl) = !DECL_EXTERNAL (decl);
    }

  ಯದಿ (ವೃಕ್ಷ_CODE (decl) == FUNCTION_DECL
      && DECL_DECLARED_INLINE_P (decl)
      && DECL_UNINLINABLE (decl)
      && lookup_attribute ("noinline", DECL_ATTRIBUTES (decl)))
    {
      auto_urlify_attributes sentinel;
      warning (OPT_Wattributes, "inline function %q+D given attribute %qs",
	       decl, "noinline");
    }

  /* C99 6.7.4p3: An inline definition of a function with external
     linkage shall not contain a definition of a modifiable object
     with static storage duration...  */
  ಯದಿ (VAR_P (decl)
      && current_scope != file_scope
      && ವೃಕ್ಷ_STATIC (decl)
      && !ವೃಕ್ಷ_READONLY (decl)
      && DECL_DECLARED_INLINE_P (current_function_decl)
      && DECL_EXTERNAL (current_function_decl))
    record_inline_static (ಒಳಹರಿವು_location, current_function_decl,
			  decl, csi_modifiable);

  ಯದಿ (c_dialect_objc ()
      && VAR_OR_FUNCTION_DECL_P (decl))
      objc_check_global_decl (decl);

  /* To enable versions to be created across TU's we mark and mangle all
     non-default versioned functions.  */
  ಯದಿ (ವೃಕ್ಷ_CODE (decl) == FUNCTION_DECL
      && !TARGET_HAS_FMV_TARGET_ATTRIBUTE
      && get_target_version (decl).is_valid ())
    {
      maybe_mark_function_versioned (decl);
      ಯದಿ (current_scope != file_scope)
	error ("versioned declarations are only allowed at file scope");
    }

  /* Add this decl to the current scope.
     TEM may equal DECL or it may be a previous decl of the same name.  */
  ಯದಿ (do_ತಳ್ಳು)
    {
      tem = pushdecl (decl);

      ಯದಿ (initialized && DECL_EXTERNAL (tem))
	{
	  DECL_EXTERNAL (tem) = 0;
	  ವೃಕ್ಷ_STATIC (tem) = 1;
	}

      ಪ್ರತ್ಯಾಗಮ tem;
    }
  ಅನ್ಯಥಾ
    ಪ್ರತ್ಯಾಗಮ decl;
}

/* Subroutine of finish_decl. TYPE is the type of an uninitialized object
   DECL or the non-array element type if DECL is an uninitialized array.
   If that type has a const member, diagnose this. */

ಸ್ಥಿರ ಶೂನ್ಯ
diagnose_uninitialized_cst_member (ವೃಕ್ಷ decl, ವೃಕ್ಷ type)
{
  ವೃಕ್ಷ field;
  ಪ್ರತಿ (field = TYPE_FIELDS (type); field; field = ವೃಕ್ಷ_CHAIN (field))
    {
      ವೃಕ್ಷ field_type;
      ಯದಿ (ವೃಕ್ಷ_CODE (field) != FIELD_DECL)
	ಅನುವರ್ತ;
      field_type = strip_array_types (ವೃಕ್ಷ_TYPE (field));

      ಯದಿ (TYPE_QUALS (field_type) & TYPE_QUAL_CONST)
      	{
	  auto_diagnostic_group d;
	  ಯದಿ (warning_at (DECL_SOURCE_LOCATION (decl), OPT_Wc___compat,
			  "uninitialized const member in %qT is invalid in C++",
			  strip_array_types (ವೃಕ್ಷ_TYPE (decl))))
	    inform (DECL_SOURCE_LOCATION (field), "%qD should be initialized", field);
	}

      ಯದಿ (RECORD_OR_UNION_TYPE_P (field_type))
	diagnose_uninitialized_cst_member (decl, field_type);
    }
}

/* Finish processing of a declaration;
   install its initial value.
   If ORIGTYPE is not NULL_TREE, it is the original type of INIT.
   If the length of an array type is not known before,
   it must be determined now, from the initial value, or it is an error.

   INIT_LOC is the location of the initial value.  */

ಶೂನ್ಯ
finish_decl (ವೃಕ್ಷ decl, location_t init_loc, ವೃಕ್ಷ init,
	     ವೃಕ್ಷ origtype, ವೃಕ್ಷ asmspec_ವೃಕ್ಷ)
{
  ವೃಕ್ಷ type;
  ತಾರ್ಕಿಕ was_incomplete = (DECL_SIZE (decl) == NULL_ವೃಕ್ಷ);
  ಧ್ರುವ ವರ್ಣ *asmspec = 0;

  /* If a name was specified, get the string.  */
  ಯದಿ (VAR_OR_FUNCTION_DECL_P (decl)
      && DECL_FILE_SCOPE_P (decl))
    asmspec_ವೃಕ್ಷ = maybe_apply_renaming_pragma (decl, asmspec_ವೃಕ್ಷ);
  ಯದಿ (asmspec_ವೃಕ್ಷ)
    asmspec = ವೃಕ್ಷ_STRING_POINTER (asmspec_ವೃಕ್ಷ);

  ಯದಿ (VAR_P (decl)
      && ವೃಕ್ಷ_STATIC (decl)
      && global_bindings_p ())
    /* So decl is a global variable. Record the types it uses
       so that we can decide later to emit debug info for them.  */
    record_types_used_by_current_var_decl (decl);

  /* If `start_decl' didn't like having an initialization, ignore it now.  */
  ಯದಿ (init != NULL_ವೃಕ್ಷ && DECL_INITIAL (decl) == NULL_ವೃಕ್ಷ)
    init = NULL_ವೃಕ್ಷ;

  /* Don't crash if parm is initialized.  */
  ಯದಿ (ವೃಕ್ಷ_CODE (decl) == PARM_DECL)
    init = NULL_ವೃಕ್ಷ;

  ಯದಿ (init)
    store_init_ಮೌಲ್ಯ (init_loc, decl, init, origtype);

  ಯದಿ (c_dialect_objc () && (VAR_OR_FUNCTION_DECL_P (decl)
			    || ವೃಕ್ಷ_CODE (decl) == FIELD_DECL))
    objc_check_decl (decl);

  type = ವೃಕ್ಷ_TYPE (decl);

  /* Deduce size of array from initialization, if not already known.
     This is only needed for an initialization in the current scope;
     it must not be done for a file-scope initialization of a
     declaration with external linkage, redeclared in an inner scope
     with the outer declaration shadowed in an intermediate scope.  */
  ಯದಿ (ವೃಕ್ಷ_CODE (type) == ARRAY_TYPE
      && TYPE_DOMAIN (type) == NULL_ವೃಕ್ಷ
      && ವೃಕ್ಷ_CODE (decl) != TYPE_DECL
      && !(ವೃಕ್ಷ_PUBLIC (decl) && current_scope != file_scope))
    {
      ತಾರ್ಕಿಕ do_default
	= !ವೃಕ್ಷ_STATIC (decl) && !DECL_EXTERNAL (decl);
      ಪೂರ್ಣಾಙ್ಕ failure
	= complete_array_type (&ವೃಕ್ಷ_TYPE (decl), DECL_INITIAL (decl),
			       do_default);

      /* Get the completed type made by complete_array_type.  */
      type = ವೃಕ್ಷ_TYPE (decl);

      ವಿಕಲ್ಪ (failure)
	{
	ಪಕ್ಷ 1:
	  error ("initializer fails to determine size of %q+D", decl);
	  ಭಙ್ಗ;

	ಪಕ್ಷ 2:
	  ಯದಿ (do_default)
	    error ("array size missing in %q+D", decl);
	  ಅನ್ಯಥಾ ಯದಿ (!ವೃಕ್ಷ_PUBLIC (decl))
	    pedwarn_c23 (DECL_SOURCE_LOCATION (decl), OPT_Wpedantic,
			 "array size missing in %q+D", decl);
	  ಭಙ್ಗ;

	ಪಕ್ಷ 3:
	  error ("zero or negative size array %q+D", decl);
	  ಭಙ್ಗ;

	ಪಕ್ಷ 0:
	  /* For global variables, update the copy of the type that
	     exists in the binding.  */
	  ಯದಿ (ವೃಕ್ಷ_PUBLIC (decl))
	    {
	      ಸಂರಚನಾ c_binding *b_ext = I_ಚಿಹ್ನೆ_BINDING (DECL_NAME (decl));
	      ಯಾವತ್ (b_ext && !B_IN_EXTERNAL_SCOPE (b_ext))
		b_ext = b_ext->shadowed;
	      ಯದಿ (b_ext && ವೃಕ್ಷ_CODE (decl) == ವೃಕ್ಷ_CODE (b_ext->decl))
		{
		  ಯದಿ (b_ext->u.type && comptypes (b_ext->u.type, type))
		    b_ext->u.type = composite_type (b_ext->u.type, type);
		  ಅನ್ಯಥಾ
		    b_ext->u.type = type;
		}
	    }
	  ಭಙ್ಗ;

	ಸ್ವಭಾವ:
	  gcc_unreachable ();
	}

      ಯದಿ (DECL_INITIAL (decl) && DECL_INITIAL (decl) != error_mark_ಗಂಟು)
	ವೃಕ್ಷ_TYPE (DECL_INITIAL (decl)) = type;

      relayout_decl (decl);
    }

  /* Look for braced array initializers for character arrays and
     recursively convert them into STRING_CSTs.  */
  ಯದಿ (ವೃಕ್ಷ init = DECL_INITIAL (decl))
    DECL_INITIAL (decl) = braced_lists_to_strings (type, init);

  ಯದಿ (VAR_P (decl))
    {
      ಯದಿ (init && ವೃಕ್ಷ_CODE (init) == CONSTRUCTOR)
	add_flexible_array_elts_to_size (decl, init);

      complete_flexible_array_elts (DECL_INITIAL (decl));

      ಯದಿ (is_global_var (decl))
	{
	  type_context_kind context = (DECL_THREAD_LOCAL_P (decl)
				       ? TCTX_THREAD_STORAGE
				       : TCTX_STATIC_STORAGE);
	  ಯದಿ (!verify_type_context (ಒಳಹರಿವು_location, context, ವೃಕ್ಷ_TYPE (decl)))
	    ವೃಕ್ಷ_TYPE (decl) = error_mark_ಗಂಟು;
	}

      ಯದಿ (DECL_SIZE (decl) == NULL_ವೃಕ್ಷ && ವೃಕ್ಷ_TYPE (decl) != error_mark_ಗಂಟು
	  && COMPLETE_TYPE_P (ವೃಕ್ಷ_TYPE (decl)))
	layout_decl (decl, 0);

      ಯದಿ (DECL_SIZE (decl) == NULL_ವೃಕ್ಷ
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

      ಯದಿ ((RECORD_OR_UNION_TYPE_P (ವೃಕ್ಷ_TYPE (decl))
	  || ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (decl)) == ENUMERAL_TYPE)
	  && DECL_SIZE (decl) == NULL_ವೃಕ್ಷ
	  && ವೃಕ್ಷ_STATIC (decl))
	incomplete_record_decls.safe_ತಳ್ಳು (decl);

      ಯದಿ (is_global_var (decl)
	  && DECL_SIZE (decl) != NULL_ವೃಕ್ಷ
	  && ವೃಕ್ಷ_TYPE (decl) != error_mark_ಗಂಟು)
	{
	  ಯದಿ (ವೃಕ್ಷ_CODE (DECL_SIZE (decl)) == INTEGER_CST)
	    constant_expression_warning (DECL_SIZE (decl));
	  ಅನ್ಯಥಾ
	    {
	      error ("storage size of %q+D isn%'t constant", decl);
	      ವೃಕ್ಷ_TYPE (decl) = error_mark_ಗಂಟು;
	    }
	}

      ಯದಿ (ವೃಕ್ಷ_USED (type))
	{
	  ವೃಕ್ಷ_USED (decl) = 1;
	  DECL_READ_P (decl) = 1;
	}
    }

  /* If this is a function and an assembler name is specified, reset DECL_RTL
     so we can give it its new name.  Also, update builtin_decl if it
     was a normal built-in.  */
  ಯದಿ (ವೃಕ್ಷ_CODE (decl) == FUNCTION_DECL && asmspec)
    {
      ಯದಿ (DECL_BUILT_IN_CLASS (decl) == BUILT_IN_NORMAL)
	set_builtin_user_assembler_name (decl, asmspec);
      set_user_assembler_name (decl, asmspec);
    }

  /* If #pragma weak was used, mark the decl weak now.  */
  maybe_apply_pragma_weak (decl);

  /* Output the assembler code and/or RTL code for variables and functions,
     unless the type is an undefined structure or union.
     If not, it will get done when the type is completed.  */

  ಯದಿ (VAR_OR_FUNCTION_DECL_P (decl))
    {
      /* Determine the ELF visibility.  */
      ಯದಿ (ವೃಕ್ಷ_PUBLIC (decl))
	c_determine_visibility (decl);

      /* This is a no-op in c-lang.cc or something real in objc-act.cc.  */
      ಯದಿ (c_dialect_objc ())
	objc_check_decl (decl);

      ಯದಿ (asmspec)
	{
	  /* If this is not a static variable, issue a warning.
	     It doesn't make any sense to give an ASMSPEC for an
	     ordinary, non-register local variable.  Historically,
	     GCC has accepted -- but ignored -- the ASMSPEC in
	     this case.  */
	  ಯದಿ (!DECL_FILE_SCOPE_P (decl)
	      && VAR_P (decl)
	      && !C_DECL_REGISTER (decl)
	      && !ವೃಕ್ಷ_STATIC (decl))
	    warning (0, "ignoring %<asm%> specifier for non-static local "
		     "variable %q+D", decl);
	  ಅನ್ಯಥಾ
	    set_user_assembler_name (decl, asmspec);
	}

      ಯದಿ (DECL_FILE_SCOPE_P (decl))
	{
	  ಯದಿ (DECL_INITIAL (decl) == NULL_ವೃಕ್ಷ
	      || DECL_INITIAL (decl) == error_mark_ಗಂಟು)
	    /* Don't output anything
	       when a tentative file-scope definition is seen.
	       But at end of compilation, do output code for them.  */
	    DECL_DEFER_OUTPUT (decl) = 1;
	  ಯದಿ (asmspec && VAR_P (decl) && C_DECL_REGISTER (decl))
	    DECL_HARD_REGISTER (decl) = 1;
	  rest_of_decl_compilation (decl, ಸತ್ಯ, 0);

	  ಯದಿ (ವೃಕ್ಷ_CODE (decl) == FUNCTION_DECL)
	    {
	      ವೃಕ್ಷ parms = DECL_ARGUMENTS (decl);
	      ಧ್ರುವ ತಾರ್ಕಿಕ builtin = fndecl_built_in_p (decl);
	      ಯದಿ (ವೃಕ್ಷ access = build_attr_access_from_parms (parms, !builtin))
		decl_attributes (&decl, access, 0);
	    }
	}
      ಅನ್ಯಥಾ
	{
	  /* In conjunction with an ASMSPEC, the `register'
	     keyword indicates that we should place the variable
	     in a particular register.  */
	  ಯದಿ (asmspec && C_DECL_REGISTER (decl))
	    {
	      DECL_HARD_REGISTER (decl) = 1;
	      /* This cannot be done for a structure with volatile
		 fields, on which DECL_REGISTER will have been
		 reset.  */
	      ಯದಿ (!DECL_REGISTER (decl))
		error ("cannot put object with volatile field into register");
	    }

	  ಯದಿ (ವೃಕ್ಷ_CODE (decl) != FUNCTION_DECL)
	    {
	      /* If we're building a variable sized type, and we might be
		 reachable other than via the top of the current binding
		 level, then create a new BIND_EXPR so that we deallocate
		 the object at the right time.  */
	      /* Note that DECL_SIZE can be null due to errors.  */
	      ಯದಿ (DECL_SIZE (decl)
		  && !ವೃಕ್ಷ_CONSTANT (DECL_SIZE (decl))
		  && STATEMENT_LIST_HAS_LABEL (cur_stmt_list))
		{
		  ವೃಕ್ಷ bind;
		  bind = build3 (BIND_ಅಭಿವ್ಯಕ್ತಿ, void_type_ಗಂಟು, ರಿಕ್ತ, ರಿಕ್ತ, ರಿಕ್ತ);
		  ವೃಕ್ಷ_SIDE_EFFECTS (bind) = 1;
		  add_stmt (bind);
		  BIND_ಅಭಿವ್ಯಕ್ತಿ_BODY (bind) = ತಳ್ಳು_stmt_list ();
		}
	      add_stmt (build_stmt (DECL_SOURCE_LOCATION (decl),
				    DECL_ಅಭಿವ್ಯಕ್ತಿ, decl));
	    }
	}


      ಯದಿ (!DECL_FILE_SCOPE_P (decl))
	{
	  /* Recompute the RTL of a local array now
	     if it used to be an incomplete type.  */
	  ಯದಿ (was_incomplete && !is_global_var (decl))
	    {
	      /* If we used it already as memory, it must stay in memory.  */
	      ವೃಕ್ಷ_ADDRESSABLE (decl) = ವೃಕ್ಷ_USED (decl);
	      /* If it's still incomplete now, no init will save it.  */
	      ಯದಿ (DECL_SIZE (decl) == NULL_ವೃಕ್ಷ)
		DECL_INITIAL (decl) = NULL_ವೃಕ್ಷ;
	    }
	}
    }

  ಯದಿ (ವೃಕ್ಷ_CODE (decl) == TYPE_DECL)
    {
      ಯದಿ (!DECL_FILE_SCOPE_P (decl)
	  && c_type_variably_modified_p (ವೃಕ್ಷ_TYPE (decl)))
	add_stmt (build_stmt (DECL_SOURCE_LOCATION (decl), DECL_ಅಭಿವ್ಯಕ್ತಿ, decl));

      rest_of_decl_compilation (decl, DECL_FILE_SCOPE_P (decl), 0);
    }

  /* Install a cleanup (aka destructor) if one was given.  */
  ಯದಿ (VAR_P (decl) && !ವೃಕ್ಷ_STATIC (decl))
    {
      ವೃಕ್ಷ attr = lookup_attribute ("cleanup", DECL_ATTRIBUTES (decl));
      ಯದಿ (attr)
	{
	  ವೃಕ್ಷ cleanup_id = ವೃಕ್ಷ_ಮೌಲ್ಯ (ವೃಕ್ಷ_ಮೌಲ್ಯ (attr));
	  ವೃಕ್ಷ cleanup_decl = lookup_name (cleanup_id);
	  ವೃಕ್ಷ cleanup;
	  vec<ವೃಕ್ಷ, va_gc> *v;

	  /* Build "cleanup(&decl)" for the destructor.  */
	  cleanup = build_unary_op (ಒಳಹರಿವು_location, ADDR_ಅಭಿವ್ಯಕ್ತಿ, decl, ಅಸತ್ಯ);
	  vec_alloc (v, 1);
	  v->quick_ತಳ್ಳು (cleanup);
	  cleanup = c_build_function_call_vec (DECL_SOURCE_LOCATION (decl),
					       vNULL, cleanup_decl, v, ರಿಕ್ತ);
	  vec_free (v);

	  /* Don't warn about decl unused; the cleanup uses it.  */
	  ವೃಕ್ಷ_USED (decl) = 1;
	  ವೃಕ್ಷ_USED (cleanup_decl) = 1;
	  DECL_READ_P (decl) = 1;

	  ತಳ್ಳು_cleanup (decl, cleanup, ಅಸತ್ಯ);
	}
    }

  ಯದಿ (warn_cxx_compat
      && VAR_P (decl)
      && !DECL_EXTERNAL (decl)
      && DECL_INITIAL (decl) == NULL_ವೃಕ್ಷ)
    {
      type = strip_array_types (type);
      ಯದಿ (ವೃಕ್ಷ_READONLY (decl))
	warning_at (DECL_SOURCE_LOCATION (decl), OPT_Wc___compat,
		    "uninitialized %<const %D%> is invalid in C++", decl);
      ಅನ್ಯಥಾ ಯದಿ (RECORD_OR_UNION_TYPE_P (type)
	       && C_TYPE_FIELDS_READONLY (type))
	diagnose_uninitialized_cst_member (decl, type);
    }

  ಯದಿ (flag_openmp
      && VAR_P (decl)
      && lookup_attribute ("omp declare target implicit",
			   DECL_ATTRIBUTES (decl)))
    {
      DECL_ATTRIBUTES (decl)
	= remove_attribute ("omp declare target implicit",
			    DECL_ATTRIBUTES (decl));
      ಯದಿ (!omp_mappable_type (ವೃಕ್ಷ_TYPE (decl)))
	error ("%q+D in declare target directive does not have mappable type",
	       decl);
      ಅನ್ಯಥಾ ಯದಿ (!lookup_attribute ("omp declare target",
				  DECL_ATTRIBUTES (decl))
	       && !lookup_attribute ("omp declare target link",
				     DECL_ATTRIBUTES (decl)))
	{
	  DECL_ATTRIBUTES (decl)
	    = ವೃಕ್ಷ_cons (get_identifier ("omp declare target"),
			 NULL_ವೃಕ್ಷ, DECL_ATTRIBUTES (decl));
	    symtab_ಗಂಟು *ಗಂಟು = symtab_ಗಂಟು::get (decl);
	    ಯದಿ (ಗಂಟು != ರಿಕ್ತ)
	      {
		ಗಂಟು->offloadable = 1;
		ಯದಿ (ENABLE_OFFLOADING)
		  {
		    g->have_offload = ಸತ್ಯ;
		    ಯದಿ (is_a <varpool_ಗಂಟು *> (ಗಂಟು))
		      vec_safe_ತಳ್ಳು (offload_vars, decl);
		  }
	      }
	}
    }

  /* This is the last point we can lower alignment so give the target the
     chance to do so.  */
  ಯದಿ (VAR_P (decl)
      && !is_global_var (decl)
      && !DECL_HARD_REGISTER (decl))
    targetm.lower_local_decl_alignment (decl);

  invoke_plugin_callbacks (PLUGIN_FINISH_DECL, decl);
}

/* Given a parsed parameter declaration, decode it into a PARM_DECL.
   EXPR is NULL or a pointer to an expression that needs to be
   evaluated for the side effects of array size expressions in the
   parameters.  */

ವೃಕ್ಷ
grokparm (ಧ್ರುವ ಸಂರಚನಾ c_parm *parm, ವೃಕ್ಷ *ಅಭಿವ್ಯಕ್ತಿ)
{
  ವೃಕ್ಷ attrs = parm->attrs;
  ವೃಕ್ಷ decl = grokdeclarator (parm->declarator, parm->specs, PARM, ಅಸತ್ಯ,
			      ರಿಕ್ತ, &attrs, ಅಭಿವ್ಯಕ್ತಿ, ರಿಕ್ತ, DEPRECATED_NORMAL);

  decl_attributes (&decl, attrs, 0);

  ಪ್ರತ್ಯಾಗಮ decl;
}



/* Given a parsed parameter declaration, decode it into a PARM_DECL
   and push that on the current scope.  EXPR is a pointer to an
   expression that needs to be evaluated for the side effects of array
   size expressions in the parameters.  */

ಶೂನ್ಯ
ತಳ್ಳು_parm_decl (ಧ್ರುವ ಸಂರಚನಾ c_parm *parm, ವೃಕ್ಷ *ಅಭಿವ್ಯಕ್ತಿ)
{
  ವೃಕ್ಷ attrs = parm->attrs;
  ವೃಕ್ಷ decl = grokdeclarator (parm->declarator, parm->specs, PARM, ಅಸತ್ಯ, ರಿಕ್ತ,
			      &attrs, ಅಭಿವ್ಯಕ್ತಿ, ರಿಕ್ತ, DEPRECATED_NORMAL);
  ಯದಿ (decl && DECL_P (decl))
    DECL_SOURCE_LOCATION (decl) = parm->loc;

  decl_attributes (&decl, attrs, 0);

  decl = pushdecl (decl);

  finish_decl (decl, ಒಳಹರಿವು_location, NULL_ವೃಕ್ಷ, NULL_ವೃಕ್ಷ, NULL_ವೃಕ್ಷ);
}

/* Mark all the parameter declarations to date as forward decls.
   Also diagnose use of this extension.  */

ಶೂನ್ಯ
mark_forward_parm_decls (ಶೂನ್ಯ)
{
  ಸಂರಚನಾ c_binding *b;

  ಯದಿ (current_scope->had_forward_parm_decls)
    warning_at (ಒಳಹರಿವು_location, OPT_Wmultiple_parameter_fwd_decl_lists,
		"more than one list of forward declarations of parameters");
  ಯದಿ (pedantic && !current_scope->had_forward_parm_decls)
    pedwarn (ಒಳಹರಿವು_location, OPT_Wpedantic,
	     "ISO C forbids forward parameter declarations");

  current_scope->had_forward_parm_decls = ಸತ್ಯ;

  ಪ್ರತಿ (b = current_scope->bindings; b; b = b->prev)
    ಯದಿ (ವೃಕ್ಷ_CODE (b->decl) == PARM_DECL)
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
			unsigned ಪೂರ್ಣಾಙ್ಕ alignas_align,
			ಸಂರಚನಾ c_declspecs *scspecs)
{
  /* We do not use start_decl here because we have a type, not a declarator;
     and do not use finish_decl because the decl should be stored inside
     the COMPOUND_LITERAL_EXPR rather than added elsewhere as a DECL_EXPR.  */
  ವೃಕ್ಷ decl;
  ವೃಕ್ಷ complit;
  ವೃಕ್ಷ stmt;
  ತಾರ್ಕಿಕ threadp = scspecs ? scspecs->thread_p : ಅಸತ್ಯ;
  ಗಣನಾ c_storage_class storage_class = (scspecs
					? scspecs->storage_class
					: csc_none);

  ಯದಿ (type == error_mark_ಗಂಟು
      || init == error_mark_ಗಂಟು)
    ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;

  ಯದಿ (current_scope == file_scope && storage_class == csc_register)
    {
      error_at (loc, "file-scope compound literal specifies %<register%>");
      storage_class = csc_none;
    }

  ಯದಿ (current_scope != file_scope && threadp && storage_class == csc_none)
    {
      error_at (loc, "compound literal implicitly auto and declared %qs",
		scspecs->thread_gnu_p ? "__thread" : "_Thread_local");
      threadp = ಅಸತ್ಯ;
    }

  decl = build_decl (loc, VAR_DECL, NULL_ವೃಕ್ಷ, type);
  DECL_EXTERNAL (decl) = 0;
  ವೃಕ್ಷ_PUBLIC (decl) = 0;
  ವೃಕ್ಷ_STATIC (decl) = (current_scope == file_scope
			|| storage_class == csc_static);
  DECL_CONTEXT (decl) = current_function_decl;
  ವೃಕ್ಷ_USED (decl) = 1;
  DECL_READ_P (decl) = 1;
  DECL_ARTIFICIAL (decl) = 1;
  DECL_IGNORED_P (decl) = 1;
  C_DECL_COMPOUND_LITERAL_P (decl) = 1;
  C_DECL_DECLARED_CONSTEXPR (decl) = scspecs && scspecs->constexpr_p;
  ವೃಕ್ಷ_TYPE (decl) = type;
  ಯದಿ (threadp)
    set_decl_tls_model (decl, decl_default_tls_model (decl));
  ಯದಿ (storage_class == csc_register)
    {
      C_DECL_REGISTER (decl) = 1;
      DECL_REGISTER (decl) = 1;
    }
  c_apply_type_quals_to_decl (TYPE_QUALS (strip_array_types (type)), decl);
  ಯದಿ (alignas_align)
    {
      SET_DECL_ALIGN (decl, alignas_align * BITS_PER_UNIT);
      DECL_USER_ALIGN (decl) = 1;
    }
  store_init_ಮೌಲ್ಯ (loc, decl, init, NULL_ವೃಕ್ಷ);
  ಯದಿ (current_scope != file_scope
      && ವೃಕ್ಷ_STATIC (decl)
      && !ವೃಕ್ಷ_READONLY (decl)
      && DECL_DECLARED_INLINE_P (current_function_decl)
      && DECL_EXTERNAL (current_function_decl))
    record_inline_static (ಒಳಹರಿವು_location, current_function_decl,
			  decl, csi_modifiable);

  ಯದಿ (ವೃಕ್ಷ_CODE (type) == ARRAY_TYPE && !COMPLETE_TYPE_P (type))
    {
      ಪೂರ್ಣಾಙ್ಕ failure = complete_array_type (&ವೃಕ್ಷ_TYPE (decl),
					 DECL_INITIAL (decl), ಸತ್ಯ);
      /* If complete_array_type returns 3, it means that the initial value of
         the compound literal is empty.  Allow it with a pedwarn; in pre-C23
         modes, the empty initializer itself has been diagnosed if pedantic so
         does not need to be diagnosed again here.  */
      gcc_assert (failure == 0 || failure == 3);
      ಯದಿ (failure == 3 && flag_isoc23)
	pedwarn (loc, OPT_Wpedantic,
		 "array of unknown size with empty initializer");

      type = ವೃಕ್ಷ_TYPE (decl);
      ವೃಕ್ಷ_TYPE (DECL_INITIAL (decl)) = type;
      relayout_decl (decl);
    }

  ಯದಿ (type == error_mark_ಗಂಟು || !COMPLETE_TYPE_P (type))
    {
      c_incomplete_type_error (loc, NULL_ವೃಕ್ಷ, type);
      ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
    }

  ಯದಿ ((ವೃಕ್ಷ_STATIC (decl) || C_DECL_DECLARED_CONSTEXPR (decl))
      && C_TYPE_VARIABLE_SIZE (type))
    error_at (loc, "storage size isn%'t constant");

  ಯದಿ (ವೃಕ್ಷ_STATIC (decl)
      && !verify_type_context (loc, TCTX_STATIC_STORAGE, type))
    ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;

  stmt = build_stmt (DECL_SOURCE_LOCATION (decl), DECL_ಅಭಿವ್ಯಕ್ತಿ, decl);
  complit = build1 (COMPOUND_LITERAL_ಅಭಿವ್ಯಕ್ತಿ, type, stmt);
  ವೃಕ್ಷ_SIDE_EFFECTS (complit) = 1;

  layout_decl (decl, 0);

  ಯದಿ (ವೃಕ್ಷ_STATIC (decl))
    {
      /* This decl needs a name for the assembler output.  */
      set_compound_literal_name (decl);
      DECL_DEFER_OUTPUT (decl) = 1;
      DECL_COMDAT (decl) = 1;
      pushdecl (decl);
      rest_of_decl_compilation (decl, 1, 0);
    }
  ಅನ್ಯಥಾ ಯದಿ (current_function_decl && !current_scope->parm_flag)
    pushdecl (decl);

  ಯದಿ (non_const)
    {
      complit = build2 (C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ, type, ರಿಕ್ತ, complit);
      C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ_NON_CONST (complit) = 1;
    }

  ಪ್ರತ್ಯಾಗಮ complit;
}

/* Check the type of a compound literal.  Here we just check that it
   is valid for C++.  */

ಶೂನ್ಯ
check_compound_literal_type (location_t loc, ಸಂರಚನಾ c_type_name *type_name)
{
  ಯದಿ (warn_cxx_compat
      && (type_name->specs->typespec_kind == ctsk_tagdef
          || type_name->specs->typespec_kind == ctsk_tagfirstref
	  || type_name->specs->typespec_kind == ctsk_tagfirstref_attrs))
    warning_at (loc, OPT_Wc___compat,
		"defining a type in a compound literal is invalid in C++");
}

/* Performs sanity checks on the TYPE and WIDTH of the bit-field NAME,
   replacing with appropriate values if they are invalid.  */

ಸ್ಥಿರ ಶೂನ್ಯ
check_bitfield_type_and_width (location_t loc, ವೃಕ್ಷ *type, ವೃಕ್ಷ *width,
			       ವೃಕ್ಷ orig_name)
{
  ವೃಕ್ಷ type_mv;
  unsigned ಪೂರ್ಣಾಙ್ಕ max_width;
  unsigned HOST_WIDE_INT w;
  ಧ್ರುವ ವರ್ಣ *name = (orig_name
		      ? identifier_to_locale (IDENTIFIER_POINTER (orig_name))
		      : _("<anonymous>"));

  /* Detect and ignore out of range field width and process valid
     field widths.  */
  ಯದಿ (!INTEGRAL_TYPE_P (ವೃಕ್ಷ_TYPE (*width)))
    {
      error_at (loc, "bit-field %qs width not an integer constant", name);
      *width = integer_one_ಗಂಟು;
    }
  ಅನ್ಯಥಾ
    {
      ಯದಿ (ವೃಕ್ಷ_CODE (*width) != INTEGER_CST)
	{
	  *width = c_fully_fold (*width, ಅಸತ್ಯ, ರಿಕ್ತ);
	  ಯದಿ (ವೃಕ್ಷ_CODE (*width) == INTEGER_CST)
	    pedwarn (loc, OPT_Wpedantic,
		     "bit-field %qs width not an integer constant expression",
		     name);
	}
      ಯದಿ (ವೃಕ್ಷ_CODE (*width) != INTEGER_CST)
	{
	  error_at (loc, "bit-field %qs width not an integer constant", name);
	  *width = integer_one_ಗಂಟು;
	}
      constant_expression_warning (*width);
      ಯದಿ (ವೃಕ್ಷ_int_cst_sgn (*width) < 0)
	{
	  error_at (loc, "negative width in bit-field %qs", name);
	  *width = integer_one_ಗಂಟು;
	}
      ಅನ್ಯಥಾ ಯದಿ (integer_zerop (*width) && orig_name)
	{
	  error_at (loc, "zero width for bit-field %qs", name);
	  *width = integer_one_ಗಂಟು;
	}
    }

  /* Detect invalid bit-field type.  */
  ಯದಿ (ವೃಕ್ಷ_CODE (*type) != INTEGER_TYPE
      && ವೃಕ್ಷ_CODE (*type) != BOOLEAN_TYPE
      && ವೃಕ್ಷ_CODE (*type) != ENUMERAL_TYPE
      && ವೃಕ್ಷ_CODE (*type) != BITINT_TYPE)
    {
      error_at (loc, "bit-field %qs has invalid type", name);
      *type = unsigned_type_ಗಂಟು;
    }

  ಯದಿ (TYPE_WARN_IF_NOT_ALIGN (*type))
    {
      error_at (loc, "cannot declare bit-field %qs with %<warn_if_not_aligned%> type",
		name);
      *type = unsigned_type_ಗಂಟು;
    }

  type_mv = TYPE_MAIN_VARIANT (*type);
  ಯದಿ (!in_system_header_at (ಒಳಹರಿವು_location)
      && type_mv != integer_type_ಗಂಟು
      && type_mv != unsigned_type_ಗಂಟು
      && type_mv != boolean_type_ಗಂಟು)
    pedwarn_c90 (loc, OPT_Wpedantic,
		 "type of bit-field %qs is a GCC extension", name);

  max_width = TYPE_PRECISION (*type);

  ಯದಿ (compare_ವೃಕ್ಷ_int (*width, max_width) > 0)
    {
      error_at (loc, "width of %qs exceeds its type", name);
      w = max_width;
      *width = build_int_cst (integer_type_ಗಂಟು, w);
    }
  ಅನ್ಯಥಾ
    w = ವೃಕ್ಷ_to_uhwi (*width);

  /* Truncation of hardbool false and true representation values is always safe:
     either the values remain different, or we'll report a problem when creating
     the narrower type.  */
  ಯದಿ (c_hardbool_type_attr (*type))
    ಪ್ರತ್ಯಾಗಮ;

  ಯದಿ (ವೃಕ್ಷ_CODE (*type) == ENUMERAL_TYPE)
    {
      ಸಂರಚನಾ lang_type *lt = TYPE_LANG_SPECIFIC (*type);
      ಯದಿ (!lt
	  || w < ವೃಕ್ಷ_int_cst_min_precision (lt->enum_min, TYPE_SIGN (*type))
	  || w < ವೃಕ್ಷ_int_cst_min_precision (lt->enum_max, TYPE_SIGN (*type)))
	warning_at (loc, 0, "%qs is narrower than values of its type", name);
    }
}



/* Print warning about variable length array if necessary.  */

ಸ್ಥಿರ ಶೂನ್ಯ
warn_variable_length_array (ವೃಕ್ಷ name, ವೃಕ್ಷ size)
{
  ಯದಿ (ವೃಕ್ಷ_CONSTANT (size))
    {
      ಯದಿ (name)
	pedwarn_c90 (ಒಳಹರಿವು_location, OPT_Wvla,
		     "ISO C90 forbids array %qE whose size "
		     "cannot be evaluated", name);
      ಅನ್ಯಥಾ
	pedwarn_c90 (ಒಳಹರಿವು_location, OPT_Wvla, "ISO C90 forbids array "
		     "whose size cannot be evaluated");
    }
  ಅನ್ಯಥಾ
    {
      ಯದಿ (name)
	pedwarn_c90 (ಒಳಹರಿವು_location, OPT_Wvla,
		     "ISO C90 forbids variable length array %qE", name);
      ಅನ್ಯಥಾ
	pedwarn_c90 (ಒಳಹರಿವು_location, OPT_Wvla, "ISO C90 forbids variable "
		     "length array");
    }
}

/* Returns the smallest location != UNKNOWN_LOCATION in LOCATIONS,
   considering only those c_declspec_words found in LIST, which
   must be terminated by cdw_number_of_elements.  */

ಸ್ಥಿರ location_t
smallest_type_quals_location (ಧ್ರುವ location_t *locations,
			      ಧ್ರುವ c_declspec_word *list)
{
  location_t loc = UNKNOWN_LOCATION;
  ಯಾವತ್ (*list != cdw_ಸಂಖ್ಯೆ_of_elements)
    {
      location_t newloc = locations[*list];
      ಯದಿ (loc == UNKNOWN_LOCATION
	  || (newloc != UNKNOWN_LOCATION && newloc < loc))
	loc = newloc;
      list++;
    }

  ಪ್ರತ್ಯಾಗಮ loc;
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
add_decl_ಅಭಿವ್ಯಕ್ತಿ (location_t loc, ವೃಕ್ಷ type, ವೃಕ್ಷ *ಅಭಿವ್ಯಕ್ತಿ, ತಾರ್ಕಿಕ set_name_p)
{
  ವೃಕ್ಷ bind = NULL_ವೃಕ್ಷ;
  ಯದಿ (ಅಭಿವ್ಯಕ್ತಿ)
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
  add_stmt (build_stmt (DECL_SOURCE_LOCATION (decl), DECL_ಅಭಿವ್ಯಕ್ತಿ, decl));
  ಯದಿ (set_name_p)
    TYPE_NAME (type) = decl;

  ಯದಿ (bind)
    {
      ತೆಗೆ_scope ();
      BIND_ಅಭಿವ್ಯಕ್ತಿ_BODY (bind) = ತೆಗೆ_stmt_list (BIND_ಅಭಿವ್ಯಕ್ತಿ_BODY (bind));
      ಯದಿ (*ಅಭಿವ್ಯಕ್ತಿ)
	*ಅಭಿವ್ಯಕ್ತಿ = build2 (COMPOUND_ಅಭಿವ್ಯಕ್ತಿ, void_type_ಗಂಟು, *ಅಭಿವ್ಯಕ್ತಿ, bind);
      ಅನ್ಯಥಾ
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
  ವೃಕ್ಷ args = ವೃಕ್ಷ_cons (NULL_ವೃಕ್ಷ, acsstr, vbchain);
  ವೃಕ್ಷ name = get_identifier ("arg spec");
  ಪ್ರತ್ಯಾಗಮ ವೃಕ್ಷ_cons (name, args, attrs);
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
grokdeclarator (ಧ್ರುವ ಸಂರಚನಾ c_declarator *declarator,
		ಸಂರಚನಾ c_declspecs *declspecs,
		ಗಣನಾ decl_context decl_context, ತಾರ್ಕಿಕ initialized, ವೃಕ್ಷ *width,
		ವೃಕ್ಷ *decl_attrs, ವೃಕ್ಷ *ಅಭಿವ್ಯಕ್ತಿ, ತಾರ್ಕಿಕ *ಅಭಿವ್ಯಕ್ತಿ_const_operands,
		ಗಣನಾ deprecated_states deprecated_state)
{
  ವೃಕ್ಷ type = declspecs->type;
  ತಾರ್ಕಿಕ threadp = declspecs->thread_p;
  ತಾರ್ಕಿಕ constexprp = declspecs->constexpr_p;
  ಗಣನಾ c_storage_class storage_class = declspecs->storage_class;
  ಪೂರ್ಣಾಙ್ಕ constp;
  ಪೂರ್ಣಾಙ್ಕ restrictp;
  ಪೂರ್ಣಾಙ್ಕ volatilep;
  ಪೂರ್ಣಾಙ್ಕ atomicp;
  ಪೂರ್ಣಾಙ್ಕ type_quals = TYPE_UNQUALIFIED;
  ವೃಕ್ಷ name = NULL_ವೃಕ್ಷ;
  ತಾರ್ಕಿಕ funcdef_flag = ಅಸತ್ಯ;
  ತಾರ್ಕಿಕ funcdef_syntax = ಅಸತ್ಯ;
  ತಾರ್ಕಿಕ size_varies = ಅಸತ್ಯ;
  ತಾರ್ಕಿಕ size_error = ಅಸತ್ಯ;
  ವೃಕ್ಷ decl_attr = declspecs->decl_attr;
  ಪೂರ್ಣಾಙ್ಕ array_ptr_quals = TYPE_UNQUALIFIED;
  ವೃಕ್ಷ array_ptr_attrs = NULL_ವೃಕ್ಷ;
  ತಾರ್ಕಿಕ array_parm_static = ಅಸತ್ಯ;
  ತಾರ್ಕಿಕ array_parm_vla_unspec_p = ಅಸತ್ಯ;
  ವೃಕ್ಷ returned_attrs = NULL_ವೃಕ್ಷ;
  ವೃಕ್ಷ decl_id_attrs = NULL_ವೃಕ್ಷ;
  ತಾರ್ಕಿಕ bitfield = width != ರಿಕ್ತ;
  ವೃಕ್ಷ element_type;
  ವೃಕ್ಷ orig_qual_type = ರಿಕ್ತ;
  size_t orig_qual_indirect = 0;
  ಸಂರಚನಾ c_arg_info *arg_info = 0;
  addr_space_t as1, as2, address_space;
  location_t loc = UNKNOWN_LOCATION;
  ವೃಕ್ಷ ಅಭಿವ್ಯಕ್ತಿ_dummy;
  ತಾರ್ಕಿಕ ಅಭಿವ್ಯಕ್ತಿ_const_operands_dummy;
  ಗಣನಾ c_declarator_kind first_non_attr_kind;
  unsigned ಪೂರ್ಣಾಙ್ಕ alignas_align = 0;

  ಯದಿ (type == NULL_ವೃಕ್ಷ)
    {
      /* This can occur for auto on a parameter in C23 mode.  Set a
	 dummy type here so subsequent code can give diagnostics for
	 this case.  */
      gcc_assert (declspecs->c23_auto_p);
      gcc_assert (decl_context == PARM);
      type = declspecs->type = integer_type_ಗಂಟು;
    }
  ಯದಿ (ವೃಕ್ಷ_CODE (type) == ERROR_MARK)
    ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
  ಯದಿ (ಅಭಿವ್ಯಕ್ತಿ == ರಿಕ್ತ)
    {
      ಅಭಿವ್ಯಕ್ತಿ = &ಅಭಿವ್ಯಕ್ತಿ_dummy;
      ಅಭಿವ್ಯಕ್ತಿ_dummy = NULL_ವೃಕ್ಷ;
    }
  ಯದಿ (ಅಭಿವ್ಯಕ್ತಿ_const_operands == ರಿಕ್ತ)
    ಅಭಿವ್ಯಕ್ತಿ_const_operands = &ಅಭಿವ್ಯಕ್ತಿ_const_operands_dummy;

  ಯದಿ (declspecs->ಅಭಿವ್ಯಕ್ತಿ)
    {
      ಯದಿ (*ಅಭಿವ್ಯಕ್ತಿ)
	*ಅಭಿವ್ಯಕ್ತಿ = build2 (COMPOUND_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (declspecs->ಅಭಿವ್ಯಕ್ತಿ), *ಅಭಿವ್ಯಕ್ತಿ,
			declspecs->ಅಭಿವ್ಯಕ್ತಿ);
      ಅನ್ಯಥಾ
	*ಅಭಿವ್ಯಕ್ತಿ = declspecs->ಅಭಿವ್ಯಕ್ತಿ;
    }
  *ಅಭಿವ್ಯಕ್ತಿ_const_operands = declspecs->ಅಭಿವ್ಯಕ್ತಿ_const_operands;

  ಯದಿ (decl_context == FUNCDEF)
    funcdef_flag = ಸತ್ಯ, decl_context = NORMAL;

  /* Look inside a declarator for the name being declared
     and get it as an IDENTIFIER_NODE, for an error message.  */
  {
    ಧ್ರುವ ಸಂರಚನಾ c_declarator *decl = declarator;

    first_non_attr_kind = cdk_attrs;
    ಯಾವತ್ (decl)
      ವಿಕಲ್ಪ (decl->kind)
	{
	ಪಕ್ಷ cdk_array:
	  loc = decl->id_loc;
	  /* FALL THRU.  */

	ಪಕ್ಷ cdk_function:
	ಪಕ್ಷ cdk_pointer:
	  funcdef_syntax = (decl->kind == cdk_function);
	  ಯದಿ (first_non_attr_kind == cdk_attrs)
	    first_non_attr_kind = decl->kind;
	  decl = decl->declarator;
	  ಭಙ್ಗ;

	ಪಕ್ಷ cdk_attrs:
	  decl = decl->declarator;
	  ಭಙ್ಗ;

	ಪಕ್ಷ cdk_id:
	  loc = decl->id_loc;
	  ಯದಿ (decl->u.id.id)
	    name = decl->u.id.id;
	  decl_id_attrs = decl->u.id.attrs;
	  ಯದಿ (first_non_attr_kind == cdk_attrs)
	    first_non_attr_kind = decl->kind;
	  decl = 0;
	  ಭಙ್ಗ;

	ಸ್ವಭಾವ:
	  gcc_unreachable ();
	}
    ಯದಿ (name == NULL_ವೃಕ್ಷ)
      {
	gcc_assert (decl_context == PARM
		    || decl_context == TYPENAME
		    || decl_context == GENERIC_ASSOC
		    || (decl_context == FIELD
			&& declarator->kind == cdk_id));
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
  ಯದಿ (declspecs->enum_type_specifier_ref_p)
    error_at (loc, "%<enum%> underlying type may not be specified here");

  /* A function definition's declarator must have the form of
     a function declarator.  */

  ಯದಿ (funcdef_flag && !funcdef_syntax)
    ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;

  /* If this looks like a function definition, make it one,
     even if it occurs where parms are expected.
     Then store_parm_decls will reject it and not use it as a parm.  */
  ಯದಿ (decl_context == NORMAL && !funcdef_flag && current_scope->parm_flag)
    decl_context = PARM;

  ಯದಿ (deprecated_state != UNAVAILABLE_DEPRECATED_SUPPRESS)
    {
      ಯದಿ (declspecs->unavailable_p)
	error_unavailable_use (declspecs->type, declspecs->decl_attr);
      ಅನ್ಯಥಾ ಯದಿ (declspecs->deprecated_p
		&& deprecated_state != DEPRECATED_SUPPRESS)
	warn_deprecated_use (declspecs->type, declspecs->decl_attr);
    }

  ಯದಿ ((decl_context == NORMAL || decl_context == FIELD)
      && current_scope == file_scope
      && c_type_variably_modified_p (type))
    {
      ಯದಿ (name)
	error_at (loc, "variably modified %qE at file scope", name);
      ಅನ್ಯಥಾ
	error_at (loc, "variably modified field at file scope");
      type = integer_type_ಗಂಟು;
    }

  size_varies = C_TYPE_VARIABLE_SIZE (type) != 0;

  /* Diagnose defaulting to "int".  */

  ಯದಿ (declspecs->default_int_p)
    {
      /* Issue a warning if this is an ISO C 99 program or if
	 -Wreturn-type and this is a function, or if -Wimplicit;
	 prefer the former warning since it is more explicit.  */
      ಯದಿ ((warn_implicit_int || warn_return_type > 0 || flag_isoc99)
	  && funcdef_flag)
	warn_about_return_type = 1;
      ಅನ್ಯಥಾ
	{
	  ಯದಿ (name)
	    permerror_opt (loc, OPT_Wimplicit_int,
			   "type defaults to %<int%> in declaration "
			   "of %qE", name);
	  ಅನ್ಯಥಾ
	    permerror_opt (loc, OPT_Wimplicit_int,
			   "type defaults to %<int%> in type name");
	}
    }

  /* Adjust the type if a bit-field is being declared,
     -funsigned-bitfields applied and the type is not explicitly
     "signed".  */
  ಯದಿ (bitfield && !flag_signed_bitfields && !declspecs->explicit_signed_p
      && ವೃಕ್ಷ_CODE (type) == INTEGER_TYPE)
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
  as1 = declspecs->address_space;
  as2 = TYPE_ADDR_SPACE (element_type);
  address_space = ADDR_SPACE_GENERIC_P (as1)? as2 : as1;

  ಯದಿ (constp > 1)
    pedwarn_c90 (loc, OPT_Wpedantic, "duplicate %<const%>");
  ಯದಿ (restrictp > 1)
    pedwarn_c90 (loc, OPT_Wpedantic, "duplicate %<restrict%>");
  ಯದಿ (volatilep > 1)
    pedwarn_c90 (loc, OPT_Wpedantic, "duplicate %<volatile%>");
  ಯದಿ (atomicp > 1)
    pedwarn_c90 (loc, OPT_Wpedantic, "duplicate %<_Atomic%>");

  ಯದಿ (!ADDR_SPACE_GENERIC_P (as1) && !ADDR_SPACE_GENERIC_P (as2) && as1 != as2)
    error_at (loc, "conflicting named address spaces (%s vs %s)",
	      c_addr_space_name (as1), c_addr_space_name (as2));

  ಯದಿ ((ವೃಕ್ಷ_CODE (type) == ARRAY_TYPE
       || first_non_attr_kind == cdk_array)
      && TYPE_QUALS (element_type))
    {
      orig_qual_type = type;
      type = c_build_qualified_type (type, TYPE_UNQUALIFIED);
    }
  type_quals = ((constp ? TYPE_QUAL_CONST : 0)
		| (restrictp ? TYPE_QUAL_RESTRICT : 0)
		| (volatilep ? TYPE_QUAL_VOLATILE : 0)
		| (atomicp ? TYPE_QUAL_ATOMIC : 0)
		| ENCODE_QUAL_ADDR_SPACE (address_space));
  ಯದಿ (type_quals != TYPE_QUALS (element_type))
    orig_qual_type = NULL_ವೃಕ್ಷ;

  /* Applying the _Atomic qualifier to an array type (through the use
     of typedefs or typeof) must be detected here.  If the qualifier
     is introduced later, any appearance of applying it to an array is
     actually applying it to an element of that array.  */
  ಯದಿ (declspecs->atomic_p && ವೃಕ್ಷ_CODE (type) == ARRAY_TYPE)
    error_at (loc, "%<_Atomic%>-qualified array type");

  /* Warn about storage classes that are invalid for certain
     kinds of declarations (parameters, typenames, etc.).  */

  ಯದಿ (funcdef_flag
      && (threadp
	  || constexprp
	  || storage_class == csc_auto
	  || storage_class == csc_register
	  || storage_class == csc_typedef))
    {
      ಯದಿ (storage_class == csc_auto)
	pedwarn (loc,
		 (current_scope == file_scope) ? 0 : OPT_Wpedantic,
		 "function definition declared %<auto%>");
      ಯದಿ (storage_class == csc_register)
	error_at (loc, "function definition declared %<register%>");
      ಯದಿ (storage_class == csc_typedef)
	error_at (loc, "function definition declared %<typedef%>");
      ಯದಿ (threadp)
	error_at (loc, "function definition declared %qs",
		  declspecs->thread_gnu_p ? "__thread" : "_Thread_local");
      threadp = ಅಸತ್ಯ;
      /* The parser ensures a constexpr function definition never
	 reaches here.  */
      gcc_assert (!constexprp);
      ಯದಿ (storage_class == csc_auto
	  || storage_class == csc_register
	  || storage_class == csc_typedef)
	storage_class = csc_none;
    }
  ಅನ್ಯಥಾ ಯದಿ (decl_context != NORMAL && (storage_class != csc_none
				      || threadp
				      || constexprp
				      || declspecs->c23_auto_p))
    {
      ಯದಿ (decl_context == PARM
	  && storage_class == csc_register
	  && !constexprp
	  && !declspecs->c23_auto_p)
	;
      ಅನ್ಯಥಾ
	{
	  ವಿಕಲ್ಪ (decl_context)
	    {
	    ಪಕ್ಷ FIELD:
	      ಯದಿ (name)
		error_at (loc, "storage class specified for structure "
		    	  "field %qE", name);
	      ಅನ್ಯಥಾ
		error_at (loc, "storage class specified for structure field");
	      ಭಙ್ಗ;
	    ಪಕ್ಷ PARM:
	      ಯದಿ (name)
		error_at (loc, "storage class specified for parameter %qE",
		    	  name);
	      ಅನ್ಯಥಾ
		error_at (loc, "storage class specified for unnamed parameter");
	      ಭಙ್ಗ;
	    ಸ್ವಭಾವ:
	      error_at (loc, "storage class specified for typename");
	      ಭಙ್ಗ;
	    }
	  storage_class = csc_none;
	  threadp = ಅಸತ್ಯ;
	  constexprp = ಅಸತ್ಯ;
	}
    }
  ಅನ್ಯಥಾ ಯದಿ (storage_class == csc_extern
	   && initialized
	   && !funcdef_flag)
    {
      /* 'extern' with initialization is invalid if not at file scope.  */
       ಯದಿ (current_scope == file_scope)
         {
           /* It is fine to have 'extern const' when compiling at C
              and C++ intersection.  */
           ಯದಿ (!(warn_cxx_compat && constp))
             warning_at (loc, 0, "%qE initialized and declared %<extern%>",
		 	 name);
         }
      ಅನ್ಯಥಾ
	error_at (loc, "%qE has both %<extern%> and initializer", name);
    }
  ಅನ್ಯಥಾ ಯದಿ (current_scope == file_scope)
    {
      ಯದಿ (storage_class == csc_auto)
	error_at (loc, "file-scope declaration of %qE specifies %<auto%>",
	    	  name);
      ಯದಿ (pedantic && storage_class == csc_register)
	pedwarn (ಒಳಹರಿವು_location, OPT_Wpedantic,
		 "file-scope declaration of %qE specifies %<register%>", name);
    }
  ಅನ್ಯಥಾ
    {
      ಯದಿ (storage_class == csc_extern && funcdef_flag)
	error_at (loc, "nested function %qE declared %<extern%>", name);
      ಅನ್ಯಥಾ ಯದಿ (threadp && storage_class == csc_none)
	{
	  error_at (loc, "function-scope %qE implicitly auto and declared "
		    "%qs", name,
		    declspecs->thread_gnu_p ? "__thread" : "_Thread_local");
	  threadp = ಅಸತ್ಯ;
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

  ಯಾವತ್ (declarator && declarator->kind != cdk_id)
    {
      ಯದಿ (type == error_mark_ಗಂಟು)
	{
	  declarator = declarator->declarator;
	  ಅನುವರ್ತ;
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

      ಯದಿ (array_ptr_quals != TYPE_UNQUALIFIED
	  || array_ptr_attrs != NULL_ವೃಕ್ಷ
	  || array_parm_static)
	{
	  /* Only the innermost declarator (making a parameter be of
	     array type which is converted to pointer type)
	     may have static or type qualifiers.  */
	  error_at (loc, "static or type qualifiers in non-parameter array declarator");
	  array_ptr_quals = TYPE_UNQUALIFIED;
	  array_ptr_attrs = NULL_ವೃಕ್ಷ;
	  array_parm_static = ಅಸತ್ಯ;
	}

      ವಿಕಲ್ಪ (declarator->kind)
	{
	ಪಕ್ಷ cdk_attrs:
	  {
	    /* A declarator with embedded attributes.  */
	    ವೃಕ್ಷ attrs = declarator->u.attrs;
	    ಧ್ರುವ ಸಂರಚನಾ c_declarator *inner_decl;
	    ಪೂರ್ಣಾಙ್ಕ attr_flags = 0;
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
	    ಯಾವತ್ (inner_decl->kind == cdk_attrs)
	      inner_decl = inner_decl->declarator;
	    ಯದಿ (!cxx11_attribute_p (attrs))
	      {
		ಯದಿ (inner_decl->kind == cdk_id)
		  attr_flags |= (ಪೂರ್ಣಾಙ್ಕ) ATTR_FLAG_DECL_NEXT;
		ಅನ್ಯಥಾ ಯದಿ (inner_decl->kind == cdk_function)
		  attr_flags |= (ಪೂರ್ಣಾಙ್ಕ) ATTR_FLAG_FUNCTION_NEXT;
		ಅನ್ಯಥಾ ಯದಿ (inner_decl->kind == cdk_array)
		  attr_flags |= (ಪೂರ್ಣಾಙ್ಕ) ATTR_FLAG_ARRAY_NEXT;
	      }
	    attrs = c_warn_type_attributes (type, attrs);
	    returned_attrs = decl_attributes (&type,
					      chainon (returned_attrs, attrs),
					      attr_flags);
	    ಭಙ್ಗ;
	  }
	ಪಕ್ಷ cdk_array:
	  {
	    ವೃಕ್ಷ itype = NULL_ವೃಕ್ಷ;
	    ವೃಕ್ಷ size = declarator->u.array.dimen;
	    /* The index is a signed object `sizetype' bits wide.  */
	    ವೃಕ್ಷ index_type = c_common_signed_type (sizetype);

	    array_ptr_quals = declarator->u.array.quals;
	    array_ptr_attrs = declarator->u.array.attrs;
	    array_parm_static = declarator->u.array.static_p;
	    array_parm_vla_unspec_p = declarator->u.array.vla_unspec_p;

	    declarator = declarator->declarator;

	    ತಾರ್ಕಿಕ flexible_array_member = ಅಸತ್ಯ;

	    /* Check for some types that there cannot be arrays of.  */

	    ಯದಿ (VOID_TYPE_P (type))
	      {
		ಯದಿ (name)
		  error_at (loc, "declaration of %qE as array of voids", name);
		ಅನ್ಯಥಾ
		  error_at (loc, "declaration of type name as array of voids");
		type = error_mark_ಗಂಟು;
	      }

	    ಯದಿ (ವೃಕ್ಷ_CODE (type) == FUNCTION_TYPE)
	      {
		ಯದಿ (name)
		  error_at (loc, "declaration of %qE as array of functions",
		      	    name);
		ಅನ್ಯಥಾ
		  error_at (loc, "declaration of type name as array of "
		            "functions");
		type = error_mark_ಗಂಟು;
	      }

	    ಯದಿ (pedantic && !in_system_header_at (ಒಳಹರಿವು_location)
		&& flexible_array_type_p (type))
	      pedwarn (loc, OPT_Wpedantic,
		       "invalid use of structure with flexible array member");

	    ಯದಿ (size == error_mark_ಗಂಟು)
	      type = error_mark_ಗಂಟು;

	    ಯದಿ (type == error_mark_ಗಂಟು)
	      ಅನುವರ್ತ;

	    ಯದಿ (!verify_type_context (loc, TCTX_ARRAY_ELEMENT, type))
	      {
		type = error_mark_ಗಂಟು;
		ಅನುವರ್ತ;
	      }

	    /* If size was specified, set ITYPE to a range-type for
	       that size.  Otherwise, ITYPE remains null.  finish_decl
	       may figure it out from an initial value.  */

	    ಯದಿ (size)
	      {
		ತಾರ್ಕಿಕ size_maybe_const = ಸತ್ಯ;
		ತಾರ್ಕಿಕ size_int_const = (ವೃಕ್ಷ_CODE (size) == INTEGER_CST
				       && !ವೃಕ್ಷ_OVERFLOW (size));
		ತಾರ್ಕಿಕ this_size_varies = ಅಸತ್ಯ;

		/* Strip NON_LVALUE_EXPRs since we aren't using as an
		   lvalue.  */
		STRIP_TYPE_NOPS (size);

		ಯದಿ (!INTEGRAL_TYPE_P (ವೃಕ್ಷ_TYPE (size)))
		  {
		    ಯದಿ (name)
		      error_at (loc, "size of array %qE has non-integer type",
				name);
		    ಅನ್ಯಥಾ
		      error_at (loc,
				"size of unnamed array has non-integer type");
		    size = integer_one_ಗಂಟು;
		    size_int_const = ಸತ್ಯ;
		    size_error = ಸತ್ಯ;
		  }
		/* This can happen with enum forward declaration.  */
		ಅನ್ಯಥಾ ಯದಿ (!COMPLETE_TYPE_P (ವೃಕ್ಷ_TYPE (size)))
		  {
		    ಯದಿ (name)
		      error_at (loc, "size of array %qE has incomplete type",
				name);
		    ಅನ್ಯಥಾ
		      error_at (loc, "size of unnamed array has incomplete "
				"type");
		    size = integer_one_ಗಂಟು;
		    size_int_const = ಸತ್ಯ;
		    size_error = ಸತ್ಯ;
		  }

		size = c_fully_fold (size, ಅಸತ್ಯ, &size_maybe_const);

		ಯದಿ (pedantic && size_maybe_const && integer_zerop (size))
		  {
		    ಯದಿ (name)
		      pedwarn (loc, OPT_Wpedantic,
			       "ISO C forbids zero-size array %qE", name);
		    ಅನ್ಯಥಾ
		      pedwarn (loc, OPT_Wpedantic,
			       "ISO C forbids zero-size array");
		  }

		ಯದಿ (ವೃಕ್ಷ_CODE (size) == INTEGER_CST && size_maybe_const)
		  {
		    constant_expression_warning (size);
		    ಯದಿ (ವೃಕ್ಷ_int_cst_sgn (size) < 0)
		      {
			ಯದಿ (name)
			  error_at (loc, "size of array %qE is negative", name);
			ಅನ್ಯಥಾ
			  error_at (loc, "size of unnamed array is negative");
			size = integer_one_ಗಂಟು;
			size_int_const = ಸತ್ಯ;
			size_error = ಸತ್ಯ;
		      }
		    /* Handle a size folded to an integer constant but
		       not an integer constant expression.  */
		    ಯದಿ (!size_int_const)
		      {
			/* If this is a file scope declaration of an
			   ordinary identifier, this is invalid code;
			   diagnosing it here and not subsequently
			   treating the type as variable-length avoids
			   more confusing diagnostics later.  */
			ಯದಿ ((decl_context == NORMAL || decl_context == FIELD)
			    && current_scope == file_scope)
			  pedwarn (ಒಳಹರಿವು_location, 0,
				   "variably modified %qE at file scope",
				   name);
			ಅನ್ಯಥಾ
			  this_size_varies = size_varies = ಸತ್ಯ;
			warn_variable_length_array (name, size);
		      }
		  }
		ಅನ್ಯಥಾ ಯದಿ ((decl_context == NORMAL || decl_context == FIELD)
			 && current_scope == file_scope)
		  {
		    error_at (loc, "variably modified %qE at file scope", name);
		    size = integer_one_ಗಂಟು;
		  }
		ಅನ್ಯಥಾ
		  {
		    /* Make sure the array size remains visibly
		       nonconstant even if it is (eg) a const variable
		       with known value.  */
		    this_size_varies = size_varies = ಸತ್ಯ;
		    warn_variable_length_array (name, size);
		    ಯದಿ (sanitize_flags_p (SANITIZE_VLA)
			&& current_function_decl != NULL_ವೃಕ್ಷ
			&& decl_context == NORMAL)
		      {
			/* Evaluate the array size only once.  */
			size = save_ಅಭಿವ್ಯಕ್ತಿ (size);
			size = c_fully_fold (size, ಅಸತ್ಯ, ರಿಕ್ತ);
		        size = fold_build2 (COMPOUND_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (size),
					    ubsan_instrument_vla (loc, size),
					    size);
		      }
		  }

		ಯದಿ (integer_zerop (size) && !this_size_varies)
		  {
		    /* A zero-length array cannot be represented with
		       an unsigned index type, which is what we'll
		       get with build_index_type.  Create an
		       open-ended range instead.  */
		    itype = build_index_type (NULL_ವೃಕ್ಷ);
		  }
		ಅನ್ಯಥಾ
		  {
		    /* Arrange for the SAVE_EXPR on the inside of the
		       MINUS_EXPR, which allows the -1 to get folded
		       with the +1 that happens when building TYPE_SIZE.  */
		    ಯದಿ (size_varies)
		      size = save_ಅಭಿವ್ಯಕ್ತಿ (size);
		    ಯದಿ (this_size_varies && ವೃಕ್ಷ_CODE (size) == INTEGER_CST)
		      size = build2 (COMPOUND_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (size),
				     integer_zero_ಗಂಟು, size);

		    /* Compute the maximum valid index, that is, size
		       - 1.  Do the calculation in index_type, so that
		       if it is a variable the computations will be
		       done in the proper mode.  */
		    itype = fold_build2_loc (loc, MINUS_ಅಭಿವ್ಯಕ್ತಿ, index_type,
					     convert (index_type, size),
					     convert (index_type,
						      size_one_ಗಂಟು));

		    /* The above overflows when size does not fit
		       in index_type.
		       ???  While a size of INT_MAX+1 technically shouldn't
		       cause an overflow (because we subtract 1), handling
		       this case seems like an unnecessary complication.  */
		    ಯದಿ (ವೃಕ್ಷ_CODE (size) == INTEGER_CST
			&& !int_fits_type_p (size, index_type))
		      {
			ಯದಿ (name)
			  error_at (loc, "size of array %qE is too large",
			            name);
			ಅನ್ಯಥಾ
			  error_at (loc, "size of unnamed array is too large");
			type = error_mark_ಗಂಟು;
			ಅನುವರ್ತ;
		      }

		    itype = build_index_type (itype);
		  }
		ಯದಿ (this_size_varies)
		  {
		    ಯದಿ (ವೃಕ್ಷ_SIDE_EFFECTS (size))
		      {
			ಯದಿ (*ಅಭಿವ್ಯಕ್ತಿ)
			  *ಅಭಿವ್ಯಕ್ತಿ = build2 (COMPOUND_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (size),
					  *ಅಭಿವ್ಯಕ್ತಿ, size);
			ಅನ್ಯಥಾ
			  *ಅಭಿವ್ಯಕ್ತಿ = size;
		      }
		    *ಅಭಿವ್ಯಕ್ತಿ_const_operands &= size_maybe_const;
		  }
	      }
	    ಅನ್ಯಥಾ ಯದಿ (decl_context == FIELD)
	      {
		ಯದಿ (array_parm_vla_unspec_p)
		  /* Field names can in fact have function prototype
		     scope so [*] is disallowed here through making
		     the field variably modified, not through being
		     something other than a declaration with function
		     prototype scope.  */
		  size_varies = ಸತ್ಯ;
		ಅನ್ಯಥಾ
		  {
		    ಧ್ರುವ ಸಂರಚನಾ c_declarator *t = declarator;
		    ಯಾವತ್ (t->kind == cdk_attrs)
		      t = t->declarator;
		    flexible_array_member = (t->kind == cdk_id);
		  }
		ಯದಿ (flexible_array_member
		    && !in_system_header_at (ಒಳಹರಿವು_location))
		  pedwarn_c90 (loc, OPT_Wpedantic, "ISO C90 does not "
			       "support flexible array members");

		/* ISO C99 Flexible array members are effectively
		   identical to GCC's zero-length array extension.  */
		ಯದಿ (flexible_array_member)
		  itype = build_index_type (NULL_ವೃಕ್ಷ);
	      }

	    /* Complain about arrays of incomplete types.  */
	    ಯದಿ (!COMPLETE_TYPE_P (type))
	      {
		auto_diagnostic_group d;
		error_at (loc, "array type has incomplete element type %qT",
			  type);
		/* See if we can be more helpful.  */
		ಯದಿ (ವೃಕ್ಷ_CODE (type) == ARRAY_TYPE)
		  {
		    ಯದಿ (name)
		      inform (loc, "declaration of %qE as multidimensional "
			      "array must have bounds for all dimensions "
			      "except the first", name);
		    ಅನ್ಯಥಾ
		      inform (loc, "declaration of multidimensional array "
			      "must have bounds for all dimensions except "
			      "the first");
		  }
		type = error_mark_ಗಂಟು;
	      }
	    ಅನ್ಯಥಾ
	    /* When itype is NULL, a shared incomplete array type is
	       returned for all array of a given type.  Elsewhere we
	       make sure we don't complete that type before copying
	       it, but here we want to make sure we don't ever
	       modify the shared type, so we gcc_assert (itype)
	       below.  */
	      {
		addr_space_t as = DECODE_QUAL_ADDR_SPACE (type_quals);
		ಯದಿ (!ADDR_SPACE_GENERIC_P (as) && as != TYPE_ADDR_SPACE (type))
		  type = c_build_qualified_type (type,
						 ENCODE_QUAL_ADDR_SPACE (as));
		ಯದಿ (array_parm_vla_unspec_p)
		  type = c_build_array_type_unspecified (type);
		/* The GCC extension for zero-length arrays differs from
		   ISO flexible array members in that sizeof yields
		   zero.  */
		ಅನ್ಯಥಾ ಯದಿ (size && integer_zerop (size))
		  type = c_build_array_type_zero_size (type);
		ಅನ್ಯಥಾ
		  type = c_build_array_type (type, itype);

		ಯದಿ (!valid_array_size_p (loc, type, name))
		  type = error_mark_ಗಂಟು;
	      }

	    ಯದಿ (array_parm_vla_unspec_p)
	      {
		/* C99 6.7.5.2p4 */
		ಯದಿ (decl_context == TYPENAME)
		  warning (0, "%<[*]%> not in a declaration");
		ಅನ್ಯಥಾ ಯದಿ (decl_context != GENERIC_ASSOC
			 && decl_context != PARM
			 && decl_context != FIELD)
		  {
		    error ("%<[*]%> not allowed in other than function prototype scope "
			   "or generic association");
		    type = error_mark_ಗಂಟು;
		  }
		size_varies = ಸತ್ಯ;
	      }


	    gcc_assert (type == error_mark_ಗಂಟು
			|| flexible_array_member
			   == flexible_array_member_type_p (type));

	    ಯದಿ (decl_context != PARM
		&& (array_ptr_quals != TYPE_UNQUALIFIED
		    || array_ptr_attrs != NULL_ವೃಕ್ಷ
		    || array_parm_static))
	      {
		error_at (loc, "static or type qualifiers in non-parameter "
			  "array declarator");
		array_ptr_quals = TYPE_UNQUALIFIED;
		array_ptr_attrs = NULL_ವೃಕ್ಷ;
		array_parm_static = ಅಸತ್ಯ;
	      }
	    orig_qual_indirect++;
	    ಭಙ್ಗ;
	  }
	ಪಕ್ಷ cdk_function:
	  {
	    /* Say it's a definition only for the declarator closest
	       to the identifier, apart possibly from some
	       attributes.  */
	    ತಾರ್ಕಿಕ really_funcdef = ಅಸತ್ಯ;
	    ವೃಕ್ಷ arg_types;
	    orig_qual_type = NULL_ವೃಕ್ಷ;
	    ಯದಿ (funcdef_flag)
	      {
		ಧ್ರುವ ಸಂರಚನಾ c_declarator *t = declarator->declarator;
		ಯಾವತ್ (t->kind == cdk_attrs)
		  t = t->declarator;
		really_funcdef = (t->kind == cdk_id);
	      }

	    /* Declaring a function type.  Make sure we have a valid
	       type for the function to return.  */
	    ಯದಿ (type == error_mark_ಗಂಟು)
	      ಅನುವರ್ತ;

	    size_varies = ಅಸತ್ಯ;

	    /* Warn about some types functions can't return.  */
	    ಯದಿ (ವೃಕ್ಷ_CODE (type) == FUNCTION_TYPE)
	      {
		ಯದಿ (name)
		  error_at (loc, "%qE declared as function returning a "
		      		 "function", name);
		ಅನ್ಯಥಾ
		  error_at (loc, "type name declared as function "
			    "returning a function");
		type = integer_type_ಗಂಟು;
	      }
	    ಯದಿ (ವೃಕ್ಷ_CODE (type) == ARRAY_TYPE)
	      {
		ಯದಿ (name)
		  error_at (loc, "%qE declared as function returning an array",
		      	    name);
		ಅನ್ಯಥಾ
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
	    ಯದಿ (type_quals)
	      {
		ಧ್ರುವ ಗಣನಾ c_declspec_word ignored_quals_list[] =
		  {
		    cdw_const, cdw_volatile, cdw_restrict, cdw_address_space,
		    cdw_atomic, cdw_ಸಂಖ್ಯೆ_of_elements
		  };
		location_t specs_loc
		  = smallest_type_quals_location (declspecs->locations,
						  ignored_quals_list);
		ಯದಿ (specs_loc == UNKNOWN_LOCATION)
		  specs_loc = declspecs->locations[cdw_typedef];
		ಯದಿ (specs_loc == UNKNOWN_LOCATION)
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
		ಪೂರ್ಣಾಙ್ಕ quals_used = type_quals;
		ಯದಿ (flag_isoc23)
		  quals_used = 0;
		ಅನ್ಯಥಾ ಯದಿ (flag_isoc11)
		  quals_used &= TYPE_QUAL_ATOMIC;
		ಯದಿ (quals_used && VOID_TYPE_P (type) && really_funcdef)
		  pedwarn (specs_loc, 0,
			   "function definition has qualified void "
			   "return type");
		ಅನ್ಯಥಾ
		  warning_at (specs_loc, OPT_Wignored_qualifiers,
			      "type qualifiers ignored on function "
			      "return type");

		/* Ensure an error for restrict on invalid types; the
		   DR#423 resolution is not entirely clear about
		   this.  */
		ಯದಿ (flag_isoc11
		    && (type_quals & TYPE_QUAL_RESTRICT)
		    && (!POINTER_TYPE_P (type)
			|| !C_TYPE_OBJECT_OR_INCOMPLETE_P (ವೃಕ್ಷ_TYPE (type))))
		  error_at (loc, "invalid use of %<restrict%>");
		type = c_build_qualified_type (type, quals_used);
	      }
	    type_quals = TYPE_UNQUALIFIED;

	    type = c_build_function_type (type, arg_types,
					  arg_info->no_named_args_stdarg_p);
	    declarator = declarator->declarator;

	    /* Set the TYPE_CONTEXTs for each tagged type which is local to
	       the formal parameter list of this FUNCTION_TYPE to point to
	       the FUNCTION_TYPE node itself.  */
	    {
	      c_arg_tag *tag;
	      unsigned ix;

	      FOR_EACH_VEC_SAFE_ELT_REVERSE (arg_info->tags, ix, tag)
		TYPE_CONTEXT (tag->type) = type;
	    }
	    ಭಙ್ಗ;
	  }
	ಪಕ್ಷ cdk_pointer:
	  {
	    /* Merge any constancy or volatility into the target type
	       for the pointer.  */
	    ಯದಿ ((type_quals & TYPE_QUAL_ATOMIC)
		&& ವೃಕ್ಷ_CODE (type) == FUNCTION_TYPE)
	      {
		error_at (loc,
			  "%<_Atomic%>-qualified function type");
		type_quals &= ~TYPE_QUAL_ATOMIC;
	      }
	    ಅನ್ಯಥಾ ಯದಿ (pedantic && ವೃಕ್ಷ_CODE (type) == FUNCTION_TYPE
		     && type_quals)
	      pedwarn (loc, OPT_Wpedantic,
		       "ISO C forbids qualified function types");
	    ಯದಿ (type_quals)
	      type = c_build_qualified_type (type, type_quals, orig_qual_type,
					     orig_qual_indirect);
	    orig_qual_type = NULL_ವೃಕ್ಷ;
	    size_varies = ಅಸತ್ಯ;

	    /* When the pointed-to type involves components of variable size,
	       care must be taken to ensure that the size evaluation code is
	       emitted early enough to dominate all the possible later uses
	       and late enough for the variables on which it depends to have
	       been assigned.

	       This is expected to happen automatically when the pointed-to
	       type has a name/declaration of it's own, but special attention
	       is required if the type is anonymous. */
	    ಯದಿ (!TYPE_NAME (type) && c_type_variably_modified_p (type))
	      {
		ತಾರ್ಕಿಕ bind_p = decl_context == TYPENAME
			      || decl_context == FIELD
			      || decl_context == PARM;
		add_decl_ಅಭಿವ್ಯಕ್ತಿ (loc, type, bind_p ? ಅಭಿವ್ಯಕ್ತಿ : ರಿಕ್ತ, ಸತ್ಯ);
	      }

	    type = c_build_pointer_type (type);

	    /* Process type qualifiers (such as const or volatile)
	       that were given inside the `*'.  */
	    type_quals = declarator->u.pointer_quals;

	    declarator = declarator->declarator;
	    ಭಙ್ಗ;
	  }
	ಸ್ವಭಾವ:
	  gcc_unreachable ();
	}
    }
  *decl_attrs = chainon (returned_attrs, *decl_attrs);
  *decl_attrs = chainon (decl_id_attrs, *decl_attrs);

  /* Now TYPE has the actual type, apart from any qualifiers in
     TYPE_QUALS.  */

  /* Warn about address space used for things other than static memory or
     pointers.  */
  address_space = DECODE_QUAL_ADDR_SPACE (type_quals);
  ಯದಿ (!ADDR_SPACE_GENERIC_P (address_space))
    {
      ಯದಿ (decl_context == NORMAL)
	{
	  ವಿಕಲ್ಪ (storage_class)
	    {
	    ಪಕ್ಷ csc_auto:
	      error ("%qs combined with %<auto%> qualifier for %qE",
		     c_addr_space_name (address_space), name);
	      ಭಙ್ಗ;
	    ಪಕ್ಷ csc_register:
	      error ("%qs combined with %<register%> qualifier for %qE",
		     c_addr_space_name (address_space), name);
	      ಭಙ್ಗ;
	    ಪಕ್ಷ csc_none:
	      ಯದಿ (current_function_scope)
		{
		  error ("%qs specified for auto variable %qE",
			 c_addr_space_name (address_space), name);
		  ಭಙ್ಗ;
		}
	      ಭಙ್ಗ;
	    ಪಕ್ಷ csc_static:
	    ಪಕ್ಷ csc_extern:
	    ಪಕ್ಷ csc_typedef:
	      ಭಙ್ಗ;
	    ಸ್ವಭಾವ:
	      gcc_unreachable ();
	    }
	}
      ಅನ್ಯಥಾ ಯದಿ (decl_context == PARM && ವೃಕ್ಷ_CODE (type) != ARRAY_TYPE)
	{
	  ಯದಿ (name)
	    error ("%qs specified for parameter %qE",
		   c_addr_space_name (address_space), name);
	  ಅನ್ಯಥಾ
	    error ("%qs specified for unnamed parameter",
		   c_addr_space_name (address_space));
	}
      ಅನ್ಯಥಾ ಯದಿ (decl_context == FIELD)
	{
	  ಯದಿ (name)
	    error ("%qs specified for structure field %qE",
		   c_addr_space_name (address_space), name);
	  ಅನ್ಯಥಾ
	    error ("%qs specified for structure field",
		   c_addr_space_name (address_space));
	}
    }

  /* Check the type and width of a bit-field.  */
  ಯದಿ (bitfield)
    {
      check_bitfield_type_and_width (loc, &type, width, name);
      /* C11 makes it implementation-defined (6.7.2.1#5) whether
	 atomic types are permitted for bit-fields; we have no code to
	 make bit-field accesses atomic, so disallow them.  */
      ಯದಿ (type_quals & TYPE_QUAL_ATOMIC)
	{
	  ಯದಿ (name)
	    error_at (loc, "bit-field %qE has atomic type", name);
	  ಅನ್ಯಥಾ
	    error_at (loc, "bit-field has atomic type");
	  type_quals &= ~TYPE_QUAL_ATOMIC;
	}
    }

  /* Reject invalid uses of _Alignas.  */
  ಯದಿ (declspecs->alignas_p)
    {
      ಯದಿ (storage_class == csc_typedef)
	error_at (loc, "alignment specified for typedef %qE", name);
      ಅನ್ಯಥಾ ಯದಿ (storage_class == csc_register)
	error_at (loc, "alignment specified for %<register%> object %qE",
		  name);
      ಅನ್ಯಥಾ ಯದಿ (decl_context == PARM)
	{
	  ಯದಿ (name)
	    error_at (loc, "alignment specified for parameter %qE", name);
	  ಅನ್ಯಥಾ
	    error_at (loc, "alignment specified for unnamed parameter");
	}
      ಅನ್ಯಥಾ ಯದಿ (bitfield)
	{
	  ಯದಿ (name)
	    error_at (loc, "alignment specified for bit-field %qE", name);
	  ಅನ್ಯಥಾ
	    error_at (loc, "alignment specified for unnamed bit-field");
	}
      ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_CODE (type) == FUNCTION_TYPE)
	error_at (loc, "alignment specified for function %qE", name);
      ಅನ್ಯಥಾ ಯದಿ (declspecs->align_log != -1 && TYPE_P (type))
	{
	  alignas_align = 1U << declspecs->align_log;
	  ಯದಿ (alignas_align < min_align_of_type (type))
	    {
	      ಯದಿ (name)
		error_at (loc, "%<_Alignas%> specifiers cannot reduce "
			  "alignment of %qE", name);
	      ಅನ್ಯಥಾ
		error_at (loc, "%<_Alignas%> specifiers cannot reduce "
			  "alignment of unnamed field");
	      alignas_align = 0;
	    }
	}
    }

  /* If this is declaring a typedef name, return a TYPE_DECL.  */

  ಯದಿ (storage_class == csc_typedef)
    {
      ವೃಕ್ಷ decl;
      ಯದಿ ((type_quals & TYPE_QUAL_ATOMIC)
	  && ವೃಕ್ಷ_CODE (type) == FUNCTION_TYPE)
	{
	  error_at (loc,
		    "%<_Atomic%>-qualified function type");
	  type_quals &= ~TYPE_QUAL_ATOMIC;
	}
      ಅನ್ಯಥಾ ಯದಿ (pedantic && ವೃಕ್ಷ_CODE (type) == FUNCTION_TYPE
	       && type_quals)
	pedwarn (loc, OPT_Wpedantic,
		 "ISO C forbids qualified function types");
      ಯದಿ (type_quals)
	type = c_build_qualified_type (type, type_quals, orig_qual_type,
				       orig_qual_indirect);
      decl = build_decl (declarator->id_loc,
			 TYPE_DECL, declarator->u.id.id, type);
      ಯದಿ (declspecs->explicit_signed_p)
	C_TYPEDEF_EXPLICITLY_SIGNED (decl) = 1;
      ಯದಿ (declspecs->inline_p)
	pedwarn (loc, 0,"typedef %q+D declared %<inline%>", decl);
      ಯದಿ (declspecs->noreturn_p)
	pedwarn (loc, 0,"typedef %q+D declared %<_Noreturn%>", decl);

      ಯದಿ (warn_cxx_compat && declarator->u.id.id != NULL_ವೃಕ್ಷ)
	{
	  ಸಂರಚನಾ c_binding *b = I_TAG_BINDING (declarator->u.id.id);

	  ಯದಿ (b != ರಿಕ್ತ
	      && b->decl != NULL_ವೃಕ್ಷ
	      && (B_IN_CURRENT_SCOPE (b)
		  || (current_scope == file_scope && B_IN_EXTERNAL_SCOPE (b)))
	      && TYPE_MAIN_VARIANT (b->decl) != TYPE_MAIN_VARIANT (type))
	    {
	      auto_diagnostic_group d;
	      ಯದಿ (warning_at (declarator->id_loc, OPT_Wc___compat,
			      "using %qD as both a typedef and a tag is "
			      "invalid in C++", decl)
		  && b->locus != UNKNOWN_LOCATION)
		inform (b->locus, "originally defined here");
	    }
	}

      ಪ್ರತ್ಯಾಗಮ decl;
    }

  /* If this is a type name (such as, in a cast or sizeof),
     compute the type and return it now.  */

  ಯದಿ (decl_context == TYPENAME || decl_context == GENERIC_ASSOC)
    {
      /* Note that the grammar rejects storage classes in typenames
	 and fields.  */
      gcc_assert (storage_class == csc_none && !threadp
		  && !declspecs->inline_p && !declspecs->noreturn_p);
      ಯದಿ ((type_quals & TYPE_QUAL_ATOMIC)
	  && ವೃಕ್ಷ_CODE (type) == FUNCTION_TYPE)
	{
	  error_at (loc,
		    "%<_Atomic%>-qualified function type");
	  type_quals &= ~TYPE_QUAL_ATOMIC;
	}
      ಅನ್ಯಥಾ ಯದಿ (pedantic && ವೃಕ್ಷ_CODE (type) == FUNCTION_TYPE
	       && type_quals)
	pedwarn (loc, OPT_Wpedantic,
		 "ISO C forbids const or volatile function types");
      ಯದಿ (type_quals)
	type = c_build_qualified_type (type, type_quals, orig_qual_type,
				       orig_qual_indirect);
      ಪ್ರತ್ಯಾಗಮ type;
    }

  ಯದಿ (pedantic && decl_context == FIELD
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

  ಯದಿ (VOID_TYPE_P (type) && decl_context != PARM
      && !((decl_context != FIELD && ವೃಕ್ಷ_CODE (type) != FUNCTION_TYPE)
	    && (storage_class == csc_extern
		|| (current_scope == file_scope
		    && !(storage_class == csc_static
			 || storage_class == csc_register)))))
    {
      error_at (loc, "variable or field %qE declared void", name);
      type = integer_type_ಗಂಟು;
    }

  /* Now create the decl, which may be a VAR_DECL, a PARM_DECL
     or a FUNCTION_DECL, depending on DECL_CONTEXT and TYPE.  */

  {
    ವೃಕ್ಷ decl;

    ಯದಿ (decl_context == PARM)
      {
	ವೃಕ್ಷ promoted_type;
	ತಾರ್ಕಿಕ array_parameter_p = ಅಸತ್ಯ;

	/* A parameter declared as an array of T is really a pointer to T.
	   One declared as a function is really a pointer to a function.  */

	ಯದಿ (ವೃಕ್ಷ_CODE (type) == ARRAY_TYPE)
	  {
	    ಯದಿ (!size_error)
	      *decl_attrs = build_arg_spec_attribute (type, array_parm_static,
						      *decl_attrs);

	    /* Transfer const-ness of array into that of type pointed to.  */
	    type = ವೃಕ್ಷ_TYPE (type);
	    ಯದಿ (orig_qual_type != NULL_ವೃಕ್ಷ)
	      {
		ಯದಿ (orig_qual_indirect == 0)
		  orig_qual_type = ವೃಕ್ಷ_TYPE (orig_qual_type);
		ಅನ್ಯಥಾ
		  orig_qual_indirect--;
	      }
	    ಯದಿ (type_quals)
	      type = c_build_qualified_type (type, type_quals, orig_qual_type,
					     orig_qual_indirect);

	    /* The pointed-to type may need a decl expr (see above).  */
	    ಯದಿ (!TYPE_NAME (type) && c_type_variably_modified_p (type))
	      {
		ತಾರ್ಕಿಕ bind_p = decl_context == TYPENAME
			      || decl_context == FIELD
			      || decl_context == PARM;
		add_decl_ಅಭಿವ್ಯಕ್ತಿ (loc, type, bind_p ? ಅಭಿವ್ಯಕ್ತಿ : ರಿಕ್ತ, ಸತ್ಯ);
	      }

	    type = c_build_pointer_type (type);
	    type_quals = array_ptr_quals;
	    ಯದಿ (type_quals)
	      type = c_build_qualified_type (type, type_quals);

	    /* We don't yet implement attributes in this context.  */
	    ಯದಿ (array_ptr_attrs != NULL_ವೃಕ್ಷ)
	      warning_at (loc, OPT_Wattributes,
			  "attributes in parameter array declarator ignored");

	    size_varies = ಅಸತ್ಯ;
	    array_parameter_p = ಸತ್ಯ;
	  }
	ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_CODE (type) == FUNCTION_TYPE)
	  {
	    ಯದಿ (type_quals & TYPE_QUAL_ATOMIC)
	      {
		error_at (loc,
			  "%<_Atomic%>-qualified function type");
		type_quals &= ~TYPE_QUAL_ATOMIC;
	      }
	    ಅನ್ಯಥಾ ಯದಿ (type_quals)
	      pedwarn (loc, OPT_Wpedantic,
		       "ISO C forbids qualified function types");
	    ಯದಿ (type_quals)
	      type = c_build_qualified_type (type, type_quals);
	    type = c_build_pointer_type (type);
	    type_quals = TYPE_UNQUALIFIED;
	  }
	ಅನ್ಯಥಾ ಯದಿ (type_quals)
	  type = c_build_qualified_type (type, type_quals);

	decl = build_decl (declarator->id_loc,
			   PARM_DECL, declarator->u.id.id, type);
	ಯದಿ (size_varies)
	  C_DECL_VARIABLE_SIZE (decl) = 1;
	C_ARRAY_PARAMETER (decl) = array_parameter_p;

	/* Compute the type actually passed in the parmlist,
	   for the case where there is no prototype.
	   (For example, shorts and chars are passed as ints.)
	   When there is a prototype, this is overridden later.  */

	ಯದಿ (type == error_mark_ಗಂಟು)
	  promoted_type = type;
	ಅನ್ಯಥಾ
	  promoted_type = c_type_promotes_to (type);

	DECL_ARG_TYPE (decl) = promoted_type;
	ಯದಿ (declspecs->inline_p)
	  pedwarn (loc, 0, "parameter %q+D declared %<inline%>", decl);
	ಯದಿ (declspecs->noreturn_p)
	  pedwarn (loc, 0, "parameter %q+D declared %<_Noreturn%>", decl);
      }
    ಅನ್ಯಥಾ ಯದಿ (decl_context == FIELD)
      {
	/* Note that the grammar rejects storage classes in typenames
	   and fields.  */
	gcc_assert (storage_class == csc_none && !threadp
		    && !declspecs->inline_p && !declspecs->noreturn_p);

	/* Structure field.  It may not be a function.  */

	ಯದಿ (ವೃಕ್ಷ_CODE (type) == FUNCTION_TYPE)
	  {
	    error_at (loc, "field %qE declared as a function", name);
	    type = c_build_pointer_type (type);
	  }
	ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_CODE (type) != ERROR_MARK
		 && !COMPLETE_OR_UNBOUND_ARRAY_TYPE_P (type))
	  {
	    ಯದಿ (name)
	      error_at (loc, "field %qE has incomplete type", name);
	    ಅನ್ಯಥಾ
	      error_at (loc, "unnamed field has incomplete type");
	    type = error_mark_ಗಂಟು;
	  }
	ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_CODE (type) == ARRAY_TYPE
		 && TYPE_DOMAIN (type) == NULL_ವೃಕ್ಷ)
	  {
	    /* We have a flexible array member through a typedef.
	       Set suitable range.  Whether this is a correct position
	       for a flexible array member will be determined elsewhere.  */
	    ಯದಿ (!in_system_header_at (ಒಳಹರಿವು_location))
	      pedwarn_c90 (loc, OPT_Wpedantic, "ISO C90 does not "
			   "support flexible array members");
	    type = build_distinct_type_copy (TYPE_MAIN_VARIANT (type));
	    TYPE_DOMAIN (type) = build_index_type (NULL_ವೃಕ್ಷ);
	    ಯದಿ (orig_qual_indirect == 0)
	      orig_qual_type = NULL_ವೃಕ್ಷ;
	  }
	ಯದಿ (type != error_mark_ಗಂಟು
	    && !verify_type_context (loc, TCTX_FIELD, type))
	  type = error_mark_ಗಂಟು;

	type = c_build_qualified_type (type, type_quals, orig_qual_type,
				       orig_qual_indirect);
	decl = build_decl (declarator->id_loc,
			   FIELD_DECL, declarator->u.id.id, type);
	DECL_NONADDRESSABLE_P (decl) = bitfield;
	ಯದಿ (bitfield && !declarator->u.id.id)
	  DECL_PADDING_P (decl) = 1;

	ಯದಿ (size_varies)
	  C_DECL_VARIABLE_SIZE (decl) = 1;
      }
    ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_CODE (type) == FUNCTION_TYPE)
      {
	ಯದಿ (storage_class == csc_register || threadp || constexprp)
	  {
	    error_at (loc, "invalid storage class for function %qE", name);
	  }
	ಅನ್ಯಥಾ ಯದಿ (current_scope != file_scope)
	  {
	    /* Function declaration not at file scope.  Storage
	       classes other than `extern' are not allowed, C99
	       6.7.1p5, and `extern' makes no difference.  However,
	       GCC allows 'auto', perhaps with 'inline', to support
	       nested functions.  */
	    ಯದಿ (storage_class == csc_auto)
		pedwarn (loc, OPT_Wpedantic,
			 "invalid storage class for function %qE", name);
	    ಅನ್ಯಥಾ ಯದಿ (storage_class == csc_static)
	      {
		error_at (loc, "invalid storage class for function %qE", name);
		ಯದಿ (funcdef_flag)
		  storage_class = declspecs->storage_class = csc_none;
		ಅನ್ಯಥಾ
		  ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;
	      }
	  }

	decl = build_decl (declarator->id_loc,
			   FUNCTION_DECL, declarator->u.id.id, type);
	decl = build_decl_attribute_variant (decl, decl_attr);

	ಯದಿ (type_quals & TYPE_QUAL_ATOMIC)
	  {
	    error_at (loc,
		      "%<_Atomic%>-qualified function type");
	    type_quals &= ~TYPE_QUAL_ATOMIC;
	  }
	ಅನ್ಯಥಾ ಯದಿ (pedantic && type_quals && !DECL_IN_SYSTEM_HEADER (decl))
	  pedwarn (loc, OPT_Wpedantic,
		   "ISO C forbids qualified function types");

	/* Every function declaration is an external reference
	   (DECL_EXTERNAL) except for those which are not at file
	   scope and are explicitly declared "auto".  This is
	   forbidden by standard C (C99 6.7.1p5) and is interpreted by
	   GCC to signify a forward declaration of a nested function.  */
	ಯದಿ (storage_class == csc_auto && current_scope != file_scope)
	  DECL_EXTERNAL (decl) = 0;
	/* In C99, a function which is declared 'inline' with 'extern'
	   is not an external reference (which is confusing).  It
	   means that the later definition of the function must be output
	   in this file, C99 6.7.4p6.  In GNU C89, a function declared
	   'extern inline' is an external reference.  */
	ಅನ್ಯಥಾ ಯದಿ (declspecs->inline_p && storage_class != csc_static)
	  DECL_EXTERNAL (decl) = ((storage_class == csc_extern)
				  == flag_gnu89_inline);
	ಅನ್ಯಥಾ
	  DECL_EXTERNAL (decl) = !initialized;

	/* Record absence of global scope for `static' or `auto'.  */
	ವೃಕ್ಷ_PUBLIC (decl)
	  = !(storage_class == csc_static || storage_class == csc_auto);

	/* For a function definition, record the argument information
	   block where store_parm_decls will look for it.  */
	ಯದಿ (funcdef_flag)
	  current_function_arg_info = arg_info;

	ಯದಿ (declspecs->default_int_p)
	  C_FUNCTION_IMPLICIT_INT (decl) = 1;

	/* Record presence of `inline' and `_Noreturn', if it is
	   reasonable.  */
	ಯದಿ (flag_hosted && MAIN_NAME_P (declarator->u.id.id))
	  {
	    ಯದಿ (declspecs->inline_p)
	      pedwarn (loc, 0, "cannot inline function %<main%>");
	    ಯದಿ (declspecs->noreturn_p)
	      pedwarn (loc, 0, "%<main%> declared %<_Noreturn%>");
	  }
	ಅನ್ಯಥಾ
	  {
	    ಯದಿ (declspecs->inline_p)
	      /* Record that the function is declared `inline'.  */
	      DECL_DECLARED_INLINE_P (decl) = 1;
	    ಯದಿ (declspecs->noreturn_p)
	      {
		ಯದಿ (flag_isoc99)
		  pedwarn_c99 (loc, OPT_Wpedantic,
			       "ISO C99 does not support %<_Noreturn%>");
		ಅನ್ಯಥಾ
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
	ಯದಿ (!initialized
	    && ವೃಕ್ಷ_PUBLIC (decl)
	    && current_scope != file_scope)
	  {
	    ವೃಕ್ಷ global_decl  = identifier_global_ಮೌಲ್ಯ (declarator->u.id.id);
	    ವೃಕ್ಷ visible_decl = lookup_name (declarator->u.id.id);

	    ಯದಿ (global_decl
		&& global_decl != visible_decl
		&& VAR_OR_FUNCTION_DECL_P (global_decl)
		&& !ವೃಕ್ಷ_PUBLIC (global_decl))
	      error_at (loc, "function previously declared %<static%> "
			"redeclared %<extern%>");
	  }
      }
    ಅನ್ಯಥಾ
      {
	/* It's a variable.  */
	/* An uninitialized decl with `extern' is a reference.  */
	ಪೂರ್ಣಾಙ್ಕ extern_ref = !initialized && storage_class == csc_extern;

	ಯದಿ (constexprp)
	  {
	    /* The type of a constexpr variable must not be variably
	       modified, volatile, atomic or restrict qualified or
	       have a member with such a qualifier.  const
	       qualification is implicitly added, and, at file scope,
	       has internal linkage.  */
	    ಯದಿ (c_type_variably_modified_p (type))
	      error_at (loc, "%<constexpr%> object has variably modified "
			"type");
	    ಯದಿ (type_quals
		& (TYPE_QUAL_VOLATILE | TYPE_QUAL_RESTRICT | TYPE_QUAL_ATOMIC))
	      error_at (loc, "invalid qualifiers for %<constexpr%> object");
	    ಅನ್ಯಥಾ
	      {
		ವೃಕ್ಷ type_no_array = strip_array_types (type);
		ಯದಿ (RECORD_OR_UNION_TYPE_P (type_no_array)
		    && C_TYPE_FIELDS_NON_CONSTEXPR (type_no_array))
		  error_at (loc, "invalid qualifiers for field of "
			    "%<constexpr%> object");
	      }
	    type_quals |= TYPE_QUAL_CONST;
	    ಯದಿ (current_scope == file_scope)
	      storage_class = csc_static;
	  }

	type = c_build_qualified_type (type, type_quals, orig_qual_type,
				       orig_qual_indirect);

	/* C99 6.2.2p7: It is invalid (compile-time undefined
	   behavior) to create an 'extern' declaration for a
	   variable if there is a global declaration that is
	   'static' and the global declaration is not visible.
	   (If the static declaration _is_ currently visible,
	   the 'extern' declaration is taken to refer to that decl.) */
	ಯದಿ (extern_ref && current_scope != file_scope)
	  {
	    ವೃಕ್ಷ global_decl  = identifier_global_ಮೌಲ್ಯ (declarator->u.id.id);
	    ವೃಕ್ಷ visible_decl = lookup_name (declarator->u.id.id);

	    ಯದಿ (global_decl
		&& global_decl != visible_decl
		&& VAR_P (global_decl)
		&& !ವೃಕ್ಷ_PUBLIC (global_decl))
	      error_at (loc, "variable previously declared %<static%> "
			"redeclared %<extern%>");
	  }

	decl = build_decl (declarator->id_loc,
			   VAR_DECL, declarator->u.id.id, type);
	ಯದಿ (size_varies)
	  C_DECL_VARIABLE_SIZE (decl) = 1;
	ಯದಿ (constexprp)
	  C_DECL_DECLARED_CONSTEXPR (decl) = 1;

	ಯದಿ (declspecs->inline_p)
	  pedwarn (loc, 0, "variable %q+D declared %<inline%>", decl);
	ಯದಿ (declspecs->noreturn_p)
	  pedwarn (loc, 0, "variable %q+D declared %<_Noreturn%>", decl);

	/* At file scope, an initialized extern declaration may follow
	   a static declaration.  In that case, DECL_EXTERNAL will be
	   reset later in start_decl.  */
	DECL_EXTERNAL (decl) = (storage_class == csc_extern);

	/* At file scope, the presence of a `static' or `register' storage
	   class specifier, or the absence of all storage class specifiers
	   makes this declaration a definition (perhaps tentative).  Also,
	   the absence of `static' makes it public.  */
	ಯದಿ (current_scope == file_scope)
	  {
	    ವೃಕ್ಷ_PUBLIC (decl) = storage_class != csc_static;
	    ವೃಕ್ಷ_STATIC (decl) = !extern_ref;
	  }
	/* Not at file scope, only `static' makes a static definition.  */
	ಅನ್ಯಥಾ
	  {
	    ವೃಕ್ಷ_STATIC (decl) = (storage_class == csc_static);
	    ವೃಕ್ಷ_PUBLIC (decl) = extern_ref;
	  }

	// NB: Set a tentative TLS model to avoid tls_model attribute
	// warnings due to lack of thread storage duration.  It will
	// be updated by c_decl_attributes later.
	ಯದಿ (threadp)
	  set_decl_tls_model (decl, TLS_MODEL_REAL);
      }

    ಯದಿ ((storage_class == csc_extern
	 || (storage_class == csc_none
	     && ವೃಕ್ಷ_CODE (type) == FUNCTION_TYPE
	     && !funcdef_flag))
	&& c_type_variably_modified_p (type))
      {
	/* C99 6.7.5.2p2 */
	ಯದಿ (ವೃಕ್ಷ_CODE (type) == FUNCTION_TYPE)
	  error_at (loc, "non-nested function with variably modified type");
	ಅನ್ಯಥಾ
	  error_at (loc, "object with variably modified type must have "
	      	    "no linkage");
      }

    /* For nested functions disqualify ones taking VLAs by value
       from inlining since the middle-end cannot deal with this.
       ???  We should arrange for those to be passed by reference
       with emitting the copy on the caller side in the frontend.  */
    ಯದಿ (storage_class == csc_none
	&& ವೃಕ್ಷ_CODE (type) == FUNCTION_TYPE)
      ಪ್ರತಿ (ವೃಕ್ಷ al = TYPE_ARG_TYPES (type); al; al = ವೃಕ್ಷ_CHAIN (al))
	{
	  ವೃಕ್ಷ arg = ವೃಕ್ಷ_ಮೌಲ್ಯ (al);
	  ಯದಿ (arg != error_mark_ಗಂಟು
	      && C_TYPE_VARIABLE_SIZE (arg))
	    {
	      DECL_UNINLINABLE (decl) = 1;
	      ಭಙ್ಗ;
	    }
	}

    /* Record `register' declaration for warnings on &
       and in case doing stupid register allocation.  */

    ಯದಿ (storage_class == csc_register
	&& ವೃಕ್ಷ_CODE (type) != FUNCTION_TYPE)
      {
	C_DECL_REGISTER (decl) = 1;
	DECL_REGISTER (decl) = 1;
      }

    /* Record constancy and volatility.  */
    c_apply_type_quals_to_decl (type_quals, decl);

    /* Apply _Alignas specifiers.  */
    ಯದಿ (alignas_align)
      {
	SET_DECL_ALIGN (decl, alignas_align * BITS_PER_UNIT);
	DECL_USER_ALIGN (decl) = 1;
      }

    /* If a type has volatile components, it should be stored in memory.
       Otherwise, the fact that those components are volatile
       will be ignored, and would even crash the compiler.
       Of course, this only makes sense on  VAR,PARM, and RESULT decl's.   */
    ಯದಿ (C_TYPE_FIELDS_VOLATILE (ವೃಕ್ಷ_TYPE (decl))
	&& (VAR_P (decl) ||  ವೃಕ್ಷ_CODE (decl) == PARM_DECL
	  || ವೃಕ್ಷ_CODE (decl) == RESULT_DECL))
      {
	/* It is not an error for a structure with volatile fields to
	   be declared register, but reset DECL_REGISTER since it
	   cannot actually go in a register.  */
	ಪೂರ್ಣಾಙ್ಕ was_reg = C_DECL_REGISTER (decl);
	C_DECL_REGISTER (decl) = 0;
	DECL_REGISTER (decl) = 0;
	c_mark_addressable (decl);
	C_DECL_REGISTER (decl) = was_reg;
      }

  /* This is the earliest point at which we might know the assembler
     name of a variable.  Thus, if it's known before this, die horribly.  */
    gcc_assert (!HAS_DECL_ASSEMBLER_NAME_P (decl)
		|| !DECL_ASSEMBLER_NAME_SET_P (decl));

    ಯದಿ (warn_cxx_compat
	&& VAR_P (decl)
	&& ವೃಕ್ಷ_PUBLIC (decl)
	&& ವೃಕ್ಷ_STATIC (decl)
	&& (RECORD_OR_UNION_TYPE_P (ವೃಕ್ಷ_TYPE (decl))
	    || ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (decl)) == ENUMERAL_TYPE)
	&& TYPE_NAME (ವೃಕ್ಷ_TYPE (decl)) == NULL_ವೃಕ್ಷ)
      warning_at (DECL_SOURCE_LOCATION (decl), OPT_Wc___compat,
		  "non-local variable %qD with anonymous type is "
		  "questionable in C++", decl);

    ಪ್ರತ್ಯಾಗಮ decl;
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
grokparms (ಸಂರಚನಾ c_arg_info *arg_info, ತಾರ್ಕಿಕ funcdef_flag)
{
  ವೃಕ್ಷ arg_types = arg_info->types;

  ಯದಿ (funcdef_flag && arg_info->had_vla_unspec)
    {
      /* A function definition isn't function prototype scope C99 6.2.1p4.  */
      /* C99 6.7.5.2p4 */
      error ("%<[*]%> not allowed in other than function prototype scope");
    }

  ಯದಿ (arg_types == NULL_ವೃಕ್ಷ && !funcdef_flag && !flag_isoc23
      && !in_system_header_at (ಒಳಹರಿವು_location))
    warning (OPT_Wstrict_prototypes,
	     "function declaration isn%'t a prototype");

  ಯದಿ (arg_types == error_mark_ಗಂಟು)
    /* Don't set TYPE_ARG_TYPES in this case.  */
    ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;

  ಅನ್ಯಥಾ ಯದಿ (arg_types && ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_ಮೌಲ್ಯ (arg_types)) == IDENTIFIER_ಗಂಟು)
    {
      ಯದಿ (!funcdef_flag)
	{
	  permerror_opt (ಒಳಹರಿವು_location,
			 OPT_Wdeclaration_missing_parameter_type,
			 "parameter names (without types) in "
			 "function declaration");
	  arg_info->parms = NULL_ವೃಕ್ಷ;
	}
      ಅನ್ಯಥಾ
	arg_info->parms = arg_info->types;

      arg_info->types = NULL_ವೃಕ್ಷ;
      ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;
    }
  ಅನ್ಯಥಾ
    {
      ವೃಕ್ಷ parm, type, typelt;
      unsigned ಪೂರ್ಣಾಙ್ಕ parmno;

      /* In C23, convert () to (void).  */
      ಯದಿ (flag_isoc23
	  && !arg_types
	  && !arg_info->parms
	  && !arg_info->no_named_args_stdarg_p)
	{
	  arg_types = arg_info->types = void_list_ಗಂಟು;
	  arg_info->c23_empty_parens = 1;
	}

      /* If there is a parameter of incomplete type in a definition,
	 this is an error.  In a declaration this is valid, and a
	 struct or union type may be completed later, before any calls
	 or definition of the function.  In the case where the tag was
	 first declared within the parameter list, a warning has
	 already been given.  If a parameter has void type, then
	 this has already received an error (constraint violation in C2Y,
	 previously implicitly undefined behavior).  */

      ಪ್ರತಿ (parm = arg_info->parms, typelt = arg_types, parmno = 1;
	   parm;
	   parm = DECL_CHAIN (parm), typelt = ವೃಕ್ಷ_CHAIN (typelt), parmno++)
	{
	  type = ವೃಕ್ಷ_ಮೌಲ್ಯ (typelt);
	  ಯದಿ (type == error_mark_ಗಂಟು)
	    ಅನುವರ್ತ;

	  ಯದಿ (!COMPLETE_TYPE_P (type))
	    {
	      ಯದಿ (funcdef_flag)
		{
		  ಯದಿ (DECL_NAME (parm))
		    error_at (ಒಳಹರಿವು_location,
			      "parameter %u (%q+D) has incomplete type",
			      parmno, parm);
		  ಅನ್ಯಥಾ
		    error_at (DECL_SOURCE_LOCATION (parm),
			      "parameter %u has incomplete type",
			      parmno);

		  ವೃಕ್ಷ_ಮೌಲ್ಯ (typelt) = error_mark_ಗಂಟು;
		  ವೃಕ್ಷ_TYPE (parm) = error_mark_ಗಂಟು;
		  arg_types = NULL_ವೃಕ್ಷ;
		}
	    }

	  ಯದಿ (DECL_NAME (parm) && ವೃಕ್ಷ_USED (parm))
	    warn_if_shadowing (parm);
	}
      ಪ್ರತ್ಯಾಗಮ arg_types;
    }
}

/* Allocate and initialize a c_arg_info structure from the parser's
   obstack.  */

ಸಂರಚನಾ c_arg_info *
build_arg_info (ಶೂನ್ಯ)
{
  ಸಂರಚನಾ c_arg_info *ret = XOBNEW (&parser_obstack, ಸಂರಚನಾ c_arg_info);
  ret->parms = NULL_ವೃಕ್ಷ;
  ret->tags = ರಿಕ್ತ;
  ret->types = NULL_ವೃಕ್ಷ;
  ret->others = NULL_ವೃಕ್ಷ;
  ret->pending_sizes = ರಿಕ್ತ;
  ret->had_vla_unspec = 0;
  ret->no_named_args_stdarg_p = 0;
  ret->c23_empty_parens = 0;
  ಪ್ರತ್ಯಾಗಮ ret;
}

/* Take apart the current scope and return a c_arg_info structure with
   info on a parameter list just parsed.

   This structure is later fed to 'grokparms' and 'store_parm_decls'.

   ELLIPSIS being true means the argument list ended in '...' so don't
   append a sentinel (void_list_node) to the end of the type-list.

   EXPR is NULL or an expression that needs to be evaluated for the
   side effects of array size expressions in the parameters.  */

ಸಂರಚನಾ c_arg_info *
get_parm_info (ತಾರ್ಕಿಕ ellipsis, ವೃಕ್ಷ ಅಭಿವ್ಯಕ್ತಿ)
{
  ಸಂರಚನಾ c_binding *b = current_scope->bindings;
  ಸಂರಚನಾ c_arg_info *arg_info = build_arg_info ();

  ವೃಕ್ಷ parms = NULL_ವೃಕ್ಷ;
  vec<c_arg_tag, va_gc> *tags = ರಿಕ್ತ;
  ವೃಕ್ಷ types = NULL_ವೃಕ್ಷ;
  ವೃಕ್ಷ others = NULL_ವೃಕ್ಷ;

  ತಾರ್ಕಿಕ gave_void_only_once_err = ಅಸತ್ಯ;

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
  ಯದಿ (b->prev == 0			    /* one binding */
      && ವೃಕ್ಷ_CODE (b->decl) == PARM_DECL   /* which is a parameter */
      && !DECL_NAME (b->decl)               /* anonymous */
      && VOID_TYPE_P (ವೃಕ್ಷ_TYPE (b->decl))) /* of void type */
    {
      ಯದಿ (TYPE_QUALS (ವೃಕ್ಷ_TYPE (b->decl)) != TYPE_UNQUALIFIED
	  || C_DECL_REGISTER (b->decl))
	error_at (b->locus, "%<void%> as only parameter may not be qualified");

      /* There cannot be an ellipsis.  */
      ಯದಿ (ellipsis)
	error_at (b->locus, "%<void%> must be the only parameter");

      arg_info->types = void_list_ಗಂಟು;
      ಪ್ರತ್ಯಾಗಮ arg_info;
    }

  ಯದಿ (!ellipsis)
    types = void_list_ಗಂಟು;

  /* Break up the bindings list into parms, tags, types, and others;
     apply sanity checks; purge the name-to-decl bindings.  */
  ಯಾವತ್ (b)
    {
      ವೃಕ್ಷ decl = b->decl;
      ವೃಕ್ಷ type = ವೃಕ್ಷ_TYPE (decl);
      c_arg_tag tag;
      ಧ್ರುವ ವರ್ಣ *keyword;

      ವಿಕಲ್ಪ (ವೃಕ್ಷ_CODE (decl))
	{
	ಪಕ್ಷ PARM_DECL:
	  ಯದಿ (b->id)
	    {
	      gcc_assert (I_ಚಿಹ್ನೆ_BINDING (b->id) == b);
	      I_ಚಿಹ್ನೆ_BINDING (b->id) = b->shadowed;
	    }

	  /* Check for forward decls that never got their actual decl.  */
	  ಯದಿ (ವೃಕ್ಷ_ASM_WRITTEN (decl))
	    error_at (b->locus,
		      "parameter %q+D has just a forward declaration", decl);
	  /* Check for (..., void, ...) and named void parameters and issue an
	     error.  */
	  ಅನ್ಯಥಾ ಯದಿ (VOID_TYPE_P (type))
	    {
	      ಯದಿ (!gave_void_only_once_err)
		{
		  error_at (b->locus,
			    "%<void%> must be the only parameter and unnamed");
		  gave_void_only_once_err = ಸತ್ಯ;
		}
	    }
	  ಅನ್ಯಥಾ
	    {
	      /* Valid parameter, add it to the list.  */
	      DECL_CHAIN (decl) = parms;
	      parms = decl;

	      /* Since there is a prototype, args are passed in their
		 declared types.  The back end may override this later.  */
	      DECL_ARG_TYPE (decl) = type;
	      types = ವೃಕ್ಷ_cons (0, type, types);
	    }
	  ಭಙ್ಗ;

	ಪಕ್ಷ ENUMERAL_TYPE: keyword = "enum"; ಗಚ್ಛ tag;
	ಪಕ್ಷ UNION_TYPE:    keyword = "union"; ಗಚ್ಛ tag;
	ಪಕ್ಷ RECORD_TYPE:   keyword = "struct"; ಗಚ್ಛ tag;
	tag:
	  /* Types may not have tag-names, in which case the type
	     appears in the bindings list with b->id NULL.  */
	  ಯದಿ (b->id)
	    {
	      gcc_assert (I_TAG_BINDING (b->id) == b);
	      I_TAG_BINDING (b->id) = b->shadowed;
	    }

	  /* Warn about any struct, union or enum tags defined in a
	     parameter list.  The scope of such types is limited to
	     the parameter list, which is rarely if ever desirable
	     (it's impossible to call such a function with type-
	     correct arguments).  An anonymous union parm type is
	     meaningful as a GNU extension, so don't warn for that.  */
	  ಯದಿ (ವೃಕ್ಷ_CODE (decl) != UNION_TYPE || b->id != NULL_ವೃಕ್ಷ)
	    {
	      ಯದಿ (b->id)
		{
		  /* The %s will be one of 'struct', 'union', or 'enum'.  */
		  ಯದಿ (!flag_isoc23 || !COMPLETE_TYPE_P (decl))
		    warning_at (b->locus, 0,
				"%<%s %E%> declared inside parameter list"
				" will not be visible outside of this definition or"
				" declaration", keyword, b->id);
		}
	      ಅನ್ಯಥಾ
		/* The %s will be one of 'struct', 'union', or 'enum'.  */
		warning_at (b->locus, 0,
			    "anonymous %s declared inside parameter list"
			    " will not be visible outside of this definition or"
			    " declaration", keyword);
	    }

	  tag.id = b->id;
	  tag.type = decl;
	  vec_safe_ತಳ್ಳು (tags, tag);
	  ಭಙ್ಗ;

	ಪಕ್ಷ FUNCTION_DECL:
	  /* FUNCTION_DECLs appear when there is an implicit function
	     declaration in the parameter list.  */
	  gcc_assert (b->nested || seen_error ());
	  ಗಚ್ಛ set_shadowed;

	ಪಕ್ಷ CONST_DECL:
	ಪಕ್ಷ TYPE_DECL:
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

	ಪಕ್ಷ ERROR_MARK:
	set_shadowed:
	  /* error_mark_node appears here when we have an undeclared
	     variable.  Just throw it away.  */
	  ಯದಿ (b->id)
	    {
	      gcc_assert (I_ಚಿಹ್ನೆ_BINDING (b->id) == b);
	      I_ಚಿಹ್ನೆ_BINDING (b->id) = b->shadowed;
	    }
	  ಭಙ್ಗ;

	  /* Other things that might be encountered.  */
	ಪಕ್ಷ LABEL_DECL:
	ಪಕ್ಷ VAR_DECL:
	ಸ್ವಭಾವ:
	  gcc_unreachable ();
	}

      b = free_binding_and_advance (b);
    }

  arg_info->parms = parms;
  arg_info->tags = tags;
  arg_info->types = types;
  arg_info->others = others;
  arg_info->pending_sizes = ಅಭಿವ್ಯಕ್ತಿ;
  arg_info->no_named_args_stdarg_p = ellipsis && !types;
  ಪ್ರತ್ಯಾಗಮ arg_info;
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

ಸಂರಚನಾ c_typespec
parser_xref_tag (location_t loc, ಗಣನಾ ವೃಕ್ಷ_code code, ವೃಕ್ಷ name,
		 ತಾರ್ಕಿಕ have_std_attrs, ವೃಕ್ಷ attrs, ತಾರ್ಕಿಕ has_enum_type_specifier)
{
  ಸಂರಚನಾ c_typespec ret;
  ವೃಕ್ಷ ref;
  location_t refloc;

  ret.ಅಭಿವ್ಯಕ್ತಿ = NULL_ವೃಕ್ಷ;
  ret.ಅಭಿವ್ಯಕ್ತಿ_const_operands = ಸತ್ಯ;
  ret.has_enum_type_specifier = has_enum_type_specifier;

  /* If a cross reference is requested, look up the type already
     defined for this tag and return it.  If an enum type specifier is
     present, only a definition in the current scope is relevant.  */

  ref = lookup_tag (code, name, has_enum_type_specifier, &refloc);

  /* If the visible type is still being defined, see if there is
     an earlier definition (which may be complete).  We do not
     have to loop because nested redefinitions are not allowed.  */
  ಯದಿ (flag_isoc23 && ref && C_TYPE_BEING_DEFINED (ref))
    {
      ವೃಕ್ಷ vis = previous_tag (ref);
      ಯದಿ (vis)
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
  ret.kind = (ref
	      ? (have_std_attrs ? ctsk_tagref_attrs : ctsk_tagref)
	      : (have_std_attrs ? ctsk_tagfirstref_attrs : ctsk_tagfirstref));
  ಯದಿ (ref && ವೃಕ್ಷ_CODE (ref) == code)
    {
      decl_attributes (&ref, attrs, (ಪೂರ್ಣಾಙ್ಕ) ATTR_FLAG_TYPE_IN_PLACE);
      ಯದಿ (C_TYPE_DEFINED_IN_STRUCT (ref)
	  && loc != UNKNOWN_LOCATION
	  && warn_cxx_compat)
	{
	  auto_diagnostic_group d;
	  ವಿಕಲ್ಪ (code)
	    {
	    ಪಕ್ಷ ENUMERAL_TYPE:
	      ಯದಿ (warning_at (loc, OPT_Wc___compat,
			      ("enum type defined in struct or union "
			       "is not visible in C++")))
		  inform (refloc, "enum type defined here");
	      ಭಙ್ಗ;
	    ಪಕ್ಷ RECORD_TYPE:
	      ಯದಿ (warning_at (loc, OPT_Wc___compat,
			      ("struct defined in struct or union "
			       "is not visible in C++")))
		inform (refloc, "struct defined here");
	      ಭಙ್ಗ;
	    ಪಕ್ಷ UNION_TYPE:
	      ಯದಿ (warning_at (loc, OPT_Wc___compat,
			      ("union defined in struct or union "
			       "is not visible in C++")))
		inform (refloc, "union defined here");
	      ಭಙ್ಗ;
	    ಸ್ವಭಾವ:
	      gcc_unreachable();
	    }
	}

      ret.spec = ref;
      ಪ್ರತ್ಯಾಗಮ ret;
    }

  /* If no such tag is yet defined, create a forward-reference node
     and record it as the "definition".
     When a real declaration of this type is found,
     the forward-reference will be altered into a real type.  */

  ref = make_ಗಂಟು (code);
  ಯದಿ (flag_isoc23 || code == ENUMERAL_TYPE)
    SET_TYPE_STRUCTURAL_EQUALITY (ref);
  ಯದಿ (code == ENUMERAL_TYPE)
    {
      /* Give the type a default layout like unsigned int
	 to avoid crashing if it does not get defined.  */
      SET_TYPE_MODE (ref, TYPE_MODE (unsigned_type_ಗಂಟು));
      SET_TYPE_ALIGN (ref, TYPE_ALIGN (unsigned_type_ಗಂಟು));
      TYPE_USER_ALIGN (ref) = 0;
      TYPE_UNSIGNED (ref) = 1;
      TYPE_PRECISION (ref) = TYPE_PRECISION (unsigned_type_ಗಂಟು);
      TYPE_MIN_ಮೌಲ್ಯ (ref) = TYPE_MIN_ಮೌಲ್ಯ (unsigned_type_ಗಂಟು);
      TYPE_MAX_ಮೌಲ್ಯ (ref) = TYPE_MAX_ಮೌಲ್ಯ (unsigned_type_ಗಂಟು);
      ENUM_FIXED_UNDERLYING_TYPE_P (ref) = has_enum_type_specifier;
    }

  pushtag (loc, name, ref);
  decl_attributes (&ref, attrs, (ಪೂರ್ಣಾಙ್ಕ) ATTR_FLAG_TYPE_IN_PLACE);
  ಯದಿ (in_underspecified_init)
    error_at (loc, "%qT declared in underspecified object initializer",
	      ref);

  ret.spec = ref;
  ಪ್ರತ್ಯಾಗಮ ret;
}

/* Get the struct, enum or union (CODE says which) with tag NAME.
   Define the tag as a forward-reference if it is not defined.
   Return a tree for the type.  */

ವೃಕ್ಷ
xref_tag (ಗಣನಾ ವೃಕ್ಷ_code code, ವೃಕ್ಷ name)
{
  ಪ್ರತ್ಯಾಗಮ parser_xref_tag (ಒಳಹರಿವು_location, code, name, ಅಸತ್ಯ, NULL_ವೃಕ್ಷ,
			  ಅಸತ್ಯ).spec;
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
start_struct (location_t loc, ಗಣನಾ ವೃಕ್ಷ_code code, ವೃಕ್ಷ name,
	      ವರ್ಗ c_struct_parse_info **enclosing_struct_parse_info)
{
  /* If there is already a tag defined at this scope
     (as a forward reference), just return it.  */

  ವೃಕ್ಷ ref = NULL_ವೃಕ್ಷ;
  location_t refloc = UNKNOWN_LOCATION;

  ಯದಿ (name != NULL_ವೃಕ್ಷ)
    ref = lookup_tag (code, name, ಸತ್ಯ, &refloc);

  /* For C23, even if we already have a completed definition,
     we do not use it. We will check for consistency later.
     If we are in a nested redefinition the type is not
     complete. We will then detect this below.  */
  ಯದಿ (flag_isoc23 && ref && TYPE_SIZE (ref))
    ref = NULL_ವೃಕ್ಷ;

  ಯದಿ (ref && ವೃಕ್ಷ_CODE (ref) == code)
    {
      ಯದಿ (TYPE_STUB_DECL (ref))
	refloc = DECL_SOURCE_LOCATION (TYPE_STUB_DECL (ref));

      ಯದಿ (TYPE_SIZE (ref))
	{
	  auto_diagnostic_group d;
	  ಯದಿ (code == UNION_TYPE)
	    error_at (loc, "redefinition of %<union %E%>", name);
	  ಅನ್ಯಥಾ
	    error_at (loc, "redefinition of %<struct %E%>", name);
	  ಯದಿ (refloc != UNKNOWN_LOCATION)
	    inform (refloc, "originally defined here");
	  /* Don't create structures using a name already in use.  */
	  ref = NULL_ವೃಕ್ಷ;
	}
      ಅನ್ಯಥಾ ಯದಿ (C_TYPE_BEING_DEFINED (ref))
	{
	  ಯದಿ (code == UNION_TYPE)
	    error_at (loc, "nested redefinition of %<union %E%>", name);
	  ಅನ್ಯಥಾ
	    error_at (loc, "nested redefinition of %<struct %E%>", name);
	  /* Don't bother to report "originally defined here" for a
	     nested redefinition; the original definition should be
	     obvious.  */
	  /* Don't create structures that contain themselves.  */
	  ref = NULL_ವೃಕ್ಷ;
	}
    }

  /* Otherwise create a forward-reference just so the tag is in scope.  */

  ಯದಿ (ref == NULL_ವೃಕ್ಷ || ವೃಕ್ಷ_CODE (ref) != code)
    {
      ref = make_ಗಂಟು (code);
      ಯದಿ (flag_isoc23)
	SET_TYPE_STRUCTURAL_EQUALITY (ref);
      pushtag (loc, name, ref);
    }

  C_TYPE_BEING_DEFINED (ref) = 1;
  ಪ್ರತಿ (ವೃಕ್ಷ v = TYPE_MAIN_VARIANT (ref); v; v = TYPE_NEXT_VARIANT (v))
    TYPE_PACKED (v) = flag_pack_struct;

  *enclosing_struct_parse_info = struct_parse_info;
  struct_parse_info = ನೂತನ c_struct_parse_info ();
  struct_parse_info->refloc = refloc;

  /* FIXME: This will issue a warning for a use of a type defined
     within a statement expr used within sizeof, et. al.  This is not
     terribly serious as C++ doesn't permit statement exprs within
     sizeof anyhow.  */
  ಯದಿ (warn_cxx_compat
      && (in_sizeof || in_typeof || in_alignof || in_countof))
    warning_at (loc, OPT_Wc___compat,
		"defining type in %qs expression is invalid in C++",
		(in_sizeof ? "sizeof"
		 : in_typeof ? "typeof"
		 : in_alignof ? "alignof"
		 : "_Countof"));

  ಯದಿ (in_underspecified_init)
    error_at (loc, "%qT defined in underspecified object initializer", ref);

  ಪ್ರತ್ಯಾಗಮ ref;
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
	   ಸಂರಚನಾ c_declarator *declarator, ಸಂರಚನಾ c_declspecs *declspecs,
	   ವೃಕ್ಷ width, ವೃಕ್ಷ *decl_attrs, ವೃಕ್ಷ *ಅಭಿವ್ಯಕ್ತಿ)
{
  ವೃಕ್ಷ ಮೌಲ್ಯ;

  ಯದಿ (declarator->kind == cdk_id && declarator->u.id.id == NULL_ವೃಕ್ಷ
      && width == NULL_ವೃಕ್ಷ)
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
      ತಾರ್ಕಿಕ ok = ಅಸತ್ಯ;

      ಯದಿ (RECORD_OR_UNION_TYPE_P (type)
	  && (flag_ms_extensions
	      || flag_plan9_extensions
	      || !declspecs->typedef_p))
	{
	  ಯದಿ (flag_ms_extensions || flag_plan9_extensions)
	    ok = ಸತ್ಯ;
	  ಅನ್ಯಥಾ ಯದಿ (TYPE_NAME (type) == ರಿಕ್ತ)
	    ok = ಸತ್ಯ;
	  ಅನ್ಯಥಾ
	    ok = ಅಸತ್ಯ;
	}
      ಯದಿ (!ok)
	{
	  pedwarn (loc, 0, "declaration does not declare anything");
	  ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;
	}
      ಯದಿ (flag_isoc99)
	pedwarn_c99 (loc, OPT_Wpedantic,
		     "ISO C99 doesn%'t support unnamed structs/unions");
      ಅನ್ಯಥಾ
	pedwarn_c99 (loc, OPT_Wpedantic,
		     "ISO C90 doesn%'t support unnamed structs/unions");
    }

  ಮೌಲ್ಯ = grokdeclarator (declarator, declspecs, FIELD, ಅಸತ್ಯ,
			  width ? &width : ರಿಕ್ತ, decl_attrs, ಅಭಿವ್ಯಕ್ತಿ, ರಿಕ್ತ,
			  DEPRECATED_NORMAL);

  /* When this field has name, its type is a top level type, we should
     call verify_counted_by_for_top_anonymous_type.  */
  ಯದಿ (DECL_NAME (ಮೌಲ್ಯ) != NULL_ವೃಕ್ಷ
      && declspecs->typespec_kind == ctsk_tagdef)
    verify_counted_by_for_ತುದಿ_anonymous_type (declspecs->type);

  finish_decl (ಮೌಲ್ಯ, loc, NULL_ವೃಕ್ಷ, NULL_ವೃಕ್ಷ, NULL_ವೃಕ್ಷ);
  DECL_INITIAL (ಮೌಲ್ಯ) = width;
  ಯದಿ (width)
    SET_DECL_C_BIT_FIELD (ಮೌಲ್ಯ);

  ಯದಿ (warn_cxx_compat && DECL_NAME (ಮೌಲ್ಯ) != NULL_ವೃಕ್ಷ)
    {
      /* If we currently have a binding for this field, set the
	 in_struct field in the binding, so that we warn about lookups
	 which find it.  */
      ಸಂರಚನಾ c_binding *b = I_ಚಿಹ್ನೆ_BINDING (DECL_NAME (ಮೌಲ್ಯ));
      ಯದಿ (b != ರಿಕ್ತ)
	{
	  /* If the in_struct field is not yet set, push it on a list
	     to be cleared when this struct is finished.  */
	  ಯದಿ (!b->in_struct)
	    {
	      struct_parse_info->fields.safe_ತಳ್ಳು (b);
	      b->in_struct = 1;
	    }
	}
    }

  ಪ್ರತ್ಯಾಗಮ ಮೌಲ್ಯ;
}

/* Subroutine of detect_field_duplicates: return whether X and Y,
   which are both fields in the same struct, have duplicate field
   names.  */

ಸ್ಥಿರ ತಾರ್ಕಿಕ
is_duplicate_field (ವೃಕ್ಷ x, ವೃಕ್ಷ y)
{
  ಯದಿ (DECL_NAME (x) != NULL_ವೃಕ್ಷ && DECL_NAME (x) == DECL_NAME (y))
    ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;

  /* When using -fplan9-extensions, an anonymous field whose name is a
     typedef can duplicate a field name.  */
  ಯದಿ (flag_plan9_extensions
      && (DECL_NAME (x) == NULL_ವೃಕ್ಷ || DECL_NAME (y) == NULL_ವೃಕ್ಷ))
    {
      ವೃಕ್ಷ xt, xn, yt, yn;

      xt = ವೃಕ್ಷ_TYPE (x);
      ಯದಿ (DECL_NAME (x) != NULL_ವೃಕ್ಷ)
	xn = DECL_NAME (x);
      ಅನ್ಯಥಾ ಯದಿ (RECORD_OR_UNION_TYPE_P (xt)
	       && TYPE_NAME (xt) != NULL_ವೃಕ್ಷ
	       && ವೃಕ್ಷ_CODE (TYPE_NAME (xt)) == TYPE_DECL)
	xn = DECL_NAME (TYPE_NAME (xt));
      ಅನ್ಯಥಾ
	xn = NULL_ವೃಕ್ಷ;

      yt = ವೃಕ್ಷ_TYPE (y);
      ಯದಿ (DECL_NAME (y) != NULL_ವೃಕ್ಷ)
	yn = DECL_NAME (y);
      ಅನ್ಯಥಾ ಯದಿ (RECORD_OR_UNION_TYPE_P (yt)
	       && TYPE_NAME (yt) != NULL_ವೃಕ್ಷ
	       && ವೃಕ್ಷ_CODE (TYPE_NAME (yt)) == TYPE_DECL)
	yn = DECL_NAME (TYPE_NAME (yt));
      ಅನ್ಯಥಾ
	yn = NULL_ವೃಕ್ಷ;

      ಯದಿ (xn != NULL_ವೃಕ್ಷ && xn == yn)
	ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
    }

  ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
}

/* Subroutine of detect_field_duplicates: add the fields of FIELDLIST
   to HTAB, giving errors for any duplicates.  */

ಸ್ಥಿರ ಶೂನ್ಯ
detect_field_duplicates_hash (ವೃಕ್ಷ fieldlist,
			      hash_table<nofree_ptr_hash <ವೃಕ್ಷ_ಗಂಟು> > *htab)
{
  ವೃಕ್ಷ x, y;
  ವೃಕ್ಷ_ಗಂಟು **slot;

  ಪ್ರತಿ (x = fieldlist; x ; x = DECL_CHAIN (x))
    ಯದಿ ((y = DECL_NAME (x)) != NULL_ವೃಕ್ಷ)
      {
	slot = htab->find_slot (y, ಸೇರಿಸು);
	ಯದಿ (*slot)
	  {
	    error ("duplicate member %q+D", x);
	    DECL_NAME (x) = NULL_ವೃಕ್ಷ;
	  }
	*slot = y;
      }
    ಅನ್ಯಥಾ ಯದಿ (RECORD_OR_UNION_TYPE_P (ವೃಕ್ಷ_TYPE (x)))
      {
	detect_field_duplicates_hash (TYPE_FIELDS (ವೃಕ್ಷ_TYPE (x)), htab);

	/* When using -fplan9-extensions, an anonymous field whose
	   name is a typedef can duplicate a field name.  */
	ಯದಿ (flag_plan9_extensions
	    && TYPE_NAME (ವೃಕ್ಷ_TYPE (x)) != NULL_ವೃಕ್ಷ
	    && ವೃಕ್ಷ_CODE (TYPE_NAME (ವೃಕ್ಷ_TYPE (x))) == TYPE_DECL)
	  {
	    ವೃಕ್ಷ xn = DECL_NAME (TYPE_NAME (ವೃಕ್ಷ_TYPE (x)));
	    slot = htab->find_slot (xn, ಸೇರಿಸು);
	    ಯದಿ (*slot)
	      error ("duplicate member %q+D", TYPE_NAME (ವೃಕ್ಷ_TYPE (x)));
	    *slot = xn;
	  }
      }
}

/* Generate an error for any duplicate field names in FIELDLIST.  Munge
   the list such that this does not present a problem later.  */

ಸ್ಥಿರ ಶೂನ್ಯ
detect_field_duplicates (ವೃಕ್ಷ fieldlist)
{
  ವೃಕ್ಷ x, y;
  ಪೂರ್ಣಾಙ್ಕ timeout = 10;

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
  ಯದಿ (c_dialect_objc ())
    ಯದಿ (objc_detect_field_duplicates (ಅಸತ್ಯ))
      ಪ್ರತ್ಯಾಗಮ;

  /* First, see if there are more than "a few" fields.
     This is trivially true if there are zero or one fields.  */
  ಯದಿ (!fieldlist || !DECL_CHAIN (fieldlist))
    ಪ್ರತ್ಯಾಗಮ;
  x = fieldlist;
  ಕುರು {
    timeout--;
    ಯದಿ (DECL_NAME (x) == NULL_ವೃಕ್ಷ
	&& RECORD_OR_UNION_TYPE_P (ವೃಕ್ಷ_TYPE (x)))
      timeout = 0;
    x = DECL_CHAIN (x);
  } ಯಾವತ್ (timeout > 0 && x);

  /* If there were "few" fields and no anonymous structures or unions,
     avoid the overhead of allocating a hash table.  Instead just do
     the nested traversal thing.  */
  ಯದಿ (timeout > 0)
    {
      ಪ್ರತಿ (x = DECL_CHAIN (fieldlist); x; x = DECL_CHAIN (x))
	/* When using -fplan9-extensions, we can have duplicates
	   between typedef names and fields.  */
	ಯದಿ (DECL_NAME (x)
	    || (flag_plan9_extensions
		&& DECL_NAME (x) == NULL_ವೃಕ್ಷ
		&& RECORD_OR_UNION_TYPE_P (ವೃಕ್ಷ_TYPE (x))
		&& TYPE_NAME (ವೃಕ್ಷ_TYPE (x)) != NULL_ವೃಕ್ಷ
		&& ವೃಕ್ಷ_CODE (TYPE_NAME (ವೃಕ್ಷ_TYPE (x))) == TYPE_DECL))
	  {
	    ಪ್ರತಿ (y = fieldlist; y != x; y = ವೃಕ್ಷ_CHAIN (y))
	      ಯದಿ (is_duplicate_field (y, x))
		{
		  error ("duplicate member %q+D", x);
		  DECL_NAME (x) = NULL_ವೃಕ್ಷ;
		}
	  }
    }
  ಅನ್ಯಥಾ
    {
      hash_table<nofree_ptr_hash <ವೃಕ್ಷ_ಗಂಟು> > htab (37);
      detect_field_duplicates_hash (fieldlist, &htab);
    }
}

/* Finish up struct info used by -Wc++-compat.  */

ಸ್ಥಿರ ಶೂನ್ಯ
warn_cxx_compat_finish_struct (ವೃಕ್ಷ fieldlist, ಗಣನಾ ವೃಕ್ಷ_code code,
			       location_t record_loc)
{
  unsigned ಪೂರ್ಣಾಙ್ಕ ix;
  ವೃಕ್ಷ x;
  ಸಂರಚನಾ c_binding *b;

  ಯದಿ (fieldlist == NULL_ವೃಕ್ಷ)
    {
      ಯದಿ (code == RECORD_TYPE)
	warning_at (record_loc, OPT_Wc___compat,
		    "empty struct has size 0 in C, size 1 in C++");
      ಅನ್ಯಥಾ
	warning_at (record_loc, OPT_Wc___compat,
		    "empty union has size 0 in C, size 1 in C++");
    }

  /* Set the C_TYPE_DEFINED_IN_STRUCT flag for each type defined in
     the current struct.  We do this now at the end of the struct
     because the flag is used to issue visibility warnings, and we
     only want to issue those warnings if the type is referenced
     outside of the struct declaration.  */
  FOR_EACH_VEC_ELT (struct_parse_info->struct_types, ix, x)
    C_TYPE_DEFINED_IN_STRUCT (x) = 1;

  /* The TYPEDEFS_SEEN field of STRUCT_PARSE_INFO is a list of
     typedefs used when declaring fields in this struct.  If the name
     of any of the fields is also a typedef name then the struct would
     not parse in C++, because the C++ lookup rules say that the
     typedef name would be looked up in the context of the struct, and
     would thus be the field rather than the typedef.  */
  ಯದಿ (!struct_parse_info->typedefs_seen.is_empty ()
      && fieldlist != NULL_ವೃಕ್ಷ)
    {
      /* Use a hash_set<tree> using the name of the typedef.  We can use
	 a hash_set<tree> because identifiers are interned.  */
      hash_set<ವೃಕ್ಷ> tset;

      FOR_EACH_VEC_ELT (struct_parse_info->typedefs_seen, ix, x)
	tset.add (DECL_NAME (x));

      ಪ್ರತಿ (x = fieldlist; x != NULL_ವೃಕ್ಷ; x = DECL_CHAIN (x))
	{
	  ಯದಿ (DECL_NAME (x) != NULL_ವೃಕ್ಷ
	      && tset.contains (DECL_NAME (x)))
	    {
	      warning_at (DECL_SOURCE_LOCATION (x), OPT_Wc___compat,
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
    b->in_struct = 0;
}

/* Function to help qsort sort FIELD_DECLs by name order.  */

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ
field_decl_cmp (ಧ್ರುವ ಶೂನ್ಯ *x_p, ಧ್ರುವ ಶೂನ್ಯ *y_p)
{
  ಧ್ರುವ ವೃಕ್ಷ *ಧ್ರುವ x = (ಧ್ರುವ ವೃಕ್ಷ *) x_p;
  ಧ್ರುವ ವೃಕ್ಷ *ಧ್ರುವ y = (ಧ್ರುವ ವೃಕ್ಷ *) y_p;

  ಯದಿ (DECL_NAME (*x) == DECL_NAME (*y))
    /* A nontype is "greater" than a type.  */
    ಪ್ರತ್ಯಾಗಮ (ವೃಕ್ಷ_CODE (*y) == TYPE_DECL) - (ವೃಕ್ಷ_CODE (*x) == TYPE_DECL);
  ಯದಿ (DECL_NAME (*x) == NULL_ವೃಕ್ಷ)
    ಪ್ರತ್ಯಾಗಮ -1;
  ಯದಿ (DECL_NAME (*y) == NULL_ವೃಕ್ಷ)
    ಪ್ರತ್ಯಾಗಮ 1;
  ಯದಿ (DECL_NAME (*x) < DECL_NAME (*y))
    ಪ್ರತ್ಯಾಗಮ -1;
  ಪ್ರತ್ಯಾಗಮ 1;
}

/* If this structure or union completes the type of any previous
   variable declaration, lay it out and output its rtl.  */
ಸ್ಥಿರ ಶೂನ್ಯ
finish_incomplete_vars (ವೃಕ್ಷ incomplete_vars, ತಾರ್ಕಿಕ toplevel)
{
  ಪ್ರತಿ (ವೃಕ್ಷ x = incomplete_vars; x; x = ವೃಕ್ಷ_CHAIN (x))
    {
      ವೃಕ್ಷ decl = ವೃಕ್ಷ_ಮೌಲ್ಯ (x);
      ಯದಿ (ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (decl)) == ARRAY_TYPE)
	layout_array_type (ವೃಕ್ಷ_TYPE (decl));
      ಯದಿ (ವೃಕ್ಷ_CODE (decl) != TYPE_DECL)
	{
	  relayout_decl (decl);
	  ಯದಿ (c_dialect_objc ())
	    objc_check_decl (decl);
	  rest_of_decl_compilation (decl, toplevel, 0);
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
is_flexible_array_member_p (ತಾರ್ಕಿಕ is_last_field,
			    ವೃಕ್ಷ x)
{
  /* If not the last field, return false.  */
  ಯದಿ (!is_last_field)
    ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;

  /* If not an array field, return false.  */
  ಯದಿ (ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (x)) != ARRAY_TYPE)
    ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;

  ತಾರ್ಕಿಕ is_zero_length_array = zero_length_array_type_p (ವೃಕ್ಷ_TYPE (x));
  ತಾರ್ಕಿಕ is_one_element_array = one_element_array_type_p (ವೃಕ್ಷ_TYPE (x));
  ತಾರ್ಕಿಕ is_flexible_array = flexible_array_member_type_p (ವೃಕ್ಷ_TYPE (x));

  unsigned ಪೂರ್ಣಾಙ್ಕ strict_flex_array_level = c_strict_flex_array_level_of (x);

  ವಿಕಲ್ಪ (strict_flex_array_level)
    {
      ಪಕ್ಷ 0:
	/* Default, all trailing arrays are flexible array members.  */
	ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
      ಪಕ್ಷ 1:
	/* Level 1: all "[1]", "[0]", and "[]" are flexible array members.  */
	ಯದಿ (is_one_element_array)
	  ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
	/* FALLTHROUGH.  */
      ಪಕ್ಷ 2:
	/* Level 2: all "[0]", and "[]" are flexible array members.  */
	ಯದಿ (is_zero_length_array)
	  ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
	/* FALLTHROUGH.  */
      ಪಕ್ಷ 3:
	/* Level 3: Only "[]" are flexible array members.  */
	ಯದಿ (is_flexible_array)
	  ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
	ಭಙ್ಗ;
      ಸ್ವಭಾವ:
	gcc_unreachable ();
    }
  ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
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
  ಪ್ರತಿ (ವೃಕ್ಷ x = t, l = NULL_ವೃಕ್ಷ; x; l = x, x = TYPE_NEXT_VARIANT (x))
    {
      ಯದಿ (x != t && TYPE_STRUCTURAL_EQUALITY_P (x))
	{
	  ಯದಿ (!TYPE_QUALS (x))
	    TYPE_CANONICAL (x) = TYPE_CANONICAL (t);
	  ಅನ್ಯಥಾ
	    {
	      ವೃಕ್ಷ
		c = c_build_qualified_type (TYPE_CANONICAL (t), TYPE_QUALS (x));
	      ಯದಿ (TYPE_STRUCTURAL_EQUALITY_P (c))
		{
		  gcc_checking_assert (TYPE_CANONICAL (t) == t);
		  ಯದಿ (c == x)
		    TYPE_CANONICAL (x) = x;
		  ಅನ್ಯಥಾ
		    {
		      /* build_qualified_type for this function unhelpfully
			 moved c from some later spot in TYPE_MAIN_VARIANT (t)
			 chain to right after t (or created it there).  Move
			 it right before x and process c and then x.  */
		      gcc_checking_assert (TYPE_NEXT_VARIANT (t) == c);
		      ಯದಿ (l != t)
			{
			  TYPE_NEXT_VARIANT (t) = TYPE_NEXT_VARIANT (c);
			  TYPE_NEXT_VARIANT (l) = c;
			  TYPE_NEXT_VARIANT (c) = x;
			}
		      TYPE_CANONICAL (c) = c;
		      x = c;
		    }
		}
	      ಅನ್ಯಥಾ
		TYPE_CANONICAL (x) = TYPE_CANONICAL (c);
	    }
	}
      ಅನ್ಯಥಾ ಯದಿ (x != t)
	ಅನುವರ್ತ;
      ಪ್ರತಿ (ವೃಕ್ಷ p = TYPE_POINTER_TO (x); p; p = TYPE_NEXT_PTR_TO (p))
	{
	  ಯದಿ (!TYPE_STRUCTURAL_EQUALITY_P (p))
	    ಅನುವರ್ತ;
	  ಯದಿ (TYPE_CANONICAL (x) != x || TYPE_REF_CAN_ALIAS_ALL (p))
	    TYPE_CANONICAL (p)
	      = c_build_pointer_type_for_mode (TYPE_CANONICAL (x), TYPE_MODE (p),
					       ಅಸತ್ಯ);
	  ಅನ್ಯಥಾ
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
  ಪ್ರತಿ (ವೃಕ್ಷ x = t; x; x = TYPE_NEXT_VARIANT (x))
    {
      C_TYPE_VARIABLY_MODIFIED (x) = 1;
      ಪ್ರತಿ (ವೃಕ್ಷ p = TYPE_POINTER_TO (x); p; p = TYPE_NEXT_PTR_TO (p))
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
  ಪ್ರತಿ (ವೃಕ್ಷ field = TYPE_FIELDS (cur_struct_type); field;
       field = ವೃಕ್ಷ_CHAIN (field))
    {
      ಯದಿ (flexible_array_member_type_p (ವೃಕ್ಷ_TYPE (field))
	   || ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (field)) == POINTER_TYPE)
	{
	  ವೃಕ್ಷ attr_counted_by = lookup_attribute ("counted_by",
						   DECL_ATTRIBUTES (field));

	  ಯದಿ (!attr_counted_by)
	    ಅನುವರ್ತ;

	  /* If there is an counted_by attribute attached to the field,
	     verify it.  */

	  ವೃಕ್ಷ fieldname = ವೃಕ್ಷ_ಮೌಲ್ಯ (ವೃಕ್ಷ_ಮೌಲ್ಯ (attr_counted_by));

	  /* Verify the argument of the attribute is a valid field of the
	     containing structure.  */

	  ವೃಕ್ಷ counted_by_field = lookup_field (outmost_struct_type,
						fieldname);

	  /* Error when the field is not found in the containing structure
	     and remove the corresponding counted_by attribute from the
	     field_decl.  */
	  ಯದಿ (!counted_by_field)
	    {
	      error_at (DECL_SOURCE_LOCATION (field),
		    "argument %qE to the %<counted_by%> attribute"
		    " is not a field declaration in the same structure"
		    " as %qD", fieldname, field);
	      DECL_ATTRIBUTES (field)
		= remove_attribute ("counted_by", DECL_ATTRIBUTES (field));
	    }
	  ಅನ್ಯಥಾ
	  /* Error when the field is not with an integer type.  */
	    {
	      ಯಾವತ್ (ವೃಕ್ಷ_CHAIN (counted_by_field))
		counted_by_field = ವೃಕ್ಷ_CHAIN (counted_by_field);
	      ವೃಕ್ಷ real_field = ವೃಕ್ಷ_ಮೌಲ್ಯ (counted_by_field);

	      ಯದಿ (!INTEGRAL_TYPE_P (ವೃಕ್ಷ_TYPE (real_field)))
		{
		  error_at (DECL_SOURCE_LOCATION (field),
			"argument %qE to the %<counted_by%> attribute"
			" is not a field declaration with an integer type",
			fieldname);
		  DECL_ATTRIBUTES (field)
		    = remove_attribute ("counted_by",
				    DECL_ATTRIBUTES (field));
		}
	    }
	}
      ಅನ್ಯಥಾ ಯದಿ (RECORD_OR_UNION_TYPE_P (ವೃಕ್ಷ_TYPE (field))
	       && (DECL_NAME (field) == NULL_ವೃಕ್ಷ))
	verify_counted_by_attribute (outmost_struct_type, ವೃಕ್ಷ_TYPE (field));
    }
}

/* Caller should make sure the TYPE is a top-level type (i.e. not being
   nested in other structure/uniona). For such type, verify its counted_by
   if it is an anonymous structure/union.  */

ಶೂನ್ಯ
verify_counted_by_for_ತುದಿ_anonymous_type (ವೃಕ್ಷ type)
{
  ಯದಿ (!RECORD_OR_UNION_TYPE_P (type))
    ಪ್ರತ್ಯಾಗಮ;

  ಯದಿ (C_TYPE_FIELDS_HAS_COUNTED_BY (type)
      && c_type_tag (type) == NULL_ವೃಕ್ಷ)
    verify_counted_by_attribute (type, type);
}

/* TYPE is a struct or union that we're applying may_alias to after the body is
   parsed.  Fixup any POINTER_TO types.  */

ಸ್ಥಿರ ಶೂನ್ಯ
c_fixup_may_alias (ವೃಕ್ಷ type)
{
  ಪ್ರತಿ (ವೃಕ್ಷ t = TYPE_POINTER_TO (type); t; t = TYPE_NEXT_PTR_TO (t))
    ಪ್ರತಿ (ವೃಕ್ಷ v = TYPE_MAIN_VARIANT (t); v; v = TYPE_NEXT_VARIANT (v))
      TYPE_REF_CAN_ALIAS_ALL (v) = ಸತ್ಯ;
}

/* Fill in the fields of a RECORD_TYPE or UNION_TYPE node, T.
   LOC is the location of the RECORD_TYPE or UNION_TYPE's definition.
   FIELDLIST is a chain of FIELD_DECL nodes for the fields.
   ATTRIBUTES are attributes to be applied to the structure.

   ENCLOSING_STRUCT_PARSE_INFO is the value of STRUCT_PARSE_INFO when
   the struct was started.  */

ವೃಕ್ಷ
finish_struct (location_t loc, ವೃಕ್ಷ t, ವೃಕ್ಷ fieldlist, ವೃಕ್ಷ attributes,
	       ವರ್ಗ c_struct_parse_info *enclosing_struct_parse_info,
	       ವೃಕ್ಷ *ಅಭಿವ್ಯಕ್ತಿ)
{
  ವೃಕ್ಷ x;
  ತಾರ್ಕಿಕ toplevel = file_scope == current_scope;

  /* If this type was previously laid out as a forward reference,
     make sure we lay it out again.  */

  TYPE_SIZE (t) = NULL_ವೃಕ್ಷ;

  decl_attributes (&t, attributes, (ಪೂರ್ಣಾಙ್ಕ) ATTR_FLAG_TYPE_IN_PLACE);

  ಯದಿ (pedantic)
    {
      ಪ್ರತಿ (x = fieldlist; x; x = DECL_CHAIN (x))
	{
	  ಯದಿ (DECL_NAME (x) != NULL_ವೃಕ್ಷ)
	    ಭಙ್ಗ;
	  ಯದಿ (flag_isoc11 && RECORD_OR_UNION_TYPE_P (ವೃಕ್ಷ_TYPE (x)))
	    ಭಙ್ಗ;
	}

      ಯದಿ (x == NULL_ವೃಕ್ಷ)
	{
	  ಯದಿ (ವೃಕ್ಷ_CODE (t) == UNION_TYPE)
	    {
	      ಯದಿ (fieldlist)
		pedwarn (loc, OPT_Wpedantic, "union has no named members");
	      ಅನ್ಯಥಾ
		pedwarn (loc, OPT_Wpedantic, "union has no members");
	    }
	  ಅನ್ಯಥಾ
	    {
	      ಯದಿ (fieldlist)
		pedwarn (loc, OPT_Wpedantic, "struct has no named members");
	      ಅನ್ಯಥಾ
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

  ತಾರ್ಕಿಕ saw_named_field = ಅಸತ್ಯ;
  ಪ್ರತಿ (x = fieldlist; x; x = DECL_CHAIN (x))
    {
      /* Whether this field is the last field of the structure or union.
	 for UNION, any field is the last field of it.  */
      ತಾರ್ಕಿಕ is_last_field = (DECL_CHAIN (x) == NULL_ವೃಕ್ಷ)
			    || (ವೃಕ್ಷ_CODE (t) == UNION_TYPE);

      ಯದಿ (ವೃಕ್ಷ_TYPE (x) == error_mark_ಗಂಟು)
	ಅನುವರ್ತ;

      DECL_CONTEXT (x) = t;

      ವೃಕ್ಷ t1 = strip_array_types (ವೃಕ್ಷ_TYPE (x));
      /* If any field is const, the structure type is pseudo-const.  */
      ಯದಿ (ವೃಕ್ಷ_READONLY (x))
	C_TYPE_FIELDS_READONLY (t) = 1;
      ಅನ್ಯಥಾ
	{
	  /* A field that is pseudo-const makes the structure likewise.  */
	  ಯದಿ (RECORD_OR_UNION_TYPE_P (t1) && C_TYPE_FIELDS_READONLY (t1))
	    C_TYPE_FIELDS_READONLY (t) = 1;
	}

      /* Any field that is volatile means variables of this type must be
	 treated in some ways as volatile.  */
      ಯದಿ (ವೃಕ್ಷ_THIS_VOLATILE (x))
	{
	  C_TYPE_FIELDS_VOLATILE (t) = 1;
	  C_TYPE_FIELDS_NON_CONSTEXPR (t) = 1;
	}

      /* Any field that is volatile, restrict-qualified or atomic
	 means the type cannot be used for a constexpr object.  */
      ಯದಿ (TYPE_QUALS (t1)
	  & (TYPE_QUAL_VOLATILE | TYPE_QUAL_RESTRICT | TYPE_QUAL_ATOMIC))
	C_TYPE_FIELDS_NON_CONSTEXPR (t) = 1;
      ಅನ್ಯಥಾ ಯದಿ (RECORD_OR_UNION_TYPE_P (t1) && C_TYPE_FIELDS_NON_CONSTEXPR (t1))
	    C_TYPE_FIELDS_NON_CONSTEXPR (t) = 1;

      /* Any field of nominal variable size implies structure is too.  */
      ಯದಿ (C_DECL_VARIABLE_SIZE (x))
	C_TYPE_VARIABLE_SIZE (t) = 1;

      /* If any field is variably modified, record this fact. */
      ಯದಿ (c_type_variably_modified_p (ವೃಕ್ಷ_TYPE (x)))
	C_TYPE_VARIABLY_MODIFIED (t) = 1;

      ಯದಿ (DECL_C_BIT_FIELD (x))
	{
	  unsigned HOST_WIDE_INT width = ವೃಕ್ಷ_to_uhwi (DECL_INITIAL (x));
	  DECL_SIZE (x) = bitsize_int (width);
	  DECL_BIT_FIELD (x) = 1;
	}

      ಯದಿ (TYPE_PACKED (t)
	  && (DECL_BIT_FIELD (x)
	      || TYPE_ALIGN (ವೃಕ್ಷ_TYPE (x)) > BITS_PER_UNIT))
	DECL_PACKED (x) = 1;

      /* Detect flexible array member in an invalid context.  */
      ಯದಿ (flexible_array_member_type_p (ವೃಕ್ಷ_TYPE (x)))
	{
	  ಯದಿ (ವೃಕ್ಷ_CODE (t) == UNION_TYPE)
	    pedwarn (DECL_SOURCE_LOCATION (x), OPT_Wpedantic,
		     "flexible array member in union is a GCC extension");
	  ಅನ್ಯಥಾ ಯದಿ (!is_last_field)
	    {
	      error_at (DECL_SOURCE_LOCATION (x),
			"flexible array member not at end of struct");
	      ವೃಕ್ಷ_TYPE (x) = error_mark_ಗಂಟು;
	    }
	  ಅನ್ಯಥಾ ಯದಿ (!saw_named_field)
	    pedwarn (DECL_SOURCE_LOCATION (x), OPT_Wpedantic,
		     "flexible array member in a struct with no named "
		     "members is a GCC extension");
	  ಯದಿ (lookup_attribute ("counted_by", DECL_ATTRIBUTES (x)))
	    C_TYPE_FIELDS_HAS_COUNTED_BY (t) = 1;
	}

      ಯದಿ (ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (x)) == POINTER_TYPE
	  && lookup_attribute ("counted_by", DECL_ATTRIBUTES (x)))
	C_TYPE_FIELDS_HAS_COUNTED_BY (t) = 1;

      /* If the field is an anonymous structure that includes a field
	 with counted_by attribute, this structure should also be marked
	 too.  */
      ಯದಿ (RECORD_OR_UNION_TYPE_P (ವೃಕ್ಷ_TYPE (x))
	  && C_TYPE_FIELDS_HAS_COUNTED_BY (ವೃಕ್ಷ_TYPE (x))
	  && DECL_NAME (x) == NULL_ವೃಕ್ಷ
	  && c_type_tag (ವೃಕ್ಷ_TYPE (x)) == NULL_ವೃಕ್ಷ)
	C_TYPE_FIELDS_HAS_COUNTED_BY (t) = 1;

      ಯದಿ (pedantic && ವೃಕ್ಷ_CODE (t) == RECORD_TYPE
	  && flexible_array_type_p (ವೃಕ್ಷ_TYPE (x)))
	pedwarn (DECL_SOURCE_LOCATION (x), OPT_Wpedantic,
		 "invalid use of structure with flexible array member");

      /* Set DECL_NOT_FLEXARRAY flag for FIELD_DECL x.  */
      DECL_NOT_FLEXARRAY (x) = !is_flexible_array_member_p (is_last_field, x);

      /* Set TYPE_INCLUDES_FLEXARRAY for the context of x, t.
	 when x is an array and is the last field.
	 There is only one last_field for a structure type, but there might
	 be multiple last_fields for a union type, therefore we should ORed
	 the result for multiple last_fields.  */
      ಯದಿ (ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (x)) == ARRAY_TYPE)
	TYPE_INCLUDES_FLEXARRAY (t)
	  |= is_last_field && flexible_array_member_type_p (ವೃಕ್ಷ_TYPE (x));
      /* Recursively set TYPE_INCLUDES_FLEXARRAY for the context of x, t
	 when x is an union or record and is the last field.  */
      ಅನ್ಯಥಾ ಯದಿ (RECORD_OR_UNION_TYPE_P (ವೃಕ್ಷ_TYPE (x)))
	TYPE_INCLUDES_FLEXARRAY (t)
	  |= is_last_field && TYPE_INCLUDES_FLEXARRAY (ವೃಕ್ಷ_TYPE (x));

      ಯದಿ (warn_flex_array_member_not_at_end
	  && !is_last_field
	  && RECORD_OR_UNION_TYPE_P (ವೃಕ್ಷ_TYPE (x))
	  && TYPE_INCLUDES_FLEXARRAY (ವೃಕ್ಷ_TYPE (x)))
	warning_at (DECL_SOURCE_LOCATION (x),
		    OPT_Wflex_array_member_not_at_end,
		    "structure containing a flexible array member"
		    " is not at the end of another structure");

      ಯದಿ (DECL_NAME (x)
	  || RECORD_OR_UNION_TYPE_P (ವೃಕ್ಷ_TYPE (x)))
	saw_named_field = ಸತ್ಯ;

      ಯದಿ (AGGREGATE_TYPE_P (ವೃಕ್ಷ_TYPE (x))
	  && TYPE_TYPELESS_STORAGE (ವೃಕ್ಷ_TYPE (x)))
	TYPE_TYPELESS_STORAGE (t) = ಸತ್ಯ;
    }

  detect_field_duplicates (fieldlist);

  /* Now we have the nearly final fieldlist.  Record it,
     then lay out the structure or union (including the fields).  */

  TYPE_FIELDS (t) = fieldlist;

  maybe_apply_pragma_scalar_storage_order (t);

  layout_type (t);

  ಯದಿ (TYPE_SIZE_UNIT (t)
      && ವೃಕ್ಷ_CODE (TYPE_SIZE_UNIT (t)) == INTEGER_CST
      && !ವೃಕ್ಷ_OVERFLOW (TYPE_SIZE_UNIT (t))
      && !valid_constant_size_p (TYPE_SIZE_UNIT (t)))
    error ("type %qT is too large", t);

  /* Give bit-fields their proper types and rewrite the type of array fields
     with scalar component if the enclosing type has reverse storage order.  */
  ಪ್ರತಿ (ವೃಕ್ಷ field = fieldlist; field; field = DECL_CHAIN (field))
    {
      ಯದಿ (ವೃಕ್ಷ_CODE (field) == FIELD_DECL
	  && DECL_INITIAL (field)
	  && ವೃಕ್ಷ_TYPE (field) != error_mark_ಗಂಟು)
	{
	  unsigned HOST_WIDE_INT width
	    = ವೃಕ್ಷ_to_uhwi (DECL_INITIAL (field));
	  ವೃಕ್ಷ type = ವೃಕ್ಷ_TYPE (field);
	  ಯದಿ (VECTOR_TYPE_P (type))
	    {
	      error_at (DECL_SOURCE_LOCATION (field),
			"bit-field %qD has invalid type", field);
	      type = ವೃಕ್ಷ_TYPE (type);
	      ವೃಕ್ಷ_TYPE (field) = type;
	    }
	  ಯದಿ (width != TYPE_PRECISION (type))
	    {
	      ಯದಿ (BITINT_TYPE_P (type)
		  && width >= ((TYPE_UNSIGNED (type) || flag_isoc2y) ? 1 : 2))
		ವೃಕ್ಷ_TYPE (field)
		  = build_bitint_type (width, TYPE_UNSIGNED (type));
	      ಅನ್ಯಥಾ
		ವೃಕ್ಷ_TYPE (field)
		  = c_build_bitfield_integer_type (width,
						   TYPE_UNSIGNED (type));
	      ಯದಿ (ವೃಕ್ಷ attr = c_hardbool_type_attr (type))
		decl_attributes (&ವೃಕ್ಷ_TYPE (field),
				 copy_list (attr),
				 0, NULL_ವೃಕ್ಷ);
	      SET_DECL_MODE (field, TYPE_MODE (ವೃಕ್ಷ_TYPE (field)));
	    }
	  DECL_INITIAL (field) = NULL_ವೃಕ್ಷ;
	}
      ಅನ್ಯಥಾ ಯದಿ (TYPE_REVERSE_STORAGE_ORDER (t)
	       && ವೃಕ್ಷ_CODE (field) == FIELD_DECL
	       && ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (field)) == ARRAY_TYPE)
	{
	  ವೃಕ್ಷ ftype = ವೃಕ್ಷ_TYPE (field);
	  ವೃಕ್ಷ ctype = strip_array_types (ftype);
	  ಯದಿ (!RECORD_OR_UNION_TYPE_P (ctype) && TYPE_MODE (ctype) != QImode)
	    {
	      ವೃಕ್ಷ fmain_type = TYPE_MAIN_VARIANT (ftype);
	      ವೃಕ್ಷ *typep = &fmain_type;
	      ಕುರು {
		*typep = build_distinct_type_copy (*typep);
		TYPE_REVERSE_STORAGE_ORDER (*typep) = 1;
		typep = &ವೃಕ್ಷ_TYPE (*typep);
	      } ಯಾವತ್ (ವೃಕ್ಷ_CODE (*typep) == ARRAY_TYPE);
	      ವೃಕ್ಷ_TYPE (field)
		= c_build_qualified_type (fmain_type, TYPE_QUALS (ftype));
	    }
	}

      /* Warn on problematic type punning for storage order purposes.  */
      ಯದಿ (ವೃಕ್ಷ_CODE (t) == UNION_TYPE
	  && ವೃಕ್ಷ_CODE (field) == FIELD_DECL
	  && AGGREGATE_TYPE_P (ವೃಕ್ಷ_TYPE (field)))
	{
	  ವೃಕ್ಷ ftype = ವೃಕ್ಷ_TYPE (field);
	  ಯದಿ (ವೃಕ್ಷ_CODE (ftype) == ARRAY_TYPE)
	    ftype = strip_array_types (ftype);
	  ಯದಿ (RECORD_OR_UNION_TYPE_P (ftype)
	      && TYPE_REVERSE_STORAGE_ORDER (ftype)
		 != TYPE_REVERSE_STORAGE_ORDER (t))
	    warning_at (DECL_SOURCE_LOCATION (field),
			OPT_Wscalar_storage_order,
			"type punning toggles scalar storage order");
	}
    }

  /* Now we have the truly final field list.
     Store it in this type and in the variants.  */

  TYPE_FIELDS (t) = fieldlist;

  /* If there are lots of fields, sort so we can look through them fast.
     We arbitrarily consider 16 or more elts to be "a lot".  */

  {
    ಪೂರ್ಣಾಙ್ಕ len = 0;

    ಪ್ರತಿ (x = fieldlist; x; x = DECL_CHAIN (x))
      {
	ಯದಿ (len > 15 || DECL_NAME (x) == ರಿಕ್ತ)
	  ಭಙ್ಗ;
	len += 1;
      }

    ಯದಿ (len > 15)
      {
	ವೃಕ್ಷ *field_array;
	ಸಂರಚನಾ lang_type *space;
	ಸಂರಚನಾ sorted_fields_type *space2;

	len += list_length (x);

	/* Use the same allocation policy here that make_node uses, to
	   ensure that this lives as long as the rest of the struct decl.
	   All decls in an inline function need to be saved.  */

	space = ((ಸಂರಚನಾ lang_type *)
		 ggc_internal_cleared_alloc (c_dialect_objc ()
					     ? ಪರಿಮಾಣ (ಸಂರಚನಾ lang_type)
					     : offsetof (ಸಂರಚನಾ lang_type,
							 info)));
	space2 = ((sorted_fields_type *)
		  ggc_internal_alloc (ಪರಿಮಾಣ (ಸಂರಚನಾ sorted_fields_type)
				      + len * ಪರಿಮಾಣ (ವೃಕ್ಷ)));

	len = 0;
	space->s = space2;
	field_array = &space2->elts[0];
	ಪ್ರತಿ (x = fieldlist; x; x = DECL_CHAIN (x))
	  {
	    field_array[len++] = x;

	    /* If there is anonymous struct or union, break out of the loop.  */
	    ಯದಿ (DECL_NAME (x) == ರಿಕ್ತ)
	      ಭಙ್ಗ;
	  }
	/* Found no anonymous struct/union.  Add the TYPE_LANG_SPECIFIC.  */
	ಯದಿ (x == ರಿಕ್ತ)
	  {
	    TYPE_LANG_SPECIFIC (t) = space;
	    TYPE_LANG_SPECIFIC (t)->s->len = len;
	    field_array = TYPE_LANG_SPECIFIC (t)->s->elts;
	    qsort (field_array, len, ಪರಿಮಾಣ (ವೃಕ್ಷ), field_decl_cmp);
	  }
      }
  }

  /* If this was supposed to be a transparent union, but we can't
     make it one, warn and turn off the flag.  */
  ಯದಿ (ವೃಕ್ಷ_CODE (t) == UNION_TYPE
      && TYPE_TRANSPARENT_AGGR (t)
      && (!TYPE_FIELDS (t) || TYPE_MODE (t) != DECL_MODE (TYPE_FIELDS (t))))
    {
      TYPE_TRANSPARENT_AGGR (t) = 0;
      warning_at (loc, 0, "union cannot be made transparent");
    }

  ವೃಕ್ಷ incomplete_vars = C_TYPE_INCOMPLETE_VARS (TYPE_MAIN_VARIANT (t));
  ಪ್ರತಿ (x = TYPE_MAIN_VARIANT (t); x; x = TYPE_NEXT_VARIANT (x))
    {
      TYPE_FIELDS (x) = TYPE_FIELDS (t);
      TYPE_LANG_SPECIFIC (x) = TYPE_LANG_SPECIFIC (t);
      TYPE_TRANSPARENT_AGGR (x) = TYPE_TRANSPARENT_AGGR (t);
      TYPE_TYPELESS_STORAGE (x) = TYPE_TYPELESS_STORAGE (t);
      C_TYPE_FIELDS_READONLY (x) = C_TYPE_FIELDS_READONLY (t);
      C_TYPE_FIELDS_VOLATILE (x) = C_TYPE_FIELDS_VOLATILE (t);
      C_TYPE_FIELDS_NON_CONSTEXPR (x) = C_TYPE_FIELDS_NON_CONSTEXPR (t);
      C_TYPE_FIELDS_HAS_COUNTED_BY (x) = C_TYPE_FIELDS_HAS_COUNTED_BY (t);
      C_TYPE_VARIABLE_SIZE (x) = C_TYPE_VARIABLE_SIZE (t);
      C_TYPE_VARIABLY_MODIFIED (x) = C_TYPE_VARIABLY_MODIFIED (t);
      C_TYPE_INCOMPLETE_VARS (x) = NULL_ವೃಕ್ಷ;
      TYPE_INCLUDES_FLEXARRAY (x) = TYPE_INCLUDES_FLEXARRAY (t);
    }

  /* Check for consistency with previous definition.  */
  ಯದಿ (flag_isoc23 && ರಿಕ್ತ != enclosing_struct_parse_info)
    {
      ವೃಕ್ಷ vistype = previous_tag (t);
      ಯದಿ (vistype
	  && ವೃಕ್ಷ_CODE (vistype) == ವೃಕ್ಷ_CODE (t)
	  && !C_TYPE_BEING_DEFINED (vistype))
	{
	  TYPE_STUB_DECL (t) = TYPE_STUB_DECL (vistype);
	  ಯದಿ (c_type_variably_modified_p (t))
	    {
	      error ("redefinition of struct or union %qT with variably "
		     "modified type", t);
	      ಯದಿ (struct_parse_info->refloc != UNKNOWN_LOCATION)
		inform (struct_parse_info->refloc, "originally defined here");
	    }
	  ಅನ್ಯಥಾ ಯದಿ (!comptypes_same_p (t, vistype))
	    {
	      error ("redefinition of struct or union %qT", t);
	      ಯದಿ (struct_parse_info->refloc != UNKNOWN_LOCATION)
		inform (struct_parse_info->refloc, "originally defined here");
	    }
	}
    }

  C_TYPE_BEING_DEFINED (t) = 0;

  ಯದಿ (lookup_attribute ("may_alias", TYPE_ATTRIBUTES (t)))
    ಪ್ರತಿ (x = TYPE_MAIN_VARIANT (t); x; x = TYPE_NEXT_VARIANT (x))
      c_fixup_may_alias (x);

  /* Set type canonical based on equivalence class.  */
  ಯದಿ (flag_isoc23 && !C_TYPE_VARIABLE_SIZE (t))
    {
      ಯದಿ (c_struct_htab == ರಿಕ್ತ)
	c_struct_htab = hash_table<c_struct_hasher>::create_ggc (61);

      hashval_t hash = c_struct_hasher::hash (t);

      gcc_checking_assert (TYPE_STRUCTURAL_EQUALITY_P (t));
      gcc_checking_assert (!TYPE_NAME (t)
			   || ವೃಕ್ಷ_CODE (TYPE_NAME (t)) == IDENTIFIER_ಗಂಟು);

      ವೃಕ್ಷ *e = c_struct_htab->find_slot_with_hash (t, hash, ಸೇರಿಸು);
      ಯದಿ (*e)
	TYPE_CANONICAL (t) = TYPE_CANONICAL (*e);
      ಅನ್ಯಥಾ
	{
	  TYPE_CANONICAL (t) = c_type_canonical (t);
	  *e = t;
	}
      c_update_type_canonical (t);
    }

  /* Update type location to the one of the definition, instead of e.g.
     a forward declaration.  */
  ಯದಿ (TYPE_STUB_DECL (t))
    DECL_SOURCE_LOCATION (TYPE_STUB_DECL (t)) = loc;

  /* Finish debugging output for this type.  */
  rest_of_type_compilation (t, toplevel);

  finish_incomplete_vars (incomplete_vars, toplevel);


  ಯದಿ (c_type_variably_modified_p (t))
    {
      c_update_variably_modified (t);
      /* Make sure a DECL_EXPR is created for structs with VLA members.
	 Because we do not know the context, we always pass expr
	 to force creation of a BIND_EXPR which is required in some
	 contexts.  */
      add_decl_ಅಭಿವ್ಯಕ್ತಿ (loc, t, ಅಭಿವ್ಯಕ್ತಿ, ಅಸತ್ಯ);
    }

  ಯದಿ (warn_cxx_compat)
    warn_cxx_compat_finish_struct (fieldlist, ವೃಕ್ಷ_CODE (t), loc);

  ಯದಿ (ರಿಕ್ತ != enclosing_struct_parse_info)
    {
      delete struct_parse_info;

      struct_parse_info = enclosing_struct_parse_info;

      /* If this struct is defined inside a struct, add it to
	 struct_types.  */
      ಯದಿ (warn_cxx_compat
	  && struct_parse_info != ರಿಕ್ತ
	  && !in_sizeof && !in_typeof && !in_alignof && !in_countof)
	struct_parse_info->struct_types.safe_ತಳ್ಳು (t);
     }

  /* Only when the enclosing struct/union type is not anonymous, do more
     verification on the fields with counted_by attributes.  */
  ಯದಿ (C_TYPE_FIELDS_HAS_COUNTED_BY (t) && c_type_tag (t) != NULL_ವೃಕ್ಷ)
    verify_counted_by_attribute (t, t);

  ಪ್ರತ್ಯಾಗಮ t;
}

ಸ್ಥಿರ ಸಂರಚನಾ {
  gt_pointer_operator new_ಮೌಲ್ಯ;
  ಶೂನ್ಯ *cookie;
} resort_data;

/* This routine compares two fields like field_decl_cmp but using the
pointer operator in resort_data.  */

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ
resort_field_decl_cmp (ಧ್ರುವ ಶೂನ್ಯ *x_p, ಧ್ರುವ ಶೂನ್ಯ *y_p)
{
  ಧ್ರುವ ವೃಕ್ಷ *ಧ್ರುವ x = (ಧ್ರುವ ವೃಕ್ಷ *) x_p;
  ಧ್ರುವ ವೃಕ್ಷ *ಧ್ರುವ y = (ಧ್ರುವ ವೃಕ್ಷ *) y_p;

  ಯದಿ (DECL_NAME (*x) == DECL_NAME (*y))
    /* A nontype is "greater" than a type.  */
    ಪ್ರತ್ಯಾಗಮ (ವೃಕ್ಷ_CODE (*y) == TYPE_DECL) - (ವೃಕ್ಷ_CODE (*x) == TYPE_DECL);
  ಯದಿ (DECL_NAME (*x) == NULL_ವೃಕ್ಷ)
    ಪ್ರತ್ಯಾಗಮ -1;
  ಯದಿ (DECL_NAME (*y) == NULL_ವೃಕ್ಷ)
    ಪ್ರತ್ಯಾಗಮ 1;
  {
    ವೃಕ್ಷ d1 = DECL_NAME (*x);
    ವೃಕ್ಷ d2 = DECL_NAME (*y);
    resort_data.new_ಮೌಲ್ಯ (&d1, &d1, resort_data.cookie);
    resort_data.new_ಮೌಲ್ಯ (&d2, &d2, resort_data.cookie);
    ಯದಿ (d1 < d2)
      ಪ್ರತ್ಯಾಗಮ -1;
  }
  ಪ್ರತ್ಯಾಗಮ 1;
}

/* Resort DECL_SORTED_FIELDS because pointers have been reordered.  */

ಶೂನ್ಯ
resort_sorted_fields (ಶೂನ್ಯ *obj,
		      ಶೂನ್ಯ * ARG_UNUSED (orig_obj),
		      gt_pointer_operator new_ಮೌಲ್ಯ,
		      ಶೂನ್ಯ *cookie)
{
  ಸಂರಚನಾ sorted_fields_type *sf = (ಸಂರಚನಾ sorted_fields_type *) obj;
  resort_data.new_ಮೌಲ್ಯ = new_ಮೌಲ್ಯ;
  resort_data.cookie = cookie;
  qsort (&sf->elts[0], sf->len, ಪರಿಮಾಣ (ವೃಕ್ಷ),
	 resort_field_decl_cmp);
}

/* Lay out the type T, and its element type, and so on.  */

ಸ್ಥಿರ ಶೂನ್ಯ
layout_array_type (ವೃಕ್ಷ t)
{
  ಯದಿ (ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (t)) == ARRAY_TYPE)
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
start_enum (location_t loc, ಸಂರಚನಾ c_enum_contents *the_enum, ವೃಕ್ಷ name,
	    ವೃಕ್ಷ fixed_underlying_type, ತಾರ್ಕಿಕ potential_nesting_p)
{
  ವೃಕ್ಷ enumtype = NULL_ವೃಕ್ಷ;
  location_t enumloc = UNKNOWN_LOCATION;

  /* If this is the real definition for a previous forward reference,
     fill in the contents in the same object that used to be the
     forward reference.  */

  ಯದಿ (name != NULL_ವೃಕ್ಷ)
    enumtype = lookup_tag (ENUMERAL_TYPE, name, ಸತ್ಯ, &enumloc);

  ಯದಿ (enumtype != NULL_ವೃಕ್ಷ && ವೃಕ್ಷ_CODE (enumtype) == ENUMERAL_TYPE)
    {
      /* If the type is currently being defined or if we have seen an
	 incomplete version which is now complete, this is a nested
	 redefinition.  The later happens if the redefinition occurs
	 inside the enum specifier itself.  */
      ಯದಿ (C_TYPE_BEING_DEFINED (enumtype)
	  || (potential_nesting_p && TYPE_ಮೌಲ್ಯಗಳು (enumtype) != NULL_ವೃಕ್ಷ))
	error_at (loc, "nested redefinition of %<enum %E%>", name);

      /* For C23 we allow redefinitions.  We set to zero and check for
	 consistency later.  */
      ಯದಿ (flag_isoc23 && TYPE_ಮೌಲ್ಯಗಳು (enumtype) != NULL_ವೃಕ್ಷ)
	enumtype = NULL_ವೃಕ್ಷ;
    }

  ಯದಿ (enumtype == NULL_ವೃಕ್ಷ || ವೃಕ್ಷ_CODE (enumtype) != ENUMERAL_TYPE)
    {
      enumtype = make_ಗಂಟು (ENUMERAL_TYPE);
      TYPE_SIZE (enumtype) = NULL_ವೃಕ್ಷ;
      SET_TYPE_STRUCTURAL_EQUALITY (enumtype);
      pushtag (loc, name, enumtype);
      ಯದಿ (fixed_underlying_type != NULL_ವೃಕ್ಷ)
	{
	  /* For an enum definition with a fixed underlying type, the
	     type is complete during the definition and the
	     enumeration constants have that type.  If there was a
	     tag, the type was completed in c_parser_enum_specifier.
	     If not, it must be completed here.  */
	  ENUM_FIXED_UNDERLYING_TYPE_P (enumtype) = ಸತ್ಯ;
	  TYPE_MIN_ಮೌಲ್ಯ (enumtype) = TYPE_MIN_ಮೌಲ್ಯ (fixed_underlying_type);
	  TYPE_MAX_ಮೌಲ್ಯ (enumtype) = TYPE_MAX_ಮೌಲ್ಯ (fixed_underlying_type);
	  TYPE_UNSIGNED (enumtype) = TYPE_UNSIGNED (fixed_underlying_type);
	  SET_TYPE_ALIGN (enumtype, TYPE_ALIGN (fixed_underlying_type));
	  TYPE_SIZE (enumtype) = NULL_ವೃಕ್ಷ;
	  TYPE_PRECISION (enumtype) = TYPE_PRECISION (fixed_underlying_type);
	  ENUM_UNDERLYING_TYPE (enumtype) = fixed_underlying_type;
	  TYPE_CANONICAL (enumtype) = TYPE_CANONICAL (fixed_underlying_type);
	  c_update_type_canonical (enumtype);
	  layout_type (enumtype);
	}
    }
  /* Update type location to the one of the definition, instead of e.g.
     a forward declaration.  */
  ಅನ್ಯಥಾ ಯದಿ (TYPE_STUB_DECL (enumtype))
    {
      enumloc = DECL_SOURCE_LOCATION (TYPE_STUB_DECL (enumtype));
      DECL_SOURCE_LOCATION (TYPE_STUB_DECL (enumtype)) = loc;
    }

  C_TYPE_BEING_DEFINED (enumtype) = 1;

  ಯದಿ (TYPE_ಮೌಲ್ಯಗಳು (enumtype) != NULL_ವೃಕ್ಷ)
    {
      /* This enum is a named one that has been declared already.  */
      auto_diagnostic_group d;
      error_at (loc, "redeclaration of %<enum %E%>", name);
      ಯದಿ (enumloc != UNKNOWN_LOCATION)
	inform (enumloc, "originally defined here");

      /* Completely replace its old definition.
	 The old enumerators remain defined, however.  */
      TYPE_ಮೌಲ್ಯಗಳು (enumtype) = NULL_ವೃಕ್ಷ;
    }

  ಯದಿ (ENUM_FIXED_UNDERLYING_TYPE_P (enumtype)
      && fixed_underlying_type == NULL_ವೃಕ್ಷ)
    {
      error_at (loc, "%<enum%> declared with but defined without "
		"fixed underlying type");
      ENUM_FIXED_UNDERLYING_TYPE_P (enumtype) = ಅಸತ್ಯ;
    }

  the_enum->enum_next_ಮೌಲ್ಯ = integer_zero_ಗಂಟು;
  the_enum->enum_type = enumtype;
  the_enum->enum_overflow = 0;

  ಯದಿ (flag_short_enums && !ENUM_FIXED_UNDERLYING_TYPE_P (enumtype))
    ಪ್ರತಿ (ವೃಕ್ಷ v = TYPE_MAIN_VARIANT (enumtype); v; v = TYPE_NEXT_VARIANT (v))
      TYPE_PACKED (v) = 1;

  /* FIXME: This will issue a warning for a use of a type defined
     within sizeof in a statement expr.  This is not terribly serious
     as C++ doesn't permit statement exprs within sizeof anyhow.  */
  ಯದಿ (warn_cxx_compat
      && (in_sizeof || in_typeof || in_alignof || in_countof))
    warning_at (loc, OPT_Wc___compat,
		"defining type in %qs expression is invalid in C++",
		(in_sizeof ? "sizeof"
		 : in_typeof ? "typeof"
		 : in_alignof ? "alignof"
		 : "_Countof"));

  ಯದಿ (in_underspecified_init)
    error_at (loc, "%qT defined in underspecified object initializer",
	      enumtype);

  ಪ್ರತ್ಯಾಗಮ enumtype;
}

/* After processing and defining all the values of an enumeration type,
   install their decls in the enumeration type and finish it off.
   ENUMTYPE is the type object, VALUES a list of decl-value pairs,
   and ATTRIBUTES are the specified attributes.
   Returns ENUMTYPE.  */

ವೃಕ್ಷ
finish_enum (ವೃಕ್ಷ enumtype, ವೃಕ್ಷ ಮೌಲ್ಯಗಳು, ವೃಕ್ಷ attributes)
{
  ವೃಕ್ಷ pair, tem;
  ವೃಕ್ಷ minnode = NULL_ವೃಕ್ಷ, maxnode = NULL_ವೃಕ್ಷ;
  ಪೂರ್ಣಾಙ್ಕ precision;
  signop sign;
  ತಾರ್ಕಿಕ toplevel = (file_scope == current_scope);
  ಸಂರಚನಾ lang_type *lt;

  decl_attributes (&enumtype, attributes, (ಪೂರ್ಣಾಙ್ಕ) ATTR_FLAG_TYPE_IN_PLACE);

  /* Calculate the maximum value of any enumerator in this type.  */

  ಯದಿ (ಮೌಲ್ಯಗಳು == error_mark_ಗಂಟು)
    minnode = maxnode = integer_zero_ಗಂಟು;
  ಅನ್ಯಥಾ
    {
      minnode = maxnode = ವೃಕ್ಷ_ಮೌಲ್ಯ (ಮೌಲ್ಯಗಳು);
      ಪ್ರತಿ (pair = ವೃಕ್ಷ_CHAIN (ಮೌಲ್ಯಗಳು); pair; pair = ವೃಕ್ಷ_CHAIN (pair))
	{
	  ವೃಕ್ಷ ಮೌಲ್ಯ = ವೃಕ್ಷ_ಮೌಲ್ಯ (pair);
	  ಯದಿ (ವೃಕ್ಷ_int_cst_lt (maxnode, ಮೌಲ್ಯ))
	    maxnode = ಮೌಲ್ಯ;
	  ಯದಿ (ವೃಕ್ಷ_int_cst_lt (ಮೌಲ್ಯ, minnode))
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


  ಯದಿ (!ENUM_FIXED_UNDERLYING_TYPE_P (enumtype))
    {
      /* If the precision of the type was specified with an attribute and it
	 was too small, give an error.  Otherwise, use it.  */
      ಯದಿ (TYPE_PRECISION (enumtype) && lookup_attribute ("mode", attributes))
	{
	  ಯದಿ (precision > TYPE_PRECISION (enumtype))
	    {
	      TYPE_PRECISION (enumtype) = 0;
	      error ("specified mode too small for enumerated values");
	    }
	  ಅನ್ಯಥಾ
	    precision = TYPE_PRECISION (enumtype);
	}
      ಅನ್ಯಥಾ
	TYPE_PRECISION (enumtype) = 0;

      ಯದಿ (TYPE_PACKED (enumtype)
	  || precision > TYPE_PRECISION (integer_type_ಗಂಟು)
	  || TYPE_PRECISION (enumtype))
	{
	  tem = c_common_type_for_size (precision, sign == UNSIGNED ? 1 : 0);
	  ಯದಿ (tem == ರಿಕ್ತ)
	    {
	      /* This should only occur when both signed and unsigned
		 values of maximum precision occur among the
		 enumerators.  */
	      pedwarn (ಒಳಹರಿವು_location, 0,
		       "enumeration values exceed range of largest integer");
	      tem = widest_integer_literal_type_ಗಂಟು;
	    }
	  ಅನ್ಯಥಾ ಯದಿ (precision > TYPE_PRECISION (intmax_type_ಗಂಟು)
		   && !ವೃಕ್ಷ_int_cst_lt (minnode,
					TYPE_MIN_ಮೌಲ್ಯ (intmax_type_ಗಂಟು))
		   && !ವೃಕ್ಷ_int_cst_lt (TYPE_MAX_ಮೌಲ್ಯ (uintmax_type_ಗಂಟು),
					maxnode))
	    pedwarn (ಒಳಹರಿವು_location, OPT_Wpedantic,
		     "enumeration values exceed range of %qs",
		     sign == UNSIGNED ? "uintmax_t" : "intmax_t");
	}
      ಅನ್ಯಥಾ
	tem = sign == UNSIGNED ? unsigned_type_ಗಂಟು : integer_type_ಗಂಟು;

      TYPE_MIN_ಮೌಲ್ಯ (enumtype) = TYPE_MIN_ಮೌಲ್ಯ (tem);
      TYPE_MAX_ಮೌಲ್ಯ (enumtype) = TYPE_MAX_ಮೌಲ್ಯ (tem);
      TYPE_UNSIGNED (enumtype) = TYPE_UNSIGNED (tem);
      SET_TYPE_ALIGN (enumtype, TYPE_ALIGN (tem));
      TYPE_SIZE (enumtype) = NULL_ವೃಕ್ಷ;
      TYPE_PRECISION (enumtype) = TYPE_PRECISION (tem);
      ENUM_UNDERLYING_TYPE (enumtype) =
	c_common_type_for_size (TYPE_PRECISION (tem), TYPE_UNSIGNED (tem));

      TYPE_CANONICAL (enumtype) =
	TYPE_CANONICAL (ENUM_UNDERLYING_TYPE (enumtype));
      c_update_type_canonical (enumtype);

      layout_type (enumtype);
    }

  ಯದಿ (ಮೌಲ್ಯಗಳು != error_mark_ಗಂಟು)
    {
      /* Change the type of the enumerators to be the enum type.  We
	 need to do this irrespective of the size of the enum, for
	 proper type checking.  Replace the DECL_INITIALs of the
	 enumerators, and the value slots of the list, with copies
	 that have the enum type; they cannot be modified in place
	 because they may be shared (e.g.  integer_zero_node) Finally,
	 change the purpose slots to point to the names of the decls.  */
      ಪ್ರತಿ (pair = ಮೌಲ್ಯಗಳು; pair; pair = ವೃಕ್ಷ_CHAIN (pair))
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
	  ಯದಿ (!ENUM_FIXED_UNDERLYING_TYPE_P (enumtype) && wider_than_int)
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
  lt = ((ಸಂರಚನಾ lang_type *)
	ggc_internal_cleared_alloc (c_dialect_objc ()
				    ? ಪರಿಮಾಣ (ಸಂರಚನಾ lang_type)
				    : offsetof (ಸಂರಚನಾ lang_type, info)));
  lt->enum_min = minnode;
  lt->enum_max = maxnode;
  TYPE_LANG_SPECIFIC (enumtype) = lt;

  /* Fix up all variant types of this enum type.  */
  ವೃಕ್ಷ incomplete_vars = C_TYPE_INCOMPLETE_VARS (TYPE_MAIN_VARIANT (enumtype));
  ಪ್ರತಿ (tem = TYPE_MAIN_VARIANT (enumtype); tem; tem = TYPE_NEXT_VARIANT (tem))
    {
      C_TYPE_INCOMPLETE_VARS (tem) = NULL_ವೃಕ್ಷ;
      ಯದಿ (tem == enumtype)
	ಅನುವರ್ತ;
      TYPE_ಮೌಲ್ಯಗಳು (tem) = TYPE_ಮೌಲ್ಯಗಳು (enumtype);
      TYPE_MIN_ಮೌಲ್ಯ (tem) = TYPE_MIN_ಮೌಲ್ಯ (enumtype);
      TYPE_MAX_ಮೌಲ್ಯ (tem) = TYPE_MAX_ಮೌಲ್ಯ (enumtype);
      TYPE_SIZE (tem) = TYPE_SIZE (enumtype);
      TYPE_SIZE_UNIT (tem) = TYPE_SIZE_UNIT (enumtype);
      SET_TYPE_MODE (tem, TYPE_MODE (enumtype));
      TYPE_PRECISION (tem) = TYPE_PRECISION (enumtype);
      SET_TYPE_ALIGN (tem, TYPE_ALIGN (enumtype));
      TYPE_USER_ALIGN (tem) = TYPE_USER_ALIGN (enumtype);
      TYPE_UNSIGNED (tem) = TYPE_UNSIGNED (enumtype);
      TYPE_LANG_SPECIFIC (tem) = TYPE_LANG_SPECIFIC (enumtype);
      ENUM_UNDERLYING_TYPE (tem) = ENUM_UNDERLYING_TYPE (enumtype);
      TYPE_PACKED (tem) = TYPE_PACKED (enumtype);
    }

  /* Finish debugging output for this type.  */
  rest_of_type_compilation (enumtype, toplevel);

  finish_incomplete_vars (incomplete_vars, toplevel);

  /* If this enum is defined inside a struct, add it to
     struct_types.  */
  ಯದಿ (warn_cxx_compat
      && struct_parse_info != ರಿಕ್ತ
      && !in_sizeof && !in_typeof && !in_alignof && !in_countof)
    struct_parse_info->struct_types.safe_ತಳ್ಳು (enumtype);

  /* Check for consistency with previous definition */
  ಯದಿ (flag_isoc23)
    {
      ವೃಕ್ಷ vistype = previous_tag (enumtype);
      ಯದಿ (vistype
	  && ವೃಕ್ಷ_CODE (vistype) == ವೃಕ್ಷ_CODE (enumtype)
	  && !C_TYPE_BEING_DEFINED (vistype))
	{
	  TYPE_STUB_DECL (enumtype) = TYPE_STUB_DECL (vistype);
	  ಯದಿ (!comptypes_same_p (enumtype, vistype))
	    error("conflicting redefinition of enum %qT", enumtype);
	}
    }

  C_TYPE_BEING_DEFINED (enumtype) = 0;

  ಪ್ರತ್ಯಾಗಮ enumtype;
}

/* Build and install a CONST_DECL for one value of the
   current enumeration type (one that was begun with start_enum).
   DECL_LOC is the location of the enumerator.
   LOC is the location of the '=' operator if any, DECL_LOC otherwise.
   Return a tree-list containing the CONST_DECL and its value.
   Assignment of sequential values by default is handled here.  */

ವೃಕ್ಷ
build_enumerator (location_t decl_loc, location_t loc,
		  ಸಂರಚನಾ c_enum_contents *the_enum, ವೃಕ್ಷ name, ವೃಕ್ಷ ಮೌಲ್ಯ)
{
  ವೃಕ್ಷ decl;
  ವೃಕ್ಷ old_decl;

  /* Validate and default VALUE.  */

  ಯದಿ (ಮೌಲ್ಯ != NULL_ವೃಕ್ಷ)
    {
      /* Don't issue more errors for error_mark_node (i.e. an
	 undeclared identifier) - just ignore the value expression.  */
      ಯದಿ (ಮೌಲ್ಯ == error_mark_ಗಂಟು)
	ಮೌಲ್ಯ = NULL_ವೃಕ್ಷ;
      ಅನ್ಯಥಾ ಯದಿ (!INTEGRAL_TYPE_P (ವೃಕ್ಷ_TYPE (ಮೌಲ್ಯ)))
	{
	  error_at (loc, "enumerator value for %qE is not an integer constant",
		    name);
	  ಮೌಲ್ಯ = NULL_ವೃಕ್ಷ;
	}
      ಅನ್ಯಥಾ
	{
	  ಯದಿ (ವೃಕ್ಷ_CODE (ಮೌಲ್ಯ) != INTEGER_CST)
	    {
	      ಮೌಲ್ಯ = c_fully_fold (ಮೌಲ್ಯ, ಅಸತ್ಯ, ರಿಕ್ತ);
	      ಯದಿ (ವೃಕ್ಷ_CODE (ಮೌಲ್ಯ) == INTEGER_CST)
		pedwarn (loc, OPT_Wpedantic,
			 "enumerator value for %qE is not an integer "
			 "constant expression", name);
	    }
	  ಯದಿ (ವೃಕ್ಷ_CODE (ಮೌಲ್ಯ) != INTEGER_CST)
	    {
	      error ("enumerator value for %qE is not an integer constant",
		     name);
	      ಮೌಲ್ಯ = NULL_ವೃಕ್ಷ;
	    }
	  ಅನ್ಯಥಾ
	    {
	      ಮೌಲ್ಯ = default_conversion (ಮೌಲ್ಯ);
	      constant_expression_warning (ಮೌಲ್ಯ);
	    }
	}
    }

  /* Default based on previous value.  */
  /* It should no longer be possible to have NON_LVALUE_EXPR
     in the default.  */
  ಯದಿ (ಮೌಲ್ಯ == NULL_ವೃಕ್ಷ)
    {
      ಮೌಲ್ಯ = the_enum->enum_next_ಮೌಲ್ಯ;
      ಯದಿ (the_enum->enum_overflow)
	error_at (loc, "overflow in enumeration values");
    }
  ಯದಿ (ENUM_FIXED_UNDERLYING_TYPE_P (the_enum->enum_type))
    {
      /* Enumeration constants must fit in the fixed underlying type.  */
      ಯದಿ (!int_fits_type_p (ಮೌಲ್ಯ, ENUM_UNDERLYING_TYPE (the_enum->enum_type)))
	error_at (loc,
		  "enumerator value outside the range of underlying type");
      /* Enumeration constants for an enum with fixed underlying type
	 have the enum type, both inside and outside the
	 definition.  */
      ಮೌಲ್ಯ = convert (the_enum->enum_type, ಮೌಲ್ಯ);
    }
  ಅನ್ಯಥಾ ಯದಿ (flag_isoc23
	   && (old_decl = lookup_name_in_scope (name, current_scope))
	   && old_decl != error_mark_ಗಂಟು
	   && ವೃಕ್ಷ_TYPE (old_decl)
	   && ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_TYPE (old_decl))
	   && ವೃಕ್ಷ_CODE (old_decl) == CONST_DECL)
    {
      /* Enumeration constants in a redeclaration have the previous type.  */
      ವೃಕ್ಷ previous_type = ವೃಕ್ಷ_TYPE (DECL_INITIAL (old_decl));
      ಯದಿ (!int_fits_type_p (ಮೌಲ್ಯ, previous_type))
	{
	  error_at (loc, "value of redeclared enumerator outside the range "
			 "of %qT", previous_type);
	  locate_old_decl (old_decl);
	}
      ಮೌಲ್ಯ = convert (previous_type, ಮೌಲ್ಯ);
    }
  ಅನ್ಯಥಾ
    {
      /* Even though the underlying type of an enum is unspecified, the
	 type of enumeration constants is explicitly defined as int
	 (6.4.4.3/2 in the C99 Standard).  C23 allows any integer type, and
	 GCC allows such types for older standards as an extension.  */
      ತಾರ್ಕಿಕ warned_range = ಅಸತ್ಯ;
      ಯದಿ (!int_fits_type_p (ಮೌಲ್ಯ,
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
      ಯದಿ (!warned_range && !int_fits_type_p (ಮೌಲ್ಯ, integer_type_ಗಂಟು))
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
      ಯದಿ (int_fits_type_p (ಮೌಲ್ಯ, integer_type_ಗಂಟು))
	ಮೌಲ್ಯ = convert (integer_type_ಗಂಟು, ಮೌಲ್ಯ);
    }

  /* Set basis for default for next value.  */
  ಯದಿ (ENUM_FIXED_UNDERLYING_TYPE_P (the_enum->enum_type))
    {
      ವೃಕ್ಷ underlying_type = ENUM_UNDERLYING_TYPE (the_enum->enum_type);
      ಯದಿ (ವೃಕ್ಷ_CODE (underlying_type) == BOOLEAN_TYPE)
	/* A value of 2 following a value of 1 overflows bool, but we
	   cannot carry out addition directly on bool without
	   promotion, and converting the result of arithmetic in a
	   wider type back to bool would not produce the right result
	   for this overflow check.  */
	the_enum->enum_next_ಮೌಲ್ಯ = invert_truthvalue_loc (loc, ಮೌಲ್ಯ);
      ಅನ್ಯಥಾ
	the_enum->enum_next_ಮೌಲ್ಯ
	  = build_ದ್ವಿಮಾನ_op (ಅಭಿವ್ಯಕ್ತಿ_LOC_OR_LOC (ಮೌಲ್ಯ, ಒಳಹರಿವು_location),
			     PLUS_ಅಭಿವ್ಯಕ್ತಿ, convert (underlying_type, ಮೌಲ್ಯ),
			     convert (underlying_type, integer_one_ಗಂಟು),
			     ಅಸತ್ಯ);
    }
  ಅನ್ಯಥಾ
    {
      /* In a redeclaration the type can already be the enumeral type.  */
      ಯದಿ (ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (ಮೌಲ್ಯ)) == ENUMERAL_TYPE)
	ಮೌಲ್ಯ = convert (ENUM_UNDERLYING_TYPE (ವೃಕ್ಷ_TYPE (ಮೌಲ್ಯ)), ಮೌಲ್ಯ);
      the_enum->enum_next_ಮೌಲ್ಯ
	= build_ದ್ವಿಮಾನ_op (ಅಭಿವ್ಯಕ್ತಿ_LOC_OR_LOC (ಮೌಲ್ಯ, ಒಳಹರಿವು_location),
			   PLUS_ಅಭಿವ್ಯಕ್ತಿ, ಮೌಲ್ಯ, integer_one_ಗಂಟು, ಅಸತ್ಯ);
    }
  the_enum->enum_overflow = ವೃಕ್ಷ_int_cst_lt (the_enum->enum_next_ಮೌಲ್ಯ, ಮೌಲ್ಯ);
  ಯದಿ (the_enum->enum_overflow
      && !ENUM_FIXED_UNDERLYING_TYPE_P (the_enum->enum_type))
    {
      /* Choose a wider type with the same signedness if
	 available.  */
      ಪೂರ್ಣಾಙ್ಕ prec = TYPE_PRECISION (ವೃಕ್ಷ_TYPE (ಮೌಲ್ಯ)) + 1;
      ತಾರ್ಕಿಕ unsignedp = TYPE_UNSIGNED (ವೃಕ್ಷ_TYPE (ಮೌಲ್ಯ));
      ವೃಕ್ಷ new_type = (unsignedp
		       ? long_unsigned_type_ಗಂಟು
		       : long_integer_type_ಗಂಟು);
      ಯದಿ (prec > TYPE_PRECISION (new_type))
	new_type = (unsignedp
		    ? long_long_unsigned_type_ಗಂಟು
		    : long_long_integer_type_ಗಂಟು);
      ಯದಿ (prec > TYPE_PRECISION (new_type))
	new_type = (unsignedp
		    ? widest_unsigned_literal_type_ಗಂಟು
		    : widest_integer_literal_type_ಗಂಟು);
      ಯದಿ (prec <= TYPE_PRECISION (new_type))
	{
	  the_enum->enum_overflow = ಅಸತ್ಯ;
	  the_enum->enum_next_ಮೌಲ್ಯ
	    = build_ದ್ವಿಮಾನ_op (ಅಭಿವ್ಯಕ್ತಿ_LOC_OR_LOC (ಮೌಲ್ಯ, ಒಳಹರಿವು_location),
			       PLUS_ಅಭಿವ್ಯಕ್ತಿ, convert (new_type, ಮೌಲ್ಯ),
			       integer_one_ಗಂಟು, ಅಸತ್ಯ);
	  gcc_assert (!ವೃಕ್ಷ_int_cst_lt (the_enum->enum_next_ಮೌಲ್ಯ, ಮೌಲ್ಯ));
	}
    }

  /* Now create a declaration for the enum value name.  */

  decl = build_decl (decl_loc, CONST_DECL, name, ವೃಕ್ಷ_TYPE (ಮೌಲ್ಯ));
  DECL_INITIAL (decl) = ಮೌಲ್ಯ;
  DECL_CONTEXT (decl) = the_enum->enum_type;
  pushdecl (decl);

  ಪ್ರತ್ಯಾಗಮ ವೃಕ್ಷ_cons (decl, ಮೌಲ್ಯ, NULL_ವೃಕ್ಷ);
}

/* Implement LANG_HOOKS_SIMULATE_ENUM_DECL.  */

ವೃಕ್ಷ
c_simulate_enum_decl (location_t loc, ಧ್ರುವ ವರ್ಣ *name,
		      vec<string_int_pair> *ಮೌಲ್ಯಗಳು_ptr)
{
  location_t saved_loc = ಒಳಹರಿವು_location;
  ಒಳಹರಿವು_location = loc;

  ಸಂರಚನಾ c_enum_contents the_enum;
  ವೃಕ್ಷ enumtype = start_enum (loc, &the_enum, get_identifier (name),
			      NULL_ವೃಕ್ಷ, ಅಸತ್ಯ);

  ವೃಕ್ಷ ಮೌಲ್ಯ_chain = NULL_ವೃಕ್ಷ;
  string_int_pair *ಮೌಲ್ಯ;
  vec<string_int_pair> ಮೌಲ್ಯಗಳು = *ಮೌಲ್ಯಗಳು_ptr;
  unsigned ಪೂರ್ಣಾಙ್ಕ i;
  FOR_EACH_VEC_ELT (ಮೌಲ್ಯಗಳು, i, ಮೌಲ್ಯ)
    {
      ವೃಕ್ಷ decl = build_enumerator (loc, loc, &the_enum,
				    get_identifier (ಮೌಲ್ಯ->first),
				    build_int_cst (integer_type_ಗಂಟು,
						   ಮೌಲ್ಯ->second));
      ವೃಕ್ಷ_CHAIN (decl) = ಮೌಲ್ಯ_chain;
      ಮೌಲ್ಯ_chain = decl;
    }

  finish_enum (enumtype, nreverse (ಮೌಲ್ಯ_chain), NULL_ವೃಕ್ಷ);

  ಒಳಹರಿವು_location = saved_loc;
  ಪ್ರತ್ಯಾಗಮ enumtype;
}

/* Implement LANG_HOOKS_SIMULATE_RECORD_DECL.  */

ವೃಕ್ಷ
c_simulate_record_decl (location_t loc, ಧ್ರುವ ವರ್ಣ *name,
			array_slice<ಧ್ರುವ ವೃಕ್ಷ> fields)
{
  location_t saved_loc = ಒಳಹರಿವು_location;
  ಒಳಹರಿವು_location = loc;

  ವರ್ಗ c_struct_parse_info *struct_info;
  ವೃಕ್ಷ ident = get_identifier (name);
  ವೃಕ್ಷ type = start_struct (loc, RECORD_TYPE, ident, &struct_info);

  ಪ್ರತಿ (unsigned ಪೂರ್ಣಾಙ್ಕ i = 0; i < fields.size (); ++i)
    {
      DECL_FIELD_CONTEXT (fields[i]) = type;
      ಯದಿ (i > 0)
	DECL_CHAIN (fields[i - 1]) = fields[i];
    }

  finish_struct (loc, type, fields[0], NULL_ವೃಕ್ಷ, struct_info);

  ವೃಕ್ಷ decl = build_decl (loc, TYPE_DECL, ident, type);
  set_underlying_type (decl);
  lang_hooks.decls.pushdecl (decl);

  ಒಳಹರಿವು_location = saved_loc;
  ಪ್ರತ್ಯಾಗಮ type;
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
start_function (ಸಂರಚನಾ c_declspecs *declspecs, ಸಂರಚನಾ c_declarator *declarator,
		ವೃಕ್ಷ attributes)
{
  ವೃಕ್ಷ decl1, old_decl;
  ವೃಕ್ಷ restype, resdecl;
  location_t loc;
  location_t result_loc;
  ವೃಕ್ಷ ಅಭಿವ್ಯಕ್ತಿ = ರಿಕ್ತ;

  current_function_returns_ಮೌಲ್ಯ = 0;  /* Assume, until we see it does.  */
  current_function_returns_null = 0;
  current_function_returns_abnormally = 0;
  warn_about_return_type = 0;
  c_switch_ರಾಶಿ = ರಿಕ್ತ;

  /* Indicate no valid break/continue context.  */
  in_statement = 0;

  decl1 = grokdeclarator (declarator, declspecs, FUNCDEF, ಸತ್ಯ, ರಿಕ್ತ,
			  &attributes, &ಅಭಿವ್ಯಕ್ತಿ, ರಿಕ್ತ, DEPRECATED_NORMAL);
  invoke_plugin_callbacks (PLUGIN_START_PARSE_FUNCTION, decl1);

  /* If the declarator is not suitable for a function definition,
     cause a syntax error.  */
  ಯದಿ (decl1 == NULL_ವೃಕ್ಷ
      || ವೃಕ್ಷ_CODE (decl1) != FUNCTION_DECL)
    ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;

  /* Nested functions may have variably modified (return) type.
     Make sure the size expression is evaluated at this point.  */
  ಯದಿ (ಅಭಿವ್ಯಕ್ತಿ && !current_scope->parm_flag)
    add_stmt (fold_convert (void_type_ಗಂಟು, ಅಭಿವ್ಯಕ್ತಿ));

  loc = DECL_SOURCE_LOCATION (decl1);

  /* A nested function is not global.  */
  ಯದಿ (current_function_decl != NULL_ವೃಕ್ಷ)
    ವೃಕ್ಷ_PUBLIC (decl1) = 0;

  c_decl_attributes (&decl1, attributes, 0);

  ಯದಿ (DECL_DECLARED_INLINE_P (decl1)
      && DECL_UNINLINABLE (decl1)
      && lookup_attribute ("noinline", DECL_ATTRIBUTES (decl1)))
    {
      auto_urlify_attributes sentinel;
      warning_at (loc, OPT_Wattributes,
		  "inline function %qD given attribute %qs",
		  decl1, "noinline");
    }

  /* Handle gnu_inline attribute.  */
  ಯದಿ (declspecs->inline_p
      && !flag_gnu89_inline
      && ವೃಕ್ಷ_CODE (decl1) == FUNCTION_DECL
      && (lookup_attribute ("gnu_inline", DECL_ATTRIBUTES (decl1))
	  || current_function_decl))
    {
      ಯದಿ (declspecs->storage_class != csc_static)
	DECL_EXTERNAL (decl1) = !DECL_EXTERNAL (decl1);
    }

  announce_function (decl1);

  ಯದಿ (!COMPLETE_OR_VOID_TYPE_P (ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_TYPE (decl1))))
    {
      error_at (loc, "return type is an incomplete type");
      /* Make it return void instead.  */
      ವೃಕ್ಷ_TYPE (decl1)
	= c_build_function_type (void_type_ಗಂಟು,
				 TYPE_ARG_TYPES (ವೃಕ್ಷ_TYPE (decl1)),
				 TYPE_NO_NAMED_ARGS_STDARG_P (ವೃಕ್ಷ_TYPE (decl1)));
    }

  ಯದಿ (warn_about_return_type)
    permerror_opt (loc, flag_isoc99 ? OPT_Wimplicit_int
		   : (warn_return_type > 0 ? OPT_Wreturn_type
		      : OPT_Wimplicit_int),
		   "return type defaults to %<int%>");

  /* Make the init_value nonzero so pushdecl knows this is not tentative.
     error_mark_node is replaced below (in pop_scope) with the BLOCK.  */
  DECL_INITIAL (decl1) = error_mark_ಗಂಟು;

  /* If this definition isn't a prototype and we had a prototype declaration
     before, copy the arg type info from that prototype.  */
  old_decl = lookup_name_in_scope (DECL_NAME (decl1), current_scope);
  ಯದಿ (old_decl && ವೃಕ್ಷ_CODE (old_decl) != FUNCTION_DECL)
    old_decl = NULL_ವೃಕ್ಷ;

  current_function_prototype_locus = UNKNOWN_LOCATION;
  current_function_prototype_built_in = ಅಸತ್ಯ;
  current_function_prototype_arg_types = NULL_ವೃಕ್ಷ;
  ವೃಕ್ಷ newtype = ವೃಕ್ಷ_TYPE (decl1);
  ವೃಕ್ಷ oldtype = old_decl ? ವೃಕ್ಷ_TYPE (old_decl) : newtype;
  ಯದಿ (!prototype_p (newtype))
    {
      ವೃಕ್ಷ oldrt = ವೃಕ್ಷ_TYPE (oldtype);
      ವೃಕ್ಷ newrt = ವೃಕ್ಷ_TYPE (newtype);
      ಯದಿ (old_decl != NULL_ವೃಕ್ಷ
	  && ವೃಕ್ಷ_CODE (oldtype) == FUNCTION_TYPE
	  && comptypes (oldrt, newrt)
	  && !TYPE_NO_NAMED_ARGS_STDARG_P (oldtype))
	{
	  ಯದಿ (stdarg_p (oldtype))
	    {
	      auto_diagnostic_group d;
	      warning_at (loc, 0, "%q+D defined as variadic function "
			  "without prototype", decl1);
	      locate_old_decl (old_decl);
	    }
	  ವೃಕ್ಷ_TYPE (decl1) = composite_type (oldtype, newtype);
	  current_function_prototype_locus = DECL_SOURCE_LOCATION (old_decl);
	  current_function_prototype_built_in
	    = C_DECL_BUILTIN_PROTOTYPE (old_decl);
	  current_function_prototype_arg_types
	    = TYPE_ARG_TYPES (newtype);
	}
      ಯದಿ (ವೃಕ್ಷ_PUBLIC (decl1))
	{
	  /* If there is an external prototype declaration of this
	     function, record its location but do not copy information
	     to this decl.  This may be an invisible declaration
	     (built-in or in a scope which has finished) or simply
	     have more refined argument types than any declaration
	     found above.  */
	  ಸಂರಚನಾ c_binding *b;
	  ಪ್ರತಿ (b = I_ಚಿಹ್ನೆ_BINDING (DECL_NAME (decl1)); b; b = b->shadowed)
	    ಯದಿ (B_IN_SCOPE (b, external_scope))
	      ಭಙ್ಗ;
	  ಯದಿ (b)
	    {
	      ವೃಕ್ಷ ext_decl, ext_type;
	      ext_decl = b->decl;
	      ext_type = b->u.type ? b->u.type : ವೃಕ್ಷ_TYPE (ext_decl);
	      ಯದಿ (ವೃಕ್ಷ_CODE (ext_type) == FUNCTION_TYPE
		  && comptypes (ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_TYPE (decl1)),
				ವೃಕ್ಷ_TYPE (ext_type)))
		{
		  current_function_prototype_locus
		    = DECL_SOURCE_LOCATION (ext_decl);
		  current_function_prototype_built_in
		    = C_DECL_BUILTIN_PROTOTYPE (ext_decl);
		  current_function_prototype_arg_types
		    = TYPE_ARG_TYPES (ext_type);
		}
	    }
	}
    }

  /* Optionally warn about C23 compatibility.  */
  ಯದಿ (warn_deprecated_non_prototype
      && old_decl != NULL_ವೃಕ್ಷ
      && ವೃಕ್ಷ_CODE (oldtype) == FUNCTION_TYPE
      && !TYPE_ARG_TYPES (oldtype)
      && !TYPE_NO_NAMED_ARGS_STDARG_P (oldtype)
      && (TYPE_ARG_TYPES (newtype)
	  && ವೃಕ್ಷ_ಮೌಲ್ಯ (TYPE_ARG_TYPES (newtype)) != void_type_ಗಂಟು))
    {
      ತಾರ್ಕಿಕ warned = warning_at (loc, OPT_Wdeprecated_non_prototype,
				"ISO C23 does not allow defining"
				" parameters for function %qE declared"
				" without parameters",
				decl1);
      ಯದಿ (warned)
	inform (DECL_SOURCE_LOCATION (old_decl), "declared here");
    }

  /* Optionally warn of old-fashioned def with no previous prototype.  */
  ಯದಿ (warn_strict_prototypes
      && old_decl != error_mark_ಗಂಟು
      && !prototype_p (ವೃಕ್ಷ_TYPE (decl1))
      && C_DECL_ISNT_PROTOTYPE (old_decl))
    warning_at (loc, OPT_Wstrict_prototypes,
		"function declaration isn%'t a prototype");
  /* Optionally warn of any global def with no previous prototype.  */
  ಅನ್ಯಥಾ ಯದಿ (warn_missing_prototypes
	   && old_decl != error_mark_ಗಂಟು
	   && ವೃಕ್ಷ_PUBLIC (decl1)
	   && !MAIN_NAME_P (DECL_NAME (decl1))
	   && C_DECL_ISNT_PROTOTYPE (old_decl)
	   && !DECL_DECLARED_INLINE_P (decl1))
    warning_at (loc, OPT_Wmissing_prototypes,
		"no previous prototype for %qD", decl1);
  /* Optionally warn of any def with no previous prototype
     if the function has already been used.  */
  ಅನ್ಯಥಾ ಯದಿ (warn_missing_prototypes
	   && old_decl != NULL_ವೃಕ್ಷ
	   && old_decl != error_mark_ಗಂಟು
	   && ವೃಕ್ಷ_USED (old_decl)
	   && !prototype_p (ವೃಕ್ಷ_TYPE (old_decl)))
    warning_at (loc, OPT_Wmissing_prototypes,
		"%qD was used with no prototype before its definition", decl1);
  /* Optionally warn of any global def with no previous declaration.  */
  ಅನ್ಯಥಾ ಯದಿ (warn_missing_declarations
	   && ವೃಕ್ಷ_PUBLIC (decl1)
	   && old_decl == NULL_ವೃಕ್ಷ
	   && !MAIN_NAME_P (DECL_NAME (decl1))
	   && !DECL_DECLARED_INLINE_P (decl1))
    warning_at (loc, OPT_Wmissing_declarations,
		"no previous declaration for %qD",
		decl1);
  /* Optionally warn of any def with no previous declaration
     if the function has already been used.  */
  ಅನ್ಯಥಾ ಯದಿ (warn_missing_declarations
	   && old_decl != NULL_ವೃಕ್ಷ
	   && old_decl != error_mark_ಗಂಟು
	   && ವೃಕ್ಷ_USED (old_decl)
	   && C_DECL_IMPLICIT (old_decl))
    warning_at (loc, OPT_Wmissing_declarations,
		"%qD was used with no declaration before its definition", decl1);

  /* This function exists in static storage.
     (This does not mean `static' in the C sense!)  */
  ವೃಕ್ಷ_STATIC (decl1) = 1;

  /* This is the earliest point at which we might know the assembler
     name of the function.  Thus, if it's set before this, die horribly.  */
  gcc_assert (!DECL_ASSEMBLER_NAME_SET_P (decl1));

  /* If #pragma weak was used, mark the decl weak now.  */
  ಯದಿ (current_scope == file_scope)
    maybe_apply_pragma_weak (decl1);

  /* Warn for unlikely, improbable, or stupid declarations of `main'.  */
  ಯದಿ (warn_main && MAIN_NAME_P (DECL_NAME (decl1)))
    {
      ಯದಿ (TYPE_MAIN_VARIANT (ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_TYPE (decl1)))
	  != integer_type_ಗಂಟು)
	pedwarn (loc, OPT_Wmain, "return type of %qD is not %<int%>", decl1);
      ಅನ್ಯಥಾ ಯದಿ (TYPE_ATOMIC (ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_TYPE (decl1))))
	pedwarn (loc, OPT_Wmain, "%<_Atomic%>-qualified return type of %qD",
		 decl1);

      check_main_parameter_types (decl1);

      ಯದಿ (!ವೃಕ್ಷ_PUBLIC (decl1))
	pedwarn (loc, OPT_Wmain,
		 "%qD is normally a non-static function", decl1);
    }

  ವೃಕ್ಷ parms = current_function_arg_info->parms;
  ಯದಿ (old_decl)
    {
      location_t origloc = DECL_SOURCE_LOCATION (old_decl);
      warn_parms_array_mismatch (origloc, old_decl, parms);
    }

  /* To enable versions to be created across TU's we mark and mangle all
     non-default versioned functions.  */
  ಯದಿ (ವೃಕ್ಷ_CODE (decl1) == FUNCTION_DECL
      && !TARGET_HAS_FMV_TARGET_ATTRIBUTE
      && get_target_version (decl1).is_valid ())
    {
      maybe_mark_function_versioned (decl1);
      ಯದಿ (current_scope != file_scope)
	error ("versioned definitions are only allowed at file scope");
    }

  /* Record the decl so that the function name is defined.
     If we already have a decl for this name, and it is a FUNCTION_DECL,
     use the old decl.  */

  current_function_decl = pushdecl (decl1);

  ಯದಿ (ವೃಕ್ಷ access = build_attr_access_from_parms (parms, ಅಸತ್ಯ))
    decl_attributes (&current_function_decl, access, ATTR_FLAG_INTERNAL,
		     old_decl);

  ತಳ್ಳು_scope ();
  declare_parm_level ();

  /* Set the result decl source location to the location of the typespec.  */
  result_loc = (declspecs->locations[cdw_typespec] == UNKNOWN_LOCATION
		? loc : declspecs->locations[cdw_typespec]);
  restype = ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_TYPE (current_function_decl));
  resdecl = build_decl (result_loc, RESULT_DECL, NULL_ವೃಕ್ಷ, restype);
  DECL_ARTIFICIAL (resdecl) = 1;
  DECL_IGNORED_P (resdecl) = 1;
  DECL_RESULT (current_function_decl) = resdecl;

  start_fname_decls ();

  ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
}

/* Subroutine of store_parm_decls which handles new-style function
   definitions (prototype format). The parms already have decls, so we
   need only record them as in effect and complain if any redundant
   old-style parm decls were written.  */
ಸ್ಥಿರ ಶೂನ್ಯ
store_parm_decls_newstyle (ವೃಕ್ಷ fndecl, ಧ್ರುವ ಸಂರಚನಾ c_arg_info *arg_info)
{
  ವೃಕ್ಷ decl;
  c_arg_tag *tag;
  unsigned ix;

  ಯದಿ (current_scope->bindings)
    {
      error_at (DECL_SOURCE_LOCATION (fndecl),
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
  ಅನ್ಯಥಾ ಯದಿ (!in_system_header_at (ಒಳಹರಿವು_location)
	   && !current_function_scope
	   && arg_info->types != error_mark_ಗಂಟು
	   && !arg_info->c23_empty_parens)
    warning_at (DECL_SOURCE_LOCATION (fndecl), OPT_Wtraditional,
		"traditional C rejects ISO C style function definitions");

  /* Now make all the parameter declarations visible in the function body.
     We can bypass most of the grunt work of pushdecl.  */
  ಪ್ರತಿ (decl = arg_info->parms; decl; decl = DECL_CHAIN (decl))
    {
      DECL_CONTEXT (decl) = current_function_decl;
      ಯದಿ (DECL_NAME (decl))
	{
	  bind (DECL_NAME (decl), decl, current_scope,
		/*invisible=*/ಅಸತ್ಯ, /*nested=*/ಅಸತ್ಯ,
		UNKNOWN_LOCATION);
	  ಯದಿ (!ವೃಕ್ಷ_USED (decl))
	    warn_if_shadowing (decl);
	}
      ಅನ್ಯಥಾ
	pedwarn_c11 (DECL_SOURCE_LOCATION (decl), OPT_Wmissing_parameter_name,
		     "ISO C does not support omitting parameter names in "
		     "function definitions before C23");
    }

  /* Record the parameter list in the function declaration.  */
  DECL_ARGUMENTS (fndecl) = arg_info->parms;

  /* Now make all the ancillary declarations visible, likewise.  */
  ಪ್ರತಿ (decl = arg_info->others; decl; decl = DECL_CHAIN (decl))
    {
      DECL_CONTEXT (decl) = current_function_decl;
      ಯದಿ (DECL_NAME (decl))
	bind (DECL_NAME (decl), decl, current_scope,
	      /*invisible=*/ಅಸತ್ಯ,
	      /*nested=*/(ವೃಕ್ಷ_CODE (decl) == FUNCTION_DECL),
	      UNKNOWN_LOCATION);
    }

  /* And all the tag declarations.  */
  FOR_EACH_VEC_SAFE_ELT_REVERSE (arg_info->tags, ix, tag)
    ಯದಿ (tag->id)
      bind (tag->id, tag->type, current_scope,
	    /*invisible=*/ಅಸತ್ಯ, /*nested=*/ಅಸತ್ಯ, UNKNOWN_LOCATION);
}

/* Subroutine of store_parm_decls which handles old-style function
   definitions (separate parameter list and declarations).  */

ಸ್ಥಿರ ಶೂನ್ಯ
store_parm_decls_oldstyle (ವೃಕ್ಷ fndecl, ಧ್ರುವ ಸಂರಚನಾ c_arg_info *arg_info)
{
  ಸಂರಚನಾ c_binding *b;
  ವೃಕ್ಷ parm, decl, last;
  ವೃಕ್ಷ parmids = arg_info->parms;
  hash_set<ವೃಕ್ಷ> seen_args;

  ಯದಿ (!in_system_header_at (ಒಳಹರಿವು_location))
    {
      ಯದಿ (flag_isoc23)
	pedwarn (DECL_SOURCE_LOCATION (fndecl),
		 OPT_Wold_style_definition, "old-style function definition");
      ಅನ್ಯಥಾ
	warning_at (DECL_SOURCE_LOCATION (fndecl),
		    OPT_Wold_style_definition,
		    "old-style function definition");
    }

  ಯದಿ (current_scope->had_vla_unspec)
    error ("%<[*]%> not allowed in other than function prototype scope");

  /* Match each formal parameter name with its declaration.  Save each
     decl in the appropriate TREE_PURPOSE slot of the parmids chain.  */
  ಪ್ರತಿ (parm = parmids; parm; parm = ವೃಕ್ಷ_CHAIN (parm))
    {
      ಯದಿ (ವೃಕ್ಷ_ಮೌಲ್ಯ (parm) == NULL_ವೃಕ್ಷ)
	{
	  error_at (DECL_SOURCE_LOCATION (fndecl),
		    "parameter name missing from parameter list");
	  ವೃಕ್ಷ_PURPOSE (parm) = NULL_ವೃಕ್ಷ;
	  ಅನುವರ್ತ;
	}

      b = I_ಚಿಹ್ನೆ_BINDING (ವೃಕ್ಷ_ಮೌಲ್ಯ (parm));
      ಯದಿ (b && B_IN_CURRENT_SCOPE (b))
	{
	  decl = b->decl;
	  /* Skip erroneous parameters.  */
	  ಯದಿ (decl == error_mark_ಗಂಟು)
	    ಅನುವರ್ತ;
	  /* If we got something other than a PARM_DECL it is an error.  */
	  ಯದಿ (ವೃಕ್ಷ_CODE (decl) != PARM_DECL)
	    {
	      error_at (DECL_SOURCE_LOCATION (decl),
			"%qD declared as a non-parameter", decl);
	      ಅನುವರ್ತ;
	    }
	  /* If the declaration is already marked, we have a duplicate
	     name.  Complain and ignore the duplicate.  */
	  ಅನ್ಯಥಾ ಯದಿ (seen_args.contains (decl))
	    {
	      error_at (DECL_SOURCE_LOCATION (decl),
			"multiple parameters named %qD", decl);
	      ವೃಕ್ಷ_PURPOSE (parm) = NULL_ವೃಕ್ಷ;
	      ಅನುವರ್ತ;
	    }
	  /* If the declaration says "void", complain and turn it into
	     an int.  */
	  ಅನ್ಯಥಾ ಯದಿ (VOID_TYPE_P (ವೃಕ್ಷ_TYPE (decl)))
	    {
	      error_at (DECL_SOURCE_LOCATION (decl),
			"parameter %qD declared with void type", decl);
	      ವೃಕ್ಷ_TYPE (decl) = integer_type_ಗಂಟು;
	      DECL_ARG_TYPE (decl) = integer_type_ಗಂಟು;
	      layout_decl (decl, 0);
	    }
	  warn_if_shadowing (decl);
	}
      /* If no declaration found, default to int.  */
      ಅನ್ಯಥಾ
	{
	  /* FIXME diagnostics: This should be the location of the argument,
	     not the FNDECL.  E.g., for an old-style declaration

	       int f10(v) { blah; }

	     We should use the location of the V, not the F10.
	     Unfortunately, the V is an IDENTIFIER_NODE which has no
	     location.  In the future we need locations for c_arg_info
	     entries.

	     See gcc.dg/Wshadow-3.c for an example of this problem. */
	  decl = build_decl (DECL_SOURCE_LOCATION (fndecl),
			     PARM_DECL, ವೃಕ್ಷ_ಮೌಲ್ಯ (parm), integer_type_ಗಂಟು);
	  DECL_ARG_TYPE (decl) = ವೃಕ್ಷ_TYPE (decl);
	  pushdecl (decl);
	  warn_if_shadowing (decl);

	  ಯದಿ (flag_isoc99)
	    permerror_opt (DECL_SOURCE_LOCATION (decl),
			   OPT_Wimplicit_int, "type of %qD defaults to %<int%>",
			   decl);
	  ಅನ್ಯಥಾ
	    warning_at (DECL_SOURCE_LOCATION (decl),
			OPT_Wmissing_parameter_type,
			"type of %qD defaults to %<int%>", decl);
	}

      ವೃಕ್ಷ_PURPOSE (parm) = decl;
      seen_args.add (decl);
    }

  /* Now examine the parms chain for incomplete declarations
     and declarations with no corresponding names.  */

  ಪ್ರತಿ (b = current_scope->bindings; b; b = b->prev)
    {
      parm = b->decl;
      ಯದಿ (ವೃಕ್ಷ_CODE (parm) != PARM_DECL)
	ಅನುವರ್ತ;

      ಯದಿ (ವೃಕ್ಷ_TYPE (parm) != error_mark_ಗಂಟು
	  && !COMPLETE_TYPE_P (ವೃಕ್ಷ_TYPE (parm)))
	{
	  error_at (DECL_SOURCE_LOCATION (parm),
		    "parameter %qD has incomplete type", parm);
	  ವೃಕ್ಷ_TYPE (parm) = error_mark_ಗಂಟು;
	}

      ಯದಿ (!seen_args.contains (parm))
	{
	  error_at (DECL_SOURCE_LOCATION (parm),
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

  ಪ್ರತಿ (parm = parmids; parm; parm = ವೃಕ್ಷ_CHAIN (parm))
    ಯದಿ (ವೃಕ್ಷ_PURPOSE (parm))
      ಭಙ್ಗ;
  ಯದಿ (parm && ವೃಕ್ಷ_PURPOSE (parm))
    {
      last = ವೃಕ್ಷ_PURPOSE (parm);
      DECL_ARGUMENTS (fndecl) = last;

      ಪ್ರತಿ (parm = ವೃಕ್ಷ_CHAIN (parm); parm; parm = ವೃಕ್ಷ_CHAIN (parm))
	ಯದಿ (ವೃಕ್ಷ_PURPOSE (parm))
	  {
	    DECL_CHAIN (last) = ವೃಕ್ಷ_PURPOSE (parm);
	    last = ವೃಕ್ಷ_PURPOSE (parm);
	  }
      DECL_CHAIN (last) = NULL_ವೃಕ್ಷ;
    }

  /* If there was a previous prototype,
     set the DECL_ARG_TYPE of each argument according to
     the type previously specified, and report any mismatches.  */

  ಯದಿ (current_function_prototype_arg_types)
    {
      ವೃಕ್ಷ type;
      ಪ್ರತಿ (parm = DECL_ARGUMENTS (fndecl),
	     type = current_function_prototype_arg_types;
	   parm || (type != NULL_ವೃಕ್ಷ
		    && ವೃಕ್ಷ_ಮೌಲ್ಯ (type) != error_mark_ಗಂಟು
		    && TYPE_MAIN_VARIANT (ವೃಕ್ಷ_ಮೌಲ್ಯ (type)) != void_type_ಗಂಟು);
	   parm = DECL_CHAIN (parm), type = ವೃಕ್ಷ_CHAIN (type))
	{
	  ಯದಿ (parm == NULL_ವೃಕ್ಷ
	      || type == NULL_ವೃಕ್ಷ
	      || (ವೃಕ್ಷ_ಮೌಲ್ಯ (type) != error_mark_ಗಂಟು
		  && TYPE_MAIN_VARIANT (ವೃಕ್ಷ_ಮೌಲ್ಯ (type)) == void_type_ಗಂಟು))
	    {
	      ಯದಿ (current_function_prototype_built_in)
		warning_at (DECL_SOURCE_LOCATION (fndecl),
			    0, "number of arguments doesn%'t match "
			    "built-in prototype");
	      ಅನ್ಯಥಾ
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
	      ಭಙ್ಗ;
	    }
	  /* Type for passing arg must be consistent with that
	     declared for the arg.  ISO C says we take the unqualified
	     type for parameters declared with qualified type.  */
	  ಯದಿ (ವೃಕ್ಷ_TYPE (parm) != error_mark_ಗಂಟು
	      && ವೃಕ್ಷ_ಮೌಲ್ಯ (type) != error_mark_ಗಂಟು
	      && ((TYPE_ATOMIC (DECL_ARG_TYPE (parm))
		   != TYPE_ATOMIC (ವೃಕ್ಷ_ಮೌಲ್ಯ (type)))
		  || !comptypes (TYPE_MAIN_VARIANT (DECL_ARG_TYPE (parm)),
				 TYPE_MAIN_VARIANT (ವೃಕ್ಷ_ಮೌಲ್ಯ (type)))))
	    {
	      ಯದಿ ((TYPE_ATOMIC (DECL_ARG_TYPE (parm))
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
		  ಯದಿ (current_function_prototype_built_in)
		    warning_at (DECL_SOURCE_LOCATION (parm),
				OPT_Wpedantic, "promoted argument %qD "
				"doesn%'t match built-in prototype", parm);
		  ಅನ್ಯಥಾ
		    {
		      pedwarn (DECL_SOURCE_LOCATION (parm),
			       OPT_Wpedantic, "promoted argument %qD "
			       "doesn%'t match prototype", parm);
		      pedwarn (current_function_prototype_locus, OPT_Wpedantic,
			       "prototype declaration");
		    }
		}
	      ಅನ್ಯಥಾ
		{
		  ಯದಿ (current_function_prototype_built_in)
		    warning_at (DECL_SOURCE_LOCATION (parm),
				0, "argument %qD doesn%'t match "
				"built-in prototype", parm);
		  ಅನ್ಯಥಾ
		    {
		      error_at (DECL_SOURCE_LOCATION (parm),
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

  ಅನ್ಯಥಾ
    {
      ವೃಕ್ಷ actual = NULL_ವೃಕ್ಷ, last = NULL_ವೃಕ್ಷ, type;

      ಪ್ರತಿ (parm = DECL_ARGUMENTS (fndecl); parm; parm = DECL_CHAIN (parm))
	{
	  type = ವೃಕ್ಷ_cons (NULL_ವೃಕ್ಷ, DECL_ARG_TYPE (parm), NULL_ವೃಕ್ಷ);
	  ಯದಿ (last)
	    ವೃಕ್ಷ_CHAIN (last) = type;
	  ಅನ್ಯಥಾ
	    actual = type;
	  last = type;
	}
      type = ವೃಕ್ಷ_cons (NULL_ವೃಕ್ಷ, void_type_ಗಂಟು, NULL_ವೃಕ್ಷ);
      ಯದಿ (last)
	ವೃಕ್ಷ_CHAIN (last) = type;
      ಅನ್ಯಥಾ
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
store_parm_decls_from (ಸಂರಚನಾ c_arg_info *arg_info)
{
  current_function_arg_info = arg_info;
  store_parm_decls ();
}

/* Called by walk_tree to look for and update context-less labels
   or labels with context in the parent function.  */

ಸ್ಥಿರ ವೃಕ್ಷ
set_labels_context_r (ವೃಕ್ಷ *tp, ಪೂರ್ಣಾಙ್ಕ *walk_subtrees, ಶೂನ್ಯ *data)
{
  ವೃಕ್ಷ ctx = static_cast<ವೃಕ್ಷ>(data);
  ಯದಿ (ವೃಕ್ಷ_CODE (*tp) == LABEL_ಅಭಿವ್ಯಕ್ತಿ
      && (DECL_CONTEXT (LABEL_ಅಭಿವ್ಯಕ್ತಿ_LABEL (*tp)) == NULL_ವೃಕ್ಷ
	  || DECL_CONTEXT (LABEL_ಅಭಿವ್ಯಕ್ತಿ_LABEL (*tp)) == DECL_CONTEXT (ctx)))
    {
      DECL_CONTEXT (LABEL_ಅಭಿವ್ಯಕ್ತಿ_LABEL (*tp)) = ctx;
      *walk_subtrees = 0;
    }

  ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;
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
  ಸಂರಚನಾ c_arg_info *arg_info = current_function_arg_info;
  current_function_arg_info = 0;

  /* True if this definition is written with a prototype.  In C23, an
     empty argument list was converted to (void) in grokparms; in
     older C standard versions, it does not give the function a type
     with a prototype for future calls.  */
  proto = arg_info->types != 0 || arg_info->no_named_args_stdarg_p;

  ಯದಿ (proto)
    store_parm_decls_newstyle (fndecl, arg_info);
  ಅನ್ಯಥಾ
    store_parm_decls_oldstyle (fndecl, arg_info);

  /* The next call to push_scope will be a function body.  */

  next_is_function_body = ಸತ್ಯ;

  /* Write a record describing this function definition to the prototypes
     file (if requested).  */

  gen_aux_info_record (fndecl, 1, 0, proto);

  /* Initialize the RTL code for the function.  */
  allocate_struct_function (fndecl, ಅಸತ್ಯ);

  ಯದಿ (warn_unused_local_typedefs)
    cfun->language = ggc_cleared_alloc<language_function> ();

  /* Begin the statement tree for this function.  */
  DECL_SAVED_ವೃಕ್ಷ (fndecl) = ತಳ್ಳು_stmt_list ();

  /* ??? Insert the contents of the pending sizes list into the function
     to be evaluated.  The only reason left to have this is
	void foo(int n, int array[n++])
     because we throw away the array type in favor of a pointer type, and
     thus won't naturally see the SAVE_EXPR containing the increment.  All
     other pending sizes would be handled by gimplify_parameters.  */
  ಯದಿ (arg_info->pending_sizes)
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
				    set_labels_context_r, fndecl);
      add_stmt (arg_info->pending_sizes);
    }
}

/* Store PARM_DECLs in PARMS into scope temporarily.  Used for
   c_finish_omp_declare_simd for function prototypes.  No diagnostics
   should be done.  */

ಶೂನ್ಯ
temp_store_parm_decls (ವೃಕ್ಷ fndecl, ವೃಕ್ಷ parms)
{
  ತಳ್ಳು_scope ();
  ಪ್ರತಿ (ವೃಕ್ಷ p = parms; p; p = DECL_CHAIN (p))
    {
      DECL_CONTEXT (p) = fndecl;
      ಯದಿ (DECL_NAME (p))
	bind (DECL_NAME (p), p, current_scope,
	      /*invisible=*/ಅಸತ್ಯ, /*nested=*/ಅಸತ್ಯ,
	      UNKNOWN_LOCATION);
    }
}

/* Undo what temp_store_parm_decls did.  */

ಶೂನ್ಯ
temp_ತೆಗೆ_parm_decls (ಶೂನ್ಯ)
{
  /* Clear all bindings in this temporary scope, so that
     pop_scope doesn't create a BLOCK.  */
  ಸಂರಚನಾ c_binding *b = current_scope->bindings;
  current_scope->bindings = ರಿಕ್ತ;
  ಪ್ರತಿ (; b; b = free_binding_and_advance (b))
    {
      gcc_assert (ವೃಕ್ಷ_CODE (b->decl) == PARM_DECL
		  || b->decl == error_mark_ಗಂಟು);
      gcc_assert (I_ಚಿಹ್ನೆ_BINDING (b->id) == b);
      I_ಚಿಹ್ನೆ_BINDING (b->id) = b->shadowed;
      ಯದಿ (b->shadowed && b->shadowed->u.type)
	ವೃಕ್ಷ_TYPE (b->shadowed->decl) = b->shadowed->u.type;
    }
  ತೆಗೆ_scope ();
}


/* Finish up a function declaration and compile that function
   all the way to assembler language output.  Then free the storage
   for the function definition.

   This is called after parsing the body of the function definition.  */

ಶೂನ್ಯ
finish_function (location_t end_loc)
{
  ವೃಕ್ಷ fndecl = current_function_decl;

  ಯದಿ (c_dialect_objc ())
    objc_finish_function ();

  ಯದಿ (DECL_INITIAL (fndecl) && DECL_INITIAL (fndecl) != error_mark_ಗಂಟು)
    BLOCK_SUPERCONTEXT (DECL_INITIAL (fndecl)) = fndecl;

  /* Must mark the RESULT_DECL as being in this function.  */

  ಯದಿ (DECL_RESULT (fndecl) && DECL_RESULT (fndecl) != error_mark_ಗಂಟು)
    DECL_CONTEXT (DECL_RESULT (fndecl)) = fndecl;

  ಯದಿ (MAIN_NAME_P (DECL_NAME (fndecl)) && !ವೃಕ್ಷ_THIS_VOLATILE (fndecl)
      && TYPE_MAIN_VARIANT (ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_TYPE (fndecl)))
      == integer_type_ಗಂಟು && flag_isoc99)
    {
      /* Hack.  We don't want the middle-end to warn that this return
	 is unreachable, so we mark its location as special.  Using
	 UNKNOWN_LOCATION has the problem that it gets clobbered in
	 annotate_one_with_locus.  A cleaner solution might be to
	 ensure ! should_carry_locus_p (stmt), but that needs a flag.
      */
      c_finish_return (BUILTINS_LOCATION, integer_zero_ಗಂಟು, NULL_ವೃಕ್ಷ);
    }

  /* Tie off the statement tree for this function.  */
  DECL_SAVED_ವೃಕ್ಷ (fndecl) = ತೆಗೆ_stmt_list (DECL_SAVED_ವೃಕ್ಷ (fndecl));

  finish_fname_decls ();

  /* Complain if there's no return statement only if option specified on
     command line.  */
  ಯದಿ (warn_return_type > 0
      && ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_TYPE (fndecl))) != VOID_TYPE
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
      && !ವೃಕ್ಷ_PUBLIC (fndecl)
      && targetm.warn_func_return (fndecl)
      && warning (OPT_Wreturn_type,
		  "no return statement in function returning non-void"))
    suppress_warning (fndecl, OPT_Wreturn_type);

  /* Complain about parameters that are only set, but never otherwise used.  */
  ಯದಿ (warn_unused_but_set_parameter)
    {
      ವೃಕ್ಷ decl;

      ಪ್ರತಿ (decl = DECL_ARGUMENTS (fndecl);
	   decl;
	   decl = DECL_CHAIN (decl))
	ಯದಿ (ವೃಕ್ಷ_USED (decl)
	    && ವೃಕ್ಷ_CODE (decl) == PARM_DECL
	    && !DECL_READ_P (decl)
	    && DECL_NAME (decl)
	    && !DECL_ARTIFICIAL (decl)
	    && !warning_suppressed_p (decl, OPT_Wunused_but_set_parameter_))
	  warning_at (DECL_SOURCE_LOCATION (decl),
		      OPT_Wunused_but_set_parameter_,
		      "parameter %qD set but not used", decl);
    }

  /* Complain about locally defined typedefs that are not used in this
     function.  */
  maybe_warn_unused_local_typedefs ();

  /* Possibly warn about unused parameters.  */
  ಯದಿ (warn_unused_parameter)
    do_warn_unused_parameter (fndecl);

  /* Store the end of the function, so that we get good line number
     info for the epilogue.  */
  cfun->function_end_locus = end_loc;

  /* Finalize the ELF visibility for the function.  */
  c_determine_visibility (fndecl);

  /* For GNU C extern inline functions disregard inline limits.  */
  ಯದಿ (DECL_EXTERNAL (fndecl)
      && DECL_DECLARED_INLINE_P (fndecl)
      && (flag_gnu89_inline
	  || lookup_attribute ("gnu_inline", DECL_ATTRIBUTES (fndecl))))
    DECL_DISREGARD_INLINE_LIMITS (fndecl) = 1;

  /* Genericize before inlining.  Delay genericizing nested functions
     until their parent function is genericized.  Since finalizing
     requires GENERIC, delay that as well.  */

  ಯದಿ (DECL_INITIAL (fndecl) && DECL_INITIAL (fndecl) != error_mark_ಗಂಟು
      && !undef_nested_function)
    {
      ಯದಿ (!decl_function_context (fndecl))
	{
	  invoke_plugin_callbacks (PLUGIN_PRE_GENERICIZE, fndecl);
	  c_genericize (fndecl);

	  /* ??? Objc emits functions after finalizing the compilation unit.
	     This should be cleaned up later and this conditional removed.  */
	  ಯದಿ (symtab->global_info_ready)
	    {
	      cgraph_ಗಂಟು::add_new_function (fndecl, ಅಸತ್ಯ);
	      ಪ್ರತ್ಯಾಗಮ;
	    }
	  cgraph_ಗಂಟು::finalize_function (fndecl, ಅಸತ್ಯ);
	}
      ಅನ್ಯಥಾ
	{
	  /* Register this function with cgraph just far enough to get it
	    added to our parent's nested function list.  Handy, since the
	    C front end doesn't have such a list.  */
	  (ಶೂನ್ಯ) cgraph_ಗಂಟು::get_create (fndecl);
	}
    }

  ಯದಿ (!decl_function_context (fndecl))
    undef_nested_function = ಅಸತ್ಯ;

  ಯದಿ (cfun->language != ರಿಕ್ತ)
    {
      ggc_free (cfun->language);
      cfun->language = ರಿಕ್ತ;
    }

  /* We're leaving the context of this function, so zap cfun.
     It's still in DECL_STRUCT_FUNCTION, and we'll restore it in
     tree_rest_of_compilation.  */
  set_cfun (ರಿಕ್ತ);
  invoke_plugin_callbacks (PLUGIN_FINISH_PARSE_FUNCTION, current_function_decl);
  current_function_decl = ರಿಕ್ತ;
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
  ಸಂರಚನಾ c_binding *b;
  ವೃಕ್ಷ one_decl = NULL_ವೃಕ್ಷ;
  ಪೂರ್ಣಾಙ್ಕ n_decls = 0;

  ಯದಿ (!turn_off_iso_c99_error)
    {
      ಸ್ಥಿರ ತಾರ್ಕಿಕ hint = ಸತ್ಯ;
      /* If we get here, declarations have been used in a for loop without
	 the C99 for loop scope.  This doesn't make much sense, so don't
	 allow it.  */
      auto_diagnostic_group d;
      error_at (loc, "%<for%> loop initial declarations "
		"are only allowed in C99 or C11 mode");
      ಯದಿ (hint)
	{
	  inform (loc,
		  "use option %<-std=c99%>, %<-std=gnu99%>, %<-std=c11%> or "
		  "%<-std=gnu11%> to compile your code");
	  hint = ಅಸತ್ಯ;
	}
      ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;
    }
  ಅನ್ಯಥಾ
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

  ಪ್ರತಿ (b = current_scope->bindings; b; b = b->prev)
    {
      ವೃಕ್ಷ id = b->id;
      ವೃಕ್ಷ decl = b->decl;

      ಯದಿ (!id)
	ಅನುವರ್ತ;

      ವಿಕಲ್ಪ (ವೃಕ್ಷ_CODE (decl))
	{
	ಪಕ್ಷ VAR_DECL:
	  {
	    location_t decl_loc = DECL_SOURCE_LOCATION (decl);
	    ಯದಿ (ವೃಕ್ಷ_STATIC (decl))
	      pedwarn_c11 (decl_loc, OPT_Wpedantic,
			   "declaration of static variable %qD in %<for%> "
			   "loop initial declaration", decl);
	    ಅನ್ಯಥಾ ಯದಿ (DECL_EXTERNAL (decl))
	      pedwarn_c11 (decl_loc, OPT_Wpedantic,
			   "declaration of %<extern%> variable %qD in %<for%> "
			   "loop initial declaration", decl);
	  }
	  ಭಙ್ಗ;

	ಪಕ್ಷ RECORD_TYPE:
	  pedwarn_c11 (loc, OPT_Wpedantic,
		       "%<struct %E%> declared in %<for%> loop initial "
		       "declaration", id);
	  ಭಙ್ಗ;
	ಪಕ್ಷ UNION_TYPE:
	  pedwarn_c11 (loc, OPT_Wpedantic,
		       "%<union %E%> declared in %<for%> loop initial "
		       "declaration",
		       id);
	  ಭಙ್ಗ;
	ಪಕ್ಷ ENUMERAL_TYPE:
	  pedwarn_c11 (loc, OPT_Wpedantic,
		       "%<enum %E%> declared in %<for%> loop "
		       "initial declaration", id);
	  ಭಙ್ಗ;
	ಸ್ವಭಾವ:
	  pedwarn_c11 (loc, OPT_Wpedantic, "declaration of non-variable "
		       "%qD in %<for%> loop initial declaration", decl);
	}

      n_decls++;
      one_decl = decl;
    }

  ಪ್ರತ್ಯಾಗಮ n_decls == 1 ? one_decl : NULL_ವೃಕ್ಷ;
}

/* Save and reinitialize the variables
   used during compilation of a C function.  */

ಶೂನ್ಯ
c_ತಳ್ಳು_function_context (ಶೂನ್ಯ)
{
  ಸಂರಚನಾ language_function *p = cfun->language;
  /* cfun->language might have been already allocated by the use of
     -Wunused-local-typedefs.  In that case, just re-use it.  */
  ಯದಿ (p == ರಿಕ್ತ)
    cfun->language = p = ggc_cleared_alloc<language_function> ();

  p->base.x_stmt_ವೃಕ್ಷ = c_stmt_ವೃಕ್ಷ;
  c_stmt_ವೃಕ್ಷ.x_cur_stmt_list = vec_safe_copy (c_stmt_ವೃಕ್ಷ.x_cur_stmt_list);
  p->x_in_statement = in_statement;
  p->x_switch_ರಾಶಿ = c_switch_ರಾಶಿ;
  p->loop_names = loop_names;
  loop_names = vNULL;
  p->loop_names_hash = loop_names_hash;
  loop_names_hash = ರಿಕ್ತ;
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
  ಸಂರಚನಾ language_function *p;

  ತೆಗೆ_function_context ();
  p = cfun->language;

  /* When -Wunused-local-typedefs is in effect, cfun->languages is
     used to store data throughout the life time of the current cfun,
     So don't deallocate it.  */
  ಯದಿ (!warn_unused_local_typedefs)
    cfun->language = ರಿಕ್ತ;

  ಯದಿ (DECL_STRUCT_FUNCTION (current_function_decl) == 0
      && DECL_SAVED_ವೃಕ್ಷ (current_function_decl) == NULL_ವೃಕ್ಷ)
    {
      /* Stop pointing to the local nodes about to be freed.  */
      /* But DECL_INITIAL must remain nonzero so we know this
	 was an actual function definition.  */
      DECL_INITIAL (current_function_decl) = error_mark_ಗಂಟು;
      DECL_ARGUMENTS (current_function_decl) = NULL_ವೃಕ್ಷ;
    }

  c_stmt_ವೃಕ್ಷ = p->base.x_stmt_ವೃಕ್ಷ;
  p->base.x_stmt_ವೃಕ್ಷ.x_cur_stmt_list = ರಿಕ್ತ;
  in_statement = p->x_in_statement;
  c_switch_ರಾಶಿ = p->x_switch_ರಾಶಿ;
  loop_names.release ();
  loop_names = p->loop_names;
  p->loop_names = vNULL;
  delete loop_names_hash;
  loop_names_hash = p->loop_names_hash;
  p->loop_names_hash = ರಿಕ್ತ;
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
  ಪ್ರತ್ಯಾಗಮ &c_stmt_ವೃಕ್ಷ;
}

/* Return the global value of T as a symbol.  */

ವೃಕ್ಷ
identifier_global_ಮೌಲ್ಯ	(ವೃಕ್ಷ t)
{
  ಸಂರಚನಾ c_binding *b;

  ಪ್ರತಿ (b = I_ಚಿಹ್ನೆ_BINDING (t); b; b = b->shadowed)
    ಯದಿ (B_IN_FILE_SCOPE (b) || B_IN_EXTERNAL_SCOPE (b))
      ಪ್ರತ್ಯಾಗಮ b->decl;

  ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;
}

/* Return the global value of tag T as a symbol.  */

ವೃಕ್ಷ
identifier_global_tag (ವೃಕ್ಷ t)
{
  ಸಂರಚನಾ c_binding *b;

  ಪ್ರತಿ (b = I_TAG_BINDING (t); b; b = b->shadowed)
    ಯದಿ (B_IN_FILE_SCOPE (b) || B_IN_EXTERNAL_SCOPE (b))
      ಪ್ರತ್ಯಾಗಮ b->decl;

  ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;
}

/* Returns non-zero (result of __has_builtin) if NAME refers to a built-in
   function or function-like operator.  */

ಪೂರ್ಣಾಙ್ಕ
names_builtin_p (ಧ್ರುವ ವರ್ಣ *name)
{
  ವೃಕ್ಷ id = get_identifier (name);
  ಯದಿ (ವೃಕ್ಷ decl = identifier_global_ಮೌಲ್ಯ (id))
    ಪ್ರತ್ಯಾಗಮ ವೃಕ್ಷ_CODE (decl) == FUNCTION_DECL && DECL_IS_UNDECLARED_BUILTIN (decl);

  /* Also detect common reserved C words that aren't strictly built-in
     functions.  */
  ವಿಕಲ್ಪ (C_RID_CODE (id))
    {
    ಪಕ್ಷ RID_BUILTIN_ASSOC_BARRIER:
    ಪಕ್ಷ RID_BUILTIN_BITREVERSEG:
    ಪಕ್ಷ RID_BUILTIN_BSWAPG:
    ಪಕ್ಷ RID_BUILTIN_CONVERTVECTOR:
    ಪಕ್ಷ RID_BUILTIN_HAS_ATTRIBUTE:
    ಪಕ್ಷ RID_BUILTIN_SHUFFLE:
    ಪಕ್ಷ RID_BUILTIN_SHUFFLEVECTOR:
    ಪಕ್ಷ RID_BUILTIN_STDC:
    ಪಕ್ಷ RID_BUILTIN_COUNTED_BY_REF:
    ಪಕ್ಷ RID_CHOOSE_ಅಭಿವ್ಯಕ್ತಿ:
    ಪಕ್ಷ RID_OFFSETOF:
    ಪಕ್ಷ RID_TYPES_COMPATIBLE_P:
    ಪಕ್ಷ RID_C23_VA_START:
    ಪಕ್ಷ RID_VA_ARG:
      ಪ್ರತ್ಯಾಗಮ 1;
    ಸ್ವಭಾವ:
      ಭಙ್ಗ;
    }

  ಪ್ರತ್ಯಾಗಮ 0;
}

/* In C, the only C-linkage public declaration is at file scope.  */

ವೃಕ್ಷ
c_linkage_bindings (ವೃಕ್ಷ name)
{
  ಪ್ರತ್ಯಾಗಮ identifier_global_ಮೌಲ್ಯ (name);
}

/* Record a builtin type for C.  If NAME is non-NULL, it is the name used;
   otherwise the name is found in ridpointers from RID_INDEX.  */

ಶೂನ್ಯ
record_builtin_type (ಗಣನಾ rid rid_index, ಧ್ರುವ ವರ್ಣ *name, ವೃಕ್ಷ type)
{
  ವೃಕ್ಷ id, decl;
  ಯದಿ (name == 0)
    id = ridpointers[(ಪೂರ್ಣಾಙ್ಕ) rid_index];
  ಅನ್ಯಥಾ
    id = get_identifier (name);
  decl = build_decl (UNKNOWN_LOCATION, TYPE_DECL, id, type);
  pushdecl (decl);
  ಯದಿ (debug_hooks->type_decl)
    debug_hooks->type_decl (decl, ಅಸತ್ಯ);
}

/* Return a c_parm structure with the given SPECS, ATTRS and DECLARATOR.  */

ಸಂರಚನಾ c_parm *
build_c_parm (ಸಂರಚನಾ c_declspecs *specs, ವೃಕ್ಷ attrs,
	      ಸಂರಚನಾ c_declarator *declarator,
	      location_t loc)
{
  ಸಂರಚನಾ c_parm *ret = XOBNEW (&parser_obstack, ಸಂರಚನಾ c_parm);
  ret->specs = specs;
  ret->attrs = attrs;
  ret->declarator = declarator;
  ret->loc = loc;
  ಪ್ರತ್ಯಾಗಮ ret;
}

/* Return a declarator with nested attributes.  TARGET is the inner
   declarator to which these attributes apply.  ATTRS are the
   attributes.  */

ಸಂರಚನಾ c_declarator *
build_attrs_declarator (ವೃಕ್ಷ attrs, ಸಂರಚನಾ c_declarator *target)
{
  ಸಂರಚನಾ c_declarator *ret = XOBNEW (&parser_obstack, ಸಂರಚನಾ c_declarator);
  ret->kind = cdk_attrs;
  ret->declarator = target;
  ret->u.attrs = attrs;
  ಪ್ರತ್ಯಾಗಮ ret;
}

/* Return a declarator for a function with arguments specified by ARGS
   and return type specified by TARGET.  */

ಸಂರಚನಾ c_declarator *
build_function_declarator (ಸಂರಚನಾ c_arg_info *args,
			   ಸಂರಚನಾ c_declarator *target)
{
  ಸಂರಚನಾ c_declarator *ret = XOBNEW (&parser_obstack, ಸಂರಚನಾ c_declarator);
  ret->kind = cdk_function;
  ret->declarator = target;
  ret->u.arg_info = args;
  ಪ್ರತ್ಯಾಗಮ ret;
}

/* Return a declarator for the identifier IDENT (which may be
   NULL_TREE for an abstract declarator).  */

ಸಂರಚನಾ c_declarator *
build_id_declarator (ವೃಕ್ಷ ident)
{
  ಸಂರಚನಾ c_declarator *ret = XOBNEW (&parser_obstack, ಸಂರಚನಾ c_declarator);
  ret->kind = cdk_id;
  ret->declarator = 0;
  ret->u.id.id = ident;
  ret->u.id.attrs = NULL_ವೃಕ್ಷ;
  /* Default value - may get reset to a more precise location. */
  ret->id_loc = ಒಳಹರಿವು_location;
  ಪ್ರತ್ಯಾಗಮ ret;
}

/* Return something to represent absolute declarators containing a *.
   TARGET is the absolute declarator that the * contains.
   TYPE_QUALS_ATTRS is a structure for type qualifiers and attributes
   to apply to the pointer type.  */

ಸಂರಚನಾ c_declarator *
make_pointer_declarator (ಸಂರಚನಾ c_declspecs *type_quals_attrs,
			 ಸಂರಚನಾ c_declarator *target)
{
  ವೃಕ್ಷ attrs;
  ಪೂರ್ಣಾಙ್ಕ quals = 0;
  ಸಂರಚನಾ c_declarator *itarget = target;
  ಸಂರಚನಾ c_declarator *ret = XOBNEW (&parser_obstack, ಸಂರಚನಾ c_declarator);
  ಯದಿ (type_quals_attrs)
    {
      attrs = type_quals_attrs->attrs;
      quals = quals_from_declspecs (type_quals_attrs);
      ಯದಿ (attrs != NULL_ವೃಕ್ಷ)
	itarget = build_attrs_declarator (attrs, target);
    }
  ret->kind = cdk_pointer;
  ret->declarator = itarget;
  ret->u.pointer_quals = quals;
  ಪ್ರತ್ಯಾಗಮ ret;
}

/* Return a pointer to a structure for an empty list of declaration
   specifiers.  */

ಸಂರಚನಾ c_declspecs *
build_null_declspecs (ಶೂನ್ಯ)
{
  ಸಂರಚನಾ c_declspecs *ret = XOBNEW (&parser_obstack, ಸಂರಚನಾ c_declspecs);
  memset (ret, 0, ಪರಿಮಾಣ *ret);
  ret->align_log = -1;
  ret->typespec_word = cts_none;
  ret->storage_class = csc_none;
  ret->ಅಭಿವ್ಯಕ್ತಿ_const_operands = ಸತ್ಯ;
  ret->typespec_kind = ctsk_none;
  ret->address_space = ADDR_SPACE_GENERIC;
  ಪ್ರತ್ಯಾಗಮ ret;
}

/* Add the address space ADDRSPACE to the declaration specifiers
   SPECS, returning SPECS.  */

ಸಂರಚನಾ c_declspecs *
declspecs_add_addrspace (location_t location,
			 ಸಂರಚನಾ c_declspecs *specs, addr_space_t as)
{
  specs->non_sc_seen_p = ಸತ್ಯ;
  specs->declspecs_seen_p = ಸತ್ಯ;
  specs->non_std_attrs_seen_p = ಸತ್ಯ;

  ಯದಿ (!ADDR_SPACE_GENERIC_P (specs->address_space)
      && specs->address_space != as)
    error ("incompatible address space qualifiers %qs and %qs",
	   c_addr_space_name (as),
	   c_addr_space_name (specs->address_space));
  ಅನ್ಯಥಾ
    {
      specs->address_space = as;
      specs->locations[cdw_address_space] = location;
    }
  ಪ್ರತ್ಯಾಗಮ specs;
}

/* Add the type qualifier QUAL to the declaration specifiers SPECS,
   returning SPECS.  */

ಸಂರಚನಾ c_declspecs *
declspecs_add_qual (location_t loc,
		    ಸಂರಚನಾ c_declspecs *specs, ವೃಕ್ಷ qual)
{
  ಗಣನಾ rid i;
  ತಾರ್ಕಿಕ dupe = ಅಸತ್ಯ;
  specs->non_sc_seen_p = ಸತ್ಯ;
  specs->declspecs_seen_p = ಸತ್ಯ;
  specs->non_std_attrs_seen_p = ಸತ್ಯ;
  gcc_assert (ವೃಕ್ಷ_CODE (qual) == IDENTIFIER_ಗಂಟು
	      && C_IS_RESERVED_WORD (qual));
  i = C_RID_CODE (qual);
  location_t prev_loc = UNKNOWN_LOCATION;
  ವಿಕಲ್ಪ (i)
    {
    ಪಕ್ಷ RID_CONST:
      dupe = specs->const_p;
      specs->const_p = ಸತ್ಯ;
      prev_loc = specs->locations[cdw_const];
      specs->locations[cdw_const] = loc;
      ಭಙ್ಗ;
    ಪಕ್ಷ RID_VOLATILE:
      dupe = specs->volatile_p;
      specs->volatile_p = ಸತ್ಯ;
      prev_loc = specs->locations[cdw_volatile];
      specs->locations[cdw_volatile] = loc;
      ಭಙ್ಗ;
    ಪಕ್ಷ RID_RESTRICT:
      dupe = specs->restrict_p;
      specs->restrict_p = ಸತ್ಯ;
      prev_loc = specs->locations[cdw_restrict];
      specs->locations[cdw_restrict] = loc;
      ಭಙ್ಗ;
    ಪಕ್ಷ RID_ATOMIC:
      dupe = specs->atomic_p;
      specs->atomic_p = ಸತ್ಯ;
      prev_loc = specs->locations[cdw_atomic];
      specs->locations[cdw_atomic] = loc;
      ಭಙ್ಗ;
    ಸ್ವಭಾವ:
      gcc_unreachable ();
    }
  ಯದಿ (dupe)
    {
      ತಾರ್ಕಿಕ warned = pedwarn_c90 (loc, OPT_Wpedantic,
				 "duplicate %qE declaration specifier", qual);
      ಯದಿ (!warned
	  && warn_duplicate_decl_specifier
	  && prev_loc >= RESERVED_LOCATION_ಎಣಿಕೆ
	  && !from_macro_expansion_at (prev_loc)
	  && !from_macro_expansion_at (loc))
	warning_at (loc, OPT_Wduplicate_decl_specifier,
		    "duplicate %qE declaration specifier", qual);
    }
  ಪ್ರತ್ಯಾಗಮ specs;
}

/* Add the type specifier TYPE to the declaration specifiers SPECS,
   returning SPECS.  */

ಸಂರಚನಾ c_declspecs *
declspecs_add_type (location_t loc, ಸಂರಚನಾ c_declspecs *specs,
		    ಸಂರಚನಾ c_typespec spec)
{
  ವೃಕ್ಷ type = spec.spec;
  specs->non_sc_seen_p = ಸತ್ಯ;
  specs->declspecs_seen_p = ಸತ್ಯ;
  specs->non_std_attrs_seen_p = ಸತ್ಯ;
  specs->typespec_kind = spec.kind;
  ಯದಿ (ವೃಕ್ಷ_DEPRECATED (type))
    specs->deprecated_p = ಸತ್ಯ;
  ಯದಿ (ವೃಕ್ಷ_UNAVAILABLE (type))
    specs->unavailable_p = ಸತ್ಯ;

  /* As a type specifier is present, "auto" must be used as a storage
     class specifier, not for type deduction.  */
  ಯದಿ (specs->c23_auto_p)
    {
      specs->c23_auto_p = ಅಸತ್ಯ;
      ಯದಿ (specs->storage_class != csc_none)
	error ("multiple storage classes in declaration specifiers");
      ಅನ್ಯಥಾ ಯದಿ (specs->thread_p)
	error ("%qs used with %<auto%>",
	       specs->thread_gnu_p ? "__thread" : "_Thread_local");
      ಅನ್ಯಥಾ ಯದಿ (specs->constexpr_p)
	/* auto may only be used with another storage class specifier,
	   such as constexpr, if the type is inferred.  */
	error ("%<auto%> used with %<constexpr%>");
      ಅನ್ಯಥಾ
	specs->storage_class = csc_auto;
    }

  /* Handle type specifier keywords.  */
  ಯದಿ (ವೃಕ್ಷ_CODE (type) == IDENTIFIER_ಗಂಟು
      && C_IS_RESERVED_WORD (type)
      && C_RID_CODE (type) != RID_CXX_COMPAT_WARN)
    {
      ಗಣನಾ rid i = C_RID_CODE (type);
      ಯದಿ (specs->type)
	{
	  error_at (loc, "two or more data types in declaration specifiers");
	  ಪ್ರತ್ಯಾಗಮ specs;
	}
      ಯದಿ ((ಪೂರ್ಣಾಙ್ಕ) i <= (ಪೂರ್ಣಾಙ್ಕ) RID_LAST_MODIFIER)
	{
	  /* "long", "short", "signed", "unsigned", "_Complex" or "_Sat".  */
	  ತಾರ್ಕಿಕ dupe = ಅಸತ್ಯ;
	  ವಿಕಲ್ಪ (i)
	    {
	    ಪಕ್ಷ RID_LONG:
	      ಯದಿ (specs->long_long_p)
		{
		  error_at (loc, "%<long long long%> is too long for GCC");
		  ಭಙ್ಗ;
		}
	      ಯದಿ (specs->long_p)
		{
		  ಯದಿ (specs->typespec_word == cts_double)
		    {
		      error_at (loc,
				"both %qs and %qs in declaration specifiers",
				"long long", "double");
		      ಭಙ್ಗ;
		    }
		  pedwarn_c90 (loc, OPT_Wlong_long,
			       "ISO C90 does not support %<long long%>");
		  specs->long_long_p = 1;
		  specs->locations[cdw_long_long] = loc;
		  ಭಙ್ಗ;
		}
	      ಯದಿ (specs->short_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "short");
	      ಅನ್ಯಥಾ ಯದಿ (specs->typespec_word == cts_auto_type)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "__auto_type");
	      ಅನ್ಯಥಾ ಯದಿ (specs->typespec_word == cts_void)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "void");
	      ಅನ್ಯಥಾ ಯದಿ (specs->typespec_word == cts_int_n)
		error_at (loc,
			  "both %qs and %<__int%d%> in declaration specifiers",
			  "long", int_n_data[specs->u.int_n_idx].bitsize);
	      ಅನ್ಯಥಾ ಯದಿ (specs->typespec_word == cts_bool)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "_Bool");
	      ಅನ್ಯಥಾ ಯದಿ (specs->typespec_word == cts_bitint)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "_BitInt");
	      ಅನ್ಯಥಾ ಯದಿ (specs->typespec_word == cts_char)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "char");
	      ಅನ್ಯಥಾ ಯದಿ (specs->typespec_word == cts_float)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "float");
	      ಅನ್ಯಥಾ ಯದಿ (specs->typespec_word == cts_floatn_nx)
		error_at (loc,
			  "both %qs and %<_Float%d%s%> in declaration "
			  "specifiers", "long",
			  floatn_nx_types[specs->u.floatn_nx_idx].n,
			  floatn_nx_types[specs->u.floatn_nx_idx].extended
			  ? "x"
			  : "");
	      ಅನ್ಯಥಾ ಯದಿ (specs->typespec_word == cts_dfloat32)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "_Decimal32");
	      ಅನ್ಯಥಾ ಯದಿ (specs->typespec_word == cts_dfloat64)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "_Decimal64");
	      ಅನ್ಯಥಾ ಯದಿ (specs->typespec_word == cts_dfloat128)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "_Decimal128");
	      ಅನ್ಯಥಾ ಯದಿ (specs->typespec_word == cts_dfloat64x)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "_Decimal64x");
	      ಅನ್ಯಥಾ
		{
		  specs->long_p = ಸತ್ಯ;
		  specs->locations[cdw_long] = loc;
		}
	      ಭಙ್ಗ;
	    ಪಕ್ಷ RID_SHORT:
	      dupe = specs->short_p;
	      ಯದಿ (specs->long_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "short");
	      ಅನ್ಯಥಾ ಯದಿ (specs->typespec_word == cts_auto_type)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "__auto_type");
	      ಅನ್ಯಥಾ ಯದಿ (specs->typespec_word == cts_void)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "void");
	      ಅನ್ಯಥಾ ಯದಿ (specs->typespec_word == cts_int_n)
		error_at (loc,
			  "both %qs and %<__int%d%> in declaration specifiers",
			  "short", int_n_data[specs->u.int_n_idx].bitsize);
	      ಅನ್ಯಥಾ ಯದಿ (specs->typespec_word == cts_bool)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "_Bool");
	      ಅನ್ಯಥಾ ಯದಿ (specs->typespec_word == cts_bitint)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "_BitInt");
	      ಅನ್ಯಥಾ ಯದಿ (specs->typespec_word == cts_char)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "char");
	      ಅನ್ಯಥಾ ಯದಿ (specs->typespec_word == cts_float)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "float");
	      ಅನ್ಯಥಾ ಯದಿ (specs->typespec_word == cts_double)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "double");
	      ಅನ್ಯಥಾ ಯದಿ (specs->typespec_word == cts_floatn_nx)
		error_at (loc,
			  "both %qs and %<_Float%d%s%> in declaration "
			  "specifiers", "short",
			  floatn_nx_types[specs->u.floatn_nx_idx].n,
			  floatn_nx_types[specs->u.floatn_nx_idx].extended
			  ? "x"
			  : "");
	      ಅನ್ಯಥಾ ಯದಿ (specs->typespec_word == cts_dfloat32)
                error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "_Decimal32");
	      ಅನ್ಯಥಾ ಯದಿ (specs->typespec_word == cts_dfloat64)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "_Decimal64");
	      ಅನ್ಯಥಾ ಯದಿ (specs->typespec_word == cts_dfloat128)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "_Decimal128");
	      ಅನ್ಯಥಾ ಯದಿ (specs->typespec_word == cts_dfloat64x)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "_Decimal64x");
	      ಅನ್ಯಥಾ
		{
		  specs->short_p = ಸತ್ಯ;
		  specs->locations[cdw_short] = loc;
		}
	      ಭಙ್ಗ;
	    ಪಕ್ಷ RID_SIGNED:
	      dupe = specs->signed_p;
	      ಯದಿ (specs->unsigned_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "unsigned");
	      ಅನ್ಯಥಾ ಯದಿ (specs->typespec_word == cts_auto_type)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "__auto_type");
	      ಅನ್ಯಥಾ ಯದಿ (specs->typespec_word == cts_void)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "void");
	      ಅನ್ಯಥಾ ಯದಿ (specs->typespec_word == cts_bool)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "_Bool");
	      ಅನ್ಯಥಾ ಯದಿ (specs->typespec_word == cts_float)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "float");
	      ಅನ್ಯಥಾ ಯದಿ (specs->typespec_word == cts_double)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "double");
	      ಅನ್ಯಥಾ ಯದಿ (specs->typespec_word == cts_floatn_nx)
		error_at (loc,
			  "both %qs and %<_Float%d%s%> in declaration "
			  "specifiers", "signed",
			  floatn_nx_types[specs->u.floatn_nx_idx].n,
			  floatn_nx_types[specs->u.floatn_nx_idx].extended
			  ? "x"
			  : "");
	      ಅನ್ಯಥಾ ಯದಿ (specs->typespec_word == cts_dfloat32)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "_Decimal32");
	      ಅನ್ಯಥಾ ಯದಿ (specs->typespec_word == cts_dfloat64)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "_Decimal64");
	      ಅನ್ಯಥಾ ಯದಿ (specs->typespec_word == cts_dfloat128)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "_Decimal128");
	      ಅನ್ಯಥಾ ಯದಿ (specs->typespec_word == cts_dfloat64x)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "_Decimal64x");
	      ಅನ್ಯಥಾ
		{
		  specs->signed_p = ಸತ್ಯ;
		  specs->locations[cdw_signed] = loc;
		}
	      ಭಙ್ಗ;
	    ಪಕ್ಷ RID_UNSIGNED:
	      dupe = specs->unsigned_p;
	      ಯದಿ (specs->signed_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "unsigned");
	      ಅನ್ಯಥಾ ಯದಿ (specs->typespec_word == cts_auto_type)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "__auto_type");
	      ಅನ್ಯಥಾ ಯದಿ (specs->typespec_word == cts_void)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "void");
	      ಅನ್ಯಥಾ ಯದಿ (specs->typespec_word == cts_bool)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "_Bool");
	      ಅನ್ಯಥಾ ಯದಿ (specs->typespec_word == cts_float)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "float");
	      ಅನ್ಯಥಾ ಯದಿ (specs->typespec_word == cts_double)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "double");
	      ಅನ್ಯಥಾ ಯದಿ (specs->typespec_word == cts_floatn_nx)
		error_at (loc,
			  "both %qs and %<_Float%d%s%> in declaration "
			  "specifiers", "unsigned",
			  floatn_nx_types[specs->u.floatn_nx_idx].n,
			  floatn_nx_types[specs->u.floatn_nx_idx].extended
			  ? "x"
			  : "");
              ಅನ್ಯಥಾ ಯದಿ (specs->typespec_word == cts_dfloat32)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "_Decimal32");
	      ಅನ್ಯಥಾ ಯದಿ (specs->typespec_word == cts_dfloat64)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "_Decimal64");
	      ಅನ್ಯಥಾ ಯದಿ (specs->typespec_word == cts_dfloat128)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "_Decimal128");
	      ಅನ್ಯಥಾ ಯದಿ (specs->typespec_word == cts_dfloat64x)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "_Decimal64x");
	      ಅನ್ಯಥಾ
		{
		  specs->unsigned_p = ಸತ್ಯ;
		  specs->locations[cdw_unsigned] = loc;
		}
	      ಭಙ್ಗ;
	    ಪಕ್ಷ RID_COMPLEX:
	      dupe = specs->complex_p;
	      ಯದಿ (!in_system_header_at (loc))
		pedwarn_c90 (loc, OPT_Wpedantic,
			     "ISO C90 does not support complex types");
	      ಯದಿ (specs->typespec_word == cts_auto_type)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "__auto_type");
	      ಅನ್ಯಥಾ ಯದಿ (specs->typespec_word == cts_void)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "void");
	      ಅನ್ಯಥಾ ಯದಿ (specs->typespec_word == cts_bool)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "_Bool");
	      ಅನ್ಯಥಾ ಯದಿ (specs->typespec_word == cts_bitint)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "_BitInt");
              ಅನ್ಯಥಾ ಯದಿ (specs->typespec_word == cts_dfloat32)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "_Decimal32");
	      ಅನ್ಯಥಾ ಯದಿ (specs->typespec_word == cts_dfloat64)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "_Decimal64");
	      ಅನ್ಯಥಾ ಯದಿ (specs->typespec_word == cts_dfloat128)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "_Decimal128");
	      ಅನ್ಯಥಾ ಯದಿ (specs->typespec_word == cts_dfloat64x)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "_Decimal64x");
	      ಅನ್ಯಥಾ ಯದಿ (specs->typespec_word == cts_fract)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "_Fract");
	      ಅನ್ಯಥಾ ಯದಿ (specs->typespec_word == cts_accum)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "_Accum");
	      ಅನ್ಯಥಾ ಯದಿ (specs->saturating_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "_Sat");
	      ಅನ್ಯಥಾ
		{
		  specs->complex_p = ಸತ್ಯ;
		  specs->locations[cdw_complex] = loc;
		}
	      ಭಙ್ಗ;
	    ಪಕ್ಷ RID_SAT:
	      dupe = specs->saturating_p;
	      pedwarn (loc, OPT_Wpedantic,
		       "ISO C does not support saturating types");
	      ಯದಿ (specs->typespec_word == cts_int_n)
		error_at (loc,
			  "both %qs and %<__int%d%> in declaration specifiers",
			  "_Sat", int_n_data[specs->u.int_n_idx].bitsize);
	      ಅನ್ಯಥಾ ಯದಿ (specs->typespec_word == cts_auto_type)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "__auto_type");
	      ಅನ್ಯಥಾ ಯದಿ (specs->typespec_word == cts_void)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "void");
	      ಅನ್ಯಥಾ ಯದಿ (specs->typespec_word == cts_bool)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "_Bool");
	      ಅನ್ಯಥಾ ಯದಿ (specs->typespec_word == cts_bitint)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "_BitInt");
	      ಅನ್ಯಥಾ ಯದಿ (specs->typespec_word == cts_char)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "char");
	      ಅನ್ಯಥಾ ಯದಿ (specs->typespec_word == cts_int)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "int");
	      ಅನ್ಯಥಾ ಯದಿ (specs->typespec_word == cts_float)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "float");
	      ಅನ್ಯಥಾ ಯದಿ (specs->typespec_word == cts_double)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "double");
	      ಅನ್ಯಥಾ ಯದಿ (specs->typespec_word == cts_floatn_nx)
		error_at (loc,
			  "both %qs and %<_Float%d%s%> in declaration "
			  "specifiers", "_Sat",
			  floatn_nx_types[specs->u.floatn_nx_idx].n,
			  floatn_nx_types[specs->u.floatn_nx_idx].extended
			  ? "x"
			  : "");
              ಅನ್ಯಥಾ ಯದಿ (specs->typespec_word == cts_dfloat32)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "_Decimal32");
	      ಅನ್ಯಥಾ ಯದಿ (specs->typespec_word == cts_dfloat64)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "_Decimal64");
	      ಅನ್ಯಥಾ ಯದಿ (specs->typespec_word == cts_dfloat128)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "_Decimal128");
	      ಅನ್ಯಥಾ ಯದಿ (specs->typespec_word == cts_dfloat64x)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "_Decimal64x");
	      ಅನ್ಯಥಾ ಯದಿ (specs->complex_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "complex");
	      ಅನ್ಯಥಾ
		{
		  specs->saturating_p = ಸತ್ಯ;
		  specs->locations[cdw_saturating] = loc;
		}
	      ಭಙ್ಗ;
	    ಸ್ವಭಾವ:
	      gcc_unreachable ();
	    }

	  ಯದಿ (dupe)
	    error_at (loc, "duplicate %qE", type);

	  ಪ್ರತ್ಯಾಗಮ specs;
	}
      ಅನ್ಯಥಾ
	{
	  /* "void", "_Bool", "char", "int", "float", "double",
	     "_FloatN", "_FloatNx", "_Decimal32", "__intN",
	     "_Decimal64", "_Decimal128", "_Fract", "_Accum", "_BitInt(N)" or
	     "__auto_type".  */
	  ಯದಿ (specs->typespec_word != cts_none)
	    {
	      ಯದಿ (i == RID_BOOL)
		{
		  auto_diagnostic_group d;
		  ಯದಿ (specs->storage_class == csc_typedef)
		    error_at (loc,
			      "%qs cannot be defined via %<typedef%>",
			      IDENTIFIER_POINTER (type));
		  ಅನ್ಯಥಾ
		    error_at (loc,
			      "%qs cannot be used here",
			      IDENTIFIER_POINTER (type));
		  add_note_about_new_keyword (loc, type);
		}
	      ಅನ್ಯಥಾ
		error_at (loc,
			  "two or more data types in declaration specifiers");
	      ಪ್ರತ್ಯಾಗಮ specs;
	    }
	  ವಿಕಲ್ಪ (i)
	    {
	    ಪಕ್ಷ RID_AUTO_TYPE:
	      ಯದಿ (specs->long_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "__auto_type");
	      ಅನ್ಯಥಾ ಯದಿ (specs->short_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "__auto_type");
	      ಅನ್ಯಥಾ ಯದಿ (specs->signed_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "__auto_type");
	      ಅನ್ಯಥಾ ಯದಿ (specs->unsigned_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "__auto_type");
	      ಅನ್ಯಥಾ ಯದಿ (specs->complex_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "__auto_type");
	      ಅನ್ಯಥಾ ಯದಿ (specs->saturating_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "__auto_type");
	      ಅನ್ಯಥಾ
		{
		  specs->typespec_word = cts_auto_type;
		  specs->locations[cdw_typespec] = loc;
		}
	      ಪ್ರತ್ಯಾಗಮ specs;
	    ಪಕ್ಷ RID_INT_N_0:
	    ಪಕ್ಷ RID_INT_N_1:
	    ಪಕ್ಷ RID_INT_N_2:
	    ಪಕ್ಷ RID_INT_N_3:
	      specs->u.int_n_idx = i - RID_INT_N_0;
	      ಯದಿ (!in_system_header_at (ಒಳಹರಿವು_location)
		  /* If the INT_N type ends in "__", and so is of the format
		     "__intN__", don't pedwarn.  */
		  && (strncmp (IDENTIFIER_POINTER (type)
			       + (IDENTIFIER_LENGTH (type) - 2), "__", 2) != 0))
		pedwarn (loc, OPT_Wpedantic,
			 "ISO C does not support %<__int%d%> types",
			 int_n_data[specs->u.int_n_idx].bitsize);

	      ಯದಿ (specs->long_p)
		error_at (loc,
			  "both %<__int%d%> and %qs in declaration specifiers",
			  int_n_data[specs->u.int_n_idx].bitsize, "long");
	      ಅನ್ಯಥಾ ಯದಿ (specs->saturating_p)
		error_at (loc,
			  "both %qs and %<__int%d%> in declaration specifiers",
			  "_Sat", int_n_data[specs->u.int_n_idx].bitsize);
	      ಅನ್ಯಥಾ ಯದಿ (specs->short_p)
		error_at (loc,
			  "both %<__int%d%> and %qs in declaration specifiers",
			  int_n_data[specs->u.int_n_idx].bitsize, "short");
	      ಅನ್ಯಥಾ ಯದಿ (! int_n_enabled_p[specs->u.int_n_idx])
		{
		  specs->typespec_word = cts_int_n;
		  error_at (loc,
			    "%<__int%d%> is not supported on this target",
			    int_n_data[specs->u.int_n_idx].bitsize);
		}
	      ಅನ್ಯಥಾ
		{
		  specs->typespec_word = cts_int_n;
		  specs->locations[cdw_typespec] = loc;
		}
	      ಪ್ರತ್ಯಾಗಮ specs;
	    ಪಕ್ಷ RID_VOID:
	      ಯದಿ (specs->long_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "void");
	      ಅನ್ಯಥಾ ಯದಿ (specs->short_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "void");
	      ಅನ್ಯಥಾ ಯದಿ (specs->signed_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "void");
	      ಅನ್ಯಥಾ ಯದಿ (specs->unsigned_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "void");
	      ಅನ್ಯಥಾ ಯದಿ (specs->complex_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "void");
	      ಅನ್ಯಥಾ ಯದಿ (specs->saturating_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "void");
	      ಅನ್ಯಥಾ
		{
		  specs->typespec_word = cts_void;
		  specs->locations[cdw_typespec] = loc;
		}
	      ಪ್ರತ್ಯಾಗಮ specs;
	    ಪಕ್ಷ RID_BOOL:
	      ಯದಿ (!in_system_header_at (loc))
		pedwarn_c90 (loc, OPT_Wpedantic,
			     "ISO C90 does not support boolean types");
	      ಯದಿ (specs->long_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "_Bool");
	      ಅನ್ಯಥಾ ಯದಿ (specs->short_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "_Bool");
	      ಅನ್ಯಥಾ ಯದಿ (specs->signed_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "_Bool");
	      ಅನ್ಯಥಾ ಯದಿ (specs->unsigned_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "_Bool");
	      ಅನ್ಯಥಾ ಯದಿ (specs->complex_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "_Bool");
	      ಅನ್ಯಥಾ ಯದಿ (specs->saturating_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "_Bool");
	      ಅನ್ಯಥಾ
		{
		  specs->typespec_word = cts_bool;
		  specs->locations[cdw_typespec] = loc;
		}
	      ಪ್ರತ್ಯಾಗಮ specs;
	    ಪಕ್ಷ RID_CHAR:
	      ಯದಿ (specs->long_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "char");
	      ಅನ್ಯಥಾ ಯದಿ (specs->short_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "char");
	      ಅನ್ಯಥಾ ಯದಿ (specs->saturating_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "char");
	      ಅನ್ಯಥಾ
		{
		  specs->typespec_word = cts_char;
		  specs->locations[cdw_typespec] = loc;
		}
	      ಪ್ರತ್ಯಾಗಮ specs;
	    ಪಕ್ಷ RID_INT:
	      ಯದಿ (specs->saturating_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "int");
	      ಅನ್ಯಥಾ
		{
		  specs->typespec_word = cts_int;
		  specs->locations[cdw_typespec] = loc;
		}
	      ಪ್ರತ್ಯಾಗಮ specs;
	    ಪಕ್ಷ RID_FLOAT:
	      ಯದಿ (specs->long_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "float");
	      ಅನ್ಯಥಾ ಯದಿ (specs->short_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "float");
	      ಅನ್ಯಥಾ ಯದಿ (specs->signed_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "float");
	      ಅನ್ಯಥಾ ಯದಿ (specs->unsigned_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "float");
	      ಅನ್ಯಥಾ ಯದಿ (specs->saturating_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "float");
	      ಅನ್ಯಥಾ
		{
		  specs->typespec_word = cts_float;
		  specs->locations[cdw_typespec] = loc;
		}
	      ಪ್ರತ್ಯಾಗಮ specs;
	    ಪಕ್ಷ RID_DOUBLE:
	      ಯದಿ (specs->long_long_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long long", "double");
	      ಅನ್ಯಥಾ ಯದಿ (specs->short_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "double");
	      ಅನ್ಯಥಾ ಯದಿ (specs->signed_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "double");
	      ಅನ್ಯಥಾ ಯದಿ (specs->unsigned_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "double");
	      ಅನ್ಯಥಾ ಯದಿ (specs->saturating_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "double");
	      ಅನ್ಯಥಾ
		{
		  specs->typespec_word = cts_double;
		  specs->locations[cdw_typespec] = loc;
		}
	      ಪ್ರತ್ಯಾಗಮ specs;
	    CASE_RID_FLOATN_NX:
	      specs->u.floatn_nx_idx = i - RID_FLOATN_NX_FIRST;
	      ಯದಿ (!in_system_header_at (ಒಳಹರಿವು_location))
		pedwarn_c11 (loc, OPT_Wpedantic,
			     "ISO C does not support the %<_Float%d%s%> type"
			     " before C23",
			     floatn_nx_types[specs->u.floatn_nx_idx].n,
			     floatn_nx_types[specs->u.floatn_nx_idx].extended
			     ? "x"
			     : "");

	      ಯದಿ (specs->long_p)
		error_at (loc,
			  "both %qs and %<_Float%d%s%> in declaration "
			  "specifiers", "long",
			  floatn_nx_types[specs->u.floatn_nx_idx].n,
			  floatn_nx_types[specs->u.floatn_nx_idx].extended
			  ? "x"
			  : "");
	      ಅನ್ಯಥಾ ಯದಿ (specs->short_p)
		error_at (loc,
			  "both %qs and %<_Float%d%s%> in declaration "
			  "specifiers", "short",
			  floatn_nx_types[specs->u.floatn_nx_idx].n,
			  floatn_nx_types[specs->u.floatn_nx_idx].extended
			  ? "x"
			  : "");
	      ಅನ್ಯಥಾ ಯದಿ (specs->signed_p)
		error_at (loc,
			  "both %qs and %<_Float%d%s%> in declaration "
			  "specifiers", "signed",
			  floatn_nx_types[specs->u.floatn_nx_idx].n,
			  floatn_nx_types[specs->u.floatn_nx_idx].extended
			  ? "x"
			  : "");
	      ಅನ್ಯಥಾ ಯದಿ (specs->unsigned_p)
		error_at (loc,
			  "both %qs and %<_Float%d%s%> in declaration "
			  "specifiers", "unsigned",
			  floatn_nx_types[specs->u.floatn_nx_idx].n,
			  floatn_nx_types[specs->u.floatn_nx_idx].extended
			  ? "x"
			  : "");
	      ಅನ್ಯಥಾ ಯದಿ (specs->saturating_p)
		error_at (loc,
			  "both %qs and %<_Float%d%s%> in declaration "
			  "specifiers", "_Sat",
			  floatn_nx_types[specs->u.floatn_nx_idx].n,
			  floatn_nx_types[specs->u.floatn_nx_idx].extended
			  ? "x"
			  : "");
	      ಅನ್ಯಥಾ ಯದಿ (FLOATN_NX_TYPE_ಗಂಟು (specs->u.floatn_nx_idx) == NULL_ವೃಕ್ಷ)
		{
		  specs->typespec_word = cts_floatn_nx;
		  error_at (loc,
			    "%<_Float%d%s%> is not supported on this target",
			    floatn_nx_types[specs->u.floatn_nx_idx].n,
			    floatn_nx_types[specs->u.floatn_nx_idx].extended
			    ? "x"
			    : "");
		}
	      ಅನ್ಯಥಾ
		{
		  specs->typespec_word = cts_floatn_nx;
		  specs->locations[cdw_typespec] = loc;
		}
	      ಪ್ರತ್ಯಾಗಮ specs;
	    ಪಕ್ಷ RID_DFLOAT32:
	    ಪಕ್ಷ RID_DFLOAT64:
	    ಪಕ್ಷ RID_DFLOAT128:
	    ಪಕ್ಷ RID_DFLOAT64X:
	      {
		ಧ್ರುವ ವರ್ಣ *str;
		ಯದಿ (i == RID_DFLOAT32)
		  str = "_Decimal32";
		ಅನ್ಯಥಾ ಯದಿ (i == RID_DFLOAT64)
		  str = "_Decimal64";
		ಅನ್ಯಥಾ ಯದಿ (i == RID_DFLOAT128)
		  str = "_Decimal128";
		ಅನ್ಯಥಾ
		  str = "_Decimal64x";
		ಯದಿ (specs->long_long_p)
		  error_at (loc,
			    "both %qs and %qs in declaration specifiers",
			    "long long", str);
		ಯದಿ (specs->long_p)
		  error_at (loc,
			    "both %qs and %qs in declaration specifiers",
			    "long", str);
		ಅನ್ಯಥಾ ಯದಿ (specs->short_p)
		  error_at (loc,
			    "both %qs and %qs in declaration specifiers",
			    "short", str);
		ಅನ್ಯಥಾ ಯದಿ (specs->signed_p)
		  error_at (loc,
			    "both %qs and %qs in declaration specifiers",
			    "signed", str);
		ಅನ್ಯಥಾ ಯದಿ (specs->unsigned_p)
		  error_at (loc,
			    "both %qs and %qs in declaration specifiers",
			    "unsigned", str);
                ಅನ್ಯಥಾ ಯದಿ (specs->complex_p)
                  error_at (loc,
			    "both %qs and %qs in declaration specifiers",
			    "complex", str);
                ಅನ್ಯಥಾ ಯದಿ (specs->saturating_p)
                  error_at (loc,
			    "both %qs and %qs in declaration specifiers",
			    "_Sat", str);
		ಅನ್ಯಥಾ ಯದಿ (i == RID_DFLOAT32)
		  specs->typespec_word = cts_dfloat32;
		ಅನ್ಯಥಾ ಯದಿ (i == RID_DFLOAT64)
		  specs->typespec_word = cts_dfloat64;
		ಅನ್ಯಥಾ ಯದಿ (i == RID_DFLOAT128)
		  specs->typespec_word = cts_dfloat128;
		ಅನ್ಯಥಾ
		  specs->typespec_word = cts_dfloat64x;
		specs->locations[cdw_typespec] = loc;
	      }
	      ಯದಿ (!targetm.decimal_float_supported_p ())
		error_at (loc,
			  "decimal floating-point not supported "
			  "for this target");
	      pedwarn_c11 (loc, OPT_Wpedantic,
			   "ISO C does not support decimal floating-point "
			   "before C23");
	      ಪ್ರತ್ಯಾಗಮ specs;
	    ಪಕ್ಷ RID_FRACT:
	    ಪಕ್ಷ RID_ACCUM:
	      {
		ಧ್ರುವ ವರ್ಣ *str;
		ಯದಿ (i == RID_FRACT)
		  str = "_Fract";
		ಅನ್ಯಥಾ
		  str = "_Accum";
                ಯದಿ (specs->complex_p)
                  error_at (loc,
			    "both %qs and %qs in declaration specifiers",
			    "complex", str);
		ಅನ್ಯಥಾ ಯದಿ (i == RID_FRACT)
		    specs->typespec_word = cts_fract;
		ಅನ್ಯಥಾ
		    specs->typespec_word = cts_accum;
		specs->locations[cdw_typespec] = loc;
	      }
	      ಯದಿ (!targetm.fixed_point_supported_p ())
		error_at (loc,
			  "fixed-point types not supported for this target");
	      pedwarn (loc, OPT_Wpedantic,
		       "ISO C does not support fixed-point types");
	      ಪ್ರತ್ಯಾಗಮ specs;
	    ಪಕ್ಷ RID_BITINT:
	      ಯದಿ (specs->long_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "_BitInt");
	      ಅನ್ಯಥಾ ಯದಿ (specs->short_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "_BitInt");
	      ಅನ್ಯಥಾ ಯದಿ (specs->complex_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "_BitInt");
	      ಅನ್ಯಥಾ ಯದಿ (specs->saturating_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "_BitInt");
	      ಅನ್ಯಥಾ
		{
		  specs->typespec_word = cts_bitint;
		  specs->locations[cdw_typespec] = loc;
		  specs->u.bitint_prec = -1;
		  ಯದಿ (error_operand_p (spec.ಅಭಿವ್ಯಕ್ತಿ))
		    ಪ್ರತ್ಯಾಗಮ specs;
		  ಯದಿ (ವೃಕ್ಷ_CODE (spec.ಅಭಿವ್ಯಕ್ತಿ) != INTEGER_CST
		      || !INTEGRAL_TYPE_P (ವೃಕ್ಷ_TYPE (spec.ಅಭಿವ್ಯಕ್ತಿ)))
		    {
		      error_at (loc, "%<_BitInt%> argument is not an integer "
				     "constant expression");
		      ಪ್ರತ್ಯಾಗಮ specs;
		    }
		  ಯದಿ (ವೃಕ್ಷ_int_cst_sgn (spec.ಅಭಿವ್ಯಕ್ತಿ) <= 0)
		    {
		      error_at (loc, "%<_BitInt%> argument %qE is not a "
				     "positive integer constant expression",
				spec.ಅಭಿವ್ಯಕ್ತಿ);
		      ಪ್ರತ್ಯಾಗಮ specs;
		    }
		  ಯದಿ (wi::to_widest (spec.ಅಭಿವ್ಯಕ್ತಿ) > WIDE_INT_MAX_PRECISION - 1)
		    {
		      error_at (loc, "%<_BitInt%> argument %qE is larger than "
				     "%<BITINT_MAXWIDTH%> %qd",
				spec.ಅಭಿವ್ಯಕ್ತಿ, (ಪೂರ್ಣಾಙ್ಕ) WIDE_INT_MAX_PRECISION - 1);
		      ಪ್ರತ್ಯಾಗಮ specs;
		    }
		  specs->u.bitint_prec = ವೃಕ್ಷ_to_uhwi (spec.ಅಭಿವ್ಯಕ್ತಿ);
		  ಸಂರಚನಾ bitint_info info;
		  ಯದಿ (!targetm.c.bitint_type_info (specs->u.bitint_prec,
						   &info))
		    {
		      sorry_at (loc, "%<_BitInt(%d)%> is not supported on "
				     "this target", specs->u.bitint_prec);
		      specs->u.bitint_prec = -1;
		      ಪ್ರತ್ಯಾಗಮ specs;
		    }
		}
	      ಪ್ರತ್ಯಾಗಮ specs;
	    ಸ್ವಭಾವ:
	      /* ObjC reserved word "id", handled below.  */
	      ಭಙ್ಗ;
	    }
	}
    }

  /* Now we have a typedef (a TYPE_DECL node), an identifier (some
     form of ObjC type, cases such as "int" and "long" being handled
     above), a TYPE (struct, union, enum and typeof specifiers) or an
     ERROR_MARK.  In none of these cases may there have previously
     been any type specifiers.  */
  ಯದಿ (specs->type || specs->typespec_word != cts_none
      || specs->long_p || specs->short_p || specs->signed_p
      || specs->unsigned_p || specs->complex_p)
    error_at (loc, "two or more data types in declaration specifiers");
  ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_CODE (type) == TYPE_DECL)
    {
      specs->type = ವೃಕ್ಷ_TYPE (type);
      ಯದಿ (ವೃಕ್ಷ_TYPE (type) != error_mark_ಗಂಟು)
	{
	  mark_decl_used (type, ಅಸತ್ಯ);
	  specs->decl_attr = DECL_ATTRIBUTES (type);
	  specs->typedef_p = ಸತ್ಯ;
	  specs->explicit_signed_p = C_TYPEDEF_EXPLICITLY_SIGNED (type);
	  specs->locations[cdw_typedef] = loc;

	  /* If this typedef name is defined in a struct, then a C++
	     lookup would return a different value.  */
	  ಯದಿ (warn_cxx_compat
	      && I_ಚಿಹ್ನೆ_BINDING (DECL_NAME (type))->in_struct)
	    warning_at (loc, OPT_Wc___compat,
			"C++ lookup of %qD would return a field, not a type",
			type);

	  /* If we are parsing a struct, record that a struct field
	     used a typedef.  */
	  ಯದಿ (warn_cxx_compat && struct_parse_info != ರಿಕ್ತ)
	    struct_parse_info->typedefs_seen.safe_ತಳ್ಳು (type);
	}
    }
  ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_CODE (type) == IDENTIFIER_ಗಂಟು)
    {
      ವೃಕ್ಷ t = lookup_name (type);
      ಯದಿ (!t || ವೃಕ್ಷ_CODE (t) != TYPE_DECL)
	error_at (loc, "%qE fails to be a typedef or built in type", type);
      ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_TYPE (t) == error_mark_ಗಂಟು)
	;
      ಅನ್ಯಥಾ
	{
	  specs->type = ವೃಕ್ಷ_TYPE (t);
	  specs->locations[cdw_typespec] = loc;
	}
    }
  ಅನ್ಯಥಾ
    {
      ಯದಿ (ವೃಕ್ಷ_CODE (type) != ERROR_MARK)
	{
	  ಯದಿ (spec.kind == ctsk_typeof)
	    {
	      specs->typedef_p = ಸತ್ಯ;
	      specs->locations[cdw_typedef] = loc;
	    }

	  ಯದಿ (ವೃಕ್ಷ_CODE (type) == RECORD_TYPE || ವೃಕ್ಷ_CODE (type) == UNION_TYPE
	      || ವೃಕ್ಷ_CODE (type) == ENUMERAL_TYPE)
	    mark_decl_used (TYPE_STUB_DECL (type), ಅಸತ್ಯ);

	  ಯದಿ (spec.ಅಭಿವ್ಯಕ್ತಿ)
	    {
	      ವೃಕ್ಷ ಅಭಿವ್ಯಕ್ತಿ = save_ಅಭಿವ್ಯಕ್ತಿ (fold_convert (void_type_ಗಂಟು, spec.ಅಭಿವ್ಯಕ್ತಿ));
	      ಯದಿ (specs->ಅಭಿವ್ಯಕ್ತಿ)
		specs->ಅಭಿವ್ಯಕ್ತಿ = build2 (COMPOUND_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ),
				      specs->ಅಭಿವ್ಯಕ್ತಿ, ಅಭಿವ್ಯಕ್ತಿ);
	      ಅನ್ಯಥಾ
		specs->ಅಭಿವ್ಯಕ್ತಿ = ಅಭಿವ್ಯಕ್ತಿ;
	      specs->ಅಭಿವ್ಯಕ್ತಿ_const_operands &= spec.ಅಭಿವ್ಯಕ್ತಿ_const_operands;
	    }
	}
      specs->type = type;
      ಯದಿ (spec.has_enum_type_specifier
	  && spec.kind != ctsk_tagdef)
	specs->enum_type_specifier_ref_p = ಸತ್ಯ;
    }

  ಪ್ರತ್ಯಾಗಮ specs;
}

/* Add the storage class specifier or function specifier SCSPEC to the
   declaration specifiers SPECS, returning SPECS.  */

ಸಂರಚನಾ c_declspecs *
declspecs_add_scspec (location_t loc,
		      ಸಂರಚನಾ c_declspecs *specs,
		      ವೃಕ್ಷ scspec)
{
  ಗಣನಾ rid i;
  ಗಣನಾ c_storage_class n = csc_none;
  ತಾರ್ಕಿಕ dupe = ಅಸತ್ಯ;
  specs->declspecs_seen_p = ಸತ್ಯ;
  specs->non_std_attrs_seen_p = ಸತ್ಯ;
  gcc_assert (ವೃಕ್ಷ_CODE (scspec) == IDENTIFIER_ಗಂಟು
	      && C_IS_RESERVED_WORD (scspec));
  i = C_RID_CODE (scspec);
  ಯದಿ (specs->non_sc_seen_p)
    warning (OPT_Wold_style_declaration,
             "%qE is not at beginning of declaration", scspec);
  ವಿಕಲ್ಪ (i)
    {
    ಪಕ್ಷ RID_INLINE:
      /* C99 permits duplicate inline.  Although of doubtful utility,
	 it seems simplest to permit it in gnu89 mode as well, as
	 there is also little utility in maintaining this as a
	 difference between gnu89 and C99 inline.  */
      dupe = ಅಸತ್ಯ;
      specs->inline_p = ಸತ್ಯ;
      specs->locations[cdw_inline] = loc;
      ಭಙ್ಗ;
    ಪಕ್ಷ RID_NORETURN:
      /* Duplicate _Noreturn is permitted.  */
      dupe = ಅಸತ್ಯ;
      specs->noreturn_p = ಸತ್ಯ;
      specs->locations[cdw_noreturn] = loc;
      ಭಙ್ಗ;
    ಪಕ್ಷ RID_THREAD:
      dupe = specs->thread_p;
      ಯದಿ (specs->storage_class == csc_auto)
	error ("%qE used with %<auto%>", scspec);
      ಅನ್ಯಥಾ ಯದಿ (specs->storage_class == csc_register)
	error ("%qE used with %<register%>", scspec);
      ಅನ್ಯಥಾ ಯದಿ (specs->storage_class == csc_typedef)
	error ("%qE used with %<typedef%>", scspec);
      ಅನ್ಯಥಾ ಯದಿ (specs->constexpr_p)
	error ("%qE used with %<constexpr%>", scspec);
      ಅನ್ಯಥಾ
	{
	  specs->thread_p = ಸತ್ಯ;
	  specs->thread_gnu_p = (strcmp (IDENTIFIER_POINTER (scspec),
					 "__thread") == 0);
	  /* A diagnostic is not required for the use of this
	     identifier in the implementation namespace; only diagnose
	     it for the C11 spelling because of existing code using
	     the other spelling.  */
	  ಯದಿ (!specs->thread_gnu_p)
	    {
	      ಯದಿ (flag_isoc99)
		pedwarn_c99 (loc, OPT_Wpedantic,
			     "ISO C99 does not support %qE", scspec);
	      ಅನ್ಯಥಾ
		pedwarn_c99 (loc, OPT_Wpedantic,
			     "ISO C90 does not support %qE", scspec);
	    }
	  specs->locations[cdw_thread] = loc;
	}
      ಭಙ್ಗ;
    ಪಕ್ಷ RID_AUTO:
      ಯದಿ (flag_isoc23
	  && specs->typespec_kind == ctsk_none
	  && specs->storage_class != csc_typedef)
	{
	  /* "auto" potentially used for type deduction.  */
	  ಯದಿ (specs->c23_auto_p)
	    error ("duplicate %qE", scspec);
	  specs->c23_auto_p = ಸತ್ಯ;
	  ಪ್ರತ್ಯಾಗಮ specs;
	}
      n = csc_auto;
      /* auto may only be used with another storage class specifier,
	 such as constexpr, if the type is inferred.  */
      ಯದಿ (specs->constexpr_p)
	error ("%qE used with %<constexpr%>", scspec);
      ಭಙ್ಗ;
    ಪಕ್ಷ RID_EXTERN:
      n = csc_extern;
      /* Diagnose "__thread extern".  */
      ಯದಿ (specs->thread_p && specs->thread_gnu_p)
	error ("%<__thread%> before %<extern%>");
      ಭಙ್ಗ;
    ಪಕ್ಷ RID_REGISTER:
      n = csc_register;
      ಭಙ್ಗ;
    ಪಕ್ಷ RID_STATIC:
      n = csc_static;
      /* Diagnose "__thread static".  */
      ಯದಿ (specs->thread_p && specs->thread_gnu_p)
	error ("%<__thread%> before %<static%>");
      ಭಙ್ಗ;
    ಪಕ್ಷ RID_TYPEDEF:
      n = csc_typedef;
      ಯದಿ (specs->c23_auto_p)
	{
	  error ("%<typedef%> used with %<auto%>");
	  specs->c23_auto_p = ಅಸತ್ಯ;
	}
      ಭಙ್ಗ;
    ಪಕ್ಷ RID_CONSTEXPR:
      dupe = specs->constexpr_p;
      ಯದಿ (specs->storage_class == csc_extern)
	error ("%qE used with %<extern%>", scspec);
      ಅನ್ಯಥಾ ಯದಿ (specs->storage_class == csc_typedef)
	error ("%qE used with %<typedef%>", scspec);
      ಅನ್ಯಥಾ ಯದಿ (specs->storage_class == csc_auto)
	/* auto may only be used with another storage class specifier,
	   such as constexpr, if the type is inferred.  */
	error ("%qE used with %<auto%>", scspec);
      ಅನ್ಯಥಾ ಯದಿ (specs->thread_p)
	error ("%qE used with %qs", scspec,
	       specs->thread_gnu_p ? "__thread" : "_Thread_local");
      ಅನ್ಯಥಾ
	specs->constexpr_p = ಸತ್ಯ;
      ಭಙ್ಗ;
    ಸ್ವಭಾವ:
      gcc_unreachable ();
    }
  ಯದಿ (n != csc_none && n == specs->storage_class)
    dupe = ಸತ್ಯ;
  ಯದಿ (dupe)
    {
      ಯದಿ (i == RID_THREAD)
	error ("duplicate %<_Thread_local%> or %<__thread%>");
      ಅನ್ಯಥಾ
	error ("duplicate %qE", scspec);
    }
  ಯದಿ (n != csc_none)
    {
      ಯದಿ (specs->storage_class != csc_none && n != specs->storage_class)
	{
	  error ("multiple storage classes in declaration specifiers");
	}
      ಅನ್ಯಥಾ
	{
	  specs->storage_class = n;
	  specs->locations[cdw_storage_class] = loc;
	  ಯದಿ (n != csc_extern && n != csc_static && specs->thread_p)
	    {
	      error ("%qs used with %qE",
		     specs->thread_gnu_p ? "__thread" : "_Thread_local",
		     scspec);
	      specs->thread_p = ಅಸತ್ಯ;
	    }
	  ಯದಿ (n != csc_auto && n != csc_register && n != csc_static
	      && specs->constexpr_p)
	    {
	      error ("%<constexpr%> used with %qE", scspec);
	      specs->constexpr_p = ಅಸತ್ಯ;
	    }
	}
    }
  ಪ್ರತ್ಯಾಗಮ specs;
}

/* Add the attributes ATTRS to the declaration specifiers SPECS,
   returning SPECS.  */

ಸಂರಚನಾ c_declspecs *
declspecs_add_attrs (location_t loc, ಸಂರಚನಾ c_declspecs *specs, ವೃಕ್ಷ attrs)
{
  specs->attrs = chainon (attrs, specs->attrs);
  specs->locations[cdw_attributes] = loc;
  specs->declspecs_seen_p = ಸತ್ಯ;
  /* In the case of standard attributes at the start of the
     declaration, the caller will reset this.  */
  specs->non_std_attrs_seen_p = ಸತ್ಯ;
  ಪ್ರತ್ಯಾಗಮ specs;
}

/* Add an _Alignas specifier (expression ALIGN, or type whose
   alignment is ALIGN) to the declaration specifiers SPECS, returning
   SPECS.  */
ಸಂರಚನಾ c_declspecs *
declspecs_add_alignas (location_t loc,
		       ಸಂರಚನಾ c_declspecs *specs, ವೃಕ್ಷ align)
{
  specs->alignas_p = ಸತ್ಯ;
  specs->locations[cdw_alignas] = loc;
  ಯದಿ (align == error_mark_ಗಂಟು)
    ಪ್ರತ್ಯಾಗಮ specs;

  /* Only accept the alignment if it's valid and greater than
     the current one.  Zero is invalid but by C11 required to
     be silently ignored.  */
  ಪೂರ್ಣಾಙ್ಕ align_log = check_user_alignment (align, ಅಸತ್ಯ, /* warn_zero = */ಅಸತ್ಯ);
  ಯದಿ (align_log > specs->align_log)
    specs->align_log = align_log;
  ಪ್ರತ್ಯಾಗಮ specs;
}

/* Combine "long", "short", "signed", "unsigned" and "_Complex" type
   specifiers with any other type specifier to determine the resulting
   type.  This is where ISO C checks on complex types are made, since
   "_Complex long" is a prefix of the valid ISO C type "_Complex long
   double".  Also apply postfix standard attributes to modify the type.  */

ಸಂರಚನಾ c_declspecs *
finish_declspecs (ಸಂರಚನಾ c_declspecs *specs)
{
  /* If a type was specified as a whole, we have no modifiers and are
     done.  */
  ಯದಿ (specs->type != NULL_ವೃಕ್ಷ)
    {
      gcc_assert (!specs->long_p && !specs->long_long_p && !specs->short_p
		  && !specs->signed_p && !specs->unsigned_p
		  && !specs->complex_p && !specs->c23_auto_p);

      /* Set a dummy type.  */
      ಯದಿ (ವೃಕ್ಷ_CODE (specs->type) == ERROR_MARK)
        specs->type = integer_type_ಗಂಟು;
      ಗಚ್ಛ handle_postfix_attrs;
    }

  /* If none of "void", "_Bool", "char", "int", "float" or "double"
     has been specified, treat it as "int" unless "_Complex" is
     present and there are no other specifiers.  If we just have
     "_Complex", it is equivalent to "_Complex double", but e.g.
     "_Complex short" is equivalent to "_Complex short int".  */
  ಯದಿ (specs->typespec_word == cts_none)
    {
      ಯದಿ (specs->saturating_p)
	{
	  error_at (specs->locations[cdw_saturating],
		    "%<_Sat%> is used without %<_Fract%> or %<_Accum%>");
	  ಯದಿ (!targetm.fixed_point_supported_p ())
	    error_at (specs->locations[cdw_saturating],
		      "fixed-point types not supported for this target");
	  specs->typespec_word = cts_fract;
	}
      ಅನ್ಯಥಾ ಯದಿ (specs->long_p || specs->short_p
	       || specs->signed_p || specs->unsigned_p)
	{
	  specs->typespec_word = cts_int;
	}
      ಅನ್ಯಥಾ ಯದಿ (specs->complex_p)
	{
	  specs->typespec_word = cts_double;
	  pedwarn (specs->locations[cdw_complex], OPT_Wpedantic,
		   "ISO C does not support plain %<complex%> meaning "
		   "%<double complex%>");
	}
      ಅನ್ಯಥಾ ಯದಿ (specs->c23_auto_p)
	{
	  /* Type to be filled in later, including applying postfix
	     attributes.  This warning only actually appears for
	     -Wc11-c23-compat in C23 mode; in older modes, there may
	     be a warning or pedwarn for implicit "int" instead, or
	     other errors for use of auto at file scope.  */
	  pedwarn_c11 (ಒಳಹರಿವು_location, OPT_Wpedantic,
		       "ISO C does not support %<auto%> type deduction "
		       "before C23");
	  ಪ್ರತ್ಯಾಗಮ specs;
	}
      ಅನ್ಯಥಾ
	{
	  specs->typespec_word = cts_int;
	  specs->default_int_p = ಸತ್ಯ;
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
  ವಿಕಲ್ಪ (specs->typespec_word)
    {
    ಪಕ್ಷ cts_auto_type:
      gcc_assert (!specs->long_p && !specs->short_p
		  && !specs->signed_p && !specs->unsigned_p
		  && !specs->complex_p);
      /* Type to be filled in later.  */
      ಯದಿ (specs->postfix_attrs)
	error ("%<__auto_type%> followed by %<[[]]%> attributes");
      ಭಙ್ಗ;
    ಪಕ್ಷ cts_void:
      gcc_assert (!specs->long_p && !specs->short_p
		  && !specs->signed_p && !specs->unsigned_p
		  && !specs->complex_p);
      specs->type = void_type_ಗಂಟು;
      ಭಙ್ಗ;
    ಪಕ್ಷ cts_bool:
      gcc_assert (!specs->long_p && !specs->short_p
		  && !specs->signed_p && !specs->unsigned_p
		  && !specs->complex_p);
      specs->type = boolean_type_ಗಂಟು;
      ಭಙ್ಗ;
    ಪಕ್ಷ cts_char:
      gcc_assert (!specs->long_p && !specs->short_p);
      gcc_assert (!(specs->signed_p && specs->unsigned_p));
      ಯದಿ (specs->signed_p)
	specs->type = signed_char_type_ಗಂಟು;
      ಅನ್ಯಥಾ ಯದಿ (specs->unsigned_p)
	specs->type = unsigned_char_type_ಗಂಟು;
      ಅನ್ಯಥಾ
	specs->type = char_type_ಗಂಟು;
      ಯದಿ (specs->complex_p)
	{
	  pedwarn (specs->locations[cdw_complex], OPT_Wpedantic,
		   "ISO C does not support complex integer types");
	  specs->type = build_complex_type (specs->type);
	}
      ಭಙ್ಗ;
    ಪಕ್ಷ cts_int_n:
      gcc_assert (!specs->long_p && !specs->short_p && !specs->long_long_p);
      gcc_assert (!(specs->signed_p && specs->unsigned_p));
      ಯದಿ (! int_n_enabled_p[specs->u.int_n_idx])
	specs->type = integer_type_ಗಂಟು;
      ಅನ್ಯಥಾ
	specs->type = (specs->unsigned_p
		       ? int_n_trees[specs->u.int_n_idx].unsigned_type
		       : int_n_trees[specs->u.int_n_idx].signed_type);
      ಯದಿ (specs->complex_p)
	{
	  pedwarn (specs->locations[cdw_complex], OPT_Wpedantic,
		   "ISO C does not support complex integer types");
	  specs->type = build_complex_type (specs->type);
	}
      ಭಙ್ಗ;
    ಪಕ್ಷ cts_int:
      gcc_assert (!(specs->long_p && specs->short_p));
      gcc_assert (!(specs->signed_p && specs->unsigned_p));
      ಯದಿ (specs->long_long_p)
	specs->type = (specs->unsigned_p
		       ? long_long_unsigned_type_ಗಂಟು
		       : long_long_integer_type_ಗಂಟು);
      ಅನ್ಯಥಾ ಯದಿ (specs->long_p)
	specs->type = (specs->unsigned_p
		       ? long_unsigned_type_ಗಂಟು
		       : long_integer_type_ಗಂಟು);
      ಅನ್ಯಥಾ ಯದಿ (specs->short_p)
	specs->type = (specs->unsigned_p
		       ? short_unsigned_type_ಗಂಟು
		       : short_integer_type_ಗಂಟು);
      ಅನ್ಯಥಾ
	specs->type = (specs->unsigned_p
		       ? unsigned_type_ಗಂಟು
		       : integer_type_ಗಂಟು);
      ಯದಿ (specs->complex_p)
	{
	  pedwarn (specs->locations[cdw_complex], OPT_Wpedantic,
		   "ISO C does not support complex integer types");
	  specs->type = build_complex_type (specs->type);
	}
      ಭಙ್ಗ;
    ಪಕ್ಷ cts_float:
      gcc_assert (!specs->long_p && !specs->short_p
		  && !specs->signed_p && !specs->unsigned_p);
      specs->type = (specs->complex_p
		     ? complex_float_type_ಗಂಟು
		     : float_type_ಗಂಟು);
      ಭಙ್ಗ;
    ಪಕ್ಷ cts_double:
      gcc_assert (!specs->long_long_p && !specs->short_p
		  && !specs->signed_p && !specs->unsigned_p);
      ಯದಿ (specs->long_p)
	{
	  specs->type = (specs->complex_p
			 ? complex_long_double_type_ಗಂಟು
			 : long_double_type_ಗಂಟು);
	}
      ಅನ್ಯಥಾ
	{
	  specs->type = (specs->complex_p
			 ? complex_double_type_ಗಂಟು
			 : double_type_ಗಂಟು);
	}
      ಭಙ್ಗ;
    ಪಕ್ಷ cts_floatn_nx:
      gcc_assert (!specs->long_p && !specs->short_p
		  && !specs->signed_p && !specs->unsigned_p);
      ಯದಿ (FLOATN_NX_TYPE_ಗಂಟು (specs->u.floatn_nx_idx) == NULL_ವೃಕ್ಷ)
	specs->type = integer_type_ಗಂಟು;
      ಅನ್ಯಥಾ ಯದಿ (specs->complex_p)
	specs->type = COMPLEX_FLOATN_NX_TYPE_ಗಂಟು (specs->u.floatn_nx_idx);
      ಅನ್ಯಥಾ
	specs->type = FLOATN_NX_TYPE_ಗಂಟು (specs->u.floatn_nx_idx);
      ಭಙ್ಗ;
    ಪಕ್ಷ cts_dfloat32:
    ಪಕ್ಷ cts_dfloat64:
    ಪಕ್ಷ cts_dfloat128:
    ಪಕ್ಷ cts_dfloat64x:
      gcc_assert (!specs->long_p && !specs->long_long_p && !specs->short_p
		  && !specs->signed_p && !specs->unsigned_p && !specs->complex_p);
      ಯದಿ (!targetm.decimal_float_supported_p ())
	specs->type = integer_type_ಗಂಟು;
      ಅನ್ಯಥಾ ಯದಿ (specs->typespec_word == cts_dfloat32)
	specs->type = dfloat32_type_ಗಂಟು;
      ಅನ್ಯಥಾ ಯದಿ (specs->typespec_word == cts_dfloat64)
	specs->type = dfloat64_type_ಗಂಟು;
      ಅನ್ಯಥಾ ಯದಿ (specs->typespec_word == cts_dfloat128)
	specs->type = dfloat128_type_ಗಂಟು;
      ಅನ್ಯಥಾ
	specs->type = dfloat64x_type_ಗಂಟು;
      ಭಙ್ಗ;
    ಪಕ್ಷ cts_fract:
      gcc_assert (!specs->complex_p);
      ಯದಿ (!targetm.fixed_point_supported_p ())
	specs->type = integer_type_ಗಂಟು;
      ಅನ್ಯಥಾ ಯದಿ (specs->saturating_p)
	{
	  ಯದಿ (specs->long_long_p)
	    specs->type = specs->unsigned_p
			  ? sat_unsigned_long_long_fract_type_ಗಂಟು
			  : sat_long_long_fract_type_ಗಂಟು;
	  ಅನ್ಯಥಾ ಯದಿ (specs->long_p)
	    specs->type = specs->unsigned_p
			  ? sat_unsigned_long_fract_type_ಗಂಟು
			  : sat_long_fract_type_ಗಂಟು;
	  ಅನ್ಯಥಾ ಯದಿ (specs->short_p)
	    specs->type = specs->unsigned_p
			  ? sat_unsigned_short_fract_type_ಗಂಟು
			  : sat_short_fract_type_ಗಂಟು;
	  ಅನ್ಯಥಾ
	    specs->type = specs->unsigned_p
			  ? sat_unsigned_fract_type_ಗಂಟು
			  : sat_fract_type_ಗಂಟು;
	}
      ಅನ್ಯಥಾ
	{
	  ಯದಿ (specs->long_long_p)
	    specs->type = specs->unsigned_p
			  ? unsigned_long_long_fract_type_ಗಂಟು
			  : long_long_fract_type_ಗಂಟು;
	  ಅನ್ಯಥಾ ಯದಿ (specs->long_p)
	    specs->type = specs->unsigned_p
			  ? unsigned_long_fract_type_ಗಂಟು
			  : long_fract_type_ಗಂಟು;
	  ಅನ್ಯಥಾ ಯದಿ (specs->short_p)
	    specs->type = specs->unsigned_p
			  ? unsigned_short_fract_type_ಗಂಟು
			  : short_fract_type_ಗಂಟು;
	  ಅನ್ಯಥಾ
	    specs->type = specs->unsigned_p
			  ? unsigned_fract_type_ಗಂಟು
			  : fract_type_ಗಂಟು;
	}
      ಭಙ್ಗ;
    ಪಕ್ಷ cts_accum:
      gcc_assert (!specs->complex_p);
      ಯದಿ (!targetm.fixed_point_supported_p ())
	specs->type = integer_type_ಗಂಟು;
      ಅನ್ಯಥಾ ಯದಿ (specs->saturating_p)
	{
	  ಯದಿ (specs->long_long_p)
	    specs->type = specs->unsigned_p
			  ? sat_unsigned_long_long_accum_type_ಗಂಟು
			  : sat_long_long_accum_type_ಗಂಟು;
	  ಅನ್ಯಥಾ ಯದಿ (specs->long_p)
	    specs->type = specs->unsigned_p
			  ? sat_unsigned_long_accum_type_ಗಂಟು
			  : sat_long_accum_type_ಗಂಟು;
	  ಅನ್ಯಥಾ ಯದಿ (specs->short_p)
	    specs->type = specs->unsigned_p
			  ? sat_unsigned_short_accum_type_ಗಂಟು
			  : sat_short_accum_type_ಗಂಟು;
	  ಅನ್ಯಥಾ
	    specs->type = specs->unsigned_p
			  ? sat_unsigned_accum_type_ಗಂಟು
			  : sat_accum_type_ಗಂಟು;
	}
      ಅನ್ಯಥಾ
	{
	  ಯದಿ (specs->long_long_p)
	    specs->type = specs->unsigned_p
			  ? unsigned_long_long_accum_type_ಗಂಟು
			  : long_long_accum_type_ಗಂಟು;
	  ಅನ್ಯಥಾ ಯದಿ (specs->long_p)
	    specs->type = specs->unsigned_p
			  ? unsigned_long_accum_type_ಗಂಟು
			  : long_accum_type_ಗಂಟು;
	  ಅನ್ಯಥಾ ಯದಿ (specs->short_p)
	    specs->type = specs->unsigned_p
			  ? unsigned_short_accum_type_ಗಂಟು
			  : short_accum_type_ಗಂಟು;
	  ಅನ್ಯಥಾ
	    specs->type = specs->unsigned_p
			  ? unsigned_accum_type_ಗಂಟು
			  : accum_type_ಗಂಟು;
	}
      ಭಙ್ಗ;
    ಪಕ್ಷ cts_bitint:
      gcc_assert (!specs->long_p && !specs->short_p
		  && !specs->complex_p);
      ಯದಿ (!specs->unsigned_p && specs->u.bitint_prec == 1 && !flag_isoc2y)
	{
	  error_at (specs->locations[cdw_typespec],
		    "%<signed _BitInt%> argument must be at least 2 "
		    "before C2Y");
	  specs->type = integer_type_ಗಂಟು;
	  ಭಙ್ಗ;
	}
      ಯದಿ (specs->u.bitint_prec == -1)
	specs->type = integer_type_ಗಂಟು;
      ಅನ್ಯಥಾ
	{
	  pedwarn_c11 (specs->locations[cdw_typespec], OPT_Wpedantic,
		       "ISO C does not support %<%s_BitInt(%d)%> before C23",
		       specs->unsigned_p ? "unsigned "
		       : specs->signed_p ? "signed " : "",
		       specs->u.bitint_prec);
	  specs->type = build_bitint_type (specs->u.bitint_prec,
					   specs->unsigned_p);
	}
      ಭಙ್ಗ;
    ಸ್ವಭಾವ:
      gcc_unreachable ();
    }
 handle_postfix_attrs:
  ಯದಿ (specs->type != ರಿಕ್ತ)
    {
      specs->postfix_attrs
	= c_warn_type_attributes (specs->type, specs->postfix_attrs);
      decl_attributes (&specs->type, specs->postfix_attrs, 0);
      specs->postfix_attrs = NULL_ವೃಕ್ಷ;
    }

  ಪ್ರತ್ಯಾಗಮ specs;
}

/* Perform final processing on one file scope's declarations (or the
   external scope's declarations), GLOBALS.  */

ಸ್ಥಿರ ಶೂನ್ಯ
c_write_global_declarations_1 (ವೃಕ್ಷ globals)
{
  ವೃಕ್ಷ decl;
  ತಾರ್ಕಿಕ reconsider;

  /* Process the decls in the order they were written.  */
  ಪ್ರತಿ (decl = globals; decl; decl = DECL_CHAIN (decl))
    {
      /* Check for used but undefined static functions using the C
	 standard's definition of "used", and set TREE_NO_WARNING so
	 that check_global_declaration doesn't repeat the check.  */
      ಯದಿ (ವೃಕ್ಷ_CODE (decl) == FUNCTION_DECL
	  && DECL_INITIAL (decl) == NULL_ವೃಕ್ಷ
	  && DECL_EXTERNAL (decl)
	  && !ವೃಕ್ಷ_PUBLIC (decl)
	  && !warning_suppressed_p (decl, OPT_Wunused))
	{
	  ಯದಿ (C_DECL_USED (decl))
	    {
	      ಯದಿ (pedwarn (ಒಳಹರಿವು_location, 0, "%q+F used but never defined",
			   decl))
		suppress_warning (decl, OPT_Wunused);
	    }
	  /* For -Wunused-function warn about unused static prototypes.  */
	  ಅನ್ಯಥಾ ಯದಿ (warn_unused_function
		   && ! DECL_ARTIFICIAL (decl)
		   && warning (OPT_Wunused_function,
			       "%q+F declared %<static%> but never defined",
			       decl))
	    suppress_warning (decl, OPT_Wunused);
	}

      wrapup_global_declaration_1 (decl);
    }

  ಕುರು
    {
      reconsider = ಅಸತ್ಯ;
      ಪ್ರತಿ (decl = globals; decl; decl = DECL_CHAIN (decl))
	reconsider |= wrapup_global_declaration_2 (decl);
    }
  ಯಾವತ್ (reconsider);
}

/* Preserve the external declarations scope across a garbage collect.  */
ಸ್ಥಿರ GTY(()) ವೃಕ್ಷ ext_block;

/* Collect all references relevant to SOURCE_FILE.  */

ಸ್ಥಿರ ಶೂನ್ಯ
collect_all_refs (ಧ್ರುವ ವರ್ಣ *source_file)
{
  ವೃಕ್ಷ t;
  unsigned i;

  FOR_EACH_VEC_ELT (*all_translation_units, i, t)
    collect_ada_nodes (BLOCK_VARS (DECL_INITIAL (t)), source_file);

  collect_ada_nodes (BLOCK_VARS (ext_block), source_file);
}

/* Collect source file references at global level.  */

ಸ್ಥಿರ ಶೂನ್ಯ
collect_source_refs (ಶೂನ್ಯ)
{
  ವೃಕ್ಷ t;
  ವೃಕ್ಷ decls;
  ವೃಕ್ಷ decl;
  unsigned i;

  FOR_EACH_VEC_ELT (*all_translation_units, i, t)
    {
      decls = DECL_INITIAL (t);
      ಪ್ರತಿ (decl = BLOCK_VARS (decls); decl; decl = ವೃಕ್ಷ_CHAIN (decl))
	ಯದಿ (!DECL_IS_UNDECLARED_BUILTIN (decl))
	  collect_source_ref (DECL_SOURCE_FILE (decl));
    }

  ಪ್ರತಿ (decl = BLOCK_VARS (ext_block); decl; decl = ವೃಕ್ಷ_CHAIN (decl))
    ಯದಿ (!DECL_IS_UNDECLARED_BUILTIN (decl))
      collect_source_ref (DECL_SOURCE_FILE (decl));
}

/* Free attribute access data that are not needed by the middle end. */

ಸ್ಥಿರ ಶೂನ್ಯ
free_attr_access_data ()
{
  ಸಂರಚನಾ cgraph_ಗಂಟು *n;

  /* Iterate over all functions declared in the translation unit.  */
  FOR_EACH_FUNCTION (n)
    {
      ಪ್ರತಿ (ವೃಕ್ಷ parm = DECL_ARGUMENTS (n->decl); parm; parm = ವೃಕ್ಷ_CHAIN (parm))
	ಯದಿ (ವೃಕ್ಷ attrs = DECL_ATTRIBUTES (parm))
	  attr_access::free_lang_data (attrs);

      ವೃಕ್ಷ fntype = ವೃಕ್ಷ_TYPE (n->decl);
      ಯದಿ (!fntype || fntype == error_mark_ಗಂಟು)
	ಅನುವರ್ತ;
      ವೃಕ್ಷ attrs = TYPE_ATTRIBUTES (fntype);
      ಯದಿ (!attrs)
	ಅನುವರ್ತ;

      attr_access::free_lang_data (attrs);
    }
}

/* Perform any final parser cleanups and generate initial debugging
   information.  */

ಶೂನ್ಯ
c_parse_final_cleanups (ಶೂನ್ಯ)
{
  ವೃಕ್ಷ t;
  unsigned i;

  /* We don't want to do this if generating a PCH.  */
  ಯದಿ (pch_file)
    ಪ್ರತ್ಯಾಗಮ;

  timevar_stop (TV_PHASE_PARSING);
  timevar_start (TV_PHASE_DEFERRED);

  /* Do the Objective-C stuff.  This is where all the Objective-C
     module stuff gets generated (symtab, class/protocol/selector
     lists etc).  */
  ಯದಿ (c_dialect_objc ())
    objc_write_global_declarations ();

  /* Close the external scope.  */
  ext_block = ತೆಗೆ_scope ();
  external_scope = 0;
  gcc_assert (!current_scope);

  /* Handle -fdump-ada-spec[-slim]. */
  ಯದಿ (flag_dump_ada_spec || flag_dump_ada_spec_slim)
    {
      /* Build a table of files to generate specs for */
      collect_source_ref (main_ಒಳಹರಿವು_filename);
      ಯದಿ (!flag_dump_ada_spec_slim)
	collect_source_refs ();

      dump_ada_specs (collect_all_refs, ರಿಕ್ತ);
    }

  /* Process all file scopes in this compilation, and the external_scope,
     through wrapup_global_declarations.  */
  FOR_EACH_VEC_ELT (*all_translation_units, i, t)
    c_write_global_declarations_1 (BLOCK_VARS (DECL_INITIAL (t)));
  c_write_global_declarations_1 (BLOCK_VARS (ext_block));

  /* Call this to set cpp_implicit_aliases_done on all nodes.  This is
     important for function multiversioning aliases to get resolved.  */
  symtab->process_same_body_aliases ();

  ಯದಿ (!in_lto_p)
    free_attr_access_data ();

  timevar_stop (TV_PHASE_DEFERRED);
  timevar_start (TV_PHASE_PARSING);

  ext_block = ರಿಕ್ತ;
}

/* Register reserved keyword WORD as qualifier for address space AS.  */

ಶೂನ್ಯ
c_register_addr_space (ಧ್ರುವ ವರ್ಣ *word, addr_space_t as)
{
  ಪೂರ್ಣಾಙ್ಕ rid = RID_FIRST_ADDR_SPACE + as;
  ವೃಕ್ಷ id;

  /* Address space qualifiers are only supported
     in C with GNU extensions enabled.  */
  ಯದಿ (c_dialect_objc () || flag_no_asm)
    ಪ್ರತ್ಯಾಗಮ;

  id = get_identifier (word);
  C_SET_RID_CODE (id, rid);
  C_IS_RESERVED_WORD (id) = 1;
  ridpointers [rid] = id;
}

/* Return identifier to look up for omp declare reduction.  */

ವೃಕ್ಷ
c_omp_reduction_id (ಗಣನಾ ವೃಕ್ಷ_code reduction_code, ವೃಕ್ಷ reduction_id)
{
  ಧ್ರುವ ವರ್ಣ *p = ರಿಕ್ತ;
  ವಿಕಲ್ಪ (reduction_code)
    {
    ಪಕ್ಷ PLUS_ಅಭಿವ್ಯಕ್ತಿ: p = "+"; ಭಙ್ಗ;
    ಪಕ್ಷ MULT_ಅಭಿವ್ಯಕ್ತಿ: p = "*"; ಭಙ್ಗ;
    ಪಕ್ಷ MINUS_ಅಭಿವ್ಯಕ್ತಿ: p = "-"; ಭಙ್ಗ;
    ಪಕ್ಷ BIT_AND_ಅಭಿವ್ಯಕ್ತಿ: p = "&"; ಭಙ್ಗ;
    ಪಕ್ಷ BIT_XOR_ಅಭಿವ್ಯಕ್ತಿ: p = "^"; ಭಙ್ಗ;
    ಪಕ್ಷ BIT_IOR_ಅಭಿವ್ಯಕ್ತಿ: p = "|"; ಭಙ್ಗ;
    ಪಕ್ಷ TRUTH_ANDIF_ಅಭಿವ್ಯಕ್ತಿ: p = "&&"; ಭಙ್ಗ;
    ಪಕ್ಷ TRUTH_ORIF_ಅಭಿವ್ಯಕ್ತಿ: p = "||"; ಭಙ್ಗ;
    ಪಕ್ಷ MIN_ಅಭಿವ್ಯಕ್ತಿ: p = "min"; ಭಙ್ಗ;
    ಪಕ್ಷ MAX_ಅಭಿವ್ಯಕ್ತಿ: p = "max"; ಭಙ್ಗ;
    ಸ್ವಭಾವ:
      ಭಙ್ಗ;
    }

  ಯದಿ (p == ರಿಕ್ತ)
    {
      ಯದಿ (ವೃಕ್ಷ_CODE (reduction_id) != IDENTIFIER_ಗಂಟು)
	ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
      p = IDENTIFIER_POINTER (reduction_id);
    }

  ಧ್ರುವ ವರ್ಣ prefix[] = "omp declare reduction ";
  size_t lenp = ಪರಿಮಾಣ (prefix);
  size_t len = strlen (p);
  ವರ್ಣ *name = XALLOCAVEC (ವರ್ಣ, lenp + len);
  memcpy (name, prefix, lenp - 1);
  memcpy (name + lenp - 1, p, len + 1);
  ಪ್ರತ್ಯಾಗಮ get_identifier (name);
}

/* Lookup REDUCTION_ID in the current scope, or create an artificial
   VAR_DECL, bind it into the current scope and return it.  */

ವೃಕ್ಷ
c_omp_reduction_decl (ವೃಕ್ಷ reduction_id)
{
  ಸಂರಚನಾ c_binding *b = I_ಚಿಹ್ನೆ_BINDING (reduction_id);
  ಯದಿ (b != ರಿಕ್ತ && B_IN_CURRENT_SCOPE (b))
    ಪ್ರತ್ಯಾಗಮ b->decl;

  ವೃಕ್ಷ decl = build_decl (BUILTINS_LOCATION, VAR_DECL,
			  reduction_id, integer_type_ಗಂಟು);
  DECL_ARTIFICIAL (decl) = 1;
  DECL_EXTERNAL (decl) = 1;
  ವೃಕ್ಷ_STATIC (decl) = 1;
  ವೃಕ್ಷ_PUBLIC (decl) = 0;
  bind (reduction_id, decl, current_scope, ಸತ್ಯ, ಅಸತ್ಯ, BUILTINS_LOCATION);
  ಪ್ರತ್ಯಾಗಮ decl;
}

/* Lookup REDUCTION_ID in the first scope where it has entry for TYPE.  */

ವೃಕ್ಷ
c_omp_reduction_lookup (ವೃಕ್ಷ reduction_id, ವೃಕ್ಷ type)
{
  ಸಂರಚನಾ c_binding *b = I_ಚಿಹ್ನೆ_BINDING (reduction_id);
  ಯಾವತ್ (b)
    {
      ವೃಕ್ಷ t;
      ಪ್ರತಿ (t = DECL_INITIAL (b->decl); t; t = ವೃಕ್ಷ_CHAIN (t))
	ಯದಿ (comptypes (ವೃಕ್ಷ_PURPOSE (t), type))
	  ಪ್ರತ್ಯಾಗಮ ವೃಕ್ಷ_ಮೌಲ್ಯ (t);
      b = b->shadowed;
    }
  ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
}

/* Helper function called via walk_tree, to diagnose invalid
   #pragma omp declare reduction combiners or initializers.  */

ವೃಕ್ಷ
c_check_omp_declare_reduction_r (ವೃಕ್ಷ *tp, ಪೂರ್ಣಾಙ್ಕ *, ಶೂನ್ಯ *data)
{
  ವೃಕ್ಷ *vars = (ವೃಕ್ಷ *) data;
  ಯದಿ (SSA_VAR_P (*tp)
      && !DECL_ARTIFICIAL (*tp)
      && *tp != vars[0]
      && *tp != vars[1])
    {
      location_t loc = DECL_SOURCE_LOCATION (vars[0]);
      ಯದಿ (strcmp (IDENTIFIER_POINTER (DECL_NAME (vars[0])), "omp_out") == 0)
	error_at (loc, "%<#pragma omp declare reduction%> combiner refers to "
		       "variable %qD which is not %<omp_out%> nor %<omp_in%>",
		  *tp);
      ಅನ್ಯಥಾ
	error_at (loc, "%<#pragma omp declare reduction%> initializer refers "
		       "to variable %qD which is not %<omp_priv%> nor "
		       "%<omp_orig%>",
		  *tp);
      ಪ್ರತ್ಯಾಗಮ *tp;
    }
  ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;
}

/* Return identifier to look up for omp declare mapper.  */

ವೃಕ್ಷ
c_omp_mapper_id (ವೃಕ್ಷ mapper_id)
{
  ಧ್ರುವ ವರ್ಣ *p = ರಿಕ್ತ;

  ಧ್ರುವ ವರ್ಣ prefix[] = "omp declare mapper ";

  ಯದಿ (mapper_id == NULL_ವೃಕ್ಷ)
    p = "<default>";
  ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_CODE (mapper_id) == IDENTIFIER_ಗಂಟು)
    p = IDENTIFIER_POINTER (mapper_id);
  ಅನ್ಯಥಾ
    ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;

  size_t lenp = ಪರಿಮಾಣ (prefix);
  size_t len = strlen (p);
  ವರ್ಣ *name = XALLOCAVEC (ವರ್ಣ, lenp + len);
  memcpy (name, prefix, lenp - 1);
  memcpy (name + lenp - 1, p, len + 1);
  ಪ್ರತ್ಯಾಗಮ get_identifier (name);
}

/* Lookup MAPPER_ID in the current scope, or create an artificial
   VAR_DECL, bind it into the current scope and return it.  */

ವೃಕ್ಷ
c_omp_mapper_decl (ವೃಕ್ಷ mapper_id)
{
  ಸಂರಚನಾ c_binding *b = I_ಚಿಹ್ನೆ_BINDING (mapper_id);
  ಯದಿ (b != ರಿಕ್ತ && B_IN_CURRENT_SCOPE (b))
    ಪ್ರತ್ಯಾಗಮ b->decl;

  ವೃಕ್ಷ decl = build_decl (BUILTINS_LOCATION, VAR_DECL,
			  mapper_id, integer_type_ಗಂಟು);
  DECL_ARTIFICIAL (decl) = 1;
  DECL_EXTERNAL (decl) = 1;
  ವೃಕ್ಷ_STATIC (decl) = 1;
  ವೃಕ್ಷ_PUBLIC (decl) = 0;
  bind (mapper_id, decl, current_scope, ಸತ್ಯ, ಅಸತ್ಯ, BUILTINS_LOCATION);
  ಪ್ರತ್ಯಾಗಮ decl;
}

/* Lookup MAPPER_ID in the first scope where it has entry for TYPE.  */

ವೃಕ್ಷ
c_omp_mapper_lookup (ವೃಕ್ಷ mapper_id, ವೃಕ್ಷ type)
{
  ಯದಿ (!RECORD_OR_UNION_TYPE_P (type))
    ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;

  mapper_id = c_omp_mapper_id (mapper_id);

  ಸಂರಚನಾ c_binding *b = I_ಚಿಹ್ನೆ_BINDING (mapper_id);
  ಯಾವತ್ (b)
    {
      ವೃಕ್ಷ t;
      ಪ್ರತಿ (t = DECL_INITIAL (b->decl); t; t = ವೃಕ್ಷ_CHAIN (t))
	ಯದಿ (comptypes (ವೃಕ್ಷ_PURPOSE (t), type))
	  ಪ್ರತ್ಯಾಗಮ ವೃಕ್ಷ_ಮೌಲ್ಯ (t);
      b = b->shadowed;
    }
  ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;
}

/* For C, we record a pointer to the mapper itself without wrapping it in an
   artificial function or similar.  So, just return it.  */

ವೃಕ್ಷ
c_omp_extract_mapper_directive (ವೃಕ್ಷ mapper)
{
  ಪ್ರತ್ಯಾಗಮ mapper;
}

/* For now we can handle singleton OMP_ARRAY_SECTIONs with custom mappers, but
   nothing more complicated.  */

ವೃಕ್ಷ
c_omp_map_array_section (location_t loc, ವೃಕ್ಷ t)
{
  ವೃಕ್ಷ ಕೆಳಗಿನ = ವೃಕ್ಷ_OPERAND (t, 1);
  ವೃಕ್ಷ len = ವೃಕ್ಷ_OPERAND (t, 2);

  ಯದಿ (len && integer_onep (len))
    {
      t = ವೃಕ್ಷ_OPERAND (t, 0);

      ಯದಿ (!ಕೆಳಗಿನ)
	ಕೆಳಗಿನ = integer_zero_ಗಂಟು;

      t = build_array_ref (loc, t, ಕೆಳಗಿನ);
    }

  ಪ್ರತ್ಯಾಗಮ t;
}

/* Helper function for below function.  */

ಸ್ಥಿರ ವೃಕ್ಷ
c_omp_scan_mapper_bindings_r (ವೃಕ್ಷ *tp, ಪೂರ್ಣಾಙ್ಕ *walk_subtrees, ಶೂನ್ಯ *ptr)
{
  ವೃಕ್ಷ t = *tp;
  omp_mapper_list<ವೃಕ್ಷ> *mlist = (omp_mapper_list<ವೃಕ್ಷ> *) ptr;
  ವೃಕ್ಷ aggr_type = NULL_ವೃಕ್ಷ;

  ಯದಿ (ವೃಕ್ಷ_CODE (t) == SIZEOF_ಅಭಿವ್ಯಕ್ತಿ
      || ವೃಕ್ಷ_CODE (t) == ALIGNOF_ಅಭಿವ್ಯಕ್ತಿ)
    {
      *walk_subtrees = 0;
      ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;
    }

  ಯದಿ (ವೃಕ್ಷ_CODE (t) == OMP_CLAUSE)
    ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;

  ಯದಿ (ವೃಕ್ಷ_CODE (t) == COMPONENT_REF
      && RECORD_OR_UNION_TYPE_P (ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_OPERAND (t, 0))))
    aggr_type = ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_OPERAND (t, 0));
  ಅನ್ಯಥಾ ಯದಿ ((ವೃಕ್ಷ_CODE (t) == VAR_DECL
	    || ವೃಕ್ಷ_CODE (t) == PARM_DECL
	    || ವೃಕ್ಷ_CODE (t) == RESULT_DECL)
	   && RECORD_OR_UNION_TYPE_P (ವೃಕ್ಷ_TYPE (t)))
    aggr_type = ವೃಕ್ಷ_TYPE (t);

  ಯದಿ (aggr_type)
    {
      ವೃಕ್ಷ mapper_fn = c_omp_mapper_lookup (NULL_ವೃಕ್ಷ, aggr_type);
      ಯದಿ (mapper_fn)
	mlist->add_mapper (NULL_ವೃಕ್ಷ, aggr_type, mapper_fn);
    }

  ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;
}

/* Scan an offload region's body, and record uses of struct- or union-typed
   variables.  Add _mapper_binding_ fake clauses to *CLAUSES_PTR.  */

ಶೂನ್ಯ
c_omp_scan_mapper_bindings (location_t loc, ವೃಕ್ಷ *clauses_ptr, ವೃಕ್ಷ body)
{
  hash_set<omp_name_type<ವೃಕ್ಷ>> seen_types;
  auto_vec<ವೃಕ್ಷ> mappers;
  omp_mapper_list<ವೃಕ್ಷ> mlist (&seen_types, &mappers);

  walk_ವೃಕ್ಷ_without_duplicates (&body, c_omp_scan_mapper_bindings_r, &mlist);

  unsigned ಪೂರ್ಣಾಙ್ಕ i;
  ವೃಕ್ಷ mapper;
  FOR_EACH_VEC_ELT (mappers, i, mapper)
    c_omp_find_nested_mappers (&mlist, mapper);

  FOR_EACH_VEC_ELT (mappers, i, mapper)
    {
      ಯದಿ (mapper == error_mark_ಗಂಟು)
	ಅನುವರ್ತ;
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
c_check_in_current_scope (ವೃಕ್ಷ decl)
{
  ಸಂರಚನಾ c_binding *b = I_ಚಿಹ್ನೆ_BINDING (DECL_NAME (decl));
  ಪ್ರತ್ಯಾಗಮ b != ರಿಕ್ತ && B_IN_CURRENT_SCOPE (b);
}

/* Search for loop or switch names.  BEFORE_LABELS is last statement before
   possible labels and SWITCH_P true for a switch, false for loops.
   Searches through last statements in cur_stmt_list, stops when seeing
   BEFORE_LABELs, or statement other than LABEL_EXPR or CASE_LABEL_EXPR.
   Returns number of loop/switch names found and if any are found, sets
   *LAST_P to the canonical loop/switch name LABEL_DECL.  */

ಪೂರ್ಣಾಙ್ಕ
c_get_loop_names (ವೃಕ್ಷ before_labels, ತಾರ್ಕಿಕ switch_p, ವೃಕ್ಷ *last_p)
{
  *last_p = NULL_ವೃಕ್ಷ;
  ಯದಿ (!building_stmt_list_p ()
      || !STATEMENT_LIST_HAS_LABEL (cur_stmt_list)
      || before_labels == void_list_ಗಂಟು)
    ಪ್ರತ್ಯಾಗಮ 0;

  ಪೂರ್ಣಾಙ್ಕ ret = 0;
  ವೃಕ್ಷ last = NULL_ವೃಕ್ಷ;
  ಪ್ರತಿ (ವೃಕ್ಷ_stmt_iterator tsi = tsi_last (cur_stmt_list);
       !tsi_end_p (tsi); tsi_prev (&tsi))
    {
      ವೃಕ್ಷ stmt = tsi_stmt (tsi);
      ಯದಿ (stmt == before_labels)
	ಭಙ್ಗ;
      ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_CODE (stmt) == LABEL_ಅಭಿವ್ಯಕ್ತಿ)
	{
	  ಯದಿ (last == NULL_ವೃಕ್ಷ)
	    last = LABEL_ಅಭಿವ್ಯಕ್ತಿ_LABEL (stmt);
	  ಅನ್ಯಥಾ
	    {
	      loop_names.safe_ತಳ್ಳು (LABEL_ಅಭಿವ್ಯಕ್ತಿ_LABEL (stmt));
	      ++ret;
	    }
	}
      ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_CODE (stmt) != CASE_LABEL_ಅಭಿವ್ಯಕ್ತಿ
	       && ವೃಕ್ಷ_CODE (stmt) != DEBUG_BEGIN_STMT)
	ಭಙ್ಗ;
    }
  ಯದಿ (last)
    {
      ಯದಿ (switch_p)
	C_DECL_SWITCH_NAME (last) = 1;
      ಅನ್ಯಥಾ
	C_DECL_LOOP_NAME (last) = 1;
      loop_names.safe_ತಳ್ಳು (last);
      ++ret;
      ಯದಿ (loop_names.length () > 16)
	{
	  unsigned ಪೂರ್ಣಾಙ್ಕ first = 0, i;
	  ವೃಕ್ಷ l, c = NULL_ವೃಕ್ಷ;
	  ಯದಿ (loop_names_hash == ರಿಕ್ತ)
	    loop_names_hash = ನೂತನ decl_ವೃಕ್ಷ_map (ret);
	  ಅನ್ಯಥಾ
	    first = loop_names.length () - ret;
	  FOR_EACH_VEC_ELT_REVERSE (loop_names, i, l)
	    {
	      ಯದಿ (C_DECL_LOOP_NAME (l) || C_DECL_SWITCH_NAME (l))
		c = l;
	      gcc_checking_assert (c);
	      loop_names_hash->put (l, c);
	      ಯದಿ (i == first)
		ಭಙ್ಗ;
	    }
	}
      *last_p = last;
    }
  ಪ್ರತ್ಯಾಗಮ ret;
}

/* Undoes what get_loop_names did when it returned NUM_NAMES.  */

ಶೂನ್ಯ
c_release_loop_names (ಪೂರ್ಣಾಙ್ಕ ಅಂಕೆ_names)
{
  unsigned len = loop_names.length () - ಅಂಕೆ_names;
  ಯದಿ (loop_names_hash)
    {
      ಯದಿ (len <= 16)
	{
	  delete loop_names_hash;
	  loop_names_hash = ರಿಕ್ತ;
	}
      ಅನ್ಯಥಾ
	{
	  unsigned ಪೂರ್ಣಾಙ್ಕ i;
	  ವೃಕ್ಷ l;
	  FOR_EACH_VEC_ELT_REVERSE (loop_names, i, l)
	    {
	      loop_names_hash->remove (l);
	      ಯದಿ (i == len)
		ಭಙ್ಗ;
	    }
	}
    }
  loop_names.truncate (len);
}

/* Finish processing of break or continue identifier operand.
   NAME is the identifier operand of break or continue and
   IS_BREAK is true iff it is break stmt.  Returns the operand
   to use for BREAK_STMT or CONTINUE_STMT, either NULL_TREE or
   canonical loop/switch name LABEL_DECL.  */

ವೃಕ್ಷ
c_finish_bc_name (location_t loc, ವೃಕ್ಷ name, ತಾರ್ಕಿಕ is_break)
{
  ವೃಕ್ಷ label = NULL_ವೃಕ್ಷ, lab;
  pedwarn_c23 (loc, OPT_Wpedantic,
	       "ISO C does not support %qs statement with an identifier "
	       "operand before C2Y", is_break ? "break" : "continue");

  /* If I_LABEL_DECL is NULL or not from current function, don't waste time
     trying to find it among loop_names, it can't be there.  */
  ಯದಿ (!loop_names.is_empty ()
      && current_function_scope
      && (lab = I_LABEL_DECL (name))
      && DECL_CONTEXT (lab) == current_function_decl)
    {
      unsigned ಪೂರ್ಣಾಙ್ಕ i;
      ವೃಕ್ಷ l, c = NULL_ವೃಕ್ಷ;
      ಯದಿ (loop_names_hash)
	{
	  ಯದಿ (ವೃಕ್ಷ *val = loop_names_hash->get (lab))
	    label = *val;
	}
      ಅನ್ಯಥಾ
	FOR_EACH_VEC_ELT_REVERSE (loop_names, i, l)
	  {
	    ಯದಿ (C_DECL_LOOP_NAME (l) || C_DECL_SWITCH_NAME (l))
	      c = l;
	    gcc_checking_assert (c);
	    ಯದಿ (l == lab)
	      {
		label = c;
		ಭಙ್ಗ;
	      }
	  }
      ಯದಿ (label)
	ವೃಕ್ಷ_USED (lab) = 1;
    }
  ಯದಿ (label == NULL_ವೃಕ್ಷ)
    {
      auto_vec<ಧ್ರುವ ವರ್ಣ *> candidates;
      unsigned ಪೂರ್ಣಾಙ್ಕ i;
      ವೃಕ್ಷ l, c = NULL_ವೃಕ್ಷ;
      FOR_EACH_VEC_ELT_REVERSE (loop_names, i, l)
	{
	  ಯದಿ (C_DECL_LOOP_NAME (l) || C_DECL_SWITCH_NAME (l))
	    c = l;
	  gcc_checking_assert (c);
	  ಯದಿ (is_break || C_DECL_LOOP_NAME (c))
	    candidates.safe_ತಳ್ಳು (IDENTIFIER_POINTER (DECL_NAME (l)));
	}
      ಧ್ರುವ ವರ್ಣ *hint = find_closest_string (IDENTIFIER_POINTER (name),
					      &candidates);
      ಯದಿ (hint)
	{
	  gcc_rich_location richloc (loc);
	  richloc.add_fixit_replace (hint);
	  ಯದಿ (is_break)
	    error_at (&richloc, "%<break%> statement operand %qE does not "
				"refer to a named loop or %<switch%>; "
				"did you mean %qs?", name, hint);
	  ಅನ್ಯಥಾ
	    error_at (&richloc, "%<continue%> statement operand %qE does not "
				"refer to a named loop; did you mean %qs?",
		      name, hint);
	}
      ಅನ್ಯಥಾ ಯದಿ (is_break)
	error_at (loc, "%<break%> statement operand %qE does not refer to a "
		       "named loop or %<switch%>", name);
      ಅನ್ಯಥಾ
	error_at (loc, "%<continue%> statement operand %qE does not refer to "
		       "a named loop", name);
    }
  ಅನ್ಯಥಾ ಯದಿ (!C_DECL_LOOP_NAME (label) && !is_break)
    {
      auto_diagnostic_group d;
      error_at (loc, "%<continue%> statement operand %qE refers to a named "
		     "%<switch%>", name);
      inform (DECL_SOURCE_LOCATION (label), "%<switch%> name defined here");
      label = NULL_ವೃಕ್ಷ;
    }
  ಅನ್ಯಥಾ ಯದಿ (!C_DECL_LOOP_SWITCH_NAME_VALID (label))
    {
      auto_diagnostic_group d;
      ಯದಿ (C_DECL_LOOP_NAME (label))
	{
	  error_at (loc, "%qs statement operand %qE refers to a loop outside "
			 "of its body", is_break ? "break" : "continue", name);
	  inform (DECL_SOURCE_LOCATION (label), "loop name defined here");
	}
      ಅನ್ಯಥಾ
	{
	  error_at (loc, "%<break%> statement operand %qE refers to a "
			 "%<switch%> outside of its body", name);
	  inform (DECL_SOURCE_LOCATION (label),
		  "%<switch%> name defined here");
	}
      label = NULL_ವೃಕ್ಷ;
    }
  ಅನ್ಯಥಾ ಯದಿ (label == loop_names.last () && (in_statement & IN_NAMED_STMT) != 0)
    /* If it is just a fancy reference to the innermost construct, handle it
       just like break; or continue; though tracking cheaply what is the
       innermost loop for continue when nested in switches would require
       another global variable and updating it.  */
    label = NULL_ವೃಕ್ಷ;
  ಅನ್ಯಥಾ
    C_DECL_LOOP_SWITCH_NAME_USED (label) = 1;
  ಪ್ರತ್ಯಾಗಮ label;
}

#ಅನ್ತರ್ಭಾವ "gt-c-c-decl.h"
