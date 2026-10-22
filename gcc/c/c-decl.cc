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

#شامل "config.h"
#تعریف_کرو INCLUDE_STRING
#شامل "system.h"
#شامل "coretypes.h"
#شامل "target.h"
#شامل "function.h"
#شامل "c-tree.h"
#شامل "timevar.h"
#شامل "stringpool.h"
#شامل "cgraph.h"
#شامل "intl.h"
#شامل "print-tree.h"
#شامل "stor-layout.h"
#شامل "varasm.h"
#شامل "attribs.h"
#شامل "toplev.h"
#شامل "debug.h"
#شامل "c-family/c-objc.h"
#شامل "c-family/c-pragma.h"
#شامل "c-family/c-ubsan.h"
#شامل "c-lang.h"
#شامل "langhooks.h"
#شامل "tree-iterator.h"
#شامل "dumpfile.h"
#شامل "plugin.h"
#شامل "c-family/c-ada-spec.h"
#شامل "builtins.h"
#شامل "spellcheck-tree.h"
#شامل "gcc-rich-location.h"
#شامل "asan.h"
#شامل "c-family/name-hint.h"
#شامل "c-family/known-headers.h"
#شامل "c-family/c-spellcheck.h"
#شامل "context.h"  /* For 'g'.  */
#شامل "omp-general.h"
#شامل "omp-offload.h"  /* For offload_vars.  */
#شامل "c-parser.h"
#شامل "gcc-urlifier.h"

#شامل "tree-pretty-print.h"

/* In grokdeclarator, distinguish syntactic contexts of declarators.  */
شمار decl_context
{ معمول,			/* Ordinary declaration */
  FUNCDEF,			/* Function definition */
  PARM,				/* Declaration of parm before function body */
  میدان,			/* Declaration inside struct or union */
  TYPENAME,			/* Typename (inside cast or sizeof)  */
  GENERIC_ASSOC };		/* Typename in generic association  */

/* States indicating how grokdeclarator() should handle declspecs marked
   with __attribute__((deprecated)) or __attribute__((unavailable)).
   An object declared as __attribute__((unavailable)) should suppress
   any reports of being declared  with unavailable or deprecated items.
   An object declared as __attribute__((deprecated)) should suppress
   warnings of uses of other deprecated items.  */

شمار deprecated_حالتیں {
  DEPRECATED_معمول,
  DEPRECATED_SUPPRESS,
  UNAVAILABLE_DEPRECATED_SUPPRESS
};


/* Nonzero if we have seen an invalid cross reference
   to a struct, union, or enum, but not yet printed the message.  */
درخت pending_invalid_xref;

/* File and line to appear in the eventual error message.  */
location_t pending_invalid_xref_location;

/* The file and line that the prototype came from if this is an
   old-style definition; used for diagnostics in
   store_parm_decls_oldstyle.  */

ساکن location_t current_function_prototype_locus;

/* Whether this prototype was built-in.  */

ساکن منطقی current_function_prototype_built_اندر;

/* The argument type information of this prototype.  */

ساکن درخت current_function_prototype_arg_types;

/* The argument information structure for the function currently being
   defined.  */

ساکن ساخت c_arg_info *current_function_arg_info;

/* The obstack on which parser and related data structures, which are
   not live beyond their top-level declaration or definition, are
   allocated.  */
ساخت obstack parser_obstack;

/* The current statement tree.  */

ساکن GTY(()) ساخت stmt_درخت_s c_stmt_درخت;

/* Zero if we are not in an iteration or switch statement, otherwise
   a bitmask.  See bitmask definitions in c-tree.h.  */
غیرعلامتی حرف اندر_statement;

/* A list of decls to be made automatically visible in each file scope.  */
ساکن GTY(()) درخت visible_builtins;

/* Set to 0 at beginning of a function definition, set to 1 if
   a return statement that specifies a return value is seen.  */

صحیح current_function_returns_قدر;

/* Set to 0 at beginning of a function definition, set to 1 if
   a return statement with no argument is seen.  */

صحیح current_function_returns_null;

/* Set to 0 at beginning of a function definition, set to 1 if
   a call to a noreturn function is seen.  */

صحیح current_function_returns_abnormally;

/* Set to nonzero by `grokdeclarator' for a function
   whose return type is defaulted, if warnings for this are desired.  */

ساکن صحیح warn_about_return_type;

/* Nonzero when the current toplevel function contains a declaration
   of a nested function which is never defined.  */

ساکن منطقی undef_nested_function;

/* Vector of implicit "omp declare target" attributes to be added into
   the attribute lists.  */
vec<c_omp_declare_ہدف_attr, va_gc> *current_omp_declare_ہدف_attribute;

/* Vector of
   #pragma omp begin assumes ... #pragma omp end assumes regions
   we are in.  */
vec<c_omp_begin_assumes_ڈیٹا, va_gc> *current_omp_begin_assumes;

/* Vector of "omp begin/end declare variant" blocks we are in.  */
vec<c_omp_declare_variant_attr, va_gc> *current_omp_declare_variant_attribute;

/* Vector of loop names with C_DECL_LOOP_NAME or C_DECL_SWITCH_NAME marked
   LABEL_DECL as the last and canonical for each loop or switch.  */
ساکن vec<درخت> loop_نام;

/* Hash table mapping LABEL_DECLs to the canonical LABEL_DECLs if LOOP_NAMES
   vector becomes too long.  */
ساکن decl_درخت_map *loop_نام_hash;

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

ساخت GTY((chain_اگلا ("%h.prev"))) c_binding {
  اتحاد GTY(()) {		/* first so GTY desc can use decl */
    درخت GTY((لیبل ("0"))) type; /* the type in this scope */
    ساخت c_label_vars * GTY((لیبل ("1"))) label; /* for warnings */
  } GTY((desc ("TREE_CODE (%0.decl) == LABEL_DECL"))) u;
  درخت decl;			/* the decl bound */
  درخت id;			/* the identifier it's bound to */
  ساخت c_binding *پچھلا;	/* the previous decl in this scope */
  ساخت c_binding *shadowed;	/* the innermost decl shadowed by this one */
  غیرعلامتی صحیح گہرائی : 28;      /* depth of this scope */
  منطقی invisible : 1;  /* normal lookup should ignore this binding */
  منطقی nested : 1;     /* do not set DECL_CONTEXT when popping */
  منطقی inner_comp : 1; /* incomplete array completed in inner scope */
  منطقی اندر_struct : 1;	/* currently defined as struct field */
  location_t locus;		/* location for nested bindings */
};
#تعریف_کرو B_اندر_SCOPE(b1, b2) ((b1)->گہرائی == (b2)->گہرائی)
#تعریف_کرو B_اندر_CURRENT_SCOPE(b) ((b)->گہرائی == current_scope->گہرائی)
#تعریف_کرو B_اندر_FILE_SCOPE(b) ((b)->گہرائی == 1 /*file_scope->depth*/)
#تعریف_کرو B_اندر_EXTERNAL_SCOPE(b) ((b)->گہرائی == 0 /*external_scope->depth*/)

/* Each C symbol points to three linked lists of c_binding structures.
   These describe the values of the identifier in the three different
   namespaces defined by the language.  */

ساخت GTY(()) lang_identifier {
  ساخت c_common_identifier common_id;
  ساخت c_binding *علامت_binding; /* vars, funcs, constants, typedefs */
  ساخت c_binding *لیبل_binding;    /* struct/union/enum tags */
  ساخت c_binding *label_binding;  /* labels */
};

/* Validate c-lang.cc's assumptions.  */
خارجی حرف C_SIZEOF_STRUCT_LANG_IDENTIFIER_isnt_accurate
[(حجم(ساخت lang_identifier) == C_SIZEOF_STRUCT_LANG_IDENTIFIER) ? 1 : -1];

/* The binding oracle; see c-tree.h.  */
خالی (*c_binding_oracle) (شمار c_oracle_request, درخت identifier);

/* This flag is set on an identifier if we have previously asked the
   binding oracle for this identifier's symbol binding.  */
#تعریف_کرو I_علامت_CHECKED(گرہ) \
  (درخت_LANG_FLAG_4 (IDENTIFIER_گرہ_CHECK (گرہ)))

ساکن اندرونی ساخت c_binding* *
i_علامت_binding (درخت گرہ)
{
  ساخت lang_identifier *lid
    = (ساخت lang_identifier *) IDENTIFIER_گرہ_CHECK (گرہ);

  اگر (lid->علامت_binding == تہی
      && c_binding_oracle != تہی
      && !I_علامت_CHECKED (گرہ))
    {
      /* Set the "checked" flag first, to avoid infinite recursion
	 when the binding oracle calls back into gcc.  */
      I_علامت_CHECKED (گرہ) = 1;
      c_binding_oracle (C_ORACLE_علامت, گرہ);
    }

  واپس &lid->علامت_binding;
}

#تعریف_کرو I_علامت_BINDING(گرہ) (*i_علامت_binding (گرہ))

#تعریف_کرو I_علامت_DECL(گرہ) \
 (I_علامت_BINDING(گرہ) ? I_علامت_BINDING(گرہ)->decl : 0)

/* This flag is set on an identifier if we have previously asked the
   binding oracle for this identifier's tag binding.  */
#تعریف_کرو I_لیبل_CHECKED(گرہ) \
  (درخت_LANG_FLAG_5 (IDENTIFIER_گرہ_CHECK (گرہ)))

ساکن اندرونی ساخت c_binding **
i_لیبل_binding (درخت گرہ)
{
  ساخت lang_identifier *lid
    = (ساخت lang_identifier *) IDENTIFIER_گرہ_CHECK (گرہ);

  اگر (lid->لیبل_binding == تہی
      && c_binding_oracle != تہی
      && !I_لیبل_CHECKED (گرہ))
    {
      /* Set the "checked" flag first, to avoid infinite recursion
	 when the binding oracle calls back into gcc.  */
      I_لیبل_CHECKED (گرہ) = 1;
      c_binding_oracle (C_ORACLE_لیبل, گرہ);
    }

  واپس &lid->لیبل_binding;
}

#تعریف_کرو I_لیبل_BINDING(گرہ) (*i_لیبل_binding (گرہ))

#تعریف_کرو I_لیبل_DECL(گرہ) \
 (I_لیبل_BINDING(گرہ) ? I_لیبل_BINDING(گرہ)->decl : 0)

/* This flag is set on an identifier if we have previously asked the
   binding oracle for this identifier's label binding.  */
#تعریف_کرو I_LABEL_CHECKED(گرہ) \
  (درخت_LANG_FLAG_6 (IDENTIFIER_گرہ_CHECK (گرہ)))

ساکن اندرونی ساخت c_binding **
i_label_binding (درخت گرہ)
{
  ساخت lang_identifier *lid
    = (ساخت lang_identifier *) IDENTIFIER_گرہ_CHECK (گرہ);

  اگر (lid->label_binding == تہی
      && c_binding_oracle != تہی
      && !I_LABEL_CHECKED (گرہ))
    {
      /* Set the "checked" flag first, to avoid infinite recursion
	 when the binding oracle calls back into gcc.  */
      I_LABEL_CHECKED (گرہ) = 1;
      c_binding_oracle (C_ORACLE_LABEL, گرہ);
    }

  واپس &lid->label_binding;
}

#تعریف_کرو I_LABEL_BINDING(گرہ) (*i_label_binding (گرہ))

#تعریف_کرو I_LABEL_DECL(گرہ) \
 (I_LABEL_BINDING(گرہ) ? I_LABEL_BINDING(گرہ)->decl : 0)

/* Used by C_TOKEN_VEC tree.  */
ساخت GTY (()) c_درخت_token_vec {
  ساخت درخت_بنیاد بنیاد;
  vec<c_token, va_gc> *علامات;
};

STATIC_ASSERT (حجم (c_درخت_token_vec) == حجم (c_درخت_token_vec_struct));
STATIC_ASSERT (offsetof (c_درخت_token_vec, علامات)
	       == offsetof (c_درخت_token_vec_struct, علامات));

/* The resulting tree type.  */

اتحاد GTY((desc ("TREE_CODE (&%h.generic) == IDENTIFIER_NODE + 2 * (TREE_CODE (&%h.generic) == C_TOKEN_VEC)"),
       chain_اگلا ("(union lang_tree_node *) c_tree_chain_next (&%h.generic)"))) lang_درخت_گرہ
 {
  اتحاد درخت_گرہ GTY ((لیبل ("0"),
			desc ("tree_node_structure (&%h)")))
    generic;
  ساخت lang_identifier GTY ((لیبل ("1"))) identifier;
  ساخت c_درخت_token_vec GTY ((لیبل ("2"))) c_token_vec;
};

/* Langhook for tree_size.  */
سائز_t
c_درخت_سائز (شمار درخت_رمز_2 رمز)
{
  gcc_checking_assert (رمز >= عدد_درخت_CODES);
  انتخاب (رمز)
    {
    حالت C_TOKEN_VEC: واپس حجم (c_درخت_token_vec);
    طےشدہ:
      انتخاب (درخت_رمز_CLASS (رمز))
	{
	حالت tcc_declaration: واپس حجم (درخت_decl_non_common);
	حالت tcc_type: واپس حجم (درخت_type_non_common);
	طےشدہ: gcc_unreachable ();
	}
    }
}

/* Track bindings and other things that matter for goto warnings.  For
   efficiency, we do not gather all the decls at the point of
   definition.  Instead, we point into the bindings structure.  As
   scopes are popped, we update these structures and gather the decls
   that matter at that time.  */

ساخت GTY(()) c_spot_bindings {
  /* The currently open scope which holds bindings defined when the
     label was defined or the goto statement was found.  */
  ساخت c_scope *scope;
  /* The bindings in the scope field which were defined at the point
     of the label or goto.  This lets us look at older or newer
     bindings in the scope, as appropriate.  */
  ساخت c_binding *bindings_اندر_scope;
  /* The number of statement expressions that have started since this
     label or goto statement was defined.  This is zero if we are at
     the same statement expression level.  It is positive if we are in
     a statement expression started since this spot.  It is negative
     if this spot was in a statement expression and we have left
     it.  */
  صحیح stmt_exprs;
  /* Whether we started in a statement expression but are no longer in
     it.  This is set to true if stmt_exprs ever goes negative.  */
  منطقی بایاں_stmt_اظہاریہ;
};

/* This structure is used to keep track of bindings seen when a goto
   statement is defined.  This is only used if we see the goto
   statement before we see the label.  */

ساخت GTY(()) c_goto_bindings {
  /* The location of the goto statement.  */
  location_t loc;
  /* The bindings of the goto statement.  */
  ساخت c_spot_bindings goto_bindings;
};

قسمتعریف ساخت c_goto_bindings *c_goto_bindings_p;

/* The additional information we keep track of for a label binding.
   These fields are updated as scopes are popped.  */

ساخت GTY(()) c_label_vars {
  /* The shadowed c_label_vars, when one label shadows another (which
     can only happen using a __label__ declaration).  */
  ساخت c_label_vars *shadowed;
  /* The bindings when the label was defined.  */
  ساخت c_spot_bindings label_bindings;
  /* A list of decls that we care about: decls about which we should
     warn if a goto branches to this label from later in the function.
     Decls are added to this list as scopes are popped.  We only add
     the decls that matter.  */
  vec<درخت, va_gc> *decls_اندر_scope;
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


ساخت GTY((chain_اگلا ("%h.outer"))) c_scope {
  /* The scope containing this one.  */
  ساخت c_scope *outer;

  /* The next outermost function scope.  */
  ساخت c_scope *outer_function;

  /* All bindings in this scope.  */
  ساخت c_binding *bindings;

  /* For each scope (except the global one), a chain of BLOCK nodes
     for all the scopes that were entered and exited one level down.  */
  درخت بلاکیں;
  درخت بلاکیں_آخری;

  /* The depth of this scope.  Used to keep the ->shadowed chain of
     bindings sorted innermost to outermost.  */
  غیرعلامتی صحیح گہرائی : 28;

  /* True if we are currently filling this scope with parameter
     declarations.  */
  منطقی parm_flag : 1;

  /* True if we saw [*] in this scope.  Used to give an error messages
     if these appears in a function definition.  */
  منطقی had_vla_unspec : 1;

  /* True if we parsed a list of forward parameter decls in this scope.  */
  منطقی had_forward_parm_decls : 1;

  /* True if this is the outermost block scope of a function body.
     This scope contains the parameters, the local variables declared
     in the outermost block, and all the labels (except those in
     nested functions, or declared at block scope with __label__).  */
  منطقی function_body : 1;

  /* True means make a BLOCK for this scope no matter what.  */
  منطقی keep : 1;

  /* True means that an unsuffixed float constant is _Decimal64.  */
  منطقی float_const_decimal64 : 1;

  /* True if this scope has any label bindings.  This is used to speed
     up searching for labels when popping scopes, particularly since
     labels are normally only found at function scope.  */
  منطقی has_label_bindings : 1;

  /* True if we should issue a warning if a goto statement crosses any
     of the bindings.  We still need to check the list of bindings to
     find the specific ones we need to warn about.  This is true if
     decl_jump_unsafe would return true for any of the bindings.  This
     is used to avoid looping over all the bindings unnecessarily.  */
  منطقی has_jump_unsafe_decl : 1;
};

/* The scope currently in effect.  */

ساکن GTY(()) ساخت c_scope *current_scope;

/* The innermost function scope.  Ordinary (not explicitly declared)
   labels, bindings to error_mark_node, and the lazily-created
   bindings of __func__ and its friends get this scope.  */

ساکن GTY(()) ساخت c_scope *current_function_scope;

/* The C file scope.  This is reset for each input translation unit.  */

ساکن GTY(()) ساخت c_scope *file_scope;

/* The outermost scope.  This is used for all declarations with
   external linkage, and only these, hence the name.  */

ساکن GTY(()) ساخت c_scope *external_scope;

/* A chain of c_scope structures awaiting reuse.  */

ساکن GTY((deletable)) ساخت c_scope *scope_freelist;

/* A chain of c_binding structures awaiting reuse.  */

ساکن GTY((deletable)) ساخت c_binding *binding_freelist;

/* Append VAR to LIST in scope SCOPE.  */
#تعریف_کرو SCOPE_LIST_APPEND(scope, list, decl) کرو {	\
  ساخت c_scope *s_ = (scope);				\
  درخت d_ = (decl);					\
  اگر (s_->list##_last)					\
    بلاک_CHAIN (s_->list##_last) = d_;			\
  ورنہ							\
    s_->list = d_;					\
  s_->list##_last = d_;					\
} جب (0)

/* Concatenate FROM in scope FSCOPE onto TO in scope TSCOPE.  */
#تعریف_کرو SCOPE_LIST_CONCAT(tscope, مقصد, fscope, from) کرو {	\
  ساخت c_scope *t_ = (tscope);				\
  ساخت c_scope *f_ = (fscope);				\
  اگر (t_->مقصد##_last)						\
    بلاک_CHAIN (t_->مقصد##_last) = f_->from;			\
  ورنہ								\
    t_->مقصد = f_->from;						\
  t_->مقصد##_last = f_->from##_last;				\
} جب (0)

/* A c_inline_static structure stores details of a static identifier
   referenced in a definition of a function that may be an inline
   definition if no subsequent declaration of that function uses
   "extern" or does not use "inline".  */

ساخت GTY((chain_اگلا ("%h.next"))) c_inline_static {
  /* The location for a diagnostic.  */
  location_t location;

  /* The function that may be an inline definition.  */
  درخت function;

  /* The object or function referenced.  */
  درخت static_decl;

  /* What sort of reference this is.  */
  شمار c_inline_static_type type;

  /* The next such structure or NULL.  */
  ساخت c_inline_static *اگلا;
};

/* List of static identifiers used or referenced in functions that may
   be inline definitions.  */
ساکن GTY(()) ساخت c_inline_static *c_inline_statics;

/* True means unconditionally make a BLOCK for the next scope pushed.  */

ساکن منطقی keep_اگلا_level_flag;

/* True means the next call to push_scope will be the outermost scope
   of a function body, so do not push a new scope, merely cease
   expecting parameter decls.  */

ساکن منطقی اگلا_is_function_body;

/* A vector of pointers to c_binding structures.  */

قسمتعریف ساخت c_binding *c_binding_ptr;

/* Information that we keep for a struct or union while it is being
   parsed.  */

جماعت c_struct_parse_info
{
عوامی:
  /* If warn_cxx_compat, a list of types defined within this
     struct.  */
  auto_vec<درخت> struct_types;
  /* If warn_cxx_compat, a list of field names which have bindings,
     and which are defined in this struct, but which are not defined
     in any enclosing struct.  This is used to clear the in_struct
     field of the c_bindings structure.  */
  auto_vec<c_binding_ptr> fields;
  /* If warn_cxx_compat, a list of typedef names used when defining
     fields in this struct.  */
  auto_vec<درخت> typedefs_نظر_آیا;
  /* The location of a previous definition of this struct.  */
  location_t refloc;
};


/* Hash table for structs and unions.  */
ساخت c_struct_hasher : ggc_ptr_hash<درخت_گرہ>
{
  ساکن hashval_t hash (درخت t);
  ساکن منطقی equal (درخت, درخت);
};

/* Hash an RECORD OR UNION.  */
hashval_t
c_struct_hasher::hash (درخت type)
{
  inchash::hash hstate;

  hstate.جوڑو_int (درخت_رمز (type));
  درخت لیبل = c_type_لیبل (type);
  hstate.جوڑو_object (لیبل);

  واپس hstate.انتہا ();
}

/* Compare two RECORD or UNION types.  */
منطقی
c_struct_hasher::equal (درخت t1,  درخت t2)
{
  واپس comptypes_equiv_p (t1, t2);
}

/* All tagged typed so that TYPE_CANONICAL can be set correctly.  */
ساکن GTY (()) hash_جدول<c_struct_hasher> *c_struct_htab;

/* Information for the struct or union currently being parsed, or
   NULL if not parsing a struct or union.  */
ساکن جماعت c_struct_parse_info *struct_parse_info;

/* Forward declarations.  */
ساکن درخت lookup_name_اندر_scope (درخت, ساخت c_scope *);
ساکن درخت c_make_fname_decl (location_t, درخت, صحیح);
ساکن درخت grokdeclarator (ثابت ساخت c_declarator *,
			    ساخت c_declspecs *,
			    شمار decl_context, منطقی, درخت *, درخت *, درخت *,
			    منطقی *, شمار deprecated_حالتیں);
ساکن درخت grokparms (ساخت c_arg_info *, منطقی);
ساکن خالی layout_array_type (درخت);
ساکن ثابت حرف *سرخی_for_builtin_fn (درخت);

/* T is a statement.  Add it to the statement-tree.  This is the
   C/ObjC version--C++ has a slightly different version of this
   function.  */

درخت
جوڑو_stmt (درخت t)
{
  شمار درخت_رمز_2 رمز = درخت_رمز (t);

  اگر (CAN_HAVE_LOCATION_P (t) && رمز != LABEL_اظہاریہ)
    {
      اگر (!اظہاریہ_HAS_LOCATION (t))
	سیٹ_اظہاریہ_LOCATION (t, داخلہ_location);
    }

  /* Add T to the statement-tree.  Non-side-effect statements need to be
     recorded during statement expressions.  */
  اگر (!building_stmt_list_p ())
    ڈالو_stmt_list ();

  اگر (رمز == LABEL_اظہاریہ || رمز == CASE_LABEL_اظہاریہ)
    STATEMENT_LIST_HAS_LABEL (cur_stmt_list) = 1;

  append_مقصد_statement_list_force (t, &cur_stmt_list);

  واپس t;
}





/* Return true if we will want to say something if a goto statement
   crosses DECL.  */

ساکن منطقی
decl_jump_unsafe (درخت decl)
{
  اگر (error_عملیہ_p (decl))
    واپس جھوٹ;

  /* Don't warn for compound literals.  If a goto statement crosses
     their initialization, it should cross also all the places where
     the complit is used or where the complit address might be saved
     into some variable, so code after the label to which goto jumps
     should not be able to refer to the compound literal.  */
  اگر (VAR_P (decl) && C_DECL_COMPOUND_LITERAL_P (decl))
    واپس جھوٹ;

  اگر (flag_openmp
      && VAR_P (decl)
      && lookup_attribute ("omp allocate", DECL_اوصاف (decl)))
    واپس سچ;

  /* Always warn about crossing variably modified types.  */
  اگر ((VAR_P (decl) || درخت_رمز (decl) == TYPE_DECL)
      && c_type_variably_modified_p (درخت_TYPE (decl)))
    واپس سچ;

  /* Otherwise, only warn if -Wgoto-misses-init and this is an
     initialized automatic decl.  */
  اگر (warn_jump_ناکامیاں_init
      && VAR_P (decl)
      && !درخت_STATIC (decl)
      && DECL_INITIAL (decl) != NULL_درخت)
    واپس سچ;

  واپس جھوٹ;
}


خالی
c_print_identifier (FILE *file, درخت گرہ, صحیح indent)
{
  خالی (*save) (شمار c_oracle_request, درخت identifier);

  /* Temporarily hide any binding oracle.  Without this, calls to
     debug_tree from the debugger will end up calling into the oracle,
     making for a confusing debug session.  As the oracle isn't needed
     here for normal operation, it's simplest to suppress it.  */
  save = c_binding_oracle;
  c_binding_oracle = تہی;

  print_گرہ (file, "symbol", I_علامت_DECL (گرہ), indent + 4);
  print_گرہ (file, "tag", I_لیبل_DECL (گرہ), indent + 4);
  print_گرہ (file, "label", I_LABEL_DECL (گرہ), indent + 4);
  اگر (C_IS_RESERVED_لفظ (گرہ) && C_RID_رمز (گرہ) != RID_CXX_COMPAT_WARN)
    {
      درخت rid = ridpointers[C_RID_رمز (گرہ)];
      indent_مقصد (file, indent + 4);
      fprintf (file, "rid " HOST_PTR_PRINTF " \"%s\"",
	       (خالی *) rid, IDENTIFIER_اشارہ_گر (rid));
    }

  c_binding_oracle = save;
}

/* Establish that the scope contains declarations that are sensitive to
   jumps that cross a binding.  Together with decl_jump_unsafe, this is
   used to diagnose such jumps.  */
خالی
c_mark_decl_jump_unsafe_اندر_current_scope ()
{
  current_scope->has_jump_unsafe_decl = 1;
}

/* Establish a binding between NAME, an IDENTIFIER_NODE, and DECL,
   which may be any of several kinds of DECL or TYPE or error_mark_node,
   in the scope SCOPE.  */
ساکن خالی
bind (درخت name, درخت decl, ساخت c_scope *scope, منطقی invisible,
      منطقی nested, location_t locus)
{
  ساخت c_binding *b, **یہاں;

  اگر (binding_freelist)
    {
      b = binding_freelist;
      binding_freelist = b->پچھلا;
    }
  ورنہ
    b = ggc_alloc<c_binding> ();

  b->shadowed = 0;
  b->decl = decl;
  b->id = name;
  b->گہرائی = scope->گہرائی;
  b->invisible = invisible;
  b->nested = nested;
  b->inner_comp = 0;
  b->اندر_struct = 0;
  b->locus = locus;

  b->u.type = تہی;

  b->پچھلا = scope->bindings;
  scope->bindings = b;

  اگر (decl_jump_unsafe (decl))
    scope->has_jump_unsafe_decl = 1;

  اگر (!name)
    واپس;

  انتخاب (درخت_رمز (decl))
    {
    حالت LABEL_DECL:     یہاں = &I_LABEL_BINDING (name);   توڑو;
    حالت ENUMERAL_TYPE:
    حالت UNION_TYPE:
    حالت ریکارڈ_TYPE:    یہاں = &I_لیبل_BINDING (name);     توڑو;
    حالت VAR_DECL:
    حالت FUNCTION_DECL:
    حالت TYPE_DECL:
    حالت CONST_DECL:
    حالت PARM_DECL:
    حالت ERROR_MARK:     یہاں = &I_علامت_BINDING (name);  توڑو;

    طےشدہ:
      gcc_unreachable ();
    }

  /* Locate the appropriate place in the chain of shadowed decls
     to insert this binding.  Normally, scope == current_scope and
     this does nothing.  */
  جب (*یہاں && (*یہاں)->گہرائی > scope->گہرائی)
    یہاں = &(*یہاں)->shadowed;

  b->shadowed = *یہاں;
  *یہاں = b;
}

/* Clear the binding structure B, stick it on the binding_freelist,
   and return the former value of b->prev.  This is used by pop_scope
   and get_parm_info to iterate destructively over all the bindings
   from a given scope.  */
ساکن ساخت c_binding *
free_binding_and_advance (ساخت c_binding *b)
{
  ساخت c_binding *پچھلا = b->پچھلا;

  memset (b, 0, حجم (ساخت c_binding));
  b->پچھلا = binding_freelist;
  binding_freelist = b;

  واپس پچھلا;
}

/* Bind a label.  Like bind, but skip fields which aren't used for
   labels, and add the LABEL_VARS value.  */
ساکن خالی
bind_label (درخت name, درخت label, ساخت c_scope *scope,
	    ساخت c_label_vars *label_vars)
{
  ساخت c_binding *b;

  bind (name, label, scope, /*invisible=*/جھوٹ, /*nested=*/جھوٹ,
	UNKNOWN_LOCATION);

  scope->has_label_bindings = سچ;

  b = scope->bindings;
  gcc_assert (b->decl == label);
  label_vars->shadowed = b->u.label;
  b->u.label = label_vars;
}

/* Hook called at end of compilation to assume 1 elt
   for a file-scope tentative array defn that wasn't complete before.  */

خالی
c_اختتام_incomplete_decl (درخت decl)
{
  اگر (VAR_P (decl))
    {
      درخت type = درخت_TYPE (decl);
      اگر (type != error_mark_گرہ
	  && درخت_رمز (type) == ARRAY_TYPE
	  && !DECL_EXTERNAL (decl)
	  && TYPE_DOMAIN (type) == NULL_درخت)
	{
	  اگر (flag_isoc2y && !درخت_عوامی (decl))
	    error_at (DECL_ماخذ_LOCATION (decl),
		      "array size missing in %q+D", decl);
	  ورنہ
	    warning_at (DECL_ماخذ_LOCATION (decl),
			0, "array %q+D assumed to have one element", decl);

	  complete_array_type (&درخت_TYPE (decl), NULL_درخت, سچ);

	  relayout_decl (decl);
	}
    }
}

/* Record that inline function FUNC contains a reference (location
   LOC) to static DECL (file-scope or function-local according to
   TYPE).  */

خالی
ریکارڈ_inline_static (location_t loc, درخت func, درخت decl,
		      شمار c_inline_static_type type)
{
  c_inline_static *csi = ggc_alloc<c_inline_static> ();
  csi->location = loc;
  csi->function = func;
  csi->static_decl = decl;
  csi->type = type;
  csi->اگلا = c_inline_statics;
  c_inline_statics = csi;
}

/* Check for references to static declarations in inline functions at
   the end of the translation unit and diagnose them if the functions
   are still inline definitions.  */

ساکن خالی
check_inline_statics (خالی)
{
  ساخت c_inline_static *csi;
  برائے (csi = c_inline_statics; csi; csi = csi->اگلا)
    {
      اگر (DECL_EXTERNAL (csi->function))
	انتخاب (csi->type)
	  {
	  حالت csi_اندرونی:
	    pedwarn (csi->location, 0,
		     "%qD is static but used in inline function %qD "
		     "which is not static", csi->static_decl, csi->function);
	    توڑو;
	  حالت csi_modifiable:
	    pedwarn (csi->location, 0,
		     "%q+D is static but declared in inline function %qD "
		     "which is not static", csi->static_decl, csi->function);
	    توڑو;
	  طےشدہ:
	    gcc_unreachable ();
	  }
    }
  c_inline_statics = تہی;
}

/* Fill in a c_spot_bindings structure.  If DEFINING is true, set it
   for the current state, otherwise set it to uninitialized.  */

ساکن خالی
سیٹ_spot_bindings (ساخت c_spot_bindings *p, منطقی defining)
{
  اگر (defining)
    {
      p->scope = current_scope;
      p->bindings_اندر_scope = current_scope->bindings;
    }
  ورنہ
    {
      p->scope = تہی;
      p->bindings_اندر_scope = تہی;
    }
  p->stmt_exprs = 0;
  p->بایاں_stmt_اظہاریہ = جھوٹ;
}

/* Update spot bindings P as we pop out of SCOPE.  Return true if we
   should push decls for a label.  */

ساکن منطقی
update_spot_bindings (ساخت c_scope *scope, ساخت c_spot_bindings *p)
{
  اگر (p->scope != scope)
    {
      /* This label or goto is defined in some other scope, or it is a
	 label which is not yet defined.  There is nothing to
	 update.  */
      واپس جھوٹ;
    }

  /* Adjust the spot bindings to refer to the bindings already defined
     in the enclosing scope.  */
  p->scope = scope->outer;
  p->bindings_اندر_scope = p->scope->bindings;

  واپس سچ;
}

/* The Objective-C front-end often needs to determine the current scope.  */

خالی *
objc_get_current_scope (خالی)
{
  واپس current_scope;
}

/* The following function is used only by Objective-C.  It needs to live here
   because it accesses the innards of c_scope.  */

خالی
objc_mark_locals_volatile (خالی *enclosing_blk)
{
  ساخت c_scope *scope;
  ساخت c_binding *b;

  برائے (scope = current_scope;
       scope && scope != enclosing_blk;
       scope = scope->outer)
    {
      برائے (b = scope->bindings; b; b = b->پچھلا)
	objc_volatilize_decl (b->decl);

      /* Do not climb up past the current function.  */
      اگر (scope->function_body)
	توڑو;
    }
}

/* Return true if we are in the global binding level.  */

منطقی
global_bindings_p (خالی)
{
  واپس current_scope == file_scope;
}

/* Return true if we're declaring parameters in an old-style function
   declaration.  */

منطقی
old_style_parameter_scope (خالی)
{
  /* If processing parameters and there is no function statement list, we
   * have an old-style function declaration.  */
  واپس (current_scope->parm_flag && !DECL_SAVED_درخت (current_function_decl));
}

خالی
keep_اگلا_level (خالی)
{
  keep_اگلا_level_flag = سچ;
}

/* Set the flag for the FLOAT_CONST_DECIMAL64 pragma being ON.  */

خالی
سیٹ_float_const_decimal64 (خالی)
{
  current_scope->float_const_decimal64 = سچ;
}

/* Clear the flag for the FLOAT_CONST_DECIMAL64 pragma.  */

خالی
clear_float_const_decimal64 (خالی)
{
  current_scope->float_const_decimal64 = جھوٹ;
}

/* Return nonzero if an unsuffixed float constant is _Decimal64.  */

منطقی
float_const_decimal64_p (خالی)
{
  واپس current_scope->float_const_decimal64;
}

/* Identify this scope as currently being filled with parameters.  */

خالی
declare_parm_level (خالی)
{
  current_scope->parm_flag = سچ;
}

خالی
ڈالو_scope (خالی)
{
  اگر (اگلا_is_function_body)
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
      current_scope->parm_flag         = جھوٹ;
      current_scope->function_body     = سچ;
      current_scope->keep              = سچ;
      current_scope->outer_function    = current_function_scope;
      current_function_scope           = current_scope;

      keep_اگلا_level_flag = جھوٹ;
      اگلا_is_function_body = جھوٹ;

      /* The FLOAT_CONST_DECIMAL64 pragma applies to nested scopes.  */
      اگر (current_scope->outer)
	current_scope->float_const_decimal64
	  = current_scope->outer->float_const_decimal64;
      ورنہ
	current_scope->float_const_decimal64 = جھوٹ;
    }
  ورنہ
    {
      ساخت c_scope *scope;
      اگر (scope_freelist)
	{
	  scope = scope_freelist;
	  scope_freelist = scope->outer;
	}
      ورنہ
	scope = ggc_cleared_alloc<c_scope> ();

      /* The FLOAT_CONST_DECIMAL64 pragma applies to nested scopes.  */
      اگر (current_scope)
	scope->float_const_decimal64 = current_scope->float_const_decimal64;
      ورنہ
	scope->float_const_decimal64 = جھوٹ;

      scope->keep          = keep_اگلا_level_flag;
      scope->outer         = current_scope;
      scope->گہرائی	   = current_scope ? (current_scope->گہرائی + 1) : 0;

      /* Check for scope depth overflow.  Unlikely (2^28 == 268,435,456) but
	 possible.  */
      اگر (current_scope && scope->گہرائی == 0)
	{
	  scope->گہرائی--;
	  sorry ("GCC supports only %u nested scopes", scope->گہرائی);
	}

      current_scope        = scope;
      keep_اگلا_level_flag = جھوٹ;
    }
}

/* This is called when we are leaving SCOPE.  For each label defined
   in SCOPE, add any appropriate decls to its decls_in_scope fields.
   These are the decls whose initialization will be skipped by a goto
   later in the function.  */

ساکن خالی
update_label_decls (ساخت c_scope *scope)
{
  ساخت c_scope *s;

  s = scope;
  جب (s != تہی)
    {
      اگر (s->has_label_bindings)
	{
	  ساخت c_binding *b;

	  برائے (b = s->bindings; b != تہی; b = b->پچھلا)
	    {
	      ساخت c_label_vars *label_vars;
	      ساخت c_binding *b1;
	      منطقی hjud;
	      غیرعلامتی صحیح ix;
	      ساخت c_goto_bindings *g;

	      اگر (درخت_رمز (b->decl) != LABEL_DECL)
		جاری;
	      label_vars = b->u.label;

	      b1 = label_vars->label_bindings.bindings_اندر_scope;
	      اگر (label_vars->label_bindings.scope == تہی)
		hjud = جھوٹ;
	      ورنہ
		hjud = label_vars->label_bindings.scope->has_jump_unsafe_decl;
	      اگر (update_spot_bindings (scope, &label_vars->label_bindings))
		{
		  /* This label is defined in this scope.  */
		  اگر (hjud)
		    {
		      برائے (; b1 != تہی; b1 = b1->پچھلا)
			{
			  /* A goto from later in the function to this
			     label will never see the initialization
			     of B1, if any.  Save it to issue a
			     warning if needed.  */
			  اگر (decl_jump_unsafe (b1->decl))
			    vec_محفوظ_ڈالو(label_vars->decls_اندر_scope, b1->decl);
			}
		    }
		}

	      /* Update the bindings of any goto statements associated
		 with this label.  */
	      FOR_EACH_VEC_محفوظ_ELT (label_vars->gotos, ix, g)
		update_spot_bindings (scope, &g->goto_bindings);
	    }
	}

      /* Don't search beyond the current function.  */
      اگر (s == current_function_scope)
	توڑو;

      s = s->outer;
    }
}

/* Exit a scope.  Restore the state of the identifier-decl mappings
   that were in effect when this scope was entered.  Return a BLOCK
   node containing all the DECLs in this scope that are of interest
   to debug info generation.  */

درخت
نکالو_scope (خالی)
{
  ساخت c_scope *scope = current_scope;
  درخت بلاک, context, p;
  ساخت c_binding *b;

  منطقی functionbody = scope->function_body;
  منطقی keep = functionbody || scope->keep || scope->bindings;

  update_label_decls (scope);

  /* If appropriate, create a BLOCK to record the decls for the life
     of this function.  */
  بلاک = NULL_درخت;
  اگر (keep)
    {
      بلاک = make_گرہ (بلاک_2);
      بلاک_SUBBLOCKS (بلاک) = scope->بلاکیں;
      درخت_مستعمل (بلاک) = 1;

      /* In each subblock, record that this is its superior.  */
      برائے (p = scope->بلاکیں; p; p = بلاک_CHAIN (p))
	بلاک_SUPERCONTEXT (p) = بلاک;

      بلاک_VARS (بلاک) = NULL_درخت;
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
  اگر (scope->function_body)
    context = current_function_decl;
  ورنہ اگر (scope == file_scope)
    {
      درخت file_decl
	= build_translation_unit_decl (get_identifier (main_داخلہ_filename));
      context = file_decl;
      debug_hooks->رجسٹر_main_translation_unit (file_decl);
    }
  ورنہ
    context = بلاک;

  /* Clear all bindings in this scope.  */
  برائے (b = scope->bindings; b; b = free_binding_and_advance (b))
    {
      p = b->decl;
      انتخاب (درخت_رمز (p))
	{
	حالت LABEL_DECL:
	  /* Warnings for unused labels, errors for undefined labels.  */
	  اگر (درخت_مستعمل (p) && !DECL_INITIAL (p))
	    {
	      error ("label %q+D used but not defined", p);
	      DECL_INITIAL (p) = error_mark_گرہ;
	    }
	  ورنہ
	    warn_for_غیر_مستعمل_label (p);

	  /* Labels go in BLOCK_VARS.  */
	  DECL_CHAIN (p) = بلاک_VARS (بلاک);
	  بلاک_VARS (بلاک) = p;
	  gcc_assert (I_LABEL_BINDING (b->id) == b);
	  I_LABEL_BINDING (b->id) = b->shadowed;

	  /* Also pop back to the shadowed label_vars.  */
	  release_درخت_سمتیہ (b->u.label->decls_اندر_scope);
	  b->u.label = b->u.label->shadowed;
	  توڑو;

	حالت ENUMERAL_TYPE:
	حالت UNION_TYPE:
	حالت ریکارڈ_TYPE:

	  /* Types may not have tag-names, in which case the type
	     appears in the bindings list with b->id NULL.  */
	  اگر (b->id)
	    {
	      gcc_assert (I_لیبل_BINDING (b->id) == b);
	      I_لیبل_BINDING (b->id) = b->shadowed;
	    }
	  توڑو;

	حالت FUNCTION_DECL:
	  /* Propagate TREE_ADDRESSABLE from nested functions to their
	     containing functions.  */
	  اگر (!درخت_ASM_WRITTEN (p)
	      && DECL_INITIAL (p) != NULL_درخت
	      && درخت_ADDRESSABLE (p)
	      && DECL_ABSTRACT_ORIGIN (p) != NULL_درخت
	      && DECL_ABSTRACT_ORIGIN (p) != p)
	    درخت_ADDRESSABLE (DECL_ABSTRACT_ORIGIN (p)) = 1;
	  اگر (!درخت_عوامی (p)
	      && !DECL_INITIAL (p)
	      && !b->nested
	      && scope != file_scope
	      && scope != external_scope)
	    {
	      error ("nested function %q+D declared but never defined", p);
	      undef_nested_function = سچ;
	    }
	  ورنہ اگر (DECL_DECLARED_INLINE_P (p)
		   && درخت_عوامی (p)
		   && !DECL_INITIAL (p))
	    {
	      /* C99 6.7.4p6: "a function with external linkage... declared
		 with an inline function specifier ... shall also be defined
		 in the same translation unit."  */
	      اگر (!flag_gnu89_inline
		  && !lookup_attribute ("gnu_inline", DECL_اوصاف (p))
		  && scope == external_scope)
		pedwarn (داخلہ_location, 0,
			 "inline function %q+D declared but never defined", p);
	      DECL_EXTERNAL (p) = 1;
	    }

	  جاؤ common_علامت;

	حالت VAR_DECL:
	  /* Warnings for unused variables.  */
	  اگر ((!درخت_مستعمل (p) || !DECL_READ_P (p))
	      && !warning_suppressed_p (p, OPT_Wunused_but_سیٹ_variable)
	      && !DECL_اندر_SYSTEM_سرخی (p)
	      && DECL_NAME (p)
	      && !DECL_ARTIFICIAL (p)
	      && scope != file_scope
	      && scope != external_scope)
	    {
	      اگر (!درخت_مستعمل (p))
		{
		  warning (OPT_Wunused_variable, "unused variable %q+D", p);
		  suppress_warning (p, OPT_Wunused_variable);
		}
	      ورنہ اگر (DECL_CONTEXT (p) == current_function_decl)
		warning_at (DECL_ماخذ_LOCATION (p),
			    OPT_Wunused_but_سیٹ_variable,
			    "variable %qD set but not used", p);
	    }

	  اگر (b->inner_comp)
	    {
	      error ("type of array %q+D completed incompatibly with"
		     " implicit initialization", p);
	    }

	  /* Fall through.  */
	حالت TYPE_DECL:
	حالت CONST_DECL:
	common_علامت:
	  /* All of these go in BLOCK_VARS, but only if this is the
	     binding in the home scope.  */
	  اگر (!b->nested)
	    {
	      DECL_CHAIN (p) = بلاک_VARS (بلاک);
	      بلاک_VARS (بلاک) = p;
	    }
	  ورنہ اگر (VAR_OR_FUNCTION_DECL_P (p) && scope != file_scope)
	    {
	      /* For block local externs add a special
		 DECL_EXTERNAL decl for debug info generation.  */
	      درخت extp = copy_گرہ (p);

	      DECL_EXTERNAL (extp) = 1;
	      درخت_STATIC (extp) = 0;
	      درخت_عوامی (extp) = 1;
	      DECL_INITIAL (extp) = NULL_درخت;
	      DECL_LANG_SPECIFIC (extp) = تہی;
	      DECL_CONTEXT (extp) = current_function_decl;
	      اگر (درخت_رمز (p) == FUNCTION_DECL)
		{
		  DECL_نتیجہ (extp) = NULL_درخت;
		  DECL_SAVED_درخت (extp) = NULL_درخت;
		  DECL_STRUCT_FUNCTION (extp) = تہی;
		}
	      اگر (b->locus != UNKNOWN_LOCATION)
		DECL_ماخذ_LOCATION (extp) = b->locus;
	      DECL_CHAIN (extp) = بلاک_VARS (بلاک);
	      بلاک_VARS (بلاک) = extp;
	    }
	  /* If this is the file scope set DECL_CONTEXT of each decl to
	     the TRANSLATION_UNIT_DECL.  This makes same_translation_unit_p
	     work.  */
	  اگر (scope == file_scope)
	      DECL_CONTEXT (p) = context;

	  gcc_fallthrough ();
	  /* Parameters go in DECL_ARGUMENTS, not BLOCK_VARS, and have
	     already been put there by store_parm_decls.  Unused-
	     parameter warnings are handled by function.cc.
	     error_mark_node obviously does not go in BLOCK_VARS and
	     does not get unused-variable warnings.  */
	حالت PARM_DECL:
	حالت ERROR_MARK:
	  /* It is possible for a decl not to have a name.  We get
	     here with b->id NULL in this case.  */
	  اگر (b->id)
	    {
	      gcc_assert (I_علامت_BINDING (b->id) == b);
	      I_علامت_BINDING (b->id) = b->shadowed;
	      اگر (b->shadowed && b->shadowed->u.type)
		درخت_TYPE (b->shadowed->decl) = b->shadowed->u.type;
	    }
	  توڑو;

	طےشدہ:
	  gcc_unreachable ();
	}
    }


  /* Dispose of the block that we just made inside some higher level.  */
  اگر ((scope->function_body || scope == file_scope) && context)
    {
      DECL_INITIAL (context) = بلاک;
      بلاک_SUPERCONTEXT (بلاک) = context;
    }
  ورنہ اگر (scope->outer)
    {
      اگر (بلاک)
	SCOPE_LIST_APPEND (scope->outer, بلاکیں, بلاک);
      /* If we did not make a block for the scope just exited, any
	 blocks made for inner scopes must be carried forward so they
	 will later become subblocks of something else.  */
      ورنہ اگر (scope->بلاکیں)
	SCOPE_LIST_CONCAT (scope->outer, بلاکیں, scope, بلاکیں);
    }

  /* Pop the current scope, and free the structure for reuse.  */
  current_scope = scope->outer;
  اگر (scope->function_body)
    current_function_scope = scope->outer_function;

  memset (scope, 0, حجم (ساخت c_scope));
  scope->outer = scope_freelist;
  scope_freelist = scope;

  واپس بلاک;
}

خالی
ڈالو_file_scope (خالی)
{
  درخت decl;

  اگر (file_scope)
    واپس;

  /* Call the target stack_protect_guard hook if the stack protection
     guard is declared as a global symbol.  */
  اگر (targetm.ڈھیر_protect_guard_علامت_p ())
    {
      درخت decl = targetm.ڈھیر_protect_guard ();
      DECL_CHAIN (decl) = visible_builtins;
      visible_builtins = decl;
    }

  ڈالو_scope ();
  file_scope = current_scope;

  آغاز_fname_decls ();

  برائے (decl = visible_builtins; decl; decl = DECL_CHAIN (decl))
    bind (DECL_NAME (decl), decl, file_scope,
	  /*invisible=*/جھوٹ, /*nested=*/سچ, DECL_ماخذ_LOCATION (decl));
}

خالی
نکالو_file_scope (خالی)
{
  /* In case there were missing closebraces, get us back to the global
     binding level.  */
  جب (current_scope != file_scope)
    نکالو_scope ();

  /* __FUNCTION__ is defined at file scope ("").  This
     call may not be necessary as my tests indicate it
     still works without it.  */
  اختتام_fname_decls ();

  check_inline_statics ();

  /* This is the point to write out a PCH if we're doing that.
     In that case we do not want to do anything else.  */
  اگر (pch_file)
    {
      c_common_write_pch ();
      /* Ensure even the callers don't try to finalize the CU.  */
      flag_syntax_only = 1;
      واپس;
    }

  /* Pop off the file scope and close this translation unit.  */
  نکالو_scope ();
  file_scope = 0;

  maybe_apply_pending_pragma_weaks ();
}

/* Whether we are currently inside the initializer for an
   underspecified object definition (C23 auto or constexpr).  */
ساکن منطقی اندر_underspecified_init;

/* Start an underspecified object definition for NAME at LOC.  This
   means that NAME is shadowed inside its initializer, so neither the
   definition being initialized, nor any definition from an outer
   scope, may be referenced during that initializer.  Return state to
   be passed to finish_underspecified_init.  If NAME is NULL_TREE, the
   underspecified object is a (constexpr) compound literal; there is
   no shadowing in that case, but all the other restrictions on
   underspecified object definitions still apply.  */
غیرعلامتی صحیح
آغاز_underspecified_init (location_t loc, درخت name)
{
  منطقی پچھلا = اندر_underspecified_init;
  منطقی ok;
  اگر (name == NULL_درخت)
    ok = سچ;
  ورنہ
    {
      درخت decl = build_decl (loc, VAR_DECL, name, error_mark_گرہ);
      C_DECL_UNDERSPECIFIED (decl) = 1;
      ساخت c_scope *scope = current_scope;
      ساخت c_binding *b = I_علامت_BINDING (name);
      اگر (b && B_اندر_SCOPE (b, scope))
	{
	  error_at (loc, "underspecified declaration of %qE, which is already "
		    "declared in this scope", name);
	  ok = جھوٹ;
	}
      ورنہ
	{
	  bind (name, decl, scope, جھوٹ, جھوٹ, loc);
	  ok = سچ;
	}
    }
  اندر_underspecified_init = سچ;
  واپس ok | (پچھلا << 1);
}

/* Finish an underspecified object definition for NAME, before that
   name is bound to the real declaration instead of a placeholder.
   PREV_STATE is the value returned by the call to
   start_underspecified_init.  If NAME is NULL_TREE, this means a
   compound literal, as for start_underspecified_init.  */
خالی
اختتام_underspecified_init (درخت name, غیرعلامتی صحیح پچھلا_state)
{
  اگر (name != NULL_درخت && (پچھلا_state & 1))
    {
      /* A VAR_DECL was bound to the name to shadow any previous
	 declarations for the name; remove that binding now.  */
      ساخت c_scope *scope = current_scope;
      ساخت c_binding *b = I_علامت_BINDING (name);
      gcc_assert (b);
      gcc_assert (B_اندر_SCOPE (b, scope));
      gcc_assert (VAR_P (b->decl));
      gcc_assert (C_DECL_UNDERSPECIFIED (b->decl));
      I_علامت_BINDING (name) = b->shadowed;
      /* In erroneous cases there may be other bindings added to this
	 scope during the initializer.  */
      ساخت c_binding **p = &scope->bindings;
      جب (*p != b)
	p = &((*p)->پچھلا);
      *p = free_binding_and_advance (*p);
    }
  اندر_underspecified_init = (پچھلا_state & (1u << 1)) >> 1;
}

/* Adjust the bindings for the start of a statement expression.  */

خالی
c_bindings_آغاز_stmt_اظہاریہ (ساخت c_spot_bindings* switch_bindings)
{
  ساخت c_scope *scope;

  برائے (scope = current_scope; scope != تہی; scope = scope->outer)
    {
      ساخت c_binding *b;

      اگر (!scope->has_label_bindings)
	جاری;

      برائے (b = scope->bindings; b != تہی; b = b->پچھلا)
	{
	  ساخت c_label_vars *label_vars;
	  غیرعلامتی صحیح ix;
	  ساخت c_goto_bindings *g;

	  اگر (درخت_رمز (b->decl) != LABEL_DECL)
	    جاری;
	  label_vars = b->u.label;
	  ++label_vars->label_bindings.stmt_exprs;
	  FOR_EACH_VEC_محفوظ_ELT (label_vars->gotos, ix, g)
	    ++g->goto_bindings.stmt_exprs;
	}
    }

  اگر (switch_bindings != تہی)
    ++switch_bindings->stmt_exprs;
}

/* Adjust the bindings for the end of a statement expression.  */

خالی
c_bindings_انتہا_stmt_اظہاریہ (ساخت c_spot_bindings *switch_bindings)
{
  ساخت c_scope *scope;

  برائے (scope = current_scope; scope != تہی; scope = scope->outer)
    {
      ساخت c_binding *b;

      اگر (!scope->has_label_bindings)
	جاری;

      برائے (b = scope->bindings; b != تہی; b = b->پچھلا)
	{
	  ساخت c_label_vars *label_vars;
	  غیرعلامتی صحیح ix;
	  ساخت c_goto_bindings *g;

	  اگر (درخت_رمز (b->decl) != LABEL_DECL)
	    جاری;
	  label_vars = b->u.label;
	  --label_vars->label_bindings.stmt_exprs;
	  اگر (label_vars->label_bindings.stmt_exprs < 0)
	    {
	      label_vars->label_bindings.بایاں_stmt_اظہاریہ = سچ;
	      label_vars->label_bindings.stmt_exprs = 0;
	    }
	  FOR_EACH_VEC_محفوظ_ELT (label_vars->gotos, ix, g)
	    {
	      --g->goto_bindings.stmt_exprs;
	      اگر (g->goto_bindings.stmt_exprs < 0)
		{
		  g->goto_bindings.بایاں_stmt_اظہاریہ = سچ;
		  g->goto_bindings.stmt_exprs = 0;
		}
	    }
	}
    }

  اگر (switch_bindings != تہی)
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

ساکن خالی
pushtag (location_t loc, درخت name, درخت type)
{
  /* Record the identifier as the type's name if it has none.  */
  اگر (name && !TYPE_NAME (type))
    TYPE_NAME (type) = name;
  bind (name, type, current_scope, /*invisible=*/جھوٹ, /*nested=*/جھوٹ, loc);

  /* Create a fake NULL-named TYPE_DECL node whose TREE_TYPE will be the
     tagged type we just added to the current scope.  This fake
     NULL-named TYPE_DECL node helps dwarfout.c to know when it needs
     to output a representation of a tagged type, and it also gives
     us a convenient place to record the "scope start" address for the
     tagged type, and it is used to track whether the type is used
     in a non-local context via mark_decl_used.  */

  TYPE_STUB_DECL (type) = pushdecl (build_decl (loc,
						TYPE_DECL, NULL_درخت, type));

  /* An approximation for now, so we can tell this is a function-scope tag.
     This will be updated in pop_scope.  */
  TYPE_CONTEXT (type) = DECL_CONTEXT (TYPE_STUB_DECL (type));

  اگر (warn_cxx_compat && name != NULL_درخت)
    {
      ساخت c_binding *b = I_علامت_BINDING (name);

      اگر (b != تہی
	  && b->decl != NULL_درخت
	  && درخت_رمز (b->decl) == TYPE_DECL
	  && (B_اندر_CURRENT_SCOPE (b)
	      || (current_scope == file_scope && B_اندر_EXTERNAL_SCOPE (b)))
	  && (TYPE_MAIN_VARIANT (درخت_TYPE (b->decl))
	      != TYPE_MAIN_VARIANT (type)))
	{
	  auto_diagnostic_گروہ d;
	  اگر (warning_at (loc, OPT_Wc___compat,
			  "using %qD as both a typedef and a tag is "
			  "invalid in C++", b->decl)
	      && b->locus != UNKNOWN_LOCATION)
	    inform (b->locus, "originally defined here");
	}
    }
}

/* An exported interface to pushtag.  This is used by the gdb plugin's
   binding oracle to introduce a new tag binding.  */

خالی
c_pushtag (location_t loc, درخت name, درخت type)
{
  pushtag (loc, name, type);
}

/* An exported interface to bind a declaration.  LOC is the location
   to use.  DECL is the declaration to bind.  The decl's name is used
   to determine how it is bound.  If DECL is a VAR_DECL, then
   IS_GLOBAL determines whether the decl is put into the global (file
   and external) scope or the current function's scope; if DECL is not
   a VAR_DECL then it is always put into the file scope.  */

خالی
c_bind (location_t loc, درخت decl, منطقی is_global)
{
  ساخت c_scope *scope;
  منطقی nested = جھوٹ;

  اگر (!VAR_P (decl) || current_function_scope == تہی)
    {
      /* Types and functions are always considered to be global.  */
      scope = file_scope;
      DECL_EXTERNAL (decl) = 1;
      درخت_عوامی (decl) = 1;
    }
  ورنہ اگر (is_global)
    {
      /* Also bind it into the external scope.  */
      bind (DECL_NAME (decl), decl, external_scope, سچ, جھوٹ, loc);
      nested = سچ;
      scope = file_scope;
      DECL_EXTERNAL (decl) = 1;
      درخت_عوامی (decl) = 1;
    }
  ورنہ
    {
      DECL_CONTEXT (decl) = current_function_decl;
      درخت_عوامی (decl) = 0;
      scope = current_function_scope;
    }

  bind (DECL_NAME (decl), decl, scope, جھوٹ, nested, loc);
}


/* Stores the first FILE*, const struct tm* etc. argument type (whatever
   it is) seen in a declaration of a file I/O etc. built-in, corresponding
   to the builtin_structptr_types array.  Subsequent declarations of such
   built-ins are expected to refer to it rather than to fileptr_type_node,
   etc. which is just void* (or to any other type).
   Used only by match_builtin_function_types.  */

ساکن ثابت غیرعلامتی builtin_structptr_type_گنتی
  = ARRAY_سائز (builtin_structptr_types);

ساکن GTY(()) درخت آخری_structptr_types[builtin_structptr_type_گنتی];

/* Returns true if types T1 and T2 representing return types or types
   of function arguments are close enough to be considered interchangeable
   in redeclarations of built-in functions.  */

ساکن منطقی
types_close_enough_مقصد_مطابقت (درخت t1, درخت t2)
{
  واپس (TYPE_منوال (t1) == TYPE_منوال (t2)
	  && اشارہ_گر_TYPE_P (t1) == اشارہ_گر_TYPE_P (t2)
	  && FUNCTION_اشارہ_گر_TYPE_P (t1) == FUNCTION_اشارہ_گر_TYPE_P (t2));
}

/* Subroutine of compare_decls.  Allow harmless mismatches in return
   and argument types provided that the type modes match.  Set *STRICT
   and *ARGNO to the expected argument type and number in case of
   an argument type mismatch or null and zero otherwise.  Return
   a unified type given a suitable match, and 0 otherwise.  */

ساکن درخت
مطابقت_builtin_function_types (درخت newtype, درخت oldtype,
			      درخت *strict, غیرعلامتی *argno)
{
  *argno = 0;
  *strict = NULL_درخت;

  /* Accept the return type of the new declaration if it has the same
     mode and if they're both pointers or if neither is.  */
  درخت oldrettype = درخت_TYPE (oldtype);
  درخت newrettype = درخت_TYPE (newtype);

  اگر (!types_close_enough_مقصد_مطابقت (oldrettype, newrettype))
    واپس NULL_درخت;

  /* Check that the return types are compatible but don't fail if they
     are not (e.g., int vs long in ILP32) and just let the caller know.  */
  اگر (!comptypes (TYPE_MAIN_VARIANT (oldrettype),
		  TYPE_MAIN_VARIANT (newrettype)))
    *strict = oldrettype;

  درخت oldargs = TYPE_ARG_TYPES (oldtype);
  درخت newargs = TYPE_ARG_TYPES (newtype);
  درخت tryargs = newargs;

  ثابت غیرعلامتی nlst = ARRAY_سائز (آخری_structptr_types);
  ثابت غیرعلامتی nbst = ARRAY_سائز (builtin_structptr_types);

  gcc_checking_assert (nlst == nbst);

  برائے (غیرعلامتی i = 1; oldargs || newargs; ++i)
    {
      اگر (!oldargs
	  || !newargs
	  || !درخت_قدر (oldargs)
	  || !درخت_قدر (newargs))
	واپس NULL_درخت;

      درخت oldtype = TYPE_MAIN_VARIANT (درخت_قدر (oldargs));
      درخت newtype = درخت_قدر (newargs);
      اگر (newtype == error_mark_گرہ)
       واپس NULL_درخت;
      newtype = TYPE_MAIN_VARIANT (newtype);

      اگر (!types_close_enough_مقصد_مطابقت (oldtype, newtype))
	واپس NULL_درخت;

      غیرعلامتی j = nbst;
      اگر (اشارہ_گر_TYPE_P (oldtype))
	/* Iterate over well-known struct types like FILE (whose types
	   aren't known to us) and compare the pointer to each to
	   the pointer argument.  */
	برائے (j = 0; j < nbst; ++j)
	  {
	    اگر (درخت_قدر (oldargs) != builtin_structptr_types[j].گرہ)
	      جاری;
	    /* Store the first FILE* etc. argument type (whatever it is), and
	       expect any subsequent declarations of file I/O etc. built-ins
	       to refer to it rather than to fileptr_type_node etc. which is
	       just void* (or const void*).  */
	    اگر (آخری_structptr_types[j])
	      {
		اگر (!comptypes (آخری_structptr_types[j], newtype))
		  {
		    *argno = i;
		    *strict = آخری_structptr_types[j];
		  }
	      }
	    ورنہ
	      آخری_structptr_types[j] = newtype;
	    توڑو;
	  }

      اگر (j == nbst && !comptypes (oldtype, newtype))
	{
	  اگر (اشارہ_گر_TYPE_P (oldtype))
	    {
	      /* For incompatible pointers, only reject differences in
		 the unqualified variants of the referenced types but
		 consider differences in qualifiers as benign (report
		 those to caller via *STRICT below).  */
	      درخت oldref = TYPE_MAIN_VARIANT (درخت_TYPE (oldtype));
	      درخت newref = TYPE_MAIN_VARIANT (درخت_TYPE (newtype));
	      اگر (!comptypes (oldref, newref))
		واپس NULL_درخت;
	    }

	  اگر (!*strict)
	    {
	      *argno = i;
	      *strict = oldtype;
	    }
	}

      oldargs = درخت_CHAIN (oldargs);
      newargs = درخت_CHAIN (newargs);
    }

  درخت trytype = c_build_function_type (newrettype, tryargs);

  /* Allow declaration to change transaction_safe attribute.  */
  درخت oldattrs = TYPE_اوصاف (oldtype);
  درخت oldtsafe = lookup_attribute ("transaction_safe", oldattrs);
  درخت newattrs = TYPE_اوصاف (newtype);
  درخت newtsafe = lookup_attribute ("transaction_safe", newattrs);
  اگر (oldtsafe && !newtsafe)
    oldattrs = remove_attribute ("transaction_safe", oldattrs);
  ورنہ اگر (newtsafe && !oldtsafe)
    oldattrs = درخت_cons (get_identifier ("transaction_safe"),
			  NULL_درخت, oldattrs);

  واپس c_build_type_attribute_variant (trytype, oldattrs);
}

/* Subroutine of diagnose_mismatched_decls.  Check for function type
   mismatch involving an empty arglist vs a nonempty one and give clearer
   diagnostics.  */
ساکن خالی
diagnose_arglist_conflict (درخت newdecl, درخت olddecl,
			   درخت newtype, درخت oldtype)
{
  درخت t;

  اگر (درخت_رمز (olddecl) != FUNCTION_DECL
      || !comptypes (درخت_TYPE (oldtype), درخت_TYPE (newtype))
      || !((!prototype_p (oldtype) && DECL_INITIAL (olddecl) == NULL_درخت)
	   || (!prototype_p (newtype) && DECL_INITIAL (newdecl) == NULL_درخت)))
    واپس;

  t = TYPE_ARG_TYPES (oldtype);
  اگر (t == NULL_درخت)
    t = TYPE_ARG_TYPES (newtype);
  برائے (; t; t = درخت_CHAIN (t))
    {
      درخت type = درخت_قدر (t);

      اگر (درخت_CHAIN (t) == NULL_درخت
	  && TYPE_MAIN_VARIANT (type) != void_type_گرہ)
	{
	  inform (داخلہ_location, "a parameter list with an ellipsis "
		  "cannot match an empty parameter name list declaration");
	  توڑو;
	}

      اگر (!error_عملیہ_p (type)
	  && c_type_promotes_مقصد (type) != type)
	{
	  inform (داخلہ_location, "an argument type that has a default "
		  "promotion cannot match an empty parameter name list "
		  "declaration");
	  توڑو;
	}
    }
}

/* Another subroutine of diagnose_mismatched_decls.  OLDDECL is an
   old-style function definition, NEWDECL is a prototype declaration.
   Diagnose inconsistencies in the argument list.  Returns TRUE if
   the prototype is compatible, FALSE if not.  */
ساکن منطقی
validate_proto_after_old_defn (درخت newdecl, درخت newtype, درخت oldtype)
{
  درخت newargs, oldargs;
  صحیح i;

#تعریف_کرو انتہا_کا_ARGLIST(t) ((t) == void_type_گرہ)

  oldargs = TYPE_ACTUAL_ARG_TYPES (oldtype);
  newargs = TYPE_ARG_TYPES (newtype);
  i = 1;

  برائے (;;)
    {
      درخت oldargtype = درخت_قدر (oldargs);
      درخت newargtype = درخت_قدر (newargs);

      اگر (oldargtype == error_mark_گرہ || newargtype == error_mark_گرہ)
	واپس جھوٹ;

      oldargtype = (TYPE_ATOMIC (oldargtype)
		    ? c_build_qualified_type (TYPE_MAIN_VARIANT (oldargtype),
					      TYPE_QUAL_ATOMIC)
		    : TYPE_MAIN_VARIANT (oldargtype));
      newargtype = (TYPE_ATOMIC (newargtype)
		    ? c_build_qualified_type (TYPE_MAIN_VARIANT (newargtype),
					      TYPE_QUAL_ATOMIC)
		    : TYPE_MAIN_VARIANT (newargtype));

      اگر (انتہا_کا_ARGLIST (oldargtype) && انتہا_کا_ARGLIST (newargtype))
	توڑو;

      /* Reaching the end of just one list means the two decls don't
	 agree on the number of arguments.  */
      اگر (انتہا_کا_ARGLIST (oldargtype))
	{
	  error ("prototype for %q+D declares more arguments "
		 "than previous old-style definition", newdecl);
	  واپس جھوٹ;
	}
      ورنہ اگر (انتہا_کا_ARGLIST (newargtype))
	{
	  error ("prototype for %q+D declares fewer arguments "
		 "than previous old-style definition", newdecl);
	  واپس جھوٹ;
	}

      /* Type for passing arg must be consistent with that declared
	 for the arg.  */
      ورنہ اگر (!comptypes (oldargtype, newargtype))
	{
	  error ("prototype for %q+D declares argument %d"
		 " with incompatible type",
		 newdecl, i);
	  واپس جھوٹ;
	}

      oldargs = درخت_CHAIN (oldargs);
      newargs = درخت_CHAIN (newargs);
      i++;
    }

  /* If we get here, no errors were found, but do issue a warning
     for this poor-style construct.  */
  warning (0, "prototype for %q+D follows non-prototype definition",
	   newdecl);
  واپس سچ;
#تعریف_منسوخ انتہا_کا_ARGLIST
}

/* Subroutine of diagnose_mismatched_decls.  Report the location of DECL,
   first in a pair of mismatched declarations, using the diagnostic
   function DIAG.  */
ساکن خالی
locate_old_decl (درخت decl)
{
  اگر (درخت_رمز (decl) == FUNCTION_DECL
      && fndecl_built_اندر_p (decl)
      && !C_DECL_DECLARED_BUILTIN (decl))
    ;
  ورنہ اگر (DECL_INITIAL (decl))
    inform (داخلہ_location,
	    "previous definition of %q+D with type %qT",
	    decl, درخت_TYPE (decl));
  ورنہ اگر (C_DECL_IMPLICIT (decl))
    inform (داخلہ_location,
	    "previous implicit declaration of %q+D with type %qT",
	    decl, درخت_TYPE (decl));
  ورنہ
    inform (داخلہ_location,
	    "previous declaration of %q+D with type %qT",
	    decl, درخت_TYPE (decl));
}


/* Helper function.  For a tagged type, it finds the declaration
   for a visible tag declared in the same scope if such a
   declaration exists.  */
ساکن درخت
پچھلا_لیبل (درخت type)
{
  ساخت c_binding *b = تہی;
  درخت name = c_type_لیبل (type);

  اگر (name)
    b = I_لیبل_BINDING (name);

  اگر (b)
    b = b->shadowed;

  اگر (b && B_اندر_CURRENT_SCOPE (b))
    واپس b->decl;

  واپس NULL_درخت;
}

/* Subroutine to mark functions as versioned when using the attribute
   'target_version'.  */

ساکن خالی
maybe_mark_function_versioned (درخت decl)
{
  اگر (!DECL_FUNCTION_VERSIONED (decl))
    {
      /* Check if the name of the function has been overridden.  */
      اگر (DECL_ASSEMBLER_NAME_سیٹ_P (decl)
	  && IDENTIFIER_اشارہ_گر (DECL_ASSEMBLER_NAME (decl))[0] == '*')
	error_at (DECL_ماخذ_LOCATION (decl),
		  "cannot use function multiversioning on a renamed function");

      /* We need to insert function version now to make sure the correct
	 pre-mangled assembler name is recorded.  */
      cgraph_گرہ *گرہ = cgraph_گرہ::get_create (decl);

      اگر (!گرہ->function_نسخہ ())
	گرہ->داخل_کرو_new_function_نسخہ ();

      DECL_FUNCTION_VERSIONED (decl) = 1;

      درخت mangled_name
	= targetm.mangle_decl_assembler_name (decl, DECL_NAME (decl));
      سیٹ_DECL_ASSEMBLER_NAME (decl, mangled_name);
    }
}

/* Subroutine of duplicate_decls.  Compare NEWDECL to OLDDECL.
   Returns true if the caller should proceed to merge the two, false
   if OLDDECL should simply be discarded.  As a side effect, issues
   all necessary diagnostics for invalid or poor-style combinations.
   If it returns true, writes the types of NEWDECL and OLDDECL to
   *NEWTYPEP and *OLDTYPEP - these may have been adjusted from
   TREE_TYPE (NEWDECL, OLDDECL) respectively.  */

ساکن منطقی
diagnose_mismatched_decls (درخت newdecl, درخت olddecl,
			   درخت *newtypep, درخت *oldtypep)
{
  درخت newtype, oldtype;
  منطقی retval = سچ;

#تعریف_کرو DECL_EXTERN_INLINE(DECL) (DECL_DECLARED_INLINE_P (DECL)  \
				  && DECL_EXTERNAL (DECL))

  /* If we have error_mark_node for either decl or type, just discard
     the previous decl - we're in an error cascade already.  */
  اگر (olddecl == error_mark_گرہ || newdecl == error_mark_گرہ)
    واپس جھوٹ;
  *oldtypep = oldtype = درخت_TYPE (olddecl);
  *newtypep = newtype = درخت_TYPE (newdecl);
  اگر (oldtype == error_mark_گرہ || newtype == error_mark_گرہ)
    واپس جھوٹ;

  /* Two different categories of symbol altogether.  This is an error
     unless OLDDECL is a builtin.  OLDDECL will be discarded in any case.  */
  اگر (درخت_رمز (olddecl) != درخت_رمز (newdecl))
    {
      اگر (!(درخت_رمز (olddecl) == FUNCTION_DECL
	    && fndecl_built_اندر_p (olddecl)
	    && !C_DECL_DECLARED_BUILTIN (olddecl)))
	{
	  auto_diagnostic_گروہ d;
	  error ("%q+D redeclared as different kind of symbol", newdecl);
	  locate_old_decl (olddecl);
	}
      ورنہ اگر (درخت_عوامی (newdecl))
	warning (OPT_Wbuiltin_declaration_mismatch,
		 "built-in function %q+D declared as non-function",
		 newdecl);
      ورنہ
	warning (OPT_Wshadow, "declaration of %q+D shadows "
		 "a built-in function", newdecl);
      واپس جھوٹ;
    }

  /* Enumerators have no linkage, so may only be declared once in a
     given scope.  */
  اگر (درخت_رمز (olddecl) == CONST_DECL)
    {
      اگر (flag_isoc23
	  && TYPE_NAME (DECL_CONTEXT (newdecl))
	  && DECL_CONTEXT (newdecl) != DECL_CONTEXT (olddecl)
	  && TYPE_NAME (DECL_CONTEXT (newdecl)) == TYPE_NAME (DECL_CONTEXT (olddecl)))
	{
	  اگر (!simple_cst_equal (DECL_INITIAL (olddecl), DECL_INITIAL (newdecl)))
	    {
	      auto_diagnostic_گروہ d;
	      error ("conflicting redeclaration of enumerator %q+D", newdecl);
	      locate_old_decl (olddecl);
	    }
	}
      ورنہ
	{
	  auto_diagnostic_گروہ d;
	  error ("redeclaration of enumerator %q+D", newdecl);
	  locate_old_decl (olddecl);
	}
      واپس جھوٹ;
    }

  منطقی pedwarned = جھوٹ;
  منطقی warned = جھوٹ;
  منطقی enum_and_int_p = جھوٹ;
  auto_diagnostic_گروہ d;

  منطقی comptypes_نتیجہ = comptypes_check_enum_int (oldtype, newtype,
						    &enum_and_int_p);
  اگر (!comptypes_نتیجہ)
    {
      اگر (درخت_رمز (olddecl) == FUNCTION_DECL
	  && fndecl_built_اندر_p (olddecl, BUILT_اندر_معمول)
	  && !C_DECL_DECLARED_BUILTIN (olddecl))
	{
	  /* Accept "harmless" mismatches in function types such
	     as missing qualifiers or int vs long when they're the same
	     size.  However, diagnose return and argument types that are
	     incompatible according to language rules.  */
	  درخت mismatch_expect;
	  غیرعلامتی mismatch_argno;

	  درخت trytype = مطابقت_builtin_function_types (newtype, oldtype,
						       &mismatch_expect,
						       &mismatch_argno);

	  اگر (trytype && comptypes (newtype, trytype))
	    *oldtypep = oldtype = trytype;
	  ورنہ
	    {
	      /* If types don't match for a built-in, throw away the
		 built-in.  No point in calling locate_old_decl here, it
		 won't print anything.  */
	      ثابت حرف *سرخی = سرخی_for_builtin_fn (olddecl);
	      location_t loc = DECL_ماخذ_LOCATION (newdecl);
	      اگر (warning_at (loc, OPT_Wbuiltin_declaration_mismatch,
			      "conflicting types for built-in function %q+D; "
			      "expected %qT",
			      newdecl, oldtype)
		  && سرخی)
		{
		  /* Suggest the right header to include as the preferred
		     solution rather than the spelling of the declaration.  */
		  rich_location richloc (سطر_جدول, loc);
		  maybe_جوڑو_include_fixit (&richloc, سرخی, سچ);
		  inform (&richloc,
			  "%qD is declared in header %qs", olddecl, سرخی);
		}
	      واپس جھوٹ;
	    }

	  اگر (mismatch_expect && extra_warnings)
	    {
	      location_t newloc = DECL_ماخذ_LOCATION (newdecl);
	      منطقی warned = جھوٹ;
	      اگر (mismatch_argno)
		warned = warning_at (newloc, OPT_Wbuiltin_declaration_mismatch,
				     "mismatch in argument %u type of built-in "
				     "function %qD; expected %qT",
				     mismatch_argno, newdecl, mismatch_expect);
	      ورنہ
		warned = warning_at (newloc, OPT_Wbuiltin_declaration_mismatch,
				     "mismatch in return type of built-in "
				     "function %qD; expected %qT",
				     newdecl, mismatch_expect);
	      ثابت حرف *سرخی = سرخی_for_builtin_fn (olddecl);
	      اگر (warned && سرخی)
		{
		  rich_location richloc (سطر_جدول, newloc);
		  maybe_جوڑو_include_fixit (&richloc, سرخی, سچ);
		  inform (&richloc,
			  "%qD is declared in header %qs", olddecl, سرخی);
		}
	    }
	}
      ورنہ اگر (درخت_رمز (olddecl) == FUNCTION_DECL
	       && DECL_IS_UNDECLARED_BUILTIN (olddecl))
	{
	  /* A conflicting function declaration for a predeclared
	     function that isn't actually built in.  Objective C uses
	     these.  The new declaration silently overrides everything
	     but the volatility (i.e. noreturn) indication.  See also
	     below.  FIXME: Make Objective C use normal builtins.  */
	  درخت_THIS_VOLATILE (newdecl) |= درخت_THIS_VOLATILE (olddecl);
	  واپس جھوٹ;
	}
      /* Permit void foo (...) to match int foo (...) if the latter is
	 the definition and implicit int was used.  See
	 c-torture/compile/920625-2.c.  */
      ورنہ اگر (درخت_رمز (newdecl) == FUNCTION_DECL && DECL_INITIAL (newdecl)
	       && TYPE_MAIN_VARIANT (درخت_TYPE (oldtype)) == void_type_گرہ
	       && TYPE_MAIN_VARIANT (درخت_TYPE (newtype)) == integer_type_گرہ
	       && C_FUNCTION_IMPLICIT_INT (newdecl) && !DECL_INITIAL (olddecl))
	{
	  pedwarned = pedwarn (داخلہ_location, 0,
			       "conflicting types for %q+D", newdecl);
	  /* Make sure we keep void as the return type.  */
	  درخت_TYPE (newdecl) = *newtypep = newtype = oldtype;
	  C_FUNCTION_IMPLICIT_INT (newdecl) = 0;
	}
      /* Permit void foo (...) to match an earlier call to foo (...) with
	 no declared type (thus, implicitly int).  */
      ورنہ اگر (درخت_رمز (newdecl) == FUNCTION_DECL
	       && TYPE_MAIN_VARIANT (درخت_TYPE (newtype)) == void_type_گرہ
	       && TYPE_MAIN_VARIANT (درخت_TYPE (oldtype)) == integer_type_گرہ
	       && C_DECL_IMPLICIT (olddecl) && !DECL_INITIAL (olddecl))
	{
	  pedwarned = pedwarn (داخلہ_location, 0,
			       "conflicting types for %q+D; have %qT",
			       newdecl, newtype);
	  /* Make sure we keep void as the return type.  */
	  درخت_TYPE (olddecl) = *oldtypep = oldtype = newtype;
	}
      ورنہ
	{
	  صحیح new_quals = TYPE_QUALS (newtype);
	  صحیح old_quals = TYPE_QUALS (oldtype);

	  اگر (new_quals != old_quals)
	    {
	      addr_space_t new_addr = DECODE_QUAL_ADDR_SPACE (new_quals);
	      addr_space_t old_addr = DECODE_QUAL_ADDR_SPACE (old_quals);
	      اگر (new_addr != old_addr)
		{
		  اگر (ADDR_SPACE_GENERIC_P (new_addr))
		    error ("conflicting named address spaces (generic vs %s) "
			   "for %q+D",
			   c_addr_space_name (old_addr), newdecl);
		  ورنہ اگر (ADDR_SPACE_GENERIC_P (old_addr))
		    error ("conflicting named address spaces (%s vs generic) "
			   "for %q+D",
			   c_addr_space_name (new_addr), newdecl);
		  ورنہ
		    error ("conflicting named address spaces (%s vs %s) "
			   "for %q+D",
			   c_addr_space_name (new_addr),
			   c_addr_space_name (old_addr),
			   newdecl);
		}

	      اگر (CLEAR_QUAL_ADDR_SPACE (new_quals)
		  != CLEAR_QUAL_ADDR_SPACE (old_quals))
		error ("conflicting type qualifiers for %q+D", newdecl);
	    }
	  ورنہ
	    {
	      اگر (درخت_رمز (olddecl) == FUNCTION_DECL)
		{
		  درخت attrs = TYPE_اوصاف (درخت_TYPE (olddecl));
		  اگر (attrs && !TYPE_اوصاف (درخت_TYPE (newdecl)))
		    {
		      /* Similar to the C++ front-end, for FUNCTION_DECL,
			 if OLDDECL has attributes and NEWDECL doesn't,
			 try the type with OLDDECL attributes.  */
		      درخت rettype = درخت_TYPE (newtype);
		      درخت tryargs = TYPE_ARG_TYPES (newtype);
		      درخت trytype = c_build_function_type (rettype,
							    tryargs);
		      trytype = c_build_type_attribute_variant (trytype,
								attrs);
		      اگر (comptypes (oldtype, trytype))
			{
			  *newtypep = newtype = trytype;
			  comptypes_نتیجہ = سچ;
			}
		    }
		}

	      اگر (!comptypes_نتیجہ)
		error ("conflicting types for %q+D; have %qT", newdecl,
		       newtype);
	    }
	  اگر (!comptypes_نتیجہ)
	    {
	      diagnose_arglist_conflict (newdecl, olddecl, newtype,
					 oldtype);
	      locate_old_decl (olddecl);
	      واپس جھوٹ;
	    }
	}
    }
  /* Warn about enum/integer type mismatches.  They are compatible types
     (C23 6.7.2.2/5), but may pose portability problems.  */
  ورنہ اگر (enum_and_int_p
	   && درخت_رمز (newdecl) != TYPE_DECL
	   /* Don't warn about acc_on_device built-in redeclaration,
	      the built-in is declared with int rather than enum because
	      the enum isn't intrinsic.  */
	   && !(درخت_رمز (olddecl) == FUNCTION_DECL
		&& fndecl_built_اندر_p (olddecl, BUILT_اندر_ACC_ON_DEVICE)
		&& !C_DECL_DECLARED_BUILTIN (olddecl)))
    warned = warning_at (DECL_ماخذ_LOCATION (newdecl),
			 OPT_Wenum_int_mismatch,
			 "conflicting types for %q+D due to enum/integer "
			 "mismatch; have %qT", newdecl, newtype);

  /* Redeclaration of a type is a constraint violation (6.7.2.3p1),
     but silently ignore the redeclaration if either is in a system
     header.  (Conflicting redeclarations were handled above.)  This
     is allowed for C11 if the types are the same, not just
     compatible.  */
  اگر (درخت_رمز (newdecl) == TYPE_DECL)
    {
      اگر (!comptypes_same_p (oldtype, newtype))
	{
	  error ("redefinition of typedef %q+D with different type", newdecl);
	  locate_old_decl (olddecl);
	  واپس جھوٹ;
	}

      اگر (DECL_اندر_SYSTEM_سرخی (newdecl)
	  || DECL_اندر_SYSTEM_سرخی (olddecl)
	  || warning_suppressed_p (newdecl, OPT_Wpedantic)
	  || warning_suppressed_p (olddecl, OPT_Wpedantic))
	واپس سچ;  /* Allow OLDDECL to continue in use.  */

      اگر (c_type_variably_modified_p (newtype))
	{
	  error ("redefinition of typedef %q+D with variably modified type",
		 newdecl);
	  locate_old_decl (olddecl);
	}
      ورنہ اگر (pedwarn_c99 (داخلہ_location, OPT_Wpedantic,
			    "redefinition of typedef %q+D", newdecl))
	locate_old_decl (olddecl);

      واپس سچ;
    }

  /* Function declarations can either be 'static' or 'extern' (no
     qualifier is equivalent to 'extern' - C99 6.2.2p5) and therefore
     can never conflict with each other on account of linkage
     (6.2.2p4).  Multiple definitions are not allowed (6.9p3,5) but
     gnu89 mode permits two definitions if one is 'extern inline' and
     one is not.  The non- extern-inline definition supersedes the
     extern-inline definition.  */

  ورنہ اگر (درخت_رمز (newdecl) == FUNCTION_DECL)
    {
      /* If you declare a built-in function name as static, or
	 define the built-in with an old-style definition (so we
	 can't validate the argument list) the built-in definition is
	 overridden, but optionally warn this was a bad choice of name.  */
      اگر (fndecl_built_اندر_p (olddecl)
	  && !C_DECL_DECLARED_BUILTIN (olddecl))
	{
	  اگر (!درخت_عوامی (newdecl)
	      || (DECL_INITIAL (newdecl)
		  && !prototype_p (درخت_TYPE (newdecl))))
	    {
	      warning_at (DECL_ماخذ_LOCATION (newdecl),
			  OPT_Wshadow, "declaration of %qD shadows "
			  "a built-in function", newdecl);
	      /* Discard the old built-in function.  */
	      واپس جھوٹ;
	    }

	  اگر (!prototype_p (درخت_TYPE (newdecl)))
	    {
	      /* Set for built-ins that take no arguments.  */
	      منطقی func_void_دلائل = جھوٹ;
	      اگر (درخت at = TYPE_ARG_TYPES (oldtype))
		func_void_دلائل = VOID_TYPE_P (درخت_قدر (at));

	      اگر (extra_warnings && !func_void_دلائل)
		warning_at (DECL_ماخذ_LOCATION (newdecl),
			    OPT_Wbuiltin_declaration_mismatch,
			    "declaration of built-in function %qD without "
			    "a prototype; expected %qT",
			    newdecl, درخت_TYPE (olddecl));
	    }
	}

      اگر (DECL_INITIAL (newdecl))
	{
	  اگر (DECL_INITIAL (olddecl))
	    {
	      /* If the new declaration isn't overriding an extern inline
		 reject the new decl. In c99, no overriding is allowed
		 in the same translation unit.  */
	      اگر (!DECL_EXTERN_INLINE (olddecl)
		  || DECL_EXTERN_INLINE (newdecl)
		  || (!flag_gnu89_inline
		      && (!DECL_DECLARED_INLINE_P (olddecl)
			  || !lookup_attribute ("gnu_inline",
						DECL_اوصاف (olddecl)))
		      && (!DECL_DECLARED_INLINE_P (newdecl)
			  || !lookup_attribute ("gnu_inline",
						DECL_اوصاف (newdecl)))))
		{
		  auto_diagnostic_گروہ d;
		  error ("redefinition of %q+D", newdecl);
		  locate_old_decl (olddecl);
		  واپس جھوٹ;
		}
	    }
	}
      /* If we have a prototype after an old-style function definition,
	 the argument types must be checked specially.  */
      ورنہ اگر (DECL_INITIAL (olddecl)
	       && !prototype_p (oldtype) && prototype_p (newtype)
	       && TYPE_ACTUAL_ARG_TYPES (oldtype))
	{
	  auto_diagnostic_گروہ d;
	  اگر (!validate_proto_after_old_defn (newdecl, newtype, oldtype))
	    {
	      locate_old_decl (olddecl);
	      واپس جھوٹ;
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
      اگر (درخت_عوامی (olddecl) && !درخت_عوامی (newdecl))
	{
	  /* Two exceptions to the rule.  If olddecl is an extern
	     inline, or a predeclared function that isn't actually
	     built in, newdecl silently overrides olddecl.  The latter
	     occur only in Objective C; see also above.  (FIXME: Make
	     Objective C use normal builtins.)  */
	  اگر (!DECL_IS_UNDECLARED_BUILTIN (olddecl)
	      && !DECL_EXTERN_INLINE (olddecl))
	    {
	      auto_diagnostic_گروہ d;
	      error ("static declaration of %q+D follows "
		     "non-static declaration", newdecl);
	      locate_old_decl (olddecl);
	    }
	  واپس جھوٹ;
	}
      ورنہ اگر (درخت_عوامی (newdecl) && !درخت_عوامی (olddecl))
	{
	  اگر (DECL_CONTEXT (olddecl))
	    {
	      auto_diagnostic_گروہ d;
	      error ("non-static declaration of %q+D follows "
		     "static declaration", newdecl);
	      locate_old_decl (olddecl);
	      واپس جھوٹ;
	    }
	  ورنہ اگر (warn_traditional)
	    {
	      warned |= warning (OPT_Wtraditional,
				 "non-static declaration of %q+D "
				 "follows static declaration", newdecl);
	    }
	}

      /* Make sure gnu_inline attribute is either not present, or
	 present on all inline decls.  */
      اگر (DECL_DECLARED_INLINE_P (olddecl)
	  && DECL_DECLARED_INLINE_P (newdecl))
	{
	  منطقی newa = lookup_attribute ("gnu_inline",
					DECL_اوصاف (newdecl)) != تہی;
	  منطقی olda = lookup_attribute ("gnu_inline",
					DECL_اوصاف (olddecl)) != تہی;
	  اگر (newa != olda)
	    {
	      auto_diagnostic_گروہ d;
	      error_at (داخلہ_location, "%<gnu_inline%> attribute present on %q+D",
			newa ? newdecl : olddecl);
	      error_at (DECL_ماخذ_LOCATION (newa ? olddecl : newdecl),
			"but not here");
	    }
	}
      /* Check if these are unmergeable overlapping FMV declarations.  */
      اگر (!ہدف_HAS_FMV_ہدف_ATTRIBUTE
	  && diagnose_versioned_decls (olddecl, newdecl))
	واپس جھوٹ;
    }
  ورنہ اگر (VAR_P (newdecl))
    {
      /* Only variables can be thread-local, and all declarations must
	 agree on this property.  */
      اگر (C_DECL_THREADPRIVATE_P (olddecl) && !DECL_THREAD_LOCAL_P (newdecl))
	{
	  /* Nothing to check.  Since OLDDECL is marked threadprivate
	     and NEWDECL does not have a thread-local attribute, we
	     will merge the threadprivate attribute into NEWDECL.  */
	  ;
	}
      ورنہ اگر (DECL_THREAD_LOCAL_P (newdecl) != DECL_THREAD_LOCAL_P (olddecl))
	{
	  auto_diagnostic_گروہ d;
	  اگر (DECL_THREAD_LOCAL_P (newdecl))
	    error ("thread-local declaration of %q+D follows "
		   "non-thread-local declaration", newdecl);
	  ورنہ
	    error ("non-thread-local declaration of %q+D follows "
		   "thread-local declaration", newdecl);

	  locate_old_decl (olddecl);
	  واپس جھوٹ;
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
      اگر ((DECL_INITIAL (newdecl) && DECL_INITIAL (olddecl))
	  || (flag_isoc23
	      && DECL_THREAD_LOCAL_P (newdecl)
	      && !DECL_EXTERNAL (newdecl)
	      && !DECL_EXTERNAL (olddecl)))
	{
	  auto_diagnostic_گروہ d;
	  error ("redefinition of %q+D", newdecl);
	  locate_old_decl (olddecl);
	  واپس جھوٹ;
	}

      /* Objects declared at file scope: if the first declaration had
	 external linkage (even if it was an external reference) the
	 second must have external linkage as well, or the behavior is
	 undefined.  If the first declaration had internal linkage, then
	 the second must too, or else be an external reference (in which
	 case the composite declaration still has internal linkage).
	 As for function declarations, we warn about the static-then-
	 extern case only for -Wtraditional.  See generally 6.2.2p3-5,7.  */
      اگر (DECL_FILE_SCOPE_P (newdecl)
	  && درخت_عوامی (newdecl) != درخت_عوامی (olddecl))
	{
	  اگر (DECL_EXTERNAL (newdecl))
	    {
	      اگر (!DECL_FILE_SCOPE_P (olddecl))
		{
		  auto_diagnostic_گروہ d;
		  error ("extern declaration of %q+D follows "
			 "declaration with no linkage", newdecl);
		  locate_old_decl (olddecl);
		  واپس جھوٹ;
		}
	      ورنہ اگر (warn_traditional)
		{
		  warned |= warning (OPT_Wtraditional,
				     "non-static declaration of %q+D "
				     "follows static declaration", newdecl);
		}
	    }
	  ورنہ
	    {
	      auto_diagnostic_گروہ d;
	      اگر (درخت_عوامی (newdecl))
		error ("non-static declaration of %q+D follows "
		       "static declaration", newdecl);
	      ورنہ
		error ("static declaration of %q+D follows "
		       "non-static declaration", newdecl);

	      locate_old_decl (olddecl);
	      واپس جھوٹ;
	    }
	}
      /* Two objects with the same name declared at the same block
	 scope must both be external references (6.7p3).  */
      ورنہ اگر (!DECL_FILE_SCOPE_P (newdecl))
	{
	  اگر (DECL_EXTERNAL (newdecl))
	    {
	      /* Extern with initializer at block scope, which will
		 already have received an error.  */
	    }
	  ورنہ اگر (DECL_EXTERNAL (olddecl))
	    {
	      auto_diagnostic_گروہ d;
	      error ("declaration of %q+D with no linkage follows "
		     "extern declaration", newdecl);
	      locate_old_decl (olddecl);
	    }
	  ورنہ
	    {
	      auto_diagnostic_گروہ d;
	      error ("redeclaration of %q+D with no linkage", newdecl);
	      locate_old_decl (olddecl);
	    }

	  واپس جھوٹ;
	}

      /* C++ does not permit a decl to appear multiple times at file
	 scope.  */
      اگر (warn_cxx_compat
	  && DECL_FILE_SCOPE_P (newdecl)
	  && !DECL_EXTERNAL (newdecl)
	  && !DECL_EXTERNAL (olddecl))
	warned |= warning_at (DECL_ماخذ_LOCATION (newdecl),
			      OPT_Wc___compat,
			      "duplicate declaration of %qD is "
			      "invalid in C++", newdecl);
    }

  /* warnings */
  /* All decls must agree on a visibility.  */
  اگر (رمز_شامل_ہے_STRUCT (درخت_رمز (newdecl), TS_DECL_WITH_VIS)
      && DECL_VISIBILITY_SPECIFIED (newdecl) && DECL_VISIBILITY_SPECIFIED (olddecl)
      && DECL_VISIBILITY (newdecl) != DECL_VISIBILITY (olddecl))
    {
      warned |= warning (0, "redeclaration of %q+D with different visibility "
			 "(old visibility preserved)", newdecl);
    }

  اگر (درخت_رمز (newdecl) == FUNCTION_DECL)
    warned |= diagnose_mismatched_اوصاف (olddecl, newdecl);
  ورنہ /* PARM_DECL, VAR_DECL */
    {
      /* Redeclaration of a parameter is a constraint violation (this is
	 not explicitly stated, but follows from C99 6.7p3 [no more than
	 one declaration of the same identifier with no linkage in the
	 same scope, except type tags] and 6.2.2p6 [parameters have no
	 linkage]).  We must check for a forward parameter declaration,
	 indicated by TREE_ASM_WRITTEN on the old declaration - this is
	 an extension, the mandatory diagnostic for which is handled by
	 mark_forward_parm_decls.  */

      اگر (درخت_رمز (newdecl) == PARM_DECL
	  && (!درخت_ASM_WRITTEN (olddecl) || درخت_ASM_WRITTEN (newdecl)))
	{
	  auto_diagnostic_گروہ d;
	  error ("redefinition of parameter %q+D", newdecl);
	  locate_old_decl (olddecl);
	  واپس جھوٹ;
	}
    }

  /* Optional warning for completely redundant decls.  */
  اگر (!warned && !pedwarned
      && warn_redundant_decls
      /* Don't warn about a function declaration followed by a
	 definition.  */
      && !(درخت_رمز (newdecl) == FUNCTION_DECL
	   && DECL_INITIAL (newdecl) && !DECL_INITIAL (olddecl))
      /* Don't warn about redundant redeclarations of builtins.  */
      && !(درخت_رمز (newdecl) == FUNCTION_DECL
	   && !fndecl_built_اندر_p (newdecl)
	   && fndecl_built_اندر_p (olddecl)
	   && !C_DECL_DECLARED_BUILTIN (olddecl))
      /* Don't warn about an extern followed by a definition.  */
      && !(DECL_EXTERNAL (olddecl) && !DECL_EXTERNAL (newdecl))
      /* Don't warn about forward parameter decls.  */
      && !(درخت_رمز (newdecl) == PARM_DECL
	   && درخت_ASM_WRITTEN (olddecl) && !درخت_ASM_WRITTEN (newdecl))
      /* Don't warn about a variable definition following a declaration.  */
      && !(VAR_P (newdecl)
	   && DECL_INITIAL (newdecl) && !DECL_INITIAL (olddecl)))
    {
      warned = warning (OPT_Wredundant_decls, "redundant redeclaration of %q+D",
			newdecl);
    }

  /* Report location of previous decl/defn.  */
  اگر (warned || pedwarned)
    locate_old_decl (olddecl);

#تعریف_منسوخ DECL_EXTERN_INLINE

  واپس retval;
}

/* Subroutine of duplicate_decls.  NEWDECL has been found to be
   consistent with OLDDECL, but carries new information.  Merge the
   new information into OLDDECL.  This function issues no
   diagnostics.  */

ساکن خالی
ملاؤ_decls (درخت newdecl, درخت olddecl, درخت newtype, درخت oldtype)
{
  منطقی new_is_definition = (درخت_رمز (newdecl) == FUNCTION_DECL
			    && DECL_INITIAL (newdecl) != NULL_درخت);
  منطقی new_is_prototype = (درخت_رمز (newdecl) == FUNCTION_DECL
			   && prototype_p (درخت_TYPE (newdecl)));
  منطقی old_is_prototype = (درخت_رمز (olddecl) == FUNCTION_DECL
			   && prototype_p (درخت_TYPE (olddecl)));

  /* For real parm decl following a forward decl, rechain the old decl
     in its new location and clear TREE_ASM_WRITTEN (it's not a
     forward decl anymore).  */
  اگر (درخت_رمز (newdecl) == PARM_DECL
      && درخت_ASM_WRITTEN (olddecl) && !درخت_ASM_WRITTEN (newdecl))
    {
      ساخت c_binding *b, **یہاں;

      برائے (یہاں = &current_scope->bindings; *یہاں; یہاں = &(*یہاں)->پچھلا)
	اگر ((*یہاں)->decl == olddecl)
	  جاؤ ملا;
      gcc_unreachable ();

    ملا:
      b = *یہاں;
      *یہاں = b->پچھلا;
      b->پچھلا = current_scope->bindings;
      current_scope->bindings = b;

      درخت_ASM_WRITTEN (olddecl) = 0;
    }

  DECL_اوصاف (newdecl)
    = targetm.ملاؤ_decl_اوصاف (olddecl, newdecl);

  /* For typedefs use the old type, as the new type's DECL_NAME points
     at newdecl, which will be ggc_freed.  */
  اگر (درخت_رمز (newdecl) == TYPE_DECL)
    {
      /* But NEWTYPE might have an attribute, honor that.  */
      درخت tem = newtype;
      newtype = oldtype;

      اگر (TYPE_USER_ALIGN (tem))
	{
	  اگر (TYPE_ALIGN (tem) > TYPE_ALIGN (newtype))
	    سیٹ_TYPE_ALIGN (newtype, TYPE_ALIGN (tem));
	  TYPE_USER_ALIGN (newtype) = سچ;
	}

      /* And remove the new type from the variants list.  */
      اگر (TYPE_NAME (درخت_TYPE (newdecl)) == newdecl)
	{
	  درخت remove = درخت_TYPE (newdecl);
	  اگر (TYPE_MAIN_VARIANT (remove) == remove)
	    {
	      gcc_assert (TYPE_اگلا_VARIANT (remove) == NULL_درخت);
	      /* If remove is the main variant, no need to remove that
		 from the list.  One of the DECL_ORIGINAL_TYPE
		 variants, e.g. created for aligned attribute, might still
		 refer to the newdecl TYPE_DECL though, so remove that one
		 in that case.  */
	      اگر (DECL_ORIGINAL_TYPE (newdecl)
		  && DECL_ORIGINAL_TYPE (newdecl) != remove)
		برائے (درخت t = TYPE_MAIN_VARIANT (DECL_ORIGINAL_TYPE (newdecl));
		     t; t = TYPE_MAIN_VARIANT (t))
		  اگر (TYPE_NAME (TYPE_اگلا_VARIANT (t)) == newdecl)
		    {
		      TYPE_اگلا_VARIANT (t)
			= TYPE_اگلا_VARIANT (TYPE_اگلا_VARIANT (t));
		      توڑو;
		    }
	    }
	  ورنہ
	    برائے (درخت t = TYPE_MAIN_VARIANT (remove); ;
		 t = TYPE_اگلا_VARIANT (t))
	      اگر (TYPE_اگلا_VARIANT (t) == remove)
		{
		  TYPE_اگلا_VARIANT (t) = TYPE_اگلا_VARIANT (remove);
		  توڑو;
		}
	}

      /* Make sure we refer to the same type as the olddecl.  */
      DECL_ORIGINAL_TYPE (newdecl) = DECL_ORIGINAL_TYPE (olddecl);
    }

  /* Merge the data types specified in the two decls.  */
  درخت_TYPE (newdecl)
    = درخت_TYPE (olddecl)
    = مرکب_type (newtype, oldtype);

  /* Lay the type out, unless already done.  */
  اگر (!comptypes (oldtype, درخت_TYPE (newdecl)))
    {
      اگر (درخت_TYPE (newdecl) != error_mark_گرہ)
	layout_type (درخت_TYPE (newdecl));
      اگر (درخت_رمز (newdecl) != FUNCTION_DECL
	  && درخت_رمز (newdecl) != TYPE_DECL
	  && درخت_رمز (newdecl) != CONST_DECL)
	layout_decl (newdecl, 0);
    }
  ورنہ
    {
      /* Since the type is OLDDECL's, make OLDDECL's size go with.  */
      DECL_سائز (newdecl) = DECL_سائز (olddecl);
      DECL_سائز_UNIT (newdecl) = DECL_سائز_UNIT (olddecl);
      سیٹ_DECL_منوال (newdecl, DECL_منوال (olddecl));
      اگر (DECL_ALIGN (olddecl) > DECL_ALIGN (newdecl))
	{
	  سیٹ_DECL_ALIGN (newdecl, DECL_ALIGN (olddecl));
	  DECL_USER_ALIGN (newdecl) |= DECL_USER_ALIGN (olddecl);
	}
      ورنہ اگر (DECL_ALIGN (olddecl) == DECL_ALIGN (newdecl)
	       && DECL_USER_ALIGN (olddecl) != DECL_USER_ALIGN (newdecl))
	DECL_USER_ALIGN (newdecl) = 1;
      اگر (DECL_WARN_IF_NOT_ALIGN (olddecl)
	  > DECL_WARN_IF_NOT_ALIGN (newdecl))
	سیٹ_DECL_WARN_IF_NOT_ALIGN (newdecl,
				    DECL_WARN_IF_NOT_ALIGN (olddecl));
    }

  /* Keep the old rtl since we can safely use it.  */
  اگر (HAS_RTL_P (olddecl))
    COPY_DECL_RTL (olddecl, newdecl);

  /* Merge the type qualifiers.  */
  اگر (درخت_READONLY (newdecl))
    درخت_READONLY (olddecl) = 1;

  اگر (درخت_THIS_VOLATILE (newdecl))
    درخت_THIS_VOLATILE (olddecl) = 1;

  /* Merge deprecatedness.  */
  اگر (درخت_DEPRECATED (newdecl))
    درخت_DEPRECATED (olddecl) = 1;

  /* Merge unavailability.  */
  اگر (درخت_UNAVAILABLE (newdecl))
    درخت_UNAVAILABLE (olddecl) = 1;

  /* If a decl is in a system header and the other isn't, keep the one on the
     system header. Otherwise, keep source location of definition rather than
     declaration and of prototype rather than non-prototype unless that
     prototype is built-in.  */
  اگر (HAS_DECL_ASSEMBLER_NAME_P (olddecl)
      && DECL_اندر_SYSTEM_سرخی (olddecl)
      && !DECL_اندر_SYSTEM_سرخی (newdecl) )
    DECL_ماخذ_LOCATION (newdecl) = DECL_ماخذ_LOCATION (olddecl);
  ورنہ اگر (HAS_DECL_ASSEMBLER_NAME_P (olddecl)
	   && DECL_اندر_SYSTEM_سرخی (newdecl)
	   && !DECL_اندر_SYSTEM_سرخی (olddecl))
    DECL_ماخذ_LOCATION (olddecl) = DECL_ماخذ_LOCATION (newdecl);
  ورنہ اگر ((DECL_INITIAL (newdecl) == NULL_درخت
	    && DECL_INITIAL (olddecl) != NULL_درخت)
	   || (old_is_prototype && !new_is_prototype
	       && !C_DECL_BUILTIN_PROTOTYPE (olddecl)))
    DECL_ماخذ_LOCATION (newdecl) = DECL_ماخذ_LOCATION (olddecl);

  /* Merge the initialization information.  */
   اگر (DECL_INITIAL (newdecl) == NULL_درخت)
    DECL_INITIAL (newdecl) = DECL_INITIAL (olddecl);

  /* Merge 'constexpr' information.  */
  اگر (VAR_P (olddecl) && VAR_P (newdecl))
    {
      اگر (C_DECL_DECLARED_CONSTEXPR (olddecl))
	C_DECL_DECLARED_CONSTEXPR (newdecl) = 1;
      ورنہ اگر (C_DECL_DECLARED_CONSTEXPR (newdecl))
	C_DECL_DECLARED_CONSTEXPR (olddecl) = 1;
    }

  /* Merge the threadprivate attribute.  */
  اگر (VAR_P (olddecl) && C_DECL_THREADPRIVATE_P (olddecl))
    C_DECL_THREADPRIVATE_P (newdecl) = 1;

  اگر (HAS_DECL_ASSEMBLER_NAME_P (olddecl))
    {
      /* Copy the assembler name.
	 Currently, it can only be defined in the prototype.  */
      COPY_DECL_ASSEMBLER_NAME (olddecl, newdecl);

      /* Use visibility of whichever declaration had it specified */
      اگر (DECL_VISIBILITY_SPECIFIED (olddecl))
	{
	  DECL_VISIBILITY (newdecl) = DECL_VISIBILITY (olddecl);
	  DECL_VISIBILITY_SPECIFIED (newdecl) = 1;
	}

      اگر (درخت_رمز (newdecl) == FUNCTION_DECL)
	{
	  DECL_STATIC_CONSTRUCTOR(newdecl) |= DECL_STATIC_CONSTRUCTOR(olddecl);
	  DECL_STATIC_DESTRUCTOR (newdecl) |= DECL_STATIC_DESTRUCTOR (olddecl);
	  DECL_NO_حد_بندی_ڈھیر (newdecl) |= DECL_NO_حد_بندی_ڈھیر (olddecl);
	  DECL_NO_INSTRUMENT_FUNCTION_اندراج_EXIT (newdecl)
	    |= DECL_NO_INSTRUMENT_FUNCTION_اندراج_EXIT (olddecl);
	  درخت_THIS_VOLATILE (newdecl) |= درخت_THIS_VOLATILE (olddecl);
	  DECL_IS_MALLOC (newdecl) |= DECL_IS_MALLOC (olddecl);
	  اگر (DECL_IS_OPERATOR_NEW_P (olddecl))
	    DECL_سیٹ_IS_OPERATOR_NEW (newdecl, سچ);
	  اگر (DECL_IS_OPERATOR_DELETE_P (olddecl))
	    DECL_سیٹ_IS_OPERATOR_DELETE (newdecl, سچ);
	  درخت_READONLY (newdecl) |= درخت_READONLY (olddecl);
	  DECL_خالص_P (newdecl) |= DECL_خالص_P (olddecl);
	  DECL_IS_NOVOPS (newdecl) |= DECL_IS_NOVOPS (olddecl);
	}

      /* Merge the storage class information.  */
      ملاؤ_weak (newdecl, olddecl);

      /* For functions, static overrides non-static.  */
      اگر (درخت_رمز (newdecl) == FUNCTION_DECL)
	{
	  درخت_عوامی (newdecl) &= درخت_عوامی (olddecl);
	  /* This is since we don't automatically
	     copy the attributes of NEWDECL into OLDDECL.  */
	  درخت_عوامی (olddecl) = درخت_عوامی (newdecl);
	  /* If this clears `static', clear it in the identifier too.  */
	  اگر (!درخت_عوامی (olddecl))
	    درخت_عوامی (DECL_NAME (olddecl)) = 0;
	}
    }

  /* In c99, 'extern' declaration before (or after) 'inline' means this
     function is not DECL_EXTERNAL, unless 'gnu_inline' attribute
     is present.  */
  اگر (درخت_رمز (newdecl) == FUNCTION_DECL
      && !flag_gnu89_inline
      && (DECL_DECLARED_INLINE_P (newdecl)
	  || DECL_DECLARED_INLINE_P (olddecl))
      && (!DECL_DECLARED_INLINE_P (newdecl)
	  || !DECL_DECLARED_INLINE_P (olddecl)
	  || !DECL_EXTERNAL (olddecl))
      && DECL_EXTERNAL (newdecl)
      && !lookup_attribute ("gnu_inline", DECL_اوصاف (newdecl))
      && !current_function_decl)
    DECL_EXTERNAL (newdecl) = 0;

  /* An inline definition following a static declaration is not
     DECL_EXTERNAL.  */
  اگر (new_is_definition
      && (DECL_DECLARED_INLINE_P (newdecl)
	  || DECL_DECLARED_INLINE_P (olddecl))
      && !درخت_عوامی (olddecl))
    DECL_EXTERNAL (newdecl) = 0;

  اگر (DECL_EXTERNAL (newdecl))
    {
      درخت_STATIC (newdecl) = درخت_STATIC (olddecl);
      DECL_EXTERNAL (newdecl) = DECL_EXTERNAL (olddecl);

      /* An extern decl does not override previous storage class.  */
      درخت_عوامی (newdecl) = درخت_عوامی (olddecl);
      اگر (!DECL_EXTERNAL (newdecl))
	{
	  DECL_CONTEXT (newdecl) = DECL_CONTEXT (olddecl);
	  DECL_COMMON (newdecl) = DECL_COMMON (olddecl);
	}
    }
  ورنہ
    {
      درخت_STATIC (olddecl) = درخت_STATIC (newdecl);
      درخت_عوامی (olddecl) = درخت_عوامی (newdecl);
    }

  اگر (درخت_رمز (newdecl) == FUNCTION_DECL)
    {
      اگر (DECL_FUNCTION_VERSIONED (olddecl)
	  || DECL_FUNCTION_VERSIONED (newdecl))
	{
	  maybe_mark_function_versioned (olddecl);
	  maybe_mark_function_versioned (newdecl);
	}
      /* If we're redefining a function previously defined as extern
	 inline, make sure we emit debug info for the inline before we
	 throw it away, in case it was inlined into a function that
	 hasn't been written out yet.  */
      اگر (new_is_definition && DECL_INITIAL (olddecl))
	/* The new defn must not be inline.  */
	DECL_UNINLINABLE (newdecl) = 1;
      ورنہ
	{
	  /* If either decl says `inline', this fn is inline, unless
	     its definition was passed already.  */
	  اگر (DECL_DECLARED_INLINE_P (newdecl)
	      || DECL_DECLARED_INLINE_P (olddecl))
	    DECL_DECLARED_INLINE_P (newdecl) = 1;

	  DECL_UNINLINABLE (newdecl) = DECL_UNINLINABLE (olddecl)
	    = (DECL_UNINLINABLE (newdecl) || DECL_UNINLINABLE (olddecl));

	  DECL_DISREGARD_INLINE_LIMITS (newdecl)
	    = DECL_DISREGARD_INLINE_LIMITS (olddecl)
	    = (DECL_DISREGARD_INLINE_LIMITS (newdecl)
	       || DECL_DISREGARD_INLINE_LIMITS (olddecl));
	}

      اگر (fndecl_built_اندر_p (olddecl))
	{
	  /* If redeclaring a builtin function, it stays built in.
	     But it gets tagged as having been declared.  */
	  copy_decl_built_اندر_function (newdecl, olddecl);
	  C_DECL_DECLARED_BUILTIN (newdecl) = 1;
	  اگر (new_is_prototype)
	    {
	      C_DECL_BUILTIN_PROTOTYPE (newdecl) = 0;
	      اگر (DECL_BUILT_اندر_CLASS (newdecl) == BUILT_اندر_معمول)
		{
		  شمار built_اندر_function fncode = DECL_FUNCTION_رمز (newdecl);
		  انتخاب (fncode)
		    {
		      /* If a compatible prototype of these builtin functions
			 is seen, assume the runtime implements it with the
			 expected semantics.  */
		    حالت BUILT_اندر_STPCPY:
		      اگر (builtin_decl_explicit_p (fncode))
			سیٹ_builtin_decl_implicit_p (fncode, سچ);
		      توڑو;
		    طےشدہ:
		      اگر (builtin_decl_explicit_p (fncode))
			سیٹ_builtin_decl_declared_p (fncode, سچ);
		      توڑو;
		    }

		  copy_اوصاف_مقصد_builtin (newdecl);
		}
	    }
	  ورنہ
	    C_DECL_BUILTIN_PROTOTYPE (newdecl)
	      = C_DECL_BUILTIN_PROTOTYPE (olddecl);
	}

      /* Preserve function specific target and optimization options */
      اگر (DECL_FUNCTION_SPECIFIC_ہدف (olddecl)
	  && !DECL_FUNCTION_SPECIFIC_ہدف (newdecl))
	DECL_FUNCTION_SPECIFIC_ہدف (newdecl)
	  = DECL_FUNCTION_SPECIFIC_ہدف (olddecl);

      اگر (DECL_FUNCTION_SPECIFIC_OPTIMIZATION (olddecl)
	  && !DECL_FUNCTION_SPECIFIC_OPTIMIZATION (newdecl))
	DECL_FUNCTION_SPECIFIC_OPTIMIZATION (newdecl)
	  = DECL_FUNCTION_SPECIFIC_OPTIMIZATION (olddecl);

      /* Also preserve various other info from the definition.  */
      اگر (!new_is_definition)
	{
	  درخت t;
	  DECL_نتیجہ (newdecl) = DECL_نتیجہ (olddecl);
	  DECL_INITIAL (newdecl) = DECL_INITIAL (olddecl);
	  DECL_STRUCT_FUNCTION (newdecl) = DECL_STRUCT_FUNCTION (olddecl);
	  DECL_SAVED_درخت (newdecl) = DECL_SAVED_درخت (olddecl);
	  DECL_ARGUMENTS (newdecl) = copy_list (DECL_ARGUMENTS (olddecl));
	  برائے (t = DECL_ARGUMENTS (newdecl); t ; t = DECL_CHAIN (t))
	    DECL_CONTEXT (t) = newdecl;

	  /* See if we've got a function to instantiate from.  */
	  اگر (DECL_SAVED_درخت (olddecl))
	    DECL_ABSTRACT_ORIGIN (newdecl)
	      = DECL_ABSTRACT_ORIGIN (olddecl);
	}
    }

  /* Merge the USED information.  */
  اگر (درخت_مستعمل (olddecl))
    درخت_مستعمل (newdecl) = 1;
  ورنہ اگر (درخت_مستعمل (newdecl))
    درخت_مستعمل (olddecl) = 1;
  اگر (VAR_P (olddecl) || درخت_رمز (olddecl) == PARM_DECL)
    DECL_READ_P (newdecl) |= DECL_READ_P (olddecl);
  اگر (DECL_PRESERVE_P (olddecl))
    DECL_PRESERVE_P (newdecl) = 1;
  ورنہ اگر (DECL_PRESERVE_P (newdecl))
    DECL_PRESERVE_P (olddecl) = 1;

  /* Merge DECL_COMMON */
  اگر (VAR_P (olddecl) && VAR_P (newdecl)
      && !lookup_attribute ("common", DECL_اوصاف (newdecl))
      && !lookup_attribute ("nocommon", DECL_اوصاف (newdecl)))
    DECL_COMMON (newdecl) = DECL_COMMON (newdecl) && DECL_COMMON (olddecl);

  /* Copy most of the decl-specific fields of NEWDECL into OLDDECL.
     But preserve OLDDECL's DECL_UID, DECL_CONTEXT and
     DECL_ARGUMENTS (if appropriate).  */
  {
    غیرعلامتی olddecl_uid = DECL_UID (olddecl);
    درخت olddecl_context = DECL_CONTEXT (olddecl);
    درخت olddecl_arguments = تہی;
    اگر (درخت_رمز (olddecl) == FUNCTION_DECL)
      olddecl_arguments = DECL_ARGUMENTS (olddecl);

    حافظہ_نقل ((حرف *) olddecl + حجم (ساخت درخت_common),
	    (حرف *) newdecl + حجم (ساخت درخت_common),
	    حجم (ساخت درخت_decl_common) - حجم (ساخت درخت_common));
    DECL_USER_ALIGN (olddecl) = DECL_USER_ALIGN (newdecl);
    انتخاب (درخت_رمز (olddecl))
      {
      حالت FUNCTION_DECL:
      حالت VAR_DECL:
	{
	  ساخت symtab_گرہ *snode = olddecl->decl_with_vis.symtab_گرہ;

	  حافظہ_نقل ((حرف *) olddecl + حجم (ساخت درخت_decl_common),
		  (حرف *) newdecl + حجم (ساخت درخت_decl_common),
		  درخت_رمز_سائز (درخت_رمز (olddecl)) - حجم (ساخت درخت_decl_common));
	  olddecl->decl_with_vis.symtab_گرہ = snode;

	  اگر ((DECL_EXTERNAL (olddecl)
	       || درخت_عوامی (olddecl)
	       || درخت_STATIC (olddecl))
	      && DECL_SECTION_NAME (newdecl) != تہی)
	    سیٹ_decl_section_name (olddecl, newdecl);

	  /* This isn't quite correct for something like
		int __thread x attribute ((tls_model ("local-exec")));
		extern int __thread x;
	     as we'll lose the "local-exec" model.  */
	  اگر (VAR_P (olddecl) && DECL_THREAD_LOCAL_P (newdecl))
	    سیٹ_decl_tls_model (olddecl, DECL_TLS_MODEL (newdecl));
	  توڑو;
	}

      حالت میدان_DECL:
      حالت PARM_DECL:
      حالت LABEL_DECL:
      حالت نتیجہ_DECL:
      حالت CONST_DECL:
      حالت TYPE_DECL:
	حافظہ_نقل ((حرف *) olddecl + حجم (ساخت درخت_decl_common),
		(حرف *) newdecl + حجم (ساخت درخت_decl_common),
		درخت_رمز_سائز (درخت_رمز (olddecl)) - حجم (ساخت درخت_decl_common));
	توڑو;

      طےشدہ:

	حافظہ_نقل ((حرف *) olddecl + حجم (ساخت درخت_decl_common),
		(حرف *) newdecl + حجم (ساخت درخت_decl_common),
		حجم (ساخت درخت_decl_non_common) - حجم (ساخت درخت_decl_common));
      }
    DECL_UID (olddecl) = olddecl_uid;
    DECL_CONTEXT (olddecl) = olddecl_context;
    اگر (درخت_رمز (olddecl) == FUNCTION_DECL)
      DECL_ARGUMENTS (olddecl) = olddecl_arguments;
  }

  /* If OLDDECL had its DECL_RTL instantiated, re-invoke make_decl_rtl
     so that encode_section_info has a chance to look at the new decl
     flags and attributes.  */
  اگر (DECL_RTL_سیٹ_P (olddecl)
      && (درخت_رمز (olddecl) == FUNCTION_DECL
	  || (VAR_P (olddecl) && درخت_STATIC (olddecl))))
    make_decl_rtl (olddecl);
}

/* Handle when a new declaration NEWDECL has the same name as an old
   one OLDDECL in the same binding contour.  Prints an error message
   if appropriate.

   If safely possible, alter OLDDECL to look like NEWDECL, and return
   true.  Otherwise, return false.  */

ساکن منطقی
duplicate_decls (درخت newdecl, درخت olddecl)
{
  درخت newtype = تہی, oldtype = تہی;

  اگر (!diagnose_mismatched_decls (newdecl, olddecl, &newtype, &oldtype))
    {
      /* Avoid `unused variable' and other warnings for OLDDECL.  */
      suppress_warning (olddecl, OPT_Wunused);
      /* If the types are completely different, poison them both with
 	 error_mark_node.  */
      اگر (درخت_رمز (درخت_TYPE (newdecl)) != درخت_رمز (درخت_TYPE (olddecl))
	  && olddecl != error_mark_گرہ
	  && نظر_آیا_error ())
	{
	  اگر (درخت_رمز (olddecl) != FUNCTION_DECL)
	    درخت_TYPE (olddecl) = error_mark_گرہ;
	  اگر (درخت_رمز (newdecl) != FUNCTION_DECL)
	    درخت_TYPE (newdecl) = error_mark_گرہ;
	}
      واپس جھوٹ;
    }

  ملاؤ_decls (newdecl, olddecl, newtype, oldtype);

  /* The NEWDECL will no longer be needed.

     Before releasing the node, be sure to remove function from symbol
     table that might have been inserted there to record comdat group.
     Be sure to however do not free DECL_STRUCT_FUNCTION because this
     structure is shared in between NEWDECL and OLDECL.  */
  اگر (درخت_رمز (newdecl) == FUNCTION_DECL)
    DECL_STRUCT_FUNCTION (newdecl) = تہی;
  اگر (VAR_OR_FUNCTION_DECL_P (newdecl))
    {
      ساخت symtab_گرہ *snode = symtab_گرہ::get (newdecl);
      اگر (snode)
	snode->remove ();
    }
  ggc_free (newdecl);
  واپس سچ;
}


/* Check whether decl-node NEW_DECL shadows an existing declaration.  */
ساکن خالی
warn_if_shadowing (درخت new_decl)
{
  ساخت c_binding *b;

  /* Shadow warnings wanted?  */
  اگر (!(warn_shadow
        || warn_shadow_local
        || warn_shadow_compatible_local)
      /* No shadow warnings for internally generated vars.  */
      || DECL_IS_UNDECLARED_BUILTIN (new_decl))
    واپس;

  /* Is anything being shadowed?  Invisible decls do not count.  */
  برائے (b = I_علامت_BINDING (DECL_NAME (new_decl)); b; b = b->shadowed)
    اگر (b->decl && b->decl != new_decl && !b->invisible
	&& (b->decl == error_mark_گرہ
	    || diagnostic_report_warnings_p (global_dc,
					     DECL_ماخذ_LOCATION (b->decl))))
      {
	درخت old_decl = b->decl;

	اگر (old_decl == error_mark_گرہ)
	  {
	    warning (OPT_Wshadow, "declaration of %q+D shadows previous "
		     "non-variable", new_decl);
	    توڑو;
	  }

	منطقی warned = جھوٹ;
	auto_diagnostic_گروہ d;
	اگر (درخت_رمز (old_decl) == PARM_DECL)
	  {
	    شمار opt_رمز warning_رمز;

	    /* If '-Wshadow=compatible-local' is specified without other
	       -Wshadow= flags, we will warn only when the types of the
	       shadowing variable (i.e. new_decl) and the shadowed variable
	       (old_decl) are compatible.  */
	    اگر (warn_shadow)
	      warning_رمز = OPT_Wshadow;
	    ورنہ اگر (comptypes (درخت_TYPE (old_decl), درخت_TYPE (new_decl)))
	      warning_رمز = OPT_Wshadow_compatible_local;
	    ورنہ
	      warning_رمز = OPT_Wshadow_local;
	    warned = warning_at (DECL_ماخذ_LOCATION (new_decl), warning_رمز,
				 "declaration of %qD shadows a parameter",
				 new_decl);
	  }
	ورنہ اگر (DECL_FILE_SCOPE_P (old_decl))
	  {
	    /* Do not warn if a variable shadows a function, unless
	       the variable is a function or a pointer-to-function.  */
	    اگر (درخت_رمز (old_decl) == FUNCTION_DECL
		&& درخت_رمز (new_decl) != FUNCTION_DECL
		&& !FUNCTION_اشارہ_گر_TYPE_P (درخت_TYPE (new_decl)))
		جاری;

	    warned = warning_at (DECL_ماخذ_LOCATION (new_decl), OPT_Wshadow,
				 "declaration of %qD shadows a global "
				 "declaration",
				 new_decl);
	  }
	ورنہ اگر (درخت_رمز (old_decl) == FUNCTION_DECL
		 && fndecl_built_اندر_p (old_decl))
	  {
	    warning (OPT_Wshadow, "declaration of %q+D shadows "
		     "a built-in function", new_decl);
	    توڑو;
	  }
	ورنہ
	  {
	    شمار opt_رمز warning_رمز;

	    /* If '-Wshadow=compatible-local' is specified without other
	       -Wshadow= flags, we will warn only when the types of the
	       shadowing variable (i.e. new_decl) and the shadowed variable
	       (old_decl) are compatible.  */
	    اگر (warn_shadow)
	      warning_رمز = OPT_Wshadow;
	    ورنہ اگر (comptypes (درخت_TYPE (old_decl), درخت_TYPE (new_decl)))
	      warning_رمز = OPT_Wshadow_compatible_local;
	    ورنہ
	      warning_رمز = OPT_Wshadow_local;
	    warned = warning_at (DECL_ماخذ_LOCATION (new_decl), warning_رمز,
				 "declaration of %qD shadows a previous local",
				 new_decl);
	  }

	اگر (warned)
	  inform (DECL_ماخذ_LOCATION (old_decl),
		  "shadowed declaration is here");

	توڑو;
      }
}

/* Record a decl-node X as belonging to the current lexical scope.
   Check for errors (such as an incompatible declaration for the same
   name already seen in the same scope).

   Returns either X or an old decl for the same name.
   If an old decl is returned, it may have been smashed
   to agree with what X says.  */

درخت
pushdecl (درخت x)
{
  درخت name = DECL_NAME (x);
  ساخت c_scope *scope = current_scope;
  ساخت c_binding *b;
  منطقی nested = جھوٹ;
  location_t locus = DECL_ماخذ_LOCATION (x);

  /* Must set DECL_CONTEXT for everything not at file scope or
     DECL_FILE_SCOPE_P won't work.  Local externs don't count
     unless they have initializers (which generate code).  We
     also exclude CONST_DECLs because enumerators will get the
     type of the enum as context.  */
  اگر (current_function_decl
      && درخت_رمز (x) != CONST_DECL
      && (!VAR_OR_FUNCTION_DECL_P (x)
	  || DECL_INITIAL (x) || !درخت_عوامی (x)))
    DECL_CONTEXT (x) = current_function_decl;

  /* Anonymous decls are just inserted in the scope.  */
  اگر (!name)
    {
      bind (name, x, scope, /*invisible=*/جھوٹ, /*nested=*/جھوٹ,
	    locus);
      واپس x;
    }

  /* First, see if there is another declaration with the same name in
     the current scope.  If there is, duplicate_decls may do all the
     work for us.  If duplicate_decls returns false, that indicates
     two incompatible decls in the same scope; we are to silently
     replace the old one (duplicate_decls has issued all appropriate
     diagnostics).  In particular, we should not consider possible
     duplicates in the external scope, or shadowing.  */
  b = I_علامت_BINDING (name);
  اگر (b && B_اندر_SCOPE (b, scope))
    {
      ساخت c_binding *b_ext, *b_use;
      درخت type = درخت_TYPE (x);
      درخت visdecl = b->decl;
      درخت vistype = درخت_TYPE (visdecl);
      اگر (درخت_رمز (درخت_TYPE (x)) == ARRAY_TYPE
	  && COMPLETE_TYPE_P (درخت_TYPE (x)))
	b->inner_comp = جھوٹ;
      b_use = b;
      b_ext = b;
      /* If this is an external linkage declaration, we should check
	 for compatibility with the type in the external scope before
	 setting the type at this scope based on the visible
	 information only.  */
      اگر (درخت_عوامی (x) && درخت_عوامی (visdecl))
	{
	  جب (b_ext && !B_اندر_EXTERNAL_SCOPE (b_ext))
	    b_ext = b_ext->shadowed;
	  اگر (b_ext)
	    {
	      b_use = b_ext;
	      اگر (b_use->u.type)
		درخت_TYPE (b_use->decl) = b_use->u.type;
	    }
	}

      /* Check if x is part of a FMV set with b_use.
	 FMV is only supported in c for targets with target_version
	 attributes.  */
      اگر (!ہدف_HAS_FMV_ہدف_ATTRIBUTE
	  && b_use && درخت_رمز (b_use->decl) == FUNCTION_DECL
	  && درخت_رمز (x) == FUNCTION_DECL && DECL_FILE_SCOPE_P (b_use->decl)
	  && DECL_FILE_SCOPE_P (x)
	  && disjoint_نسخہ_decls (x, b_use->decl)
	  && comptypes (vistype, type))
	{
	  maybe_mark_function_versioned (b_use->decl);
	  maybe_mark_function_versioned (b->decl);
	  maybe_mark_function_versioned (x);

	  cgraph_گرہ *b_گرہ = cgraph_گرہ::get_create (b_use->decl);
	  cgraph_function_نسخہ_info *b_v = b_گرہ->function_نسخہ ();
	  اگر (!b_v)
	    b_v = b_گرہ->داخل_کرو_new_function_نسخہ ();

	  /* Check if this new node conflicts with any previous functions
	     in the set.  */
	  cgraph_function_نسخہ_info *نسخہ = b_v;
	  برائے (; نسخہ; نسخہ = نسخہ->اگلا)
	    اگر (!disjoint_نسخہ_decls (نسخہ->this_گرہ->decl, x))
	      {
		/* The decls define overlapping version, so attempt to merge
		   or diagnose the conflict.  */
		اگر (duplicate_decls (x, نسخہ->this_گرہ->decl))
		  واپس نسخہ->this_گرہ->decl;
		ورنہ
		  واپس error_mark_گرہ;
	      }

	  /* This is a new version to be added to FMV structure.  */
	  cgraph_گرہ::جوڑو_function_نسخہ (b_v, x);

	  /* Get the first node from the structure.  */
	  cgraph_function_نسخہ_info *default_v = b_v;
	  جب (default_v->پچھلا)
	    default_v = default_v->پچھلا;
	  /* Always use the default node for the bindings.  */
	  b_use->decl = default_v->this_گرہ->decl;
	  b->decl = default_v->this_گرہ->decl;

	  /* Node is not a duplicate, so no need to do the rest of the
	     checks.  */
	  واپس x;
	}

      اگر (duplicate_decls (x, b_use->decl))
	{
	  اگر (b_use != b)
	    {
	      /* Save the updated type in the external scope and
		 restore the proper type for this scope.  */
	      درخت thistype;
	      اگر (comptypes (vistype, type))
		thistype = مرکب_type (vistype, type);
	      ورنہ
		thistype = درخت_TYPE (b_use->decl);
	      b_use->u.type = درخت_TYPE (b_use->decl);
	      اگر (درخت_رمز (b_use->decl) == FUNCTION_DECL
		  && fndecl_built_اندر_p (b_use->decl))
		thistype
		  = c_build_type_attribute_variant (thistype,
						    TYPE_اوصاف
						    (b_use->u.type));
	      درخت_TYPE (b_use->decl) = thistype;
	    }
	  واپس b_use->decl;
	}
      ورنہ
	جاؤ skip_external_and_shadow_checks;
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
  اگر ((DECL_EXTERNAL (x) || scope == file_scope)
      && (VAR_OR_FUNCTION_DECL_P (x) || c_dialect_objc ()))
    {
      درخت type = درخت_TYPE (x);
      درخت vistype = NULL_درخت;
      درخت visdecl = NULL_درخت;
      منطقی type_saved = جھوٹ;
      اگر (b && !B_اندر_EXTERNAL_SCOPE (b)
	  && VAR_OR_FUNCTION_DECL_P (b->decl)
	  && DECL_FILE_SCOPE_P (b->decl))
	{
	  visdecl = b->decl;
	  vistype = درخت_TYPE (visdecl);
	}
      اگر (scope != file_scope
	  && !DECL_اندر_SYSTEM_سرخی (x))
	warning_at (locus, OPT_Wnested_externs,
		    "nested extern declaration of %qD", x);

      جب (b && !B_اندر_EXTERNAL_SCOPE (b))
	{
	  /* If this decl might be modified, save its type.  This is
	     done here rather than when the decl is first bound
	     because the type may change after first binding, through
	     being completed or through attributes being added.  If we
	     encounter multiple such decls, only the first should have
	     its type saved; the others will already have had their
	     proper types saved and the types will not have changed as
	     their scopes will not have been re-entered.  */
	  اگر (DECL_P (b->decl) && DECL_FILE_SCOPE_P (b->decl) && !type_saved)
	    {
	      b->u.type = درخت_TYPE (b->decl);
	      type_saved = سچ;
	    }
	  اگر (B_اندر_FILE_SCOPE (b)
	      && VAR_P (b->decl)
	      && درخت_STATIC (b->decl)
	      && درخت_رمز (درخت_TYPE (b->decl)) == ARRAY_TYPE
	      && !TYPE_DOMAIN (درخت_TYPE (b->decl))
	      && درخت_رمز (type) == ARRAY_TYPE
	      && TYPE_DOMAIN (type)
	      && TYPE_MAX_قدر (TYPE_DOMAIN (type))
	      && !integer_zerop (TYPE_MAX_قدر (TYPE_DOMAIN (type))))
	    {
	      /* Array type completed in inner scope, which should be
		 diagnosed if the completion does not have size 1 and
		 it does not get completed in the file scope.  */
	      b->inner_comp = سچ;
	    }
	  b = b->shadowed;
	}

      /* If a matching external declaration has been found, set its
	 type to the composite of all the types of that declaration.
	 After the consistency checks, it will be reset to the
	 composite of the visible types only.  */
      اگر (b && b->u.type)
	درخت_TYPE (b->decl) = b->u.type;

      /* the static does not go in the externals scope.  */
      اگر (b && duplicate_decls (x, b->decl))
	{
	  درخت thistype;
	  اگر (vistype)
	    {
	      اگر (comptypes (vistype, type))
		thistype = مرکب_type (vistype, type);
	      ورنہ
		thistype = درخت_TYPE (b->decl);
	    }
	  ورنہ
	    thistype = type;
	  b->u.type = درخت_TYPE (b->decl);
	  /* Propagate the type attributes to the decl.  */
	  thistype
	    = c_build_type_attribute_variant (thistype,
					      TYPE_اوصاف (b->u.type));
	  درخت_TYPE (b->decl) = thistype;
	  bind (name, b->decl, scope, /*invisible=*/جھوٹ, /*nested=*/سچ,
		locus);
	  واپس b->decl;
	}
      ورنہ اگر (درخت_عوامی (x))
	{
	  اگر (visdecl && !b && duplicate_decls (x, visdecl))
	    {
	      /* An external declaration at block scope referring to a
		 visible entity with internal linkage.  The composite
		 type will already be correct for this scope, so we
		 just need to fall through to make the declaration in
		 this scope.  */
	      nested = سچ;
	      x = visdecl;
	    }
	  ورنہ
	    {
	      bind (name, x, external_scope, /*invisible=*/سچ,
		    /*nested=*/جھوٹ, locus);
	      nested = سچ;
	    }
	}
    }

  اگر (درخت_رمز (x) != PARM_DECL)
    warn_if_shadowing (x);

 skip_external_and_shadow_checks:
  اگر (درخت_رمز (x) == TYPE_DECL)
    {
      /* So this is a typedef, set its underlying type.  */
      سیٹ_underlying_type (x);

      /* If X is a typedef defined in the current function, record it
	 for the purpose of implementing the -Wunused-local-typedefs
	 warning.  */
      ریکارڈ_locally_defined_typedef (x);
    }

  bind (name, x, scope, /*invisible=*/جھوٹ, nested, locus);

  /* If x's type is incomplete because it's based on a
     structure or union which has not yet been fully declared,
     attach it to that structure or union type, so we can go
     back and complete the variable declaration later, if the
     structure or union gets fully declared.

     If the input is erroneous, we can have error_mark in the type
     slot (e.g. "f(void a, ...)") - that doesn't count as an
     incomplete type.  */
  اگر (درخت_TYPE (x) != error_mark_گرہ
      && !COMPLETE_TYPE_P (درخت_TYPE (x)))
    {
      درخت element = درخت_TYPE (x);

      جب (درخت_رمز (element) == ARRAY_TYPE)
	element = درخت_TYPE (element);
      element = TYPE_MAIN_VARIANT (element);

      اگر ((ریکارڈ_OR_UNION_TYPE_P (element)
	   || درخت_رمز (element) == ENUMERAL_TYPE)
	  && (درخت_رمز (x) != TYPE_DECL
	      || درخت_رمز (درخت_TYPE (x)) == ARRAY_TYPE)
	  && !COMPLETE_TYPE_P (element))
	C_TYPE_INCOMPLETE_VARS (element)
	  = درخت_cons (NULL_درخت, x, C_TYPE_INCOMPLETE_VARS (element));
    }
  واپس x;
}


/* Issue a permerror about implicit function declaration.  ID is the function
   identifier, OLDDECL is a declaration of the function in a different scope,
   or NULL_TREE.  */

ساکن خالی
implicit_decl_permerror (location_t loc, درخت id, درخت olddecl)
{
  اگر (!warn_implicit_function_declaration)
    واپس;

  منطقی warned;
  auto_diagnostic_گروہ d;
  name_hint hint;
  اگر (!olddecl)
    hint = lookup_name_fuzzy (id, FUZZY_LOOKUP_FUNCTION_NAME, loc);

  اگر (flag_isoc99)
    {
      اگر (ثابت حرف *suggestion = hint.suggestion ())
	{
	  gcc_rich_location richloc (loc);
	  richloc.جوڑو_fixit_replace (suggestion);
	  warned = permerror_opt (&richloc, OPT_Wimplicit_function_declaration,
				  "implicit declaration of function %qE;"
				  " did you mean %qs?",
				  id, suggestion);
	}
      ورنہ
	warned = permerror_opt (loc, OPT_Wimplicit_function_declaration,
				"implicit declaration of function %qE", id);
    }
  ورنہ اگر (ثابت حرف *suggestion = hint.suggestion ())
    {
      gcc_rich_location richloc (loc);
      richloc.جوڑو_fixit_replace (suggestion);
      warned = warning_at
	(&richloc, OPT_Wimplicit_function_declaration,
	 G_("implicit declaration of function %qE; did you mean %qs?"),
	 id, suggestion);
    }
  ورنہ
    warned = warning_at (loc, OPT_Wimplicit_function_declaration,
			 G_("implicit declaration of function %qE"), id);

  اگر (warned)
    {
      /* Whether the olddecl is an undeclared builtin function.
	 locate_old_decl will not generate a diagnostic for those,
	 so in that case we want to look elsewhere.  */
      منطقی undeclared_builtin = (olddecl
				 && درخت_رمز (olddecl) == FUNCTION_DECL
				 && fndecl_built_اندر_p (olddecl)
				 && !C_DECL_DECLARED_BUILTIN (olddecl));
      اگر (undeclared_builtin)
	{
	  ثابت حرف *سرخی = سرخی_for_builtin_fn (olddecl);
	  اگر (سرخی)
	    {
	      rich_location richloc (سطر_جدول, loc);
	      maybe_جوڑو_include_fixit (&richloc, سرخی, سچ);
	      inform (&richloc,
		      "include %qs or provide a declaration of %qE",
		      سرخی, id);
	    }
	}
      ورنہ اگر (olddecl)
	locate_old_decl (olddecl);
    }

  اگر (!warned)
    hint.suppress ();
}

/* Return the name of the header file that declares built-in function
   FNDECL, or null if either we don't know or don't expect to see an
   explicit declaration.  */

ساکن ثابت حرف *
سرخی_for_builtin_fn (درخت fndecl)
{
  اگر (DECL_BUILT_اندر_CLASS (fndecl) != BUILT_اندر_معمول)
    واپس تہی;

  انتخاب (DECL_FUNCTION_رمز (fndecl))
    {
    CASE_FLT_FN (BUILT_اندر_ACOS):
    CASE_FLT_FN (BUILT_اندر_ACOSH):
    CASE_FLT_FN (BUILT_اندر_ASIN):
    CASE_FLT_FN (BUILT_اندر_ASINH):
    CASE_FLT_FN (BUILT_اندر_ATAN):
    CASE_FLT_FN (BUILT_اندر_ATANH):
    CASE_FLT_FN (BUILT_اندر_ATAN2):
    CASE_FLT_FN (BUILT_اندر_CBRT):
    CASE_FLT_FN (BUILT_اندر_CEIL):
    CASE_FLT_FN_FLOATN_NX (BUILT_اندر_CEIL):
    CASE_FLT_FN (BUILT_اندر_COPYSIGN):
    CASE_FLT_FN_FLOATN_NX (BUILT_اندر_COPYSIGN):
    CASE_FLT_FN (BUILT_اندر_COS):
    CASE_FLT_FN (BUILT_اندر_COSH):
    CASE_FLT_FN (BUILT_اندر_ERF):
    CASE_FLT_FN (BUILT_اندر_ERFC):
    CASE_FLT_FN (BUILT_اندر_EXP):
    CASE_FLT_FN (BUILT_اندر_EXP2):
    CASE_FLT_FN (BUILT_اندر_EXPM1):
    CASE_FLT_FN (BUILT_اندر_FABS):
    CASE_FLT_FN_FLOATN_NX (BUILT_اندر_FABS):
    CASE_FLT_FN (BUILT_اندر_FDIM):
    CASE_FLT_FN (BUILT_اندر_FLOOR):
    CASE_FLT_FN_FLOATN_NX (BUILT_اندر_FLOOR):
    CASE_FLT_FN (BUILT_اندر_FMA):
    CASE_FLT_FN_FLOATN_NX (BUILT_اندر_FMA):
    CASE_FLT_FN (BUILT_اندر_FMAX):
    CASE_FLT_FN_FLOATN_NX (BUILT_اندر_FMAX):
    CASE_FLT_FN (BUILT_اندر_FMIN):
    CASE_FLT_FN_FLOATN_NX (BUILT_اندر_FMIN):
    CASE_FLT_FN (BUILT_اندر_FMOD):
    CASE_FLT_FN (BUILT_اندر_FREXP):
    CASE_FLT_FN (BUILT_اندر_HYPOT):
    CASE_FLT_FN (BUILT_اندر_ILOGB):
    CASE_FLT_FN (BUILT_اندر_LDEXP):
    CASE_FLT_FN (BUILT_اندر_LGAMMA):
    CASE_FLT_FN (BUILT_اندر_LLRINT):
    CASE_FLT_FN (BUILT_اندر_LLROUND):
    CASE_FLT_FN (BUILT_اندر_LOG):
    CASE_FLT_FN (BUILT_اندر_LOG10):
    CASE_FLT_FN (BUILT_اندر_LOG1_P):
    CASE_FLT_FN (BUILT_اندر_LOG2):
    CASE_FLT_FN (BUILT_اندر_LOGB):
    CASE_FLT_FN (BUILT_اندر_LRINT):
    CASE_FLT_FN (BUILT_اندر_LROUND):
    CASE_FLT_FN (BUILT_اندر_MODF):
    CASE_FLT_FN (BUILT_اندر_NAN):
    CASE_FLT_FN (BUILT_اندر_NEARBYINT):
    CASE_FLT_FN_FLOATN_NX (BUILT_اندر_NEARBYINT):
    CASE_FLT_FN (BUILT_اندر_NEXTAFTER):
    CASE_FLT_FN (BUILT_اندر_NEXTTOWARD):
    CASE_FLT_FN (BUILT_اندر_POW):
    CASE_FLT_FN (BUILT_اندر_REMAINDER):
    CASE_FLT_FN (BUILT_اندر_REMQUO):
    CASE_FLT_FN (BUILT_اندر_RINT):
    CASE_FLT_FN_FLOATN_NX (BUILT_اندر_RINT):
    CASE_FLT_FN (BUILT_اندر_باری):
    CASE_FLT_FN_FLOATN_NX (BUILT_اندر_باری):
    CASE_FLT_FN (BUILT_اندر_SCALBLN):
    CASE_FLT_FN (BUILT_اندر_SCALBN):
    CASE_FLT_FN (BUILT_اندر_SIN):
    CASE_FLT_FN (BUILT_اندر_SINH):
    CASE_FLT_FN (BUILT_اندر_SINCOS):
    CASE_FLT_FN (BUILT_اندر_SQRT):
    CASE_FLT_FN_FLOATN_NX (BUILT_اندر_SQRT):
    CASE_FLT_FN (BUILT_اندر_TAN):
    CASE_FLT_FN (BUILT_اندر_TANH):
    CASE_FLT_FN (BUILT_اندر_TGAMMA):
    CASE_FLT_FN (BUILT_اندر_TRUNC):
    CASE_FLT_FN_FLOATN_NX (BUILT_اندر_TRUNC):
    حالت BUILT_اندر_ISINF:
    حالت BUILT_اندر_ISNAN:
      واپس "<math.h>";
    CASE_FLT_FN (BUILT_اندر_CABS):
    CASE_FLT_FN (BUILT_اندر_CACOS):
    CASE_FLT_FN (BUILT_اندر_CACOSH):
    CASE_FLT_FN (BUILT_اندر_CARG):
    CASE_FLT_FN (BUILT_اندر_CASIN):
    CASE_FLT_FN (BUILT_اندر_CASINH):
    CASE_FLT_FN (BUILT_اندر_CATAN):
    CASE_FLT_FN (BUILT_اندر_CATANH):
    CASE_FLT_FN (BUILT_اندر_CCOS):
    CASE_FLT_FN (BUILT_اندر_CCOSH):
    CASE_FLT_FN (BUILT_اندر_CEXP):
    CASE_FLT_FN (BUILT_اندر_CIMAG):
    CASE_FLT_FN (BUILT_اندر_CLOG):
    CASE_FLT_FN (BUILT_اندر_CONJ):
    CASE_FLT_FN (BUILT_اندر_CPOW):
    CASE_FLT_FN (BUILT_اندر_CPROJ):
    CASE_FLT_FN (BUILT_اندر_CREAL):
    CASE_FLT_FN (BUILT_اندر_CSIN):
    CASE_FLT_FN (BUILT_اندر_CSINH):
    CASE_FLT_FN (BUILT_اندر_CSQRT):
    CASE_FLT_FN (BUILT_اندر_CTAN):
    CASE_FLT_FN (BUILT_اندر_CTANH):
      واپس "<complex.h>";
    حالت BUILT_اندر_MEMCHR:
    حالت BUILT_اندر_MEMCMP:
    حالت BUILT_اندر_MEMCPY:
    حالت BUILT_اندر_MEMMOVE:
    حالت BUILT_اندر_MEMSET:
    حالت BUILT_اندر_STRCAT:
    حالت BUILT_اندر_STRCHR:
    حالت BUILT_اندر_STRCMP:
    حالت BUILT_اندر_STRCPY:
    حالت BUILT_اندر_STRCSPN:
    حالت BUILT_اندر_STRLEN:
    حالت BUILT_اندر_STRNCAT:
    حالت BUILT_اندر_STRNCMP:
    حالت BUILT_اندر_STRNCPY:
    حالت BUILT_اندر_STRPBRK:
    حالت BUILT_اندر_STRRCHR:
    حالت BUILT_اندر_STRSPN:
    حالت BUILT_اندر_STRSTR:
      واپس "<string.h>";
    حالت BUILT_اندر_FPRINTF:
    حالت BUILT_اندر_PUTC:
    حالت BUILT_اندر_FPUTC:
    حالت BUILT_اندر_FPUTS:
    حالت BUILT_اندر_FSCANF:
    حالت BUILT_اندر_FWRITE:
    حالت BUILT_اندر_PRINTF:
    حالت BUILT_اندر_PUTCHAR:
    حالت BUILT_اندر_PUTS:
    حالت BUILT_اندر_SCANF:
    حالت BUILT_اندر_SNPRINTF:
    حالت BUILT_اندر_SPRINTF:
    حالت BUILT_اندر_SSCANF:
    حالت BUILT_اندر_VFPRINTF:
    حالت BUILT_اندر_VFSCANF:
    حالت BUILT_اندر_VPRINTF:
    حالت BUILT_اندر_VSCANF:
    حالت BUILT_اندر_VSNPRINTF:
    حالت BUILT_اندر_VSPRINTF:
    حالت BUILT_اندر_VSSCANF:
      واپس "<stdio.h>";
    حالت BUILT_اندر_ISALNUM:
    حالت BUILT_اندر_ISALPHA:
    حالت BUILT_اندر_ISBLANK:
    حالت BUILT_اندر_ISCNTRL:
    حالت BUILT_اندر_ISDIGIT:
    حالت BUILT_اندر_ISGRAPH:
    حالت BUILT_اندر_ISLOWER:
    حالت BUILT_اندر_ISPRINT:
    حالت BUILT_اندر_ISPUNCT:
    حالت BUILT_اندر_ISSPACE:
    حالت BUILT_اندر_ISUPPER:
    حالت BUILT_اندر_ISXDIGIT:
    حالت BUILT_اندر_TOLOWER:
    حالت BUILT_اندر_TOUPPER:
      واپس "<ctype.h>";
    حالت BUILT_اندر_ISWALNUM:
    حالت BUILT_اندر_ISWALPHA:
    حالت BUILT_اندر_ISWBLANK:
    حالت BUILT_اندر_ISWCNTRL:
    حالت BUILT_اندر_ISWDIGIT:
    حالت BUILT_اندر_ISWGRAPH:
    حالت BUILT_اندر_ISWLOWER:
    حالت BUILT_اندر_ISWPRINT:
    حالت BUILT_اندر_ISWPUNCT:
    حالت BUILT_اندر_ISWSPACE:
    حالت BUILT_اندر_ISWUPPER:
    حالت BUILT_اندر_ISWXDIGIT:
    حالت BUILT_اندر_TOWLOWER:
    حالت BUILT_اندر_TOWUPPER:
      واپس "<wctype.h>";
    حالت BUILT_اندر_ABORT:
    حالت BUILT_اندر_ABS:
    حالت BUILT_اندر_CALLOC:
    حالت BUILT_اندر_EXIT:
    حالت BUILT_اندر_FREE:
    حالت BUILT_اندر_LABS:
    حالت BUILT_اندر_LLABS:
    حالت BUILT_اندر_MALLOC:
    حالت BUILT_اندر_REALLOC:
    حالت BUILT_اندر_EXIT2:
    حالت BUILT_اندر_ALIGNED_ALLOC:
      واپس "<stdlib.h>";
    حالت BUILT_اندر_IMAXABS:
      واپس "<inttypes.h>";
    حالت BUILT_اندر_STRFTIME:
      واپس "<time.h>";
    طےشدہ:
      واپس تہی;
    }
}

/* Generate an implicit declaration for identifier FUNCTIONID at LOC as a
   function of type int ().  */

درخت
implicitly_declare (location_t loc, درخت functionid)
{
  ساخت c_binding *b;
  درخت decl = NULL_درخت;
  درخت asmspec_درخت;

  برائے (b = I_علامت_BINDING (functionid); b; b = b->shadowed)
    {
      اگر (B_اندر_SCOPE (b, external_scope))
	{
	  decl = b->decl;
	  توڑو;
	}
    }

  اگر (decl)
    {
      اگر (درخت_رمز (decl) != FUNCTION_DECL)
	واپس decl;

      /* FIXME: Objective-C has weird not-really-builtin functions
	 which are supposed to be visible automatically.  They wind up
	 in the external scope because they're pushed before the file
	 scope gets created.  Catch this here and rebind them into the
	 file scope.  */
      اگر (!fndecl_built_اندر_p (decl) && DECL_IS_UNDECLARED_BUILTIN (decl))
	{
	  bind (functionid, decl, file_scope,
		/*invisible=*/جھوٹ, /*nested=*/سچ,
		DECL_ماخذ_LOCATION (decl));
	  واپس decl;
	}
      ورنہ
	{
	  درخت newtype = default_function_type;
	  اگر (b->u.type)
	    درخت_TYPE (decl) = b->u.type;
	  /* Implicit declaration of a function already declared
	     (somehow) in a different scope, or as a built-in.
	     If this is the first time this has happened, warn;
	     then recycle the old declaration but with the new type.  */
	  اگر (!C_DECL_IMPLICIT (decl))
	    {
	      implicit_decl_permerror (loc, functionid, decl);
	      C_DECL_IMPLICIT (decl) = 1;
	    }
	  اگر (fndecl_built_اندر_p (decl))
	    {
	      newtype = c_build_type_attribute_variant (newtype,
							TYPE_اوصاف
							(درخت_TYPE (decl)));
	      اگر (!comptypes (newtype, درخت_TYPE (decl)))
		{
		  auto_diagnostic_گروہ d;
		  منطقی warned = warning_at (loc,
					    OPT_Wbuiltin_declaration_mismatch,
					    "incompatible implicit "
					    "declaration of built-in "
					    "function %qD", decl);
		  /* See if we can hint which header to include.  */
		  ثابت حرف *سرخی = سرخی_for_builtin_fn (decl);
		  اگر (سرخی != تہی && warned)
		    {
		      rich_location richloc (سطر_جدول, loc);
		      maybe_جوڑو_include_fixit (&richloc, سرخی, سچ);
		      inform (&richloc,
			      "include %qs or provide a declaration of %qD",
			      سرخی, decl);
		    }
		  newtype = درخت_TYPE (decl);
		}
	    }
	  ورنہ
	    {
	      اگر (!comptypes (newtype, درخت_TYPE (decl)))
		{
		  auto_diagnostic_گروہ d;
		  error_at (loc, "incompatible implicit declaration of "
			    "function %qD", decl);
		  locate_old_decl (decl);
		}
	    }
	  b->u.type = درخت_TYPE (decl);
	  درخت_TYPE (decl) = newtype;
	  bind (functionid, decl, current_scope,
		/*invisible=*/جھوٹ, /*nested=*/سچ,
		DECL_ماخذ_LOCATION (decl));
	  واپس decl;
	}
    }

  /* Not seen before.  */
  decl = build_decl (loc, FUNCTION_DECL, functionid, default_function_type);
  DECL_EXTERNAL (decl) = 1;
  درخت_عوامی (decl) = 1;
  C_DECL_IMPLICIT (decl) = 1;
  implicit_decl_permerror (loc, functionid, 0);
  asmspec_درخت = maybe_apply_renaming_pragma (decl, /*asmname=*/تہی);
  اگر (asmspec_درخت)
    سیٹ_user_assembler_name (decl, درخت_STRING_اشارہ_گر (asmspec_درخت));

  /* C89 says implicit declarations are in the innermost block.
     So we record the decl in the standard fashion.  */
  decl = pushdecl (decl);

  /* No need to call objc_check_decl here - it's a function type.  */
  rest_کا_decl_compilation (decl, 0, 0);

  /* Write a record describing this implicit function declaration
     to the prototypes file (if requested).  */
  gen_aux_info_ریکارڈ (decl, 0, 1, 0);

  /* Possibly apply some default attributes to this implicit declaration.  */
  decl_اوصاف (&decl, NULL_درخت, 0);

  واپس decl;
}

/* Issue an error message for a reference to an undeclared variable
   ID, including a reference to a builtin outside of function-call
   context.  Establish a binding of the identifier to error_mark_node
   in an appropriate scope, which will suppress further errors for the
   same identifier.  The error message should be given location LOC.  */
خالی
undeclared_variable (location_t loc, درخت id)
{
  ساکن منطقی already = جھوٹ;
  ساخت c_scope *scope;

  auto_diagnostic_گروہ d;
  اگر (current_function_decl == NULL_درخت)
    {
      name_hint guessed_id = lookup_name_fuzzy (id, FUZZY_LOOKUP_NAME, loc);
      اگر (ثابت حرف *suggestion = guessed_id.suggestion ())
	{
	  gcc_rich_location richloc (loc);
	  richloc.جوڑو_fixit_replace (suggestion);
	  error_at (&richloc,
		    "%qE undeclared here (not in a function);"
		    " did you mean %qs?",
		    id, suggestion);
	}
      ورنہ
	error_at (loc, "%qE undeclared here (not in a function)", id);
      scope = current_scope;
    }
  ورنہ
    {
      اگر (!objc_diagnose_نجی_ivar (id))
	{
	  name_hint guessed_id = lookup_name_fuzzy (id, FUZZY_LOOKUP_NAME, loc);
	  اگر (ثابت حرف *suggestion = guessed_id.suggestion ())
	    {
	      gcc_rich_location richloc (loc);
	      richloc.جوڑو_fixit_replace (suggestion);
	      error_at (&richloc,
			"%qE undeclared (first use in this function);"
			" did you mean %qs?",
			id, suggestion);
	    }
	  ورنہ
	    error_at (loc, "%qE undeclared (first use in this function)", id);
	}
      اگر (!already)
	{
          inform (loc, "each undeclared identifier is reported only"
                  " once for each function it appears in");
	  already = سچ;
	}

      /* If we are parsing old-style parameter decls, current_function_decl
	 will be nonnull but current_function_scope will be null.  */
      scope = current_function_scope ? current_function_scope : current_scope;
    }
  bind (id, error_mark_گرہ, scope, /*invisible=*/جھوٹ, /*nested=*/جھوٹ,
	UNKNOWN_LOCATION);
}

/* Subroutine of lookup_label, declare_label, define_label: construct a
   LABEL_DECL with all the proper frills.  Also create a struct
   c_label_vars initialized for the current scope.  */

ساکن درخت
make_label (location_t location, درخت name, منطقی defining,
	    ساخت c_label_vars **p_label_vars)
{
  درخت label = build_decl (location, LABEL_DECL, name, void_type_گرہ);
  DECL_CONTEXT (label) = current_function_decl;
  سیٹ_DECL_منوال (label, VOIDmode);

  c_label_vars *label_vars = ggc_alloc<c_label_vars> ();
  label_vars->shadowed = تہی;
  سیٹ_spot_bindings (&label_vars->label_bindings, defining);
  label_vars->decls_اندر_scope = make_درخت_سمتیہ ();
  label_vars->gotos = تہی;
  *p_label_vars = label_vars;

  واپس label;
}

/* Get the LABEL_DECL corresponding to identifier NAME as a label.
   Create one if none exists so far for the current function.
   This is called when a label is used in a goto expression or
   has its address taken.  */

درخت
lookup_label (درخت name)
{
  درخت label;
  ساخت c_label_vars *label_vars;

  اگر (current_function_scope == 0)
    {
      error ("label %qE referenced outside of any function", name);
      واپس NULL_درخت;
    }

  /* Use a label already defined or ref'd with this name, but not if
     it is inherited from a containing function and wasn't declared
     using __label__.  */
  label = I_LABEL_DECL (name);
  اگر (label && (DECL_CONTEXT (label) == current_function_decl
		|| C_DECLARED_LABEL_FLAG (label)))
    {
      /* If the label has only been declared, update its apparent
	 location to point here, for better diagnostics if it
	 turns out not to have been defined.  */
      اگر (DECL_INITIAL (label) == NULL_درخت)
	DECL_ماخذ_LOCATION (label) = داخلہ_location;
      واپس label;
    }

  /* No label binding for that identifier; make one.  */
  label = make_label (داخلہ_location, name, جھوٹ, &label_vars);

  /* Ordinary labels go in the current function scope.  */
  bind_label (name, label, current_function_scope, label_vars);

  واپس label;
}

/* Issue a warning about DECL for a goto statement at GOTO_LOC going
   to LABEL.  */

ساکن خالی
warn_about_goto (location_t goto_loc, درخت label, درخت decl)
{
  auto_diagnostic_گروہ d;
  اگر (c_type_variably_modified_p (درخت_TYPE (decl)))
    error_at (goto_loc,
	      "jump into scope of identifier with variably modified type");
  ورنہ اگر (flag_openmp
	   && lookup_attribute ("omp allocate", DECL_اوصاف (decl)))
    error_at (goto_loc, "jump skips OpenMP %<allocate%> allocation");
  ورنہ
    اگر (!warning_at (goto_loc, OPT_Wjump_ناکامیاں_init,
		     "jump skips variable initialization"))
      واپس;
  inform (DECL_ماخذ_LOCATION (label), "label %qD defined here", label);
  inform (DECL_ماخذ_LOCATION (decl), "%qD declared here", decl);
}

/* Look up a label because of a goto statement.  This is like
   lookup_label, but also issues any appropriate warnings.  */

درخت
lookup_label_for_goto (location_t loc, درخت name)
{
  درخت label;
  ساخت c_label_vars *label_vars;
  غیرعلامتی صحیح ix;
  درخت decl;

  label = lookup_label (name);
  اگر (label == NULL_درخت)
    واپس NULL_درخت;

  /* If we are jumping to a different function, we can't issue any
     useful warnings.  */
  اگر (DECL_CONTEXT (label) != current_function_decl)
    {
      gcc_assert (C_DECLARED_LABEL_FLAG (label));
      واپس label;
    }

  label_vars = I_LABEL_BINDING (name)->u.label;

  /* If the label has not yet been defined, then push this goto on a
     list for possible later warnings.  */
  اگر (label_vars->label_bindings.scope == تہی)
    {
      c_goto_bindings *g = ggc_alloc<c_goto_bindings> ();

      g->loc = loc;
      سیٹ_spot_bindings (&g->goto_bindings, سچ);
      vec_محفوظ_ڈالو (label_vars->gotos, g);
      واپس label;
    }

  /* If there are any decls in label_vars->decls_in_scope, then this
     goto has missed the declaration of the decl.  This happens for a
     case like
       int i = 1;
      lab:
       ...
       goto lab;
     Issue a warning or error.  */
  FOR_EACH_VEC_محفوظ_ELT (label_vars->decls_اندر_scope, ix, decl)
    warn_about_goto (loc, label, decl);

  اگر (label_vars->label_bindings.بایاں_stmt_اظہاریہ)
    {
      auto_diagnostic_گروہ d;
      error_at (loc, "jump into statement expression");
      inform (DECL_ماخذ_LOCATION (label), "label %qD defined here", label);
    }

  واپس label;
}

/* Make a label named NAME in the current function, shadowing silently
   any that may be inherited from containing functions or containing
   scopes.  This is called for __label__ declarations.  */

درخت
declare_label (درخت name)
{
  ساخت c_binding *b = I_LABEL_BINDING (name);
  درخت label;
  ساخت c_label_vars *label_vars;

  /* Check to make sure that the label hasn't already been declared
     at this scope */
  اگر (b && B_اندر_CURRENT_SCOPE (b))
    {
      auto_diagnostic_گروہ d;
      error ("duplicate label declaration %qE", name);
      locate_old_decl (b->decl);

      /* Just use the previous declaration.  */
      واپس b->decl;
    }

  label = make_label (داخلہ_location, name, جھوٹ, &label_vars);
  C_DECLARED_LABEL_FLAG (label) = 1;

  /* Declared labels go in the current scope.  */
  bind_label (name, label, current_scope, label_vars);

  واپس label;
}

/* When we define a label, issue any appropriate warnings if there are
   any gotos earlier in the function which jump to this label.  */

ساکن خالی
check_earlier_gotos (درخت label, ساخت c_label_vars* label_vars)
{
  غیرعلامتی صحیح ix;
  ساخت c_goto_bindings *g;

  FOR_EACH_VEC_محفوظ_ELT (label_vars->gotos, ix, g)
    {
      ساخت c_binding *b;
      ساخت c_scope *scope;

      /* We have a goto to this label.  The goto is going forward.  In
	 g->scope, the goto is going to skip any binding which was
	 defined after g->bindings_in_scope.  */
      اگر (g->goto_bindings.scope->has_jump_unsafe_decl)
	{
	  برائے (b = g->goto_bindings.scope->bindings;
	       b != g->goto_bindings.bindings_اندر_scope;
	       b = b->پچھلا)
	    {
	      اگر (decl_jump_unsafe (b->decl))
		warn_about_goto (g->loc, label, b->decl);
	    }
	}

      /* We also need to warn about decls defined in any scopes
	 between the scope of the label and the scope of the goto.  */
      برائے (scope = label_vars->label_bindings.scope;
	   scope != g->goto_bindings.scope;
	   scope = scope->outer)
	{
	  gcc_assert (scope != تہی);
	  اگر (scope->has_jump_unsafe_decl)
	    {
	      اگر (scope == label_vars->label_bindings.scope)
		b = label_vars->label_bindings.bindings_اندر_scope;
	      ورنہ
		b = scope->bindings;
	      برائے (; b != تہی; b = b->پچھلا)
		{
		  اگر (decl_jump_unsafe (b->decl))
		    warn_about_goto (g->loc, label, b->decl);
		}
	    }
	}

      اگر (g->goto_bindings.stmt_exprs > 0)
	{
	  auto_diagnostic_گروہ d;
	  error_at (g->loc, "jump into statement expression");
	  inform (DECL_ماخذ_LOCATION (label), "label %qD defined here",
		  label);
	}
    }

  /* Now that the label is defined, we will issue warnings about
     subsequent gotos to this label when we see them.  */
  vec_محفوظ_truncate (label_vars->gotos, 0);
  label_vars->gotos = تہی;
}

/* Define a label, specifying the location in the source file.
   Return the LABEL_DECL node for the label, if the definition is valid.
   Otherwise return NULL_TREE.  */

درخت
define_label (location_t location, درخت name)
{
  /* Find any preexisting label with this name.  It is an error
     if that label has already been defined in this function, or
     if there is a containing function with a declared label with
     the same name.  */
  درخت label = I_LABEL_DECL (name);

  اگر (label
      && ((DECL_CONTEXT (label) == current_function_decl
	   && DECL_INITIAL (label) != NULL_درخت)
	  || (DECL_CONTEXT (label) != current_function_decl
	      && C_DECLARED_LABEL_FLAG (label))))
    {
      auto_diagnostic_گروہ d;
      error_at (location, "duplicate label %qD", label);
      locate_old_decl (label);
      واپس NULL_درخت;
    }
  ورنہ اگر (label && DECL_CONTEXT (label) == current_function_decl)
    {
      ساخت c_label_vars *label_vars = I_LABEL_BINDING (name)->u.label;

      /* The label has been used or declared already in this function,
	 but not defined.  Update its location to point to this
	 definition.  */
      DECL_ماخذ_LOCATION (label) = location;
      سیٹ_spot_bindings (&label_vars->label_bindings, سچ);

      /* Issue warnings as required about any goto statements from
	 earlier in the function.  */
      check_earlier_gotos (label, label_vars);
    }
  ورنہ
    {
      ساخت c_label_vars *label_vars;

      /* No label binding for that identifier; make one.  */
      label = make_label (location, name, سچ, &label_vars);

      /* Ordinary labels go in the current function scope.  */
      bind_label (name, label, current_function_scope, label_vars);
    }

  اگر (!اندر_system_سرخی_at (داخلہ_location) && lookup_name (name))
    warning_at (location, OPT_Wtraditional,
		"traditional C lacks a separate namespace "
		"for labels, identifier %qE conflicts", name);

  /* Mark label as having been defined.  */
  DECL_INITIAL (label) = error_mark_گرہ;
  واپس label;
}

/* Get the bindings for a new switch statement.  This is used to issue
   warnings as appropriate for jumps from the switch to case or
   default labels.  */

ساخت c_spot_bindings *
c_get_switch_bindings (خالی)
{
  ساخت c_spot_bindings *switch_bindings;

  switch_bindings = XNEW (ساخت c_spot_bindings);
  سیٹ_spot_bindings (switch_bindings, سچ);
  واپس switch_bindings;
}

خالی
c_release_switch_bindings (ساخت c_spot_bindings *bindings)
{
  gcc_assert (bindings->stmt_exprs == 0 && !bindings->بایاں_stmt_اظہاریہ);
  XDELETE (bindings);
}

/* This is called at the point of a case or default label to issue
   warnings about decls as needed.  It returns true if it found an
   error, not just a warning.  */

منطقی
c_check_switch_jump_warnings (ساخت c_spot_bindings *switch_bindings,
			      location_t switch_loc, location_t case_loc)
{
  منطقی saw_error;
  ساخت c_scope *scope;

  saw_error = جھوٹ;
  برائے (scope = current_scope;
       scope != switch_bindings->scope;
       scope = scope->outer)
    {
      ساخت c_binding *b;

      gcc_assert (scope != تہی);

      اگر (!scope->has_jump_unsafe_decl)
	جاری;

      برائے (b = scope->bindings; b != تہی; b = b->پچھلا)
	{
	  اگر (decl_jump_unsafe (b->decl))
	    {
	      auto_diagnostic_گروہ d;
	      منطقی emitted;
	      اگر (c_type_variably_modified_p (درخت_TYPE (b->decl)))
		{
		  saw_error = سچ;
		  error_at (case_loc,
			    "switch jumps into scope of identifier with "
			    "variably modified type");
		  emitted = سچ;
		}
	      ورنہ اگر (flag_openmp
		       && lookup_attribute ("omp allocate",
					    DECL_اوصاف (b->decl)))
		{
		  saw_error = سچ;
		  error_at (case_loc,
			    "switch jumps over OpenMP %<allocate%> allocation");
		  emitted = سچ;
		}
	      ورنہ
		emitted
		  = warning_at (case_loc, OPT_Wjump_ناکامیاں_init,
				"switch jumps over variable initialization");
	      اگر (emitted)
		{
		  inform (switch_loc, "switch starts here");
		  inform (DECL_ماخذ_LOCATION (b->decl), "%qD declared here",
			  b->decl);
		}
	    }
	}
    }

  اگر (switch_bindings->stmt_exprs > 0)
    {
      saw_error = سچ;
      auto_diagnostic_گروہ d;
      error_at (case_loc, "switch jumps into statement expression");
      inform (switch_loc, "switch starts here");
    }

  واپس saw_error;
}

/* Given NAME, an IDENTIFIER_NODE,
   return the structure (or union or enum) definition for that name.
   If THISLEVEL_ONLY is nonzero, searches only the current_scope.
   CODE says which kind of type the caller wants;
   it is RECORD_TYPE or UNION_TYPE or ENUMERAL_TYPE.
   If PLOC is not NULL and this returns non-null, it sets *PLOC to the
   location where the tag was defined.
   If the wrong kind of type is found, an error is reported.  */

ساکن درخت
lookup_لیبل (شمار درخت_رمز_2 رمز, درخت name, منطقی thislevel_only,
	    location_t *ploc)
{
  ساخت c_binding *b = I_لیبل_BINDING (name);
  منطقی thislevel = جھوٹ;

  اگر (!b || !b->decl)
    واپس NULL_درخت;

  /* We only care about whether it's in this level if
     thislevel_only was set or it might be a type clash.  */
  اگر (thislevel_only || درخت_رمز (b->decl) != رمز)
    {
      /* For our purposes, a tag in the external scope is the same as
	 a tag in the file scope.  (Primarily relevant to Objective-C
	 and its builtin structure tags, which get pushed before the
	 file scope is created.)  */
      اگر (B_اندر_CURRENT_SCOPE (b)
	  || (current_scope == file_scope && B_اندر_EXTERNAL_SCOPE (b)))
	thislevel = سچ;
    }

  اگر (thislevel_only && !thislevel)
    واپس NULL_درخت;

  اگر (درخت_رمز (b->decl) != رمز)
    {
      /* Definition isn't the kind we were looking for.  */
      pending_invalid_xref = name;
      pending_invalid_xref_location = داخلہ_location;

      /* If in the same binding level as a declaration as a tag
	 of a different type, this must not be allowed to
	 shadow that tag, so give the error immediately.
	 (For example, "struct foo; union foo;" is invalid.)  */
      اگر (thislevel)
	pending_xref_error ();
    }

  اگر (ploc != تہی)
    *ploc = b->locus;

  واپس b->decl;
}

/* Return true if a definition exists for NAME with code CODE.  */

منطقی
لیبل_exists_p (شمار درخت_رمز_2 رمز, درخت name)
{
  ساخت c_binding *b = I_لیبل_BINDING (name);

  اگر (b == تہی || b->decl == NULL_درخت)
    واپس جھوٹ;
  واپس درخت_رمز (b->decl) == رمز;
}

/* Print an error message now
   for a recent invalid struct, union or enum cross reference.
   We don't print them immediately because they are not invalid
   when used in the `struct foo;' construct for shadowing.  */

خالی
pending_xref_error (خالی)
{
  اگر (pending_invalid_xref != NULL_درخت)
    error_at (pending_invalid_xref_location, "%qE defined as wrong kind of tag",
	      pending_invalid_xref);
  pending_invalid_xref = NULL_درخت;
}


/* Look up NAME in the current scope and its superiors
   in the namespace of variables, functions and typedefs.
   Return a ..._DECL node of some kind representing its definition,
   or return NULL_TREE if it is undefined.  */

درخت
lookup_name (درخت name)
{
  ساخت c_binding *b = I_علامت_BINDING (name);
  /* Do not resolve non-default function versions.  */
  اگر (b
      && درخت_رمز (b->decl) == FUNCTION_DECL
      && DECL_FUNCTION_VERSIONED (b->decl)
      && !is_function_default_نسخہ (b->decl))
    واپس NULL_درخت;
  اگر (b && !b->invisible)
    {
      maybe_ریکارڈ_typedef_use (b->decl);
      واپس b->decl;
    }
  واپس NULL_درخت;
}

/* Similar to `lookup_name' but look only at the indicated scope.  */

ساکن درخت
lookup_name_اندر_scope (درخت name, ساخت c_scope *scope)
{
  ساخت c_binding *b;

  برائے (b = I_علامت_BINDING (name); b; b = b->shadowed)
    اگر (B_اندر_SCOPE (b, scope))
      واپس b->decl;
  واپس NULL_درخت;
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
lookup_name_fuzzy (درخت name, شمار lookup_name_fuzzy_قسم قسم, location_t loc)
{
  gcc_assert (درخت_رمز (name) == IDENTIFIER_گرہ);

  /* Look up function-like macros first; maybe misusing them. */
  خودکار cpp_گرہ = cpp_lookup (parse_اندر,
			      (ثابت غیرعلامتی حرف*)IDENTIFIER_اشارہ_گر (name),
			      IDENTIFIER_لمبائی (name));
  اگر (cpp_گرہ && cpp_fun_like_macro_p (cpp_گرہ))
    واپس name_hint
      (خالی_اشاریہ,
       std::make_unique<macro_like_function_مستعمل> (loc,
						   IDENTIFIER_اشارہ_گر (name)));

  /* Next, try some well-known names in the C standard library, in case
     the user forgot a #include.  */
  ثابت حرف *سرخی_hint
    = get_c_stdlib_سرخی_for_name (IDENTIFIER_اشارہ_گر (name));

  اگر (سرخی_hint)
    واپس name_hint
      (خالی_اشاریہ,
       std::make_unique<suggest_missing_سرخی> (loc,
						 IDENTIFIER_اشارہ_گر (name),
						 سرخی_hint));

  /* Next, look for exact matches for builtin defines that would have been
     defined if the user had passed a command-line option (e.g. -fopenmp
     for "_OPENMP").  */
  diagnostics::option_id option_id
    = get_option_for_builtin_define (IDENTIFIER_اشارہ_گر (name));
  اگر (option_id.m_idx > 0)
    واپس name_hint
      (خالی_اشاریہ,
       std::make_unique<suggest_missing_option> (loc,
						 IDENTIFIER_اشارہ_گر (name),
						 option_id));

  /* Only suggest names reserved for the implementation if NAME begins
     with an underscore.  */
  منطقی consider_implementation_نام = (IDENTIFIER_اشارہ_گر (name)[0] == '_');

  بہترین_مطابقت<درخت, درخت> bm (name);

  /* Look within currently valid scopes.  */
  برائے (c_scope *scope = current_scope; scope; scope = scope->outer)
    برائے (c_binding *binding = scope->bindings; binding; binding = binding->پچھلا)
      {
	اگر (!binding->id || binding->invisible)
	  جاری;
	اگر (binding->decl == error_mark_گرہ)
	  جاری;
	/* Don't use bindings from implicitly declared functions,
	   as they were likely misspellings themselves.  */
	اگر (درخت_رمز (binding->decl) == FUNCTION_DECL)
	  اگر (C_DECL_IMPLICIT (binding->decl))
	    جاری;
	/* Don't suggest names that are reserved for use by the
	   implementation, unless NAME began with an underscore.  */
	اگر (!consider_implementation_نام)
	  {
	    ثابت حرف *suggestion_str = IDENTIFIER_اشارہ_گر (binding->id);
	    اگر (name_reserved_for_implementation_p (suggestion_str))
	      جاری;
	  }
	انتخاب (قسم)
	  {
	  حالت FUZZY_LOOKUP_TYPENAME:
	    اگر (درخت_رمز (binding->decl) != TYPE_DECL)
	      جاری;
	    توڑو;

	  حالت FUZZY_LOOKUP_FUNCTION_NAME:
	    اگر (درخت_رمز (binding->decl) != FUNCTION_DECL)
	      {
		/* Allow function pointers.  */
		اگر ((VAR_P (binding->decl)
		     || درخت_رمز (binding->decl) == PARM_DECL)
		    && درخت_رمز (درخت_TYPE (binding->decl)) == اشارہ_گر_TYPE
		    && (درخت_رمز (درخت_TYPE (درخت_TYPE (binding->decl)))
			== FUNCTION_TYPE))
		  توڑو;
		جاری;
	      }
	    توڑو;

	  طےشدہ:
	    توڑو;
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
  بہترین_macro_مطابقت bmm (name, bm.get_بہترین_فاصلہ (), parse_اندر);
  cpp_hashnode *بہترین_macro = bmm.get_بہترین_meaningful_candidate ();
  /* If a macro is the closest so far to NAME, use it, creating an
     identifier tree node for it.  */
  اگر (بہترین_macro)
    {
      ثابت حرف *id = (ثابت حرف *)بہترین_macro->ident.str;
      درخت macro_as_identifier
	= get_identifier_with_لمبائی (id, بہترین_macro->ident.len);
      bm.سیٹ_بہترین_so_far (macro_as_identifier,
			  bmm.get_بہترین_فاصلہ (),
			  bmm.get_بہترین_candidate_لمبائی ());
    }

  /* Try the "start_typename" keywords to detect
     "singed" vs "signed" typos.  */
  اگر (قسم == FUZZY_LOOKUP_TYPENAME)
    {
      برائے (غیرعلامتی i = 0; i < عدد_c_common_reswords; i++)
	{
	  ثابت c_common_resword *resword = &c_common_reswords[i];
	  اگر (!c_keyword_starts_typename (resword->rid))
	    جاری;
	  درخت resword_identifier = ridpointers [resword->rid];
	  اگر (!resword_identifier)
	    جاری;
	  gcc_assert (درخت_رمز (resword_identifier) == IDENTIFIER_گرہ);
	  bm.consider (resword_identifier);
	}
    }

  درخت بہترین = bm.get_بہترین_meaningful_candidate ();
  اگر (بہترین)
    واپس name_hint (IDENTIFIER_اشارہ_گر (بہترین), تہی);
  ورنہ
    واپس name_hint (تہی, تہی);
}


/* Handle the standard [[nodiscard]] attribute.  */

ساکن درخت
handle_nodiscard_attribute (درخت *گرہ, درخت name, درخت /*دلائل*/,
			    صحیح /*flags*/, منطقی *no_جوڑو_attrs)
{
  اگر (درخت_رمز (*گرہ) == FUNCTION_DECL)
    {
      اگر (VOID_TYPE_P (درخت_TYPE (درخت_TYPE (*گرہ))))
	warning_at (DECL_ماخذ_LOCATION (*گرہ),
		    OPT_Wattributes, "%qE attribute applied to %qD with void "
		    "return type", name, *گرہ);
    }
  ورنہ اگر (ریکارڈ_OR_UNION_TYPE_P (*گرہ)
	   || درخت_رمز (*گرہ) == ENUMERAL_TYPE)
    /* OK */;
  ورنہ
    {
      pedwarn (داخلہ_location,
	       OPT_Wattributes, "%qE attribute can only be applied to "
	       "functions or to structure, union or enumeration types", name);
      *no_جوڑو_attrs = سچ;
    }
  واپس NULL_درخت;
}

/* Handle the standard [[noreturn]] attribute.  */

ساکن درخت
handle_std_noreturn_attribute (درخت *گرہ, درخت name, درخت دلائل,
			       صحیح flags, منطقی *no_جوڑو_attrs)
{
  /* Unlike GNU __attribute__ ((noreturn)), the standard [[noreturn]]
     only applies to functions, not function pointers.  */
  اگر (درخت_رمز (*گرہ) == FUNCTION_DECL)
    واپس handle_noreturn_attribute (گرہ, name, دلائل, flags, no_جوڑو_attrs);
  ورنہ
    {
      pedwarn (داخلہ_location, OPT_Wattributes,
	       "standard %qE attribute can only be applied to functions",
	       name);
      *no_جوڑو_attrs = سچ;
      واپس NULL_درخت;
    }
}

/* Handle the standard [[unsequenced]] attribute.  */

ساکن درخت
handle_std_unsequenced_attribute (درخت *گرہ, درخت name, درخت دلائل,
				  صحیح flags, منطقی *no_جوڑو_attrs)
{
  /* Unlike GNU __attribute__ ((unsequenced)), the standard [[unsequenced]]
     should be only applied to function declarators or type specifiers which
     have function type.  */
  اگر (گرہ[2])
    {
      auto_diagnostic_گروہ d;
      اگر (pedwarn (داخلہ_location, OPT_Wattributes,
		   "standard %qE attribute can only be applied to function "
		   "declarators or type specifiers with function type", name))
	inform (داخلہ_location, "did you mean to specify it after %<)%> "
				"following function parameters?");
      *no_جوڑو_attrs = سچ;
      واپس NULL_درخت;
    }
  واپس handle_unsequenced_attribute (گرہ, name, دلائل, flags, no_جوڑو_attrs);
}

/* Handle the standard [[reproducible]] attribute.  */

ساکن درخت
handle_std_reproducible_attribute (درخت *گرہ, درخت name, درخت دلائل,
				   صحیح flags, منطقی *no_جوڑو_attrs)
{
  واپس handle_std_unsequenced_attribute (گرہ, name, دلائل, flags,
					   no_جوڑو_attrs);
}

/* Table of supported standard (C23) attributes.  */
ساکن ثابت attribute_spec std_اوصاف[] =
{
  /* { name, min_len, max_len, decl_req, type_req, fn_type_req,
       affects_type_identity, handler, exclude } */
  { "_Noreturn", 0, 0, جھوٹ, جھوٹ, جھوٹ, جھوٹ,
    handle_std_noreturn_attribute, تہی },
  { "deprecated", 0, 1, جھوٹ, جھوٹ, جھوٹ, جھوٹ,
    handle_deprecated_attribute, تہی },
  { "fallthrough", 0, 0, جھوٹ, جھوٹ, جھوٹ, جھوٹ,
    handle_fallthrough_attribute, تہی },
  { "maybe_unused", 0, 0, جھوٹ, جھوٹ, جھوٹ, جھوٹ,
    handle_غیر_مستعمل_attribute, تہی },
  { "nodiscard", 0, 1, جھوٹ, جھوٹ, جھوٹ, جھوٹ,
    handle_nodiscard_attribute, تہی },
  { "noreturn", 0, 0, جھوٹ, جھوٹ, جھوٹ, جھوٹ,
    handle_std_noreturn_attribute, تہی },
  { "reproducible", 0, 0, جھوٹ, سچ, سچ, جھوٹ,
    handle_std_reproducible_attribute, تہی },
  { "unsequenced", 0, 0, جھوٹ, سچ, سچ, جھوٹ,
    handle_std_unsequenced_attribute, تہی }
};

ثابت scoped_attribute_specs std_attribute_جدول =
{
  خالی_اشاریہ, { std_اوصاف }
};

/* Create the predefined scalar types of C,
   and some nodes representing standard constants (0, 1, (void *) 0).
   Initialize the global scope.
   Make definitions for built-in primitive functions.  */

خالی
c_init_decl_processing (خالی)
{
  location_t save_loc = داخلہ_location;

  /* Initialize reserved words for parser.  */
  c_parse_init ();

  current_function_decl = NULL_درخت;

  gcc_obstack_init (&parser_obstack);

  /* Make the externals scope.  */
  ڈالو_scope ();
  external_scope = current_scope;

  /* Declarations from c_common_nodes_and_builtins must not be associated
     with this input file, lest we get differences between using and not
     using preprocessed headers.  */
  داخلہ_location = BUILTINS_LOCATION;

  c_common_nodes_and_builtins ();

  /* In C, comparisons and TRUTH_* expressions have type int.  */
  truthvalue_type_گرہ = integer_type_گرہ;
  truthvalue_true_گرہ = integer_one_گرہ;
  truthvalue_false_گرہ = integer_zero_گرہ;

  /* Even in C99, which has a real boolean type.  */
  pushdecl (build_decl (UNKNOWN_LOCATION, TYPE_DECL,
			get_identifier (flag_isoc23 ? "bool" : "_Bool"),
			boolean_type_گرہ));

  /* C-specific nullptr initialization.  */
  ریکارڈ_builtin_type (RID_MAX, "typeof (nullptr)", nullptr_type_گرہ);
  /* The size and alignment of nullptr_t is the same as for a pointer to
     character type.  */
  سیٹ_TYPE_ALIGN (nullptr_type_گرہ, GET_منوال_ALIGNMENT (ptr_منوال));

  داخلہ_location = save_loc;

  make_fname_decl = c_make_fname_decl;
  آغاز_fname_decls ();

  اگر (warn_keyword_macro)
    {
      برائے (غیرعلامتی صحیح i = 0; i < عدد_c_common_reswords; ++i)
	/* For C register keywords which don't start with underscore
	   or start with just single underscore.  Don't complain about
	   ObjC or Transactional Memory keywords.  */
	اگر (c_common_reswords[i].لفظ[0] == '_'
	    && c_common_reswords[i].لفظ[1] == '_')
	  جاری;
	ورنہ اگر (c_common_reswords[i].disable
		 & (D_TRANSMEM | D_OBJC | D_CXX_OBJC))
	  جاری;
	ورنہ
	  {
	    درخت id = get_identifier (c_common_reswords[i].لفظ);
	    اگر (C_IS_RESERVED_لفظ (id)
		&& C_RID_رمز (id) != RID_CXX_COMPAT_WARN)
	      cpp_warn (parse_اندر, IDENTIFIER_اشارہ_گر (id),
			IDENTIFIER_لمبائی (id));
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

ساکن درخت
c_make_fname_decl (location_t loc, درخت id, صحیح type_dep)
{
  ثابت حرف *name = fname_as_string (type_dep);
  درخت decl, type, init;
  سائز_t لمبائی = لڑی_لمبائی (name);

  type = c_build_array_type (char_type_گرہ,
			     build_اشاریہ_type (سائز_int (لمبائی)));
  type = c_build_qualified_type (type, TYPE_QUAL_CONST);

  decl = build_decl (loc, VAR_DECL, id, type);

  درخت_STATIC (decl) = 1;
  درخت_READONLY (decl) = 1;
  DECL_ARTIFICIAL (decl) = 1;

  init = build_string (لمبائی + 1, name);
  آزاد (const_cast<حرف *> (name));
  درخت_TYPE (init) = type;
  DECL_INITIAL (decl) = init;

  درخت_مستعمل (decl) = 1;

  اگر (current_function_decl
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
	    /*invisible=*/جھوٹ, /*nested=*/جھوٹ, UNKNOWN_LOCATION);
    }

  اختتام_decl (decl, loc, init, NULL_درخت, NULL_درخت);

  واپس decl;
}

درخت
c_builtin_function (درخت decl)
{
  درخت type = درخت_TYPE (decl);
  درخت   id = DECL_NAME (decl);

  ثابت حرف *name = IDENTIFIER_اشارہ_گر (id);
  C_DECL_BUILTIN_PROTOTYPE (decl) = prototype_p (type);

  /* Should never be called on a symbol with a preexisting meaning.  */
  gcc_assert (!I_علامت_BINDING (id));

  bind (id, decl, external_scope, /*invisible=*/سچ, /*nested=*/جھوٹ,
	UNKNOWN_LOCATION);

  /* Builtins in the implementation namespace are made visible without
     needing to be explicitly declared.  See push_file_scope.  */
  اگر (name[0] == '_' && (name[1] == '_' || ISUPPER (name[1])))
    {
      DECL_CHAIN (decl) = visible_builtins;
      visible_builtins = decl;
    }

  واپس decl;
}

درخت
c_builtin_function_ext_scope (درخت decl)
{
  درخت type = درخت_TYPE (decl);
  درخت   id = DECL_NAME (decl);

  ثابت حرف *name = IDENTIFIER_اشارہ_گر (id);
  C_DECL_BUILTIN_PROTOTYPE (decl) = prototype_p (type);

  اگر (external_scope)
    bind (id, decl, external_scope, /*invisible=*/جھوٹ, /*nested=*/جھوٹ,
	  UNKNOWN_LOCATION);

  /* Builtins in the implementation namespace are made visible without
     needing to be explicitly declared.  See push_file_scope.  */
  اگر (name[0] == '_' && (name[1] == '_' || ISUPPER (name[1])))
    {
      DECL_CHAIN (decl) = visible_builtins;
      visible_builtins = decl;
    }

  واپس decl;
}

/* Implement LANG_HOOKS_SIMULATE_BUILTIN_FUNCTION_DECL.  */

درخت
c_simulate_builtin_function_decl (درخت decl)
{
  درخت type = درخت_TYPE (decl);
  C_DECL_BUILTIN_PROTOTYPE (decl) = prototype_p (type);
  واپس pushdecl (decl);
}

/* Warn about attributes in a context where they are unused
   (attribute-declarations, except for the "fallthrough" case, and
   attributes on statements).  */

خالی
c_warn_غیر_مستعمل_اوصاف (درخت attrs)
{
  برائے (درخت t = attrs; t != NULL_درخت; t = درخت_CHAIN (t))
    اگر (get_attribute_namespace (t) == NULL_درخت)
      /* The specifications of standard attributes mean this is a
	 constraint violation.  */
      pedwarn (داخلہ_location, OPT_Wattributes, "%qE attribute ignored",
	       get_attribute_name (t));
    ورنہ اگر (!attribute_ignored_p (t))
      warning (OPT_Wattributes, "%qE attribute ignored",
	       get_attribute_name (t));
}

/* Warn for standard attributes being applied to a type that is not
   being defined, where that is a constraint violation, and return a
   list of attributes with them removed.  */

درخت
c_warn_type_اوصاف (درخت type, درخت attrs)
{
  درخت *attr_ptr = &attrs;
  جب (*attr_ptr)
    اگر (get_attribute_namespace (*attr_ptr) == NULL_درخت)
      {
	اگر (درخت_رمز (type) == FUNCTION_TYPE)
	  {
	    درخت name = get_attribute_name (*attr_ptr);
	    /* [[unsequenced]] and [[reproducible]] is fine on function
	       types that aren't being defined.  */
	    اگر (is_attribute_p ("unsequenced", name)
		|| is_attribute_p ("reproducible", name))
	      {
		attr_ptr = &درخت_CHAIN (*attr_ptr);
		جاری;
	      }
	  }
	pedwarn (داخلہ_location, OPT_Wattributes, "%qE attribute ignored",
		 get_attribute_name (*attr_ptr));
	*attr_ptr = درخت_CHAIN (*attr_ptr);
      }
    ورنہ
      attr_ptr = &درخت_CHAIN (*attr_ptr);
  واپس attrs;
}

/* Called when a declaration is seen that contains no names to declare.
   If its type is a reference to a structure, union or enum inherited
   from a containing scope, shadow that tag name for the current scope
   with a forward reference.
   If its type defines a new named structure or union
   or defines an enum, it is valid but we need not do anything here.
   Otherwise, it is an error.  */

خالی
shadow_لیبل (ثابت ساخت c_declspecs *declspecs)
{
  shadow_لیبل_warned (declspecs, 0);
}

/* WARNED is 1 if we have done a pedwarn, 2 if we have done a warning,
   but no pedwarn.  */
خالی
shadow_لیبل_warned (ثابت ساخت c_declspecs *declspecs, صحیح warned)
{
  منطقی ملا_لیبل = جھوٹ;

  اگر (declspecs->type && !declspecs->default_int_p && !declspecs->typedef_p)
    {
      درخت قدر = declspecs->type;
      شمار درخت_رمز_2 رمز = درخت_رمز (قدر);

      اگر (رمز == ریکارڈ_TYPE || رمز == UNION_TYPE || رمز == ENUMERAL_TYPE)
	/* Used to test also that TYPE_SIZE (value) != 0.
	   That caused warning for `struct foo;' at top level in the file.  */
	{
	  درخت name = TYPE_NAME (قدر);
	  درخت t;

	  ملا_لیبل = سچ;

	  اگر (declspecs->restrict_p)
	    {
	      error ("invalid use of %<restrict%>");
	      warned = 1;
	    }

	  اگر (اندر_underspecified_init)
	    {
	      /* This can only occur with extensions such as statement
		 expressions, but is still appropriate as an error to
		 avoid types declared in such a context escaping to
		 the type of an auto variable.  */
	      error ("%qT declared in underspecified object initializer",
		     قدر);
	      warned = 1;
	    }

	  اگر (name == NULL_درخت)
	    {
	      اگر (warned != 1 && رمز != ENUMERAL_TYPE)
		/* Empty unnamed enum OK */
		{
		  pedwarn (داخلہ_location, 0,
			   "unnamed struct/union that defines no instances");
		  warned = 1;
		}
	    }
	  ورنہ اگر (declspecs->typespec_قسم != ctsk_tagdef
                   && declspecs->typespec_قسم != ctsk_tagfirstref
		   && declspecs->typespec_قسم != ctsk_tagfirstref_attrs
		   && declspecs->storage_class != csc_none)
	    {
	      اگر (warned != 1)
		pedwarn (داخلہ_location, 0,
			 "empty declaration with storage class specifier "
			 "does not redeclare tag");
	      warned = 1;
	      pending_xref_error ();
	    }
	  ورنہ اگر (declspecs->typespec_قسم != ctsk_tagdef
                   && declspecs->typespec_قسم != ctsk_tagfirstref
                   && declspecs->typespec_قسم != ctsk_tagfirstref_attrs
		   && (declspecs->const_p
		       || declspecs->volatile_p
		       || declspecs->atomic_p
		       || declspecs->restrict_p
		       || declspecs->پتہ_space))
	    {
	      اگر (warned != 1)
		pedwarn (داخلہ_location, 0,
			 "empty declaration with type qualifier "
			  "does not redeclare tag");
	      warned = 1;
	      pending_xref_error ();
	    }
	  ورنہ اگر (declspecs->typespec_قسم != ctsk_tagdef
                   && declspecs->typespec_قسم != ctsk_tagfirstref
                   && declspecs->typespec_قسم != ctsk_tagfirstref_attrs
		   && declspecs->alignas_p)
	    {
	      اگر (warned != 1)
		pedwarn (داخلہ_location, 0,
			 "empty declaration with %<_Alignas%> "
			  "does not redeclare tag");
	      warned = 1;
	      pending_xref_error ();
	    }
	  ورنہ اگر (declspecs->typespec_قسم != ctsk_tagdef
		   && declspecs->typespec_قسم != ctsk_tagfirstref
		   && declspecs->typespec_قسم != ctsk_tagfirstref_attrs
		   && رمز == ENUMERAL_TYPE
		   && !declspecs->enum_type_specifier_ref_p)
	    {
	      منطقی warned_enum = جھوٹ;
	      اگر (warned != 1)
		warned_enum = pedwarn (داخلہ_location, OPT_Wpedantic,
				       "empty declaration of %<enum%> type "
				       "does not redeclare tag");
	      اگر (warned_enum)
		warned = 1;
	      pending_xref_error ();
	    }
	  ورنہ
	    {
	      pending_invalid_xref = NULL_درخت;
	      t = lookup_لیبل (رمز, name, سچ, تہی);

	      اگر (t == NULL_درخت)
		{
		  t = make_گرہ (رمز);
		  اگر (flag_isoc23 || رمز == ENUMERAL_TYPE)
		    سیٹ_TYPE_STRUCTURAL_EQUALITY (t);
		  pushtag (داخلہ_location, name, t);
		}
	    }
	}
      ورنہ
	{
	  اگر (warned != 1 && !اندر_system_سرخی_at (داخلہ_location))
	    {
	      pedwarn (داخلہ_location, 0,
		       "useless type name in empty declaration");
	      warned = 1;
	    }
	}
    }
  ورنہ اگر (warned != 1 && !اندر_system_سرخی_at (داخلہ_location)
	   && declspecs->typedef_p)
    {
      pedwarn (داخلہ_location, 0, "useless type name in empty declaration");
      warned = 1;
    }

  pending_invalid_xref = NULL_درخت;

  اگر (declspecs->inline_p)
    {
      error ("%<inline%> in empty declaration");
      warned = 1;
    }

  اگر (declspecs->noreturn_p)
    {
      error ("%<_Noreturn%> in empty declaration");
      warned = 1;
    }

  اگر (declspecs->constexpr_p)
    {
      error ("%<constexpr%> in empty declaration");
      warned = 1;
    }

  اگر (current_scope == file_scope && declspecs->storage_class == csc_auto)
    {
      error ("%<auto%> in file-scope empty declaration");
      warned = 1;
    }

  اگر (current_scope == file_scope && declspecs->storage_class == csc_رجسٹر)
    {
      error ("%<register%> in file-scope empty declaration");
      warned = 1;
    }

  اگر (declspecs->enum_type_specifier_ref_p && !warned)
    {
      اگر (declspecs->storage_class != csc_none)
	{
	  error ("storage class specifier in empty declaration with %<enum%> "
		 "underlying type");
	  warned = 1;
	}
      ورنہ اگر (declspecs->thread_p)
	{
	  error ("%qs in empty declaration with %<enum%> underlying type",
		 declspecs->thread_gnu_p ? "__thread" : "_Thread_local");
	  warned = 1;
	}
      ورنہ اگر (declspecs->const_p
	       || declspecs->volatile_p
	       || declspecs->atomic_p
	       || declspecs->restrict_p
	       || declspecs->پتہ_space)
	{
	  error ("type qualifier in empty declaration with %<enum%> "
		 "underlying type");
	  warned = 1;
	}
      ورنہ اگر (declspecs->alignas_p)
	{
	  error ("%<alignas%> in empty declaration with %<enum%> "
		 "underlying type");
	  warned = 1;
	}
    }

  اگر (!warned && !اندر_system_سرخی_at (داخلہ_location)
      && declspecs->storage_class != csc_none)
    {
      warning (0, "useless storage class specifier in empty declaration");
      warned = 2;
    }

  اگر (!warned && !اندر_system_سرخی_at (داخلہ_location) && declspecs->thread_p)
    {
      warning (0, "useless %qs in empty declaration",
	       declspecs->thread_gnu_p ? "__thread" : "_Thread_local");
      warned = 2;
    }

  اگر (!warned
      && !اندر_system_سرخی_at (داخلہ_location)
      && (declspecs->const_p
	  || declspecs->volatile_p
	  || declspecs->atomic_p
	  || declspecs->restrict_p
	  || declspecs->پتہ_space))
    {
      warning (0, "useless type qualifier in empty declaration");
      warned = 2;
    }

  اگر (!warned && !اندر_system_سرخی_at (داخلہ_location)
      && declspecs->alignas_p)
    {
      warning (0, "useless %<_Alignas%> in empty declaration");
      warned = 2;
    }

  اگر (ملا_لیبل
      && warned == 2
      && (declspecs->typespec_قسم == ctsk_tagref_attrs
	  || declspecs->typespec_قسم == ctsk_tagfirstref_attrs))
    {
      /* Standard attributes after the "struct" or "union" keyword are
	 only permitted when the contents of the type are defined, or
	 in the form "struct-or-union attribute-specifier-sequence
	 identifier;".  If the ';' was not present, attributes were
	 diagnosed in the parser.  Here, ensure that any other useless
	 elements of the declaration result in a pedwarn, not just a
	 warning.  Forward declarations of enum types are not part of
	 standard C, but handle them the same.  */
      pedwarn (داخلہ_location, 0,
	       "invalid use of attributes in empty declaration");
      warned = 1;
    }

  اگر (warned != 1)
    {
      اگر (declspecs->declspecs_نظر_آیا_p
	  && !declspecs->non_std_attrs_نظر_آیا_p)
	/* An attribute declaration (but not a fallthrough attribute
	   declaration, which was handled separately); warn if there
	   are any attributes being ignored (but not if the attributes
	   were empty).  */
	c_warn_غیر_مستعمل_اوصاف (declspecs->attrs);
      ورنہ اگر (!ملا_لیبل)
	pedwarn (داخلہ_location, 0, "empty declaration");
    }
}


/* Return the qualifiers from SPECS as a bitwise OR of TYPE_QUAL_*
   bits.  SPECS represents declaration specifiers that the grammar
   only permits to contain type qualifiers and attributes.  */

صحیح
quals_from_declspecs (ثابت ساخت c_declspecs *specs)
{
  صحیح quals = ((specs->const_p ? TYPE_QUAL_CONST : 0)
	       | (specs->volatile_p ? TYPE_QUAL_VOLATILE : 0)
	       | (specs->restrict_p ? TYPE_QUAL_RESTRICT : 0)
	       | (specs->atomic_p ? TYPE_QUAL_ATOMIC : 0)
	       | (ENCODE_QUAL_ADDR_SPACE (specs->پتہ_space)));
  gcc_assert (!specs->type
	      && !specs->decl_attr
	      && specs->typespec_لفظ == cts_none
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
  واپس quals;
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

ساخت c_declarator *
build_array_declarator (location_t loc,
			درخت اظہاریہ, ساخت c_declspecs *quals, منطقی static_p,
			منطقی vla_unspec_p)
{
  ساخت c_declarator *declarator = XOBNEW (&parser_obstack,
					    ساخت c_declarator);
  declarator->id_loc = loc;
  declarator->قسم = cdk_array;
  declarator->declarator = 0;
  declarator->u.array.dimen = اظہاریہ;
  اگر (quals)
    {
      declarator->u.array.attrs = quals->attrs;
      declarator->u.array.quals = quals_from_declspecs (quals);
    }
  ورنہ
    {
      declarator->u.array.attrs = NULL_درخت;
      declarator->u.array.quals = 0;
    }
  declarator->u.array.static_p = static_p;
  declarator->u.array.vla_unspec_p = vla_unspec_p;
  اگر (static_p || quals != تہی)
    pedwarn_c90 (loc, OPT_Wpedantic,
		 "ISO C90 does not support %<static%> or type "
		 "qualifiers in parameter array declarators");
  اگر (vla_unspec_p)
    {
      pedwarn_c90 (loc, OPT_Wpedantic,
		   "ISO C90 does not support %<[*]%> array declarators");
      اگر (current_scope->parm_flag)
	current_scope->had_vla_unspec = سچ;
    }
  واپس declarator;
}

/* Set the contained declarator of an array declarator.  DECL is the
   declarator, as constructed by build_array_declarator; INNER is what
   appears on the left of the [].  */

ساخت c_declarator *
سیٹ_array_declarator_inner (ساخت c_declarator *decl,
			    ساخت c_declarator *inner)
{
  decl->declarator = inner;
  واپس decl;
}

/* Determine whether TYPE is a one-element array type "[1]".  */
ساکن منطقی
one_element_array_type_p (const_درخت type)
{
  اگر (درخت_رمز (type) != ARRAY_TYPE)
    واپس جھوٹ;
  واپس integer_zerop (array_type_nelts_minus_one (type));
}

/* Determine whether TYPE is a zero-length array type "[0]".  */
منطقی
zero_لمبائی_array_type_p (const_درخت type)
{
  اگر (درخت_رمز (type) == ARRAY_TYPE
      && COMPLETE_TYPE_P (type)
      && TYPE_DOMAIN (type) != NULL_درخت
      && (TYPE_MAX_قدر (TYPE_DOMAIN (type)) == NULL_درخت
	  || integer_all_onesp (TYPE_MAX_قدر (TYPE_DOMAIN (type)))))
    واپس سچ;
  واپس جھوٹ;
}

/* INIT is a constructor that forms DECL's initializer.  If the final
   element initializes a flexible array field, adjust the size of the
   DECL with the initializer based on whether the DECL is a union or
   a structure.  */

ساکن خالی
جوڑو_flexible_array_elts_مقصد_سائز (درخت decl, درخت init)
{
  درخت elt, type;

  اگر (vec_محفوظ_is_خالی_خانے (CONSTRUCTOR_ELTS (init)))
    واپس;

  elt = CONSTRUCTOR_ELTS (init)->آخری ().قدر;
  type = درخت_TYPE (elt);
  اگر (flexible_array_member_type_p (type))
    {
      complete_array_type (&type, elt, جھوٹ);
      /* For a structure, add the size of the initializer to the DECL's
	 size.  */
      اگر (درخت_رمز (درخت_TYPE (decl)) == ریکارڈ_TYPE)
	{
	  DECL_سائز (decl)
	    = سائز_binop (PLUS_اظہاریہ, DECL_سائز (decl), TYPE_سائز (type));
	  DECL_سائز_UNIT (decl)
	    = سائز_binop (PLUS_اظہاریہ, DECL_سائز_UNIT (decl),
			  TYPE_سائز_UNIT (type));
	}
      /* For a union, the DECL's size is the maximum of the current size
	 and the size of the initializer.  */
      ورنہ
	{
	  DECL_سائز (decl)
	    = سائز_binop (MAX_اظہاریہ, DECL_سائز (decl), TYPE_سائز (type));
	  DECL_سائز_UNIT (decl)
	    = سائز_binop (MAX_اظہاریہ, DECL_سائز_UNIT (decl),
			  TYPE_سائز_UNIT (type));
	}
    }
}

/* Decode a "typename", such as "int **", returning a ..._TYPE node.
   Set *EXPR, if EXPR not NULL, to any expression to be evaluated
   before the type name, and set *EXPR_CONST_OPERANDS, if
   EXPR_CONST_OPERANDS not NULL, to indicate whether the type name may
   appear in a constant expression.  */

درخت
groktypename (ساخت c_type_name *type_name, درخت *اظہاریہ,
	      منطقی *اظہاریہ_const_operands)
{
  درخت type;
  درخت attrs = type_name->specs->attrs;

  type_name->specs->attrs = NULL_درخت;

  type = grokdeclarator (type_name->declarator, type_name->specs, TYPENAME,
			 جھوٹ, تہی, &attrs, اظہاریہ, اظہاریہ_const_operands,
			 DEPRECATED_معمول);

  /* Apply attributes.  */
  attrs = c_warn_type_اوصاف (type, attrs);
  decl_اوصاف (&type, attrs, 0);

  واپس type;
}


/* Decode a "typename", such as "int **", returning a ..._TYPE node,
   as for groktypename but setting the context to GENERIC_ASSOC.  */

درخت
grokgenassoc (ساخت c_type_name *type_name)
{
  درخت type;
  درخت attrs = type_name->specs->attrs;

  type_name->specs->attrs = NULL_درخت;

  type = grokdeclarator (type_name->declarator, type_name->specs, GENERIC_ASSOC,
			 جھوٹ, تہی, &attrs, تہی, تہی, DEPRECATED_معمول);

  /* Apply attributes.  */
  attrs = c_warn_type_اوصاف (type, attrs);
  decl_اوصاف (&type, attrs, 0);

  واپس type;
}


/* Looks up the most recent pushed declaration corresponding to DECL.  */

ساکن درخت
lookup_آخری_decl (درخت decl)
{
  درخت آخری_decl = lookup_name (DECL_NAME (decl));
  اگر (!آخری_decl)
    آخری_decl = lookup_name_اندر_scope (DECL_NAME (decl), external_scope);
  واپس آخری_decl;
}

/* Wrapper for decl_attributes that adds some implicit attributes
   to VAR_DECLs or FUNCTION_DECLs.  */

ساکن درخت
c_decl_اوصاف (درخت *گرہ, درخت اوصاف, صحیح flags)
{
  /* Add implicit "omp declare target" attribute if requested.  */
  اگر (vec_محفوظ_لمبائی (current_omp_declare_ہدف_attribute)
      && ((VAR_P (*گرہ) && is_global_var (*گرہ))
	  || درخت_رمز (*گرہ) == FUNCTION_DECL))
    {
      اگر (VAR_P (*گرہ) && !omp_mappable_type (درخت_TYPE (*گرہ)))
	اوصاف = درخت_cons (get_identifier ("omp declare target implicit"),
				NULL_درخت, اوصاف);
      ورنہ
	اوصاف = درخت_cons (get_identifier ("omp declare target"),
				NULL_درخت, اوصاف);
      اگر (درخت_رمز (*گرہ) == FUNCTION_DECL)
	{
	  صحیح device_type
	    = current_omp_declare_ہدف_attribute->آخری ().device_type;
	  device_type = MAX (device_type, 0);
	  اگر ((device_type & OMP_CLAUSE_DEVICE_TYPE_HOST) != 0
	      && !lookup_attribute ("omp declare target host", اوصاف))
	    اوصاف
	      = درخت_cons (get_identifier ("omp declare target host"),
			   NULL_درخت, اوصاف);
	  اگر ((device_type & OMP_CLAUSE_DEVICE_TYPE_NOHOST) != 0
	      && !lookup_attribute ("omp declare target nohost", اوصاف))
	    اوصاف
	      = درخت_cons (get_identifier ("omp declare target nohost"),
			   NULL_درخت, اوصاف);

	  صحیح بالواسطہ
	    = current_omp_declare_ہدف_attribute->آخری ().بالواسطہ;
	  اگر (بالواسطہ && !lookup_attribute ("omp declare target indirect",
					     اوصاف))
	    اوصاف
	      = درخت_cons (get_identifier ("omp declare target indirect"),
			   NULL_درخت, اوصاف);
	}
    }

  اگر (flag_openmp || flag_openmp_simd)
    {
      منطقی diagnosed = جھوٹ;
      برائے (درخت *pa = &اوصاف; *pa; )
	{
	  اگر (is_attribute_namespace_p ("omp", *pa))
	    {
	      درخت name = get_attribute_name (*pa);
	      اگر (is_attribute_p ("directive", name)
		  || is_attribute_p ("sequence", name)
		  || is_attribute_p ("decl", name))
		{
		  ثابت حرف *p = تہی;
		  اگر (درخت_قدر (*pa) == NULL_درخت)
		    p = IDENTIFIER_اشارہ_گر (name);
		  برائے (درخت a = درخت_قدر (*pa); a; a = درخت_CHAIN (a))
		    {
		      درخت d = درخت_قدر (a);
		      gcc_assert (درخت_رمز (d) == C_TOKEN_VEC);
		      اگر (درخت_عوامی (d)
			  && (VAR_P (*گرہ)
			      || درخت_رمز (*گرہ) == FUNCTION_DECL)
			  && c_maybe_parse_omp_decl (*گرہ, d))
			جاری;
		      p = درخت_عوامی (d) ? "decl" : "directive";
		    }
		  اگر (p && !diagnosed)
		    {
		      error ("%<omp::%s%> not allowed to be specified in "
			     "this context", p);
		      diagnosed = سچ;
		    }
		  اگر (p)
		    {
		      *pa = درخت_CHAIN (*pa);
		      جاری;
		    }
		}
	    }
	  pa = &درخت_CHAIN (*pa);
	}
    }

  /* Look up the current declaration with all the attributes merged
     so far so that attributes on the current declaration that's
     about to be pushed that conflict with the former can be detected,
     diagnosed, and rejected as appropriate.  To match the C++ FE, do
     not pass an error_mark_node when we found an undeclared variable.  */
  درخت آخری_decl = lookup_آخری_decl (*گرہ);
  اگر (آخری_decl == error_mark_گرہ)
    آخری_decl = NULL_درخت;
  درخت attr = decl_اوصاف (گرہ, اوصاف, flags, آخری_decl);
  اگر (VAR_P (*گرہ) && DECL_THREAD_LOCAL_P (*گرہ))
    {
      // tls_model attribute can set a stronger TLS access model.
      tls_model model = DECL_TLS_MODEL (*گرہ);
      tls_model default_model = decl_default_tls_model (*گرہ);
      اگر (default_model > model)
	سیٹ_decl_tls_model (*گرہ, default_model);
    }
  واپس attr;
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

درخت
آغاز_decl (ساخت c_declarator *declarator, ساخت c_declspecs *declspecs,
	    منطقی initialized, درخت اوصاف, منطقی do_ڈالو /* = true */,
	    location_t *lastloc /* = NULL */)
{
  درخت decl;
  درخت old_decl;
  درخت tem;
  درخت اظہاریہ = NULL_درخت;
  شمار deprecated_حالتیں deprecated_state = DEPRECATED_معمول;

  /* An object declared as __attribute__((unavailable)) suppresses
     warnings and errors from __attribute__((deprecated/unavailable))
     components.
     An object declared as __attribute__((deprecated)) suppresses
     warnings of uses of other deprecated items.  */
  اگر (lookup_attribute ("unavailable", اوصاف))
    deprecated_state = UNAVAILABLE_DEPRECATED_SUPPRESS;
  ورنہ اگر (lookup_attribute ("deprecated", اوصاف))
    deprecated_state = DEPRECATED_SUPPRESS;

  decl = grokdeclarator (declarator, declspecs,
			 معمول, initialized, تہی, &اوصاف, &اظہاریہ, تہی,
			 deprecated_state);
  اگر (!decl || decl == error_mark_گرہ)
    واپس NULL_درخت;

  old_decl = lookup_آخری_decl (decl);

  اگر (درخت lastdecl = lastloc ? old_decl : NULL_درخت)
    اگر (lastdecl != error_mark_گرہ)
      *lastloc = DECL_ماخذ_LOCATION (lastdecl);

  /* Make sure the size expression is evaluated at this point.  */
  اگر (اظہاریہ && !current_scope->parm_flag)
    جوڑو_stmt (fold_convert (void_type_گرہ, اظہاریہ));

  اگر (درخت_رمز (decl) != FUNCTION_DECL && MAIN_NAME_P (DECL_NAME (decl))
      && درخت_عوامی (decl))
    warning (OPT_Wmain, "%q+D is usually a function", decl);

  اگر (warn_missing_variable_declarations && VAR_P (decl)
      && !DECL_EXTERNAL (decl) && درخت_عوامی (decl) && old_decl == NULL_درخت)
    warning_at (DECL_ماخذ_LOCATION (decl), OPT_Wmissing_variable_declarations,
		"no previous declaration for %qD", decl);

  اگر (initialized)
    /* Is it valid for this decl to have an initializer at all?
       If not, set INITIALIZED to zero, which will indirectly
       tell 'finish_decl' to ignore the initializer once it is parsed.  */
    انتخاب (درخت_رمز (decl))
      {
      حالت TYPE_DECL:
	error ("typedef %qD is initialized (use %<__typeof__%> instead)", decl);
	initialized = جھوٹ;
	توڑو;

      حالت FUNCTION_DECL:
	error ("function %qD is initialized like a variable", decl);
	initialized = جھوٹ;
	توڑو;

      حالت PARM_DECL:
	/* DECL_INITIAL in a PARM_DECL is really DECL_ARG_TYPE.  */
	error ("parameter %qD is initialized", decl);
	initialized = جھوٹ;
	توڑو;

      طےشدہ:
	/* Don't allow initializations for incomplete types except for
	   arrays which might be completed by the initialization.  */

	/* This can happen if the array size is an undefined macro.
	   We already gave a warning, so we don't need another one.  */
	اگر (درخت_TYPE (decl) == error_mark_گرہ)
	  initialized = جھوٹ;
	ورنہ اگر (COMPLETE_TYPE_P (درخت_TYPE (decl)))
	  {
	    /* A complete type is ok if size is fixed.  If the size is
	       variable, an empty initializer is OK and nonempty
	       initializers will be diagnosed in the parser.  */
	  }
	ورنہ اگر (درخت_رمز (درخت_TYPE (decl)) != ARRAY_TYPE)
	  {
	    error ("variable %qD has initializer but incomplete type", decl);
	    initialized = جھوٹ;
	  }
      }

  اگر (initialized)
    {
      اگر (current_scope == file_scope)
	درخت_STATIC (decl) = 1;

      /* Tell 'pushdecl' this is an initialized decl
	 even though we don't yet have the initializer expression.
	 Also tell 'finish_decl' it may store the real initializer.  */
      DECL_INITIAL (decl) = error_mark_گرہ;
    }

  /* If this is a function declaration, write a record describing it to the
     prototypes file (if requested).  */

  اگر (درخت_رمز (decl) == FUNCTION_DECL)
    gen_aux_info_ریکارڈ (decl, 0, 0, prototype_p (درخت_TYPE (decl)));

  /* ANSI specifies that a tentative definition which is not merged with
     a non-tentative definition behaves exactly like a definition with an
     initializer equal to zero.  (Section 3.7.2)

     -fno-common gives strict ANSI behavior, though this tends to break
     a large body of code that grew up without this rule.

     Thread-local variables are never common, since there's no entrenched
     body of code to break, and it allows more efficient variable references
     in the presence of dynamic linking.  */

  اگر (VAR_P (decl)
      && !initialized
      && درخت_عوامی (decl)
      && !DECL_THREAD_LOCAL_P (decl)
      && !flag_no_common)
    DECL_COMMON (decl) = 1;

  /* Set attributes here so if duplicate decl, will have proper attributes.  */
  c_decl_اوصاف (&decl, اوصاف, 0);

  /* Handle gnu_inline attribute.  */
  اگر (declspecs->inline_p
      && !flag_gnu89_inline
      && درخت_رمز (decl) == FUNCTION_DECL
      && (lookup_attribute ("gnu_inline", DECL_اوصاف (decl))
	  || current_function_decl))
    {
      اگر (declspecs->storage_class == csc_auto && current_scope != file_scope)
	;
      ورنہ اگر (declspecs->storage_class != csc_static)
	DECL_EXTERNAL (decl) = !DECL_EXTERNAL (decl);
    }

  اگر (درخت_رمز (decl) == FUNCTION_DECL
      && DECL_DECLARED_INLINE_P (decl)
      && DECL_UNINLINABLE (decl)
      && lookup_attribute ("noinline", DECL_اوصاف (decl)))
    {
      auto_urlify_اوصاف sentinel;
      warning (OPT_Wattributes, "inline function %q+D given attribute %qs",
	       decl, "noinline");
    }

  /* C99 6.7.4p3: An inline definition of a function with external
     linkage shall not contain a definition of a modifiable object
     with static storage duration...  */
  اگر (VAR_P (decl)
      && current_scope != file_scope
      && درخت_STATIC (decl)
      && !درخت_READONLY (decl)
      && DECL_DECLARED_INLINE_P (current_function_decl)
      && DECL_EXTERNAL (current_function_decl))
    ریکارڈ_inline_static (داخلہ_location, current_function_decl,
			  decl, csi_modifiable);

  اگر (c_dialect_objc ()
      && VAR_OR_FUNCTION_DECL_P (decl))
      objc_check_global_decl (decl);

  /* To enable versions to be created across TU's we mark and mangle all
     non-default versioned functions.  */
  اگر (درخت_رمز (decl) == FUNCTION_DECL
      && !ہدف_HAS_FMV_ہدف_ATTRIBUTE
      && get_ہدف_نسخہ (decl).is_valid ())
    {
      maybe_mark_function_versioned (decl);
      اگر (current_scope != file_scope)
	error ("versioned declarations are only allowed at file scope");
    }

  /* Add this decl to the current scope.
     TEM may equal DECL or it may be a previous decl of the same name.  */
  اگر (do_ڈالو)
    {
      tem = pushdecl (decl);

      اگر (initialized && DECL_EXTERNAL (tem))
	{
	  DECL_EXTERNAL (tem) = 0;
	  درخت_STATIC (tem) = 1;
	}

      واپس tem;
    }
  ورنہ
    واپس decl;
}

/* Subroutine of finish_decl. TYPE is the type of an uninitialized object
   DECL or the non-array element type if DECL is an uninitialized array.
   If that type has a const member, diagnose this. */

ساکن خالی
diagnose_uninitialized_cst_member (درخت decl, درخت type)
{
  درخت میدان_2;
  برائے (میدان_2 = TYPE_FIELDS (type); میدان_2; میدان_2 = درخت_CHAIN (میدان_2))
    {
      درخت میدان_type;
      اگر (درخت_رمز (میدان_2) != میدان_DECL)
	جاری;
      میدان_type = strip_array_types (درخت_TYPE (میدان_2));

      اگر (TYPE_QUALS (میدان_type) & TYPE_QUAL_CONST)
      	{
	  auto_diagnostic_گروہ d;
	  اگر (warning_at (DECL_ماخذ_LOCATION (decl), OPT_Wc___compat,
			  "uninitialized const member in %qT is invalid in C++",
			  strip_array_types (درخت_TYPE (decl))))
	    inform (DECL_ماخذ_LOCATION (میدان_2), "%qD should be initialized", میدان_2);
	}

      اگر (ریکارڈ_OR_UNION_TYPE_P (میدان_type))
	diagnose_uninitialized_cst_member (decl, میدان_type);
    }
}

/* Finish processing of a declaration;
   install its initial value.
   If ORIGTYPE is not NULL_TREE, it is the original type of INIT.
   If the length of an array type is not known before,
   it must be determined now, from the initial value, or it is an error.

   INIT_LOC is the location of the initial value.  */

خالی
اختتام_decl (درخت decl, location_t init_loc, درخت init,
	     درخت origtype, درخت asmspec_درخت)
{
  درخت type;
  منطقی was_incomplete = (DECL_سائز (decl) == NULL_درخت);
  ثابت حرف *asmspec = 0;

  /* If a name was specified, get the string.  */
  اگر (VAR_OR_FUNCTION_DECL_P (decl)
      && DECL_FILE_SCOPE_P (decl))
    asmspec_درخت = maybe_apply_renaming_pragma (decl, asmspec_درخت);
  اگر (asmspec_درخت)
    asmspec = درخت_STRING_اشارہ_گر (asmspec_درخت);

  اگر (VAR_P (decl)
      && درخت_STATIC (decl)
      && global_bindings_p ())
    /* So decl is a global variable. Record the types it uses
       so that we can decide later to emit debug info for them.  */
    ریکارڈ_types_مستعمل_by_current_var_decl (decl);

  /* If `start_decl' didn't like having an initialization, ignore it now.  */
  اگر (init != NULL_درخت && DECL_INITIAL (decl) == NULL_درخت)
    init = NULL_درخت;

  /* Don't crash if parm is initialized.  */
  اگر (درخت_رمز (decl) == PARM_DECL)
    init = NULL_درخت;

  اگر (init)
    store_init_قدر (init_loc, decl, init, origtype);

  اگر (c_dialect_objc () && (VAR_OR_FUNCTION_DECL_P (decl)
			    || درخت_رمز (decl) == میدان_DECL))
    objc_check_decl (decl);

  type = درخت_TYPE (decl);

  /* Deduce size of array from initialization, if not already known.
     This is only needed for an initialization in the current scope;
     it must not be done for a file-scope initialization of a
     declaration with external linkage, redeclared in an inner scope
     with the outer declaration shadowed in an intermediate scope.  */
  اگر (درخت_رمز (type) == ARRAY_TYPE
      && TYPE_DOMAIN (type) == NULL_درخت
      && درخت_رمز (decl) != TYPE_DECL
      && !(درخت_عوامی (decl) && current_scope != file_scope))
    {
      منطقی do_default
	= !درخت_STATIC (decl) && !DECL_EXTERNAL (decl);
      صحیح failure
	= complete_array_type (&درخت_TYPE (decl), DECL_INITIAL (decl),
			       do_default);

      /* Get the completed type made by complete_array_type.  */
      type = درخت_TYPE (decl);

      انتخاب (failure)
	{
	حالت 1:
	  error ("initializer fails to determine size of %q+D", decl);
	  توڑو;

	حالت 2:
	  اگر (do_default)
	    error ("array size missing in %q+D", decl);
	  ورنہ اگر (!درخت_عوامی (decl))
	    pedwarn_c23 (DECL_ماخذ_LOCATION (decl), OPT_Wpedantic,
			 "array size missing in %q+D", decl);
	  توڑو;

	حالت 3:
	  error ("zero or negative size array %q+D", decl);
	  توڑو;

	حالت 0:
	  /* For global variables, update the copy of the type that
	     exists in the binding.  */
	  اگر (درخت_عوامی (decl))
	    {
	      ساخت c_binding *b_ext = I_علامت_BINDING (DECL_NAME (decl));
	      جب (b_ext && !B_اندر_EXTERNAL_SCOPE (b_ext))
		b_ext = b_ext->shadowed;
	      اگر (b_ext && درخت_رمز (decl) == درخت_رمز (b_ext->decl))
		{
		  اگر (b_ext->u.type && comptypes (b_ext->u.type, type))
		    b_ext->u.type = مرکب_type (b_ext->u.type, type);
		  ورنہ
		    b_ext->u.type = type;
		}
	    }
	  توڑو;

	طےشدہ:
	  gcc_unreachable ();
	}

      اگر (DECL_INITIAL (decl) && DECL_INITIAL (decl) != error_mark_گرہ)
	درخت_TYPE (DECL_INITIAL (decl)) = type;

      relayout_decl (decl);
    }

  /* Look for braced array initializers for character arrays and
     recursively convert them into STRING_CSTs.  */
  اگر (درخت init = DECL_INITIAL (decl))
    DECL_INITIAL (decl) = braced_lists_مقصد_لڑیاں (type, init);

  اگر (VAR_P (decl))
    {
      اگر (init && درخت_رمز (init) == CONSTRUCTOR)
	جوڑو_flexible_array_elts_مقصد_سائز (decl, init);

      complete_flexible_array_elts (DECL_INITIAL (decl));

      اگر (is_global_var (decl))
	{
	  type_context_قسم context = (DECL_THREAD_LOCAL_P (decl)
				       ? TCTX_THREAD_STORAGE
				       : TCTX_STATIC_STORAGE);
	  اگر (!verify_type_context (داخلہ_location, context, درخت_TYPE (decl)))
	    درخت_TYPE (decl) = error_mark_گرہ;
	}

      اگر (DECL_سائز (decl) == NULL_درخت && درخت_TYPE (decl) != error_mark_گرہ
	  && COMPLETE_TYPE_P (درخت_TYPE (decl)))
	layout_decl (decl, 0);

      اگر (DECL_سائز (decl) == NULL_درخت
	  /* Don't give an error if we already gave one earlier.  */
	  && درخت_TYPE (decl) != error_mark_گرہ
	  && (درخت_STATIC (decl)
	      /* A static variable with an incomplete type
		 is an error if it is initialized.
		 Also if it is not file scope.
		 Also if it is thread-local (in C23).
		 Otherwise, let it through, but if it is not `extern'
		 then it may cause an error message later.  */
	      ? (DECL_INITIAL (decl) != NULL_درخت
		 || !DECL_FILE_SCOPE_P (decl)
		 || (flag_isoc23 && DECL_THREAD_LOCAL_P (decl)))
	      /* An automatic variable with an incomplete type
		 is an error.  */
	      : !DECL_EXTERNAL (decl)))
	 {
	   error ("storage size of %q+D isn%'t known", decl);
	   درخت_TYPE (decl) = error_mark_گرہ;
	 }

      اگر ((ریکارڈ_OR_UNION_TYPE_P (درخت_TYPE (decl))
	  || درخت_رمز (درخت_TYPE (decl)) == ENUMERAL_TYPE)
	  && DECL_سائز (decl) == NULL_درخت
	  && درخت_STATIC (decl))
	incomplete_ریکارڈ_decls.محفوظ_ڈالو (decl);

      اگر (is_global_var (decl)
	  && DECL_سائز (decl) != NULL_درخت
	  && درخت_TYPE (decl) != error_mark_گرہ)
	{
	  اگر (درخت_رمز (DECL_سائز (decl)) == INTEGER_CST)
	    constant_عبارت_warning (DECL_سائز (decl));
	  ورنہ
	    {
	      error ("storage size of %q+D isn%'t constant", decl);
	      درخت_TYPE (decl) = error_mark_گرہ;
	    }
	}

      اگر (درخت_مستعمل (type))
	{
	  درخت_مستعمل (decl) = 1;
	  DECL_READ_P (decl) = 1;
	}
    }

  /* If this is a function and an assembler name is specified, reset DECL_RTL
     so we can give it its new name.  Also, update builtin_decl if it
     was a normal built-in.  */
  اگر (درخت_رمز (decl) == FUNCTION_DECL && asmspec)
    {
      اگر (DECL_BUILT_اندر_CLASS (decl) == BUILT_اندر_معمول)
	سیٹ_builtin_user_assembler_name (decl, asmspec);
      سیٹ_user_assembler_name (decl, asmspec);
    }

  /* If #pragma weak was used, mark the decl weak now.  */
  maybe_apply_pragma_weak (decl);

  /* Output the assembler code and/or RTL code for variables and functions,
     unless the type is an undefined structure or union.
     If not, it will get done when the type is completed.  */

  اگر (VAR_OR_FUNCTION_DECL_P (decl))
    {
      /* Determine the ELF visibility.  */
      اگر (درخت_عوامی (decl))
	c_determine_visibility (decl);

      /* This is a no-op in c-lang.cc or something real in objc-act.cc.  */
      اگر (c_dialect_objc ())
	objc_check_decl (decl);

      اگر (asmspec)
	{
	  /* If this is not a static variable, issue a warning.
	     It doesn't make any sense to give an ASMSPEC for an
	     ordinary, non-register local variable.  Historically,
	     GCC has accepted -- but ignored -- the ASMSPEC in
	     this case.  */
	  اگر (!DECL_FILE_SCOPE_P (decl)
	      && VAR_P (decl)
	      && !C_DECL_رجسٹر (decl)
	      && !درخت_STATIC (decl))
	    warning (0, "ignoring %<asm%> specifier for non-static local "
		     "variable %q+D", decl);
	  ورنہ
	    سیٹ_user_assembler_name (decl, asmspec);
	}

      اگر (DECL_FILE_SCOPE_P (decl))
	{
	  اگر (DECL_INITIAL (decl) == NULL_درخت
	      || DECL_INITIAL (decl) == error_mark_گرہ)
	    /* Don't output anything
	       when a tentative file-scope definition is seen.
	       But at end of compilation, do output code for them.  */
	    DECL_DEFER_OUTPUT (decl) = 1;
	  اگر (asmspec && VAR_P (decl) && C_DECL_رجسٹر (decl))
	    DECL_HARD_رجسٹر (decl) = 1;
	  rest_کا_decl_compilation (decl, سچ, 0);

	  اگر (درخت_رمز (decl) == FUNCTION_DECL)
	    {
	      درخت parms = DECL_ARGUMENTS (decl);
	      ثابت منطقی builtin = fndecl_built_اندر_p (decl);
	      اگر (درخت access = build_attr_access_from_parms (parms, !builtin))
		decl_اوصاف (&decl, access, 0);
	    }
	}
      ورنہ
	{
	  /* In conjunction with an ASMSPEC, the `register'
	     keyword indicates that we should place the variable
	     in a particular register.  */
	  اگر (asmspec && C_DECL_رجسٹر (decl))
	    {
	      DECL_HARD_رجسٹر (decl) = 1;
	      /* This cannot be done for a structure with volatile
		 fields, on which DECL_REGISTER will have been
		 reset.  */
	      اگر (!DECL_رجسٹر (decl))
		error ("cannot put object with volatile field into register");
	    }

	  اگر (درخت_رمز (decl) != FUNCTION_DECL)
	    {
	      /* If we're building a variable sized type, and we might be
		 reachable other than via the top of the current binding
		 level, then create a new BIND_EXPR so that we deallocate
		 the object at the right time.  */
	      /* Note that DECL_SIZE can be null due to errors.  */
	      اگر (DECL_سائز (decl)
		  && !درخت_CONSTANT (DECL_سائز (decl))
		  && STATEMENT_LIST_HAS_LABEL (cur_stmt_list))
		{
		  درخت bind;
		  bind = build3 (BIND_اظہاریہ, void_type_گرہ, تہی, تہی, تہی);
		  درخت_SIDE_EFFECTS (bind) = 1;
		  جوڑو_stmt (bind);
		  BIND_اظہاریہ_BODY (bind) = ڈالو_stmt_list ();
		}
	      جوڑو_stmt (build_stmt (DECL_ماخذ_LOCATION (decl),
				    DECL_اظہاریہ, decl));
	    }
	}


      اگر (!DECL_FILE_SCOPE_P (decl))
	{
	  /* Recompute the RTL of a local array now
	     if it used to be an incomplete type.  */
	  اگر (was_incomplete && !is_global_var (decl))
	    {
	      /* If we used it already as memory, it must stay in memory.  */
	      درخت_ADDRESSABLE (decl) = درخت_مستعمل (decl);
	      /* If it's still incomplete now, no init will save it.  */
	      اگر (DECL_سائز (decl) == NULL_درخت)
		DECL_INITIAL (decl) = NULL_درخت;
	    }
	}
    }

  اگر (درخت_رمز (decl) == TYPE_DECL)
    {
      اگر (!DECL_FILE_SCOPE_P (decl)
	  && c_type_variably_modified_p (درخت_TYPE (decl)))
	جوڑو_stmt (build_stmt (DECL_ماخذ_LOCATION (decl), DECL_اظہاریہ, decl));

      rest_کا_decl_compilation (decl, DECL_FILE_SCOPE_P (decl), 0);
    }

  /* Install a cleanup (aka destructor) if one was given.  */
  اگر (VAR_P (decl) && !درخت_STATIC (decl))
    {
      درخت attr = lookup_attribute ("cleanup", DECL_اوصاف (decl));
      اگر (attr)
	{
	  درخت cleanup_id = درخت_قدر (درخت_قدر (attr));
	  درخت cleanup_decl = lookup_name (cleanup_id);
	  درخت cleanup;
	  vec<درخت, va_gc> *v;

	  /* Build "cleanup(&decl)" for the destructor.  */
	  cleanup = build_unary_op (داخلہ_location, ADDR_اظہاریہ, decl, جھوٹ);
	  vec_alloc (v, 1);
	  v->تیز_ڈالو (cleanup);
	  cleanup = c_build_function_call_vec (DECL_ماخذ_LOCATION (decl),
					       vNULL, cleanup_decl, v, تہی);
	  vec_free (v);

	  /* Don't warn about decl unused; the cleanup uses it.  */
	  درخت_مستعمل (decl) = 1;
	  درخت_مستعمل (cleanup_decl) = 1;
	  DECL_READ_P (decl) = 1;

	  ڈالو_cleanup (decl, cleanup, جھوٹ);
	}
    }

  اگر (warn_cxx_compat
      && VAR_P (decl)
      && !DECL_EXTERNAL (decl)
      && DECL_INITIAL (decl) == NULL_درخت)
    {
      type = strip_array_types (type);
      اگر (درخت_READONLY (decl))
	warning_at (DECL_ماخذ_LOCATION (decl), OPT_Wc___compat,
		    "uninitialized %<const %D%> is invalid in C++", decl);
      ورنہ اگر (ریکارڈ_OR_UNION_TYPE_P (type)
	       && C_TYPE_FIELDS_READONLY (type))
	diagnose_uninitialized_cst_member (decl, type);
    }

  اگر (flag_openmp
      && VAR_P (decl)
      && lookup_attribute ("omp declare target implicit",
			   DECL_اوصاف (decl)))
    {
      DECL_اوصاف (decl)
	= remove_attribute ("omp declare target implicit",
			    DECL_اوصاف (decl));
      اگر (!omp_mappable_type (درخت_TYPE (decl)))
	error ("%q+D in declare target directive does not have mappable type",
	       decl);
      ورنہ اگر (!lookup_attribute ("omp declare target",
				  DECL_اوصاف (decl))
	       && !lookup_attribute ("omp declare target link",
				     DECL_اوصاف (decl)))
	{
	  DECL_اوصاف (decl)
	    = درخت_cons (get_identifier ("omp declare target"),
			 NULL_درخت, DECL_اوصاف (decl));
	    symtab_گرہ *گرہ = symtab_گرہ::get (decl);
	    اگر (گرہ != تہی)
	      {
		گرہ->offloadable = 1;
		اگر (ENABLE_OFFLOADING)
		  {
		    g->have_offload = سچ;
		    اگر (is_a <varpool_گرہ *> (گرہ))
		      vec_محفوظ_ڈالو (offload_vars, decl);
		  }
	      }
	}
    }

  /* This is the last point we can lower alignment so give the target the
     chance to do so.  */
  اگر (VAR_P (decl)
      && !is_global_var (decl)
      && !DECL_HARD_رجسٹر (decl))
    targetm.زیریں_local_decl_alignment (decl);

  invoke_plugin_callbacks (PLUGIN_اختتام_DECL, decl);
}

/* Given a parsed parameter declaration, decode it into a PARM_DECL.
   EXPR is NULL or a pointer to an expression that needs to be
   evaluated for the side effects of array size expressions in the
   parameters.  */

درخت
grokparm (ثابت ساخت c_parm *parm, درخت *اظہاریہ)
{
  درخت attrs = parm->attrs;
  درخت decl = grokdeclarator (parm->declarator, parm->specs, PARM, جھوٹ,
			      تہی, &attrs, اظہاریہ, تہی, DEPRECATED_معمول);

  decl_اوصاف (&decl, attrs, 0);

  واپس decl;
}



/* Given a parsed parameter declaration, decode it into a PARM_DECL
   and push that on the current scope.  EXPR is a pointer to an
   expression that needs to be evaluated for the side effects of array
   size expressions in the parameters.  */

خالی
ڈالو_parm_decl (ثابت ساخت c_parm *parm, درخت *اظہاریہ)
{
  درخت attrs = parm->attrs;
  درخت decl = grokdeclarator (parm->declarator, parm->specs, PARM, جھوٹ, تہی,
			      &attrs, اظہاریہ, تہی, DEPRECATED_معمول);
  اگر (decl && DECL_P (decl))
    DECL_ماخذ_LOCATION (decl) = parm->loc;

  decl_اوصاف (&decl, attrs, 0);

  decl = pushdecl (decl);

  اختتام_decl (decl, داخلہ_location, NULL_درخت, NULL_درخت, NULL_درخت);
}

/* Mark all the parameter declarations to date as forward decls.
   Also diagnose use of this extension.  */

خالی
mark_forward_parm_decls (خالی)
{
  ساخت c_binding *b;

  اگر (current_scope->had_forward_parm_decls)
    warning_at (داخلہ_location, OPT_Wmultiple_parameter_fwd_decl_lists,
		"more than one list of forward declarations of parameters");
  اگر (pedantic && !current_scope->had_forward_parm_decls)
    pedwarn (داخلہ_location, OPT_Wpedantic,
	     "ISO C forbids forward parameter declarations");

  current_scope->had_forward_parm_decls = سچ;

  برائے (b = current_scope->bindings; b; b = b->پچھلا)
    اگر (درخت_رمز (b->decl) == PARM_DECL)
      درخت_ASM_WRITTEN (b->decl) = 1;
}

/* Build a COMPOUND_LITERAL_EXPR.  TYPE is the type given in the compound
   literal, which may be an incomplete array type completed by the
   initializer; INIT is a CONSTRUCTOR at LOC that initializes the compound
   literal.  NON_CONST is true if the initializers contain something
   that cannot occur in a constant expression.  If ALIGNAS_ALIGN is nonzero,
   it is the (valid) alignment for this compound literal, as specified
   with _Alignas.  SCSPECS are the storage class specifiers (C23) from the
   compound literal.  */

درخت
build_compound_literal (location_t loc, درخت type, درخت init, منطقی non_const,
			غیرعلامتی صحیح alignas_align,
			ساخت c_declspecs *scspecs)
{
  /* We do not use start_decl here because we have a type, not a declarator;
     and do not use finish_decl because the decl should be stored inside
     the COMPOUND_LITERAL_EXPR rather than added elsewhere as a DECL_EXPR.  */
  درخت decl;
  درخت complit;
  درخت stmt;
  منطقی threadp = scspecs ? scspecs->thread_p : جھوٹ;
  شمار c_storage_class storage_class = (scspecs
					? scspecs->storage_class
					: csc_none);

  اگر (type == error_mark_گرہ
      || init == error_mark_گرہ)
    واپس error_mark_گرہ;

  اگر (current_scope == file_scope && storage_class == csc_رجسٹر)
    {
      error_at (loc, "file-scope compound literal specifies %<register%>");
      storage_class = csc_none;
    }

  اگر (current_scope != file_scope && threadp && storage_class == csc_none)
    {
      error_at (loc, "compound literal implicitly auto and declared %qs",
		scspecs->thread_gnu_p ? "__thread" : "_Thread_local");
      threadp = جھوٹ;
    }

  decl = build_decl (loc, VAR_DECL, NULL_درخت, type);
  DECL_EXTERNAL (decl) = 0;
  درخت_عوامی (decl) = 0;
  درخت_STATIC (decl) = (current_scope == file_scope
			|| storage_class == csc_static);
  DECL_CONTEXT (decl) = current_function_decl;
  درخت_مستعمل (decl) = 1;
  DECL_READ_P (decl) = 1;
  DECL_ARTIFICIAL (decl) = 1;
  DECL_IGNORED_P (decl) = 1;
  C_DECL_COMPOUND_LITERAL_P (decl) = 1;
  C_DECL_DECLARED_CONSTEXPR (decl) = scspecs && scspecs->constexpr_p;
  درخت_TYPE (decl) = type;
  اگر (threadp)
    سیٹ_decl_tls_model (decl, decl_default_tls_model (decl));
  اگر (storage_class == csc_رجسٹر)
    {
      C_DECL_رجسٹر (decl) = 1;
      DECL_رجسٹر (decl) = 1;
    }
  c_apply_type_quals_مقصد_decl (TYPE_QUALS (strip_array_types (type)), decl);
  اگر (alignas_align)
    {
      سیٹ_DECL_ALIGN (decl, alignas_align * بٹ_فی_UNIT);
      DECL_USER_ALIGN (decl) = 1;
    }
  store_init_قدر (loc, decl, init, NULL_درخت);
  اگر (current_scope != file_scope
      && درخت_STATIC (decl)
      && !درخت_READONLY (decl)
      && DECL_DECLARED_INLINE_P (current_function_decl)
      && DECL_EXTERNAL (current_function_decl))
    ریکارڈ_inline_static (داخلہ_location, current_function_decl,
			  decl, csi_modifiable);

  اگر (درخت_رمز (type) == ARRAY_TYPE && !COMPLETE_TYPE_P (type))
    {
      صحیح failure = complete_array_type (&درخت_TYPE (decl),
					 DECL_INITIAL (decl), سچ);
      /* If complete_array_type returns 3, it means that the initial value of
         the compound literal is empty.  Allow it with a pedwarn; in pre-C23
         modes, the empty initializer itself has been diagnosed if pedantic so
         does not need to be diagnosed again here.  */
      gcc_assert (failure == 0 || failure == 3);
      اگر (failure == 3 && flag_isoc23)
	pedwarn (loc, OPT_Wpedantic,
		 "array of unknown size with empty initializer");

      type = درخت_TYPE (decl);
      درخت_TYPE (DECL_INITIAL (decl)) = type;
      relayout_decl (decl);
    }

  اگر (type == error_mark_گرہ || !COMPLETE_TYPE_P (type))
    {
      c_incomplete_type_error (loc, NULL_درخت, type);
      واپس error_mark_گرہ;
    }

  اگر ((درخت_STATIC (decl) || C_DECL_DECLARED_CONSTEXPR (decl))
      && C_TYPE_VARIABLE_سائز (type))
    error_at (loc, "storage size isn%'t constant");

  اگر (درخت_STATIC (decl)
      && !verify_type_context (loc, TCTX_STATIC_STORAGE, type))
    واپس error_mark_گرہ;

  stmt = build_stmt (DECL_ماخذ_LOCATION (decl), DECL_اظہاریہ, decl);
  complit = build1 (COMPOUND_LITERAL_اظہاریہ, type, stmt);
  درخت_SIDE_EFFECTS (complit) = 1;

  layout_decl (decl, 0);

  اگر (درخت_STATIC (decl))
    {
      /* This decl needs a name for the assembler output.  */
      سیٹ_compound_literal_name (decl);
      DECL_DEFER_OUTPUT (decl) = 1;
      DECL_COMDAT (decl) = 1;
      pushdecl (decl);
      rest_کا_decl_compilation (decl, 1, 0);
    }
  ورنہ اگر (current_function_decl && !current_scope->parm_flag)
    pushdecl (decl);

  اگر (non_const)
    {
      complit = build2 (C_MAYBE_CONST_اظہاریہ, type, تہی, complit);
      C_MAYBE_CONST_اظہاریہ_NON_CONST (complit) = 1;
    }

  واپس complit;
}

/* Check the type of a compound literal.  Here we just check that it
   is valid for C++.  */

خالی
check_compound_literal_type (location_t loc, ساخت c_type_name *type_name)
{
  اگر (warn_cxx_compat
      && (type_name->specs->typespec_قسم == ctsk_tagdef
          || type_name->specs->typespec_قسم == ctsk_tagfirstref
	  || type_name->specs->typespec_قسم == ctsk_tagfirstref_attrs))
    warning_at (loc, OPT_Wc___compat,
		"defining a type in a compound literal is invalid in C++");
}

/* Performs sanity checks on the TYPE and WIDTH of the bit-field NAME,
   replacing with appropriate values if they are invalid.  */

ساکن خالی
check_bitfield_type_and_چوڑائی (location_t loc, درخت *type, درخت *چوڑائی,
			       درخت orig_name)
{
  درخت type_mv;
  غیرعلامتی صحیح max_چوڑائی;
  غیرعلامتی HOST_WIDE_INT w;
  ثابت حرف *name = (orig_name
		      ? identifier_مقصد_locale (IDENTIFIER_اشارہ_گر (orig_name))
		      : _("<anonymous>"));

  /* Detect and ignore out of range field width and process valid
     field widths.  */
  اگر (!INTEGRAL_TYPE_P (درخت_TYPE (*چوڑائی)))
    {
      error_at (loc, "bit-field %qs width not an integer constant", name);
      *چوڑائی = integer_one_گرہ;
    }
  ورنہ
    {
      اگر (درخت_رمز (*چوڑائی) != INTEGER_CST)
	{
	  *چوڑائی = c_fully_fold (*چوڑائی, جھوٹ, تہی);
	  اگر (درخت_رمز (*چوڑائی) == INTEGER_CST)
	    pedwarn (loc, OPT_Wpedantic,
		     "bit-field %qs width not an integer constant expression",
		     name);
	}
      اگر (درخت_رمز (*چوڑائی) != INTEGER_CST)
	{
	  error_at (loc, "bit-field %qs width not an integer constant", name);
	  *چوڑائی = integer_one_گرہ;
	}
      constant_عبارت_warning (*چوڑائی);
      اگر (درخت_int_cst_sgn (*چوڑائی) < 0)
	{
	  error_at (loc, "negative width in bit-field %qs", name);
	  *چوڑائی = integer_one_گرہ;
	}
      ورنہ اگر (integer_zerop (*چوڑائی) && orig_name)
	{
	  error_at (loc, "zero width for bit-field %qs", name);
	  *چوڑائی = integer_one_گرہ;
	}
    }

  /* Detect invalid bit-field type.  */
  اگر (درخت_رمز (*type) != INTEGER_TYPE
      && درخت_رمز (*type) != BOOLEAN_TYPE
      && درخت_رمز (*type) != ENUMERAL_TYPE
      && درخت_رمز (*type) != BITINT_TYPE)
    {
      error_at (loc, "bit-field %qs has invalid type", name);
      *type = unsigned_type_گرہ;
    }

  اگر (TYPE_WARN_IF_NOT_ALIGN (*type))
    {
      error_at (loc, "cannot declare bit-field %qs with %<warn_if_not_aligned%> type",
		name);
      *type = unsigned_type_گرہ;
    }

  type_mv = TYPE_MAIN_VARIANT (*type);
  اگر (!اندر_system_سرخی_at (داخلہ_location)
      && type_mv != integer_type_گرہ
      && type_mv != unsigned_type_گرہ
      && type_mv != boolean_type_گرہ)
    pedwarn_c90 (loc, OPT_Wpedantic,
		 "type of bit-field %qs is a GCC extension", name);

  max_چوڑائی = TYPE_PRECISION (*type);

  اگر (compare_درخت_int (*چوڑائی, max_چوڑائی) > 0)
    {
      error_at (loc, "width of %qs exceeds its type", name);
      w = max_چوڑائی;
      *چوڑائی = build_int_cst (integer_type_گرہ, w);
    }
  ورنہ
    w = درخت_مقصد_uhwi (*چوڑائی);

  /* Truncation of hardbool false and true representation values is always safe:
     either the values remain different, or we'll report a problem when creating
     the narrower type.  */
  اگر (c_hardbool_type_attr (*type))
    واپس;

  اگر (درخت_رمز (*type) == ENUMERAL_TYPE)
    {
      ساخت lang_type *lt = TYPE_LANG_SPECIFIC (*type);
      اگر (!lt
	  || w < درخت_int_cst_min_precision (lt->enum_min, TYPE_SIGN (*type))
	  || w < درخت_int_cst_min_precision (lt->enum_max, TYPE_SIGN (*type)))
	warning_at (loc, 0, "%qs is narrower than values of its type", name);
    }
}



/* Print warning about variable length array if necessary.  */

ساکن خالی
warn_variable_لمبائی_array (درخت name, درخت سائز)
{
  اگر (درخت_CONSTANT (سائز))
    {
      اگر (name)
	pedwarn_c90 (داخلہ_location, OPT_Wvla,
		     "ISO C90 forbids array %qE whose size "
		     "cannot be evaluated", name);
      ورنہ
	pedwarn_c90 (داخلہ_location, OPT_Wvla, "ISO C90 forbids array "
		     "whose size cannot be evaluated");
    }
  ورنہ
    {
      اگر (name)
	pedwarn_c90 (داخلہ_location, OPT_Wvla,
		     "ISO C90 forbids variable length array %qE", name);
      ورنہ
	pedwarn_c90 (داخلہ_location, OPT_Wvla, "ISO C90 forbids variable "
		     "length array");
    }
}

/* Returns the smallest location != UNKNOWN_LOCATION in LOCATIONS,
   considering only those c_declspec_words found in LIST, which
   must be terminated by cdw_number_of_elements.  */

ساکن location_t
سب_سے_چھوٹا_type_quals_location (ثابت location_t *locations,
			      ثابت c_declspec_لفظ *list)
{
  location_t loc = UNKNOWN_LOCATION;
  جب (*list != cdw_نمبر_کا_elements)
    {
      location_t newloc = locations[*list];
      اگر (loc == UNKNOWN_LOCATION
	  || (newloc != UNKNOWN_LOCATION && newloc < loc))
	loc = newloc;
      list++;
    }

  واپس loc;
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
ساکن خالی
جوڑو_decl_اظہاریہ (location_t loc, درخت type, درخت *اظہاریہ, منطقی سیٹ_name_p)
{
  درخت bind = NULL_درخت;
  اگر (اظہاریہ)
    {
      bind = build3 (BIND_اظہاریہ, void_type_گرہ, NULL_درخت, NULL_درخت,
		     NULL_درخت);
      درخت_SIDE_EFFECTS (bind) = 1;
      BIND_اظہاریہ_BODY (bind) = ڈالو_stmt_list ();
      ڈالو_scope ();
    }

  درخت decl = build_decl (loc, TYPE_DECL, NULL_درخت, type);
  pushdecl (decl);
  DECL_ARTIFICIAL (decl) = 1;
  جوڑو_stmt (build_stmt (DECL_ماخذ_LOCATION (decl), DECL_اظہاریہ, decl));
  اگر (سیٹ_name_p)
    TYPE_NAME (type) = decl;

  اگر (bind)
    {
      نکالو_scope ();
      BIND_اظہاریہ_BODY (bind) = نکالو_stmt_list (BIND_اظہاریہ_BODY (bind));
      اگر (*اظہاریہ)
	*اظہاریہ = build2 (COMPOUND_اظہاریہ, void_type_گرہ, *اظہاریہ, bind);
      ورنہ
	*اظہاریہ = bind;
    }
}


/* Add attribute "arg spec" to ATTRS corresponding to an array/VLA parameter
   declared with type TYPE.  The attribute has two arguments.  The first is
   a string that encodes the presence of the static keyword.  The second is
   the declared type of the array before adjustment, i.e. as an array type
   including the outermost bound.  */

ساکن درخت
build_arg_spec_attribute (درخت type, منطقی static_p, درخت attrs)
{
  درخت vbchain = درخت_cons (NULL_درخت, type, NULL_درخت);
  درخت acsstr = static_p ? build_string (7, "static") :
			   build_string (1, "");
  درخت دلائل = درخت_cons (NULL_درخت, acsstr, vbchain);
  درخت name = get_identifier ("arg spec");
  واپس درخت_cons (name, دلائل, attrs);
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

ساکن درخت
grokdeclarator (ثابت ساخت c_declarator *declarator,
		ساخت c_declspecs *declspecs,
		شمار decl_context decl_context, منطقی initialized, درخت *چوڑائی,
		درخت *decl_attrs, درخت *اظہاریہ, منطقی *اظہاریہ_const_operands,
		شمار deprecated_حالتیں deprecated_state)
{
  درخت type = declspecs->type;
  منطقی threadp = declspecs->thread_p;
  منطقی constexprp = declspecs->constexpr_p;
  شمار c_storage_class storage_class = declspecs->storage_class;
  صحیح constp;
  صحیح restrictp;
  صحیح volatilep;
  صحیح atomicp;
  صحیح type_quals = TYPE_UNQUALIFIED;
  درخت name = NULL_درخت;
  منطقی funcdef_flag = جھوٹ;
  منطقی funcdef_syntax = جھوٹ;
  منطقی سائز_varies = جھوٹ;
  منطقی سائز_error = جھوٹ;
  درخت decl_attr = declspecs->decl_attr;
  صحیح array_ptr_quals = TYPE_UNQUALIFIED;
  درخت array_ptr_attrs = NULL_درخت;
  منطقی array_parm_static = جھوٹ;
  منطقی array_parm_vla_unspec_p = جھوٹ;
  درخت returned_attrs = NULL_درخت;
  درخت decl_id_attrs = NULL_درخت;
  منطقی bitfield = چوڑائی != تہی;
  درخت element_type;
  درخت orig_qual_type = تہی;
  سائز_t orig_qual_بالواسطہ = 0;
  ساخت c_arg_info *arg_info = 0;
  addr_space_t as1, as2, پتہ_space;
  location_t loc = UNKNOWN_LOCATION;
  درخت اظہاریہ_dummy;
  منطقی اظہاریہ_const_operands_dummy;
  شمار c_declarator_قسم پہلا_non_attr_قسم;
  غیرعلامتی صحیح alignas_align = 0;

  اگر (type == NULL_درخت)
    {
      /* This can occur for auto on a parameter in C23 mode.  Set a
	 dummy type here so subsequent code can give diagnostics for
	 this case.  */
      gcc_assert (declspecs->c23_auto_p);
      gcc_assert (decl_context == PARM);
      type = declspecs->type = integer_type_گرہ;
    }
  اگر (درخت_رمز (type) == ERROR_MARK)
    واپس error_mark_گرہ;
  اگر (اظہاریہ == تہی)
    {
      اظہاریہ = &اظہاریہ_dummy;
      اظہاریہ_dummy = NULL_درخت;
    }
  اگر (اظہاریہ_const_operands == تہی)
    اظہاریہ_const_operands = &اظہاریہ_const_operands_dummy;

  اگر (declspecs->اظہاریہ)
    {
      اگر (*اظہاریہ)
	*اظہاریہ = build2 (COMPOUND_اظہاریہ, درخت_TYPE (declspecs->اظہاریہ), *اظہاریہ,
			declspecs->اظہاریہ);
      ورنہ
	*اظہاریہ = declspecs->اظہاریہ;
    }
  *اظہاریہ_const_operands = declspecs->اظہاریہ_const_operands;

  اگر (decl_context == FUNCDEF)
    funcdef_flag = سچ, decl_context = معمول;

  /* Look inside a declarator for the name being declared
     and get it as an IDENTIFIER_NODE, for an error message.  */
  {
    ثابت ساخت c_declarator *decl = declarator;

    پہلا_non_attr_قسم = cdk_attrs;
    جب (decl)
      انتخاب (decl->قسم)
	{
	حالت cdk_array:
	  loc = decl->id_loc;
	  /* FALL THRU.  */

	حالت cdk_function:
	حالت cdk_اشارہ_گر:
	  funcdef_syntax = (decl->قسم == cdk_function);
	  اگر (پہلا_non_attr_قسم == cdk_attrs)
	    پہلا_non_attr_قسم = decl->قسم;
	  decl = decl->declarator;
	  توڑو;

	حالت cdk_attrs:
	  decl = decl->declarator;
	  توڑو;

	حالت cdk_id:
	  loc = decl->id_loc;
	  اگر (decl->u.id.id)
	    name = decl->u.id.id;
	  decl_id_attrs = decl->u.id.attrs;
	  اگر (پہلا_non_attr_قسم == cdk_attrs)
	    پہلا_non_attr_قسم = decl->قسم;
	  decl = 0;
	  توڑو;

	طےشدہ:
	  gcc_unreachable ();
	}
    اگر (name == NULL_درخت)
      {
	gcc_assert (decl_context == PARM
		    || decl_context == TYPENAME
		    || decl_context == GENERIC_ASSOC
		    || (decl_context == میدان
			&& declarator->قسم == cdk_id));
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
  اگر (declspecs->enum_type_specifier_ref_p)
    error_at (loc, "%<enum%> underlying type may not be specified here");

  /* A function definition's declarator must have the form of
     a function declarator.  */

  اگر (funcdef_flag && !funcdef_syntax)
    واپس NULL_درخت;

  /* If this looks like a function definition, make it one,
     even if it occurs where parms are expected.
     Then store_parm_decls will reject it and not use it as a parm.  */
  اگر (decl_context == معمول && !funcdef_flag && current_scope->parm_flag)
    decl_context = PARM;

  اگر (deprecated_state != UNAVAILABLE_DEPRECATED_SUPPRESS)
    {
      اگر (declspecs->unavailable_p)
	error_unavailable_use (declspecs->type, declspecs->decl_attr);
      ورنہ اگر (declspecs->deprecated_p
		&& deprecated_state != DEPRECATED_SUPPRESS)
	warn_deprecated_use (declspecs->type, declspecs->decl_attr);
    }

  اگر ((decl_context == معمول || decl_context == میدان)
      && current_scope == file_scope
      && c_type_variably_modified_p (type))
    {
      اگر (name)
	error_at (loc, "variably modified %qE at file scope", name);
      ورنہ
	error_at (loc, "variably modified field at file scope");
      type = integer_type_گرہ;
    }

  سائز_varies = C_TYPE_VARIABLE_سائز (type) != 0;

  /* Diagnose defaulting to "int".  */

  اگر (declspecs->default_int_p)
    {
      /* Issue a warning if this is an ISO C 99 program or if
	 -Wreturn-type and this is a function, or if -Wimplicit;
	 prefer the former warning since it is more explicit.  */
      اگر ((warn_implicit_int || warn_return_type > 0 || flag_isoc99)
	  && funcdef_flag)
	warn_about_return_type = 1;
      ورنہ
	{
	  اگر (name)
	    permerror_opt (loc, OPT_Wimplicit_int,
			   "type defaults to %<int%> in declaration "
			   "of %qE", name);
	  ورنہ
	    permerror_opt (loc, OPT_Wimplicit_int,
			   "type defaults to %<int%> in type name");
	}
    }

  /* Adjust the type if a bit-field is being declared,
     -funsigned-bitfields applied and the type is not explicitly
     "signed".  */
  اگر (bitfield && !flag_signed_bitfields && !declspecs->explicit_signed_p
      && درخت_رمز (type) == INTEGER_TYPE)
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
  as1 = declspecs->پتہ_space;
  as2 = TYPE_ADDR_SPACE (element_type);
  پتہ_space = ADDR_SPACE_GENERIC_P (as1)? as2 : as1;

  اگر (constp > 1)
    pedwarn_c90 (loc, OPT_Wpedantic, "duplicate %<const%>");
  اگر (restrictp > 1)
    pedwarn_c90 (loc, OPT_Wpedantic, "duplicate %<restrict%>");
  اگر (volatilep > 1)
    pedwarn_c90 (loc, OPT_Wpedantic, "duplicate %<volatile%>");
  اگر (atomicp > 1)
    pedwarn_c90 (loc, OPT_Wpedantic, "duplicate %<_Atomic%>");

  اگر (!ADDR_SPACE_GENERIC_P (as1) && !ADDR_SPACE_GENERIC_P (as2) && as1 != as2)
    error_at (loc, "conflicting named address spaces (%s vs %s)",
	      c_addr_space_name (as1), c_addr_space_name (as2));

  اگر ((درخت_رمز (type) == ARRAY_TYPE
       || پہلا_non_attr_قسم == cdk_array)
      && TYPE_QUALS (element_type))
    {
      orig_qual_type = type;
      type = c_build_qualified_type (type, TYPE_UNQUALIFIED);
    }
  type_quals = ((constp ? TYPE_QUAL_CONST : 0)
		| (restrictp ? TYPE_QUAL_RESTRICT : 0)
		| (volatilep ? TYPE_QUAL_VOLATILE : 0)
		| (atomicp ? TYPE_QUAL_ATOMIC : 0)
		| ENCODE_QUAL_ADDR_SPACE (پتہ_space));
  اگر (type_quals != TYPE_QUALS (element_type))
    orig_qual_type = NULL_درخت;

  /* Applying the _Atomic qualifier to an array type (through the use
     of typedefs or typeof) must be detected here.  If the qualifier
     is introduced later, any appearance of applying it to an array is
     actually applying it to an element of that array.  */
  اگر (declspecs->atomic_p && درخت_رمز (type) == ARRAY_TYPE)
    error_at (loc, "%<_Atomic%>-qualified array type");

  /* Warn about storage classes that are invalid for certain
     kinds of declarations (parameters, typenames, etc.).  */

  اگر (funcdef_flag
      && (threadp
	  || constexprp
	  || storage_class == csc_auto
	  || storage_class == csc_رجسٹر
	  || storage_class == csc_typedef))
    {
      اگر (storage_class == csc_auto)
	pedwarn (loc,
		 (current_scope == file_scope) ? 0 : OPT_Wpedantic,
		 "function definition declared %<auto%>");
      اگر (storage_class == csc_رجسٹر)
	error_at (loc, "function definition declared %<register%>");
      اگر (storage_class == csc_typedef)
	error_at (loc, "function definition declared %<typedef%>");
      اگر (threadp)
	error_at (loc, "function definition declared %qs",
		  declspecs->thread_gnu_p ? "__thread" : "_Thread_local");
      threadp = جھوٹ;
      /* The parser ensures a constexpr function definition never
	 reaches here.  */
      gcc_assert (!constexprp);
      اگر (storage_class == csc_auto
	  || storage_class == csc_رجسٹر
	  || storage_class == csc_typedef)
	storage_class = csc_none;
    }
  ورنہ اگر (decl_context != معمول && (storage_class != csc_none
				      || threadp
				      || constexprp
				      || declspecs->c23_auto_p))
    {
      اگر (decl_context == PARM
	  && storage_class == csc_رجسٹر
	  && !constexprp
	  && !declspecs->c23_auto_p)
	;
      ورنہ
	{
	  انتخاب (decl_context)
	    {
	    حالت میدان:
	      اگر (name)
		error_at (loc, "storage class specified for structure "
		    	  "field %qE", name);
	      ورنہ
		error_at (loc, "storage class specified for structure field");
	      توڑو;
	    حالت PARM:
	      اگر (name)
		error_at (loc, "storage class specified for parameter %qE",
		    	  name);
	      ورنہ
		error_at (loc, "storage class specified for unnamed parameter");
	      توڑو;
	    طےشدہ:
	      error_at (loc, "storage class specified for typename");
	      توڑو;
	    }
	  storage_class = csc_none;
	  threadp = جھوٹ;
	  constexprp = جھوٹ;
	}
    }
  ورنہ اگر (storage_class == csc_extern
	   && initialized
	   && !funcdef_flag)
    {
      /* 'extern' with initialization is invalid if not at file scope.  */
       اگر (current_scope == file_scope)
         {
           /* It is fine to have 'extern const' when compiling at C
              and C++ intersection.  */
           اگر (!(warn_cxx_compat && constp))
             warning_at (loc, 0, "%qE initialized and declared %<extern%>",
		 	 name);
         }
      ورنہ
	error_at (loc, "%qE has both %<extern%> and initializer", name);
    }
  ورنہ اگر (current_scope == file_scope)
    {
      اگر (storage_class == csc_auto)
	error_at (loc, "file-scope declaration of %qE specifies %<auto%>",
	    	  name);
      اگر (pedantic && storage_class == csc_رجسٹر)
	pedwarn (داخلہ_location, OPT_Wpedantic,
		 "file-scope declaration of %qE specifies %<register%>", name);
    }
  ورنہ
    {
      اگر (storage_class == csc_extern && funcdef_flag)
	error_at (loc, "nested function %qE declared %<extern%>", name);
      ورنہ اگر (threadp && storage_class == csc_none)
	{
	  error_at (loc, "function-scope %qE implicitly auto and declared "
		    "%qs", name,
		    declspecs->thread_gnu_p ? "__thread" : "_Thread_local");
	  threadp = جھوٹ;
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

  جب (declarator && declarator->قسم != cdk_id)
    {
      اگر (type == error_mark_گرہ)
	{
	  declarator = declarator->declarator;
	  جاری;
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

      اگر (array_ptr_quals != TYPE_UNQUALIFIED
	  || array_ptr_attrs != NULL_درخت
	  || array_parm_static)
	{
	  /* Only the innermost declarator (making a parameter be of
	     array type which is converted to pointer type)
	     may have static or type qualifiers.  */
	  error_at (loc, "static or type qualifiers in non-parameter array declarator");
	  array_ptr_quals = TYPE_UNQUALIFIED;
	  array_ptr_attrs = NULL_درخت;
	  array_parm_static = جھوٹ;
	}

      انتخاب (declarator->قسم)
	{
	حالت cdk_attrs:
	  {
	    /* A declarator with embedded attributes.  */
	    درخت attrs = declarator->u.attrs;
	    ثابت ساخت c_declarator *inner_decl;
	    صحیح attr_flags = 0;
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
	    جب (inner_decl->قسم == cdk_attrs)
	      inner_decl = inner_decl->declarator;
	    اگر (!cxx11_attribute_p (attrs))
	      {
		اگر (inner_decl->قسم == cdk_id)
		  attr_flags |= (صحیح) ATTR_FLAG_DECL_اگلا;
		ورنہ اگر (inner_decl->قسم == cdk_function)
		  attr_flags |= (صحیح) ATTR_FLAG_FUNCTION_اگلا;
		ورنہ اگر (inner_decl->قسم == cdk_array)
		  attr_flags |= (صحیح) ATTR_FLAG_ARRAY_اگلا;
	      }
	    attrs = c_warn_type_اوصاف (type, attrs);
	    returned_attrs = decl_اوصاف (&type,
					      chainon (returned_attrs, attrs),
					      attr_flags);
	    توڑو;
	  }
	حالت cdk_array:
	  {
	    درخت itype = NULL_درخت;
	    درخت سائز = declarator->u.array.dimen;
	    /* The index is a signed object `sizetype' bits wide.  */
	    درخت اشاریہ_type = c_common_signed_type (sizetype);

	    array_ptr_quals = declarator->u.array.quals;
	    array_ptr_attrs = declarator->u.array.attrs;
	    array_parm_static = declarator->u.array.static_p;
	    array_parm_vla_unspec_p = declarator->u.array.vla_unspec_p;

	    declarator = declarator->declarator;

	    منطقی flexible_array_member = جھوٹ;

	    /* Check for some types that there cannot be arrays of.  */

	    اگر (VOID_TYPE_P (type))
	      {
		اگر (name)
		  error_at (loc, "declaration of %qE as array of voids", name);
		ورنہ
		  error_at (loc, "declaration of type name as array of voids");
		type = error_mark_گرہ;
	      }

	    اگر (درخت_رمز (type) == FUNCTION_TYPE)
	      {
		اگر (name)
		  error_at (loc, "declaration of %qE as array of functions",
		      	    name);
		ورنہ
		  error_at (loc, "declaration of type name as array of "
		            "functions");
		type = error_mark_گرہ;
	      }

	    اگر (pedantic && !اندر_system_سرخی_at (داخلہ_location)
		&& flexible_array_type_p (type))
	      pedwarn (loc, OPT_Wpedantic,
		       "invalid use of structure with flexible array member");

	    اگر (سائز == error_mark_گرہ)
	      type = error_mark_گرہ;

	    اگر (type == error_mark_گرہ)
	      جاری;

	    اگر (!verify_type_context (loc, TCTX_ARRAY_ELEMENT, type))
	      {
		type = error_mark_گرہ;
		جاری;
	      }

	    /* If size was specified, set ITYPE to a range-type for
	       that size.  Otherwise, ITYPE remains null.  finish_decl
	       may figure it out from an initial value.  */

	    اگر (سائز)
	      {
		منطقی سائز_maybe_const = سچ;
		منطقی سائز_int_const = (درخت_رمز (سائز) == INTEGER_CST
				       && !درخت_حد_سے_تجاوز (سائز));
		منطقی this_سائز_varies = جھوٹ;

		/* Strip NON_LVALUE_EXPRs since we aren't using as an
		   lvalue.  */
		STRIP_TYPE_NOPS (سائز);

		اگر (!INTEGRAL_TYPE_P (درخت_TYPE (سائز)))
		  {
		    اگر (name)
		      error_at (loc, "size of array %qE has non-integer type",
				name);
		    ورنہ
		      error_at (loc,
				"size of unnamed array has non-integer type");
		    سائز = integer_one_گرہ;
		    سائز_int_const = سچ;
		    سائز_error = سچ;
		  }
		/* This can happen with enum forward declaration.  */
		ورنہ اگر (!COMPLETE_TYPE_P (درخت_TYPE (سائز)))
		  {
		    اگر (name)
		      error_at (loc, "size of array %qE has incomplete type",
				name);
		    ورنہ
		      error_at (loc, "size of unnamed array has incomplete "
				"type");
		    سائز = integer_one_گرہ;
		    سائز_int_const = سچ;
		    سائز_error = سچ;
		  }

		سائز = c_fully_fold (سائز, جھوٹ, &سائز_maybe_const);

		اگر (pedantic && سائز_maybe_const && integer_zerop (سائز))
		  {
		    اگر (name)
		      pedwarn (loc, OPT_Wpedantic,
			       "ISO C forbids zero-size array %qE", name);
		    ورنہ
		      pedwarn (loc, OPT_Wpedantic,
			       "ISO C forbids zero-size array");
		  }

		اگر (درخت_رمز (سائز) == INTEGER_CST && سائز_maybe_const)
		  {
		    constant_عبارت_warning (سائز);
		    اگر (درخت_int_cst_sgn (سائز) < 0)
		      {
			اگر (name)
			  error_at (loc, "size of array %qE is negative", name);
			ورنہ
			  error_at (loc, "size of unnamed array is negative");
			سائز = integer_one_گرہ;
			سائز_int_const = سچ;
			سائز_error = سچ;
		      }
		    /* Handle a size folded to an integer constant but
		       not an integer constant expression.  */
		    اگر (!سائز_int_const)
		      {
			/* If this is a file scope declaration of an
			   ordinary identifier, this is invalid code;
			   diagnosing it here and not subsequently
			   treating the type as variable-length avoids
			   more confusing diagnostics later.  */
			اگر ((decl_context == معمول || decl_context == میدان)
			    && current_scope == file_scope)
			  pedwarn (داخلہ_location, 0,
				   "variably modified %qE at file scope",
				   name);
			ورنہ
			  this_سائز_varies = سائز_varies = سچ;
			warn_variable_لمبائی_array (name, سائز);
		      }
		  }
		ورنہ اگر ((decl_context == معمول || decl_context == میدان)
			 && current_scope == file_scope)
		  {
		    error_at (loc, "variably modified %qE at file scope", name);
		    سائز = integer_one_گرہ;
		  }
		ورنہ
		  {
		    /* Make sure the array size remains visibly
		       nonconstant even if it is (eg) a const variable
		       with known value.  */
		    this_سائز_varies = سائز_varies = سچ;
		    warn_variable_لمبائی_array (name, سائز);
		    اگر (sanitize_flags_p (SANITIZE_VLA)
			&& current_function_decl != NULL_درخت
			&& decl_context == معمول)
		      {
			/* Evaluate the array size only once.  */
			سائز = save_اظہاریہ (سائز);
			سائز = c_fully_fold (سائز, جھوٹ, تہی);
		        سائز = fold_build2 (COMPOUND_اظہاریہ, درخت_TYPE (سائز),
					    ubsan_instrument_vla (loc, سائز),
					    سائز);
		      }
		  }

		اگر (integer_zerop (سائز) && !this_سائز_varies)
		  {
		    /* A zero-length array cannot be represented with
		       an unsigned index type, which is what we'll
		       get with build_index_type.  Create an
		       open-ended range instead.  */
		    itype = build_اشاریہ_type (NULL_درخت);
		  }
		ورنہ
		  {
		    /* Arrange for the SAVE_EXPR on the inside of the
		       MINUS_EXPR, which allows the -1 to get folded
		       with the +1 that happens when building TYPE_SIZE.  */
		    اگر (سائز_varies)
		      سائز = save_اظہاریہ (سائز);
		    اگر (this_سائز_varies && درخت_رمز (سائز) == INTEGER_CST)
		      سائز = build2 (COMPOUND_اظہاریہ, درخت_TYPE (سائز),
				     integer_zero_گرہ, سائز);

		    /* Compute the maximum valid index, that is, size
		       - 1.  Do the calculation in index_type, so that
		       if it is a variable the computations will be
		       done in the proper mode.  */
		    itype = fold_build2_loc (loc, MINUS_اظہاریہ, اشاریہ_type,
					     convert (اشاریہ_type, سائز),
					     convert (اشاریہ_type,
						      سائز_one_گرہ));

		    /* The above overflows when size does not fit
		       in index_type.
		       ???  While a size of INT_MAX+1 technically shouldn't
		       cause an overflow (because we subtract 1), handling
		       this case seems like an unnecessary complication.  */
		    اگر (درخت_رمز (سائز) == INTEGER_CST
			&& !int_سماتا_type_p (سائز, اشاریہ_type))
		      {
			اگر (name)
			  error_at (loc, "size of array %qE is too large",
			            name);
			ورنہ
			  error_at (loc, "size of unnamed array is too large");
			type = error_mark_گرہ;
			جاری;
		      }

		    itype = build_اشاریہ_type (itype);
		  }
		اگر (this_سائز_varies)
		  {
		    اگر (درخت_SIDE_EFFECTS (سائز))
		      {
			اگر (*اظہاریہ)
			  *اظہاریہ = build2 (COMPOUND_اظہاریہ, درخت_TYPE (سائز),
					  *اظہاریہ, سائز);
			ورنہ
			  *اظہاریہ = سائز;
		      }
		    *اظہاریہ_const_operands &= سائز_maybe_const;
		  }
	      }
	    ورنہ اگر (decl_context == میدان)
	      {
		اگر (array_parm_vla_unspec_p)
		  /* Field names can in fact have function prototype
		     scope so [*] is disallowed here through making
		     the field variably modified, not through being
		     something other than a declaration with function
		     prototype scope.  */
		  سائز_varies = سچ;
		ورنہ
		  {
		    ثابت ساخت c_declarator *t = declarator;
		    جب (t->قسم == cdk_attrs)
		      t = t->declarator;
		    flexible_array_member = (t->قسم == cdk_id);
		  }
		اگر (flexible_array_member
		    && !اندر_system_سرخی_at (داخلہ_location))
		  pedwarn_c90 (loc, OPT_Wpedantic, "ISO C90 does not "
			       "support flexible array members");

		/* ISO C99 Flexible array members are effectively
		   identical to GCC's zero-length array extension.  */
		اگر (flexible_array_member)
		  itype = build_اشاریہ_type (NULL_درخت);
	      }

	    /* Complain about arrays of incomplete types.  */
	    اگر (!COMPLETE_TYPE_P (type))
	      {
		auto_diagnostic_گروہ d;
		error_at (loc, "array type has incomplete element type %qT",
			  type);
		/* See if we can be more helpful.  */
		اگر (درخت_رمز (type) == ARRAY_TYPE)
		  {
		    اگر (name)
		      inform (loc, "declaration of %qE as multidimensional "
			      "array must have bounds for all dimensions "
			      "except the first", name);
		    ورنہ
		      inform (loc, "declaration of multidimensional array "
			      "must have bounds for all dimensions except "
			      "the first");
		  }
		type = error_mark_گرہ;
	      }
	    ورنہ
	    /* When itype is NULL, a shared incomplete array type is
	       returned for all array of a given type.  Elsewhere we
	       make sure we don't complete that type before copying
	       it, but here we want to make sure we don't ever
	       modify the shared type, so we gcc_assert (itype)
	       below.  */
	      {
		addr_space_t as = DECODE_QUAL_ADDR_SPACE (type_quals);
		اگر (!ADDR_SPACE_GENERIC_P (as) && as != TYPE_ADDR_SPACE (type))
		  type = c_build_qualified_type (type,
						 ENCODE_QUAL_ADDR_SPACE (as));
		اگر (array_parm_vla_unspec_p)
		  type = c_build_array_type_unspecified (type);
		/* The GCC extension for zero-length arrays differs from
		   ISO flexible array members in that sizeof yields
		   zero.  */
		ورنہ اگر (سائز && integer_zerop (سائز))
		  type = c_build_array_type_zero_سائز (type);
		ورنہ
		  type = c_build_array_type (type, itype);

		اگر (!valid_array_سائز_p (loc, type, name))
		  type = error_mark_گرہ;
	      }

	    اگر (array_parm_vla_unspec_p)
	      {
		/* C99 6.7.5.2p4 */
		اگر (decl_context == TYPENAME)
		  warning (0, "%<[*]%> not in a declaration");
		ورنہ اگر (decl_context != GENERIC_ASSOC
			 && decl_context != PARM
			 && decl_context != میدان)
		  {
		    error ("%<[*]%> not allowed in other than function prototype scope "
			   "or generic association");
		    type = error_mark_گرہ;
		  }
		سائز_varies = سچ;
	      }


	    gcc_assert (type == error_mark_گرہ
			|| flexible_array_member
			   == flexible_array_member_type_p (type));

	    اگر (decl_context != PARM
		&& (array_ptr_quals != TYPE_UNQUALIFIED
		    || array_ptr_attrs != NULL_درخت
		    || array_parm_static))
	      {
		error_at (loc, "static or type qualifiers in non-parameter "
			  "array declarator");
		array_ptr_quals = TYPE_UNQUALIFIED;
		array_ptr_attrs = NULL_درخت;
		array_parm_static = جھوٹ;
	      }
	    orig_qual_بالواسطہ++;
	    توڑو;
	  }
	حالت cdk_function:
	  {
	    /* Say it's a definition only for the declarator closest
	       to the identifier, apart possibly from some
	       attributes.  */
	    منطقی really_funcdef = جھوٹ;
	    درخت arg_types;
	    orig_qual_type = NULL_درخت;
	    اگر (funcdef_flag)
	      {
		ثابت ساخت c_declarator *t = declarator->declarator;
		جب (t->قسم == cdk_attrs)
		  t = t->declarator;
		really_funcdef = (t->قسم == cdk_id);
	      }

	    /* Declaring a function type.  Make sure we have a valid
	       type for the function to return.  */
	    اگر (type == error_mark_گرہ)
	      جاری;

	    سائز_varies = جھوٹ;

	    /* Warn about some types functions can't return.  */
	    اگر (درخت_رمز (type) == FUNCTION_TYPE)
	      {
		اگر (name)
		  error_at (loc, "%qE declared as function returning a "
		      		 "function", name);
		ورنہ
		  error_at (loc, "type name declared as function "
			    "returning a function");
		type = integer_type_گرہ;
	      }
	    اگر (درخت_رمز (type) == ARRAY_TYPE)
	      {
		اگر (name)
		  error_at (loc, "%qE declared as function returning an array",
		      	    name);
		ورنہ
		  error_at (loc, "type name declared as function returning "
		      	    "an array");
		type = integer_type_گرہ;
	      }

	    /* Construct the function type and go to the next
	       inner layer of declarator.  */
	    arg_info = declarator->u.arg_info;
	    arg_types = grokparms (arg_info, really_funcdef);

	    /* Type qualifiers before the return type of the function
	       qualify the return type, not the function type.  */
	    اگر (type_quals)
	      {
		ثابت شمار c_declspec_لفظ ignored_quals_list[] =
		  {
		    cdw_const, cdw_volatile, cdw_restrict, cdw_پتہ_space,
		    cdw_atomic, cdw_نمبر_کا_elements
		  };
		location_t specs_loc
		  = سب_سے_چھوٹا_type_quals_location (declspecs->locations,
						  ignored_quals_list);
		اگر (specs_loc == UNKNOWN_LOCATION)
		  specs_loc = declspecs->locations[cdw_typedef];
		اگر (specs_loc == UNKNOWN_LOCATION)
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
		صحیح quals_مستعمل = type_quals;
		اگر (flag_isoc23)
		  quals_مستعمل = 0;
		ورنہ اگر (flag_isoc11)
		  quals_مستعمل &= TYPE_QUAL_ATOMIC;
		اگر (quals_مستعمل && VOID_TYPE_P (type) && really_funcdef)
		  pedwarn (specs_loc, 0,
			   "function definition has qualified void "
			   "return type");
		ورنہ
		  warning_at (specs_loc, OPT_Wignored_qualifiers,
			      "type qualifiers ignored on function "
			      "return type");

		/* Ensure an error for restrict on invalid types; the
		   DR#423 resolution is not entirely clear about
		   this.  */
		اگر (flag_isoc11
		    && (type_quals & TYPE_QUAL_RESTRICT)
		    && (!اشارہ_گر_TYPE_P (type)
			|| !C_TYPE_OBJECT_OR_INCOMPLETE_P (درخت_TYPE (type))))
		  error_at (loc, "invalid use of %<restrict%>");
		type = c_build_qualified_type (type, quals_مستعمل);
	      }
	    type_quals = TYPE_UNQUALIFIED;

	    type = c_build_function_type (type, arg_types,
					  arg_info->no_named_دلائل_stdarg_p);
	    declarator = declarator->declarator;

	    /* Set the TYPE_CONTEXTs for each tagged type which is local to
	       the formal parameter list of this FUNCTION_TYPE to point to
	       the FUNCTION_TYPE node itself.  */
	    {
	      c_arg_لیبل *لیبل;
	      غیرعلامتی ix;

	      FOR_EACH_VEC_محفوظ_ELT_الٹ (arg_info->لیبل_فہرست, ix, لیبل)
		TYPE_CONTEXT (لیبل->type) = type;
	    }
	    توڑو;
	  }
	حالت cdk_اشارہ_گر:
	  {
	    /* Merge any constancy or volatility into the target type
	       for the pointer.  */
	    اگر ((type_quals & TYPE_QUAL_ATOMIC)
		&& درخت_رمز (type) == FUNCTION_TYPE)
	      {
		error_at (loc,
			  "%<_Atomic%>-qualified function type");
		type_quals &= ~TYPE_QUAL_ATOMIC;
	      }
	    ورنہ اگر (pedantic && درخت_رمز (type) == FUNCTION_TYPE
		     && type_quals)
	      pedwarn (loc, OPT_Wpedantic,
		       "ISO C forbids qualified function types");
	    اگر (type_quals)
	      type = c_build_qualified_type (type, type_quals, orig_qual_type,
					     orig_qual_بالواسطہ);
	    orig_qual_type = NULL_درخت;
	    سائز_varies = جھوٹ;

	    /* When the pointed-to type involves components of variable size,
	       care must be taken to ensure that the size evaluation code is
	       emitted early enough to dominate all the possible later uses
	       and late enough for the variables on which it depends to have
	       been assigned.

	       This is expected to happen automatically when the pointed-to
	       type has a name/declaration of it's own, but special attention
	       is required if the type is anonymous. */
	    اگر (!TYPE_NAME (type) && c_type_variably_modified_p (type))
	      {
		منطقی bind_p = decl_context == TYPENAME
			      || decl_context == میدان
			      || decl_context == PARM;
		جوڑو_decl_اظہاریہ (loc, type, bind_p ? اظہاریہ : تہی, سچ);
	      }

	    type = c_build_اشارہ_گر_type (type);

	    /* Process type qualifiers (such as const or volatile)
	       that were given inside the `*'.  */
	    type_quals = declarator->u.اشارہ_گر_quals;

	    declarator = declarator->declarator;
	    توڑو;
	  }
	طےشدہ:
	  gcc_unreachable ();
	}
    }
  *decl_attrs = chainon (returned_attrs, *decl_attrs);
  *decl_attrs = chainon (decl_id_attrs, *decl_attrs);

  /* Now TYPE has the actual type, apart from any qualifiers in
     TYPE_QUALS.  */

  /* Warn about address space used for things other than static memory or
     pointers.  */
  پتہ_space = DECODE_QUAL_ADDR_SPACE (type_quals);
  اگر (!ADDR_SPACE_GENERIC_P (پتہ_space))
    {
      اگر (decl_context == معمول)
	{
	  انتخاب (storage_class)
	    {
	    حالت csc_auto:
	      error ("%qs combined with %<auto%> qualifier for %qE",
		     c_addr_space_name (پتہ_space), name);
	      توڑو;
	    حالت csc_رجسٹر:
	      error ("%qs combined with %<register%> qualifier for %qE",
		     c_addr_space_name (پتہ_space), name);
	      توڑو;
	    حالت csc_none:
	      اگر (current_function_scope)
		{
		  error ("%qs specified for auto variable %qE",
			 c_addr_space_name (پتہ_space), name);
		  توڑو;
		}
	      توڑو;
	    حالت csc_static:
	    حالت csc_extern:
	    حالت csc_typedef:
	      توڑو;
	    طےشدہ:
	      gcc_unreachable ();
	    }
	}
      ورنہ اگر (decl_context == PARM && درخت_رمز (type) != ARRAY_TYPE)
	{
	  اگر (name)
	    error ("%qs specified for parameter %qE",
		   c_addr_space_name (پتہ_space), name);
	  ورنہ
	    error ("%qs specified for unnamed parameter",
		   c_addr_space_name (پتہ_space));
	}
      ورنہ اگر (decl_context == میدان)
	{
	  اگر (name)
	    error ("%qs specified for structure field %qE",
		   c_addr_space_name (پتہ_space), name);
	  ورنہ
	    error ("%qs specified for structure field",
		   c_addr_space_name (پتہ_space));
	}
    }

  /* Check the type and width of a bit-field.  */
  اگر (bitfield)
    {
      check_bitfield_type_and_چوڑائی (loc, &type, چوڑائی, name);
      /* C11 makes it implementation-defined (6.7.2.1#5) whether
	 atomic types are permitted for bit-fields; we have no code to
	 make bit-field accesses atomic, so disallow them.  */
      اگر (type_quals & TYPE_QUAL_ATOMIC)
	{
	  اگر (name)
	    error_at (loc, "bit-field %qE has atomic type", name);
	  ورنہ
	    error_at (loc, "bit-field has atomic type");
	  type_quals &= ~TYPE_QUAL_ATOMIC;
	}
    }

  /* Reject invalid uses of _Alignas.  */
  اگر (declspecs->alignas_p)
    {
      اگر (storage_class == csc_typedef)
	error_at (loc, "alignment specified for typedef %qE", name);
      ورنہ اگر (storage_class == csc_رجسٹر)
	error_at (loc, "alignment specified for %<register%> object %qE",
		  name);
      ورنہ اگر (decl_context == PARM)
	{
	  اگر (name)
	    error_at (loc, "alignment specified for parameter %qE", name);
	  ورنہ
	    error_at (loc, "alignment specified for unnamed parameter");
	}
      ورنہ اگر (bitfield)
	{
	  اگر (name)
	    error_at (loc, "alignment specified for bit-field %qE", name);
	  ورنہ
	    error_at (loc, "alignment specified for unnamed bit-field");
	}
      ورنہ اگر (درخت_رمز (type) == FUNCTION_TYPE)
	error_at (loc, "alignment specified for function %qE", name);
      ورنہ اگر (declspecs->align_log != -1 && TYPE_P (type))
	{
	  alignas_align = 1U << declspecs->align_log;
	  اگر (alignas_align < min_align_کا_type (type))
	    {
	      اگر (name)
		error_at (loc, "%<_Alignas%> specifiers cannot reduce "
			  "alignment of %qE", name);
	      ورنہ
		error_at (loc, "%<_Alignas%> specifiers cannot reduce "
			  "alignment of unnamed field");
	      alignas_align = 0;
	    }
	}
    }

  /* If this is declaring a typedef name, return a TYPE_DECL.  */

  اگر (storage_class == csc_typedef)
    {
      درخت decl;
      اگر ((type_quals & TYPE_QUAL_ATOMIC)
	  && درخت_رمز (type) == FUNCTION_TYPE)
	{
	  error_at (loc,
		    "%<_Atomic%>-qualified function type");
	  type_quals &= ~TYPE_QUAL_ATOMIC;
	}
      ورنہ اگر (pedantic && درخت_رمز (type) == FUNCTION_TYPE
	       && type_quals)
	pedwarn (loc, OPT_Wpedantic,
		 "ISO C forbids qualified function types");
      اگر (type_quals)
	type = c_build_qualified_type (type, type_quals, orig_qual_type,
				       orig_qual_بالواسطہ);
      decl = build_decl (declarator->id_loc,
			 TYPE_DECL, declarator->u.id.id, type);
      اگر (declspecs->explicit_signed_p)
	C_TYPEDEF_EXPLICITLY_SIGNED (decl) = 1;
      اگر (declspecs->inline_p)
	pedwarn (loc, 0,"typedef %q+D declared %<inline%>", decl);
      اگر (declspecs->noreturn_p)
	pedwarn (loc, 0,"typedef %q+D declared %<_Noreturn%>", decl);

      اگر (warn_cxx_compat && declarator->u.id.id != NULL_درخت)
	{
	  ساخت c_binding *b = I_لیبل_BINDING (declarator->u.id.id);

	  اگر (b != تہی
	      && b->decl != NULL_درخت
	      && (B_اندر_CURRENT_SCOPE (b)
		  || (current_scope == file_scope && B_اندر_EXTERNAL_SCOPE (b)))
	      && TYPE_MAIN_VARIANT (b->decl) != TYPE_MAIN_VARIANT (type))
	    {
	      auto_diagnostic_گروہ d;
	      اگر (warning_at (declarator->id_loc, OPT_Wc___compat,
			      "using %qD as both a typedef and a tag is "
			      "invalid in C++", decl)
		  && b->locus != UNKNOWN_LOCATION)
		inform (b->locus, "originally defined here");
	    }
	}

      واپس decl;
    }

  /* If this is a type name (such as, in a cast or sizeof),
     compute the type and return it now.  */

  اگر (decl_context == TYPENAME || decl_context == GENERIC_ASSOC)
    {
      /* Note that the grammar rejects storage classes in typenames
	 and fields.  */
      gcc_assert (storage_class == csc_none && !threadp
		  && !declspecs->inline_p && !declspecs->noreturn_p);
      اگر ((type_quals & TYPE_QUAL_ATOMIC)
	  && درخت_رمز (type) == FUNCTION_TYPE)
	{
	  error_at (loc,
		    "%<_Atomic%>-qualified function type");
	  type_quals &= ~TYPE_QUAL_ATOMIC;
	}
      ورنہ اگر (pedantic && درخت_رمز (type) == FUNCTION_TYPE
	       && type_quals)
	pedwarn (loc, OPT_Wpedantic,
		 "ISO C forbids const or volatile function types");
      اگر (type_quals)
	type = c_build_qualified_type (type, type_quals, orig_qual_type,
				       orig_qual_بالواسطہ);
      واپس type;
    }

  اگر (pedantic && decl_context == میدان
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

  اگر (VOID_TYPE_P (type) && decl_context != PARM
      && !((decl_context != میدان && درخت_رمز (type) != FUNCTION_TYPE)
	    && (storage_class == csc_extern
		|| (current_scope == file_scope
		    && !(storage_class == csc_static
			 || storage_class == csc_رجسٹر)))))
    {
      error_at (loc, "variable or field %qE declared void", name);
      type = integer_type_گرہ;
    }

  /* Now create the decl, which may be a VAR_DECL, a PARM_DECL
     or a FUNCTION_DECL, depending on DECL_CONTEXT and TYPE.  */

  {
    درخت decl;

    اگر (decl_context == PARM)
      {
	درخت promoted_type;
	منطقی array_parameter_p = جھوٹ;

	/* A parameter declared as an array of T is really a pointer to T.
	   One declared as a function is really a pointer to a function.  */

	اگر (درخت_رمز (type) == ARRAY_TYPE)
	  {
	    اگر (!سائز_error)
	      *decl_attrs = build_arg_spec_attribute (type, array_parm_static,
						      *decl_attrs);

	    /* Transfer const-ness of array into that of type pointed to.  */
	    type = درخت_TYPE (type);
	    اگر (orig_qual_type != NULL_درخت)
	      {
		اگر (orig_qual_بالواسطہ == 0)
		  orig_qual_type = درخت_TYPE (orig_qual_type);
		ورنہ
		  orig_qual_بالواسطہ--;
	      }
	    اگر (type_quals)
	      type = c_build_qualified_type (type, type_quals, orig_qual_type,
					     orig_qual_بالواسطہ);

	    /* The pointed-to type may need a decl expr (see above).  */
	    اگر (!TYPE_NAME (type) && c_type_variably_modified_p (type))
	      {
		منطقی bind_p = decl_context == TYPENAME
			      || decl_context == میدان
			      || decl_context == PARM;
		جوڑو_decl_اظہاریہ (loc, type, bind_p ? اظہاریہ : تہی, سچ);
	      }

	    type = c_build_اشارہ_گر_type (type);
	    type_quals = array_ptr_quals;
	    اگر (type_quals)
	      type = c_build_qualified_type (type, type_quals);

	    /* We don't yet implement attributes in this context.  */
	    اگر (array_ptr_attrs != NULL_درخت)
	      warning_at (loc, OPT_Wattributes,
			  "attributes in parameter array declarator ignored");

	    سائز_varies = جھوٹ;
	    array_parameter_p = سچ;
	  }
	ورنہ اگر (درخت_رمز (type) == FUNCTION_TYPE)
	  {
	    اگر (type_quals & TYPE_QUAL_ATOMIC)
	      {
		error_at (loc,
			  "%<_Atomic%>-qualified function type");
		type_quals &= ~TYPE_QUAL_ATOMIC;
	      }
	    ورنہ اگر (type_quals)
	      pedwarn (loc, OPT_Wpedantic,
		       "ISO C forbids qualified function types");
	    اگر (type_quals)
	      type = c_build_qualified_type (type, type_quals);
	    type = c_build_اشارہ_گر_type (type);
	    type_quals = TYPE_UNQUALIFIED;
	  }
	ورنہ اگر (type_quals)
	  type = c_build_qualified_type (type, type_quals);

	decl = build_decl (declarator->id_loc,
			   PARM_DECL, declarator->u.id.id, type);
	اگر (سائز_varies)
	  C_DECL_VARIABLE_سائز (decl) = 1;
	C_ARRAY_PARAMETER (decl) = array_parameter_p;

	/* Compute the type actually passed in the parmlist,
	   for the case where there is no prototype.
	   (For example, shorts and chars are passed as ints.)
	   When there is a prototype, this is overridden later.  */

	اگر (type == error_mark_گرہ)
	  promoted_type = type;
	ورنہ
	  promoted_type = c_type_promotes_مقصد (type);

	DECL_ARG_TYPE (decl) = promoted_type;
	اگر (declspecs->inline_p)
	  pedwarn (loc, 0, "parameter %q+D declared %<inline%>", decl);
	اگر (declspecs->noreturn_p)
	  pedwarn (loc, 0, "parameter %q+D declared %<_Noreturn%>", decl);
      }
    ورنہ اگر (decl_context == میدان)
      {
	/* Note that the grammar rejects storage classes in typenames
	   and fields.  */
	gcc_assert (storage_class == csc_none && !threadp
		    && !declspecs->inline_p && !declspecs->noreturn_p);

	/* Structure field.  It may not be a function.  */

	اگر (درخت_رمز (type) == FUNCTION_TYPE)
	  {
	    error_at (loc, "field %qE declared as a function", name);
	    type = c_build_اشارہ_گر_type (type);
	  }
	ورنہ اگر (درخت_رمز (type) != ERROR_MARK
		 && !COMPLETE_OR_UNBOUND_ARRAY_TYPE_P (type))
	  {
	    اگر (name)
	      error_at (loc, "field %qE has incomplete type", name);
	    ورنہ
	      error_at (loc, "unnamed field has incomplete type");
	    type = error_mark_گرہ;
	  }
	ورنہ اگر (درخت_رمز (type) == ARRAY_TYPE
		 && TYPE_DOMAIN (type) == NULL_درخت)
	  {
	    /* We have a flexible array member through a typedef.
	       Set suitable range.  Whether this is a correct position
	       for a flexible array member will be determined elsewhere.  */
	    اگر (!اندر_system_سرخی_at (داخلہ_location))
	      pedwarn_c90 (loc, OPT_Wpedantic, "ISO C90 does not "
			   "support flexible array members");
	    type = build_distinct_type_copy (TYPE_MAIN_VARIANT (type));
	    TYPE_DOMAIN (type) = build_اشاریہ_type (NULL_درخت);
	    اگر (orig_qual_بالواسطہ == 0)
	      orig_qual_type = NULL_درخت;
	  }
	اگر (type != error_mark_گرہ
	    && !verify_type_context (loc, TCTX_میدان, type))
	  type = error_mark_گرہ;

	type = c_build_qualified_type (type, type_quals, orig_qual_type,
				       orig_qual_بالواسطہ);
	decl = build_decl (declarator->id_loc,
			   میدان_DECL, declarator->u.id.id, type);
	DECL_NONADDRESSABLE_P (decl) = bitfield;
	اگر (bitfield && !declarator->u.id.id)
	  DECL_PADDING_P (decl) = 1;

	اگر (سائز_varies)
	  C_DECL_VARIABLE_سائز (decl) = 1;
      }
    ورنہ اگر (درخت_رمز (type) == FUNCTION_TYPE)
      {
	اگر (storage_class == csc_رجسٹر || threadp || constexprp)
	  {
	    error_at (loc, "invalid storage class for function %qE", name);
	  }
	ورنہ اگر (current_scope != file_scope)
	  {
	    /* Function declaration not at file scope.  Storage
	       classes other than `extern' are not allowed, C99
	       6.7.1p5, and `extern' makes no difference.  However,
	       GCC allows 'auto', perhaps with 'inline', to support
	       nested functions.  */
	    اگر (storage_class == csc_auto)
		pedwarn (loc, OPT_Wpedantic,
			 "invalid storage class for function %qE", name);
	    ورنہ اگر (storage_class == csc_static)
	      {
		error_at (loc, "invalid storage class for function %qE", name);
		اگر (funcdef_flag)
		  storage_class = declspecs->storage_class = csc_none;
		ورنہ
		  واپس NULL_درخت;
	      }
	  }

	decl = build_decl (declarator->id_loc,
			   FUNCTION_DECL, declarator->u.id.id, type);
	decl = build_decl_attribute_variant (decl, decl_attr);

	اگر (type_quals & TYPE_QUAL_ATOMIC)
	  {
	    error_at (loc,
		      "%<_Atomic%>-qualified function type");
	    type_quals &= ~TYPE_QUAL_ATOMIC;
	  }
	ورنہ اگر (pedantic && type_quals && !DECL_اندر_SYSTEM_سرخی (decl))
	  pedwarn (loc, OPT_Wpedantic,
		   "ISO C forbids qualified function types");

	/* Every function declaration is an external reference
	   (DECL_EXTERNAL) except for those which are not at file
	   scope and are explicitly declared "auto".  This is
	   forbidden by standard C (C99 6.7.1p5) and is interpreted by
	   GCC to signify a forward declaration of a nested function.  */
	اگر (storage_class == csc_auto && current_scope != file_scope)
	  DECL_EXTERNAL (decl) = 0;
	/* In C99, a function which is declared 'inline' with 'extern'
	   is not an external reference (which is confusing).  It
	   means that the later definition of the function must be output
	   in this file, C99 6.7.4p6.  In GNU C89, a function declared
	   'extern inline' is an external reference.  */
	ورنہ اگر (declspecs->inline_p && storage_class != csc_static)
	  DECL_EXTERNAL (decl) = ((storage_class == csc_extern)
				  == flag_gnu89_inline);
	ورنہ
	  DECL_EXTERNAL (decl) = !initialized;

	/* Record absence of global scope for `static' or `auto'.  */
	درخت_عوامی (decl)
	  = !(storage_class == csc_static || storage_class == csc_auto);

	/* For a function definition, record the argument information
	   block where store_parm_decls will look for it.  */
	اگر (funcdef_flag)
	  current_function_arg_info = arg_info;

	اگر (declspecs->default_int_p)
	  C_FUNCTION_IMPLICIT_INT (decl) = 1;

	/* Record presence of `inline' and `_Noreturn', if it is
	   reasonable.  */
	اگر (flag_hosted && MAIN_NAME_P (declarator->u.id.id))
	  {
	    اگر (declspecs->inline_p)
	      pedwarn (loc, 0, "cannot inline function %<main%>");
	    اگر (declspecs->noreturn_p)
	      pedwarn (loc, 0, "%<main%> declared %<_Noreturn%>");
	  }
	ورنہ
	  {
	    اگر (declspecs->inline_p)
	      /* Record that the function is declared `inline'.  */
	      DECL_DECLARED_INLINE_P (decl) = 1;
	    اگر (declspecs->noreturn_p)
	      {
		اگر (flag_isoc99)
		  pedwarn_c99 (loc, OPT_Wpedantic,
			       "ISO C99 does not support %<_Noreturn%>");
		ورنہ
		  pedwarn_c99 (loc, OPT_Wpedantic,
			       "ISO C90 does not support %<_Noreturn%>");
		درخت_THIS_VOLATILE (decl) = 1;
	      }
	  }

	/* C99 6.2.2p7: It is invalid (compile-time undefined
	   behavior) to create an 'extern' declaration for a
	   function if there is a global declaration that is
	   'static' and the global declaration is not visible.
	   (If the static declaration _is_ currently visible,
	   the 'extern' declaration is taken to refer to that decl.) */
	اگر (!initialized
	    && درخت_عوامی (decl)
	    && current_scope != file_scope)
	  {
	    درخت global_decl  = identifier_global_قدر (declarator->u.id.id);
	    درخت visible_decl = lookup_name (declarator->u.id.id);

	    اگر (global_decl
		&& global_decl != visible_decl
		&& VAR_OR_FUNCTION_DECL_P (global_decl)
		&& !درخت_عوامی (global_decl))
	      error_at (loc, "function previously declared %<static%> "
			"redeclared %<extern%>");
	  }
      }
    ورنہ
      {
	/* It's a variable.  */
	/* An uninitialized decl with `extern' is a reference.  */
	صحیح extern_ref = !initialized && storage_class == csc_extern;

	اگر (constexprp)
	  {
	    /* The type of a constexpr variable must not be variably
	       modified, volatile, atomic or restrict qualified or
	       have a member with such a qualifier.  const
	       qualification is implicitly added, and, at file scope,
	       has internal linkage.  */
	    اگر (c_type_variably_modified_p (type))
	      error_at (loc, "%<constexpr%> object has variably modified "
			"type");
	    اگر (type_quals
		& (TYPE_QUAL_VOLATILE | TYPE_QUAL_RESTRICT | TYPE_QUAL_ATOMIC))
	      error_at (loc, "invalid qualifiers for %<constexpr%> object");
	    ورنہ
	      {
		درخت type_no_array = strip_array_types (type);
		اگر (ریکارڈ_OR_UNION_TYPE_P (type_no_array)
		    && C_TYPE_FIELDS_NON_CONSTEXPR (type_no_array))
		  error_at (loc, "invalid qualifiers for field of "
			    "%<constexpr%> object");
	      }
	    type_quals |= TYPE_QUAL_CONST;
	    اگر (current_scope == file_scope)
	      storage_class = csc_static;
	  }

	type = c_build_qualified_type (type, type_quals, orig_qual_type,
				       orig_qual_بالواسطہ);

	/* C99 6.2.2p7: It is invalid (compile-time undefined
	   behavior) to create an 'extern' declaration for a
	   variable if there is a global declaration that is
	   'static' and the global declaration is not visible.
	   (If the static declaration _is_ currently visible,
	   the 'extern' declaration is taken to refer to that decl.) */
	اگر (extern_ref && current_scope != file_scope)
	  {
	    درخت global_decl  = identifier_global_قدر (declarator->u.id.id);
	    درخت visible_decl = lookup_name (declarator->u.id.id);

	    اگر (global_decl
		&& global_decl != visible_decl
		&& VAR_P (global_decl)
		&& !درخت_عوامی (global_decl))
	      error_at (loc, "variable previously declared %<static%> "
			"redeclared %<extern%>");
	  }

	decl = build_decl (declarator->id_loc,
			   VAR_DECL, declarator->u.id.id, type);
	اگر (سائز_varies)
	  C_DECL_VARIABLE_سائز (decl) = 1;
	اگر (constexprp)
	  C_DECL_DECLARED_CONSTEXPR (decl) = 1;

	اگر (declspecs->inline_p)
	  pedwarn (loc, 0, "variable %q+D declared %<inline%>", decl);
	اگر (declspecs->noreturn_p)
	  pedwarn (loc, 0, "variable %q+D declared %<_Noreturn%>", decl);

	/* At file scope, an initialized extern declaration may follow
	   a static declaration.  In that case, DECL_EXTERNAL will be
	   reset later in start_decl.  */
	DECL_EXTERNAL (decl) = (storage_class == csc_extern);

	/* At file scope, the presence of a `static' or `register' storage
	   class specifier, or the absence of all storage class specifiers
	   makes this declaration a definition (perhaps tentative).  Also,
	   the absence of `static' makes it public.  */
	اگر (current_scope == file_scope)
	  {
	    درخت_عوامی (decl) = storage_class != csc_static;
	    درخت_STATIC (decl) = !extern_ref;
	  }
	/* Not at file scope, only `static' makes a static definition.  */
	ورنہ
	  {
	    درخت_STATIC (decl) = (storage_class == csc_static);
	    درخت_عوامی (decl) = extern_ref;
	  }

	// NB: Set a tentative TLS model to avoid tls_model attribute
	// warnings due to lack of thread storage duration.  It will
	// be updated by c_decl_attributes later.
	اگر (threadp)
	  سیٹ_decl_tls_model (decl, TLS_MODEL_REAL);
      }

    اگر ((storage_class == csc_extern
	 || (storage_class == csc_none
	     && درخت_رمز (type) == FUNCTION_TYPE
	     && !funcdef_flag))
	&& c_type_variably_modified_p (type))
      {
	/* C99 6.7.5.2p2 */
	اگر (درخت_رمز (type) == FUNCTION_TYPE)
	  error_at (loc, "non-nested function with variably modified type");
	ورنہ
	  error_at (loc, "object with variably modified type must have "
	      	    "no linkage");
      }

    /* For nested functions disqualify ones taking VLAs by value
       from inlining since the middle-end cannot deal with this.
       ???  We should arrange for those to be passed by reference
       with emitting the copy on the caller side in the frontend.  */
    اگر (storage_class == csc_none
	&& درخت_رمز (type) == FUNCTION_TYPE)
      برائے (درخت al = TYPE_ARG_TYPES (type); al; al = درخت_CHAIN (al))
	{
	  درخت arg = درخت_قدر (al);
	  اگر (arg != error_mark_گرہ
	      && C_TYPE_VARIABLE_سائز (arg))
	    {
	      DECL_UNINLINABLE (decl) = 1;
	      توڑو;
	    }
	}

    /* Record `register' declaration for warnings on &
       and in case doing stupid register allocation.  */

    اگر (storage_class == csc_رجسٹر
	&& درخت_رمز (type) != FUNCTION_TYPE)
      {
	C_DECL_رجسٹر (decl) = 1;
	DECL_رجسٹر (decl) = 1;
      }

    /* Record constancy and volatility.  */
    c_apply_type_quals_مقصد_decl (type_quals, decl);

    /* Apply _Alignas specifiers.  */
    اگر (alignas_align)
      {
	سیٹ_DECL_ALIGN (decl, alignas_align * بٹ_فی_UNIT);
	DECL_USER_ALIGN (decl) = 1;
      }

    /* If a type has volatile components, it should be stored in memory.
       Otherwise, the fact that those components are volatile
       will be ignored, and would even crash the compiler.
       Of course, this only makes sense on  VAR,PARM, and RESULT decl's.   */
    اگر (C_TYPE_FIELDS_VOLATILE (درخت_TYPE (decl))
	&& (VAR_P (decl) ||  درخت_رمز (decl) == PARM_DECL
	  || درخت_رمز (decl) == نتیجہ_DECL))
      {
	/* It is not an error for a structure with volatile fields to
	   be declared register, but reset DECL_REGISTER since it
	   cannot actually go in a register.  */
	صحیح was_reg = C_DECL_رجسٹر (decl);
	C_DECL_رجسٹر (decl) = 0;
	DECL_رجسٹر (decl) = 0;
	c_mark_addressable (decl);
	C_DECL_رجسٹر (decl) = was_reg;
      }

  /* This is the earliest point at which we might know the assembler
     name of a variable.  Thus, if it's known before this, die horribly.  */
    gcc_assert (!HAS_DECL_ASSEMBLER_NAME_P (decl)
		|| !DECL_ASSEMBLER_NAME_سیٹ_P (decl));

    اگر (warn_cxx_compat
	&& VAR_P (decl)
	&& درخت_عوامی (decl)
	&& درخت_STATIC (decl)
	&& (ریکارڈ_OR_UNION_TYPE_P (درخت_TYPE (decl))
	    || درخت_رمز (درخت_TYPE (decl)) == ENUMERAL_TYPE)
	&& TYPE_NAME (درخت_TYPE (decl)) == NULL_درخت)
      warning_at (DECL_ماخذ_LOCATION (decl), OPT_Wc___compat,
		  "non-local variable %qD with anonymous type is "
		  "questionable in C++", decl);

    واپس decl;
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

ساکن درخت
grokparms (ساخت c_arg_info *arg_info, منطقی funcdef_flag)
{
  درخت arg_types = arg_info->types;

  اگر (funcdef_flag && arg_info->had_vla_unspec)
    {
      /* A function definition isn't function prototype scope C99 6.2.1p4.  */
      /* C99 6.7.5.2p4 */
      error ("%<[*]%> not allowed in other than function prototype scope");
    }

  اگر (arg_types == NULL_درخت && !funcdef_flag && !flag_isoc23
      && !اندر_system_سرخی_at (داخلہ_location))
    warning (OPT_Wstrict_prototypes,
	     "function declaration isn%'t a prototype");

  اگر (arg_types == error_mark_گرہ)
    /* Don't set TYPE_ARG_TYPES in this case.  */
    واپس NULL_درخت;

  ورنہ اگر (arg_types && درخت_رمز (درخت_قدر (arg_types)) == IDENTIFIER_گرہ)
    {
      اگر (!funcdef_flag)
	{
	  permerror_opt (داخلہ_location,
			 OPT_Wdeclaration_missing_parameter_type,
			 "parameter names (without types) in "
			 "function declaration");
	  arg_info->parms = NULL_درخت;
	}
      ورنہ
	arg_info->parms = arg_info->types;

      arg_info->types = NULL_درخت;
      واپس NULL_درخت;
    }
  ورنہ
    {
      درخت parm, type, typelt;
      غیرعلامتی صحیح parmno;

      /* In C23, convert () to (void).  */
      اگر (flag_isoc23
	  && !arg_types
	  && !arg_info->parms
	  && !arg_info->no_named_دلائل_stdarg_p)
	{
	  arg_types = arg_info->types = void_list_گرہ;
	  arg_info->c23_خالی_خانے_parens = 1;
	}

      /* If there is a parameter of incomplete type in a definition,
	 this is an error.  In a declaration this is valid, and a
	 struct or union type may be completed later, before any calls
	 or definition of the function.  In the case where the tag was
	 first declared within the parameter list, a warning has
	 already been given.  If a parameter has void type, then
	 this has already received an error (constraint violation in C2Y,
	 previously implicitly undefined behavior).  */

      برائے (parm = arg_info->parms, typelt = arg_types, parmno = 1;
	   parm;
	   parm = DECL_CHAIN (parm), typelt = درخت_CHAIN (typelt), parmno++)
	{
	  type = درخت_قدر (typelt);
	  اگر (type == error_mark_گرہ)
	    جاری;

	  اگر (!COMPLETE_TYPE_P (type))
	    {
	      اگر (funcdef_flag)
		{
		  اگر (DECL_NAME (parm))
		    error_at (داخلہ_location,
			      "parameter %u (%q+D) has incomplete type",
			      parmno, parm);
		  ورنہ
		    error_at (DECL_ماخذ_LOCATION (parm),
			      "parameter %u has incomplete type",
			      parmno);

		  درخت_قدر (typelt) = error_mark_گرہ;
		  درخت_TYPE (parm) = error_mark_گرہ;
		  arg_types = NULL_درخت;
		}
	    }

	  اگر (DECL_NAME (parm) && درخت_مستعمل (parm))
	    warn_if_shadowing (parm);
	}
      واپس arg_types;
    }
}

/* Allocate and initialize a c_arg_info structure from the parser's
   obstack.  */

ساخت c_arg_info *
build_arg_info (خالی)
{
  ساخت c_arg_info *ret = XOBNEW (&parser_obstack, ساخت c_arg_info);
  ret->parms = NULL_درخت;
  ret->لیبل_فہرست = تہی;
  ret->types = NULL_درخت;
  ret->others = NULL_درخت;
  ret->pending_sizes = تہی;
  ret->had_vla_unspec = 0;
  ret->no_named_دلائل_stdarg_p = 0;
  ret->c23_خالی_خانے_parens = 0;
  واپس ret;
}

/* Take apart the current scope and return a c_arg_info structure with
   info on a parameter list just parsed.

   This structure is later fed to 'grokparms' and 'store_parm_decls'.

   ELLIPSIS being true means the argument list ended in '...' so don't
   append a sentinel (void_list_node) to the end of the type-list.

   EXPR is NULL or an expression that needs to be evaluated for the
   side effects of array size expressions in the parameters.  */

ساخت c_arg_info *
get_parm_info (منطقی ellipsis, درخت اظہاریہ)
{
  ساخت c_binding *b = current_scope->bindings;
  ساخت c_arg_info *arg_info = build_arg_info ();

  درخت parms = NULL_درخت;
  vec<c_arg_لیبل, va_gc> *لیبل_فہرست = تہی;
  درخت types = NULL_درخت;
  درخت others = NULL_درخت;

  منطقی gave_void_only_once_err = جھوٹ;

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
  اگر (b->پچھلا == 0			    /* one binding */
      && درخت_رمز (b->decl) == PARM_DECL   /* which is a parameter */
      && !DECL_NAME (b->decl)               /* anonymous */
      && VOID_TYPE_P (درخت_TYPE (b->decl))) /* of void type */
    {
      اگر (TYPE_QUALS (درخت_TYPE (b->decl)) != TYPE_UNQUALIFIED
	  || C_DECL_رجسٹر (b->decl))
	error_at (b->locus, "%<void%> as only parameter may not be qualified");

      /* There cannot be an ellipsis.  */
      اگر (ellipsis)
	error_at (b->locus, "%<void%> must be the only parameter");

      arg_info->types = void_list_گرہ;
      واپس arg_info;
    }

  اگر (!ellipsis)
    types = void_list_گرہ;

  /* Break up the bindings list into parms, tags, types, and others;
     apply sanity checks; purge the name-to-decl bindings.  */
  جب (b)
    {
      درخت decl = b->decl;
      درخت type = درخت_TYPE (decl);
      c_arg_لیبل لیبل;
      ثابت حرف *keyword;

      انتخاب (درخت_رمز (decl))
	{
	حالت PARM_DECL:
	  اگر (b->id)
	    {
	      gcc_assert (I_علامت_BINDING (b->id) == b);
	      I_علامت_BINDING (b->id) = b->shadowed;
	    }

	  /* Check for forward decls that never got their actual decl.  */
	  اگر (درخت_ASM_WRITTEN (decl))
	    error_at (b->locus,
		      "parameter %q+D has just a forward declaration", decl);
	  /* Check for (..., void, ...) and named void parameters and issue an
	     error.  */
	  ورنہ اگر (VOID_TYPE_P (type))
	    {
	      اگر (!gave_void_only_once_err)
		{
		  error_at (b->locus,
			    "%<void%> must be the only parameter and unnamed");
		  gave_void_only_once_err = سچ;
		}
	    }
	  ورنہ
	    {
	      /* Valid parameter, add it to the list.  */
	      DECL_CHAIN (decl) = parms;
	      parms = decl;

	      /* Since there is a prototype, args are passed in their
		 declared types.  The back end may override this later.  */
	      DECL_ARG_TYPE (decl) = type;
	      types = درخت_cons (0, type, types);
	    }
	  توڑو;

	حالت ENUMERAL_TYPE: keyword = "enum"; جاؤ لیبل;
	حالت UNION_TYPE:    keyword = "union"; جاؤ لیبل;
	حالت ریکارڈ_TYPE:   keyword = "struct"; جاؤ لیبل;
	لیبل:
	  /* Types may not have tag-names, in which case the type
	     appears in the bindings list with b->id NULL.  */
	  اگر (b->id)
	    {
	      gcc_assert (I_لیبل_BINDING (b->id) == b);
	      I_لیبل_BINDING (b->id) = b->shadowed;
	    }

	  /* Warn about any struct, union or enum tags defined in a
	     parameter list.  The scope of such types is limited to
	     the parameter list, which is rarely if ever desirable
	     (it's impossible to call such a function with type-
	     correct arguments).  An anonymous union parm type is
	     meaningful as a GNU extension, so don't warn for that.  */
	  اگر (درخت_رمز (decl) != UNION_TYPE || b->id != NULL_درخت)
	    {
	      اگر (b->id)
		{
		  /* The %s will be one of 'struct', 'union', or 'enum'.  */
		  اگر (!flag_isoc23 || !COMPLETE_TYPE_P (decl))
		    warning_at (b->locus, 0,
				"%<%s %E%> declared inside parameter list"
				" will not be visible outside of this definition or"
				" declaration", keyword, b->id);
		}
	      ورنہ
		/* The %s will be one of 'struct', 'union', or 'enum'.  */
		warning_at (b->locus, 0,
			    "anonymous %s declared inside parameter list"
			    " will not be visible outside of this definition or"
			    " declaration", keyword);
	    }

	  لیبل.id = b->id;
	  لیبل.type = decl;
	  vec_محفوظ_ڈالو (لیبل_فہرست, لیبل);
	  توڑو;

	حالت FUNCTION_DECL:
	  /* FUNCTION_DECLs appear when there is an implicit function
	     declaration in the parameter list.  */
	  gcc_assert (b->nested || نظر_آیا_error ());
	  جاؤ سیٹ_shadowed;

	حالت CONST_DECL:
	حالت TYPE_DECL:
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

	حالت ERROR_MARK:
	سیٹ_shadowed:
	  /* error_mark_node appears here when we have an undeclared
	     variable.  Just throw it away.  */
	  اگر (b->id)
	    {
	      gcc_assert (I_علامت_BINDING (b->id) == b);
	      I_علامت_BINDING (b->id) = b->shadowed;
	    }
	  توڑو;

	  /* Other things that might be encountered.  */
	حالت LABEL_DECL:
	حالت VAR_DECL:
	طےشدہ:
	  gcc_unreachable ();
	}

      b = free_binding_and_advance (b);
    }

  arg_info->parms = parms;
  arg_info->لیبل_فہرست = لیبل_فہرست;
  arg_info->types = types;
  arg_info->others = others;
  arg_info->pending_sizes = اظہاریہ;
  arg_info->no_named_دلائل_stdarg_p = ellipsis && !types;
  واپس arg_info;
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

ساخت c_typespec
parser_xref_لیبل (location_t loc, شمار درخت_رمز_2 رمز, درخت name,
		 منطقی have_std_attrs, درخت attrs, منطقی has_enum_type_specifier)
{
  ساخت c_typespec ret;
  درخت ref;
  location_t refloc;

  ret.اظہاریہ = NULL_درخت;
  ret.اظہاریہ_const_operands = سچ;
  ret.has_enum_type_specifier = has_enum_type_specifier;

  /* If a cross reference is requested, look up the type already
     defined for this tag and return it.  If an enum type specifier is
     present, only a definition in the current scope is relevant.  */

  ref = lookup_لیبل (رمز, name, has_enum_type_specifier, &refloc);

  /* If the visible type is still being defined, see if there is
     an earlier definition (which may be complete).  We do not
     have to loop because nested redefinitions are not allowed.  */
  اگر (flag_isoc23 && ref && C_TYPE_BEING_DEFINED (ref))
    {
      درخت vis = پچھلا_لیبل (ref);
      اگر (vis)
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
  ret.قسم = (ref
	      ? (have_std_attrs ? ctsk_tagref_attrs : ctsk_tagref)
	      : (have_std_attrs ? ctsk_tagfirstref_attrs : ctsk_tagfirstref));
  اگر (ref && درخت_رمز (ref) == رمز)
    {
      decl_اوصاف (&ref, attrs, (صحیح) ATTR_FLAG_TYPE_اندر_رکھو);
      اگر (C_TYPE_DEFINED_اندر_STRUCT (ref)
	  && loc != UNKNOWN_LOCATION
	  && warn_cxx_compat)
	{
	  auto_diagnostic_گروہ d;
	  انتخاب (رمز)
	    {
	    حالت ENUMERAL_TYPE:
	      اگر (warning_at (loc, OPT_Wc___compat,
			      ("enum type defined in struct or union "
			       "is not visible in C++")))
		  inform (refloc, "enum type defined here");
	      توڑو;
	    حالت ریکارڈ_TYPE:
	      اگر (warning_at (loc, OPT_Wc___compat,
			      ("struct defined in struct or union "
			       "is not visible in C++")))
		inform (refloc, "struct defined here");
	      توڑو;
	    حالت UNION_TYPE:
	      اگر (warning_at (loc, OPT_Wc___compat,
			      ("union defined in struct or union "
			       "is not visible in C++")))
		inform (refloc, "union defined here");
	      توڑو;
	    طےشدہ:
	      gcc_unreachable();
	    }
	}

      ret.spec = ref;
      واپس ret;
    }

  /* If no such tag is yet defined, create a forward-reference node
     and record it as the "definition".
     When a real declaration of this type is found,
     the forward-reference will be altered into a real type.  */

  ref = make_گرہ (رمز);
  اگر (flag_isoc23 || رمز == ENUMERAL_TYPE)
    سیٹ_TYPE_STRUCTURAL_EQUALITY (ref);
  اگر (رمز == ENUMERAL_TYPE)
    {
      /* Give the type a default layout like unsigned int
	 to avoid crashing if it does not get defined.  */
      سیٹ_TYPE_منوال (ref, TYPE_منوال (unsigned_type_گرہ));
      سیٹ_TYPE_ALIGN (ref, TYPE_ALIGN (unsigned_type_گرہ));
      TYPE_USER_ALIGN (ref) = 0;
      TYPE_UNSIGNED (ref) = 1;
      TYPE_PRECISION (ref) = TYPE_PRECISION (unsigned_type_گرہ);
      TYPE_MIN_قدر (ref) = TYPE_MIN_قدر (unsigned_type_گرہ);
      TYPE_MAX_قدر (ref) = TYPE_MAX_قدر (unsigned_type_گرہ);
      ENUM_FIXED_UNDERLYING_TYPE_P (ref) = has_enum_type_specifier;
    }

  pushtag (loc, name, ref);
  decl_اوصاف (&ref, attrs, (صحیح) ATTR_FLAG_TYPE_اندر_رکھو);
  اگر (اندر_underspecified_init)
    error_at (loc, "%qT declared in underspecified object initializer",
	      ref);

  ret.spec = ref;
  واپس ret;
}

/* Get the struct, enum or union (CODE says which) with tag NAME.
   Define the tag as a forward-reference if it is not defined.
   Return a tree for the type.  */

درخت
xref_لیبل (شمار درخت_رمز_2 رمز, درخت name)
{
  واپس parser_xref_لیبل (داخلہ_location, رمز, name, جھوٹ, NULL_درخت,
			  جھوٹ).spec;
}

/* Make sure that the tag NAME is defined *in the current scope*
   at least as a forward reference.
   LOC is the location of the struct's definition.
   CODE says which kind of tag NAME ought to be.

   This stores the current value of the file static STRUCT_PARSE_INFO
   in *ENCLOSING_STRUCT_PARSE_INFO, and points STRUCT_PARSE_INFO at a
   new c_struct_parse_info structure.  The old value of
   STRUCT_PARSE_INFO is restored in finish_struct.  */

درخت
آغاز_struct (location_t loc, شمار درخت_رمز_2 رمز, درخت name,
	      جماعت c_struct_parse_info **enclosing_struct_parse_info)
{
  /* If there is already a tag defined at this scope
     (as a forward reference), just return it.  */

  درخت ref = NULL_درخت;
  location_t refloc = UNKNOWN_LOCATION;

  اگر (name != NULL_درخت)
    ref = lookup_لیبل (رمز, name, سچ, &refloc);

  /* For C23, even if we already have a completed definition,
     we do not use it. We will check for consistency later.
     If we are in a nested redefinition the type is not
     complete. We will then detect this below.  */
  اگر (flag_isoc23 && ref && TYPE_سائز (ref))
    ref = NULL_درخت;

  اگر (ref && درخت_رمز (ref) == رمز)
    {
      اگر (TYPE_STUB_DECL (ref))
	refloc = DECL_ماخذ_LOCATION (TYPE_STUB_DECL (ref));

      اگر (TYPE_سائز (ref))
	{
	  auto_diagnostic_گروہ d;
	  اگر (رمز == UNION_TYPE)
	    error_at (loc, "redefinition of %<union %E%>", name);
	  ورنہ
	    error_at (loc, "redefinition of %<struct %E%>", name);
	  اگر (refloc != UNKNOWN_LOCATION)
	    inform (refloc, "originally defined here");
	  /* Don't create structures using a name already in use.  */
	  ref = NULL_درخت;
	}
      ورنہ اگر (C_TYPE_BEING_DEFINED (ref))
	{
	  اگر (رمز == UNION_TYPE)
	    error_at (loc, "nested redefinition of %<union %E%>", name);
	  ورنہ
	    error_at (loc, "nested redefinition of %<struct %E%>", name);
	  /* Don't bother to report "originally defined here" for a
	     nested redefinition; the original definition should be
	     obvious.  */
	  /* Don't create structures that contain themselves.  */
	  ref = NULL_درخت;
	}
    }

  /* Otherwise create a forward-reference just so the tag is in scope.  */

  اگر (ref == NULL_درخت || درخت_رمز (ref) != رمز)
    {
      ref = make_گرہ (رمز);
      اگر (flag_isoc23)
	سیٹ_TYPE_STRUCTURAL_EQUALITY (ref);
      pushtag (loc, name, ref);
    }

  C_TYPE_BEING_DEFINED (ref) = 1;
  برائے (درخت v = TYPE_MAIN_VARIANT (ref); v; v = TYPE_اگلا_VARIANT (v))
    TYPE_PACKED (v) = flag_pack_struct;

  *enclosing_struct_parse_info = struct_parse_info;
  struct_parse_info = نیا c_struct_parse_info ();
  struct_parse_info->refloc = refloc;

  /* FIXME: This will issue a warning for a use of a type defined
     within a statement expr used within sizeof, et. al.  This is not
     terribly serious as C++ doesn't permit statement exprs within
     sizeof anyhow.  */
  اگر (warn_cxx_compat
      && (اندر_sizeof || اندر_typeof || اندر_alignof || اندر_countof))
    warning_at (loc, OPT_Wc___compat,
		"defining type in %qs expression is invalid in C++",
		(اندر_sizeof ? "sizeof"
		 : اندر_typeof ? "typeof"
		 : اندر_alignof ? "alignof"
		 : "_Countof"));

  اگر (اندر_underspecified_init)
    error_at (loc, "%qT defined in underspecified object initializer", ref);

  واپس ref;
}

/* Process the specs, declarator and width (NULL if omitted)
   of a structure component, returning a FIELD_DECL node.
   WIDTH is non-NULL for bit-fields only, and is an INTEGER_CST node.
   DECL_ATTRS is as for grokdeclarator.

   LOC is the location of the structure component.

   This is done during the parsing of the struct declaration.
   The FIELD_DECL nodes are chained together and the lot of them
   are ultimately passed to `build_struct' to make the RECORD_TYPE node.  */

درخت
grokfield (location_t loc,
	   ساخت c_declarator *declarator, ساخت c_declspecs *declspecs,
	   درخت چوڑائی, درخت *decl_attrs, درخت *اظہاریہ)
{
  درخت قدر;

  اگر (declarator->قسم == cdk_id && declarator->u.id.id == NULL_درخت
      && چوڑائی == NULL_درخت)
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

      درخت type = declspecs->type;
      منطقی ok = جھوٹ;

      اگر (ریکارڈ_OR_UNION_TYPE_P (type)
	  && (flag_ms_extensions
	      || flag_plan9_extensions
	      || !declspecs->typedef_p))
	{
	  اگر (flag_ms_extensions || flag_plan9_extensions)
	    ok = سچ;
	  ورنہ اگر (TYPE_NAME (type) == تہی)
	    ok = سچ;
	  ورنہ
	    ok = جھوٹ;
	}
      اگر (!ok)
	{
	  pedwarn (loc, 0, "declaration does not declare anything");
	  واپس NULL_درخت;
	}
      اگر (flag_isoc99)
	pedwarn_c99 (loc, OPT_Wpedantic,
		     "ISO C99 doesn%'t support unnamed structs/unions");
      ورنہ
	pedwarn_c99 (loc, OPT_Wpedantic,
		     "ISO C90 doesn%'t support unnamed structs/unions");
    }

  قدر = grokdeclarator (declarator, declspecs, میدان, جھوٹ,
			  چوڑائی ? &چوڑائی : تہی, decl_attrs, اظہاریہ, تہی,
			  DEPRECATED_معمول);

  /* When this field has name, its type is a top level type, we should
     call verify_counted_by_for_top_anonymous_type.  */
  اگر (DECL_NAME (قدر) != NULL_درخت
      && declspecs->typespec_قسم == ctsk_tagdef)
    verify_counted_by_for_چوٹی_anonymous_type (declspecs->type);

  اختتام_decl (قدر, loc, NULL_درخت, NULL_درخت, NULL_درخت);
  DECL_INITIAL (قدر) = چوڑائی;
  اگر (چوڑائی)
    سیٹ_DECL_C_ثنائی_ہندسہ_میدان (قدر);

  اگر (warn_cxx_compat && DECL_NAME (قدر) != NULL_درخت)
    {
      /* If we currently have a binding for this field, set the
	 in_struct field in the binding, so that we warn about lookups
	 which find it.  */
      ساخت c_binding *b = I_علامت_BINDING (DECL_NAME (قدر));
      اگر (b != تہی)
	{
	  /* If the in_struct field is not yet set, push it on a list
	     to be cleared when this struct is finished.  */
	  اگر (!b->اندر_struct)
	    {
	      struct_parse_info->fields.محفوظ_ڈالو (b);
	      b->اندر_struct = 1;
	    }
	}
    }

  واپس قدر;
}

/* Subroutine of detect_field_duplicates: return whether X and Y,
   which are both fields in the same struct, have duplicate field
   names.  */

ساکن منطقی
is_duplicate_میدان (درخت x, درخت y)
{
  اگر (DECL_NAME (x) != NULL_درخت && DECL_NAME (x) == DECL_NAME (y))
    واپس سچ;

  /* When using -fplan9-extensions, an anonymous field whose name is a
     typedef can duplicate a field name.  */
  اگر (flag_plan9_extensions
      && (DECL_NAME (x) == NULL_درخت || DECL_NAME (y) == NULL_درخت))
    {
      درخت xt, xn, yt, yn;

      xt = درخت_TYPE (x);
      اگر (DECL_NAME (x) != NULL_درخت)
	xn = DECL_NAME (x);
      ورنہ اگر (ریکارڈ_OR_UNION_TYPE_P (xt)
	       && TYPE_NAME (xt) != NULL_درخت
	       && درخت_رمز (TYPE_NAME (xt)) == TYPE_DECL)
	xn = DECL_NAME (TYPE_NAME (xt));
      ورنہ
	xn = NULL_درخت;

      yt = درخت_TYPE (y);
      اگر (DECL_NAME (y) != NULL_درخت)
	yn = DECL_NAME (y);
      ورنہ اگر (ریکارڈ_OR_UNION_TYPE_P (yt)
	       && TYPE_NAME (yt) != NULL_درخت
	       && درخت_رمز (TYPE_NAME (yt)) == TYPE_DECL)
	yn = DECL_NAME (TYPE_NAME (yt));
      ورنہ
	yn = NULL_درخت;

      اگر (xn != NULL_درخت && xn == yn)
	واپس سچ;
    }

  واپس جھوٹ;
}

/* Subroutine of detect_field_duplicates: add the fields of FIELDLIST
   to HTAB, giving errors for any duplicates.  */

ساکن خالی
detect_میدان_duplicates_hash (درخت fieldlist,
			      hash_جدول<nofree_ptr_hash <درخت_گرہ> > *htab)
{
  درخت x, y;
  درخت_گرہ **خانہ;

  برائے (x = fieldlist; x ; x = DECL_CHAIN (x))
    اگر ((y = DECL_NAME (x)) != NULL_درخت)
      {
	خانہ = htab->ڈھونڈو_خانہ (y, داخل_کرو);
	اگر (*خانہ)
	  {
	    error ("duplicate member %q+D", x);
	    DECL_NAME (x) = NULL_درخت;
	  }
	*خانہ = y;
      }
    ورنہ اگر (ریکارڈ_OR_UNION_TYPE_P (درخت_TYPE (x)))
      {
	detect_میدان_duplicates_hash (TYPE_FIELDS (درخت_TYPE (x)), htab);

	/* When using -fplan9-extensions, an anonymous field whose
	   name is a typedef can duplicate a field name.  */
	اگر (flag_plan9_extensions
	    && TYPE_NAME (درخت_TYPE (x)) != NULL_درخت
	    && درخت_رمز (TYPE_NAME (درخت_TYPE (x))) == TYPE_DECL)
	  {
	    درخت xn = DECL_NAME (TYPE_NAME (درخت_TYPE (x)));
	    خانہ = htab->ڈھونڈو_خانہ (xn, داخل_کرو);
	    اگر (*خانہ)
	      error ("duplicate member %q+D", TYPE_NAME (درخت_TYPE (x)));
	    *خانہ = xn;
	  }
      }
}

/* Generate an error for any duplicate field names in FIELDLIST.  Munge
   the list such that this does not present a problem later.  */

ساکن خالی
detect_میدان_duplicates (درخت fieldlist)
{
  درخت x, y;
  صحیح timeout = 10;

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
  اگر (c_dialect_objc ())
    اگر (objc_detect_میدان_duplicates (جھوٹ))
      واپس;

  /* First, see if there are more than "a few" fields.
     This is trivially true if there are zero or one fields.  */
  اگر (!fieldlist || !DECL_CHAIN (fieldlist))
    واپس;
  x = fieldlist;
  کرو {
    timeout--;
    اگر (DECL_NAME (x) == NULL_درخت
	&& ریکارڈ_OR_UNION_TYPE_P (درخت_TYPE (x)))
      timeout = 0;
    x = DECL_CHAIN (x);
  } جب (timeout > 0 && x);

  /* If there were "few" fields and no anonymous structures or unions,
     avoid the overhead of allocating a hash table.  Instead just do
     the nested traversal thing.  */
  اگر (timeout > 0)
    {
      برائے (x = DECL_CHAIN (fieldlist); x; x = DECL_CHAIN (x))
	/* When using -fplan9-extensions, we can have duplicates
	   between typedef names and fields.  */
	اگر (DECL_NAME (x)
	    || (flag_plan9_extensions
		&& DECL_NAME (x) == NULL_درخت
		&& ریکارڈ_OR_UNION_TYPE_P (درخت_TYPE (x))
		&& TYPE_NAME (درخت_TYPE (x)) != NULL_درخت
		&& درخت_رمز (TYPE_NAME (درخت_TYPE (x))) == TYPE_DECL))
	  {
	    برائے (y = fieldlist; y != x; y = درخت_CHAIN (y))
	      اگر (is_duplicate_میدان (y, x))
		{
		  error ("duplicate member %q+D", x);
		  DECL_NAME (x) = NULL_درخت;
		}
	  }
    }
  ورنہ
    {
      hash_جدول<nofree_ptr_hash <درخت_گرہ> > htab (37);
      detect_میدان_duplicates_hash (fieldlist, &htab);
    }
}

/* Finish up struct info used by -Wc++-compat.  */

ساکن خالی
warn_cxx_compat_اختتام_struct (درخت fieldlist, شمار درخت_رمز_2 رمز,
			       location_t ریکارڈ_loc)
{
  غیرعلامتی صحیح ix;
  درخت x;
  ساخت c_binding *b;

  اگر (fieldlist == NULL_درخت)
    {
      اگر (رمز == ریکارڈ_TYPE)
	warning_at (ریکارڈ_loc, OPT_Wc___compat,
		    "empty struct has size 0 in C, size 1 in C++");
      ورنہ
	warning_at (ریکارڈ_loc, OPT_Wc___compat,
		    "empty union has size 0 in C, size 1 in C++");
    }

  /* Set the C_TYPE_DEFINED_IN_STRUCT flag for each type defined in
     the current struct.  We do this now at the end of the struct
     because the flag is used to issue visibility warnings, and we
     only want to issue those warnings if the type is referenced
     outside of the struct declaration.  */
  FOR_EACH_VEC_ELT (struct_parse_info->struct_types, ix, x)
    C_TYPE_DEFINED_اندر_STRUCT (x) = 1;

  /* The TYPEDEFS_SEEN field of STRUCT_PARSE_INFO is a list of
     typedefs used when declaring fields in this struct.  If the name
     of any of the fields is also a typedef name then the struct would
     not parse in C++, because the C++ lookup rules say that the
     typedef name would be looked up in the context of the struct, and
     would thus be the field rather than the typedef.  */
  اگر (!struct_parse_info->typedefs_نظر_آیا.is_خالی_خانے ()
      && fieldlist != NULL_درخت)
    {
      /* Use a hash_set<tree> using the name of the typedef.  We can use
	 a hash_set<tree> because identifiers are interned.  */
      hash_سیٹ<درخت> tset;

      FOR_EACH_VEC_ELT (struct_parse_info->typedefs_نظر_آیا, ix, x)
	tset.جوڑو (DECL_NAME (x));

      برائے (x = fieldlist; x != NULL_درخت; x = DECL_CHAIN (x))
	{
	  اگر (DECL_NAME (x) != NULL_درخت
	      && tset.شامل_ہے (DECL_NAME (x)))
	    {
	      warning_at (DECL_ماخذ_LOCATION (x), OPT_Wc___compat,
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
    b->اندر_struct = 0;
}

/* Function to help qsort sort FIELD_DECLs by name order.  */

ساکن صحیح
میدان_decl_cmp (ثابت خالی *x_p, ثابت خالی *y_p)
{
  ثابت درخت *ثابت x = (ثابت درخت *) x_p;
  ثابت درخت *ثابت y = (ثابت درخت *) y_p;

  اگر (DECL_NAME (*x) == DECL_NAME (*y))
    /* A nontype is "greater" than a type.  */
    واپس (درخت_رمز (*y) == TYPE_DECL) - (درخت_رمز (*x) == TYPE_DECL);
  اگر (DECL_NAME (*x) == NULL_درخت)
    واپس -1;
  اگر (DECL_NAME (*y) == NULL_درخت)
    واپس 1;
  اگر (DECL_NAME (*x) < DECL_NAME (*y))
    واپس -1;
  واپس 1;
}

/* If this structure or union completes the type of any previous
   variable declaration, lay it out and output its rtl.  */
ساکن خالی
اختتام_incomplete_vars (درخت incomplete_vars, منطقی toplevel)
{
  برائے (درخت x = incomplete_vars; x; x = درخت_CHAIN (x))
    {
      درخت decl = درخت_قدر (x);
      اگر (درخت_رمز (درخت_TYPE (decl)) == ARRAY_TYPE)
	layout_array_type (درخت_TYPE (decl));
      اگر (درخت_رمز (decl) != TYPE_DECL)
	{
	  relayout_decl (decl);
	  اگر (c_dialect_objc ())
	    objc_check_decl (decl);
	  rest_کا_decl_compilation (decl, toplevel, 0);
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

ساکن منطقی
is_flexible_array_member_p (منطقی is_آخری_میدان,
			    درخت x)
{
  /* If not the last field, return false.  */
  اگر (!is_آخری_میدان)
    واپس جھوٹ;

  /* If not an array field, return false.  */
  اگر (درخت_رمز (درخت_TYPE (x)) != ARRAY_TYPE)
    واپس جھوٹ;

  منطقی is_zero_لمبائی_array = zero_لمبائی_array_type_p (درخت_TYPE (x));
  منطقی is_one_element_array = one_element_array_type_p (درخت_TYPE (x));
  منطقی is_flexible_array = flexible_array_member_type_p (درخت_TYPE (x));

  غیرعلامتی صحیح strict_flex_array_level = c_strict_flex_array_level_کا (x);

  انتخاب (strict_flex_array_level)
    {
      حالت 0:
	/* Default, all trailing arrays are flexible array members.  */
	واپس سچ;
      حالت 1:
	/* Level 1: all "[1]", "[0]", and "[]" are flexible array members.  */
	اگر (is_one_element_array)
	  واپس سچ;
	/* FALLTHROUGH.  */
      حالت 2:
	/* Level 2: all "[0]", and "[]" are flexible array members.  */
	اگر (is_zero_لمبائی_array)
	  واپس سچ;
	/* FALLTHROUGH.  */
      حالت 3:
	/* Level 3: Only "[]" are flexible array members.  */
	اگر (is_flexible_array)
	  واپس سچ;
	توڑو;
      طےشدہ:
	gcc_unreachable ();
    }
  واپس جھوٹ;
}

/* Recompute TYPE_CANONICAL for variants of the type including qualified
   versions of the type and related pointer types after an aggregate type
   has been finalized.
   Will not update array types, pointers to array types, function
   types and other derived types created while the type was still
   incomplete, those will remain TYPE_STRUCTURAL_EQUALITY_P.  */

ساکن خالی
c_update_type_canonical (درخت t)
{
  gcc_checking_assert (TYPE_MAIN_VARIANT (t) == t && !TYPE_QUALS (t));
  برائے (درخت x = t, l = NULL_درخت; x; l = x, x = TYPE_اگلا_VARIANT (x))
    {
      اگر (x != t && TYPE_STRUCTURAL_EQUALITY_P (x))
	{
	  اگر (!TYPE_QUALS (x))
	    TYPE_CANONICAL (x) = TYPE_CANONICAL (t);
	  ورنہ
	    {
	      درخت
		c = c_build_qualified_type (TYPE_CANONICAL (t), TYPE_QUALS (x));
	      اگر (TYPE_STRUCTURAL_EQUALITY_P (c))
		{
		  gcc_checking_assert (TYPE_CANONICAL (t) == t);
		  اگر (c == x)
		    TYPE_CANONICAL (x) = x;
		  ورنہ
		    {
		      /* build_qualified_type for this function unhelpfully
			 moved c from some later spot in TYPE_MAIN_VARIANT (t)
			 chain to right after t (or created it there).  Move
			 it right before x and process c and then x.  */
		      gcc_checking_assert (TYPE_اگلا_VARIANT (t) == c);
		      اگر (l != t)
			{
			  TYPE_اگلا_VARIANT (t) = TYPE_اگلا_VARIANT (c);
			  TYPE_اگلا_VARIANT (l) = c;
			  TYPE_اگلا_VARIANT (c) = x;
			}
		      TYPE_CANONICAL (c) = c;
		      x = c;
		    }
		}
	      ورنہ
		TYPE_CANONICAL (x) = TYPE_CANONICAL (c);
	    }
	}
      ورنہ اگر (x != t)
	جاری;
      برائے (درخت p = TYPE_اشارہ_گر_مقصد (x); p; p = TYPE_اگلا_PTR_مقصد (p))
	{
	  اگر (!TYPE_STRUCTURAL_EQUALITY_P (p))
	    جاری;
	  اگر (TYPE_CANONICAL (x) != x || TYPE_REF_CAN_ALIAS_ALL (p))
	    TYPE_CANONICAL (p)
	      = c_build_اشارہ_گر_type_for_منوال (TYPE_CANONICAL (x), TYPE_منوال (p),
					       جھوٹ);
	  ورنہ
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

ساکن خالی
c_update_variably_modified (درخت t)
{
  برائے (درخت x = t; x; x = TYPE_اگلا_VARIANT (x))
    {
      C_TYPE_VARIABLY_MODIFIED (x) = 1;
      برائے (درخت p = TYPE_اشارہ_گر_مقصد (x); p; p = TYPE_اگلا_PTR_مقصد (p))
	c_update_variably_modified (p);
    }
}


/* Verify the argument of the counted_by attribute of each field of
   the containing structure, OUTMOST_STRUCT_TYPE, including its inner
   anonymous struct/union, Report error and remove the corresponding
   attribute when it's not.  */

ساکن خالی
verify_counted_by_attribute (درخت outmost_struct_type,
			     درخت cur_struct_type)
{
  برائے (درخت میدان_2 = TYPE_FIELDS (cur_struct_type); میدان_2;
       میدان_2 = درخت_CHAIN (میدان_2))
    {
      اگر (flexible_array_member_type_p (درخت_TYPE (میدان_2))
	   || درخت_رمز (درخت_TYPE (میدان_2)) == اشارہ_گر_TYPE)
	{
	  درخت attr_counted_by = lookup_attribute ("counted_by",
						   DECL_اوصاف (میدان_2));

	  اگر (!attr_counted_by)
	    جاری;

	  /* If there is an counted_by attribute attached to the field,
	     verify it.  */

	  درخت fieldname = درخت_قدر (درخت_قدر (attr_counted_by));

	  /* Verify the argument of the attribute is a valid field of the
	     containing structure.  */

	  درخت counted_by_میدان = lookup_میدان (outmost_struct_type,
						fieldname);

	  /* Error when the field is not found in the containing structure
	     and remove the corresponding counted_by attribute from the
	     field_decl.  */
	  اگر (!counted_by_میدان)
	    {
	      error_at (DECL_ماخذ_LOCATION (میدان_2),
		    "argument %qE to the %<counted_by%> attribute"
		    " is not a field declaration in the same structure"
		    " as %qD", fieldname, میدان_2);
	      DECL_اوصاف (میدان_2)
		= remove_attribute ("counted_by", DECL_اوصاف (میدان_2));
	    }
	  ورنہ
	  /* Error when the field is not with an integer type.  */
	    {
	      جب (درخت_CHAIN (counted_by_میدان))
		counted_by_میدان = درخت_CHAIN (counted_by_میدان);
	      درخت real_میدان = درخت_قدر (counted_by_میدان);

	      اگر (!INTEGRAL_TYPE_P (درخت_TYPE (real_میدان)))
		{
		  error_at (DECL_ماخذ_LOCATION (میدان_2),
			"argument %qE to the %<counted_by%> attribute"
			" is not a field declaration with an integer type",
			fieldname);
		  DECL_اوصاف (میدان_2)
		    = remove_attribute ("counted_by",
				    DECL_اوصاف (میدان_2));
		}
	    }
	}
      ورنہ اگر (ریکارڈ_OR_UNION_TYPE_P (درخت_TYPE (میدان_2))
	       && (DECL_NAME (میدان_2) == NULL_درخت))
	verify_counted_by_attribute (outmost_struct_type, درخت_TYPE (میدان_2));
    }
}

/* Caller should make sure the TYPE is a top-level type (i.e. not being
   nested in other structure/uniona). For such type, verify its counted_by
   if it is an anonymous structure/union.  */

خالی
verify_counted_by_for_چوٹی_anonymous_type (درخت type)
{
  اگر (!ریکارڈ_OR_UNION_TYPE_P (type))
    واپس;

  اگر (C_TYPE_FIELDS_HAS_COUNTED_BY (type)
      && c_type_لیبل (type) == NULL_درخت)
    verify_counted_by_attribute (type, type);
}

/* TYPE is a struct or union that we're applying may_alias to after the body is
   parsed.  Fixup any POINTER_TO types.  */

ساکن خالی
c_fixup_may_alias (درخت type)
{
  برائے (درخت t = TYPE_اشارہ_گر_مقصد (type); t; t = TYPE_اگلا_PTR_مقصد (t))
    برائے (درخت v = TYPE_MAIN_VARIANT (t); v; v = TYPE_اگلا_VARIANT (v))
      TYPE_REF_CAN_ALIAS_ALL (v) = سچ;
}

/* Fill in the fields of a RECORD_TYPE or UNION_TYPE node, T.
   LOC is the location of the RECORD_TYPE or UNION_TYPE's definition.
   FIELDLIST is a chain of FIELD_DECL nodes for the fields.
   ATTRIBUTES are attributes to be applied to the structure.

   ENCLOSING_STRUCT_PARSE_INFO is the value of STRUCT_PARSE_INFO when
   the struct was started.  */

درخت
اختتام_struct (location_t loc, درخت t, درخت fieldlist, درخت اوصاف,
	       جماعت c_struct_parse_info *enclosing_struct_parse_info,
	       درخت *اظہاریہ)
{
  درخت x;
  منطقی toplevel = file_scope == current_scope;

  /* If this type was previously laid out as a forward reference,
     make sure we lay it out again.  */

  TYPE_سائز (t) = NULL_درخت;

  decl_اوصاف (&t, اوصاف, (صحیح) ATTR_FLAG_TYPE_اندر_رکھو);

  اگر (pedantic)
    {
      برائے (x = fieldlist; x; x = DECL_CHAIN (x))
	{
	  اگر (DECL_NAME (x) != NULL_درخت)
	    توڑو;
	  اگر (flag_isoc11 && ریکارڈ_OR_UNION_TYPE_P (درخت_TYPE (x)))
	    توڑو;
	}

      اگر (x == NULL_درخت)
	{
	  اگر (درخت_رمز (t) == UNION_TYPE)
	    {
	      اگر (fieldlist)
		pedwarn (loc, OPT_Wpedantic, "union has no named members");
	      ورنہ
		pedwarn (loc, OPT_Wpedantic, "union has no members");
	    }
	  ورنہ
	    {
	      اگر (fieldlist)
		pedwarn (loc, OPT_Wpedantic, "struct has no named members");
	      ورنہ
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

  منطقی saw_named_میدان = جھوٹ;
  برائے (x = fieldlist; x; x = DECL_CHAIN (x))
    {
      /* Whether this field is the last field of the structure or union.
	 for UNION, any field is the last field of it.  */
      منطقی is_آخری_میدان = (DECL_CHAIN (x) == NULL_درخت)
			    || (درخت_رمز (t) == UNION_TYPE);

      اگر (درخت_TYPE (x) == error_mark_گرہ)
	جاری;

      DECL_CONTEXT (x) = t;

      درخت t1 = strip_array_types (درخت_TYPE (x));
      /* If any field is const, the structure type is pseudo-const.  */
      اگر (درخت_READONLY (x))
	C_TYPE_FIELDS_READONLY (t) = 1;
      ورنہ
	{
	  /* A field that is pseudo-const makes the structure likewise.  */
	  اگر (ریکارڈ_OR_UNION_TYPE_P (t1) && C_TYPE_FIELDS_READONLY (t1))
	    C_TYPE_FIELDS_READONLY (t) = 1;
	}

      /* Any field that is volatile means variables of this type must be
	 treated in some ways as volatile.  */
      اگر (درخت_THIS_VOLATILE (x))
	{
	  C_TYPE_FIELDS_VOLATILE (t) = 1;
	  C_TYPE_FIELDS_NON_CONSTEXPR (t) = 1;
	}

      /* Any field that is volatile, restrict-qualified or atomic
	 means the type cannot be used for a constexpr object.  */
      اگر (TYPE_QUALS (t1)
	  & (TYPE_QUAL_VOLATILE | TYPE_QUAL_RESTRICT | TYPE_QUAL_ATOMIC))
	C_TYPE_FIELDS_NON_CONSTEXPR (t) = 1;
      ورنہ اگر (ریکارڈ_OR_UNION_TYPE_P (t1) && C_TYPE_FIELDS_NON_CONSTEXPR (t1))
	    C_TYPE_FIELDS_NON_CONSTEXPR (t) = 1;

      /* Any field of nominal variable size implies structure is too.  */
      اگر (C_DECL_VARIABLE_سائز (x))
	C_TYPE_VARIABLE_سائز (t) = 1;

      /* If any field is variably modified, record this fact. */
      اگر (c_type_variably_modified_p (درخت_TYPE (x)))
	C_TYPE_VARIABLY_MODIFIED (t) = 1;

      اگر (DECL_C_ثنائی_ہندسہ_میدان (x))
	{
	  غیرعلامتی HOST_WIDE_INT چوڑائی = درخت_مقصد_uhwi (DECL_INITIAL (x));
	  DECL_سائز (x) = bitsize_int (چوڑائی);
	  DECL_ثنائی_ہندسہ_میدان (x) = 1;
	}

      اگر (TYPE_PACKED (t)
	  && (DECL_ثنائی_ہندسہ_میدان (x)
	      || TYPE_ALIGN (درخت_TYPE (x)) > بٹ_فی_UNIT))
	DECL_PACKED (x) = 1;

      /* Detect flexible array member in an invalid context.  */
      اگر (flexible_array_member_type_p (درخت_TYPE (x)))
	{
	  اگر (درخت_رمز (t) == UNION_TYPE)
	    pedwarn (DECL_ماخذ_LOCATION (x), OPT_Wpedantic,
		     "flexible array member in union is a GCC extension");
	  ورنہ اگر (!is_آخری_میدان)
	    {
	      error_at (DECL_ماخذ_LOCATION (x),
			"flexible array member not at end of struct");
	      درخت_TYPE (x) = error_mark_گرہ;
	    }
	  ورنہ اگر (!saw_named_میدان)
	    pedwarn (DECL_ماخذ_LOCATION (x), OPT_Wpedantic,
		     "flexible array member in a struct with no named "
		     "members is a GCC extension");
	  اگر (lookup_attribute ("counted_by", DECL_اوصاف (x)))
	    C_TYPE_FIELDS_HAS_COUNTED_BY (t) = 1;
	}

      اگر (درخت_رمز (درخت_TYPE (x)) == اشارہ_گر_TYPE
	  && lookup_attribute ("counted_by", DECL_اوصاف (x)))
	C_TYPE_FIELDS_HAS_COUNTED_BY (t) = 1;

      /* If the field is an anonymous structure that includes a field
	 with counted_by attribute, this structure should also be marked
	 too.  */
      اگر (ریکارڈ_OR_UNION_TYPE_P (درخت_TYPE (x))
	  && C_TYPE_FIELDS_HAS_COUNTED_BY (درخت_TYPE (x))
	  && DECL_NAME (x) == NULL_درخت
	  && c_type_لیبل (درخت_TYPE (x)) == NULL_درخت)
	C_TYPE_FIELDS_HAS_COUNTED_BY (t) = 1;

      اگر (pedantic && درخت_رمز (t) == ریکارڈ_TYPE
	  && flexible_array_type_p (درخت_TYPE (x)))
	pedwarn (DECL_ماخذ_LOCATION (x), OPT_Wpedantic,
		 "invalid use of structure with flexible array member");

      /* Set DECL_NOT_FLEXARRAY flag for FIELD_DECL x.  */
      DECL_NOT_FLEXARRAY (x) = !is_flexible_array_member_p (is_آخری_میدان, x);

      /* Set TYPE_INCLUDES_FLEXARRAY for the context of x, t.
	 when x is an array and is the last field.
	 There is only one last_field for a structure type, but there might
	 be multiple last_fields for a union type, therefore we should ORed
	 the result for multiple last_fields.  */
      اگر (درخت_رمز (درخت_TYPE (x)) == ARRAY_TYPE)
	TYPE_INCLUDES_FLEXARRAY (t)
	  |= is_آخری_میدان && flexible_array_member_type_p (درخت_TYPE (x));
      /* Recursively set TYPE_INCLUDES_FLEXARRAY for the context of x, t
	 when x is an union or record and is the last field.  */
      ورنہ اگر (ریکارڈ_OR_UNION_TYPE_P (درخت_TYPE (x)))
	TYPE_INCLUDES_FLEXARRAY (t)
	  |= is_آخری_میدان && TYPE_INCLUDES_FLEXARRAY (درخت_TYPE (x));

      اگر (warn_flex_array_member_not_at_انتہا
	  && !is_آخری_میدان
	  && ریکارڈ_OR_UNION_TYPE_P (درخت_TYPE (x))
	  && TYPE_INCLUDES_FLEXARRAY (درخت_TYPE (x)))
	warning_at (DECL_ماخذ_LOCATION (x),
		    OPT_Wflex_array_member_not_at_انتہا,
		    "structure containing a flexible array member"
		    " is not at the end of another structure");

      اگر (DECL_NAME (x)
	  || ریکارڈ_OR_UNION_TYPE_P (درخت_TYPE (x)))
	saw_named_میدان = سچ;

      اگر (AGGREGATE_TYPE_P (درخت_TYPE (x))
	  && TYPE_TYPELESS_STORAGE (درخت_TYPE (x)))
	TYPE_TYPELESS_STORAGE (t) = سچ;
    }

  detect_میدان_duplicates (fieldlist);

  /* Now we have the nearly final fieldlist.  Record it,
     then lay out the structure or union (including the fields).  */

  TYPE_FIELDS (t) = fieldlist;

  maybe_apply_pragma_scalar_storage_ترتیب (t);

  layout_type (t);

  اگر (TYPE_سائز_UNIT (t)
      && درخت_رمز (TYPE_سائز_UNIT (t)) == INTEGER_CST
      && !درخت_حد_سے_تجاوز (TYPE_سائز_UNIT (t))
      && !valid_constant_سائز_p (TYPE_سائز_UNIT (t)))
    error ("type %qT is too large", t);

  /* Give bit-fields their proper types and rewrite the type of array fields
     with scalar component if the enclosing type has reverse storage order.  */
  برائے (درخت میدان_2 = fieldlist; میدان_2; میدان_2 = DECL_CHAIN (میدان_2))
    {
      اگر (درخت_رمز (میدان_2) == میدان_DECL
	  && DECL_INITIAL (میدان_2)
	  && درخت_TYPE (میدان_2) != error_mark_گرہ)
	{
	  غیرعلامتی HOST_WIDE_INT چوڑائی
	    = درخت_مقصد_uhwi (DECL_INITIAL (میدان_2));
	  درخت type = درخت_TYPE (میدان_2);
	  اگر (سمتیہ_TYPE_P (type))
	    {
	      error_at (DECL_ماخذ_LOCATION (میدان_2),
			"bit-field %qD has invalid type", میدان_2);
	      type = درخت_TYPE (type);
	      درخت_TYPE (میدان_2) = type;
	    }
	  اگر (چوڑائی != TYPE_PRECISION (type))
	    {
	      اگر (BITINT_TYPE_P (type)
		  && چوڑائی >= ((TYPE_UNSIGNED (type) || flag_isoc2y) ? 1 : 2))
		درخت_TYPE (میدان_2)
		  = build_bitint_type (چوڑائی, TYPE_UNSIGNED (type));
	      ورنہ
		درخت_TYPE (میدان_2)
		  = c_build_bitfield_integer_type (چوڑائی,
						   TYPE_UNSIGNED (type));
	      اگر (درخت attr = c_hardbool_type_attr (type))
		decl_اوصاف (&درخت_TYPE (میدان_2),
				 copy_list (attr),
				 0, NULL_درخت);
	      سیٹ_DECL_منوال (میدان_2, TYPE_منوال (درخت_TYPE (میدان_2)));
	    }
	  DECL_INITIAL (میدان_2) = NULL_درخت;
	}
      ورنہ اگر (TYPE_الٹ_STORAGE_ترتیب (t)
	       && درخت_رمز (میدان_2) == میدان_DECL
	       && درخت_رمز (درخت_TYPE (میدان_2)) == ARRAY_TYPE)
	{
	  درخت ftype = درخت_TYPE (میدان_2);
	  درخت ctype = strip_array_types (ftype);
	  اگر (!ریکارڈ_OR_UNION_TYPE_P (ctype) && TYPE_منوال (ctype) != QImode)
	    {
	      درخت fmain_type = TYPE_MAIN_VARIANT (ftype);
	      درخت *typep = &fmain_type;
	      کرو {
		*typep = build_distinct_type_copy (*typep);
		TYPE_الٹ_STORAGE_ترتیب (*typep) = 1;
		typep = &درخت_TYPE (*typep);
	      } جب (درخت_رمز (*typep) == ARRAY_TYPE);
	      درخت_TYPE (میدان_2)
		= c_build_qualified_type (fmain_type, TYPE_QUALS (ftype));
	    }
	}

      /* Warn on problematic type punning for storage order purposes.  */
      اگر (درخت_رمز (t) == UNION_TYPE
	  && درخت_رمز (میدان_2) == میدان_DECL
	  && AGGREGATE_TYPE_P (درخت_TYPE (میدان_2)))
	{
	  درخت ftype = درخت_TYPE (میدان_2);
	  اگر (درخت_رمز (ftype) == ARRAY_TYPE)
	    ftype = strip_array_types (ftype);
	  اگر (ریکارڈ_OR_UNION_TYPE_P (ftype)
	      && TYPE_الٹ_STORAGE_ترتیب (ftype)
		 != TYPE_الٹ_STORAGE_ترتیب (t))
	    warning_at (DECL_ماخذ_LOCATION (میدان_2),
			OPT_Wscalar_storage_ترتیب,
			"type punning toggles scalar storage order");
	}
    }

  /* Now we have the truly final field list.
     Store it in this type and in the variants.  */

  TYPE_FIELDS (t) = fieldlist;

  /* If there are lots of fields, sort so we can look through them fast.
     We arbitrarily consider 16 or more elts to be "a lot".  */

  {
    صحیح len = 0;

    برائے (x = fieldlist; x; x = DECL_CHAIN (x))
      {
	اگر (len > 15 || DECL_NAME (x) == تہی)
	  توڑو;
	len += 1;
      }

    اگر (len > 15)
      {
	درخت *میدان_array;
	ساخت lang_type *space;
	ساخت sorted_fields_type *space2;

	len += list_لمبائی (x);

	/* Use the same allocation policy here that make_node uses, to
	   ensure that this lives as long as the rest of the struct decl.
	   All decls in an inline function need to be saved.  */

	space = ((ساخت lang_type *)
		 ggc_اندرونی_cleared_alloc (c_dialect_objc ()
					     ? حجم (ساخت lang_type)
					     : offsetof (ساخت lang_type,
							 info)));
	space2 = ((sorted_fields_type *)
		  ggc_اندرونی_alloc (حجم (ساخت sorted_fields_type)
				      + len * حجم (درخت)));

	len = 0;
	space->s = space2;
	میدان_array = &space2->elts[0];
	برائے (x = fieldlist; x; x = DECL_CHAIN (x))
	  {
	    میدان_array[len++] = x;

	    /* If there is anonymous struct or union, break out of the loop.  */
	    اگر (DECL_NAME (x) == تہی)
	      توڑو;
	  }
	/* Found no anonymous struct/union.  Add the TYPE_LANG_SPECIFIC.  */
	اگر (x == تہی)
	  {
	    TYPE_LANG_SPECIFIC (t) = space;
	    TYPE_LANG_SPECIFIC (t)->s->len = len;
	    میدان_array = TYPE_LANG_SPECIFIC (t)->s->elts;
	    qsort (میدان_array, len, حجم (درخت), میدان_decl_cmp);
	  }
      }
  }

  /* If this was supposed to be a transparent union, but we can't
     make it one, warn and turn off the flag.  */
  اگر (درخت_رمز (t) == UNION_TYPE
      && TYPE_TRANSPARENT_AGGR (t)
      && (!TYPE_FIELDS (t) || TYPE_منوال (t) != DECL_منوال (TYPE_FIELDS (t))))
    {
      TYPE_TRANSPARENT_AGGR (t) = 0;
      warning_at (loc, 0, "union cannot be made transparent");
    }

  درخت incomplete_vars = C_TYPE_INCOMPLETE_VARS (TYPE_MAIN_VARIANT (t));
  برائے (x = TYPE_MAIN_VARIANT (t); x; x = TYPE_اگلا_VARIANT (x))
    {
      TYPE_FIELDS (x) = TYPE_FIELDS (t);
      TYPE_LANG_SPECIFIC (x) = TYPE_LANG_SPECIFIC (t);
      TYPE_TRANSPARENT_AGGR (x) = TYPE_TRANSPARENT_AGGR (t);
      TYPE_TYPELESS_STORAGE (x) = TYPE_TYPELESS_STORAGE (t);
      C_TYPE_FIELDS_READONLY (x) = C_TYPE_FIELDS_READONLY (t);
      C_TYPE_FIELDS_VOLATILE (x) = C_TYPE_FIELDS_VOLATILE (t);
      C_TYPE_FIELDS_NON_CONSTEXPR (x) = C_TYPE_FIELDS_NON_CONSTEXPR (t);
      C_TYPE_FIELDS_HAS_COUNTED_BY (x) = C_TYPE_FIELDS_HAS_COUNTED_BY (t);
      C_TYPE_VARIABLE_سائز (x) = C_TYPE_VARIABLE_سائز (t);
      C_TYPE_VARIABLY_MODIFIED (x) = C_TYPE_VARIABLY_MODIFIED (t);
      C_TYPE_INCOMPLETE_VARS (x) = NULL_درخت;
      TYPE_INCLUDES_FLEXARRAY (x) = TYPE_INCLUDES_FLEXARRAY (t);
    }

  /* Check for consistency with previous definition.  */
  اگر (flag_isoc23 && تہی != enclosing_struct_parse_info)
    {
      درخت vistype = پچھلا_لیبل (t);
      اگر (vistype
	  && درخت_رمز (vistype) == درخت_رمز (t)
	  && !C_TYPE_BEING_DEFINED (vistype))
	{
	  TYPE_STUB_DECL (t) = TYPE_STUB_DECL (vistype);
	  اگر (c_type_variably_modified_p (t))
	    {
	      error ("redefinition of struct or union %qT with variably "
		     "modified type", t);
	      اگر (struct_parse_info->refloc != UNKNOWN_LOCATION)
		inform (struct_parse_info->refloc, "originally defined here");
	    }
	  ورنہ اگر (!comptypes_same_p (t, vistype))
	    {
	      error ("redefinition of struct or union %qT", t);
	      اگر (struct_parse_info->refloc != UNKNOWN_LOCATION)
		inform (struct_parse_info->refloc, "originally defined here");
	    }
	}
    }

  C_TYPE_BEING_DEFINED (t) = 0;

  اگر (lookup_attribute ("may_alias", TYPE_اوصاف (t)))
    برائے (x = TYPE_MAIN_VARIANT (t); x; x = TYPE_اگلا_VARIANT (x))
      c_fixup_may_alias (x);

  /* Set type canonical based on equivalence class.  */
  اگر (flag_isoc23 && !C_TYPE_VARIABLE_سائز (t))
    {
      اگر (c_struct_htab == تہی)
	c_struct_htab = hash_جدول<c_struct_hasher>::create_ggc (61);

      hashval_t hash = c_struct_hasher::hash (t);

      gcc_checking_assert (TYPE_STRUCTURAL_EQUALITY_P (t));
      gcc_checking_assert (!TYPE_NAME (t)
			   || درخت_رمز (TYPE_NAME (t)) == IDENTIFIER_گرہ);

      درخت *e = c_struct_htab->ڈھونڈو_خانہ_with_hash (t, hash, داخل_کرو);
      اگر (*e)
	TYPE_CANONICAL (t) = TYPE_CANONICAL (*e);
      ورنہ
	{
	  TYPE_CANONICAL (t) = c_type_canonical (t);
	  *e = t;
	}
      c_update_type_canonical (t);
    }

  /* Update type location to the one of the definition, instead of e.g.
     a forward declaration.  */
  اگر (TYPE_STUB_DECL (t))
    DECL_ماخذ_LOCATION (TYPE_STUB_DECL (t)) = loc;

  /* Finish debugging output for this type.  */
  rest_کا_type_compilation (t, toplevel);

  اختتام_incomplete_vars (incomplete_vars, toplevel);


  اگر (c_type_variably_modified_p (t))
    {
      c_update_variably_modified (t);
      /* Make sure a DECL_EXPR is created for structs with VLA members.
	 Because we do not know the context, we always pass expr
	 to force creation of a BIND_EXPR which is required in some
	 contexts.  */
      جوڑو_decl_اظہاریہ (loc, t, اظہاریہ, جھوٹ);
    }

  اگر (warn_cxx_compat)
    warn_cxx_compat_اختتام_struct (fieldlist, درخت_رمز (t), loc);

  اگر (تہی != enclosing_struct_parse_info)
    {
      حذف struct_parse_info;

      struct_parse_info = enclosing_struct_parse_info;

      /* If this struct is defined inside a struct, add it to
	 struct_types.  */
      اگر (warn_cxx_compat
	  && struct_parse_info != تہی
	  && !اندر_sizeof && !اندر_typeof && !اندر_alignof && !اندر_countof)
	struct_parse_info->struct_types.محفوظ_ڈالو (t);
     }

  /* Only when the enclosing struct/union type is not anonymous, do more
     verification on the fields with counted_by attributes.  */
  اگر (C_TYPE_FIELDS_HAS_COUNTED_BY (t) && c_type_لیبل (t) != NULL_درخت)
    verify_counted_by_attribute (t, t);

  واپس t;
}

ساکن ساخت {
  gt_اشارہ_گر_operator new_قدر;
  خالی *cookie;
} resort_ڈیٹا;

/* This routine compares two fields like field_decl_cmp but using the
pointer operator in resort_data.  */

ساکن صحیح
resort_میدان_decl_cmp (ثابت خالی *x_p, ثابت خالی *y_p)
{
  ثابت درخت *ثابت x = (ثابت درخت *) x_p;
  ثابت درخت *ثابت y = (ثابت درخت *) y_p;

  اگر (DECL_NAME (*x) == DECL_NAME (*y))
    /* A nontype is "greater" than a type.  */
    واپس (درخت_رمز (*y) == TYPE_DECL) - (درخت_رمز (*x) == TYPE_DECL);
  اگر (DECL_NAME (*x) == NULL_درخت)
    واپس -1;
  اگر (DECL_NAME (*y) == NULL_درخت)
    واپس 1;
  {
    درخت d1 = DECL_NAME (*x);
    درخت d2 = DECL_NAME (*y);
    resort_ڈیٹا.new_قدر (&d1, &d1, resort_ڈیٹا.cookie);
    resort_ڈیٹا.new_قدر (&d2, &d2, resort_ڈیٹا.cookie);
    اگر (d1 < d2)
      واپس -1;
  }
  واپس 1;
}

/* Resort DECL_SORTED_FIELDS because pointers have been reordered.  */

خالی
resort_sorted_fields (خالی *obj,
		      خالی * ARG_غیر_مستعمل (orig_obj),
		      gt_اشارہ_گر_operator new_قدر,
		      خالی *cookie)
{
  ساخت sorted_fields_type *sf = (ساخت sorted_fields_type *) obj;
  resort_ڈیٹا.new_قدر = new_قدر;
  resort_ڈیٹا.cookie = cookie;
  qsort (&sf->elts[0], sf->len, حجم (درخت),
	 resort_میدان_decl_cmp);
}

/* Lay out the type T, and its element type, and so on.  */

ساکن خالی
layout_array_type (درخت t)
{
  اگر (درخت_رمز (درخت_TYPE (t)) == ARRAY_TYPE)
    layout_array_type (درخت_TYPE (t));
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

درخت
آغاز_enum (location_t loc, ساخت c_enum_contents *the_enum, درخت name,
	    درخت fixed_underlying_type, منطقی potential_nesting_p)
{
  درخت enumtype = NULL_درخت;
  location_t enumloc = UNKNOWN_LOCATION;

  /* If this is the real definition for a previous forward reference,
     fill in the contents in the same object that used to be the
     forward reference.  */

  اگر (name != NULL_درخت)
    enumtype = lookup_لیبل (ENUMERAL_TYPE, name, سچ, &enumloc);

  اگر (enumtype != NULL_درخت && درخت_رمز (enumtype) == ENUMERAL_TYPE)
    {
      /* If the type is currently being defined or if we have seen an
	 incomplete version which is now complete, this is a nested
	 redefinition.  The later happens if the redefinition occurs
	 inside the enum specifier itself.  */
      اگر (C_TYPE_BEING_DEFINED (enumtype)
	  || (potential_nesting_p && TYPE_اقدار (enumtype) != NULL_درخت))
	error_at (loc, "nested redefinition of %<enum %E%>", name);

      /* For C23 we allow redefinitions.  We set to zero and check for
	 consistency later.  */
      اگر (flag_isoc23 && TYPE_اقدار (enumtype) != NULL_درخت)
	enumtype = NULL_درخت;
    }

  اگر (enumtype == NULL_درخت || درخت_رمز (enumtype) != ENUMERAL_TYPE)
    {
      enumtype = make_گرہ (ENUMERAL_TYPE);
      TYPE_سائز (enumtype) = NULL_درخت;
      سیٹ_TYPE_STRUCTURAL_EQUALITY (enumtype);
      pushtag (loc, name, enumtype);
      اگر (fixed_underlying_type != NULL_درخت)
	{
	  /* For an enum definition with a fixed underlying type, the
	     type is complete during the definition and the
	     enumeration constants have that type.  If there was a
	     tag, the type was completed in c_parser_enum_specifier.
	     If not, it must be completed here.  */
	  ENUM_FIXED_UNDERLYING_TYPE_P (enumtype) = سچ;
	  TYPE_MIN_قدر (enumtype) = TYPE_MIN_قدر (fixed_underlying_type);
	  TYPE_MAX_قدر (enumtype) = TYPE_MAX_قدر (fixed_underlying_type);
	  TYPE_UNSIGNED (enumtype) = TYPE_UNSIGNED (fixed_underlying_type);
	  سیٹ_TYPE_ALIGN (enumtype, TYPE_ALIGN (fixed_underlying_type));
	  TYPE_سائز (enumtype) = NULL_درخت;
	  TYPE_PRECISION (enumtype) = TYPE_PRECISION (fixed_underlying_type);
	  ENUM_UNDERLYING_TYPE (enumtype) = fixed_underlying_type;
	  TYPE_CANONICAL (enumtype) = TYPE_CANONICAL (fixed_underlying_type);
	  c_update_type_canonical (enumtype);
	  layout_type (enumtype);
	}
    }
  /* Update type location to the one of the definition, instead of e.g.
     a forward declaration.  */
  ورنہ اگر (TYPE_STUB_DECL (enumtype))
    {
      enumloc = DECL_ماخذ_LOCATION (TYPE_STUB_DECL (enumtype));
      DECL_ماخذ_LOCATION (TYPE_STUB_DECL (enumtype)) = loc;
    }

  C_TYPE_BEING_DEFINED (enumtype) = 1;

  اگر (TYPE_اقدار (enumtype) != NULL_درخت)
    {
      /* This enum is a named one that has been declared already.  */
      auto_diagnostic_گروہ d;
      error_at (loc, "redeclaration of %<enum %E%>", name);
      اگر (enumloc != UNKNOWN_LOCATION)
	inform (enumloc, "originally defined here");

      /* Completely replace its old definition.
	 The old enumerators remain defined, however.  */
      TYPE_اقدار (enumtype) = NULL_درخت;
    }

  اگر (ENUM_FIXED_UNDERLYING_TYPE_P (enumtype)
      && fixed_underlying_type == NULL_درخت)
    {
      error_at (loc, "%<enum%> declared with but defined without "
		"fixed underlying type");
      ENUM_FIXED_UNDERLYING_TYPE_P (enumtype) = جھوٹ;
    }

  the_enum->enum_اگلا_قدر = integer_zero_گرہ;
  the_enum->enum_type = enumtype;
  the_enum->enum_حد_سے_تجاوز = 0;

  اگر (flag_short_enums && !ENUM_FIXED_UNDERLYING_TYPE_P (enumtype))
    برائے (درخت v = TYPE_MAIN_VARIANT (enumtype); v; v = TYPE_اگلا_VARIANT (v))
      TYPE_PACKED (v) = 1;

  /* FIXME: This will issue a warning for a use of a type defined
     within sizeof in a statement expr.  This is not terribly serious
     as C++ doesn't permit statement exprs within sizeof anyhow.  */
  اگر (warn_cxx_compat
      && (اندر_sizeof || اندر_typeof || اندر_alignof || اندر_countof))
    warning_at (loc, OPT_Wc___compat,
		"defining type in %qs expression is invalid in C++",
		(اندر_sizeof ? "sizeof"
		 : اندر_typeof ? "typeof"
		 : اندر_alignof ? "alignof"
		 : "_Countof"));

  اگر (اندر_underspecified_init)
    error_at (loc, "%qT defined in underspecified object initializer",
	      enumtype);

  واپس enumtype;
}

/* After processing and defining all the values of an enumeration type,
   install their decls in the enumeration type and finish it off.
   ENUMTYPE is the type object, VALUES a list of decl-value pairs,
   and ATTRIBUTES are the specified attributes.
   Returns ENUMTYPE.  */

درخت
اختتام_enum (درخت enumtype, درخت اقدار, درخت اوصاف)
{
  درخت pair, tem;
  درخت minnode = NULL_درخت, maxnode = NULL_درخت;
  صحیح precision;
  signop sign;
  منطقی toplevel = (file_scope == current_scope);
  ساخت lang_type *lt;

  decl_اوصاف (&enumtype, اوصاف, (صحیح) ATTR_FLAG_TYPE_اندر_رکھو);

  /* Calculate the maximum value of any enumerator in this type.  */

  اگر (اقدار == error_mark_گرہ)
    minnode = maxnode = integer_zero_گرہ;
  ورنہ
    {
      minnode = maxnode = درخت_قدر (اقدار);
      برائے (pair = درخت_CHAIN (اقدار); pair; pair = درخت_CHAIN (pair))
	{
	  درخت قدر = درخت_قدر (pair);
	  اگر (درخت_int_cst_lt (maxnode, قدر))
	    maxnode = قدر;
	  اگر (درخت_int_cst_lt (قدر, minnode))
	    minnode = قدر;
	}
    }

  /* Construct the final type of this enumeration.  It is the same
     as one of the integral types - the narrowest one that fits, except
     that normally we only go as narrow as int - and signed iff any of
     the values are negative.  */
  sign = (درخت_int_cst_sgn (minnode) >= 0) ? UNSIGNED : SIGNED;
  precision = MAX (درخت_int_cst_min_precision (minnode, sign),
		   درخت_int_cst_min_precision (maxnode, sign));

  منطقی wider_than_int =
    (درخت_int_cst_lt (minnode, TYPE_MIN_قدر (integer_type_گرہ))
     || درخت_int_cst_lt (TYPE_MAX_قدر (integer_type_گرہ), maxnode));


  اگر (!ENUM_FIXED_UNDERLYING_TYPE_P (enumtype))
    {
      /* If the precision of the type was specified with an attribute and it
	 was too small, give an error.  Otherwise, use it.  */
      اگر (TYPE_PRECISION (enumtype) && lookup_attribute ("mode", اوصاف))
	{
	  اگر (precision > TYPE_PRECISION (enumtype))
	    {
	      TYPE_PRECISION (enumtype) = 0;
	      error ("specified mode too small for enumerated values");
	    }
	  ورنہ
	    precision = TYPE_PRECISION (enumtype);
	}
      ورنہ
	TYPE_PRECISION (enumtype) = 0;

      اگر (TYPE_PACKED (enumtype)
	  || precision > TYPE_PRECISION (integer_type_گرہ)
	  || TYPE_PRECISION (enumtype))
	{
	  tem = c_common_type_for_سائز (precision, sign == UNSIGNED ? 1 : 0);
	  اگر (tem == تہی)
	    {
	      /* This should only occur when both signed and unsigned
		 values of maximum precision occur among the
		 enumerators.  */
	      pedwarn (داخلہ_location, 0,
		       "enumeration values exceed range of largest integer");
	      tem = widest_integer_literal_type_گرہ;
	    }
	  ورنہ اگر (precision > TYPE_PRECISION (intmax_type_گرہ)
		   && !درخت_int_cst_lt (minnode,
					TYPE_MIN_قدر (intmax_type_گرہ))
		   && !درخت_int_cst_lt (TYPE_MAX_قدر (uintmax_type_گرہ),
					maxnode))
	    pedwarn (داخلہ_location, OPT_Wpedantic,
		     "enumeration values exceed range of %qs",
		     sign == UNSIGNED ? "uintmax_t" : "intmax_t");
	}
      ورنہ
	tem = sign == UNSIGNED ? unsigned_type_گرہ : integer_type_گرہ;

      TYPE_MIN_قدر (enumtype) = TYPE_MIN_قدر (tem);
      TYPE_MAX_قدر (enumtype) = TYPE_MAX_قدر (tem);
      TYPE_UNSIGNED (enumtype) = TYPE_UNSIGNED (tem);
      سیٹ_TYPE_ALIGN (enumtype, TYPE_ALIGN (tem));
      TYPE_سائز (enumtype) = NULL_درخت;
      TYPE_PRECISION (enumtype) = TYPE_PRECISION (tem);
      ENUM_UNDERLYING_TYPE (enumtype) =
	c_common_type_for_سائز (TYPE_PRECISION (tem), TYPE_UNSIGNED (tem));

      TYPE_CANONICAL (enumtype) =
	TYPE_CANONICAL (ENUM_UNDERLYING_TYPE (enumtype));
      c_update_type_canonical (enumtype);

      layout_type (enumtype);
    }

  اگر (اقدار != error_mark_گرہ)
    {
      /* Change the type of the enumerators to be the enum type.  We
	 need to do this irrespective of the size of the enum, for
	 proper type checking.  Replace the DECL_INITIALs of the
	 enumerators, and the value slots of the list, with copies
	 that have the enum type; they cannot be modified in place
	 because they may be shared (e.g.  integer_zero_node) Finally,
	 change the purpose slots to point to the names of the decls.  */
      برائے (pair = اقدار; pair; pair = درخت_CHAIN (pair))
	{
	  درخت enu = درخت_PURPOSE (pair);
	  درخت ini = DECL_INITIAL (enu);

	  درخت_TYPE (enu) = enumtype;

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
	  اگر (!ENUM_FIXED_UNDERLYING_TYPE_P (enumtype) && wider_than_int)
	    ini = convert (enumtype, ini);

	  DECL_INITIAL (enu) = ini;
	  درخت_PURPOSE (pair) = DECL_NAME (enu);
	  /* To match the C++ FE, store the CONST_DECL rather than just its
	     value.  */
	  درخت_قدر (pair) = enu;
	}

      TYPE_اقدار (enumtype) = اقدار;
    }

  /* Record the min/max values so that we can warn about bit-field
     enumerations that are too small for the values.  */
  lt = ((ساخت lang_type *)
	ggc_اندرونی_cleared_alloc (c_dialect_objc ()
				    ? حجم (ساخت lang_type)
				    : offsetof (ساخت lang_type, info)));
  lt->enum_min = minnode;
  lt->enum_max = maxnode;
  TYPE_LANG_SPECIFIC (enumtype) = lt;

  /* Fix up all variant types of this enum type.  */
  درخت incomplete_vars = C_TYPE_INCOMPLETE_VARS (TYPE_MAIN_VARIANT (enumtype));
  برائے (tem = TYPE_MAIN_VARIANT (enumtype); tem; tem = TYPE_اگلا_VARIANT (tem))
    {
      C_TYPE_INCOMPLETE_VARS (tem) = NULL_درخت;
      اگر (tem == enumtype)
	جاری;
      TYPE_اقدار (tem) = TYPE_اقدار (enumtype);
      TYPE_MIN_قدر (tem) = TYPE_MIN_قدر (enumtype);
      TYPE_MAX_قدر (tem) = TYPE_MAX_قدر (enumtype);
      TYPE_سائز (tem) = TYPE_سائز (enumtype);
      TYPE_سائز_UNIT (tem) = TYPE_سائز_UNIT (enumtype);
      سیٹ_TYPE_منوال (tem, TYPE_منوال (enumtype));
      TYPE_PRECISION (tem) = TYPE_PRECISION (enumtype);
      سیٹ_TYPE_ALIGN (tem, TYPE_ALIGN (enumtype));
      TYPE_USER_ALIGN (tem) = TYPE_USER_ALIGN (enumtype);
      TYPE_UNSIGNED (tem) = TYPE_UNSIGNED (enumtype);
      TYPE_LANG_SPECIFIC (tem) = TYPE_LANG_SPECIFIC (enumtype);
      ENUM_UNDERLYING_TYPE (tem) = ENUM_UNDERLYING_TYPE (enumtype);
      TYPE_PACKED (tem) = TYPE_PACKED (enumtype);
    }

  /* Finish debugging output for this type.  */
  rest_کا_type_compilation (enumtype, toplevel);

  اختتام_incomplete_vars (incomplete_vars, toplevel);

  /* If this enum is defined inside a struct, add it to
     struct_types.  */
  اگر (warn_cxx_compat
      && struct_parse_info != تہی
      && !اندر_sizeof && !اندر_typeof && !اندر_alignof && !اندر_countof)
    struct_parse_info->struct_types.محفوظ_ڈالو (enumtype);

  /* Check for consistency with previous definition */
  اگر (flag_isoc23)
    {
      درخت vistype = پچھلا_لیبل (enumtype);
      اگر (vistype
	  && درخت_رمز (vistype) == درخت_رمز (enumtype)
	  && !C_TYPE_BEING_DEFINED (vistype))
	{
	  TYPE_STUB_DECL (enumtype) = TYPE_STUB_DECL (vistype);
	  اگر (!comptypes_same_p (enumtype, vistype))
	    error("conflicting redefinition of enum %qT", enumtype);
	}
    }

  C_TYPE_BEING_DEFINED (enumtype) = 0;

  واپس enumtype;
}

/* Build and install a CONST_DECL for one value of the
   current enumeration type (one that was begun with start_enum).
   DECL_LOC is the location of the enumerator.
   LOC is the location of the '=' operator if any, DECL_LOC otherwise.
   Return a tree-list containing the CONST_DECL and its value.
   Assignment of sequential values by default is handled here.  */

درخت
build_enumerator (location_t decl_loc, location_t loc,
		  ساخت c_enum_contents *the_enum, درخت name, درخت قدر)
{
  درخت decl;
  درخت old_decl;

  /* Validate and default VALUE.  */

  اگر (قدر != NULL_درخت)
    {
      /* Don't issue more errors for error_mark_node (i.e. an
	 undeclared identifier) - just ignore the value expression.  */
      اگر (قدر == error_mark_گرہ)
	قدر = NULL_درخت;
      ورنہ اگر (!INTEGRAL_TYPE_P (درخت_TYPE (قدر)))
	{
	  error_at (loc, "enumerator value for %qE is not an integer constant",
		    name);
	  قدر = NULL_درخت;
	}
      ورنہ
	{
	  اگر (درخت_رمز (قدر) != INTEGER_CST)
	    {
	      قدر = c_fully_fold (قدر, جھوٹ, تہی);
	      اگر (درخت_رمز (قدر) == INTEGER_CST)
		pedwarn (loc, OPT_Wpedantic,
			 "enumerator value for %qE is not an integer "
			 "constant expression", name);
	    }
	  اگر (درخت_رمز (قدر) != INTEGER_CST)
	    {
	      error ("enumerator value for %qE is not an integer constant",
		     name);
	      قدر = NULL_درخت;
	    }
	  ورنہ
	    {
	      قدر = default_conversion (قدر);
	      constant_عبارت_warning (قدر);
	    }
	}
    }

  /* Default based on previous value.  */
  /* It should no longer be possible to have NON_LVALUE_EXPR
     in the default.  */
  اگر (قدر == NULL_درخت)
    {
      قدر = the_enum->enum_اگلا_قدر;
      اگر (the_enum->enum_حد_سے_تجاوز)
	error_at (loc, "overflow in enumeration values");
    }
  اگر (ENUM_FIXED_UNDERLYING_TYPE_P (the_enum->enum_type))
    {
      /* Enumeration constants must fit in the fixed underlying type.  */
      اگر (!int_سماتا_type_p (قدر, ENUM_UNDERLYING_TYPE (the_enum->enum_type)))
	error_at (loc,
		  "enumerator value outside the range of underlying type");
      /* Enumeration constants for an enum with fixed underlying type
	 have the enum type, both inside and outside the
	 definition.  */
      قدر = convert (the_enum->enum_type, قدر);
    }
  ورنہ اگر (flag_isoc23
	   && (old_decl = lookup_name_اندر_scope (name, current_scope))
	   && old_decl != error_mark_گرہ
	   && درخت_TYPE (old_decl)
	   && درخت_TYPE (درخت_TYPE (old_decl))
	   && درخت_رمز (old_decl) == CONST_DECL)
    {
      /* Enumeration constants in a redeclaration have the previous type.  */
      درخت پچھلا_type = درخت_TYPE (DECL_INITIAL (old_decl));
      اگر (!int_سماتا_type_p (قدر, پچھلا_type))
	{
	  error_at (loc, "value of redeclared enumerator outside the range "
			 "of %qT", پچھلا_type);
	  locate_old_decl (old_decl);
	}
      قدر = convert (پچھلا_type, قدر);
    }
  ورنہ
    {
      /* Even though the underlying type of an enum is unspecified, the
	 type of enumeration constants is explicitly defined as int
	 (6.4.4.3/2 in the C99 Standard).  C23 allows any integer type, and
	 GCC allows such types for older standards as an extension.  */
      منطقی warned_range = جھوٹ;
      اگر (!int_سماتا_type_p (قدر,
			    (TYPE_UNSIGNED (درخت_TYPE (قدر))
			     ? uintmax_type_گرہ
			     : intmax_type_گرہ)))
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
				TYPE_UNSIGNED (درخت_TYPE (قدر))
				? "uintmax_t"
				: "intmax_t");
      اگر (!warned_range && !int_سماتا_type_p (قدر, integer_type_گرہ))
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
      اگر (int_سماتا_type_p (قدر, integer_type_گرہ))
	قدر = convert (integer_type_گرہ, قدر);
    }

  /* Set basis for default for next value.  */
  اگر (ENUM_FIXED_UNDERLYING_TYPE_P (the_enum->enum_type))
    {
      درخت underlying_type = ENUM_UNDERLYING_TYPE (the_enum->enum_type);
      اگر (درخت_رمز (underlying_type) == BOOLEAN_TYPE)
	/* A value of 2 following a value of 1 overflows bool, but we
	   cannot carry out addition directly on bool without
	   promotion, and converting the result of arithmetic in a
	   wider type back to bool would not produce the right result
	   for this overflow check.  */
	the_enum->enum_اگلا_قدر = invert_truthvalue_loc (loc, قدر);
      ورنہ
	the_enum->enum_اگلا_قدر
	  = build_ثنائی_op (اظہاریہ_LOC_OR_LOC (قدر, داخلہ_location),
			     PLUS_اظہاریہ, convert (underlying_type, قدر),
			     convert (underlying_type, integer_one_گرہ),
			     جھوٹ);
    }
  ورنہ
    {
      /* In a redeclaration the type can already be the enumeral type.  */
      اگر (درخت_رمز (درخت_TYPE (قدر)) == ENUMERAL_TYPE)
	قدر = convert (ENUM_UNDERLYING_TYPE (درخت_TYPE (قدر)), قدر);
      the_enum->enum_اگلا_قدر
	= build_ثنائی_op (اظہاریہ_LOC_OR_LOC (قدر, داخلہ_location),
			   PLUS_اظہاریہ, قدر, integer_one_گرہ, جھوٹ);
    }
  the_enum->enum_حد_سے_تجاوز = درخت_int_cst_lt (the_enum->enum_اگلا_قدر, قدر);
  اگر (the_enum->enum_حد_سے_تجاوز
      && !ENUM_FIXED_UNDERLYING_TYPE_P (the_enum->enum_type))
    {
      /* Choose a wider type with the same signedness if
	 available.  */
      صحیح prec = TYPE_PRECISION (درخت_TYPE (قدر)) + 1;
      منطقی unsignedp = TYPE_UNSIGNED (درخت_TYPE (قدر));
      درخت new_type = (unsignedp
		       ? long_unsigned_type_گرہ
		       : long_integer_type_گرہ);
      اگر (prec > TYPE_PRECISION (new_type))
	new_type = (unsignedp
		    ? long_long_unsigned_type_گرہ
		    : long_long_integer_type_گرہ);
      اگر (prec > TYPE_PRECISION (new_type))
	new_type = (unsignedp
		    ? widest_unsigned_literal_type_گرہ
		    : widest_integer_literal_type_گرہ);
      اگر (prec <= TYPE_PRECISION (new_type))
	{
	  the_enum->enum_حد_سے_تجاوز = جھوٹ;
	  the_enum->enum_اگلا_قدر
	    = build_ثنائی_op (اظہاریہ_LOC_OR_LOC (قدر, داخلہ_location),
			       PLUS_اظہاریہ, convert (new_type, قدر),
			       integer_one_گرہ, جھوٹ);
	  gcc_assert (!درخت_int_cst_lt (the_enum->enum_اگلا_قدر, قدر));
	}
    }

  /* Now create a declaration for the enum value name.  */

  decl = build_decl (decl_loc, CONST_DECL, name, درخت_TYPE (قدر));
  DECL_INITIAL (decl) = قدر;
  DECL_CONTEXT (decl) = the_enum->enum_type;
  pushdecl (decl);

  واپس درخت_cons (decl, قدر, NULL_درخت);
}

/* Implement LANG_HOOKS_SIMULATE_ENUM_DECL.  */

درخت
c_simulate_enum_decl (location_t loc, ثابت حرف *name,
		      vec<string_int_pair> *اقدار_ptr)
{
  location_t saved_loc = داخلہ_location;
  داخلہ_location = loc;

  ساخت c_enum_contents the_enum;
  درخت enumtype = آغاز_enum (loc, &the_enum, get_identifier (name),
			      NULL_درخت, جھوٹ);

  درخت قدر_chain = NULL_درخت;
  string_int_pair *قدر;
  vec<string_int_pair> اقدار = *اقدار_ptr;
  غیرعلامتی صحیح i;
  FOR_EACH_VEC_ELT (اقدار, i, قدر)
    {
      درخت decl = build_enumerator (loc, loc, &the_enum,
				    get_identifier (قدر->پہلا),
				    build_int_cst (integer_type_گرہ,
						   قدر->دوسرا));
      درخت_CHAIN (decl) = قدر_chain;
      قدر_chain = decl;
    }

  اختتام_enum (enumtype, nreverse (قدر_chain), NULL_درخت);

  داخلہ_location = saved_loc;
  واپس enumtype;
}

/* Implement LANG_HOOKS_SIMULATE_RECORD_DECL.  */

درخت
c_simulate_ریکارڈ_decl (location_t loc, ثابت حرف *name,
			array_قاش<ثابت درخت> fields)
{
  location_t saved_loc = داخلہ_location;
  داخلہ_location = loc;

  جماعت c_struct_parse_info *struct_info;
  درخت ident = get_identifier (name);
  درخت type = آغاز_struct (loc, ریکارڈ_TYPE, ident, &struct_info);

  برائے (غیرعلامتی صحیح i = 0; i < fields.سائز (); ++i)
    {
      DECL_میدان_CONTEXT (fields[i]) = type;
      اگر (i > 0)
	DECL_CHAIN (fields[i - 1]) = fields[i];
    }

  اختتام_struct (loc, type, fields[0], NULL_درخت, struct_info);

  درخت decl = build_decl (loc, TYPE_DECL, ident, type);
  سیٹ_underlying_type (decl);
  lang_hooks.decls.pushdecl (decl);

  داخلہ_location = saved_loc;
  واپس type;
}

/* Create the FUNCTION_DECL for a function definition.
   DECLSPECS, DECLARATOR and ATTRIBUTES are the parts of
   the declaration; they describe the function's name and the type it returns,
   but twisted together in a fashion that parallels the syntax of C.

   This function creates a binding context for the function body
   as well as setting up the FUNCTION_DECL in current_function_decl.

   Returns true on success.  If the DECLARATOR is not suitable for a function
   (it defines a datum instead), we return false to report a parse error.  */

منطقی
آغاز_function (ساخت c_declspecs *declspecs, ساخت c_declarator *declarator,
		درخت اوصاف)
{
  درخت decl1, old_decl;
  درخت restype, resdecl;
  location_t loc;
  location_t نتیجہ_loc;
  درخت اظہاریہ = تہی;

  current_function_returns_قدر = 0;  /* Assume, until we see it does.  */
  current_function_returns_null = 0;
  current_function_returns_abnormally = 0;
  warn_about_return_type = 0;
  c_switch_ڈھیر = تہی;

  /* Indicate no valid break/continue context.  */
  اندر_statement = 0;

  decl1 = grokdeclarator (declarator, declspecs, FUNCDEF, سچ, تہی,
			  &اوصاف, &اظہاریہ, تہی, DEPRECATED_معمول);
  invoke_plugin_callbacks (PLUGIN_آغاز_PARSE_FUNCTION, decl1);

  /* If the declarator is not suitable for a function definition,
     cause a syntax error.  */
  اگر (decl1 == NULL_درخت
      || درخت_رمز (decl1) != FUNCTION_DECL)
    واپس جھوٹ;

  /* Nested functions may have variably modified (return) type.
     Make sure the size expression is evaluated at this point.  */
  اگر (اظہاریہ && !current_scope->parm_flag)
    جوڑو_stmt (fold_convert (void_type_گرہ, اظہاریہ));

  loc = DECL_ماخذ_LOCATION (decl1);

  /* A nested function is not global.  */
  اگر (current_function_decl != NULL_درخت)
    درخت_عوامی (decl1) = 0;

  c_decl_اوصاف (&decl1, اوصاف, 0);

  اگر (DECL_DECLARED_INLINE_P (decl1)
      && DECL_UNINLINABLE (decl1)
      && lookup_attribute ("noinline", DECL_اوصاف (decl1)))
    {
      auto_urlify_اوصاف sentinel;
      warning_at (loc, OPT_Wattributes,
		  "inline function %qD given attribute %qs",
		  decl1, "noinline");
    }

  /* Handle gnu_inline attribute.  */
  اگر (declspecs->inline_p
      && !flag_gnu89_inline
      && درخت_رمز (decl1) == FUNCTION_DECL
      && (lookup_attribute ("gnu_inline", DECL_اوصاف (decl1))
	  || current_function_decl))
    {
      اگر (declspecs->storage_class != csc_static)
	DECL_EXTERNAL (decl1) = !DECL_EXTERNAL (decl1);
    }

  announce_function (decl1);

  اگر (!COMPLETE_OR_VOID_TYPE_P (درخت_TYPE (درخت_TYPE (decl1))))
    {
      error_at (loc, "return type is an incomplete type");
      /* Make it return void instead.  */
      درخت_TYPE (decl1)
	= c_build_function_type (void_type_گرہ,
				 TYPE_ARG_TYPES (درخت_TYPE (decl1)),
				 TYPE_NO_NAMED_دلائل_STDARG_P (درخت_TYPE (decl1)));
    }

  اگر (warn_about_return_type)
    permerror_opt (loc, flag_isoc99 ? OPT_Wimplicit_int
		   : (warn_return_type > 0 ? OPT_Wreturn_type
		      : OPT_Wimplicit_int),
		   "return type defaults to %<int%>");

  /* Make the init_value nonzero so pushdecl knows this is not tentative.
     error_mark_node is replaced below (in pop_scope) with the BLOCK.  */
  DECL_INITIAL (decl1) = error_mark_گرہ;

  /* If this definition isn't a prototype and we had a prototype declaration
     before, copy the arg type info from that prototype.  */
  old_decl = lookup_name_اندر_scope (DECL_NAME (decl1), current_scope);
  اگر (old_decl && درخت_رمز (old_decl) != FUNCTION_DECL)
    old_decl = NULL_درخت;

  current_function_prototype_locus = UNKNOWN_LOCATION;
  current_function_prototype_built_اندر = جھوٹ;
  current_function_prototype_arg_types = NULL_درخت;
  درخت newtype = درخت_TYPE (decl1);
  درخت oldtype = old_decl ? درخت_TYPE (old_decl) : newtype;
  اگر (!prototype_p (newtype))
    {
      درخت oldrt = درخت_TYPE (oldtype);
      درخت newrt = درخت_TYPE (newtype);
      اگر (old_decl != NULL_درخت
	  && درخت_رمز (oldtype) == FUNCTION_TYPE
	  && comptypes (oldrt, newrt)
	  && !TYPE_NO_NAMED_دلائل_STDARG_P (oldtype))
	{
	  اگر (stdarg_p (oldtype))
	    {
	      auto_diagnostic_گروہ d;
	      warning_at (loc, 0, "%q+D defined as variadic function "
			  "without prototype", decl1);
	      locate_old_decl (old_decl);
	    }
	  درخت_TYPE (decl1) = مرکب_type (oldtype, newtype);
	  current_function_prototype_locus = DECL_ماخذ_LOCATION (old_decl);
	  current_function_prototype_built_اندر
	    = C_DECL_BUILTIN_PROTOTYPE (old_decl);
	  current_function_prototype_arg_types
	    = TYPE_ARG_TYPES (newtype);
	}
      اگر (درخت_عوامی (decl1))
	{
	  /* If there is an external prototype declaration of this
	     function, record its location but do not copy information
	     to this decl.  This may be an invisible declaration
	     (built-in or in a scope which has finished) or simply
	     have more refined argument types than any declaration
	     found above.  */
	  ساخت c_binding *b;
	  برائے (b = I_علامت_BINDING (DECL_NAME (decl1)); b; b = b->shadowed)
	    اگر (B_اندر_SCOPE (b, external_scope))
	      توڑو;
	  اگر (b)
	    {
	      درخت ext_decl, ext_type;
	      ext_decl = b->decl;
	      ext_type = b->u.type ? b->u.type : درخت_TYPE (ext_decl);
	      اگر (درخت_رمز (ext_type) == FUNCTION_TYPE
		  && comptypes (درخت_TYPE (درخت_TYPE (decl1)),
				درخت_TYPE (ext_type)))
		{
		  current_function_prototype_locus
		    = DECL_ماخذ_LOCATION (ext_decl);
		  current_function_prototype_built_اندر
		    = C_DECL_BUILTIN_PROTOTYPE (ext_decl);
		  current_function_prototype_arg_types
		    = TYPE_ARG_TYPES (ext_type);
		}
	    }
	}
    }

  /* Optionally warn about C23 compatibility.  */
  اگر (warn_deprecated_non_prototype
      && old_decl != NULL_درخت
      && درخت_رمز (oldtype) == FUNCTION_TYPE
      && !TYPE_ARG_TYPES (oldtype)
      && !TYPE_NO_NAMED_دلائل_STDARG_P (oldtype)
      && (TYPE_ARG_TYPES (newtype)
	  && درخت_قدر (TYPE_ARG_TYPES (newtype)) != void_type_گرہ))
    {
      منطقی warned = warning_at (loc, OPT_Wdeprecated_non_prototype,
				"ISO C23 does not allow defining"
				" parameters for function %qE declared"
				" without parameters",
				decl1);
      اگر (warned)
	inform (DECL_ماخذ_LOCATION (old_decl), "declared here");
    }

  /* Optionally warn of old-fashioned def with no previous prototype.  */
  اگر (warn_strict_prototypes
      && old_decl != error_mark_گرہ
      && !prototype_p (درخت_TYPE (decl1))
      && C_DECL_ISNT_PROTOTYPE (old_decl))
    warning_at (loc, OPT_Wstrict_prototypes,
		"function declaration isn%'t a prototype");
  /* Optionally warn of any global def with no previous prototype.  */
  ورنہ اگر (warn_missing_prototypes
	   && old_decl != error_mark_گرہ
	   && درخت_عوامی (decl1)
	   && !MAIN_NAME_P (DECL_NAME (decl1))
	   && C_DECL_ISNT_PROTOTYPE (old_decl)
	   && !DECL_DECLARED_INLINE_P (decl1))
    warning_at (loc, OPT_Wmissing_prototypes,
		"no previous prototype for %qD", decl1);
  /* Optionally warn of any def with no previous prototype
     if the function has already been used.  */
  ورنہ اگر (warn_missing_prototypes
	   && old_decl != NULL_درخت
	   && old_decl != error_mark_گرہ
	   && درخت_مستعمل (old_decl)
	   && !prototype_p (درخت_TYPE (old_decl)))
    warning_at (loc, OPT_Wmissing_prototypes,
		"%qD was used with no prototype before its definition", decl1);
  /* Optionally warn of any global def with no previous declaration.  */
  ورنہ اگر (warn_missing_declarations
	   && درخت_عوامی (decl1)
	   && old_decl == NULL_درخت
	   && !MAIN_NAME_P (DECL_NAME (decl1))
	   && !DECL_DECLARED_INLINE_P (decl1))
    warning_at (loc, OPT_Wmissing_declarations,
		"no previous declaration for %qD",
		decl1);
  /* Optionally warn of any def with no previous declaration
     if the function has already been used.  */
  ورنہ اگر (warn_missing_declarations
	   && old_decl != NULL_درخت
	   && old_decl != error_mark_گرہ
	   && درخت_مستعمل (old_decl)
	   && C_DECL_IMPLICIT (old_decl))
    warning_at (loc, OPT_Wmissing_declarations,
		"%qD was used with no declaration before its definition", decl1);

  /* This function exists in static storage.
     (This does not mean `static' in the C sense!)  */
  درخت_STATIC (decl1) = 1;

  /* This is the earliest point at which we might know the assembler
     name of the function.  Thus, if it's set before this, die horribly.  */
  gcc_assert (!DECL_ASSEMBLER_NAME_سیٹ_P (decl1));

  /* If #pragma weak was used, mark the decl weak now.  */
  اگر (current_scope == file_scope)
    maybe_apply_pragma_weak (decl1);

  /* Warn for unlikely, improbable, or stupid declarations of `main'.  */
  اگر (warn_main && MAIN_NAME_P (DECL_NAME (decl1)))
    {
      اگر (TYPE_MAIN_VARIANT (درخت_TYPE (درخت_TYPE (decl1)))
	  != integer_type_گرہ)
	pedwarn (loc, OPT_Wmain, "return type of %qD is not %<int%>", decl1);
      ورنہ اگر (TYPE_ATOMIC (درخت_TYPE (درخت_TYPE (decl1))))
	pedwarn (loc, OPT_Wmain, "%<_Atomic%>-qualified return type of %qD",
		 decl1);

      check_main_parameter_types (decl1);

      اگر (!درخت_عوامی (decl1))
	pedwarn (loc, OPT_Wmain,
		 "%qD is normally a non-static function", decl1);
    }

  درخت parms = current_function_arg_info->parms;
  اگر (old_decl)
    {
      location_t origloc = DECL_ماخذ_LOCATION (old_decl);
      warn_parms_array_mismatch (origloc, old_decl, parms);
    }

  /* To enable versions to be created across TU's we mark and mangle all
     non-default versioned functions.  */
  اگر (درخت_رمز (decl1) == FUNCTION_DECL
      && !ہدف_HAS_FMV_ہدف_ATTRIBUTE
      && get_ہدف_نسخہ (decl1).is_valid ())
    {
      maybe_mark_function_versioned (decl1);
      اگر (current_scope != file_scope)
	error ("versioned definitions are only allowed at file scope");
    }

  /* Record the decl so that the function name is defined.
     If we already have a decl for this name, and it is a FUNCTION_DECL,
     use the old decl.  */

  current_function_decl = pushdecl (decl1);

  اگر (درخت access = build_attr_access_from_parms (parms, جھوٹ))
    decl_اوصاف (&current_function_decl, access, ATTR_FLAG_اندرونی,
		     old_decl);

  ڈالو_scope ();
  declare_parm_level ();

  /* Set the result decl source location to the location of the typespec.  */
  نتیجہ_loc = (declspecs->locations[cdw_typespec] == UNKNOWN_LOCATION
		? loc : declspecs->locations[cdw_typespec]);
  restype = درخت_TYPE (درخت_TYPE (current_function_decl));
  resdecl = build_decl (نتیجہ_loc, نتیجہ_DECL, NULL_درخت, restype);
  DECL_ARTIFICIAL (resdecl) = 1;
  DECL_IGNORED_P (resdecl) = 1;
  DECL_نتیجہ (current_function_decl) = resdecl;

  آغاز_fname_decls ();

  واپس سچ;
}

/* Subroutine of store_parm_decls which handles new-style function
   definitions (prototype format). The parms already have decls, so we
   need only record them as in effect and complain if any redundant
   old-style parm decls were written.  */
ساکن خالی
store_parm_decls_newstyle (درخت fndecl, ثابت ساخت c_arg_info *arg_info)
{
  درخت decl;
  c_arg_لیبل *لیبل;
  غیرعلامتی ix;

  اگر (current_scope->bindings)
    {
      error_at (DECL_ماخذ_LOCATION (fndecl),
		"old-style parameter declarations in prototyped "
		"function definition");

      /* Get rid of the old-style declarations.  */
      نکالو_scope ();
      ڈالو_scope ();
    }
  /* Don't issue this warning for nested functions, and don't issue this
     warning if we got here because ARG_INFO_TYPES was error_mark_node
     (this happens when a function definition has just an ellipsis in
     its parameter list).  */
  ورنہ اگر (!اندر_system_سرخی_at (داخلہ_location)
	   && !current_function_scope
	   && arg_info->types != error_mark_گرہ
	   && !arg_info->c23_خالی_خانے_parens)
    warning_at (DECL_ماخذ_LOCATION (fndecl), OPT_Wtraditional,
		"traditional C rejects ISO C style function definitions");

  /* Now make all the parameter declarations visible in the function body.
     We can bypass most of the grunt work of pushdecl.  */
  برائے (decl = arg_info->parms; decl; decl = DECL_CHAIN (decl))
    {
      DECL_CONTEXT (decl) = current_function_decl;
      اگر (DECL_NAME (decl))
	{
	  bind (DECL_NAME (decl), decl, current_scope,
		/*invisible=*/جھوٹ, /*nested=*/جھوٹ,
		UNKNOWN_LOCATION);
	  اگر (!درخت_مستعمل (decl))
	    warn_if_shadowing (decl);
	}
      ورنہ
	pedwarn_c11 (DECL_ماخذ_LOCATION (decl), OPT_Wmissing_parameter_name,
		     "ISO C does not support omitting parameter names in "
		     "function definitions before C23");
    }

  /* Record the parameter list in the function declaration.  */
  DECL_ARGUMENTS (fndecl) = arg_info->parms;

  /* Now make all the ancillary declarations visible, likewise.  */
  برائے (decl = arg_info->others; decl; decl = DECL_CHAIN (decl))
    {
      DECL_CONTEXT (decl) = current_function_decl;
      اگر (DECL_NAME (decl))
	bind (DECL_NAME (decl), decl, current_scope,
	      /*invisible=*/جھوٹ,
	      /*nested=*/(درخت_رمز (decl) == FUNCTION_DECL),
	      UNKNOWN_LOCATION);
    }

  /* And all the tag declarations.  */
  FOR_EACH_VEC_محفوظ_ELT_الٹ (arg_info->لیبل_فہرست, ix, لیبل)
    اگر (لیبل->id)
      bind (لیبل->id, لیبل->type, current_scope,
	    /*invisible=*/جھوٹ, /*nested=*/جھوٹ, UNKNOWN_LOCATION);
}

/* Subroutine of store_parm_decls which handles old-style function
   definitions (separate parameter list and declarations).  */

ساکن خالی
store_parm_decls_oldstyle (درخت fndecl, ثابت ساخت c_arg_info *arg_info)
{
  ساخت c_binding *b;
  درخت parm, decl, آخری;
  درخت parmids = arg_info->parms;
  hash_سیٹ<درخت> نظر_آیا_دلائل;

  اگر (!اندر_system_سرخی_at (داخلہ_location))
    {
      اگر (flag_isoc23)
	pedwarn (DECL_ماخذ_LOCATION (fndecl),
		 OPT_Wold_style_definition, "old-style function definition");
      ورنہ
	warning_at (DECL_ماخذ_LOCATION (fndecl),
		    OPT_Wold_style_definition,
		    "old-style function definition");
    }

  اگر (current_scope->had_vla_unspec)
    error ("%<[*]%> not allowed in other than function prototype scope");

  /* Match each formal parameter name with its declaration.  Save each
     decl in the appropriate TREE_PURPOSE slot of the parmids chain.  */
  برائے (parm = parmids; parm; parm = درخت_CHAIN (parm))
    {
      اگر (درخت_قدر (parm) == NULL_درخت)
	{
	  error_at (DECL_ماخذ_LOCATION (fndecl),
		    "parameter name missing from parameter list");
	  درخت_PURPOSE (parm) = NULL_درخت;
	  جاری;
	}

      b = I_علامت_BINDING (درخت_قدر (parm));
      اگر (b && B_اندر_CURRENT_SCOPE (b))
	{
	  decl = b->decl;
	  /* Skip erroneous parameters.  */
	  اگر (decl == error_mark_گرہ)
	    جاری;
	  /* If we got something other than a PARM_DECL it is an error.  */
	  اگر (درخت_رمز (decl) != PARM_DECL)
	    {
	      error_at (DECL_ماخذ_LOCATION (decl),
			"%qD declared as a non-parameter", decl);
	      جاری;
	    }
	  /* If the declaration is already marked, we have a duplicate
	     name.  Complain and ignore the duplicate.  */
	  ورنہ اگر (نظر_آیا_دلائل.شامل_ہے (decl))
	    {
	      error_at (DECL_ماخذ_LOCATION (decl),
			"multiple parameters named %qD", decl);
	      درخت_PURPOSE (parm) = NULL_درخت;
	      جاری;
	    }
	  /* If the declaration says "void", complain and turn it into
	     an int.  */
	  ورنہ اگر (VOID_TYPE_P (درخت_TYPE (decl)))
	    {
	      error_at (DECL_ماخذ_LOCATION (decl),
			"parameter %qD declared with void type", decl);
	      درخت_TYPE (decl) = integer_type_گرہ;
	      DECL_ARG_TYPE (decl) = integer_type_گرہ;
	      layout_decl (decl, 0);
	    }
	  warn_if_shadowing (decl);
	}
      /* If no declaration found, default to int.  */
      ورنہ
	{
	  /* FIXME diagnostics: This should be the location of the argument,
	     not the FNDECL.  E.g., for an old-style declaration

	       int f10(v) { blah; }

	     We should use the location of the V, not the F10.
	     Unfortunately, the V is an IDENTIFIER_NODE which has no
	     location.  In the future we need locations for c_arg_info
	     entries.

	     See gcc.dg/Wshadow-3.c for an example of this problem. */
	  decl = build_decl (DECL_ماخذ_LOCATION (fndecl),
			     PARM_DECL, درخت_قدر (parm), integer_type_گرہ);
	  DECL_ARG_TYPE (decl) = درخت_TYPE (decl);
	  pushdecl (decl);
	  warn_if_shadowing (decl);

	  اگر (flag_isoc99)
	    permerror_opt (DECL_ماخذ_LOCATION (decl),
			   OPT_Wimplicit_int, "type of %qD defaults to %<int%>",
			   decl);
	  ورنہ
	    warning_at (DECL_ماخذ_LOCATION (decl),
			OPT_Wmissing_parameter_type,
			"type of %qD defaults to %<int%>", decl);
	}

      درخت_PURPOSE (parm) = decl;
      نظر_آیا_دلائل.جوڑو (decl);
    }

  /* Now examine the parms chain for incomplete declarations
     and declarations with no corresponding names.  */

  برائے (b = current_scope->bindings; b; b = b->پچھلا)
    {
      parm = b->decl;
      اگر (درخت_رمز (parm) != PARM_DECL)
	جاری;

      اگر (درخت_TYPE (parm) != error_mark_گرہ
	  && !COMPLETE_TYPE_P (درخت_TYPE (parm)))
	{
	  error_at (DECL_ماخذ_LOCATION (parm),
		    "parameter %qD has incomplete type", parm);
	  درخت_TYPE (parm) = error_mark_گرہ;
	}

      اگر (!نظر_آیا_دلائل.شامل_ہے (parm))
	{
	  error_at (DECL_ماخذ_LOCATION (parm),
		    "declaration for parameter %qD but no such parameter",
		    parm);

	  /* Pretend the parameter was not missing.
	     This gets us to a standard state and minimizes
	     further error messages.  */
	  parmids = chainon (parmids, درخت_cons (parm, 0, 0));
	}
    }

  /* Chain the declarations together in the order of the list of
     names.  Store that chain in the function decl, replacing the
     list of names.  Update the current scope to match.  */
  DECL_ARGUMENTS (fndecl) = NULL_درخت;

  برائے (parm = parmids; parm; parm = درخت_CHAIN (parm))
    اگر (درخت_PURPOSE (parm))
      توڑو;
  اگر (parm && درخت_PURPOSE (parm))
    {
      آخری = درخت_PURPOSE (parm);
      DECL_ARGUMENTS (fndecl) = آخری;

      برائے (parm = درخت_CHAIN (parm); parm; parm = درخت_CHAIN (parm))
	اگر (درخت_PURPOSE (parm))
	  {
	    DECL_CHAIN (آخری) = درخت_PURPOSE (parm);
	    آخری = درخت_PURPOSE (parm);
	  }
      DECL_CHAIN (آخری) = NULL_درخت;
    }

  /* If there was a previous prototype,
     set the DECL_ARG_TYPE of each argument according to
     the type previously specified, and report any mismatches.  */

  اگر (current_function_prototype_arg_types)
    {
      درخت type;
      برائے (parm = DECL_ARGUMENTS (fndecl),
	     type = current_function_prototype_arg_types;
	   parm || (type != NULL_درخت
		    && درخت_قدر (type) != error_mark_گرہ
		    && TYPE_MAIN_VARIANT (درخت_قدر (type)) != void_type_گرہ);
	   parm = DECL_CHAIN (parm), type = درخت_CHAIN (type))
	{
	  اگر (parm == NULL_درخت
	      || type == NULL_درخت
	      || (درخت_قدر (type) != error_mark_گرہ
		  && TYPE_MAIN_VARIANT (درخت_قدر (type)) == void_type_گرہ))
	    {
	      اگر (current_function_prototype_built_اندر)
		warning_at (DECL_ماخذ_LOCATION (fndecl),
			    0, "number of arguments doesn%'t match "
			    "built-in prototype");
	      ورنہ
		{
		  /* FIXME diagnostics: This should be the location of
		     FNDECL, but there is bug when a prototype is
		     declared inside function context, but defined
		     outside of it (e.g., gcc.dg/pr15698-2.c).  In
		     which case FNDECL gets the location of the
		     prototype, not the definition.  */
		  error_at (داخلہ_location,
			    "number of arguments doesn%'t match prototype");

		  error_at (current_function_prototype_locus,
			    "prototype declaration");
		}
	      توڑو;
	    }
	  /* Type for passing arg must be consistent with that
	     declared for the arg.  ISO C says we take the unqualified
	     type for parameters declared with qualified type.  */
	  اگر (درخت_TYPE (parm) != error_mark_گرہ
	      && درخت_قدر (type) != error_mark_گرہ
	      && ((TYPE_ATOMIC (DECL_ARG_TYPE (parm))
		   != TYPE_ATOMIC (درخت_قدر (type)))
		  || !comptypes (TYPE_MAIN_VARIANT (DECL_ARG_TYPE (parm)),
				 TYPE_MAIN_VARIANT (درخت_قدر (type)))))
	    {
	      اگر ((TYPE_ATOMIC (DECL_ARG_TYPE (parm))
		   == TYPE_ATOMIC (درخت_قدر (type)))
		  && (TYPE_MAIN_VARIANT (درخت_TYPE (parm))
		      == TYPE_MAIN_VARIANT (درخت_قدر (type))))
		{
		  /* Adjust argument to match prototype.  E.g. a previous
		     `int foo(float);' prototype causes
		     `int foo(x) float x; {...}' to be treated like
		     `int foo(float x) {...}'.  This is particularly
		     useful for argument types like uid_t.  */
		  DECL_ARG_TYPE (parm) = درخت_TYPE (parm);

		  /* ??? Is it possible to get here with a
		     built-in prototype or will it always have
		     been diagnosed as conflicting with an
		     old-style definition and discarded?  */
		  اگر (current_function_prototype_built_اندر)
		    warning_at (DECL_ماخذ_LOCATION (parm),
				OPT_Wpedantic, "promoted argument %qD "
				"doesn%'t match built-in prototype", parm);
		  ورنہ
		    {
		      pedwarn (DECL_ماخذ_LOCATION (parm),
			       OPT_Wpedantic, "promoted argument %qD "
			       "doesn%'t match prototype", parm);
		      pedwarn (current_function_prototype_locus, OPT_Wpedantic,
			       "prototype declaration");
		    }
		}
	      ورنہ
		{
		  اگر (current_function_prototype_built_اندر)
		    warning_at (DECL_ماخذ_LOCATION (parm),
				0, "argument %qD doesn%'t match "
				"built-in prototype", parm);
		  ورنہ
		    {
		      error_at (DECL_ماخذ_LOCATION (parm),
				"argument %qD doesn%'t match prototype", parm);
		      error_at (current_function_prototype_locus,
				"prototype declaration");
		    }
		}
	    }
	}
      TYPE_ACTUAL_ARG_TYPES (درخت_TYPE (fndecl)) = NULL_درخت;
    }

  /* Otherwise, create a prototype that would match.  */

  ورنہ
    {
      درخت actual = NULL_درخت, آخری = NULL_درخت, type;

      برائے (parm = DECL_ARGUMENTS (fndecl); parm; parm = DECL_CHAIN (parm))
	{
	  type = درخت_cons (NULL_درخت, DECL_ARG_TYPE (parm), NULL_درخت);
	  اگر (آخری)
	    درخت_CHAIN (آخری) = type;
	  ورنہ
	    actual = type;
	  آخری = type;
	}
      type = درخت_cons (NULL_درخت, void_type_گرہ, NULL_درخت);
      اگر (آخری)
	درخت_CHAIN (آخری) = type;
      ورنہ
	actual = type;

      /* We are going to assign a new value for the TYPE_ACTUAL_ARG_TYPES
	 of the type of this function, but we need to avoid having this
	 affect the types of other similarly-typed functions, so we must
	 first force the generation of an identical (but separate) type
	 node for the relevant function type.  The new node we create
	 will be a variant of the main variant of the original function
	 type.  */

      درخت_TYPE (fndecl) = build_variant_type_copy (درخت_TYPE (fndecl));

      TYPE_ACTUAL_ARG_TYPES (درخت_TYPE (fndecl)) = actual;
    }
}

/* Store parameter declarations passed in ARG_INFO into the current
   function declaration.  */

خالی
store_parm_decls_from (ساخت c_arg_info *arg_info)
{
  current_function_arg_info = arg_info;
  store_parm_decls ();
}

/* Called by walk_tree to look for and update context-less labels
   or labels with context in the parent function.  */

ساکن درخت
سیٹ_labels_context_r (درخت *tp, صحیح *walk_subtrees, خالی *ڈیٹا)
{
  درخت ctx = static_cast<درخت>(ڈیٹا);
  اگر (درخت_رمز (*tp) == LABEL_اظہاریہ
      && (DECL_CONTEXT (LABEL_اظہاریہ_LABEL (*tp)) == NULL_درخت
	  || DECL_CONTEXT (LABEL_اظہاریہ_LABEL (*tp)) == DECL_CONTEXT (ctx)))
    {
      DECL_CONTEXT (LABEL_اظہاریہ_LABEL (*tp)) = ctx;
      *walk_subtrees = 0;
    }

  واپس NULL_درخت;
}

/* Store the parameter declarations into the current function declaration.
   This is called after parsing the parameter declarations, before
   digesting the body of the function.

   For an old-style definition, construct a prototype out of the old-style
   parameter declarations and inject it into the function's type.  */

خالی
store_parm_decls (خالی)
{
  درخت fndecl = current_function_decl;
  منطقی proto;

  /* The argument information block for FNDECL.  */
  ساخت c_arg_info *arg_info = current_function_arg_info;
  current_function_arg_info = 0;

  /* True if this definition is written with a prototype.  In C23, an
     empty argument list was converted to (void) in grokparms; in
     older C standard versions, it does not give the function a type
     with a prototype for future calls.  */
  proto = arg_info->types != 0 || arg_info->no_named_دلائل_stdarg_p;

  اگر (proto)
    store_parm_decls_newstyle (fndecl, arg_info);
  ورنہ
    store_parm_decls_oldstyle (fndecl, arg_info);

  /* The next call to push_scope will be a function body.  */

  اگلا_is_function_body = سچ;

  /* Write a record describing this function definition to the prototypes
     file (if requested).  */

  gen_aux_info_ریکارڈ (fndecl, 1, 0, proto);

  /* Initialize the RTL code for the function.  */
  allocate_struct_function (fndecl, جھوٹ);

  اگر (warn_غیر_مستعمل_local_typedefs)
    cfun->language = ggc_cleared_alloc<language_function> ();

  /* Begin the statement tree for this function.  */
  DECL_SAVED_درخت (fndecl) = ڈالو_stmt_list ();

  /* ??? Insert the contents of the pending sizes list into the function
     to be evaluated.  The only reason left to have this is
	void foo(int n, int array[n++])
     because we throw away the array type in favor of a pointer type, and
     thus won't naturally see the SAVE_EXPR containing the increment.  All
     other pending sizes would be handled by gimplify_parameters.  */
  اگر (arg_info->pending_sizes)
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
      walk_درخت_without_duplicates (&arg_info->pending_sizes,
				    سیٹ_labels_context_r, fndecl);
      جوڑو_stmt (arg_info->pending_sizes);
    }
}

/* Store PARM_DECLs in PARMS into scope temporarily.  Used for
   c_finish_omp_declare_simd for function prototypes.  No diagnostics
   should be done.  */

خالی
عارضی_store_parm_decls (درخت fndecl, درخت parms)
{
  ڈالو_scope ();
  برائے (درخت p = parms; p; p = DECL_CHAIN (p))
    {
      DECL_CONTEXT (p) = fndecl;
      اگر (DECL_NAME (p))
	bind (DECL_NAME (p), p, current_scope,
	      /*invisible=*/جھوٹ, /*nested=*/جھوٹ,
	      UNKNOWN_LOCATION);
    }
}

/* Undo what temp_store_parm_decls did.  */

خالی
عارضی_نکالو_parm_decls (خالی)
{
  /* Clear all bindings in this temporary scope, so that
     pop_scope doesn't create a BLOCK.  */
  ساخت c_binding *b = current_scope->bindings;
  current_scope->bindings = تہی;
  برائے (; b; b = free_binding_and_advance (b))
    {
      gcc_assert (درخت_رمز (b->decl) == PARM_DECL
		  || b->decl == error_mark_گرہ);
      gcc_assert (I_علامت_BINDING (b->id) == b);
      I_علامت_BINDING (b->id) = b->shadowed;
      اگر (b->shadowed && b->shadowed->u.type)
	درخت_TYPE (b->shadowed->decl) = b->shadowed->u.type;
    }
  نکالو_scope ();
}


/* Finish up a function declaration and compile that function
   all the way to assembler language output.  Then free the storage
   for the function definition.

   This is called after parsing the body of the function definition.  */

خالی
اختتام_function (location_t انتہا_loc)
{
  درخت fndecl = current_function_decl;

  اگر (c_dialect_objc ())
    objc_اختتام_function ();

  اگر (DECL_INITIAL (fndecl) && DECL_INITIAL (fndecl) != error_mark_گرہ)
    بلاک_SUPERCONTEXT (DECL_INITIAL (fndecl)) = fndecl;

  /* Must mark the RESULT_DECL as being in this function.  */

  اگر (DECL_نتیجہ (fndecl) && DECL_نتیجہ (fndecl) != error_mark_گرہ)
    DECL_CONTEXT (DECL_نتیجہ (fndecl)) = fndecl;

  اگر (MAIN_NAME_P (DECL_NAME (fndecl)) && !درخت_THIS_VOLATILE (fndecl)
      && TYPE_MAIN_VARIANT (درخت_TYPE (درخت_TYPE (fndecl)))
      == integer_type_گرہ && flag_isoc99)
    {
      /* Hack.  We don't want the middle-end to warn that this return
	 is unreachable, so we mark its location as special.  Using
	 UNKNOWN_LOCATION has the problem that it gets clobbered in
	 annotate_one_with_locus.  A cleaner solution might be to
	 ensure ! should_carry_locus_p (stmt), but that needs a flag.
      */
      c_اختتام_return (BUILTINS_LOCATION, integer_zero_گرہ, NULL_درخت);
    }

  /* Tie off the statement tree for this function.  */
  DECL_SAVED_درخت (fndecl) = نکالو_stmt_list (DECL_SAVED_درخت (fndecl));

  اختتام_fname_decls ();

  /* Complain if there's no return statement only if option specified on
     command line.  */
  اگر (warn_return_type > 0
      && درخت_رمز (درخت_TYPE (درخت_TYPE (fndecl))) != VOID_TYPE
      && !current_function_returns_قدر && !current_function_returns_null
      /* Don't complain if we are no-return.  */
      && !current_function_returns_abnormally
      /* Don't complain if we are declared noreturn.  */
      && !درخت_THIS_VOLATILE (fndecl)
      /* Don't warn for main().  */
      && !MAIN_NAME_P (DECL_NAME (fndecl))
      /* Or if they didn't actually specify a return type.  */
      && !C_FUNCTION_IMPLICIT_INT (fndecl)
      /* Normally, with -Wreturn-type, flow will complain, but we might
         optimize out static functions.  */
      && !درخت_عوامی (fndecl)
      && targetm.warn_func_return (fndecl)
      && warning (OPT_Wreturn_type,
		  "no return statement in function returning non-void"))
    suppress_warning (fndecl, OPT_Wreturn_type);

  /* Complain about parameters that are only set, but never otherwise used.  */
  اگر (warn_غیر_مستعمل_but_سیٹ_parameter)
    {
      درخت decl;

      برائے (decl = DECL_ARGUMENTS (fndecl);
	   decl;
	   decl = DECL_CHAIN (decl))
	اگر (درخت_مستعمل (decl)
	    && درخت_رمز (decl) == PARM_DECL
	    && !DECL_READ_P (decl)
	    && DECL_NAME (decl)
	    && !DECL_ARTIFICIAL (decl)
	    && !warning_suppressed_p (decl, OPT_Wunused_but_سیٹ_parameter))
	  warning_at (DECL_ماخذ_LOCATION (decl),
		      OPT_Wunused_but_سیٹ_parameter,
		      "parameter %qD set but not used", decl);
    }

  /* Complain about locally defined typedefs that are not used in this
     function.  */
  maybe_warn_غیر_مستعمل_local_typedefs ();

  /* Possibly warn about unused parameters.  */
  اگر (warn_غیر_مستعمل_parameter)
    do_warn_غیر_مستعمل_parameter (fndecl);

  /* Store the end of the function, so that we get good line number
     info for the epilogue.  */
  cfun->function_انتہا_locus = انتہا_loc;

  /* Finalize the ELF visibility for the function.  */
  c_determine_visibility (fndecl);

  /* For GNU C extern inline functions disregard inline limits.  */
  اگر (DECL_EXTERNAL (fndecl)
      && DECL_DECLARED_INLINE_P (fndecl)
      && (flag_gnu89_inline
	  || lookup_attribute ("gnu_inline", DECL_اوصاف (fndecl))))
    DECL_DISREGARD_INLINE_LIMITS (fndecl) = 1;

  /* Genericize before inlining.  Delay genericizing nested functions
     until their parent function is genericized.  Since finalizing
     requires GENERIC, delay that as well.  */

  اگر (DECL_INITIAL (fndecl) && DECL_INITIAL (fndecl) != error_mark_گرہ
      && !undef_nested_function)
    {
      اگر (!decl_function_context (fndecl))
	{
	  invoke_plugin_callbacks (PLUGIN_PRE_GENERICIZE, fndecl);
	  c_genericize (fndecl);

	  /* ??? Objc emits functions after finalizing the compilation unit.
	     This should be cleaned up later and this conditional removed.  */
	  اگر (symtab->global_info_ready)
	    {
	      cgraph_گرہ::جوڑو_new_function (fndecl, جھوٹ);
	      واپس;
	    }
	  cgraph_گرہ::finalize_function (fndecl, جھوٹ);
	}
      ورنہ
	{
	  /* Register this function with cgraph just far enough to get it
	    added to our parent's nested function list.  Handy, since the
	    C front end doesn't have such a list.  */
	  (خالی) cgraph_گرہ::get_create (fndecl);
	}
    }

  اگر (!decl_function_context (fndecl))
    undef_nested_function = جھوٹ;

  اگر (cfun->language != تہی)
    {
      ggc_free (cfun->language);
      cfun->language = تہی;
    }

  /* We're leaving the context of this function, so zap cfun.
     It's still in DECL_STRUCT_FUNCTION, and we'll restore it in
     tree_rest_of_compilation.  */
  سیٹ_cfun (تہی);
  invoke_plugin_callbacks (PLUGIN_اختتام_PARSE_FUNCTION, current_function_decl);
  current_function_decl = تہی;
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

درخت
check_for_loop_decls (location_t loc, منطقی turn_off_iso_c99_error)
{
  ساخت c_binding *b;
  درخت one_decl = NULL_درخت;
  صحیح n_decls = 0;

  اگر (!turn_off_iso_c99_error)
    {
      ساکن منطقی hint = سچ;
      /* If we get here, declarations have been used in a for loop without
	 the C99 for loop scope.  This doesn't make much sense, so don't
	 allow it.  */
      auto_diagnostic_گروہ d;
      error_at (loc, "%<for%> loop initial declarations "
		"are only allowed in C99 or C11 mode");
      اگر (hint)
	{
	  inform (loc,
		  "use option %<-std=c99%>, %<-std=gnu99%>, %<-std=c11%> or "
		  "%<-std=gnu11%> to compile your code");
	  hint = جھوٹ;
	}
      واپس NULL_درخت;
    }
  ورنہ
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

  برائے (b = current_scope->bindings; b; b = b->پچھلا)
    {
      درخت id = b->id;
      درخت decl = b->decl;

      اگر (!id)
	جاری;

      انتخاب (درخت_رمز (decl))
	{
	حالت VAR_DECL:
	  {
	    location_t decl_loc = DECL_ماخذ_LOCATION (decl);
	    اگر (درخت_STATIC (decl))
	      pedwarn_c11 (decl_loc, OPT_Wpedantic,
			   "declaration of static variable %qD in %<for%> "
			   "loop initial declaration", decl);
	    ورنہ اگر (DECL_EXTERNAL (decl))
	      pedwarn_c11 (decl_loc, OPT_Wpedantic,
			   "declaration of %<extern%> variable %qD in %<for%> "
			   "loop initial declaration", decl);
	  }
	  توڑو;

	حالت ریکارڈ_TYPE:
	  pedwarn_c11 (loc, OPT_Wpedantic,
		       "%<struct %E%> declared in %<for%> loop initial "
		       "declaration", id);
	  توڑو;
	حالت UNION_TYPE:
	  pedwarn_c11 (loc, OPT_Wpedantic,
		       "%<union %E%> declared in %<for%> loop initial "
		       "declaration",
		       id);
	  توڑو;
	حالت ENUMERAL_TYPE:
	  pedwarn_c11 (loc, OPT_Wpedantic,
		       "%<enum %E%> declared in %<for%> loop "
		       "initial declaration", id);
	  توڑو;
	طےشدہ:
	  pedwarn_c11 (loc, OPT_Wpedantic, "declaration of non-variable "
		       "%qD in %<for%> loop initial declaration", decl);
	}

      n_decls++;
      one_decl = decl;
    }

  واپس n_decls == 1 ? one_decl : NULL_درخت;
}

/* Save and reinitialize the variables
   used during compilation of a C function.  */

خالی
c_ڈالو_function_context (خالی)
{
  ساخت language_function *p = cfun->language;
  /* cfun->language might have been already allocated by the use of
     -Wunused-local-typedefs.  In that case, just re-use it.  */
  اگر (p == تہی)
    cfun->language = p = ggc_cleared_alloc<language_function> ();

  p->بنیاد.x_stmt_درخت = c_stmt_درخت;
  c_stmt_درخت.x_cur_stmt_list = vec_محفوظ_copy (c_stmt_درخت.x_cur_stmt_list);
  p->x_اندر_statement = اندر_statement;
  p->x_switch_ڈھیر = c_switch_ڈھیر;
  p->loop_نام = loop_نام;
  loop_نام = vNULL;
  p->loop_نام_hash = loop_نام_hash;
  loop_نام_hash = تہی;
  p->arg_info = current_function_arg_info;
  p->returns_قدر = current_function_returns_قدر;
  p->returns_null = current_function_returns_null;
  p->returns_abnormally = current_function_returns_abnormally;
  p->warn_about_return_type = warn_about_return_type;

  ڈالو_function_context ();
}

/* Restore the variables used during compilation of a C function.  */

خالی
c_نکالو_function_context (خالی)
{
  ساخت language_function *p;

  نکالو_function_context ();
  p = cfun->language;

  /* When -Wunused-local-typedefs is in effect, cfun->languages is
     used to store data throughout the life time of the current cfun,
     So don't deallocate it.  */
  اگر (!warn_غیر_مستعمل_local_typedefs)
    cfun->language = تہی;

  اگر (DECL_STRUCT_FUNCTION (current_function_decl) == 0
      && DECL_SAVED_درخت (current_function_decl) == NULL_درخت)
    {
      /* Stop pointing to the local nodes about to be freed.  */
      /* But DECL_INITIAL must remain nonzero so we know this
	 was an actual function definition.  */
      DECL_INITIAL (current_function_decl) = error_mark_گرہ;
      DECL_ARGUMENTS (current_function_decl) = NULL_درخت;
    }

  c_stmt_درخت = p->بنیاد.x_stmt_درخت;
  p->بنیاد.x_stmt_درخت.x_cur_stmt_list = تہی;
  اندر_statement = p->x_اندر_statement;
  c_switch_ڈھیر = p->x_switch_ڈھیر;
  loop_نام.release ();
  loop_نام = p->loop_نام;
  p->loop_نام = vNULL;
  حذف loop_نام_hash;
  loop_نام_hash = p->loop_نام_hash;
  p->loop_نام_hash = تہی;
  current_function_arg_info = p->arg_info;
  current_function_returns_قدر = p->returns_قدر;
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

stmt_درخت
current_stmt_درخت (خالی)
{
  واپس &c_stmt_درخت;
}

/* Return the global value of T as a symbol.  */

درخت
identifier_global_قدر	(درخت t)
{
  ساخت c_binding *b;

  برائے (b = I_علامت_BINDING (t); b; b = b->shadowed)
    اگر (B_اندر_FILE_SCOPE (b) || B_اندر_EXTERNAL_SCOPE (b))
      واپس b->decl;

  واپس NULL_درخت;
}

/* Return the global value of tag T as a symbol.  */

درخت
identifier_global_لیبل (درخت t)
{
  ساخت c_binding *b;

  برائے (b = I_لیبل_BINDING (t); b; b = b->shadowed)
    اگر (B_اندر_FILE_SCOPE (b) || B_اندر_EXTERNAL_SCOPE (b))
      واپس b->decl;

  واپس NULL_درخت;
}

/* Returns non-zero (result of __has_builtin) if NAME refers to a built-in
   function or function-like operator.  */

صحیح
نام_builtin_p (ثابت حرف *name)
{
  درخت id = get_identifier (name);
  اگر (درخت decl = identifier_global_قدر (id))
    واپس درخت_رمز (decl) == FUNCTION_DECL && DECL_IS_UNDECLARED_BUILTIN (decl);

  /* Also detect common reserved C words that aren't strictly built-in
     functions.  */
  انتخاب (C_RID_رمز (id))
    {
    حالت RID_BUILTIN_ASSOC_BARRIER:
    حالت RID_BUILTIN_BITREVERSEG:
    حالت RID_BUILTIN_BSWAPG:
    حالت RID_BUILTIN_CONVERTVECTOR:
    حالت RID_BUILTIN_HAS_ATTRIBUTE:
    حالت RID_BUILTIN_SHUFFLE:
    حالت RID_BUILTIN_SHUFFLEVECTOR:
    حالت RID_BUILTIN_STDC:
    حالت RID_BUILTIN_COUNTED_BY_REF:
    حالت RID_انتخاب_اظہاریہ:
    حالت RID_OFFSETOF:
    حالت RID_TYPES_COMPATIBLE_P:
    حالت RID_C23_VA_آغاز:
    حالت RID_VA_ARG:
      واپس 1;
    طےشدہ:
      توڑو;
    }

  واپس 0;
}

/* In C, the only C-linkage public declaration is at file scope.  */

درخت
c_linkage_bindings (درخت name)
{
  واپس identifier_global_قدر (name);
}

/* Record a builtin type for C.  If NAME is non-NULL, it is the name used;
   otherwise the name is found in ridpointers from RID_INDEX.  */

خالی
ریکارڈ_builtin_type (شمار rid rid_اشاریہ, ثابت حرف *name, درخت type)
{
  درخت id, decl;
  اگر (name == 0)
    id = ridpointers[(صحیح) rid_اشاریہ];
  ورنہ
    id = get_identifier (name);
  decl = build_decl (UNKNOWN_LOCATION, TYPE_DECL, id, type);
  pushdecl (decl);
  اگر (debug_hooks->type_decl)
    debug_hooks->type_decl (decl, جھوٹ);
}

/* Return a c_parm structure with the given SPECS, ATTRS and DECLARATOR.  */

ساخت c_parm *
build_c_parm (ساخت c_declspecs *specs, درخت attrs,
	      ساخت c_declarator *declarator,
	      location_t loc)
{
  ساخت c_parm *ret = XOBNEW (&parser_obstack, ساخت c_parm);
  ret->specs = specs;
  ret->attrs = attrs;
  ret->declarator = declarator;
  ret->loc = loc;
  واپس ret;
}

/* Return a declarator with nested attributes.  TARGET is the inner
   declarator to which these attributes apply.  ATTRS are the
   attributes.  */

ساخت c_declarator *
build_attrs_declarator (درخت attrs, ساخت c_declarator *ہدف)
{
  ساخت c_declarator *ret = XOBNEW (&parser_obstack, ساخت c_declarator);
  ret->قسم = cdk_attrs;
  ret->declarator = ہدف;
  ret->u.attrs = attrs;
  واپس ret;
}

/* Return a declarator for a function with arguments specified by ARGS
   and return type specified by TARGET.  */

ساخت c_declarator *
build_function_declarator (ساخت c_arg_info *دلائل,
			   ساخت c_declarator *ہدف)
{
  ساخت c_declarator *ret = XOBNEW (&parser_obstack, ساخت c_declarator);
  ret->قسم = cdk_function;
  ret->declarator = ہدف;
  ret->u.arg_info = دلائل;
  واپس ret;
}

/* Return a declarator for the identifier IDENT (which may be
   NULL_TREE for an abstract declarator).  */

ساخت c_declarator *
build_id_declarator (درخت ident)
{
  ساخت c_declarator *ret = XOBNEW (&parser_obstack, ساخت c_declarator);
  ret->قسم = cdk_id;
  ret->declarator = 0;
  ret->u.id.id = ident;
  ret->u.id.attrs = NULL_درخت;
  /* Default value - may get reset to a more precise location. */
  ret->id_loc = داخلہ_location;
  واپس ret;
}

/* Return something to represent absolute declarators containing a *.
   TARGET is the absolute declarator that the * contains.
   TYPE_QUALS_ATTRS is a structure for type qualifiers and attributes
   to apply to the pointer type.  */

ساخت c_declarator *
make_اشارہ_گر_declarator (ساخت c_declspecs *type_quals_attrs,
			 ساخت c_declarator *ہدف)
{
  درخت attrs;
  صحیح quals = 0;
  ساخت c_declarator *itarget = ہدف;
  ساخت c_declarator *ret = XOBNEW (&parser_obstack, ساخت c_declarator);
  اگر (type_quals_attrs)
    {
      attrs = type_quals_attrs->attrs;
      quals = quals_from_declspecs (type_quals_attrs);
      اگر (attrs != NULL_درخت)
	itarget = build_attrs_declarator (attrs, ہدف);
    }
  ret->قسم = cdk_اشارہ_گر;
  ret->declarator = itarget;
  ret->u.اشارہ_گر_quals = quals;
  واپس ret;
}

/* Return a pointer to a structure for an empty list of declaration
   specifiers.  */

ساخت c_declspecs *
build_null_declspecs (خالی)
{
  ساخت c_declspecs *ret = XOBNEW (&parser_obstack, ساخت c_declspecs);
  memset (ret, 0, حجم *ret);
  ret->align_log = -1;
  ret->typespec_لفظ = cts_none;
  ret->storage_class = csc_none;
  ret->اظہاریہ_const_operands = سچ;
  ret->typespec_قسم = ctsk_none;
  ret->پتہ_space = ADDR_SPACE_GENERIC;
  واپس ret;
}

/* Add the address space ADDRSPACE to the declaration specifiers
   SPECS, returning SPECS.  */

ساخت c_declspecs *
declspecs_جوڑو_addrspace (location_t location,
			 ساخت c_declspecs *specs, addr_space_t as)
{
  specs->non_sc_نظر_آیا_p = سچ;
  specs->declspecs_نظر_آیا_p = سچ;
  specs->non_std_attrs_نظر_آیا_p = سچ;

  اگر (!ADDR_SPACE_GENERIC_P (specs->پتہ_space)
      && specs->پتہ_space != as)
    error ("incompatible address space qualifiers %qs and %qs",
	   c_addr_space_name (as),
	   c_addr_space_name (specs->پتہ_space));
  ورنہ
    {
      specs->پتہ_space = as;
      specs->locations[cdw_پتہ_space] = location;
    }
  واپس specs;
}

/* Add the type qualifier QUAL to the declaration specifiers SPECS,
   returning SPECS.  */

ساخت c_declspecs *
declspecs_جوڑو_qual (location_t loc,
		    ساخت c_declspecs *specs, درخت qual)
{
  شمار rid i;
  منطقی dupe = جھوٹ;
  specs->non_sc_نظر_آیا_p = سچ;
  specs->declspecs_نظر_آیا_p = سچ;
  specs->non_std_attrs_نظر_آیا_p = سچ;
  gcc_assert (درخت_رمز (qual) == IDENTIFIER_گرہ
	      && C_IS_RESERVED_لفظ (qual));
  i = C_RID_رمز (qual);
  location_t پچھلا_loc = UNKNOWN_LOCATION;
  انتخاب (i)
    {
    حالت RID_CONST:
      dupe = specs->const_p;
      specs->const_p = سچ;
      پچھلا_loc = specs->locations[cdw_const];
      specs->locations[cdw_const] = loc;
      توڑو;
    حالت RID_VOLATILE:
      dupe = specs->volatile_p;
      specs->volatile_p = سچ;
      پچھلا_loc = specs->locations[cdw_volatile];
      specs->locations[cdw_volatile] = loc;
      توڑو;
    حالت RID_RESTRICT:
      dupe = specs->restrict_p;
      specs->restrict_p = سچ;
      پچھلا_loc = specs->locations[cdw_restrict];
      specs->locations[cdw_restrict] = loc;
      توڑو;
    حالت RID_ATOMIC:
      dupe = specs->atomic_p;
      specs->atomic_p = سچ;
      پچھلا_loc = specs->locations[cdw_atomic];
      specs->locations[cdw_atomic] = loc;
      توڑو;
    طےشدہ:
      gcc_unreachable ();
    }
  اگر (dupe)
    {
      منطقی warned = pedwarn_c90 (loc, OPT_Wpedantic,
				 "duplicate %qE declaration specifier", qual);
      اگر (!warned
	  && warn_duplicate_decl_specifier
	  && پچھلا_loc >= RESERVED_LOCATION_گنتی
	  && !from_macro_expansion_at (پچھلا_loc)
	  && !from_macro_expansion_at (loc))
	warning_at (loc, OPT_Wduplicate_decl_specifier,
		    "duplicate %qE declaration specifier", qual);
    }
  واپس specs;
}

/* Add the type specifier TYPE to the declaration specifiers SPECS,
   returning SPECS.  */

ساخت c_declspecs *
declspecs_جوڑو_type (location_t loc, ساخت c_declspecs *specs,
		    ساخت c_typespec spec)
{
  درخت type = spec.spec;
  specs->non_sc_نظر_آیا_p = سچ;
  specs->declspecs_نظر_آیا_p = سچ;
  specs->non_std_attrs_نظر_آیا_p = سچ;
  specs->typespec_قسم = spec.قسم;
  اگر (درخت_DEPRECATED (type))
    specs->deprecated_p = سچ;
  اگر (درخت_UNAVAILABLE (type))
    specs->unavailable_p = سچ;

  /* As a type specifier is present, "auto" must be used as a storage
     class specifier, not for type deduction.  */
  اگر (specs->c23_auto_p)
    {
      specs->c23_auto_p = جھوٹ;
      اگر (specs->storage_class != csc_none)
	error ("multiple storage classes in declaration specifiers");
      ورنہ اگر (specs->thread_p)
	error ("%qs used with %<auto%>",
	       specs->thread_gnu_p ? "__thread" : "_Thread_local");
      ورنہ اگر (specs->constexpr_p)
	/* auto may only be used with another storage class specifier,
	   such as constexpr, if the type is inferred.  */
	error ("%<auto%> used with %<constexpr%>");
      ورنہ
	specs->storage_class = csc_auto;
    }

  /* Handle type specifier keywords.  */
  اگر (درخت_رمز (type) == IDENTIFIER_گرہ
      && C_IS_RESERVED_لفظ (type)
      && C_RID_رمز (type) != RID_CXX_COMPAT_WARN)
    {
      شمار rid i = C_RID_رمز (type);
      اگر (specs->type)
	{
	  error_at (loc, "two or more data types in declaration specifiers");
	  واپس specs;
	}
      اگر ((صحیح) i <= (صحیح) RID_آخری_MODIFIER)
	{
	  /* "long", "short", "signed", "unsigned", "_Complex" or "_Sat".  */
	  منطقی dupe = جھوٹ;
	  انتخاب (i)
	    {
	    حالت RID_LONG:
	      اگر (specs->long_long_p)
		{
		  error_at (loc, "%<long long long%> is too long for GCC");
		  توڑو;
		}
	      اگر (specs->long_p)
		{
		  اگر (specs->typespec_لفظ == cts_double)
		    {
		      error_at (loc,
				"both %qs and %qs in declaration specifiers",
				"long long", "double");
		      توڑو;
		    }
		  pedwarn_c90 (loc, OPT_Wlong_long,
			       "ISO C90 does not support %<long long%>");
		  specs->long_long_p = 1;
		  specs->locations[cdw_long_long] = loc;
		  توڑو;
		}
	      اگر (specs->short_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "short");
	      ورنہ اگر (specs->typespec_لفظ == cts_auto_type)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "__auto_type");
	      ورنہ اگر (specs->typespec_لفظ == cts_void)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "void");
	      ورنہ اگر (specs->typespec_لفظ == cts_int_n)
		error_at (loc,
			  "both %qs and %<__int%d%> in declaration specifiers",
			  "long", int_n_ڈیٹا[specs->u.int_n_idx].bitsize);
	      ورنہ اگر (specs->typespec_لفظ == cts_bool)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "_Bool");
	      ورنہ اگر (specs->typespec_لفظ == cts_bitint)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "_BitInt");
	      ورنہ اگر (specs->typespec_لفظ == cts_char)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "char");
	      ورنہ اگر (specs->typespec_لفظ == cts_float)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "float");
	      ورنہ اگر (specs->typespec_لفظ == cts_floatn_nx)
		error_at (loc,
			  "both %qs and %<_Float%d%s%> in declaration "
			  "specifiers", "long",
			  floatn_nx_types[specs->u.floatn_nx_idx].n,
			  floatn_nx_types[specs->u.floatn_nx_idx].extended
			  ? "x"
			  : "");
	      ورنہ اگر (specs->typespec_لفظ == cts_dfloat32)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "_Decimal32");
	      ورنہ اگر (specs->typespec_لفظ == cts_dfloat64)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "_Decimal64");
	      ورنہ اگر (specs->typespec_لفظ == cts_dfloat128)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "_Decimal128");
	      ورنہ اگر (specs->typespec_لفظ == cts_dfloat64x)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "_Decimal64x");
	      ورنہ
		{
		  specs->long_p = سچ;
		  specs->locations[cdw_long] = loc;
		}
	      توڑو;
	    حالت RID_SHORT:
	      dupe = specs->short_p;
	      اگر (specs->long_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "short");
	      ورنہ اگر (specs->typespec_لفظ == cts_auto_type)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "__auto_type");
	      ورنہ اگر (specs->typespec_لفظ == cts_void)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "void");
	      ورنہ اگر (specs->typespec_لفظ == cts_int_n)
		error_at (loc,
			  "both %qs and %<__int%d%> in declaration specifiers",
			  "short", int_n_ڈیٹا[specs->u.int_n_idx].bitsize);
	      ورنہ اگر (specs->typespec_لفظ == cts_bool)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "_Bool");
	      ورنہ اگر (specs->typespec_لفظ == cts_bitint)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "_BitInt");
	      ورنہ اگر (specs->typespec_لفظ == cts_char)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "char");
	      ورنہ اگر (specs->typespec_لفظ == cts_float)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "float");
	      ورنہ اگر (specs->typespec_لفظ == cts_double)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "double");
	      ورنہ اگر (specs->typespec_لفظ == cts_floatn_nx)
		error_at (loc,
			  "both %qs and %<_Float%d%s%> in declaration "
			  "specifiers", "short",
			  floatn_nx_types[specs->u.floatn_nx_idx].n,
			  floatn_nx_types[specs->u.floatn_nx_idx].extended
			  ? "x"
			  : "");
	      ورنہ اگر (specs->typespec_لفظ == cts_dfloat32)
                error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "_Decimal32");
	      ورنہ اگر (specs->typespec_لفظ == cts_dfloat64)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "_Decimal64");
	      ورنہ اگر (specs->typespec_لفظ == cts_dfloat128)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "_Decimal128");
	      ورنہ اگر (specs->typespec_لفظ == cts_dfloat64x)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "_Decimal64x");
	      ورنہ
		{
		  specs->short_p = سچ;
		  specs->locations[cdw_short] = loc;
		}
	      توڑو;
	    حالت RID_SIGNED:
	      dupe = specs->signed_p;
	      اگر (specs->unsigned_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "unsigned");
	      ورنہ اگر (specs->typespec_لفظ == cts_auto_type)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "__auto_type");
	      ورنہ اگر (specs->typespec_لفظ == cts_void)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "void");
	      ورنہ اگر (specs->typespec_لفظ == cts_bool)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "_Bool");
	      ورنہ اگر (specs->typespec_لفظ == cts_float)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "float");
	      ورنہ اگر (specs->typespec_لفظ == cts_double)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "double");
	      ورنہ اگر (specs->typespec_لفظ == cts_floatn_nx)
		error_at (loc,
			  "both %qs and %<_Float%d%s%> in declaration "
			  "specifiers", "signed",
			  floatn_nx_types[specs->u.floatn_nx_idx].n,
			  floatn_nx_types[specs->u.floatn_nx_idx].extended
			  ? "x"
			  : "");
	      ورنہ اگر (specs->typespec_لفظ == cts_dfloat32)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "_Decimal32");
	      ورنہ اگر (specs->typespec_لفظ == cts_dfloat64)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "_Decimal64");
	      ورنہ اگر (specs->typespec_لفظ == cts_dfloat128)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "_Decimal128");
	      ورنہ اگر (specs->typespec_لفظ == cts_dfloat64x)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "_Decimal64x");
	      ورنہ
		{
		  specs->signed_p = سچ;
		  specs->locations[cdw_signed] = loc;
		}
	      توڑو;
	    حالت RID_UNSIGNED:
	      dupe = specs->unsigned_p;
	      اگر (specs->signed_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "unsigned");
	      ورنہ اگر (specs->typespec_لفظ == cts_auto_type)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "__auto_type");
	      ورنہ اگر (specs->typespec_لفظ == cts_void)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "void");
	      ورنہ اگر (specs->typespec_لفظ == cts_bool)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "_Bool");
	      ورنہ اگر (specs->typespec_لفظ == cts_float)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "float");
	      ورنہ اگر (specs->typespec_لفظ == cts_double)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "double");
	      ورنہ اگر (specs->typespec_لفظ == cts_floatn_nx)
		error_at (loc,
			  "both %qs and %<_Float%d%s%> in declaration "
			  "specifiers", "unsigned",
			  floatn_nx_types[specs->u.floatn_nx_idx].n,
			  floatn_nx_types[specs->u.floatn_nx_idx].extended
			  ? "x"
			  : "");
              ورنہ اگر (specs->typespec_لفظ == cts_dfloat32)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "_Decimal32");
	      ورنہ اگر (specs->typespec_لفظ == cts_dfloat64)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "_Decimal64");
	      ورنہ اگر (specs->typespec_لفظ == cts_dfloat128)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "_Decimal128");
	      ورنہ اگر (specs->typespec_لفظ == cts_dfloat64x)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "_Decimal64x");
	      ورنہ
		{
		  specs->unsigned_p = سچ;
		  specs->locations[cdw_unsigned] = loc;
		}
	      توڑو;
	    حالت RID_COMPLEX:
	      dupe = specs->complex_p;
	      اگر (!اندر_system_سرخی_at (loc))
		pedwarn_c90 (loc, OPT_Wpedantic,
			     "ISO C90 does not support complex types");
	      اگر (specs->typespec_لفظ == cts_auto_type)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "__auto_type");
	      ورنہ اگر (specs->typespec_لفظ == cts_void)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "void");
	      ورنہ اگر (specs->typespec_لفظ == cts_bool)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "_Bool");
	      ورنہ اگر (specs->typespec_لفظ == cts_bitint)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "_BitInt");
              ورنہ اگر (specs->typespec_لفظ == cts_dfloat32)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "_Decimal32");
	      ورنہ اگر (specs->typespec_لفظ == cts_dfloat64)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "_Decimal64");
	      ورنہ اگر (specs->typespec_لفظ == cts_dfloat128)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "_Decimal128");
	      ورنہ اگر (specs->typespec_لفظ == cts_dfloat64x)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "_Decimal64x");
	      ورنہ اگر (specs->typespec_لفظ == cts_fract)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "_Fract");
	      ورنہ اگر (specs->typespec_لفظ == cts_accum)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "_Accum");
	      ورنہ اگر (specs->saturating_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "_Sat");
	      ورنہ
		{
		  specs->complex_p = سچ;
		  specs->locations[cdw_complex] = loc;
		}
	      توڑو;
	    حالت RID_SAT:
	      dupe = specs->saturating_p;
	      pedwarn (loc, OPT_Wpedantic,
		       "ISO C does not support saturating types");
	      اگر (specs->typespec_لفظ == cts_int_n)
		error_at (loc,
			  "both %qs and %<__int%d%> in declaration specifiers",
			  "_Sat", int_n_ڈیٹا[specs->u.int_n_idx].bitsize);
	      ورنہ اگر (specs->typespec_لفظ == cts_auto_type)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "__auto_type");
	      ورنہ اگر (specs->typespec_لفظ == cts_void)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "void");
	      ورنہ اگر (specs->typespec_لفظ == cts_bool)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "_Bool");
	      ورنہ اگر (specs->typespec_لفظ == cts_bitint)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "_BitInt");
	      ورنہ اگر (specs->typespec_لفظ == cts_char)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "char");
	      ورنہ اگر (specs->typespec_لفظ == cts_int)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "int");
	      ورنہ اگر (specs->typespec_لفظ == cts_float)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "float");
	      ورنہ اگر (specs->typespec_لفظ == cts_double)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "double");
	      ورنہ اگر (specs->typespec_لفظ == cts_floatn_nx)
		error_at (loc,
			  "both %qs and %<_Float%d%s%> in declaration "
			  "specifiers", "_Sat",
			  floatn_nx_types[specs->u.floatn_nx_idx].n,
			  floatn_nx_types[specs->u.floatn_nx_idx].extended
			  ? "x"
			  : "");
              ورنہ اگر (specs->typespec_لفظ == cts_dfloat32)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "_Decimal32");
	      ورنہ اگر (specs->typespec_لفظ == cts_dfloat64)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "_Decimal64");
	      ورنہ اگر (specs->typespec_لفظ == cts_dfloat128)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "_Decimal128");
	      ورنہ اگر (specs->typespec_لفظ == cts_dfloat64x)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "_Decimal64x");
	      ورنہ اگر (specs->complex_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "complex");
	      ورنہ
		{
		  specs->saturating_p = سچ;
		  specs->locations[cdw_saturating] = loc;
		}
	      توڑو;
	    طےشدہ:
	      gcc_unreachable ();
	    }

	  اگر (dupe)
	    error_at (loc, "duplicate %qE", type);

	  واپس specs;
	}
      ورنہ
	{
	  /* "void", "_Bool", "char", "int", "float", "double",
	     "_FloatN", "_FloatNx", "_Decimal32", "__intN",
	     "_Decimal64", "_Decimal128", "_Fract", "_Accum", "_BitInt(N)" or
	     "__auto_type".  */
	  اگر (specs->typespec_لفظ != cts_none)
	    {
	      اگر (i == RID_BOOL)
		{
		  auto_diagnostic_گروہ d;
		  اگر (specs->storage_class == csc_typedef)
		    error_at (loc,
			      "%qs cannot be defined via %<typedef%>",
			      IDENTIFIER_اشارہ_گر (type));
		  ورنہ
		    error_at (loc,
			      "%qs cannot be used here",
			      IDENTIFIER_اشارہ_گر (type));
		  جوڑو_note_about_new_keyword (loc, type);
		}
	      ورنہ
		error_at (loc,
			  "two or more data types in declaration specifiers");
	      واپس specs;
	    }
	  انتخاب (i)
	    {
	    حالت RID_AUTO_TYPE:
	      اگر (specs->long_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "__auto_type");
	      ورنہ اگر (specs->short_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "__auto_type");
	      ورنہ اگر (specs->signed_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "__auto_type");
	      ورنہ اگر (specs->unsigned_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "__auto_type");
	      ورنہ اگر (specs->complex_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "__auto_type");
	      ورنہ اگر (specs->saturating_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "__auto_type");
	      ورنہ
		{
		  specs->typespec_لفظ = cts_auto_type;
		  specs->locations[cdw_typespec] = loc;
		}
	      واپس specs;
	    حالت RID_INT_N_0:
	    حالت RID_INT_N_1:
	    حالت RID_INT_N_2:
	    حالت RID_INT_N_3:
	      specs->u.int_n_idx = i - RID_INT_N_0;
	      اگر (!اندر_system_سرخی_at (داخلہ_location)
		  /* If the INT_N type ends in "__", and so is of the format
		     "__intN__", don't pedwarn.  */
		  && (لڑی_موازنہ (IDENTIFIER_اشارہ_گر (type)
			       + (IDENTIFIER_لمبائی (type) - 2), "__", 2) != 0))
		pedwarn (loc, OPT_Wpedantic,
			 "ISO C does not support %<__int%d%> types",
			 int_n_ڈیٹا[specs->u.int_n_idx].bitsize);

	      اگر (specs->long_p)
		error_at (loc,
			  "both %<__int%d%> and %qs in declaration specifiers",
			  int_n_ڈیٹا[specs->u.int_n_idx].bitsize, "long");
	      ورنہ اگر (specs->saturating_p)
		error_at (loc,
			  "both %qs and %<__int%d%> in declaration specifiers",
			  "_Sat", int_n_ڈیٹا[specs->u.int_n_idx].bitsize);
	      ورنہ اگر (specs->short_p)
		error_at (loc,
			  "both %<__int%d%> and %qs in declaration specifiers",
			  int_n_ڈیٹا[specs->u.int_n_idx].bitsize, "short");
	      ورنہ اگر (! int_n_enabled_p[specs->u.int_n_idx])
		{
		  specs->typespec_لفظ = cts_int_n;
		  error_at (loc,
			    "%<__int%d%> is not supported on this target",
			    int_n_ڈیٹا[specs->u.int_n_idx].bitsize);
		}
	      ورنہ
		{
		  specs->typespec_لفظ = cts_int_n;
		  specs->locations[cdw_typespec] = loc;
		}
	      واپس specs;
	    حالت RID_VOID:
	      اگر (specs->long_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "void");
	      ورنہ اگر (specs->short_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "void");
	      ورنہ اگر (specs->signed_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "void");
	      ورنہ اگر (specs->unsigned_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "void");
	      ورنہ اگر (specs->complex_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "void");
	      ورنہ اگر (specs->saturating_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "void");
	      ورنہ
		{
		  specs->typespec_لفظ = cts_void;
		  specs->locations[cdw_typespec] = loc;
		}
	      واپس specs;
	    حالت RID_BOOL:
	      اگر (!اندر_system_سرخی_at (loc))
		pedwarn_c90 (loc, OPT_Wpedantic,
			     "ISO C90 does not support boolean types");
	      اگر (specs->long_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "_Bool");
	      ورنہ اگر (specs->short_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "_Bool");
	      ورنہ اگر (specs->signed_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "_Bool");
	      ورنہ اگر (specs->unsigned_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "_Bool");
	      ورنہ اگر (specs->complex_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "_Bool");
	      ورنہ اگر (specs->saturating_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "_Bool");
	      ورنہ
		{
		  specs->typespec_لفظ = cts_bool;
		  specs->locations[cdw_typespec] = loc;
		}
	      واپس specs;
	    حالت RID_CHAR:
	      اگر (specs->long_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "char");
	      ورنہ اگر (specs->short_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "char");
	      ورنہ اگر (specs->saturating_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "char");
	      ورنہ
		{
		  specs->typespec_لفظ = cts_char;
		  specs->locations[cdw_typespec] = loc;
		}
	      واپس specs;
	    حالت RID_INT:
	      اگر (specs->saturating_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "int");
	      ورنہ
		{
		  specs->typespec_لفظ = cts_int;
		  specs->locations[cdw_typespec] = loc;
		}
	      واپس specs;
	    حالت RID_FLOAT:
	      اگر (specs->long_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "float");
	      ورنہ اگر (specs->short_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "float");
	      ورنہ اگر (specs->signed_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "float");
	      ورنہ اگر (specs->unsigned_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "float");
	      ورنہ اگر (specs->saturating_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "float");
	      ورنہ
		{
		  specs->typespec_لفظ = cts_float;
		  specs->locations[cdw_typespec] = loc;
		}
	      واپس specs;
	    حالت RID_DOUBLE:
	      اگر (specs->long_long_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long long", "double");
	      ورنہ اگر (specs->short_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "double");
	      ورنہ اگر (specs->signed_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "double");
	      ورنہ اگر (specs->unsigned_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "double");
	      ورنہ اگر (specs->saturating_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "double");
	      ورنہ
		{
		  specs->typespec_لفظ = cts_double;
		  specs->locations[cdw_typespec] = loc;
		}
	      واپس specs;
	    CASE_RID_FLOATN_NX:
	      specs->u.floatn_nx_idx = i - RID_FLOATN_NX_پہلا;
	      اگر (!اندر_system_سرخی_at (داخلہ_location))
		pedwarn_c11 (loc, OPT_Wpedantic,
			     "ISO C does not support the %<_Float%d%s%> type"
			     " before C23",
			     floatn_nx_types[specs->u.floatn_nx_idx].n,
			     floatn_nx_types[specs->u.floatn_nx_idx].extended
			     ? "x"
			     : "");

	      اگر (specs->long_p)
		error_at (loc,
			  "both %qs and %<_Float%d%s%> in declaration "
			  "specifiers", "long",
			  floatn_nx_types[specs->u.floatn_nx_idx].n,
			  floatn_nx_types[specs->u.floatn_nx_idx].extended
			  ? "x"
			  : "");
	      ورنہ اگر (specs->short_p)
		error_at (loc,
			  "both %qs and %<_Float%d%s%> in declaration "
			  "specifiers", "short",
			  floatn_nx_types[specs->u.floatn_nx_idx].n,
			  floatn_nx_types[specs->u.floatn_nx_idx].extended
			  ? "x"
			  : "");
	      ورنہ اگر (specs->signed_p)
		error_at (loc,
			  "both %qs and %<_Float%d%s%> in declaration "
			  "specifiers", "signed",
			  floatn_nx_types[specs->u.floatn_nx_idx].n,
			  floatn_nx_types[specs->u.floatn_nx_idx].extended
			  ? "x"
			  : "");
	      ورنہ اگر (specs->unsigned_p)
		error_at (loc,
			  "both %qs and %<_Float%d%s%> in declaration "
			  "specifiers", "unsigned",
			  floatn_nx_types[specs->u.floatn_nx_idx].n,
			  floatn_nx_types[specs->u.floatn_nx_idx].extended
			  ? "x"
			  : "");
	      ورنہ اگر (specs->saturating_p)
		error_at (loc,
			  "both %qs and %<_Float%d%s%> in declaration "
			  "specifiers", "_Sat",
			  floatn_nx_types[specs->u.floatn_nx_idx].n,
			  floatn_nx_types[specs->u.floatn_nx_idx].extended
			  ? "x"
			  : "");
	      ورنہ اگر (FLOATN_NX_TYPE_گرہ (specs->u.floatn_nx_idx) == NULL_درخت)
		{
		  specs->typespec_لفظ = cts_floatn_nx;
		  error_at (loc,
			    "%<_Float%d%s%> is not supported on this target",
			    floatn_nx_types[specs->u.floatn_nx_idx].n,
			    floatn_nx_types[specs->u.floatn_nx_idx].extended
			    ? "x"
			    : "");
		}
	      ورنہ
		{
		  specs->typespec_لفظ = cts_floatn_nx;
		  specs->locations[cdw_typespec] = loc;
		}
	      واپس specs;
	    حالت RID_DFLOAT32:
	    حالت RID_DFLOAT64:
	    حالت RID_DFLOAT128:
	    حالت RID_DFLOAT64X:
	      {
		ثابت حرف *str;
		اگر (i == RID_DFLOAT32)
		  str = "_Decimal32";
		ورنہ اگر (i == RID_DFLOAT64)
		  str = "_Decimal64";
		ورنہ اگر (i == RID_DFLOAT128)
		  str = "_Decimal128";
		ورنہ
		  str = "_Decimal64x";
		اگر (specs->long_long_p)
		  error_at (loc,
			    "both %qs and %qs in declaration specifiers",
			    "long long", str);
		اگر (specs->long_p)
		  error_at (loc,
			    "both %qs and %qs in declaration specifiers",
			    "long", str);
		ورنہ اگر (specs->short_p)
		  error_at (loc,
			    "both %qs and %qs in declaration specifiers",
			    "short", str);
		ورنہ اگر (specs->signed_p)
		  error_at (loc,
			    "both %qs and %qs in declaration specifiers",
			    "signed", str);
		ورنہ اگر (specs->unsigned_p)
		  error_at (loc,
			    "both %qs and %qs in declaration specifiers",
			    "unsigned", str);
                ورنہ اگر (specs->complex_p)
                  error_at (loc,
			    "both %qs and %qs in declaration specifiers",
			    "complex", str);
                ورنہ اگر (specs->saturating_p)
                  error_at (loc,
			    "both %qs and %qs in declaration specifiers",
			    "_Sat", str);
		ورنہ اگر (i == RID_DFLOAT32)
		  specs->typespec_لفظ = cts_dfloat32;
		ورنہ اگر (i == RID_DFLOAT64)
		  specs->typespec_لفظ = cts_dfloat64;
		ورنہ اگر (i == RID_DFLOAT128)
		  specs->typespec_لفظ = cts_dfloat128;
		ورنہ
		  specs->typespec_لفظ = cts_dfloat64x;
		specs->locations[cdw_typespec] = loc;
	      }
	      اگر (!targetm.decimal_float_supported_p ())
		error_at (loc,
			  "decimal floating-point not supported "
			  "for this target");
	      pedwarn_c11 (loc, OPT_Wpedantic,
			   "ISO C does not support decimal floating-point "
			   "before C23");
	      واپس specs;
	    حالت RID_FRACT:
	    حالت RID_ACCUM:
	      {
		ثابت حرف *str;
		اگر (i == RID_FRACT)
		  str = "_Fract";
		ورنہ
		  str = "_Accum";
                اگر (specs->complex_p)
                  error_at (loc,
			    "both %qs and %qs in declaration specifiers",
			    "complex", str);
		ورنہ اگر (i == RID_FRACT)
		    specs->typespec_لفظ = cts_fract;
		ورنہ
		    specs->typespec_لفظ = cts_accum;
		specs->locations[cdw_typespec] = loc;
	      }
	      اگر (!targetm.fixed_نقطہ_supported_p ())
		error_at (loc,
			  "fixed-point types not supported for this target");
	      pedwarn (loc, OPT_Wpedantic,
		       "ISO C does not support fixed-point types");
	      واپس specs;
	    حالت RID_BITINT:
	      اگر (specs->long_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "_BitInt");
	      ورنہ اگر (specs->short_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "_BitInt");
	      ورنہ اگر (specs->complex_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "_BitInt");
	      ورنہ اگر (specs->saturating_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "_BitInt");
	      ورنہ
		{
		  specs->typespec_لفظ = cts_bitint;
		  specs->locations[cdw_typespec] = loc;
		  specs->u.bitint_prec = -1;
		  اگر (error_عملیہ_p (spec.اظہاریہ))
		    واپس specs;
		  اگر (درخت_رمز (spec.اظہاریہ) != INTEGER_CST
		      || !INTEGRAL_TYPE_P (درخت_TYPE (spec.اظہاریہ)))
		    {
		      error_at (loc, "%<_BitInt%> argument is not an integer "
				     "constant expression");
		      واپس specs;
		    }
		  اگر (درخت_int_cst_sgn (spec.اظہاریہ) <= 0)
		    {
		      error_at (loc, "%<_BitInt%> argument %qE is not a "
				     "positive integer constant expression",
				spec.اظہاریہ);
		      واپس specs;
		    }
		  اگر (wi::مقصد_widest (spec.اظہاریہ) > WIDE_INT_MAX_PRECISION - 1)
		    {
		      error_at (loc, "%<_BitInt%> argument %qE is larger than "
				     "%<BITINT_MAXWIDTH%> %qd",
				spec.اظہاریہ, (صحیح) WIDE_INT_MAX_PRECISION - 1);
		      واپس specs;
		    }
		  specs->u.bitint_prec = درخت_مقصد_uhwi (spec.اظہاریہ);
		  ساخت bitint_info info;
		  اگر (!targetm.c.bitint_type_info (specs->u.bitint_prec,
						   &info))
		    {
		      sorry_at (loc, "%<_BitInt(%d)%> is not supported on "
				     "this target", specs->u.bitint_prec);
		      specs->u.bitint_prec = -1;
		      واپس specs;
		    }
		}
	      واپس specs;
	    طےشدہ:
	      /* ObjC reserved word "id", handled below.  */
	      توڑو;
	    }
	}
    }

  /* Now we have a typedef (a TYPE_DECL node), an identifier (some
     form of ObjC type, cases such as "int" and "long" being handled
     above), a TYPE (struct, union, enum and typeof specifiers) or an
     ERROR_MARK.  In none of these cases may there have previously
     been any type specifiers.  */
  اگر (specs->type || specs->typespec_لفظ != cts_none
      || specs->long_p || specs->short_p || specs->signed_p
      || specs->unsigned_p || specs->complex_p)
    error_at (loc, "two or more data types in declaration specifiers");
  ورنہ اگر (درخت_رمز (type) == TYPE_DECL)
    {
      specs->type = درخت_TYPE (type);
      اگر (درخت_TYPE (type) != error_mark_گرہ)
	{
	  mark_decl_مستعمل (type, جھوٹ);
	  specs->decl_attr = DECL_اوصاف (type);
	  specs->typedef_p = سچ;
	  specs->explicit_signed_p = C_TYPEDEF_EXPLICITLY_SIGNED (type);
	  specs->locations[cdw_typedef] = loc;

	  /* If this typedef name is defined in a struct, then a C++
	     lookup would return a different value.  */
	  اگر (warn_cxx_compat
	      && I_علامت_BINDING (DECL_NAME (type))->اندر_struct)
	    warning_at (loc, OPT_Wc___compat,
			"C++ lookup of %qD would return a field, not a type",
			type);

	  /* If we are parsing a struct, record that a struct field
	     used a typedef.  */
	  اگر (warn_cxx_compat && struct_parse_info != تہی)
	    struct_parse_info->typedefs_نظر_آیا.محفوظ_ڈالو (type);
	}
    }
  ورنہ اگر (درخت_رمز (type) == IDENTIFIER_گرہ)
    {
      درخت t = lookup_name (type);
      اگر (!t || درخت_رمز (t) != TYPE_DECL)
	error_at (loc, "%qE fails to be a typedef or built in type", type);
      ورنہ اگر (درخت_TYPE (t) == error_mark_گرہ)
	;
      ورنہ
	{
	  specs->type = درخت_TYPE (t);
	  specs->locations[cdw_typespec] = loc;
	}
    }
  ورنہ
    {
      اگر (درخت_رمز (type) != ERROR_MARK)
	{
	  اگر (spec.قسم == ctsk_typeof)
	    {
	      specs->typedef_p = سچ;
	      specs->locations[cdw_typedef] = loc;
	    }

	  اگر (درخت_رمز (type) == ریکارڈ_TYPE || درخت_رمز (type) == UNION_TYPE
	      || درخت_رمز (type) == ENUMERAL_TYPE)
	    mark_decl_مستعمل (TYPE_STUB_DECL (type), جھوٹ);

	  اگر (spec.اظہاریہ)
	    {
	      درخت اظہاریہ = save_اظہاریہ (fold_convert (void_type_گرہ, spec.اظہاریہ));
	      اگر (specs->اظہاریہ)
		specs->اظہاریہ = build2 (COMPOUND_اظہاریہ, درخت_TYPE (اظہاریہ),
				      specs->اظہاریہ, اظہاریہ);
	      ورنہ
		specs->اظہاریہ = اظہاریہ;
	      specs->اظہاریہ_const_operands &= spec.اظہاریہ_const_operands;
	    }
	}
      specs->type = type;
      اگر (spec.has_enum_type_specifier
	  && spec.قسم != ctsk_tagdef)
	specs->enum_type_specifier_ref_p = سچ;
    }

  واپس specs;
}

/* Add the storage class specifier or function specifier SCSPEC to the
   declaration specifiers SPECS, returning SPECS.  */

ساخت c_declspecs *
declspecs_جوڑو_scspec (location_t loc,
		      ساخت c_declspecs *specs,
		      درخت scspec)
{
  شمار rid i;
  شمار c_storage_class n = csc_none;
  منطقی dupe = جھوٹ;
  specs->declspecs_نظر_آیا_p = سچ;
  specs->non_std_attrs_نظر_آیا_p = سچ;
  gcc_assert (درخت_رمز (scspec) == IDENTIFIER_گرہ
	      && C_IS_RESERVED_لفظ (scspec));
  i = C_RID_رمز (scspec);
  اگر (specs->non_sc_نظر_آیا_p)
    warning (OPT_Wold_style_declaration,
             "%qE is not at beginning of declaration", scspec);
  انتخاب (i)
    {
    حالت RID_INLINE:
      /* C99 permits duplicate inline.  Although of doubtful utility,
	 it seems simplest to permit it in gnu89 mode as well, as
	 there is also little utility in maintaining this as a
	 difference between gnu89 and C99 inline.  */
      dupe = جھوٹ;
      specs->inline_p = سچ;
      specs->locations[cdw_inline] = loc;
      توڑو;
    حالت RID_NORETURN:
      /* Duplicate _Noreturn is permitted.  */
      dupe = جھوٹ;
      specs->noreturn_p = سچ;
      specs->locations[cdw_noreturn] = loc;
      توڑو;
    حالت RID_THREAD:
      dupe = specs->thread_p;
      اگر (specs->storage_class == csc_auto)
	error ("%qE used with %<auto%>", scspec);
      ورنہ اگر (specs->storage_class == csc_رجسٹر)
	error ("%qE used with %<register%>", scspec);
      ورنہ اگر (specs->storage_class == csc_typedef)
	error ("%qE used with %<typedef%>", scspec);
      ورنہ اگر (specs->constexpr_p)
	error ("%qE used with %<constexpr%>", scspec);
      ورنہ
	{
	  specs->thread_p = سچ;
	  specs->thread_gnu_p = (strcmp (IDENTIFIER_اشارہ_گر (scspec),
					 "__thread") == 0);
	  /* A diagnostic is not required for the use of this
	     identifier in the implementation namespace; only diagnose
	     it for the C11 spelling because of existing code using
	     the other spelling.  */
	  اگر (!specs->thread_gnu_p)
	    {
	      اگر (flag_isoc99)
		pedwarn_c99 (loc, OPT_Wpedantic,
			     "ISO C99 does not support %qE", scspec);
	      ورنہ
		pedwarn_c99 (loc, OPT_Wpedantic,
			     "ISO C90 does not support %qE", scspec);
	    }
	  specs->locations[cdw_thread] = loc;
	}
      توڑو;
    حالت RID_AUTO:
      اگر (flag_isoc23
	  && specs->typespec_قسم == ctsk_none
	  && specs->storage_class != csc_typedef)
	{
	  /* "auto" potentially used for type deduction.  */
	  اگر (specs->c23_auto_p)
	    error ("duplicate %qE", scspec);
	  specs->c23_auto_p = سچ;
	  واپس specs;
	}
      n = csc_auto;
      /* auto may only be used with another storage class specifier,
	 such as constexpr, if the type is inferred.  */
      اگر (specs->constexpr_p)
	error ("%qE used with %<constexpr%>", scspec);
      توڑو;
    حالت RID_EXTERN:
      n = csc_extern;
      /* Diagnose "__thread extern".  */
      اگر (specs->thread_p && specs->thread_gnu_p)
	error ("%<__thread%> before %<extern%>");
      توڑو;
    حالت RID_رجسٹر:
      n = csc_رجسٹر;
      توڑو;
    حالت RID_STATIC:
      n = csc_static;
      /* Diagnose "__thread static".  */
      اگر (specs->thread_p && specs->thread_gnu_p)
	error ("%<__thread%> before %<static%>");
      توڑو;
    حالت RID_TYPEDEF:
      n = csc_typedef;
      اگر (specs->c23_auto_p)
	{
	  error ("%<typedef%> used with %<auto%>");
	  specs->c23_auto_p = جھوٹ;
	}
      توڑو;
    حالت RID_CONSTEXPR:
      dupe = specs->constexpr_p;
      اگر (specs->storage_class == csc_extern)
	error ("%qE used with %<extern%>", scspec);
      ورنہ اگر (specs->storage_class == csc_typedef)
	error ("%qE used with %<typedef%>", scspec);
      ورنہ اگر (specs->storage_class == csc_auto)
	/* auto may only be used with another storage class specifier,
	   such as constexpr, if the type is inferred.  */
	error ("%qE used with %<auto%>", scspec);
      ورنہ اگر (specs->thread_p)
	error ("%qE used with %qs", scspec,
	       specs->thread_gnu_p ? "__thread" : "_Thread_local");
      ورنہ
	specs->constexpr_p = سچ;
      توڑو;
    طےشدہ:
      gcc_unreachable ();
    }
  اگر (n != csc_none && n == specs->storage_class)
    dupe = سچ;
  اگر (dupe)
    {
      اگر (i == RID_THREAD)
	error ("duplicate %<_Thread_local%> or %<__thread%>");
      ورنہ
	error ("duplicate %qE", scspec);
    }
  اگر (n != csc_none)
    {
      اگر (specs->storage_class != csc_none && n != specs->storage_class)
	{
	  error ("multiple storage classes in declaration specifiers");
	}
      ورنہ
	{
	  specs->storage_class = n;
	  specs->locations[cdw_storage_class] = loc;
	  اگر (n != csc_extern && n != csc_static && specs->thread_p)
	    {
	      error ("%qs used with %qE",
		     specs->thread_gnu_p ? "__thread" : "_Thread_local",
		     scspec);
	      specs->thread_p = جھوٹ;
	    }
	  اگر (n != csc_auto && n != csc_رجسٹر && n != csc_static
	      && specs->constexpr_p)
	    {
	      error ("%<constexpr%> used with %qE", scspec);
	      specs->constexpr_p = جھوٹ;
	    }
	}
    }
  واپس specs;
}

/* Add the attributes ATTRS to the declaration specifiers SPECS,
   returning SPECS.  */

ساخت c_declspecs *
declspecs_جوڑو_attrs (location_t loc, ساخت c_declspecs *specs, درخت attrs)
{
  specs->attrs = chainon (attrs, specs->attrs);
  specs->locations[cdw_اوصاف] = loc;
  specs->declspecs_نظر_آیا_p = سچ;
  /* In the case of standard attributes at the start of the
     declaration, the caller will reset this.  */
  specs->non_std_attrs_نظر_آیا_p = سچ;
  واپس specs;
}

/* Add an _Alignas specifier (expression ALIGN, or type whose
   alignment is ALIGN) to the declaration specifiers SPECS, returning
   SPECS.  */
ساخت c_declspecs *
declspecs_جوڑو_alignas (location_t loc,
		       ساخت c_declspecs *specs, درخت align)
{
  specs->alignas_p = سچ;
  specs->locations[cdw_alignas] = loc;
  اگر (align == error_mark_گرہ)
    واپس specs;

  /* Only accept the alignment if it's valid and greater than
     the current one.  Zero is invalid but by C11 required to
     be silently ignored.  */
  صحیح align_log = check_user_alignment (align, جھوٹ, /* warn_zero = */جھوٹ);
  اگر (align_log > specs->align_log)
    specs->align_log = align_log;
  واپس specs;
}

/* Combine "long", "short", "signed", "unsigned" and "_Complex" type
   specifiers with any other type specifier to determine the resulting
   type.  This is where ISO C checks on complex types are made, since
   "_Complex long" is a prefix of the valid ISO C type "_Complex long
   double".  Also apply postfix standard attributes to modify the type.  */

ساخت c_declspecs *
اختتام_declspecs (ساخت c_declspecs *specs)
{
  /* If a type was specified as a whole, we have no modifiers and are
     done.  */
  اگر (specs->type != NULL_درخت)
    {
      gcc_assert (!specs->long_p && !specs->long_long_p && !specs->short_p
		  && !specs->signed_p && !specs->unsigned_p
		  && !specs->complex_p && !specs->c23_auto_p);

      /* Set a dummy type.  */
      اگر (درخت_رمز (specs->type) == ERROR_MARK)
        specs->type = integer_type_گرہ;
      جاؤ handle_postfix_attrs;
    }

  /* If none of "void", "_Bool", "char", "int", "float" or "double"
     has been specified, treat it as "int" unless "_Complex" is
     present and there are no other specifiers.  If we just have
     "_Complex", it is equivalent to "_Complex double", but e.g.
     "_Complex short" is equivalent to "_Complex short int".  */
  اگر (specs->typespec_لفظ == cts_none)
    {
      اگر (specs->saturating_p)
	{
	  error_at (specs->locations[cdw_saturating],
		    "%<_Sat%> is used without %<_Fract%> or %<_Accum%>");
	  اگر (!targetm.fixed_نقطہ_supported_p ())
	    error_at (specs->locations[cdw_saturating],
		      "fixed-point types not supported for this target");
	  specs->typespec_لفظ = cts_fract;
	}
      ورنہ اگر (specs->long_p || specs->short_p
	       || specs->signed_p || specs->unsigned_p)
	{
	  specs->typespec_لفظ = cts_int;
	}
      ورنہ اگر (specs->complex_p)
	{
	  specs->typespec_لفظ = cts_double;
	  pedwarn (specs->locations[cdw_complex], OPT_Wpedantic,
		   "ISO C does not support plain %<complex%> meaning "
		   "%<double complex%>");
	}
      ورنہ اگر (specs->c23_auto_p)
	{
	  /* Type to be filled in later, including applying postfix
	     attributes.  This warning only actually appears for
	     -Wc11-c23-compat in C23 mode; in older modes, there may
	     be a warning or pedwarn for implicit "int" instead, or
	     other errors for use of auto at file scope.  */
	  pedwarn_c11 (داخلہ_location, OPT_Wpedantic,
		       "ISO C does not support %<auto%> type deduction "
		       "before C23");
	  واپس specs;
	}
      ورنہ
	{
	  specs->typespec_لفظ = cts_int;
	  specs->default_int_p = سچ;
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
  انتخاب (specs->typespec_لفظ)
    {
    حالت cts_auto_type:
      gcc_assert (!specs->long_p && !specs->short_p
		  && !specs->signed_p && !specs->unsigned_p
		  && !specs->complex_p);
      /* Type to be filled in later.  */
      اگر (specs->postfix_attrs)
	error ("%<__auto_type%> followed by %<[[]]%> attributes");
      توڑو;
    حالت cts_void:
      gcc_assert (!specs->long_p && !specs->short_p
		  && !specs->signed_p && !specs->unsigned_p
		  && !specs->complex_p);
      specs->type = void_type_گرہ;
      توڑو;
    حالت cts_bool:
      gcc_assert (!specs->long_p && !specs->short_p
		  && !specs->signed_p && !specs->unsigned_p
		  && !specs->complex_p);
      specs->type = boolean_type_گرہ;
      توڑو;
    حالت cts_char:
      gcc_assert (!specs->long_p && !specs->short_p);
      gcc_assert (!(specs->signed_p && specs->unsigned_p));
      اگر (specs->signed_p)
	specs->type = signed_char_type_گرہ;
      ورنہ اگر (specs->unsigned_p)
	specs->type = unsigned_char_type_گرہ;
      ورنہ
	specs->type = char_type_گرہ;
      اگر (specs->complex_p)
	{
	  pedwarn (specs->locations[cdw_complex], OPT_Wpedantic,
		   "ISO C does not support complex integer types");
	  specs->type = build_complex_type (specs->type);
	}
      توڑو;
    حالت cts_int_n:
      gcc_assert (!specs->long_p && !specs->short_p && !specs->long_long_p);
      gcc_assert (!(specs->signed_p && specs->unsigned_p));
      اگر (! int_n_enabled_p[specs->u.int_n_idx])
	specs->type = integer_type_گرہ;
      ورنہ
	specs->type = (specs->unsigned_p
		       ? int_n_trees[specs->u.int_n_idx].unsigned_type
		       : int_n_trees[specs->u.int_n_idx].signed_type);
      اگر (specs->complex_p)
	{
	  pedwarn (specs->locations[cdw_complex], OPT_Wpedantic,
		   "ISO C does not support complex integer types");
	  specs->type = build_complex_type (specs->type);
	}
      توڑو;
    حالت cts_int:
      gcc_assert (!(specs->long_p && specs->short_p));
      gcc_assert (!(specs->signed_p && specs->unsigned_p));
      اگر (specs->long_long_p)
	specs->type = (specs->unsigned_p
		       ? long_long_unsigned_type_گرہ
		       : long_long_integer_type_گرہ);
      ورنہ اگر (specs->long_p)
	specs->type = (specs->unsigned_p
		       ? long_unsigned_type_گرہ
		       : long_integer_type_گرہ);
      ورنہ اگر (specs->short_p)
	specs->type = (specs->unsigned_p
		       ? short_unsigned_type_گرہ
		       : short_integer_type_گرہ);
      ورنہ
	specs->type = (specs->unsigned_p
		       ? unsigned_type_گرہ
		       : integer_type_گرہ);
      اگر (specs->complex_p)
	{
	  pedwarn (specs->locations[cdw_complex], OPT_Wpedantic,
		   "ISO C does not support complex integer types");
	  specs->type = build_complex_type (specs->type);
	}
      توڑو;
    حالت cts_float:
      gcc_assert (!specs->long_p && !specs->short_p
		  && !specs->signed_p && !specs->unsigned_p);
      specs->type = (specs->complex_p
		     ? complex_float_type_گرہ
		     : float_type_گرہ);
      توڑو;
    حالت cts_double:
      gcc_assert (!specs->long_long_p && !specs->short_p
		  && !specs->signed_p && !specs->unsigned_p);
      اگر (specs->long_p)
	{
	  specs->type = (specs->complex_p
			 ? complex_long_double_type_گرہ
			 : long_double_type_گرہ);
	}
      ورنہ
	{
	  specs->type = (specs->complex_p
			 ? complex_double_type_گرہ
			 : double_type_گرہ);
	}
      توڑو;
    حالت cts_floatn_nx:
      gcc_assert (!specs->long_p && !specs->short_p
		  && !specs->signed_p && !specs->unsigned_p);
      اگر (FLOATN_NX_TYPE_گرہ (specs->u.floatn_nx_idx) == NULL_درخت)
	specs->type = integer_type_گرہ;
      ورنہ اگر (specs->complex_p)
	specs->type = COMPLEX_FLOATN_NX_TYPE_گرہ (specs->u.floatn_nx_idx);
      ورنہ
	specs->type = FLOATN_NX_TYPE_گرہ (specs->u.floatn_nx_idx);
      توڑو;
    حالت cts_dfloat32:
    حالت cts_dfloat64:
    حالت cts_dfloat128:
    حالت cts_dfloat64x:
      gcc_assert (!specs->long_p && !specs->long_long_p && !specs->short_p
		  && !specs->signed_p && !specs->unsigned_p && !specs->complex_p);
      اگر (!targetm.decimal_float_supported_p ())
	specs->type = integer_type_گرہ;
      ورنہ اگر (specs->typespec_لفظ == cts_dfloat32)
	specs->type = dfloat32_type_گرہ;
      ورنہ اگر (specs->typespec_لفظ == cts_dfloat64)
	specs->type = dfloat64_type_گرہ;
      ورنہ اگر (specs->typespec_لفظ == cts_dfloat128)
	specs->type = dfloat128_type_گرہ;
      ورنہ
	specs->type = dfloat64x_type_گرہ;
      توڑو;
    حالت cts_fract:
      gcc_assert (!specs->complex_p);
      اگر (!targetm.fixed_نقطہ_supported_p ())
	specs->type = integer_type_گرہ;
      ورنہ اگر (specs->saturating_p)
	{
	  اگر (specs->long_long_p)
	    specs->type = specs->unsigned_p
			  ? sat_unsigned_long_long_fract_type_گرہ
			  : sat_long_long_fract_type_گرہ;
	  ورنہ اگر (specs->long_p)
	    specs->type = specs->unsigned_p
			  ? sat_unsigned_long_fract_type_گرہ
			  : sat_long_fract_type_گرہ;
	  ورنہ اگر (specs->short_p)
	    specs->type = specs->unsigned_p
			  ? sat_unsigned_short_fract_type_گرہ
			  : sat_short_fract_type_گرہ;
	  ورنہ
	    specs->type = specs->unsigned_p
			  ? sat_unsigned_fract_type_گرہ
			  : sat_fract_type_گرہ;
	}
      ورنہ
	{
	  اگر (specs->long_long_p)
	    specs->type = specs->unsigned_p
			  ? unsigned_long_long_fract_type_گرہ
			  : long_long_fract_type_گرہ;
	  ورنہ اگر (specs->long_p)
	    specs->type = specs->unsigned_p
			  ? unsigned_long_fract_type_گرہ
			  : long_fract_type_گرہ;
	  ورنہ اگر (specs->short_p)
	    specs->type = specs->unsigned_p
			  ? unsigned_short_fract_type_گرہ
			  : short_fract_type_گرہ;
	  ورنہ
	    specs->type = specs->unsigned_p
			  ? unsigned_fract_type_گرہ
			  : fract_type_گرہ;
	}
      توڑو;
    حالت cts_accum:
      gcc_assert (!specs->complex_p);
      اگر (!targetm.fixed_نقطہ_supported_p ())
	specs->type = integer_type_گرہ;
      ورنہ اگر (specs->saturating_p)
	{
	  اگر (specs->long_long_p)
	    specs->type = specs->unsigned_p
			  ? sat_unsigned_long_long_accum_type_گرہ
			  : sat_long_long_accum_type_گرہ;
	  ورنہ اگر (specs->long_p)
	    specs->type = specs->unsigned_p
			  ? sat_unsigned_long_accum_type_گرہ
			  : sat_long_accum_type_گرہ;
	  ورنہ اگر (specs->short_p)
	    specs->type = specs->unsigned_p
			  ? sat_unsigned_short_accum_type_گرہ
			  : sat_short_accum_type_گرہ;
	  ورنہ
	    specs->type = specs->unsigned_p
			  ? sat_unsigned_accum_type_گرہ
			  : sat_accum_type_گرہ;
	}
      ورنہ
	{
	  اگر (specs->long_long_p)
	    specs->type = specs->unsigned_p
			  ? unsigned_long_long_accum_type_گرہ
			  : long_long_accum_type_گرہ;
	  ورنہ اگر (specs->long_p)
	    specs->type = specs->unsigned_p
			  ? unsigned_long_accum_type_گرہ
			  : long_accum_type_گرہ;
	  ورنہ اگر (specs->short_p)
	    specs->type = specs->unsigned_p
			  ? unsigned_short_accum_type_گرہ
			  : short_accum_type_گرہ;
	  ورنہ
	    specs->type = specs->unsigned_p
			  ? unsigned_accum_type_گرہ
			  : accum_type_گرہ;
	}
      توڑو;
    حالت cts_bitint:
      gcc_assert (!specs->long_p && !specs->short_p
		  && !specs->complex_p);
      اگر (!specs->unsigned_p && specs->u.bitint_prec == 1 && !flag_isoc2y)
	{
	  error_at (specs->locations[cdw_typespec],
		    "%<signed _BitInt%> argument must be at least 2 "
		    "before C2Y");
	  specs->type = integer_type_گرہ;
	  توڑو;
	}
      اگر (specs->u.bitint_prec == -1)
	specs->type = integer_type_گرہ;
      ورنہ
	{
	  pedwarn_c11 (specs->locations[cdw_typespec], OPT_Wpedantic,
		       "ISO C does not support %<%s_BitInt(%d)%> before C23",
		       specs->unsigned_p ? "unsigned "
		       : specs->signed_p ? "signed " : "",
		       specs->u.bitint_prec);
	  specs->type = build_bitint_type (specs->u.bitint_prec,
					   specs->unsigned_p);
	}
      توڑو;
    طےشدہ:
      gcc_unreachable ();
    }
 handle_postfix_attrs:
  اگر (specs->type != تہی)
    {
      specs->postfix_attrs
	= c_warn_type_اوصاف (specs->type, specs->postfix_attrs);
      decl_اوصاف (&specs->type, specs->postfix_attrs, 0);
      specs->postfix_attrs = NULL_درخت;
    }

  واپس specs;
}

/* Perform final processing on one file scope's declarations (or the
   external scope's declarations), GLOBALS.  */

ساکن خالی
c_write_global_declarations_1 (درخت globals)
{
  درخت decl;
  منطقی reconsider;

  /* Process the decls in the order they were written.  */
  برائے (decl = globals; decl; decl = DECL_CHAIN (decl))
    {
      /* Check for used but undefined static functions using the C
	 standard's definition of "used", and set TREE_NO_WARNING so
	 that check_global_declaration doesn't repeat the check.  */
      اگر (درخت_رمز (decl) == FUNCTION_DECL
	  && DECL_INITIAL (decl) == NULL_درخت
	  && DECL_EXTERNAL (decl)
	  && !درخت_عوامی (decl)
	  && !warning_suppressed_p (decl, OPT_Wunused))
	{
	  اگر (C_DECL_مستعمل (decl))
	    {
	      اگر (pedwarn (داخلہ_location, 0, "%q+F used but never defined",
			   decl))
		suppress_warning (decl, OPT_Wunused);
	    }
	  /* For -Wunused-function warn about unused static prototypes.  */
	  ورنہ اگر (warn_غیر_مستعمل_function
		   && ! DECL_ARTIFICIAL (decl)
		   && warning (OPT_Wunused_function,
			       "%q+F declared %<static%> but never defined",
			       decl))
	    suppress_warning (decl, OPT_Wunused);
	}

      wrapup_global_declaration_1 (decl);
    }

  کرو
    {
      reconsider = جھوٹ;
      برائے (decl = globals; decl; decl = DECL_CHAIN (decl))
	reconsider |= wrapup_global_declaration_2 (decl);
    }
  جب (reconsider);
}

/* Preserve the external declarations scope across a garbage collect.  */
ساکن GTY(()) درخت ext_بلاک;

/* Collect all references relevant to SOURCE_FILE.  */

ساکن خالی
collect_all_refs (ثابت حرف *ماخذ_file)
{
  درخت t;
  غیرعلامتی i;

  FOR_EACH_VEC_ELT (*all_translation_units, i, t)
    collect_ada_nodes (بلاک_VARS (DECL_INITIAL (t)), ماخذ_file);

  collect_ada_nodes (بلاک_VARS (ext_بلاک), ماخذ_file);
}

/* Collect source file references at global level.  */

ساکن خالی
collect_ماخذ_refs (خالی)
{
  درخت t;
  درخت decls;
  درخت decl;
  غیرعلامتی i;

  FOR_EACH_VEC_ELT (*all_translation_units, i, t)
    {
      decls = DECL_INITIAL (t);
      برائے (decl = بلاک_VARS (decls); decl; decl = درخت_CHAIN (decl))
	اگر (!DECL_IS_UNDECLARED_BUILTIN (decl))
	  collect_ماخذ_ref (DECL_ماخذ_FILE (decl));
    }

  برائے (decl = بلاک_VARS (ext_بلاک); decl; decl = درخت_CHAIN (decl))
    اگر (!DECL_IS_UNDECLARED_BUILTIN (decl))
      collect_ماخذ_ref (DECL_ماخذ_FILE (decl));
}

/* Free attribute access data that are not needed by the middle end. */

ساکن خالی
free_attr_access_ڈیٹا ()
{
  ساخت cgraph_گرہ *n;

  /* Iterate over all functions declared in the translation unit.  */
  FOR_EACH_FUNCTION (n)
    {
      برائے (درخت parm = DECL_ARGUMENTS (n->decl); parm; parm = درخت_CHAIN (parm))
	اگر (درخت attrs = DECL_اوصاف (parm))
	  attr_access::free_lang_ڈیٹا (attrs);

      درخت fntype = درخت_TYPE (n->decl);
      اگر (!fntype || fntype == error_mark_گرہ)
	جاری;
      درخت attrs = TYPE_اوصاف (fntype);
      اگر (!attrs)
	جاری;

      attr_access::free_lang_ڈیٹا (attrs);
    }
}

/* Perform any final parser cleanups and generate initial debugging
   information.  */

خالی
c_parse_final_cleanups (خالی)
{
  درخت t;
  غیرعلامتی i;

  /* We don't want to do this if generating a PCH.  */
  اگر (pch_file)
    واپس;

  timevar_stop (TV_PHASE_PARSING);
  timevar_آغاز (TV_PHASE_DEFERRED);

  /* Do the Objective-C stuff.  This is where all the Objective-C
     module stuff gets generated (symtab, class/protocol/selector
     lists etc).  */
  اگر (c_dialect_objc ())
    objc_write_global_declarations ();

  /* Close the external scope.  */
  ext_بلاک = نکالو_scope ();
  external_scope = 0;
  gcc_assert (!current_scope);

  /* Handle -fdump-ada-spec[-slim]. */
  اگر (flag_dump_ada_spec || flag_dump_ada_spec_slim)
    {
      /* Build a table of files to generate specs for */
      collect_ماخذ_ref (main_داخلہ_filename);
      اگر (!flag_dump_ada_spec_slim)
	collect_ماخذ_refs ();

      dump_ada_specs (collect_all_refs, تہی);
    }

  /* Process all file scopes in this compilation, and the external_scope,
     through wrapup_global_declarations.  */
  FOR_EACH_VEC_ELT (*all_translation_units, i, t)
    c_write_global_declarations_1 (بلاک_VARS (DECL_INITIAL (t)));
  c_write_global_declarations_1 (بلاک_VARS (ext_بلاک));

  /* Call this to set cpp_implicit_aliases_done on all nodes.  This is
     important for function multiversioning aliases to get resolved.  */
  symtab->process_same_body_aliases ();

  اگر (!اندر_lto_p)
    free_attr_access_ڈیٹا ();

  timevar_stop (TV_PHASE_DEFERRED);
  timevar_آغاز (TV_PHASE_PARSING);

  ext_بلاک = تہی;
}

/* Register reserved keyword WORD as qualifier for address space AS.  */

خالی
c_رجسٹر_addr_space (ثابت حرف *لفظ, addr_space_t as)
{
  صحیح rid = RID_پہلا_ADDR_SPACE + as;
  درخت id;

  /* Address space qualifiers are only supported
     in C with GNU extensions enabled.  */
  اگر (c_dialect_objc () || flag_no_asm)
    واپس;

  id = get_identifier (لفظ);
  C_سیٹ_RID_رمز (id, rid);
  C_IS_RESERVED_لفظ (id) = 1;
  ridpointers [rid] = id;
}

/* Return identifier to look up for omp declare reduction.  */

درخت
c_omp_reduction_id (شمار درخت_رمز_2 reduction_رمز, درخت reduction_id)
{
  ثابت حرف *p = تہی;
  انتخاب (reduction_رمز)
    {
    حالت PLUS_اظہاریہ: p = "+"; توڑو;
    حالت MULT_اظہاریہ: p = "*"; توڑو;
    حالت MINUS_اظہاریہ: p = "-"; توڑو;
    حالت ثنائی_ہندسہ_AND_اظہاریہ: p = "&"; توڑو;
    حالت ثنائی_ہندسہ_XOR_اظہاریہ: p = "^"; توڑو;
    حالت ثنائی_ہندسہ_IOR_اظہاریہ: p = "|"; توڑو;
    حالت TRUTH_ANDIF_اظہاریہ: p = "&&"; توڑو;
    حالت TRUTH_ORIF_اظہاریہ: p = "||"; توڑو;
    حالت MIN_اظہاریہ: p = "min"; توڑو;
    حالت MAX_اظہاریہ: p = "max"; توڑو;
    طےشدہ:
      توڑو;
    }

  اگر (p == تہی)
    {
      اگر (درخت_رمز (reduction_id) != IDENTIFIER_گرہ)
	واپس error_mark_گرہ;
      p = IDENTIFIER_اشارہ_گر (reduction_id);
    }

  ثابت حرف سابقہ[] = "omp declare reduction ";
  سائز_t lenp = حجم (سابقہ);
  سائز_t len = لڑی_لمبائی (p);
  حرف *name = XALLOCAVEC (حرف, lenp + len);
  حافظہ_نقل (name, سابقہ, lenp - 1);
  حافظہ_نقل (name + lenp - 1, p, len + 1);
  واپس get_identifier (name);
}

/* Lookup REDUCTION_ID in the current scope, or create an artificial
   VAR_DECL, bind it into the current scope and return it.  */

درخت
c_omp_reduction_decl (درخت reduction_id)
{
  ساخت c_binding *b = I_علامت_BINDING (reduction_id);
  اگر (b != تہی && B_اندر_CURRENT_SCOPE (b))
    واپس b->decl;

  درخت decl = build_decl (BUILTINS_LOCATION, VAR_DECL,
			  reduction_id, integer_type_گرہ);
  DECL_ARTIFICIAL (decl) = 1;
  DECL_EXTERNAL (decl) = 1;
  درخت_STATIC (decl) = 1;
  درخت_عوامی (decl) = 0;
  bind (reduction_id, decl, current_scope, سچ, جھوٹ, BUILTINS_LOCATION);
  واپس decl;
}

/* Lookup REDUCTION_ID in the first scope where it has entry for TYPE.  */

درخت
c_omp_reduction_lookup (درخت reduction_id, درخت type)
{
  ساخت c_binding *b = I_علامت_BINDING (reduction_id);
  جب (b)
    {
      درخت t;
      برائے (t = DECL_INITIAL (b->decl); t; t = درخت_CHAIN (t))
	اگر (comptypes (درخت_PURPOSE (t), type))
	  واپس درخت_قدر (t);
      b = b->shadowed;
    }
  واپس error_mark_گرہ;
}

/* Helper function called via walk_tree, to diagnose invalid
   #pragma omp declare reduction combiners or initializers.  */

درخت
c_check_omp_declare_reduction_r (درخت *tp, صحیح *, خالی *ڈیٹا)
{
  درخت *vars = (درخت *) ڈیٹا;
  اگر (SSA_VAR_P (*tp)
      && !DECL_ARTIFICIAL (*tp)
      && *tp != vars[0]
      && *tp != vars[1])
    {
      location_t loc = DECL_ماخذ_LOCATION (vars[0]);
      اگر (strcmp (IDENTIFIER_اشارہ_گر (DECL_NAME (vars[0])), "omp_out") == 0)
	error_at (loc, "%<#pragma omp declare reduction%> combiner refers to "
		       "variable %qD which is not %<omp_out%> nor %<omp_in%>",
		  *tp);
      ورنہ
	error_at (loc, "%<#pragma omp declare reduction%> initializer refers "
		       "to variable %qD which is not %<omp_priv%> nor "
		       "%<omp_orig%>",
		  *tp);
      واپس *tp;
    }
  واپس NULL_درخت;
}

/* Return identifier to look up for omp declare mapper.  */

درخت
c_omp_mapper_id (درخت mapper_id)
{
  ثابت حرف *p = تہی;

  ثابت حرف سابقہ[] = "omp declare mapper ";

  اگر (mapper_id == NULL_درخت)
    p = "<default>";
  ورنہ اگر (درخت_رمز (mapper_id) == IDENTIFIER_گرہ)
    p = IDENTIFIER_اشارہ_گر (mapper_id);
  ورنہ
    واپس error_mark_گرہ;

  سائز_t lenp = حجم (سابقہ);
  سائز_t len = لڑی_لمبائی (p);
  حرف *name = XALLOCAVEC (حرف, lenp + len);
  حافظہ_نقل (name, سابقہ, lenp - 1);
  حافظہ_نقل (name + lenp - 1, p, len + 1);
  واپس get_identifier (name);
}

/* Lookup MAPPER_ID in the current scope, or create an artificial
   VAR_DECL, bind it into the current scope and return it.  */

درخت
c_omp_mapper_decl (درخت mapper_id)
{
  ساخت c_binding *b = I_علامت_BINDING (mapper_id);
  اگر (b != تہی && B_اندر_CURRENT_SCOPE (b))
    واپس b->decl;

  درخت decl = build_decl (BUILTINS_LOCATION, VAR_DECL,
			  mapper_id, integer_type_گرہ);
  DECL_ARTIFICIAL (decl) = 1;
  DECL_EXTERNAL (decl) = 1;
  درخت_STATIC (decl) = 1;
  درخت_عوامی (decl) = 0;
  bind (mapper_id, decl, current_scope, سچ, جھوٹ, BUILTINS_LOCATION);
  واپس decl;
}

/* Lookup MAPPER_ID in the first scope where it has entry for TYPE.  */

درخت
c_omp_mapper_lookup (درخت mapper_id, درخت type)
{
  اگر (!ریکارڈ_OR_UNION_TYPE_P (type))
    واپس NULL_درخت;

  mapper_id = c_omp_mapper_id (mapper_id);

  ساخت c_binding *b = I_علامت_BINDING (mapper_id);
  جب (b)
    {
      درخت t;
      برائے (t = DECL_INITIAL (b->decl); t; t = درخت_CHAIN (t))
	اگر (comptypes (درخت_PURPOSE (t), type))
	  واپس درخت_قدر (t);
      b = b->shadowed;
    }
  واپس NULL_درخت;
}

/* For C, we record a pointer to the mapper itself without wrapping it in an
   artificial function or similar.  So, just return it.  */

درخت
c_omp_نکالو_mapper_directive (درخت mapper)
{
  واپس mapper;
}

/* For now we can handle singleton OMP_ARRAY_SECTIONs with custom mappers, but
   nothing more complicated.  */

درخت
c_omp_map_array_section (location_t loc, درخت t)
{
  درخت کم = درخت_عملیہ (t, 1);
  درخت len = درخت_عملیہ (t, 2);

  اگر (len && integer_onep (len))
    {
      t = درخت_عملیہ (t, 0);

      اگر (!کم)
	کم = integer_zero_گرہ;

      t = build_array_ref (loc, t, کم);
    }

  واپس t;
}

/* Helper function for below function.  */

ساکن درخت
c_omp_جائزہ_mapper_bindings_r (درخت *tp, صحیح *walk_subtrees, خالی *ptr)
{
  درخت t = *tp;
  omp_mapper_list<درخت> *mlist = (omp_mapper_list<درخت> *) ptr;
  درخت aggr_type = NULL_درخت;

  اگر (درخت_رمز (t) == SIZEOF_اظہاریہ
      || درخت_رمز (t) == ALIGNOF_اظہاریہ)
    {
      *walk_subtrees = 0;
      واپس NULL_درخت;
    }

  اگر (درخت_رمز (t) == OMP_CLAUSE)
    واپس NULL_درخت;

  اگر (درخت_رمز (t) == COMPONENT_REF
      && ریکارڈ_OR_UNION_TYPE_P (درخت_TYPE (درخت_عملیہ (t, 0))))
    aggr_type = درخت_TYPE (درخت_عملیہ (t, 0));
  ورنہ اگر ((درخت_رمز (t) == VAR_DECL
	    || درخت_رمز (t) == PARM_DECL
	    || درخت_رمز (t) == نتیجہ_DECL)
	   && ریکارڈ_OR_UNION_TYPE_P (درخت_TYPE (t)))
    aggr_type = درخت_TYPE (t);

  اگر (aggr_type)
    {
      درخت mapper_fn = c_omp_mapper_lookup (NULL_درخت, aggr_type);
      اگر (mapper_fn)
	mlist->جوڑو_mapper (NULL_درخت, aggr_type, mapper_fn);
    }

  واپس NULL_درخت;
}

/* Scan an offload region's body, and record uses of struct- or union-typed
   variables.  Add _mapper_binding_ fake clauses to *CLAUSES_PTR.  */

خالی
c_omp_جائزہ_mapper_bindings (location_t loc, درخت *clauses_ptr, درخت body)
{
  hash_سیٹ<omp_name_type<درخت>> نظر_آیا_types;
  auto_vec<درخت> mappers;
  omp_mapper_list<درخت> mlist (&نظر_آیا_types, &mappers);

  walk_درخت_without_duplicates (&body, c_omp_جائزہ_mapper_bindings_r, &mlist);

  غیرعلامتی صحیح i;
  درخت mapper;
  FOR_EACH_VEC_ELT (mappers, i, mapper)
    c_omp_ڈھونڈو_nested_mappers (&mlist, mapper);

  FOR_EACH_VEC_ELT (mappers, i, mapper)
    {
      اگر (mapper == error_mark_گرہ)
	جاری;
      درخت mapper_name = OMP_DECLARE_MAPPER_ID (mapper);
      درخت decl = OMP_DECLARE_MAPPER_DECL (mapper);

      درخت c = build_omp_clause (loc, OMP_CLAUSE__MAPPER_BINDING_);
      OMP_CLAUSE__MAPPER_BINDING__ID (c) = mapper_name;
      OMP_CLAUSE__MAPPER_BINDING__DECL (c) = decl;
      OMP_CLAUSE__MAPPER_BINDING__MAPPER (c) = mapper;

      OMP_CLAUSE_CHAIN (c) = *clauses_ptr;
      *clauses_ptr = c;
    }
}

منطقی
c_check_اندر_current_scope (درخت decl)
{
  ساخت c_binding *b = I_علامت_BINDING (DECL_NAME (decl));
  واپس b != تہی && B_اندر_CURRENT_SCOPE (b);
}

/* Search for loop or switch names.  BEFORE_LABELS is last statement before
   possible labels and SWITCH_P true for a switch, false for loops.
   Searches through last statements in cur_stmt_list, stops when seeing
   BEFORE_LABELs, or statement other than LABEL_EXPR or CASE_LABEL_EXPR.
   Returns number of loop/switch names found and if any are found, sets
   *LAST_P to the canonical loop/switch name LABEL_DECL.  */

صحیح
c_get_loop_نام (درخت before_labels, منطقی switch_p, درخت *آخری_p)
{
  *آخری_p = NULL_درخت;
  اگر (!building_stmt_list_p ()
      || !STATEMENT_LIST_HAS_LABEL (cur_stmt_list)
      || before_labels == void_list_گرہ)
    واپس 0;

  صحیح ret = 0;
  درخت آخری = NULL_درخت;
  برائے (درخت_stmt_iterator tsi = tsi_آخری (cur_stmt_list);
       !tsi_انتہا_p (tsi); tsi_پچھلا (&tsi))
    {
      درخت stmt = tsi_stmt (tsi);
      اگر (stmt == before_labels)
	توڑو;
      ورنہ اگر (درخت_رمز (stmt) == LABEL_اظہاریہ)
	{
	  اگر (آخری == NULL_درخت)
	    آخری = LABEL_اظہاریہ_LABEL (stmt);
	  ورنہ
	    {
	      loop_نام.محفوظ_ڈالو (LABEL_اظہاریہ_LABEL (stmt));
	      ++ret;
	    }
	}
      ورنہ اگر (درخت_رمز (stmt) != CASE_LABEL_اظہاریہ
	       && درخت_رمز (stmt) != DEBUG_BEGIN_STMT)
	توڑو;
    }
  اگر (آخری)
    {
      اگر (switch_p)
	C_DECL_SWITCH_NAME (آخری) = 1;
      ورنہ
	C_DECL_LOOP_NAME (آخری) = 1;
      loop_نام.محفوظ_ڈالو (آخری);
      ++ret;
      اگر (loop_نام.لمبائی () > 16)
	{
	  غیرعلامتی صحیح پہلا = 0, i;
	  درخت l, c = NULL_درخت;
	  اگر (loop_نام_hash == تہی)
	    loop_نام_hash = نیا decl_درخت_map (ret);
	  ورنہ
	    پہلا = loop_نام.لمبائی () - ret;
	  FOR_EACH_VEC_ELT_الٹ (loop_نام, i, l)
	    {
	      اگر (C_DECL_LOOP_NAME (l) || C_DECL_SWITCH_NAME (l))
		c = l;
	      gcc_checking_assert (c);
	      loop_نام_hash->put (l, c);
	      اگر (i == پہلا)
		توڑو;
	    }
	}
      *آخری_p = آخری;
    }
  واپس ret;
}

/* Undoes what get_loop_names did when it returned NUM_NAMES.  */

خالی
c_release_loop_نام (صحیح عدد_نام)
{
  غیرعلامتی len = loop_نام.لمبائی () - عدد_نام;
  اگر (loop_نام_hash)
    {
      اگر (len <= 16)
	{
	  حذف loop_نام_hash;
	  loop_نام_hash = تہی;
	}
      ورنہ
	{
	  غیرعلامتی صحیح i;
	  درخت l;
	  FOR_EACH_VEC_ELT_الٹ (loop_نام, i, l)
	    {
	      loop_نام_hash->remove (l);
	      اگر (i == len)
		توڑو;
	    }
	}
    }
  loop_نام.truncate (len);
}

/* Finish processing of break or continue identifier operand.
   NAME is the identifier operand of break or continue and
   IS_BREAK is true iff it is break stmt.  Returns the operand
   to use for BREAK_STMT or CONTINUE_STMT, either NULL_TREE or
   canonical loop/switch name LABEL_DECL.  */

درخت
c_اختتام_bc_name (location_t loc, درخت name, منطقی is_break)
{
  درخت label = NULL_درخت, lab;
  pedwarn_c23 (loc, OPT_Wpedantic,
	       "ISO C does not support %qs statement with an identifier "
	       "operand before C2Y", is_break ? "break" : "continue");

  /* If I_LABEL_DECL is NULL or not from current function, don't waste time
     trying to find it among loop_names, it can't be there.  */
  اگر (!loop_نام.is_خالی_خانے ()
      && current_function_scope
      && (lab = I_LABEL_DECL (name))
      && DECL_CONTEXT (lab) == current_function_decl)
    {
      غیرعلامتی صحیح i;
      درخت l, c = NULL_درخت;
      اگر (loop_نام_hash)
	{
	  اگر (درخت *val = loop_نام_hash->get (lab))
	    label = *val;
	}
      ورنہ
	FOR_EACH_VEC_ELT_الٹ (loop_نام, i, l)
	  {
	    اگر (C_DECL_LOOP_NAME (l) || C_DECL_SWITCH_NAME (l))
	      c = l;
	    gcc_checking_assert (c);
	    اگر (l == lab)
	      {
		label = c;
		توڑو;
	      }
	  }
      اگر (label)
	درخت_مستعمل (lab) = 1;
    }
  اگر (label == NULL_درخت)
    {
      auto_vec<ثابت حرف *> candidates;
      غیرعلامتی صحیح i;
      درخت l, c = NULL_درخت;
      FOR_EACH_VEC_ELT_الٹ (loop_نام, i, l)
	{
	  اگر (C_DECL_LOOP_NAME (l) || C_DECL_SWITCH_NAME (l))
	    c = l;
	  gcc_checking_assert (c);
	  اگر (is_break || C_DECL_LOOP_NAME (c))
	    candidates.محفوظ_ڈالو (IDENTIFIER_اشارہ_گر (DECL_NAME (l)));
	}
      ثابت حرف *hint = ڈھونڈو_closest_string (IDENTIFIER_اشارہ_گر (name),
					      &candidates);
      اگر (hint)
	{
	  gcc_rich_location richloc (loc);
	  richloc.جوڑو_fixit_replace (hint);
	  اگر (is_break)
	    error_at (&richloc, "%<break%> statement operand %qE does not "
				"refer to a named loop or %<switch%>; "
				"did you mean %qs?", name, hint);
	  ورنہ
	    error_at (&richloc, "%<continue%> statement operand %qE does not "
				"refer to a named loop; did you mean %qs?",
		      name, hint);
	}
      ورنہ اگر (is_break)
	error_at (loc, "%<break%> statement operand %qE does not refer to a "
		       "named loop or %<switch%>", name);
      ورنہ
	error_at (loc, "%<continue%> statement operand %qE does not refer to "
		       "a named loop", name);
    }
  ورنہ اگر (!C_DECL_LOOP_NAME (label) && !is_break)
    {
      auto_diagnostic_گروہ d;
      error_at (loc, "%<continue%> statement operand %qE refers to a named "
		     "%<switch%>", name);
      inform (DECL_ماخذ_LOCATION (label), "%<switch%> name defined here");
      label = NULL_درخت;
    }
  ورنہ اگر (!C_DECL_LOOP_SWITCH_NAME_VALID (label))
    {
      auto_diagnostic_گروہ d;
      اگر (C_DECL_LOOP_NAME (label))
	{
	  error_at (loc, "%qs statement operand %qE refers to a loop outside "
			 "of its body", is_break ? "break" : "continue", name);
	  inform (DECL_ماخذ_LOCATION (label), "loop name defined here");
	}
      ورنہ
	{
	  error_at (loc, "%<break%> statement operand %qE refers to a "
			 "%<switch%> outside of its body", name);
	  inform (DECL_ماخذ_LOCATION (label),
		  "%<switch%> name defined here");
	}
      label = NULL_درخت;
    }
  ورنہ اگر (label == loop_نام.آخری () && (اندر_statement & اندر_NAMED_STMT) != 0)
    /* If it is just a fancy reference to the innermost construct, handle it
       just like break; or continue; though tracking cheaply what is the
       innermost loop for continue when nested in switches would require
       another global variable and updating it.  */
    label = NULL_درخت;
  ورنہ
    C_DECL_LOOP_SWITCH_NAME_مستعمل (label) = 1;
  واپس label;
}

#شامل "gt-c-c-decl.h"
