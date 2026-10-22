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

#ਅਨ੍ਤਰ੍ਭਾਵ "config.h"
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ INCLUDE_STRING
#ਅਨ੍ਤਰ੍ਭਾਵ "system.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "coretypes.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "target.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "function.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "c-tree.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "timevar.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "stringpool.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "cgraph.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "intl.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "print-tree.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "stor-layout.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "varasm.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "attribs.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "toplev.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "debug.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "c-family/c-objc.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "c-family/c-pragma.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "c-family/c-ubsan.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "c-lang.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "langhooks.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "tree-iterator.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "dumpfile.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "plugin.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "c-family/c-ada-spec.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "builtins.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "spellcheck-tree.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "gcc-rich-location.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "asan.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "c-family/name-hint.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "c-family/known-headers.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "c-family/c-spellcheck.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "context.h"  /* For 'g'.  */
#ਅਨ੍ਤਰ੍ਭਾਵ "omp-general.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "omp-offload.h"  /* For offload_vars.  */
#ਅਨ੍ਤਰ੍ਭਾਵ "c-parser.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "gcc-urlifier.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "tree-pretty-print.h"

/* In grokdeclarator, distinguish syntactic contexts of declarators.  */
ਗਿਣਤੀ decl_context
{ ਸਾਧਾਰਨ,			/* Ordinary declaration */
  FUNCDEF,			/* Function definition */
  PARM,				/* Declaration of parm before function body */
  ਖੇਤਰ,			/* Declaration inside struct or union */
  TYPENAME,			/* Typename (inside cast or sizeof)  */
  GENERIC_ASSOC };		/* Typename in generic association  */

/* States indicating how grokdeclarator() should handle declspecs marked
   with __attribute__((deprecated)) or __attribute__((unavailable)).
   An object declared as __attribute__((unavailable)) should suppress
   any reports of being declared  with unavailable or deprecated items.
   An object declared as __attribute__((deprecated)) should suppress
   warnings of uses of other deprecated items.  */

ਗਿਣਤੀ deprecated_ਹਾਲਤਾਂ {
  DEPRECATED_ਸਾਧਾਰਨ,
  DEPRECATED_SUPPRESS,
  UNAVAILABLE_DEPRECATED_SUPPRESS
};


/* Nonzero if we have seen an invalid cross reference
   to a struct, union, or enum, but not yet printed the message.  */
ਰੁੱਖ pending_invalid_xref;

/* File and line to appear in the eventual error message.  */
location_t pending_invalid_xref_location;

/* The file and line that the prototype came from if this is an
   old-style definition; used for diagnostics in
   store_parm_decls_oldstyle.  */

ਸਥਿਰ location_t current_function_prototype_locus;

/* Whether this prototype was built-in.  */

ਸਥਿਰ ਤਾਰਕਿਕ current_function_prototype_built_ਵਿੱਚ;

/* The argument type information of this prototype.  */

ਸਥਿਰ ਰੁੱਖ current_function_prototype_arg_types;

/* The argument information structure for the function currently being
   defined.  */

ਸਥਿਰ ਬਣਤਰ c_arg_info *current_function_arg_info;

/* The obstack on which parser and related data structures, which are
   not live beyond their top-level declaration or definition, are
   allocated.  */
ਬਣਤਰ obstack parser_obstack;

/* The current statement tree.  */

ਸਥਿਰ GTY(()) ਬਣਤਰ stmt_ਰੁੱਖ_s c_stmt_ਰੁੱਖ;

/* Zero if we are not in an iteration or switch statement, otherwise
   a bitmask.  See bitmask definitions in c-tree.h.  */
ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ ਵਿੱਚ_statement;

/* A list of decls to be made automatically visible in each file scope.  */
ਸਥਿਰ GTY(()) ਰੁੱਖ visible_builtins;

/* Set to 0 at beginning of a function definition, set to 1 if
   a return statement that specifies a return value is seen.  */

ਪੂਰਨ current_function_returns_ਮੁੱਲ;

/* Set to 0 at beginning of a function definition, set to 1 if
   a return statement with no argument is seen.  */

ਪੂਰਨ current_function_returns_null;

/* Set to 0 at beginning of a function definition, set to 1 if
   a call to a noreturn function is seen.  */

ਪੂਰਨ current_function_returns_abnormally;

/* Set to nonzero by `grokdeclarator' for a function
   whose return type is defaulted, if warnings for this are desired.  */

ਸਥਿਰ ਪੂਰਨ warn_about_return_type;

/* Nonzero when the current toplevel function contains a declaration
   of a nested function which is never defined.  */

ਸਥਿਰ ਤਾਰਕਿਕ undef_nested_function;

/* Vector of implicit "omp declare target" attributes to be added into
   the attribute lists.  */
vec<c_omp_declare_ਨਿਸ਼ਾਨਾ_attr, va_gc> *current_omp_declare_ਨਿਸ਼ਾਨਾ_attribute;

/* Vector of
   #pragma omp begin assumes ... #pragma omp end assumes regions
   we are in.  */
vec<c_omp_begin_assumes_ਅੰਕੜੇ, va_gc> *current_omp_begin_assumes;

/* Vector of "omp begin/end declare variant" blocks we are in.  */
vec<c_omp_declare_variant_attr, va_gc> *current_omp_declare_variant_attribute;

/* Vector of loop names with C_DECL_LOOP_NAME or C_DECL_SWITCH_NAME marked
   LABEL_DECL as the last and canonical for each loop or switch.  */
ਸਥਿਰ vec<ਰੁੱਖ> loop_ਨਾਂ;

/* Hash table mapping LABEL_DECLs to the canonical LABEL_DECLs if LOOP_NAMES
   vector becomes too long.  */
ਸਥਿਰ decl_ਰੁੱਖ_map *loop_ਨਾਂ_hash;

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

ਬਣਤਰ GTY((chain_ਅਗਲਾ ("%h.prev"))) c_binding {
  ਸੰਘ GTY(()) {		/* first so GTY desc can use decl */
    ਰੁੱਖ GTY((ਟੈਗ ("0"))) type; /* the type in this scope */
    ਬਣਤਰ c_label_vars * GTY((ਟੈਗ ("1"))) label; /* for warnings */
  } GTY((desc ("TREE_CODE (%0.decl) == LABEL_DECL"))) u;
  ਰੁੱਖ decl;			/* the decl bound */
  ਰੁੱਖ id;			/* the identifier it's bound to */
  ਬਣਤਰ c_binding *prev;	/* the previous decl in this scope */
  ਬਣਤਰ c_binding *shadowed;	/* the innermost decl shadowed by this one */
  ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ਡੂੰਘਾਈ : 28;      /* depth of this scope */
  ਤਾਰਕਿਕ invisible : 1;  /* normal lookup should ignore this binding */
  ਤਾਰਕਿਕ nested : 1;     /* do not set DECL_CONTEXT when popping */
  ਤਾਰਕਿਕ inner_comp : 1; /* incomplete array completed in inner scope */
  ਤਾਰਕਿਕ ਵਿੱਚ_struct : 1;	/* currently defined as struct field */
  location_t locus;		/* location for nested bindings */
};
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ B_ਵਿੱਚ_SCOPE(b1, b2) ((b1)->ਡੂੰਘਾਈ == (b2)->ਡੂੰਘਾਈ)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ B_ਵਿੱਚ_CURRENT_SCOPE(b) ((b)->ਡੂੰਘਾਈ == current_scope->ਡੂੰਘਾਈ)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ B_ਵਿੱਚ_FILE_SCOPE(b) ((b)->ਡੂੰਘਾਈ == 1 /*file_scope->depth*/)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ B_ਵਿੱਚ_EXTERNAL_SCOPE(b) ((b)->ਡੂੰਘਾਈ == 0 /*external_scope->depth*/)

/* Each C symbol points to three linked lists of c_binding structures.
   These describe the values of the identifier in the three different
   namespaces defined by the language.  */

ਬਣਤਰ GTY(()) lang_identifier {
  ਬਣਤਰ c_common_identifier common_id;
  ਬਣਤਰ c_binding *ਚਿੰਨ੍ਹ_binding; /* vars, funcs, constants, typedefs */
  ਬਣਤਰ c_binding *ਟੈਗ_binding;    /* struct/union/enum tags */
  ਬਣਤਰ c_binding *label_binding;  /* labels */
};

/* Validate c-lang.cc's assumptions.  */
ਬਾਹਰੀ ਅੱਖਰ C_SIZEOF_STRUCT_LANG_IDENTIFIER_isnt_accurate
[(ਆਕਾਰ(ਬਣਤਰ lang_identifier) == C_SIZEOF_STRUCT_LANG_IDENTIFIER) ? 1 : -1];

/* The binding oracle; see c-tree.h.  */
ਖਾਲੀ (*c_binding_oracle) (ਗਿਣਤੀ c_oracle_request, ਰੁੱਖ identifier);

/* This flag is set on an identifier if we have previously asked the
   binding oracle for this identifier's symbol binding.  */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ I_ਚਿੰਨ੍ਹ_CHECKED(ਗੰਢ) \
  (ਰੁੱਖ_LANG_FLAG_4 (IDENTIFIER_ਗੰਢ_CHECK (ਗੰਢ)))

ਸਥਿਰ ਸਤਰਅੰਦਰ ਬਣਤਰ c_binding* *
i_ਚਿੰਨ੍ਹ_binding (ਰੁੱਖ ਗੰਢ)
{
  ਬਣਤਰ lang_identifier *lid
    = (ਬਣਤਰ lang_identifier *) IDENTIFIER_ਗੰਢ_CHECK (ਗੰਢ);

  ਜੇ (lid->ਚਿੰਨ੍ਹ_binding == ਨਿਰਾ
      && c_binding_oracle != ਨਿਰਾ
      && !I_ਚਿੰਨ੍ਹ_CHECKED (ਗੰਢ))
    {
      /* Set the "checked" flag first, to avoid infinite recursion
	 when the binding oracle calls back into gcc.  */
      I_ਚਿੰਨ੍ਹ_CHECKED (ਗੰਢ) = 1;
      c_binding_oracle (C_ORACLE_ਚਿੰਨ੍ਹ, ਗੰਢ);
    }

  ਵਾਪਸ &lid->ਚਿੰਨ੍ਹ_binding;
}

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ I_ਚਿੰਨ੍ਹ_BINDING(ਗੰਢ) (*i_ਚਿੰਨ੍ਹ_binding (ਗੰਢ))

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ I_ਚਿੰਨ੍ਹ_DECL(ਗੰਢ) \
 (I_ਚਿੰਨ੍ਹ_BINDING(ਗੰਢ) ? I_ਚਿੰਨ੍ਹ_BINDING(ਗੰਢ)->decl : 0)

/* This flag is set on an identifier if we have previously asked the
   binding oracle for this identifier's tag binding.  */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ I_ਟੈਗ_CHECKED(ਗੰਢ) \
  (ਰੁੱਖ_LANG_FLAG_5 (IDENTIFIER_ਗੰਢ_CHECK (ਗੰਢ)))

ਸਥਿਰ ਸਤਰਅੰਦਰ ਬਣਤਰ c_binding **
i_ਟੈਗ_binding (ਰੁੱਖ ਗੰਢ)
{
  ਬਣਤਰ lang_identifier *lid
    = (ਬਣਤਰ lang_identifier *) IDENTIFIER_ਗੰਢ_CHECK (ਗੰਢ);

  ਜੇ (lid->ਟੈਗ_binding == ਨਿਰਾ
      && c_binding_oracle != ਨਿਰਾ
      && !I_ਟੈਗ_CHECKED (ਗੰਢ))
    {
      /* Set the "checked" flag first, to avoid infinite recursion
	 when the binding oracle calls back into gcc.  */
      I_ਟੈਗ_CHECKED (ਗੰਢ) = 1;
      c_binding_oracle (C_ORACLE_ਟੈਗ, ਗੰਢ);
    }

  ਵਾਪਸ &lid->ਟੈਗ_binding;
}

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ I_ਟੈਗ_BINDING(ਗੰਢ) (*i_ਟੈਗ_binding (ਗੰਢ))

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ I_ਟੈਗ_DECL(ਗੰਢ) \
 (I_ਟੈਗ_BINDING(ਗੰਢ) ? I_ਟੈਗ_BINDING(ਗੰਢ)->decl : 0)

/* This flag is set on an identifier if we have previously asked the
   binding oracle for this identifier's label binding.  */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ I_LABEL_CHECKED(ਗੰਢ) \
  (ਰੁੱਖ_LANG_FLAG_6 (IDENTIFIER_ਗੰਢ_CHECK (ਗੰਢ)))

ਸਥਿਰ ਸਤਰਅੰਦਰ ਬਣਤਰ c_binding **
i_label_binding (ਰੁੱਖ ਗੰਢ)
{
  ਬਣਤਰ lang_identifier *lid
    = (ਬਣਤਰ lang_identifier *) IDENTIFIER_ਗੰਢ_CHECK (ਗੰਢ);

  ਜੇ (lid->label_binding == ਨਿਰਾ
      && c_binding_oracle != ਨਿਰਾ
      && !I_LABEL_CHECKED (ਗੰਢ))
    {
      /* Set the "checked" flag first, to avoid infinite recursion
	 when the binding oracle calls back into gcc.  */
      I_LABEL_CHECKED (ਗੰਢ) = 1;
      c_binding_oracle (C_ORACLE_LABEL, ਗੰਢ);
    }

  ਵਾਪਸ &lid->label_binding;
}

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ I_LABEL_BINDING(ਗੰਢ) (*i_label_binding (ਗੰਢ))

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ I_LABEL_DECL(ਗੰਢ) \
 (I_LABEL_BINDING(ਗੰਢ) ? I_LABEL_BINDING(ਗੰਢ)->decl : 0)

/* Used by C_TOKEN_VEC tree.  */
ਬਣਤਰ GTY (()) c_ਰੁੱਖ_token_vec {
  ਬਣਤਰ ਰੁੱਖ_ਅਧਾਰ ਅਧਾਰ;
  vec<c_token, va_gc> *ਟੋਕਨ;
};

STATIC_ASSERT (ਆਕਾਰ (c_ਰੁੱਖ_token_vec) == ਆਕਾਰ (c_ਰੁੱਖ_token_vec_struct));
STATIC_ASSERT (offsetof (c_ਰੁੱਖ_token_vec, ਟੋਕਨ)
	       == offsetof (c_ਰੁੱਖ_token_vec_struct, ਟੋਕਨ));

/* The resulting tree type.  */

ਸੰਘ GTY((desc ("TREE_CODE (&%h.generic) == IDENTIFIER_NODE + 2 * (TREE_CODE (&%h.generic) == C_TOKEN_VEC)"),
       chain_ਅਗਲਾ ("(union lang_tree_node *) c_tree_chain_next (&%h.generic)"))) lang_ਰੁੱਖ_ਗੰਢ
 {
  ਸੰਘ ਰੁੱਖ_ਗੰਢ GTY ((ਟੈਗ ("0"),
			desc ("tree_node_structure (&%h)")))
    generic;
  ਬਣਤਰ lang_identifier GTY ((ਟੈਗ ("1"))) identifier;
  ਬਣਤਰ c_ਰੁੱਖ_token_vec GTY ((ਟੈਗ ("2"))) c_token_vec;
};

/* Langhook for tree_size.  */
ਮਾਪ_t
c_ਰੁੱਖ_ਮਾਪ (ਗਿਣਤੀ ਰੁੱਖ_ਕੋਡ_2 ਕੋਡ)
{
  gcc_checking_assert (ਕੋਡ >= ਅੰਕ_ਰੁੱਖ_CODES);
  ਚੋਣ (ਕੋਡ)
    {
    ਹਾਲਤ C_TOKEN_VEC: ਵਾਪਸ ਆਕਾਰ (c_ਰੁੱਖ_token_vec);
    ਮੂਲ:
      ਚੋਣ (ਰੁੱਖ_ਕੋਡ_CLASS (ਕੋਡ))
	{
	ਹਾਲਤ tcc_declaration: ਵਾਪਸ ਆਕਾਰ (ਰੁੱਖ_decl_non_common);
	ਹਾਲਤ tcc_type: ਵਾਪਸ ਆਕਾਰ (ਰੁੱਖ_type_non_common);
	ਮੂਲ: gcc_unreachable ();
	}
    }
}

/* Track bindings and other things that matter for goto warnings.  For
   efficiency, we do not gather all the decls at the point of
   definition.  Instead, we point into the bindings structure.  As
   scopes are popped, we update these structures and gather the decls
   that matter at that time.  */

ਬਣਤਰ GTY(()) c_spot_bindings {
  /* The currently open scope which holds bindings defined when the
     label was defined or the goto statement was found.  */
  ਬਣਤਰ c_scope *scope;
  /* The bindings in the scope field which were defined at the point
     of the label or goto.  This lets us look at older or newer
     bindings in the scope, as appropriate.  */
  ਬਣਤਰ c_binding *bindings_ਵਿੱਚ_scope;
  /* The number of statement expressions that have started since this
     label or goto statement was defined.  This is zero if we are at
     the same statement expression level.  It is positive if we are in
     a statement expression started since this spot.  It is negative
     if this spot was in a statement expression and we have left
     it.  */
  ਪੂਰਨ stmt_exprs;
  /* Whether we started in a statement expression but are no longer in
     it.  This is set to true if stmt_exprs ever goes negative.  */
  ਤਾਰਕਿਕ ਖੱਬਾ_stmt_ਵਿਅੰਜਕ;
};

/* This structure is used to keep track of bindings seen when a goto
   statement is defined.  This is only used if we see the goto
   statement before we see the label.  */

ਬਣਤਰ GTY(()) c_goto_bindings {
  /* The location of the goto statement.  */
  location_t loc;
  /* The bindings of the goto statement.  */
  ਬਣਤਰ c_spot_bindings goto_bindings;
};

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ c_goto_bindings *c_goto_bindings_p;

/* The additional information we keep track of for a label binding.
   These fields are updated as scopes are popped.  */

ਬਣਤਰ GTY(()) c_label_vars {
  /* The shadowed c_label_vars, when one label shadows another (which
     can only happen using a __label__ declaration).  */
  ਬਣਤਰ c_label_vars *shadowed;
  /* The bindings when the label was defined.  */
  ਬਣਤਰ c_spot_bindings label_bindings;
  /* A list of decls that we care about: decls about which we should
     warn if a goto branches to this label from later in the function.
     Decls are added to this list as scopes are popped.  We only add
     the decls that matter.  */
  vec<ਰੁੱਖ, va_gc> *decls_ਵਿੱਚ_scope;
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


ਬਣਤਰ GTY((chain_ਅਗਲਾ ("%h.outer"))) c_scope {
  /* The scope containing this one.  */
  ਬਣਤਰ c_scope *outer;

  /* The next outermost function scope.  */
  ਬਣਤਰ c_scope *outer_function;

  /* All bindings in this scope.  */
  ਬਣਤਰ c_binding *bindings;

  /* For each scope (except the global one), a chain of BLOCK nodes
     for all the scopes that were entered and exited one level down.  */
  ਰੁੱਖ ਖੰਡਾਂ;
  ਰੁੱਖ ਖੰਡਾਂ_ਆਖਰੀ;

  /* The depth of this scope.  Used to keep the ->shadowed chain of
     bindings sorted innermost to outermost.  */
  ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ਡੂੰਘਾਈ : 28;

  /* True if we are currently filling this scope with parameter
     declarations.  */
  ਤਾਰਕਿਕ parm_flag : 1;

  /* True if we saw [*] in this scope.  Used to give an error messages
     if these appears in a function definition.  */
  ਤਾਰਕਿਕ had_vla_unspec : 1;

  /* True if we parsed a list of forward parameter decls in this scope.  */
  ਤਾਰਕਿਕ had_forward_parm_decls : 1;

  /* True if this is the outermost block scope of a function body.
     This scope contains the parameters, the local variables declared
     in the outermost block, and all the labels (except those in
     nested functions, or declared at block scope with __label__).  */
  ਤਾਰਕਿਕ function_body : 1;

  /* True means make a BLOCK for this scope no matter what.  */
  ਤਾਰਕਿਕ keep : 1;

  /* True means that an unsuffixed float constant is _Decimal64.  */
  ਤਾਰਕਿਕ float_const_decimal64 : 1;

  /* True if this scope has any label bindings.  This is used to speed
     up searching for labels when popping scopes, particularly since
     labels are normally only found at function scope.  */
  ਤਾਰਕਿਕ has_label_bindings : 1;

  /* True if we should issue a warning if a goto statement crosses any
     of the bindings.  We still need to check the list of bindings to
     find the specific ones we need to warn about.  This is true if
     decl_jump_unsafe would return true for any of the bindings.  This
     is used to avoid looping over all the bindings unnecessarily.  */
  ਤਾਰਕਿਕ has_jump_unsafe_decl : 1;
};

/* The scope currently in effect.  */

ਸਥਿਰ GTY(()) ਬਣਤਰ c_scope *current_scope;

/* The innermost function scope.  Ordinary (not explicitly declared)
   labels, bindings to error_mark_node, and the lazily-created
   bindings of __func__ and its friends get this scope.  */

ਸਥਿਰ GTY(()) ਬਣਤਰ c_scope *current_function_scope;

/* The C file scope.  This is reset for each input translation unit.  */

ਸਥਿਰ GTY(()) ਬਣਤਰ c_scope *file_scope;

/* The outermost scope.  This is used for all declarations with
   external linkage, and only these, hence the name.  */

ਸਥਿਰ GTY(()) ਬਣਤਰ c_scope *external_scope;

/* A chain of c_scope structures awaiting reuse.  */

ਸਥਿਰ GTY((deletable)) ਬਣਤਰ c_scope *scope_freelist;

/* A chain of c_binding structures awaiting reuse.  */

ਸਥਿਰ GTY((deletable)) ਬਣਤਰ c_binding *binding_freelist;

/* Append VAR to LIST in scope SCOPE.  */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SCOPE_LIST_APPEND(scope, list, decl) ਕਰੋ {	\
  ਬਣਤਰ c_scope *s_ = (scope);				\
  ਰੁੱਖ d_ = (decl);					\
  ਜੇ (s_->list##_last)					\
    ਖੰਡ_CHAIN (s_->list##_last) = d_;			\
  ਨਹੀਂਤਾਂ							\
    s_->list = d_;					\
  s_->list##_last = d_;					\
} ਜਦੋਂ (0)

/* Concatenate FROM in scope FSCOPE onto TO in scope TSCOPE.  */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SCOPE_LIST_CONCAT(tscope, ਮੰਜ਼ਿਲ, fscope, from) ਕਰੋ {	\
  ਬਣਤਰ c_scope *t_ = (tscope);				\
  ਬਣਤਰ c_scope *f_ = (fscope);				\
  ਜੇ (t_->ਮੰਜ਼ਿਲ##_last)						\
    ਖੰਡ_CHAIN (t_->ਮੰਜ਼ਿਲ##_last) = f_->from;			\
  ਨਹੀਂਤਾਂ								\
    t_->ਮੰਜ਼ਿਲ = f_->from;						\
  t_->ਮੰਜ਼ਿਲ##_last = f_->from##_last;				\
} ਜਦੋਂ (0)

/* A c_inline_static structure stores details of a static identifier
   referenced in a definition of a function that may be an inline
   definition if no subsequent declaration of that function uses
   "extern" or does not use "inline".  */

ਬਣਤਰ GTY((chain_ਅਗਲਾ ("%h.next"))) c_inline_static {
  /* The location for a diagnostic.  */
  location_t location;

  /* The function that may be an inline definition.  */
  ਰੁੱਖ function;

  /* The object or function referenced.  */
  ਰੁੱਖ static_decl;

  /* What sort of reference this is.  */
  ਗਿਣਤੀ c_inline_static_type type;

  /* The next such structure or NULL.  */
  ਬਣਤਰ c_inline_static *ਅਗਲਾ;
};

/* List of static identifiers used or referenced in functions that may
   be inline definitions.  */
ਸਥਿਰ GTY(()) ਬਣਤਰ c_inline_static *c_inline_statics;

/* True means unconditionally make a BLOCK for the next scope pushed.  */

ਸਥਿਰ ਤਾਰਕਿਕ keep_ਅਗਲਾ_level_flag;

/* True means the next call to push_scope will be the outermost scope
   of a function body, so do not push a new scope, merely cease
   expecting parameter decls.  */

ਸਥਿਰ ਤਾਰਕਿਕ ਅਗਲਾ_is_function_body;

/* A vector of pointers to c_binding structures.  */

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ c_binding *c_binding_ptr;

/* Information that we keep for a struct or union while it is being
   parsed.  */

ਵਰਗ c_struct_parse_info
{
ਜਨਤਕ:
  /* If warn_cxx_compat, a list of types defined within this
     struct.  */
  auto_vec<ਰੁੱਖ> struct_types;
  /* If warn_cxx_compat, a list of field names which have bindings,
     and which are defined in this struct, but which are not defined
     in any enclosing struct.  This is used to clear the in_struct
     field of the c_bindings structure.  */
  auto_vec<c_binding_ptr> fields;
  /* If warn_cxx_compat, a list of typedef names used when defining
     fields in this struct.  */
  auto_vec<ਰੁੱਖ> typedefs_ਵੇਖਿਆ;
  /* The location of a previous definition of this struct.  */
  location_t refloc;
};


/* Hash table for structs and unions.  */
ਬਣਤਰ c_struct_hasher : ggc_ptr_hash<ਰੁੱਖ_ਗੰਢ>
{
  ਸਥਿਰ hashval_t hash (ਰੁੱਖ t);
  ਸਥਿਰ ਤਾਰਕਿਕ equal (ਰੁੱਖ, ਰੁੱਖ);
};

/* Hash an RECORD OR UNION.  */
hashval_t
c_struct_hasher::hash (ਰੁੱਖ type)
{
  inchash::hash hstate;

  hstate.ਜੋੜੋ_int (ਰੁੱਖ_ਕੋਡ (type));
  ਰੁੱਖ ਟੈਗ = c_type_ਟੈਗ (type);
  hstate.ਜੋੜੋ_object (ਟੈਗ);

  ਵਾਪਸ hstate.ਸਿਰਾ ();
}

/* Compare two RECORD or UNION types.  */
ਤਾਰਕਿਕ
c_struct_hasher::equal (ਰੁੱਖ t1,  ਰੁੱਖ t2)
{
  ਵਾਪਸ comptypes_equiv_p (t1, t2);
}

/* All tagged typed so that TYPE_CANONICAL can be set correctly.  */
ਸਥਿਰ GTY (()) hash_ਸਾਰਣੀ<c_struct_hasher> *c_struct_htab;

/* Information for the struct or union currently being parsed, or
   NULL if not parsing a struct or union.  */
ਸਥਿਰ ਵਰਗ c_struct_parse_info *struct_parse_info;

/* Forward declarations.  */
ਸਥਿਰ ਰੁੱਖ lookup_name_ਵਿੱਚ_scope (ਰੁੱਖ, ਬਣਤਰ c_scope *);
ਸਥਿਰ ਰੁੱਖ c_make_fname_decl (location_t, ਰੁੱਖ, ਪੂਰਨ);
ਸਥਿਰ ਰੁੱਖ grokdeclarator (ਅਚਲ ਬਣਤਰ c_declarator *,
			    ਬਣਤਰ c_declspecs *,
			    ਗਿਣਤੀ decl_context, ਤਾਰਕਿਕ, ਰੁੱਖ *, ਰੁੱਖ *, ਰੁੱਖ *,
			    ਤਾਰਕਿਕ *, ਗਿਣਤੀ deprecated_ਹਾਲਤਾਂ);
ਸਥਿਰ ਰੁੱਖ grokparms (ਬਣਤਰ c_arg_info *, ਤਾਰਕਿਕ);
ਸਥਿਰ ਖਾਲੀ layout_array_type (ਰੁੱਖ);
ਸਥਿਰ ਅਚਲ ਅੱਖਰ *ਸਿਰਲੇਖ_for_builtin_fn (ਰੁੱਖ);

/* T is a statement.  Add it to the statement-tree.  This is the
   C/ObjC version--C++ has a slightly different version of this
   function.  */

ਰੁੱਖ
ਜੋੜੋ_stmt (ਰੁੱਖ t)
{
  ਗਿਣਤੀ ਰੁੱਖ_ਕੋਡ_2 ਕੋਡ = ਰੁੱਖ_ਕੋਡ (t);

  ਜੇ (CAN_HAVE_LOCATION_P (t) && ਕੋਡ != LABEL_ਵਿਅੰਜਕ)
    {
      ਜੇ (!ਵਿਅੰਜਕ_HAS_LOCATION (t))
	ਸੈੱਟ_ਵਿਅੰਜਕ_LOCATION (t, ਨਿਵੇਸ਼_location);
    }

  /* Add T to the statement-tree.  Non-side-effect statements need to be
     recorded during statement expressions.  */
  ਜੇ (!building_stmt_list_p ())
    ਧੱਕੋ_stmt_list ();

  ਜੇ (ਕੋਡ == LABEL_ਵਿਅੰਜਕ || ਕੋਡ == CASE_LABEL_ਵਿਅੰਜਕ)
    STATEMENT_LIST_HAS_LABEL (cur_stmt_list) = 1;

  append_ਮੰਜ਼ਿਲ_statement_list_force (t, &cur_stmt_list);

  ਵਾਪਸ t;
}





/* Return true if we will want to say something if a goto statement
   crosses DECL.  */

ਸਥਿਰ ਤਾਰਕਿਕ
decl_jump_unsafe (ਰੁੱਖ decl)
{
  ਜੇ (error_ਸੰਕਾਰਜ_p (decl))
    ਵਾਪਸ ਝੂਠ;

  /* Don't warn for compound literals.  If a goto statement crosses
     their initialization, it should cross also all the places where
     the complit is used or where the complit address might be saved
     into some variable, so code after the label to which goto jumps
     should not be able to refer to the compound literal.  */
  ਜੇ (VAR_P (decl) && C_DECL_COMPOUND_LITERAL_P (decl))
    ਵਾਪਸ ਝੂਠ;

  ਜੇ (flag_openmp
      && VAR_P (decl)
      && lookup_attribute ("omp allocate", DECL_ਗੁਣ (decl)))
    ਵਾਪਸ ਸੱਚ;

  /* Always warn about crossing variably modified types.  */
  ਜੇ ((VAR_P (decl) || ਰੁੱਖ_ਕੋਡ (decl) == TYPE_DECL)
      && c_type_variably_modified_p (ਰੁੱਖ_TYPE (decl)))
    ਵਾਪਸ ਸੱਚ;

  /* Otherwise, only warn if -Wgoto-misses-init and this is an
     initialized automatic decl.  */
  ਜੇ (warn_jump_ਖੁੰਝਾਂ_init
      && VAR_P (decl)
      && !ਰੁੱਖ_STATIC (decl)
      && DECL_INITIAL (decl) != NULL_ਰੁੱਖ)
    ਵਾਪਸ ਸੱਚ;

  ਵਾਪਸ ਝੂਠ;
}


ਖਾਲੀ
c_print_identifier (FILE *file, ਰੁੱਖ ਗੰਢ, ਪੂਰਨ indent)
{
  ਖਾਲੀ (*save) (ਗਿਣਤੀ c_oracle_request, ਰੁੱਖ identifier);

  /* Temporarily hide any binding oracle.  Without this, calls to
     debug_tree from the debugger will end up calling into the oracle,
     making for a confusing debug session.  As the oracle isn't needed
     here for normal operation, it's simplest to suppress it.  */
  save = c_binding_oracle;
  c_binding_oracle = ਨਿਰਾ;

  print_ਗੰਢ (file, "symbol", I_ਚਿੰਨ੍ਹ_DECL (ਗੰਢ), indent + 4);
  print_ਗੰਢ (file, "tag", I_ਟੈਗ_DECL (ਗੰਢ), indent + 4);
  print_ਗੰਢ (file, "label", I_LABEL_DECL (ਗੰਢ), indent + 4);
  ਜੇ (C_IS_RESERVED_ਸ਼ਬਦ (ਗੰਢ) && C_RID_ਕੋਡ (ਗੰਢ) != RID_CXX_COMPAT_WARN)
    {
      ਰੁੱਖ rid = ridpointers[C_RID_ਕੋਡ (ਗੰਢ)];
      indent_ਮੰਜ਼ਿਲ (file, indent + 4);
      fprintf (file, "rid " HOST_PTR_PRINTF " \"%s\"",
	       (ਖਾਲੀ *) rid, IDENTIFIER_ਸੂਚਕ (rid));
    }

  c_binding_oracle = save;
}

/* Establish that the scope contains declarations that are sensitive to
   jumps that cross a binding.  Together with decl_jump_unsafe, this is
   used to diagnose such jumps.  */
ਖਾਲੀ
c_mark_decl_jump_unsafe_ਵਿੱਚ_current_scope ()
{
  current_scope->has_jump_unsafe_decl = 1;
}

/* Establish a binding between NAME, an IDENTIFIER_NODE, and DECL,
   which may be any of several kinds of DECL or TYPE or error_mark_node,
   in the scope SCOPE.  */
ਸਥਿਰ ਖਾਲੀ
bind (ਰੁੱਖ name, ਰੁੱਖ decl, ਬਣਤਰ c_scope *scope, ਤਾਰਕਿਕ invisible,
      ਤਾਰਕਿਕ nested, location_t locus)
{
  ਬਣਤਰ c_binding *b, **ਇੱਥੇ;

  ਜੇ (binding_freelist)
    {
      b = binding_freelist;
      binding_freelist = b->prev;
    }
  ਨਹੀਂਤਾਂ
    b = ggc_alloc<c_binding> ();

  b->shadowed = 0;
  b->decl = decl;
  b->id = name;
  b->ਡੂੰਘਾਈ = scope->ਡੂੰਘਾਈ;
  b->invisible = invisible;
  b->nested = nested;
  b->inner_comp = 0;
  b->ਵਿੱਚ_struct = 0;
  b->locus = locus;

  b->u.type = ਨਿਰਾ;

  b->prev = scope->bindings;
  scope->bindings = b;

  ਜੇ (decl_jump_unsafe (decl))
    scope->has_jump_unsafe_decl = 1;

  ਜੇ (!name)
    ਵਾਪਸ;

  ਚੋਣ (ਰੁੱਖ_ਕੋਡ (decl))
    {
    ਹਾਲਤ LABEL_DECL:     ਇੱਥੇ = &I_LABEL_BINDING (name);   ਰੋਕੋ;
    ਹਾਲਤ ENUMERAL_TYPE:
    ਹਾਲਤ UNION_TYPE:
    ਹਾਲਤ ਰਿਕਾਰਡ_TYPE:    ਇੱਥੇ = &I_ਟੈਗ_BINDING (name);     ਰੋਕੋ;
    ਹਾਲਤ VAR_DECL:
    ਹਾਲਤ FUNCTION_DECL:
    ਹਾਲਤ TYPE_DECL:
    ਹਾਲਤ CONST_DECL:
    ਹਾਲਤ PARM_DECL:
    ਹਾਲਤ ERROR_MARK:     ਇੱਥੇ = &I_ਚਿੰਨ੍ਹ_BINDING (name);  ਰੋਕੋ;

    ਮੂਲ:
      gcc_unreachable ();
    }

  /* Locate the appropriate place in the chain of shadowed decls
     to insert this binding.  Normally, scope == current_scope and
     this does nothing.  */
  ਜਦੋਂ (*ਇੱਥੇ && (*ਇੱਥੇ)->ਡੂੰਘਾਈ > scope->ਡੂੰਘਾਈ)
    ਇੱਥੇ = &(*ਇੱਥੇ)->shadowed;

  b->shadowed = *ਇੱਥੇ;
  *ਇੱਥੇ = b;
}

/* Clear the binding structure B, stick it on the binding_freelist,
   and return the former value of b->prev.  This is used by pop_scope
   and get_parm_info to iterate destructively over all the bindings
   from a given scope.  */
ਸਥਿਰ ਬਣਤਰ c_binding *
free_binding_and_advance (ਬਣਤਰ c_binding *b)
{
  ਬਣਤਰ c_binding *prev = b->prev;

  memset (b, 0, ਆਕਾਰ (ਬਣਤਰ c_binding));
  b->prev = binding_freelist;
  binding_freelist = b;

  ਵਾਪਸ prev;
}

/* Bind a label.  Like bind, but skip fields which aren't used for
   labels, and add the LABEL_VARS value.  */
ਸਥਿਰ ਖਾਲੀ
bind_label (ਰੁੱਖ name, ਰੁੱਖ label, ਬਣਤਰ c_scope *scope,
	    ਬਣਤਰ c_label_vars *label_vars)
{
  ਬਣਤਰ c_binding *b;

  bind (name, label, scope, /*invisible=*/ਝੂਠ, /*nested=*/ਝੂਠ,
	UNKNOWN_LOCATION);

  scope->has_label_bindings = ਸੱਚ;

  b = scope->bindings;
  gcc_assert (b->decl == label);
  label_vars->shadowed = b->u.label;
  b->u.label = label_vars;
}

/* Hook called at end of compilation to assume 1 elt
   for a file-scope tentative array defn that wasn't complete before.  */

ਖਾਲੀ
c_ਅੰਤ_incomplete_decl (ਰੁੱਖ decl)
{
  ਜੇ (VAR_P (decl))
    {
      ਰੁੱਖ type = ਰੁੱਖ_TYPE (decl);
      ਜੇ (type != error_mark_ਗੰਢ
	  && ਰੁੱਖ_ਕੋਡ (type) == ARRAY_TYPE
	  && !DECL_EXTERNAL (decl)
	  && TYPE_DOMAIN (type) == NULL_ਰੁੱਖ)
	{
	  ਜੇ (flag_isoc2y && !ਰੁੱਖ_ਜਨਤਕ (decl))
	    error_at (DECL_ਸਰੋਤ_LOCATION (decl),
		      "array size missing in %q+D", decl);
	  ਨਹੀਂਤਾਂ
	    warning_at (DECL_ਸਰੋਤ_LOCATION (decl),
			0, "array %q+D assumed to have one element", decl);

	  complete_array_type (&ਰੁੱਖ_TYPE (decl), NULL_ਰੁੱਖ, ਸੱਚ);

	  relayout_decl (decl);
	}
    }
}

/* Record that inline function FUNC contains a reference (location
   LOC) to static DECL (file-scope or function-local according to
   TYPE).  */

ਖਾਲੀ
ਰਿਕਾਰਡ_inline_static (location_t loc, ਰੁੱਖ func, ਰੁੱਖ decl,
		      ਗਿਣਤੀ c_inline_static_type type)
{
  c_inline_static *csi = ggc_alloc<c_inline_static> ();
  csi->location = loc;
  csi->function = func;
  csi->static_decl = decl;
  csi->type = type;
  csi->ਅਗਲਾ = c_inline_statics;
  c_inline_statics = csi;
}

/* Check for references to static declarations in inline functions at
   the end of the translation unit and diagnose them if the functions
   are still inline definitions.  */

ਸਥਿਰ ਖਾਲੀ
check_inline_statics (ਖਾਲੀ)
{
  ਬਣਤਰ c_inline_static *csi;
  ਲਈ (csi = c_inline_statics; csi; csi = csi->ਅਗਲਾ)
    {
      ਜੇ (DECL_EXTERNAL (csi->function))
	ਚੋਣ (csi->type)
	  {
	  ਹਾਲਤ csi_ਅੰਦਰੂਨੀ:
	    pedwarn (csi->location, 0,
		     "%qD is static but used in inline function %qD "
		     "which is not static", csi->static_decl, csi->function);
	    ਰੋਕੋ;
	  ਹਾਲਤ csi_modifiable:
	    pedwarn (csi->location, 0,
		     "%q+D is static but declared in inline function %qD "
		     "which is not static", csi->static_decl, csi->function);
	    ਰੋਕੋ;
	  ਮੂਲ:
	    gcc_unreachable ();
	  }
    }
  c_inline_statics = ਨਿਰਾ;
}

/* Fill in a c_spot_bindings structure.  If DEFINING is true, set it
   for the current state, otherwise set it to uninitialized.  */

ਸਥਿਰ ਖਾਲੀ
ਸੈੱਟ_spot_bindings (ਬਣਤਰ c_spot_bindings *p, ਤਾਰਕਿਕ defining)
{
  ਜੇ (defining)
    {
      p->scope = current_scope;
      p->bindings_ਵਿੱਚ_scope = current_scope->bindings;
    }
  ਨਹੀਂਤਾਂ
    {
      p->scope = ਨਿਰਾ;
      p->bindings_ਵਿੱਚ_scope = ਨਿਰਾ;
    }
  p->stmt_exprs = 0;
  p->ਖੱਬਾ_stmt_ਵਿਅੰਜਕ = ਝੂਠ;
}

/* Update spot bindings P as we pop out of SCOPE.  Return true if we
   should push decls for a label.  */

ਸਥਿਰ ਤਾਰਕਿਕ
update_spot_bindings (ਬਣਤਰ c_scope *scope, ਬਣਤਰ c_spot_bindings *p)
{
  ਜੇ (p->scope != scope)
    {
      /* This label or goto is defined in some other scope, or it is a
	 label which is not yet defined.  There is nothing to
	 update.  */
      ਵਾਪਸ ਝੂਠ;
    }

  /* Adjust the spot bindings to refer to the bindings already defined
     in the enclosing scope.  */
  p->scope = scope->outer;
  p->bindings_ਵਿੱਚ_scope = p->scope->bindings;

  ਵਾਪਸ ਸੱਚ;
}

/* The Objective-C front-end often needs to determine the current scope.  */

ਖਾਲੀ *
objc_get_current_scope (ਖਾਲੀ)
{
  ਵਾਪਸ current_scope;
}

/* The following function is used only by Objective-C.  It needs to live here
   because it accesses the innards of c_scope.  */

ਖਾਲੀ
objc_mark_locals_volatile (ਖਾਲੀ *enclosing_blk)
{
  ਬਣਤਰ c_scope *scope;
  ਬਣਤਰ c_binding *b;

  ਲਈ (scope = current_scope;
       scope && scope != enclosing_blk;
       scope = scope->outer)
    {
      ਲਈ (b = scope->bindings; b; b = b->prev)
	objc_volatilize_decl (b->decl);

      /* Do not climb up past the current function.  */
      ਜੇ (scope->function_body)
	ਰੋਕੋ;
    }
}

/* Return true if we are in the global binding level.  */

ਤਾਰਕਿਕ
global_bindings_p (ਖਾਲੀ)
{
  ਵਾਪਸ current_scope == file_scope;
}

/* Return true if we're declaring parameters in an old-style function
   declaration.  */

ਤਾਰਕਿਕ
old_style_parameter_scope (ਖਾਲੀ)
{
  /* If processing parameters and there is no function statement list, we
   * have an old-style function declaration.  */
  ਵਾਪਸ (current_scope->parm_flag && !DECL_SAVED_ਰੁੱਖ (current_function_decl));
}

ਖਾਲੀ
keep_ਅਗਲਾ_level (ਖਾਲੀ)
{
  keep_ਅਗਲਾ_level_flag = ਸੱਚ;
}

/* Set the flag for the FLOAT_CONST_DECIMAL64 pragma being ON.  */

ਖਾਲੀ
ਸੈੱਟ_float_const_decimal64 (ਖਾਲੀ)
{
  current_scope->float_const_decimal64 = ਸੱਚ;
}

/* Clear the flag for the FLOAT_CONST_DECIMAL64 pragma.  */

ਖਾਲੀ
clear_float_const_decimal64 (ਖਾਲੀ)
{
  current_scope->float_const_decimal64 = ਝੂਠ;
}

/* Return nonzero if an unsuffixed float constant is _Decimal64.  */

ਤਾਰਕਿਕ
float_const_decimal64_p (ਖਾਲੀ)
{
  ਵਾਪਸ current_scope->float_const_decimal64;
}

/* Identify this scope as currently being filled with parameters.  */

ਖਾਲੀ
declare_parm_level (ਖਾਲੀ)
{
  current_scope->parm_flag = ਸੱਚ;
}

ਖਾਲੀ
ਧੱਕੋ_scope (ਖਾਲੀ)
{
  ਜੇ (ਅਗਲਾ_is_function_body)
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
      current_scope->parm_flag         = ਝੂਠ;
      current_scope->function_body     = ਸੱਚ;
      current_scope->keep              = ਸੱਚ;
      current_scope->outer_function    = current_function_scope;
      current_function_scope           = current_scope;

      keep_ਅਗਲਾ_level_flag = ਝੂਠ;
      ਅਗਲਾ_is_function_body = ਝੂਠ;

      /* The FLOAT_CONST_DECIMAL64 pragma applies to nested scopes.  */
      ਜੇ (current_scope->outer)
	current_scope->float_const_decimal64
	  = current_scope->outer->float_const_decimal64;
      ਨਹੀਂਤਾਂ
	current_scope->float_const_decimal64 = ਝੂਠ;
    }
  ਨਹੀਂਤਾਂ
    {
      ਬਣਤਰ c_scope *scope;
      ਜੇ (scope_freelist)
	{
	  scope = scope_freelist;
	  scope_freelist = scope->outer;
	}
      ਨਹੀਂਤਾਂ
	scope = ggc_cleared_alloc<c_scope> ();

      /* The FLOAT_CONST_DECIMAL64 pragma applies to nested scopes.  */
      ਜੇ (current_scope)
	scope->float_const_decimal64 = current_scope->float_const_decimal64;
      ਨਹੀਂਤਾਂ
	scope->float_const_decimal64 = ਝੂਠ;

      scope->keep          = keep_ਅਗਲਾ_level_flag;
      scope->outer         = current_scope;
      scope->ਡੂੰਘਾਈ	   = current_scope ? (current_scope->ਡੂੰਘਾਈ + 1) : 0;

      /* Check for scope depth overflow.  Unlikely (2^28 == 268,435,456) but
	 possible.  */
      ਜੇ (current_scope && scope->ਡੂੰਘਾਈ == 0)
	{
	  scope->ਡੂੰਘਾਈ--;
	  sorry ("GCC supports only %u nested scopes", scope->ਡੂੰਘਾਈ);
	}

      current_scope        = scope;
      keep_ਅਗਲਾ_level_flag = ਝੂਠ;
    }
}

/* This is called when we are leaving SCOPE.  For each label defined
   in SCOPE, add any appropriate decls to its decls_in_scope fields.
   These are the decls whose initialization will be skipped by a goto
   later in the function.  */

ਸਥਿਰ ਖਾਲੀ
update_label_decls (ਬਣਤਰ c_scope *scope)
{
  ਬਣਤਰ c_scope *s;

  s = scope;
  ਜਦੋਂ (s != ਨਿਰਾ)
    {
      ਜੇ (s->has_label_bindings)
	{
	  ਬਣਤਰ c_binding *b;

	  ਲਈ (b = s->bindings; b != ਨਿਰਾ; b = b->prev)
	    {
	      ਬਣਤਰ c_label_vars *label_vars;
	      ਬਣਤਰ c_binding *b1;
	      ਤਾਰਕਿਕ hjud;
	      ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ix;
	      ਬਣਤਰ c_goto_bindings *g;

	      ਜੇ (ਰੁੱਖ_ਕੋਡ (b->decl) != LABEL_DECL)
		ਜਾਰੀ;
	      label_vars = b->u.label;

	      b1 = label_vars->label_bindings.bindings_ਵਿੱਚ_scope;
	      ਜੇ (label_vars->label_bindings.scope == ਨਿਰਾ)
		hjud = ਝੂਠ;
	      ਨਹੀਂਤਾਂ
		hjud = label_vars->label_bindings.scope->has_jump_unsafe_decl;
	      ਜੇ (update_spot_bindings (scope, &label_vars->label_bindings))
		{
		  /* This label is defined in this scope.  */
		  ਜੇ (hjud)
		    {
		      ਲਈ (; b1 != ਨਿਰਾ; b1 = b1->prev)
			{
			  /* A goto from later in the function to this
			     label will never see the initialization
			     of B1, if any.  Save it to issue a
			     warning if needed.  */
			  ਜੇ (decl_jump_unsafe (b1->decl))
			    vec_ਸੁਰੱਖਿਅਤ_ਧੱਕੋ(label_vars->decls_ਵਿੱਚ_scope, b1->decl);
			}
		    }
		}

	      /* Update the bindings of any goto statements associated
		 with this label.  */
	      FOR_EACH_VEC_ਸੁਰੱਖਿਅਤ_ELT (label_vars->gotos, ix, g)
		update_spot_bindings (scope, &g->goto_bindings);
	    }
	}

      /* Don't search beyond the current function.  */
      ਜੇ (s == current_function_scope)
	ਰੋਕੋ;

      s = s->outer;
    }
}

/* Exit a scope.  Restore the state of the identifier-decl mappings
   that were in effect when this scope was entered.  Return a BLOCK
   node containing all the DECLs in this scope that are of interest
   to debug info generation.  */

ਰੁੱਖ
ਕੱਢੋ_scope (ਖਾਲੀ)
{
  ਬਣਤਰ c_scope *scope = current_scope;
  ਰੁੱਖ ਖੰਡ, context, p;
  ਬਣਤਰ c_binding *b;

  ਤਾਰਕਿਕ functionbody = scope->function_body;
  ਤਾਰਕਿਕ keep = functionbody || scope->keep || scope->bindings;

  update_label_decls (scope);

  /* If appropriate, create a BLOCK to record the decls for the life
     of this function.  */
  ਖੰਡ = NULL_ਰੁੱਖ;
  ਜੇ (keep)
    {
      ਖੰਡ = make_ਗੰਢ (ਖੰਡ_2);
      ਖੰਡ_SUBBLOCKS (ਖੰਡ) = scope->ਖੰਡਾਂ;
      ਰੁੱਖ_ਵਰਤਿਆ (ਖੰਡ) = 1;

      /* In each subblock, record that this is its superior.  */
      ਲਈ (p = scope->ਖੰਡਾਂ; p; p = ਖੰਡ_CHAIN (p))
	ਖੰਡ_SUPERCONTEXT (p) = ਖੰਡ;

      ਖੰਡ_VARS (ਖੰਡ) = NULL_ਰੁੱਖ;
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
  ਜੇ (scope->function_body)
    context = current_function_decl;
  ਨਹੀਂਤਾਂ ਜੇ (scope == file_scope)
    {
      ਰੁੱਖ file_decl
	= build_translation_unit_decl (get_identifier (main_ਨਿਵੇਸ਼_filename));
      context = file_decl;
      debug_hooks->ਰਜਿਸਟਰ_main_translation_unit (file_decl);
    }
  ਨਹੀਂਤਾਂ
    context = ਖੰਡ;

  /* Clear all bindings in this scope.  */
  ਲਈ (b = scope->bindings; b; b = free_binding_and_advance (b))
    {
      p = b->decl;
      ਚੋਣ (ਰੁੱਖ_ਕੋਡ (p))
	{
	ਹਾਲਤ LABEL_DECL:
	  /* Warnings for unused labels, errors for undefined labels.  */
	  ਜੇ (ਰੁੱਖ_ਵਰਤਿਆ (p) && !DECL_INITIAL (p))
	    {
	      error ("label %q+D used but not defined", p);
	      DECL_INITIAL (p) = error_mark_ਗੰਢ;
	    }
	  ਨਹੀਂਤਾਂ
	    warn_for_ਅਣਵਰਤਿਆ_label (p);

	  /* Labels go in BLOCK_VARS.  */
	  DECL_CHAIN (p) = ਖੰਡ_VARS (ਖੰਡ);
	  ਖੰਡ_VARS (ਖੰਡ) = p;
	  gcc_assert (I_LABEL_BINDING (b->id) == b);
	  I_LABEL_BINDING (b->id) = b->shadowed;

	  /* Also pop back to the shadowed label_vars.  */
	  release_ਰੁੱਖ_ਸਦਿਸ਼ (b->u.label->decls_ਵਿੱਚ_scope);
	  b->u.label = b->u.label->shadowed;
	  ਰੋਕੋ;

	ਹਾਲਤ ENUMERAL_TYPE:
	ਹਾਲਤ UNION_TYPE:
	ਹਾਲਤ ਰਿਕਾਰਡ_TYPE:

	  /* Types may not have tag-names, in which case the type
	     appears in the bindings list with b->id NULL.  */
	  ਜੇ (b->id)
	    {
	      gcc_assert (I_ਟੈਗ_BINDING (b->id) == b);
	      I_ਟੈਗ_BINDING (b->id) = b->shadowed;
	    }
	  ਰੋਕੋ;

	ਹਾਲਤ FUNCTION_DECL:
	  /* Propagate TREE_ADDRESSABLE from nested functions to their
	     containing functions.  */
	  ਜੇ (!ਰੁੱਖ_ASM_WRITTEN (p)
	      && DECL_INITIAL (p) != NULL_ਰੁੱਖ
	      && ਰੁੱਖ_ADDRESSABLE (p)
	      && DECL_ABSTRACT_ORIGIN (p) != NULL_ਰੁੱਖ
	      && DECL_ABSTRACT_ORIGIN (p) != p)
	    ਰੁੱਖ_ADDRESSABLE (DECL_ABSTRACT_ORIGIN (p)) = 1;
	  ਜੇ (!ਰੁੱਖ_ਜਨਤਕ (p)
	      && !DECL_INITIAL (p)
	      && !b->nested
	      && scope != file_scope
	      && scope != external_scope)
	    {
	      error ("nested function %q+D declared but never defined", p);
	      undef_nested_function = ਸੱਚ;
	    }
	  ਨਹੀਂਤਾਂ ਜੇ (DECL_DECLARED_INLINE_P (p)
		   && ਰੁੱਖ_ਜਨਤਕ (p)
		   && !DECL_INITIAL (p))
	    {
	      /* C99 6.7.4p6: "a function with external linkage... declared
		 with an inline function specifier ... shall also be defined
		 in the same translation unit."  */
	      ਜੇ (!flag_gnu89_inline
		  && !lookup_attribute ("gnu_inline", DECL_ਗੁਣ (p))
		  && scope == external_scope)
		pedwarn (ਨਿਵੇਸ਼_location, 0,
			 "inline function %q+D declared but never defined", p);
	      DECL_EXTERNAL (p) = 1;
	    }

	  ਜਾਓ common_ਚਿੰਨ੍ਹ;

	ਹਾਲਤ VAR_DECL:
	  /* Warnings for unused variables.  */
	  ਜੇ ((!ਰੁੱਖ_ਵਰਤਿਆ (p) || !DECL_READ_P (p))
	      && !warning_suppressed_p (p, OPT_Wunused_but_ਸੈੱਟ_variable)
	      && !DECL_ਵਿੱਚ_SYSTEM_ਸਿਰਲੇਖ (p)
	      && DECL_NAME (p)
	      && !DECL_ARTIFICIAL (p)
	      && scope != file_scope
	      && scope != external_scope)
	    {
	      ਜੇ (!ਰੁੱਖ_ਵਰਤਿਆ (p))
		{
		  warning (OPT_Wunused_variable, "unused variable %q+D", p);
		  suppress_warning (p, OPT_Wunused_variable);
		}
	      ਨਹੀਂਤਾਂ ਜੇ (DECL_CONTEXT (p) == current_function_decl)
		warning_at (DECL_ਸਰੋਤ_LOCATION (p),
			    OPT_Wunused_but_ਸੈੱਟ_variable,
			    "variable %qD set but not used", p);
	    }

	  ਜੇ (b->inner_comp)
	    {
	      error ("type of array %q+D completed incompatibly with"
		     " implicit initialization", p);
	    }

	  /* Fall through.  */
	ਹਾਲਤ TYPE_DECL:
	ਹਾਲਤ CONST_DECL:
	common_ਚਿੰਨ੍ਹ:
	  /* All of these go in BLOCK_VARS, but only if this is the
	     binding in the home scope.  */
	  ਜੇ (!b->nested)
	    {
	      DECL_CHAIN (p) = ਖੰਡ_VARS (ਖੰਡ);
	      ਖੰਡ_VARS (ਖੰਡ) = p;
	    }
	  ਨਹੀਂਤਾਂ ਜੇ (VAR_OR_FUNCTION_DECL_P (p) && scope != file_scope)
	    {
	      /* For block local externs add a special
		 DECL_EXTERNAL decl for debug info generation.  */
	      ਰੁੱਖ extp = copy_ਗੰਢ (p);

	      DECL_EXTERNAL (extp) = 1;
	      ਰੁੱਖ_STATIC (extp) = 0;
	      ਰੁੱਖ_ਜਨਤਕ (extp) = 1;
	      DECL_INITIAL (extp) = NULL_ਰੁੱਖ;
	      DECL_LANG_SPECIFIC (extp) = ਨਿਰਾ;
	      DECL_CONTEXT (extp) = current_function_decl;
	      ਜੇ (ਰੁੱਖ_ਕੋਡ (p) == FUNCTION_DECL)
		{
		  DECL_ਨਤੀਜਾ (extp) = NULL_ਰੁੱਖ;
		  DECL_SAVED_ਰੁੱਖ (extp) = NULL_ਰੁੱਖ;
		  DECL_STRUCT_FUNCTION (extp) = ਨਿਰਾ;
		}
	      ਜੇ (b->locus != UNKNOWN_LOCATION)
		DECL_ਸਰੋਤ_LOCATION (extp) = b->locus;
	      DECL_CHAIN (extp) = ਖੰਡ_VARS (ਖੰਡ);
	      ਖੰਡ_VARS (ਖੰਡ) = extp;
	    }
	  /* If this is the file scope set DECL_CONTEXT of each decl to
	     the TRANSLATION_UNIT_DECL.  This makes same_translation_unit_p
	     work.  */
	  ਜੇ (scope == file_scope)
	      DECL_CONTEXT (p) = context;

	  gcc_fallthrough ();
	  /* Parameters go in DECL_ARGUMENTS, not BLOCK_VARS, and have
	     already been put there by store_parm_decls.  Unused-
	     parameter warnings are handled by function.cc.
	     error_mark_node obviously does not go in BLOCK_VARS and
	     does not get unused-variable warnings.  */
	ਹਾਲਤ PARM_DECL:
	ਹਾਲਤ ERROR_MARK:
	  /* It is possible for a decl not to have a name.  We get
	     here with b->id NULL in this case.  */
	  ਜੇ (b->id)
	    {
	      gcc_assert (I_ਚਿੰਨ੍ਹ_BINDING (b->id) == b);
	      I_ਚਿੰਨ੍ਹ_BINDING (b->id) = b->shadowed;
	      ਜੇ (b->shadowed && b->shadowed->u.type)
		ਰੁੱਖ_TYPE (b->shadowed->decl) = b->shadowed->u.type;
	    }
	  ਰੋਕੋ;

	ਮੂਲ:
	  gcc_unreachable ();
	}
    }


  /* Dispose of the block that we just made inside some higher level.  */
  ਜੇ ((scope->function_body || scope == file_scope) && context)
    {
      DECL_INITIAL (context) = ਖੰਡ;
      ਖੰਡ_SUPERCONTEXT (ਖੰਡ) = context;
    }
  ਨਹੀਂਤਾਂ ਜੇ (scope->outer)
    {
      ਜੇ (ਖੰਡ)
	SCOPE_LIST_APPEND (scope->outer, ਖੰਡਾਂ, ਖੰਡ);
      /* If we did not make a block for the scope just exited, any
	 blocks made for inner scopes must be carried forward so they
	 will later become subblocks of something else.  */
      ਨਹੀਂਤਾਂ ਜੇ (scope->ਖੰਡਾਂ)
	SCOPE_LIST_CONCAT (scope->outer, ਖੰਡਾਂ, scope, ਖੰਡਾਂ);
    }

  /* Pop the current scope, and free the structure for reuse.  */
  current_scope = scope->outer;
  ਜੇ (scope->function_body)
    current_function_scope = scope->outer_function;

  memset (scope, 0, ਆਕਾਰ (ਬਣਤਰ c_scope));
  scope->outer = scope_freelist;
  scope_freelist = scope;

  ਵਾਪਸ ਖੰਡ;
}

ਖਾਲੀ
ਧੱਕੋ_file_scope (ਖਾਲੀ)
{
  ਰੁੱਖ decl;

  ਜੇ (file_scope)
    ਵਾਪਸ;

  /* Call the target stack_protect_guard hook if the stack protection
     guard is declared as a global symbol.  */
  ਜੇ (targetm.ਢੇਰ_protect_guard_ਚਿੰਨ੍ਹ_p ())
    {
      ਰੁੱਖ decl = targetm.ਢੇਰ_protect_guard ();
      DECL_CHAIN (decl) = visible_builtins;
      visible_builtins = decl;
    }

  ਧੱਕੋ_scope ();
  file_scope = current_scope;

  ਸ਼ੁਰੂ_fname_decls ();

  ਲਈ (decl = visible_builtins; decl; decl = DECL_CHAIN (decl))
    bind (DECL_NAME (decl), decl, file_scope,
	  /*invisible=*/ਝੂਠ, /*nested=*/ਸੱਚ, DECL_ਸਰੋਤ_LOCATION (decl));
}

ਖਾਲੀ
ਕੱਢੋ_file_scope (ਖਾਲੀ)
{
  /* In case there were missing closebraces, get us back to the global
     binding level.  */
  ਜਦੋਂ (current_scope != file_scope)
    ਕੱਢੋ_scope ();

  /* __FUNCTION__ is defined at file scope ("").  This
     call may not be necessary as my tests indicate it
     still works without it.  */
  ਅੰਤ_fname_decls ();

  check_inline_statics ();

  /* This is the point to write out a PCH if we're doing that.
     In that case we do not want to do anything else.  */
  ਜੇ (pch_file)
    {
      c_common_write_pch ();
      /* Ensure even the callers don't try to finalize the CU.  */
      flag_syntax_only = 1;
      ਵਾਪਸ;
    }

  /* Pop off the file scope and close this translation unit.  */
  ਕੱਢੋ_scope ();
  file_scope = 0;

  maybe_apply_pending_pragma_weaks ();
}

/* Whether we are currently inside the initializer for an
   underspecified object definition (C23 auto or constexpr).  */
ਸਥਿਰ ਤਾਰਕਿਕ ਵਿੱਚ_underspecified_init;

/* Start an underspecified object definition for NAME at LOC.  This
   means that NAME is shadowed inside its initializer, so neither the
   definition being initialized, nor any definition from an outer
   scope, may be referenced during that initializer.  Return state to
   be passed to finish_underspecified_init.  If NAME is NULL_TREE, the
   underspecified object is a (constexpr) compound literal; there is
   no shadowing in that case, but all the other restrictions on
   underspecified object definitions still apply.  */
ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ
ਸ਼ੁਰੂ_underspecified_init (location_t loc, ਰੁੱਖ name)
{
  ਤਾਰਕਿਕ prev = ਵਿੱਚ_underspecified_init;
  ਤਾਰਕਿਕ ok;
  ਜੇ (name == NULL_ਰੁੱਖ)
    ok = ਸੱਚ;
  ਨਹੀਂਤਾਂ
    {
      ਰੁੱਖ decl = build_decl (loc, VAR_DECL, name, error_mark_ਗੰਢ);
      C_DECL_UNDERSPECIFIED (decl) = 1;
      ਬਣਤਰ c_scope *scope = current_scope;
      ਬਣਤਰ c_binding *b = I_ਚਿੰਨ੍ਹ_BINDING (name);
      ਜੇ (b && B_ਵਿੱਚ_SCOPE (b, scope))
	{
	  error_at (loc, "underspecified declaration of %qE, which is already "
		    "declared in this scope", name);
	  ok = ਝੂਠ;
	}
      ਨਹੀਂਤਾਂ
	{
	  bind (name, decl, scope, ਝੂਠ, ਝੂਠ, loc);
	  ok = ਸੱਚ;
	}
    }
  ਵਿੱਚ_underspecified_init = ਸੱਚ;
  ਵਾਪਸ ok | (prev << 1);
}

/* Finish an underspecified object definition for NAME, before that
   name is bound to the real declaration instead of a placeholder.
   PREV_STATE is the value returned by the call to
   start_underspecified_init.  If NAME is NULL_TREE, this means a
   compound literal, as for start_underspecified_init.  */
ਖਾਲੀ
ਅੰਤ_underspecified_init (ਰੁੱਖ name, ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ prev_state)
{
  ਜੇ (name != NULL_ਰੁੱਖ && (prev_state & 1))
    {
      /* A VAR_DECL was bound to the name to shadow any previous
	 declarations for the name; remove that binding now.  */
      ਬਣਤਰ c_scope *scope = current_scope;
      ਬਣਤਰ c_binding *b = I_ਚਿੰਨ੍ਹ_BINDING (name);
      gcc_assert (b);
      gcc_assert (B_ਵਿੱਚ_SCOPE (b, scope));
      gcc_assert (VAR_P (b->decl));
      gcc_assert (C_DECL_UNDERSPECIFIED (b->decl));
      I_ਚਿੰਨ੍ਹ_BINDING (name) = b->shadowed;
      /* In erroneous cases there may be other bindings added to this
	 scope during the initializer.  */
      ਬਣਤਰ c_binding **p = &scope->bindings;
      ਜਦੋਂ (*p != b)
	p = &((*p)->prev);
      *p = free_binding_and_advance (*p);
    }
  ਵਿੱਚ_underspecified_init = (prev_state & (1u << 1)) >> 1;
}

/* Adjust the bindings for the start of a statement expression.  */

ਖਾਲੀ
c_bindings_ਸ਼ੁਰੂ_stmt_ਵਿਅੰਜਕ (ਬਣਤਰ c_spot_bindings* switch_bindings)
{
  ਬਣਤਰ c_scope *scope;

  ਲਈ (scope = current_scope; scope != ਨਿਰਾ; scope = scope->outer)
    {
      ਬਣਤਰ c_binding *b;

      ਜੇ (!scope->has_label_bindings)
	ਜਾਰੀ;

      ਲਈ (b = scope->bindings; b != ਨਿਰਾ; b = b->prev)
	{
	  ਬਣਤਰ c_label_vars *label_vars;
	  ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ix;
	  ਬਣਤਰ c_goto_bindings *g;

	  ਜੇ (ਰੁੱਖ_ਕੋਡ (b->decl) != LABEL_DECL)
	    ਜਾਰੀ;
	  label_vars = b->u.label;
	  ++label_vars->label_bindings.stmt_exprs;
	  FOR_EACH_VEC_ਸੁਰੱਖਿਅਤ_ELT (label_vars->gotos, ix, g)
	    ++g->goto_bindings.stmt_exprs;
	}
    }

  ਜੇ (switch_bindings != ਨਿਰਾ)
    ++switch_bindings->stmt_exprs;
}

/* Adjust the bindings for the end of a statement expression.  */

ਖਾਲੀ
c_bindings_ਸਿਰਾ_stmt_ਵਿਅੰਜਕ (ਬਣਤਰ c_spot_bindings *switch_bindings)
{
  ਬਣਤਰ c_scope *scope;

  ਲਈ (scope = current_scope; scope != ਨਿਰਾ; scope = scope->outer)
    {
      ਬਣਤਰ c_binding *b;

      ਜੇ (!scope->has_label_bindings)
	ਜਾਰੀ;

      ਲਈ (b = scope->bindings; b != ਨਿਰਾ; b = b->prev)
	{
	  ਬਣਤਰ c_label_vars *label_vars;
	  ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ix;
	  ਬਣਤਰ c_goto_bindings *g;

	  ਜੇ (ਰੁੱਖ_ਕੋਡ (b->decl) != LABEL_DECL)
	    ਜਾਰੀ;
	  label_vars = b->u.label;
	  --label_vars->label_bindings.stmt_exprs;
	  ਜੇ (label_vars->label_bindings.stmt_exprs < 0)
	    {
	      label_vars->label_bindings.ਖੱਬਾ_stmt_ਵਿਅੰਜਕ = ਸੱਚ;
	      label_vars->label_bindings.stmt_exprs = 0;
	    }
	  FOR_EACH_VEC_ਸੁਰੱਖਿਅਤ_ELT (label_vars->gotos, ix, g)
	    {
	      --g->goto_bindings.stmt_exprs;
	      ਜੇ (g->goto_bindings.stmt_exprs < 0)
		{
		  g->goto_bindings.ਖੱਬਾ_stmt_ਵਿਅੰਜਕ = ਸੱਚ;
		  g->goto_bindings.stmt_exprs = 0;
		}
	    }
	}
    }

  ਜੇ (switch_bindings != ਨਿਰਾ)
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

ਸਥਿਰ ਖਾਲੀ
pushtag (location_t loc, ਰੁੱਖ name, ਰੁੱਖ type)
{
  /* Record the identifier as the type's name if it has none.  */
  ਜੇ (name && !TYPE_NAME (type))
    TYPE_NAME (type) = name;
  bind (name, type, current_scope, /*invisible=*/ਝੂਠ, /*nested=*/ਝੂਠ, loc);

  /* Create a fake NULL-named TYPE_DECL node whose TREE_TYPE will be the
     tagged type we just added to the current scope.  This fake
     NULL-named TYPE_DECL node helps dwarfout.c to know when it needs
     to output a representation of a tagged type, and it also gives
     us a convenient place to record the "scope start" address for the
     tagged type, and it is used to track whether the type is used
     in a non-local context via mark_decl_used.  */

  TYPE_STUB_DECL (type) = pushdecl (build_decl (loc,
						TYPE_DECL, NULL_ਰੁੱਖ, type));

  /* An approximation for now, so we can tell this is a function-scope tag.
     This will be updated in pop_scope.  */
  TYPE_CONTEXT (type) = DECL_CONTEXT (TYPE_STUB_DECL (type));

  ਜੇ (warn_cxx_compat && name != NULL_ਰੁੱਖ)
    {
      ਬਣਤਰ c_binding *b = I_ਚਿੰਨ੍ਹ_BINDING (name);

      ਜੇ (b != ਨਿਰਾ
	  && b->decl != NULL_ਰੁੱਖ
	  && ਰੁੱਖ_ਕੋਡ (b->decl) == TYPE_DECL
	  && (B_ਵਿੱਚ_CURRENT_SCOPE (b)
	      || (current_scope == file_scope && B_ਵਿੱਚ_EXTERNAL_SCOPE (b)))
	  && (TYPE_MAIN_VARIANT (ਰੁੱਖ_TYPE (b->decl))
	      != TYPE_MAIN_VARIANT (type)))
	{
	  auto_diagnostic_ਸਮੂਹ d;
	  ਜੇ (warning_at (loc, OPT_Wc___compat,
			  "using %qD as both a typedef and a tag is "
			  "invalid in C++", b->decl)
	      && b->locus != UNKNOWN_LOCATION)
	    inform (b->locus, "originally defined here");
	}
    }
}

/* An exported interface to pushtag.  This is used by the gdb plugin's
   binding oracle to introduce a new tag binding.  */

ਖਾਲੀ
c_pushtag (location_t loc, ਰੁੱਖ name, ਰੁੱਖ type)
{
  pushtag (loc, name, type);
}

/* An exported interface to bind a declaration.  LOC is the location
   to use.  DECL is the declaration to bind.  The decl's name is used
   to determine how it is bound.  If DECL is a VAR_DECL, then
   IS_GLOBAL determines whether the decl is put into the global (file
   and external) scope or the current function's scope; if DECL is not
   a VAR_DECL then it is always put into the file scope.  */

ਖਾਲੀ
c_bind (location_t loc, ਰੁੱਖ decl, ਤਾਰਕਿਕ is_global)
{
  ਬਣਤਰ c_scope *scope;
  ਤਾਰਕਿਕ nested = ਝੂਠ;

  ਜੇ (!VAR_P (decl) || current_function_scope == ਨਿਰਾ)
    {
      /* Types and functions are always considered to be global.  */
      scope = file_scope;
      DECL_EXTERNAL (decl) = 1;
      ਰੁੱਖ_ਜਨਤਕ (decl) = 1;
    }
  ਨਹੀਂਤਾਂ ਜੇ (is_global)
    {
      /* Also bind it into the external scope.  */
      bind (DECL_NAME (decl), decl, external_scope, ਸੱਚ, ਝੂਠ, loc);
      nested = ਸੱਚ;
      scope = file_scope;
      DECL_EXTERNAL (decl) = 1;
      ਰੁੱਖ_ਜਨਤਕ (decl) = 1;
    }
  ਨਹੀਂਤਾਂ
    {
      DECL_CONTEXT (decl) = current_function_decl;
      ਰੁੱਖ_ਜਨਤਕ (decl) = 0;
      scope = current_function_scope;
    }

  bind (DECL_NAME (decl), decl, scope, ਝੂਠ, nested, loc);
}


/* Stores the first FILE*, const struct tm* etc. argument type (whatever
   it is) seen in a declaration of a file I/O etc. built-in, corresponding
   to the builtin_structptr_types array.  Subsequent declarations of such
   built-ins are expected to refer to it rather than to fileptr_type_node,
   etc. which is just void* (or to any other type).
   Used only by match_builtin_function_types.  */

ਸਥਿਰ ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ builtin_structptr_type_ਗਿਣਤੀ
  = ARRAY_ਮਾਪ (builtin_structptr_types);

ਸਥਿਰ GTY(()) ਰੁੱਖ ਆਖਰੀ_structptr_types[builtin_structptr_type_ਗਿਣਤੀ];

/* Returns true if types T1 and T2 representing return types or types
   of function arguments are close enough to be considered interchangeable
   in redeclarations of built-in functions.  */

ਸਥਿਰ ਤਾਰਕਿਕ
types_close_enough_ਮੰਜ਼ਿਲ_ਮੇਲ (ਰੁੱਖ t1, ਰੁੱਖ t2)
{
  ਵਾਪਸ (TYPE_ਬਹੁਲਕ (t1) == TYPE_ਬਹੁਲਕ (t2)
	  && ਸੂਚਕ_TYPE_P (t1) == ਸੂਚਕ_TYPE_P (t2)
	  && FUNCTION_ਸੂਚਕ_TYPE_P (t1) == FUNCTION_ਸੂਚਕ_TYPE_P (t2));
}

/* Subroutine of compare_decls.  Allow harmless mismatches in return
   and argument types provided that the type modes match.  Set *STRICT
   and *ARGNO to the expected argument type and number in case of
   an argument type mismatch or null and zero otherwise.  Return
   a unified type given a suitable match, and 0 otherwise.  */

ਸਥਿਰ ਰੁੱਖ
ਮੇਲ_builtin_function_types (ਰੁੱਖ newtype, ਰੁੱਖ oldtype,
			      ਰੁੱਖ *strict, ਬਿਨਾਨਿਸ਼ਾਨੀ *argno)
{
  *argno = 0;
  *strict = NULL_ਰੁੱਖ;

  /* Accept the return type of the new declaration if it has the same
     mode and if they're both pointers or if neither is.  */
  ਰੁੱਖ oldrettype = ਰੁੱਖ_TYPE (oldtype);
  ਰੁੱਖ newrettype = ਰੁੱਖ_TYPE (newtype);

  ਜੇ (!types_close_enough_ਮੰਜ਼ਿਲ_ਮੇਲ (oldrettype, newrettype))
    ਵਾਪਸ NULL_ਰੁੱਖ;

  /* Check that the return types are compatible but don't fail if they
     are not (e.g., int vs long in ILP32) and just let the caller know.  */
  ਜੇ (!comptypes (TYPE_MAIN_VARIANT (oldrettype),
		  TYPE_MAIN_VARIANT (newrettype)))
    *strict = oldrettype;

  ਰੁੱਖ oldargs = TYPE_ARG_TYPES (oldtype);
  ਰੁੱਖ newargs = TYPE_ARG_TYPES (newtype);
  ਰੁੱਖ tryargs = newargs;

  ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ nlst = ARRAY_ਮਾਪ (ਆਖਰੀ_structptr_types);
  ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ nbst = ARRAY_ਮਾਪ (builtin_structptr_types);

  gcc_checking_assert (nlst == nbst);

  ਲਈ (ਬਿਨਾਨਿਸ਼ਾਨੀ i = 1; oldargs || newargs; ++i)
    {
      ਜੇ (!oldargs
	  || !newargs
	  || !ਰੁੱਖ_ਮੁੱਲ (oldargs)
	  || !ਰੁੱਖ_ਮੁੱਲ (newargs))
	ਵਾਪਸ NULL_ਰੁੱਖ;

      ਰੁੱਖ oldtype = TYPE_MAIN_VARIANT (ਰੁੱਖ_ਮੁੱਲ (oldargs));
      ਰੁੱਖ newtype = ਰੁੱਖ_ਮੁੱਲ (newargs);
      ਜੇ (newtype == error_mark_ਗੰਢ)
       ਵਾਪਸ NULL_ਰੁੱਖ;
      newtype = TYPE_MAIN_VARIANT (newtype);

      ਜੇ (!types_close_enough_ਮੰਜ਼ਿਲ_ਮੇਲ (oldtype, newtype))
	ਵਾਪਸ NULL_ਰੁੱਖ;

      ਬਿਨਾਨਿਸ਼ਾਨੀ j = nbst;
      ਜੇ (ਸੂਚਕ_TYPE_P (oldtype))
	/* Iterate over well-known struct types like FILE (whose types
	   aren't known to us) and compare the pointer to each to
	   the pointer argument.  */
	ਲਈ (j = 0; j < nbst; ++j)
	  {
	    ਜੇ (ਰੁੱਖ_ਮੁੱਲ (oldargs) != builtin_structptr_types[j].ਗੰਢ)
	      ਜਾਰੀ;
	    /* Store the first FILE* etc. argument type (whatever it is), and
	       expect any subsequent declarations of file I/O etc. built-ins
	       to refer to it rather than to fileptr_type_node etc. which is
	       just void* (or const void*).  */
	    ਜੇ (ਆਖਰੀ_structptr_types[j])
	      {
		ਜੇ (!comptypes (ਆਖਰੀ_structptr_types[j], newtype))
		  {
		    *argno = i;
		    *strict = ਆਖਰੀ_structptr_types[j];
		  }
	      }
	    ਨਹੀਂਤਾਂ
	      ਆਖਰੀ_structptr_types[j] = newtype;
	    ਰੋਕੋ;
	  }

      ਜੇ (j == nbst && !comptypes (oldtype, newtype))
	{
	  ਜੇ (ਸੂਚਕ_TYPE_P (oldtype))
	    {
	      /* For incompatible pointers, only reject differences in
		 the unqualified variants of the referenced types but
		 consider differences in qualifiers as benign (report
		 those to caller via *STRICT below).  */
	      ਰੁੱਖ oldref = TYPE_MAIN_VARIANT (ਰੁੱਖ_TYPE (oldtype));
	      ਰੁੱਖ newref = TYPE_MAIN_VARIANT (ਰੁੱਖ_TYPE (newtype));
	      ਜੇ (!comptypes (oldref, newref))
		ਵਾਪਸ NULL_ਰੁੱਖ;
	    }

	  ਜੇ (!*strict)
	    {
	      *argno = i;
	      *strict = oldtype;
	    }
	}

      oldargs = ਰੁੱਖ_CHAIN (oldargs);
      newargs = ਰੁੱਖ_CHAIN (newargs);
    }

  ਰੁੱਖ trytype = c_build_function_type (newrettype, tryargs);

  /* Allow declaration to change transaction_safe attribute.  */
  ਰੁੱਖ oldattrs = TYPE_ਗੁਣ (oldtype);
  ਰੁੱਖ oldtsafe = lookup_attribute ("transaction_safe", oldattrs);
  ਰੁੱਖ newattrs = TYPE_ਗੁਣ (newtype);
  ਰੁੱਖ newtsafe = lookup_attribute ("transaction_safe", newattrs);
  ਜੇ (oldtsafe && !newtsafe)
    oldattrs = remove_attribute ("transaction_safe", oldattrs);
  ਨਹੀਂਤਾਂ ਜੇ (newtsafe && !oldtsafe)
    oldattrs = ਰੁੱਖ_cons (get_identifier ("transaction_safe"),
			  NULL_ਰੁੱਖ, oldattrs);

  ਵਾਪਸ c_build_type_attribute_variant (trytype, oldattrs);
}

/* Subroutine of diagnose_mismatched_decls.  Check for function type
   mismatch involving an empty arglist vs a nonempty one and give clearer
   diagnostics.  */
ਸਥਿਰ ਖਾਲੀ
diagnose_arglist_conflict (ਰੁੱਖ newdecl, ਰੁੱਖ olddecl,
			   ਰੁੱਖ newtype, ਰੁੱਖ oldtype)
{
  ਰੁੱਖ t;

  ਜੇ (ਰੁੱਖ_ਕੋਡ (olddecl) != FUNCTION_DECL
      || !comptypes (ਰੁੱਖ_TYPE (oldtype), ਰੁੱਖ_TYPE (newtype))
      || !((!prototype_p (oldtype) && DECL_INITIAL (olddecl) == NULL_ਰੁੱਖ)
	   || (!prototype_p (newtype) && DECL_INITIAL (newdecl) == NULL_ਰੁੱਖ)))
    ਵਾਪਸ;

  t = TYPE_ARG_TYPES (oldtype);
  ਜੇ (t == NULL_ਰੁੱਖ)
    t = TYPE_ARG_TYPES (newtype);
  ਲਈ (; t; t = ਰੁੱਖ_CHAIN (t))
    {
      ਰੁੱਖ type = ਰੁੱਖ_ਮੁੱਲ (t);

      ਜੇ (ਰੁੱਖ_CHAIN (t) == NULL_ਰੁੱਖ
	  && TYPE_MAIN_VARIANT (type) != void_type_ਗੰਢ)
	{
	  inform (ਨਿਵੇਸ਼_location, "a parameter list with an ellipsis "
		  "cannot match an empty parameter name list declaration");
	  ਰੋਕੋ;
	}

      ਜੇ (!error_ਸੰਕਾਰਜ_p (type)
	  && c_type_promotes_ਮੰਜ਼ਿਲ (type) != type)
	{
	  inform (ਨਿਵੇਸ਼_location, "an argument type that has a default "
		  "promotion cannot match an empty parameter name list "
		  "declaration");
	  ਰੋਕੋ;
	}
    }
}

/* Another subroutine of diagnose_mismatched_decls.  OLDDECL is an
   old-style function definition, NEWDECL is a prototype declaration.
   Diagnose inconsistencies in the argument list.  Returns TRUE if
   the prototype is compatible, FALSE if not.  */
ਸਥਿਰ ਤਾਰਕਿਕ
validate_proto_after_old_defn (ਰੁੱਖ newdecl, ਰੁੱਖ newtype, ਰੁੱਖ oldtype)
{
  ਰੁੱਖ newargs, oldargs;
  ਪੂਰਨ i;

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਸਿਰਾ_ਦਾ_ARGLIST(t) ((t) == void_type_ਗੰਢ)

  oldargs = TYPE_ACTUAL_ARG_TYPES (oldtype);
  newargs = TYPE_ARG_TYPES (newtype);
  i = 1;

  ਲਈ (;;)
    {
      ਰੁੱਖ oldargtype = ਰੁੱਖ_ਮੁੱਲ (oldargs);
      ਰੁੱਖ newargtype = ਰੁੱਖ_ਮੁੱਲ (newargs);

      ਜੇ (oldargtype == error_mark_ਗੰਢ || newargtype == error_mark_ਗੰਢ)
	ਵਾਪਸ ਝੂਠ;

      oldargtype = (TYPE_ATOMIC (oldargtype)
		    ? c_build_qualified_type (TYPE_MAIN_VARIANT (oldargtype),
					      TYPE_QUAL_ATOMIC)
		    : TYPE_MAIN_VARIANT (oldargtype));
      newargtype = (TYPE_ATOMIC (newargtype)
		    ? c_build_qualified_type (TYPE_MAIN_VARIANT (newargtype),
					      TYPE_QUAL_ATOMIC)
		    : TYPE_MAIN_VARIANT (newargtype));

      ਜੇ (ਸਿਰਾ_ਦਾ_ARGLIST (oldargtype) && ਸਿਰਾ_ਦਾ_ARGLIST (newargtype))
	ਰੋਕੋ;

      /* Reaching the end of just one list means the two decls don't
	 agree on the number of arguments.  */
      ਜੇ (ਸਿਰਾ_ਦਾ_ARGLIST (oldargtype))
	{
	  error ("prototype for %q+D declares more arguments "
		 "than previous old-style definition", newdecl);
	  ਵਾਪਸ ਝੂਠ;
	}
      ਨਹੀਂਤਾਂ ਜੇ (ਸਿਰਾ_ਦਾ_ARGLIST (newargtype))
	{
	  error ("prototype for %q+D declares fewer arguments "
		 "than previous old-style definition", newdecl);
	  ਵਾਪਸ ਝੂਠ;
	}

      /* Type for passing arg must be consistent with that declared
	 for the arg.  */
      ਨਹੀਂਤਾਂ ਜੇ (!comptypes (oldargtype, newargtype))
	{
	  error ("prototype for %q+D declares argument %d"
		 " with incompatible type",
		 newdecl, i);
	  ਵਾਪਸ ਝੂਠ;
	}

      oldargs = ਰੁੱਖ_CHAIN (oldargs);
      newargs = ਰੁੱਖ_CHAIN (newargs);
      i++;
    }

  /* If we get here, no errors were found, but do issue a warning
     for this poor-style construct.  */
  warning (0, "prototype for %q+D follows non-prototype definition",
	   newdecl);
  ਵਾਪਸ ਸੱਚ;
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ ਸਿਰਾ_ਦਾ_ARGLIST
}

/* Subroutine of diagnose_mismatched_decls.  Report the location of DECL,
   first in a pair of mismatched declarations, using the diagnostic
   function DIAG.  */
ਸਥਿਰ ਖਾਲੀ
locate_old_decl (ਰੁੱਖ decl)
{
  ਜੇ (ਰੁੱਖ_ਕੋਡ (decl) == FUNCTION_DECL
      && fndecl_built_ਵਿੱਚ_p (decl)
      && !C_DECL_DECLARED_BUILTIN (decl))
    ;
  ਨਹੀਂਤਾਂ ਜੇ (DECL_INITIAL (decl))
    inform (ਨਿਵੇਸ਼_location,
	    "previous definition of %q+D with type %qT",
	    decl, ਰੁੱਖ_TYPE (decl));
  ਨਹੀਂਤਾਂ ਜੇ (C_DECL_IMPLICIT (decl))
    inform (ਨਿਵੇਸ਼_location,
	    "previous implicit declaration of %q+D with type %qT",
	    decl, ਰੁੱਖ_TYPE (decl));
  ਨਹੀਂਤਾਂ
    inform (ਨਿਵੇਸ਼_location,
	    "previous declaration of %q+D with type %qT",
	    decl, ਰੁੱਖ_TYPE (decl));
}


/* Helper function.  For a tagged type, it finds the declaration
   for a visible tag declared in the same scope if such a
   declaration exists.  */
ਸਥਿਰ ਰੁੱਖ
ਪਿਛਲਾ_ਟੈਗ (ਰੁੱਖ type)
{
  ਬਣਤਰ c_binding *b = ਨਿਰਾ;
  ਰੁੱਖ name = c_type_ਟੈਗ (type);

  ਜੇ (name)
    b = I_ਟੈਗ_BINDING (name);

  ਜੇ (b)
    b = b->shadowed;

  ਜੇ (b && B_ਵਿੱਚ_CURRENT_SCOPE (b))
    ਵਾਪਸ b->decl;

  ਵਾਪਸ NULL_ਰੁੱਖ;
}

/* Subroutine to mark functions as versioned when using the attribute
   'target_version'.  */

ਸਥਿਰ ਖਾਲੀ
maybe_mark_function_versioned (ਰੁੱਖ decl)
{
  ਜੇ (!DECL_FUNCTION_VERSIONED (decl))
    {
      /* Check if the name of the function has been overridden.  */
      ਜੇ (DECL_ASSEMBLER_NAME_ਸੈੱਟ_P (decl)
	  && IDENTIFIER_ਸੂਚਕ (DECL_ASSEMBLER_NAME (decl))[0] == '*')
	error_at (DECL_ਸਰੋਤ_LOCATION (decl),
		  "cannot use function multiversioning on a renamed function");

      /* We need to insert function version now to make sure the correct
	 pre-mangled assembler name is recorded.  */
      cgraph_ਗੰਢ *ਗੰਢ = cgraph_ਗੰਢ::get_create (decl);

      ਜੇ (!ਗੰਢ->function_ਸੰਸਕਰਣ ())
	ਗੰਢ->ਪਾਓ_new_function_ਸੰਸਕਰਣ ();

      DECL_FUNCTION_VERSIONED (decl) = 1;

      ਰੁੱਖ mangled_name
	= targetm.mangle_decl_assembler_name (decl, DECL_NAME (decl));
      ਸੈੱਟ_DECL_ASSEMBLER_NAME (decl, mangled_name);
    }
}

/* Subroutine of duplicate_decls.  Compare NEWDECL to OLDDECL.
   Returns true if the caller should proceed to merge the two, false
   if OLDDECL should simply be discarded.  As a side effect, issues
   all necessary diagnostics for invalid or poor-style combinations.
   If it returns true, writes the types of NEWDECL and OLDDECL to
   *NEWTYPEP and *OLDTYPEP - these may have been adjusted from
   TREE_TYPE (NEWDECL, OLDDECL) respectively.  */

ਸਥਿਰ ਤਾਰਕਿਕ
diagnose_mismatched_decls (ਰੁੱਖ newdecl, ਰੁੱਖ olddecl,
			   ਰੁੱਖ *newtypep, ਰੁੱਖ *oldtypep)
{
  ਰੁੱਖ newtype, oldtype;
  ਤਾਰਕਿਕ retval = ਸੱਚ;

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DECL_EXTERN_INLINE(DECL) (DECL_DECLARED_INLINE_P (DECL)  \
				  && DECL_EXTERNAL (DECL))

  /* If we have error_mark_node for either decl or type, just discard
     the previous decl - we're in an error cascade already.  */
  ਜੇ (olddecl == error_mark_ਗੰਢ || newdecl == error_mark_ਗੰਢ)
    ਵਾਪਸ ਝੂਠ;
  *oldtypep = oldtype = ਰੁੱਖ_TYPE (olddecl);
  *newtypep = newtype = ਰੁੱਖ_TYPE (newdecl);
  ਜੇ (oldtype == error_mark_ਗੰਢ || newtype == error_mark_ਗੰਢ)
    ਵਾਪਸ ਝੂਠ;

  /* Two different categories of symbol altogether.  This is an error
     unless OLDDECL is a builtin.  OLDDECL will be discarded in any case.  */
  ਜੇ (ਰੁੱਖ_ਕੋਡ (olddecl) != ਰੁੱਖ_ਕੋਡ (newdecl))
    {
      ਜੇ (!(ਰੁੱਖ_ਕੋਡ (olddecl) == FUNCTION_DECL
	    && fndecl_built_ਵਿੱਚ_p (olddecl)
	    && !C_DECL_DECLARED_BUILTIN (olddecl)))
	{
	  auto_diagnostic_ਸਮੂਹ d;
	  error ("%q+D redeclared as different kind of symbol", newdecl);
	  locate_old_decl (olddecl);
	}
      ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਜਨਤਕ (newdecl))
	warning (OPT_Wbuiltin_declaration_mismatch,
		 "built-in function %q+D declared as non-function",
		 newdecl);
      ਨਹੀਂਤਾਂ
	warning (OPT_Wshadow, "declaration of %q+D shadows "
		 "a built-in function", newdecl);
      ਵਾਪਸ ਝੂਠ;
    }

  /* Enumerators have no linkage, so may only be declared once in a
     given scope.  */
  ਜੇ (ਰੁੱਖ_ਕੋਡ (olddecl) == CONST_DECL)
    {
      ਜੇ (flag_isoc23
	  && TYPE_NAME (DECL_CONTEXT (newdecl))
	  && DECL_CONTEXT (newdecl) != DECL_CONTEXT (olddecl)
	  && TYPE_NAME (DECL_CONTEXT (newdecl)) == TYPE_NAME (DECL_CONTEXT (olddecl)))
	{
	  ਜੇ (!simple_cst_equal (DECL_INITIAL (olddecl), DECL_INITIAL (newdecl)))
	    {
	      auto_diagnostic_ਸਮੂਹ d;
	      error ("conflicting redeclaration of enumerator %q+D", newdecl);
	      locate_old_decl (olddecl);
	    }
	}
      ਨਹੀਂਤਾਂ
	{
	  auto_diagnostic_ਸਮੂਹ d;
	  error ("redeclaration of enumerator %q+D", newdecl);
	  locate_old_decl (olddecl);
	}
      ਵਾਪਸ ਝੂਠ;
    }

  ਤਾਰਕਿਕ pedwarned = ਝੂਠ;
  ਤਾਰਕਿਕ warned = ਝੂਠ;
  ਤਾਰਕਿਕ enum_and_int_p = ਝੂਠ;
  auto_diagnostic_ਸਮੂਹ d;

  ਤਾਰਕਿਕ comptypes_ਨਤੀਜਾ = comptypes_check_enum_int (oldtype, newtype,
						    &enum_and_int_p);
  ਜੇ (!comptypes_ਨਤੀਜਾ)
    {
      ਜੇ (ਰੁੱਖ_ਕੋਡ (olddecl) == FUNCTION_DECL
	  && fndecl_built_ਵਿੱਚ_p (olddecl, BUILT_ਵਿੱਚ_ਸਾਧਾਰਨ)
	  && !C_DECL_DECLARED_BUILTIN (olddecl))
	{
	  /* Accept "harmless" mismatches in function types such
	     as missing qualifiers or int vs long when they're the same
	     size.  However, diagnose return and argument types that are
	     incompatible according to language rules.  */
	  ਰੁੱਖ mismatch_expect;
	  ਬਿਨਾਨਿਸ਼ਾਨੀ mismatch_argno;

	  ਰੁੱਖ trytype = ਮੇਲ_builtin_function_types (newtype, oldtype,
						       &mismatch_expect,
						       &mismatch_argno);

	  ਜੇ (trytype && comptypes (newtype, trytype))
	    *oldtypep = oldtype = trytype;
	  ਨਹੀਂਤਾਂ
	    {
	      /* If types don't match for a built-in, throw away the
		 built-in.  No point in calling locate_old_decl here, it
		 won't print anything.  */
	      ਅਚਲ ਅੱਖਰ *ਸਿਰਲੇਖ = ਸਿਰਲੇਖ_for_builtin_fn (olddecl);
	      location_t loc = DECL_ਸਰੋਤ_LOCATION (newdecl);
	      ਜੇ (warning_at (loc, OPT_Wbuiltin_declaration_mismatch,
			      "conflicting types for built-in function %q+D; "
			      "expected %qT",
			      newdecl, oldtype)
		  && ਸਿਰਲੇਖ)
		{
		  /* Suggest the right header to include as the preferred
		     solution rather than the spelling of the declaration.  */
		  rich_location richloc (ਸਤਰ_ਸਾਰਣੀ, loc);
		  maybe_ਜੋੜੋ_include_fixit (&richloc, ਸਿਰਲੇਖ, ਸੱਚ);
		  inform (&richloc,
			  "%qD is declared in header %qs", olddecl, ਸਿਰਲੇਖ);
		}
	      ਵਾਪਸ ਝੂਠ;
	    }

	  ਜੇ (mismatch_expect && extra_warnings)
	    {
	      location_t newloc = DECL_ਸਰੋਤ_LOCATION (newdecl);
	      ਤਾਰਕਿਕ warned = ਝੂਠ;
	      ਜੇ (mismatch_argno)
		warned = warning_at (newloc, OPT_Wbuiltin_declaration_mismatch,
				     "mismatch in argument %u type of built-in "
				     "function %qD; expected %qT",
				     mismatch_argno, newdecl, mismatch_expect);
	      ਨਹੀਂਤਾਂ
		warned = warning_at (newloc, OPT_Wbuiltin_declaration_mismatch,
				     "mismatch in return type of built-in "
				     "function %qD; expected %qT",
				     newdecl, mismatch_expect);
	      ਅਚਲ ਅੱਖਰ *ਸਿਰਲੇਖ = ਸਿਰਲੇਖ_for_builtin_fn (olddecl);
	      ਜੇ (warned && ਸਿਰਲੇਖ)
		{
		  rich_location richloc (ਸਤਰ_ਸਾਰਣੀ, newloc);
		  maybe_ਜੋੜੋ_include_fixit (&richloc, ਸਿਰਲੇਖ, ਸੱਚ);
		  inform (&richloc,
			  "%qD is declared in header %qs", olddecl, ਸਿਰਲੇਖ);
		}
	    }
	}
      ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਕੋਡ (olddecl) == FUNCTION_DECL
	       && DECL_IS_UNDECLARED_BUILTIN (olddecl))
	{
	  /* A conflicting function declaration for a predeclared
	     function that isn't actually built in.  Objective C uses
	     these.  The new declaration silently overrides everything
	     but the volatility (i.e. noreturn) indication.  See also
	     below.  FIXME: Make Objective C use normal builtins.  */
	  ਰੁੱਖ_THIS_VOLATILE (newdecl) |= ਰੁੱਖ_THIS_VOLATILE (olddecl);
	  ਵਾਪਸ ਝੂਠ;
	}
      /* Permit void foo (...) to match int foo (...) if the latter is
	 the definition and implicit int was used.  See
	 c-torture/compile/920625-2.c.  */
      ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਕੋਡ (newdecl) == FUNCTION_DECL && DECL_INITIAL (newdecl)
	       && TYPE_MAIN_VARIANT (ਰੁੱਖ_TYPE (oldtype)) == void_type_ਗੰਢ
	       && TYPE_MAIN_VARIANT (ਰੁੱਖ_TYPE (newtype)) == integer_type_ਗੰਢ
	       && C_FUNCTION_IMPLICIT_INT (newdecl) && !DECL_INITIAL (olddecl))
	{
	  pedwarned = pedwarn (ਨਿਵੇਸ਼_location, 0,
			       "conflicting types for %q+D", newdecl);
	  /* Make sure we keep void as the return type.  */
	  ਰੁੱਖ_TYPE (newdecl) = *newtypep = newtype = oldtype;
	  C_FUNCTION_IMPLICIT_INT (newdecl) = 0;
	}
      /* Permit void foo (...) to match an earlier call to foo (...) with
	 no declared type (thus, implicitly int).  */
      ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਕੋਡ (newdecl) == FUNCTION_DECL
	       && TYPE_MAIN_VARIANT (ਰੁੱਖ_TYPE (newtype)) == void_type_ਗੰਢ
	       && TYPE_MAIN_VARIANT (ਰੁੱਖ_TYPE (oldtype)) == integer_type_ਗੰਢ
	       && C_DECL_IMPLICIT (olddecl) && !DECL_INITIAL (olddecl))
	{
	  pedwarned = pedwarn (ਨਿਵੇਸ਼_location, 0,
			       "conflicting types for %q+D; have %qT",
			       newdecl, newtype);
	  /* Make sure we keep void as the return type.  */
	  ਰੁੱਖ_TYPE (olddecl) = *oldtypep = oldtype = newtype;
	}
      ਨਹੀਂਤਾਂ
	{
	  ਪੂਰਨ new_quals = TYPE_QUALS (newtype);
	  ਪੂਰਨ old_quals = TYPE_QUALS (oldtype);

	  ਜੇ (new_quals != old_quals)
	    {
	      addr_space_t new_addr = DECODE_QUAL_ADDR_SPACE (new_quals);
	      addr_space_t old_addr = DECODE_QUAL_ADDR_SPACE (old_quals);
	      ਜੇ (new_addr != old_addr)
		{
		  ਜੇ (ADDR_SPACE_GENERIC_P (new_addr))
		    error ("conflicting named address spaces (generic vs %s) "
			   "for %q+D",
			   c_addr_space_name (old_addr), newdecl);
		  ਨਹੀਂਤਾਂ ਜੇ (ADDR_SPACE_GENERIC_P (old_addr))
		    error ("conflicting named address spaces (%s vs generic) "
			   "for %q+D",
			   c_addr_space_name (new_addr), newdecl);
		  ਨਹੀਂਤਾਂ
		    error ("conflicting named address spaces (%s vs %s) "
			   "for %q+D",
			   c_addr_space_name (new_addr),
			   c_addr_space_name (old_addr),
			   newdecl);
		}

	      ਜੇ (CLEAR_QUAL_ADDR_SPACE (new_quals)
		  != CLEAR_QUAL_ADDR_SPACE (old_quals))
		error ("conflicting type qualifiers for %q+D", newdecl);
	    }
	  ਨਹੀਂਤਾਂ
	    {
	      ਜੇ (ਰੁੱਖ_ਕੋਡ (olddecl) == FUNCTION_DECL)
		{
		  ਰੁੱਖ attrs = TYPE_ਗੁਣ (ਰੁੱਖ_TYPE (olddecl));
		  ਜੇ (attrs && !TYPE_ਗੁਣ (ਰੁੱਖ_TYPE (newdecl)))
		    {
		      /* Similar to the C++ front-end, for FUNCTION_DECL,
			 if OLDDECL has attributes and NEWDECL doesn't,
			 try the type with OLDDECL attributes.  */
		      ਰੁੱਖ rettype = ਰੁੱਖ_TYPE (newtype);
		      ਰੁੱਖ tryargs = TYPE_ARG_TYPES (newtype);
		      ਰੁੱਖ trytype = c_build_function_type (rettype,
							    tryargs);
		      trytype = c_build_type_attribute_variant (trytype,
								attrs);
		      ਜੇ (comptypes (oldtype, trytype))
			{
			  *newtypep = newtype = trytype;
			  comptypes_ਨਤੀਜਾ = ਸੱਚ;
			}
		    }
		}

	      ਜੇ (!comptypes_ਨਤੀਜਾ)
		error ("conflicting types for %q+D; have %qT", newdecl,
		       newtype);
	    }
	  ਜੇ (!comptypes_ਨਤੀਜਾ)
	    {
	      diagnose_arglist_conflict (newdecl, olddecl, newtype,
					 oldtype);
	      locate_old_decl (olddecl);
	      ਵਾਪਸ ਝੂਠ;
	    }
	}
    }
  /* Warn about enum/integer type mismatches.  They are compatible types
     (C23 6.7.2.2/5), but may pose portability problems.  */
  ਨਹੀਂਤਾਂ ਜੇ (enum_and_int_p
	   && ਰੁੱਖ_ਕੋਡ (newdecl) != TYPE_DECL
	   /* Don't warn about acc_on_device built-in redeclaration,
	      the built-in is declared with int rather than enum because
	      the enum isn't intrinsic.  */
	   && !(ਰੁੱਖ_ਕੋਡ (olddecl) == FUNCTION_DECL
		&& fndecl_built_ਵਿੱਚ_p (olddecl, BUILT_ਵਿੱਚ_ACC_ON_DEVICE)
		&& !C_DECL_DECLARED_BUILTIN (olddecl)))
    warned = warning_at (DECL_ਸਰੋਤ_LOCATION (newdecl),
			 OPT_Wenum_int_mismatch,
			 "conflicting types for %q+D due to enum/integer "
			 "mismatch; have %qT", newdecl, newtype);

  /* Redeclaration of a type is a constraint violation (6.7.2.3p1),
     but silently ignore the redeclaration if either is in a system
     header.  (Conflicting redeclarations were handled above.)  This
     is allowed for C11 if the types are the same, not just
     compatible.  */
  ਜੇ (ਰੁੱਖ_ਕੋਡ (newdecl) == TYPE_DECL)
    {
      ਜੇ (!comptypes_same_p (oldtype, newtype))
	{
	  error ("redefinition of typedef %q+D with different type", newdecl);
	  locate_old_decl (olddecl);
	  ਵਾਪਸ ਝੂਠ;
	}

      ਜੇ (DECL_ਵਿੱਚ_SYSTEM_ਸਿਰਲੇਖ (newdecl)
	  || DECL_ਵਿੱਚ_SYSTEM_ਸਿਰਲੇਖ (olddecl)
	  || warning_suppressed_p (newdecl, OPT_Wpedantic)
	  || warning_suppressed_p (olddecl, OPT_Wpedantic))
	ਵਾਪਸ ਸੱਚ;  /* Allow OLDDECL to continue in use.  */

      ਜੇ (c_type_variably_modified_p (newtype))
	{
	  error ("redefinition of typedef %q+D with variably modified type",
		 newdecl);
	  locate_old_decl (olddecl);
	}
      ਨਹੀਂਤਾਂ ਜੇ (pedwarn_c99 (ਨਿਵੇਸ਼_location, OPT_Wpedantic,
			    "redefinition of typedef %q+D", newdecl))
	locate_old_decl (olddecl);

      ਵਾਪਸ ਸੱਚ;
    }

  /* Function declarations can either be 'static' or 'extern' (no
     qualifier is equivalent to 'extern' - C99 6.2.2p5) and therefore
     can never conflict with each other on account of linkage
     (6.2.2p4).  Multiple definitions are not allowed (6.9p3,5) but
     gnu89 mode permits two definitions if one is 'extern inline' and
     one is not.  The non- extern-inline definition supersedes the
     extern-inline definition.  */

  ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਕੋਡ (newdecl) == FUNCTION_DECL)
    {
      /* If you declare a built-in function name as static, or
	 define the built-in with an old-style definition (so we
	 can't validate the argument list) the built-in definition is
	 overridden, but optionally warn this was a bad choice of name.  */
      ਜੇ (fndecl_built_ਵਿੱਚ_p (olddecl)
	  && !C_DECL_DECLARED_BUILTIN (olddecl))
	{
	  ਜੇ (!ਰੁੱਖ_ਜਨਤਕ (newdecl)
	      || (DECL_INITIAL (newdecl)
		  && !prototype_p (ਰੁੱਖ_TYPE (newdecl))))
	    {
	      warning_at (DECL_ਸਰੋਤ_LOCATION (newdecl),
			  OPT_Wshadow, "declaration of %qD shadows "
			  "a built-in function", newdecl);
	      /* Discard the old built-in function.  */
	      ਵਾਪਸ ਝੂਠ;
	    }

	  ਜੇ (!prototype_p (ਰੁੱਖ_TYPE (newdecl)))
	    {
	      /* Set for built-ins that take no arguments.  */
	      ਤਾਰਕਿਕ func_void_ਦਲੀਲਾਂ = ਝੂਠ;
	      ਜੇ (ਰੁੱਖ at = TYPE_ARG_TYPES (oldtype))
		func_void_ਦਲੀਲਾਂ = VOID_TYPE_P (ਰੁੱਖ_ਮੁੱਲ (at));

	      ਜੇ (extra_warnings && !func_void_ਦਲੀਲਾਂ)
		warning_at (DECL_ਸਰੋਤ_LOCATION (newdecl),
			    OPT_Wbuiltin_declaration_mismatch,
			    "declaration of built-in function %qD without "
			    "a prototype; expected %qT",
			    newdecl, ਰੁੱਖ_TYPE (olddecl));
	    }
	}

      ਜੇ (DECL_INITIAL (newdecl))
	{
	  ਜੇ (DECL_INITIAL (olddecl))
	    {
	      /* If the new declaration isn't overriding an extern inline
		 reject the new decl. In c99, no overriding is allowed
		 in the same translation unit.  */
	      ਜੇ (!DECL_EXTERN_INLINE (olddecl)
		  || DECL_EXTERN_INLINE (newdecl)
		  || (!flag_gnu89_inline
		      && (!DECL_DECLARED_INLINE_P (olddecl)
			  || !lookup_attribute ("gnu_inline",
						DECL_ਗੁਣ (olddecl)))
		      && (!DECL_DECLARED_INLINE_P (newdecl)
			  || !lookup_attribute ("gnu_inline",
						DECL_ਗੁਣ (newdecl)))))
		{
		  auto_diagnostic_ਸਮੂਹ d;
		  error ("redefinition of %q+D", newdecl);
		  locate_old_decl (olddecl);
		  ਵਾਪਸ ਝੂਠ;
		}
	    }
	}
      /* If we have a prototype after an old-style function definition,
	 the argument types must be checked specially.  */
      ਨਹੀਂਤਾਂ ਜੇ (DECL_INITIAL (olddecl)
	       && !prototype_p (oldtype) && prototype_p (newtype)
	       && TYPE_ACTUAL_ARG_TYPES (oldtype))
	{
	  auto_diagnostic_ਸਮੂਹ d;
	  ਜੇ (!validate_proto_after_old_defn (newdecl, newtype, oldtype))
	    {
	      locate_old_decl (olddecl);
	      ਵਾਪਸ ਝੂਠ;
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
      ਜੇ (ਰੁੱਖ_ਜਨਤਕ (olddecl) && !ਰੁੱਖ_ਜਨਤਕ (newdecl))
	{
	  /* Two exceptions to the rule.  If olddecl is an extern
	     inline, or a predeclared function that isn't actually
	     built in, newdecl silently overrides olddecl.  The latter
	     occur only in Objective C; see also above.  (FIXME: Make
	     Objective C use normal builtins.)  */
	  ਜੇ (!DECL_IS_UNDECLARED_BUILTIN (olddecl)
	      && !DECL_EXTERN_INLINE (olddecl))
	    {
	      auto_diagnostic_ਸਮੂਹ d;
	      error ("static declaration of %q+D follows "
		     "non-static declaration", newdecl);
	      locate_old_decl (olddecl);
	    }
	  ਵਾਪਸ ਝੂਠ;
	}
      ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਜਨਤਕ (newdecl) && !ਰੁੱਖ_ਜਨਤਕ (olddecl))
	{
	  ਜੇ (DECL_CONTEXT (olddecl))
	    {
	      auto_diagnostic_ਸਮੂਹ d;
	      error ("non-static declaration of %q+D follows "
		     "static declaration", newdecl);
	      locate_old_decl (olddecl);
	      ਵਾਪਸ ਝੂਠ;
	    }
	  ਨਹੀਂਤਾਂ ਜੇ (warn_traditional)
	    {
	      warned |= warning (OPT_Wtraditional,
				 "non-static declaration of %q+D "
				 "follows static declaration", newdecl);
	    }
	}

      /* Make sure gnu_inline attribute is either not present, or
	 present on all inline decls.  */
      ਜੇ (DECL_DECLARED_INLINE_P (olddecl)
	  && DECL_DECLARED_INLINE_P (newdecl))
	{
	  ਤਾਰਕਿਕ newa = lookup_attribute ("gnu_inline",
					DECL_ਗੁਣ (newdecl)) != ਨਿਰਾ;
	  ਤਾਰਕਿਕ olda = lookup_attribute ("gnu_inline",
					DECL_ਗੁਣ (olddecl)) != ਨਿਰਾ;
	  ਜੇ (newa != olda)
	    {
	      auto_diagnostic_ਸਮੂਹ d;
	      error_at (ਨਿਵੇਸ਼_location, "%<gnu_inline%> attribute present on %q+D",
			newa ? newdecl : olddecl);
	      error_at (DECL_ਸਰੋਤ_LOCATION (newa ? olddecl : newdecl),
			"but not here");
	    }
	}
      /* Check if these are unmergeable overlapping FMV declarations.  */
      ਜੇ (!ਨਿਸ਼ਾਨਾ_HAS_FMV_ਨਿਸ਼ਾਨਾ_ATTRIBUTE
	  && diagnose_versioned_decls (olddecl, newdecl))
	ਵਾਪਸ ਝੂਠ;
    }
  ਨਹੀਂਤਾਂ ਜੇ (VAR_P (newdecl))
    {
      /* Only variables can be thread-local, and all declarations must
	 agree on this property.  */
      ਜੇ (C_DECL_THREADPRIVATE_P (olddecl) && !DECL_THREAD_LOCAL_P (newdecl))
	{
	  /* Nothing to check.  Since OLDDECL is marked threadprivate
	     and NEWDECL does not have a thread-local attribute, we
	     will merge the threadprivate attribute into NEWDECL.  */
	  ;
	}
      ਨਹੀਂਤਾਂ ਜੇ (DECL_THREAD_LOCAL_P (newdecl) != DECL_THREAD_LOCAL_P (olddecl))
	{
	  auto_diagnostic_ਸਮੂਹ d;
	  ਜੇ (DECL_THREAD_LOCAL_P (newdecl))
	    error ("thread-local declaration of %q+D follows "
		   "non-thread-local declaration", newdecl);
	  ਨਹੀਂਤਾਂ
	    error ("non-thread-local declaration of %q+D follows "
		   "thread-local declaration", newdecl);

	  locate_old_decl (olddecl);
	  ਵਾਪਸ ਝੂਠ;
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
      ਜੇ ((DECL_INITIAL (newdecl) && DECL_INITIAL (olddecl))
	  || (flag_isoc23
	      && DECL_THREAD_LOCAL_P (newdecl)
	      && !DECL_EXTERNAL (newdecl)
	      && !DECL_EXTERNAL (olddecl)))
	{
	  auto_diagnostic_ਸਮੂਹ d;
	  error ("redefinition of %q+D", newdecl);
	  locate_old_decl (olddecl);
	  ਵਾਪਸ ਝੂਠ;
	}

      /* Objects declared at file scope: if the first declaration had
	 external linkage (even if it was an external reference) the
	 second must have external linkage as well, or the behavior is
	 undefined.  If the first declaration had internal linkage, then
	 the second must too, or else be an external reference (in which
	 case the composite declaration still has internal linkage).
	 As for function declarations, we warn about the static-then-
	 extern case only for -Wtraditional.  See generally 6.2.2p3-5,7.  */
      ਜੇ (DECL_FILE_SCOPE_P (newdecl)
	  && ਰੁੱਖ_ਜਨਤਕ (newdecl) != ਰੁੱਖ_ਜਨਤਕ (olddecl))
	{
	  ਜੇ (DECL_EXTERNAL (newdecl))
	    {
	      ਜੇ (!DECL_FILE_SCOPE_P (olddecl))
		{
		  auto_diagnostic_ਸਮੂਹ d;
		  error ("extern declaration of %q+D follows "
			 "declaration with no linkage", newdecl);
		  locate_old_decl (olddecl);
		  ਵਾਪਸ ਝੂਠ;
		}
	      ਨਹੀਂਤਾਂ ਜੇ (warn_traditional)
		{
		  warned |= warning (OPT_Wtraditional,
				     "non-static declaration of %q+D "
				     "follows static declaration", newdecl);
		}
	    }
	  ਨਹੀਂਤਾਂ
	    {
	      auto_diagnostic_ਸਮੂਹ d;
	      ਜੇ (ਰੁੱਖ_ਜਨਤਕ (newdecl))
		error ("non-static declaration of %q+D follows "
		       "static declaration", newdecl);
	      ਨਹੀਂਤਾਂ
		error ("static declaration of %q+D follows "
		       "non-static declaration", newdecl);

	      locate_old_decl (olddecl);
	      ਵਾਪਸ ਝੂਠ;
	    }
	}
      /* Two objects with the same name declared at the same block
	 scope must both be external references (6.7p3).  */
      ਨਹੀਂਤਾਂ ਜੇ (!DECL_FILE_SCOPE_P (newdecl))
	{
	  ਜੇ (DECL_EXTERNAL (newdecl))
	    {
	      /* Extern with initializer at block scope, which will
		 already have received an error.  */
	    }
	  ਨਹੀਂਤਾਂ ਜੇ (DECL_EXTERNAL (olddecl))
	    {
	      auto_diagnostic_ਸਮੂਹ d;
	      error ("declaration of %q+D with no linkage follows "
		     "extern declaration", newdecl);
	      locate_old_decl (olddecl);
	    }
	  ਨਹੀਂਤਾਂ
	    {
	      auto_diagnostic_ਸਮੂਹ d;
	      error ("redeclaration of %q+D with no linkage", newdecl);
	      locate_old_decl (olddecl);
	    }

	  ਵਾਪਸ ਝੂਠ;
	}

      /* C++ does not permit a decl to appear multiple times at file
	 scope.  */
      ਜੇ (warn_cxx_compat
	  && DECL_FILE_SCOPE_P (newdecl)
	  && !DECL_EXTERNAL (newdecl)
	  && !DECL_EXTERNAL (olddecl))
	warned |= warning_at (DECL_ਸਰੋਤ_LOCATION (newdecl),
			      OPT_Wc___compat,
			      "duplicate declaration of %qD is "
			      "invalid in C++", newdecl);
    }

  /* warnings */
  /* All decls must agree on a visibility.  */
  ਜੇ (ਕੋਡ_ਸ਼ਾਮਲ_ਹੈ_STRUCT (ਰੁੱਖ_ਕੋਡ (newdecl), TS_DECL_WITH_VIS)
      && DECL_VISIBILITY_SPECIFIED (newdecl) && DECL_VISIBILITY_SPECIFIED (olddecl)
      && DECL_VISIBILITY (newdecl) != DECL_VISIBILITY (olddecl))
    {
      warned |= warning (0, "redeclaration of %q+D with different visibility "
			 "(old visibility preserved)", newdecl);
    }

  ਜੇ (ਰੁੱਖ_ਕੋਡ (newdecl) == FUNCTION_DECL)
    warned |= diagnose_mismatched_ਗੁਣ (olddecl, newdecl);
  ਨਹੀਂਤਾਂ /* PARM_DECL, VAR_DECL */
    {
      /* Redeclaration of a parameter is a constraint violation (this is
	 not explicitly stated, but follows from C99 6.7p3 [no more than
	 one declaration of the same identifier with no linkage in the
	 same scope, except type tags] and 6.2.2p6 [parameters have no
	 linkage]).  We must check for a forward parameter declaration,
	 indicated by TREE_ASM_WRITTEN on the old declaration - this is
	 an extension, the mandatory diagnostic for which is handled by
	 mark_forward_parm_decls.  */

      ਜੇ (ਰੁੱਖ_ਕੋਡ (newdecl) == PARM_DECL
	  && (!ਰੁੱਖ_ASM_WRITTEN (olddecl) || ਰੁੱਖ_ASM_WRITTEN (newdecl)))
	{
	  auto_diagnostic_ਸਮੂਹ d;
	  error ("redefinition of parameter %q+D", newdecl);
	  locate_old_decl (olddecl);
	  ਵਾਪਸ ਝੂਠ;
	}
    }

  /* Optional warning for completely redundant decls.  */
  ਜੇ (!warned && !pedwarned
      && warn_redundant_decls
      /* Don't warn about a function declaration followed by a
	 definition.  */
      && !(ਰੁੱਖ_ਕੋਡ (newdecl) == FUNCTION_DECL
	   && DECL_INITIAL (newdecl) && !DECL_INITIAL (olddecl))
      /* Don't warn about redundant redeclarations of builtins.  */
      && !(ਰੁੱਖ_ਕੋਡ (newdecl) == FUNCTION_DECL
	   && !fndecl_built_ਵਿੱਚ_p (newdecl)
	   && fndecl_built_ਵਿੱਚ_p (olddecl)
	   && !C_DECL_DECLARED_BUILTIN (olddecl))
      /* Don't warn about an extern followed by a definition.  */
      && !(DECL_EXTERNAL (olddecl) && !DECL_EXTERNAL (newdecl))
      /* Don't warn about forward parameter decls.  */
      && !(ਰੁੱਖ_ਕੋਡ (newdecl) == PARM_DECL
	   && ਰੁੱਖ_ASM_WRITTEN (olddecl) && !ਰੁੱਖ_ASM_WRITTEN (newdecl))
      /* Don't warn about a variable definition following a declaration.  */
      && !(VAR_P (newdecl)
	   && DECL_INITIAL (newdecl) && !DECL_INITIAL (olddecl)))
    {
      warned = warning (OPT_Wredundant_decls, "redundant redeclaration of %q+D",
			newdecl);
    }

  /* Report location of previous decl/defn.  */
  ਜੇ (warned || pedwarned)
    locate_old_decl (olddecl);

#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ DECL_EXTERN_INLINE

  ਵਾਪਸ retval;
}

/* Subroutine of duplicate_decls.  NEWDECL has been found to be
   consistent with OLDDECL, but carries new information.  Merge the
   new information into OLDDECL.  This function issues no
   diagnostics.  */

ਸਥਿਰ ਖਾਲੀ
ਮਿਲਾਓ_decls (ਰੁੱਖ newdecl, ਰੁੱਖ olddecl, ਰੁੱਖ newtype, ਰੁੱਖ oldtype)
{
  ਤਾਰਕਿਕ new_is_definition = (ਰੁੱਖ_ਕੋਡ (newdecl) == FUNCTION_DECL
			    && DECL_INITIAL (newdecl) != NULL_ਰੁੱਖ);
  ਤਾਰਕਿਕ new_is_prototype = (ਰੁੱਖ_ਕੋਡ (newdecl) == FUNCTION_DECL
			   && prototype_p (ਰੁੱਖ_TYPE (newdecl)));
  ਤਾਰਕਿਕ old_is_prototype = (ਰੁੱਖ_ਕੋਡ (olddecl) == FUNCTION_DECL
			   && prototype_p (ਰੁੱਖ_TYPE (olddecl)));

  /* For real parm decl following a forward decl, rechain the old decl
     in its new location and clear TREE_ASM_WRITTEN (it's not a
     forward decl anymore).  */
  ਜੇ (ਰੁੱਖ_ਕੋਡ (newdecl) == PARM_DECL
      && ਰੁੱਖ_ASM_WRITTEN (olddecl) && !ਰੁੱਖ_ASM_WRITTEN (newdecl))
    {
      ਬਣਤਰ c_binding *b, **ਇੱਥੇ;

      ਲਈ (ਇੱਥੇ = &current_scope->bindings; *ਇੱਥੇ; ਇੱਥੇ = &(*ਇੱਥੇ)->prev)
	ਜੇ ((*ਇੱਥੇ)->decl == olddecl)
	  ਜਾਓ ਮਿਲਿਆ;
      gcc_unreachable ();

    ਮਿਲਿਆ:
      b = *ਇੱਥੇ;
      *ਇੱਥੇ = b->prev;
      b->prev = current_scope->bindings;
      current_scope->bindings = b;

      ਰੁੱਖ_ASM_WRITTEN (olddecl) = 0;
    }

  DECL_ਗੁਣ (newdecl)
    = targetm.ਮਿਲਾਓ_decl_ਗੁਣ (olddecl, newdecl);

  /* For typedefs use the old type, as the new type's DECL_NAME points
     at newdecl, which will be ggc_freed.  */
  ਜੇ (ਰੁੱਖ_ਕੋਡ (newdecl) == TYPE_DECL)
    {
      /* But NEWTYPE might have an attribute, honor that.  */
      ਰੁੱਖ tem = newtype;
      newtype = oldtype;

      ਜੇ (TYPE_USER_ALIGN (tem))
	{
	  ਜੇ (TYPE_ALIGN (tem) > TYPE_ALIGN (newtype))
	    ਸੈੱਟ_TYPE_ALIGN (newtype, TYPE_ALIGN (tem));
	  TYPE_USER_ALIGN (newtype) = ਸੱਚ;
	}

      /* And remove the new type from the variants list.  */
      ਜੇ (TYPE_NAME (ਰੁੱਖ_TYPE (newdecl)) == newdecl)
	{
	  ਰੁੱਖ remove = ਰੁੱਖ_TYPE (newdecl);
	  ਜੇ (TYPE_MAIN_VARIANT (remove) == remove)
	    {
	      gcc_assert (TYPE_ਅਗਲਾ_VARIANT (remove) == NULL_ਰੁੱਖ);
	      /* If remove is the main variant, no need to remove that
		 from the list.  One of the DECL_ORIGINAL_TYPE
		 variants, e.g. created for aligned attribute, might still
		 refer to the newdecl TYPE_DECL though, so remove that one
		 in that case.  */
	      ਜੇ (DECL_ORIGINAL_TYPE (newdecl)
		  && DECL_ORIGINAL_TYPE (newdecl) != remove)
		ਲਈ (ਰੁੱਖ t = TYPE_MAIN_VARIANT (DECL_ORIGINAL_TYPE (newdecl));
		     t; t = TYPE_MAIN_VARIANT (t))
		  ਜੇ (TYPE_NAME (TYPE_ਅਗਲਾ_VARIANT (t)) == newdecl)
		    {
		      TYPE_ਅਗਲਾ_VARIANT (t)
			= TYPE_ਅਗਲਾ_VARIANT (TYPE_ਅਗਲਾ_VARIANT (t));
		      ਰੋਕੋ;
		    }
	    }
	  ਨਹੀਂਤਾਂ
	    ਲਈ (ਰੁੱਖ t = TYPE_MAIN_VARIANT (remove); ;
		 t = TYPE_ਅਗਲਾ_VARIANT (t))
	      ਜੇ (TYPE_ਅਗਲਾ_VARIANT (t) == remove)
		{
		  TYPE_ਅਗਲਾ_VARIANT (t) = TYPE_ਅਗਲਾ_VARIANT (remove);
		  ਰੋਕੋ;
		}
	}

      /* Make sure we refer to the same type as the olddecl.  */
      DECL_ORIGINAL_TYPE (newdecl) = DECL_ORIGINAL_TYPE (olddecl);
    }

  /* Merge the data types specified in the two decls.  */
  ਰੁੱਖ_TYPE (newdecl)
    = ਰੁੱਖ_TYPE (olddecl)
    = ਸੰਯੁਕਤ_type (newtype, oldtype);

  /* Lay the type out, unless already done.  */
  ਜੇ (!comptypes (oldtype, ਰੁੱਖ_TYPE (newdecl)))
    {
      ਜੇ (ਰੁੱਖ_TYPE (newdecl) != error_mark_ਗੰਢ)
	layout_type (ਰੁੱਖ_TYPE (newdecl));
      ਜੇ (ਰੁੱਖ_ਕੋਡ (newdecl) != FUNCTION_DECL
	  && ਰੁੱਖ_ਕੋਡ (newdecl) != TYPE_DECL
	  && ਰੁੱਖ_ਕੋਡ (newdecl) != CONST_DECL)
	layout_decl (newdecl, 0);
    }
  ਨਹੀਂਤਾਂ
    {
      /* Since the type is OLDDECL's, make OLDDECL's size go with.  */
      DECL_ਮਾਪ (newdecl) = DECL_ਮਾਪ (olddecl);
      DECL_ਮਾਪ_UNIT (newdecl) = DECL_ਮਾਪ_UNIT (olddecl);
      ਸੈੱਟ_DECL_ਬਹੁਲਕ (newdecl, DECL_ਬਹੁਲਕ (olddecl));
      ਜੇ (DECL_ALIGN (olddecl) > DECL_ALIGN (newdecl))
	{
	  ਸੈੱਟ_DECL_ALIGN (newdecl, DECL_ALIGN (olddecl));
	  DECL_USER_ALIGN (newdecl) |= DECL_USER_ALIGN (olddecl);
	}
      ਨਹੀਂਤਾਂ ਜੇ (DECL_ALIGN (olddecl) == DECL_ALIGN (newdecl)
	       && DECL_USER_ALIGN (olddecl) != DECL_USER_ALIGN (newdecl))
	DECL_USER_ALIGN (newdecl) = 1;
      ਜੇ (DECL_WARN_IF_NOT_ALIGN (olddecl)
	  > DECL_WARN_IF_NOT_ALIGN (newdecl))
	ਸੈੱਟ_DECL_WARN_IF_NOT_ALIGN (newdecl,
				    DECL_WARN_IF_NOT_ALIGN (olddecl));
    }

  /* Keep the old rtl since we can safely use it.  */
  ਜੇ (HAS_RTL_P (olddecl))
    COPY_DECL_RTL (olddecl, newdecl);

  /* Merge the type qualifiers.  */
  ਜੇ (ਰੁੱਖ_READONLY (newdecl))
    ਰੁੱਖ_READONLY (olddecl) = 1;

  ਜੇ (ਰੁੱਖ_THIS_VOLATILE (newdecl))
    ਰੁੱਖ_THIS_VOLATILE (olddecl) = 1;

  /* Merge deprecatedness.  */
  ਜੇ (ਰੁੱਖ_DEPRECATED (newdecl))
    ਰੁੱਖ_DEPRECATED (olddecl) = 1;

  /* Merge unavailability.  */
  ਜੇ (ਰੁੱਖ_UNAVAILABLE (newdecl))
    ਰੁੱਖ_UNAVAILABLE (olddecl) = 1;

  /* If a decl is in a system header and the other isn't, keep the one on the
     system header. Otherwise, keep source location of definition rather than
     declaration and of prototype rather than non-prototype unless that
     prototype is built-in.  */
  ਜੇ (HAS_DECL_ASSEMBLER_NAME_P (olddecl)
      && DECL_ਵਿੱਚ_SYSTEM_ਸਿਰਲੇਖ (olddecl)
      && !DECL_ਵਿੱਚ_SYSTEM_ਸਿਰਲੇਖ (newdecl) )
    DECL_ਸਰੋਤ_LOCATION (newdecl) = DECL_ਸਰੋਤ_LOCATION (olddecl);
  ਨਹੀਂਤਾਂ ਜੇ (HAS_DECL_ASSEMBLER_NAME_P (olddecl)
	   && DECL_ਵਿੱਚ_SYSTEM_ਸਿਰਲੇਖ (newdecl)
	   && !DECL_ਵਿੱਚ_SYSTEM_ਸਿਰਲੇਖ (olddecl))
    DECL_ਸਰੋਤ_LOCATION (olddecl) = DECL_ਸਰੋਤ_LOCATION (newdecl);
  ਨਹੀਂਤਾਂ ਜੇ ((DECL_INITIAL (newdecl) == NULL_ਰੁੱਖ
	    && DECL_INITIAL (olddecl) != NULL_ਰੁੱਖ)
	   || (old_is_prototype && !new_is_prototype
	       && !C_DECL_BUILTIN_PROTOTYPE (olddecl)))
    DECL_ਸਰੋਤ_LOCATION (newdecl) = DECL_ਸਰੋਤ_LOCATION (olddecl);

  /* Merge the initialization information.  */
   ਜੇ (DECL_INITIAL (newdecl) == NULL_ਰੁੱਖ)
    DECL_INITIAL (newdecl) = DECL_INITIAL (olddecl);

  /* Merge 'constexpr' information.  */
  ਜੇ (VAR_P (olddecl) && VAR_P (newdecl))
    {
      ਜੇ (C_DECL_DECLARED_CONSTEXPR (olddecl))
	C_DECL_DECLARED_CONSTEXPR (newdecl) = 1;
      ਨਹੀਂਤਾਂ ਜੇ (C_DECL_DECLARED_CONSTEXPR (newdecl))
	C_DECL_DECLARED_CONSTEXPR (olddecl) = 1;
    }

  /* Merge the threadprivate attribute.  */
  ਜੇ (VAR_P (olddecl) && C_DECL_THREADPRIVATE_P (olddecl))
    C_DECL_THREADPRIVATE_P (newdecl) = 1;

  ਜੇ (HAS_DECL_ASSEMBLER_NAME_P (olddecl))
    {
      /* Copy the assembler name.
	 Currently, it can only be defined in the prototype.  */
      COPY_DECL_ASSEMBLER_NAME (olddecl, newdecl);

      /* Use visibility of whichever declaration had it specified */
      ਜੇ (DECL_VISIBILITY_SPECIFIED (olddecl))
	{
	  DECL_VISIBILITY (newdecl) = DECL_VISIBILITY (olddecl);
	  DECL_VISIBILITY_SPECIFIED (newdecl) = 1;
	}

      ਜੇ (ਰੁੱਖ_ਕੋਡ (newdecl) == FUNCTION_DECL)
	{
	  DECL_STATIC_CONSTRUCTOR(newdecl) |= DECL_STATIC_CONSTRUCTOR(olddecl);
	  DECL_STATIC_DESTRUCTOR (newdecl) |= DECL_STATIC_DESTRUCTOR (olddecl);
	  DECL_NO_ਹੱਦਬੰਦੀ_ਢੇਰ (newdecl) |= DECL_NO_ਹੱਦਬੰਦੀ_ਢੇਰ (olddecl);
	  DECL_NO_INSTRUMENT_FUNCTION_ਇੰਦਰਾਜ_EXIT (newdecl)
	    |= DECL_NO_INSTRUMENT_FUNCTION_ਇੰਦਰਾਜ_EXIT (olddecl);
	  ਰੁੱਖ_THIS_VOLATILE (newdecl) |= ਰੁੱਖ_THIS_VOLATILE (olddecl);
	  DECL_IS_MALLOC (newdecl) |= DECL_IS_MALLOC (olddecl);
	  ਜੇ (DECL_IS_OPERATOR_NEW_P (olddecl))
	    DECL_ਸੈੱਟ_IS_OPERATOR_NEW (newdecl, ਸੱਚ);
	  ਜੇ (DECL_IS_OPERATOR_DELETE_P (olddecl))
	    DECL_ਸੈੱਟ_IS_OPERATOR_DELETE (newdecl, ਸੱਚ);
	  ਰੁੱਖ_READONLY (newdecl) |= ਰੁੱਖ_READONLY (olddecl);
	  DECL_ਸ਼ੁੱਧ_P (newdecl) |= DECL_ਸ਼ੁੱਧ_P (olddecl);
	  DECL_IS_NOVOPS (newdecl) |= DECL_IS_NOVOPS (olddecl);
	}

      /* Merge the storage class information.  */
      ਮਿਲਾਓ_weak (newdecl, olddecl);

      /* For functions, static overrides non-static.  */
      ਜੇ (ਰੁੱਖ_ਕੋਡ (newdecl) == FUNCTION_DECL)
	{
	  ਰੁੱਖ_ਜਨਤਕ (newdecl) &= ਰੁੱਖ_ਜਨਤਕ (olddecl);
	  /* This is since we don't automatically
	     copy the attributes of NEWDECL into OLDDECL.  */
	  ਰੁੱਖ_ਜਨਤਕ (olddecl) = ਰੁੱਖ_ਜਨਤਕ (newdecl);
	  /* If this clears `static', clear it in the identifier too.  */
	  ਜੇ (!ਰੁੱਖ_ਜਨਤਕ (olddecl))
	    ਰੁੱਖ_ਜਨਤਕ (DECL_NAME (olddecl)) = 0;
	}
    }

  /* In c99, 'extern' declaration before (or after) 'inline' means this
     function is not DECL_EXTERNAL, unless 'gnu_inline' attribute
     is present.  */
  ਜੇ (ਰੁੱਖ_ਕੋਡ (newdecl) == FUNCTION_DECL
      && !flag_gnu89_inline
      && (DECL_DECLARED_INLINE_P (newdecl)
	  || DECL_DECLARED_INLINE_P (olddecl))
      && (!DECL_DECLARED_INLINE_P (newdecl)
	  || !DECL_DECLARED_INLINE_P (olddecl)
	  || !DECL_EXTERNAL (olddecl))
      && DECL_EXTERNAL (newdecl)
      && !lookup_attribute ("gnu_inline", DECL_ਗੁਣ (newdecl))
      && !current_function_decl)
    DECL_EXTERNAL (newdecl) = 0;

  /* An inline definition following a static declaration is not
     DECL_EXTERNAL.  */
  ਜੇ (new_is_definition
      && (DECL_DECLARED_INLINE_P (newdecl)
	  || DECL_DECLARED_INLINE_P (olddecl))
      && !ਰੁੱਖ_ਜਨਤਕ (olddecl))
    DECL_EXTERNAL (newdecl) = 0;

  ਜੇ (DECL_EXTERNAL (newdecl))
    {
      ਰੁੱਖ_STATIC (newdecl) = ਰੁੱਖ_STATIC (olddecl);
      DECL_EXTERNAL (newdecl) = DECL_EXTERNAL (olddecl);

      /* An extern decl does not override previous storage class.  */
      ਰੁੱਖ_ਜਨਤਕ (newdecl) = ਰੁੱਖ_ਜਨਤਕ (olddecl);
      ਜੇ (!DECL_EXTERNAL (newdecl))
	{
	  DECL_CONTEXT (newdecl) = DECL_CONTEXT (olddecl);
	  DECL_COMMON (newdecl) = DECL_COMMON (olddecl);
	}
    }
  ਨਹੀਂਤਾਂ
    {
      ਰੁੱਖ_STATIC (olddecl) = ਰੁੱਖ_STATIC (newdecl);
      ਰੁੱਖ_ਜਨਤਕ (olddecl) = ਰੁੱਖ_ਜਨਤਕ (newdecl);
    }

  ਜੇ (ਰੁੱਖ_ਕੋਡ (newdecl) == FUNCTION_DECL)
    {
      ਜੇ (DECL_FUNCTION_VERSIONED (olddecl)
	  || DECL_FUNCTION_VERSIONED (newdecl))
	{
	  maybe_mark_function_versioned (olddecl);
	  maybe_mark_function_versioned (newdecl);
	}
      /* If we're redefining a function previously defined as extern
	 inline, make sure we emit debug info for the inline before we
	 throw it away, in case it was inlined into a function that
	 hasn't been written out yet.  */
      ਜੇ (new_is_definition && DECL_INITIAL (olddecl))
	/* The new defn must not be inline.  */
	DECL_UNINLINABLE (newdecl) = 1;
      ਨਹੀਂਤਾਂ
	{
	  /* If either decl says `inline', this fn is inline, unless
	     its definition was passed already.  */
	  ਜੇ (DECL_DECLARED_INLINE_P (newdecl)
	      || DECL_DECLARED_INLINE_P (olddecl))
	    DECL_DECLARED_INLINE_P (newdecl) = 1;

	  DECL_UNINLINABLE (newdecl) = DECL_UNINLINABLE (olddecl)
	    = (DECL_UNINLINABLE (newdecl) || DECL_UNINLINABLE (olddecl));

	  DECL_DISREGARD_INLINE_LIMITS (newdecl)
	    = DECL_DISREGARD_INLINE_LIMITS (olddecl)
	    = (DECL_DISREGARD_INLINE_LIMITS (newdecl)
	       || DECL_DISREGARD_INLINE_LIMITS (olddecl));
	}

      ਜੇ (fndecl_built_ਵਿੱਚ_p (olddecl))
	{
	  /* If redeclaring a builtin function, it stays built in.
	     But it gets tagged as having been declared.  */
	  copy_decl_built_ਵਿੱਚ_function (newdecl, olddecl);
	  C_DECL_DECLARED_BUILTIN (newdecl) = 1;
	  ਜੇ (new_is_prototype)
	    {
	      C_DECL_BUILTIN_PROTOTYPE (newdecl) = 0;
	      ਜੇ (DECL_BUILT_ਵਿੱਚ_CLASS (newdecl) == BUILT_ਵਿੱਚ_ਸਾਧਾਰਨ)
		{
		  ਗਿਣਤੀ built_ਵਿੱਚ_function fncode = DECL_FUNCTION_ਕੋਡ (newdecl);
		  ਚੋਣ (fncode)
		    {
		      /* If a compatible prototype of these builtin functions
			 is seen, assume the runtime implements it with the
			 expected semantics.  */
		    ਹਾਲਤ BUILT_ਵਿੱਚ_STPCPY:
		      ਜੇ (builtin_decl_explicit_p (fncode))
			ਸੈੱਟ_builtin_decl_implicit_p (fncode, ਸੱਚ);
		      ਰੋਕੋ;
		    ਮੂਲ:
		      ਜੇ (builtin_decl_explicit_p (fncode))
			ਸੈੱਟ_builtin_decl_declared_p (fncode, ਸੱਚ);
		      ਰੋਕੋ;
		    }

		  copy_ਗੁਣ_ਮੰਜ਼ਿਲ_builtin (newdecl);
		}
	    }
	  ਨਹੀਂਤਾਂ
	    C_DECL_BUILTIN_PROTOTYPE (newdecl)
	      = C_DECL_BUILTIN_PROTOTYPE (olddecl);
	}

      /* Preserve function specific target and optimization options */
      ਜੇ (DECL_FUNCTION_SPECIFIC_ਨਿਸ਼ਾਨਾ (olddecl)
	  && !DECL_FUNCTION_SPECIFIC_ਨਿਸ਼ਾਨਾ (newdecl))
	DECL_FUNCTION_SPECIFIC_ਨਿਸ਼ਾਨਾ (newdecl)
	  = DECL_FUNCTION_SPECIFIC_ਨਿਸ਼ਾਨਾ (olddecl);

      ਜੇ (DECL_FUNCTION_SPECIFIC_OPTIMIZATION (olddecl)
	  && !DECL_FUNCTION_SPECIFIC_OPTIMIZATION (newdecl))
	DECL_FUNCTION_SPECIFIC_OPTIMIZATION (newdecl)
	  = DECL_FUNCTION_SPECIFIC_OPTIMIZATION (olddecl);

      /* Also preserve various other info from the definition.  */
      ਜੇ (!new_is_definition)
	{
	  ਰੁੱਖ t;
	  DECL_ਨਤੀਜਾ (newdecl) = DECL_ਨਤੀਜਾ (olddecl);
	  DECL_INITIAL (newdecl) = DECL_INITIAL (olddecl);
	  DECL_STRUCT_FUNCTION (newdecl) = DECL_STRUCT_FUNCTION (olddecl);
	  DECL_SAVED_ਰੁੱਖ (newdecl) = DECL_SAVED_ਰੁੱਖ (olddecl);
	  DECL_ARGUMENTS (newdecl) = copy_list (DECL_ARGUMENTS (olddecl));
	  ਲਈ (t = DECL_ARGUMENTS (newdecl); t ; t = DECL_CHAIN (t))
	    DECL_CONTEXT (t) = newdecl;

	  /* See if we've got a function to instantiate from.  */
	  ਜੇ (DECL_SAVED_ਰੁੱਖ (olddecl))
	    DECL_ABSTRACT_ORIGIN (newdecl)
	      = DECL_ABSTRACT_ORIGIN (olddecl);
	}
    }

  /* Merge the USED information.  */
  ਜੇ (ਰੁੱਖ_ਵਰਤਿਆ (olddecl))
    ਰੁੱਖ_ਵਰਤਿਆ (newdecl) = 1;
  ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਵਰਤਿਆ (newdecl))
    ਰੁੱਖ_ਵਰਤਿਆ (olddecl) = 1;
  ਜੇ (VAR_P (olddecl) || ਰੁੱਖ_ਕੋਡ (olddecl) == PARM_DECL)
    DECL_READ_P (newdecl) |= DECL_READ_P (olddecl);
  ਜੇ (DECL_PRESERVE_P (olddecl))
    DECL_PRESERVE_P (newdecl) = 1;
  ਨਹੀਂਤਾਂ ਜੇ (DECL_PRESERVE_P (newdecl))
    DECL_PRESERVE_P (olddecl) = 1;

  /* Merge DECL_COMMON */
  ਜੇ (VAR_P (olddecl) && VAR_P (newdecl)
      && !lookup_attribute ("common", DECL_ਗੁਣ (newdecl))
      && !lookup_attribute ("nocommon", DECL_ਗੁਣ (newdecl)))
    DECL_COMMON (newdecl) = DECL_COMMON (newdecl) && DECL_COMMON (olddecl);

  /* Copy most of the decl-specific fields of NEWDECL into OLDDECL.
     But preserve OLDDECL's DECL_UID, DECL_CONTEXT and
     DECL_ARGUMENTS (if appropriate).  */
  {
    ਬਿਨਾਨਿਸ਼ਾਨੀ olddecl_uid = DECL_UID (olddecl);
    ਰੁੱਖ olddecl_context = DECL_CONTEXT (olddecl);
    ਰੁੱਖ olddecl_arguments = ਨਿਰਾ;
    ਜੇ (ਰੁੱਖ_ਕੋਡ (olddecl) == FUNCTION_DECL)
      olddecl_arguments = DECL_ARGUMENTS (olddecl);

    ਸਮ੍ਰਿਤੀ_ਨਕਲ ((ਅੱਖਰ *) olddecl + ਆਕਾਰ (ਬਣਤਰ ਰੁੱਖ_common),
	    (ਅੱਖਰ *) newdecl + ਆਕਾਰ (ਬਣਤਰ ਰੁੱਖ_common),
	    ਆਕਾਰ (ਬਣਤਰ ਰੁੱਖ_decl_common) - ਆਕਾਰ (ਬਣਤਰ ਰੁੱਖ_common));
    DECL_USER_ALIGN (olddecl) = DECL_USER_ALIGN (newdecl);
    ਚੋਣ (ਰੁੱਖ_ਕੋਡ (olddecl))
      {
      ਹਾਲਤ FUNCTION_DECL:
      ਹਾਲਤ VAR_DECL:
	{
	  ਬਣਤਰ symtab_ਗੰਢ *snode = olddecl->decl_with_vis.symtab_ਗੰਢ;

	  ਸਮ੍ਰਿਤੀ_ਨਕਲ ((ਅੱਖਰ *) olddecl + ਆਕਾਰ (ਬਣਤਰ ਰੁੱਖ_decl_common),
		  (ਅੱਖਰ *) newdecl + ਆਕਾਰ (ਬਣਤਰ ਰੁੱਖ_decl_common),
		  ਰੁੱਖ_ਕੋਡ_ਮਾਪ (ਰੁੱਖ_ਕੋਡ (olddecl)) - ਆਕਾਰ (ਬਣਤਰ ਰੁੱਖ_decl_common));
	  olddecl->decl_with_vis.symtab_ਗੰਢ = snode;

	  ਜੇ ((DECL_EXTERNAL (olddecl)
	       || ਰੁੱਖ_ਜਨਤਕ (olddecl)
	       || ਰੁੱਖ_STATIC (olddecl))
	      && DECL_SECTION_NAME (newdecl) != ਨਿਰਾ)
	    ਸੈੱਟ_decl_section_name (olddecl, newdecl);

	  /* This isn't quite correct for something like
		int __thread x attribute ((tls_model ("local-exec")));
		extern int __thread x;
	     as we'll lose the "local-exec" model.  */
	  ਜੇ (VAR_P (olddecl) && DECL_THREAD_LOCAL_P (newdecl))
	    ਸੈੱਟ_decl_tls_model (olddecl, DECL_TLS_MODEL (newdecl));
	  ਰੋਕੋ;
	}

      ਹਾਲਤ ਖੇਤਰ_DECL:
      ਹਾਲਤ PARM_DECL:
      ਹਾਲਤ LABEL_DECL:
      ਹਾਲਤ ਨਤੀਜਾ_DECL:
      ਹਾਲਤ CONST_DECL:
      ਹਾਲਤ TYPE_DECL:
	ਸਮ੍ਰਿਤੀ_ਨਕਲ ((ਅੱਖਰ *) olddecl + ਆਕਾਰ (ਬਣਤਰ ਰੁੱਖ_decl_common),
		(ਅੱਖਰ *) newdecl + ਆਕਾਰ (ਬਣਤਰ ਰੁੱਖ_decl_common),
		ਰੁੱਖ_ਕੋਡ_ਮਾਪ (ਰੁੱਖ_ਕੋਡ (olddecl)) - ਆਕਾਰ (ਬਣਤਰ ਰੁੱਖ_decl_common));
	ਰੋਕੋ;

      ਮੂਲ:

	ਸਮ੍ਰਿਤੀ_ਨਕਲ ((ਅੱਖਰ *) olddecl + ਆਕਾਰ (ਬਣਤਰ ਰੁੱਖ_decl_common),
		(ਅੱਖਰ *) newdecl + ਆਕਾਰ (ਬਣਤਰ ਰੁੱਖ_decl_common),
		ਆਕਾਰ (ਬਣਤਰ ਰੁੱਖ_decl_non_common) - ਆਕਾਰ (ਬਣਤਰ ਰੁੱਖ_decl_common));
      }
    DECL_UID (olddecl) = olddecl_uid;
    DECL_CONTEXT (olddecl) = olddecl_context;
    ਜੇ (ਰੁੱਖ_ਕੋਡ (olddecl) == FUNCTION_DECL)
      DECL_ARGUMENTS (olddecl) = olddecl_arguments;
  }

  /* If OLDDECL had its DECL_RTL instantiated, re-invoke make_decl_rtl
     so that encode_section_info has a chance to look at the new decl
     flags and attributes.  */
  ਜੇ (DECL_RTL_ਸੈੱਟ_P (olddecl)
      && (ਰੁੱਖ_ਕੋਡ (olddecl) == FUNCTION_DECL
	  || (VAR_P (olddecl) && ਰੁੱਖ_STATIC (olddecl))))
    make_decl_rtl (olddecl);
}

/* Handle when a new declaration NEWDECL has the same name as an old
   one OLDDECL in the same binding contour.  Prints an error message
   if appropriate.

   If safely possible, alter OLDDECL to look like NEWDECL, and return
   true.  Otherwise, return false.  */

ਸਥਿਰ ਤਾਰਕਿਕ
duplicate_decls (ਰੁੱਖ newdecl, ਰੁੱਖ olddecl)
{
  ਰੁੱਖ newtype = ਨਿਰਾ, oldtype = ਨਿਰਾ;

  ਜੇ (!diagnose_mismatched_decls (newdecl, olddecl, &newtype, &oldtype))
    {
      /* Avoid `unused variable' and other warnings for OLDDECL.  */
      suppress_warning (olddecl, OPT_Wunused);
      /* If the types are completely different, poison them both with
 	 error_mark_node.  */
      ਜੇ (ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (newdecl)) != ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (olddecl))
	  && olddecl != error_mark_ਗੰਢ
	  && ਵੇਖਿਆ_error ())
	{
	  ਜੇ (ਰੁੱਖ_ਕੋਡ (olddecl) != FUNCTION_DECL)
	    ਰੁੱਖ_TYPE (olddecl) = error_mark_ਗੰਢ;
	  ਜੇ (ਰੁੱਖ_ਕੋਡ (newdecl) != FUNCTION_DECL)
	    ਰੁੱਖ_TYPE (newdecl) = error_mark_ਗੰਢ;
	}
      ਵਾਪਸ ਝੂਠ;
    }

  ਮਿਲਾਓ_decls (newdecl, olddecl, newtype, oldtype);

  /* The NEWDECL will no longer be needed.

     Before releasing the node, be sure to remove function from symbol
     table that might have been inserted there to record comdat group.
     Be sure to however do not free DECL_STRUCT_FUNCTION because this
     structure is shared in between NEWDECL and OLDECL.  */
  ਜੇ (ਰੁੱਖ_ਕੋਡ (newdecl) == FUNCTION_DECL)
    DECL_STRUCT_FUNCTION (newdecl) = ਨਿਰਾ;
  ਜੇ (VAR_OR_FUNCTION_DECL_P (newdecl))
    {
      ਬਣਤਰ symtab_ਗੰਢ *snode = symtab_ਗੰਢ::get (newdecl);
      ਜੇ (snode)
	snode->remove ();
    }
  ggc_free (newdecl);
  ਵਾਪਸ ਸੱਚ;
}


/* Check whether decl-node NEW_DECL shadows an existing declaration.  */
ਸਥਿਰ ਖਾਲੀ
warn_if_shadowing (ਰੁੱਖ new_decl)
{
  ਬਣਤਰ c_binding *b;

  /* Shadow warnings wanted?  */
  ਜੇ (!(warn_shadow
        || warn_shadow_local
        || warn_shadow_compatible_local)
      /* No shadow warnings for internally generated vars.  */
      || DECL_IS_UNDECLARED_BUILTIN (new_decl))
    ਵਾਪਸ;

  /* Is anything being shadowed?  Invisible decls do not count.  */
  ਲਈ (b = I_ਚਿੰਨ੍ਹ_BINDING (DECL_NAME (new_decl)); b; b = b->shadowed)
    ਜੇ (b->decl && b->decl != new_decl && !b->invisible
	&& (b->decl == error_mark_ਗੰਢ
	    || diagnostic_report_warnings_p (global_dc,
					     DECL_ਸਰੋਤ_LOCATION (b->decl))))
      {
	ਰੁੱਖ old_decl = b->decl;

	ਜੇ (old_decl == error_mark_ਗੰਢ)
	  {
	    warning (OPT_Wshadow, "declaration of %q+D shadows previous "
		     "non-variable", new_decl);
	    ਰੋਕੋ;
	  }

	ਤਾਰਕਿਕ warned = ਝੂਠ;
	auto_diagnostic_ਸਮੂਹ d;
	ਜੇ (ਰੁੱਖ_ਕੋਡ (old_decl) == PARM_DECL)
	  {
	    ਗਿਣਤੀ opt_ਕੋਡ warning_ਕੋਡ;

	    /* If '-Wshadow=compatible-local' is specified without other
	       -Wshadow= flags, we will warn only when the types of the
	       shadowing variable (i.e. new_decl) and the shadowed variable
	       (old_decl) are compatible.  */
	    ਜੇ (warn_shadow)
	      warning_ਕੋਡ = OPT_Wshadow;
	    ਨਹੀਂਤਾਂ ਜੇ (comptypes (ਰੁੱਖ_TYPE (old_decl), ਰੁੱਖ_TYPE (new_decl)))
	      warning_ਕੋਡ = OPT_Wshadow_compatible_local;
	    ਨਹੀਂਤਾਂ
	      warning_ਕੋਡ = OPT_Wshadow_local;
	    warned = warning_at (DECL_ਸਰੋਤ_LOCATION (new_decl), warning_ਕੋਡ,
				 "declaration of %qD shadows a parameter",
				 new_decl);
	  }
	ਨਹੀਂਤਾਂ ਜੇ (DECL_FILE_SCOPE_P (old_decl))
	  {
	    /* Do not warn if a variable shadows a function, unless
	       the variable is a function or a pointer-to-function.  */
	    ਜੇ (ਰੁੱਖ_ਕੋਡ (old_decl) == FUNCTION_DECL
		&& ਰੁੱਖ_ਕੋਡ (new_decl) != FUNCTION_DECL
		&& !FUNCTION_ਸੂਚਕ_TYPE_P (ਰੁੱਖ_TYPE (new_decl)))
		ਜਾਰੀ;

	    warned = warning_at (DECL_ਸਰੋਤ_LOCATION (new_decl), OPT_Wshadow,
				 "declaration of %qD shadows a global "
				 "declaration",
				 new_decl);
	  }
	ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਕੋਡ (old_decl) == FUNCTION_DECL
		 && fndecl_built_ਵਿੱਚ_p (old_decl))
	  {
	    warning (OPT_Wshadow, "declaration of %q+D shadows "
		     "a built-in function", new_decl);
	    ਰੋਕੋ;
	  }
	ਨਹੀਂਤਾਂ
	  {
	    ਗਿਣਤੀ opt_ਕੋਡ warning_ਕੋਡ;

	    /* If '-Wshadow=compatible-local' is specified without other
	       -Wshadow= flags, we will warn only when the types of the
	       shadowing variable (i.e. new_decl) and the shadowed variable
	       (old_decl) are compatible.  */
	    ਜੇ (warn_shadow)
	      warning_ਕੋਡ = OPT_Wshadow;
	    ਨਹੀਂਤਾਂ ਜੇ (comptypes (ਰੁੱਖ_TYPE (old_decl), ਰੁੱਖ_TYPE (new_decl)))
	      warning_ਕੋਡ = OPT_Wshadow_compatible_local;
	    ਨਹੀਂਤਾਂ
	      warning_ਕੋਡ = OPT_Wshadow_local;
	    warned = warning_at (DECL_ਸਰੋਤ_LOCATION (new_decl), warning_ਕੋਡ,
				 "declaration of %qD shadows a previous local",
				 new_decl);
	  }

	ਜੇ (warned)
	  inform (DECL_ਸਰੋਤ_LOCATION (old_decl),
		  "shadowed declaration is here");

	ਰੋਕੋ;
      }
}

/* Record a decl-node X as belonging to the current lexical scope.
   Check for errors (such as an incompatible declaration for the same
   name already seen in the same scope).

   Returns either X or an old decl for the same name.
   If an old decl is returned, it may have been smashed
   to agree with what X says.  */

ਰੁੱਖ
pushdecl (ਰੁੱਖ x)
{
  ਰੁੱਖ name = DECL_NAME (x);
  ਬਣਤਰ c_scope *scope = current_scope;
  ਬਣਤਰ c_binding *b;
  ਤਾਰਕਿਕ nested = ਝੂਠ;
  location_t locus = DECL_ਸਰੋਤ_LOCATION (x);

  /* Must set DECL_CONTEXT for everything not at file scope or
     DECL_FILE_SCOPE_P won't work.  Local externs don't count
     unless they have initializers (which generate code).  We
     also exclude CONST_DECLs because enumerators will get the
     type of the enum as context.  */
  ਜੇ (current_function_decl
      && ਰੁੱਖ_ਕੋਡ (x) != CONST_DECL
      && (!VAR_OR_FUNCTION_DECL_P (x)
	  || DECL_INITIAL (x) || !ਰੁੱਖ_ਜਨਤਕ (x)))
    DECL_CONTEXT (x) = current_function_decl;

  /* Anonymous decls are just inserted in the scope.  */
  ਜੇ (!name)
    {
      bind (name, x, scope, /*invisible=*/ਝੂਠ, /*nested=*/ਝੂਠ,
	    locus);
      ਵਾਪਸ x;
    }

  /* First, see if there is another declaration with the same name in
     the current scope.  If there is, duplicate_decls may do all the
     work for us.  If duplicate_decls returns false, that indicates
     two incompatible decls in the same scope; we are to silently
     replace the old one (duplicate_decls has issued all appropriate
     diagnostics).  In particular, we should not consider possible
     duplicates in the external scope, or shadowing.  */
  b = I_ਚਿੰਨ੍ਹ_BINDING (name);
  ਜੇ (b && B_ਵਿੱਚ_SCOPE (b, scope))
    {
      ਬਣਤਰ c_binding *b_ext, *b_use;
      ਰੁੱਖ type = ਰੁੱਖ_TYPE (x);
      ਰੁੱਖ visdecl = b->decl;
      ਰੁੱਖ vistype = ਰੁੱਖ_TYPE (visdecl);
      ਜੇ (ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (x)) == ARRAY_TYPE
	  && COMPLETE_TYPE_P (ਰੁੱਖ_TYPE (x)))
	b->inner_comp = ਝੂਠ;
      b_use = b;
      b_ext = b;
      /* If this is an external linkage declaration, we should check
	 for compatibility with the type in the external scope before
	 setting the type at this scope based on the visible
	 information only.  */
      ਜੇ (ਰੁੱਖ_ਜਨਤਕ (x) && ਰੁੱਖ_ਜਨਤਕ (visdecl))
	{
	  ਜਦੋਂ (b_ext && !B_ਵਿੱਚ_EXTERNAL_SCOPE (b_ext))
	    b_ext = b_ext->shadowed;
	  ਜੇ (b_ext)
	    {
	      b_use = b_ext;
	      ਜੇ (b_use->u.type)
		ਰੁੱਖ_TYPE (b_use->decl) = b_use->u.type;
	    }
	}

      /* Check if x is part of a FMV set with b_use.
	 FMV is only supported in c for targets with target_version
	 attributes.  */
      ਜੇ (!ਨਿਸ਼ਾਨਾ_HAS_FMV_ਨਿਸ਼ਾਨਾ_ATTRIBUTE
	  && b_use && ਰੁੱਖ_ਕੋਡ (b_use->decl) == FUNCTION_DECL
	  && ਰੁੱਖ_ਕੋਡ (x) == FUNCTION_DECL && DECL_FILE_SCOPE_P (b_use->decl)
	  && DECL_FILE_SCOPE_P (x)
	  && disjoint_ਸੰਸਕਰਣ_decls (x, b_use->decl)
	  && comptypes (vistype, type))
	{
	  maybe_mark_function_versioned (b_use->decl);
	  maybe_mark_function_versioned (b->decl);
	  maybe_mark_function_versioned (x);

	  cgraph_ਗੰਢ *b_ਗੰਢ = cgraph_ਗੰਢ::get_create (b_use->decl);
	  cgraph_function_ਸੰਸਕਰਣ_info *b_v = b_ਗੰਢ->function_ਸੰਸਕਰਣ ();
	  ਜੇ (!b_v)
	    b_v = b_ਗੰਢ->ਪਾਓ_new_function_ਸੰਸਕਰਣ ();

	  /* Check if this new node conflicts with any previous functions
	     in the set.  */
	  cgraph_function_ਸੰਸਕਰਣ_info *ਸੰਸਕਰਣ = b_v;
	  ਲਈ (; ਸੰਸਕਰਣ; ਸੰਸਕਰਣ = ਸੰਸਕਰਣ->ਅਗਲਾ)
	    ਜੇ (!disjoint_ਸੰਸਕਰਣ_decls (ਸੰਸਕਰਣ->this_ਗੰਢ->decl, x))
	      {
		/* The decls define overlapping version, so attempt to merge
		   or diagnose the conflict.  */
		ਜੇ (duplicate_decls (x, ਸੰਸਕਰਣ->this_ਗੰਢ->decl))
		  ਵਾਪਸ ਸੰਸਕਰਣ->this_ਗੰਢ->decl;
		ਨਹੀਂਤਾਂ
		  ਵਾਪਸ error_mark_ਗੰਢ;
	      }

	  /* This is a new version to be added to FMV structure.  */
	  cgraph_ਗੰਢ::ਜੋੜੋ_function_ਸੰਸਕਰਣ (b_v, x);

	  /* Get the first node from the structure.  */
	  cgraph_function_ਸੰਸਕਰਣ_info *default_v = b_v;
	  ਜਦੋਂ (default_v->prev)
	    default_v = default_v->prev;
	  /* Always use the default node for the bindings.  */
	  b_use->decl = default_v->this_ਗੰਢ->decl;
	  b->decl = default_v->this_ਗੰਢ->decl;

	  /* Node is not a duplicate, so no need to do the rest of the
	     checks.  */
	  ਵਾਪਸ x;
	}

      ਜੇ (duplicate_decls (x, b_use->decl))
	{
	  ਜੇ (b_use != b)
	    {
	      /* Save the updated type in the external scope and
		 restore the proper type for this scope.  */
	      ਰੁੱਖ thistype;
	      ਜੇ (comptypes (vistype, type))
		thistype = ਸੰਯੁਕਤ_type (vistype, type);
	      ਨਹੀਂਤਾਂ
		thistype = ਰੁੱਖ_TYPE (b_use->decl);
	      b_use->u.type = ਰੁੱਖ_TYPE (b_use->decl);
	      ਜੇ (ਰੁੱਖ_ਕੋਡ (b_use->decl) == FUNCTION_DECL
		  && fndecl_built_ਵਿੱਚ_p (b_use->decl))
		thistype
		  = c_build_type_attribute_variant (thistype,
						    TYPE_ਗੁਣ
						    (b_use->u.type));
	      ਰੁੱਖ_TYPE (b_use->decl) = thistype;
	    }
	  ਵਾਪਸ b_use->decl;
	}
      ਨਹੀਂਤਾਂ
	ਜਾਓ skip_external_and_shadow_checks;
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
  ਜੇ ((DECL_EXTERNAL (x) || scope == file_scope)
      && (VAR_OR_FUNCTION_DECL_P (x) || c_dialect_objc ()))
    {
      ਰੁੱਖ type = ਰੁੱਖ_TYPE (x);
      ਰੁੱਖ vistype = NULL_ਰੁੱਖ;
      ਰੁੱਖ visdecl = NULL_ਰੁੱਖ;
      ਤਾਰਕਿਕ type_saved = ਝੂਠ;
      ਜੇ (b && !B_ਵਿੱਚ_EXTERNAL_SCOPE (b)
	  && VAR_OR_FUNCTION_DECL_P (b->decl)
	  && DECL_FILE_SCOPE_P (b->decl))
	{
	  visdecl = b->decl;
	  vistype = ਰੁੱਖ_TYPE (visdecl);
	}
      ਜੇ (scope != file_scope
	  && !DECL_ਵਿੱਚ_SYSTEM_ਸਿਰਲੇਖ (x))
	warning_at (locus, OPT_Wnested_externs,
		    "nested extern declaration of %qD", x);

      ਜਦੋਂ (b && !B_ਵਿੱਚ_EXTERNAL_SCOPE (b))
	{
	  /* If this decl might be modified, save its type.  This is
	     done here rather than when the decl is first bound
	     because the type may change after first binding, through
	     being completed or through attributes being added.  If we
	     encounter multiple such decls, only the first should have
	     its type saved; the others will already have had their
	     proper types saved and the types will not have changed as
	     their scopes will not have been re-entered.  */
	  ਜੇ (DECL_P (b->decl) && DECL_FILE_SCOPE_P (b->decl) && !type_saved)
	    {
	      b->u.type = ਰੁੱਖ_TYPE (b->decl);
	      type_saved = ਸੱਚ;
	    }
	  ਜੇ (B_ਵਿੱਚ_FILE_SCOPE (b)
	      && VAR_P (b->decl)
	      && ਰੁੱਖ_STATIC (b->decl)
	      && ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (b->decl)) == ARRAY_TYPE
	      && !TYPE_DOMAIN (ਰੁੱਖ_TYPE (b->decl))
	      && ਰੁੱਖ_ਕੋਡ (type) == ARRAY_TYPE
	      && TYPE_DOMAIN (type)
	      && TYPE_MAX_ਮੁੱਲ (TYPE_DOMAIN (type))
	      && !integer_zerop (TYPE_MAX_ਮੁੱਲ (TYPE_DOMAIN (type))))
	    {
	      /* Array type completed in inner scope, which should be
		 diagnosed if the completion does not have size 1 and
		 it does not get completed in the file scope.  */
	      b->inner_comp = ਸੱਚ;
	    }
	  b = b->shadowed;
	}

      /* If a matching external declaration has been found, set its
	 type to the composite of all the types of that declaration.
	 After the consistency checks, it will be reset to the
	 composite of the visible types only.  */
      ਜੇ (b && b->u.type)
	ਰੁੱਖ_TYPE (b->decl) = b->u.type;

      /* the static does not go in the externals scope.  */
      ਜੇ (b && duplicate_decls (x, b->decl))
	{
	  ਰੁੱਖ thistype;
	  ਜੇ (vistype)
	    {
	      ਜੇ (comptypes (vistype, type))
		thistype = ਸੰਯੁਕਤ_type (vistype, type);
	      ਨਹੀਂਤਾਂ
		thistype = ਰੁੱਖ_TYPE (b->decl);
	    }
	  ਨਹੀਂਤਾਂ
	    thistype = type;
	  b->u.type = ਰੁੱਖ_TYPE (b->decl);
	  /* Propagate the type attributes to the decl.  */
	  thistype
	    = c_build_type_attribute_variant (thistype,
					      TYPE_ਗੁਣ (b->u.type));
	  ਰੁੱਖ_TYPE (b->decl) = thistype;
	  bind (name, b->decl, scope, /*invisible=*/ਝੂਠ, /*nested=*/ਸੱਚ,
		locus);
	  ਵਾਪਸ b->decl;
	}
      ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਜਨਤਕ (x))
	{
	  ਜੇ (visdecl && !b && duplicate_decls (x, visdecl))
	    {
	      /* An external declaration at block scope referring to a
		 visible entity with internal linkage.  The composite
		 type will already be correct for this scope, so we
		 just need to fall through to make the declaration in
		 this scope.  */
	      nested = ਸੱਚ;
	      x = visdecl;
	    }
	  ਨਹੀਂਤਾਂ
	    {
	      bind (name, x, external_scope, /*invisible=*/ਸੱਚ,
		    /*nested=*/ਝੂਠ, locus);
	      nested = ਸੱਚ;
	    }
	}
    }

  ਜੇ (ਰੁੱਖ_ਕੋਡ (x) != PARM_DECL)
    warn_if_shadowing (x);

 skip_external_and_shadow_checks:
  ਜੇ (ਰੁੱਖ_ਕੋਡ (x) == TYPE_DECL)
    {
      /* So this is a typedef, set its underlying type.  */
      ਸੈੱਟ_underlying_type (x);

      /* If X is a typedef defined in the current function, record it
	 for the purpose of implementing the -Wunused-local-typedefs
	 warning.  */
      ਰਿਕਾਰਡ_locally_defined_typedef (x);
    }

  bind (name, x, scope, /*invisible=*/ਝੂਠ, nested, locus);

  /* If x's type is incomplete because it's based on a
     structure or union which has not yet been fully declared,
     attach it to that structure or union type, so we can go
     back and complete the variable declaration later, if the
     structure or union gets fully declared.

     If the input is erroneous, we can have error_mark in the type
     slot (e.g. "f(void a, ...)") - that doesn't count as an
     incomplete type.  */
  ਜੇ (ਰੁੱਖ_TYPE (x) != error_mark_ਗੰਢ
      && !COMPLETE_TYPE_P (ਰੁੱਖ_TYPE (x)))
    {
      ਰੁੱਖ element = ਰੁੱਖ_TYPE (x);

      ਜਦੋਂ (ਰੁੱਖ_ਕੋਡ (element) == ARRAY_TYPE)
	element = ਰੁੱਖ_TYPE (element);
      element = TYPE_MAIN_VARIANT (element);

      ਜੇ ((ਰਿਕਾਰਡ_OR_UNION_TYPE_P (element)
	   || ਰੁੱਖ_ਕੋਡ (element) == ENUMERAL_TYPE)
	  && (ਰੁੱਖ_ਕੋਡ (x) != TYPE_DECL
	      || ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (x)) == ARRAY_TYPE)
	  && !COMPLETE_TYPE_P (element))
	C_TYPE_INCOMPLETE_VARS (element)
	  = ਰੁੱਖ_cons (NULL_ਰੁੱਖ, x, C_TYPE_INCOMPLETE_VARS (element));
    }
  ਵਾਪਸ x;
}


/* Issue a permerror about implicit function declaration.  ID is the function
   identifier, OLDDECL is a declaration of the function in a different scope,
   or NULL_TREE.  */

ਸਥਿਰ ਖਾਲੀ
implicit_decl_permerror (location_t loc, ਰੁੱਖ id, ਰੁੱਖ olddecl)
{
  ਜੇ (!warn_implicit_function_declaration)
    ਵਾਪਸ;

  ਤਾਰਕਿਕ warned;
  auto_diagnostic_ਸਮੂਹ d;
  name_hint hint;
  ਜੇ (!olddecl)
    hint = lookup_name_fuzzy (id, FUZZY_LOOKUP_FUNCTION_NAME, loc);

  ਜੇ (flag_isoc99)
    {
      ਜੇ (ਅਚਲ ਅੱਖਰ *suggestion = hint.suggestion ())
	{
	  gcc_rich_location richloc (loc);
	  richloc.ਜੋੜੋ_fixit_replace (suggestion);
	  warned = permerror_opt (&richloc, OPT_Wimplicit_function_declaration,
				  "implicit declaration of function %qE;"
				  " did you mean %qs?",
				  id, suggestion);
	}
      ਨਹੀਂਤਾਂ
	warned = permerror_opt (loc, OPT_Wimplicit_function_declaration,
				"implicit declaration of function %qE", id);
    }
  ਨਹੀਂਤਾਂ ਜੇ (ਅਚਲ ਅੱਖਰ *suggestion = hint.suggestion ())
    {
      gcc_rich_location richloc (loc);
      richloc.ਜੋੜੋ_fixit_replace (suggestion);
      warned = warning_at
	(&richloc, OPT_Wimplicit_function_declaration,
	 G_("implicit declaration of function %qE; did you mean %qs?"),
	 id, suggestion);
    }
  ਨਹੀਂਤਾਂ
    warned = warning_at (loc, OPT_Wimplicit_function_declaration,
			 G_("implicit declaration of function %qE"), id);

  ਜੇ (warned)
    {
      /* Whether the olddecl is an undeclared builtin function.
	 locate_old_decl will not generate a diagnostic for those,
	 so in that case we want to look elsewhere.  */
      ਤਾਰਕਿਕ undeclared_builtin = (olddecl
				 && ਰੁੱਖ_ਕੋਡ (olddecl) == FUNCTION_DECL
				 && fndecl_built_ਵਿੱਚ_p (olddecl)
				 && !C_DECL_DECLARED_BUILTIN (olddecl));
      ਜੇ (undeclared_builtin)
	{
	  ਅਚਲ ਅੱਖਰ *ਸਿਰਲੇਖ = ਸਿਰਲੇਖ_for_builtin_fn (olddecl);
	  ਜੇ (ਸਿਰਲੇਖ)
	    {
	      rich_location richloc (ਸਤਰ_ਸਾਰਣੀ, loc);
	      maybe_ਜੋੜੋ_include_fixit (&richloc, ਸਿਰਲੇਖ, ਸੱਚ);
	      inform (&richloc,
		      "include %qs or provide a declaration of %qE",
		      ਸਿਰਲੇਖ, id);
	    }
	}
      ਨਹੀਂਤਾਂ ਜੇ (olddecl)
	locate_old_decl (olddecl);
    }

  ਜੇ (!warned)
    hint.suppress ();
}

/* Return the name of the header file that declares built-in function
   FNDECL, or null if either we don't know or don't expect to see an
   explicit declaration.  */

ਸਥਿਰ ਅਚਲ ਅੱਖਰ *
ਸਿਰਲੇਖ_for_builtin_fn (ਰੁੱਖ fndecl)
{
  ਜੇ (DECL_BUILT_ਵਿੱਚ_CLASS (fndecl) != BUILT_ਵਿੱਚ_ਸਾਧਾਰਨ)
    ਵਾਪਸ ਨਿਰਾ;

  ਚੋਣ (DECL_FUNCTION_ਕੋਡ (fndecl))
    {
    CASE_FLT_FN (BUILT_ਵਿੱਚ_ACOS):
    CASE_FLT_FN (BUILT_ਵਿੱਚ_ACOSH):
    CASE_FLT_FN (BUILT_ਵਿੱਚ_ASIN):
    CASE_FLT_FN (BUILT_ਵਿੱਚ_ASINH):
    CASE_FLT_FN (BUILT_ਵਿੱਚ_ATAN):
    CASE_FLT_FN (BUILT_ਵਿੱਚ_ATANH):
    CASE_FLT_FN (BUILT_ਵਿੱਚ_ATAN2):
    CASE_FLT_FN (BUILT_ਵਿੱਚ_CBRT):
    CASE_FLT_FN (BUILT_ਵਿੱਚ_CEIL):
    CASE_FLT_FN_FLOATN_NX (BUILT_ਵਿੱਚ_CEIL):
    CASE_FLT_FN (BUILT_ਵਿੱਚ_COPYSIGN):
    CASE_FLT_FN_FLOATN_NX (BUILT_ਵਿੱਚ_COPYSIGN):
    CASE_FLT_FN (BUILT_ਵਿੱਚ_COS):
    CASE_FLT_FN (BUILT_ਵਿੱਚ_COSH):
    CASE_FLT_FN (BUILT_ਵਿੱਚ_ERF):
    CASE_FLT_FN (BUILT_ਵਿੱਚ_ERFC):
    CASE_FLT_FN (BUILT_ਵਿੱਚ_EXP):
    CASE_FLT_FN (BUILT_ਵਿੱਚ_EXP2):
    CASE_FLT_FN (BUILT_ਵਿੱਚ_EXPM1):
    CASE_FLT_FN (BUILT_ਵਿੱਚ_FABS):
    CASE_FLT_FN_FLOATN_NX (BUILT_ਵਿੱਚ_FABS):
    CASE_FLT_FN (BUILT_ਵਿੱਚ_FDIM):
    CASE_FLT_FN (BUILT_ਵਿੱਚ_FLOOR):
    CASE_FLT_FN_FLOATN_NX (BUILT_ਵਿੱਚ_FLOOR):
    CASE_FLT_FN (BUILT_ਵਿੱਚ_FMA):
    CASE_FLT_FN_FLOATN_NX (BUILT_ਵਿੱਚ_FMA):
    CASE_FLT_FN (BUILT_ਵਿੱਚ_FMAX):
    CASE_FLT_FN_FLOATN_NX (BUILT_ਵਿੱਚ_FMAX):
    CASE_FLT_FN (BUILT_ਵਿੱਚ_FMIN):
    CASE_FLT_FN_FLOATN_NX (BUILT_ਵਿੱਚ_FMIN):
    CASE_FLT_FN (BUILT_ਵਿੱਚ_FMOD):
    CASE_FLT_FN (BUILT_ਵਿੱਚ_FREXP):
    CASE_FLT_FN (BUILT_ਵਿੱਚ_HYPOT):
    CASE_FLT_FN (BUILT_ਵਿੱਚ_ILOGB):
    CASE_FLT_FN (BUILT_ਵਿੱਚ_LDEXP):
    CASE_FLT_FN (BUILT_ਵਿੱਚ_LGAMMA):
    CASE_FLT_FN (BUILT_ਵਿੱਚ_LLRINT):
    CASE_FLT_FN (BUILT_ਵਿੱਚ_LLROUND):
    CASE_FLT_FN (BUILT_ਵਿੱਚ_LOG):
    CASE_FLT_FN (BUILT_ਵਿੱਚ_LOG10):
    CASE_FLT_FN (BUILT_ਵਿੱਚ_LOG1_P):
    CASE_FLT_FN (BUILT_ਵਿੱਚ_LOG2):
    CASE_FLT_FN (BUILT_ਵਿੱਚ_LOGB):
    CASE_FLT_FN (BUILT_ਵਿੱਚ_LRINT):
    CASE_FLT_FN (BUILT_ਵਿੱਚ_LROUND):
    CASE_FLT_FN (BUILT_ਵਿੱਚ_MODF):
    CASE_FLT_FN (BUILT_ਵਿੱਚ_NAN):
    CASE_FLT_FN (BUILT_ਵਿੱਚ_NEARBYINT):
    CASE_FLT_FN_FLOATN_NX (BUILT_ਵਿੱਚ_NEARBYINT):
    CASE_FLT_FN (BUILT_ਵਿੱਚ_NEXTAFTER):
    CASE_FLT_FN (BUILT_ਵਿੱਚ_NEXTTOWARD):
    CASE_FLT_FN (BUILT_ਵਿੱਚ_POW):
    CASE_FLT_FN (BUILT_ਵਿੱਚ_REMAINDER):
    CASE_FLT_FN (BUILT_ਵਿੱਚ_REMQUO):
    CASE_FLT_FN (BUILT_ਵਿੱਚ_RINT):
    CASE_FLT_FN_FLOATN_NX (BUILT_ਵਿੱਚ_RINT):
    CASE_FLT_FN (BUILT_ਵਿੱਚ_ਗੇੜਾ):
    CASE_FLT_FN_FLOATN_NX (BUILT_ਵਿੱਚ_ਗੇੜਾ):
    CASE_FLT_FN (BUILT_ਵਿੱਚ_SCALBLN):
    CASE_FLT_FN (BUILT_ਵਿੱਚ_SCALBN):
    CASE_FLT_FN (BUILT_ਵਿੱਚ_SIN):
    CASE_FLT_FN (BUILT_ਵਿੱਚ_SINH):
    CASE_FLT_FN (BUILT_ਵਿੱਚ_SINCOS):
    CASE_FLT_FN (BUILT_ਵਿੱਚ_SQRT):
    CASE_FLT_FN_FLOATN_NX (BUILT_ਵਿੱਚ_SQRT):
    CASE_FLT_FN (BUILT_ਵਿੱਚ_TAN):
    CASE_FLT_FN (BUILT_ਵਿੱਚ_TANH):
    CASE_FLT_FN (BUILT_ਵਿੱਚ_TGAMMA):
    CASE_FLT_FN (BUILT_ਵਿੱਚ_TRUNC):
    CASE_FLT_FN_FLOATN_NX (BUILT_ਵਿੱਚ_TRUNC):
    ਹਾਲਤ BUILT_ਵਿੱਚ_ISINF:
    ਹਾਲਤ BUILT_ਵਿੱਚ_ISNAN:
      ਵਾਪਸ "<math.h>";
    CASE_FLT_FN (BUILT_ਵਿੱਚ_CABS):
    CASE_FLT_FN (BUILT_ਵਿੱਚ_CACOS):
    CASE_FLT_FN (BUILT_ਵਿੱਚ_CACOSH):
    CASE_FLT_FN (BUILT_ਵਿੱਚ_CARG):
    CASE_FLT_FN (BUILT_ਵਿੱਚ_CASIN):
    CASE_FLT_FN (BUILT_ਵਿੱਚ_CASINH):
    CASE_FLT_FN (BUILT_ਵਿੱਚ_CATAN):
    CASE_FLT_FN (BUILT_ਵਿੱਚ_CATANH):
    CASE_FLT_FN (BUILT_ਵਿੱਚ_CCOS):
    CASE_FLT_FN (BUILT_ਵਿੱਚ_CCOSH):
    CASE_FLT_FN (BUILT_ਵਿੱਚ_CEXP):
    CASE_FLT_FN (BUILT_ਵਿੱਚ_CIMAG):
    CASE_FLT_FN (BUILT_ਵਿੱਚ_CLOG):
    CASE_FLT_FN (BUILT_ਵਿੱਚ_CONJ):
    CASE_FLT_FN (BUILT_ਵਿੱਚ_CPOW):
    CASE_FLT_FN (BUILT_ਵਿੱਚ_CPROJ):
    CASE_FLT_FN (BUILT_ਵਿੱਚ_CREAL):
    CASE_FLT_FN (BUILT_ਵਿੱਚ_CSIN):
    CASE_FLT_FN (BUILT_ਵਿੱਚ_CSINH):
    CASE_FLT_FN (BUILT_ਵਿੱਚ_CSQRT):
    CASE_FLT_FN (BUILT_ਵਿੱਚ_CTAN):
    CASE_FLT_FN (BUILT_ਵਿੱਚ_CTANH):
      ਵਾਪਸ "<complex.h>";
    ਹਾਲਤ BUILT_ਵਿੱਚ_MEMCHR:
    ਹਾਲਤ BUILT_ਵਿੱਚ_MEMCMP:
    ਹਾਲਤ BUILT_ਵਿੱਚ_MEMCPY:
    ਹਾਲਤ BUILT_ਵਿੱਚ_MEMMOVE:
    ਹਾਲਤ BUILT_ਵਿੱਚ_MEMSET:
    ਹਾਲਤ BUILT_ਵਿੱਚ_STRCAT:
    ਹਾਲਤ BUILT_ਵਿੱਚ_STRCHR:
    ਹਾਲਤ BUILT_ਵਿੱਚ_STRCMP:
    ਹਾਲਤ BUILT_ਵਿੱਚ_STRCPY:
    ਹਾਲਤ BUILT_ਵਿੱਚ_STRCSPN:
    ਹਾਲਤ BUILT_ਵਿੱਚ_STRLEN:
    ਹਾਲਤ BUILT_ਵਿੱਚ_STRNCAT:
    ਹਾਲਤ BUILT_ਵਿੱਚ_STRNCMP:
    ਹਾਲਤ BUILT_ਵਿੱਚ_STRNCPY:
    ਹਾਲਤ BUILT_ਵਿੱਚ_STRPBRK:
    ਹਾਲਤ BUILT_ਵਿੱਚ_STRRCHR:
    ਹਾਲਤ BUILT_ਵਿੱਚ_STRSPN:
    ਹਾਲਤ BUILT_ਵਿੱਚ_STRSTR:
      ਵਾਪਸ "<string.h>";
    ਹਾਲਤ BUILT_ਵਿੱਚ_FPRINTF:
    ਹਾਲਤ BUILT_ਵਿੱਚ_PUTC:
    ਹਾਲਤ BUILT_ਵਿੱਚ_FPUTC:
    ਹਾਲਤ BUILT_ਵਿੱਚ_FPUTS:
    ਹਾਲਤ BUILT_ਵਿੱਚ_FSCANF:
    ਹਾਲਤ BUILT_ਵਿੱਚ_FWRITE:
    ਹਾਲਤ BUILT_ਵਿੱਚ_PRINTF:
    ਹਾਲਤ BUILT_ਵਿੱਚ_PUTCHAR:
    ਹਾਲਤ BUILT_ਵਿੱਚ_PUTS:
    ਹਾਲਤ BUILT_ਵਿੱਚ_SCANF:
    ਹਾਲਤ BUILT_ਵਿੱਚ_SNPRINTF:
    ਹਾਲਤ BUILT_ਵਿੱਚ_SPRINTF:
    ਹਾਲਤ BUILT_ਵਿੱਚ_SSCANF:
    ਹਾਲਤ BUILT_ਵਿੱਚ_VFPRINTF:
    ਹਾਲਤ BUILT_ਵਿੱਚ_VFSCANF:
    ਹਾਲਤ BUILT_ਵਿੱਚ_VPRINTF:
    ਹਾਲਤ BUILT_ਵਿੱਚ_VSCANF:
    ਹਾਲਤ BUILT_ਵਿੱਚ_VSNPRINTF:
    ਹਾਲਤ BUILT_ਵਿੱਚ_VSPRINTF:
    ਹਾਲਤ BUILT_ਵਿੱਚ_VSSCANF:
      ਵਾਪਸ "<stdio.h>";
    ਹਾਲਤ BUILT_ਵਿੱਚ_ISALNUM:
    ਹਾਲਤ BUILT_ਵਿੱਚ_ISALPHA:
    ਹਾਲਤ BUILT_ਵਿੱਚ_ISBLANK:
    ਹਾਲਤ BUILT_ਵਿੱਚ_ISCNTRL:
    ਹਾਲਤ BUILT_ਵਿੱਚ_ISDIGIT:
    ਹਾਲਤ BUILT_ਵਿੱਚ_ISGRAPH:
    ਹਾਲਤ BUILT_ਵਿੱਚ_ISLOWER:
    ਹਾਲਤ BUILT_ਵਿੱਚ_ISPRINT:
    ਹਾਲਤ BUILT_ਵਿੱਚ_ISPUNCT:
    ਹਾਲਤ BUILT_ਵਿੱਚ_ISSPACE:
    ਹਾਲਤ BUILT_ਵਿੱਚ_ISUPPER:
    ਹਾਲਤ BUILT_ਵਿੱਚ_ISXDIGIT:
    ਹਾਲਤ BUILT_ਵਿੱਚ_TOLOWER:
    ਹਾਲਤ BUILT_ਵਿੱਚ_TOUPPER:
      ਵਾਪਸ "<ctype.h>";
    ਹਾਲਤ BUILT_ਵਿੱਚ_ISWALNUM:
    ਹਾਲਤ BUILT_ਵਿੱਚ_ISWALPHA:
    ਹਾਲਤ BUILT_ਵਿੱਚ_ISWBLANK:
    ਹਾਲਤ BUILT_ਵਿੱਚ_ISWCNTRL:
    ਹਾਲਤ BUILT_ਵਿੱਚ_ISWDIGIT:
    ਹਾਲਤ BUILT_ਵਿੱਚ_ISWGRAPH:
    ਹਾਲਤ BUILT_ਵਿੱਚ_ISWLOWER:
    ਹਾਲਤ BUILT_ਵਿੱਚ_ISWPRINT:
    ਹਾਲਤ BUILT_ਵਿੱਚ_ISWPUNCT:
    ਹਾਲਤ BUILT_ਵਿੱਚ_ISWSPACE:
    ਹਾਲਤ BUILT_ਵਿੱਚ_ISWUPPER:
    ਹਾਲਤ BUILT_ਵਿੱਚ_ISWXDIGIT:
    ਹਾਲਤ BUILT_ਵਿੱਚ_TOWLOWER:
    ਹਾਲਤ BUILT_ਵਿੱਚ_TOWUPPER:
      ਵਾਪਸ "<wctype.h>";
    ਹਾਲਤ BUILT_ਵਿੱਚ_ABORT:
    ਹਾਲਤ BUILT_ਵਿੱਚ_ABS:
    ਹਾਲਤ BUILT_ਵਿੱਚ_CALLOC:
    ਹਾਲਤ BUILT_ਵਿੱਚ_EXIT:
    ਹਾਲਤ BUILT_ਵਿੱਚ_FREE:
    ਹਾਲਤ BUILT_ਵਿੱਚ_LABS:
    ਹਾਲਤ BUILT_ਵਿੱਚ_LLABS:
    ਹਾਲਤ BUILT_ਵਿੱਚ_MALLOC:
    ਹਾਲਤ BUILT_ਵਿੱਚ_REALLOC:
    ਹਾਲਤ BUILT_ਵਿੱਚ_EXIT2:
    ਹਾਲਤ BUILT_ਵਿੱਚ_ALIGNED_ALLOC:
      ਵਾਪਸ "<stdlib.h>";
    ਹਾਲਤ BUILT_ਵਿੱਚ_IMAXABS:
      ਵਾਪਸ "<inttypes.h>";
    ਹਾਲਤ BUILT_ਵਿੱਚ_STRFTIME:
      ਵਾਪਸ "<time.h>";
    ਮੂਲ:
      ਵਾਪਸ ਨਿਰਾ;
    }
}

/* Generate an implicit declaration for identifier FUNCTIONID at LOC as a
   function of type int ().  */

ਰੁੱਖ
implicitly_declare (location_t loc, ਰੁੱਖ functionid)
{
  ਬਣਤਰ c_binding *b;
  ਰੁੱਖ decl = NULL_ਰੁੱਖ;
  ਰੁੱਖ asmspec_ਰੁੱਖ;

  ਲਈ (b = I_ਚਿੰਨ੍ਹ_BINDING (functionid); b; b = b->shadowed)
    {
      ਜੇ (B_ਵਿੱਚ_SCOPE (b, external_scope))
	{
	  decl = b->decl;
	  ਰੋਕੋ;
	}
    }

  ਜੇ (decl)
    {
      ਜੇ (ਰੁੱਖ_ਕੋਡ (decl) != FUNCTION_DECL)
	ਵਾਪਸ decl;

      /* FIXME: Objective-C has weird not-really-builtin functions
	 which are supposed to be visible automatically.  They wind up
	 in the external scope because they're pushed before the file
	 scope gets created.  Catch this here and rebind them into the
	 file scope.  */
      ਜੇ (!fndecl_built_ਵਿੱਚ_p (decl) && DECL_IS_UNDECLARED_BUILTIN (decl))
	{
	  bind (functionid, decl, file_scope,
		/*invisible=*/ਝੂਠ, /*nested=*/ਸੱਚ,
		DECL_ਸਰੋਤ_LOCATION (decl));
	  ਵਾਪਸ decl;
	}
      ਨਹੀਂਤਾਂ
	{
	  ਰੁੱਖ newtype = default_function_type;
	  ਜੇ (b->u.type)
	    ਰੁੱਖ_TYPE (decl) = b->u.type;
	  /* Implicit declaration of a function already declared
	     (somehow) in a different scope, or as a built-in.
	     If this is the first time this has happened, warn;
	     then recycle the old declaration but with the new type.  */
	  ਜੇ (!C_DECL_IMPLICIT (decl))
	    {
	      implicit_decl_permerror (loc, functionid, decl);
	      C_DECL_IMPLICIT (decl) = 1;
	    }
	  ਜੇ (fndecl_built_ਵਿੱਚ_p (decl))
	    {
	      newtype = c_build_type_attribute_variant (newtype,
							TYPE_ਗੁਣ
							(ਰੁੱਖ_TYPE (decl)));
	      ਜੇ (!comptypes (newtype, ਰੁੱਖ_TYPE (decl)))
		{
		  auto_diagnostic_ਸਮੂਹ d;
		  ਤਾਰਕਿਕ warned = warning_at (loc,
					    OPT_Wbuiltin_declaration_mismatch,
					    "incompatible implicit "
					    "declaration of built-in "
					    "function %qD", decl);
		  /* See if we can hint which header to include.  */
		  ਅਚਲ ਅੱਖਰ *ਸਿਰਲੇਖ = ਸਿਰਲੇਖ_for_builtin_fn (decl);
		  ਜੇ (ਸਿਰਲੇਖ != ਨਿਰਾ && warned)
		    {
		      rich_location richloc (ਸਤਰ_ਸਾਰਣੀ, loc);
		      maybe_ਜੋੜੋ_include_fixit (&richloc, ਸਿਰਲੇਖ, ਸੱਚ);
		      inform (&richloc,
			      "include %qs or provide a declaration of %qD",
			      ਸਿਰਲੇਖ, decl);
		    }
		  newtype = ਰੁੱਖ_TYPE (decl);
		}
	    }
	  ਨਹੀਂਤਾਂ
	    {
	      ਜੇ (!comptypes (newtype, ਰੁੱਖ_TYPE (decl)))
		{
		  auto_diagnostic_ਸਮੂਹ d;
		  error_at (loc, "incompatible implicit declaration of "
			    "function %qD", decl);
		  locate_old_decl (decl);
		}
	    }
	  b->u.type = ਰੁੱਖ_TYPE (decl);
	  ਰੁੱਖ_TYPE (decl) = newtype;
	  bind (functionid, decl, current_scope,
		/*invisible=*/ਝੂਠ, /*nested=*/ਸੱਚ,
		DECL_ਸਰੋਤ_LOCATION (decl));
	  ਵਾਪਸ decl;
	}
    }

  /* Not seen before.  */
  decl = build_decl (loc, FUNCTION_DECL, functionid, default_function_type);
  DECL_EXTERNAL (decl) = 1;
  ਰੁੱਖ_ਜਨਤਕ (decl) = 1;
  C_DECL_IMPLICIT (decl) = 1;
  implicit_decl_permerror (loc, functionid, 0);
  asmspec_ਰੁੱਖ = maybe_apply_renaming_pragma (decl, /*asmname=*/ਨਿਰਾ);
  ਜੇ (asmspec_ਰੁੱਖ)
    ਸੈੱਟ_user_assembler_name (decl, ਰੁੱਖ_STRING_ਸੂਚਕ (asmspec_ਰੁੱਖ));

  /* C89 says implicit declarations are in the innermost block.
     So we record the decl in the standard fashion.  */
  decl = pushdecl (decl);

  /* No need to call objc_check_decl here - it's a function type.  */
  rest_ਦਾ_decl_compilation (decl, 0, 0);

  /* Write a record describing this implicit function declaration
     to the prototypes file (if requested).  */
  gen_aux_info_ਰਿਕਾਰਡ (decl, 0, 1, 0);

  /* Possibly apply some default attributes to this implicit declaration.  */
  decl_ਗੁਣ (&decl, NULL_ਰੁੱਖ, 0);

  ਵਾਪਸ decl;
}

/* Issue an error message for a reference to an undeclared variable
   ID, including a reference to a builtin outside of function-call
   context.  Establish a binding of the identifier to error_mark_node
   in an appropriate scope, which will suppress further errors for the
   same identifier.  The error message should be given location LOC.  */
ਖਾਲੀ
undeclared_variable (location_t loc, ਰੁੱਖ id)
{
  ਸਥਿਰ ਤਾਰਕਿਕ already = ਝੂਠ;
  ਬਣਤਰ c_scope *scope;

  auto_diagnostic_ਸਮੂਹ d;
  ਜੇ (current_function_decl == NULL_ਰੁੱਖ)
    {
      name_hint guessed_id = lookup_name_fuzzy (id, FUZZY_LOOKUP_NAME, loc);
      ਜੇ (ਅਚਲ ਅੱਖਰ *suggestion = guessed_id.suggestion ())
	{
	  gcc_rich_location richloc (loc);
	  richloc.ਜੋੜੋ_fixit_replace (suggestion);
	  error_at (&richloc,
		    "%qE undeclared here (not in a function);"
		    " did you mean %qs?",
		    id, suggestion);
	}
      ਨਹੀਂਤਾਂ
	error_at (loc, "%qE undeclared here (not in a function)", id);
      scope = current_scope;
    }
  ਨਹੀਂਤਾਂ
    {
      ਜੇ (!objc_diagnose_ਨਿੱਜੀ_ivar (id))
	{
	  name_hint guessed_id = lookup_name_fuzzy (id, FUZZY_LOOKUP_NAME, loc);
	  ਜੇ (ਅਚਲ ਅੱਖਰ *suggestion = guessed_id.suggestion ())
	    {
	      gcc_rich_location richloc (loc);
	      richloc.ਜੋੜੋ_fixit_replace (suggestion);
	      error_at (&richloc,
			"%qE undeclared (first use in this function);"
			" did you mean %qs?",
			id, suggestion);
	    }
	  ਨਹੀਂਤਾਂ
	    error_at (loc, "%qE undeclared (first use in this function)", id);
	}
      ਜੇ (!already)
	{
          inform (loc, "each undeclared identifier is reported only"
                  " once for each function it appears in");
	  already = ਸੱਚ;
	}

      /* If we are parsing old-style parameter decls, current_function_decl
	 will be nonnull but current_function_scope will be null.  */
      scope = current_function_scope ? current_function_scope : current_scope;
    }
  bind (id, error_mark_ਗੰਢ, scope, /*invisible=*/ਝੂਠ, /*nested=*/ਝੂਠ,
	UNKNOWN_LOCATION);
}

/* Subroutine of lookup_label, declare_label, define_label: construct a
   LABEL_DECL with all the proper frills.  Also create a struct
   c_label_vars initialized for the current scope.  */

ਸਥਿਰ ਰੁੱਖ
make_label (location_t location, ਰੁੱਖ name, ਤਾਰਕਿਕ defining,
	    ਬਣਤਰ c_label_vars **p_label_vars)
{
  ਰੁੱਖ label = build_decl (location, LABEL_DECL, name, void_type_ਗੰਢ);
  DECL_CONTEXT (label) = current_function_decl;
  ਸੈੱਟ_DECL_ਬਹੁਲਕ (label, VOIDmode);

  c_label_vars *label_vars = ggc_alloc<c_label_vars> ();
  label_vars->shadowed = ਨਿਰਾ;
  ਸੈੱਟ_spot_bindings (&label_vars->label_bindings, defining);
  label_vars->decls_ਵਿੱਚ_scope = make_ਰੁੱਖ_ਸਦਿਸ਼ ();
  label_vars->gotos = ਨਿਰਾ;
  *p_label_vars = label_vars;

  ਵਾਪਸ label;
}

/* Get the LABEL_DECL corresponding to identifier NAME as a label.
   Create one if none exists so far for the current function.
   This is called when a label is used in a goto expression or
   has its address taken.  */

ਰੁੱਖ
lookup_label (ਰੁੱਖ name)
{
  ਰੁੱਖ label;
  ਬਣਤਰ c_label_vars *label_vars;

  ਜੇ (current_function_scope == 0)
    {
      error ("label %qE referenced outside of any function", name);
      ਵਾਪਸ NULL_ਰੁੱਖ;
    }

  /* Use a label already defined or ref'd with this name, but not if
     it is inherited from a containing function and wasn't declared
     using __label__.  */
  label = I_LABEL_DECL (name);
  ਜੇ (label && (DECL_CONTEXT (label) == current_function_decl
		|| C_DECLARED_LABEL_FLAG (label)))
    {
      /* If the label has only been declared, update its apparent
	 location to point here, for better diagnostics if it
	 turns out not to have been defined.  */
      ਜੇ (DECL_INITIAL (label) == NULL_ਰੁੱਖ)
	DECL_ਸਰੋਤ_LOCATION (label) = ਨਿਵੇਸ਼_location;
      ਵਾਪਸ label;
    }

  /* No label binding for that identifier; make one.  */
  label = make_label (ਨਿਵੇਸ਼_location, name, ਝੂਠ, &label_vars);

  /* Ordinary labels go in the current function scope.  */
  bind_label (name, label, current_function_scope, label_vars);

  ਵਾਪਸ label;
}

/* Issue a warning about DECL for a goto statement at GOTO_LOC going
   to LABEL.  */

ਸਥਿਰ ਖਾਲੀ
warn_about_goto (location_t goto_loc, ਰੁੱਖ label, ਰੁੱਖ decl)
{
  auto_diagnostic_ਸਮੂਹ d;
  ਜੇ (c_type_variably_modified_p (ਰੁੱਖ_TYPE (decl)))
    error_at (goto_loc,
	      "jump into scope of identifier with variably modified type");
  ਨਹੀਂਤਾਂ ਜੇ (flag_openmp
	   && lookup_attribute ("omp allocate", DECL_ਗੁਣ (decl)))
    error_at (goto_loc, "jump skips OpenMP %<allocate%> allocation");
  ਨਹੀਂਤਾਂ
    ਜੇ (!warning_at (goto_loc, OPT_Wjump_ਖੁੰਝਾਂ_init,
		     "jump skips variable initialization"))
      ਵਾਪਸ;
  inform (DECL_ਸਰੋਤ_LOCATION (label), "label %qD defined here", label);
  inform (DECL_ਸਰੋਤ_LOCATION (decl), "%qD declared here", decl);
}

/* Look up a label because of a goto statement.  This is like
   lookup_label, but also issues any appropriate warnings.  */

ਰੁੱਖ
lookup_label_for_goto (location_t loc, ਰੁੱਖ name)
{
  ਰੁੱਖ label;
  ਬਣਤਰ c_label_vars *label_vars;
  ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ix;
  ਰੁੱਖ decl;

  label = lookup_label (name);
  ਜੇ (label == NULL_ਰੁੱਖ)
    ਵਾਪਸ NULL_ਰੁੱਖ;

  /* If we are jumping to a different function, we can't issue any
     useful warnings.  */
  ਜੇ (DECL_CONTEXT (label) != current_function_decl)
    {
      gcc_assert (C_DECLARED_LABEL_FLAG (label));
      ਵਾਪਸ label;
    }

  label_vars = I_LABEL_BINDING (name)->u.label;

  /* If the label has not yet been defined, then push this goto on a
     list for possible later warnings.  */
  ਜੇ (label_vars->label_bindings.scope == ਨਿਰਾ)
    {
      c_goto_bindings *g = ggc_alloc<c_goto_bindings> ();

      g->loc = loc;
      ਸੈੱਟ_spot_bindings (&g->goto_bindings, ਸੱਚ);
      vec_ਸੁਰੱਖਿਅਤ_ਧੱਕੋ (label_vars->gotos, g);
      ਵਾਪਸ label;
    }

  /* If there are any decls in label_vars->decls_in_scope, then this
     goto has missed the declaration of the decl.  This happens for a
     case like
       int i = 1;
      lab:
       ...
       goto lab;
     Issue a warning or error.  */
  FOR_EACH_VEC_ਸੁਰੱਖਿਅਤ_ELT (label_vars->decls_ਵਿੱਚ_scope, ix, decl)
    warn_about_goto (loc, label, decl);

  ਜੇ (label_vars->label_bindings.ਖੱਬਾ_stmt_ਵਿਅੰਜਕ)
    {
      auto_diagnostic_ਸਮੂਹ d;
      error_at (loc, "jump into statement expression");
      inform (DECL_ਸਰੋਤ_LOCATION (label), "label %qD defined here", label);
    }

  ਵਾਪਸ label;
}

/* Make a label named NAME in the current function, shadowing silently
   any that may be inherited from containing functions or containing
   scopes.  This is called for __label__ declarations.  */

ਰੁੱਖ
declare_label (ਰੁੱਖ name)
{
  ਬਣਤਰ c_binding *b = I_LABEL_BINDING (name);
  ਰੁੱਖ label;
  ਬਣਤਰ c_label_vars *label_vars;

  /* Check to make sure that the label hasn't already been declared
     at this scope */
  ਜੇ (b && B_ਵਿੱਚ_CURRENT_SCOPE (b))
    {
      auto_diagnostic_ਸਮੂਹ d;
      error ("duplicate label declaration %qE", name);
      locate_old_decl (b->decl);

      /* Just use the previous declaration.  */
      ਵਾਪਸ b->decl;
    }

  label = make_label (ਨਿਵੇਸ਼_location, name, ਝੂਠ, &label_vars);
  C_DECLARED_LABEL_FLAG (label) = 1;

  /* Declared labels go in the current scope.  */
  bind_label (name, label, current_scope, label_vars);

  ਵਾਪਸ label;
}

/* When we define a label, issue any appropriate warnings if there are
   any gotos earlier in the function which jump to this label.  */

ਸਥਿਰ ਖਾਲੀ
check_earlier_gotos (ਰੁੱਖ label, ਬਣਤਰ c_label_vars* label_vars)
{
  ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ix;
  ਬਣਤਰ c_goto_bindings *g;

  FOR_EACH_VEC_ਸੁਰੱਖਿਅਤ_ELT (label_vars->gotos, ix, g)
    {
      ਬਣਤਰ c_binding *b;
      ਬਣਤਰ c_scope *scope;

      /* We have a goto to this label.  The goto is going forward.  In
	 g->scope, the goto is going to skip any binding which was
	 defined after g->bindings_in_scope.  */
      ਜੇ (g->goto_bindings.scope->has_jump_unsafe_decl)
	{
	  ਲਈ (b = g->goto_bindings.scope->bindings;
	       b != g->goto_bindings.bindings_ਵਿੱਚ_scope;
	       b = b->prev)
	    {
	      ਜੇ (decl_jump_unsafe (b->decl))
		warn_about_goto (g->loc, label, b->decl);
	    }
	}

      /* We also need to warn about decls defined in any scopes
	 between the scope of the label and the scope of the goto.  */
      ਲਈ (scope = label_vars->label_bindings.scope;
	   scope != g->goto_bindings.scope;
	   scope = scope->outer)
	{
	  gcc_assert (scope != ਨਿਰਾ);
	  ਜੇ (scope->has_jump_unsafe_decl)
	    {
	      ਜੇ (scope == label_vars->label_bindings.scope)
		b = label_vars->label_bindings.bindings_ਵਿੱਚ_scope;
	      ਨਹੀਂਤਾਂ
		b = scope->bindings;
	      ਲਈ (; b != ਨਿਰਾ; b = b->prev)
		{
		  ਜੇ (decl_jump_unsafe (b->decl))
		    warn_about_goto (g->loc, label, b->decl);
		}
	    }
	}

      ਜੇ (g->goto_bindings.stmt_exprs > 0)
	{
	  auto_diagnostic_ਸਮੂਹ d;
	  error_at (g->loc, "jump into statement expression");
	  inform (DECL_ਸਰੋਤ_LOCATION (label), "label %qD defined here",
		  label);
	}
    }

  /* Now that the label is defined, we will issue warnings about
     subsequent gotos to this label when we see them.  */
  vec_ਸੁਰੱਖਿਅਤ_truncate (label_vars->gotos, 0);
  label_vars->gotos = ਨਿਰਾ;
}

/* Define a label, specifying the location in the source file.
   Return the LABEL_DECL node for the label, if the definition is valid.
   Otherwise return NULL_TREE.  */

ਰੁੱਖ
define_label (location_t location, ਰੁੱਖ name)
{
  /* Find any preexisting label with this name.  It is an error
     if that label has already been defined in this function, or
     if there is a containing function with a declared label with
     the same name.  */
  ਰੁੱਖ label = I_LABEL_DECL (name);

  ਜੇ (label
      && ((DECL_CONTEXT (label) == current_function_decl
	   && DECL_INITIAL (label) != NULL_ਰੁੱਖ)
	  || (DECL_CONTEXT (label) != current_function_decl
	      && C_DECLARED_LABEL_FLAG (label))))
    {
      auto_diagnostic_ਸਮੂਹ d;
      error_at (location, "duplicate label %qD", label);
      locate_old_decl (label);
      ਵਾਪਸ NULL_ਰੁੱਖ;
    }
  ਨਹੀਂਤਾਂ ਜੇ (label && DECL_CONTEXT (label) == current_function_decl)
    {
      ਬਣਤਰ c_label_vars *label_vars = I_LABEL_BINDING (name)->u.label;

      /* The label has been used or declared already in this function,
	 but not defined.  Update its location to point to this
	 definition.  */
      DECL_ਸਰੋਤ_LOCATION (label) = location;
      ਸੈੱਟ_spot_bindings (&label_vars->label_bindings, ਸੱਚ);

      /* Issue warnings as required about any goto statements from
	 earlier in the function.  */
      check_earlier_gotos (label, label_vars);
    }
  ਨਹੀਂਤਾਂ
    {
      ਬਣਤਰ c_label_vars *label_vars;

      /* No label binding for that identifier; make one.  */
      label = make_label (location, name, ਸੱਚ, &label_vars);

      /* Ordinary labels go in the current function scope.  */
      bind_label (name, label, current_function_scope, label_vars);
    }

  ਜੇ (!ਵਿੱਚ_system_ਸਿਰਲੇਖ_at (ਨਿਵੇਸ਼_location) && lookup_name (name))
    warning_at (location, OPT_Wtraditional,
		"traditional C lacks a separate namespace "
		"for labels, identifier %qE conflicts", name);

  /* Mark label as having been defined.  */
  DECL_INITIAL (label) = error_mark_ਗੰਢ;
  ਵਾਪਸ label;
}

/* Get the bindings for a new switch statement.  This is used to issue
   warnings as appropriate for jumps from the switch to case or
   default labels.  */

ਬਣਤਰ c_spot_bindings *
c_get_switch_bindings (ਖਾਲੀ)
{
  ਬਣਤਰ c_spot_bindings *switch_bindings;

  switch_bindings = XNEW (ਬਣਤਰ c_spot_bindings);
  ਸੈੱਟ_spot_bindings (switch_bindings, ਸੱਚ);
  ਵਾਪਸ switch_bindings;
}

ਖਾਲੀ
c_release_switch_bindings (ਬਣਤਰ c_spot_bindings *bindings)
{
  gcc_assert (bindings->stmt_exprs == 0 && !bindings->ਖੱਬਾ_stmt_ਵਿਅੰਜਕ);
  XDELETE (bindings);
}

/* This is called at the point of a case or default label to issue
   warnings about decls as needed.  It returns true if it found an
   error, not just a warning.  */

ਤਾਰਕਿਕ
c_check_switch_jump_warnings (ਬਣਤਰ c_spot_bindings *switch_bindings,
			      location_t switch_loc, location_t case_loc)
{
  ਤਾਰਕਿਕ saw_error;
  ਬਣਤਰ c_scope *scope;

  saw_error = ਝੂਠ;
  ਲਈ (scope = current_scope;
       scope != switch_bindings->scope;
       scope = scope->outer)
    {
      ਬਣਤਰ c_binding *b;

      gcc_assert (scope != ਨਿਰਾ);

      ਜੇ (!scope->has_jump_unsafe_decl)
	ਜਾਰੀ;

      ਲਈ (b = scope->bindings; b != ਨਿਰਾ; b = b->prev)
	{
	  ਜੇ (decl_jump_unsafe (b->decl))
	    {
	      auto_diagnostic_ਸਮੂਹ d;
	      ਤਾਰਕਿਕ emitted;
	      ਜੇ (c_type_variably_modified_p (ਰੁੱਖ_TYPE (b->decl)))
		{
		  saw_error = ਸੱਚ;
		  error_at (case_loc,
			    "switch jumps into scope of identifier with "
			    "variably modified type");
		  emitted = ਸੱਚ;
		}
	      ਨਹੀਂਤਾਂ ਜੇ (flag_openmp
		       && lookup_attribute ("omp allocate",
					    DECL_ਗੁਣ (b->decl)))
		{
		  saw_error = ਸੱਚ;
		  error_at (case_loc,
			    "switch jumps over OpenMP %<allocate%> allocation");
		  emitted = ਸੱਚ;
		}
	      ਨਹੀਂਤਾਂ
		emitted
		  = warning_at (case_loc, OPT_Wjump_ਖੁੰਝਾਂ_init,
				"switch jumps over variable initialization");
	      ਜੇ (emitted)
		{
		  inform (switch_loc, "switch starts here");
		  inform (DECL_ਸਰੋਤ_LOCATION (b->decl), "%qD declared here",
			  b->decl);
		}
	    }
	}
    }

  ਜੇ (switch_bindings->stmt_exprs > 0)
    {
      saw_error = ਸੱਚ;
      auto_diagnostic_ਸਮੂਹ d;
      error_at (case_loc, "switch jumps into statement expression");
      inform (switch_loc, "switch starts here");
    }

  ਵਾਪਸ saw_error;
}

/* Given NAME, an IDENTIFIER_NODE,
   return the structure (or union or enum) definition for that name.
   If THISLEVEL_ONLY is nonzero, searches only the current_scope.
   CODE says which kind of type the caller wants;
   it is RECORD_TYPE or UNION_TYPE or ENUMERAL_TYPE.
   If PLOC is not NULL and this returns non-null, it sets *PLOC to the
   location where the tag was defined.
   If the wrong kind of type is found, an error is reported.  */

ਸਥਿਰ ਰੁੱਖ
lookup_ਟੈਗ (ਗਿਣਤੀ ਰੁੱਖ_ਕੋਡ_2 ਕੋਡ, ਰੁੱਖ name, ਤਾਰਕਿਕ thislevel_only,
	    location_t *ploc)
{
  ਬਣਤਰ c_binding *b = I_ਟੈਗ_BINDING (name);
  ਤਾਰਕਿਕ thislevel = ਝੂਠ;

  ਜੇ (!b || !b->decl)
    ਵਾਪਸ NULL_ਰੁੱਖ;

  /* We only care about whether it's in this level if
     thislevel_only was set or it might be a type clash.  */
  ਜੇ (thislevel_only || ਰੁੱਖ_ਕੋਡ (b->decl) != ਕੋਡ)
    {
      /* For our purposes, a tag in the external scope is the same as
	 a tag in the file scope.  (Primarily relevant to Objective-C
	 and its builtin structure tags, which get pushed before the
	 file scope is created.)  */
      ਜੇ (B_ਵਿੱਚ_CURRENT_SCOPE (b)
	  || (current_scope == file_scope && B_ਵਿੱਚ_EXTERNAL_SCOPE (b)))
	thislevel = ਸੱਚ;
    }

  ਜੇ (thislevel_only && !thislevel)
    ਵਾਪਸ NULL_ਰੁੱਖ;

  ਜੇ (ਰੁੱਖ_ਕੋਡ (b->decl) != ਕੋਡ)
    {
      /* Definition isn't the kind we were looking for.  */
      pending_invalid_xref = name;
      pending_invalid_xref_location = ਨਿਵੇਸ਼_location;

      /* If in the same binding level as a declaration as a tag
	 of a different type, this must not be allowed to
	 shadow that tag, so give the error immediately.
	 (For example, "struct foo; union foo;" is invalid.)  */
      ਜੇ (thislevel)
	pending_xref_error ();
    }

  ਜੇ (ploc != ਨਿਰਾ)
    *ploc = b->locus;

  ਵਾਪਸ b->decl;
}

/* Return true if a definition exists for NAME with code CODE.  */

ਤਾਰਕਿਕ
ਟੈਗ_exists_p (ਗਿਣਤੀ ਰੁੱਖ_ਕੋਡ_2 ਕੋਡ, ਰੁੱਖ name)
{
  ਬਣਤਰ c_binding *b = I_ਟੈਗ_BINDING (name);

  ਜੇ (b == ਨਿਰਾ || b->decl == NULL_ਰੁੱਖ)
    ਵਾਪਸ ਝੂਠ;
  ਵਾਪਸ ਰੁੱਖ_ਕੋਡ (b->decl) == ਕੋਡ;
}

/* Print an error message now
   for a recent invalid struct, union or enum cross reference.
   We don't print them immediately because they are not invalid
   when used in the `struct foo;' construct for shadowing.  */

ਖਾਲੀ
pending_xref_error (ਖਾਲੀ)
{
  ਜੇ (pending_invalid_xref != NULL_ਰੁੱਖ)
    error_at (pending_invalid_xref_location, "%qE defined as wrong kind of tag",
	      pending_invalid_xref);
  pending_invalid_xref = NULL_ਰੁੱਖ;
}


/* Look up NAME in the current scope and its superiors
   in the namespace of variables, functions and typedefs.
   Return a ..._DECL node of some kind representing its definition,
   or return NULL_TREE if it is undefined.  */

ਰੁੱਖ
lookup_name (ਰੁੱਖ name)
{
  ਬਣਤਰ c_binding *b = I_ਚਿੰਨ੍ਹ_BINDING (name);
  /* Do not resolve non-default function versions.  */
  ਜੇ (b
      && ਰੁੱਖ_ਕੋਡ (b->decl) == FUNCTION_DECL
      && DECL_FUNCTION_VERSIONED (b->decl)
      && !is_function_default_ਸੰਸਕਰਣ (b->decl))
    ਵਾਪਸ NULL_ਰੁੱਖ;
  ਜੇ (b && !b->invisible)
    {
      maybe_ਰਿਕਾਰਡ_typedef_use (b->decl);
      ਵਾਪਸ b->decl;
    }
  ਵਾਪਸ NULL_ਰੁੱਖ;
}

/* Similar to `lookup_name' but look only at the indicated scope.  */

ਸਥਿਰ ਰੁੱਖ
lookup_name_ਵਿੱਚ_scope (ਰੁੱਖ name, ਬਣਤਰ c_scope *scope)
{
  ਬਣਤਰ c_binding *b;

  ਲਈ (b = I_ਚਿੰਨ੍ਹ_BINDING (name); b; b = b->shadowed)
    ਜੇ (B_ਵਿੱਚ_SCOPE (b, scope))
      ਵਾਪਸ b->decl;
  ਵਾਪਸ NULL_ਰੁੱਖ;
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
lookup_name_fuzzy (ਰੁੱਖ name, ਗਿਣਤੀ lookup_name_fuzzy_ਕਿਸਮ ਕਿਸਮ, location_t loc)
{
  gcc_assert (ਰੁੱਖ_ਕੋਡ (name) == IDENTIFIER_ਗੰਢ);

  /* Look up function-like macros first; maybe misusing them. */
  ਸਵੈਚਾਲਿਤ cpp_ਗੰਢ = cpp_lookup (parse_ਵਿੱਚ,
			      (ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ*)IDENTIFIER_ਸੂਚਕ (name),
			      IDENTIFIER_ਲੰਮਾਈ (name));
  ਜੇ (cpp_ਗੰਢ && cpp_fun_like_macro_p (cpp_ਗੰਢ))
    ਵਾਪਸ name_hint
      (ਖਾਲੀ_ਸੂਚਕ,
       std::make_unique<macro_like_function_ਵਰਤਿਆ> (loc,
						   IDENTIFIER_ਸੂਚਕ (name)));

  /* Next, try some well-known names in the C standard library, in case
     the user forgot a #include.  */
  ਅਚਲ ਅੱਖਰ *ਸਿਰਲੇਖ_hint
    = get_c_stdlib_ਸਿਰਲੇਖ_for_name (IDENTIFIER_ਸੂਚਕ (name));

  ਜੇ (ਸਿਰਲੇਖ_hint)
    ਵਾਪਸ name_hint
      (ਖਾਲੀ_ਸੂਚਕ,
       std::make_unique<suggest_missing_ਸਿਰਲੇਖ> (loc,
						 IDENTIFIER_ਸੂਚਕ (name),
						 ਸਿਰਲੇਖ_hint));

  /* Next, look for exact matches for builtin defines that would have been
     defined if the user had passed a command-line option (e.g. -fopenmp
     for "_OPENMP").  */
  diagnostics::option_id option_id
    = get_option_for_builtin_define (IDENTIFIER_ਸੂਚਕ (name));
  ਜੇ (option_id.m_idx > 0)
    ਵਾਪਸ name_hint
      (ਖਾਲੀ_ਸੂਚਕ,
       std::make_unique<suggest_missing_option> (loc,
						 IDENTIFIER_ਸੂਚਕ (name),
						 option_id));

  /* Only suggest names reserved for the implementation if NAME begins
     with an underscore.  */
  ਤਾਰਕਿਕ consider_implementation_ਨਾਂ = (IDENTIFIER_ਸੂਚਕ (name)[0] == '_');

  ਉੱਤਮ_ਮੇਲ<ਰੁੱਖ, ਰੁੱਖ> bm (name);

  /* Look within currently valid scopes.  */
  ਲਈ (c_scope *scope = current_scope; scope; scope = scope->outer)
    ਲਈ (c_binding *binding = scope->bindings; binding; binding = binding->prev)
      {
	ਜੇ (!binding->id || binding->invisible)
	  ਜਾਰੀ;
	ਜੇ (binding->decl == error_mark_ਗੰਢ)
	  ਜਾਰੀ;
	/* Don't use bindings from implicitly declared functions,
	   as they were likely misspellings themselves.  */
	ਜੇ (ਰੁੱਖ_ਕੋਡ (binding->decl) == FUNCTION_DECL)
	  ਜੇ (C_DECL_IMPLICIT (binding->decl))
	    ਜਾਰੀ;
	/* Don't suggest names that are reserved for use by the
	   implementation, unless NAME began with an underscore.  */
	ਜੇ (!consider_implementation_ਨਾਂ)
	  {
	    ਅਚਲ ਅੱਖਰ *suggestion_str = IDENTIFIER_ਸੂਚਕ (binding->id);
	    ਜੇ (name_reserved_for_implementation_p (suggestion_str))
	      ਜਾਰੀ;
	  }
	ਚੋਣ (ਕਿਸਮ)
	  {
	  ਹਾਲਤ FUZZY_LOOKUP_TYPENAME:
	    ਜੇ (ਰੁੱਖ_ਕੋਡ (binding->decl) != TYPE_DECL)
	      ਜਾਰੀ;
	    ਰੋਕੋ;

	  ਹਾਲਤ FUZZY_LOOKUP_FUNCTION_NAME:
	    ਜੇ (ਰੁੱਖ_ਕੋਡ (binding->decl) != FUNCTION_DECL)
	      {
		/* Allow function pointers.  */
		ਜੇ ((VAR_P (binding->decl)
		     || ਰੁੱਖ_ਕੋਡ (binding->decl) == PARM_DECL)
		    && ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (binding->decl)) == ਸੂਚਕ_TYPE
		    && (ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (ਰੁੱਖ_TYPE (binding->decl)))
			== FUNCTION_TYPE))
		  ਰੋਕੋ;
		ਜਾਰੀ;
	      }
	    ਰੋਕੋ;

	  ਮੂਲ:
	    ਰੋਕੋ;
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
  ਉੱਤਮ_macro_ਮੇਲ bmm (name, bm.get_ਉੱਤਮ_ਦੂਰੀ (), parse_ਵਿੱਚ);
  cpp_hashnode *ਉੱਤਮ_macro = bmm.get_ਉੱਤਮ_meaningful_candidate ();
  /* If a macro is the closest so far to NAME, use it, creating an
     identifier tree node for it.  */
  ਜੇ (ਉੱਤਮ_macro)
    {
      ਅਚਲ ਅੱਖਰ *id = (ਅਚਲ ਅੱਖਰ *)ਉੱਤਮ_macro->ident.str;
      ਰੁੱਖ macro_as_identifier
	= get_identifier_with_ਲੰਮਾਈ (id, ਉੱਤਮ_macro->ident.len);
      bm.ਸੈੱਟ_ਉੱਤਮ_so_far (macro_as_identifier,
			  bmm.get_ਉੱਤਮ_ਦੂਰੀ (),
			  bmm.get_ਉੱਤਮ_candidate_ਲੰਮਾਈ ());
    }

  /* Try the "start_typename" keywords to detect
     "singed" vs "signed" typos.  */
  ਜੇ (ਕਿਸਮ == FUZZY_LOOKUP_TYPENAME)
    {
      ਲਈ (ਬਿਨਾਨਿਸ਼ਾਨੀ i = 0; i < ਅੰਕ_c_common_reswords; i++)
	{
	  ਅਚਲ c_common_resword *resword = &c_common_reswords[i];
	  ਜੇ (!c_keyword_starts_typename (resword->rid))
	    ਜਾਰੀ;
	  ਰੁੱਖ resword_identifier = ridpointers [resword->rid];
	  ਜੇ (!resword_identifier)
	    ਜਾਰੀ;
	  gcc_assert (ਰੁੱਖ_ਕੋਡ (resword_identifier) == IDENTIFIER_ਗੰਢ);
	  bm.consider (resword_identifier);
	}
    }

  ਰੁੱਖ ਉੱਤਮ = bm.get_ਉੱਤਮ_meaningful_candidate ();
  ਜੇ (ਉੱਤਮ)
    ਵਾਪਸ name_hint (IDENTIFIER_ਸੂਚਕ (ਉੱਤਮ), ਨਿਰਾ);
  ਨਹੀਂਤਾਂ
    ਵਾਪਸ name_hint (ਨਿਰਾ, ਨਿਰਾ);
}


/* Handle the standard [[nodiscard]] attribute.  */

ਸਥਿਰ ਰੁੱਖ
handle_nodiscard_attribute (ਰੁੱਖ *ਗੰਢ, ਰੁੱਖ name, ਰੁੱਖ /*ਦਲੀਲਾਂ*/,
			    ਪੂਰਨ /*flags*/, ਤਾਰਕਿਕ *no_ਜੋੜੋ_attrs)
{
  ਜੇ (ਰੁੱਖ_ਕੋਡ (*ਗੰਢ) == FUNCTION_DECL)
    {
      ਜੇ (VOID_TYPE_P (ਰੁੱਖ_TYPE (ਰੁੱਖ_TYPE (*ਗੰਢ))))
	warning_at (DECL_ਸਰੋਤ_LOCATION (*ਗੰਢ),
		    OPT_Wattributes, "%qE attribute applied to %qD with void "
		    "return type", name, *ਗੰਢ);
    }
  ਨਹੀਂਤਾਂ ਜੇ (ਰਿਕਾਰਡ_OR_UNION_TYPE_P (*ਗੰਢ)
	   || ਰੁੱਖ_ਕੋਡ (*ਗੰਢ) == ENUMERAL_TYPE)
    /* OK */;
  ਨਹੀਂਤਾਂ
    {
      pedwarn (ਨਿਵੇਸ਼_location,
	       OPT_Wattributes, "%qE attribute can only be applied to "
	       "functions or to structure, union or enumeration types", name);
      *no_ਜੋੜੋ_attrs = ਸੱਚ;
    }
  ਵਾਪਸ NULL_ਰੁੱਖ;
}

/* Handle the standard [[noreturn]] attribute.  */

ਸਥਿਰ ਰੁੱਖ
handle_std_noreturn_attribute (ਰੁੱਖ *ਗੰਢ, ਰੁੱਖ name, ਰੁੱਖ ਦਲੀਲਾਂ,
			       ਪੂਰਨ flags, ਤਾਰਕਿਕ *no_ਜੋੜੋ_attrs)
{
  /* Unlike GNU __attribute__ ((noreturn)), the standard [[noreturn]]
     only applies to functions, not function pointers.  */
  ਜੇ (ਰੁੱਖ_ਕੋਡ (*ਗੰਢ) == FUNCTION_DECL)
    ਵਾਪਸ handle_noreturn_attribute (ਗੰਢ, name, ਦਲੀਲਾਂ, flags, no_ਜੋੜੋ_attrs);
  ਨਹੀਂਤਾਂ
    {
      pedwarn (ਨਿਵੇਸ਼_location, OPT_Wattributes,
	       "standard %qE attribute can only be applied to functions",
	       name);
      *no_ਜੋੜੋ_attrs = ਸੱਚ;
      ਵਾਪਸ NULL_ਰੁੱਖ;
    }
}

/* Handle the standard [[unsequenced]] attribute.  */

ਸਥਿਰ ਰੁੱਖ
handle_std_unsequenced_attribute (ਰੁੱਖ *ਗੰਢ, ਰੁੱਖ name, ਰੁੱਖ ਦਲੀਲਾਂ,
				  ਪੂਰਨ flags, ਤਾਰਕਿਕ *no_ਜੋੜੋ_attrs)
{
  /* Unlike GNU __attribute__ ((unsequenced)), the standard [[unsequenced]]
     should be only applied to function declarators or type specifiers which
     have function type.  */
  ਜੇ (ਗੰਢ[2])
    {
      auto_diagnostic_ਸਮੂਹ d;
      ਜੇ (pedwarn (ਨਿਵੇਸ਼_location, OPT_Wattributes,
		   "standard %qE attribute can only be applied to function "
		   "declarators or type specifiers with function type", name))
	inform (ਨਿਵੇਸ਼_location, "did you mean to specify it after %<)%> "
				"following function parameters?");
      *no_ਜੋੜੋ_attrs = ਸੱਚ;
      ਵਾਪਸ NULL_ਰੁੱਖ;
    }
  ਵਾਪਸ handle_unsequenced_attribute (ਗੰਢ, name, ਦਲੀਲਾਂ, flags, no_ਜੋੜੋ_attrs);
}

/* Handle the standard [[reproducible]] attribute.  */

ਸਥਿਰ ਰੁੱਖ
handle_std_reproducible_attribute (ਰੁੱਖ *ਗੰਢ, ਰੁੱਖ name, ਰੁੱਖ ਦਲੀਲਾਂ,
				   ਪੂਰਨ flags, ਤਾਰਕਿਕ *no_ਜੋੜੋ_attrs)
{
  ਵਾਪਸ handle_std_unsequenced_attribute (ਗੰਢ, name, ਦਲੀਲਾਂ, flags,
					   no_ਜੋੜੋ_attrs);
}

/* Table of supported standard (C23) attributes.  */
ਸਥਿਰ ਅਚਲ attribute_spec std_ਗੁਣ[] =
{
  /* { name, min_len, max_len, decl_req, type_req, fn_type_req,
       affects_type_identity, handler, exclude } */
  { "_Noreturn", 0, 0, ਝੂਠ, ਝੂਠ, ਝੂਠ, ਝੂਠ,
    handle_std_noreturn_attribute, ਨਿਰਾ },
  { "deprecated", 0, 1, ਝੂਠ, ਝੂਠ, ਝੂਠ, ਝੂਠ,
    handle_deprecated_attribute, ਨਿਰਾ },
  { "fallthrough", 0, 0, ਝੂਠ, ਝੂਠ, ਝੂਠ, ਝੂਠ,
    handle_fallthrough_attribute, ਨਿਰਾ },
  { "maybe_unused", 0, 0, ਝੂਠ, ਝੂਠ, ਝੂਠ, ਝੂਠ,
    handle_ਅਣਵਰਤਿਆ_attribute, ਨਿਰਾ },
  { "nodiscard", 0, 1, ਝੂਠ, ਝੂਠ, ਝੂਠ, ਝੂਠ,
    handle_nodiscard_attribute, ਨਿਰਾ },
  { "noreturn", 0, 0, ਝੂਠ, ਝੂਠ, ਝੂਠ, ਝੂਠ,
    handle_std_noreturn_attribute, ਨਿਰਾ },
  { "reproducible", 0, 0, ਝੂਠ, ਸੱਚ, ਸੱਚ, ਝੂਠ,
    handle_std_reproducible_attribute, ਨਿਰਾ },
  { "unsequenced", 0, 0, ਝੂਠ, ਸੱਚ, ਸੱਚ, ਝੂਠ,
    handle_std_unsequenced_attribute, ਨਿਰਾ }
};

ਅਚਲ scoped_attribute_specs std_attribute_ਸਾਰਣੀ =
{
  ਖਾਲੀ_ਸੂਚਕ, { std_ਗੁਣ }
};

/* Create the predefined scalar types of C,
   and some nodes representing standard constants (0, 1, (void *) 0).
   Initialize the global scope.
   Make definitions for built-in primitive functions.  */

ਖਾਲੀ
c_init_decl_processing (ਖਾਲੀ)
{
  location_t save_loc = ਨਿਵੇਸ਼_location;

  /* Initialize reserved words for parser.  */
  c_parse_init ();

  current_function_decl = NULL_ਰੁੱਖ;

  gcc_obstack_init (&parser_obstack);

  /* Make the externals scope.  */
  ਧੱਕੋ_scope ();
  external_scope = current_scope;

  /* Declarations from c_common_nodes_and_builtins must not be associated
     with this input file, lest we get differences between using and not
     using preprocessed headers.  */
  ਨਿਵੇਸ਼_location = BUILTINS_LOCATION;

  c_common_nodes_and_builtins ();

  /* In C, comparisons and TRUTH_* expressions have type int.  */
  truthvalue_type_ਗੰਢ = integer_type_ਗੰਢ;
  truthvalue_true_ਗੰਢ = integer_one_ਗੰਢ;
  truthvalue_false_ਗੰਢ = integer_zero_ਗੰਢ;

  /* Even in C99, which has a real boolean type.  */
  pushdecl (build_decl (UNKNOWN_LOCATION, TYPE_DECL,
			get_identifier (flag_isoc23 ? "bool" : "_Bool"),
			boolean_type_ਗੰਢ));

  /* C-specific nullptr initialization.  */
  ਰਿਕਾਰਡ_builtin_type (RID_MAX, "typeof (nullptr)", nullptr_type_ਗੰਢ);
  /* The size and alignment of nullptr_t is the same as for a pointer to
     character type.  */
  ਸੈੱਟ_TYPE_ALIGN (nullptr_type_ਗੰਢ, GET_ਬਹੁਲਕ_ALIGNMENT (ptr_ਬਹੁਲਕ));

  ਨਿਵੇਸ਼_location = save_loc;

  make_fname_decl = c_make_fname_decl;
  ਸ਼ੁਰੂ_fname_decls ();

  ਜੇ (warn_keyword_macro)
    {
      ਲਈ (ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ i = 0; i < ਅੰਕ_c_common_reswords; ++i)
	/* For C register keywords which don't start with underscore
	   or start with just single underscore.  Don't complain about
	   ObjC or Transactional Memory keywords.  */
	ਜੇ (c_common_reswords[i].ਸ਼ਬਦ[0] == '_'
	    && c_common_reswords[i].ਸ਼ਬਦ[1] == '_')
	  ਜਾਰੀ;
	ਨਹੀਂਤਾਂ ਜੇ (c_common_reswords[i].disable
		 & (D_TRANSMEM | D_OBJC | D_CXX_OBJC))
	  ਜਾਰੀ;
	ਨਹੀਂਤਾਂ
	  {
	    ਰੁੱਖ id = get_identifier (c_common_reswords[i].ਸ਼ਬਦ);
	    ਜੇ (C_IS_RESERVED_ਸ਼ਬਦ (id)
		&& C_RID_ਕੋਡ (id) != RID_CXX_COMPAT_WARN)
	      cpp_warn (parse_ਵਿੱਚ, IDENTIFIER_ਸੂਚਕ (id),
			IDENTIFIER_ਲੰਮਾਈ (id));
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

ਸਥਿਰ ਰੁੱਖ
c_make_fname_decl (location_t loc, ਰੁੱਖ id, ਪੂਰਨ type_dep)
{
  ਅਚਲ ਅੱਖਰ *name = fname_as_string (type_dep);
  ਰੁੱਖ decl, type, init;
  ਮਾਪ_t ਲੰਮਾਈ = ਲੜੀ_ਲੰਬਾਈ (name);

  type = c_build_array_type (char_type_ਗੰਢ,
			     build_ਸੂਚਕਾਂਕ_type (ਮਾਪ_int (ਲੰਮਾਈ)));
  type = c_build_qualified_type (type, TYPE_QUAL_CONST);

  decl = build_decl (loc, VAR_DECL, id, type);

  ਰੁੱਖ_STATIC (decl) = 1;
  ਰੁੱਖ_READONLY (decl) = 1;
  DECL_ARTIFICIAL (decl) = 1;

  init = build_string (ਲੰਮਾਈ + 1, name);
  ਮੁਕਤ (const_cast<ਅੱਖਰ *> (name));
  ਰੁੱਖ_TYPE (init) = type;
  DECL_INITIAL (decl) = init;

  ਰੁੱਖ_ਵਰਤਿਆ (decl) = 1;

  ਜੇ (current_function_decl
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
	    /*invisible=*/ਝੂਠ, /*nested=*/ਝੂਠ, UNKNOWN_LOCATION);
    }

  ਅੰਤ_decl (decl, loc, init, NULL_ਰੁੱਖ, NULL_ਰੁੱਖ);

  ਵਾਪਸ decl;
}

ਰੁੱਖ
c_builtin_function (ਰੁੱਖ decl)
{
  ਰੁੱਖ type = ਰੁੱਖ_TYPE (decl);
  ਰੁੱਖ   id = DECL_NAME (decl);

  ਅਚਲ ਅੱਖਰ *name = IDENTIFIER_ਸੂਚਕ (id);
  C_DECL_BUILTIN_PROTOTYPE (decl) = prototype_p (type);

  /* Should never be called on a symbol with a preexisting meaning.  */
  gcc_assert (!I_ਚਿੰਨ੍ਹ_BINDING (id));

  bind (id, decl, external_scope, /*invisible=*/ਸੱਚ, /*nested=*/ਝੂਠ,
	UNKNOWN_LOCATION);

  /* Builtins in the implementation namespace are made visible without
     needing to be explicitly declared.  See push_file_scope.  */
  ਜੇ (name[0] == '_' && (name[1] == '_' || ISUPPER (name[1])))
    {
      DECL_CHAIN (decl) = visible_builtins;
      visible_builtins = decl;
    }

  ਵਾਪਸ decl;
}

ਰੁੱਖ
c_builtin_function_ext_scope (ਰੁੱਖ decl)
{
  ਰੁੱਖ type = ਰੁੱਖ_TYPE (decl);
  ਰੁੱਖ   id = DECL_NAME (decl);

  ਅਚਲ ਅੱਖਰ *name = IDENTIFIER_ਸੂਚਕ (id);
  C_DECL_BUILTIN_PROTOTYPE (decl) = prototype_p (type);

  ਜੇ (external_scope)
    bind (id, decl, external_scope, /*invisible=*/ਝੂਠ, /*nested=*/ਝੂਠ,
	  UNKNOWN_LOCATION);

  /* Builtins in the implementation namespace are made visible without
     needing to be explicitly declared.  See push_file_scope.  */
  ਜੇ (name[0] == '_' && (name[1] == '_' || ISUPPER (name[1])))
    {
      DECL_CHAIN (decl) = visible_builtins;
      visible_builtins = decl;
    }

  ਵਾਪਸ decl;
}

/* Implement LANG_HOOKS_SIMULATE_BUILTIN_FUNCTION_DECL.  */

ਰੁੱਖ
c_simulate_builtin_function_decl (ਰੁੱਖ decl)
{
  ਰੁੱਖ type = ਰੁੱਖ_TYPE (decl);
  C_DECL_BUILTIN_PROTOTYPE (decl) = prototype_p (type);
  ਵਾਪਸ pushdecl (decl);
}

/* Warn about attributes in a context where they are unused
   (attribute-declarations, except for the "fallthrough" case, and
   attributes on statements).  */

ਖਾਲੀ
c_warn_ਅਣਵਰਤਿਆ_ਗੁਣ (ਰੁੱਖ attrs)
{
  ਲਈ (ਰੁੱਖ t = attrs; t != NULL_ਰੁੱਖ; t = ਰੁੱਖ_CHAIN (t))
    ਜੇ (get_attribute_namespace (t) == NULL_ਰੁੱਖ)
      /* The specifications of standard attributes mean this is a
	 constraint violation.  */
      pedwarn (ਨਿਵੇਸ਼_location, OPT_Wattributes, "%qE attribute ignored",
	       get_attribute_name (t));
    ਨਹੀਂਤਾਂ ਜੇ (!attribute_ignored_p (t))
      warning (OPT_Wattributes, "%qE attribute ignored",
	       get_attribute_name (t));
}

/* Warn for standard attributes being applied to a type that is not
   being defined, where that is a constraint violation, and return a
   list of attributes with them removed.  */

ਰੁੱਖ
c_warn_type_ਗੁਣ (ਰੁੱਖ type, ਰੁੱਖ attrs)
{
  ਰੁੱਖ *attr_ptr = &attrs;
  ਜਦੋਂ (*attr_ptr)
    ਜੇ (get_attribute_namespace (*attr_ptr) == NULL_ਰੁੱਖ)
      {
	ਜੇ (ਰੁੱਖ_ਕੋਡ (type) == FUNCTION_TYPE)
	  {
	    ਰੁੱਖ name = get_attribute_name (*attr_ptr);
	    /* [[unsequenced]] and [[reproducible]] is fine on function
	       types that aren't being defined.  */
	    ਜੇ (is_attribute_p ("unsequenced", name)
		|| is_attribute_p ("reproducible", name))
	      {
		attr_ptr = &ਰੁੱਖ_CHAIN (*attr_ptr);
		ਜਾਰੀ;
	      }
	  }
	pedwarn (ਨਿਵੇਸ਼_location, OPT_Wattributes, "%qE attribute ignored",
		 get_attribute_name (*attr_ptr));
	*attr_ptr = ਰੁੱਖ_CHAIN (*attr_ptr);
      }
    ਨਹੀਂਤਾਂ
      attr_ptr = &ਰੁੱਖ_CHAIN (*attr_ptr);
  ਵਾਪਸ attrs;
}

/* Called when a declaration is seen that contains no names to declare.
   If its type is a reference to a structure, union or enum inherited
   from a containing scope, shadow that tag name for the current scope
   with a forward reference.
   If its type defines a new named structure or union
   or defines an enum, it is valid but we need not do anything here.
   Otherwise, it is an error.  */

ਖਾਲੀ
shadow_ਟੈਗ (ਅਚਲ ਬਣਤਰ c_declspecs *declspecs)
{
  shadow_ਟੈਗ_warned (declspecs, 0);
}

/* WARNED is 1 if we have done a pedwarn, 2 if we have done a warning,
   but no pedwarn.  */
ਖਾਲੀ
shadow_ਟੈਗ_warned (ਅਚਲ ਬਣਤਰ c_declspecs *declspecs, ਪੂਰਨ warned)
{
  ਤਾਰਕਿਕ ਮਿਲਿਆ_ਟੈਗ = ਝੂਠ;

  ਜੇ (declspecs->type && !declspecs->default_int_p && !declspecs->typedef_p)
    {
      ਰੁੱਖ ਮੁੱਲ = declspecs->type;
      ਗਿਣਤੀ ਰੁੱਖ_ਕੋਡ_2 ਕੋਡ = ਰੁੱਖ_ਕੋਡ (ਮੁੱਲ);

      ਜੇ (ਕੋਡ == ਰਿਕਾਰਡ_TYPE || ਕੋਡ == UNION_TYPE || ਕੋਡ == ENUMERAL_TYPE)
	/* Used to test also that TYPE_SIZE (value) != 0.
	   That caused warning for `struct foo;' at top level in the file.  */
	{
	  ਰੁੱਖ name = TYPE_NAME (ਮੁੱਲ);
	  ਰੁੱਖ t;

	  ਮਿਲਿਆ_ਟੈਗ = ਸੱਚ;

	  ਜੇ (declspecs->restrict_p)
	    {
	      error ("invalid use of %<restrict%>");
	      warned = 1;
	    }

	  ਜੇ (ਵਿੱਚ_underspecified_init)
	    {
	      /* This can only occur with extensions such as statement
		 expressions, but is still appropriate as an error to
		 avoid types declared in such a context escaping to
		 the type of an auto variable.  */
	      error ("%qT declared in underspecified object initializer",
		     ਮੁੱਲ);
	      warned = 1;
	    }

	  ਜੇ (name == NULL_ਰੁੱਖ)
	    {
	      ਜੇ (warned != 1 && ਕੋਡ != ENUMERAL_TYPE)
		/* Empty unnamed enum OK */
		{
		  pedwarn (ਨਿਵੇਸ਼_location, 0,
			   "unnamed struct/union that defines no instances");
		  warned = 1;
		}
	    }
	  ਨਹੀਂਤਾਂ ਜੇ (declspecs->typespec_ਕਿਸਮ != ctsk_tagdef
                   && declspecs->typespec_ਕਿਸਮ != ctsk_tagfirstref
		   && declspecs->typespec_ਕਿਸਮ != ctsk_tagfirstref_attrs
		   && declspecs->storage_class != csc_none)
	    {
	      ਜੇ (warned != 1)
		pedwarn (ਨਿਵੇਸ਼_location, 0,
			 "empty declaration with storage class specifier "
			 "does not redeclare tag");
	      warned = 1;
	      pending_xref_error ();
	    }
	  ਨਹੀਂਤਾਂ ਜੇ (declspecs->typespec_ਕਿਸਮ != ctsk_tagdef
                   && declspecs->typespec_ਕਿਸਮ != ctsk_tagfirstref
                   && declspecs->typespec_ਕਿਸਮ != ctsk_tagfirstref_attrs
		   && (declspecs->const_p
		       || declspecs->volatile_p
		       || declspecs->atomic_p
		       || declspecs->restrict_p
		       || declspecs->ਪਤਾ_space))
	    {
	      ਜੇ (warned != 1)
		pedwarn (ਨਿਵੇਸ਼_location, 0,
			 "empty declaration with type qualifier "
			  "does not redeclare tag");
	      warned = 1;
	      pending_xref_error ();
	    }
	  ਨਹੀਂਤਾਂ ਜੇ (declspecs->typespec_ਕਿਸਮ != ctsk_tagdef
                   && declspecs->typespec_ਕਿਸਮ != ctsk_tagfirstref
                   && declspecs->typespec_ਕਿਸਮ != ctsk_tagfirstref_attrs
		   && declspecs->alignas_p)
	    {
	      ਜੇ (warned != 1)
		pedwarn (ਨਿਵੇਸ਼_location, 0,
			 "empty declaration with %<_Alignas%> "
			  "does not redeclare tag");
	      warned = 1;
	      pending_xref_error ();
	    }
	  ਨਹੀਂਤਾਂ ਜੇ (declspecs->typespec_ਕਿਸਮ != ctsk_tagdef
		   && declspecs->typespec_ਕਿਸਮ != ctsk_tagfirstref
		   && declspecs->typespec_ਕਿਸਮ != ctsk_tagfirstref_attrs
		   && ਕੋਡ == ENUMERAL_TYPE
		   && !declspecs->enum_type_specifier_ref_p)
	    {
	      ਤਾਰਕਿਕ warned_enum = ਝੂਠ;
	      ਜੇ (warned != 1)
		warned_enum = pedwarn (ਨਿਵੇਸ਼_location, OPT_Wpedantic,
				       "empty declaration of %<enum%> type "
				       "does not redeclare tag");
	      ਜੇ (warned_enum)
		warned = 1;
	      pending_xref_error ();
	    }
	  ਨਹੀਂਤਾਂ
	    {
	      pending_invalid_xref = NULL_ਰੁੱਖ;
	      t = lookup_ਟੈਗ (ਕੋਡ, name, ਸੱਚ, ਨਿਰਾ);

	      ਜੇ (t == NULL_ਰੁੱਖ)
		{
		  t = make_ਗੰਢ (ਕੋਡ);
		  ਜੇ (flag_isoc23 || ਕੋਡ == ENUMERAL_TYPE)
		    ਸੈੱਟ_TYPE_STRUCTURAL_EQUALITY (t);
		  pushtag (ਨਿਵੇਸ਼_location, name, t);
		}
	    }
	}
      ਨਹੀਂਤਾਂ
	{
	  ਜੇ (warned != 1 && !ਵਿੱਚ_system_ਸਿਰਲੇਖ_at (ਨਿਵੇਸ਼_location))
	    {
	      pedwarn (ਨਿਵੇਸ਼_location, 0,
		       "useless type name in empty declaration");
	      warned = 1;
	    }
	}
    }
  ਨਹੀਂਤਾਂ ਜੇ (warned != 1 && !ਵਿੱਚ_system_ਸਿਰਲੇਖ_at (ਨਿਵੇਸ਼_location)
	   && declspecs->typedef_p)
    {
      pedwarn (ਨਿਵੇਸ਼_location, 0, "useless type name in empty declaration");
      warned = 1;
    }

  pending_invalid_xref = NULL_ਰੁੱਖ;

  ਜੇ (declspecs->inline_p)
    {
      error ("%<inline%> in empty declaration");
      warned = 1;
    }

  ਜੇ (declspecs->noreturn_p)
    {
      error ("%<_Noreturn%> in empty declaration");
      warned = 1;
    }

  ਜੇ (declspecs->constexpr_p)
    {
      error ("%<constexpr%> in empty declaration");
      warned = 1;
    }

  ਜੇ (current_scope == file_scope && declspecs->storage_class == csc_auto)
    {
      error ("%<auto%> in file-scope empty declaration");
      warned = 1;
    }

  ਜੇ (current_scope == file_scope && declspecs->storage_class == csc_ਰਜਿਸਟਰ)
    {
      error ("%<register%> in file-scope empty declaration");
      warned = 1;
    }

  ਜੇ (declspecs->enum_type_specifier_ref_p && !warned)
    {
      ਜੇ (declspecs->storage_class != csc_none)
	{
	  error ("storage class specifier in empty declaration with %<enum%> "
		 "underlying type");
	  warned = 1;
	}
      ਨਹੀਂਤਾਂ ਜੇ (declspecs->thread_p)
	{
	  error ("%qs in empty declaration with %<enum%> underlying type",
		 declspecs->thread_gnu_p ? "__thread" : "_Thread_local");
	  warned = 1;
	}
      ਨਹੀਂਤਾਂ ਜੇ (declspecs->const_p
	       || declspecs->volatile_p
	       || declspecs->atomic_p
	       || declspecs->restrict_p
	       || declspecs->ਪਤਾ_space)
	{
	  error ("type qualifier in empty declaration with %<enum%> "
		 "underlying type");
	  warned = 1;
	}
      ਨਹੀਂਤਾਂ ਜੇ (declspecs->alignas_p)
	{
	  error ("%<alignas%> in empty declaration with %<enum%> "
		 "underlying type");
	  warned = 1;
	}
    }

  ਜੇ (!warned && !ਵਿੱਚ_system_ਸਿਰਲੇਖ_at (ਨਿਵੇਸ਼_location)
      && declspecs->storage_class != csc_none)
    {
      warning (0, "useless storage class specifier in empty declaration");
      warned = 2;
    }

  ਜੇ (!warned && !ਵਿੱਚ_system_ਸਿਰਲੇਖ_at (ਨਿਵੇਸ਼_location) && declspecs->thread_p)
    {
      warning (0, "useless %qs in empty declaration",
	       declspecs->thread_gnu_p ? "__thread" : "_Thread_local");
      warned = 2;
    }

  ਜੇ (!warned
      && !ਵਿੱਚ_system_ਸਿਰਲੇਖ_at (ਨਿਵੇਸ਼_location)
      && (declspecs->const_p
	  || declspecs->volatile_p
	  || declspecs->atomic_p
	  || declspecs->restrict_p
	  || declspecs->ਪਤਾ_space))
    {
      warning (0, "useless type qualifier in empty declaration");
      warned = 2;
    }

  ਜੇ (!warned && !ਵਿੱਚ_system_ਸਿਰਲੇਖ_at (ਨਿਵੇਸ਼_location)
      && declspecs->alignas_p)
    {
      warning (0, "useless %<_Alignas%> in empty declaration");
      warned = 2;
    }

  ਜੇ (ਮਿਲਿਆ_ਟੈਗ
      && warned == 2
      && (declspecs->typespec_ਕਿਸਮ == ctsk_tagref_attrs
	  || declspecs->typespec_ਕਿਸਮ == ctsk_tagfirstref_attrs))
    {
      /* Standard attributes after the "struct" or "union" keyword are
	 only permitted when the contents of the type are defined, or
	 in the form "struct-or-union attribute-specifier-sequence
	 identifier;".  If the ';' was not present, attributes were
	 diagnosed in the parser.  Here, ensure that any other useless
	 elements of the declaration result in a pedwarn, not just a
	 warning.  Forward declarations of enum types are not part of
	 standard C, but handle them the same.  */
      pedwarn (ਨਿਵੇਸ਼_location, 0,
	       "invalid use of attributes in empty declaration");
      warned = 1;
    }

  ਜੇ (warned != 1)
    {
      ਜੇ (declspecs->declspecs_ਵੇਖਿਆ_p
	  && !declspecs->non_std_attrs_ਵੇਖਿਆ_p)
	/* An attribute declaration (but not a fallthrough attribute
	   declaration, which was handled separately); warn if there
	   are any attributes being ignored (but not if the attributes
	   were empty).  */
	c_warn_ਅਣਵਰਤਿਆ_ਗੁਣ (declspecs->attrs);
      ਨਹੀਂਤਾਂ ਜੇ (!ਮਿਲਿਆ_ਟੈਗ)
	pedwarn (ਨਿਵੇਸ਼_location, 0, "empty declaration");
    }
}


/* Return the qualifiers from SPECS as a bitwise OR of TYPE_QUAL_*
   bits.  SPECS represents declaration specifiers that the grammar
   only permits to contain type qualifiers and attributes.  */

ਪੂਰਨ
quals_from_declspecs (ਅਚਲ ਬਣਤਰ c_declspecs *specs)
{
  ਪੂਰਨ quals = ((specs->const_p ? TYPE_QUAL_CONST : 0)
	       | (specs->volatile_p ? TYPE_QUAL_VOLATILE : 0)
	       | (specs->restrict_p ? TYPE_QUAL_RESTRICT : 0)
	       | (specs->atomic_p ? TYPE_QUAL_ATOMIC : 0)
	       | (ENCODE_QUAL_ADDR_SPACE (specs->ਪਤਾ_space)));
  gcc_assert (!specs->type
	      && !specs->decl_attr
	      && specs->typespec_ਸ਼ਬਦ == cts_none
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
  ਵਾਪਸ quals;
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

ਬਣਤਰ c_declarator *
build_array_declarator (location_t loc,
			ਰੁੱਖ ਵਿਅੰਜਕ, ਬਣਤਰ c_declspecs *quals, ਤਾਰਕਿਕ static_p,
			ਤਾਰਕਿਕ vla_unspec_p)
{
  ਬਣਤਰ c_declarator *declarator = XOBNEW (&parser_obstack,
					    ਬਣਤਰ c_declarator);
  declarator->id_loc = loc;
  declarator->ਕਿਸਮ = cdk_array;
  declarator->declarator = 0;
  declarator->u.array.dimen = ਵਿਅੰਜਕ;
  ਜੇ (quals)
    {
      declarator->u.array.attrs = quals->attrs;
      declarator->u.array.quals = quals_from_declspecs (quals);
    }
  ਨਹੀਂਤਾਂ
    {
      declarator->u.array.attrs = NULL_ਰੁੱਖ;
      declarator->u.array.quals = 0;
    }
  declarator->u.array.static_p = static_p;
  declarator->u.array.vla_unspec_p = vla_unspec_p;
  ਜੇ (static_p || quals != ਨਿਰਾ)
    pedwarn_c90 (loc, OPT_Wpedantic,
		 "ISO C90 does not support %<static%> or type "
		 "qualifiers in parameter array declarators");
  ਜੇ (vla_unspec_p)
    {
      pedwarn_c90 (loc, OPT_Wpedantic,
		   "ISO C90 does not support %<[*]%> array declarators");
      ਜੇ (current_scope->parm_flag)
	current_scope->had_vla_unspec = ਸੱਚ;
    }
  ਵਾਪਸ declarator;
}

/* Set the contained declarator of an array declarator.  DECL is the
   declarator, as constructed by build_array_declarator; INNER is what
   appears on the left of the [].  */

ਬਣਤਰ c_declarator *
ਸੈੱਟ_array_declarator_inner (ਬਣਤਰ c_declarator *decl,
			    ਬਣਤਰ c_declarator *inner)
{
  decl->declarator = inner;
  ਵਾਪਸ decl;
}

/* Determine whether TYPE is a one-element array type "[1]".  */
ਸਥਿਰ ਤਾਰਕਿਕ
one_element_array_type_p (const_ਰੁੱਖ type)
{
  ਜੇ (ਰੁੱਖ_ਕੋਡ (type) != ARRAY_TYPE)
    ਵਾਪਸ ਝੂਠ;
  ਵਾਪਸ integer_zerop (array_type_nelts_minus_one (type));
}

/* Determine whether TYPE is a zero-length array type "[0]".  */
ਤਾਰਕਿਕ
zero_ਲੰਮਾਈ_array_type_p (const_ਰੁੱਖ type)
{
  ਜੇ (ਰੁੱਖ_ਕੋਡ (type) == ARRAY_TYPE
      && COMPLETE_TYPE_P (type)
      && TYPE_DOMAIN (type) != NULL_ਰੁੱਖ
      && (TYPE_MAX_ਮੁੱਲ (TYPE_DOMAIN (type)) == NULL_ਰੁੱਖ
	  || integer_all_onesp (TYPE_MAX_ਮੁੱਲ (TYPE_DOMAIN (type)))))
    ਵਾਪਸ ਸੱਚ;
  ਵਾਪਸ ਝੂਠ;
}

/* INIT is a constructor that forms DECL's initializer.  If the final
   element initializes a flexible array field, adjust the size of the
   DECL with the initializer based on whether the DECL is a union or
   a structure.  */

ਸਥਿਰ ਖਾਲੀ
ਜੋੜੋ_flexible_array_elts_ਮੰਜ਼ਿਲ_ਮਾਪ (ਰੁੱਖ decl, ਰੁੱਖ init)
{
  ਰੁੱਖ elt, type;

  ਜੇ (vec_ਸੁਰੱਖਿਅਤ_is_ਖਾਲੀ_ਥਾਵਾਂ (CONSTRUCTOR_ELTS (init)))
    ਵਾਪਸ;

  elt = CONSTRUCTOR_ELTS (init)->ਆਖਰੀ ().ਮੁੱਲ;
  type = ਰੁੱਖ_TYPE (elt);
  ਜੇ (flexible_array_member_type_p (type))
    {
      complete_array_type (&type, elt, ਝੂਠ);
      /* For a structure, add the size of the initializer to the DECL's
	 size.  */
      ਜੇ (ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (decl)) == ਰਿਕਾਰਡ_TYPE)
	{
	  DECL_ਮਾਪ (decl)
	    = ਮਾਪ_binop (PLUS_ਵਿਅੰਜਕ, DECL_ਮਾਪ (decl), TYPE_ਮਾਪ (type));
	  DECL_ਮਾਪ_UNIT (decl)
	    = ਮਾਪ_binop (PLUS_ਵਿਅੰਜਕ, DECL_ਮਾਪ_UNIT (decl),
			  TYPE_ਮਾਪ_UNIT (type));
	}
      /* For a union, the DECL's size is the maximum of the current size
	 and the size of the initializer.  */
      ਨਹੀਂਤਾਂ
	{
	  DECL_ਮਾਪ (decl)
	    = ਮਾਪ_binop (MAX_ਵਿਅੰਜਕ, DECL_ਮਾਪ (decl), TYPE_ਮਾਪ (type));
	  DECL_ਮਾਪ_UNIT (decl)
	    = ਮਾਪ_binop (MAX_ਵਿਅੰਜਕ, DECL_ਮਾਪ_UNIT (decl),
			  TYPE_ਮਾਪ_UNIT (type));
	}
    }
}

/* Decode a "typename", such as "int **", returning a ..._TYPE node.
   Set *EXPR, if EXPR not NULL, to any expression to be evaluated
   before the type name, and set *EXPR_CONST_OPERANDS, if
   EXPR_CONST_OPERANDS not NULL, to indicate whether the type name may
   appear in a constant expression.  */

ਰੁੱਖ
groktypename (ਬਣਤਰ c_type_name *type_name, ਰੁੱਖ *ਵਿਅੰਜਕ,
	      ਤਾਰਕਿਕ *ਵਿਅੰਜਕ_const_operands)
{
  ਰੁੱਖ type;
  ਰੁੱਖ attrs = type_name->specs->attrs;

  type_name->specs->attrs = NULL_ਰੁੱਖ;

  type = grokdeclarator (type_name->declarator, type_name->specs, TYPENAME,
			 ਝੂਠ, ਨਿਰਾ, &attrs, ਵਿਅੰਜਕ, ਵਿਅੰਜਕ_const_operands,
			 DEPRECATED_ਸਾਧਾਰਨ);

  /* Apply attributes.  */
  attrs = c_warn_type_ਗੁਣ (type, attrs);
  decl_ਗੁਣ (&type, attrs, 0);

  ਵਾਪਸ type;
}


/* Decode a "typename", such as "int **", returning a ..._TYPE node,
   as for groktypename but setting the context to GENERIC_ASSOC.  */

ਰੁੱਖ
grokgenassoc (ਬਣਤਰ c_type_name *type_name)
{
  ਰੁੱਖ type;
  ਰੁੱਖ attrs = type_name->specs->attrs;

  type_name->specs->attrs = NULL_ਰੁੱਖ;

  type = grokdeclarator (type_name->declarator, type_name->specs, GENERIC_ASSOC,
			 ਝੂਠ, ਨਿਰਾ, &attrs, ਨਿਰਾ, ਨਿਰਾ, DEPRECATED_ਸਾਧਾਰਨ);

  /* Apply attributes.  */
  attrs = c_warn_type_ਗੁਣ (type, attrs);
  decl_ਗੁਣ (&type, attrs, 0);

  ਵਾਪਸ type;
}


/* Looks up the most recent pushed declaration corresponding to DECL.  */

ਸਥਿਰ ਰੁੱਖ
lookup_ਆਖਰੀ_decl (ਰੁੱਖ decl)
{
  ਰੁੱਖ ਆਖਰੀ_decl = lookup_name (DECL_NAME (decl));
  ਜੇ (!ਆਖਰੀ_decl)
    ਆਖਰੀ_decl = lookup_name_ਵਿੱਚ_scope (DECL_NAME (decl), external_scope);
  ਵਾਪਸ ਆਖਰੀ_decl;
}

/* Wrapper for decl_attributes that adds some implicit attributes
   to VAR_DECLs or FUNCTION_DECLs.  */

ਸਥਿਰ ਰੁੱਖ
c_decl_ਗੁਣ (ਰੁੱਖ *ਗੰਢ, ਰੁੱਖ ਗੁਣ, ਪੂਰਨ flags)
{
  /* Add implicit "omp declare target" attribute if requested.  */
  ਜੇ (vec_ਸੁਰੱਖਿਅਤ_ਲੰਮਾਈ (current_omp_declare_ਨਿਸ਼ਾਨਾ_attribute)
      && ((VAR_P (*ਗੰਢ) && is_global_var (*ਗੰਢ))
	  || ਰੁੱਖ_ਕੋਡ (*ਗੰਢ) == FUNCTION_DECL))
    {
      ਜੇ (VAR_P (*ਗੰਢ) && !omp_mappable_type (ਰੁੱਖ_TYPE (*ਗੰਢ)))
	ਗੁਣ = ਰੁੱਖ_cons (get_identifier ("omp declare target implicit"),
				NULL_ਰੁੱਖ, ਗੁਣ);
      ਨਹੀਂਤਾਂ
	ਗੁਣ = ਰੁੱਖ_cons (get_identifier ("omp declare target"),
				NULL_ਰੁੱਖ, ਗੁਣ);
      ਜੇ (ਰੁੱਖ_ਕੋਡ (*ਗੰਢ) == FUNCTION_DECL)
	{
	  ਪੂਰਨ device_type
	    = current_omp_declare_ਨਿਸ਼ਾਨਾ_attribute->ਆਖਰੀ ().device_type;
	  device_type = MAX (device_type, 0);
	  ਜੇ ((device_type & OMP_CLAUSE_DEVICE_TYPE_HOST) != 0
	      && !lookup_attribute ("omp declare target host", ਗੁਣ))
	    ਗੁਣ
	      = ਰੁੱਖ_cons (get_identifier ("omp declare target host"),
			   NULL_ਰੁੱਖ, ਗੁਣ);
	  ਜੇ ((device_type & OMP_CLAUSE_DEVICE_TYPE_NOHOST) != 0
	      && !lookup_attribute ("omp declare target nohost", ਗੁਣ))
	    ਗੁਣ
	      = ਰੁੱਖ_cons (get_identifier ("omp declare target nohost"),
			   NULL_ਰੁੱਖ, ਗੁਣ);

	  ਪੂਰਨ ਅਸਿੱਧਾ
	    = current_omp_declare_ਨਿਸ਼ਾਨਾ_attribute->ਆਖਰੀ ().ਅਸਿੱਧਾ;
	  ਜੇ (ਅਸਿੱਧਾ && !lookup_attribute ("omp declare target indirect",
					     ਗੁਣ))
	    ਗੁਣ
	      = ਰੁੱਖ_cons (get_identifier ("omp declare target indirect"),
			   NULL_ਰੁੱਖ, ਗੁਣ);
	}
    }

  ਜੇ (flag_openmp || flag_openmp_simd)
    {
      ਤਾਰਕਿਕ diagnosed = ਝੂਠ;
      ਲਈ (ਰੁੱਖ *pa = &ਗੁਣ; *pa; )
	{
	  ਜੇ (is_attribute_namespace_p ("omp", *pa))
	    {
	      ਰੁੱਖ name = get_attribute_name (*pa);
	      ਜੇ (is_attribute_p ("directive", name)
		  || is_attribute_p ("sequence", name)
		  || is_attribute_p ("decl", name))
		{
		  ਅਚਲ ਅੱਖਰ *p = ਨਿਰਾ;
		  ਜੇ (ਰੁੱਖ_ਮੁੱਲ (*pa) == NULL_ਰੁੱਖ)
		    p = IDENTIFIER_ਸੂਚਕ (name);
		  ਲਈ (ਰੁੱਖ a = ਰੁੱਖ_ਮੁੱਲ (*pa); a; a = ਰੁੱਖ_CHAIN (a))
		    {
		      ਰੁੱਖ d = ਰੁੱਖ_ਮੁੱਲ (a);
		      gcc_assert (ਰੁੱਖ_ਕੋਡ (d) == C_TOKEN_VEC);
		      ਜੇ (ਰੁੱਖ_ਜਨਤਕ (d)
			  && (VAR_P (*ਗੰਢ)
			      || ਰੁੱਖ_ਕੋਡ (*ਗੰਢ) == FUNCTION_DECL)
			  && c_maybe_parse_omp_decl (*ਗੰਢ, d))
			ਜਾਰੀ;
		      p = ਰੁੱਖ_ਜਨਤਕ (d) ? "decl" : "directive";
		    }
		  ਜੇ (p && !diagnosed)
		    {
		      error ("%<omp::%s%> not allowed to be specified in "
			     "this context", p);
		      diagnosed = ਸੱਚ;
		    }
		  ਜੇ (p)
		    {
		      *pa = ਰੁੱਖ_CHAIN (*pa);
		      ਜਾਰੀ;
		    }
		}
	    }
	  pa = &ਰੁੱਖ_CHAIN (*pa);
	}
    }

  /* Look up the current declaration with all the attributes merged
     so far so that attributes on the current declaration that's
     about to be pushed that conflict with the former can be detected,
     diagnosed, and rejected as appropriate.  To match the C++ FE, do
     not pass an error_mark_node when we found an undeclared variable.  */
  ਰੁੱਖ ਆਖਰੀ_decl = lookup_ਆਖਰੀ_decl (*ਗੰਢ);
  ਜੇ (ਆਖਰੀ_decl == error_mark_ਗੰਢ)
    ਆਖਰੀ_decl = NULL_ਰੁੱਖ;
  ਰੁੱਖ attr = decl_ਗੁਣ (ਗੰਢ, ਗੁਣ, flags, ਆਖਰੀ_decl);
  ਜੇ (VAR_P (*ਗੰਢ) && DECL_THREAD_LOCAL_P (*ਗੰਢ))
    {
      // tls_model attribute can set a stronger TLS access model.
      tls_model model = DECL_TLS_MODEL (*ਗੰਢ);
      tls_model default_model = decl_default_tls_model (*ਗੰਢ);
      ਜੇ (default_model > model)
	ਸੈੱਟ_decl_tls_model (*ਗੰਢ, default_model);
    }
  ਵਾਪਸ attr;
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

ਰੁੱਖ
ਸ਼ੁਰੂ_decl (ਬਣਤਰ c_declarator *declarator, ਬਣਤਰ c_declspecs *declspecs,
	    ਤਾਰਕਿਕ initialized, ਰੁੱਖ ਗੁਣ, ਤਾਰਕਿਕ do_ਧੱਕੋ /* = true */,
	    location_t *lastloc /* = NULL */)
{
  ਰੁੱਖ decl;
  ਰੁੱਖ old_decl;
  ਰੁੱਖ tem;
  ਰੁੱਖ ਵਿਅੰਜਕ = NULL_ਰੁੱਖ;
  ਗਿਣਤੀ deprecated_ਹਾਲਤਾਂ deprecated_state = DEPRECATED_ਸਾਧਾਰਨ;

  /* An object declared as __attribute__((unavailable)) suppresses
     warnings and errors from __attribute__((deprecated/unavailable))
     components.
     An object declared as __attribute__((deprecated)) suppresses
     warnings of uses of other deprecated items.  */
  ਜੇ (lookup_attribute ("unavailable", ਗੁਣ))
    deprecated_state = UNAVAILABLE_DEPRECATED_SUPPRESS;
  ਨਹੀਂਤਾਂ ਜੇ (lookup_attribute ("deprecated", ਗੁਣ))
    deprecated_state = DEPRECATED_SUPPRESS;

  decl = grokdeclarator (declarator, declspecs,
			 ਸਾਧਾਰਨ, initialized, ਨਿਰਾ, &ਗੁਣ, &ਵਿਅੰਜਕ, ਨਿਰਾ,
			 deprecated_state);
  ਜੇ (!decl || decl == error_mark_ਗੰਢ)
    ਵਾਪਸ NULL_ਰੁੱਖ;

  old_decl = lookup_ਆਖਰੀ_decl (decl);

  ਜੇ (ਰੁੱਖ lastdecl = lastloc ? old_decl : NULL_ਰੁੱਖ)
    ਜੇ (lastdecl != error_mark_ਗੰਢ)
      *lastloc = DECL_ਸਰੋਤ_LOCATION (lastdecl);

  /* Make sure the size expression is evaluated at this point.  */
  ਜੇ (ਵਿਅੰਜਕ && !current_scope->parm_flag)
    ਜੋੜੋ_stmt (fold_convert (void_type_ਗੰਢ, ਵਿਅੰਜਕ));

  ਜੇ (ਰੁੱਖ_ਕੋਡ (decl) != FUNCTION_DECL && MAIN_NAME_P (DECL_NAME (decl))
      && ਰੁੱਖ_ਜਨਤਕ (decl))
    warning (OPT_Wmain, "%q+D is usually a function", decl);

  ਜੇ (warn_missing_variable_declarations && VAR_P (decl)
      && !DECL_EXTERNAL (decl) && ਰੁੱਖ_ਜਨਤਕ (decl) && old_decl == NULL_ਰੁੱਖ)
    warning_at (DECL_ਸਰੋਤ_LOCATION (decl), OPT_Wmissing_variable_declarations,
		"no previous declaration for %qD", decl);

  ਜੇ (initialized)
    /* Is it valid for this decl to have an initializer at all?
       If not, set INITIALIZED to zero, which will indirectly
       tell 'finish_decl' to ignore the initializer once it is parsed.  */
    ਚੋਣ (ਰੁੱਖ_ਕੋਡ (decl))
      {
      ਹਾਲਤ TYPE_DECL:
	error ("typedef %qD is initialized (use %<__typeof__%> instead)", decl);
	initialized = ਝੂਠ;
	ਰੋਕੋ;

      ਹਾਲਤ FUNCTION_DECL:
	error ("function %qD is initialized like a variable", decl);
	initialized = ਝੂਠ;
	ਰੋਕੋ;

      ਹਾਲਤ PARM_DECL:
	/* DECL_INITIAL in a PARM_DECL is really DECL_ARG_TYPE.  */
	error ("parameter %qD is initialized", decl);
	initialized = ਝੂਠ;
	ਰੋਕੋ;

      ਮੂਲ:
	/* Don't allow initializations for incomplete types except for
	   arrays which might be completed by the initialization.  */

	/* This can happen if the array size is an undefined macro.
	   We already gave a warning, so we don't need another one.  */
	ਜੇ (ਰੁੱਖ_TYPE (decl) == error_mark_ਗੰਢ)
	  initialized = ਝੂਠ;
	ਨਹੀਂਤਾਂ ਜੇ (COMPLETE_TYPE_P (ਰੁੱਖ_TYPE (decl)))
	  {
	    /* A complete type is ok if size is fixed.  If the size is
	       variable, an empty initializer is OK and nonempty
	       initializers will be diagnosed in the parser.  */
	  }
	ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (decl)) != ARRAY_TYPE)
	  {
	    error ("variable %qD has initializer but incomplete type", decl);
	    initialized = ਝੂਠ;
	  }
      }

  ਜੇ (initialized)
    {
      ਜੇ (current_scope == file_scope)
	ਰੁੱਖ_STATIC (decl) = 1;

      /* Tell 'pushdecl' this is an initialized decl
	 even though we don't yet have the initializer expression.
	 Also tell 'finish_decl' it may store the real initializer.  */
      DECL_INITIAL (decl) = error_mark_ਗੰਢ;
    }

  /* If this is a function declaration, write a record describing it to the
     prototypes file (if requested).  */

  ਜੇ (ਰੁੱਖ_ਕੋਡ (decl) == FUNCTION_DECL)
    gen_aux_info_ਰਿਕਾਰਡ (decl, 0, 0, prototype_p (ਰੁੱਖ_TYPE (decl)));

  /* ANSI specifies that a tentative definition which is not merged with
     a non-tentative definition behaves exactly like a definition with an
     initializer equal to zero.  (Section 3.7.2)

     -fno-common gives strict ANSI behavior, though this tends to break
     a large body of code that grew up without this rule.

     Thread-local variables are never common, since there's no entrenched
     body of code to break, and it allows more efficient variable references
     in the presence of dynamic linking.  */

  ਜੇ (VAR_P (decl)
      && !initialized
      && ਰੁੱਖ_ਜਨਤਕ (decl)
      && !DECL_THREAD_LOCAL_P (decl)
      && !flag_no_common)
    DECL_COMMON (decl) = 1;

  /* Set attributes here so if duplicate decl, will have proper attributes.  */
  c_decl_ਗੁਣ (&decl, ਗੁਣ, 0);

  /* Handle gnu_inline attribute.  */
  ਜੇ (declspecs->inline_p
      && !flag_gnu89_inline
      && ਰੁੱਖ_ਕੋਡ (decl) == FUNCTION_DECL
      && (lookup_attribute ("gnu_inline", DECL_ਗੁਣ (decl))
	  || current_function_decl))
    {
      ਜੇ (declspecs->storage_class == csc_auto && current_scope != file_scope)
	;
      ਨਹੀਂਤਾਂ ਜੇ (declspecs->storage_class != csc_static)
	DECL_EXTERNAL (decl) = !DECL_EXTERNAL (decl);
    }

  ਜੇ (ਰੁੱਖ_ਕੋਡ (decl) == FUNCTION_DECL
      && DECL_DECLARED_INLINE_P (decl)
      && DECL_UNINLINABLE (decl)
      && lookup_attribute ("noinline", DECL_ਗੁਣ (decl)))
    {
      auto_urlify_ਗੁਣ sentinel;
      warning (OPT_Wattributes, "inline function %q+D given attribute %qs",
	       decl, "noinline");
    }

  /* C99 6.7.4p3: An inline definition of a function with external
     linkage shall not contain a definition of a modifiable object
     with static storage duration...  */
  ਜੇ (VAR_P (decl)
      && current_scope != file_scope
      && ਰੁੱਖ_STATIC (decl)
      && !ਰੁੱਖ_READONLY (decl)
      && DECL_DECLARED_INLINE_P (current_function_decl)
      && DECL_EXTERNAL (current_function_decl))
    ਰਿਕਾਰਡ_inline_static (ਨਿਵੇਸ਼_location, current_function_decl,
			  decl, csi_modifiable);

  ਜੇ (c_dialect_objc ()
      && VAR_OR_FUNCTION_DECL_P (decl))
      objc_check_global_decl (decl);

  /* To enable versions to be created across TU's we mark and mangle all
     non-default versioned functions.  */
  ਜੇ (ਰੁੱਖ_ਕੋਡ (decl) == FUNCTION_DECL
      && !ਨਿਸ਼ਾਨਾ_HAS_FMV_ਨਿਸ਼ਾਨਾ_ATTRIBUTE
      && get_ਨਿਸ਼ਾਨਾ_ਸੰਸਕਰਣ (decl).is_valid ())
    {
      maybe_mark_function_versioned (decl);
      ਜੇ (current_scope != file_scope)
	error ("versioned declarations are only allowed at file scope");
    }

  /* Add this decl to the current scope.
     TEM may equal DECL or it may be a previous decl of the same name.  */
  ਜੇ (do_ਧੱਕੋ)
    {
      tem = pushdecl (decl);

      ਜੇ (initialized && DECL_EXTERNAL (tem))
	{
	  DECL_EXTERNAL (tem) = 0;
	  ਰੁੱਖ_STATIC (tem) = 1;
	}

      ਵਾਪਸ tem;
    }
  ਨਹੀਂਤਾਂ
    ਵਾਪਸ decl;
}

/* Subroutine of finish_decl. TYPE is the type of an uninitialized object
   DECL or the non-array element type if DECL is an uninitialized array.
   If that type has a const member, diagnose this. */

ਸਥਿਰ ਖਾਲੀ
diagnose_uninitialized_cst_member (ਰੁੱਖ decl, ਰੁੱਖ type)
{
  ਰੁੱਖ ਖੇਤਰ_2;
  ਲਈ (ਖੇਤਰ_2 = TYPE_FIELDS (type); ਖੇਤਰ_2; ਖੇਤਰ_2 = ਰੁੱਖ_CHAIN (ਖੇਤਰ_2))
    {
      ਰੁੱਖ ਖੇਤਰ_type;
      ਜੇ (ਰੁੱਖ_ਕੋਡ (ਖੇਤਰ_2) != ਖੇਤਰ_DECL)
	ਜਾਰੀ;
      ਖੇਤਰ_type = strip_array_types (ਰੁੱਖ_TYPE (ਖੇਤਰ_2));

      ਜੇ (TYPE_QUALS (ਖੇਤਰ_type) & TYPE_QUAL_CONST)
      	{
	  auto_diagnostic_ਸਮੂਹ d;
	  ਜੇ (warning_at (DECL_ਸਰੋਤ_LOCATION (decl), OPT_Wc___compat,
			  "uninitialized const member in %qT is invalid in C++",
			  strip_array_types (ਰੁੱਖ_TYPE (decl))))
	    inform (DECL_ਸਰੋਤ_LOCATION (ਖੇਤਰ_2), "%qD should be initialized", ਖੇਤਰ_2);
	}

      ਜੇ (ਰਿਕਾਰਡ_OR_UNION_TYPE_P (ਖੇਤਰ_type))
	diagnose_uninitialized_cst_member (decl, ਖੇਤਰ_type);
    }
}

/* Finish processing of a declaration;
   install its initial value.
   If ORIGTYPE is not NULL_TREE, it is the original type of INIT.
   If the length of an array type is not known before,
   it must be determined now, from the initial value, or it is an error.

   INIT_LOC is the location of the initial value.  */

ਖਾਲੀ
ਅੰਤ_decl (ਰੁੱਖ decl, location_t init_loc, ਰੁੱਖ init,
	     ਰੁੱਖ origtype, ਰੁੱਖ asmspec_ਰੁੱਖ)
{
  ਰੁੱਖ type;
  ਤਾਰਕਿਕ was_incomplete = (DECL_ਮਾਪ (decl) == NULL_ਰੁੱਖ);
  ਅਚਲ ਅੱਖਰ *asmspec = 0;

  /* If a name was specified, get the string.  */
  ਜੇ (VAR_OR_FUNCTION_DECL_P (decl)
      && DECL_FILE_SCOPE_P (decl))
    asmspec_ਰੁੱਖ = maybe_apply_renaming_pragma (decl, asmspec_ਰੁੱਖ);
  ਜੇ (asmspec_ਰੁੱਖ)
    asmspec = ਰੁੱਖ_STRING_ਸੂਚਕ (asmspec_ਰੁੱਖ);

  ਜੇ (VAR_P (decl)
      && ਰੁੱਖ_STATIC (decl)
      && global_bindings_p ())
    /* So decl is a global variable. Record the types it uses
       so that we can decide later to emit debug info for them.  */
    ਰਿਕਾਰਡ_types_ਵਰਤਿਆ_by_current_var_decl (decl);

  /* If `start_decl' didn't like having an initialization, ignore it now.  */
  ਜੇ (init != NULL_ਰੁੱਖ && DECL_INITIAL (decl) == NULL_ਰੁੱਖ)
    init = NULL_ਰੁੱਖ;

  /* Don't crash if parm is initialized.  */
  ਜੇ (ਰੁੱਖ_ਕੋਡ (decl) == PARM_DECL)
    init = NULL_ਰੁੱਖ;

  ਜੇ (init)
    store_init_ਮੁੱਲ (init_loc, decl, init, origtype);

  ਜੇ (c_dialect_objc () && (VAR_OR_FUNCTION_DECL_P (decl)
			    || ਰੁੱਖ_ਕੋਡ (decl) == ਖੇਤਰ_DECL))
    objc_check_decl (decl);

  type = ਰੁੱਖ_TYPE (decl);

  /* Deduce size of array from initialization, if not already known.
     This is only needed for an initialization in the current scope;
     it must not be done for a file-scope initialization of a
     declaration with external linkage, redeclared in an inner scope
     with the outer declaration shadowed in an intermediate scope.  */
  ਜੇ (ਰੁੱਖ_ਕੋਡ (type) == ARRAY_TYPE
      && TYPE_DOMAIN (type) == NULL_ਰੁੱਖ
      && ਰੁੱਖ_ਕੋਡ (decl) != TYPE_DECL
      && !(ਰੁੱਖ_ਜਨਤਕ (decl) && current_scope != file_scope))
    {
      ਤਾਰਕਿਕ do_default
	= !ਰੁੱਖ_STATIC (decl) && !DECL_EXTERNAL (decl);
      ਪੂਰਨ failure
	= complete_array_type (&ਰੁੱਖ_TYPE (decl), DECL_INITIAL (decl),
			       do_default);

      /* Get the completed type made by complete_array_type.  */
      type = ਰੁੱਖ_TYPE (decl);

      ਚੋਣ (failure)
	{
	ਹਾਲਤ 1:
	  error ("initializer fails to determine size of %q+D", decl);
	  ਰੋਕੋ;

	ਹਾਲਤ 2:
	  ਜੇ (do_default)
	    error ("array size missing in %q+D", decl);
	  ਨਹੀਂਤਾਂ ਜੇ (!ਰੁੱਖ_ਜਨਤਕ (decl))
	    pedwarn_c23 (DECL_ਸਰੋਤ_LOCATION (decl), OPT_Wpedantic,
			 "array size missing in %q+D", decl);
	  ਰੋਕੋ;

	ਹਾਲਤ 3:
	  error ("zero or negative size array %q+D", decl);
	  ਰੋਕੋ;

	ਹਾਲਤ 0:
	  /* For global variables, update the copy of the type that
	     exists in the binding.  */
	  ਜੇ (ਰੁੱਖ_ਜਨਤਕ (decl))
	    {
	      ਬਣਤਰ c_binding *b_ext = I_ਚਿੰਨ੍ਹ_BINDING (DECL_NAME (decl));
	      ਜਦੋਂ (b_ext && !B_ਵਿੱਚ_EXTERNAL_SCOPE (b_ext))
		b_ext = b_ext->shadowed;
	      ਜੇ (b_ext && ਰੁੱਖ_ਕੋਡ (decl) == ਰੁੱਖ_ਕੋਡ (b_ext->decl))
		{
		  ਜੇ (b_ext->u.type && comptypes (b_ext->u.type, type))
		    b_ext->u.type = ਸੰਯੁਕਤ_type (b_ext->u.type, type);
		  ਨਹੀਂਤਾਂ
		    b_ext->u.type = type;
		}
	    }
	  ਰੋਕੋ;

	ਮੂਲ:
	  gcc_unreachable ();
	}

      ਜੇ (DECL_INITIAL (decl) && DECL_INITIAL (decl) != error_mark_ਗੰਢ)
	ਰੁੱਖ_TYPE (DECL_INITIAL (decl)) = type;

      relayout_decl (decl);
    }

  /* Look for braced array initializers for character arrays and
     recursively convert them into STRING_CSTs.  */
  ਜੇ (ਰੁੱਖ init = DECL_INITIAL (decl))
    DECL_INITIAL (decl) = braced_lists_ਮੰਜ਼ਿਲ_ਲੜੀਆਂ (type, init);

  ਜੇ (VAR_P (decl))
    {
      ਜੇ (init && ਰੁੱਖ_ਕੋਡ (init) == CONSTRUCTOR)
	ਜੋੜੋ_flexible_array_elts_ਮੰਜ਼ਿਲ_ਮਾਪ (decl, init);

      complete_flexible_array_elts (DECL_INITIAL (decl));

      ਜੇ (is_global_var (decl))
	{
	  type_context_ਕਿਸਮ context = (DECL_THREAD_LOCAL_P (decl)
				       ? TCTX_THREAD_STORAGE
				       : TCTX_STATIC_STORAGE);
	  ਜੇ (!verify_type_context (ਨਿਵੇਸ਼_location, context, ਰੁੱਖ_TYPE (decl)))
	    ਰੁੱਖ_TYPE (decl) = error_mark_ਗੰਢ;
	}

      ਜੇ (DECL_ਮਾਪ (decl) == NULL_ਰੁੱਖ && ਰੁੱਖ_TYPE (decl) != error_mark_ਗੰਢ
	  && COMPLETE_TYPE_P (ਰੁੱਖ_TYPE (decl)))
	layout_decl (decl, 0);

      ਜੇ (DECL_ਮਾਪ (decl) == NULL_ਰੁੱਖ
	  /* Don't give an error if we already gave one earlier.  */
	  && ਰੁੱਖ_TYPE (decl) != error_mark_ਗੰਢ
	  && (ਰੁੱਖ_STATIC (decl)
	      /* A static variable with an incomplete type
		 is an error if it is initialized.
		 Also if it is not file scope.
		 Also if it is thread-local (in C23).
		 Otherwise, let it through, but if it is not `extern'
		 then it may cause an error message later.  */
	      ? (DECL_INITIAL (decl) != NULL_ਰੁੱਖ
		 || !DECL_FILE_SCOPE_P (decl)
		 || (flag_isoc23 && DECL_THREAD_LOCAL_P (decl)))
	      /* An automatic variable with an incomplete type
		 is an error.  */
	      : !DECL_EXTERNAL (decl)))
	 {
	   error ("storage size of %q+D isn%'t known", decl);
	   ਰੁੱਖ_TYPE (decl) = error_mark_ਗੰਢ;
	 }

      ਜੇ ((ਰਿਕਾਰਡ_OR_UNION_TYPE_P (ਰੁੱਖ_TYPE (decl))
	  || ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (decl)) == ENUMERAL_TYPE)
	  && DECL_ਮਾਪ (decl) == NULL_ਰੁੱਖ
	  && ਰੁੱਖ_STATIC (decl))
	incomplete_ਰਿਕਾਰਡ_decls.ਸੁਰੱਖਿਅਤ_ਧੱਕੋ (decl);

      ਜੇ (is_global_var (decl)
	  && DECL_ਮਾਪ (decl) != NULL_ਰੁੱਖ
	  && ਰੁੱਖ_TYPE (decl) != error_mark_ਗੰਢ)
	{
	  ਜੇ (ਰੁੱਖ_ਕੋਡ (DECL_ਮਾਪ (decl)) == INTEGER_CST)
	    constant_ਵਿਅੰਜਕ_warning (DECL_ਮਾਪ (decl));
	  ਨਹੀਂਤਾਂ
	    {
	      error ("storage size of %q+D isn%'t constant", decl);
	      ਰੁੱਖ_TYPE (decl) = error_mark_ਗੰਢ;
	    }
	}

      ਜੇ (ਰੁੱਖ_ਵਰਤਿਆ (type))
	{
	  ਰੁੱਖ_ਵਰਤਿਆ (decl) = 1;
	  DECL_READ_P (decl) = 1;
	}
    }

  /* If this is a function and an assembler name is specified, reset DECL_RTL
     so we can give it its new name.  Also, update builtin_decl if it
     was a normal built-in.  */
  ਜੇ (ਰੁੱਖ_ਕੋਡ (decl) == FUNCTION_DECL && asmspec)
    {
      ਜੇ (DECL_BUILT_ਵਿੱਚ_CLASS (decl) == BUILT_ਵਿੱਚ_ਸਾਧਾਰਨ)
	ਸੈੱਟ_builtin_user_assembler_name (decl, asmspec);
      ਸੈੱਟ_user_assembler_name (decl, asmspec);
    }

  /* If #pragma weak was used, mark the decl weak now.  */
  maybe_apply_pragma_weak (decl);

  /* Output the assembler code and/or RTL code for variables and functions,
     unless the type is an undefined structure or union.
     If not, it will get done when the type is completed.  */

  ਜੇ (VAR_OR_FUNCTION_DECL_P (decl))
    {
      /* Determine the ELF visibility.  */
      ਜੇ (ਰੁੱਖ_ਜਨਤਕ (decl))
	c_determine_visibility (decl);

      /* This is a no-op in c-lang.cc or something real in objc-act.cc.  */
      ਜੇ (c_dialect_objc ())
	objc_check_decl (decl);

      ਜੇ (asmspec)
	{
	  /* If this is not a static variable, issue a warning.
	     It doesn't make any sense to give an ASMSPEC for an
	     ordinary, non-register local variable.  Historically,
	     GCC has accepted -- but ignored -- the ASMSPEC in
	     this case.  */
	  ਜੇ (!DECL_FILE_SCOPE_P (decl)
	      && VAR_P (decl)
	      && !C_DECL_ਰਜਿਸਟਰ (decl)
	      && !ਰੁੱਖ_STATIC (decl))
	    warning (0, "ignoring %<asm%> specifier for non-static local "
		     "variable %q+D", decl);
	  ਨਹੀਂਤਾਂ
	    ਸੈੱਟ_user_assembler_name (decl, asmspec);
	}

      ਜੇ (DECL_FILE_SCOPE_P (decl))
	{
	  ਜੇ (DECL_INITIAL (decl) == NULL_ਰੁੱਖ
	      || DECL_INITIAL (decl) == error_mark_ਗੰਢ)
	    /* Don't output anything
	       when a tentative file-scope definition is seen.
	       But at end of compilation, do output code for them.  */
	    DECL_DEFER_OUTPUT (decl) = 1;
	  ਜੇ (asmspec && VAR_P (decl) && C_DECL_ਰਜਿਸਟਰ (decl))
	    DECL_HARD_ਰਜਿਸਟਰ (decl) = 1;
	  rest_ਦਾ_decl_compilation (decl, ਸੱਚ, 0);

	  ਜੇ (ਰੁੱਖ_ਕੋਡ (decl) == FUNCTION_DECL)
	    {
	      ਰੁੱਖ parms = DECL_ARGUMENTS (decl);
	      ਅਚਲ ਤਾਰਕਿਕ builtin = fndecl_built_ਵਿੱਚ_p (decl);
	      ਜੇ (ਰੁੱਖ access = build_attr_access_from_parms (parms, !builtin))
		decl_ਗੁਣ (&decl, access, 0);
	    }
	}
      ਨਹੀਂਤਾਂ
	{
	  /* In conjunction with an ASMSPEC, the `register'
	     keyword indicates that we should place the variable
	     in a particular register.  */
	  ਜੇ (asmspec && C_DECL_ਰਜਿਸਟਰ (decl))
	    {
	      DECL_HARD_ਰਜਿਸਟਰ (decl) = 1;
	      /* This cannot be done for a structure with volatile
		 fields, on which DECL_REGISTER will have been
		 reset.  */
	      ਜੇ (!DECL_ਰਜਿਸਟਰ (decl))
		error ("cannot put object with volatile field into register");
	    }

	  ਜੇ (ਰੁੱਖ_ਕੋਡ (decl) != FUNCTION_DECL)
	    {
	      /* If we're building a variable sized type, and we might be
		 reachable other than via the top of the current binding
		 level, then create a new BIND_EXPR so that we deallocate
		 the object at the right time.  */
	      /* Note that DECL_SIZE can be null due to errors.  */
	      ਜੇ (DECL_ਮਾਪ (decl)
		  && !ਰੁੱਖ_CONSTANT (DECL_ਮਾਪ (decl))
		  && STATEMENT_LIST_HAS_LABEL (cur_stmt_list))
		{
		  ਰੁੱਖ bind;
		  bind = build3 (BIND_ਵਿਅੰਜਕ, void_type_ਗੰਢ, ਨਿਰਾ, ਨਿਰਾ, ਨਿਰਾ);
		  ਰੁੱਖ_SIDE_EFFECTS (bind) = 1;
		  ਜੋੜੋ_stmt (bind);
		  BIND_ਵਿਅੰਜਕ_BODY (bind) = ਧੱਕੋ_stmt_list ();
		}
	      ਜੋੜੋ_stmt (build_stmt (DECL_ਸਰੋਤ_LOCATION (decl),
				    DECL_ਵਿਅੰਜਕ, decl));
	    }
	}


      ਜੇ (!DECL_FILE_SCOPE_P (decl))
	{
	  /* Recompute the RTL of a local array now
	     if it used to be an incomplete type.  */
	  ਜੇ (was_incomplete && !is_global_var (decl))
	    {
	      /* If we used it already as memory, it must stay in memory.  */
	      ਰੁੱਖ_ADDRESSABLE (decl) = ਰੁੱਖ_ਵਰਤਿਆ (decl);
	      /* If it's still incomplete now, no init will save it.  */
	      ਜੇ (DECL_ਮਾਪ (decl) == NULL_ਰੁੱਖ)
		DECL_INITIAL (decl) = NULL_ਰੁੱਖ;
	    }
	}
    }

  ਜੇ (ਰੁੱਖ_ਕੋਡ (decl) == TYPE_DECL)
    {
      ਜੇ (!DECL_FILE_SCOPE_P (decl)
	  && c_type_variably_modified_p (ਰੁੱਖ_TYPE (decl)))
	ਜੋੜੋ_stmt (build_stmt (DECL_ਸਰੋਤ_LOCATION (decl), DECL_ਵਿਅੰਜਕ, decl));

      rest_ਦਾ_decl_compilation (decl, DECL_FILE_SCOPE_P (decl), 0);
    }

  /* Install a cleanup (aka destructor) if one was given.  */
  ਜੇ (VAR_P (decl) && !ਰੁੱਖ_STATIC (decl))
    {
      ਰੁੱਖ attr = lookup_attribute ("cleanup", DECL_ਗੁਣ (decl));
      ਜੇ (attr)
	{
	  ਰੁੱਖ cleanup_id = ਰੁੱਖ_ਮੁੱਲ (ਰੁੱਖ_ਮੁੱਲ (attr));
	  ਰੁੱਖ cleanup_decl = lookup_name (cleanup_id);
	  ਰੁੱਖ cleanup;
	  vec<ਰੁੱਖ, va_gc> *v;

	  /* Build "cleanup(&decl)" for the destructor.  */
	  cleanup = build_unary_op (ਨਿਵੇਸ਼_location, ADDR_ਵਿਅੰਜਕ, decl, ਝੂਠ);
	  vec_alloc (v, 1);
	  v->ਤੇਜ਼_ਧੱਕੋ (cleanup);
	  cleanup = c_build_function_call_vec (DECL_ਸਰੋਤ_LOCATION (decl),
					       vNULL, cleanup_decl, v, ਨਿਰਾ);
	  vec_free (v);

	  /* Don't warn about decl unused; the cleanup uses it.  */
	  ਰੁੱਖ_ਵਰਤਿਆ (decl) = 1;
	  ਰੁੱਖ_ਵਰਤਿਆ (cleanup_decl) = 1;
	  DECL_READ_P (decl) = 1;

	  ਧੱਕੋ_cleanup (decl, cleanup, ਝੂਠ);
	}
    }

  ਜੇ (warn_cxx_compat
      && VAR_P (decl)
      && !DECL_EXTERNAL (decl)
      && DECL_INITIAL (decl) == NULL_ਰੁੱਖ)
    {
      type = strip_array_types (type);
      ਜੇ (ਰੁੱਖ_READONLY (decl))
	warning_at (DECL_ਸਰੋਤ_LOCATION (decl), OPT_Wc___compat,
		    "uninitialized %<const %D%> is invalid in C++", decl);
      ਨਹੀਂਤਾਂ ਜੇ (ਰਿਕਾਰਡ_OR_UNION_TYPE_P (type)
	       && C_TYPE_FIELDS_READONLY (type))
	diagnose_uninitialized_cst_member (decl, type);
    }

  ਜੇ (flag_openmp
      && VAR_P (decl)
      && lookup_attribute ("omp declare target implicit",
			   DECL_ਗੁਣ (decl)))
    {
      DECL_ਗੁਣ (decl)
	= remove_attribute ("omp declare target implicit",
			    DECL_ਗੁਣ (decl));
      ਜੇ (!omp_mappable_type (ਰੁੱਖ_TYPE (decl)))
	error ("%q+D in declare target directive does not have mappable type",
	       decl);
      ਨਹੀਂਤਾਂ ਜੇ (!lookup_attribute ("omp declare target",
				  DECL_ਗੁਣ (decl))
	       && !lookup_attribute ("omp declare target link",
				     DECL_ਗੁਣ (decl)))
	{
	  DECL_ਗੁਣ (decl)
	    = ਰੁੱਖ_cons (get_identifier ("omp declare target"),
			 NULL_ਰੁੱਖ, DECL_ਗੁਣ (decl));
	    symtab_ਗੰਢ *ਗੰਢ = symtab_ਗੰਢ::get (decl);
	    ਜੇ (ਗੰਢ != ਨਿਰਾ)
	      {
		ਗੰਢ->offloadable = 1;
		ਜੇ (ENABLE_OFFLOADING)
		  {
		    g->have_offload = ਸੱਚ;
		    ਜੇ (is_a <varpool_ਗੰਢ *> (ਗੰਢ))
		      vec_ਸੁਰੱਖਿਅਤ_ਧੱਕੋ (offload_vars, decl);
		  }
	      }
	}
    }

  /* This is the last point we can lower alignment so give the target the
     chance to do so.  */
  ਜੇ (VAR_P (decl)
      && !is_global_var (decl)
      && !DECL_HARD_ਰਜਿਸਟਰ (decl))
    targetm.ਹੇਠਲਾ_local_decl_alignment (decl);

  invoke_plugin_callbacks (PLUGIN_ਅੰਤ_DECL, decl);
}

/* Given a parsed parameter declaration, decode it into a PARM_DECL.
   EXPR is NULL or a pointer to an expression that needs to be
   evaluated for the side effects of array size expressions in the
   parameters.  */

ਰੁੱਖ
grokparm (ਅਚਲ ਬਣਤਰ c_parm *parm, ਰੁੱਖ *ਵਿਅੰਜਕ)
{
  ਰੁੱਖ attrs = parm->attrs;
  ਰੁੱਖ decl = grokdeclarator (parm->declarator, parm->specs, PARM, ਝੂਠ,
			      ਨਿਰਾ, &attrs, ਵਿਅੰਜਕ, ਨਿਰਾ, DEPRECATED_ਸਾਧਾਰਨ);

  decl_ਗੁਣ (&decl, attrs, 0);

  ਵਾਪਸ decl;
}



/* Given a parsed parameter declaration, decode it into a PARM_DECL
   and push that on the current scope.  EXPR is a pointer to an
   expression that needs to be evaluated for the side effects of array
   size expressions in the parameters.  */

ਖਾਲੀ
ਧੱਕੋ_parm_decl (ਅਚਲ ਬਣਤਰ c_parm *parm, ਰੁੱਖ *ਵਿਅੰਜਕ)
{
  ਰੁੱਖ attrs = parm->attrs;
  ਰੁੱਖ decl = grokdeclarator (parm->declarator, parm->specs, PARM, ਝੂਠ, ਨਿਰਾ,
			      &attrs, ਵਿਅੰਜਕ, ਨਿਰਾ, DEPRECATED_ਸਾਧਾਰਨ);
  ਜੇ (decl && DECL_P (decl))
    DECL_ਸਰੋਤ_LOCATION (decl) = parm->loc;

  decl_ਗੁਣ (&decl, attrs, 0);

  decl = pushdecl (decl);

  ਅੰਤ_decl (decl, ਨਿਵੇਸ਼_location, NULL_ਰੁੱਖ, NULL_ਰੁੱਖ, NULL_ਰੁੱਖ);
}

/* Mark all the parameter declarations to date as forward decls.
   Also diagnose use of this extension.  */

ਖਾਲੀ
mark_forward_parm_decls (ਖਾਲੀ)
{
  ਬਣਤਰ c_binding *b;

  ਜੇ (current_scope->had_forward_parm_decls)
    warning_at (ਨਿਵੇਸ਼_location, OPT_Wmultiple_parameter_fwd_decl_lists,
		"more than one list of forward declarations of parameters");
  ਜੇ (pedantic && !current_scope->had_forward_parm_decls)
    pedwarn (ਨਿਵੇਸ਼_location, OPT_Wpedantic,
	     "ISO C forbids forward parameter declarations");

  current_scope->had_forward_parm_decls = ਸੱਚ;

  ਲਈ (b = current_scope->bindings; b; b = b->prev)
    ਜੇ (ਰੁੱਖ_ਕੋਡ (b->decl) == PARM_DECL)
      ਰੁੱਖ_ASM_WRITTEN (b->decl) = 1;
}

/* Build a COMPOUND_LITERAL_EXPR.  TYPE is the type given in the compound
   literal, which may be an incomplete array type completed by the
   initializer; INIT is a CONSTRUCTOR at LOC that initializes the compound
   literal.  NON_CONST is true if the initializers contain something
   that cannot occur in a constant expression.  If ALIGNAS_ALIGN is nonzero,
   it is the (valid) alignment for this compound literal, as specified
   with _Alignas.  SCSPECS are the storage class specifiers (C23) from the
   compound literal.  */

ਰੁੱਖ
build_compound_literal (location_t loc, ਰੁੱਖ type, ਰੁੱਖ init, ਤਾਰਕਿਕ non_const,
			ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ alignas_align,
			ਬਣਤਰ c_declspecs *scspecs)
{
  /* We do not use start_decl here because we have a type, not a declarator;
     and do not use finish_decl because the decl should be stored inside
     the COMPOUND_LITERAL_EXPR rather than added elsewhere as a DECL_EXPR.  */
  ਰੁੱਖ decl;
  ਰੁੱਖ complit;
  ਰੁੱਖ stmt;
  ਤਾਰਕਿਕ threadp = scspecs ? scspecs->thread_p : ਝੂਠ;
  ਗਿਣਤੀ c_storage_class storage_class = (scspecs
					? scspecs->storage_class
					: csc_none);

  ਜੇ (type == error_mark_ਗੰਢ
      || init == error_mark_ਗੰਢ)
    ਵਾਪਸ error_mark_ਗੰਢ;

  ਜੇ (current_scope == file_scope && storage_class == csc_ਰਜਿਸਟਰ)
    {
      error_at (loc, "file-scope compound literal specifies %<register%>");
      storage_class = csc_none;
    }

  ਜੇ (current_scope != file_scope && threadp && storage_class == csc_none)
    {
      error_at (loc, "compound literal implicitly auto and declared %qs",
		scspecs->thread_gnu_p ? "__thread" : "_Thread_local");
      threadp = ਝੂਠ;
    }

  decl = build_decl (loc, VAR_DECL, NULL_ਰੁੱਖ, type);
  DECL_EXTERNAL (decl) = 0;
  ਰੁੱਖ_ਜਨਤਕ (decl) = 0;
  ਰੁੱਖ_STATIC (decl) = (current_scope == file_scope
			|| storage_class == csc_static);
  DECL_CONTEXT (decl) = current_function_decl;
  ਰੁੱਖ_ਵਰਤਿਆ (decl) = 1;
  DECL_READ_P (decl) = 1;
  DECL_ARTIFICIAL (decl) = 1;
  DECL_IGNORED_P (decl) = 1;
  C_DECL_COMPOUND_LITERAL_P (decl) = 1;
  C_DECL_DECLARED_CONSTEXPR (decl) = scspecs && scspecs->constexpr_p;
  ਰੁੱਖ_TYPE (decl) = type;
  ਜੇ (threadp)
    ਸੈੱਟ_decl_tls_model (decl, decl_default_tls_model (decl));
  ਜੇ (storage_class == csc_ਰਜਿਸਟਰ)
    {
      C_DECL_ਰਜਿਸਟਰ (decl) = 1;
      DECL_ਰਜਿਸਟਰ (decl) = 1;
    }
  c_apply_type_quals_ਮੰਜ਼ਿਲ_decl (TYPE_QUALS (strip_array_types (type)), decl);
  ਜੇ (alignas_align)
    {
      ਸੈੱਟ_DECL_ALIGN (decl, alignas_align * ਬਿੱਟ_ਪ੍ਰਤੀ_UNIT);
      DECL_USER_ALIGN (decl) = 1;
    }
  store_init_ਮੁੱਲ (loc, decl, init, NULL_ਰੁੱਖ);
  ਜੇ (current_scope != file_scope
      && ਰੁੱਖ_STATIC (decl)
      && !ਰੁੱਖ_READONLY (decl)
      && DECL_DECLARED_INLINE_P (current_function_decl)
      && DECL_EXTERNAL (current_function_decl))
    ਰਿਕਾਰਡ_inline_static (ਨਿਵੇਸ਼_location, current_function_decl,
			  decl, csi_modifiable);

  ਜੇ (ਰੁੱਖ_ਕੋਡ (type) == ARRAY_TYPE && !COMPLETE_TYPE_P (type))
    {
      ਪੂਰਨ failure = complete_array_type (&ਰੁੱਖ_TYPE (decl),
					 DECL_INITIAL (decl), ਸੱਚ);
      /* If complete_array_type returns 3, it means that the initial value of
         the compound literal is empty.  Allow it with a pedwarn; in pre-C23
         modes, the empty initializer itself has been diagnosed if pedantic so
         does not need to be diagnosed again here.  */
      gcc_assert (failure == 0 || failure == 3);
      ਜੇ (failure == 3 && flag_isoc23)
	pedwarn (loc, OPT_Wpedantic,
		 "array of unknown size with empty initializer");

      type = ਰੁੱਖ_TYPE (decl);
      ਰੁੱਖ_TYPE (DECL_INITIAL (decl)) = type;
      relayout_decl (decl);
    }

  ਜੇ (type == error_mark_ਗੰਢ || !COMPLETE_TYPE_P (type))
    {
      c_incomplete_type_error (loc, NULL_ਰੁੱਖ, type);
      ਵਾਪਸ error_mark_ਗੰਢ;
    }

  ਜੇ ((ਰੁੱਖ_STATIC (decl) || C_DECL_DECLARED_CONSTEXPR (decl))
      && C_TYPE_VARIABLE_ਮਾਪ (type))
    error_at (loc, "storage size isn%'t constant");

  ਜੇ (ਰੁੱਖ_STATIC (decl)
      && !verify_type_context (loc, TCTX_STATIC_STORAGE, type))
    ਵਾਪਸ error_mark_ਗੰਢ;

  stmt = build_stmt (DECL_ਸਰੋਤ_LOCATION (decl), DECL_ਵਿਅੰਜਕ, decl);
  complit = build1 (COMPOUND_LITERAL_ਵਿਅੰਜਕ, type, stmt);
  ਰੁੱਖ_SIDE_EFFECTS (complit) = 1;

  layout_decl (decl, 0);

  ਜੇ (ਰੁੱਖ_STATIC (decl))
    {
      /* This decl needs a name for the assembler output.  */
      ਸੈੱਟ_compound_literal_name (decl);
      DECL_DEFER_OUTPUT (decl) = 1;
      DECL_COMDAT (decl) = 1;
      pushdecl (decl);
      rest_ਦਾ_decl_compilation (decl, 1, 0);
    }
  ਨਹੀਂਤਾਂ ਜੇ (current_function_decl && !current_scope->parm_flag)
    pushdecl (decl);

  ਜੇ (non_const)
    {
      complit = build2 (C_MAYBE_CONST_ਵਿਅੰਜਕ, type, ਨਿਰਾ, complit);
      C_MAYBE_CONST_ਵਿਅੰਜਕ_NON_CONST (complit) = 1;
    }

  ਵਾਪਸ complit;
}

/* Check the type of a compound literal.  Here we just check that it
   is valid for C++.  */

ਖਾਲੀ
check_compound_literal_type (location_t loc, ਬਣਤਰ c_type_name *type_name)
{
  ਜੇ (warn_cxx_compat
      && (type_name->specs->typespec_ਕਿਸਮ == ctsk_tagdef
          || type_name->specs->typespec_ਕਿਸਮ == ctsk_tagfirstref
	  || type_name->specs->typespec_ਕਿਸਮ == ctsk_tagfirstref_attrs))
    warning_at (loc, OPT_Wc___compat,
		"defining a type in a compound literal is invalid in C++");
}

/* Performs sanity checks on the TYPE and WIDTH of the bit-field NAME,
   replacing with appropriate values if they are invalid.  */

ਸਥਿਰ ਖਾਲੀ
check_bitfield_type_and_ਚੌੜਾਈ (location_t loc, ਰੁੱਖ *type, ਰੁੱਖ *ਚੌੜਾਈ,
			       ਰੁੱਖ orig_name)
{
  ਰੁੱਖ type_mv;
  ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ max_ਚੌੜਾਈ;
  ਬਿਨਾਨਿਸ਼ਾਨੀ HOST_WIDE_INT w;
  ਅਚਲ ਅੱਖਰ *name = (orig_name
		      ? identifier_ਮੰਜ਼ਿਲ_locale (IDENTIFIER_ਸੂਚਕ (orig_name))
		      : _("<anonymous>"));

  /* Detect and ignore out of range field width and process valid
     field widths.  */
  ਜੇ (!INTEGRAL_TYPE_P (ਰੁੱਖ_TYPE (*ਚੌੜਾਈ)))
    {
      error_at (loc, "bit-field %qs width not an integer constant", name);
      *ਚੌੜਾਈ = integer_one_ਗੰਢ;
    }
  ਨਹੀਂਤਾਂ
    {
      ਜੇ (ਰੁੱਖ_ਕੋਡ (*ਚੌੜਾਈ) != INTEGER_CST)
	{
	  *ਚੌੜਾਈ = c_fully_fold (*ਚੌੜਾਈ, ਝੂਠ, ਨਿਰਾ);
	  ਜੇ (ਰੁੱਖ_ਕੋਡ (*ਚੌੜਾਈ) == INTEGER_CST)
	    pedwarn (loc, OPT_Wpedantic,
		     "bit-field %qs width not an integer constant expression",
		     name);
	}
      ਜੇ (ਰੁੱਖ_ਕੋਡ (*ਚੌੜਾਈ) != INTEGER_CST)
	{
	  error_at (loc, "bit-field %qs width not an integer constant", name);
	  *ਚੌੜਾਈ = integer_one_ਗੰਢ;
	}
      constant_ਵਿਅੰਜਕ_warning (*ਚੌੜਾਈ);
      ਜੇ (ਰੁੱਖ_int_cst_sgn (*ਚੌੜਾਈ) < 0)
	{
	  error_at (loc, "negative width in bit-field %qs", name);
	  *ਚੌੜਾਈ = integer_one_ਗੰਢ;
	}
      ਨਹੀਂਤਾਂ ਜੇ (integer_zerop (*ਚੌੜਾਈ) && orig_name)
	{
	  error_at (loc, "zero width for bit-field %qs", name);
	  *ਚੌੜਾਈ = integer_one_ਗੰਢ;
	}
    }

  /* Detect invalid bit-field type.  */
  ਜੇ (ਰੁੱਖ_ਕੋਡ (*type) != INTEGER_TYPE
      && ਰੁੱਖ_ਕੋਡ (*type) != BOOLEAN_TYPE
      && ਰੁੱਖ_ਕੋਡ (*type) != ENUMERAL_TYPE
      && ਰੁੱਖ_ਕੋਡ (*type) != BITINT_TYPE)
    {
      error_at (loc, "bit-field %qs has invalid type", name);
      *type = unsigned_type_ਗੰਢ;
    }

  ਜੇ (TYPE_WARN_IF_NOT_ALIGN (*type))
    {
      error_at (loc, "cannot declare bit-field %qs with %<warn_if_not_aligned%> type",
		name);
      *type = unsigned_type_ਗੰਢ;
    }

  type_mv = TYPE_MAIN_VARIANT (*type);
  ਜੇ (!ਵਿੱਚ_system_ਸਿਰਲੇਖ_at (ਨਿਵੇਸ਼_location)
      && type_mv != integer_type_ਗੰਢ
      && type_mv != unsigned_type_ਗੰਢ
      && type_mv != boolean_type_ਗੰਢ)
    pedwarn_c90 (loc, OPT_Wpedantic,
		 "type of bit-field %qs is a GCC extension", name);

  max_ਚੌੜਾਈ = TYPE_PRECISION (*type);

  ਜੇ (compare_ਰੁੱਖ_int (*ਚੌੜਾਈ, max_ਚੌੜਾਈ) > 0)
    {
      error_at (loc, "width of %qs exceeds its type", name);
      w = max_ਚੌੜਾਈ;
      *ਚੌੜਾਈ = build_int_cst (integer_type_ਗੰਢ, w);
    }
  ਨਹੀਂਤਾਂ
    w = ਰੁੱਖ_ਮੰਜ਼ਿਲ_uhwi (*ਚੌੜਾਈ);

  /* Truncation of hardbool false and true representation values is always safe:
     either the values remain different, or we'll report a problem when creating
     the narrower type.  */
  ਜੇ (c_hardbool_type_attr (*type))
    ਵਾਪਸ;

  ਜੇ (ਰੁੱਖ_ਕੋਡ (*type) == ENUMERAL_TYPE)
    {
      ਬਣਤਰ lang_type *lt = TYPE_LANG_SPECIFIC (*type);
      ਜੇ (!lt
	  || w < ਰੁੱਖ_int_cst_min_precision (lt->enum_min, TYPE_SIGN (*type))
	  || w < ਰੁੱਖ_int_cst_min_precision (lt->enum_max, TYPE_SIGN (*type)))
	warning_at (loc, 0, "%qs is narrower than values of its type", name);
    }
}



/* Print warning about variable length array if necessary.  */

ਸਥਿਰ ਖਾਲੀ
warn_variable_ਲੰਮਾਈ_array (ਰੁੱਖ name, ਰੁੱਖ ਮਾਪ)
{
  ਜੇ (ਰੁੱਖ_CONSTANT (ਮਾਪ))
    {
      ਜੇ (name)
	pedwarn_c90 (ਨਿਵੇਸ਼_location, OPT_Wvla,
		     "ISO C90 forbids array %qE whose size "
		     "cannot be evaluated", name);
      ਨਹੀਂਤਾਂ
	pedwarn_c90 (ਨਿਵੇਸ਼_location, OPT_Wvla, "ISO C90 forbids array "
		     "whose size cannot be evaluated");
    }
  ਨਹੀਂਤਾਂ
    {
      ਜੇ (name)
	pedwarn_c90 (ਨਿਵੇਸ਼_location, OPT_Wvla,
		     "ISO C90 forbids variable length array %qE", name);
      ਨਹੀਂਤਾਂ
	pedwarn_c90 (ਨਿਵੇਸ਼_location, OPT_Wvla, "ISO C90 forbids variable "
		     "length array");
    }
}

/* Returns the smallest location != UNKNOWN_LOCATION in LOCATIONS,
   considering only those c_declspec_words found in LIST, which
   must be terminated by cdw_number_of_elements.  */

ਸਥਿਰ location_t
ਸਭ_ਤੋਂ_ਛੋਟਾ_type_quals_location (ਅਚਲ location_t *locations,
			      ਅਚਲ c_declspec_ਸ਼ਬਦ *list)
{
  location_t loc = UNKNOWN_LOCATION;
  ਜਦੋਂ (*list != cdw_ਸੰਖਿਆ_ਦਾ_elements)
    {
      location_t newloc = locations[*list];
      ਜੇ (loc == UNKNOWN_LOCATION
	  || (newloc != UNKNOWN_LOCATION && newloc < loc))
	loc = newloc;
      list++;
    }

  ਵਾਪਸ loc;
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
ਸਥਿਰ ਖਾਲੀ
ਜੋੜੋ_decl_ਵਿਅੰਜਕ (location_t loc, ਰੁੱਖ type, ਰੁੱਖ *ਵਿਅੰਜਕ, ਤਾਰਕਿਕ ਸੈੱਟ_name_p)
{
  ਰੁੱਖ bind = NULL_ਰੁੱਖ;
  ਜੇ (ਵਿਅੰਜਕ)
    {
      bind = build3 (BIND_ਵਿਅੰਜਕ, void_type_ਗੰਢ, NULL_ਰੁੱਖ, NULL_ਰੁੱਖ,
		     NULL_ਰੁੱਖ);
      ਰੁੱਖ_SIDE_EFFECTS (bind) = 1;
      BIND_ਵਿਅੰਜਕ_BODY (bind) = ਧੱਕੋ_stmt_list ();
      ਧੱਕੋ_scope ();
    }

  ਰੁੱਖ decl = build_decl (loc, TYPE_DECL, NULL_ਰੁੱਖ, type);
  pushdecl (decl);
  DECL_ARTIFICIAL (decl) = 1;
  ਜੋੜੋ_stmt (build_stmt (DECL_ਸਰੋਤ_LOCATION (decl), DECL_ਵਿਅੰਜਕ, decl));
  ਜੇ (ਸੈੱਟ_name_p)
    TYPE_NAME (type) = decl;

  ਜੇ (bind)
    {
      ਕੱਢੋ_scope ();
      BIND_ਵਿਅੰਜਕ_BODY (bind) = ਕੱਢੋ_stmt_list (BIND_ਵਿਅੰਜਕ_BODY (bind));
      ਜੇ (*ਵਿਅੰਜਕ)
	*ਵਿਅੰਜਕ = build2 (COMPOUND_ਵਿਅੰਜਕ, void_type_ਗੰਢ, *ਵਿਅੰਜਕ, bind);
      ਨਹੀਂਤਾਂ
	*ਵਿਅੰਜਕ = bind;
    }
}


/* Add attribute "arg spec" to ATTRS corresponding to an array/VLA parameter
   declared with type TYPE.  The attribute has two arguments.  The first is
   a string that encodes the presence of the static keyword.  The second is
   the declared type of the array before adjustment, i.e. as an array type
   including the outermost bound.  */

ਸਥਿਰ ਰੁੱਖ
build_arg_spec_attribute (ਰੁੱਖ type, ਤਾਰਕਿਕ static_p, ਰੁੱਖ attrs)
{
  ਰੁੱਖ vbchain = ਰੁੱਖ_cons (NULL_ਰੁੱਖ, type, NULL_ਰੁੱਖ);
  ਰੁੱਖ acsstr = static_p ? build_string (7, "static") :
			   build_string (1, "");
  ਰੁੱਖ ਦਲੀਲਾਂ = ਰੁੱਖ_cons (NULL_ਰੁੱਖ, acsstr, vbchain);
  ਰੁੱਖ name = get_identifier ("arg spec");
  ਵਾਪਸ ਰੁੱਖ_cons (name, ਦਲੀਲਾਂ, attrs);
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

ਸਥਿਰ ਰੁੱਖ
grokdeclarator (ਅਚਲ ਬਣਤਰ c_declarator *declarator,
		ਬਣਤਰ c_declspecs *declspecs,
		ਗਿਣਤੀ decl_context decl_context, ਤਾਰਕਿਕ initialized, ਰੁੱਖ *ਚੌੜਾਈ,
		ਰੁੱਖ *decl_attrs, ਰੁੱਖ *ਵਿਅੰਜਕ, ਤਾਰਕਿਕ *ਵਿਅੰਜਕ_const_operands,
		ਗਿਣਤੀ deprecated_ਹਾਲਤਾਂ deprecated_state)
{
  ਰੁੱਖ type = declspecs->type;
  ਤਾਰਕਿਕ threadp = declspecs->thread_p;
  ਤਾਰਕਿਕ constexprp = declspecs->constexpr_p;
  ਗਿਣਤੀ c_storage_class storage_class = declspecs->storage_class;
  ਪੂਰਨ constp;
  ਪੂਰਨ restrictp;
  ਪੂਰਨ volatilep;
  ਪੂਰਨ atomicp;
  ਪੂਰਨ type_quals = TYPE_UNQUALIFIED;
  ਰੁੱਖ name = NULL_ਰੁੱਖ;
  ਤਾਰਕਿਕ funcdef_flag = ਝੂਠ;
  ਤਾਰਕਿਕ funcdef_syntax = ਝੂਠ;
  ਤਾਰਕਿਕ ਮਾਪ_varies = ਝੂਠ;
  ਤਾਰਕਿਕ ਮਾਪ_error = ਝੂਠ;
  ਰੁੱਖ decl_attr = declspecs->decl_attr;
  ਪੂਰਨ array_ptr_quals = TYPE_UNQUALIFIED;
  ਰੁੱਖ array_ptr_attrs = NULL_ਰੁੱਖ;
  ਤਾਰਕਿਕ array_parm_static = ਝੂਠ;
  ਤਾਰਕਿਕ array_parm_vla_unspec_p = ਝੂਠ;
  ਰੁੱਖ returned_attrs = NULL_ਰੁੱਖ;
  ਰੁੱਖ decl_id_attrs = NULL_ਰੁੱਖ;
  ਤਾਰਕਿਕ bitfield = ਚੌੜਾਈ != ਨਿਰਾ;
  ਰੁੱਖ element_type;
  ਰੁੱਖ orig_qual_type = ਨਿਰਾ;
  ਮਾਪ_t orig_qual_ਅਸਿੱਧਾ = 0;
  ਬਣਤਰ c_arg_info *arg_info = 0;
  addr_space_t as1, as2, ਪਤਾ_space;
  location_t loc = UNKNOWN_LOCATION;
  ਰੁੱਖ ਵਿਅੰਜਕ_dummy;
  ਤਾਰਕਿਕ ਵਿਅੰਜਕ_const_operands_dummy;
  ਗਿਣਤੀ c_declarator_ਕਿਸਮ ਪਹਿਲਾ_non_attr_ਕਿਸਮ;
  ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ alignas_align = 0;

  ਜੇ (type == NULL_ਰੁੱਖ)
    {
      /* This can occur for auto on a parameter in C23 mode.  Set a
	 dummy type here so subsequent code can give diagnostics for
	 this case.  */
      gcc_assert (declspecs->c23_auto_p);
      gcc_assert (decl_context == PARM);
      type = declspecs->type = integer_type_ਗੰਢ;
    }
  ਜੇ (ਰੁੱਖ_ਕੋਡ (type) == ERROR_MARK)
    ਵਾਪਸ error_mark_ਗੰਢ;
  ਜੇ (ਵਿਅੰਜਕ == ਨਿਰਾ)
    {
      ਵਿਅੰਜਕ = &ਵਿਅੰਜਕ_dummy;
      ਵਿਅੰਜਕ_dummy = NULL_ਰੁੱਖ;
    }
  ਜੇ (ਵਿਅੰਜਕ_const_operands == ਨਿਰਾ)
    ਵਿਅੰਜਕ_const_operands = &ਵਿਅੰਜਕ_const_operands_dummy;

  ਜੇ (declspecs->ਵਿਅੰਜਕ)
    {
      ਜੇ (*ਵਿਅੰਜਕ)
	*ਵਿਅੰਜਕ = build2 (COMPOUND_ਵਿਅੰਜਕ, ਰੁੱਖ_TYPE (declspecs->ਵਿਅੰਜਕ), *ਵਿਅੰਜਕ,
			declspecs->ਵਿਅੰਜਕ);
      ਨਹੀਂਤਾਂ
	*ਵਿਅੰਜਕ = declspecs->ਵਿਅੰਜਕ;
    }
  *ਵਿਅੰਜਕ_const_operands = declspecs->ਵਿਅੰਜਕ_const_operands;

  ਜੇ (decl_context == FUNCDEF)
    funcdef_flag = ਸੱਚ, decl_context = ਸਾਧਾਰਨ;

  /* Look inside a declarator for the name being declared
     and get it as an IDENTIFIER_NODE, for an error message.  */
  {
    ਅਚਲ ਬਣਤਰ c_declarator *decl = declarator;

    ਪਹਿਲਾ_non_attr_ਕਿਸਮ = cdk_attrs;
    ਜਦੋਂ (decl)
      ਚੋਣ (decl->ਕਿਸਮ)
	{
	ਹਾਲਤ cdk_array:
	  loc = decl->id_loc;
	  /* FALL THRU.  */

	ਹਾਲਤ cdk_function:
	ਹਾਲਤ cdk_ਸੂਚਕ:
	  funcdef_syntax = (decl->ਕਿਸਮ == cdk_function);
	  ਜੇ (ਪਹਿਲਾ_non_attr_ਕਿਸਮ == cdk_attrs)
	    ਪਹਿਲਾ_non_attr_ਕਿਸਮ = decl->ਕਿਸਮ;
	  decl = decl->declarator;
	  ਰੋਕੋ;

	ਹਾਲਤ cdk_attrs:
	  decl = decl->declarator;
	  ਰੋਕੋ;

	ਹਾਲਤ cdk_id:
	  loc = decl->id_loc;
	  ਜੇ (decl->u.id.id)
	    name = decl->u.id.id;
	  decl_id_attrs = decl->u.id.attrs;
	  ਜੇ (ਪਹਿਲਾ_non_attr_ਕਿਸਮ == cdk_attrs)
	    ਪਹਿਲਾ_non_attr_ਕਿਸਮ = decl->ਕਿਸਮ;
	  decl = 0;
	  ਰੋਕੋ;

	ਮੂਲ:
	  gcc_unreachable ();
	}
    ਜੇ (name == NULL_ਰੁੱਖ)
      {
	gcc_assert (decl_context == PARM
		    || decl_context == TYPENAME
		    || decl_context == GENERIC_ASSOC
		    || (decl_context == ਖੇਤਰ
			&& declarator->ਕਿਸਮ == cdk_id));
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
  ਜੇ (declspecs->enum_type_specifier_ref_p)
    error_at (loc, "%<enum%> underlying type may not be specified here");

  /* A function definition's declarator must have the form of
     a function declarator.  */

  ਜੇ (funcdef_flag && !funcdef_syntax)
    ਵਾਪਸ NULL_ਰੁੱਖ;

  /* If this looks like a function definition, make it one,
     even if it occurs where parms are expected.
     Then store_parm_decls will reject it and not use it as a parm.  */
  ਜੇ (decl_context == ਸਾਧਾਰਨ && !funcdef_flag && current_scope->parm_flag)
    decl_context = PARM;

  ਜੇ (deprecated_state != UNAVAILABLE_DEPRECATED_SUPPRESS)
    {
      ਜੇ (declspecs->unavailable_p)
	error_unavailable_use (declspecs->type, declspecs->decl_attr);
      ਨਹੀਂਤਾਂ ਜੇ (declspecs->deprecated_p
		&& deprecated_state != DEPRECATED_SUPPRESS)
	warn_deprecated_use (declspecs->type, declspecs->decl_attr);
    }

  ਜੇ ((decl_context == ਸਾਧਾਰਨ || decl_context == ਖੇਤਰ)
      && current_scope == file_scope
      && c_type_variably_modified_p (type))
    {
      ਜੇ (name)
	error_at (loc, "variably modified %qE at file scope", name);
      ਨਹੀਂਤਾਂ
	error_at (loc, "variably modified field at file scope");
      type = integer_type_ਗੰਢ;
    }

  ਮਾਪ_varies = C_TYPE_VARIABLE_ਮਾਪ (type) != 0;

  /* Diagnose defaulting to "int".  */

  ਜੇ (declspecs->default_int_p)
    {
      /* Issue a warning if this is an ISO C 99 program or if
	 -Wreturn-type and this is a function, or if -Wimplicit;
	 prefer the former warning since it is more explicit.  */
      ਜੇ ((warn_implicit_int || warn_return_type > 0 || flag_isoc99)
	  && funcdef_flag)
	warn_about_return_type = 1;
      ਨਹੀਂਤਾਂ
	{
	  ਜੇ (name)
	    permerror_opt (loc, OPT_Wimplicit_int,
			   "type defaults to %<int%> in declaration "
			   "of %qE", name);
	  ਨਹੀਂਤਾਂ
	    permerror_opt (loc, OPT_Wimplicit_int,
			   "type defaults to %<int%> in type name");
	}
    }

  /* Adjust the type if a bit-field is being declared,
     -funsigned-bitfields applied and the type is not explicitly
     "signed".  */
  ਜੇ (bitfield && !flag_signed_bitfields && !declspecs->explicit_signed_p
      && ਰੁੱਖ_ਕੋਡ (type) == INTEGER_TYPE)
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
  as1 = declspecs->ਪਤਾ_space;
  as2 = TYPE_ADDR_SPACE (element_type);
  ਪਤਾ_space = ADDR_SPACE_GENERIC_P (as1)? as2 : as1;

  ਜੇ (constp > 1)
    pedwarn_c90 (loc, OPT_Wpedantic, "duplicate %<const%>");
  ਜੇ (restrictp > 1)
    pedwarn_c90 (loc, OPT_Wpedantic, "duplicate %<restrict%>");
  ਜੇ (volatilep > 1)
    pedwarn_c90 (loc, OPT_Wpedantic, "duplicate %<volatile%>");
  ਜੇ (atomicp > 1)
    pedwarn_c90 (loc, OPT_Wpedantic, "duplicate %<_Atomic%>");

  ਜੇ (!ADDR_SPACE_GENERIC_P (as1) && !ADDR_SPACE_GENERIC_P (as2) && as1 != as2)
    error_at (loc, "conflicting named address spaces (%s vs %s)",
	      c_addr_space_name (as1), c_addr_space_name (as2));

  ਜੇ ((ਰੁੱਖ_ਕੋਡ (type) == ARRAY_TYPE
       || ਪਹਿਲਾ_non_attr_ਕਿਸਮ == cdk_array)
      && TYPE_QUALS (element_type))
    {
      orig_qual_type = type;
      type = c_build_qualified_type (type, TYPE_UNQUALIFIED);
    }
  type_quals = ((constp ? TYPE_QUAL_CONST : 0)
		| (restrictp ? TYPE_QUAL_RESTRICT : 0)
		| (volatilep ? TYPE_QUAL_VOLATILE : 0)
		| (atomicp ? TYPE_QUAL_ATOMIC : 0)
		| ENCODE_QUAL_ADDR_SPACE (ਪਤਾ_space));
  ਜੇ (type_quals != TYPE_QUALS (element_type))
    orig_qual_type = NULL_ਰੁੱਖ;

  /* Applying the _Atomic qualifier to an array type (through the use
     of typedefs or typeof) must be detected here.  If the qualifier
     is introduced later, any appearance of applying it to an array is
     actually applying it to an element of that array.  */
  ਜੇ (declspecs->atomic_p && ਰੁੱਖ_ਕੋਡ (type) == ARRAY_TYPE)
    error_at (loc, "%<_Atomic%>-qualified array type");

  /* Warn about storage classes that are invalid for certain
     kinds of declarations (parameters, typenames, etc.).  */

  ਜੇ (funcdef_flag
      && (threadp
	  || constexprp
	  || storage_class == csc_auto
	  || storage_class == csc_ਰਜਿਸਟਰ
	  || storage_class == csc_typedef))
    {
      ਜੇ (storage_class == csc_auto)
	pedwarn (loc,
		 (current_scope == file_scope) ? 0 : OPT_Wpedantic,
		 "function definition declared %<auto%>");
      ਜੇ (storage_class == csc_ਰਜਿਸਟਰ)
	error_at (loc, "function definition declared %<register%>");
      ਜੇ (storage_class == csc_typedef)
	error_at (loc, "function definition declared %<typedef%>");
      ਜੇ (threadp)
	error_at (loc, "function definition declared %qs",
		  declspecs->thread_gnu_p ? "__thread" : "_Thread_local");
      threadp = ਝੂਠ;
      /* The parser ensures a constexpr function definition never
	 reaches here.  */
      gcc_assert (!constexprp);
      ਜੇ (storage_class == csc_auto
	  || storage_class == csc_ਰਜਿਸਟਰ
	  || storage_class == csc_typedef)
	storage_class = csc_none;
    }
  ਨਹੀਂਤਾਂ ਜੇ (decl_context != ਸਾਧਾਰਨ && (storage_class != csc_none
				      || threadp
				      || constexprp
				      || declspecs->c23_auto_p))
    {
      ਜੇ (decl_context == PARM
	  && storage_class == csc_ਰਜਿਸਟਰ
	  && !constexprp
	  && !declspecs->c23_auto_p)
	;
      ਨਹੀਂਤਾਂ
	{
	  ਚੋਣ (decl_context)
	    {
	    ਹਾਲਤ ਖੇਤਰ:
	      ਜੇ (name)
		error_at (loc, "storage class specified for structure "
		    	  "field %qE", name);
	      ਨਹੀਂਤਾਂ
		error_at (loc, "storage class specified for structure field");
	      ਰੋਕੋ;
	    ਹਾਲਤ PARM:
	      ਜੇ (name)
		error_at (loc, "storage class specified for parameter %qE",
		    	  name);
	      ਨਹੀਂਤਾਂ
		error_at (loc, "storage class specified for unnamed parameter");
	      ਰੋਕੋ;
	    ਮੂਲ:
	      error_at (loc, "storage class specified for typename");
	      ਰੋਕੋ;
	    }
	  storage_class = csc_none;
	  threadp = ਝੂਠ;
	  constexprp = ਝੂਠ;
	}
    }
  ਨਹੀਂਤਾਂ ਜੇ (storage_class == csc_extern
	   && initialized
	   && !funcdef_flag)
    {
      /* 'extern' with initialization is invalid if not at file scope.  */
       ਜੇ (current_scope == file_scope)
         {
           /* It is fine to have 'extern const' when compiling at C
              and C++ intersection.  */
           ਜੇ (!(warn_cxx_compat && constp))
             warning_at (loc, 0, "%qE initialized and declared %<extern%>",
		 	 name);
         }
      ਨਹੀਂਤਾਂ
	error_at (loc, "%qE has both %<extern%> and initializer", name);
    }
  ਨਹੀਂਤਾਂ ਜੇ (current_scope == file_scope)
    {
      ਜੇ (storage_class == csc_auto)
	error_at (loc, "file-scope declaration of %qE specifies %<auto%>",
	    	  name);
      ਜੇ (pedantic && storage_class == csc_ਰਜਿਸਟਰ)
	pedwarn (ਨਿਵੇਸ਼_location, OPT_Wpedantic,
		 "file-scope declaration of %qE specifies %<register%>", name);
    }
  ਨਹੀਂਤਾਂ
    {
      ਜੇ (storage_class == csc_extern && funcdef_flag)
	error_at (loc, "nested function %qE declared %<extern%>", name);
      ਨਹੀਂਤਾਂ ਜੇ (threadp && storage_class == csc_none)
	{
	  error_at (loc, "function-scope %qE implicitly auto and declared "
		    "%qs", name,
		    declspecs->thread_gnu_p ? "__thread" : "_Thread_local");
	  threadp = ਝੂਠ;
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

  ਜਦੋਂ (declarator && declarator->ਕਿਸਮ != cdk_id)
    {
      ਜੇ (type == error_mark_ਗੰਢ)
	{
	  declarator = declarator->declarator;
	  ਜਾਰੀ;
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

      ਜੇ (array_ptr_quals != TYPE_UNQUALIFIED
	  || array_ptr_attrs != NULL_ਰੁੱਖ
	  || array_parm_static)
	{
	  /* Only the innermost declarator (making a parameter be of
	     array type which is converted to pointer type)
	     may have static or type qualifiers.  */
	  error_at (loc, "static or type qualifiers in non-parameter array declarator");
	  array_ptr_quals = TYPE_UNQUALIFIED;
	  array_ptr_attrs = NULL_ਰੁੱਖ;
	  array_parm_static = ਝੂਠ;
	}

      ਚੋਣ (declarator->ਕਿਸਮ)
	{
	ਹਾਲਤ cdk_attrs:
	  {
	    /* A declarator with embedded attributes.  */
	    ਰੁੱਖ attrs = declarator->u.attrs;
	    ਅਚਲ ਬਣਤਰ c_declarator *inner_decl;
	    ਪੂਰਨ attr_flags = 0;
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
	    ਜਦੋਂ (inner_decl->ਕਿਸਮ == cdk_attrs)
	      inner_decl = inner_decl->declarator;
	    ਜੇ (!cxx11_attribute_p (attrs))
	      {
		ਜੇ (inner_decl->ਕਿਸਮ == cdk_id)
		  attr_flags |= (ਪੂਰਨ) ATTR_FLAG_DECL_ਅਗਲਾ;
		ਨਹੀਂਤਾਂ ਜੇ (inner_decl->ਕਿਸਮ == cdk_function)
		  attr_flags |= (ਪੂਰਨ) ATTR_FLAG_FUNCTION_ਅਗਲਾ;
		ਨਹੀਂਤਾਂ ਜੇ (inner_decl->ਕਿਸਮ == cdk_array)
		  attr_flags |= (ਪੂਰਨ) ATTR_FLAG_ARRAY_ਅਗਲਾ;
	      }
	    attrs = c_warn_type_ਗੁਣ (type, attrs);
	    returned_attrs = decl_ਗੁਣ (&type,
					      chainon (returned_attrs, attrs),
					      attr_flags);
	    ਰੋਕੋ;
	  }
	ਹਾਲਤ cdk_array:
	  {
	    ਰੁੱਖ itype = NULL_ਰੁੱਖ;
	    ਰੁੱਖ ਮਾਪ = declarator->u.array.dimen;
	    /* The index is a signed object `sizetype' bits wide.  */
	    ਰੁੱਖ ਸੂਚਕਾਂਕ_type = c_common_signed_type (sizetype);

	    array_ptr_quals = declarator->u.array.quals;
	    array_ptr_attrs = declarator->u.array.attrs;
	    array_parm_static = declarator->u.array.static_p;
	    array_parm_vla_unspec_p = declarator->u.array.vla_unspec_p;

	    declarator = declarator->declarator;

	    ਤਾਰਕਿਕ flexible_array_member = ਝੂਠ;

	    /* Check for some types that there cannot be arrays of.  */

	    ਜੇ (VOID_TYPE_P (type))
	      {
		ਜੇ (name)
		  error_at (loc, "declaration of %qE as array of voids", name);
		ਨਹੀਂਤਾਂ
		  error_at (loc, "declaration of type name as array of voids");
		type = error_mark_ਗੰਢ;
	      }

	    ਜੇ (ਰੁੱਖ_ਕੋਡ (type) == FUNCTION_TYPE)
	      {
		ਜੇ (name)
		  error_at (loc, "declaration of %qE as array of functions",
		      	    name);
		ਨਹੀਂਤਾਂ
		  error_at (loc, "declaration of type name as array of "
		            "functions");
		type = error_mark_ਗੰਢ;
	      }

	    ਜੇ (pedantic && !ਵਿੱਚ_system_ਸਿਰਲੇਖ_at (ਨਿਵੇਸ਼_location)
		&& flexible_array_type_p (type))
	      pedwarn (loc, OPT_Wpedantic,
		       "invalid use of structure with flexible array member");

	    ਜੇ (ਮਾਪ == error_mark_ਗੰਢ)
	      type = error_mark_ਗੰਢ;

	    ਜੇ (type == error_mark_ਗੰਢ)
	      ਜਾਰੀ;

	    ਜੇ (!verify_type_context (loc, TCTX_ARRAY_ELEMENT, type))
	      {
		type = error_mark_ਗੰਢ;
		ਜਾਰੀ;
	      }

	    /* If size was specified, set ITYPE to a range-type for
	       that size.  Otherwise, ITYPE remains null.  finish_decl
	       may figure it out from an initial value.  */

	    ਜੇ (ਮਾਪ)
	      {
		ਤਾਰਕਿਕ ਮਾਪ_maybe_const = ਸੱਚ;
		ਤਾਰਕਿਕ ਮਾਪ_int_const = (ਰੁੱਖ_ਕੋਡ (ਮਾਪ) == INTEGER_CST
				       && !ਰੁੱਖ_ਉਛਾਲ (ਮਾਪ));
		ਤਾਰਕਿਕ this_ਮਾਪ_varies = ਝੂਠ;

		/* Strip NON_LVALUE_EXPRs since we aren't using as an
		   lvalue.  */
		STRIP_TYPE_NOPS (ਮਾਪ);

		ਜੇ (!INTEGRAL_TYPE_P (ਰੁੱਖ_TYPE (ਮਾਪ)))
		  {
		    ਜੇ (name)
		      error_at (loc, "size of array %qE has non-integer type",
				name);
		    ਨਹੀਂਤਾਂ
		      error_at (loc,
				"size of unnamed array has non-integer type");
		    ਮਾਪ = integer_one_ਗੰਢ;
		    ਮਾਪ_int_const = ਸੱਚ;
		    ਮਾਪ_error = ਸੱਚ;
		  }
		/* This can happen with enum forward declaration.  */
		ਨਹੀਂਤਾਂ ਜੇ (!COMPLETE_TYPE_P (ਰੁੱਖ_TYPE (ਮਾਪ)))
		  {
		    ਜੇ (name)
		      error_at (loc, "size of array %qE has incomplete type",
				name);
		    ਨਹੀਂਤਾਂ
		      error_at (loc, "size of unnamed array has incomplete "
				"type");
		    ਮਾਪ = integer_one_ਗੰਢ;
		    ਮਾਪ_int_const = ਸੱਚ;
		    ਮਾਪ_error = ਸੱਚ;
		  }

		ਮਾਪ = c_fully_fold (ਮਾਪ, ਝੂਠ, &ਮਾਪ_maybe_const);

		ਜੇ (pedantic && ਮਾਪ_maybe_const && integer_zerop (ਮਾਪ))
		  {
		    ਜੇ (name)
		      pedwarn (loc, OPT_Wpedantic,
			       "ISO C forbids zero-size array %qE", name);
		    ਨਹੀਂਤਾਂ
		      pedwarn (loc, OPT_Wpedantic,
			       "ISO C forbids zero-size array");
		  }

		ਜੇ (ਰੁੱਖ_ਕੋਡ (ਮਾਪ) == INTEGER_CST && ਮਾਪ_maybe_const)
		  {
		    constant_ਵਿਅੰਜਕ_warning (ਮਾਪ);
		    ਜੇ (ਰੁੱਖ_int_cst_sgn (ਮਾਪ) < 0)
		      {
			ਜੇ (name)
			  error_at (loc, "size of array %qE is negative", name);
			ਨਹੀਂਤਾਂ
			  error_at (loc, "size of unnamed array is negative");
			ਮਾਪ = integer_one_ਗੰਢ;
			ਮਾਪ_int_const = ਸੱਚ;
			ਮਾਪ_error = ਸੱਚ;
		      }
		    /* Handle a size folded to an integer constant but
		       not an integer constant expression.  */
		    ਜੇ (!ਮਾਪ_int_const)
		      {
			/* If this is a file scope declaration of an
			   ordinary identifier, this is invalid code;
			   diagnosing it here and not subsequently
			   treating the type as variable-length avoids
			   more confusing diagnostics later.  */
			ਜੇ ((decl_context == ਸਾਧਾਰਨ || decl_context == ਖੇਤਰ)
			    && current_scope == file_scope)
			  pedwarn (ਨਿਵੇਸ਼_location, 0,
				   "variably modified %qE at file scope",
				   name);
			ਨਹੀਂਤਾਂ
			  this_ਮਾਪ_varies = ਮਾਪ_varies = ਸੱਚ;
			warn_variable_ਲੰਮਾਈ_array (name, ਮਾਪ);
		      }
		  }
		ਨਹੀਂਤਾਂ ਜੇ ((decl_context == ਸਾਧਾਰਨ || decl_context == ਖੇਤਰ)
			 && current_scope == file_scope)
		  {
		    error_at (loc, "variably modified %qE at file scope", name);
		    ਮਾਪ = integer_one_ਗੰਢ;
		  }
		ਨਹੀਂਤਾਂ
		  {
		    /* Make sure the array size remains visibly
		       nonconstant even if it is (eg) a const variable
		       with known value.  */
		    this_ਮਾਪ_varies = ਮਾਪ_varies = ਸੱਚ;
		    warn_variable_ਲੰਮਾਈ_array (name, ਮਾਪ);
		    ਜੇ (sanitize_flags_p (SANITIZE_VLA)
			&& current_function_decl != NULL_ਰੁੱਖ
			&& decl_context == ਸਾਧਾਰਨ)
		      {
			/* Evaluate the array size only once.  */
			ਮਾਪ = save_ਵਿਅੰਜਕ (ਮਾਪ);
			ਮਾਪ = c_fully_fold (ਮਾਪ, ਝੂਠ, ਨਿਰਾ);
		        ਮਾਪ = fold_build2 (COMPOUND_ਵਿਅੰਜਕ, ਰੁੱਖ_TYPE (ਮਾਪ),
					    ubsan_instrument_vla (loc, ਮਾਪ),
					    ਮਾਪ);
		      }
		  }

		ਜੇ (integer_zerop (ਮਾਪ) && !this_ਮਾਪ_varies)
		  {
		    /* A zero-length array cannot be represented with
		       an unsigned index type, which is what we'll
		       get with build_index_type.  Create an
		       open-ended range instead.  */
		    itype = build_ਸੂਚਕਾਂਕ_type (NULL_ਰੁੱਖ);
		  }
		ਨਹੀਂਤਾਂ
		  {
		    /* Arrange for the SAVE_EXPR on the inside of the
		       MINUS_EXPR, which allows the -1 to get folded
		       with the +1 that happens when building TYPE_SIZE.  */
		    ਜੇ (ਮਾਪ_varies)
		      ਮਾਪ = save_ਵਿਅੰਜਕ (ਮਾਪ);
		    ਜੇ (this_ਮਾਪ_varies && ਰੁੱਖ_ਕੋਡ (ਮਾਪ) == INTEGER_CST)
		      ਮਾਪ = build2 (COMPOUND_ਵਿਅੰਜਕ, ਰੁੱਖ_TYPE (ਮਾਪ),
				     integer_zero_ਗੰਢ, ਮਾਪ);

		    /* Compute the maximum valid index, that is, size
		       - 1.  Do the calculation in index_type, so that
		       if it is a variable the computations will be
		       done in the proper mode.  */
		    itype = fold_build2_loc (loc, MINUS_ਵਿਅੰਜਕ, ਸੂਚਕਾਂਕ_type,
					     convert (ਸੂਚਕਾਂਕ_type, ਮਾਪ),
					     convert (ਸੂਚਕਾਂਕ_type,
						      ਮਾਪ_one_ਗੰਢ));

		    /* The above overflows when size does not fit
		       in index_type.
		       ???  While a size of INT_MAX+1 technically shouldn't
		       cause an overflow (because we subtract 1), handling
		       this case seems like an unnecessary complication.  */
		    ਜੇ (ਰੁੱਖ_ਕੋਡ (ਮਾਪ) == INTEGER_CST
			&& !int_ਸਮਾਉਂਦਾ_type_p (ਮਾਪ, ਸੂਚਕਾਂਕ_type))
		      {
			ਜੇ (name)
			  error_at (loc, "size of array %qE is too large",
			            name);
			ਨਹੀਂਤਾਂ
			  error_at (loc, "size of unnamed array is too large");
			type = error_mark_ਗੰਢ;
			ਜਾਰੀ;
		      }

		    itype = build_ਸੂਚਕਾਂਕ_type (itype);
		  }
		ਜੇ (this_ਮਾਪ_varies)
		  {
		    ਜੇ (ਰੁੱਖ_SIDE_EFFECTS (ਮਾਪ))
		      {
			ਜੇ (*ਵਿਅੰਜਕ)
			  *ਵਿਅੰਜਕ = build2 (COMPOUND_ਵਿਅੰਜਕ, ਰੁੱਖ_TYPE (ਮਾਪ),
					  *ਵਿਅੰਜਕ, ਮਾਪ);
			ਨਹੀਂਤਾਂ
			  *ਵਿਅੰਜਕ = ਮਾਪ;
		      }
		    *ਵਿਅੰਜਕ_const_operands &= ਮਾਪ_maybe_const;
		  }
	      }
	    ਨਹੀਂਤਾਂ ਜੇ (decl_context == ਖੇਤਰ)
	      {
		ਜੇ (array_parm_vla_unspec_p)
		  /* Field names can in fact have function prototype
		     scope so [*] is disallowed here through making
		     the field variably modified, not through being
		     something other than a declaration with function
		     prototype scope.  */
		  ਮਾਪ_varies = ਸੱਚ;
		ਨਹੀਂਤਾਂ
		  {
		    ਅਚਲ ਬਣਤਰ c_declarator *t = declarator;
		    ਜਦੋਂ (t->ਕਿਸਮ == cdk_attrs)
		      t = t->declarator;
		    flexible_array_member = (t->ਕਿਸਮ == cdk_id);
		  }
		ਜੇ (flexible_array_member
		    && !ਵਿੱਚ_system_ਸਿਰਲੇਖ_at (ਨਿਵੇਸ਼_location))
		  pedwarn_c90 (loc, OPT_Wpedantic, "ISO C90 does not "
			       "support flexible array members");

		/* ISO C99 Flexible array members are effectively
		   identical to GCC's zero-length array extension.  */
		ਜੇ (flexible_array_member)
		  itype = build_ਸੂਚਕਾਂਕ_type (NULL_ਰੁੱਖ);
	      }

	    /* Complain about arrays of incomplete types.  */
	    ਜੇ (!COMPLETE_TYPE_P (type))
	      {
		auto_diagnostic_ਸਮੂਹ d;
		error_at (loc, "array type has incomplete element type %qT",
			  type);
		/* See if we can be more helpful.  */
		ਜੇ (ਰੁੱਖ_ਕੋਡ (type) == ARRAY_TYPE)
		  {
		    ਜੇ (name)
		      inform (loc, "declaration of %qE as multidimensional "
			      "array must have bounds for all dimensions "
			      "except the first", name);
		    ਨਹੀਂਤਾਂ
		      inform (loc, "declaration of multidimensional array "
			      "must have bounds for all dimensions except "
			      "the first");
		  }
		type = error_mark_ਗੰਢ;
	      }
	    ਨਹੀਂਤਾਂ
	    /* When itype is NULL, a shared incomplete array type is
	       returned for all array of a given type.  Elsewhere we
	       make sure we don't complete that type before copying
	       it, but here we want to make sure we don't ever
	       modify the shared type, so we gcc_assert (itype)
	       below.  */
	      {
		addr_space_t as = DECODE_QUAL_ADDR_SPACE (type_quals);
		ਜੇ (!ADDR_SPACE_GENERIC_P (as) && as != TYPE_ADDR_SPACE (type))
		  type = c_build_qualified_type (type,
						 ENCODE_QUAL_ADDR_SPACE (as));
		ਜੇ (array_parm_vla_unspec_p)
		  type = c_build_array_type_unspecified (type);
		/* The GCC extension for zero-length arrays differs from
		   ISO flexible array members in that sizeof yields
		   zero.  */
		ਨਹੀਂਤਾਂ ਜੇ (ਮਾਪ && integer_zerop (ਮਾਪ))
		  type = c_build_array_type_zero_ਮਾਪ (type);
		ਨਹੀਂਤਾਂ
		  type = c_build_array_type (type, itype);

		ਜੇ (!valid_array_ਮਾਪ_p (loc, type, name))
		  type = error_mark_ਗੰਢ;
	      }

	    ਜੇ (array_parm_vla_unspec_p)
	      {
		/* C99 6.7.5.2p4 */
		ਜੇ (decl_context == TYPENAME)
		  warning (0, "%<[*]%> not in a declaration");
		ਨਹੀਂਤਾਂ ਜੇ (decl_context != GENERIC_ASSOC
			 && decl_context != PARM
			 && decl_context != ਖੇਤਰ)
		  {
		    error ("%<[*]%> not allowed in other than function prototype scope "
			   "or generic association");
		    type = error_mark_ਗੰਢ;
		  }
		ਮਾਪ_varies = ਸੱਚ;
	      }


	    gcc_assert (type == error_mark_ਗੰਢ
			|| flexible_array_member
			   == flexible_array_member_type_p (type));

	    ਜੇ (decl_context != PARM
		&& (array_ptr_quals != TYPE_UNQUALIFIED
		    || array_ptr_attrs != NULL_ਰੁੱਖ
		    || array_parm_static))
	      {
		error_at (loc, "static or type qualifiers in non-parameter "
			  "array declarator");
		array_ptr_quals = TYPE_UNQUALIFIED;
		array_ptr_attrs = NULL_ਰੁੱਖ;
		array_parm_static = ਝੂਠ;
	      }
	    orig_qual_ਅਸਿੱਧਾ++;
	    ਰੋਕੋ;
	  }
	ਹਾਲਤ cdk_function:
	  {
	    /* Say it's a definition only for the declarator closest
	       to the identifier, apart possibly from some
	       attributes.  */
	    ਤਾਰਕਿਕ really_funcdef = ਝੂਠ;
	    ਰੁੱਖ arg_types;
	    orig_qual_type = NULL_ਰੁੱਖ;
	    ਜੇ (funcdef_flag)
	      {
		ਅਚਲ ਬਣਤਰ c_declarator *t = declarator->declarator;
		ਜਦੋਂ (t->ਕਿਸਮ == cdk_attrs)
		  t = t->declarator;
		really_funcdef = (t->ਕਿਸਮ == cdk_id);
	      }

	    /* Declaring a function type.  Make sure we have a valid
	       type for the function to return.  */
	    ਜੇ (type == error_mark_ਗੰਢ)
	      ਜਾਰੀ;

	    ਮਾਪ_varies = ਝੂਠ;

	    /* Warn about some types functions can't return.  */
	    ਜੇ (ਰੁੱਖ_ਕੋਡ (type) == FUNCTION_TYPE)
	      {
		ਜੇ (name)
		  error_at (loc, "%qE declared as function returning a "
		      		 "function", name);
		ਨਹੀਂਤਾਂ
		  error_at (loc, "type name declared as function "
			    "returning a function");
		type = integer_type_ਗੰਢ;
	      }
	    ਜੇ (ਰੁੱਖ_ਕੋਡ (type) == ARRAY_TYPE)
	      {
		ਜੇ (name)
		  error_at (loc, "%qE declared as function returning an array",
		      	    name);
		ਨਹੀਂਤਾਂ
		  error_at (loc, "type name declared as function returning "
		      	    "an array");
		type = integer_type_ਗੰਢ;
	      }

	    /* Construct the function type and go to the next
	       inner layer of declarator.  */
	    arg_info = declarator->u.arg_info;
	    arg_types = grokparms (arg_info, really_funcdef);

	    /* Type qualifiers before the return type of the function
	       qualify the return type, not the function type.  */
	    ਜੇ (type_quals)
	      {
		ਅਚਲ ਗਿਣਤੀ c_declspec_ਸ਼ਬਦ ignored_quals_list[] =
		  {
		    cdw_const, cdw_volatile, cdw_restrict, cdw_ਪਤਾ_space,
		    cdw_atomic, cdw_ਸੰਖਿਆ_ਦਾ_elements
		  };
		location_t specs_loc
		  = ਸਭ_ਤੋਂ_ਛੋਟਾ_type_quals_location (declspecs->locations,
						  ignored_quals_list);
		ਜੇ (specs_loc == UNKNOWN_LOCATION)
		  specs_loc = declspecs->locations[cdw_typedef];
		ਜੇ (specs_loc == UNKNOWN_LOCATION)
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
		ਪੂਰਨ quals_ਵਰਤਿਆ = type_quals;
		ਜੇ (flag_isoc23)
		  quals_ਵਰਤਿਆ = 0;
		ਨਹੀਂਤਾਂ ਜੇ (flag_isoc11)
		  quals_ਵਰਤਿਆ &= TYPE_QUAL_ATOMIC;
		ਜੇ (quals_ਵਰਤਿਆ && VOID_TYPE_P (type) && really_funcdef)
		  pedwarn (specs_loc, 0,
			   "function definition has qualified void "
			   "return type");
		ਨਹੀਂਤਾਂ
		  warning_at (specs_loc, OPT_Wignored_qualifiers,
			      "type qualifiers ignored on function "
			      "return type");

		/* Ensure an error for restrict on invalid types; the
		   DR#423 resolution is not entirely clear about
		   this.  */
		ਜੇ (flag_isoc11
		    && (type_quals & TYPE_QUAL_RESTRICT)
		    && (!ਸੂਚਕ_TYPE_P (type)
			|| !C_TYPE_OBJECT_OR_INCOMPLETE_P (ਰੁੱਖ_TYPE (type))))
		  error_at (loc, "invalid use of %<restrict%>");
		type = c_build_qualified_type (type, quals_ਵਰਤਿਆ);
	      }
	    type_quals = TYPE_UNQUALIFIED;

	    type = c_build_function_type (type, arg_types,
					  arg_info->no_named_ਦਲੀਲਾਂ_stdarg_p);
	    declarator = declarator->declarator;

	    /* Set the TYPE_CONTEXTs for each tagged type which is local to
	       the formal parameter list of this FUNCTION_TYPE to point to
	       the FUNCTION_TYPE node itself.  */
	    {
	      c_arg_ਟੈਗ *ਟੈਗ;
	      ਬਿਨਾਨਿਸ਼ਾਨੀ ix;

	      FOR_EACH_VEC_ਸੁਰੱਖਿਅਤ_ELT_ਉਲਟ (arg_info->ਟੈਗ_ਸੂਚੀ, ix, ਟੈਗ)
		TYPE_CONTEXT (ਟੈਗ->type) = type;
	    }
	    ਰੋਕੋ;
	  }
	ਹਾਲਤ cdk_ਸੂਚਕ:
	  {
	    /* Merge any constancy or volatility into the target type
	       for the pointer.  */
	    ਜੇ ((type_quals & TYPE_QUAL_ATOMIC)
		&& ਰੁੱਖ_ਕੋਡ (type) == FUNCTION_TYPE)
	      {
		error_at (loc,
			  "%<_Atomic%>-qualified function type");
		type_quals &= ~TYPE_QUAL_ATOMIC;
	      }
	    ਨਹੀਂਤਾਂ ਜੇ (pedantic && ਰੁੱਖ_ਕੋਡ (type) == FUNCTION_TYPE
		     && type_quals)
	      pedwarn (loc, OPT_Wpedantic,
		       "ISO C forbids qualified function types");
	    ਜੇ (type_quals)
	      type = c_build_qualified_type (type, type_quals, orig_qual_type,
					     orig_qual_ਅਸਿੱਧਾ);
	    orig_qual_type = NULL_ਰੁੱਖ;
	    ਮਾਪ_varies = ਝੂਠ;

	    /* When the pointed-to type involves components of variable size,
	       care must be taken to ensure that the size evaluation code is
	       emitted early enough to dominate all the possible later uses
	       and late enough for the variables on which it depends to have
	       been assigned.

	       This is expected to happen automatically when the pointed-to
	       type has a name/declaration of it's own, but special attention
	       is required if the type is anonymous. */
	    ਜੇ (!TYPE_NAME (type) && c_type_variably_modified_p (type))
	      {
		ਤਾਰਕਿਕ bind_p = decl_context == TYPENAME
			      || decl_context == ਖੇਤਰ
			      || decl_context == PARM;
		ਜੋੜੋ_decl_ਵਿਅੰਜਕ (loc, type, bind_p ? ਵਿਅੰਜਕ : ਨਿਰਾ, ਸੱਚ);
	      }

	    type = c_build_ਸੂਚਕ_type (type);

	    /* Process type qualifiers (such as const or volatile)
	       that were given inside the `*'.  */
	    type_quals = declarator->u.ਸੂਚਕ_quals;

	    declarator = declarator->declarator;
	    ਰੋਕੋ;
	  }
	ਮੂਲ:
	  gcc_unreachable ();
	}
    }
  *decl_attrs = chainon (returned_attrs, *decl_attrs);
  *decl_attrs = chainon (decl_id_attrs, *decl_attrs);

  /* Now TYPE has the actual type, apart from any qualifiers in
     TYPE_QUALS.  */

  /* Warn about address space used for things other than static memory or
     pointers.  */
  ਪਤਾ_space = DECODE_QUAL_ADDR_SPACE (type_quals);
  ਜੇ (!ADDR_SPACE_GENERIC_P (ਪਤਾ_space))
    {
      ਜੇ (decl_context == ਸਾਧਾਰਨ)
	{
	  ਚੋਣ (storage_class)
	    {
	    ਹਾਲਤ csc_auto:
	      error ("%qs combined with %<auto%> qualifier for %qE",
		     c_addr_space_name (ਪਤਾ_space), name);
	      ਰੋਕੋ;
	    ਹਾਲਤ csc_ਰਜਿਸਟਰ:
	      error ("%qs combined with %<register%> qualifier for %qE",
		     c_addr_space_name (ਪਤਾ_space), name);
	      ਰੋਕੋ;
	    ਹਾਲਤ csc_none:
	      ਜੇ (current_function_scope)
		{
		  error ("%qs specified for auto variable %qE",
			 c_addr_space_name (ਪਤਾ_space), name);
		  ਰੋਕੋ;
		}
	      ਰੋਕੋ;
	    ਹਾਲਤ csc_static:
	    ਹਾਲਤ csc_extern:
	    ਹਾਲਤ csc_typedef:
	      ਰੋਕੋ;
	    ਮੂਲ:
	      gcc_unreachable ();
	    }
	}
      ਨਹੀਂਤਾਂ ਜੇ (decl_context == PARM && ਰੁੱਖ_ਕੋਡ (type) != ARRAY_TYPE)
	{
	  ਜੇ (name)
	    error ("%qs specified for parameter %qE",
		   c_addr_space_name (ਪਤਾ_space), name);
	  ਨਹੀਂਤਾਂ
	    error ("%qs specified for unnamed parameter",
		   c_addr_space_name (ਪਤਾ_space));
	}
      ਨਹੀਂਤਾਂ ਜੇ (decl_context == ਖੇਤਰ)
	{
	  ਜੇ (name)
	    error ("%qs specified for structure field %qE",
		   c_addr_space_name (ਪਤਾ_space), name);
	  ਨਹੀਂਤਾਂ
	    error ("%qs specified for structure field",
		   c_addr_space_name (ਪਤਾ_space));
	}
    }

  /* Check the type and width of a bit-field.  */
  ਜੇ (bitfield)
    {
      check_bitfield_type_and_ਚੌੜਾਈ (loc, &type, ਚੌੜਾਈ, name);
      /* C11 makes it implementation-defined (6.7.2.1#5) whether
	 atomic types are permitted for bit-fields; we have no code to
	 make bit-field accesses atomic, so disallow them.  */
      ਜੇ (type_quals & TYPE_QUAL_ATOMIC)
	{
	  ਜੇ (name)
	    error_at (loc, "bit-field %qE has atomic type", name);
	  ਨਹੀਂਤਾਂ
	    error_at (loc, "bit-field has atomic type");
	  type_quals &= ~TYPE_QUAL_ATOMIC;
	}
    }

  /* Reject invalid uses of _Alignas.  */
  ਜੇ (declspecs->alignas_p)
    {
      ਜੇ (storage_class == csc_typedef)
	error_at (loc, "alignment specified for typedef %qE", name);
      ਨਹੀਂਤਾਂ ਜੇ (storage_class == csc_ਰਜਿਸਟਰ)
	error_at (loc, "alignment specified for %<register%> object %qE",
		  name);
      ਨਹੀਂਤਾਂ ਜੇ (decl_context == PARM)
	{
	  ਜੇ (name)
	    error_at (loc, "alignment specified for parameter %qE", name);
	  ਨਹੀਂਤਾਂ
	    error_at (loc, "alignment specified for unnamed parameter");
	}
      ਨਹੀਂਤਾਂ ਜੇ (bitfield)
	{
	  ਜੇ (name)
	    error_at (loc, "alignment specified for bit-field %qE", name);
	  ਨਹੀਂਤਾਂ
	    error_at (loc, "alignment specified for unnamed bit-field");
	}
      ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਕੋਡ (type) == FUNCTION_TYPE)
	error_at (loc, "alignment specified for function %qE", name);
      ਨਹੀਂਤਾਂ ਜੇ (declspecs->align_log != -1 && TYPE_P (type))
	{
	  alignas_align = 1U << declspecs->align_log;
	  ਜੇ (alignas_align < min_align_ਦਾ_type (type))
	    {
	      ਜੇ (name)
		error_at (loc, "%<_Alignas%> specifiers cannot reduce "
			  "alignment of %qE", name);
	      ਨਹੀਂਤਾਂ
		error_at (loc, "%<_Alignas%> specifiers cannot reduce "
			  "alignment of unnamed field");
	      alignas_align = 0;
	    }
	}
    }

  /* If this is declaring a typedef name, return a TYPE_DECL.  */

  ਜੇ (storage_class == csc_typedef)
    {
      ਰੁੱਖ decl;
      ਜੇ ((type_quals & TYPE_QUAL_ATOMIC)
	  && ਰੁੱਖ_ਕੋਡ (type) == FUNCTION_TYPE)
	{
	  error_at (loc,
		    "%<_Atomic%>-qualified function type");
	  type_quals &= ~TYPE_QUAL_ATOMIC;
	}
      ਨਹੀਂਤਾਂ ਜੇ (pedantic && ਰੁੱਖ_ਕੋਡ (type) == FUNCTION_TYPE
	       && type_quals)
	pedwarn (loc, OPT_Wpedantic,
		 "ISO C forbids qualified function types");
      ਜੇ (type_quals)
	type = c_build_qualified_type (type, type_quals, orig_qual_type,
				       orig_qual_ਅਸਿੱਧਾ);
      decl = build_decl (declarator->id_loc,
			 TYPE_DECL, declarator->u.id.id, type);
      ਜੇ (declspecs->explicit_signed_p)
	C_TYPEDEF_EXPLICITLY_SIGNED (decl) = 1;
      ਜੇ (declspecs->inline_p)
	pedwarn (loc, 0,"typedef %q+D declared %<inline%>", decl);
      ਜੇ (declspecs->noreturn_p)
	pedwarn (loc, 0,"typedef %q+D declared %<_Noreturn%>", decl);

      ਜੇ (warn_cxx_compat && declarator->u.id.id != NULL_ਰੁੱਖ)
	{
	  ਬਣਤਰ c_binding *b = I_ਟੈਗ_BINDING (declarator->u.id.id);

	  ਜੇ (b != ਨਿਰਾ
	      && b->decl != NULL_ਰੁੱਖ
	      && (B_ਵਿੱਚ_CURRENT_SCOPE (b)
		  || (current_scope == file_scope && B_ਵਿੱਚ_EXTERNAL_SCOPE (b)))
	      && TYPE_MAIN_VARIANT (b->decl) != TYPE_MAIN_VARIANT (type))
	    {
	      auto_diagnostic_ਸਮੂਹ d;
	      ਜੇ (warning_at (declarator->id_loc, OPT_Wc___compat,
			      "using %qD as both a typedef and a tag is "
			      "invalid in C++", decl)
		  && b->locus != UNKNOWN_LOCATION)
		inform (b->locus, "originally defined here");
	    }
	}

      ਵਾਪਸ decl;
    }

  /* If this is a type name (such as, in a cast or sizeof),
     compute the type and return it now.  */

  ਜੇ (decl_context == TYPENAME || decl_context == GENERIC_ASSOC)
    {
      /* Note that the grammar rejects storage classes in typenames
	 and fields.  */
      gcc_assert (storage_class == csc_none && !threadp
		  && !declspecs->inline_p && !declspecs->noreturn_p);
      ਜੇ ((type_quals & TYPE_QUAL_ATOMIC)
	  && ਰੁੱਖ_ਕੋਡ (type) == FUNCTION_TYPE)
	{
	  error_at (loc,
		    "%<_Atomic%>-qualified function type");
	  type_quals &= ~TYPE_QUAL_ATOMIC;
	}
      ਨਹੀਂਤਾਂ ਜੇ (pedantic && ਰੁੱਖ_ਕੋਡ (type) == FUNCTION_TYPE
	       && type_quals)
	pedwarn (loc, OPT_Wpedantic,
		 "ISO C forbids const or volatile function types");
      ਜੇ (type_quals)
	type = c_build_qualified_type (type, type_quals, orig_qual_type,
				       orig_qual_ਅਸਿੱਧਾ);
      ਵਾਪਸ type;
    }

  ਜੇ (pedantic && decl_context == ਖੇਤਰ
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

  ਜੇ (VOID_TYPE_P (type) && decl_context != PARM
      && !((decl_context != ਖੇਤਰ && ਰੁੱਖ_ਕੋਡ (type) != FUNCTION_TYPE)
	    && (storage_class == csc_extern
		|| (current_scope == file_scope
		    && !(storage_class == csc_static
			 || storage_class == csc_ਰਜਿਸਟਰ)))))
    {
      error_at (loc, "variable or field %qE declared void", name);
      type = integer_type_ਗੰਢ;
    }

  /* Now create the decl, which may be a VAR_DECL, a PARM_DECL
     or a FUNCTION_DECL, depending on DECL_CONTEXT and TYPE.  */

  {
    ਰੁੱਖ decl;

    ਜੇ (decl_context == PARM)
      {
	ਰੁੱਖ promoted_type;
	ਤਾਰਕਿਕ array_parameter_p = ਝੂਠ;

	/* A parameter declared as an array of T is really a pointer to T.
	   One declared as a function is really a pointer to a function.  */

	ਜੇ (ਰੁੱਖ_ਕੋਡ (type) == ARRAY_TYPE)
	  {
	    ਜੇ (!ਮਾਪ_error)
	      *decl_attrs = build_arg_spec_attribute (type, array_parm_static,
						      *decl_attrs);

	    /* Transfer const-ness of array into that of type pointed to.  */
	    type = ਰੁੱਖ_TYPE (type);
	    ਜੇ (orig_qual_type != NULL_ਰੁੱਖ)
	      {
		ਜੇ (orig_qual_ਅਸਿੱਧਾ == 0)
		  orig_qual_type = ਰੁੱਖ_TYPE (orig_qual_type);
		ਨਹੀਂਤਾਂ
		  orig_qual_ਅਸਿੱਧਾ--;
	      }
	    ਜੇ (type_quals)
	      type = c_build_qualified_type (type, type_quals, orig_qual_type,
					     orig_qual_ਅਸਿੱਧਾ);

	    /* The pointed-to type may need a decl expr (see above).  */
	    ਜੇ (!TYPE_NAME (type) && c_type_variably_modified_p (type))
	      {
		ਤਾਰਕਿਕ bind_p = decl_context == TYPENAME
			      || decl_context == ਖੇਤਰ
			      || decl_context == PARM;
		ਜੋੜੋ_decl_ਵਿਅੰਜਕ (loc, type, bind_p ? ਵਿਅੰਜਕ : ਨਿਰਾ, ਸੱਚ);
	      }

	    type = c_build_ਸੂਚਕ_type (type);
	    type_quals = array_ptr_quals;
	    ਜੇ (type_quals)
	      type = c_build_qualified_type (type, type_quals);

	    /* We don't yet implement attributes in this context.  */
	    ਜੇ (array_ptr_attrs != NULL_ਰੁੱਖ)
	      warning_at (loc, OPT_Wattributes,
			  "attributes in parameter array declarator ignored");

	    ਮਾਪ_varies = ਝੂਠ;
	    array_parameter_p = ਸੱਚ;
	  }
	ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਕੋਡ (type) == FUNCTION_TYPE)
	  {
	    ਜੇ (type_quals & TYPE_QUAL_ATOMIC)
	      {
		error_at (loc,
			  "%<_Atomic%>-qualified function type");
		type_quals &= ~TYPE_QUAL_ATOMIC;
	      }
	    ਨਹੀਂਤਾਂ ਜੇ (type_quals)
	      pedwarn (loc, OPT_Wpedantic,
		       "ISO C forbids qualified function types");
	    ਜੇ (type_quals)
	      type = c_build_qualified_type (type, type_quals);
	    type = c_build_ਸੂਚਕ_type (type);
	    type_quals = TYPE_UNQUALIFIED;
	  }
	ਨਹੀਂਤਾਂ ਜੇ (type_quals)
	  type = c_build_qualified_type (type, type_quals);

	decl = build_decl (declarator->id_loc,
			   PARM_DECL, declarator->u.id.id, type);
	ਜੇ (ਮਾਪ_varies)
	  C_DECL_VARIABLE_ਮਾਪ (decl) = 1;
	C_ARRAY_PARAMETER (decl) = array_parameter_p;

	/* Compute the type actually passed in the parmlist,
	   for the case where there is no prototype.
	   (For example, shorts and chars are passed as ints.)
	   When there is a prototype, this is overridden later.  */

	ਜੇ (type == error_mark_ਗੰਢ)
	  promoted_type = type;
	ਨਹੀਂਤਾਂ
	  promoted_type = c_type_promotes_ਮੰਜ਼ਿਲ (type);

	DECL_ARG_TYPE (decl) = promoted_type;
	ਜੇ (declspecs->inline_p)
	  pedwarn (loc, 0, "parameter %q+D declared %<inline%>", decl);
	ਜੇ (declspecs->noreturn_p)
	  pedwarn (loc, 0, "parameter %q+D declared %<_Noreturn%>", decl);
      }
    ਨਹੀਂਤਾਂ ਜੇ (decl_context == ਖੇਤਰ)
      {
	/* Note that the grammar rejects storage classes in typenames
	   and fields.  */
	gcc_assert (storage_class == csc_none && !threadp
		    && !declspecs->inline_p && !declspecs->noreturn_p);

	/* Structure field.  It may not be a function.  */

	ਜੇ (ਰੁੱਖ_ਕੋਡ (type) == FUNCTION_TYPE)
	  {
	    error_at (loc, "field %qE declared as a function", name);
	    type = c_build_ਸੂਚਕ_type (type);
	  }
	ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਕੋਡ (type) != ERROR_MARK
		 && !COMPLETE_OR_UNBOUND_ARRAY_TYPE_P (type))
	  {
	    ਜੇ (name)
	      error_at (loc, "field %qE has incomplete type", name);
	    ਨਹੀਂਤਾਂ
	      error_at (loc, "unnamed field has incomplete type");
	    type = error_mark_ਗੰਢ;
	  }
	ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਕੋਡ (type) == ARRAY_TYPE
		 && TYPE_DOMAIN (type) == NULL_ਰੁੱਖ)
	  {
	    /* We have a flexible array member through a typedef.
	       Set suitable range.  Whether this is a correct position
	       for a flexible array member will be determined elsewhere.  */
	    ਜੇ (!ਵਿੱਚ_system_ਸਿਰਲੇਖ_at (ਨਿਵੇਸ਼_location))
	      pedwarn_c90 (loc, OPT_Wpedantic, "ISO C90 does not "
			   "support flexible array members");
	    type = build_distinct_type_copy (TYPE_MAIN_VARIANT (type));
	    TYPE_DOMAIN (type) = build_ਸੂਚਕਾਂਕ_type (NULL_ਰੁੱਖ);
	    ਜੇ (orig_qual_ਅਸਿੱਧਾ == 0)
	      orig_qual_type = NULL_ਰੁੱਖ;
	  }
	ਜੇ (type != error_mark_ਗੰਢ
	    && !verify_type_context (loc, TCTX_ਖੇਤਰ, type))
	  type = error_mark_ਗੰਢ;

	type = c_build_qualified_type (type, type_quals, orig_qual_type,
				       orig_qual_ਅਸਿੱਧਾ);
	decl = build_decl (declarator->id_loc,
			   ਖੇਤਰ_DECL, declarator->u.id.id, type);
	DECL_NONADDRESSABLE_P (decl) = bitfield;
	ਜੇ (bitfield && !declarator->u.id.id)
	  DECL_PADDING_P (decl) = 1;

	ਜੇ (ਮਾਪ_varies)
	  C_DECL_VARIABLE_ਮਾਪ (decl) = 1;
      }
    ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਕੋਡ (type) == FUNCTION_TYPE)
      {
	ਜੇ (storage_class == csc_ਰਜਿਸਟਰ || threadp || constexprp)
	  {
	    error_at (loc, "invalid storage class for function %qE", name);
	  }
	ਨਹੀਂਤਾਂ ਜੇ (current_scope != file_scope)
	  {
	    /* Function declaration not at file scope.  Storage
	       classes other than `extern' are not allowed, C99
	       6.7.1p5, and `extern' makes no difference.  However,
	       GCC allows 'auto', perhaps with 'inline', to support
	       nested functions.  */
	    ਜੇ (storage_class == csc_auto)
		pedwarn (loc, OPT_Wpedantic,
			 "invalid storage class for function %qE", name);
	    ਨਹੀਂਤਾਂ ਜੇ (storage_class == csc_static)
	      {
		error_at (loc, "invalid storage class for function %qE", name);
		ਜੇ (funcdef_flag)
		  storage_class = declspecs->storage_class = csc_none;
		ਨਹੀਂਤਾਂ
		  ਵਾਪਸ NULL_ਰੁੱਖ;
	      }
	  }

	decl = build_decl (declarator->id_loc,
			   FUNCTION_DECL, declarator->u.id.id, type);
	decl = build_decl_attribute_variant (decl, decl_attr);

	ਜੇ (type_quals & TYPE_QUAL_ATOMIC)
	  {
	    error_at (loc,
		      "%<_Atomic%>-qualified function type");
	    type_quals &= ~TYPE_QUAL_ATOMIC;
	  }
	ਨਹੀਂਤਾਂ ਜੇ (pedantic && type_quals && !DECL_ਵਿੱਚ_SYSTEM_ਸਿਰਲੇਖ (decl))
	  pedwarn (loc, OPT_Wpedantic,
		   "ISO C forbids qualified function types");

	/* Every function declaration is an external reference
	   (DECL_EXTERNAL) except for those which are not at file
	   scope and are explicitly declared "auto".  This is
	   forbidden by standard C (C99 6.7.1p5) and is interpreted by
	   GCC to signify a forward declaration of a nested function.  */
	ਜੇ (storage_class == csc_auto && current_scope != file_scope)
	  DECL_EXTERNAL (decl) = 0;
	/* In C99, a function which is declared 'inline' with 'extern'
	   is not an external reference (which is confusing).  It
	   means that the later definition of the function must be output
	   in this file, C99 6.7.4p6.  In GNU C89, a function declared
	   'extern inline' is an external reference.  */
	ਨਹੀਂਤਾਂ ਜੇ (declspecs->inline_p && storage_class != csc_static)
	  DECL_EXTERNAL (decl) = ((storage_class == csc_extern)
				  == flag_gnu89_inline);
	ਨਹੀਂਤਾਂ
	  DECL_EXTERNAL (decl) = !initialized;

	/* Record absence of global scope for `static' or `auto'.  */
	ਰੁੱਖ_ਜਨਤਕ (decl)
	  = !(storage_class == csc_static || storage_class == csc_auto);

	/* For a function definition, record the argument information
	   block where store_parm_decls will look for it.  */
	ਜੇ (funcdef_flag)
	  current_function_arg_info = arg_info;

	ਜੇ (declspecs->default_int_p)
	  C_FUNCTION_IMPLICIT_INT (decl) = 1;

	/* Record presence of `inline' and `_Noreturn', if it is
	   reasonable.  */
	ਜੇ (flag_hosted && MAIN_NAME_P (declarator->u.id.id))
	  {
	    ਜੇ (declspecs->inline_p)
	      pedwarn (loc, 0, "cannot inline function %<main%>");
	    ਜੇ (declspecs->noreturn_p)
	      pedwarn (loc, 0, "%<main%> declared %<_Noreturn%>");
	  }
	ਨਹੀਂਤਾਂ
	  {
	    ਜੇ (declspecs->inline_p)
	      /* Record that the function is declared `inline'.  */
	      DECL_DECLARED_INLINE_P (decl) = 1;
	    ਜੇ (declspecs->noreturn_p)
	      {
		ਜੇ (flag_isoc99)
		  pedwarn_c99 (loc, OPT_Wpedantic,
			       "ISO C99 does not support %<_Noreturn%>");
		ਨਹੀਂਤਾਂ
		  pedwarn_c99 (loc, OPT_Wpedantic,
			       "ISO C90 does not support %<_Noreturn%>");
		ਰੁੱਖ_THIS_VOLATILE (decl) = 1;
	      }
	  }

	/* C99 6.2.2p7: It is invalid (compile-time undefined
	   behavior) to create an 'extern' declaration for a
	   function if there is a global declaration that is
	   'static' and the global declaration is not visible.
	   (If the static declaration _is_ currently visible,
	   the 'extern' declaration is taken to refer to that decl.) */
	ਜੇ (!initialized
	    && ਰੁੱਖ_ਜਨਤਕ (decl)
	    && current_scope != file_scope)
	  {
	    ਰੁੱਖ global_decl  = identifier_global_ਮੁੱਲ (declarator->u.id.id);
	    ਰੁੱਖ visible_decl = lookup_name (declarator->u.id.id);

	    ਜੇ (global_decl
		&& global_decl != visible_decl
		&& VAR_OR_FUNCTION_DECL_P (global_decl)
		&& !ਰੁੱਖ_ਜਨਤਕ (global_decl))
	      error_at (loc, "function previously declared %<static%> "
			"redeclared %<extern%>");
	  }
      }
    ਨਹੀਂਤਾਂ
      {
	/* It's a variable.  */
	/* An uninitialized decl with `extern' is a reference.  */
	ਪੂਰਨ extern_ref = !initialized && storage_class == csc_extern;

	ਜੇ (constexprp)
	  {
	    /* The type of a constexpr variable must not be variably
	       modified, volatile, atomic or restrict qualified or
	       have a member with such a qualifier.  const
	       qualification is implicitly added, and, at file scope,
	       has internal linkage.  */
	    ਜੇ (c_type_variably_modified_p (type))
	      error_at (loc, "%<constexpr%> object has variably modified "
			"type");
	    ਜੇ (type_quals
		& (TYPE_QUAL_VOLATILE | TYPE_QUAL_RESTRICT | TYPE_QUAL_ATOMIC))
	      error_at (loc, "invalid qualifiers for %<constexpr%> object");
	    ਨਹੀਂਤਾਂ
	      {
		ਰੁੱਖ type_no_array = strip_array_types (type);
		ਜੇ (ਰਿਕਾਰਡ_OR_UNION_TYPE_P (type_no_array)
		    && C_TYPE_FIELDS_NON_CONSTEXPR (type_no_array))
		  error_at (loc, "invalid qualifiers for field of "
			    "%<constexpr%> object");
	      }
	    type_quals |= TYPE_QUAL_CONST;
	    ਜੇ (current_scope == file_scope)
	      storage_class = csc_static;
	  }

	type = c_build_qualified_type (type, type_quals, orig_qual_type,
				       orig_qual_ਅਸਿੱਧਾ);

	/* C99 6.2.2p7: It is invalid (compile-time undefined
	   behavior) to create an 'extern' declaration for a
	   variable if there is a global declaration that is
	   'static' and the global declaration is not visible.
	   (If the static declaration _is_ currently visible,
	   the 'extern' declaration is taken to refer to that decl.) */
	ਜੇ (extern_ref && current_scope != file_scope)
	  {
	    ਰੁੱਖ global_decl  = identifier_global_ਮੁੱਲ (declarator->u.id.id);
	    ਰੁੱਖ visible_decl = lookup_name (declarator->u.id.id);

	    ਜੇ (global_decl
		&& global_decl != visible_decl
		&& VAR_P (global_decl)
		&& !ਰੁੱਖ_ਜਨਤਕ (global_decl))
	      error_at (loc, "variable previously declared %<static%> "
			"redeclared %<extern%>");
	  }

	decl = build_decl (declarator->id_loc,
			   VAR_DECL, declarator->u.id.id, type);
	ਜੇ (ਮਾਪ_varies)
	  C_DECL_VARIABLE_ਮਾਪ (decl) = 1;
	ਜੇ (constexprp)
	  C_DECL_DECLARED_CONSTEXPR (decl) = 1;

	ਜੇ (declspecs->inline_p)
	  pedwarn (loc, 0, "variable %q+D declared %<inline%>", decl);
	ਜੇ (declspecs->noreturn_p)
	  pedwarn (loc, 0, "variable %q+D declared %<_Noreturn%>", decl);

	/* At file scope, an initialized extern declaration may follow
	   a static declaration.  In that case, DECL_EXTERNAL will be
	   reset later in start_decl.  */
	DECL_EXTERNAL (decl) = (storage_class == csc_extern);

	/* At file scope, the presence of a `static' or `register' storage
	   class specifier, or the absence of all storage class specifiers
	   makes this declaration a definition (perhaps tentative).  Also,
	   the absence of `static' makes it public.  */
	ਜੇ (current_scope == file_scope)
	  {
	    ਰੁੱਖ_ਜਨਤਕ (decl) = storage_class != csc_static;
	    ਰੁੱਖ_STATIC (decl) = !extern_ref;
	  }
	/* Not at file scope, only `static' makes a static definition.  */
	ਨਹੀਂਤਾਂ
	  {
	    ਰੁੱਖ_STATIC (decl) = (storage_class == csc_static);
	    ਰੁੱਖ_ਜਨਤਕ (decl) = extern_ref;
	  }

	// NB: Set a tentative TLS model to avoid tls_model attribute
	// warnings due to lack of thread storage duration.  It will
	// be updated by c_decl_attributes later.
	ਜੇ (threadp)
	  ਸੈੱਟ_decl_tls_model (decl, TLS_MODEL_REAL);
      }

    ਜੇ ((storage_class == csc_extern
	 || (storage_class == csc_none
	     && ਰੁੱਖ_ਕੋਡ (type) == FUNCTION_TYPE
	     && !funcdef_flag))
	&& c_type_variably_modified_p (type))
      {
	/* C99 6.7.5.2p2 */
	ਜੇ (ਰੁੱਖ_ਕੋਡ (type) == FUNCTION_TYPE)
	  error_at (loc, "non-nested function with variably modified type");
	ਨਹੀਂਤਾਂ
	  error_at (loc, "object with variably modified type must have "
	      	    "no linkage");
      }

    /* For nested functions disqualify ones taking VLAs by value
       from inlining since the middle-end cannot deal with this.
       ???  We should arrange for those to be passed by reference
       with emitting the copy on the caller side in the frontend.  */
    ਜੇ (storage_class == csc_none
	&& ਰੁੱਖ_ਕੋਡ (type) == FUNCTION_TYPE)
      ਲਈ (ਰੁੱਖ al = TYPE_ARG_TYPES (type); al; al = ਰੁੱਖ_CHAIN (al))
	{
	  ਰੁੱਖ arg = ਰੁੱਖ_ਮੁੱਲ (al);
	  ਜੇ (arg != error_mark_ਗੰਢ
	      && C_TYPE_VARIABLE_ਮਾਪ (arg))
	    {
	      DECL_UNINLINABLE (decl) = 1;
	      ਰੋਕੋ;
	    }
	}

    /* Record `register' declaration for warnings on &
       and in case doing stupid register allocation.  */

    ਜੇ (storage_class == csc_ਰਜਿਸਟਰ
	&& ਰੁੱਖ_ਕੋਡ (type) != FUNCTION_TYPE)
      {
	C_DECL_ਰਜਿਸਟਰ (decl) = 1;
	DECL_ਰਜਿਸਟਰ (decl) = 1;
      }

    /* Record constancy and volatility.  */
    c_apply_type_quals_ਮੰਜ਼ਿਲ_decl (type_quals, decl);

    /* Apply _Alignas specifiers.  */
    ਜੇ (alignas_align)
      {
	ਸੈੱਟ_DECL_ALIGN (decl, alignas_align * ਬਿੱਟ_ਪ੍ਰਤੀ_UNIT);
	DECL_USER_ALIGN (decl) = 1;
      }

    /* If a type has volatile components, it should be stored in memory.
       Otherwise, the fact that those components are volatile
       will be ignored, and would even crash the compiler.
       Of course, this only makes sense on  VAR,PARM, and RESULT decl's.   */
    ਜੇ (C_TYPE_FIELDS_VOLATILE (ਰੁੱਖ_TYPE (decl))
	&& (VAR_P (decl) ||  ਰੁੱਖ_ਕੋਡ (decl) == PARM_DECL
	  || ਰੁੱਖ_ਕੋਡ (decl) == ਨਤੀਜਾ_DECL))
      {
	/* It is not an error for a structure with volatile fields to
	   be declared register, but reset DECL_REGISTER since it
	   cannot actually go in a register.  */
	ਪੂਰਨ was_reg = C_DECL_ਰਜਿਸਟਰ (decl);
	C_DECL_ਰਜਿਸਟਰ (decl) = 0;
	DECL_ਰਜਿਸਟਰ (decl) = 0;
	c_mark_addressable (decl);
	C_DECL_ਰਜਿਸਟਰ (decl) = was_reg;
      }

  /* This is the earliest point at which we might know the assembler
     name of a variable.  Thus, if it's known before this, die horribly.  */
    gcc_assert (!HAS_DECL_ASSEMBLER_NAME_P (decl)
		|| !DECL_ASSEMBLER_NAME_ਸੈੱਟ_P (decl));

    ਜੇ (warn_cxx_compat
	&& VAR_P (decl)
	&& ਰੁੱਖ_ਜਨਤਕ (decl)
	&& ਰੁੱਖ_STATIC (decl)
	&& (ਰਿਕਾਰਡ_OR_UNION_TYPE_P (ਰੁੱਖ_TYPE (decl))
	    || ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (decl)) == ENUMERAL_TYPE)
	&& TYPE_NAME (ਰੁੱਖ_TYPE (decl)) == NULL_ਰੁੱਖ)
      warning_at (DECL_ਸਰੋਤ_LOCATION (decl), OPT_Wc___compat,
		  "non-local variable %qD with anonymous type is "
		  "questionable in C++", decl);

    ਵਾਪਸ decl;
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

ਸਥਿਰ ਰੁੱਖ
grokparms (ਬਣਤਰ c_arg_info *arg_info, ਤਾਰਕਿਕ funcdef_flag)
{
  ਰੁੱਖ arg_types = arg_info->types;

  ਜੇ (funcdef_flag && arg_info->had_vla_unspec)
    {
      /* A function definition isn't function prototype scope C99 6.2.1p4.  */
      /* C99 6.7.5.2p4 */
      error ("%<[*]%> not allowed in other than function prototype scope");
    }

  ਜੇ (arg_types == NULL_ਰੁੱਖ && !funcdef_flag && !flag_isoc23
      && !ਵਿੱਚ_system_ਸਿਰਲੇਖ_at (ਨਿਵੇਸ਼_location))
    warning (OPT_Wstrict_prototypes,
	     "function declaration isn%'t a prototype");

  ਜੇ (arg_types == error_mark_ਗੰਢ)
    /* Don't set TYPE_ARG_TYPES in this case.  */
    ਵਾਪਸ NULL_ਰੁੱਖ;

  ਨਹੀਂਤਾਂ ਜੇ (arg_types && ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_ਮੁੱਲ (arg_types)) == IDENTIFIER_ਗੰਢ)
    {
      ਜੇ (!funcdef_flag)
	{
	  permerror_opt (ਨਿਵੇਸ਼_location,
			 OPT_Wdeclaration_missing_parameter_type,
			 "parameter names (without types) in "
			 "function declaration");
	  arg_info->parms = NULL_ਰੁੱਖ;
	}
      ਨਹੀਂਤਾਂ
	arg_info->parms = arg_info->types;

      arg_info->types = NULL_ਰੁੱਖ;
      ਵਾਪਸ NULL_ਰੁੱਖ;
    }
  ਨਹੀਂਤਾਂ
    {
      ਰੁੱਖ parm, type, typelt;
      ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ parmno;

      /* In C23, convert () to (void).  */
      ਜੇ (flag_isoc23
	  && !arg_types
	  && !arg_info->parms
	  && !arg_info->no_named_ਦਲੀਲਾਂ_stdarg_p)
	{
	  arg_types = arg_info->types = void_list_ਗੰਢ;
	  arg_info->c23_ਖਾਲੀ_ਥਾਵਾਂ_parens = 1;
	}

      /* If there is a parameter of incomplete type in a definition,
	 this is an error.  In a declaration this is valid, and a
	 struct or union type may be completed later, before any calls
	 or definition of the function.  In the case where the tag was
	 first declared within the parameter list, a warning has
	 already been given.  If a parameter has void type, then
	 this has already received an error (constraint violation in C2Y,
	 previously implicitly undefined behavior).  */

      ਲਈ (parm = arg_info->parms, typelt = arg_types, parmno = 1;
	   parm;
	   parm = DECL_CHAIN (parm), typelt = ਰੁੱਖ_CHAIN (typelt), parmno++)
	{
	  type = ਰੁੱਖ_ਮੁੱਲ (typelt);
	  ਜੇ (type == error_mark_ਗੰਢ)
	    ਜਾਰੀ;

	  ਜੇ (!COMPLETE_TYPE_P (type))
	    {
	      ਜੇ (funcdef_flag)
		{
		  ਜੇ (DECL_NAME (parm))
		    error_at (ਨਿਵੇਸ਼_location,
			      "parameter %u (%q+D) has incomplete type",
			      parmno, parm);
		  ਨਹੀਂਤਾਂ
		    error_at (DECL_ਸਰੋਤ_LOCATION (parm),
			      "parameter %u has incomplete type",
			      parmno);

		  ਰੁੱਖ_ਮੁੱਲ (typelt) = error_mark_ਗੰਢ;
		  ਰੁੱਖ_TYPE (parm) = error_mark_ਗੰਢ;
		  arg_types = NULL_ਰੁੱਖ;
		}
	    }

	  ਜੇ (DECL_NAME (parm) && ਰੁੱਖ_ਵਰਤਿਆ (parm))
	    warn_if_shadowing (parm);
	}
      ਵਾਪਸ arg_types;
    }
}

/* Allocate and initialize a c_arg_info structure from the parser's
   obstack.  */

ਬਣਤਰ c_arg_info *
build_arg_info (ਖਾਲੀ)
{
  ਬਣਤਰ c_arg_info *ret = XOBNEW (&parser_obstack, ਬਣਤਰ c_arg_info);
  ret->parms = NULL_ਰੁੱਖ;
  ret->ਟੈਗ_ਸੂਚੀ = ਨਿਰਾ;
  ret->types = NULL_ਰੁੱਖ;
  ret->others = NULL_ਰੁੱਖ;
  ret->pending_sizes = ਨਿਰਾ;
  ret->had_vla_unspec = 0;
  ret->no_named_ਦਲੀਲਾਂ_stdarg_p = 0;
  ret->c23_ਖਾਲੀ_ਥਾਵਾਂ_parens = 0;
  ਵਾਪਸ ret;
}

/* Take apart the current scope and return a c_arg_info structure with
   info on a parameter list just parsed.

   This structure is later fed to 'grokparms' and 'store_parm_decls'.

   ELLIPSIS being true means the argument list ended in '...' so don't
   append a sentinel (void_list_node) to the end of the type-list.

   EXPR is NULL or an expression that needs to be evaluated for the
   side effects of array size expressions in the parameters.  */

ਬਣਤਰ c_arg_info *
get_parm_info (ਤਾਰਕਿਕ ellipsis, ਰੁੱਖ ਵਿਅੰਜਕ)
{
  ਬਣਤਰ c_binding *b = current_scope->bindings;
  ਬਣਤਰ c_arg_info *arg_info = build_arg_info ();

  ਰੁੱਖ parms = NULL_ਰੁੱਖ;
  vec<c_arg_ਟੈਗ, va_gc> *ਟੈਗ_ਸੂਚੀ = ਨਿਰਾ;
  ਰੁੱਖ types = NULL_ਰੁੱਖ;
  ਰੁੱਖ others = NULL_ਰੁੱਖ;

  ਤਾਰਕਿਕ gave_void_only_once_err = ਝੂਠ;

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
  ਜੇ (b->prev == 0			    /* one binding */
      && ਰੁੱਖ_ਕੋਡ (b->decl) == PARM_DECL   /* which is a parameter */
      && !DECL_NAME (b->decl)               /* anonymous */
      && VOID_TYPE_P (ਰੁੱਖ_TYPE (b->decl))) /* of void type */
    {
      ਜੇ (TYPE_QUALS (ਰੁੱਖ_TYPE (b->decl)) != TYPE_UNQUALIFIED
	  || C_DECL_ਰਜਿਸਟਰ (b->decl))
	error_at (b->locus, "%<void%> as only parameter may not be qualified");

      /* There cannot be an ellipsis.  */
      ਜੇ (ellipsis)
	error_at (b->locus, "%<void%> must be the only parameter");

      arg_info->types = void_list_ਗੰਢ;
      ਵਾਪਸ arg_info;
    }

  ਜੇ (!ellipsis)
    types = void_list_ਗੰਢ;

  /* Break up the bindings list into parms, tags, types, and others;
     apply sanity checks; purge the name-to-decl bindings.  */
  ਜਦੋਂ (b)
    {
      ਰੁੱਖ decl = b->decl;
      ਰੁੱਖ type = ਰੁੱਖ_TYPE (decl);
      c_arg_ਟੈਗ ਟੈਗ;
      ਅਚਲ ਅੱਖਰ *keyword;

      ਚੋਣ (ਰੁੱਖ_ਕੋਡ (decl))
	{
	ਹਾਲਤ PARM_DECL:
	  ਜੇ (b->id)
	    {
	      gcc_assert (I_ਚਿੰਨ੍ਹ_BINDING (b->id) == b);
	      I_ਚਿੰਨ੍ਹ_BINDING (b->id) = b->shadowed;
	    }

	  /* Check for forward decls that never got their actual decl.  */
	  ਜੇ (ਰੁੱਖ_ASM_WRITTEN (decl))
	    error_at (b->locus,
		      "parameter %q+D has just a forward declaration", decl);
	  /* Check for (..., void, ...) and named void parameters and issue an
	     error.  */
	  ਨਹੀਂਤਾਂ ਜੇ (VOID_TYPE_P (type))
	    {
	      ਜੇ (!gave_void_only_once_err)
		{
		  error_at (b->locus,
			    "%<void%> must be the only parameter and unnamed");
		  gave_void_only_once_err = ਸੱਚ;
		}
	    }
	  ਨਹੀਂਤਾਂ
	    {
	      /* Valid parameter, add it to the list.  */
	      DECL_CHAIN (decl) = parms;
	      parms = decl;

	      /* Since there is a prototype, args are passed in their
		 declared types.  The back end may override this later.  */
	      DECL_ARG_TYPE (decl) = type;
	      types = ਰੁੱਖ_cons (0, type, types);
	    }
	  ਰੋਕੋ;

	ਹਾਲਤ ENUMERAL_TYPE: keyword = "enum"; ਜਾਓ ਟੈਗ;
	ਹਾਲਤ UNION_TYPE:    keyword = "union"; ਜਾਓ ਟੈਗ;
	ਹਾਲਤ ਰਿਕਾਰਡ_TYPE:   keyword = "struct"; ਜਾਓ ਟੈਗ;
	ਟੈਗ:
	  /* Types may not have tag-names, in which case the type
	     appears in the bindings list with b->id NULL.  */
	  ਜੇ (b->id)
	    {
	      gcc_assert (I_ਟੈਗ_BINDING (b->id) == b);
	      I_ਟੈਗ_BINDING (b->id) = b->shadowed;
	    }

	  /* Warn about any struct, union or enum tags defined in a
	     parameter list.  The scope of such types is limited to
	     the parameter list, which is rarely if ever desirable
	     (it's impossible to call such a function with type-
	     correct arguments).  An anonymous union parm type is
	     meaningful as a GNU extension, so don't warn for that.  */
	  ਜੇ (ਰੁੱਖ_ਕੋਡ (decl) != UNION_TYPE || b->id != NULL_ਰੁੱਖ)
	    {
	      ਜੇ (b->id)
		{
		  /* The %s will be one of 'struct', 'union', or 'enum'.  */
		  ਜੇ (!flag_isoc23 || !COMPLETE_TYPE_P (decl))
		    warning_at (b->locus, 0,
				"%<%s %E%> declared inside parameter list"
				" will not be visible outside of this definition or"
				" declaration", keyword, b->id);
		}
	      ਨਹੀਂਤਾਂ
		/* The %s will be one of 'struct', 'union', or 'enum'.  */
		warning_at (b->locus, 0,
			    "anonymous %s declared inside parameter list"
			    " will not be visible outside of this definition or"
			    " declaration", keyword);
	    }

	  ਟੈਗ.id = b->id;
	  ਟੈਗ.type = decl;
	  vec_ਸੁਰੱਖਿਅਤ_ਧੱਕੋ (ਟੈਗ_ਸੂਚੀ, ਟੈਗ);
	  ਰੋਕੋ;

	ਹਾਲਤ FUNCTION_DECL:
	  /* FUNCTION_DECLs appear when there is an implicit function
	     declaration in the parameter list.  */
	  gcc_assert (b->nested || ਵੇਖਿਆ_error ());
	  ਜਾਓ ਸੈੱਟ_shadowed;

	ਹਾਲਤ CONST_DECL:
	ਹਾਲਤ TYPE_DECL:
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

	ਹਾਲਤ ERROR_MARK:
	ਸੈੱਟ_shadowed:
	  /* error_mark_node appears here when we have an undeclared
	     variable.  Just throw it away.  */
	  ਜੇ (b->id)
	    {
	      gcc_assert (I_ਚਿੰਨ੍ਹ_BINDING (b->id) == b);
	      I_ਚਿੰਨ੍ਹ_BINDING (b->id) = b->shadowed;
	    }
	  ਰੋਕੋ;

	  /* Other things that might be encountered.  */
	ਹਾਲਤ LABEL_DECL:
	ਹਾਲਤ VAR_DECL:
	ਮੂਲ:
	  gcc_unreachable ();
	}

      b = free_binding_and_advance (b);
    }

  arg_info->parms = parms;
  arg_info->ਟੈਗ_ਸੂਚੀ = ਟੈਗ_ਸੂਚੀ;
  arg_info->types = types;
  arg_info->others = others;
  arg_info->pending_sizes = ਵਿਅੰਜਕ;
  arg_info->no_named_ਦਲੀਲਾਂ_stdarg_p = ellipsis && !types;
  ਵਾਪਸ arg_info;
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

ਬਣਤਰ c_typespec
parser_xref_ਟੈਗ (location_t loc, ਗਿਣਤੀ ਰੁੱਖ_ਕੋਡ_2 ਕੋਡ, ਰੁੱਖ name,
		 ਤਾਰਕਿਕ have_std_attrs, ਰੁੱਖ attrs, ਤਾਰਕਿਕ has_enum_type_specifier)
{
  ਬਣਤਰ c_typespec ret;
  ਰੁੱਖ ref;
  location_t refloc;

  ret.ਵਿਅੰਜਕ = NULL_ਰੁੱਖ;
  ret.ਵਿਅੰਜਕ_const_operands = ਸੱਚ;
  ret.has_enum_type_specifier = has_enum_type_specifier;

  /* If a cross reference is requested, look up the type already
     defined for this tag and return it.  If an enum type specifier is
     present, only a definition in the current scope is relevant.  */

  ref = lookup_ਟੈਗ (ਕੋਡ, name, has_enum_type_specifier, &refloc);

  /* If the visible type is still being defined, see if there is
     an earlier definition (which may be complete).  We do not
     have to loop because nested redefinitions are not allowed.  */
  ਜੇ (flag_isoc23 && ref && C_TYPE_BEING_DEFINED (ref))
    {
      ਰੁੱਖ vis = ਪਿਛਲਾ_ਟੈਗ (ref);
      ਜੇ (vis)
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
  ret.ਕਿਸਮ = (ref
	      ? (have_std_attrs ? ctsk_tagref_attrs : ctsk_tagref)
	      : (have_std_attrs ? ctsk_tagfirstref_attrs : ctsk_tagfirstref));
  ਜੇ (ref && ਰੁੱਖ_ਕੋਡ (ref) == ਕੋਡ)
    {
      decl_ਗੁਣ (&ref, attrs, (ਪੂਰਨ) ATTR_FLAG_TYPE_ਵਿੱਚ_ਰੱਖੋ);
      ਜੇ (C_TYPE_DEFINED_ਵਿੱਚ_STRUCT (ref)
	  && loc != UNKNOWN_LOCATION
	  && warn_cxx_compat)
	{
	  auto_diagnostic_ਸਮੂਹ d;
	  ਚੋਣ (ਕੋਡ)
	    {
	    ਹਾਲਤ ENUMERAL_TYPE:
	      ਜੇ (warning_at (loc, OPT_Wc___compat,
			      ("enum type defined in struct or union "
			       "is not visible in C++")))
		  inform (refloc, "enum type defined here");
	      ਰੋਕੋ;
	    ਹਾਲਤ ਰਿਕਾਰਡ_TYPE:
	      ਜੇ (warning_at (loc, OPT_Wc___compat,
			      ("struct defined in struct or union "
			       "is not visible in C++")))
		inform (refloc, "struct defined here");
	      ਰੋਕੋ;
	    ਹਾਲਤ UNION_TYPE:
	      ਜੇ (warning_at (loc, OPT_Wc___compat,
			      ("union defined in struct or union "
			       "is not visible in C++")))
		inform (refloc, "union defined here");
	      ਰੋਕੋ;
	    ਮੂਲ:
	      gcc_unreachable();
	    }
	}

      ret.spec = ref;
      ਵਾਪਸ ret;
    }

  /* If no such tag is yet defined, create a forward-reference node
     and record it as the "definition".
     When a real declaration of this type is found,
     the forward-reference will be altered into a real type.  */

  ref = make_ਗੰਢ (ਕੋਡ);
  ਜੇ (flag_isoc23 || ਕੋਡ == ENUMERAL_TYPE)
    ਸੈੱਟ_TYPE_STRUCTURAL_EQUALITY (ref);
  ਜੇ (ਕੋਡ == ENUMERAL_TYPE)
    {
      /* Give the type a default layout like unsigned int
	 to avoid crashing if it does not get defined.  */
      ਸੈੱਟ_TYPE_ਬਹੁਲਕ (ref, TYPE_ਬਹੁਲਕ (unsigned_type_ਗੰਢ));
      ਸੈੱਟ_TYPE_ALIGN (ref, TYPE_ALIGN (unsigned_type_ਗੰਢ));
      TYPE_USER_ALIGN (ref) = 0;
      TYPE_UNSIGNED (ref) = 1;
      TYPE_PRECISION (ref) = TYPE_PRECISION (unsigned_type_ਗੰਢ);
      TYPE_MIN_ਮੁੱਲ (ref) = TYPE_MIN_ਮੁੱਲ (unsigned_type_ਗੰਢ);
      TYPE_MAX_ਮੁੱਲ (ref) = TYPE_MAX_ਮੁੱਲ (unsigned_type_ਗੰਢ);
      ENUM_FIXED_UNDERLYING_TYPE_P (ref) = has_enum_type_specifier;
    }

  pushtag (loc, name, ref);
  decl_ਗੁਣ (&ref, attrs, (ਪੂਰਨ) ATTR_FLAG_TYPE_ਵਿੱਚ_ਰੱਖੋ);
  ਜੇ (ਵਿੱਚ_underspecified_init)
    error_at (loc, "%qT declared in underspecified object initializer",
	      ref);

  ret.spec = ref;
  ਵਾਪਸ ret;
}

/* Get the struct, enum or union (CODE says which) with tag NAME.
   Define the tag as a forward-reference if it is not defined.
   Return a tree for the type.  */

ਰੁੱਖ
xref_ਟੈਗ (ਗਿਣਤੀ ਰੁੱਖ_ਕੋਡ_2 ਕੋਡ, ਰੁੱਖ name)
{
  ਵਾਪਸ parser_xref_ਟੈਗ (ਨਿਵੇਸ਼_location, ਕੋਡ, name, ਝੂਠ, NULL_ਰੁੱਖ,
			  ਝੂਠ).spec;
}

/* Make sure that the tag NAME is defined *in the current scope*
   at least as a forward reference.
   LOC is the location of the struct's definition.
   CODE says which kind of tag NAME ought to be.

   This stores the current value of the file static STRUCT_PARSE_INFO
   in *ENCLOSING_STRUCT_PARSE_INFO, and points STRUCT_PARSE_INFO at a
   new c_struct_parse_info structure.  The old value of
   STRUCT_PARSE_INFO is restored in finish_struct.  */

ਰੁੱਖ
ਸ਼ੁਰੂ_struct (location_t loc, ਗਿਣਤੀ ਰੁੱਖ_ਕੋਡ_2 ਕੋਡ, ਰੁੱਖ name,
	      ਵਰਗ c_struct_parse_info **enclosing_struct_parse_info)
{
  /* If there is already a tag defined at this scope
     (as a forward reference), just return it.  */

  ਰੁੱਖ ref = NULL_ਰੁੱਖ;
  location_t refloc = UNKNOWN_LOCATION;

  ਜੇ (name != NULL_ਰੁੱਖ)
    ref = lookup_ਟੈਗ (ਕੋਡ, name, ਸੱਚ, &refloc);

  /* For C23, even if we already have a completed definition,
     we do not use it. We will check for consistency later.
     If we are in a nested redefinition the type is not
     complete. We will then detect this below.  */
  ਜੇ (flag_isoc23 && ref && TYPE_ਮਾਪ (ref))
    ref = NULL_ਰੁੱਖ;

  ਜੇ (ref && ਰੁੱਖ_ਕੋਡ (ref) == ਕੋਡ)
    {
      ਜੇ (TYPE_STUB_DECL (ref))
	refloc = DECL_ਸਰੋਤ_LOCATION (TYPE_STUB_DECL (ref));

      ਜੇ (TYPE_ਮਾਪ (ref))
	{
	  auto_diagnostic_ਸਮੂਹ d;
	  ਜੇ (ਕੋਡ == UNION_TYPE)
	    error_at (loc, "redefinition of %<union %E%>", name);
	  ਨਹੀਂਤਾਂ
	    error_at (loc, "redefinition of %<struct %E%>", name);
	  ਜੇ (refloc != UNKNOWN_LOCATION)
	    inform (refloc, "originally defined here");
	  /* Don't create structures using a name already in use.  */
	  ref = NULL_ਰੁੱਖ;
	}
      ਨਹੀਂਤਾਂ ਜੇ (C_TYPE_BEING_DEFINED (ref))
	{
	  ਜੇ (ਕੋਡ == UNION_TYPE)
	    error_at (loc, "nested redefinition of %<union %E%>", name);
	  ਨਹੀਂਤਾਂ
	    error_at (loc, "nested redefinition of %<struct %E%>", name);
	  /* Don't bother to report "originally defined here" for a
	     nested redefinition; the original definition should be
	     obvious.  */
	  /* Don't create structures that contain themselves.  */
	  ref = NULL_ਰੁੱਖ;
	}
    }

  /* Otherwise create a forward-reference just so the tag is in scope.  */

  ਜੇ (ref == NULL_ਰੁੱਖ || ਰੁੱਖ_ਕੋਡ (ref) != ਕੋਡ)
    {
      ref = make_ਗੰਢ (ਕੋਡ);
      ਜੇ (flag_isoc23)
	ਸੈੱਟ_TYPE_STRUCTURAL_EQUALITY (ref);
      pushtag (loc, name, ref);
    }

  C_TYPE_BEING_DEFINED (ref) = 1;
  ਲਈ (ਰੁੱਖ v = TYPE_MAIN_VARIANT (ref); v; v = TYPE_ਅਗਲਾ_VARIANT (v))
    TYPE_PACKED (v) = flag_pack_struct;

  *enclosing_struct_parse_info = struct_parse_info;
  struct_parse_info = ਨਵਾਂ c_struct_parse_info ();
  struct_parse_info->refloc = refloc;

  /* FIXME: This will issue a warning for a use of a type defined
     within a statement expr used within sizeof, et. al.  This is not
     terribly serious as C++ doesn't permit statement exprs within
     sizeof anyhow.  */
  ਜੇ (warn_cxx_compat
      && (ਵਿੱਚ_sizeof || ਵਿੱਚ_typeof || ਵਿੱਚ_alignof || ਵਿੱਚ_countof))
    warning_at (loc, OPT_Wc___compat,
		"defining type in %qs expression is invalid in C++",
		(ਵਿੱਚ_sizeof ? "sizeof"
		 : ਵਿੱਚ_typeof ? "typeof"
		 : ਵਿੱਚ_alignof ? "alignof"
		 : "_Countof"));

  ਜੇ (ਵਿੱਚ_underspecified_init)
    error_at (loc, "%qT defined in underspecified object initializer", ref);

  ਵਾਪਸ ref;
}

/* Process the specs, declarator and width (NULL if omitted)
   of a structure component, returning a FIELD_DECL node.
   WIDTH is non-NULL for bit-fields only, and is an INTEGER_CST node.
   DECL_ATTRS is as for grokdeclarator.

   LOC is the location of the structure component.

   This is done during the parsing of the struct declaration.
   The FIELD_DECL nodes are chained together and the lot of them
   are ultimately passed to `build_struct' to make the RECORD_TYPE node.  */

ਰੁੱਖ
grokfield (location_t loc,
	   ਬਣਤਰ c_declarator *declarator, ਬਣਤਰ c_declspecs *declspecs,
	   ਰੁੱਖ ਚੌੜਾਈ, ਰੁੱਖ *decl_attrs, ਰੁੱਖ *ਵਿਅੰਜਕ)
{
  ਰੁੱਖ ਮੁੱਲ;

  ਜੇ (declarator->ਕਿਸਮ == cdk_id && declarator->u.id.id == NULL_ਰੁੱਖ
      && ਚੌੜਾਈ == NULL_ਰੁੱਖ)
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

      ਰੁੱਖ type = declspecs->type;
      ਤਾਰਕਿਕ ok = ਝੂਠ;

      ਜੇ (ਰਿਕਾਰਡ_OR_UNION_TYPE_P (type)
	  && (flag_ms_extensions
	      || flag_plan9_extensions
	      || !declspecs->typedef_p))
	{
	  ਜੇ (flag_ms_extensions || flag_plan9_extensions)
	    ok = ਸੱਚ;
	  ਨਹੀਂਤਾਂ ਜੇ (TYPE_NAME (type) == ਨਿਰਾ)
	    ok = ਸੱਚ;
	  ਨਹੀਂਤਾਂ
	    ok = ਝੂਠ;
	}
      ਜੇ (!ok)
	{
	  pedwarn (loc, 0, "declaration does not declare anything");
	  ਵਾਪਸ NULL_ਰੁੱਖ;
	}
      ਜੇ (flag_isoc99)
	pedwarn_c99 (loc, OPT_Wpedantic,
		     "ISO C99 doesn%'t support unnamed structs/unions");
      ਨਹੀਂਤਾਂ
	pedwarn_c99 (loc, OPT_Wpedantic,
		     "ISO C90 doesn%'t support unnamed structs/unions");
    }

  ਮੁੱਲ = grokdeclarator (declarator, declspecs, ਖੇਤਰ, ਝੂਠ,
			  ਚੌੜਾਈ ? &ਚੌੜਾਈ : ਨਿਰਾ, decl_attrs, ਵਿਅੰਜਕ, ਨਿਰਾ,
			  DEPRECATED_ਸਾਧਾਰਨ);

  /* When this field has name, its type is a top level type, we should
     call verify_counted_by_for_top_anonymous_type.  */
  ਜੇ (DECL_NAME (ਮੁੱਲ) != NULL_ਰੁੱਖ
      && declspecs->typespec_ਕਿਸਮ == ctsk_tagdef)
    verify_counted_by_for_ਸਿਖਰ_anonymous_type (declspecs->type);

  ਅੰਤ_decl (ਮੁੱਲ, loc, NULL_ਰੁੱਖ, NULL_ਰੁੱਖ, NULL_ਰੁੱਖ);
  DECL_INITIAL (ਮੁੱਲ) = ਚੌੜਾਈ;
  ਜੇ (ਚੌੜਾਈ)
    ਸੈੱਟ_DECL_C_ਦੋਆਧਾਰੀ_ਅੰਕ_ਖੇਤਰ (ਮੁੱਲ);

  ਜੇ (warn_cxx_compat && DECL_NAME (ਮੁੱਲ) != NULL_ਰੁੱਖ)
    {
      /* If we currently have a binding for this field, set the
	 in_struct field in the binding, so that we warn about lookups
	 which find it.  */
      ਬਣਤਰ c_binding *b = I_ਚਿੰਨ੍ਹ_BINDING (DECL_NAME (ਮੁੱਲ));
      ਜੇ (b != ਨਿਰਾ)
	{
	  /* If the in_struct field is not yet set, push it on a list
	     to be cleared when this struct is finished.  */
	  ਜੇ (!b->ਵਿੱਚ_struct)
	    {
	      struct_parse_info->fields.ਸੁਰੱਖਿਅਤ_ਧੱਕੋ (b);
	      b->ਵਿੱਚ_struct = 1;
	    }
	}
    }

  ਵਾਪਸ ਮੁੱਲ;
}

/* Subroutine of detect_field_duplicates: return whether X and Y,
   which are both fields in the same struct, have duplicate field
   names.  */

ਸਥਿਰ ਤਾਰਕਿਕ
is_duplicate_ਖੇਤਰ (ਰੁੱਖ x, ਰੁੱਖ y)
{
  ਜੇ (DECL_NAME (x) != NULL_ਰੁੱਖ && DECL_NAME (x) == DECL_NAME (y))
    ਵਾਪਸ ਸੱਚ;

  /* When using -fplan9-extensions, an anonymous field whose name is a
     typedef can duplicate a field name.  */
  ਜੇ (flag_plan9_extensions
      && (DECL_NAME (x) == NULL_ਰੁੱਖ || DECL_NAME (y) == NULL_ਰੁੱਖ))
    {
      ਰੁੱਖ xt, xn, yt, yn;

      xt = ਰੁੱਖ_TYPE (x);
      ਜੇ (DECL_NAME (x) != NULL_ਰੁੱਖ)
	xn = DECL_NAME (x);
      ਨਹੀਂਤਾਂ ਜੇ (ਰਿਕਾਰਡ_OR_UNION_TYPE_P (xt)
	       && TYPE_NAME (xt) != NULL_ਰੁੱਖ
	       && ਰੁੱਖ_ਕੋਡ (TYPE_NAME (xt)) == TYPE_DECL)
	xn = DECL_NAME (TYPE_NAME (xt));
      ਨਹੀਂਤਾਂ
	xn = NULL_ਰੁੱਖ;

      yt = ਰੁੱਖ_TYPE (y);
      ਜੇ (DECL_NAME (y) != NULL_ਰੁੱਖ)
	yn = DECL_NAME (y);
      ਨਹੀਂਤਾਂ ਜੇ (ਰਿਕਾਰਡ_OR_UNION_TYPE_P (yt)
	       && TYPE_NAME (yt) != NULL_ਰੁੱਖ
	       && ਰੁੱਖ_ਕੋਡ (TYPE_NAME (yt)) == TYPE_DECL)
	yn = DECL_NAME (TYPE_NAME (yt));
      ਨਹੀਂਤਾਂ
	yn = NULL_ਰੁੱਖ;

      ਜੇ (xn != NULL_ਰੁੱਖ && xn == yn)
	ਵਾਪਸ ਸੱਚ;
    }

  ਵਾਪਸ ਝੂਠ;
}

/* Subroutine of detect_field_duplicates: add the fields of FIELDLIST
   to HTAB, giving errors for any duplicates.  */

ਸਥਿਰ ਖਾਲੀ
detect_ਖੇਤਰ_duplicates_hash (ਰੁੱਖ fieldlist,
			      hash_ਸਾਰਣੀ<nofree_ptr_hash <ਰੁੱਖ_ਗੰਢ> > *htab)
{
  ਰੁੱਖ x, y;
  ਰੁੱਖ_ਗੰਢ **ਥਾਂ;

  ਲਈ (x = fieldlist; x ; x = DECL_CHAIN (x))
    ਜੇ ((y = DECL_NAME (x)) != NULL_ਰੁੱਖ)
      {
	ਥਾਂ = htab->ਲੱਭੋ_ਥਾਂ (y, ਪਾਓ);
	ਜੇ (*ਥਾਂ)
	  {
	    error ("duplicate member %q+D", x);
	    DECL_NAME (x) = NULL_ਰੁੱਖ;
	  }
	*ਥਾਂ = y;
      }
    ਨਹੀਂਤਾਂ ਜੇ (ਰਿਕਾਰਡ_OR_UNION_TYPE_P (ਰੁੱਖ_TYPE (x)))
      {
	detect_ਖੇਤਰ_duplicates_hash (TYPE_FIELDS (ਰੁੱਖ_TYPE (x)), htab);

	/* When using -fplan9-extensions, an anonymous field whose
	   name is a typedef can duplicate a field name.  */
	ਜੇ (flag_plan9_extensions
	    && TYPE_NAME (ਰੁੱਖ_TYPE (x)) != NULL_ਰੁੱਖ
	    && ਰੁੱਖ_ਕੋਡ (TYPE_NAME (ਰੁੱਖ_TYPE (x))) == TYPE_DECL)
	  {
	    ਰੁੱਖ xn = DECL_NAME (TYPE_NAME (ਰੁੱਖ_TYPE (x)));
	    ਥਾਂ = htab->ਲੱਭੋ_ਥਾਂ (xn, ਪਾਓ);
	    ਜੇ (*ਥਾਂ)
	      error ("duplicate member %q+D", TYPE_NAME (ਰੁੱਖ_TYPE (x)));
	    *ਥਾਂ = xn;
	  }
      }
}

/* Generate an error for any duplicate field names in FIELDLIST.  Munge
   the list such that this does not present a problem later.  */

ਸਥਿਰ ਖਾਲੀ
detect_ਖੇਤਰ_duplicates (ਰੁੱਖ fieldlist)
{
  ਰੁੱਖ x, y;
  ਪੂਰਨ timeout = 10;

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
  ਜੇ (c_dialect_objc ())
    ਜੇ (objc_detect_ਖੇਤਰ_duplicates (ਝੂਠ))
      ਵਾਪਸ;

  /* First, see if there are more than "a few" fields.
     This is trivially true if there are zero or one fields.  */
  ਜੇ (!fieldlist || !DECL_CHAIN (fieldlist))
    ਵਾਪਸ;
  x = fieldlist;
  ਕਰੋ {
    timeout--;
    ਜੇ (DECL_NAME (x) == NULL_ਰੁੱਖ
	&& ਰਿਕਾਰਡ_OR_UNION_TYPE_P (ਰੁੱਖ_TYPE (x)))
      timeout = 0;
    x = DECL_CHAIN (x);
  } ਜਦੋਂ (timeout > 0 && x);

  /* If there were "few" fields and no anonymous structures or unions,
     avoid the overhead of allocating a hash table.  Instead just do
     the nested traversal thing.  */
  ਜੇ (timeout > 0)
    {
      ਲਈ (x = DECL_CHAIN (fieldlist); x; x = DECL_CHAIN (x))
	/* When using -fplan9-extensions, we can have duplicates
	   between typedef names and fields.  */
	ਜੇ (DECL_NAME (x)
	    || (flag_plan9_extensions
		&& DECL_NAME (x) == NULL_ਰੁੱਖ
		&& ਰਿਕਾਰਡ_OR_UNION_TYPE_P (ਰੁੱਖ_TYPE (x))
		&& TYPE_NAME (ਰੁੱਖ_TYPE (x)) != NULL_ਰੁੱਖ
		&& ਰੁੱਖ_ਕੋਡ (TYPE_NAME (ਰੁੱਖ_TYPE (x))) == TYPE_DECL))
	  {
	    ਲਈ (y = fieldlist; y != x; y = ਰੁੱਖ_CHAIN (y))
	      ਜੇ (is_duplicate_ਖੇਤਰ (y, x))
		{
		  error ("duplicate member %q+D", x);
		  DECL_NAME (x) = NULL_ਰੁੱਖ;
		}
	  }
    }
  ਨਹੀਂਤਾਂ
    {
      hash_ਸਾਰਣੀ<nofree_ptr_hash <ਰੁੱਖ_ਗੰਢ> > htab (37);
      detect_ਖੇਤਰ_duplicates_hash (fieldlist, &htab);
    }
}

/* Finish up struct info used by -Wc++-compat.  */

ਸਥਿਰ ਖਾਲੀ
warn_cxx_compat_ਅੰਤ_struct (ਰੁੱਖ fieldlist, ਗਿਣਤੀ ਰੁੱਖ_ਕੋਡ_2 ਕੋਡ,
			       location_t ਰਿਕਾਰਡ_loc)
{
  ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ix;
  ਰੁੱਖ x;
  ਬਣਤਰ c_binding *b;

  ਜੇ (fieldlist == NULL_ਰੁੱਖ)
    {
      ਜੇ (ਕੋਡ == ਰਿਕਾਰਡ_TYPE)
	warning_at (ਰਿਕਾਰਡ_loc, OPT_Wc___compat,
		    "empty struct has size 0 in C, size 1 in C++");
      ਨਹੀਂਤਾਂ
	warning_at (ਰਿਕਾਰਡ_loc, OPT_Wc___compat,
		    "empty union has size 0 in C, size 1 in C++");
    }

  /* Set the C_TYPE_DEFINED_IN_STRUCT flag for each type defined in
     the current struct.  We do this now at the end of the struct
     because the flag is used to issue visibility warnings, and we
     only want to issue those warnings if the type is referenced
     outside of the struct declaration.  */
  FOR_EACH_VEC_ELT (struct_parse_info->struct_types, ix, x)
    C_TYPE_DEFINED_ਵਿੱਚ_STRUCT (x) = 1;

  /* The TYPEDEFS_SEEN field of STRUCT_PARSE_INFO is a list of
     typedefs used when declaring fields in this struct.  If the name
     of any of the fields is also a typedef name then the struct would
     not parse in C++, because the C++ lookup rules say that the
     typedef name would be looked up in the context of the struct, and
     would thus be the field rather than the typedef.  */
  ਜੇ (!struct_parse_info->typedefs_ਵੇਖਿਆ.is_ਖਾਲੀ_ਥਾਵਾਂ ()
      && fieldlist != NULL_ਰੁੱਖ)
    {
      /* Use a hash_set<tree> using the name of the typedef.  We can use
	 a hash_set<tree> because identifiers are interned.  */
      hash_ਸੈੱਟ<ਰੁੱਖ> tset;

      FOR_EACH_VEC_ELT (struct_parse_info->typedefs_ਵੇਖਿਆ, ix, x)
	tset.ਜੋੜੋ (DECL_NAME (x));

      ਲਈ (x = fieldlist; x != NULL_ਰੁੱਖ; x = DECL_CHAIN (x))
	{
	  ਜੇ (DECL_NAME (x) != NULL_ਰੁੱਖ
	      && tset.ਸ਼ਾਮਲ_ਹੈ (DECL_NAME (x)))
	    {
	      warning_at (DECL_ਸਰੋਤ_LOCATION (x), OPT_Wc___compat,
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
    b->ਵਿੱਚ_struct = 0;
}

/* Function to help qsort sort FIELD_DECLs by name order.  */

ਸਥਿਰ ਪੂਰਨ
ਖੇਤਰ_decl_cmp (ਅਚਲ ਖਾਲੀ *x_p, ਅਚਲ ਖਾਲੀ *y_p)
{
  ਅਚਲ ਰੁੱਖ *ਅਚਲ x = (ਅਚਲ ਰੁੱਖ *) x_p;
  ਅਚਲ ਰੁੱਖ *ਅਚਲ y = (ਅਚਲ ਰੁੱਖ *) y_p;

  ਜੇ (DECL_NAME (*x) == DECL_NAME (*y))
    /* A nontype is "greater" than a type.  */
    ਵਾਪਸ (ਰੁੱਖ_ਕੋਡ (*y) == TYPE_DECL) - (ਰੁੱਖ_ਕੋਡ (*x) == TYPE_DECL);
  ਜੇ (DECL_NAME (*x) == NULL_ਰੁੱਖ)
    ਵਾਪਸ -1;
  ਜੇ (DECL_NAME (*y) == NULL_ਰੁੱਖ)
    ਵਾਪਸ 1;
  ਜੇ (DECL_NAME (*x) < DECL_NAME (*y))
    ਵਾਪਸ -1;
  ਵਾਪਸ 1;
}

/* If this structure or union completes the type of any previous
   variable declaration, lay it out and output its rtl.  */
ਸਥਿਰ ਖਾਲੀ
ਅੰਤ_incomplete_vars (ਰੁੱਖ incomplete_vars, ਤਾਰਕਿਕ toplevel)
{
  ਲਈ (ਰੁੱਖ x = incomplete_vars; x; x = ਰੁੱਖ_CHAIN (x))
    {
      ਰੁੱਖ decl = ਰੁੱਖ_ਮੁੱਲ (x);
      ਜੇ (ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (decl)) == ARRAY_TYPE)
	layout_array_type (ਰੁੱਖ_TYPE (decl));
      ਜੇ (ਰੁੱਖ_ਕੋਡ (decl) != TYPE_DECL)
	{
	  relayout_decl (decl);
	  ਜੇ (c_dialect_objc ())
	    objc_check_decl (decl);
	  rest_ਦਾ_decl_compilation (decl, toplevel, 0);
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

ਸਥਿਰ ਤਾਰਕਿਕ
is_flexible_array_member_p (ਤਾਰਕਿਕ is_ਆਖਰੀ_ਖੇਤਰ,
			    ਰੁੱਖ x)
{
  /* If not the last field, return false.  */
  ਜੇ (!is_ਆਖਰੀ_ਖੇਤਰ)
    ਵਾਪਸ ਝੂਠ;

  /* If not an array field, return false.  */
  ਜੇ (ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (x)) != ARRAY_TYPE)
    ਵਾਪਸ ਝੂਠ;

  ਤਾਰਕਿਕ is_zero_ਲੰਮਾਈ_array = zero_ਲੰਮਾਈ_array_type_p (ਰੁੱਖ_TYPE (x));
  ਤਾਰਕਿਕ is_one_element_array = one_element_array_type_p (ਰੁੱਖ_TYPE (x));
  ਤਾਰਕਿਕ is_flexible_array = flexible_array_member_type_p (ਰੁੱਖ_TYPE (x));

  ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ strict_flex_array_level = c_strict_flex_array_level_ਦਾ (x);

  ਚੋਣ (strict_flex_array_level)
    {
      ਹਾਲਤ 0:
	/* Default, all trailing arrays are flexible array members.  */
	ਵਾਪਸ ਸੱਚ;
      ਹਾਲਤ 1:
	/* Level 1: all "[1]", "[0]", and "[]" are flexible array members.  */
	ਜੇ (is_one_element_array)
	  ਵਾਪਸ ਸੱਚ;
	/* FALLTHROUGH.  */
      ਹਾਲਤ 2:
	/* Level 2: all "[0]", and "[]" are flexible array members.  */
	ਜੇ (is_zero_ਲੰਮਾਈ_array)
	  ਵਾਪਸ ਸੱਚ;
	/* FALLTHROUGH.  */
      ਹਾਲਤ 3:
	/* Level 3: Only "[]" are flexible array members.  */
	ਜੇ (is_flexible_array)
	  ਵਾਪਸ ਸੱਚ;
	ਰੋਕੋ;
      ਮੂਲ:
	gcc_unreachable ();
    }
  ਵਾਪਸ ਝੂਠ;
}

/* Recompute TYPE_CANONICAL for variants of the type including qualified
   versions of the type and related pointer types after an aggregate type
   has been finalized.
   Will not update array types, pointers to array types, function
   types and other derived types created while the type was still
   incomplete, those will remain TYPE_STRUCTURAL_EQUALITY_P.  */

ਸਥਿਰ ਖਾਲੀ
c_update_type_canonical (ਰੁੱਖ t)
{
  gcc_checking_assert (TYPE_MAIN_VARIANT (t) == t && !TYPE_QUALS (t));
  ਲਈ (ਰੁੱਖ x = t, l = NULL_ਰੁੱਖ; x; l = x, x = TYPE_ਅਗਲਾ_VARIANT (x))
    {
      ਜੇ (x != t && TYPE_STRUCTURAL_EQUALITY_P (x))
	{
	  ਜੇ (!TYPE_QUALS (x))
	    TYPE_CANONICAL (x) = TYPE_CANONICAL (t);
	  ਨਹੀਂਤਾਂ
	    {
	      ਰੁੱਖ
		c = c_build_qualified_type (TYPE_CANONICAL (t), TYPE_QUALS (x));
	      ਜੇ (TYPE_STRUCTURAL_EQUALITY_P (c))
		{
		  gcc_checking_assert (TYPE_CANONICAL (t) == t);
		  ਜੇ (c == x)
		    TYPE_CANONICAL (x) = x;
		  ਨਹੀਂਤਾਂ
		    {
		      /* build_qualified_type for this function unhelpfully
			 moved c from some later spot in TYPE_MAIN_VARIANT (t)
			 chain to right after t (or created it there).  Move
			 it right before x and process c and then x.  */
		      gcc_checking_assert (TYPE_ਅਗਲਾ_VARIANT (t) == c);
		      ਜੇ (l != t)
			{
			  TYPE_ਅਗਲਾ_VARIANT (t) = TYPE_ਅਗਲਾ_VARIANT (c);
			  TYPE_ਅਗਲਾ_VARIANT (l) = c;
			  TYPE_ਅਗਲਾ_VARIANT (c) = x;
			}
		      TYPE_CANONICAL (c) = c;
		      x = c;
		    }
		}
	      ਨਹੀਂਤਾਂ
		TYPE_CANONICAL (x) = TYPE_CANONICAL (c);
	    }
	}
      ਨਹੀਂਤਾਂ ਜੇ (x != t)
	ਜਾਰੀ;
      ਲਈ (ਰੁੱਖ p = TYPE_ਸੂਚਕ_ਮੰਜ਼ਿਲ (x); p; p = TYPE_ਅਗਲਾ_PTR_ਮੰਜ਼ਿਲ (p))
	{
	  ਜੇ (!TYPE_STRUCTURAL_EQUALITY_P (p))
	    ਜਾਰੀ;
	  ਜੇ (TYPE_CANONICAL (x) != x || TYPE_REF_CAN_ALIAS_ALL (p))
	    TYPE_CANONICAL (p)
	      = c_build_ਸੂਚਕ_type_for_ਬਹੁਲਕ (TYPE_CANONICAL (x), TYPE_ਬਹੁਲਕ (p),
					       ਝੂਠ);
	  ਨਹੀਂਤਾਂ
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

ਸਥਿਰ ਖਾਲੀ
c_update_variably_modified (ਰੁੱਖ t)
{
  ਲਈ (ਰੁੱਖ x = t; x; x = TYPE_ਅਗਲਾ_VARIANT (x))
    {
      C_TYPE_VARIABLY_MODIFIED (x) = 1;
      ਲਈ (ਰੁੱਖ p = TYPE_ਸੂਚਕ_ਮੰਜ਼ਿਲ (x); p; p = TYPE_ਅਗਲਾ_PTR_ਮੰਜ਼ਿਲ (p))
	c_update_variably_modified (p);
    }
}


/* Verify the argument of the counted_by attribute of each field of
   the containing structure, OUTMOST_STRUCT_TYPE, including its inner
   anonymous struct/union, Report error and remove the corresponding
   attribute when it's not.  */

ਸਥਿਰ ਖਾਲੀ
verify_counted_by_attribute (ਰੁੱਖ outmost_struct_type,
			     ਰੁੱਖ cur_struct_type)
{
  ਲਈ (ਰੁੱਖ ਖੇਤਰ_2 = TYPE_FIELDS (cur_struct_type); ਖੇਤਰ_2;
       ਖੇਤਰ_2 = ਰੁੱਖ_CHAIN (ਖੇਤਰ_2))
    {
      ਜੇ (flexible_array_member_type_p (ਰੁੱਖ_TYPE (ਖੇਤਰ_2))
	   || ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (ਖੇਤਰ_2)) == ਸੂਚਕ_TYPE)
	{
	  ਰੁੱਖ attr_counted_by = lookup_attribute ("counted_by",
						   DECL_ਗੁਣ (ਖੇਤਰ_2));

	  ਜੇ (!attr_counted_by)
	    ਜਾਰੀ;

	  /* If there is an counted_by attribute attached to the field,
	     verify it.  */

	  ਰੁੱਖ fieldname = ਰੁੱਖ_ਮੁੱਲ (ਰੁੱਖ_ਮੁੱਲ (attr_counted_by));

	  /* Verify the argument of the attribute is a valid field of the
	     containing structure.  */

	  ਰੁੱਖ counted_by_ਖੇਤਰ = lookup_ਖੇਤਰ (outmost_struct_type,
						fieldname);

	  /* Error when the field is not found in the containing structure
	     and remove the corresponding counted_by attribute from the
	     field_decl.  */
	  ਜੇ (!counted_by_ਖੇਤਰ)
	    {
	      error_at (DECL_ਸਰੋਤ_LOCATION (ਖੇਤਰ_2),
		    "argument %qE to the %<counted_by%> attribute"
		    " is not a field declaration in the same structure"
		    " as %qD", fieldname, ਖੇਤਰ_2);
	      DECL_ਗੁਣ (ਖੇਤਰ_2)
		= remove_attribute ("counted_by", DECL_ਗੁਣ (ਖੇਤਰ_2));
	    }
	  ਨਹੀਂਤਾਂ
	  /* Error when the field is not with an integer type.  */
	    {
	      ਜਦੋਂ (ਰੁੱਖ_CHAIN (counted_by_ਖੇਤਰ))
		counted_by_ਖੇਤਰ = ਰੁੱਖ_CHAIN (counted_by_ਖੇਤਰ);
	      ਰੁੱਖ real_ਖੇਤਰ = ਰੁੱਖ_ਮੁੱਲ (counted_by_ਖੇਤਰ);

	      ਜੇ (!INTEGRAL_TYPE_P (ਰੁੱਖ_TYPE (real_ਖੇਤਰ)))
		{
		  error_at (DECL_ਸਰੋਤ_LOCATION (ਖੇਤਰ_2),
			"argument %qE to the %<counted_by%> attribute"
			" is not a field declaration with an integer type",
			fieldname);
		  DECL_ਗੁਣ (ਖੇਤਰ_2)
		    = remove_attribute ("counted_by",
				    DECL_ਗੁਣ (ਖੇਤਰ_2));
		}
	    }
	}
      ਨਹੀਂਤਾਂ ਜੇ (ਰਿਕਾਰਡ_OR_UNION_TYPE_P (ਰੁੱਖ_TYPE (ਖੇਤਰ_2))
	       && (DECL_NAME (ਖੇਤਰ_2) == NULL_ਰੁੱਖ))
	verify_counted_by_attribute (outmost_struct_type, ਰੁੱਖ_TYPE (ਖੇਤਰ_2));
    }
}

/* Caller should make sure the TYPE is a top-level type (i.e. not being
   nested in other structure/uniona). For such type, verify its counted_by
   if it is an anonymous structure/union.  */

ਖਾਲੀ
verify_counted_by_for_ਸਿਖਰ_anonymous_type (ਰੁੱਖ type)
{
  ਜੇ (!ਰਿਕਾਰਡ_OR_UNION_TYPE_P (type))
    ਵਾਪਸ;

  ਜੇ (C_TYPE_FIELDS_HAS_COUNTED_BY (type)
      && c_type_ਟੈਗ (type) == NULL_ਰੁੱਖ)
    verify_counted_by_attribute (type, type);
}

/* TYPE is a struct or union that we're applying may_alias to after the body is
   parsed.  Fixup any POINTER_TO types.  */

ਸਥਿਰ ਖਾਲੀ
c_fixup_may_alias (ਰੁੱਖ type)
{
  ਲਈ (ਰੁੱਖ t = TYPE_ਸੂਚਕ_ਮੰਜ਼ਿਲ (type); t; t = TYPE_ਅਗਲਾ_PTR_ਮੰਜ਼ਿਲ (t))
    ਲਈ (ਰੁੱਖ v = TYPE_MAIN_VARIANT (t); v; v = TYPE_ਅਗਲਾ_VARIANT (v))
      TYPE_REF_CAN_ALIAS_ALL (v) = ਸੱਚ;
}

/* Fill in the fields of a RECORD_TYPE or UNION_TYPE node, T.
   LOC is the location of the RECORD_TYPE or UNION_TYPE's definition.
   FIELDLIST is a chain of FIELD_DECL nodes for the fields.
   ATTRIBUTES are attributes to be applied to the structure.

   ENCLOSING_STRUCT_PARSE_INFO is the value of STRUCT_PARSE_INFO when
   the struct was started.  */

ਰੁੱਖ
ਅੰਤ_struct (location_t loc, ਰੁੱਖ t, ਰੁੱਖ fieldlist, ਰੁੱਖ ਗੁਣ,
	       ਵਰਗ c_struct_parse_info *enclosing_struct_parse_info,
	       ਰੁੱਖ *ਵਿਅੰਜਕ)
{
  ਰੁੱਖ x;
  ਤਾਰਕਿਕ toplevel = file_scope == current_scope;

  /* If this type was previously laid out as a forward reference,
     make sure we lay it out again.  */

  TYPE_ਮਾਪ (t) = NULL_ਰੁੱਖ;

  decl_ਗੁਣ (&t, ਗੁਣ, (ਪੂਰਨ) ATTR_FLAG_TYPE_ਵਿੱਚ_ਰੱਖੋ);

  ਜੇ (pedantic)
    {
      ਲਈ (x = fieldlist; x; x = DECL_CHAIN (x))
	{
	  ਜੇ (DECL_NAME (x) != NULL_ਰੁੱਖ)
	    ਰੋਕੋ;
	  ਜੇ (flag_isoc11 && ਰਿਕਾਰਡ_OR_UNION_TYPE_P (ਰੁੱਖ_TYPE (x)))
	    ਰੋਕੋ;
	}

      ਜੇ (x == NULL_ਰੁੱਖ)
	{
	  ਜੇ (ਰੁੱਖ_ਕੋਡ (t) == UNION_TYPE)
	    {
	      ਜੇ (fieldlist)
		pedwarn (loc, OPT_Wpedantic, "union has no named members");
	      ਨਹੀਂਤਾਂ
		pedwarn (loc, OPT_Wpedantic, "union has no members");
	    }
	  ਨਹੀਂਤਾਂ
	    {
	      ਜੇ (fieldlist)
		pedwarn (loc, OPT_Wpedantic, "struct has no named members");
	      ਨਹੀਂਤਾਂ
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

  ਤਾਰਕਿਕ saw_named_ਖੇਤਰ = ਝੂਠ;
  ਲਈ (x = fieldlist; x; x = DECL_CHAIN (x))
    {
      /* Whether this field is the last field of the structure or union.
	 for UNION, any field is the last field of it.  */
      ਤਾਰਕਿਕ is_ਆਖਰੀ_ਖੇਤਰ = (DECL_CHAIN (x) == NULL_ਰੁੱਖ)
			    || (ਰੁੱਖ_ਕੋਡ (t) == UNION_TYPE);

      ਜੇ (ਰੁੱਖ_TYPE (x) == error_mark_ਗੰਢ)
	ਜਾਰੀ;

      DECL_CONTEXT (x) = t;

      ਰੁੱਖ t1 = strip_array_types (ਰੁੱਖ_TYPE (x));
      /* If any field is const, the structure type is pseudo-const.  */
      ਜੇ (ਰੁੱਖ_READONLY (x))
	C_TYPE_FIELDS_READONLY (t) = 1;
      ਨਹੀਂਤਾਂ
	{
	  /* A field that is pseudo-const makes the structure likewise.  */
	  ਜੇ (ਰਿਕਾਰਡ_OR_UNION_TYPE_P (t1) && C_TYPE_FIELDS_READONLY (t1))
	    C_TYPE_FIELDS_READONLY (t) = 1;
	}

      /* Any field that is volatile means variables of this type must be
	 treated in some ways as volatile.  */
      ਜੇ (ਰੁੱਖ_THIS_VOLATILE (x))
	{
	  C_TYPE_FIELDS_VOLATILE (t) = 1;
	  C_TYPE_FIELDS_NON_CONSTEXPR (t) = 1;
	}

      /* Any field that is volatile, restrict-qualified or atomic
	 means the type cannot be used for a constexpr object.  */
      ਜੇ (TYPE_QUALS (t1)
	  & (TYPE_QUAL_VOLATILE | TYPE_QUAL_RESTRICT | TYPE_QUAL_ATOMIC))
	C_TYPE_FIELDS_NON_CONSTEXPR (t) = 1;
      ਨਹੀਂਤਾਂ ਜੇ (ਰਿਕਾਰਡ_OR_UNION_TYPE_P (t1) && C_TYPE_FIELDS_NON_CONSTEXPR (t1))
	    C_TYPE_FIELDS_NON_CONSTEXPR (t) = 1;

      /* Any field of nominal variable size implies structure is too.  */
      ਜੇ (C_DECL_VARIABLE_ਮਾਪ (x))
	C_TYPE_VARIABLE_ਮਾਪ (t) = 1;

      /* If any field is variably modified, record this fact. */
      ਜੇ (c_type_variably_modified_p (ਰੁੱਖ_TYPE (x)))
	C_TYPE_VARIABLY_MODIFIED (t) = 1;

      ਜੇ (DECL_C_ਦੋਆਧਾਰੀ_ਅੰਕ_ਖੇਤਰ (x))
	{
	  ਬਿਨਾਨਿਸ਼ਾਨੀ HOST_WIDE_INT ਚੌੜਾਈ = ਰੁੱਖ_ਮੰਜ਼ਿਲ_uhwi (DECL_INITIAL (x));
	  DECL_ਮਾਪ (x) = bitsize_int (ਚੌੜਾਈ);
	  DECL_ਦੋਆਧਾਰੀ_ਅੰਕ_ਖੇਤਰ (x) = 1;
	}

      ਜੇ (TYPE_PACKED (t)
	  && (DECL_ਦੋਆਧਾਰੀ_ਅੰਕ_ਖੇਤਰ (x)
	      || TYPE_ALIGN (ਰੁੱਖ_TYPE (x)) > ਬਿੱਟ_ਪ੍ਰਤੀ_UNIT))
	DECL_PACKED (x) = 1;

      /* Detect flexible array member in an invalid context.  */
      ਜੇ (flexible_array_member_type_p (ਰੁੱਖ_TYPE (x)))
	{
	  ਜੇ (ਰੁੱਖ_ਕੋਡ (t) == UNION_TYPE)
	    pedwarn (DECL_ਸਰੋਤ_LOCATION (x), OPT_Wpedantic,
		     "flexible array member in union is a GCC extension");
	  ਨਹੀਂਤਾਂ ਜੇ (!is_ਆਖਰੀ_ਖੇਤਰ)
	    {
	      error_at (DECL_ਸਰੋਤ_LOCATION (x),
			"flexible array member not at end of struct");
	      ਰੁੱਖ_TYPE (x) = error_mark_ਗੰਢ;
	    }
	  ਨਹੀਂਤਾਂ ਜੇ (!saw_named_ਖੇਤਰ)
	    pedwarn (DECL_ਸਰੋਤ_LOCATION (x), OPT_Wpedantic,
		     "flexible array member in a struct with no named "
		     "members is a GCC extension");
	  ਜੇ (lookup_attribute ("counted_by", DECL_ਗੁਣ (x)))
	    C_TYPE_FIELDS_HAS_COUNTED_BY (t) = 1;
	}

      ਜੇ (ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (x)) == ਸੂਚਕ_TYPE
	  && lookup_attribute ("counted_by", DECL_ਗੁਣ (x)))
	C_TYPE_FIELDS_HAS_COUNTED_BY (t) = 1;

      /* If the field is an anonymous structure that includes a field
	 with counted_by attribute, this structure should also be marked
	 too.  */
      ਜੇ (ਰਿਕਾਰਡ_OR_UNION_TYPE_P (ਰੁੱਖ_TYPE (x))
	  && C_TYPE_FIELDS_HAS_COUNTED_BY (ਰੁੱਖ_TYPE (x))
	  && DECL_NAME (x) == NULL_ਰੁੱਖ
	  && c_type_ਟੈਗ (ਰੁੱਖ_TYPE (x)) == NULL_ਰੁੱਖ)
	C_TYPE_FIELDS_HAS_COUNTED_BY (t) = 1;

      ਜੇ (pedantic && ਰੁੱਖ_ਕੋਡ (t) == ਰਿਕਾਰਡ_TYPE
	  && flexible_array_type_p (ਰੁੱਖ_TYPE (x)))
	pedwarn (DECL_ਸਰੋਤ_LOCATION (x), OPT_Wpedantic,
		 "invalid use of structure with flexible array member");

      /* Set DECL_NOT_FLEXARRAY flag for FIELD_DECL x.  */
      DECL_NOT_FLEXARRAY (x) = !is_flexible_array_member_p (is_ਆਖਰੀ_ਖੇਤਰ, x);

      /* Set TYPE_INCLUDES_FLEXARRAY for the context of x, t.
	 when x is an array and is the last field.
	 There is only one last_field for a structure type, but there might
	 be multiple last_fields for a union type, therefore we should ORed
	 the result for multiple last_fields.  */
      ਜੇ (ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (x)) == ARRAY_TYPE)
	TYPE_INCLUDES_FLEXARRAY (t)
	  |= is_ਆਖਰੀ_ਖੇਤਰ && flexible_array_member_type_p (ਰੁੱਖ_TYPE (x));
      /* Recursively set TYPE_INCLUDES_FLEXARRAY for the context of x, t
	 when x is an union or record and is the last field.  */
      ਨਹੀਂਤਾਂ ਜੇ (ਰਿਕਾਰਡ_OR_UNION_TYPE_P (ਰੁੱਖ_TYPE (x)))
	TYPE_INCLUDES_FLEXARRAY (t)
	  |= is_ਆਖਰੀ_ਖੇਤਰ && TYPE_INCLUDES_FLEXARRAY (ਰੁੱਖ_TYPE (x));

      ਜੇ (warn_flex_array_member_not_at_ਸਿਰਾ
	  && !is_ਆਖਰੀ_ਖੇਤਰ
	  && ਰਿਕਾਰਡ_OR_UNION_TYPE_P (ਰੁੱਖ_TYPE (x))
	  && TYPE_INCLUDES_FLEXARRAY (ਰੁੱਖ_TYPE (x)))
	warning_at (DECL_ਸਰੋਤ_LOCATION (x),
		    OPT_Wflex_array_member_not_at_ਸਿਰਾ,
		    "structure containing a flexible array member"
		    " is not at the end of another structure");

      ਜੇ (DECL_NAME (x)
	  || ਰਿਕਾਰਡ_OR_UNION_TYPE_P (ਰੁੱਖ_TYPE (x)))
	saw_named_ਖੇਤਰ = ਸੱਚ;

      ਜੇ (AGGREGATE_TYPE_P (ਰੁੱਖ_TYPE (x))
	  && TYPE_TYPELESS_STORAGE (ਰੁੱਖ_TYPE (x)))
	TYPE_TYPELESS_STORAGE (t) = ਸੱਚ;
    }

  detect_ਖੇਤਰ_duplicates (fieldlist);

  /* Now we have the nearly final fieldlist.  Record it,
     then lay out the structure or union (including the fields).  */

  TYPE_FIELDS (t) = fieldlist;

  maybe_apply_pragma_scalar_storage_ਕ੍ਰਮ (t);

  layout_type (t);

  ਜੇ (TYPE_ਮਾਪ_UNIT (t)
      && ਰੁੱਖ_ਕੋਡ (TYPE_ਮਾਪ_UNIT (t)) == INTEGER_CST
      && !ਰੁੱਖ_ਉਛਾਲ (TYPE_ਮਾਪ_UNIT (t))
      && !valid_constant_ਮਾਪ_p (TYPE_ਮਾਪ_UNIT (t)))
    error ("type %qT is too large", t);

  /* Give bit-fields their proper types and rewrite the type of array fields
     with scalar component if the enclosing type has reverse storage order.  */
  ਲਈ (ਰੁੱਖ ਖੇਤਰ_2 = fieldlist; ਖੇਤਰ_2; ਖੇਤਰ_2 = DECL_CHAIN (ਖੇਤਰ_2))
    {
      ਜੇ (ਰੁੱਖ_ਕੋਡ (ਖੇਤਰ_2) == ਖੇਤਰ_DECL
	  && DECL_INITIAL (ਖੇਤਰ_2)
	  && ਰੁੱਖ_TYPE (ਖੇਤਰ_2) != error_mark_ਗੰਢ)
	{
	  ਬਿਨਾਨਿਸ਼ਾਨੀ HOST_WIDE_INT ਚੌੜਾਈ
	    = ਰੁੱਖ_ਮੰਜ਼ਿਲ_uhwi (DECL_INITIAL (ਖੇਤਰ_2));
	  ਰੁੱਖ type = ਰੁੱਖ_TYPE (ਖੇਤਰ_2);
	  ਜੇ (ਸਦਿਸ਼_TYPE_P (type))
	    {
	      error_at (DECL_ਸਰੋਤ_LOCATION (ਖੇਤਰ_2),
			"bit-field %qD has invalid type", ਖੇਤਰ_2);
	      type = ਰੁੱਖ_TYPE (type);
	      ਰੁੱਖ_TYPE (ਖੇਤਰ_2) = type;
	    }
	  ਜੇ (ਚੌੜਾਈ != TYPE_PRECISION (type))
	    {
	      ਜੇ (BITINT_TYPE_P (type)
		  && ਚੌੜਾਈ >= ((TYPE_UNSIGNED (type) || flag_isoc2y) ? 1 : 2))
		ਰੁੱਖ_TYPE (ਖੇਤਰ_2)
		  = build_bitint_type (ਚੌੜਾਈ, TYPE_UNSIGNED (type));
	      ਨਹੀਂਤਾਂ
		ਰੁੱਖ_TYPE (ਖੇਤਰ_2)
		  = c_build_bitfield_integer_type (ਚੌੜਾਈ,
						   TYPE_UNSIGNED (type));
	      ਜੇ (ਰੁੱਖ attr = c_hardbool_type_attr (type))
		decl_ਗੁਣ (&ਰੁੱਖ_TYPE (ਖੇਤਰ_2),
				 copy_list (attr),
				 0, NULL_ਰੁੱਖ);
	      ਸੈੱਟ_DECL_ਬਹੁਲਕ (ਖੇਤਰ_2, TYPE_ਬਹੁਲਕ (ਰੁੱਖ_TYPE (ਖੇਤਰ_2)));
	    }
	  DECL_INITIAL (ਖੇਤਰ_2) = NULL_ਰੁੱਖ;
	}
      ਨਹੀਂਤਾਂ ਜੇ (TYPE_ਉਲਟ_STORAGE_ਕ੍ਰਮ (t)
	       && ਰੁੱਖ_ਕੋਡ (ਖੇਤਰ_2) == ਖੇਤਰ_DECL
	       && ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (ਖੇਤਰ_2)) == ARRAY_TYPE)
	{
	  ਰੁੱਖ ftype = ਰੁੱਖ_TYPE (ਖੇਤਰ_2);
	  ਰੁੱਖ ctype = strip_array_types (ftype);
	  ਜੇ (!ਰਿਕਾਰਡ_OR_UNION_TYPE_P (ctype) && TYPE_ਬਹੁਲਕ (ctype) != QImode)
	    {
	      ਰੁੱਖ fmain_type = TYPE_MAIN_VARIANT (ftype);
	      ਰੁੱਖ *typep = &fmain_type;
	      ਕਰੋ {
		*typep = build_distinct_type_copy (*typep);
		TYPE_ਉਲਟ_STORAGE_ਕ੍ਰਮ (*typep) = 1;
		typep = &ਰੁੱਖ_TYPE (*typep);
	      } ਜਦੋਂ (ਰੁੱਖ_ਕੋਡ (*typep) == ARRAY_TYPE);
	      ਰੁੱਖ_TYPE (ਖੇਤਰ_2)
		= c_build_qualified_type (fmain_type, TYPE_QUALS (ftype));
	    }
	}

      /* Warn on problematic type punning for storage order purposes.  */
      ਜੇ (ਰੁੱਖ_ਕੋਡ (t) == UNION_TYPE
	  && ਰੁੱਖ_ਕੋਡ (ਖੇਤਰ_2) == ਖੇਤਰ_DECL
	  && AGGREGATE_TYPE_P (ਰੁੱਖ_TYPE (ਖੇਤਰ_2)))
	{
	  ਰੁੱਖ ftype = ਰੁੱਖ_TYPE (ਖੇਤਰ_2);
	  ਜੇ (ਰੁੱਖ_ਕੋਡ (ftype) == ARRAY_TYPE)
	    ftype = strip_array_types (ftype);
	  ਜੇ (ਰਿਕਾਰਡ_OR_UNION_TYPE_P (ftype)
	      && TYPE_ਉਲਟ_STORAGE_ਕ੍ਰਮ (ftype)
		 != TYPE_ਉਲਟ_STORAGE_ਕ੍ਰਮ (t))
	    warning_at (DECL_ਸਰੋਤ_LOCATION (ਖੇਤਰ_2),
			OPT_Wscalar_storage_ਕ੍ਰਮ,
			"type punning toggles scalar storage order");
	}
    }

  /* Now we have the truly final field list.
     Store it in this type and in the variants.  */

  TYPE_FIELDS (t) = fieldlist;

  /* If there are lots of fields, sort so we can look through them fast.
     We arbitrarily consider 16 or more elts to be "a lot".  */

  {
    ਪੂਰਨ len = 0;

    ਲਈ (x = fieldlist; x; x = DECL_CHAIN (x))
      {
	ਜੇ (len > 15 || DECL_NAME (x) == ਨਿਰਾ)
	  ਰੋਕੋ;
	len += 1;
      }

    ਜੇ (len > 15)
      {
	ਰੁੱਖ *ਖੇਤਰ_array;
	ਬਣਤਰ lang_type *space;
	ਬਣਤਰ sorted_fields_type *space2;

	len += list_ਲੰਮਾਈ (x);

	/* Use the same allocation policy here that make_node uses, to
	   ensure that this lives as long as the rest of the struct decl.
	   All decls in an inline function need to be saved.  */

	space = ((ਬਣਤਰ lang_type *)
		 ggc_ਅੰਦਰੂਨੀ_cleared_alloc (c_dialect_objc ()
					     ? ਆਕਾਰ (ਬਣਤਰ lang_type)
					     : offsetof (ਬਣਤਰ lang_type,
							 info)));
	space2 = ((sorted_fields_type *)
		  ggc_ਅੰਦਰੂਨੀ_alloc (ਆਕਾਰ (ਬਣਤਰ sorted_fields_type)
				      + len * ਆਕਾਰ (ਰੁੱਖ)));

	len = 0;
	space->s = space2;
	ਖੇਤਰ_array = &space2->elts[0];
	ਲਈ (x = fieldlist; x; x = DECL_CHAIN (x))
	  {
	    ਖੇਤਰ_array[len++] = x;

	    /* If there is anonymous struct or union, break out of the loop.  */
	    ਜੇ (DECL_NAME (x) == ਨਿਰਾ)
	      ਰੋਕੋ;
	  }
	/* Found no anonymous struct/union.  Add the TYPE_LANG_SPECIFIC.  */
	ਜੇ (x == ਨਿਰਾ)
	  {
	    TYPE_LANG_SPECIFIC (t) = space;
	    TYPE_LANG_SPECIFIC (t)->s->len = len;
	    ਖੇਤਰ_array = TYPE_LANG_SPECIFIC (t)->s->elts;
	    qsort (ਖੇਤਰ_array, len, ਆਕਾਰ (ਰੁੱਖ), ਖੇਤਰ_decl_cmp);
	  }
      }
  }

  /* If this was supposed to be a transparent union, but we can't
     make it one, warn and turn off the flag.  */
  ਜੇ (ਰੁੱਖ_ਕੋਡ (t) == UNION_TYPE
      && TYPE_TRANSPARENT_AGGR (t)
      && (!TYPE_FIELDS (t) || TYPE_ਬਹੁਲਕ (t) != DECL_ਬਹੁਲਕ (TYPE_FIELDS (t))))
    {
      TYPE_TRANSPARENT_AGGR (t) = 0;
      warning_at (loc, 0, "union cannot be made transparent");
    }

  ਰੁੱਖ incomplete_vars = C_TYPE_INCOMPLETE_VARS (TYPE_MAIN_VARIANT (t));
  ਲਈ (x = TYPE_MAIN_VARIANT (t); x; x = TYPE_ਅਗਲਾ_VARIANT (x))
    {
      TYPE_FIELDS (x) = TYPE_FIELDS (t);
      TYPE_LANG_SPECIFIC (x) = TYPE_LANG_SPECIFIC (t);
      TYPE_TRANSPARENT_AGGR (x) = TYPE_TRANSPARENT_AGGR (t);
      TYPE_TYPELESS_STORAGE (x) = TYPE_TYPELESS_STORAGE (t);
      C_TYPE_FIELDS_READONLY (x) = C_TYPE_FIELDS_READONLY (t);
      C_TYPE_FIELDS_VOLATILE (x) = C_TYPE_FIELDS_VOLATILE (t);
      C_TYPE_FIELDS_NON_CONSTEXPR (x) = C_TYPE_FIELDS_NON_CONSTEXPR (t);
      C_TYPE_FIELDS_HAS_COUNTED_BY (x) = C_TYPE_FIELDS_HAS_COUNTED_BY (t);
      C_TYPE_VARIABLE_ਮਾਪ (x) = C_TYPE_VARIABLE_ਮਾਪ (t);
      C_TYPE_VARIABLY_MODIFIED (x) = C_TYPE_VARIABLY_MODIFIED (t);
      C_TYPE_INCOMPLETE_VARS (x) = NULL_ਰੁੱਖ;
      TYPE_INCLUDES_FLEXARRAY (x) = TYPE_INCLUDES_FLEXARRAY (t);
    }

  /* Check for consistency with previous definition.  */
  ਜੇ (flag_isoc23 && ਨਿਰਾ != enclosing_struct_parse_info)
    {
      ਰੁੱਖ vistype = ਪਿਛਲਾ_ਟੈਗ (t);
      ਜੇ (vistype
	  && ਰੁੱਖ_ਕੋਡ (vistype) == ਰੁੱਖ_ਕੋਡ (t)
	  && !C_TYPE_BEING_DEFINED (vistype))
	{
	  TYPE_STUB_DECL (t) = TYPE_STUB_DECL (vistype);
	  ਜੇ (c_type_variably_modified_p (t))
	    {
	      error ("redefinition of struct or union %qT with variably "
		     "modified type", t);
	      ਜੇ (struct_parse_info->refloc != UNKNOWN_LOCATION)
		inform (struct_parse_info->refloc, "originally defined here");
	    }
	  ਨਹੀਂਤਾਂ ਜੇ (!comptypes_same_p (t, vistype))
	    {
	      error ("redefinition of struct or union %qT", t);
	      ਜੇ (struct_parse_info->refloc != UNKNOWN_LOCATION)
		inform (struct_parse_info->refloc, "originally defined here");
	    }
	}
    }

  C_TYPE_BEING_DEFINED (t) = 0;

  ਜੇ (lookup_attribute ("may_alias", TYPE_ਗੁਣ (t)))
    ਲਈ (x = TYPE_MAIN_VARIANT (t); x; x = TYPE_ਅਗਲਾ_VARIANT (x))
      c_fixup_may_alias (x);

  /* Set type canonical based on equivalence class.  */
  ਜੇ (flag_isoc23 && !C_TYPE_VARIABLE_ਮਾਪ (t))
    {
      ਜੇ (c_struct_htab == ਨਿਰਾ)
	c_struct_htab = hash_ਸਾਰਣੀ<c_struct_hasher>::create_ggc (61);

      hashval_t hash = c_struct_hasher::hash (t);

      gcc_checking_assert (TYPE_STRUCTURAL_EQUALITY_P (t));
      gcc_checking_assert (!TYPE_NAME (t)
			   || ਰੁੱਖ_ਕੋਡ (TYPE_NAME (t)) == IDENTIFIER_ਗੰਢ);

      ਰੁੱਖ *e = c_struct_htab->ਲੱਭੋ_ਥਾਂ_with_hash (t, hash, ਪਾਓ);
      ਜੇ (*e)
	TYPE_CANONICAL (t) = TYPE_CANONICAL (*e);
      ਨਹੀਂਤਾਂ
	{
	  TYPE_CANONICAL (t) = c_type_canonical (t);
	  *e = t;
	}
      c_update_type_canonical (t);
    }

  /* Update type location to the one of the definition, instead of e.g.
     a forward declaration.  */
  ਜੇ (TYPE_STUB_DECL (t))
    DECL_ਸਰੋਤ_LOCATION (TYPE_STUB_DECL (t)) = loc;

  /* Finish debugging output for this type.  */
  rest_ਦਾ_type_compilation (t, toplevel);

  ਅੰਤ_incomplete_vars (incomplete_vars, toplevel);


  ਜੇ (c_type_variably_modified_p (t))
    {
      c_update_variably_modified (t);
      /* Make sure a DECL_EXPR is created for structs with VLA members.
	 Because we do not know the context, we always pass expr
	 to force creation of a BIND_EXPR which is required in some
	 contexts.  */
      ਜੋੜੋ_decl_ਵਿਅੰਜਕ (loc, t, ਵਿਅੰਜਕ, ਝੂਠ);
    }

  ਜੇ (warn_cxx_compat)
    warn_cxx_compat_ਅੰਤ_struct (fieldlist, ਰੁੱਖ_ਕੋਡ (t), loc);

  ਜੇ (ਨਿਰਾ != enclosing_struct_parse_info)
    {
      ਮਿਟਾਓ struct_parse_info;

      struct_parse_info = enclosing_struct_parse_info;

      /* If this struct is defined inside a struct, add it to
	 struct_types.  */
      ਜੇ (warn_cxx_compat
	  && struct_parse_info != ਨਿਰਾ
	  && !ਵਿੱਚ_sizeof && !ਵਿੱਚ_typeof && !ਵਿੱਚ_alignof && !ਵਿੱਚ_countof)
	struct_parse_info->struct_types.ਸੁਰੱਖਿਅਤ_ਧੱਕੋ (t);
     }

  /* Only when the enclosing struct/union type is not anonymous, do more
     verification on the fields with counted_by attributes.  */
  ਜੇ (C_TYPE_FIELDS_HAS_COUNTED_BY (t) && c_type_ਟੈਗ (t) != NULL_ਰੁੱਖ)
    verify_counted_by_attribute (t, t);

  ਵਾਪਸ t;
}

ਸਥਿਰ ਬਣਤਰ {
  gt_ਸੂਚਕ_operator new_ਮੁੱਲ;
  ਖਾਲੀ *cookie;
} resort_ਅੰਕੜੇ;

/* This routine compares two fields like field_decl_cmp but using the
pointer operator in resort_data.  */

ਸਥਿਰ ਪੂਰਨ
resort_ਖੇਤਰ_decl_cmp (ਅਚਲ ਖਾਲੀ *x_p, ਅਚਲ ਖਾਲੀ *y_p)
{
  ਅਚਲ ਰੁੱਖ *ਅਚਲ x = (ਅਚਲ ਰੁੱਖ *) x_p;
  ਅਚਲ ਰੁੱਖ *ਅਚਲ y = (ਅਚਲ ਰੁੱਖ *) y_p;

  ਜੇ (DECL_NAME (*x) == DECL_NAME (*y))
    /* A nontype is "greater" than a type.  */
    ਵਾਪਸ (ਰੁੱਖ_ਕੋਡ (*y) == TYPE_DECL) - (ਰੁੱਖ_ਕੋਡ (*x) == TYPE_DECL);
  ਜੇ (DECL_NAME (*x) == NULL_ਰੁੱਖ)
    ਵਾਪਸ -1;
  ਜੇ (DECL_NAME (*y) == NULL_ਰੁੱਖ)
    ਵਾਪਸ 1;
  {
    ਰੁੱਖ d1 = DECL_NAME (*x);
    ਰੁੱਖ d2 = DECL_NAME (*y);
    resort_ਅੰਕੜੇ.new_ਮੁੱਲ (&d1, &d1, resort_ਅੰਕੜੇ.cookie);
    resort_ਅੰਕੜੇ.new_ਮੁੱਲ (&d2, &d2, resort_ਅੰਕੜੇ.cookie);
    ਜੇ (d1 < d2)
      ਵਾਪਸ -1;
  }
  ਵਾਪਸ 1;
}

/* Resort DECL_SORTED_FIELDS because pointers have been reordered.  */

ਖਾਲੀ
resort_sorted_fields (ਖਾਲੀ *obj,
		      ਖਾਲੀ * ARG_ਅਣਵਰਤਿਆ (orig_obj),
		      gt_ਸੂਚਕ_operator new_ਮੁੱਲ,
		      ਖਾਲੀ *cookie)
{
  ਬਣਤਰ sorted_fields_type *sf = (ਬਣਤਰ sorted_fields_type *) obj;
  resort_ਅੰਕੜੇ.new_ਮੁੱਲ = new_ਮੁੱਲ;
  resort_ਅੰਕੜੇ.cookie = cookie;
  qsort (&sf->elts[0], sf->len, ਆਕਾਰ (ਰੁੱਖ),
	 resort_ਖੇਤਰ_decl_cmp);
}

/* Lay out the type T, and its element type, and so on.  */

ਸਥਿਰ ਖਾਲੀ
layout_array_type (ਰੁੱਖ t)
{
  ਜੇ (ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (t)) == ARRAY_TYPE)
    layout_array_type (ਰੁੱਖ_TYPE (t));
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

ਰੁੱਖ
ਸ਼ੁਰੂ_enum (location_t loc, ਬਣਤਰ c_enum_contents *the_enum, ਰੁੱਖ name,
	    ਰੁੱਖ fixed_underlying_type, ਤਾਰਕਿਕ potential_nesting_p)
{
  ਰੁੱਖ enumtype = NULL_ਰੁੱਖ;
  location_t enumloc = UNKNOWN_LOCATION;

  /* If this is the real definition for a previous forward reference,
     fill in the contents in the same object that used to be the
     forward reference.  */

  ਜੇ (name != NULL_ਰੁੱਖ)
    enumtype = lookup_ਟੈਗ (ENUMERAL_TYPE, name, ਸੱਚ, &enumloc);

  ਜੇ (enumtype != NULL_ਰੁੱਖ && ਰੁੱਖ_ਕੋਡ (enumtype) == ENUMERAL_TYPE)
    {
      /* If the type is currently being defined or if we have seen an
	 incomplete version which is now complete, this is a nested
	 redefinition.  The later happens if the redefinition occurs
	 inside the enum specifier itself.  */
      ਜੇ (C_TYPE_BEING_DEFINED (enumtype)
	  || (potential_nesting_p && TYPE_ਮੁੱਲਾਂ (enumtype) != NULL_ਰੁੱਖ))
	error_at (loc, "nested redefinition of %<enum %E%>", name);

      /* For C23 we allow redefinitions.  We set to zero and check for
	 consistency later.  */
      ਜੇ (flag_isoc23 && TYPE_ਮੁੱਲਾਂ (enumtype) != NULL_ਰੁੱਖ)
	enumtype = NULL_ਰੁੱਖ;
    }

  ਜੇ (enumtype == NULL_ਰੁੱਖ || ਰੁੱਖ_ਕੋਡ (enumtype) != ENUMERAL_TYPE)
    {
      enumtype = make_ਗੰਢ (ENUMERAL_TYPE);
      TYPE_ਮਾਪ (enumtype) = NULL_ਰੁੱਖ;
      ਸੈੱਟ_TYPE_STRUCTURAL_EQUALITY (enumtype);
      pushtag (loc, name, enumtype);
      ਜੇ (fixed_underlying_type != NULL_ਰੁੱਖ)
	{
	  /* For an enum definition with a fixed underlying type, the
	     type is complete during the definition and the
	     enumeration constants have that type.  If there was a
	     tag, the type was completed in c_parser_enum_specifier.
	     If not, it must be completed here.  */
	  ENUM_FIXED_UNDERLYING_TYPE_P (enumtype) = ਸੱਚ;
	  TYPE_MIN_ਮੁੱਲ (enumtype) = TYPE_MIN_ਮੁੱਲ (fixed_underlying_type);
	  TYPE_MAX_ਮੁੱਲ (enumtype) = TYPE_MAX_ਮੁੱਲ (fixed_underlying_type);
	  TYPE_UNSIGNED (enumtype) = TYPE_UNSIGNED (fixed_underlying_type);
	  ਸੈੱਟ_TYPE_ALIGN (enumtype, TYPE_ALIGN (fixed_underlying_type));
	  TYPE_ਮਾਪ (enumtype) = NULL_ਰੁੱਖ;
	  TYPE_PRECISION (enumtype) = TYPE_PRECISION (fixed_underlying_type);
	  ENUM_UNDERLYING_TYPE (enumtype) = fixed_underlying_type;
	  TYPE_CANONICAL (enumtype) = TYPE_CANONICAL (fixed_underlying_type);
	  c_update_type_canonical (enumtype);
	  layout_type (enumtype);
	}
    }
  /* Update type location to the one of the definition, instead of e.g.
     a forward declaration.  */
  ਨਹੀਂਤਾਂ ਜੇ (TYPE_STUB_DECL (enumtype))
    {
      enumloc = DECL_ਸਰੋਤ_LOCATION (TYPE_STUB_DECL (enumtype));
      DECL_ਸਰੋਤ_LOCATION (TYPE_STUB_DECL (enumtype)) = loc;
    }

  C_TYPE_BEING_DEFINED (enumtype) = 1;

  ਜੇ (TYPE_ਮੁੱਲਾਂ (enumtype) != NULL_ਰੁੱਖ)
    {
      /* This enum is a named one that has been declared already.  */
      auto_diagnostic_ਸਮੂਹ d;
      error_at (loc, "redeclaration of %<enum %E%>", name);
      ਜੇ (enumloc != UNKNOWN_LOCATION)
	inform (enumloc, "originally defined here");

      /* Completely replace its old definition.
	 The old enumerators remain defined, however.  */
      TYPE_ਮੁੱਲਾਂ (enumtype) = NULL_ਰੁੱਖ;
    }

  ਜੇ (ENUM_FIXED_UNDERLYING_TYPE_P (enumtype)
      && fixed_underlying_type == NULL_ਰੁੱਖ)
    {
      error_at (loc, "%<enum%> declared with but defined without "
		"fixed underlying type");
      ENUM_FIXED_UNDERLYING_TYPE_P (enumtype) = ਝੂਠ;
    }

  the_enum->enum_ਅਗਲਾ_ਮੁੱਲ = integer_zero_ਗੰਢ;
  the_enum->enum_type = enumtype;
  the_enum->enum_ਉਛਾਲ = 0;

  ਜੇ (flag_short_enums && !ENUM_FIXED_UNDERLYING_TYPE_P (enumtype))
    ਲਈ (ਰੁੱਖ v = TYPE_MAIN_VARIANT (enumtype); v; v = TYPE_ਅਗਲਾ_VARIANT (v))
      TYPE_PACKED (v) = 1;

  /* FIXME: This will issue a warning for a use of a type defined
     within sizeof in a statement expr.  This is not terribly serious
     as C++ doesn't permit statement exprs within sizeof anyhow.  */
  ਜੇ (warn_cxx_compat
      && (ਵਿੱਚ_sizeof || ਵਿੱਚ_typeof || ਵਿੱਚ_alignof || ਵਿੱਚ_countof))
    warning_at (loc, OPT_Wc___compat,
		"defining type in %qs expression is invalid in C++",
		(ਵਿੱਚ_sizeof ? "sizeof"
		 : ਵਿੱਚ_typeof ? "typeof"
		 : ਵਿੱਚ_alignof ? "alignof"
		 : "_Countof"));

  ਜੇ (ਵਿੱਚ_underspecified_init)
    error_at (loc, "%qT defined in underspecified object initializer",
	      enumtype);

  ਵਾਪਸ enumtype;
}

/* After processing and defining all the values of an enumeration type,
   install their decls in the enumeration type and finish it off.
   ENUMTYPE is the type object, VALUES a list of decl-value pairs,
   and ATTRIBUTES are the specified attributes.
   Returns ENUMTYPE.  */

ਰੁੱਖ
ਅੰਤ_enum (ਰੁੱਖ enumtype, ਰੁੱਖ ਮੁੱਲਾਂ, ਰੁੱਖ ਗੁਣ)
{
  ਰੁੱਖ pair, tem;
  ਰੁੱਖ minnode = NULL_ਰੁੱਖ, maxnode = NULL_ਰੁੱਖ;
  ਪੂਰਨ precision;
  signop sign;
  ਤਾਰਕਿਕ toplevel = (file_scope == current_scope);
  ਬਣਤਰ lang_type *lt;

  decl_ਗੁਣ (&enumtype, ਗੁਣ, (ਪੂਰਨ) ATTR_FLAG_TYPE_ਵਿੱਚ_ਰੱਖੋ);

  /* Calculate the maximum value of any enumerator in this type.  */

  ਜੇ (ਮੁੱਲਾਂ == error_mark_ਗੰਢ)
    minnode = maxnode = integer_zero_ਗੰਢ;
  ਨਹੀਂਤਾਂ
    {
      minnode = maxnode = ਰੁੱਖ_ਮੁੱਲ (ਮੁੱਲਾਂ);
      ਲਈ (pair = ਰੁੱਖ_CHAIN (ਮੁੱਲਾਂ); pair; pair = ਰੁੱਖ_CHAIN (pair))
	{
	  ਰੁੱਖ ਮੁੱਲ = ਰੁੱਖ_ਮੁੱਲ (pair);
	  ਜੇ (ਰੁੱਖ_int_cst_lt (maxnode, ਮੁੱਲ))
	    maxnode = ਮੁੱਲ;
	  ਜੇ (ਰੁੱਖ_int_cst_lt (ਮੁੱਲ, minnode))
	    minnode = ਮੁੱਲ;
	}
    }

  /* Construct the final type of this enumeration.  It is the same
     as one of the integral types - the narrowest one that fits, except
     that normally we only go as narrow as int - and signed iff any of
     the values are negative.  */
  sign = (ਰੁੱਖ_int_cst_sgn (minnode) >= 0) ? UNSIGNED : SIGNED;
  precision = MAX (ਰੁੱਖ_int_cst_min_precision (minnode, sign),
		   ਰੁੱਖ_int_cst_min_precision (maxnode, sign));

  ਤਾਰਕਿਕ wider_than_int =
    (ਰੁੱਖ_int_cst_lt (minnode, TYPE_MIN_ਮੁੱਲ (integer_type_ਗੰਢ))
     || ਰੁੱਖ_int_cst_lt (TYPE_MAX_ਮੁੱਲ (integer_type_ਗੰਢ), maxnode));


  ਜੇ (!ENUM_FIXED_UNDERLYING_TYPE_P (enumtype))
    {
      /* If the precision of the type was specified with an attribute and it
	 was too small, give an error.  Otherwise, use it.  */
      ਜੇ (TYPE_PRECISION (enumtype) && lookup_attribute ("mode", ਗੁਣ))
	{
	  ਜੇ (precision > TYPE_PRECISION (enumtype))
	    {
	      TYPE_PRECISION (enumtype) = 0;
	      error ("specified mode too small for enumerated values");
	    }
	  ਨਹੀਂਤਾਂ
	    precision = TYPE_PRECISION (enumtype);
	}
      ਨਹੀਂਤਾਂ
	TYPE_PRECISION (enumtype) = 0;

      ਜੇ (TYPE_PACKED (enumtype)
	  || precision > TYPE_PRECISION (integer_type_ਗੰਢ)
	  || TYPE_PRECISION (enumtype))
	{
	  tem = c_common_type_for_ਮਾਪ (precision, sign == UNSIGNED ? 1 : 0);
	  ਜੇ (tem == ਨਿਰਾ)
	    {
	      /* This should only occur when both signed and unsigned
		 values of maximum precision occur among the
		 enumerators.  */
	      pedwarn (ਨਿਵੇਸ਼_location, 0,
		       "enumeration values exceed range of largest integer");
	      tem = widest_integer_literal_type_ਗੰਢ;
	    }
	  ਨਹੀਂਤਾਂ ਜੇ (precision > TYPE_PRECISION (intmax_type_ਗੰਢ)
		   && !ਰੁੱਖ_int_cst_lt (minnode,
					TYPE_MIN_ਮੁੱਲ (intmax_type_ਗੰਢ))
		   && !ਰੁੱਖ_int_cst_lt (TYPE_MAX_ਮੁੱਲ (uintmax_type_ਗੰਢ),
					maxnode))
	    pedwarn (ਨਿਵੇਸ਼_location, OPT_Wpedantic,
		     "enumeration values exceed range of %qs",
		     sign == UNSIGNED ? "uintmax_t" : "intmax_t");
	}
      ਨਹੀਂਤਾਂ
	tem = sign == UNSIGNED ? unsigned_type_ਗੰਢ : integer_type_ਗੰਢ;

      TYPE_MIN_ਮੁੱਲ (enumtype) = TYPE_MIN_ਮੁੱਲ (tem);
      TYPE_MAX_ਮੁੱਲ (enumtype) = TYPE_MAX_ਮੁੱਲ (tem);
      TYPE_UNSIGNED (enumtype) = TYPE_UNSIGNED (tem);
      ਸੈੱਟ_TYPE_ALIGN (enumtype, TYPE_ALIGN (tem));
      TYPE_ਮਾਪ (enumtype) = NULL_ਰੁੱਖ;
      TYPE_PRECISION (enumtype) = TYPE_PRECISION (tem);
      ENUM_UNDERLYING_TYPE (enumtype) =
	c_common_type_for_ਮਾਪ (TYPE_PRECISION (tem), TYPE_UNSIGNED (tem));

      TYPE_CANONICAL (enumtype) =
	TYPE_CANONICAL (ENUM_UNDERLYING_TYPE (enumtype));
      c_update_type_canonical (enumtype);

      layout_type (enumtype);
    }

  ਜੇ (ਮੁੱਲਾਂ != error_mark_ਗੰਢ)
    {
      /* Change the type of the enumerators to be the enum type.  We
	 need to do this irrespective of the size of the enum, for
	 proper type checking.  Replace the DECL_INITIALs of the
	 enumerators, and the value slots of the list, with copies
	 that have the enum type; they cannot be modified in place
	 because they may be shared (e.g.  integer_zero_node) Finally,
	 change the purpose slots to point to the names of the decls.  */
      ਲਈ (pair = ਮੁੱਲਾਂ; pair; pair = ਰੁੱਖ_CHAIN (pair))
	{
	  ਰੁੱਖ enu = ਰੁੱਖ_PURPOSE (pair);
	  ਰੁੱਖ ini = DECL_INITIAL (enu);

	  ਰੁੱਖ_TYPE (enu) = enumtype;

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
	  ਜੇ (!ENUM_FIXED_UNDERLYING_TYPE_P (enumtype) && wider_than_int)
	    ini = convert (enumtype, ini);

	  DECL_INITIAL (enu) = ini;
	  ਰੁੱਖ_PURPOSE (pair) = DECL_NAME (enu);
	  /* To match the C++ FE, store the CONST_DECL rather than just its
	     value.  */
	  ਰੁੱਖ_ਮੁੱਲ (pair) = enu;
	}

      TYPE_ਮੁੱਲਾਂ (enumtype) = ਮੁੱਲਾਂ;
    }

  /* Record the min/max values so that we can warn about bit-field
     enumerations that are too small for the values.  */
  lt = ((ਬਣਤਰ lang_type *)
	ggc_ਅੰਦਰੂਨੀ_cleared_alloc (c_dialect_objc ()
				    ? ਆਕਾਰ (ਬਣਤਰ lang_type)
				    : offsetof (ਬਣਤਰ lang_type, info)));
  lt->enum_min = minnode;
  lt->enum_max = maxnode;
  TYPE_LANG_SPECIFIC (enumtype) = lt;

  /* Fix up all variant types of this enum type.  */
  ਰੁੱਖ incomplete_vars = C_TYPE_INCOMPLETE_VARS (TYPE_MAIN_VARIANT (enumtype));
  ਲਈ (tem = TYPE_MAIN_VARIANT (enumtype); tem; tem = TYPE_ਅਗਲਾ_VARIANT (tem))
    {
      C_TYPE_INCOMPLETE_VARS (tem) = NULL_ਰੁੱਖ;
      ਜੇ (tem == enumtype)
	ਜਾਰੀ;
      TYPE_ਮੁੱਲਾਂ (tem) = TYPE_ਮੁੱਲਾਂ (enumtype);
      TYPE_MIN_ਮੁੱਲ (tem) = TYPE_MIN_ਮੁੱਲ (enumtype);
      TYPE_MAX_ਮੁੱਲ (tem) = TYPE_MAX_ਮੁੱਲ (enumtype);
      TYPE_ਮਾਪ (tem) = TYPE_ਮਾਪ (enumtype);
      TYPE_ਮਾਪ_UNIT (tem) = TYPE_ਮਾਪ_UNIT (enumtype);
      ਸੈੱਟ_TYPE_ਬਹੁਲਕ (tem, TYPE_ਬਹੁਲਕ (enumtype));
      TYPE_PRECISION (tem) = TYPE_PRECISION (enumtype);
      ਸੈੱਟ_TYPE_ALIGN (tem, TYPE_ALIGN (enumtype));
      TYPE_USER_ALIGN (tem) = TYPE_USER_ALIGN (enumtype);
      TYPE_UNSIGNED (tem) = TYPE_UNSIGNED (enumtype);
      TYPE_LANG_SPECIFIC (tem) = TYPE_LANG_SPECIFIC (enumtype);
      ENUM_UNDERLYING_TYPE (tem) = ENUM_UNDERLYING_TYPE (enumtype);
      TYPE_PACKED (tem) = TYPE_PACKED (enumtype);
    }

  /* Finish debugging output for this type.  */
  rest_ਦਾ_type_compilation (enumtype, toplevel);

  ਅੰਤ_incomplete_vars (incomplete_vars, toplevel);

  /* If this enum is defined inside a struct, add it to
     struct_types.  */
  ਜੇ (warn_cxx_compat
      && struct_parse_info != ਨਿਰਾ
      && !ਵਿੱਚ_sizeof && !ਵਿੱਚ_typeof && !ਵਿੱਚ_alignof && !ਵਿੱਚ_countof)
    struct_parse_info->struct_types.ਸੁਰੱਖਿਅਤ_ਧੱਕੋ (enumtype);

  /* Check for consistency with previous definition */
  ਜੇ (flag_isoc23)
    {
      ਰੁੱਖ vistype = ਪਿਛਲਾ_ਟੈਗ (enumtype);
      ਜੇ (vistype
	  && ਰੁੱਖ_ਕੋਡ (vistype) == ਰੁੱਖ_ਕੋਡ (enumtype)
	  && !C_TYPE_BEING_DEFINED (vistype))
	{
	  TYPE_STUB_DECL (enumtype) = TYPE_STUB_DECL (vistype);
	  ਜੇ (!comptypes_same_p (enumtype, vistype))
	    error("conflicting redefinition of enum %qT", enumtype);
	}
    }

  C_TYPE_BEING_DEFINED (enumtype) = 0;

  ਵਾਪਸ enumtype;
}

/* Build and install a CONST_DECL for one value of the
   current enumeration type (one that was begun with start_enum).
   DECL_LOC is the location of the enumerator.
   LOC is the location of the '=' operator if any, DECL_LOC otherwise.
   Return a tree-list containing the CONST_DECL and its value.
   Assignment of sequential values by default is handled here.  */

ਰੁੱਖ
build_enumerator (location_t decl_loc, location_t loc,
		  ਬਣਤਰ c_enum_contents *the_enum, ਰੁੱਖ name, ਰੁੱਖ ਮੁੱਲ)
{
  ਰੁੱਖ decl;
  ਰੁੱਖ old_decl;

  /* Validate and default VALUE.  */

  ਜੇ (ਮੁੱਲ != NULL_ਰੁੱਖ)
    {
      /* Don't issue more errors for error_mark_node (i.e. an
	 undeclared identifier) - just ignore the value expression.  */
      ਜੇ (ਮੁੱਲ == error_mark_ਗੰਢ)
	ਮੁੱਲ = NULL_ਰੁੱਖ;
      ਨਹੀਂਤਾਂ ਜੇ (!INTEGRAL_TYPE_P (ਰੁੱਖ_TYPE (ਮੁੱਲ)))
	{
	  error_at (loc, "enumerator value for %qE is not an integer constant",
		    name);
	  ਮੁੱਲ = NULL_ਰੁੱਖ;
	}
      ਨਹੀਂਤਾਂ
	{
	  ਜੇ (ਰੁੱਖ_ਕੋਡ (ਮੁੱਲ) != INTEGER_CST)
	    {
	      ਮੁੱਲ = c_fully_fold (ਮੁੱਲ, ਝੂਠ, ਨਿਰਾ);
	      ਜੇ (ਰੁੱਖ_ਕੋਡ (ਮੁੱਲ) == INTEGER_CST)
		pedwarn (loc, OPT_Wpedantic,
			 "enumerator value for %qE is not an integer "
			 "constant expression", name);
	    }
	  ਜੇ (ਰੁੱਖ_ਕੋਡ (ਮੁੱਲ) != INTEGER_CST)
	    {
	      error ("enumerator value for %qE is not an integer constant",
		     name);
	      ਮੁੱਲ = NULL_ਰੁੱਖ;
	    }
	  ਨਹੀਂਤਾਂ
	    {
	      ਮੁੱਲ = default_conversion (ਮੁੱਲ);
	      constant_ਵਿਅੰਜਕ_warning (ਮੁੱਲ);
	    }
	}
    }

  /* Default based on previous value.  */
  /* It should no longer be possible to have NON_LVALUE_EXPR
     in the default.  */
  ਜੇ (ਮੁੱਲ == NULL_ਰੁੱਖ)
    {
      ਮੁੱਲ = the_enum->enum_ਅਗਲਾ_ਮੁੱਲ;
      ਜੇ (the_enum->enum_ਉਛਾਲ)
	error_at (loc, "overflow in enumeration values");
    }
  ਜੇ (ENUM_FIXED_UNDERLYING_TYPE_P (the_enum->enum_type))
    {
      /* Enumeration constants must fit in the fixed underlying type.  */
      ਜੇ (!int_ਸਮਾਉਂਦਾ_type_p (ਮੁੱਲ, ENUM_UNDERLYING_TYPE (the_enum->enum_type)))
	error_at (loc,
		  "enumerator value outside the range of underlying type");
      /* Enumeration constants for an enum with fixed underlying type
	 have the enum type, both inside and outside the
	 definition.  */
      ਮੁੱਲ = convert (the_enum->enum_type, ਮੁੱਲ);
    }
  ਨਹੀਂਤਾਂ ਜੇ (flag_isoc23
	   && (old_decl = lookup_name_ਵਿੱਚ_scope (name, current_scope))
	   && old_decl != error_mark_ਗੰਢ
	   && ਰੁੱਖ_TYPE (old_decl)
	   && ਰੁੱਖ_TYPE (ਰੁੱਖ_TYPE (old_decl))
	   && ਰੁੱਖ_ਕੋਡ (old_decl) == CONST_DECL)
    {
      /* Enumeration constants in a redeclaration have the previous type.  */
      ਰੁੱਖ ਪਿਛਲਾ_type = ਰੁੱਖ_TYPE (DECL_INITIAL (old_decl));
      ਜੇ (!int_ਸਮਾਉਂਦਾ_type_p (ਮੁੱਲ, ਪਿਛਲਾ_type))
	{
	  error_at (loc, "value of redeclared enumerator outside the range "
			 "of %qT", ਪਿਛਲਾ_type);
	  locate_old_decl (old_decl);
	}
      ਮੁੱਲ = convert (ਪਿਛਲਾ_type, ਮੁੱਲ);
    }
  ਨਹੀਂਤਾਂ
    {
      /* Even though the underlying type of an enum is unspecified, the
	 type of enumeration constants is explicitly defined as int
	 (6.4.4.3/2 in the C99 Standard).  C23 allows any integer type, and
	 GCC allows such types for older standards as an extension.  */
      ਤਾਰਕਿਕ warned_range = ਝੂਠ;
      ਜੇ (!int_ਸਮਾਉਂਦਾ_type_p (ਮੁੱਲ,
			    (TYPE_UNSIGNED (ਰੁੱਖ_TYPE (ਮੁੱਲ))
			     ? uintmax_type_ਗੰਢ
			     : intmax_type_ਗੰਢ)))
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
				TYPE_UNSIGNED (ਰੁੱਖ_TYPE (ਮੁੱਲ))
				? "uintmax_t"
				: "intmax_t");
      ਜੇ (!warned_range && !int_ਸਮਾਉਂਦਾ_type_p (ਮੁੱਲ, integer_type_ਗੰਢ))
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
      ਜੇ (int_ਸਮਾਉਂਦਾ_type_p (ਮੁੱਲ, integer_type_ਗੰਢ))
	ਮੁੱਲ = convert (integer_type_ਗੰਢ, ਮੁੱਲ);
    }

  /* Set basis for default for next value.  */
  ਜੇ (ENUM_FIXED_UNDERLYING_TYPE_P (the_enum->enum_type))
    {
      ਰੁੱਖ underlying_type = ENUM_UNDERLYING_TYPE (the_enum->enum_type);
      ਜੇ (ਰੁੱਖ_ਕੋਡ (underlying_type) == BOOLEAN_TYPE)
	/* A value of 2 following a value of 1 overflows bool, but we
	   cannot carry out addition directly on bool without
	   promotion, and converting the result of arithmetic in a
	   wider type back to bool would not produce the right result
	   for this overflow check.  */
	the_enum->enum_ਅਗਲਾ_ਮੁੱਲ = invert_truthvalue_loc (loc, ਮੁੱਲ);
      ਨਹੀਂਤਾਂ
	the_enum->enum_ਅਗਲਾ_ਮੁੱਲ
	  = build_ਦੁਆਧਾਰੀ_op (ਵਿਅੰਜਕ_LOC_OR_LOC (ਮੁੱਲ, ਨਿਵੇਸ਼_location),
			     PLUS_ਵਿਅੰਜਕ, convert (underlying_type, ਮੁੱਲ),
			     convert (underlying_type, integer_one_ਗੰਢ),
			     ਝੂਠ);
    }
  ਨਹੀਂਤਾਂ
    {
      /* In a redeclaration the type can already be the enumeral type.  */
      ਜੇ (ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (ਮੁੱਲ)) == ENUMERAL_TYPE)
	ਮੁੱਲ = convert (ENUM_UNDERLYING_TYPE (ਰੁੱਖ_TYPE (ਮੁੱਲ)), ਮੁੱਲ);
      the_enum->enum_ਅਗਲਾ_ਮੁੱਲ
	= build_ਦੁਆਧਾਰੀ_op (ਵਿਅੰਜਕ_LOC_OR_LOC (ਮੁੱਲ, ਨਿਵੇਸ਼_location),
			   PLUS_ਵਿਅੰਜਕ, ਮੁੱਲ, integer_one_ਗੰਢ, ਝੂਠ);
    }
  the_enum->enum_ਉਛਾਲ = ਰੁੱਖ_int_cst_lt (the_enum->enum_ਅਗਲਾ_ਮੁੱਲ, ਮੁੱਲ);
  ਜੇ (the_enum->enum_ਉਛਾਲ
      && !ENUM_FIXED_UNDERLYING_TYPE_P (the_enum->enum_type))
    {
      /* Choose a wider type with the same signedness if
	 available.  */
      ਪੂਰਨ prec = TYPE_PRECISION (ਰੁੱਖ_TYPE (ਮੁੱਲ)) + 1;
      ਤਾਰਕਿਕ unsignedp = TYPE_UNSIGNED (ਰੁੱਖ_TYPE (ਮੁੱਲ));
      ਰੁੱਖ new_type = (unsignedp
		       ? long_unsigned_type_ਗੰਢ
		       : long_integer_type_ਗੰਢ);
      ਜੇ (prec > TYPE_PRECISION (new_type))
	new_type = (unsignedp
		    ? long_long_unsigned_type_ਗੰਢ
		    : long_long_integer_type_ਗੰਢ);
      ਜੇ (prec > TYPE_PRECISION (new_type))
	new_type = (unsignedp
		    ? widest_unsigned_literal_type_ਗੰਢ
		    : widest_integer_literal_type_ਗੰਢ);
      ਜੇ (prec <= TYPE_PRECISION (new_type))
	{
	  the_enum->enum_ਉਛਾਲ = ਝੂਠ;
	  the_enum->enum_ਅਗਲਾ_ਮੁੱਲ
	    = build_ਦੁਆਧਾਰੀ_op (ਵਿਅੰਜਕ_LOC_OR_LOC (ਮੁੱਲ, ਨਿਵੇਸ਼_location),
			       PLUS_ਵਿਅੰਜਕ, convert (new_type, ਮੁੱਲ),
			       integer_one_ਗੰਢ, ਝੂਠ);
	  gcc_assert (!ਰੁੱਖ_int_cst_lt (the_enum->enum_ਅਗਲਾ_ਮੁੱਲ, ਮੁੱਲ));
	}
    }

  /* Now create a declaration for the enum value name.  */

  decl = build_decl (decl_loc, CONST_DECL, name, ਰੁੱਖ_TYPE (ਮੁੱਲ));
  DECL_INITIAL (decl) = ਮੁੱਲ;
  DECL_CONTEXT (decl) = the_enum->enum_type;
  pushdecl (decl);

  ਵਾਪਸ ਰੁੱਖ_cons (decl, ਮੁੱਲ, NULL_ਰੁੱਖ);
}

/* Implement LANG_HOOKS_SIMULATE_ENUM_DECL.  */

ਰੁੱਖ
c_simulate_enum_decl (location_t loc, ਅਚਲ ਅੱਖਰ *name,
		      vec<string_int_pair> *ਮੁੱਲਾਂ_ptr)
{
  location_t saved_loc = ਨਿਵੇਸ਼_location;
  ਨਿਵੇਸ਼_location = loc;

  ਬਣਤਰ c_enum_contents the_enum;
  ਰੁੱਖ enumtype = ਸ਼ੁਰੂ_enum (loc, &the_enum, get_identifier (name),
			      NULL_ਰੁੱਖ, ਝੂਠ);

  ਰੁੱਖ ਮੁੱਲ_chain = NULL_ਰੁੱਖ;
  string_int_pair *ਮੁੱਲ;
  vec<string_int_pair> ਮੁੱਲਾਂ = *ਮੁੱਲਾਂ_ptr;
  ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ i;
  FOR_EACH_VEC_ELT (ਮੁੱਲਾਂ, i, ਮੁੱਲ)
    {
      ਰੁੱਖ decl = build_enumerator (loc, loc, &the_enum,
				    get_identifier (ਮੁੱਲ->ਪਹਿਲਾ),
				    build_int_cst (integer_type_ਗੰਢ,
						   ਮੁੱਲ->ਦੂਜਾ));
      ਰੁੱਖ_CHAIN (decl) = ਮੁੱਲ_chain;
      ਮੁੱਲ_chain = decl;
    }

  ਅੰਤ_enum (enumtype, nreverse (ਮੁੱਲ_chain), NULL_ਰੁੱਖ);

  ਨਿਵੇਸ਼_location = saved_loc;
  ਵਾਪਸ enumtype;
}

/* Implement LANG_HOOKS_SIMULATE_RECORD_DECL.  */

ਰੁੱਖ
c_simulate_ਰਿਕਾਰਡ_decl (location_t loc, ਅਚਲ ਅੱਖਰ *name,
			array_ਟੁਕੜਾ<ਅਚਲ ਰੁੱਖ> fields)
{
  location_t saved_loc = ਨਿਵੇਸ਼_location;
  ਨਿਵੇਸ਼_location = loc;

  ਵਰਗ c_struct_parse_info *struct_info;
  ਰੁੱਖ ident = get_identifier (name);
  ਰੁੱਖ type = ਸ਼ੁਰੂ_struct (loc, ਰਿਕਾਰਡ_TYPE, ident, &struct_info);

  ਲਈ (ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ i = 0; i < fields.ਮਾਪ (); ++i)
    {
      DECL_ਖੇਤਰ_CONTEXT (fields[i]) = type;
      ਜੇ (i > 0)
	DECL_CHAIN (fields[i - 1]) = fields[i];
    }

  ਅੰਤ_struct (loc, type, fields[0], NULL_ਰੁੱਖ, struct_info);

  ਰੁੱਖ decl = build_decl (loc, TYPE_DECL, ident, type);
  ਸੈੱਟ_underlying_type (decl);
  lang_hooks.decls.pushdecl (decl);

  ਨਿਵੇਸ਼_location = saved_loc;
  ਵਾਪਸ type;
}

/* Create the FUNCTION_DECL for a function definition.
   DECLSPECS, DECLARATOR and ATTRIBUTES are the parts of
   the declaration; they describe the function's name and the type it returns,
   but twisted together in a fashion that parallels the syntax of C.

   This function creates a binding context for the function body
   as well as setting up the FUNCTION_DECL in current_function_decl.

   Returns true on success.  If the DECLARATOR is not suitable for a function
   (it defines a datum instead), we return false to report a parse error.  */

ਤਾਰਕਿਕ
ਸ਼ੁਰੂ_function (ਬਣਤਰ c_declspecs *declspecs, ਬਣਤਰ c_declarator *declarator,
		ਰੁੱਖ ਗੁਣ)
{
  ਰੁੱਖ decl1, old_decl;
  ਰੁੱਖ restype, resdecl;
  location_t loc;
  location_t ਨਤੀਜਾ_loc;
  ਰੁੱਖ ਵਿਅੰਜਕ = ਨਿਰਾ;

  current_function_returns_ਮੁੱਲ = 0;  /* Assume, until we see it does.  */
  current_function_returns_null = 0;
  current_function_returns_abnormally = 0;
  warn_about_return_type = 0;
  c_switch_ਢੇਰ = ਨਿਰਾ;

  /* Indicate no valid break/continue context.  */
  ਵਿੱਚ_statement = 0;

  decl1 = grokdeclarator (declarator, declspecs, FUNCDEF, ਸੱਚ, ਨਿਰਾ,
			  &ਗੁਣ, &ਵਿਅੰਜਕ, ਨਿਰਾ, DEPRECATED_ਸਾਧਾਰਨ);
  invoke_plugin_callbacks (PLUGIN_ਸ਼ੁਰੂ_PARSE_FUNCTION, decl1);

  /* If the declarator is not suitable for a function definition,
     cause a syntax error.  */
  ਜੇ (decl1 == NULL_ਰੁੱਖ
      || ਰੁੱਖ_ਕੋਡ (decl1) != FUNCTION_DECL)
    ਵਾਪਸ ਝੂਠ;

  /* Nested functions may have variably modified (return) type.
     Make sure the size expression is evaluated at this point.  */
  ਜੇ (ਵਿਅੰਜਕ && !current_scope->parm_flag)
    ਜੋੜੋ_stmt (fold_convert (void_type_ਗੰਢ, ਵਿਅੰਜਕ));

  loc = DECL_ਸਰੋਤ_LOCATION (decl1);

  /* A nested function is not global.  */
  ਜੇ (current_function_decl != NULL_ਰੁੱਖ)
    ਰੁੱਖ_ਜਨਤਕ (decl1) = 0;

  c_decl_ਗੁਣ (&decl1, ਗੁਣ, 0);

  ਜੇ (DECL_DECLARED_INLINE_P (decl1)
      && DECL_UNINLINABLE (decl1)
      && lookup_attribute ("noinline", DECL_ਗੁਣ (decl1)))
    {
      auto_urlify_ਗੁਣ sentinel;
      warning_at (loc, OPT_Wattributes,
		  "inline function %qD given attribute %qs",
		  decl1, "noinline");
    }

  /* Handle gnu_inline attribute.  */
  ਜੇ (declspecs->inline_p
      && !flag_gnu89_inline
      && ਰੁੱਖ_ਕੋਡ (decl1) == FUNCTION_DECL
      && (lookup_attribute ("gnu_inline", DECL_ਗੁਣ (decl1))
	  || current_function_decl))
    {
      ਜੇ (declspecs->storage_class != csc_static)
	DECL_EXTERNAL (decl1) = !DECL_EXTERNAL (decl1);
    }

  announce_function (decl1);

  ਜੇ (!COMPLETE_OR_VOID_TYPE_P (ਰੁੱਖ_TYPE (ਰੁੱਖ_TYPE (decl1))))
    {
      error_at (loc, "return type is an incomplete type");
      /* Make it return void instead.  */
      ਰੁੱਖ_TYPE (decl1)
	= c_build_function_type (void_type_ਗੰਢ,
				 TYPE_ARG_TYPES (ਰੁੱਖ_TYPE (decl1)),
				 TYPE_NO_NAMED_ਦਲੀਲਾਂ_STDARG_P (ਰੁੱਖ_TYPE (decl1)));
    }

  ਜੇ (warn_about_return_type)
    permerror_opt (loc, flag_isoc99 ? OPT_Wimplicit_int
		   : (warn_return_type > 0 ? OPT_Wreturn_type
		      : OPT_Wimplicit_int),
		   "return type defaults to %<int%>");

  /* Make the init_value nonzero so pushdecl knows this is not tentative.
     error_mark_node is replaced below (in pop_scope) with the BLOCK.  */
  DECL_INITIAL (decl1) = error_mark_ਗੰਢ;

  /* If this definition isn't a prototype and we had a prototype declaration
     before, copy the arg type info from that prototype.  */
  old_decl = lookup_name_ਵਿੱਚ_scope (DECL_NAME (decl1), current_scope);
  ਜੇ (old_decl && ਰੁੱਖ_ਕੋਡ (old_decl) != FUNCTION_DECL)
    old_decl = NULL_ਰੁੱਖ;

  current_function_prototype_locus = UNKNOWN_LOCATION;
  current_function_prototype_built_ਵਿੱਚ = ਝੂਠ;
  current_function_prototype_arg_types = NULL_ਰੁੱਖ;
  ਰੁੱਖ newtype = ਰੁੱਖ_TYPE (decl1);
  ਰੁੱਖ oldtype = old_decl ? ਰੁੱਖ_TYPE (old_decl) : newtype;
  ਜੇ (!prototype_p (newtype))
    {
      ਰੁੱਖ oldrt = ਰੁੱਖ_TYPE (oldtype);
      ਰੁੱਖ newrt = ਰੁੱਖ_TYPE (newtype);
      ਜੇ (old_decl != NULL_ਰੁੱਖ
	  && ਰੁੱਖ_ਕੋਡ (oldtype) == FUNCTION_TYPE
	  && comptypes (oldrt, newrt)
	  && !TYPE_NO_NAMED_ਦਲੀਲਾਂ_STDARG_P (oldtype))
	{
	  ਜੇ (stdarg_p (oldtype))
	    {
	      auto_diagnostic_ਸਮੂਹ d;
	      warning_at (loc, 0, "%q+D defined as variadic function "
			  "without prototype", decl1);
	      locate_old_decl (old_decl);
	    }
	  ਰੁੱਖ_TYPE (decl1) = ਸੰਯੁਕਤ_type (oldtype, newtype);
	  current_function_prototype_locus = DECL_ਸਰੋਤ_LOCATION (old_decl);
	  current_function_prototype_built_ਵਿੱਚ
	    = C_DECL_BUILTIN_PROTOTYPE (old_decl);
	  current_function_prototype_arg_types
	    = TYPE_ARG_TYPES (newtype);
	}
      ਜੇ (ਰੁੱਖ_ਜਨਤਕ (decl1))
	{
	  /* If there is an external prototype declaration of this
	     function, record its location but do not copy information
	     to this decl.  This may be an invisible declaration
	     (built-in or in a scope which has finished) or simply
	     have more refined argument types than any declaration
	     found above.  */
	  ਬਣਤਰ c_binding *b;
	  ਲਈ (b = I_ਚਿੰਨ੍ਹ_BINDING (DECL_NAME (decl1)); b; b = b->shadowed)
	    ਜੇ (B_ਵਿੱਚ_SCOPE (b, external_scope))
	      ਰੋਕੋ;
	  ਜੇ (b)
	    {
	      ਰੁੱਖ ext_decl, ext_type;
	      ext_decl = b->decl;
	      ext_type = b->u.type ? b->u.type : ਰੁੱਖ_TYPE (ext_decl);
	      ਜੇ (ਰੁੱਖ_ਕੋਡ (ext_type) == FUNCTION_TYPE
		  && comptypes (ਰੁੱਖ_TYPE (ਰੁੱਖ_TYPE (decl1)),
				ਰੁੱਖ_TYPE (ext_type)))
		{
		  current_function_prototype_locus
		    = DECL_ਸਰੋਤ_LOCATION (ext_decl);
		  current_function_prototype_built_ਵਿੱਚ
		    = C_DECL_BUILTIN_PROTOTYPE (ext_decl);
		  current_function_prototype_arg_types
		    = TYPE_ARG_TYPES (ext_type);
		}
	    }
	}
    }

  /* Optionally warn about C23 compatibility.  */
  ਜੇ (warn_deprecated_non_prototype
      && old_decl != NULL_ਰੁੱਖ
      && ਰੁੱਖ_ਕੋਡ (oldtype) == FUNCTION_TYPE
      && !TYPE_ARG_TYPES (oldtype)
      && !TYPE_NO_NAMED_ਦਲੀਲਾਂ_STDARG_P (oldtype)
      && (TYPE_ARG_TYPES (newtype)
	  && ਰੁੱਖ_ਮੁੱਲ (TYPE_ARG_TYPES (newtype)) != void_type_ਗੰਢ))
    {
      ਤਾਰਕਿਕ warned = warning_at (loc, OPT_Wdeprecated_non_prototype,
				"ISO C23 does not allow defining"
				" parameters for function %qE declared"
				" without parameters",
				decl1);
      ਜੇ (warned)
	inform (DECL_ਸਰੋਤ_LOCATION (old_decl), "declared here");
    }

  /* Optionally warn of old-fashioned def with no previous prototype.  */
  ਜੇ (warn_strict_prototypes
      && old_decl != error_mark_ਗੰਢ
      && !prototype_p (ਰੁੱਖ_TYPE (decl1))
      && C_DECL_ISNT_PROTOTYPE (old_decl))
    warning_at (loc, OPT_Wstrict_prototypes,
		"function declaration isn%'t a prototype");
  /* Optionally warn of any global def with no previous prototype.  */
  ਨਹੀਂਤਾਂ ਜੇ (warn_missing_prototypes
	   && old_decl != error_mark_ਗੰਢ
	   && ਰੁੱਖ_ਜਨਤਕ (decl1)
	   && !MAIN_NAME_P (DECL_NAME (decl1))
	   && C_DECL_ISNT_PROTOTYPE (old_decl)
	   && !DECL_DECLARED_INLINE_P (decl1))
    warning_at (loc, OPT_Wmissing_prototypes,
		"no previous prototype for %qD", decl1);
  /* Optionally warn of any def with no previous prototype
     if the function has already been used.  */
  ਨਹੀਂਤਾਂ ਜੇ (warn_missing_prototypes
	   && old_decl != NULL_ਰੁੱਖ
	   && old_decl != error_mark_ਗੰਢ
	   && ਰੁੱਖ_ਵਰਤਿਆ (old_decl)
	   && !prototype_p (ਰੁੱਖ_TYPE (old_decl)))
    warning_at (loc, OPT_Wmissing_prototypes,
		"%qD was used with no prototype before its definition", decl1);
  /* Optionally warn of any global def with no previous declaration.  */
  ਨਹੀਂਤਾਂ ਜੇ (warn_missing_declarations
	   && ਰੁੱਖ_ਜਨਤਕ (decl1)
	   && old_decl == NULL_ਰੁੱਖ
	   && !MAIN_NAME_P (DECL_NAME (decl1))
	   && !DECL_DECLARED_INLINE_P (decl1))
    warning_at (loc, OPT_Wmissing_declarations,
		"no previous declaration for %qD",
		decl1);
  /* Optionally warn of any def with no previous declaration
     if the function has already been used.  */
  ਨਹੀਂਤਾਂ ਜੇ (warn_missing_declarations
	   && old_decl != NULL_ਰੁੱਖ
	   && old_decl != error_mark_ਗੰਢ
	   && ਰੁੱਖ_ਵਰਤਿਆ (old_decl)
	   && C_DECL_IMPLICIT (old_decl))
    warning_at (loc, OPT_Wmissing_declarations,
		"%qD was used with no declaration before its definition", decl1);

  /* This function exists in static storage.
     (This does not mean `static' in the C sense!)  */
  ਰੁੱਖ_STATIC (decl1) = 1;

  /* This is the earliest point at which we might know the assembler
     name of the function.  Thus, if it's set before this, die horribly.  */
  gcc_assert (!DECL_ASSEMBLER_NAME_ਸੈੱਟ_P (decl1));

  /* If #pragma weak was used, mark the decl weak now.  */
  ਜੇ (current_scope == file_scope)
    maybe_apply_pragma_weak (decl1);

  /* Warn for unlikely, improbable, or stupid declarations of `main'.  */
  ਜੇ (warn_main && MAIN_NAME_P (DECL_NAME (decl1)))
    {
      ਜੇ (TYPE_MAIN_VARIANT (ਰੁੱਖ_TYPE (ਰੁੱਖ_TYPE (decl1)))
	  != integer_type_ਗੰਢ)
	pedwarn (loc, OPT_Wmain, "return type of %qD is not %<int%>", decl1);
      ਨਹੀਂਤਾਂ ਜੇ (TYPE_ATOMIC (ਰੁੱਖ_TYPE (ਰੁੱਖ_TYPE (decl1))))
	pedwarn (loc, OPT_Wmain, "%<_Atomic%>-qualified return type of %qD",
		 decl1);

      check_main_parameter_types (decl1);

      ਜੇ (!ਰੁੱਖ_ਜਨਤਕ (decl1))
	pedwarn (loc, OPT_Wmain,
		 "%qD is normally a non-static function", decl1);
    }

  ਰੁੱਖ parms = current_function_arg_info->parms;
  ਜੇ (old_decl)
    {
      location_t origloc = DECL_ਸਰੋਤ_LOCATION (old_decl);
      warn_parms_array_mismatch (origloc, old_decl, parms);
    }

  /* To enable versions to be created across TU's we mark and mangle all
     non-default versioned functions.  */
  ਜੇ (ਰੁੱਖ_ਕੋਡ (decl1) == FUNCTION_DECL
      && !ਨਿਸ਼ਾਨਾ_HAS_FMV_ਨਿਸ਼ਾਨਾ_ATTRIBUTE
      && get_ਨਿਸ਼ਾਨਾ_ਸੰਸਕਰਣ (decl1).is_valid ())
    {
      maybe_mark_function_versioned (decl1);
      ਜੇ (current_scope != file_scope)
	error ("versioned definitions are only allowed at file scope");
    }

  /* Record the decl so that the function name is defined.
     If we already have a decl for this name, and it is a FUNCTION_DECL,
     use the old decl.  */

  current_function_decl = pushdecl (decl1);

  ਜੇ (ਰੁੱਖ access = build_attr_access_from_parms (parms, ਝੂਠ))
    decl_ਗੁਣ (&current_function_decl, access, ATTR_FLAG_ਅੰਦਰੂਨੀ,
		     old_decl);

  ਧੱਕੋ_scope ();
  declare_parm_level ();

  /* Set the result decl source location to the location of the typespec.  */
  ਨਤੀਜਾ_loc = (declspecs->locations[cdw_typespec] == UNKNOWN_LOCATION
		? loc : declspecs->locations[cdw_typespec]);
  restype = ਰੁੱਖ_TYPE (ਰੁੱਖ_TYPE (current_function_decl));
  resdecl = build_decl (ਨਤੀਜਾ_loc, ਨਤੀਜਾ_DECL, NULL_ਰੁੱਖ, restype);
  DECL_ARTIFICIAL (resdecl) = 1;
  DECL_IGNORED_P (resdecl) = 1;
  DECL_ਨਤੀਜਾ (current_function_decl) = resdecl;

  ਸ਼ੁਰੂ_fname_decls ();

  ਵਾਪਸ ਸੱਚ;
}

/* Subroutine of store_parm_decls which handles new-style function
   definitions (prototype format). The parms already have decls, so we
   need only record them as in effect and complain if any redundant
   old-style parm decls were written.  */
ਸਥਿਰ ਖਾਲੀ
store_parm_decls_newstyle (ਰੁੱਖ fndecl, ਅਚਲ ਬਣਤਰ c_arg_info *arg_info)
{
  ਰੁੱਖ decl;
  c_arg_ਟੈਗ *ਟੈਗ;
  ਬਿਨਾਨਿਸ਼ਾਨੀ ix;

  ਜੇ (current_scope->bindings)
    {
      error_at (DECL_ਸਰੋਤ_LOCATION (fndecl),
		"old-style parameter declarations in prototyped "
		"function definition");

      /* Get rid of the old-style declarations.  */
      ਕੱਢੋ_scope ();
      ਧੱਕੋ_scope ();
    }
  /* Don't issue this warning for nested functions, and don't issue this
     warning if we got here because ARG_INFO_TYPES was error_mark_node
     (this happens when a function definition has just an ellipsis in
     its parameter list).  */
  ਨਹੀਂਤਾਂ ਜੇ (!ਵਿੱਚ_system_ਸਿਰਲੇਖ_at (ਨਿਵੇਸ਼_location)
	   && !current_function_scope
	   && arg_info->types != error_mark_ਗੰਢ
	   && !arg_info->c23_ਖਾਲੀ_ਥਾਵਾਂ_parens)
    warning_at (DECL_ਸਰੋਤ_LOCATION (fndecl), OPT_Wtraditional,
		"traditional C rejects ISO C style function definitions");

  /* Now make all the parameter declarations visible in the function body.
     We can bypass most of the grunt work of pushdecl.  */
  ਲਈ (decl = arg_info->parms; decl; decl = DECL_CHAIN (decl))
    {
      DECL_CONTEXT (decl) = current_function_decl;
      ਜੇ (DECL_NAME (decl))
	{
	  bind (DECL_NAME (decl), decl, current_scope,
		/*invisible=*/ਝੂਠ, /*nested=*/ਝੂਠ,
		UNKNOWN_LOCATION);
	  ਜੇ (!ਰੁੱਖ_ਵਰਤਿਆ (decl))
	    warn_if_shadowing (decl);
	}
      ਨਹੀਂਤਾਂ
	pedwarn_c11 (DECL_ਸਰੋਤ_LOCATION (decl), OPT_Wmissing_parameter_name,
		     "ISO C does not support omitting parameter names in "
		     "function definitions before C23");
    }

  /* Record the parameter list in the function declaration.  */
  DECL_ARGUMENTS (fndecl) = arg_info->parms;

  /* Now make all the ancillary declarations visible, likewise.  */
  ਲਈ (decl = arg_info->others; decl; decl = DECL_CHAIN (decl))
    {
      DECL_CONTEXT (decl) = current_function_decl;
      ਜੇ (DECL_NAME (decl))
	bind (DECL_NAME (decl), decl, current_scope,
	      /*invisible=*/ਝੂਠ,
	      /*nested=*/(ਰੁੱਖ_ਕੋਡ (decl) == FUNCTION_DECL),
	      UNKNOWN_LOCATION);
    }

  /* And all the tag declarations.  */
  FOR_EACH_VEC_ਸੁਰੱਖਿਅਤ_ELT_ਉਲਟ (arg_info->ਟੈਗ_ਸੂਚੀ, ix, ਟੈਗ)
    ਜੇ (ਟੈਗ->id)
      bind (ਟੈਗ->id, ਟੈਗ->type, current_scope,
	    /*invisible=*/ਝੂਠ, /*nested=*/ਝੂਠ, UNKNOWN_LOCATION);
}

/* Subroutine of store_parm_decls which handles old-style function
   definitions (separate parameter list and declarations).  */

ਸਥਿਰ ਖਾਲੀ
store_parm_decls_oldstyle (ਰੁੱਖ fndecl, ਅਚਲ ਬਣਤਰ c_arg_info *arg_info)
{
  ਬਣਤਰ c_binding *b;
  ਰੁੱਖ parm, decl, ਆਖਰੀ;
  ਰੁੱਖ parmids = arg_info->parms;
  hash_ਸੈੱਟ<ਰੁੱਖ> ਵੇਖਿਆ_ਦਲੀਲਾਂ;

  ਜੇ (!ਵਿੱਚ_system_ਸਿਰਲੇਖ_at (ਨਿਵੇਸ਼_location))
    {
      ਜੇ (flag_isoc23)
	pedwarn (DECL_ਸਰੋਤ_LOCATION (fndecl),
		 OPT_Wold_style_definition, "old-style function definition");
      ਨਹੀਂਤਾਂ
	warning_at (DECL_ਸਰੋਤ_LOCATION (fndecl),
		    OPT_Wold_style_definition,
		    "old-style function definition");
    }

  ਜੇ (current_scope->had_vla_unspec)
    error ("%<[*]%> not allowed in other than function prototype scope");

  /* Match each formal parameter name with its declaration.  Save each
     decl in the appropriate TREE_PURPOSE slot of the parmids chain.  */
  ਲਈ (parm = parmids; parm; parm = ਰੁੱਖ_CHAIN (parm))
    {
      ਜੇ (ਰੁੱਖ_ਮੁੱਲ (parm) == NULL_ਰੁੱਖ)
	{
	  error_at (DECL_ਸਰੋਤ_LOCATION (fndecl),
		    "parameter name missing from parameter list");
	  ਰੁੱਖ_PURPOSE (parm) = NULL_ਰੁੱਖ;
	  ਜਾਰੀ;
	}

      b = I_ਚਿੰਨ੍ਹ_BINDING (ਰੁੱਖ_ਮੁੱਲ (parm));
      ਜੇ (b && B_ਵਿੱਚ_CURRENT_SCOPE (b))
	{
	  decl = b->decl;
	  /* Skip erroneous parameters.  */
	  ਜੇ (decl == error_mark_ਗੰਢ)
	    ਜਾਰੀ;
	  /* If we got something other than a PARM_DECL it is an error.  */
	  ਜੇ (ਰੁੱਖ_ਕੋਡ (decl) != PARM_DECL)
	    {
	      error_at (DECL_ਸਰੋਤ_LOCATION (decl),
			"%qD declared as a non-parameter", decl);
	      ਜਾਰੀ;
	    }
	  /* If the declaration is already marked, we have a duplicate
	     name.  Complain and ignore the duplicate.  */
	  ਨਹੀਂਤਾਂ ਜੇ (ਵੇਖਿਆ_ਦਲੀਲਾਂ.ਸ਼ਾਮਲ_ਹੈ (decl))
	    {
	      error_at (DECL_ਸਰੋਤ_LOCATION (decl),
			"multiple parameters named %qD", decl);
	      ਰੁੱਖ_PURPOSE (parm) = NULL_ਰੁੱਖ;
	      ਜਾਰੀ;
	    }
	  /* If the declaration says "void", complain and turn it into
	     an int.  */
	  ਨਹੀਂਤਾਂ ਜੇ (VOID_TYPE_P (ਰੁੱਖ_TYPE (decl)))
	    {
	      error_at (DECL_ਸਰੋਤ_LOCATION (decl),
			"parameter %qD declared with void type", decl);
	      ਰੁੱਖ_TYPE (decl) = integer_type_ਗੰਢ;
	      DECL_ARG_TYPE (decl) = integer_type_ਗੰਢ;
	      layout_decl (decl, 0);
	    }
	  warn_if_shadowing (decl);
	}
      /* If no declaration found, default to int.  */
      ਨਹੀਂਤਾਂ
	{
	  /* FIXME diagnostics: This should be the location of the argument,
	     not the FNDECL.  E.g., for an old-style declaration

	       int f10(v) { blah; }

	     We should use the location of the V, not the F10.
	     Unfortunately, the V is an IDENTIFIER_NODE which has no
	     location.  In the future we need locations for c_arg_info
	     entries.

	     See gcc.dg/Wshadow-3.c for an example of this problem. */
	  decl = build_decl (DECL_ਸਰੋਤ_LOCATION (fndecl),
			     PARM_DECL, ਰੁੱਖ_ਮੁੱਲ (parm), integer_type_ਗੰਢ);
	  DECL_ARG_TYPE (decl) = ਰੁੱਖ_TYPE (decl);
	  pushdecl (decl);
	  warn_if_shadowing (decl);

	  ਜੇ (flag_isoc99)
	    permerror_opt (DECL_ਸਰੋਤ_LOCATION (decl),
			   OPT_Wimplicit_int, "type of %qD defaults to %<int%>",
			   decl);
	  ਨਹੀਂਤਾਂ
	    warning_at (DECL_ਸਰੋਤ_LOCATION (decl),
			OPT_Wmissing_parameter_type,
			"type of %qD defaults to %<int%>", decl);
	}

      ਰੁੱਖ_PURPOSE (parm) = decl;
      ਵੇਖਿਆ_ਦਲੀਲਾਂ.ਜੋੜੋ (decl);
    }

  /* Now examine the parms chain for incomplete declarations
     and declarations with no corresponding names.  */

  ਲਈ (b = current_scope->bindings; b; b = b->prev)
    {
      parm = b->decl;
      ਜੇ (ਰੁੱਖ_ਕੋਡ (parm) != PARM_DECL)
	ਜਾਰੀ;

      ਜੇ (ਰੁੱਖ_TYPE (parm) != error_mark_ਗੰਢ
	  && !COMPLETE_TYPE_P (ਰੁੱਖ_TYPE (parm)))
	{
	  error_at (DECL_ਸਰੋਤ_LOCATION (parm),
		    "parameter %qD has incomplete type", parm);
	  ਰੁੱਖ_TYPE (parm) = error_mark_ਗੰਢ;
	}

      ਜੇ (!ਵੇਖਿਆ_ਦਲੀਲਾਂ.ਸ਼ਾਮਲ_ਹੈ (parm))
	{
	  error_at (DECL_ਸਰੋਤ_LOCATION (parm),
		    "declaration for parameter %qD but no such parameter",
		    parm);

	  /* Pretend the parameter was not missing.
	     This gets us to a standard state and minimizes
	     further error messages.  */
	  parmids = chainon (parmids, ਰੁੱਖ_cons (parm, 0, 0));
	}
    }

  /* Chain the declarations together in the order of the list of
     names.  Store that chain in the function decl, replacing the
     list of names.  Update the current scope to match.  */
  DECL_ARGUMENTS (fndecl) = NULL_ਰੁੱਖ;

  ਲਈ (parm = parmids; parm; parm = ਰੁੱਖ_CHAIN (parm))
    ਜੇ (ਰੁੱਖ_PURPOSE (parm))
      ਰੋਕੋ;
  ਜੇ (parm && ਰੁੱਖ_PURPOSE (parm))
    {
      ਆਖਰੀ = ਰੁੱਖ_PURPOSE (parm);
      DECL_ARGUMENTS (fndecl) = ਆਖਰੀ;

      ਲਈ (parm = ਰੁੱਖ_CHAIN (parm); parm; parm = ਰੁੱਖ_CHAIN (parm))
	ਜੇ (ਰੁੱਖ_PURPOSE (parm))
	  {
	    DECL_CHAIN (ਆਖਰੀ) = ਰੁੱਖ_PURPOSE (parm);
	    ਆਖਰੀ = ਰੁੱਖ_PURPOSE (parm);
	  }
      DECL_CHAIN (ਆਖਰੀ) = NULL_ਰੁੱਖ;
    }

  /* If there was a previous prototype,
     set the DECL_ARG_TYPE of each argument according to
     the type previously specified, and report any mismatches.  */

  ਜੇ (current_function_prototype_arg_types)
    {
      ਰੁੱਖ type;
      ਲਈ (parm = DECL_ARGUMENTS (fndecl),
	     type = current_function_prototype_arg_types;
	   parm || (type != NULL_ਰੁੱਖ
		    && ਰੁੱਖ_ਮੁੱਲ (type) != error_mark_ਗੰਢ
		    && TYPE_MAIN_VARIANT (ਰੁੱਖ_ਮੁੱਲ (type)) != void_type_ਗੰਢ);
	   parm = DECL_CHAIN (parm), type = ਰੁੱਖ_CHAIN (type))
	{
	  ਜੇ (parm == NULL_ਰੁੱਖ
	      || type == NULL_ਰੁੱਖ
	      || (ਰੁੱਖ_ਮੁੱਲ (type) != error_mark_ਗੰਢ
		  && TYPE_MAIN_VARIANT (ਰੁੱਖ_ਮੁੱਲ (type)) == void_type_ਗੰਢ))
	    {
	      ਜੇ (current_function_prototype_built_ਵਿੱਚ)
		warning_at (DECL_ਸਰੋਤ_LOCATION (fndecl),
			    0, "number of arguments doesn%'t match "
			    "built-in prototype");
	      ਨਹੀਂਤਾਂ
		{
		  /* FIXME diagnostics: This should be the location of
		     FNDECL, but there is bug when a prototype is
		     declared inside function context, but defined
		     outside of it (e.g., gcc.dg/pr15698-2.c).  In
		     which case FNDECL gets the location of the
		     prototype, not the definition.  */
		  error_at (ਨਿਵੇਸ਼_location,
			    "number of arguments doesn%'t match prototype");

		  error_at (current_function_prototype_locus,
			    "prototype declaration");
		}
	      ਰੋਕੋ;
	    }
	  /* Type for passing arg must be consistent with that
	     declared for the arg.  ISO C says we take the unqualified
	     type for parameters declared with qualified type.  */
	  ਜੇ (ਰੁੱਖ_TYPE (parm) != error_mark_ਗੰਢ
	      && ਰੁੱਖ_ਮੁੱਲ (type) != error_mark_ਗੰਢ
	      && ((TYPE_ATOMIC (DECL_ARG_TYPE (parm))
		   != TYPE_ATOMIC (ਰੁੱਖ_ਮੁੱਲ (type)))
		  || !comptypes (TYPE_MAIN_VARIANT (DECL_ARG_TYPE (parm)),
				 TYPE_MAIN_VARIANT (ਰੁੱਖ_ਮੁੱਲ (type)))))
	    {
	      ਜੇ ((TYPE_ATOMIC (DECL_ARG_TYPE (parm))
		   == TYPE_ATOMIC (ਰੁੱਖ_ਮੁੱਲ (type)))
		  && (TYPE_MAIN_VARIANT (ਰੁੱਖ_TYPE (parm))
		      == TYPE_MAIN_VARIANT (ਰੁੱਖ_ਮੁੱਲ (type))))
		{
		  /* Adjust argument to match prototype.  E.g. a previous
		     `int foo(float);' prototype causes
		     `int foo(x) float x; {...}' to be treated like
		     `int foo(float x) {...}'.  This is particularly
		     useful for argument types like uid_t.  */
		  DECL_ARG_TYPE (parm) = ਰੁੱਖ_TYPE (parm);

		  /* ??? Is it possible to get here with a
		     built-in prototype or will it always have
		     been diagnosed as conflicting with an
		     old-style definition and discarded?  */
		  ਜੇ (current_function_prototype_built_ਵਿੱਚ)
		    warning_at (DECL_ਸਰੋਤ_LOCATION (parm),
				OPT_Wpedantic, "promoted argument %qD "
				"doesn%'t match built-in prototype", parm);
		  ਨਹੀਂਤਾਂ
		    {
		      pedwarn (DECL_ਸਰੋਤ_LOCATION (parm),
			       OPT_Wpedantic, "promoted argument %qD "
			       "doesn%'t match prototype", parm);
		      pedwarn (current_function_prototype_locus, OPT_Wpedantic,
			       "prototype declaration");
		    }
		}
	      ਨਹੀਂਤਾਂ
		{
		  ਜੇ (current_function_prototype_built_ਵਿੱਚ)
		    warning_at (DECL_ਸਰੋਤ_LOCATION (parm),
				0, "argument %qD doesn%'t match "
				"built-in prototype", parm);
		  ਨਹੀਂਤਾਂ
		    {
		      error_at (DECL_ਸਰੋਤ_LOCATION (parm),
				"argument %qD doesn%'t match prototype", parm);
		      error_at (current_function_prototype_locus,
				"prototype declaration");
		    }
		}
	    }
	}
      TYPE_ACTUAL_ARG_TYPES (ਰੁੱਖ_TYPE (fndecl)) = NULL_ਰੁੱਖ;
    }

  /* Otherwise, create a prototype that would match.  */

  ਨਹੀਂਤਾਂ
    {
      ਰੁੱਖ actual = NULL_ਰੁੱਖ, ਆਖਰੀ = NULL_ਰੁੱਖ, type;

      ਲਈ (parm = DECL_ARGUMENTS (fndecl); parm; parm = DECL_CHAIN (parm))
	{
	  type = ਰੁੱਖ_cons (NULL_ਰੁੱਖ, DECL_ARG_TYPE (parm), NULL_ਰੁੱਖ);
	  ਜੇ (ਆਖਰੀ)
	    ਰੁੱਖ_CHAIN (ਆਖਰੀ) = type;
	  ਨਹੀਂਤਾਂ
	    actual = type;
	  ਆਖਰੀ = type;
	}
      type = ਰੁੱਖ_cons (NULL_ਰੁੱਖ, void_type_ਗੰਢ, NULL_ਰੁੱਖ);
      ਜੇ (ਆਖਰੀ)
	ਰੁੱਖ_CHAIN (ਆਖਰੀ) = type;
      ਨਹੀਂਤਾਂ
	actual = type;

      /* We are going to assign a new value for the TYPE_ACTUAL_ARG_TYPES
	 of the type of this function, but we need to avoid having this
	 affect the types of other similarly-typed functions, so we must
	 first force the generation of an identical (but separate) type
	 node for the relevant function type.  The new node we create
	 will be a variant of the main variant of the original function
	 type.  */

      ਰੁੱਖ_TYPE (fndecl) = build_variant_type_copy (ਰੁੱਖ_TYPE (fndecl));

      TYPE_ACTUAL_ARG_TYPES (ਰੁੱਖ_TYPE (fndecl)) = actual;
    }
}

/* Store parameter declarations passed in ARG_INFO into the current
   function declaration.  */

ਖਾਲੀ
store_parm_decls_from (ਬਣਤਰ c_arg_info *arg_info)
{
  current_function_arg_info = arg_info;
  store_parm_decls ();
}

/* Called by walk_tree to look for and update context-less labels
   or labels with context in the parent function.  */

ਸਥਿਰ ਰੁੱਖ
ਸੈੱਟ_labels_context_r (ਰੁੱਖ *tp, ਪੂਰਨ *walk_subtrees, ਖਾਲੀ *ਅੰਕੜੇ)
{
  ਰੁੱਖ ctx = static_cast<ਰੁੱਖ>(ਅੰਕੜੇ);
  ਜੇ (ਰੁੱਖ_ਕੋਡ (*tp) == LABEL_ਵਿਅੰਜਕ
      && (DECL_CONTEXT (LABEL_ਵਿਅੰਜਕ_LABEL (*tp)) == NULL_ਰੁੱਖ
	  || DECL_CONTEXT (LABEL_ਵਿਅੰਜਕ_LABEL (*tp)) == DECL_CONTEXT (ctx)))
    {
      DECL_CONTEXT (LABEL_ਵਿਅੰਜਕ_LABEL (*tp)) = ctx;
      *walk_subtrees = 0;
    }

  ਵਾਪਸ NULL_ਰੁੱਖ;
}

/* Store the parameter declarations into the current function declaration.
   This is called after parsing the parameter declarations, before
   digesting the body of the function.

   For an old-style definition, construct a prototype out of the old-style
   parameter declarations and inject it into the function's type.  */

ਖਾਲੀ
store_parm_decls (ਖਾਲੀ)
{
  ਰੁੱਖ fndecl = current_function_decl;
  ਤਾਰਕਿਕ proto;

  /* The argument information block for FNDECL.  */
  ਬਣਤਰ c_arg_info *arg_info = current_function_arg_info;
  current_function_arg_info = 0;

  /* True if this definition is written with a prototype.  In C23, an
     empty argument list was converted to (void) in grokparms; in
     older C standard versions, it does not give the function a type
     with a prototype for future calls.  */
  proto = arg_info->types != 0 || arg_info->no_named_ਦਲੀਲਾਂ_stdarg_p;

  ਜੇ (proto)
    store_parm_decls_newstyle (fndecl, arg_info);
  ਨਹੀਂਤਾਂ
    store_parm_decls_oldstyle (fndecl, arg_info);

  /* The next call to push_scope will be a function body.  */

  ਅਗਲਾ_is_function_body = ਸੱਚ;

  /* Write a record describing this function definition to the prototypes
     file (if requested).  */

  gen_aux_info_ਰਿਕਾਰਡ (fndecl, 1, 0, proto);

  /* Initialize the RTL code for the function.  */
  allocate_struct_function (fndecl, ਝੂਠ);

  ਜੇ (warn_ਅਣਵਰਤਿਆ_local_typedefs)
    cfun->language = ggc_cleared_alloc<language_function> ();

  /* Begin the statement tree for this function.  */
  DECL_SAVED_ਰੁੱਖ (fndecl) = ਧੱਕੋ_stmt_list ();

  /* ??? Insert the contents of the pending sizes list into the function
     to be evaluated.  The only reason left to have this is
	void foo(int n, int array[n++])
     because we throw away the array type in favor of a pointer type, and
     thus won't naturally see the SAVE_EXPR containing the increment.  All
     other pending sizes would be handled by gimplify_parameters.  */
  ਜੇ (arg_info->pending_sizes)
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
      walk_ਰੁੱਖ_without_duplicates (&arg_info->pending_sizes,
				    ਸੈੱਟ_labels_context_r, fndecl);
      ਜੋੜੋ_stmt (arg_info->pending_sizes);
    }
}

/* Store PARM_DECLs in PARMS into scope temporarily.  Used for
   c_finish_omp_declare_simd for function prototypes.  No diagnostics
   should be done.  */

ਖਾਲੀ
ਆਰਜ਼ੀ_store_parm_decls (ਰੁੱਖ fndecl, ਰੁੱਖ parms)
{
  ਧੱਕੋ_scope ();
  ਲਈ (ਰੁੱਖ p = parms; p; p = DECL_CHAIN (p))
    {
      DECL_CONTEXT (p) = fndecl;
      ਜੇ (DECL_NAME (p))
	bind (DECL_NAME (p), p, current_scope,
	      /*invisible=*/ਝੂਠ, /*nested=*/ਝੂਠ,
	      UNKNOWN_LOCATION);
    }
}

/* Undo what temp_store_parm_decls did.  */

ਖਾਲੀ
ਆਰਜ਼ੀ_ਕੱਢੋ_parm_decls (ਖਾਲੀ)
{
  /* Clear all bindings in this temporary scope, so that
     pop_scope doesn't create a BLOCK.  */
  ਬਣਤਰ c_binding *b = current_scope->bindings;
  current_scope->bindings = ਨਿਰਾ;
  ਲਈ (; b; b = free_binding_and_advance (b))
    {
      gcc_assert (ਰੁੱਖ_ਕੋਡ (b->decl) == PARM_DECL
		  || b->decl == error_mark_ਗੰਢ);
      gcc_assert (I_ਚਿੰਨ੍ਹ_BINDING (b->id) == b);
      I_ਚਿੰਨ੍ਹ_BINDING (b->id) = b->shadowed;
      ਜੇ (b->shadowed && b->shadowed->u.type)
	ਰੁੱਖ_TYPE (b->shadowed->decl) = b->shadowed->u.type;
    }
  ਕੱਢੋ_scope ();
}


/* Finish up a function declaration and compile that function
   all the way to assembler language output.  Then free the storage
   for the function definition.

   This is called after parsing the body of the function definition.  */

ਖਾਲੀ
ਅੰਤ_function (location_t ਸਿਰਾ_loc)
{
  ਰੁੱਖ fndecl = current_function_decl;

  ਜੇ (c_dialect_objc ())
    objc_ਅੰਤ_function ();

  ਜੇ (DECL_INITIAL (fndecl) && DECL_INITIAL (fndecl) != error_mark_ਗੰਢ)
    ਖੰਡ_SUPERCONTEXT (DECL_INITIAL (fndecl)) = fndecl;

  /* Must mark the RESULT_DECL as being in this function.  */

  ਜੇ (DECL_ਨਤੀਜਾ (fndecl) && DECL_ਨਤੀਜਾ (fndecl) != error_mark_ਗੰਢ)
    DECL_CONTEXT (DECL_ਨਤੀਜਾ (fndecl)) = fndecl;

  ਜੇ (MAIN_NAME_P (DECL_NAME (fndecl)) && !ਰੁੱਖ_THIS_VOLATILE (fndecl)
      && TYPE_MAIN_VARIANT (ਰੁੱਖ_TYPE (ਰੁੱਖ_TYPE (fndecl)))
      == integer_type_ਗੰਢ && flag_isoc99)
    {
      /* Hack.  We don't want the middle-end to warn that this return
	 is unreachable, so we mark its location as special.  Using
	 UNKNOWN_LOCATION has the problem that it gets clobbered in
	 annotate_one_with_locus.  A cleaner solution might be to
	 ensure ! should_carry_locus_p (stmt), but that needs a flag.
      */
      c_ਅੰਤ_return (BUILTINS_LOCATION, integer_zero_ਗੰਢ, NULL_ਰੁੱਖ);
    }

  /* Tie off the statement tree for this function.  */
  DECL_SAVED_ਰੁੱਖ (fndecl) = ਕੱਢੋ_stmt_list (DECL_SAVED_ਰੁੱਖ (fndecl));

  ਅੰਤ_fname_decls ();

  /* Complain if there's no return statement only if option specified on
     command line.  */
  ਜੇ (warn_return_type > 0
      && ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (ਰੁੱਖ_TYPE (fndecl))) != VOID_TYPE
      && !current_function_returns_ਮੁੱਲ && !current_function_returns_null
      /* Don't complain if we are no-return.  */
      && !current_function_returns_abnormally
      /* Don't complain if we are declared noreturn.  */
      && !ਰੁੱਖ_THIS_VOLATILE (fndecl)
      /* Don't warn for main().  */
      && !MAIN_NAME_P (DECL_NAME (fndecl))
      /* Or if they didn't actually specify a return type.  */
      && !C_FUNCTION_IMPLICIT_INT (fndecl)
      /* Normally, with -Wreturn-type, flow will complain, but we might
         optimize out static functions.  */
      && !ਰੁੱਖ_ਜਨਤਕ (fndecl)
      && targetm.warn_func_return (fndecl)
      && warning (OPT_Wreturn_type,
		  "no return statement in function returning non-void"))
    suppress_warning (fndecl, OPT_Wreturn_type);

  /* Complain about parameters that are only set, but never otherwise used.  */
  ਜੇ (warn_ਅਣਵਰਤਿਆ_but_ਸੈੱਟ_parameter)
    {
      ਰੁੱਖ decl;

      ਲਈ (decl = DECL_ARGUMENTS (fndecl);
	   decl;
	   decl = DECL_CHAIN (decl))
	ਜੇ (ਰੁੱਖ_ਵਰਤਿਆ (decl)
	    && ਰੁੱਖ_ਕੋਡ (decl) == PARM_DECL
	    && !DECL_READ_P (decl)
	    && DECL_NAME (decl)
	    && !DECL_ARTIFICIAL (decl)
	    && !warning_suppressed_p (decl, OPT_Wunused_but_ਸੈੱਟ_parameter))
	  warning_at (DECL_ਸਰੋਤ_LOCATION (decl),
		      OPT_Wunused_but_ਸੈੱਟ_parameter,
		      "parameter %qD set but not used", decl);
    }

  /* Complain about locally defined typedefs that are not used in this
     function.  */
  maybe_warn_ਅਣਵਰਤਿਆ_local_typedefs ();

  /* Possibly warn about unused parameters.  */
  ਜੇ (warn_ਅਣਵਰਤਿਆ_parameter)
    do_warn_ਅਣਵਰਤਿਆ_parameter (fndecl);

  /* Store the end of the function, so that we get good line number
     info for the epilogue.  */
  cfun->function_ਸਿਰਾ_locus = ਸਿਰਾ_loc;

  /* Finalize the ELF visibility for the function.  */
  c_determine_visibility (fndecl);

  /* For GNU C extern inline functions disregard inline limits.  */
  ਜੇ (DECL_EXTERNAL (fndecl)
      && DECL_DECLARED_INLINE_P (fndecl)
      && (flag_gnu89_inline
	  || lookup_attribute ("gnu_inline", DECL_ਗੁਣ (fndecl))))
    DECL_DISREGARD_INLINE_LIMITS (fndecl) = 1;

  /* Genericize before inlining.  Delay genericizing nested functions
     until their parent function is genericized.  Since finalizing
     requires GENERIC, delay that as well.  */

  ਜੇ (DECL_INITIAL (fndecl) && DECL_INITIAL (fndecl) != error_mark_ਗੰਢ
      && !undef_nested_function)
    {
      ਜੇ (!decl_function_context (fndecl))
	{
	  invoke_plugin_callbacks (PLUGIN_PRE_GENERICIZE, fndecl);
	  c_genericize (fndecl);

	  /* ??? Objc emits functions after finalizing the compilation unit.
	     This should be cleaned up later and this conditional removed.  */
	  ਜੇ (symtab->global_info_ready)
	    {
	      cgraph_ਗੰਢ::ਜੋੜੋ_new_function (fndecl, ਝੂਠ);
	      ਵਾਪਸ;
	    }
	  cgraph_ਗੰਢ::finalize_function (fndecl, ਝੂਠ);
	}
      ਨਹੀਂਤਾਂ
	{
	  /* Register this function with cgraph just far enough to get it
	    added to our parent's nested function list.  Handy, since the
	    C front end doesn't have such a list.  */
	  (ਖਾਲੀ) cgraph_ਗੰਢ::get_create (fndecl);
	}
    }

  ਜੇ (!decl_function_context (fndecl))
    undef_nested_function = ਝੂਠ;

  ਜੇ (cfun->language != ਨਿਰਾ)
    {
      ggc_free (cfun->language);
      cfun->language = ਨਿਰਾ;
    }

  /* We're leaving the context of this function, so zap cfun.
     It's still in DECL_STRUCT_FUNCTION, and we'll restore it in
     tree_rest_of_compilation.  */
  ਸੈੱਟ_cfun (ਨਿਰਾ);
  invoke_plugin_callbacks (PLUGIN_ਅੰਤ_PARSE_FUNCTION, current_function_decl);
  current_function_decl = ਨਿਰਾ;
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

ਰੁੱਖ
check_for_loop_decls (location_t loc, ਤਾਰਕਿਕ turn_off_iso_c99_error)
{
  ਬਣਤਰ c_binding *b;
  ਰੁੱਖ one_decl = NULL_ਰੁੱਖ;
  ਪੂਰਨ n_decls = 0;

  ਜੇ (!turn_off_iso_c99_error)
    {
      ਸਥਿਰ ਤਾਰਕਿਕ hint = ਸੱਚ;
      /* If we get here, declarations have been used in a for loop without
	 the C99 for loop scope.  This doesn't make much sense, so don't
	 allow it.  */
      auto_diagnostic_ਸਮੂਹ d;
      error_at (loc, "%<for%> loop initial declarations "
		"are only allowed in C99 or C11 mode");
      ਜੇ (hint)
	{
	  inform (loc,
		  "use option %<-std=c99%>, %<-std=gnu99%>, %<-std=c11%> or "
		  "%<-std=gnu11%> to compile your code");
	  hint = ਝੂਠ;
	}
      ਵਾਪਸ NULL_ਰੁੱਖ;
    }
  ਨਹੀਂਤਾਂ
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

  ਲਈ (b = current_scope->bindings; b; b = b->prev)
    {
      ਰੁੱਖ id = b->id;
      ਰੁੱਖ decl = b->decl;

      ਜੇ (!id)
	ਜਾਰੀ;

      ਚੋਣ (ਰੁੱਖ_ਕੋਡ (decl))
	{
	ਹਾਲਤ VAR_DECL:
	  {
	    location_t decl_loc = DECL_ਸਰੋਤ_LOCATION (decl);
	    ਜੇ (ਰੁੱਖ_STATIC (decl))
	      pedwarn_c11 (decl_loc, OPT_Wpedantic,
			   "declaration of static variable %qD in %<for%> "
			   "loop initial declaration", decl);
	    ਨਹੀਂਤਾਂ ਜੇ (DECL_EXTERNAL (decl))
	      pedwarn_c11 (decl_loc, OPT_Wpedantic,
			   "declaration of %<extern%> variable %qD in %<for%> "
			   "loop initial declaration", decl);
	  }
	  ਰੋਕੋ;

	ਹਾਲਤ ਰਿਕਾਰਡ_TYPE:
	  pedwarn_c11 (loc, OPT_Wpedantic,
		       "%<struct %E%> declared in %<for%> loop initial "
		       "declaration", id);
	  ਰੋਕੋ;
	ਹਾਲਤ UNION_TYPE:
	  pedwarn_c11 (loc, OPT_Wpedantic,
		       "%<union %E%> declared in %<for%> loop initial "
		       "declaration",
		       id);
	  ਰੋਕੋ;
	ਹਾਲਤ ENUMERAL_TYPE:
	  pedwarn_c11 (loc, OPT_Wpedantic,
		       "%<enum %E%> declared in %<for%> loop "
		       "initial declaration", id);
	  ਰੋਕੋ;
	ਮੂਲ:
	  pedwarn_c11 (loc, OPT_Wpedantic, "declaration of non-variable "
		       "%qD in %<for%> loop initial declaration", decl);
	}

      n_decls++;
      one_decl = decl;
    }

  ਵਾਪਸ n_decls == 1 ? one_decl : NULL_ਰੁੱਖ;
}

/* Save and reinitialize the variables
   used during compilation of a C function.  */

ਖਾਲੀ
c_ਧੱਕੋ_function_context (ਖਾਲੀ)
{
  ਬਣਤਰ language_function *p = cfun->language;
  /* cfun->language might have been already allocated by the use of
     -Wunused-local-typedefs.  In that case, just re-use it.  */
  ਜੇ (p == ਨਿਰਾ)
    cfun->language = p = ggc_cleared_alloc<language_function> ();

  p->ਅਧਾਰ.x_stmt_ਰੁੱਖ = c_stmt_ਰੁੱਖ;
  c_stmt_ਰੁੱਖ.x_cur_stmt_list = vec_ਸੁਰੱਖਿਅਤ_copy (c_stmt_ਰੁੱਖ.x_cur_stmt_list);
  p->x_ਵਿੱਚ_statement = ਵਿੱਚ_statement;
  p->x_switch_ਢੇਰ = c_switch_ਢੇਰ;
  p->loop_ਨਾਂ = loop_ਨਾਂ;
  loop_ਨਾਂ = vNULL;
  p->loop_ਨਾਂ_hash = loop_ਨਾਂ_hash;
  loop_ਨਾਂ_hash = ਨਿਰਾ;
  p->arg_info = current_function_arg_info;
  p->returns_ਮੁੱਲ = current_function_returns_ਮੁੱਲ;
  p->returns_null = current_function_returns_null;
  p->returns_abnormally = current_function_returns_abnormally;
  p->warn_about_return_type = warn_about_return_type;

  ਧੱਕੋ_function_context ();
}

/* Restore the variables used during compilation of a C function.  */

ਖਾਲੀ
c_ਕੱਢੋ_function_context (ਖਾਲੀ)
{
  ਬਣਤਰ language_function *p;

  ਕੱਢੋ_function_context ();
  p = cfun->language;

  /* When -Wunused-local-typedefs is in effect, cfun->languages is
     used to store data throughout the life time of the current cfun,
     So don't deallocate it.  */
  ਜੇ (!warn_ਅਣਵਰਤਿਆ_local_typedefs)
    cfun->language = ਨਿਰਾ;

  ਜੇ (DECL_STRUCT_FUNCTION (current_function_decl) == 0
      && DECL_SAVED_ਰੁੱਖ (current_function_decl) == NULL_ਰੁੱਖ)
    {
      /* Stop pointing to the local nodes about to be freed.  */
      /* But DECL_INITIAL must remain nonzero so we know this
	 was an actual function definition.  */
      DECL_INITIAL (current_function_decl) = error_mark_ਗੰਢ;
      DECL_ARGUMENTS (current_function_decl) = NULL_ਰੁੱਖ;
    }

  c_stmt_ਰੁੱਖ = p->ਅਧਾਰ.x_stmt_ਰੁੱਖ;
  p->ਅਧਾਰ.x_stmt_ਰੁੱਖ.x_cur_stmt_list = ਨਿਰਾ;
  ਵਿੱਚ_statement = p->x_ਵਿੱਚ_statement;
  c_switch_ਢੇਰ = p->x_switch_ਢੇਰ;
  loop_ਨਾਂ.release ();
  loop_ਨਾਂ = p->loop_ਨਾਂ;
  p->loop_ਨਾਂ = vNULL;
  ਮਿਟਾਓ loop_ਨਾਂ_hash;
  loop_ਨਾਂ_hash = p->loop_ਨਾਂ_hash;
  p->loop_ਨਾਂ_hash = ਨਿਰਾ;
  current_function_arg_info = p->arg_info;
  current_function_returns_ਮੁੱਲ = p->returns_ਮੁੱਲ;
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

stmt_ਰੁੱਖ
current_stmt_ਰੁੱਖ (ਖਾਲੀ)
{
  ਵਾਪਸ &c_stmt_ਰੁੱਖ;
}

/* Return the global value of T as a symbol.  */

ਰੁੱਖ
identifier_global_ਮੁੱਲ	(ਰੁੱਖ t)
{
  ਬਣਤਰ c_binding *b;

  ਲਈ (b = I_ਚਿੰਨ੍ਹ_BINDING (t); b; b = b->shadowed)
    ਜੇ (B_ਵਿੱਚ_FILE_SCOPE (b) || B_ਵਿੱਚ_EXTERNAL_SCOPE (b))
      ਵਾਪਸ b->decl;

  ਵਾਪਸ NULL_ਰੁੱਖ;
}

/* Return the global value of tag T as a symbol.  */

ਰੁੱਖ
identifier_global_ਟੈਗ (ਰੁੱਖ t)
{
  ਬਣਤਰ c_binding *b;

  ਲਈ (b = I_ਟੈਗ_BINDING (t); b; b = b->shadowed)
    ਜੇ (B_ਵਿੱਚ_FILE_SCOPE (b) || B_ਵਿੱਚ_EXTERNAL_SCOPE (b))
      ਵਾਪਸ b->decl;

  ਵਾਪਸ NULL_ਰੁੱਖ;
}

/* Returns non-zero (result of __has_builtin) if NAME refers to a built-in
   function or function-like operator.  */

ਪੂਰਨ
ਨਾਂ_builtin_p (ਅਚਲ ਅੱਖਰ *name)
{
  ਰੁੱਖ id = get_identifier (name);
  ਜੇ (ਰੁੱਖ decl = identifier_global_ਮੁੱਲ (id))
    ਵਾਪਸ ਰੁੱਖ_ਕੋਡ (decl) == FUNCTION_DECL && DECL_IS_UNDECLARED_BUILTIN (decl);

  /* Also detect common reserved C words that aren't strictly built-in
     functions.  */
  ਚੋਣ (C_RID_ਕੋਡ (id))
    {
    ਹਾਲਤ RID_BUILTIN_ASSOC_BARRIER:
    ਹਾਲਤ RID_BUILTIN_BITREVERSEG:
    ਹਾਲਤ RID_BUILTIN_BSWAPG:
    ਹਾਲਤ RID_BUILTIN_CONVERTVECTOR:
    ਹਾਲਤ RID_BUILTIN_HAS_ATTRIBUTE:
    ਹਾਲਤ RID_BUILTIN_SHUFFLE:
    ਹਾਲਤ RID_BUILTIN_SHUFFLEVECTOR:
    ਹਾਲਤ RID_BUILTIN_STDC:
    ਹਾਲਤ RID_BUILTIN_COUNTED_BY_REF:
    ਹਾਲਤ RID_ਚੁਣੋ_ਵਿਅੰਜਕ:
    ਹਾਲਤ RID_OFFSETOF:
    ਹਾਲਤ RID_TYPES_COMPATIBLE_P:
    ਹਾਲਤ RID_C23_VA_ਸ਼ੁਰੂ:
    ਹਾਲਤ RID_VA_ARG:
      ਵਾਪਸ 1;
    ਮੂਲ:
      ਰੋਕੋ;
    }

  ਵਾਪਸ 0;
}

/* In C, the only C-linkage public declaration is at file scope.  */

ਰੁੱਖ
c_linkage_bindings (ਰੁੱਖ name)
{
  ਵਾਪਸ identifier_global_ਮੁੱਲ (name);
}

/* Record a builtin type for C.  If NAME is non-NULL, it is the name used;
   otherwise the name is found in ridpointers from RID_INDEX.  */

ਖਾਲੀ
ਰਿਕਾਰਡ_builtin_type (ਗਿਣਤੀ rid rid_ਸੂਚਕਾਂਕ, ਅਚਲ ਅੱਖਰ *name, ਰੁੱਖ type)
{
  ਰੁੱਖ id, decl;
  ਜੇ (name == 0)
    id = ridpointers[(ਪੂਰਨ) rid_ਸੂਚਕਾਂਕ];
  ਨਹੀਂਤਾਂ
    id = get_identifier (name);
  decl = build_decl (UNKNOWN_LOCATION, TYPE_DECL, id, type);
  pushdecl (decl);
  ਜੇ (debug_hooks->type_decl)
    debug_hooks->type_decl (decl, ਝੂਠ);
}

/* Return a c_parm structure with the given SPECS, ATTRS and DECLARATOR.  */

ਬਣਤਰ c_parm *
build_c_parm (ਬਣਤਰ c_declspecs *specs, ਰੁੱਖ attrs,
	      ਬਣਤਰ c_declarator *declarator,
	      location_t loc)
{
  ਬਣਤਰ c_parm *ret = XOBNEW (&parser_obstack, ਬਣਤਰ c_parm);
  ret->specs = specs;
  ret->attrs = attrs;
  ret->declarator = declarator;
  ret->loc = loc;
  ਵਾਪਸ ret;
}

/* Return a declarator with nested attributes.  TARGET is the inner
   declarator to which these attributes apply.  ATTRS are the
   attributes.  */

ਬਣਤਰ c_declarator *
build_attrs_declarator (ਰੁੱਖ attrs, ਬਣਤਰ c_declarator *ਨਿਸ਼ਾਨਾ)
{
  ਬਣਤਰ c_declarator *ret = XOBNEW (&parser_obstack, ਬਣਤਰ c_declarator);
  ret->ਕਿਸਮ = cdk_attrs;
  ret->declarator = ਨਿਸ਼ਾਨਾ;
  ret->u.attrs = attrs;
  ਵਾਪਸ ret;
}

/* Return a declarator for a function with arguments specified by ARGS
   and return type specified by TARGET.  */

ਬਣਤਰ c_declarator *
build_function_declarator (ਬਣਤਰ c_arg_info *ਦਲੀਲਾਂ,
			   ਬਣਤਰ c_declarator *ਨਿਸ਼ਾਨਾ)
{
  ਬਣਤਰ c_declarator *ret = XOBNEW (&parser_obstack, ਬਣਤਰ c_declarator);
  ret->ਕਿਸਮ = cdk_function;
  ret->declarator = ਨਿਸ਼ਾਨਾ;
  ret->u.arg_info = ਦਲੀਲਾਂ;
  ਵਾਪਸ ret;
}

/* Return a declarator for the identifier IDENT (which may be
   NULL_TREE for an abstract declarator).  */

ਬਣਤਰ c_declarator *
build_id_declarator (ਰੁੱਖ ident)
{
  ਬਣਤਰ c_declarator *ret = XOBNEW (&parser_obstack, ਬਣਤਰ c_declarator);
  ret->ਕਿਸਮ = cdk_id;
  ret->declarator = 0;
  ret->u.id.id = ident;
  ret->u.id.attrs = NULL_ਰੁੱਖ;
  /* Default value - may get reset to a more precise location. */
  ret->id_loc = ਨਿਵੇਸ਼_location;
  ਵਾਪਸ ret;
}

/* Return something to represent absolute declarators containing a *.
   TARGET is the absolute declarator that the * contains.
   TYPE_QUALS_ATTRS is a structure for type qualifiers and attributes
   to apply to the pointer type.  */

ਬਣਤਰ c_declarator *
make_ਸੂਚਕ_declarator (ਬਣਤਰ c_declspecs *type_quals_attrs,
			 ਬਣਤਰ c_declarator *ਨਿਸ਼ਾਨਾ)
{
  ਰੁੱਖ attrs;
  ਪੂਰਨ quals = 0;
  ਬਣਤਰ c_declarator *itarget = ਨਿਸ਼ਾਨਾ;
  ਬਣਤਰ c_declarator *ret = XOBNEW (&parser_obstack, ਬਣਤਰ c_declarator);
  ਜੇ (type_quals_attrs)
    {
      attrs = type_quals_attrs->attrs;
      quals = quals_from_declspecs (type_quals_attrs);
      ਜੇ (attrs != NULL_ਰੁੱਖ)
	itarget = build_attrs_declarator (attrs, ਨਿਸ਼ਾਨਾ);
    }
  ret->ਕਿਸਮ = cdk_ਸੂਚਕ;
  ret->declarator = itarget;
  ret->u.ਸੂਚਕ_quals = quals;
  ਵਾਪਸ ret;
}

/* Return a pointer to a structure for an empty list of declaration
   specifiers.  */

ਬਣਤਰ c_declspecs *
build_null_declspecs (ਖਾਲੀ)
{
  ਬਣਤਰ c_declspecs *ret = XOBNEW (&parser_obstack, ਬਣਤਰ c_declspecs);
  memset (ret, 0, ਆਕਾਰ *ret);
  ret->align_log = -1;
  ret->typespec_ਸ਼ਬਦ = cts_none;
  ret->storage_class = csc_none;
  ret->ਵਿਅੰਜਕ_const_operands = ਸੱਚ;
  ret->typespec_ਕਿਸਮ = ctsk_none;
  ret->ਪਤਾ_space = ADDR_SPACE_GENERIC;
  ਵਾਪਸ ret;
}

/* Add the address space ADDRSPACE to the declaration specifiers
   SPECS, returning SPECS.  */

ਬਣਤਰ c_declspecs *
declspecs_ਜੋੜੋ_addrspace (location_t location,
			 ਬਣਤਰ c_declspecs *specs, addr_space_t as)
{
  specs->non_sc_ਵੇਖਿਆ_p = ਸੱਚ;
  specs->declspecs_ਵੇਖਿਆ_p = ਸੱਚ;
  specs->non_std_attrs_ਵੇਖਿਆ_p = ਸੱਚ;

  ਜੇ (!ADDR_SPACE_GENERIC_P (specs->ਪਤਾ_space)
      && specs->ਪਤਾ_space != as)
    error ("incompatible address space qualifiers %qs and %qs",
	   c_addr_space_name (as),
	   c_addr_space_name (specs->ਪਤਾ_space));
  ਨਹੀਂਤਾਂ
    {
      specs->ਪਤਾ_space = as;
      specs->locations[cdw_ਪਤਾ_space] = location;
    }
  ਵਾਪਸ specs;
}

/* Add the type qualifier QUAL to the declaration specifiers SPECS,
   returning SPECS.  */

ਬਣਤਰ c_declspecs *
declspecs_ਜੋੜੋ_qual (location_t loc,
		    ਬਣਤਰ c_declspecs *specs, ਰੁੱਖ qual)
{
  ਗਿਣਤੀ rid i;
  ਤਾਰਕਿਕ dupe = ਝੂਠ;
  specs->non_sc_ਵੇਖਿਆ_p = ਸੱਚ;
  specs->declspecs_ਵੇਖਿਆ_p = ਸੱਚ;
  specs->non_std_attrs_ਵੇਖਿਆ_p = ਸੱਚ;
  gcc_assert (ਰੁੱਖ_ਕੋਡ (qual) == IDENTIFIER_ਗੰਢ
	      && C_IS_RESERVED_ਸ਼ਬਦ (qual));
  i = C_RID_ਕੋਡ (qual);
  location_t prev_loc = UNKNOWN_LOCATION;
  ਚੋਣ (i)
    {
    ਹਾਲਤ RID_CONST:
      dupe = specs->const_p;
      specs->const_p = ਸੱਚ;
      prev_loc = specs->locations[cdw_const];
      specs->locations[cdw_const] = loc;
      ਰੋਕੋ;
    ਹਾਲਤ RID_VOLATILE:
      dupe = specs->volatile_p;
      specs->volatile_p = ਸੱਚ;
      prev_loc = specs->locations[cdw_volatile];
      specs->locations[cdw_volatile] = loc;
      ਰੋਕੋ;
    ਹਾਲਤ RID_RESTRICT:
      dupe = specs->restrict_p;
      specs->restrict_p = ਸੱਚ;
      prev_loc = specs->locations[cdw_restrict];
      specs->locations[cdw_restrict] = loc;
      ਰੋਕੋ;
    ਹਾਲਤ RID_ATOMIC:
      dupe = specs->atomic_p;
      specs->atomic_p = ਸੱਚ;
      prev_loc = specs->locations[cdw_atomic];
      specs->locations[cdw_atomic] = loc;
      ਰੋਕੋ;
    ਮੂਲ:
      gcc_unreachable ();
    }
  ਜੇ (dupe)
    {
      ਤਾਰਕਿਕ warned = pedwarn_c90 (loc, OPT_Wpedantic,
				 "duplicate %qE declaration specifier", qual);
      ਜੇ (!warned
	  && warn_duplicate_decl_specifier
	  && prev_loc >= RESERVED_LOCATION_ਗਿਣਤੀ
	  && !from_macro_expansion_at (prev_loc)
	  && !from_macro_expansion_at (loc))
	warning_at (loc, OPT_Wduplicate_decl_specifier,
		    "duplicate %qE declaration specifier", qual);
    }
  ਵਾਪਸ specs;
}

/* Add the type specifier TYPE to the declaration specifiers SPECS,
   returning SPECS.  */

ਬਣਤਰ c_declspecs *
declspecs_ਜੋੜੋ_type (location_t loc, ਬਣਤਰ c_declspecs *specs,
		    ਬਣਤਰ c_typespec spec)
{
  ਰੁੱਖ type = spec.spec;
  specs->non_sc_ਵੇਖਿਆ_p = ਸੱਚ;
  specs->declspecs_ਵੇਖਿਆ_p = ਸੱਚ;
  specs->non_std_attrs_ਵੇਖਿਆ_p = ਸੱਚ;
  specs->typespec_ਕਿਸਮ = spec.ਕਿਸਮ;
  ਜੇ (ਰੁੱਖ_DEPRECATED (type))
    specs->deprecated_p = ਸੱਚ;
  ਜੇ (ਰੁੱਖ_UNAVAILABLE (type))
    specs->unavailable_p = ਸੱਚ;

  /* As a type specifier is present, "auto" must be used as a storage
     class specifier, not for type deduction.  */
  ਜੇ (specs->c23_auto_p)
    {
      specs->c23_auto_p = ਝੂਠ;
      ਜੇ (specs->storage_class != csc_none)
	error ("multiple storage classes in declaration specifiers");
      ਨਹੀਂਤਾਂ ਜੇ (specs->thread_p)
	error ("%qs used with %<auto%>",
	       specs->thread_gnu_p ? "__thread" : "_Thread_local");
      ਨਹੀਂਤਾਂ ਜੇ (specs->constexpr_p)
	/* auto may only be used with another storage class specifier,
	   such as constexpr, if the type is inferred.  */
	error ("%<auto%> used with %<constexpr%>");
      ਨਹੀਂਤਾਂ
	specs->storage_class = csc_auto;
    }

  /* Handle type specifier keywords.  */
  ਜੇ (ਰੁੱਖ_ਕੋਡ (type) == IDENTIFIER_ਗੰਢ
      && C_IS_RESERVED_ਸ਼ਬਦ (type)
      && C_RID_ਕੋਡ (type) != RID_CXX_COMPAT_WARN)
    {
      ਗਿਣਤੀ rid i = C_RID_ਕੋਡ (type);
      ਜੇ (specs->type)
	{
	  error_at (loc, "two or more data types in declaration specifiers");
	  ਵਾਪਸ specs;
	}
      ਜੇ ((ਪੂਰਨ) i <= (ਪੂਰਨ) RID_ਆਖਰੀ_MODIFIER)
	{
	  /* "long", "short", "signed", "unsigned", "_Complex" or "_Sat".  */
	  ਤਾਰਕਿਕ dupe = ਝੂਠ;
	  ਚੋਣ (i)
	    {
	    ਹਾਲਤ RID_LONG:
	      ਜੇ (specs->long_long_p)
		{
		  error_at (loc, "%<long long long%> is too long for GCC");
		  ਰੋਕੋ;
		}
	      ਜੇ (specs->long_p)
		{
		  ਜੇ (specs->typespec_ਸ਼ਬਦ == cts_double)
		    {
		      error_at (loc,
				"both %qs and %qs in declaration specifiers",
				"long long", "double");
		      ਰੋਕੋ;
		    }
		  pedwarn_c90 (loc, OPT_Wlong_long,
			       "ISO C90 does not support %<long long%>");
		  specs->long_long_p = 1;
		  specs->locations[cdw_long_long] = loc;
		  ਰੋਕੋ;
		}
	      ਜੇ (specs->short_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "short");
	      ਨਹੀਂਤਾਂ ਜੇ (specs->typespec_ਸ਼ਬਦ == cts_auto_type)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "__auto_type");
	      ਨਹੀਂਤਾਂ ਜੇ (specs->typespec_ਸ਼ਬਦ == cts_void)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "void");
	      ਨਹੀਂਤਾਂ ਜੇ (specs->typespec_ਸ਼ਬਦ == cts_int_n)
		error_at (loc,
			  "both %qs and %<__int%d%> in declaration specifiers",
			  "long", int_n_ਅੰਕੜੇ[specs->u.int_n_idx].bitsize);
	      ਨਹੀਂਤਾਂ ਜੇ (specs->typespec_ਸ਼ਬਦ == cts_bool)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "_Bool");
	      ਨਹੀਂਤਾਂ ਜੇ (specs->typespec_ਸ਼ਬਦ == cts_bitint)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "_BitInt");
	      ਨਹੀਂਤਾਂ ਜੇ (specs->typespec_ਸ਼ਬਦ == cts_char)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "char");
	      ਨਹੀਂਤਾਂ ਜੇ (specs->typespec_ਸ਼ਬਦ == cts_float)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "float");
	      ਨਹੀਂਤਾਂ ਜੇ (specs->typespec_ਸ਼ਬਦ == cts_floatn_nx)
		error_at (loc,
			  "both %qs and %<_Float%d%s%> in declaration "
			  "specifiers", "long",
			  floatn_nx_types[specs->u.floatn_nx_idx].n,
			  floatn_nx_types[specs->u.floatn_nx_idx].extended
			  ? "x"
			  : "");
	      ਨਹੀਂਤਾਂ ਜੇ (specs->typespec_ਸ਼ਬਦ == cts_dfloat32)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "_Decimal32");
	      ਨਹੀਂਤਾਂ ਜੇ (specs->typespec_ਸ਼ਬਦ == cts_dfloat64)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "_Decimal64");
	      ਨਹੀਂਤਾਂ ਜੇ (specs->typespec_ਸ਼ਬਦ == cts_dfloat128)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "_Decimal128");
	      ਨਹੀਂਤਾਂ ਜੇ (specs->typespec_ਸ਼ਬਦ == cts_dfloat64x)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "_Decimal64x");
	      ਨਹੀਂਤਾਂ
		{
		  specs->long_p = ਸੱਚ;
		  specs->locations[cdw_long] = loc;
		}
	      ਰੋਕੋ;
	    ਹਾਲਤ RID_SHORT:
	      dupe = specs->short_p;
	      ਜੇ (specs->long_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "short");
	      ਨਹੀਂਤਾਂ ਜੇ (specs->typespec_ਸ਼ਬਦ == cts_auto_type)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "__auto_type");
	      ਨਹੀਂਤਾਂ ਜੇ (specs->typespec_ਸ਼ਬਦ == cts_void)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "void");
	      ਨਹੀਂਤਾਂ ਜੇ (specs->typespec_ਸ਼ਬਦ == cts_int_n)
		error_at (loc,
			  "both %qs and %<__int%d%> in declaration specifiers",
			  "short", int_n_ਅੰਕੜੇ[specs->u.int_n_idx].bitsize);
	      ਨਹੀਂਤਾਂ ਜੇ (specs->typespec_ਸ਼ਬਦ == cts_bool)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "_Bool");
	      ਨਹੀਂਤਾਂ ਜੇ (specs->typespec_ਸ਼ਬਦ == cts_bitint)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "_BitInt");
	      ਨਹੀਂਤਾਂ ਜੇ (specs->typespec_ਸ਼ਬਦ == cts_char)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "char");
	      ਨਹੀਂਤਾਂ ਜੇ (specs->typespec_ਸ਼ਬਦ == cts_float)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "float");
	      ਨਹੀਂਤਾਂ ਜੇ (specs->typespec_ਸ਼ਬਦ == cts_double)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "double");
	      ਨਹੀਂਤਾਂ ਜੇ (specs->typespec_ਸ਼ਬਦ == cts_floatn_nx)
		error_at (loc,
			  "both %qs and %<_Float%d%s%> in declaration "
			  "specifiers", "short",
			  floatn_nx_types[specs->u.floatn_nx_idx].n,
			  floatn_nx_types[specs->u.floatn_nx_idx].extended
			  ? "x"
			  : "");
	      ਨਹੀਂਤਾਂ ਜੇ (specs->typespec_ਸ਼ਬਦ == cts_dfloat32)
                error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "_Decimal32");
	      ਨਹੀਂਤਾਂ ਜੇ (specs->typespec_ਸ਼ਬਦ == cts_dfloat64)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "_Decimal64");
	      ਨਹੀਂਤਾਂ ਜੇ (specs->typespec_ਸ਼ਬਦ == cts_dfloat128)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "_Decimal128");
	      ਨਹੀਂਤਾਂ ਜੇ (specs->typespec_ਸ਼ਬਦ == cts_dfloat64x)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "_Decimal64x");
	      ਨਹੀਂਤਾਂ
		{
		  specs->short_p = ਸੱਚ;
		  specs->locations[cdw_short] = loc;
		}
	      ਰੋਕੋ;
	    ਹਾਲਤ RID_SIGNED:
	      dupe = specs->signed_p;
	      ਜੇ (specs->unsigned_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "unsigned");
	      ਨਹੀਂਤਾਂ ਜੇ (specs->typespec_ਸ਼ਬਦ == cts_auto_type)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "__auto_type");
	      ਨਹੀਂਤਾਂ ਜੇ (specs->typespec_ਸ਼ਬਦ == cts_void)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "void");
	      ਨਹੀਂਤਾਂ ਜੇ (specs->typespec_ਸ਼ਬਦ == cts_bool)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "_Bool");
	      ਨਹੀਂਤਾਂ ਜੇ (specs->typespec_ਸ਼ਬਦ == cts_float)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "float");
	      ਨਹੀਂਤਾਂ ਜੇ (specs->typespec_ਸ਼ਬਦ == cts_double)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "double");
	      ਨਹੀਂਤਾਂ ਜੇ (specs->typespec_ਸ਼ਬਦ == cts_floatn_nx)
		error_at (loc,
			  "both %qs and %<_Float%d%s%> in declaration "
			  "specifiers", "signed",
			  floatn_nx_types[specs->u.floatn_nx_idx].n,
			  floatn_nx_types[specs->u.floatn_nx_idx].extended
			  ? "x"
			  : "");
	      ਨਹੀਂਤਾਂ ਜੇ (specs->typespec_ਸ਼ਬਦ == cts_dfloat32)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "_Decimal32");
	      ਨਹੀਂਤਾਂ ਜੇ (specs->typespec_ਸ਼ਬਦ == cts_dfloat64)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "_Decimal64");
	      ਨਹੀਂਤਾਂ ਜੇ (specs->typespec_ਸ਼ਬਦ == cts_dfloat128)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "_Decimal128");
	      ਨਹੀਂਤਾਂ ਜੇ (specs->typespec_ਸ਼ਬਦ == cts_dfloat64x)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "_Decimal64x");
	      ਨਹੀਂਤਾਂ
		{
		  specs->signed_p = ਸੱਚ;
		  specs->locations[cdw_signed] = loc;
		}
	      ਰੋਕੋ;
	    ਹਾਲਤ RID_UNSIGNED:
	      dupe = specs->unsigned_p;
	      ਜੇ (specs->signed_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "unsigned");
	      ਨਹੀਂਤਾਂ ਜੇ (specs->typespec_ਸ਼ਬਦ == cts_auto_type)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "__auto_type");
	      ਨਹੀਂਤਾਂ ਜੇ (specs->typespec_ਸ਼ਬਦ == cts_void)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "void");
	      ਨਹੀਂਤਾਂ ਜੇ (specs->typespec_ਸ਼ਬਦ == cts_bool)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "_Bool");
	      ਨਹੀਂਤਾਂ ਜੇ (specs->typespec_ਸ਼ਬਦ == cts_float)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "float");
	      ਨਹੀਂਤਾਂ ਜੇ (specs->typespec_ਸ਼ਬਦ == cts_double)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "double");
	      ਨਹੀਂਤਾਂ ਜੇ (specs->typespec_ਸ਼ਬਦ == cts_floatn_nx)
		error_at (loc,
			  "both %qs and %<_Float%d%s%> in declaration "
			  "specifiers", "unsigned",
			  floatn_nx_types[specs->u.floatn_nx_idx].n,
			  floatn_nx_types[specs->u.floatn_nx_idx].extended
			  ? "x"
			  : "");
              ਨਹੀਂਤਾਂ ਜੇ (specs->typespec_ਸ਼ਬਦ == cts_dfloat32)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "_Decimal32");
	      ਨਹੀਂਤਾਂ ਜੇ (specs->typespec_ਸ਼ਬਦ == cts_dfloat64)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "_Decimal64");
	      ਨਹੀਂਤਾਂ ਜੇ (specs->typespec_ਸ਼ਬਦ == cts_dfloat128)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "_Decimal128");
	      ਨਹੀਂਤਾਂ ਜੇ (specs->typespec_ਸ਼ਬਦ == cts_dfloat64x)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "_Decimal64x");
	      ਨਹੀਂਤਾਂ
		{
		  specs->unsigned_p = ਸੱਚ;
		  specs->locations[cdw_unsigned] = loc;
		}
	      ਰੋਕੋ;
	    ਹਾਲਤ RID_COMPLEX:
	      dupe = specs->complex_p;
	      ਜੇ (!ਵਿੱਚ_system_ਸਿਰਲੇਖ_at (loc))
		pedwarn_c90 (loc, OPT_Wpedantic,
			     "ISO C90 does not support complex types");
	      ਜੇ (specs->typespec_ਸ਼ਬਦ == cts_auto_type)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "__auto_type");
	      ਨਹੀਂਤਾਂ ਜੇ (specs->typespec_ਸ਼ਬਦ == cts_void)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "void");
	      ਨਹੀਂਤਾਂ ਜੇ (specs->typespec_ਸ਼ਬਦ == cts_bool)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "_Bool");
	      ਨਹੀਂਤਾਂ ਜੇ (specs->typespec_ਸ਼ਬਦ == cts_bitint)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "_BitInt");
              ਨਹੀਂਤਾਂ ਜੇ (specs->typespec_ਸ਼ਬਦ == cts_dfloat32)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "_Decimal32");
	      ਨਹੀਂਤਾਂ ਜੇ (specs->typespec_ਸ਼ਬਦ == cts_dfloat64)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "_Decimal64");
	      ਨਹੀਂਤਾਂ ਜੇ (specs->typespec_ਸ਼ਬਦ == cts_dfloat128)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "_Decimal128");
	      ਨਹੀਂਤਾਂ ਜੇ (specs->typespec_ਸ਼ਬਦ == cts_dfloat64x)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "_Decimal64x");
	      ਨਹੀਂਤਾਂ ਜੇ (specs->typespec_ਸ਼ਬਦ == cts_fract)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "_Fract");
	      ਨਹੀਂਤਾਂ ਜੇ (specs->typespec_ਸ਼ਬਦ == cts_accum)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "_Accum");
	      ਨਹੀਂਤਾਂ ਜੇ (specs->saturating_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "_Sat");
	      ਨਹੀਂਤਾਂ
		{
		  specs->complex_p = ਸੱਚ;
		  specs->locations[cdw_complex] = loc;
		}
	      ਰੋਕੋ;
	    ਹਾਲਤ RID_SAT:
	      dupe = specs->saturating_p;
	      pedwarn (loc, OPT_Wpedantic,
		       "ISO C does not support saturating types");
	      ਜੇ (specs->typespec_ਸ਼ਬਦ == cts_int_n)
		error_at (loc,
			  "both %qs and %<__int%d%> in declaration specifiers",
			  "_Sat", int_n_ਅੰਕੜੇ[specs->u.int_n_idx].bitsize);
	      ਨਹੀਂਤਾਂ ਜੇ (specs->typespec_ਸ਼ਬਦ == cts_auto_type)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "__auto_type");
	      ਨਹੀਂਤਾਂ ਜੇ (specs->typespec_ਸ਼ਬਦ == cts_void)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "void");
	      ਨਹੀਂਤਾਂ ਜੇ (specs->typespec_ਸ਼ਬਦ == cts_bool)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "_Bool");
	      ਨਹੀਂਤਾਂ ਜੇ (specs->typespec_ਸ਼ਬਦ == cts_bitint)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "_BitInt");
	      ਨਹੀਂਤਾਂ ਜੇ (specs->typespec_ਸ਼ਬਦ == cts_char)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "char");
	      ਨਹੀਂਤਾਂ ਜੇ (specs->typespec_ਸ਼ਬਦ == cts_int)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "int");
	      ਨਹੀਂਤਾਂ ਜੇ (specs->typespec_ਸ਼ਬਦ == cts_float)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "float");
	      ਨਹੀਂਤਾਂ ਜੇ (specs->typespec_ਸ਼ਬਦ == cts_double)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "double");
	      ਨਹੀਂਤਾਂ ਜੇ (specs->typespec_ਸ਼ਬਦ == cts_floatn_nx)
		error_at (loc,
			  "both %qs and %<_Float%d%s%> in declaration "
			  "specifiers", "_Sat",
			  floatn_nx_types[specs->u.floatn_nx_idx].n,
			  floatn_nx_types[specs->u.floatn_nx_idx].extended
			  ? "x"
			  : "");
              ਨਹੀਂਤਾਂ ਜੇ (specs->typespec_ਸ਼ਬਦ == cts_dfloat32)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "_Decimal32");
	      ਨਹੀਂਤਾਂ ਜੇ (specs->typespec_ਸ਼ਬਦ == cts_dfloat64)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "_Decimal64");
	      ਨਹੀਂਤਾਂ ਜੇ (specs->typespec_ਸ਼ਬਦ == cts_dfloat128)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "_Decimal128");
	      ਨਹੀਂਤਾਂ ਜੇ (specs->typespec_ਸ਼ਬਦ == cts_dfloat64x)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "_Decimal64x");
	      ਨਹੀਂਤਾਂ ਜੇ (specs->complex_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "complex");
	      ਨਹੀਂਤਾਂ
		{
		  specs->saturating_p = ਸੱਚ;
		  specs->locations[cdw_saturating] = loc;
		}
	      ਰੋਕੋ;
	    ਮੂਲ:
	      gcc_unreachable ();
	    }

	  ਜੇ (dupe)
	    error_at (loc, "duplicate %qE", type);

	  ਵਾਪਸ specs;
	}
      ਨਹੀਂਤਾਂ
	{
	  /* "void", "_Bool", "char", "int", "float", "double",
	     "_FloatN", "_FloatNx", "_Decimal32", "__intN",
	     "_Decimal64", "_Decimal128", "_Fract", "_Accum", "_BitInt(N)" or
	     "__auto_type".  */
	  ਜੇ (specs->typespec_ਸ਼ਬਦ != cts_none)
	    {
	      ਜੇ (i == RID_BOOL)
		{
		  auto_diagnostic_ਸਮੂਹ d;
		  ਜੇ (specs->storage_class == csc_typedef)
		    error_at (loc,
			      "%qs cannot be defined via %<typedef%>",
			      IDENTIFIER_ਸੂਚਕ (type));
		  ਨਹੀਂਤਾਂ
		    error_at (loc,
			      "%qs cannot be used here",
			      IDENTIFIER_ਸੂਚਕ (type));
		  ਜੋੜੋ_note_about_new_keyword (loc, type);
		}
	      ਨਹੀਂਤਾਂ
		error_at (loc,
			  "two or more data types in declaration specifiers");
	      ਵਾਪਸ specs;
	    }
	  ਚੋਣ (i)
	    {
	    ਹਾਲਤ RID_AUTO_TYPE:
	      ਜੇ (specs->long_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "__auto_type");
	      ਨਹੀਂਤਾਂ ਜੇ (specs->short_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "__auto_type");
	      ਨਹੀਂਤਾਂ ਜੇ (specs->signed_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "__auto_type");
	      ਨਹੀਂਤਾਂ ਜੇ (specs->unsigned_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "__auto_type");
	      ਨਹੀਂਤਾਂ ਜੇ (specs->complex_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "__auto_type");
	      ਨਹੀਂਤਾਂ ਜੇ (specs->saturating_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "__auto_type");
	      ਨਹੀਂਤਾਂ
		{
		  specs->typespec_ਸ਼ਬਦ = cts_auto_type;
		  specs->locations[cdw_typespec] = loc;
		}
	      ਵਾਪਸ specs;
	    ਹਾਲਤ RID_INT_N_0:
	    ਹਾਲਤ RID_INT_N_1:
	    ਹਾਲਤ RID_INT_N_2:
	    ਹਾਲਤ RID_INT_N_3:
	      specs->u.int_n_idx = i - RID_INT_N_0;
	      ਜੇ (!ਵਿੱਚ_system_ਸਿਰਲੇਖ_at (ਨਿਵੇਸ਼_location)
		  /* If the INT_N type ends in "__", and so is of the format
		     "__intN__", don't pedwarn.  */
		  && (ਲੜੀ_ਤੁਲਨਾ (IDENTIFIER_ਸੂਚਕ (type)
			       + (IDENTIFIER_ਲੰਮਾਈ (type) - 2), "__", 2) != 0))
		pedwarn (loc, OPT_Wpedantic,
			 "ISO C does not support %<__int%d%> types",
			 int_n_ਅੰਕੜੇ[specs->u.int_n_idx].bitsize);

	      ਜੇ (specs->long_p)
		error_at (loc,
			  "both %<__int%d%> and %qs in declaration specifiers",
			  int_n_ਅੰਕੜੇ[specs->u.int_n_idx].bitsize, "long");
	      ਨਹੀਂਤਾਂ ਜੇ (specs->saturating_p)
		error_at (loc,
			  "both %qs and %<__int%d%> in declaration specifiers",
			  "_Sat", int_n_ਅੰਕੜੇ[specs->u.int_n_idx].bitsize);
	      ਨਹੀਂਤਾਂ ਜੇ (specs->short_p)
		error_at (loc,
			  "both %<__int%d%> and %qs in declaration specifiers",
			  int_n_ਅੰਕੜੇ[specs->u.int_n_idx].bitsize, "short");
	      ਨਹੀਂਤਾਂ ਜੇ (! int_n_enabled_p[specs->u.int_n_idx])
		{
		  specs->typespec_ਸ਼ਬਦ = cts_int_n;
		  error_at (loc,
			    "%<__int%d%> is not supported on this target",
			    int_n_ਅੰਕੜੇ[specs->u.int_n_idx].bitsize);
		}
	      ਨਹੀਂਤਾਂ
		{
		  specs->typespec_ਸ਼ਬਦ = cts_int_n;
		  specs->locations[cdw_typespec] = loc;
		}
	      ਵਾਪਸ specs;
	    ਹਾਲਤ RID_VOID:
	      ਜੇ (specs->long_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "void");
	      ਨਹੀਂਤਾਂ ਜੇ (specs->short_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "void");
	      ਨਹੀਂਤਾਂ ਜੇ (specs->signed_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "void");
	      ਨਹੀਂਤਾਂ ਜੇ (specs->unsigned_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "void");
	      ਨਹੀਂਤਾਂ ਜੇ (specs->complex_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "void");
	      ਨਹੀਂਤਾਂ ਜੇ (specs->saturating_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "void");
	      ਨਹੀਂਤਾਂ
		{
		  specs->typespec_ਸ਼ਬਦ = cts_void;
		  specs->locations[cdw_typespec] = loc;
		}
	      ਵਾਪਸ specs;
	    ਹਾਲਤ RID_BOOL:
	      ਜੇ (!ਵਿੱਚ_system_ਸਿਰਲੇਖ_at (loc))
		pedwarn_c90 (loc, OPT_Wpedantic,
			     "ISO C90 does not support boolean types");
	      ਜੇ (specs->long_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "_Bool");
	      ਨਹੀਂਤਾਂ ਜੇ (specs->short_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "_Bool");
	      ਨਹੀਂਤਾਂ ਜੇ (specs->signed_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "_Bool");
	      ਨਹੀਂਤਾਂ ਜੇ (specs->unsigned_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "_Bool");
	      ਨਹੀਂਤਾਂ ਜੇ (specs->complex_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "_Bool");
	      ਨਹੀਂਤਾਂ ਜੇ (specs->saturating_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "_Bool");
	      ਨਹੀਂਤਾਂ
		{
		  specs->typespec_ਸ਼ਬਦ = cts_bool;
		  specs->locations[cdw_typespec] = loc;
		}
	      ਵਾਪਸ specs;
	    ਹਾਲਤ RID_CHAR:
	      ਜੇ (specs->long_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "char");
	      ਨਹੀਂਤਾਂ ਜੇ (specs->short_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "char");
	      ਨਹੀਂਤਾਂ ਜੇ (specs->saturating_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "char");
	      ਨਹੀਂਤਾਂ
		{
		  specs->typespec_ਸ਼ਬਦ = cts_char;
		  specs->locations[cdw_typespec] = loc;
		}
	      ਵਾਪਸ specs;
	    ਹਾਲਤ RID_INT:
	      ਜੇ (specs->saturating_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "int");
	      ਨਹੀਂਤਾਂ
		{
		  specs->typespec_ਸ਼ਬਦ = cts_int;
		  specs->locations[cdw_typespec] = loc;
		}
	      ਵਾਪਸ specs;
	    ਹਾਲਤ RID_FLOAT:
	      ਜੇ (specs->long_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "float");
	      ਨਹੀਂਤਾਂ ਜੇ (specs->short_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "float");
	      ਨਹੀਂਤਾਂ ਜੇ (specs->signed_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "float");
	      ਨਹੀਂਤਾਂ ਜੇ (specs->unsigned_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "float");
	      ਨਹੀਂਤਾਂ ਜੇ (specs->saturating_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "float");
	      ਨਹੀਂਤਾਂ
		{
		  specs->typespec_ਸ਼ਬਦ = cts_float;
		  specs->locations[cdw_typespec] = loc;
		}
	      ਵਾਪਸ specs;
	    ਹਾਲਤ RID_DOUBLE:
	      ਜੇ (specs->long_long_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long long", "double");
	      ਨਹੀਂਤਾਂ ਜੇ (specs->short_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "double");
	      ਨਹੀਂਤਾਂ ਜੇ (specs->signed_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "double");
	      ਨਹੀਂਤਾਂ ਜੇ (specs->unsigned_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "double");
	      ਨਹੀਂਤਾਂ ਜੇ (specs->saturating_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "double");
	      ਨਹੀਂਤਾਂ
		{
		  specs->typespec_ਸ਼ਬਦ = cts_double;
		  specs->locations[cdw_typespec] = loc;
		}
	      ਵਾਪਸ specs;
	    CASE_RID_FLOATN_NX:
	      specs->u.floatn_nx_idx = i - RID_FLOATN_NX_ਪਹਿਲਾ;
	      ਜੇ (!ਵਿੱਚ_system_ਸਿਰਲੇਖ_at (ਨਿਵੇਸ਼_location))
		pedwarn_c11 (loc, OPT_Wpedantic,
			     "ISO C does not support the %<_Float%d%s%> type"
			     " before C23",
			     floatn_nx_types[specs->u.floatn_nx_idx].n,
			     floatn_nx_types[specs->u.floatn_nx_idx].extended
			     ? "x"
			     : "");

	      ਜੇ (specs->long_p)
		error_at (loc,
			  "both %qs and %<_Float%d%s%> in declaration "
			  "specifiers", "long",
			  floatn_nx_types[specs->u.floatn_nx_idx].n,
			  floatn_nx_types[specs->u.floatn_nx_idx].extended
			  ? "x"
			  : "");
	      ਨਹੀਂਤਾਂ ਜੇ (specs->short_p)
		error_at (loc,
			  "both %qs and %<_Float%d%s%> in declaration "
			  "specifiers", "short",
			  floatn_nx_types[specs->u.floatn_nx_idx].n,
			  floatn_nx_types[specs->u.floatn_nx_idx].extended
			  ? "x"
			  : "");
	      ਨਹੀਂਤਾਂ ਜੇ (specs->signed_p)
		error_at (loc,
			  "both %qs and %<_Float%d%s%> in declaration "
			  "specifiers", "signed",
			  floatn_nx_types[specs->u.floatn_nx_idx].n,
			  floatn_nx_types[specs->u.floatn_nx_idx].extended
			  ? "x"
			  : "");
	      ਨਹੀਂਤਾਂ ਜੇ (specs->unsigned_p)
		error_at (loc,
			  "both %qs and %<_Float%d%s%> in declaration "
			  "specifiers", "unsigned",
			  floatn_nx_types[specs->u.floatn_nx_idx].n,
			  floatn_nx_types[specs->u.floatn_nx_idx].extended
			  ? "x"
			  : "");
	      ਨਹੀਂਤਾਂ ਜੇ (specs->saturating_p)
		error_at (loc,
			  "both %qs and %<_Float%d%s%> in declaration "
			  "specifiers", "_Sat",
			  floatn_nx_types[specs->u.floatn_nx_idx].n,
			  floatn_nx_types[specs->u.floatn_nx_idx].extended
			  ? "x"
			  : "");
	      ਨਹੀਂਤਾਂ ਜੇ (FLOATN_NX_TYPE_ਗੰਢ (specs->u.floatn_nx_idx) == NULL_ਰੁੱਖ)
		{
		  specs->typespec_ਸ਼ਬਦ = cts_floatn_nx;
		  error_at (loc,
			    "%<_Float%d%s%> is not supported on this target",
			    floatn_nx_types[specs->u.floatn_nx_idx].n,
			    floatn_nx_types[specs->u.floatn_nx_idx].extended
			    ? "x"
			    : "");
		}
	      ਨਹੀਂਤਾਂ
		{
		  specs->typespec_ਸ਼ਬਦ = cts_floatn_nx;
		  specs->locations[cdw_typespec] = loc;
		}
	      ਵਾਪਸ specs;
	    ਹਾਲਤ RID_DFLOAT32:
	    ਹਾਲਤ RID_DFLOAT64:
	    ਹਾਲਤ RID_DFLOAT128:
	    ਹਾਲਤ RID_DFLOAT64X:
	      {
		ਅਚਲ ਅੱਖਰ *str;
		ਜੇ (i == RID_DFLOAT32)
		  str = "_Decimal32";
		ਨਹੀਂਤਾਂ ਜੇ (i == RID_DFLOAT64)
		  str = "_Decimal64";
		ਨਹੀਂਤਾਂ ਜੇ (i == RID_DFLOAT128)
		  str = "_Decimal128";
		ਨਹੀਂਤਾਂ
		  str = "_Decimal64x";
		ਜੇ (specs->long_long_p)
		  error_at (loc,
			    "both %qs and %qs in declaration specifiers",
			    "long long", str);
		ਜੇ (specs->long_p)
		  error_at (loc,
			    "both %qs and %qs in declaration specifiers",
			    "long", str);
		ਨਹੀਂਤਾਂ ਜੇ (specs->short_p)
		  error_at (loc,
			    "both %qs and %qs in declaration specifiers",
			    "short", str);
		ਨਹੀਂਤਾਂ ਜੇ (specs->signed_p)
		  error_at (loc,
			    "both %qs and %qs in declaration specifiers",
			    "signed", str);
		ਨਹੀਂਤਾਂ ਜੇ (specs->unsigned_p)
		  error_at (loc,
			    "both %qs and %qs in declaration specifiers",
			    "unsigned", str);
                ਨਹੀਂਤਾਂ ਜੇ (specs->complex_p)
                  error_at (loc,
			    "both %qs and %qs in declaration specifiers",
			    "complex", str);
                ਨਹੀਂਤਾਂ ਜੇ (specs->saturating_p)
                  error_at (loc,
			    "both %qs and %qs in declaration specifiers",
			    "_Sat", str);
		ਨਹੀਂਤਾਂ ਜੇ (i == RID_DFLOAT32)
		  specs->typespec_ਸ਼ਬਦ = cts_dfloat32;
		ਨਹੀਂਤਾਂ ਜੇ (i == RID_DFLOAT64)
		  specs->typespec_ਸ਼ਬਦ = cts_dfloat64;
		ਨਹੀਂਤਾਂ ਜੇ (i == RID_DFLOAT128)
		  specs->typespec_ਸ਼ਬਦ = cts_dfloat128;
		ਨਹੀਂਤਾਂ
		  specs->typespec_ਸ਼ਬਦ = cts_dfloat64x;
		specs->locations[cdw_typespec] = loc;
	      }
	      ਜੇ (!targetm.decimal_float_supported_p ())
		error_at (loc,
			  "decimal floating-point not supported "
			  "for this target");
	      pedwarn_c11 (loc, OPT_Wpedantic,
			   "ISO C does not support decimal floating-point "
			   "before C23");
	      ਵਾਪਸ specs;
	    ਹਾਲਤ RID_FRACT:
	    ਹਾਲਤ RID_ACCUM:
	      {
		ਅਚਲ ਅੱਖਰ *str;
		ਜੇ (i == RID_FRACT)
		  str = "_Fract";
		ਨਹੀਂਤਾਂ
		  str = "_Accum";
                ਜੇ (specs->complex_p)
                  error_at (loc,
			    "both %qs and %qs in declaration specifiers",
			    "complex", str);
		ਨਹੀਂਤਾਂ ਜੇ (i == RID_FRACT)
		    specs->typespec_ਸ਼ਬਦ = cts_fract;
		ਨਹੀਂਤਾਂ
		    specs->typespec_ਸ਼ਬਦ = cts_accum;
		specs->locations[cdw_typespec] = loc;
	      }
	      ਜੇ (!targetm.fixed_ਬਿੰਦੂ_supported_p ())
		error_at (loc,
			  "fixed-point types not supported for this target");
	      pedwarn (loc, OPT_Wpedantic,
		       "ISO C does not support fixed-point types");
	      ਵਾਪਸ specs;
	    ਹਾਲਤ RID_BITINT:
	      ਜੇ (specs->long_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "_BitInt");
	      ਨਹੀਂਤਾਂ ਜੇ (specs->short_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "_BitInt");
	      ਨਹੀਂਤਾਂ ਜੇ (specs->complex_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "_BitInt");
	      ਨਹੀਂਤਾਂ ਜੇ (specs->saturating_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "_BitInt");
	      ਨਹੀਂਤਾਂ
		{
		  specs->typespec_ਸ਼ਬਦ = cts_bitint;
		  specs->locations[cdw_typespec] = loc;
		  specs->u.bitint_prec = -1;
		  ਜੇ (error_ਸੰਕਾਰਜ_p (spec.ਵਿਅੰਜਕ))
		    ਵਾਪਸ specs;
		  ਜੇ (ਰੁੱਖ_ਕੋਡ (spec.ਵਿਅੰਜਕ) != INTEGER_CST
		      || !INTEGRAL_TYPE_P (ਰੁੱਖ_TYPE (spec.ਵਿਅੰਜਕ)))
		    {
		      error_at (loc, "%<_BitInt%> argument is not an integer "
				     "constant expression");
		      ਵਾਪਸ specs;
		    }
		  ਜੇ (ਰੁੱਖ_int_cst_sgn (spec.ਵਿਅੰਜਕ) <= 0)
		    {
		      error_at (loc, "%<_BitInt%> argument %qE is not a "
				     "positive integer constant expression",
				spec.ਵਿਅੰਜਕ);
		      ਵਾਪਸ specs;
		    }
		  ਜੇ (wi::ਮੰਜ਼ਿਲ_widest (spec.ਵਿਅੰਜਕ) > WIDE_INT_MAX_PRECISION - 1)
		    {
		      error_at (loc, "%<_BitInt%> argument %qE is larger than "
				     "%<BITINT_MAXWIDTH%> %qd",
				spec.ਵਿਅੰਜਕ, (ਪੂਰਨ) WIDE_INT_MAX_PRECISION - 1);
		      ਵਾਪਸ specs;
		    }
		  specs->u.bitint_prec = ਰੁੱਖ_ਮੰਜ਼ਿਲ_uhwi (spec.ਵਿਅੰਜਕ);
		  ਬਣਤਰ bitint_info info;
		  ਜੇ (!targetm.c.bitint_type_info (specs->u.bitint_prec,
						   &info))
		    {
		      sorry_at (loc, "%<_BitInt(%d)%> is not supported on "
				     "this target", specs->u.bitint_prec);
		      specs->u.bitint_prec = -1;
		      ਵਾਪਸ specs;
		    }
		}
	      ਵਾਪਸ specs;
	    ਮੂਲ:
	      /* ObjC reserved word "id", handled below.  */
	      ਰੋਕੋ;
	    }
	}
    }

  /* Now we have a typedef (a TYPE_DECL node), an identifier (some
     form of ObjC type, cases such as "int" and "long" being handled
     above), a TYPE (struct, union, enum and typeof specifiers) or an
     ERROR_MARK.  In none of these cases may there have previously
     been any type specifiers.  */
  ਜੇ (specs->type || specs->typespec_ਸ਼ਬਦ != cts_none
      || specs->long_p || specs->short_p || specs->signed_p
      || specs->unsigned_p || specs->complex_p)
    error_at (loc, "two or more data types in declaration specifiers");
  ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਕੋਡ (type) == TYPE_DECL)
    {
      specs->type = ਰੁੱਖ_TYPE (type);
      ਜੇ (ਰੁੱਖ_TYPE (type) != error_mark_ਗੰਢ)
	{
	  mark_decl_ਵਰਤਿਆ (type, ਝੂਠ);
	  specs->decl_attr = DECL_ਗੁਣ (type);
	  specs->typedef_p = ਸੱਚ;
	  specs->explicit_signed_p = C_TYPEDEF_EXPLICITLY_SIGNED (type);
	  specs->locations[cdw_typedef] = loc;

	  /* If this typedef name is defined in a struct, then a C++
	     lookup would return a different value.  */
	  ਜੇ (warn_cxx_compat
	      && I_ਚਿੰਨ੍ਹ_BINDING (DECL_NAME (type))->ਵਿੱਚ_struct)
	    warning_at (loc, OPT_Wc___compat,
			"C++ lookup of %qD would return a field, not a type",
			type);

	  /* If we are parsing a struct, record that a struct field
	     used a typedef.  */
	  ਜੇ (warn_cxx_compat && struct_parse_info != ਨਿਰਾ)
	    struct_parse_info->typedefs_ਵੇਖਿਆ.ਸੁਰੱਖਿਅਤ_ਧੱਕੋ (type);
	}
    }
  ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਕੋਡ (type) == IDENTIFIER_ਗੰਢ)
    {
      ਰੁੱਖ t = lookup_name (type);
      ਜੇ (!t || ਰੁੱਖ_ਕੋਡ (t) != TYPE_DECL)
	error_at (loc, "%qE fails to be a typedef or built in type", type);
      ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_TYPE (t) == error_mark_ਗੰਢ)
	;
      ਨਹੀਂਤਾਂ
	{
	  specs->type = ਰੁੱਖ_TYPE (t);
	  specs->locations[cdw_typespec] = loc;
	}
    }
  ਨਹੀਂਤਾਂ
    {
      ਜੇ (ਰੁੱਖ_ਕੋਡ (type) != ERROR_MARK)
	{
	  ਜੇ (spec.ਕਿਸਮ == ctsk_typeof)
	    {
	      specs->typedef_p = ਸੱਚ;
	      specs->locations[cdw_typedef] = loc;
	    }

	  ਜੇ (ਰੁੱਖ_ਕੋਡ (type) == ਰਿਕਾਰਡ_TYPE || ਰੁੱਖ_ਕੋਡ (type) == UNION_TYPE
	      || ਰੁੱਖ_ਕੋਡ (type) == ENUMERAL_TYPE)
	    mark_decl_ਵਰਤਿਆ (TYPE_STUB_DECL (type), ਝੂਠ);

	  ਜੇ (spec.ਵਿਅੰਜਕ)
	    {
	      ਰੁੱਖ ਵਿਅੰਜਕ = save_ਵਿਅੰਜਕ (fold_convert (void_type_ਗੰਢ, spec.ਵਿਅੰਜਕ));
	      ਜੇ (specs->ਵਿਅੰਜਕ)
		specs->ਵਿਅੰਜਕ = build2 (COMPOUND_ਵਿਅੰਜਕ, ਰੁੱਖ_TYPE (ਵਿਅੰਜਕ),
				      specs->ਵਿਅੰਜਕ, ਵਿਅੰਜਕ);
	      ਨਹੀਂਤਾਂ
		specs->ਵਿਅੰਜਕ = ਵਿਅੰਜਕ;
	      specs->ਵਿਅੰਜਕ_const_operands &= spec.ਵਿਅੰਜਕ_const_operands;
	    }
	}
      specs->type = type;
      ਜੇ (spec.has_enum_type_specifier
	  && spec.ਕਿਸਮ != ctsk_tagdef)
	specs->enum_type_specifier_ref_p = ਸੱਚ;
    }

  ਵਾਪਸ specs;
}

/* Add the storage class specifier or function specifier SCSPEC to the
   declaration specifiers SPECS, returning SPECS.  */

ਬਣਤਰ c_declspecs *
declspecs_ਜੋੜੋ_scspec (location_t loc,
		      ਬਣਤਰ c_declspecs *specs,
		      ਰੁੱਖ scspec)
{
  ਗਿਣਤੀ rid i;
  ਗਿਣਤੀ c_storage_class n = csc_none;
  ਤਾਰਕਿਕ dupe = ਝੂਠ;
  specs->declspecs_ਵੇਖਿਆ_p = ਸੱਚ;
  specs->non_std_attrs_ਵੇਖਿਆ_p = ਸੱਚ;
  gcc_assert (ਰੁੱਖ_ਕੋਡ (scspec) == IDENTIFIER_ਗੰਢ
	      && C_IS_RESERVED_ਸ਼ਬਦ (scspec));
  i = C_RID_ਕੋਡ (scspec);
  ਜੇ (specs->non_sc_ਵੇਖਿਆ_p)
    warning (OPT_Wold_style_declaration,
             "%qE is not at beginning of declaration", scspec);
  ਚੋਣ (i)
    {
    ਹਾਲਤ RID_INLINE:
      /* C99 permits duplicate inline.  Although of doubtful utility,
	 it seems simplest to permit it in gnu89 mode as well, as
	 there is also little utility in maintaining this as a
	 difference between gnu89 and C99 inline.  */
      dupe = ਝੂਠ;
      specs->inline_p = ਸੱਚ;
      specs->locations[cdw_inline] = loc;
      ਰੋਕੋ;
    ਹਾਲਤ RID_NORETURN:
      /* Duplicate _Noreturn is permitted.  */
      dupe = ਝੂਠ;
      specs->noreturn_p = ਸੱਚ;
      specs->locations[cdw_noreturn] = loc;
      ਰੋਕੋ;
    ਹਾਲਤ RID_THREAD:
      dupe = specs->thread_p;
      ਜੇ (specs->storage_class == csc_auto)
	error ("%qE used with %<auto%>", scspec);
      ਨਹੀਂਤਾਂ ਜੇ (specs->storage_class == csc_ਰਜਿਸਟਰ)
	error ("%qE used with %<register%>", scspec);
      ਨਹੀਂਤਾਂ ਜੇ (specs->storage_class == csc_typedef)
	error ("%qE used with %<typedef%>", scspec);
      ਨਹੀਂਤਾਂ ਜੇ (specs->constexpr_p)
	error ("%qE used with %<constexpr%>", scspec);
      ਨਹੀਂਤਾਂ
	{
	  specs->thread_p = ਸੱਚ;
	  specs->thread_gnu_p = (strcmp (IDENTIFIER_ਸੂਚਕ (scspec),
					 "__thread") == 0);
	  /* A diagnostic is not required for the use of this
	     identifier in the implementation namespace; only diagnose
	     it for the C11 spelling because of existing code using
	     the other spelling.  */
	  ਜੇ (!specs->thread_gnu_p)
	    {
	      ਜੇ (flag_isoc99)
		pedwarn_c99 (loc, OPT_Wpedantic,
			     "ISO C99 does not support %qE", scspec);
	      ਨਹੀਂਤਾਂ
		pedwarn_c99 (loc, OPT_Wpedantic,
			     "ISO C90 does not support %qE", scspec);
	    }
	  specs->locations[cdw_thread] = loc;
	}
      ਰੋਕੋ;
    ਹਾਲਤ RID_AUTO:
      ਜੇ (flag_isoc23
	  && specs->typespec_ਕਿਸਮ == ctsk_none
	  && specs->storage_class != csc_typedef)
	{
	  /* "auto" potentially used for type deduction.  */
	  ਜੇ (specs->c23_auto_p)
	    error ("duplicate %qE", scspec);
	  specs->c23_auto_p = ਸੱਚ;
	  ਵਾਪਸ specs;
	}
      n = csc_auto;
      /* auto may only be used with another storage class specifier,
	 such as constexpr, if the type is inferred.  */
      ਜੇ (specs->constexpr_p)
	error ("%qE used with %<constexpr%>", scspec);
      ਰੋਕੋ;
    ਹਾਲਤ RID_EXTERN:
      n = csc_extern;
      /* Diagnose "__thread extern".  */
      ਜੇ (specs->thread_p && specs->thread_gnu_p)
	error ("%<__thread%> before %<extern%>");
      ਰੋਕੋ;
    ਹਾਲਤ RID_ਰਜਿਸਟਰ:
      n = csc_ਰਜਿਸਟਰ;
      ਰੋਕੋ;
    ਹਾਲਤ RID_STATIC:
      n = csc_static;
      /* Diagnose "__thread static".  */
      ਜੇ (specs->thread_p && specs->thread_gnu_p)
	error ("%<__thread%> before %<static%>");
      ਰੋਕੋ;
    ਹਾਲਤ RID_TYPEDEF:
      n = csc_typedef;
      ਜੇ (specs->c23_auto_p)
	{
	  error ("%<typedef%> used with %<auto%>");
	  specs->c23_auto_p = ਝੂਠ;
	}
      ਰੋਕੋ;
    ਹਾਲਤ RID_CONSTEXPR:
      dupe = specs->constexpr_p;
      ਜੇ (specs->storage_class == csc_extern)
	error ("%qE used with %<extern%>", scspec);
      ਨਹੀਂਤਾਂ ਜੇ (specs->storage_class == csc_typedef)
	error ("%qE used with %<typedef%>", scspec);
      ਨਹੀਂਤਾਂ ਜੇ (specs->storage_class == csc_auto)
	/* auto may only be used with another storage class specifier,
	   such as constexpr, if the type is inferred.  */
	error ("%qE used with %<auto%>", scspec);
      ਨਹੀਂਤਾਂ ਜੇ (specs->thread_p)
	error ("%qE used with %qs", scspec,
	       specs->thread_gnu_p ? "__thread" : "_Thread_local");
      ਨਹੀਂਤਾਂ
	specs->constexpr_p = ਸੱਚ;
      ਰੋਕੋ;
    ਮੂਲ:
      gcc_unreachable ();
    }
  ਜੇ (n != csc_none && n == specs->storage_class)
    dupe = ਸੱਚ;
  ਜੇ (dupe)
    {
      ਜੇ (i == RID_THREAD)
	error ("duplicate %<_Thread_local%> or %<__thread%>");
      ਨਹੀਂਤਾਂ
	error ("duplicate %qE", scspec);
    }
  ਜੇ (n != csc_none)
    {
      ਜੇ (specs->storage_class != csc_none && n != specs->storage_class)
	{
	  error ("multiple storage classes in declaration specifiers");
	}
      ਨਹੀਂਤਾਂ
	{
	  specs->storage_class = n;
	  specs->locations[cdw_storage_class] = loc;
	  ਜੇ (n != csc_extern && n != csc_static && specs->thread_p)
	    {
	      error ("%qs used with %qE",
		     specs->thread_gnu_p ? "__thread" : "_Thread_local",
		     scspec);
	      specs->thread_p = ਝੂਠ;
	    }
	  ਜੇ (n != csc_auto && n != csc_ਰਜਿਸਟਰ && n != csc_static
	      && specs->constexpr_p)
	    {
	      error ("%<constexpr%> used with %qE", scspec);
	      specs->constexpr_p = ਝੂਠ;
	    }
	}
    }
  ਵਾਪਸ specs;
}

/* Add the attributes ATTRS to the declaration specifiers SPECS,
   returning SPECS.  */

ਬਣਤਰ c_declspecs *
declspecs_ਜੋੜੋ_attrs (location_t loc, ਬਣਤਰ c_declspecs *specs, ਰੁੱਖ attrs)
{
  specs->attrs = chainon (attrs, specs->attrs);
  specs->locations[cdw_ਗੁਣ] = loc;
  specs->declspecs_ਵੇਖਿਆ_p = ਸੱਚ;
  /* In the case of standard attributes at the start of the
     declaration, the caller will reset this.  */
  specs->non_std_attrs_ਵੇਖਿਆ_p = ਸੱਚ;
  ਵਾਪਸ specs;
}

/* Add an _Alignas specifier (expression ALIGN, or type whose
   alignment is ALIGN) to the declaration specifiers SPECS, returning
   SPECS.  */
ਬਣਤਰ c_declspecs *
declspecs_ਜੋੜੋ_alignas (location_t loc,
		       ਬਣਤਰ c_declspecs *specs, ਰੁੱਖ align)
{
  specs->alignas_p = ਸੱਚ;
  specs->locations[cdw_alignas] = loc;
  ਜੇ (align == error_mark_ਗੰਢ)
    ਵਾਪਸ specs;

  /* Only accept the alignment if it's valid and greater than
     the current one.  Zero is invalid but by C11 required to
     be silently ignored.  */
  ਪੂਰਨ align_log = check_user_alignment (align, ਝੂਠ, /* warn_zero = */ਝੂਠ);
  ਜੇ (align_log > specs->align_log)
    specs->align_log = align_log;
  ਵਾਪਸ specs;
}

/* Combine "long", "short", "signed", "unsigned" and "_Complex" type
   specifiers with any other type specifier to determine the resulting
   type.  This is where ISO C checks on complex types are made, since
   "_Complex long" is a prefix of the valid ISO C type "_Complex long
   double".  Also apply postfix standard attributes to modify the type.  */

ਬਣਤਰ c_declspecs *
ਅੰਤ_declspecs (ਬਣਤਰ c_declspecs *specs)
{
  /* If a type was specified as a whole, we have no modifiers and are
     done.  */
  ਜੇ (specs->type != NULL_ਰੁੱਖ)
    {
      gcc_assert (!specs->long_p && !specs->long_long_p && !specs->short_p
		  && !specs->signed_p && !specs->unsigned_p
		  && !specs->complex_p && !specs->c23_auto_p);

      /* Set a dummy type.  */
      ਜੇ (ਰੁੱਖ_ਕੋਡ (specs->type) == ERROR_MARK)
        specs->type = integer_type_ਗੰਢ;
      ਜਾਓ handle_postfix_attrs;
    }

  /* If none of "void", "_Bool", "char", "int", "float" or "double"
     has been specified, treat it as "int" unless "_Complex" is
     present and there are no other specifiers.  If we just have
     "_Complex", it is equivalent to "_Complex double", but e.g.
     "_Complex short" is equivalent to "_Complex short int".  */
  ਜੇ (specs->typespec_ਸ਼ਬਦ == cts_none)
    {
      ਜੇ (specs->saturating_p)
	{
	  error_at (specs->locations[cdw_saturating],
		    "%<_Sat%> is used without %<_Fract%> or %<_Accum%>");
	  ਜੇ (!targetm.fixed_ਬਿੰਦੂ_supported_p ())
	    error_at (specs->locations[cdw_saturating],
		      "fixed-point types not supported for this target");
	  specs->typespec_ਸ਼ਬਦ = cts_fract;
	}
      ਨਹੀਂਤਾਂ ਜੇ (specs->long_p || specs->short_p
	       || specs->signed_p || specs->unsigned_p)
	{
	  specs->typespec_ਸ਼ਬਦ = cts_int;
	}
      ਨਹੀਂਤਾਂ ਜੇ (specs->complex_p)
	{
	  specs->typespec_ਸ਼ਬਦ = cts_double;
	  pedwarn (specs->locations[cdw_complex], OPT_Wpedantic,
		   "ISO C does not support plain %<complex%> meaning "
		   "%<double complex%>");
	}
      ਨਹੀਂਤਾਂ ਜੇ (specs->c23_auto_p)
	{
	  /* Type to be filled in later, including applying postfix
	     attributes.  This warning only actually appears for
	     -Wc11-c23-compat in C23 mode; in older modes, there may
	     be a warning or pedwarn for implicit "int" instead, or
	     other errors for use of auto at file scope.  */
	  pedwarn_c11 (ਨਿਵੇਸ਼_location, OPT_Wpedantic,
		       "ISO C does not support %<auto%> type deduction "
		       "before C23");
	  ਵਾਪਸ specs;
	}
      ਨਹੀਂਤਾਂ
	{
	  specs->typespec_ਸ਼ਬਦ = cts_int;
	  specs->default_int_p = ਸੱਚ;
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
  ਚੋਣ (specs->typespec_ਸ਼ਬਦ)
    {
    ਹਾਲਤ cts_auto_type:
      gcc_assert (!specs->long_p && !specs->short_p
		  && !specs->signed_p && !specs->unsigned_p
		  && !specs->complex_p);
      /* Type to be filled in later.  */
      ਜੇ (specs->postfix_attrs)
	error ("%<__auto_type%> followed by %<[[]]%> attributes");
      ਰੋਕੋ;
    ਹਾਲਤ cts_void:
      gcc_assert (!specs->long_p && !specs->short_p
		  && !specs->signed_p && !specs->unsigned_p
		  && !specs->complex_p);
      specs->type = void_type_ਗੰਢ;
      ਰੋਕੋ;
    ਹਾਲਤ cts_bool:
      gcc_assert (!specs->long_p && !specs->short_p
		  && !specs->signed_p && !specs->unsigned_p
		  && !specs->complex_p);
      specs->type = boolean_type_ਗੰਢ;
      ਰੋਕੋ;
    ਹਾਲਤ cts_char:
      gcc_assert (!specs->long_p && !specs->short_p);
      gcc_assert (!(specs->signed_p && specs->unsigned_p));
      ਜੇ (specs->signed_p)
	specs->type = signed_char_type_ਗੰਢ;
      ਨਹੀਂਤਾਂ ਜੇ (specs->unsigned_p)
	specs->type = unsigned_char_type_ਗੰਢ;
      ਨਹੀਂਤਾਂ
	specs->type = char_type_ਗੰਢ;
      ਜੇ (specs->complex_p)
	{
	  pedwarn (specs->locations[cdw_complex], OPT_Wpedantic,
		   "ISO C does not support complex integer types");
	  specs->type = build_complex_type (specs->type);
	}
      ਰੋਕੋ;
    ਹਾਲਤ cts_int_n:
      gcc_assert (!specs->long_p && !specs->short_p && !specs->long_long_p);
      gcc_assert (!(specs->signed_p && specs->unsigned_p));
      ਜੇ (! int_n_enabled_p[specs->u.int_n_idx])
	specs->type = integer_type_ਗੰਢ;
      ਨਹੀਂਤਾਂ
	specs->type = (specs->unsigned_p
		       ? int_n_trees[specs->u.int_n_idx].unsigned_type
		       : int_n_trees[specs->u.int_n_idx].signed_type);
      ਜੇ (specs->complex_p)
	{
	  pedwarn (specs->locations[cdw_complex], OPT_Wpedantic,
		   "ISO C does not support complex integer types");
	  specs->type = build_complex_type (specs->type);
	}
      ਰੋਕੋ;
    ਹਾਲਤ cts_int:
      gcc_assert (!(specs->long_p && specs->short_p));
      gcc_assert (!(specs->signed_p && specs->unsigned_p));
      ਜੇ (specs->long_long_p)
	specs->type = (specs->unsigned_p
		       ? long_long_unsigned_type_ਗੰਢ
		       : long_long_integer_type_ਗੰਢ);
      ਨਹੀਂਤਾਂ ਜੇ (specs->long_p)
	specs->type = (specs->unsigned_p
		       ? long_unsigned_type_ਗੰਢ
		       : long_integer_type_ਗੰਢ);
      ਨਹੀਂਤਾਂ ਜੇ (specs->short_p)
	specs->type = (specs->unsigned_p
		       ? short_unsigned_type_ਗੰਢ
		       : short_integer_type_ਗੰਢ);
      ਨਹੀਂਤਾਂ
	specs->type = (specs->unsigned_p
		       ? unsigned_type_ਗੰਢ
		       : integer_type_ਗੰਢ);
      ਜੇ (specs->complex_p)
	{
	  pedwarn (specs->locations[cdw_complex], OPT_Wpedantic,
		   "ISO C does not support complex integer types");
	  specs->type = build_complex_type (specs->type);
	}
      ਰੋਕੋ;
    ਹਾਲਤ cts_float:
      gcc_assert (!specs->long_p && !specs->short_p
		  && !specs->signed_p && !specs->unsigned_p);
      specs->type = (specs->complex_p
		     ? complex_float_type_ਗੰਢ
		     : float_type_ਗੰਢ);
      ਰੋਕੋ;
    ਹਾਲਤ cts_double:
      gcc_assert (!specs->long_long_p && !specs->short_p
		  && !specs->signed_p && !specs->unsigned_p);
      ਜੇ (specs->long_p)
	{
	  specs->type = (specs->complex_p
			 ? complex_long_double_type_ਗੰਢ
			 : long_double_type_ਗੰਢ);
	}
      ਨਹੀਂਤਾਂ
	{
	  specs->type = (specs->complex_p
			 ? complex_double_type_ਗੰਢ
			 : double_type_ਗੰਢ);
	}
      ਰੋਕੋ;
    ਹਾਲਤ cts_floatn_nx:
      gcc_assert (!specs->long_p && !specs->short_p
		  && !specs->signed_p && !specs->unsigned_p);
      ਜੇ (FLOATN_NX_TYPE_ਗੰਢ (specs->u.floatn_nx_idx) == NULL_ਰੁੱਖ)
	specs->type = integer_type_ਗੰਢ;
      ਨਹੀਂਤਾਂ ਜੇ (specs->complex_p)
	specs->type = COMPLEX_FLOATN_NX_TYPE_ਗੰਢ (specs->u.floatn_nx_idx);
      ਨਹੀਂਤਾਂ
	specs->type = FLOATN_NX_TYPE_ਗੰਢ (specs->u.floatn_nx_idx);
      ਰੋਕੋ;
    ਹਾਲਤ cts_dfloat32:
    ਹਾਲਤ cts_dfloat64:
    ਹਾਲਤ cts_dfloat128:
    ਹਾਲਤ cts_dfloat64x:
      gcc_assert (!specs->long_p && !specs->long_long_p && !specs->short_p
		  && !specs->signed_p && !specs->unsigned_p && !specs->complex_p);
      ਜੇ (!targetm.decimal_float_supported_p ())
	specs->type = integer_type_ਗੰਢ;
      ਨਹੀਂਤਾਂ ਜੇ (specs->typespec_ਸ਼ਬਦ == cts_dfloat32)
	specs->type = dfloat32_type_ਗੰਢ;
      ਨਹੀਂਤਾਂ ਜੇ (specs->typespec_ਸ਼ਬਦ == cts_dfloat64)
	specs->type = dfloat64_type_ਗੰਢ;
      ਨਹੀਂਤਾਂ ਜੇ (specs->typespec_ਸ਼ਬਦ == cts_dfloat128)
	specs->type = dfloat128_type_ਗੰਢ;
      ਨਹੀਂਤਾਂ
	specs->type = dfloat64x_type_ਗੰਢ;
      ਰੋਕੋ;
    ਹਾਲਤ cts_fract:
      gcc_assert (!specs->complex_p);
      ਜੇ (!targetm.fixed_ਬਿੰਦੂ_supported_p ())
	specs->type = integer_type_ਗੰਢ;
      ਨਹੀਂਤਾਂ ਜੇ (specs->saturating_p)
	{
	  ਜੇ (specs->long_long_p)
	    specs->type = specs->unsigned_p
			  ? sat_unsigned_long_long_fract_type_ਗੰਢ
			  : sat_long_long_fract_type_ਗੰਢ;
	  ਨਹੀਂਤਾਂ ਜੇ (specs->long_p)
	    specs->type = specs->unsigned_p
			  ? sat_unsigned_long_fract_type_ਗੰਢ
			  : sat_long_fract_type_ਗੰਢ;
	  ਨਹੀਂਤਾਂ ਜੇ (specs->short_p)
	    specs->type = specs->unsigned_p
			  ? sat_unsigned_short_fract_type_ਗੰਢ
			  : sat_short_fract_type_ਗੰਢ;
	  ਨਹੀਂਤਾਂ
	    specs->type = specs->unsigned_p
			  ? sat_unsigned_fract_type_ਗੰਢ
			  : sat_fract_type_ਗੰਢ;
	}
      ਨਹੀਂਤਾਂ
	{
	  ਜੇ (specs->long_long_p)
	    specs->type = specs->unsigned_p
			  ? unsigned_long_long_fract_type_ਗੰਢ
			  : long_long_fract_type_ਗੰਢ;
	  ਨਹੀਂਤਾਂ ਜੇ (specs->long_p)
	    specs->type = specs->unsigned_p
			  ? unsigned_long_fract_type_ਗੰਢ
			  : long_fract_type_ਗੰਢ;
	  ਨਹੀਂਤਾਂ ਜੇ (specs->short_p)
	    specs->type = specs->unsigned_p
			  ? unsigned_short_fract_type_ਗੰਢ
			  : short_fract_type_ਗੰਢ;
	  ਨਹੀਂਤਾਂ
	    specs->type = specs->unsigned_p
			  ? unsigned_fract_type_ਗੰਢ
			  : fract_type_ਗੰਢ;
	}
      ਰੋਕੋ;
    ਹਾਲਤ cts_accum:
      gcc_assert (!specs->complex_p);
      ਜੇ (!targetm.fixed_ਬਿੰਦੂ_supported_p ())
	specs->type = integer_type_ਗੰਢ;
      ਨਹੀਂਤਾਂ ਜੇ (specs->saturating_p)
	{
	  ਜੇ (specs->long_long_p)
	    specs->type = specs->unsigned_p
			  ? sat_unsigned_long_long_accum_type_ਗੰਢ
			  : sat_long_long_accum_type_ਗੰਢ;
	  ਨਹੀਂਤਾਂ ਜੇ (specs->long_p)
	    specs->type = specs->unsigned_p
			  ? sat_unsigned_long_accum_type_ਗੰਢ
			  : sat_long_accum_type_ਗੰਢ;
	  ਨਹੀਂਤਾਂ ਜੇ (specs->short_p)
	    specs->type = specs->unsigned_p
			  ? sat_unsigned_short_accum_type_ਗੰਢ
			  : sat_short_accum_type_ਗੰਢ;
	  ਨਹੀਂਤਾਂ
	    specs->type = specs->unsigned_p
			  ? sat_unsigned_accum_type_ਗੰਢ
			  : sat_accum_type_ਗੰਢ;
	}
      ਨਹੀਂਤਾਂ
	{
	  ਜੇ (specs->long_long_p)
	    specs->type = specs->unsigned_p
			  ? unsigned_long_long_accum_type_ਗੰਢ
			  : long_long_accum_type_ਗੰਢ;
	  ਨਹੀਂਤਾਂ ਜੇ (specs->long_p)
	    specs->type = specs->unsigned_p
			  ? unsigned_long_accum_type_ਗੰਢ
			  : long_accum_type_ਗੰਢ;
	  ਨਹੀਂਤਾਂ ਜੇ (specs->short_p)
	    specs->type = specs->unsigned_p
			  ? unsigned_short_accum_type_ਗੰਢ
			  : short_accum_type_ਗੰਢ;
	  ਨਹੀਂਤਾਂ
	    specs->type = specs->unsigned_p
			  ? unsigned_accum_type_ਗੰਢ
			  : accum_type_ਗੰਢ;
	}
      ਰੋਕੋ;
    ਹਾਲਤ cts_bitint:
      gcc_assert (!specs->long_p && !specs->short_p
		  && !specs->complex_p);
      ਜੇ (!specs->unsigned_p && specs->u.bitint_prec == 1 && !flag_isoc2y)
	{
	  error_at (specs->locations[cdw_typespec],
		    "%<signed _BitInt%> argument must be at least 2 "
		    "before C2Y");
	  specs->type = integer_type_ਗੰਢ;
	  ਰੋਕੋ;
	}
      ਜੇ (specs->u.bitint_prec == -1)
	specs->type = integer_type_ਗੰਢ;
      ਨਹੀਂਤਾਂ
	{
	  pedwarn_c11 (specs->locations[cdw_typespec], OPT_Wpedantic,
		       "ISO C does not support %<%s_BitInt(%d)%> before C23",
		       specs->unsigned_p ? "unsigned "
		       : specs->signed_p ? "signed " : "",
		       specs->u.bitint_prec);
	  specs->type = build_bitint_type (specs->u.bitint_prec,
					   specs->unsigned_p);
	}
      ਰੋਕੋ;
    ਮੂਲ:
      gcc_unreachable ();
    }
 handle_postfix_attrs:
  ਜੇ (specs->type != ਨਿਰਾ)
    {
      specs->postfix_attrs
	= c_warn_type_ਗੁਣ (specs->type, specs->postfix_attrs);
      decl_ਗੁਣ (&specs->type, specs->postfix_attrs, 0);
      specs->postfix_attrs = NULL_ਰੁੱਖ;
    }

  ਵਾਪਸ specs;
}

/* Perform final processing on one file scope's declarations (or the
   external scope's declarations), GLOBALS.  */

ਸਥਿਰ ਖਾਲੀ
c_write_global_declarations_1 (ਰੁੱਖ globals)
{
  ਰੁੱਖ decl;
  ਤਾਰਕਿਕ reconsider;

  /* Process the decls in the order they were written.  */
  ਲਈ (decl = globals; decl; decl = DECL_CHAIN (decl))
    {
      /* Check for used but undefined static functions using the C
	 standard's definition of "used", and set TREE_NO_WARNING so
	 that check_global_declaration doesn't repeat the check.  */
      ਜੇ (ਰੁੱਖ_ਕੋਡ (decl) == FUNCTION_DECL
	  && DECL_INITIAL (decl) == NULL_ਰੁੱਖ
	  && DECL_EXTERNAL (decl)
	  && !ਰੁੱਖ_ਜਨਤਕ (decl)
	  && !warning_suppressed_p (decl, OPT_Wunused))
	{
	  ਜੇ (C_DECL_ਵਰਤਿਆ (decl))
	    {
	      ਜੇ (pedwarn (ਨਿਵੇਸ਼_location, 0, "%q+F used but never defined",
			   decl))
		suppress_warning (decl, OPT_Wunused);
	    }
	  /* For -Wunused-function warn about unused static prototypes.  */
	  ਨਹੀਂਤਾਂ ਜੇ (warn_ਅਣਵਰਤਿਆ_function
		   && ! DECL_ARTIFICIAL (decl)
		   && warning (OPT_Wunused_function,
			       "%q+F declared %<static%> but never defined",
			       decl))
	    suppress_warning (decl, OPT_Wunused);
	}

      wrapup_global_declaration_1 (decl);
    }

  ਕਰੋ
    {
      reconsider = ਝੂਠ;
      ਲਈ (decl = globals; decl; decl = DECL_CHAIN (decl))
	reconsider |= wrapup_global_declaration_2 (decl);
    }
  ਜਦੋਂ (reconsider);
}

/* Preserve the external declarations scope across a garbage collect.  */
ਸਥਿਰ GTY(()) ਰੁੱਖ ext_ਖੰਡ;

/* Collect all references relevant to SOURCE_FILE.  */

ਸਥਿਰ ਖਾਲੀ
collect_all_refs (ਅਚਲ ਅੱਖਰ *ਸਰੋਤ_file)
{
  ਰੁੱਖ t;
  ਬਿਨਾਨਿਸ਼ਾਨੀ i;

  FOR_EACH_VEC_ELT (*all_translation_units, i, t)
    collect_ada_nodes (ਖੰਡ_VARS (DECL_INITIAL (t)), ਸਰੋਤ_file);

  collect_ada_nodes (ਖੰਡ_VARS (ext_ਖੰਡ), ਸਰੋਤ_file);
}

/* Collect source file references at global level.  */

ਸਥਿਰ ਖਾਲੀ
collect_ਸਰੋਤ_refs (ਖਾਲੀ)
{
  ਰੁੱਖ t;
  ਰੁੱਖ decls;
  ਰੁੱਖ decl;
  ਬਿਨਾਨਿਸ਼ਾਨੀ i;

  FOR_EACH_VEC_ELT (*all_translation_units, i, t)
    {
      decls = DECL_INITIAL (t);
      ਲਈ (decl = ਖੰਡ_VARS (decls); decl; decl = ਰੁੱਖ_CHAIN (decl))
	ਜੇ (!DECL_IS_UNDECLARED_BUILTIN (decl))
	  collect_ਸਰੋਤ_ref (DECL_ਸਰੋਤ_FILE (decl));
    }

  ਲਈ (decl = ਖੰਡ_VARS (ext_ਖੰਡ); decl; decl = ਰੁੱਖ_CHAIN (decl))
    ਜੇ (!DECL_IS_UNDECLARED_BUILTIN (decl))
      collect_ਸਰੋਤ_ref (DECL_ਸਰੋਤ_FILE (decl));
}

/* Free attribute access data that are not needed by the middle end. */

ਸਥਿਰ ਖਾਲੀ
free_attr_access_ਅੰਕੜੇ ()
{
  ਬਣਤਰ cgraph_ਗੰਢ *n;

  /* Iterate over all functions declared in the translation unit.  */
  FOR_EACH_FUNCTION (n)
    {
      ਲਈ (ਰੁੱਖ parm = DECL_ARGUMENTS (n->decl); parm; parm = ਰੁੱਖ_CHAIN (parm))
	ਜੇ (ਰੁੱਖ attrs = DECL_ਗੁਣ (parm))
	  attr_access::free_lang_ਅੰਕੜੇ (attrs);

      ਰੁੱਖ fntype = ਰੁੱਖ_TYPE (n->decl);
      ਜੇ (!fntype || fntype == error_mark_ਗੰਢ)
	ਜਾਰੀ;
      ਰੁੱਖ attrs = TYPE_ਗੁਣ (fntype);
      ਜੇ (!attrs)
	ਜਾਰੀ;

      attr_access::free_lang_ਅੰਕੜੇ (attrs);
    }
}

/* Perform any final parser cleanups and generate initial debugging
   information.  */

ਖਾਲੀ
c_parse_final_cleanups (ਖਾਲੀ)
{
  ਰੁੱਖ t;
  ਬਿਨਾਨਿਸ਼ਾਨੀ i;

  /* We don't want to do this if generating a PCH.  */
  ਜੇ (pch_file)
    ਵਾਪਸ;

  timevar_stop (TV_PHASE_PARSING);
  timevar_ਸ਼ੁਰੂ (TV_PHASE_DEFERRED);

  /* Do the Objective-C stuff.  This is where all the Objective-C
     module stuff gets generated (symtab, class/protocol/selector
     lists etc).  */
  ਜੇ (c_dialect_objc ())
    objc_write_global_declarations ();

  /* Close the external scope.  */
  ext_ਖੰਡ = ਕੱਢੋ_scope ();
  external_scope = 0;
  gcc_assert (!current_scope);

  /* Handle -fdump-ada-spec[-slim]. */
  ਜੇ (flag_dump_ada_spec || flag_dump_ada_spec_slim)
    {
      /* Build a table of files to generate specs for */
      collect_ਸਰੋਤ_ref (main_ਨਿਵੇਸ਼_filename);
      ਜੇ (!flag_dump_ada_spec_slim)
	collect_ਸਰੋਤ_refs ();

      dump_ada_specs (collect_all_refs, ਨਿਰਾ);
    }

  /* Process all file scopes in this compilation, and the external_scope,
     through wrapup_global_declarations.  */
  FOR_EACH_VEC_ELT (*all_translation_units, i, t)
    c_write_global_declarations_1 (ਖੰਡ_VARS (DECL_INITIAL (t)));
  c_write_global_declarations_1 (ਖੰਡ_VARS (ext_ਖੰਡ));

  /* Call this to set cpp_implicit_aliases_done on all nodes.  This is
     important for function multiversioning aliases to get resolved.  */
  symtab->process_same_body_aliases ();

  ਜੇ (!ਵਿੱਚ_lto_p)
    free_attr_access_ਅੰਕੜੇ ();

  timevar_stop (TV_PHASE_DEFERRED);
  timevar_ਸ਼ੁਰੂ (TV_PHASE_PARSING);

  ext_ਖੰਡ = ਨਿਰਾ;
}

/* Register reserved keyword WORD as qualifier for address space AS.  */

ਖਾਲੀ
c_ਰਜਿਸਟਰ_addr_space (ਅਚਲ ਅੱਖਰ *ਸ਼ਬਦ, addr_space_t as)
{
  ਪੂਰਨ rid = RID_ਪਹਿਲਾ_ADDR_SPACE + as;
  ਰੁੱਖ id;

  /* Address space qualifiers are only supported
     in C with GNU extensions enabled.  */
  ਜੇ (c_dialect_objc () || flag_no_asm)
    ਵਾਪਸ;

  id = get_identifier (ਸ਼ਬਦ);
  C_ਸੈੱਟ_RID_ਕੋਡ (id, rid);
  C_IS_RESERVED_ਸ਼ਬਦ (id) = 1;
  ridpointers [rid] = id;
}

/* Return identifier to look up for omp declare reduction.  */

ਰੁੱਖ
c_omp_reduction_id (ਗਿਣਤੀ ਰੁੱਖ_ਕੋਡ_2 reduction_ਕੋਡ, ਰੁੱਖ reduction_id)
{
  ਅਚਲ ਅੱਖਰ *p = ਨਿਰਾ;
  ਚੋਣ (reduction_ਕੋਡ)
    {
    ਹਾਲਤ PLUS_ਵਿਅੰਜਕ: p = "+"; ਰੋਕੋ;
    ਹਾਲਤ MULT_ਵਿਅੰਜਕ: p = "*"; ਰੋਕੋ;
    ਹਾਲਤ MINUS_ਵਿਅੰਜਕ: p = "-"; ਰੋਕੋ;
    ਹਾਲਤ ਦੋਆਧਾਰੀ_ਅੰਕ_AND_ਵਿਅੰਜਕ: p = "&"; ਰੋਕੋ;
    ਹਾਲਤ ਦੋਆਧਾਰੀ_ਅੰਕ_XOR_ਵਿਅੰਜਕ: p = "^"; ਰੋਕੋ;
    ਹਾਲਤ ਦੋਆਧਾਰੀ_ਅੰਕ_IOR_ਵਿਅੰਜਕ: p = "|"; ਰੋਕੋ;
    ਹਾਲਤ TRUTH_ANDIF_ਵਿਅੰਜਕ: p = "&&"; ਰੋਕੋ;
    ਹਾਲਤ TRUTH_ORIF_ਵਿਅੰਜਕ: p = "||"; ਰੋਕੋ;
    ਹਾਲਤ MIN_ਵਿਅੰਜਕ: p = "min"; ਰੋਕੋ;
    ਹਾਲਤ MAX_ਵਿਅੰਜਕ: p = "max"; ਰੋਕੋ;
    ਮੂਲ:
      ਰੋਕੋ;
    }

  ਜੇ (p == ਨਿਰਾ)
    {
      ਜੇ (ਰੁੱਖ_ਕੋਡ (reduction_id) != IDENTIFIER_ਗੰਢ)
	ਵਾਪਸ error_mark_ਗੰਢ;
      p = IDENTIFIER_ਸੂਚਕ (reduction_id);
    }

  ਅਚਲ ਅੱਖਰ ਅਗੇਤਰ[] = "omp declare reduction ";
  ਮਾਪ_t lenp = ਆਕਾਰ (ਅਗੇਤਰ);
  ਮਾਪ_t len = ਲੜੀ_ਲੰਬਾਈ (p);
  ਅੱਖਰ *name = XALLOCAVEC (ਅੱਖਰ, lenp + len);
  ਸਮ੍ਰਿਤੀ_ਨਕਲ (name, ਅਗੇਤਰ, lenp - 1);
  ਸਮ੍ਰਿਤੀ_ਨਕਲ (name + lenp - 1, p, len + 1);
  ਵਾਪਸ get_identifier (name);
}

/* Lookup REDUCTION_ID in the current scope, or create an artificial
   VAR_DECL, bind it into the current scope and return it.  */

ਰੁੱਖ
c_omp_reduction_decl (ਰੁੱਖ reduction_id)
{
  ਬਣਤਰ c_binding *b = I_ਚਿੰਨ੍ਹ_BINDING (reduction_id);
  ਜੇ (b != ਨਿਰਾ && B_ਵਿੱਚ_CURRENT_SCOPE (b))
    ਵਾਪਸ b->decl;

  ਰੁੱਖ decl = build_decl (BUILTINS_LOCATION, VAR_DECL,
			  reduction_id, integer_type_ਗੰਢ);
  DECL_ARTIFICIAL (decl) = 1;
  DECL_EXTERNAL (decl) = 1;
  ਰੁੱਖ_STATIC (decl) = 1;
  ਰੁੱਖ_ਜਨਤਕ (decl) = 0;
  bind (reduction_id, decl, current_scope, ਸੱਚ, ਝੂਠ, BUILTINS_LOCATION);
  ਵਾਪਸ decl;
}

/* Lookup REDUCTION_ID in the first scope where it has entry for TYPE.  */

ਰੁੱਖ
c_omp_reduction_lookup (ਰੁੱਖ reduction_id, ਰੁੱਖ type)
{
  ਬਣਤਰ c_binding *b = I_ਚਿੰਨ੍ਹ_BINDING (reduction_id);
  ਜਦੋਂ (b)
    {
      ਰੁੱਖ t;
      ਲਈ (t = DECL_INITIAL (b->decl); t; t = ਰੁੱਖ_CHAIN (t))
	ਜੇ (comptypes (ਰੁੱਖ_PURPOSE (t), type))
	  ਵਾਪਸ ਰੁੱਖ_ਮੁੱਲ (t);
      b = b->shadowed;
    }
  ਵਾਪਸ error_mark_ਗੰਢ;
}

/* Helper function called via walk_tree, to diagnose invalid
   #pragma omp declare reduction combiners or initializers.  */

ਰੁੱਖ
c_check_omp_declare_reduction_r (ਰੁੱਖ *tp, ਪੂਰਨ *, ਖਾਲੀ *ਅੰਕੜੇ)
{
  ਰੁੱਖ *vars = (ਰੁੱਖ *) ਅੰਕੜੇ;
  ਜੇ (SSA_VAR_P (*tp)
      && !DECL_ARTIFICIAL (*tp)
      && *tp != vars[0]
      && *tp != vars[1])
    {
      location_t loc = DECL_ਸਰੋਤ_LOCATION (vars[0]);
      ਜੇ (strcmp (IDENTIFIER_ਸੂਚਕ (DECL_NAME (vars[0])), "omp_out") == 0)
	error_at (loc, "%<#pragma omp declare reduction%> combiner refers to "
		       "variable %qD which is not %<omp_out%> nor %<omp_in%>",
		  *tp);
      ਨਹੀਂਤਾਂ
	error_at (loc, "%<#pragma omp declare reduction%> initializer refers "
		       "to variable %qD which is not %<omp_priv%> nor "
		       "%<omp_orig%>",
		  *tp);
      ਵਾਪਸ *tp;
    }
  ਵਾਪਸ NULL_ਰੁੱਖ;
}

/* Return identifier to look up for omp declare mapper.  */

ਰੁੱਖ
c_omp_mapper_id (ਰੁੱਖ mapper_id)
{
  ਅਚਲ ਅੱਖਰ *p = ਨਿਰਾ;

  ਅਚਲ ਅੱਖਰ ਅਗੇਤਰ[] = "omp declare mapper ";

  ਜੇ (mapper_id == NULL_ਰੁੱਖ)
    p = "<default>";
  ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਕੋਡ (mapper_id) == IDENTIFIER_ਗੰਢ)
    p = IDENTIFIER_ਸੂਚਕ (mapper_id);
  ਨਹੀਂਤਾਂ
    ਵਾਪਸ error_mark_ਗੰਢ;

  ਮਾਪ_t lenp = ਆਕਾਰ (ਅਗੇਤਰ);
  ਮਾਪ_t len = ਲੜੀ_ਲੰਬਾਈ (p);
  ਅੱਖਰ *name = XALLOCAVEC (ਅੱਖਰ, lenp + len);
  ਸਮ੍ਰਿਤੀ_ਨਕਲ (name, ਅਗੇਤਰ, lenp - 1);
  ਸਮ੍ਰਿਤੀ_ਨਕਲ (name + lenp - 1, p, len + 1);
  ਵਾਪਸ get_identifier (name);
}

/* Lookup MAPPER_ID in the current scope, or create an artificial
   VAR_DECL, bind it into the current scope and return it.  */

ਰੁੱਖ
c_omp_mapper_decl (ਰੁੱਖ mapper_id)
{
  ਬਣਤਰ c_binding *b = I_ਚਿੰਨ੍ਹ_BINDING (mapper_id);
  ਜੇ (b != ਨਿਰਾ && B_ਵਿੱਚ_CURRENT_SCOPE (b))
    ਵਾਪਸ b->decl;

  ਰੁੱਖ decl = build_decl (BUILTINS_LOCATION, VAR_DECL,
			  mapper_id, integer_type_ਗੰਢ);
  DECL_ARTIFICIAL (decl) = 1;
  DECL_EXTERNAL (decl) = 1;
  ਰੁੱਖ_STATIC (decl) = 1;
  ਰੁੱਖ_ਜਨਤਕ (decl) = 0;
  bind (mapper_id, decl, current_scope, ਸੱਚ, ਝੂਠ, BUILTINS_LOCATION);
  ਵਾਪਸ decl;
}

/* Lookup MAPPER_ID in the first scope where it has entry for TYPE.  */

ਰੁੱਖ
c_omp_mapper_lookup (ਰੁੱਖ mapper_id, ਰੁੱਖ type)
{
  ਜੇ (!ਰਿਕਾਰਡ_OR_UNION_TYPE_P (type))
    ਵਾਪਸ NULL_ਰੁੱਖ;

  mapper_id = c_omp_mapper_id (mapper_id);

  ਬਣਤਰ c_binding *b = I_ਚਿੰਨ੍ਹ_BINDING (mapper_id);
  ਜਦੋਂ (b)
    {
      ਰੁੱਖ t;
      ਲਈ (t = DECL_INITIAL (b->decl); t; t = ਰੁੱਖ_CHAIN (t))
	ਜੇ (comptypes (ਰੁੱਖ_PURPOSE (t), type))
	  ਵਾਪਸ ਰੁੱਖ_ਮੁੱਲ (t);
      b = b->shadowed;
    }
  ਵਾਪਸ NULL_ਰੁੱਖ;
}

/* For C, we record a pointer to the mapper itself without wrapping it in an
   artificial function or similar.  So, just return it.  */

ਰੁੱਖ
c_omp_ਕੱਢੋ_mapper_directive (ਰੁੱਖ mapper)
{
  ਵਾਪਸ mapper;
}

/* For now we can handle singleton OMP_ARRAY_SECTIONs with custom mappers, but
   nothing more complicated.  */

ਰੁੱਖ
c_omp_map_array_section (location_t loc, ਰੁੱਖ t)
{
  ਰੁੱਖ ਨੀਵਾਂ = ਰੁੱਖ_ਸੰਕਾਰਜ (t, 1);
  ਰੁੱਖ len = ਰੁੱਖ_ਸੰਕਾਰਜ (t, 2);

  ਜੇ (len && integer_onep (len))
    {
      t = ਰੁੱਖ_ਸੰਕਾਰਜ (t, 0);

      ਜੇ (!ਨੀਵਾਂ)
	ਨੀਵਾਂ = integer_zero_ਗੰਢ;

      t = build_array_ref (loc, t, ਨੀਵਾਂ);
    }

  ਵਾਪਸ t;
}

/* Helper function for below function.  */

ਸਥਿਰ ਰੁੱਖ
c_omp_ਜਾਂਚ_mapper_bindings_r (ਰੁੱਖ *tp, ਪੂਰਨ *walk_subtrees, ਖਾਲੀ *ptr)
{
  ਰੁੱਖ t = *tp;
  omp_mapper_list<ਰੁੱਖ> *mlist = (omp_mapper_list<ਰੁੱਖ> *) ptr;
  ਰੁੱਖ aggr_type = NULL_ਰੁੱਖ;

  ਜੇ (ਰੁੱਖ_ਕੋਡ (t) == SIZEOF_ਵਿਅੰਜਕ
      || ਰੁੱਖ_ਕੋਡ (t) == ALIGNOF_ਵਿਅੰਜਕ)
    {
      *walk_subtrees = 0;
      ਵਾਪਸ NULL_ਰੁੱਖ;
    }

  ਜੇ (ਰੁੱਖ_ਕੋਡ (t) == OMP_CLAUSE)
    ਵਾਪਸ NULL_ਰੁੱਖ;

  ਜੇ (ਰੁੱਖ_ਕੋਡ (t) == COMPONENT_REF
      && ਰਿਕਾਰਡ_OR_UNION_TYPE_P (ਰੁੱਖ_TYPE (ਰੁੱਖ_ਸੰਕਾਰਜ (t, 0))))
    aggr_type = ਰੁੱਖ_TYPE (ਰੁੱਖ_ਸੰਕਾਰਜ (t, 0));
  ਨਹੀਂਤਾਂ ਜੇ ((ਰੁੱਖ_ਕੋਡ (t) == VAR_DECL
	    || ਰੁੱਖ_ਕੋਡ (t) == PARM_DECL
	    || ਰੁੱਖ_ਕੋਡ (t) == ਨਤੀਜਾ_DECL)
	   && ਰਿਕਾਰਡ_OR_UNION_TYPE_P (ਰੁੱਖ_TYPE (t)))
    aggr_type = ਰੁੱਖ_TYPE (t);

  ਜੇ (aggr_type)
    {
      ਰੁੱਖ mapper_fn = c_omp_mapper_lookup (NULL_ਰੁੱਖ, aggr_type);
      ਜੇ (mapper_fn)
	mlist->ਜੋੜੋ_mapper (NULL_ਰੁੱਖ, aggr_type, mapper_fn);
    }

  ਵਾਪਸ NULL_ਰੁੱਖ;
}

/* Scan an offload region's body, and record uses of struct- or union-typed
   variables.  Add _mapper_binding_ fake clauses to *CLAUSES_PTR.  */

ਖਾਲੀ
c_omp_ਜਾਂਚ_mapper_bindings (location_t loc, ਰੁੱਖ *clauses_ptr, ਰੁੱਖ body)
{
  hash_ਸੈੱਟ<omp_name_type<ਰੁੱਖ>> ਵੇਖਿਆ_types;
  auto_vec<ਰੁੱਖ> mappers;
  omp_mapper_list<ਰੁੱਖ> mlist (&ਵੇਖਿਆ_types, &mappers);

  walk_ਰੁੱਖ_without_duplicates (&body, c_omp_ਜਾਂਚ_mapper_bindings_r, &mlist);

  ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ i;
  ਰੁੱਖ mapper;
  FOR_EACH_VEC_ELT (mappers, i, mapper)
    c_omp_ਲੱਭੋ_nested_mappers (&mlist, mapper);

  FOR_EACH_VEC_ELT (mappers, i, mapper)
    {
      ਜੇ (mapper == error_mark_ਗੰਢ)
	ਜਾਰੀ;
      ਰੁੱਖ mapper_name = OMP_DECLARE_MAPPER_ID (mapper);
      ਰੁੱਖ decl = OMP_DECLARE_MAPPER_DECL (mapper);

      ਰੁੱਖ c = build_omp_clause (loc, OMP_CLAUSE__MAPPER_BINDING_);
      OMP_CLAUSE__MAPPER_BINDING__ID (c) = mapper_name;
      OMP_CLAUSE__MAPPER_BINDING__DECL (c) = decl;
      OMP_CLAUSE__MAPPER_BINDING__MAPPER (c) = mapper;

      OMP_CLAUSE_CHAIN (c) = *clauses_ptr;
      *clauses_ptr = c;
    }
}

ਤਾਰਕਿਕ
c_check_ਵਿੱਚ_current_scope (ਰੁੱਖ decl)
{
  ਬਣਤਰ c_binding *b = I_ਚਿੰਨ੍ਹ_BINDING (DECL_NAME (decl));
  ਵਾਪਸ b != ਨਿਰਾ && B_ਵਿੱਚ_CURRENT_SCOPE (b);
}

/* Search for loop or switch names.  BEFORE_LABELS is last statement before
   possible labels and SWITCH_P true for a switch, false for loops.
   Searches through last statements in cur_stmt_list, stops when seeing
   BEFORE_LABELs, or statement other than LABEL_EXPR or CASE_LABEL_EXPR.
   Returns number of loop/switch names found and if any are found, sets
   *LAST_P to the canonical loop/switch name LABEL_DECL.  */

ਪੂਰਨ
c_get_loop_ਨਾਂ (ਰੁੱਖ before_labels, ਤਾਰਕਿਕ switch_p, ਰੁੱਖ *ਆਖਰੀ_p)
{
  *ਆਖਰੀ_p = NULL_ਰੁੱਖ;
  ਜੇ (!building_stmt_list_p ()
      || !STATEMENT_LIST_HAS_LABEL (cur_stmt_list)
      || before_labels == void_list_ਗੰਢ)
    ਵਾਪਸ 0;

  ਪੂਰਨ ret = 0;
  ਰੁੱਖ ਆਖਰੀ = NULL_ਰੁੱਖ;
  ਲਈ (ਰੁੱਖ_stmt_iterator tsi = tsi_ਆਖਰੀ (cur_stmt_list);
       !tsi_ਸਿਰਾ_p (tsi); tsi_prev (&tsi))
    {
      ਰੁੱਖ stmt = tsi_stmt (tsi);
      ਜੇ (stmt == before_labels)
	ਰੋਕੋ;
      ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਕੋਡ (stmt) == LABEL_ਵਿਅੰਜਕ)
	{
	  ਜੇ (ਆਖਰੀ == NULL_ਰੁੱਖ)
	    ਆਖਰੀ = LABEL_ਵਿਅੰਜਕ_LABEL (stmt);
	  ਨਹੀਂਤਾਂ
	    {
	      loop_ਨਾਂ.ਸੁਰੱਖਿਅਤ_ਧੱਕੋ (LABEL_ਵਿਅੰਜਕ_LABEL (stmt));
	      ++ret;
	    }
	}
      ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਕੋਡ (stmt) != CASE_LABEL_ਵਿਅੰਜਕ
	       && ਰੁੱਖ_ਕੋਡ (stmt) != DEBUG_BEGIN_STMT)
	ਰੋਕੋ;
    }
  ਜੇ (ਆਖਰੀ)
    {
      ਜੇ (switch_p)
	C_DECL_SWITCH_NAME (ਆਖਰੀ) = 1;
      ਨਹੀਂਤਾਂ
	C_DECL_LOOP_NAME (ਆਖਰੀ) = 1;
      loop_ਨਾਂ.ਸੁਰੱਖਿਅਤ_ਧੱਕੋ (ਆਖਰੀ);
      ++ret;
      ਜੇ (loop_ਨਾਂ.ਲੰਮਾਈ () > 16)
	{
	  ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ਪਹਿਲਾ = 0, i;
	  ਰੁੱਖ l, c = NULL_ਰੁੱਖ;
	  ਜੇ (loop_ਨਾਂ_hash == ਨਿਰਾ)
	    loop_ਨਾਂ_hash = ਨਵਾਂ decl_ਰੁੱਖ_map (ret);
	  ਨਹੀਂਤਾਂ
	    ਪਹਿਲਾ = loop_ਨਾਂ.ਲੰਮਾਈ () - ret;
	  FOR_EACH_VEC_ELT_ਉਲਟ (loop_ਨਾਂ, i, l)
	    {
	      ਜੇ (C_DECL_LOOP_NAME (l) || C_DECL_SWITCH_NAME (l))
		c = l;
	      gcc_checking_assert (c);
	      loop_ਨਾਂ_hash->put (l, c);
	      ਜੇ (i == ਪਹਿਲਾ)
		ਰੋਕੋ;
	    }
	}
      *ਆਖਰੀ_p = ਆਖਰੀ;
    }
  ਵਾਪਸ ret;
}

/* Undoes what get_loop_names did when it returned NUM_NAMES.  */

ਖਾਲੀ
c_release_loop_ਨਾਂ (ਪੂਰਨ ਅੰਕ_ਨਾਂ)
{
  ਬਿਨਾਨਿਸ਼ਾਨੀ len = loop_ਨਾਂ.ਲੰਮਾਈ () - ਅੰਕ_ਨਾਂ;
  ਜੇ (loop_ਨਾਂ_hash)
    {
      ਜੇ (len <= 16)
	{
	  ਮਿਟਾਓ loop_ਨਾਂ_hash;
	  loop_ਨਾਂ_hash = ਨਿਰਾ;
	}
      ਨਹੀਂਤਾਂ
	{
	  ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ i;
	  ਰੁੱਖ l;
	  FOR_EACH_VEC_ELT_ਉਲਟ (loop_ਨਾਂ, i, l)
	    {
	      loop_ਨਾਂ_hash->remove (l);
	      ਜੇ (i == len)
		ਰੋਕੋ;
	    }
	}
    }
  loop_ਨਾਂ.truncate (len);
}

/* Finish processing of break or continue identifier operand.
   NAME is the identifier operand of break or continue and
   IS_BREAK is true iff it is break stmt.  Returns the operand
   to use for BREAK_STMT or CONTINUE_STMT, either NULL_TREE or
   canonical loop/switch name LABEL_DECL.  */

ਰੁੱਖ
c_ਅੰਤ_bc_name (location_t loc, ਰੁੱਖ name, ਤਾਰਕਿਕ is_break)
{
  ਰੁੱਖ label = NULL_ਰੁੱਖ, lab;
  pedwarn_c23 (loc, OPT_Wpedantic,
	       "ISO C does not support %qs statement with an identifier "
	       "operand before C2Y", is_break ? "break" : "continue");

  /* If I_LABEL_DECL is NULL or not from current function, don't waste time
     trying to find it among loop_names, it can't be there.  */
  ਜੇ (!loop_ਨਾਂ.is_ਖਾਲੀ_ਥਾਵਾਂ ()
      && current_function_scope
      && (lab = I_LABEL_DECL (name))
      && DECL_CONTEXT (lab) == current_function_decl)
    {
      ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ i;
      ਰੁੱਖ l, c = NULL_ਰੁੱਖ;
      ਜੇ (loop_ਨਾਂ_hash)
	{
	  ਜੇ (ਰੁੱਖ *val = loop_ਨਾਂ_hash->get (lab))
	    label = *val;
	}
      ਨਹੀਂਤਾਂ
	FOR_EACH_VEC_ELT_ਉਲਟ (loop_ਨਾਂ, i, l)
	  {
	    ਜੇ (C_DECL_LOOP_NAME (l) || C_DECL_SWITCH_NAME (l))
	      c = l;
	    gcc_checking_assert (c);
	    ਜੇ (l == lab)
	      {
		label = c;
		ਰੋਕੋ;
	      }
	  }
      ਜੇ (label)
	ਰੁੱਖ_ਵਰਤਿਆ (lab) = 1;
    }
  ਜੇ (label == NULL_ਰੁੱਖ)
    {
      auto_vec<ਅਚਲ ਅੱਖਰ *> candidates;
      ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ i;
      ਰੁੱਖ l, c = NULL_ਰੁੱਖ;
      FOR_EACH_VEC_ELT_ਉਲਟ (loop_ਨਾਂ, i, l)
	{
	  ਜੇ (C_DECL_LOOP_NAME (l) || C_DECL_SWITCH_NAME (l))
	    c = l;
	  gcc_checking_assert (c);
	  ਜੇ (is_break || C_DECL_LOOP_NAME (c))
	    candidates.ਸੁਰੱਖਿਅਤ_ਧੱਕੋ (IDENTIFIER_ਸੂਚਕ (DECL_NAME (l)));
	}
      ਅਚਲ ਅੱਖਰ *hint = ਲੱਭੋ_closest_string (IDENTIFIER_ਸੂਚਕ (name),
					      &candidates);
      ਜੇ (hint)
	{
	  gcc_rich_location richloc (loc);
	  richloc.ਜੋੜੋ_fixit_replace (hint);
	  ਜੇ (is_break)
	    error_at (&richloc, "%<break%> statement operand %qE does not "
				"refer to a named loop or %<switch%>; "
				"did you mean %qs?", name, hint);
	  ਨਹੀਂਤਾਂ
	    error_at (&richloc, "%<continue%> statement operand %qE does not "
				"refer to a named loop; did you mean %qs?",
		      name, hint);
	}
      ਨਹੀਂਤਾਂ ਜੇ (is_break)
	error_at (loc, "%<break%> statement operand %qE does not refer to a "
		       "named loop or %<switch%>", name);
      ਨਹੀਂਤਾਂ
	error_at (loc, "%<continue%> statement operand %qE does not refer to "
		       "a named loop", name);
    }
  ਨਹੀਂਤਾਂ ਜੇ (!C_DECL_LOOP_NAME (label) && !is_break)
    {
      auto_diagnostic_ਸਮੂਹ d;
      error_at (loc, "%<continue%> statement operand %qE refers to a named "
		     "%<switch%>", name);
      inform (DECL_ਸਰੋਤ_LOCATION (label), "%<switch%> name defined here");
      label = NULL_ਰੁੱਖ;
    }
  ਨਹੀਂਤਾਂ ਜੇ (!C_DECL_LOOP_SWITCH_NAME_VALID (label))
    {
      auto_diagnostic_ਸਮੂਹ d;
      ਜੇ (C_DECL_LOOP_NAME (label))
	{
	  error_at (loc, "%qs statement operand %qE refers to a loop outside "
			 "of its body", is_break ? "break" : "continue", name);
	  inform (DECL_ਸਰੋਤ_LOCATION (label), "loop name defined here");
	}
      ਨਹੀਂਤਾਂ
	{
	  error_at (loc, "%<break%> statement operand %qE refers to a "
			 "%<switch%> outside of its body", name);
	  inform (DECL_ਸਰੋਤ_LOCATION (label),
		  "%<switch%> name defined here");
	}
      label = NULL_ਰੁੱਖ;
    }
  ਨਹੀਂਤਾਂ ਜੇ (label == loop_ਨਾਂ.ਆਖਰੀ () && (ਵਿੱਚ_statement & ਵਿੱਚ_NAMED_STMT) != 0)
    /* If it is just a fancy reference to the innermost construct, handle it
       just like break; or continue; though tracking cheaply what is the
       innermost loop for continue when nested in switches would require
       another global variable and updating it.  */
    label = NULL_ਰੁੱਖ;
  ਨਹੀਂਤਾਂ
    C_DECL_LOOP_SWITCH_NAME_ਵਰਤਿਆ (label) = 1;
  ਵਾਪਸ label;
}

#ਅਨ੍ਤਰ੍ਭਾਵ "gt-c-c-decl.h"
