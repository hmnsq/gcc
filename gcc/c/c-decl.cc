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

#अन्तर्भाव "config.h"
#define INCLUDE_STRING
#अन्तर्भाव "system.h"
#अन्तर्भाव "coretypes.h"
#अन्तर्भाव "target.h"
#अन्तर्भाव "function.h"
#अन्तर्भाव "c-tree.h"
#अन्तर्भाव "timevar.h"
#अन्तर्भाव "stringpool.h"
#अन्तर्भाव "cgraph.h"
#अन्तर्भाव "intl.h"
#अन्तर्भाव "print-tree.h"
#अन्तर्भाव "stor-layout.h"
#अन्तर्भाव "varasm.h"
#अन्तर्भाव "attribs.h"
#अन्तर्भाव "toplev.h"
#अन्तर्भाव "debug.h"
#अन्तर्भाव "c-family/c-objc.h"
#अन्तर्भाव "c-family/c-pragma.h"
#अन्तर्भाव "c-family/c-ubsan.h"
#अन्तर्भाव "c-lang.h"
#अन्तर्भाव "langhooks.h"
#अन्तर्भाव "tree-iterator.h"
#अन्तर्भाव "dumpfile.h"
#अन्तर्भाव "plugin.h"
#अन्तर्भाव "c-family/c-ada-spec.h"
#अन्तर्भाव "builtins.h"
#अन्तर्भाव "spellcheck-tree.h"
#अन्तर्भाव "gcc-rich-location.h"
#अन्तर्भाव "asan.h"
#अन्तर्भाव "c-family/name-hint.h"
#अन्तर्भाव "c-family/known-headers.h"
#अन्तर्भाव "c-family/c-spellcheck.h"
#अन्तर्भाव "context.h"  /* For 'g'.  */
#अन्तर्भाव "omp-general.h"
#अन्तर्भाव "omp-offload.h"  /* For offload_vars.  */
#अन्तर्भाव "c-parser.h"
#अन्तर्भाव "gcc-urlifier.h"

#अन्तर्भाव "tree-pretty-print.h"

/* In grokdeclarator, distinguish syntactic contexts of declarators.  */
गणना decl_context
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

गणना deprecated_states {
  DEPRECATED_NORMAL,
  DEPRECATED_SUPPRESS,
  UNAVAILABLE_DEPRECATED_SUPPRESS
};


/* Nonzero if we have seen an invalid cross reference
   to a struct, union, or enum, but not yet printed the message.  */
वृक्षः pending_invalid_xref;

/* File and line to appear in the eventual error message.  */
location_t pending_invalid_xref_location;

/* The file and line that the prototype came from if this is an
   old-style definition; used for diagnostics in
   store_parm_decls_oldstyle.  */

स्थिर location_t current_function_prototype_locus;

/* Whether this prototype was built-in.  */

स्थिर तार्किक current_function_prototype_built_in;

/* The argument type information of this prototype.  */

स्थिर वृक्षः current_function_prototype_arg_types;

/* The argument information structure for the function currently being
   defined.  */

स्थिर संरचना c_arg_info *current_function_arg_info;

/* The obstack on which parser and related data structures, which are
   not live beyond their top-level declaration or definition, are
   allocated.  */
संरचना obstack parser_obstack;

/* The current statement tree.  */

स्थिर GTY(()) संरचना stmt_वृक्षः_s c_stmt_वृक्षः;

/* Zero if we are not in an iteration or switch statement, otherwise
   a bitmask.  See bitmask definitions in c-tree.h.  */
unsigned वर्ण in_statement;

/* A list of decls to be made automatically visible in each file scope.  */
स्थिर GTY(()) वृक्षः visible_builtins;

/* Set to 0 at beginning of a function definition, set to 1 if
   a return statement that specifies a return value is seen.  */

पूर्णाङ्क current_function_returns_मानम्;

/* Set to 0 at beginning of a function definition, set to 1 if
   a return statement with no argument is seen.  */

पूर्णाङ्क current_function_returns_null;

/* Set to 0 at beginning of a function definition, set to 1 if
   a call to a noreturn function is seen.  */

पूर्णाङ्क current_function_returns_abnormally;

/* Set to nonzero by `grokdeclarator' for a function
   whose return type is defaulted, if warnings for this are desired.  */

स्थिर पूर्णाङ्क warn_about_return_type;

/* Nonzero when the current toplevel function contains a declaration
   of a nested function which is never defined.  */

स्थिर तार्किक undef_nested_function;

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
स्थिर vec<वृक्षः> loop_names;

/* Hash table mapping LABEL_DECLs to the canonical LABEL_DECLs if LOOP_NAMES
   vector becomes too long.  */
स्थिर decl_वृक्षः_map *loop_names_hash;

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

संरचना GTY((chain_next ("%h.prev"))) c_binding {
  सङ्घ GTY(()) {		/* first so GTY desc can use decl */
    वृक्षः GTY((tag ("0"))) type; /* the type in this scope */
    संरचना c_label_vars * GTY((tag ("1"))) label; /* for warnings */
  } GTY((desc ("TREE_CODE (%0.decl) == LABEL_DECL"))) u;
  वृक्षः decl;			/* the decl bound */
  वृक्षः id;			/* the identifier it's bound to */
  संरचना c_binding *prev;	/* the previous decl in this scope */
  संरचना c_binding *shadowed;	/* the innermost decl shadowed by this one */
  unsigned पूर्णाङ्क depth : 28;      /* depth of this scope */
  तार्किक invisible : 1;  /* normal lookup should ignore this binding */
  तार्किक nested : 1;     /* do not set DECL_CONTEXT when popping */
  तार्किक inner_comp : 1; /* incomplete array completed in inner scope */
  तार्किक in_struct : 1;	/* currently defined as struct field */
  location_t locus;		/* location for nested bindings */
};
#define B_IN_SCOPE(b1, b2) ((b1)->depth == (b2)->depth)
#define B_IN_CURRENT_SCOPE(b) ((b)->depth == current_scope->depth)
#define B_IN_FILE_SCOPE(b) ((b)->depth == 1 /*file_scope->depth*/)
#define B_IN_EXTERNAL_SCOPE(b) ((b)->depth == 0 /*external_scope->depth*/)

/* Each C symbol points to three linked lists of c_binding structures.
   These describe the values of the identifier in the three different
   namespaces defined by the language.  */

संरचना GTY(()) lang_identifier {
  संरचना c_common_identifier common_id;
  संरचना c_binding *चिह्नम्_binding; /* vars, funcs, constants, typedefs */
  संरचना c_binding *tag_binding;    /* struct/union/enum tags */
  संरचना c_binding *label_binding;  /* labels */
};

/* Validate c-lang.cc's assumptions.  */
बाह्य वर्ण C_SIZEOF_STRUCT_LANG_IDENTIFIER_isnt_accurate
[(परिमाण(संरचना lang_identifier) == C_SIZEOF_STRUCT_LANG_IDENTIFIER) ? 1 : -1];

/* The binding oracle; see c-tree.h.  */
शून्य (*c_binding_oracle) (गणना c_oracle_request, वृक्षः identifier);

/* This flag is set on an identifier if we have previously asked the
   binding oracle for this identifier's symbol binding.  */
#define I_चिह्नम्_CHECKED(ग्रन्थिः) \
  (वृक्षः_LANG_FLAG_4 (IDENTIFIER_ग्रन्थिः_CHECK (ग्रन्थिः)))

स्थिर अन्तःस्थ संरचना c_binding* *
i_चिह्नम्_binding (वृक्षः ग्रन्थिः)
{
  संरचना lang_identifier *lid
    = (संरचना lang_identifier *) IDENTIFIER_ग्रन्थिः_CHECK (ग्रन्थिः);

  जइ (lid->चिह्नम्_binding == रिक्त
      && c_binding_oracle != रिक्त
      && !I_चिह्नम्_CHECKED (ग्रन्थिः))
    {
      /* Set the "checked" flag first, to avoid infinite recursion
	 when the binding oracle calls back into gcc.  */
      I_चिह्नम्_CHECKED (ग्रन्थिः) = 1;
      c_binding_oracle (C_ORACLE_चिह्नम्, ग्रन्थिः);
    }

  प्रत्यागम &lid->चिह्नम्_binding;
}

#define I_चिह्नम्_BINDING(ग्रन्थिः) (*i_चिह्नम्_binding (ग्रन्थिः))

#define I_चिह्नम्_DECL(ग्रन्थिः) \
 (I_चिह्नम्_BINDING(ग्रन्थिः) ? I_चिह्नम्_BINDING(ग्रन्थिः)->decl : 0)

/* This flag is set on an identifier if we have previously asked the
   binding oracle for this identifier's tag binding.  */
#define I_TAG_CHECKED(ग्रन्थिः) \
  (वृक्षः_LANG_FLAG_5 (IDENTIFIER_ग्रन्थिः_CHECK (ग्रन्थिः)))

स्थिर अन्तःस्थ संरचना c_binding **
i_tag_binding (वृक्षः ग्रन्थिः)
{
  संरचना lang_identifier *lid
    = (संरचना lang_identifier *) IDENTIFIER_ग्रन्थिः_CHECK (ग्रन्थिः);

  जइ (lid->tag_binding == रिक्त
      && c_binding_oracle != रिक्त
      && !I_TAG_CHECKED (ग्रन्थिः))
    {
      /* Set the "checked" flag first, to avoid infinite recursion
	 when the binding oracle calls back into gcc.  */
      I_TAG_CHECKED (ग्रन्थिः) = 1;
      c_binding_oracle (C_ORACLE_TAG, ग्रन्थिः);
    }

  प्रत्यागम &lid->tag_binding;
}

#define I_TAG_BINDING(ग्रन्थिः) (*i_tag_binding (ग्रन्थिः))

#define I_TAG_DECL(ग्रन्थिः) \
 (I_TAG_BINDING(ग्रन्थिः) ? I_TAG_BINDING(ग्रन्थिः)->decl : 0)

/* This flag is set on an identifier if we have previously asked the
   binding oracle for this identifier's label binding.  */
#define I_LABEL_CHECKED(ग्रन्थिः) \
  (वृक्षः_LANG_FLAG_6 (IDENTIFIER_ग्रन्थिः_CHECK (ग्रन्थिः)))

स्थिर अन्तःस्थ संरचना c_binding **
i_label_binding (वृक्षः ग्रन्थिः)
{
  संरचना lang_identifier *lid
    = (संरचना lang_identifier *) IDENTIFIER_ग्रन्थिः_CHECK (ग्रन्थिः);

  जइ (lid->label_binding == रिक्त
      && c_binding_oracle != रिक्त
      && !I_LABEL_CHECKED (ग्रन्थिः))
    {
      /* Set the "checked" flag first, to avoid infinite recursion
	 when the binding oracle calls back into gcc.  */
      I_LABEL_CHECKED (ग्रन्थिः) = 1;
      c_binding_oracle (C_ORACLE_LABEL, ग्रन्थिः);
    }

  प्रत्यागम &lid->label_binding;
}

#define I_LABEL_BINDING(ग्रन्थिः) (*i_label_binding (ग्रन्थिः))

#define I_LABEL_DECL(ग्रन्थिः) \
 (I_LABEL_BINDING(ग्रन्थिः) ? I_LABEL_BINDING(ग्रन्थिः)->decl : 0)

/* Used by C_TOKEN_VEC tree.  */
संरचना GTY (()) c_वृक्षः_token_vec {
  संरचना वृक्षः_base base;
  vec<c_token, va_gc> *tokens;
};

STATIC_ASSERT (परिमाण (c_वृक्षः_token_vec) == परिमाण (c_वृक्षः_token_vec_struct));
STATIC_ASSERT (offsetof (c_वृक्षः_token_vec, tokens)
	       == offsetof (c_वृक्षः_token_vec_struct, tokens));

/* The resulting tree type.  */

सङ्घ GTY((desc ("TREE_CODE (&%h.generic) == IDENTIFIER_NODE + 2 * (TREE_CODE (&%h.generic) == C_TOKEN_VEC)"),
       chain_next ("(union lang_tree_node *) c_tree_chain_next (&%h.generic)"))) lang_वृक्षः_ग्रन्थिः
 {
  सङ्घ वृक्ष_ग्रन्थिः GTY ((tag ("0"),
			desc ("tree_node_structure (&%h)")))
    generic;
  संरचना lang_identifier GTY ((tag ("1"))) identifier;
  संरचना c_वृक्षः_token_vec GTY ((tag ("2"))) c_token_vec;
};

/* Langhook for tree_size.  */
size_t
c_वृक्षः_size (गणना वृक्षः_code code)
{
  gcc_checking_assert (code >= अङ्कः_वृक्षः_CODES);
  विकल्प (code)
    {
    पक्ष C_TOKEN_VEC: प्रत्यागम परिमाण (c_वृक्षः_token_vec);
    स्वभाव:
      विकल्प (वृक्षः_CODE_CLASS (code))
	{
	पक्ष tcc_declaration: प्रत्यागम परिमाण (वृक्षः_decl_non_common);
	पक्ष tcc_type: प्रत्यागम परिमाण (वृक्षः_type_non_common);
	स्वभाव: gcc_unreachable ();
	}
    }
}

/* Track bindings and other things that matter for goto warnings.  For
   efficiency, we do not gather all the decls at the point of
   definition.  Instead, we point into the bindings structure.  As
   scopes are popped, we update these structures and gather the decls
   that matter at that time.  */

संरचना GTY(()) c_spot_bindings {
  /* The currently open scope which holds bindings defined when the
     label was defined or the goto statement was found.  */
  संरचना c_scope *scope;
  /* The bindings in the scope field which were defined at the point
     of the label or goto.  This lets us look at older or newer
     bindings in the scope, as appropriate.  */
  संरचना c_binding *bindings_in_scope;
  /* The number of statement expressions that have started since this
     label or goto statement was defined.  This is zero if we are at
     the same statement expression level.  It is positive if we are in
     a statement expression started since this spot.  It is negative
     if this spot was in a statement expression and we have left
     it.  */
  पूर्णाङ्क stmt_exprs;
  /* Whether we started in a statement expression but are no longer in
     it.  This is set to true if stmt_exprs ever goes negative.  */
  तार्किक वामः_stmt_व्यञ्जकम्;
};

/* This structure is used to keep track of bindings seen when a goto
   statement is defined.  This is only used if we see the goto
   statement before we see the label.  */

संरचना GTY(()) c_goto_bindings {
  /* The location of the goto statement.  */
  location_t loc;
  /* The bindings of the goto statement.  */
  संरचना c_spot_bindings goto_bindings;
};

प्रकारनिर्देश संरचना c_goto_bindings *c_goto_bindings_p;

/* The additional information we keep track of for a label binding.
   These fields are updated as scopes are popped.  */

संरचना GTY(()) c_label_vars {
  /* The shadowed c_label_vars, when one label shadows another (which
     can only happen using a __label__ declaration).  */
  संरचना c_label_vars *shadowed;
  /* The bindings when the label was defined.  */
  संरचना c_spot_bindings label_bindings;
  /* A list of decls that we care about: decls about which we should
     warn if a goto branches to this label from later in the function.
     Decls are added to this list as scopes are popped.  We only add
     the decls that matter.  */
  vec<वृक्षः, va_gc> *decls_in_scope;
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


संरचना GTY((chain_next ("%h.outer"))) c_scope {
  /* The scope containing this one.  */
  संरचना c_scope *outer;

  /* The next outermost function scope.  */
  संरचना c_scope *outer_function;

  /* All bindings in this scope.  */
  संरचना c_binding *bindings;

  /* For each scope (except the global one), a chain of BLOCK nodes
     for all the scopes that were entered and exited one level down.  */
  वृक्षः blocks;
  वृक्षः blocks_last;

  /* The depth of this scope.  Used to keep the ->shadowed chain of
     bindings sorted innermost to outermost.  */
  unsigned पूर्णाङ्क depth : 28;

  /* True if we are currently filling this scope with parameter
     declarations.  */
  तार्किक parm_flag : 1;

  /* True if we saw [*] in this scope.  Used to give an error messages
     if these appears in a function definition.  */
  तार्किक had_vla_unspec : 1;

  /* True if we parsed a list of forward parameter decls in this scope.  */
  तार्किक had_forward_parm_decls : 1;

  /* True if this is the outermost block scope of a function body.
     This scope contains the parameters, the local variables declared
     in the outermost block, and all the labels (except those in
     nested functions, or declared at block scope with __label__).  */
  तार्किक function_body : 1;

  /* True means make a BLOCK for this scope no matter what.  */
  तार्किक keep : 1;

  /* True means that an unsuffixed float constant is _Decimal64.  */
  तार्किक float_const_decimal64 : 1;

  /* True if this scope has any label bindings.  This is used to speed
     up searching for labels when popping scopes, particularly since
     labels are normally only found at function scope.  */
  तार्किक has_label_bindings : 1;

  /* True if we should issue a warning if a goto statement crosses any
     of the bindings.  We still need to check the list of bindings to
     find the specific ones we need to warn about.  This is true if
     decl_jump_unsafe would return true for any of the bindings.  This
     is used to avoid looping over all the bindings unnecessarily.  */
  तार्किक has_jump_unsafe_decl : 1;
};

/* The scope currently in effect.  */

स्थिर GTY(()) संरचना c_scope *current_scope;

/* The innermost function scope.  Ordinary (not explicitly declared)
   labels, bindings to error_mark_node, and the lazily-created
   bindings of __func__ and its friends get this scope.  */

स्थिर GTY(()) संरचना c_scope *current_function_scope;

/* The C file scope.  This is reset for each input translation unit.  */

स्थिर GTY(()) संरचना c_scope *file_scope;

/* The outermost scope.  This is used for all declarations with
   external linkage, and only these, hence the name.  */

स्थिर GTY(()) संरचना c_scope *external_scope;

/* A chain of c_scope structures awaiting reuse.  */

स्थिर GTY((deletable)) संरचना c_scope *scope_freelist;

/* A chain of c_binding structures awaiting reuse.  */

स्थिर GTY((deletable)) संरचना c_binding *binding_freelist;

/* Append VAR to LIST in scope SCOPE.  */
#define SCOPE_LIST_APPEND(scope, list, decl) करेहि {	\
  संरचना c_scope *s_ = (scope);				\
  वृक्षः d_ = (decl);					\
  जइ (s_->list##_last)					\
    BLOCK_CHAIN (s_->list##_last) = d_;			\
  अण्णहा							\
    s_->list = d_;					\
  s_->list##_last = d_;					\
} जाव (0)

/* Concatenate FROM in scope FSCOPE onto TO in scope TSCOPE.  */
#define SCOPE_LIST_CONCAT(tscope, to, fscope, from) करेहि {	\
  संरचना c_scope *t_ = (tscope);				\
  संरचना c_scope *f_ = (fscope);				\
  जइ (t_->to##_last)						\
    BLOCK_CHAIN (t_->to##_last) = f_->from;			\
  अण्णहा								\
    t_->to = f_->from;						\
  t_->to##_last = f_->from##_last;				\
} जाव (0)

/* A c_inline_static structure stores details of a static identifier
   referenced in a definition of a function that may be an inline
   definition if no subsequent declaration of that function uses
   "extern" or does not use "inline".  */

संरचना GTY((chain_next ("%h.next"))) c_inline_static {
  /* The location for a diagnostic.  */
  location_t location;

  /* The function that may be an inline definition.  */
  वृक्षः function;

  /* The object or function referenced.  */
  वृक्षः static_decl;

  /* What sort of reference this is.  */
  गणना c_inline_static_type type;

  /* The next such structure or NULL.  */
  संरचना c_inline_static *next;
};

/* List of static identifiers used or referenced in functions that may
   be inline definitions.  */
स्थिर GTY(()) संरचना c_inline_static *c_inline_statics;

/* True means unconditionally make a BLOCK for the next scope pushed.  */

स्थिर तार्किक keep_next_level_flag;

/* True means the next call to push_scope will be the outermost scope
   of a function body, so do not push a new scope, merely cease
   expecting parameter decls.  */

स्थिर तार्किक next_is_function_body;

/* A vector of pointers to c_binding structures.  */

प्रकारनिर्देश संरचना c_binding *c_binding_ptr;

/* Information that we keep for a struct or union while it is being
   parsed.  */

वर्ग c_struct_parse_info
{
सार्वजनिक:
  /* If warn_cxx_compat, a list of types defined within this
     struct.  */
  auto_vec<वृक्षः> struct_types;
  /* If warn_cxx_compat, a list of field names which have bindings,
     and which are defined in this struct, but which are not defined
     in any enclosing struct.  This is used to clear the in_struct
     field of the c_bindings structure.  */
  auto_vec<c_binding_ptr> fields;
  /* If warn_cxx_compat, a list of typedef names used when defining
     fields in this struct.  */
  auto_vec<वृक्षः> typedefs_seen;
  /* The location of a previous definition of this struct.  */
  location_t refloc;
};


/* Hash table for structs and unions.  */
संरचना c_struct_hasher : ggc_ptr_hash<वृक्ष_ग्रन्थिः>
{
  स्थिर hashval_t hash (वृक्षः t);
  स्थिर तार्किक equal (वृक्षः, वृक्षः);
};

/* Hash an RECORD OR UNION.  */
hashval_t
c_struct_hasher::hash (वृक्षः type)
{
  inchash::hash hstate;

  hstate.add_int (वृक्षः_CODE (type));
  वृक्षः tag = c_type_tag (type);
  hstate.add_object (tag);

  प्रत्यागम hstate.end ();
}

/* Compare two RECORD or UNION types.  */
तार्किक
c_struct_hasher::equal (वृक्षः t1,  वृक्षः t2)
{
  प्रत्यागम comptypes_equiv_p (t1, t2);
}

/* All tagged typed so that TYPE_CANONICAL can be set correctly.  */
स्थिर GTY (()) hash_table<c_struct_hasher> *c_struct_htab;

/* Information for the struct or union currently being parsed, or
   NULL if not parsing a struct or union.  */
स्थिर वर्ग c_struct_parse_info *struct_parse_info;

/* Forward declarations.  */
स्थिर वृक्षः lookup_name_in_scope (वृक्षः, संरचना c_scope *);
स्थिर वृक्षः c_make_fname_decl (location_t, वृक्षः, पूर्णाङ्क);
स्थिर वृक्षः grokdeclarator (ध्रुव संरचना c_declarator *,
			    संरचना c_declspecs *,
			    गणना decl_context, तार्किक, वृक्षः *, वृक्षः *, वृक्षः *,
			    तार्किक *, गणना deprecated_states);
स्थिर वृक्षः grokparms (संरचना c_arg_info *, तार्किक);
स्थिर शून्य layout_array_type (वृक्षः);
स्थिर ध्रुव वर्ण *header_for_builtin_fn (वृक्षः);

/* T is a statement.  Add it to the statement-tree.  This is the
   C/ObjC version--C++ has a slightly different version of this
   function.  */

वृक्षः
add_stmt (वृक्षः t)
{
  गणना वृक्षः_code code = वृक्षः_CODE (t);

  जइ (CAN_HAVE_LOCATION_P (t) && code != LABEL_व्यञ्जकम्)
    {
      जइ (!व्यञ्जकम्_HAS_LOCATION (t))
	SET_व्यञ्जकम्_LOCATION (t, निवेशः_location);
    }

  /* Add T to the statement-tree.  Non-side-effect statements need to be
     recorded during statement expressions.  */
  जइ (!building_stmt_list_p ())
    प्रक्षिप_stmt_list ();

  जइ (code == LABEL_व्यञ्जकम् || code == CASE_LABEL_व्यञ्जकम्)
    STATEMENT_LIST_HAS_LABEL (cur_stmt_list) = 1;

  append_to_statement_list_force (t, &cur_stmt_list);

  प्रत्यागम t;
}





/* Return true if we will want to say something if a goto statement
   crosses DECL.  */

स्थिर तार्किक
decl_jump_unsafe (वृक्षः decl)
{
  जइ (error_operand_p (decl))
    प्रत्यागम मिच्छ;

  /* Don't warn for compound literals.  If a goto statement crosses
     their initialization, it should cross also all the places where
     the complit is used or where the complit address might be saved
     into some variable, so code after the label to which goto jumps
     should not be able to refer to the compound literal.  */
  जइ (VAR_P (decl) && C_DECL_COMPOUND_LITERAL_P (decl))
    प्रत्यागम मिच्छ;

  जइ (flag_openmp
      && VAR_P (decl)
      && lookup_attribute ("omp allocate", DECL_ATTRIBUTES (decl)))
    प्रत्यागम सच्च;

  /* Always warn about crossing variably modified types.  */
  जइ ((VAR_P (decl) || वृक्षः_CODE (decl) == TYPE_DECL)
      && c_type_variably_modified_p (वृक्षः_TYPE (decl)))
    प्रत्यागम सच्च;

  /* Otherwise, only warn if -Wgoto-misses-init and this is an
     initialized automatic decl.  */
  जइ (warn_jump_misses_init
      && VAR_P (decl)
      && !वृक्षः_STATIC (decl)
      && DECL_INITIAL (decl) != NULL_वृक्षः)
    प्रत्यागम सच्च;

  प्रत्यागम मिच्छ;
}


शून्य
c_print_identifier (FILE *file, वृक्षः ग्रन्थिः, पूर्णाङ्क indent)
{
  शून्य (*save) (गणना c_oracle_request, वृक्षः identifier);

  /* Temporarily hide any binding oracle.  Without this, calls to
     debug_tree from the debugger will end up calling into the oracle,
     making for a confusing debug session.  As the oracle isn't needed
     here for normal operation, it's simplest to suppress it.  */
  save = c_binding_oracle;
  c_binding_oracle = रिक्त;

  print_ग्रन्थिः (file, "symbol", I_चिह्नम्_DECL (ग्रन्थिः), indent + 4);
  print_ग्रन्थिः (file, "tag", I_TAG_DECL (ग्रन्थिः), indent + 4);
  print_ग्रन्थिः (file, "label", I_LABEL_DECL (ग्रन्थिः), indent + 4);
  जइ (C_IS_RESERVED_WORD (ग्रन्थिः) && C_RID_CODE (ग्रन्थिः) != RID_CXX_COMPAT_WARN)
    {
      वृक्षः rid = ridpointers[C_RID_CODE (ग्रन्थिः)];
      indent_to (file, indent + 4);
      fprintf (file, "rid " HOST_PTR_PRINTF " \"%s\"",
	       (शून्य *) rid, IDENTIFIER_POINTER (rid));
    }

  c_binding_oracle = save;
}

/* Establish that the scope contains declarations that are sensitive to
   jumps that cross a binding.  Together with decl_jump_unsafe, this is
   used to diagnose such jumps.  */
शून्य
c_mark_decl_jump_unsafe_in_current_scope ()
{
  current_scope->has_jump_unsafe_decl = 1;
}

/* Establish a binding between NAME, an IDENTIFIER_NODE, and DECL,
   which may be any of several kinds of DECL or TYPE or error_mark_node,
   in the scope SCOPE.  */
स्थिर शून्य
bind (वृक्षः name, वृक्षः decl, संरचना c_scope *scope, तार्किक invisible,
      तार्किक nested, location_t locus)
{
  संरचना c_binding *b, **here;

  जइ (binding_freelist)
    {
      b = binding_freelist;
      binding_freelist = b->prev;
    }
  अण्णहा
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

  b->u.type = रिक्त;

  b->prev = scope->bindings;
  scope->bindings = b;

  जइ (decl_jump_unsafe (decl))
    scope->has_jump_unsafe_decl = 1;

  जइ (!name)
    प्रत्यागम;

  विकल्प (वृक्षः_CODE (decl))
    {
    पक्ष LABEL_DECL:     here = &I_LABEL_BINDING (name);   भङ्ग;
    पक्ष ENUMERAL_TYPE:
    पक्ष UNION_TYPE:
    पक्ष RECORD_TYPE:    here = &I_TAG_BINDING (name);     भङ्ग;
    पक्ष VAR_DECL:
    पक्ष FUNCTION_DECL:
    पक्ष TYPE_DECL:
    पक्ष CONST_DECL:
    पक्ष PARM_DECL:
    पक्ष ERROR_MARK:     here = &I_चिह्नम्_BINDING (name);  भङ्ग;

    स्वभाव:
      gcc_unreachable ();
    }

  /* Locate the appropriate place in the chain of shadowed decls
     to insert this binding.  Normally, scope == current_scope and
     this does nothing.  */
  जाव (*here && (*here)->depth > scope->depth)
    here = &(*here)->shadowed;

  b->shadowed = *here;
  *here = b;
}

/* Clear the binding structure B, stick it on the binding_freelist,
   and return the former value of b->prev.  This is used by pop_scope
   and get_parm_info to iterate destructively over all the bindings
   from a given scope.  */
स्थिर संरचना c_binding *
free_binding_and_advance (संरचना c_binding *b)
{
  संरचना c_binding *prev = b->prev;

  memset (b, 0, परिमाण (संरचना c_binding));
  b->prev = binding_freelist;
  binding_freelist = b;

  प्रत्यागम prev;
}

/* Bind a label.  Like bind, but skip fields which aren't used for
   labels, and add the LABEL_VARS value.  */
स्थिर शून्य
bind_label (वृक्षः name, वृक्षः label, संरचना c_scope *scope,
	    संरचना c_label_vars *label_vars)
{
  संरचना c_binding *b;

  bind (name, label, scope, /*invisible=*/मिच्छ, /*nested=*/मिच्छ,
	UNKNOWN_LOCATION);

  scope->has_label_bindings = सच्च;

  b = scope->bindings;
  gcc_assert (b->decl == label);
  label_vars->shadowed = b->u.label;
  b->u.label = label_vars;
}

/* Hook called at end of compilation to assume 1 elt
   for a file-scope tentative array defn that wasn't complete before.  */

शून्य
c_finish_incomplete_decl (वृक्षः decl)
{
  जइ (VAR_P (decl))
    {
      वृक्षः type = वृक्षः_TYPE (decl);
      जइ (type != error_mark_ग्रन्थिः
	  && वृक्षः_CODE (type) == ARRAY_TYPE
	  && !DECL_EXTERNAL (decl)
	  && TYPE_DOMAIN (type) == NULL_वृक्षः)
	{
	  जइ (flag_isoc2y && !वृक्षः_PUBLIC (decl))
	    error_at (DECL_SOURCE_LOCATION (decl),
		      "array size missing in %q+D", decl);
	  अण्णहा
	    warning_at (DECL_SOURCE_LOCATION (decl),
			0, "array %q+D assumed to have one element", decl);

	  complete_array_type (&वृक्षः_TYPE (decl), NULL_वृक्षः, सच्च);

	  relayout_decl (decl);
	}
    }
}

/* Record that inline function FUNC contains a reference (location
   LOC) to static DECL (file-scope or function-local according to
   TYPE).  */

शून्य
record_inline_static (location_t loc, वृक्षः func, वृक्षः decl,
		      गणना c_inline_static_type type)
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

स्थिर शून्य
check_inline_statics (शून्य)
{
  संरचना c_inline_static *csi;
  प्रति (csi = c_inline_statics; csi; csi = csi->next)
    {
      जइ (DECL_EXTERNAL (csi->function))
	विकल्प (csi->type)
	  {
	  पक्ष csi_internal:
	    pedwarn (csi->location, 0,
		     "%qD is static but used in inline function %qD "
		     "which is not static", csi->static_decl, csi->function);
	    भङ्ग;
	  पक्ष csi_modifiable:
	    pedwarn (csi->location, 0,
		     "%q+D is static but declared in inline function %qD "
		     "which is not static", csi->static_decl, csi->function);
	    भङ्ग;
	  स्वभाव:
	    gcc_unreachable ();
	  }
    }
  c_inline_statics = रिक्त;
}

/* Fill in a c_spot_bindings structure.  If DEFINING is true, set it
   for the current state, otherwise set it to uninitialized.  */

स्थिर शून्य
set_spot_bindings (संरचना c_spot_bindings *p, तार्किक defining)
{
  जइ (defining)
    {
      p->scope = current_scope;
      p->bindings_in_scope = current_scope->bindings;
    }
  अण्णहा
    {
      p->scope = रिक्त;
      p->bindings_in_scope = रिक्त;
    }
  p->stmt_exprs = 0;
  p->वामः_stmt_व्यञ्जकम् = मिच्छ;
}

/* Update spot bindings P as we pop out of SCOPE.  Return true if we
   should push decls for a label.  */

स्थिर तार्किक
update_spot_bindings (संरचना c_scope *scope, संरचना c_spot_bindings *p)
{
  जइ (p->scope != scope)
    {
      /* This label or goto is defined in some other scope, or it is a
	 label which is not yet defined.  There is nothing to
	 update.  */
      प्रत्यागम मिच्छ;
    }

  /* Adjust the spot bindings to refer to the bindings already defined
     in the enclosing scope.  */
  p->scope = scope->outer;
  p->bindings_in_scope = p->scope->bindings;

  प्रत्यागम सच्च;
}

/* The Objective-C front-end often needs to determine the current scope.  */

शून्य *
objc_get_current_scope (शून्य)
{
  प्रत्यागम current_scope;
}

/* The following function is used only by Objective-C.  It needs to live here
   because it accesses the innards of c_scope.  */

शून्य
objc_mark_locals_volatile (शून्य *enclosing_blk)
{
  संरचना c_scope *scope;
  संरचना c_binding *b;

  प्रति (scope = current_scope;
       scope && scope != enclosing_blk;
       scope = scope->outer)
    {
      प्रति (b = scope->bindings; b; b = b->prev)
	objc_volatilize_decl (b->decl);

      /* Do not climb up past the current function.  */
      जइ (scope->function_body)
	भङ्ग;
    }
}

/* Return true if we are in the global binding level.  */

तार्किक
global_bindings_p (शून्य)
{
  प्रत्यागम current_scope == file_scope;
}

/* Return true if we're declaring parameters in an old-style function
   declaration.  */

तार्किक
old_style_parameter_scope (शून्य)
{
  /* If processing parameters and there is no function statement list, we
   * have an old-style function declaration.  */
  प्रत्यागम (current_scope->parm_flag && !DECL_SAVED_वृक्षः (current_function_decl));
}

शून्य
keep_next_level (शून्य)
{
  keep_next_level_flag = सच्च;
}

/* Set the flag for the FLOAT_CONST_DECIMAL64 pragma being ON.  */

शून्य
set_float_const_decimal64 (शून्य)
{
  current_scope->float_const_decimal64 = सच्च;
}

/* Clear the flag for the FLOAT_CONST_DECIMAL64 pragma.  */

शून्य
clear_float_const_decimal64 (शून्य)
{
  current_scope->float_const_decimal64 = मिच्छ;
}

/* Return nonzero if an unsuffixed float constant is _Decimal64.  */

तार्किक
float_const_decimal64_p (शून्य)
{
  प्रत्यागम current_scope->float_const_decimal64;
}

/* Identify this scope as currently being filled with parameters.  */

शून्य
declare_parm_level (शून्य)
{
  current_scope->parm_flag = सच्च;
}

शून्य
प्रक्षिप_scope (शून्य)
{
  जइ (next_is_function_body)
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
      current_scope->parm_flag         = मिच्छ;
      current_scope->function_body     = सच्च;
      current_scope->keep              = सच्च;
      current_scope->outer_function    = current_function_scope;
      current_function_scope           = current_scope;

      keep_next_level_flag = मिच्छ;
      next_is_function_body = मिच्छ;

      /* The FLOAT_CONST_DECIMAL64 pragma applies to nested scopes.  */
      जइ (current_scope->outer)
	current_scope->float_const_decimal64
	  = current_scope->outer->float_const_decimal64;
      अण्णहा
	current_scope->float_const_decimal64 = मिच्छ;
    }
  अण्णहा
    {
      संरचना c_scope *scope;
      जइ (scope_freelist)
	{
	  scope = scope_freelist;
	  scope_freelist = scope->outer;
	}
      अण्णहा
	scope = ggc_cleared_alloc<c_scope> ();

      /* The FLOAT_CONST_DECIMAL64 pragma applies to nested scopes.  */
      जइ (current_scope)
	scope->float_const_decimal64 = current_scope->float_const_decimal64;
      अण्णहा
	scope->float_const_decimal64 = मिच्छ;

      scope->keep          = keep_next_level_flag;
      scope->outer         = current_scope;
      scope->depth	   = current_scope ? (current_scope->depth + 1) : 0;

      /* Check for scope depth overflow.  Unlikely (2^28 == 268,435,456) but
	 possible.  */
      जइ (current_scope && scope->depth == 0)
	{
	  scope->depth--;
	  sorry ("GCC supports only %u nested scopes", scope->depth);
	}

      current_scope        = scope;
      keep_next_level_flag = मिच्छ;
    }
}

/* This is called when we are leaving SCOPE.  For each label defined
   in SCOPE, add any appropriate decls to its decls_in_scope fields.
   These are the decls whose initialization will be skipped by a goto
   later in the function.  */

स्थिर शून्य
update_label_decls (संरचना c_scope *scope)
{
  संरचना c_scope *s;

  s = scope;
  जाव (s != रिक्त)
    {
      जइ (s->has_label_bindings)
	{
	  संरचना c_binding *b;

	  प्रति (b = s->bindings; b != रिक्त; b = b->prev)
	    {
	      संरचना c_label_vars *label_vars;
	      संरचना c_binding *b1;
	      तार्किक hjud;
	      unsigned पूर्णाङ्क ix;
	      संरचना c_goto_bindings *g;

	      जइ (वृक्षः_CODE (b->decl) != LABEL_DECL)
		अनुवर्त;
	      label_vars = b->u.label;

	      b1 = label_vars->label_bindings.bindings_in_scope;
	      जइ (label_vars->label_bindings.scope == रिक्त)
		hjud = मिच्छ;
	      अण्णहा
		hjud = label_vars->label_bindings.scope->has_jump_unsafe_decl;
	      जइ (update_spot_bindings (scope, &label_vars->label_bindings))
		{
		  /* This label is defined in this scope.  */
		  जइ (hjud)
		    {
		      प्रति (; b1 != रिक्त; b1 = b1->prev)
			{
			  /* A goto from later in the function to this
			     label will never see the initialization
			     of B1, if any.  Save it to issue a
			     warning if needed.  */
			  जइ (decl_jump_unsafe (b1->decl))
			    vec_safe_प्रक्षिप(label_vars->decls_in_scope, b1->decl);
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
      जइ (s == current_function_scope)
	भङ्ग;

      s = s->outer;
    }
}

/* Exit a scope.  Restore the state of the identifier-decl mappings
   that were in effect when this scope was entered.  Return a BLOCK
   node containing all the DECLs in this scope that are of interest
   to debug info generation.  */

वृक्षः
निष्कासय_scope (शून्य)
{
  संरचना c_scope *scope = current_scope;
  वृक्षः block, context, p;
  संरचना c_binding *b;

  तार्किक functionbody = scope->function_body;
  तार्किक keep = functionbody || scope->keep || scope->bindings;

  update_label_decls (scope);

  /* If appropriate, create a BLOCK to record the decls for the life
     of this function.  */
  block = NULL_वृक्षः;
  जइ (keep)
    {
      block = make_ग्रन्थिः (BLOCK);
      BLOCK_SUBBLOCKS (block) = scope->blocks;
      वृक्षः_USED (block) = 1;

      /* In each subblock, record that this is its superior.  */
      प्रति (p = scope->blocks; p; p = BLOCK_CHAIN (p))
	BLOCK_SUPERCONTEXT (p) = block;

      BLOCK_VARS (block) = NULL_वृक्षः;
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
  जइ (scope->function_body)
    context = current_function_decl;
  अण्णहा जइ (scope == file_scope)
    {
      वृक्षः file_decl
	= build_translation_unit_decl (get_identifier (main_निवेशः_filename));
      context = file_decl;
      debug_hooks->register_main_translation_unit (file_decl);
    }
  अण्णहा
    context = block;

  /* Clear all bindings in this scope.  */
  प्रति (b = scope->bindings; b; b = free_binding_and_advance (b))
    {
      p = b->decl;
      विकल्प (वृक्षः_CODE (p))
	{
	पक्ष LABEL_DECL:
	  /* Warnings for unused labels, errors for undefined labels.  */
	  जइ (वृक्षः_USED (p) && !DECL_INITIAL (p))
	    {
	      error ("label %q+D used but not defined", p);
	      DECL_INITIAL (p) = error_mark_ग्रन्थिः;
	    }
	  अण्णहा
	    warn_for_unused_label (p);

	  /* Labels go in BLOCK_VARS.  */
	  DECL_CHAIN (p) = BLOCK_VARS (block);
	  BLOCK_VARS (block) = p;
	  gcc_assert (I_LABEL_BINDING (b->id) == b);
	  I_LABEL_BINDING (b->id) = b->shadowed;

	  /* Also pop back to the shadowed label_vars.  */
	  release_वृक्षः_vector (b->u.label->decls_in_scope);
	  b->u.label = b->u.label->shadowed;
	  भङ्ग;

	पक्ष ENUMERAL_TYPE:
	पक्ष UNION_TYPE:
	पक्ष RECORD_TYPE:

	  /* Types may not have tag-names, in which case the type
	     appears in the bindings list with b->id NULL.  */
	  जइ (b->id)
	    {
	      gcc_assert (I_TAG_BINDING (b->id) == b);
	      I_TAG_BINDING (b->id) = b->shadowed;
	    }
	  भङ्ग;

	पक्ष FUNCTION_DECL:
	  /* Propagate TREE_ADDRESSABLE from nested functions to their
	     containing functions.  */
	  जइ (!वृक्षः_ASM_WRITTEN (p)
	      && DECL_INITIAL (p) != NULL_वृक्षः
	      && वृक्षः_ADDRESSABLE (p)
	      && DECL_ABSTRACT_ORIGIN (p) != NULL_वृक्षः
	      && DECL_ABSTRACT_ORIGIN (p) != p)
	    वृक्षः_ADDRESSABLE (DECL_ABSTRACT_ORIGIN (p)) = 1;
	  जइ (!वृक्षः_PUBLIC (p)
	      && !DECL_INITIAL (p)
	      && !b->nested
	      && scope != file_scope
	      && scope != external_scope)
	    {
	      error ("nested function %q+D declared but never defined", p);
	      undef_nested_function = सच्च;
	    }
	  अण्णहा जइ (DECL_DECLARED_INLINE_P (p)
		   && वृक्षः_PUBLIC (p)
		   && !DECL_INITIAL (p))
	    {
	      /* C99 6.7.4p6: "a function with external linkage... declared
		 with an inline function specifier ... shall also be defined
		 in the same translation unit."  */
	      जइ (!flag_gnu89_inline
		  && !lookup_attribute ("gnu_inline", DECL_ATTRIBUTES (p))
		  && scope == external_scope)
		pedwarn (निवेशः_location, 0,
			 "inline function %q+D declared but never defined", p);
	      DECL_EXTERNAL (p) = 1;
	    }

	  गच्छ common_चिह्नम्;

	पक्ष VAR_DECL:
	  /* Warnings for unused variables.  */
	  जइ ((!वृक्षः_USED (p) || !DECL_READ_P (p))
	      && !warning_suppressed_p (p, OPT_Wunused_but_set_variable_)
	      && !DECL_IN_SYSTEM_HEADER (p)
	      && DECL_NAME (p)
	      && !DECL_ARTIFICIAL (p)
	      && scope != file_scope
	      && scope != external_scope)
	    {
	      जइ (!वृक्षः_USED (p))
		{
		  warning (OPT_Wunused_variable, "unused variable %q+D", p);
		  suppress_warning (p, OPT_Wunused_variable);
		}
	      अण्णहा जइ (DECL_CONTEXT (p) == current_function_decl)
		warning_at (DECL_SOURCE_LOCATION (p),
			    OPT_Wunused_but_set_variable_,
			    "variable %qD set but not used", p);
	    }

	  जइ (b->inner_comp)
	    {
	      error ("type of array %q+D completed incompatibly with"
		     " implicit initialization", p);
	    }

	  /* Fall through.  */
	पक्ष TYPE_DECL:
	पक्ष CONST_DECL:
	common_चिह्नम्:
	  /* All of these go in BLOCK_VARS, but only if this is the
	     binding in the home scope.  */
	  जइ (!b->nested)
	    {
	      DECL_CHAIN (p) = BLOCK_VARS (block);
	      BLOCK_VARS (block) = p;
	    }
	  अण्णहा जइ (VAR_OR_FUNCTION_DECL_P (p) && scope != file_scope)
	    {
	      /* For block local externs add a special
		 DECL_EXTERNAL decl for debug info generation.  */
	      वृक्षः extp = copy_ग्रन्थिः (p);

	      DECL_EXTERNAL (extp) = 1;
	      वृक्षः_STATIC (extp) = 0;
	      वृक्षः_PUBLIC (extp) = 1;
	      DECL_INITIAL (extp) = NULL_वृक्षः;
	      DECL_LANG_SPECIFIC (extp) = रिक्त;
	      DECL_CONTEXT (extp) = current_function_decl;
	      जइ (वृक्षः_CODE (p) == FUNCTION_DECL)
		{
		  DECL_RESULT (extp) = NULL_वृक्षः;
		  DECL_SAVED_वृक्षः (extp) = NULL_वृक्षः;
		  DECL_STRUCT_FUNCTION (extp) = रिक्त;
		}
	      जइ (b->locus != UNKNOWN_LOCATION)
		DECL_SOURCE_LOCATION (extp) = b->locus;
	      DECL_CHAIN (extp) = BLOCK_VARS (block);
	      BLOCK_VARS (block) = extp;
	    }
	  /* If this is the file scope set DECL_CONTEXT of each decl to
	     the TRANSLATION_UNIT_DECL.  This makes same_translation_unit_p
	     work.  */
	  जइ (scope == file_scope)
	      DECL_CONTEXT (p) = context;

	  gcc_fallthrough ();
	  /* Parameters go in DECL_ARGUMENTS, not BLOCK_VARS, and have
	     already been put there by store_parm_decls.  Unused-
	     parameter warnings are handled by function.cc.
	     error_mark_node obviously does not go in BLOCK_VARS and
	     does not get unused-variable warnings.  */
	पक्ष PARM_DECL:
	पक्ष ERROR_MARK:
	  /* It is possible for a decl not to have a name.  We get
	     here with b->id NULL in this case.  */
	  जइ (b->id)
	    {
	      gcc_assert (I_चिह्नम्_BINDING (b->id) == b);
	      I_चिह्नम्_BINDING (b->id) = b->shadowed;
	      जइ (b->shadowed && b->shadowed->u.type)
		वृक्षः_TYPE (b->shadowed->decl) = b->shadowed->u.type;
	    }
	  भङ्ग;

	स्वभाव:
	  gcc_unreachable ();
	}
    }


  /* Dispose of the block that we just made inside some higher level.  */
  जइ ((scope->function_body || scope == file_scope) && context)
    {
      DECL_INITIAL (context) = block;
      BLOCK_SUPERCONTEXT (block) = context;
    }
  अण्णहा जइ (scope->outer)
    {
      जइ (block)
	SCOPE_LIST_APPEND (scope->outer, blocks, block);
      /* If we did not make a block for the scope just exited, any
	 blocks made for inner scopes must be carried forward so they
	 will later become subblocks of something else.  */
      अण्णहा जइ (scope->blocks)
	SCOPE_LIST_CONCAT (scope->outer, blocks, scope, blocks);
    }

  /* Pop the current scope, and free the structure for reuse.  */
  current_scope = scope->outer;
  जइ (scope->function_body)
    current_function_scope = scope->outer_function;

  memset (scope, 0, परिमाण (संरचना c_scope));
  scope->outer = scope_freelist;
  scope_freelist = scope;

  प्रत्यागम block;
}

शून्य
प्रक्षिप_file_scope (शून्य)
{
  वृक्षः decl;

  जइ (file_scope)
    प्रत्यागम;

  /* Call the target stack_protect_guard hook if the stack protection
     guard is declared as a global symbol.  */
  जइ (targetm.राशिः_protect_guard_चिह्नम्_p ())
    {
      वृक्षः decl = targetm.राशिः_protect_guard ();
      DECL_CHAIN (decl) = visible_builtins;
      visible_builtins = decl;
    }

  प्रक्षिप_scope ();
  file_scope = current_scope;

  start_fname_decls ();

  प्रति (decl = visible_builtins; decl; decl = DECL_CHAIN (decl))
    bind (DECL_NAME (decl), decl, file_scope,
	  /*invisible=*/मिच्छ, /*nested=*/सच्च, DECL_SOURCE_LOCATION (decl));
}

शून्य
निष्कासय_file_scope (शून्य)
{
  /* In case there were missing closebraces, get us back to the global
     binding level.  */
  जाव (current_scope != file_scope)
    निष्कासय_scope ();

  /* __FUNCTION__ is defined at file scope ("").  This
     call may not be necessary as my tests indicate it
     still works without it.  */
  finish_fname_decls ();

  check_inline_statics ();

  /* This is the point to write out a PCH if we're doing that.
     In that case we do not want to do anything else.  */
  जइ (pch_file)
    {
      c_common_write_pch ();
      /* Ensure even the callers don't try to finalize the CU.  */
      flag_syntax_only = 1;
      प्रत्यागम;
    }

  /* Pop off the file scope and close this translation unit.  */
  निष्कासय_scope ();
  file_scope = 0;

  maybe_apply_pending_pragma_weaks ();
}

/* Whether we are currently inside the initializer for an
   underspecified object definition (C23 auto or constexpr).  */
स्थिर तार्किक in_underspecified_init;

/* Start an underspecified object definition for NAME at LOC.  This
   means that NAME is shadowed inside its initializer, so neither the
   definition being initialized, nor any definition from an outer
   scope, may be referenced during that initializer.  Return state to
   be passed to finish_underspecified_init.  If NAME is NULL_TREE, the
   underspecified object is a (constexpr) compound literal; there is
   no shadowing in that case, but all the other restrictions on
   underspecified object definitions still apply.  */
unsigned पूर्णाङ्क
start_underspecified_init (location_t loc, वृक्षः name)
{
  तार्किक prev = in_underspecified_init;
  तार्किक ok;
  जइ (name == NULL_वृक्षः)
    ok = सच्च;
  अण्णहा
    {
      वृक्षः decl = build_decl (loc, VAR_DECL, name, error_mark_ग्रन्थिः);
      C_DECL_UNDERSPECIFIED (decl) = 1;
      संरचना c_scope *scope = current_scope;
      संरचना c_binding *b = I_चिह्नम्_BINDING (name);
      जइ (b && B_IN_SCOPE (b, scope))
	{
	  error_at (loc, "underspecified declaration of %qE, which is already "
		    "declared in this scope", name);
	  ok = मिच्छ;
	}
      अण्णहा
	{
	  bind (name, decl, scope, मिच्छ, मिच्छ, loc);
	  ok = सच्च;
	}
    }
  in_underspecified_init = सच्च;
  प्रत्यागम ok | (prev << 1);
}

/* Finish an underspecified object definition for NAME, before that
   name is bound to the real declaration instead of a placeholder.
   PREV_STATE is the value returned by the call to
   start_underspecified_init.  If NAME is NULL_TREE, this means a
   compound literal, as for start_underspecified_init.  */
शून्य
finish_underspecified_init (वृक्षः name, unsigned पूर्णाङ्क prev_state)
{
  जइ (name != NULL_वृक्षः && (prev_state & 1))
    {
      /* A VAR_DECL was bound to the name to shadow any previous
	 declarations for the name; remove that binding now.  */
      संरचना c_scope *scope = current_scope;
      संरचना c_binding *b = I_चिह्नम्_BINDING (name);
      gcc_assert (b);
      gcc_assert (B_IN_SCOPE (b, scope));
      gcc_assert (VAR_P (b->decl));
      gcc_assert (C_DECL_UNDERSPECIFIED (b->decl));
      I_चिह्नम्_BINDING (name) = b->shadowed;
      /* In erroneous cases there may be other bindings added to this
	 scope during the initializer.  */
      संरचना c_binding **p = &scope->bindings;
      जाव (*p != b)
	p = &((*p)->prev);
      *p = free_binding_and_advance (*p);
    }
  in_underspecified_init = (prev_state & (1u << 1)) >> 1;
}

/* Adjust the bindings for the start of a statement expression.  */

शून्य
c_bindings_start_stmt_व्यञ्जकम् (संरचना c_spot_bindings* switch_bindings)
{
  संरचना c_scope *scope;

  प्रति (scope = current_scope; scope != रिक्त; scope = scope->outer)
    {
      संरचना c_binding *b;

      जइ (!scope->has_label_bindings)
	अनुवर्त;

      प्रति (b = scope->bindings; b != रिक्त; b = b->prev)
	{
	  संरचना c_label_vars *label_vars;
	  unsigned पूर्णाङ्क ix;
	  संरचना c_goto_bindings *g;

	  जइ (वृक्षः_CODE (b->decl) != LABEL_DECL)
	    अनुवर्त;
	  label_vars = b->u.label;
	  ++label_vars->label_bindings.stmt_exprs;
	  FOR_EACH_VEC_SAFE_ELT (label_vars->gotos, ix, g)
	    ++g->goto_bindings.stmt_exprs;
	}
    }

  जइ (switch_bindings != रिक्त)
    ++switch_bindings->stmt_exprs;
}

/* Adjust the bindings for the end of a statement expression.  */

शून्य
c_bindings_end_stmt_व्यञ्जकम् (संरचना c_spot_bindings *switch_bindings)
{
  संरचना c_scope *scope;

  प्रति (scope = current_scope; scope != रिक्त; scope = scope->outer)
    {
      संरचना c_binding *b;

      जइ (!scope->has_label_bindings)
	अनुवर्त;

      प्रति (b = scope->bindings; b != रिक्त; b = b->prev)
	{
	  संरचना c_label_vars *label_vars;
	  unsigned पूर्णाङ्क ix;
	  संरचना c_goto_bindings *g;

	  जइ (वृक्षः_CODE (b->decl) != LABEL_DECL)
	    अनुवर्त;
	  label_vars = b->u.label;
	  --label_vars->label_bindings.stmt_exprs;
	  जइ (label_vars->label_bindings.stmt_exprs < 0)
	    {
	      label_vars->label_bindings.वामः_stmt_व्यञ्जकम् = सच्च;
	      label_vars->label_bindings.stmt_exprs = 0;
	    }
	  FOR_EACH_VEC_SAFE_ELT (label_vars->gotos, ix, g)
	    {
	      --g->goto_bindings.stmt_exprs;
	      जइ (g->goto_bindings.stmt_exprs < 0)
		{
		  g->goto_bindings.वामः_stmt_व्यञ्जकम् = सच्च;
		  g->goto_bindings.stmt_exprs = 0;
		}
	    }
	}
    }

  जइ (switch_bindings != रिक्त)
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

स्थिर शून्य
pushtag (location_t loc, वृक्षः name, वृक्षः type)
{
  /* Record the identifier as the type's name if it has none.  */
  जइ (name && !TYPE_NAME (type))
    TYPE_NAME (type) = name;
  bind (name, type, current_scope, /*invisible=*/मिच्छ, /*nested=*/मिच्छ, loc);

  /* Create a fake NULL-named TYPE_DECL node whose TREE_TYPE will be the
     tagged type we just added to the current scope.  This fake
     NULL-named TYPE_DECL node helps dwarfout.c to know when it needs
     to output a representation of a tagged type, and it also gives
     us a convenient place to record the "scope start" address for the
     tagged type, and it is used to track whether the type is used
     in a non-local context via mark_decl_used.  */

  TYPE_STUB_DECL (type) = pushdecl (build_decl (loc,
						TYPE_DECL, NULL_वृक्षः, type));

  /* An approximation for now, so we can tell this is a function-scope tag.
     This will be updated in pop_scope.  */
  TYPE_CONTEXT (type) = DECL_CONTEXT (TYPE_STUB_DECL (type));

  जइ (warn_cxx_compat && name != NULL_वृक्षः)
    {
      संरचना c_binding *b = I_चिह्नम्_BINDING (name);

      जइ (b != रिक्त
	  && b->decl != NULL_वृक्षः
	  && वृक्षः_CODE (b->decl) == TYPE_DECL
	  && (B_IN_CURRENT_SCOPE (b)
	      || (current_scope == file_scope && B_IN_EXTERNAL_SCOPE (b)))
	  && (TYPE_MAIN_VARIANT (वृक्षः_TYPE (b->decl))
	      != TYPE_MAIN_VARIANT (type)))
	{
	  auto_diagnostic_group d;
	  जइ (warning_at (loc, OPT_Wc___compat,
			  "using %qD as both a typedef and a tag is "
			  "invalid in C++", b->decl)
	      && b->locus != UNKNOWN_LOCATION)
	    inform (b->locus, "originally defined here");
	}
    }
}

/* An exported interface to pushtag.  This is used by the gdb plugin's
   binding oracle to introduce a new tag binding.  */

शून्य
c_pushtag (location_t loc, वृक्षः name, वृक्षः type)
{
  pushtag (loc, name, type);
}

/* An exported interface to bind a declaration.  LOC is the location
   to use.  DECL is the declaration to bind.  The decl's name is used
   to determine how it is bound.  If DECL is a VAR_DECL, then
   IS_GLOBAL determines whether the decl is put into the global (file
   and external) scope or the current function's scope; if DECL is not
   a VAR_DECL then it is always put into the file scope.  */

शून्य
c_bind (location_t loc, वृक्षः decl, तार्किक is_global)
{
  संरचना c_scope *scope;
  तार्किक nested = मिच्छ;

  जइ (!VAR_P (decl) || current_function_scope == रिक्त)
    {
      /* Types and functions are always considered to be global.  */
      scope = file_scope;
      DECL_EXTERNAL (decl) = 1;
      वृक्षः_PUBLIC (decl) = 1;
    }
  अण्णहा जइ (is_global)
    {
      /* Also bind it into the external scope.  */
      bind (DECL_NAME (decl), decl, external_scope, सच्च, मिच्छ, loc);
      nested = सच्च;
      scope = file_scope;
      DECL_EXTERNAL (decl) = 1;
      वृक्षः_PUBLIC (decl) = 1;
    }
  अण्णहा
    {
      DECL_CONTEXT (decl) = current_function_decl;
      वृक्षः_PUBLIC (decl) = 0;
      scope = current_function_scope;
    }

  bind (DECL_NAME (decl), decl, scope, मिच्छ, nested, loc);
}


/* Stores the first FILE*, const struct tm* etc. argument type (whatever
   it is) seen in a declaration of a file I/O etc. built-in, corresponding
   to the builtin_structptr_types array.  Subsequent declarations of such
   built-ins are expected to refer to it rather than to fileptr_type_node,
   etc. which is just void* (or to any other type).
   Used only by match_builtin_function_types.  */

स्थिर ध्रुव unsigned builtin_structptr_type_गणनम्
  = ARRAY_SIZE (builtin_structptr_types);

स्थिर GTY(()) वृक्षः last_structptr_types[builtin_structptr_type_गणनम्];

/* Returns true if types T1 and T2 representing return types or types
   of function arguments are close enough to be considered interchangeable
   in redeclarations of built-in functions.  */

स्थिर तार्किक
types_close_enough_to_match (वृक्षः t1, वृक्षः t2)
{
  प्रत्यागम (TYPE_MODE (t1) == TYPE_MODE (t2)
	  && POINTER_TYPE_P (t1) == POINTER_TYPE_P (t2)
	  && FUNCTION_POINTER_TYPE_P (t1) == FUNCTION_POINTER_TYPE_P (t2));
}

/* Subroutine of compare_decls.  Allow harmless mismatches in return
   and argument types provided that the type modes match.  Set *STRICT
   and *ARGNO to the expected argument type and number in case of
   an argument type mismatch or null and zero otherwise.  Return
   a unified type given a suitable match, and 0 otherwise.  */

स्थिर वृक्षः
match_builtin_function_types (वृक्षः newtype, वृक्षः oldtype,
			      वृक्षः *strict, unsigned *argno)
{
  *argno = 0;
  *strict = NULL_वृक्षः;

  /* Accept the return type of the new declaration if it has the same
     mode and if they're both pointers or if neither is.  */
  वृक्षः oldrettype = वृक्षः_TYPE (oldtype);
  वृक्षः newrettype = वृक्षः_TYPE (newtype);

  जइ (!types_close_enough_to_match (oldrettype, newrettype))
    प्रत्यागम NULL_वृक्षः;

  /* Check that the return types are compatible but don't fail if they
     are not (e.g., int vs long in ILP32) and just let the caller know.  */
  जइ (!comptypes (TYPE_MAIN_VARIANT (oldrettype),
		  TYPE_MAIN_VARIANT (newrettype)))
    *strict = oldrettype;

  वृक्षः oldargs = TYPE_ARG_TYPES (oldtype);
  वृक्षः newargs = TYPE_ARG_TYPES (newtype);
  वृक्षः tryargs = newargs;

  ध्रुव unsigned nlst = ARRAY_SIZE (last_structptr_types);
  ध्रुव unsigned nbst = ARRAY_SIZE (builtin_structptr_types);

  gcc_checking_assert (nlst == nbst);

  प्रति (unsigned i = 1; oldargs || newargs; ++i)
    {
      जइ (!oldargs
	  || !newargs
	  || !वृक्षः_मानम् (oldargs)
	  || !वृक्षः_मानम् (newargs))
	प्रत्यागम NULL_वृक्षः;

      वृक्षः oldtype = TYPE_MAIN_VARIANT (वृक्षः_मानम् (oldargs));
      वृक्षः newtype = वृक्षः_मानम् (newargs);
      जइ (newtype == error_mark_ग्रन्थिः)
       प्रत्यागम NULL_वृक्षः;
      newtype = TYPE_MAIN_VARIANT (newtype);

      जइ (!types_close_enough_to_match (oldtype, newtype))
	प्रत्यागम NULL_वृक्षः;

      unsigned j = nbst;
      जइ (POINTER_TYPE_P (oldtype))
	/* Iterate over well-known struct types like FILE (whose types
	   aren't known to us) and compare the pointer to each to
	   the pointer argument.  */
	प्रति (j = 0; j < nbst; ++j)
	  {
	    जइ (वृक्षः_मानम् (oldargs) != builtin_structptr_types[j].ग्रन्थिः)
	      अनुवर्त;
	    /* Store the first FILE* etc. argument type (whatever it is), and
	       expect any subsequent declarations of file I/O etc. built-ins
	       to refer to it rather than to fileptr_type_node etc. which is
	       just void* (or const void*).  */
	    जइ (last_structptr_types[j])
	      {
		जइ (!comptypes (last_structptr_types[j], newtype))
		  {
		    *argno = i;
		    *strict = last_structptr_types[j];
		  }
	      }
	    अण्णहा
	      last_structptr_types[j] = newtype;
	    भङ्ग;
	  }

      जइ (j == nbst && !comptypes (oldtype, newtype))
	{
	  जइ (POINTER_TYPE_P (oldtype))
	    {
	      /* For incompatible pointers, only reject differences in
		 the unqualified variants of the referenced types but
		 consider differences in qualifiers as benign (report
		 those to caller via *STRICT below).  */
	      वृक्षः oldref = TYPE_MAIN_VARIANT (वृक्षः_TYPE (oldtype));
	      वृक्षः newref = TYPE_MAIN_VARIANT (वृक्षः_TYPE (newtype));
	      जइ (!comptypes (oldref, newref))
		प्रत्यागम NULL_वृक्षः;
	    }

	  जइ (!*strict)
	    {
	      *argno = i;
	      *strict = oldtype;
	    }
	}

      oldargs = वृक्षः_CHAIN (oldargs);
      newargs = वृक्षः_CHAIN (newargs);
    }

  वृक्षः trytype = c_build_function_type (newrettype, tryargs);

  /* Allow declaration to change transaction_safe attribute.  */
  वृक्षः oldattrs = TYPE_ATTRIBUTES (oldtype);
  वृक्षः oldtsafe = lookup_attribute ("transaction_safe", oldattrs);
  वृक्षः newattrs = TYPE_ATTRIBUTES (newtype);
  वृक्षः newtsafe = lookup_attribute ("transaction_safe", newattrs);
  जइ (oldtsafe && !newtsafe)
    oldattrs = remove_attribute ("transaction_safe", oldattrs);
  अण्णहा जइ (newtsafe && !oldtsafe)
    oldattrs = वृक्षः_cons (get_identifier ("transaction_safe"),
			  NULL_वृक्षः, oldattrs);

  प्रत्यागम c_build_type_attribute_variant (trytype, oldattrs);
}

/* Subroutine of diagnose_mismatched_decls.  Check for function type
   mismatch involving an empty arglist vs a nonempty one and give clearer
   diagnostics.  */
स्थिर शून्य
diagnose_arglist_conflict (वृक्षः newdecl, वृक्षः olddecl,
			   वृक्षः newtype, वृक्षः oldtype)
{
  वृक्षः t;

  जइ (वृक्षः_CODE (olddecl) != FUNCTION_DECL
      || !comptypes (वृक्षः_TYPE (oldtype), वृक्षः_TYPE (newtype))
      || !((!prototype_p (oldtype) && DECL_INITIAL (olddecl) == NULL_वृक्षः)
	   || (!prototype_p (newtype) && DECL_INITIAL (newdecl) == NULL_वृक्षः)))
    प्रत्यागम;

  t = TYPE_ARG_TYPES (oldtype);
  जइ (t == NULL_वृक्षः)
    t = TYPE_ARG_TYPES (newtype);
  प्रति (; t; t = वृक्षः_CHAIN (t))
    {
      वृक्षः type = वृक्षः_मानम् (t);

      जइ (वृक्षः_CHAIN (t) == NULL_वृक्षः
	  && TYPE_MAIN_VARIANT (type) != void_type_ग्रन्थिः)
	{
	  inform (निवेशः_location, "a parameter list with an ellipsis "
		  "cannot match an empty parameter name list declaration");
	  भङ्ग;
	}

      जइ (!error_operand_p (type)
	  && c_type_promotes_to (type) != type)
	{
	  inform (निवेशः_location, "an argument type that has a default "
		  "promotion cannot match an empty parameter name list "
		  "declaration");
	  भङ्ग;
	}
    }
}

/* Another subroutine of diagnose_mismatched_decls.  OLDDECL is an
   old-style function definition, NEWDECL is a prototype declaration.
   Diagnose inconsistencies in the argument list.  Returns TRUE if
   the prototype is compatible, FALSE if not.  */
स्थिर तार्किक
validate_proto_after_old_defn (वृक्षः newdecl, वृक्षः newtype, वृक्षः oldtype)
{
  वृक्षः newargs, oldargs;
  पूर्णाङ्क i;

#define END_OF_ARGLIST(t) ((t) == void_type_ग्रन्थिः)

  oldargs = TYPE_ACTUAL_ARG_TYPES (oldtype);
  newargs = TYPE_ARG_TYPES (newtype);
  i = 1;

  प्रति (;;)
    {
      वृक्षः oldargtype = वृक्षः_मानम् (oldargs);
      वृक्षः newargtype = वृक्षः_मानम् (newargs);

      जइ (oldargtype == error_mark_ग्रन्थिः || newargtype == error_mark_ग्रन्थिः)
	प्रत्यागम मिच्छ;

      oldargtype = (TYPE_ATOMIC (oldargtype)
		    ? c_build_qualified_type (TYPE_MAIN_VARIANT (oldargtype),
					      TYPE_QUAL_ATOMIC)
		    : TYPE_MAIN_VARIANT (oldargtype));
      newargtype = (TYPE_ATOMIC (newargtype)
		    ? c_build_qualified_type (TYPE_MAIN_VARIANT (newargtype),
					      TYPE_QUAL_ATOMIC)
		    : TYPE_MAIN_VARIANT (newargtype));

      जइ (END_OF_ARGLIST (oldargtype) && END_OF_ARGLIST (newargtype))
	भङ्ग;

      /* Reaching the end of just one list means the two decls don't
	 agree on the number of arguments.  */
      जइ (END_OF_ARGLIST (oldargtype))
	{
	  error ("prototype for %q+D declares more arguments "
		 "than previous old-style definition", newdecl);
	  प्रत्यागम मिच्छ;
	}
      अण्णहा जइ (END_OF_ARGLIST (newargtype))
	{
	  error ("prototype for %q+D declares fewer arguments "
		 "than previous old-style definition", newdecl);
	  प्रत्यागम मिच्छ;
	}

      /* Type for passing arg must be consistent with that declared
	 for the arg.  */
      अण्णहा जइ (!comptypes (oldargtype, newargtype))
	{
	  error ("prototype for %q+D declares argument %d"
		 " with incompatible type",
		 newdecl, i);
	  प्रत्यागम मिच्छ;
	}

      oldargs = वृक्षः_CHAIN (oldargs);
      newargs = वृक्षः_CHAIN (newargs);
      i++;
    }

  /* If we get here, no errors were found, but do issue a warning
     for this poor-style construct.  */
  warning (0, "prototype for %q+D follows non-prototype definition",
	   newdecl);
  प्रत्यागम सच्च;
#undef END_OF_ARGLIST
}

/* Subroutine of diagnose_mismatched_decls.  Report the location of DECL,
   first in a pair of mismatched declarations, using the diagnostic
   function DIAG.  */
स्थिर शून्य
locate_old_decl (वृक्षः decl)
{
  जइ (वृक्षः_CODE (decl) == FUNCTION_DECL
      && fndecl_built_in_p (decl)
      && !C_DECL_DECLARED_BUILTIN (decl))
    ;
  अण्णहा जइ (DECL_INITIAL (decl))
    inform (निवेशः_location,
	    "previous definition of %q+D with type %qT",
	    decl, वृक्षः_TYPE (decl));
  अण्णहा जइ (C_DECL_IMPLICIT (decl))
    inform (निवेशः_location,
	    "previous implicit declaration of %q+D with type %qT",
	    decl, वृक्षः_TYPE (decl));
  अण्णहा
    inform (निवेशः_location,
	    "previous declaration of %q+D with type %qT",
	    decl, वृक्षः_TYPE (decl));
}


/* Helper function.  For a tagged type, it finds the declaration
   for a visible tag declared in the same scope if such a
   declaration exists.  */
स्थिर वृक्षः
previous_tag (वृक्षः type)
{
  संरचना c_binding *b = रिक्त;
  वृक्षः name = c_type_tag (type);

  जइ (name)
    b = I_TAG_BINDING (name);

  जइ (b)
    b = b->shadowed;

  जइ (b && B_IN_CURRENT_SCOPE (b))
    प्रत्यागम b->decl;

  प्रत्यागम NULL_वृक्षः;
}

/* Subroutine to mark functions as versioned when using the attribute
   'target_version'.  */

स्थिर शून्य
maybe_mark_function_versioned (वृक्षः decl)
{
  जइ (!DECL_FUNCTION_VERSIONED (decl))
    {
      /* Check if the name of the function has been overridden.  */
      जइ (DECL_ASSEMBLER_NAME_SET_P (decl)
	  && IDENTIFIER_POINTER (DECL_ASSEMBLER_NAME (decl))[0] == '*')
	error_at (DECL_SOURCE_LOCATION (decl),
		  "cannot use function multiversioning on a renamed function");

      /* We need to insert function version now to make sure the correct
	 pre-mangled assembler name is recorded.  */
      cgraph_ग्रन्थिः *ग्रन्थिः = cgraph_ग्रन्थिः::get_create (decl);

      जइ (!ग्रन्थिः->function_version ())
	ग्रन्थिः->निवेशय_new_function_version ();

      DECL_FUNCTION_VERSIONED (decl) = 1;

      वृक्षः mangled_name
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

स्थिर तार्किक
diagnose_mismatched_decls (वृक्षः newdecl, वृक्षः olddecl,
			   वृक्षः *newtypep, वृक्षः *oldtypep)
{
  वृक्षः newtype, oldtype;
  तार्किक retval = सच्च;

#define DECL_EXTERN_INLINE(DECL) (DECL_DECLARED_INLINE_P (DECL)  \
				  && DECL_EXTERNAL (DECL))

  /* If we have error_mark_node for either decl or type, just discard
     the previous decl - we're in an error cascade already.  */
  जइ (olddecl == error_mark_ग्रन्थिः || newdecl == error_mark_ग्रन्थिः)
    प्रत्यागम मिच्छ;
  *oldtypep = oldtype = वृक्षः_TYPE (olddecl);
  *newtypep = newtype = वृक्षः_TYPE (newdecl);
  जइ (oldtype == error_mark_ग्रन्थिः || newtype == error_mark_ग्रन्थिः)
    प्रत्यागम मिच्छ;

  /* Two different categories of symbol altogether.  This is an error
     unless OLDDECL is a builtin.  OLDDECL will be discarded in any case.  */
  जइ (वृक्षः_CODE (olddecl) != वृक्षः_CODE (newdecl))
    {
      जइ (!(वृक्षः_CODE (olddecl) == FUNCTION_DECL
	    && fndecl_built_in_p (olddecl)
	    && !C_DECL_DECLARED_BUILTIN (olddecl)))
	{
	  auto_diagnostic_group d;
	  error ("%q+D redeclared as different kind of symbol", newdecl);
	  locate_old_decl (olddecl);
	}
      अण्णहा जइ (वृक्षः_PUBLIC (newdecl))
	warning (OPT_Wbuiltin_declaration_mismatch,
		 "built-in function %q+D declared as non-function",
		 newdecl);
      अण्णहा
	warning (OPT_Wshadow, "declaration of %q+D shadows "
		 "a built-in function", newdecl);
      प्रत्यागम मिच्छ;
    }

  /* Enumerators have no linkage, so may only be declared once in a
     given scope.  */
  जइ (वृक्षः_CODE (olddecl) == CONST_DECL)
    {
      जइ (flag_isoc23
	  && TYPE_NAME (DECL_CONTEXT (newdecl))
	  && DECL_CONTEXT (newdecl) != DECL_CONTEXT (olddecl)
	  && TYPE_NAME (DECL_CONTEXT (newdecl)) == TYPE_NAME (DECL_CONTEXT (olddecl)))
	{
	  जइ (!simple_cst_equal (DECL_INITIAL (olddecl), DECL_INITIAL (newdecl)))
	    {
	      auto_diagnostic_group d;
	      error ("conflicting redeclaration of enumerator %q+D", newdecl);
	      locate_old_decl (olddecl);
	    }
	}
      अण्णहा
	{
	  auto_diagnostic_group d;
	  error ("redeclaration of enumerator %q+D", newdecl);
	  locate_old_decl (olddecl);
	}
      प्रत्यागम मिच्छ;
    }

  तार्किक pedwarned = मिच्छ;
  तार्किक warned = मिच्छ;
  तार्किक enum_and_int_p = मिच्छ;
  auto_diagnostic_group d;

  तार्किक comptypes_result = comptypes_check_enum_int (oldtype, newtype,
						    &enum_and_int_p);
  जइ (!comptypes_result)
    {
      जइ (वृक्षः_CODE (olddecl) == FUNCTION_DECL
	  && fndecl_built_in_p (olddecl, BUILT_IN_NORMAL)
	  && !C_DECL_DECLARED_BUILTIN (olddecl))
	{
	  /* Accept "harmless" mismatches in function types such
	     as missing qualifiers or int vs long when they're the same
	     size.  However, diagnose return and argument types that are
	     incompatible according to language rules.  */
	  वृक्षः mismatch_expect;
	  unsigned mismatch_argno;

	  वृक्षः trytype = match_builtin_function_types (newtype, oldtype,
						       &mismatch_expect,
						       &mismatch_argno);

	  जइ (trytype && comptypes (newtype, trytype))
	    *oldtypep = oldtype = trytype;
	  अण्णहा
	    {
	      /* If types don't match for a built-in, throw away the
		 built-in.  No point in calling locate_old_decl here, it
		 won't print anything.  */
	      ध्रुव वर्ण *header = header_for_builtin_fn (olddecl);
	      location_t loc = DECL_SOURCE_LOCATION (newdecl);
	      जइ (warning_at (loc, OPT_Wbuiltin_declaration_mismatch,
			      "conflicting types for built-in function %q+D; "
			      "expected %qT",
			      newdecl, oldtype)
		  && header)
		{
		  /* Suggest the right header to include as the preferred
		     solution rather than the spelling of the declaration.  */
		  rich_location richloc (पङ्क्तिः_table, loc);
		  maybe_add_include_fixit (&richloc, header, सच्च);
		  inform (&richloc,
			  "%qD is declared in header %qs", olddecl, header);
		}
	      प्रत्यागम मिच्छ;
	    }

	  जइ (mismatch_expect && extra_warnings)
	    {
	      location_t newloc = DECL_SOURCE_LOCATION (newdecl);
	      तार्किक warned = मिच्छ;
	      जइ (mismatch_argno)
		warned = warning_at (newloc, OPT_Wbuiltin_declaration_mismatch,
				     "mismatch in argument %u type of built-in "
				     "function %qD; expected %qT",
				     mismatch_argno, newdecl, mismatch_expect);
	      अण्णहा
		warned = warning_at (newloc, OPT_Wbuiltin_declaration_mismatch,
				     "mismatch in return type of built-in "
				     "function %qD; expected %qT",
				     newdecl, mismatch_expect);
	      ध्रुव वर्ण *header = header_for_builtin_fn (olddecl);
	      जइ (warned && header)
		{
		  rich_location richloc (पङ्क्तिः_table, newloc);
		  maybe_add_include_fixit (&richloc, header, सच्च);
		  inform (&richloc,
			  "%qD is declared in header %qs", olddecl, header);
		}
	    }
	}
      अण्णहा जइ (वृक्षः_CODE (olddecl) == FUNCTION_DECL
	       && DECL_IS_UNDECLARED_BUILTIN (olddecl))
	{
	  /* A conflicting function declaration for a predeclared
	     function that isn't actually built in.  Objective C uses
	     these.  The new declaration silently overrides everything
	     but the volatility (i.e. noreturn) indication.  See also
	     below.  FIXME: Make Objective C use normal builtins.  */
	  वृक्षः_THIS_VOLATILE (newdecl) |= वृक्षः_THIS_VOLATILE (olddecl);
	  प्रत्यागम मिच्छ;
	}
      /* Permit void foo (...) to match int foo (...) if the latter is
	 the definition and implicit int was used.  See
	 c-torture/compile/920625-2.c.  */
      अण्णहा जइ (वृक्षः_CODE (newdecl) == FUNCTION_DECL && DECL_INITIAL (newdecl)
	       && TYPE_MAIN_VARIANT (वृक्षः_TYPE (oldtype)) == void_type_ग्रन्थिः
	       && TYPE_MAIN_VARIANT (वृक्षः_TYPE (newtype)) == integer_type_ग्रन्थिः
	       && C_FUNCTION_IMPLICIT_INT (newdecl) && !DECL_INITIAL (olddecl))
	{
	  pedwarned = pedwarn (निवेशः_location, 0,
			       "conflicting types for %q+D", newdecl);
	  /* Make sure we keep void as the return type.  */
	  वृक्षः_TYPE (newdecl) = *newtypep = newtype = oldtype;
	  C_FUNCTION_IMPLICIT_INT (newdecl) = 0;
	}
      /* Permit void foo (...) to match an earlier call to foo (...) with
	 no declared type (thus, implicitly int).  */
      अण्णहा जइ (वृक्षः_CODE (newdecl) == FUNCTION_DECL
	       && TYPE_MAIN_VARIANT (वृक्षः_TYPE (newtype)) == void_type_ग्रन्थिः
	       && TYPE_MAIN_VARIANT (वृक्षः_TYPE (oldtype)) == integer_type_ग्रन्थिः
	       && C_DECL_IMPLICIT (olddecl) && !DECL_INITIAL (olddecl))
	{
	  pedwarned = pedwarn (निवेशः_location, 0,
			       "conflicting types for %q+D; have %qT",
			       newdecl, newtype);
	  /* Make sure we keep void as the return type.  */
	  वृक्षः_TYPE (olddecl) = *oldtypep = oldtype = newtype;
	}
      अण्णहा
	{
	  पूर्णाङ्क new_quals = TYPE_QUALS (newtype);
	  पूर्णाङ्क old_quals = TYPE_QUALS (oldtype);

	  जइ (new_quals != old_quals)
	    {
	      addr_space_t new_addr = DECODE_QUAL_ADDR_SPACE (new_quals);
	      addr_space_t old_addr = DECODE_QUAL_ADDR_SPACE (old_quals);
	      जइ (new_addr != old_addr)
		{
		  जइ (ADDR_SPACE_GENERIC_P (new_addr))
		    error ("conflicting named address spaces (generic vs %s) "
			   "for %q+D",
			   c_addr_space_name (old_addr), newdecl);
		  अण्णहा जइ (ADDR_SPACE_GENERIC_P (old_addr))
		    error ("conflicting named address spaces (%s vs generic) "
			   "for %q+D",
			   c_addr_space_name (new_addr), newdecl);
		  अण्णहा
		    error ("conflicting named address spaces (%s vs %s) "
			   "for %q+D",
			   c_addr_space_name (new_addr),
			   c_addr_space_name (old_addr),
			   newdecl);
		}

	      जइ (CLEAR_QUAL_ADDR_SPACE (new_quals)
		  != CLEAR_QUAL_ADDR_SPACE (old_quals))
		error ("conflicting type qualifiers for %q+D", newdecl);
	    }
	  अण्णहा
	    {
	      जइ (वृक्षः_CODE (olddecl) == FUNCTION_DECL)
		{
		  वृक्षः attrs = TYPE_ATTRIBUTES (वृक्षः_TYPE (olddecl));
		  जइ (attrs && !TYPE_ATTRIBUTES (वृक्षः_TYPE (newdecl)))
		    {
		      /* Similar to the C++ front-end, for FUNCTION_DECL,
			 if OLDDECL has attributes and NEWDECL doesn't,
			 try the type with OLDDECL attributes.  */
		      वृक्षः rettype = वृक्षः_TYPE (newtype);
		      वृक्षः tryargs = TYPE_ARG_TYPES (newtype);
		      वृक्षः trytype = c_build_function_type (rettype,
							    tryargs);
		      trytype = c_build_type_attribute_variant (trytype,
								attrs);
		      जइ (comptypes (oldtype, trytype))
			{
			  *newtypep = newtype = trytype;
			  comptypes_result = सच्च;
			}
		    }
		}

	      जइ (!comptypes_result)
		error ("conflicting types for %q+D; have %qT", newdecl,
		       newtype);
	    }
	  जइ (!comptypes_result)
	    {
	      diagnose_arglist_conflict (newdecl, olddecl, newtype,
					 oldtype);
	      locate_old_decl (olddecl);
	      प्रत्यागम मिच्छ;
	    }
	}
    }
  /* Warn about enum/integer type mismatches.  They are compatible types
     (C23 6.7.2.2/5), but may pose portability problems.  */
  अण्णहा जइ (enum_and_int_p
	   && वृक्षः_CODE (newdecl) != TYPE_DECL
	   /* Don't warn about acc_on_device built-in redeclaration,
	      the built-in is declared with int rather than enum because
	      the enum isn't intrinsic.  */
	   && !(वृक्षः_CODE (olddecl) == FUNCTION_DECL
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
  जइ (वृक्षः_CODE (newdecl) == TYPE_DECL)
    {
      जइ (!comptypes_same_p (oldtype, newtype))
	{
	  error ("redefinition of typedef %q+D with different type", newdecl);
	  locate_old_decl (olddecl);
	  प्रत्यागम मिच्छ;
	}

      जइ (DECL_IN_SYSTEM_HEADER (newdecl)
	  || DECL_IN_SYSTEM_HEADER (olddecl)
	  || warning_suppressed_p (newdecl, OPT_Wpedantic)
	  || warning_suppressed_p (olddecl, OPT_Wpedantic))
	प्रत्यागम सच्च;  /* Allow OLDDECL to continue in use.  */

      जइ (c_type_variably_modified_p (newtype))
	{
	  error ("redefinition of typedef %q+D with variably modified type",
		 newdecl);
	  locate_old_decl (olddecl);
	}
      अण्णहा जइ (pedwarn_c99 (निवेशः_location, OPT_Wpedantic,
			    "redefinition of typedef %q+D", newdecl))
	locate_old_decl (olddecl);

      प्रत्यागम सच्च;
    }

  /* Function declarations can either be 'static' or 'extern' (no
     qualifier is equivalent to 'extern' - C99 6.2.2p5) and therefore
     can never conflict with each other on account of linkage
     (6.2.2p4).  Multiple definitions are not allowed (6.9p3,5) but
     gnu89 mode permits two definitions if one is 'extern inline' and
     one is not.  The non- extern-inline definition supersedes the
     extern-inline definition.  */

  अण्णहा जइ (वृक्षः_CODE (newdecl) == FUNCTION_DECL)
    {
      /* If you declare a built-in function name as static, or
	 define the built-in with an old-style definition (so we
	 can't validate the argument list) the built-in definition is
	 overridden, but optionally warn this was a bad choice of name.  */
      जइ (fndecl_built_in_p (olddecl)
	  && !C_DECL_DECLARED_BUILTIN (olddecl))
	{
	  जइ (!वृक्षः_PUBLIC (newdecl)
	      || (DECL_INITIAL (newdecl)
		  && !prototype_p (वृक्षः_TYPE (newdecl))))
	    {
	      warning_at (DECL_SOURCE_LOCATION (newdecl),
			  OPT_Wshadow, "declaration of %qD shadows "
			  "a built-in function", newdecl);
	      /* Discard the old built-in function.  */
	      प्रत्यागम मिच्छ;
	    }

	  जइ (!prototype_p (वृक्षः_TYPE (newdecl)))
	    {
	      /* Set for built-ins that take no arguments.  */
	      तार्किक func_void_args = मिच्छ;
	      जइ (वृक्षः at = TYPE_ARG_TYPES (oldtype))
		func_void_args = VOID_TYPE_P (वृक्षः_मानम् (at));

	      जइ (extra_warnings && !func_void_args)
		warning_at (DECL_SOURCE_LOCATION (newdecl),
			    OPT_Wbuiltin_declaration_mismatch,
			    "declaration of built-in function %qD without "
			    "a prototype; expected %qT",
			    newdecl, वृक्षः_TYPE (olddecl));
	    }
	}

      जइ (DECL_INITIAL (newdecl))
	{
	  जइ (DECL_INITIAL (olddecl))
	    {
	      /* If the new declaration isn't overriding an extern inline
		 reject the new decl. In c99, no overriding is allowed
		 in the same translation unit.  */
	      जइ (!DECL_EXTERN_INLINE (olddecl)
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
		  प्रत्यागम मिच्छ;
		}
	    }
	}
      /* If we have a prototype after an old-style function definition,
	 the argument types must be checked specially.  */
      अण्णहा जइ (DECL_INITIAL (olddecl)
	       && !prototype_p (oldtype) && prototype_p (newtype)
	       && TYPE_ACTUAL_ARG_TYPES (oldtype))
	{
	  auto_diagnostic_group d;
	  जइ (!validate_proto_after_old_defn (newdecl, newtype, oldtype))
	    {
	      locate_old_decl (olddecl);
	      प्रत्यागम मिच्छ;
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
      जइ (वृक्षः_PUBLIC (olddecl) && !वृक्षः_PUBLIC (newdecl))
	{
	  /* Two exceptions to the rule.  If olddecl is an extern
	     inline, or a predeclared function that isn't actually
	     built in, newdecl silently overrides olddecl.  The latter
	     occur only in Objective C; see also above.  (FIXME: Make
	     Objective C use normal builtins.)  */
	  जइ (!DECL_IS_UNDECLARED_BUILTIN (olddecl)
	      && !DECL_EXTERN_INLINE (olddecl))
	    {
	      auto_diagnostic_group d;
	      error ("static declaration of %q+D follows "
		     "non-static declaration", newdecl);
	      locate_old_decl (olddecl);
	    }
	  प्रत्यागम मिच्छ;
	}
      अण्णहा जइ (वृक्षः_PUBLIC (newdecl) && !वृक्षः_PUBLIC (olddecl))
	{
	  जइ (DECL_CONTEXT (olddecl))
	    {
	      auto_diagnostic_group d;
	      error ("non-static declaration of %q+D follows "
		     "static declaration", newdecl);
	      locate_old_decl (olddecl);
	      प्रत्यागम मिच्छ;
	    }
	  अण्णहा जइ (warn_traditional)
	    {
	      warned |= warning (OPT_Wtraditional,
				 "non-static declaration of %q+D "
				 "follows static declaration", newdecl);
	    }
	}

      /* Make sure gnu_inline attribute is either not present, or
	 present on all inline decls.  */
      जइ (DECL_DECLARED_INLINE_P (olddecl)
	  && DECL_DECLARED_INLINE_P (newdecl))
	{
	  तार्किक newa = lookup_attribute ("gnu_inline",
					DECL_ATTRIBUTES (newdecl)) != रिक्त;
	  तार्किक olda = lookup_attribute ("gnu_inline",
					DECL_ATTRIBUTES (olddecl)) != रिक्त;
	  जइ (newa != olda)
	    {
	      auto_diagnostic_group d;
	      error_at (निवेशः_location, "%<gnu_inline%> attribute present on %q+D",
			newa ? newdecl : olddecl);
	      error_at (DECL_SOURCE_LOCATION (newa ? olddecl : newdecl),
			"but not here");
	    }
	}
      /* Check if these are unmergeable overlapping FMV declarations.  */
      जइ (!TARGET_HAS_FMV_TARGET_ATTRIBUTE
	  && diagnose_versioned_decls (olddecl, newdecl))
	प्रत्यागम मिच्छ;
    }
  अण्णहा जइ (VAR_P (newdecl))
    {
      /* Only variables can be thread-local, and all declarations must
	 agree on this property.  */
      जइ (C_DECL_THREADPRIVATE_P (olddecl) && !DECL_THREAD_LOCAL_P (newdecl))
	{
	  /* Nothing to check.  Since OLDDECL is marked threadprivate
	     and NEWDECL does not have a thread-local attribute, we
	     will merge the threadprivate attribute into NEWDECL.  */
	  ;
	}
      अण्णहा जइ (DECL_THREAD_LOCAL_P (newdecl) != DECL_THREAD_LOCAL_P (olddecl))
	{
	  auto_diagnostic_group d;
	  जइ (DECL_THREAD_LOCAL_P (newdecl))
	    error ("thread-local declaration of %q+D follows "
		   "non-thread-local declaration", newdecl);
	  अण्णहा
	    error ("non-thread-local declaration of %q+D follows "
		   "thread-local declaration", newdecl);

	  locate_old_decl (olddecl);
	  प्रत्यागम मिच्छ;
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
      जइ ((DECL_INITIAL (newdecl) && DECL_INITIAL (olddecl))
	  || (flag_isoc23
	      && DECL_THREAD_LOCAL_P (newdecl)
	      && !DECL_EXTERNAL (newdecl)
	      && !DECL_EXTERNAL (olddecl)))
	{
	  auto_diagnostic_group d;
	  error ("redefinition of %q+D", newdecl);
	  locate_old_decl (olddecl);
	  प्रत्यागम मिच्छ;
	}

      /* Objects declared at file scope: if the first declaration had
	 external linkage (even if it was an external reference) the
	 second must have external linkage as well, or the behavior is
	 undefined.  If the first declaration had internal linkage, then
	 the second must too, or else be an external reference (in which
	 case the composite declaration still has internal linkage).
	 As for function declarations, we warn about the static-then-
	 extern case only for -Wtraditional.  See generally 6.2.2p3-5,7.  */
      जइ (DECL_FILE_SCOPE_P (newdecl)
	  && वृक्षः_PUBLIC (newdecl) != वृक्षः_PUBLIC (olddecl))
	{
	  जइ (DECL_EXTERNAL (newdecl))
	    {
	      जइ (!DECL_FILE_SCOPE_P (olddecl))
		{
		  auto_diagnostic_group d;
		  error ("extern declaration of %q+D follows "
			 "declaration with no linkage", newdecl);
		  locate_old_decl (olddecl);
		  प्रत्यागम मिच्छ;
		}
	      अण्णहा जइ (warn_traditional)
		{
		  warned |= warning (OPT_Wtraditional,
				     "non-static declaration of %q+D "
				     "follows static declaration", newdecl);
		}
	    }
	  अण्णहा
	    {
	      auto_diagnostic_group d;
	      जइ (वृक्षः_PUBLIC (newdecl))
		error ("non-static declaration of %q+D follows "
		       "static declaration", newdecl);
	      अण्णहा
		error ("static declaration of %q+D follows "
		       "non-static declaration", newdecl);

	      locate_old_decl (olddecl);
	      प्रत्यागम मिच्छ;
	    }
	}
      /* Two objects with the same name declared at the same block
	 scope must both be external references (6.7p3).  */
      अण्णहा जइ (!DECL_FILE_SCOPE_P (newdecl))
	{
	  जइ (DECL_EXTERNAL (newdecl))
	    {
	      /* Extern with initializer at block scope, which will
		 already have received an error.  */
	    }
	  अण्णहा जइ (DECL_EXTERNAL (olddecl))
	    {
	      auto_diagnostic_group d;
	      error ("declaration of %q+D with no linkage follows "
		     "extern declaration", newdecl);
	      locate_old_decl (olddecl);
	    }
	  अण्णहा
	    {
	      auto_diagnostic_group d;
	      error ("redeclaration of %q+D with no linkage", newdecl);
	      locate_old_decl (olddecl);
	    }

	  प्रत्यागम मिच्छ;
	}

      /* C++ does not permit a decl to appear multiple times at file
	 scope.  */
      जइ (warn_cxx_compat
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
  जइ (CODE_CONTAINS_STRUCT (वृक्षः_CODE (newdecl), TS_DECL_WITH_VIS)
      && DECL_VISIBILITY_SPECIFIED (newdecl) && DECL_VISIBILITY_SPECIFIED (olddecl)
      && DECL_VISIBILITY (newdecl) != DECL_VISIBILITY (olddecl))
    {
      warned |= warning (0, "redeclaration of %q+D with different visibility "
			 "(old visibility preserved)", newdecl);
    }

  जइ (वृक्षः_CODE (newdecl) == FUNCTION_DECL)
    warned |= diagnose_mismatched_attributes (olddecl, newdecl);
  अण्णहा /* PARM_DECL, VAR_DECL */
    {
      /* Redeclaration of a parameter is a constraint violation (this is
	 not explicitly stated, but follows from C99 6.7p3 [no more than
	 one declaration of the same identifier with no linkage in the
	 same scope, except type tags] and 6.2.2p6 [parameters have no
	 linkage]).  We must check for a forward parameter declaration,
	 indicated by TREE_ASM_WRITTEN on the old declaration - this is
	 an extension, the mandatory diagnostic for which is handled by
	 mark_forward_parm_decls.  */

      जइ (वृक्षः_CODE (newdecl) == PARM_DECL
	  && (!वृक्षः_ASM_WRITTEN (olddecl) || वृक्षः_ASM_WRITTEN (newdecl)))
	{
	  auto_diagnostic_group d;
	  error ("redefinition of parameter %q+D", newdecl);
	  locate_old_decl (olddecl);
	  प्रत्यागम मिच्छ;
	}
    }

  /* Optional warning for completely redundant decls.  */
  जइ (!warned && !pedwarned
      && warn_redundant_decls
      /* Don't warn about a function declaration followed by a
	 definition.  */
      && !(वृक्षः_CODE (newdecl) == FUNCTION_DECL
	   && DECL_INITIAL (newdecl) && !DECL_INITIAL (olddecl))
      /* Don't warn about redundant redeclarations of builtins.  */
      && !(वृक्षः_CODE (newdecl) == FUNCTION_DECL
	   && !fndecl_built_in_p (newdecl)
	   && fndecl_built_in_p (olddecl)
	   && !C_DECL_DECLARED_BUILTIN (olddecl))
      /* Don't warn about an extern followed by a definition.  */
      && !(DECL_EXTERNAL (olddecl) && !DECL_EXTERNAL (newdecl))
      /* Don't warn about forward parameter decls.  */
      && !(वृक्षः_CODE (newdecl) == PARM_DECL
	   && वृक्षः_ASM_WRITTEN (olddecl) && !वृक्षः_ASM_WRITTEN (newdecl))
      /* Don't warn about a variable definition following a declaration.  */
      && !(VAR_P (newdecl)
	   && DECL_INITIAL (newdecl) && !DECL_INITIAL (olddecl)))
    {
      warned = warning (OPT_Wredundant_decls, "redundant redeclaration of %q+D",
			newdecl);
    }

  /* Report location of previous decl/defn.  */
  जइ (warned || pedwarned)
    locate_old_decl (olddecl);

#undef DECL_EXTERN_INLINE

  प्रत्यागम retval;
}

/* Subroutine of duplicate_decls.  NEWDECL has been found to be
   consistent with OLDDECL, but carries new information.  Merge the
   new information into OLDDECL.  This function issues no
   diagnostics.  */

स्थिर शून्य
merge_decls (वृक्षः newdecl, वृक्षः olddecl, वृक्षः newtype, वृक्षः oldtype)
{
  तार्किक new_is_definition = (वृक्षः_CODE (newdecl) == FUNCTION_DECL
			    && DECL_INITIAL (newdecl) != NULL_वृक्षः);
  तार्किक new_is_prototype = (वृक्षः_CODE (newdecl) == FUNCTION_DECL
			   && prototype_p (वृक्षः_TYPE (newdecl)));
  तार्किक old_is_prototype = (वृक्षः_CODE (olddecl) == FUNCTION_DECL
			   && prototype_p (वृक्षः_TYPE (olddecl)));

  /* For real parm decl following a forward decl, rechain the old decl
     in its new location and clear TREE_ASM_WRITTEN (it's not a
     forward decl anymore).  */
  जइ (वृक्षः_CODE (newdecl) == PARM_DECL
      && वृक्षः_ASM_WRITTEN (olddecl) && !वृक्षः_ASM_WRITTEN (newdecl))
    {
      संरचना c_binding *b, **here;

      प्रति (here = &current_scope->bindings; *here; here = &(*here)->prev)
	जइ ((*here)->decl == olddecl)
	  गच्छ found;
      gcc_unreachable ();

    found:
      b = *here;
      *here = b->prev;
      b->prev = current_scope->bindings;
      current_scope->bindings = b;

      वृक्षः_ASM_WRITTEN (olddecl) = 0;
    }

  DECL_ATTRIBUTES (newdecl)
    = targetm.merge_decl_attributes (olddecl, newdecl);

  /* For typedefs use the old type, as the new type's DECL_NAME points
     at newdecl, which will be ggc_freed.  */
  जइ (वृक्षः_CODE (newdecl) == TYPE_DECL)
    {
      /* But NEWTYPE might have an attribute, honor that.  */
      वृक्षः tem = newtype;
      newtype = oldtype;

      जइ (TYPE_USER_ALIGN (tem))
	{
	  जइ (TYPE_ALIGN (tem) > TYPE_ALIGN (newtype))
	    SET_TYPE_ALIGN (newtype, TYPE_ALIGN (tem));
	  TYPE_USER_ALIGN (newtype) = सच्च;
	}

      /* And remove the new type from the variants list.  */
      जइ (TYPE_NAME (वृक्षः_TYPE (newdecl)) == newdecl)
	{
	  वृक्षः remove = वृक्षः_TYPE (newdecl);
	  जइ (TYPE_MAIN_VARIANT (remove) == remove)
	    {
	      gcc_assert (TYPE_NEXT_VARIANT (remove) == NULL_वृक्षः);
	      /* If remove is the main variant, no need to remove that
		 from the list.  One of the DECL_ORIGINAL_TYPE
		 variants, e.g. created for aligned attribute, might still
		 refer to the newdecl TYPE_DECL though, so remove that one
		 in that case.  */
	      जइ (DECL_ORIGINAL_TYPE (newdecl)
		  && DECL_ORIGINAL_TYPE (newdecl) != remove)
		प्रति (वृक्षः t = TYPE_MAIN_VARIANT (DECL_ORIGINAL_TYPE (newdecl));
		     t; t = TYPE_MAIN_VARIANT (t))
		  जइ (TYPE_NAME (TYPE_NEXT_VARIANT (t)) == newdecl)
		    {
		      TYPE_NEXT_VARIANT (t)
			= TYPE_NEXT_VARIANT (TYPE_NEXT_VARIANT (t));
		      भङ्ग;
		    }
	    }
	  अण्णहा
	    प्रति (वृक्षः t = TYPE_MAIN_VARIANT (remove); ;
		 t = TYPE_NEXT_VARIANT (t))
	      जइ (TYPE_NEXT_VARIANT (t) == remove)
		{
		  TYPE_NEXT_VARIANT (t) = TYPE_NEXT_VARIANT (remove);
		  भङ्ग;
		}
	}

      /* Make sure we refer to the same type as the olddecl.  */
      DECL_ORIGINAL_TYPE (newdecl) = DECL_ORIGINAL_TYPE (olddecl);
    }

  /* Merge the data types specified in the two decls.  */
  वृक्षः_TYPE (newdecl)
    = वृक्षः_TYPE (olddecl)
    = composite_type (newtype, oldtype);

  /* Lay the type out, unless already done.  */
  जइ (!comptypes (oldtype, वृक्षः_TYPE (newdecl)))
    {
      जइ (वृक्षः_TYPE (newdecl) != error_mark_ग्रन्थिः)
	layout_type (वृक्षः_TYPE (newdecl));
      जइ (वृक्षः_CODE (newdecl) != FUNCTION_DECL
	  && वृक्षः_CODE (newdecl) != TYPE_DECL
	  && वृक्षः_CODE (newdecl) != CONST_DECL)
	layout_decl (newdecl, 0);
    }
  अण्णहा
    {
      /* Since the type is OLDDECL's, make OLDDECL's size go with.  */
      DECL_SIZE (newdecl) = DECL_SIZE (olddecl);
      DECL_SIZE_UNIT (newdecl) = DECL_SIZE_UNIT (olddecl);
      SET_DECL_MODE (newdecl, DECL_MODE (olddecl));
      जइ (DECL_ALIGN (olddecl) > DECL_ALIGN (newdecl))
	{
	  SET_DECL_ALIGN (newdecl, DECL_ALIGN (olddecl));
	  DECL_USER_ALIGN (newdecl) |= DECL_USER_ALIGN (olddecl);
	}
      अण्णहा जइ (DECL_ALIGN (olddecl) == DECL_ALIGN (newdecl)
	       && DECL_USER_ALIGN (olddecl) != DECL_USER_ALIGN (newdecl))
	DECL_USER_ALIGN (newdecl) = 1;
      जइ (DECL_WARN_IF_NOT_ALIGN (olddecl)
	  > DECL_WARN_IF_NOT_ALIGN (newdecl))
	SET_DECL_WARN_IF_NOT_ALIGN (newdecl,
				    DECL_WARN_IF_NOT_ALIGN (olddecl));
    }

  /* Keep the old rtl since we can safely use it.  */
  जइ (HAS_RTL_P (olddecl))
    COPY_DECL_RTL (olddecl, newdecl);

  /* Merge the type qualifiers.  */
  जइ (वृक्षः_READONLY (newdecl))
    वृक्षः_READONLY (olddecl) = 1;

  जइ (वृक्षः_THIS_VOLATILE (newdecl))
    वृक्षः_THIS_VOLATILE (olddecl) = 1;

  /* Merge deprecatedness.  */
  जइ (वृक्षः_DEPRECATED (newdecl))
    वृक्षः_DEPRECATED (olddecl) = 1;

  /* Merge unavailability.  */
  जइ (वृक्षः_UNAVAILABLE (newdecl))
    वृक्षः_UNAVAILABLE (olddecl) = 1;

  /* If a decl is in a system header and the other isn't, keep the one on the
     system header. Otherwise, keep source location of definition rather than
     declaration and of prototype rather than non-prototype unless that
     prototype is built-in.  */
  जइ (HAS_DECL_ASSEMBLER_NAME_P (olddecl)
      && DECL_IN_SYSTEM_HEADER (olddecl)
      && !DECL_IN_SYSTEM_HEADER (newdecl) )
    DECL_SOURCE_LOCATION (newdecl) = DECL_SOURCE_LOCATION (olddecl);
  अण्णहा जइ (HAS_DECL_ASSEMBLER_NAME_P (olddecl)
	   && DECL_IN_SYSTEM_HEADER (newdecl)
	   && !DECL_IN_SYSTEM_HEADER (olddecl))
    DECL_SOURCE_LOCATION (olddecl) = DECL_SOURCE_LOCATION (newdecl);
  अण्णहा जइ ((DECL_INITIAL (newdecl) == NULL_वृक्षः
	    && DECL_INITIAL (olddecl) != NULL_वृक्षः)
	   || (old_is_prototype && !new_is_prototype
	       && !C_DECL_BUILTIN_PROTOTYPE (olddecl)))
    DECL_SOURCE_LOCATION (newdecl) = DECL_SOURCE_LOCATION (olddecl);

  /* Merge the initialization information.  */
   जइ (DECL_INITIAL (newdecl) == NULL_वृक्षः)
    DECL_INITIAL (newdecl) = DECL_INITIAL (olddecl);

  /* Merge 'constexpr' information.  */
  जइ (VAR_P (olddecl) && VAR_P (newdecl))
    {
      जइ (C_DECL_DECLARED_CONSTEXPR (olddecl))
	C_DECL_DECLARED_CONSTEXPR (newdecl) = 1;
      अण्णहा जइ (C_DECL_DECLARED_CONSTEXPR (newdecl))
	C_DECL_DECLARED_CONSTEXPR (olddecl) = 1;
    }

  /* Merge the threadprivate attribute.  */
  जइ (VAR_P (olddecl) && C_DECL_THREADPRIVATE_P (olddecl))
    C_DECL_THREADPRIVATE_P (newdecl) = 1;

  जइ (HAS_DECL_ASSEMBLER_NAME_P (olddecl))
    {
      /* Copy the assembler name.
	 Currently, it can only be defined in the prototype.  */
      COPY_DECL_ASSEMBLER_NAME (olddecl, newdecl);

      /* Use visibility of whichever declaration had it specified */
      जइ (DECL_VISIBILITY_SPECIFIED (olddecl))
	{
	  DECL_VISIBILITY (newdecl) = DECL_VISIBILITY (olddecl);
	  DECL_VISIBILITY_SPECIFIED (newdecl) = 1;
	}

      जइ (वृक्षः_CODE (newdecl) == FUNCTION_DECL)
	{
	  DECL_STATIC_CONSTRUCTOR(newdecl) |= DECL_STATIC_CONSTRUCTOR(olddecl);
	  DECL_STATIC_DESTRUCTOR (newdecl) |= DECL_STATIC_DESTRUCTOR (olddecl);
	  DECL_NO_LIMIT_राशिः (newdecl) |= DECL_NO_LIMIT_राशिः (olddecl);
	  DECL_NO_INSTRUMENT_FUNCTION_ENTRY_EXIT (newdecl)
	    |= DECL_NO_INSTRUMENT_FUNCTION_ENTRY_EXIT (olddecl);
	  वृक्षः_THIS_VOLATILE (newdecl) |= वृक्षः_THIS_VOLATILE (olddecl);
	  DECL_IS_MALLOC (newdecl) |= DECL_IS_MALLOC (olddecl);
	  जइ (DECL_IS_OPERATOR_NEW_P (olddecl))
	    DECL_SET_IS_OPERATOR_NEW (newdecl, सच्च);
	  जइ (DECL_IS_OPERATOR_DELETE_P (olddecl))
	    DECL_SET_IS_OPERATOR_DELETE (newdecl, सच्च);
	  वृक्षः_READONLY (newdecl) |= वृक्षः_READONLY (olddecl);
	  DECL_PURE_P (newdecl) |= DECL_PURE_P (olddecl);
	  DECL_IS_NOVOPS (newdecl) |= DECL_IS_NOVOPS (olddecl);
	}

      /* Merge the storage class information.  */
      merge_weak (newdecl, olddecl);

      /* For functions, static overrides non-static.  */
      जइ (वृक्षः_CODE (newdecl) == FUNCTION_DECL)
	{
	  वृक्षः_PUBLIC (newdecl) &= वृक्षः_PUBLIC (olddecl);
	  /* This is since we don't automatically
	     copy the attributes of NEWDECL into OLDDECL.  */
	  वृक्षः_PUBLIC (olddecl) = वृक्षः_PUBLIC (newdecl);
	  /* If this clears `static', clear it in the identifier too.  */
	  जइ (!वृक्षः_PUBLIC (olddecl))
	    वृक्षः_PUBLIC (DECL_NAME (olddecl)) = 0;
	}
    }

  /* In c99, 'extern' declaration before (or after) 'inline' means this
     function is not DECL_EXTERNAL, unless 'gnu_inline' attribute
     is present.  */
  जइ (वृक्षः_CODE (newdecl) == FUNCTION_DECL
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
  जइ (new_is_definition
      && (DECL_DECLARED_INLINE_P (newdecl)
	  || DECL_DECLARED_INLINE_P (olddecl))
      && !वृक्षः_PUBLIC (olddecl))
    DECL_EXTERNAL (newdecl) = 0;

  जइ (DECL_EXTERNAL (newdecl))
    {
      वृक्षः_STATIC (newdecl) = वृक्षः_STATIC (olddecl);
      DECL_EXTERNAL (newdecl) = DECL_EXTERNAL (olddecl);

      /* An extern decl does not override previous storage class.  */
      वृक्षः_PUBLIC (newdecl) = वृक्षः_PUBLIC (olddecl);
      जइ (!DECL_EXTERNAL (newdecl))
	{
	  DECL_CONTEXT (newdecl) = DECL_CONTEXT (olddecl);
	  DECL_COMMON (newdecl) = DECL_COMMON (olddecl);
	}
    }
  अण्णहा
    {
      वृक्षः_STATIC (olddecl) = वृक्षः_STATIC (newdecl);
      वृक्षः_PUBLIC (olddecl) = वृक्षः_PUBLIC (newdecl);
    }

  जइ (वृक्षः_CODE (newdecl) == FUNCTION_DECL)
    {
      जइ (DECL_FUNCTION_VERSIONED (olddecl)
	  || DECL_FUNCTION_VERSIONED (newdecl))
	{
	  maybe_mark_function_versioned (olddecl);
	  maybe_mark_function_versioned (newdecl);
	}
      /* If we're redefining a function previously defined as extern
	 inline, make sure we emit debug info for the inline before we
	 throw it away, in case it was inlined into a function that
	 hasn't been written out yet.  */
      जइ (new_is_definition && DECL_INITIAL (olddecl))
	/* The new defn must not be inline.  */
	DECL_UNINLINABLE (newdecl) = 1;
      अण्णहा
	{
	  /* If either decl says `inline', this fn is inline, unless
	     its definition was passed already.  */
	  जइ (DECL_DECLARED_INLINE_P (newdecl)
	      || DECL_DECLARED_INLINE_P (olddecl))
	    DECL_DECLARED_INLINE_P (newdecl) = 1;

	  DECL_UNINLINABLE (newdecl) = DECL_UNINLINABLE (olddecl)
	    = (DECL_UNINLINABLE (newdecl) || DECL_UNINLINABLE (olddecl));

	  DECL_DISREGARD_INLINE_LIMITS (newdecl)
	    = DECL_DISREGARD_INLINE_LIMITS (olddecl)
	    = (DECL_DISREGARD_INLINE_LIMITS (newdecl)
	       || DECL_DISREGARD_INLINE_LIMITS (olddecl));
	}

      जइ (fndecl_built_in_p (olddecl))
	{
	  /* If redeclaring a builtin function, it stays built in.
	     But it gets tagged as having been declared.  */
	  copy_decl_built_in_function (newdecl, olddecl);
	  C_DECL_DECLARED_BUILTIN (newdecl) = 1;
	  जइ (new_is_prototype)
	    {
	      C_DECL_BUILTIN_PROTOTYPE (newdecl) = 0;
	      जइ (DECL_BUILT_IN_CLASS (newdecl) == BUILT_IN_NORMAL)
		{
		  गणना built_in_function fncode = DECL_FUNCTION_CODE (newdecl);
		  विकल्प (fncode)
		    {
		      /* If a compatible prototype of these builtin functions
			 is seen, assume the runtime implements it with the
			 expected semantics.  */
		    पक्ष BUILT_IN_STPCPY:
		      जइ (builtin_decl_explicit_p (fncode))
			set_builtin_decl_implicit_p (fncode, सच्च);
		      भङ्ग;
		    स्वभाव:
		      जइ (builtin_decl_explicit_p (fncode))
			set_builtin_decl_declared_p (fncode, सच्च);
		      भङ्ग;
		    }

		  copy_attributes_to_builtin (newdecl);
		}
	    }
	  अण्णहा
	    C_DECL_BUILTIN_PROTOTYPE (newdecl)
	      = C_DECL_BUILTIN_PROTOTYPE (olddecl);
	}

      /* Preserve function specific target and optimization options */
      जइ (DECL_FUNCTION_SPECIFIC_TARGET (olddecl)
	  && !DECL_FUNCTION_SPECIFIC_TARGET (newdecl))
	DECL_FUNCTION_SPECIFIC_TARGET (newdecl)
	  = DECL_FUNCTION_SPECIFIC_TARGET (olddecl);

      जइ (DECL_FUNCTION_SPECIFIC_OPTIMIZATION (olddecl)
	  && !DECL_FUNCTION_SPECIFIC_OPTIMIZATION (newdecl))
	DECL_FUNCTION_SPECIFIC_OPTIMIZATION (newdecl)
	  = DECL_FUNCTION_SPECIFIC_OPTIMIZATION (olddecl);

      /* Also preserve various other info from the definition.  */
      जइ (!new_is_definition)
	{
	  वृक्षः t;
	  DECL_RESULT (newdecl) = DECL_RESULT (olddecl);
	  DECL_INITIAL (newdecl) = DECL_INITIAL (olddecl);
	  DECL_STRUCT_FUNCTION (newdecl) = DECL_STRUCT_FUNCTION (olddecl);
	  DECL_SAVED_वृक्षः (newdecl) = DECL_SAVED_वृक्षः (olddecl);
	  DECL_ARGUMENTS (newdecl) = copy_list (DECL_ARGUMENTS (olddecl));
	  प्रति (t = DECL_ARGUMENTS (newdecl); t ; t = DECL_CHAIN (t))
	    DECL_CONTEXT (t) = newdecl;

	  /* See if we've got a function to instantiate from.  */
	  जइ (DECL_SAVED_वृक्षः (olddecl))
	    DECL_ABSTRACT_ORIGIN (newdecl)
	      = DECL_ABSTRACT_ORIGIN (olddecl);
	}
    }

  /* Merge the USED information.  */
  जइ (वृक्षः_USED (olddecl))
    वृक्षः_USED (newdecl) = 1;
  अण्णहा जइ (वृक्षः_USED (newdecl))
    वृक्षः_USED (olddecl) = 1;
  जइ (VAR_P (olddecl) || वृक्षः_CODE (olddecl) == PARM_DECL)
    DECL_READ_P (newdecl) |= DECL_READ_P (olddecl);
  जइ (DECL_PRESERVE_P (olddecl))
    DECL_PRESERVE_P (newdecl) = 1;
  अण्णहा जइ (DECL_PRESERVE_P (newdecl))
    DECL_PRESERVE_P (olddecl) = 1;

  /* Merge DECL_COMMON */
  जइ (VAR_P (olddecl) && VAR_P (newdecl)
      && !lookup_attribute ("common", DECL_ATTRIBUTES (newdecl))
      && !lookup_attribute ("nocommon", DECL_ATTRIBUTES (newdecl)))
    DECL_COMMON (newdecl) = DECL_COMMON (newdecl) && DECL_COMMON (olddecl);

  /* Copy most of the decl-specific fields of NEWDECL into OLDDECL.
     But preserve OLDDECL's DECL_UID, DECL_CONTEXT and
     DECL_ARGUMENTS (if appropriate).  */
  {
    unsigned olddecl_uid = DECL_UID (olddecl);
    वृक्षः olddecl_context = DECL_CONTEXT (olddecl);
    वृक्षः olddecl_arguments = रिक्त;
    जइ (वृक्षः_CODE (olddecl) == FUNCTION_DECL)
      olddecl_arguments = DECL_ARGUMENTS (olddecl);

    memcpy ((वर्ण *) olddecl + परिमाण (संरचना वृक्षः_common),
	    (वर्ण *) newdecl + परिमाण (संरचना वृक्षः_common),
	    परिमाण (संरचना वृक्षः_decl_common) - परिमाण (संरचना वृक्षः_common));
    DECL_USER_ALIGN (olddecl) = DECL_USER_ALIGN (newdecl);
    विकल्प (वृक्षः_CODE (olddecl))
      {
      पक्ष FUNCTION_DECL:
      पक्ष VAR_DECL:
	{
	  संरचना symtab_ग्रन्थिः *snode = olddecl->decl_with_vis.symtab_ग्रन्थिः;

	  memcpy ((वर्ण *) olddecl + परिमाण (संरचना वृक्षः_decl_common),
		  (वर्ण *) newdecl + परिमाण (संरचना वृक्षः_decl_common),
		  वृक्षः_code_size (वृक्षः_CODE (olddecl)) - परिमाण (संरचना वृक्षः_decl_common));
	  olddecl->decl_with_vis.symtab_ग्रन्थिः = snode;

	  जइ ((DECL_EXTERNAL (olddecl)
	       || वृक्षः_PUBLIC (olddecl)
	       || वृक्षः_STATIC (olddecl))
	      && DECL_SECTION_NAME (newdecl) != रिक्त)
	    set_decl_section_name (olddecl, newdecl);

	  /* This isn't quite correct for something like
		int __thread x attribute ((tls_model ("local-exec")));
		extern int __thread x;
	     as we'll lose the "local-exec" model.  */
	  जइ (VAR_P (olddecl) && DECL_THREAD_LOCAL_P (newdecl))
	    set_decl_tls_model (olddecl, DECL_TLS_MODEL (newdecl));
	  भङ्ग;
	}

      पक्ष FIELD_DECL:
      पक्ष PARM_DECL:
      पक्ष LABEL_DECL:
      पक्ष RESULT_DECL:
      पक्ष CONST_DECL:
      पक्ष TYPE_DECL:
	memcpy ((वर्ण *) olddecl + परिमाण (संरचना वृक्षः_decl_common),
		(वर्ण *) newdecl + परिमाण (संरचना वृक्षः_decl_common),
		वृक्षः_code_size (वृक्षः_CODE (olddecl)) - परिमाण (संरचना वृक्षः_decl_common));
	भङ्ग;

      स्वभाव:

	memcpy ((वर्ण *) olddecl + परिमाण (संरचना वृक्षः_decl_common),
		(वर्ण *) newdecl + परिमाण (संरचना वृक्षः_decl_common),
		परिमाण (संरचना वृक्षः_decl_non_common) - परिमाण (संरचना वृक्षः_decl_common));
      }
    DECL_UID (olddecl) = olddecl_uid;
    DECL_CONTEXT (olddecl) = olddecl_context;
    जइ (वृक्षः_CODE (olddecl) == FUNCTION_DECL)
      DECL_ARGUMENTS (olddecl) = olddecl_arguments;
  }

  /* If OLDDECL had its DECL_RTL instantiated, re-invoke make_decl_rtl
     so that encode_section_info has a chance to look at the new decl
     flags and attributes.  */
  जइ (DECL_RTL_SET_P (olddecl)
      && (वृक्षः_CODE (olddecl) == FUNCTION_DECL
	  || (VAR_P (olddecl) && वृक्षः_STATIC (olddecl))))
    make_decl_rtl (olddecl);
}

/* Handle when a new declaration NEWDECL has the same name as an old
   one OLDDECL in the same binding contour.  Prints an error message
   if appropriate.

   If safely possible, alter OLDDECL to look like NEWDECL, and return
   true.  Otherwise, return false.  */

स्थिर तार्किक
duplicate_decls (वृक्षः newdecl, वृक्षः olddecl)
{
  वृक्षः newtype = रिक्त, oldtype = रिक्त;

  जइ (!diagnose_mismatched_decls (newdecl, olddecl, &newtype, &oldtype))
    {
      /* Avoid `unused variable' and other warnings for OLDDECL.  */
      suppress_warning (olddecl, OPT_Wunused);
      /* If the types are completely different, poison them both with
 	 error_mark_node.  */
      जइ (वृक्षः_CODE (वृक्षः_TYPE (newdecl)) != वृक्षः_CODE (वृक्षः_TYPE (olddecl))
	  && olddecl != error_mark_ग्रन्थिः
	  && seen_error ())
	{
	  जइ (वृक्षः_CODE (olddecl) != FUNCTION_DECL)
	    वृक्षः_TYPE (olddecl) = error_mark_ग्रन्थिः;
	  जइ (वृक्षः_CODE (newdecl) != FUNCTION_DECL)
	    वृक्षः_TYPE (newdecl) = error_mark_ग्रन्थिः;
	}
      प्रत्यागम मिच्छ;
    }

  merge_decls (newdecl, olddecl, newtype, oldtype);

  /* The NEWDECL will no longer be needed.

     Before releasing the node, be sure to remove function from symbol
     table that might have been inserted there to record comdat group.
     Be sure to however do not free DECL_STRUCT_FUNCTION because this
     structure is shared in between NEWDECL and OLDECL.  */
  जइ (वृक्षः_CODE (newdecl) == FUNCTION_DECL)
    DECL_STRUCT_FUNCTION (newdecl) = रिक्त;
  जइ (VAR_OR_FUNCTION_DECL_P (newdecl))
    {
      संरचना symtab_ग्रन्थिः *snode = symtab_ग्रन्थिः::get (newdecl);
      जइ (snode)
	snode->remove ();
    }
  ggc_free (newdecl);
  प्रत्यागम सच्च;
}


/* Check whether decl-node NEW_DECL shadows an existing declaration.  */
स्थिर शून्य
warn_if_shadowing (वृक्षः new_decl)
{
  संरचना c_binding *b;

  /* Shadow warnings wanted?  */
  जइ (!(warn_shadow
        || warn_shadow_local
        || warn_shadow_compatible_local)
      /* No shadow warnings for internally generated vars.  */
      || DECL_IS_UNDECLARED_BUILTIN (new_decl))
    प्रत्यागम;

  /* Is anything being shadowed?  Invisible decls do not count.  */
  प्रति (b = I_चिह्नम्_BINDING (DECL_NAME (new_decl)); b; b = b->shadowed)
    जइ (b->decl && b->decl != new_decl && !b->invisible
	&& (b->decl == error_mark_ग्रन्थिः
	    || diagnostic_report_warnings_p (global_dc,
					     DECL_SOURCE_LOCATION (b->decl))))
      {
	वृक्षः old_decl = b->decl;

	जइ (old_decl == error_mark_ग्रन्थिः)
	  {
	    warning (OPT_Wshadow, "declaration of %q+D shadows previous "
		     "non-variable", new_decl);
	    भङ्ग;
	  }

	तार्किक warned = मिच्छ;
	auto_diagnostic_group d;
	जइ (वृक्षः_CODE (old_decl) == PARM_DECL)
	  {
	    गणना opt_code warning_code;

	    /* If '-Wshadow=compatible-local' is specified without other
	       -Wshadow= flags, we will warn only when the types of the
	       shadowing variable (i.e. new_decl) and the shadowed variable
	       (old_decl) are compatible.  */
	    जइ (warn_shadow)
	      warning_code = OPT_Wshadow;
	    अण्णहा जइ (comptypes (वृक्षः_TYPE (old_decl), वृक्षः_TYPE (new_decl)))
	      warning_code = OPT_Wshadow_compatible_local;
	    अण्णहा
	      warning_code = OPT_Wshadow_local;
	    warned = warning_at (DECL_SOURCE_LOCATION (new_decl), warning_code,
				 "declaration of %qD shadows a parameter",
				 new_decl);
	  }
	अण्णहा जइ (DECL_FILE_SCOPE_P (old_decl))
	  {
	    /* Do not warn if a variable shadows a function, unless
	       the variable is a function or a pointer-to-function.  */
	    जइ (वृक्षः_CODE (old_decl) == FUNCTION_DECL
		&& वृक्षः_CODE (new_decl) != FUNCTION_DECL
		&& !FUNCTION_POINTER_TYPE_P (वृक्षः_TYPE (new_decl)))
		अनुवर्त;

	    warned = warning_at (DECL_SOURCE_LOCATION (new_decl), OPT_Wshadow,
				 "declaration of %qD shadows a global "
				 "declaration",
				 new_decl);
	  }
	अण्णहा जइ (वृक्षः_CODE (old_decl) == FUNCTION_DECL
		 && fndecl_built_in_p (old_decl))
	  {
	    warning (OPT_Wshadow, "declaration of %q+D shadows "
		     "a built-in function", new_decl);
	    भङ्ग;
	  }
	अण्णहा
	  {
	    गणना opt_code warning_code;

	    /* If '-Wshadow=compatible-local' is specified without other
	       -Wshadow= flags, we will warn only when the types of the
	       shadowing variable (i.e. new_decl) and the shadowed variable
	       (old_decl) are compatible.  */
	    जइ (warn_shadow)
	      warning_code = OPT_Wshadow;
	    अण्णहा जइ (comptypes (वृक्षः_TYPE (old_decl), वृक्षः_TYPE (new_decl)))
	      warning_code = OPT_Wshadow_compatible_local;
	    अण्णहा
	      warning_code = OPT_Wshadow_local;
	    warned = warning_at (DECL_SOURCE_LOCATION (new_decl), warning_code,
				 "declaration of %qD shadows a previous local",
				 new_decl);
	  }

	जइ (warned)
	  inform (DECL_SOURCE_LOCATION (old_decl),
		  "shadowed declaration is here");

	भङ्ग;
      }
}

/* Record a decl-node X as belonging to the current lexical scope.
   Check for errors (such as an incompatible declaration for the same
   name already seen in the same scope).

   Returns either X or an old decl for the same name.
   If an old decl is returned, it may have been smashed
   to agree with what X says.  */

वृक्षः
pushdecl (वृक्षः x)
{
  वृक्षः name = DECL_NAME (x);
  संरचना c_scope *scope = current_scope;
  संरचना c_binding *b;
  तार्किक nested = मिच्छ;
  location_t locus = DECL_SOURCE_LOCATION (x);

  /* Must set DECL_CONTEXT for everything not at file scope or
     DECL_FILE_SCOPE_P won't work.  Local externs don't count
     unless they have initializers (which generate code).  We
     also exclude CONST_DECLs because enumerators will get the
     type of the enum as context.  */
  जइ (current_function_decl
      && वृक्षः_CODE (x) != CONST_DECL
      && (!VAR_OR_FUNCTION_DECL_P (x)
	  || DECL_INITIAL (x) || !वृक्षः_PUBLIC (x)))
    DECL_CONTEXT (x) = current_function_decl;

  /* Anonymous decls are just inserted in the scope.  */
  जइ (!name)
    {
      bind (name, x, scope, /*invisible=*/मिच्छ, /*nested=*/मिच्छ,
	    locus);
      प्रत्यागम x;
    }

  /* First, see if there is another declaration with the same name in
     the current scope.  If there is, duplicate_decls may do all the
     work for us.  If duplicate_decls returns false, that indicates
     two incompatible decls in the same scope; we are to silently
     replace the old one (duplicate_decls has issued all appropriate
     diagnostics).  In particular, we should not consider possible
     duplicates in the external scope, or shadowing.  */
  b = I_चिह्नम्_BINDING (name);
  जइ (b && B_IN_SCOPE (b, scope))
    {
      संरचना c_binding *b_ext, *b_use;
      वृक्षः type = वृक्षः_TYPE (x);
      वृक्षः visdecl = b->decl;
      वृक्षः vistype = वृक्षः_TYPE (visdecl);
      जइ (वृक्षः_CODE (वृक्षः_TYPE (x)) == ARRAY_TYPE
	  && COMPLETE_TYPE_P (वृक्षः_TYPE (x)))
	b->inner_comp = मिच्छ;
      b_use = b;
      b_ext = b;
      /* If this is an external linkage declaration, we should check
	 for compatibility with the type in the external scope before
	 setting the type at this scope based on the visible
	 information only.  */
      जइ (वृक्षः_PUBLIC (x) && वृक्षः_PUBLIC (visdecl))
	{
	  जाव (b_ext && !B_IN_EXTERNAL_SCOPE (b_ext))
	    b_ext = b_ext->shadowed;
	  जइ (b_ext)
	    {
	      b_use = b_ext;
	      जइ (b_use->u.type)
		वृक्षः_TYPE (b_use->decl) = b_use->u.type;
	    }
	}

      /* Check if x is part of a FMV set with b_use.
	 FMV is only supported in c for targets with target_version
	 attributes.  */
      जइ (!TARGET_HAS_FMV_TARGET_ATTRIBUTE
	  && b_use && वृक्षः_CODE (b_use->decl) == FUNCTION_DECL
	  && वृक्षः_CODE (x) == FUNCTION_DECL && DECL_FILE_SCOPE_P (b_use->decl)
	  && DECL_FILE_SCOPE_P (x)
	  && disjoint_version_decls (x, b_use->decl)
	  && comptypes (vistype, type))
	{
	  maybe_mark_function_versioned (b_use->decl);
	  maybe_mark_function_versioned (b->decl);
	  maybe_mark_function_versioned (x);

	  cgraph_ग्रन्थिः *b_ग्रन्थिः = cgraph_ग्रन्थिः::get_create (b_use->decl);
	  cgraph_function_version_info *b_v = b_ग्रन्थिः->function_version ();
	  जइ (!b_v)
	    b_v = b_ग्रन्थिः->निवेशय_new_function_version ();

	  /* Check if this new node conflicts with any previous functions
	     in the set.  */
	  cgraph_function_version_info *version = b_v;
	  प्रति (; version; version = version->next)
	    जइ (!disjoint_version_decls (version->this_ग्रन्थिः->decl, x))
	      {
		/* The decls define overlapping version, so attempt to merge
		   or diagnose the conflict.  */
		जइ (duplicate_decls (x, version->this_ग्रन्थिः->decl))
		  प्रत्यागम version->this_ग्रन्थिः->decl;
		अण्णहा
		  प्रत्यागम error_mark_ग्रन्थिः;
	      }

	  /* This is a new version to be added to FMV structure.  */
	  cgraph_ग्रन्थिः::add_function_version (b_v, x);

	  /* Get the first node from the structure.  */
	  cgraph_function_version_info *default_v = b_v;
	  जाव (default_v->prev)
	    default_v = default_v->prev;
	  /* Always use the default node for the bindings.  */
	  b_use->decl = default_v->this_ग्रन्थिः->decl;
	  b->decl = default_v->this_ग्रन्थिः->decl;

	  /* Node is not a duplicate, so no need to do the rest of the
	     checks.  */
	  प्रत्यागम x;
	}

      जइ (duplicate_decls (x, b_use->decl))
	{
	  जइ (b_use != b)
	    {
	      /* Save the updated type in the external scope and
		 restore the proper type for this scope.  */
	      वृक्षः thistype;
	      जइ (comptypes (vistype, type))
		thistype = composite_type (vistype, type);
	      अण्णहा
		thistype = वृक्षः_TYPE (b_use->decl);
	      b_use->u.type = वृक्षः_TYPE (b_use->decl);
	      जइ (वृक्षः_CODE (b_use->decl) == FUNCTION_DECL
		  && fndecl_built_in_p (b_use->decl))
		thistype
		  = c_build_type_attribute_variant (thistype,
						    TYPE_ATTRIBUTES
						    (b_use->u.type));
	      वृक्षः_TYPE (b_use->decl) = thistype;
	    }
	  प्रत्यागम b_use->decl;
	}
      अण्णहा
	गच्छ skip_external_and_shadow_checks;
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
  जइ ((DECL_EXTERNAL (x) || scope == file_scope)
      && (VAR_OR_FUNCTION_DECL_P (x) || c_dialect_objc ()))
    {
      वृक्षः type = वृक्षः_TYPE (x);
      वृक्षः vistype = NULL_वृक्षः;
      वृक्षः visdecl = NULL_वृक्षः;
      तार्किक type_saved = मिच्छ;
      जइ (b && !B_IN_EXTERNAL_SCOPE (b)
	  && VAR_OR_FUNCTION_DECL_P (b->decl)
	  && DECL_FILE_SCOPE_P (b->decl))
	{
	  visdecl = b->decl;
	  vistype = वृक्षः_TYPE (visdecl);
	}
      जइ (scope != file_scope
	  && !DECL_IN_SYSTEM_HEADER (x))
	warning_at (locus, OPT_Wnested_externs,
		    "nested extern declaration of %qD", x);

      जाव (b && !B_IN_EXTERNAL_SCOPE (b))
	{
	  /* If this decl might be modified, save its type.  This is
	     done here rather than when the decl is first bound
	     because the type may change after first binding, through
	     being completed or through attributes being added.  If we
	     encounter multiple such decls, only the first should have
	     its type saved; the others will already have had their
	     proper types saved and the types will not have changed as
	     their scopes will not have been re-entered.  */
	  जइ (DECL_P (b->decl) && DECL_FILE_SCOPE_P (b->decl) && !type_saved)
	    {
	      b->u.type = वृक्षः_TYPE (b->decl);
	      type_saved = सच्च;
	    }
	  जइ (B_IN_FILE_SCOPE (b)
	      && VAR_P (b->decl)
	      && वृक्षः_STATIC (b->decl)
	      && वृक्षः_CODE (वृक्षः_TYPE (b->decl)) == ARRAY_TYPE
	      && !TYPE_DOMAIN (वृक्षः_TYPE (b->decl))
	      && वृक्षः_CODE (type) == ARRAY_TYPE
	      && TYPE_DOMAIN (type)
	      && TYPE_MAX_मानम् (TYPE_DOMAIN (type))
	      && !integer_zerop (TYPE_MAX_मानम् (TYPE_DOMAIN (type))))
	    {
	      /* Array type completed in inner scope, which should be
		 diagnosed if the completion does not have size 1 and
		 it does not get completed in the file scope.  */
	      b->inner_comp = सच्च;
	    }
	  b = b->shadowed;
	}

      /* If a matching external declaration has been found, set its
	 type to the composite of all the types of that declaration.
	 After the consistency checks, it will be reset to the
	 composite of the visible types only.  */
      जइ (b && b->u.type)
	वृक्षः_TYPE (b->decl) = b->u.type;

      /* the static does not go in the externals scope.  */
      जइ (b && duplicate_decls (x, b->decl))
	{
	  वृक्षः thistype;
	  जइ (vistype)
	    {
	      जइ (comptypes (vistype, type))
		thistype = composite_type (vistype, type);
	      अण्णहा
		thistype = वृक्षः_TYPE (b->decl);
	    }
	  अण्णहा
	    thistype = type;
	  b->u.type = वृक्षः_TYPE (b->decl);
	  /* Propagate the type attributes to the decl.  */
	  thistype
	    = c_build_type_attribute_variant (thistype,
					      TYPE_ATTRIBUTES (b->u.type));
	  वृक्षः_TYPE (b->decl) = thistype;
	  bind (name, b->decl, scope, /*invisible=*/मिच्छ, /*nested=*/सच्च,
		locus);
	  प्रत्यागम b->decl;
	}
      अण्णहा जइ (वृक्षः_PUBLIC (x))
	{
	  जइ (visdecl && !b && duplicate_decls (x, visdecl))
	    {
	      /* An external declaration at block scope referring to a
		 visible entity with internal linkage.  The composite
		 type will already be correct for this scope, so we
		 just need to fall through to make the declaration in
		 this scope.  */
	      nested = सच्च;
	      x = visdecl;
	    }
	  अण्णहा
	    {
	      bind (name, x, external_scope, /*invisible=*/सच्च,
		    /*nested=*/मिच्छ, locus);
	      nested = सच्च;
	    }
	}
    }

  जइ (वृक्षः_CODE (x) != PARM_DECL)
    warn_if_shadowing (x);

 skip_external_and_shadow_checks:
  जइ (वृक्षः_CODE (x) == TYPE_DECL)
    {
      /* So this is a typedef, set its underlying type.  */
      set_underlying_type (x);

      /* If X is a typedef defined in the current function, record it
	 for the purpose of implementing the -Wunused-local-typedefs
	 warning.  */
      record_locally_defined_typedef (x);
    }

  bind (name, x, scope, /*invisible=*/मिच्छ, nested, locus);

  /* If x's type is incomplete because it's based on a
     structure or union which has not yet been fully declared,
     attach it to that structure or union type, so we can go
     back and complete the variable declaration later, if the
     structure or union gets fully declared.

     If the input is erroneous, we can have error_mark in the type
     slot (e.g. "f(void a, ...)") - that doesn't count as an
     incomplete type.  */
  जइ (वृक्षः_TYPE (x) != error_mark_ग्रन्थिः
      && !COMPLETE_TYPE_P (वृक्षः_TYPE (x)))
    {
      वृक्षः element = वृक्षः_TYPE (x);

      जाव (वृक्षः_CODE (element) == ARRAY_TYPE)
	element = वृक्षः_TYPE (element);
      element = TYPE_MAIN_VARIANT (element);

      जइ ((RECORD_OR_UNION_TYPE_P (element)
	   || वृक्षः_CODE (element) == ENUMERAL_TYPE)
	  && (वृक्षः_CODE (x) != TYPE_DECL
	      || वृक्षः_CODE (वृक्षः_TYPE (x)) == ARRAY_TYPE)
	  && !COMPLETE_TYPE_P (element))
	C_TYPE_INCOMPLETE_VARS (element)
	  = वृक्षः_cons (NULL_वृक्षः, x, C_TYPE_INCOMPLETE_VARS (element));
    }
  प्रत्यागम x;
}


/* Issue a permerror about implicit function declaration.  ID is the function
   identifier, OLDDECL is a declaration of the function in a different scope,
   or NULL_TREE.  */

स्थिर शून्य
implicit_decl_permerror (location_t loc, वृक्षः id, वृक्षः olddecl)
{
  जइ (!warn_implicit_function_declaration)
    प्रत्यागम;

  तार्किक warned;
  auto_diagnostic_group d;
  name_hint hint;
  जइ (!olddecl)
    hint = lookup_name_fuzzy (id, FUZZY_LOOKUP_FUNCTION_NAME, loc);

  जइ (flag_isoc99)
    {
      जइ (ध्रुव वर्ण *suggestion = hint.suggestion ())
	{
	  gcc_rich_location richloc (loc);
	  richloc.add_fixit_replace (suggestion);
	  warned = permerror_opt (&richloc, OPT_Wimplicit_function_declaration,
				  "implicit declaration of function %qE;"
				  " did you mean %qs?",
				  id, suggestion);
	}
      अण्णहा
	warned = permerror_opt (loc, OPT_Wimplicit_function_declaration,
				"implicit declaration of function %qE", id);
    }
  अण्णहा जइ (ध्रुव वर्ण *suggestion = hint.suggestion ())
    {
      gcc_rich_location richloc (loc);
      richloc.add_fixit_replace (suggestion);
      warned = warning_at
	(&richloc, OPT_Wimplicit_function_declaration,
	 G_("implicit declaration of function %qE; did you mean %qs?"),
	 id, suggestion);
    }
  अण्णहा
    warned = warning_at (loc, OPT_Wimplicit_function_declaration,
			 G_("implicit declaration of function %qE"), id);

  जइ (warned)
    {
      /* Whether the olddecl is an undeclared builtin function.
	 locate_old_decl will not generate a diagnostic for those,
	 so in that case we want to look elsewhere.  */
      तार्किक undeclared_builtin = (olddecl
				 && वृक्षः_CODE (olddecl) == FUNCTION_DECL
				 && fndecl_built_in_p (olddecl)
				 && !C_DECL_DECLARED_BUILTIN (olddecl));
      जइ (undeclared_builtin)
	{
	  ध्रुव वर्ण *header = header_for_builtin_fn (olddecl);
	  जइ (header)
	    {
	      rich_location richloc (पङ्क्तिः_table, loc);
	      maybe_add_include_fixit (&richloc, header, सच्च);
	      inform (&richloc,
		      "include %qs or provide a declaration of %qE",
		      header, id);
	    }
	}
      अण्णहा जइ (olddecl)
	locate_old_decl (olddecl);
    }

  जइ (!warned)
    hint.suppress ();
}

/* Return the name of the header file that declares built-in function
   FNDECL, or null if either we don't know or don't expect to see an
   explicit declaration.  */

स्थिर ध्रुव वर्ण *
header_for_builtin_fn (वृक्षः fndecl)
{
  जइ (DECL_BUILT_IN_CLASS (fndecl) != BUILT_IN_NORMAL)
    प्रत्यागम रिक्त;

  विकल्प (DECL_FUNCTION_CODE (fndecl))
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
    पक्ष BUILT_IN_ISINF:
    पक्ष BUILT_IN_ISNAN:
      प्रत्यागम "<math.h>";
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
      प्रत्यागम "<complex.h>";
    पक्ष BUILT_IN_MEMCHR:
    पक्ष BUILT_IN_MEMCMP:
    पक्ष BUILT_IN_MEMCPY:
    पक्ष BUILT_IN_MEMMOVE:
    पक्ष BUILT_IN_MEMSET:
    पक्ष BUILT_IN_STRCAT:
    पक्ष BUILT_IN_STRCHR:
    पक्ष BUILT_IN_STRCMP:
    पक्ष BUILT_IN_STRCPY:
    पक्ष BUILT_IN_STRCSPN:
    पक्ष BUILT_IN_STRLEN:
    पक्ष BUILT_IN_STRNCAT:
    पक्ष BUILT_IN_STRNCMP:
    पक्ष BUILT_IN_STRNCPY:
    पक्ष BUILT_IN_STRPBRK:
    पक्ष BUILT_IN_STRRCHR:
    पक्ष BUILT_IN_STRSPN:
    पक्ष BUILT_IN_STRSTR:
      प्रत्यागम "<string.h>";
    पक्ष BUILT_IN_FPRINTF:
    पक्ष BUILT_IN_PUTC:
    पक्ष BUILT_IN_FPUTC:
    पक्ष BUILT_IN_FPUTS:
    पक्ष BUILT_IN_FSCANF:
    पक्ष BUILT_IN_FWRITE:
    पक्ष BUILT_IN_PRINTF:
    पक्ष BUILT_IN_PUTCHAR:
    पक्ष BUILT_IN_PUTS:
    पक्ष BUILT_IN_SCANF:
    पक्ष BUILT_IN_SNPRINTF:
    पक्ष BUILT_IN_SPRINTF:
    पक्ष BUILT_IN_SSCANF:
    पक्ष BUILT_IN_VFPRINTF:
    पक्ष BUILT_IN_VFSCANF:
    पक्ष BUILT_IN_VPRINTF:
    पक्ष BUILT_IN_VSCANF:
    पक्ष BUILT_IN_VSNPRINTF:
    पक्ष BUILT_IN_VSPRINTF:
    पक्ष BUILT_IN_VSSCANF:
      प्रत्यागम "<stdio.h>";
    पक्ष BUILT_IN_ISALNUM:
    पक्ष BUILT_IN_ISALPHA:
    पक्ष BUILT_IN_ISBLANK:
    पक्ष BUILT_IN_ISCNTRL:
    पक्ष BUILT_IN_ISDIGIT:
    पक्ष BUILT_IN_ISGRAPH:
    पक्ष BUILT_IN_ISLOWER:
    पक्ष BUILT_IN_ISPRINT:
    पक्ष BUILT_IN_ISPUNCT:
    पक्ष BUILT_IN_ISSPACE:
    पक्ष BUILT_IN_ISUPPER:
    पक्ष BUILT_IN_ISXDIGIT:
    पक्ष BUILT_IN_TOLOWER:
    पक्ष BUILT_IN_TOUPPER:
      प्रत्यागम "<ctype.h>";
    पक्ष BUILT_IN_ISWALNUM:
    पक्ष BUILT_IN_ISWALPHA:
    पक्ष BUILT_IN_ISWBLANK:
    पक्ष BUILT_IN_ISWCNTRL:
    पक्ष BUILT_IN_ISWDIGIT:
    पक्ष BUILT_IN_ISWGRAPH:
    पक्ष BUILT_IN_ISWLOWER:
    पक्ष BUILT_IN_ISWPRINT:
    पक्ष BUILT_IN_ISWPUNCT:
    पक्ष BUILT_IN_ISWSPACE:
    पक्ष BUILT_IN_ISWUPPER:
    पक्ष BUILT_IN_ISWXDIGIT:
    पक्ष BUILT_IN_TOWLOWER:
    पक्ष BUILT_IN_TOWUPPER:
      प्रत्यागम "<wctype.h>";
    पक्ष BUILT_IN_ABORT:
    पक्ष BUILT_IN_ABS:
    पक्ष BUILT_IN_CALLOC:
    पक्ष BUILT_IN_EXIT:
    पक्ष BUILT_IN_FREE:
    पक्ष BUILT_IN_LABS:
    पक्ष BUILT_IN_LLABS:
    पक्ष BUILT_IN_MALLOC:
    पक्ष BUILT_IN_REALLOC:
    पक्ष BUILT_IN__EXIT2:
    पक्ष BUILT_IN_ALIGNED_ALLOC:
      प्रत्यागम "<stdlib.h>";
    पक्ष BUILT_IN_IMAXABS:
      प्रत्यागम "<inttypes.h>";
    पक्ष BUILT_IN_STRFTIME:
      प्रत्यागम "<time.h>";
    स्वभाव:
      प्रत्यागम रिक्त;
    }
}

/* Generate an implicit declaration for identifier FUNCTIONID at LOC as a
   function of type int ().  */

वृक्षः
implicitly_declare (location_t loc, वृक्षः functionid)
{
  संरचना c_binding *b;
  वृक्षः decl = NULL_वृक्षः;
  वृक्षः asmspec_वृक्षः;

  प्रति (b = I_चिह्नम्_BINDING (functionid); b; b = b->shadowed)
    {
      जइ (B_IN_SCOPE (b, external_scope))
	{
	  decl = b->decl;
	  भङ्ग;
	}
    }

  जइ (decl)
    {
      जइ (वृक्षः_CODE (decl) != FUNCTION_DECL)
	प्रत्यागम decl;

      /* FIXME: Objective-C has weird not-really-builtin functions
	 which are supposed to be visible automatically.  They wind up
	 in the external scope because they're pushed before the file
	 scope gets created.  Catch this here and rebind them into the
	 file scope.  */
      जइ (!fndecl_built_in_p (decl) && DECL_IS_UNDECLARED_BUILTIN (decl))
	{
	  bind (functionid, decl, file_scope,
		/*invisible=*/मिच्छ, /*nested=*/सच्च,
		DECL_SOURCE_LOCATION (decl));
	  प्रत्यागम decl;
	}
      अण्णहा
	{
	  वृक्षः newtype = default_function_type;
	  जइ (b->u.type)
	    वृक्षः_TYPE (decl) = b->u.type;
	  /* Implicit declaration of a function already declared
	     (somehow) in a different scope, or as a built-in.
	     If this is the first time this has happened, warn;
	     then recycle the old declaration but with the new type.  */
	  जइ (!C_DECL_IMPLICIT (decl))
	    {
	      implicit_decl_permerror (loc, functionid, decl);
	      C_DECL_IMPLICIT (decl) = 1;
	    }
	  जइ (fndecl_built_in_p (decl))
	    {
	      newtype = c_build_type_attribute_variant (newtype,
							TYPE_ATTRIBUTES
							(वृक्षः_TYPE (decl)));
	      जइ (!comptypes (newtype, वृक्षः_TYPE (decl)))
		{
		  auto_diagnostic_group d;
		  तार्किक warned = warning_at (loc,
					    OPT_Wbuiltin_declaration_mismatch,
					    "incompatible implicit "
					    "declaration of built-in "
					    "function %qD", decl);
		  /* See if we can hint which header to include.  */
		  ध्रुव वर्ण *header = header_for_builtin_fn (decl);
		  जइ (header != रिक्त && warned)
		    {
		      rich_location richloc (पङ्क्तिः_table, loc);
		      maybe_add_include_fixit (&richloc, header, सच्च);
		      inform (&richloc,
			      "include %qs or provide a declaration of %qD",
			      header, decl);
		    }
		  newtype = वृक्षः_TYPE (decl);
		}
	    }
	  अण्णहा
	    {
	      जइ (!comptypes (newtype, वृक्षः_TYPE (decl)))
		{
		  auto_diagnostic_group d;
		  error_at (loc, "incompatible implicit declaration of "
			    "function %qD", decl);
		  locate_old_decl (decl);
		}
	    }
	  b->u.type = वृक्षः_TYPE (decl);
	  वृक्षः_TYPE (decl) = newtype;
	  bind (functionid, decl, current_scope,
		/*invisible=*/मिच्छ, /*nested=*/सच्च,
		DECL_SOURCE_LOCATION (decl));
	  प्रत्यागम decl;
	}
    }

  /* Not seen before.  */
  decl = build_decl (loc, FUNCTION_DECL, functionid, default_function_type);
  DECL_EXTERNAL (decl) = 1;
  वृक्षः_PUBLIC (decl) = 1;
  C_DECL_IMPLICIT (decl) = 1;
  implicit_decl_permerror (loc, functionid, 0);
  asmspec_वृक्षः = maybe_apply_renaming_pragma (decl, /*asmname=*/रिक्त);
  जइ (asmspec_वृक्षः)
    set_user_assembler_name (decl, वृक्षः_STRING_POINTER (asmspec_वृक्षः));

  /* C89 says implicit declarations are in the innermost block.
     So we record the decl in the standard fashion.  */
  decl = pushdecl (decl);

  /* No need to call objc_check_decl here - it's a function type.  */
  rest_of_decl_compilation (decl, 0, 0);

  /* Write a record describing this implicit function declaration
     to the prototypes file (if requested).  */
  gen_aux_info_record (decl, 0, 1, 0);

  /* Possibly apply some default attributes to this implicit declaration.  */
  decl_attributes (&decl, NULL_वृक्षः, 0);

  प्रत्यागम decl;
}

/* Issue an error message for a reference to an undeclared variable
   ID, including a reference to a builtin outside of function-call
   context.  Establish a binding of the identifier to error_mark_node
   in an appropriate scope, which will suppress further errors for the
   same identifier.  The error message should be given location LOC.  */
शून्य
undeclared_variable (location_t loc, वृक्षः id)
{
  स्थिर तार्किक already = मिच्छ;
  संरचना c_scope *scope;

  auto_diagnostic_group d;
  जइ (current_function_decl == NULL_वृक्षः)
    {
      name_hint guessed_id = lookup_name_fuzzy (id, FUZZY_LOOKUP_NAME, loc);
      जइ (ध्रुव वर्ण *suggestion = guessed_id.suggestion ())
	{
	  gcc_rich_location richloc (loc);
	  richloc.add_fixit_replace (suggestion);
	  error_at (&richloc,
		    "%qE undeclared here (not in a function);"
		    " did you mean %qs?",
		    id, suggestion);
	}
      अण्णहा
	error_at (loc, "%qE undeclared here (not in a function)", id);
      scope = current_scope;
    }
  अण्णहा
    {
      जइ (!objc_diagnose_private_ivar (id))
	{
	  name_hint guessed_id = lookup_name_fuzzy (id, FUZZY_LOOKUP_NAME, loc);
	  जइ (ध्रुव वर्ण *suggestion = guessed_id.suggestion ())
	    {
	      gcc_rich_location richloc (loc);
	      richloc.add_fixit_replace (suggestion);
	      error_at (&richloc,
			"%qE undeclared (first use in this function);"
			" did you mean %qs?",
			id, suggestion);
	    }
	  अण्णहा
	    error_at (loc, "%qE undeclared (first use in this function)", id);
	}
      जइ (!already)
	{
          inform (loc, "each undeclared identifier is reported only"
                  " once for each function it appears in");
	  already = सच्च;
	}

      /* If we are parsing old-style parameter decls, current_function_decl
	 will be nonnull but current_function_scope will be null.  */
      scope = current_function_scope ? current_function_scope : current_scope;
    }
  bind (id, error_mark_ग्रन्थिः, scope, /*invisible=*/मिच्छ, /*nested=*/मिच्छ,
	UNKNOWN_LOCATION);
}

/* Subroutine of lookup_label, declare_label, define_label: construct a
   LABEL_DECL with all the proper frills.  Also create a struct
   c_label_vars initialized for the current scope.  */

स्थिर वृक्षः
make_label (location_t location, वृक्षः name, तार्किक defining,
	    संरचना c_label_vars **p_label_vars)
{
  वृक्षः label = build_decl (location, LABEL_DECL, name, void_type_ग्रन्थिः);
  DECL_CONTEXT (label) = current_function_decl;
  SET_DECL_MODE (label, VOIDmode);

  c_label_vars *label_vars = ggc_alloc<c_label_vars> ();
  label_vars->shadowed = रिक्त;
  set_spot_bindings (&label_vars->label_bindings, defining);
  label_vars->decls_in_scope = make_वृक्षः_vector ();
  label_vars->gotos = रिक्त;
  *p_label_vars = label_vars;

  प्रत्यागम label;
}

/* Get the LABEL_DECL corresponding to identifier NAME as a label.
   Create one if none exists so far for the current function.
   This is called when a label is used in a goto expression or
   has its address taken.  */

वृक्षः
lookup_label (वृक्षः name)
{
  वृक्षः label;
  संरचना c_label_vars *label_vars;

  जइ (current_function_scope == 0)
    {
      error ("label %qE referenced outside of any function", name);
      प्रत्यागम NULL_वृक्षः;
    }

  /* Use a label already defined or ref'd with this name, but not if
     it is inherited from a containing function and wasn't declared
     using __label__.  */
  label = I_LABEL_DECL (name);
  जइ (label && (DECL_CONTEXT (label) == current_function_decl
		|| C_DECLARED_LABEL_FLAG (label)))
    {
      /* If the label has only been declared, update its apparent
	 location to point here, for better diagnostics if it
	 turns out not to have been defined.  */
      जइ (DECL_INITIAL (label) == NULL_वृक्षः)
	DECL_SOURCE_LOCATION (label) = निवेशः_location;
      प्रत्यागम label;
    }

  /* No label binding for that identifier; make one.  */
  label = make_label (निवेशः_location, name, मिच्छ, &label_vars);

  /* Ordinary labels go in the current function scope.  */
  bind_label (name, label, current_function_scope, label_vars);

  प्रत्यागम label;
}

/* Issue a warning about DECL for a goto statement at GOTO_LOC going
   to LABEL.  */

स्थिर शून्य
warn_about_goto (location_t goto_loc, वृक्षः label, वृक्षः decl)
{
  auto_diagnostic_group d;
  जइ (c_type_variably_modified_p (वृक्षः_TYPE (decl)))
    error_at (goto_loc,
	      "jump into scope of identifier with variably modified type");
  अण्णहा जइ (flag_openmp
	   && lookup_attribute ("omp allocate", DECL_ATTRIBUTES (decl)))
    error_at (goto_loc, "jump skips OpenMP %<allocate%> allocation");
  अण्णहा
    जइ (!warning_at (goto_loc, OPT_Wjump_misses_init,
		     "jump skips variable initialization"))
      प्रत्यागम;
  inform (DECL_SOURCE_LOCATION (label), "label %qD defined here", label);
  inform (DECL_SOURCE_LOCATION (decl), "%qD declared here", decl);
}

/* Look up a label because of a goto statement.  This is like
   lookup_label, but also issues any appropriate warnings.  */

वृक्षः
lookup_label_for_goto (location_t loc, वृक्षः name)
{
  वृक्षः label;
  संरचना c_label_vars *label_vars;
  unsigned पूर्णाङ्क ix;
  वृक्षः decl;

  label = lookup_label (name);
  जइ (label == NULL_वृक्षः)
    प्रत्यागम NULL_वृक्षः;

  /* If we are jumping to a different function, we can't issue any
     useful warnings.  */
  जइ (DECL_CONTEXT (label) != current_function_decl)
    {
      gcc_assert (C_DECLARED_LABEL_FLAG (label));
      प्रत्यागम label;
    }

  label_vars = I_LABEL_BINDING (name)->u.label;

  /* If the label has not yet been defined, then push this goto on a
     list for possible later warnings.  */
  जइ (label_vars->label_bindings.scope == रिक्त)
    {
      c_goto_bindings *g = ggc_alloc<c_goto_bindings> ();

      g->loc = loc;
      set_spot_bindings (&g->goto_bindings, सच्च);
      vec_safe_प्रक्षिप (label_vars->gotos, g);
      प्रत्यागम label;
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

  जइ (label_vars->label_bindings.वामः_stmt_व्यञ्जकम्)
    {
      auto_diagnostic_group d;
      error_at (loc, "jump into statement expression");
      inform (DECL_SOURCE_LOCATION (label), "label %qD defined here", label);
    }

  प्रत्यागम label;
}

/* Make a label named NAME in the current function, shadowing silently
   any that may be inherited from containing functions or containing
   scopes.  This is called for __label__ declarations.  */

वृक्षः
declare_label (वृक्षः name)
{
  संरचना c_binding *b = I_LABEL_BINDING (name);
  वृक्षः label;
  संरचना c_label_vars *label_vars;

  /* Check to make sure that the label hasn't already been declared
     at this scope */
  जइ (b && B_IN_CURRENT_SCOPE (b))
    {
      auto_diagnostic_group d;
      error ("duplicate label declaration %qE", name);
      locate_old_decl (b->decl);

      /* Just use the previous declaration.  */
      प्रत्यागम b->decl;
    }

  label = make_label (निवेशः_location, name, मिच्छ, &label_vars);
  C_DECLARED_LABEL_FLAG (label) = 1;

  /* Declared labels go in the current scope.  */
  bind_label (name, label, current_scope, label_vars);

  प्रत्यागम label;
}

/* When we define a label, issue any appropriate warnings if there are
   any gotos earlier in the function which jump to this label.  */

स्थिर शून्य
check_earlier_gotos (वृक्षः label, संरचना c_label_vars* label_vars)
{
  unsigned पूर्णाङ्क ix;
  संरचना c_goto_bindings *g;

  FOR_EACH_VEC_SAFE_ELT (label_vars->gotos, ix, g)
    {
      संरचना c_binding *b;
      संरचना c_scope *scope;

      /* We have a goto to this label.  The goto is going forward.  In
	 g->scope, the goto is going to skip any binding which was
	 defined after g->bindings_in_scope.  */
      जइ (g->goto_bindings.scope->has_jump_unsafe_decl)
	{
	  प्रति (b = g->goto_bindings.scope->bindings;
	       b != g->goto_bindings.bindings_in_scope;
	       b = b->prev)
	    {
	      जइ (decl_jump_unsafe (b->decl))
		warn_about_goto (g->loc, label, b->decl);
	    }
	}

      /* We also need to warn about decls defined in any scopes
	 between the scope of the label and the scope of the goto.  */
      प्रति (scope = label_vars->label_bindings.scope;
	   scope != g->goto_bindings.scope;
	   scope = scope->outer)
	{
	  gcc_assert (scope != रिक्त);
	  जइ (scope->has_jump_unsafe_decl)
	    {
	      जइ (scope == label_vars->label_bindings.scope)
		b = label_vars->label_bindings.bindings_in_scope;
	      अण्णहा
		b = scope->bindings;
	      प्रति (; b != रिक्त; b = b->prev)
		{
		  जइ (decl_jump_unsafe (b->decl))
		    warn_about_goto (g->loc, label, b->decl);
		}
	    }
	}

      जइ (g->goto_bindings.stmt_exprs > 0)
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
  label_vars->gotos = रिक्त;
}

/* Define a label, specifying the location in the source file.
   Return the LABEL_DECL node for the label, if the definition is valid.
   Otherwise return NULL_TREE.  */

वृक्षः
define_label (location_t location, वृक्षः name)
{
  /* Find any preexisting label with this name.  It is an error
     if that label has already been defined in this function, or
     if there is a containing function with a declared label with
     the same name.  */
  वृक्षः label = I_LABEL_DECL (name);

  जइ (label
      && ((DECL_CONTEXT (label) == current_function_decl
	   && DECL_INITIAL (label) != NULL_वृक्षः)
	  || (DECL_CONTEXT (label) != current_function_decl
	      && C_DECLARED_LABEL_FLAG (label))))
    {
      auto_diagnostic_group d;
      error_at (location, "duplicate label %qD", label);
      locate_old_decl (label);
      प्रत्यागम NULL_वृक्षः;
    }
  अण्णहा जइ (label && DECL_CONTEXT (label) == current_function_decl)
    {
      संरचना c_label_vars *label_vars = I_LABEL_BINDING (name)->u.label;

      /* The label has been used or declared already in this function,
	 but not defined.  Update its location to point to this
	 definition.  */
      DECL_SOURCE_LOCATION (label) = location;
      set_spot_bindings (&label_vars->label_bindings, सच्च);

      /* Issue warnings as required about any goto statements from
	 earlier in the function.  */
      check_earlier_gotos (label, label_vars);
    }
  अण्णहा
    {
      संरचना c_label_vars *label_vars;

      /* No label binding for that identifier; make one.  */
      label = make_label (location, name, सच्च, &label_vars);

      /* Ordinary labels go in the current function scope.  */
      bind_label (name, label, current_function_scope, label_vars);
    }

  जइ (!in_system_header_at (निवेशः_location) && lookup_name (name))
    warning_at (location, OPT_Wtraditional,
		"traditional C lacks a separate namespace "
		"for labels, identifier %qE conflicts", name);

  /* Mark label as having been defined.  */
  DECL_INITIAL (label) = error_mark_ग्रन्थिः;
  प्रत्यागम label;
}

/* Get the bindings for a new switch statement.  This is used to issue
   warnings as appropriate for jumps from the switch to case or
   default labels.  */

संरचना c_spot_bindings *
c_get_switch_bindings (शून्य)
{
  संरचना c_spot_bindings *switch_bindings;

  switch_bindings = XNEW (संरचना c_spot_bindings);
  set_spot_bindings (switch_bindings, सच्च);
  प्रत्यागम switch_bindings;
}

शून्य
c_release_switch_bindings (संरचना c_spot_bindings *bindings)
{
  gcc_assert (bindings->stmt_exprs == 0 && !bindings->वामः_stmt_व्यञ्जकम्);
  XDELETE (bindings);
}

/* This is called at the point of a case or default label to issue
   warnings about decls as needed.  It returns true if it found an
   error, not just a warning.  */

तार्किक
c_check_switch_jump_warnings (संरचना c_spot_bindings *switch_bindings,
			      location_t switch_loc, location_t case_loc)
{
  तार्किक saw_error;
  संरचना c_scope *scope;

  saw_error = मिच्छ;
  प्रति (scope = current_scope;
       scope != switch_bindings->scope;
       scope = scope->outer)
    {
      संरचना c_binding *b;

      gcc_assert (scope != रिक्त);

      जइ (!scope->has_jump_unsafe_decl)
	अनुवर्त;

      प्रति (b = scope->bindings; b != रिक्त; b = b->prev)
	{
	  जइ (decl_jump_unsafe (b->decl))
	    {
	      auto_diagnostic_group d;
	      तार्किक emitted;
	      जइ (c_type_variably_modified_p (वृक्षः_TYPE (b->decl)))
		{
		  saw_error = सच्च;
		  error_at (case_loc,
			    "switch jumps into scope of identifier with "
			    "variably modified type");
		  emitted = सच्च;
		}
	      अण्णहा जइ (flag_openmp
		       && lookup_attribute ("omp allocate",
					    DECL_ATTRIBUTES (b->decl)))
		{
		  saw_error = सच्च;
		  error_at (case_loc,
			    "switch jumps over OpenMP %<allocate%> allocation");
		  emitted = सच्च;
		}
	      अण्णहा
		emitted
		  = warning_at (case_loc, OPT_Wjump_misses_init,
				"switch jumps over variable initialization");
	      जइ (emitted)
		{
		  inform (switch_loc, "switch starts here");
		  inform (DECL_SOURCE_LOCATION (b->decl), "%qD declared here",
			  b->decl);
		}
	    }
	}
    }

  जइ (switch_bindings->stmt_exprs > 0)
    {
      saw_error = सच्च;
      auto_diagnostic_group d;
      error_at (case_loc, "switch jumps into statement expression");
      inform (switch_loc, "switch starts here");
    }

  प्रत्यागम saw_error;
}

/* Given NAME, an IDENTIFIER_NODE,
   return the structure (or union or enum) definition for that name.
   If THISLEVEL_ONLY is nonzero, searches only the current_scope.
   CODE says which kind of type the caller wants;
   it is RECORD_TYPE or UNION_TYPE or ENUMERAL_TYPE.
   If PLOC is not NULL and this returns non-null, it sets *PLOC to the
   location where the tag was defined.
   If the wrong kind of type is found, an error is reported.  */

स्थिर वृक्षः
lookup_tag (गणना वृक्षः_code code, वृक्षः name, तार्किक thislevel_only,
	    location_t *ploc)
{
  संरचना c_binding *b = I_TAG_BINDING (name);
  तार्किक thislevel = मिच्छ;

  जइ (!b || !b->decl)
    प्रत्यागम NULL_वृक्षः;

  /* We only care about whether it's in this level if
     thislevel_only was set or it might be a type clash.  */
  जइ (thislevel_only || वृक्षः_CODE (b->decl) != code)
    {
      /* For our purposes, a tag in the external scope is the same as
	 a tag in the file scope.  (Primarily relevant to Objective-C
	 and its builtin structure tags, which get pushed before the
	 file scope is created.)  */
      जइ (B_IN_CURRENT_SCOPE (b)
	  || (current_scope == file_scope && B_IN_EXTERNAL_SCOPE (b)))
	thislevel = सच्च;
    }

  जइ (thislevel_only && !thislevel)
    प्रत्यागम NULL_वृक्षः;

  जइ (वृक्षः_CODE (b->decl) != code)
    {
      /* Definition isn't the kind we were looking for.  */
      pending_invalid_xref = name;
      pending_invalid_xref_location = निवेशः_location;

      /* If in the same binding level as a declaration as a tag
	 of a different type, this must not be allowed to
	 shadow that tag, so give the error immediately.
	 (For example, "struct foo; union foo;" is invalid.)  */
      जइ (thislevel)
	pending_xref_error ();
    }

  जइ (ploc != रिक्त)
    *ploc = b->locus;

  प्रत्यागम b->decl;
}

/* Return true if a definition exists for NAME with code CODE.  */

तार्किक
tag_exists_p (गणना वृक्षः_code code, वृक्षः name)
{
  संरचना c_binding *b = I_TAG_BINDING (name);

  जइ (b == रिक्त || b->decl == NULL_वृक्षः)
    प्रत्यागम मिच्छ;
  प्रत्यागम वृक्षः_CODE (b->decl) == code;
}

/* Print an error message now
   for a recent invalid struct, union or enum cross reference.
   We don't print them immediately because they are not invalid
   when used in the `struct foo;' construct for shadowing.  */

शून्य
pending_xref_error (शून्य)
{
  जइ (pending_invalid_xref != NULL_वृक्षः)
    error_at (pending_invalid_xref_location, "%qE defined as wrong kind of tag",
	      pending_invalid_xref);
  pending_invalid_xref = NULL_वृक्षः;
}


/* Look up NAME in the current scope and its superiors
   in the namespace of variables, functions and typedefs.
   Return a ..._DECL node of some kind representing its definition,
   or return NULL_TREE if it is undefined.  */

वृक्षः
lookup_name (वृक्षः name)
{
  संरचना c_binding *b = I_चिह्नम्_BINDING (name);
  /* Do not resolve non-default function versions.  */
  जइ (b
      && वृक्षः_CODE (b->decl) == FUNCTION_DECL
      && DECL_FUNCTION_VERSIONED (b->decl)
      && !is_function_default_version (b->decl))
    प्रत्यागम NULL_वृक्षः;
  जइ (b && !b->invisible)
    {
      maybe_record_typedef_use (b->decl);
      प्रत्यागम b->decl;
    }
  प्रत्यागम NULL_वृक्षः;
}

/* Similar to `lookup_name' but look only at the indicated scope.  */

स्थिर वृक्षः
lookup_name_in_scope (वृक्षः name, संरचना c_scope *scope)
{
  संरचना c_binding *b;

  प्रति (b = I_चिह्नम्_BINDING (name); b; b = b->shadowed)
    जइ (B_IN_SCOPE (b, scope))
      प्रत्यागम b->decl;
  प्रत्यागम NULL_वृक्षः;
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
lookup_name_fuzzy (वृक्षः name, गणना lookup_name_fuzzy_kind kind, location_t loc)
{
  gcc_assert (वृक्षः_CODE (name) == IDENTIFIER_ग्रन्थिः);

  /* Look up function-like macros first; maybe misusing them. */
  auto cpp_ग्रन्थिः = cpp_lookup (parse_in,
			      (ध्रुव unsigned वर्ण*)IDENTIFIER_POINTER (name),
			      IDENTIFIER_LENGTH (name));
  जइ (cpp_ग्रन्थिः && cpp_fun_like_macro_p (cpp_ग्रन्थिः))
    प्रत्यागम name_hint
      (nullptr,
       std::make_unique<macro_like_function_used> (loc,
						   IDENTIFIER_POINTER (name)));

  /* Next, try some well-known names in the C standard library, in case
     the user forgot a #include.  */
  ध्रुव वर्ण *header_hint
    = get_c_stdlib_header_for_name (IDENTIFIER_POINTER (name));

  जइ (header_hint)
    प्रत्यागम name_hint
      (nullptr,
       std::make_unique<suggest_missing_header> (loc,
						 IDENTIFIER_POINTER (name),
						 header_hint));

  /* Next, look for exact matches for builtin defines that would have been
     defined if the user had passed a command-line option (e.g. -fopenmp
     for "_OPENMP").  */
  diagnostics::option_id option_id
    = get_option_for_builtin_define (IDENTIFIER_POINTER (name));
  जइ (option_id.m_idx > 0)
    प्रत्यागम name_hint
      (nullptr,
       std::make_unique<suggest_missing_option> (loc,
						 IDENTIFIER_POINTER (name),
						 option_id));

  /* Only suggest names reserved for the implementation if NAME begins
     with an underscore.  */
  तार्किक consider_implementation_names = (IDENTIFIER_POINTER (name)[0] == '_');

  best_match<वृक्षः, वृक्षः> bm (name);

  /* Look within currently valid scopes.  */
  प्रति (c_scope *scope = current_scope; scope; scope = scope->outer)
    प्रति (c_binding *binding = scope->bindings; binding; binding = binding->prev)
      {
	जइ (!binding->id || binding->invisible)
	  अनुवर्त;
	जइ (binding->decl == error_mark_ग्रन्थिः)
	  अनुवर्त;
	/* Don't use bindings from implicitly declared functions,
	   as they were likely misspellings themselves.  */
	जइ (वृक्षः_CODE (binding->decl) == FUNCTION_DECL)
	  जइ (C_DECL_IMPLICIT (binding->decl))
	    अनुवर्त;
	/* Don't suggest names that are reserved for use by the
	   implementation, unless NAME began with an underscore.  */
	जइ (!consider_implementation_names)
	  {
	    ध्रुव वर्ण *suggestion_str = IDENTIFIER_POINTER (binding->id);
	    जइ (name_reserved_for_implementation_p (suggestion_str))
	      अनुवर्त;
	  }
	विकल्प (kind)
	  {
	  पक्ष FUZZY_LOOKUP_TYPENAME:
	    जइ (वृक्षः_CODE (binding->decl) != TYPE_DECL)
	      अनुवर्त;
	    भङ्ग;

	  पक्ष FUZZY_LOOKUP_FUNCTION_NAME:
	    जइ (वृक्षः_CODE (binding->decl) != FUNCTION_DECL)
	      {
		/* Allow function pointers.  */
		जइ ((VAR_P (binding->decl)
		     || वृक्षः_CODE (binding->decl) == PARM_DECL)
		    && वृक्षः_CODE (वृक्षः_TYPE (binding->decl)) == POINTER_TYPE
		    && (वृक्षः_CODE (वृक्षः_TYPE (वृक्षः_TYPE (binding->decl)))
			== FUNCTION_TYPE))
		  भङ्ग;
		अनुवर्त;
	      }
	    भङ्ग;

	  स्वभाव:
	    भङ्ग;
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
  जइ (best_macro)
    {
      ध्रुव वर्ण *id = (ध्रुव वर्ण *)best_macro->ident.str;
      वृक्षः macro_as_identifier
	= get_identifier_with_length (id, best_macro->ident.len);
      bm.set_best_so_far (macro_as_identifier,
			  bmm.get_best_distance (),
			  bmm.get_best_candidate_length ());
    }

  /* Try the "start_typename" keywords to detect
     "singed" vs "signed" typos.  */
  जइ (kind == FUZZY_LOOKUP_TYPENAME)
    {
      प्रति (unsigned i = 0; i < अङ्कः_c_common_reswords; i++)
	{
	  ध्रुव c_common_resword *resword = &c_common_reswords[i];
	  जइ (!c_keyword_starts_typename (resword->rid))
	    अनुवर्त;
	  वृक्षः resword_identifier = ridpointers [resword->rid];
	  जइ (!resword_identifier)
	    अनुवर्त;
	  gcc_assert (वृक्षः_CODE (resword_identifier) == IDENTIFIER_ग्रन्थिः);
	  bm.consider (resword_identifier);
	}
    }

  वृक्षः best = bm.get_best_meaningful_candidate ();
  जइ (best)
    प्रत्यागम name_hint (IDENTIFIER_POINTER (best), रिक्त);
  अण्णहा
    प्रत्यागम name_hint (रिक्त, रिक्त);
}


/* Handle the standard [[nodiscard]] attribute.  */

स्थिर वृक्षः
handle_nodiscard_attribute (वृक्षः *ग्रन्थिः, वृक्षः name, वृक्षः /*args*/,
			    पूर्णाङ्क /*flags*/, तार्किक *no_add_attrs)
{
  जइ (वृक्षः_CODE (*ग्रन्थिः) == FUNCTION_DECL)
    {
      जइ (VOID_TYPE_P (वृक्षः_TYPE (वृक्षः_TYPE (*ग्रन्थिः))))
	warning_at (DECL_SOURCE_LOCATION (*ग्रन्थिः),
		    OPT_Wattributes, "%qE attribute applied to %qD with void "
		    "return type", name, *ग्रन्थिः);
    }
  अण्णहा जइ (RECORD_OR_UNION_TYPE_P (*ग्रन्थिः)
	   || वृक्षः_CODE (*ग्रन्थिः) == ENUMERAL_TYPE)
    /* OK */;
  अण्णहा
    {
      pedwarn (निवेशः_location,
	       OPT_Wattributes, "%qE attribute can only be applied to "
	       "functions or to structure, union or enumeration types", name);
      *no_add_attrs = सच्च;
    }
  प्रत्यागम NULL_वृक्षः;
}

/* Handle the standard [[noreturn]] attribute.  */

स्थिर वृक्षः
handle_std_noreturn_attribute (वृक्षः *ग्रन्थिः, वृक्षः name, वृक्षः args,
			       पूर्णाङ्क flags, तार्किक *no_add_attrs)
{
  /* Unlike GNU __attribute__ ((noreturn)), the standard [[noreturn]]
     only applies to functions, not function pointers.  */
  जइ (वृक्षः_CODE (*ग्रन्थिः) == FUNCTION_DECL)
    प्रत्यागम handle_noreturn_attribute (ग्रन्थिः, name, args, flags, no_add_attrs);
  अण्णहा
    {
      pedwarn (निवेशः_location, OPT_Wattributes,
	       "standard %qE attribute can only be applied to functions",
	       name);
      *no_add_attrs = सच्च;
      प्रत्यागम NULL_वृक्षः;
    }
}

/* Handle the standard [[unsequenced]] attribute.  */

स्थिर वृक्षः
handle_std_unsequenced_attribute (वृक्षः *ग्रन्थिः, वृक्षः name, वृक्षः args,
				  पूर्णाङ्क flags, तार्किक *no_add_attrs)
{
  /* Unlike GNU __attribute__ ((unsequenced)), the standard [[unsequenced]]
     should be only applied to function declarators or type specifiers which
     have function type.  */
  जइ (ग्रन्थिः[2])
    {
      auto_diagnostic_group d;
      जइ (pedwarn (निवेशः_location, OPT_Wattributes,
		   "standard %qE attribute can only be applied to function "
		   "declarators or type specifiers with function type", name))
	inform (निवेशः_location, "did you mean to specify it after %<)%> "
				"following function parameters?");
      *no_add_attrs = सच्च;
      प्रत्यागम NULL_वृक्षः;
    }
  प्रत्यागम handle_unsequenced_attribute (ग्रन्थिः, name, args, flags, no_add_attrs);
}

/* Handle the standard [[reproducible]] attribute.  */

स्थिर वृक्षः
handle_std_reproducible_attribute (वृक्षः *ग्रन्थिः, वृक्षः name, वृक्षः args,
				   पूर्णाङ्क flags, तार्किक *no_add_attrs)
{
  प्रत्यागम handle_std_unsequenced_attribute (ग्रन्थिः, name, args, flags,
					   no_add_attrs);
}

/* Table of supported standard (C23) attributes.  */
स्थिर ध्रुव attribute_spec std_attributes[] =
{
  /* { name, min_len, max_len, decl_req, type_req, fn_type_req,
       affects_type_identity, handler, exclude } */
  { "_Noreturn", 0, 0, मिच्छ, मिच्छ, मिच्छ, मिच्छ,
    handle_std_noreturn_attribute, रिक्त },
  { "deprecated", 0, 1, मिच्छ, मिच्छ, मिच्छ, मिच्छ,
    handle_deprecated_attribute, रिक्त },
  { "fallthrough", 0, 0, मिच्छ, मिच्छ, मिच्छ, मिच्छ,
    handle_fallthrough_attribute, रिक्त },
  { "maybe_unused", 0, 0, मिच्छ, मिच्छ, मिच्छ, मिच्छ,
    handle_unused_attribute, रिक्त },
  { "nodiscard", 0, 1, मिच्छ, मिच्छ, मिच्छ, मिच्छ,
    handle_nodiscard_attribute, रिक्त },
  { "noreturn", 0, 0, मिच्छ, मिच्छ, मिच्छ, मिच्छ,
    handle_std_noreturn_attribute, रिक्त },
  { "reproducible", 0, 0, मिच्छ, सच्च, सच्च, मिच्छ,
    handle_std_reproducible_attribute, रिक्त },
  { "unsequenced", 0, 0, मिच्छ, सच्च, सच्च, मिच्छ,
    handle_std_unsequenced_attribute, रिक्त }
};

ध्रुव scoped_attribute_specs std_attribute_table =
{
  nullptr, { std_attributes }
};

/* Create the predefined scalar types of C,
   and some nodes representing standard constants (0, 1, (void *) 0).
   Initialize the global scope.
   Make definitions for built-in primitive functions.  */

शून्य
c_init_decl_processing (शून्य)
{
  location_t save_loc = निवेशः_location;

  /* Initialize reserved words for parser.  */
  c_parse_init ();

  current_function_decl = NULL_वृक्षः;

  gcc_obstack_init (&parser_obstack);

  /* Make the externals scope.  */
  प्रक्षिप_scope ();
  external_scope = current_scope;

  /* Declarations from c_common_nodes_and_builtins must not be associated
     with this input file, lest we get differences between using and not
     using preprocessed headers.  */
  निवेशः_location = BUILTINS_LOCATION;

  c_common_nodes_and_builtins ();

  /* In C, comparisons and TRUTH_* expressions have type int.  */
  truthvalue_type_ग्रन्थिः = integer_type_ग्रन्थिः;
  truthvalue_true_ग्रन्थिः = integer_one_ग्रन्थिः;
  truthvalue_false_ग्रन्थिः = integer_zero_ग्रन्थिः;

  /* Even in C99, which has a real boolean type.  */
  pushdecl (build_decl (UNKNOWN_LOCATION, TYPE_DECL,
			get_identifier (flag_isoc23 ? "bool" : "_Bool"),
			boolean_type_ग्रन्थिः));

  /* C-specific nullptr initialization.  */
  record_builtin_type (RID_MAX, "typeof (nullptr)", nullptr_type_ग्रन्थिः);
  /* The size and alignment of nullptr_t is the same as for a pointer to
     character type.  */
  SET_TYPE_ALIGN (nullptr_type_ग्रन्थिः, GET_MODE_ALIGNMENT (ptr_mode));

  निवेशः_location = save_loc;

  make_fname_decl = c_make_fname_decl;
  start_fname_decls ();

  जइ (warn_keyword_macro)
    {
      प्रति (unsigned पूर्णाङ्क i = 0; i < अङ्कः_c_common_reswords; ++i)
	/* For C register keywords which don't start with underscore
	   or start with just single underscore.  Don't complain about
	   ObjC or Transactional Memory keywords.  */
	जइ (c_common_reswords[i].word[0] == '_'
	    && c_common_reswords[i].word[1] == '_')
	  अनुवर्त;
	अण्णहा जइ (c_common_reswords[i].disable
		 & (D_TRANSMEM | D_OBJC | D_CXX_OBJC))
	  अनुवर्त;
	अण्णहा
	  {
	    वृक्षः id = get_identifier (c_common_reswords[i].word);
	    जइ (C_IS_RESERVED_WORD (id)
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

स्थिर वृक्षः
c_make_fname_decl (location_t loc, वृक्षः id, पूर्णाङ्क type_dep)
{
  ध्रुव वर्ण *name = fname_as_string (type_dep);
  वृक्षः decl, type, init;
  size_t length = strlen (name);

  type = c_build_array_type (char_type_ग्रन्थिः,
			     build_index_type (size_int (length)));
  type = c_build_qualified_type (type, TYPE_QUAL_CONST);

  decl = build_decl (loc, VAR_DECL, id, type);

  वृक्षः_STATIC (decl) = 1;
  वृक्षः_READONLY (decl) = 1;
  DECL_ARTIFICIAL (decl) = 1;

  init = build_string (length + 1, name);
  मुक्त (const_cast<वर्ण *> (name));
  वृक्षः_TYPE (init) = type;
  DECL_INITIAL (decl) = init;

  वृक्षः_USED (decl) = 1;

  जइ (current_function_decl
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
	    /*invisible=*/मिच्छ, /*nested=*/मिच्छ, UNKNOWN_LOCATION);
    }

  finish_decl (decl, loc, init, NULL_वृक्षः, NULL_वृक्षः);

  प्रत्यागम decl;
}

वृक्षः
c_builtin_function (वृक्षः decl)
{
  वृक्षः type = वृक्षः_TYPE (decl);
  वृक्षः   id = DECL_NAME (decl);

  ध्रुव वर्ण *name = IDENTIFIER_POINTER (id);
  C_DECL_BUILTIN_PROTOTYPE (decl) = prototype_p (type);

  /* Should never be called on a symbol with a preexisting meaning.  */
  gcc_assert (!I_चिह्नम्_BINDING (id));

  bind (id, decl, external_scope, /*invisible=*/सच्च, /*nested=*/मिच्छ,
	UNKNOWN_LOCATION);

  /* Builtins in the implementation namespace are made visible without
     needing to be explicitly declared.  See push_file_scope.  */
  जइ (name[0] == '_' && (name[1] == '_' || ISUPPER (name[1])))
    {
      DECL_CHAIN (decl) = visible_builtins;
      visible_builtins = decl;
    }

  प्रत्यागम decl;
}

वृक्षः
c_builtin_function_ext_scope (वृक्षः decl)
{
  वृक्षः type = वृक्षः_TYPE (decl);
  वृक्षः   id = DECL_NAME (decl);

  ध्रुव वर्ण *name = IDENTIFIER_POINTER (id);
  C_DECL_BUILTIN_PROTOTYPE (decl) = prototype_p (type);

  जइ (external_scope)
    bind (id, decl, external_scope, /*invisible=*/मिच्छ, /*nested=*/मिच्छ,
	  UNKNOWN_LOCATION);

  /* Builtins in the implementation namespace are made visible without
     needing to be explicitly declared.  See push_file_scope.  */
  जइ (name[0] == '_' && (name[1] == '_' || ISUPPER (name[1])))
    {
      DECL_CHAIN (decl) = visible_builtins;
      visible_builtins = decl;
    }

  प्रत्यागम decl;
}

/* Implement LANG_HOOKS_SIMULATE_BUILTIN_FUNCTION_DECL.  */

वृक्षः
c_simulate_builtin_function_decl (वृक्षः decl)
{
  वृक्षः type = वृक्षः_TYPE (decl);
  C_DECL_BUILTIN_PROTOTYPE (decl) = prototype_p (type);
  प्रत्यागम pushdecl (decl);
}

/* Warn about attributes in a context where they are unused
   (attribute-declarations, except for the "fallthrough" case, and
   attributes on statements).  */

शून्य
c_warn_unused_attributes (वृक्षः attrs)
{
  प्रति (वृक्षः t = attrs; t != NULL_वृक्षः; t = वृक्षः_CHAIN (t))
    जइ (get_attribute_namespace (t) == NULL_वृक्षः)
      /* The specifications of standard attributes mean this is a
	 constraint violation.  */
      pedwarn (निवेशः_location, OPT_Wattributes, "%qE attribute ignored",
	       get_attribute_name (t));
    अण्णहा जइ (!attribute_ignored_p (t))
      warning (OPT_Wattributes, "%qE attribute ignored",
	       get_attribute_name (t));
}

/* Warn for standard attributes being applied to a type that is not
   being defined, where that is a constraint violation, and return a
   list of attributes with them removed.  */

वृक्षः
c_warn_type_attributes (वृक्षः type, वृक्षः attrs)
{
  वृक्षः *attr_ptr = &attrs;
  जाव (*attr_ptr)
    जइ (get_attribute_namespace (*attr_ptr) == NULL_वृक्षः)
      {
	जइ (वृक्षः_CODE (type) == FUNCTION_TYPE)
	  {
	    वृक्षः name = get_attribute_name (*attr_ptr);
	    /* [[unsequenced]] and [[reproducible]] is fine on function
	       types that aren't being defined.  */
	    जइ (is_attribute_p ("unsequenced", name)
		|| is_attribute_p ("reproducible", name))
	      {
		attr_ptr = &वृक्षः_CHAIN (*attr_ptr);
		अनुवर्त;
	      }
	  }
	pedwarn (निवेशः_location, OPT_Wattributes, "%qE attribute ignored",
		 get_attribute_name (*attr_ptr));
	*attr_ptr = वृक्षः_CHAIN (*attr_ptr);
      }
    अण्णहा
      attr_ptr = &वृक्षः_CHAIN (*attr_ptr);
  प्रत्यागम attrs;
}

/* Called when a declaration is seen that contains no names to declare.
   If its type is a reference to a structure, union or enum inherited
   from a containing scope, shadow that tag name for the current scope
   with a forward reference.
   If its type defines a new named structure or union
   or defines an enum, it is valid but we need not do anything here.
   Otherwise, it is an error.  */

शून्य
shadow_tag (ध्रुव संरचना c_declspecs *declspecs)
{
  shadow_tag_warned (declspecs, 0);
}

/* WARNED is 1 if we have done a pedwarn, 2 if we have done a warning,
   but no pedwarn.  */
शून्य
shadow_tag_warned (ध्रुव संरचना c_declspecs *declspecs, पूर्णाङ्क warned)
{
  तार्किक found_tag = मिच्छ;

  जइ (declspecs->type && !declspecs->default_int_p && !declspecs->typedef_p)
    {
      वृक्षः मानम् = declspecs->type;
      गणना वृक्षः_code code = वृक्षः_CODE (मानम्);

      जइ (code == RECORD_TYPE || code == UNION_TYPE || code == ENUMERAL_TYPE)
	/* Used to test also that TYPE_SIZE (value) != 0.
	   That caused warning for `struct foo;' at top level in the file.  */
	{
	  वृक्षः name = TYPE_NAME (मानम्);
	  वृक्षः t;

	  found_tag = सच्च;

	  जइ (declspecs->restrict_p)
	    {
	      error ("invalid use of %<restrict%>");
	      warned = 1;
	    }

	  जइ (in_underspecified_init)
	    {
	      /* This can only occur with extensions such as statement
		 expressions, but is still appropriate as an error to
		 avoid types declared in such a context escaping to
		 the type of an auto variable.  */
	      error ("%qT declared in underspecified object initializer",
		     मानम्);
	      warned = 1;
	    }

	  जइ (name == NULL_वृक्षः)
	    {
	      जइ (warned != 1 && code != ENUMERAL_TYPE)
		/* Empty unnamed enum OK */
		{
		  pedwarn (निवेशः_location, 0,
			   "unnamed struct/union that defines no instances");
		  warned = 1;
		}
	    }
	  अण्णहा जइ (declspecs->typespec_kind != ctsk_tagdef
                   && declspecs->typespec_kind != ctsk_tagfirstref
		   && declspecs->typespec_kind != ctsk_tagfirstref_attrs
		   && declspecs->storage_class != csc_none)
	    {
	      जइ (warned != 1)
		pedwarn (निवेशः_location, 0,
			 "empty declaration with storage class specifier "
			 "does not redeclare tag");
	      warned = 1;
	      pending_xref_error ();
	    }
	  अण्णहा जइ (declspecs->typespec_kind != ctsk_tagdef
                   && declspecs->typespec_kind != ctsk_tagfirstref
                   && declspecs->typespec_kind != ctsk_tagfirstref_attrs
		   && (declspecs->const_p
		       || declspecs->volatile_p
		       || declspecs->atomic_p
		       || declspecs->restrict_p
		       || declspecs->address_space))
	    {
	      जइ (warned != 1)
		pedwarn (निवेशः_location, 0,
			 "empty declaration with type qualifier "
			  "does not redeclare tag");
	      warned = 1;
	      pending_xref_error ();
	    }
	  अण्णहा जइ (declspecs->typespec_kind != ctsk_tagdef
                   && declspecs->typespec_kind != ctsk_tagfirstref
                   && declspecs->typespec_kind != ctsk_tagfirstref_attrs
		   && declspecs->alignas_p)
	    {
	      जइ (warned != 1)
		pedwarn (निवेशः_location, 0,
			 "empty declaration with %<_Alignas%> "
			  "does not redeclare tag");
	      warned = 1;
	      pending_xref_error ();
	    }
	  अण्णहा जइ (declspecs->typespec_kind != ctsk_tagdef
		   && declspecs->typespec_kind != ctsk_tagfirstref
		   && declspecs->typespec_kind != ctsk_tagfirstref_attrs
		   && code == ENUMERAL_TYPE
		   && !declspecs->enum_type_specifier_ref_p)
	    {
	      तार्किक warned_enum = मिच्छ;
	      जइ (warned != 1)
		warned_enum = pedwarn (निवेशः_location, OPT_Wpedantic,
				       "empty declaration of %<enum%> type "
				       "does not redeclare tag");
	      जइ (warned_enum)
		warned = 1;
	      pending_xref_error ();
	    }
	  अण्णहा
	    {
	      pending_invalid_xref = NULL_वृक्षः;
	      t = lookup_tag (code, name, सच्च, रिक्त);

	      जइ (t == NULL_वृक्षः)
		{
		  t = make_ग्रन्थिः (code);
		  जइ (flag_isoc23 || code == ENUMERAL_TYPE)
		    SET_TYPE_STRUCTURAL_EQUALITY (t);
		  pushtag (निवेशः_location, name, t);
		}
	    }
	}
      अण्णहा
	{
	  जइ (warned != 1 && !in_system_header_at (निवेशः_location))
	    {
	      pedwarn (निवेशः_location, 0,
		       "useless type name in empty declaration");
	      warned = 1;
	    }
	}
    }
  अण्णहा जइ (warned != 1 && !in_system_header_at (निवेशः_location)
	   && declspecs->typedef_p)
    {
      pedwarn (निवेशः_location, 0, "useless type name in empty declaration");
      warned = 1;
    }

  pending_invalid_xref = NULL_वृक्षः;

  जइ (declspecs->inline_p)
    {
      error ("%<inline%> in empty declaration");
      warned = 1;
    }

  जइ (declspecs->noreturn_p)
    {
      error ("%<_Noreturn%> in empty declaration");
      warned = 1;
    }

  जइ (declspecs->constexpr_p)
    {
      error ("%<constexpr%> in empty declaration");
      warned = 1;
    }

  जइ (current_scope == file_scope && declspecs->storage_class == csc_auto)
    {
      error ("%<auto%> in file-scope empty declaration");
      warned = 1;
    }

  जइ (current_scope == file_scope && declspecs->storage_class == csc_register)
    {
      error ("%<register%> in file-scope empty declaration");
      warned = 1;
    }

  जइ (declspecs->enum_type_specifier_ref_p && !warned)
    {
      जइ (declspecs->storage_class != csc_none)
	{
	  error ("storage class specifier in empty declaration with %<enum%> "
		 "underlying type");
	  warned = 1;
	}
      अण्णहा जइ (declspecs->thread_p)
	{
	  error ("%qs in empty declaration with %<enum%> underlying type",
		 declspecs->thread_gnu_p ? "__thread" : "_Thread_local");
	  warned = 1;
	}
      अण्णहा जइ (declspecs->const_p
	       || declspecs->volatile_p
	       || declspecs->atomic_p
	       || declspecs->restrict_p
	       || declspecs->address_space)
	{
	  error ("type qualifier in empty declaration with %<enum%> "
		 "underlying type");
	  warned = 1;
	}
      अण्णहा जइ (declspecs->alignas_p)
	{
	  error ("%<alignas%> in empty declaration with %<enum%> "
		 "underlying type");
	  warned = 1;
	}
    }

  जइ (!warned && !in_system_header_at (निवेशः_location)
      && declspecs->storage_class != csc_none)
    {
      warning (0, "useless storage class specifier in empty declaration");
      warned = 2;
    }

  जइ (!warned && !in_system_header_at (निवेशः_location) && declspecs->thread_p)
    {
      warning (0, "useless %qs in empty declaration",
	       declspecs->thread_gnu_p ? "__thread" : "_Thread_local");
      warned = 2;
    }

  जइ (!warned
      && !in_system_header_at (निवेशः_location)
      && (declspecs->const_p
	  || declspecs->volatile_p
	  || declspecs->atomic_p
	  || declspecs->restrict_p
	  || declspecs->address_space))
    {
      warning (0, "useless type qualifier in empty declaration");
      warned = 2;
    }

  जइ (!warned && !in_system_header_at (निवेशः_location)
      && declspecs->alignas_p)
    {
      warning (0, "useless %<_Alignas%> in empty declaration");
      warned = 2;
    }

  जइ (found_tag
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
      pedwarn (निवेशः_location, 0,
	       "invalid use of attributes in empty declaration");
      warned = 1;
    }

  जइ (warned != 1)
    {
      जइ (declspecs->declspecs_seen_p
	  && !declspecs->non_std_attrs_seen_p)
	/* An attribute declaration (but not a fallthrough attribute
	   declaration, which was handled separately); warn if there
	   are any attributes being ignored (but not if the attributes
	   were empty).  */
	c_warn_unused_attributes (declspecs->attrs);
      अण्णहा जइ (!found_tag)
	pedwarn (निवेशः_location, 0, "empty declaration");
    }
}


/* Return the qualifiers from SPECS as a bitwise OR of TYPE_QUAL_*
   bits.  SPECS represents declaration specifiers that the grammar
   only permits to contain type qualifiers and attributes.  */

पूर्णाङ्क
quals_from_declspecs (ध्रुव संरचना c_declspecs *specs)
{
  पूर्णाङ्क quals = ((specs->const_p ? TYPE_QUAL_CONST : 0)
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
  प्रत्यागम quals;
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

संरचना c_declarator *
build_array_declarator (location_t loc,
			वृक्षः व्यञ्जकम्, संरचना c_declspecs *quals, तार्किक static_p,
			तार्किक vla_unspec_p)
{
  संरचना c_declarator *declarator = XOBNEW (&parser_obstack,
					    संरचना c_declarator);
  declarator->id_loc = loc;
  declarator->kind = cdk_array;
  declarator->declarator = 0;
  declarator->u.array.dimen = व्यञ्जकम्;
  जइ (quals)
    {
      declarator->u.array.attrs = quals->attrs;
      declarator->u.array.quals = quals_from_declspecs (quals);
    }
  अण्णहा
    {
      declarator->u.array.attrs = NULL_वृक्षः;
      declarator->u.array.quals = 0;
    }
  declarator->u.array.static_p = static_p;
  declarator->u.array.vla_unspec_p = vla_unspec_p;
  जइ (static_p || quals != रिक्त)
    pedwarn_c90 (loc, OPT_Wpedantic,
		 "ISO C90 does not support %<static%> or type "
		 "qualifiers in parameter array declarators");
  जइ (vla_unspec_p)
    {
      pedwarn_c90 (loc, OPT_Wpedantic,
		   "ISO C90 does not support %<[*]%> array declarators");
      जइ (current_scope->parm_flag)
	current_scope->had_vla_unspec = सच्च;
    }
  प्रत्यागम declarator;
}

/* Set the contained declarator of an array declarator.  DECL is the
   declarator, as constructed by build_array_declarator; INNER is what
   appears on the left of the [].  */

संरचना c_declarator *
set_array_declarator_inner (संरचना c_declarator *decl,
			    संरचना c_declarator *inner)
{
  decl->declarator = inner;
  प्रत्यागम decl;
}

/* Determine whether TYPE is a one-element array type "[1]".  */
स्थिर तार्किक
one_element_array_type_p (const_वृक्षः type)
{
  जइ (वृक्षः_CODE (type) != ARRAY_TYPE)
    प्रत्यागम मिच्छ;
  प्रत्यागम integer_zerop (array_type_nelts_minus_one (type));
}

/* Determine whether TYPE is a zero-length array type "[0]".  */
तार्किक
zero_length_array_type_p (const_वृक्षः type)
{
  जइ (वृक्षः_CODE (type) == ARRAY_TYPE
      && COMPLETE_TYPE_P (type)
      && TYPE_DOMAIN (type) != NULL_वृक्षः
      && (TYPE_MAX_मानम् (TYPE_DOMAIN (type)) == NULL_वृक्षः
	  || integer_all_onesp (TYPE_MAX_मानम् (TYPE_DOMAIN (type)))))
    प्रत्यागम सच्च;
  प्रत्यागम मिच्छ;
}

/* INIT is a constructor that forms DECL's initializer.  If the final
   element initializes a flexible array field, adjust the size of the
   DECL with the initializer based on whether the DECL is a union or
   a structure.  */

स्थिर शून्य
add_flexible_array_elts_to_size (वृक्षः decl, वृक्षः init)
{
  वृक्षः elt, type;

  जइ (vec_safe_is_empty (CONSTRUCTOR_ELTS (init)))
    प्रत्यागम;

  elt = CONSTRUCTOR_ELTS (init)->last ().मानम्;
  type = वृक्षः_TYPE (elt);
  जइ (flexible_array_member_type_p (type))
    {
      complete_array_type (&type, elt, मिच्छ);
      /* For a structure, add the size of the initializer to the DECL's
	 size.  */
      जइ (वृक्षः_CODE (वृक्षः_TYPE (decl)) == RECORD_TYPE)
	{
	  DECL_SIZE (decl)
	    = size_binop (PLUS_व्यञ्जकम्, DECL_SIZE (decl), TYPE_SIZE (type));
	  DECL_SIZE_UNIT (decl)
	    = size_binop (PLUS_व्यञ्जकम्, DECL_SIZE_UNIT (decl),
			  TYPE_SIZE_UNIT (type));
	}
      /* For a union, the DECL's size is the maximum of the current size
	 and the size of the initializer.  */
      अण्णहा
	{
	  DECL_SIZE (decl)
	    = size_binop (MAX_व्यञ्जकम्, DECL_SIZE (decl), TYPE_SIZE (type));
	  DECL_SIZE_UNIT (decl)
	    = size_binop (MAX_व्यञ्जकम्, DECL_SIZE_UNIT (decl),
			  TYPE_SIZE_UNIT (type));
	}
    }
}

/* Decode a "typename", such as "int **", returning a ..._TYPE node.
   Set *EXPR, if EXPR not NULL, to any expression to be evaluated
   before the type name, and set *EXPR_CONST_OPERANDS, if
   EXPR_CONST_OPERANDS not NULL, to indicate whether the type name may
   appear in a constant expression.  */

वृक्षः
groktypename (संरचना c_type_name *type_name, वृक्षः *व्यञ्जकम्,
	      तार्किक *व्यञ्जकम्_const_operands)
{
  वृक्षः type;
  वृक्षः attrs = type_name->specs->attrs;

  type_name->specs->attrs = NULL_वृक्षः;

  type = grokdeclarator (type_name->declarator, type_name->specs, TYPENAME,
			 मिच्छ, रिक्त, &attrs, व्यञ्जकम्, व्यञ्जकम्_const_operands,
			 DEPRECATED_NORMAL);

  /* Apply attributes.  */
  attrs = c_warn_type_attributes (type, attrs);
  decl_attributes (&type, attrs, 0);

  प्रत्यागम type;
}


/* Decode a "typename", such as "int **", returning a ..._TYPE node,
   as for groktypename but setting the context to GENERIC_ASSOC.  */

वृक्षः
grokgenassoc (संरचना c_type_name *type_name)
{
  वृक्षः type;
  वृक्षः attrs = type_name->specs->attrs;

  type_name->specs->attrs = NULL_वृक्षः;

  type = grokdeclarator (type_name->declarator, type_name->specs, GENERIC_ASSOC,
			 मिच्छ, रिक्त, &attrs, रिक्त, रिक्त, DEPRECATED_NORMAL);

  /* Apply attributes.  */
  attrs = c_warn_type_attributes (type, attrs);
  decl_attributes (&type, attrs, 0);

  प्रत्यागम type;
}


/* Looks up the most recent pushed declaration corresponding to DECL.  */

स्थिर वृक्षः
lookup_last_decl (वृक्षः decl)
{
  वृक्षः last_decl = lookup_name (DECL_NAME (decl));
  जइ (!last_decl)
    last_decl = lookup_name_in_scope (DECL_NAME (decl), external_scope);
  प्रत्यागम last_decl;
}

/* Wrapper for decl_attributes that adds some implicit attributes
   to VAR_DECLs or FUNCTION_DECLs.  */

स्थिर वृक्षः
c_decl_attributes (वृक्षः *ग्रन्थिः, वृक्षः attributes, पूर्णाङ्क flags)
{
  /* Add implicit "omp declare target" attribute if requested.  */
  जइ (vec_safe_length (current_omp_declare_target_attribute)
      && ((VAR_P (*ग्रन्थिः) && is_global_var (*ग्रन्थिः))
	  || वृक्षः_CODE (*ग्रन्थिः) == FUNCTION_DECL))
    {
      जइ (VAR_P (*ग्रन्थिः) && !omp_mappable_type (वृक्षः_TYPE (*ग्रन्थिः)))
	attributes = वृक्षः_cons (get_identifier ("omp declare target implicit"),
				NULL_वृक्षः, attributes);
      अण्णहा
	attributes = वृक्षः_cons (get_identifier ("omp declare target"),
				NULL_वृक्षः, attributes);
      जइ (वृक्षः_CODE (*ग्रन्थिः) == FUNCTION_DECL)
	{
	  पूर्णाङ्क device_type
	    = current_omp_declare_target_attribute->last ().device_type;
	  device_type = MAX (device_type, 0);
	  जइ ((device_type & OMP_CLAUSE_DEVICE_TYPE_HOST) != 0
	      && !lookup_attribute ("omp declare target host", attributes))
	    attributes
	      = वृक्षः_cons (get_identifier ("omp declare target host"),
			   NULL_वृक्षः, attributes);
	  जइ ((device_type & OMP_CLAUSE_DEVICE_TYPE_NOHOST) != 0
	      && !lookup_attribute ("omp declare target nohost", attributes))
	    attributes
	      = वृक्षः_cons (get_identifier ("omp declare target nohost"),
			   NULL_वृक्षः, attributes);

	  पूर्णाङ्क indirect
	    = current_omp_declare_target_attribute->last ().indirect;
	  जइ (indirect && !lookup_attribute ("omp declare target indirect",
					     attributes))
	    attributes
	      = वृक्षः_cons (get_identifier ("omp declare target indirect"),
			   NULL_वृक्षः, attributes);
	}
    }

  जइ (flag_openmp || flag_openmp_simd)
    {
      तार्किक diagnosed = मिच्छ;
      प्रति (वृक्षः *pa = &attributes; *pa; )
	{
	  जइ (is_attribute_namespace_p ("omp", *pa))
	    {
	      वृक्षः name = get_attribute_name (*pa);
	      जइ (is_attribute_p ("directive", name)
		  || is_attribute_p ("sequence", name)
		  || is_attribute_p ("decl", name))
		{
		  ध्रुव वर्ण *p = रिक्त;
		  जइ (वृक्षः_मानम् (*pa) == NULL_वृक्षः)
		    p = IDENTIFIER_POINTER (name);
		  प्रति (वृक्षः a = वृक्षः_मानम् (*pa); a; a = वृक्षः_CHAIN (a))
		    {
		      वृक्षः d = वृक्षः_मानम् (a);
		      gcc_assert (वृक्षः_CODE (d) == C_TOKEN_VEC);
		      जइ (वृक्षः_PUBLIC (d)
			  && (VAR_P (*ग्रन्थिः)
			      || वृक्षः_CODE (*ग्रन्थिः) == FUNCTION_DECL)
			  && c_maybe_parse_omp_decl (*ग्रन्थिः, d))
			अनुवर्त;
		      p = वृक्षः_PUBLIC (d) ? "decl" : "directive";
		    }
		  जइ (p && !diagnosed)
		    {
		      error ("%<omp::%s%> not allowed to be specified in "
			     "this context", p);
		      diagnosed = सच्च;
		    }
		  जइ (p)
		    {
		      *pa = वृक्षः_CHAIN (*pa);
		      अनुवर्त;
		    }
		}
	    }
	  pa = &वृक्षः_CHAIN (*pa);
	}
    }

  /* Look up the current declaration with all the attributes merged
     so far so that attributes on the current declaration that's
     about to be pushed that conflict with the former can be detected,
     diagnosed, and rejected as appropriate.  To match the C++ FE, do
     not pass an error_mark_node when we found an undeclared variable.  */
  वृक्षः last_decl = lookup_last_decl (*ग्रन्थिः);
  जइ (last_decl == error_mark_ग्रन्थिः)
    last_decl = NULL_वृक्षः;
  वृक्षः attr = decl_attributes (ग्रन्थिः, attributes, flags, last_decl);
  जइ (VAR_P (*ग्रन्थिः) && DECL_THREAD_LOCAL_P (*ग्रन्थिः))
    {
      // tls_model attribute can set a stronger TLS access model.
      tls_model model = DECL_TLS_MODEL (*ग्रन्थिः);
      tls_model default_model = decl_default_tls_model (*ग्रन्थिः);
      जइ (default_model > model)
	set_decl_tls_model (*ग्रन्थिः, default_model);
    }
  प्रत्यागम attr;
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

वृक्षः
start_decl (संरचना c_declarator *declarator, संरचना c_declspecs *declspecs,
	    तार्किक initialized, वृक्षः attributes, तार्किक do_प्रक्षिप /* = true */,
	    location_t *lastloc /* = NULL */)
{
  वृक्षः decl;
  वृक्षः old_decl;
  वृक्षः tem;
  वृक्षः व्यञ्जकम् = NULL_वृक्षः;
  गणना deprecated_states deprecated_state = DEPRECATED_NORMAL;

  /* An object declared as __attribute__((unavailable)) suppresses
     warnings and errors from __attribute__((deprecated/unavailable))
     components.
     An object declared as __attribute__((deprecated)) suppresses
     warnings of uses of other deprecated items.  */
  जइ (lookup_attribute ("unavailable", attributes))
    deprecated_state = UNAVAILABLE_DEPRECATED_SUPPRESS;
  अण्णहा जइ (lookup_attribute ("deprecated", attributes))
    deprecated_state = DEPRECATED_SUPPRESS;

  decl = grokdeclarator (declarator, declspecs,
			 NORMAL, initialized, रिक्त, &attributes, &व्यञ्जकम्, रिक्त,
			 deprecated_state);
  जइ (!decl || decl == error_mark_ग्रन्थिः)
    प्रत्यागम NULL_वृक्षः;

  old_decl = lookup_last_decl (decl);

  जइ (वृक्षः lastdecl = lastloc ? old_decl : NULL_वृक्षः)
    जइ (lastdecl != error_mark_ग्रन्थिः)
      *lastloc = DECL_SOURCE_LOCATION (lastdecl);

  /* Make sure the size expression is evaluated at this point.  */
  जइ (व्यञ्जकम् && !current_scope->parm_flag)
    add_stmt (fold_convert (void_type_ग्रन्थिः, व्यञ्जकम्));

  जइ (वृक्षः_CODE (decl) != FUNCTION_DECL && MAIN_NAME_P (DECL_NAME (decl))
      && वृक्षः_PUBLIC (decl))
    warning (OPT_Wmain, "%q+D is usually a function", decl);

  जइ (warn_missing_variable_declarations && VAR_P (decl)
      && !DECL_EXTERNAL (decl) && वृक्षः_PUBLIC (decl) && old_decl == NULL_वृक्षः)
    warning_at (DECL_SOURCE_LOCATION (decl), OPT_Wmissing_variable_declarations,
		"no previous declaration for %qD", decl);

  जइ (initialized)
    /* Is it valid for this decl to have an initializer at all?
       If not, set INITIALIZED to zero, which will indirectly
       tell 'finish_decl' to ignore the initializer once it is parsed.  */
    विकल्प (वृक्षः_CODE (decl))
      {
      पक्ष TYPE_DECL:
	error ("typedef %qD is initialized (use %<__typeof__%> instead)", decl);
	initialized = मिच्छ;
	भङ्ग;

      पक्ष FUNCTION_DECL:
	error ("function %qD is initialized like a variable", decl);
	initialized = मिच्छ;
	भङ्ग;

      पक्ष PARM_DECL:
	/* DECL_INITIAL in a PARM_DECL is really DECL_ARG_TYPE.  */
	error ("parameter %qD is initialized", decl);
	initialized = मिच्छ;
	भङ्ग;

      स्वभाव:
	/* Don't allow initializations for incomplete types except for
	   arrays which might be completed by the initialization.  */

	/* This can happen if the array size is an undefined macro.
	   We already gave a warning, so we don't need another one.  */
	जइ (वृक्षः_TYPE (decl) == error_mark_ग्रन्थिः)
	  initialized = मिच्छ;
	अण्णहा जइ (COMPLETE_TYPE_P (वृक्षः_TYPE (decl)))
	  {
	    /* A complete type is ok if size is fixed.  If the size is
	       variable, an empty initializer is OK and nonempty
	       initializers will be diagnosed in the parser.  */
	  }
	अण्णहा जइ (वृक्षः_CODE (वृक्षः_TYPE (decl)) != ARRAY_TYPE)
	  {
	    error ("variable %qD has initializer but incomplete type", decl);
	    initialized = मिच्छ;
	  }
      }

  जइ (initialized)
    {
      जइ (current_scope == file_scope)
	वृक्षः_STATIC (decl) = 1;

      /* Tell 'pushdecl' this is an initialized decl
	 even though we don't yet have the initializer expression.
	 Also tell 'finish_decl' it may store the real initializer.  */
      DECL_INITIAL (decl) = error_mark_ग्रन्थिः;
    }

  /* If this is a function declaration, write a record describing it to the
     prototypes file (if requested).  */

  जइ (वृक्षः_CODE (decl) == FUNCTION_DECL)
    gen_aux_info_record (decl, 0, 0, prototype_p (वृक्षः_TYPE (decl)));

  /* ANSI specifies that a tentative definition which is not merged with
     a non-tentative definition behaves exactly like a definition with an
     initializer equal to zero.  (Section 3.7.2)

     -fno-common gives strict ANSI behavior, though this tends to break
     a large body of code that grew up without this rule.

     Thread-local variables are never common, since there's no entrenched
     body of code to break, and it allows more efficient variable references
     in the presence of dynamic linking.  */

  जइ (VAR_P (decl)
      && !initialized
      && वृक्षः_PUBLIC (decl)
      && !DECL_THREAD_LOCAL_P (decl)
      && !flag_no_common)
    DECL_COMMON (decl) = 1;

  /* Set attributes here so if duplicate decl, will have proper attributes.  */
  c_decl_attributes (&decl, attributes, 0);

  /* Handle gnu_inline attribute.  */
  जइ (declspecs->inline_p
      && !flag_gnu89_inline
      && वृक्षः_CODE (decl) == FUNCTION_DECL
      && (lookup_attribute ("gnu_inline", DECL_ATTRIBUTES (decl))
	  || current_function_decl))
    {
      जइ (declspecs->storage_class == csc_auto && current_scope != file_scope)
	;
      अण्णहा जइ (declspecs->storage_class != csc_static)
	DECL_EXTERNAL (decl) = !DECL_EXTERNAL (decl);
    }

  जइ (वृक्षः_CODE (decl) == FUNCTION_DECL
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
  जइ (VAR_P (decl)
      && current_scope != file_scope
      && वृक्षः_STATIC (decl)
      && !वृक्षः_READONLY (decl)
      && DECL_DECLARED_INLINE_P (current_function_decl)
      && DECL_EXTERNAL (current_function_decl))
    record_inline_static (निवेशः_location, current_function_decl,
			  decl, csi_modifiable);

  जइ (c_dialect_objc ()
      && VAR_OR_FUNCTION_DECL_P (decl))
      objc_check_global_decl (decl);

  /* To enable versions to be created across TU's we mark and mangle all
     non-default versioned functions.  */
  जइ (वृक्षः_CODE (decl) == FUNCTION_DECL
      && !TARGET_HAS_FMV_TARGET_ATTRIBUTE
      && get_target_version (decl).is_valid ())
    {
      maybe_mark_function_versioned (decl);
      जइ (current_scope != file_scope)
	error ("versioned declarations are only allowed at file scope");
    }

  /* Add this decl to the current scope.
     TEM may equal DECL or it may be a previous decl of the same name.  */
  जइ (do_प्रक्षिप)
    {
      tem = pushdecl (decl);

      जइ (initialized && DECL_EXTERNAL (tem))
	{
	  DECL_EXTERNAL (tem) = 0;
	  वृक्षः_STATIC (tem) = 1;
	}

      प्रत्यागम tem;
    }
  अण्णहा
    प्रत्यागम decl;
}

/* Subroutine of finish_decl. TYPE is the type of an uninitialized object
   DECL or the non-array element type if DECL is an uninitialized array.
   If that type has a const member, diagnose this. */

स्थिर शून्य
diagnose_uninitialized_cst_member (वृक्षः decl, वृक्षः type)
{
  वृक्षः field;
  प्रति (field = TYPE_FIELDS (type); field; field = वृक्षः_CHAIN (field))
    {
      वृक्षः field_type;
      जइ (वृक्षः_CODE (field) != FIELD_DECL)
	अनुवर्त;
      field_type = strip_array_types (वृक्षः_TYPE (field));

      जइ (TYPE_QUALS (field_type) & TYPE_QUAL_CONST)
      	{
	  auto_diagnostic_group d;
	  जइ (warning_at (DECL_SOURCE_LOCATION (decl), OPT_Wc___compat,
			  "uninitialized const member in %qT is invalid in C++",
			  strip_array_types (वृक्षः_TYPE (decl))))
	    inform (DECL_SOURCE_LOCATION (field), "%qD should be initialized", field);
	}

      जइ (RECORD_OR_UNION_TYPE_P (field_type))
	diagnose_uninitialized_cst_member (decl, field_type);
    }
}

/* Finish processing of a declaration;
   install its initial value.
   If ORIGTYPE is not NULL_TREE, it is the original type of INIT.
   If the length of an array type is not known before,
   it must be determined now, from the initial value, or it is an error.

   INIT_LOC is the location of the initial value.  */

शून्य
finish_decl (वृक्षः decl, location_t init_loc, वृक्षः init,
	     वृक्षः origtype, वृक्षः asmspec_वृक्षः)
{
  वृक्षः type;
  तार्किक was_incomplete = (DECL_SIZE (decl) == NULL_वृक्षः);
  ध्रुव वर्ण *asmspec = 0;

  /* If a name was specified, get the string.  */
  जइ (VAR_OR_FUNCTION_DECL_P (decl)
      && DECL_FILE_SCOPE_P (decl))
    asmspec_वृक्षः = maybe_apply_renaming_pragma (decl, asmspec_वृक्षः);
  जइ (asmspec_वृक्षः)
    asmspec = वृक्षः_STRING_POINTER (asmspec_वृक्षः);

  जइ (VAR_P (decl)
      && वृक्षः_STATIC (decl)
      && global_bindings_p ())
    /* So decl is a global variable. Record the types it uses
       so that we can decide later to emit debug info for them.  */
    record_types_used_by_current_var_decl (decl);

  /* If `start_decl' didn't like having an initialization, ignore it now.  */
  जइ (init != NULL_वृक्षः && DECL_INITIAL (decl) == NULL_वृक्षः)
    init = NULL_वृक्षः;

  /* Don't crash if parm is initialized.  */
  जइ (वृक्षः_CODE (decl) == PARM_DECL)
    init = NULL_वृक्षः;

  जइ (init)
    store_init_मानम् (init_loc, decl, init, origtype);

  जइ (c_dialect_objc () && (VAR_OR_FUNCTION_DECL_P (decl)
			    || वृक्षः_CODE (decl) == FIELD_DECL))
    objc_check_decl (decl);

  type = वृक्षः_TYPE (decl);

  /* Deduce size of array from initialization, if not already known.
     This is only needed for an initialization in the current scope;
     it must not be done for a file-scope initialization of a
     declaration with external linkage, redeclared in an inner scope
     with the outer declaration shadowed in an intermediate scope.  */
  जइ (वृक्षः_CODE (type) == ARRAY_TYPE
      && TYPE_DOMAIN (type) == NULL_वृक्षः
      && वृक्षः_CODE (decl) != TYPE_DECL
      && !(वृक्षः_PUBLIC (decl) && current_scope != file_scope))
    {
      तार्किक do_default
	= !वृक्षः_STATIC (decl) && !DECL_EXTERNAL (decl);
      पूर्णाङ्क failure
	= complete_array_type (&वृक्षः_TYPE (decl), DECL_INITIAL (decl),
			       do_default);

      /* Get the completed type made by complete_array_type.  */
      type = वृक्षः_TYPE (decl);

      विकल्प (failure)
	{
	पक्ष 1:
	  error ("initializer fails to determine size of %q+D", decl);
	  भङ्ग;

	पक्ष 2:
	  जइ (do_default)
	    error ("array size missing in %q+D", decl);
	  अण्णहा जइ (!वृक्षः_PUBLIC (decl))
	    pedwarn_c23 (DECL_SOURCE_LOCATION (decl), OPT_Wpedantic,
			 "array size missing in %q+D", decl);
	  भङ्ग;

	पक्ष 3:
	  error ("zero or negative size array %q+D", decl);
	  भङ्ग;

	पक्ष 0:
	  /* For global variables, update the copy of the type that
	     exists in the binding.  */
	  जइ (वृक्षः_PUBLIC (decl))
	    {
	      संरचना c_binding *b_ext = I_चिह्नम्_BINDING (DECL_NAME (decl));
	      जाव (b_ext && !B_IN_EXTERNAL_SCOPE (b_ext))
		b_ext = b_ext->shadowed;
	      जइ (b_ext && वृक्षः_CODE (decl) == वृक्षः_CODE (b_ext->decl))
		{
		  जइ (b_ext->u.type && comptypes (b_ext->u.type, type))
		    b_ext->u.type = composite_type (b_ext->u.type, type);
		  अण्णहा
		    b_ext->u.type = type;
		}
	    }
	  भङ्ग;

	स्वभाव:
	  gcc_unreachable ();
	}

      जइ (DECL_INITIAL (decl) && DECL_INITIAL (decl) != error_mark_ग्रन्थिः)
	वृक्षः_TYPE (DECL_INITIAL (decl)) = type;

      relayout_decl (decl);
    }

  /* Look for braced array initializers for character arrays and
     recursively convert them into STRING_CSTs.  */
  जइ (वृक्षः init = DECL_INITIAL (decl))
    DECL_INITIAL (decl) = braced_lists_to_strings (type, init);

  जइ (VAR_P (decl))
    {
      जइ (init && वृक्षः_CODE (init) == CONSTRUCTOR)
	add_flexible_array_elts_to_size (decl, init);

      complete_flexible_array_elts (DECL_INITIAL (decl));

      जइ (is_global_var (decl))
	{
	  type_context_kind context = (DECL_THREAD_LOCAL_P (decl)
				       ? TCTX_THREAD_STORAGE
				       : TCTX_STATIC_STORAGE);
	  जइ (!verify_type_context (निवेशः_location, context, वृक्षः_TYPE (decl)))
	    वृक्षः_TYPE (decl) = error_mark_ग्रन्थिः;
	}

      जइ (DECL_SIZE (decl) == NULL_वृक्षः && वृक्षः_TYPE (decl) != error_mark_ग्रन्थिः
	  && COMPLETE_TYPE_P (वृक्षः_TYPE (decl)))
	layout_decl (decl, 0);

      जइ (DECL_SIZE (decl) == NULL_वृक्षः
	  /* Don't give an error if we already gave one earlier.  */
	  && वृक्षः_TYPE (decl) != error_mark_ग्रन्थिः
	  && (वृक्षः_STATIC (decl)
	      /* A static variable with an incomplete type
		 is an error if it is initialized.
		 Also if it is not file scope.
		 Also if it is thread-local (in C23).
		 Otherwise, let it through, but if it is not `extern'
		 then it may cause an error message later.  */
	      ? (DECL_INITIAL (decl) != NULL_वृक्षः
		 || !DECL_FILE_SCOPE_P (decl)
		 || (flag_isoc23 && DECL_THREAD_LOCAL_P (decl)))
	      /* An automatic variable with an incomplete type
		 is an error.  */
	      : !DECL_EXTERNAL (decl)))
	 {
	   error ("storage size of %q+D isn%'t known", decl);
	   वृक्षः_TYPE (decl) = error_mark_ग्रन्थिः;
	 }

      जइ ((RECORD_OR_UNION_TYPE_P (वृक्षः_TYPE (decl))
	  || वृक्षः_CODE (वृक्षः_TYPE (decl)) == ENUMERAL_TYPE)
	  && DECL_SIZE (decl) == NULL_वृक्षः
	  && वृक्षः_STATIC (decl))
	incomplete_record_decls.safe_प्रक्षिप (decl);

      जइ (is_global_var (decl)
	  && DECL_SIZE (decl) != NULL_वृक्षः
	  && वृक्षः_TYPE (decl) != error_mark_ग्रन्थिः)
	{
	  जइ (वृक्षः_CODE (DECL_SIZE (decl)) == INTEGER_CST)
	    constant_expression_warning (DECL_SIZE (decl));
	  अण्णहा
	    {
	      error ("storage size of %q+D isn%'t constant", decl);
	      वृक्षः_TYPE (decl) = error_mark_ग्रन्थिः;
	    }
	}

      जइ (वृक्षः_USED (type))
	{
	  वृक्षः_USED (decl) = 1;
	  DECL_READ_P (decl) = 1;
	}
    }

  /* If this is a function and an assembler name is specified, reset DECL_RTL
     so we can give it its new name.  Also, update builtin_decl if it
     was a normal built-in.  */
  जइ (वृक्षः_CODE (decl) == FUNCTION_DECL && asmspec)
    {
      जइ (DECL_BUILT_IN_CLASS (decl) == BUILT_IN_NORMAL)
	set_builtin_user_assembler_name (decl, asmspec);
      set_user_assembler_name (decl, asmspec);
    }

  /* If #pragma weak was used, mark the decl weak now.  */
  maybe_apply_pragma_weak (decl);

  /* Output the assembler code and/or RTL code for variables and functions,
     unless the type is an undefined structure or union.
     If not, it will get done when the type is completed.  */

  जइ (VAR_OR_FUNCTION_DECL_P (decl))
    {
      /* Determine the ELF visibility.  */
      जइ (वृक्षः_PUBLIC (decl))
	c_determine_visibility (decl);

      /* This is a no-op in c-lang.cc or something real in objc-act.cc.  */
      जइ (c_dialect_objc ())
	objc_check_decl (decl);

      जइ (asmspec)
	{
	  /* If this is not a static variable, issue a warning.
	     It doesn't make any sense to give an ASMSPEC for an
	     ordinary, non-register local variable.  Historically,
	     GCC has accepted -- but ignored -- the ASMSPEC in
	     this case.  */
	  जइ (!DECL_FILE_SCOPE_P (decl)
	      && VAR_P (decl)
	      && !C_DECL_REGISTER (decl)
	      && !वृक्षः_STATIC (decl))
	    warning (0, "ignoring %<asm%> specifier for non-static local "
		     "variable %q+D", decl);
	  अण्णहा
	    set_user_assembler_name (decl, asmspec);
	}

      जइ (DECL_FILE_SCOPE_P (decl))
	{
	  जइ (DECL_INITIAL (decl) == NULL_वृक्षः
	      || DECL_INITIAL (decl) == error_mark_ग्रन्थिः)
	    /* Don't output anything
	       when a tentative file-scope definition is seen.
	       But at end of compilation, do output code for them.  */
	    DECL_DEFER_OUTPUT (decl) = 1;
	  जइ (asmspec && VAR_P (decl) && C_DECL_REGISTER (decl))
	    DECL_HARD_REGISTER (decl) = 1;
	  rest_of_decl_compilation (decl, सच्च, 0);

	  जइ (वृक्षः_CODE (decl) == FUNCTION_DECL)
	    {
	      वृक्षः parms = DECL_ARGUMENTS (decl);
	      ध्रुव तार्किक builtin = fndecl_built_in_p (decl);
	      जइ (वृक्षः access = build_attr_access_from_parms (parms, !builtin))
		decl_attributes (&decl, access, 0);
	    }
	}
      अण्णहा
	{
	  /* In conjunction with an ASMSPEC, the `register'
	     keyword indicates that we should place the variable
	     in a particular register.  */
	  जइ (asmspec && C_DECL_REGISTER (decl))
	    {
	      DECL_HARD_REGISTER (decl) = 1;
	      /* This cannot be done for a structure with volatile
		 fields, on which DECL_REGISTER will have been
		 reset.  */
	      जइ (!DECL_REGISTER (decl))
		error ("cannot put object with volatile field into register");
	    }

	  जइ (वृक्षः_CODE (decl) != FUNCTION_DECL)
	    {
	      /* If we're building a variable sized type, and we might be
		 reachable other than via the top of the current binding
		 level, then create a new BIND_EXPR so that we deallocate
		 the object at the right time.  */
	      /* Note that DECL_SIZE can be null due to errors.  */
	      जइ (DECL_SIZE (decl)
		  && !वृक्षः_CONSTANT (DECL_SIZE (decl))
		  && STATEMENT_LIST_HAS_LABEL (cur_stmt_list))
		{
		  वृक्षः bind;
		  bind = build3 (BIND_व्यञ्जकम्, void_type_ग्रन्थिः, रिक्त, रिक्त, रिक्त);
		  वृक्षः_SIDE_EFFECTS (bind) = 1;
		  add_stmt (bind);
		  BIND_व्यञ्जकम्_BODY (bind) = प्रक्षिप_stmt_list ();
		}
	      add_stmt (build_stmt (DECL_SOURCE_LOCATION (decl),
				    DECL_व्यञ्जकम्, decl));
	    }
	}


      जइ (!DECL_FILE_SCOPE_P (decl))
	{
	  /* Recompute the RTL of a local array now
	     if it used to be an incomplete type.  */
	  जइ (was_incomplete && !is_global_var (decl))
	    {
	      /* If we used it already as memory, it must stay in memory.  */
	      वृक्षः_ADDRESSABLE (decl) = वृक्षः_USED (decl);
	      /* If it's still incomplete now, no init will save it.  */
	      जइ (DECL_SIZE (decl) == NULL_वृक्षः)
		DECL_INITIAL (decl) = NULL_वृक्षः;
	    }
	}
    }

  जइ (वृक्षः_CODE (decl) == TYPE_DECL)
    {
      जइ (!DECL_FILE_SCOPE_P (decl)
	  && c_type_variably_modified_p (वृक्षः_TYPE (decl)))
	add_stmt (build_stmt (DECL_SOURCE_LOCATION (decl), DECL_व्यञ्जकम्, decl));

      rest_of_decl_compilation (decl, DECL_FILE_SCOPE_P (decl), 0);
    }

  /* Install a cleanup (aka destructor) if one was given.  */
  जइ (VAR_P (decl) && !वृक्षः_STATIC (decl))
    {
      वृक्षः attr = lookup_attribute ("cleanup", DECL_ATTRIBUTES (decl));
      जइ (attr)
	{
	  वृक्षः cleanup_id = वृक्षः_मानम् (वृक्षः_मानम् (attr));
	  वृक्षः cleanup_decl = lookup_name (cleanup_id);
	  वृक्षः cleanup;
	  vec<वृक्षः, va_gc> *v;

	  /* Build "cleanup(&decl)" for the destructor.  */
	  cleanup = build_unary_op (निवेशः_location, ADDR_व्यञ्जकम्, decl, मिच्छ);
	  vec_alloc (v, 1);
	  v->quick_प्रक्षिप (cleanup);
	  cleanup = c_build_function_call_vec (DECL_SOURCE_LOCATION (decl),
					       vNULL, cleanup_decl, v, रिक्त);
	  vec_free (v);

	  /* Don't warn about decl unused; the cleanup uses it.  */
	  वृक्षः_USED (decl) = 1;
	  वृक्षः_USED (cleanup_decl) = 1;
	  DECL_READ_P (decl) = 1;

	  प्रक्षिप_cleanup (decl, cleanup, मिच्छ);
	}
    }

  जइ (warn_cxx_compat
      && VAR_P (decl)
      && !DECL_EXTERNAL (decl)
      && DECL_INITIAL (decl) == NULL_वृक्षः)
    {
      type = strip_array_types (type);
      जइ (वृक्षः_READONLY (decl))
	warning_at (DECL_SOURCE_LOCATION (decl), OPT_Wc___compat,
		    "uninitialized %<const %D%> is invalid in C++", decl);
      अण्णहा जइ (RECORD_OR_UNION_TYPE_P (type)
	       && C_TYPE_FIELDS_READONLY (type))
	diagnose_uninitialized_cst_member (decl, type);
    }

  जइ (flag_openmp
      && VAR_P (decl)
      && lookup_attribute ("omp declare target implicit",
			   DECL_ATTRIBUTES (decl)))
    {
      DECL_ATTRIBUTES (decl)
	= remove_attribute ("omp declare target implicit",
			    DECL_ATTRIBUTES (decl));
      जइ (!omp_mappable_type (वृक्षः_TYPE (decl)))
	error ("%q+D in declare target directive does not have mappable type",
	       decl);
      अण्णहा जइ (!lookup_attribute ("omp declare target",
				  DECL_ATTRIBUTES (decl))
	       && !lookup_attribute ("omp declare target link",
				     DECL_ATTRIBUTES (decl)))
	{
	  DECL_ATTRIBUTES (decl)
	    = वृक्षः_cons (get_identifier ("omp declare target"),
			 NULL_वृक्षः, DECL_ATTRIBUTES (decl));
	    symtab_ग्रन्थिः *ग्रन्थिः = symtab_ग्रन्थिः::get (decl);
	    जइ (ग्रन्थिः != रिक्त)
	      {
		ग्रन्थिः->offloadable = 1;
		जइ (ENABLE_OFFLOADING)
		  {
		    g->have_offload = सच्च;
		    जइ (is_a <varpool_ग्रन्थिः *> (ग्रन्थिः))
		      vec_safe_प्रक्षिप (offload_vars, decl);
		  }
	      }
	}
    }

  /* This is the last point we can lower alignment so give the target the
     chance to do so.  */
  जइ (VAR_P (decl)
      && !is_global_var (decl)
      && !DECL_HARD_REGISTER (decl))
    targetm.lower_local_decl_alignment (decl);

  invoke_plugin_callbacks (PLUGIN_FINISH_DECL, decl);
}

/* Given a parsed parameter declaration, decode it into a PARM_DECL.
   EXPR is NULL or a pointer to an expression that needs to be
   evaluated for the side effects of array size expressions in the
   parameters.  */

वृक्षः
grokparm (ध्रुव संरचना c_parm *parm, वृक्षः *व्यञ्जकम्)
{
  वृक्षः attrs = parm->attrs;
  वृक्षः decl = grokdeclarator (parm->declarator, parm->specs, PARM, मिच्छ,
			      रिक्त, &attrs, व्यञ्जकम्, रिक्त, DEPRECATED_NORMAL);

  decl_attributes (&decl, attrs, 0);

  प्रत्यागम decl;
}



/* Given a parsed parameter declaration, decode it into a PARM_DECL
   and push that on the current scope.  EXPR is a pointer to an
   expression that needs to be evaluated for the side effects of array
   size expressions in the parameters.  */

शून्य
प्रक्षिप_parm_decl (ध्रुव संरचना c_parm *parm, वृक्षः *व्यञ्जकम्)
{
  वृक्षः attrs = parm->attrs;
  वृक्षः decl = grokdeclarator (parm->declarator, parm->specs, PARM, मिच्छ, रिक्त,
			      &attrs, व्यञ्जकम्, रिक्त, DEPRECATED_NORMAL);
  जइ (decl && DECL_P (decl))
    DECL_SOURCE_LOCATION (decl) = parm->loc;

  decl_attributes (&decl, attrs, 0);

  decl = pushdecl (decl);

  finish_decl (decl, निवेशः_location, NULL_वृक्षः, NULL_वृक्षः, NULL_वृक्षः);
}

/* Mark all the parameter declarations to date as forward decls.
   Also diagnose use of this extension.  */

शून्य
mark_forward_parm_decls (शून्य)
{
  संरचना c_binding *b;

  जइ (current_scope->had_forward_parm_decls)
    warning_at (निवेशः_location, OPT_Wmultiple_parameter_fwd_decl_lists,
		"more than one list of forward declarations of parameters");
  जइ (pedantic && !current_scope->had_forward_parm_decls)
    pedwarn (निवेशः_location, OPT_Wpedantic,
	     "ISO C forbids forward parameter declarations");

  current_scope->had_forward_parm_decls = सच्च;

  प्रति (b = current_scope->bindings; b; b = b->prev)
    जइ (वृक्षः_CODE (b->decl) == PARM_DECL)
      वृक्षः_ASM_WRITTEN (b->decl) = 1;
}

/* Build a COMPOUND_LITERAL_EXPR.  TYPE is the type given in the compound
   literal, which may be an incomplete array type completed by the
   initializer; INIT is a CONSTRUCTOR at LOC that initializes the compound
   literal.  NON_CONST is true if the initializers contain something
   that cannot occur in a constant expression.  If ALIGNAS_ALIGN is nonzero,
   it is the (valid) alignment for this compound literal, as specified
   with _Alignas.  SCSPECS are the storage class specifiers (C23) from the
   compound literal.  */

वृक्षः
build_compound_literal (location_t loc, वृक्षः type, वृक्षः init, तार्किक non_const,
			unsigned पूर्णाङ्क alignas_align,
			संरचना c_declspecs *scspecs)
{
  /* We do not use start_decl here because we have a type, not a declarator;
     and do not use finish_decl because the decl should be stored inside
     the COMPOUND_LITERAL_EXPR rather than added elsewhere as a DECL_EXPR.  */
  वृक्षः decl;
  वृक्षः complit;
  वृक्षः stmt;
  तार्किक threadp = scspecs ? scspecs->thread_p : मिच्छ;
  गणना c_storage_class storage_class = (scspecs
					? scspecs->storage_class
					: csc_none);

  जइ (type == error_mark_ग्रन्थिः
      || init == error_mark_ग्रन्थिः)
    प्रत्यागम error_mark_ग्रन्थिः;

  जइ (current_scope == file_scope && storage_class == csc_register)
    {
      error_at (loc, "file-scope compound literal specifies %<register%>");
      storage_class = csc_none;
    }

  जइ (current_scope != file_scope && threadp && storage_class == csc_none)
    {
      error_at (loc, "compound literal implicitly auto and declared %qs",
		scspecs->thread_gnu_p ? "__thread" : "_Thread_local");
      threadp = मिच्छ;
    }

  decl = build_decl (loc, VAR_DECL, NULL_वृक्षः, type);
  DECL_EXTERNAL (decl) = 0;
  वृक्षः_PUBLIC (decl) = 0;
  वृक्षः_STATIC (decl) = (current_scope == file_scope
			|| storage_class == csc_static);
  DECL_CONTEXT (decl) = current_function_decl;
  वृक्षः_USED (decl) = 1;
  DECL_READ_P (decl) = 1;
  DECL_ARTIFICIAL (decl) = 1;
  DECL_IGNORED_P (decl) = 1;
  C_DECL_COMPOUND_LITERAL_P (decl) = 1;
  C_DECL_DECLARED_CONSTEXPR (decl) = scspecs && scspecs->constexpr_p;
  वृक्षः_TYPE (decl) = type;
  जइ (threadp)
    set_decl_tls_model (decl, decl_default_tls_model (decl));
  जइ (storage_class == csc_register)
    {
      C_DECL_REGISTER (decl) = 1;
      DECL_REGISTER (decl) = 1;
    }
  c_apply_type_quals_to_decl (TYPE_QUALS (strip_array_types (type)), decl);
  जइ (alignas_align)
    {
      SET_DECL_ALIGN (decl, alignas_align * BITS_PER_UNIT);
      DECL_USER_ALIGN (decl) = 1;
    }
  store_init_मानम् (loc, decl, init, NULL_वृक्षः);
  जइ (current_scope != file_scope
      && वृक्षः_STATIC (decl)
      && !वृक्षः_READONLY (decl)
      && DECL_DECLARED_INLINE_P (current_function_decl)
      && DECL_EXTERNAL (current_function_decl))
    record_inline_static (निवेशः_location, current_function_decl,
			  decl, csi_modifiable);

  जइ (वृक्षः_CODE (type) == ARRAY_TYPE && !COMPLETE_TYPE_P (type))
    {
      पूर्णाङ्क failure = complete_array_type (&वृक्षः_TYPE (decl),
					 DECL_INITIAL (decl), सच्च);
      /* If complete_array_type returns 3, it means that the initial value of
         the compound literal is empty.  Allow it with a pedwarn; in pre-C23
         modes, the empty initializer itself has been diagnosed if pedantic so
         does not need to be diagnosed again here.  */
      gcc_assert (failure == 0 || failure == 3);
      जइ (failure == 3 && flag_isoc23)
	pedwarn (loc, OPT_Wpedantic,
		 "array of unknown size with empty initializer");

      type = वृक्षः_TYPE (decl);
      वृक्षः_TYPE (DECL_INITIAL (decl)) = type;
      relayout_decl (decl);
    }

  जइ (type == error_mark_ग्रन्थिः || !COMPLETE_TYPE_P (type))
    {
      c_incomplete_type_error (loc, NULL_वृक्षः, type);
      प्रत्यागम error_mark_ग्रन्थिः;
    }

  जइ ((वृक्षः_STATIC (decl) || C_DECL_DECLARED_CONSTEXPR (decl))
      && C_TYPE_VARIABLE_SIZE (type))
    error_at (loc, "storage size isn%'t constant");

  जइ (वृक्षः_STATIC (decl)
      && !verify_type_context (loc, TCTX_STATIC_STORAGE, type))
    प्रत्यागम error_mark_ग्रन्थिः;

  stmt = build_stmt (DECL_SOURCE_LOCATION (decl), DECL_व्यञ्जकम्, decl);
  complit = build1 (COMPOUND_LITERAL_व्यञ्जकम्, type, stmt);
  वृक्षः_SIDE_EFFECTS (complit) = 1;

  layout_decl (decl, 0);

  जइ (वृक्षः_STATIC (decl))
    {
      /* This decl needs a name for the assembler output.  */
      set_compound_literal_name (decl);
      DECL_DEFER_OUTPUT (decl) = 1;
      DECL_COMDAT (decl) = 1;
      pushdecl (decl);
      rest_of_decl_compilation (decl, 1, 0);
    }
  अण्णहा जइ (current_function_decl && !current_scope->parm_flag)
    pushdecl (decl);

  जइ (non_const)
    {
      complit = build2 (C_MAYBE_CONST_व्यञ्जकम्, type, रिक्त, complit);
      C_MAYBE_CONST_व्यञ्जकम्_NON_CONST (complit) = 1;
    }

  प्रत्यागम complit;
}

/* Check the type of a compound literal.  Here we just check that it
   is valid for C++.  */

शून्य
check_compound_literal_type (location_t loc, संरचना c_type_name *type_name)
{
  जइ (warn_cxx_compat
      && (type_name->specs->typespec_kind == ctsk_tagdef
          || type_name->specs->typespec_kind == ctsk_tagfirstref
	  || type_name->specs->typespec_kind == ctsk_tagfirstref_attrs))
    warning_at (loc, OPT_Wc___compat,
		"defining a type in a compound literal is invalid in C++");
}

/* Performs sanity checks on the TYPE and WIDTH of the bit-field NAME,
   replacing with appropriate values if they are invalid.  */

स्थिर शून्य
check_bitfield_type_and_width (location_t loc, वृक्षः *type, वृक्षः *width,
			       वृक्षः orig_name)
{
  वृक्षः type_mv;
  unsigned पूर्णाङ्क max_width;
  unsigned HOST_WIDE_INT w;
  ध्रुव वर्ण *name = (orig_name
		      ? identifier_to_locale (IDENTIFIER_POINTER (orig_name))
		      : _("<anonymous>"));

  /* Detect and ignore out of range field width and process valid
     field widths.  */
  जइ (!INTEGRAL_TYPE_P (वृक्षः_TYPE (*width)))
    {
      error_at (loc, "bit-field %qs width not an integer constant", name);
      *width = integer_one_ग्रन्थिः;
    }
  अण्णहा
    {
      जइ (वृक्षः_CODE (*width) != INTEGER_CST)
	{
	  *width = c_fully_fold (*width, मिच्छ, रिक्त);
	  जइ (वृक्षः_CODE (*width) == INTEGER_CST)
	    pedwarn (loc, OPT_Wpedantic,
		     "bit-field %qs width not an integer constant expression",
		     name);
	}
      जइ (वृक्षः_CODE (*width) != INTEGER_CST)
	{
	  error_at (loc, "bit-field %qs width not an integer constant", name);
	  *width = integer_one_ग्रन्थिः;
	}
      constant_expression_warning (*width);
      जइ (वृक्षः_int_cst_sgn (*width) < 0)
	{
	  error_at (loc, "negative width in bit-field %qs", name);
	  *width = integer_one_ग्रन्थिः;
	}
      अण्णहा जइ (integer_zerop (*width) && orig_name)
	{
	  error_at (loc, "zero width for bit-field %qs", name);
	  *width = integer_one_ग्रन्थिः;
	}
    }

  /* Detect invalid bit-field type.  */
  जइ (वृक्षः_CODE (*type) != INTEGER_TYPE
      && वृक्षः_CODE (*type) != BOOLEAN_TYPE
      && वृक्षः_CODE (*type) != ENUMERAL_TYPE
      && वृक्षः_CODE (*type) != BITINT_TYPE)
    {
      error_at (loc, "bit-field %qs has invalid type", name);
      *type = unsigned_type_ग्रन्थिः;
    }

  जइ (TYPE_WARN_IF_NOT_ALIGN (*type))
    {
      error_at (loc, "cannot declare bit-field %qs with %<warn_if_not_aligned%> type",
		name);
      *type = unsigned_type_ग्रन्थिः;
    }

  type_mv = TYPE_MAIN_VARIANT (*type);
  जइ (!in_system_header_at (निवेशः_location)
      && type_mv != integer_type_ग्रन्थिः
      && type_mv != unsigned_type_ग्रन्थिः
      && type_mv != boolean_type_ग्रन्थिः)
    pedwarn_c90 (loc, OPT_Wpedantic,
		 "type of bit-field %qs is a GCC extension", name);

  max_width = TYPE_PRECISION (*type);

  जइ (compare_वृक्षः_int (*width, max_width) > 0)
    {
      error_at (loc, "width of %qs exceeds its type", name);
      w = max_width;
      *width = build_int_cst (integer_type_ग्रन्थिः, w);
    }
  अण्णहा
    w = वृक्षः_to_uhwi (*width);

  /* Truncation of hardbool false and true representation values is always safe:
     either the values remain different, or we'll report a problem when creating
     the narrower type.  */
  जइ (c_hardbool_type_attr (*type))
    प्रत्यागम;

  जइ (वृक्षः_CODE (*type) == ENUMERAL_TYPE)
    {
      संरचना lang_type *lt = TYPE_LANG_SPECIFIC (*type);
      जइ (!lt
	  || w < वृक्षः_int_cst_min_precision (lt->enum_min, TYPE_SIGN (*type))
	  || w < वृक्षः_int_cst_min_precision (lt->enum_max, TYPE_SIGN (*type)))
	warning_at (loc, 0, "%qs is narrower than values of its type", name);
    }
}



/* Print warning about variable length array if necessary.  */

स्थिर शून्य
warn_variable_length_array (वृक्षः name, वृक्षः size)
{
  जइ (वृक्षः_CONSTANT (size))
    {
      जइ (name)
	pedwarn_c90 (निवेशः_location, OPT_Wvla,
		     "ISO C90 forbids array %qE whose size "
		     "cannot be evaluated", name);
      अण्णहा
	pedwarn_c90 (निवेशः_location, OPT_Wvla, "ISO C90 forbids array "
		     "whose size cannot be evaluated");
    }
  अण्णहा
    {
      जइ (name)
	pedwarn_c90 (निवेशः_location, OPT_Wvla,
		     "ISO C90 forbids variable length array %qE", name);
      अण्णहा
	pedwarn_c90 (निवेशः_location, OPT_Wvla, "ISO C90 forbids variable "
		     "length array");
    }
}

/* Returns the smallest location != UNKNOWN_LOCATION in LOCATIONS,
   considering only those c_declspec_words found in LIST, which
   must be terminated by cdw_number_of_elements.  */

स्थिर location_t
smallest_type_quals_location (ध्रुव location_t *locations,
			      ध्रुव c_declspec_word *list)
{
  location_t loc = UNKNOWN_LOCATION;
  जाव (*list != cdw_सङ्ख्या_of_elements)
    {
      location_t newloc = locations[*list];
      जइ (loc == UNKNOWN_LOCATION
	  || (newloc != UNKNOWN_LOCATION && newloc < loc))
	loc = newloc;
      list++;
    }

  प्रत्यागम loc;
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
स्थिर शून्य
add_decl_व्यञ्जकम् (location_t loc, वृक्षः type, वृक्षः *व्यञ्जकम्, तार्किक set_name_p)
{
  वृक्षः bind = NULL_वृक्षः;
  जइ (व्यञ्जकम्)
    {
      bind = build3 (BIND_व्यञ्जकम्, void_type_ग्रन्थिः, NULL_वृक्षः, NULL_वृक्षः,
		     NULL_वृक्षः);
      वृक्षः_SIDE_EFFECTS (bind) = 1;
      BIND_व्यञ्जकम्_BODY (bind) = प्रक्षिप_stmt_list ();
      प्रक्षिप_scope ();
    }

  वृक्षः decl = build_decl (loc, TYPE_DECL, NULL_वृक्षः, type);
  pushdecl (decl);
  DECL_ARTIFICIAL (decl) = 1;
  add_stmt (build_stmt (DECL_SOURCE_LOCATION (decl), DECL_व्यञ्जकम्, decl));
  जइ (set_name_p)
    TYPE_NAME (type) = decl;

  जइ (bind)
    {
      निष्कासय_scope ();
      BIND_व्यञ्जकम्_BODY (bind) = निष्कासय_stmt_list (BIND_व्यञ्जकम्_BODY (bind));
      जइ (*व्यञ्जकम्)
	*व्यञ्जकम् = build2 (COMPOUND_व्यञ्जकम्, void_type_ग्रन्थिः, *व्यञ्जकम्, bind);
      अण्णहा
	*व्यञ्जकम् = bind;
    }
}


/* Add attribute "arg spec" to ATTRS corresponding to an array/VLA parameter
   declared with type TYPE.  The attribute has two arguments.  The first is
   a string that encodes the presence of the static keyword.  The second is
   the declared type of the array before adjustment, i.e. as an array type
   including the outermost bound.  */

स्थिर वृक्षः
build_arg_spec_attribute (वृक्षः type, तार्किक static_p, वृक्षः attrs)
{
  वृक्षः vbchain = वृक्षः_cons (NULL_वृक्षः, type, NULL_वृक्षः);
  वृक्षः acsstr = static_p ? build_string (7, "static") :
			   build_string (1, "");
  वृक्षः args = वृक्षः_cons (NULL_वृक्षः, acsstr, vbchain);
  वृक्षः name = get_identifier ("arg spec");
  प्रत्यागम वृक्षः_cons (name, args, attrs);
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

स्थिर वृक्षः
grokdeclarator (ध्रुव संरचना c_declarator *declarator,
		संरचना c_declspecs *declspecs,
		गणना decl_context decl_context, तार्किक initialized, वृक्षः *width,
		वृक्षः *decl_attrs, वृक्षः *व्यञ्जकम्, तार्किक *व्यञ्जकम्_const_operands,
		गणना deprecated_states deprecated_state)
{
  वृक्षः type = declspecs->type;
  तार्किक threadp = declspecs->thread_p;
  तार्किक constexprp = declspecs->constexpr_p;
  गणना c_storage_class storage_class = declspecs->storage_class;
  पूर्णाङ्क constp;
  पूर्णाङ्क restrictp;
  पूर्णाङ्क volatilep;
  पूर्णाङ्क atomicp;
  पूर्णाङ्क type_quals = TYPE_UNQUALIFIED;
  वृक्षः name = NULL_वृक्षः;
  तार्किक funcdef_flag = मिच्छ;
  तार्किक funcdef_syntax = मिच्छ;
  तार्किक size_varies = मिच्छ;
  तार्किक size_error = मिच्छ;
  वृक्षः decl_attr = declspecs->decl_attr;
  पूर्णाङ्क array_ptr_quals = TYPE_UNQUALIFIED;
  वृक्षः array_ptr_attrs = NULL_वृक्षः;
  तार्किक array_parm_static = मिच्छ;
  तार्किक array_parm_vla_unspec_p = मिच्छ;
  वृक्षः returned_attrs = NULL_वृक्षः;
  वृक्षः decl_id_attrs = NULL_वृक्षः;
  तार्किक bitfield = width != रिक्त;
  वृक्षः element_type;
  वृक्षः orig_qual_type = रिक्त;
  size_t orig_qual_indirect = 0;
  संरचना c_arg_info *arg_info = 0;
  addr_space_t as1, as2, address_space;
  location_t loc = UNKNOWN_LOCATION;
  वृक्षः व्यञ्जकम्_dummy;
  तार्किक व्यञ्जकम्_const_operands_dummy;
  गणना c_declarator_kind first_non_attr_kind;
  unsigned पूर्णाङ्क alignas_align = 0;

  जइ (type == NULL_वृक्षः)
    {
      /* This can occur for auto on a parameter in C23 mode.  Set a
	 dummy type here so subsequent code can give diagnostics for
	 this case.  */
      gcc_assert (declspecs->c23_auto_p);
      gcc_assert (decl_context == PARM);
      type = declspecs->type = integer_type_ग्रन्थिः;
    }
  जइ (वृक्षः_CODE (type) == ERROR_MARK)
    प्रत्यागम error_mark_ग्रन्थिः;
  जइ (व्यञ्जकम् == रिक्त)
    {
      व्यञ्जकम् = &व्यञ्जकम्_dummy;
      व्यञ्जकम्_dummy = NULL_वृक्षः;
    }
  जइ (व्यञ्जकम्_const_operands == रिक्त)
    व्यञ्जकम्_const_operands = &व्यञ्जकम्_const_operands_dummy;

  जइ (declspecs->व्यञ्जकम्)
    {
      जइ (*व्यञ्जकम्)
	*व्यञ्जकम् = build2 (COMPOUND_व्यञ्जकम्, वृक्षः_TYPE (declspecs->व्यञ्जकम्), *व्यञ्जकम्,
			declspecs->व्यञ्जकम्);
      अण्णहा
	*व्यञ्जकम् = declspecs->व्यञ्जकम्;
    }
  *व्यञ्जकम्_const_operands = declspecs->व्यञ्जकम्_const_operands;

  जइ (decl_context == FUNCDEF)
    funcdef_flag = सच्च, decl_context = NORMAL;

  /* Look inside a declarator for the name being declared
     and get it as an IDENTIFIER_NODE, for an error message.  */
  {
    ध्रुव संरचना c_declarator *decl = declarator;

    first_non_attr_kind = cdk_attrs;
    जाव (decl)
      विकल्प (decl->kind)
	{
	पक्ष cdk_array:
	  loc = decl->id_loc;
	  /* FALL THRU.  */

	पक्ष cdk_function:
	पक्ष cdk_pointer:
	  funcdef_syntax = (decl->kind == cdk_function);
	  जइ (first_non_attr_kind == cdk_attrs)
	    first_non_attr_kind = decl->kind;
	  decl = decl->declarator;
	  भङ्ग;

	पक्ष cdk_attrs:
	  decl = decl->declarator;
	  भङ्ग;

	पक्ष cdk_id:
	  loc = decl->id_loc;
	  जइ (decl->u.id.id)
	    name = decl->u.id.id;
	  decl_id_attrs = decl->u.id.attrs;
	  जइ (first_non_attr_kind == cdk_attrs)
	    first_non_attr_kind = decl->kind;
	  decl = 0;
	  भङ्ग;

	स्वभाव:
	  gcc_unreachable ();
	}
    जइ (name == NULL_वृक्षः)
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
  जइ (declspecs->enum_type_specifier_ref_p)
    error_at (loc, "%<enum%> underlying type may not be specified here");

  /* A function definition's declarator must have the form of
     a function declarator.  */

  जइ (funcdef_flag && !funcdef_syntax)
    प्रत्यागम NULL_वृक्षः;

  /* If this looks like a function definition, make it one,
     even if it occurs where parms are expected.
     Then store_parm_decls will reject it and not use it as a parm.  */
  जइ (decl_context == NORMAL && !funcdef_flag && current_scope->parm_flag)
    decl_context = PARM;

  जइ (deprecated_state != UNAVAILABLE_DEPRECATED_SUPPRESS)
    {
      जइ (declspecs->unavailable_p)
	error_unavailable_use (declspecs->type, declspecs->decl_attr);
      अण्णहा जइ (declspecs->deprecated_p
		&& deprecated_state != DEPRECATED_SUPPRESS)
	warn_deprecated_use (declspecs->type, declspecs->decl_attr);
    }

  जइ ((decl_context == NORMAL || decl_context == FIELD)
      && current_scope == file_scope
      && c_type_variably_modified_p (type))
    {
      जइ (name)
	error_at (loc, "variably modified %qE at file scope", name);
      अण्णहा
	error_at (loc, "variably modified field at file scope");
      type = integer_type_ग्रन्थिः;
    }

  size_varies = C_TYPE_VARIABLE_SIZE (type) != 0;

  /* Diagnose defaulting to "int".  */

  जइ (declspecs->default_int_p)
    {
      /* Issue a warning if this is an ISO C 99 program or if
	 -Wreturn-type and this is a function, or if -Wimplicit;
	 prefer the former warning since it is more explicit.  */
      जइ ((warn_implicit_int || warn_return_type > 0 || flag_isoc99)
	  && funcdef_flag)
	warn_about_return_type = 1;
      अण्णहा
	{
	  जइ (name)
	    permerror_opt (loc, OPT_Wimplicit_int,
			   "type defaults to %<int%> in declaration "
			   "of %qE", name);
	  अण्णहा
	    permerror_opt (loc, OPT_Wimplicit_int,
			   "type defaults to %<int%> in type name");
	}
    }

  /* Adjust the type if a bit-field is being declared,
     -funsigned-bitfields applied and the type is not explicitly
     "signed".  */
  जइ (bitfield && !flag_signed_bitfields && !declspecs->explicit_signed_p
      && वृक्षः_CODE (type) == INTEGER_TYPE)
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

  जइ (constp > 1)
    pedwarn_c90 (loc, OPT_Wpedantic, "duplicate %<const%>");
  जइ (restrictp > 1)
    pedwarn_c90 (loc, OPT_Wpedantic, "duplicate %<restrict%>");
  जइ (volatilep > 1)
    pedwarn_c90 (loc, OPT_Wpedantic, "duplicate %<volatile%>");
  जइ (atomicp > 1)
    pedwarn_c90 (loc, OPT_Wpedantic, "duplicate %<_Atomic%>");

  जइ (!ADDR_SPACE_GENERIC_P (as1) && !ADDR_SPACE_GENERIC_P (as2) && as1 != as2)
    error_at (loc, "conflicting named address spaces (%s vs %s)",
	      c_addr_space_name (as1), c_addr_space_name (as2));

  जइ ((वृक्षः_CODE (type) == ARRAY_TYPE
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
  जइ (type_quals != TYPE_QUALS (element_type))
    orig_qual_type = NULL_वृक्षः;

  /* Applying the _Atomic qualifier to an array type (through the use
     of typedefs or typeof) must be detected here.  If the qualifier
     is introduced later, any appearance of applying it to an array is
     actually applying it to an element of that array.  */
  जइ (declspecs->atomic_p && वृक्षः_CODE (type) == ARRAY_TYPE)
    error_at (loc, "%<_Atomic%>-qualified array type");

  /* Warn about storage classes that are invalid for certain
     kinds of declarations (parameters, typenames, etc.).  */

  जइ (funcdef_flag
      && (threadp
	  || constexprp
	  || storage_class == csc_auto
	  || storage_class == csc_register
	  || storage_class == csc_typedef))
    {
      जइ (storage_class == csc_auto)
	pedwarn (loc,
		 (current_scope == file_scope) ? 0 : OPT_Wpedantic,
		 "function definition declared %<auto%>");
      जइ (storage_class == csc_register)
	error_at (loc, "function definition declared %<register%>");
      जइ (storage_class == csc_typedef)
	error_at (loc, "function definition declared %<typedef%>");
      जइ (threadp)
	error_at (loc, "function definition declared %qs",
		  declspecs->thread_gnu_p ? "__thread" : "_Thread_local");
      threadp = मिच्छ;
      /* The parser ensures a constexpr function definition never
	 reaches here.  */
      gcc_assert (!constexprp);
      जइ (storage_class == csc_auto
	  || storage_class == csc_register
	  || storage_class == csc_typedef)
	storage_class = csc_none;
    }
  अण्णहा जइ (decl_context != NORMAL && (storage_class != csc_none
				      || threadp
				      || constexprp
				      || declspecs->c23_auto_p))
    {
      जइ (decl_context == PARM
	  && storage_class == csc_register
	  && !constexprp
	  && !declspecs->c23_auto_p)
	;
      अण्णहा
	{
	  विकल्प (decl_context)
	    {
	    पक्ष FIELD:
	      जइ (name)
		error_at (loc, "storage class specified for structure "
		    	  "field %qE", name);
	      अण्णहा
		error_at (loc, "storage class specified for structure field");
	      भङ्ग;
	    पक्ष PARM:
	      जइ (name)
		error_at (loc, "storage class specified for parameter %qE",
		    	  name);
	      अण्णहा
		error_at (loc, "storage class specified for unnamed parameter");
	      भङ्ग;
	    स्वभाव:
	      error_at (loc, "storage class specified for typename");
	      भङ्ग;
	    }
	  storage_class = csc_none;
	  threadp = मिच्छ;
	  constexprp = मिच्छ;
	}
    }
  अण्णहा जइ (storage_class == csc_extern
	   && initialized
	   && !funcdef_flag)
    {
      /* 'extern' with initialization is invalid if not at file scope.  */
       जइ (current_scope == file_scope)
         {
           /* It is fine to have 'extern const' when compiling at C
              and C++ intersection.  */
           जइ (!(warn_cxx_compat && constp))
             warning_at (loc, 0, "%qE initialized and declared %<extern%>",
		 	 name);
         }
      अण्णहा
	error_at (loc, "%qE has both %<extern%> and initializer", name);
    }
  अण्णहा जइ (current_scope == file_scope)
    {
      जइ (storage_class == csc_auto)
	error_at (loc, "file-scope declaration of %qE specifies %<auto%>",
	    	  name);
      जइ (pedantic && storage_class == csc_register)
	pedwarn (निवेशः_location, OPT_Wpedantic,
		 "file-scope declaration of %qE specifies %<register%>", name);
    }
  अण्णहा
    {
      जइ (storage_class == csc_extern && funcdef_flag)
	error_at (loc, "nested function %qE declared %<extern%>", name);
      अण्णहा जइ (threadp && storage_class == csc_none)
	{
	  error_at (loc, "function-scope %qE implicitly auto and declared "
		    "%qs", name,
		    declspecs->thread_gnu_p ? "__thread" : "_Thread_local");
	  threadp = मिच्छ;
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

  जाव (declarator && declarator->kind != cdk_id)
    {
      जइ (type == error_mark_ग्रन्थिः)
	{
	  declarator = declarator->declarator;
	  अनुवर्त;
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

      जइ (array_ptr_quals != TYPE_UNQUALIFIED
	  || array_ptr_attrs != NULL_वृक्षः
	  || array_parm_static)
	{
	  /* Only the innermost declarator (making a parameter be of
	     array type which is converted to pointer type)
	     may have static or type qualifiers.  */
	  error_at (loc, "static or type qualifiers in non-parameter array declarator");
	  array_ptr_quals = TYPE_UNQUALIFIED;
	  array_ptr_attrs = NULL_वृक्षः;
	  array_parm_static = मिच्छ;
	}

      विकल्प (declarator->kind)
	{
	पक्ष cdk_attrs:
	  {
	    /* A declarator with embedded attributes.  */
	    वृक्षः attrs = declarator->u.attrs;
	    ध्रुव संरचना c_declarator *inner_decl;
	    पूर्णाङ्क attr_flags = 0;
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
	    जाव (inner_decl->kind == cdk_attrs)
	      inner_decl = inner_decl->declarator;
	    जइ (!cxx11_attribute_p (attrs))
	      {
		जइ (inner_decl->kind == cdk_id)
		  attr_flags |= (पूर्णाङ्क) ATTR_FLAG_DECL_NEXT;
		अण्णहा जइ (inner_decl->kind == cdk_function)
		  attr_flags |= (पूर्णाङ्क) ATTR_FLAG_FUNCTION_NEXT;
		अण्णहा जइ (inner_decl->kind == cdk_array)
		  attr_flags |= (पूर्णाङ्क) ATTR_FLAG_ARRAY_NEXT;
	      }
	    attrs = c_warn_type_attributes (type, attrs);
	    returned_attrs = decl_attributes (&type,
					      chainon (returned_attrs, attrs),
					      attr_flags);
	    भङ्ग;
	  }
	पक्ष cdk_array:
	  {
	    वृक्षः itype = NULL_वृक्षः;
	    वृक्षः size = declarator->u.array.dimen;
	    /* The index is a signed object `sizetype' bits wide.  */
	    वृक्षः index_type = c_common_signed_type (sizetype);

	    array_ptr_quals = declarator->u.array.quals;
	    array_ptr_attrs = declarator->u.array.attrs;
	    array_parm_static = declarator->u.array.static_p;
	    array_parm_vla_unspec_p = declarator->u.array.vla_unspec_p;

	    declarator = declarator->declarator;

	    तार्किक flexible_array_member = मिच्छ;

	    /* Check for some types that there cannot be arrays of.  */

	    जइ (VOID_TYPE_P (type))
	      {
		जइ (name)
		  error_at (loc, "declaration of %qE as array of voids", name);
		अण्णहा
		  error_at (loc, "declaration of type name as array of voids");
		type = error_mark_ग्रन्थिः;
	      }

	    जइ (वृक्षः_CODE (type) == FUNCTION_TYPE)
	      {
		जइ (name)
		  error_at (loc, "declaration of %qE as array of functions",
		      	    name);
		अण्णहा
		  error_at (loc, "declaration of type name as array of "
		            "functions");
		type = error_mark_ग्रन्थिः;
	      }

	    जइ (pedantic && !in_system_header_at (निवेशः_location)
		&& flexible_array_type_p (type))
	      pedwarn (loc, OPT_Wpedantic,
		       "invalid use of structure with flexible array member");

	    जइ (size == error_mark_ग्रन्थिः)
	      type = error_mark_ग्रन्थिः;

	    जइ (type == error_mark_ग्रन्थिः)
	      अनुवर्त;

	    जइ (!verify_type_context (loc, TCTX_ARRAY_ELEMENT, type))
	      {
		type = error_mark_ग्रन्थिः;
		अनुवर्त;
	      }

	    /* If size was specified, set ITYPE to a range-type for
	       that size.  Otherwise, ITYPE remains null.  finish_decl
	       may figure it out from an initial value.  */

	    जइ (size)
	      {
		तार्किक size_maybe_const = सच्च;
		तार्किक size_int_const = (वृक्षः_CODE (size) == INTEGER_CST
				       && !वृक्षः_OVERFLOW (size));
		तार्किक this_size_varies = मिच्छ;

		/* Strip NON_LVALUE_EXPRs since we aren't using as an
		   lvalue.  */
		STRIP_TYPE_NOPS (size);

		जइ (!INTEGRAL_TYPE_P (वृक्षः_TYPE (size)))
		  {
		    जइ (name)
		      error_at (loc, "size of array %qE has non-integer type",
				name);
		    अण्णहा
		      error_at (loc,
				"size of unnamed array has non-integer type");
		    size = integer_one_ग्रन्थिः;
		    size_int_const = सच्च;
		    size_error = सच्च;
		  }
		/* This can happen with enum forward declaration.  */
		अण्णहा जइ (!COMPLETE_TYPE_P (वृक्षः_TYPE (size)))
		  {
		    जइ (name)
		      error_at (loc, "size of array %qE has incomplete type",
				name);
		    अण्णहा
		      error_at (loc, "size of unnamed array has incomplete "
				"type");
		    size = integer_one_ग्रन्थिः;
		    size_int_const = सच्च;
		    size_error = सच्च;
		  }

		size = c_fully_fold (size, मिच्छ, &size_maybe_const);

		जइ (pedantic && size_maybe_const && integer_zerop (size))
		  {
		    जइ (name)
		      pedwarn (loc, OPT_Wpedantic,
			       "ISO C forbids zero-size array %qE", name);
		    अण्णहा
		      pedwarn (loc, OPT_Wpedantic,
			       "ISO C forbids zero-size array");
		  }

		जइ (वृक्षः_CODE (size) == INTEGER_CST && size_maybe_const)
		  {
		    constant_expression_warning (size);
		    जइ (वृक्षः_int_cst_sgn (size) < 0)
		      {
			जइ (name)
			  error_at (loc, "size of array %qE is negative", name);
			अण्णहा
			  error_at (loc, "size of unnamed array is negative");
			size = integer_one_ग्रन्थिः;
			size_int_const = सच्च;
			size_error = सच्च;
		      }
		    /* Handle a size folded to an integer constant but
		       not an integer constant expression.  */
		    जइ (!size_int_const)
		      {
			/* If this is a file scope declaration of an
			   ordinary identifier, this is invalid code;
			   diagnosing it here and not subsequently
			   treating the type as variable-length avoids
			   more confusing diagnostics later.  */
			जइ ((decl_context == NORMAL || decl_context == FIELD)
			    && current_scope == file_scope)
			  pedwarn (निवेशः_location, 0,
				   "variably modified %qE at file scope",
				   name);
			अण्णहा
			  this_size_varies = size_varies = सच्च;
			warn_variable_length_array (name, size);
		      }
		  }
		अण्णहा जइ ((decl_context == NORMAL || decl_context == FIELD)
			 && current_scope == file_scope)
		  {
		    error_at (loc, "variably modified %qE at file scope", name);
		    size = integer_one_ग्रन्थिः;
		  }
		अण्णहा
		  {
		    /* Make sure the array size remains visibly
		       nonconstant even if it is (eg) a const variable
		       with known value.  */
		    this_size_varies = size_varies = सच्च;
		    warn_variable_length_array (name, size);
		    जइ (sanitize_flags_p (SANITIZE_VLA)
			&& current_function_decl != NULL_वृक्षः
			&& decl_context == NORMAL)
		      {
			/* Evaluate the array size only once.  */
			size = save_व्यञ्जकम् (size);
			size = c_fully_fold (size, मिच्छ, रिक्त);
		        size = fold_build2 (COMPOUND_व्यञ्जकम्, वृक्षः_TYPE (size),
					    ubsan_instrument_vla (loc, size),
					    size);
		      }
		  }

		जइ (integer_zerop (size) && !this_size_varies)
		  {
		    /* A zero-length array cannot be represented with
		       an unsigned index type, which is what we'll
		       get with build_index_type.  Create an
		       open-ended range instead.  */
		    itype = build_index_type (NULL_वृक्षः);
		  }
		अण्णहा
		  {
		    /* Arrange for the SAVE_EXPR on the inside of the
		       MINUS_EXPR, which allows the -1 to get folded
		       with the +1 that happens when building TYPE_SIZE.  */
		    जइ (size_varies)
		      size = save_व्यञ्जकम् (size);
		    जइ (this_size_varies && वृक्षः_CODE (size) == INTEGER_CST)
		      size = build2 (COMPOUND_व्यञ्जकम्, वृक्षः_TYPE (size),
				     integer_zero_ग्रन्थिः, size);

		    /* Compute the maximum valid index, that is, size
		       - 1.  Do the calculation in index_type, so that
		       if it is a variable the computations will be
		       done in the proper mode.  */
		    itype = fold_build2_loc (loc, MINUS_व्यञ्जकम्, index_type,
					     convert (index_type, size),
					     convert (index_type,
						      size_one_ग्रन्थिः));

		    /* The above overflows when size does not fit
		       in index_type.
		       ???  While a size of INT_MAX+1 technically shouldn't
		       cause an overflow (because we subtract 1), handling
		       this case seems like an unnecessary complication.  */
		    जइ (वृक्षः_CODE (size) == INTEGER_CST
			&& !int_fits_type_p (size, index_type))
		      {
			जइ (name)
			  error_at (loc, "size of array %qE is too large",
			            name);
			अण्णहा
			  error_at (loc, "size of unnamed array is too large");
			type = error_mark_ग्रन्थिः;
			अनुवर्त;
		      }

		    itype = build_index_type (itype);
		  }
		जइ (this_size_varies)
		  {
		    जइ (वृक्षः_SIDE_EFFECTS (size))
		      {
			जइ (*व्यञ्जकम्)
			  *व्यञ्जकम् = build2 (COMPOUND_व्यञ्जकम्, वृक्षः_TYPE (size),
					  *व्यञ्जकम्, size);
			अण्णहा
			  *व्यञ्जकम् = size;
		      }
		    *व्यञ्जकम्_const_operands &= size_maybe_const;
		  }
	      }
	    अण्णहा जइ (decl_context == FIELD)
	      {
		जइ (array_parm_vla_unspec_p)
		  /* Field names can in fact have function prototype
		     scope so [*] is disallowed here through making
		     the field variably modified, not through being
		     something other than a declaration with function
		     prototype scope.  */
		  size_varies = सच्च;
		अण्णहा
		  {
		    ध्रुव संरचना c_declarator *t = declarator;
		    जाव (t->kind == cdk_attrs)
		      t = t->declarator;
		    flexible_array_member = (t->kind == cdk_id);
		  }
		जइ (flexible_array_member
		    && !in_system_header_at (निवेशः_location))
		  pedwarn_c90 (loc, OPT_Wpedantic, "ISO C90 does not "
			       "support flexible array members");

		/* ISO C99 Flexible array members are effectively
		   identical to GCC's zero-length array extension.  */
		जइ (flexible_array_member)
		  itype = build_index_type (NULL_वृक्षः);
	      }

	    /* Complain about arrays of incomplete types.  */
	    जइ (!COMPLETE_TYPE_P (type))
	      {
		auto_diagnostic_group d;
		error_at (loc, "array type has incomplete element type %qT",
			  type);
		/* See if we can be more helpful.  */
		जइ (वृक्षः_CODE (type) == ARRAY_TYPE)
		  {
		    जइ (name)
		      inform (loc, "declaration of %qE as multidimensional "
			      "array must have bounds for all dimensions "
			      "except the first", name);
		    अण्णहा
		      inform (loc, "declaration of multidimensional array "
			      "must have bounds for all dimensions except "
			      "the first");
		  }
		type = error_mark_ग्रन्थिः;
	      }
	    अण्णहा
	    /* When itype is NULL, a shared incomplete array type is
	       returned for all array of a given type.  Elsewhere we
	       make sure we don't complete that type before copying
	       it, but here we want to make sure we don't ever
	       modify the shared type, so we gcc_assert (itype)
	       below.  */
	      {
		addr_space_t as = DECODE_QUAL_ADDR_SPACE (type_quals);
		जइ (!ADDR_SPACE_GENERIC_P (as) && as != TYPE_ADDR_SPACE (type))
		  type = c_build_qualified_type (type,
						 ENCODE_QUAL_ADDR_SPACE (as));
		जइ (array_parm_vla_unspec_p)
		  type = c_build_array_type_unspecified (type);
		/* The GCC extension for zero-length arrays differs from
		   ISO flexible array members in that sizeof yields
		   zero.  */
		अण्णहा जइ (size && integer_zerop (size))
		  type = c_build_array_type_zero_size (type);
		अण्णहा
		  type = c_build_array_type (type, itype);

		जइ (!valid_array_size_p (loc, type, name))
		  type = error_mark_ग्रन्थिः;
	      }

	    जइ (array_parm_vla_unspec_p)
	      {
		/* C99 6.7.5.2p4 */
		जइ (decl_context == TYPENAME)
		  warning (0, "%<[*]%> not in a declaration");
		अण्णहा जइ (decl_context != GENERIC_ASSOC
			 && decl_context != PARM
			 && decl_context != FIELD)
		  {
		    error ("%<[*]%> not allowed in other than function prototype scope "
			   "or generic association");
		    type = error_mark_ग्रन्थिः;
		  }
		size_varies = सच्च;
	      }


	    gcc_assert (type == error_mark_ग्रन्थिः
			|| flexible_array_member
			   == flexible_array_member_type_p (type));

	    जइ (decl_context != PARM
		&& (array_ptr_quals != TYPE_UNQUALIFIED
		    || array_ptr_attrs != NULL_वृक्षः
		    || array_parm_static))
	      {
		error_at (loc, "static or type qualifiers in non-parameter "
			  "array declarator");
		array_ptr_quals = TYPE_UNQUALIFIED;
		array_ptr_attrs = NULL_वृक्षः;
		array_parm_static = मिच्छ;
	      }
	    orig_qual_indirect++;
	    भङ्ग;
	  }
	पक्ष cdk_function:
	  {
	    /* Say it's a definition only for the declarator closest
	       to the identifier, apart possibly from some
	       attributes.  */
	    तार्किक really_funcdef = मिच्छ;
	    वृक्षः arg_types;
	    orig_qual_type = NULL_वृक्षः;
	    जइ (funcdef_flag)
	      {
		ध्रुव संरचना c_declarator *t = declarator->declarator;
		जाव (t->kind == cdk_attrs)
		  t = t->declarator;
		really_funcdef = (t->kind == cdk_id);
	      }

	    /* Declaring a function type.  Make sure we have a valid
	       type for the function to return.  */
	    जइ (type == error_mark_ग्रन्थिः)
	      अनुवर्त;

	    size_varies = मिच्छ;

	    /* Warn about some types functions can't return.  */
	    जइ (वृक्षः_CODE (type) == FUNCTION_TYPE)
	      {
		जइ (name)
		  error_at (loc, "%qE declared as function returning a "
		      		 "function", name);
		अण्णहा
		  error_at (loc, "type name declared as function "
			    "returning a function");
		type = integer_type_ग्रन्थिः;
	      }
	    जइ (वृक्षः_CODE (type) == ARRAY_TYPE)
	      {
		जइ (name)
		  error_at (loc, "%qE declared as function returning an array",
		      	    name);
		अण्णहा
		  error_at (loc, "type name declared as function returning "
		      	    "an array");
		type = integer_type_ग्रन्थिः;
	      }

	    /* Construct the function type and go to the next
	       inner layer of declarator.  */
	    arg_info = declarator->u.arg_info;
	    arg_types = grokparms (arg_info, really_funcdef);

	    /* Type qualifiers before the return type of the function
	       qualify the return type, not the function type.  */
	    जइ (type_quals)
	      {
		ध्रुव गणना c_declspec_word ignored_quals_list[] =
		  {
		    cdw_const, cdw_volatile, cdw_restrict, cdw_address_space,
		    cdw_atomic, cdw_सङ्ख्या_of_elements
		  };
		location_t specs_loc
		  = smallest_type_quals_location (declspecs->locations,
						  ignored_quals_list);
		जइ (specs_loc == UNKNOWN_LOCATION)
		  specs_loc = declspecs->locations[cdw_typedef];
		जइ (specs_loc == UNKNOWN_LOCATION)
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
		पूर्णाङ्क quals_used = type_quals;
		जइ (flag_isoc23)
		  quals_used = 0;
		अण्णहा जइ (flag_isoc11)
		  quals_used &= TYPE_QUAL_ATOMIC;
		जइ (quals_used && VOID_TYPE_P (type) && really_funcdef)
		  pedwarn (specs_loc, 0,
			   "function definition has qualified void "
			   "return type");
		अण्णहा
		  warning_at (specs_loc, OPT_Wignored_qualifiers,
			      "type qualifiers ignored on function "
			      "return type");

		/* Ensure an error for restrict on invalid types; the
		   DR#423 resolution is not entirely clear about
		   this.  */
		जइ (flag_isoc11
		    && (type_quals & TYPE_QUAL_RESTRICT)
		    && (!POINTER_TYPE_P (type)
			|| !C_TYPE_OBJECT_OR_INCOMPLETE_P (वृक्षः_TYPE (type))))
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
	    भङ्ग;
	  }
	पक्ष cdk_pointer:
	  {
	    /* Merge any constancy or volatility into the target type
	       for the pointer.  */
	    जइ ((type_quals & TYPE_QUAL_ATOMIC)
		&& वृक्षः_CODE (type) == FUNCTION_TYPE)
	      {
		error_at (loc,
			  "%<_Atomic%>-qualified function type");
		type_quals &= ~TYPE_QUAL_ATOMIC;
	      }
	    अण्णहा जइ (pedantic && वृक्षः_CODE (type) == FUNCTION_TYPE
		     && type_quals)
	      pedwarn (loc, OPT_Wpedantic,
		       "ISO C forbids qualified function types");
	    जइ (type_quals)
	      type = c_build_qualified_type (type, type_quals, orig_qual_type,
					     orig_qual_indirect);
	    orig_qual_type = NULL_वृक्षः;
	    size_varies = मिच्छ;

	    /* When the pointed-to type involves components of variable size,
	       care must be taken to ensure that the size evaluation code is
	       emitted early enough to dominate all the possible later uses
	       and late enough for the variables on which it depends to have
	       been assigned.

	       This is expected to happen automatically when the pointed-to
	       type has a name/declaration of it's own, but special attention
	       is required if the type is anonymous. */
	    जइ (!TYPE_NAME (type) && c_type_variably_modified_p (type))
	      {
		तार्किक bind_p = decl_context == TYPENAME
			      || decl_context == FIELD
			      || decl_context == PARM;
		add_decl_व्यञ्जकम् (loc, type, bind_p ? व्यञ्जकम् : रिक्त, सच्च);
	      }

	    type = c_build_pointer_type (type);

	    /* Process type qualifiers (such as const or volatile)
	       that were given inside the `*'.  */
	    type_quals = declarator->u.pointer_quals;

	    declarator = declarator->declarator;
	    भङ्ग;
	  }
	स्वभाव:
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
  जइ (!ADDR_SPACE_GENERIC_P (address_space))
    {
      जइ (decl_context == NORMAL)
	{
	  विकल्प (storage_class)
	    {
	    पक्ष csc_auto:
	      error ("%qs combined with %<auto%> qualifier for %qE",
		     c_addr_space_name (address_space), name);
	      भङ्ग;
	    पक्ष csc_register:
	      error ("%qs combined with %<register%> qualifier for %qE",
		     c_addr_space_name (address_space), name);
	      भङ्ग;
	    पक्ष csc_none:
	      जइ (current_function_scope)
		{
		  error ("%qs specified for auto variable %qE",
			 c_addr_space_name (address_space), name);
		  भङ्ग;
		}
	      भङ्ग;
	    पक्ष csc_static:
	    पक्ष csc_extern:
	    पक्ष csc_typedef:
	      भङ्ग;
	    स्वभाव:
	      gcc_unreachable ();
	    }
	}
      अण्णहा जइ (decl_context == PARM && वृक्षः_CODE (type) != ARRAY_TYPE)
	{
	  जइ (name)
	    error ("%qs specified for parameter %qE",
		   c_addr_space_name (address_space), name);
	  अण्णहा
	    error ("%qs specified for unnamed parameter",
		   c_addr_space_name (address_space));
	}
      अण्णहा जइ (decl_context == FIELD)
	{
	  जइ (name)
	    error ("%qs specified for structure field %qE",
		   c_addr_space_name (address_space), name);
	  अण्णहा
	    error ("%qs specified for structure field",
		   c_addr_space_name (address_space));
	}
    }

  /* Check the type and width of a bit-field.  */
  जइ (bitfield)
    {
      check_bitfield_type_and_width (loc, &type, width, name);
      /* C11 makes it implementation-defined (6.7.2.1#5) whether
	 atomic types are permitted for bit-fields; we have no code to
	 make bit-field accesses atomic, so disallow them.  */
      जइ (type_quals & TYPE_QUAL_ATOMIC)
	{
	  जइ (name)
	    error_at (loc, "bit-field %qE has atomic type", name);
	  अण्णहा
	    error_at (loc, "bit-field has atomic type");
	  type_quals &= ~TYPE_QUAL_ATOMIC;
	}
    }

  /* Reject invalid uses of _Alignas.  */
  जइ (declspecs->alignas_p)
    {
      जइ (storage_class == csc_typedef)
	error_at (loc, "alignment specified for typedef %qE", name);
      अण्णहा जइ (storage_class == csc_register)
	error_at (loc, "alignment specified for %<register%> object %qE",
		  name);
      अण्णहा जइ (decl_context == PARM)
	{
	  जइ (name)
	    error_at (loc, "alignment specified for parameter %qE", name);
	  अण्णहा
	    error_at (loc, "alignment specified for unnamed parameter");
	}
      अण्णहा जइ (bitfield)
	{
	  जइ (name)
	    error_at (loc, "alignment specified for bit-field %qE", name);
	  अण्णहा
	    error_at (loc, "alignment specified for unnamed bit-field");
	}
      अण्णहा जइ (वृक्षः_CODE (type) == FUNCTION_TYPE)
	error_at (loc, "alignment specified for function %qE", name);
      अण्णहा जइ (declspecs->align_log != -1 && TYPE_P (type))
	{
	  alignas_align = 1U << declspecs->align_log;
	  जइ (alignas_align < min_align_of_type (type))
	    {
	      जइ (name)
		error_at (loc, "%<_Alignas%> specifiers cannot reduce "
			  "alignment of %qE", name);
	      अण्णहा
		error_at (loc, "%<_Alignas%> specifiers cannot reduce "
			  "alignment of unnamed field");
	      alignas_align = 0;
	    }
	}
    }

  /* If this is declaring a typedef name, return a TYPE_DECL.  */

  जइ (storage_class == csc_typedef)
    {
      वृक्षः decl;
      जइ ((type_quals & TYPE_QUAL_ATOMIC)
	  && वृक्षः_CODE (type) == FUNCTION_TYPE)
	{
	  error_at (loc,
		    "%<_Atomic%>-qualified function type");
	  type_quals &= ~TYPE_QUAL_ATOMIC;
	}
      अण्णहा जइ (pedantic && वृक्षः_CODE (type) == FUNCTION_TYPE
	       && type_quals)
	pedwarn (loc, OPT_Wpedantic,
		 "ISO C forbids qualified function types");
      जइ (type_quals)
	type = c_build_qualified_type (type, type_quals, orig_qual_type,
				       orig_qual_indirect);
      decl = build_decl (declarator->id_loc,
			 TYPE_DECL, declarator->u.id.id, type);
      जइ (declspecs->explicit_signed_p)
	C_TYPEDEF_EXPLICITLY_SIGNED (decl) = 1;
      जइ (declspecs->inline_p)
	pedwarn (loc, 0,"typedef %q+D declared %<inline%>", decl);
      जइ (declspecs->noreturn_p)
	pedwarn (loc, 0,"typedef %q+D declared %<_Noreturn%>", decl);

      जइ (warn_cxx_compat && declarator->u.id.id != NULL_वृक्षः)
	{
	  संरचना c_binding *b = I_TAG_BINDING (declarator->u.id.id);

	  जइ (b != रिक्त
	      && b->decl != NULL_वृक्षः
	      && (B_IN_CURRENT_SCOPE (b)
		  || (current_scope == file_scope && B_IN_EXTERNAL_SCOPE (b)))
	      && TYPE_MAIN_VARIANT (b->decl) != TYPE_MAIN_VARIANT (type))
	    {
	      auto_diagnostic_group d;
	      जइ (warning_at (declarator->id_loc, OPT_Wc___compat,
			      "using %qD as both a typedef and a tag is "
			      "invalid in C++", decl)
		  && b->locus != UNKNOWN_LOCATION)
		inform (b->locus, "originally defined here");
	    }
	}

      प्रत्यागम decl;
    }

  /* If this is a type name (such as, in a cast or sizeof),
     compute the type and return it now.  */

  जइ (decl_context == TYPENAME || decl_context == GENERIC_ASSOC)
    {
      /* Note that the grammar rejects storage classes in typenames
	 and fields.  */
      gcc_assert (storage_class == csc_none && !threadp
		  && !declspecs->inline_p && !declspecs->noreturn_p);
      जइ ((type_quals & TYPE_QUAL_ATOMIC)
	  && वृक्षः_CODE (type) == FUNCTION_TYPE)
	{
	  error_at (loc,
		    "%<_Atomic%>-qualified function type");
	  type_quals &= ~TYPE_QUAL_ATOMIC;
	}
      अण्णहा जइ (pedantic && वृक्षः_CODE (type) == FUNCTION_TYPE
	       && type_quals)
	pedwarn (loc, OPT_Wpedantic,
		 "ISO C forbids const or volatile function types");
      जइ (type_quals)
	type = c_build_qualified_type (type, type_quals, orig_qual_type,
				       orig_qual_indirect);
      प्रत्यागम type;
    }

  जइ (pedantic && decl_context == FIELD
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

  जइ (VOID_TYPE_P (type) && decl_context != PARM
      && !((decl_context != FIELD && वृक्षः_CODE (type) != FUNCTION_TYPE)
	    && (storage_class == csc_extern
		|| (current_scope == file_scope
		    && !(storage_class == csc_static
			 || storage_class == csc_register)))))
    {
      error_at (loc, "variable or field %qE declared void", name);
      type = integer_type_ग्रन्थिः;
    }

  /* Now create the decl, which may be a VAR_DECL, a PARM_DECL
     or a FUNCTION_DECL, depending on DECL_CONTEXT and TYPE.  */

  {
    वृक्षः decl;

    जइ (decl_context == PARM)
      {
	वृक्षः promoted_type;
	तार्किक array_parameter_p = मिच्छ;

	/* A parameter declared as an array of T is really a pointer to T.
	   One declared as a function is really a pointer to a function.  */

	जइ (वृक्षः_CODE (type) == ARRAY_TYPE)
	  {
	    जइ (!size_error)
	      *decl_attrs = build_arg_spec_attribute (type, array_parm_static,
						      *decl_attrs);

	    /* Transfer const-ness of array into that of type pointed to.  */
	    type = वृक्षः_TYPE (type);
	    जइ (orig_qual_type != NULL_वृक्षः)
	      {
		जइ (orig_qual_indirect == 0)
		  orig_qual_type = वृक्षः_TYPE (orig_qual_type);
		अण्णहा
		  orig_qual_indirect--;
	      }
	    जइ (type_quals)
	      type = c_build_qualified_type (type, type_quals, orig_qual_type,
					     orig_qual_indirect);

	    /* The pointed-to type may need a decl expr (see above).  */
	    जइ (!TYPE_NAME (type) && c_type_variably_modified_p (type))
	      {
		तार्किक bind_p = decl_context == TYPENAME
			      || decl_context == FIELD
			      || decl_context == PARM;
		add_decl_व्यञ्जकम् (loc, type, bind_p ? व्यञ्जकम् : रिक्त, सच्च);
	      }

	    type = c_build_pointer_type (type);
	    type_quals = array_ptr_quals;
	    जइ (type_quals)
	      type = c_build_qualified_type (type, type_quals);

	    /* We don't yet implement attributes in this context.  */
	    जइ (array_ptr_attrs != NULL_वृक्षः)
	      warning_at (loc, OPT_Wattributes,
			  "attributes in parameter array declarator ignored");

	    size_varies = मिच्छ;
	    array_parameter_p = सच्च;
	  }
	अण्णहा जइ (वृक्षः_CODE (type) == FUNCTION_TYPE)
	  {
	    जइ (type_quals & TYPE_QUAL_ATOMIC)
	      {
		error_at (loc,
			  "%<_Atomic%>-qualified function type");
		type_quals &= ~TYPE_QUAL_ATOMIC;
	      }
	    अण्णहा जइ (type_quals)
	      pedwarn (loc, OPT_Wpedantic,
		       "ISO C forbids qualified function types");
	    जइ (type_quals)
	      type = c_build_qualified_type (type, type_quals);
	    type = c_build_pointer_type (type);
	    type_quals = TYPE_UNQUALIFIED;
	  }
	अण्णहा जइ (type_quals)
	  type = c_build_qualified_type (type, type_quals);

	decl = build_decl (declarator->id_loc,
			   PARM_DECL, declarator->u.id.id, type);
	जइ (size_varies)
	  C_DECL_VARIABLE_SIZE (decl) = 1;
	C_ARRAY_PARAMETER (decl) = array_parameter_p;

	/* Compute the type actually passed in the parmlist,
	   for the case where there is no prototype.
	   (For example, shorts and chars are passed as ints.)
	   When there is a prototype, this is overridden later.  */

	जइ (type == error_mark_ग्रन्थिः)
	  promoted_type = type;
	अण्णहा
	  promoted_type = c_type_promotes_to (type);

	DECL_ARG_TYPE (decl) = promoted_type;
	जइ (declspecs->inline_p)
	  pedwarn (loc, 0, "parameter %q+D declared %<inline%>", decl);
	जइ (declspecs->noreturn_p)
	  pedwarn (loc, 0, "parameter %q+D declared %<_Noreturn%>", decl);
      }
    अण्णहा जइ (decl_context == FIELD)
      {
	/* Note that the grammar rejects storage classes in typenames
	   and fields.  */
	gcc_assert (storage_class == csc_none && !threadp
		    && !declspecs->inline_p && !declspecs->noreturn_p);

	/* Structure field.  It may not be a function.  */

	जइ (वृक्षः_CODE (type) == FUNCTION_TYPE)
	  {
	    error_at (loc, "field %qE declared as a function", name);
	    type = c_build_pointer_type (type);
	  }
	अण्णहा जइ (वृक्षः_CODE (type) != ERROR_MARK
		 && !COMPLETE_OR_UNBOUND_ARRAY_TYPE_P (type))
	  {
	    जइ (name)
	      error_at (loc, "field %qE has incomplete type", name);
	    अण्णहा
	      error_at (loc, "unnamed field has incomplete type");
	    type = error_mark_ग्रन्थिः;
	  }
	अण्णहा जइ (वृक्षः_CODE (type) == ARRAY_TYPE
		 && TYPE_DOMAIN (type) == NULL_वृक्षः)
	  {
	    /* We have a flexible array member through a typedef.
	       Set suitable range.  Whether this is a correct position
	       for a flexible array member will be determined elsewhere.  */
	    जइ (!in_system_header_at (निवेशः_location))
	      pedwarn_c90 (loc, OPT_Wpedantic, "ISO C90 does not "
			   "support flexible array members");
	    type = build_distinct_type_copy (TYPE_MAIN_VARIANT (type));
	    TYPE_DOMAIN (type) = build_index_type (NULL_वृक्षः);
	    जइ (orig_qual_indirect == 0)
	      orig_qual_type = NULL_वृक्षः;
	  }
	जइ (type != error_mark_ग्रन्थिः
	    && !verify_type_context (loc, TCTX_FIELD, type))
	  type = error_mark_ग्रन्थिः;

	type = c_build_qualified_type (type, type_quals, orig_qual_type,
				       orig_qual_indirect);
	decl = build_decl (declarator->id_loc,
			   FIELD_DECL, declarator->u.id.id, type);
	DECL_NONADDRESSABLE_P (decl) = bitfield;
	जइ (bitfield && !declarator->u.id.id)
	  DECL_PADDING_P (decl) = 1;

	जइ (size_varies)
	  C_DECL_VARIABLE_SIZE (decl) = 1;
      }
    अण्णहा जइ (वृक्षः_CODE (type) == FUNCTION_TYPE)
      {
	जइ (storage_class == csc_register || threadp || constexprp)
	  {
	    error_at (loc, "invalid storage class for function %qE", name);
	  }
	अण्णहा जइ (current_scope != file_scope)
	  {
	    /* Function declaration not at file scope.  Storage
	       classes other than `extern' are not allowed, C99
	       6.7.1p5, and `extern' makes no difference.  However,
	       GCC allows 'auto', perhaps with 'inline', to support
	       nested functions.  */
	    जइ (storage_class == csc_auto)
		pedwarn (loc, OPT_Wpedantic,
			 "invalid storage class for function %qE", name);
	    अण्णहा जइ (storage_class == csc_static)
	      {
		error_at (loc, "invalid storage class for function %qE", name);
		जइ (funcdef_flag)
		  storage_class = declspecs->storage_class = csc_none;
		अण्णहा
		  प्रत्यागम NULL_वृक्षः;
	      }
	  }

	decl = build_decl (declarator->id_loc,
			   FUNCTION_DECL, declarator->u.id.id, type);
	decl = build_decl_attribute_variant (decl, decl_attr);

	जइ (type_quals & TYPE_QUAL_ATOMIC)
	  {
	    error_at (loc,
		      "%<_Atomic%>-qualified function type");
	    type_quals &= ~TYPE_QUAL_ATOMIC;
	  }
	अण्णहा जइ (pedantic && type_quals && !DECL_IN_SYSTEM_HEADER (decl))
	  pedwarn (loc, OPT_Wpedantic,
		   "ISO C forbids qualified function types");

	/* Every function declaration is an external reference
	   (DECL_EXTERNAL) except for those which are not at file
	   scope and are explicitly declared "auto".  This is
	   forbidden by standard C (C99 6.7.1p5) and is interpreted by
	   GCC to signify a forward declaration of a nested function.  */
	जइ (storage_class == csc_auto && current_scope != file_scope)
	  DECL_EXTERNAL (decl) = 0;
	/* In C99, a function which is declared 'inline' with 'extern'
	   is not an external reference (which is confusing).  It
	   means that the later definition of the function must be output
	   in this file, C99 6.7.4p6.  In GNU C89, a function declared
	   'extern inline' is an external reference.  */
	अण्णहा जइ (declspecs->inline_p && storage_class != csc_static)
	  DECL_EXTERNAL (decl) = ((storage_class == csc_extern)
				  == flag_gnu89_inline);
	अण्णहा
	  DECL_EXTERNAL (decl) = !initialized;

	/* Record absence of global scope for `static' or `auto'.  */
	वृक्षः_PUBLIC (decl)
	  = !(storage_class == csc_static || storage_class == csc_auto);

	/* For a function definition, record the argument information
	   block where store_parm_decls will look for it.  */
	जइ (funcdef_flag)
	  current_function_arg_info = arg_info;

	जइ (declspecs->default_int_p)
	  C_FUNCTION_IMPLICIT_INT (decl) = 1;

	/* Record presence of `inline' and `_Noreturn', if it is
	   reasonable.  */
	जइ (flag_hosted && MAIN_NAME_P (declarator->u.id.id))
	  {
	    जइ (declspecs->inline_p)
	      pedwarn (loc, 0, "cannot inline function %<main%>");
	    जइ (declspecs->noreturn_p)
	      pedwarn (loc, 0, "%<main%> declared %<_Noreturn%>");
	  }
	अण्णहा
	  {
	    जइ (declspecs->inline_p)
	      /* Record that the function is declared `inline'.  */
	      DECL_DECLARED_INLINE_P (decl) = 1;
	    जइ (declspecs->noreturn_p)
	      {
		जइ (flag_isoc99)
		  pedwarn_c99 (loc, OPT_Wpedantic,
			       "ISO C99 does not support %<_Noreturn%>");
		अण्णहा
		  pedwarn_c99 (loc, OPT_Wpedantic,
			       "ISO C90 does not support %<_Noreturn%>");
		वृक्षः_THIS_VOLATILE (decl) = 1;
	      }
	  }

	/* C99 6.2.2p7: It is invalid (compile-time undefined
	   behavior) to create an 'extern' declaration for a
	   function if there is a global declaration that is
	   'static' and the global declaration is not visible.
	   (If the static declaration _is_ currently visible,
	   the 'extern' declaration is taken to refer to that decl.) */
	जइ (!initialized
	    && वृक्षः_PUBLIC (decl)
	    && current_scope != file_scope)
	  {
	    वृक्षः global_decl  = identifier_global_मानम् (declarator->u.id.id);
	    वृक्षः visible_decl = lookup_name (declarator->u.id.id);

	    जइ (global_decl
		&& global_decl != visible_decl
		&& VAR_OR_FUNCTION_DECL_P (global_decl)
		&& !वृक्षः_PUBLIC (global_decl))
	      error_at (loc, "function previously declared %<static%> "
			"redeclared %<extern%>");
	  }
      }
    अण्णहा
      {
	/* It's a variable.  */
	/* An uninitialized decl with `extern' is a reference.  */
	पूर्णाङ्क extern_ref = !initialized && storage_class == csc_extern;

	जइ (constexprp)
	  {
	    /* The type of a constexpr variable must not be variably
	       modified, volatile, atomic or restrict qualified or
	       have a member with such a qualifier.  const
	       qualification is implicitly added, and, at file scope,
	       has internal linkage.  */
	    जइ (c_type_variably_modified_p (type))
	      error_at (loc, "%<constexpr%> object has variably modified "
			"type");
	    जइ (type_quals
		& (TYPE_QUAL_VOLATILE | TYPE_QUAL_RESTRICT | TYPE_QUAL_ATOMIC))
	      error_at (loc, "invalid qualifiers for %<constexpr%> object");
	    अण्णहा
	      {
		वृक्षः type_no_array = strip_array_types (type);
		जइ (RECORD_OR_UNION_TYPE_P (type_no_array)
		    && C_TYPE_FIELDS_NON_CONSTEXPR (type_no_array))
		  error_at (loc, "invalid qualifiers for field of "
			    "%<constexpr%> object");
	      }
	    type_quals |= TYPE_QUAL_CONST;
	    जइ (current_scope == file_scope)
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
	जइ (extern_ref && current_scope != file_scope)
	  {
	    वृक्षः global_decl  = identifier_global_मानम् (declarator->u.id.id);
	    वृक्षः visible_decl = lookup_name (declarator->u.id.id);

	    जइ (global_decl
		&& global_decl != visible_decl
		&& VAR_P (global_decl)
		&& !वृक्षः_PUBLIC (global_decl))
	      error_at (loc, "variable previously declared %<static%> "
			"redeclared %<extern%>");
	  }

	decl = build_decl (declarator->id_loc,
			   VAR_DECL, declarator->u.id.id, type);
	जइ (size_varies)
	  C_DECL_VARIABLE_SIZE (decl) = 1;
	जइ (constexprp)
	  C_DECL_DECLARED_CONSTEXPR (decl) = 1;

	जइ (declspecs->inline_p)
	  pedwarn (loc, 0, "variable %q+D declared %<inline%>", decl);
	जइ (declspecs->noreturn_p)
	  pedwarn (loc, 0, "variable %q+D declared %<_Noreturn%>", decl);

	/* At file scope, an initialized extern declaration may follow
	   a static declaration.  In that case, DECL_EXTERNAL will be
	   reset later in start_decl.  */
	DECL_EXTERNAL (decl) = (storage_class == csc_extern);

	/* At file scope, the presence of a `static' or `register' storage
	   class specifier, or the absence of all storage class specifiers
	   makes this declaration a definition (perhaps tentative).  Also,
	   the absence of `static' makes it public.  */
	जइ (current_scope == file_scope)
	  {
	    वृक्षः_PUBLIC (decl) = storage_class != csc_static;
	    वृक्षः_STATIC (decl) = !extern_ref;
	  }
	/* Not at file scope, only `static' makes a static definition.  */
	अण्णहा
	  {
	    वृक्षः_STATIC (decl) = (storage_class == csc_static);
	    वृक्षः_PUBLIC (decl) = extern_ref;
	  }

	// NB: Set a tentative TLS model to avoid tls_model attribute
	// warnings due to lack of thread storage duration.  It will
	// be updated by c_decl_attributes later.
	जइ (threadp)
	  set_decl_tls_model (decl, TLS_MODEL_REAL);
      }

    जइ ((storage_class == csc_extern
	 || (storage_class == csc_none
	     && वृक्षः_CODE (type) == FUNCTION_TYPE
	     && !funcdef_flag))
	&& c_type_variably_modified_p (type))
      {
	/* C99 6.7.5.2p2 */
	जइ (वृक्षः_CODE (type) == FUNCTION_TYPE)
	  error_at (loc, "non-nested function with variably modified type");
	अण्णहा
	  error_at (loc, "object with variably modified type must have "
	      	    "no linkage");
      }

    /* For nested functions disqualify ones taking VLAs by value
       from inlining since the middle-end cannot deal with this.
       ???  We should arrange for those to be passed by reference
       with emitting the copy on the caller side in the frontend.  */
    जइ (storage_class == csc_none
	&& वृक्षः_CODE (type) == FUNCTION_TYPE)
      प्रति (वृक्षः al = TYPE_ARG_TYPES (type); al; al = वृक्षः_CHAIN (al))
	{
	  वृक्षः arg = वृक्षः_मानम् (al);
	  जइ (arg != error_mark_ग्रन्थिः
	      && C_TYPE_VARIABLE_SIZE (arg))
	    {
	      DECL_UNINLINABLE (decl) = 1;
	      भङ्ग;
	    }
	}

    /* Record `register' declaration for warnings on &
       and in case doing stupid register allocation.  */

    जइ (storage_class == csc_register
	&& वृक्षः_CODE (type) != FUNCTION_TYPE)
      {
	C_DECL_REGISTER (decl) = 1;
	DECL_REGISTER (decl) = 1;
      }

    /* Record constancy and volatility.  */
    c_apply_type_quals_to_decl (type_quals, decl);

    /* Apply _Alignas specifiers.  */
    जइ (alignas_align)
      {
	SET_DECL_ALIGN (decl, alignas_align * BITS_PER_UNIT);
	DECL_USER_ALIGN (decl) = 1;
      }

    /* If a type has volatile components, it should be stored in memory.
       Otherwise, the fact that those components are volatile
       will be ignored, and would even crash the compiler.
       Of course, this only makes sense on  VAR,PARM, and RESULT decl's.   */
    जइ (C_TYPE_FIELDS_VOLATILE (वृक्षः_TYPE (decl))
	&& (VAR_P (decl) ||  वृक्षः_CODE (decl) == PARM_DECL
	  || वृक्षः_CODE (decl) == RESULT_DECL))
      {
	/* It is not an error for a structure with volatile fields to
	   be declared register, but reset DECL_REGISTER since it
	   cannot actually go in a register.  */
	पूर्णाङ्क was_reg = C_DECL_REGISTER (decl);
	C_DECL_REGISTER (decl) = 0;
	DECL_REGISTER (decl) = 0;
	c_mark_addressable (decl);
	C_DECL_REGISTER (decl) = was_reg;
      }

  /* This is the earliest point at which we might know the assembler
     name of a variable.  Thus, if it's known before this, die horribly.  */
    gcc_assert (!HAS_DECL_ASSEMBLER_NAME_P (decl)
		|| !DECL_ASSEMBLER_NAME_SET_P (decl));

    जइ (warn_cxx_compat
	&& VAR_P (decl)
	&& वृक्षः_PUBLIC (decl)
	&& वृक्षः_STATIC (decl)
	&& (RECORD_OR_UNION_TYPE_P (वृक्षः_TYPE (decl))
	    || वृक्षः_CODE (वृक्षः_TYPE (decl)) == ENUMERAL_TYPE)
	&& TYPE_NAME (वृक्षः_TYPE (decl)) == NULL_वृक्षः)
      warning_at (DECL_SOURCE_LOCATION (decl), OPT_Wc___compat,
		  "non-local variable %qD with anonymous type is "
		  "questionable in C++", decl);

    प्रत्यागम decl;
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

स्थिर वृक्षः
grokparms (संरचना c_arg_info *arg_info, तार्किक funcdef_flag)
{
  वृक्षः arg_types = arg_info->types;

  जइ (funcdef_flag && arg_info->had_vla_unspec)
    {
      /* A function definition isn't function prototype scope C99 6.2.1p4.  */
      /* C99 6.7.5.2p4 */
      error ("%<[*]%> not allowed in other than function prototype scope");
    }

  जइ (arg_types == NULL_वृक्षः && !funcdef_flag && !flag_isoc23
      && !in_system_header_at (निवेशः_location))
    warning (OPT_Wstrict_prototypes,
	     "function declaration isn%'t a prototype");

  जइ (arg_types == error_mark_ग्रन्थिः)
    /* Don't set TYPE_ARG_TYPES in this case.  */
    प्रत्यागम NULL_वृक्षः;

  अण्णहा जइ (arg_types && वृक्षः_CODE (वृक्षः_मानम् (arg_types)) == IDENTIFIER_ग्रन्थिः)
    {
      जइ (!funcdef_flag)
	{
	  permerror_opt (निवेशः_location,
			 OPT_Wdeclaration_missing_parameter_type,
			 "parameter names (without types) in "
			 "function declaration");
	  arg_info->parms = NULL_वृक्षः;
	}
      अण्णहा
	arg_info->parms = arg_info->types;

      arg_info->types = NULL_वृक्षः;
      प्रत्यागम NULL_वृक्षः;
    }
  अण्णहा
    {
      वृक्षः parm, type, typelt;
      unsigned पूर्णाङ्क parmno;

      /* In C23, convert () to (void).  */
      जइ (flag_isoc23
	  && !arg_types
	  && !arg_info->parms
	  && !arg_info->no_named_args_stdarg_p)
	{
	  arg_types = arg_info->types = void_list_ग्रन्थिः;
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

      प्रति (parm = arg_info->parms, typelt = arg_types, parmno = 1;
	   parm;
	   parm = DECL_CHAIN (parm), typelt = वृक्षः_CHAIN (typelt), parmno++)
	{
	  type = वृक्षः_मानम् (typelt);
	  जइ (type == error_mark_ग्रन्थिः)
	    अनुवर्त;

	  जइ (!COMPLETE_TYPE_P (type))
	    {
	      जइ (funcdef_flag)
		{
		  जइ (DECL_NAME (parm))
		    error_at (निवेशः_location,
			      "parameter %u (%q+D) has incomplete type",
			      parmno, parm);
		  अण्णहा
		    error_at (DECL_SOURCE_LOCATION (parm),
			      "parameter %u has incomplete type",
			      parmno);

		  वृक्षः_मानम् (typelt) = error_mark_ग्रन्थिः;
		  वृक्षः_TYPE (parm) = error_mark_ग्रन्थिः;
		  arg_types = NULL_वृक्षः;
		}
	    }

	  जइ (DECL_NAME (parm) && वृक्षः_USED (parm))
	    warn_if_shadowing (parm);
	}
      प्रत्यागम arg_types;
    }
}

/* Allocate and initialize a c_arg_info structure from the parser's
   obstack.  */

संरचना c_arg_info *
build_arg_info (शून्य)
{
  संरचना c_arg_info *ret = XOBNEW (&parser_obstack, संरचना c_arg_info);
  ret->parms = NULL_वृक्षः;
  ret->tags = रिक्त;
  ret->types = NULL_वृक्षः;
  ret->others = NULL_वृक्षः;
  ret->pending_sizes = रिक्त;
  ret->had_vla_unspec = 0;
  ret->no_named_args_stdarg_p = 0;
  ret->c23_empty_parens = 0;
  प्रत्यागम ret;
}

/* Take apart the current scope and return a c_arg_info structure with
   info on a parameter list just parsed.

   This structure is later fed to 'grokparms' and 'store_parm_decls'.

   ELLIPSIS being true means the argument list ended in '...' so don't
   append a sentinel (void_list_node) to the end of the type-list.

   EXPR is NULL or an expression that needs to be evaluated for the
   side effects of array size expressions in the parameters.  */

संरचना c_arg_info *
get_parm_info (तार्किक ellipsis, वृक्षः व्यञ्जकम्)
{
  संरचना c_binding *b = current_scope->bindings;
  संरचना c_arg_info *arg_info = build_arg_info ();

  वृक्षः parms = NULL_वृक्षः;
  vec<c_arg_tag, va_gc> *tags = रिक्त;
  वृक्षः types = NULL_वृक्षः;
  वृक्षः others = NULL_वृक्षः;

  तार्किक gave_void_only_once_err = मिच्छ;

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
  जइ (b->prev == 0			    /* one binding */
      && वृक्षः_CODE (b->decl) == PARM_DECL   /* which is a parameter */
      && !DECL_NAME (b->decl)               /* anonymous */
      && VOID_TYPE_P (वृक्षः_TYPE (b->decl))) /* of void type */
    {
      जइ (TYPE_QUALS (वृक्षः_TYPE (b->decl)) != TYPE_UNQUALIFIED
	  || C_DECL_REGISTER (b->decl))
	error_at (b->locus, "%<void%> as only parameter may not be qualified");

      /* There cannot be an ellipsis.  */
      जइ (ellipsis)
	error_at (b->locus, "%<void%> must be the only parameter");

      arg_info->types = void_list_ग्रन्थिः;
      प्रत्यागम arg_info;
    }

  जइ (!ellipsis)
    types = void_list_ग्रन्थिः;

  /* Break up the bindings list into parms, tags, types, and others;
     apply sanity checks; purge the name-to-decl bindings.  */
  जाव (b)
    {
      वृक्षः decl = b->decl;
      वृक्षः type = वृक्षः_TYPE (decl);
      c_arg_tag tag;
      ध्रुव वर्ण *keyword;

      विकल्प (वृक्षः_CODE (decl))
	{
	पक्ष PARM_DECL:
	  जइ (b->id)
	    {
	      gcc_assert (I_चिह्नम्_BINDING (b->id) == b);
	      I_चिह्नम्_BINDING (b->id) = b->shadowed;
	    }

	  /* Check for forward decls that never got their actual decl.  */
	  जइ (वृक्षः_ASM_WRITTEN (decl))
	    error_at (b->locus,
		      "parameter %q+D has just a forward declaration", decl);
	  /* Check for (..., void, ...) and named void parameters and issue an
	     error.  */
	  अण्णहा जइ (VOID_TYPE_P (type))
	    {
	      जइ (!gave_void_only_once_err)
		{
		  error_at (b->locus,
			    "%<void%> must be the only parameter and unnamed");
		  gave_void_only_once_err = सच्च;
		}
	    }
	  अण्णहा
	    {
	      /* Valid parameter, add it to the list.  */
	      DECL_CHAIN (decl) = parms;
	      parms = decl;

	      /* Since there is a prototype, args are passed in their
		 declared types.  The back end may override this later.  */
	      DECL_ARG_TYPE (decl) = type;
	      types = वृक्षः_cons (0, type, types);
	    }
	  भङ्ग;

	पक्ष ENUMERAL_TYPE: keyword = "enum"; गच्छ tag;
	पक्ष UNION_TYPE:    keyword = "union"; गच्छ tag;
	पक्ष RECORD_TYPE:   keyword = "struct"; गच्छ tag;
	tag:
	  /* Types may not have tag-names, in which case the type
	     appears in the bindings list with b->id NULL.  */
	  जइ (b->id)
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
	  जइ (वृक्षः_CODE (decl) != UNION_TYPE || b->id != NULL_वृक्षः)
	    {
	      जइ (b->id)
		{
		  /* The %s will be one of 'struct', 'union', or 'enum'.  */
		  जइ (!flag_isoc23 || !COMPLETE_TYPE_P (decl))
		    warning_at (b->locus, 0,
				"%<%s %E%> declared inside parameter list"
				" will not be visible outside of this definition or"
				" declaration", keyword, b->id);
		}
	      अण्णहा
		/* The %s will be one of 'struct', 'union', or 'enum'.  */
		warning_at (b->locus, 0,
			    "anonymous %s declared inside parameter list"
			    " will not be visible outside of this definition or"
			    " declaration", keyword);
	    }

	  tag.id = b->id;
	  tag.type = decl;
	  vec_safe_प्रक्षिप (tags, tag);
	  भङ्ग;

	पक्ष FUNCTION_DECL:
	  /* FUNCTION_DECLs appear when there is an implicit function
	     declaration in the parameter list.  */
	  gcc_assert (b->nested || seen_error ());
	  गच्छ set_shadowed;

	पक्ष CONST_DECL:
	पक्ष TYPE_DECL:
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

	पक्ष ERROR_MARK:
	set_shadowed:
	  /* error_mark_node appears here when we have an undeclared
	     variable.  Just throw it away.  */
	  जइ (b->id)
	    {
	      gcc_assert (I_चिह्नम्_BINDING (b->id) == b);
	      I_चिह्नम्_BINDING (b->id) = b->shadowed;
	    }
	  भङ्ग;

	  /* Other things that might be encountered.  */
	पक्ष LABEL_DECL:
	पक्ष VAR_DECL:
	स्वभाव:
	  gcc_unreachable ();
	}

      b = free_binding_and_advance (b);
    }

  arg_info->parms = parms;
  arg_info->tags = tags;
  arg_info->types = types;
  arg_info->others = others;
  arg_info->pending_sizes = व्यञ्जकम्;
  arg_info->no_named_args_stdarg_p = ellipsis && !types;
  प्रत्यागम arg_info;
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

संरचना c_typespec
parser_xref_tag (location_t loc, गणना वृक्षः_code code, वृक्षः name,
		 तार्किक have_std_attrs, वृक्षः attrs, तार्किक has_enum_type_specifier)
{
  संरचना c_typespec ret;
  वृक्षः ref;
  location_t refloc;

  ret.व्यञ्जकम् = NULL_वृक्षः;
  ret.व्यञ्जकम्_const_operands = सच्च;
  ret.has_enum_type_specifier = has_enum_type_specifier;

  /* If a cross reference is requested, look up the type already
     defined for this tag and return it.  If an enum type specifier is
     present, only a definition in the current scope is relevant.  */

  ref = lookup_tag (code, name, has_enum_type_specifier, &refloc);

  /* If the visible type is still being defined, see if there is
     an earlier definition (which may be complete).  We do not
     have to loop because nested redefinitions are not allowed.  */
  जइ (flag_isoc23 && ref && C_TYPE_BEING_DEFINED (ref))
    {
      वृक्षः vis = previous_tag (ref);
      जइ (vis)
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
  जइ (ref && वृक्षः_CODE (ref) == code)
    {
      decl_attributes (&ref, attrs, (पूर्णाङ्क) ATTR_FLAG_TYPE_IN_PLACE);
      जइ (C_TYPE_DEFINED_IN_STRUCT (ref)
	  && loc != UNKNOWN_LOCATION
	  && warn_cxx_compat)
	{
	  auto_diagnostic_group d;
	  विकल्प (code)
	    {
	    पक्ष ENUMERAL_TYPE:
	      जइ (warning_at (loc, OPT_Wc___compat,
			      ("enum type defined in struct or union "
			       "is not visible in C++")))
		  inform (refloc, "enum type defined here");
	      भङ्ग;
	    पक्ष RECORD_TYPE:
	      जइ (warning_at (loc, OPT_Wc___compat,
			      ("struct defined in struct or union "
			       "is not visible in C++")))
		inform (refloc, "struct defined here");
	      भङ्ग;
	    पक्ष UNION_TYPE:
	      जइ (warning_at (loc, OPT_Wc___compat,
			      ("union defined in struct or union "
			       "is not visible in C++")))
		inform (refloc, "union defined here");
	      भङ्ग;
	    स्वभाव:
	      gcc_unreachable();
	    }
	}

      ret.spec = ref;
      प्रत्यागम ret;
    }

  /* If no such tag is yet defined, create a forward-reference node
     and record it as the "definition".
     When a real declaration of this type is found,
     the forward-reference will be altered into a real type.  */

  ref = make_ग्रन्थिः (code);
  जइ (flag_isoc23 || code == ENUMERAL_TYPE)
    SET_TYPE_STRUCTURAL_EQUALITY (ref);
  जइ (code == ENUMERAL_TYPE)
    {
      /* Give the type a default layout like unsigned int
	 to avoid crashing if it does not get defined.  */
      SET_TYPE_MODE (ref, TYPE_MODE (unsigned_type_ग्रन्थिः));
      SET_TYPE_ALIGN (ref, TYPE_ALIGN (unsigned_type_ग्रन्थिः));
      TYPE_USER_ALIGN (ref) = 0;
      TYPE_UNSIGNED (ref) = 1;
      TYPE_PRECISION (ref) = TYPE_PRECISION (unsigned_type_ग्रन्थिः);
      TYPE_MIN_मानम् (ref) = TYPE_MIN_मानम् (unsigned_type_ग्रन्थिः);
      TYPE_MAX_मानम् (ref) = TYPE_MAX_मानम् (unsigned_type_ग्रन्थिः);
      ENUM_FIXED_UNDERLYING_TYPE_P (ref) = has_enum_type_specifier;
    }

  pushtag (loc, name, ref);
  decl_attributes (&ref, attrs, (पूर्णाङ्क) ATTR_FLAG_TYPE_IN_PLACE);
  जइ (in_underspecified_init)
    error_at (loc, "%qT declared in underspecified object initializer",
	      ref);

  ret.spec = ref;
  प्रत्यागम ret;
}

/* Get the struct, enum or union (CODE says which) with tag NAME.
   Define the tag as a forward-reference if it is not defined.
   Return a tree for the type.  */

वृक्षः
xref_tag (गणना वृक्षः_code code, वृक्षः name)
{
  प्रत्यागम parser_xref_tag (निवेशः_location, code, name, मिच्छ, NULL_वृक्षः,
			  मिच्छ).spec;
}

/* Make sure that the tag NAME is defined *in the current scope*
   at least as a forward reference.
   LOC is the location of the struct's definition.
   CODE says which kind of tag NAME ought to be.

   This stores the current value of the file static STRUCT_PARSE_INFO
   in *ENCLOSING_STRUCT_PARSE_INFO, and points STRUCT_PARSE_INFO at a
   new c_struct_parse_info structure.  The old value of
   STRUCT_PARSE_INFO is restored in finish_struct.  */

वृक्षः
start_struct (location_t loc, गणना वृक्षः_code code, वृक्षः name,
	      वर्ग c_struct_parse_info **enclosing_struct_parse_info)
{
  /* If there is already a tag defined at this scope
     (as a forward reference), just return it.  */

  वृक्षः ref = NULL_वृक्षः;
  location_t refloc = UNKNOWN_LOCATION;

  जइ (name != NULL_वृक्षः)
    ref = lookup_tag (code, name, सच्च, &refloc);

  /* For C23, even if we already have a completed definition,
     we do not use it. We will check for consistency later.
     If we are in a nested redefinition the type is not
     complete. We will then detect this below.  */
  जइ (flag_isoc23 && ref && TYPE_SIZE (ref))
    ref = NULL_वृक्षः;

  जइ (ref && वृक्षः_CODE (ref) == code)
    {
      जइ (TYPE_STUB_DECL (ref))
	refloc = DECL_SOURCE_LOCATION (TYPE_STUB_DECL (ref));

      जइ (TYPE_SIZE (ref))
	{
	  auto_diagnostic_group d;
	  जइ (code == UNION_TYPE)
	    error_at (loc, "redefinition of %<union %E%>", name);
	  अण्णहा
	    error_at (loc, "redefinition of %<struct %E%>", name);
	  जइ (refloc != UNKNOWN_LOCATION)
	    inform (refloc, "originally defined here");
	  /* Don't create structures using a name already in use.  */
	  ref = NULL_वृक्षः;
	}
      अण्णहा जइ (C_TYPE_BEING_DEFINED (ref))
	{
	  जइ (code == UNION_TYPE)
	    error_at (loc, "nested redefinition of %<union %E%>", name);
	  अण्णहा
	    error_at (loc, "nested redefinition of %<struct %E%>", name);
	  /* Don't bother to report "originally defined here" for a
	     nested redefinition; the original definition should be
	     obvious.  */
	  /* Don't create structures that contain themselves.  */
	  ref = NULL_वृक्षः;
	}
    }

  /* Otherwise create a forward-reference just so the tag is in scope.  */

  जइ (ref == NULL_वृक्षः || वृक्षः_CODE (ref) != code)
    {
      ref = make_ग्रन्थिः (code);
      जइ (flag_isoc23)
	SET_TYPE_STRUCTURAL_EQUALITY (ref);
      pushtag (loc, name, ref);
    }

  C_TYPE_BEING_DEFINED (ref) = 1;
  प्रति (वृक्षः v = TYPE_MAIN_VARIANT (ref); v; v = TYPE_NEXT_VARIANT (v))
    TYPE_PACKED (v) = flag_pack_struct;

  *enclosing_struct_parse_info = struct_parse_info;
  struct_parse_info = नूतन c_struct_parse_info ();
  struct_parse_info->refloc = refloc;

  /* FIXME: This will issue a warning for a use of a type defined
     within a statement expr used within sizeof, et. al.  This is not
     terribly serious as C++ doesn't permit statement exprs within
     sizeof anyhow.  */
  जइ (warn_cxx_compat
      && (in_sizeof || in_typeof || in_alignof || in_countof))
    warning_at (loc, OPT_Wc___compat,
		"defining type in %qs expression is invalid in C++",
		(in_sizeof ? "sizeof"
		 : in_typeof ? "typeof"
		 : in_alignof ? "alignof"
		 : "_Countof"));

  जइ (in_underspecified_init)
    error_at (loc, "%qT defined in underspecified object initializer", ref);

  प्रत्यागम ref;
}

/* Process the specs, declarator and width (NULL if omitted)
   of a structure component, returning a FIELD_DECL node.
   WIDTH is non-NULL for bit-fields only, and is an INTEGER_CST node.
   DECL_ATTRS is as for grokdeclarator.

   LOC is the location of the structure component.

   This is done during the parsing of the struct declaration.
   The FIELD_DECL nodes are chained together and the lot of them
   are ultimately passed to `build_struct' to make the RECORD_TYPE node.  */

वृक्षः
grokfield (location_t loc,
	   संरचना c_declarator *declarator, संरचना c_declspecs *declspecs,
	   वृक्षः width, वृक्षः *decl_attrs, वृक्षः *व्यञ्जकम्)
{
  वृक्षः मानम्;

  जइ (declarator->kind == cdk_id && declarator->u.id.id == NULL_वृक्षः
      && width == NULL_वृक्षः)
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

      वृक्षः type = declspecs->type;
      तार्किक ok = मिच्छ;

      जइ (RECORD_OR_UNION_TYPE_P (type)
	  && (flag_ms_extensions
	      || flag_plan9_extensions
	      || !declspecs->typedef_p))
	{
	  जइ (flag_ms_extensions || flag_plan9_extensions)
	    ok = सच्च;
	  अण्णहा जइ (TYPE_NAME (type) == रिक्त)
	    ok = सच्च;
	  अण्णहा
	    ok = मिच्छ;
	}
      जइ (!ok)
	{
	  pedwarn (loc, 0, "declaration does not declare anything");
	  प्रत्यागम NULL_वृक्षः;
	}
      जइ (flag_isoc99)
	pedwarn_c99 (loc, OPT_Wpedantic,
		     "ISO C99 doesn%'t support unnamed structs/unions");
      अण्णहा
	pedwarn_c99 (loc, OPT_Wpedantic,
		     "ISO C90 doesn%'t support unnamed structs/unions");
    }

  मानम् = grokdeclarator (declarator, declspecs, FIELD, मिच्छ,
			  width ? &width : रिक्त, decl_attrs, व्यञ्जकम्, रिक्त,
			  DEPRECATED_NORMAL);

  /* When this field has name, its type is a top level type, we should
     call verify_counted_by_for_top_anonymous_type.  */
  जइ (DECL_NAME (मानम्) != NULL_वृक्षः
      && declspecs->typespec_kind == ctsk_tagdef)
    verify_counted_by_for_शिखरम्_anonymous_type (declspecs->type);

  finish_decl (मानम्, loc, NULL_वृक्षः, NULL_वृक्षः, NULL_वृक्षः);
  DECL_INITIAL (मानम्) = width;
  जइ (width)
    SET_DECL_C_BIT_FIELD (मानम्);

  जइ (warn_cxx_compat && DECL_NAME (मानम्) != NULL_वृक्षः)
    {
      /* If we currently have a binding for this field, set the
	 in_struct field in the binding, so that we warn about lookups
	 which find it.  */
      संरचना c_binding *b = I_चिह्नम्_BINDING (DECL_NAME (मानम्));
      जइ (b != रिक्त)
	{
	  /* If the in_struct field is not yet set, push it on a list
	     to be cleared when this struct is finished.  */
	  जइ (!b->in_struct)
	    {
	      struct_parse_info->fields.safe_प्रक्षिप (b);
	      b->in_struct = 1;
	    }
	}
    }

  प्रत्यागम मानम्;
}

/* Subroutine of detect_field_duplicates: return whether X and Y,
   which are both fields in the same struct, have duplicate field
   names.  */

स्थिर तार्किक
is_duplicate_field (वृक्षः x, वृक्षः y)
{
  जइ (DECL_NAME (x) != NULL_वृक्षः && DECL_NAME (x) == DECL_NAME (y))
    प्रत्यागम सच्च;

  /* When using -fplan9-extensions, an anonymous field whose name is a
     typedef can duplicate a field name.  */
  जइ (flag_plan9_extensions
      && (DECL_NAME (x) == NULL_वृक्षः || DECL_NAME (y) == NULL_वृक्षः))
    {
      वृक्षः xt, xn, yt, yn;

      xt = वृक्षः_TYPE (x);
      जइ (DECL_NAME (x) != NULL_वृक्षः)
	xn = DECL_NAME (x);
      अण्णहा जइ (RECORD_OR_UNION_TYPE_P (xt)
	       && TYPE_NAME (xt) != NULL_वृक्षः
	       && वृक्षः_CODE (TYPE_NAME (xt)) == TYPE_DECL)
	xn = DECL_NAME (TYPE_NAME (xt));
      अण्णहा
	xn = NULL_वृक्षः;

      yt = वृक्षः_TYPE (y);
      जइ (DECL_NAME (y) != NULL_वृक्षः)
	yn = DECL_NAME (y);
      अण्णहा जइ (RECORD_OR_UNION_TYPE_P (yt)
	       && TYPE_NAME (yt) != NULL_वृक्षः
	       && वृक्षः_CODE (TYPE_NAME (yt)) == TYPE_DECL)
	yn = DECL_NAME (TYPE_NAME (yt));
      अण्णहा
	yn = NULL_वृक्षः;

      जइ (xn != NULL_वृक्षः && xn == yn)
	प्रत्यागम सच्च;
    }

  प्रत्यागम मिच्छ;
}

/* Subroutine of detect_field_duplicates: add the fields of FIELDLIST
   to HTAB, giving errors for any duplicates.  */

स्थिर शून्य
detect_field_duplicates_hash (वृक्षः fieldlist,
			      hash_table<nofree_ptr_hash <वृक्ष_ग्रन्थिः> > *htab)
{
  वृक्षः x, y;
  वृक्ष_ग्रन्थिः **slot;

  प्रति (x = fieldlist; x ; x = DECL_CHAIN (x))
    जइ ((y = DECL_NAME (x)) != NULL_वृक्षः)
      {
	slot = htab->find_slot (y, निवेशय);
	जइ (*slot)
	  {
	    error ("duplicate member %q+D", x);
	    DECL_NAME (x) = NULL_वृक्षः;
	  }
	*slot = y;
      }
    अण्णहा जइ (RECORD_OR_UNION_TYPE_P (वृक्षः_TYPE (x)))
      {
	detect_field_duplicates_hash (TYPE_FIELDS (वृक्षः_TYPE (x)), htab);

	/* When using -fplan9-extensions, an anonymous field whose
	   name is a typedef can duplicate a field name.  */
	जइ (flag_plan9_extensions
	    && TYPE_NAME (वृक्षः_TYPE (x)) != NULL_वृक्षः
	    && वृक्षः_CODE (TYPE_NAME (वृक्षः_TYPE (x))) == TYPE_DECL)
	  {
	    वृक्षः xn = DECL_NAME (TYPE_NAME (वृक्षः_TYPE (x)));
	    slot = htab->find_slot (xn, निवेशय);
	    जइ (*slot)
	      error ("duplicate member %q+D", TYPE_NAME (वृक्षः_TYPE (x)));
	    *slot = xn;
	  }
      }
}

/* Generate an error for any duplicate field names in FIELDLIST.  Munge
   the list such that this does not present a problem later.  */

स्थिर शून्य
detect_field_duplicates (वृक्षः fieldlist)
{
  वृक्षः x, y;
  पूर्णाङ्क timeout = 10;

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
  जइ (c_dialect_objc ())
    जइ (objc_detect_field_duplicates (मिच्छ))
      प्रत्यागम;

  /* First, see if there are more than "a few" fields.
     This is trivially true if there are zero or one fields.  */
  जइ (!fieldlist || !DECL_CHAIN (fieldlist))
    प्रत्यागम;
  x = fieldlist;
  करेहि {
    timeout--;
    जइ (DECL_NAME (x) == NULL_वृक्षः
	&& RECORD_OR_UNION_TYPE_P (वृक्षः_TYPE (x)))
      timeout = 0;
    x = DECL_CHAIN (x);
  } जाव (timeout > 0 && x);

  /* If there were "few" fields and no anonymous structures or unions,
     avoid the overhead of allocating a hash table.  Instead just do
     the nested traversal thing.  */
  जइ (timeout > 0)
    {
      प्रति (x = DECL_CHAIN (fieldlist); x; x = DECL_CHAIN (x))
	/* When using -fplan9-extensions, we can have duplicates
	   between typedef names and fields.  */
	जइ (DECL_NAME (x)
	    || (flag_plan9_extensions
		&& DECL_NAME (x) == NULL_वृक्षः
		&& RECORD_OR_UNION_TYPE_P (वृक्षः_TYPE (x))
		&& TYPE_NAME (वृक्षः_TYPE (x)) != NULL_वृक्षः
		&& वृक्षः_CODE (TYPE_NAME (वृक्षः_TYPE (x))) == TYPE_DECL))
	  {
	    प्रति (y = fieldlist; y != x; y = वृक्षः_CHAIN (y))
	      जइ (is_duplicate_field (y, x))
		{
		  error ("duplicate member %q+D", x);
		  DECL_NAME (x) = NULL_वृक्षः;
		}
	  }
    }
  अण्णहा
    {
      hash_table<nofree_ptr_hash <वृक्ष_ग्रन्थिः> > htab (37);
      detect_field_duplicates_hash (fieldlist, &htab);
    }
}

/* Finish up struct info used by -Wc++-compat.  */

स्थिर शून्य
warn_cxx_compat_finish_struct (वृक्षः fieldlist, गणना वृक्षः_code code,
			       location_t record_loc)
{
  unsigned पूर्णाङ्क ix;
  वृक्षः x;
  संरचना c_binding *b;

  जइ (fieldlist == NULL_वृक्षः)
    {
      जइ (code == RECORD_TYPE)
	warning_at (record_loc, OPT_Wc___compat,
		    "empty struct has size 0 in C, size 1 in C++");
      अण्णहा
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
  जइ (!struct_parse_info->typedefs_seen.is_empty ()
      && fieldlist != NULL_वृक्षः)
    {
      /* Use a hash_set<tree> using the name of the typedef.  We can use
	 a hash_set<tree> because identifiers are interned.  */
      hash_set<वृक्षः> tset;

      FOR_EACH_VEC_ELT (struct_parse_info->typedefs_seen, ix, x)
	tset.add (DECL_NAME (x));

      प्रति (x = fieldlist; x != NULL_वृक्षः; x = DECL_CHAIN (x))
	{
	  जइ (DECL_NAME (x) != NULL_वृक्षः
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

स्थिर पूर्णाङ्क
field_decl_cmp (ध्रुव शून्य *x_p, ध्रुव शून्य *y_p)
{
  ध्रुव वृक्षः *ध्रुव x = (ध्रुव वृक्षः *) x_p;
  ध्रुव वृक्षः *ध्रुव y = (ध्रुव वृक्षः *) y_p;

  जइ (DECL_NAME (*x) == DECL_NAME (*y))
    /* A nontype is "greater" than a type.  */
    प्रत्यागम (वृक्षः_CODE (*y) == TYPE_DECL) - (वृक्षः_CODE (*x) == TYPE_DECL);
  जइ (DECL_NAME (*x) == NULL_वृक्षः)
    प्रत्यागम -1;
  जइ (DECL_NAME (*y) == NULL_वृक्षः)
    प्रत्यागम 1;
  जइ (DECL_NAME (*x) < DECL_NAME (*y))
    प्रत्यागम -1;
  प्रत्यागम 1;
}

/* If this structure or union completes the type of any previous
   variable declaration, lay it out and output its rtl.  */
स्थिर शून्य
finish_incomplete_vars (वृक्षः incomplete_vars, तार्किक toplevel)
{
  प्रति (वृक्षः x = incomplete_vars; x; x = वृक्षः_CHAIN (x))
    {
      वृक्षः decl = वृक्षः_मानम् (x);
      जइ (वृक्षः_CODE (वृक्षः_TYPE (decl)) == ARRAY_TYPE)
	layout_array_type (वृक्षः_TYPE (decl));
      जइ (वृक्षः_CODE (decl) != TYPE_DECL)
	{
	  relayout_decl (decl);
	  जइ (c_dialect_objc ())
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

स्थिर तार्किक
is_flexible_array_member_p (तार्किक is_last_field,
			    वृक्षः x)
{
  /* If not the last field, return false.  */
  जइ (!is_last_field)
    प्रत्यागम मिच्छ;

  /* If not an array field, return false.  */
  जइ (वृक्षः_CODE (वृक्षः_TYPE (x)) != ARRAY_TYPE)
    प्रत्यागम मिच्छ;

  तार्किक is_zero_length_array = zero_length_array_type_p (वृक्षः_TYPE (x));
  तार्किक is_one_element_array = one_element_array_type_p (वृक्षः_TYPE (x));
  तार्किक is_flexible_array = flexible_array_member_type_p (वृक्षः_TYPE (x));

  unsigned पूर्णाङ्क strict_flex_array_level = c_strict_flex_array_level_of (x);

  विकल्प (strict_flex_array_level)
    {
      पक्ष 0:
	/* Default, all trailing arrays are flexible array members.  */
	प्रत्यागम सच्च;
      पक्ष 1:
	/* Level 1: all "[1]", "[0]", and "[]" are flexible array members.  */
	जइ (is_one_element_array)
	  प्रत्यागम सच्च;
	/* FALLTHROUGH.  */
      पक्ष 2:
	/* Level 2: all "[0]", and "[]" are flexible array members.  */
	जइ (is_zero_length_array)
	  प्रत्यागम सच्च;
	/* FALLTHROUGH.  */
      पक्ष 3:
	/* Level 3: Only "[]" are flexible array members.  */
	जइ (is_flexible_array)
	  प्रत्यागम सच्च;
	भङ्ग;
      स्वभाव:
	gcc_unreachable ();
    }
  प्रत्यागम मिच्छ;
}

/* Recompute TYPE_CANONICAL for variants of the type including qualified
   versions of the type and related pointer types after an aggregate type
   has been finalized.
   Will not update array types, pointers to array types, function
   types and other derived types created while the type was still
   incomplete, those will remain TYPE_STRUCTURAL_EQUALITY_P.  */

स्थिर शून्य
c_update_type_canonical (वृक्षः t)
{
  gcc_checking_assert (TYPE_MAIN_VARIANT (t) == t && !TYPE_QUALS (t));
  प्रति (वृक्षः x = t, l = NULL_वृक्षः; x; l = x, x = TYPE_NEXT_VARIANT (x))
    {
      जइ (x != t && TYPE_STRUCTURAL_EQUALITY_P (x))
	{
	  जइ (!TYPE_QUALS (x))
	    TYPE_CANONICAL (x) = TYPE_CANONICAL (t);
	  अण्णहा
	    {
	      वृक्षः
		c = c_build_qualified_type (TYPE_CANONICAL (t), TYPE_QUALS (x));
	      जइ (TYPE_STRUCTURAL_EQUALITY_P (c))
		{
		  gcc_checking_assert (TYPE_CANONICAL (t) == t);
		  जइ (c == x)
		    TYPE_CANONICAL (x) = x;
		  अण्णहा
		    {
		      /* build_qualified_type for this function unhelpfully
			 moved c from some later spot in TYPE_MAIN_VARIANT (t)
			 chain to right after t (or created it there).  Move
			 it right before x and process c and then x.  */
		      gcc_checking_assert (TYPE_NEXT_VARIANT (t) == c);
		      जइ (l != t)
			{
			  TYPE_NEXT_VARIANT (t) = TYPE_NEXT_VARIANT (c);
			  TYPE_NEXT_VARIANT (l) = c;
			  TYPE_NEXT_VARIANT (c) = x;
			}
		      TYPE_CANONICAL (c) = c;
		      x = c;
		    }
		}
	      अण्णहा
		TYPE_CANONICAL (x) = TYPE_CANONICAL (c);
	    }
	}
      अण्णहा जइ (x != t)
	अनुवर्त;
      प्रति (वृक्षः p = TYPE_POINTER_TO (x); p; p = TYPE_NEXT_PTR_TO (p))
	{
	  जइ (!TYPE_STRUCTURAL_EQUALITY_P (p))
	    अनुवर्त;
	  जइ (TYPE_CANONICAL (x) != x || TYPE_REF_CAN_ALIAS_ALL (p))
	    TYPE_CANONICAL (p)
	      = c_build_pointer_type_for_mode (TYPE_CANONICAL (x), TYPE_MODE (p),
					       मिच्छ);
	  अण्णहा
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

स्थिर शून्य
c_update_variably_modified (वृक्षः t)
{
  प्रति (वृक्षः x = t; x; x = TYPE_NEXT_VARIANT (x))
    {
      C_TYPE_VARIABLY_MODIFIED (x) = 1;
      प्रति (वृक्षः p = TYPE_POINTER_TO (x); p; p = TYPE_NEXT_PTR_TO (p))
	c_update_variably_modified (p);
    }
}


/* Verify the argument of the counted_by attribute of each field of
   the containing structure, OUTMOST_STRUCT_TYPE, including its inner
   anonymous struct/union, Report error and remove the corresponding
   attribute when it's not.  */

स्थिर शून्य
verify_counted_by_attribute (वृक्षः outmost_struct_type,
			     वृक्षः cur_struct_type)
{
  प्रति (वृक्षः field = TYPE_FIELDS (cur_struct_type); field;
       field = वृक्षः_CHAIN (field))
    {
      जइ (flexible_array_member_type_p (वृक्षः_TYPE (field))
	   || वृक्षः_CODE (वृक्षः_TYPE (field)) == POINTER_TYPE)
	{
	  वृक्षः attr_counted_by = lookup_attribute ("counted_by",
						   DECL_ATTRIBUTES (field));

	  जइ (!attr_counted_by)
	    अनुवर्त;

	  /* If there is an counted_by attribute attached to the field,
	     verify it.  */

	  वृक्षः fieldname = वृक्षः_मानम् (वृक्षः_मानम् (attr_counted_by));

	  /* Verify the argument of the attribute is a valid field of the
	     containing structure.  */

	  वृक्षः counted_by_field = lookup_field (outmost_struct_type,
						fieldname);

	  /* Error when the field is not found in the containing structure
	     and remove the corresponding counted_by attribute from the
	     field_decl.  */
	  जइ (!counted_by_field)
	    {
	      error_at (DECL_SOURCE_LOCATION (field),
		    "argument %qE to the %<counted_by%> attribute"
		    " is not a field declaration in the same structure"
		    " as %qD", fieldname, field);
	      DECL_ATTRIBUTES (field)
		= remove_attribute ("counted_by", DECL_ATTRIBUTES (field));
	    }
	  अण्णहा
	  /* Error when the field is not with an integer type.  */
	    {
	      जाव (वृक्षः_CHAIN (counted_by_field))
		counted_by_field = वृक्षः_CHAIN (counted_by_field);
	      वृक्षः real_field = वृक्षः_मानम् (counted_by_field);

	      जइ (!INTEGRAL_TYPE_P (वृक्षः_TYPE (real_field)))
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
      अण्णहा जइ (RECORD_OR_UNION_TYPE_P (वृक्षः_TYPE (field))
	       && (DECL_NAME (field) == NULL_वृक्षः))
	verify_counted_by_attribute (outmost_struct_type, वृक्षः_TYPE (field));
    }
}

/* Caller should make sure the TYPE is a top-level type (i.e. not being
   nested in other structure/uniona). For such type, verify its counted_by
   if it is an anonymous structure/union.  */

शून्य
verify_counted_by_for_शिखरम्_anonymous_type (वृक्षः type)
{
  जइ (!RECORD_OR_UNION_TYPE_P (type))
    प्रत्यागम;

  जइ (C_TYPE_FIELDS_HAS_COUNTED_BY (type)
      && c_type_tag (type) == NULL_वृक्षः)
    verify_counted_by_attribute (type, type);
}

/* TYPE is a struct or union that we're applying may_alias to after the body is
   parsed.  Fixup any POINTER_TO types.  */

स्थिर शून्य
c_fixup_may_alias (वृक्षः type)
{
  प्रति (वृक्षः t = TYPE_POINTER_TO (type); t; t = TYPE_NEXT_PTR_TO (t))
    प्रति (वृक्षः v = TYPE_MAIN_VARIANT (t); v; v = TYPE_NEXT_VARIANT (v))
      TYPE_REF_CAN_ALIAS_ALL (v) = सच्च;
}

/* Fill in the fields of a RECORD_TYPE or UNION_TYPE node, T.
   LOC is the location of the RECORD_TYPE or UNION_TYPE's definition.
   FIELDLIST is a chain of FIELD_DECL nodes for the fields.
   ATTRIBUTES are attributes to be applied to the structure.

   ENCLOSING_STRUCT_PARSE_INFO is the value of STRUCT_PARSE_INFO when
   the struct was started.  */

वृक्षः
finish_struct (location_t loc, वृक्षः t, वृक्षः fieldlist, वृक्षः attributes,
	       वर्ग c_struct_parse_info *enclosing_struct_parse_info,
	       वृक्षः *व्यञ्जकम्)
{
  वृक्षः x;
  तार्किक toplevel = file_scope == current_scope;

  /* If this type was previously laid out as a forward reference,
     make sure we lay it out again.  */

  TYPE_SIZE (t) = NULL_वृक्षः;

  decl_attributes (&t, attributes, (पूर्णाङ्क) ATTR_FLAG_TYPE_IN_PLACE);

  जइ (pedantic)
    {
      प्रति (x = fieldlist; x; x = DECL_CHAIN (x))
	{
	  जइ (DECL_NAME (x) != NULL_वृक्षः)
	    भङ्ग;
	  जइ (flag_isoc11 && RECORD_OR_UNION_TYPE_P (वृक्षः_TYPE (x)))
	    भङ्ग;
	}

      जइ (x == NULL_वृक्षः)
	{
	  जइ (वृक्षः_CODE (t) == UNION_TYPE)
	    {
	      जइ (fieldlist)
		pedwarn (loc, OPT_Wpedantic, "union has no named members");
	      अण्णहा
		pedwarn (loc, OPT_Wpedantic, "union has no members");
	    }
	  अण्णहा
	    {
	      जइ (fieldlist)
		pedwarn (loc, OPT_Wpedantic, "struct has no named members");
	      अण्णहा
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

  तार्किक saw_named_field = मिच्छ;
  प्रति (x = fieldlist; x; x = DECL_CHAIN (x))
    {
      /* Whether this field is the last field of the structure or union.
	 for UNION, any field is the last field of it.  */
      तार्किक is_last_field = (DECL_CHAIN (x) == NULL_वृक्षः)
			    || (वृक्षः_CODE (t) == UNION_TYPE);

      जइ (वृक्षः_TYPE (x) == error_mark_ग्रन्थिः)
	अनुवर्त;

      DECL_CONTEXT (x) = t;

      वृक्षः t1 = strip_array_types (वृक्षः_TYPE (x));
      /* If any field is const, the structure type is pseudo-const.  */
      जइ (वृक्षः_READONLY (x))
	C_TYPE_FIELDS_READONLY (t) = 1;
      अण्णहा
	{
	  /* A field that is pseudo-const makes the structure likewise.  */
	  जइ (RECORD_OR_UNION_TYPE_P (t1) && C_TYPE_FIELDS_READONLY (t1))
	    C_TYPE_FIELDS_READONLY (t) = 1;
	}

      /* Any field that is volatile means variables of this type must be
	 treated in some ways as volatile.  */
      जइ (वृक्षः_THIS_VOLATILE (x))
	{
	  C_TYPE_FIELDS_VOLATILE (t) = 1;
	  C_TYPE_FIELDS_NON_CONSTEXPR (t) = 1;
	}

      /* Any field that is volatile, restrict-qualified or atomic
	 means the type cannot be used for a constexpr object.  */
      जइ (TYPE_QUALS (t1)
	  & (TYPE_QUAL_VOLATILE | TYPE_QUAL_RESTRICT | TYPE_QUAL_ATOMIC))
	C_TYPE_FIELDS_NON_CONSTEXPR (t) = 1;
      अण्णहा जइ (RECORD_OR_UNION_TYPE_P (t1) && C_TYPE_FIELDS_NON_CONSTEXPR (t1))
	    C_TYPE_FIELDS_NON_CONSTEXPR (t) = 1;

      /* Any field of nominal variable size implies structure is too.  */
      जइ (C_DECL_VARIABLE_SIZE (x))
	C_TYPE_VARIABLE_SIZE (t) = 1;

      /* If any field is variably modified, record this fact. */
      जइ (c_type_variably_modified_p (वृक्षः_TYPE (x)))
	C_TYPE_VARIABLY_MODIFIED (t) = 1;

      जइ (DECL_C_BIT_FIELD (x))
	{
	  unsigned HOST_WIDE_INT width = वृक्षः_to_uhwi (DECL_INITIAL (x));
	  DECL_SIZE (x) = bitsize_int (width);
	  DECL_BIT_FIELD (x) = 1;
	}

      जइ (TYPE_PACKED (t)
	  && (DECL_BIT_FIELD (x)
	      || TYPE_ALIGN (वृक्षः_TYPE (x)) > BITS_PER_UNIT))
	DECL_PACKED (x) = 1;

      /* Detect flexible array member in an invalid context.  */
      जइ (flexible_array_member_type_p (वृक्षः_TYPE (x)))
	{
	  जइ (वृक्षः_CODE (t) == UNION_TYPE)
	    pedwarn (DECL_SOURCE_LOCATION (x), OPT_Wpedantic,
		     "flexible array member in union is a GCC extension");
	  अण्णहा जइ (!is_last_field)
	    {
	      error_at (DECL_SOURCE_LOCATION (x),
			"flexible array member not at end of struct");
	      वृक्षः_TYPE (x) = error_mark_ग्रन्थिः;
	    }
	  अण्णहा जइ (!saw_named_field)
	    pedwarn (DECL_SOURCE_LOCATION (x), OPT_Wpedantic,
		     "flexible array member in a struct with no named "
		     "members is a GCC extension");
	  जइ (lookup_attribute ("counted_by", DECL_ATTRIBUTES (x)))
	    C_TYPE_FIELDS_HAS_COUNTED_BY (t) = 1;
	}

      जइ (वृक्षः_CODE (वृक्षः_TYPE (x)) == POINTER_TYPE
	  && lookup_attribute ("counted_by", DECL_ATTRIBUTES (x)))
	C_TYPE_FIELDS_HAS_COUNTED_BY (t) = 1;

      /* If the field is an anonymous structure that includes a field
	 with counted_by attribute, this structure should also be marked
	 too.  */
      जइ (RECORD_OR_UNION_TYPE_P (वृक्षः_TYPE (x))
	  && C_TYPE_FIELDS_HAS_COUNTED_BY (वृक्षः_TYPE (x))
	  && DECL_NAME (x) == NULL_वृक्षः
	  && c_type_tag (वृक्षः_TYPE (x)) == NULL_वृक्षः)
	C_TYPE_FIELDS_HAS_COUNTED_BY (t) = 1;

      जइ (pedantic && वृक्षः_CODE (t) == RECORD_TYPE
	  && flexible_array_type_p (वृक्षः_TYPE (x)))
	pedwarn (DECL_SOURCE_LOCATION (x), OPT_Wpedantic,
		 "invalid use of structure with flexible array member");

      /* Set DECL_NOT_FLEXARRAY flag for FIELD_DECL x.  */
      DECL_NOT_FLEXARRAY (x) = !is_flexible_array_member_p (is_last_field, x);

      /* Set TYPE_INCLUDES_FLEXARRAY for the context of x, t.
	 when x is an array and is the last field.
	 There is only one last_field for a structure type, but there might
	 be multiple last_fields for a union type, therefore we should ORed
	 the result for multiple last_fields.  */
      जइ (वृक्षः_CODE (वृक्षः_TYPE (x)) == ARRAY_TYPE)
	TYPE_INCLUDES_FLEXARRAY (t)
	  |= is_last_field && flexible_array_member_type_p (वृक्षः_TYPE (x));
      /* Recursively set TYPE_INCLUDES_FLEXARRAY for the context of x, t
	 when x is an union or record and is the last field.  */
      अण्णहा जइ (RECORD_OR_UNION_TYPE_P (वृक्षः_TYPE (x)))
	TYPE_INCLUDES_FLEXARRAY (t)
	  |= is_last_field && TYPE_INCLUDES_FLEXARRAY (वृक्षः_TYPE (x));

      जइ (warn_flex_array_member_not_at_end
	  && !is_last_field
	  && RECORD_OR_UNION_TYPE_P (वृक्षः_TYPE (x))
	  && TYPE_INCLUDES_FLEXARRAY (वृक्षः_TYPE (x)))
	warning_at (DECL_SOURCE_LOCATION (x),
		    OPT_Wflex_array_member_not_at_end,
		    "structure containing a flexible array member"
		    " is not at the end of another structure");

      जइ (DECL_NAME (x)
	  || RECORD_OR_UNION_TYPE_P (वृक्षः_TYPE (x)))
	saw_named_field = सच्च;

      जइ (AGGREGATE_TYPE_P (वृक्षः_TYPE (x))
	  && TYPE_TYPELESS_STORAGE (वृक्षः_TYPE (x)))
	TYPE_TYPELESS_STORAGE (t) = सच्च;
    }

  detect_field_duplicates (fieldlist);

  /* Now we have the nearly final fieldlist.  Record it,
     then lay out the structure or union (including the fields).  */

  TYPE_FIELDS (t) = fieldlist;

  maybe_apply_pragma_scalar_storage_order (t);

  layout_type (t);

  जइ (TYPE_SIZE_UNIT (t)
      && वृक्षः_CODE (TYPE_SIZE_UNIT (t)) == INTEGER_CST
      && !वृक्षः_OVERFLOW (TYPE_SIZE_UNIT (t))
      && !valid_constant_size_p (TYPE_SIZE_UNIT (t)))
    error ("type %qT is too large", t);

  /* Give bit-fields their proper types and rewrite the type of array fields
     with scalar component if the enclosing type has reverse storage order.  */
  प्रति (वृक्षः field = fieldlist; field; field = DECL_CHAIN (field))
    {
      जइ (वृक्षः_CODE (field) == FIELD_DECL
	  && DECL_INITIAL (field)
	  && वृक्षः_TYPE (field) != error_mark_ग्रन्थिः)
	{
	  unsigned HOST_WIDE_INT width
	    = वृक्षः_to_uhwi (DECL_INITIAL (field));
	  वृक्षः type = वृक्षः_TYPE (field);
	  जइ (VECTOR_TYPE_P (type))
	    {
	      error_at (DECL_SOURCE_LOCATION (field),
			"bit-field %qD has invalid type", field);
	      type = वृक्षः_TYPE (type);
	      वृक्षः_TYPE (field) = type;
	    }
	  जइ (width != TYPE_PRECISION (type))
	    {
	      जइ (BITINT_TYPE_P (type)
		  && width >= ((TYPE_UNSIGNED (type) || flag_isoc2y) ? 1 : 2))
		वृक्षः_TYPE (field)
		  = build_bitint_type (width, TYPE_UNSIGNED (type));
	      अण्णहा
		वृक्षः_TYPE (field)
		  = c_build_bitfield_integer_type (width,
						   TYPE_UNSIGNED (type));
	      जइ (वृक्षः attr = c_hardbool_type_attr (type))
		decl_attributes (&वृक्षः_TYPE (field),
				 copy_list (attr),
				 0, NULL_वृक्षः);
	      SET_DECL_MODE (field, TYPE_MODE (वृक्षः_TYPE (field)));
	    }
	  DECL_INITIAL (field) = NULL_वृक्षः;
	}
      अण्णहा जइ (TYPE_REVERSE_STORAGE_ORDER (t)
	       && वृक्षः_CODE (field) == FIELD_DECL
	       && वृक्षः_CODE (वृक्षः_TYPE (field)) == ARRAY_TYPE)
	{
	  वृक्षः ftype = वृक्षः_TYPE (field);
	  वृक्षः ctype = strip_array_types (ftype);
	  जइ (!RECORD_OR_UNION_TYPE_P (ctype) && TYPE_MODE (ctype) != QImode)
	    {
	      वृक्षः fmain_type = TYPE_MAIN_VARIANT (ftype);
	      वृक्षः *typep = &fmain_type;
	      करेहि {
		*typep = build_distinct_type_copy (*typep);
		TYPE_REVERSE_STORAGE_ORDER (*typep) = 1;
		typep = &वृक्षः_TYPE (*typep);
	      } जाव (वृक्षः_CODE (*typep) == ARRAY_TYPE);
	      वृक्षः_TYPE (field)
		= c_build_qualified_type (fmain_type, TYPE_QUALS (ftype));
	    }
	}

      /* Warn on problematic type punning for storage order purposes.  */
      जइ (वृक्षः_CODE (t) == UNION_TYPE
	  && वृक्षः_CODE (field) == FIELD_DECL
	  && AGGREGATE_TYPE_P (वृक्षः_TYPE (field)))
	{
	  वृक्षः ftype = वृक्षः_TYPE (field);
	  जइ (वृक्षः_CODE (ftype) == ARRAY_TYPE)
	    ftype = strip_array_types (ftype);
	  जइ (RECORD_OR_UNION_TYPE_P (ftype)
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
    पूर्णाङ्क len = 0;

    प्रति (x = fieldlist; x; x = DECL_CHAIN (x))
      {
	जइ (len > 15 || DECL_NAME (x) == रिक्त)
	  भङ्ग;
	len += 1;
      }

    जइ (len > 15)
      {
	वृक्षः *field_array;
	संरचना lang_type *space;
	संरचना sorted_fields_type *space2;

	len += list_length (x);

	/* Use the same allocation policy here that make_node uses, to
	   ensure that this lives as long as the rest of the struct decl.
	   All decls in an inline function need to be saved.  */

	space = ((संरचना lang_type *)
		 ggc_internal_cleared_alloc (c_dialect_objc ()
					     ? परिमाण (संरचना lang_type)
					     : offsetof (संरचना lang_type,
							 info)));
	space2 = ((sorted_fields_type *)
		  ggc_internal_alloc (परिमाण (संरचना sorted_fields_type)
				      + len * परिमाण (वृक्षः)));

	len = 0;
	space->s = space2;
	field_array = &space2->elts[0];
	प्रति (x = fieldlist; x; x = DECL_CHAIN (x))
	  {
	    field_array[len++] = x;

	    /* If there is anonymous struct or union, break out of the loop.  */
	    जइ (DECL_NAME (x) == रिक्त)
	      भङ्ग;
	  }
	/* Found no anonymous struct/union.  Add the TYPE_LANG_SPECIFIC.  */
	जइ (x == रिक्त)
	  {
	    TYPE_LANG_SPECIFIC (t) = space;
	    TYPE_LANG_SPECIFIC (t)->s->len = len;
	    field_array = TYPE_LANG_SPECIFIC (t)->s->elts;
	    qsort (field_array, len, परिमाण (वृक्षः), field_decl_cmp);
	  }
      }
  }

  /* If this was supposed to be a transparent union, but we can't
     make it one, warn and turn off the flag.  */
  जइ (वृक्षः_CODE (t) == UNION_TYPE
      && TYPE_TRANSPARENT_AGGR (t)
      && (!TYPE_FIELDS (t) || TYPE_MODE (t) != DECL_MODE (TYPE_FIELDS (t))))
    {
      TYPE_TRANSPARENT_AGGR (t) = 0;
      warning_at (loc, 0, "union cannot be made transparent");
    }

  वृक्षः incomplete_vars = C_TYPE_INCOMPLETE_VARS (TYPE_MAIN_VARIANT (t));
  प्रति (x = TYPE_MAIN_VARIANT (t); x; x = TYPE_NEXT_VARIANT (x))
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
      C_TYPE_INCOMPLETE_VARS (x) = NULL_वृक्षः;
      TYPE_INCLUDES_FLEXARRAY (x) = TYPE_INCLUDES_FLEXARRAY (t);
    }

  /* Check for consistency with previous definition.  */
  जइ (flag_isoc23 && रिक्त != enclosing_struct_parse_info)
    {
      वृक्षः vistype = previous_tag (t);
      जइ (vistype
	  && वृक्षः_CODE (vistype) == वृक्षः_CODE (t)
	  && !C_TYPE_BEING_DEFINED (vistype))
	{
	  TYPE_STUB_DECL (t) = TYPE_STUB_DECL (vistype);
	  जइ (c_type_variably_modified_p (t))
	    {
	      error ("redefinition of struct or union %qT with variably "
		     "modified type", t);
	      जइ (struct_parse_info->refloc != UNKNOWN_LOCATION)
		inform (struct_parse_info->refloc, "originally defined here");
	    }
	  अण्णहा जइ (!comptypes_same_p (t, vistype))
	    {
	      error ("redefinition of struct or union %qT", t);
	      जइ (struct_parse_info->refloc != UNKNOWN_LOCATION)
		inform (struct_parse_info->refloc, "originally defined here");
	    }
	}
    }

  C_TYPE_BEING_DEFINED (t) = 0;

  जइ (lookup_attribute ("may_alias", TYPE_ATTRIBUTES (t)))
    प्रति (x = TYPE_MAIN_VARIANT (t); x; x = TYPE_NEXT_VARIANT (x))
      c_fixup_may_alias (x);

  /* Set type canonical based on equivalence class.  */
  जइ (flag_isoc23 && !C_TYPE_VARIABLE_SIZE (t))
    {
      जइ (c_struct_htab == रिक्त)
	c_struct_htab = hash_table<c_struct_hasher>::create_ggc (61);

      hashval_t hash = c_struct_hasher::hash (t);

      gcc_checking_assert (TYPE_STRUCTURAL_EQUALITY_P (t));
      gcc_checking_assert (!TYPE_NAME (t)
			   || वृक्षः_CODE (TYPE_NAME (t)) == IDENTIFIER_ग्रन्थिः);

      वृक्षः *e = c_struct_htab->find_slot_with_hash (t, hash, निवेशय);
      जइ (*e)
	TYPE_CANONICAL (t) = TYPE_CANONICAL (*e);
      अण्णहा
	{
	  TYPE_CANONICAL (t) = c_type_canonical (t);
	  *e = t;
	}
      c_update_type_canonical (t);
    }

  /* Update type location to the one of the definition, instead of e.g.
     a forward declaration.  */
  जइ (TYPE_STUB_DECL (t))
    DECL_SOURCE_LOCATION (TYPE_STUB_DECL (t)) = loc;

  /* Finish debugging output for this type.  */
  rest_of_type_compilation (t, toplevel);

  finish_incomplete_vars (incomplete_vars, toplevel);


  जइ (c_type_variably_modified_p (t))
    {
      c_update_variably_modified (t);
      /* Make sure a DECL_EXPR is created for structs with VLA members.
	 Because we do not know the context, we always pass expr
	 to force creation of a BIND_EXPR which is required in some
	 contexts.  */
      add_decl_व्यञ्जकम् (loc, t, व्यञ्जकम्, मिच्छ);
    }

  जइ (warn_cxx_compat)
    warn_cxx_compat_finish_struct (fieldlist, वृक्षः_CODE (t), loc);

  जइ (रिक्त != enclosing_struct_parse_info)
    {
      delete struct_parse_info;

      struct_parse_info = enclosing_struct_parse_info;

      /* If this struct is defined inside a struct, add it to
	 struct_types.  */
      जइ (warn_cxx_compat
	  && struct_parse_info != रिक्त
	  && !in_sizeof && !in_typeof && !in_alignof && !in_countof)
	struct_parse_info->struct_types.safe_प्रक्षिप (t);
     }

  /* Only when the enclosing struct/union type is not anonymous, do more
     verification on the fields with counted_by attributes.  */
  जइ (C_TYPE_FIELDS_HAS_COUNTED_BY (t) && c_type_tag (t) != NULL_वृक्षः)
    verify_counted_by_attribute (t, t);

  प्रत्यागम t;
}

स्थिर संरचना {
  gt_pointer_operator new_मानम्;
  शून्य *cookie;
} resort_data;

/* This routine compares two fields like field_decl_cmp but using the
pointer operator in resort_data.  */

स्थिर पूर्णाङ्क
resort_field_decl_cmp (ध्रुव शून्य *x_p, ध्रुव शून्य *y_p)
{
  ध्रुव वृक्षः *ध्रुव x = (ध्रुव वृक्षः *) x_p;
  ध्रुव वृक्षः *ध्रुव y = (ध्रुव वृक्षः *) y_p;

  जइ (DECL_NAME (*x) == DECL_NAME (*y))
    /* A nontype is "greater" than a type.  */
    प्रत्यागम (वृक्षः_CODE (*y) == TYPE_DECL) - (वृक्षः_CODE (*x) == TYPE_DECL);
  जइ (DECL_NAME (*x) == NULL_वृक्षः)
    प्रत्यागम -1;
  जइ (DECL_NAME (*y) == NULL_वृक्षः)
    प्रत्यागम 1;
  {
    वृक्षः d1 = DECL_NAME (*x);
    वृक्षः d2 = DECL_NAME (*y);
    resort_data.new_मानम् (&d1, &d1, resort_data.cookie);
    resort_data.new_मानम् (&d2, &d2, resort_data.cookie);
    जइ (d1 < d2)
      प्रत्यागम -1;
  }
  प्रत्यागम 1;
}

/* Resort DECL_SORTED_FIELDS because pointers have been reordered.  */

शून्य
resort_sorted_fields (शून्य *obj,
		      शून्य * ARG_UNUSED (orig_obj),
		      gt_pointer_operator new_मानम्,
		      शून्य *cookie)
{
  संरचना sorted_fields_type *sf = (संरचना sorted_fields_type *) obj;
  resort_data.new_मानम् = new_मानम्;
  resort_data.cookie = cookie;
  qsort (&sf->elts[0], sf->len, परिमाण (वृक्षः),
	 resort_field_decl_cmp);
}

/* Lay out the type T, and its element type, and so on.  */

स्थिर शून्य
layout_array_type (वृक्षः t)
{
  जइ (वृक्षः_CODE (वृक्षः_TYPE (t)) == ARRAY_TYPE)
    layout_array_type (वृक्षः_TYPE (t));
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

वृक्षः
start_enum (location_t loc, संरचना c_enum_contents *the_enum, वृक्षः name,
	    वृक्षः fixed_underlying_type, तार्किक potential_nesting_p)
{
  वृक्षः enumtype = NULL_वृक्षः;
  location_t enumloc = UNKNOWN_LOCATION;

  /* If this is the real definition for a previous forward reference,
     fill in the contents in the same object that used to be the
     forward reference.  */

  जइ (name != NULL_वृक्षः)
    enumtype = lookup_tag (ENUMERAL_TYPE, name, सच्च, &enumloc);

  जइ (enumtype != NULL_वृक्षः && वृक्षः_CODE (enumtype) == ENUMERAL_TYPE)
    {
      /* If the type is currently being defined or if we have seen an
	 incomplete version which is now complete, this is a nested
	 redefinition.  The later happens if the redefinition occurs
	 inside the enum specifier itself.  */
      जइ (C_TYPE_BEING_DEFINED (enumtype)
	  || (potential_nesting_p && TYPE_मानानि (enumtype) != NULL_वृक्षः))
	error_at (loc, "nested redefinition of %<enum %E%>", name);

      /* For C23 we allow redefinitions.  We set to zero and check for
	 consistency later.  */
      जइ (flag_isoc23 && TYPE_मानानि (enumtype) != NULL_वृक्षः)
	enumtype = NULL_वृक्षः;
    }

  जइ (enumtype == NULL_वृक्षः || वृक्षः_CODE (enumtype) != ENUMERAL_TYPE)
    {
      enumtype = make_ग्रन्थिः (ENUMERAL_TYPE);
      TYPE_SIZE (enumtype) = NULL_वृक्षः;
      SET_TYPE_STRUCTURAL_EQUALITY (enumtype);
      pushtag (loc, name, enumtype);
      जइ (fixed_underlying_type != NULL_वृक्षः)
	{
	  /* For an enum definition with a fixed underlying type, the
	     type is complete during the definition and the
	     enumeration constants have that type.  If there was a
	     tag, the type was completed in c_parser_enum_specifier.
	     If not, it must be completed here.  */
	  ENUM_FIXED_UNDERLYING_TYPE_P (enumtype) = सच्च;
	  TYPE_MIN_मानम् (enumtype) = TYPE_MIN_मानम् (fixed_underlying_type);
	  TYPE_MAX_मानम् (enumtype) = TYPE_MAX_मानम् (fixed_underlying_type);
	  TYPE_UNSIGNED (enumtype) = TYPE_UNSIGNED (fixed_underlying_type);
	  SET_TYPE_ALIGN (enumtype, TYPE_ALIGN (fixed_underlying_type));
	  TYPE_SIZE (enumtype) = NULL_वृक्षः;
	  TYPE_PRECISION (enumtype) = TYPE_PRECISION (fixed_underlying_type);
	  ENUM_UNDERLYING_TYPE (enumtype) = fixed_underlying_type;
	  TYPE_CANONICAL (enumtype) = TYPE_CANONICAL (fixed_underlying_type);
	  c_update_type_canonical (enumtype);
	  layout_type (enumtype);
	}
    }
  /* Update type location to the one of the definition, instead of e.g.
     a forward declaration.  */
  अण्णहा जइ (TYPE_STUB_DECL (enumtype))
    {
      enumloc = DECL_SOURCE_LOCATION (TYPE_STUB_DECL (enumtype));
      DECL_SOURCE_LOCATION (TYPE_STUB_DECL (enumtype)) = loc;
    }

  C_TYPE_BEING_DEFINED (enumtype) = 1;

  जइ (TYPE_मानानि (enumtype) != NULL_वृक्षः)
    {
      /* This enum is a named one that has been declared already.  */
      auto_diagnostic_group d;
      error_at (loc, "redeclaration of %<enum %E%>", name);
      जइ (enumloc != UNKNOWN_LOCATION)
	inform (enumloc, "originally defined here");

      /* Completely replace its old definition.
	 The old enumerators remain defined, however.  */
      TYPE_मानानि (enumtype) = NULL_वृक्षः;
    }

  जइ (ENUM_FIXED_UNDERLYING_TYPE_P (enumtype)
      && fixed_underlying_type == NULL_वृक्षः)
    {
      error_at (loc, "%<enum%> declared with but defined without "
		"fixed underlying type");
      ENUM_FIXED_UNDERLYING_TYPE_P (enumtype) = मिच्छ;
    }

  the_enum->enum_next_मानम् = integer_zero_ग्रन्थिः;
  the_enum->enum_type = enumtype;
  the_enum->enum_overflow = 0;

  जइ (flag_short_enums && !ENUM_FIXED_UNDERLYING_TYPE_P (enumtype))
    प्रति (वृक्षः v = TYPE_MAIN_VARIANT (enumtype); v; v = TYPE_NEXT_VARIANT (v))
      TYPE_PACKED (v) = 1;

  /* FIXME: This will issue a warning for a use of a type defined
     within sizeof in a statement expr.  This is not terribly serious
     as C++ doesn't permit statement exprs within sizeof anyhow.  */
  जइ (warn_cxx_compat
      && (in_sizeof || in_typeof || in_alignof || in_countof))
    warning_at (loc, OPT_Wc___compat,
		"defining type in %qs expression is invalid in C++",
		(in_sizeof ? "sizeof"
		 : in_typeof ? "typeof"
		 : in_alignof ? "alignof"
		 : "_Countof"));

  जइ (in_underspecified_init)
    error_at (loc, "%qT defined in underspecified object initializer",
	      enumtype);

  प्रत्यागम enumtype;
}

/* After processing and defining all the values of an enumeration type,
   install their decls in the enumeration type and finish it off.
   ENUMTYPE is the type object, VALUES a list of decl-value pairs,
   and ATTRIBUTES are the specified attributes.
   Returns ENUMTYPE.  */

वृक्षः
finish_enum (वृक्षः enumtype, वृक्षः मानानि, वृक्षः attributes)
{
  वृक्षः pair, tem;
  वृक्षः minnode = NULL_वृक्षः, maxnode = NULL_वृक्षः;
  पूर्णाङ्क precision;
  signop sign;
  तार्किक toplevel = (file_scope == current_scope);
  संरचना lang_type *lt;

  decl_attributes (&enumtype, attributes, (पूर्णाङ्क) ATTR_FLAG_TYPE_IN_PLACE);

  /* Calculate the maximum value of any enumerator in this type.  */

  जइ (मानानि == error_mark_ग्रन्थिः)
    minnode = maxnode = integer_zero_ग्रन्थिः;
  अण्णहा
    {
      minnode = maxnode = वृक्षः_मानम् (मानानि);
      प्रति (pair = वृक्षः_CHAIN (मानानि); pair; pair = वृक्षः_CHAIN (pair))
	{
	  वृक्षः मानम् = वृक्षः_मानम् (pair);
	  जइ (वृक्षः_int_cst_lt (maxnode, मानम्))
	    maxnode = मानम्;
	  जइ (वृक्षः_int_cst_lt (मानम्, minnode))
	    minnode = मानम्;
	}
    }

  /* Construct the final type of this enumeration.  It is the same
     as one of the integral types - the narrowest one that fits, except
     that normally we only go as narrow as int - and signed iff any of
     the values are negative.  */
  sign = (वृक्षः_int_cst_sgn (minnode) >= 0) ? UNSIGNED : SIGNED;
  precision = MAX (वृक्षः_int_cst_min_precision (minnode, sign),
		   वृक्षः_int_cst_min_precision (maxnode, sign));

  तार्किक wider_than_int =
    (वृक्षः_int_cst_lt (minnode, TYPE_MIN_मानम् (integer_type_ग्रन्थिः))
     || वृक्षः_int_cst_lt (TYPE_MAX_मानम् (integer_type_ग्रन्थिः), maxnode));


  जइ (!ENUM_FIXED_UNDERLYING_TYPE_P (enumtype))
    {
      /* If the precision of the type was specified with an attribute and it
	 was too small, give an error.  Otherwise, use it.  */
      जइ (TYPE_PRECISION (enumtype) && lookup_attribute ("mode", attributes))
	{
	  जइ (precision > TYPE_PRECISION (enumtype))
	    {
	      TYPE_PRECISION (enumtype) = 0;
	      error ("specified mode too small for enumerated values");
	    }
	  अण्णहा
	    precision = TYPE_PRECISION (enumtype);
	}
      अण्णहा
	TYPE_PRECISION (enumtype) = 0;

      जइ (TYPE_PACKED (enumtype)
	  || precision > TYPE_PRECISION (integer_type_ग्रन्थिः)
	  || TYPE_PRECISION (enumtype))
	{
	  tem = c_common_type_for_size (precision, sign == UNSIGNED ? 1 : 0);
	  जइ (tem == रिक्त)
	    {
	      /* This should only occur when both signed and unsigned
		 values of maximum precision occur among the
		 enumerators.  */
	      pedwarn (निवेशः_location, 0,
		       "enumeration values exceed range of largest integer");
	      tem = widest_integer_literal_type_ग्रन्थिः;
	    }
	  अण्णहा जइ (precision > TYPE_PRECISION (intmax_type_ग्रन्थिः)
		   && !वृक्षः_int_cst_lt (minnode,
					TYPE_MIN_मानम् (intmax_type_ग्रन्थिः))
		   && !वृक्षः_int_cst_lt (TYPE_MAX_मानम् (uintmax_type_ग्रन्थिः),
					maxnode))
	    pedwarn (निवेशः_location, OPT_Wpedantic,
		     "enumeration values exceed range of %qs",
		     sign == UNSIGNED ? "uintmax_t" : "intmax_t");
	}
      अण्णहा
	tem = sign == UNSIGNED ? unsigned_type_ग्रन्थिः : integer_type_ग्रन्थिः;

      TYPE_MIN_मानम् (enumtype) = TYPE_MIN_मानम् (tem);
      TYPE_MAX_मानम् (enumtype) = TYPE_MAX_मानम् (tem);
      TYPE_UNSIGNED (enumtype) = TYPE_UNSIGNED (tem);
      SET_TYPE_ALIGN (enumtype, TYPE_ALIGN (tem));
      TYPE_SIZE (enumtype) = NULL_वृक्षः;
      TYPE_PRECISION (enumtype) = TYPE_PRECISION (tem);
      ENUM_UNDERLYING_TYPE (enumtype) =
	c_common_type_for_size (TYPE_PRECISION (tem), TYPE_UNSIGNED (tem));

      TYPE_CANONICAL (enumtype) =
	TYPE_CANONICAL (ENUM_UNDERLYING_TYPE (enumtype));
      c_update_type_canonical (enumtype);

      layout_type (enumtype);
    }

  जइ (मानानि != error_mark_ग्रन्थिः)
    {
      /* Change the type of the enumerators to be the enum type.  We
	 need to do this irrespective of the size of the enum, for
	 proper type checking.  Replace the DECL_INITIALs of the
	 enumerators, and the value slots of the list, with copies
	 that have the enum type; they cannot be modified in place
	 because they may be shared (e.g.  integer_zero_node) Finally,
	 change the purpose slots to point to the names of the decls.  */
      प्रति (pair = मानानि; pair; pair = वृक्षः_CHAIN (pair))
	{
	  वृक्षः enu = वृक्षः_PURPOSE (pair);
	  वृक्षः ini = DECL_INITIAL (enu);

	  वृक्षः_TYPE (enu) = enumtype;

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
	  जइ (!ENUM_FIXED_UNDERLYING_TYPE_P (enumtype) && wider_than_int)
	    ini = convert (enumtype, ini);

	  DECL_INITIAL (enu) = ini;
	  वृक्षः_PURPOSE (pair) = DECL_NAME (enu);
	  /* To match the C++ FE, store the CONST_DECL rather than just its
	     value.  */
	  वृक्षः_मानम् (pair) = enu;
	}

      TYPE_मानानि (enumtype) = मानानि;
    }

  /* Record the min/max values so that we can warn about bit-field
     enumerations that are too small for the values.  */
  lt = ((संरचना lang_type *)
	ggc_internal_cleared_alloc (c_dialect_objc ()
				    ? परिमाण (संरचना lang_type)
				    : offsetof (संरचना lang_type, info)));
  lt->enum_min = minnode;
  lt->enum_max = maxnode;
  TYPE_LANG_SPECIFIC (enumtype) = lt;

  /* Fix up all variant types of this enum type.  */
  वृक्षः incomplete_vars = C_TYPE_INCOMPLETE_VARS (TYPE_MAIN_VARIANT (enumtype));
  प्रति (tem = TYPE_MAIN_VARIANT (enumtype); tem; tem = TYPE_NEXT_VARIANT (tem))
    {
      C_TYPE_INCOMPLETE_VARS (tem) = NULL_वृक्षः;
      जइ (tem == enumtype)
	अनुवर्त;
      TYPE_मानानि (tem) = TYPE_मानानि (enumtype);
      TYPE_MIN_मानम् (tem) = TYPE_MIN_मानम् (enumtype);
      TYPE_MAX_मानम् (tem) = TYPE_MAX_मानम् (enumtype);
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
  जइ (warn_cxx_compat
      && struct_parse_info != रिक्त
      && !in_sizeof && !in_typeof && !in_alignof && !in_countof)
    struct_parse_info->struct_types.safe_प्रक्षिप (enumtype);

  /* Check for consistency with previous definition */
  जइ (flag_isoc23)
    {
      वृक्षः vistype = previous_tag (enumtype);
      जइ (vistype
	  && वृक्षः_CODE (vistype) == वृक्षः_CODE (enumtype)
	  && !C_TYPE_BEING_DEFINED (vistype))
	{
	  TYPE_STUB_DECL (enumtype) = TYPE_STUB_DECL (vistype);
	  जइ (!comptypes_same_p (enumtype, vistype))
	    error("conflicting redefinition of enum %qT", enumtype);
	}
    }

  C_TYPE_BEING_DEFINED (enumtype) = 0;

  प्रत्यागम enumtype;
}

/* Build and install a CONST_DECL for one value of the
   current enumeration type (one that was begun with start_enum).
   DECL_LOC is the location of the enumerator.
   LOC is the location of the '=' operator if any, DECL_LOC otherwise.
   Return a tree-list containing the CONST_DECL and its value.
   Assignment of sequential values by default is handled here.  */

वृक्षः
build_enumerator (location_t decl_loc, location_t loc,
		  संरचना c_enum_contents *the_enum, वृक्षः name, वृक्षः मानम्)
{
  वृक्षः decl;
  वृक्षः old_decl;

  /* Validate and default VALUE.  */

  जइ (मानम् != NULL_वृक्षः)
    {
      /* Don't issue more errors for error_mark_node (i.e. an
	 undeclared identifier) - just ignore the value expression.  */
      जइ (मानम् == error_mark_ग्रन्थिः)
	मानम् = NULL_वृक्षः;
      अण्णहा जइ (!INTEGRAL_TYPE_P (वृक्षः_TYPE (मानम्)))
	{
	  error_at (loc, "enumerator value for %qE is not an integer constant",
		    name);
	  मानम् = NULL_वृक्षः;
	}
      अण्णहा
	{
	  जइ (वृक्षः_CODE (मानम्) != INTEGER_CST)
	    {
	      मानम् = c_fully_fold (मानम्, मिच्छ, रिक्त);
	      जइ (वृक्षः_CODE (मानम्) == INTEGER_CST)
		pedwarn (loc, OPT_Wpedantic,
			 "enumerator value for %qE is not an integer "
			 "constant expression", name);
	    }
	  जइ (वृक्षः_CODE (मानम्) != INTEGER_CST)
	    {
	      error ("enumerator value for %qE is not an integer constant",
		     name);
	      मानम् = NULL_वृक्षः;
	    }
	  अण्णहा
	    {
	      मानम् = default_conversion (मानम्);
	      constant_expression_warning (मानम्);
	    }
	}
    }

  /* Default based on previous value.  */
  /* It should no longer be possible to have NON_LVALUE_EXPR
     in the default.  */
  जइ (मानम् == NULL_वृक्षः)
    {
      मानम् = the_enum->enum_next_मानम्;
      जइ (the_enum->enum_overflow)
	error_at (loc, "overflow in enumeration values");
    }
  जइ (ENUM_FIXED_UNDERLYING_TYPE_P (the_enum->enum_type))
    {
      /* Enumeration constants must fit in the fixed underlying type.  */
      जइ (!int_fits_type_p (मानम्, ENUM_UNDERLYING_TYPE (the_enum->enum_type)))
	error_at (loc,
		  "enumerator value outside the range of underlying type");
      /* Enumeration constants for an enum with fixed underlying type
	 have the enum type, both inside and outside the
	 definition.  */
      मानम् = convert (the_enum->enum_type, मानम्);
    }
  अण्णहा जइ (flag_isoc23
	   && (old_decl = lookup_name_in_scope (name, current_scope))
	   && old_decl != error_mark_ग्रन्थिः
	   && वृक्षः_TYPE (old_decl)
	   && वृक्षः_TYPE (वृक्षः_TYPE (old_decl))
	   && वृक्षः_CODE (old_decl) == CONST_DECL)
    {
      /* Enumeration constants in a redeclaration have the previous type.  */
      वृक्षः previous_type = वृक्षः_TYPE (DECL_INITIAL (old_decl));
      जइ (!int_fits_type_p (मानम्, previous_type))
	{
	  error_at (loc, "value of redeclared enumerator outside the range "
			 "of %qT", previous_type);
	  locate_old_decl (old_decl);
	}
      मानम् = convert (previous_type, मानम्);
    }
  अण्णहा
    {
      /* Even though the underlying type of an enum is unspecified, the
	 type of enumeration constants is explicitly defined as int
	 (6.4.4.3/2 in the C99 Standard).  C23 allows any integer type, and
	 GCC allows such types for older standards as an extension.  */
      तार्किक warned_range = मिच्छ;
      जइ (!int_fits_type_p (मानम्,
			    (TYPE_UNSIGNED (वृक्षः_TYPE (मानम्))
			     ? uintmax_type_ग्रन्थिः
			     : intmax_type_ग्रन्थिः)))
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
				TYPE_UNSIGNED (वृक्षः_TYPE (मानम्))
				? "uintmax_t"
				: "intmax_t");
      जइ (!warned_range && !int_fits_type_p (मानम्, integer_type_ग्रन्थिः))
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
      जइ (int_fits_type_p (मानम्, integer_type_ग्रन्थिः))
	मानम् = convert (integer_type_ग्रन्थिः, मानम्);
    }

  /* Set basis for default for next value.  */
  जइ (ENUM_FIXED_UNDERLYING_TYPE_P (the_enum->enum_type))
    {
      वृक्षः underlying_type = ENUM_UNDERLYING_TYPE (the_enum->enum_type);
      जइ (वृक्षः_CODE (underlying_type) == BOOLEAN_TYPE)
	/* A value of 2 following a value of 1 overflows bool, but we
	   cannot carry out addition directly on bool without
	   promotion, and converting the result of arithmetic in a
	   wider type back to bool would not produce the right result
	   for this overflow check.  */
	the_enum->enum_next_मानम् = invert_truthvalue_loc (loc, मानम्);
      अण्णहा
	the_enum->enum_next_मानम्
	  = build_द्विमान_op (व्यञ्जकम्_LOC_OR_LOC (मानम्, निवेशः_location),
			     PLUS_व्यञ्जकम्, convert (underlying_type, मानम्),
			     convert (underlying_type, integer_one_ग्रन्थिः),
			     मिच्छ);
    }
  अण्णहा
    {
      /* In a redeclaration the type can already be the enumeral type.  */
      जइ (वृक्षः_CODE (वृक्षः_TYPE (मानम्)) == ENUMERAL_TYPE)
	मानम् = convert (ENUM_UNDERLYING_TYPE (वृक्षः_TYPE (मानम्)), मानम्);
      the_enum->enum_next_मानम्
	= build_द्विमान_op (व्यञ्जकम्_LOC_OR_LOC (मानम्, निवेशः_location),
			   PLUS_व्यञ्जकम्, मानम्, integer_one_ग्रन्थिः, मिच्छ);
    }
  the_enum->enum_overflow = वृक्षः_int_cst_lt (the_enum->enum_next_मानम्, मानम्);
  जइ (the_enum->enum_overflow
      && !ENUM_FIXED_UNDERLYING_TYPE_P (the_enum->enum_type))
    {
      /* Choose a wider type with the same signedness if
	 available.  */
      पूर्णाङ्क prec = TYPE_PRECISION (वृक्षः_TYPE (मानम्)) + 1;
      तार्किक unsignedp = TYPE_UNSIGNED (वृक्षः_TYPE (मानम्));
      वृक्षः new_type = (unsignedp
		       ? long_unsigned_type_ग्रन्थिः
		       : long_integer_type_ग्रन्थिः);
      जइ (prec > TYPE_PRECISION (new_type))
	new_type = (unsignedp
		    ? long_long_unsigned_type_ग्रन्थिः
		    : long_long_integer_type_ग्रन्थिः);
      जइ (prec > TYPE_PRECISION (new_type))
	new_type = (unsignedp
		    ? widest_unsigned_literal_type_ग्रन्थिः
		    : widest_integer_literal_type_ग्रन्थिः);
      जइ (prec <= TYPE_PRECISION (new_type))
	{
	  the_enum->enum_overflow = मिच्छ;
	  the_enum->enum_next_मानम्
	    = build_द्विमान_op (व्यञ्जकम्_LOC_OR_LOC (मानम्, निवेशः_location),
			       PLUS_व्यञ्जकम्, convert (new_type, मानम्),
			       integer_one_ग्रन्थिः, मिच्छ);
	  gcc_assert (!वृक्षः_int_cst_lt (the_enum->enum_next_मानम्, मानम्));
	}
    }

  /* Now create a declaration for the enum value name.  */

  decl = build_decl (decl_loc, CONST_DECL, name, वृक्षः_TYPE (मानम्));
  DECL_INITIAL (decl) = मानम्;
  DECL_CONTEXT (decl) = the_enum->enum_type;
  pushdecl (decl);

  प्रत्यागम वृक्षः_cons (decl, मानम्, NULL_वृक्षः);
}

/* Implement LANG_HOOKS_SIMULATE_ENUM_DECL.  */

वृक्षः
c_simulate_enum_decl (location_t loc, ध्रुव वर्ण *name,
		      vec<string_int_pair> *मानानि_ptr)
{
  location_t saved_loc = निवेशः_location;
  निवेशः_location = loc;

  संरचना c_enum_contents the_enum;
  वृक्षः enumtype = start_enum (loc, &the_enum, get_identifier (name),
			      NULL_वृक्षः, मिच्छ);

  वृक्षः मानम्_chain = NULL_वृक्षः;
  string_int_pair *मानम्;
  vec<string_int_pair> मानानि = *मानानि_ptr;
  unsigned पूर्णाङ्क i;
  FOR_EACH_VEC_ELT (मानानि, i, मानम्)
    {
      वृक्षः decl = build_enumerator (loc, loc, &the_enum,
				    get_identifier (मानम्->first),
				    build_int_cst (integer_type_ग्रन्थिः,
						   मानम्->second));
      वृक्षः_CHAIN (decl) = मानम्_chain;
      मानम्_chain = decl;
    }

  finish_enum (enumtype, nreverse (मानम्_chain), NULL_वृक्षः);

  निवेशः_location = saved_loc;
  प्रत्यागम enumtype;
}

/* Implement LANG_HOOKS_SIMULATE_RECORD_DECL.  */

वृक्षः
c_simulate_record_decl (location_t loc, ध्रुव वर्ण *name,
			array_slice<ध्रुव वृक्षः> fields)
{
  location_t saved_loc = निवेशः_location;
  निवेशः_location = loc;

  वर्ग c_struct_parse_info *struct_info;
  वृक्षः ident = get_identifier (name);
  वृक्षः type = start_struct (loc, RECORD_TYPE, ident, &struct_info);

  प्रति (unsigned पूर्णाङ्क i = 0; i < fields.size (); ++i)
    {
      DECL_FIELD_CONTEXT (fields[i]) = type;
      जइ (i > 0)
	DECL_CHAIN (fields[i - 1]) = fields[i];
    }

  finish_struct (loc, type, fields[0], NULL_वृक्षः, struct_info);

  वृक्षः decl = build_decl (loc, TYPE_DECL, ident, type);
  set_underlying_type (decl);
  lang_hooks.decls.pushdecl (decl);

  निवेशः_location = saved_loc;
  प्रत्यागम type;
}

/* Create the FUNCTION_DECL for a function definition.
   DECLSPECS, DECLARATOR and ATTRIBUTES are the parts of
   the declaration; they describe the function's name and the type it returns,
   but twisted together in a fashion that parallels the syntax of C.

   This function creates a binding context for the function body
   as well as setting up the FUNCTION_DECL in current_function_decl.

   Returns true on success.  If the DECLARATOR is not suitable for a function
   (it defines a datum instead), we return false to report a parse error.  */

तार्किक
start_function (संरचना c_declspecs *declspecs, संरचना c_declarator *declarator,
		वृक्षः attributes)
{
  वृक्षः decl1, old_decl;
  वृक्षः restype, resdecl;
  location_t loc;
  location_t result_loc;
  वृक्षः व्यञ्जकम् = रिक्त;

  current_function_returns_मानम् = 0;  /* Assume, until we see it does.  */
  current_function_returns_null = 0;
  current_function_returns_abnormally = 0;
  warn_about_return_type = 0;
  c_switch_राशिः = रिक्त;

  /* Indicate no valid break/continue context.  */
  in_statement = 0;

  decl1 = grokdeclarator (declarator, declspecs, FUNCDEF, सच्च, रिक्त,
			  &attributes, &व्यञ्जकम्, रिक्त, DEPRECATED_NORMAL);
  invoke_plugin_callbacks (PLUGIN_START_PARSE_FUNCTION, decl1);

  /* If the declarator is not suitable for a function definition,
     cause a syntax error.  */
  जइ (decl1 == NULL_वृक्षः
      || वृक्षः_CODE (decl1) != FUNCTION_DECL)
    प्रत्यागम मिच्छ;

  /* Nested functions may have variably modified (return) type.
     Make sure the size expression is evaluated at this point.  */
  जइ (व्यञ्जकम् && !current_scope->parm_flag)
    add_stmt (fold_convert (void_type_ग्रन्थिः, व्यञ्जकम्));

  loc = DECL_SOURCE_LOCATION (decl1);

  /* A nested function is not global.  */
  जइ (current_function_decl != NULL_वृक्षः)
    वृक्षः_PUBLIC (decl1) = 0;

  c_decl_attributes (&decl1, attributes, 0);

  जइ (DECL_DECLARED_INLINE_P (decl1)
      && DECL_UNINLINABLE (decl1)
      && lookup_attribute ("noinline", DECL_ATTRIBUTES (decl1)))
    {
      auto_urlify_attributes sentinel;
      warning_at (loc, OPT_Wattributes,
		  "inline function %qD given attribute %qs",
		  decl1, "noinline");
    }

  /* Handle gnu_inline attribute.  */
  जइ (declspecs->inline_p
      && !flag_gnu89_inline
      && वृक्षः_CODE (decl1) == FUNCTION_DECL
      && (lookup_attribute ("gnu_inline", DECL_ATTRIBUTES (decl1))
	  || current_function_decl))
    {
      जइ (declspecs->storage_class != csc_static)
	DECL_EXTERNAL (decl1) = !DECL_EXTERNAL (decl1);
    }

  announce_function (decl1);

  जइ (!COMPLETE_OR_VOID_TYPE_P (वृक्षः_TYPE (वृक्षः_TYPE (decl1))))
    {
      error_at (loc, "return type is an incomplete type");
      /* Make it return void instead.  */
      वृक्षः_TYPE (decl1)
	= c_build_function_type (void_type_ग्रन्थिः,
				 TYPE_ARG_TYPES (वृक्षः_TYPE (decl1)),
				 TYPE_NO_NAMED_ARGS_STDARG_P (वृक्षः_TYPE (decl1)));
    }

  जइ (warn_about_return_type)
    permerror_opt (loc, flag_isoc99 ? OPT_Wimplicit_int
		   : (warn_return_type > 0 ? OPT_Wreturn_type
		      : OPT_Wimplicit_int),
		   "return type defaults to %<int%>");

  /* Make the init_value nonzero so pushdecl knows this is not tentative.
     error_mark_node is replaced below (in pop_scope) with the BLOCK.  */
  DECL_INITIAL (decl1) = error_mark_ग्रन्थिः;

  /* If this definition isn't a prototype and we had a prototype declaration
     before, copy the arg type info from that prototype.  */
  old_decl = lookup_name_in_scope (DECL_NAME (decl1), current_scope);
  जइ (old_decl && वृक्षः_CODE (old_decl) != FUNCTION_DECL)
    old_decl = NULL_वृक्षः;

  current_function_prototype_locus = UNKNOWN_LOCATION;
  current_function_prototype_built_in = मिच्छ;
  current_function_prototype_arg_types = NULL_वृक्षः;
  वृक्षः newtype = वृक्षः_TYPE (decl1);
  वृक्षः oldtype = old_decl ? वृक्षः_TYPE (old_decl) : newtype;
  जइ (!prototype_p (newtype))
    {
      वृक्षः oldrt = वृक्षः_TYPE (oldtype);
      वृक्षः newrt = वृक्षः_TYPE (newtype);
      जइ (old_decl != NULL_वृक्षः
	  && वृक्षः_CODE (oldtype) == FUNCTION_TYPE
	  && comptypes (oldrt, newrt)
	  && !TYPE_NO_NAMED_ARGS_STDARG_P (oldtype))
	{
	  जइ (stdarg_p (oldtype))
	    {
	      auto_diagnostic_group d;
	      warning_at (loc, 0, "%q+D defined as variadic function "
			  "without prototype", decl1);
	      locate_old_decl (old_decl);
	    }
	  वृक्षः_TYPE (decl1) = composite_type (oldtype, newtype);
	  current_function_prototype_locus = DECL_SOURCE_LOCATION (old_decl);
	  current_function_prototype_built_in
	    = C_DECL_BUILTIN_PROTOTYPE (old_decl);
	  current_function_prototype_arg_types
	    = TYPE_ARG_TYPES (newtype);
	}
      जइ (वृक्षः_PUBLIC (decl1))
	{
	  /* If there is an external prototype declaration of this
	     function, record its location but do not copy information
	     to this decl.  This may be an invisible declaration
	     (built-in or in a scope which has finished) or simply
	     have more refined argument types than any declaration
	     found above.  */
	  संरचना c_binding *b;
	  प्रति (b = I_चिह्नम्_BINDING (DECL_NAME (decl1)); b; b = b->shadowed)
	    जइ (B_IN_SCOPE (b, external_scope))
	      भङ्ग;
	  जइ (b)
	    {
	      वृक्षः ext_decl, ext_type;
	      ext_decl = b->decl;
	      ext_type = b->u.type ? b->u.type : वृक्षः_TYPE (ext_decl);
	      जइ (वृक्षः_CODE (ext_type) == FUNCTION_TYPE
		  && comptypes (वृक्षः_TYPE (वृक्षः_TYPE (decl1)),
				वृक्षः_TYPE (ext_type)))
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
  जइ (warn_deprecated_non_prototype
      && old_decl != NULL_वृक्षः
      && वृक्षः_CODE (oldtype) == FUNCTION_TYPE
      && !TYPE_ARG_TYPES (oldtype)
      && !TYPE_NO_NAMED_ARGS_STDARG_P (oldtype)
      && (TYPE_ARG_TYPES (newtype)
	  && वृक्षः_मानम् (TYPE_ARG_TYPES (newtype)) != void_type_ग्रन्थिः))
    {
      तार्किक warned = warning_at (loc, OPT_Wdeprecated_non_prototype,
				"ISO C23 does not allow defining"
				" parameters for function %qE declared"
				" without parameters",
				decl1);
      जइ (warned)
	inform (DECL_SOURCE_LOCATION (old_decl), "declared here");
    }

  /* Optionally warn of old-fashioned def with no previous prototype.  */
  जइ (warn_strict_prototypes
      && old_decl != error_mark_ग्रन्थिः
      && !prototype_p (वृक्षः_TYPE (decl1))
      && C_DECL_ISNT_PROTOTYPE (old_decl))
    warning_at (loc, OPT_Wstrict_prototypes,
		"function declaration isn%'t a prototype");
  /* Optionally warn of any global def with no previous prototype.  */
  अण्णहा जइ (warn_missing_prototypes
	   && old_decl != error_mark_ग्रन्थिः
	   && वृक्षः_PUBLIC (decl1)
	   && !MAIN_NAME_P (DECL_NAME (decl1))
	   && C_DECL_ISNT_PROTOTYPE (old_decl)
	   && !DECL_DECLARED_INLINE_P (decl1))
    warning_at (loc, OPT_Wmissing_prototypes,
		"no previous prototype for %qD", decl1);
  /* Optionally warn of any def with no previous prototype
     if the function has already been used.  */
  अण्णहा जइ (warn_missing_prototypes
	   && old_decl != NULL_वृक्षः
	   && old_decl != error_mark_ग्रन्थिः
	   && वृक्षः_USED (old_decl)
	   && !prototype_p (वृक्षः_TYPE (old_decl)))
    warning_at (loc, OPT_Wmissing_prototypes,
		"%qD was used with no prototype before its definition", decl1);
  /* Optionally warn of any global def with no previous declaration.  */
  अण्णहा जइ (warn_missing_declarations
	   && वृक्षः_PUBLIC (decl1)
	   && old_decl == NULL_वृक्षः
	   && !MAIN_NAME_P (DECL_NAME (decl1))
	   && !DECL_DECLARED_INLINE_P (decl1))
    warning_at (loc, OPT_Wmissing_declarations,
		"no previous declaration for %qD",
		decl1);
  /* Optionally warn of any def with no previous declaration
     if the function has already been used.  */
  अण्णहा जइ (warn_missing_declarations
	   && old_decl != NULL_वृक्षः
	   && old_decl != error_mark_ग्रन्थिः
	   && वृक्षः_USED (old_decl)
	   && C_DECL_IMPLICIT (old_decl))
    warning_at (loc, OPT_Wmissing_declarations,
		"%qD was used with no declaration before its definition", decl1);

  /* This function exists in static storage.
     (This does not mean `static' in the C sense!)  */
  वृक्षः_STATIC (decl1) = 1;

  /* This is the earliest point at which we might know the assembler
     name of the function.  Thus, if it's set before this, die horribly.  */
  gcc_assert (!DECL_ASSEMBLER_NAME_SET_P (decl1));

  /* If #pragma weak was used, mark the decl weak now.  */
  जइ (current_scope == file_scope)
    maybe_apply_pragma_weak (decl1);

  /* Warn for unlikely, improbable, or stupid declarations of `main'.  */
  जइ (warn_main && MAIN_NAME_P (DECL_NAME (decl1)))
    {
      जइ (TYPE_MAIN_VARIANT (वृक्षः_TYPE (वृक्षः_TYPE (decl1)))
	  != integer_type_ग्रन्थिः)
	pedwarn (loc, OPT_Wmain, "return type of %qD is not %<int%>", decl1);
      अण्णहा जइ (TYPE_ATOMIC (वृक्षः_TYPE (वृक्षः_TYPE (decl1))))
	pedwarn (loc, OPT_Wmain, "%<_Atomic%>-qualified return type of %qD",
		 decl1);

      check_main_parameter_types (decl1);

      जइ (!वृक्षः_PUBLIC (decl1))
	pedwarn (loc, OPT_Wmain,
		 "%qD is normally a non-static function", decl1);
    }

  वृक्षः parms = current_function_arg_info->parms;
  जइ (old_decl)
    {
      location_t origloc = DECL_SOURCE_LOCATION (old_decl);
      warn_parms_array_mismatch (origloc, old_decl, parms);
    }

  /* To enable versions to be created across TU's we mark and mangle all
     non-default versioned functions.  */
  जइ (वृक्षः_CODE (decl1) == FUNCTION_DECL
      && !TARGET_HAS_FMV_TARGET_ATTRIBUTE
      && get_target_version (decl1).is_valid ())
    {
      maybe_mark_function_versioned (decl1);
      जइ (current_scope != file_scope)
	error ("versioned definitions are only allowed at file scope");
    }

  /* Record the decl so that the function name is defined.
     If we already have a decl for this name, and it is a FUNCTION_DECL,
     use the old decl.  */

  current_function_decl = pushdecl (decl1);

  जइ (वृक्षः access = build_attr_access_from_parms (parms, मिच्छ))
    decl_attributes (&current_function_decl, access, ATTR_FLAG_INTERNAL,
		     old_decl);

  प्रक्षिप_scope ();
  declare_parm_level ();

  /* Set the result decl source location to the location of the typespec.  */
  result_loc = (declspecs->locations[cdw_typespec] == UNKNOWN_LOCATION
		? loc : declspecs->locations[cdw_typespec]);
  restype = वृक्षः_TYPE (वृक्षः_TYPE (current_function_decl));
  resdecl = build_decl (result_loc, RESULT_DECL, NULL_वृक्षः, restype);
  DECL_ARTIFICIAL (resdecl) = 1;
  DECL_IGNORED_P (resdecl) = 1;
  DECL_RESULT (current_function_decl) = resdecl;

  start_fname_decls ();

  प्रत्यागम सच्च;
}

/* Subroutine of store_parm_decls which handles new-style function
   definitions (prototype format). The parms already have decls, so we
   need only record them as in effect and complain if any redundant
   old-style parm decls were written.  */
स्थिर शून्य
store_parm_decls_newstyle (वृक्षः fndecl, ध्रुव संरचना c_arg_info *arg_info)
{
  वृक्षः decl;
  c_arg_tag *tag;
  unsigned ix;

  जइ (current_scope->bindings)
    {
      error_at (DECL_SOURCE_LOCATION (fndecl),
		"old-style parameter declarations in prototyped "
		"function definition");

      /* Get rid of the old-style declarations.  */
      निष्कासय_scope ();
      प्रक्षिप_scope ();
    }
  /* Don't issue this warning for nested functions, and don't issue this
     warning if we got here because ARG_INFO_TYPES was error_mark_node
     (this happens when a function definition has just an ellipsis in
     its parameter list).  */
  अण्णहा जइ (!in_system_header_at (निवेशः_location)
	   && !current_function_scope
	   && arg_info->types != error_mark_ग्रन्थिः
	   && !arg_info->c23_empty_parens)
    warning_at (DECL_SOURCE_LOCATION (fndecl), OPT_Wtraditional,
		"traditional C rejects ISO C style function definitions");

  /* Now make all the parameter declarations visible in the function body.
     We can bypass most of the grunt work of pushdecl.  */
  प्रति (decl = arg_info->parms; decl; decl = DECL_CHAIN (decl))
    {
      DECL_CONTEXT (decl) = current_function_decl;
      जइ (DECL_NAME (decl))
	{
	  bind (DECL_NAME (decl), decl, current_scope,
		/*invisible=*/मिच्छ, /*nested=*/मिच्छ,
		UNKNOWN_LOCATION);
	  जइ (!वृक्षः_USED (decl))
	    warn_if_shadowing (decl);
	}
      अण्णहा
	pedwarn_c11 (DECL_SOURCE_LOCATION (decl), OPT_Wmissing_parameter_name,
		     "ISO C does not support omitting parameter names in "
		     "function definitions before C23");
    }

  /* Record the parameter list in the function declaration.  */
  DECL_ARGUMENTS (fndecl) = arg_info->parms;

  /* Now make all the ancillary declarations visible, likewise.  */
  प्रति (decl = arg_info->others; decl; decl = DECL_CHAIN (decl))
    {
      DECL_CONTEXT (decl) = current_function_decl;
      जइ (DECL_NAME (decl))
	bind (DECL_NAME (decl), decl, current_scope,
	      /*invisible=*/मिच्छ,
	      /*nested=*/(वृक्षः_CODE (decl) == FUNCTION_DECL),
	      UNKNOWN_LOCATION);
    }

  /* And all the tag declarations.  */
  FOR_EACH_VEC_SAFE_ELT_REVERSE (arg_info->tags, ix, tag)
    जइ (tag->id)
      bind (tag->id, tag->type, current_scope,
	    /*invisible=*/मिच्छ, /*nested=*/मिच्छ, UNKNOWN_LOCATION);
}

/* Subroutine of store_parm_decls which handles old-style function
   definitions (separate parameter list and declarations).  */

स्थिर शून्य
store_parm_decls_oldstyle (वृक्षः fndecl, ध्रुव संरचना c_arg_info *arg_info)
{
  संरचना c_binding *b;
  वृक्षः parm, decl, last;
  वृक्षः parmids = arg_info->parms;
  hash_set<वृक्षः> seen_args;

  जइ (!in_system_header_at (निवेशः_location))
    {
      जइ (flag_isoc23)
	pedwarn (DECL_SOURCE_LOCATION (fndecl),
		 OPT_Wold_style_definition, "old-style function definition");
      अण्णहा
	warning_at (DECL_SOURCE_LOCATION (fndecl),
		    OPT_Wold_style_definition,
		    "old-style function definition");
    }

  जइ (current_scope->had_vla_unspec)
    error ("%<[*]%> not allowed in other than function prototype scope");

  /* Match each formal parameter name with its declaration.  Save each
     decl in the appropriate TREE_PURPOSE slot of the parmids chain.  */
  प्रति (parm = parmids; parm; parm = वृक्षः_CHAIN (parm))
    {
      जइ (वृक्षः_मानम् (parm) == NULL_वृक्षः)
	{
	  error_at (DECL_SOURCE_LOCATION (fndecl),
		    "parameter name missing from parameter list");
	  वृक्षः_PURPOSE (parm) = NULL_वृक्षः;
	  अनुवर्त;
	}

      b = I_चिह्नम्_BINDING (वृक्षः_मानम् (parm));
      जइ (b && B_IN_CURRENT_SCOPE (b))
	{
	  decl = b->decl;
	  /* Skip erroneous parameters.  */
	  जइ (decl == error_mark_ग्रन्थिः)
	    अनुवर्त;
	  /* If we got something other than a PARM_DECL it is an error.  */
	  जइ (वृक्षः_CODE (decl) != PARM_DECL)
	    {
	      error_at (DECL_SOURCE_LOCATION (decl),
			"%qD declared as a non-parameter", decl);
	      अनुवर्त;
	    }
	  /* If the declaration is already marked, we have a duplicate
	     name.  Complain and ignore the duplicate.  */
	  अण्णहा जइ (seen_args.contains (decl))
	    {
	      error_at (DECL_SOURCE_LOCATION (decl),
			"multiple parameters named %qD", decl);
	      वृक्षः_PURPOSE (parm) = NULL_वृक्षः;
	      अनुवर्त;
	    }
	  /* If the declaration says "void", complain and turn it into
	     an int.  */
	  अण्णहा जइ (VOID_TYPE_P (वृक्षः_TYPE (decl)))
	    {
	      error_at (DECL_SOURCE_LOCATION (decl),
			"parameter %qD declared with void type", decl);
	      वृक्षः_TYPE (decl) = integer_type_ग्रन्थिः;
	      DECL_ARG_TYPE (decl) = integer_type_ग्रन्थिः;
	      layout_decl (decl, 0);
	    }
	  warn_if_shadowing (decl);
	}
      /* If no declaration found, default to int.  */
      अण्णहा
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
			     PARM_DECL, वृक्षः_मानम् (parm), integer_type_ग्रन्थिः);
	  DECL_ARG_TYPE (decl) = वृक्षः_TYPE (decl);
	  pushdecl (decl);
	  warn_if_shadowing (decl);

	  जइ (flag_isoc99)
	    permerror_opt (DECL_SOURCE_LOCATION (decl),
			   OPT_Wimplicit_int, "type of %qD defaults to %<int%>",
			   decl);
	  अण्णहा
	    warning_at (DECL_SOURCE_LOCATION (decl),
			OPT_Wmissing_parameter_type,
			"type of %qD defaults to %<int%>", decl);
	}

      वृक्षः_PURPOSE (parm) = decl;
      seen_args.add (decl);
    }

  /* Now examine the parms chain for incomplete declarations
     and declarations with no corresponding names.  */

  प्रति (b = current_scope->bindings; b; b = b->prev)
    {
      parm = b->decl;
      जइ (वृक्षः_CODE (parm) != PARM_DECL)
	अनुवर्त;

      जइ (वृक्षः_TYPE (parm) != error_mark_ग्रन्थिः
	  && !COMPLETE_TYPE_P (वृक्षः_TYPE (parm)))
	{
	  error_at (DECL_SOURCE_LOCATION (parm),
		    "parameter %qD has incomplete type", parm);
	  वृक्षः_TYPE (parm) = error_mark_ग्रन्थिः;
	}

      जइ (!seen_args.contains (parm))
	{
	  error_at (DECL_SOURCE_LOCATION (parm),
		    "declaration for parameter %qD but no such parameter",
		    parm);

	  /* Pretend the parameter was not missing.
	     This gets us to a standard state and minimizes
	     further error messages.  */
	  parmids = chainon (parmids, वृक्षः_cons (parm, 0, 0));
	}
    }

  /* Chain the declarations together in the order of the list of
     names.  Store that chain in the function decl, replacing the
     list of names.  Update the current scope to match.  */
  DECL_ARGUMENTS (fndecl) = NULL_वृक्षः;

  प्रति (parm = parmids; parm; parm = वृक्षः_CHAIN (parm))
    जइ (वृक्षः_PURPOSE (parm))
      भङ्ग;
  जइ (parm && वृक्षः_PURPOSE (parm))
    {
      last = वृक्षः_PURPOSE (parm);
      DECL_ARGUMENTS (fndecl) = last;

      प्रति (parm = वृक्षः_CHAIN (parm); parm; parm = वृक्षः_CHAIN (parm))
	जइ (वृक्षः_PURPOSE (parm))
	  {
	    DECL_CHAIN (last) = वृक्षः_PURPOSE (parm);
	    last = वृक्षः_PURPOSE (parm);
	  }
      DECL_CHAIN (last) = NULL_वृक्षः;
    }

  /* If there was a previous prototype,
     set the DECL_ARG_TYPE of each argument according to
     the type previously specified, and report any mismatches.  */

  जइ (current_function_prototype_arg_types)
    {
      वृक्षः type;
      प्रति (parm = DECL_ARGUMENTS (fndecl),
	     type = current_function_prototype_arg_types;
	   parm || (type != NULL_वृक्षः
		    && वृक्षः_मानम् (type) != error_mark_ग्रन्थिः
		    && TYPE_MAIN_VARIANT (वृक्षः_मानम् (type)) != void_type_ग्रन्थिः);
	   parm = DECL_CHAIN (parm), type = वृक्षः_CHAIN (type))
	{
	  जइ (parm == NULL_वृक्षः
	      || type == NULL_वृक्षः
	      || (वृक्षः_मानम् (type) != error_mark_ग्रन्थिः
		  && TYPE_MAIN_VARIANT (वृक्षः_मानम् (type)) == void_type_ग्रन्थिः))
	    {
	      जइ (current_function_prototype_built_in)
		warning_at (DECL_SOURCE_LOCATION (fndecl),
			    0, "number of arguments doesn%'t match "
			    "built-in prototype");
	      अण्णहा
		{
		  /* FIXME diagnostics: This should be the location of
		     FNDECL, but there is bug when a prototype is
		     declared inside function context, but defined
		     outside of it (e.g., gcc.dg/pr15698-2.c).  In
		     which case FNDECL gets the location of the
		     prototype, not the definition.  */
		  error_at (निवेशः_location,
			    "number of arguments doesn%'t match prototype");

		  error_at (current_function_prototype_locus,
			    "prototype declaration");
		}
	      भङ्ग;
	    }
	  /* Type for passing arg must be consistent with that
	     declared for the arg.  ISO C says we take the unqualified
	     type for parameters declared with qualified type.  */
	  जइ (वृक्षः_TYPE (parm) != error_mark_ग्रन्थिः
	      && वृक्षः_मानम् (type) != error_mark_ग्रन्थिः
	      && ((TYPE_ATOMIC (DECL_ARG_TYPE (parm))
		   != TYPE_ATOMIC (वृक्षः_मानम् (type)))
		  || !comptypes (TYPE_MAIN_VARIANT (DECL_ARG_TYPE (parm)),
				 TYPE_MAIN_VARIANT (वृक्षः_मानम् (type)))))
	    {
	      जइ ((TYPE_ATOMIC (DECL_ARG_TYPE (parm))
		   == TYPE_ATOMIC (वृक्षः_मानम् (type)))
		  && (TYPE_MAIN_VARIANT (वृक्षः_TYPE (parm))
		      == TYPE_MAIN_VARIANT (वृक्षः_मानम् (type))))
		{
		  /* Adjust argument to match prototype.  E.g. a previous
		     `int foo(float);' prototype causes
		     `int foo(x) float x; {...}' to be treated like
		     `int foo(float x) {...}'.  This is particularly
		     useful for argument types like uid_t.  */
		  DECL_ARG_TYPE (parm) = वृक्षः_TYPE (parm);

		  /* ??? Is it possible to get here with a
		     built-in prototype or will it always have
		     been diagnosed as conflicting with an
		     old-style definition and discarded?  */
		  जइ (current_function_prototype_built_in)
		    warning_at (DECL_SOURCE_LOCATION (parm),
				OPT_Wpedantic, "promoted argument %qD "
				"doesn%'t match built-in prototype", parm);
		  अण्णहा
		    {
		      pedwarn (DECL_SOURCE_LOCATION (parm),
			       OPT_Wpedantic, "promoted argument %qD "
			       "doesn%'t match prototype", parm);
		      pedwarn (current_function_prototype_locus, OPT_Wpedantic,
			       "prototype declaration");
		    }
		}
	      अण्णहा
		{
		  जइ (current_function_prototype_built_in)
		    warning_at (DECL_SOURCE_LOCATION (parm),
				0, "argument %qD doesn%'t match "
				"built-in prototype", parm);
		  अण्णहा
		    {
		      error_at (DECL_SOURCE_LOCATION (parm),
				"argument %qD doesn%'t match prototype", parm);
		      error_at (current_function_prototype_locus,
				"prototype declaration");
		    }
		}
	    }
	}
      TYPE_ACTUAL_ARG_TYPES (वृक्षः_TYPE (fndecl)) = NULL_वृक्षः;
    }

  /* Otherwise, create a prototype that would match.  */

  अण्णहा
    {
      वृक्षः actual = NULL_वृक्षः, last = NULL_वृक्षः, type;

      प्रति (parm = DECL_ARGUMENTS (fndecl); parm; parm = DECL_CHAIN (parm))
	{
	  type = वृक्षः_cons (NULL_वृक्षः, DECL_ARG_TYPE (parm), NULL_वृक्षः);
	  जइ (last)
	    वृक्षः_CHAIN (last) = type;
	  अण्णहा
	    actual = type;
	  last = type;
	}
      type = वृक्षः_cons (NULL_वृक्षः, void_type_ग्रन्थिः, NULL_वृक्षः);
      जइ (last)
	वृक्षः_CHAIN (last) = type;
      अण्णहा
	actual = type;

      /* We are going to assign a new value for the TYPE_ACTUAL_ARG_TYPES
	 of the type of this function, but we need to avoid having this
	 affect the types of other similarly-typed functions, so we must
	 first force the generation of an identical (but separate) type
	 node for the relevant function type.  The new node we create
	 will be a variant of the main variant of the original function
	 type.  */

      वृक्षः_TYPE (fndecl) = build_variant_type_copy (वृक्षः_TYPE (fndecl));

      TYPE_ACTUAL_ARG_TYPES (वृक्षः_TYPE (fndecl)) = actual;
    }
}

/* Store parameter declarations passed in ARG_INFO into the current
   function declaration.  */

शून्य
store_parm_decls_from (संरचना c_arg_info *arg_info)
{
  current_function_arg_info = arg_info;
  store_parm_decls ();
}

/* Called by walk_tree to look for and update context-less labels
   or labels with context in the parent function.  */

स्थिर वृक्षः
set_labels_context_r (वृक्षः *tp, पूर्णाङ्क *walk_subtrees, शून्य *data)
{
  वृक्षः ctx = static_cast<वृक्षः>(data);
  जइ (वृक्षः_CODE (*tp) == LABEL_व्यञ्जकम्
      && (DECL_CONTEXT (LABEL_व्यञ्जकम्_LABEL (*tp)) == NULL_वृक्षः
	  || DECL_CONTEXT (LABEL_व्यञ्जकम्_LABEL (*tp)) == DECL_CONTEXT (ctx)))
    {
      DECL_CONTEXT (LABEL_व्यञ्जकम्_LABEL (*tp)) = ctx;
      *walk_subtrees = 0;
    }

  प्रत्यागम NULL_वृक्षः;
}

/* Store the parameter declarations into the current function declaration.
   This is called after parsing the parameter declarations, before
   digesting the body of the function.

   For an old-style definition, construct a prototype out of the old-style
   parameter declarations and inject it into the function's type.  */

शून्य
store_parm_decls (शून्य)
{
  वृक्षः fndecl = current_function_decl;
  तार्किक proto;

  /* The argument information block for FNDECL.  */
  संरचना c_arg_info *arg_info = current_function_arg_info;
  current_function_arg_info = 0;

  /* True if this definition is written with a prototype.  In C23, an
     empty argument list was converted to (void) in grokparms; in
     older C standard versions, it does not give the function a type
     with a prototype for future calls.  */
  proto = arg_info->types != 0 || arg_info->no_named_args_stdarg_p;

  जइ (proto)
    store_parm_decls_newstyle (fndecl, arg_info);
  अण्णहा
    store_parm_decls_oldstyle (fndecl, arg_info);

  /* The next call to push_scope will be a function body.  */

  next_is_function_body = सच्च;

  /* Write a record describing this function definition to the prototypes
     file (if requested).  */

  gen_aux_info_record (fndecl, 1, 0, proto);

  /* Initialize the RTL code for the function.  */
  allocate_struct_function (fndecl, मिच्छ);

  जइ (warn_unused_local_typedefs)
    cfun->language = ggc_cleared_alloc<language_function> ();

  /* Begin the statement tree for this function.  */
  DECL_SAVED_वृक्षः (fndecl) = प्रक्षिप_stmt_list ();

  /* ??? Insert the contents of the pending sizes list into the function
     to be evaluated.  The only reason left to have this is
	void foo(int n, int array[n++])
     because we throw away the array type in favor of a pointer type, and
     thus won't naturally see the SAVE_EXPR containing the increment.  All
     other pending sizes would be handled by gimplify_parameters.  */
  जइ (arg_info->pending_sizes)
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
      walk_वृक्षः_without_duplicates (&arg_info->pending_sizes,
				    set_labels_context_r, fndecl);
      add_stmt (arg_info->pending_sizes);
    }
}

/* Store PARM_DECLs in PARMS into scope temporarily.  Used for
   c_finish_omp_declare_simd for function prototypes.  No diagnostics
   should be done.  */

शून्य
temp_store_parm_decls (वृक्षः fndecl, वृक्षः parms)
{
  प्रक्षिप_scope ();
  प्रति (वृक्षः p = parms; p; p = DECL_CHAIN (p))
    {
      DECL_CONTEXT (p) = fndecl;
      जइ (DECL_NAME (p))
	bind (DECL_NAME (p), p, current_scope,
	      /*invisible=*/मिच्छ, /*nested=*/मिच्छ,
	      UNKNOWN_LOCATION);
    }
}

/* Undo what temp_store_parm_decls did.  */

शून्य
temp_निष्कासय_parm_decls (शून्य)
{
  /* Clear all bindings in this temporary scope, so that
     pop_scope doesn't create a BLOCK.  */
  संरचना c_binding *b = current_scope->bindings;
  current_scope->bindings = रिक्त;
  प्रति (; b; b = free_binding_and_advance (b))
    {
      gcc_assert (वृक्षः_CODE (b->decl) == PARM_DECL
		  || b->decl == error_mark_ग्रन्थिः);
      gcc_assert (I_चिह्नम्_BINDING (b->id) == b);
      I_चिह्नम्_BINDING (b->id) = b->shadowed;
      जइ (b->shadowed && b->shadowed->u.type)
	वृक्षः_TYPE (b->shadowed->decl) = b->shadowed->u.type;
    }
  निष्कासय_scope ();
}


/* Finish up a function declaration and compile that function
   all the way to assembler language output.  Then free the storage
   for the function definition.

   This is called after parsing the body of the function definition.  */

शून्य
finish_function (location_t end_loc)
{
  वृक्षः fndecl = current_function_decl;

  जइ (c_dialect_objc ())
    objc_finish_function ();

  जइ (DECL_INITIAL (fndecl) && DECL_INITIAL (fndecl) != error_mark_ग्रन्थिः)
    BLOCK_SUPERCONTEXT (DECL_INITIAL (fndecl)) = fndecl;

  /* Must mark the RESULT_DECL as being in this function.  */

  जइ (DECL_RESULT (fndecl) && DECL_RESULT (fndecl) != error_mark_ग्रन्थिः)
    DECL_CONTEXT (DECL_RESULT (fndecl)) = fndecl;

  जइ (MAIN_NAME_P (DECL_NAME (fndecl)) && !वृक्षः_THIS_VOLATILE (fndecl)
      && TYPE_MAIN_VARIANT (वृक्षः_TYPE (वृक्षः_TYPE (fndecl)))
      == integer_type_ग्रन्थिः && flag_isoc99)
    {
      /* Hack.  We don't want the middle-end to warn that this return
	 is unreachable, so we mark its location as special.  Using
	 UNKNOWN_LOCATION has the problem that it gets clobbered in
	 annotate_one_with_locus.  A cleaner solution might be to
	 ensure ! should_carry_locus_p (stmt), but that needs a flag.
      */
      c_finish_return (BUILTINS_LOCATION, integer_zero_ग्रन्थिः, NULL_वृक्षः);
    }

  /* Tie off the statement tree for this function.  */
  DECL_SAVED_वृक्षः (fndecl) = निष्कासय_stmt_list (DECL_SAVED_वृक्षः (fndecl));

  finish_fname_decls ();

  /* Complain if there's no return statement only if option specified on
     command line.  */
  जइ (warn_return_type > 0
      && वृक्षः_CODE (वृक्षः_TYPE (वृक्षः_TYPE (fndecl))) != VOID_TYPE
      && !current_function_returns_मानम् && !current_function_returns_null
      /* Don't complain if we are no-return.  */
      && !current_function_returns_abnormally
      /* Don't complain if we are declared noreturn.  */
      && !वृक्षः_THIS_VOLATILE (fndecl)
      /* Don't warn for main().  */
      && !MAIN_NAME_P (DECL_NAME (fndecl))
      /* Or if they didn't actually specify a return type.  */
      && !C_FUNCTION_IMPLICIT_INT (fndecl)
      /* Normally, with -Wreturn-type, flow will complain, but we might
         optimize out static functions.  */
      && !वृक्षः_PUBLIC (fndecl)
      && targetm.warn_func_return (fndecl)
      && warning (OPT_Wreturn_type,
		  "no return statement in function returning non-void"))
    suppress_warning (fndecl, OPT_Wreturn_type);

  /* Complain about parameters that are only set, but never otherwise used.  */
  जइ (warn_unused_but_set_parameter)
    {
      वृक्षः decl;

      प्रति (decl = DECL_ARGUMENTS (fndecl);
	   decl;
	   decl = DECL_CHAIN (decl))
	जइ (वृक्षः_USED (decl)
	    && वृक्षः_CODE (decl) == PARM_DECL
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
  जइ (warn_unused_parameter)
    do_warn_unused_parameter (fndecl);

  /* Store the end of the function, so that we get good line number
     info for the epilogue.  */
  cfun->function_end_locus = end_loc;

  /* Finalize the ELF visibility for the function.  */
  c_determine_visibility (fndecl);

  /* For GNU C extern inline functions disregard inline limits.  */
  जइ (DECL_EXTERNAL (fndecl)
      && DECL_DECLARED_INLINE_P (fndecl)
      && (flag_gnu89_inline
	  || lookup_attribute ("gnu_inline", DECL_ATTRIBUTES (fndecl))))
    DECL_DISREGARD_INLINE_LIMITS (fndecl) = 1;

  /* Genericize before inlining.  Delay genericizing nested functions
     until their parent function is genericized.  Since finalizing
     requires GENERIC, delay that as well.  */

  जइ (DECL_INITIAL (fndecl) && DECL_INITIAL (fndecl) != error_mark_ग्रन्थिः
      && !undef_nested_function)
    {
      जइ (!decl_function_context (fndecl))
	{
	  invoke_plugin_callbacks (PLUGIN_PRE_GENERICIZE, fndecl);
	  c_genericize (fndecl);

	  /* ??? Objc emits functions after finalizing the compilation unit.
	     This should be cleaned up later and this conditional removed.  */
	  जइ (symtab->global_info_ready)
	    {
	      cgraph_ग्रन्थिः::add_new_function (fndecl, मिच्छ);
	      प्रत्यागम;
	    }
	  cgraph_ग्रन्थिः::finalize_function (fndecl, मिच्छ);
	}
      अण्णहा
	{
	  /* Register this function with cgraph just far enough to get it
	    added to our parent's nested function list.  Handy, since the
	    C front end doesn't have such a list.  */
	  (शून्य) cgraph_ग्रन्थिः::get_create (fndecl);
	}
    }

  जइ (!decl_function_context (fndecl))
    undef_nested_function = मिच्छ;

  जइ (cfun->language != रिक्त)
    {
      ggc_free (cfun->language);
      cfun->language = रिक्त;
    }

  /* We're leaving the context of this function, so zap cfun.
     It's still in DECL_STRUCT_FUNCTION, and we'll restore it in
     tree_rest_of_compilation.  */
  set_cfun (रिक्त);
  invoke_plugin_callbacks (PLUGIN_FINISH_PARSE_FUNCTION, current_function_decl);
  current_function_decl = रिक्त;
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

वृक्षः
check_for_loop_decls (location_t loc, तार्किक turn_off_iso_c99_error)
{
  संरचना c_binding *b;
  वृक्षः one_decl = NULL_वृक्षः;
  पूर्णाङ्क n_decls = 0;

  जइ (!turn_off_iso_c99_error)
    {
      स्थिर तार्किक hint = सच्च;
      /* If we get here, declarations have been used in a for loop without
	 the C99 for loop scope.  This doesn't make much sense, so don't
	 allow it.  */
      auto_diagnostic_group d;
      error_at (loc, "%<for%> loop initial declarations "
		"are only allowed in C99 or C11 mode");
      जइ (hint)
	{
	  inform (loc,
		  "use option %<-std=c99%>, %<-std=gnu99%>, %<-std=c11%> or "
		  "%<-std=gnu11%> to compile your code");
	  hint = मिच्छ;
	}
      प्रत्यागम NULL_वृक्षः;
    }
  अण्णहा
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

  प्रति (b = current_scope->bindings; b; b = b->prev)
    {
      वृक्षः id = b->id;
      वृक्षः decl = b->decl;

      जइ (!id)
	अनुवर्त;

      विकल्प (वृक्षः_CODE (decl))
	{
	पक्ष VAR_DECL:
	  {
	    location_t decl_loc = DECL_SOURCE_LOCATION (decl);
	    जइ (वृक्षः_STATIC (decl))
	      pedwarn_c11 (decl_loc, OPT_Wpedantic,
			   "declaration of static variable %qD in %<for%> "
			   "loop initial declaration", decl);
	    अण्णहा जइ (DECL_EXTERNAL (decl))
	      pedwarn_c11 (decl_loc, OPT_Wpedantic,
			   "declaration of %<extern%> variable %qD in %<for%> "
			   "loop initial declaration", decl);
	  }
	  भङ्ग;

	पक्ष RECORD_TYPE:
	  pedwarn_c11 (loc, OPT_Wpedantic,
		       "%<struct %E%> declared in %<for%> loop initial "
		       "declaration", id);
	  भङ्ग;
	पक्ष UNION_TYPE:
	  pedwarn_c11 (loc, OPT_Wpedantic,
		       "%<union %E%> declared in %<for%> loop initial "
		       "declaration",
		       id);
	  भङ्ग;
	पक्ष ENUMERAL_TYPE:
	  pedwarn_c11 (loc, OPT_Wpedantic,
		       "%<enum %E%> declared in %<for%> loop "
		       "initial declaration", id);
	  भङ्ग;
	स्वभाव:
	  pedwarn_c11 (loc, OPT_Wpedantic, "declaration of non-variable "
		       "%qD in %<for%> loop initial declaration", decl);
	}

      n_decls++;
      one_decl = decl;
    }

  प्रत्यागम n_decls == 1 ? one_decl : NULL_वृक्षः;
}

/* Save and reinitialize the variables
   used during compilation of a C function.  */

शून्य
c_प्रक्षिप_function_context (शून्य)
{
  संरचना language_function *p = cfun->language;
  /* cfun->language might have been already allocated by the use of
     -Wunused-local-typedefs.  In that case, just re-use it.  */
  जइ (p == रिक्त)
    cfun->language = p = ggc_cleared_alloc<language_function> ();

  p->base.x_stmt_वृक्षः = c_stmt_वृक्षः;
  c_stmt_वृक्षः.x_cur_stmt_list = vec_safe_copy (c_stmt_वृक्षः.x_cur_stmt_list);
  p->x_in_statement = in_statement;
  p->x_switch_राशिः = c_switch_राशिः;
  p->loop_names = loop_names;
  loop_names = vNULL;
  p->loop_names_hash = loop_names_hash;
  loop_names_hash = रिक्त;
  p->arg_info = current_function_arg_info;
  p->returns_मानम् = current_function_returns_मानम्;
  p->returns_null = current_function_returns_null;
  p->returns_abnormally = current_function_returns_abnormally;
  p->warn_about_return_type = warn_about_return_type;

  प्रक्षिप_function_context ();
}

/* Restore the variables used during compilation of a C function.  */

शून्य
c_निष्कासय_function_context (शून्य)
{
  संरचना language_function *p;

  निष्कासय_function_context ();
  p = cfun->language;

  /* When -Wunused-local-typedefs is in effect, cfun->languages is
     used to store data throughout the life time of the current cfun,
     So don't deallocate it.  */
  जइ (!warn_unused_local_typedefs)
    cfun->language = रिक्त;

  जइ (DECL_STRUCT_FUNCTION (current_function_decl) == 0
      && DECL_SAVED_वृक्षः (current_function_decl) == NULL_वृक्षः)
    {
      /* Stop pointing to the local nodes about to be freed.  */
      /* But DECL_INITIAL must remain nonzero so we know this
	 was an actual function definition.  */
      DECL_INITIAL (current_function_decl) = error_mark_ग्रन्थिः;
      DECL_ARGUMENTS (current_function_decl) = NULL_वृक्षः;
    }

  c_stmt_वृक्षः = p->base.x_stmt_वृक्षः;
  p->base.x_stmt_वृक्षः.x_cur_stmt_list = रिक्त;
  in_statement = p->x_in_statement;
  c_switch_राशिः = p->x_switch_राशिः;
  loop_names.release ();
  loop_names = p->loop_names;
  p->loop_names = vNULL;
  delete loop_names_hash;
  loop_names_hash = p->loop_names_hash;
  p->loop_names_hash = रिक्त;
  current_function_arg_info = p->arg_info;
  current_function_returns_मानम् = p->returns_मानम्;
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

stmt_वृक्षः
current_stmt_वृक्षः (शून्य)
{
  प्रत्यागम &c_stmt_वृक्षः;
}

/* Return the global value of T as a symbol.  */

वृक्षः
identifier_global_मानम्	(वृक्षः t)
{
  संरचना c_binding *b;

  प्रति (b = I_चिह्नम्_BINDING (t); b; b = b->shadowed)
    जइ (B_IN_FILE_SCOPE (b) || B_IN_EXTERNAL_SCOPE (b))
      प्रत्यागम b->decl;

  प्रत्यागम NULL_वृक्षः;
}

/* Return the global value of tag T as a symbol.  */

वृक्षः
identifier_global_tag (वृक्षः t)
{
  संरचना c_binding *b;

  प्रति (b = I_TAG_BINDING (t); b; b = b->shadowed)
    जइ (B_IN_FILE_SCOPE (b) || B_IN_EXTERNAL_SCOPE (b))
      प्रत्यागम b->decl;

  प्रत्यागम NULL_वृक्षः;
}

/* Returns non-zero (result of __has_builtin) if NAME refers to a built-in
   function or function-like operator.  */

पूर्णाङ्क
names_builtin_p (ध्रुव वर्ण *name)
{
  वृक्षः id = get_identifier (name);
  जइ (वृक्षः decl = identifier_global_मानम् (id))
    प्रत्यागम वृक्षः_CODE (decl) == FUNCTION_DECL && DECL_IS_UNDECLARED_BUILTIN (decl);

  /* Also detect common reserved C words that aren't strictly built-in
     functions.  */
  विकल्प (C_RID_CODE (id))
    {
    पक्ष RID_BUILTIN_ASSOC_BARRIER:
    पक्ष RID_BUILTIN_BITREVERSEG:
    पक्ष RID_BUILTIN_BSWAPG:
    पक्ष RID_BUILTIN_CONVERTVECTOR:
    पक्ष RID_BUILTIN_HAS_ATTRIBUTE:
    पक्ष RID_BUILTIN_SHUFFLE:
    पक्ष RID_BUILTIN_SHUFFLEVECTOR:
    पक्ष RID_BUILTIN_STDC:
    पक्ष RID_BUILTIN_COUNTED_BY_REF:
    पक्ष RID_CHOOSE_व्यञ्जकम्:
    पक्ष RID_OFFSETOF:
    पक्ष RID_TYPES_COMPATIBLE_P:
    पक्ष RID_C23_VA_START:
    पक्ष RID_VA_ARG:
      प्रत्यागम 1;
    स्वभाव:
      भङ्ग;
    }

  प्रत्यागम 0;
}

/* In C, the only C-linkage public declaration is at file scope.  */

वृक्षः
c_linkage_bindings (वृक्षः name)
{
  प्रत्यागम identifier_global_मानम् (name);
}

/* Record a builtin type for C.  If NAME is non-NULL, it is the name used;
   otherwise the name is found in ridpointers from RID_INDEX.  */

शून्य
record_builtin_type (गणना rid rid_index, ध्रुव वर्ण *name, वृक्षः type)
{
  वृक्षः id, decl;
  जइ (name == 0)
    id = ridpointers[(पूर्णाङ्क) rid_index];
  अण्णहा
    id = get_identifier (name);
  decl = build_decl (UNKNOWN_LOCATION, TYPE_DECL, id, type);
  pushdecl (decl);
  जइ (debug_hooks->type_decl)
    debug_hooks->type_decl (decl, मिच्छ);
}

/* Return a c_parm structure with the given SPECS, ATTRS and DECLARATOR.  */

संरचना c_parm *
build_c_parm (संरचना c_declspecs *specs, वृक्षः attrs,
	      संरचना c_declarator *declarator,
	      location_t loc)
{
  संरचना c_parm *ret = XOBNEW (&parser_obstack, संरचना c_parm);
  ret->specs = specs;
  ret->attrs = attrs;
  ret->declarator = declarator;
  ret->loc = loc;
  प्रत्यागम ret;
}

/* Return a declarator with nested attributes.  TARGET is the inner
   declarator to which these attributes apply.  ATTRS are the
   attributes.  */

संरचना c_declarator *
build_attrs_declarator (वृक्षः attrs, संरचना c_declarator *target)
{
  संरचना c_declarator *ret = XOBNEW (&parser_obstack, संरचना c_declarator);
  ret->kind = cdk_attrs;
  ret->declarator = target;
  ret->u.attrs = attrs;
  प्रत्यागम ret;
}

/* Return a declarator for a function with arguments specified by ARGS
   and return type specified by TARGET.  */

संरचना c_declarator *
build_function_declarator (संरचना c_arg_info *args,
			   संरचना c_declarator *target)
{
  संरचना c_declarator *ret = XOBNEW (&parser_obstack, संरचना c_declarator);
  ret->kind = cdk_function;
  ret->declarator = target;
  ret->u.arg_info = args;
  प्रत्यागम ret;
}

/* Return a declarator for the identifier IDENT (which may be
   NULL_TREE for an abstract declarator).  */

संरचना c_declarator *
build_id_declarator (वृक्षः ident)
{
  संरचना c_declarator *ret = XOBNEW (&parser_obstack, संरचना c_declarator);
  ret->kind = cdk_id;
  ret->declarator = 0;
  ret->u.id.id = ident;
  ret->u.id.attrs = NULL_वृक्षः;
  /* Default value - may get reset to a more precise location. */
  ret->id_loc = निवेशः_location;
  प्रत्यागम ret;
}

/* Return something to represent absolute declarators containing a *.
   TARGET is the absolute declarator that the * contains.
   TYPE_QUALS_ATTRS is a structure for type qualifiers and attributes
   to apply to the pointer type.  */

संरचना c_declarator *
make_pointer_declarator (संरचना c_declspecs *type_quals_attrs,
			 संरचना c_declarator *target)
{
  वृक्षः attrs;
  पूर्णाङ्क quals = 0;
  संरचना c_declarator *itarget = target;
  संरचना c_declarator *ret = XOBNEW (&parser_obstack, संरचना c_declarator);
  जइ (type_quals_attrs)
    {
      attrs = type_quals_attrs->attrs;
      quals = quals_from_declspecs (type_quals_attrs);
      जइ (attrs != NULL_वृक्षः)
	itarget = build_attrs_declarator (attrs, target);
    }
  ret->kind = cdk_pointer;
  ret->declarator = itarget;
  ret->u.pointer_quals = quals;
  प्रत्यागम ret;
}

/* Return a pointer to a structure for an empty list of declaration
   specifiers.  */

संरचना c_declspecs *
build_null_declspecs (शून्य)
{
  संरचना c_declspecs *ret = XOBNEW (&parser_obstack, संरचना c_declspecs);
  memset (ret, 0, परिमाण *ret);
  ret->align_log = -1;
  ret->typespec_word = cts_none;
  ret->storage_class = csc_none;
  ret->व्यञ्जकम्_const_operands = सच्च;
  ret->typespec_kind = ctsk_none;
  ret->address_space = ADDR_SPACE_GENERIC;
  प्रत्यागम ret;
}

/* Add the address space ADDRSPACE to the declaration specifiers
   SPECS, returning SPECS.  */

संरचना c_declspecs *
declspecs_add_addrspace (location_t location,
			 संरचना c_declspecs *specs, addr_space_t as)
{
  specs->non_sc_seen_p = सच्च;
  specs->declspecs_seen_p = सच्च;
  specs->non_std_attrs_seen_p = सच्च;

  जइ (!ADDR_SPACE_GENERIC_P (specs->address_space)
      && specs->address_space != as)
    error ("incompatible address space qualifiers %qs and %qs",
	   c_addr_space_name (as),
	   c_addr_space_name (specs->address_space));
  अण्णहा
    {
      specs->address_space = as;
      specs->locations[cdw_address_space] = location;
    }
  प्रत्यागम specs;
}

/* Add the type qualifier QUAL to the declaration specifiers SPECS,
   returning SPECS.  */

संरचना c_declspecs *
declspecs_add_qual (location_t loc,
		    संरचना c_declspecs *specs, वृक्षः qual)
{
  गणना rid i;
  तार्किक dupe = मिच्छ;
  specs->non_sc_seen_p = सच्च;
  specs->declspecs_seen_p = सच्च;
  specs->non_std_attrs_seen_p = सच्च;
  gcc_assert (वृक्षः_CODE (qual) == IDENTIFIER_ग्रन्थिः
	      && C_IS_RESERVED_WORD (qual));
  i = C_RID_CODE (qual);
  location_t prev_loc = UNKNOWN_LOCATION;
  विकल्प (i)
    {
    पक्ष RID_CONST:
      dupe = specs->const_p;
      specs->const_p = सच्च;
      prev_loc = specs->locations[cdw_const];
      specs->locations[cdw_const] = loc;
      भङ्ग;
    पक्ष RID_VOLATILE:
      dupe = specs->volatile_p;
      specs->volatile_p = सच्च;
      prev_loc = specs->locations[cdw_volatile];
      specs->locations[cdw_volatile] = loc;
      भङ्ग;
    पक्ष RID_RESTRICT:
      dupe = specs->restrict_p;
      specs->restrict_p = सच्च;
      prev_loc = specs->locations[cdw_restrict];
      specs->locations[cdw_restrict] = loc;
      भङ्ग;
    पक्ष RID_ATOMIC:
      dupe = specs->atomic_p;
      specs->atomic_p = सच्च;
      prev_loc = specs->locations[cdw_atomic];
      specs->locations[cdw_atomic] = loc;
      भङ्ग;
    स्वभाव:
      gcc_unreachable ();
    }
  जइ (dupe)
    {
      तार्किक warned = pedwarn_c90 (loc, OPT_Wpedantic,
				 "duplicate %qE declaration specifier", qual);
      जइ (!warned
	  && warn_duplicate_decl_specifier
	  && prev_loc >= RESERVED_LOCATION_गणनम्
	  && !from_macro_expansion_at (prev_loc)
	  && !from_macro_expansion_at (loc))
	warning_at (loc, OPT_Wduplicate_decl_specifier,
		    "duplicate %qE declaration specifier", qual);
    }
  प्रत्यागम specs;
}

/* Add the type specifier TYPE to the declaration specifiers SPECS,
   returning SPECS.  */

संरचना c_declspecs *
declspecs_add_type (location_t loc, संरचना c_declspecs *specs,
		    संरचना c_typespec spec)
{
  वृक्षः type = spec.spec;
  specs->non_sc_seen_p = सच्च;
  specs->declspecs_seen_p = सच्च;
  specs->non_std_attrs_seen_p = सच्च;
  specs->typespec_kind = spec.kind;
  जइ (वृक्षः_DEPRECATED (type))
    specs->deprecated_p = सच्च;
  जइ (वृक्षः_UNAVAILABLE (type))
    specs->unavailable_p = सच्च;

  /* As a type specifier is present, "auto" must be used as a storage
     class specifier, not for type deduction.  */
  जइ (specs->c23_auto_p)
    {
      specs->c23_auto_p = मिच्छ;
      जइ (specs->storage_class != csc_none)
	error ("multiple storage classes in declaration specifiers");
      अण्णहा जइ (specs->thread_p)
	error ("%qs used with %<auto%>",
	       specs->thread_gnu_p ? "__thread" : "_Thread_local");
      अण्णहा जइ (specs->constexpr_p)
	/* auto may only be used with another storage class specifier,
	   such as constexpr, if the type is inferred.  */
	error ("%<auto%> used with %<constexpr%>");
      अण्णहा
	specs->storage_class = csc_auto;
    }

  /* Handle type specifier keywords.  */
  जइ (वृक्षः_CODE (type) == IDENTIFIER_ग्रन्थिः
      && C_IS_RESERVED_WORD (type)
      && C_RID_CODE (type) != RID_CXX_COMPAT_WARN)
    {
      गणना rid i = C_RID_CODE (type);
      जइ (specs->type)
	{
	  error_at (loc, "two or more data types in declaration specifiers");
	  प्रत्यागम specs;
	}
      जइ ((पूर्णाङ्क) i <= (पूर्णाङ्क) RID_LAST_MODIFIER)
	{
	  /* "long", "short", "signed", "unsigned", "_Complex" or "_Sat".  */
	  तार्किक dupe = मिच्छ;
	  विकल्प (i)
	    {
	    पक्ष RID_LONG:
	      जइ (specs->long_long_p)
		{
		  error_at (loc, "%<long long long%> is too long for GCC");
		  भङ्ग;
		}
	      जइ (specs->long_p)
		{
		  जइ (specs->typespec_word == cts_double)
		    {
		      error_at (loc,
				"both %qs and %qs in declaration specifiers",
				"long long", "double");
		      भङ्ग;
		    }
		  pedwarn_c90 (loc, OPT_Wlong_long,
			       "ISO C90 does not support %<long long%>");
		  specs->long_long_p = 1;
		  specs->locations[cdw_long_long] = loc;
		  भङ्ग;
		}
	      जइ (specs->short_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "short");
	      अण्णहा जइ (specs->typespec_word == cts_auto_type)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "__auto_type");
	      अण्णहा जइ (specs->typespec_word == cts_void)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "void");
	      अण्णहा जइ (specs->typespec_word == cts_int_n)
		error_at (loc,
			  "both %qs and %<__int%d%> in declaration specifiers",
			  "long", int_n_data[specs->u.int_n_idx].bitsize);
	      अण्णहा जइ (specs->typespec_word == cts_bool)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "_Bool");
	      अण्णहा जइ (specs->typespec_word == cts_bitint)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "_BitInt");
	      अण्णहा जइ (specs->typespec_word == cts_char)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "char");
	      अण्णहा जइ (specs->typespec_word == cts_float)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "float");
	      अण्णहा जइ (specs->typespec_word == cts_floatn_nx)
		error_at (loc,
			  "both %qs and %<_Float%d%s%> in declaration "
			  "specifiers", "long",
			  floatn_nx_types[specs->u.floatn_nx_idx].n,
			  floatn_nx_types[specs->u.floatn_nx_idx].extended
			  ? "x"
			  : "");
	      अण्णहा जइ (specs->typespec_word == cts_dfloat32)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "_Decimal32");
	      अण्णहा जइ (specs->typespec_word == cts_dfloat64)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "_Decimal64");
	      अण्णहा जइ (specs->typespec_word == cts_dfloat128)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "_Decimal128");
	      अण्णहा जइ (specs->typespec_word == cts_dfloat64x)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "_Decimal64x");
	      अण्णहा
		{
		  specs->long_p = सच्च;
		  specs->locations[cdw_long] = loc;
		}
	      भङ्ग;
	    पक्ष RID_SHORT:
	      dupe = specs->short_p;
	      जइ (specs->long_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "short");
	      अण्णहा जइ (specs->typespec_word == cts_auto_type)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "__auto_type");
	      अण्णहा जइ (specs->typespec_word == cts_void)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "void");
	      अण्णहा जइ (specs->typespec_word == cts_int_n)
		error_at (loc,
			  "both %qs and %<__int%d%> in declaration specifiers",
			  "short", int_n_data[specs->u.int_n_idx].bitsize);
	      अण्णहा जइ (specs->typespec_word == cts_bool)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "_Bool");
	      अण्णहा जइ (specs->typespec_word == cts_bitint)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "_BitInt");
	      अण्णहा जइ (specs->typespec_word == cts_char)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "char");
	      अण्णहा जइ (specs->typespec_word == cts_float)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "float");
	      अण्णहा जइ (specs->typespec_word == cts_double)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "double");
	      अण्णहा जइ (specs->typespec_word == cts_floatn_nx)
		error_at (loc,
			  "both %qs and %<_Float%d%s%> in declaration "
			  "specifiers", "short",
			  floatn_nx_types[specs->u.floatn_nx_idx].n,
			  floatn_nx_types[specs->u.floatn_nx_idx].extended
			  ? "x"
			  : "");
	      अण्णहा जइ (specs->typespec_word == cts_dfloat32)
                error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "_Decimal32");
	      अण्णहा जइ (specs->typespec_word == cts_dfloat64)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "_Decimal64");
	      अण्णहा जइ (specs->typespec_word == cts_dfloat128)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "_Decimal128");
	      अण्णहा जइ (specs->typespec_word == cts_dfloat64x)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "_Decimal64x");
	      अण्णहा
		{
		  specs->short_p = सच्च;
		  specs->locations[cdw_short] = loc;
		}
	      भङ्ग;
	    पक्ष RID_SIGNED:
	      dupe = specs->signed_p;
	      जइ (specs->unsigned_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "unsigned");
	      अण्णहा जइ (specs->typespec_word == cts_auto_type)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "__auto_type");
	      अण्णहा जइ (specs->typespec_word == cts_void)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "void");
	      अण्णहा जइ (specs->typespec_word == cts_bool)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "_Bool");
	      अण्णहा जइ (specs->typespec_word == cts_float)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "float");
	      अण्णहा जइ (specs->typespec_word == cts_double)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "double");
	      अण्णहा जइ (specs->typespec_word == cts_floatn_nx)
		error_at (loc,
			  "both %qs and %<_Float%d%s%> in declaration "
			  "specifiers", "signed",
			  floatn_nx_types[specs->u.floatn_nx_idx].n,
			  floatn_nx_types[specs->u.floatn_nx_idx].extended
			  ? "x"
			  : "");
	      अण्णहा जइ (specs->typespec_word == cts_dfloat32)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "_Decimal32");
	      अण्णहा जइ (specs->typespec_word == cts_dfloat64)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "_Decimal64");
	      अण्णहा जइ (specs->typespec_word == cts_dfloat128)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "_Decimal128");
	      अण्णहा जइ (specs->typespec_word == cts_dfloat64x)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "_Decimal64x");
	      अण्णहा
		{
		  specs->signed_p = सच्च;
		  specs->locations[cdw_signed] = loc;
		}
	      भङ्ग;
	    पक्ष RID_UNSIGNED:
	      dupe = specs->unsigned_p;
	      जइ (specs->signed_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "unsigned");
	      अण्णहा जइ (specs->typespec_word == cts_auto_type)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "__auto_type");
	      अण्णहा जइ (specs->typespec_word == cts_void)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "void");
	      अण्णहा जइ (specs->typespec_word == cts_bool)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "_Bool");
	      अण्णहा जइ (specs->typespec_word == cts_float)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "float");
	      अण्णहा जइ (specs->typespec_word == cts_double)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "double");
	      अण्णहा जइ (specs->typespec_word == cts_floatn_nx)
		error_at (loc,
			  "both %qs and %<_Float%d%s%> in declaration "
			  "specifiers", "unsigned",
			  floatn_nx_types[specs->u.floatn_nx_idx].n,
			  floatn_nx_types[specs->u.floatn_nx_idx].extended
			  ? "x"
			  : "");
              अण्णहा जइ (specs->typespec_word == cts_dfloat32)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "_Decimal32");
	      अण्णहा जइ (specs->typespec_word == cts_dfloat64)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "_Decimal64");
	      अण्णहा जइ (specs->typespec_word == cts_dfloat128)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "_Decimal128");
	      अण्णहा जइ (specs->typespec_word == cts_dfloat64x)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "_Decimal64x");
	      अण्णहा
		{
		  specs->unsigned_p = सच्च;
		  specs->locations[cdw_unsigned] = loc;
		}
	      भङ्ग;
	    पक्ष RID_COMPLEX:
	      dupe = specs->complex_p;
	      जइ (!in_system_header_at (loc))
		pedwarn_c90 (loc, OPT_Wpedantic,
			     "ISO C90 does not support complex types");
	      जइ (specs->typespec_word == cts_auto_type)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "__auto_type");
	      अण्णहा जइ (specs->typespec_word == cts_void)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "void");
	      अण्णहा जइ (specs->typespec_word == cts_bool)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "_Bool");
	      अण्णहा जइ (specs->typespec_word == cts_bitint)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "_BitInt");
              अण्णहा जइ (specs->typespec_word == cts_dfloat32)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "_Decimal32");
	      अण्णहा जइ (specs->typespec_word == cts_dfloat64)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "_Decimal64");
	      अण्णहा जइ (specs->typespec_word == cts_dfloat128)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "_Decimal128");
	      अण्णहा जइ (specs->typespec_word == cts_dfloat64x)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "_Decimal64x");
	      अण्णहा जइ (specs->typespec_word == cts_fract)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "_Fract");
	      अण्णहा जइ (specs->typespec_word == cts_accum)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "_Accum");
	      अण्णहा जइ (specs->saturating_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "_Sat");
	      अण्णहा
		{
		  specs->complex_p = सच्च;
		  specs->locations[cdw_complex] = loc;
		}
	      भङ्ग;
	    पक्ष RID_SAT:
	      dupe = specs->saturating_p;
	      pedwarn (loc, OPT_Wpedantic,
		       "ISO C does not support saturating types");
	      जइ (specs->typespec_word == cts_int_n)
		error_at (loc,
			  "both %qs and %<__int%d%> in declaration specifiers",
			  "_Sat", int_n_data[specs->u.int_n_idx].bitsize);
	      अण्णहा जइ (specs->typespec_word == cts_auto_type)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "__auto_type");
	      अण्णहा जइ (specs->typespec_word == cts_void)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "void");
	      अण्णहा जइ (specs->typespec_word == cts_bool)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "_Bool");
	      अण्णहा जइ (specs->typespec_word == cts_bitint)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "_BitInt");
	      अण्णहा जइ (specs->typespec_word == cts_char)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "char");
	      अण्णहा जइ (specs->typespec_word == cts_int)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "int");
	      अण्णहा जइ (specs->typespec_word == cts_float)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "float");
	      अण्णहा जइ (specs->typespec_word == cts_double)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "double");
	      अण्णहा जइ (specs->typespec_word == cts_floatn_nx)
		error_at (loc,
			  "both %qs and %<_Float%d%s%> in declaration "
			  "specifiers", "_Sat",
			  floatn_nx_types[specs->u.floatn_nx_idx].n,
			  floatn_nx_types[specs->u.floatn_nx_idx].extended
			  ? "x"
			  : "");
              अण्णहा जइ (specs->typespec_word == cts_dfloat32)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "_Decimal32");
	      अण्णहा जइ (specs->typespec_word == cts_dfloat64)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "_Decimal64");
	      अण्णहा जइ (specs->typespec_word == cts_dfloat128)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "_Decimal128");
	      अण्णहा जइ (specs->typespec_word == cts_dfloat64x)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "_Decimal64x");
	      अण्णहा जइ (specs->complex_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "complex");
	      अण्णहा
		{
		  specs->saturating_p = सच्च;
		  specs->locations[cdw_saturating] = loc;
		}
	      भङ्ग;
	    स्वभाव:
	      gcc_unreachable ();
	    }

	  जइ (dupe)
	    error_at (loc, "duplicate %qE", type);

	  प्रत्यागम specs;
	}
      अण्णहा
	{
	  /* "void", "_Bool", "char", "int", "float", "double",
	     "_FloatN", "_FloatNx", "_Decimal32", "__intN",
	     "_Decimal64", "_Decimal128", "_Fract", "_Accum", "_BitInt(N)" or
	     "__auto_type".  */
	  जइ (specs->typespec_word != cts_none)
	    {
	      जइ (i == RID_BOOL)
		{
		  auto_diagnostic_group d;
		  जइ (specs->storage_class == csc_typedef)
		    error_at (loc,
			      "%qs cannot be defined via %<typedef%>",
			      IDENTIFIER_POINTER (type));
		  अण्णहा
		    error_at (loc,
			      "%qs cannot be used here",
			      IDENTIFIER_POINTER (type));
		  add_note_about_new_keyword (loc, type);
		}
	      अण्णहा
		error_at (loc,
			  "two or more data types in declaration specifiers");
	      प्रत्यागम specs;
	    }
	  विकल्प (i)
	    {
	    पक्ष RID_AUTO_TYPE:
	      जइ (specs->long_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "__auto_type");
	      अण्णहा जइ (specs->short_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "__auto_type");
	      अण्णहा जइ (specs->signed_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "__auto_type");
	      अण्णहा जइ (specs->unsigned_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "__auto_type");
	      अण्णहा जइ (specs->complex_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "__auto_type");
	      अण्णहा जइ (specs->saturating_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "__auto_type");
	      अण्णहा
		{
		  specs->typespec_word = cts_auto_type;
		  specs->locations[cdw_typespec] = loc;
		}
	      प्रत्यागम specs;
	    पक्ष RID_INT_N_0:
	    पक्ष RID_INT_N_1:
	    पक्ष RID_INT_N_2:
	    पक्ष RID_INT_N_3:
	      specs->u.int_n_idx = i - RID_INT_N_0;
	      जइ (!in_system_header_at (निवेशः_location)
		  /* If the INT_N type ends in "__", and so is of the format
		     "__intN__", don't pedwarn.  */
		  && (strncmp (IDENTIFIER_POINTER (type)
			       + (IDENTIFIER_LENGTH (type) - 2), "__", 2) != 0))
		pedwarn (loc, OPT_Wpedantic,
			 "ISO C does not support %<__int%d%> types",
			 int_n_data[specs->u.int_n_idx].bitsize);

	      जइ (specs->long_p)
		error_at (loc,
			  "both %<__int%d%> and %qs in declaration specifiers",
			  int_n_data[specs->u.int_n_idx].bitsize, "long");
	      अण्णहा जइ (specs->saturating_p)
		error_at (loc,
			  "both %qs and %<__int%d%> in declaration specifiers",
			  "_Sat", int_n_data[specs->u.int_n_idx].bitsize);
	      अण्णहा जइ (specs->short_p)
		error_at (loc,
			  "both %<__int%d%> and %qs in declaration specifiers",
			  int_n_data[specs->u.int_n_idx].bitsize, "short");
	      अण्णहा जइ (! int_n_enabled_p[specs->u.int_n_idx])
		{
		  specs->typespec_word = cts_int_n;
		  error_at (loc,
			    "%<__int%d%> is not supported on this target",
			    int_n_data[specs->u.int_n_idx].bitsize);
		}
	      अण्णहा
		{
		  specs->typespec_word = cts_int_n;
		  specs->locations[cdw_typespec] = loc;
		}
	      प्रत्यागम specs;
	    पक्ष RID_VOID:
	      जइ (specs->long_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "void");
	      अण्णहा जइ (specs->short_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "void");
	      अण्णहा जइ (specs->signed_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "void");
	      अण्णहा जइ (specs->unsigned_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "void");
	      अण्णहा जइ (specs->complex_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "void");
	      अण्णहा जइ (specs->saturating_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "void");
	      अण्णहा
		{
		  specs->typespec_word = cts_void;
		  specs->locations[cdw_typespec] = loc;
		}
	      प्रत्यागम specs;
	    पक्ष RID_BOOL:
	      जइ (!in_system_header_at (loc))
		pedwarn_c90 (loc, OPT_Wpedantic,
			     "ISO C90 does not support boolean types");
	      जइ (specs->long_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "_Bool");
	      अण्णहा जइ (specs->short_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "_Bool");
	      अण्णहा जइ (specs->signed_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "_Bool");
	      अण्णहा जइ (specs->unsigned_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "_Bool");
	      अण्णहा जइ (specs->complex_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "_Bool");
	      अण्णहा जइ (specs->saturating_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "_Bool");
	      अण्णहा
		{
		  specs->typespec_word = cts_bool;
		  specs->locations[cdw_typespec] = loc;
		}
	      प्रत्यागम specs;
	    पक्ष RID_CHAR:
	      जइ (specs->long_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "char");
	      अण्णहा जइ (specs->short_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "char");
	      अण्णहा जइ (specs->saturating_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "char");
	      अण्णहा
		{
		  specs->typespec_word = cts_char;
		  specs->locations[cdw_typespec] = loc;
		}
	      प्रत्यागम specs;
	    पक्ष RID_INT:
	      जइ (specs->saturating_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "int");
	      अण्णहा
		{
		  specs->typespec_word = cts_int;
		  specs->locations[cdw_typespec] = loc;
		}
	      प्रत्यागम specs;
	    पक्ष RID_FLOAT:
	      जइ (specs->long_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "float");
	      अण्णहा जइ (specs->short_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "float");
	      अण्णहा जइ (specs->signed_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "float");
	      अण्णहा जइ (specs->unsigned_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "float");
	      अण्णहा जइ (specs->saturating_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "float");
	      अण्णहा
		{
		  specs->typespec_word = cts_float;
		  specs->locations[cdw_typespec] = loc;
		}
	      प्रत्यागम specs;
	    पक्ष RID_DOUBLE:
	      जइ (specs->long_long_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long long", "double");
	      अण्णहा जइ (specs->short_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "double");
	      अण्णहा जइ (specs->signed_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "double");
	      अण्णहा जइ (specs->unsigned_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "double");
	      अण्णहा जइ (specs->saturating_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "double");
	      अण्णहा
		{
		  specs->typespec_word = cts_double;
		  specs->locations[cdw_typespec] = loc;
		}
	      प्रत्यागम specs;
	    CASE_RID_FLOATN_NX:
	      specs->u.floatn_nx_idx = i - RID_FLOATN_NX_FIRST;
	      जइ (!in_system_header_at (निवेशः_location))
		pedwarn_c11 (loc, OPT_Wpedantic,
			     "ISO C does not support the %<_Float%d%s%> type"
			     " before C23",
			     floatn_nx_types[specs->u.floatn_nx_idx].n,
			     floatn_nx_types[specs->u.floatn_nx_idx].extended
			     ? "x"
			     : "");

	      जइ (specs->long_p)
		error_at (loc,
			  "both %qs and %<_Float%d%s%> in declaration "
			  "specifiers", "long",
			  floatn_nx_types[specs->u.floatn_nx_idx].n,
			  floatn_nx_types[specs->u.floatn_nx_idx].extended
			  ? "x"
			  : "");
	      अण्णहा जइ (specs->short_p)
		error_at (loc,
			  "both %qs and %<_Float%d%s%> in declaration "
			  "specifiers", "short",
			  floatn_nx_types[specs->u.floatn_nx_idx].n,
			  floatn_nx_types[specs->u.floatn_nx_idx].extended
			  ? "x"
			  : "");
	      अण्णहा जइ (specs->signed_p)
		error_at (loc,
			  "both %qs and %<_Float%d%s%> in declaration "
			  "specifiers", "signed",
			  floatn_nx_types[specs->u.floatn_nx_idx].n,
			  floatn_nx_types[specs->u.floatn_nx_idx].extended
			  ? "x"
			  : "");
	      अण्णहा जइ (specs->unsigned_p)
		error_at (loc,
			  "both %qs and %<_Float%d%s%> in declaration "
			  "specifiers", "unsigned",
			  floatn_nx_types[specs->u.floatn_nx_idx].n,
			  floatn_nx_types[specs->u.floatn_nx_idx].extended
			  ? "x"
			  : "");
	      अण्णहा जइ (specs->saturating_p)
		error_at (loc,
			  "both %qs and %<_Float%d%s%> in declaration "
			  "specifiers", "_Sat",
			  floatn_nx_types[specs->u.floatn_nx_idx].n,
			  floatn_nx_types[specs->u.floatn_nx_idx].extended
			  ? "x"
			  : "");
	      अण्णहा जइ (FLOATN_NX_TYPE_ग्रन्थिः (specs->u.floatn_nx_idx) == NULL_वृक्षः)
		{
		  specs->typespec_word = cts_floatn_nx;
		  error_at (loc,
			    "%<_Float%d%s%> is not supported on this target",
			    floatn_nx_types[specs->u.floatn_nx_idx].n,
			    floatn_nx_types[specs->u.floatn_nx_idx].extended
			    ? "x"
			    : "");
		}
	      अण्णहा
		{
		  specs->typespec_word = cts_floatn_nx;
		  specs->locations[cdw_typespec] = loc;
		}
	      प्रत्यागम specs;
	    पक्ष RID_DFLOAT32:
	    पक्ष RID_DFLOAT64:
	    पक्ष RID_DFLOAT128:
	    पक्ष RID_DFLOAT64X:
	      {
		ध्रुव वर्ण *str;
		जइ (i == RID_DFLOAT32)
		  str = "_Decimal32";
		अण्णहा जइ (i == RID_DFLOAT64)
		  str = "_Decimal64";
		अण्णहा जइ (i == RID_DFLOAT128)
		  str = "_Decimal128";
		अण्णहा
		  str = "_Decimal64x";
		जइ (specs->long_long_p)
		  error_at (loc,
			    "both %qs and %qs in declaration specifiers",
			    "long long", str);
		जइ (specs->long_p)
		  error_at (loc,
			    "both %qs and %qs in declaration specifiers",
			    "long", str);
		अण्णहा जइ (specs->short_p)
		  error_at (loc,
			    "both %qs and %qs in declaration specifiers",
			    "short", str);
		अण्णहा जइ (specs->signed_p)
		  error_at (loc,
			    "both %qs and %qs in declaration specifiers",
			    "signed", str);
		अण्णहा जइ (specs->unsigned_p)
		  error_at (loc,
			    "both %qs and %qs in declaration specifiers",
			    "unsigned", str);
                अण्णहा जइ (specs->complex_p)
                  error_at (loc,
			    "both %qs and %qs in declaration specifiers",
			    "complex", str);
                अण्णहा जइ (specs->saturating_p)
                  error_at (loc,
			    "both %qs and %qs in declaration specifiers",
			    "_Sat", str);
		अण्णहा जइ (i == RID_DFLOAT32)
		  specs->typespec_word = cts_dfloat32;
		अण्णहा जइ (i == RID_DFLOAT64)
		  specs->typespec_word = cts_dfloat64;
		अण्णहा जइ (i == RID_DFLOAT128)
		  specs->typespec_word = cts_dfloat128;
		अण्णहा
		  specs->typespec_word = cts_dfloat64x;
		specs->locations[cdw_typespec] = loc;
	      }
	      जइ (!targetm.decimal_float_supported_p ())
		error_at (loc,
			  "decimal floating-point not supported "
			  "for this target");
	      pedwarn_c11 (loc, OPT_Wpedantic,
			   "ISO C does not support decimal floating-point "
			   "before C23");
	      प्रत्यागम specs;
	    पक्ष RID_FRACT:
	    पक्ष RID_ACCUM:
	      {
		ध्रुव वर्ण *str;
		जइ (i == RID_FRACT)
		  str = "_Fract";
		अण्णहा
		  str = "_Accum";
                जइ (specs->complex_p)
                  error_at (loc,
			    "both %qs and %qs in declaration specifiers",
			    "complex", str);
		अण्णहा जइ (i == RID_FRACT)
		    specs->typespec_word = cts_fract;
		अण्णहा
		    specs->typespec_word = cts_accum;
		specs->locations[cdw_typespec] = loc;
	      }
	      जइ (!targetm.fixed_point_supported_p ())
		error_at (loc,
			  "fixed-point types not supported for this target");
	      pedwarn (loc, OPT_Wpedantic,
		       "ISO C does not support fixed-point types");
	      प्रत्यागम specs;
	    पक्ष RID_BITINT:
	      जइ (specs->long_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "_BitInt");
	      अण्णहा जइ (specs->short_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "_BitInt");
	      अण्णहा जइ (specs->complex_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "_BitInt");
	      अण्णहा जइ (specs->saturating_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "_BitInt");
	      अण्णहा
		{
		  specs->typespec_word = cts_bitint;
		  specs->locations[cdw_typespec] = loc;
		  specs->u.bitint_prec = -1;
		  जइ (error_operand_p (spec.व्यञ्जकम्))
		    प्रत्यागम specs;
		  जइ (वृक्षः_CODE (spec.व्यञ्जकम्) != INTEGER_CST
		      || !INTEGRAL_TYPE_P (वृक्षः_TYPE (spec.व्यञ्जकम्)))
		    {
		      error_at (loc, "%<_BitInt%> argument is not an integer "
				     "constant expression");
		      प्रत्यागम specs;
		    }
		  जइ (वृक्षः_int_cst_sgn (spec.व्यञ्जकम्) <= 0)
		    {
		      error_at (loc, "%<_BitInt%> argument %qE is not a "
				     "positive integer constant expression",
				spec.व्यञ्जकम्);
		      प्रत्यागम specs;
		    }
		  जइ (wi::to_widest (spec.व्यञ्जकम्) > WIDE_INT_MAX_PRECISION - 1)
		    {
		      error_at (loc, "%<_BitInt%> argument %qE is larger than "
				     "%<BITINT_MAXWIDTH%> %qd",
				spec.व्यञ्जकम्, (पूर्णाङ्क) WIDE_INT_MAX_PRECISION - 1);
		      प्रत्यागम specs;
		    }
		  specs->u.bitint_prec = वृक्षः_to_uhwi (spec.व्यञ्जकम्);
		  संरचना bitint_info info;
		  जइ (!targetm.c.bitint_type_info (specs->u.bitint_prec,
						   &info))
		    {
		      sorry_at (loc, "%<_BitInt(%d)%> is not supported on "
				     "this target", specs->u.bitint_prec);
		      specs->u.bitint_prec = -1;
		      प्रत्यागम specs;
		    }
		}
	      प्रत्यागम specs;
	    स्वभाव:
	      /* ObjC reserved word "id", handled below.  */
	      भङ्ग;
	    }
	}
    }

  /* Now we have a typedef (a TYPE_DECL node), an identifier (some
     form of ObjC type, cases such as "int" and "long" being handled
     above), a TYPE (struct, union, enum and typeof specifiers) or an
     ERROR_MARK.  In none of these cases may there have previously
     been any type specifiers.  */
  जइ (specs->type || specs->typespec_word != cts_none
      || specs->long_p || specs->short_p || specs->signed_p
      || specs->unsigned_p || specs->complex_p)
    error_at (loc, "two or more data types in declaration specifiers");
  अण्णहा जइ (वृक्षः_CODE (type) == TYPE_DECL)
    {
      specs->type = वृक्षः_TYPE (type);
      जइ (वृक्षः_TYPE (type) != error_mark_ग्रन्थिः)
	{
	  mark_decl_used (type, मिच्छ);
	  specs->decl_attr = DECL_ATTRIBUTES (type);
	  specs->typedef_p = सच्च;
	  specs->explicit_signed_p = C_TYPEDEF_EXPLICITLY_SIGNED (type);
	  specs->locations[cdw_typedef] = loc;

	  /* If this typedef name is defined in a struct, then a C++
	     lookup would return a different value.  */
	  जइ (warn_cxx_compat
	      && I_चिह्नम्_BINDING (DECL_NAME (type))->in_struct)
	    warning_at (loc, OPT_Wc___compat,
			"C++ lookup of %qD would return a field, not a type",
			type);

	  /* If we are parsing a struct, record that a struct field
	     used a typedef.  */
	  जइ (warn_cxx_compat && struct_parse_info != रिक्त)
	    struct_parse_info->typedefs_seen.safe_प्रक्षिप (type);
	}
    }
  अण्णहा जइ (वृक्षः_CODE (type) == IDENTIFIER_ग्रन्थिः)
    {
      वृक्षः t = lookup_name (type);
      जइ (!t || वृक्षः_CODE (t) != TYPE_DECL)
	error_at (loc, "%qE fails to be a typedef or built in type", type);
      अण्णहा जइ (वृक्षः_TYPE (t) == error_mark_ग्रन्थिः)
	;
      अण्णहा
	{
	  specs->type = वृक्षः_TYPE (t);
	  specs->locations[cdw_typespec] = loc;
	}
    }
  अण्णहा
    {
      जइ (वृक्षः_CODE (type) != ERROR_MARK)
	{
	  जइ (spec.kind == ctsk_typeof)
	    {
	      specs->typedef_p = सच्च;
	      specs->locations[cdw_typedef] = loc;
	    }

	  जइ (वृक्षः_CODE (type) == RECORD_TYPE || वृक्षः_CODE (type) == UNION_TYPE
	      || वृक्षः_CODE (type) == ENUMERAL_TYPE)
	    mark_decl_used (TYPE_STUB_DECL (type), मिच्छ);

	  जइ (spec.व्यञ्जकम्)
	    {
	      वृक्षः व्यञ्जकम् = save_व्यञ्जकम् (fold_convert (void_type_ग्रन्थिः, spec.व्यञ्जकम्));
	      जइ (specs->व्यञ्जकम्)
		specs->व्यञ्जकम् = build2 (COMPOUND_व्यञ्जकम्, वृक्षः_TYPE (व्यञ्जकम्),
				      specs->व्यञ्जकम्, व्यञ्जकम्);
	      अण्णहा
		specs->व्यञ्जकम् = व्यञ्जकम्;
	      specs->व्यञ्जकम्_const_operands &= spec.व्यञ्जकम्_const_operands;
	    }
	}
      specs->type = type;
      जइ (spec.has_enum_type_specifier
	  && spec.kind != ctsk_tagdef)
	specs->enum_type_specifier_ref_p = सच्च;
    }

  प्रत्यागम specs;
}

/* Add the storage class specifier or function specifier SCSPEC to the
   declaration specifiers SPECS, returning SPECS.  */

संरचना c_declspecs *
declspecs_add_scspec (location_t loc,
		      संरचना c_declspecs *specs,
		      वृक्षः scspec)
{
  गणना rid i;
  गणना c_storage_class n = csc_none;
  तार्किक dupe = मिच्छ;
  specs->declspecs_seen_p = सच्च;
  specs->non_std_attrs_seen_p = सच्च;
  gcc_assert (वृक्षः_CODE (scspec) == IDENTIFIER_ग्रन्थिः
	      && C_IS_RESERVED_WORD (scspec));
  i = C_RID_CODE (scspec);
  जइ (specs->non_sc_seen_p)
    warning (OPT_Wold_style_declaration,
             "%qE is not at beginning of declaration", scspec);
  विकल्प (i)
    {
    पक्ष RID_INLINE:
      /* C99 permits duplicate inline.  Although of doubtful utility,
	 it seems simplest to permit it in gnu89 mode as well, as
	 there is also little utility in maintaining this as a
	 difference between gnu89 and C99 inline.  */
      dupe = मिच्छ;
      specs->inline_p = सच्च;
      specs->locations[cdw_inline] = loc;
      भङ्ग;
    पक्ष RID_NORETURN:
      /* Duplicate _Noreturn is permitted.  */
      dupe = मिच्छ;
      specs->noreturn_p = सच्च;
      specs->locations[cdw_noreturn] = loc;
      भङ्ग;
    पक्ष RID_THREAD:
      dupe = specs->thread_p;
      जइ (specs->storage_class == csc_auto)
	error ("%qE used with %<auto%>", scspec);
      अण्णहा जइ (specs->storage_class == csc_register)
	error ("%qE used with %<register%>", scspec);
      अण्णहा जइ (specs->storage_class == csc_typedef)
	error ("%qE used with %<typedef%>", scspec);
      अण्णहा जइ (specs->constexpr_p)
	error ("%qE used with %<constexpr%>", scspec);
      अण्णहा
	{
	  specs->thread_p = सच्च;
	  specs->thread_gnu_p = (strcmp (IDENTIFIER_POINTER (scspec),
					 "__thread") == 0);
	  /* A diagnostic is not required for the use of this
	     identifier in the implementation namespace; only diagnose
	     it for the C11 spelling because of existing code using
	     the other spelling.  */
	  जइ (!specs->thread_gnu_p)
	    {
	      जइ (flag_isoc99)
		pedwarn_c99 (loc, OPT_Wpedantic,
			     "ISO C99 does not support %qE", scspec);
	      अण्णहा
		pedwarn_c99 (loc, OPT_Wpedantic,
			     "ISO C90 does not support %qE", scspec);
	    }
	  specs->locations[cdw_thread] = loc;
	}
      भङ्ग;
    पक्ष RID_AUTO:
      जइ (flag_isoc23
	  && specs->typespec_kind == ctsk_none
	  && specs->storage_class != csc_typedef)
	{
	  /* "auto" potentially used for type deduction.  */
	  जइ (specs->c23_auto_p)
	    error ("duplicate %qE", scspec);
	  specs->c23_auto_p = सच्च;
	  प्रत्यागम specs;
	}
      n = csc_auto;
      /* auto may only be used with another storage class specifier,
	 such as constexpr, if the type is inferred.  */
      जइ (specs->constexpr_p)
	error ("%qE used with %<constexpr%>", scspec);
      भङ्ग;
    पक्ष RID_EXTERN:
      n = csc_extern;
      /* Diagnose "__thread extern".  */
      जइ (specs->thread_p && specs->thread_gnu_p)
	error ("%<__thread%> before %<extern%>");
      भङ्ग;
    पक्ष RID_REGISTER:
      n = csc_register;
      भङ्ग;
    पक्ष RID_STATIC:
      n = csc_static;
      /* Diagnose "__thread static".  */
      जइ (specs->thread_p && specs->thread_gnu_p)
	error ("%<__thread%> before %<static%>");
      भङ्ग;
    पक्ष RID_TYPEDEF:
      n = csc_typedef;
      जइ (specs->c23_auto_p)
	{
	  error ("%<typedef%> used with %<auto%>");
	  specs->c23_auto_p = मिच्छ;
	}
      भङ्ग;
    पक्ष RID_CONSTEXPR:
      dupe = specs->constexpr_p;
      जइ (specs->storage_class == csc_extern)
	error ("%qE used with %<extern%>", scspec);
      अण्णहा जइ (specs->storage_class == csc_typedef)
	error ("%qE used with %<typedef%>", scspec);
      अण्णहा जइ (specs->storage_class == csc_auto)
	/* auto may only be used with another storage class specifier,
	   such as constexpr, if the type is inferred.  */
	error ("%qE used with %<auto%>", scspec);
      अण्णहा जइ (specs->thread_p)
	error ("%qE used with %qs", scspec,
	       specs->thread_gnu_p ? "__thread" : "_Thread_local");
      अण्णहा
	specs->constexpr_p = सच्च;
      भङ्ग;
    स्वभाव:
      gcc_unreachable ();
    }
  जइ (n != csc_none && n == specs->storage_class)
    dupe = सच्च;
  जइ (dupe)
    {
      जइ (i == RID_THREAD)
	error ("duplicate %<_Thread_local%> or %<__thread%>");
      अण्णहा
	error ("duplicate %qE", scspec);
    }
  जइ (n != csc_none)
    {
      जइ (specs->storage_class != csc_none && n != specs->storage_class)
	{
	  error ("multiple storage classes in declaration specifiers");
	}
      अण्णहा
	{
	  specs->storage_class = n;
	  specs->locations[cdw_storage_class] = loc;
	  जइ (n != csc_extern && n != csc_static && specs->thread_p)
	    {
	      error ("%qs used with %qE",
		     specs->thread_gnu_p ? "__thread" : "_Thread_local",
		     scspec);
	      specs->thread_p = मिच्छ;
	    }
	  जइ (n != csc_auto && n != csc_register && n != csc_static
	      && specs->constexpr_p)
	    {
	      error ("%<constexpr%> used with %qE", scspec);
	      specs->constexpr_p = मिच्छ;
	    }
	}
    }
  प्रत्यागम specs;
}

/* Add the attributes ATTRS to the declaration specifiers SPECS,
   returning SPECS.  */

संरचना c_declspecs *
declspecs_add_attrs (location_t loc, संरचना c_declspecs *specs, वृक्षः attrs)
{
  specs->attrs = chainon (attrs, specs->attrs);
  specs->locations[cdw_attributes] = loc;
  specs->declspecs_seen_p = सच्च;
  /* In the case of standard attributes at the start of the
     declaration, the caller will reset this.  */
  specs->non_std_attrs_seen_p = सच्च;
  प्रत्यागम specs;
}

/* Add an _Alignas specifier (expression ALIGN, or type whose
   alignment is ALIGN) to the declaration specifiers SPECS, returning
   SPECS.  */
संरचना c_declspecs *
declspecs_add_alignas (location_t loc,
		       संरचना c_declspecs *specs, वृक्षः align)
{
  specs->alignas_p = सच्च;
  specs->locations[cdw_alignas] = loc;
  जइ (align == error_mark_ग्रन्थिः)
    प्रत्यागम specs;

  /* Only accept the alignment if it's valid and greater than
     the current one.  Zero is invalid but by C11 required to
     be silently ignored.  */
  पूर्णाङ्क align_log = check_user_alignment (align, मिच्छ, /* warn_zero = */मिच्छ);
  जइ (align_log > specs->align_log)
    specs->align_log = align_log;
  प्रत्यागम specs;
}

/* Combine "long", "short", "signed", "unsigned" and "_Complex" type
   specifiers with any other type specifier to determine the resulting
   type.  This is where ISO C checks on complex types are made, since
   "_Complex long" is a prefix of the valid ISO C type "_Complex long
   double".  Also apply postfix standard attributes to modify the type.  */

संरचना c_declspecs *
finish_declspecs (संरचना c_declspecs *specs)
{
  /* If a type was specified as a whole, we have no modifiers and are
     done.  */
  जइ (specs->type != NULL_वृक्षः)
    {
      gcc_assert (!specs->long_p && !specs->long_long_p && !specs->short_p
		  && !specs->signed_p && !specs->unsigned_p
		  && !specs->complex_p && !specs->c23_auto_p);

      /* Set a dummy type.  */
      जइ (वृक्षः_CODE (specs->type) == ERROR_MARK)
        specs->type = integer_type_ग्रन्थिः;
      गच्छ handle_postfix_attrs;
    }

  /* If none of "void", "_Bool", "char", "int", "float" or "double"
     has been specified, treat it as "int" unless "_Complex" is
     present and there are no other specifiers.  If we just have
     "_Complex", it is equivalent to "_Complex double", but e.g.
     "_Complex short" is equivalent to "_Complex short int".  */
  जइ (specs->typespec_word == cts_none)
    {
      जइ (specs->saturating_p)
	{
	  error_at (specs->locations[cdw_saturating],
		    "%<_Sat%> is used without %<_Fract%> or %<_Accum%>");
	  जइ (!targetm.fixed_point_supported_p ())
	    error_at (specs->locations[cdw_saturating],
		      "fixed-point types not supported for this target");
	  specs->typespec_word = cts_fract;
	}
      अण्णहा जइ (specs->long_p || specs->short_p
	       || specs->signed_p || specs->unsigned_p)
	{
	  specs->typespec_word = cts_int;
	}
      अण्णहा जइ (specs->complex_p)
	{
	  specs->typespec_word = cts_double;
	  pedwarn (specs->locations[cdw_complex], OPT_Wpedantic,
		   "ISO C does not support plain %<complex%> meaning "
		   "%<double complex%>");
	}
      अण्णहा जइ (specs->c23_auto_p)
	{
	  /* Type to be filled in later, including applying postfix
	     attributes.  This warning only actually appears for
	     -Wc11-c23-compat in C23 mode; in older modes, there may
	     be a warning or pedwarn for implicit "int" instead, or
	     other errors for use of auto at file scope.  */
	  pedwarn_c11 (निवेशः_location, OPT_Wpedantic,
		       "ISO C does not support %<auto%> type deduction "
		       "before C23");
	  प्रत्यागम specs;
	}
      अण्णहा
	{
	  specs->typespec_word = cts_int;
	  specs->default_int_p = सच्च;
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
  विकल्प (specs->typespec_word)
    {
    पक्ष cts_auto_type:
      gcc_assert (!specs->long_p && !specs->short_p
		  && !specs->signed_p && !specs->unsigned_p
		  && !specs->complex_p);
      /* Type to be filled in later.  */
      जइ (specs->postfix_attrs)
	error ("%<__auto_type%> followed by %<[[]]%> attributes");
      भङ्ग;
    पक्ष cts_void:
      gcc_assert (!specs->long_p && !specs->short_p
		  && !specs->signed_p && !specs->unsigned_p
		  && !specs->complex_p);
      specs->type = void_type_ग्रन्थिः;
      भङ्ग;
    पक्ष cts_bool:
      gcc_assert (!specs->long_p && !specs->short_p
		  && !specs->signed_p && !specs->unsigned_p
		  && !specs->complex_p);
      specs->type = boolean_type_ग्रन्थिः;
      भङ्ग;
    पक्ष cts_char:
      gcc_assert (!specs->long_p && !specs->short_p);
      gcc_assert (!(specs->signed_p && specs->unsigned_p));
      जइ (specs->signed_p)
	specs->type = signed_char_type_ग्रन्थिः;
      अण्णहा जइ (specs->unsigned_p)
	specs->type = unsigned_char_type_ग्रन्थिः;
      अण्णहा
	specs->type = char_type_ग्रन्थिः;
      जइ (specs->complex_p)
	{
	  pedwarn (specs->locations[cdw_complex], OPT_Wpedantic,
		   "ISO C does not support complex integer types");
	  specs->type = build_complex_type (specs->type);
	}
      भङ्ग;
    पक्ष cts_int_n:
      gcc_assert (!specs->long_p && !specs->short_p && !specs->long_long_p);
      gcc_assert (!(specs->signed_p && specs->unsigned_p));
      जइ (! int_n_enabled_p[specs->u.int_n_idx])
	specs->type = integer_type_ग्रन्थिः;
      अण्णहा
	specs->type = (specs->unsigned_p
		       ? int_n_trees[specs->u.int_n_idx].unsigned_type
		       : int_n_trees[specs->u.int_n_idx].signed_type);
      जइ (specs->complex_p)
	{
	  pedwarn (specs->locations[cdw_complex], OPT_Wpedantic,
		   "ISO C does not support complex integer types");
	  specs->type = build_complex_type (specs->type);
	}
      भङ्ग;
    पक्ष cts_int:
      gcc_assert (!(specs->long_p && specs->short_p));
      gcc_assert (!(specs->signed_p && specs->unsigned_p));
      जइ (specs->long_long_p)
	specs->type = (specs->unsigned_p
		       ? long_long_unsigned_type_ग्रन्थिः
		       : long_long_integer_type_ग्रन्थिः);
      अण्णहा जइ (specs->long_p)
	specs->type = (specs->unsigned_p
		       ? long_unsigned_type_ग्रन्थिः
		       : long_integer_type_ग्रन्थिः);
      अण्णहा जइ (specs->short_p)
	specs->type = (specs->unsigned_p
		       ? short_unsigned_type_ग्रन्थिः
		       : short_integer_type_ग्रन्थिः);
      अण्णहा
	specs->type = (specs->unsigned_p
		       ? unsigned_type_ग्रन्थिः
		       : integer_type_ग्रन्थिः);
      जइ (specs->complex_p)
	{
	  pedwarn (specs->locations[cdw_complex], OPT_Wpedantic,
		   "ISO C does not support complex integer types");
	  specs->type = build_complex_type (specs->type);
	}
      भङ्ग;
    पक्ष cts_float:
      gcc_assert (!specs->long_p && !specs->short_p
		  && !specs->signed_p && !specs->unsigned_p);
      specs->type = (specs->complex_p
		     ? complex_float_type_ग्रन्थिः
		     : float_type_ग्रन्थिः);
      भङ्ग;
    पक्ष cts_double:
      gcc_assert (!specs->long_long_p && !specs->short_p
		  && !specs->signed_p && !specs->unsigned_p);
      जइ (specs->long_p)
	{
	  specs->type = (specs->complex_p
			 ? complex_long_double_type_ग्रन्थिः
			 : long_double_type_ग्रन्थिः);
	}
      अण्णहा
	{
	  specs->type = (specs->complex_p
			 ? complex_double_type_ग्रन्थिः
			 : double_type_ग्रन्थिः);
	}
      भङ्ग;
    पक्ष cts_floatn_nx:
      gcc_assert (!specs->long_p && !specs->short_p
		  && !specs->signed_p && !specs->unsigned_p);
      जइ (FLOATN_NX_TYPE_ग्रन्थिः (specs->u.floatn_nx_idx) == NULL_वृक्षः)
	specs->type = integer_type_ग्रन्थिः;
      अण्णहा जइ (specs->complex_p)
	specs->type = COMPLEX_FLOATN_NX_TYPE_ग्रन्थिः (specs->u.floatn_nx_idx);
      अण्णहा
	specs->type = FLOATN_NX_TYPE_ग्रन्थिः (specs->u.floatn_nx_idx);
      भङ्ग;
    पक्ष cts_dfloat32:
    पक्ष cts_dfloat64:
    पक्ष cts_dfloat128:
    पक्ष cts_dfloat64x:
      gcc_assert (!specs->long_p && !specs->long_long_p && !specs->short_p
		  && !specs->signed_p && !specs->unsigned_p && !specs->complex_p);
      जइ (!targetm.decimal_float_supported_p ())
	specs->type = integer_type_ग्रन्थिः;
      अण्णहा जइ (specs->typespec_word == cts_dfloat32)
	specs->type = dfloat32_type_ग्रन्थिः;
      अण्णहा जइ (specs->typespec_word == cts_dfloat64)
	specs->type = dfloat64_type_ग्रन्थिः;
      अण्णहा जइ (specs->typespec_word == cts_dfloat128)
	specs->type = dfloat128_type_ग्रन्थिः;
      अण्णहा
	specs->type = dfloat64x_type_ग्रन्थिः;
      भङ्ग;
    पक्ष cts_fract:
      gcc_assert (!specs->complex_p);
      जइ (!targetm.fixed_point_supported_p ())
	specs->type = integer_type_ग्रन्थिः;
      अण्णहा जइ (specs->saturating_p)
	{
	  जइ (specs->long_long_p)
	    specs->type = specs->unsigned_p
			  ? sat_unsigned_long_long_fract_type_ग्रन्थिः
			  : sat_long_long_fract_type_ग्रन्थिः;
	  अण्णहा जइ (specs->long_p)
	    specs->type = specs->unsigned_p
			  ? sat_unsigned_long_fract_type_ग्रन्थिः
			  : sat_long_fract_type_ग्रन्थिः;
	  अण्णहा जइ (specs->short_p)
	    specs->type = specs->unsigned_p
			  ? sat_unsigned_short_fract_type_ग्रन्थिः
			  : sat_short_fract_type_ग्रन्थिः;
	  अण्णहा
	    specs->type = specs->unsigned_p
			  ? sat_unsigned_fract_type_ग्रन्थिः
			  : sat_fract_type_ग्रन्थिः;
	}
      अण्णहा
	{
	  जइ (specs->long_long_p)
	    specs->type = specs->unsigned_p
			  ? unsigned_long_long_fract_type_ग्रन्थिः
			  : long_long_fract_type_ग्रन्थिः;
	  अण्णहा जइ (specs->long_p)
	    specs->type = specs->unsigned_p
			  ? unsigned_long_fract_type_ग्रन्थिः
			  : long_fract_type_ग्रन्थिः;
	  अण्णहा जइ (specs->short_p)
	    specs->type = specs->unsigned_p
			  ? unsigned_short_fract_type_ग्रन्थिः
			  : short_fract_type_ग्रन्थिः;
	  अण्णहा
	    specs->type = specs->unsigned_p
			  ? unsigned_fract_type_ग्रन्थिः
			  : fract_type_ग्रन्थिः;
	}
      भङ्ग;
    पक्ष cts_accum:
      gcc_assert (!specs->complex_p);
      जइ (!targetm.fixed_point_supported_p ())
	specs->type = integer_type_ग्रन्थिः;
      अण्णहा जइ (specs->saturating_p)
	{
	  जइ (specs->long_long_p)
	    specs->type = specs->unsigned_p
			  ? sat_unsigned_long_long_accum_type_ग्रन्थिः
			  : sat_long_long_accum_type_ग्रन्थिः;
	  अण्णहा जइ (specs->long_p)
	    specs->type = specs->unsigned_p
			  ? sat_unsigned_long_accum_type_ग्रन्थिः
			  : sat_long_accum_type_ग्रन्थिः;
	  अण्णहा जइ (specs->short_p)
	    specs->type = specs->unsigned_p
			  ? sat_unsigned_short_accum_type_ग्रन्थिः
			  : sat_short_accum_type_ग्रन्थिः;
	  अण्णहा
	    specs->type = specs->unsigned_p
			  ? sat_unsigned_accum_type_ग्रन्थिः
			  : sat_accum_type_ग्रन्थिः;
	}
      अण्णहा
	{
	  जइ (specs->long_long_p)
	    specs->type = specs->unsigned_p
			  ? unsigned_long_long_accum_type_ग्रन्थिः
			  : long_long_accum_type_ग्रन्थिः;
	  अण्णहा जइ (specs->long_p)
	    specs->type = specs->unsigned_p
			  ? unsigned_long_accum_type_ग्रन्थिः
			  : long_accum_type_ग्रन्थिः;
	  अण्णहा जइ (specs->short_p)
	    specs->type = specs->unsigned_p
			  ? unsigned_short_accum_type_ग्रन्थिः
			  : short_accum_type_ग्रन्थिः;
	  अण्णहा
	    specs->type = specs->unsigned_p
			  ? unsigned_accum_type_ग्रन्थिः
			  : accum_type_ग्रन्थिः;
	}
      भङ्ग;
    पक्ष cts_bitint:
      gcc_assert (!specs->long_p && !specs->short_p
		  && !specs->complex_p);
      जइ (!specs->unsigned_p && specs->u.bitint_prec == 1 && !flag_isoc2y)
	{
	  error_at (specs->locations[cdw_typespec],
		    "%<signed _BitInt%> argument must be at least 2 "
		    "before C2Y");
	  specs->type = integer_type_ग्रन्थिः;
	  भङ्ग;
	}
      जइ (specs->u.bitint_prec == -1)
	specs->type = integer_type_ग्रन्थिः;
      अण्णहा
	{
	  pedwarn_c11 (specs->locations[cdw_typespec], OPT_Wpedantic,
		       "ISO C does not support %<%s_BitInt(%d)%> before C23",
		       specs->unsigned_p ? "unsigned "
		       : specs->signed_p ? "signed " : "",
		       specs->u.bitint_prec);
	  specs->type = build_bitint_type (specs->u.bitint_prec,
					   specs->unsigned_p);
	}
      भङ्ग;
    स्वभाव:
      gcc_unreachable ();
    }
 handle_postfix_attrs:
  जइ (specs->type != रिक्त)
    {
      specs->postfix_attrs
	= c_warn_type_attributes (specs->type, specs->postfix_attrs);
      decl_attributes (&specs->type, specs->postfix_attrs, 0);
      specs->postfix_attrs = NULL_वृक्षः;
    }

  प्रत्यागम specs;
}

/* Perform final processing on one file scope's declarations (or the
   external scope's declarations), GLOBALS.  */

स्थिर शून्य
c_write_global_declarations_1 (वृक्षः globals)
{
  वृक्षः decl;
  तार्किक reconsider;

  /* Process the decls in the order they were written.  */
  प्रति (decl = globals; decl; decl = DECL_CHAIN (decl))
    {
      /* Check for used but undefined static functions using the C
	 standard's definition of "used", and set TREE_NO_WARNING so
	 that check_global_declaration doesn't repeat the check.  */
      जइ (वृक्षः_CODE (decl) == FUNCTION_DECL
	  && DECL_INITIAL (decl) == NULL_वृक्षः
	  && DECL_EXTERNAL (decl)
	  && !वृक्षः_PUBLIC (decl)
	  && !warning_suppressed_p (decl, OPT_Wunused))
	{
	  जइ (C_DECL_USED (decl))
	    {
	      जइ (pedwarn (निवेशः_location, 0, "%q+F used but never defined",
			   decl))
		suppress_warning (decl, OPT_Wunused);
	    }
	  /* For -Wunused-function warn about unused static prototypes.  */
	  अण्णहा जइ (warn_unused_function
		   && ! DECL_ARTIFICIAL (decl)
		   && warning (OPT_Wunused_function,
			       "%q+F declared %<static%> but never defined",
			       decl))
	    suppress_warning (decl, OPT_Wunused);
	}

      wrapup_global_declaration_1 (decl);
    }

  करेहि
    {
      reconsider = मिच्छ;
      प्रति (decl = globals; decl; decl = DECL_CHAIN (decl))
	reconsider |= wrapup_global_declaration_2 (decl);
    }
  जाव (reconsider);
}

/* Preserve the external declarations scope across a garbage collect.  */
स्थिर GTY(()) वृक्षः ext_block;

/* Collect all references relevant to SOURCE_FILE.  */

स्थिर शून्य
collect_all_refs (ध्रुव वर्ण *source_file)
{
  वृक्षः t;
  unsigned i;

  FOR_EACH_VEC_ELT (*all_translation_units, i, t)
    collect_ada_nodes (BLOCK_VARS (DECL_INITIAL (t)), source_file);

  collect_ada_nodes (BLOCK_VARS (ext_block), source_file);
}

/* Collect source file references at global level.  */

स्थिर शून्य
collect_source_refs (शून्य)
{
  वृक्षः t;
  वृक्षः decls;
  वृक्षः decl;
  unsigned i;

  FOR_EACH_VEC_ELT (*all_translation_units, i, t)
    {
      decls = DECL_INITIAL (t);
      प्रति (decl = BLOCK_VARS (decls); decl; decl = वृक्षः_CHAIN (decl))
	जइ (!DECL_IS_UNDECLARED_BUILTIN (decl))
	  collect_source_ref (DECL_SOURCE_FILE (decl));
    }

  प्रति (decl = BLOCK_VARS (ext_block); decl; decl = वृक्षः_CHAIN (decl))
    जइ (!DECL_IS_UNDECLARED_BUILTIN (decl))
      collect_source_ref (DECL_SOURCE_FILE (decl));
}

/* Free attribute access data that are not needed by the middle end. */

स्थिर शून्य
free_attr_access_data ()
{
  संरचना cgraph_ग्रन्थिः *n;

  /* Iterate over all functions declared in the translation unit.  */
  FOR_EACH_FUNCTION (n)
    {
      प्रति (वृक्षः parm = DECL_ARGUMENTS (n->decl); parm; parm = वृक्षः_CHAIN (parm))
	जइ (वृक्षः attrs = DECL_ATTRIBUTES (parm))
	  attr_access::free_lang_data (attrs);

      वृक्षः fntype = वृक्षः_TYPE (n->decl);
      जइ (!fntype || fntype == error_mark_ग्रन्थिः)
	अनुवर्त;
      वृक्षः attrs = TYPE_ATTRIBUTES (fntype);
      जइ (!attrs)
	अनुवर्त;

      attr_access::free_lang_data (attrs);
    }
}

/* Perform any final parser cleanups and generate initial debugging
   information.  */

शून्य
c_parse_final_cleanups (शून्य)
{
  वृक्षः t;
  unsigned i;

  /* We don't want to do this if generating a PCH.  */
  जइ (pch_file)
    प्रत्यागम;

  timevar_stop (TV_PHASE_PARSING);
  timevar_start (TV_PHASE_DEFERRED);

  /* Do the Objective-C stuff.  This is where all the Objective-C
     module stuff gets generated (symtab, class/protocol/selector
     lists etc).  */
  जइ (c_dialect_objc ())
    objc_write_global_declarations ();

  /* Close the external scope.  */
  ext_block = निष्कासय_scope ();
  external_scope = 0;
  gcc_assert (!current_scope);

  /* Handle -fdump-ada-spec[-slim]. */
  जइ (flag_dump_ada_spec || flag_dump_ada_spec_slim)
    {
      /* Build a table of files to generate specs for */
      collect_source_ref (main_निवेशः_filename);
      जइ (!flag_dump_ada_spec_slim)
	collect_source_refs ();

      dump_ada_specs (collect_all_refs, रिक्त);
    }

  /* Process all file scopes in this compilation, and the external_scope,
     through wrapup_global_declarations.  */
  FOR_EACH_VEC_ELT (*all_translation_units, i, t)
    c_write_global_declarations_1 (BLOCK_VARS (DECL_INITIAL (t)));
  c_write_global_declarations_1 (BLOCK_VARS (ext_block));

  /* Call this to set cpp_implicit_aliases_done on all nodes.  This is
     important for function multiversioning aliases to get resolved.  */
  symtab->process_same_body_aliases ();

  जइ (!in_lto_p)
    free_attr_access_data ();

  timevar_stop (TV_PHASE_DEFERRED);
  timevar_start (TV_PHASE_PARSING);

  ext_block = रिक्त;
}

/* Register reserved keyword WORD as qualifier for address space AS.  */

शून्य
c_register_addr_space (ध्रुव वर्ण *word, addr_space_t as)
{
  पूर्णाङ्क rid = RID_FIRST_ADDR_SPACE + as;
  वृक्षः id;

  /* Address space qualifiers are only supported
     in C with GNU extensions enabled.  */
  जइ (c_dialect_objc () || flag_no_asm)
    प्रत्यागम;

  id = get_identifier (word);
  C_SET_RID_CODE (id, rid);
  C_IS_RESERVED_WORD (id) = 1;
  ridpointers [rid] = id;
}

/* Return identifier to look up for omp declare reduction.  */

वृक्षः
c_omp_reduction_id (गणना वृक्षः_code reduction_code, वृक्षः reduction_id)
{
  ध्रुव वर्ण *p = रिक्त;
  विकल्प (reduction_code)
    {
    पक्ष PLUS_व्यञ्जकम्: p = "+"; भङ्ग;
    पक्ष MULT_व्यञ्जकम्: p = "*"; भङ्ग;
    पक्ष MINUS_व्यञ्जकम्: p = "-"; भङ्ग;
    पक्ष BIT_AND_व्यञ्जकम्: p = "&"; भङ्ग;
    पक्ष BIT_XOR_व्यञ्जकम्: p = "^"; भङ्ग;
    पक्ष BIT_IOR_व्यञ्जकम्: p = "|"; भङ्ग;
    पक्ष TRUTH_ANDIF_व्यञ्जकम्: p = "&&"; भङ्ग;
    पक्ष TRUTH_ORIF_व्यञ्जकम्: p = "||"; भङ्ग;
    पक्ष MIN_व्यञ्जकम्: p = "min"; भङ्ग;
    पक्ष MAX_व्यञ्जकम्: p = "max"; भङ्ग;
    स्वभाव:
      भङ्ग;
    }

  जइ (p == रिक्त)
    {
      जइ (वृक्षः_CODE (reduction_id) != IDENTIFIER_ग्रन्थिः)
	प्रत्यागम error_mark_ग्रन्थिः;
      p = IDENTIFIER_POINTER (reduction_id);
    }

  ध्रुव वर्ण prefix[] = "omp declare reduction ";
  size_t lenp = परिमाण (prefix);
  size_t len = strlen (p);
  वर्ण *name = XALLOCAVEC (वर्ण, lenp + len);
  memcpy (name, prefix, lenp - 1);
  memcpy (name + lenp - 1, p, len + 1);
  प्रत्यागम get_identifier (name);
}

/* Lookup REDUCTION_ID in the current scope, or create an artificial
   VAR_DECL, bind it into the current scope and return it.  */

वृक्षः
c_omp_reduction_decl (वृक्षः reduction_id)
{
  संरचना c_binding *b = I_चिह्नम्_BINDING (reduction_id);
  जइ (b != रिक्त && B_IN_CURRENT_SCOPE (b))
    प्रत्यागम b->decl;

  वृक्षः decl = build_decl (BUILTINS_LOCATION, VAR_DECL,
			  reduction_id, integer_type_ग्रन्थिः);
  DECL_ARTIFICIAL (decl) = 1;
  DECL_EXTERNAL (decl) = 1;
  वृक्षः_STATIC (decl) = 1;
  वृक्षः_PUBLIC (decl) = 0;
  bind (reduction_id, decl, current_scope, सच्च, मिच्छ, BUILTINS_LOCATION);
  प्रत्यागम decl;
}

/* Lookup REDUCTION_ID in the first scope where it has entry for TYPE.  */

वृक्षः
c_omp_reduction_lookup (वृक्षः reduction_id, वृक्षः type)
{
  संरचना c_binding *b = I_चिह्नम्_BINDING (reduction_id);
  जाव (b)
    {
      वृक्षः t;
      प्रति (t = DECL_INITIAL (b->decl); t; t = वृक्षः_CHAIN (t))
	जइ (comptypes (वृक्षः_PURPOSE (t), type))
	  प्रत्यागम वृक्षः_मानम् (t);
      b = b->shadowed;
    }
  प्रत्यागम error_mark_ग्रन्थिः;
}

/* Helper function called via walk_tree, to diagnose invalid
   #pragma omp declare reduction combiners or initializers.  */

वृक्षः
c_check_omp_declare_reduction_r (वृक्षः *tp, पूर्णाङ्क *, शून्य *data)
{
  वृक्षः *vars = (वृक्षः *) data;
  जइ (SSA_VAR_P (*tp)
      && !DECL_ARTIFICIAL (*tp)
      && *tp != vars[0]
      && *tp != vars[1])
    {
      location_t loc = DECL_SOURCE_LOCATION (vars[0]);
      जइ (strcmp (IDENTIFIER_POINTER (DECL_NAME (vars[0])), "omp_out") == 0)
	error_at (loc, "%<#pragma omp declare reduction%> combiner refers to "
		       "variable %qD which is not %<omp_out%> nor %<omp_in%>",
		  *tp);
      अण्णहा
	error_at (loc, "%<#pragma omp declare reduction%> initializer refers "
		       "to variable %qD which is not %<omp_priv%> nor "
		       "%<omp_orig%>",
		  *tp);
      प्रत्यागम *tp;
    }
  प्रत्यागम NULL_वृक्षः;
}

/* Return identifier to look up for omp declare mapper.  */

वृक्षः
c_omp_mapper_id (वृक्षः mapper_id)
{
  ध्रुव वर्ण *p = रिक्त;

  ध्रुव वर्ण prefix[] = "omp declare mapper ";

  जइ (mapper_id == NULL_वृक्षः)
    p = "<default>";
  अण्णहा जइ (वृक्षः_CODE (mapper_id) == IDENTIFIER_ग्रन्थिः)
    p = IDENTIFIER_POINTER (mapper_id);
  अण्णहा
    प्रत्यागम error_mark_ग्रन्थिः;

  size_t lenp = परिमाण (prefix);
  size_t len = strlen (p);
  वर्ण *name = XALLOCAVEC (वर्ण, lenp + len);
  memcpy (name, prefix, lenp - 1);
  memcpy (name + lenp - 1, p, len + 1);
  प्रत्यागम get_identifier (name);
}

/* Lookup MAPPER_ID in the current scope, or create an artificial
   VAR_DECL, bind it into the current scope and return it.  */

वृक्षः
c_omp_mapper_decl (वृक्षः mapper_id)
{
  संरचना c_binding *b = I_चिह्नम्_BINDING (mapper_id);
  जइ (b != रिक्त && B_IN_CURRENT_SCOPE (b))
    प्रत्यागम b->decl;

  वृक्षः decl = build_decl (BUILTINS_LOCATION, VAR_DECL,
			  mapper_id, integer_type_ग्रन्थिः);
  DECL_ARTIFICIAL (decl) = 1;
  DECL_EXTERNAL (decl) = 1;
  वृक्षः_STATIC (decl) = 1;
  वृक्षः_PUBLIC (decl) = 0;
  bind (mapper_id, decl, current_scope, सच्च, मिच्छ, BUILTINS_LOCATION);
  प्रत्यागम decl;
}

/* Lookup MAPPER_ID in the first scope where it has entry for TYPE.  */

वृक्षः
c_omp_mapper_lookup (वृक्षः mapper_id, वृक्षः type)
{
  जइ (!RECORD_OR_UNION_TYPE_P (type))
    प्रत्यागम NULL_वृक्षः;

  mapper_id = c_omp_mapper_id (mapper_id);

  संरचना c_binding *b = I_चिह्नम्_BINDING (mapper_id);
  जाव (b)
    {
      वृक्षः t;
      प्रति (t = DECL_INITIAL (b->decl); t; t = वृक्षः_CHAIN (t))
	जइ (comptypes (वृक्षः_PURPOSE (t), type))
	  प्रत्यागम वृक्षः_मानम् (t);
      b = b->shadowed;
    }
  प्रत्यागम NULL_वृक्षः;
}

/* For C, we record a pointer to the mapper itself without wrapping it in an
   artificial function or similar.  So, just return it.  */

वृक्षः
c_omp_extract_mapper_directive (वृक्षः mapper)
{
  प्रत्यागम mapper;
}

/* For now we can handle singleton OMP_ARRAY_SECTIONs with custom mappers, but
   nothing more complicated.  */

वृक्षः
c_omp_map_array_section (location_t loc, वृक्षः t)
{
  वृक्षः नीचः = वृक्षः_OPERAND (t, 1);
  वृक्षः len = वृक्षः_OPERAND (t, 2);

  जइ (len && integer_onep (len))
    {
      t = वृक्षः_OPERAND (t, 0);

      जइ (!नीचः)
	नीचः = integer_zero_ग्रन्थिः;

      t = build_array_ref (loc, t, नीचः);
    }

  प्रत्यागम t;
}

/* Helper function for below function.  */

स्थिर वृक्षः
c_omp_scan_mapper_bindings_r (वृक्षः *tp, पूर्णाङ्क *walk_subtrees, शून्य *ptr)
{
  वृक्षः t = *tp;
  omp_mapper_list<वृक्षः> *mlist = (omp_mapper_list<वृक्षः> *) ptr;
  वृक्षः aggr_type = NULL_वृक्षः;

  जइ (वृक्षः_CODE (t) == SIZEOF_व्यञ्जकम्
      || वृक्षः_CODE (t) == ALIGNOF_व्यञ्जकम्)
    {
      *walk_subtrees = 0;
      प्रत्यागम NULL_वृक्षः;
    }

  जइ (वृक्षः_CODE (t) == OMP_CLAUSE)
    प्रत्यागम NULL_वृक्षः;

  जइ (वृक्षः_CODE (t) == COMPONENT_REF
      && RECORD_OR_UNION_TYPE_P (वृक्षः_TYPE (वृक्षः_OPERAND (t, 0))))
    aggr_type = वृक्षः_TYPE (वृक्षः_OPERAND (t, 0));
  अण्णहा जइ ((वृक्षः_CODE (t) == VAR_DECL
	    || वृक्षः_CODE (t) == PARM_DECL
	    || वृक्षः_CODE (t) == RESULT_DECL)
	   && RECORD_OR_UNION_TYPE_P (वृक्षः_TYPE (t)))
    aggr_type = वृक्षः_TYPE (t);

  जइ (aggr_type)
    {
      वृक्षः mapper_fn = c_omp_mapper_lookup (NULL_वृक्षः, aggr_type);
      जइ (mapper_fn)
	mlist->add_mapper (NULL_वृक्षः, aggr_type, mapper_fn);
    }

  प्रत्यागम NULL_वृक्षः;
}

/* Scan an offload region's body, and record uses of struct- or union-typed
   variables.  Add _mapper_binding_ fake clauses to *CLAUSES_PTR.  */

शून्य
c_omp_scan_mapper_bindings (location_t loc, वृक्षः *clauses_ptr, वृक्षः body)
{
  hash_set<omp_name_type<वृक्षः>> seen_types;
  auto_vec<वृक्षः> mappers;
  omp_mapper_list<वृक्षः> mlist (&seen_types, &mappers);

  walk_वृक्षः_without_duplicates (&body, c_omp_scan_mapper_bindings_r, &mlist);

  unsigned पूर्णाङ्क i;
  वृक्षः mapper;
  FOR_EACH_VEC_ELT (mappers, i, mapper)
    c_omp_find_nested_mappers (&mlist, mapper);

  FOR_EACH_VEC_ELT (mappers, i, mapper)
    {
      जइ (mapper == error_mark_ग्रन्थिः)
	अनुवर्त;
      वृक्षः mapper_name = OMP_DECLARE_MAPPER_ID (mapper);
      वृक्षः decl = OMP_DECLARE_MAPPER_DECL (mapper);

      वृक्षः c = build_omp_clause (loc, OMP_CLAUSE__MAPPER_BINDING_);
      OMP_CLAUSE__MAPPER_BINDING__ID (c) = mapper_name;
      OMP_CLAUSE__MAPPER_BINDING__DECL (c) = decl;
      OMP_CLAUSE__MAPPER_BINDING__MAPPER (c) = mapper;

      OMP_CLAUSE_CHAIN (c) = *clauses_ptr;
      *clauses_ptr = c;
    }
}

तार्किक
c_check_in_current_scope (वृक्षः decl)
{
  संरचना c_binding *b = I_चिह्नम्_BINDING (DECL_NAME (decl));
  प्रत्यागम b != रिक्त && B_IN_CURRENT_SCOPE (b);
}

/* Search for loop or switch names.  BEFORE_LABELS is last statement before
   possible labels and SWITCH_P true for a switch, false for loops.
   Searches through last statements in cur_stmt_list, stops when seeing
   BEFORE_LABELs, or statement other than LABEL_EXPR or CASE_LABEL_EXPR.
   Returns number of loop/switch names found and if any are found, sets
   *LAST_P to the canonical loop/switch name LABEL_DECL.  */

पूर्णाङ्क
c_get_loop_names (वृक्षः before_labels, तार्किक switch_p, वृक्षः *last_p)
{
  *last_p = NULL_वृक्षः;
  जइ (!building_stmt_list_p ()
      || !STATEMENT_LIST_HAS_LABEL (cur_stmt_list)
      || before_labels == void_list_ग्रन्थिः)
    प्रत्यागम 0;

  पूर्णाङ्क ret = 0;
  वृक्षः last = NULL_वृक्षः;
  प्रति (वृक्षः_stmt_iterator tsi = tsi_last (cur_stmt_list);
       !tsi_end_p (tsi); tsi_prev (&tsi))
    {
      वृक्षः stmt = tsi_stmt (tsi);
      जइ (stmt == before_labels)
	भङ्ग;
      अण्णहा जइ (वृक्षः_CODE (stmt) == LABEL_व्यञ्जकम्)
	{
	  जइ (last == NULL_वृक्षः)
	    last = LABEL_व्यञ्जकम्_LABEL (stmt);
	  अण्णहा
	    {
	      loop_names.safe_प्रक्षिप (LABEL_व्यञ्जकम्_LABEL (stmt));
	      ++ret;
	    }
	}
      अण्णहा जइ (वृक्षः_CODE (stmt) != CASE_LABEL_व्यञ्जकम्
	       && वृक्षः_CODE (stmt) != DEBUG_BEGIN_STMT)
	भङ्ग;
    }
  जइ (last)
    {
      जइ (switch_p)
	C_DECL_SWITCH_NAME (last) = 1;
      अण्णहा
	C_DECL_LOOP_NAME (last) = 1;
      loop_names.safe_प्रक्षिप (last);
      ++ret;
      जइ (loop_names.length () > 16)
	{
	  unsigned पूर्णाङ्क first = 0, i;
	  वृक्षः l, c = NULL_वृक्षः;
	  जइ (loop_names_hash == रिक्त)
	    loop_names_hash = नूतन decl_वृक्षः_map (ret);
	  अण्णहा
	    first = loop_names.length () - ret;
	  FOR_EACH_VEC_ELT_REVERSE (loop_names, i, l)
	    {
	      जइ (C_DECL_LOOP_NAME (l) || C_DECL_SWITCH_NAME (l))
		c = l;
	      gcc_checking_assert (c);
	      loop_names_hash->put (l, c);
	      जइ (i == first)
		भङ्ग;
	    }
	}
      *last_p = last;
    }
  प्रत्यागम ret;
}

/* Undoes what get_loop_names did when it returned NUM_NAMES.  */

शून्य
c_release_loop_names (पूर्णाङ्क अङ्कः_names)
{
  unsigned len = loop_names.length () - अङ्कः_names;
  जइ (loop_names_hash)
    {
      जइ (len <= 16)
	{
	  delete loop_names_hash;
	  loop_names_hash = रिक्त;
	}
      अण्णहा
	{
	  unsigned पूर्णाङ्क i;
	  वृक्षः l;
	  FOR_EACH_VEC_ELT_REVERSE (loop_names, i, l)
	    {
	      loop_names_hash->remove (l);
	      जइ (i == len)
		भङ्ग;
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

वृक्षः
c_finish_bc_name (location_t loc, वृक्षः name, तार्किक is_break)
{
  वृक्षः label = NULL_वृक्षः, lab;
  pedwarn_c23 (loc, OPT_Wpedantic,
	       "ISO C does not support %qs statement with an identifier "
	       "operand before C2Y", is_break ? "break" : "continue");

  /* If I_LABEL_DECL is NULL or not from current function, don't waste time
     trying to find it among loop_names, it can't be there.  */
  जइ (!loop_names.is_empty ()
      && current_function_scope
      && (lab = I_LABEL_DECL (name))
      && DECL_CONTEXT (lab) == current_function_decl)
    {
      unsigned पूर्णाङ्क i;
      वृक्षः l, c = NULL_वृक्षः;
      जइ (loop_names_hash)
	{
	  जइ (वृक्षः *val = loop_names_hash->get (lab))
	    label = *val;
	}
      अण्णहा
	FOR_EACH_VEC_ELT_REVERSE (loop_names, i, l)
	  {
	    जइ (C_DECL_LOOP_NAME (l) || C_DECL_SWITCH_NAME (l))
	      c = l;
	    gcc_checking_assert (c);
	    जइ (l == lab)
	      {
		label = c;
		भङ्ग;
	      }
	  }
      जइ (label)
	वृक्षः_USED (lab) = 1;
    }
  जइ (label == NULL_वृक्षः)
    {
      auto_vec<ध्रुव वर्ण *> candidates;
      unsigned पूर्णाङ्क i;
      वृक्षः l, c = NULL_वृक्षः;
      FOR_EACH_VEC_ELT_REVERSE (loop_names, i, l)
	{
	  जइ (C_DECL_LOOP_NAME (l) || C_DECL_SWITCH_NAME (l))
	    c = l;
	  gcc_checking_assert (c);
	  जइ (is_break || C_DECL_LOOP_NAME (c))
	    candidates.safe_प्रक्षिप (IDENTIFIER_POINTER (DECL_NAME (l)));
	}
      ध्रुव वर्ण *hint = find_closest_string (IDENTIFIER_POINTER (name),
					      &candidates);
      जइ (hint)
	{
	  gcc_rich_location richloc (loc);
	  richloc.add_fixit_replace (hint);
	  जइ (is_break)
	    error_at (&richloc, "%<break%> statement operand %qE does not "
				"refer to a named loop or %<switch%>; "
				"did you mean %qs?", name, hint);
	  अण्णहा
	    error_at (&richloc, "%<continue%> statement operand %qE does not "
				"refer to a named loop; did you mean %qs?",
		      name, hint);
	}
      अण्णहा जइ (is_break)
	error_at (loc, "%<break%> statement operand %qE does not refer to a "
		       "named loop or %<switch%>", name);
      अण्णहा
	error_at (loc, "%<continue%> statement operand %qE does not refer to "
		       "a named loop", name);
    }
  अण्णहा जइ (!C_DECL_LOOP_NAME (label) && !is_break)
    {
      auto_diagnostic_group d;
      error_at (loc, "%<continue%> statement operand %qE refers to a named "
		     "%<switch%>", name);
      inform (DECL_SOURCE_LOCATION (label), "%<switch%> name defined here");
      label = NULL_वृक्षः;
    }
  अण्णहा जइ (!C_DECL_LOOP_SWITCH_NAME_VALID (label))
    {
      auto_diagnostic_group d;
      जइ (C_DECL_LOOP_NAME (label))
	{
	  error_at (loc, "%qs statement operand %qE refers to a loop outside "
			 "of its body", is_break ? "break" : "continue", name);
	  inform (DECL_SOURCE_LOCATION (label), "loop name defined here");
	}
      अण्णहा
	{
	  error_at (loc, "%<break%> statement operand %qE refers to a "
			 "%<switch%> outside of its body", name);
	  inform (DECL_SOURCE_LOCATION (label),
		  "%<switch%> name defined here");
	}
      label = NULL_वृक्षः;
    }
  अण्णहा जइ (label == loop_names.last () && (in_statement & IN_NAMED_STMT) != 0)
    /* If it is just a fancy reference to the innermost construct, handle it
       just like break; or continue; though tracking cheaply what is the
       innermost loop for continue when nested in switches would require
       another global variable and updating it.  */
    label = NULL_वृक्षः;
  अण्णहा
    C_DECL_LOOP_SWITCH_NAME_USED (label) = 1;
  प्रत्यागम label;
}

#अन्तर्भाव "gt-c-c-decl.h"
