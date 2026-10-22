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

#అన్తర్భావ "config.h"
#నిర్వచించు INCLUDE_STRING
#అన్తర్భావ "system.h"
#అన్తర్భావ "coretypes.h"
#అన్తర్భావ "target.h"
#అన్తర్భావ "function.h"
#అన్తర్భావ "c-tree.h"
#అన్తర్భావ "timevar.h"
#అన్తర్భావ "stringpool.h"
#అన్తర్భావ "cgraph.h"
#అన్తర్భావ "intl.h"
#అన్తర్భావ "print-tree.h"
#అన్తర్భావ "stor-layout.h"
#అన్తర్భావ "varasm.h"
#అన్తర్భావ "attribs.h"
#అన్తర్భావ "toplev.h"
#అన్తర్భావ "debug.h"
#అన్తర్భావ "c-family/c-objc.h"
#అన్తర్భావ "c-family/c-pragma.h"
#అన్తర్భావ "c-family/c-ubsan.h"
#అన్తర్భావ "c-lang.h"
#అన్తర్భావ "langhooks.h"
#అన్తర్భావ "tree-iterator.h"
#అన్తర్భావ "dumpfile.h"
#అన్తర్భావ "plugin.h"
#అన్తర్భావ "c-family/c-ada-spec.h"
#అన్తర్భావ "builtins.h"
#అన్తర్భావ "spellcheck-tree.h"
#అన్తర్భావ "gcc-rich-location.h"
#అన్తర్భావ "asan.h"
#అన్తర్భావ "c-family/name-hint.h"
#అన్తర్భావ "c-family/known-headers.h"
#అన్తర్భావ "c-family/c-spellcheck.h"
#అన్తర్భావ "context.h"  /* For 'g'.  */
#అన్తర్భావ "omp-general.h"
#అన్తర్భావ "omp-offload.h"  /* For offload_vars.  */
#అన్తర్భావ "c-parser.h"
#అన్తర్భావ "gcc-urlifier.h"

#అన్తర్భావ "tree-pretty-print.h"

/* In grokdeclarator, distinguish syntactic contexts of declarators.  */
గణన decl_context
{ సాధారణ,			/* Ordinary declaration */
  FUNCDEF,			/* Function definition */
  PARM,				/* Declaration of parm before function body */
  క్షేత్రం,			/* Declaration inside struct or union */
  TYPENAME,			/* Typename (inside cast or sizeof)  */
  GENERIC_ASSOC };		/* Typename in generic association  */

/* States indicating how grokdeclarator() should handle declspecs marked
   with __attribute__((deprecated)) or __attribute__((unavailable)).
   An object declared as __attribute__((unavailable)) should suppress
   any reports of being declared  with unavailable or deprecated items.
   An object declared as __attribute__((deprecated)) should suppress
   warnings of uses of other deprecated items.  */

గణన deprecated_స్థితులు {
  DEPRECATED_సాధారణ,
  DEPRECATED_SUPPRESS,
  UNAVAILABLE_DEPRECATED_SUPPRESS
};


/* Nonzero if we have seen an invalid cross reference
   to a struct, union, or enum, but not yet printed the message.  */
వృక్షం pending_invalid_xref;

/* File and line to appear in the eventual error message.  */
location_t pending_invalid_xref_location;

/* The file and line that the prototype came from if this is an
   old-style definition; used for diagnostics in
   store_parm_decls_oldstyle.  */

స్థిర location_t current_function_prototype_locus;

/* Whether this prototype was built-in.  */

స్థిర తార్కిక current_function_prototype_built_లోపల;

/* The argument type information of this prototype.  */

స్థిర వృక్షం current_function_prototype_arg_types;

/* The argument information structure for the function currently being
   defined.  */

స్థిర నిర్మాణం c_arg_info *current_function_arg_info;

/* The obstack on which parser and related data structures, which are
   not live beyond their top-level declaration or definition, are
   allocated.  */
నిర్మాణం obstack parser_obstack;

/* The current statement tree.  */

స్థిర GTY(()) నిర్మాణం stmt_వృక్షం_s c_stmt_వృక్షం;

/* Zero if we are not in an iteration or switch statement, otherwise
   a bitmask.  See bitmask definitions in c-tree.h.  */
గుర్తులేని అక్షరం లోపల_statement;

/* A list of decls to be made automatically visible in each file scope.  */
స్థిర GTY(()) వృక్షం visible_builtins;

/* Set to 0 at beginning of a function definition, set to 1 if
   a return statement that specifies a return value is seen.  */

పూర్ణాంకం current_function_returns_విలువ;

/* Set to 0 at beginning of a function definition, set to 1 if
   a return statement with no argument is seen.  */

పూర్ణాంకం current_function_returns_null;

/* Set to 0 at beginning of a function definition, set to 1 if
   a call to a noreturn function is seen.  */

పూర్ణాంకం current_function_returns_abnormally;

/* Set to nonzero by `grokdeclarator' for a function
   whose return type is defaulted, if warnings for this are desired.  */

స్థిర పూర్ణాంకం warn_about_return_type;

/* Nonzero when the current toplevel function contains a declaration
   of a nested function which is never defined.  */

స్థిర తార్కిక undef_nested_function;

/* Vector of implicit "omp declare target" attributes to be added into
   the attribute lists.  */
vec<c_omp_declare_లక్ష్యం_attr, va_gc> *current_omp_declare_లక్ష్యం_attribute;

/* Vector of
   #pragma omp begin assumes ... #pragma omp end assumes regions
   we are in.  */
vec<c_omp_begin_assumes_దత్తాంశం, va_gc> *current_omp_begin_assumes;

/* Vector of "omp begin/end declare variant" blocks we are in.  */
vec<c_omp_declare_variant_attr, va_gc> *current_omp_declare_variant_attribute;

/* Vector of loop names with C_DECL_LOOP_NAME or C_DECL_SWITCH_NAME marked
   LABEL_DECL as the last and canonical for each loop or switch.  */
స్థిర vec<వృక్షం> loop_పేర్లు;

/* Hash table mapping LABEL_DECLs to the canonical LABEL_DECLs if LOOP_NAMES
   vector becomes too long.  */
స్థిర decl_వృక్షం_map *loop_పేర్లు_hash;

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

నిర్మాణం GTY((chain_తదుపరి ("%h.prev"))) c_binding {
  సంఘం GTY(()) {		/* first so GTY desc can use decl */
    వృక్షం GTY((ట్యాగ్ ("0"))) type; /* the type in this scope */
    నిర్మాణం c_label_vars * GTY((ట్యాగ్ ("1"))) label; /* for warnings */
  } GTY((desc ("TREE_CODE (%0.decl) == LABEL_DECL"))) u;
  వృక్షం decl;			/* the decl bound */
  వృక్షం id;			/* the identifier it's bound to */
  నిర్మాణం c_binding *prev;	/* the previous decl in this scope */
  నిర్మాణం c_binding *shadowed;	/* the innermost decl shadowed by this one */
  గుర్తులేని పూర్ణాంకం లోతు : 28;      /* depth of this scope */
  తార్కిక invisible : 1;  /* normal lookup should ignore this binding */
  తార్కిక nested : 1;     /* do not set DECL_CONTEXT when popping */
  తార్కిక inner_comp : 1; /* incomplete array completed in inner scope */
  తార్కిక లోపల_struct : 1;	/* currently defined as struct field */
  location_t locus;		/* location for nested bindings */
};
#నిర్వచించు B_లోపల_SCOPE(b1, b2) ((b1)->లోతు == (b2)->లోతు)
#నిర్వచించు B_లోపల_CURRENT_SCOPE(b) ((b)->లోతు == current_scope->లోతు)
#నిర్వచించు B_లోపల_FILE_SCOPE(b) ((b)->లోతు == 1 /*file_scope->depth*/)
#నిర్వచించు B_లోపల_EXTERNAL_SCOPE(b) ((b)->లోతు == 0 /*external_scope->depth*/)

/* Each C symbol points to three linked lists of c_binding structures.
   These describe the values of the identifier in the three different
   namespaces defined by the language.  */

నిర్మాణం GTY(()) lang_identifier {
  నిర్మాణం c_common_identifier common_id;
  నిర్మాణం c_binding *చిహ్నం_binding; /* vars, funcs, constants, typedefs */
  నిర్మాణం c_binding *ట్యాగ్_binding;    /* struct/union/enum tags */
  నిర్మాణం c_binding *label_binding;  /* labels */
};

/* Validate c-lang.cc's assumptions.  */
బాహ్య అక్షరం C_SIZEOF_STRUCT_LANG_IDENTIFIER_isnt_accurate
[(పరిమాణం(నిర్మాణం lang_identifier) == C_SIZEOF_STRUCT_LANG_IDENTIFIER) ? 1 : -1];

/* The binding oracle; see c-tree.h.  */
శూన్య (*c_binding_oracle) (గణన c_oracle_request, వృక్షం identifier);

/* This flag is set on an identifier if we have previously asked the
   binding oracle for this identifier's symbol binding.  */
#నిర్వచించు I_చిహ్నం_CHECKED(కణుపు) \
  (వృక్షం_LANG_FLAG_4 (IDENTIFIER_కణుపు_CHECK (కణుపు)))

స్థిర అంతఃవరుస నిర్మాణం c_binding* *
i_చిహ్నం_binding (వృక్షం కణుపు)
{
  నిర్మాణం lang_identifier *lid
    = (నిర్మాణం lang_identifier *) IDENTIFIER_కణుపు_CHECK (కణుపు);

  ఒకవేళ (lid->చిహ్నం_binding == ఖాళీ
      && c_binding_oracle != ఖాళీ
      && !I_చిహ్నం_CHECKED (కణుపు))
    {
      /* Set the "checked" flag first, to avoid infinite recursion
	 when the binding oracle calls back into gcc.  */
      I_చిహ్నం_CHECKED (కణుపు) = 1;
      c_binding_oracle (C_ORACLE_చిహ్నం, కణుపు);
    }

  తిరిగి &lid->చిహ్నం_binding;
}

#నిర్వచించు I_చిహ్నం_BINDING(కణుపు) (*i_చిహ్నం_binding (కణుపు))

#నిర్వచించు I_చిహ్నం_DECL(కణుపు) \
 (I_చిహ్నం_BINDING(కణుపు) ? I_చిహ్నం_BINDING(కణుపు)->decl : 0)

/* This flag is set on an identifier if we have previously asked the
   binding oracle for this identifier's tag binding.  */
#నిర్వచించు I_ట్యాగ్_CHECKED(కణుపు) \
  (వృక్షం_LANG_FLAG_5 (IDENTIFIER_కణుపు_CHECK (కణుపు)))

స్థిర అంతఃవరుస నిర్మాణం c_binding **
i_ట్యాగ్_binding (వృక్షం కణుపు)
{
  నిర్మాణం lang_identifier *lid
    = (నిర్మాణం lang_identifier *) IDENTIFIER_కణుపు_CHECK (కణుపు);

  ఒకవేళ (lid->ట్యాగ్_binding == ఖాళీ
      && c_binding_oracle != ఖాళీ
      && !I_ట్యాగ్_CHECKED (కణుపు))
    {
      /* Set the "checked" flag first, to avoid infinite recursion
	 when the binding oracle calls back into gcc.  */
      I_ట్యాగ్_CHECKED (కణుపు) = 1;
      c_binding_oracle (C_ORACLE_ట్యాగ్, కణుపు);
    }

  తిరిగి &lid->ట్యాగ్_binding;
}

#నిర్వచించు I_ట్యాగ్_BINDING(కణుపు) (*i_ట్యాగ్_binding (కణుపు))

#నిర్వచించు I_ట్యాగ్_DECL(కణుపు) \
 (I_ట్యాగ్_BINDING(కణుపు) ? I_ట్యాగ్_BINDING(కణుపు)->decl : 0)

/* This flag is set on an identifier if we have previously asked the
   binding oracle for this identifier's label binding.  */
#నిర్వచించు I_LABEL_CHECKED(కణుపు) \
  (వృక్షం_LANG_FLAG_6 (IDENTIFIER_కణుపు_CHECK (కణుపు)))

స్థిర అంతఃవరుస నిర్మాణం c_binding **
i_label_binding (వృక్షం కణుపు)
{
  నిర్మాణం lang_identifier *lid
    = (నిర్మాణం lang_identifier *) IDENTIFIER_కణుపు_CHECK (కణుపు);

  ఒకవేళ (lid->label_binding == ఖాళీ
      && c_binding_oracle != ఖాళీ
      && !I_LABEL_CHECKED (కణుపు))
    {
      /* Set the "checked" flag first, to avoid infinite recursion
	 when the binding oracle calls back into gcc.  */
      I_LABEL_CHECKED (కణుపు) = 1;
      c_binding_oracle (C_ORACLE_LABEL, కణుపు);
    }

  తిరిగి &lid->label_binding;
}

#నిర్వచించు I_LABEL_BINDING(కణుపు) (*i_label_binding (కణుపు))

#నిర్వచించు I_LABEL_DECL(కణుపు) \
 (I_LABEL_BINDING(కణుపు) ? I_LABEL_BINDING(కణుపు)->decl : 0)

/* Used by C_TOKEN_VEC tree.  */
నిర్మాణం GTY (()) c_వృక్షం_token_vec {
  నిర్మాణం వృక్షం_పునాది పునాది;
  vec<c_token, va_gc> *టోకెన్లు;
};

STATIC_ASSERT (పరిమాణం (c_వృక్షం_token_vec) == పరిమాణం (c_వృక్షం_token_vec_struct));
STATIC_ASSERT (offsetof (c_వృక్షం_token_vec, టోకెన్లు)
	       == offsetof (c_వృక్షం_token_vec_struct, టోకెన్లు));

/* The resulting tree type.  */

సంఘం GTY((desc ("TREE_CODE (&%h.generic) == IDENTIFIER_NODE + 2 * (TREE_CODE (&%h.generic) == C_TOKEN_VEC)"),
       chain_తదుపరి ("(union lang_tree_node *) c_tree_chain_next (&%h.generic)"))) lang_వృక్షం_కణుపు
 {
  సంఘం వృక్ష_కణుపు GTY ((ట్యాగ్ ("0"),
			desc ("tree_node_structure (&%h)")))
    generic;
  నిర్మాణం lang_identifier GTY ((ట్యాగ్ ("1"))) identifier;
  నిర్మాణం c_వృక్షం_token_vec GTY ((ట్యాగ్ ("2"))) c_token_vec;
};

/* Langhook for tree_size.  */
కొలత_t
c_వృక్షం_కొలత (గణన వృక్షం_సంకేతం_2 సంకేతం_2)
{
  gcc_checking_assert (సంకేతం_2 >= అంకె_వృక్షం_CODES);
  ఎంపిక (సంకేతం_2)
    {
    స్థితి C_TOKEN_VEC: తిరిగి పరిమాణం (c_వృక్షం_token_vec);
    అప్రమేయ:
      ఎంపిక (వృక్షం_సంకేతం_CLASS (సంకేతం_2))
	{
	స్థితి tcc_declaration: తిరిగి పరిమాణం (వృక్షం_decl_non_common);
	స్థితి tcc_type: తిరిగి పరిమాణం (వృక్షం_type_non_common);
	అప్రమేయ: gcc_unreachable ();
	}
    }
}

/* Track bindings and other things that matter for goto warnings.  For
   efficiency, we do not gather all the decls at the point of
   definition.  Instead, we point into the bindings structure.  As
   scopes are popped, we update these structures and gather the decls
   that matter at that time.  */

నిర్మాణం GTY(()) c_spot_bindings {
  /* The currently open scope which holds bindings defined when the
     label was defined or the goto statement was found.  */
  నిర్మాణం c_scope *scope;
  /* The bindings in the scope field which were defined at the point
     of the label or goto.  This lets us look at older or newer
     bindings in the scope, as appropriate.  */
  నిర్మాణం c_binding *bindings_లోపల_scope;
  /* The number of statement expressions that have started since this
     label or goto statement was defined.  This is zero if we are at
     the same statement expression level.  It is positive if we are in
     a statement expression started since this spot.  It is negative
     if this spot was in a statement expression and we have left
     it.  */
  పూర్ణాంకం stmt_exprs;
  /* Whether we started in a statement expression but are no longer in
     it.  This is set to true if stmt_exprs ever goes negative.  */
  తార్కిక ఎడమ_stmt_సమాసం;
};

/* This structure is used to keep track of bindings seen when a goto
   statement is defined.  This is only used if we see the goto
   statement before we see the label.  */

నిర్మాణం GTY(()) c_goto_bindings {
  /* The location of the goto statement.  */
  location_t loc;
  /* The bindings of the goto statement.  */
  నిర్మాణం c_spot_bindings goto_bindings;
};

రకనిర్వచనం నిర్మాణం c_goto_bindings *c_goto_bindings_p;

/* The additional information we keep track of for a label binding.
   These fields are updated as scopes are popped.  */

నిర్మాణం GTY(()) c_label_vars {
  /* The shadowed c_label_vars, when one label shadows another (which
     can only happen using a __label__ declaration).  */
  నిర్మాణం c_label_vars *shadowed;
  /* The bindings when the label was defined.  */
  నిర్మాణం c_spot_bindings label_bindings;
  /* A list of decls that we care about: decls about which we should
     warn if a goto branches to this label from later in the function.
     Decls are added to this list as scopes are popped.  We only add
     the decls that matter.  */
  vec<వృక్షం, va_gc> *decls_లోపల_scope;
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


నిర్మాణం GTY((chain_తదుపరి ("%h.outer"))) c_scope {
  /* The scope containing this one.  */
  నిర్మాణం c_scope *outer;

  /* The next outermost function scope.  */
  నిర్మాణం c_scope *outer_function;

  /* All bindings in this scope.  */
  నిర్మాణం c_binding *bindings;

  /* For each scope (except the global one), a chain of BLOCK nodes
     for all the scopes that were entered and exited one level down.  */
  వృక్షం ఖండాలు;
  వృక్షం ఖండాలు_చివరి;

  /* The depth of this scope.  Used to keep the ->shadowed chain of
     bindings sorted innermost to outermost.  */
  గుర్తులేని పూర్ణాంకం లోతు : 28;

  /* True if we are currently filling this scope with parameter
     declarations.  */
  తార్కిక parm_flag : 1;

  /* True if we saw [*] in this scope.  Used to give an error messages
     if these appears in a function definition.  */
  తార్కిక had_vla_unspec : 1;

  /* True if we parsed a list of forward parameter decls in this scope.  */
  తార్కిక had_forward_parm_decls : 1;

  /* True if this is the outermost block scope of a function body.
     This scope contains the parameters, the local variables declared
     in the outermost block, and all the labels (except those in
     nested functions, or declared at block scope with __label__).  */
  తార్కిక function_body : 1;

  /* True means make a BLOCK for this scope no matter what.  */
  తార్కిక keep : 1;

  /* True means that an unsuffixed float constant is _Decimal64.  */
  తార్కిక float_const_decimal64 : 1;

  /* True if this scope has any label bindings.  This is used to speed
     up searching for labels when popping scopes, particularly since
     labels are normally only found at function scope.  */
  తార్కిక has_label_bindings : 1;

  /* True if we should issue a warning if a goto statement crosses any
     of the bindings.  We still need to check the list of bindings to
     find the specific ones we need to warn about.  This is true if
     decl_jump_unsafe would return true for any of the bindings.  This
     is used to avoid looping over all the bindings unnecessarily.  */
  తార్కిక has_jump_unsafe_decl : 1;
};

/* The scope currently in effect.  */

స్థిర GTY(()) నిర్మాణం c_scope *current_scope;

/* The innermost function scope.  Ordinary (not explicitly declared)
   labels, bindings to error_mark_node, and the lazily-created
   bindings of __func__ and its friends get this scope.  */

స్థిర GTY(()) నిర్మాణం c_scope *current_function_scope;

/* The C file scope.  This is reset for each input translation unit.  */

స్థిర GTY(()) నిర్మాణం c_scope *file_scope;

/* The outermost scope.  This is used for all declarations with
   external linkage, and only these, hence the name.  */

స్థిర GTY(()) నిర్మాణం c_scope *external_scope;

/* A chain of c_scope structures awaiting reuse.  */

స్థిర GTY((deletable)) నిర్మాణం c_scope *scope_freelist;

/* A chain of c_binding structures awaiting reuse.  */

స్థిర GTY((deletable)) నిర్మాణం c_binding *binding_freelist;

/* Append VAR to LIST in scope SCOPE.  */
#నిర్వచించు SCOPE_LIST_APPEND(scope, list, decl) చేయి {	\
  నిర్మాణం c_scope *s_ = (scope);				\
  వృక్షం d_ = (decl);					\
  ఒకవేళ (s_->list##_last)					\
    ఖండం_CHAIN (s_->list##_last) = d_;			\
  లేకపోతే							\
    s_->list = d_;					\
  s_->list##_last = d_;					\
} అయితే (0)

/* Concatenate FROM in scope FSCOPE onto TO in scope TSCOPE.  */
#నిర్వచించు SCOPE_LIST_CONCAT(tscope, గమ్యం, fscope, from) చేయి {	\
  నిర్మాణం c_scope *t_ = (tscope);				\
  నిర్మాణం c_scope *f_ = (fscope);				\
  ఒకవేళ (t_->గమ్యం##_last)						\
    ఖండం_CHAIN (t_->గమ్యం##_last) = f_->from;			\
  లేకపోతే								\
    t_->గమ్యం = f_->from;						\
  t_->గమ్యం##_last = f_->from##_last;				\
} అయితే (0)

/* A c_inline_static structure stores details of a static identifier
   referenced in a definition of a function that may be an inline
   definition if no subsequent declaration of that function uses
   "extern" or does not use "inline".  */

నిర్మాణం GTY((chain_తదుపరి ("%h.next"))) c_inline_static {
  /* The location for a diagnostic.  */
  location_t location;

  /* The function that may be an inline definition.  */
  వృక్షం function;

  /* The object or function referenced.  */
  వృక్షం static_decl;

  /* What sort of reference this is.  */
  గణన c_inline_static_type type;

  /* The next such structure or NULL.  */
  నిర్మాణం c_inline_static *తదుపరి;
};

/* List of static identifiers used or referenced in functions that may
   be inline definitions.  */
స్థిర GTY(()) నిర్మాణం c_inline_static *c_inline_statics;

/* True means unconditionally make a BLOCK for the next scope pushed.  */

స్థిర తార్కిక keep_తదుపరి_level_flag;

/* True means the next call to push_scope will be the outermost scope
   of a function body, so do not push a new scope, merely cease
   expecting parameter decls.  */

స్థిర తార్కిక తదుపరి_is_function_body;

/* A vector of pointers to c_binding structures.  */

రకనిర్వచనం నిర్మాణం c_binding *c_binding_ptr;

/* Information that we keep for a struct or union while it is being
   parsed.  */

తరగతి c_struct_parse_info
{
బహిరంగ:
  /* If warn_cxx_compat, a list of types defined within this
     struct.  */
  auto_vec<వృక్షం> struct_types;
  /* If warn_cxx_compat, a list of field names which have bindings,
     and which are defined in this struct, but which are not defined
     in any enclosing struct.  This is used to clear the in_struct
     field of the c_bindings structure.  */
  auto_vec<c_binding_ptr> fields;
  /* If warn_cxx_compat, a list of typedef names used when defining
     fields in this struct.  */
  auto_vec<వృక్షం> typedefs_చూసిన;
  /* The location of a previous definition of this struct.  */
  location_t refloc;
};


/* Hash table for structs and unions.  */
నిర్మాణం c_struct_hasher : ggc_ptr_hash<వృక్ష_కణుపు>
{
  స్థిర hashval_t hash (వృక్షం t);
  స్థిర తార్కిక equal (వృక్షం, వృక్షం);
};

/* Hash an RECORD OR UNION.  */
hashval_t
c_struct_hasher::hash (వృక్షం type)
{
  inchash::hash hstate;

  hstate.కూడు_int (వృక్షం_సంకేతం (type));
  వృక్షం ట్యాగ్ = c_type_ట్యాగ్ (type);
  hstate.కూడు_object (ట్యాగ్);

  తిరిగి hstate.చివర ();
}

/* Compare two RECORD or UNION types.  */
తార్కిక
c_struct_hasher::equal (వృక్షం t1,  వృక్షం t2)
{
  తిరిగి comptypes_equiv_p (t1, t2);
}

/* All tagged typed so that TYPE_CANONICAL can be set correctly.  */
స్థిర GTY (()) hash_పట్టిక<c_struct_hasher> *c_struct_htab;

/* Information for the struct or union currently being parsed, or
   NULL if not parsing a struct or union.  */
స్థిర తరగతి c_struct_parse_info *struct_parse_info;

/* Forward declarations.  */
స్థిర వృక్షం lookup_name_లోపల_scope (వృక్షం, నిర్మాణం c_scope *);
స్థిర వృక్షం c_make_fname_decl (location_t, వృక్షం, పూర్ణాంకం);
స్థిర వృక్షం grokdeclarator (స్థిరరాశి నిర్మాణం c_declarator *,
			    నిర్మాణం c_declspecs *,
			    గణన decl_context, తార్కిక, వృక్షం *, వృక్షం *, వృక్షం *,
			    తార్కిక *, గణన deprecated_స్థితులు);
స్థిర వృక్షం grokparms (నిర్మాణం c_arg_info *, తార్కిక);
స్థిర శూన్య layout_array_type (వృక్షం);
స్థిర స్థిరరాశి అక్షరం *శీర్షిక_for_builtin_fn (వృక్షం);

/* T is a statement.  Add it to the statement-tree.  This is the
   C/ObjC version--C++ has a slightly different version of this
   function.  */

వృక్షం
కూడు_stmt (వృక్షం t)
{
  గణన వృక్షం_సంకేతం_2 సంకేతం_2 = వృక్షం_సంకేతం (t);

  ఒకవేళ (CAN_HAVE_LOCATION_P (t) && సంకేతం_2 != LABEL_సమాసం)
    {
      ఒకవేళ (!సమాసం_HAS_LOCATION (t))
	సమితి_సమాసం_LOCATION (t, ఆదానం_location);
    }

  /* Add T to the statement-tree.  Non-side-effect statements need to be
     recorded during statement expressions.  */
  ఒకవేళ (!building_stmt_list_p ())
    నెట్టు_stmt_list ();

  ఒకవేళ (సంకేతం_2 == LABEL_సమాసం || సంకేతం_2 == CASE_LABEL_సమాసం)
    STATEMENT_LIST_HAS_LABEL (cur_stmt_list) = 1;

  append_గమ్యం_statement_list_force (t, &cur_stmt_list);

  తిరిగి t;
}





/* Return true if we will want to say something if a goto statement
   crosses DECL.  */

స్థిర తార్కిక
decl_jump_unsafe (వృక్షం decl)
{
  ఒకవేళ (error_నిర్వాహ్యం_p (decl))
    తిరిగి అబద్ధం;

  /* Don't warn for compound literals.  If a goto statement crosses
     their initialization, it should cross also all the places where
     the complit is used or where the complit address might be saved
     into some variable, so code after the label to which goto jumps
     should not be able to refer to the compound literal.  */
  ఒకవేళ (VAR_P (decl) && C_DECL_COMPOUND_LITERAL_P (decl))
    తిరిగి అబద్ధం;

  ఒకవేళ (flag_openmp
      && VAR_P (decl)
      && lookup_attribute ("omp allocate", DECL_లక్షణాలు (decl)))
    తిరిగి నిజం;

  /* Always warn about crossing variably modified types.  */
  ఒకవేళ ((VAR_P (decl) || వృక్షం_సంకేతం (decl) == TYPE_DECL)
      && c_type_variably_modified_p (వృక్షం_TYPE (decl)))
    తిరిగి నిజం;

  /* Otherwise, only warn if -Wgoto-misses-init and this is an
     initialized automatic decl.  */
  ఒకవేళ (warn_jump_తప్పినవి_init
      && VAR_P (decl)
      && !వృక్షం_STATIC (decl)
      && DECL_INITIAL (decl) != NULL_వృక్షం)
    తిరిగి నిజం;

  తిరిగి అబద్ధం;
}


శూన్య
c_print_identifier (FILE *file, వృక్షం కణుపు, పూర్ణాంకం indent)
{
  శూన్య (*save) (గణన c_oracle_request, వృక్షం identifier);

  /* Temporarily hide any binding oracle.  Without this, calls to
     debug_tree from the debugger will end up calling into the oracle,
     making for a confusing debug session.  As the oracle isn't needed
     here for normal operation, it's simplest to suppress it.  */
  save = c_binding_oracle;
  c_binding_oracle = ఖాళీ;

  print_కణుపు (file, "symbol", I_చిహ్నం_DECL (కణుపు), indent + 4);
  print_కణుపు (file, "tag", I_ట్యాగ్_DECL (కణుపు), indent + 4);
  print_కణుపు (file, "label", I_LABEL_DECL (కణుపు), indent + 4);
  ఒకవేళ (C_IS_RESERVED_మాట (కణుపు) && C_RID_సంకేతం (కణుపు) != RID_CXX_COMPAT_WARN)
    {
      వృక్షం rid = ridpointers[C_RID_సంకేతం (కణుపు)];
      indent_గమ్యం (file, indent + 4);
      fprintf (file, "rid " HOST_PTR_PRINTF " \"%s\"",
	       (శూన్య *) rid, IDENTIFIER_సూచిక (rid));
    }

  c_binding_oracle = save;
}

/* Establish that the scope contains declarations that are sensitive to
   jumps that cross a binding.  Together with decl_jump_unsafe, this is
   used to diagnose such jumps.  */
శూన్య
c_mark_decl_jump_unsafe_లోపల_current_scope ()
{
  current_scope->has_jump_unsafe_decl = 1;
}

/* Establish a binding between NAME, an IDENTIFIER_NODE, and DECL,
   which may be any of several kinds of DECL or TYPE or error_mark_node,
   in the scope SCOPE.  */
స్థిర శూన్య
bind (వృక్షం name, వృక్షం decl, నిర్మాణం c_scope *scope, తార్కిక invisible,
      తార్కిక nested, location_t locus)
{
  నిర్మాణం c_binding *b, **ఇక్కడ;

  ఒకవేళ (binding_freelist)
    {
      b = binding_freelist;
      binding_freelist = b->prev;
    }
  లేకపోతే
    b = ggc_alloc<c_binding> ();

  b->shadowed = 0;
  b->decl = decl;
  b->id = name;
  b->లోతు = scope->లోతు;
  b->invisible = invisible;
  b->nested = nested;
  b->inner_comp = 0;
  b->లోపల_struct = 0;
  b->locus = locus;

  b->u.type = ఖాళీ;

  b->prev = scope->bindings;
  scope->bindings = b;

  ఒకవేళ (decl_jump_unsafe (decl))
    scope->has_jump_unsafe_decl = 1;

  ఒకవేళ (!name)
    తిరిగి;

  ఎంపిక (వృక్షం_సంకేతం (decl))
    {
    స్థితి LABEL_DECL:     ఇక్కడ = &I_LABEL_BINDING (name);   ఆపు;
    స్థితి ENUMERAL_TYPE:
    స్థితి UNION_TYPE:
    స్థితి రికార్డు_TYPE:    ఇక్కడ = &I_ట్యాగ్_BINDING (name);     ఆపు;
    స్థితి VAR_DECL:
    స్థితి FUNCTION_DECL:
    స్థితి TYPE_DECL:
    స్థితి CONST_DECL:
    స్థితి PARM_DECL:
    స్థితి ERROR_MARK:     ఇక్కడ = &I_చిహ్నం_BINDING (name);  ఆపు;

    అప్రమేయ:
      gcc_unreachable ();
    }

  /* Locate the appropriate place in the chain of shadowed decls
     to insert this binding.  Normally, scope == current_scope and
     this does nothing.  */
  అయితే (*ఇక్కడ && (*ఇక్కడ)->లోతు > scope->లోతు)
    ఇక్కడ = &(*ఇక్కడ)->shadowed;

  b->shadowed = *ఇక్కడ;
  *ఇక్కడ = b;
}

/* Clear the binding structure B, stick it on the binding_freelist,
   and return the former value of b->prev.  This is used by pop_scope
   and get_parm_info to iterate destructively over all the bindings
   from a given scope.  */
స్థిర నిర్మాణం c_binding *
free_binding_and_advance (నిర్మాణం c_binding *b)
{
  నిర్మాణం c_binding *prev = b->prev;

  memset (b, 0, పరిమాణం (నిర్మాణం c_binding));
  b->prev = binding_freelist;
  binding_freelist = b;

  తిరిగి prev;
}

/* Bind a label.  Like bind, but skip fields which aren't used for
   labels, and add the LABEL_VARS value.  */
స్థిర శూన్య
bind_label (వృక్షం name, వృక్షం label, నిర్మాణం c_scope *scope,
	    నిర్మాణం c_label_vars *label_vars)
{
  నిర్మాణం c_binding *b;

  bind (name, label, scope, /*invisible=*/అబద్ధం, /*nested=*/అబద్ధం,
	UNKNOWN_LOCATION);

  scope->has_label_bindings = నిజం;

  b = scope->bindings;
  gcc_assert (b->decl == label);
  label_vars->shadowed = b->u.label;
  b->u.label = label_vars;
}

/* Hook called at end of compilation to assume 1 elt
   for a file-scope tentative array defn that wasn't complete before.  */

శూన్య
c_ముగింపు_incomplete_decl (వృక్షం decl)
{
  ఒకవేళ (VAR_P (decl))
    {
      వృక్షం type = వృక్షం_TYPE (decl);
      ఒకవేళ (type != error_mark_కణుపు
	  && వృక్షం_సంకేతం (type) == ARRAY_TYPE
	  && !DECL_EXTERNAL (decl)
	  && TYPE_DOMAIN (type) == NULL_వృక్షం)
	{
	  ఒకవేళ (flag_isoc2y && !వృక్షం_ప్రజా (decl))
	    error_at (DECL_ఆధారం_LOCATION (decl),
		      "array size missing in %q+D", decl);
	  లేకపోతే
	    warning_at (DECL_ఆధారం_LOCATION (decl),
			0, "array %q+D assumed to have one element", decl);

	  complete_array_type (&వృక్షం_TYPE (decl), NULL_వృక్షం, నిజం);

	  relayout_decl (decl);
	}
    }
}

/* Record that inline function FUNC contains a reference (location
   LOC) to static DECL (file-scope or function-local according to
   TYPE).  */

శూన్య
రికార్డు_inline_static (location_t loc, వృక్షం func, వృక్షం decl,
		      గణన c_inline_static_type type)
{
  c_inline_static *csi = ggc_alloc<c_inline_static> ();
  csi->location = loc;
  csi->function = func;
  csi->static_decl = decl;
  csi->type = type;
  csi->తదుపరి = c_inline_statics;
  c_inline_statics = csi;
}

/* Check for references to static declarations in inline functions at
   the end of the translation unit and diagnose them if the functions
   are still inline definitions.  */

స్థిర శూన్య
check_inline_statics (శూన్య)
{
  నిర్మాణం c_inline_static *csi;
  కొరకు (csi = c_inline_statics; csi; csi = csi->తదుపరి)
    {
      ఒకవేళ (DECL_EXTERNAL (csi->function))
	ఎంపిక (csi->type)
	  {
	  స్థితి csi_అంతర్గత:
	    pedwarn (csi->location, 0,
		     "%qD is static but used in inline function %qD "
		     "which is not static", csi->static_decl, csi->function);
	    ఆపు;
	  స్థితి csi_modifiable:
	    pedwarn (csi->location, 0,
		     "%q+D is static but declared in inline function %qD "
		     "which is not static", csi->static_decl, csi->function);
	    ఆపు;
	  అప్రమేయ:
	    gcc_unreachable ();
	  }
    }
  c_inline_statics = ఖాళీ;
}

/* Fill in a c_spot_bindings structure.  If DEFINING is true, set it
   for the current state, otherwise set it to uninitialized.  */

స్థిర శూన్య
సమితి_spot_bindings (నిర్మాణం c_spot_bindings *p, తార్కిక defining)
{
  ఒకవేళ (defining)
    {
      p->scope = current_scope;
      p->bindings_లోపల_scope = current_scope->bindings;
    }
  లేకపోతే
    {
      p->scope = ఖాళీ;
      p->bindings_లోపల_scope = ఖాళీ;
    }
  p->stmt_exprs = 0;
  p->ఎడమ_stmt_సమాసం = అబద్ధం;
}

/* Update spot bindings P as we pop out of SCOPE.  Return true if we
   should push decls for a label.  */

స్థిర తార్కిక
update_spot_bindings (నిర్మాణం c_scope *scope, నిర్మాణం c_spot_bindings *p)
{
  ఒకవేళ (p->scope != scope)
    {
      /* This label or goto is defined in some other scope, or it is a
	 label which is not yet defined.  There is nothing to
	 update.  */
      తిరిగి అబద్ధం;
    }

  /* Adjust the spot bindings to refer to the bindings already defined
     in the enclosing scope.  */
  p->scope = scope->outer;
  p->bindings_లోపల_scope = p->scope->bindings;

  తిరిగి నిజం;
}

/* The Objective-C front-end often needs to determine the current scope.  */

శూన్య *
objc_get_current_scope (శూన్య)
{
  తిరిగి current_scope;
}

/* The following function is used only by Objective-C.  It needs to live here
   because it accesses the innards of c_scope.  */

శూన్య
objc_mark_locals_volatile (శూన్య *enclosing_blk)
{
  నిర్మాణం c_scope *scope;
  నిర్మాణం c_binding *b;

  కొరకు (scope = current_scope;
       scope && scope != enclosing_blk;
       scope = scope->outer)
    {
      కొరకు (b = scope->bindings; b; b = b->prev)
	objc_volatilize_decl (b->decl);

      /* Do not climb up past the current function.  */
      ఒకవేళ (scope->function_body)
	ఆపు;
    }
}

/* Return true if we are in the global binding level.  */

తార్కిక
global_bindings_p (శూన్య)
{
  తిరిగి current_scope == file_scope;
}

/* Return true if we're declaring parameters in an old-style function
   declaration.  */

తార్కిక
old_style_parameter_scope (శూన్య)
{
  /* If processing parameters and there is no function statement list, we
   * have an old-style function declaration.  */
  తిరిగి (current_scope->parm_flag && !DECL_SAVED_వృక్షం (current_function_decl));
}

శూన్య
keep_తదుపరి_level (శూన్య)
{
  keep_తదుపరి_level_flag = నిజం;
}

/* Set the flag for the FLOAT_CONST_DECIMAL64 pragma being ON.  */

శూన్య
సమితి_float_const_decimal64 (శూన్య)
{
  current_scope->float_const_decimal64 = నిజం;
}

/* Clear the flag for the FLOAT_CONST_DECIMAL64 pragma.  */

శూన్య
clear_float_const_decimal64 (శూన్య)
{
  current_scope->float_const_decimal64 = అబద్ధం;
}

/* Return nonzero if an unsuffixed float constant is _Decimal64.  */

తార్కిక
float_const_decimal64_p (శూన్య)
{
  తిరిగి current_scope->float_const_decimal64;
}

/* Identify this scope as currently being filled with parameters.  */

శూన్య
declare_parm_level (శూన్య)
{
  current_scope->parm_flag = నిజం;
}

శూన్య
నెట్టు_scope (శూన్య)
{
  ఒకవేళ (తదుపరి_is_function_body)
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
      current_scope->parm_flag         = అబద్ధం;
      current_scope->function_body     = నిజం;
      current_scope->keep              = నిజం;
      current_scope->outer_function    = current_function_scope;
      current_function_scope           = current_scope;

      keep_తదుపరి_level_flag = అబద్ధం;
      తదుపరి_is_function_body = అబద్ధం;

      /* The FLOAT_CONST_DECIMAL64 pragma applies to nested scopes.  */
      ఒకవేళ (current_scope->outer)
	current_scope->float_const_decimal64
	  = current_scope->outer->float_const_decimal64;
      లేకపోతే
	current_scope->float_const_decimal64 = అబద్ధం;
    }
  లేకపోతే
    {
      నిర్మాణం c_scope *scope;
      ఒకవేళ (scope_freelist)
	{
	  scope = scope_freelist;
	  scope_freelist = scope->outer;
	}
      లేకపోతే
	scope = ggc_cleared_alloc<c_scope> ();

      /* The FLOAT_CONST_DECIMAL64 pragma applies to nested scopes.  */
      ఒకవేళ (current_scope)
	scope->float_const_decimal64 = current_scope->float_const_decimal64;
      లేకపోతే
	scope->float_const_decimal64 = అబద్ధం;

      scope->keep          = keep_తదుపరి_level_flag;
      scope->outer         = current_scope;
      scope->లోతు	   = current_scope ? (current_scope->లోతు + 1) : 0;

      /* Check for scope depth overflow.  Unlikely (2^28 == 268,435,456) but
	 possible.  */
      ఒకవేళ (current_scope && scope->లోతు == 0)
	{
	  scope->లోతు--;
	  sorry ("GCC supports only %u nested scopes", scope->లోతు);
	}

      current_scope        = scope;
      keep_తదుపరి_level_flag = అబద్ధం;
    }
}

/* This is called when we are leaving SCOPE.  For each label defined
   in SCOPE, add any appropriate decls to its decls_in_scope fields.
   These are the decls whose initialization will be skipped by a goto
   later in the function.  */

స్థిర శూన్య
update_label_decls (నిర్మాణం c_scope *scope)
{
  నిర్మాణం c_scope *s;

  s = scope;
  అయితే (s != ఖాళీ)
    {
      ఒకవేళ (s->has_label_bindings)
	{
	  నిర్మాణం c_binding *b;

	  కొరకు (b = s->bindings; b != ఖాళీ; b = b->prev)
	    {
	      నిర్మాణం c_label_vars *label_vars;
	      నిర్మాణం c_binding *b1;
	      తార్కిక hjud;
	      గుర్తులేని పూర్ణాంకం ix;
	      నిర్మాణం c_goto_bindings *g;

	      ఒకవేళ (వృక్షం_సంకేతం (b->decl) != LABEL_DECL)
		కొనసాగు;
	      label_vars = b->u.label;

	      b1 = label_vars->label_bindings.bindings_లోపల_scope;
	      ఒకవేళ (label_vars->label_bindings.scope == ఖాళీ)
		hjud = అబద్ధం;
	      లేకపోతే
		hjud = label_vars->label_bindings.scope->has_jump_unsafe_decl;
	      ఒకవేళ (update_spot_bindings (scope, &label_vars->label_bindings))
		{
		  /* This label is defined in this scope.  */
		  ఒకవేళ (hjud)
		    {
		      కొరకు (; b1 != ఖాళీ; b1 = b1->prev)
			{
			  /* A goto from later in the function to this
			     label will never see the initialization
			     of B1, if any.  Save it to issue a
			     warning if needed.  */
			  ఒకవేళ (decl_jump_unsafe (b1->decl))
			    vec_సురక్షిత_నెట్టు(label_vars->decls_లోపల_scope, b1->decl);
			}
		    }
		}

	      /* Update the bindings of any goto statements associated
		 with this label.  */
	      FOR_EACH_VEC_సురక్షిత_ELT (label_vars->gotos, ix, g)
		update_spot_bindings (scope, &g->goto_bindings);
	    }
	}

      /* Don't search beyond the current function.  */
      ఒకవేళ (s == current_function_scope)
	ఆపు;

      s = s->outer;
    }
}

/* Exit a scope.  Restore the state of the identifier-decl mappings
   that were in effect when this scope was entered.  Return a BLOCK
   node containing all the DECLs in this scope that are of interest
   to debug info generation.  */

వృక్షం
తీయి_scope (శూన్య)
{
  నిర్మాణం c_scope *scope = current_scope;
  వృక్షం ఖండం, context, p;
  నిర్మాణం c_binding *b;

  తార్కిక functionbody = scope->function_body;
  తార్కిక keep = functionbody || scope->keep || scope->bindings;

  update_label_decls (scope);

  /* If appropriate, create a BLOCK to record the decls for the life
     of this function.  */
  ఖండం = NULL_వృక్షం;
  ఒకవేళ (keep)
    {
      ఖండం = make_కణుపు (ఖండం_2);
      ఖండం_SUBBLOCKS (ఖండం) = scope->ఖండాలు;
      వృక్షం_వాడిన (ఖండం) = 1;

      /* In each subblock, record that this is its superior.  */
      కొరకు (p = scope->ఖండాలు; p; p = ఖండం_CHAIN (p))
	ఖండం_SUPERCONTEXT (p) = ఖండం;

      ఖండం_VARS (ఖండం) = NULL_వృక్షం;
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
  ఒకవేళ (scope->function_body)
    context = current_function_decl;
  లేకపోతే ఒకవేళ (scope == file_scope)
    {
      వృక్షం file_decl
	= build_translation_unit_decl (get_identifier (main_ఆదానం_filename));
      context = file_decl;
      debug_hooks->రిజిస్టరు_main_translation_unit (file_decl);
    }
  లేకపోతే
    context = ఖండం;

  /* Clear all bindings in this scope.  */
  కొరకు (b = scope->bindings; b; b = free_binding_and_advance (b))
    {
      p = b->decl;
      ఎంపిక (వృక్షం_సంకేతం (p))
	{
	స్థితి LABEL_DECL:
	  /* Warnings for unused labels, errors for undefined labels.  */
	  ఒకవేళ (వృక్షం_వాడిన (p) && !DECL_INITIAL (p))
	    {
	      error ("label %q+D used but not defined", p);
	      DECL_INITIAL (p) = error_mark_కణుపు;
	    }
	  లేకపోతే
	    warn_for_వాడని_label (p);

	  /* Labels go in BLOCK_VARS.  */
	  DECL_CHAIN (p) = ఖండం_VARS (ఖండం);
	  ఖండం_VARS (ఖండం) = p;
	  gcc_assert (I_LABEL_BINDING (b->id) == b);
	  I_LABEL_BINDING (b->id) = b->shadowed;

	  /* Also pop back to the shadowed label_vars.  */
	  release_వృక్షం_సదిశ (b->u.label->decls_లోపల_scope);
	  b->u.label = b->u.label->shadowed;
	  ఆపు;

	స్థితి ENUMERAL_TYPE:
	స్థితి UNION_TYPE:
	స్థితి రికార్డు_TYPE:

	  /* Types may not have tag-names, in which case the type
	     appears in the bindings list with b->id NULL.  */
	  ఒకవేళ (b->id)
	    {
	      gcc_assert (I_ట్యాగ్_BINDING (b->id) == b);
	      I_ట్యాగ్_BINDING (b->id) = b->shadowed;
	    }
	  ఆపు;

	స్థితి FUNCTION_DECL:
	  /* Propagate TREE_ADDRESSABLE from nested functions to their
	     containing functions.  */
	  ఒకవేళ (!వృక్షం_ASM_WRITTEN (p)
	      && DECL_INITIAL (p) != NULL_వృక్షం
	      && వృక్షం_ADDRESSABLE (p)
	      && DECL_ABSTRACT_ORIGIN (p) != NULL_వృక్షం
	      && DECL_ABSTRACT_ORIGIN (p) != p)
	    వృక్షం_ADDRESSABLE (DECL_ABSTRACT_ORIGIN (p)) = 1;
	  ఒకవేళ (!వృక్షం_ప్రజా (p)
	      && !DECL_INITIAL (p)
	      && !b->nested
	      && scope != file_scope
	      && scope != external_scope)
	    {
	      error ("nested function %q+D declared but never defined", p);
	      undef_nested_function = నిజం;
	    }
	  లేకపోతే ఒకవేళ (DECL_DECLARED_INLINE_P (p)
		   && వృక్షం_ప్రజా (p)
		   && !DECL_INITIAL (p))
	    {
	      /* C99 6.7.4p6: "a function with external linkage... declared
		 with an inline function specifier ... shall also be defined
		 in the same translation unit."  */
	      ఒకవేళ (!flag_gnu89_inline
		  && !lookup_attribute ("gnu_inline", DECL_లక్షణాలు (p))
		  && scope == external_scope)
		pedwarn (ఆదానం_location, 0,
			 "inline function %q+D declared but never defined", p);
	      DECL_EXTERNAL (p) = 1;
	    }

	  వెళ్ళు common_చిహ్నం;

	స్థితి VAR_DECL:
	  /* Warnings for unused variables.  */
	  ఒకవేళ ((!వృక్షం_వాడిన (p) || !DECL_READ_P (p))
	      && !warning_suppressed_p (p, OPT_Wunused_but_సమితి_variable)
	      && !DECL_లోపల_SYSTEM_శీర్షిక (p)
	      && DECL_NAME (p)
	      && !DECL_ARTIFICIAL (p)
	      && scope != file_scope
	      && scope != external_scope)
	    {
	      ఒకవేళ (!వృక్షం_వాడిన (p))
		{
		  warning (OPT_Wunused_variable, "unused variable %q+D", p);
		  suppress_warning (p, OPT_Wunused_variable);
		}
	      లేకపోతే ఒకవేళ (DECL_CONTEXT (p) == current_function_decl)
		warning_at (DECL_ఆధారం_LOCATION (p),
			    OPT_Wunused_but_సమితి_variable,
			    "variable %qD set but not used", p);
	    }

	  ఒకవేళ (b->inner_comp)
	    {
	      error ("type of array %q+D completed incompatibly with"
		     " implicit initialization", p);
	    }

	  /* Fall through.  */
	స్థితి TYPE_DECL:
	స్థితి CONST_DECL:
	common_చిహ్నం:
	  /* All of these go in BLOCK_VARS, but only if this is the
	     binding in the home scope.  */
	  ఒకవేళ (!b->nested)
	    {
	      DECL_CHAIN (p) = ఖండం_VARS (ఖండం);
	      ఖండం_VARS (ఖండం) = p;
	    }
	  లేకపోతే ఒకవేళ (VAR_OR_FUNCTION_DECL_P (p) && scope != file_scope)
	    {
	      /* For block local externs add a special
		 DECL_EXTERNAL decl for debug info generation.  */
	      వృక్షం extp = copy_కణుపు (p);

	      DECL_EXTERNAL (extp) = 1;
	      వృక్షం_STATIC (extp) = 0;
	      వృక్షం_ప్రజా (extp) = 1;
	      DECL_INITIAL (extp) = NULL_వృక్షం;
	      DECL_LANG_SPECIFIC (extp) = ఖాళీ;
	      DECL_CONTEXT (extp) = current_function_decl;
	      ఒకవేళ (వృక్షం_సంకేతం (p) == FUNCTION_DECL)
		{
		  DECL_ఫలితం (extp) = NULL_వృక్షం;
		  DECL_SAVED_వృక్షం (extp) = NULL_వృక్షం;
		  DECL_STRUCT_FUNCTION (extp) = ఖాళీ;
		}
	      ఒకవేళ (b->locus != UNKNOWN_LOCATION)
		DECL_ఆధారం_LOCATION (extp) = b->locus;
	      DECL_CHAIN (extp) = ఖండం_VARS (ఖండం);
	      ఖండం_VARS (ఖండం) = extp;
	    }
	  /* If this is the file scope set DECL_CONTEXT of each decl to
	     the TRANSLATION_UNIT_DECL.  This makes same_translation_unit_p
	     work.  */
	  ఒకవేళ (scope == file_scope)
	      DECL_CONTEXT (p) = context;

	  gcc_fallthrough ();
	  /* Parameters go in DECL_ARGUMENTS, not BLOCK_VARS, and have
	     already been put there by store_parm_decls.  Unused-
	     parameter warnings are handled by function.cc.
	     error_mark_node obviously does not go in BLOCK_VARS and
	     does not get unused-variable warnings.  */
	స్థితి PARM_DECL:
	స్థితి ERROR_MARK:
	  /* It is possible for a decl not to have a name.  We get
	     here with b->id NULL in this case.  */
	  ఒకవేళ (b->id)
	    {
	      gcc_assert (I_చిహ్నం_BINDING (b->id) == b);
	      I_చిహ్నం_BINDING (b->id) = b->shadowed;
	      ఒకవేళ (b->shadowed && b->shadowed->u.type)
		వృక్షం_TYPE (b->shadowed->decl) = b->shadowed->u.type;
	    }
	  ఆపు;

	అప్రమేయ:
	  gcc_unreachable ();
	}
    }


  /* Dispose of the block that we just made inside some higher level.  */
  ఒకవేళ ((scope->function_body || scope == file_scope) && context)
    {
      DECL_INITIAL (context) = ఖండం;
      ఖండం_SUPERCONTEXT (ఖండం) = context;
    }
  లేకపోతే ఒకవేళ (scope->outer)
    {
      ఒకవేళ (ఖండం)
	SCOPE_LIST_APPEND (scope->outer, ఖండాలు, ఖండం);
      /* If we did not make a block for the scope just exited, any
	 blocks made for inner scopes must be carried forward so they
	 will later become subblocks of something else.  */
      లేకపోతే ఒకవేళ (scope->ఖండాలు)
	SCOPE_LIST_CONCAT (scope->outer, ఖండాలు, scope, ఖండాలు);
    }

  /* Pop the current scope, and free the structure for reuse.  */
  current_scope = scope->outer;
  ఒకవేళ (scope->function_body)
    current_function_scope = scope->outer_function;

  memset (scope, 0, పరిమాణం (నిర్మాణం c_scope));
  scope->outer = scope_freelist;
  scope_freelist = scope;

  తిరిగి ఖండం;
}

శూన్య
నెట్టు_file_scope (శూన్య)
{
  వృక్షం decl;

  ఒకవేళ (file_scope)
    తిరిగి;

  /* Call the target stack_protect_guard hook if the stack protection
     guard is declared as a global symbol.  */
  ఒకవేళ (targetm.దొంతర_protect_guard_చిహ్నం_p ())
    {
      వృక్షం decl = targetm.దొంతర_protect_guard ();
      DECL_CHAIN (decl) = visible_builtins;
      visible_builtins = decl;
    }

  నెట్టు_scope ();
  file_scope = current_scope;

  ప్రారంభం_fname_decls ();

  కొరకు (decl = visible_builtins; decl; decl = DECL_CHAIN (decl))
    bind (DECL_NAME (decl), decl, file_scope,
	  /*invisible=*/అబద్ధం, /*nested=*/నిజం, DECL_ఆధారం_LOCATION (decl));
}

శూన్య
తీయి_file_scope (శూన్య)
{
  /* In case there were missing closebraces, get us back to the global
     binding level.  */
  అయితే (current_scope != file_scope)
    తీయి_scope ();

  /* __FUNCTION__ is defined at file scope ("").  This
     call may not be necessary as my tests indicate it
     still works without it.  */
  ముగింపు_fname_decls ();

  check_inline_statics ();

  /* This is the point to write out a PCH if we're doing that.
     In that case we do not want to do anything else.  */
  ఒకవేళ (pch_file)
    {
      c_common_write_pch ();
      /* Ensure even the callers don't try to finalize the CU.  */
      flag_syntax_only = 1;
      తిరిగి;
    }

  /* Pop off the file scope and close this translation unit.  */
  తీయి_scope ();
  file_scope = 0;

  maybe_apply_pending_pragma_weaks ();
}

/* Whether we are currently inside the initializer for an
   underspecified object definition (C23 auto or constexpr).  */
స్థిర తార్కిక లోపల_underspecified_init;

/* Start an underspecified object definition for NAME at LOC.  This
   means that NAME is shadowed inside its initializer, so neither the
   definition being initialized, nor any definition from an outer
   scope, may be referenced during that initializer.  Return state to
   be passed to finish_underspecified_init.  If NAME is NULL_TREE, the
   underspecified object is a (constexpr) compound literal; there is
   no shadowing in that case, but all the other restrictions on
   underspecified object definitions still apply.  */
గుర్తులేని పూర్ణాంకం
ప్రారంభం_underspecified_init (location_t loc, వృక్షం name)
{
  తార్కిక prev = లోపల_underspecified_init;
  తార్కిక ok;
  ఒకవేళ (name == NULL_వృక్షం)
    ok = నిజం;
  లేకపోతే
    {
      వృక్షం decl = build_decl (loc, VAR_DECL, name, error_mark_కణుపు);
      C_DECL_UNDERSPECIFIED (decl) = 1;
      నిర్మాణం c_scope *scope = current_scope;
      నిర్మాణం c_binding *b = I_చిహ్నం_BINDING (name);
      ఒకవేళ (b && B_లోపల_SCOPE (b, scope))
	{
	  error_at (loc, "underspecified declaration of %qE, which is already "
		    "declared in this scope", name);
	  ok = అబద్ధం;
	}
      లేకపోతే
	{
	  bind (name, decl, scope, అబద్ధం, అబద్ధం, loc);
	  ok = నిజం;
	}
    }
  లోపల_underspecified_init = నిజం;
  తిరిగి ok | (prev << 1);
}

/* Finish an underspecified object definition for NAME, before that
   name is bound to the real declaration instead of a placeholder.
   PREV_STATE is the value returned by the call to
   start_underspecified_init.  If NAME is NULL_TREE, this means a
   compound literal, as for start_underspecified_init.  */
శూన్య
ముగింపు_underspecified_init (వృక్షం name, గుర్తులేని పూర్ణాంకం prev_state)
{
  ఒకవేళ (name != NULL_వృక్షం && (prev_state & 1))
    {
      /* A VAR_DECL was bound to the name to shadow any previous
	 declarations for the name; remove that binding now.  */
      నిర్మాణం c_scope *scope = current_scope;
      నిర్మాణం c_binding *b = I_చిహ్నం_BINDING (name);
      gcc_assert (b);
      gcc_assert (B_లోపల_SCOPE (b, scope));
      gcc_assert (VAR_P (b->decl));
      gcc_assert (C_DECL_UNDERSPECIFIED (b->decl));
      I_చిహ్నం_BINDING (name) = b->shadowed;
      /* In erroneous cases there may be other bindings added to this
	 scope during the initializer.  */
      నిర్మాణం c_binding **p = &scope->bindings;
      అయితే (*p != b)
	p = &((*p)->prev);
      *p = free_binding_and_advance (*p);
    }
  లోపల_underspecified_init = (prev_state & (1u << 1)) >> 1;
}

/* Adjust the bindings for the start of a statement expression.  */

శూన్య
c_bindings_ప్రారంభం_stmt_సమాసం (నిర్మాణం c_spot_bindings* switch_bindings)
{
  నిర్మాణం c_scope *scope;

  కొరకు (scope = current_scope; scope != ఖాళీ; scope = scope->outer)
    {
      నిర్మాణం c_binding *b;

      ఒకవేళ (!scope->has_label_bindings)
	కొనసాగు;

      కొరకు (b = scope->bindings; b != ఖాళీ; b = b->prev)
	{
	  నిర్మాణం c_label_vars *label_vars;
	  గుర్తులేని పూర్ణాంకం ix;
	  నిర్మాణం c_goto_bindings *g;

	  ఒకవేళ (వృక్షం_సంకేతం (b->decl) != LABEL_DECL)
	    కొనసాగు;
	  label_vars = b->u.label;
	  ++label_vars->label_bindings.stmt_exprs;
	  FOR_EACH_VEC_సురక్షిత_ELT (label_vars->gotos, ix, g)
	    ++g->goto_bindings.stmt_exprs;
	}
    }

  ఒకవేళ (switch_bindings != ఖాళీ)
    ++switch_bindings->stmt_exprs;
}

/* Adjust the bindings for the end of a statement expression.  */

శూన్య
c_bindings_చివర_stmt_సమాసం (నిర్మాణం c_spot_bindings *switch_bindings)
{
  నిర్మాణం c_scope *scope;

  కొరకు (scope = current_scope; scope != ఖాళీ; scope = scope->outer)
    {
      నిర్మాణం c_binding *b;

      ఒకవేళ (!scope->has_label_bindings)
	కొనసాగు;

      కొరకు (b = scope->bindings; b != ఖాళీ; b = b->prev)
	{
	  నిర్మాణం c_label_vars *label_vars;
	  గుర్తులేని పూర్ణాంకం ix;
	  నిర్మాణం c_goto_bindings *g;

	  ఒకవేళ (వృక్షం_సంకేతం (b->decl) != LABEL_DECL)
	    కొనసాగు;
	  label_vars = b->u.label;
	  --label_vars->label_bindings.stmt_exprs;
	  ఒకవేళ (label_vars->label_bindings.stmt_exprs < 0)
	    {
	      label_vars->label_bindings.ఎడమ_stmt_సమాసం = నిజం;
	      label_vars->label_bindings.stmt_exprs = 0;
	    }
	  FOR_EACH_VEC_సురక్షిత_ELT (label_vars->gotos, ix, g)
	    {
	      --g->goto_bindings.stmt_exprs;
	      ఒకవేళ (g->goto_bindings.stmt_exprs < 0)
		{
		  g->goto_bindings.ఎడమ_stmt_సమాసం = నిజం;
		  g->goto_bindings.stmt_exprs = 0;
		}
	    }
	}
    }

  ఒకవేళ (switch_bindings != ఖాళీ)
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

స్థిర శూన్య
pushtag (location_t loc, వృక్షం name, వృక్షం type)
{
  /* Record the identifier as the type's name if it has none.  */
  ఒకవేళ (name && !TYPE_NAME (type))
    TYPE_NAME (type) = name;
  bind (name, type, current_scope, /*invisible=*/అబద్ధం, /*nested=*/అబద్ధం, loc);

  /* Create a fake NULL-named TYPE_DECL node whose TREE_TYPE will be the
     tagged type we just added to the current scope.  This fake
     NULL-named TYPE_DECL node helps dwarfout.c to know when it needs
     to output a representation of a tagged type, and it also gives
     us a convenient place to record the "scope start" address for the
     tagged type, and it is used to track whether the type is used
     in a non-local context via mark_decl_used.  */

  TYPE_STUB_DECL (type) = pushdecl (build_decl (loc,
						TYPE_DECL, NULL_వృక్షం, type));

  /* An approximation for now, so we can tell this is a function-scope tag.
     This will be updated in pop_scope.  */
  TYPE_CONTEXT (type) = DECL_CONTEXT (TYPE_STUB_DECL (type));

  ఒకవేళ (warn_cxx_compat && name != NULL_వృక్షం)
    {
      నిర్మాణం c_binding *b = I_చిహ్నం_BINDING (name);

      ఒకవేళ (b != ఖాళీ
	  && b->decl != NULL_వృక్షం
	  && వృక్షం_సంకేతం (b->decl) == TYPE_DECL
	  && (B_లోపల_CURRENT_SCOPE (b)
	      || (current_scope == file_scope && B_లోపల_EXTERNAL_SCOPE (b)))
	  && (TYPE_MAIN_VARIANT (వృక్షం_TYPE (b->decl))
	      != TYPE_MAIN_VARIANT (type)))
	{
	  auto_diagnostic_సమూహం d;
	  ఒకవేళ (warning_at (loc, OPT_Wc___compat,
			  "using %qD as both a typedef and a tag is "
			  "invalid in C++", b->decl)
	      && b->locus != UNKNOWN_LOCATION)
	    inform (b->locus, "originally defined here");
	}
    }
}

/* An exported interface to pushtag.  This is used by the gdb plugin's
   binding oracle to introduce a new tag binding.  */

శూన్య
c_pushtag (location_t loc, వృక్షం name, వృక్షం type)
{
  pushtag (loc, name, type);
}

/* An exported interface to bind a declaration.  LOC is the location
   to use.  DECL is the declaration to bind.  The decl's name is used
   to determine how it is bound.  If DECL is a VAR_DECL, then
   IS_GLOBAL determines whether the decl is put into the global (file
   and external) scope or the current function's scope; if DECL is not
   a VAR_DECL then it is always put into the file scope.  */

శూన్య
c_bind (location_t loc, వృక్షం decl, తార్కిక is_global)
{
  నిర్మాణం c_scope *scope;
  తార్కిక nested = అబద్ధం;

  ఒకవేళ (!VAR_P (decl) || current_function_scope == ఖాళీ)
    {
      /* Types and functions are always considered to be global.  */
      scope = file_scope;
      DECL_EXTERNAL (decl) = 1;
      వృక్షం_ప్రజా (decl) = 1;
    }
  లేకపోతే ఒకవేళ (is_global)
    {
      /* Also bind it into the external scope.  */
      bind (DECL_NAME (decl), decl, external_scope, నిజం, అబద్ధం, loc);
      nested = నిజం;
      scope = file_scope;
      DECL_EXTERNAL (decl) = 1;
      వృక్షం_ప్రజా (decl) = 1;
    }
  లేకపోతే
    {
      DECL_CONTEXT (decl) = current_function_decl;
      వృక్షం_ప్రజా (decl) = 0;
      scope = current_function_scope;
    }

  bind (DECL_NAME (decl), decl, scope, అబద్ధం, nested, loc);
}


/* Stores the first FILE*, const struct tm* etc. argument type (whatever
   it is) seen in a declaration of a file I/O etc. built-in, corresponding
   to the builtin_structptr_types array.  Subsequent declarations of such
   built-ins are expected to refer to it rather than to fileptr_type_node,
   etc. which is just void* (or to any other type).
   Used only by match_builtin_function_types.  */

స్థిర స్థిరరాశి గుర్తులేని builtin_structptr_type_లెక్క
  = ARRAY_కొలత (builtin_structptr_types);

స్థిర GTY(()) వృక్షం చివరి_structptr_types[builtin_structptr_type_లెక్క];

/* Returns true if types T1 and T2 representing return types or types
   of function arguments are close enough to be considered interchangeable
   in redeclarations of built-in functions.  */

స్థిర తార్కిక
types_close_enough_గమ్యం_సరిపోలిక (వృక్షం t1, వృక్షం t2)
{
  తిరిగి (TYPE_బహుళకం (t1) == TYPE_బహుళకం (t2)
	  && సూచిక_TYPE_P (t1) == సూచిక_TYPE_P (t2)
	  && FUNCTION_సూచిక_TYPE_P (t1) == FUNCTION_సూచిక_TYPE_P (t2));
}

/* Subroutine of compare_decls.  Allow harmless mismatches in return
   and argument types provided that the type modes match.  Set *STRICT
   and *ARGNO to the expected argument type and number in case of
   an argument type mismatch or null and zero otherwise.  Return
   a unified type given a suitable match, and 0 otherwise.  */

స్థిర వృక్షం
సరిపోలిక_builtin_function_types (వృక్షం newtype, వృక్షం oldtype,
			      వృక్షం *strict, గుర్తులేని *argno)
{
  *argno = 0;
  *strict = NULL_వృక్షం;

  /* Accept the return type of the new declaration if it has the same
     mode and if they're both pointers or if neither is.  */
  వృక్షం oldrettype = వృక్షం_TYPE (oldtype);
  వృక్షం newrettype = వృక్షం_TYPE (newtype);

  ఒకవేళ (!types_close_enough_గమ్యం_సరిపోలిక (oldrettype, newrettype))
    తిరిగి NULL_వృక్షం;

  /* Check that the return types are compatible but don't fail if they
     are not (e.g., int vs long in ILP32) and just let the caller know.  */
  ఒకవేళ (!comptypes (TYPE_MAIN_VARIANT (oldrettype),
		  TYPE_MAIN_VARIANT (newrettype)))
    *strict = oldrettype;

  వృక్షం oldargs = TYPE_ARG_TYPES (oldtype);
  వృక్షం newargs = TYPE_ARG_TYPES (newtype);
  వృక్షం tryargs = newargs;

  స్థిరరాశి గుర్తులేని nlst = ARRAY_కొలత (చివరి_structptr_types);
  స్థిరరాశి గుర్తులేని nbst = ARRAY_కొలత (builtin_structptr_types);

  gcc_checking_assert (nlst == nbst);

  కొరకు (గుర్తులేని i = 1; oldargs || newargs; ++i)
    {
      ఒకవేళ (!oldargs
	  || !newargs
	  || !వృక్షం_విలువ (oldargs)
	  || !వృక్షం_విలువ (newargs))
	తిరిగి NULL_వృక్షం;

      వృక్షం oldtype = TYPE_MAIN_VARIANT (వృక్షం_విలువ (oldargs));
      వృక్షం newtype = వృక్షం_విలువ (newargs);
      ఒకవేళ (newtype == error_mark_కణుపు)
       తిరిగి NULL_వృక్షం;
      newtype = TYPE_MAIN_VARIANT (newtype);

      ఒకవేళ (!types_close_enough_గమ్యం_సరిపోలిక (oldtype, newtype))
	తిరిగి NULL_వృక్షం;

      గుర్తులేని j = nbst;
      ఒకవేళ (సూచిక_TYPE_P (oldtype))
	/* Iterate over well-known struct types like FILE (whose types
	   aren't known to us) and compare the pointer to each to
	   the pointer argument.  */
	కొరకు (j = 0; j < nbst; ++j)
	  {
	    ఒకవేళ (వృక్షం_విలువ (oldargs) != builtin_structptr_types[j].కణుపు)
	      కొనసాగు;
	    /* Store the first FILE* etc. argument type (whatever it is), and
	       expect any subsequent declarations of file I/O etc. built-ins
	       to refer to it rather than to fileptr_type_node etc. which is
	       just void* (or const void*).  */
	    ఒకవేళ (చివరి_structptr_types[j])
	      {
		ఒకవేళ (!comptypes (చివరి_structptr_types[j], newtype))
		  {
		    *argno = i;
		    *strict = చివరి_structptr_types[j];
		  }
	      }
	    లేకపోతే
	      చివరి_structptr_types[j] = newtype;
	    ఆపు;
	  }

      ఒకవేళ (j == nbst && !comptypes (oldtype, newtype))
	{
	  ఒకవేళ (సూచిక_TYPE_P (oldtype))
	    {
	      /* For incompatible pointers, only reject differences in
		 the unqualified variants of the referenced types but
		 consider differences in qualifiers as benign (report
		 those to caller via *STRICT below).  */
	      వృక్షం oldref = TYPE_MAIN_VARIANT (వృక్షం_TYPE (oldtype));
	      వృక్షం newref = TYPE_MAIN_VARIANT (వృక్షం_TYPE (newtype));
	      ఒకవేళ (!comptypes (oldref, newref))
		తిరిగి NULL_వృక్షం;
	    }

	  ఒకవేళ (!*strict)
	    {
	      *argno = i;
	      *strict = oldtype;
	    }
	}

      oldargs = వృక్షం_CHAIN (oldargs);
      newargs = వృక్షం_CHAIN (newargs);
    }

  వృక్షం trytype = c_build_function_type (newrettype, tryargs);

  /* Allow declaration to change transaction_safe attribute.  */
  వృక్షం oldattrs = TYPE_లక్షణాలు (oldtype);
  వృక్షం oldtsafe = lookup_attribute ("transaction_safe", oldattrs);
  వృక్షం newattrs = TYPE_లక్షణాలు (newtype);
  వృక్షం newtsafe = lookup_attribute ("transaction_safe", newattrs);
  ఒకవేళ (oldtsafe && !newtsafe)
    oldattrs = remove_attribute ("transaction_safe", oldattrs);
  లేకపోతే ఒకవేళ (newtsafe && !oldtsafe)
    oldattrs = వృక్షం_cons (get_identifier ("transaction_safe"),
			  NULL_వృక్షం, oldattrs);

  తిరిగి c_build_type_attribute_variant (trytype, oldattrs);
}

/* Subroutine of diagnose_mismatched_decls.  Check for function type
   mismatch involving an empty arglist vs a nonempty one and give clearer
   diagnostics.  */
స్థిర శూన్య
diagnose_arglist_conflict (వృక్షం newdecl, వృక్షం olddecl,
			   వృక్షం newtype, వృక్షం oldtype)
{
  వృక్షం t;

  ఒకవేళ (వృక్షం_సంకేతం (olddecl) != FUNCTION_DECL
      || !comptypes (వృక్షం_TYPE (oldtype), వృక్షం_TYPE (newtype))
      || !((!prototype_p (oldtype) && DECL_INITIAL (olddecl) == NULL_వృక్షం)
	   || (!prototype_p (newtype) && DECL_INITIAL (newdecl) == NULL_వృక్షం)))
    తిరిగి;

  t = TYPE_ARG_TYPES (oldtype);
  ఒకవేళ (t == NULL_వృక్షం)
    t = TYPE_ARG_TYPES (newtype);
  కొరకు (; t; t = వృక్షం_CHAIN (t))
    {
      వృక్షం type = వృక్షం_విలువ (t);

      ఒకవేళ (వృక్షం_CHAIN (t) == NULL_వృక్షం
	  && TYPE_MAIN_VARIANT (type) != void_type_కణుపు)
	{
	  inform (ఆదానం_location, "a parameter list with an ellipsis "
		  "cannot match an empty parameter name list declaration");
	  ఆపు;
	}

      ఒకవేళ (!error_నిర్వాహ్యం_p (type)
	  && c_type_promotes_గమ్యం (type) != type)
	{
	  inform (ఆదానం_location, "an argument type that has a default "
		  "promotion cannot match an empty parameter name list "
		  "declaration");
	  ఆపు;
	}
    }
}

/* Another subroutine of diagnose_mismatched_decls.  OLDDECL is an
   old-style function definition, NEWDECL is a prototype declaration.
   Diagnose inconsistencies in the argument list.  Returns TRUE if
   the prototype is compatible, FALSE if not.  */
స్థిర తార్కిక
validate_proto_after_old_defn (వృక్షం newdecl, వృక్షం newtype, వృక్షం oldtype)
{
  వృక్షం newargs, oldargs;
  పూర్ణాంకం i;

#నిర్వచించు చివర_యొక్క_ARGLIST(t) ((t) == void_type_కణుపు)

  oldargs = TYPE_ACTUAL_ARG_TYPES (oldtype);
  newargs = TYPE_ARG_TYPES (newtype);
  i = 1;

  కొరకు (;;)
    {
      వృక్షం oldargtype = వృక్షం_విలువ (oldargs);
      వృక్షం newargtype = వృక్షం_విలువ (newargs);

      ఒకవేళ (oldargtype == error_mark_కణుపు || newargtype == error_mark_కణుపు)
	తిరిగి అబద్ధం;

      oldargtype = (TYPE_ATOMIC (oldargtype)
		    ? c_build_qualified_type (TYPE_MAIN_VARIANT (oldargtype),
					      TYPE_QUAL_ATOMIC)
		    : TYPE_MAIN_VARIANT (oldargtype));
      newargtype = (TYPE_ATOMIC (newargtype)
		    ? c_build_qualified_type (TYPE_MAIN_VARIANT (newargtype),
					      TYPE_QUAL_ATOMIC)
		    : TYPE_MAIN_VARIANT (newargtype));

      ఒకవేళ (చివర_యొక్క_ARGLIST (oldargtype) && చివర_యొక్క_ARGLIST (newargtype))
	ఆపు;

      /* Reaching the end of just one list means the two decls don't
	 agree on the number of arguments.  */
      ఒకవేళ (చివర_యొక్క_ARGLIST (oldargtype))
	{
	  error ("prototype for %q+D declares more arguments "
		 "than previous old-style definition", newdecl);
	  తిరిగి అబద్ధం;
	}
      లేకపోతే ఒకవేళ (చివర_యొక్క_ARGLIST (newargtype))
	{
	  error ("prototype for %q+D declares fewer arguments "
		 "than previous old-style definition", newdecl);
	  తిరిగి అబద్ధం;
	}

      /* Type for passing arg must be consistent with that declared
	 for the arg.  */
      లేకపోతే ఒకవేళ (!comptypes (oldargtype, newargtype))
	{
	  error ("prototype for %q+D declares argument %d"
		 " with incompatible type",
		 newdecl, i);
	  తిరిగి అబద్ధం;
	}

      oldargs = వృక్షం_CHAIN (oldargs);
      newargs = వృక్షం_CHAIN (newargs);
      i++;
    }

  /* If we get here, no errors were found, but do issue a warning
     for this poor-style construct.  */
  warning (0, "prototype for %q+D follows non-prototype definition",
	   newdecl);
  తిరిగి నిజం;
#నిర్వచనం_రద్దు చివర_యొక్క_ARGLIST
}

/* Subroutine of diagnose_mismatched_decls.  Report the location of DECL,
   first in a pair of mismatched declarations, using the diagnostic
   function DIAG.  */
స్థిర శూన్య
locate_old_decl (వృక్షం decl)
{
  ఒకవేళ (వృక్షం_సంకేతం (decl) == FUNCTION_DECL
      && fndecl_built_లోపల_p (decl)
      && !C_DECL_DECLARED_BUILTIN (decl))
    ;
  లేకపోతే ఒకవేళ (DECL_INITIAL (decl))
    inform (ఆదానం_location,
	    "previous definition of %q+D with type %qT",
	    decl, వృక్షం_TYPE (decl));
  లేకపోతే ఒకవేళ (C_DECL_IMPLICIT (decl))
    inform (ఆదానం_location,
	    "previous implicit declaration of %q+D with type %qT",
	    decl, వృక్షం_TYPE (decl));
  లేకపోతే
    inform (ఆదానం_location,
	    "previous declaration of %q+D with type %qT",
	    decl, వృక్షం_TYPE (decl));
}


/* Helper function.  For a tagged type, it finds the declaration
   for a visible tag declared in the same scope if such a
   declaration exists.  */
స్థిర వృక్షం
మునుపటి_ట్యాగ్ (వృక్షం type)
{
  నిర్మాణం c_binding *b = ఖాళీ;
  వృక్షం name = c_type_ట్యాగ్ (type);

  ఒకవేళ (name)
    b = I_ట్యాగ్_BINDING (name);

  ఒకవేళ (b)
    b = b->shadowed;

  ఒకవేళ (b && B_లోపల_CURRENT_SCOPE (b))
    తిరిగి b->decl;

  తిరిగి NULL_వృక్షం;
}

/* Subroutine to mark functions as versioned when using the attribute
   'target_version'.  */

స్థిర శూన్య
maybe_mark_function_versioned (వృక్షం decl)
{
  ఒకవేళ (!DECL_FUNCTION_VERSIONED (decl))
    {
      /* Check if the name of the function has been overridden.  */
      ఒకవేళ (DECL_ASSEMBLER_NAME_సమితి_P (decl)
	  && IDENTIFIER_సూచిక (DECL_ASSEMBLER_NAME (decl))[0] == '*')
	error_at (DECL_ఆధారం_LOCATION (decl),
		  "cannot use function multiversioning on a renamed function");

      /* We need to insert function version now to make sure the correct
	 pre-mangled assembler name is recorded.  */
      cgraph_కణుపు *కణుపు = cgraph_కణుపు::get_create (decl);

      ఒకవేళ (!కణుపు->function_సంస్కరణ ())
	కణుపు->చొప్పించు_new_function_సంస్కరణ ();

      DECL_FUNCTION_VERSIONED (decl) = 1;

      వృక్షం mangled_name
	= targetm.mangle_decl_assembler_name (decl, DECL_NAME (decl));
      సమితి_DECL_ASSEMBLER_NAME (decl, mangled_name);
    }
}

/* Subroutine of duplicate_decls.  Compare NEWDECL to OLDDECL.
   Returns true if the caller should proceed to merge the two, false
   if OLDDECL should simply be discarded.  As a side effect, issues
   all necessary diagnostics for invalid or poor-style combinations.
   If it returns true, writes the types of NEWDECL and OLDDECL to
   *NEWTYPEP and *OLDTYPEP - these may have been adjusted from
   TREE_TYPE (NEWDECL, OLDDECL) respectively.  */

స్థిర తార్కిక
diagnose_mismatched_decls (వృక్షం newdecl, వృక్షం olddecl,
			   వృక్షం *newtypep, వృక్షం *oldtypep)
{
  వృక్షం newtype, oldtype;
  తార్కిక retval = నిజం;

#నిర్వచించు DECL_EXTERN_INLINE(DECL) (DECL_DECLARED_INLINE_P (DECL)  \
				  && DECL_EXTERNAL (DECL))

  /* If we have error_mark_node for either decl or type, just discard
     the previous decl - we're in an error cascade already.  */
  ఒకవేళ (olddecl == error_mark_కణుపు || newdecl == error_mark_కణుపు)
    తిరిగి అబద్ధం;
  *oldtypep = oldtype = వృక్షం_TYPE (olddecl);
  *newtypep = newtype = వృక్షం_TYPE (newdecl);
  ఒకవేళ (oldtype == error_mark_కణుపు || newtype == error_mark_కణుపు)
    తిరిగి అబద్ధం;

  /* Two different categories of symbol altogether.  This is an error
     unless OLDDECL is a builtin.  OLDDECL will be discarded in any case.  */
  ఒకవేళ (వృక్షం_సంకేతం (olddecl) != వృక్షం_సంకేతం (newdecl))
    {
      ఒకవేళ (!(వృక్షం_సంకేతం (olddecl) == FUNCTION_DECL
	    && fndecl_built_లోపల_p (olddecl)
	    && !C_DECL_DECLARED_BUILTIN (olddecl)))
	{
	  auto_diagnostic_సమూహం d;
	  error ("%q+D redeclared as different kind of symbol", newdecl);
	  locate_old_decl (olddecl);
	}
      లేకపోతే ఒకవేళ (వృక్షం_ప్రజా (newdecl))
	warning (OPT_Wbuiltin_declaration_mismatch,
		 "built-in function %q+D declared as non-function",
		 newdecl);
      లేకపోతే
	warning (OPT_Wshadow, "declaration of %q+D shadows "
		 "a built-in function", newdecl);
      తిరిగి అబద్ధం;
    }

  /* Enumerators have no linkage, so may only be declared once in a
     given scope.  */
  ఒకవేళ (వృక్షం_సంకేతం (olddecl) == CONST_DECL)
    {
      ఒకవేళ (flag_isoc23
	  && TYPE_NAME (DECL_CONTEXT (newdecl))
	  && DECL_CONTEXT (newdecl) != DECL_CONTEXT (olddecl)
	  && TYPE_NAME (DECL_CONTEXT (newdecl)) == TYPE_NAME (DECL_CONTEXT (olddecl)))
	{
	  ఒకవేళ (!simple_cst_equal (DECL_INITIAL (olddecl), DECL_INITIAL (newdecl)))
	    {
	      auto_diagnostic_సమూహం d;
	      error ("conflicting redeclaration of enumerator %q+D", newdecl);
	      locate_old_decl (olddecl);
	    }
	}
      లేకపోతే
	{
	  auto_diagnostic_సమూహం d;
	  error ("redeclaration of enumerator %q+D", newdecl);
	  locate_old_decl (olddecl);
	}
      తిరిగి అబద్ధం;
    }

  తార్కిక pedwarned = అబద్ధం;
  తార్కిక warned = అబద్ధం;
  తార్కిక enum_and_int_p = అబద్ధం;
  auto_diagnostic_సమూహం d;

  తార్కిక comptypes_ఫలితం = comptypes_check_enum_int (oldtype, newtype,
						    &enum_and_int_p);
  ఒకవేళ (!comptypes_ఫలితం)
    {
      ఒకవేళ (వృక్షం_సంకేతం (olddecl) == FUNCTION_DECL
	  && fndecl_built_లోపల_p (olddecl, BUILT_లోపల_సాధారణ)
	  && !C_DECL_DECLARED_BUILTIN (olddecl))
	{
	  /* Accept "harmless" mismatches in function types such
	     as missing qualifiers or int vs long when they're the same
	     size.  However, diagnose return and argument types that are
	     incompatible according to language rules.  */
	  వృక్షం mismatch_expect;
	  గుర్తులేని mismatch_argno;

	  వృక్షం trytype = సరిపోలిక_builtin_function_types (newtype, oldtype,
						       &mismatch_expect,
						       &mismatch_argno);

	  ఒకవేళ (trytype && comptypes (newtype, trytype))
	    *oldtypep = oldtype = trytype;
	  లేకపోతే
	    {
	      /* If types don't match for a built-in, throw away the
		 built-in.  No point in calling locate_old_decl here, it
		 won't print anything.  */
	      స్థిరరాశి అక్షరం *శీర్షిక = శీర్షిక_for_builtin_fn (olddecl);
	      location_t loc = DECL_ఆధారం_LOCATION (newdecl);
	      ఒకవేళ (warning_at (loc, OPT_Wbuiltin_declaration_mismatch,
			      "conflicting types for built-in function %q+D; "
			      "expected %qT",
			      newdecl, oldtype)
		  && శీర్షిక)
		{
		  /* Suggest the right header to include as the preferred
		     solution rather than the spelling of the declaration.  */
		  rich_location richloc (పంక్తి_పట్టిక, loc);
		  maybe_కూడు_include_fixit (&richloc, శీర్షిక, నిజం);
		  inform (&richloc,
			  "%qD is declared in header %qs", olddecl, శీర్షిక);
		}
	      తిరిగి అబద్ధం;
	    }

	  ఒకవేళ (mismatch_expect && extra_warnings)
	    {
	      location_t newloc = DECL_ఆధారం_LOCATION (newdecl);
	      తార్కిక warned = అబద్ధం;
	      ఒకవేళ (mismatch_argno)
		warned = warning_at (newloc, OPT_Wbuiltin_declaration_mismatch,
				     "mismatch in argument %u type of built-in "
				     "function %qD; expected %qT",
				     mismatch_argno, newdecl, mismatch_expect);
	      లేకపోతే
		warned = warning_at (newloc, OPT_Wbuiltin_declaration_mismatch,
				     "mismatch in return type of built-in "
				     "function %qD; expected %qT",
				     newdecl, mismatch_expect);
	      స్థిరరాశి అక్షరం *శీర్షిక = శీర్షిక_for_builtin_fn (olddecl);
	      ఒకవేళ (warned && శీర్షిక)
		{
		  rich_location richloc (పంక్తి_పట్టిక, newloc);
		  maybe_కూడు_include_fixit (&richloc, శీర్షిక, నిజం);
		  inform (&richloc,
			  "%qD is declared in header %qs", olddecl, శీర్షిక);
		}
	    }
	}
      లేకపోతే ఒకవేళ (వృక్షం_సంకేతం (olddecl) == FUNCTION_DECL
	       && DECL_IS_UNDECLARED_BUILTIN (olddecl))
	{
	  /* A conflicting function declaration for a predeclared
	     function that isn't actually built in.  Objective C uses
	     these.  The new declaration silently overrides everything
	     but the volatility (i.e. noreturn) indication.  See also
	     below.  FIXME: Make Objective C use normal builtins.  */
	  వృక్షం_THIS_VOLATILE (newdecl) |= వృక్షం_THIS_VOLATILE (olddecl);
	  తిరిగి అబద్ధం;
	}
      /* Permit void foo (...) to match int foo (...) if the latter is
	 the definition and implicit int was used.  See
	 c-torture/compile/920625-2.c.  */
      లేకపోతే ఒకవేళ (వృక్షం_సంకేతం (newdecl) == FUNCTION_DECL && DECL_INITIAL (newdecl)
	       && TYPE_MAIN_VARIANT (వృక్షం_TYPE (oldtype)) == void_type_కణుపు
	       && TYPE_MAIN_VARIANT (వృక్షం_TYPE (newtype)) == integer_type_కణుపు
	       && C_FUNCTION_IMPLICIT_INT (newdecl) && !DECL_INITIAL (olddecl))
	{
	  pedwarned = pedwarn (ఆదానం_location, 0,
			       "conflicting types for %q+D", newdecl);
	  /* Make sure we keep void as the return type.  */
	  వృక్షం_TYPE (newdecl) = *newtypep = newtype = oldtype;
	  C_FUNCTION_IMPLICIT_INT (newdecl) = 0;
	}
      /* Permit void foo (...) to match an earlier call to foo (...) with
	 no declared type (thus, implicitly int).  */
      లేకపోతే ఒకవేళ (వృక్షం_సంకేతం (newdecl) == FUNCTION_DECL
	       && TYPE_MAIN_VARIANT (వృక్షం_TYPE (newtype)) == void_type_కణుపు
	       && TYPE_MAIN_VARIANT (వృక్షం_TYPE (oldtype)) == integer_type_కణుపు
	       && C_DECL_IMPLICIT (olddecl) && !DECL_INITIAL (olddecl))
	{
	  pedwarned = pedwarn (ఆదానం_location, 0,
			       "conflicting types for %q+D; have %qT",
			       newdecl, newtype);
	  /* Make sure we keep void as the return type.  */
	  వృక్షం_TYPE (olddecl) = *oldtypep = oldtype = newtype;
	}
      లేకపోతే
	{
	  పూర్ణాంకం new_quals = TYPE_QUALS (newtype);
	  పూర్ణాంకం old_quals = TYPE_QUALS (oldtype);

	  ఒకవేళ (new_quals != old_quals)
	    {
	      addr_space_t new_addr = DECODE_QUAL_ADDR_SPACE (new_quals);
	      addr_space_t old_addr = DECODE_QUAL_ADDR_SPACE (old_quals);
	      ఒకవేళ (new_addr != old_addr)
		{
		  ఒకవేళ (ADDR_SPACE_GENERIC_P (new_addr))
		    error ("conflicting named address spaces (generic vs %s) "
			   "for %q+D",
			   c_addr_space_name (old_addr), newdecl);
		  లేకపోతే ఒకవేళ (ADDR_SPACE_GENERIC_P (old_addr))
		    error ("conflicting named address spaces (%s vs generic) "
			   "for %q+D",
			   c_addr_space_name (new_addr), newdecl);
		  లేకపోతే
		    error ("conflicting named address spaces (%s vs %s) "
			   "for %q+D",
			   c_addr_space_name (new_addr),
			   c_addr_space_name (old_addr),
			   newdecl);
		}

	      ఒకవేళ (CLEAR_QUAL_ADDR_SPACE (new_quals)
		  != CLEAR_QUAL_ADDR_SPACE (old_quals))
		error ("conflicting type qualifiers for %q+D", newdecl);
	    }
	  లేకపోతే
	    {
	      ఒకవేళ (వృక్షం_సంకేతం (olddecl) == FUNCTION_DECL)
		{
		  వృక్షం attrs = TYPE_లక్షణాలు (వృక్షం_TYPE (olddecl));
		  ఒకవేళ (attrs && !TYPE_లక్షణాలు (వృక్షం_TYPE (newdecl)))
		    {
		      /* Similar to the C++ front-end, for FUNCTION_DECL,
			 if OLDDECL has attributes and NEWDECL doesn't,
			 try the type with OLDDECL attributes.  */
		      వృక్షం rettype = వృక్షం_TYPE (newtype);
		      వృక్షం tryargs = TYPE_ARG_TYPES (newtype);
		      వృక్షం trytype = c_build_function_type (rettype,
							    tryargs);
		      trytype = c_build_type_attribute_variant (trytype,
								attrs);
		      ఒకవేళ (comptypes (oldtype, trytype))
			{
			  *newtypep = newtype = trytype;
			  comptypes_ఫలితం = నిజం;
			}
		    }
		}

	      ఒకవేళ (!comptypes_ఫలితం)
		error ("conflicting types for %q+D; have %qT", newdecl,
		       newtype);
	    }
	  ఒకవేళ (!comptypes_ఫలితం)
	    {
	      diagnose_arglist_conflict (newdecl, olddecl, newtype,
					 oldtype);
	      locate_old_decl (olddecl);
	      తిరిగి అబద్ధం;
	    }
	}
    }
  /* Warn about enum/integer type mismatches.  They are compatible types
     (C23 6.7.2.2/5), but may pose portability problems.  */
  లేకపోతే ఒకవేళ (enum_and_int_p
	   && వృక్షం_సంకేతం (newdecl) != TYPE_DECL
	   /* Don't warn about acc_on_device built-in redeclaration,
	      the built-in is declared with int rather than enum because
	      the enum isn't intrinsic.  */
	   && !(వృక్షం_సంకేతం (olddecl) == FUNCTION_DECL
		&& fndecl_built_లోపల_p (olddecl, BUILT_లోపల_ACC_ON_DEVICE)
		&& !C_DECL_DECLARED_BUILTIN (olddecl)))
    warned = warning_at (DECL_ఆధారం_LOCATION (newdecl),
			 OPT_Wenum_int_mismatch,
			 "conflicting types for %q+D due to enum/integer "
			 "mismatch; have %qT", newdecl, newtype);

  /* Redeclaration of a type is a constraint violation (6.7.2.3p1),
     but silently ignore the redeclaration if either is in a system
     header.  (Conflicting redeclarations were handled above.)  This
     is allowed for C11 if the types are the same, not just
     compatible.  */
  ఒకవేళ (వృక్షం_సంకేతం (newdecl) == TYPE_DECL)
    {
      ఒకవేళ (!comptypes_same_p (oldtype, newtype))
	{
	  error ("redefinition of typedef %q+D with different type", newdecl);
	  locate_old_decl (olddecl);
	  తిరిగి అబద్ధం;
	}

      ఒకవేళ (DECL_లోపల_SYSTEM_శీర్షిక (newdecl)
	  || DECL_లోపల_SYSTEM_శీర్షిక (olddecl)
	  || warning_suppressed_p (newdecl, OPT_Wpedantic)
	  || warning_suppressed_p (olddecl, OPT_Wpedantic))
	తిరిగి నిజం;  /* Allow OLDDECL to continue in use.  */

      ఒకవేళ (c_type_variably_modified_p (newtype))
	{
	  error ("redefinition of typedef %q+D with variably modified type",
		 newdecl);
	  locate_old_decl (olddecl);
	}
      లేకపోతే ఒకవేళ (pedwarn_c99 (ఆదానం_location, OPT_Wpedantic,
			    "redefinition of typedef %q+D", newdecl))
	locate_old_decl (olddecl);

      తిరిగి నిజం;
    }

  /* Function declarations can either be 'static' or 'extern' (no
     qualifier is equivalent to 'extern' - C99 6.2.2p5) and therefore
     can never conflict with each other on account of linkage
     (6.2.2p4).  Multiple definitions are not allowed (6.9p3,5) but
     gnu89 mode permits two definitions if one is 'extern inline' and
     one is not.  The non- extern-inline definition supersedes the
     extern-inline definition.  */

  లేకపోతే ఒకవేళ (వృక్షం_సంకేతం (newdecl) == FUNCTION_DECL)
    {
      /* If you declare a built-in function name as static, or
	 define the built-in with an old-style definition (so we
	 can't validate the argument list) the built-in definition is
	 overridden, but optionally warn this was a bad choice of name.  */
      ఒకవేళ (fndecl_built_లోపల_p (olddecl)
	  && !C_DECL_DECLARED_BUILTIN (olddecl))
	{
	  ఒకవేళ (!వృక్షం_ప్రజా (newdecl)
	      || (DECL_INITIAL (newdecl)
		  && !prototype_p (వృక్షం_TYPE (newdecl))))
	    {
	      warning_at (DECL_ఆధారం_LOCATION (newdecl),
			  OPT_Wshadow, "declaration of %qD shadows "
			  "a built-in function", newdecl);
	      /* Discard the old built-in function.  */
	      తిరిగి అబద్ధం;
	    }

	  ఒకవేళ (!prototype_p (వృక్షం_TYPE (newdecl)))
	    {
	      /* Set for built-ins that take no arguments.  */
	      తార్కిక func_void_వాదనలు = అబద్ధం;
	      ఒకవేళ (వృక్షం at = TYPE_ARG_TYPES (oldtype))
		func_void_వాదనలు = VOID_TYPE_P (వృక్షం_విలువ (at));

	      ఒకవేళ (extra_warnings && !func_void_వాదనలు)
		warning_at (DECL_ఆధారం_LOCATION (newdecl),
			    OPT_Wbuiltin_declaration_mismatch,
			    "declaration of built-in function %qD without "
			    "a prototype; expected %qT",
			    newdecl, వృక్షం_TYPE (olddecl));
	    }
	}

      ఒకవేళ (DECL_INITIAL (newdecl))
	{
	  ఒకవేళ (DECL_INITIAL (olddecl))
	    {
	      /* If the new declaration isn't overriding an extern inline
		 reject the new decl. In c99, no overriding is allowed
		 in the same translation unit.  */
	      ఒకవేళ (!DECL_EXTERN_INLINE (olddecl)
		  || DECL_EXTERN_INLINE (newdecl)
		  || (!flag_gnu89_inline
		      && (!DECL_DECLARED_INLINE_P (olddecl)
			  || !lookup_attribute ("gnu_inline",
						DECL_లక్షణాలు (olddecl)))
		      && (!DECL_DECLARED_INLINE_P (newdecl)
			  || !lookup_attribute ("gnu_inline",
						DECL_లక్షణాలు (newdecl)))))
		{
		  auto_diagnostic_సమూహం d;
		  error ("redefinition of %q+D", newdecl);
		  locate_old_decl (olddecl);
		  తిరిగి అబద్ధం;
		}
	    }
	}
      /* If we have a prototype after an old-style function definition,
	 the argument types must be checked specially.  */
      లేకపోతే ఒకవేళ (DECL_INITIAL (olddecl)
	       && !prototype_p (oldtype) && prototype_p (newtype)
	       && TYPE_ACTUAL_ARG_TYPES (oldtype))
	{
	  auto_diagnostic_సమూహం d;
	  ఒకవేళ (!validate_proto_after_old_defn (newdecl, newtype, oldtype))
	    {
	      locate_old_decl (olddecl);
	      తిరిగి అబద్ధం;
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
      ఒకవేళ (వృక్షం_ప్రజా (olddecl) && !వృక్షం_ప్రజా (newdecl))
	{
	  /* Two exceptions to the rule.  If olddecl is an extern
	     inline, or a predeclared function that isn't actually
	     built in, newdecl silently overrides olddecl.  The latter
	     occur only in Objective C; see also above.  (FIXME: Make
	     Objective C use normal builtins.)  */
	  ఒకవేళ (!DECL_IS_UNDECLARED_BUILTIN (olddecl)
	      && !DECL_EXTERN_INLINE (olddecl))
	    {
	      auto_diagnostic_సమూహం d;
	      error ("static declaration of %q+D follows "
		     "non-static declaration", newdecl);
	      locate_old_decl (olddecl);
	    }
	  తిరిగి అబద్ధం;
	}
      లేకపోతే ఒకవేళ (వృక్షం_ప్రజా (newdecl) && !వృక్షం_ప్రజా (olddecl))
	{
	  ఒకవేళ (DECL_CONTEXT (olddecl))
	    {
	      auto_diagnostic_సమూహం d;
	      error ("non-static declaration of %q+D follows "
		     "static declaration", newdecl);
	      locate_old_decl (olddecl);
	      తిరిగి అబద్ధం;
	    }
	  లేకపోతే ఒకవేళ (warn_traditional)
	    {
	      warned |= warning (OPT_Wtraditional,
				 "non-static declaration of %q+D "
				 "follows static declaration", newdecl);
	    }
	}

      /* Make sure gnu_inline attribute is either not present, or
	 present on all inline decls.  */
      ఒకవేళ (DECL_DECLARED_INLINE_P (olddecl)
	  && DECL_DECLARED_INLINE_P (newdecl))
	{
	  తార్కిక newa = lookup_attribute ("gnu_inline",
					DECL_లక్షణాలు (newdecl)) != ఖాళీ;
	  తార్కిక olda = lookup_attribute ("gnu_inline",
					DECL_లక్షణాలు (olddecl)) != ఖాళీ;
	  ఒకవేళ (newa != olda)
	    {
	      auto_diagnostic_సమూహం d;
	      error_at (ఆదానం_location, "%<gnu_inline%> attribute present on %q+D",
			newa ? newdecl : olddecl);
	      error_at (DECL_ఆధారం_LOCATION (newa ? olddecl : newdecl),
			"but not here");
	    }
	}
      /* Check if these are unmergeable overlapping FMV declarations.  */
      ఒకవేళ (!లక్ష్యం_HAS_FMV_లక్ష్యం_ATTRIBUTE
	  && diagnose_versioned_decls (olddecl, newdecl))
	తిరిగి అబద్ధం;
    }
  లేకపోతే ఒకవేళ (VAR_P (newdecl))
    {
      /* Only variables can be thread-local, and all declarations must
	 agree on this property.  */
      ఒకవేళ (C_DECL_THREADPRIVATE_P (olddecl) && !DECL_THREAD_LOCAL_P (newdecl))
	{
	  /* Nothing to check.  Since OLDDECL is marked threadprivate
	     and NEWDECL does not have a thread-local attribute, we
	     will merge the threadprivate attribute into NEWDECL.  */
	  ;
	}
      లేకపోతే ఒకవేళ (DECL_THREAD_LOCAL_P (newdecl) != DECL_THREAD_LOCAL_P (olddecl))
	{
	  auto_diagnostic_సమూహం d;
	  ఒకవేళ (DECL_THREAD_LOCAL_P (newdecl))
	    error ("thread-local declaration of %q+D follows "
		   "non-thread-local declaration", newdecl);
	  లేకపోతే
	    error ("non-thread-local declaration of %q+D follows "
		   "thread-local declaration", newdecl);

	  locate_old_decl (olddecl);
	  తిరిగి అబద్ధం;
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
      ఒకవేళ ((DECL_INITIAL (newdecl) && DECL_INITIAL (olddecl))
	  || (flag_isoc23
	      && DECL_THREAD_LOCAL_P (newdecl)
	      && !DECL_EXTERNAL (newdecl)
	      && !DECL_EXTERNAL (olddecl)))
	{
	  auto_diagnostic_సమూహం d;
	  error ("redefinition of %q+D", newdecl);
	  locate_old_decl (olddecl);
	  తిరిగి అబద్ధం;
	}

      /* Objects declared at file scope: if the first declaration had
	 external linkage (even if it was an external reference) the
	 second must have external linkage as well, or the behavior is
	 undefined.  If the first declaration had internal linkage, then
	 the second must too, or else be an external reference (in which
	 case the composite declaration still has internal linkage).
	 As for function declarations, we warn about the static-then-
	 extern case only for -Wtraditional.  See generally 6.2.2p3-5,7.  */
      ఒకవేళ (DECL_FILE_SCOPE_P (newdecl)
	  && వృక్షం_ప్రజా (newdecl) != వృక్షం_ప్రజా (olddecl))
	{
	  ఒకవేళ (DECL_EXTERNAL (newdecl))
	    {
	      ఒకవేళ (!DECL_FILE_SCOPE_P (olddecl))
		{
		  auto_diagnostic_సమూహం d;
		  error ("extern declaration of %q+D follows "
			 "declaration with no linkage", newdecl);
		  locate_old_decl (olddecl);
		  తిరిగి అబద్ధం;
		}
	      లేకపోతే ఒకవేళ (warn_traditional)
		{
		  warned |= warning (OPT_Wtraditional,
				     "non-static declaration of %q+D "
				     "follows static declaration", newdecl);
		}
	    }
	  లేకపోతే
	    {
	      auto_diagnostic_సమూహం d;
	      ఒకవేళ (వృక్షం_ప్రజా (newdecl))
		error ("non-static declaration of %q+D follows "
		       "static declaration", newdecl);
	      లేకపోతే
		error ("static declaration of %q+D follows "
		       "non-static declaration", newdecl);

	      locate_old_decl (olddecl);
	      తిరిగి అబద్ధం;
	    }
	}
      /* Two objects with the same name declared at the same block
	 scope must both be external references (6.7p3).  */
      లేకపోతే ఒకవేళ (!DECL_FILE_SCOPE_P (newdecl))
	{
	  ఒకవేళ (DECL_EXTERNAL (newdecl))
	    {
	      /* Extern with initializer at block scope, which will
		 already have received an error.  */
	    }
	  లేకపోతే ఒకవేళ (DECL_EXTERNAL (olddecl))
	    {
	      auto_diagnostic_సమూహం d;
	      error ("declaration of %q+D with no linkage follows "
		     "extern declaration", newdecl);
	      locate_old_decl (olddecl);
	    }
	  లేకపోతే
	    {
	      auto_diagnostic_సమూహం d;
	      error ("redeclaration of %q+D with no linkage", newdecl);
	      locate_old_decl (olddecl);
	    }

	  తిరిగి అబద్ధం;
	}

      /* C++ does not permit a decl to appear multiple times at file
	 scope.  */
      ఒకవేళ (warn_cxx_compat
	  && DECL_FILE_SCOPE_P (newdecl)
	  && !DECL_EXTERNAL (newdecl)
	  && !DECL_EXTERNAL (olddecl))
	warned |= warning_at (DECL_ఆధారం_LOCATION (newdecl),
			      OPT_Wc___compat,
			      "duplicate declaration of %qD is "
			      "invalid in C++", newdecl);
    }

  /* warnings */
  /* All decls must agree on a visibility.  */
  ఒకవేళ (సంకేతం_కలిగియుంది_STRUCT (వృక్షం_సంకేతం (newdecl), TS_DECL_WITH_VIS)
      && DECL_VISIBILITY_SPECIFIED (newdecl) && DECL_VISIBILITY_SPECIFIED (olddecl)
      && DECL_VISIBILITY (newdecl) != DECL_VISIBILITY (olddecl))
    {
      warned |= warning (0, "redeclaration of %q+D with different visibility "
			 "(old visibility preserved)", newdecl);
    }

  ఒకవేళ (వృక్షం_సంకేతం (newdecl) == FUNCTION_DECL)
    warned |= diagnose_mismatched_లక్షణాలు (olddecl, newdecl);
  లేకపోతే /* PARM_DECL, VAR_DECL */
    {
      /* Redeclaration of a parameter is a constraint violation (this is
	 not explicitly stated, but follows from C99 6.7p3 [no more than
	 one declaration of the same identifier with no linkage in the
	 same scope, except type tags] and 6.2.2p6 [parameters have no
	 linkage]).  We must check for a forward parameter declaration,
	 indicated by TREE_ASM_WRITTEN on the old declaration - this is
	 an extension, the mandatory diagnostic for which is handled by
	 mark_forward_parm_decls.  */

      ఒకవేళ (వృక్షం_సంకేతం (newdecl) == PARM_DECL
	  && (!వృక్షం_ASM_WRITTEN (olddecl) || వృక్షం_ASM_WRITTEN (newdecl)))
	{
	  auto_diagnostic_సమూహం d;
	  error ("redefinition of parameter %q+D", newdecl);
	  locate_old_decl (olddecl);
	  తిరిగి అబద్ధం;
	}
    }

  /* Optional warning for completely redundant decls.  */
  ఒకవేళ (!warned && !pedwarned
      && warn_redundant_decls
      /* Don't warn about a function declaration followed by a
	 definition.  */
      && !(వృక్షం_సంకేతం (newdecl) == FUNCTION_DECL
	   && DECL_INITIAL (newdecl) && !DECL_INITIAL (olddecl))
      /* Don't warn about redundant redeclarations of builtins.  */
      && !(వృక్షం_సంకేతం (newdecl) == FUNCTION_DECL
	   && !fndecl_built_లోపల_p (newdecl)
	   && fndecl_built_లోపల_p (olddecl)
	   && !C_DECL_DECLARED_BUILTIN (olddecl))
      /* Don't warn about an extern followed by a definition.  */
      && !(DECL_EXTERNAL (olddecl) && !DECL_EXTERNAL (newdecl))
      /* Don't warn about forward parameter decls.  */
      && !(వృక్షం_సంకేతం (newdecl) == PARM_DECL
	   && వృక్షం_ASM_WRITTEN (olddecl) && !వృక్షం_ASM_WRITTEN (newdecl))
      /* Don't warn about a variable definition following a declaration.  */
      && !(VAR_P (newdecl)
	   && DECL_INITIAL (newdecl) && !DECL_INITIAL (olddecl)))
    {
      warned = warning (OPT_Wredundant_decls, "redundant redeclaration of %q+D",
			newdecl);
    }

  /* Report location of previous decl/defn.  */
  ఒకవేళ (warned || pedwarned)
    locate_old_decl (olddecl);

#నిర్వచనం_రద్దు DECL_EXTERN_INLINE

  తిరిగి retval;
}

/* Subroutine of duplicate_decls.  NEWDECL has been found to be
   consistent with OLDDECL, but carries new information.  Merge the
   new information into OLDDECL.  This function issues no
   diagnostics.  */

స్థిర శూన్య
విలీనం_decls (వృక్షం newdecl, వృక్షం olddecl, వృక్షం newtype, వృక్షం oldtype)
{
  తార్కిక new_is_definition = (వృక్షం_సంకేతం (newdecl) == FUNCTION_DECL
			    && DECL_INITIAL (newdecl) != NULL_వృక్షం);
  తార్కిక new_is_prototype = (వృక్షం_సంకేతం (newdecl) == FUNCTION_DECL
			   && prototype_p (వృక్షం_TYPE (newdecl)));
  తార్కిక old_is_prototype = (వృక్షం_సంకేతం (olddecl) == FUNCTION_DECL
			   && prototype_p (వృక్షం_TYPE (olddecl)));

  /* For real parm decl following a forward decl, rechain the old decl
     in its new location and clear TREE_ASM_WRITTEN (it's not a
     forward decl anymore).  */
  ఒకవేళ (వృక్షం_సంకేతం (newdecl) == PARM_DECL
      && వృక్షం_ASM_WRITTEN (olddecl) && !వృక్షం_ASM_WRITTEN (newdecl))
    {
      నిర్మాణం c_binding *b, **ఇక్కడ;

      కొరకు (ఇక్కడ = &current_scope->bindings; *ఇక్కడ; ఇక్కడ = &(*ఇక్కడ)->prev)
	ఒకవేళ ((*ఇక్కడ)->decl == olddecl)
	  వెళ్ళు దొరికింది;
      gcc_unreachable ();

    దొరికింది:
      b = *ఇక్కడ;
      *ఇక్కడ = b->prev;
      b->prev = current_scope->bindings;
      current_scope->bindings = b;

      వృక్షం_ASM_WRITTEN (olddecl) = 0;
    }

  DECL_లక్షణాలు (newdecl)
    = targetm.విలీనం_decl_లక్షణాలు (olddecl, newdecl);

  /* For typedefs use the old type, as the new type's DECL_NAME points
     at newdecl, which will be ggc_freed.  */
  ఒకవేళ (వృక్షం_సంకేతం (newdecl) == TYPE_DECL)
    {
      /* But NEWTYPE might have an attribute, honor that.  */
      వృక్షం tem = newtype;
      newtype = oldtype;

      ఒకవేళ (TYPE_USER_ALIGN (tem))
	{
	  ఒకవేళ (TYPE_ALIGN (tem) > TYPE_ALIGN (newtype))
	    సమితి_TYPE_ALIGN (newtype, TYPE_ALIGN (tem));
	  TYPE_USER_ALIGN (newtype) = నిజం;
	}

      /* And remove the new type from the variants list.  */
      ఒకవేళ (TYPE_NAME (వృక్షం_TYPE (newdecl)) == newdecl)
	{
	  వృక్షం remove = వృక్షం_TYPE (newdecl);
	  ఒకవేళ (TYPE_MAIN_VARIANT (remove) == remove)
	    {
	      gcc_assert (TYPE_తదుపరి_VARIANT (remove) == NULL_వృక్షం);
	      /* If remove is the main variant, no need to remove that
		 from the list.  One of the DECL_ORIGINAL_TYPE
		 variants, e.g. created for aligned attribute, might still
		 refer to the newdecl TYPE_DECL though, so remove that one
		 in that case.  */
	      ఒకవేళ (DECL_ORIGINAL_TYPE (newdecl)
		  && DECL_ORIGINAL_TYPE (newdecl) != remove)
		కొరకు (వృక్షం t = TYPE_MAIN_VARIANT (DECL_ORIGINAL_TYPE (newdecl));
		     t; t = TYPE_MAIN_VARIANT (t))
		  ఒకవేళ (TYPE_NAME (TYPE_తదుపరి_VARIANT (t)) == newdecl)
		    {
		      TYPE_తదుపరి_VARIANT (t)
			= TYPE_తదుపరి_VARIANT (TYPE_తదుపరి_VARIANT (t));
		      ఆపు;
		    }
	    }
	  లేకపోతే
	    కొరకు (వృక్షం t = TYPE_MAIN_VARIANT (remove); ;
		 t = TYPE_తదుపరి_VARIANT (t))
	      ఒకవేళ (TYPE_తదుపరి_VARIANT (t) == remove)
		{
		  TYPE_తదుపరి_VARIANT (t) = TYPE_తదుపరి_VARIANT (remove);
		  ఆపు;
		}
	}

      /* Make sure we refer to the same type as the olddecl.  */
      DECL_ORIGINAL_TYPE (newdecl) = DECL_ORIGINAL_TYPE (olddecl);
    }

  /* Merge the data types specified in the two decls.  */
  వృక్షం_TYPE (newdecl)
    = వృక్షం_TYPE (olddecl)
    = సంయుక్త_type (newtype, oldtype);

  /* Lay the type out, unless already done.  */
  ఒకవేళ (!comptypes (oldtype, వృక్షం_TYPE (newdecl)))
    {
      ఒకవేళ (వృక్షం_TYPE (newdecl) != error_mark_కణుపు)
	layout_type (వృక్షం_TYPE (newdecl));
      ఒకవేళ (వృక్షం_సంకేతం (newdecl) != FUNCTION_DECL
	  && వృక్షం_సంకేతం (newdecl) != TYPE_DECL
	  && వృక్షం_సంకేతం (newdecl) != CONST_DECL)
	layout_decl (newdecl, 0);
    }
  లేకపోతే
    {
      /* Since the type is OLDDECL's, make OLDDECL's size go with.  */
      DECL_కొలత (newdecl) = DECL_కొలత (olddecl);
      DECL_కొలత_UNIT (newdecl) = DECL_కొలత_UNIT (olddecl);
      సమితి_DECL_బహుళకం (newdecl, DECL_బహుళకం (olddecl));
      ఒకవేళ (DECL_ALIGN (olddecl) > DECL_ALIGN (newdecl))
	{
	  సమితి_DECL_ALIGN (newdecl, DECL_ALIGN (olddecl));
	  DECL_USER_ALIGN (newdecl) |= DECL_USER_ALIGN (olddecl);
	}
      లేకపోతే ఒకవేళ (DECL_ALIGN (olddecl) == DECL_ALIGN (newdecl)
	       && DECL_USER_ALIGN (olddecl) != DECL_USER_ALIGN (newdecl))
	DECL_USER_ALIGN (newdecl) = 1;
      ఒకవేళ (DECL_WARN_IF_NOT_ALIGN (olddecl)
	  > DECL_WARN_IF_NOT_ALIGN (newdecl))
	సమితి_DECL_WARN_IF_NOT_ALIGN (newdecl,
				    DECL_WARN_IF_NOT_ALIGN (olddecl));
    }

  /* Keep the old rtl since we can safely use it.  */
  ఒకవేళ (HAS_RTL_P (olddecl))
    COPY_DECL_RTL (olddecl, newdecl);

  /* Merge the type qualifiers.  */
  ఒకవేళ (వృక్షం_READONLY (newdecl))
    వృక్షం_READONLY (olddecl) = 1;

  ఒకవేళ (వృక్షం_THIS_VOLATILE (newdecl))
    వృక్షం_THIS_VOLATILE (olddecl) = 1;

  /* Merge deprecatedness.  */
  ఒకవేళ (వృక్షం_DEPRECATED (newdecl))
    వృక్షం_DEPRECATED (olddecl) = 1;

  /* Merge unavailability.  */
  ఒకవేళ (వృక్షం_UNAVAILABLE (newdecl))
    వృక్షం_UNAVAILABLE (olddecl) = 1;

  /* If a decl is in a system header and the other isn't, keep the one on the
     system header. Otherwise, keep source location of definition rather than
     declaration and of prototype rather than non-prototype unless that
     prototype is built-in.  */
  ఒకవేళ (HAS_DECL_ASSEMBLER_NAME_P (olddecl)
      && DECL_లోపల_SYSTEM_శీర్షిక (olddecl)
      && !DECL_లోపల_SYSTEM_శీర్షిక (newdecl) )
    DECL_ఆధారం_LOCATION (newdecl) = DECL_ఆధారం_LOCATION (olddecl);
  లేకపోతే ఒకవేళ (HAS_DECL_ASSEMBLER_NAME_P (olddecl)
	   && DECL_లోపల_SYSTEM_శీర్షిక (newdecl)
	   && !DECL_లోపల_SYSTEM_శీర్షిక (olddecl))
    DECL_ఆధారం_LOCATION (olddecl) = DECL_ఆధారం_LOCATION (newdecl);
  లేకపోతే ఒకవేళ ((DECL_INITIAL (newdecl) == NULL_వృక్షం
	    && DECL_INITIAL (olddecl) != NULL_వృక్షం)
	   || (old_is_prototype && !new_is_prototype
	       && !C_DECL_BUILTIN_PROTOTYPE (olddecl)))
    DECL_ఆధారం_LOCATION (newdecl) = DECL_ఆధారం_LOCATION (olddecl);

  /* Merge the initialization information.  */
   ఒకవేళ (DECL_INITIAL (newdecl) == NULL_వృక్షం)
    DECL_INITIAL (newdecl) = DECL_INITIAL (olddecl);

  /* Merge 'constexpr' information.  */
  ఒకవేళ (VAR_P (olddecl) && VAR_P (newdecl))
    {
      ఒకవేళ (C_DECL_DECLARED_CONSTEXPR (olddecl))
	C_DECL_DECLARED_CONSTEXPR (newdecl) = 1;
      లేకపోతే ఒకవేళ (C_DECL_DECLARED_CONSTEXPR (newdecl))
	C_DECL_DECLARED_CONSTEXPR (olddecl) = 1;
    }

  /* Merge the threadprivate attribute.  */
  ఒకవేళ (VAR_P (olddecl) && C_DECL_THREADPRIVATE_P (olddecl))
    C_DECL_THREADPRIVATE_P (newdecl) = 1;

  ఒకవేళ (HAS_DECL_ASSEMBLER_NAME_P (olddecl))
    {
      /* Copy the assembler name.
	 Currently, it can only be defined in the prototype.  */
      COPY_DECL_ASSEMBLER_NAME (olddecl, newdecl);

      /* Use visibility of whichever declaration had it specified */
      ఒకవేళ (DECL_VISIBILITY_SPECIFIED (olddecl))
	{
	  DECL_VISIBILITY (newdecl) = DECL_VISIBILITY (olddecl);
	  DECL_VISIBILITY_SPECIFIED (newdecl) = 1;
	}

      ఒకవేళ (వృక్షం_సంకేతం (newdecl) == FUNCTION_DECL)
	{
	  DECL_STATIC_CONSTRUCTOR(newdecl) |= DECL_STATIC_CONSTRUCTOR(olddecl);
	  DECL_STATIC_DESTRUCTOR (newdecl) |= DECL_STATIC_DESTRUCTOR (olddecl);
	  DECL_NO_హద్దు_దొంతర (newdecl) |= DECL_NO_హద్దు_దొంతర (olddecl);
	  DECL_NO_INSTRUMENT_FUNCTION_నమోదు_EXIT (newdecl)
	    |= DECL_NO_INSTRUMENT_FUNCTION_నమోదు_EXIT (olddecl);
	  వృక్షం_THIS_VOLATILE (newdecl) |= వృక్షం_THIS_VOLATILE (olddecl);
	  DECL_IS_MALLOC (newdecl) |= DECL_IS_MALLOC (olddecl);
	  ఒకవేళ (DECL_IS_OPERATOR_NEW_P (olddecl))
	    DECL_సమితి_IS_OPERATOR_NEW (newdecl, నిజం);
	  ఒకవేళ (DECL_IS_OPERATOR_DELETE_P (olddecl))
	    DECL_సమితి_IS_OPERATOR_DELETE (newdecl, నిజం);
	  వృక్షం_READONLY (newdecl) |= వృక్షం_READONLY (olddecl);
	  DECL_శుద్ధ_P (newdecl) |= DECL_శుద్ధ_P (olddecl);
	  DECL_IS_NOVOPS (newdecl) |= DECL_IS_NOVOPS (olddecl);
	}

      /* Merge the storage class information.  */
      విలీనం_weak (newdecl, olddecl);

      /* For functions, static overrides non-static.  */
      ఒకవేళ (వృక్షం_సంకేతం (newdecl) == FUNCTION_DECL)
	{
	  వృక్షం_ప్రజా (newdecl) &= వృక్షం_ప్రజా (olddecl);
	  /* This is since we don't automatically
	     copy the attributes of NEWDECL into OLDDECL.  */
	  వృక్షం_ప్రజా (olddecl) = వృక్షం_ప్రజా (newdecl);
	  /* If this clears `static', clear it in the identifier too.  */
	  ఒకవేళ (!వృక్షం_ప్రజా (olddecl))
	    వృక్షం_ప్రజా (DECL_NAME (olddecl)) = 0;
	}
    }

  /* In c99, 'extern' declaration before (or after) 'inline' means this
     function is not DECL_EXTERNAL, unless 'gnu_inline' attribute
     is present.  */
  ఒకవేళ (వృక్షం_సంకేతం (newdecl) == FUNCTION_DECL
      && !flag_gnu89_inline
      && (DECL_DECLARED_INLINE_P (newdecl)
	  || DECL_DECLARED_INLINE_P (olddecl))
      && (!DECL_DECLARED_INLINE_P (newdecl)
	  || !DECL_DECLARED_INLINE_P (olddecl)
	  || !DECL_EXTERNAL (olddecl))
      && DECL_EXTERNAL (newdecl)
      && !lookup_attribute ("gnu_inline", DECL_లక్షణాలు (newdecl))
      && !current_function_decl)
    DECL_EXTERNAL (newdecl) = 0;

  /* An inline definition following a static declaration is not
     DECL_EXTERNAL.  */
  ఒకవేళ (new_is_definition
      && (DECL_DECLARED_INLINE_P (newdecl)
	  || DECL_DECLARED_INLINE_P (olddecl))
      && !వృక్షం_ప్రజా (olddecl))
    DECL_EXTERNAL (newdecl) = 0;

  ఒకవేళ (DECL_EXTERNAL (newdecl))
    {
      వృక్షం_STATIC (newdecl) = వృక్షం_STATIC (olddecl);
      DECL_EXTERNAL (newdecl) = DECL_EXTERNAL (olddecl);

      /* An extern decl does not override previous storage class.  */
      వృక్షం_ప్రజా (newdecl) = వృక్షం_ప్రజా (olddecl);
      ఒకవేళ (!DECL_EXTERNAL (newdecl))
	{
	  DECL_CONTEXT (newdecl) = DECL_CONTEXT (olddecl);
	  DECL_COMMON (newdecl) = DECL_COMMON (olddecl);
	}
    }
  లేకపోతే
    {
      వృక్షం_STATIC (olddecl) = వృక్షం_STATIC (newdecl);
      వృక్షం_ప్రజా (olddecl) = వృక్షం_ప్రజా (newdecl);
    }

  ఒకవేళ (వృక్షం_సంకేతం (newdecl) == FUNCTION_DECL)
    {
      ఒకవేళ (DECL_FUNCTION_VERSIONED (olddecl)
	  || DECL_FUNCTION_VERSIONED (newdecl))
	{
	  maybe_mark_function_versioned (olddecl);
	  maybe_mark_function_versioned (newdecl);
	}
      /* If we're redefining a function previously defined as extern
	 inline, make sure we emit debug info for the inline before we
	 throw it away, in case it was inlined into a function that
	 hasn't been written out yet.  */
      ఒకవేళ (new_is_definition && DECL_INITIAL (olddecl))
	/* The new defn must not be inline.  */
	DECL_UNINLINABLE (newdecl) = 1;
      లేకపోతే
	{
	  /* If either decl says `inline', this fn is inline, unless
	     its definition was passed already.  */
	  ఒకవేళ (DECL_DECLARED_INLINE_P (newdecl)
	      || DECL_DECLARED_INLINE_P (olddecl))
	    DECL_DECLARED_INLINE_P (newdecl) = 1;

	  DECL_UNINLINABLE (newdecl) = DECL_UNINLINABLE (olddecl)
	    = (DECL_UNINLINABLE (newdecl) || DECL_UNINLINABLE (olddecl));

	  DECL_DISREGARD_INLINE_LIMITS (newdecl)
	    = DECL_DISREGARD_INLINE_LIMITS (olddecl)
	    = (DECL_DISREGARD_INLINE_LIMITS (newdecl)
	       || DECL_DISREGARD_INLINE_LIMITS (olddecl));
	}

      ఒకవేళ (fndecl_built_లోపల_p (olddecl))
	{
	  /* If redeclaring a builtin function, it stays built in.
	     But it gets tagged as having been declared.  */
	  copy_decl_built_లోపల_function (newdecl, olddecl);
	  C_DECL_DECLARED_BUILTIN (newdecl) = 1;
	  ఒకవేళ (new_is_prototype)
	    {
	      C_DECL_BUILTIN_PROTOTYPE (newdecl) = 0;
	      ఒకవేళ (DECL_BUILT_లోపల_CLASS (newdecl) == BUILT_లోపల_సాధారణ)
		{
		  గణన built_లోపల_function fncode = DECL_FUNCTION_సంకేతం (newdecl);
		  ఎంపిక (fncode)
		    {
		      /* If a compatible prototype of these builtin functions
			 is seen, assume the runtime implements it with the
			 expected semantics.  */
		    స్థితి BUILT_లోపల_STPCPY:
		      ఒకవేళ (builtin_decl_explicit_p (fncode))
			సమితి_builtin_decl_implicit_p (fncode, నిజం);
		      ఆపు;
		    అప్రమేయ:
		      ఒకవేళ (builtin_decl_explicit_p (fncode))
			సమితి_builtin_decl_declared_p (fncode, నిజం);
		      ఆపు;
		    }

		  copy_లక్షణాలు_గమ్యం_builtin (newdecl);
		}
	    }
	  లేకపోతే
	    C_DECL_BUILTIN_PROTOTYPE (newdecl)
	      = C_DECL_BUILTIN_PROTOTYPE (olddecl);
	}

      /* Preserve function specific target and optimization options */
      ఒకవేళ (DECL_FUNCTION_SPECIFIC_లక్ష్యం (olddecl)
	  && !DECL_FUNCTION_SPECIFIC_లక్ష్యం (newdecl))
	DECL_FUNCTION_SPECIFIC_లక్ష్యం (newdecl)
	  = DECL_FUNCTION_SPECIFIC_లక్ష్యం (olddecl);

      ఒకవేళ (DECL_FUNCTION_SPECIFIC_OPTIMIZATION (olddecl)
	  && !DECL_FUNCTION_SPECIFIC_OPTIMIZATION (newdecl))
	DECL_FUNCTION_SPECIFIC_OPTIMIZATION (newdecl)
	  = DECL_FUNCTION_SPECIFIC_OPTIMIZATION (olddecl);

      /* Also preserve various other info from the definition.  */
      ఒకవేళ (!new_is_definition)
	{
	  వృక్షం t;
	  DECL_ఫలితం (newdecl) = DECL_ఫలితం (olddecl);
	  DECL_INITIAL (newdecl) = DECL_INITIAL (olddecl);
	  DECL_STRUCT_FUNCTION (newdecl) = DECL_STRUCT_FUNCTION (olddecl);
	  DECL_SAVED_వృక్షం (newdecl) = DECL_SAVED_వృక్షం (olddecl);
	  DECL_ARGUMENTS (newdecl) = copy_list (DECL_ARGUMENTS (olddecl));
	  కొరకు (t = DECL_ARGUMENTS (newdecl); t ; t = DECL_CHAIN (t))
	    DECL_CONTEXT (t) = newdecl;

	  /* See if we've got a function to instantiate from.  */
	  ఒకవేళ (DECL_SAVED_వృక్షం (olddecl))
	    DECL_ABSTRACT_ORIGIN (newdecl)
	      = DECL_ABSTRACT_ORIGIN (olddecl);
	}
    }

  /* Merge the USED information.  */
  ఒకవేళ (వృక్షం_వాడిన (olddecl))
    వృక్షం_వాడిన (newdecl) = 1;
  లేకపోతే ఒకవేళ (వృక్షం_వాడిన (newdecl))
    వృక్షం_వాడిన (olddecl) = 1;
  ఒకవేళ (VAR_P (olddecl) || వృక్షం_సంకేతం (olddecl) == PARM_DECL)
    DECL_READ_P (newdecl) |= DECL_READ_P (olddecl);
  ఒకవేళ (DECL_PRESERVE_P (olddecl))
    DECL_PRESERVE_P (newdecl) = 1;
  లేకపోతే ఒకవేళ (DECL_PRESERVE_P (newdecl))
    DECL_PRESERVE_P (olddecl) = 1;

  /* Merge DECL_COMMON */
  ఒకవేళ (VAR_P (olddecl) && VAR_P (newdecl)
      && !lookup_attribute ("common", DECL_లక్షణాలు (newdecl))
      && !lookup_attribute ("nocommon", DECL_లక్షణాలు (newdecl)))
    DECL_COMMON (newdecl) = DECL_COMMON (newdecl) && DECL_COMMON (olddecl);

  /* Copy most of the decl-specific fields of NEWDECL into OLDDECL.
     But preserve OLDDECL's DECL_UID, DECL_CONTEXT and
     DECL_ARGUMENTS (if appropriate).  */
  {
    గుర్తులేని olddecl_uid = DECL_UID (olddecl);
    వృక్షం olddecl_context = DECL_CONTEXT (olddecl);
    వృక్షం olddecl_arguments = ఖాళీ;
    ఒకవేళ (వృక్షం_సంకేతం (olddecl) == FUNCTION_DECL)
      olddecl_arguments = DECL_ARGUMENTS (olddecl);

    జ్ఞాపకం_నకలు ((అక్షరం *) olddecl + పరిమాణం (నిర్మాణం వృక్షం_common),
	    (అక్షరం *) newdecl + పరిమాణం (నిర్మాణం వృక్షం_common),
	    పరిమాణం (నిర్మాణం వృక్షం_decl_common) - పరిమాణం (నిర్మాణం వృక్షం_common));
    DECL_USER_ALIGN (olddecl) = DECL_USER_ALIGN (newdecl);
    ఎంపిక (వృక్షం_సంకేతం (olddecl))
      {
      స్థితి FUNCTION_DECL:
      స్థితి VAR_DECL:
	{
	  నిర్మాణం symtab_కణుపు *snode = olddecl->decl_with_vis.symtab_కణుపు;

	  జ్ఞాపకం_నకలు ((అక్షరం *) olddecl + పరిమాణం (నిర్మాణం వృక్షం_decl_common),
		  (అక్షరం *) newdecl + పరిమాణం (నిర్మాణం వృక్షం_decl_common),
		  వృక్షం_సంకేతం_కొలత (వృక్షం_సంకేతం (olddecl)) - పరిమాణం (నిర్మాణం వృక్షం_decl_common));
	  olddecl->decl_with_vis.symtab_కణుపు = snode;

	  ఒకవేళ ((DECL_EXTERNAL (olddecl)
	       || వృక్షం_ప్రజా (olddecl)
	       || వృక్షం_STATIC (olddecl))
	      && DECL_SECTION_NAME (newdecl) != ఖాళీ)
	    సమితి_decl_section_name (olddecl, newdecl);

	  /* This isn't quite correct for something like
		int __thread x attribute ((tls_model ("local-exec")));
		extern int __thread x;
	     as we'll lose the "local-exec" model.  */
	  ఒకవేళ (VAR_P (olddecl) && DECL_THREAD_LOCAL_P (newdecl))
	    సమితి_decl_tls_model (olddecl, DECL_TLS_MODEL (newdecl));
	  ఆపు;
	}

      స్థితి క్షేత్రం_DECL:
      స్థితి PARM_DECL:
      స్థితి LABEL_DECL:
      స్థితి ఫలితం_DECL:
      స్థితి CONST_DECL:
      స్థితి TYPE_DECL:
	జ్ఞాపకం_నకలు ((అక్షరం *) olddecl + పరిమాణం (నిర్మాణం వృక్షం_decl_common),
		(అక్షరం *) newdecl + పరిమాణం (నిర్మాణం వృక్షం_decl_common),
		వృక్షం_సంకేతం_కొలత (వృక్షం_సంకేతం (olddecl)) - పరిమాణం (నిర్మాణం వృక్షం_decl_common));
	ఆపు;

      అప్రమేయ:

	జ్ఞాపకం_నకలు ((అక్షరం *) olddecl + పరిమాణం (నిర్మాణం వృక్షం_decl_common),
		(అక్షరం *) newdecl + పరిమాణం (నిర్మాణం వృక్షం_decl_common),
		పరిమాణం (నిర్మాణం వృక్షం_decl_non_common) - పరిమాణం (నిర్మాణం వృక్షం_decl_common));
      }
    DECL_UID (olddecl) = olddecl_uid;
    DECL_CONTEXT (olddecl) = olddecl_context;
    ఒకవేళ (వృక్షం_సంకేతం (olddecl) == FUNCTION_DECL)
      DECL_ARGUMENTS (olddecl) = olddecl_arguments;
  }

  /* If OLDDECL had its DECL_RTL instantiated, re-invoke make_decl_rtl
     so that encode_section_info has a chance to look at the new decl
     flags and attributes.  */
  ఒకవేళ (DECL_RTL_సమితి_P (olddecl)
      && (వృక్షం_సంకేతం (olddecl) == FUNCTION_DECL
	  || (VAR_P (olddecl) && వృక్షం_STATIC (olddecl))))
    make_decl_rtl (olddecl);
}

/* Handle when a new declaration NEWDECL has the same name as an old
   one OLDDECL in the same binding contour.  Prints an error message
   if appropriate.

   If safely possible, alter OLDDECL to look like NEWDECL, and return
   true.  Otherwise, return false.  */

స్థిర తార్కిక
duplicate_decls (వృక్షం newdecl, వృక్షం olddecl)
{
  వృక్షం newtype = ఖాళీ, oldtype = ఖాళీ;

  ఒకవేళ (!diagnose_mismatched_decls (newdecl, olddecl, &newtype, &oldtype))
    {
      /* Avoid `unused variable' and other warnings for OLDDECL.  */
      suppress_warning (olddecl, OPT_Wunused);
      /* If the types are completely different, poison them both with
 	 error_mark_node.  */
      ఒకవేళ (వృక్షం_సంకేతం (వృక్షం_TYPE (newdecl)) != వృక్షం_సంకేతం (వృక్షం_TYPE (olddecl))
	  && olddecl != error_mark_కణుపు
	  && చూసిన_error ())
	{
	  ఒకవేళ (వృక్షం_సంకేతం (olddecl) != FUNCTION_DECL)
	    వృక్షం_TYPE (olddecl) = error_mark_కణుపు;
	  ఒకవేళ (వృక్షం_సంకేతం (newdecl) != FUNCTION_DECL)
	    వృక్షం_TYPE (newdecl) = error_mark_కణుపు;
	}
      తిరిగి అబద్ధం;
    }

  విలీనం_decls (newdecl, olddecl, newtype, oldtype);

  /* The NEWDECL will no longer be needed.

     Before releasing the node, be sure to remove function from symbol
     table that might have been inserted there to record comdat group.
     Be sure to however do not free DECL_STRUCT_FUNCTION because this
     structure is shared in between NEWDECL and OLDECL.  */
  ఒకవేళ (వృక్షం_సంకేతం (newdecl) == FUNCTION_DECL)
    DECL_STRUCT_FUNCTION (newdecl) = ఖాళీ;
  ఒకవేళ (VAR_OR_FUNCTION_DECL_P (newdecl))
    {
      నిర్మాణం symtab_కణుపు *snode = symtab_కణుపు::get (newdecl);
      ఒకవేళ (snode)
	snode->remove ();
    }
  ggc_free (newdecl);
  తిరిగి నిజం;
}


/* Check whether decl-node NEW_DECL shadows an existing declaration.  */
స్థిర శూన్య
warn_if_shadowing (వృక్షం new_decl)
{
  నిర్మాణం c_binding *b;

  /* Shadow warnings wanted?  */
  ఒకవేళ (!(warn_shadow
        || warn_shadow_local
        || warn_shadow_compatible_local)
      /* No shadow warnings for internally generated vars.  */
      || DECL_IS_UNDECLARED_BUILTIN (new_decl))
    తిరిగి;

  /* Is anything being shadowed?  Invisible decls do not count.  */
  కొరకు (b = I_చిహ్నం_BINDING (DECL_NAME (new_decl)); b; b = b->shadowed)
    ఒకవేళ (b->decl && b->decl != new_decl && !b->invisible
	&& (b->decl == error_mark_కణుపు
	    || diagnostic_report_warnings_p (global_dc,
					     DECL_ఆధారం_LOCATION (b->decl))))
      {
	వృక్షం old_decl = b->decl;

	ఒకవేళ (old_decl == error_mark_కణుపు)
	  {
	    warning (OPT_Wshadow, "declaration of %q+D shadows previous "
		     "non-variable", new_decl);
	    ఆపు;
	  }

	తార్కిక warned = అబద్ధం;
	auto_diagnostic_సమూహం d;
	ఒకవేళ (వృక్షం_సంకేతం (old_decl) == PARM_DECL)
	  {
	    గణన opt_సంకేతం warning_సంకేతం;

	    /* If '-Wshadow=compatible-local' is specified without other
	       -Wshadow= flags, we will warn only when the types of the
	       shadowing variable (i.e. new_decl) and the shadowed variable
	       (old_decl) are compatible.  */
	    ఒకవేళ (warn_shadow)
	      warning_సంకేతం = OPT_Wshadow;
	    లేకపోతే ఒకవేళ (comptypes (వృక్షం_TYPE (old_decl), వృక్షం_TYPE (new_decl)))
	      warning_సంకేతం = OPT_Wshadow_compatible_local;
	    లేకపోతే
	      warning_సంకేతం = OPT_Wshadow_local;
	    warned = warning_at (DECL_ఆధారం_LOCATION (new_decl), warning_సంకేతం,
				 "declaration of %qD shadows a parameter",
				 new_decl);
	  }
	లేకపోతే ఒకవేళ (DECL_FILE_SCOPE_P (old_decl))
	  {
	    /* Do not warn if a variable shadows a function, unless
	       the variable is a function or a pointer-to-function.  */
	    ఒకవేళ (వృక్షం_సంకేతం (old_decl) == FUNCTION_DECL
		&& వృక్షం_సంకేతం (new_decl) != FUNCTION_DECL
		&& !FUNCTION_సూచిక_TYPE_P (వృక్షం_TYPE (new_decl)))
		కొనసాగు;

	    warned = warning_at (DECL_ఆధారం_LOCATION (new_decl), OPT_Wshadow,
				 "declaration of %qD shadows a global "
				 "declaration",
				 new_decl);
	  }
	లేకపోతే ఒకవేళ (వృక్షం_సంకేతం (old_decl) == FUNCTION_DECL
		 && fndecl_built_లోపల_p (old_decl))
	  {
	    warning (OPT_Wshadow, "declaration of %q+D shadows "
		     "a built-in function", new_decl);
	    ఆపు;
	  }
	లేకపోతే
	  {
	    గణన opt_సంకేతం warning_సంకేతం;

	    /* If '-Wshadow=compatible-local' is specified without other
	       -Wshadow= flags, we will warn only when the types of the
	       shadowing variable (i.e. new_decl) and the shadowed variable
	       (old_decl) are compatible.  */
	    ఒకవేళ (warn_shadow)
	      warning_సంకేతం = OPT_Wshadow;
	    లేకపోతే ఒకవేళ (comptypes (వృక్షం_TYPE (old_decl), వృక్షం_TYPE (new_decl)))
	      warning_సంకేతం = OPT_Wshadow_compatible_local;
	    లేకపోతే
	      warning_సంకేతం = OPT_Wshadow_local;
	    warned = warning_at (DECL_ఆధారం_LOCATION (new_decl), warning_సంకేతం,
				 "declaration of %qD shadows a previous local",
				 new_decl);
	  }

	ఒకవేళ (warned)
	  inform (DECL_ఆధారం_LOCATION (old_decl),
		  "shadowed declaration is here");

	ఆపు;
      }
}

/* Record a decl-node X as belonging to the current lexical scope.
   Check for errors (such as an incompatible declaration for the same
   name already seen in the same scope).

   Returns either X or an old decl for the same name.
   If an old decl is returned, it may have been smashed
   to agree with what X says.  */

వృక్షం
pushdecl (వృక్షం x)
{
  వృక్షం name = DECL_NAME (x);
  నిర్మాణం c_scope *scope = current_scope;
  నిర్మాణం c_binding *b;
  తార్కిక nested = అబద్ధం;
  location_t locus = DECL_ఆధారం_LOCATION (x);

  /* Must set DECL_CONTEXT for everything not at file scope or
     DECL_FILE_SCOPE_P won't work.  Local externs don't count
     unless they have initializers (which generate code).  We
     also exclude CONST_DECLs because enumerators will get the
     type of the enum as context.  */
  ఒకవేళ (current_function_decl
      && వృక్షం_సంకేతం (x) != CONST_DECL
      && (!VAR_OR_FUNCTION_DECL_P (x)
	  || DECL_INITIAL (x) || !వృక్షం_ప్రజా (x)))
    DECL_CONTEXT (x) = current_function_decl;

  /* Anonymous decls are just inserted in the scope.  */
  ఒకవేళ (!name)
    {
      bind (name, x, scope, /*invisible=*/అబద్ధం, /*nested=*/అబద్ధం,
	    locus);
      తిరిగి x;
    }

  /* First, see if there is another declaration with the same name in
     the current scope.  If there is, duplicate_decls may do all the
     work for us.  If duplicate_decls returns false, that indicates
     two incompatible decls in the same scope; we are to silently
     replace the old one (duplicate_decls has issued all appropriate
     diagnostics).  In particular, we should not consider possible
     duplicates in the external scope, or shadowing.  */
  b = I_చిహ్నం_BINDING (name);
  ఒకవేళ (b && B_లోపల_SCOPE (b, scope))
    {
      నిర్మాణం c_binding *b_ext, *b_use;
      వృక్షం type = వృక్షం_TYPE (x);
      వృక్షం visdecl = b->decl;
      వృక్షం vistype = వృక్షం_TYPE (visdecl);
      ఒకవేళ (వృక్షం_సంకేతం (వృక్షం_TYPE (x)) == ARRAY_TYPE
	  && COMPLETE_TYPE_P (వృక్షం_TYPE (x)))
	b->inner_comp = అబద్ధం;
      b_use = b;
      b_ext = b;
      /* If this is an external linkage declaration, we should check
	 for compatibility with the type in the external scope before
	 setting the type at this scope based on the visible
	 information only.  */
      ఒకవేళ (వృక్షం_ప్రజా (x) && వృక్షం_ప్రజా (visdecl))
	{
	  అయితే (b_ext && !B_లోపల_EXTERNAL_SCOPE (b_ext))
	    b_ext = b_ext->shadowed;
	  ఒకవేళ (b_ext)
	    {
	      b_use = b_ext;
	      ఒకవేళ (b_use->u.type)
		వృక్షం_TYPE (b_use->decl) = b_use->u.type;
	    }
	}

      /* Check if x is part of a FMV set with b_use.
	 FMV is only supported in c for targets with target_version
	 attributes.  */
      ఒకవేళ (!లక్ష్యం_HAS_FMV_లక్ష్యం_ATTRIBUTE
	  && b_use && వృక్షం_సంకేతం (b_use->decl) == FUNCTION_DECL
	  && వృక్షం_సంకేతం (x) == FUNCTION_DECL && DECL_FILE_SCOPE_P (b_use->decl)
	  && DECL_FILE_SCOPE_P (x)
	  && disjoint_సంస్కరణ_decls (x, b_use->decl)
	  && comptypes (vistype, type))
	{
	  maybe_mark_function_versioned (b_use->decl);
	  maybe_mark_function_versioned (b->decl);
	  maybe_mark_function_versioned (x);

	  cgraph_కణుపు *b_కణుపు = cgraph_కణుపు::get_create (b_use->decl);
	  cgraph_function_సంస్కరణ_info *b_v = b_కణుపు->function_సంస్కరణ ();
	  ఒకవేళ (!b_v)
	    b_v = b_కణుపు->చొప్పించు_new_function_సంస్కరణ ();

	  /* Check if this new node conflicts with any previous functions
	     in the set.  */
	  cgraph_function_సంస్కరణ_info *సంస్కరణ = b_v;
	  కొరకు (; సంస్కరణ; సంస్కరణ = సంస్కరణ->తదుపరి)
	    ఒకవేళ (!disjoint_సంస్కరణ_decls (సంస్కరణ->this_కణుపు->decl, x))
	      {
		/* The decls define overlapping version, so attempt to merge
		   or diagnose the conflict.  */
		ఒకవేళ (duplicate_decls (x, సంస్కరణ->this_కణుపు->decl))
		  తిరిగి సంస్కరణ->this_కణుపు->decl;
		లేకపోతే
		  తిరిగి error_mark_కణుపు;
	      }

	  /* This is a new version to be added to FMV structure.  */
	  cgraph_కణుపు::కూడు_function_సంస్కరణ (b_v, x);

	  /* Get the first node from the structure.  */
	  cgraph_function_సంస్కరణ_info *default_v = b_v;
	  అయితే (default_v->prev)
	    default_v = default_v->prev;
	  /* Always use the default node for the bindings.  */
	  b_use->decl = default_v->this_కణుపు->decl;
	  b->decl = default_v->this_కణుపు->decl;

	  /* Node is not a duplicate, so no need to do the rest of the
	     checks.  */
	  తిరిగి x;
	}

      ఒకవేళ (duplicate_decls (x, b_use->decl))
	{
	  ఒకవేళ (b_use != b)
	    {
	      /* Save the updated type in the external scope and
		 restore the proper type for this scope.  */
	      వృక్షం thistype;
	      ఒకవేళ (comptypes (vistype, type))
		thistype = సంయుక్త_type (vistype, type);
	      లేకపోతే
		thistype = వృక్షం_TYPE (b_use->decl);
	      b_use->u.type = వృక్షం_TYPE (b_use->decl);
	      ఒకవేళ (వృక్షం_సంకేతం (b_use->decl) == FUNCTION_DECL
		  && fndecl_built_లోపల_p (b_use->decl))
		thistype
		  = c_build_type_attribute_variant (thistype,
						    TYPE_లక్షణాలు
						    (b_use->u.type));
	      వృక్షం_TYPE (b_use->decl) = thistype;
	    }
	  తిరిగి b_use->decl;
	}
      లేకపోతే
	వెళ్ళు skip_external_and_shadow_checks;
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
  ఒకవేళ ((DECL_EXTERNAL (x) || scope == file_scope)
      && (VAR_OR_FUNCTION_DECL_P (x) || c_dialect_objc ()))
    {
      వృక్షం type = వృక్షం_TYPE (x);
      వృక్షం vistype = NULL_వృక్షం;
      వృక్షం visdecl = NULL_వృక్షం;
      తార్కిక type_saved = అబద్ధం;
      ఒకవేళ (b && !B_లోపల_EXTERNAL_SCOPE (b)
	  && VAR_OR_FUNCTION_DECL_P (b->decl)
	  && DECL_FILE_SCOPE_P (b->decl))
	{
	  visdecl = b->decl;
	  vistype = వృక్షం_TYPE (visdecl);
	}
      ఒకవేళ (scope != file_scope
	  && !DECL_లోపల_SYSTEM_శీర్షిక (x))
	warning_at (locus, OPT_Wnested_externs,
		    "nested extern declaration of %qD", x);

      అయితే (b && !B_లోపల_EXTERNAL_SCOPE (b))
	{
	  /* If this decl might be modified, save its type.  This is
	     done here rather than when the decl is first bound
	     because the type may change after first binding, through
	     being completed or through attributes being added.  If we
	     encounter multiple such decls, only the first should have
	     its type saved; the others will already have had their
	     proper types saved and the types will not have changed as
	     their scopes will not have been re-entered.  */
	  ఒకవేళ (DECL_P (b->decl) && DECL_FILE_SCOPE_P (b->decl) && !type_saved)
	    {
	      b->u.type = వృక్షం_TYPE (b->decl);
	      type_saved = నిజం;
	    }
	  ఒకవేళ (B_లోపల_FILE_SCOPE (b)
	      && VAR_P (b->decl)
	      && వృక్షం_STATIC (b->decl)
	      && వృక్షం_సంకేతం (వృక్షం_TYPE (b->decl)) == ARRAY_TYPE
	      && !TYPE_DOMAIN (వృక్షం_TYPE (b->decl))
	      && వృక్షం_సంకేతం (type) == ARRAY_TYPE
	      && TYPE_DOMAIN (type)
	      && TYPE_MAX_విలువ (TYPE_DOMAIN (type))
	      && !integer_zerop (TYPE_MAX_విలువ (TYPE_DOMAIN (type))))
	    {
	      /* Array type completed in inner scope, which should be
		 diagnosed if the completion does not have size 1 and
		 it does not get completed in the file scope.  */
	      b->inner_comp = నిజం;
	    }
	  b = b->shadowed;
	}

      /* If a matching external declaration has been found, set its
	 type to the composite of all the types of that declaration.
	 After the consistency checks, it will be reset to the
	 composite of the visible types only.  */
      ఒకవేళ (b && b->u.type)
	వృక్షం_TYPE (b->decl) = b->u.type;

      /* the static does not go in the externals scope.  */
      ఒకవేళ (b && duplicate_decls (x, b->decl))
	{
	  వృక్షం thistype;
	  ఒకవేళ (vistype)
	    {
	      ఒకవేళ (comptypes (vistype, type))
		thistype = సంయుక్త_type (vistype, type);
	      లేకపోతే
		thistype = వృక్షం_TYPE (b->decl);
	    }
	  లేకపోతే
	    thistype = type;
	  b->u.type = వృక్షం_TYPE (b->decl);
	  /* Propagate the type attributes to the decl.  */
	  thistype
	    = c_build_type_attribute_variant (thistype,
					      TYPE_లక్షణాలు (b->u.type));
	  వృక్షం_TYPE (b->decl) = thistype;
	  bind (name, b->decl, scope, /*invisible=*/అబద్ధం, /*nested=*/నిజం,
		locus);
	  తిరిగి b->decl;
	}
      లేకపోతే ఒకవేళ (వృక్షం_ప్రజా (x))
	{
	  ఒకవేళ (visdecl && !b && duplicate_decls (x, visdecl))
	    {
	      /* An external declaration at block scope referring to a
		 visible entity with internal linkage.  The composite
		 type will already be correct for this scope, so we
		 just need to fall through to make the declaration in
		 this scope.  */
	      nested = నిజం;
	      x = visdecl;
	    }
	  లేకపోతే
	    {
	      bind (name, x, external_scope, /*invisible=*/నిజం,
		    /*nested=*/అబద్ధం, locus);
	      nested = నిజం;
	    }
	}
    }

  ఒకవేళ (వృక్షం_సంకేతం (x) != PARM_DECL)
    warn_if_shadowing (x);

 skip_external_and_shadow_checks:
  ఒకవేళ (వృక్షం_సంకేతం (x) == TYPE_DECL)
    {
      /* So this is a typedef, set its underlying type.  */
      సమితి_underlying_type (x);

      /* If X is a typedef defined in the current function, record it
	 for the purpose of implementing the -Wunused-local-typedefs
	 warning.  */
      రికార్డు_locally_defined_typedef (x);
    }

  bind (name, x, scope, /*invisible=*/అబద్ధం, nested, locus);

  /* If x's type is incomplete because it's based on a
     structure or union which has not yet been fully declared,
     attach it to that structure or union type, so we can go
     back and complete the variable declaration later, if the
     structure or union gets fully declared.

     If the input is erroneous, we can have error_mark in the type
     slot (e.g. "f(void a, ...)") - that doesn't count as an
     incomplete type.  */
  ఒకవేళ (వృక్షం_TYPE (x) != error_mark_కణుపు
      && !COMPLETE_TYPE_P (వృక్షం_TYPE (x)))
    {
      వృక్షం element = వృక్షం_TYPE (x);

      అయితే (వృక్షం_సంకేతం (element) == ARRAY_TYPE)
	element = వృక్షం_TYPE (element);
      element = TYPE_MAIN_VARIANT (element);

      ఒకవేళ ((రికార్డు_OR_UNION_TYPE_P (element)
	   || వృక్షం_సంకేతం (element) == ENUMERAL_TYPE)
	  && (వృక్షం_సంకేతం (x) != TYPE_DECL
	      || వృక్షం_సంకేతం (వృక్షం_TYPE (x)) == ARRAY_TYPE)
	  && !COMPLETE_TYPE_P (element))
	C_TYPE_INCOMPLETE_VARS (element)
	  = వృక్షం_cons (NULL_వృక్షం, x, C_TYPE_INCOMPLETE_VARS (element));
    }
  తిరిగి x;
}


/* Issue a permerror about implicit function declaration.  ID is the function
   identifier, OLDDECL is a declaration of the function in a different scope,
   or NULL_TREE.  */

స్థిర శూన్య
implicit_decl_permerror (location_t loc, వృక్షం id, వృక్షం olddecl)
{
  ఒకవేళ (!warn_implicit_function_declaration)
    తిరిగి;

  తార్కిక warned;
  auto_diagnostic_సమూహం d;
  name_hint hint;
  ఒకవేళ (!olddecl)
    hint = lookup_name_fuzzy (id, FUZZY_LOOKUP_FUNCTION_NAME, loc);

  ఒకవేళ (flag_isoc99)
    {
      ఒకవేళ (స్థిరరాశి అక్షరం *suggestion = hint.suggestion ())
	{
	  gcc_rich_location richloc (loc);
	  richloc.కూడు_fixit_replace (suggestion);
	  warned = permerror_opt (&richloc, OPT_Wimplicit_function_declaration,
				  "implicit declaration of function %qE;"
				  " did you mean %qs?",
				  id, suggestion);
	}
      లేకపోతే
	warned = permerror_opt (loc, OPT_Wimplicit_function_declaration,
				"implicit declaration of function %qE", id);
    }
  లేకపోతే ఒకవేళ (స్థిరరాశి అక్షరం *suggestion = hint.suggestion ())
    {
      gcc_rich_location richloc (loc);
      richloc.కూడు_fixit_replace (suggestion);
      warned = warning_at
	(&richloc, OPT_Wimplicit_function_declaration,
	 G_("implicit declaration of function %qE; did you mean %qs?"),
	 id, suggestion);
    }
  లేకపోతే
    warned = warning_at (loc, OPT_Wimplicit_function_declaration,
			 G_("implicit declaration of function %qE"), id);

  ఒకవేళ (warned)
    {
      /* Whether the olddecl is an undeclared builtin function.
	 locate_old_decl will not generate a diagnostic for those,
	 so in that case we want to look elsewhere.  */
      తార్కిక undeclared_builtin = (olddecl
				 && వృక్షం_సంకేతం (olddecl) == FUNCTION_DECL
				 && fndecl_built_లోపల_p (olddecl)
				 && !C_DECL_DECLARED_BUILTIN (olddecl));
      ఒకవేళ (undeclared_builtin)
	{
	  స్థిరరాశి అక్షరం *శీర్షిక = శీర్షిక_for_builtin_fn (olddecl);
	  ఒకవేళ (శీర్షిక)
	    {
	      rich_location richloc (పంక్తి_పట్టిక, loc);
	      maybe_కూడు_include_fixit (&richloc, శీర్షిక, నిజం);
	      inform (&richloc,
		      "include %qs or provide a declaration of %qE",
		      శీర్షిక, id);
	    }
	}
      లేకపోతే ఒకవేళ (olddecl)
	locate_old_decl (olddecl);
    }

  ఒకవేళ (!warned)
    hint.suppress ();
}

/* Return the name of the header file that declares built-in function
   FNDECL, or null if either we don't know or don't expect to see an
   explicit declaration.  */

స్థిర స్థిరరాశి అక్షరం *
శీర్షిక_for_builtin_fn (వృక్షం fndecl)
{
  ఒకవేళ (DECL_BUILT_లోపల_CLASS (fndecl) != BUILT_లోపల_సాధారణ)
    తిరిగి ఖాళీ;

  ఎంపిక (DECL_FUNCTION_సంకేతం (fndecl))
    {
    CASE_FLT_FN (BUILT_లోపల_ACOS):
    CASE_FLT_FN (BUILT_లోపల_ACOSH):
    CASE_FLT_FN (BUILT_లోపల_ASIN):
    CASE_FLT_FN (BUILT_లోపల_ASINH):
    CASE_FLT_FN (BUILT_లోపల_ATAN):
    CASE_FLT_FN (BUILT_లోపల_ATANH):
    CASE_FLT_FN (BUILT_లోపల_ATAN2):
    CASE_FLT_FN (BUILT_లోపల_CBRT):
    CASE_FLT_FN (BUILT_లోపల_CEIL):
    CASE_FLT_FN_FLOATN_NX (BUILT_లోపల_CEIL):
    CASE_FLT_FN (BUILT_లోపల_COPYSIGN):
    CASE_FLT_FN_FLOATN_NX (BUILT_లోపల_COPYSIGN):
    CASE_FLT_FN (BUILT_లోపల_COS):
    CASE_FLT_FN (BUILT_లోపల_COSH):
    CASE_FLT_FN (BUILT_లోపల_ERF):
    CASE_FLT_FN (BUILT_లోపల_ERFC):
    CASE_FLT_FN (BUILT_లోపల_EXP):
    CASE_FLT_FN (BUILT_లోపల_EXP2):
    CASE_FLT_FN (BUILT_లోపల_EXPM1):
    CASE_FLT_FN (BUILT_లోపల_FABS):
    CASE_FLT_FN_FLOATN_NX (BUILT_లోపల_FABS):
    CASE_FLT_FN (BUILT_లోపల_FDIM):
    CASE_FLT_FN (BUILT_లోపల_FLOOR):
    CASE_FLT_FN_FLOATN_NX (BUILT_లోపల_FLOOR):
    CASE_FLT_FN (BUILT_లోపల_FMA):
    CASE_FLT_FN_FLOATN_NX (BUILT_లోపల_FMA):
    CASE_FLT_FN (BUILT_లోపల_FMAX):
    CASE_FLT_FN_FLOATN_NX (BUILT_లోపల_FMAX):
    CASE_FLT_FN (BUILT_లోపల_FMIN):
    CASE_FLT_FN_FLOATN_NX (BUILT_లోపల_FMIN):
    CASE_FLT_FN (BUILT_లోపల_FMOD):
    CASE_FLT_FN (BUILT_లోపల_FREXP):
    CASE_FLT_FN (BUILT_లోపల_HYPOT):
    CASE_FLT_FN (BUILT_లోపల_ILOGB):
    CASE_FLT_FN (BUILT_లోపల_LDEXP):
    CASE_FLT_FN (BUILT_లోపల_LGAMMA):
    CASE_FLT_FN (BUILT_లోపల_LLRINT):
    CASE_FLT_FN (BUILT_లోపల_LLROUND):
    CASE_FLT_FN (BUILT_లోపల_LOG):
    CASE_FLT_FN (BUILT_లోపల_LOG10):
    CASE_FLT_FN (BUILT_లోపల_LOG1_P):
    CASE_FLT_FN (BUILT_లోపల_LOG2):
    CASE_FLT_FN (BUILT_లోపల_LOGB):
    CASE_FLT_FN (BUILT_లోపల_LRINT):
    CASE_FLT_FN (BUILT_లోపల_LROUND):
    CASE_FLT_FN (BUILT_లోపల_MODF):
    CASE_FLT_FN (BUILT_లోపల_NAN):
    CASE_FLT_FN (BUILT_లోపల_NEARBYINT):
    CASE_FLT_FN_FLOATN_NX (BUILT_లోపల_NEARBYINT):
    CASE_FLT_FN (BUILT_లోపల_NEXTAFTER):
    CASE_FLT_FN (BUILT_లోపల_NEXTTOWARD):
    CASE_FLT_FN (BUILT_లోపల_POW):
    CASE_FLT_FN (BUILT_లోపల_REMAINDER):
    CASE_FLT_FN (BUILT_లోపల_REMQUO):
    CASE_FLT_FN (BUILT_లోపల_RINT):
    CASE_FLT_FN_FLOATN_NX (BUILT_లోపల_RINT):
    CASE_FLT_FN (BUILT_లోపల_విడత):
    CASE_FLT_FN_FLOATN_NX (BUILT_లోపల_విడత):
    CASE_FLT_FN (BUILT_లోపల_SCALBLN):
    CASE_FLT_FN (BUILT_లోపల_SCALBN):
    CASE_FLT_FN (BUILT_లోపల_SIN):
    CASE_FLT_FN (BUILT_లోపల_SINH):
    CASE_FLT_FN (BUILT_లోపల_SINCOS):
    CASE_FLT_FN (BUILT_లోపల_SQRT):
    CASE_FLT_FN_FLOATN_NX (BUILT_లోపల_SQRT):
    CASE_FLT_FN (BUILT_లోపల_TAN):
    CASE_FLT_FN (BUILT_లోపల_TANH):
    CASE_FLT_FN (BUILT_లోపల_TGAMMA):
    CASE_FLT_FN (BUILT_లోపల_TRUNC):
    CASE_FLT_FN_FLOATN_NX (BUILT_లోపల_TRUNC):
    స్థితి BUILT_లోపల_ISINF:
    స్థితి BUILT_లోపల_ISNAN:
      తిరిగి "<math.h>";
    CASE_FLT_FN (BUILT_లోపల_CABS):
    CASE_FLT_FN (BUILT_లోపల_CACOS):
    CASE_FLT_FN (BUILT_లోపల_CACOSH):
    CASE_FLT_FN (BUILT_లోపల_CARG):
    CASE_FLT_FN (BUILT_లోపల_CASIN):
    CASE_FLT_FN (BUILT_లోపల_CASINH):
    CASE_FLT_FN (BUILT_లోపల_CATAN):
    CASE_FLT_FN (BUILT_లోపల_CATANH):
    CASE_FLT_FN (BUILT_లోపల_CCOS):
    CASE_FLT_FN (BUILT_లోపల_CCOSH):
    CASE_FLT_FN (BUILT_లోపల_CEXP):
    CASE_FLT_FN (BUILT_లోపల_CIMAG):
    CASE_FLT_FN (BUILT_లోపల_CLOG):
    CASE_FLT_FN (BUILT_లోపల_CONJ):
    CASE_FLT_FN (BUILT_లోపల_CPOW):
    CASE_FLT_FN (BUILT_లోపల_CPROJ):
    CASE_FLT_FN (BUILT_లోపల_CREAL):
    CASE_FLT_FN (BUILT_లోపల_CSIN):
    CASE_FLT_FN (BUILT_లోపల_CSINH):
    CASE_FLT_FN (BUILT_లోపల_CSQRT):
    CASE_FLT_FN (BUILT_లోపల_CTAN):
    CASE_FLT_FN (BUILT_లోపల_CTANH):
      తిరిగి "<complex.h>";
    స్థితి BUILT_లోపల_MEMCHR:
    స్థితి BUILT_లోపల_MEMCMP:
    స్థితి BUILT_లోపల_MEMCPY:
    స్థితి BUILT_లోపల_MEMMOVE:
    స్థితి BUILT_లోపల_MEMSET:
    స్థితి BUILT_లోపల_STRCAT:
    స్థితి BUILT_లోపల_STRCHR:
    స్థితి BUILT_లోపల_STRCMP:
    స్థితి BUILT_లోపల_STRCPY:
    స్థితి BUILT_లోపల_STRCSPN:
    స్థితి BUILT_లోపల_STRLEN:
    స్థితి BUILT_లోపల_STRNCAT:
    స్థితి BUILT_లోపల_STRNCMP:
    స్థితి BUILT_లోపల_STRNCPY:
    స్థితి BUILT_లోపల_STRPBRK:
    స్థితి BUILT_లోపల_STRRCHR:
    స్థితి BUILT_లోపల_STRSPN:
    స్థితి BUILT_లోపల_STRSTR:
      తిరిగి "<string.h>";
    స్థితి BUILT_లోపల_FPRINTF:
    స్థితి BUILT_లోపల_PUTC:
    స్థితి BUILT_లోపల_FPUTC:
    స్థితి BUILT_లోపల_FPUTS:
    స్థితి BUILT_లోపల_FSCANF:
    స్థితి BUILT_లోపల_FWRITE:
    స్థితి BUILT_లోపల_PRINTF:
    స్థితి BUILT_లోపల_PUTCHAR:
    స్థితి BUILT_లోపల_PUTS:
    స్థితి BUILT_లోపల_SCANF:
    స్థితి BUILT_లోపల_SNPRINTF:
    స్థితి BUILT_లోపల_SPRINTF:
    స్థితి BUILT_లోపల_SSCANF:
    స్థితి BUILT_లోపల_VFPRINTF:
    స్థితి BUILT_లోపల_VFSCANF:
    స్థితి BUILT_లోపల_VPRINTF:
    స్థితి BUILT_లోపల_VSCANF:
    స్థితి BUILT_లోపల_VSNPRINTF:
    స్థితి BUILT_లోపల_VSPRINTF:
    స్థితి BUILT_లోపల_VSSCANF:
      తిరిగి "<stdio.h>";
    స్థితి BUILT_లోపల_ISALNUM:
    స్థితి BUILT_లోపల_ISALPHA:
    స్థితి BUILT_లోపల_ISBLANK:
    స్థితి BUILT_లోపల_ISCNTRL:
    స్థితి BUILT_లోపల_ISDIGIT:
    స్థితి BUILT_లోపల_ISGRAPH:
    స్థితి BUILT_లోపల_ISLOWER:
    స్థితి BUILT_లోపల_ISPRINT:
    స్థితి BUILT_లోపల_ISPUNCT:
    స్థితి BUILT_లోపల_ISSPACE:
    స్థితి BUILT_లోపల_ISUPPER:
    స్థితి BUILT_లోపల_ISXDIGIT:
    స్థితి BUILT_లోపల_TOLOWER:
    స్థితి BUILT_లోపల_TOUPPER:
      తిరిగి "<ctype.h>";
    స్థితి BUILT_లోపల_ISWALNUM:
    స్థితి BUILT_లోపల_ISWALPHA:
    స్థితి BUILT_లోపల_ISWBLANK:
    స్థితి BUILT_లోపల_ISWCNTRL:
    స్థితి BUILT_లోపల_ISWDIGIT:
    స్థితి BUILT_లోపల_ISWGRAPH:
    స్థితి BUILT_లోపల_ISWLOWER:
    స్థితి BUILT_లోపల_ISWPRINT:
    స్థితి BUILT_లోపల_ISWPUNCT:
    స్థితి BUILT_లోపల_ISWSPACE:
    స్థితి BUILT_లోపల_ISWUPPER:
    స్థితి BUILT_లోపల_ISWXDIGIT:
    స్థితి BUILT_లోపల_TOWLOWER:
    స్థితి BUILT_లోపల_TOWUPPER:
      తిరిగి "<wctype.h>";
    స్థితి BUILT_లోపల_ABORT:
    స్థితి BUILT_లోపల_ABS:
    స్థితి BUILT_లోపల_CALLOC:
    స్థితి BUILT_లోపల_EXIT:
    స్థితి BUILT_లోపల_FREE:
    స్థితి BUILT_లోపల_LABS:
    స్థితి BUILT_లోపల_LLABS:
    స్థితి BUILT_లోపల_MALLOC:
    స్థితి BUILT_లోపల_REALLOC:
    స్థితి BUILT_లోపల_EXIT2:
    స్థితి BUILT_లోపల_ALIGNED_ALLOC:
      తిరిగి "<stdlib.h>";
    స్థితి BUILT_లోపల_IMAXABS:
      తిరిగి "<inttypes.h>";
    స్థితి BUILT_లోపల_STRFTIME:
      తిరిగి "<time.h>";
    అప్రమేయ:
      తిరిగి ఖాళీ;
    }
}

/* Generate an implicit declaration for identifier FUNCTIONID at LOC as a
   function of type int ().  */

వృక్షం
implicitly_declare (location_t loc, వృక్షం functionid)
{
  నిర్మాణం c_binding *b;
  వృక్షం decl = NULL_వృక్షం;
  వృక్షం asmspec_వృక్షం;

  కొరకు (b = I_చిహ్నం_BINDING (functionid); b; b = b->shadowed)
    {
      ఒకవేళ (B_లోపల_SCOPE (b, external_scope))
	{
	  decl = b->decl;
	  ఆపు;
	}
    }

  ఒకవేళ (decl)
    {
      ఒకవేళ (వృక్షం_సంకేతం (decl) != FUNCTION_DECL)
	తిరిగి decl;

      /* FIXME: Objective-C has weird not-really-builtin functions
	 which are supposed to be visible automatically.  They wind up
	 in the external scope because they're pushed before the file
	 scope gets created.  Catch this here and rebind them into the
	 file scope.  */
      ఒకవేళ (!fndecl_built_లోపల_p (decl) && DECL_IS_UNDECLARED_BUILTIN (decl))
	{
	  bind (functionid, decl, file_scope,
		/*invisible=*/అబద్ధం, /*nested=*/నిజం,
		DECL_ఆధారం_LOCATION (decl));
	  తిరిగి decl;
	}
      లేకపోతే
	{
	  వృక్షం newtype = default_function_type;
	  ఒకవేళ (b->u.type)
	    వృక్షం_TYPE (decl) = b->u.type;
	  /* Implicit declaration of a function already declared
	     (somehow) in a different scope, or as a built-in.
	     If this is the first time this has happened, warn;
	     then recycle the old declaration but with the new type.  */
	  ఒకవేళ (!C_DECL_IMPLICIT (decl))
	    {
	      implicit_decl_permerror (loc, functionid, decl);
	      C_DECL_IMPLICIT (decl) = 1;
	    }
	  ఒకవేళ (fndecl_built_లోపల_p (decl))
	    {
	      newtype = c_build_type_attribute_variant (newtype,
							TYPE_లక్షణాలు
							(వృక్షం_TYPE (decl)));
	      ఒకవేళ (!comptypes (newtype, వృక్షం_TYPE (decl)))
		{
		  auto_diagnostic_సమూహం d;
		  తార్కిక warned = warning_at (loc,
					    OPT_Wbuiltin_declaration_mismatch,
					    "incompatible implicit "
					    "declaration of built-in "
					    "function %qD", decl);
		  /* See if we can hint which header to include.  */
		  స్థిరరాశి అక్షరం *శీర్షిక = శీర్షిక_for_builtin_fn (decl);
		  ఒకవేళ (శీర్షిక != ఖాళీ && warned)
		    {
		      rich_location richloc (పంక్తి_పట్టిక, loc);
		      maybe_కూడు_include_fixit (&richloc, శీర్షిక, నిజం);
		      inform (&richloc,
			      "include %qs or provide a declaration of %qD",
			      శీర్షిక, decl);
		    }
		  newtype = వృక్షం_TYPE (decl);
		}
	    }
	  లేకపోతే
	    {
	      ఒకవేళ (!comptypes (newtype, వృక్షం_TYPE (decl)))
		{
		  auto_diagnostic_సమూహం d;
		  error_at (loc, "incompatible implicit declaration of "
			    "function %qD", decl);
		  locate_old_decl (decl);
		}
	    }
	  b->u.type = వృక్షం_TYPE (decl);
	  వృక్షం_TYPE (decl) = newtype;
	  bind (functionid, decl, current_scope,
		/*invisible=*/అబద్ధం, /*nested=*/నిజం,
		DECL_ఆధారం_LOCATION (decl));
	  తిరిగి decl;
	}
    }

  /* Not seen before.  */
  decl = build_decl (loc, FUNCTION_DECL, functionid, default_function_type);
  DECL_EXTERNAL (decl) = 1;
  వృక్షం_ప్రజా (decl) = 1;
  C_DECL_IMPLICIT (decl) = 1;
  implicit_decl_permerror (loc, functionid, 0);
  asmspec_వృక్షం = maybe_apply_renaming_pragma (decl, /*asmname=*/ఖాళీ);
  ఒకవేళ (asmspec_వృక్షం)
    సమితి_user_assembler_name (decl, వృక్షం_STRING_సూచిక (asmspec_వృక్షం));

  /* C89 says implicit declarations are in the innermost block.
     So we record the decl in the standard fashion.  */
  decl = pushdecl (decl);

  /* No need to call objc_check_decl here - it's a function type.  */
  rest_యొక్క_decl_compilation (decl, 0, 0);

  /* Write a record describing this implicit function declaration
     to the prototypes file (if requested).  */
  gen_aux_info_రికార్డు (decl, 0, 1, 0);

  /* Possibly apply some default attributes to this implicit declaration.  */
  decl_లక్షణాలు (&decl, NULL_వృక్షం, 0);

  తిరిగి decl;
}

/* Issue an error message for a reference to an undeclared variable
   ID, including a reference to a builtin outside of function-call
   context.  Establish a binding of the identifier to error_mark_node
   in an appropriate scope, which will suppress further errors for the
   same identifier.  The error message should be given location LOC.  */
శూన్య
undeclared_variable (location_t loc, వృక్షం id)
{
  స్థిర తార్కిక already = అబద్ధం;
  నిర్మాణం c_scope *scope;

  auto_diagnostic_సమూహం d;
  ఒకవేళ (current_function_decl == NULL_వృక్షం)
    {
      name_hint guessed_id = lookup_name_fuzzy (id, FUZZY_LOOKUP_NAME, loc);
      ఒకవేళ (స్థిరరాశి అక్షరం *suggestion = guessed_id.suggestion ())
	{
	  gcc_rich_location richloc (loc);
	  richloc.కూడు_fixit_replace (suggestion);
	  error_at (&richloc,
		    "%qE undeclared here (not in a function);"
		    " did you mean %qs?",
		    id, suggestion);
	}
      లేకపోతే
	error_at (loc, "%qE undeclared here (not in a function)", id);
      scope = current_scope;
    }
  లేకపోతే
    {
      ఒకవేళ (!objc_diagnose_వ్యక్తిగత_ivar (id))
	{
	  name_hint guessed_id = lookup_name_fuzzy (id, FUZZY_LOOKUP_NAME, loc);
	  ఒకవేళ (స్థిరరాశి అక్షరం *suggestion = guessed_id.suggestion ())
	    {
	      gcc_rich_location richloc (loc);
	      richloc.కూడు_fixit_replace (suggestion);
	      error_at (&richloc,
			"%qE undeclared (first use in this function);"
			" did you mean %qs?",
			id, suggestion);
	    }
	  లేకపోతే
	    error_at (loc, "%qE undeclared (first use in this function)", id);
	}
      ఒకవేళ (!already)
	{
          inform (loc, "each undeclared identifier is reported only"
                  " once for each function it appears in");
	  already = నిజం;
	}

      /* If we are parsing old-style parameter decls, current_function_decl
	 will be nonnull but current_function_scope will be null.  */
      scope = current_function_scope ? current_function_scope : current_scope;
    }
  bind (id, error_mark_కణుపు, scope, /*invisible=*/అబద్ధం, /*nested=*/అబద్ధం,
	UNKNOWN_LOCATION);
}

/* Subroutine of lookup_label, declare_label, define_label: construct a
   LABEL_DECL with all the proper frills.  Also create a struct
   c_label_vars initialized for the current scope.  */

స్థిర వృక్షం
make_label (location_t location, వృక్షం name, తార్కిక defining,
	    నిర్మాణం c_label_vars **p_label_vars)
{
  వృక్షం label = build_decl (location, LABEL_DECL, name, void_type_కణుపు);
  DECL_CONTEXT (label) = current_function_decl;
  సమితి_DECL_బహుళకం (label, VOIDmode);

  c_label_vars *label_vars = ggc_alloc<c_label_vars> ();
  label_vars->shadowed = ఖాళీ;
  సమితి_spot_bindings (&label_vars->label_bindings, defining);
  label_vars->decls_లోపల_scope = make_వృక్షం_సదిశ ();
  label_vars->gotos = ఖాళీ;
  *p_label_vars = label_vars;

  తిరిగి label;
}

/* Get the LABEL_DECL corresponding to identifier NAME as a label.
   Create one if none exists so far for the current function.
   This is called when a label is used in a goto expression or
   has its address taken.  */

వృక్షం
lookup_label (వృక్షం name)
{
  వృక్షం label;
  నిర్మాణం c_label_vars *label_vars;

  ఒకవేళ (current_function_scope == 0)
    {
      error ("label %qE referenced outside of any function", name);
      తిరిగి NULL_వృక్షం;
    }

  /* Use a label already defined or ref'd with this name, but not if
     it is inherited from a containing function and wasn't declared
     using __label__.  */
  label = I_LABEL_DECL (name);
  ఒకవేళ (label && (DECL_CONTEXT (label) == current_function_decl
		|| C_DECLARED_LABEL_FLAG (label)))
    {
      /* If the label has only been declared, update its apparent
	 location to point here, for better diagnostics if it
	 turns out not to have been defined.  */
      ఒకవేళ (DECL_INITIAL (label) == NULL_వృక్షం)
	DECL_ఆధారం_LOCATION (label) = ఆదానం_location;
      తిరిగి label;
    }

  /* No label binding for that identifier; make one.  */
  label = make_label (ఆదానం_location, name, అబద్ధం, &label_vars);

  /* Ordinary labels go in the current function scope.  */
  bind_label (name, label, current_function_scope, label_vars);

  తిరిగి label;
}

/* Issue a warning about DECL for a goto statement at GOTO_LOC going
   to LABEL.  */

స్థిర శూన్య
warn_about_goto (location_t goto_loc, వృక్షం label, వృక్షం decl)
{
  auto_diagnostic_సమూహం d;
  ఒకవేళ (c_type_variably_modified_p (వృక్షం_TYPE (decl)))
    error_at (goto_loc,
	      "jump into scope of identifier with variably modified type");
  లేకపోతే ఒకవేళ (flag_openmp
	   && lookup_attribute ("omp allocate", DECL_లక్షణాలు (decl)))
    error_at (goto_loc, "jump skips OpenMP %<allocate%> allocation");
  లేకపోతే
    ఒకవేళ (!warning_at (goto_loc, OPT_Wjump_తప్పినవి_init,
		     "jump skips variable initialization"))
      తిరిగి;
  inform (DECL_ఆధారం_LOCATION (label), "label %qD defined here", label);
  inform (DECL_ఆధారం_LOCATION (decl), "%qD declared here", decl);
}

/* Look up a label because of a goto statement.  This is like
   lookup_label, but also issues any appropriate warnings.  */

వృక్షం
lookup_label_for_goto (location_t loc, వృక్షం name)
{
  వృక్షం label;
  నిర్మాణం c_label_vars *label_vars;
  గుర్తులేని పూర్ణాంకం ix;
  వృక్షం decl;

  label = lookup_label (name);
  ఒకవేళ (label == NULL_వృక్షం)
    తిరిగి NULL_వృక్షం;

  /* If we are jumping to a different function, we can't issue any
     useful warnings.  */
  ఒకవేళ (DECL_CONTEXT (label) != current_function_decl)
    {
      gcc_assert (C_DECLARED_LABEL_FLAG (label));
      తిరిగి label;
    }

  label_vars = I_LABEL_BINDING (name)->u.label;

  /* If the label has not yet been defined, then push this goto on a
     list for possible later warnings.  */
  ఒకవేళ (label_vars->label_bindings.scope == ఖాళీ)
    {
      c_goto_bindings *g = ggc_alloc<c_goto_bindings> ();

      g->loc = loc;
      సమితి_spot_bindings (&g->goto_bindings, నిజం);
      vec_సురక్షిత_నెట్టు (label_vars->gotos, g);
      తిరిగి label;
    }

  /* If there are any decls in label_vars->decls_in_scope, then this
     goto has missed the declaration of the decl.  This happens for a
     case like
       int i = 1;
      lab:
       ...
       goto lab;
     Issue a warning or error.  */
  FOR_EACH_VEC_సురక్షిత_ELT (label_vars->decls_లోపల_scope, ix, decl)
    warn_about_goto (loc, label, decl);

  ఒకవేళ (label_vars->label_bindings.ఎడమ_stmt_సమాసం)
    {
      auto_diagnostic_సమూహం d;
      error_at (loc, "jump into statement expression");
      inform (DECL_ఆధారం_LOCATION (label), "label %qD defined here", label);
    }

  తిరిగి label;
}

/* Make a label named NAME in the current function, shadowing silently
   any that may be inherited from containing functions or containing
   scopes.  This is called for __label__ declarations.  */

వృక్షం
declare_label (వృక్షం name)
{
  నిర్మాణం c_binding *b = I_LABEL_BINDING (name);
  వృక్షం label;
  నిర్మాణం c_label_vars *label_vars;

  /* Check to make sure that the label hasn't already been declared
     at this scope */
  ఒకవేళ (b && B_లోపల_CURRENT_SCOPE (b))
    {
      auto_diagnostic_సమూహం d;
      error ("duplicate label declaration %qE", name);
      locate_old_decl (b->decl);

      /* Just use the previous declaration.  */
      తిరిగి b->decl;
    }

  label = make_label (ఆదానం_location, name, అబద్ధం, &label_vars);
  C_DECLARED_LABEL_FLAG (label) = 1;

  /* Declared labels go in the current scope.  */
  bind_label (name, label, current_scope, label_vars);

  తిరిగి label;
}

/* When we define a label, issue any appropriate warnings if there are
   any gotos earlier in the function which jump to this label.  */

స్థిర శూన్య
check_earlier_gotos (వృక్షం label, నిర్మాణం c_label_vars* label_vars)
{
  గుర్తులేని పూర్ణాంకం ix;
  నిర్మాణం c_goto_bindings *g;

  FOR_EACH_VEC_సురక్షిత_ELT (label_vars->gotos, ix, g)
    {
      నిర్మాణం c_binding *b;
      నిర్మాణం c_scope *scope;

      /* We have a goto to this label.  The goto is going forward.  In
	 g->scope, the goto is going to skip any binding which was
	 defined after g->bindings_in_scope.  */
      ఒకవేళ (g->goto_bindings.scope->has_jump_unsafe_decl)
	{
	  కొరకు (b = g->goto_bindings.scope->bindings;
	       b != g->goto_bindings.bindings_లోపల_scope;
	       b = b->prev)
	    {
	      ఒకవేళ (decl_jump_unsafe (b->decl))
		warn_about_goto (g->loc, label, b->decl);
	    }
	}

      /* We also need to warn about decls defined in any scopes
	 between the scope of the label and the scope of the goto.  */
      కొరకు (scope = label_vars->label_bindings.scope;
	   scope != g->goto_bindings.scope;
	   scope = scope->outer)
	{
	  gcc_assert (scope != ఖాళీ);
	  ఒకవేళ (scope->has_jump_unsafe_decl)
	    {
	      ఒకవేళ (scope == label_vars->label_bindings.scope)
		b = label_vars->label_bindings.bindings_లోపల_scope;
	      లేకపోతే
		b = scope->bindings;
	      కొరకు (; b != ఖాళీ; b = b->prev)
		{
		  ఒకవేళ (decl_jump_unsafe (b->decl))
		    warn_about_goto (g->loc, label, b->decl);
		}
	    }
	}

      ఒకవేళ (g->goto_bindings.stmt_exprs > 0)
	{
	  auto_diagnostic_సమూహం d;
	  error_at (g->loc, "jump into statement expression");
	  inform (DECL_ఆధారం_LOCATION (label), "label %qD defined here",
		  label);
	}
    }

  /* Now that the label is defined, we will issue warnings about
     subsequent gotos to this label when we see them.  */
  vec_సురక్షిత_truncate (label_vars->gotos, 0);
  label_vars->gotos = ఖాళీ;
}

/* Define a label, specifying the location in the source file.
   Return the LABEL_DECL node for the label, if the definition is valid.
   Otherwise return NULL_TREE.  */

వృక్షం
define_label (location_t location, వృక్షం name)
{
  /* Find any preexisting label with this name.  It is an error
     if that label has already been defined in this function, or
     if there is a containing function with a declared label with
     the same name.  */
  వృక్షం label = I_LABEL_DECL (name);

  ఒకవేళ (label
      && ((DECL_CONTEXT (label) == current_function_decl
	   && DECL_INITIAL (label) != NULL_వృక్షం)
	  || (DECL_CONTEXT (label) != current_function_decl
	      && C_DECLARED_LABEL_FLAG (label))))
    {
      auto_diagnostic_సమూహం d;
      error_at (location, "duplicate label %qD", label);
      locate_old_decl (label);
      తిరిగి NULL_వృక్షం;
    }
  లేకపోతే ఒకవేళ (label && DECL_CONTEXT (label) == current_function_decl)
    {
      నిర్మాణం c_label_vars *label_vars = I_LABEL_BINDING (name)->u.label;

      /* The label has been used or declared already in this function,
	 but not defined.  Update its location to point to this
	 definition.  */
      DECL_ఆధారం_LOCATION (label) = location;
      సమితి_spot_bindings (&label_vars->label_bindings, నిజం);

      /* Issue warnings as required about any goto statements from
	 earlier in the function.  */
      check_earlier_gotos (label, label_vars);
    }
  లేకపోతే
    {
      నిర్మాణం c_label_vars *label_vars;

      /* No label binding for that identifier; make one.  */
      label = make_label (location, name, నిజం, &label_vars);

      /* Ordinary labels go in the current function scope.  */
      bind_label (name, label, current_function_scope, label_vars);
    }

  ఒకవేళ (!లోపల_system_శీర్షిక_at (ఆదానం_location) && lookup_name (name))
    warning_at (location, OPT_Wtraditional,
		"traditional C lacks a separate namespace "
		"for labels, identifier %qE conflicts", name);

  /* Mark label as having been defined.  */
  DECL_INITIAL (label) = error_mark_కణుపు;
  తిరిగి label;
}

/* Get the bindings for a new switch statement.  This is used to issue
   warnings as appropriate for jumps from the switch to case or
   default labels.  */

నిర్మాణం c_spot_bindings *
c_get_switch_bindings (శూన్య)
{
  నిర్మాణం c_spot_bindings *switch_bindings;

  switch_bindings = XNEW (నిర్మాణం c_spot_bindings);
  సమితి_spot_bindings (switch_bindings, నిజం);
  తిరిగి switch_bindings;
}

శూన్య
c_release_switch_bindings (నిర్మాణం c_spot_bindings *bindings)
{
  gcc_assert (bindings->stmt_exprs == 0 && !bindings->ఎడమ_stmt_సమాసం);
  XDELETE (bindings);
}

/* This is called at the point of a case or default label to issue
   warnings about decls as needed.  It returns true if it found an
   error, not just a warning.  */

తార్కిక
c_check_switch_jump_warnings (నిర్మాణం c_spot_bindings *switch_bindings,
			      location_t switch_loc, location_t case_loc)
{
  తార్కిక saw_error;
  నిర్మాణం c_scope *scope;

  saw_error = అబద్ధం;
  కొరకు (scope = current_scope;
       scope != switch_bindings->scope;
       scope = scope->outer)
    {
      నిర్మాణం c_binding *b;

      gcc_assert (scope != ఖాళీ);

      ఒకవేళ (!scope->has_jump_unsafe_decl)
	కొనసాగు;

      కొరకు (b = scope->bindings; b != ఖాళీ; b = b->prev)
	{
	  ఒకవేళ (decl_jump_unsafe (b->decl))
	    {
	      auto_diagnostic_సమూహం d;
	      తార్కిక emitted;
	      ఒకవేళ (c_type_variably_modified_p (వృక్షం_TYPE (b->decl)))
		{
		  saw_error = నిజం;
		  error_at (case_loc,
			    "switch jumps into scope of identifier with "
			    "variably modified type");
		  emitted = నిజం;
		}
	      లేకపోతే ఒకవేళ (flag_openmp
		       && lookup_attribute ("omp allocate",
					    DECL_లక్షణాలు (b->decl)))
		{
		  saw_error = నిజం;
		  error_at (case_loc,
			    "switch jumps over OpenMP %<allocate%> allocation");
		  emitted = నిజం;
		}
	      లేకపోతే
		emitted
		  = warning_at (case_loc, OPT_Wjump_తప్పినవి_init,
				"switch jumps over variable initialization");
	      ఒకవేళ (emitted)
		{
		  inform (switch_loc, "switch starts here");
		  inform (DECL_ఆధారం_LOCATION (b->decl), "%qD declared here",
			  b->decl);
		}
	    }
	}
    }

  ఒకవేళ (switch_bindings->stmt_exprs > 0)
    {
      saw_error = నిజం;
      auto_diagnostic_సమూహం d;
      error_at (case_loc, "switch jumps into statement expression");
      inform (switch_loc, "switch starts here");
    }

  తిరిగి saw_error;
}

/* Given NAME, an IDENTIFIER_NODE,
   return the structure (or union or enum) definition for that name.
   If THISLEVEL_ONLY is nonzero, searches only the current_scope.
   CODE says which kind of type the caller wants;
   it is RECORD_TYPE or UNION_TYPE or ENUMERAL_TYPE.
   If PLOC is not NULL and this returns non-null, it sets *PLOC to the
   location where the tag was defined.
   If the wrong kind of type is found, an error is reported.  */

స్థిర వృక్షం
lookup_ట్యాగ్ (గణన వృక్షం_సంకేతం_2 సంకేతం_2, వృక్షం name, తార్కిక thislevel_only,
	    location_t *ploc)
{
  నిర్మాణం c_binding *b = I_ట్యాగ్_BINDING (name);
  తార్కిక thislevel = అబద్ధం;

  ఒకవేళ (!b || !b->decl)
    తిరిగి NULL_వృక్షం;

  /* We only care about whether it's in this level if
     thislevel_only was set or it might be a type clash.  */
  ఒకవేళ (thislevel_only || వృక్షం_సంకేతం (b->decl) != సంకేతం_2)
    {
      /* For our purposes, a tag in the external scope is the same as
	 a tag in the file scope.  (Primarily relevant to Objective-C
	 and its builtin structure tags, which get pushed before the
	 file scope is created.)  */
      ఒకవేళ (B_లోపల_CURRENT_SCOPE (b)
	  || (current_scope == file_scope && B_లోపల_EXTERNAL_SCOPE (b)))
	thislevel = నిజం;
    }

  ఒకవేళ (thislevel_only && !thislevel)
    తిరిగి NULL_వృక్షం;

  ఒకవేళ (వృక్షం_సంకేతం (b->decl) != సంకేతం_2)
    {
      /* Definition isn't the kind we were looking for.  */
      pending_invalid_xref = name;
      pending_invalid_xref_location = ఆదానం_location;

      /* If in the same binding level as a declaration as a tag
	 of a different type, this must not be allowed to
	 shadow that tag, so give the error immediately.
	 (For example, "struct foo; union foo;" is invalid.)  */
      ఒకవేళ (thislevel)
	pending_xref_error ();
    }

  ఒకవేళ (ploc != ఖాళీ)
    *ploc = b->locus;

  తిరిగి b->decl;
}

/* Return true if a definition exists for NAME with code CODE.  */

తార్కిక
ట్యాగ్_exists_p (గణన వృక్షం_సంకేతం_2 సంకేతం_2, వృక్షం name)
{
  నిర్మాణం c_binding *b = I_ట్యాగ్_BINDING (name);

  ఒకవేళ (b == ఖాళీ || b->decl == NULL_వృక్షం)
    తిరిగి అబద్ధం;
  తిరిగి వృక్షం_సంకేతం (b->decl) == సంకేతం_2;
}

/* Print an error message now
   for a recent invalid struct, union or enum cross reference.
   We don't print them immediately because they are not invalid
   when used in the `struct foo;' construct for shadowing.  */

శూన్య
pending_xref_error (శూన్య)
{
  ఒకవేళ (pending_invalid_xref != NULL_వృక్షం)
    error_at (pending_invalid_xref_location, "%qE defined as wrong kind of tag",
	      pending_invalid_xref);
  pending_invalid_xref = NULL_వృక్షం;
}


/* Look up NAME in the current scope and its superiors
   in the namespace of variables, functions and typedefs.
   Return a ..._DECL node of some kind representing its definition,
   or return NULL_TREE if it is undefined.  */

వృక్షం
lookup_name (వృక్షం name)
{
  నిర్మాణం c_binding *b = I_చిహ్నం_BINDING (name);
  /* Do not resolve non-default function versions.  */
  ఒకవేళ (b
      && వృక్షం_సంకేతం (b->decl) == FUNCTION_DECL
      && DECL_FUNCTION_VERSIONED (b->decl)
      && !is_function_default_సంస్కరణ (b->decl))
    తిరిగి NULL_వృక్షం;
  ఒకవేళ (b && !b->invisible)
    {
      maybe_రికార్డు_typedef_use (b->decl);
      తిరిగి b->decl;
    }
  తిరిగి NULL_వృక్షం;
}

/* Similar to `lookup_name' but look only at the indicated scope.  */

స్థిర వృక్షం
lookup_name_లోపల_scope (వృక్షం name, నిర్మాణం c_scope *scope)
{
  నిర్మాణం c_binding *b;

  కొరకు (b = I_చిహ్నం_BINDING (name); b; b = b->shadowed)
    ఒకవేళ (B_లోపల_SCOPE (b, scope))
      తిరిగి b->decl;
  తిరిగి NULL_వృక్షం;
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
lookup_name_fuzzy (వృక్షం name, గణన lookup_name_fuzzy_రకం రకం, location_t loc)
{
  gcc_assert (వృక్షం_సంకేతం (name) == IDENTIFIER_కణుపు);

  /* Look up function-like macros first; maybe misusing them. */
  స్వయంచాలక cpp_కణుపు = cpp_lookup (parse_లోపల,
			      (స్థిరరాశి గుర్తులేని అక్షరం*)IDENTIFIER_సూచిక (name),
			      IDENTIFIER_నిడివి (name));
  ఒకవేళ (cpp_కణుపు && cpp_fun_like_macro_p (cpp_కణుపు))
    తిరిగి name_hint
      (శూన్యసూచిక,
       std::make_unique<macro_like_function_వాడిన> (loc,
						   IDENTIFIER_సూచిక (name)));

  /* Next, try some well-known names in the C standard library, in case
     the user forgot a #include.  */
  స్థిరరాశి అక్షరం *శీర్షిక_hint
    = get_c_stdlib_శీర్షిక_for_name (IDENTIFIER_సూచిక (name));

  ఒకవేళ (శీర్షిక_hint)
    తిరిగి name_hint
      (శూన్యసూచిక,
       std::make_unique<suggest_missing_శీర్షిక> (loc,
						 IDENTIFIER_సూచిక (name),
						 శీర్షిక_hint));

  /* Next, look for exact matches for builtin defines that would have been
     defined if the user had passed a command-line option (e.g. -fopenmp
     for "_OPENMP").  */
  diagnostics::option_id option_id
    = get_option_for_builtin_define (IDENTIFIER_సూచిక (name));
  ఒకవేళ (option_id.m_idx > 0)
    తిరిగి name_hint
      (శూన్యసూచిక,
       std::make_unique<suggest_missing_option> (loc,
						 IDENTIFIER_సూచిక (name),
						 option_id));

  /* Only suggest names reserved for the implementation if NAME begins
     with an underscore.  */
  తార్కిక consider_implementation_పేర్లు = (IDENTIFIER_సూచిక (name)[0] == '_');

  ఉత్తమ_సరిపోలిక<వృక్షం, వృక్షం> bm (name);

  /* Look within currently valid scopes.  */
  కొరకు (c_scope *scope = current_scope; scope; scope = scope->outer)
    కొరకు (c_binding *binding = scope->bindings; binding; binding = binding->prev)
      {
	ఒకవేళ (!binding->id || binding->invisible)
	  కొనసాగు;
	ఒకవేళ (binding->decl == error_mark_కణుపు)
	  కొనసాగు;
	/* Don't use bindings from implicitly declared functions,
	   as they were likely misspellings themselves.  */
	ఒకవేళ (వృక్షం_సంకేతం (binding->decl) == FUNCTION_DECL)
	  ఒకవేళ (C_DECL_IMPLICIT (binding->decl))
	    కొనసాగు;
	/* Don't suggest names that are reserved for use by the
	   implementation, unless NAME began with an underscore.  */
	ఒకవేళ (!consider_implementation_పేర్లు)
	  {
	    స్థిరరాశి అక్షరం *suggestion_str = IDENTIFIER_సూచిక (binding->id);
	    ఒకవేళ (name_reserved_for_implementation_p (suggestion_str))
	      కొనసాగు;
	  }
	ఎంపిక (రకం)
	  {
	  స్థితి FUZZY_LOOKUP_TYPENAME:
	    ఒకవేళ (వృక్షం_సంకేతం (binding->decl) != TYPE_DECL)
	      కొనసాగు;
	    ఆపు;

	  స్థితి FUZZY_LOOKUP_FUNCTION_NAME:
	    ఒకవేళ (వృక్షం_సంకేతం (binding->decl) != FUNCTION_DECL)
	      {
		/* Allow function pointers.  */
		ఒకవేళ ((VAR_P (binding->decl)
		     || వృక్షం_సంకేతం (binding->decl) == PARM_DECL)
		    && వృక్షం_సంకేతం (వృక్షం_TYPE (binding->decl)) == సూచిక_TYPE
		    && (వృక్షం_సంకేతం (వృక్షం_TYPE (వృక్షం_TYPE (binding->decl)))
			== FUNCTION_TYPE))
		  ఆపు;
		కొనసాగు;
	      }
	    ఆపు;

	  అప్రమేయ:
	    ఆపు;
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
  ఉత్తమ_macro_సరిపోలిక bmm (name, bm.get_ఉత్తమ_దూరం (), parse_లోపల);
  cpp_hashnode *ఉత్తమ_macro = bmm.get_ఉత్తమ_meaningful_candidate ();
  /* If a macro is the closest so far to NAME, use it, creating an
     identifier tree node for it.  */
  ఒకవేళ (ఉత్తమ_macro)
    {
      స్థిరరాశి అక్షరం *id = (స్థిరరాశి అక్షరం *)ఉత్తమ_macro->ident.str;
      వృక్షం macro_as_identifier
	= get_identifier_with_నిడివి (id, ఉత్తమ_macro->ident.len);
      bm.సమితి_ఉత్తమ_so_far (macro_as_identifier,
			  bmm.get_ఉత్తమ_దూరం (),
			  bmm.get_ఉత్తమ_candidate_నిడివి ());
    }

  /* Try the "start_typename" keywords to detect
     "singed" vs "signed" typos.  */
  ఒకవేళ (రకం == FUZZY_LOOKUP_TYPENAME)
    {
      కొరకు (గుర్తులేని i = 0; i < అంకె_c_common_reswords; i++)
	{
	  స్థిరరాశి c_common_resword *resword = &c_common_reswords[i];
	  ఒకవేళ (!c_keyword_starts_typename (resword->rid))
	    కొనసాగు;
	  వృక్షం resword_identifier = ridpointers [resword->rid];
	  ఒకవేళ (!resword_identifier)
	    కొనసాగు;
	  gcc_assert (వృక్షం_సంకేతం (resword_identifier) == IDENTIFIER_కణుపు);
	  bm.consider (resword_identifier);
	}
    }

  వృక్షం ఉత్తమ = bm.get_ఉత్తమ_meaningful_candidate ();
  ఒకవేళ (ఉత్తమ)
    తిరిగి name_hint (IDENTIFIER_సూచిక (ఉత్తమ), ఖాళీ);
  లేకపోతే
    తిరిగి name_hint (ఖాళీ, ఖాళీ);
}


/* Handle the standard [[nodiscard]] attribute.  */

స్థిర వృక్షం
handle_nodiscard_attribute (వృక్షం *కణుపు, వృక్షం name, వృక్షం /*వాదనలు*/,
			    పూర్ణాంకం /*flags*/, తార్కిక *no_కూడు_attrs)
{
  ఒకవేళ (వృక్షం_సంకేతం (*కణుపు) == FUNCTION_DECL)
    {
      ఒకవేళ (VOID_TYPE_P (వృక్షం_TYPE (వృక్షం_TYPE (*కణుపు))))
	warning_at (DECL_ఆధారం_LOCATION (*కణుపు),
		    OPT_Wattributes, "%qE attribute applied to %qD with void "
		    "return type", name, *కణుపు);
    }
  లేకపోతే ఒకవేళ (రికార్డు_OR_UNION_TYPE_P (*కణుపు)
	   || వృక్షం_సంకేతం (*కణుపు) == ENUMERAL_TYPE)
    /* OK */;
  లేకపోతే
    {
      pedwarn (ఆదానం_location,
	       OPT_Wattributes, "%qE attribute can only be applied to "
	       "functions or to structure, union or enumeration types", name);
      *no_కూడు_attrs = నిజం;
    }
  తిరిగి NULL_వృక్షం;
}

/* Handle the standard [[noreturn]] attribute.  */

స్థిర వృక్షం
handle_std_noreturn_attribute (వృక్షం *కణుపు, వృక్షం name, వృక్షం వాదనలు,
			       పూర్ణాంకం flags, తార్కిక *no_కూడు_attrs)
{
  /* Unlike GNU __attribute__ ((noreturn)), the standard [[noreturn]]
     only applies to functions, not function pointers.  */
  ఒకవేళ (వృక్షం_సంకేతం (*కణుపు) == FUNCTION_DECL)
    తిరిగి handle_noreturn_attribute (కణుపు, name, వాదనలు, flags, no_కూడు_attrs);
  లేకపోతే
    {
      pedwarn (ఆదానం_location, OPT_Wattributes,
	       "standard %qE attribute can only be applied to functions",
	       name);
      *no_కూడు_attrs = నిజం;
      తిరిగి NULL_వృక్షం;
    }
}

/* Handle the standard [[unsequenced]] attribute.  */

స్థిర వృక్షం
handle_std_unsequenced_attribute (వృక్షం *కణుపు, వృక్షం name, వృక్షం వాదనలు,
				  పూర్ణాంకం flags, తార్కిక *no_కూడు_attrs)
{
  /* Unlike GNU __attribute__ ((unsequenced)), the standard [[unsequenced]]
     should be only applied to function declarators or type specifiers which
     have function type.  */
  ఒకవేళ (కణుపు[2])
    {
      auto_diagnostic_సమూహం d;
      ఒకవేళ (pedwarn (ఆదానం_location, OPT_Wattributes,
		   "standard %qE attribute can only be applied to function "
		   "declarators or type specifiers with function type", name))
	inform (ఆదానం_location, "did you mean to specify it after %<)%> "
				"following function parameters?");
      *no_కూడు_attrs = నిజం;
      తిరిగి NULL_వృక్షం;
    }
  తిరిగి handle_unsequenced_attribute (కణుపు, name, వాదనలు, flags, no_కూడు_attrs);
}

/* Handle the standard [[reproducible]] attribute.  */

స్థిర వృక్షం
handle_std_reproducible_attribute (వృక్షం *కణుపు, వృక్షం name, వృక్షం వాదనలు,
				   పూర్ణాంకం flags, తార్కిక *no_కూడు_attrs)
{
  తిరిగి handle_std_unsequenced_attribute (కణుపు, name, వాదనలు, flags,
					   no_కూడు_attrs);
}

/* Table of supported standard (C23) attributes.  */
స్థిర స్థిరరాశి attribute_spec std_లక్షణాలు[] =
{
  /* { name, min_len, max_len, decl_req, type_req, fn_type_req,
       affects_type_identity, handler, exclude } */
  { "_Noreturn", 0, 0, అబద్ధం, అబద్ధం, అబద్ధం, అబద్ధం,
    handle_std_noreturn_attribute, ఖాళీ },
  { "deprecated", 0, 1, అబద్ధం, అబద్ధం, అబద్ధం, అబద్ధం,
    handle_deprecated_attribute, ఖాళీ },
  { "fallthrough", 0, 0, అబద్ధం, అబద్ధం, అబద్ధం, అబద్ధం,
    handle_fallthrough_attribute, ఖాళీ },
  { "maybe_unused", 0, 0, అబద్ధం, అబద్ధం, అబద్ధం, అబద్ధం,
    handle_వాడని_attribute, ఖాళీ },
  { "nodiscard", 0, 1, అబద్ధం, అబద్ధం, అబద్ధం, అబద్ధం,
    handle_nodiscard_attribute, ఖాళీ },
  { "noreturn", 0, 0, అబద్ధం, అబద్ధం, అబద్ధం, అబద్ధం,
    handle_std_noreturn_attribute, ఖాళీ },
  { "reproducible", 0, 0, అబద్ధం, నిజం, నిజం, అబద్ధం,
    handle_std_reproducible_attribute, ఖాళీ },
  { "unsequenced", 0, 0, అబద్ధం, నిజం, నిజం, అబద్ధం,
    handle_std_unsequenced_attribute, ఖాళీ }
};

స్థిరరాశి scoped_attribute_specs std_attribute_పట్టిక =
{
  శూన్యసూచిక, { std_లక్షణాలు }
};

/* Create the predefined scalar types of C,
   and some nodes representing standard constants (0, 1, (void *) 0).
   Initialize the global scope.
   Make definitions for built-in primitive functions.  */

శూన్య
c_init_decl_processing (శూన్య)
{
  location_t save_loc = ఆదానం_location;

  /* Initialize reserved words for parser.  */
  c_parse_init ();

  current_function_decl = NULL_వృక్షం;

  gcc_obstack_init (&parser_obstack);

  /* Make the externals scope.  */
  నెట్టు_scope ();
  external_scope = current_scope;

  /* Declarations from c_common_nodes_and_builtins must not be associated
     with this input file, lest we get differences between using and not
     using preprocessed headers.  */
  ఆదానం_location = BUILTINS_LOCATION;

  c_common_nodes_and_builtins ();

  /* In C, comparisons and TRUTH_* expressions have type int.  */
  truthvalue_type_కణుపు = integer_type_కణుపు;
  truthvalue_true_కణుపు = integer_one_కణుపు;
  truthvalue_false_కణుపు = integer_zero_కణుపు;

  /* Even in C99, which has a real boolean type.  */
  pushdecl (build_decl (UNKNOWN_LOCATION, TYPE_DECL,
			get_identifier (flag_isoc23 ? "bool" : "_Bool"),
			boolean_type_కణుపు));

  /* C-specific nullptr initialization.  */
  రికార్డు_builtin_type (RID_MAX, "typeof (nullptr)", nullptr_type_కణుపు);
  /* The size and alignment of nullptr_t is the same as for a pointer to
     character type.  */
  సమితి_TYPE_ALIGN (nullptr_type_కణుపు, GET_బహుళకం_ALIGNMENT (ptr_బహుళకం));

  ఆదానం_location = save_loc;

  make_fname_decl = c_make_fname_decl;
  ప్రారంభం_fname_decls ();

  ఒకవేళ (warn_keyword_macro)
    {
      కొరకు (గుర్తులేని పూర్ణాంకం i = 0; i < అంకె_c_common_reswords; ++i)
	/* For C register keywords which don't start with underscore
	   or start with just single underscore.  Don't complain about
	   ObjC or Transactional Memory keywords.  */
	ఒకవేళ (c_common_reswords[i].మాట[0] == '_'
	    && c_common_reswords[i].మాట[1] == '_')
	  కొనసాగు;
	లేకపోతే ఒకవేళ (c_common_reswords[i].disable
		 & (D_TRANSMEM | D_OBJC | D_CXX_OBJC))
	  కొనసాగు;
	లేకపోతే
	  {
	    వృక్షం id = get_identifier (c_common_reswords[i].మాట);
	    ఒకవేళ (C_IS_RESERVED_మాట (id)
		&& C_RID_సంకేతం (id) != RID_CXX_COMPAT_WARN)
	      cpp_warn (parse_లోపల, IDENTIFIER_సూచిక (id),
			IDENTIFIER_నిడివి (id));
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

స్థిర వృక్షం
c_make_fname_decl (location_t loc, వృక్షం id, పూర్ణాంకం type_dep)
{
  స్థిరరాశి అక్షరం *name = fname_as_string (type_dep);
  వృక్షం decl, type, init;
  కొలత_t నిడివి = అక్షరశ్రేణి_పొడవు (name);

  type = c_build_array_type (char_type_కణుపు,
			     build_సూచీ_type (కొలత_int (నిడివి)));
  type = c_build_qualified_type (type, TYPE_QUAL_CONST);

  decl = build_decl (loc, VAR_DECL, id, type);

  వృక్షం_STATIC (decl) = 1;
  వృక్షం_READONLY (decl) = 1;
  DECL_ARTIFICIAL (decl) = 1;

  init = build_string (నిడివి + 1, name);
  విడుదల (const_cast<అక్షరం *> (name));
  వృక్షం_TYPE (init) = type;
  DECL_INITIAL (decl) = init;

  వృక్షం_వాడిన (decl) = 1;

  ఒకవేళ (current_function_decl
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
	    /*invisible=*/అబద్ధం, /*nested=*/అబద్ధం, UNKNOWN_LOCATION);
    }

  ముగింపు_decl (decl, loc, init, NULL_వృక్షం, NULL_వృక్షం);

  తిరిగి decl;
}

వృక్షం
c_builtin_function (వృక్షం decl)
{
  వృక్షం type = వృక్షం_TYPE (decl);
  వృక్షం   id = DECL_NAME (decl);

  స్థిరరాశి అక్షరం *name = IDENTIFIER_సూచిక (id);
  C_DECL_BUILTIN_PROTOTYPE (decl) = prototype_p (type);

  /* Should never be called on a symbol with a preexisting meaning.  */
  gcc_assert (!I_చిహ్నం_BINDING (id));

  bind (id, decl, external_scope, /*invisible=*/నిజం, /*nested=*/అబద్ధం,
	UNKNOWN_LOCATION);

  /* Builtins in the implementation namespace are made visible without
     needing to be explicitly declared.  See push_file_scope.  */
  ఒకవేళ (name[0] == '_' && (name[1] == '_' || ISUPPER (name[1])))
    {
      DECL_CHAIN (decl) = visible_builtins;
      visible_builtins = decl;
    }

  తిరిగి decl;
}

వృక్షం
c_builtin_function_ext_scope (వృక్షం decl)
{
  వృక్షం type = వృక్షం_TYPE (decl);
  వృక్షం   id = DECL_NAME (decl);

  స్థిరరాశి అక్షరం *name = IDENTIFIER_సూచిక (id);
  C_DECL_BUILTIN_PROTOTYPE (decl) = prototype_p (type);

  ఒకవేళ (external_scope)
    bind (id, decl, external_scope, /*invisible=*/అబద్ధం, /*nested=*/అబద్ధం,
	  UNKNOWN_LOCATION);

  /* Builtins in the implementation namespace are made visible without
     needing to be explicitly declared.  See push_file_scope.  */
  ఒకవేళ (name[0] == '_' && (name[1] == '_' || ISUPPER (name[1])))
    {
      DECL_CHAIN (decl) = visible_builtins;
      visible_builtins = decl;
    }

  తిరిగి decl;
}

/* Implement LANG_HOOKS_SIMULATE_BUILTIN_FUNCTION_DECL.  */

వృక్షం
c_simulate_builtin_function_decl (వృక్షం decl)
{
  వృక్షం type = వృక్షం_TYPE (decl);
  C_DECL_BUILTIN_PROTOTYPE (decl) = prototype_p (type);
  తిరిగి pushdecl (decl);
}

/* Warn about attributes in a context where they are unused
   (attribute-declarations, except for the "fallthrough" case, and
   attributes on statements).  */

శూన్య
c_warn_వాడని_లక్షణాలు (వృక్షం attrs)
{
  కొరకు (వృక్షం t = attrs; t != NULL_వృక్షం; t = వృక్షం_CHAIN (t))
    ఒకవేళ (get_attribute_namespace (t) == NULL_వృక్షం)
      /* The specifications of standard attributes mean this is a
	 constraint violation.  */
      pedwarn (ఆదానం_location, OPT_Wattributes, "%qE attribute ignored",
	       get_attribute_name (t));
    లేకపోతే ఒకవేళ (!attribute_ignored_p (t))
      warning (OPT_Wattributes, "%qE attribute ignored",
	       get_attribute_name (t));
}

/* Warn for standard attributes being applied to a type that is not
   being defined, where that is a constraint violation, and return a
   list of attributes with them removed.  */

వృక్షం
c_warn_type_లక్షణాలు (వృక్షం type, వృక్షం attrs)
{
  వృక్షం *attr_ptr = &attrs;
  అయితే (*attr_ptr)
    ఒకవేళ (get_attribute_namespace (*attr_ptr) == NULL_వృక్షం)
      {
	ఒకవేళ (వృక్షం_సంకేతం (type) == FUNCTION_TYPE)
	  {
	    వృక్షం name = get_attribute_name (*attr_ptr);
	    /* [[unsequenced]] and [[reproducible]] is fine on function
	       types that aren't being defined.  */
	    ఒకవేళ (is_attribute_p ("unsequenced", name)
		|| is_attribute_p ("reproducible", name))
	      {
		attr_ptr = &వృక్షం_CHAIN (*attr_ptr);
		కొనసాగు;
	      }
	  }
	pedwarn (ఆదానం_location, OPT_Wattributes, "%qE attribute ignored",
		 get_attribute_name (*attr_ptr));
	*attr_ptr = వృక్షం_CHAIN (*attr_ptr);
      }
    లేకపోతే
      attr_ptr = &వృక్షం_CHAIN (*attr_ptr);
  తిరిగి attrs;
}

/* Called when a declaration is seen that contains no names to declare.
   If its type is a reference to a structure, union or enum inherited
   from a containing scope, shadow that tag name for the current scope
   with a forward reference.
   If its type defines a new named structure or union
   or defines an enum, it is valid but we need not do anything here.
   Otherwise, it is an error.  */

శూన్య
shadow_ట్యాగ్ (స్థిరరాశి నిర్మాణం c_declspecs *declspecs)
{
  shadow_ట్యాగ్_warned (declspecs, 0);
}

/* WARNED is 1 if we have done a pedwarn, 2 if we have done a warning,
   but no pedwarn.  */
శూన్య
shadow_ట్యాగ్_warned (స్థిరరాశి నిర్మాణం c_declspecs *declspecs, పూర్ణాంకం warned)
{
  తార్కిక దొరికింది_ట్యాగ్ = అబద్ధం;

  ఒకవేళ (declspecs->type && !declspecs->default_int_p && !declspecs->typedef_p)
    {
      వృక్షం విలువ = declspecs->type;
      గణన వృక్షం_సంకేతం_2 సంకేతం_2 = వృక్షం_సంకేతం (విలువ);

      ఒకవేళ (సంకేతం_2 == రికార్డు_TYPE || సంకేతం_2 == UNION_TYPE || సంకేతం_2 == ENUMERAL_TYPE)
	/* Used to test also that TYPE_SIZE (value) != 0.
	   That caused warning for `struct foo;' at top level in the file.  */
	{
	  వృక్షం name = TYPE_NAME (విలువ);
	  వృక్షం t;

	  దొరికింది_ట్యాగ్ = నిజం;

	  ఒకవేళ (declspecs->restrict_p)
	    {
	      error ("invalid use of %<restrict%>");
	      warned = 1;
	    }

	  ఒకవేళ (లోపల_underspecified_init)
	    {
	      /* This can only occur with extensions such as statement
		 expressions, but is still appropriate as an error to
		 avoid types declared in such a context escaping to
		 the type of an auto variable.  */
	      error ("%qT declared in underspecified object initializer",
		     విలువ);
	      warned = 1;
	    }

	  ఒకవేళ (name == NULL_వృక్షం)
	    {
	      ఒకవేళ (warned != 1 && సంకేతం_2 != ENUMERAL_TYPE)
		/* Empty unnamed enum OK */
		{
		  pedwarn (ఆదానం_location, 0,
			   "unnamed struct/union that defines no instances");
		  warned = 1;
		}
	    }
	  లేకపోతే ఒకవేళ (declspecs->typespec_రకం != ctsk_tagdef
                   && declspecs->typespec_రకం != ctsk_tagfirstref
		   && declspecs->typespec_రకం != ctsk_tagfirstref_attrs
		   && declspecs->storage_class != csc_none)
	    {
	      ఒకవేళ (warned != 1)
		pedwarn (ఆదానం_location, 0,
			 "empty declaration with storage class specifier "
			 "does not redeclare tag");
	      warned = 1;
	      pending_xref_error ();
	    }
	  లేకపోతే ఒకవేళ (declspecs->typespec_రకం != ctsk_tagdef
                   && declspecs->typespec_రకం != ctsk_tagfirstref
                   && declspecs->typespec_రకం != ctsk_tagfirstref_attrs
		   && (declspecs->const_p
		       || declspecs->volatile_p
		       || declspecs->atomic_p
		       || declspecs->restrict_p
		       || declspecs->చిరునామా_space))
	    {
	      ఒకవేళ (warned != 1)
		pedwarn (ఆదానం_location, 0,
			 "empty declaration with type qualifier "
			  "does not redeclare tag");
	      warned = 1;
	      pending_xref_error ();
	    }
	  లేకపోతే ఒకవేళ (declspecs->typespec_రకం != ctsk_tagdef
                   && declspecs->typespec_రకం != ctsk_tagfirstref
                   && declspecs->typespec_రకం != ctsk_tagfirstref_attrs
		   && declspecs->alignas_p)
	    {
	      ఒకవేళ (warned != 1)
		pedwarn (ఆదానం_location, 0,
			 "empty declaration with %<_Alignas%> "
			  "does not redeclare tag");
	      warned = 1;
	      pending_xref_error ();
	    }
	  లేకపోతే ఒకవేళ (declspecs->typespec_రకం != ctsk_tagdef
		   && declspecs->typespec_రకం != ctsk_tagfirstref
		   && declspecs->typespec_రకం != ctsk_tagfirstref_attrs
		   && సంకేతం_2 == ENUMERAL_TYPE
		   && !declspecs->enum_type_specifier_ref_p)
	    {
	      తార్కిక warned_enum = అబద్ధం;
	      ఒకవేళ (warned != 1)
		warned_enum = pedwarn (ఆదానం_location, OPT_Wpedantic,
				       "empty declaration of %<enum%> type "
				       "does not redeclare tag");
	      ఒకవేళ (warned_enum)
		warned = 1;
	      pending_xref_error ();
	    }
	  లేకపోతే
	    {
	      pending_invalid_xref = NULL_వృక్షం;
	      t = lookup_ట్యాగ్ (సంకేతం_2, name, నిజం, ఖాళీ);

	      ఒకవేళ (t == NULL_వృక్షం)
		{
		  t = make_కణుపు (సంకేతం_2);
		  ఒకవేళ (flag_isoc23 || సంకేతం_2 == ENUMERAL_TYPE)
		    సమితి_TYPE_STRUCTURAL_EQUALITY (t);
		  pushtag (ఆదానం_location, name, t);
		}
	    }
	}
      లేకపోతే
	{
	  ఒకవేళ (warned != 1 && !లోపల_system_శీర్షిక_at (ఆదానం_location))
	    {
	      pedwarn (ఆదానం_location, 0,
		       "useless type name in empty declaration");
	      warned = 1;
	    }
	}
    }
  లేకపోతే ఒకవేళ (warned != 1 && !లోపల_system_శీర్షిక_at (ఆదానం_location)
	   && declspecs->typedef_p)
    {
      pedwarn (ఆదానం_location, 0, "useless type name in empty declaration");
      warned = 1;
    }

  pending_invalid_xref = NULL_వృక్షం;

  ఒకవేళ (declspecs->inline_p)
    {
      error ("%<inline%> in empty declaration");
      warned = 1;
    }

  ఒకవేళ (declspecs->noreturn_p)
    {
      error ("%<_Noreturn%> in empty declaration");
      warned = 1;
    }

  ఒకవేళ (declspecs->constexpr_p)
    {
      error ("%<constexpr%> in empty declaration");
      warned = 1;
    }

  ఒకవేళ (current_scope == file_scope && declspecs->storage_class == csc_auto)
    {
      error ("%<auto%> in file-scope empty declaration");
      warned = 1;
    }

  ఒకవేళ (current_scope == file_scope && declspecs->storage_class == csc_రిజిస్టరు)
    {
      error ("%<register%> in file-scope empty declaration");
      warned = 1;
    }

  ఒకవేళ (declspecs->enum_type_specifier_ref_p && !warned)
    {
      ఒకవేళ (declspecs->storage_class != csc_none)
	{
	  error ("storage class specifier in empty declaration with %<enum%> "
		 "underlying type");
	  warned = 1;
	}
      లేకపోతే ఒకవేళ (declspecs->thread_p)
	{
	  error ("%qs in empty declaration with %<enum%> underlying type",
		 declspecs->thread_gnu_p ? "__thread" : "_Thread_local");
	  warned = 1;
	}
      లేకపోతే ఒకవేళ (declspecs->const_p
	       || declspecs->volatile_p
	       || declspecs->atomic_p
	       || declspecs->restrict_p
	       || declspecs->చిరునామా_space)
	{
	  error ("type qualifier in empty declaration with %<enum%> "
		 "underlying type");
	  warned = 1;
	}
      లేకపోతే ఒకవేళ (declspecs->alignas_p)
	{
	  error ("%<alignas%> in empty declaration with %<enum%> "
		 "underlying type");
	  warned = 1;
	}
    }

  ఒకవేళ (!warned && !లోపల_system_శీర్షిక_at (ఆదానం_location)
      && declspecs->storage_class != csc_none)
    {
      warning (0, "useless storage class specifier in empty declaration");
      warned = 2;
    }

  ఒకవేళ (!warned && !లోపల_system_శీర్షిక_at (ఆదానం_location) && declspecs->thread_p)
    {
      warning (0, "useless %qs in empty declaration",
	       declspecs->thread_gnu_p ? "__thread" : "_Thread_local");
      warned = 2;
    }

  ఒకవేళ (!warned
      && !లోపల_system_శీర్షిక_at (ఆదానం_location)
      && (declspecs->const_p
	  || declspecs->volatile_p
	  || declspecs->atomic_p
	  || declspecs->restrict_p
	  || declspecs->చిరునామా_space))
    {
      warning (0, "useless type qualifier in empty declaration");
      warned = 2;
    }

  ఒకవేళ (!warned && !లోపల_system_శీర్షిక_at (ఆదానం_location)
      && declspecs->alignas_p)
    {
      warning (0, "useless %<_Alignas%> in empty declaration");
      warned = 2;
    }

  ఒకవేళ (దొరికింది_ట్యాగ్
      && warned == 2
      && (declspecs->typespec_రకం == ctsk_tagref_attrs
	  || declspecs->typespec_రకం == ctsk_tagfirstref_attrs))
    {
      /* Standard attributes after the "struct" or "union" keyword are
	 only permitted when the contents of the type are defined, or
	 in the form "struct-or-union attribute-specifier-sequence
	 identifier;".  If the ';' was not present, attributes were
	 diagnosed in the parser.  Here, ensure that any other useless
	 elements of the declaration result in a pedwarn, not just a
	 warning.  Forward declarations of enum types are not part of
	 standard C, but handle them the same.  */
      pedwarn (ఆదానం_location, 0,
	       "invalid use of attributes in empty declaration");
      warned = 1;
    }

  ఒకవేళ (warned != 1)
    {
      ఒకవేళ (declspecs->declspecs_చూసిన_p
	  && !declspecs->non_std_attrs_చూసిన_p)
	/* An attribute declaration (but not a fallthrough attribute
	   declaration, which was handled separately); warn if there
	   are any attributes being ignored (but not if the attributes
	   were empty).  */
	c_warn_వాడని_లక్షణాలు (declspecs->attrs);
      లేకపోతే ఒకవేళ (!దొరికింది_ట్యాగ్)
	pedwarn (ఆదానం_location, 0, "empty declaration");
    }
}


/* Return the qualifiers from SPECS as a bitwise OR of TYPE_QUAL_*
   bits.  SPECS represents declaration specifiers that the grammar
   only permits to contain type qualifiers and attributes.  */

పూర్ణాంకం
quals_from_declspecs (స్థిరరాశి నిర్మాణం c_declspecs *specs)
{
  పూర్ణాంకం quals = ((specs->const_p ? TYPE_QUAL_CONST : 0)
	       | (specs->volatile_p ? TYPE_QUAL_VOLATILE : 0)
	       | (specs->restrict_p ? TYPE_QUAL_RESTRICT : 0)
	       | (specs->atomic_p ? TYPE_QUAL_ATOMIC : 0)
	       | (ENCODE_QUAL_ADDR_SPACE (specs->చిరునామా_space)));
  gcc_assert (!specs->type
	      && !specs->decl_attr
	      && specs->typespec_మాట == cts_none
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
  తిరిగి quals;
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

నిర్మాణం c_declarator *
build_array_declarator (location_t loc,
			వృక్షం సమాసం, నిర్మాణం c_declspecs *quals, తార్కిక static_p,
			తార్కిక vla_unspec_p)
{
  నిర్మాణం c_declarator *declarator = XOBNEW (&parser_obstack,
					    నిర్మాణం c_declarator);
  declarator->id_loc = loc;
  declarator->రకం = cdk_array;
  declarator->declarator = 0;
  declarator->u.array.dimen = సమాసం;
  ఒకవేళ (quals)
    {
      declarator->u.array.attrs = quals->attrs;
      declarator->u.array.quals = quals_from_declspecs (quals);
    }
  లేకపోతే
    {
      declarator->u.array.attrs = NULL_వృక్షం;
      declarator->u.array.quals = 0;
    }
  declarator->u.array.static_p = static_p;
  declarator->u.array.vla_unspec_p = vla_unspec_p;
  ఒకవేళ (static_p || quals != ఖాళీ)
    pedwarn_c90 (loc, OPT_Wpedantic,
		 "ISO C90 does not support %<static%> or type "
		 "qualifiers in parameter array declarators");
  ఒకవేళ (vla_unspec_p)
    {
      pedwarn_c90 (loc, OPT_Wpedantic,
		   "ISO C90 does not support %<[*]%> array declarators");
      ఒకవేళ (current_scope->parm_flag)
	current_scope->had_vla_unspec = నిజం;
    }
  తిరిగి declarator;
}

/* Set the contained declarator of an array declarator.  DECL is the
   declarator, as constructed by build_array_declarator; INNER is what
   appears on the left of the [].  */

నిర్మాణం c_declarator *
సమితి_array_declarator_inner (నిర్మాణం c_declarator *decl,
			    నిర్మాణం c_declarator *inner)
{
  decl->declarator = inner;
  తిరిగి decl;
}

/* Determine whether TYPE is a one-element array type "[1]".  */
స్థిర తార్కిక
one_element_array_type_p (const_వృక్షం type)
{
  ఒకవేళ (వృక్షం_సంకేతం (type) != ARRAY_TYPE)
    తిరిగి అబద్ధం;
  తిరిగి integer_zerop (array_type_nelts_minus_one (type));
}

/* Determine whether TYPE is a zero-length array type "[0]".  */
తార్కిక
zero_నిడివి_array_type_p (const_వృక్షం type)
{
  ఒకవేళ (వృక్షం_సంకేతం (type) == ARRAY_TYPE
      && COMPLETE_TYPE_P (type)
      && TYPE_DOMAIN (type) != NULL_వృక్షం
      && (TYPE_MAX_విలువ (TYPE_DOMAIN (type)) == NULL_వృక్షం
	  || integer_all_onesp (TYPE_MAX_విలువ (TYPE_DOMAIN (type)))))
    తిరిగి నిజం;
  తిరిగి అబద్ధం;
}

/* INIT is a constructor that forms DECL's initializer.  If the final
   element initializes a flexible array field, adjust the size of the
   DECL with the initializer based on whether the DECL is a union or
   a structure.  */

స్థిర శూన్య
కూడు_flexible_array_elts_గమ్యం_కొలత (వృక్షం decl, వృక్షం init)
{
  వృక్షం elt, type;

  ఒకవేళ (vec_సురక్షిత_is_ఖాళీలు (CONSTRUCTOR_ELTS (init)))
    తిరిగి;

  elt = CONSTRUCTOR_ELTS (init)->చివరి ().విలువ;
  type = వృక్షం_TYPE (elt);
  ఒకవేళ (flexible_array_member_type_p (type))
    {
      complete_array_type (&type, elt, అబద్ధం);
      /* For a structure, add the size of the initializer to the DECL's
	 size.  */
      ఒకవేళ (వృక్షం_సంకేతం (వృక్షం_TYPE (decl)) == రికార్డు_TYPE)
	{
	  DECL_కొలత (decl)
	    = కొలత_binop (PLUS_సమాసం, DECL_కొలత (decl), TYPE_కొలత (type));
	  DECL_కొలత_UNIT (decl)
	    = కొలత_binop (PLUS_సమాసం, DECL_కొలత_UNIT (decl),
			  TYPE_కొలత_UNIT (type));
	}
      /* For a union, the DECL's size is the maximum of the current size
	 and the size of the initializer.  */
      లేకపోతే
	{
	  DECL_కొలత (decl)
	    = కొలత_binop (MAX_సమాసం, DECL_కొలత (decl), TYPE_కొలత (type));
	  DECL_కొలత_UNIT (decl)
	    = కొలత_binop (MAX_సమాసం, DECL_కొలత_UNIT (decl),
			  TYPE_కొలత_UNIT (type));
	}
    }
}

/* Decode a "typename", such as "int **", returning a ..._TYPE node.
   Set *EXPR, if EXPR not NULL, to any expression to be evaluated
   before the type name, and set *EXPR_CONST_OPERANDS, if
   EXPR_CONST_OPERANDS not NULL, to indicate whether the type name may
   appear in a constant expression.  */

వృక్షం
groktypename (నిర్మాణం c_type_name *type_name, వృక్షం *సమాసం,
	      తార్కిక *సమాసం_const_operands)
{
  వృక్షం type;
  వృక్షం attrs = type_name->specs->attrs;

  type_name->specs->attrs = NULL_వృక్షం;

  type = grokdeclarator (type_name->declarator, type_name->specs, TYPENAME,
			 అబద్ధం, ఖాళీ, &attrs, సమాసం, సమాసం_const_operands,
			 DEPRECATED_సాధారణ);

  /* Apply attributes.  */
  attrs = c_warn_type_లక్షణాలు (type, attrs);
  decl_లక్షణాలు (&type, attrs, 0);

  తిరిగి type;
}


/* Decode a "typename", such as "int **", returning a ..._TYPE node,
   as for groktypename but setting the context to GENERIC_ASSOC.  */

వృక్షం
grokgenassoc (నిర్మాణం c_type_name *type_name)
{
  వృక్షం type;
  వృక్షం attrs = type_name->specs->attrs;

  type_name->specs->attrs = NULL_వృక్షం;

  type = grokdeclarator (type_name->declarator, type_name->specs, GENERIC_ASSOC,
			 అబద్ధం, ఖాళీ, &attrs, ఖాళీ, ఖాళీ, DEPRECATED_సాధారణ);

  /* Apply attributes.  */
  attrs = c_warn_type_లక్షణాలు (type, attrs);
  decl_లక్షణాలు (&type, attrs, 0);

  తిరిగి type;
}


/* Looks up the most recent pushed declaration corresponding to DECL.  */

స్థిర వృక్షం
lookup_చివరి_decl (వృక్షం decl)
{
  వృక్షం చివరి_decl = lookup_name (DECL_NAME (decl));
  ఒకవేళ (!చివరి_decl)
    చివరి_decl = lookup_name_లోపల_scope (DECL_NAME (decl), external_scope);
  తిరిగి చివరి_decl;
}

/* Wrapper for decl_attributes that adds some implicit attributes
   to VAR_DECLs or FUNCTION_DECLs.  */

స్థిర వృక్షం
c_decl_లక్షణాలు (వృక్షం *కణుపు, వృక్షం లక్షణాలు, పూర్ణాంకం flags)
{
  /* Add implicit "omp declare target" attribute if requested.  */
  ఒకవేళ (vec_సురక్షిత_నిడివి (current_omp_declare_లక్ష్యం_attribute)
      && ((VAR_P (*కణుపు) && is_global_var (*కణుపు))
	  || వృక్షం_సంకేతం (*కణుపు) == FUNCTION_DECL))
    {
      ఒకవేళ (VAR_P (*కణుపు) && !omp_mappable_type (వృక్షం_TYPE (*కణుపు)))
	లక్షణాలు = వృక్షం_cons (get_identifier ("omp declare target implicit"),
				NULL_వృక్షం, లక్షణాలు);
      లేకపోతే
	లక్షణాలు = వృక్షం_cons (get_identifier ("omp declare target"),
				NULL_వృక్షం, లక్షణాలు);
      ఒకవేళ (వృక్షం_సంకేతం (*కణుపు) == FUNCTION_DECL)
	{
	  పూర్ణాంకం device_type
	    = current_omp_declare_లక్ష్యం_attribute->చివరి ().device_type;
	  device_type = MAX (device_type, 0);
	  ఒకవేళ ((device_type & OMP_CLAUSE_DEVICE_TYPE_HOST) != 0
	      && !lookup_attribute ("omp declare target host", లక్షణాలు))
	    లక్షణాలు
	      = వృక్షం_cons (get_identifier ("omp declare target host"),
			   NULL_వృక్షం, లక్షణాలు);
	  ఒకవేళ ((device_type & OMP_CLAUSE_DEVICE_TYPE_NOHOST) != 0
	      && !lookup_attribute ("omp declare target nohost", లక్షణాలు))
	    లక్షణాలు
	      = వృక్షం_cons (get_identifier ("omp declare target nohost"),
			   NULL_వృక్షం, లక్షణాలు);

	  పూర్ణాంకం పరోక్ష
	    = current_omp_declare_లక్ష్యం_attribute->చివరి ().పరోక్ష;
	  ఒకవేళ (పరోక్ష && !lookup_attribute ("omp declare target indirect",
					     లక్షణాలు))
	    లక్షణాలు
	      = వృక్షం_cons (get_identifier ("omp declare target indirect"),
			   NULL_వృక్షం, లక్షణాలు);
	}
    }

  ఒకవేళ (flag_openmp || flag_openmp_simd)
    {
      తార్కిక diagnosed = అబద్ధం;
      కొరకు (వృక్షం *pa = &లక్షణాలు; *pa; )
	{
	  ఒకవేళ (is_attribute_namespace_p ("omp", *pa))
	    {
	      వృక్షం name = get_attribute_name (*pa);
	      ఒకవేళ (is_attribute_p ("directive", name)
		  || is_attribute_p ("sequence", name)
		  || is_attribute_p ("decl", name))
		{
		  స్థిరరాశి అక్షరం *p = ఖాళీ;
		  ఒకవేళ (వృక్షం_విలువ (*pa) == NULL_వృక్షం)
		    p = IDENTIFIER_సూచిక (name);
		  కొరకు (వృక్షం a = వృక్షం_విలువ (*pa); a; a = వృక్షం_CHAIN (a))
		    {
		      వృక్షం d = వృక్షం_విలువ (a);
		      gcc_assert (వృక్షం_సంకేతం (d) == C_TOKEN_VEC);
		      ఒకవేళ (వృక్షం_ప్రజా (d)
			  && (VAR_P (*కణుపు)
			      || వృక్షం_సంకేతం (*కణుపు) == FUNCTION_DECL)
			  && c_maybe_parse_omp_decl (*కణుపు, d))
			కొనసాగు;
		      p = వృక్షం_ప్రజా (d) ? "decl" : "directive";
		    }
		  ఒకవేళ (p && !diagnosed)
		    {
		      error ("%<omp::%s%> not allowed to be specified in "
			     "this context", p);
		      diagnosed = నిజం;
		    }
		  ఒకవేళ (p)
		    {
		      *pa = వృక్షం_CHAIN (*pa);
		      కొనసాగు;
		    }
		}
	    }
	  pa = &వృక్షం_CHAIN (*pa);
	}
    }

  /* Look up the current declaration with all the attributes merged
     so far so that attributes on the current declaration that's
     about to be pushed that conflict with the former can be detected,
     diagnosed, and rejected as appropriate.  To match the C++ FE, do
     not pass an error_mark_node when we found an undeclared variable.  */
  వృక్షం చివరి_decl = lookup_చివరి_decl (*కణుపు);
  ఒకవేళ (చివరి_decl == error_mark_కణుపు)
    చివరి_decl = NULL_వృక్షం;
  వృక్షం attr = decl_లక్షణాలు (కణుపు, లక్షణాలు, flags, చివరి_decl);
  ఒకవేళ (VAR_P (*కణుపు) && DECL_THREAD_LOCAL_P (*కణుపు))
    {
      // tls_model attribute can set a stronger TLS access model.
      tls_model model = DECL_TLS_MODEL (*కణుపు);
      tls_model default_model = decl_default_tls_model (*కణుపు);
      ఒకవేళ (default_model > model)
	సమితి_decl_tls_model (*కణుపు, default_model);
    }
  తిరిగి attr;
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

వృక్షం
ప్రారంభం_decl (నిర్మాణం c_declarator *declarator, నిర్మాణం c_declspecs *declspecs,
	    తార్కిక initialized, వృక్షం లక్షణాలు, తార్కిక do_నెట్టు /* = true */,
	    location_t *lastloc /* = NULL */)
{
  వృక్షం decl;
  వృక్షం old_decl;
  వృక్షం tem;
  వృక్షం సమాసం = NULL_వృక్షం;
  గణన deprecated_స్థితులు deprecated_state = DEPRECATED_సాధారణ;

  /* An object declared as __attribute__((unavailable)) suppresses
     warnings and errors from __attribute__((deprecated/unavailable))
     components.
     An object declared as __attribute__((deprecated)) suppresses
     warnings of uses of other deprecated items.  */
  ఒకవేళ (lookup_attribute ("unavailable", లక్షణాలు))
    deprecated_state = UNAVAILABLE_DEPRECATED_SUPPRESS;
  లేకపోతే ఒకవేళ (lookup_attribute ("deprecated", లక్షణాలు))
    deprecated_state = DEPRECATED_SUPPRESS;

  decl = grokdeclarator (declarator, declspecs,
			 సాధారణ, initialized, ఖాళీ, &లక్షణాలు, &సమాసం, ఖాళీ,
			 deprecated_state);
  ఒకవేళ (!decl || decl == error_mark_కణుపు)
    తిరిగి NULL_వృక్షం;

  old_decl = lookup_చివరి_decl (decl);

  ఒకవేళ (వృక్షం lastdecl = lastloc ? old_decl : NULL_వృక్షం)
    ఒకవేళ (lastdecl != error_mark_కణుపు)
      *lastloc = DECL_ఆధారం_LOCATION (lastdecl);

  /* Make sure the size expression is evaluated at this point.  */
  ఒకవేళ (సమాసం && !current_scope->parm_flag)
    కూడు_stmt (fold_convert (void_type_కణుపు, సమాసం));

  ఒకవేళ (వృక్షం_సంకేతం (decl) != FUNCTION_DECL && MAIN_NAME_P (DECL_NAME (decl))
      && వృక్షం_ప్రజా (decl))
    warning (OPT_Wmain, "%q+D is usually a function", decl);

  ఒకవేళ (warn_missing_variable_declarations && VAR_P (decl)
      && !DECL_EXTERNAL (decl) && వృక్షం_ప్రజా (decl) && old_decl == NULL_వృక్షం)
    warning_at (DECL_ఆధారం_LOCATION (decl), OPT_Wmissing_variable_declarations,
		"no previous declaration for %qD", decl);

  ఒకవేళ (initialized)
    /* Is it valid for this decl to have an initializer at all?
       If not, set INITIALIZED to zero, which will indirectly
       tell 'finish_decl' to ignore the initializer once it is parsed.  */
    ఎంపిక (వృక్షం_సంకేతం (decl))
      {
      స్థితి TYPE_DECL:
	error ("typedef %qD is initialized (use %<__typeof__%> instead)", decl);
	initialized = అబద్ధం;
	ఆపు;

      స్థితి FUNCTION_DECL:
	error ("function %qD is initialized like a variable", decl);
	initialized = అబద్ధం;
	ఆపు;

      స్థితి PARM_DECL:
	/* DECL_INITIAL in a PARM_DECL is really DECL_ARG_TYPE.  */
	error ("parameter %qD is initialized", decl);
	initialized = అబద్ధం;
	ఆపు;

      అప్రమేయ:
	/* Don't allow initializations for incomplete types except for
	   arrays which might be completed by the initialization.  */

	/* This can happen if the array size is an undefined macro.
	   We already gave a warning, so we don't need another one.  */
	ఒకవేళ (వృక్షం_TYPE (decl) == error_mark_కణుపు)
	  initialized = అబద్ధం;
	లేకపోతే ఒకవేళ (COMPLETE_TYPE_P (వృక్షం_TYPE (decl)))
	  {
	    /* A complete type is ok if size is fixed.  If the size is
	       variable, an empty initializer is OK and nonempty
	       initializers will be diagnosed in the parser.  */
	  }
	లేకపోతే ఒకవేళ (వృక్షం_సంకేతం (వృక్షం_TYPE (decl)) != ARRAY_TYPE)
	  {
	    error ("variable %qD has initializer but incomplete type", decl);
	    initialized = అబద్ధం;
	  }
      }

  ఒకవేళ (initialized)
    {
      ఒకవేళ (current_scope == file_scope)
	వృక్షం_STATIC (decl) = 1;

      /* Tell 'pushdecl' this is an initialized decl
	 even though we don't yet have the initializer expression.
	 Also tell 'finish_decl' it may store the real initializer.  */
      DECL_INITIAL (decl) = error_mark_కణుపు;
    }

  /* If this is a function declaration, write a record describing it to the
     prototypes file (if requested).  */

  ఒకవేళ (వృక్షం_సంకేతం (decl) == FUNCTION_DECL)
    gen_aux_info_రికార్డు (decl, 0, 0, prototype_p (వృక్షం_TYPE (decl)));

  /* ANSI specifies that a tentative definition which is not merged with
     a non-tentative definition behaves exactly like a definition with an
     initializer equal to zero.  (Section 3.7.2)

     -fno-common gives strict ANSI behavior, though this tends to break
     a large body of code that grew up without this rule.

     Thread-local variables are never common, since there's no entrenched
     body of code to break, and it allows more efficient variable references
     in the presence of dynamic linking.  */

  ఒకవేళ (VAR_P (decl)
      && !initialized
      && వృక్షం_ప్రజా (decl)
      && !DECL_THREAD_LOCAL_P (decl)
      && !flag_no_common)
    DECL_COMMON (decl) = 1;

  /* Set attributes here so if duplicate decl, will have proper attributes.  */
  c_decl_లక్షణాలు (&decl, లక్షణాలు, 0);

  /* Handle gnu_inline attribute.  */
  ఒకవేళ (declspecs->inline_p
      && !flag_gnu89_inline
      && వృక్షం_సంకేతం (decl) == FUNCTION_DECL
      && (lookup_attribute ("gnu_inline", DECL_లక్షణాలు (decl))
	  || current_function_decl))
    {
      ఒకవేళ (declspecs->storage_class == csc_auto && current_scope != file_scope)
	;
      లేకపోతే ఒకవేళ (declspecs->storage_class != csc_static)
	DECL_EXTERNAL (decl) = !DECL_EXTERNAL (decl);
    }

  ఒకవేళ (వృక్షం_సంకేతం (decl) == FUNCTION_DECL
      && DECL_DECLARED_INLINE_P (decl)
      && DECL_UNINLINABLE (decl)
      && lookup_attribute ("noinline", DECL_లక్షణాలు (decl)))
    {
      auto_urlify_లక్షణాలు sentinel;
      warning (OPT_Wattributes, "inline function %q+D given attribute %qs",
	       decl, "noinline");
    }

  /* C99 6.7.4p3: An inline definition of a function with external
     linkage shall not contain a definition of a modifiable object
     with static storage duration...  */
  ఒకవేళ (VAR_P (decl)
      && current_scope != file_scope
      && వృక్షం_STATIC (decl)
      && !వృక్షం_READONLY (decl)
      && DECL_DECLARED_INLINE_P (current_function_decl)
      && DECL_EXTERNAL (current_function_decl))
    రికార్డు_inline_static (ఆదానం_location, current_function_decl,
			  decl, csi_modifiable);

  ఒకవేళ (c_dialect_objc ()
      && VAR_OR_FUNCTION_DECL_P (decl))
      objc_check_global_decl (decl);

  /* To enable versions to be created across TU's we mark and mangle all
     non-default versioned functions.  */
  ఒకవేళ (వృక్షం_సంకేతం (decl) == FUNCTION_DECL
      && !లక్ష్యం_HAS_FMV_లక్ష్యం_ATTRIBUTE
      && get_లక్ష్యం_సంస్కరణ (decl).is_valid ())
    {
      maybe_mark_function_versioned (decl);
      ఒకవేళ (current_scope != file_scope)
	error ("versioned declarations are only allowed at file scope");
    }

  /* Add this decl to the current scope.
     TEM may equal DECL or it may be a previous decl of the same name.  */
  ఒకవేళ (do_నెట్టు)
    {
      tem = pushdecl (decl);

      ఒకవేళ (initialized && DECL_EXTERNAL (tem))
	{
	  DECL_EXTERNAL (tem) = 0;
	  వృక్షం_STATIC (tem) = 1;
	}

      తిరిగి tem;
    }
  లేకపోతే
    తిరిగి decl;
}

/* Subroutine of finish_decl. TYPE is the type of an uninitialized object
   DECL or the non-array element type if DECL is an uninitialized array.
   If that type has a const member, diagnose this. */

స్థిర శూన్య
diagnose_uninitialized_cst_member (వృక్షం decl, వృక్షం type)
{
  వృక్షం క్షేత్రం_2;
  కొరకు (క్షేత్రం_2 = TYPE_FIELDS (type); క్షేత్రం_2; క్షేత్రం_2 = వృక్షం_CHAIN (క్షేత్రం_2))
    {
      వృక్షం క్షేత్రం_type;
      ఒకవేళ (వృక్షం_సంకేతం (క్షేత్రం_2) != క్షేత్రం_DECL)
	కొనసాగు;
      క్షేత్రం_type = strip_array_types (వృక్షం_TYPE (క్షేత్రం_2));

      ఒకవేళ (TYPE_QUALS (క్షేత్రం_type) & TYPE_QUAL_CONST)
      	{
	  auto_diagnostic_సమూహం d;
	  ఒకవేళ (warning_at (DECL_ఆధారం_LOCATION (decl), OPT_Wc___compat,
			  "uninitialized const member in %qT is invalid in C++",
			  strip_array_types (వృక్షం_TYPE (decl))))
	    inform (DECL_ఆధారం_LOCATION (క్షేత్రం_2), "%qD should be initialized", క్షేత్రం_2);
	}

      ఒకవేళ (రికార్డు_OR_UNION_TYPE_P (క్షేత్రం_type))
	diagnose_uninitialized_cst_member (decl, క్షేత్రం_type);
    }
}

/* Finish processing of a declaration;
   install its initial value.
   If ORIGTYPE is not NULL_TREE, it is the original type of INIT.
   If the length of an array type is not known before,
   it must be determined now, from the initial value, or it is an error.

   INIT_LOC is the location of the initial value.  */

శూన్య
ముగింపు_decl (వృక్షం decl, location_t init_loc, వృక్షం init,
	     వృక్షం origtype, వృక్షం asmspec_వృక్షం)
{
  వృక్షం type;
  తార్కిక was_incomplete = (DECL_కొలత (decl) == NULL_వృక్షం);
  స్థిరరాశి అక్షరం *asmspec = 0;

  /* If a name was specified, get the string.  */
  ఒకవేళ (VAR_OR_FUNCTION_DECL_P (decl)
      && DECL_FILE_SCOPE_P (decl))
    asmspec_వృక్షం = maybe_apply_renaming_pragma (decl, asmspec_వృక్షం);
  ఒకవేళ (asmspec_వృక్షం)
    asmspec = వృక్షం_STRING_సూచిక (asmspec_వృక్షం);

  ఒకవేళ (VAR_P (decl)
      && వృక్షం_STATIC (decl)
      && global_bindings_p ())
    /* So decl is a global variable. Record the types it uses
       so that we can decide later to emit debug info for them.  */
    రికార్డు_types_వాడిన_by_current_var_decl (decl);

  /* If `start_decl' didn't like having an initialization, ignore it now.  */
  ఒకవేళ (init != NULL_వృక్షం && DECL_INITIAL (decl) == NULL_వృక్షం)
    init = NULL_వృక్షం;

  /* Don't crash if parm is initialized.  */
  ఒకవేళ (వృక్షం_సంకేతం (decl) == PARM_DECL)
    init = NULL_వృక్షం;

  ఒకవేళ (init)
    store_init_విలువ (init_loc, decl, init, origtype);

  ఒకవేళ (c_dialect_objc () && (VAR_OR_FUNCTION_DECL_P (decl)
			    || వృక్షం_సంకేతం (decl) == క్షేత్రం_DECL))
    objc_check_decl (decl);

  type = వృక్షం_TYPE (decl);

  /* Deduce size of array from initialization, if not already known.
     This is only needed for an initialization in the current scope;
     it must not be done for a file-scope initialization of a
     declaration with external linkage, redeclared in an inner scope
     with the outer declaration shadowed in an intermediate scope.  */
  ఒకవేళ (వృక్షం_సంకేతం (type) == ARRAY_TYPE
      && TYPE_DOMAIN (type) == NULL_వృక్షం
      && వృక్షం_సంకేతం (decl) != TYPE_DECL
      && !(వృక్షం_ప్రజా (decl) && current_scope != file_scope))
    {
      తార్కిక do_default
	= !వృక్షం_STATIC (decl) && !DECL_EXTERNAL (decl);
      పూర్ణాంకం failure
	= complete_array_type (&వృక్షం_TYPE (decl), DECL_INITIAL (decl),
			       do_default);

      /* Get the completed type made by complete_array_type.  */
      type = వృక్షం_TYPE (decl);

      ఎంపిక (failure)
	{
	స్థితి 1:
	  error ("initializer fails to determine size of %q+D", decl);
	  ఆపు;

	స్థితి 2:
	  ఒకవేళ (do_default)
	    error ("array size missing in %q+D", decl);
	  లేకపోతే ఒకవేళ (!వృక్షం_ప్రజా (decl))
	    pedwarn_c23 (DECL_ఆధారం_LOCATION (decl), OPT_Wpedantic,
			 "array size missing in %q+D", decl);
	  ఆపు;

	స్థితి 3:
	  error ("zero or negative size array %q+D", decl);
	  ఆపు;

	స్థితి 0:
	  /* For global variables, update the copy of the type that
	     exists in the binding.  */
	  ఒకవేళ (వృక్షం_ప్రజా (decl))
	    {
	      నిర్మాణం c_binding *b_ext = I_చిహ్నం_BINDING (DECL_NAME (decl));
	      అయితే (b_ext && !B_లోపల_EXTERNAL_SCOPE (b_ext))
		b_ext = b_ext->shadowed;
	      ఒకవేళ (b_ext && వృక్షం_సంకేతం (decl) == వృక్షం_సంకేతం (b_ext->decl))
		{
		  ఒకవేళ (b_ext->u.type && comptypes (b_ext->u.type, type))
		    b_ext->u.type = సంయుక్త_type (b_ext->u.type, type);
		  లేకపోతే
		    b_ext->u.type = type;
		}
	    }
	  ఆపు;

	అప్రమేయ:
	  gcc_unreachable ();
	}

      ఒకవేళ (DECL_INITIAL (decl) && DECL_INITIAL (decl) != error_mark_కణుపు)
	వృక్షం_TYPE (DECL_INITIAL (decl)) = type;

      relayout_decl (decl);
    }

  /* Look for braced array initializers for character arrays and
     recursively convert them into STRING_CSTs.  */
  ఒకవేళ (వృక్షం init = DECL_INITIAL (decl))
    DECL_INITIAL (decl) = braced_lists_గమ్యం_అక్షరశ్రేణులు (type, init);

  ఒకవేళ (VAR_P (decl))
    {
      ఒకవేళ (init && వృక్షం_సంకేతం (init) == CONSTRUCTOR)
	కూడు_flexible_array_elts_గమ్యం_కొలత (decl, init);

      complete_flexible_array_elts (DECL_INITIAL (decl));

      ఒకవేళ (is_global_var (decl))
	{
	  type_context_రకం context = (DECL_THREAD_LOCAL_P (decl)
				       ? TCTX_THREAD_STORAGE
				       : TCTX_STATIC_STORAGE);
	  ఒకవేళ (!verify_type_context (ఆదానం_location, context, వృక్షం_TYPE (decl)))
	    వృక్షం_TYPE (decl) = error_mark_కణుపు;
	}

      ఒకవేళ (DECL_కొలత (decl) == NULL_వృక్షం && వృక్షం_TYPE (decl) != error_mark_కణుపు
	  && COMPLETE_TYPE_P (వృక్షం_TYPE (decl)))
	layout_decl (decl, 0);

      ఒకవేళ (DECL_కొలత (decl) == NULL_వృక్షం
	  /* Don't give an error if we already gave one earlier.  */
	  && వృక్షం_TYPE (decl) != error_mark_కణుపు
	  && (వృక్షం_STATIC (decl)
	      /* A static variable with an incomplete type
		 is an error if it is initialized.
		 Also if it is not file scope.
		 Also if it is thread-local (in C23).
		 Otherwise, let it through, but if it is not `extern'
		 then it may cause an error message later.  */
	      ? (DECL_INITIAL (decl) != NULL_వృక్షం
		 || !DECL_FILE_SCOPE_P (decl)
		 || (flag_isoc23 && DECL_THREAD_LOCAL_P (decl)))
	      /* An automatic variable with an incomplete type
		 is an error.  */
	      : !DECL_EXTERNAL (decl)))
	 {
	   error ("storage size of %q+D isn%'t known", decl);
	   వృక్షం_TYPE (decl) = error_mark_కణుపు;
	 }

      ఒకవేళ ((రికార్డు_OR_UNION_TYPE_P (వృక్షం_TYPE (decl))
	  || వృక్షం_సంకేతం (వృక్షం_TYPE (decl)) == ENUMERAL_TYPE)
	  && DECL_కొలత (decl) == NULL_వృక్షం
	  && వృక్షం_STATIC (decl))
	incomplete_రికార్డు_decls.సురక్షిత_నెట్టు (decl);

      ఒకవేళ (is_global_var (decl)
	  && DECL_కొలత (decl) != NULL_వృక్షం
	  && వృక్షం_TYPE (decl) != error_mark_కణుపు)
	{
	  ఒకవేళ (వృక్షం_సంకేతం (DECL_కొలత (decl)) == INTEGER_CST)
	    constant_వ్యక్తీకరణ_warning (DECL_కొలత (decl));
	  లేకపోతే
	    {
	      error ("storage size of %q+D isn%'t constant", decl);
	      వృక్షం_TYPE (decl) = error_mark_కణుపు;
	    }
	}

      ఒకవేళ (వృక్షం_వాడిన (type))
	{
	  వృక్షం_వాడిన (decl) = 1;
	  DECL_READ_P (decl) = 1;
	}
    }

  /* If this is a function and an assembler name is specified, reset DECL_RTL
     so we can give it its new name.  Also, update builtin_decl if it
     was a normal built-in.  */
  ఒకవేళ (వృక్షం_సంకేతం (decl) == FUNCTION_DECL && asmspec)
    {
      ఒకవేళ (DECL_BUILT_లోపల_CLASS (decl) == BUILT_లోపల_సాధారణ)
	సమితి_builtin_user_assembler_name (decl, asmspec);
      సమితి_user_assembler_name (decl, asmspec);
    }

  /* If #pragma weak was used, mark the decl weak now.  */
  maybe_apply_pragma_weak (decl);

  /* Output the assembler code and/or RTL code for variables and functions,
     unless the type is an undefined structure or union.
     If not, it will get done when the type is completed.  */

  ఒకవేళ (VAR_OR_FUNCTION_DECL_P (decl))
    {
      /* Determine the ELF visibility.  */
      ఒకవేళ (వృక్షం_ప్రజా (decl))
	c_determine_visibility (decl);

      /* This is a no-op in c-lang.cc or something real in objc-act.cc.  */
      ఒకవేళ (c_dialect_objc ())
	objc_check_decl (decl);

      ఒకవేళ (asmspec)
	{
	  /* If this is not a static variable, issue a warning.
	     It doesn't make any sense to give an ASMSPEC for an
	     ordinary, non-register local variable.  Historically,
	     GCC has accepted -- but ignored -- the ASMSPEC in
	     this case.  */
	  ఒకవేళ (!DECL_FILE_SCOPE_P (decl)
	      && VAR_P (decl)
	      && !C_DECL_రిజిస్టరు (decl)
	      && !వృక్షం_STATIC (decl))
	    warning (0, "ignoring %<asm%> specifier for non-static local "
		     "variable %q+D", decl);
	  లేకపోతే
	    సమితి_user_assembler_name (decl, asmspec);
	}

      ఒకవేళ (DECL_FILE_SCOPE_P (decl))
	{
	  ఒకవేళ (DECL_INITIAL (decl) == NULL_వృక్షం
	      || DECL_INITIAL (decl) == error_mark_కణుపు)
	    /* Don't output anything
	       when a tentative file-scope definition is seen.
	       But at end of compilation, do output code for them.  */
	    DECL_DEFER_OUTPUT (decl) = 1;
	  ఒకవేళ (asmspec && VAR_P (decl) && C_DECL_రిజిస్టరు (decl))
	    DECL_HARD_రిజిస్టరు (decl) = 1;
	  rest_యొక్క_decl_compilation (decl, నిజం, 0);

	  ఒకవేళ (వృక్షం_సంకేతం (decl) == FUNCTION_DECL)
	    {
	      వృక్షం parms = DECL_ARGUMENTS (decl);
	      స్థిరరాశి తార్కిక builtin = fndecl_built_లోపల_p (decl);
	      ఒకవేళ (వృక్షం access = build_attr_access_from_parms (parms, !builtin))
		decl_లక్షణాలు (&decl, access, 0);
	    }
	}
      లేకపోతే
	{
	  /* In conjunction with an ASMSPEC, the `register'
	     keyword indicates that we should place the variable
	     in a particular register.  */
	  ఒకవేళ (asmspec && C_DECL_రిజిస్టరు (decl))
	    {
	      DECL_HARD_రిజిస్టరు (decl) = 1;
	      /* This cannot be done for a structure with volatile
		 fields, on which DECL_REGISTER will have been
		 reset.  */
	      ఒకవేళ (!DECL_రిజిస్టరు (decl))
		error ("cannot put object with volatile field into register");
	    }

	  ఒకవేళ (వృక్షం_సంకేతం (decl) != FUNCTION_DECL)
	    {
	      /* If we're building a variable sized type, and we might be
		 reachable other than via the top of the current binding
		 level, then create a new BIND_EXPR so that we deallocate
		 the object at the right time.  */
	      /* Note that DECL_SIZE can be null due to errors.  */
	      ఒకవేళ (DECL_కొలత (decl)
		  && !వృక్షం_CONSTANT (DECL_కొలత (decl))
		  && STATEMENT_LIST_HAS_LABEL (cur_stmt_list))
		{
		  వృక్షం bind;
		  bind = build3 (BIND_సమాసం, void_type_కణుపు, ఖాళీ, ఖాళీ, ఖాళీ);
		  వృక్షం_SIDE_EFFECTS (bind) = 1;
		  కూడు_stmt (bind);
		  BIND_సమాసం_BODY (bind) = నెట్టు_stmt_list ();
		}
	      కూడు_stmt (build_stmt (DECL_ఆధారం_LOCATION (decl),
				    DECL_సమాసం, decl));
	    }
	}


      ఒకవేళ (!DECL_FILE_SCOPE_P (decl))
	{
	  /* Recompute the RTL of a local array now
	     if it used to be an incomplete type.  */
	  ఒకవేళ (was_incomplete && !is_global_var (decl))
	    {
	      /* If we used it already as memory, it must stay in memory.  */
	      వృక్షం_ADDRESSABLE (decl) = వృక్షం_వాడిన (decl);
	      /* If it's still incomplete now, no init will save it.  */
	      ఒకవేళ (DECL_కొలత (decl) == NULL_వృక్షం)
		DECL_INITIAL (decl) = NULL_వృక్షం;
	    }
	}
    }

  ఒకవేళ (వృక్షం_సంకేతం (decl) == TYPE_DECL)
    {
      ఒకవేళ (!DECL_FILE_SCOPE_P (decl)
	  && c_type_variably_modified_p (వృక్షం_TYPE (decl)))
	కూడు_stmt (build_stmt (DECL_ఆధారం_LOCATION (decl), DECL_సమాసం, decl));

      rest_యొక్క_decl_compilation (decl, DECL_FILE_SCOPE_P (decl), 0);
    }

  /* Install a cleanup (aka destructor) if one was given.  */
  ఒకవేళ (VAR_P (decl) && !వృక్షం_STATIC (decl))
    {
      వృక్షం attr = lookup_attribute ("cleanup", DECL_లక్షణాలు (decl));
      ఒకవేళ (attr)
	{
	  వృక్షం cleanup_id = వృక్షం_విలువ (వృక్షం_విలువ (attr));
	  వృక్షం cleanup_decl = lookup_name (cleanup_id);
	  వృక్షం cleanup;
	  vec<వృక్షం, va_gc> *v;

	  /* Build "cleanup(&decl)" for the destructor.  */
	  cleanup = build_unary_op (ఆదానం_location, ADDR_సమాసం, decl, అబద్ధం);
	  vec_alloc (v, 1);
	  v->శీఘ్ర_నెట్టు (cleanup);
	  cleanup = c_build_function_call_vec (DECL_ఆధారం_LOCATION (decl),
					       vNULL, cleanup_decl, v, ఖాళీ);
	  vec_free (v);

	  /* Don't warn about decl unused; the cleanup uses it.  */
	  వృక్షం_వాడిన (decl) = 1;
	  వృక్షం_వాడిన (cleanup_decl) = 1;
	  DECL_READ_P (decl) = 1;

	  నెట్టు_cleanup (decl, cleanup, అబద్ధం);
	}
    }

  ఒకవేళ (warn_cxx_compat
      && VAR_P (decl)
      && !DECL_EXTERNAL (decl)
      && DECL_INITIAL (decl) == NULL_వృక్షం)
    {
      type = strip_array_types (type);
      ఒకవేళ (వృక్షం_READONLY (decl))
	warning_at (DECL_ఆధారం_LOCATION (decl), OPT_Wc___compat,
		    "uninitialized %<const %D%> is invalid in C++", decl);
      లేకపోతే ఒకవేళ (రికార్డు_OR_UNION_TYPE_P (type)
	       && C_TYPE_FIELDS_READONLY (type))
	diagnose_uninitialized_cst_member (decl, type);
    }

  ఒకవేళ (flag_openmp
      && VAR_P (decl)
      && lookup_attribute ("omp declare target implicit",
			   DECL_లక్షణాలు (decl)))
    {
      DECL_లక్షణాలు (decl)
	= remove_attribute ("omp declare target implicit",
			    DECL_లక్షణాలు (decl));
      ఒకవేళ (!omp_mappable_type (వృక్షం_TYPE (decl)))
	error ("%q+D in declare target directive does not have mappable type",
	       decl);
      లేకపోతే ఒకవేళ (!lookup_attribute ("omp declare target",
				  DECL_లక్షణాలు (decl))
	       && !lookup_attribute ("omp declare target link",
				     DECL_లక్షణాలు (decl)))
	{
	  DECL_లక్షణాలు (decl)
	    = వృక్షం_cons (get_identifier ("omp declare target"),
			 NULL_వృక్షం, DECL_లక్షణాలు (decl));
	    symtab_కణుపు *కణుపు = symtab_కణుపు::get (decl);
	    ఒకవేళ (కణుపు != ఖాళీ)
	      {
		కణుపు->offloadable = 1;
		ఒకవేళ (ENABLE_OFFLOADING)
		  {
		    g->have_offload = నిజం;
		    ఒకవేళ (is_a <varpool_కణుపు *> (కణుపు))
		      vec_సురక్షిత_నెట్టు (offload_vars, decl);
		  }
	      }
	}
    }

  /* This is the last point we can lower alignment so give the target the
     chance to do so.  */
  ఒకవేళ (VAR_P (decl)
      && !is_global_var (decl)
      && !DECL_HARD_రిజిస్టరు (decl))
    targetm.క్రింది_local_decl_alignment (decl);

  invoke_plugin_callbacks (PLUGIN_ముగింపు_DECL, decl);
}

/* Given a parsed parameter declaration, decode it into a PARM_DECL.
   EXPR is NULL or a pointer to an expression that needs to be
   evaluated for the side effects of array size expressions in the
   parameters.  */

వృక్షం
grokparm (స్థిరరాశి నిర్మాణం c_parm *parm, వృక్షం *సమాసం)
{
  వృక్షం attrs = parm->attrs;
  వృక్షం decl = grokdeclarator (parm->declarator, parm->specs, PARM, అబద్ధం,
			      ఖాళీ, &attrs, సమాసం, ఖాళీ, DEPRECATED_సాధారణ);

  decl_లక్షణాలు (&decl, attrs, 0);

  తిరిగి decl;
}



/* Given a parsed parameter declaration, decode it into a PARM_DECL
   and push that on the current scope.  EXPR is a pointer to an
   expression that needs to be evaluated for the side effects of array
   size expressions in the parameters.  */

శూన్య
నెట్టు_parm_decl (స్థిరరాశి నిర్మాణం c_parm *parm, వృక్షం *సమాసం)
{
  వృక్షం attrs = parm->attrs;
  వృక్షం decl = grokdeclarator (parm->declarator, parm->specs, PARM, అబద్ధం, ఖాళీ,
			      &attrs, సమాసం, ఖాళీ, DEPRECATED_సాధారణ);
  ఒకవేళ (decl && DECL_P (decl))
    DECL_ఆధారం_LOCATION (decl) = parm->loc;

  decl_లక్షణాలు (&decl, attrs, 0);

  decl = pushdecl (decl);

  ముగింపు_decl (decl, ఆదానం_location, NULL_వృక్షం, NULL_వృక్షం, NULL_వృక్షం);
}

/* Mark all the parameter declarations to date as forward decls.
   Also diagnose use of this extension.  */

శూన్య
mark_forward_parm_decls (శూన్య)
{
  నిర్మాణం c_binding *b;

  ఒకవేళ (current_scope->had_forward_parm_decls)
    warning_at (ఆదానం_location, OPT_Wmultiple_parameter_fwd_decl_lists,
		"more than one list of forward declarations of parameters");
  ఒకవేళ (pedantic && !current_scope->had_forward_parm_decls)
    pedwarn (ఆదానం_location, OPT_Wpedantic,
	     "ISO C forbids forward parameter declarations");

  current_scope->had_forward_parm_decls = నిజం;

  కొరకు (b = current_scope->bindings; b; b = b->prev)
    ఒకవేళ (వృక్షం_సంకేతం (b->decl) == PARM_DECL)
      వృక్షం_ASM_WRITTEN (b->decl) = 1;
}

/* Build a COMPOUND_LITERAL_EXPR.  TYPE is the type given in the compound
   literal, which may be an incomplete array type completed by the
   initializer; INIT is a CONSTRUCTOR at LOC that initializes the compound
   literal.  NON_CONST is true if the initializers contain something
   that cannot occur in a constant expression.  If ALIGNAS_ALIGN is nonzero,
   it is the (valid) alignment for this compound literal, as specified
   with _Alignas.  SCSPECS are the storage class specifiers (C23) from the
   compound literal.  */

వృక్షం
build_compound_literal (location_t loc, వృక్షం type, వృక్షం init, తార్కిక non_const,
			గుర్తులేని పూర్ణాంకం alignas_align,
			నిర్మాణం c_declspecs *scspecs)
{
  /* We do not use start_decl here because we have a type, not a declarator;
     and do not use finish_decl because the decl should be stored inside
     the COMPOUND_LITERAL_EXPR rather than added elsewhere as a DECL_EXPR.  */
  వృక్షం decl;
  వృక్షం complit;
  వృక్షం stmt;
  తార్కిక threadp = scspecs ? scspecs->thread_p : అబద్ధం;
  గణన c_storage_class storage_class = (scspecs
					? scspecs->storage_class
					: csc_none);

  ఒకవేళ (type == error_mark_కణుపు
      || init == error_mark_కణుపు)
    తిరిగి error_mark_కణుపు;

  ఒకవేళ (current_scope == file_scope && storage_class == csc_రిజిస్టరు)
    {
      error_at (loc, "file-scope compound literal specifies %<register%>");
      storage_class = csc_none;
    }

  ఒకవేళ (current_scope != file_scope && threadp && storage_class == csc_none)
    {
      error_at (loc, "compound literal implicitly auto and declared %qs",
		scspecs->thread_gnu_p ? "__thread" : "_Thread_local");
      threadp = అబద్ధం;
    }

  decl = build_decl (loc, VAR_DECL, NULL_వృక్షం, type);
  DECL_EXTERNAL (decl) = 0;
  వృక్షం_ప్రజా (decl) = 0;
  వృక్షం_STATIC (decl) = (current_scope == file_scope
			|| storage_class == csc_static);
  DECL_CONTEXT (decl) = current_function_decl;
  వృక్షం_వాడిన (decl) = 1;
  DECL_READ_P (decl) = 1;
  DECL_ARTIFICIAL (decl) = 1;
  DECL_IGNORED_P (decl) = 1;
  C_DECL_COMPOUND_LITERAL_P (decl) = 1;
  C_DECL_DECLARED_CONSTEXPR (decl) = scspecs && scspecs->constexpr_p;
  వృక్షం_TYPE (decl) = type;
  ఒకవేళ (threadp)
    సమితి_decl_tls_model (decl, decl_default_tls_model (decl));
  ఒకవేళ (storage_class == csc_రిజిస్టరు)
    {
      C_DECL_రిజిస్టరు (decl) = 1;
      DECL_రిజిస్టరు (decl) = 1;
    }
  c_apply_type_quals_గమ్యం_decl (TYPE_QUALS (strip_array_types (type)), decl);
  ఒకవేళ (alignas_align)
    {
      సమితి_DECL_ALIGN (decl, alignas_align * బిట్లు_చొప్పున_UNIT);
      DECL_USER_ALIGN (decl) = 1;
    }
  store_init_విలువ (loc, decl, init, NULL_వృక్షం);
  ఒకవేళ (current_scope != file_scope
      && వృక్షం_STATIC (decl)
      && !వృక్షం_READONLY (decl)
      && DECL_DECLARED_INLINE_P (current_function_decl)
      && DECL_EXTERNAL (current_function_decl))
    రికార్డు_inline_static (ఆదానం_location, current_function_decl,
			  decl, csi_modifiable);

  ఒకవేళ (వృక్షం_సంకేతం (type) == ARRAY_TYPE && !COMPLETE_TYPE_P (type))
    {
      పూర్ణాంకం failure = complete_array_type (&వృక్షం_TYPE (decl),
					 DECL_INITIAL (decl), నిజం);
      /* If complete_array_type returns 3, it means that the initial value of
         the compound literal is empty.  Allow it with a pedwarn; in pre-C23
         modes, the empty initializer itself has been diagnosed if pedantic so
         does not need to be diagnosed again here.  */
      gcc_assert (failure == 0 || failure == 3);
      ఒకవేళ (failure == 3 && flag_isoc23)
	pedwarn (loc, OPT_Wpedantic,
		 "array of unknown size with empty initializer");

      type = వృక్షం_TYPE (decl);
      వృక్షం_TYPE (DECL_INITIAL (decl)) = type;
      relayout_decl (decl);
    }

  ఒకవేళ (type == error_mark_కణుపు || !COMPLETE_TYPE_P (type))
    {
      c_incomplete_type_error (loc, NULL_వృక్షం, type);
      తిరిగి error_mark_కణుపు;
    }

  ఒకవేళ ((వృక్షం_STATIC (decl) || C_DECL_DECLARED_CONSTEXPR (decl))
      && C_TYPE_VARIABLE_కొలత (type))
    error_at (loc, "storage size isn%'t constant");

  ఒకవేళ (వృక్షం_STATIC (decl)
      && !verify_type_context (loc, TCTX_STATIC_STORAGE, type))
    తిరిగి error_mark_కణుపు;

  stmt = build_stmt (DECL_ఆధారం_LOCATION (decl), DECL_సమాసం, decl);
  complit = build1 (COMPOUND_LITERAL_సమాసం, type, stmt);
  వృక్షం_SIDE_EFFECTS (complit) = 1;

  layout_decl (decl, 0);

  ఒకవేళ (వృక్షం_STATIC (decl))
    {
      /* This decl needs a name for the assembler output.  */
      సమితి_compound_literal_name (decl);
      DECL_DEFER_OUTPUT (decl) = 1;
      DECL_COMDAT (decl) = 1;
      pushdecl (decl);
      rest_యొక్క_decl_compilation (decl, 1, 0);
    }
  లేకపోతే ఒకవేళ (current_function_decl && !current_scope->parm_flag)
    pushdecl (decl);

  ఒకవేళ (non_const)
    {
      complit = build2 (C_MAYBE_CONST_సమాసం, type, ఖాళీ, complit);
      C_MAYBE_CONST_సమాసం_NON_CONST (complit) = 1;
    }

  తిరిగి complit;
}

/* Check the type of a compound literal.  Here we just check that it
   is valid for C++.  */

శూన్య
check_compound_literal_type (location_t loc, నిర్మాణం c_type_name *type_name)
{
  ఒకవేళ (warn_cxx_compat
      && (type_name->specs->typespec_రకం == ctsk_tagdef
          || type_name->specs->typespec_రకం == ctsk_tagfirstref
	  || type_name->specs->typespec_రకం == ctsk_tagfirstref_attrs))
    warning_at (loc, OPT_Wc___compat,
		"defining a type in a compound literal is invalid in C++");
}

/* Performs sanity checks on the TYPE and WIDTH of the bit-field NAME,
   replacing with appropriate values if they are invalid.  */

స్థిర శూన్య
check_bitfield_type_and_వెడల్పు (location_t loc, వృక్షం *type, వృక్షం *వెడల్పు,
			       వృక్షం orig_name)
{
  వృక్షం type_mv;
  గుర్తులేని పూర్ణాంకం max_వెడల్పు;
  గుర్తులేని HOST_WIDE_INT w;
  స్థిరరాశి అక్షరం *name = (orig_name
		      ? identifier_గమ్యం_locale (IDENTIFIER_సూచిక (orig_name))
		      : _("<anonymous>"));

  /* Detect and ignore out of range field width and process valid
     field widths.  */
  ఒకవేళ (!INTEGRAL_TYPE_P (వృక్షం_TYPE (*వెడల్పు)))
    {
      error_at (loc, "bit-field %qs width not an integer constant", name);
      *వెడల్పు = integer_one_కణుపు;
    }
  లేకపోతే
    {
      ఒకవేళ (వృక్షం_సంకేతం (*వెడల్పు) != INTEGER_CST)
	{
	  *వెడల్పు = c_fully_fold (*వెడల్పు, అబద్ధం, ఖాళీ);
	  ఒకవేళ (వృక్షం_సంకేతం (*వెడల్పు) == INTEGER_CST)
	    pedwarn (loc, OPT_Wpedantic,
		     "bit-field %qs width not an integer constant expression",
		     name);
	}
      ఒకవేళ (వృక్షం_సంకేతం (*వెడల్పు) != INTEGER_CST)
	{
	  error_at (loc, "bit-field %qs width not an integer constant", name);
	  *వెడల్పు = integer_one_కణుపు;
	}
      constant_వ్యక్తీకరణ_warning (*వెడల్పు);
      ఒకవేళ (వృక్షం_int_cst_sgn (*వెడల్పు) < 0)
	{
	  error_at (loc, "negative width in bit-field %qs", name);
	  *వెడల్పు = integer_one_కణుపు;
	}
      లేకపోతే ఒకవేళ (integer_zerop (*వెడల్పు) && orig_name)
	{
	  error_at (loc, "zero width for bit-field %qs", name);
	  *వెడల్పు = integer_one_కణుపు;
	}
    }

  /* Detect invalid bit-field type.  */
  ఒకవేళ (వృక్షం_సంకేతం (*type) != INTEGER_TYPE
      && వృక్షం_సంకేతం (*type) != BOOLEAN_TYPE
      && వృక్షం_సంకేతం (*type) != ENUMERAL_TYPE
      && వృక్షం_సంకేతం (*type) != BITINT_TYPE)
    {
      error_at (loc, "bit-field %qs has invalid type", name);
      *type = unsigned_type_కణుపు;
    }

  ఒకవేళ (TYPE_WARN_IF_NOT_ALIGN (*type))
    {
      error_at (loc, "cannot declare bit-field %qs with %<warn_if_not_aligned%> type",
		name);
      *type = unsigned_type_కణుపు;
    }

  type_mv = TYPE_MAIN_VARIANT (*type);
  ఒకవేళ (!లోపల_system_శీర్షిక_at (ఆదానం_location)
      && type_mv != integer_type_కణుపు
      && type_mv != unsigned_type_కణుపు
      && type_mv != boolean_type_కణుపు)
    pedwarn_c90 (loc, OPT_Wpedantic,
		 "type of bit-field %qs is a GCC extension", name);

  max_వెడల్పు = TYPE_PRECISION (*type);

  ఒకవేళ (compare_వృక్షం_int (*వెడల్పు, max_వెడల్పు) > 0)
    {
      error_at (loc, "width of %qs exceeds its type", name);
      w = max_వెడల్పు;
      *వెడల్పు = build_int_cst (integer_type_కణుపు, w);
    }
  లేకపోతే
    w = వృక్షం_గమ్యం_uhwi (*వెడల్పు);

  /* Truncation of hardbool false and true representation values is always safe:
     either the values remain different, or we'll report a problem when creating
     the narrower type.  */
  ఒకవేళ (c_hardbool_type_attr (*type))
    తిరిగి;

  ఒకవేళ (వృక్షం_సంకేతం (*type) == ENUMERAL_TYPE)
    {
      నిర్మాణం lang_type *lt = TYPE_LANG_SPECIFIC (*type);
      ఒకవేళ (!lt
	  || w < వృక్షం_int_cst_min_precision (lt->enum_min, TYPE_SIGN (*type))
	  || w < వృక్షం_int_cst_min_precision (lt->enum_max, TYPE_SIGN (*type)))
	warning_at (loc, 0, "%qs is narrower than values of its type", name);
    }
}



/* Print warning about variable length array if necessary.  */

స్థిర శూన్య
warn_variable_నిడివి_array (వృక్షం name, వృక్షం కొలత)
{
  ఒకవేళ (వృక్షం_CONSTANT (కొలత))
    {
      ఒకవేళ (name)
	pedwarn_c90 (ఆదానం_location, OPT_Wvla,
		     "ISO C90 forbids array %qE whose size "
		     "cannot be evaluated", name);
      లేకపోతే
	pedwarn_c90 (ఆదానం_location, OPT_Wvla, "ISO C90 forbids array "
		     "whose size cannot be evaluated");
    }
  లేకపోతే
    {
      ఒకవేళ (name)
	pedwarn_c90 (ఆదానం_location, OPT_Wvla,
		     "ISO C90 forbids variable length array %qE", name);
      లేకపోతే
	pedwarn_c90 (ఆదానం_location, OPT_Wvla, "ISO C90 forbids variable "
		     "length array");
    }
}

/* Returns the smallest location != UNKNOWN_LOCATION in LOCATIONS,
   considering only those c_declspec_words found in LIST, which
   must be terminated by cdw_number_of_elements.  */

స్థిర location_t
అతిచిన్న_type_quals_location (స్థిరరాశి location_t *locations,
			      స్థిరరాశి c_declspec_మాట *list)
{
  location_t loc = UNKNOWN_LOCATION;
  అయితే (*list != cdw_సంఖ్య_యొక్క_elements)
    {
      location_t newloc = locations[*list];
      ఒకవేళ (loc == UNKNOWN_LOCATION
	  || (newloc != UNKNOWN_LOCATION && newloc < loc))
	loc = newloc;
      list++;
    }

  తిరిగి loc;
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
స్థిర శూన్య
కూడు_decl_సమాసం (location_t loc, వృక్షం type, వృక్షం *సమాసం, తార్కిక సమితి_name_p)
{
  వృక్షం bind = NULL_వృక్షం;
  ఒకవేళ (సమాసం)
    {
      bind = build3 (BIND_సమాసం, void_type_కణుపు, NULL_వృక్షం, NULL_వృక్షం,
		     NULL_వృక్షం);
      వృక్షం_SIDE_EFFECTS (bind) = 1;
      BIND_సమాసం_BODY (bind) = నెట్టు_stmt_list ();
      నెట్టు_scope ();
    }

  వృక్షం decl = build_decl (loc, TYPE_DECL, NULL_వృక్షం, type);
  pushdecl (decl);
  DECL_ARTIFICIAL (decl) = 1;
  కూడు_stmt (build_stmt (DECL_ఆధారం_LOCATION (decl), DECL_సమాసం, decl));
  ఒకవేళ (సమితి_name_p)
    TYPE_NAME (type) = decl;

  ఒకవేళ (bind)
    {
      తీయి_scope ();
      BIND_సమాసం_BODY (bind) = తీయి_stmt_list (BIND_సమాసం_BODY (bind));
      ఒకవేళ (*సమాసం)
	*సమాసం = build2 (COMPOUND_సమాసం, void_type_కణుపు, *సమాసం, bind);
      లేకపోతే
	*సమాసం = bind;
    }
}


/* Add attribute "arg spec" to ATTRS corresponding to an array/VLA parameter
   declared with type TYPE.  The attribute has two arguments.  The first is
   a string that encodes the presence of the static keyword.  The second is
   the declared type of the array before adjustment, i.e. as an array type
   including the outermost bound.  */

స్థిర వృక్షం
build_arg_spec_attribute (వృక్షం type, తార్కిక static_p, వృక్షం attrs)
{
  వృక్షం vbchain = వృక్షం_cons (NULL_వృక్షం, type, NULL_వృక్షం);
  వృక్షం acsstr = static_p ? build_string (7, "static") :
			   build_string (1, "");
  వృక్షం వాదనలు = వృక్షం_cons (NULL_వృక్షం, acsstr, vbchain);
  వృక్షం name = get_identifier ("arg spec");
  తిరిగి వృక్షం_cons (name, వాదనలు, attrs);
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

స్థిర వృక్షం
grokdeclarator (స్థిరరాశి నిర్మాణం c_declarator *declarator,
		నిర్మాణం c_declspecs *declspecs,
		గణన decl_context decl_context, తార్కిక initialized, వృక్షం *వెడల్పు,
		వృక్షం *decl_attrs, వృక్షం *సమాసం, తార్కిక *సమాసం_const_operands,
		గణన deprecated_స్థితులు deprecated_state)
{
  వృక్షం type = declspecs->type;
  తార్కిక threadp = declspecs->thread_p;
  తార్కిక constexprp = declspecs->constexpr_p;
  గణన c_storage_class storage_class = declspecs->storage_class;
  పూర్ణాంకం constp;
  పూర్ణాంకం restrictp;
  పూర్ణాంకం volatilep;
  పూర్ణాంకం atomicp;
  పూర్ణాంకం type_quals = TYPE_UNQUALIFIED;
  వృక్షం name = NULL_వృక్షం;
  తార్కిక funcdef_flag = అబద్ధం;
  తార్కిక funcdef_syntax = అబద్ధం;
  తార్కిక కొలత_varies = అబద్ధం;
  తార్కిక కొలత_error = అబద్ధం;
  వృక్షం decl_attr = declspecs->decl_attr;
  పూర్ణాంకం array_ptr_quals = TYPE_UNQUALIFIED;
  వృక్షం array_ptr_attrs = NULL_వృక్షం;
  తార్కిక array_parm_static = అబద్ధం;
  తార్కిక array_parm_vla_unspec_p = అబద్ధం;
  వృక్షం returned_attrs = NULL_వృక్షం;
  వృక్షం decl_id_attrs = NULL_వృక్షం;
  తార్కిక bitfield = వెడల్పు != ఖాళీ;
  వృక్షం element_type;
  వృక్షం orig_qual_type = ఖాళీ;
  కొలత_t orig_qual_పరోక్ష = 0;
  నిర్మాణం c_arg_info *arg_info = 0;
  addr_space_t as1, as2, చిరునామా_space;
  location_t loc = UNKNOWN_LOCATION;
  వృక్షం సమాసం_dummy;
  తార్కిక సమాసం_const_operands_dummy;
  గణన c_declarator_రకం మొదటి_non_attr_రకం;
  గుర్తులేని పూర్ణాంకం alignas_align = 0;

  ఒకవేళ (type == NULL_వృక్షం)
    {
      /* This can occur for auto on a parameter in C23 mode.  Set a
	 dummy type here so subsequent code can give diagnostics for
	 this case.  */
      gcc_assert (declspecs->c23_auto_p);
      gcc_assert (decl_context == PARM);
      type = declspecs->type = integer_type_కణుపు;
    }
  ఒకవేళ (వృక్షం_సంకేతం (type) == ERROR_MARK)
    తిరిగి error_mark_కణుపు;
  ఒకవేళ (సమాసం == ఖాళీ)
    {
      సమాసం = &సమాసం_dummy;
      సమాసం_dummy = NULL_వృక్షం;
    }
  ఒకవేళ (సమాసం_const_operands == ఖాళీ)
    సమాసం_const_operands = &సమాసం_const_operands_dummy;

  ఒకవేళ (declspecs->సమాసం)
    {
      ఒకవేళ (*సమాసం)
	*సమాసం = build2 (COMPOUND_సమాసం, వృక్షం_TYPE (declspecs->సమాసం), *సమాసం,
			declspecs->సమాసం);
      లేకపోతే
	*సమాసం = declspecs->సమాసం;
    }
  *సమాసం_const_operands = declspecs->సమాసం_const_operands;

  ఒకవేళ (decl_context == FUNCDEF)
    funcdef_flag = నిజం, decl_context = సాధారణ;

  /* Look inside a declarator for the name being declared
     and get it as an IDENTIFIER_NODE, for an error message.  */
  {
    స్థిరరాశి నిర్మాణం c_declarator *decl = declarator;

    మొదటి_non_attr_రకం = cdk_attrs;
    అయితే (decl)
      ఎంపిక (decl->రకం)
	{
	స్థితి cdk_array:
	  loc = decl->id_loc;
	  /* FALL THRU.  */

	స్థితి cdk_function:
	స్థితి cdk_సూచిక:
	  funcdef_syntax = (decl->రకం == cdk_function);
	  ఒకవేళ (మొదటి_non_attr_రకం == cdk_attrs)
	    మొదటి_non_attr_రకం = decl->రకం;
	  decl = decl->declarator;
	  ఆపు;

	స్థితి cdk_attrs:
	  decl = decl->declarator;
	  ఆపు;

	స్థితి cdk_id:
	  loc = decl->id_loc;
	  ఒకవేళ (decl->u.id.id)
	    name = decl->u.id.id;
	  decl_id_attrs = decl->u.id.attrs;
	  ఒకవేళ (మొదటి_non_attr_రకం == cdk_attrs)
	    మొదటి_non_attr_రకం = decl->రకం;
	  decl = 0;
	  ఆపు;

	అప్రమేయ:
	  gcc_unreachable ();
	}
    ఒకవేళ (name == NULL_వృక్షం)
      {
	gcc_assert (decl_context == PARM
		    || decl_context == TYPENAME
		    || decl_context == GENERIC_ASSOC
		    || (decl_context == క్షేత్రం
			&& declarator->రకం == cdk_id));
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
  ఒకవేళ (declspecs->enum_type_specifier_ref_p)
    error_at (loc, "%<enum%> underlying type may not be specified here");

  /* A function definition's declarator must have the form of
     a function declarator.  */

  ఒకవేళ (funcdef_flag && !funcdef_syntax)
    తిరిగి NULL_వృక్షం;

  /* If this looks like a function definition, make it one,
     even if it occurs where parms are expected.
     Then store_parm_decls will reject it and not use it as a parm.  */
  ఒకవేళ (decl_context == సాధారణ && !funcdef_flag && current_scope->parm_flag)
    decl_context = PARM;

  ఒకవేళ (deprecated_state != UNAVAILABLE_DEPRECATED_SUPPRESS)
    {
      ఒకవేళ (declspecs->unavailable_p)
	error_unavailable_use (declspecs->type, declspecs->decl_attr);
      లేకపోతే ఒకవేళ (declspecs->deprecated_p
		&& deprecated_state != DEPRECATED_SUPPRESS)
	warn_deprecated_use (declspecs->type, declspecs->decl_attr);
    }

  ఒకవేళ ((decl_context == సాధారణ || decl_context == క్షేత్రం)
      && current_scope == file_scope
      && c_type_variably_modified_p (type))
    {
      ఒకవేళ (name)
	error_at (loc, "variably modified %qE at file scope", name);
      లేకపోతే
	error_at (loc, "variably modified field at file scope");
      type = integer_type_కణుపు;
    }

  కొలత_varies = C_TYPE_VARIABLE_కొలత (type) != 0;

  /* Diagnose defaulting to "int".  */

  ఒకవేళ (declspecs->default_int_p)
    {
      /* Issue a warning if this is an ISO C 99 program or if
	 -Wreturn-type and this is a function, or if -Wimplicit;
	 prefer the former warning since it is more explicit.  */
      ఒకవేళ ((warn_implicit_int || warn_return_type > 0 || flag_isoc99)
	  && funcdef_flag)
	warn_about_return_type = 1;
      లేకపోతే
	{
	  ఒకవేళ (name)
	    permerror_opt (loc, OPT_Wimplicit_int,
			   "type defaults to %<int%> in declaration "
			   "of %qE", name);
	  లేకపోతే
	    permerror_opt (loc, OPT_Wimplicit_int,
			   "type defaults to %<int%> in type name");
	}
    }

  /* Adjust the type if a bit-field is being declared,
     -funsigned-bitfields applied and the type is not explicitly
     "signed".  */
  ఒకవేళ (bitfield && !flag_signed_bitfields && !declspecs->explicit_signed_p
      && వృక్షం_సంకేతం (type) == INTEGER_TYPE)
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
  as1 = declspecs->చిరునామా_space;
  as2 = TYPE_ADDR_SPACE (element_type);
  చిరునామా_space = ADDR_SPACE_GENERIC_P (as1)? as2 : as1;

  ఒకవేళ (constp > 1)
    pedwarn_c90 (loc, OPT_Wpedantic, "duplicate %<const%>");
  ఒకవేళ (restrictp > 1)
    pedwarn_c90 (loc, OPT_Wpedantic, "duplicate %<restrict%>");
  ఒకవేళ (volatilep > 1)
    pedwarn_c90 (loc, OPT_Wpedantic, "duplicate %<volatile%>");
  ఒకవేళ (atomicp > 1)
    pedwarn_c90 (loc, OPT_Wpedantic, "duplicate %<_Atomic%>");

  ఒకవేళ (!ADDR_SPACE_GENERIC_P (as1) && !ADDR_SPACE_GENERIC_P (as2) && as1 != as2)
    error_at (loc, "conflicting named address spaces (%s vs %s)",
	      c_addr_space_name (as1), c_addr_space_name (as2));

  ఒకవేళ ((వృక్షం_సంకేతం (type) == ARRAY_TYPE
       || మొదటి_non_attr_రకం == cdk_array)
      && TYPE_QUALS (element_type))
    {
      orig_qual_type = type;
      type = c_build_qualified_type (type, TYPE_UNQUALIFIED);
    }
  type_quals = ((constp ? TYPE_QUAL_CONST : 0)
		| (restrictp ? TYPE_QUAL_RESTRICT : 0)
		| (volatilep ? TYPE_QUAL_VOLATILE : 0)
		| (atomicp ? TYPE_QUAL_ATOMIC : 0)
		| ENCODE_QUAL_ADDR_SPACE (చిరునామా_space));
  ఒకవేళ (type_quals != TYPE_QUALS (element_type))
    orig_qual_type = NULL_వృక్షం;

  /* Applying the _Atomic qualifier to an array type (through the use
     of typedefs or typeof) must be detected here.  If the qualifier
     is introduced later, any appearance of applying it to an array is
     actually applying it to an element of that array.  */
  ఒకవేళ (declspecs->atomic_p && వృక్షం_సంకేతం (type) == ARRAY_TYPE)
    error_at (loc, "%<_Atomic%>-qualified array type");

  /* Warn about storage classes that are invalid for certain
     kinds of declarations (parameters, typenames, etc.).  */

  ఒకవేళ (funcdef_flag
      && (threadp
	  || constexprp
	  || storage_class == csc_auto
	  || storage_class == csc_రిజిస్టరు
	  || storage_class == csc_typedef))
    {
      ఒకవేళ (storage_class == csc_auto)
	pedwarn (loc,
		 (current_scope == file_scope) ? 0 : OPT_Wpedantic,
		 "function definition declared %<auto%>");
      ఒకవేళ (storage_class == csc_రిజిస్టరు)
	error_at (loc, "function definition declared %<register%>");
      ఒకవేళ (storage_class == csc_typedef)
	error_at (loc, "function definition declared %<typedef%>");
      ఒకవేళ (threadp)
	error_at (loc, "function definition declared %qs",
		  declspecs->thread_gnu_p ? "__thread" : "_Thread_local");
      threadp = అబద్ధం;
      /* The parser ensures a constexpr function definition never
	 reaches here.  */
      gcc_assert (!constexprp);
      ఒకవేళ (storage_class == csc_auto
	  || storage_class == csc_రిజిస్టరు
	  || storage_class == csc_typedef)
	storage_class = csc_none;
    }
  లేకపోతే ఒకవేళ (decl_context != సాధారణ && (storage_class != csc_none
				      || threadp
				      || constexprp
				      || declspecs->c23_auto_p))
    {
      ఒకవేళ (decl_context == PARM
	  && storage_class == csc_రిజిస్టరు
	  && !constexprp
	  && !declspecs->c23_auto_p)
	;
      లేకపోతే
	{
	  ఎంపిక (decl_context)
	    {
	    స్థితి క్షేత్రం:
	      ఒకవేళ (name)
		error_at (loc, "storage class specified for structure "
		    	  "field %qE", name);
	      లేకపోతే
		error_at (loc, "storage class specified for structure field");
	      ఆపు;
	    స్థితి PARM:
	      ఒకవేళ (name)
		error_at (loc, "storage class specified for parameter %qE",
		    	  name);
	      లేకపోతే
		error_at (loc, "storage class specified for unnamed parameter");
	      ఆపు;
	    అప్రమేయ:
	      error_at (loc, "storage class specified for typename");
	      ఆపు;
	    }
	  storage_class = csc_none;
	  threadp = అబద్ధం;
	  constexprp = అబద్ధం;
	}
    }
  లేకపోతే ఒకవేళ (storage_class == csc_extern
	   && initialized
	   && !funcdef_flag)
    {
      /* 'extern' with initialization is invalid if not at file scope.  */
       ఒకవేళ (current_scope == file_scope)
         {
           /* It is fine to have 'extern const' when compiling at C
              and C++ intersection.  */
           ఒకవేళ (!(warn_cxx_compat && constp))
             warning_at (loc, 0, "%qE initialized and declared %<extern%>",
		 	 name);
         }
      లేకపోతే
	error_at (loc, "%qE has both %<extern%> and initializer", name);
    }
  లేకపోతే ఒకవేళ (current_scope == file_scope)
    {
      ఒకవేళ (storage_class == csc_auto)
	error_at (loc, "file-scope declaration of %qE specifies %<auto%>",
	    	  name);
      ఒకవేళ (pedantic && storage_class == csc_రిజిస్టరు)
	pedwarn (ఆదానం_location, OPT_Wpedantic,
		 "file-scope declaration of %qE specifies %<register%>", name);
    }
  లేకపోతే
    {
      ఒకవేళ (storage_class == csc_extern && funcdef_flag)
	error_at (loc, "nested function %qE declared %<extern%>", name);
      లేకపోతే ఒకవేళ (threadp && storage_class == csc_none)
	{
	  error_at (loc, "function-scope %qE implicitly auto and declared "
		    "%qs", name,
		    declspecs->thread_gnu_p ? "__thread" : "_Thread_local");
	  threadp = అబద్ధం;
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

  అయితే (declarator && declarator->రకం != cdk_id)
    {
      ఒకవేళ (type == error_mark_కణుపు)
	{
	  declarator = declarator->declarator;
	  కొనసాగు;
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

      ఒకవేళ (array_ptr_quals != TYPE_UNQUALIFIED
	  || array_ptr_attrs != NULL_వృక్షం
	  || array_parm_static)
	{
	  /* Only the innermost declarator (making a parameter be of
	     array type which is converted to pointer type)
	     may have static or type qualifiers.  */
	  error_at (loc, "static or type qualifiers in non-parameter array declarator");
	  array_ptr_quals = TYPE_UNQUALIFIED;
	  array_ptr_attrs = NULL_వృక్షం;
	  array_parm_static = అబద్ధం;
	}

      ఎంపిక (declarator->రకం)
	{
	స్థితి cdk_attrs:
	  {
	    /* A declarator with embedded attributes.  */
	    వృక్షం attrs = declarator->u.attrs;
	    స్థిరరాశి నిర్మాణం c_declarator *inner_decl;
	    పూర్ణాంకం attr_flags = 0;
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
	    అయితే (inner_decl->రకం == cdk_attrs)
	      inner_decl = inner_decl->declarator;
	    ఒకవేళ (!cxx11_attribute_p (attrs))
	      {
		ఒకవేళ (inner_decl->రకం == cdk_id)
		  attr_flags |= (పూర్ణాంకం) ATTR_FLAG_DECL_తదుపరి;
		లేకపోతే ఒకవేళ (inner_decl->రకం == cdk_function)
		  attr_flags |= (పూర్ణాంకం) ATTR_FLAG_FUNCTION_తదుపరి;
		లేకపోతే ఒకవేళ (inner_decl->రకం == cdk_array)
		  attr_flags |= (పూర్ణాంకం) ATTR_FLAG_ARRAY_తదుపరి;
	      }
	    attrs = c_warn_type_లక్షణాలు (type, attrs);
	    returned_attrs = decl_లక్షణాలు (&type,
					      chainon (returned_attrs, attrs),
					      attr_flags);
	    ఆపు;
	  }
	స్థితి cdk_array:
	  {
	    వృక్షం itype = NULL_వృక్షం;
	    వృక్షం కొలత = declarator->u.array.dimen;
	    /* The index is a signed object `sizetype' bits wide.  */
	    వృక్షం సూచీ_type = c_common_signed_type (sizetype);

	    array_ptr_quals = declarator->u.array.quals;
	    array_ptr_attrs = declarator->u.array.attrs;
	    array_parm_static = declarator->u.array.static_p;
	    array_parm_vla_unspec_p = declarator->u.array.vla_unspec_p;

	    declarator = declarator->declarator;

	    తార్కిక flexible_array_member = అబద్ధం;

	    /* Check for some types that there cannot be arrays of.  */

	    ఒకవేళ (VOID_TYPE_P (type))
	      {
		ఒకవేళ (name)
		  error_at (loc, "declaration of %qE as array of voids", name);
		లేకపోతే
		  error_at (loc, "declaration of type name as array of voids");
		type = error_mark_కణుపు;
	      }

	    ఒకవేళ (వృక్షం_సంకేతం (type) == FUNCTION_TYPE)
	      {
		ఒకవేళ (name)
		  error_at (loc, "declaration of %qE as array of functions",
		      	    name);
		లేకపోతే
		  error_at (loc, "declaration of type name as array of "
		            "functions");
		type = error_mark_కణుపు;
	      }

	    ఒకవేళ (pedantic && !లోపల_system_శీర్షిక_at (ఆదానం_location)
		&& flexible_array_type_p (type))
	      pedwarn (loc, OPT_Wpedantic,
		       "invalid use of structure with flexible array member");

	    ఒకవేళ (కొలత == error_mark_కణుపు)
	      type = error_mark_కణుపు;

	    ఒకవేళ (type == error_mark_కణుపు)
	      కొనసాగు;

	    ఒకవేళ (!verify_type_context (loc, TCTX_ARRAY_ELEMENT, type))
	      {
		type = error_mark_కణుపు;
		కొనసాగు;
	      }

	    /* If size was specified, set ITYPE to a range-type for
	       that size.  Otherwise, ITYPE remains null.  finish_decl
	       may figure it out from an initial value.  */

	    ఒకవేళ (కొలత)
	      {
		తార్కిక కొలత_maybe_const = నిజం;
		తార్కిక కొలత_int_const = (వృక్షం_సంకేతం (కొలత) == INTEGER_CST
				       && !వృక్షం_అధికప్రవాహం (కొలత));
		తార్కిక this_కొలత_varies = అబద్ధం;

		/* Strip NON_LVALUE_EXPRs since we aren't using as an
		   lvalue.  */
		STRIP_TYPE_NOPS (కొలత);

		ఒకవేళ (!INTEGRAL_TYPE_P (వృక్షం_TYPE (కొలత)))
		  {
		    ఒకవేళ (name)
		      error_at (loc, "size of array %qE has non-integer type",
				name);
		    లేకపోతే
		      error_at (loc,
				"size of unnamed array has non-integer type");
		    కొలత = integer_one_కణుపు;
		    కొలత_int_const = నిజం;
		    కొలత_error = నిజం;
		  }
		/* This can happen with enum forward declaration.  */
		లేకపోతే ఒకవేళ (!COMPLETE_TYPE_P (వృక్షం_TYPE (కొలత)))
		  {
		    ఒకవేళ (name)
		      error_at (loc, "size of array %qE has incomplete type",
				name);
		    లేకపోతే
		      error_at (loc, "size of unnamed array has incomplete "
				"type");
		    కొలత = integer_one_కణుపు;
		    కొలత_int_const = నిజం;
		    కొలత_error = నిజం;
		  }

		కొలత = c_fully_fold (కొలత, అబద్ధం, &కొలత_maybe_const);

		ఒకవేళ (pedantic && కొలత_maybe_const && integer_zerop (కొలత))
		  {
		    ఒకవేళ (name)
		      pedwarn (loc, OPT_Wpedantic,
			       "ISO C forbids zero-size array %qE", name);
		    లేకపోతే
		      pedwarn (loc, OPT_Wpedantic,
			       "ISO C forbids zero-size array");
		  }

		ఒకవేళ (వృక్షం_సంకేతం (కొలత) == INTEGER_CST && కొలత_maybe_const)
		  {
		    constant_వ్యక్తీకరణ_warning (కొలత);
		    ఒకవేళ (వృక్షం_int_cst_sgn (కొలత) < 0)
		      {
			ఒకవేళ (name)
			  error_at (loc, "size of array %qE is negative", name);
			లేకపోతే
			  error_at (loc, "size of unnamed array is negative");
			కొలత = integer_one_కణుపు;
			కొలత_int_const = నిజం;
			కొలత_error = నిజం;
		      }
		    /* Handle a size folded to an integer constant but
		       not an integer constant expression.  */
		    ఒకవేళ (!కొలత_int_const)
		      {
			/* If this is a file scope declaration of an
			   ordinary identifier, this is invalid code;
			   diagnosing it here and not subsequently
			   treating the type as variable-length avoids
			   more confusing diagnostics later.  */
			ఒకవేళ ((decl_context == సాధారణ || decl_context == క్షేత్రం)
			    && current_scope == file_scope)
			  pedwarn (ఆదానం_location, 0,
				   "variably modified %qE at file scope",
				   name);
			లేకపోతే
			  this_కొలత_varies = కొలత_varies = నిజం;
			warn_variable_నిడివి_array (name, కొలత);
		      }
		  }
		లేకపోతే ఒకవేళ ((decl_context == సాధారణ || decl_context == క్షేత్రం)
			 && current_scope == file_scope)
		  {
		    error_at (loc, "variably modified %qE at file scope", name);
		    కొలత = integer_one_కణుపు;
		  }
		లేకపోతే
		  {
		    /* Make sure the array size remains visibly
		       nonconstant even if it is (eg) a const variable
		       with known value.  */
		    this_కొలత_varies = కొలత_varies = నిజం;
		    warn_variable_నిడివి_array (name, కొలత);
		    ఒకవేళ (sanitize_flags_p (SANITIZE_VLA)
			&& current_function_decl != NULL_వృక్షం
			&& decl_context == సాధారణ)
		      {
			/* Evaluate the array size only once.  */
			కొలత = save_సమాసం (కొలత);
			కొలత = c_fully_fold (కొలత, అబద్ధం, ఖాళీ);
		        కొలత = fold_build2 (COMPOUND_సమాసం, వృక్షం_TYPE (కొలత),
					    ubsan_instrument_vla (loc, కొలత),
					    కొలత);
		      }
		  }

		ఒకవేళ (integer_zerop (కొలత) && !this_కొలత_varies)
		  {
		    /* A zero-length array cannot be represented with
		       an unsigned index type, which is what we'll
		       get with build_index_type.  Create an
		       open-ended range instead.  */
		    itype = build_సూచీ_type (NULL_వృక్షం);
		  }
		లేకపోతే
		  {
		    /* Arrange for the SAVE_EXPR on the inside of the
		       MINUS_EXPR, which allows the -1 to get folded
		       with the +1 that happens when building TYPE_SIZE.  */
		    ఒకవేళ (కొలత_varies)
		      కొలత = save_సమాసం (కొలత);
		    ఒకవేళ (this_కొలత_varies && వృక్షం_సంకేతం (కొలత) == INTEGER_CST)
		      కొలత = build2 (COMPOUND_సమాసం, వృక్షం_TYPE (కొలత),
				     integer_zero_కణుపు, కొలత);

		    /* Compute the maximum valid index, that is, size
		       - 1.  Do the calculation in index_type, so that
		       if it is a variable the computations will be
		       done in the proper mode.  */
		    itype = fold_build2_loc (loc, MINUS_సమాసం, సూచీ_type,
					     convert (సూచీ_type, కొలత),
					     convert (సూచీ_type,
						      కొలత_one_కణుపు));

		    /* The above overflows when size does not fit
		       in index_type.
		       ???  While a size of INT_MAX+1 technically shouldn't
		       cause an overflow (because we subtract 1), handling
		       this case seems like an unnecessary complication.  */
		    ఒకవేళ (వృక్షం_సంకేతం (కొలత) == INTEGER_CST
			&& !int_సరిపోతుంది_type_p (కొలత, సూచీ_type))
		      {
			ఒకవేళ (name)
			  error_at (loc, "size of array %qE is too large",
			            name);
			లేకపోతే
			  error_at (loc, "size of unnamed array is too large");
			type = error_mark_కణుపు;
			కొనసాగు;
		      }

		    itype = build_సూచీ_type (itype);
		  }
		ఒకవేళ (this_కొలత_varies)
		  {
		    ఒకవేళ (వృక్షం_SIDE_EFFECTS (కొలత))
		      {
			ఒకవేళ (*సమాసం)
			  *సమాసం = build2 (COMPOUND_సమాసం, వృక్షం_TYPE (కొలత),
					  *సమాసం, కొలత);
			లేకపోతే
			  *సమాసం = కొలత;
		      }
		    *సమాసం_const_operands &= కొలత_maybe_const;
		  }
	      }
	    లేకపోతే ఒకవేళ (decl_context == క్షేత్రం)
	      {
		ఒకవేళ (array_parm_vla_unspec_p)
		  /* Field names can in fact have function prototype
		     scope so [*] is disallowed here through making
		     the field variably modified, not through being
		     something other than a declaration with function
		     prototype scope.  */
		  కొలత_varies = నిజం;
		లేకపోతే
		  {
		    స్థిరరాశి నిర్మాణం c_declarator *t = declarator;
		    అయితే (t->రకం == cdk_attrs)
		      t = t->declarator;
		    flexible_array_member = (t->రకం == cdk_id);
		  }
		ఒకవేళ (flexible_array_member
		    && !లోపల_system_శీర్షిక_at (ఆదానం_location))
		  pedwarn_c90 (loc, OPT_Wpedantic, "ISO C90 does not "
			       "support flexible array members");

		/* ISO C99 Flexible array members are effectively
		   identical to GCC's zero-length array extension.  */
		ఒకవేళ (flexible_array_member)
		  itype = build_సూచీ_type (NULL_వృక్షం);
	      }

	    /* Complain about arrays of incomplete types.  */
	    ఒకవేళ (!COMPLETE_TYPE_P (type))
	      {
		auto_diagnostic_సమూహం d;
		error_at (loc, "array type has incomplete element type %qT",
			  type);
		/* See if we can be more helpful.  */
		ఒకవేళ (వృక్షం_సంకేతం (type) == ARRAY_TYPE)
		  {
		    ఒకవేళ (name)
		      inform (loc, "declaration of %qE as multidimensional "
			      "array must have bounds for all dimensions "
			      "except the first", name);
		    లేకపోతే
		      inform (loc, "declaration of multidimensional array "
			      "must have bounds for all dimensions except "
			      "the first");
		  }
		type = error_mark_కణుపు;
	      }
	    లేకపోతే
	    /* When itype is NULL, a shared incomplete array type is
	       returned for all array of a given type.  Elsewhere we
	       make sure we don't complete that type before copying
	       it, but here we want to make sure we don't ever
	       modify the shared type, so we gcc_assert (itype)
	       below.  */
	      {
		addr_space_t as = DECODE_QUAL_ADDR_SPACE (type_quals);
		ఒకవేళ (!ADDR_SPACE_GENERIC_P (as) && as != TYPE_ADDR_SPACE (type))
		  type = c_build_qualified_type (type,
						 ENCODE_QUAL_ADDR_SPACE (as));
		ఒకవేళ (array_parm_vla_unspec_p)
		  type = c_build_array_type_unspecified (type);
		/* The GCC extension for zero-length arrays differs from
		   ISO flexible array members in that sizeof yields
		   zero.  */
		లేకపోతే ఒకవేళ (కొలత && integer_zerop (కొలత))
		  type = c_build_array_type_zero_కొలత (type);
		లేకపోతే
		  type = c_build_array_type (type, itype);

		ఒకవేళ (!valid_array_కొలత_p (loc, type, name))
		  type = error_mark_కణుపు;
	      }

	    ఒకవేళ (array_parm_vla_unspec_p)
	      {
		/* C99 6.7.5.2p4 */
		ఒకవేళ (decl_context == TYPENAME)
		  warning (0, "%<[*]%> not in a declaration");
		లేకపోతే ఒకవేళ (decl_context != GENERIC_ASSOC
			 && decl_context != PARM
			 && decl_context != క్షేత్రం)
		  {
		    error ("%<[*]%> not allowed in other than function prototype scope "
			   "or generic association");
		    type = error_mark_కణుపు;
		  }
		కొలత_varies = నిజం;
	      }


	    gcc_assert (type == error_mark_కణుపు
			|| flexible_array_member
			   == flexible_array_member_type_p (type));

	    ఒకవేళ (decl_context != PARM
		&& (array_ptr_quals != TYPE_UNQUALIFIED
		    || array_ptr_attrs != NULL_వృక్షం
		    || array_parm_static))
	      {
		error_at (loc, "static or type qualifiers in non-parameter "
			  "array declarator");
		array_ptr_quals = TYPE_UNQUALIFIED;
		array_ptr_attrs = NULL_వృక్షం;
		array_parm_static = అబద్ధం;
	      }
	    orig_qual_పరోక్ష++;
	    ఆపు;
	  }
	స్థితి cdk_function:
	  {
	    /* Say it's a definition only for the declarator closest
	       to the identifier, apart possibly from some
	       attributes.  */
	    తార్కిక really_funcdef = అబద్ధం;
	    వృక్షం arg_types;
	    orig_qual_type = NULL_వృక్షం;
	    ఒకవేళ (funcdef_flag)
	      {
		స్థిరరాశి నిర్మాణం c_declarator *t = declarator->declarator;
		అయితే (t->రకం == cdk_attrs)
		  t = t->declarator;
		really_funcdef = (t->రకం == cdk_id);
	      }

	    /* Declaring a function type.  Make sure we have a valid
	       type for the function to return.  */
	    ఒకవేళ (type == error_mark_కణుపు)
	      కొనసాగు;

	    కొలత_varies = అబద్ధం;

	    /* Warn about some types functions can't return.  */
	    ఒకవేళ (వృక్షం_సంకేతం (type) == FUNCTION_TYPE)
	      {
		ఒకవేళ (name)
		  error_at (loc, "%qE declared as function returning a "
		      		 "function", name);
		లేకపోతే
		  error_at (loc, "type name declared as function "
			    "returning a function");
		type = integer_type_కణుపు;
	      }
	    ఒకవేళ (వృక్షం_సంకేతం (type) == ARRAY_TYPE)
	      {
		ఒకవేళ (name)
		  error_at (loc, "%qE declared as function returning an array",
		      	    name);
		లేకపోతే
		  error_at (loc, "type name declared as function returning "
		      	    "an array");
		type = integer_type_కణుపు;
	      }

	    /* Construct the function type and go to the next
	       inner layer of declarator.  */
	    arg_info = declarator->u.arg_info;
	    arg_types = grokparms (arg_info, really_funcdef);

	    /* Type qualifiers before the return type of the function
	       qualify the return type, not the function type.  */
	    ఒకవేళ (type_quals)
	      {
		స్థిరరాశి గణన c_declspec_మాట ignored_quals_list[] =
		  {
		    cdw_const, cdw_volatile, cdw_restrict, cdw_చిరునామా_space,
		    cdw_atomic, cdw_సంఖ్య_యొక్క_elements
		  };
		location_t specs_loc
		  = అతిచిన్న_type_quals_location (declspecs->locations,
						  ignored_quals_list);
		ఒకవేళ (specs_loc == UNKNOWN_LOCATION)
		  specs_loc = declspecs->locations[cdw_typedef];
		ఒకవేళ (specs_loc == UNKNOWN_LOCATION)
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
		పూర్ణాంకం quals_వాడిన = type_quals;
		ఒకవేళ (flag_isoc23)
		  quals_వాడిన = 0;
		లేకపోతే ఒకవేళ (flag_isoc11)
		  quals_వాడిన &= TYPE_QUAL_ATOMIC;
		ఒకవేళ (quals_వాడిన && VOID_TYPE_P (type) && really_funcdef)
		  pedwarn (specs_loc, 0,
			   "function definition has qualified void "
			   "return type");
		లేకపోతే
		  warning_at (specs_loc, OPT_Wignored_qualifiers,
			      "type qualifiers ignored on function "
			      "return type");

		/* Ensure an error for restrict on invalid types; the
		   DR#423 resolution is not entirely clear about
		   this.  */
		ఒకవేళ (flag_isoc11
		    && (type_quals & TYPE_QUAL_RESTRICT)
		    && (!సూచిక_TYPE_P (type)
			|| !C_TYPE_OBJECT_OR_INCOMPLETE_P (వృక్షం_TYPE (type))))
		  error_at (loc, "invalid use of %<restrict%>");
		type = c_build_qualified_type (type, quals_వాడిన);
	      }
	    type_quals = TYPE_UNQUALIFIED;

	    type = c_build_function_type (type, arg_types,
					  arg_info->no_named_వాదనలు_stdarg_p);
	    declarator = declarator->declarator;

	    /* Set the TYPE_CONTEXTs for each tagged type which is local to
	       the formal parameter list of this FUNCTION_TYPE to point to
	       the FUNCTION_TYPE node itself.  */
	    {
	      c_arg_ట్యాగ్ *ట్యాగ్;
	      గుర్తులేని ix;

	      FOR_EACH_VEC_సురక్షిత_ELT_తిరగేయి (arg_info->ట్యాగులు, ix, ట్యాగ్)
		TYPE_CONTEXT (ట్యాగ్->type) = type;
	    }
	    ఆపు;
	  }
	స్థితి cdk_సూచిక:
	  {
	    /* Merge any constancy or volatility into the target type
	       for the pointer.  */
	    ఒకవేళ ((type_quals & TYPE_QUAL_ATOMIC)
		&& వృక్షం_సంకేతం (type) == FUNCTION_TYPE)
	      {
		error_at (loc,
			  "%<_Atomic%>-qualified function type");
		type_quals &= ~TYPE_QUAL_ATOMIC;
	      }
	    లేకపోతే ఒకవేళ (pedantic && వృక్షం_సంకేతం (type) == FUNCTION_TYPE
		     && type_quals)
	      pedwarn (loc, OPT_Wpedantic,
		       "ISO C forbids qualified function types");
	    ఒకవేళ (type_quals)
	      type = c_build_qualified_type (type, type_quals, orig_qual_type,
					     orig_qual_పరోక్ష);
	    orig_qual_type = NULL_వృక్షం;
	    కొలత_varies = అబద్ధం;

	    /* When the pointed-to type involves components of variable size,
	       care must be taken to ensure that the size evaluation code is
	       emitted early enough to dominate all the possible later uses
	       and late enough for the variables on which it depends to have
	       been assigned.

	       This is expected to happen automatically when the pointed-to
	       type has a name/declaration of it's own, but special attention
	       is required if the type is anonymous. */
	    ఒకవేళ (!TYPE_NAME (type) && c_type_variably_modified_p (type))
	      {
		తార్కిక bind_p = decl_context == TYPENAME
			      || decl_context == క్షేత్రం
			      || decl_context == PARM;
		కూడు_decl_సమాసం (loc, type, bind_p ? సమాసం : ఖాళీ, నిజం);
	      }

	    type = c_build_సూచిక_type (type);

	    /* Process type qualifiers (such as const or volatile)
	       that were given inside the `*'.  */
	    type_quals = declarator->u.సూచిక_quals;

	    declarator = declarator->declarator;
	    ఆపు;
	  }
	అప్రమేయ:
	  gcc_unreachable ();
	}
    }
  *decl_attrs = chainon (returned_attrs, *decl_attrs);
  *decl_attrs = chainon (decl_id_attrs, *decl_attrs);

  /* Now TYPE has the actual type, apart from any qualifiers in
     TYPE_QUALS.  */

  /* Warn about address space used for things other than static memory or
     pointers.  */
  చిరునామా_space = DECODE_QUAL_ADDR_SPACE (type_quals);
  ఒకవేళ (!ADDR_SPACE_GENERIC_P (చిరునామా_space))
    {
      ఒకవేళ (decl_context == సాధారణ)
	{
	  ఎంపిక (storage_class)
	    {
	    స్థితి csc_auto:
	      error ("%qs combined with %<auto%> qualifier for %qE",
		     c_addr_space_name (చిరునామా_space), name);
	      ఆపు;
	    స్థితి csc_రిజిస్టరు:
	      error ("%qs combined with %<register%> qualifier for %qE",
		     c_addr_space_name (చిరునామా_space), name);
	      ఆపు;
	    స్థితి csc_none:
	      ఒకవేళ (current_function_scope)
		{
		  error ("%qs specified for auto variable %qE",
			 c_addr_space_name (చిరునామా_space), name);
		  ఆపు;
		}
	      ఆపు;
	    స్థితి csc_static:
	    స్థితి csc_extern:
	    స్థితి csc_typedef:
	      ఆపు;
	    అప్రమేయ:
	      gcc_unreachable ();
	    }
	}
      లేకపోతే ఒకవేళ (decl_context == PARM && వృక్షం_సంకేతం (type) != ARRAY_TYPE)
	{
	  ఒకవేళ (name)
	    error ("%qs specified for parameter %qE",
		   c_addr_space_name (చిరునామా_space), name);
	  లేకపోతే
	    error ("%qs specified for unnamed parameter",
		   c_addr_space_name (చిరునామా_space));
	}
      లేకపోతే ఒకవేళ (decl_context == క్షేత్రం)
	{
	  ఒకవేళ (name)
	    error ("%qs specified for structure field %qE",
		   c_addr_space_name (చిరునామా_space), name);
	  లేకపోతే
	    error ("%qs specified for structure field",
		   c_addr_space_name (చిరునామా_space));
	}
    }

  /* Check the type and width of a bit-field.  */
  ఒకవేళ (bitfield)
    {
      check_bitfield_type_and_వెడల్పు (loc, &type, వెడల్పు, name);
      /* C11 makes it implementation-defined (6.7.2.1#5) whether
	 atomic types are permitted for bit-fields; we have no code to
	 make bit-field accesses atomic, so disallow them.  */
      ఒకవేళ (type_quals & TYPE_QUAL_ATOMIC)
	{
	  ఒకవేళ (name)
	    error_at (loc, "bit-field %qE has atomic type", name);
	  లేకపోతే
	    error_at (loc, "bit-field has atomic type");
	  type_quals &= ~TYPE_QUAL_ATOMIC;
	}
    }

  /* Reject invalid uses of _Alignas.  */
  ఒకవేళ (declspecs->alignas_p)
    {
      ఒకవేళ (storage_class == csc_typedef)
	error_at (loc, "alignment specified for typedef %qE", name);
      లేకపోతే ఒకవేళ (storage_class == csc_రిజిస్టరు)
	error_at (loc, "alignment specified for %<register%> object %qE",
		  name);
      లేకపోతే ఒకవేళ (decl_context == PARM)
	{
	  ఒకవేళ (name)
	    error_at (loc, "alignment specified for parameter %qE", name);
	  లేకపోతే
	    error_at (loc, "alignment specified for unnamed parameter");
	}
      లేకపోతే ఒకవేళ (bitfield)
	{
	  ఒకవేళ (name)
	    error_at (loc, "alignment specified for bit-field %qE", name);
	  లేకపోతే
	    error_at (loc, "alignment specified for unnamed bit-field");
	}
      లేకపోతే ఒకవేళ (వృక్షం_సంకేతం (type) == FUNCTION_TYPE)
	error_at (loc, "alignment specified for function %qE", name);
      లేకపోతే ఒకవేళ (declspecs->align_log != -1 && TYPE_P (type))
	{
	  alignas_align = 1U << declspecs->align_log;
	  ఒకవేళ (alignas_align < min_align_యొక్క_type (type))
	    {
	      ఒకవేళ (name)
		error_at (loc, "%<_Alignas%> specifiers cannot reduce "
			  "alignment of %qE", name);
	      లేకపోతే
		error_at (loc, "%<_Alignas%> specifiers cannot reduce "
			  "alignment of unnamed field");
	      alignas_align = 0;
	    }
	}
    }

  /* If this is declaring a typedef name, return a TYPE_DECL.  */

  ఒకవేళ (storage_class == csc_typedef)
    {
      వృక్షం decl;
      ఒకవేళ ((type_quals & TYPE_QUAL_ATOMIC)
	  && వృక్షం_సంకేతం (type) == FUNCTION_TYPE)
	{
	  error_at (loc,
		    "%<_Atomic%>-qualified function type");
	  type_quals &= ~TYPE_QUAL_ATOMIC;
	}
      లేకపోతే ఒకవేళ (pedantic && వృక్షం_సంకేతం (type) == FUNCTION_TYPE
	       && type_quals)
	pedwarn (loc, OPT_Wpedantic,
		 "ISO C forbids qualified function types");
      ఒకవేళ (type_quals)
	type = c_build_qualified_type (type, type_quals, orig_qual_type,
				       orig_qual_పరోక్ష);
      decl = build_decl (declarator->id_loc,
			 TYPE_DECL, declarator->u.id.id, type);
      ఒకవేళ (declspecs->explicit_signed_p)
	C_TYPEDEF_EXPLICITLY_SIGNED (decl) = 1;
      ఒకవేళ (declspecs->inline_p)
	pedwarn (loc, 0,"typedef %q+D declared %<inline%>", decl);
      ఒకవేళ (declspecs->noreturn_p)
	pedwarn (loc, 0,"typedef %q+D declared %<_Noreturn%>", decl);

      ఒకవేళ (warn_cxx_compat && declarator->u.id.id != NULL_వృక్షం)
	{
	  నిర్మాణం c_binding *b = I_ట్యాగ్_BINDING (declarator->u.id.id);

	  ఒకవేళ (b != ఖాళీ
	      && b->decl != NULL_వృక్షం
	      && (B_లోపల_CURRENT_SCOPE (b)
		  || (current_scope == file_scope && B_లోపల_EXTERNAL_SCOPE (b)))
	      && TYPE_MAIN_VARIANT (b->decl) != TYPE_MAIN_VARIANT (type))
	    {
	      auto_diagnostic_సమూహం d;
	      ఒకవేళ (warning_at (declarator->id_loc, OPT_Wc___compat,
			      "using %qD as both a typedef and a tag is "
			      "invalid in C++", decl)
		  && b->locus != UNKNOWN_LOCATION)
		inform (b->locus, "originally defined here");
	    }
	}

      తిరిగి decl;
    }

  /* If this is a type name (such as, in a cast or sizeof),
     compute the type and return it now.  */

  ఒకవేళ (decl_context == TYPENAME || decl_context == GENERIC_ASSOC)
    {
      /* Note that the grammar rejects storage classes in typenames
	 and fields.  */
      gcc_assert (storage_class == csc_none && !threadp
		  && !declspecs->inline_p && !declspecs->noreturn_p);
      ఒకవేళ ((type_quals & TYPE_QUAL_ATOMIC)
	  && వృక్షం_సంకేతం (type) == FUNCTION_TYPE)
	{
	  error_at (loc,
		    "%<_Atomic%>-qualified function type");
	  type_quals &= ~TYPE_QUAL_ATOMIC;
	}
      లేకపోతే ఒకవేళ (pedantic && వృక్షం_సంకేతం (type) == FUNCTION_TYPE
	       && type_quals)
	pedwarn (loc, OPT_Wpedantic,
		 "ISO C forbids const or volatile function types");
      ఒకవేళ (type_quals)
	type = c_build_qualified_type (type, type_quals, orig_qual_type,
				       orig_qual_పరోక్ష);
      తిరిగి type;
    }

  ఒకవేళ (pedantic && decl_context == క్షేత్రం
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

  ఒకవేళ (VOID_TYPE_P (type) && decl_context != PARM
      && !((decl_context != క్షేత్రం && వృక్షం_సంకేతం (type) != FUNCTION_TYPE)
	    && (storage_class == csc_extern
		|| (current_scope == file_scope
		    && !(storage_class == csc_static
			 || storage_class == csc_రిజిస్టరు)))))
    {
      error_at (loc, "variable or field %qE declared void", name);
      type = integer_type_కణుపు;
    }

  /* Now create the decl, which may be a VAR_DECL, a PARM_DECL
     or a FUNCTION_DECL, depending on DECL_CONTEXT and TYPE.  */

  {
    వృక్షం decl;

    ఒకవేళ (decl_context == PARM)
      {
	వృక్షం promoted_type;
	తార్కిక array_parameter_p = అబద్ధం;

	/* A parameter declared as an array of T is really a pointer to T.
	   One declared as a function is really a pointer to a function.  */

	ఒకవేళ (వృక్షం_సంకేతం (type) == ARRAY_TYPE)
	  {
	    ఒకవేళ (!కొలత_error)
	      *decl_attrs = build_arg_spec_attribute (type, array_parm_static,
						      *decl_attrs);

	    /* Transfer const-ness of array into that of type pointed to.  */
	    type = వృక్షం_TYPE (type);
	    ఒకవేళ (orig_qual_type != NULL_వృక్షం)
	      {
		ఒకవేళ (orig_qual_పరోక్ష == 0)
		  orig_qual_type = వృక్షం_TYPE (orig_qual_type);
		లేకపోతే
		  orig_qual_పరోక్ష--;
	      }
	    ఒకవేళ (type_quals)
	      type = c_build_qualified_type (type, type_quals, orig_qual_type,
					     orig_qual_పరోక్ష);

	    /* The pointed-to type may need a decl expr (see above).  */
	    ఒకవేళ (!TYPE_NAME (type) && c_type_variably_modified_p (type))
	      {
		తార్కిక bind_p = decl_context == TYPENAME
			      || decl_context == క్షేత్రం
			      || decl_context == PARM;
		కూడు_decl_సమాసం (loc, type, bind_p ? సమాసం : ఖాళీ, నిజం);
	      }

	    type = c_build_సూచిక_type (type);
	    type_quals = array_ptr_quals;
	    ఒకవేళ (type_quals)
	      type = c_build_qualified_type (type, type_quals);

	    /* We don't yet implement attributes in this context.  */
	    ఒకవేళ (array_ptr_attrs != NULL_వృక్షం)
	      warning_at (loc, OPT_Wattributes,
			  "attributes in parameter array declarator ignored");

	    కొలత_varies = అబద్ధం;
	    array_parameter_p = నిజం;
	  }
	లేకపోతే ఒకవేళ (వృక్షం_సంకేతం (type) == FUNCTION_TYPE)
	  {
	    ఒకవేళ (type_quals & TYPE_QUAL_ATOMIC)
	      {
		error_at (loc,
			  "%<_Atomic%>-qualified function type");
		type_quals &= ~TYPE_QUAL_ATOMIC;
	      }
	    లేకపోతే ఒకవేళ (type_quals)
	      pedwarn (loc, OPT_Wpedantic,
		       "ISO C forbids qualified function types");
	    ఒకవేళ (type_quals)
	      type = c_build_qualified_type (type, type_quals);
	    type = c_build_సూచిక_type (type);
	    type_quals = TYPE_UNQUALIFIED;
	  }
	లేకపోతే ఒకవేళ (type_quals)
	  type = c_build_qualified_type (type, type_quals);

	decl = build_decl (declarator->id_loc,
			   PARM_DECL, declarator->u.id.id, type);
	ఒకవేళ (కొలత_varies)
	  C_DECL_VARIABLE_కొలత (decl) = 1;
	C_ARRAY_PARAMETER (decl) = array_parameter_p;

	/* Compute the type actually passed in the parmlist,
	   for the case where there is no prototype.
	   (For example, shorts and chars are passed as ints.)
	   When there is a prototype, this is overridden later.  */

	ఒకవేళ (type == error_mark_కణుపు)
	  promoted_type = type;
	లేకపోతే
	  promoted_type = c_type_promotes_గమ్యం (type);

	DECL_ARG_TYPE (decl) = promoted_type;
	ఒకవేళ (declspecs->inline_p)
	  pedwarn (loc, 0, "parameter %q+D declared %<inline%>", decl);
	ఒకవేళ (declspecs->noreturn_p)
	  pedwarn (loc, 0, "parameter %q+D declared %<_Noreturn%>", decl);
      }
    లేకపోతే ఒకవేళ (decl_context == క్షేత్రం)
      {
	/* Note that the grammar rejects storage classes in typenames
	   and fields.  */
	gcc_assert (storage_class == csc_none && !threadp
		    && !declspecs->inline_p && !declspecs->noreturn_p);

	/* Structure field.  It may not be a function.  */

	ఒకవేళ (వృక్షం_సంకేతం (type) == FUNCTION_TYPE)
	  {
	    error_at (loc, "field %qE declared as a function", name);
	    type = c_build_సూచిక_type (type);
	  }
	లేకపోతే ఒకవేళ (వృక్షం_సంకేతం (type) != ERROR_MARK
		 && !COMPLETE_OR_UNBOUND_ARRAY_TYPE_P (type))
	  {
	    ఒకవేళ (name)
	      error_at (loc, "field %qE has incomplete type", name);
	    లేకపోతే
	      error_at (loc, "unnamed field has incomplete type");
	    type = error_mark_కణుపు;
	  }
	లేకపోతే ఒకవేళ (వృక్షం_సంకేతం (type) == ARRAY_TYPE
		 && TYPE_DOMAIN (type) == NULL_వృక్షం)
	  {
	    /* We have a flexible array member through a typedef.
	       Set suitable range.  Whether this is a correct position
	       for a flexible array member will be determined elsewhere.  */
	    ఒకవేళ (!లోపల_system_శీర్షిక_at (ఆదానం_location))
	      pedwarn_c90 (loc, OPT_Wpedantic, "ISO C90 does not "
			   "support flexible array members");
	    type = build_distinct_type_copy (TYPE_MAIN_VARIANT (type));
	    TYPE_DOMAIN (type) = build_సూచీ_type (NULL_వృక్షం);
	    ఒకవేళ (orig_qual_పరోక్ష == 0)
	      orig_qual_type = NULL_వృక్షం;
	  }
	ఒకవేళ (type != error_mark_కణుపు
	    && !verify_type_context (loc, TCTX_క్షేత్రం, type))
	  type = error_mark_కణుపు;

	type = c_build_qualified_type (type, type_quals, orig_qual_type,
				       orig_qual_పరోక్ష);
	decl = build_decl (declarator->id_loc,
			   క్షేత్రం_DECL, declarator->u.id.id, type);
	DECL_NONADDRESSABLE_P (decl) = bitfield;
	ఒకవేళ (bitfield && !declarator->u.id.id)
	  DECL_PADDING_P (decl) = 1;

	ఒకవేళ (కొలత_varies)
	  C_DECL_VARIABLE_కొలత (decl) = 1;
      }
    లేకపోతే ఒకవేళ (వృక్షం_సంకేతం (type) == FUNCTION_TYPE)
      {
	ఒకవేళ (storage_class == csc_రిజిస్టరు || threadp || constexprp)
	  {
	    error_at (loc, "invalid storage class for function %qE", name);
	  }
	లేకపోతే ఒకవేళ (current_scope != file_scope)
	  {
	    /* Function declaration not at file scope.  Storage
	       classes other than `extern' are not allowed, C99
	       6.7.1p5, and `extern' makes no difference.  However,
	       GCC allows 'auto', perhaps with 'inline', to support
	       nested functions.  */
	    ఒకవేళ (storage_class == csc_auto)
		pedwarn (loc, OPT_Wpedantic,
			 "invalid storage class for function %qE", name);
	    లేకపోతే ఒకవేళ (storage_class == csc_static)
	      {
		error_at (loc, "invalid storage class for function %qE", name);
		ఒకవేళ (funcdef_flag)
		  storage_class = declspecs->storage_class = csc_none;
		లేకపోతే
		  తిరిగి NULL_వృక్షం;
	      }
	  }

	decl = build_decl (declarator->id_loc,
			   FUNCTION_DECL, declarator->u.id.id, type);
	decl = build_decl_attribute_variant (decl, decl_attr);

	ఒకవేళ (type_quals & TYPE_QUAL_ATOMIC)
	  {
	    error_at (loc,
		      "%<_Atomic%>-qualified function type");
	    type_quals &= ~TYPE_QUAL_ATOMIC;
	  }
	లేకపోతే ఒకవేళ (pedantic && type_quals && !DECL_లోపల_SYSTEM_శీర్షిక (decl))
	  pedwarn (loc, OPT_Wpedantic,
		   "ISO C forbids qualified function types");

	/* Every function declaration is an external reference
	   (DECL_EXTERNAL) except for those which are not at file
	   scope and are explicitly declared "auto".  This is
	   forbidden by standard C (C99 6.7.1p5) and is interpreted by
	   GCC to signify a forward declaration of a nested function.  */
	ఒకవేళ (storage_class == csc_auto && current_scope != file_scope)
	  DECL_EXTERNAL (decl) = 0;
	/* In C99, a function which is declared 'inline' with 'extern'
	   is not an external reference (which is confusing).  It
	   means that the later definition of the function must be output
	   in this file, C99 6.7.4p6.  In GNU C89, a function declared
	   'extern inline' is an external reference.  */
	లేకపోతే ఒకవేళ (declspecs->inline_p && storage_class != csc_static)
	  DECL_EXTERNAL (decl) = ((storage_class == csc_extern)
				  == flag_gnu89_inline);
	లేకపోతే
	  DECL_EXTERNAL (decl) = !initialized;

	/* Record absence of global scope for `static' or `auto'.  */
	వృక్షం_ప్రజా (decl)
	  = !(storage_class == csc_static || storage_class == csc_auto);

	/* For a function definition, record the argument information
	   block where store_parm_decls will look for it.  */
	ఒకవేళ (funcdef_flag)
	  current_function_arg_info = arg_info;

	ఒకవేళ (declspecs->default_int_p)
	  C_FUNCTION_IMPLICIT_INT (decl) = 1;

	/* Record presence of `inline' and `_Noreturn', if it is
	   reasonable.  */
	ఒకవేళ (flag_hosted && MAIN_NAME_P (declarator->u.id.id))
	  {
	    ఒకవేళ (declspecs->inline_p)
	      pedwarn (loc, 0, "cannot inline function %<main%>");
	    ఒకవేళ (declspecs->noreturn_p)
	      pedwarn (loc, 0, "%<main%> declared %<_Noreturn%>");
	  }
	లేకపోతే
	  {
	    ఒకవేళ (declspecs->inline_p)
	      /* Record that the function is declared `inline'.  */
	      DECL_DECLARED_INLINE_P (decl) = 1;
	    ఒకవేళ (declspecs->noreturn_p)
	      {
		ఒకవేళ (flag_isoc99)
		  pedwarn_c99 (loc, OPT_Wpedantic,
			       "ISO C99 does not support %<_Noreturn%>");
		లేకపోతే
		  pedwarn_c99 (loc, OPT_Wpedantic,
			       "ISO C90 does not support %<_Noreturn%>");
		వృక్షం_THIS_VOLATILE (decl) = 1;
	      }
	  }

	/* C99 6.2.2p7: It is invalid (compile-time undefined
	   behavior) to create an 'extern' declaration for a
	   function if there is a global declaration that is
	   'static' and the global declaration is not visible.
	   (If the static declaration _is_ currently visible,
	   the 'extern' declaration is taken to refer to that decl.) */
	ఒకవేళ (!initialized
	    && వృక్షం_ప్రజా (decl)
	    && current_scope != file_scope)
	  {
	    వృక్షం global_decl  = identifier_global_విలువ (declarator->u.id.id);
	    వృక్షం visible_decl = lookup_name (declarator->u.id.id);

	    ఒకవేళ (global_decl
		&& global_decl != visible_decl
		&& VAR_OR_FUNCTION_DECL_P (global_decl)
		&& !వృక్షం_ప్రజా (global_decl))
	      error_at (loc, "function previously declared %<static%> "
			"redeclared %<extern%>");
	  }
      }
    లేకపోతే
      {
	/* It's a variable.  */
	/* An uninitialized decl with `extern' is a reference.  */
	పూర్ణాంకం extern_ref = !initialized && storage_class == csc_extern;

	ఒకవేళ (constexprp)
	  {
	    /* The type of a constexpr variable must not be variably
	       modified, volatile, atomic or restrict qualified or
	       have a member with such a qualifier.  const
	       qualification is implicitly added, and, at file scope,
	       has internal linkage.  */
	    ఒకవేళ (c_type_variably_modified_p (type))
	      error_at (loc, "%<constexpr%> object has variably modified "
			"type");
	    ఒకవేళ (type_quals
		& (TYPE_QUAL_VOLATILE | TYPE_QUAL_RESTRICT | TYPE_QUAL_ATOMIC))
	      error_at (loc, "invalid qualifiers for %<constexpr%> object");
	    లేకపోతే
	      {
		వృక్షం type_no_array = strip_array_types (type);
		ఒకవేళ (రికార్డు_OR_UNION_TYPE_P (type_no_array)
		    && C_TYPE_FIELDS_NON_CONSTEXPR (type_no_array))
		  error_at (loc, "invalid qualifiers for field of "
			    "%<constexpr%> object");
	      }
	    type_quals |= TYPE_QUAL_CONST;
	    ఒకవేళ (current_scope == file_scope)
	      storage_class = csc_static;
	  }

	type = c_build_qualified_type (type, type_quals, orig_qual_type,
				       orig_qual_పరోక్ష);

	/* C99 6.2.2p7: It is invalid (compile-time undefined
	   behavior) to create an 'extern' declaration for a
	   variable if there is a global declaration that is
	   'static' and the global declaration is not visible.
	   (If the static declaration _is_ currently visible,
	   the 'extern' declaration is taken to refer to that decl.) */
	ఒకవేళ (extern_ref && current_scope != file_scope)
	  {
	    వృక్షం global_decl  = identifier_global_విలువ (declarator->u.id.id);
	    వృక్షం visible_decl = lookup_name (declarator->u.id.id);

	    ఒకవేళ (global_decl
		&& global_decl != visible_decl
		&& VAR_P (global_decl)
		&& !వృక్షం_ప్రజా (global_decl))
	      error_at (loc, "variable previously declared %<static%> "
			"redeclared %<extern%>");
	  }

	decl = build_decl (declarator->id_loc,
			   VAR_DECL, declarator->u.id.id, type);
	ఒకవేళ (కొలత_varies)
	  C_DECL_VARIABLE_కొలత (decl) = 1;
	ఒకవేళ (constexprp)
	  C_DECL_DECLARED_CONSTEXPR (decl) = 1;

	ఒకవేళ (declspecs->inline_p)
	  pedwarn (loc, 0, "variable %q+D declared %<inline%>", decl);
	ఒకవేళ (declspecs->noreturn_p)
	  pedwarn (loc, 0, "variable %q+D declared %<_Noreturn%>", decl);

	/* At file scope, an initialized extern declaration may follow
	   a static declaration.  In that case, DECL_EXTERNAL will be
	   reset later in start_decl.  */
	DECL_EXTERNAL (decl) = (storage_class == csc_extern);

	/* At file scope, the presence of a `static' or `register' storage
	   class specifier, or the absence of all storage class specifiers
	   makes this declaration a definition (perhaps tentative).  Also,
	   the absence of `static' makes it public.  */
	ఒకవేళ (current_scope == file_scope)
	  {
	    వృక్షం_ప్రజా (decl) = storage_class != csc_static;
	    వృక్షం_STATIC (decl) = !extern_ref;
	  }
	/* Not at file scope, only `static' makes a static definition.  */
	లేకపోతే
	  {
	    వృక్షం_STATIC (decl) = (storage_class == csc_static);
	    వృక్షం_ప్రజా (decl) = extern_ref;
	  }

	// NB: Set a tentative TLS model to avoid tls_model attribute
	// warnings due to lack of thread storage duration.  It will
	// be updated by c_decl_attributes later.
	ఒకవేళ (threadp)
	  సమితి_decl_tls_model (decl, TLS_MODEL_REAL);
      }

    ఒకవేళ ((storage_class == csc_extern
	 || (storage_class == csc_none
	     && వృక్షం_సంకేతం (type) == FUNCTION_TYPE
	     && !funcdef_flag))
	&& c_type_variably_modified_p (type))
      {
	/* C99 6.7.5.2p2 */
	ఒకవేళ (వృక్షం_సంకేతం (type) == FUNCTION_TYPE)
	  error_at (loc, "non-nested function with variably modified type");
	లేకపోతే
	  error_at (loc, "object with variably modified type must have "
	      	    "no linkage");
      }

    /* For nested functions disqualify ones taking VLAs by value
       from inlining since the middle-end cannot deal with this.
       ???  We should arrange for those to be passed by reference
       with emitting the copy on the caller side in the frontend.  */
    ఒకవేళ (storage_class == csc_none
	&& వృక్షం_సంకేతం (type) == FUNCTION_TYPE)
      కొరకు (వృక్షం al = TYPE_ARG_TYPES (type); al; al = వృక్షం_CHAIN (al))
	{
	  వృక్షం arg = వృక్షం_విలువ (al);
	  ఒకవేళ (arg != error_mark_కణుపు
	      && C_TYPE_VARIABLE_కొలత (arg))
	    {
	      DECL_UNINLINABLE (decl) = 1;
	      ఆపు;
	    }
	}

    /* Record `register' declaration for warnings on &
       and in case doing stupid register allocation.  */

    ఒకవేళ (storage_class == csc_రిజిస్టరు
	&& వృక్షం_సంకేతం (type) != FUNCTION_TYPE)
      {
	C_DECL_రిజిస్టరు (decl) = 1;
	DECL_రిజిస్టరు (decl) = 1;
      }

    /* Record constancy and volatility.  */
    c_apply_type_quals_గమ్యం_decl (type_quals, decl);

    /* Apply _Alignas specifiers.  */
    ఒకవేళ (alignas_align)
      {
	సమితి_DECL_ALIGN (decl, alignas_align * బిట్లు_చొప్పున_UNIT);
	DECL_USER_ALIGN (decl) = 1;
      }

    /* If a type has volatile components, it should be stored in memory.
       Otherwise, the fact that those components are volatile
       will be ignored, and would even crash the compiler.
       Of course, this only makes sense on  VAR,PARM, and RESULT decl's.   */
    ఒకవేళ (C_TYPE_FIELDS_VOLATILE (వృక్షం_TYPE (decl))
	&& (VAR_P (decl) ||  వృక్షం_సంకేతం (decl) == PARM_DECL
	  || వృక్షం_సంకేతం (decl) == ఫలితం_DECL))
      {
	/* It is not an error for a structure with volatile fields to
	   be declared register, but reset DECL_REGISTER since it
	   cannot actually go in a register.  */
	పూర్ణాంకం was_reg = C_DECL_రిజిస్టరు (decl);
	C_DECL_రిజిస్టరు (decl) = 0;
	DECL_రిజిస్టరు (decl) = 0;
	c_mark_addressable (decl);
	C_DECL_రిజిస్టరు (decl) = was_reg;
      }

  /* This is the earliest point at which we might know the assembler
     name of a variable.  Thus, if it's known before this, die horribly.  */
    gcc_assert (!HAS_DECL_ASSEMBLER_NAME_P (decl)
		|| !DECL_ASSEMBLER_NAME_సమితి_P (decl));

    ఒకవేళ (warn_cxx_compat
	&& VAR_P (decl)
	&& వృక్షం_ప్రజా (decl)
	&& వృక్షం_STATIC (decl)
	&& (రికార్డు_OR_UNION_TYPE_P (వృక్షం_TYPE (decl))
	    || వృక్షం_సంకేతం (వృక్షం_TYPE (decl)) == ENUMERAL_TYPE)
	&& TYPE_NAME (వృక్షం_TYPE (decl)) == NULL_వృక్షం)
      warning_at (DECL_ఆధారం_LOCATION (decl), OPT_Wc___compat,
		  "non-local variable %qD with anonymous type is "
		  "questionable in C++", decl);

    తిరిగి decl;
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

స్థిర వృక్షం
grokparms (నిర్మాణం c_arg_info *arg_info, తార్కిక funcdef_flag)
{
  వృక్షం arg_types = arg_info->types;

  ఒకవేళ (funcdef_flag && arg_info->had_vla_unspec)
    {
      /* A function definition isn't function prototype scope C99 6.2.1p4.  */
      /* C99 6.7.5.2p4 */
      error ("%<[*]%> not allowed in other than function prototype scope");
    }

  ఒకవేళ (arg_types == NULL_వృక్షం && !funcdef_flag && !flag_isoc23
      && !లోపల_system_శీర్షిక_at (ఆదానం_location))
    warning (OPT_Wstrict_prototypes,
	     "function declaration isn%'t a prototype");

  ఒకవేళ (arg_types == error_mark_కణుపు)
    /* Don't set TYPE_ARG_TYPES in this case.  */
    తిరిగి NULL_వృక్షం;

  లేకపోతే ఒకవేళ (arg_types && వృక్షం_సంకేతం (వృక్షం_విలువ (arg_types)) == IDENTIFIER_కణుపు)
    {
      ఒకవేళ (!funcdef_flag)
	{
	  permerror_opt (ఆదానం_location,
			 OPT_Wdeclaration_missing_parameter_type,
			 "parameter names (without types) in "
			 "function declaration");
	  arg_info->parms = NULL_వృక్షం;
	}
      లేకపోతే
	arg_info->parms = arg_info->types;

      arg_info->types = NULL_వృక్షం;
      తిరిగి NULL_వృక్షం;
    }
  లేకపోతే
    {
      వృక్షం parm, type, typelt;
      గుర్తులేని పూర్ణాంకం parmno;

      /* In C23, convert () to (void).  */
      ఒకవేళ (flag_isoc23
	  && !arg_types
	  && !arg_info->parms
	  && !arg_info->no_named_వాదనలు_stdarg_p)
	{
	  arg_types = arg_info->types = void_list_కణుపు;
	  arg_info->c23_ఖాళీలు_parens = 1;
	}

      /* If there is a parameter of incomplete type in a definition,
	 this is an error.  In a declaration this is valid, and a
	 struct or union type may be completed later, before any calls
	 or definition of the function.  In the case where the tag was
	 first declared within the parameter list, a warning has
	 already been given.  If a parameter has void type, then
	 this has already received an error (constraint violation in C2Y,
	 previously implicitly undefined behavior).  */

      కొరకు (parm = arg_info->parms, typelt = arg_types, parmno = 1;
	   parm;
	   parm = DECL_CHAIN (parm), typelt = వృక్షం_CHAIN (typelt), parmno++)
	{
	  type = వృక్షం_విలువ (typelt);
	  ఒకవేళ (type == error_mark_కణుపు)
	    కొనసాగు;

	  ఒకవేళ (!COMPLETE_TYPE_P (type))
	    {
	      ఒకవేళ (funcdef_flag)
		{
		  ఒకవేళ (DECL_NAME (parm))
		    error_at (ఆదానం_location,
			      "parameter %u (%q+D) has incomplete type",
			      parmno, parm);
		  లేకపోతే
		    error_at (DECL_ఆధారం_LOCATION (parm),
			      "parameter %u has incomplete type",
			      parmno);

		  వృక్షం_విలువ (typelt) = error_mark_కణుపు;
		  వృక్షం_TYPE (parm) = error_mark_కణుపు;
		  arg_types = NULL_వృక్షం;
		}
	    }

	  ఒకవేళ (DECL_NAME (parm) && వృక్షం_వాడిన (parm))
	    warn_if_shadowing (parm);
	}
      తిరిగి arg_types;
    }
}

/* Allocate and initialize a c_arg_info structure from the parser's
   obstack.  */

నిర్మాణం c_arg_info *
build_arg_info (శూన్య)
{
  నిర్మాణం c_arg_info *ret = XOBNEW (&parser_obstack, నిర్మాణం c_arg_info);
  ret->parms = NULL_వృక్షం;
  ret->ట్యాగులు = ఖాళీ;
  ret->types = NULL_వృక్షం;
  ret->others = NULL_వృక్షం;
  ret->pending_sizes = ఖాళీ;
  ret->had_vla_unspec = 0;
  ret->no_named_వాదనలు_stdarg_p = 0;
  ret->c23_ఖాళీలు_parens = 0;
  తిరిగి ret;
}

/* Take apart the current scope and return a c_arg_info structure with
   info on a parameter list just parsed.

   This structure is later fed to 'grokparms' and 'store_parm_decls'.

   ELLIPSIS being true means the argument list ended in '...' so don't
   append a sentinel (void_list_node) to the end of the type-list.

   EXPR is NULL or an expression that needs to be evaluated for the
   side effects of array size expressions in the parameters.  */

నిర్మాణం c_arg_info *
get_parm_info (తార్కిక ellipsis, వృక్షం సమాసం)
{
  నిర్మాణం c_binding *b = current_scope->bindings;
  నిర్మాణం c_arg_info *arg_info = build_arg_info ();

  వృక్షం parms = NULL_వృక్షం;
  vec<c_arg_ట్యాగ్, va_gc> *ట్యాగులు = ఖాళీ;
  వృక్షం types = NULL_వృక్షం;
  వృక్షం others = NULL_వృక్షం;

  తార్కిక gave_void_only_once_err = అబద్ధం;

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
  ఒకవేళ (b->prev == 0			    /* one binding */
      && వృక్షం_సంకేతం (b->decl) == PARM_DECL   /* which is a parameter */
      && !DECL_NAME (b->decl)               /* anonymous */
      && VOID_TYPE_P (వృక్షం_TYPE (b->decl))) /* of void type */
    {
      ఒకవేళ (TYPE_QUALS (వృక్షం_TYPE (b->decl)) != TYPE_UNQUALIFIED
	  || C_DECL_రిజిస్టరు (b->decl))
	error_at (b->locus, "%<void%> as only parameter may not be qualified");

      /* There cannot be an ellipsis.  */
      ఒకవేళ (ellipsis)
	error_at (b->locus, "%<void%> must be the only parameter");

      arg_info->types = void_list_కణుపు;
      తిరిగి arg_info;
    }

  ఒకవేళ (!ellipsis)
    types = void_list_కణుపు;

  /* Break up the bindings list into parms, tags, types, and others;
     apply sanity checks; purge the name-to-decl bindings.  */
  అయితే (b)
    {
      వృక్షం decl = b->decl;
      వృక్షం type = వృక్షం_TYPE (decl);
      c_arg_ట్యాగ్ ట్యాగ్;
      స్థిరరాశి అక్షరం *keyword;

      ఎంపిక (వృక్షం_సంకేతం (decl))
	{
	స్థితి PARM_DECL:
	  ఒకవేళ (b->id)
	    {
	      gcc_assert (I_చిహ్నం_BINDING (b->id) == b);
	      I_చిహ్నం_BINDING (b->id) = b->shadowed;
	    }

	  /* Check for forward decls that never got their actual decl.  */
	  ఒకవేళ (వృక్షం_ASM_WRITTEN (decl))
	    error_at (b->locus,
		      "parameter %q+D has just a forward declaration", decl);
	  /* Check for (..., void, ...) and named void parameters and issue an
	     error.  */
	  లేకపోతే ఒకవేళ (VOID_TYPE_P (type))
	    {
	      ఒకవేళ (!gave_void_only_once_err)
		{
		  error_at (b->locus,
			    "%<void%> must be the only parameter and unnamed");
		  gave_void_only_once_err = నిజం;
		}
	    }
	  లేకపోతే
	    {
	      /* Valid parameter, add it to the list.  */
	      DECL_CHAIN (decl) = parms;
	      parms = decl;

	      /* Since there is a prototype, args are passed in their
		 declared types.  The back end may override this later.  */
	      DECL_ARG_TYPE (decl) = type;
	      types = వృక్షం_cons (0, type, types);
	    }
	  ఆపు;

	స్థితి ENUMERAL_TYPE: keyword = "enum"; వెళ్ళు ట్యాగ్;
	స్థితి UNION_TYPE:    keyword = "union"; వెళ్ళు ట్యాగ్;
	స్థితి రికార్డు_TYPE:   keyword = "struct"; వెళ్ళు ట్యాగ్;
	ట్యాగ్:
	  /* Types may not have tag-names, in which case the type
	     appears in the bindings list with b->id NULL.  */
	  ఒకవేళ (b->id)
	    {
	      gcc_assert (I_ట్యాగ్_BINDING (b->id) == b);
	      I_ట్యాగ్_BINDING (b->id) = b->shadowed;
	    }

	  /* Warn about any struct, union or enum tags defined in a
	     parameter list.  The scope of such types is limited to
	     the parameter list, which is rarely if ever desirable
	     (it's impossible to call such a function with type-
	     correct arguments).  An anonymous union parm type is
	     meaningful as a GNU extension, so don't warn for that.  */
	  ఒకవేళ (వృక్షం_సంకేతం (decl) != UNION_TYPE || b->id != NULL_వృక్షం)
	    {
	      ఒకవేళ (b->id)
		{
		  /* The %s will be one of 'struct', 'union', or 'enum'.  */
		  ఒకవేళ (!flag_isoc23 || !COMPLETE_TYPE_P (decl))
		    warning_at (b->locus, 0,
				"%<%s %E%> declared inside parameter list"
				" will not be visible outside of this definition or"
				" declaration", keyword, b->id);
		}
	      లేకపోతే
		/* The %s will be one of 'struct', 'union', or 'enum'.  */
		warning_at (b->locus, 0,
			    "anonymous %s declared inside parameter list"
			    " will not be visible outside of this definition or"
			    " declaration", keyword);
	    }

	  ట్యాగ్.id = b->id;
	  ట్యాగ్.type = decl;
	  vec_సురక్షిత_నెట్టు (ట్యాగులు, ట్యాగ్);
	  ఆపు;

	స్థితి FUNCTION_DECL:
	  /* FUNCTION_DECLs appear when there is an implicit function
	     declaration in the parameter list.  */
	  gcc_assert (b->nested || చూసిన_error ());
	  వెళ్ళు సమితి_shadowed;

	స్థితి CONST_DECL:
	స్థితి TYPE_DECL:
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

	స్థితి ERROR_MARK:
	సమితి_shadowed:
	  /* error_mark_node appears here when we have an undeclared
	     variable.  Just throw it away.  */
	  ఒకవేళ (b->id)
	    {
	      gcc_assert (I_చిహ్నం_BINDING (b->id) == b);
	      I_చిహ్నం_BINDING (b->id) = b->shadowed;
	    }
	  ఆపు;

	  /* Other things that might be encountered.  */
	స్థితి LABEL_DECL:
	స్థితి VAR_DECL:
	అప్రమేయ:
	  gcc_unreachable ();
	}

      b = free_binding_and_advance (b);
    }

  arg_info->parms = parms;
  arg_info->ట్యాగులు = ట్యాగులు;
  arg_info->types = types;
  arg_info->others = others;
  arg_info->pending_sizes = సమాసం;
  arg_info->no_named_వాదనలు_stdarg_p = ellipsis && !types;
  తిరిగి arg_info;
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

నిర్మాణం c_typespec
parser_xref_ట్యాగ్ (location_t loc, గణన వృక్షం_సంకేతం_2 సంకేతం_2, వృక్షం name,
		 తార్కిక have_std_attrs, వృక్షం attrs, తార్కిక has_enum_type_specifier)
{
  నిర్మాణం c_typespec ret;
  వృక్షం ref;
  location_t refloc;

  ret.సమాసం = NULL_వృక్షం;
  ret.సమాసం_const_operands = నిజం;
  ret.has_enum_type_specifier = has_enum_type_specifier;

  /* If a cross reference is requested, look up the type already
     defined for this tag and return it.  If an enum type specifier is
     present, only a definition in the current scope is relevant.  */

  ref = lookup_ట్యాగ్ (సంకేతం_2, name, has_enum_type_specifier, &refloc);

  /* If the visible type is still being defined, see if there is
     an earlier definition (which may be complete).  We do not
     have to loop because nested redefinitions are not allowed.  */
  ఒకవేళ (flag_isoc23 && ref && C_TYPE_BEING_DEFINED (ref))
    {
      వృక్షం vis = మునుపటి_ట్యాగ్ (ref);
      ఒకవేళ (vis)
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
  ret.రకం = (ref
	      ? (have_std_attrs ? ctsk_tagref_attrs : ctsk_tagref)
	      : (have_std_attrs ? ctsk_tagfirstref_attrs : ctsk_tagfirstref));
  ఒకవేళ (ref && వృక్షం_సంకేతం (ref) == సంకేతం_2)
    {
      decl_లక్షణాలు (&ref, attrs, (పూర్ణాంకం) ATTR_FLAG_TYPE_లోపల_ఉంచు);
      ఒకవేళ (C_TYPE_DEFINED_లోపల_STRUCT (ref)
	  && loc != UNKNOWN_LOCATION
	  && warn_cxx_compat)
	{
	  auto_diagnostic_సమూహం d;
	  ఎంపిక (సంకేతం_2)
	    {
	    స్థితి ENUMERAL_TYPE:
	      ఒకవేళ (warning_at (loc, OPT_Wc___compat,
			      ("enum type defined in struct or union "
			       "is not visible in C++")))
		  inform (refloc, "enum type defined here");
	      ఆపు;
	    స్థితి రికార్డు_TYPE:
	      ఒకవేళ (warning_at (loc, OPT_Wc___compat,
			      ("struct defined in struct or union "
			       "is not visible in C++")))
		inform (refloc, "struct defined here");
	      ఆపు;
	    స్థితి UNION_TYPE:
	      ఒకవేళ (warning_at (loc, OPT_Wc___compat,
			      ("union defined in struct or union "
			       "is not visible in C++")))
		inform (refloc, "union defined here");
	      ఆపు;
	    అప్రమేయ:
	      gcc_unreachable();
	    }
	}

      ret.spec = ref;
      తిరిగి ret;
    }

  /* If no such tag is yet defined, create a forward-reference node
     and record it as the "definition".
     When a real declaration of this type is found,
     the forward-reference will be altered into a real type.  */

  ref = make_కణుపు (సంకేతం_2);
  ఒకవేళ (flag_isoc23 || సంకేతం_2 == ENUMERAL_TYPE)
    సమితి_TYPE_STRUCTURAL_EQUALITY (ref);
  ఒకవేళ (సంకేతం_2 == ENUMERAL_TYPE)
    {
      /* Give the type a default layout like unsigned int
	 to avoid crashing if it does not get defined.  */
      సమితి_TYPE_బహుళకం (ref, TYPE_బహుళకం (unsigned_type_కణుపు));
      సమితి_TYPE_ALIGN (ref, TYPE_ALIGN (unsigned_type_కణుపు));
      TYPE_USER_ALIGN (ref) = 0;
      TYPE_UNSIGNED (ref) = 1;
      TYPE_PRECISION (ref) = TYPE_PRECISION (unsigned_type_కణుపు);
      TYPE_MIN_విలువ (ref) = TYPE_MIN_విలువ (unsigned_type_కణుపు);
      TYPE_MAX_విలువ (ref) = TYPE_MAX_విలువ (unsigned_type_కణుపు);
      ENUM_FIXED_UNDERLYING_TYPE_P (ref) = has_enum_type_specifier;
    }

  pushtag (loc, name, ref);
  decl_లక్షణాలు (&ref, attrs, (పూర్ణాంకం) ATTR_FLAG_TYPE_లోపల_ఉంచు);
  ఒకవేళ (లోపల_underspecified_init)
    error_at (loc, "%qT declared in underspecified object initializer",
	      ref);

  ret.spec = ref;
  తిరిగి ret;
}

/* Get the struct, enum or union (CODE says which) with tag NAME.
   Define the tag as a forward-reference if it is not defined.
   Return a tree for the type.  */

వృక్షం
xref_ట్యాగ్ (గణన వృక్షం_సంకేతం_2 సంకేతం_2, వృక్షం name)
{
  తిరిగి parser_xref_ట్యాగ్ (ఆదానం_location, సంకేతం_2, name, అబద్ధం, NULL_వృక్షం,
			  అబద్ధం).spec;
}

/* Make sure that the tag NAME is defined *in the current scope*
   at least as a forward reference.
   LOC is the location of the struct's definition.
   CODE says which kind of tag NAME ought to be.

   This stores the current value of the file static STRUCT_PARSE_INFO
   in *ENCLOSING_STRUCT_PARSE_INFO, and points STRUCT_PARSE_INFO at a
   new c_struct_parse_info structure.  The old value of
   STRUCT_PARSE_INFO is restored in finish_struct.  */

వృక్షం
ప్రారంభం_struct (location_t loc, గణన వృక్షం_సంకేతం_2 సంకేతం_2, వృక్షం name,
	      తరగతి c_struct_parse_info **enclosing_struct_parse_info)
{
  /* If there is already a tag defined at this scope
     (as a forward reference), just return it.  */

  వృక్షం ref = NULL_వృక్షం;
  location_t refloc = UNKNOWN_LOCATION;

  ఒకవేళ (name != NULL_వృక్షం)
    ref = lookup_ట్యాగ్ (సంకేతం_2, name, నిజం, &refloc);

  /* For C23, even if we already have a completed definition,
     we do not use it. We will check for consistency later.
     If we are in a nested redefinition the type is not
     complete. We will then detect this below.  */
  ఒకవేళ (flag_isoc23 && ref && TYPE_కొలత (ref))
    ref = NULL_వృక్షం;

  ఒకవేళ (ref && వృక్షం_సంకేతం (ref) == సంకేతం_2)
    {
      ఒకవేళ (TYPE_STUB_DECL (ref))
	refloc = DECL_ఆధారం_LOCATION (TYPE_STUB_DECL (ref));

      ఒకవేళ (TYPE_కొలత (ref))
	{
	  auto_diagnostic_సమూహం d;
	  ఒకవేళ (సంకేతం_2 == UNION_TYPE)
	    error_at (loc, "redefinition of %<union %E%>", name);
	  లేకపోతే
	    error_at (loc, "redefinition of %<struct %E%>", name);
	  ఒకవేళ (refloc != UNKNOWN_LOCATION)
	    inform (refloc, "originally defined here");
	  /* Don't create structures using a name already in use.  */
	  ref = NULL_వృక్షం;
	}
      లేకపోతే ఒకవేళ (C_TYPE_BEING_DEFINED (ref))
	{
	  ఒకవేళ (సంకేతం_2 == UNION_TYPE)
	    error_at (loc, "nested redefinition of %<union %E%>", name);
	  లేకపోతే
	    error_at (loc, "nested redefinition of %<struct %E%>", name);
	  /* Don't bother to report "originally defined here" for a
	     nested redefinition; the original definition should be
	     obvious.  */
	  /* Don't create structures that contain themselves.  */
	  ref = NULL_వృక్షం;
	}
    }

  /* Otherwise create a forward-reference just so the tag is in scope.  */

  ఒకవేళ (ref == NULL_వృక్షం || వృక్షం_సంకేతం (ref) != సంకేతం_2)
    {
      ref = make_కణుపు (సంకేతం_2);
      ఒకవేళ (flag_isoc23)
	సమితి_TYPE_STRUCTURAL_EQUALITY (ref);
      pushtag (loc, name, ref);
    }

  C_TYPE_BEING_DEFINED (ref) = 1;
  కొరకు (వృక్షం v = TYPE_MAIN_VARIANT (ref); v; v = TYPE_తదుపరి_VARIANT (v))
    TYPE_PACKED (v) = flag_pack_struct;

  *enclosing_struct_parse_info = struct_parse_info;
  struct_parse_info = కొత్త c_struct_parse_info ();
  struct_parse_info->refloc = refloc;

  /* FIXME: This will issue a warning for a use of a type defined
     within a statement expr used within sizeof, et. al.  This is not
     terribly serious as C++ doesn't permit statement exprs within
     sizeof anyhow.  */
  ఒకవేళ (warn_cxx_compat
      && (లోపల_sizeof || లోపల_typeof || లోపల_alignof || లోపల_countof))
    warning_at (loc, OPT_Wc___compat,
		"defining type in %qs expression is invalid in C++",
		(లోపల_sizeof ? "sizeof"
		 : లోపల_typeof ? "typeof"
		 : లోపల_alignof ? "alignof"
		 : "_Countof"));

  ఒకవేళ (లోపల_underspecified_init)
    error_at (loc, "%qT defined in underspecified object initializer", ref);

  తిరిగి ref;
}

/* Process the specs, declarator and width (NULL if omitted)
   of a structure component, returning a FIELD_DECL node.
   WIDTH is non-NULL for bit-fields only, and is an INTEGER_CST node.
   DECL_ATTRS is as for grokdeclarator.

   LOC is the location of the structure component.

   This is done during the parsing of the struct declaration.
   The FIELD_DECL nodes are chained together and the lot of them
   are ultimately passed to `build_struct' to make the RECORD_TYPE node.  */

వృక్షం
grokfield (location_t loc,
	   నిర్మాణం c_declarator *declarator, నిర్మాణం c_declspecs *declspecs,
	   వృక్షం వెడల్పు, వృక్షం *decl_attrs, వృక్షం *సమాసం)
{
  వృక్షం విలువ;

  ఒకవేళ (declarator->రకం == cdk_id && declarator->u.id.id == NULL_వృక్షం
      && వెడల్పు == NULL_వృక్షం)
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

      వృక్షం type = declspecs->type;
      తార్కిక ok = అబద్ధం;

      ఒకవేళ (రికార్డు_OR_UNION_TYPE_P (type)
	  && (flag_ms_extensions
	      || flag_plan9_extensions
	      || !declspecs->typedef_p))
	{
	  ఒకవేళ (flag_ms_extensions || flag_plan9_extensions)
	    ok = నిజం;
	  లేకపోతే ఒకవేళ (TYPE_NAME (type) == ఖాళీ)
	    ok = నిజం;
	  లేకపోతే
	    ok = అబద్ధం;
	}
      ఒకవేళ (!ok)
	{
	  pedwarn (loc, 0, "declaration does not declare anything");
	  తిరిగి NULL_వృక్షం;
	}
      ఒకవేళ (flag_isoc99)
	pedwarn_c99 (loc, OPT_Wpedantic,
		     "ISO C99 doesn%'t support unnamed structs/unions");
      లేకపోతే
	pedwarn_c99 (loc, OPT_Wpedantic,
		     "ISO C90 doesn%'t support unnamed structs/unions");
    }

  విలువ = grokdeclarator (declarator, declspecs, క్షేత్రం, అబద్ధం,
			  వెడల్పు ? &వెడల్పు : ఖాళీ, decl_attrs, సమాసం, ఖాళీ,
			  DEPRECATED_సాధారణ);

  /* When this field has name, its type is a top level type, we should
     call verify_counted_by_for_top_anonymous_type.  */
  ఒకవేళ (DECL_NAME (విలువ) != NULL_వృక్షం
      && declspecs->typespec_రకం == ctsk_tagdef)
    verify_counted_by_for_శిఖరం_anonymous_type (declspecs->type);

  ముగింపు_decl (విలువ, loc, NULL_వృక్షం, NULL_వృక్షం, NULL_వృక్షం);
  DECL_INITIAL (విలువ) = వెడల్పు;
  ఒకవేళ (వెడల్పు)
    సమితి_DECL_C_బిట్టు_క్షేత్రం (విలువ);

  ఒకవేళ (warn_cxx_compat && DECL_NAME (విలువ) != NULL_వృక్షం)
    {
      /* If we currently have a binding for this field, set the
	 in_struct field in the binding, so that we warn about lookups
	 which find it.  */
      నిర్మాణం c_binding *b = I_చిహ్నం_BINDING (DECL_NAME (విలువ));
      ఒకవేళ (b != ఖాళీ)
	{
	  /* If the in_struct field is not yet set, push it on a list
	     to be cleared when this struct is finished.  */
	  ఒకవేళ (!b->లోపల_struct)
	    {
	      struct_parse_info->fields.సురక్షిత_నెట్టు (b);
	      b->లోపల_struct = 1;
	    }
	}
    }

  తిరిగి విలువ;
}

/* Subroutine of detect_field_duplicates: return whether X and Y,
   which are both fields in the same struct, have duplicate field
   names.  */

స్థిర తార్కిక
is_duplicate_క్షేత్రం (వృక్షం x, వృక్షం y)
{
  ఒకవేళ (DECL_NAME (x) != NULL_వృక్షం && DECL_NAME (x) == DECL_NAME (y))
    తిరిగి నిజం;

  /* When using -fplan9-extensions, an anonymous field whose name is a
     typedef can duplicate a field name.  */
  ఒకవేళ (flag_plan9_extensions
      && (DECL_NAME (x) == NULL_వృక్షం || DECL_NAME (y) == NULL_వృక్షం))
    {
      వృక్షం xt, xn, yt, yn;

      xt = వృక్షం_TYPE (x);
      ఒకవేళ (DECL_NAME (x) != NULL_వృక్షం)
	xn = DECL_NAME (x);
      లేకపోతే ఒకవేళ (రికార్డు_OR_UNION_TYPE_P (xt)
	       && TYPE_NAME (xt) != NULL_వృక్షం
	       && వృక్షం_సంకేతం (TYPE_NAME (xt)) == TYPE_DECL)
	xn = DECL_NAME (TYPE_NAME (xt));
      లేకపోతే
	xn = NULL_వృక్షం;

      yt = వృక్షం_TYPE (y);
      ఒకవేళ (DECL_NAME (y) != NULL_వృక్షం)
	yn = DECL_NAME (y);
      లేకపోతే ఒకవేళ (రికార్డు_OR_UNION_TYPE_P (yt)
	       && TYPE_NAME (yt) != NULL_వృక్షం
	       && వృక్షం_సంకేతం (TYPE_NAME (yt)) == TYPE_DECL)
	yn = DECL_NAME (TYPE_NAME (yt));
      లేకపోతే
	yn = NULL_వృక్షం;

      ఒకవేళ (xn != NULL_వృక్షం && xn == yn)
	తిరిగి నిజం;
    }

  తిరిగి అబద్ధం;
}

/* Subroutine of detect_field_duplicates: add the fields of FIELDLIST
   to HTAB, giving errors for any duplicates.  */

స్థిర శూన్య
detect_క్షేత్రం_duplicates_hash (వృక్షం fieldlist,
			      hash_పట్టిక<nofree_ptr_hash <వృక్ష_కణుపు> > *htab)
{
  వృక్షం x, y;
  వృక్ష_కణుపు **స్థానం;

  కొరకు (x = fieldlist; x ; x = DECL_CHAIN (x))
    ఒకవేళ ((y = DECL_NAME (x)) != NULL_వృక్షం)
      {
	స్థానం = htab->కనుగొను_స్థానం (y, చొప్పించు);
	ఒకవేళ (*స్థానం)
	  {
	    error ("duplicate member %q+D", x);
	    DECL_NAME (x) = NULL_వృక్షం;
	  }
	*స్థానం = y;
      }
    లేకపోతే ఒకవేళ (రికార్డు_OR_UNION_TYPE_P (వృక్షం_TYPE (x)))
      {
	detect_క్షేత్రం_duplicates_hash (TYPE_FIELDS (వృక్షం_TYPE (x)), htab);

	/* When using -fplan9-extensions, an anonymous field whose
	   name is a typedef can duplicate a field name.  */
	ఒకవేళ (flag_plan9_extensions
	    && TYPE_NAME (వృక్షం_TYPE (x)) != NULL_వృక్షం
	    && వృక్షం_సంకేతం (TYPE_NAME (వృక్షం_TYPE (x))) == TYPE_DECL)
	  {
	    వృక్షం xn = DECL_NAME (TYPE_NAME (వృక్షం_TYPE (x)));
	    స్థానం = htab->కనుగొను_స్థానం (xn, చొప్పించు);
	    ఒకవేళ (*స్థానం)
	      error ("duplicate member %q+D", TYPE_NAME (వృక్షం_TYPE (x)));
	    *స్థానం = xn;
	  }
      }
}

/* Generate an error for any duplicate field names in FIELDLIST.  Munge
   the list such that this does not present a problem later.  */

స్థిర శూన్య
detect_క్షేత్రం_duplicates (వృక్షం fieldlist)
{
  వృక్షం x, y;
  పూర్ణాంకం timeout = 10;

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
  ఒకవేళ (c_dialect_objc ())
    ఒకవేళ (objc_detect_క్షేత్రం_duplicates (అబద్ధం))
      తిరిగి;

  /* First, see if there are more than "a few" fields.
     This is trivially true if there are zero or one fields.  */
  ఒకవేళ (!fieldlist || !DECL_CHAIN (fieldlist))
    తిరిగి;
  x = fieldlist;
  చేయి {
    timeout--;
    ఒకవేళ (DECL_NAME (x) == NULL_వృక్షం
	&& రికార్డు_OR_UNION_TYPE_P (వృక్షం_TYPE (x)))
      timeout = 0;
    x = DECL_CHAIN (x);
  } అయితే (timeout > 0 && x);

  /* If there were "few" fields and no anonymous structures or unions,
     avoid the overhead of allocating a hash table.  Instead just do
     the nested traversal thing.  */
  ఒకవేళ (timeout > 0)
    {
      కొరకు (x = DECL_CHAIN (fieldlist); x; x = DECL_CHAIN (x))
	/* When using -fplan9-extensions, we can have duplicates
	   between typedef names and fields.  */
	ఒకవేళ (DECL_NAME (x)
	    || (flag_plan9_extensions
		&& DECL_NAME (x) == NULL_వృక్షం
		&& రికార్డు_OR_UNION_TYPE_P (వృక్షం_TYPE (x))
		&& TYPE_NAME (వృక్షం_TYPE (x)) != NULL_వృక్షం
		&& వృక్షం_సంకేతం (TYPE_NAME (వృక్షం_TYPE (x))) == TYPE_DECL))
	  {
	    కొరకు (y = fieldlist; y != x; y = వృక్షం_CHAIN (y))
	      ఒకవేళ (is_duplicate_క్షేత్రం (y, x))
		{
		  error ("duplicate member %q+D", x);
		  DECL_NAME (x) = NULL_వృక్షం;
		}
	  }
    }
  లేకపోతే
    {
      hash_పట్టిక<nofree_ptr_hash <వృక్ష_కణుపు> > htab (37);
      detect_క్షేత్రం_duplicates_hash (fieldlist, &htab);
    }
}

/* Finish up struct info used by -Wc++-compat.  */

స్థిర శూన్య
warn_cxx_compat_ముగింపు_struct (వృక్షం fieldlist, గణన వృక్షం_సంకేతం_2 సంకేతం_2,
			       location_t రికార్డు_loc)
{
  గుర్తులేని పూర్ణాంకం ix;
  వృక్షం x;
  నిర్మాణం c_binding *b;

  ఒకవేళ (fieldlist == NULL_వృక్షం)
    {
      ఒకవేళ (సంకేతం_2 == రికార్డు_TYPE)
	warning_at (రికార్డు_loc, OPT_Wc___compat,
		    "empty struct has size 0 in C, size 1 in C++");
      లేకపోతే
	warning_at (రికార్డు_loc, OPT_Wc___compat,
		    "empty union has size 0 in C, size 1 in C++");
    }

  /* Set the C_TYPE_DEFINED_IN_STRUCT flag for each type defined in
     the current struct.  We do this now at the end of the struct
     because the flag is used to issue visibility warnings, and we
     only want to issue those warnings if the type is referenced
     outside of the struct declaration.  */
  FOR_EACH_VEC_ELT (struct_parse_info->struct_types, ix, x)
    C_TYPE_DEFINED_లోపల_STRUCT (x) = 1;

  /* The TYPEDEFS_SEEN field of STRUCT_PARSE_INFO is a list of
     typedefs used when declaring fields in this struct.  If the name
     of any of the fields is also a typedef name then the struct would
     not parse in C++, because the C++ lookup rules say that the
     typedef name would be looked up in the context of the struct, and
     would thus be the field rather than the typedef.  */
  ఒకవేళ (!struct_parse_info->typedefs_చూసిన.is_ఖాళీలు ()
      && fieldlist != NULL_వృక్షం)
    {
      /* Use a hash_set<tree> using the name of the typedef.  We can use
	 a hash_set<tree> because identifiers are interned.  */
      hash_సమితి<వృక్షం> tset;

      FOR_EACH_VEC_ELT (struct_parse_info->typedefs_చూసిన, ix, x)
	tset.కూడు (DECL_NAME (x));

      కొరకు (x = fieldlist; x != NULL_వృక్షం; x = DECL_CHAIN (x))
	{
	  ఒకవేళ (DECL_NAME (x) != NULL_వృక్షం
	      && tset.కలిగియుంది (DECL_NAME (x)))
	    {
	      warning_at (DECL_ఆధారం_LOCATION (x), OPT_Wc___compat,
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
    b->లోపల_struct = 0;
}

/* Function to help qsort sort FIELD_DECLs by name order.  */

స్థిర పూర్ణాంకం
క్షేత్రం_decl_cmp (స్థిరరాశి శూన్య *x_p, స్థిరరాశి శూన్య *y_p)
{
  స్థిరరాశి వృక్షం *స్థిరరాశి x = (స్థిరరాశి వృక్షం *) x_p;
  స్థిరరాశి వృక్షం *స్థిరరాశి y = (స్థిరరాశి వృక్షం *) y_p;

  ఒకవేళ (DECL_NAME (*x) == DECL_NAME (*y))
    /* A nontype is "greater" than a type.  */
    తిరిగి (వృక్షం_సంకేతం (*y) == TYPE_DECL) - (వృక్షం_సంకేతం (*x) == TYPE_DECL);
  ఒకవేళ (DECL_NAME (*x) == NULL_వృక్షం)
    తిరిగి -1;
  ఒకవేళ (DECL_NAME (*y) == NULL_వృక్షం)
    తిరిగి 1;
  ఒకవేళ (DECL_NAME (*x) < DECL_NAME (*y))
    తిరిగి -1;
  తిరిగి 1;
}

/* If this structure or union completes the type of any previous
   variable declaration, lay it out and output its rtl.  */
స్థిర శూన్య
ముగింపు_incomplete_vars (వృక్షం incomplete_vars, తార్కిక toplevel)
{
  కొరకు (వృక్షం x = incomplete_vars; x; x = వృక్షం_CHAIN (x))
    {
      వృక్షం decl = వృక్షం_విలువ (x);
      ఒకవేళ (వృక్షం_సంకేతం (వృక్షం_TYPE (decl)) == ARRAY_TYPE)
	layout_array_type (వృక్షం_TYPE (decl));
      ఒకవేళ (వృక్షం_సంకేతం (decl) != TYPE_DECL)
	{
	  relayout_decl (decl);
	  ఒకవేళ (c_dialect_objc ())
	    objc_check_decl (decl);
	  rest_యొక్క_decl_compilation (decl, toplevel, 0);
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

స్థిర తార్కిక
is_flexible_array_member_p (తార్కిక is_చివరి_క్షేత్రం,
			    వృక్షం x)
{
  /* If not the last field, return false.  */
  ఒకవేళ (!is_చివరి_క్షేత్రం)
    తిరిగి అబద్ధం;

  /* If not an array field, return false.  */
  ఒకవేళ (వృక్షం_సంకేతం (వృక్షం_TYPE (x)) != ARRAY_TYPE)
    తిరిగి అబద్ధం;

  తార్కిక is_zero_నిడివి_array = zero_నిడివి_array_type_p (వృక్షం_TYPE (x));
  తార్కిక is_one_element_array = one_element_array_type_p (వృక్షం_TYPE (x));
  తార్కిక is_flexible_array = flexible_array_member_type_p (వృక్షం_TYPE (x));

  గుర్తులేని పూర్ణాంకం strict_flex_array_level = c_strict_flex_array_level_యొక్క (x);

  ఎంపిక (strict_flex_array_level)
    {
      స్థితి 0:
	/* Default, all trailing arrays are flexible array members.  */
	తిరిగి నిజం;
      స్థితి 1:
	/* Level 1: all "[1]", "[0]", and "[]" are flexible array members.  */
	ఒకవేళ (is_one_element_array)
	  తిరిగి నిజం;
	/* FALLTHROUGH.  */
      స్థితి 2:
	/* Level 2: all "[0]", and "[]" are flexible array members.  */
	ఒకవేళ (is_zero_నిడివి_array)
	  తిరిగి నిజం;
	/* FALLTHROUGH.  */
      స్థితి 3:
	/* Level 3: Only "[]" are flexible array members.  */
	ఒకవేళ (is_flexible_array)
	  తిరిగి నిజం;
	ఆపు;
      అప్రమేయ:
	gcc_unreachable ();
    }
  తిరిగి అబద్ధం;
}

/* Recompute TYPE_CANONICAL for variants of the type including qualified
   versions of the type and related pointer types after an aggregate type
   has been finalized.
   Will not update array types, pointers to array types, function
   types and other derived types created while the type was still
   incomplete, those will remain TYPE_STRUCTURAL_EQUALITY_P.  */

స్థిర శూన్య
c_update_type_canonical (వృక్షం t)
{
  gcc_checking_assert (TYPE_MAIN_VARIANT (t) == t && !TYPE_QUALS (t));
  కొరకు (వృక్షం x = t, l = NULL_వృక్షం; x; l = x, x = TYPE_తదుపరి_VARIANT (x))
    {
      ఒకవేళ (x != t && TYPE_STRUCTURAL_EQUALITY_P (x))
	{
	  ఒకవేళ (!TYPE_QUALS (x))
	    TYPE_CANONICAL (x) = TYPE_CANONICAL (t);
	  లేకపోతే
	    {
	      వృక్షం
		c = c_build_qualified_type (TYPE_CANONICAL (t), TYPE_QUALS (x));
	      ఒకవేళ (TYPE_STRUCTURAL_EQUALITY_P (c))
		{
		  gcc_checking_assert (TYPE_CANONICAL (t) == t);
		  ఒకవేళ (c == x)
		    TYPE_CANONICAL (x) = x;
		  లేకపోతే
		    {
		      /* build_qualified_type for this function unhelpfully
			 moved c from some later spot in TYPE_MAIN_VARIANT (t)
			 chain to right after t (or created it there).  Move
			 it right before x and process c and then x.  */
		      gcc_checking_assert (TYPE_తదుపరి_VARIANT (t) == c);
		      ఒకవేళ (l != t)
			{
			  TYPE_తదుపరి_VARIANT (t) = TYPE_తదుపరి_VARIANT (c);
			  TYPE_తదుపరి_VARIANT (l) = c;
			  TYPE_తదుపరి_VARIANT (c) = x;
			}
		      TYPE_CANONICAL (c) = c;
		      x = c;
		    }
		}
	      లేకపోతే
		TYPE_CANONICAL (x) = TYPE_CANONICAL (c);
	    }
	}
      లేకపోతే ఒకవేళ (x != t)
	కొనసాగు;
      కొరకు (వృక్షం p = TYPE_సూచిక_గమ్యం (x); p; p = TYPE_తదుపరి_PTR_గమ్యం (p))
	{
	  ఒకవేళ (!TYPE_STRUCTURAL_EQUALITY_P (p))
	    కొనసాగు;
	  ఒకవేళ (TYPE_CANONICAL (x) != x || TYPE_REF_CAN_ALIAS_ALL (p))
	    TYPE_CANONICAL (p)
	      = c_build_సూచిక_type_for_బహుళకం (TYPE_CANONICAL (x), TYPE_బహుళకం (p),
					       అబద్ధం);
	  లేకపోతే
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

స్థిర శూన్య
c_update_variably_modified (వృక్షం t)
{
  కొరకు (వృక్షం x = t; x; x = TYPE_తదుపరి_VARIANT (x))
    {
      C_TYPE_VARIABLY_MODIFIED (x) = 1;
      కొరకు (వృక్షం p = TYPE_సూచిక_గమ్యం (x); p; p = TYPE_తదుపరి_PTR_గమ్యం (p))
	c_update_variably_modified (p);
    }
}


/* Verify the argument of the counted_by attribute of each field of
   the containing structure, OUTMOST_STRUCT_TYPE, including its inner
   anonymous struct/union, Report error and remove the corresponding
   attribute when it's not.  */

స్థిర శూన్య
verify_counted_by_attribute (వృక్షం outmost_struct_type,
			     వృక్షం cur_struct_type)
{
  కొరకు (వృక్షం క్షేత్రం_2 = TYPE_FIELDS (cur_struct_type); క్షేత్రం_2;
       క్షేత్రం_2 = వృక్షం_CHAIN (క్షేత్రం_2))
    {
      ఒకవేళ (flexible_array_member_type_p (వృక్షం_TYPE (క్షేత్రం_2))
	   || వృక్షం_సంకేతం (వృక్షం_TYPE (క్షేత్రం_2)) == సూచిక_TYPE)
	{
	  వృక్షం attr_counted_by = lookup_attribute ("counted_by",
						   DECL_లక్షణాలు (క్షేత్రం_2));

	  ఒకవేళ (!attr_counted_by)
	    కొనసాగు;

	  /* If there is an counted_by attribute attached to the field,
	     verify it.  */

	  వృక్షం fieldname = వృక్షం_విలువ (వృక్షం_విలువ (attr_counted_by));

	  /* Verify the argument of the attribute is a valid field of the
	     containing structure.  */

	  వృక్షం counted_by_క్షేత్రం = lookup_క్షేత్రం (outmost_struct_type,
						fieldname);

	  /* Error when the field is not found in the containing structure
	     and remove the corresponding counted_by attribute from the
	     field_decl.  */
	  ఒకవేళ (!counted_by_క్షేత్రం)
	    {
	      error_at (DECL_ఆధారం_LOCATION (క్షేత్రం_2),
		    "argument %qE to the %<counted_by%> attribute"
		    " is not a field declaration in the same structure"
		    " as %qD", fieldname, క్షేత్రం_2);
	      DECL_లక్షణాలు (క్షేత్రం_2)
		= remove_attribute ("counted_by", DECL_లక్షణాలు (క్షేత్రం_2));
	    }
	  లేకపోతే
	  /* Error when the field is not with an integer type.  */
	    {
	      అయితే (వృక్షం_CHAIN (counted_by_క్షేత్రం))
		counted_by_క్షేత్రం = వృక్షం_CHAIN (counted_by_క్షేత్రం);
	      వృక్షం real_క్షేత్రం = వృక్షం_విలువ (counted_by_క్షేత్రం);

	      ఒకవేళ (!INTEGRAL_TYPE_P (వృక్షం_TYPE (real_క్షేత్రం)))
		{
		  error_at (DECL_ఆధారం_LOCATION (క్షేత్రం_2),
			"argument %qE to the %<counted_by%> attribute"
			" is not a field declaration with an integer type",
			fieldname);
		  DECL_లక్షణాలు (క్షేత్రం_2)
		    = remove_attribute ("counted_by",
				    DECL_లక్షణాలు (క్షేత్రం_2));
		}
	    }
	}
      లేకపోతే ఒకవేళ (రికార్డు_OR_UNION_TYPE_P (వృక్షం_TYPE (క్షేత్రం_2))
	       && (DECL_NAME (క్షేత్రం_2) == NULL_వృక్షం))
	verify_counted_by_attribute (outmost_struct_type, వృక్షం_TYPE (క్షేత్రం_2));
    }
}

/* Caller should make sure the TYPE is a top-level type (i.e. not being
   nested in other structure/uniona). For such type, verify its counted_by
   if it is an anonymous structure/union.  */

శూన్య
verify_counted_by_for_శిఖరం_anonymous_type (వృక్షం type)
{
  ఒకవేళ (!రికార్డు_OR_UNION_TYPE_P (type))
    తిరిగి;

  ఒకవేళ (C_TYPE_FIELDS_HAS_COUNTED_BY (type)
      && c_type_ట్యాగ్ (type) == NULL_వృక్షం)
    verify_counted_by_attribute (type, type);
}

/* TYPE is a struct or union that we're applying may_alias to after the body is
   parsed.  Fixup any POINTER_TO types.  */

స్థిర శూన్య
c_fixup_may_alias (వృక్షం type)
{
  కొరకు (వృక్షం t = TYPE_సూచిక_గమ్యం (type); t; t = TYPE_తదుపరి_PTR_గమ్యం (t))
    కొరకు (వృక్షం v = TYPE_MAIN_VARIANT (t); v; v = TYPE_తదుపరి_VARIANT (v))
      TYPE_REF_CAN_ALIAS_ALL (v) = నిజం;
}

/* Fill in the fields of a RECORD_TYPE or UNION_TYPE node, T.
   LOC is the location of the RECORD_TYPE or UNION_TYPE's definition.
   FIELDLIST is a chain of FIELD_DECL nodes for the fields.
   ATTRIBUTES are attributes to be applied to the structure.

   ENCLOSING_STRUCT_PARSE_INFO is the value of STRUCT_PARSE_INFO when
   the struct was started.  */

వృక్షం
ముగింపు_struct (location_t loc, వృక్షం t, వృక్షం fieldlist, వృక్షం లక్షణాలు,
	       తరగతి c_struct_parse_info *enclosing_struct_parse_info,
	       వృక్షం *సమాసం)
{
  వృక్షం x;
  తార్కిక toplevel = file_scope == current_scope;

  /* If this type was previously laid out as a forward reference,
     make sure we lay it out again.  */

  TYPE_కొలత (t) = NULL_వృక్షం;

  decl_లక్షణాలు (&t, లక్షణాలు, (పూర్ణాంకం) ATTR_FLAG_TYPE_లోపల_ఉంచు);

  ఒకవేళ (pedantic)
    {
      కొరకు (x = fieldlist; x; x = DECL_CHAIN (x))
	{
	  ఒకవేళ (DECL_NAME (x) != NULL_వృక్షం)
	    ఆపు;
	  ఒకవేళ (flag_isoc11 && రికార్డు_OR_UNION_TYPE_P (వృక్షం_TYPE (x)))
	    ఆపు;
	}

      ఒకవేళ (x == NULL_వృక్షం)
	{
	  ఒకవేళ (వృక్షం_సంకేతం (t) == UNION_TYPE)
	    {
	      ఒకవేళ (fieldlist)
		pedwarn (loc, OPT_Wpedantic, "union has no named members");
	      లేకపోతే
		pedwarn (loc, OPT_Wpedantic, "union has no members");
	    }
	  లేకపోతే
	    {
	      ఒకవేళ (fieldlist)
		pedwarn (loc, OPT_Wpedantic, "struct has no named members");
	      లేకపోతే
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

  తార్కిక saw_named_క్షేత్రం = అబద్ధం;
  కొరకు (x = fieldlist; x; x = DECL_CHAIN (x))
    {
      /* Whether this field is the last field of the structure or union.
	 for UNION, any field is the last field of it.  */
      తార్కిక is_చివరి_క్షేత్రం = (DECL_CHAIN (x) == NULL_వృక్షం)
			    || (వృక్షం_సంకేతం (t) == UNION_TYPE);

      ఒకవేళ (వృక్షం_TYPE (x) == error_mark_కణుపు)
	కొనసాగు;

      DECL_CONTEXT (x) = t;

      వృక్షం t1 = strip_array_types (వృక్షం_TYPE (x));
      /* If any field is const, the structure type is pseudo-const.  */
      ఒకవేళ (వృక్షం_READONLY (x))
	C_TYPE_FIELDS_READONLY (t) = 1;
      లేకపోతే
	{
	  /* A field that is pseudo-const makes the structure likewise.  */
	  ఒకవేళ (రికార్డు_OR_UNION_TYPE_P (t1) && C_TYPE_FIELDS_READONLY (t1))
	    C_TYPE_FIELDS_READONLY (t) = 1;
	}

      /* Any field that is volatile means variables of this type must be
	 treated in some ways as volatile.  */
      ఒకవేళ (వృక్షం_THIS_VOLATILE (x))
	{
	  C_TYPE_FIELDS_VOLATILE (t) = 1;
	  C_TYPE_FIELDS_NON_CONSTEXPR (t) = 1;
	}

      /* Any field that is volatile, restrict-qualified or atomic
	 means the type cannot be used for a constexpr object.  */
      ఒకవేళ (TYPE_QUALS (t1)
	  & (TYPE_QUAL_VOLATILE | TYPE_QUAL_RESTRICT | TYPE_QUAL_ATOMIC))
	C_TYPE_FIELDS_NON_CONSTEXPR (t) = 1;
      లేకపోతే ఒకవేళ (రికార్డు_OR_UNION_TYPE_P (t1) && C_TYPE_FIELDS_NON_CONSTEXPR (t1))
	    C_TYPE_FIELDS_NON_CONSTEXPR (t) = 1;

      /* Any field of nominal variable size implies structure is too.  */
      ఒకవేళ (C_DECL_VARIABLE_కొలత (x))
	C_TYPE_VARIABLE_కొలత (t) = 1;

      /* If any field is variably modified, record this fact. */
      ఒకవేళ (c_type_variably_modified_p (వృక్షం_TYPE (x)))
	C_TYPE_VARIABLY_MODIFIED (t) = 1;

      ఒకవేళ (DECL_C_బిట్టు_క్షేత్రం (x))
	{
	  గుర్తులేని HOST_WIDE_INT వెడల్పు = వృక్షం_గమ్యం_uhwi (DECL_INITIAL (x));
	  DECL_కొలత (x) = bitsize_int (వెడల్పు);
	  DECL_బిట్టు_క్షేత్రం (x) = 1;
	}

      ఒకవేళ (TYPE_PACKED (t)
	  && (DECL_బిట్టు_క్షేత్రం (x)
	      || TYPE_ALIGN (వృక్షం_TYPE (x)) > బిట్లు_చొప్పున_UNIT))
	DECL_PACKED (x) = 1;

      /* Detect flexible array member in an invalid context.  */
      ఒకవేళ (flexible_array_member_type_p (వృక్షం_TYPE (x)))
	{
	  ఒకవేళ (వృక్షం_సంకేతం (t) == UNION_TYPE)
	    pedwarn (DECL_ఆధారం_LOCATION (x), OPT_Wpedantic,
		     "flexible array member in union is a GCC extension");
	  లేకపోతే ఒకవేళ (!is_చివరి_క్షేత్రం)
	    {
	      error_at (DECL_ఆధారం_LOCATION (x),
			"flexible array member not at end of struct");
	      వృక్షం_TYPE (x) = error_mark_కణుపు;
	    }
	  లేకపోతే ఒకవేళ (!saw_named_క్షేత్రం)
	    pedwarn (DECL_ఆధారం_LOCATION (x), OPT_Wpedantic,
		     "flexible array member in a struct with no named "
		     "members is a GCC extension");
	  ఒకవేళ (lookup_attribute ("counted_by", DECL_లక్షణాలు (x)))
	    C_TYPE_FIELDS_HAS_COUNTED_BY (t) = 1;
	}

      ఒకవేళ (వృక్షం_సంకేతం (వృక్షం_TYPE (x)) == సూచిక_TYPE
	  && lookup_attribute ("counted_by", DECL_లక్షణాలు (x)))
	C_TYPE_FIELDS_HAS_COUNTED_BY (t) = 1;

      /* If the field is an anonymous structure that includes a field
	 with counted_by attribute, this structure should also be marked
	 too.  */
      ఒకవేళ (రికార్డు_OR_UNION_TYPE_P (వృక్షం_TYPE (x))
	  && C_TYPE_FIELDS_HAS_COUNTED_BY (వృక్షం_TYPE (x))
	  && DECL_NAME (x) == NULL_వృక్షం
	  && c_type_ట్యాగ్ (వృక్షం_TYPE (x)) == NULL_వృక్షం)
	C_TYPE_FIELDS_HAS_COUNTED_BY (t) = 1;

      ఒకవేళ (pedantic && వృక్షం_సంకేతం (t) == రికార్డు_TYPE
	  && flexible_array_type_p (వృక్షం_TYPE (x)))
	pedwarn (DECL_ఆధారం_LOCATION (x), OPT_Wpedantic,
		 "invalid use of structure with flexible array member");

      /* Set DECL_NOT_FLEXARRAY flag for FIELD_DECL x.  */
      DECL_NOT_FLEXARRAY (x) = !is_flexible_array_member_p (is_చివరి_క్షేత్రం, x);

      /* Set TYPE_INCLUDES_FLEXARRAY for the context of x, t.
	 when x is an array and is the last field.
	 There is only one last_field for a structure type, but there might
	 be multiple last_fields for a union type, therefore we should ORed
	 the result for multiple last_fields.  */
      ఒకవేళ (వృక్షం_సంకేతం (వృక్షం_TYPE (x)) == ARRAY_TYPE)
	TYPE_INCLUDES_FLEXARRAY (t)
	  |= is_చివరి_క్షేత్రం && flexible_array_member_type_p (వృక్షం_TYPE (x));
      /* Recursively set TYPE_INCLUDES_FLEXARRAY for the context of x, t
	 when x is an union or record and is the last field.  */
      లేకపోతే ఒకవేళ (రికార్డు_OR_UNION_TYPE_P (వృక్షం_TYPE (x)))
	TYPE_INCLUDES_FLEXARRAY (t)
	  |= is_చివరి_క్షేత్రం && TYPE_INCLUDES_FLEXARRAY (వృక్షం_TYPE (x));

      ఒకవేళ (warn_flex_array_member_not_at_చివర
	  && !is_చివరి_క్షేత్రం
	  && రికార్డు_OR_UNION_TYPE_P (వృక్షం_TYPE (x))
	  && TYPE_INCLUDES_FLEXARRAY (వృక్షం_TYPE (x)))
	warning_at (DECL_ఆధారం_LOCATION (x),
		    OPT_Wflex_array_member_not_at_చివర,
		    "structure containing a flexible array member"
		    " is not at the end of another structure");

      ఒకవేళ (DECL_NAME (x)
	  || రికార్డు_OR_UNION_TYPE_P (వృక్షం_TYPE (x)))
	saw_named_క్షేత్రం = నిజం;

      ఒకవేళ (AGGREGATE_TYPE_P (వృక్షం_TYPE (x))
	  && TYPE_TYPELESS_STORAGE (వృక్షం_TYPE (x)))
	TYPE_TYPELESS_STORAGE (t) = నిజం;
    }

  detect_క్షేత్రం_duplicates (fieldlist);

  /* Now we have the nearly final fieldlist.  Record it,
     then lay out the structure or union (including the fields).  */

  TYPE_FIELDS (t) = fieldlist;

  maybe_apply_pragma_scalar_storage_క్రమం (t);

  layout_type (t);

  ఒకవేళ (TYPE_కొలత_UNIT (t)
      && వృక్షం_సంకేతం (TYPE_కొలత_UNIT (t)) == INTEGER_CST
      && !వృక్షం_అధికప్రవాహం (TYPE_కొలత_UNIT (t))
      && !valid_constant_కొలత_p (TYPE_కొలత_UNIT (t)))
    error ("type %qT is too large", t);

  /* Give bit-fields their proper types and rewrite the type of array fields
     with scalar component if the enclosing type has reverse storage order.  */
  కొరకు (వృక్షం క్షేత్రం_2 = fieldlist; క్షేత్రం_2; క్షేత్రం_2 = DECL_CHAIN (క్షేత్రం_2))
    {
      ఒకవేళ (వృక్షం_సంకేతం (క్షేత్రం_2) == క్షేత్రం_DECL
	  && DECL_INITIAL (క్షేత్రం_2)
	  && వృక్షం_TYPE (క్షేత్రం_2) != error_mark_కణుపు)
	{
	  గుర్తులేని HOST_WIDE_INT వెడల్పు
	    = వృక్షం_గమ్యం_uhwi (DECL_INITIAL (క్షేత్రం_2));
	  వృక్షం type = వృక్షం_TYPE (క్షేత్రం_2);
	  ఒకవేళ (సదిశ_TYPE_P (type))
	    {
	      error_at (DECL_ఆధారం_LOCATION (క్షేత్రం_2),
			"bit-field %qD has invalid type", క్షేత్రం_2);
	      type = వృక్షం_TYPE (type);
	      వృక్షం_TYPE (క్షేత్రం_2) = type;
	    }
	  ఒకవేళ (వెడల్పు != TYPE_PRECISION (type))
	    {
	      ఒకవేళ (BITINT_TYPE_P (type)
		  && వెడల్పు >= ((TYPE_UNSIGNED (type) || flag_isoc2y) ? 1 : 2))
		వృక్షం_TYPE (క్షేత్రం_2)
		  = build_bitint_type (వెడల్పు, TYPE_UNSIGNED (type));
	      లేకపోతే
		వృక్షం_TYPE (క్షేత్రం_2)
		  = c_build_bitfield_integer_type (వెడల్పు,
						   TYPE_UNSIGNED (type));
	      ఒకవేళ (వృక్షం attr = c_hardbool_type_attr (type))
		decl_లక్షణాలు (&వృక్షం_TYPE (క్షేత్రం_2),
				 copy_list (attr),
				 0, NULL_వృక్షం);
	      సమితి_DECL_బహుళకం (క్షేత్రం_2, TYPE_బహుళకం (వృక్షం_TYPE (క్షేత్రం_2)));
	    }
	  DECL_INITIAL (క్షేత్రం_2) = NULL_వృక్షం;
	}
      లేకపోతే ఒకవేళ (TYPE_తిరగేయి_STORAGE_క్రమం (t)
	       && వృక్షం_సంకేతం (క్షేత్రం_2) == క్షేత్రం_DECL
	       && వృక్షం_సంకేతం (వృక్షం_TYPE (క్షేత్రం_2)) == ARRAY_TYPE)
	{
	  వృక్షం ftype = వృక్షం_TYPE (క్షేత్రం_2);
	  వృక్షం ctype = strip_array_types (ftype);
	  ఒకవేళ (!రికార్డు_OR_UNION_TYPE_P (ctype) && TYPE_బహుళకం (ctype) != QImode)
	    {
	      వృక్షం fmain_type = TYPE_MAIN_VARIANT (ftype);
	      వృక్షం *typep = &fmain_type;
	      చేయి {
		*typep = build_distinct_type_copy (*typep);
		TYPE_తిరగేయి_STORAGE_క్రమం (*typep) = 1;
		typep = &వృక్షం_TYPE (*typep);
	      } అయితే (వృక్షం_సంకేతం (*typep) == ARRAY_TYPE);
	      వృక్షం_TYPE (క్షేత్రం_2)
		= c_build_qualified_type (fmain_type, TYPE_QUALS (ftype));
	    }
	}

      /* Warn on problematic type punning for storage order purposes.  */
      ఒకవేళ (వృక్షం_సంకేతం (t) == UNION_TYPE
	  && వృక్షం_సంకేతం (క్షేత్రం_2) == క్షేత్రం_DECL
	  && AGGREGATE_TYPE_P (వృక్షం_TYPE (క్షేత్రం_2)))
	{
	  వృక్షం ftype = వృక్షం_TYPE (క్షేత్రం_2);
	  ఒకవేళ (వృక్షం_సంకేతం (ftype) == ARRAY_TYPE)
	    ftype = strip_array_types (ftype);
	  ఒకవేళ (రికార్డు_OR_UNION_TYPE_P (ftype)
	      && TYPE_తిరగేయి_STORAGE_క్రమం (ftype)
		 != TYPE_తిరగేయి_STORAGE_క్రమం (t))
	    warning_at (DECL_ఆధారం_LOCATION (క్షేత్రం_2),
			OPT_Wscalar_storage_క్రమం,
			"type punning toggles scalar storage order");
	}
    }

  /* Now we have the truly final field list.
     Store it in this type and in the variants.  */

  TYPE_FIELDS (t) = fieldlist;

  /* If there are lots of fields, sort so we can look through them fast.
     We arbitrarily consider 16 or more elts to be "a lot".  */

  {
    పూర్ణాంకం len = 0;

    కొరకు (x = fieldlist; x; x = DECL_CHAIN (x))
      {
	ఒకవేళ (len > 15 || DECL_NAME (x) == ఖాళీ)
	  ఆపు;
	len += 1;
      }

    ఒకవేళ (len > 15)
      {
	వృక్షం *క్షేత్రం_array;
	నిర్మాణం lang_type *space;
	నిర్మాణం sorted_fields_type *space2;

	len += list_నిడివి (x);

	/* Use the same allocation policy here that make_node uses, to
	   ensure that this lives as long as the rest of the struct decl.
	   All decls in an inline function need to be saved.  */

	space = ((నిర్మాణం lang_type *)
		 ggc_అంతర్గత_cleared_alloc (c_dialect_objc ()
					     ? పరిమాణం (నిర్మాణం lang_type)
					     : offsetof (నిర్మాణం lang_type,
							 info)));
	space2 = ((sorted_fields_type *)
		  ggc_అంతర్గత_alloc (పరిమాణం (నిర్మాణం sorted_fields_type)
				      + len * పరిమాణం (వృక్షం)));

	len = 0;
	space->s = space2;
	క్షేత్రం_array = &space2->elts[0];
	కొరకు (x = fieldlist; x; x = DECL_CHAIN (x))
	  {
	    క్షేత్రం_array[len++] = x;

	    /* If there is anonymous struct or union, break out of the loop.  */
	    ఒకవేళ (DECL_NAME (x) == ఖాళీ)
	      ఆపు;
	  }
	/* Found no anonymous struct/union.  Add the TYPE_LANG_SPECIFIC.  */
	ఒకవేళ (x == ఖాళీ)
	  {
	    TYPE_LANG_SPECIFIC (t) = space;
	    TYPE_LANG_SPECIFIC (t)->s->len = len;
	    క్షేత్రం_array = TYPE_LANG_SPECIFIC (t)->s->elts;
	    qsort (క్షేత్రం_array, len, పరిమాణం (వృక్షం), క్షేత్రం_decl_cmp);
	  }
      }
  }

  /* If this was supposed to be a transparent union, but we can't
     make it one, warn and turn off the flag.  */
  ఒకవేళ (వృక్షం_సంకేతం (t) == UNION_TYPE
      && TYPE_TRANSPARENT_AGGR (t)
      && (!TYPE_FIELDS (t) || TYPE_బహుళకం (t) != DECL_బహుళకం (TYPE_FIELDS (t))))
    {
      TYPE_TRANSPARENT_AGGR (t) = 0;
      warning_at (loc, 0, "union cannot be made transparent");
    }

  వృక్షం incomplete_vars = C_TYPE_INCOMPLETE_VARS (TYPE_MAIN_VARIANT (t));
  కొరకు (x = TYPE_MAIN_VARIANT (t); x; x = TYPE_తదుపరి_VARIANT (x))
    {
      TYPE_FIELDS (x) = TYPE_FIELDS (t);
      TYPE_LANG_SPECIFIC (x) = TYPE_LANG_SPECIFIC (t);
      TYPE_TRANSPARENT_AGGR (x) = TYPE_TRANSPARENT_AGGR (t);
      TYPE_TYPELESS_STORAGE (x) = TYPE_TYPELESS_STORAGE (t);
      C_TYPE_FIELDS_READONLY (x) = C_TYPE_FIELDS_READONLY (t);
      C_TYPE_FIELDS_VOLATILE (x) = C_TYPE_FIELDS_VOLATILE (t);
      C_TYPE_FIELDS_NON_CONSTEXPR (x) = C_TYPE_FIELDS_NON_CONSTEXPR (t);
      C_TYPE_FIELDS_HAS_COUNTED_BY (x) = C_TYPE_FIELDS_HAS_COUNTED_BY (t);
      C_TYPE_VARIABLE_కొలత (x) = C_TYPE_VARIABLE_కొలత (t);
      C_TYPE_VARIABLY_MODIFIED (x) = C_TYPE_VARIABLY_MODIFIED (t);
      C_TYPE_INCOMPLETE_VARS (x) = NULL_వృక్షం;
      TYPE_INCLUDES_FLEXARRAY (x) = TYPE_INCLUDES_FLEXARRAY (t);
    }

  /* Check for consistency with previous definition.  */
  ఒకవేళ (flag_isoc23 && ఖాళీ != enclosing_struct_parse_info)
    {
      వృక్షం vistype = మునుపటి_ట్యాగ్ (t);
      ఒకవేళ (vistype
	  && వృక్షం_సంకేతం (vistype) == వృక్షం_సంకేతం (t)
	  && !C_TYPE_BEING_DEFINED (vistype))
	{
	  TYPE_STUB_DECL (t) = TYPE_STUB_DECL (vistype);
	  ఒకవేళ (c_type_variably_modified_p (t))
	    {
	      error ("redefinition of struct or union %qT with variably "
		     "modified type", t);
	      ఒకవేళ (struct_parse_info->refloc != UNKNOWN_LOCATION)
		inform (struct_parse_info->refloc, "originally defined here");
	    }
	  లేకపోతే ఒకవేళ (!comptypes_same_p (t, vistype))
	    {
	      error ("redefinition of struct or union %qT", t);
	      ఒకవేళ (struct_parse_info->refloc != UNKNOWN_LOCATION)
		inform (struct_parse_info->refloc, "originally defined here");
	    }
	}
    }

  C_TYPE_BEING_DEFINED (t) = 0;

  ఒకవేళ (lookup_attribute ("may_alias", TYPE_లక్షణాలు (t)))
    కొరకు (x = TYPE_MAIN_VARIANT (t); x; x = TYPE_తదుపరి_VARIANT (x))
      c_fixup_may_alias (x);

  /* Set type canonical based on equivalence class.  */
  ఒకవేళ (flag_isoc23 && !C_TYPE_VARIABLE_కొలత (t))
    {
      ఒకవేళ (c_struct_htab == ఖాళీ)
	c_struct_htab = hash_పట్టిక<c_struct_hasher>::create_ggc (61);

      hashval_t hash = c_struct_hasher::hash (t);

      gcc_checking_assert (TYPE_STRUCTURAL_EQUALITY_P (t));
      gcc_checking_assert (!TYPE_NAME (t)
			   || వృక్షం_సంకేతం (TYPE_NAME (t)) == IDENTIFIER_కణుపు);

      వృక్షం *e = c_struct_htab->కనుగొను_స్థానం_with_hash (t, hash, చొప్పించు);
      ఒకవేళ (*e)
	TYPE_CANONICAL (t) = TYPE_CANONICAL (*e);
      లేకపోతే
	{
	  TYPE_CANONICAL (t) = c_type_canonical (t);
	  *e = t;
	}
      c_update_type_canonical (t);
    }

  /* Update type location to the one of the definition, instead of e.g.
     a forward declaration.  */
  ఒకవేళ (TYPE_STUB_DECL (t))
    DECL_ఆధారం_LOCATION (TYPE_STUB_DECL (t)) = loc;

  /* Finish debugging output for this type.  */
  rest_యొక్క_type_compilation (t, toplevel);

  ముగింపు_incomplete_vars (incomplete_vars, toplevel);


  ఒకవేళ (c_type_variably_modified_p (t))
    {
      c_update_variably_modified (t);
      /* Make sure a DECL_EXPR is created for structs with VLA members.
	 Because we do not know the context, we always pass expr
	 to force creation of a BIND_EXPR which is required in some
	 contexts.  */
      కూడు_decl_సమాసం (loc, t, సమాసం, అబద్ధం);
    }

  ఒకవేళ (warn_cxx_compat)
    warn_cxx_compat_ముగింపు_struct (fieldlist, వృక్షం_సంకేతం (t), loc);

  ఒకవేళ (ఖాళీ != enclosing_struct_parse_info)
    {
      తొలగించు struct_parse_info;

      struct_parse_info = enclosing_struct_parse_info;

      /* If this struct is defined inside a struct, add it to
	 struct_types.  */
      ఒకవేళ (warn_cxx_compat
	  && struct_parse_info != ఖాళీ
	  && !లోపల_sizeof && !లోపల_typeof && !లోపల_alignof && !లోపల_countof)
	struct_parse_info->struct_types.సురక్షిత_నెట్టు (t);
     }

  /* Only when the enclosing struct/union type is not anonymous, do more
     verification on the fields with counted_by attributes.  */
  ఒకవేళ (C_TYPE_FIELDS_HAS_COUNTED_BY (t) && c_type_ట్యాగ్ (t) != NULL_వృక్షం)
    verify_counted_by_attribute (t, t);

  తిరిగి t;
}

స్థిర నిర్మాణం {
  gt_సూచిక_operator new_విలువ;
  శూన్య *cookie;
} resort_దత్తాంశం;

/* This routine compares two fields like field_decl_cmp but using the
pointer operator in resort_data.  */

స్థిర పూర్ణాంకం
resort_క్షేత్రం_decl_cmp (స్థిరరాశి శూన్య *x_p, స్థిరరాశి శూన్య *y_p)
{
  స్థిరరాశి వృక్షం *స్థిరరాశి x = (స్థిరరాశి వృక్షం *) x_p;
  స్థిరరాశి వృక్షం *స్థిరరాశి y = (స్థిరరాశి వృక్షం *) y_p;

  ఒకవేళ (DECL_NAME (*x) == DECL_NAME (*y))
    /* A nontype is "greater" than a type.  */
    తిరిగి (వృక్షం_సంకేతం (*y) == TYPE_DECL) - (వృక్షం_సంకేతం (*x) == TYPE_DECL);
  ఒకవేళ (DECL_NAME (*x) == NULL_వృక్షం)
    తిరిగి -1;
  ఒకవేళ (DECL_NAME (*y) == NULL_వృక్షం)
    తిరిగి 1;
  {
    వృక్షం d1 = DECL_NAME (*x);
    వృక్షం d2 = DECL_NAME (*y);
    resort_దత్తాంశం.new_విలువ (&d1, &d1, resort_దత్తాంశం.cookie);
    resort_దత్తాంశం.new_విలువ (&d2, &d2, resort_దత్తాంశం.cookie);
    ఒకవేళ (d1 < d2)
      తిరిగి -1;
  }
  తిరిగి 1;
}

/* Resort DECL_SORTED_FIELDS because pointers have been reordered.  */

శూన్య
resort_sorted_fields (శూన్య *obj,
		      శూన్య * ARG_వాడని (orig_obj),
		      gt_సూచిక_operator new_విలువ,
		      శూన్య *cookie)
{
  నిర్మాణం sorted_fields_type *sf = (నిర్మాణం sorted_fields_type *) obj;
  resort_దత్తాంశం.new_విలువ = new_విలువ;
  resort_దత్తాంశం.cookie = cookie;
  qsort (&sf->elts[0], sf->len, పరిమాణం (వృక్షం),
	 resort_క్షేత్రం_decl_cmp);
}

/* Lay out the type T, and its element type, and so on.  */

స్థిర శూన్య
layout_array_type (వృక్షం t)
{
  ఒకవేళ (వృక్షం_సంకేతం (వృక్షం_TYPE (t)) == ARRAY_TYPE)
    layout_array_type (వృక్షం_TYPE (t));
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

వృక్షం
ప్రారంభం_enum (location_t loc, నిర్మాణం c_enum_contents *the_enum, వృక్షం name,
	    వృక్షం fixed_underlying_type, తార్కిక potential_nesting_p)
{
  వృక్షం enumtype = NULL_వృక్షం;
  location_t enumloc = UNKNOWN_LOCATION;

  /* If this is the real definition for a previous forward reference,
     fill in the contents in the same object that used to be the
     forward reference.  */

  ఒకవేళ (name != NULL_వృక్షం)
    enumtype = lookup_ట్యాగ్ (ENUMERAL_TYPE, name, నిజం, &enumloc);

  ఒకవేళ (enumtype != NULL_వృక్షం && వృక్షం_సంకేతం (enumtype) == ENUMERAL_TYPE)
    {
      /* If the type is currently being defined or if we have seen an
	 incomplete version which is now complete, this is a nested
	 redefinition.  The later happens if the redefinition occurs
	 inside the enum specifier itself.  */
      ఒకవేళ (C_TYPE_BEING_DEFINED (enumtype)
	  || (potential_nesting_p && TYPE_విలువలు (enumtype) != NULL_వృక్షం))
	error_at (loc, "nested redefinition of %<enum %E%>", name);

      /* For C23 we allow redefinitions.  We set to zero and check for
	 consistency later.  */
      ఒకవేళ (flag_isoc23 && TYPE_విలువలు (enumtype) != NULL_వృక్షం)
	enumtype = NULL_వృక్షం;
    }

  ఒకవేళ (enumtype == NULL_వృక్షం || వృక్షం_సంకేతం (enumtype) != ENUMERAL_TYPE)
    {
      enumtype = make_కణుపు (ENUMERAL_TYPE);
      TYPE_కొలత (enumtype) = NULL_వృక్షం;
      సమితి_TYPE_STRUCTURAL_EQUALITY (enumtype);
      pushtag (loc, name, enumtype);
      ఒకవేళ (fixed_underlying_type != NULL_వృక్షం)
	{
	  /* For an enum definition with a fixed underlying type, the
	     type is complete during the definition and the
	     enumeration constants have that type.  If there was a
	     tag, the type was completed in c_parser_enum_specifier.
	     If not, it must be completed here.  */
	  ENUM_FIXED_UNDERLYING_TYPE_P (enumtype) = నిజం;
	  TYPE_MIN_విలువ (enumtype) = TYPE_MIN_విలువ (fixed_underlying_type);
	  TYPE_MAX_విలువ (enumtype) = TYPE_MAX_విలువ (fixed_underlying_type);
	  TYPE_UNSIGNED (enumtype) = TYPE_UNSIGNED (fixed_underlying_type);
	  సమితి_TYPE_ALIGN (enumtype, TYPE_ALIGN (fixed_underlying_type));
	  TYPE_కొలత (enumtype) = NULL_వృక్షం;
	  TYPE_PRECISION (enumtype) = TYPE_PRECISION (fixed_underlying_type);
	  ENUM_UNDERLYING_TYPE (enumtype) = fixed_underlying_type;
	  TYPE_CANONICAL (enumtype) = TYPE_CANONICAL (fixed_underlying_type);
	  c_update_type_canonical (enumtype);
	  layout_type (enumtype);
	}
    }
  /* Update type location to the one of the definition, instead of e.g.
     a forward declaration.  */
  లేకపోతే ఒకవేళ (TYPE_STUB_DECL (enumtype))
    {
      enumloc = DECL_ఆధారం_LOCATION (TYPE_STUB_DECL (enumtype));
      DECL_ఆధారం_LOCATION (TYPE_STUB_DECL (enumtype)) = loc;
    }

  C_TYPE_BEING_DEFINED (enumtype) = 1;

  ఒకవేళ (TYPE_విలువలు (enumtype) != NULL_వృక్షం)
    {
      /* This enum is a named one that has been declared already.  */
      auto_diagnostic_సమూహం d;
      error_at (loc, "redeclaration of %<enum %E%>", name);
      ఒకవేళ (enumloc != UNKNOWN_LOCATION)
	inform (enumloc, "originally defined here");

      /* Completely replace its old definition.
	 The old enumerators remain defined, however.  */
      TYPE_విలువలు (enumtype) = NULL_వృక్షం;
    }

  ఒకవేళ (ENUM_FIXED_UNDERLYING_TYPE_P (enumtype)
      && fixed_underlying_type == NULL_వృక్షం)
    {
      error_at (loc, "%<enum%> declared with but defined without "
		"fixed underlying type");
      ENUM_FIXED_UNDERLYING_TYPE_P (enumtype) = అబద్ధం;
    }

  the_enum->enum_తదుపరి_విలువ = integer_zero_కణుపు;
  the_enum->enum_type = enumtype;
  the_enum->enum_అధికప్రవాహం = 0;

  ఒకవేళ (flag_short_enums && !ENUM_FIXED_UNDERLYING_TYPE_P (enumtype))
    కొరకు (వృక్షం v = TYPE_MAIN_VARIANT (enumtype); v; v = TYPE_తదుపరి_VARIANT (v))
      TYPE_PACKED (v) = 1;

  /* FIXME: This will issue a warning for a use of a type defined
     within sizeof in a statement expr.  This is not terribly serious
     as C++ doesn't permit statement exprs within sizeof anyhow.  */
  ఒకవేళ (warn_cxx_compat
      && (లోపల_sizeof || లోపల_typeof || లోపల_alignof || లోపల_countof))
    warning_at (loc, OPT_Wc___compat,
		"defining type in %qs expression is invalid in C++",
		(లోపల_sizeof ? "sizeof"
		 : లోపల_typeof ? "typeof"
		 : లోపల_alignof ? "alignof"
		 : "_Countof"));

  ఒకవేళ (లోపల_underspecified_init)
    error_at (loc, "%qT defined in underspecified object initializer",
	      enumtype);

  తిరిగి enumtype;
}

/* After processing and defining all the values of an enumeration type,
   install their decls in the enumeration type and finish it off.
   ENUMTYPE is the type object, VALUES a list of decl-value pairs,
   and ATTRIBUTES are the specified attributes.
   Returns ENUMTYPE.  */

వృక్షం
ముగింపు_enum (వృక్షం enumtype, వృక్షం విలువలు, వృక్షం లక్షణాలు)
{
  వృక్షం pair, tem;
  వృక్షం minnode = NULL_వృక్షం, maxnode = NULL_వృక్షం;
  పూర్ణాంకం precision;
  signop sign;
  తార్కిక toplevel = (file_scope == current_scope);
  నిర్మాణం lang_type *lt;

  decl_లక్షణాలు (&enumtype, లక్షణాలు, (పూర్ణాంకం) ATTR_FLAG_TYPE_లోపల_ఉంచు);

  /* Calculate the maximum value of any enumerator in this type.  */

  ఒకవేళ (విలువలు == error_mark_కణుపు)
    minnode = maxnode = integer_zero_కణుపు;
  లేకపోతే
    {
      minnode = maxnode = వృక్షం_విలువ (విలువలు);
      కొరకు (pair = వృక్షం_CHAIN (విలువలు); pair; pair = వృక్షం_CHAIN (pair))
	{
	  వృక్షం విలువ = వృక్షం_విలువ (pair);
	  ఒకవేళ (వృక్షం_int_cst_lt (maxnode, విలువ))
	    maxnode = విలువ;
	  ఒకవేళ (వృక్షం_int_cst_lt (విలువ, minnode))
	    minnode = విలువ;
	}
    }

  /* Construct the final type of this enumeration.  It is the same
     as one of the integral types - the narrowest one that fits, except
     that normally we only go as narrow as int - and signed iff any of
     the values are negative.  */
  sign = (వృక్షం_int_cst_sgn (minnode) >= 0) ? UNSIGNED : SIGNED;
  precision = MAX (వృక్షం_int_cst_min_precision (minnode, sign),
		   వృక్షం_int_cst_min_precision (maxnode, sign));

  తార్కిక wider_than_int =
    (వృక్షం_int_cst_lt (minnode, TYPE_MIN_విలువ (integer_type_కణుపు))
     || వృక్షం_int_cst_lt (TYPE_MAX_విలువ (integer_type_కణుపు), maxnode));


  ఒకవేళ (!ENUM_FIXED_UNDERLYING_TYPE_P (enumtype))
    {
      /* If the precision of the type was specified with an attribute and it
	 was too small, give an error.  Otherwise, use it.  */
      ఒకవేళ (TYPE_PRECISION (enumtype) && lookup_attribute ("mode", లక్షణాలు))
	{
	  ఒకవేళ (precision > TYPE_PRECISION (enumtype))
	    {
	      TYPE_PRECISION (enumtype) = 0;
	      error ("specified mode too small for enumerated values");
	    }
	  లేకపోతే
	    precision = TYPE_PRECISION (enumtype);
	}
      లేకపోతే
	TYPE_PRECISION (enumtype) = 0;

      ఒకవేళ (TYPE_PACKED (enumtype)
	  || precision > TYPE_PRECISION (integer_type_కణుపు)
	  || TYPE_PRECISION (enumtype))
	{
	  tem = c_common_type_for_కొలత (precision, sign == UNSIGNED ? 1 : 0);
	  ఒకవేళ (tem == ఖాళీ)
	    {
	      /* This should only occur when both signed and unsigned
		 values of maximum precision occur among the
		 enumerators.  */
	      pedwarn (ఆదానం_location, 0,
		       "enumeration values exceed range of largest integer");
	      tem = widest_integer_literal_type_కణుపు;
	    }
	  లేకపోతే ఒకవేళ (precision > TYPE_PRECISION (intmax_type_కణుపు)
		   && !వృక్షం_int_cst_lt (minnode,
					TYPE_MIN_విలువ (intmax_type_కణుపు))
		   && !వృక్షం_int_cst_lt (TYPE_MAX_విలువ (uintmax_type_కణుపు),
					maxnode))
	    pedwarn (ఆదానం_location, OPT_Wpedantic,
		     "enumeration values exceed range of %qs",
		     sign == UNSIGNED ? "uintmax_t" : "intmax_t");
	}
      లేకపోతే
	tem = sign == UNSIGNED ? unsigned_type_కణుపు : integer_type_కణుపు;

      TYPE_MIN_విలువ (enumtype) = TYPE_MIN_విలువ (tem);
      TYPE_MAX_విలువ (enumtype) = TYPE_MAX_విలువ (tem);
      TYPE_UNSIGNED (enumtype) = TYPE_UNSIGNED (tem);
      సమితి_TYPE_ALIGN (enumtype, TYPE_ALIGN (tem));
      TYPE_కొలత (enumtype) = NULL_వృక్షం;
      TYPE_PRECISION (enumtype) = TYPE_PRECISION (tem);
      ENUM_UNDERLYING_TYPE (enumtype) =
	c_common_type_for_కొలత (TYPE_PRECISION (tem), TYPE_UNSIGNED (tem));

      TYPE_CANONICAL (enumtype) =
	TYPE_CANONICAL (ENUM_UNDERLYING_TYPE (enumtype));
      c_update_type_canonical (enumtype);

      layout_type (enumtype);
    }

  ఒకవేళ (విలువలు != error_mark_కణుపు)
    {
      /* Change the type of the enumerators to be the enum type.  We
	 need to do this irrespective of the size of the enum, for
	 proper type checking.  Replace the DECL_INITIALs of the
	 enumerators, and the value slots of the list, with copies
	 that have the enum type; they cannot be modified in place
	 because they may be shared (e.g.  integer_zero_node) Finally,
	 change the purpose slots to point to the names of the decls.  */
      కొరకు (pair = విలువలు; pair; pair = వృక్షం_CHAIN (pair))
	{
	  వృక్షం enu = వృక్షం_PURPOSE (pair);
	  వృక్షం ini = DECL_INITIAL (enu);

	  వృక్షం_TYPE (enu) = enumtype;

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
	  ఒకవేళ (!ENUM_FIXED_UNDERLYING_TYPE_P (enumtype) && wider_than_int)
	    ini = convert (enumtype, ini);

	  DECL_INITIAL (enu) = ini;
	  వృక్షం_PURPOSE (pair) = DECL_NAME (enu);
	  /* To match the C++ FE, store the CONST_DECL rather than just its
	     value.  */
	  వృక్షం_విలువ (pair) = enu;
	}

      TYPE_విలువలు (enumtype) = విలువలు;
    }

  /* Record the min/max values so that we can warn about bit-field
     enumerations that are too small for the values.  */
  lt = ((నిర్మాణం lang_type *)
	ggc_అంతర్గత_cleared_alloc (c_dialect_objc ()
				    ? పరిమాణం (నిర్మాణం lang_type)
				    : offsetof (నిర్మాణం lang_type, info)));
  lt->enum_min = minnode;
  lt->enum_max = maxnode;
  TYPE_LANG_SPECIFIC (enumtype) = lt;

  /* Fix up all variant types of this enum type.  */
  వృక్షం incomplete_vars = C_TYPE_INCOMPLETE_VARS (TYPE_MAIN_VARIANT (enumtype));
  కొరకు (tem = TYPE_MAIN_VARIANT (enumtype); tem; tem = TYPE_తదుపరి_VARIANT (tem))
    {
      C_TYPE_INCOMPLETE_VARS (tem) = NULL_వృక్షం;
      ఒకవేళ (tem == enumtype)
	కొనసాగు;
      TYPE_విలువలు (tem) = TYPE_విలువలు (enumtype);
      TYPE_MIN_విలువ (tem) = TYPE_MIN_విలువ (enumtype);
      TYPE_MAX_విలువ (tem) = TYPE_MAX_విలువ (enumtype);
      TYPE_కొలత (tem) = TYPE_కొలత (enumtype);
      TYPE_కొలత_UNIT (tem) = TYPE_కొలత_UNIT (enumtype);
      సమితి_TYPE_బహుళకం (tem, TYPE_బహుళకం (enumtype));
      TYPE_PRECISION (tem) = TYPE_PRECISION (enumtype);
      సమితి_TYPE_ALIGN (tem, TYPE_ALIGN (enumtype));
      TYPE_USER_ALIGN (tem) = TYPE_USER_ALIGN (enumtype);
      TYPE_UNSIGNED (tem) = TYPE_UNSIGNED (enumtype);
      TYPE_LANG_SPECIFIC (tem) = TYPE_LANG_SPECIFIC (enumtype);
      ENUM_UNDERLYING_TYPE (tem) = ENUM_UNDERLYING_TYPE (enumtype);
      TYPE_PACKED (tem) = TYPE_PACKED (enumtype);
    }

  /* Finish debugging output for this type.  */
  rest_యొక్క_type_compilation (enumtype, toplevel);

  ముగింపు_incomplete_vars (incomplete_vars, toplevel);

  /* If this enum is defined inside a struct, add it to
     struct_types.  */
  ఒకవేళ (warn_cxx_compat
      && struct_parse_info != ఖాళీ
      && !లోపల_sizeof && !లోపల_typeof && !లోపల_alignof && !లోపల_countof)
    struct_parse_info->struct_types.సురక్షిత_నెట్టు (enumtype);

  /* Check for consistency with previous definition */
  ఒకవేళ (flag_isoc23)
    {
      వృక్షం vistype = మునుపటి_ట్యాగ్ (enumtype);
      ఒకవేళ (vistype
	  && వృక్షం_సంకేతం (vistype) == వృక్షం_సంకేతం (enumtype)
	  && !C_TYPE_BEING_DEFINED (vistype))
	{
	  TYPE_STUB_DECL (enumtype) = TYPE_STUB_DECL (vistype);
	  ఒకవేళ (!comptypes_same_p (enumtype, vistype))
	    error("conflicting redefinition of enum %qT", enumtype);
	}
    }

  C_TYPE_BEING_DEFINED (enumtype) = 0;

  తిరిగి enumtype;
}

/* Build and install a CONST_DECL for one value of the
   current enumeration type (one that was begun with start_enum).
   DECL_LOC is the location of the enumerator.
   LOC is the location of the '=' operator if any, DECL_LOC otherwise.
   Return a tree-list containing the CONST_DECL and its value.
   Assignment of sequential values by default is handled here.  */

వృక్షం
build_enumerator (location_t decl_loc, location_t loc,
		  నిర్మాణం c_enum_contents *the_enum, వృక్షం name, వృక్షం విలువ)
{
  వృక్షం decl;
  వృక్షం old_decl;

  /* Validate and default VALUE.  */

  ఒకవేళ (విలువ != NULL_వృక్షం)
    {
      /* Don't issue more errors for error_mark_node (i.e. an
	 undeclared identifier) - just ignore the value expression.  */
      ఒకవేళ (విలువ == error_mark_కణుపు)
	విలువ = NULL_వృక్షం;
      లేకపోతే ఒకవేళ (!INTEGRAL_TYPE_P (వృక్షం_TYPE (విలువ)))
	{
	  error_at (loc, "enumerator value for %qE is not an integer constant",
		    name);
	  విలువ = NULL_వృక్షం;
	}
      లేకపోతే
	{
	  ఒకవేళ (వృక్షం_సంకేతం (విలువ) != INTEGER_CST)
	    {
	      విలువ = c_fully_fold (విలువ, అబద్ధం, ఖాళీ);
	      ఒకవేళ (వృక్షం_సంకేతం (విలువ) == INTEGER_CST)
		pedwarn (loc, OPT_Wpedantic,
			 "enumerator value for %qE is not an integer "
			 "constant expression", name);
	    }
	  ఒకవేళ (వృక్షం_సంకేతం (విలువ) != INTEGER_CST)
	    {
	      error ("enumerator value for %qE is not an integer constant",
		     name);
	      విలువ = NULL_వృక్షం;
	    }
	  లేకపోతే
	    {
	      విలువ = default_conversion (విలువ);
	      constant_వ్యక్తీకరణ_warning (విలువ);
	    }
	}
    }

  /* Default based on previous value.  */
  /* It should no longer be possible to have NON_LVALUE_EXPR
     in the default.  */
  ఒకవేళ (విలువ == NULL_వృక్షం)
    {
      విలువ = the_enum->enum_తదుపరి_విలువ;
      ఒకవేళ (the_enum->enum_అధికప్రవాహం)
	error_at (loc, "overflow in enumeration values");
    }
  ఒకవేళ (ENUM_FIXED_UNDERLYING_TYPE_P (the_enum->enum_type))
    {
      /* Enumeration constants must fit in the fixed underlying type.  */
      ఒకవేళ (!int_సరిపోతుంది_type_p (విలువ, ENUM_UNDERLYING_TYPE (the_enum->enum_type)))
	error_at (loc,
		  "enumerator value outside the range of underlying type");
      /* Enumeration constants for an enum with fixed underlying type
	 have the enum type, both inside and outside the
	 definition.  */
      విలువ = convert (the_enum->enum_type, విలువ);
    }
  లేకపోతే ఒకవేళ (flag_isoc23
	   && (old_decl = lookup_name_లోపల_scope (name, current_scope))
	   && old_decl != error_mark_కణుపు
	   && వృక్షం_TYPE (old_decl)
	   && వృక్షం_TYPE (వృక్షం_TYPE (old_decl))
	   && వృక్షం_సంకేతం (old_decl) == CONST_DECL)
    {
      /* Enumeration constants in a redeclaration have the previous type.  */
      వృక్షం మునుపటి_type = వృక్షం_TYPE (DECL_INITIAL (old_decl));
      ఒకవేళ (!int_సరిపోతుంది_type_p (విలువ, మునుపటి_type))
	{
	  error_at (loc, "value of redeclared enumerator outside the range "
			 "of %qT", మునుపటి_type);
	  locate_old_decl (old_decl);
	}
      విలువ = convert (మునుపటి_type, విలువ);
    }
  లేకపోతే
    {
      /* Even though the underlying type of an enum is unspecified, the
	 type of enumeration constants is explicitly defined as int
	 (6.4.4.3/2 in the C99 Standard).  C23 allows any integer type, and
	 GCC allows such types for older standards as an extension.  */
      తార్కిక warned_range = అబద్ధం;
      ఒకవేళ (!int_సరిపోతుంది_type_p (విలువ,
			    (TYPE_UNSIGNED (వృక్షం_TYPE (విలువ))
			     ? uintmax_type_కణుపు
			     : intmax_type_కణుపు)))
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
				TYPE_UNSIGNED (వృక్షం_TYPE (విలువ))
				? "uintmax_t"
				: "intmax_t");
      ఒకవేళ (!warned_range && !int_సరిపోతుంది_type_p (విలువ, integer_type_కణుపు))
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
      ఒకవేళ (int_సరిపోతుంది_type_p (విలువ, integer_type_కణుపు))
	విలువ = convert (integer_type_కణుపు, విలువ);
    }

  /* Set basis for default for next value.  */
  ఒకవేళ (ENUM_FIXED_UNDERLYING_TYPE_P (the_enum->enum_type))
    {
      వృక్షం underlying_type = ENUM_UNDERLYING_TYPE (the_enum->enum_type);
      ఒకవేళ (వృక్షం_సంకేతం (underlying_type) == BOOLEAN_TYPE)
	/* A value of 2 following a value of 1 overflows bool, but we
	   cannot carry out addition directly on bool without
	   promotion, and converting the result of arithmetic in a
	   wider type back to bool would not produce the right result
	   for this overflow check.  */
	the_enum->enum_తదుపరి_విలువ = invert_truthvalue_loc (loc, విలువ);
      లేకపోతే
	the_enum->enum_తదుపరి_విలువ
	  = build_ద్విమాన_op (సమాసం_LOC_OR_LOC (విలువ, ఆదానం_location),
			     PLUS_సమాసం, convert (underlying_type, విలువ),
			     convert (underlying_type, integer_one_కణుపు),
			     అబద్ధం);
    }
  లేకపోతే
    {
      /* In a redeclaration the type can already be the enumeral type.  */
      ఒకవేళ (వృక్షం_సంకేతం (వృక్షం_TYPE (విలువ)) == ENUMERAL_TYPE)
	విలువ = convert (ENUM_UNDERLYING_TYPE (వృక్షం_TYPE (విలువ)), విలువ);
      the_enum->enum_తదుపరి_విలువ
	= build_ద్విమాన_op (సమాసం_LOC_OR_LOC (విలువ, ఆదానం_location),
			   PLUS_సమాసం, విలువ, integer_one_కణుపు, అబద్ధం);
    }
  the_enum->enum_అధికప్రవాహం = వృక్షం_int_cst_lt (the_enum->enum_తదుపరి_విలువ, విలువ);
  ఒకవేళ (the_enum->enum_అధికప్రవాహం
      && !ENUM_FIXED_UNDERLYING_TYPE_P (the_enum->enum_type))
    {
      /* Choose a wider type with the same signedness if
	 available.  */
      పూర్ణాంకం prec = TYPE_PRECISION (వృక్షం_TYPE (విలువ)) + 1;
      తార్కిక unsignedp = TYPE_UNSIGNED (వృక్షం_TYPE (విలువ));
      వృక్షం new_type = (unsignedp
		       ? long_unsigned_type_కణుపు
		       : long_integer_type_కణుపు);
      ఒకవేళ (prec > TYPE_PRECISION (new_type))
	new_type = (unsignedp
		    ? long_long_unsigned_type_కణుపు
		    : long_long_integer_type_కణుపు);
      ఒకవేళ (prec > TYPE_PRECISION (new_type))
	new_type = (unsignedp
		    ? widest_unsigned_literal_type_కణుపు
		    : widest_integer_literal_type_కణుపు);
      ఒకవేళ (prec <= TYPE_PRECISION (new_type))
	{
	  the_enum->enum_అధికప్రవాహం = అబద్ధం;
	  the_enum->enum_తదుపరి_విలువ
	    = build_ద్విమాన_op (సమాసం_LOC_OR_LOC (విలువ, ఆదానం_location),
			       PLUS_సమాసం, convert (new_type, విలువ),
			       integer_one_కణుపు, అబద్ధం);
	  gcc_assert (!వృక్షం_int_cst_lt (the_enum->enum_తదుపరి_విలువ, విలువ));
	}
    }

  /* Now create a declaration for the enum value name.  */

  decl = build_decl (decl_loc, CONST_DECL, name, వృక్షం_TYPE (విలువ));
  DECL_INITIAL (decl) = విలువ;
  DECL_CONTEXT (decl) = the_enum->enum_type;
  pushdecl (decl);

  తిరిగి వృక్షం_cons (decl, విలువ, NULL_వృక్షం);
}

/* Implement LANG_HOOKS_SIMULATE_ENUM_DECL.  */

వృక్షం
c_simulate_enum_decl (location_t loc, స్థిరరాశి అక్షరం *name,
		      vec<string_int_pair> *విలువలు_ptr)
{
  location_t saved_loc = ఆదానం_location;
  ఆదానం_location = loc;

  నిర్మాణం c_enum_contents the_enum;
  వృక్షం enumtype = ప్రారంభం_enum (loc, &the_enum, get_identifier (name),
			      NULL_వృక్షం, అబద్ధం);

  వృక్షం విలువ_chain = NULL_వృక్షం;
  string_int_pair *విలువ;
  vec<string_int_pair> విలువలు = *విలువలు_ptr;
  గుర్తులేని పూర్ణాంకం i;
  FOR_EACH_VEC_ELT (విలువలు, i, విలువ)
    {
      వృక్షం decl = build_enumerator (loc, loc, &the_enum,
				    get_identifier (విలువ->మొదటి),
				    build_int_cst (integer_type_కణుపు,
						   విలువ->రెండవ));
      వృక్షం_CHAIN (decl) = విలువ_chain;
      విలువ_chain = decl;
    }

  ముగింపు_enum (enumtype, nreverse (విలువ_chain), NULL_వృక్షం);

  ఆదానం_location = saved_loc;
  తిరిగి enumtype;
}

/* Implement LANG_HOOKS_SIMULATE_RECORD_DECL.  */

వృక్షం
c_simulate_రికార్డు_decl (location_t loc, స్థిరరాశి అక్షరం *name,
			array_ముక్క<స్థిరరాశి వృక్షం> fields)
{
  location_t saved_loc = ఆదానం_location;
  ఆదానం_location = loc;

  తరగతి c_struct_parse_info *struct_info;
  వృక్షం ident = get_identifier (name);
  వృక్షం type = ప్రారంభం_struct (loc, రికార్డు_TYPE, ident, &struct_info);

  కొరకు (గుర్తులేని పూర్ణాంకం i = 0; i < fields.కొలత (); ++i)
    {
      DECL_క్షేత్రం_CONTEXT (fields[i]) = type;
      ఒకవేళ (i > 0)
	DECL_CHAIN (fields[i - 1]) = fields[i];
    }

  ముగింపు_struct (loc, type, fields[0], NULL_వృక్షం, struct_info);

  వృక్షం decl = build_decl (loc, TYPE_DECL, ident, type);
  సమితి_underlying_type (decl);
  lang_hooks.decls.pushdecl (decl);

  ఆదానం_location = saved_loc;
  తిరిగి type;
}

/* Create the FUNCTION_DECL for a function definition.
   DECLSPECS, DECLARATOR and ATTRIBUTES are the parts of
   the declaration; they describe the function's name and the type it returns,
   but twisted together in a fashion that parallels the syntax of C.

   This function creates a binding context for the function body
   as well as setting up the FUNCTION_DECL in current_function_decl.

   Returns true on success.  If the DECLARATOR is not suitable for a function
   (it defines a datum instead), we return false to report a parse error.  */

తార్కిక
ప్రారంభం_function (నిర్మాణం c_declspecs *declspecs, నిర్మాణం c_declarator *declarator,
		వృక్షం లక్షణాలు)
{
  వృక్షం decl1, old_decl;
  వృక్షం restype, resdecl;
  location_t loc;
  location_t ఫలితం_loc;
  వృక్షం సమాసం = ఖాళీ;

  current_function_returns_విలువ = 0;  /* Assume, until we see it does.  */
  current_function_returns_null = 0;
  current_function_returns_abnormally = 0;
  warn_about_return_type = 0;
  c_switch_దొంతర = ఖాళీ;

  /* Indicate no valid break/continue context.  */
  లోపల_statement = 0;

  decl1 = grokdeclarator (declarator, declspecs, FUNCDEF, నిజం, ఖాళీ,
			  &లక్షణాలు, &సమాసం, ఖాళీ, DEPRECATED_సాధారణ);
  invoke_plugin_callbacks (PLUGIN_ప్రారంభం_PARSE_FUNCTION, decl1);

  /* If the declarator is not suitable for a function definition,
     cause a syntax error.  */
  ఒకవేళ (decl1 == NULL_వృక్షం
      || వృక్షం_సంకేతం (decl1) != FUNCTION_DECL)
    తిరిగి అబద్ధం;

  /* Nested functions may have variably modified (return) type.
     Make sure the size expression is evaluated at this point.  */
  ఒకవేళ (సమాసం && !current_scope->parm_flag)
    కూడు_stmt (fold_convert (void_type_కణుపు, సమాసం));

  loc = DECL_ఆధారం_LOCATION (decl1);

  /* A nested function is not global.  */
  ఒకవేళ (current_function_decl != NULL_వృక్షం)
    వృక్షం_ప్రజా (decl1) = 0;

  c_decl_లక్షణాలు (&decl1, లక్షణాలు, 0);

  ఒకవేళ (DECL_DECLARED_INLINE_P (decl1)
      && DECL_UNINLINABLE (decl1)
      && lookup_attribute ("noinline", DECL_లక్షణాలు (decl1)))
    {
      auto_urlify_లక్షణాలు sentinel;
      warning_at (loc, OPT_Wattributes,
		  "inline function %qD given attribute %qs",
		  decl1, "noinline");
    }

  /* Handle gnu_inline attribute.  */
  ఒకవేళ (declspecs->inline_p
      && !flag_gnu89_inline
      && వృక్షం_సంకేతం (decl1) == FUNCTION_DECL
      && (lookup_attribute ("gnu_inline", DECL_లక్షణాలు (decl1))
	  || current_function_decl))
    {
      ఒకవేళ (declspecs->storage_class != csc_static)
	DECL_EXTERNAL (decl1) = !DECL_EXTERNAL (decl1);
    }

  announce_function (decl1);

  ఒకవేళ (!COMPLETE_OR_VOID_TYPE_P (వృక్షం_TYPE (వృక్షం_TYPE (decl1))))
    {
      error_at (loc, "return type is an incomplete type");
      /* Make it return void instead.  */
      వృక్షం_TYPE (decl1)
	= c_build_function_type (void_type_కణుపు,
				 TYPE_ARG_TYPES (వృక్షం_TYPE (decl1)),
				 TYPE_NO_NAMED_వాదనలు_STDARG_P (వృక్షం_TYPE (decl1)));
    }

  ఒకవేళ (warn_about_return_type)
    permerror_opt (loc, flag_isoc99 ? OPT_Wimplicit_int
		   : (warn_return_type > 0 ? OPT_Wreturn_type
		      : OPT_Wimplicit_int),
		   "return type defaults to %<int%>");

  /* Make the init_value nonzero so pushdecl knows this is not tentative.
     error_mark_node is replaced below (in pop_scope) with the BLOCK.  */
  DECL_INITIAL (decl1) = error_mark_కణుపు;

  /* If this definition isn't a prototype and we had a prototype declaration
     before, copy the arg type info from that prototype.  */
  old_decl = lookup_name_లోపల_scope (DECL_NAME (decl1), current_scope);
  ఒకవేళ (old_decl && వృక్షం_సంకేతం (old_decl) != FUNCTION_DECL)
    old_decl = NULL_వృక్షం;

  current_function_prototype_locus = UNKNOWN_LOCATION;
  current_function_prototype_built_లోపల = అబద్ధం;
  current_function_prototype_arg_types = NULL_వృక్షం;
  వృక్షం newtype = వృక్షం_TYPE (decl1);
  వృక్షం oldtype = old_decl ? వృక్షం_TYPE (old_decl) : newtype;
  ఒకవేళ (!prototype_p (newtype))
    {
      వృక్షం oldrt = వృక్షం_TYPE (oldtype);
      వృక్షం newrt = వృక్షం_TYPE (newtype);
      ఒకవేళ (old_decl != NULL_వృక్షం
	  && వృక్షం_సంకేతం (oldtype) == FUNCTION_TYPE
	  && comptypes (oldrt, newrt)
	  && !TYPE_NO_NAMED_వాదనలు_STDARG_P (oldtype))
	{
	  ఒకవేళ (stdarg_p (oldtype))
	    {
	      auto_diagnostic_సమూహం d;
	      warning_at (loc, 0, "%q+D defined as variadic function "
			  "without prototype", decl1);
	      locate_old_decl (old_decl);
	    }
	  వృక్షం_TYPE (decl1) = సంయుక్త_type (oldtype, newtype);
	  current_function_prototype_locus = DECL_ఆధారం_LOCATION (old_decl);
	  current_function_prototype_built_లోపల
	    = C_DECL_BUILTIN_PROTOTYPE (old_decl);
	  current_function_prototype_arg_types
	    = TYPE_ARG_TYPES (newtype);
	}
      ఒకవేళ (వృక్షం_ప్రజా (decl1))
	{
	  /* If there is an external prototype declaration of this
	     function, record its location but do not copy information
	     to this decl.  This may be an invisible declaration
	     (built-in or in a scope which has finished) or simply
	     have more refined argument types than any declaration
	     found above.  */
	  నిర్మాణం c_binding *b;
	  కొరకు (b = I_చిహ్నం_BINDING (DECL_NAME (decl1)); b; b = b->shadowed)
	    ఒకవేళ (B_లోపల_SCOPE (b, external_scope))
	      ఆపు;
	  ఒకవేళ (b)
	    {
	      వృక్షం ext_decl, ext_type;
	      ext_decl = b->decl;
	      ext_type = b->u.type ? b->u.type : వృక్షం_TYPE (ext_decl);
	      ఒకవేళ (వృక్షం_సంకేతం (ext_type) == FUNCTION_TYPE
		  && comptypes (వృక్షం_TYPE (వృక్షం_TYPE (decl1)),
				వృక్షం_TYPE (ext_type)))
		{
		  current_function_prototype_locus
		    = DECL_ఆధారం_LOCATION (ext_decl);
		  current_function_prototype_built_లోపల
		    = C_DECL_BUILTIN_PROTOTYPE (ext_decl);
		  current_function_prototype_arg_types
		    = TYPE_ARG_TYPES (ext_type);
		}
	    }
	}
    }

  /* Optionally warn about C23 compatibility.  */
  ఒకవేళ (warn_deprecated_non_prototype
      && old_decl != NULL_వృక్షం
      && వృక్షం_సంకేతం (oldtype) == FUNCTION_TYPE
      && !TYPE_ARG_TYPES (oldtype)
      && !TYPE_NO_NAMED_వాదనలు_STDARG_P (oldtype)
      && (TYPE_ARG_TYPES (newtype)
	  && వృక్షం_విలువ (TYPE_ARG_TYPES (newtype)) != void_type_కణుపు))
    {
      తార్కిక warned = warning_at (loc, OPT_Wdeprecated_non_prototype,
				"ISO C23 does not allow defining"
				" parameters for function %qE declared"
				" without parameters",
				decl1);
      ఒకవేళ (warned)
	inform (DECL_ఆధారం_LOCATION (old_decl), "declared here");
    }

  /* Optionally warn of old-fashioned def with no previous prototype.  */
  ఒకవేళ (warn_strict_prototypes
      && old_decl != error_mark_కణుపు
      && !prototype_p (వృక్షం_TYPE (decl1))
      && C_DECL_ISNT_PROTOTYPE (old_decl))
    warning_at (loc, OPT_Wstrict_prototypes,
		"function declaration isn%'t a prototype");
  /* Optionally warn of any global def with no previous prototype.  */
  లేకపోతే ఒకవేళ (warn_missing_prototypes
	   && old_decl != error_mark_కణుపు
	   && వృక్షం_ప్రజా (decl1)
	   && !MAIN_NAME_P (DECL_NAME (decl1))
	   && C_DECL_ISNT_PROTOTYPE (old_decl)
	   && !DECL_DECLARED_INLINE_P (decl1))
    warning_at (loc, OPT_Wmissing_prototypes,
		"no previous prototype for %qD", decl1);
  /* Optionally warn of any def with no previous prototype
     if the function has already been used.  */
  లేకపోతే ఒకవేళ (warn_missing_prototypes
	   && old_decl != NULL_వృక్షం
	   && old_decl != error_mark_కణుపు
	   && వృక్షం_వాడిన (old_decl)
	   && !prototype_p (వృక్షం_TYPE (old_decl)))
    warning_at (loc, OPT_Wmissing_prototypes,
		"%qD was used with no prototype before its definition", decl1);
  /* Optionally warn of any global def with no previous declaration.  */
  లేకపోతే ఒకవేళ (warn_missing_declarations
	   && వృక్షం_ప్రజా (decl1)
	   && old_decl == NULL_వృక్షం
	   && !MAIN_NAME_P (DECL_NAME (decl1))
	   && !DECL_DECLARED_INLINE_P (decl1))
    warning_at (loc, OPT_Wmissing_declarations,
		"no previous declaration for %qD",
		decl1);
  /* Optionally warn of any def with no previous declaration
     if the function has already been used.  */
  లేకపోతే ఒకవేళ (warn_missing_declarations
	   && old_decl != NULL_వృక్షం
	   && old_decl != error_mark_కణుపు
	   && వృక్షం_వాడిన (old_decl)
	   && C_DECL_IMPLICIT (old_decl))
    warning_at (loc, OPT_Wmissing_declarations,
		"%qD was used with no declaration before its definition", decl1);

  /* This function exists in static storage.
     (This does not mean `static' in the C sense!)  */
  వృక్షం_STATIC (decl1) = 1;

  /* This is the earliest point at which we might know the assembler
     name of the function.  Thus, if it's set before this, die horribly.  */
  gcc_assert (!DECL_ASSEMBLER_NAME_సమితి_P (decl1));

  /* If #pragma weak was used, mark the decl weak now.  */
  ఒకవేళ (current_scope == file_scope)
    maybe_apply_pragma_weak (decl1);

  /* Warn for unlikely, improbable, or stupid declarations of `main'.  */
  ఒకవేళ (warn_main && MAIN_NAME_P (DECL_NAME (decl1)))
    {
      ఒకవేళ (TYPE_MAIN_VARIANT (వృక్షం_TYPE (వృక్షం_TYPE (decl1)))
	  != integer_type_కణుపు)
	pedwarn (loc, OPT_Wmain, "return type of %qD is not %<int%>", decl1);
      లేకపోతే ఒకవేళ (TYPE_ATOMIC (వృక్షం_TYPE (వృక్షం_TYPE (decl1))))
	pedwarn (loc, OPT_Wmain, "%<_Atomic%>-qualified return type of %qD",
		 decl1);

      check_main_parameter_types (decl1);

      ఒకవేళ (!వృక్షం_ప్రజా (decl1))
	pedwarn (loc, OPT_Wmain,
		 "%qD is normally a non-static function", decl1);
    }

  వృక్షం parms = current_function_arg_info->parms;
  ఒకవేళ (old_decl)
    {
      location_t origloc = DECL_ఆధారం_LOCATION (old_decl);
      warn_parms_array_mismatch (origloc, old_decl, parms);
    }

  /* To enable versions to be created across TU's we mark and mangle all
     non-default versioned functions.  */
  ఒకవేళ (వృక్షం_సంకేతం (decl1) == FUNCTION_DECL
      && !లక్ష్యం_HAS_FMV_లక్ష్యం_ATTRIBUTE
      && get_లక్ష్యం_సంస్కరణ (decl1).is_valid ())
    {
      maybe_mark_function_versioned (decl1);
      ఒకవేళ (current_scope != file_scope)
	error ("versioned definitions are only allowed at file scope");
    }

  /* Record the decl so that the function name is defined.
     If we already have a decl for this name, and it is a FUNCTION_DECL,
     use the old decl.  */

  current_function_decl = pushdecl (decl1);

  ఒకవేళ (వృక్షం access = build_attr_access_from_parms (parms, అబద్ధం))
    decl_లక్షణాలు (&current_function_decl, access, ATTR_FLAG_అంతర్గత,
		     old_decl);

  నెట్టు_scope ();
  declare_parm_level ();

  /* Set the result decl source location to the location of the typespec.  */
  ఫలితం_loc = (declspecs->locations[cdw_typespec] == UNKNOWN_LOCATION
		? loc : declspecs->locations[cdw_typespec]);
  restype = వృక్షం_TYPE (వృక్షం_TYPE (current_function_decl));
  resdecl = build_decl (ఫలితం_loc, ఫలితం_DECL, NULL_వృక్షం, restype);
  DECL_ARTIFICIAL (resdecl) = 1;
  DECL_IGNORED_P (resdecl) = 1;
  DECL_ఫలితం (current_function_decl) = resdecl;

  ప్రారంభం_fname_decls ();

  తిరిగి నిజం;
}

/* Subroutine of store_parm_decls which handles new-style function
   definitions (prototype format). The parms already have decls, so we
   need only record them as in effect and complain if any redundant
   old-style parm decls were written.  */
స్థిర శూన్య
store_parm_decls_newstyle (వృక్షం fndecl, స్థిరరాశి నిర్మాణం c_arg_info *arg_info)
{
  వృక్షం decl;
  c_arg_ట్యాగ్ *ట్యాగ్;
  గుర్తులేని ix;

  ఒకవేళ (current_scope->bindings)
    {
      error_at (DECL_ఆధారం_LOCATION (fndecl),
		"old-style parameter declarations in prototyped "
		"function definition");

      /* Get rid of the old-style declarations.  */
      తీయి_scope ();
      నెట్టు_scope ();
    }
  /* Don't issue this warning for nested functions, and don't issue this
     warning if we got here because ARG_INFO_TYPES was error_mark_node
     (this happens when a function definition has just an ellipsis in
     its parameter list).  */
  లేకపోతే ఒకవేళ (!లోపల_system_శీర్షిక_at (ఆదానం_location)
	   && !current_function_scope
	   && arg_info->types != error_mark_కణుపు
	   && !arg_info->c23_ఖాళీలు_parens)
    warning_at (DECL_ఆధారం_LOCATION (fndecl), OPT_Wtraditional,
		"traditional C rejects ISO C style function definitions");

  /* Now make all the parameter declarations visible in the function body.
     We can bypass most of the grunt work of pushdecl.  */
  కొరకు (decl = arg_info->parms; decl; decl = DECL_CHAIN (decl))
    {
      DECL_CONTEXT (decl) = current_function_decl;
      ఒకవేళ (DECL_NAME (decl))
	{
	  bind (DECL_NAME (decl), decl, current_scope,
		/*invisible=*/అబద్ధం, /*nested=*/అబద్ధం,
		UNKNOWN_LOCATION);
	  ఒకవేళ (!వృక్షం_వాడిన (decl))
	    warn_if_shadowing (decl);
	}
      లేకపోతే
	pedwarn_c11 (DECL_ఆధారం_LOCATION (decl), OPT_Wmissing_parameter_name,
		     "ISO C does not support omitting parameter names in "
		     "function definitions before C23");
    }

  /* Record the parameter list in the function declaration.  */
  DECL_ARGUMENTS (fndecl) = arg_info->parms;

  /* Now make all the ancillary declarations visible, likewise.  */
  కొరకు (decl = arg_info->others; decl; decl = DECL_CHAIN (decl))
    {
      DECL_CONTEXT (decl) = current_function_decl;
      ఒకవేళ (DECL_NAME (decl))
	bind (DECL_NAME (decl), decl, current_scope,
	      /*invisible=*/అబద్ధం,
	      /*nested=*/(వృక్షం_సంకేతం (decl) == FUNCTION_DECL),
	      UNKNOWN_LOCATION);
    }

  /* And all the tag declarations.  */
  FOR_EACH_VEC_సురక్షిత_ELT_తిరగేయి (arg_info->ట్యాగులు, ix, ట్యాగ్)
    ఒకవేళ (ట్యాగ్->id)
      bind (ట్యాగ్->id, ట్యాగ్->type, current_scope,
	    /*invisible=*/అబద్ధం, /*nested=*/అబద్ధం, UNKNOWN_LOCATION);
}

/* Subroutine of store_parm_decls which handles old-style function
   definitions (separate parameter list and declarations).  */

స్థిర శూన్య
store_parm_decls_oldstyle (వృక్షం fndecl, స్థిరరాశి నిర్మాణం c_arg_info *arg_info)
{
  నిర్మాణం c_binding *b;
  వృక్షం parm, decl, చివరి;
  వృక్షం parmids = arg_info->parms;
  hash_సమితి<వృక్షం> చూసిన_వాదనలు;

  ఒకవేళ (!లోపల_system_శీర్షిక_at (ఆదానం_location))
    {
      ఒకవేళ (flag_isoc23)
	pedwarn (DECL_ఆధారం_LOCATION (fndecl),
		 OPT_Wold_style_definition, "old-style function definition");
      లేకపోతే
	warning_at (DECL_ఆధారం_LOCATION (fndecl),
		    OPT_Wold_style_definition,
		    "old-style function definition");
    }

  ఒకవేళ (current_scope->had_vla_unspec)
    error ("%<[*]%> not allowed in other than function prototype scope");

  /* Match each formal parameter name with its declaration.  Save each
     decl in the appropriate TREE_PURPOSE slot of the parmids chain.  */
  కొరకు (parm = parmids; parm; parm = వృక్షం_CHAIN (parm))
    {
      ఒకవేళ (వృక్షం_విలువ (parm) == NULL_వృక్షం)
	{
	  error_at (DECL_ఆధారం_LOCATION (fndecl),
		    "parameter name missing from parameter list");
	  వృక్షం_PURPOSE (parm) = NULL_వృక్షం;
	  కొనసాగు;
	}

      b = I_చిహ్నం_BINDING (వృక్షం_విలువ (parm));
      ఒకవేళ (b && B_లోపల_CURRENT_SCOPE (b))
	{
	  decl = b->decl;
	  /* Skip erroneous parameters.  */
	  ఒకవేళ (decl == error_mark_కణుపు)
	    కొనసాగు;
	  /* If we got something other than a PARM_DECL it is an error.  */
	  ఒకవేళ (వృక్షం_సంకేతం (decl) != PARM_DECL)
	    {
	      error_at (DECL_ఆధారం_LOCATION (decl),
			"%qD declared as a non-parameter", decl);
	      కొనసాగు;
	    }
	  /* If the declaration is already marked, we have a duplicate
	     name.  Complain and ignore the duplicate.  */
	  లేకపోతే ఒకవేళ (చూసిన_వాదనలు.కలిగియుంది (decl))
	    {
	      error_at (DECL_ఆధారం_LOCATION (decl),
			"multiple parameters named %qD", decl);
	      వృక్షం_PURPOSE (parm) = NULL_వృక్షం;
	      కొనసాగు;
	    }
	  /* If the declaration says "void", complain and turn it into
	     an int.  */
	  లేకపోతే ఒకవేళ (VOID_TYPE_P (వృక్షం_TYPE (decl)))
	    {
	      error_at (DECL_ఆధారం_LOCATION (decl),
			"parameter %qD declared with void type", decl);
	      వృక్షం_TYPE (decl) = integer_type_కణుపు;
	      DECL_ARG_TYPE (decl) = integer_type_కణుపు;
	      layout_decl (decl, 0);
	    }
	  warn_if_shadowing (decl);
	}
      /* If no declaration found, default to int.  */
      లేకపోతే
	{
	  /* FIXME diagnostics: This should be the location of the argument,
	     not the FNDECL.  E.g., for an old-style declaration

	       int f10(v) { blah; }

	     We should use the location of the V, not the F10.
	     Unfortunately, the V is an IDENTIFIER_NODE which has no
	     location.  In the future we need locations for c_arg_info
	     entries.

	     See gcc.dg/Wshadow-3.c for an example of this problem. */
	  decl = build_decl (DECL_ఆధారం_LOCATION (fndecl),
			     PARM_DECL, వృక్షం_విలువ (parm), integer_type_కణుపు);
	  DECL_ARG_TYPE (decl) = వృక్షం_TYPE (decl);
	  pushdecl (decl);
	  warn_if_shadowing (decl);

	  ఒకవేళ (flag_isoc99)
	    permerror_opt (DECL_ఆధారం_LOCATION (decl),
			   OPT_Wimplicit_int, "type of %qD defaults to %<int%>",
			   decl);
	  లేకపోతే
	    warning_at (DECL_ఆధారం_LOCATION (decl),
			OPT_Wmissing_parameter_type,
			"type of %qD defaults to %<int%>", decl);
	}

      వృక్షం_PURPOSE (parm) = decl;
      చూసిన_వాదనలు.కూడు (decl);
    }

  /* Now examine the parms chain for incomplete declarations
     and declarations with no corresponding names.  */

  కొరకు (b = current_scope->bindings; b; b = b->prev)
    {
      parm = b->decl;
      ఒకవేళ (వృక్షం_సంకేతం (parm) != PARM_DECL)
	కొనసాగు;

      ఒకవేళ (వృక్షం_TYPE (parm) != error_mark_కణుపు
	  && !COMPLETE_TYPE_P (వృక్షం_TYPE (parm)))
	{
	  error_at (DECL_ఆధారం_LOCATION (parm),
		    "parameter %qD has incomplete type", parm);
	  వృక్షం_TYPE (parm) = error_mark_కణుపు;
	}

      ఒకవేళ (!చూసిన_వాదనలు.కలిగియుంది (parm))
	{
	  error_at (DECL_ఆధారం_LOCATION (parm),
		    "declaration for parameter %qD but no such parameter",
		    parm);

	  /* Pretend the parameter was not missing.
	     This gets us to a standard state and minimizes
	     further error messages.  */
	  parmids = chainon (parmids, వృక్షం_cons (parm, 0, 0));
	}
    }

  /* Chain the declarations together in the order of the list of
     names.  Store that chain in the function decl, replacing the
     list of names.  Update the current scope to match.  */
  DECL_ARGUMENTS (fndecl) = NULL_వృక్షం;

  కొరకు (parm = parmids; parm; parm = వృక్షం_CHAIN (parm))
    ఒకవేళ (వృక్షం_PURPOSE (parm))
      ఆపు;
  ఒకవేళ (parm && వృక్షం_PURPOSE (parm))
    {
      చివరి = వృక్షం_PURPOSE (parm);
      DECL_ARGUMENTS (fndecl) = చివరి;

      కొరకు (parm = వృక్షం_CHAIN (parm); parm; parm = వృక్షం_CHAIN (parm))
	ఒకవేళ (వృక్షం_PURPOSE (parm))
	  {
	    DECL_CHAIN (చివరి) = వృక్షం_PURPOSE (parm);
	    చివరి = వృక్షం_PURPOSE (parm);
	  }
      DECL_CHAIN (చివరి) = NULL_వృక్షం;
    }

  /* If there was a previous prototype,
     set the DECL_ARG_TYPE of each argument according to
     the type previously specified, and report any mismatches.  */

  ఒకవేళ (current_function_prototype_arg_types)
    {
      వృక్షం type;
      కొరకు (parm = DECL_ARGUMENTS (fndecl),
	     type = current_function_prototype_arg_types;
	   parm || (type != NULL_వృక్షం
		    && వృక్షం_విలువ (type) != error_mark_కణుపు
		    && TYPE_MAIN_VARIANT (వృక్షం_విలువ (type)) != void_type_కణుపు);
	   parm = DECL_CHAIN (parm), type = వృక్షం_CHAIN (type))
	{
	  ఒకవేళ (parm == NULL_వృక్షం
	      || type == NULL_వృక్షం
	      || (వృక్షం_విలువ (type) != error_mark_కణుపు
		  && TYPE_MAIN_VARIANT (వృక్షం_విలువ (type)) == void_type_కణుపు))
	    {
	      ఒకవేళ (current_function_prototype_built_లోపల)
		warning_at (DECL_ఆధారం_LOCATION (fndecl),
			    0, "number of arguments doesn%'t match "
			    "built-in prototype");
	      లేకపోతే
		{
		  /* FIXME diagnostics: This should be the location of
		     FNDECL, but there is bug when a prototype is
		     declared inside function context, but defined
		     outside of it (e.g., gcc.dg/pr15698-2.c).  In
		     which case FNDECL gets the location of the
		     prototype, not the definition.  */
		  error_at (ఆదానం_location,
			    "number of arguments doesn%'t match prototype");

		  error_at (current_function_prototype_locus,
			    "prototype declaration");
		}
	      ఆపు;
	    }
	  /* Type for passing arg must be consistent with that
	     declared for the arg.  ISO C says we take the unqualified
	     type for parameters declared with qualified type.  */
	  ఒకవేళ (వృక్షం_TYPE (parm) != error_mark_కణుపు
	      && వృక్షం_విలువ (type) != error_mark_కణుపు
	      && ((TYPE_ATOMIC (DECL_ARG_TYPE (parm))
		   != TYPE_ATOMIC (వృక్షం_విలువ (type)))
		  || !comptypes (TYPE_MAIN_VARIANT (DECL_ARG_TYPE (parm)),
				 TYPE_MAIN_VARIANT (వృక్షం_విలువ (type)))))
	    {
	      ఒకవేళ ((TYPE_ATOMIC (DECL_ARG_TYPE (parm))
		   == TYPE_ATOMIC (వృక్షం_విలువ (type)))
		  && (TYPE_MAIN_VARIANT (వృక్షం_TYPE (parm))
		      == TYPE_MAIN_VARIANT (వృక్షం_విలువ (type))))
		{
		  /* Adjust argument to match prototype.  E.g. a previous
		     `int foo(float);' prototype causes
		     `int foo(x) float x; {...}' to be treated like
		     `int foo(float x) {...}'.  This is particularly
		     useful for argument types like uid_t.  */
		  DECL_ARG_TYPE (parm) = వృక్షం_TYPE (parm);

		  /* ??? Is it possible to get here with a
		     built-in prototype or will it always have
		     been diagnosed as conflicting with an
		     old-style definition and discarded?  */
		  ఒకవేళ (current_function_prototype_built_లోపల)
		    warning_at (DECL_ఆధారం_LOCATION (parm),
				OPT_Wpedantic, "promoted argument %qD "
				"doesn%'t match built-in prototype", parm);
		  లేకపోతే
		    {
		      pedwarn (DECL_ఆధారం_LOCATION (parm),
			       OPT_Wpedantic, "promoted argument %qD "
			       "doesn%'t match prototype", parm);
		      pedwarn (current_function_prototype_locus, OPT_Wpedantic,
			       "prototype declaration");
		    }
		}
	      లేకపోతే
		{
		  ఒకవేళ (current_function_prototype_built_లోపల)
		    warning_at (DECL_ఆధారం_LOCATION (parm),
				0, "argument %qD doesn%'t match "
				"built-in prototype", parm);
		  లేకపోతే
		    {
		      error_at (DECL_ఆధారం_LOCATION (parm),
				"argument %qD doesn%'t match prototype", parm);
		      error_at (current_function_prototype_locus,
				"prototype declaration");
		    }
		}
	    }
	}
      TYPE_ACTUAL_ARG_TYPES (వృక్షం_TYPE (fndecl)) = NULL_వృక్షం;
    }

  /* Otherwise, create a prototype that would match.  */

  లేకపోతే
    {
      వృక్షం actual = NULL_వృక్షం, చివరి = NULL_వృక్షం, type;

      కొరకు (parm = DECL_ARGUMENTS (fndecl); parm; parm = DECL_CHAIN (parm))
	{
	  type = వృక్షం_cons (NULL_వృక్షం, DECL_ARG_TYPE (parm), NULL_వృక్షం);
	  ఒకవేళ (చివరి)
	    వృక్షం_CHAIN (చివరి) = type;
	  లేకపోతే
	    actual = type;
	  చివరి = type;
	}
      type = వృక్షం_cons (NULL_వృక్షం, void_type_కణుపు, NULL_వృక్షం);
      ఒకవేళ (చివరి)
	వృక్షం_CHAIN (చివరి) = type;
      లేకపోతే
	actual = type;

      /* We are going to assign a new value for the TYPE_ACTUAL_ARG_TYPES
	 of the type of this function, but we need to avoid having this
	 affect the types of other similarly-typed functions, so we must
	 first force the generation of an identical (but separate) type
	 node for the relevant function type.  The new node we create
	 will be a variant of the main variant of the original function
	 type.  */

      వృక్షం_TYPE (fndecl) = build_variant_type_copy (వృక్షం_TYPE (fndecl));

      TYPE_ACTUAL_ARG_TYPES (వృక్షం_TYPE (fndecl)) = actual;
    }
}

/* Store parameter declarations passed in ARG_INFO into the current
   function declaration.  */

శూన్య
store_parm_decls_from (నిర్మాణం c_arg_info *arg_info)
{
  current_function_arg_info = arg_info;
  store_parm_decls ();
}

/* Called by walk_tree to look for and update context-less labels
   or labels with context in the parent function.  */

స్థిర వృక్షం
సమితి_labels_context_r (వృక్షం *tp, పూర్ణాంకం *walk_subtrees, శూన్య *దత్తాంశం)
{
  వృక్షం ctx = static_cast<వృక్షం>(దత్తాంశం);
  ఒకవేళ (వృక్షం_సంకేతం (*tp) == LABEL_సమాసం
      && (DECL_CONTEXT (LABEL_సమాసం_LABEL (*tp)) == NULL_వృక్షం
	  || DECL_CONTEXT (LABEL_సమాసం_LABEL (*tp)) == DECL_CONTEXT (ctx)))
    {
      DECL_CONTEXT (LABEL_సమాసం_LABEL (*tp)) = ctx;
      *walk_subtrees = 0;
    }

  తిరిగి NULL_వృక్షం;
}

/* Store the parameter declarations into the current function declaration.
   This is called after parsing the parameter declarations, before
   digesting the body of the function.

   For an old-style definition, construct a prototype out of the old-style
   parameter declarations and inject it into the function's type.  */

శూన్య
store_parm_decls (శూన్య)
{
  వృక్షం fndecl = current_function_decl;
  తార్కిక proto;

  /* The argument information block for FNDECL.  */
  నిర్మాణం c_arg_info *arg_info = current_function_arg_info;
  current_function_arg_info = 0;

  /* True if this definition is written with a prototype.  In C23, an
     empty argument list was converted to (void) in grokparms; in
     older C standard versions, it does not give the function a type
     with a prototype for future calls.  */
  proto = arg_info->types != 0 || arg_info->no_named_వాదనలు_stdarg_p;

  ఒకవేళ (proto)
    store_parm_decls_newstyle (fndecl, arg_info);
  లేకపోతే
    store_parm_decls_oldstyle (fndecl, arg_info);

  /* The next call to push_scope will be a function body.  */

  తదుపరి_is_function_body = నిజం;

  /* Write a record describing this function definition to the prototypes
     file (if requested).  */

  gen_aux_info_రికార్డు (fndecl, 1, 0, proto);

  /* Initialize the RTL code for the function.  */
  allocate_struct_function (fndecl, అబద్ధం);

  ఒకవేళ (warn_వాడని_local_typedefs)
    cfun->language = ggc_cleared_alloc<language_function> ();

  /* Begin the statement tree for this function.  */
  DECL_SAVED_వృక్షం (fndecl) = నెట్టు_stmt_list ();

  /* ??? Insert the contents of the pending sizes list into the function
     to be evaluated.  The only reason left to have this is
	void foo(int n, int array[n++])
     because we throw away the array type in favor of a pointer type, and
     thus won't naturally see the SAVE_EXPR containing the increment.  All
     other pending sizes would be handled by gimplify_parameters.  */
  ఒకవేళ (arg_info->pending_sizes)
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
      walk_వృక్షం_without_duplicates (&arg_info->pending_sizes,
				    సమితి_labels_context_r, fndecl);
      కూడు_stmt (arg_info->pending_sizes);
    }
}

/* Store PARM_DECLs in PARMS into scope temporarily.  Used for
   c_finish_omp_declare_simd for function prototypes.  No diagnostics
   should be done.  */

శూన్య
తాత్కాలిక_store_parm_decls (వృక్షం fndecl, వృక్షం parms)
{
  నెట్టు_scope ();
  కొరకు (వృక్షం p = parms; p; p = DECL_CHAIN (p))
    {
      DECL_CONTEXT (p) = fndecl;
      ఒకవేళ (DECL_NAME (p))
	bind (DECL_NAME (p), p, current_scope,
	      /*invisible=*/అబద్ధం, /*nested=*/అబద్ధం,
	      UNKNOWN_LOCATION);
    }
}

/* Undo what temp_store_parm_decls did.  */

శూన్య
తాత్కాలిక_తీయి_parm_decls (శూన్య)
{
  /* Clear all bindings in this temporary scope, so that
     pop_scope doesn't create a BLOCK.  */
  నిర్మాణం c_binding *b = current_scope->bindings;
  current_scope->bindings = ఖాళీ;
  కొరకు (; b; b = free_binding_and_advance (b))
    {
      gcc_assert (వృక్షం_సంకేతం (b->decl) == PARM_DECL
		  || b->decl == error_mark_కణుపు);
      gcc_assert (I_చిహ్నం_BINDING (b->id) == b);
      I_చిహ్నం_BINDING (b->id) = b->shadowed;
      ఒకవేళ (b->shadowed && b->shadowed->u.type)
	వృక్షం_TYPE (b->shadowed->decl) = b->shadowed->u.type;
    }
  తీయి_scope ();
}


/* Finish up a function declaration and compile that function
   all the way to assembler language output.  Then free the storage
   for the function definition.

   This is called after parsing the body of the function definition.  */

శూన్య
ముగింపు_function (location_t చివర_loc)
{
  వృక్షం fndecl = current_function_decl;

  ఒకవేళ (c_dialect_objc ())
    objc_ముగింపు_function ();

  ఒకవేళ (DECL_INITIAL (fndecl) && DECL_INITIAL (fndecl) != error_mark_కణుపు)
    ఖండం_SUPERCONTEXT (DECL_INITIAL (fndecl)) = fndecl;

  /* Must mark the RESULT_DECL as being in this function.  */

  ఒకవేళ (DECL_ఫలితం (fndecl) && DECL_ఫలితం (fndecl) != error_mark_కణుపు)
    DECL_CONTEXT (DECL_ఫలితం (fndecl)) = fndecl;

  ఒకవేళ (MAIN_NAME_P (DECL_NAME (fndecl)) && !వృక్షం_THIS_VOLATILE (fndecl)
      && TYPE_MAIN_VARIANT (వృక్షం_TYPE (వృక్షం_TYPE (fndecl)))
      == integer_type_కణుపు && flag_isoc99)
    {
      /* Hack.  We don't want the middle-end to warn that this return
	 is unreachable, so we mark its location as special.  Using
	 UNKNOWN_LOCATION has the problem that it gets clobbered in
	 annotate_one_with_locus.  A cleaner solution might be to
	 ensure ! should_carry_locus_p (stmt), but that needs a flag.
      */
      c_ముగింపు_return (BUILTINS_LOCATION, integer_zero_కణుపు, NULL_వృక్షం);
    }

  /* Tie off the statement tree for this function.  */
  DECL_SAVED_వృక్షం (fndecl) = తీయి_stmt_list (DECL_SAVED_వృక్షం (fndecl));

  ముగింపు_fname_decls ();

  /* Complain if there's no return statement only if option specified on
     command line.  */
  ఒకవేళ (warn_return_type > 0
      && వృక్షం_సంకేతం (వృక్షం_TYPE (వృక్షం_TYPE (fndecl))) != VOID_TYPE
      && !current_function_returns_విలువ && !current_function_returns_null
      /* Don't complain if we are no-return.  */
      && !current_function_returns_abnormally
      /* Don't complain if we are declared noreturn.  */
      && !వృక్షం_THIS_VOLATILE (fndecl)
      /* Don't warn for main().  */
      && !MAIN_NAME_P (DECL_NAME (fndecl))
      /* Or if they didn't actually specify a return type.  */
      && !C_FUNCTION_IMPLICIT_INT (fndecl)
      /* Normally, with -Wreturn-type, flow will complain, but we might
         optimize out static functions.  */
      && !వృక్షం_ప్రజా (fndecl)
      && targetm.warn_func_return (fndecl)
      && warning (OPT_Wreturn_type,
		  "no return statement in function returning non-void"))
    suppress_warning (fndecl, OPT_Wreturn_type);

  /* Complain about parameters that are only set, but never otherwise used.  */
  ఒకవేళ (warn_వాడని_but_సమితి_parameter)
    {
      వృక్షం decl;

      కొరకు (decl = DECL_ARGUMENTS (fndecl);
	   decl;
	   decl = DECL_CHAIN (decl))
	ఒకవేళ (వృక్షం_వాడిన (decl)
	    && వృక్షం_సంకేతం (decl) == PARM_DECL
	    && !DECL_READ_P (decl)
	    && DECL_NAME (decl)
	    && !DECL_ARTIFICIAL (decl)
	    && !warning_suppressed_p (decl, OPT_Wunused_but_సమితి_parameter))
	  warning_at (DECL_ఆధారం_LOCATION (decl),
		      OPT_Wunused_but_సమితి_parameter,
		      "parameter %qD set but not used", decl);
    }

  /* Complain about locally defined typedefs that are not used in this
     function.  */
  maybe_warn_వాడని_local_typedefs ();

  /* Possibly warn about unused parameters.  */
  ఒకవేళ (warn_వాడని_parameter)
    do_warn_వాడని_parameter (fndecl);

  /* Store the end of the function, so that we get good line number
     info for the epilogue.  */
  cfun->function_చివర_locus = చివర_loc;

  /* Finalize the ELF visibility for the function.  */
  c_determine_visibility (fndecl);

  /* For GNU C extern inline functions disregard inline limits.  */
  ఒకవేళ (DECL_EXTERNAL (fndecl)
      && DECL_DECLARED_INLINE_P (fndecl)
      && (flag_gnu89_inline
	  || lookup_attribute ("gnu_inline", DECL_లక్షణాలు (fndecl))))
    DECL_DISREGARD_INLINE_LIMITS (fndecl) = 1;

  /* Genericize before inlining.  Delay genericizing nested functions
     until their parent function is genericized.  Since finalizing
     requires GENERIC, delay that as well.  */

  ఒకవేళ (DECL_INITIAL (fndecl) && DECL_INITIAL (fndecl) != error_mark_కణుపు
      && !undef_nested_function)
    {
      ఒకవేళ (!decl_function_context (fndecl))
	{
	  invoke_plugin_callbacks (PLUGIN_PRE_GENERICIZE, fndecl);
	  c_genericize (fndecl);

	  /* ??? Objc emits functions after finalizing the compilation unit.
	     This should be cleaned up later and this conditional removed.  */
	  ఒకవేళ (symtab->global_info_ready)
	    {
	      cgraph_కణుపు::కూడు_new_function (fndecl, అబద్ధం);
	      తిరిగి;
	    }
	  cgraph_కణుపు::finalize_function (fndecl, అబద్ధం);
	}
      లేకపోతే
	{
	  /* Register this function with cgraph just far enough to get it
	    added to our parent's nested function list.  Handy, since the
	    C front end doesn't have such a list.  */
	  (శూన్య) cgraph_కణుపు::get_create (fndecl);
	}
    }

  ఒకవేళ (!decl_function_context (fndecl))
    undef_nested_function = అబద్ధం;

  ఒకవేళ (cfun->language != ఖాళీ)
    {
      ggc_free (cfun->language);
      cfun->language = ఖాళీ;
    }

  /* We're leaving the context of this function, so zap cfun.
     It's still in DECL_STRUCT_FUNCTION, and we'll restore it in
     tree_rest_of_compilation.  */
  సమితి_cfun (ఖాళీ);
  invoke_plugin_callbacks (PLUGIN_ముగింపు_PARSE_FUNCTION, current_function_decl);
  current_function_decl = ఖాళీ;
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

వృక్షం
check_for_loop_decls (location_t loc, తార్కిక turn_off_iso_c99_error)
{
  నిర్మాణం c_binding *b;
  వృక్షం one_decl = NULL_వృక్షం;
  పూర్ణాంకం n_decls = 0;

  ఒకవేళ (!turn_off_iso_c99_error)
    {
      స్థిర తార్కిక hint = నిజం;
      /* If we get here, declarations have been used in a for loop without
	 the C99 for loop scope.  This doesn't make much sense, so don't
	 allow it.  */
      auto_diagnostic_సమూహం d;
      error_at (loc, "%<for%> loop initial declarations "
		"are only allowed in C99 or C11 mode");
      ఒకవేళ (hint)
	{
	  inform (loc,
		  "use option %<-std=c99%>, %<-std=gnu99%>, %<-std=c11%> or "
		  "%<-std=gnu11%> to compile your code");
	  hint = అబద్ధం;
	}
      తిరిగి NULL_వృక్షం;
    }
  లేకపోతే
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

  కొరకు (b = current_scope->bindings; b; b = b->prev)
    {
      వృక్షం id = b->id;
      వృక్షం decl = b->decl;

      ఒకవేళ (!id)
	కొనసాగు;

      ఎంపిక (వృక్షం_సంకేతం (decl))
	{
	స్థితి VAR_DECL:
	  {
	    location_t decl_loc = DECL_ఆధారం_LOCATION (decl);
	    ఒకవేళ (వృక్షం_STATIC (decl))
	      pedwarn_c11 (decl_loc, OPT_Wpedantic,
			   "declaration of static variable %qD in %<for%> "
			   "loop initial declaration", decl);
	    లేకపోతే ఒకవేళ (DECL_EXTERNAL (decl))
	      pedwarn_c11 (decl_loc, OPT_Wpedantic,
			   "declaration of %<extern%> variable %qD in %<for%> "
			   "loop initial declaration", decl);
	  }
	  ఆపు;

	స్థితి రికార్డు_TYPE:
	  pedwarn_c11 (loc, OPT_Wpedantic,
		       "%<struct %E%> declared in %<for%> loop initial "
		       "declaration", id);
	  ఆపు;
	స్థితి UNION_TYPE:
	  pedwarn_c11 (loc, OPT_Wpedantic,
		       "%<union %E%> declared in %<for%> loop initial "
		       "declaration",
		       id);
	  ఆపు;
	స్థితి ENUMERAL_TYPE:
	  pedwarn_c11 (loc, OPT_Wpedantic,
		       "%<enum %E%> declared in %<for%> loop "
		       "initial declaration", id);
	  ఆపు;
	అప్రమేయ:
	  pedwarn_c11 (loc, OPT_Wpedantic, "declaration of non-variable "
		       "%qD in %<for%> loop initial declaration", decl);
	}

      n_decls++;
      one_decl = decl;
    }

  తిరిగి n_decls == 1 ? one_decl : NULL_వృక్షం;
}

/* Save and reinitialize the variables
   used during compilation of a C function.  */

శూన్య
c_నెట్టు_function_context (శూన్య)
{
  నిర్మాణం language_function *p = cfun->language;
  /* cfun->language might have been already allocated by the use of
     -Wunused-local-typedefs.  In that case, just re-use it.  */
  ఒకవేళ (p == ఖాళీ)
    cfun->language = p = ggc_cleared_alloc<language_function> ();

  p->పునాది.x_stmt_వృక్షం = c_stmt_వృక్షం;
  c_stmt_వృక్షం.x_cur_stmt_list = vec_సురక్షిత_copy (c_stmt_వృక్షం.x_cur_stmt_list);
  p->x_లోపల_statement = లోపల_statement;
  p->x_switch_దొంతర = c_switch_దొంతర;
  p->loop_పేర్లు = loop_పేర్లు;
  loop_పేర్లు = vNULL;
  p->loop_పేర్లు_hash = loop_పేర్లు_hash;
  loop_పేర్లు_hash = ఖాళీ;
  p->arg_info = current_function_arg_info;
  p->returns_విలువ = current_function_returns_విలువ;
  p->returns_null = current_function_returns_null;
  p->returns_abnormally = current_function_returns_abnormally;
  p->warn_about_return_type = warn_about_return_type;

  నెట్టు_function_context ();
}

/* Restore the variables used during compilation of a C function.  */

శూన్య
c_తీయి_function_context (శూన్య)
{
  నిర్మాణం language_function *p;

  తీయి_function_context ();
  p = cfun->language;

  /* When -Wunused-local-typedefs is in effect, cfun->languages is
     used to store data throughout the life time of the current cfun,
     So don't deallocate it.  */
  ఒకవేళ (!warn_వాడని_local_typedefs)
    cfun->language = ఖాళీ;

  ఒకవేళ (DECL_STRUCT_FUNCTION (current_function_decl) == 0
      && DECL_SAVED_వృక్షం (current_function_decl) == NULL_వృక్షం)
    {
      /* Stop pointing to the local nodes about to be freed.  */
      /* But DECL_INITIAL must remain nonzero so we know this
	 was an actual function definition.  */
      DECL_INITIAL (current_function_decl) = error_mark_కణుపు;
      DECL_ARGUMENTS (current_function_decl) = NULL_వృక్షం;
    }

  c_stmt_వృక్షం = p->పునాది.x_stmt_వృక్షం;
  p->పునాది.x_stmt_వృక్షం.x_cur_stmt_list = ఖాళీ;
  లోపల_statement = p->x_లోపల_statement;
  c_switch_దొంతర = p->x_switch_దొంతర;
  loop_పేర్లు.release ();
  loop_పేర్లు = p->loop_పేర్లు;
  p->loop_పేర్లు = vNULL;
  తొలగించు loop_పేర్లు_hash;
  loop_పేర్లు_hash = p->loop_పేర్లు_hash;
  p->loop_పేర్లు_hash = ఖాళీ;
  current_function_arg_info = p->arg_info;
  current_function_returns_విలువ = p->returns_విలువ;
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

stmt_వృక్షం
current_stmt_వృక్షం (శూన్య)
{
  తిరిగి &c_stmt_వృక్షం;
}

/* Return the global value of T as a symbol.  */

వృక్షం
identifier_global_విలువ	(వృక్షం t)
{
  నిర్మాణం c_binding *b;

  కొరకు (b = I_చిహ్నం_BINDING (t); b; b = b->shadowed)
    ఒకవేళ (B_లోపల_FILE_SCOPE (b) || B_లోపల_EXTERNAL_SCOPE (b))
      తిరిగి b->decl;

  తిరిగి NULL_వృక్షం;
}

/* Return the global value of tag T as a symbol.  */

వృక్షం
identifier_global_ట్యాగ్ (వృక్షం t)
{
  నిర్మాణం c_binding *b;

  కొరకు (b = I_ట్యాగ్_BINDING (t); b; b = b->shadowed)
    ఒకవేళ (B_లోపల_FILE_SCOPE (b) || B_లోపల_EXTERNAL_SCOPE (b))
      తిరిగి b->decl;

  తిరిగి NULL_వృక్షం;
}

/* Returns non-zero (result of __has_builtin) if NAME refers to a built-in
   function or function-like operator.  */

పూర్ణాంకం
పేర్లు_builtin_p (స్థిరరాశి అక్షరం *name)
{
  వృక్షం id = get_identifier (name);
  ఒకవేళ (వృక్షం decl = identifier_global_విలువ (id))
    తిరిగి వృక్షం_సంకేతం (decl) == FUNCTION_DECL && DECL_IS_UNDECLARED_BUILTIN (decl);

  /* Also detect common reserved C words that aren't strictly built-in
     functions.  */
  ఎంపిక (C_RID_సంకేతం (id))
    {
    స్థితి RID_BUILTIN_ASSOC_BARRIER:
    స్థితి RID_BUILTIN_BITREVERSEG:
    స్థితి RID_BUILTIN_BSWAPG:
    స్థితి RID_BUILTIN_CONVERTVECTOR:
    స్థితి RID_BUILTIN_HAS_ATTRIBUTE:
    స్థితి RID_BUILTIN_SHUFFLE:
    స్థితి RID_BUILTIN_SHUFFLEVECTOR:
    స్థితి RID_BUILTIN_STDC:
    స్థితి RID_BUILTIN_COUNTED_BY_REF:
    స్థితి RID_ఎంచుకో_సమాసం:
    స్థితి RID_OFFSETOF:
    స్థితి RID_TYPES_COMPATIBLE_P:
    స్థితి RID_C23_VA_ప్రారంభం:
    స్థితి RID_VA_ARG:
      తిరిగి 1;
    అప్రమేయ:
      ఆపు;
    }

  తిరిగి 0;
}

/* In C, the only C-linkage public declaration is at file scope.  */

వృక్షం
c_linkage_bindings (వృక్షం name)
{
  తిరిగి identifier_global_విలువ (name);
}

/* Record a builtin type for C.  If NAME is non-NULL, it is the name used;
   otherwise the name is found in ridpointers from RID_INDEX.  */

శూన్య
రికార్డు_builtin_type (గణన rid rid_సూచీ, స్థిరరాశి అక్షరం *name, వృక్షం type)
{
  వృక్షం id, decl;
  ఒకవేళ (name == 0)
    id = ridpointers[(పూర్ణాంకం) rid_సూచీ];
  లేకపోతే
    id = get_identifier (name);
  decl = build_decl (UNKNOWN_LOCATION, TYPE_DECL, id, type);
  pushdecl (decl);
  ఒకవేళ (debug_hooks->type_decl)
    debug_hooks->type_decl (decl, అబద్ధం);
}

/* Return a c_parm structure with the given SPECS, ATTRS and DECLARATOR.  */

నిర్మాణం c_parm *
build_c_parm (నిర్మాణం c_declspecs *specs, వృక్షం attrs,
	      నిర్మాణం c_declarator *declarator,
	      location_t loc)
{
  నిర్మాణం c_parm *ret = XOBNEW (&parser_obstack, నిర్మాణం c_parm);
  ret->specs = specs;
  ret->attrs = attrs;
  ret->declarator = declarator;
  ret->loc = loc;
  తిరిగి ret;
}

/* Return a declarator with nested attributes.  TARGET is the inner
   declarator to which these attributes apply.  ATTRS are the
   attributes.  */

నిర్మాణం c_declarator *
build_attrs_declarator (వృక్షం attrs, నిర్మాణం c_declarator *లక్ష్యం)
{
  నిర్మాణం c_declarator *ret = XOBNEW (&parser_obstack, నిర్మాణం c_declarator);
  ret->రకం = cdk_attrs;
  ret->declarator = లక్ష్యం;
  ret->u.attrs = attrs;
  తిరిగి ret;
}

/* Return a declarator for a function with arguments specified by ARGS
   and return type specified by TARGET.  */

నిర్మాణం c_declarator *
build_function_declarator (నిర్మాణం c_arg_info *వాదనలు,
			   నిర్మాణం c_declarator *లక్ష్యం)
{
  నిర్మాణం c_declarator *ret = XOBNEW (&parser_obstack, నిర్మాణం c_declarator);
  ret->రకం = cdk_function;
  ret->declarator = లక్ష్యం;
  ret->u.arg_info = వాదనలు;
  తిరిగి ret;
}

/* Return a declarator for the identifier IDENT (which may be
   NULL_TREE for an abstract declarator).  */

నిర్మాణం c_declarator *
build_id_declarator (వృక్షం ident)
{
  నిర్మాణం c_declarator *ret = XOBNEW (&parser_obstack, నిర్మాణం c_declarator);
  ret->రకం = cdk_id;
  ret->declarator = 0;
  ret->u.id.id = ident;
  ret->u.id.attrs = NULL_వృక్షం;
  /* Default value - may get reset to a more precise location. */
  ret->id_loc = ఆదానం_location;
  తిరిగి ret;
}

/* Return something to represent absolute declarators containing a *.
   TARGET is the absolute declarator that the * contains.
   TYPE_QUALS_ATTRS is a structure for type qualifiers and attributes
   to apply to the pointer type.  */

నిర్మాణం c_declarator *
make_సూచిక_declarator (నిర్మాణం c_declspecs *type_quals_attrs,
			 నిర్మాణం c_declarator *లక్ష్యం)
{
  వృక్షం attrs;
  పూర్ణాంకం quals = 0;
  నిర్మాణం c_declarator *itarget = లక్ష్యం;
  నిర్మాణం c_declarator *ret = XOBNEW (&parser_obstack, నిర్మాణం c_declarator);
  ఒకవేళ (type_quals_attrs)
    {
      attrs = type_quals_attrs->attrs;
      quals = quals_from_declspecs (type_quals_attrs);
      ఒకవేళ (attrs != NULL_వృక్షం)
	itarget = build_attrs_declarator (attrs, లక్ష్యం);
    }
  ret->రకం = cdk_సూచిక;
  ret->declarator = itarget;
  ret->u.సూచిక_quals = quals;
  తిరిగి ret;
}

/* Return a pointer to a structure for an empty list of declaration
   specifiers.  */

నిర్మాణం c_declspecs *
build_null_declspecs (శూన్య)
{
  నిర్మాణం c_declspecs *ret = XOBNEW (&parser_obstack, నిర్మాణం c_declspecs);
  memset (ret, 0, పరిమాణం *ret);
  ret->align_log = -1;
  ret->typespec_మాట = cts_none;
  ret->storage_class = csc_none;
  ret->సమాసం_const_operands = నిజం;
  ret->typespec_రకం = ctsk_none;
  ret->చిరునామా_space = ADDR_SPACE_GENERIC;
  తిరిగి ret;
}

/* Add the address space ADDRSPACE to the declaration specifiers
   SPECS, returning SPECS.  */

నిర్మాణం c_declspecs *
declspecs_కూడు_addrspace (location_t location,
			 నిర్మాణం c_declspecs *specs, addr_space_t as)
{
  specs->non_sc_చూసిన_p = నిజం;
  specs->declspecs_చూసిన_p = నిజం;
  specs->non_std_attrs_చూసిన_p = నిజం;

  ఒకవేళ (!ADDR_SPACE_GENERIC_P (specs->చిరునామా_space)
      && specs->చిరునామా_space != as)
    error ("incompatible address space qualifiers %qs and %qs",
	   c_addr_space_name (as),
	   c_addr_space_name (specs->చిరునామా_space));
  లేకపోతే
    {
      specs->చిరునామా_space = as;
      specs->locations[cdw_చిరునామా_space] = location;
    }
  తిరిగి specs;
}

/* Add the type qualifier QUAL to the declaration specifiers SPECS,
   returning SPECS.  */

నిర్మాణం c_declspecs *
declspecs_కూడు_qual (location_t loc,
		    నిర్మాణం c_declspecs *specs, వృక్షం qual)
{
  గణన rid i;
  తార్కిక dupe = అబద్ధం;
  specs->non_sc_చూసిన_p = నిజం;
  specs->declspecs_చూసిన_p = నిజం;
  specs->non_std_attrs_చూసిన_p = నిజం;
  gcc_assert (వృక్షం_సంకేతం (qual) == IDENTIFIER_కణుపు
	      && C_IS_RESERVED_మాట (qual));
  i = C_RID_సంకేతం (qual);
  location_t prev_loc = UNKNOWN_LOCATION;
  ఎంపిక (i)
    {
    స్థితి RID_CONST:
      dupe = specs->const_p;
      specs->const_p = నిజం;
      prev_loc = specs->locations[cdw_const];
      specs->locations[cdw_const] = loc;
      ఆపు;
    స్థితి RID_VOLATILE:
      dupe = specs->volatile_p;
      specs->volatile_p = నిజం;
      prev_loc = specs->locations[cdw_volatile];
      specs->locations[cdw_volatile] = loc;
      ఆపు;
    స్థితి RID_RESTRICT:
      dupe = specs->restrict_p;
      specs->restrict_p = నిజం;
      prev_loc = specs->locations[cdw_restrict];
      specs->locations[cdw_restrict] = loc;
      ఆపు;
    స్థితి RID_ATOMIC:
      dupe = specs->atomic_p;
      specs->atomic_p = నిజం;
      prev_loc = specs->locations[cdw_atomic];
      specs->locations[cdw_atomic] = loc;
      ఆపు;
    అప్రమేయ:
      gcc_unreachable ();
    }
  ఒకవేళ (dupe)
    {
      తార్కిక warned = pedwarn_c90 (loc, OPT_Wpedantic,
				 "duplicate %qE declaration specifier", qual);
      ఒకవేళ (!warned
	  && warn_duplicate_decl_specifier
	  && prev_loc >= RESERVED_LOCATION_లెక్క
	  && !from_macro_expansion_at (prev_loc)
	  && !from_macro_expansion_at (loc))
	warning_at (loc, OPT_Wduplicate_decl_specifier,
		    "duplicate %qE declaration specifier", qual);
    }
  తిరిగి specs;
}

/* Add the type specifier TYPE to the declaration specifiers SPECS,
   returning SPECS.  */

నిర్మాణం c_declspecs *
declspecs_కూడు_type (location_t loc, నిర్మాణం c_declspecs *specs,
		    నిర్మాణం c_typespec spec)
{
  వృక్షం type = spec.spec;
  specs->non_sc_చూసిన_p = నిజం;
  specs->declspecs_చూసిన_p = నిజం;
  specs->non_std_attrs_చూసిన_p = నిజం;
  specs->typespec_రకం = spec.రకం;
  ఒకవేళ (వృక్షం_DEPRECATED (type))
    specs->deprecated_p = నిజం;
  ఒకవేళ (వృక్షం_UNAVAILABLE (type))
    specs->unavailable_p = నిజం;

  /* As a type specifier is present, "auto" must be used as a storage
     class specifier, not for type deduction.  */
  ఒకవేళ (specs->c23_auto_p)
    {
      specs->c23_auto_p = అబద్ధం;
      ఒకవేళ (specs->storage_class != csc_none)
	error ("multiple storage classes in declaration specifiers");
      లేకపోతే ఒకవేళ (specs->thread_p)
	error ("%qs used with %<auto%>",
	       specs->thread_gnu_p ? "__thread" : "_Thread_local");
      లేకపోతే ఒకవేళ (specs->constexpr_p)
	/* auto may only be used with another storage class specifier,
	   such as constexpr, if the type is inferred.  */
	error ("%<auto%> used with %<constexpr%>");
      లేకపోతే
	specs->storage_class = csc_auto;
    }

  /* Handle type specifier keywords.  */
  ఒకవేళ (వృక్షం_సంకేతం (type) == IDENTIFIER_కణుపు
      && C_IS_RESERVED_మాట (type)
      && C_RID_సంకేతం (type) != RID_CXX_COMPAT_WARN)
    {
      గణన rid i = C_RID_సంకేతం (type);
      ఒకవేళ (specs->type)
	{
	  error_at (loc, "two or more data types in declaration specifiers");
	  తిరిగి specs;
	}
      ఒకవేళ ((పూర్ణాంకం) i <= (పూర్ణాంకం) RID_చివరి_MODIFIER)
	{
	  /* "long", "short", "signed", "unsigned", "_Complex" or "_Sat".  */
	  తార్కిక dupe = అబద్ధం;
	  ఎంపిక (i)
	    {
	    స్థితి RID_LONG:
	      ఒకవేళ (specs->long_long_p)
		{
		  error_at (loc, "%<long long long%> is too long for GCC");
		  ఆపు;
		}
	      ఒకవేళ (specs->long_p)
		{
		  ఒకవేళ (specs->typespec_మాట == cts_double)
		    {
		      error_at (loc,
				"both %qs and %qs in declaration specifiers",
				"long long", "double");
		      ఆపు;
		    }
		  pedwarn_c90 (loc, OPT_Wlong_long,
			       "ISO C90 does not support %<long long%>");
		  specs->long_long_p = 1;
		  specs->locations[cdw_long_long] = loc;
		  ఆపు;
		}
	      ఒకవేళ (specs->short_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "short");
	      లేకపోతే ఒకవేళ (specs->typespec_మాట == cts_auto_type)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "__auto_type");
	      లేకపోతే ఒకవేళ (specs->typespec_మాట == cts_void)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "void");
	      లేకపోతే ఒకవేళ (specs->typespec_మాట == cts_int_n)
		error_at (loc,
			  "both %qs and %<__int%d%> in declaration specifiers",
			  "long", int_n_దత్తాంశం[specs->u.int_n_idx].bitsize);
	      లేకపోతే ఒకవేళ (specs->typespec_మాట == cts_bool)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "_Bool");
	      లేకపోతే ఒకవేళ (specs->typespec_మాట == cts_bitint)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "_BitInt");
	      లేకపోతే ఒకవేళ (specs->typespec_మాట == cts_char)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "char");
	      లేకపోతే ఒకవేళ (specs->typespec_మాట == cts_float)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "float");
	      లేకపోతే ఒకవేళ (specs->typespec_మాట == cts_floatn_nx)
		error_at (loc,
			  "both %qs and %<_Float%d%s%> in declaration "
			  "specifiers", "long",
			  floatn_nx_types[specs->u.floatn_nx_idx].n,
			  floatn_nx_types[specs->u.floatn_nx_idx].extended
			  ? "x"
			  : "");
	      లేకపోతే ఒకవేళ (specs->typespec_మాట == cts_dfloat32)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "_Decimal32");
	      లేకపోతే ఒకవేళ (specs->typespec_మాట == cts_dfloat64)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "_Decimal64");
	      లేకపోతే ఒకవేళ (specs->typespec_మాట == cts_dfloat128)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "_Decimal128");
	      లేకపోతే ఒకవేళ (specs->typespec_మాట == cts_dfloat64x)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "_Decimal64x");
	      లేకపోతే
		{
		  specs->long_p = నిజం;
		  specs->locations[cdw_long] = loc;
		}
	      ఆపు;
	    స్థితి RID_SHORT:
	      dupe = specs->short_p;
	      ఒకవేళ (specs->long_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "short");
	      లేకపోతే ఒకవేళ (specs->typespec_మాట == cts_auto_type)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "__auto_type");
	      లేకపోతే ఒకవేళ (specs->typespec_మాట == cts_void)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "void");
	      లేకపోతే ఒకవేళ (specs->typespec_మాట == cts_int_n)
		error_at (loc,
			  "both %qs and %<__int%d%> in declaration specifiers",
			  "short", int_n_దత్తాంశం[specs->u.int_n_idx].bitsize);
	      లేకపోతే ఒకవేళ (specs->typespec_మాట == cts_bool)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "_Bool");
	      లేకపోతే ఒకవేళ (specs->typespec_మాట == cts_bitint)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "_BitInt");
	      లేకపోతే ఒకవేళ (specs->typespec_మాట == cts_char)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "char");
	      లేకపోతే ఒకవేళ (specs->typespec_మాట == cts_float)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "float");
	      లేకపోతే ఒకవేళ (specs->typespec_మాట == cts_double)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "double");
	      లేకపోతే ఒకవేళ (specs->typespec_మాట == cts_floatn_nx)
		error_at (loc,
			  "both %qs and %<_Float%d%s%> in declaration "
			  "specifiers", "short",
			  floatn_nx_types[specs->u.floatn_nx_idx].n,
			  floatn_nx_types[specs->u.floatn_nx_idx].extended
			  ? "x"
			  : "");
	      లేకపోతే ఒకవేళ (specs->typespec_మాట == cts_dfloat32)
                error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "_Decimal32");
	      లేకపోతే ఒకవేళ (specs->typespec_మాట == cts_dfloat64)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "_Decimal64");
	      లేకపోతే ఒకవేళ (specs->typespec_మాట == cts_dfloat128)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "_Decimal128");
	      లేకపోతే ఒకవేళ (specs->typespec_మాట == cts_dfloat64x)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "_Decimal64x");
	      లేకపోతే
		{
		  specs->short_p = నిజం;
		  specs->locations[cdw_short] = loc;
		}
	      ఆపు;
	    స్థితి RID_SIGNED:
	      dupe = specs->signed_p;
	      ఒకవేళ (specs->unsigned_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "unsigned");
	      లేకపోతే ఒకవేళ (specs->typespec_మాట == cts_auto_type)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "__auto_type");
	      లేకపోతే ఒకవేళ (specs->typespec_మాట == cts_void)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "void");
	      లేకపోతే ఒకవేళ (specs->typespec_మాట == cts_bool)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "_Bool");
	      లేకపోతే ఒకవేళ (specs->typespec_మాట == cts_float)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "float");
	      లేకపోతే ఒకవేళ (specs->typespec_మాట == cts_double)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "double");
	      లేకపోతే ఒకవేళ (specs->typespec_మాట == cts_floatn_nx)
		error_at (loc,
			  "both %qs and %<_Float%d%s%> in declaration "
			  "specifiers", "signed",
			  floatn_nx_types[specs->u.floatn_nx_idx].n,
			  floatn_nx_types[specs->u.floatn_nx_idx].extended
			  ? "x"
			  : "");
	      లేకపోతే ఒకవేళ (specs->typespec_మాట == cts_dfloat32)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "_Decimal32");
	      లేకపోతే ఒకవేళ (specs->typespec_మాట == cts_dfloat64)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "_Decimal64");
	      లేకపోతే ఒకవేళ (specs->typespec_మాట == cts_dfloat128)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "_Decimal128");
	      లేకపోతే ఒకవేళ (specs->typespec_మాట == cts_dfloat64x)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "_Decimal64x");
	      లేకపోతే
		{
		  specs->signed_p = నిజం;
		  specs->locations[cdw_signed] = loc;
		}
	      ఆపు;
	    స్థితి RID_UNSIGNED:
	      dupe = specs->unsigned_p;
	      ఒకవేళ (specs->signed_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "unsigned");
	      లేకపోతే ఒకవేళ (specs->typespec_మాట == cts_auto_type)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "__auto_type");
	      లేకపోతే ఒకవేళ (specs->typespec_మాట == cts_void)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "void");
	      లేకపోతే ఒకవేళ (specs->typespec_మాట == cts_bool)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "_Bool");
	      లేకపోతే ఒకవేళ (specs->typespec_మాట == cts_float)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "float");
	      లేకపోతే ఒకవేళ (specs->typespec_మాట == cts_double)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "double");
	      లేకపోతే ఒకవేళ (specs->typespec_మాట == cts_floatn_nx)
		error_at (loc,
			  "both %qs and %<_Float%d%s%> in declaration "
			  "specifiers", "unsigned",
			  floatn_nx_types[specs->u.floatn_nx_idx].n,
			  floatn_nx_types[specs->u.floatn_nx_idx].extended
			  ? "x"
			  : "");
              లేకపోతే ఒకవేళ (specs->typespec_మాట == cts_dfloat32)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "_Decimal32");
	      లేకపోతే ఒకవేళ (specs->typespec_మాట == cts_dfloat64)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "_Decimal64");
	      లేకపోతే ఒకవేళ (specs->typespec_మాట == cts_dfloat128)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "_Decimal128");
	      లేకపోతే ఒకవేళ (specs->typespec_మాట == cts_dfloat64x)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "_Decimal64x");
	      లేకపోతే
		{
		  specs->unsigned_p = నిజం;
		  specs->locations[cdw_unsigned] = loc;
		}
	      ఆపు;
	    స్థితి RID_COMPLEX:
	      dupe = specs->complex_p;
	      ఒకవేళ (!లోపల_system_శీర్షిక_at (loc))
		pedwarn_c90 (loc, OPT_Wpedantic,
			     "ISO C90 does not support complex types");
	      ఒకవేళ (specs->typespec_మాట == cts_auto_type)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "__auto_type");
	      లేకపోతే ఒకవేళ (specs->typespec_మాట == cts_void)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "void");
	      లేకపోతే ఒకవేళ (specs->typespec_మాట == cts_bool)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "_Bool");
	      లేకపోతే ఒకవేళ (specs->typespec_మాట == cts_bitint)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "_BitInt");
              లేకపోతే ఒకవేళ (specs->typespec_మాట == cts_dfloat32)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "_Decimal32");
	      లేకపోతే ఒకవేళ (specs->typespec_మాట == cts_dfloat64)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "_Decimal64");
	      లేకపోతే ఒకవేళ (specs->typespec_మాట == cts_dfloat128)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "_Decimal128");
	      లేకపోతే ఒకవేళ (specs->typespec_మాట == cts_dfloat64x)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "_Decimal64x");
	      లేకపోతే ఒకవేళ (specs->typespec_మాట == cts_fract)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "_Fract");
	      లేకపోతే ఒకవేళ (specs->typespec_మాట == cts_accum)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "_Accum");
	      లేకపోతే ఒకవేళ (specs->saturating_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "_Sat");
	      లేకపోతే
		{
		  specs->complex_p = నిజం;
		  specs->locations[cdw_complex] = loc;
		}
	      ఆపు;
	    స్థితి RID_SAT:
	      dupe = specs->saturating_p;
	      pedwarn (loc, OPT_Wpedantic,
		       "ISO C does not support saturating types");
	      ఒకవేళ (specs->typespec_మాట == cts_int_n)
		error_at (loc,
			  "both %qs and %<__int%d%> in declaration specifiers",
			  "_Sat", int_n_దత్తాంశం[specs->u.int_n_idx].bitsize);
	      లేకపోతే ఒకవేళ (specs->typespec_మాట == cts_auto_type)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "__auto_type");
	      లేకపోతే ఒకవేళ (specs->typespec_మాట == cts_void)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "void");
	      లేకపోతే ఒకవేళ (specs->typespec_మాట == cts_bool)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "_Bool");
	      లేకపోతే ఒకవేళ (specs->typespec_మాట == cts_bitint)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "_BitInt");
	      లేకపోతే ఒకవేళ (specs->typespec_మాట == cts_char)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "char");
	      లేకపోతే ఒకవేళ (specs->typespec_మాట == cts_int)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "int");
	      లేకపోతే ఒకవేళ (specs->typespec_మాట == cts_float)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "float");
	      లేకపోతే ఒకవేళ (specs->typespec_మాట == cts_double)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "double");
	      లేకపోతే ఒకవేళ (specs->typespec_మాట == cts_floatn_nx)
		error_at (loc,
			  "both %qs and %<_Float%d%s%> in declaration "
			  "specifiers", "_Sat",
			  floatn_nx_types[specs->u.floatn_nx_idx].n,
			  floatn_nx_types[specs->u.floatn_nx_idx].extended
			  ? "x"
			  : "");
              లేకపోతే ఒకవేళ (specs->typespec_మాట == cts_dfloat32)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "_Decimal32");
	      లేకపోతే ఒకవేళ (specs->typespec_మాట == cts_dfloat64)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "_Decimal64");
	      లేకపోతే ఒకవేళ (specs->typespec_మాట == cts_dfloat128)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "_Decimal128");
	      లేకపోతే ఒకవేళ (specs->typespec_మాట == cts_dfloat64x)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "_Decimal64x");
	      లేకపోతే ఒకవేళ (specs->complex_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "complex");
	      లేకపోతే
		{
		  specs->saturating_p = నిజం;
		  specs->locations[cdw_saturating] = loc;
		}
	      ఆపు;
	    అప్రమేయ:
	      gcc_unreachable ();
	    }

	  ఒకవేళ (dupe)
	    error_at (loc, "duplicate %qE", type);

	  తిరిగి specs;
	}
      లేకపోతే
	{
	  /* "void", "_Bool", "char", "int", "float", "double",
	     "_FloatN", "_FloatNx", "_Decimal32", "__intN",
	     "_Decimal64", "_Decimal128", "_Fract", "_Accum", "_BitInt(N)" or
	     "__auto_type".  */
	  ఒకవేళ (specs->typespec_మాట != cts_none)
	    {
	      ఒకవేళ (i == RID_BOOL)
		{
		  auto_diagnostic_సమూహం d;
		  ఒకవేళ (specs->storage_class == csc_typedef)
		    error_at (loc,
			      "%qs cannot be defined via %<typedef%>",
			      IDENTIFIER_సూచిక (type));
		  లేకపోతే
		    error_at (loc,
			      "%qs cannot be used here",
			      IDENTIFIER_సూచిక (type));
		  కూడు_note_about_new_keyword (loc, type);
		}
	      లేకపోతే
		error_at (loc,
			  "two or more data types in declaration specifiers");
	      తిరిగి specs;
	    }
	  ఎంపిక (i)
	    {
	    స్థితి RID_AUTO_TYPE:
	      ఒకవేళ (specs->long_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "__auto_type");
	      లేకపోతే ఒకవేళ (specs->short_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "__auto_type");
	      లేకపోతే ఒకవేళ (specs->signed_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "__auto_type");
	      లేకపోతే ఒకవేళ (specs->unsigned_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "__auto_type");
	      లేకపోతే ఒకవేళ (specs->complex_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "__auto_type");
	      లేకపోతే ఒకవేళ (specs->saturating_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "__auto_type");
	      లేకపోతే
		{
		  specs->typespec_మాట = cts_auto_type;
		  specs->locations[cdw_typespec] = loc;
		}
	      తిరిగి specs;
	    స్థితి RID_INT_N_0:
	    స్థితి RID_INT_N_1:
	    స్థితి RID_INT_N_2:
	    స్థితి RID_INT_N_3:
	      specs->u.int_n_idx = i - RID_INT_N_0;
	      ఒకవేళ (!లోపల_system_శీర్షిక_at (ఆదానం_location)
		  /* If the INT_N type ends in "__", and so is of the format
		     "__intN__", don't pedwarn.  */
		  && (అక్షరశ్రేణి_పోలిక (IDENTIFIER_సూచిక (type)
			       + (IDENTIFIER_నిడివి (type) - 2), "__", 2) != 0))
		pedwarn (loc, OPT_Wpedantic,
			 "ISO C does not support %<__int%d%> types",
			 int_n_దత్తాంశం[specs->u.int_n_idx].bitsize);

	      ఒకవేళ (specs->long_p)
		error_at (loc,
			  "both %<__int%d%> and %qs in declaration specifiers",
			  int_n_దత్తాంశం[specs->u.int_n_idx].bitsize, "long");
	      లేకపోతే ఒకవేళ (specs->saturating_p)
		error_at (loc,
			  "both %qs and %<__int%d%> in declaration specifiers",
			  "_Sat", int_n_దత్తాంశం[specs->u.int_n_idx].bitsize);
	      లేకపోతే ఒకవేళ (specs->short_p)
		error_at (loc,
			  "both %<__int%d%> and %qs in declaration specifiers",
			  int_n_దత్తాంశం[specs->u.int_n_idx].bitsize, "short");
	      లేకపోతే ఒకవేళ (! int_n_enabled_p[specs->u.int_n_idx])
		{
		  specs->typespec_మాట = cts_int_n;
		  error_at (loc,
			    "%<__int%d%> is not supported on this target",
			    int_n_దత్తాంశం[specs->u.int_n_idx].bitsize);
		}
	      లేకపోతే
		{
		  specs->typespec_మాట = cts_int_n;
		  specs->locations[cdw_typespec] = loc;
		}
	      తిరిగి specs;
	    స్థితి RID_VOID:
	      ఒకవేళ (specs->long_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "void");
	      లేకపోతే ఒకవేళ (specs->short_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "void");
	      లేకపోతే ఒకవేళ (specs->signed_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "void");
	      లేకపోతే ఒకవేళ (specs->unsigned_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "void");
	      లేకపోతే ఒకవేళ (specs->complex_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "void");
	      లేకపోతే ఒకవేళ (specs->saturating_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "void");
	      లేకపోతే
		{
		  specs->typespec_మాట = cts_void;
		  specs->locations[cdw_typespec] = loc;
		}
	      తిరిగి specs;
	    స్థితి RID_BOOL:
	      ఒకవేళ (!లోపల_system_శీర్షిక_at (loc))
		pedwarn_c90 (loc, OPT_Wpedantic,
			     "ISO C90 does not support boolean types");
	      ఒకవేళ (specs->long_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "_Bool");
	      లేకపోతే ఒకవేళ (specs->short_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "_Bool");
	      లేకపోతే ఒకవేళ (specs->signed_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "_Bool");
	      లేకపోతే ఒకవేళ (specs->unsigned_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "_Bool");
	      లేకపోతే ఒకవేళ (specs->complex_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "_Bool");
	      లేకపోతే ఒకవేళ (specs->saturating_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "_Bool");
	      లేకపోతే
		{
		  specs->typespec_మాట = cts_bool;
		  specs->locations[cdw_typespec] = loc;
		}
	      తిరిగి specs;
	    స్థితి RID_CHAR:
	      ఒకవేళ (specs->long_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "char");
	      లేకపోతే ఒకవేళ (specs->short_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "char");
	      లేకపోతే ఒకవేళ (specs->saturating_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "char");
	      లేకపోతే
		{
		  specs->typespec_మాట = cts_char;
		  specs->locations[cdw_typespec] = loc;
		}
	      తిరిగి specs;
	    స్థితి RID_INT:
	      ఒకవేళ (specs->saturating_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "int");
	      లేకపోతే
		{
		  specs->typespec_మాట = cts_int;
		  specs->locations[cdw_typespec] = loc;
		}
	      తిరిగి specs;
	    స్థితి RID_FLOAT:
	      ఒకవేళ (specs->long_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "float");
	      లేకపోతే ఒకవేళ (specs->short_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "float");
	      లేకపోతే ఒకవేళ (specs->signed_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "float");
	      లేకపోతే ఒకవేళ (specs->unsigned_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "float");
	      లేకపోతే ఒకవేళ (specs->saturating_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "float");
	      లేకపోతే
		{
		  specs->typespec_మాట = cts_float;
		  specs->locations[cdw_typespec] = loc;
		}
	      తిరిగి specs;
	    స్థితి RID_DOUBLE:
	      ఒకవేళ (specs->long_long_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long long", "double");
	      లేకపోతే ఒకవేళ (specs->short_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "double");
	      లేకపోతే ఒకవేళ (specs->signed_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "double");
	      లేకపోతే ఒకవేళ (specs->unsigned_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "double");
	      లేకపోతే ఒకవేళ (specs->saturating_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "double");
	      లేకపోతే
		{
		  specs->typespec_మాట = cts_double;
		  specs->locations[cdw_typespec] = loc;
		}
	      తిరిగి specs;
	    CASE_RID_FLOATN_NX:
	      specs->u.floatn_nx_idx = i - RID_FLOATN_NX_మొదటి;
	      ఒకవేళ (!లోపల_system_శీర్షిక_at (ఆదానం_location))
		pedwarn_c11 (loc, OPT_Wpedantic,
			     "ISO C does not support the %<_Float%d%s%> type"
			     " before C23",
			     floatn_nx_types[specs->u.floatn_nx_idx].n,
			     floatn_nx_types[specs->u.floatn_nx_idx].extended
			     ? "x"
			     : "");

	      ఒకవేళ (specs->long_p)
		error_at (loc,
			  "both %qs and %<_Float%d%s%> in declaration "
			  "specifiers", "long",
			  floatn_nx_types[specs->u.floatn_nx_idx].n,
			  floatn_nx_types[specs->u.floatn_nx_idx].extended
			  ? "x"
			  : "");
	      లేకపోతే ఒకవేళ (specs->short_p)
		error_at (loc,
			  "both %qs and %<_Float%d%s%> in declaration "
			  "specifiers", "short",
			  floatn_nx_types[specs->u.floatn_nx_idx].n,
			  floatn_nx_types[specs->u.floatn_nx_idx].extended
			  ? "x"
			  : "");
	      లేకపోతే ఒకవేళ (specs->signed_p)
		error_at (loc,
			  "both %qs and %<_Float%d%s%> in declaration "
			  "specifiers", "signed",
			  floatn_nx_types[specs->u.floatn_nx_idx].n,
			  floatn_nx_types[specs->u.floatn_nx_idx].extended
			  ? "x"
			  : "");
	      లేకపోతే ఒకవేళ (specs->unsigned_p)
		error_at (loc,
			  "both %qs and %<_Float%d%s%> in declaration "
			  "specifiers", "unsigned",
			  floatn_nx_types[specs->u.floatn_nx_idx].n,
			  floatn_nx_types[specs->u.floatn_nx_idx].extended
			  ? "x"
			  : "");
	      లేకపోతే ఒకవేళ (specs->saturating_p)
		error_at (loc,
			  "both %qs and %<_Float%d%s%> in declaration "
			  "specifiers", "_Sat",
			  floatn_nx_types[specs->u.floatn_nx_idx].n,
			  floatn_nx_types[specs->u.floatn_nx_idx].extended
			  ? "x"
			  : "");
	      లేకపోతే ఒకవేళ (FLOATN_NX_TYPE_కణుపు (specs->u.floatn_nx_idx) == NULL_వృక్షం)
		{
		  specs->typespec_మాట = cts_floatn_nx;
		  error_at (loc,
			    "%<_Float%d%s%> is not supported on this target",
			    floatn_nx_types[specs->u.floatn_nx_idx].n,
			    floatn_nx_types[specs->u.floatn_nx_idx].extended
			    ? "x"
			    : "");
		}
	      లేకపోతే
		{
		  specs->typespec_మాట = cts_floatn_nx;
		  specs->locations[cdw_typespec] = loc;
		}
	      తిరిగి specs;
	    స్థితి RID_DFLOAT32:
	    స్థితి RID_DFLOAT64:
	    స్థితి RID_DFLOAT128:
	    స్థితి RID_DFLOAT64X:
	      {
		స్థిరరాశి అక్షరం *str;
		ఒకవేళ (i == RID_DFLOAT32)
		  str = "_Decimal32";
		లేకపోతే ఒకవేళ (i == RID_DFLOAT64)
		  str = "_Decimal64";
		లేకపోతే ఒకవేళ (i == RID_DFLOAT128)
		  str = "_Decimal128";
		లేకపోతే
		  str = "_Decimal64x";
		ఒకవేళ (specs->long_long_p)
		  error_at (loc,
			    "both %qs and %qs in declaration specifiers",
			    "long long", str);
		ఒకవేళ (specs->long_p)
		  error_at (loc,
			    "both %qs and %qs in declaration specifiers",
			    "long", str);
		లేకపోతే ఒకవేళ (specs->short_p)
		  error_at (loc,
			    "both %qs and %qs in declaration specifiers",
			    "short", str);
		లేకపోతే ఒకవేళ (specs->signed_p)
		  error_at (loc,
			    "both %qs and %qs in declaration specifiers",
			    "signed", str);
		లేకపోతే ఒకవేళ (specs->unsigned_p)
		  error_at (loc,
			    "both %qs and %qs in declaration specifiers",
			    "unsigned", str);
                లేకపోతే ఒకవేళ (specs->complex_p)
                  error_at (loc,
			    "both %qs and %qs in declaration specifiers",
			    "complex", str);
                లేకపోతే ఒకవేళ (specs->saturating_p)
                  error_at (loc,
			    "both %qs and %qs in declaration specifiers",
			    "_Sat", str);
		లేకపోతే ఒకవేళ (i == RID_DFLOAT32)
		  specs->typespec_మాట = cts_dfloat32;
		లేకపోతే ఒకవేళ (i == RID_DFLOAT64)
		  specs->typespec_మాట = cts_dfloat64;
		లేకపోతే ఒకవేళ (i == RID_DFLOAT128)
		  specs->typespec_మాట = cts_dfloat128;
		లేకపోతే
		  specs->typespec_మాట = cts_dfloat64x;
		specs->locations[cdw_typespec] = loc;
	      }
	      ఒకవేళ (!targetm.decimal_float_supported_p ())
		error_at (loc,
			  "decimal floating-point not supported "
			  "for this target");
	      pedwarn_c11 (loc, OPT_Wpedantic,
			   "ISO C does not support decimal floating-point "
			   "before C23");
	      తిరిగి specs;
	    స్థితి RID_FRACT:
	    స్థితి RID_ACCUM:
	      {
		స్థిరరాశి అక్షరం *str;
		ఒకవేళ (i == RID_FRACT)
		  str = "_Fract";
		లేకపోతే
		  str = "_Accum";
                ఒకవేళ (specs->complex_p)
                  error_at (loc,
			    "both %qs and %qs in declaration specifiers",
			    "complex", str);
		లేకపోతే ఒకవేళ (i == RID_FRACT)
		    specs->typespec_మాట = cts_fract;
		లేకపోతే
		    specs->typespec_మాట = cts_accum;
		specs->locations[cdw_typespec] = loc;
	      }
	      ఒకవేళ (!targetm.fixed_బిందువు_supported_p ())
		error_at (loc,
			  "fixed-point types not supported for this target");
	      pedwarn (loc, OPT_Wpedantic,
		       "ISO C does not support fixed-point types");
	      తిరిగి specs;
	    స్థితి RID_BITINT:
	      ఒకవేళ (specs->long_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "_BitInt");
	      లేకపోతే ఒకవేళ (specs->short_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "_BitInt");
	      లేకపోతే ఒకవేళ (specs->complex_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "_BitInt");
	      లేకపోతే ఒకవేళ (specs->saturating_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "_BitInt");
	      లేకపోతే
		{
		  specs->typespec_మాట = cts_bitint;
		  specs->locations[cdw_typespec] = loc;
		  specs->u.bitint_prec = -1;
		  ఒకవేళ (error_నిర్వాహ్యం_p (spec.సమాసం))
		    తిరిగి specs;
		  ఒకవేళ (వృక్షం_సంకేతం (spec.సమాసం) != INTEGER_CST
		      || !INTEGRAL_TYPE_P (వృక్షం_TYPE (spec.సమాసం)))
		    {
		      error_at (loc, "%<_BitInt%> argument is not an integer "
				     "constant expression");
		      తిరిగి specs;
		    }
		  ఒకవేళ (వృక్షం_int_cst_sgn (spec.సమాసం) <= 0)
		    {
		      error_at (loc, "%<_BitInt%> argument %qE is not a "
				     "positive integer constant expression",
				spec.సమాసం);
		      తిరిగి specs;
		    }
		  ఒకవేళ (wi::గమ్యం_widest (spec.సమాసం) > WIDE_INT_MAX_PRECISION - 1)
		    {
		      error_at (loc, "%<_BitInt%> argument %qE is larger than "
				     "%<BITINT_MAXWIDTH%> %qd",
				spec.సమాసం, (పూర్ణాంకం) WIDE_INT_MAX_PRECISION - 1);
		      తిరిగి specs;
		    }
		  specs->u.bitint_prec = వృక్షం_గమ్యం_uhwi (spec.సమాసం);
		  నిర్మాణం bitint_info info;
		  ఒకవేళ (!targetm.c.bitint_type_info (specs->u.bitint_prec,
						   &info))
		    {
		      sorry_at (loc, "%<_BitInt(%d)%> is not supported on "
				     "this target", specs->u.bitint_prec);
		      specs->u.bitint_prec = -1;
		      తిరిగి specs;
		    }
		}
	      తిరిగి specs;
	    అప్రమేయ:
	      /* ObjC reserved word "id", handled below.  */
	      ఆపు;
	    }
	}
    }

  /* Now we have a typedef (a TYPE_DECL node), an identifier (some
     form of ObjC type, cases such as "int" and "long" being handled
     above), a TYPE (struct, union, enum and typeof specifiers) or an
     ERROR_MARK.  In none of these cases may there have previously
     been any type specifiers.  */
  ఒకవేళ (specs->type || specs->typespec_మాట != cts_none
      || specs->long_p || specs->short_p || specs->signed_p
      || specs->unsigned_p || specs->complex_p)
    error_at (loc, "two or more data types in declaration specifiers");
  లేకపోతే ఒకవేళ (వృక్షం_సంకేతం (type) == TYPE_DECL)
    {
      specs->type = వృక్షం_TYPE (type);
      ఒకవేళ (వృక్షం_TYPE (type) != error_mark_కణుపు)
	{
	  mark_decl_వాడిన (type, అబద్ధం);
	  specs->decl_attr = DECL_లక్షణాలు (type);
	  specs->typedef_p = నిజం;
	  specs->explicit_signed_p = C_TYPEDEF_EXPLICITLY_SIGNED (type);
	  specs->locations[cdw_typedef] = loc;

	  /* If this typedef name is defined in a struct, then a C++
	     lookup would return a different value.  */
	  ఒకవేళ (warn_cxx_compat
	      && I_చిహ్నం_BINDING (DECL_NAME (type))->లోపల_struct)
	    warning_at (loc, OPT_Wc___compat,
			"C++ lookup of %qD would return a field, not a type",
			type);

	  /* If we are parsing a struct, record that a struct field
	     used a typedef.  */
	  ఒకవేళ (warn_cxx_compat && struct_parse_info != ఖాళీ)
	    struct_parse_info->typedefs_చూసిన.సురక్షిత_నెట్టు (type);
	}
    }
  లేకపోతే ఒకవేళ (వృక్షం_సంకేతం (type) == IDENTIFIER_కణుపు)
    {
      వృక్షం t = lookup_name (type);
      ఒకవేళ (!t || వృక్షం_సంకేతం (t) != TYPE_DECL)
	error_at (loc, "%qE fails to be a typedef or built in type", type);
      లేకపోతే ఒకవేళ (వృక్షం_TYPE (t) == error_mark_కణుపు)
	;
      లేకపోతే
	{
	  specs->type = వృక్షం_TYPE (t);
	  specs->locations[cdw_typespec] = loc;
	}
    }
  లేకపోతే
    {
      ఒకవేళ (వృక్షం_సంకేతం (type) != ERROR_MARK)
	{
	  ఒకవేళ (spec.రకం == ctsk_typeof)
	    {
	      specs->typedef_p = నిజం;
	      specs->locations[cdw_typedef] = loc;
	    }

	  ఒకవేళ (వృక్షం_సంకేతం (type) == రికార్డు_TYPE || వృక్షం_సంకేతం (type) == UNION_TYPE
	      || వృక్షం_సంకేతం (type) == ENUMERAL_TYPE)
	    mark_decl_వాడిన (TYPE_STUB_DECL (type), అబద్ధం);

	  ఒకవేళ (spec.సమాసం)
	    {
	      వృక్షం సమాసం = save_సమాసం (fold_convert (void_type_కణుపు, spec.సమాసం));
	      ఒకవేళ (specs->సమాసం)
		specs->సమాసం = build2 (COMPOUND_సమాసం, వృక్షం_TYPE (సమాసం),
				      specs->సమాసం, సమాసం);
	      లేకపోతే
		specs->సమాసం = సమాసం;
	      specs->సమాసం_const_operands &= spec.సమాసం_const_operands;
	    }
	}
      specs->type = type;
      ఒకవేళ (spec.has_enum_type_specifier
	  && spec.రకం != ctsk_tagdef)
	specs->enum_type_specifier_ref_p = నిజం;
    }

  తిరిగి specs;
}

/* Add the storage class specifier or function specifier SCSPEC to the
   declaration specifiers SPECS, returning SPECS.  */

నిర్మాణం c_declspecs *
declspecs_కూడు_scspec (location_t loc,
		      నిర్మాణం c_declspecs *specs,
		      వృక్షం scspec)
{
  గణన rid i;
  గణన c_storage_class n = csc_none;
  తార్కిక dupe = అబద్ధం;
  specs->declspecs_చూసిన_p = నిజం;
  specs->non_std_attrs_చూసిన_p = నిజం;
  gcc_assert (వృక్షం_సంకేతం (scspec) == IDENTIFIER_కణుపు
	      && C_IS_RESERVED_మాట (scspec));
  i = C_RID_సంకేతం (scspec);
  ఒకవేళ (specs->non_sc_చూసిన_p)
    warning (OPT_Wold_style_declaration,
             "%qE is not at beginning of declaration", scspec);
  ఎంపిక (i)
    {
    స్థితి RID_INLINE:
      /* C99 permits duplicate inline.  Although of doubtful utility,
	 it seems simplest to permit it in gnu89 mode as well, as
	 there is also little utility in maintaining this as a
	 difference between gnu89 and C99 inline.  */
      dupe = అబద్ధం;
      specs->inline_p = నిజం;
      specs->locations[cdw_inline] = loc;
      ఆపు;
    స్థితి RID_NORETURN:
      /* Duplicate _Noreturn is permitted.  */
      dupe = అబద్ధం;
      specs->noreturn_p = నిజం;
      specs->locations[cdw_noreturn] = loc;
      ఆపు;
    స్థితి RID_THREAD:
      dupe = specs->thread_p;
      ఒకవేళ (specs->storage_class == csc_auto)
	error ("%qE used with %<auto%>", scspec);
      లేకపోతే ఒకవేళ (specs->storage_class == csc_రిజిస్టరు)
	error ("%qE used with %<register%>", scspec);
      లేకపోతే ఒకవేళ (specs->storage_class == csc_typedef)
	error ("%qE used with %<typedef%>", scspec);
      లేకపోతే ఒకవేళ (specs->constexpr_p)
	error ("%qE used with %<constexpr%>", scspec);
      లేకపోతే
	{
	  specs->thread_p = నిజం;
	  specs->thread_gnu_p = (strcmp (IDENTIFIER_సూచిక (scspec),
					 "__thread") == 0);
	  /* A diagnostic is not required for the use of this
	     identifier in the implementation namespace; only diagnose
	     it for the C11 spelling because of existing code using
	     the other spelling.  */
	  ఒకవేళ (!specs->thread_gnu_p)
	    {
	      ఒకవేళ (flag_isoc99)
		pedwarn_c99 (loc, OPT_Wpedantic,
			     "ISO C99 does not support %qE", scspec);
	      లేకపోతే
		pedwarn_c99 (loc, OPT_Wpedantic,
			     "ISO C90 does not support %qE", scspec);
	    }
	  specs->locations[cdw_thread] = loc;
	}
      ఆపు;
    స్థితి RID_AUTO:
      ఒకవేళ (flag_isoc23
	  && specs->typespec_రకం == ctsk_none
	  && specs->storage_class != csc_typedef)
	{
	  /* "auto" potentially used for type deduction.  */
	  ఒకవేళ (specs->c23_auto_p)
	    error ("duplicate %qE", scspec);
	  specs->c23_auto_p = నిజం;
	  తిరిగి specs;
	}
      n = csc_auto;
      /* auto may only be used with another storage class specifier,
	 such as constexpr, if the type is inferred.  */
      ఒకవేళ (specs->constexpr_p)
	error ("%qE used with %<constexpr%>", scspec);
      ఆపు;
    స్థితి RID_EXTERN:
      n = csc_extern;
      /* Diagnose "__thread extern".  */
      ఒకవేళ (specs->thread_p && specs->thread_gnu_p)
	error ("%<__thread%> before %<extern%>");
      ఆపు;
    స్థితి RID_రిజిస్టరు:
      n = csc_రిజిస్టరు;
      ఆపు;
    స్థితి RID_STATIC:
      n = csc_static;
      /* Diagnose "__thread static".  */
      ఒకవేళ (specs->thread_p && specs->thread_gnu_p)
	error ("%<__thread%> before %<static%>");
      ఆపు;
    స్థితి RID_TYPEDEF:
      n = csc_typedef;
      ఒకవేళ (specs->c23_auto_p)
	{
	  error ("%<typedef%> used with %<auto%>");
	  specs->c23_auto_p = అబద్ధం;
	}
      ఆపు;
    స్థితి RID_CONSTEXPR:
      dupe = specs->constexpr_p;
      ఒకవేళ (specs->storage_class == csc_extern)
	error ("%qE used with %<extern%>", scspec);
      లేకపోతే ఒకవేళ (specs->storage_class == csc_typedef)
	error ("%qE used with %<typedef%>", scspec);
      లేకపోతే ఒకవేళ (specs->storage_class == csc_auto)
	/* auto may only be used with another storage class specifier,
	   such as constexpr, if the type is inferred.  */
	error ("%qE used with %<auto%>", scspec);
      లేకపోతే ఒకవేళ (specs->thread_p)
	error ("%qE used with %qs", scspec,
	       specs->thread_gnu_p ? "__thread" : "_Thread_local");
      లేకపోతే
	specs->constexpr_p = నిజం;
      ఆపు;
    అప్రమేయ:
      gcc_unreachable ();
    }
  ఒకవేళ (n != csc_none && n == specs->storage_class)
    dupe = నిజం;
  ఒకవేళ (dupe)
    {
      ఒకవేళ (i == RID_THREAD)
	error ("duplicate %<_Thread_local%> or %<__thread%>");
      లేకపోతే
	error ("duplicate %qE", scspec);
    }
  ఒకవేళ (n != csc_none)
    {
      ఒకవేళ (specs->storage_class != csc_none && n != specs->storage_class)
	{
	  error ("multiple storage classes in declaration specifiers");
	}
      లేకపోతే
	{
	  specs->storage_class = n;
	  specs->locations[cdw_storage_class] = loc;
	  ఒకవేళ (n != csc_extern && n != csc_static && specs->thread_p)
	    {
	      error ("%qs used with %qE",
		     specs->thread_gnu_p ? "__thread" : "_Thread_local",
		     scspec);
	      specs->thread_p = అబద్ధం;
	    }
	  ఒకవేళ (n != csc_auto && n != csc_రిజిస్టరు && n != csc_static
	      && specs->constexpr_p)
	    {
	      error ("%<constexpr%> used with %qE", scspec);
	      specs->constexpr_p = అబద్ధం;
	    }
	}
    }
  తిరిగి specs;
}

/* Add the attributes ATTRS to the declaration specifiers SPECS,
   returning SPECS.  */

నిర్మాణం c_declspecs *
declspecs_కూడు_attrs (location_t loc, నిర్మాణం c_declspecs *specs, వృక్షం attrs)
{
  specs->attrs = chainon (attrs, specs->attrs);
  specs->locations[cdw_లక్షణాలు] = loc;
  specs->declspecs_చూసిన_p = నిజం;
  /* In the case of standard attributes at the start of the
     declaration, the caller will reset this.  */
  specs->non_std_attrs_చూసిన_p = నిజం;
  తిరిగి specs;
}

/* Add an _Alignas specifier (expression ALIGN, or type whose
   alignment is ALIGN) to the declaration specifiers SPECS, returning
   SPECS.  */
నిర్మాణం c_declspecs *
declspecs_కూడు_alignas (location_t loc,
		       నిర్మాణం c_declspecs *specs, వృక్షం align)
{
  specs->alignas_p = నిజం;
  specs->locations[cdw_alignas] = loc;
  ఒకవేళ (align == error_mark_కణుపు)
    తిరిగి specs;

  /* Only accept the alignment if it's valid and greater than
     the current one.  Zero is invalid but by C11 required to
     be silently ignored.  */
  పూర్ణాంకం align_log = check_user_alignment (align, అబద్ధం, /* warn_zero = */అబద్ధం);
  ఒకవేళ (align_log > specs->align_log)
    specs->align_log = align_log;
  తిరిగి specs;
}

/* Combine "long", "short", "signed", "unsigned" and "_Complex" type
   specifiers with any other type specifier to determine the resulting
   type.  This is where ISO C checks on complex types are made, since
   "_Complex long" is a prefix of the valid ISO C type "_Complex long
   double".  Also apply postfix standard attributes to modify the type.  */

నిర్మాణం c_declspecs *
ముగింపు_declspecs (నిర్మాణం c_declspecs *specs)
{
  /* If a type was specified as a whole, we have no modifiers and are
     done.  */
  ఒకవేళ (specs->type != NULL_వృక్షం)
    {
      gcc_assert (!specs->long_p && !specs->long_long_p && !specs->short_p
		  && !specs->signed_p && !specs->unsigned_p
		  && !specs->complex_p && !specs->c23_auto_p);

      /* Set a dummy type.  */
      ఒకవేళ (వృక్షం_సంకేతం (specs->type) == ERROR_MARK)
        specs->type = integer_type_కణుపు;
      వెళ్ళు handle_postfix_attrs;
    }

  /* If none of "void", "_Bool", "char", "int", "float" or "double"
     has been specified, treat it as "int" unless "_Complex" is
     present and there are no other specifiers.  If we just have
     "_Complex", it is equivalent to "_Complex double", but e.g.
     "_Complex short" is equivalent to "_Complex short int".  */
  ఒకవేళ (specs->typespec_మాట == cts_none)
    {
      ఒకవేళ (specs->saturating_p)
	{
	  error_at (specs->locations[cdw_saturating],
		    "%<_Sat%> is used without %<_Fract%> or %<_Accum%>");
	  ఒకవేళ (!targetm.fixed_బిందువు_supported_p ())
	    error_at (specs->locations[cdw_saturating],
		      "fixed-point types not supported for this target");
	  specs->typespec_మాట = cts_fract;
	}
      లేకపోతే ఒకవేళ (specs->long_p || specs->short_p
	       || specs->signed_p || specs->unsigned_p)
	{
	  specs->typespec_మాట = cts_int;
	}
      లేకపోతే ఒకవేళ (specs->complex_p)
	{
	  specs->typespec_మాట = cts_double;
	  pedwarn (specs->locations[cdw_complex], OPT_Wpedantic,
		   "ISO C does not support plain %<complex%> meaning "
		   "%<double complex%>");
	}
      లేకపోతే ఒకవేళ (specs->c23_auto_p)
	{
	  /* Type to be filled in later, including applying postfix
	     attributes.  This warning only actually appears for
	     -Wc11-c23-compat in C23 mode; in older modes, there may
	     be a warning or pedwarn for implicit "int" instead, or
	     other errors for use of auto at file scope.  */
	  pedwarn_c11 (ఆదానం_location, OPT_Wpedantic,
		       "ISO C does not support %<auto%> type deduction "
		       "before C23");
	  తిరిగి specs;
	}
      లేకపోతే
	{
	  specs->typespec_మాట = cts_int;
	  specs->default_int_p = నిజం;
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
  ఎంపిక (specs->typespec_మాట)
    {
    స్థితి cts_auto_type:
      gcc_assert (!specs->long_p && !specs->short_p
		  && !specs->signed_p && !specs->unsigned_p
		  && !specs->complex_p);
      /* Type to be filled in later.  */
      ఒకవేళ (specs->postfix_attrs)
	error ("%<__auto_type%> followed by %<[[]]%> attributes");
      ఆపు;
    స్థితి cts_void:
      gcc_assert (!specs->long_p && !specs->short_p
		  && !specs->signed_p && !specs->unsigned_p
		  && !specs->complex_p);
      specs->type = void_type_కణుపు;
      ఆపు;
    స్థితి cts_bool:
      gcc_assert (!specs->long_p && !specs->short_p
		  && !specs->signed_p && !specs->unsigned_p
		  && !specs->complex_p);
      specs->type = boolean_type_కణుపు;
      ఆపు;
    స్థితి cts_char:
      gcc_assert (!specs->long_p && !specs->short_p);
      gcc_assert (!(specs->signed_p && specs->unsigned_p));
      ఒకవేళ (specs->signed_p)
	specs->type = signed_char_type_కణుపు;
      లేకపోతే ఒకవేళ (specs->unsigned_p)
	specs->type = unsigned_char_type_కణుపు;
      లేకపోతే
	specs->type = char_type_కణుపు;
      ఒకవేళ (specs->complex_p)
	{
	  pedwarn (specs->locations[cdw_complex], OPT_Wpedantic,
		   "ISO C does not support complex integer types");
	  specs->type = build_complex_type (specs->type);
	}
      ఆపు;
    స్థితి cts_int_n:
      gcc_assert (!specs->long_p && !specs->short_p && !specs->long_long_p);
      gcc_assert (!(specs->signed_p && specs->unsigned_p));
      ఒకవేళ (! int_n_enabled_p[specs->u.int_n_idx])
	specs->type = integer_type_కణుపు;
      లేకపోతే
	specs->type = (specs->unsigned_p
		       ? int_n_trees[specs->u.int_n_idx].unsigned_type
		       : int_n_trees[specs->u.int_n_idx].signed_type);
      ఒకవేళ (specs->complex_p)
	{
	  pedwarn (specs->locations[cdw_complex], OPT_Wpedantic,
		   "ISO C does not support complex integer types");
	  specs->type = build_complex_type (specs->type);
	}
      ఆపు;
    స్థితి cts_int:
      gcc_assert (!(specs->long_p && specs->short_p));
      gcc_assert (!(specs->signed_p && specs->unsigned_p));
      ఒకవేళ (specs->long_long_p)
	specs->type = (specs->unsigned_p
		       ? long_long_unsigned_type_కణుపు
		       : long_long_integer_type_కణుపు);
      లేకపోతే ఒకవేళ (specs->long_p)
	specs->type = (specs->unsigned_p
		       ? long_unsigned_type_కణుపు
		       : long_integer_type_కణుపు);
      లేకపోతే ఒకవేళ (specs->short_p)
	specs->type = (specs->unsigned_p
		       ? short_unsigned_type_కణుపు
		       : short_integer_type_కణుపు);
      లేకపోతే
	specs->type = (specs->unsigned_p
		       ? unsigned_type_కణుపు
		       : integer_type_కణుపు);
      ఒకవేళ (specs->complex_p)
	{
	  pedwarn (specs->locations[cdw_complex], OPT_Wpedantic,
		   "ISO C does not support complex integer types");
	  specs->type = build_complex_type (specs->type);
	}
      ఆపు;
    స్థితి cts_float:
      gcc_assert (!specs->long_p && !specs->short_p
		  && !specs->signed_p && !specs->unsigned_p);
      specs->type = (specs->complex_p
		     ? complex_float_type_కణుపు
		     : float_type_కణుపు);
      ఆపు;
    స్థితి cts_double:
      gcc_assert (!specs->long_long_p && !specs->short_p
		  && !specs->signed_p && !specs->unsigned_p);
      ఒకవేళ (specs->long_p)
	{
	  specs->type = (specs->complex_p
			 ? complex_long_double_type_కణుపు
			 : long_double_type_కణుపు);
	}
      లేకపోతే
	{
	  specs->type = (specs->complex_p
			 ? complex_double_type_కణుపు
			 : double_type_కణుపు);
	}
      ఆపు;
    స్థితి cts_floatn_nx:
      gcc_assert (!specs->long_p && !specs->short_p
		  && !specs->signed_p && !specs->unsigned_p);
      ఒకవేళ (FLOATN_NX_TYPE_కణుపు (specs->u.floatn_nx_idx) == NULL_వృక్షం)
	specs->type = integer_type_కణుపు;
      లేకపోతే ఒకవేళ (specs->complex_p)
	specs->type = COMPLEX_FLOATN_NX_TYPE_కణుపు (specs->u.floatn_nx_idx);
      లేకపోతే
	specs->type = FLOATN_NX_TYPE_కణుపు (specs->u.floatn_nx_idx);
      ఆపు;
    స్థితి cts_dfloat32:
    స్థితి cts_dfloat64:
    స్థితి cts_dfloat128:
    స్థితి cts_dfloat64x:
      gcc_assert (!specs->long_p && !specs->long_long_p && !specs->short_p
		  && !specs->signed_p && !specs->unsigned_p && !specs->complex_p);
      ఒకవేళ (!targetm.decimal_float_supported_p ())
	specs->type = integer_type_కణుపు;
      లేకపోతే ఒకవేళ (specs->typespec_మాట == cts_dfloat32)
	specs->type = dfloat32_type_కణుపు;
      లేకపోతే ఒకవేళ (specs->typespec_మాట == cts_dfloat64)
	specs->type = dfloat64_type_కణుపు;
      లేకపోతే ఒకవేళ (specs->typespec_మాట == cts_dfloat128)
	specs->type = dfloat128_type_కణుపు;
      లేకపోతే
	specs->type = dfloat64x_type_కణుపు;
      ఆపు;
    స్థితి cts_fract:
      gcc_assert (!specs->complex_p);
      ఒకవేళ (!targetm.fixed_బిందువు_supported_p ())
	specs->type = integer_type_కణుపు;
      లేకపోతే ఒకవేళ (specs->saturating_p)
	{
	  ఒకవేళ (specs->long_long_p)
	    specs->type = specs->unsigned_p
			  ? sat_unsigned_long_long_fract_type_కణుపు
			  : sat_long_long_fract_type_కణుపు;
	  లేకపోతే ఒకవేళ (specs->long_p)
	    specs->type = specs->unsigned_p
			  ? sat_unsigned_long_fract_type_కణుపు
			  : sat_long_fract_type_కణుపు;
	  లేకపోతే ఒకవేళ (specs->short_p)
	    specs->type = specs->unsigned_p
			  ? sat_unsigned_short_fract_type_కణుపు
			  : sat_short_fract_type_కణుపు;
	  లేకపోతే
	    specs->type = specs->unsigned_p
			  ? sat_unsigned_fract_type_కణుపు
			  : sat_fract_type_కణుపు;
	}
      లేకపోతే
	{
	  ఒకవేళ (specs->long_long_p)
	    specs->type = specs->unsigned_p
			  ? unsigned_long_long_fract_type_కణుపు
			  : long_long_fract_type_కణుపు;
	  లేకపోతే ఒకవేళ (specs->long_p)
	    specs->type = specs->unsigned_p
			  ? unsigned_long_fract_type_కణుపు
			  : long_fract_type_కణుపు;
	  లేకపోతే ఒకవేళ (specs->short_p)
	    specs->type = specs->unsigned_p
			  ? unsigned_short_fract_type_కణుపు
			  : short_fract_type_కణుపు;
	  లేకపోతే
	    specs->type = specs->unsigned_p
			  ? unsigned_fract_type_కణుపు
			  : fract_type_కణుపు;
	}
      ఆపు;
    స్థితి cts_accum:
      gcc_assert (!specs->complex_p);
      ఒకవేళ (!targetm.fixed_బిందువు_supported_p ())
	specs->type = integer_type_కణుపు;
      లేకపోతే ఒకవేళ (specs->saturating_p)
	{
	  ఒకవేళ (specs->long_long_p)
	    specs->type = specs->unsigned_p
			  ? sat_unsigned_long_long_accum_type_కణుపు
			  : sat_long_long_accum_type_కణుపు;
	  లేకపోతే ఒకవేళ (specs->long_p)
	    specs->type = specs->unsigned_p
			  ? sat_unsigned_long_accum_type_కణుపు
			  : sat_long_accum_type_కణుపు;
	  లేకపోతే ఒకవేళ (specs->short_p)
	    specs->type = specs->unsigned_p
			  ? sat_unsigned_short_accum_type_కణుపు
			  : sat_short_accum_type_కణుపు;
	  లేకపోతే
	    specs->type = specs->unsigned_p
			  ? sat_unsigned_accum_type_కణుపు
			  : sat_accum_type_కణుపు;
	}
      లేకపోతే
	{
	  ఒకవేళ (specs->long_long_p)
	    specs->type = specs->unsigned_p
			  ? unsigned_long_long_accum_type_కణుపు
			  : long_long_accum_type_కణుపు;
	  లేకపోతే ఒకవేళ (specs->long_p)
	    specs->type = specs->unsigned_p
			  ? unsigned_long_accum_type_కణుపు
			  : long_accum_type_కణుపు;
	  లేకపోతే ఒకవేళ (specs->short_p)
	    specs->type = specs->unsigned_p
			  ? unsigned_short_accum_type_కణుపు
			  : short_accum_type_కణుపు;
	  లేకపోతే
	    specs->type = specs->unsigned_p
			  ? unsigned_accum_type_కణుపు
			  : accum_type_కణుపు;
	}
      ఆపు;
    స్థితి cts_bitint:
      gcc_assert (!specs->long_p && !specs->short_p
		  && !specs->complex_p);
      ఒకవేళ (!specs->unsigned_p && specs->u.bitint_prec == 1 && !flag_isoc2y)
	{
	  error_at (specs->locations[cdw_typespec],
		    "%<signed _BitInt%> argument must be at least 2 "
		    "before C2Y");
	  specs->type = integer_type_కణుపు;
	  ఆపు;
	}
      ఒకవేళ (specs->u.bitint_prec == -1)
	specs->type = integer_type_కణుపు;
      లేకపోతే
	{
	  pedwarn_c11 (specs->locations[cdw_typespec], OPT_Wpedantic,
		       "ISO C does not support %<%s_BitInt(%d)%> before C23",
		       specs->unsigned_p ? "unsigned "
		       : specs->signed_p ? "signed " : "",
		       specs->u.bitint_prec);
	  specs->type = build_bitint_type (specs->u.bitint_prec,
					   specs->unsigned_p);
	}
      ఆపు;
    అప్రమేయ:
      gcc_unreachable ();
    }
 handle_postfix_attrs:
  ఒకవేళ (specs->type != ఖాళీ)
    {
      specs->postfix_attrs
	= c_warn_type_లక్షణాలు (specs->type, specs->postfix_attrs);
      decl_లక్షణాలు (&specs->type, specs->postfix_attrs, 0);
      specs->postfix_attrs = NULL_వృక్షం;
    }

  తిరిగి specs;
}

/* Perform final processing on one file scope's declarations (or the
   external scope's declarations), GLOBALS.  */

స్థిర శూన్య
c_write_global_declarations_1 (వృక్షం globals)
{
  వృక్షం decl;
  తార్కిక reconsider;

  /* Process the decls in the order they were written.  */
  కొరకు (decl = globals; decl; decl = DECL_CHAIN (decl))
    {
      /* Check for used but undefined static functions using the C
	 standard's definition of "used", and set TREE_NO_WARNING so
	 that check_global_declaration doesn't repeat the check.  */
      ఒకవేళ (వృక్షం_సంకేతం (decl) == FUNCTION_DECL
	  && DECL_INITIAL (decl) == NULL_వృక్షం
	  && DECL_EXTERNAL (decl)
	  && !వృక్షం_ప్రజా (decl)
	  && !warning_suppressed_p (decl, OPT_Wunused))
	{
	  ఒకవేళ (C_DECL_వాడిన (decl))
	    {
	      ఒకవేళ (pedwarn (ఆదానం_location, 0, "%q+F used but never defined",
			   decl))
		suppress_warning (decl, OPT_Wunused);
	    }
	  /* For -Wunused-function warn about unused static prototypes.  */
	  లేకపోతే ఒకవేళ (warn_వాడని_function
		   && ! DECL_ARTIFICIAL (decl)
		   && warning (OPT_Wunused_function,
			       "%q+F declared %<static%> but never defined",
			       decl))
	    suppress_warning (decl, OPT_Wunused);
	}

      wrapup_global_declaration_1 (decl);
    }

  చేయి
    {
      reconsider = అబద్ధం;
      కొరకు (decl = globals; decl; decl = DECL_CHAIN (decl))
	reconsider |= wrapup_global_declaration_2 (decl);
    }
  అయితే (reconsider);
}

/* Preserve the external declarations scope across a garbage collect.  */
స్థిర GTY(()) వృక్షం ext_ఖండం;

/* Collect all references relevant to SOURCE_FILE.  */

స్థిర శూన్య
collect_all_refs (స్థిరరాశి అక్షరం *ఆధారం_file)
{
  వృక్షం t;
  గుర్తులేని i;

  FOR_EACH_VEC_ELT (*all_translation_units, i, t)
    collect_ada_nodes (ఖండం_VARS (DECL_INITIAL (t)), ఆధారం_file);

  collect_ada_nodes (ఖండం_VARS (ext_ఖండం), ఆధారం_file);
}

/* Collect source file references at global level.  */

స్థిర శూన్య
collect_ఆధారం_refs (శూన్య)
{
  వృక్షం t;
  వృక్షం decls;
  వృక్షం decl;
  గుర్తులేని i;

  FOR_EACH_VEC_ELT (*all_translation_units, i, t)
    {
      decls = DECL_INITIAL (t);
      కొరకు (decl = ఖండం_VARS (decls); decl; decl = వృక్షం_CHAIN (decl))
	ఒకవేళ (!DECL_IS_UNDECLARED_BUILTIN (decl))
	  collect_ఆధారం_ref (DECL_ఆధారం_FILE (decl));
    }

  కొరకు (decl = ఖండం_VARS (ext_ఖండం); decl; decl = వృక్షం_CHAIN (decl))
    ఒకవేళ (!DECL_IS_UNDECLARED_BUILTIN (decl))
      collect_ఆధారం_ref (DECL_ఆధారం_FILE (decl));
}

/* Free attribute access data that are not needed by the middle end. */

స్థిర శూన్య
free_attr_access_దత్తాంశం ()
{
  నిర్మాణం cgraph_కణుపు *n;

  /* Iterate over all functions declared in the translation unit.  */
  FOR_EACH_FUNCTION (n)
    {
      కొరకు (వృక్షం parm = DECL_ARGUMENTS (n->decl); parm; parm = వృక్షం_CHAIN (parm))
	ఒకవేళ (వృక్షం attrs = DECL_లక్షణాలు (parm))
	  attr_access::free_lang_దత్తాంశం (attrs);

      వృక్షం fntype = వృక్షం_TYPE (n->decl);
      ఒకవేళ (!fntype || fntype == error_mark_కణుపు)
	కొనసాగు;
      వృక్షం attrs = TYPE_లక్షణాలు (fntype);
      ఒకవేళ (!attrs)
	కొనసాగు;

      attr_access::free_lang_దత్తాంశం (attrs);
    }
}

/* Perform any final parser cleanups and generate initial debugging
   information.  */

శూన్య
c_parse_final_cleanups (శూన్య)
{
  వృక్షం t;
  గుర్తులేని i;

  /* We don't want to do this if generating a PCH.  */
  ఒకవేళ (pch_file)
    తిరిగి;

  timevar_stop (TV_PHASE_PARSING);
  timevar_ప్రారంభం (TV_PHASE_DEFERRED);

  /* Do the Objective-C stuff.  This is where all the Objective-C
     module stuff gets generated (symtab, class/protocol/selector
     lists etc).  */
  ఒకవేళ (c_dialect_objc ())
    objc_write_global_declarations ();

  /* Close the external scope.  */
  ext_ఖండం = తీయి_scope ();
  external_scope = 0;
  gcc_assert (!current_scope);

  /* Handle -fdump-ada-spec[-slim]. */
  ఒకవేళ (flag_dump_ada_spec || flag_dump_ada_spec_slim)
    {
      /* Build a table of files to generate specs for */
      collect_ఆధారం_ref (main_ఆదానం_filename);
      ఒకవేళ (!flag_dump_ada_spec_slim)
	collect_ఆధారం_refs ();

      dump_ada_specs (collect_all_refs, ఖాళీ);
    }

  /* Process all file scopes in this compilation, and the external_scope,
     through wrapup_global_declarations.  */
  FOR_EACH_VEC_ELT (*all_translation_units, i, t)
    c_write_global_declarations_1 (ఖండం_VARS (DECL_INITIAL (t)));
  c_write_global_declarations_1 (ఖండం_VARS (ext_ఖండం));

  /* Call this to set cpp_implicit_aliases_done on all nodes.  This is
     important for function multiversioning aliases to get resolved.  */
  symtab->process_same_body_aliases ();

  ఒకవేళ (!లోపల_lto_p)
    free_attr_access_దత్తాంశం ();

  timevar_stop (TV_PHASE_DEFERRED);
  timevar_ప్రారంభం (TV_PHASE_PARSING);

  ext_ఖండం = ఖాళీ;
}

/* Register reserved keyword WORD as qualifier for address space AS.  */

శూన్య
c_రిజిస్టరు_addr_space (స్థిరరాశి అక్షరం *మాట, addr_space_t as)
{
  పూర్ణాంకం rid = RID_మొదటి_ADDR_SPACE + as;
  వృక్షం id;

  /* Address space qualifiers are only supported
     in C with GNU extensions enabled.  */
  ఒకవేళ (c_dialect_objc () || flag_no_asm)
    తిరిగి;

  id = get_identifier (మాట);
  C_సమితి_RID_సంకేతం (id, rid);
  C_IS_RESERVED_మాట (id) = 1;
  ridpointers [rid] = id;
}

/* Return identifier to look up for omp declare reduction.  */

వృక్షం
c_omp_reduction_id (గణన వృక్షం_సంకేతం_2 reduction_సంకేతం, వృక్షం reduction_id)
{
  స్థిరరాశి అక్షరం *p = ఖాళీ;
  ఎంపిక (reduction_సంకేతం)
    {
    స్థితి PLUS_సమాసం: p = "+"; ఆపు;
    స్థితి MULT_సమాసం: p = "*"; ఆపు;
    స్థితి MINUS_సమాసం: p = "-"; ఆపు;
    స్థితి బిట్టు_AND_సమాసం: p = "&"; ఆపు;
    స్థితి బిట్టు_XOR_సమాసం: p = "^"; ఆపు;
    స్థితి బిట్టు_IOR_సమాసం: p = "|"; ఆపు;
    స్థితి TRUTH_ANDIF_సమాసం: p = "&&"; ఆపు;
    స్థితి TRUTH_ORIF_సమాసం: p = "||"; ఆపు;
    స్థితి MIN_సమాసం: p = "min"; ఆపు;
    స్థితి MAX_సమాసం: p = "max"; ఆపు;
    అప్రమేయ:
      ఆపు;
    }

  ఒకవేళ (p == ఖాళీ)
    {
      ఒకవేళ (వృక్షం_సంకేతం (reduction_id) != IDENTIFIER_కణుపు)
	తిరిగి error_mark_కణుపు;
      p = IDENTIFIER_సూచిక (reduction_id);
    }

  స్థిరరాశి అక్షరం ఉపసర్గ[] = "omp declare reduction ";
  కొలత_t lenp = పరిమాణం (ఉపసర్గ);
  కొలత_t len = అక్షరశ్రేణి_పొడవు (p);
  అక్షరం *name = XALLOCAVEC (అక్షరం, lenp + len);
  జ్ఞాపకం_నకలు (name, ఉపసర్గ, lenp - 1);
  జ్ఞాపకం_నకలు (name + lenp - 1, p, len + 1);
  తిరిగి get_identifier (name);
}

/* Lookup REDUCTION_ID in the current scope, or create an artificial
   VAR_DECL, bind it into the current scope and return it.  */

వృక్షం
c_omp_reduction_decl (వృక్షం reduction_id)
{
  నిర్మాణం c_binding *b = I_చిహ్నం_BINDING (reduction_id);
  ఒకవేళ (b != ఖాళీ && B_లోపల_CURRENT_SCOPE (b))
    తిరిగి b->decl;

  వృక్షం decl = build_decl (BUILTINS_LOCATION, VAR_DECL,
			  reduction_id, integer_type_కణుపు);
  DECL_ARTIFICIAL (decl) = 1;
  DECL_EXTERNAL (decl) = 1;
  వృక్షం_STATIC (decl) = 1;
  వృక్షం_ప్రజా (decl) = 0;
  bind (reduction_id, decl, current_scope, నిజం, అబద్ధం, BUILTINS_LOCATION);
  తిరిగి decl;
}

/* Lookup REDUCTION_ID in the first scope where it has entry for TYPE.  */

వృక్షం
c_omp_reduction_lookup (వృక్షం reduction_id, వృక్షం type)
{
  నిర్మాణం c_binding *b = I_చిహ్నం_BINDING (reduction_id);
  అయితే (b)
    {
      వృక్షం t;
      కొరకు (t = DECL_INITIAL (b->decl); t; t = వృక్షం_CHAIN (t))
	ఒకవేళ (comptypes (వృక్షం_PURPOSE (t), type))
	  తిరిగి వృక్షం_విలువ (t);
      b = b->shadowed;
    }
  తిరిగి error_mark_కణుపు;
}

/* Helper function called via walk_tree, to diagnose invalid
   #pragma omp declare reduction combiners or initializers.  */

వృక్షం
c_check_omp_declare_reduction_r (వృక్షం *tp, పూర్ణాంకం *, శూన్య *దత్తాంశం)
{
  వృక్షం *vars = (వృక్షం *) దత్తాంశం;
  ఒకవేళ (SSA_VAR_P (*tp)
      && !DECL_ARTIFICIAL (*tp)
      && *tp != vars[0]
      && *tp != vars[1])
    {
      location_t loc = DECL_ఆధారం_LOCATION (vars[0]);
      ఒకవేళ (strcmp (IDENTIFIER_సూచిక (DECL_NAME (vars[0])), "omp_out") == 0)
	error_at (loc, "%<#pragma omp declare reduction%> combiner refers to "
		       "variable %qD which is not %<omp_out%> nor %<omp_in%>",
		  *tp);
      లేకపోతే
	error_at (loc, "%<#pragma omp declare reduction%> initializer refers "
		       "to variable %qD which is not %<omp_priv%> nor "
		       "%<omp_orig%>",
		  *tp);
      తిరిగి *tp;
    }
  తిరిగి NULL_వృక్షం;
}

/* Return identifier to look up for omp declare mapper.  */

వృక్షం
c_omp_mapper_id (వృక్షం mapper_id)
{
  స్థిరరాశి అక్షరం *p = ఖాళీ;

  స్థిరరాశి అక్షరం ఉపసర్గ[] = "omp declare mapper ";

  ఒకవేళ (mapper_id == NULL_వృక్షం)
    p = "<default>";
  లేకపోతే ఒకవేళ (వృక్షం_సంకేతం (mapper_id) == IDENTIFIER_కణుపు)
    p = IDENTIFIER_సూచిక (mapper_id);
  లేకపోతే
    తిరిగి error_mark_కణుపు;

  కొలత_t lenp = పరిమాణం (ఉపసర్గ);
  కొలత_t len = అక్షరశ్రేణి_పొడవు (p);
  అక్షరం *name = XALLOCAVEC (అక్షరం, lenp + len);
  జ్ఞాపకం_నకలు (name, ఉపసర్గ, lenp - 1);
  జ్ఞాపకం_నకలు (name + lenp - 1, p, len + 1);
  తిరిగి get_identifier (name);
}

/* Lookup MAPPER_ID in the current scope, or create an artificial
   VAR_DECL, bind it into the current scope and return it.  */

వృక్షం
c_omp_mapper_decl (వృక్షం mapper_id)
{
  నిర్మాణం c_binding *b = I_చిహ్నం_BINDING (mapper_id);
  ఒకవేళ (b != ఖాళీ && B_లోపల_CURRENT_SCOPE (b))
    తిరిగి b->decl;

  వృక్షం decl = build_decl (BUILTINS_LOCATION, VAR_DECL,
			  mapper_id, integer_type_కణుపు);
  DECL_ARTIFICIAL (decl) = 1;
  DECL_EXTERNAL (decl) = 1;
  వృక్షం_STATIC (decl) = 1;
  వృక్షం_ప్రజా (decl) = 0;
  bind (mapper_id, decl, current_scope, నిజం, అబద్ధం, BUILTINS_LOCATION);
  తిరిగి decl;
}

/* Lookup MAPPER_ID in the first scope where it has entry for TYPE.  */

వృక్షం
c_omp_mapper_lookup (వృక్షం mapper_id, వృక్షం type)
{
  ఒకవేళ (!రికార్డు_OR_UNION_TYPE_P (type))
    తిరిగి NULL_వృక్షం;

  mapper_id = c_omp_mapper_id (mapper_id);

  నిర్మాణం c_binding *b = I_చిహ్నం_BINDING (mapper_id);
  అయితే (b)
    {
      వృక్షం t;
      కొరకు (t = DECL_INITIAL (b->decl); t; t = వృక్షం_CHAIN (t))
	ఒకవేళ (comptypes (వృక్షం_PURPOSE (t), type))
	  తిరిగి వృక్షం_విలువ (t);
      b = b->shadowed;
    }
  తిరిగి NULL_వృక్షం;
}

/* For C, we record a pointer to the mapper itself without wrapping it in an
   artificial function or similar.  So, just return it.  */

వృక్షం
c_omp_వెలికితీయి_mapper_directive (వృక్షం mapper)
{
  తిరిగి mapper;
}

/* For now we can handle singleton OMP_ARRAY_SECTIONs with custom mappers, but
   nothing more complicated.  */

వృక్షం
c_omp_map_array_section (location_t loc, వృక్షం t)
{
  వృక్షం దిగువ = వృక్షం_నిర్వాహ్యం (t, 1);
  వృక్షం len = వృక్షం_నిర్వాహ్యం (t, 2);

  ఒకవేళ (len && integer_onep (len))
    {
      t = వృక్షం_నిర్వాహ్యం (t, 0);

      ఒకవేళ (!దిగువ)
	దిగువ = integer_zero_కణుపు;

      t = build_array_ref (loc, t, దిగువ);
    }

  తిరిగి t;
}

/* Helper function for below function.  */

స్థిర వృక్షం
c_omp_పరిశీలన_mapper_bindings_r (వృక్షం *tp, పూర్ణాంకం *walk_subtrees, శూన్య *ptr)
{
  వృక్షం t = *tp;
  omp_mapper_list<వృక్షం> *mlist = (omp_mapper_list<వృక్షం> *) ptr;
  వృక్షం aggr_type = NULL_వృక్షం;

  ఒకవేళ (వృక్షం_సంకేతం (t) == SIZEOF_సమాసం
      || వృక్షం_సంకేతం (t) == ALIGNOF_సమాసం)
    {
      *walk_subtrees = 0;
      తిరిగి NULL_వృక్షం;
    }

  ఒకవేళ (వృక్షం_సంకేతం (t) == OMP_CLAUSE)
    తిరిగి NULL_వృక్షం;

  ఒకవేళ (వృక్షం_సంకేతం (t) == COMPONENT_REF
      && రికార్డు_OR_UNION_TYPE_P (వృక్షం_TYPE (వృక్షం_నిర్వాహ్యం (t, 0))))
    aggr_type = వృక్షం_TYPE (వృక్షం_నిర్వాహ్యం (t, 0));
  లేకపోతే ఒకవేళ ((వృక్షం_సంకేతం (t) == VAR_DECL
	    || వృక్షం_సంకేతం (t) == PARM_DECL
	    || వృక్షం_సంకేతం (t) == ఫలితం_DECL)
	   && రికార్డు_OR_UNION_TYPE_P (వృక్షం_TYPE (t)))
    aggr_type = వృక్షం_TYPE (t);

  ఒకవేళ (aggr_type)
    {
      వృక్షం mapper_fn = c_omp_mapper_lookup (NULL_వృక్షం, aggr_type);
      ఒకవేళ (mapper_fn)
	mlist->కూడు_mapper (NULL_వృక్షం, aggr_type, mapper_fn);
    }

  తిరిగి NULL_వృక్షం;
}

/* Scan an offload region's body, and record uses of struct- or union-typed
   variables.  Add _mapper_binding_ fake clauses to *CLAUSES_PTR.  */

శూన్య
c_omp_పరిశీలన_mapper_bindings (location_t loc, వృక్షం *clauses_ptr, వృక్షం body)
{
  hash_సమితి<omp_name_type<వృక్షం>> చూసిన_types;
  auto_vec<వృక్షం> mappers;
  omp_mapper_list<వృక్షం> mlist (&చూసిన_types, &mappers);

  walk_వృక్షం_without_duplicates (&body, c_omp_పరిశీలన_mapper_bindings_r, &mlist);

  గుర్తులేని పూర్ణాంకం i;
  వృక్షం mapper;
  FOR_EACH_VEC_ELT (mappers, i, mapper)
    c_omp_కనుగొను_nested_mappers (&mlist, mapper);

  FOR_EACH_VEC_ELT (mappers, i, mapper)
    {
      ఒకవేళ (mapper == error_mark_కణుపు)
	కొనసాగు;
      వృక్షం mapper_name = OMP_DECLARE_MAPPER_ID (mapper);
      వృక్షం decl = OMP_DECLARE_MAPPER_DECL (mapper);

      వృక్షం c = build_omp_clause (loc, OMP_CLAUSE__MAPPER_BINDING_);
      OMP_CLAUSE__MAPPER_BINDING__ID (c) = mapper_name;
      OMP_CLAUSE__MAPPER_BINDING__DECL (c) = decl;
      OMP_CLAUSE__MAPPER_BINDING__MAPPER (c) = mapper;

      OMP_CLAUSE_CHAIN (c) = *clauses_ptr;
      *clauses_ptr = c;
    }
}

తార్కిక
c_check_లోపల_current_scope (వృక్షం decl)
{
  నిర్మాణం c_binding *b = I_చిహ్నం_BINDING (DECL_NAME (decl));
  తిరిగి b != ఖాళీ && B_లోపల_CURRENT_SCOPE (b);
}

/* Search for loop or switch names.  BEFORE_LABELS is last statement before
   possible labels and SWITCH_P true for a switch, false for loops.
   Searches through last statements in cur_stmt_list, stops when seeing
   BEFORE_LABELs, or statement other than LABEL_EXPR or CASE_LABEL_EXPR.
   Returns number of loop/switch names found and if any are found, sets
   *LAST_P to the canonical loop/switch name LABEL_DECL.  */

పూర్ణాంకం
c_get_loop_పేర్లు (వృక్షం before_labels, తార్కిక switch_p, వృక్షం *చివరి_p)
{
  *చివరి_p = NULL_వృక్షం;
  ఒకవేళ (!building_stmt_list_p ()
      || !STATEMENT_LIST_HAS_LABEL (cur_stmt_list)
      || before_labels == void_list_కణుపు)
    తిరిగి 0;

  పూర్ణాంకం ret = 0;
  వృక్షం చివరి = NULL_వృక్షం;
  కొరకు (వృక్షం_stmt_iterator tsi = tsi_చివరి (cur_stmt_list);
       !tsi_చివర_p (tsi); tsi_prev (&tsi))
    {
      వృక్షం stmt = tsi_stmt (tsi);
      ఒకవేళ (stmt == before_labels)
	ఆపు;
      లేకపోతే ఒకవేళ (వృక్షం_సంకేతం (stmt) == LABEL_సమాసం)
	{
	  ఒకవేళ (చివరి == NULL_వృక్షం)
	    చివరి = LABEL_సమాసం_LABEL (stmt);
	  లేకపోతే
	    {
	      loop_పేర్లు.సురక్షిత_నెట్టు (LABEL_సమాసం_LABEL (stmt));
	      ++ret;
	    }
	}
      లేకపోతే ఒకవేళ (వృక్షం_సంకేతం (stmt) != CASE_LABEL_సమాసం
	       && వృక్షం_సంకేతం (stmt) != DEBUG_BEGIN_STMT)
	ఆపు;
    }
  ఒకవేళ (చివరి)
    {
      ఒకవేళ (switch_p)
	C_DECL_SWITCH_NAME (చివరి) = 1;
      లేకపోతే
	C_DECL_LOOP_NAME (చివరి) = 1;
      loop_పేర్లు.సురక్షిత_నెట్టు (చివరి);
      ++ret;
      ఒకవేళ (loop_పేర్లు.నిడివి () > 16)
	{
	  గుర్తులేని పూర్ణాంకం మొదటి = 0, i;
	  వృక్షం l, c = NULL_వృక్షం;
	  ఒకవేళ (loop_పేర్లు_hash == ఖాళీ)
	    loop_పేర్లు_hash = కొత్త decl_వృక్షం_map (ret);
	  లేకపోతే
	    మొదటి = loop_పేర్లు.నిడివి () - ret;
	  FOR_EACH_VEC_ELT_తిరగేయి (loop_పేర్లు, i, l)
	    {
	      ఒకవేళ (C_DECL_LOOP_NAME (l) || C_DECL_SWITCH_NAME (l))
		c = l;
	      gcc_checking_assert (c);
	      loop_పేర్లు_hash->put (l, c);
	      ఒకవేళ (i == మొదటి)
		ఆపు;
	    }
	}
      *చివరి_p = చివరి;
    }
  తిరిగి ret;
}

/* Undoes what get_loop_names did when it returned NUM_NAMES.  */

శూన్య
c_release_loop_పేర్లు (పూర్ణాంకం అంకె_పేర్లు)
{
  గుర్తులేని len = loop_పేర్లు.నిడివి () - అంకె_పేర్లు;
  ఒకవేళ (loop_పేర్లు_hash)
    {
      ఒకవేళ (len <= 16)
	{
	  తొలగించు loop_పేర్లు_hash;
	  loop_పేర్లు_hash = ఖాళీ;
	}
      లేకపోతే
	{
	  గుర్తులేని పూర్ణాంకం i;
	  వృక్షం l;
	  FOR_EACH_VEC_ELT_తిరగేయి (loop_పేర్లు, i, l)
	    {
	      loop_పేర్లు_hash->remove (l);
	      ఒకవేళ (i == len)
		ఆపు;
	    }
	}
    }
  loop_పేర్లు.truncate (len);
}

/* Finish processing of break or continue identifier operand.
   NAME is the identifier operand of break or continue and
   IS_BREAK is true iff it is break stmt.  Returns the operand
   to use for BREAK_STMT or CONTINUE_STMT, either NULL_TREE or
   canonical loop/switch name LABEL_DECL.  */

వృక్షం
c_ముగింపు_bc_name (location_t loc, వృక్షం name, తార్కిక is_break)
{
  వృక్షం label = NULL_వృక్షం, lab;
  pedwarn_c23 (loc, OPT_Wpedantic,
	       "ISO C does not support %qs statement with an identifier "
	       "operand before C2Y", is_break ? "break" : "continue");

  /* If I_LABEL_DECL is NULL or not from current function, don't waste time
     trying to find it among loop_names, it can't be there.  */
  ఒకవేళ (!loop_పేర్లు.is_ఖాళీలు ()
      && current_function_scope
      && (lab = I_LABEL_DECL (name))
      && DECL_CONTEXT (lab) == current_function_decl)
    {
      గుర్తులేని పూర్ణాంకం i;
      వృక్షం l, c = NULL_వృక్షం;
      ఒకవేళ (loop_పేర్లు_hash)
	{
	  ఒకవేళ (వృక్షం *val = loop_పేర్లు_hash->get (lab))
	    label = *val;
	}
      లేకపోతే
	FOR_EACH_VEC_ELT_తిరగేయి (loop_పేర్లు, i, l)
	  {
	    ఒకవేళ (C_DECL_LOOP_NAME (l) || C_DECL_SWITCH_NAME (l))
	      c = l;
	    gcc_checking_assert (c);
	    ఒకవేళ (l == lab)
	      {
		label = c;
		ఆపు;
	      }
	  }
      ఒకవేళ (label)
	వృక్షం_వాడిన (lab) = 1;
    }
  ఒకవేళ (label == NULL_వృక్షం)
    {
      auto_vec<స్థిరరాశి అక్షరం *> candidates;
      గుర్తులేని పూర్ణాంకం i;
      వృక్షం l, c = NULL_వృక్షం;
      FOR_EACH_VEC_ELT_తిరగేయి (loop_పేర్లు, i, l)
	{
	  ఒకవేళ (C_DECL_LOOP_NAME (l) || C_DECL_SWITCH_NAME (l))
	    c = l;
	  gcc_checking_assert (c);
	  ఒకవేళ (is_break || C_DECL_LOOP_NAME (c))
	    candidates.సురక్షిత_నెట్టు (IDENTIFIER_సూచిక (DECL_NAME (l)));
	}
      స్థిరరాశి అక్షరం *hint = కనుగొను_closest_string (IDENTIFIER_సూచిక (name),
					      &candidates);
      ఒకవేళ (hint)
	{
	  gcc_rich_location richloc (loc);
	  richloc.కూడు_fixit_replace (hint);
	  ఒకవేళ (is_break)
	    error_at (&richloc, "%<break%> statement operand %qE does not "
				"refer to a named loop or %<switch%>; "
				"did you mean %qs?", name, hint);
	  లేకపోతే
	    error_at (&richloc, "%<continue%> statement operand %qE does not "
				"refer to a named loop; did you mean %qs?",
		      name, hint);
	}
      లేకపోతే ఒకవేళ (is_break)
	error_at (loc, "%<break%> statement operand %qE does not refer to a "
		       "named loop or %<switch%>", name);
      లేకపోతే
	error_at (loc, "%<continue%> statement operand %qE does not refer to "
		       "a named loop", name);
    }
  లేకపోతే ఒకవేళ (!C_DECL_LOOP_NAME (label) && !is_break)
    {
      auto_diagnostic_సమూహం d;
      error_at (loc, "%<continue%> statement operand %qE refers to a named "
		     "%<switch%>", name);
      inform (DECL_ఆధారం_LOCATION (label), "%<switch%> name defined here");
      label = NULL_వృక్షం;
    }
  లేకపోతే ఒకవేళ (!C_DECL_LOOP_SWITCH_NAME_VALID (label))
    {
      auto_diagnostic_సమూహం d;
      ఒకవేళ (C_DECL_LOOP_NAME (label))
	{
	  error_at (loc, "%qs statement operand %qE refers to a loop outside "
			 "of its body", is_break ? "break" : "continue", name);
	  inform (DECL_ఆధారం_LOCATION (label), "loop name defined here");
	}
      లేకపోతే
	{
	  error_at (loc, "%<break%> statement operand %qE refers to a "
			 "%<switch%> outside of its body", name);
	  inform (DECL_ఆధారం_LOCATION (label),
		  "%<switch%> name defined here");
	}
      label = NULL_వృక్షం;
    }
  లేకపోతే ఒకవేళ (label == loop_పేర్లు.చివరి () && (లోపల_statement & లోపల_NAMED_STMT) != 0)
    /* If it is just a fancy reference to the innermost construct, handle it
       just like break; or continue; though tracking cheaply what is the
       innermost loop for continue when nested in switches would require
       another global variable and updating it.  */
    label = NULL_వృక్షం;
  లేకపోతే
    C_DECL_LOOP_SWITCH_NAME_వాడిన (label) = 1;
  తిరిగి label;
}

#అన్తర్భావ "gt-c-c-decl.h"
