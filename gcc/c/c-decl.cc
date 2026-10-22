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

#ضمن "config.h"
#وصف_ڪريو INCLUDE_STRING
#ضمن "system.h"
#ضمن "coretypes.h"
#ضمن "target.h"
#ضمن "function.h"
#ضمن "c-tree.h"
#ضمن "timevar.h"
#ضمن "stringpool.h"
#ضمن "cgraph.h"
#ضمن "intl.h"
#ضمن "print-tree.h"
#ضمن "stor-layout.h"
#ضمن "varasm.h"
#ضمن "attribs.h"
#ضمن "toplev.h"
#ضمن "debug.h"
#ضمن "c-family/c-objc.h"
#ضمن "c-family/c-pragma.h"
#ضمن "c-family/c-ubsan.h"
#ضمن "c-lang.h"
#ضمن "langhooks.h"
#ضمن "tree-iterator.h"
#ضمن "dumpfile.h"
#ضمن "plugin.h"
#ضمن "c-family/c-ada-spec.h"
#ضمن "builtins.h"
#ضمن "spellcheck-tree.h"
#ضمن "gcc-rich-location.h"
#ضمن "asan.h"
#ضمن "c-family/name-hint.h"
#ضمن "c-family/known-headers.h"
#ضمن "c-family/c-spellcheck.h"
#ضمن "context.h"  /* For 'g'.  */
#ضمن "omp-general.h"
#ضمن "omp-offload.h"  /* For offload_vars.  */
#ضمن "c-parser.h"
#ضمن "gcc-urlifier.h"

#ضمن "tree-pretty-print.h"

/* In grokdeclarator, distinguish syntactic contexts of declarators.  */
تعداد decl_context
{ عام_2,			/* Ordinary declaration */
  FUNCDEF,			/* Function definition */
  PARM,				/* Declaration of parm before function body */
  ميدان,			/* Declaration inside struct or union */
  TYPENAME,			/* Typename (inside cast or sizeof)  */
  GENERIC_ASSOC };		/* Typename in generic association  */

/* States indicating how grokdeclarator() should handle declspecs marked
   with __attribute__((deprecated)) or __attribute__((unavailable)).
   An object declared as __attribute__((unavailable)) should suppress
   any reports of being declared  with unavailable or deprecated items.
   An object declared as __attribute__((deprecated)) should suppress
   warnings of uses of other deprecated items.  */

تعداد deprecated_حالتون {
  DEPRECATED_عام,
  DEPRECATED_SUPPRESS,
  UNAVAILABLE_DEPRECATED_SUPPRESS
};


/* Nonzero if we have seen an invalid cross reference
   to a struct, union, or enum, but not yet printed the message.  */
وڻ pending_invalid_xref;

/* File and line to appear in the eventual error message.  */
location_t pending_invalid_xref_location;

/* The file and line that the prototype came from if this is an
   old-style definition; used for diagnostics in
   store_parm_decls_oldstyle.  */

ساكن location_t current_function_prototype_locus;

/* Whether this prototype was built-in.  */

ساكن منطقي current_function_prototype_built_اندريون;

/* The argument type information of this prototype.  */

ساكن وڻ current_function_prototype_arg_types;

/* The argument information structure for the function currently being
   defined.  */

ساكن بنية c_arg_info *current_function_arg_info;

/* The obstack on which parser and related data structures, which are
   not live beyond their top-level declaration or definition, are
   allocated.  */
بنية obstack parser_obstack;

/* The current statement tree.  */

ساكن GTY(()) بنية stmt_وڻ_s c_stmt_وڻ;

/* Zero if we are not in an iteration or switch statement, otherwise
   a bitmask.  See bitmask definitions in c-tree.h.  */
بنانشان حرف اندريون_statement;

/* A list of decls to be made automatically visible in each file scope.  */
ساكن GTY(()) وڻ visible_builtins;

/* Set to 0 at beginning of a function definition, set to 1 if
   a return statement that specifies a return value is seen.  */

صحيح current_function_returns_قدر;

/* Set to 0 at beginning of a function definition, set to 1 if
   a return statement with no argument is seen.  */

صحيح current_function_returns_null;

/* Set to 0 at beginning of a function definition, set to 1 if
   a call to a noreturn function is seen.  */

صحيح current_function_returns_abnormally;

/* Set to nonzero by `grokdeclarator' for a function
   whose return type is defaulted, if warnings for this are desired.  */

ساكن صحيح warn_about_return_type;

/* Nonzero when the current toplevel function contains a declaration
   of a nested function which is never defined.  */

ساكن منطقي undef_nested_function;

/* Vector of implicit "omp declare target" attributes to be added into
   the attribute lists.  */
vec<c_omp_declare_هدف_attr, va_gc> *current_omp_declare_هدف_attribute;

/* Vector of
   #pragma omp begin assumes ... #pragma omp end assumes regions
   we are in.  */
vec<c_omp_begin_assumes_معلومات, va_gc> *current_omp_begin_assumes;

/* Vector of "omp begin/end declare variant" blocks we are in.  */
vec<c_omp_declare_variant_attr, va_gc> *current_omp_declare_variant_attribute;

/* Vector of loop names with C_DECL_LOOP_NAME or C_DECL_SWITCH_NAME marked
   LABEL_DECL as the last and canonical for each loop or switch.  */
ساكن vec<وڻ> loop_نالا;

/* Hash table mapping LABEL_DECLs to the canonical LABEL_DECLs if LOOP_NAMES
   vector becomes too long.  */
ساكن decl_وڻ_map *loop_نالا_hash;

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

بنية GTY((chain_ايندڙ ("%h.prev"))) c_binding {
  اتحاد GTY(()) {		/* first so GTY desc can use decl */
    وڻ GTY((ٽيگ ("0"))) type; /* the type in this scope */
    بنية c_label_vars * GTY((ٽيگ ("1"))) label; /* for warnings */
  } GTY((desc ("TREE_CODE (%0.decl) == LABEL_DECL"))) u;
  وڻ decl;			/* the decl bound */
  وڻ id;			/* the identifier it's bound to */
  بنية c_binding *prev;	/* the previous decl in this scope */
  بنية c_binding *shadowed;	/* the innermost decl shadowed by this one */
  بنانشان صحيح اونهائي : 28;      /* depth of this scope */
  منطقي invisible : 1;  /* normal lookup should ignore this binding */
  منطقي nested : 1;     /* do not set DECL_CONTEXT when popping */
  منطقي inner_comp : 1; /* incomplete array completed in inner scope */
  منطقي اندريون_struct : 1;	/* currently defined as struct field */
  location_t locus;		/* location for nested bindings */
};
#وصف_ڪريو B_اندريون_SCOPE(b1, b2) ((b1)->اونهائي == (b2)->اونهائي)
#وصف_ڪريو B_اندريون_CURRENT_SCOPE(b) ((b)->اونهائي == current_scope->اونهائي)
#وصف_ڪريو B_اندريون_FILE_SCOPE(b) ((b)->اونهائي == 1 /*file_scope->depth*/)
#وصف_ڪريو B_اندريون_EXTERNAL_SCOPE(b) ((b)->اونهائي == 0 /*external_scope->depth*/)

/* Each C symbol points to three linked lists of c_binding structures.
   These describe the values of the identifier in the three different
   namespaces defined by the language.  */

بنية GTY(()) lang_identifier {
  بنية c_common_identifier common_id;
  بنية c_binding *نشان_binding; /* vars, funcs, constants, typedefs */
  بنية c_binding *ٽيگ_binding;    /* struct/union/enum tags */
  بنية c_binding *label_binding;  /* labels */
};

/* Validate c-lang.cc's assumptions.  */
خارجي حرف C_SIZEOF_STRUCT_LANG_IDENTIFIER_isnt_accurate
[(حجم(بنية lang_identifier) == C_SIZEOF_STRUCT_LANG_IDENTIFIER) ? 1 : -1];

/* The binding oracle; see c-tree.h.  */
فراغ (*c_binding_oracle) (تعداد c_oracle_request, وڻ identifier);

/* This flag is set on an identifier if we have previously asked the
   binding oracle for this identifier's symbol binding.  */
#وصف_ڪريو I_نشان_CHECKED(ڳنڍ) \
  (وڻ_LANG_FLAG_4 (IDENTIFIER_ڳنڍ_CHECK (ڳنڍ)))

ساكن مضمن بنية c_binding* *
i_نشان_binding (وڻ ڳنڍ)
{
  بنية lang_identifier *lid
    = (بنية lang_identifier *) IDENTIFIER_ڳنڍ_CHECK (ڳنڍ);

  إذا (lid->نشان_binding == عدم
      && c_binding_oracle != عدم
      && !I_نشان_CHECKED (ڳنڍ))
    {
      /* Set the "checked" flag first, to avoid infinite recursion
	 when the binding oracle calls back into gcc.  */
      I_نشان_CHECKED (ڳنڍ) = 1;
      c_binding_oracle (C_ORACLE_نشان, ڳنڍ);
    }

  أرجع &lid->نشان_binding;
}

#وصف_ڪريو I_نشان_BINDING(ڳنڍ) (*i_نشان_binding (ڳنڍ))

#وصف_ڪريو I_نشان_DECL(ڳنڍ) \
 (I_نشان_BINDING(ڳنڍ) ? I_نشان_BINDING(ڳنڍ)->decl : 0)

/* This flag is set on an identifier if we have previously asked the
   binding oracle for this identifier's tag binding.  */
#وصف_ڪريو I_ٽيگ_CHECKED(ڳنڍ) \
  (وڻ_LANG_FLAG_5 (IDENTIFIER_ڳنڍ_CHECK (ڳنڍ)))

ساكن مضمن بنية c_binding **
i_ٽيگ_binding (وڻ ڳنڍ)
{
  بنية lang_identifier *lid
    = (بنية lang_identifier *) IDENTIFIER_ڳنڍ_CHECK (ڳنڍ);

  إذا (lid->ٽيگ_binding == عدم
      && c_binding_oracle != عدم
      && !I_ٽيگ_CHECKED (ڳنڍ))
    {
      /* Set the "checked" flag first, to avoid infinite recursion
	 when the binding oracle calls back into gcc.  */
      I_ٽيگ_CHECKED (ڳنڍ) = 1;
      c_binding_oracle (C_ORACLE_ٽيگ, ڳنڍ);
    }

  أرجع &lid->ٽيگ_binding;
}

#وصف_ڪريو I_ٽيگ_BINDING(ڳنڍ) (*i_ٽيگ_binding (ڳنڍ))

#وصف_ڪريو I_ٽيگ_DECL(ڳنڍ) \
 (I_ٽيگ_BINDING(ڳنڍ) ? I_ٽيگ_BINDING(ڳنڍ)->decl : 0)

/* This flag is set on an identifier if we have previously asked the
   binding oracle for this identifier's label binding.  */
#وصف_ڪريو I_LABEL_CHECKED(ڳنڍ) \
  (وڻ_LANG_FLAG_6 (IDENTIFIER_ڳنڍ_CHECK (ڳنڍ)))

ساكن مضمن بنية c_binding **
i_label_binding (وڻ ڳنڍ)
{
  بنية lang_identifier *lid
    = (بنية lang_identifier *) IDENTIFIER_ڳنڍ_CHECK (ڳنڍ);

  إذا (lid->label_binding == عدم
      && c_binding_oracle != عدم
      && !I_LABEL_CHECKED (ڳنڍ))
    {
      /* Set the "checked" flag first, to avoid infinite recursion
	 when the binding oracle calls back into gcc.  */
      I_LABEL_CHECKED (ڳنڍ) = 1;
      c_binding_oracle (C_ORACLE_LABEL, ڳنڍ);
    }

  أرجع &lid->label_binding;
}

#وصف_ڪريو I_LABEL_BINDING(ڳنڍ) (*i_label_binding (ڳنڍ))

#وصف_ڪريو I_LABEL_DECL(ڳنڍ) \
 (I_LABEL_BINDING(ڳنڍ) ? I_LABEL_BINDING(ڳنڍ)->decl : 0)

/* Used by C_TOKEN_VEC tree.  */
بنية GTY (()) c_وڻ_token_vec {
  بنية وڻ_بنياد بنياد;
  vec<c_token, va_gc> *ٽوڪن;
};

STATIC_ASSERT (حجم (c_وڻ_token_vec) == حجم (c_وڻ_token_vec_struct));
STATIC_ASSERT (offsetof (c_وڻ_token_vec, ٽوڪن)
	       == offsetof (c_وڻ_token_vec_struct, ٽوڪن));

/* The resulting tree type.  */

اتحاد GTY((desc ("TREE_CODE (&%h.generic) == IDENTIFIER_NODE + 2 * (TREE_CODE (&%h.generic) == C_TOKEN_VEC)"),
       chain_ايندڙ ("(union lang_tree_node *) c_tree_chain_next (&%h.generic)"))) lang_وڻ_ڳنڍ
 {
  اتحاد وڻ_ڳنڍ GTY ((ٽيگ ("0"),
			desc ("tree_node_structure (&%h)")))
    generic;
  بنية lang_identifier GTY ((ٽيگ ("1"))) identifier;
  بنية c_وڻ_token_vec GTY ((ٽيگ ("2"))) c_token_vec;
};

/* Langhook for tree_size.  */
سائيز_t
c_وڻ_سائيز (تعداد وڻ_ڪوڊ_2 ڪوڊ)
{
  gcc_checking_assert (ڪوڊ >= انگ_وڻ_CODES);
  بدل (ڪوڊ)
    {
    حالة C_TOKEN_VEC: أرجع حجم (c_وڻ_token_vec);
    افتراضي:
      بدل (وڻ_ڪوڊ_CLASS (ڪوڊ))
	{
	حالة tcc_declaration: أرجع حجم (وڻ_decl_non_common);
	حالة tcc_type: أرجع حجم (وڻ_type_non_common);
	افتراضي: gcc_unreachable ();
	}
    }
}

/* Track bindings and other things that matter for goto warnings.  For
   efficiency, we do not gather all the decls at the point of
   definition.  Instead, we point into the bindings structure.  As
   scopes are popped, we update these structures and gather the decls
   that matter at that time.  */

بنية GTY(()) c_spot_bindings {
  /* The currently open scope which holds bindings defined when the
     label was defined or the goto statement was found.  */
  بنية c_scope *scope;
  /* The bindings in the scope field which were defined at the point
     of the label or goto.  This lets us look at older or newer
     bindings in the scope, as appropriate.  */
  بنية c_binding *bindings_اندريون_scope;
  /* The number of statement expressions that have started since this
     label or goto statement was defined.  This is zero if we are at
     the same statement expression level.  It is positive if we are in
     a statement expression started since this spot.  It is negative
     if this spot was in a statement expression and we have left
     it.  */
  صحيح stmt_exprs;
  /* Whether we started in a statement expression but are no longer in
     it.  This is set to true if stmt_exprs ever goes negative.  */
  منطقي کاٻو_stmt_اظهار;
};

/* This structure is used to keep track of bindings seen when a goto
   statement is defined.  This is only used if we see the goto
   statement before we see the label.  */

بنية GTY(()) c_goto_bindings {
  /* The location of the goto statement.  */
  location_t loc;
  /* The bindings of the goto statement.  */
  بنية c_spot_bindings goto_bindings;
};

تعريفنوع بنية c_goto_bindings *c_goto_bindings_p;

/* The additional information we keep track of for a label binding.
   These fields are updated as scopes are popped.  */

بنية GTY(()) c_label_vars {
  /* The shadowed c_label_vars, when one label shadows another (which
     can only happen using a __label__ declaration).  */
  بنية c_label_vars *shadowed;
  /* The bindings when the label was defined.  */
  بنية c_spot_bindings label_bindings;
  /* A list of decls that we care about: decls about which we should
     warn if a goto branches to this label from later in the function.
     Decls are added to this list as scopes are popped.  We only add
     the decls that matter.  */
  vec<وڻ, va_gc> *decls_اندريون_scope;
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


بنية GTY((chain_ايندڙ ("%h.outer"))) c_scope {
  /* The scope containing this one.  */
  بنية c_scope *outer;

  /* The next outermost function scope.  */
  بنية c_scope *outer_function;

  /* All bindings in this scope.  */
  بنية c_binding *bindings;

  /* For each scope (except the global one), a chain of BLOCK nodes
     for all the scopes that were entered and exited one level down.  */
  وڻ بلاڪون;
  وڻ بلاڪون_آخري;

  /* The depth of this scope.  Used to keep the ->shadowed chain of
     bindings sorted innermost to outermost.  */
  بنانشان صحيح اونهائي : 28;

  /* True if we are currently filling this scope with parameter
     declarations.  */
  منطقي parm_flag : 1;

  /* True if we saw [*] in this scope.  Used to give an error messages
     if these appears in a function definition.  */
  منطقي had_vla_unspec : 1;

  /* True if we parsed a list of forward parameter decls in this scope.  */
  منطقي had_forward_parm_decls : 1;

  /* True if this is the outermost block scope of a function body.
     This scope contains the parameters, the local variables declared
     in the outermost block, and all the labels (except those in
     nested functions, or declared at block scope with __label__).  */
  منطقي function_body : 1;

  /* True means make a BLOCK for this scope no matter what.  */
  منطقي keep : 1;

  /* True means that an unsuffixed float constant is _Decimal64.  */
  منطقي float_const_decimal64 : 1;

  /* True if this scope has any label bindings.  This is used to speed
     up searching for labels when popping scopes, particularly since
     labels are normally only found at function scope.  */
  منطقي has_label_bindings : 1;

  /* True if we should issue a warning if a goto statement crosses any
     of the bindings.  We still need to check the list of bindings to
     find the specific ones we need to warn about.  This is true if
     decl_jump_unsafe would return true for any of the bindings.  This
     is used to avoid looping over all the bindings unnecessarily.  */
  منطقي has_jump_unsafe_decl : 1;
};

/* The scope currently in effect.  */

ساكن GTY(()) بنية c_scope *current_scope;

/* The innermost function scope.  Ordinary (not explicitly declared)
   labels, bindings to error_mark_node, and the lazily-created
   bindings of __func__ and its friends get this scope.  */

ساكن GTY(()) بنية c_scope *current_function_scope;

/* The C file scope.  This is reset for each input translation unit.  */

ساكن GTY(()) بنية c_scope *file_scope;

/* The outermost scope.  This is used for all declarations with
   external linkage, and only these, hence the name.  */

ساكن GTY(()) بنية c_scope *external_scope;

/* A chain of c_scope structures awaiting reuse.  */

ساكن GTY((deletable)) بنية c_scope *scope_freelist;

/* A chain of c_binding structures awaiting reuse.  */

ساكن GTY((deletable)) بنية c_binding *binding_freelist;

/* Append VAR to LIST in scope SCOPE.  */
#وصف_ڪريو SCOPE_LIST_APPEND(scope, list, decl) افعل {	\
  بنية c_scope *s_ = (scope);				\
  وڻ d_ = (decl);					\
  إذا (s_->list##_last)					\
    بلاڪ_CHAIN (s_->list##_last) = d_;			\
  وإلا							\
    s_->list = d_;					\
  s_->list##_last = d_;					\
} طالما (0)

/* Concatenate FROM in scope FSCOPE onto TO in scope TSCOPE.  */
#وصف_ڪريو SCOPE_LIST_CONCAT(tscope, منزل, fscope, from) افعل {	\
  بنية c_scope *t_ = (tscope);				\
  بنية c_scope *f_ = (fscope);				\
  إذا (t_->منزل##_last)						\
    بلاڪ_CHAIN (t_->منزل##_last) = f_->from;			\
  وإلا								\
    t_->منزل = f_->from;						\
  t_->منزل##_last = f_->from##_last;				\
} طالما (0)

/* A c_inline_static structure stores details of a static identifier
   referenced in a definition of a function that may be an inline
   definition if no subsequent declaration of that function uses
   "extern" or does not use "inline".  */

بنية GTY((chain_ايندڙ ("%h.next"))) c_inline_static {
  /* The location for a diagnostic.  */
  location_t location;

  /* The function that may be an inline definition.  */
  وڻ function;

  /* The object or function referenced.  */
  وڻ static_decl;

  /* What sort of reference this is.  */
  تعداد c_inline_static_type type;

  /* The next such structure or NULL.  */
  بنية c_inline_static *ايندڙ;
};

/* List of static identifiers used or referenced in functions that may
   be inline definitions.  */
ساكن GTY(()) بنية c_inline_static *c_inline_statics;

/* True means unconditionally make a BLOCK for the next scope pushed.  */

ساكن منطقي keep_ايندڙ_level_flag;

/* True means the next call to push_scope will be the outermost scope
   of a function body, so do not push a new scope, merely cease
   expecting parameter decls.  */

ساكن منطقي ايندڙ_is_function_body;

/* A vector of pointers to c_binding structures.  */

تعريفنوع بنية c_binding *c_binding_ptr;

/* Information that we keep for a struct or union while it is being
   parsed.  */

صنف c_struct_parse_info
{
عام:
  /* If warn_cxx_compat, a list of types defined within this
     struct.  */
  auto_vec<وڻ> struct_types;
  /* If warn_cxx_compat, a list of field names which have bindings,
     and which are defined in this struct, but which are not defined
     in any enclosing struct.  This is used to clear the in_struct
     field of the c_bindings structure.  */
  auto_vec<c_binding_ptr> fields;
  /* If warn_cxx_compat, a list of typedef names used when defining
     fields in this struct.  */
  auto_vec<وڻ> typedefs_ڏٺل;
  /* The location of a previous definition of this struct.  */
  location_t refloc;
};


/* Hash table for structs and unions.  */
بنية c_struct_hasher : ggc_ptr_hash<وڻ_ڳنڍ>
{
  ساكن hashval_t hash (وڻ t);
  ساكن منطقي equal (وڻ, وڻ);
};

/* Hash an RECORD OR UNION.  */
hashval_t
c_struct_hasher::hash (وڻ type)
{
  inchash::hash hstate;

  hstate.جوڙيو_int (وڻ_ڪوڊ (type));
  وڻ ٽيگ = c_type_ٽيگ (type);
  hstate.جوڙيو_object (ٽيگ);

  أرجع hstate.پڇاڙي ();
}

/* Compare two RECORD or UNION types.  */
منطقي
c_struct_hasher::equal (وڻ t1,  وڻ t2)
{
  أرجع comptypes_equiv_p (t1, t2);
}

/* All tagged typed so that TYPE_CANONICAL can be set correctly.  */
ساكن GTY (()) hash_جدول<c_struct_hasher> *c_struct_htab;

/* Information for the struct or union currently being parsed, or
   NULL if not parsing a struct or union.  */
ساكن صنف c_struct_parse_info *struct_parse_info;

/* Forward declarations.  */
ساكن وڻ lookup_name_اندريون_scope (وڻ, بنية c_scope *);
ساكن وڻ c_make_fname_decl (location_t, وڻ, صحيح);
ساكن وڻ grokdeclarator (ثابت بنية c_declarator *,
			    بنية c_declspecs *,
			    تعداد decl_context, منطقي, وڻ *, وڻ *, وڻ *,
			    منطقي *, تعداد deprecated_حالتون);
ساكن وڻ grokparms (بنية c_arg_info *, منطقي);
ساكن فراغ layout_array_type (وڻ);
ساكن ثابت حرف *سرو_for_builtin_fn (وڻ);

/* T is a statement.  Add it to the statement-tree.  This is the
   C/ObjC version--C++ has a slightly different version of this
   function.  */

وڻ
جوڙيو_stmt (وڻ t)
{
  تعداد وڻ_ڪوڊ_2 ڪوڊ = وڻ_ڪوڊ (t);

  إذا (CAN_HAVE_LOCATION_P (t) && ڪوڊ != LABEL_اظهار)
    {
      إذا (!اظهار_HAS_LOCATION (t))
	سيٽ_اظهار_LOCATION (t, داخلا_location);
    }

  /* Add T to the statement-tree.  Non-side-effect statements need to be
     recorded during statement expressions.  */
  إذا (!building_stmt_list_p ())
    ڌڪو_stmt_list ();

  إذا (ڪوڊ == LABEL_اظهار || ڪوڊ == CASE_LABEL_اظهار)
    STATEMENT_LIST_HAS_LABEL (cur_stmt_list) = 1;

  append_منزل_statement_list_force (t, &cur_stmt_list);

  أرجع t;
}





/* Return true if we will want to say something if a goto statement
   crosses DECL.  */

ساكن منطقي
decl_jump_unsafe (وڻ decl)
{
  إذا (error_عمليو_p (decl))
    أرجع خطأ;

  /* Don't warn for compound literals.  If a goto statement crosses
     their initialization, it should cross also all the places where
     the complit is used or where the complit address might be saved
     into some variable, so code after the label to which goto jumps
     should not be able to refer to the compound literal.  */
  إذا (VAR_P (decl) && C_DECL_COMPOUND_LITERAL_P (decl))
    أرجع خطأ;

  إذا (flag_openmp
      && VAR_P (decl)
      && lookup_attribute ("omp allocate", DECL_خاصيتون (decl)))
    أرجع سچ;

  /* Always warn about crossing variably modified types.  */
  إذا ((VAR_P (decl) || وڻ_ڪوڊ (decl) == TYPE_DECL)
      && c_type_variably_modified_p (وڻ_TYPE (decl)))
    أرجع سچ;

  /* Otherwise, only warn if -Wgoto-misses-init and this is an
     initialized automatic decl.  */
  إذا (warn_jump_ناڪاميون_init
      && VAR_P (decl)
      && !وڻ_STATIC (decl)
      && DECL_INITIAL (decl) != NULL_وڻ)
    أرجع سچ;

  أرجع خطأ;
}


فراغ
c_print_identifier (FILE *file, وڻ ڳنڍ, صحيح indent)
{
  فراغ (*save) (تعداد c_oracle_request, وڻ identifier);

  /* Temporarily hide any binding oracle.  Without this, calls to
     debug_tree from the debugger will end up calling into the oracle,
     making for a confusing debug session.  As the oracle isn't needed
     here for normal operation, it's simplest to suppress it.  */
  save = c_binding_oracle;
  c_binding_oracle = عدم;

  print_ڳنڍ (file, "symbol", I_نشان_DECL (ڳنڍ), indent + 4);
  print_ڳنڍ (file, "tag", I_ٽيگ_DECL (ڳنڍ), indent + 4);
  print_ڳنڍ (file, "label", I_LABEL_DECL (ڳنڍ), indent + 4);
  إذا (C_IS_RESERVED_لفظ (ڳنڍ) && C_RID_ڪوڊ (ڳنڍ) != RID_CXX_COMPAT_WARN)
    {
      وڻ rid = ridpointers[C_RID_ڪوڊ (ڳنڍ)];
      indent_منزل (file, indent + 4);
      fprintf (file, "rid " HOST_PTR_PRINTF " \"%s\"",
	       (فراغ *) rid, IDENTIFIER_اشارو (rid));
    }

  c_binding_oracle = save;
}

/* Establish that the scope contains declarations that are sensitive to
   jumps that cross a binding.  Together with decl_jump_unsafe, this is
   used to diagnose such jumps.  */
فراغ
c_mark_decl_jump_unsafe_اندريون_current_scope ()
{
  current_scope->has_jump_unsafe_decl = 1;
}

/* Establish a binding between NAME, an IDENTIFIER_NODE, and DECL,
   which may be any of several kinds of DECL or TYPE or error_mark_node,
   in the scope SCOPE.  */
ساكن فراغ
bind (وڻ name, وڻ decl, بنية c_scope *scope, منطقي invisible,
      منطقي nested, location_t locus)
{
  بنية c_binding *b, **هتي;

  إذا (binding_freelist)
    {
      b = binding_freelist;
      binding_freelist = b->prev;
    }
  وإلا
    b = ggc_alloc<c_binding> ();

  b->shadowed = 0;
  b->decl = decl;
  b->id = name;
  b->اونهائي = scope->اونهائي;
  b->invisible = invisible;
  b->nested = nested;
  b->inner_comp = 0;
  b->اندريون_struct = 0;
  b->locus = locus;

  b->u.type = عدم;

  b->prev = scope->bindings;
  scope->bindings = b;

  إذا (decl_jump_unsafe (decl))
    scope->has_jump_unsafe_decl = 1;

  إذا (!name)
    أرجع;

  بدل (وڻ_ڪوڊ (decl))
    {
    حالة LABEL_DECL:     هتي = &I_LABEL_BINDING (name);   اكسر;
    حالة ENUMERAL_TYPE:
    حالة UNION_TYPE:
    حالة رڪارڊ_TYPE:    هتي = &I_ٽيگ_BINDING (name);     اكسر;
    حالة VAR_DECL:
    حالة FUNCTION_DECL:
    حالة TYPE_DECL:
    حالة CONST_DECL:
    حالة PARM_DECL:
    حالة ERROR_MARK:     هتي = &I_نشان_BINDING (name);  اكسر;

    افتراضي:
      gcc_unreachable ();
    }

  /* Locate the appropriate place in the chain of shadowed decls
     to insert this binding.  Normally, scope == current_scope and
     this does nothing.  */
  طالما (*هتي && (*هتي)->اونهائي > scope->اونهائي)
    هتي = &(*هتي)->shadowed;

  b->shadowed = *هتي;
  *هتي = b;
}

/* Clear the binding structure B, stick it on the binding_freelist,
   and return the former value of b->prev.  This is used by pop_scope
   and get_parm_info to iterate destructively over all the bindings
   from a given scope.  */
ساكن بنية c_binding *
free_binding_and_advance (بنية c_binding *b)
{
  بنية c_binding *prev = b->prev;

  memset (b, 0, حجم (بنية c_binding));
  b->prev = binding_freelist;
  binding_freelist = b;

  أرجع prev;
}

/* Bind a label.  Like bind, but skip fields which aren't used for
   labels, and add the LABEL_VARS value.  */
ساكن فراغ
bind_label (وڻ name, وڻ label, بنية c_scope *scope,
	    بنية c_label_vars *label_vars)
{
  بنية c_binding *b;

  bind (name, label, scope, /*invisible=*/خطأ, /*nested=*/خطأ,
	UNKNOWN_LOCATION);

  scope->has_label_bindings = سچ;

  b = scope->bindings;
  gcc_assert (b->decl == label);
  label_vars->shadowed = b->u.label;
  b->u.label = label_vars;
}

/* Hook called at end of compilation to assume 1 elt
   for a file-scope tentative array defn that wasn't complete before.  */

فراغ
c_پڄاڻي_incomplete_decl (وڻ decl)
{
  إذا (VAR_P (decl))
    {
      وڻ type = وڻ_TYPE (decl);
      إذا (type != error_mark_ڳنڍ
	  && وڻ_ڪوڊ (type) == ARRAY_TYPE
	  && !DECL_EXTERNAL (decl)
	  && TYPE_DOMAIN (type) == NULL_وڻ)
	{
	  إذا (flag_isoc2y && !وڻ_عوامي (decl))
	    error_at (DECL_ذريعو_LOCATION (decl),
		      "array size missing in %q+D", decl);
	  وإلا
	    warning_at (DECL_ذريعو_LOCATION (decl),
			0, "array %q+D assumed to have one element", decl);

	  complete_array_type (&وڻ_TYPE (decl), NULL_وڻ, سچ);

	  relayout_decl (decl);
	}
    }
}

/* Record that inline function FUNC contains a reference (location
   LOC) to static DECL (file-scope or function-local according to
   TYPE).  */

فراغ
رڪارڊ_inline_static (location_t loc, وڻ func, وڻ decl,
		      تعداد c_inline_static_type type)
{
  c_inline_static *csi = ggc_alloc<c_inline_static> ();
  csi->location = loc;
  csi->function = func;
  csi->static_decl = decl;
  csi->type = type;
  csi->ايندڙ = c_inline_statics;
  c_inline_statics = csi;
}

/* Check for references to static declarations in inline functions at
   the end of the translation unit and diagnose them if the functions
   are still inline definitions.  */

ساكن فراغ
check_inline_statics (فراغ)
{
  بنية c_inline_static *csi;
  لكل (csi = c_inline_statics; csi; csi = csi->ايندڙ)
    {
      إذا (DECL_EXTERNAL (csi->function))
	بدل (csi->type)
	  {
	  حالة csi_اندروني:
	    pedwarn (csi->location, 0,
		     "%qD is static but used in inline function %qD "
		     "which is not static", csi->static_decl, csi->function);
	    اكسر;
	  حالة csi_modifiable:
	    pedwarn (csi->location, 0,
		     "%q+D is static but declared in inline function %qD "
		     "which is not static", csi->static_decl, csi->function);
	    اكسر;
	  افتراضي:
	    gcc_unreachable ();
	  }
    }
  c_inline_statics = عدم;
}

/* Fill in a c_spot_bindings structure.  If DEFINING is true, set it
   for the current state, otherwise set it to uninitialized.  */

ساكن فراغ
سيٽ_spot_bindings (بنية c_spot_bindings *p, منطقي defining)
{
  إذا (defining)
    {
      p->scope = current_scope;
      p->bindings_اندريون_scope = current_scope->bindings;
    }
  وإلا
    {
      p->scope = عدم;
      p->bindings_اندريون_scope = عدم;
    }
  p->stmt_exprs = 0;
  p->کاٻو_stmt_اظهار = خطأ;
}

/* Update spot bindings P as we pop out of SCOPE.  Return true if we
   should push decls for a label.  */

ساكن منطقي
update_spot_bindings (بنية c_scope *scope, بنية c_spot_bindings *p)
{
  إذا (p->scope != scope)
    {
      /* This label or goto is defined in some other scope, or it is a
	 label which is not yet defined.  There is nothing to
	 update.  */
      أرجع خطأ;
    }

  /* Adjust the spot bindings to refer to the bindings already defined
     in the enclosing scope.  */
  p->scope = scope->outer;
  p->bindings_اندريون_scope = p->scope->bindings;

  أرجع سچ;
}

/* The Objective-C front-end often needs to determine the current scope.  */

فراغ *
objc_get_current_scope (فراغ)
{
  أرجع current_scope;
}

/* The following function is used only by Objective-C.  It needs to live here
   because it accesses the innards of c_scope.  */

فراغ
objc_mark_locals_volatile (فراغ *enclosing_blk)
{
  بنية c_scope *scope;
  بنية c_binding *b;

  لكل (scope = current_scope;
       scope && scope != enclosing_blk;
       scope = scope->outer)
    {
      لكل (b = scope->bindings; b; b = b->prev)
	objc_volatilize_decl (b->decl);

      /* Do not climb up past the current function.  */
      إذا (scope->function_body)
	اكسر;
    }
}

/* Return true if we are in the global binding level.  */

منطقي
global_bindings_p (فراغ)
{
  أرجع current_scope == file_scope;
}

/* Return true if we're declaring parameters in an old-style function
   declaration.  */

منطقي
old_style_parameter_scope (فراغ)
{
  /* If processing parameters and there is no function statement list, we
   * have an old-style function declaration.  */
  أرجع (current_scope->parm_flag && !DECL_SAVED_وڻ (current_function_decl));
}

فراغ
keep_ايندڙ_level (فراغ)
{
  keep_ايندڙ_level_flag = سچ;
}

/* Set the flag for the FLOAT_CONST_DECIMAL64 pragma being ON.  */

فراغ
سيٽ_float_const_decimal64 (فراغ)
{
  current_scope->float_const_decimal64 = سچ;
}

/* Clear the flag for the FLOAT_CONST_DECIMAL64 pragma.  */

فراغ
clear_float_const_decimal64 (فراغ)
{
  current_scope->float_const_decimal64 = خطأ;
}

/* Return nonzero if an unsuffixed float constant is _Decimal64.  */

منطقي
float_const_decimal64_p (فراغ)
{
  أرجع current_scope->float_const_decimal64;
}

/* Identify this scope as currently being filled with parameters.  */

فراغ
declare_parm_level (فراغ)
{
  current_scope->parm_flag = سچ;
}

فراغ
ڌڪو_scope (فراغ)
{
  إذا (ايندڙ_is_function_body)
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
      current_scope->parm_flag         = خطأ;
      current_scope->function_body     = سچ;
      current_scope->keep              = سچ;
      current_scope->outer_function    = current_function_scope;
      current_function_scope           = current_scope;

      keep_ايندڙ_level_flag = خطأ;
      ايندڙ_is_function_body = خطأ;

      /* The FLOAT_CONST_DECIMAL64 pragma applies to nested scopes.  */
      إذا (current_scope->outer)
	current_scope->float_const_decimal64
	  = current_scope->outer->float_const_decimal64;
      وإلا
	current_scope->float_const_decimal64 = خطأ;
    }
  وإلا
    {
      بنية c_scope *scope;
      إذا (scope_freelist)
	{
	  scope = scope_freelist;
	  scope_freelist = scope->outer;
	}
      وإلا
	scope = ggc_cleared_alloc<c_scope> ();

      /* The FLOAT_CONST_DECIMAL64 pragma applies to nested scopes.  */
      إذا (current_scope)
	scope->float_const_decimal64 = current_scope->float_const_decimal64;
      وإلا
	scope->float_const_decimal64 = خطأ;

      scope->keep          = keep_ايندڙ_level_flag;
      scope->outer         = current_scope;
      scope->اونهائي	   = current_scope ? (current_scope->اونهائي + 1) : 0;

      /* Check for scope depth overflow.  Unlikely (2^28 == 268,435,456) but
	 possible.  */
      إذا (current_scope && scope->اونهائي == 0)
	{
	  scope->اونهائي--;
	  sorry ("GCC supports only %u nested scopes", scope->اونهائي);
	}

      current_scope        = scope;
      keep_ايندڙ_level_flag = خطأ;
    }
}

/* This is called when we are leaving SCOPE.  For each label defined
   in SCOPE, add any appropriate decls to its decls_in_scope fields.
   These are the decls whose initialization will be skipped by a goto
   later in the function.  */

ساكن فراغ
update_label_decls (بنية c_scope *scope)
{
  بنية c_scope *s;

  s = scope;
  طالما (s != عدم)
    {
      إذا (s->has_label_bindings)
	{
	  بنية c_binding *b;

	  لكل (b = s->bindings; b != عدم; b = b->prev)
	    {
	      بنية c_label_vars *label_vars;
	      بنية c_binding *b1;
	      منطقي hjud;
	      بنانشان صحيح ix;
	      بنية c_goto_bindings *g;

	      إذا (وڻ_ڪوڊ (b->decl) != LABEL_DECL)
		استمر;
	      label_vars = b->u.label;

	      b1 = label_vars->label_bindings.bindings_اندريون_scope;
	      إذا (label_vars->label_bindings.scope == عدم)
		hjud = خطأ;
	      وإلا
		hjud = label_vars->label_bindings.scope->has_jump_unsafe_decl;
	      إذا (update_spot_bindings (scope, &label_vars->label_bindings))
		{
		  /* This label is defined in this scope.  */
		  إذا (hjud)
		    {
		      لكل (; b1 != عدم; b1 = b1->prev)
			{
			  /* A goto from later in the function to this
			     label will never see the initialization
			     of B1, if any.  Save it to issue a
			     warning if needed.  */
			  إذا (decl_jump_unsafe (b1->decl))
			    vec_محفوظ_ڌڪو(label_vars->decls_اندريون_scope, b1->decl);
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
      إذا (s == current_function_scope)
	اكسر;

      s = s->outer;
    }
}

/* Exit a scope.  Restore the state of the identifier-decl mappings
   that were in effect when this scope was entered.  Return a BLOCK
   node containing all the DECLs in this scope that are of interest
   to debug info generation.  */

وڻ
ڪڍو_scope (فراغ)
{
  بنية c_scope *scope = current_scope;
  وڻ بلاڪ, context, p;
  بنية c_binding *b;

  منطقي functionbody = scope->function_body;
  منطقي keep = functionbody || scope->keep || scope->bindings;

  update_label_decls (scope);

  /* If appropriate, create a BLOCK to record the decls for the life
     of this function.  */
  بلاڪ = NULL_وڻ;
  إذا (keep)
    {
      بلاڪ = make_ڳنڍ (بلاڪ_2);
      بلاڪ_SUBBLOCKS (بلاڪ) = scope->بلاڪون;
      وڻ_استعمال_ٿيل (بلاڪ) = 1;

      /* In each subblock, record that this is its superior.  */
      لكل (p = scope->بلاڪون; p; p = بلاڪ_CHAIN (p))
	بلاڪ_SUPERCONTEXT (p) = بلاڪ;

      بلاڪ_VARS (بلاڪ) = NULL_وڻ;
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
  إذا (scope->function_body)
    context = current_function_decl;
  وإلا إذا (scope == file_scope)
    {
      وڻ file_decl
	= build_translation_unit_decl (get_identifier (main_داخلا_filename));
      context = file_decl;
      debug_hooks->رجسٽر_main_translation_unit (file_decl);
    }
  وإلا
    context = بلاڪ;

  /* Clear all bindings in this scope.  */
  لكل (b = scope->bindings; b; b = free_binding_and_advance (b))
    {
      p = b->decl;
      بدل (وڻ_ڪوڊ (p))
	{
	حالة LABEL_DECL:
	  /* Warnings for unused labels, errors for undefined labels.  */
	  إذا (وڻ_استعمال_ٿيل (p) && !DECL_INITIAL (p))
	    {
	      error ("label %q+D used but not defined", p);
	      DECL_INITIAL (p) = error_mark_ڳنڍ;
	    }
	  وإلا
	    warn_for_اڻ_استعمال_ٿيل_label (p);

	  /* Labels go in BLOCK_VARS.  */
	  DECL_CHAIN (p) = بلاڪ_VARS (بلاڪ);
	  بلاڪ_VARS (بلاڪ) = p;
	  gcc_assert (I_LABEL_BINDING (b->id) == b);
	  I_LABEL_BINDING (b->id) = b->shadowed;

	  /* Also pop back to the shadowed label_vars.  */
	  release_وڻ_ويڪٽر (b->u.label->decls_اندريون_scope);
	  b->u.label = b->u.label->shadowed;
	  اكسر;

	حالة ENUMERAL_TYPE:
	حالة UNION_TYPE:
	حالة رڪارڊ_TYPE:

	  /* Types may not have tag-names, in which case the type
	     appears in the bindings list with b->id NULL.  */
	  إذا (b->id)
	    {
	      gcc_assert (I_ٽيگ_BINDING (b->id) == b);
	      I_ٽيگ_BINDING (b->id) = b->shadowed;
	    }
	  اكسر;

	حالة FUNCTION_DECL:
	  /* Propagate TREE_ADDRESSABLE from nested functions to their
	     containing functions.  */
	  إذا (!وڻ_ASM_WRITTEN (p)
	      && DECL_INITIAL (p) != NULL_وڻ
	      && وڻ_ADDRESSABLE (p)
	      && DECL_ABSTRACT_ORIGIN (p) != NULL_وڻ
	      && DECL_ABSTRACT_ORIGIN (p) != p)
	    وڻ_ADDRESSABLE (DECL_ABSTRACT_ORIGIN (p)) = 1;
	  إذا (!وڻ_عوامي (p)
	      && !DECL_INITIAL (p)
	      && !b->nested
	      && scope != file_scope
	      && scope != external_scope)
	    {
	      error ("nested function %q+D declared but never defined", p);
	      undef_nested_function = سچ;
	    }
	  وإلا إذا (DECL_DECLARED_INLINE_P (p)
		   && وڻ_عوامي (p)
		   && !DECL_INITIAL (p))
	    {
	      /* C99 6.7.4p6: "a function with external linkage... declared
		 with an inline function specifier ... shall also be defined
		 in the same translation unit."  */
	      إذا (!flag_gnu89_inline
		  && !lookup_attribute ("gnu_inline", DECL_خاصيتون (p))
		  && scope == external_scope)
		pedwarn (داخلا_location, 0,
			 "inline function %q+D declared but never defined", p);
	      DECL_EXTERNAL (p) = 1;
	    }

	  اذهب common_نشان;

	حالة VAR_DECL:
	  /* Warnings for unused variables.  */
	  إذا ((!وڻ_استعمال_ٿيل (p) || !DECL_READ_P (p))
	      && !warning_suppressed_p (p, OPT_Wunused_but_سيٽ_variable)
	      && !DECL_اندريون_SYSTEM_سرو (p)
	      && DECL_NAME (p)
	      && !DECL_ARTIFICIAL (p)
	      && scope != file_scope
	      && scope != external_scope)
	    {
	      إذا (!وڻ_استعمال_ٿيل (p))
		{
		  warning (OPT_Wunused_variable, "unused variable %q+D", p);
		  suppress_warning (p, OPT_Wunused_variable);
		}
	      وإلا إذا (DECL_CONTEXT (p) == current_function_decl)
		warning_at (DECL_ذريعو_LOCATION (p),
			    OPT_Wunused_but_سيٽ_variable,
			    "variable %qD set but not used", p);
	    }

	  إذا (b->inner_comp)
	    {
	      error ("type of array %q+D completed incompatibly with"
		     " implicit initialization", p);
	    }

	  /* Fall through.  */
	حالة TYPE_DECL:
	حالة CONST_DECL:
	common_نشان:
	  /* All of these go in BLOCK_VARS, but only if this is the
	     binding in the home scope.  */
	  إذا (!b->nested)
	    {
	      DECL_CHAIN (p) = بلاڪ_VARS (بلاڪ);
	      بلاڪ_VARS (بلاڪ) = p;
	    }
	  وإلا إذا (VAR_OR_FUNCTION_DECL_P (p) && scope != file_scope)
	    {
	      /* For block local externs add a special
		 DECL_EXTERNAL decl for debug info generation.  */
	      وڻ extp = copy_ڳنڍ (p);

	      DECL_EXTERNAL (extp) = 1;
	      وڻ_STATIC (extp) = 0;
	      وڻ_عوامي (extp) = 1;
	      DECL_INITIAL (extp) = NULL_وڻ;
	      DECL_LANG_SPECIFIC (extp) = عدم;
	      DECL_CONTEXT (extp) = current_function_decl;
	      إذا (وڻ_ڪوڊ (p) == FUNCTION_DECL)
		{
		  DECL_نتيجو (extp) = NULL_وڻ;
		  DECL_SAVED_وڻ (extp) = NULL_وڻ;
		  DECL_STRUCT_FUNCTION (extp) = عدم;
		}
	      إذا (b->locus != UNKNOWN_LOCATION)
		DECL_ذريعو_LOCATION (extp) = b->locus;
	      DECL_CHAIN (extp) = بلاڪ_VARS (بلاڪ);
	      بلاڪ_VARS (بلاڪ) = extp;
	    }
	  /* If this is the file scope set DECL_CONTEXT of each decl to
	     the TRANSLATION_UNIT_DECL.  This makes same_translation_unit_p
	     work.  */
	  إذا (scope == file_scope)
	      DECL_CONTEXT (p) = context;

	  gcc_fallthrough ();
	  /* Parameters go in DECL_ARGUMENTS, not BLOCK_VARS, and have
	     already been put there by store_parm_decls.  Unused-
	     parameter warnings are handled by function.cc.
	     error_mark_node obviously does not go in BLOCK_VARS and
	     does not get unused-variable warnings.  */
	حالة PARM_DECL:
	حالة ERROR_MARK:
	  /* It is possible for a decl not to have a name.  We get
	     here with b->id NULL in this case.  */
	  إذا (b->id)
	    {
	      gcc_assert (I_نشان_BINDING (b->id) == b);
	      I_نشان_BINDING (b->id) = b->shadowed;
	      إذا (b->shadowed && b->shadowed->u.type)
		وڻ_TYPE (b->shadowed->decl) = b->shadowed->u.type;
	    }
	  اكسر;

	افتراضي:
	  gcc_unreachable ();
	}
    }


  /* Dispose of the block that we just made inside some higher level.  */
  إذا ((scope->function_body || scope == file_scope) && context)
    {
      DECL_INITIAL (context) = بلاڪ;
      بلاڪ_SUPERCONTEXT (بلاڪ) = context;
    }
  وإلا إذا (scope->outer)
    {
      إذا (بلاڪ)
	SCOPE_LIST_APPEND (scope->outer, بلاڪون, بلاڪ);
      /* If we did not make a block for the scope just exited, any
	 blocks made for inner scopes must be carried forward so they
	 will later become subblocks of something else.  */
      وإلا إذا (scope->بلاڪون)
	SCOPE_LIST_CONCAT (scope->outer, بلاڪون, scope, بلاڪون);
    }

  /* Pop the current scope, and free the structure for reuse.  */
  current_scope = scope->outer;
  إذا (scope->function_body)
    current_function_scope = scope->outer_function;

  memset (scope, 0, حجم (بنية c_scope));
  scope->outer = scope_freelist;
  scope_freelist = scope;

  أرجع بلاڪ;
}

فراغ
ڌڪو_file_scope (فراغ)
{
  وڻ decl;

  إذا (file_scope)
    أرجع;

  /* Call the target stack_protect_guard hook if the stack protection
     guard is declared as a global symbol.  */
  إذا (targetm.ڍير_protect_guard_نشان_p ())
    {
      وڻ decl = targetm.ڍير_protect_guard ();
      DECL_CHAIN (decl) = visible_builtins;
      visible_builtins = decl;
    }

  ڌڪو_scope ();
  file_scope = current_scope;

  شروعات_fname_decls ();

  لكل (decl = visible_builtins; decl; decl = DECL_CHAIN (decl))
    bind (DECL_NAME (decl), decl, file_scope,
	  /*invisible=*/خطأ, /*nested=*/سچ, DECL_ذريعو_LOCATION (decl));
}

فراغ
ڪڍو_file_scope (فراغ)
{
  /* In case there were missing closebraces, get us back to the global
     binding level.  */
  طالما (current_scope != file_scope)
    ڪڍو_scope ();

  /* __FUNCTION__ is defined at file scope ("").  This
     call may not be necessary as my tests indicate it
     still works without it.  */
  پڄاڻي_fname_decls ();

  check_inline_statics ();

  /* This is the point to write out a PCH if we're doing that.
     In that case we do not want to do anything else.  */
  إذا (pch_file)
    {
      c_common_write_pch ();
      /* Ensure even the callers don't try to finalize the CU.  */
      flag_syntax_only = 1;
      أرجع;
    }

  /* Pop off the file scope and close this translation unit.  */
  ڪڍو_scope ();
  file_scope = 0;

  maybe_apply_pending_pragma_weaks ();
}

/* Whether we are currently inside the initializer for an
   underspecified object definition (C23 auto or constexpr).  */
ساكن منطقي اندريون_underspecified_init;

/* Start an underspecified object definition for NAME at LOC.  This
   means that NAME is shadowed inside its initializer, so neither the
   definition being initialized, nor any definition from an outer
   scope, may be referenced during that initializer.  Return state to
   be passed to finish_underspecified_init.  If NAME is NULL_TREE, the
   underspecified object is a (constexpr) compound literal; there is
   no shadowing in that case, but all the other restrictions on
   underspecified object definitions still apply.  */
بنانشان صحيح
شروعات_underspecified_init (location_t loc, وڻ name)
{
  منطقي prev = اندريون_underspecified_init;
  منطقي ok;
  إذا (name == NULL_وڻ)
    ok = سچ;
  وإلا
    {
      وڻ decl = build_decl (loc, VAR_DECL, name, error_mark_ڳنڍ);
      C_DECL_UNDERSPECIFIED (decl) = 1;
      بنية c_scope *scope = current_scope;
      بنية c_binding *b = I_نشان_BINDING (name);
      إذا (b && B_اندريون_SCOPE (b, scope))
	{
	  error_at (loc, "underspecified declaration of %qE, which is already "
		    "declared in this scope", name);
	  ok = خطأ;
	}
      وإلا
	{
	  bind (name, decl, scope, خطأ, خطأ, loc);
	  ok = سچ;
	}
    }
  اندريون_underspecified_init = سچ;
  أرجع ok | (prev << 1);
}

/* Finish an underspecified object definition for NAME, before that
   name is bound to the real declaration instead of a placeholder.
   PREV_STATE is the value returned by the call to
   start_underspecified_init.  If NAME is NULL_TREE, this means a
   compound literal, as for start_underspecified_init.  */
فراغ
پڄاڻي_underspecified_init (وڻ name, بنانشان صحيح prev_state)
{
  إذا (name != NULL_وڻ && (prev_state & 1))
    {
      /* A VAR_DECL was bound to the name to shadow any previous
	 declarations for the name; remove that binding now.  */
      بنية c_scope *scope = current_scope;
      بنية c_binding *b = I_نشان_BINDING (name);
      gcc_assert (b);
      gcc_assert (B_اندريون_SCOPE (b, scope));
      gcc_assert (VAR_P (b->decl));
      gcc_assert (C_DECL_UNDERSPECIFIED (b->decl));
      I_نشان_BINDING (name) = b->shadowed;
      /* In erroneous cases there may be other bindings added to this
	 scope during the initializer.  */
      بنية c_binding **p = &scope->bindings;
      طالما (*p != b)
	p = &((*p)->prev);
      *p = free_binding_and_advance (*p);
    }
  اندريون_underspecified_init = (prev_state & (1u << 1)) >> 1;
}

/* Adjust the bindings for the start of a statement expression.  */

فراغ
c_bindings_شروعات_stmt_اظهار (بنية c_spot_bindings* switch_bindings)
{
  بنية c_scope *scope;

  لكل (scope = current_scope; scope != عدم; scope = scope->outer)
    {
      بنية c_binding *b;

      إذا (!scope->has_label_bindings)
	استمر;

      لكل (b = scope->bindings; b != عدم; b = b->prev)
	{
	  بنية c_label_vars *label_vars;
	  بنانشان صحيح ix;
	  بنية c_goto_bindings *g;

	  إذا (وڻ_ڪوڊ (b->decl) != LABEL_DECL)
	    استمر;
	  label_vars = b->u.label;
	  ++label_vars->label_bindings.stmt_exprs;
	  FOR_EACH_VEC_محفوظ_ELT (label_vars->gotos, ix, g)
	    ++g->goto_bindings.stmt_exprs;
	}
    }

  إذا (switch_bindings != عدم)
    ++switch_bindings->stmt_exprs;
}

/* Adjust the bindings for the end of a statement expression.  */

فراغ
c_bindings_پڇاڙي_stmt_اظهار (بنية c_spot_bindings *switch_bindings)
{
  بنية c_scope *scope;

  لكل (scope = current_scope; scope != عدم; scope = scope->outer)
    {
      بنية c_binding *b;

      إذا (!scope->has_label_bindings)
	استمر;

      لكل (b = scope->bindings; b != عدم; b = b->prev)
	{
	  بنية c_label_vars *label_vars;
	  بنانشان صحيح ix;
	  بنية c_goto_bindings *g;

	  إذا (وڻ_ڪوڊ (b->decl) != LABEL_DECL)
	    استمر;
	  label_vars = b->u.label;
	  --label_vars->label_bindings.stmt_exprs;
	  إذا (label_vars->label_bindings.stmt_exprs < 0)
	    {
	      label_vars->label_bindings.کاٻو_stmt_اظهار = سچ;
	      label_vars->label_bindings.stmt_exprs = 0;
	    }
	  FOR_EACH_VEC_محفوظ_ELT (label_vars->gotos, ix, g)
	    {
	      --g->goto_bindings.stmt_exprs;
	      إذا (g->goto_bindings.stmt_exprs < 0)
		{
		  g->goto_bindings.کاٻو_stmt_اظهار = سچ;
		  g->goto_bindings.stmt_exprs = 0;
		}
	    }
	}
    }

  إذا (switch_bindings != عدم)
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

ساكن فراغ
pushtag (location_t loc, وڻ name, وڻ type)
{
  /* Record the identifier as the type's name if it has none.  */
  إذا (name && !TYPE_NAME (type))
    TYPE_NAME (type) = name;
  bind (name, type, current_scope, /*invisible=*/خطأ, /*nested=*/خطأ, loc);

  /* Create a fake NULL-named TYPE_DECL node whose TREE_TYPE will be the
     tagged type we just added to the current scope.  This fake
     NULL-named TYPE_DECL node helps dwarfout.c to know when it needs
     to output a representation of a tagged type, and it also gives
     us a convenient place to record the "scope start" address for the
     tagged type, and it is used to track whether the type is used
     in a non-local context via mark_decl_used.  */

  TYPE_STUB_DECL (type) = pushdecl (build_decl (loc,
						TYPE_DECL, NULL_وڻ, type));

  /* An approximation for now, so we can tell this is a function-scope tag.
     This will be updated in pop_scope.  */
  TYPE_CONTEXT (type) = DECL_CONTEXT (TYPE_STUB_DECL (type));

  إذا (warn_cxx_compat && name != NULL_وڻ)
    {
      بنية c_binding *b = I_نشان_BINDING (name);

      إذا (b != عدم
	  && b->decl != NULL_وڻ
	  && وڻ_ڪوڊ (b->decl) == TYPE_DECL
	  && (B_اندريون_CURRENT_SCOPE (b)
	      || (current_scope == file_scope && B_اندريون_EXTERNAL_SCOPE (b)))
	  && (TYPE_MAIN_VARIANT (وڻ_TYPE (b->decl))
	      != TYPE_MAIN_VARIANT (type)))
	{
	  auto_diagnostic_گروهه d;
	  إذا (warning_at (loc, OPT_Wc___compat,
			  "using %qD as both a typedef and a tag is "
			  "invalid in C++", b->decl)
	      && b->locus != UNKNOWN_LOCATION)
	    inform (b->locus, "originally defined here");
	}
    }
}

/* An exported interface to pushtag.  This is used by the gdb plugin's
   binding oracle to introduce a new tag binding.  */

فراغ
c_pushtag (location_t loc, وڻ name, وڻ type)
{
  pushtag (loc, name, type);
}

/* An exported interface to bind a declaration.  LOC is the location
   to use.  DECL is the declaration to bind.  The decl's name is used
   to determine how it is bound.  If DECL is a VAR_DECL, then
   IS_GLOBAL determines whether the decl is put into the global (file
   and external) scope or the current function's scope; if DECL is not
   a VAR_DECL then it is always put into the file scope.  */

فراغ
c_bind (location_t loc, وڻ decl, منطقي is_global)
{
  بنية c_scope *scope;
  منطقي nested = خطأ;

  إذا (!VAR_P (decl) || current_function_scope == عدم)
    {
      /* Types and functions are always considered to be global.  */
      scope = file_scope;
      DECL_EXTERNAL (decl) = 1;
      وڻ_عوامي (decl) = 1;
    }
  وإلا إذا (is_global)
    {
      /* Also bind it into the external scope.  */
      bind (DECL_NAME (decl), decl, external_scope, سچ, خطأ, loc);
      nested = سچ;
      scope = file_scope;
      DECL_EXTERNAL (decl) = 1;
      وڻ_عوامي (decl) = 1;
    }
  وإلا
    {
      DECL_CONTEXT (decl) = current_function_decl;
      وڻ_عوامي (decl) = 0;
      scope = current_function_scope;
    }

  bind (DECL_NAME (decl), decl, scope, خطأ, nested, loc);
}


/* Stores the first FILE*, const struct tm* etc. argument type (whatever
   it is) seen in a declaration of a file I/O etc. built-in, corresponding
   to the builtin_structptr_types array.  Subsequent declarations of such
   built-ins are expected to refer to it rather than to fileptr_type_node,
   etc. which is just void* (or to any other type).
   Used only by match_builtin_function_types.  */

ساكن ثابت بنانشان builtin_structptr_type_ڳڻپ
  = ARRAY_سائيز (builtin_structptr_types);

ساكن GTY(()) وڻ آخري_structptr_types[builtin_structptr_type_ڳڻپ];

/* Returns true if types T1 and T2 representing return types or types
   of function arguments are close enough to be considered interchangeable
   in redeclarations of built-in functions.  */

ساكن منطقي
types_close_enough_منزل_ميلاپ (وڻ t1, وڻ t2)
{
  أرجع (TYPE_گهڻائي (t1) == TYPE_گهڻائي (t2)
	  && اشارو_TYPE_P (t1) == اشارو_TYPE_P (t2)
	  && FUNCTION_اشارو_TYPE_P (t1) == FUNCTION_اشارو_TYPE_P (t2));
}

/* Subroutine of compare_decls.  Allow harmless mismatches in return
   and argument types provided that the type modes match.  Set *STRICT
   and *ARGNO to the expected argument type and number in case of
   an argument type mismatch or null and zero otherwise.  Return
   a unified type given a suitable match, and 0 otherwise.  */

ساكن وڻ
ميلاپ_builtin_function_types (وڻ newtype, وڻ oldtype,
			      وڻ *strict, بنانشان *argno)
{
  *argno = 0;
  *strict = NULL_وڻ;

  /* Accept the return type of the new declaration if it has the same
     mode and if they're both pointers or if neither is.  */
  وڻ oldrettype = وڻ_TYPE (oldtype);
  وڻ newrettype = وڻ_TYPE (newtype);

  إذا (!types_close_enough_منزل_ميلاپ (oldrettype, newrettype))
    أرجع NULL_وڻ;

  /* Check that the return types are compatible but don't fail if they
     are not (e.g., int vs long in ILP32) and just let the caller know.  */
  إذا (!comptypes (TYPE_MAIN_VARIANT (oldrettype),
		  TYPE_MAIN_VARIANT (newrettype)))
    *strict = oldrettype;

  وڻ oldargs = TYPE_ARG_TYPES (oldtype);
  وڻ newargs = TYPE_ARG_TYPES (newtype);
  وڻ tryargs = newargs;

  ثابت بنانشان nlst = ARRAY_سائيز (آخري_structptr_types);
  ثابت بنانشان nbst = ARRAY_سائيز (builtin_structptr_types);

  gcc_checking_assert (nlst == nbst);

  لكل (بنانشان i = 1; oldargs || newargs; ++i)
    {
      إذا (!oldargs
	  || !newargs
	  || !وڻ_قدر (oldargs)
	  || !وڻ_قدر (newargs))
	أرجع NULL_وڻ;

      وڻ oldtype = TYPE_MAIN_VARIANT (وڻ_قدر (oldargs));
      وڻ newtype = وڻ_قدر (newargs);
      إذا (newtype == error_mark_ڳنڍ)
       أرجع NULL_وڻ;
      newtype = TYPE_MAIN_VARIANT (newtype);

      إذا (!types_close_enough_منزل_ميلاپ (oldtype, newtype))
	أرجع NULL_وڻ;

      بنانشان j = nbst;
      إذا (اشارو_TYPE_P (oldtype))
	/* Iterate over well-known struct types like FILE (whose types
	   aren't known to us) and compare the pointer to each to
	   the pointer argument.  */
	لكل (j = 0; j < nbst; ++j)
	  {
	    إذا (وڻ_قدر (oldargs) != builtin_structptr_types[j].ڳنڍ)
	      استمر;
	    /* Store the first FILE* etc. argument type (whatever it is), and
	       expect any subsequent declarations of file I/O etc. built-ins
	       to refer to it rather than to fileptr_type_node etc. which is
	       just void* (or const void*).  */
	    إذا (آخري_structptr_types[j])
	      {
		إذا (!comptypes (آخري_structptr_types[j], newtype))
		  {
		    *argno = i;
		    *strict = آخري_structptr_types[j];
		  }
	      }
	    وإلا
	      آخري_structptr_types[j] = newtype;
	    اكسر;
	  }

      إذا (j == nbst && !comptypes (oldtype, newtype))
	{
	  إذا (اشارو_TYPE_P (oldtype))
	    {
	      /* For incompatible pointers, only reject differences in
		 the unqualified variants of the referenced types but
		 consider differences in qualifiers as benign (report
		 those to caller via *STRICT below).  */
	      وڻ oldref = TYPE_MAIN_VARIANT (وڻ_TYPE (oldtype));
	      وڻ newref = TYPE_MAIN_VARIANT (وڻ_TYPE (newtype));
	      إذا (!comptypes (oldref, newref))
		أرجع NULL_وڻ;
	    }

	  إذا (!*strict)
	    {
	      *argno = i;
	      *strict = oldtype;
	    }
	}

      oldargs = وڻ_CHAIN (oldargs);
      newargs = وڻ_CHAIN (newargs);
    }

  وڻ trytype = c_build_function_type (newrettype, tryargs);

  /* Allow declaration to change transaction_safe attribute.  */
  وڻ oldattrs = TYPE_خاصيتون (oldtype);
  وڻ oldtsafe = lookup_attribute ("transaction_safe", oldattrs);
  وڻ newattrs = TYPE_خاصيتون (newtype);
  وڻ newtsafe = lookup_attribute ("transaction_safe", newattrs);
  إذا (oldtsafe && !newtsafe)
    oldattrs = remove_attribute ("transaction_safe", oldattrs);
  وإلا إذا (newtsafe && !oldtsafe)
    oldattrs = وڻ_cons (get_identifier ("transaction_safe"),
			  NULL_وڻ, oldattrs);

  أرجع c_build_type_attribute_variant (trytype, oldattrs);
}

/* Subroutine of diagnose_mismatched_decls.  Check for function type
   mismatch involving an empty arglist vs a nonempty one and give clearer
   diagnostics.  */
ساكن فراغ
diagnose_arglist_conflict (وڻ newdecl, وڻ olddecl,
			   وڻ newtype, وڻ oldtype)
{
  وڻ t;

  إذا (وڻ_ڪوڊ (olddecl) != FUNCTION_DECL
      || !comptypes (وڻ_TYPE (oldtype), وڻ_TYPE (newtype))
      || !((!prototype_p (oldtype) && DECL_INITIAL (olddecl) == NULL_وڻ)
	   || (!prototype_p (newtype) && DECL_INITIAL (newdecl) == NULL_وڻ)))
    أرجع;

  t = TYPE_ARG_TYPES (oldtype);
  إذا (t == NULL_وڻ)
    t = TYPE_ARG_TYPES (newtype);
  لكل (; t; t = وڻ_CHAIN (t))
    {
      وڻ type = وڻ_قدر (t);

      إذا (وڻ_CHAIN (t) == NULL_وڻ
	  && TYPE_MAIN_VARIANT (type) != void_type_ڳنڍ)
	{
	  inform (داخلا_location, "a parameter list with an ellipsis "
		  "cannot match an empty parameter name list declaration");
	  اكسر;
	}

      إذا (!error_عمليو_p (type)
	  && c_type_promotes_منزل (type) != type)
	{
	  inform (داخلا_location, "an argument type that has a default "
		  "promotion cannot match an empty parameter name list "
		  "declaration");
	  اكسر;
	}
    }
}

/* Another subroutine of diagnose_mismatched_decls.  OLDDECL is an
   old-style function definition, NEWDECL is a prototype declaration.
   Diagnose inconsistencies in the argument list.  Returns TRUE if
   the prototype is compatible, FALSE if not.  */
ساكن منطقي
validate_proto_after_old_defn (وڻ newdecl, وڻ newtype, وڻ oldtype)
{
  وڻ newargs, oldargs;
  صحيح i;

#وصف_ڪريو پڇاڙي_جو_ARGLIST(t) ((t) == void_type_ڳنڍ)

  oldargs = TYPE_ACTUAL_ARG_TYPES (oldtype);
  newargs = TYPE_ARG_TYPES (newtype);
  i = 1;

  لكل (;;)
    {
      وڻ oldargtype = وڻ_قدر (oldargs);
      وڻ newargtype = وڻ_قدر (newargs);

      إذا (oldargtype == error_mark_ڳنڍ || newargtype == error_mark_ڳنڍ)
	أرجع خطأ;

      oldargtype = (TYPE_ATOMIC (oldargtype)
		    ? c_build_qualified_type (TYPE_MAIN_VARIANT (oldargtype),
					      TYPE_QUAL_ATOMIC)
		    : TYPE_MAIN_VARIANT (oldargtype));
      newargtype = (TYPE_ATOMIC (newargtype)
		    ? c_build_qualified_type (TYPE_MAIN_VARIANT (newargtype),
					      TYPE_QUAL_ATOMIC)
		    : TYPE_MAIN_VARIANT (newargtype));

      إذا (پڇاڙي_جو_ARGLIST (oldargtype) && پڇاڙي_جو_ARGLIST (newargtype))
	اكسر;

      /* Reaching the end of just one list means the two decls don't
	 agree on the number of arguments.  */
      إذا (پڇاڙي_جو_ARGLIST (oldargtype))
	{
	  error ("prototype for %q+D declares more arguments "
		 "than previous old-style definition", newdecl);
	  أرجع خطأ;
	}
      وإلا إذا (پڇاڙي_جو_ARGLIST (newargtype))
	{
	  error ("prototype for %q+D declares fewer arguments "
		 "than previous old-style definition", newdecl);
	  أرجع خطأ;
	}

      /* Type for passing arg must be consistent with that declared
	 for the arg.  */
      وإلا إذا (!comptypes (oldargtype, newargtype))
	{
	  error ("prototype for %q+D declares argument %d"
		 " with incompatible type",
		 newdecl, i);
	  أرجع خطأ;
	}

      oldargs = وڻ_CHAIN (oldargs);
      newargs = وڻ_CHAIN (newargs);
      i++;
    }

  /* If we get here, no errors were found, but do issue a warning
     for this poor-style construct.  */
  warning (0, "prototype for %q+D follows non-prototype definition",
	   newdecl);
  أرجع سچ;
#وصف_رد پڇاڙي_جو_ARGLIST
}

/* Subroutine of diagnose_mismatched_decls.  Report the location of DECL,
   first in a pair of mismatched declarations, using the diagnostic
   function DIAG.  */
ساكن فراغ
locate_old_decl (وڻ decl)
{
  إذا (وڻ_ڪوڊ (decl) == FUNCTION_DECL
      && fndecl_built_اندريون_p (decl)
      && !C_DECL_DECLARED_BUILTIN (decl))
    ;
  وإلا إذا (DECL_INITIAL (decl))
    inform (داخلا_location,
	    "previous definition of %q+D with type %qT",
	    decl, وڻ_TYPE (decl));
  وإلا إذا (C_DECL_IMPLICIT (decl))
    inform (داخلا_location,
	    "previous implicit declaration of %q+D with type %qT",
	    decl, وڻ_TYPE (decl));
  وإلا
    inform (داخلا_location,
	    "previous declaration of %q+D with type %qT",
	    decl, وڻ_TYPE (decl));
}


/* Helper function.  For a tagged type, it finds the declaration
   for a visible tag declared in the same scope if such a
   declaration exists.  */
ساكن وڻ
اڳيون_ٽيگ (وڻ type)
{
  بنية c_binding *b = عدم;
  وڻ name = c_type_ٽيگ (type);

  إذا (name)
    b = I_ٽيگ_BINDING (name);

  إذا (b)
    b = b->shadowed;

  إذا (b && B_اندريون_CURRENT_SCOPE (b))
    أرجع b->decl;

  أرجع NULL_وڻ;
}

/* Subroutine to mark functions as versioned when using the attribute
   'target_version'.  */

ساكن فراغ
maybe_mark_function_versioned (وڻ decl)
{
  إذا (!DECL_FUNCTION_VERSIONED (decl))
    {
      /* Check if the name of the function has been overridden.  */
      إذا (DECL_ASSEMBLER_NAME_سيٽ_P (decl)
	  && IDENTIFIER_اشارو (DECL_ASSEMBLER_NAME (decl))[0] == '*')
	error_at (DECL_ذريعو_LOCATION (decl),
		  "cannot use function multiversioning on a renamed function");

      /* We need to insert function version now to make sure the correct
	 pre-mangled assembler name is recorded.  */
      cgraph_ڳنڍ *ڳنڍ = cgraph_ڳنڍ::get_create (decl);

      إذا (!ڳنڍ->function_نسخو ())
	ڳنڍ->وجهو_new_function_نسخو ();

      DECL_FUNCTION_VERSIONED (decl) = 1;

      وڻ mangled_name
	= targetm.mangle_decl_assembler_name (decl, DECL_NAME (decl));
      سيٽ_DECL_ASSEMBLER_NAME (decl, mangled_name);
    }
}

/* Subroutine of duplicate_decls.  Compare NEWDECL to OLDDECL.
   Returns true if the caller should proceed to merge the two, false
   if OLDDECL should simply be discarded.  As a side effect, issues
   all necessary diagnostics for invalid or poor-style combinations.
   If it returns true, writes the types of NEWDECL and OLDDECL to
   *NEWTYPEP and *OLDTYPEP - these may have been adjusted from
   TREE_TYPE (NEWDECL, OLDDECL) respectively.  */

ساكن منطقي
diagnose_mismatched_decls (وڻ newdecl, وڻ olddecl,
			   وڻ *newtypep, وڻ *oldtypep)
{
  وڻ newtype, oldtype;
  منطقي retval = سچ;

#وصف_ڪريو DECL_EXTERN_INLINE(DECL) (DECL_DECLARED_INLINE_P (DECL)  \
				  && DECL_EXTERNAL (DECL))

  /* If we have error_mark_node for either decl or type, just discard
     the previous decl - we're in an error cascade already.  */
  إذا (olddecl == error_mark_ڳنڍ || newdecl == error_mark_ڳنڍ)
    أرجع خطأ;
  *oldtypep = oldtype = وڻ_TYPE (olddecl);
  *newtypep = newtype = وڻ_TYPE (newdecl);
  إذا (oldtype == error_mark_ڳنڍ || newtype == error_mark_ڳنڍ)
    أرجع خطأ;

  /* Two different categories of symbol altogether.  This is an error
     unless OLDDECL is a builtin.  OLDDECL will be discarded in any case.  */
  إذا (وڻ_ڪوڊ (olddecl) != وڻ_ڪوڊ (newdecl))
    {
      إذا (!(وڻ_ڪوڊ (olddecl) == FUNCTION_DECL
	    && fndecl_built_اندريون_p (olddecl)
	    && !C_DECL_DECLARED_BUILTIN (olddecl)))
	{
	  auto_diagnostic_گروهه d;
	  error ("%q+D redeclared as different kind of symbol", newdecl);
	  locate_old_decl (olddecl);
	}
      وإلا إذا (وڻ_عوامي (newdecl))
	warning (OPT_Wbuiltin_declaration_mismatch,
		 "built-in function %q+D declared as non-function",
		 newdecl);
      وإلا
	warning (OPT_Wshadow, "declaration of %q+D shadows "
		 "a built-in function", newdecl);
      أرجع خطأ;
    }

  /* Enumerators have no linkage, so may only be declared once in a
     given scope.  */
  إذا (وڻ_ڪوڊ (olddecl) == CONST_DECL)
    {
      إذا (flag_isoc23
	  && TYPE_NAME (DECL_CONTEXT (newdecl))
	  && DECL_CONTEXT (newdecl) != DECL_CONTEXT (olddecl)
	  && TYPE_NAME (DECL_CONTEXT (newdecl)) == TYPE_NAME (DECL_CONTEXT (olddecl)))
	{
	  إذا (!simple_cst_equal (DECL_INITIAL (olddecl), DECL_INITIAL (newdecl)))
	    {
	      auto_diagnostic_گروهه d;
	      error ("conflicting redeclaration of enumerator %q+D", newdecl);
	      locate_old_decl (olddecl);
	    }
	}
      وإلا
	{
	  auto_diagnostic_گروهه d;
	  error ("redeclaration of enumerator %q+D", newdecl);
	  locate_old_decl (olddecl);
	}
      أرجع خطأ;
    }

  منطقي pedwarned = خطأ;
  منطقي warned = خطأ;
  منطقي enum_and_int_p = خطأ;
  auto_diagnostic_گروهه d;

  منطقي comptypes_نتيجو = comptypes_check_enum_int (oldtype, newtype,
						    &enum_and_int_p);
  إذا (!comptypes_نتيجو)
    {
      إذا (وڻ_ڪوڊ (olddecl) == FUNCTION_DECL
	  && fndecl_built_اندريون_p (olddecl, BUILT_اندريون_عام)
	  && !C_DECL_DECLARED_BUILTIN (olddecl))
	{
	  /* Accept "harmless" mismatches in function types such
	     as missing qualifiers or int vs long when they're the same
	     size.  However, diagnose return and argument types that are
	     incompatible according to language rules.  */
	  وڻ mismatch_expect;
	  بنانشان mismatch_argno;

	  وڻ trytype = ميلاپ_builtin_function_types (newtype, oldtype,
						       &mismatch_expect,
						       &mismatch_argno);

	  إذا (trytype && comptypes (newtype, trytype))
	    *oldtypep = oldtype = trytype;
	  وإلا
	    {
	      /* If types don't match for a built-in, throw away the
		 built-in.  No point in calling locate_old_decl here, it
		 won't print anything.  */
	      ثابت حرف *سرو = سرو_for_builtin_fn (olddecl);
	      location_t loc = DECL_ذريعو_LOCATION (newdecl);
	      إذا (warning_at (loc, OPT_Wbuiltin_declaration_mismatch,
			      "conflicting types for built-in function %q+D; "
			      "expected %qT",
			      newdecl, oldtype)
		  && سرو)
		{
		  /* Suggest the right header to include as the preferred
		     solution rather than the spelling of the declaration.  */
		  rich_location richloc (سٽ_جدول, loc);
		  maybe_جوڙيو_include_fixit (&richloc, سرو, سچ);
		  inform (&richloc,
			  "%qD is declared in header %qs", olddecl, سرو);
		}
	      أرجع خطأ;
	    }

	  إذا (mismatch_expect && extra_warnings)
	    {
	      location_t newloc = DECL_ذريعو_LOCATION (newdecl);
	      منطقي warned = خطأ;
	      إذا (mismatch_argno)
		warned = warning_at (newloc, OPT_Wbuiltin_declaration_mismatch,
				     "mismatch in argument %u type of built-in "
				     "function %qD; expected %qT",
				     mismatch_argno, newdecl, mismatch_expect);
	      وإلا
		warned = warning_at (newloc, OPT_Wbuiltin_declaration_mismatch,
				     "mismatch in return type of built-in "
				     "function %qD; expected %qT",
				     newdecl, mismatch_expect);
	      ثابت حرف *سرو = سرو_for_builtin_fn (olddecl);
	      إذا (warned && سرو)
		{
		  rich_location richloc (سٽ_جدول, newloc);
		  maybe_جوڙيو_include_fixit (&richloc, سرو, سچ);
		  inform (&richloc,
			  "%qD is declared in header %qs", olddecl, سرو);
		}
	    }
	}
      وإلا إذا (وڻ_ڪوڊ (olddecl) == FUNCTION_DECL
	       && DECL_IS_UNDECLARED_BUILTIN (olddecl))
	{
	  /* A conflicting function declaration for a predeclared
	     function that isn't actually built in.  Objective C uses
	     these.  The new declaration silently overrides everything
	     but the volatility (i.e. noreturn) indication.  See also
	     below.  FIXME: Make Objective C use normal builtins.  */
	  وڻ_THIS_VOLATILE (newdecl) |= وڻ_THIS_VOLATILE (olddecl);
	  أرجع خطأ;
	}
      /* Permit void foo (...) to match int foo (...) if the latter is
	 the definition and implicit int was used.  See
	 c-torture/compile/920625-2.c.  */
      وإلا إذا (وڻ_ڪوڊ (newdecl) == FUNCTION_DECL && DECL_INITIAL (newdecl)
	       && TYPE_MAIN_VARIANT (وڻ_TYPE (oldtype)) == void_type_ڳنڍ
	       && TYPE_MAIN_VARIANT (وڻ_TYPE (newtype)) == integer_type_ڳنڍ
	       && C_FUNCTION_IMPLICIT_INT (newdecl) && !DECL_INITIAL (olddecl))
	{
	  pedwarned = pedwarn (داخلا_location, 0,
			       "conflicting types for %q+D", newdecl);
	  /* Make sure we keep void as the return type.  */
	  وڻ_TYPE (newdecl) = *newtypep = newtype = oldtype;
	  C_FUNCTION_IMPLICIT_INT (newdecl) = 0;
	}
      /* Permit void foo (...) to match an earlier call to foo (...) with
	 no declared type (thus, implicitly int).  */
      وإلا إذا (وڻ_ڪوڊ (newdecl) == FUNCTION_DECL
	       && TYPE_MAIN_VARIANT (وڻ_TYPE (newtype)) == void_type_ڳنڍ
	       && TYPE_MAIN_VARIANT (وڻ_TYPE (oldtype)) == integer_type_ڳنڍ
	       && C_DECL_IMPLICIT (olddecl) && !DECL_INITIAL (olddecl))
	{
	  pedwarned = pedwarn (داخلا_location, 0,
			       "conflicting types for %q+D; have %qT",
			       newdecl, newtype);
	  /* Make sure we keep void as the return type.  */
	  وڻ_TYPE (olddecl) = *oldtypep = oldtype = newtype;
	}
      وإلا
	{
	  صحيح new_quals = TYPE_QUALS (newtype);
	  صحيح old_quals = TYPE_QUALS (oldtype);

	  إذا (new_quals != old_quals)
	    {
	      addr_space_t new_addr = DECODE_QUAL_ADDR_SPACE (new_quals);
	      addr_space_t old_addr = DECODE_QUAL_ADDR_SPACE (old_quals);
	      إذا (new_addr != old_addr)
		{
		  إذا (ADDR_SPACE_GENERIC_P (new_addr))
		    error ("conflicting named address spaces (generic vs %s) "
			   "for %q+D",
			   c_addr_space_name (old_addr), newdecl);
		  وإلا إذا (ADDR_SPACE_GENERIC_P (old_addr))
		    error ("conflicting named address spaces (%s vs generic) "
			   "for %q+D",
			   c_addr_space_name (new_addr), newdecl);
		  وإلا
		    error ("conflicting named address spaces (%s vs %s) "
			   "for %q+D",
			   c_addr_space_name (new_addr),
			   c_addr_space_name (old_addr),
			   newdecl);
		}

	      إذا (CLEAR_QUAL_ADDR_SPACE (new_quals)
		  != CLEAR_QUAL_ADDR_SPACE (old_quals))
		error ("conflicting type qualifiers for %q+D", newdecl);
	    }
	  وإلا
	    {
	      إذا (وڻ_ڪوڊ (olddecl) == FUNCTION_DECL)
		{
		  وڻ attrs = TYPE_خاصيتون (وڻ_TYPE (olddecl));
		  إذا (attrs && !TYPE_خاصيتون (وڻ_TYPE (newdecl)))
		    {
		      /* Similar to the C++ front-end, for FUNCTION_DECL,
			 if OLDDECL has attributes and NEWDECL doesn't,
			 try the type with OLDDECL attributes.  */
		      وڻ rettype = وڻ_TYPE (newtype);
		      وڻ tryargs = TYPE_ARG_TYPES (newtype);
		      وڻ trytype = c_build_function_type (rettype,
							    tryargs);
		      trytype = c_build_type_attribute_variant (trytype,
								attrs);
		      إذا (comptypes (oldtype, trytype))
			{
			  *newtypep = newtype = trytype;
			  comptypes_نتيجو = سچ;
			}
		    }
		}

	      إذا (!comptypes_نتيجو)
		error ("conflicting types for %q+D; have %qT", newdecl,
		       newtype);
	    }
	  إذا (!comptypes_نتيجو)
	    {
	      diagnose_arglist_conflict (newdecl, olddecl, newtype,
					 oldtype);
	      locate_old_decl (olddecl);
	      أرجع خطأ;
	    }
	}
    }
  /* Warn about enum/integer type mismatches.  They are compatible types
     (C23 6.7.2.2/5), but may pose portability problems.  */
  وإلا إذا (enum_and_int_p
	   && وڻ_ڪوڊ (newdecl) != TYPE_DECL
	   /* Don't warn about acc_on_device built-in redeclaration,
	      the built-in is declared with int rather than enum because
	      the enum isn't intrinsic.  */
	   && !(وڻ_ڪوڊ (olddecl) == FUNCTION_DECL
		&& fndecl_built_اندريون_p (olddecl, BUILT_اندريون_ACC_ON_DEVICE)
		&& !C_DECL_DECLARED_BUILTIN (olddecl)))
    warned = warning_at (DECL_ذريعو_LOCATION (newdecl),
			 OPT_Wenum_int_mismatch,
			 "conflicting types for %q+D due to enum/integer "
			 "mismatch; have %qT", newdecl, newtype);

  /* Redeclaration of a type is a constraint violation (6.7.2.3p1),
     but silently ignore the redeclaration if either is in a system
     header.  (Conflicting redeclarations were handled above.)  This
     is allowed for C11 if the types are the same, not just
     compatible.  */
  إذا (وڻ_ڪوڊ (newdecl) == TYPE_DECL)
    {
      إذا (!comptypes_same_p (oldtype, newtype))
	{
	  error ("redefinition of typedef %q+D with different type", newdecl);
	  locate_old_decl (olddecl);
	  أرجع خطأ;
	}

      إذا (DECL_اندريون_SYSTEM_سرو (newdecl)
	  || DECL_اندريون_SYSTEM_سرو (olddecl)
	  || warning_suppressed_p (newdecl, OPT_Wpedantic)
	  || warning_suppressed_p (olddecl, OPT_Wpedantic))
	أرجع سچ;  /* Allow OLDDECL to continue in use.  */

      إذا (c_type_variably_modified_p (newtype))
	{
	  error ("redefinition of typedef %q+D with variably modified type",
		 newdecl);
	  locate_old_decl (olddecl);
	}
      وإلا إذا (pedwarn_c99 (داخلا_location, OPT_Wpedantic,
			    "redefinition of typedef %q+D", newdecl))
	locate_old_decl (olddecl);

      أرجع سچ;
    }

  /* Function declarations can either be 'static' or 'extern' (no
     qualifier is equivalent to 'extern' - C99 6.2.2p5) and therefore
     can never conflict with each other on account of linkage
     (6.2.2p4).  Multiple definitions are not allowed (6.9p3,5) but
     gnu89 mode permits two definitions if one is 'extern inline' and
     one is not.  The non- extern-inline definition supersedes the
     extern-inline definition.  */

  وإلا إذا (وڻ_ڪوڊ (newdecl) == FUNCTION_DECL)
    {
      /* If you declare a built-in function name as static, or
	 define the built-in with an old-style definition (so we
	 can't validate the argument list) the built-in definition is
	 overridden, but optionally warn this was a bad choice of name.  */
      إذا (fndecl_built_اندريون_p (olddecl)
	  && !C_DECL_DECLARED_BUILTIN (olddecl))
	{
	  إذا (!وڻ_عوامي (newdecl)
	      || (DECL_INITIAL (newdecl)
		  && !prototype_p (وڻ_TYPE (newdecl))))
	    {
	      warning_at (DECL_ذريعو_LOCATION (newdecl),
			  OPT_Wshadow, "declaration of %qD shadows "
			  "a built-in function", newdecl);
	      /* Discard the old built-in function.  */
	      أرجع خطأ;
	    }

	  إذا (!prototype_p (وڻ_TYPE (newdecl)))
	    {
	      /* Set for built-ins that take no arguments.  */
	      منطقي func_void_دليلون = خطأ;
	      إذا (وڻ at = TYPE_ARG_TYPES (oldtype))
		func_void_دليلون = VOID_TYPE_P (وڻ_قدر (at));

	      إذا (extra_warnings && !func_void_دليلون)
		warning_at (DECL_ذريعو_LOCATION (newdecl),
			    OPT_Wbuiltin_declaration_mismatch,
			    "declaration of built-in function %qD without "
			    "a prototype; expected %qT",
			    newdecl, وڻ_TYPE (olddecl));
	    }
	}

      إذا (DECL_INITIAL (newdecl))
	{
	  إذا (DECL_INITIAL (olddecl))
	    {
	      /* If the new declaration isn't overriding an extern inline
		 reject the new decl. In c99, no overriding is allowed
		 in the same translation unit.  */
	      إذا (!DECL_EXTERN_INLINE (olddecl)
		  || DECL_EXTERN_INLINE (newdecl)
		  || (!flag_gnu89_inline
		      && (!DECL_DECLARED_INLINE_P (olddecl)
			  || !lookup_attribute ("gnu_inline",
						DECL_خاصيتون (olddecl)))
		      && (!DECL_DECLARED_INLINE_P (newdecl)
			  || !lookup_attribute ("gnu_inline",
						DECL_خاصيتون (newdecl)))))
		{
		  auto_diagnostic_گروهه d;
		  error ("redefinition of %q+D", newdecl);
		  locate_old_decl (olddecl);
		  أرجع خطأ;
		}
	    }
	}
      /* If we have a prototype after an old-style function definition,
	 the argument types must be checked specially.  */
      وإلا إذا (DECL_INITIAL (olddecl)
	       && !prototype_p (oldtype) && prototype_p (newtype)
	       && TYPE_ACTUAL_ARG_TYPES (oldtype))
	{
	  auto_diagnostic_گروهه d;
	  إذا (!validate_proto_after_old_defn (newdecl, newtype, oldtype))
	    {
	      locate_old_decl (olddecl);
	      أرجع خطأ;
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
      إذا (وڻ_عوامي (olddecl) && !وڻ_عوامي (newdecl))
	{
	  /* Two exceptions to the rule.  If olddecl is an extern
	     inline, or a predeclared function that isn't actually
	     built in, newdecl silently overrides olddecl.  The latter
	     occur only in Objective C; see also above.  (FIXME: Make
	     Objective C use normal builtins.)  */
	  إذا (!DECL_IS_UNDECLARED_BUILTIN (olddecl)
	      && !DECL_EXTERN_INLINE (olddecl))
	    {
	      auto_diagnostic_گروهه d;
	      error ("static declaration of %q+D follows "
		     "non-static declaration", newdecl);
	      locate_old_decl (olddecl);
	    }
	  أرجع خطأ;
	}
      وإلا إذا (وڻ_عوامي (newdecl) && !وڻ_عوامي (olddecl))
	{
	  إذا (DECL_CONTEXT (olddecl))
	    {
	      auto_diagnostic_گروهه d;
	      error ("non-static declaration of %q+D follows "
		     "static declaration", newdecl);
	      locate_old_decl (olddecl);
	      أرجع خطأ;
	    }
	  وإلا إذا (warn_traditional)
	    {
	      warned |= warning (OPT_Wtraditional,
				 "non-static declaration of %q+D "
				 "follows static declaration", newdecl);
	    }
	}

      /* Make sure gnu_inline attribute is either not present, or
	 present on all inline decls.  */
      إذا (DECL_DECLARED_INLINE_P (olddecl)
	  && DECL_DECLARED_INLINE_P (newdecl))
	{
	  منطقي newa = lookup_attribute ("gnu_inline",
					DECL_خاصيتون (newdecl)) != عدم;
	  منطقي olda = lookup_attribute ("gnu_inline",
					DECL_خاصيتون (olddecl)) != عدم;
	  إذا (newa != olda)
	    {
	      auto_diagnostic_گروهه d;
	      error_at (داخلا_location, "%<gnu_inline%> attribute present on %q+D",
			newa ? newdecl : olddecl);
	      error_at (DECL_ذريعو_LOCATION (newa ? olddecl : newdecl),
			"but not here");
	    }
	}
      /* Check if these are unmergeable overlapping FMV declarations.  */
      إذا (!هدف_HAS_FMV_هدف_ATTRIBUTE
	  && diagnose_versioned_decls (olddecl, newdecl))
	أرجع خطأ;
    }
  وإلا إذا (VAR_P (newdecl))
    {
      /* Only variables can be thread-local, and all declarations must
	 agree on this property.  */
      إذا (C_DECL_THREADPRIVATE_P (olddecl) && !DECL_THREAD_LOCAL_P (newdecl))
	{
	  /* Nothing to check.  Since OLDDECL is marked threadprivate
	     and NEWDECL does not have a thread-local attribute, we
	     will merge the threadprivate attribute into NEWDECL.  */
	  ;
	}
      وإلا إذا (DECL_THREAD_LOCAL_P (newdecl) != DECL_THREAD_LOCAL_P (olddecl))
	{
	  auto_diagnostic_گروهه d;
	  إذا (DECL_THREAD_LOCAL_P (newdecl))
	    error ("thread-local declaration of %q+D follows "
		   "non-thread-local declaration", newdecl);
	  وإلا
	    error ("non-thread-local declaration of %q+D follows "
		   "thread-local declaration", newdecl);

	  locate_old_decl (olddecl);
	  أرجع خطأ;
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
      إذا ((DECL_INITIAL (newdecl) && DECL_INITIAL (olddecl))
	  || (flag_isoc23
	      && DECL_THREAD_LOCAL_P (newdecl)
	      && !DECL_EXTERNAL (newdecl)
	      && !DECL_EXTERNAL (olddecl)))
	{
	  auto_diagnostic_گروهه d;
	  error ("redefinition of %q+D", newdecl);
	  locate_old_decl (olddecl);
	  أرجع خطأ;
	}

      /* Objects declared at file scope: if the first declaration had
	 external linkage (even if it was an external reference) the
	 second must have external linkage as well, or the behavior is
	 undefined.  If the first declaration had internal linkage, then
	 the second must too, or else be an external reference (in which
	 case the composite declaration still has internal linkage).
	 As for function declarations, we warn about the static-then-
	 extern case only for -Wtraditional.  See generally 6.2.2p3-5,7.  */
      إذا (DECL_FILE_SCOPE_P (newdecl)
	  && وڻ_عوامي (newdecl) != وڻ_عوامي (olddecl))
	{
	  إذا (DECL_EXTERNAL (newdecl))
	    {
	      إذا (!DECL_FILE_SCOPE_P (olddecl))
		{
		  auto_diagnostic_گروهه d;
		  error ("extern declaration of %q+D follows "
			 "declaration with no linkage", newdecl);
		  locate_old_decl (olddecl);
		  أرجع خطأ;
		}
	      وإلا إذا (warn_traditional)
		{
		  warned |= warning (OPT_Wtraditional,
				     "non-static declaration of %q+D "
				     "follows static declaration", newdecl);
		}
	    }
	  وإلا
	    {
	      auto_diagnostic_گروهه d;
	      إذا (وڻ_عوامي (newdecl))
		error ("non-static declaration of %q+D follows "
		       "static declaration", newdecl);
	      وإلا
		error ("static declaration of %q+D follows "
		       "non-static declaration", newdecl);

	      locate_old_decl (olddecl);
	      أرجع خطأ;
	    }
	}
      /* Two objects with the same name declared at the same block
	 scope must both be external references (6.7p3).  */
      وإلا إذا (!DECL_FILE_SCOPE_P (newdecl))
	{
	  إذا (DECL_EXTERNAL (newdecl))
	    {
	      /* Extern with initializer at block scope, which will
		 already have received an error.  */
	    }
	  وإلا إذا (DECL_EXTERNAL (olddecl))
	    {
	      auto_diagnostic_گروهه d;
	      error ("declaration of %q+D with no linkage follows "
		     "extern declaration", newdecl);
	      locate_old_decl (olddecl);
	    }
	  وإلا
	    {
	      auto_diagnostic_گروهه d;
	      error ("redeclaration of %q+D with no linkage", newdecl);
	      locate_old_decl (olddecl);
	    }

	  أرجع خطأ;
	}

      /* C++ does not permit a decl to appear multiple times at file
	 scope.  */
      إذا (warn_cxx_compat
	  && DECL_FILE_SCOPE_P (newdecl)
	  && !DECL_EXTERNAL (newdecl)
	  && !DECL_EXTERNAL (olddecl))
	warned |= warning_at (DECL_ذريعو_LOCATION (newdecl),
			      OPT_Wc___compat,
			      "duplicate declaration of %qD is "
			      "invalid in C++", newdecl);
    }

  /* warnings */
  /* All decls must agree on a visibility.  */
  إذا (ڪوڊ_شامل_آهي_STRUCT (وڻ_ڪوڊ (newdecl), TS_DECL_WITH_VIS)
      && DECL_VISIBILITY_SPECIFIED (newdecl) && DECL_VISIBILITY_SPECIFIED (olddecl)
      && DECL_VISIBILITY (newdecl) != DECL_VISIBILITY (olddecl))
    {
      warned |= warning (0, "redeclaration of %q+D with different visibility "
			 "(old visibility preserved)", newdecl);
    }

  إذا (وڻ_ڪوڊ (newdecl) == FUNCTION_DECL)
    warned |= diagnose_mismatched_خاصيتون (olddecl, newdecl);
  وإلا /* PARM_DECL, VAR_DECL */
    {
      /* Redeclaration of a parameter is a constraint violation (this is
	 not explicitly stated, but follows from C99 6.7p3 [no more than
	 one declaration of the same identifier with no linkage in the
	 same scope, except type tags] and 6.2.2p6 [parameters have no
	 linkage]).  We must check for a forward parameter declaration,
	 indicated by TREE_ASM_WRITTEN on the old declaration - this is
	 an extension, the mandatory diagnostic for which is handled by
	 mark_forward_parm_decls.  */

      إذا (وڻ_ڪوڊ (newdecl) == PARM_DECL
	  && (!وڻ_ASM_WRITTEN (olddecl) || وڻ_ASM_WRITTEN (newdecl)))
	{
	  auto_diagnostic_گروهه d;
	  error ("redefinition of parameter %q+D", newdecl);
	  locate_old_decl (olddecl);
	  أرجع خطأ;
	}
    }

  /* Optional warning for completely redundant decls.  */
  إذا (!warned && !pedwarned
      && warn_redundant_decls
      /* Don't warn about a function declaration followed by a
	 definition.  */
      && !(وڻ_ڪوڊ (newdecl) == FUNCTION_DECL
	   && DECL_INITIAL (newdecl) && !DECL_INITIAL (olddecl))
      /* Don't warn about redundant redeclarations of builtins.  */
      && !(وڻ_ڪوڊ (newdecl) == FUNCTION_DECL
	   && !fndecl_built_اندريون_p (newdecl)
	   && fndecl_built_اندريون_p (olddecl)
	   && !C_DECL_DECLARED_BUILTIN (olddecl))
      /* Don't warn about an extern followed by a definition.  */
      && !(DECL_EXTERNAL (olddecl) && !DECL_EXTERNAL (newdecl))
      /* Don't warn about forward parameter decls.  */
      && !(وڻ_ڪوڊ (newdecl) == PARM_DECL
	   && وڻ_ASM_WRITTEN (olddecl) && !وڻ_ASM_WRITTEN (newdecl))
      /* Don't warn about a variable definition following a declaration.  */
      && !(VAR_P (newdecl)
	   && DECL_INITIAL (newdecl) && !DECL_INITIAL (olddecl)))
    {
      warned = warning (OPT_Wredundant_decls, "redundant redeclaration of %q+D",
			newdecl);
    }

  /* Report location of previous decl/defn.  */
  إذا (warned || pedwarned)
    locate_old_decl (olddecl);

#وصف_رد DECL_EXTERN_INLINE

  أرجع retval;
}

/* Subroutine of duplicate_decls.  NEWDECL has been found to be
   consistent with OLDDECL, but carries new information.  Merge the
   new information into OLDDECL.  This function issues no
   diagnostics.  */

ساكن فراغ
ملايو_decls (وڻ newdecl, وڻ olddecl, وڻ newtype, وڻ oldtype)
{
  منطقي new_is_definition = (وڻ_ڪوڊ (newdecl) == FUNCTION_DECL
			    && DECL_INITIAL (newdecl) != NULL_وڻ);
  منطقي new_is_prototype = (وڻ_ڪوڊ (newdecl) == FUNCTION_DECL
			   && prototype_p (وڻ_TYPE (newdecl)));
  منطقي old_is_prototype = (وڻ_ڪوڊ (olddecl) == FUNCTION_DECL
			   && prototype_p (وڻ_TYPE (olddecl)));

  /* For real parm decl following a forward decl, rechain the old decl
     in its new location and clear TREE_ASM_WRITTEN (it's not a
     forward decl anymore).  */
  إذا (وڻ_ڪوڊ (newdecl) == PARM_DECL
      && وڻ_ASM_WRITTEN (olddecl) && !وڻ_ASM_WRITTEN (newdecl))
    {
      بنية c_binding *b, **هتي;

      لكل (هتي = &current_scope->bindings; *هتي; هتي = &(*هتي)->prev)
	إذا ((*هتي)->decl == olddecl)
	  اذهب مليو;
      gcc_unreachable ();

    مليو:
      b = *هتي;
      *هتي = b->prev;
      b->prev = current_scope->bindings;
      current_scope->bindings = b;

      وڻ_ASM_WRITTEN (olddecl) = 0;
    }

  DECL_خاصيتون (newdecl)
    = targetm.ملايو_decl_خاصيتون (olddecl, newdecl);

  /* For typedefs use the old type, as the new type's DECL_NAME points
     at newdecl, which will be ggc_freed.  */
  إذا (وڻ_ڪوڊ (newdecl) == TYPE_DECL)
    {
      /* But NEWTYPE might have an attribute, honor that.  */
      وڻ tem = newtype;
      newtype = oldtype;

      إذا (TYPE_USER_ALIGN (tem))
	{
	  إذا (TYPE_ALIGN (tem) > TYPE_ALIGN (newtype))
	    سيٽ_TYPE_ALIGN (newtype, TYPE_ALIGN (tem));
	  TYPE_USER_ALIGN (newtype) = سچ;
	}

      /* And remove the new type from the variants list.  */
      إذا (TYPE_NAME (وڻ_TYPE (newdecl)) == newdecl)
	{
	  وڻ remove = وڻ_TYPE (newdecl);
	  إذا (TYPE_MAIN_VARIANT (remove) == remove)
	    {
	      gcc_assert (TYPE_ايندڙ_VARIANT (remove) == NULL_وڻ);
	      /* If remove is the main variant, no need to remove that
		 from the list.  One of the DECL_ORIGINAL_TYPE
		 variants, e.g. created for aligned attribute, might still
		 refer to the newdecl TYPE_DECL though, so remove that one
		 in that case.  */
	      إذا (DECL_ORIGINAL_TYPE (newdecl)
		  && DECL_ORIGINAL_TYPE (newdecl) != remove)
		لكل (وڻ t = TYPE_MAIN_VARIANT (DECL_ORIGINAL_TYPE (newdecl));
		     t; t = TYPE_MAIN_VARIANT (t))
		  إذا (TYPE_NAME (TYPE_ايندڙ_VARIANT (t)) == newdecl)
		    {
		      TYPE_ايندڙ_VARIANT (t)
			= TYPE_ايندڙ_VARIANT (TYPE_ايندڙ_VARIANT (t));
		      اكسر;
		    }
	    }
	  وإلا
	    لكل (وڻ t = TYPE_MAIN_VARIANT (remove); ;
		 t = TYPE_ايندڙ_VARIANT (t))
	      إذا (TYPE_ايندڙ_VARIANT (t) == remove)
		{
		  TYPE_ايندڙ_VARIANT (t) = TYPE_ايندڙ_VARIANT (remove);
		  اكسر;
		}
	}

      /* Make sure we refer to the same type as the olddecl.  */
      DECL_ORIGINAL_TYPE (newdecl) = DECL_ORIGINAL_TYPE (olddecl);
    }

  /* Merge the data types specified in the two decls.  */
  وڻ_TYPE (newdecl)
    = وڻ_TYPE (olddecl)
    = مرکب_type (newtype, oldtype);

  /* Lay the type out, unless already done.  */
  إذا (!comptypes (oldtype, وڻ_TYPE (newdecl)))
    {
      إذا (وڻ_TYPE (newdecl) != error_mark_ڳنڍ)
	layout_type (وڻ_TYPE (newdecl));
      إذا (وڻ_ڪوڊ (newdecl) != FUNCTION_DECL
	  && وڻ_ڪوڊ (newdecl) != TYPE_DECL
	  && وڻ_ڪوڊ (newdecl) != CONST_DECL)
	layout_decl (newdecl, 0);
    }
  وإلا
    {
      /* Since the type is OLDDECL's, make OLDDECL's size go with.  */
      DECL_سائيز (newdecl) = DECL_سائيز (olddecl);
      DECL_سائيز_UNIT (newdecl) = DECL_سائيز_UNIT (olddecl);
      سيٽ_DECL_گهڻائي (newdecl, DECL_گهڻائي (olddecl));
      إذا (DECL_ALIGN (olddecl) > DECL_ALIGN (newdecl))
	{
	  سيٽ_DECL_ALIGN (newdecl, DECL_ALIGN (olddecl));
	  DECL_USER_ALIGN (newdecl) |= DECL_USER_ALIGN (olddecl);
	}
      وإلا إذا (DECL_ALIGN (olddecl) == DECL_ALIGN (newdecl)
	       && DECL_USER_ALIGN (olddecl) != DECL_USER_ALIGN (newdecl))
	DECL_USER_ALIGN (newdecl) = 1;
      إذا (DECL_WARN_IF_NOT_ALIGN (olddecl)
	  > DECL_WARN_IF_NOT_ALIGN (newdecl))
	سيٽ_DECL_WARN_IF_NOT_ALIGN (newdecl,
				    DECL_WARN_IF_NOT_ALIGN (olddecl));
    }

  /* Keep the old rtl since we can safely use it.  */
  إذا (HAS_RTL_P (olddecl))
    COPY_DECL_RTL (olddecl, newdecl);

  /* Merge the type qualifiers.  */
  إذا (وڻ_READONLY (newdecl))
    وڻ_READONLY (olddecl) = 1;

  إذا (وڻ_THIS_VOLATILE (newdecl))
    وڻ_THIS_VOLATILE (olddecl) = 1;

  /* Merge deprecatedness.  */
  إذا (وڻ_DEPRECATED (newdecl))
    وڻ_DEPRECATED (olddecl) = 1;

  /* Merge unavailability.  */
  إذا (وڻ_UNAVAILABLE (newdecl))
    وڻ_UNAVAILABLE (olddecl) = 1;

  /* If a decl is in a system header and the other isn't, keep the one on the
     system header. Otherwise, keep source location of definition rather than
     declaration and of prototype rather than non-prototype unless that
     prototype is built-in.  */
  إذا (HAS_DECL_ASSEMBLER_NAME_P (olddecl)
      && DECL_اندريون_SYSTEM_سرو (olddecl)
      && !DECL_اندريون_SYSTEM_سرو (newdecl) )
    DECL_ذريعو_LOCATION (newdecl) = DECL_ذريعو_LOCATION (olddecl);
  وإلا إذا (HAS_DECL_ASSEMBLER_NAME_P (olddecl)
	   && DECL_اندريون_SYSTEM_سرو (newdecl)
	   && !DECL_اندريون_SYSTEM_سرو (olddecl))
    DECL_ذريعو_LOCATION (olddecl) = DECL_ذريعو_LOCATION (newdecl);
  وإلا إذا ((DECL_INITIAL (newdecl) == NULL_وڻ
	    && DECL_INITIAL (olddecl) != NULL_وڻ)
	   || (old_is_prototype && !new_is_prototype
	       && !C_DECL_BUILTIN_PROTOTYPE (olddecl)))
    DECL_ذريعو_LOCATION (newdecl) = DECL_ذريعو_LOCATION (olddecl);

  /* Merge the initialization information.  */
   إذا (DECL_INITIAL (newdecl) == NULL_وڻ)
    DECL_INITIAL (newdecl) = DECL_INITIAL (olddecl);

  /* Merge 'constexpr' information.  */
  إذا (VAR_P (olddecl) && VAR_P (newdecl))
    {
      إذا (C_DECL_DECLARED_CONSTEXPR (olddecl))
	C_DECL_DECLARED_CONSTEXPR (newdecl) = 1;
      وإلا إذا (C_DECL_DECLARED_CONSTEXPR (newdecl))
	C_DECL_DECLARED_CONSTEXPR (olddecl) = 1;
    }

  /* Merge the threadprivate attribute.  */
  إذا (VAR_P (olddecl) && C_DECL_THREADPRIVATE_P (olddecl))
    C_DECL_THREADPRIVATE_P (newdecl) = 1;

  إذا (HAS_DECL_ASSEMBLER_NAME_P (olddecl))
    {
      /* Copy the assembler name.
	 Currently, it can only be defined in the prototype.  */
      COPY_DECL_ASSEMBLER_NAME (olddecl, newdecl);

      /* Use visibility of whichever declaration had it specified */
      إذا (DECL_VISIBILITY_SPECIFIED (olddecl))
	{
	  DECL_VISIBILITY (newdecl) = DECL_VISIBILITY (olddecl);
	  DECL_VISIBILITY_SPECIFIED (newdecl) = 1;
	}

      إذا (وڻ_ڪوڊ (newdecl) == FUNCTION_DECL)
	{
	  DECL_STATIC_CONSTRUCTOR(newdecl) |= DECL_STATIC_CONSTRUCTOR(olddecl);
	  DECL_STATIC_DESTRUCTOR (newdecl) |= DECL_STATIC_DESTRUCTOR (olddecl);
	  DECL_NO_حد_بندي_ڍير (newdecl) |= DECL_NO_حد_بندي_ڍير (olddecl);
	  DECL_NO_INSTRUMENT_FUNCTION_داخلا_EXIT (newdecl)
	    |= DECL_NO_INSTRUMENT_FUNCTION_داخلا_EXIT (olddecl);
	  وڻ_THIS_VOLATILE (newdecl) |= وڻ_THIS_VOLATILE (olddecl);
	  DECL_IS_MALLOC (newdecl) |= DECL_IS_MALLOC (olddecl);
	  إذا (DECL_IS_OPERATOR_NEW_P (olddecl))
	    DECL_سيٽ_IS_OPERATOR_NEW (newdecl, سچ);
	  إذا (DECL_IS_OPERATOR_DELETE_P (olddecl))
	    DECL_سيٽ_IS_OPERATOR_DELETE (newdecl, سچ);
	  وڻ_READONLY (newdecl) |= وڻ_READONLY (olddecl);
	  DECL_خالص_P (newdecl) |= DECL_خالص_P (olddecl);
	  DECL_IS_NOVOPS (newdecl) |= DECL_IS_NOVOPS (olddecl);
	}

      /* Merge the storage class information.  */
      ملايو_weak (newdecl, olddecl);

      /* For functions, static overrides non-static.  */
      إذا (وڻ_ڪوڊ (newdecl) == FUNCTION_DECL)
	{
	  وڻ_عوامي (newdecl) &= وڻ_عوامي (olddecl);
	  /* This is since we don't automatically
	     copy the attributes of NEWDECL into OLDDECL.  */
	  وڻ_عوامي (olddecl) = وڻ_عوامي (newdecl);
	  /* If this clears `static', clear it in the identifier too.  */
	  إذا (!وڻ_عوامي (olddecl))
	    وڻ_عوامي (DECL_NAME (olddecl)) = 0;
	}
    }

  /* In c99, 'extern' declaration before (or after) 'inline' means this
     function is not DECL_EXTERNAL, unless 'gnu_inline' attribute
     is present.  */
  إذا (وڻ_ڪوڊ (newdecl) == FUNCTION_DECL
      && !flag_gnu89_inline
      && (DECL_DECLARED_INLINE_P (newdecl)
	  || DECL_DECLARED_INLINE_P (olddecl))
      && (!DECL_DECLARED_INLINE_P (newdecl)
	  || !DECL_DECLARED_INLINE_P (olddecl)
	  || !DECL_EXTERNAL (olddecl))
      && DECL_EXTERNAL (newdecl)
      && !lookup_attribute ("gnu_inline", DECL_خاصيتون (newdecl))
      && !current_function_decl)
    DECL_EXTERNAL (newdecl) = 0;

  /* An inline definition following a static declaration is not
     DECL_EXTERNAL.  */
  إذا (new_is_definition
      && (DECL_DECLARED_INLINE_P (newdecl)
	  || DECL_DECLARED_INLINE_P (olddecl))
      && !وڻ_عوامي (olddecl))
    DECL_EXTERNAL (newdecl) = 0;

  إذا (DECL_EXTERNAL (newdecl))
    {
      وڻ_STATIC (newdecl) = وڻ_STATIC (olddecl);
      DECL_EXTERNAL (newdecl) = DECL_EXTERNAL (olddecl);

      /* An extern decl does not override previous storage class.  */
      وڻ_عوامي (newdecl) = وڻ_عوامي (olddecl);
      إذا (!DECL_EXTERNAL (newdecl))
	{
	  DECL_CONTEXT (newdecl) = DECL_CONTEXT (olddecl);
	  DECL_COMMON (newdecl) = DECL_COMMON (olddecl);
	}
    }
  وإلا
    {
      وڻ_STATIC (olddecl) = وڻ_STATIC (newdecl);
      وڻ_عوامي (olddecl) = وڻ_عوامي (newdecl);
    }

  إذا (وڻ_ڪوڊ (newdecl) == FUNCTION_DECL)
    {
      إذا (DECL_FUNCTION_VERSIONED (olddecl)
	  || DECL_FUNCTION_VERSIONED (newdecl))
	{
	  maybe_mark_function_versioned (olddecl);
	  maybe_mark_function_versioned (newdecl);
	}
      /* If we're redefining a function previously defined as extern
	 inline, make sure we emit debug info for the inline before we
	 throw it away, in case it was inlined into a function that
	 hasn't been written out yet.  */
      إذا (new_is_definition && DECL_INITIAL (olddecl))
	/* The new defn must not be inline.  */
	DECL_UNINLINABLE (newdecl) = 1;
      وإلا
	{
	  /* If either decl says `inline', this fn is inline, unless
	     its definition was passed already.  */
	  إذا (DECL_DECLARED_INLINE_P (newdecl)
	      || DECL_DECLARED_INLINE_P (olddecl))
	    DECL_DECLARED_INLINE_P (newdecl) = 1;

	  DECL_UNINLINABLE (newdecl) = DECL_UNINLINABLE (olddecl)
	    = (DECL_UNINLINABLE (newdecl) || DECL_UNINLINABLE (olddecl));

	  DECL_DISREGARD_INLINE_LIMITS (newdecl)
	    = DECL_DISREGARD_INLINE_LIMITS (olddecl)
	    = (DECL_DISREGARD_INLINE_LIMITS (newdecl)
	       || DECL_DISREGARD_INLINE_LIMITS (olddecl));
	}

      إذا (fndecl_built_اندريون_p (olddecl))
	{
	  /* If redeclaring a builtin function, it stays built in.
	     But it gets tagged as having been declared.  */
	  copy_decl_built_اندريون_function (newdecl, olddecl);
	  C_DECL_DECLARED_BUILTIN (newdecl) = 1;
	  إذا (new_is_prototype)
	    {
	      C_DECL_BUILTIN_PROTOTYPE (newdecl) = 0;
	      إذا (DECL_BUILT_اندريون_CLASS (newdecl) == BUILT_اندريون_عام)
		{
		  تعداد built_اندريون_function fncode = DECL_FUNCTION_ڪوڊ (newdecl);
		  بدل (fncode)
		    {
		      /* If a compatible prototype of these builtin functions
			 is seen, assume the runtime implements it with the
			 expected semantics.  */
		    حالة BUILT_اندريون_STPCPY:
		      إذا (builtin_decl_explicit_p (fncode))
			سيٽ_builtin_decl_implicit_p (fncode, سچ);
		      اكسر;
		    افتراضي:
		      إذا (builtin_decl_explicit_p (fncode))
			سيٽ_builtin_decl_declared_p (fncode, سچ);
		      اكسر;
		    }

		  copy_خاصيتون_منزل_builtin (newdecl);
		}
	    }
	  وإلا
	    C_DECL_BUILTIN_PROTOTYPE (newdecl)
	      = C_DECL_BUILTIN_PROTOTYPE (olddecl);
	}

      /* Preserve function specific target and optimization options */
      إذا (DECL_FUNCTION_SPECIFIC_هدف (olddecl)
	  && !DECL_FUNCTION_SPECIFIC_هدف (newdecl))
	DECL_FUNCTION_SPECIFIC_هدف (newdecl)
	  = DECL_FUNCTION_SPECIFIC_هدف (olddecl);

      إذا (DECL_FUNCTION_SPECIFIC_OPTIMIZATION (olddecl)
	  && !DECL_FUNCTION_SPECIFIC_OPTIMIZATION (newdecl))
	DECL_FUNCTION_SPECIFIC_OPTIMIZATION (newdecl)
	  = DECL_FUNCTION_SPECIFIC_OPTIMIZATION (olddecl);

      /* Also preserve various other info from the definition.  */
      إذا (!new_is_definition)
	{
	  وڻ t;
	  DECL_نتيجو (newdecl) = DECL_نتيجو (olddecl);
	  DECL_INITIAL (newdecl) = DECL_INITIAL (olddecl);
	  DECL_STRUCT_FUNCTION (newdecl) = DECL_STRUCT_FUNCTION (olddecl);
	  DECL_SAVED_وڻ (newdecl) = DECL_SAVED_وڻ (olddecl);
	  DECL_ARGUMENTS (newdecl) = copy_list (DECL_ARGUMENTS (olddecl));
	  لكل (t = DECL_ARGUMENTS (newdecl); t ; t = DECL_CHAIN (t))
	    DECL_CONTEXT (t) = newdecl;

	  /* See if we've got a function to instantiate from.  */
	  إذا (DECL_SAVED_وڻ (olddecl))
	    DECL_ABSTRACT_ORIGIN (newdecl)
	      = DECL_ABSTRACT_ORIGIN (olddecl);
	}
    }

  /* Merge the USED information.  */
  إذا (وڻ_استعمال_ٿيل (olddecl))
    وڻ_استعمال_ٿيل (newdecl) = 1;
  وإلا إذا (وڻ_استعمال_ٿيل (newdecl))
    وڻ_استعمال_ٿيل (olddecl) = 1;
  إذا (VAR_P (olddecl) || وڻ_ڪوڊ (olddecl) == PARM_DECL)
    DECL_READ_P (newdecl) |= DECL_READ_P (olddecl);
  إذا (DECL_PRESERVE_P (olddecl))
    DECL_PRESERVE_P (newdecl) = 1;
  وإلا إذا (DECL_PRESERVE_P (newdecl))
    DECL_PRESERVE_P (olddecl) = 1;

  /* Merge DECL_COMMON */
  إذا (VAR_P (olddecl) && VAR_P (newdecl)
      && !lookup_attribute ("common", DECL_خاصيتون (newdecl))
      && !lookup_attribute ("nocommon", DECL_خاصيتون (newdecl)))
    DECL_COMMON (newdecl) = DECL_COMMON (newdecl) && DECL_COMMON (olddecl);

  /* Copy most of the decl-specific fields of NEWDECL into OLDDECL.
     But preserve OLDDECL's DECL_UID, DECL_CONTEXT and
     DECL_ARGUMENTS (if appropriate).  */
  {
    بنانشان olddecl_uid = DECL_UID (olddecl);
    وڻ olddecl_context = DECL_CONTEXT (olddecl);
    وڻ olddecl_arguments = عدم;
    إذا (وڻ_ڪوڊ (olddecl) == FUNCTION_DECL)
      olddecl_arguments = DECL_ARGUMENTS (olddecl);

    يادگيري_نقل ((حرف *) olddecl + حجم (بنية وڻ_common),
	    (حرف *) newdecl + حجم (بنية وڻ_common),
	    حجم (بنية وڻ_decl_common) - حجم (بنية وڻ_common));
    DECL_USER_ALIGN (olddecl) = DECL_USER_ALIGN (newdecl);
    بدل (وڻ_ڪوڊ (olddecl))
      {
      حالة FUNCTION_DECL:
      حالة VAR_DECL:
	{
	  بنية symtab_ڳنڍ *snode = olddecl->decl_with_vis.symtab_ڳنڍ;

	  يادگيري_نقل ((حرف *) olddecl + حجم (بنية وڻ_decl_common),
		  (حرف *) newdecl + حجم (بنية وڻ_decl_common),
		  وڻ_ڪوڊ_سائيز (وڻ_ڪوڊ (olddecl)) - حجم (بنية وڻ_decl_common));
	  olddecl->decl_with_vis.symtab_ڳنڍ = snode;

	  إذا ((DECL_EXTERNAL (olddecl)
	       || وڻ_عوامي (olddecl)
	       || وڻ_STATIC (olddecl))
	      && DECL_SECTION_NAME (newdecl) != عدم)
	    سيٽ_decl_section_name (olddecl, newdecl);

	  /* This isn't quite correct for something like
		int __thread x attribute ((tls_model ("local-exec")));
		extern int __thread x;
	     as we'll lose the "local-exec" model.  */
	  إذا (VAR_P (olddecl) && DECL_THREAD_LOCAL_P (newdecl))
	    سيٽ_decl_tls_model (olddecl, DECL_TLS_MODEL (newdecl));
	  اكسر;
	}

      حالة ميدان_DECL:
      حالة PARM_DECL:
      حالة LABEL_DECL:
      حالة نتيجو_DECL:
      حالة CONST_DECL:
      حالة TYPE_DECL:
	يادگيري_نقل ((حرف *) olddecl + حجم (بنية وڻ_decl_common),
		(حرف *) newdecl + حجم (بنية وڻ_decl_common),
		وڻ_ڪوڊ_سائيز (وڻ_ڪوڊ (olddecl)) - حجم (بنية وڻ_decl_common));
	اكسر;

      افتراضي:

	يادگيري_نقل ((حرف *) olddecl + حجم (بنية وڻ_decl_common),
		(حرف *) newdecl + حجم (بنية وڻ_decl_common),
		حجم (بنية وڻ_decl_non_common) - حجم (بنية وڻ_decl_common));
      }
    DECL_UID (olddecl) = olddecl_uid;
    DECL_CONTEXT (olddecl) = olddecl_context;
    إذا (وڻ_ڪوڊ (olddecl) == FUNCTION_DECL)
      DECL_ARGUMENTS (olddecl) = olddecl_arguments;
  }

  /* If OLDDECL had its DECL_RTL instantiated, re-invoke make_decl_rtl
     so that encode_section_info has a chance to look at the new decl
     flags and attributes.  */
  إذا (DECL_RTL_سيٽ_P (olddecl)
      && (وڻ_ڪوڊ (olddecl) == FUNCTION_DECL
	  || (VAR_P (olddecl) && وڻ_STATIC (olddecl))))
    make_decl_rtl (olddecl);
}

/* Handle when a new declaration NEWDECL has the same name as an old
   one OLDDECL in the same binding contour.  Prints an error message
   if appropriate.

   If safely possible, alter OLDDECL to look like NEWDECL, and return
   true.  Otherwise, return false.  */

ساكن منطقي
duplicate_decls (وڻ newdecl, وڻ olddecl)
{
  وڻ newtype = عدم, oldtype = عدم;

  إذا (!diagnose_mismatched_decls (newdecl, olddecl, &newtype, &oldtype))
    {
      /* Avoid `unused variable' and other warnings for OLDDECL.  */
      suppress_warning (olddecl, OPT_Wunused);
      /* If the types are completely different, poison them both with
 	 error_mark_node.  */
      إذا (وڻ_ڪوڊ (وڻ_TYPE (newdecl)) != وڻ_ڪوڊ (وڻ_TYPE (olddecl))
	  && olddecl != error_mark_ڳنڍ
	  && ڏٺل_error ())
	{
	  إذا (وڻ_ڪوڊ (olddecl) != FUNCTION_DECL)
	    وڻ_TYPE (olddecl) = error_mark_ڳنڍ;
	  إذا (وڻ_ڪوڊ (newdecl) != FUNCTION_DECL)
	    وڻ_TYPE (newdecl) = error_mark_ڳنڍ;
	}
      أرجع خطأ;
    }

  ملايو_decls (newdecl, olddecl, newtype, oldtype);

  /* The NEWDECL will no longer be needed.

     Before releasing the node, be sure to remove function from symbol
     table that might have been inserted there to record comdat group.
     Be sure to however do not free DECL_STRUCT_FUNCTION because this
     structure is shared in between NEWDECL and OLDECL.  */
  إذا (وڻ_ڪوڊ (newdecl) == FUNCTION_DECL)
    DECL_STRUCT_FUNCTION (newdecl) = عدم;
  إذا (VAR_OR_FUNCTION_DECL_P (newdecl))
    {
      بنية symtab_ڳنڍ *snode = symtab_ڳنڍ::get (newdecl);
      إذا (snode)
	snode->remove ();
    }
  ggc_free (newdecl);
  أرجع سچ;
}


/* Check whether decl-node NEW_DECL shadows an existing declaration.  */
ساكن فراغ
warn_if_shadowing (وڻ new_decl)
{
  بنية c_binding *b;

  /* Shadow warnings wanted?  */
  إذا (!(warn_shadow
        || warn_shadow_local
        || warn_shadow_compatible_local)
      /* No shadow warnings for internally generated vars.  */
      || DECL_IS_UNDECLARED_BUILTIN (new_decl))
    أرجع;

  /* Is anything being shadowed?  Invisible decls do not count.  */
  لكل (b = I_نشان_BINDING (DECL_NAME (new_decl)); b; b = b->shadowed)
    إذا (b->decl && b->decl != new_decl && !b->invisible
	&& (b->decl == error_mark_ڳنڍ
	    || diagnostic_report_warnings_p (global_dc,
					     DECL_ذريعو_LOCATION (b->decl))))
      {
	وڻ old_decl = b->decl;

	إذا (old_decl == error_mark_ڳنڍ)
	  {
	    warning (OPT_Wshadow, "declaration of %q+D shadows previous "
		     "non-variable", new_decl);
	    اكسر;
	  }

	منطقي warned = خطأ;
	auto_diagnostic_گروهه d;
	إذا (وڻ_ڪوڊ (old_decl) == PARM_DECL)
	  {
	    تعداد opt_ڪوڊ warning_ڪوڊ;

	    /* If '-Wshadow=compatible-local' is specified without other
	       -Wshadow= flags, we will warn only when the types of the
	       shadowing variable (i.e. new_decl) and the shadowed variable
	       (old_decl) are compatible.  */
	    إذا (warn_shadow)
	      warning_ڪوڊ = OPT_Wshadow;
	    وإلا إذا (comptypes (وڻ_TYPE (old_decl), وڻ_TYPE (new_decl)))
	      warning_ڪوڊ = OPT_Wshadow_compatible_local;
	    وإلا
	      warning_ڪوڊ = OPT_Wshadow_local;
	    warned = warning_at (DECL_ذريعو_LOCATION (new_decl), warning_ڪوڊ,
				 "declaration of %qD shadows a parameter",
				 new_decl);
	  }
	وإلا إذا (DECL_FILE_SCOPE_P (old_decl))
	  {
	    /* Do not warn if a variable shadows a function, unless
	       the variable is a function or a pointer-to-function.  */
	    إذا (وڻ_ڪوڊ (old_decl) == FUNCTION_DECL
		&& وڻ_ڪوڊ (new_decl) != FUNCTION_DECL
		&& !FUNCTION_اشارو_TYPE_P (وڻ_TYPE (new_decl)))
		استمر;

	    warned = warning_at (DECL_ذريعو_LOCATION (new_decl), OPT_Wshadow,
				 "declaration of %qD shadows a global "
				 "declaration",
				 new_decl);
	  }
	وإلا إذا (وڻ_ڪوڊ (old_decl) == FUNCTION_DECL
		 && fndecl_built_اندريون_p (old_decl))
	  {
	    warning (OPT_Wshadow, "declaration of %q+D shadows "
		     "a built-in function", new_decl);
	    اكسر;
	  }
	وإلا
	  {
	    تعداد opt_ڪوڊ warning_ڪوڊ;

	    /* If '-Wshadow=compatible-local' is specified without other
	       -Wshadow= flags, we will warn only when the types of the
	       shadowing variable (i.e. new_decl) and the shadowed variable
	       (old_decl) are compatible.  */
	    إذا (warn_shadow)
	      warning_ڪوڊ = OPT_Wshadow;
	    وإلا إذا (comptypes (وڻ_TYPE (old_decl), وڻ_TYPE (new_decl)))
	      warning_ڪوڊ = OPT_Wshadow_compatible_local;
	    وإلا
	      warning_ڪوڊ = OPT_Wshadow_local;
	    warned = warning_at (DECL_ذريعو_LOCATION (new_decl), warning_ڪوڊ,
				 "declaration of %qD shadows a previous local",
				 new_decl);
	  }

	إذا (warned)
	  inform (DECL_ذريعو_LOCATION (old_decl),
		  "shadowed declaration is here");

	اكسر;
      }
}

/* Record a decl-node X as belonging to the current lexical scope.
   Check for errors (such as an incompatible declaration for the same
   name already seen in the same scope).

   Returns either X or an old decl for the same name.
   If an old decl is returned, it may have been smashed
   to agree with what X says.  */

وڻ
pushdecl (وڻ x)
{
  وڻ name = DECL_NAME (x);
  بنية c_scope *scope = current_scope;
  بنية c_binding *b;
  منطقي nested = خطأ;
  location_t locus = DECL_ذريعو_LOCATION (x);

  /* Must set DECL_CONTEXT for everything not at file scope or
     DECL_FILE_SCOPE_P won't work.  Local externs don't count
     unless they have initializers (which generate code).  We
     also exclude CONST_DECLs because enumerators will get the
     type of the enum as context.  */
  إذا (current_function_decl
      && وڻ_ڪوڊ (x) != CONST_DECL
      && (!VAR_OR_FUNCTION_DECL_P (x)
	  || DECL_INITIAL (x) || !وڻ_عوامي (x)))
    DECL_CONTEXT (x) = current_function_decl;

  /* Anonymous decls are just inserted in the scope.  */
  إذا (!name)
    {
      bind (name, x, scope, /*invisible=*/خطأ, /*nested=*/خطأ,
	    locus);
      أرجع x;
    }

  /* First, see if there is another declaration with the same name in
     the current scope.  If there is, duplicate_decls may do all the
     work for us.  If duplicate_decls returns false, that indicates
     two incompatible decls in the same scope; we are to silently
     replace the old one (duplicate_decls has issued all appropriate
     diagnostics).  In particular, we should not consider possible
     duplicates in the external scope, or shadowing.  */
  b = I_نشان_BINDING (name);
  إذا (b && B_اندريون_SCOPE (b, scope))
    {
      بنية c_binding *b_ext, *b_use;
      وڻ type = وڻ_TYPE (x);
      وڻ visdecl = b->decl;
      وڻ vistype = وڻ_TYPE (visdecl);
      إذا (وڻ_ڪوڊ (وڻ_TYPE (x)) == ARRAY_TYPE
	  && COMPLETE_TYPE_P (وڻ_TYPE (x)))
	b->inner_comp = خطأ;
      b_use = b;
      b_ext = b;
      /* If this is an external linkage declaration, we should check
	 for compatibility with the type in the external scope before
	 setting the type at this scope based on the visible
	 information only.  */
      إذا (وڻ_عوامي (x) && وڻ_عوامي (visdecl))
	{
	  طالما (b_ext && !B_اندريون_EXTERNAL_SCOPE (b_ext))
	    b_ext = b_ext->shadowed;
	  إذا (b_ext)
	    {
	      b_use = b_ext;
	      إذا (b_use->u.type)
		وڻ_TYPE (b_use->decl) = b_use->u.type;
	    }
	}

      /* Check if x is part of a FMV set with b_use.
	 FMV is only supported in c for targets with target_version
	 attributes.  */
      إذا (!هدف_HAS_FMV_هدف_ATTRIBUTE
	  && b_use && وڻ_ڪوڊ (b_use->decl) == FUNCTION_DECL
	  && وڻ_ڪوڊ (x) == FUNCTION_DECL && DECL_FILE_SCOPE_P (b_use->decl)
	  && DECL_FILE_SCOPE_P (x)
	  && disjoint_نسخو_decls (x, b_use->decl)
	  && comptypes (vistype, type))
	{
	  maybe_mark_function_versioned (b_use->decl);
	  maybe_mark_function_versioned (b->decl);
	  maybe_mark_function_versioned (x);

	  cgraph_ڳنڍ *b_ڳنڍ = cgraph_ڳنڍ::get_create (b_use->decl);
	  cgraph_function_نسخو_info *b_v = b_ڳنڍ->function_نسخو ();
	  إذا (!b_v)
	    b_v = b_ڳنڍ->وجهو_new_function_نسخو ();

	  /* Check if this new node conflicts with any previous functions
	     in the set.  */
	  cgraph_function_نسخو_info *نسخو = b_v;
	  لكل (; نسخو; نسخو = نسخو->ايندڙ)
	    إذا (!disjoint_نسخو_decls (نسخو->this_ڳنڍ->decl, x))
	      {
		/* The decls define overlapping version, so attempt to merge
		   or diagnose the conflict.  */
		إذا (duplicate_decls (x, نسخو->this_ڳنڍ->decl))
		  أرجع نسخو->this_ڳنڍ->decl;
		وإلا
		  أرجع error_mark_ڳنڍ;
	      }

	  /* This is a new version to be added to FMV structure.  */
	  cgraph_ڳنڍ::جوڙيو_function_نسخو (b_v, x);

	  /* Get the first node from the structure.  */
	  cgraph_function_نسخو_info *default_v = b_v;
	  طالما (default_v->prev)
	    default_v = default_v->prev;
	  /* Always use the default node for the bindings.  */
	  b_use->decl = default_v->this_ڳنڍ->decl;
	  b->decl = default_v->this_ڳنڍ->decl;

	  /* Node is not a duplicate, so no need to do the rest of the
	     checks.  */
	  أرجع x;
	}

      إذا (duplicate_decls (x, b_use->decl))
	{
	  إذا (b_use != b)
	    {
	      /* Save the updated type in the external scope and
		 restore the proper type for this scope.  */
	      وڻ thistype;
	      إذا (comptypes (vistype, type))
		thistype = مرکب_type (vistype, type);
	      وإلا
		thistype = وڻ_TYPE (b_use->decl);
	      b_use->u.type = وڻ_TYPE (b_use->decl);
	      إذا (وڻ_ڪوڊ (b_use->decl) == FUNCTION_DECL
		  && fndecl_built_اندريون_p (b_use->decl))
		thistype
		  = c_build_type_attribute_variant (thistype,
						    TYPE_خاصيتون
						    (b_use->u.type));
	      وڻ_TYPE (b_use->decl) = thistype;
	    }
	  أرجع b_use->decl;
	}
      وإلا
	اذهب skip_external_and_shadow_checks;
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
  إذا ((DECL_EXTERNAL (x) || scope == file_scope)
      && (VAR_OR_FUNCTION_DECL_P (x) || c_dialect_objc ()))
    {
      وڻ type = وڻ_TYPE (x);
      وڻ vistype = NULL_وڻ;
      وڻ visdecl = NULL_وڻ;
      منطقي type_saved = خطأ;
      إذا (b && !B_اندريون_EXTERNAL_SCOPE (b)
	  && VAR_OR_FUNCTION_DECL_P (b->decl)
	  && DECL_FILE_SCOPE_P (b->decl))
	{
	  visdecl = b->decl;
	  vistype = وڻ_TYPE (visdecl);
	}
      إذا (scope != file_scope
	  && !DECL_اندريون_SYSTEM_سرو (x))
	warning_at (locus, OPT_Wnested_externs,
		    "nested extern declaration of %qD", x);

      طالما (b && !B_اندريون_EXTERNAL_SCOPE (b))
	{
	  /* If this decl might be modified, save its type.  This is
	     done here rather than when the decl is first bound
	     because the type may change after first binding, through
	     being completed or through attributes being added.  If we
	     encounter multiple such decls, only the first should have
	     its type saved; the others will already have had their
	     proper types saved and the types will not have changed as
	     their scopes will not have been re-entered.  */
	  إذا (DECL_P (b->decl) && DECL_FILE_SCOPE_P (b->decl) && !type_saved)
	    {
	      b->u.type = وڻ_TYPE (b->decl);
	      type_saved = سچ;
	    }
	  إذا (B_اندريون_FILE_SCOPE (b)
	      && VAR_P (b->decl)
	      && وڻ_STATIC (b->decl)
	      && وڻ_ڪوڊ (وڻ_TYPE (b->decl)) == ARRAY_TYPE
	      && !TYPE_DOMAIN (وڻ_TYPE (b->decl))
	      && وڻ_ڪوڊ (type) == ARRAY_TYPE
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
      إذا (b && b->u.type)
	وڻ_TYPE (b->decl) = b->u.type;

      /* the static does not go in the externals scope.  */
      إذا (b && duplicate_decls (x, b->decl))
	{
	  وڻ thistype;
	  إذا (vistype)
	    {
	      إذا (comptypes (vistype, type))
		thistype = مرکب_type (vistype, type);
	      وإلا
		thistype = وڻ_TYPE (b->decl);
	    }
	  وإلا
	    thistype = type;
	  b->u.type = وڻ_TYPE (b->decl);
	  /* Propagate the type attributes to the decl.  */
	  thistype
	    = c_build_type_attribute_variant (thistype,
					      TYPE_خاصيتون (b->u.type));
	  وڻ_TYPE (b->decl) = thistype;
	  bind (name, b->decl, scope, /*invisible=*/خطأ, /*nested=*/سچ,
		locus);
	  أرجع b->decl;
	}
      وإلا إذا (وڻ_عوامي (x))
	{
	  إذا (visdecl && !b && duplicate_decls (x, visdecl))
	    {
	      /* An external declaration at block scope referring to a
		 visible entity with internal linkage.  The composite
		 type will already be correct for this scope, so we
		 just need to fall through to make the declaration in
		 this scope.  */
	      nested = سچ;
	      x = visdecl;
	    }
	  وإلا
	    {
	      bind (name, x, external_scope, /*invisible=*/سچ,
		    /*nested=*/خطأ, locus);
	      nested = سچ;
	    }
	}
    }

  إذا (وڻ_ڪوڊ (x) != PARM_DECL)
    warn_if_shadowing (x);

 skip_external_and_shadow_checks:
  إذا (وڻ_ڪوڊ (x) == TYPE_DECL)
    {
      /* So this is a typedef, set its underlying type.  */
      سيٽ_underlying_type (x);

      /* If X is a typedef defined in the current function, record it
	 for the purpose of implementing the -Wunused-local-typedefs
	 warning.  */
      رڪارڊ_locally_defined_typedef (x);
    }

  bind (name, x, scope, /*invisible=*/خطأ, nested, locus);

  /* If x's type is incomplete because it's based on a
     structure or union which has not yet been fully declared,
     attach it to that structure or union type, so we can go
     back and complete the variable declaration later, if the
     structure or union gets fully declared.

     If the input is erroneous, we can have error_mark in the type
     slot (e.g. "f(void a, ...)") - that doesn't count as an
     incomplete type.  */
  إذا (وڻ_TYPE (x) != error_mark_ڳنڍ
      && !COMPLETE_TYPE_P (وڻ_TYPE (x)))
    {
      وڻ element = وڻ_TYPE (x);

      طالما (وڻ_ڪوڊ (element) == ARRAY_TYPE)
	element = وڻ_TYPE (element);
      element = TYPE_MAIN_VARIANT (element);

      إذا ((رڪارڊ_OR_UNION_TYPE_P (element)
	   || وڻ_ڪوڊ (element) == ENUMERAL_TYPE)
	  && (وڻ_ڪوڊ (x) != TYPE_DECL
	      || وڻ_ڪوڊ (وڻ_TYPE (x)) == ARRAY_TYPE)
	  && !COMPLETE_TYPE_P (element))
	C_TYPE_INCOMPLETE_VARS (element)
	  = وڻ_cons (NULL_وڻ, x, C_TYPE_INCOMPLETE_VARS (element));
    }
  أرجع x;
}


/* Issue a permerror about implicit function declaration.  ID is the function
   identifier, OLDDECL is a declaration of the function in a different scope,
   or NULL_TREE.  */

ساكن فراغ
implicit_decl_permerror (location_t loc, وڻ id, وڻ olddecl)
{
  إذا (!warn_implicit_function_declaration)
    أرجع;

  منطقي warned;
  auto_diagnostic_گروهه d;
  name_hint hint;
  إذا (!olddecl)
    hint = lookup_name_fuzzy (id, FUZZY_LOOKUP_FUNCTION_NAME, loc);

  إذا (flag_isoc99)
    {
      إذا (ثابت حرف *suggestion = hint.suggestion ())
	{
	  gcc_rich_location richloc (loc);
	  richloc.جوڙيو_fixit_replace (suggestion);
	  warned = permerror_opt (&richloc, OPT_Wimplicit_function_declaration,
				  "implicit declaration of function %qE;"
				  " did you mean %qs?",
				  id, suggestion);
	}
      وإلا
	warned = permerror_opt (loc, OPT_Wimplicit_function_declaration,
				"implicit declaration of function %qE", id);
    }
  وإلا إذا (ثابت حرف *suggestion = hint.suggestion ())
    {
      gcc_rich_location richloc (loc);
      richloc.جوڙيو_fixit_replace (suggestion);
      warned = warning_at
	(&richloc, OPT_Wimplicit_function_declaration,
	 G_("implicit declaration of function %qE; did you mean %qs?"),
	 id, suggestion);
    }
  وإلا
    warned = warning_at (loc, OPT_Wimplicit_function_declaration,
			 G_("implicit declaration of function %qE"), id);

  إذا (warned)
    {
      /* Whether the olddecl is an undeclared builtin function.
	 locate_old_decl will not generate a diagnostic for those,
	 so in that case we want to look elsewhere.  */
      منطقي undeclared_builtin = (olddecl
				 && وڻ_ڪوڊ (olddecl) == FUNCTION_DECL
				 && fndecl_built_اندريون_p (olddecl)
				 && !C_DECL_DECLARED_BUILTIN (olddecl));
      إذا (undeclared_builtin)
	{
	  ثابت حرف *سرو = سرو_for_builtin_fn (olddecl);
	  إذا (سرو)
	    {
	      rich_location richloc (سٽ_جدول, loc);
	      maybe_جوڙيو_include_fixit (&richloc, سرو, سچ);
	      inform (&richloc,
		      "include %qs or provide a declaration of %qE",
		      سرو, id);
	    }
	}
      وإلا إذا (olddecl)
	locate_old_decl (olddecl);
    }

  إذا (!warned)
    hint.suppress ();
}

/* Return the name of the header file that declares built-in function
   FNDECL, or null if either we don't know or don't expect to see an
   explicit declaration.  */

ساكن ثابت حرف *
سرو_for_builtin_fn (وڻ fndecl)
{
  إذا (DECL_BUILT_اندريون_CLASS (fndecl) != BUILT_اندريون_عام)
    أرجع عدم;

  بدل (DECL_FUNCTION_ڪوڊ (fndecl))
    {
    CASE_FLT_FN (BUILT_اندريون_ACOS):
    CASE_FLT_FN (BUILT_اندريون_ACOSH):
    CASE_FLT_FN (BUILT_اندريون_ASIN):
    CASE_FLT_FN (BUILT_اندريون_ASINH):
    CASE_FLT_FN (BUILT_اندريون_ATAN):
    CASE_FLT_FN (BUILT_اندريون_ATANH):
    CASE_FLT_FN (BUILT_اندريون_ATAN2):
    CASE_FLT_FN (BUILT_اندريون_CBRT):
    CASE_FLT_FN (BUILT_اندريون_CEIL):
    CASE_FLT_FN_FLOATN_NX (BUILT_اندريون_CEIL):
    CASE_FLT_FN (BUILT_اندريون_COPYSIGN):
    CASE_FLT_FN_FLOATN_NX (BUILT_اندريون_COPYSIGN):
    CASE_FLT_FN (BUILT_اندريون_COS):
    CASE_FLT_FN (BUILT_اندريون_COSH):
    CASE_FLT_FN (BUILT_اندريون_ERF):
    CASE_FLT_FN (BUILT_اندريون_ERFC):
    CASE_FLT_FN (BUILT_اندريون_EXP):
    CASE_FLT_FN (BUILT_اندريون_EXP2):
    CASE_FLT_FN (BUILT_اندريون_EXPM1):
    CASE_FLT_FN (BUILT_اندريون_FABS):
    CASE_FLT_FN_FLOATN_NX (BUILT_اندريون_FABS):
    CASE_FLT_FN (BUILT_اندريون_FDIM):
    CASE_FLT_FN (BUILT_اندريون_FLOOR):
    CASE_FLT_FN_FLOATN_NX (BUILT_اندريون_FLOOR):
    CASE_FLT_FN (BUILT_اندريون_FMA):
    CASE_FLT_FN_FLOATN_NX (BUILT_اندريون_FMA):
    CASE_FLT_FN (BUILT_اندريون_FMAX):
    CASE_FLT_FN_FLOATN_NX (BUILT_اندريون_FMAX):
    CASE_FLT_FN (BUILT_اندريون_FMIN):
    CASE_FLT_FN_FLOATN_NX (BUILT_اندريون_FMIN):
    CASE_FLT_FN (BUILT_اندريون_FMOD):
    CASE_FLT_FN (BUILT_اندريون_FREXP):
    CASE_FLT_FN (BUILT_اندريون_HYPOT):
    CASE_FLT_FN (BUILT_اندريون_ILOGB):
    CASE_FLT_FN (BUILT_اندريون_LDEXP):
    CASE_FLT_FN (BUILT_اندريون_LGAMMA):
    CASE_FLT_FN (BUILT_اندريون_LLRINT):
    CASE_FLT_FN (BUILT_اندريون_LLROUND):
    CASE_FLT_FN (BUILT_اندريون_LOG):
    CASE_FLT_FN (BUILT_اندريون_LOG10):
    CASE_FLT_FN (BUILT_اندريون_LOG1_P):
    CASE_FLT_FN (BUILT_اندريون_LOG2):
    CASE_FLT_FN (BUILT_اندريون_LOGB):
    CASE_FLT_FN (BUILT_اندريون_LRINT):
    CASE_FLT_FN (BUILT_اندريون_LROUND):
    CASE_FLT_FN (BUILT_اندريون_MODF):
    CASE_FLT_FN (BUILT_اندريون_NAN):
    CASE_FLT_FN (BUILT_اندريون_NEARBYINT):
    CASE_FLT_FN_FLOATN_NX (BUILT_اندريون_NEARBYINT):
    CASE_FLT_FN (BUILT_اندريون_NEXTAFTER):
    CASE_FLT_FN (BUILT_اندريون_NEXTTOWARD):
    CASE_FLT_FN (BUILT_اندريون_POW):
    CASE_FLT_FN (BUILT_اندريون_REMAINDER):
    CASE_FLT_FN (BUILT_اندريون_REMQUO):
    CASE_FLT_FN (BUILT_اندريون_RINT):
    CASE_FLT_FN_FLOATN_NX (BUILT_اندريون_RINT):
    CASE_FLT_FN (BUILT_اندريون_ڦيرو):
    CASE_FLT_FN_FLOATN_NX (BUILT_اندريون_ڦيرو):
    CASE_FLT_FN (BUILT_اندريون_SCALBLN):
    CASE_FLT_FN (BUILT_اندريون_SCALBN):
    CASE_FLT_FN (BUILT_اندريون_SIN):
    CASE_FLT_FN (BUILT_اندريون_SINH):
    CASE_FLT_FN (BUILT_اندريون_SINCOS):
    CASE_FLT_FN (BUILT_اندريون_SQRT):
    CASE_FLT_FN_FLOATN_NX (BUILT_اندريون_SQRT):
    CASE_FLT_FN (BUILT_اندريون_TAN):
    CASE_FLT_FN (BUILT_اندريون_TANH):
    CASE_FLT_FN (BUILT_اندريون_TGAMMA):
    CASE_FLT_FN (BUILT_اندريون_TRUNC):
    CASE_FLT_FN_FLOATN_NX (BUILT_اندريون_TRUNC):
    حالة BUILT_اندريون_ISINF:
    حالة BUILT_اندريون_ISNAN:
      أرجع "<math.h>";
    CASE_FLT_FN (BUILT_اندريون_CABS):
    CASE_FLT_FN (BUILT_اندريون_CACOS):
    CASE_FLT_FN (BUILT_اندريون_CACOSH):
    CASE_FLT_FN (BUILT_اندريون_CARG):
    CASE_FLT_FN (BUILT_اندريون_CASIN):
    CASE_FLT_FN (BUILT_اندريون_CASINH):
    CASE_FLT_FN (BUILT_اندريون_CATAN):
    CASE_FLT_FN (BUILT_اندريون_CATANH):
    CASE_FLT_FN (BUILT_اندريون_CCOS):
    CASE_FLT_FN (BUILT_اندريون_CCOSH):
    CASE_FLT_FN (BUILT_اندريون_CEXP):
    CASE_FLT_FN (BUILT_اندريون_CIMAG):
    CASE_FLT_FN (BUILT_اندريون_CLOG):
    CASE_FLT_FN (BUILT_اندريون_CONJ):
    CASE_FLT_FN (BUILT_اندريون_CPOW):
    CASE_FLT_FN (BUILT_اندريون_CPROJ):
    CASE_FLT_FN (BUILT_اندريون_CREAL):
    CASE_FLT_FN (BUILT_اندريون_CSIN):
    CASE_FLT_FN (BUILT_اندريون_CSINH):
    CASE_FLT_FN (BUILT_اندريون_CSQRT):
    CASE_FLT_FN (BUILT_اندريون_CTAN):
    CASE_FLT_FN (BUILT_اندريون_CTANH):
      أرجع "<complex.h>";
    حالة BUILT_اندريون_MEMCHR:
    حالة BUILT_اندريون_MEMCMP:
    حالة BUILT_اندريون_MEMCPY:
    حالة BUILT_اندريون_MEMMOVE:
    حالة BUILT_اندريون_MEMSET:
    حالة BUILT_اندريون_STRCAT:
    حالة BUILT_اندريون_STRCHR:
    حالة BUILT_اندريون_STRCMP:
    حالة BUILT_اندريون_STRCPY:
    حالة BUILT_اندريون_STRCSPN:
    حالة BUILT_اندريون_STRLEN:
    حالة BUILT_اندريون_STRNCAT:
    حالة BUILT_اندريون_STRNCMP:
    حالة BUILT_اندريون_STRNCPY:
    حالة BUILT_اندريون_STRPBRK:
    حالة BUILT_اندريون_STRRCHR:
    حالة BUILT_اندريون_STRSPN:
    حالة BUILT_اندريون_STRSTR:
      أرجع "<string.h>";
    حالة BUILT_اندريون_FPRINTF:
    حالة BUILT_اندريون_PUTC:
    حالة BUILT_اندريون_FPUTC:
    حالة BUILT_اندريون_FPUTS:
    حالة BUILT_اندريون_FSCANF:
    حالة BUILT_اندريون_FWRITE:
    حالة BUILT_اندريون_PRINTF:
    حالة BUILT_اندريون_PUTCHAR:
    حالة BUILT_اندريون_PUTS:
    حالة BUILT_اندريون_SCANF:
    حالة BUILT_اندريون_SNPRINTF:
    حالة BUILT_اندريون_SPRINTF:
    حالة BUILT_اندريون_SSCANF:
    حالة BUILT_اندريون_VFPRINTF:
    حالة BUILT_اندريون_VFSCANF:
    حالة BUILT_اندريون_VPRINTF:
    حالة BUILT_اندريون_VSCANF:
    حالة BUILT_اندريون_VSNPRINTF:
    حالة BUILT_اندريون_VSPRINTF:
    حالة BUILT_اندريون_VSSCANF:
      أرجع "<stdio.h>";
    حالة BUILT_اندريون_ISALNUM:
    حالة BUILT_اندريون_ISALPHA:
    حالة BUILT_اندريون_ISBLANK:
    حالة BUILT_اندريون_ISCNTRL:
    حالة BUILT_اندريون_ISDIGIT:
    حالة BUILT_اندريون_ISGRAPH:
    حالة BUILT_اندريون_ISLOWER:
    حالة BUILT_اندريون_ISPRINT:
    حالة BUILT_اندريون_ISPUNCT:
    حالة BUILT_اندريون_ISSPACE:
    حالة BUILT_اندريون_ISUPPER:
    حالة BUILT_اندريون_ISXDIGIT:
    حالة BUILT_اندريون_TOLOWER:
    حالة BUILT_اندريون_TOUPPER:
      أرجع "<ctype.h>";
    حالة BUILT_اندريون_ISWALNUM:
    حالة BUILT_اندريون_ISWALPHA:
    حالة BUILT_اندريون_ISWBLANK:
    حالة BUILT_اندريون_ISWCNTRL:
    حالة BUILT_اندريون_ISWDIGIT:
    حالة BUILT_اندريون_ISWGRAPH:
    حالة BUILT_اندريون_ISWLOWER:
    حالة BUILT_اندريون_ISWPRINT:
    حالة BUILT_اندريون_ISWPUNCT:
    حالة BUILT_اندريون_ISWSPACE:
    حالة BUILT_اندريون_ISWUPPER:
    حالة BUILT_اندريون_ISWXDIGIT:
    حالة BUILT_اندريون_TOWLOWER:
    حالة BUILT_اندريون_TOWUPPER:
      أرجع "<wctype.h>";
    حالة BUILT_اندريون_ABORT:
    حالة BUILT_اندريون_ABS:
    حالة BUILT_اندريون_CALLOC:
    حالة BUILT_اندريون_EXIT:
    حالة BUILT_اندريون_FREE:
    حالة BUILT_اندريون_LABS:
    حالة BUILT_اندريون_LLABS:
    حالة BUILT_اندريون_MALLOC:
    حالة BUILT_اندريون_REALLOC:
    حالة BUILT_اندريون_EXIT2:
    حالة BUILT_اندريون_ALIGNED_ALLOC:
      أرجع "<stdlib.h>";
    حالة BUILT_اندريون_IMAXABS:
      أرجع "<inttypes.h>";
    حالة BUILT_اندريون_STRFTIME:
      أرجع "<time.h>";
    افتراضي:
      أرجع عدم;
    }
}

/* Generate an implicit declaration for identifier FUNCTIONID at LOC as a
   function of type int ().  */

وڻ
implicitly_declare (location_t loc, وڻ functionid)
{
  بنية c_binding *b;
  وڻ decl = NULL_وڻ;
  وڻ asmspec_وڻ;

  لكل (b = I_نشان_BINDING (functionid); b; b = b->shadowed)
    {
      إذا (B_اندريون_SCOPE (b, external_scope))
	{
	  decl = b->decl;
	  اكسر;
	}
    }

  إذا (decl)
    {
      إذا (وڻ_ڪوڊ (decl) != FUNCTION_DECL)
	أرجع decl;

      /* FIXME: Objective-C has weird not-really-builtin functions
	 which are supposed to be visible automatically.  They wind up
	 in the external scope because they're pushed before the file
	 scope gets created.  Catch this here and rebind them into the
	 file scope.  */
      إذا (!fndecl_built_اندريون_p (decl) && DECL_IS_UNDECLARED_BUILTIN (decl))
	{
	  bind (functionid, decl, file_scope,
		/*invisible=*/خطأ, /*nested=*/سچ,
		DECL_ذريعو_LOCATION (decl));
	  أرجع decl;
	}
      وإلا
	{
	  وڻ newtype = default_function_type;
	  إذا (b->u.type)
	    وڻ_TYPE (decl) = b->u.type;
	  /* Implicit declaration of a function already declared
	     (somehow) in a different scope, or as a built-in.
	     If this is the first time this has happened, warn;
	     then recycle the old declaration but with the new type.  */
	  إذا (!C_DECL_IMPLICIT (decl))
	    {
	      implicit_decl_permerror (loc, functionid, decl);
	      C_DECL_IMPLICIT (decl) = 1;
	    }
	  إذا (fndecl_built_اندريون_p (decl))
	    {
	      newtype = c_build_type_attribute_variant (newtype,
							TYPE_خاصيتون
							(وڻ_TYPE (decl)));
	      إذا (!comptypes (newtype, وڻ_TYPE (decl)))
		{
		  auto_diagnostic_گروهه d;
		  منطقي warned = warning_at (loc,
					    OPT_Wbuiltin_declaration_mismatch,
					    "incompatible implicit "
					    "declaration of built-in "
					    "function %qD", decl);
		  /* See if we can hint which header to include.  */
		  ثابت حرف *سرو = سرو_for_builtin_fn (decl);
		  إذا (سرو != عدم && warned)
		    {
		      rich_location richloc (سٽ_جدول, loc);
		      maybe_جوڙيو_include_fixit (&richloc, سرو, سچ);
		      inform (&richloc,
			      "include %qs or provide a declaration of %qD",
			      سرو, decl);
		    }
		  newtype = وڻ_TYPE (decl);
		}
	    }
	  وإلا
	    {
	      إذا (!comptypes (newtype, وڻ_TYPE (decl)))
		{
		  auto_diagnostic_گروهه d;
		  error_at (loc, "incompatible implicit declaration of "
			    "function %qD", decl);
		  locate_old_decl (decl);
		}
	    }
	  b->u.type = وڻ_TYPE (decl);
	  وڻ_TYPE (decl) = newtype;
	  bind (functionid, decl, current_scope,
		/*invisible=*/خطأ, /*nested=*/سچ,
		DECL_ذريعو_LOCATION (decl));
	  أرجع decl;
	}
    }

  /* Not seen before.  */
  decl = build_decl (loc, FUNCTION_DECL, functionid, default_function_type);
  DECL_EXTERNAL (decl) = 1;
  وڻ_عوامي (decl) = 1;
  C_DECL_IMPLICIT (decl) = 1;
  implicit_decl_permerror (loc, functionid, 0);
  asmspec_وڻ = maybe_apply_renaming_pragma (decl, /*asmname=*/عدم);
  إذا (asmspec_وڻ)
    سيٽ_user_assembler_name (decl, وڻ_STRING_اشارو (asmspec_وڻ));

  /* C89 says implicit declarations are in the innermost block.
     So we record the decl in the standard fashion.  */
  decl = pushdecl (decl);

  /* No need to call objc_check_decl here - it's a function type.  */
  rest_جو_decl_compilation (decl, 0, 0);

  /* Write a record describing this implicit function declaration
     to the prototypes file (if requested).  */
  gen_aux_info_رڪارڊ (decl, 0, 1, 0);

  /* Possibly apply some default attributes to this implicit declaration.  */
  decl_خاصيتون (&decl, NULL_وڻ, 0);

  أرجع decl;
}

/* Issue an error message for a reference to an undeclared variable
   ID, including a reference to a builtin outside of function-call
   context.  Establish a binding of the identifier to error_mark_node
   in an appropriate scope, which will suppress further errors for the
   same identifier.  The error message should be given location LOC.  */
فراغ
undeclared_variable (location_t loc, وڻ id)
{
  ساكن منطقي already = خطأ;
  بنية c_scope *scope;

  auto_diagnostic_گروهه d;
  إذا (current_function_decl == NULL_وڻ)
    {
      name_hint guessed_id = lookup_name_fuzzy (id, FUZZY_LOOKUP_NAME, loc);
      إذا (ثابت حرف *suggestion = guessed_id.suggestion ())
	{
	  gcc_rich_location richloc (loc);
	  richloc.جوڙيو_fixit_replace (suggestion);
	  error_at (&richloc,
		    "%qE undeclared here (not in a function);"
		    " did you mean %qs?",
		    id, suggestion);
	}
      وإلا
	error_at (loc, "%qE undeclared here (not in a function)", id);
      scope = current_scope;
    }
  وإلا
    {
      إذا (!objc_diagnose_ذاتي_ivar (id))
	{
	  name_hint guessed_id = lookup_name_fuzzy (id, FUZZY_LOOKUP_NAME, loc);
	  إذا (ثابت حرف *suggestion = guessed_id.suggestion ())
	    {
	      gcc_rich_location richloc (loc);
	      richloc.جوڙيو_fixit_replace (suggestion);
	      error_at (&richloc,
			"%qE undeclared (first use in this function);"
			" did you mean %qs?",
			id, suggestion);
	    }
	  وإلا
	    error_at (loc, "%qE undeclared (first use in this function)", id);
	}
      إذا (!already)
	{
          inform (loc, "each undeclared identifier is reported only"
                  " once for each function it appears in");
	  already = سچ;
	}

      /* If we are parsing old-style parameter decls, current_function_decl
	 will be nonnull but current_function_scope will be null.  */
      scope = current_function_scope ? current_function_scope : current_scope;
    }
  bind (id, error_mark_ڳنڍ, scope, /*invisible=*/خطأ, /*nested=*/خطأ,
	UNKNOWN_LOCATION);
}

/* Subroutine of lookup_label, declare_label, define_label: construct a
   LABEL_DECL with all the proper frills.  Also create a struct
   c_label_vars initialized for the current scope.  */

ساكن وڻ
make_label (location_t location, وڻ name, منطقي defining,
	    بنية c_label_vars **p_label_vars)
{
  وڻ label = build_decl (location, LABEL_DECL, name, void_type_ڳنڍ);
  DECL_CONTEXT (label) = current_function_decl;
  سيٽ_DECL_گهڻائي (label, VOIDmode);

  c_label_vars *label_vars = ggc_alloc<c_label_vars> ();
  label_vars->shadowed = عدم;
  سيٽ_spot_bindings (&label_vars->label_bindings, defining);
  label_vars->decls_اندريون_scope = make_وڻ_ويڪٽر ();
  label_vars->gotos = عدم;
  *p_label_vars = label_vars;

  أرجع label;
}

/* Get the LABEL_DECL corresponding to identifier NAME as a label.
   Create one if none exists so far for the current function.
   This is called when a label is used in a goto expression or
   has its address taken.  */

وڻ
lookup_label (وڻ name)
{
  وڻ label;
  بنية c_label_vars *label_vars;

  إذا (current_function_scope == 0)
    {
      error ("label %qE referenced outside of any function", name);
      أرجع NULL_وڻ;
    }

  /* Use a label already defined or ref'd with this name, but not if
     it is inherited from a containing function and wasn't declared
     using __label__.  */
  label = I_LABEL_DECL (name);
  إذا (label && (DECL_CONTEXT (label) == current_function_decl
		|| C_DECLARED_LABEL_FLAG (label)))
    {
      /* If the label has only been declared, update its apparent
	 location to point here, for better diagnostics if it
	 turns out not to have been defined.  */
      إذا (DECL_INITIAL (label) == NULL_وڻ)
	DECL_ذريعو_LOCATION (label) = داخلا_location;
      أرجع label;
    }

  /* No label binding for that identifier; make one.  */
  label = make_label (داخلا_location, name, خطأ, &label_vars);

  /* Ordinary labels go in the current function scope.  */
  bind_label (name, label, current_function_scope, label_vars);

  أرجع label;
}

/* Issue a warning about DECL for a goto statement at GOTO_LOC going
   to LABEL.  */

ساكن فراغ
warn_about_goto (location_t goto_loc, وڻ label, وڻ decl)
{
  auto_diagnostic_گروهه d;
  إذا (c_type_variably_modified_p (وڻ_TYPE (decl)))
    error_at (goto_loc,
	      "jump into scope of identifier with variably modified type");
  وإلا إذا (flag_openmp
	   && lookup_attribute ("omp allocate", DECL_خاصيتون (decl)))
    error_at (goto_loc, "jump skips OpenMP %<allocate%> allocation");
  وإلا
    إذا (!warning_at (goto_loc, OPT_Wjump_ناڪاميون_init,
		     "jump skips variable initialization"))
      أرجع;
  inform (DECL_ذريعو_LOCATION (label), "label %qD defined here", label);
  inform (DECL_ذريعو_LOCATION (decl), "%qD declared here", decl);
}

/* Look up a label because of a goto statement.  This is like
   lookup_label, but also issues any appropriate warnings.  */

وڻ
lookup_label_for_goto (location_t loc, وڻ name)
{
  وڻ label;
  بنية c_label_vars *label_vars;
  بنانشان صحيح ix;
  وڻ decl;

  label = lookup_label (name);
  إذا (label == NULL_وڻ)
    أرجع NULL_وڻ;

  /* If we are jumping to a different function, we can't issue any
     useful warnings.  */
  إذا (DECL_CONTEXT (label) != current_function_decl)
    {
      gcc_assert (C_DECLARED_LABEL_FLAG (label));
      أرجع label;
    }

  label_vars = I_LABEL_BINDING (name)->u.label;

  /* If the label has not yet been defined, then push this goto on a
     list for possible later warnings.  */
  إذا (label_vars->label_bindings.scope == عدم)
    {
      c_goto_bindings *g = ggc_alloc<c_goto_bindings> ();

      g->loc = loc;
      سيٽ_spot_bindings (&g->goto_bindings, سچ);
      vec_محفوظ_ڌڪو (label_vars->gotos, g);
      أرجع label;
    }

  /* If there are any decls in label_vars->decls_in_scope, then this
     goto has missed the declaration of the decl.  This happens for a
     case like
       int i = 1;
      lab:
       ...
       goto lab;
     Issue a warning or error.  */
  FOR_EACH_VEC_محفوظ_ELT (label_vars->decls_اندريون_scope, ix, decl)
    warn_about_goto (loc, label, decl);

  إذا (label_vars->label_bindings.کاٻو_stmt_اظهار)
    {
      auto_diagnostic_گروهه d;
      error_at (loc, "jump into statement expression");
      inform (DECL_ذريعو_LOCATION (label), "label %qD defined here", label);
    }

  أرجع label;
}

/* Make a label named NAME in the current function, shadowing silently
   any that may be inherited from containing functions or containing
   scopes.  This is called for __label__ declarations.  */

وڻ
declare_label (وڻ name)
{
  بنية c_binding *b = I_LABEL_BINDING (name);
  وڻ label;
  بنية c_label_vars *label_vars;

  /* Check to make sure that the label hasn't already been declared
     at this scope */
  إذا (b && B_اندريون_CURRENT_SCOPE (b))
    {
      auto_diagnostic_گروهه d;
      error ("duplicate label declaration %qE", name);
      locate_old_decl (b->decl);

      /* Just use the previous declaration.  */
      أرجع b->decl;
    }

  label = make_label (داخلا_location, name, خطأ, &label_vars);
  C_DECLARED_LABEL_FLAG (label) = 1;

  /* Declared labels go in the current scope.  */
  bind_label (name, label, current_scope, label_vars);

  أرجع label;
}

/* When we define a label, issue any appropriate warnings if there are
   any gotos earlier in the function which jump to this label.  */

ساكن فراغ
check_earlier_gotos (وڻ label, بنية c_label_vars* label_vars)
{
  بنانشان صحيح ix;
  بنية c_goto_bindings *g;

  FOR_EACH_VEC_محفوظ_ELT (label_vars->gotos, ix, g)
    {
      بنية c_binding *b;
      بنية c_scope *scope;

      /* We have a goto to this label.  The goto is going forward.  In
	 g->scope, the goto is going to skip any binding which was
	 defined after g->bindings_in_scope.  */
      إذا (g->goto_bindings.scope->has_jump_unsafe_decl)
	{
	  لكل (b = g->goto_bindings.scope->bindings;
	       b != g->goto_bindings.bindings_اندريون_scope;
	       b = b->prev)
	    {
	      إذا (decl_jump_unsafe (b->decl))
		warn_about_goto (g->loc, label, b->decl);
	    }
	}

      /* We also need to warn about decls defined in any scopes
	 between the scope of the label and the scope of the goto.  */
      لكل (scope = label_vars->label_bindings.scope;
	   scope != g->goto_bindings.scope;
	   scope = scope->outer)
	{
	  gcc_assert (scope != عدم);
	  إذا (scope->has_jump_unsafe_decl)
	    {
	      إذا (scope == label_vars->label_bindings.scope)
		b = label_vars->label_bindings.bindings_اندريون_scope;
	      وإلا
		b = scope->bindings;
	      لكل (; b != عدم; b = b->prev)
		{
		  إذا (decl_jump_unsafe (b->decl))
		    warn_about_goto (g->loc, label, b->decl);
		}
	    }
	}

      إذا (g->goto_bindings.stmt_exprs > 0)
	{
	  auto_diagnostic_گروهه d;
	  error_at (g->loc, "jump into statement expression");
	  inform (DECL_ذريعو_LOCATION (label), "label %qD defined here",
		  label);
	}
    }

  /* Now that the label is defined, we will issue warnings about
     subsequent gotos to this label when we see them.  */
  vec_محفوظ_truncate (label_vars->gotos, 0);
  label_vars->gotos = عدم;
}

/* Define a label, specifying the location in the source file.
   Return the LABEL_DECL node for the label, if the definition is valid.
   Otherwise return NULL_TREE.  */

وڻ
define_label (location_t location, وڻ name)
{
  /* Find any preexisting label with this name.  It is an error
     if that label has already been defined in this function, or
     if there is a containing function with a declared label with
     the same name.  */
  وڻ label = I_LABEL_DECL (name);

  إذا (label
      && ((DECL_CONTEXT (label) == current_function_decl
	   && DECL_INITIAL (label) != NULL_وڻ)
	  || (DECL_CONTEXT (label) != current_function_decl
	      && C_DECLARED_LABEL_FLAG (label))))
    {
      auto_diagnostic_گروهه d;
      error_at (location, "duplicate label %qD", label);
      locate_old_decl (label);
      أرجع NULL_وڻ;
    }
  وإلا إذا (label && DECL_CONTEXT (label) == current_function_decl)
    {
      بنية c_label_vars *label_vars = I_LABEL_BINDING (name)->u.label;

      /* The label has been used or declared already in this function,
	 but not defined.  Update its location to point to this
	 definition.  */
      DECL_ذريعو_LOCATION (label) = location;
      سيٽ_spot_bindings (&label_vars->label_bindings, سچ);

      /* Issue warnings as required about any goto statements from
	 earlier in the function.  */
      check_earlier_gotos (label, label_vars);
    }
  وإلا
    {
      بنية c_label_vars *label_vars;

      /* No label binding for that identifier; make one.  */
      label = make_label (location, name, سچ, &label_vars);

      /* Ordinary labels go in the current function scope.  */
      bind_label (name, label, current_function_scope, label_vars);
    }

  إذا (!اندريون_system_سرو_at (داخلا_location) && lookup_name (name))
    warning_at (location, OPT_Wtraditional,
		"traditional C lacks a separate namespace "
		"for labels, identifier %qE conflicts", name);

  /* Mark label as having been defined.  */
  DECL_INITIAL (label) = error_mark_ڳنڍ;
  أرجع label;
}

/* Get the bindings for a new switch statement.  This is used to issue
   warnings as appropriate for jumps from the switch to case or
   default labels.  */

بنية c_spot_bindings *
c_get_switch_bindings (فراغ)
{
  بنية c_spot_bindings *switch_bindings;

  switch_bindings = XNEW (بنية c_spot_bindings);
  سيٽ_spot_bindings (switch_bindings, سچ);
  أرجع switch_bindings;
}

فراغ
c_release_switch_bindings (بنية c_spot_bindings *bindings)
{
  gcc_assert (bindings->stmt_exprs == 0 && !bindings->کاٻو_stmt_اظهار);
  XDELETE (bindings);
}

/* This is called at the point of a case or default label to issue
   warnings about decls as needed.  It returns true if it found an
   error, not just a warning.  */

منطقي
c_check_switch_jump_warnings (بنية c_spot_bindings *switch_bindings,
			      location_t switch_loc, location_t case_loc)
{
  منطقي saw_error;
  بنية c_scope *scope;

  saw_error = خطأ;
  لكل (scope = current_scope;
       scope != switch_bindings->scope;
       scope = scope->outer)
    {
      بنية c_binding *b;

      gcc_assert (scope != عدم);

      إذا (!scope->has_jump_unsafe_decl)
	استمر;

      لكل (b = scope->bindings; b != عدم; b = b->prev)
	{
	  إذا (decl_jump_unsafe (b->decl))
	    {
	      auto_diagnostic_گروهه d;
	      منطقي emitted;
	      إذا (c_type_variably_modified_p (وڻ_TYPE (b->decl)))
		{
		  saw_error = سچ;
		  error_at (case_loc,
			    "switch jumps into scope of identifier with "
			    "variably modified type");
		  emitted = سچ;
		}
	      وإلا إذا (flag_openmp
		       && lookup_attribute ("omp allocate",
					    DECL_خاصيتون (b->decl)))
		{
		  saw_error = سچ;
		  error_at (case_loc,
			    "switch jumps over OpenMP %<allocate%> allocation");
		  emitted = سچ;
		}
	      وإلا
		emitted
		  = warning_at (case_loc, OPT_Wjump_ناڪاميون_init,
				"switch jumps over variable initialization");
	      إذا (emitted)
		{
		  inform (switch_loc, "switch starts here");
		  inform (DECL_ذريعو_LOCATION (b->decl), "%qD declared here",
			  b->decl);
		}
	    }
	}
    }

  إذا (switch_bindings->stmt_exprs > 0)
    {
      saw_error = سچ;
      auto_diagnostic_گروهه d;
      error_at (case_loc, "switch jumps into statement expression");
      inform (switch_loc, "switch starts here");
    }

  أرجع saw_error;
}

/* Given NAME, an IDENTIFIER_NODE,
   return the structure (or union or enum) definition for that name.
   If THISLEVEL_ONLY is nonzero, searches only the current_scope.
   CODE says which kind of type the caller wants;
   it is RECORD_TYPE or UNION_TYPE or ENUMERAL_TYPE.
   If PLOC is not NULL and this returns non-null, it sets *PLOC to the
   location where the tag was defined.
   If the wrong kind of type is found, an error is reported.  */

ساكن وڻ
lookup_ٽيگ (تعداد وڻ_ڪوڊ_2 ڪوڊ, وڻ name, منطقي thislevel_only,
	    location_t *ploc)
{
  بنية c_binding *b = I_ٽيگ_BINDING (name);
  منطقي thislevel = خطأ;

  إذا (!b || !b->decl)
    أرجع NULL_وڻ;

  /* We only care about whether it's in this level if
     thislevel_only was set or it might be a type clash.  */
  إذا (thislevel_only || وڻ_ڪوڊ (b->decl) != ڪوڊ)
    {
      /* For our purposes, a tag in the external scope is the same as
	 a tag in the file scope.  (Primarily relevant to Objective-C
	 and its builtin structure tags, which get pushed before the
	 file scope is created.)  */
      إذا (B_اندريون_CURRENT_SCOPE (b)
	  || (current_scope == file_scope && B_اندريون_EXTERNAL_SCOPE (b)))
	thislevel = سچ;
    }

  إذا (thislevel_only && !thislevel)
    أرجع NULL_وڻ;

  إذا (وڻ_ڪوڊ (b->decl) != ڪوڊ)
    {
      /* Definition isn't the kind we were looking for.  */
      pending_invalid_xref = name;
      pending_invalid_xref_location = داخلا_location;

      /* If in the same binding level as a declaration as a tag
	 of a different type, this must not be allowed to
	 shadow that tag, so give the error immediately.
	 (For example, "struct foo; union foo;" is invalid.)  */
      إذا (thislevel)
	pending_xref_error ();
    }

  إذا (ploc != عدم)
    *ploc = b->locus;

  أرجع b->decl;
}

/* Return true if a definition exists for NAME with code CODE.  */

منطقي
ٽيگ_exists_p (تعداد وڻ_ڪوڊ_2 ڪوڊ, وڻ name)
{
  بنية c_binding *b = I_ٽيگ_BINDING (name);

  إذا (b == عدم || b->decl == NULL_وڻ)
    أرجع خطأ;
  أرجع وڻ_ڪوڊ (b->decl) == ڪوڊ;
}

/* Print an error message now
   for a recent invalid struct, union or enum cross reference.
   We don't print them immediately because they are not invalid
   when used in the `struct foo;' construct for shadowing.  */

فراغ
pending_xref_error (فراغ)
{
  إذا (pending_invalid_xref != NULL_وڻ)
    error_at (pending_invalid_xref_location, "%qE defined as wrong kind of tag",
	      pending_invalid_xref);
  pending_invalid_xref = NULL_وڻ;
}


/* Look up NAME in the current scope and its superiors
   in the namespace of variables, functions and typedefs.
   Return a ..._DECL node of some kind representing its definition,
   or return NULL_TREE if it is undefined.  */

وڻ
lookup_name (وڻ name)
{
  بنية c_binding *b = I_نشان_BINDING (name);
  /* Do not resolve non-default function versions.  */
  إذا (b
      && وڻ_ڪوڊ (b->decl) == FUNCTION_DECL
      && DECL_FUNCTION_VERSIONED (b->decl)
      && !is_function_default_نسخو (b->decl))
    أرجع NULL_وڻ;
  إذا (b && !b->invisible)
    {
      maybe_رڪارڊ_typedef_use (b->decl);
      أرجع b->decl;
    }
  أرجع NULL_وڻ;
}

/* Similar to `lookup_name' but look only at the indicated scope.  */

ساكن وڻ
lookup_name_اندريون_scope (وڻ name, بنية c_scope *scope)
{
  بنية c_binding *b;

  لكل (b = I_نشان_BINDING (name); b; b = b->shadowed)
    إذا (B_اندريون_SCOPE (b, scope))
      أرجع b->decl;
  أرجع NULL_وڻ;
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
lookup_name_fuzzy (وڻ name, تعداد lookup_name_fuzzy_قسم قسم, location_t loc)
{
  gcc_assert (وڻ_ڪوڊ (name) == IDENTIFIER_ڳنڍ);

  /* Look up function-like macros first; maybe misusing them. */
  خودڪار cpp_ڳنڍ = cpp_lookup (parse_اندريون,
			      (ثابت بنانشان حرف*)IDENTIFIER_اشارو (name),
			      IDENTIFIER_ڊيگهائي (name));
  إذا (cpp_ڳنڍ && cpp_fun_like_macro_p (cpp_ڳنڍ))
    أرجع name_hint
      (خالي_اشارو,
       std::make_unique<macro_like_function_استعمال_ٿيل> (loc,
						   IDENTIFIER_اشارو (name)));

  /* Next, try some well-known names in the C standard library, in case
     the user forgot a #include.  */
  ثابت حرف *سرو_hint
    = get_c_stdlib_سرو_for_name (IDENTIFIER_اشارو (name));

  إذا (سرو_hint)
    أرجع name_hint
      (خالي_اشارو,
       std::make_unique<suggest_missing_سرو> (loc,
						 IDENTIFIER_اشارو (name),
						 سرو_hint));

  /* Next, look for exact matches for builtin defines that would have been
     defined if the user had passed a command-line option (e.g. -fopenmp
     for "_OPENMP").  */
  diagnostics::option_id option_id
    = get_option_for_builtin_define (IDENTIFIER_اشارو (name));
  إذا (option_id.m_idx > 0)
    أرجع name_hint
      (خالي_اشارو,
       std::make_unique<suggest_missing_option> (loc,
						 IDENTIFIER_اشارو (name),
						 option_id));

  /* Only suggest names reserved for the implementation if NAME begins
     with an underscore.  */
  منطقي consider_implementation_نالا = (IDENTIFIER_اشارو (name)[0] == '_');

  بهترين_ميلاپ<وڻ, وڻ> bm (name);

  /* Look within currently valid scopes.  */
  لكل (c_scope *scope = current_scope; scope; scope = scope->outer)
    لكل (c_binding *binding = scope->bindings; binding; binding = binding->prev)
      {
	إذا (!binding->id || binding->invisible)
	  استمر;
	إذا (binding->decl == error_mark_ڳنڍ)
	  استمر;
	/* Don't use bindings from implicitly declared functions,
	   as they were likely misspellings themselves.  */
	إذا (وڻ_ڪوڊ (binding->decl) == FUNCTION_DECL)
	  إذا (C_DECL_IMPLICIT (binding->decl))
	    استمر;
	/* Don't suggest names that are reserved for use by the
	   implementation, unless NAME began with an underscore.  */
	إذا (!consider_implementation_نالا)
	  {
	    ثابت حرف *suggestion_str = IDENTIFIER_اشارو (binding->id);
	    إذا (name_reserved_for_implementation_p (suggestion_str))
	      استمر;
	  }
	بدل (قسم)
	  {
	  حالة FUZZY_LOOKUP_TYPENAME:
	    إذا (وڻ_ڪوڊ (binding->decl) != TYPE_DECL)
	      استمر;
	    اكسر;

	  حالة FUZZY_LOOKUP_FUNCTION_NAME:
	    إذا (وڻ_ڪوڊ (binding->decl) != FUNCTION_DECL)
	      {
		/* Allow function pointers.  */
		إذا ((VAR_P (binding->decl)
		     || وڻ_ڪوڊ (binding->decl) == PARM_DECL)
		    && وڻ_ڪوڊ (وڻ_TYPE (binding->decl)) == اشارو_TYPE
		    && (وڻ_ڪوڊ (وڻ_TYPE (وڻ_TYPE (binding->decl)))
			== FUNCTION_TYPE))
		  اكسر;
		استمر;
	      }
	    اكسر;

	  افتراضي:
	    اكسر;
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
  بهترين_macro_ميلاپ bmm (name, bm.get_بهترين_مفاصلو (), parse_اندريون);
  cpp_hashnode *بهترين_macro = bmm.get_بهترين_meaningful_candidate ();
  /* If a macro is the closest so far to NAME, use it, creating an
     identifier tree node for it.  */
  إذا (بهترين_macro)
    {
      ثابت حرف *id = (ثابت حرف *)بهترين_macro->ident.str;
      وڻ macro_as_identifier
	= get_identifier_with_ڊيگهائي (id, بهترين_macro->ident.len);
      bm.سيٽ_بهترين_so_far (macro_as_identifier,
			  bmm.get_بهترين_مفاصلو (),
			  bmm.get_بهترين_candidate_ڊيگهائي ());
    }

  /* Try the "start_typename" keywords to detect
     "singed" vs "signed" typos.  */
  إذا (قسم == FUZZY_LOOKUP_TYPENAME)
    {
      لكل (بنانشان i = 0; i < انگ_c_common_reswords; i++)
	{
	  ثابت c_common_resword *resword = &c_common_reswords[i];
	  إذا (!c_keyword_starts_typename (resword->rid))
	    استمر;
	  وڻ resword_identifier = ridpointers [resword->rid];
	  إذا (!resword_identifier)
	    استمر;
	  gcc_assert (وڻ_ڪوڊ (resword_identifier) == IDENTIFIER_ڳنڍ);
	  bm.consider (resword_identifier);
	}
    }

  وڻ بهترين = bm.get_بهترين_meaningful_candidate ();
  إذا (بهترين)
    أرجع name_hint (IDENTIFIER_اشارو (بهترين), عدم);
  وإلا
    أرجع name_hint (عدم, عدم);
}


/* Handle the standard [[nodiscard]] attribute.  */

ساكن وڻ
handle_nodiscard_attribute (وڻ *ڳنڍ, وڻ name, وڻ /*دليلون*/,
			    صحيح /*flags*/, منطقي *no_جوڙيو_attrs)
{
  إذا (وڻ_ڪوڊ (*ڳنڍ) == FUNCTION_DECL)
    {
      إذا (VOID_TYPE_P (وڻ_TYPE (وڻ_TYPE (*ڳنڍ))))
	warning_at (DECL_ذريعو_LOCATION (*ڳنڍ),
		    OPT_Wattributes, "%qE attribute applied to %qD with void "
		    "return type", name, *ڳنڍ);
    }
  وإلا إذا (رڪارڊ_OR_UNION_TYPE_P (*ڳنڍ)
	   || وڻ_ڪوڊ (*ڳنڍ) == ENUMERAL_TYPE)
    /* OK */;
  وإلا
    {
      pedwarn (داخلا_location,
	       OPT_Wattributes, "%qE attribute can only be applied to "
	       "functions or to structure, union or enumeration types", name);
      *no_جوڙيو_attrs = سچ;
    }
  أرجع NULL_وڻ;
}

/* Handle the standard [[noreturn]] attribute.  */

ساكن وڻ
handle_std_noreturn_attribute (وڻ *ڳنڍ, وڻ name, وڻ دليلون,
			       صحيح flags, منطقي *no_جوڙيو_attrs)
{
  /* Unlike GNU __attribute__ ((noreturn)), the standard [[noreturn]]
     only applies to functions, not function pointers.  */
  إذا (وڻ_ڪوڊ (*ڳنڍ) == FUNCTION_DECL)
    أرجع handle_noreturn_attribute (ڳنڍ, name, دليلون, flags, no_جوڙيو_attrs);
  وإلا
    {
      pedwarn (داخلا_location, OPT_Wattributes,
	       "standard %qE attribute can only be applied to functions",
	       name);
      *no_جوڙيو_attrs = سچ;
      أرجع NULL_وڻ;
    }
}

/* Handle the standard [[unsequenced]] attribute.  */

ساكن وڻ
handle_std_unsequenced_attribute (وڻ *ڳنڍ, وڻ name, وڻ دليلون,
				  صحيح flags, منطقي *no_جوڙيو_attrs)
{
  /* Unlike GNU __attribute__ ((unsequenced)), the standard [[unsequenced]]
     should be only applied to function declarators or type specifiers which
     have function type.  */
  إذا (ڳنڍ[2])
    {
      auto_diagnostic_گروهه d;
      إذا (pedwarn (داخلا_location, OPT_Wattributes,
		   "standard %qE attribute can only be applied to function "
		   "declarators or type specifiers with function type", name))
	inform (داخلا_location, "did you mean to specify it after %<)%> "
				"following function parameters?");
      *no_جوڙيو_attrs = سچ;
      أرجع NULL_وڻ;
    }
  أرجع handle_unsequenced_attribute (ڳنڍ, name, دليلون, flags, no_جوڙيو_attrs);
}

/* Handle the standard [[reproducible]] attribute.  */

ساكن وڻ
handle_std_reproducible_attribute (وڻ *ڳنڍ, وڻ name, وڻ دليلون,
				   صحيح flags, منطقي *no_جوڙيو_attrs)
{
  أرجع handle_std_unsequenced_attribute (ڳنڍ, name, دليلون, flags,
					   no_جوڙيو_attrs);
}

/* Table of supported standard (C23) attributes.  */
ساكن ثابت attribute_spec std_خاصيتون[] =
{
  /* { name, min_len, max_len, decl_req, type_req, fn_type_req,
       affects_type_identity, handler, exclude } */
  { "_Noreturn", 0, 0, خطأ, خطأ, خطأ, خطأ,
    handle_std_noreturn_attribute, عدم },
  { "deprecated", 0, 1, خطأ, خطأ, خطأ, خطأ,
    handle_deprecated_attribute, عدم },
  { "fallthrough", 0, 0, خطأ, خطأ, خطأ, خطأ,
    handle_fallthrough_attribute, عدم },
  { "maybe_unused", 0, 0, خطأ, خطأ, خطأ, خطأ,
    handle_اڻ_استعمال_ٿيل_attribute, عدم },
  { "nodiscard", 0, 1, خطأ, خطأ, خطأ, خطأ,
    handle_nodiscard_attribute, عدم },
  { "noreturn", 0, 0, خطأ, خطأ, خطأ, خطأ,
    handle_std_noreturn_attribute, عدم },
  { "reproducible", 0, 0, خطأ, سچ, سچ, خطأ,
    handle_std_reproducible_attribute, عدم },
  { "unsequenced", 0, 0, خطأ, سچ, سچ, خطأ,
    handle_std_unsequenced_attribute, عدم }
};

ثابت scoped_attribute_specs std_attribute_جدول =
{
  خالي_اشارو, { std_خاصيتون }
};

/* Create the predefined scalar types of C,
   and some nodes representing standard constants (0, 1, (void *) 0).
   Initialize the global scope.
   Make definitions for built-in primitive functions.  */

فراغ
c_init_decl_processing (فراغ)
{
  location_t save_loc = داخلا_location;

  /* Initialize reserved words for parser.  */
  c_parse_init ();

  current_function_decl = NULL_وڻ;

  gcc_obstack_init (&parser_obstack);

  /* Make the externals scope.  */
  ڌڪو_scope ();
  external_scope = current_scope;

  /* Declarations from c_common_nodes_and_builtins must not be associated
     with this input file, lest we get differences between using and not
     using preprocessed headers.  */
  داخلا_location = BUILTINS_LOCATION;

  c_common_nodes_and_builtins ();

  /* In C, comparisons and TRUTH_* expressions have type int.  */
  truthvalue_type_ڳنڍ = integer_type_ڳنڍ;
  truthvalue_true_ڳنڍ = integer_one_ڳنڍ;
  truthvalue_false_ڳنڍ = integer_zero_ڳنڍ;

  /* Even in C99, which has a real boolean type.  */
  pushdecl (build_decl (UNKNOWN_LOCATION, TYPE_DECL,
			get_identifier (flag_isoc23 ? "bool" : "_Bool"),
			boolean_type_ڳنڍ));

  /* C-specific nullptr initialization.  */
  رڪارڊ_builtin_type (RID_MAX, "typeof (nullptr)", nullptr_type_ڳنڍ);
  /* The size and alignment of nullptr_t is the same as for a pointer to
     character type.  */
  سيٽ_TYPE_ALIGN (nullptr_type_ڳنڍ, GET_گهڻائي_ALIGNMENT (ptr_گهڻائي));

  داخلا_location = save_loc;

  make_fname_decl = c_make_fname_decl;
  شروعات_fname_decls ();

  إذا (warn_keyword_macro)
    {
      لكل (بنانشان صحيح i = 0; i < انگ_c_common_reswords; ++i)
	/* For C register keywords which don't start with underscore
	   or start with just single underscore.  Don't complain about
	   ObjC or Transactional Memory keywords.  */
	إذا (c_common_reswords[i].لفظ[0] == '_'
	    && c_common_reswords[i].لفظ[1] == '_')
	  استمر;
	وإلا إذا (c_common_reswords[i].disable
		 & (D_TRANSMEM | D_OBJC | D_CXX_OBJC))
	  استمر;
	وإلا
	  {
	    وڻ id = get_identifier (c_common_reswords[i].لفظ);
	    إذا (C_IS_RESERVED_لفظ (id)
		&& C_RID_ڪوڊ (id) != RID_CXX_COMPAT_WARN)
	      cpp_warn (parse_اندريون, IDENTIFIER_اشارو (id),
			IDENTIFIER_ڊيگهائي (id));
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

ساكن وڻ
c_make_fname_decl (location_t loc, وڻ id, صحيح type_dep)
{
  ثابت حرف *name = fname_as_string (type_dep);
  وڻ decl, type, init;
  سائيز_t ڊيگهائي = لڙي_ڊيگهه (name);

  type = c_build_array_type (char_type_ڳنڍ,
			     build_اشاريو_type (سائيز_int (ڊيگهائي)));
  type = c_build_qualified_type (type, TYPE_QUAL_CONST);

  decl = build_decl (loc, VAR_DECL, id, type);

  وڻ_STATIC (decl) = 1;
  وڻ_READONLY (decl) = 1;
  DECL_ARTIFICIAL (decl) = 1;

  init = build_string (ڊيگهائي + 1, name);
  حرر (const_cast<حرف *> (name));
  وڻ_TYPE (init) = type;
  DECL_INITIAL (decl) = init;

  وڻ_استعمال_ٿيل (decl) = 1;

  إذا (current_function_decl
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
	    /*invisible=*/خطأ, /*nested=*/خطأ, UNKNOWN_LOCATION);
    }

  پڄاڻي_decl (decl, loc, init, NULL_وڻ, NULL_وڻ);

  أرجع decl;
}

وڻ
c_builtin_function (وڻ decl)
{
  وڻ type = وڻ_TYPE (decl);
  وڻ   id = DECL_NAME (decl);

  ثابت حرف *name = IDENTIFIER_اشارو (id);
  C_DECL_BUILTIN_PROTOTYPE (decl) = prototype_p (type);

  /* Should never be called on a symbol with a preexisting meaning.  */
  gcc_assert (!I_نشان_BINDING (id));

  bind (id, decl, external_scope, /*invisible=*/سچ, /*nested=*/خطأ,
	UNKNOWN_LOCATION);

  /* Builtins in the implementation namespace are made visible without
     needing to be explicitly declared.  See push_file_scope.  */
  إذا (name[0] == '_' && (name[1] == '_' || ISUPPER (name[1])))
    {
      DECL_CHAIN (decl) = visible_builtins;
      visible_builtins = decl;
    }

  أرجع decl;
}

وڻ
c_builtin_function_ext_scope (وڻ decl)
{
  وڻ type = وڻ_TYPE (decl);
  وڻ   id = DECL_NAME (decl);

  ثابت حرف *name = IDENTIFIER_اشارو (id);
  C_DECL_BUILTIN_PROTOTYPE (decl) = prototype_p (type);

  إذا (external_scope)
    bind (id, decl, external_scope, /*invisible=*/خطأ, /*nested=*/خطأ,
	  UNKNOWN_LOCATION);

  /* Builtins in the implementation namespace are made visible without
     needing to be explicitly declared.  See push_file_scope.  */
  إذا (name[0] == '_' && (name[1] == '_' || ISUPPER (name[1])))
    {
      DECL_CHAIN (decl) = visible_builtins;
      visible_builtins = decl;
    }

  أرجع decl;
}

/* Implement LANG_HOOKS_SIMULATE_BUILTIN_FUNCTION_DECL.  */

وڻ
c_simulate_builtin_function_decl (وڻ decl)
{
  وڻ type = وڻ_TYPE (decl);
  C_DECL_BUILTIN_PROTOTYPE (decl) = prototype_p (type);
  أرجع pushdecl (decl);
}

/* Warn about attributes in a context where they are unused
   (attribute-declarations, except for the "fallthrough" case, and
   attributes on statements).  */

فراغ
c_warn_اڻ_استعمال_ٿيل_خاصيتون (وڻ attrs)
{
  لكل (وڻ t = attrs; t != NULL_وڻ; t = وڻ_CHAIN (t))
    إذا (get_attribute_namespace (t) == NULL_وڻ)
      /* The specifications of standard attributes mean this is a
	 constraint violation.  */
      pedwarn (داخلا_location, OPT_Wattributes, "%qE attribute ignored",
	       get_attribute_name (t));
    وإلا إذا (!attribute_ignored_p (t))
      warning (OPT_Wattributes, "%qE attribute ignored",
	       get_attribute_name (t));
}

/* Warn for standard attributes being applied to a type that is not
   being defined, where that is a constraint violation, and return a
   list of attributes with them removed.  */

وڻ
c_warn_type_خاصيتون (وڻ type, وڻ attrs)
{
  وڻ *attr_ptr = &attrs;
  طالما (*attr_ptr)
    إذا (get_attribute_namespace (*attr_ptr) == NULL_وڻ)
      {
	إذا (وڻ_ڪوڊ (type) == FUNCTION_TYPE)
	  {
	    وڻ name = get_attribute_name (*attr_ptr);
	    /* [[unsequenced]] and [[reproducible]] is fine on function
	       types that aren't being defined.  */
	    إذا (is_attribute_p ("unsequenced", name)
		|| is_attribute_p ("reproducible", name))
	      {
		attr_ptr = &وڻ_CHAIN (*attr_ptr);
		استمر;
	      }
	  }
	pedwarn (داخلا_location, OPT_Wattributes, "%qE attribute ignored",
		 get_attribute_name (*attr_ptr));
	*attr_ptr = وڻ_CHAIN (*attr_ptr);
      }
    وإلا
      attr_ptr = &وڻ_CHAIN (*attr_ptr);
  أرجع attrs;
}

/* Called when a declaration is seen that contains no names to declare.
   If its type is a reference to a structure, union or enum inherited
   from a containing scope, shadow that tag name for the current scope
   with a forward reference.
   If its type defines a new named structure or union
   or defines an enum, it is valid but we need not do anything here.
   Otherwise, it is an error.  */

فراغ
shadow_ٽيگ (ثابت بنية c_declspecs *declspecs)
{
  shadow_ٽيگ_warned (declspecs, 0);
}

/* WARNED is 1 if we have done a pedwarn, 2 if we have done a warning,
   but no pedwarn.  */
فراغ
shadow_ٽيگ_warned (ثابت بنية c_declspecs *declspecs, صحيح warned)
{
  منطقي مليو_ٽيگ = خطأ;

  إذا (declspecs->type && !declspecs->default_int_p && !declspecs->typedef_p)
    {
      وڻ قدر = declspecs->type;
      تعداد وڻ_ڪوڊ_2 ڪوڊ = وڻ_ڪوڊ (قدر);

      إذا (ڪوڊ == رڪارڊ_TYPE || ڪوڊ == UNION_TYPE || ڪوڊ == ENUMERAL_TYPE)
	/* Used to test also that TYPE_SIZE (value) != 0.
	   That caused warning for `struct foo;' at top level in the file.  */
	{
	  وڻ name = TYPE_NAME (قدر);
	  وڻ t;

	  مليو_ٽيگ = سچ;

	  إذا (declspecs->restrict_p)
	    {
	      error ("invalid use of %<restrict%>");
	      warned = 1;
	    }

	  إذا (اندريون_underspecified_init)
	    {
	      /* This can only occur with extensions such as statement
		 expressions, but is still appropriate as an error to
		 avoid types declared in such a context escaping to
		 the type of an auto variable.  */
	      error ("%qT declared in underspecified object initializer",
		     قدر);
	      warned = 1;
	    }

	  إذا (name == NULL_وڻ)
	    {
	      إذا (warned != 1 && ڪوڊ != ENUMERAL_TYPE)
		/* Empty unnamed enum OK */
		{
		  pedwarn (داخلا_location, 0,
			   "unnamed struct/union that defines no instances");
		  warned = 1;
		}
	    }
	  وإلا إذا (declspecs->typespec_قسم != ctsk_tagdef
                   && declspecs->typespec_قسم != ctsk_tagfirstref
		   && declspecs->typespec_قسم != ctsk_tagfirstref_attrs
		   && declspecs->storage_class != csc_none)
	    {
	      إذا (warned != 1)
		pedwarn (داخلا_location, 0,
			 "empty declaration with storage class specifier "
			 "does not redeclare tag");
	      warned = 1;
	      pending_xref_error ();
	    }
	  وإلا إذا (declspecs->typespec_قسم != ctsk_tagdef
                   && declspecs->typespec_قسم != ctsk_tagfirstref
                   && declspecs->typespec_قسم != ctsk_tagfirstref_attrs
		   && (declspecs->const_p
		       || declspecs->volatile_p
		       || declspecs->atomic_p
		       || declspecs->restrict_p
		       || declspecs->پتو_space))
	    {
	      إذا (warned != 1)
		pedwarn (داخلا_location, 0,
			 "empty declaration with type qualifier "
			  "does not redeclare tag");
	      warned = 1;
	      pending_xref_error ();
	    }
	  وإلا إذا (declspecs->typespec_قسم != ctsk_tagdef
                   && declspecs->typespec_قسم != ctsk_tagfirstref
                   && declspecs->typespec_قسم != ctsk_tagfirstref_attrs
		   && declspecs->alignas_p)
	    {
	      إذا (warned != 1)
		pedwarn (داخلا_location, 0,
			 "empty declaration with %<_Alignas%> "
			  "does not redeclare tag");
	      warned = 1;
	      pending_xref_error ();
	    }
	  وإلا إذا (declspecs->typespec_قسم != ctsk_tagdef
		   && declspecs->typespec_قسم != ctsk_tagfirstref
		   && declspecs->typespec_قسم != ctsk_tagfirstref_attrs
		   && ڪوڊ == ENUMERAL_TYPE
		   && !declspecs->enum_type_specifier_ref_p)
	    {
	      منطقي warned_enum = خطأ;
	      إذا (warned != 1)
		warned_enum = pedwarn (داخلا_location, OPT_Wpedantic,
				       "empty declaration of %<enum%> type "
				       "does not redeclare tag");
	      إذا (warned_enum)
		warned = 1;
	      pending_xref_error ();
	    }
	  وإلا
	    {
	      pending_invalid_xref = NULL_وڻ;
	      t = lookup_ٽيگ (ڪوڊ, name, سچ, عدم);

	      إذا (t == NULL_وڻ)
		{
		  t = make_ڳنڍ (ڪوڊ);
		  إذا (flag_isoc23 || ڪوڊ == ENUMERAL_TYPE)
		    سيٽ_TYPE_STRUCTURAL_EQUALITY (t);
		  pushtag (داخلا_location, name, t);
		}
	    }
	}
      وإلا
	{
	  إذا (warned != 1 && !اندريون_system_سرو_at (داخلا_location))
	    {
	      pedwarn (داخلا_location, 0,
		       "useless type name in empty declaration");
	      warned = 1;
	    }
	}
    }
  وإلا إذا (warned != 1 && !اندريون_system_سرو_at (داخلا_location)
	   && declspecs->typedef_p)
    {
      pedwarn (داخلا_location, 0, "useless type name in empty declaration");
      warned = 1;
    }

  pending_invalid_xref = NULL_وڻ;

  إذا (declspecs->inline_p)
    {
      error ("%<inline%> in empty declaration");
      warned = 1;
    }

  إذا (declspecs->noreturn_p)
    {
      error ("%<_Noreturn%> in empty declaration");
      warned = 1;
    }

  إذا (declspecs->constexpr_p)
    {
      error ("%<constexpr%> in empty declaration");
      warned = 1;
    }

  إذا (current_scope == file_scope && declspecs->storage_class == csc_auto)
    {
      error ("%<auto%> in file-scope empty declaration");
      warned = 1;
    }

  إذا (current_scope == file_scope && declspecs->storage_class == csc_رجسٽر)
    {
      error ("%<register%> in file-scope empty declaration");
      warned = 1;
    }

  إذا (declspecs->enum_type_specifier_ref_p && !warned)
    {
      إذا (declspecs->storage_class != csc_none)
	{
	  error ("storage class specifier in empty declaration with %<enum%> "
		 "underlying type");
	  warned = 1;
	}
      وإلا إذا (declspecs->thread_p)
	{
	  error ("%qs in empty declaration with %<enum%> underlying type",
		 declspecs->thread_gnu_p ? "__thread" : "_Thread_local");
	  warned = 1;
	}
      وإلا إذا (declspecs->const_p
	       || declspecs->volatile_p
	       || declspecs->atomic_p
	       || declspecs->restrict_p
	       || declspecs->پتو_space)
	{
	  error ("type qualifier in empty declaration with %<enum%> "
		 "underlying type");
	  warned = 1;
	}
      وإلا إذا (declspecs->alignas_p)
	{
	  error ("%<alignas%> in empty declaration with %<enum%> "
		 "underlying type");
	  warned = 1;
	}
    }

  إذا (!warned && !اندريون_system_سرو_at (داخلا_location)
      && declspecs->storage_class != csc_none)
    {
      warning (0, "useless storage class specifier in empty declaration");
      warned = 2;
    }

  إذا (!warned && !اندريون_system_سرو_at (داخلا_location) && declspecs->thread_p)
    {
      warning (0, "useless %qs in empty declaration",
	       declspecs->thread_gnu_p ? "__thread" : "_Thread_local");
      warned = 2;
    }

  إذا (!warned
      && !اندريون_system_سرو_at (داخلا_location)
      && (declspecs->const_p
	  || declspecs->volatile_p
	  || declspecs->atomic_p
	  || declspecs->restrict_p
	  || declspecs->پتو_space))
    {
      warning (0, "useless type qualifier in empty declaration");
      warned = 2;
    }

  إذا (!warned && !اندريون_system_سرو_at (داخلا_location)
      && declspecs->alignas_p)
    {
      warning (0, "useless %<_Alignas%> in empty declaration");
      warned = 2;
    }

  إذا (مليو_ٽيگ
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
      pedwarn (داخلا_location, 0,
	       "invalid use of attributes in empty declaration");
      warned = 1;
    }

  إذا (warned != 1)
    {
      إذا (declspecs->declspecs_ڏٺل_p
	  && !declspecs->non_std_attrs_ڏٺل_p)
	/* An attribute declaration (but not a fallthrough attribute
	   declaration, which was handled separately); warn if there
	   are any attributes being ignored (but not if the attributes
	   were empty).  */
	c_warn_اڻ_استعمال_ٿيل_خاصيتون (declspecs->attrs);
      وإلا إذا (!مليو_ٽيگ)
	pedwarn (داخلا_location, 0, "empty declaration");
    }
}


/* Return the qualifiers from SPECS as a bitwise OR of TYPE_QUAL_*
   bits.  SPECS represents declaration specifiers that the grammar
   only permits to contain type qualifiers and attributes.  */

صحيح
quals_from_declspecs (ثابت بنية c_declspecs *specs)
{
  صحيح quals = ((specs->const_p ? TYPE_QUAL_CONST : 0)
	       | (specs->volatile_p ? TYPE_QUAL_VOLATILE : 0)
	       | (specs->restrict_p ? TYPE_QUAL_RESTRICT : 0)
	       | (specs->atomic_p ? TYPE_QUAL_ATOMIC : 0)
	       | (ENCODE_QUAL_ADDR_SPACE (specs->پتو_space)));
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
  أرجع quals;
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

بنية c_declarator *
build_array_declarator (location_t loc,
			وڻ اظهار, بنية c_declspecs *quals, منطقي static_p,
			منطقي vla_unspec_p)
{
  بنية c_declarator *declarator = XOBNEW (&parser_obstack,
					    بنية c_declarator);
  declarator->id_loc = loc;
  declarator->قسم = cdk_array;
  declarator->declarator = 0;
  declarator->u.array.dimen = اظهار;
  إذا (quals)
    {
      declarator->u.array.attrs = quals->attrs;
      declarator->u.array.quals = quals_from_declspecs (quals);
    }
  وإلا
    {
      declarator->u.array.attrs = NULL_وڻ;
      declarator->u.array.quals = 0;
    }
  declarator->u.array.static_p = static_p;
  declarator->u.array.vla_unspec_p = vla_unspec_p;
  إذا (static_p || quals != عدم)
    pedwarn_c90 (loc, OPT_Wpedantic,
		 "ISO C90 does not support %<static%> or type "
		 "qualifiers in parameter array declarators");
  إذا (vla_unspec_p)
    {
      pedwarn_c90 (loc, OPT_Wpedantic,
		   "ISO C90 does not support %<[*]%> array declarators");
      إذا (current_scope->parm_flag)
	current_scope->had_vla_unspec = سچ;
    }
  أرجع declarator;
}

/* Set the contained declarator of an array declarator.  DECL is the
   declarator, as constructed by build_array_declarator; INNER is what
   appears on the left of the [].  */

بنية c_declarator *
سيٽ_array_declarator_inner (بنية c_declarator *decl,
			    بنية c_declarator *inner)
{
  decl->declarator = inner;
  أرجع decl;
}

/* Determine whether TYPE is a one-element array type "[1]".  */
ساكن منطقي
one_element_array_type_p (const_وڻ type)
{
  إذا (وڻ_ڪوڊ (type) != ARRAY_TYPE)
    أرجع خطأ;
  أرجع integer_zerop (array_type_nelts_minus_one (type));
}

/* Determine whether TYPE is a zero-length array type "[0]".  */
منطقي
zero_ڊيگهائي_array_type_p (const_وڻ type)
{
  إذا (وڻ_ڪوڊ (type) == ARRAY_TYPE
      && COMPLETE_TYPE_P (type)
      && TYPE_DOMAIN (type) != NULL_وڻ
      && (TYPE_MAX_قدر (TYPE_DOMAIN (type)) == NULL_وڻ
	  || integer_all_onesp (TYPE_MAX_قدر (TYPE_DOMAIN (type)))))
    أرجع سچ;
  أرجع خطأ;
}

/* INIT is a constructor that forms DECL's initializer.  If the final
   element initializes a flexible array field, adjust the size of the
   DECL with the initializer based on whether the DECL is a union or
   a structure.  */

ساكن فراغ
جوڙيو_flexible_array_elts_منزل_سائيز (وڻ decl, وڻ init)
{
  وڻ elt, type;

  إذا (vec_محفوظ_is_خالي_جايون (CONSTRUCTOR_ELTS (init)))
    أرجع;

  elt = CONSTRUCTOR_ELTS (init)->آخري ().قدر;
  type = وڻ_TYPE (elt);
  إذا (flexible_array_member_type_p (type))
    {
      complete_array_type (&type, elt, خطأ);
      /* For a structure, add the size of the initializer to the DECL's
	 size.  */
      إذا (وڻ_ڪوڊ (وڻ_TYPE (decl)) == رڪارڊ_TYPE)
	{
	  DECL_سائيز (decl)
	    = سائيز_binop (PLUS_اظهار, DECL_سائيز (decl), TYPE_سائيز (type));
	  DECL_سائيز_UNIT (decl)
	    = سائيز_binop (PLUS_اظهار, DECL_سائيز_UNIT (decl),
			  TYPE_سائيز_UNIT (type));
	}
      /* For a union, the DECL's size is the maximum of the current size
	 and the size of the initializer.  */
      وإلا
	{
	  DECL_سائيز (decl)
	    = سائيز_binop (MAX_اظهار, DECL_سائيز (decl), TYPE_سائيز (type));
	  DECL_سائيز_UNIT (decl)
	    = سائيز_binop (MAX_اظهار, DECL_سائيز_UNIT (decl),
			  TYPE_سائيز_UNIT (type));
	}
    }
}

/* Decode a "typename", such as "int **", returning a ..._TYPE node.
   Set *EXPR, if EXPR not NULL, to any expression to be evaluated
   before the type name, and set *EXPR_CONST_OPERANDS, if
   EXPR_CONST_OPERANDS not NULL, to indicate whether the type name may
   appear in a constant expression.  */

وڻ
groktypename (بنية c_type_name *type_name, وڻ *اظهار,
	      منطقي *اظهار_const_operands)
{
  وڻ type;
  وڻ attrs = type_name->specs->attrs;

  type_name->specs->attrs = NULL_وڻ;

  type = grokdeclarator (type_name->declarator, type_name->specs, TYPENAME,
			 خطأ, عدم, &attrs, اظهار, اظهار_const_operands,
			 DEPRECATED_عام);

  /* Apply attributes.  */
  attrs = c_warn_type_خاصيتون (type, attrs);
  decl_خاصيتون (&type, attrs, 0);

  أرجع type;
}


/* Decode a "typename", such as "int **", returning a ..._TYPE node,
   as for groktypename but setting the context to GENERIC_ASSOC.  */

وڻ
grokgenassoc (بنية c_type_name *type_name)
{
  وڻ type;
  وڻ attrs = type_name->specs->attrs;

  type_name->specs->attrs = NULL_وڻ;

  type = grokdeclarator (type_name->declarator, type_name->specs, GENERIC_ASSOC,
			 خطأ, عدم, &attrs, عدم, عدم, DEPRECATED_عام);

  /* Apply attributes.  */
  attrs = c_warn_type_خاصيتون (type, attrs);
  decl_خاصيتون (&type, attrs, 0);

  أرجع type;
}


/* Looks up the most recent pushed declaration corresponding to DECL.  */

ساكن وڻ
lookup_آخري_decl (وڻ decl)
{
  وڻ آخري_decl = lookup_name (DECL_NAME (decl));
  إذا (!آخري_decl)
    آخري_decl = lookup_name_اندريون_scope (DECL_NAME (decl), external_scope);
  أرجع آخري_decl;
}

/* Wrapper for decl_attributes that adds some implicit attributes
   to VAR_DECLs or FUNCTION_DECLs.  */

ساكن وڻ
c_decl_خاصيتون (وڻ *ڳنڍ, وڻ خاصيتون, صحيح flags)
{
  /* Add implicit "omp declare target" attribute if requested.  */
  إذا (vec_محفوظ_ڊيگهائي (current_omp_declare_هدف_attribute)
      && ((VAR_P (*ڳنڍ) && is_global_var (*ڳنڍ))
	  || وڻ_ڪوڊ (*ڳنڍ) == FUNCTION_DECL))
    {
      إذا (VAR_P (*ڳنڍ) && !omp_mappable_type (وڻ_TYPE (*ڳنڍ)))
	خاصيتون = وڻ_cons (get_identifier ("omp declare target implicit"),
				NULL_وڻ, خاصيتون);
      وإلا
	خاصيتون = وڻ_cons (get_identifier ("omp declare target"),
				NULL_وڻ, خاصيتون);
      إذا (وڻ_ڪوڊ (*ڳنڍ) == FUNCTION_DECL)
	{
	  صحيح device_type
	    = current_omp_declare_هدف_attribute->آخري ().device_type;
	  device_type = MAX (device_type, 0);
	  إذا ((device_type & OMP_CLAUSE_DEVICE_TYPE_HOST) != 0
	      && !lookup_attribute ("omp declare target host", خاصيتون))
	    خاصيتون
	      = وڻ_cons (get_identifier ("omp declare target host"),
			   NULL_وڻ, خاصيتون);
	  إذا ((device_type & OMP_CLAUSE_DEVICE_TYPE_NOHOST) != 0
	      && !lookup_attribute ("omp declare target nohost", خاصيتون))
	    خاصيتون
	      = وڻ_cons (get_identifier ("omp declare target nohost"),
			   NULL_وڻ, خاصيتون);

	  صحيح اڻسڌو
	    = current_omp_declare_هدف_attribute->آخري ().اڻسڌو;
	  إذا (اڻسڌو && !lookup_attribute ("omp declare target indirect",
					     خاصيتون))
	    خاصيتون
	      = وڻ_cons (get_identifier ("omp declare target indirect"),
			   NULL_وڻ, خاصيتون);
	}
    }

  إذا (flag_openmp || flag_openmp_simd)
    {
      منطقي diagnosed = خطأ;
      لكل (وڻ *pa = &خاصيتون; *pa; )
	{
	  إذا (is_attribute_namespace_p ("omp", *pa))
	    {
	      وڻ name = get_attribute_name (*pa);
	      إذا (is_attribute_p ("directive", name)
		  || is_attribute_p ("sequence", name)
		  || is_attribute_p ("decl", name))
		{
		  ثابت حرف *p = عدم;
		  إذا (وڻ_قدر (*pa) == NULL_وڻ)
		    p = IDENTIFIER_اشارو (name);
		  لكل (وڻ a = وڻ_قدر (*pa); a; a = وڻ_CHAIN (a))
		    {
		      وڻ d = وڻ_قدر (a);
		      gcc_assert (وڻ_ڪوڊ (d) == C_TOKEN_VEC);
		      إذا (وڻ_عوامي (d)
			  && (VAR_P (*ڳنڍ)
			      || وڻ_ڪوڊ (*ڳنڍ) == FUNCTION_DECL)
			  && c_maybe_parse_omp_decl (*ڳنڍ, d))
			استمر;
		      p = وڻ_عوامي (d) ? "decl" : "directive";
		    }
		  إذا (p && !diagnosed)
		    {
		      error ("%<omp::%s%> not allowed to be specified in "
			     "this context", p);
		      diagnosed = سچ;
		    }
		  إذا (p)
		    {
		      *pa = وڻ_CHAIN (*pa);
		      استمر;
		    }
		}
	    }
	  pa = &وڻ_CHAIN (*pa);
	}
    }

  /* Look up the current declaration with all the attributes merged
     so far so that attributes on the current declaration that's
     about to be pushed that conflict with the former can be detected,
     diagnosed, and rejected as appropriate.  To match the C++ FE, do
     not pass an error_mark_node when we found an undeclared variable.  */
  وڻ آخري_decl = lookup_آخري_decl (*ڳنڍ);
  إذا (آخري_decl == error_mark_ڳنڍ)
    آخري_decl = NULL_وڻ;
  وڻ attr = decl_خاصيتون (ڳنڍ, خاصيتون, flags, آخري_decl);
  إذا (VAR_P (*ڳنڍ) && DECL_THREAD_LOCAL_P (*ڳنڍ))
    {
      // tls_model attribute can set a stronger TLS access model.
      tls_model model = DECL_TLS_MODEL (*ڳنڍ);
      tls_model default_model = decl_default_tls_model (*ڳنڍ);
      إذا (default_model > model)
	سيٽ_decl_tls_model (*ڳنڍ, default_model);
    }
  أرجع attr;
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

وڻ
شروعات_decl (بنية c_declarator *declarator, بنية c_declspecs *declspecs,
	    منطقي initialized, وڻ خاصيتون, منطقي do_ڌڪو /* = true */,
	    location_t *lastloc /* = NULL */)
{
  وڻ decl;
  وڻ old_decl;
  وڻ tem;
  وڻ اظهار = NULL_وڻ;
  تعداد deprecated_حالتون deprecated_state = DEPRECATED_عام;

  /* An object declared as __attribute__((unavailable)) suppresses
     warnings and errors from __attribute__((deprecated/unavailable))
     components.
     An object declared as __attribute__((deprecated)) suppresses
     warnings of uses of other deprecated items.  */
  إذا (lookup_attribute ("unavailable", خاصيتون))
    deprecated_state = UNAVAILABLE_DEPRECATED_SUPPRESS;
  وإلا إذا (lookup_attribute ("deprecated", خاصيتون))
    deprecated_state = DEPRECATED_SUPPRESS;

  decl = grokdeclarator (declarator, declspecs,
			 عام_2, initialized, عدم, &خاصيتون, &اظهار, عدم,
			 deprecated_state);
  إذا (!decl || decl == error_mark_ڳنڍ)
    أرجع NULL_وڻ;

  old_decl = lookup_آخري_decl (decl);

  إذا (وڻ lastdecl = lastloc ? old_decl : NULL_وڻ)
    إذا (lastdecl != error_mark_ڳنڍ)
      *lastloc = DECL_ذريعو_LOCATION (lastdecl);

  /* Make sure the size expression is evaluated at this point.  */
  إذا (اظهار && !current_scope->parm_flag)
    جوڙيو_stmt (fold_convert (void_type_ڳنڍ, اظهار));

  إذا (وڻ_ڪوڊ (decl) != FUNCTION_DECL && MAIN_NAME_P (DECL_NAME (decl))
      && وڻ_عوامي (decl))
    warning (OPT_Wmain, "%q+D is usually a function", decl);

  إذا (warn_missing_variable_declarations && VAR_P (decl)
      && !DECL_EXTERNAL (decl) && وڻ_عوامي (decl) && old_decl == NULL_وڻ)
    warning_at (DECL_ذريعو_LOCATION (decl), OPT_Wmissing_variable_declarations,
		"no previous declaration for %qD", decl);

  إذا (initialized)
    /* Is it valid for this decl to have an initializer at all?
       If not, set INITIALIZED to zero, which will indirectly
       tell 'finish_decl' to ignore the initializer once it is parsed.  */
    بدل (وڻ_ڪوڊ (decl))
      {
      حالة TYPE_DECL:
	error ("typedef %qD is initialized (use %<__typeof__%> instead)", decl);
	initialized = خطأ;
	اكسر;

      حالة FUNCTION_DECL:
	error ("function %qD is initialized like a variable", decl);
	initialized = خطأ;
	اكسر;

      حالة PARM_DECL:
	/* DECL_INITIAL in a PARM_DECL is really DECL_ARG_TYPE.  */
	error ("parameter %qD is initialized", decl);
	initialized = خطأ;
	اكسر;

      افتراضي:
	/* Don't allow initializations for incomplete types except for
	   arrays which might be completed by the initialization.  */

	/* This can happen if the array size is an undefined macro.
	   We already gave a warning, so we don't need another one.  */
	إذا (وڻ_TYPE (decl) == error_mark_ڳنڍ)
	  initialized = خطأ;
	وإلا إذا (COMPLETE_TYPE_P (وڻ_TYPE (decl)))
	  {
	    /* A complete type is ok if size is fixed.  If the size is
	       variable, an empty initializer is OK and nonempty
	       initializers will be diagnosed in the parser.  */
	  }
	وإلا إذا (وڻ_ڪوڊ (وڻ_TYPE (decl)) != ARRAY_TYPE)
	  {
	    error ("variable %qD has initializer but incomplete type", decl);
	    initialized = خطأ;
	  }
      }

  إذا (initialized)
    {
      إذا (current_scope == file_scope)
	وڻ_STATIC (decl) = 1;

      /* Tell 'pushdecl' this is an initialized decl
	 even though we don't yet have the initializer expression.
	 Also tell 'finish_decl' it may store the real initializer.  */
      DECL_INITIAL (decl) = error_mark_ڳنڍ;
    }

  /* If this is a function declaration, write a record describing it to the
     prototypes file (if requested).  */

  إذا (وڻ_ڪوڊ (decl) == FUNCTION_DECL)
    gen_aux_info_رڪارڊ (decl, 0, 0, prototype_p (وڻ_TYPE (decl)));

  /* ANSI specifies that a tentative definition which is not merged with
     a non-tentative definition behaves exactly like a definition with an
     initializer equal to zero.  (Section 3.7.2)

     -fno-common gives strict ANSI behavior, though this tends to break
     a large body of code that grew up without this rule.

     Thread-local variables are never common, since there's no entrenched
     body of code to break, and it allows more efficient variable references
     in the presence of dynamic linking.  */

  إذا (VAR_P (decl)
      && !initialized
      && وڻ_عوامي (decl)
      && !DECL_THREAD_LOCAL_P (decl)
      && !flag_no_common)
    DECL_COMMON (decl) = 1;

  /* Set attributes here so if duplicate decl, will have proper attributes.  */
  c_decl_خاصيتون (&decl, خاصيتون, 0);

  /* Handle gnu_inline attribute.  */
  إذا (declspecs->inline_p
      && !flag_gnu89_inline
      && وڻ_ڪوڊ (decl) == FUNCTION_DECL
      && (lookup_attribute ("gnu_inline", DECL_خاصيتون (decl))
	  || current_function_decl))
    {
      إذا (declspecs->storage_class == csc_auto && current_scope != file_scope)
	;
      وإلا إذا (declspecs->storage_class != csc_static)
	DECL_EXTERNAL (decl) = !DECL_EXTERNAL (decl);
    }

  إذا (وڻ_ڪوڊ (decl) == FUNCTION_DECL
      && DECL_DECLARED_INLINE_P (decl)
      && DECL_UNINLINABLE (decl)
      && lookup_attribute ("noinline", DECL_خاصيتون (decl)))
    {
      auto_urlify_خاصيتون sentinel;
      warning (OPT_Wattributes, "inline function %q+D given attribute %qs",
	       decl, "noinline");
    }

  /* C99 6.7.4p3: An inline definition of a function with external
     linkage shall not contain a definition of a modifiable object
     with static storage duration...  */
  إذا (VAR_P (decl)
      && current_scope != file_scope
      && وڻ_STATIC (decl)
      && !وڻ_READONLY (decl)
      && DECL_DECLARED_INLINE_P (current_function_decl)
      && DECL_EXTERNAL (current_function_decl))
    رڪارڊ_inline_static (داخلا_location, current_function_decl,
			  decl, csi_modifiable);

  إذا (c_dialect_objc ()
      && VAR_OR_FUNCTION_DECL_P (decl))
      objc_check_global_decl (decl);

  /* To enable versions to be created across TU's we mark and mangle all
     non-default versioned functions.  */
  إذا (وڻ_ڪوڊ (decl) == FUNCTION_DECL
      && !هدف_HAS_FMV_هدف_ATTRIBUTE
      && get_هدف_نسخو (decl).is_valid ())
    {
      maybe_mark_function_versioned (decl);
      إذا (current_scope != file_scope)
	error ("versioned declarations are only allowed at file scope");
    }

  /* Add this decl to the current scope.
     TEM may equal DECL or it may be a previous decl of the same name.  */
  إذا (do_ڌڪو)
    {
      tem = pushdecl (decl);

      إذا (initialized && DECL_EXTERNAL (tem))
	{
	  DECL_EXTERNAL (tem) = 0;
	  وڻ_STATIC (tem) = 1;
	}

      أرجع tem;
    }
  وإلا
    أرجع decl;
}

/* Subroutine of finish_decl. TYPE is the type of an uninitialized object
   DECL or the non-array element type if DECL is an uninitialized array.
   If that type has a const member, diagnose this. */

ساكن فراغ
diagnose_uninitialized_cst_member (وڻ decl, وڻ type)
{
  وڻ ميدان_2;
  لكل (ميدان_2 = TYPE_FIELDS (type); ميدان_2; ميدان_2 = وڻ_CHAIN (ميدان_2))
    {
      وڻ ميدان_type;
      إذا (وڻ_ڪوڊ (ميدان_2) != ميدان_DECL)
	استمر;
      ميدان_type = strip_array_types (وڻ_TYPE (ميدان_2));

      إذا (TYPE_QUALS (ميدان_type) & TYPE_QUAL_CONST)
      	{
	  auto_diagnostic_گروهه d;
	  إذا (warning_at (DECL_ذريعو_LOCATION (decl), OPT_Wc___compat,
			  "uninitialized const member in %qT is invalid in C++",
			  strip_array_types (وڻ_TYPE (decl))))
	    inform (DECL_ذريعو_LOCATION (ميدان_2), "%qD should be initialized", ميدان_2);
	}

      إذا (رڪارڊ_OR_UNION_TYPE_P (ميدان_type))
	diagnose_uninitialized_cst_member (decl, ميدان_type);
    }
}

/* Finish processing of a declaration;
   install its initial value.
   If ORIGTYPE is not NULL_TREE, it is the original type of INIT.
   If the length of an array type is not known before,
   it must be determined now, from the initial value, or it is an error.

   INIT_LOC is the location of the initial value.  */

فراغ
پڄاڻي_decl (وڻ decl, location_t init_loc, وڻ init,
	     وڻ origtype, وڻ asmspec_وڻ)
{
  وڻ type;
  منطقي was_incomplete = (DECL_سائيز (decl) == NULL_وڻ);
  ثابت حرف *asmspec = 0;

  /* If a name was specified, get the string.  */
  إذا (VAR_OR_FUNCTION_DECL_P (decl)
      && DECL_FILE_SCOPE_P (decl))
    asmspec_وڻ = maybe_apply_renaming_pragma (decl, asmspec_وڻ);
  إذا (asmspec_وڻ)
    asmspec = وڻ_STRING_اشارو (asmspec_وڻ);

  إذا (VAR_P (decl)
      && وڻ_STATIC (decl)
      && global_bindings_p ())
    /* So decl is a global variable. Record the types it uses
       so that we can decide later to emit debug info for them.  */
    رڪارڊ_types_استعمال_ٿيل_by_current_var_decl (decl);

  /* If `start_decl' didn't like having an initialization, ignore it now.  */
  إذا (init != NULL_وڻ && DECL_INITIAL (decl) == NULL_وڻ)
    init = NULL_وڻ;

  /* Don't crash if parm is initialized.  */
  إذا (وڻ_ڪوڊ (decl) == PARM_DECL)
    init = NULL_وڻ;

  إذا (init)
    store_init_قدر (init_loc, decl, init, origtype);

  إذا (c_dialect_objc () && (VAR_OR_FUNCTION_DECL_P (decl)
			    || وڻ_ڪوڊ (decl) == ميدان_DECL))
    objc_check_decl (decl);

  type = وڻ_TYPE (decl);

  /* Deduce size of array from initialization, if not already known.
     This is only needed for an initialization in the current scope;
     it must not be done for a file-scope initialization of a
     declaration with external linkage, redeclared in an inner scope
     with the outer declaration shadowed in an intermediate scope.  */
  إذا (وڻ_ڪوڊ (type) == ARRAY_TYPE
      && TYPE_DOMAIN (type) == NULL_وڻ
      && وڻ_ڪوڊ (decl) != TYPE_DECL
      && !(وڻ_عوامي (decl) && current_scope != file_scope))
    {
      منطقي do_default
	= !وڻ_STATIC (decl) && !DECL_EXTERNAL (decl);
      صحيح failure
	= complete_array_type (&وڻ_TYPE (decl), DECL_INITIAL (decl),
			       do_default);

      /* Get the completed type made by complete_array_type.  */
      type = وڻ_TYPE (decl);

      بدل (failure)
	{
	حالة 1:
	  error ("initializer fails to determine size of %q+D", decl);
	  اكسر;

	حالة 2:
	  إذا (do_default)
	    error ("array size missing in %q+D", decl);
	  وإلا إذا (!وڻ_عوامي (decl))
	    pedwarn_c23 (DECL_ذريعو_LOCATION (decl), OPT_Wpedantic,
			 "array size missing in %q+D", decl);
	  اكسر;

	حالة 3:
	  error ("zero or negative size array %q+D", decl);
	  اكسر;

	حالة 0:
	  /* For global variables, update the copy of the type that
	     exists in the binding.  */
	  إذا (وڻ_عوامي (decl))
	    {
	      بنية c_binding *b_ext = I_نشان_BINDING (DECL_NAME (decl));
	      طالما (b_ext && !B_اندريون_EXTERNAL_SCOPE (b_ext))
		b_ext = b_ext->shadowed;
	      إذا (b_ext && وڻ_ڪوڊ (decl) == وڻ_ڪوڊ (b_ext->decl))
		{
		  إذا (b_ext->u.type && comptypes (b_ext->u.type, type))
		    b_ext->u.type = مرکب_type (b_ext->u.type, type);
		  وإلا
		    b_ext->u.type = type;
		}
	    }
	  اكسر;

	افتراضي:
	  gcc_unreachable ();
	}

      إذا (DECL_INITIAL (decl) && DECL_INITIAL (decl) != error_mark_ڳنڍ)
	وڻ_TYPE (DECL_INITIAL (decl)) = type;

      relayout_decl (decl);
    }

  /* Look for braced array initializers for character arrays and
     recursively convert them into STRING_CSTs.  */
  إذا (وڻ init = DECL_INITIAL (decl))
    DECL_INITIAL (decl) = braced_lists_منزل_لڙيون (type, init);

  إذا (VAR_P (decl))
    {
      إذا (init && وڻ_ڪوڊ (init) == CONSTRUCTOR)
	جوڙيو_flexible_array_elts_منزل_سائيز (decl, init);

      complete_flexible_array_elts (DECL_INITIAL (decl));

      إذا (is_global_var (decl))
	{
	  type_context_قسم context = (DECL_THREAD_LOCAL_P (decl)
				       ? TCTX_THREAD_STORAGE
				       : TCTX_STATIC_STORAGE);
	  إذا (!verify_type_context (داخلا_location, context, وڻ_TYPE (decl)))
	    وڻ_TYPE (decl) = error_mark_ڳنڍ;
	}

      إذا (DECL_سائيز (decl) == NULL_وڻ && وڻ_TYPE (decl) != error_mark_ڳنڍ
	  && COMPLETE_TYPE_P (وڻ_TYPE (decl)))
	layout_decl (decl, 0);

      إذا (DECL_سائيز (decl) == NULL_وڻ
	  /* Don't give an error if we already gave one earlier.  */
	  && وڻ_TYPE (decl) != error_mark_ڳنڍ
	  && (وڻ_STATIC (decl)
	      /* A static variable with an incomplete type
		 is an error if it is initialized.
		 Also if it is not file scope.
		 Also if it is thread-local (in C23).
		 Otherwise, let it through, but if it is not `extern'
		 then it may cause an error message later.  */
	      ? (DECL_INITIAL (decl) != NULL_وڻ
		 || !DECL_FILE_SCOPE_P (decl)
		 || (flag_isoc23 && DECL_THREAD_LOCAL_P (decl)))
	      /* An automatic variable with an incomplete type
		 is an error.  */
	      : !DECL_EXTERNAL (decl)))
	 {
	   error ("storage size of %q+D isn%'t known", decl);
	   وڻ_TYPE (decl) = error_mark_ڳنڍ;
	 }

      إذا ((رڪارڊ_OR_UNION_TYPE_P (وڻ_TYPE (decl))
	  || وڻ_ڪوڊ (وڻ_TYPE (decl)) == ENUMERAL_TYPE)
	  && DECL_سائيز (decl) == NULL_وڻ
	  && وڻ_STATIC (decl))
	incomplete_رڪارڊ_decls.محفوظ_ڌڪو (decl);

      إذا (is_global_var (decl)
	  && DECL_سائيز (decl) != NULL_وڻ
	  && وڻ_TYPE (decl) != error_mark_ڳنڍ)
	{
	  إذا (وڻ_ڪوڊ (DECL_سائيز (decl)) == INTEGER_CST)
	    constant_اظهار_warning (DECL_سائيز (decl));
	  وإلا
	    {
	      error ("storage size of %q+D isn%'t constant", decl);
	      وڻ_TYPE (decl) = error_mark_ڳنڍ;
	    }
	}

      إذا (وڻ_استعمال_ٿيل (type))
	{
	  وڻ_استعمال_ٿيل (decl) = 1;
	  DECL_READ_P (decl) = 1;
	}
    }

  /* If this is a function and an assembler name is specified, reset DECL_RTL
     so we can give it its new name.  Also, update builtin_decl if it
     was a normal built-in.  */
  إذا (وڻ_ڪوڊ (decl) == FUNCTION_DECL && asmspec)
    {
      إذا (DECL_BUILT_اندريون_CLASS (decl) == BUILT_اندريون_عام)
	سيٽ_builtin_user_assembler_name (decl, asmspec);
      سيٽ_user_assembler_name (decl, asmspec);
    }

  /* If #pragma weak was used, mark the decl weak now.  */
  maybe_apply_pragma_weak (decl);

  /* Output the assembler code and/or RTL code for variables and functions,
     unless the type is an undefined structure or union.
     If not, it will get done when the type is completed.  */

  إذا (VAR_OR_FUNCTION_DECL_P (decl))
    {
      /* Determine the ELF visibility.  */
      إذا (وڻ_عوامي (decl))
	c_determine_visibility (decl);

      /* This is a no-op in c-lang.cc or something real in objc-act.cc.  */
      إذا (c_dialect_objc ())
	objc_check_decl (decl);

      إذا (asmspec)
	{
	  /* If this is not a static variable, issue a warning.
	     It doesn't make any sense to give an ASMSPEC for an
	     ordinary, non-register local variable.  Historically,
	     GCC has accepted -- but ignored -- the ASMSPEC in
	     this case.  */
	  إذا (!DECL_FILE_SCOPE_P (decl)
	      && VAR_P (decl)
	      && !C_DECL_رجسٽر (decl)
	      && !وڻ_STATIC (decl))
	    warning (0, "ignoring %<asm%> specifier for non-static local "
		     "variable %q+D", decl);
	  وإلا
	    سيٽ_user_assembler_name (decl, asmspec);
	}

      إذا (DECL_FILE_SCOPE_P (decl))
	{
	  إذا (DECL_INITIAL (decl) == NULL_وڻ
	      || DECL_INITIAL (decl) == error_mark_ڳنڍ)
	    /* Don't output anything
	       when a tentative file-scope definition is seen.
	       But at end of compilation, do output code for them.  */
	    DECL_DEFER_OUTPUT (decl) = 1;
	  إذا (asmspec && VAR_P (decl) && C_DECL_رجسٽر (decl))
	    DECL_HARD_رجسٽر (decl) = 1;
	  rest_جو_decl_compilation (decl, سچ, 0);

	  إذا (وڻ_ڪوڊ (decl) == FUNCTION_DECL)
	    {
	      وڻ parms = DECL_ARGUMENTS (decl);
	      ثابت منطقي builtin = fndecl_built_اندريون_p (decl);
	      إذا (وڻ access = build_attr_access_from_parms (parms, !builtin))
		decl_خاصيتون (&decl, access, 0);
	    }
	}
      وإلا
	{
	  /* In conjunction with an ASMSPEC, the `register'
	     keyword indicates that we should place the variable
	     in a particular register.  */
	  إذا (asmspec && C_DECL_رجسٽر (decl))
	    {
	      DECL_HARD_رجسٽر (decl) = 1;
	      /* This cannot be done for a structure with volatile
		 fields, on which DECL_REGISTER will have been
		 reset.  */
	      إذا (!DECL_رجسٽر (decl))
		error ("cannot put object with volatile field into register");
	    }

	  إذا (وڻ_ڪوڊ (decl) != FUNCTION_DECL)
	    {
	      /* If we're building a variable sized type, and we might be
		 reachable other than via the top of the current binding
		 level, then create a new BIND_EXPR so that we deallocate
		 the object at the right time.  */
	      /* Note that DECL_SIZE can be null due to errors.  */
	      إذا (DECL_سائيز (decl)
		  && !وڻ_CONSTANT (DECL_سائيز (decl))
		  && STATEMENT_LIST_HAS_LABEL (cur_stmt_list))
		{
		  وڻ bind;
		  bind = build3 (BIND_اظهار, void_type_ڳنڍ, عدم, عدم, عدم);
		  وڻ_SIDE_EFFECTS (bind) = 1;
		  جوڙيو_stmt (bind);
		  BIND_اظهار_BODY (bind) = ڌڪو_stmt_list ();
		}
	      جوڙيو_stmt (build_stmt (DECL_ذريعو_LOCATION (decl),
				    DECL_اظهار, decl));
	    }
	}


      إذا (!DECL_FILE_SCOPE_P (decl))
	{
	  /* Recompute the RTL of a local array now
	     if it used to be an incomplete type.  */
	  إذا (was_incomplete && !is_global_var (decl))
	    {
	      /* If we used it already as memory, it must stay in memory.  */
	      وڻ_ADDRESSABLE (decl) = وڻ_استعمال_ٿيل (decl);
	      /* If it's still incomplete now, no init will save it.  */
	      إذا (DECL_سائيز (decl) == NULL_وڻ)
		DECL_INITIAL (decl) = NULL_وڻ;
	    }
	}
    }

  إذا (وڻ_ڪوڊ (decl) == TYPE_DECL)
    {
      إذا (!DECL_FILE_SCOPE_P (decl)
	  && c_type_variably_modified_p (وڻ_TYPE (decl)))
	جوڙيو_stmt (build_stmt (DECL_ذريعو_LOCATION (decl), DECL_اظهار, decl));

      rest_جو_decl_compilation (decl, DECL_FILE_SCOPE_P (decl), 0);
    }

  /* Install a cleanup (aka destructor) if one was given.  */
  إذا (VAR_P (decl) && !وڻ_STATIC (decl))
    {
      وڻ attr = lookup_attribute ("cleanup", DECL_خاصيتون (decl));
      إذا (attr)
	{
	  وڻ cleanup_id = وڻ_قدر (وڻ_قدر (attr));
	  وڻ cleanup_decl = lookup_name (cleanup_id);
	  وڻ cleanup;
	  vec<وڻ, va_gc> *v;

	  /* Build "cleanup(&decl)" for the destructor.  */
	  cleanup = build_unary_op (داخلا_location, ADDR_اظهار, decl, خطأ);
	  vec_alloc (v, 1);
	  v->تيز_ڌڪو (cleanup);
	  cleanup = c_build_function_call_vec (DECL_ذريعو_LOCATION (decl),
					       vNULL, cleanup_decl, v, عدم);
	  vec_free (v);

	  /* Don't warn about decl unused; the cleanup uses it.  */
	  وڻ_استعمال_ٿيل (decl) = 1;
	  وڻ_استعمال_ٿيل (cleanup_decl) = 1;
	  DECL_READ_P (decl) = 1;

	  ڌڪو_cleanup (decl, cleanup, خطأ);
	}
    }

  إذا (warn_cxx_compat
      && VAR_P (decl)
      && !DECL_EXTERNAL (decl)
      && DECL_INITIAL (decl) == NULL_وڻ)
    {
      type = strip_array_types (type);
      إذا (وڻ_READONLY (decl))
	warning_at (DECL_ذريعو_LOCATION (decl), OPT_Wc___compat,
		    "uninitialized %<const %D%> is invalid in C++", decl);
      وإلا إذا (رڪارڊ_OR_UNION_TYPE_P (type)
	       && C_TYPE_FIELDS_READONLY (type))
	diagnose_uninitialized_cst_member (decl, type);
    }

  إذا (flag_openmp
      && VAR_P (decl)
      && lookup_attribute ("omp declare target implicit",
			   DECL_خاصيتون (decl)))
    {
      DECL_خاصيتون (decl)
	= remove_attribute ("omp declare target implicit",
			    DECL_خاصيتون (decl));
      إذا (!omp_mappable_type (وڻ_TYPE (decl)))
	error ("%q+D in declare target directive does not have mappable type",
	       decl);
      وإلا إذا (!lookup_attribute ("omp declare target",
				  DECL_خاصيتون (decl))
	       && !lookup_attribute ("omp declare target link",
				     DECL_خاصيتون (decl)))
	{
	  DECL_خاصيتون (decl)
	    = وڻ_cons (get_identifier ("omp declare target"),
			 NULL_وڻ, DECL_خاصيتون (decl));
	    symtab_ڳنڍ *ڳنڍ = symtab_ڳنڍ::get (decl);
	    إذا (ڳنڍ != عدم)
	      {
		ڳنڍ->offloadable = 1;
		إذا (ENABLE_OFFLOADING)
		  {
		    g->have_offload = سچ;
		    إذا (is_a <varpool_ڳنڍ *> (ڳنڍ))
		      vec_محفوظ_ڌڪو (offload_vars, decl);
		  }
	      }
	}
    }

  /* This is the last point we can lower alignment so give the target the
     chance to do so.  */
  إذا (VAR_P (decl)
      && !is_global_var (decl)
      && !DECL_HARD_رجسٽر (decl))
    targetm.هيٺاهون_local_decl_alignment (decl);

  invoke_plugin_callbacks (PLUGIN_پڄاڻي_DECL, decl);
}

/* Given a parsed parameter declaration, decode it into a PARM_DECL.
   EXPR is NULL or a pointer to an expression that needs to be
   evaluated for the side effects of array size expressions in the
   parameters.  */

وڻ
grokparm (ثابت بنية c_parm *parm, وڻ *اظهار)
{
  وڻ attrs = parm->attrs;
  وڻ decl = grokdeclarator (parm->declarator, parm->specs, PARM, خطأ,
			      عدم, &attrs, اظهار, عدم, DEPRECATED_عام);

  decl_خاصيتون (&decl, attrs, 0);

  أرجع decl;
}



/* Given a parsed parameter declaration, decode it into a PARM_DECL
   and push that on the current scope.  EXPR is a pointer to an
   expression that needs to be evaluated for the side effects of array
   size expressions in the parameters.  */

فراغ
ڌڪو_parm_decl (ثابت بنية c_parm *parm, وڻ *اظهار)
{
  وڻ attrs = parm->attrs;
  وڻ decl = grokdeclarator (parm->declarator, parm->specs, PARM, خطأ, عدم,
			      &attrs, اظهار, عدم, DEPRECATED_عام);
  إذا (decl && DECL_P (decl))
    DECL_ذريعو_LOCATION (decl) = parm->loc;

  decl_خاصيتون (&decl, attrs, 0);

  decl = pushdecl (decl);

  پڄاڻي_decl (decl, داخلا_location, NULL_وڻ, NULL_وڻ, NULL_وڻ);
}

/* Mark all the parameter declarations to date as forward decls.
   Also diagnose use of this extension.  */

فراغ
mark_forward_parm_decls (فراغ)
{
  بنية c_binding *b;

  إذا (current_scope->had_forward_parm_decls)
    warning_at (داخلا_location, OPT_Wmultiple_parameter_fwd_decl_lists,
		"more than one list of forward declarations of parameters");
  إذا (pedantic && !current_scope->had_forward_parm_decls)
    pedwarn (داخلا_location, OPT_Wpedantic,
	     "ISO C forbids forward parameter declarations");

  current_scope->had_forward_parm_decls = سچ;

  لكل (b = current_scope->bindings; b; b = b->prev)
    إذا (وڻ_ڪوڊ (b->decl) == PARM_DECL)
      وڻ_ASM_WRITTEN (b->decl) = 1;
}

/* Build a COMPOUND_LITERAL_EXPR.  TYPE is the type given in the compound
   literal, which may be an incomplete array type completed by the
   initializer; INIT is a CONSTRUCTOR at LOC that initializes the compound
   literal.  NON_CONST is true if the initializers contain something
   that cannot occur in a constant expression.  If ALIGNAS_ALIGN is nonzero,
   it is the (valid) alignment for this compound literal, as specified
   with _Alignas.  SCSPECS are the storage class specifiers (C23) from the
   compound literal.  */

وڻ
build_compound_literal (location_t loc, وڻ type, وڻ init, منطقي non_const,
			بنانشان صحيح alignas_align,
			بنية c_declspecs *scspecs)
{
  /* We do not use start_decl here because we have a type, not a declarator;
     and do not use finish_decl because the decl should be stored inside
     the COMPOUND_LITERAL_EXPR rather than added elsewhere as a DECL_EXPR.  */
  وڻ decl;
  وڻ complit;
  وڻ stmt;
  منطقي threadp = scspecs ? scspecs->thread_p : خطأ;
  تعداد c_storage_class storage_class = (scspecs
					? scspecs->storage_class
					: csc_none);

  إذا (type == error_mark_ڳنڍ
      || init == error_mark_ڳنڍ)
    أرجع error_mark_ڳنڍ;

  إذا (current_scope == file_scope && storage_class == csc_رجسٽر)
    {
      error_at (loc, "file-scope compound literal specifies %<register%>");
      storage_class = csc_none;
    }

  إذا (current_scope != file_scope && threadp && storage_class == csc_none)
    {
      error_at (loc, "compound literal implicitly auto and declared %qs",
		scspecs->thread_gnu_p ? "__thread" : "_Thread_local");
      threadp = خطأ;
    }

  decl = build_decl (loc, VAR_DECL, NULL_وڻ, type);
  DECL_EXTERNAL (decl) = 0;
  وڻ_عوامي (decl) = 0;
  وڻ_STATIC (decl) = (current_scope == file_scope
			|| storage_class == csc_static);
  DECL_CONTEXT (decl) = current_function_decl;
  وڻ_استعمال_ٿيل (decl) = 1;
  DECL_READ_P (decl) = 1;
  DECL_ARTIFICIAL (decl) = 1;
  DECL_IGNORED_P (decl) = 1;
  C_DECL_COMPOUND_LITERAL_P (decl) = 1;
  C_DECL_DECLARED_CONSTEXPR (decl) = scspecs && scspecs->constexpr_p;
  وڻ_TYPE (decl) = type;
  إذا (threadp)
    سيٽ_decl_tls_model (decl, decl_default_tls_model (decl));
  إذا (storage_class == csc_رجسٽر)
    {
      C_DECL_رجسٽر (decl) = 1;
      DECL_رجسٽر (decl) = 1;
    }
  c_apply_type_quals_منزل_decl (TYPE_QUALS (strip_array_types (type)), decl);
  إذا (alignas_align)
    {
      سيٽ_DECL_ALIGN (decl, alignas_align * بٽ_في_UNIT);
      DECL_USER_ALIGN (decl) = 1;
    }
  store_init_قدر (loc, decl, init, NULL_وڻ);
  إذا (current_scope != file_scope
      && وڻ_STATIC (decl)
      && !وڻ_READONLY (decl)
      && DECL_DECLARED_INLINE_P (current_function_decl)
      && DECL_EXTERNAL (current_function_decl))
    رڪارڊ_inline_static (داخلا_location, current_function_decl,
			  decl, csi_modifiable);

  إذا (وڻ_ڪوڊ (type) == ARRAY_TYPE && !COMPLETE_TYPE_P (type))
    {
      صحيح failure = complete_array_type (&وڻ_TYPE (decl),
					 DECL_INITIAL (decl), سچ);
      /* If complete_array_type returns 3, it means that the initial value of
         the compound literal is empty.  Allow it with a pedwarn; in pre-C23
         modes, the empty initializer itself has been diagnosed if pedantic so
         does not need to be diagnosed again here.  */
      gcc_assert (failure == 0 || failure == 3);
      إذا (failure == 3 && flag_isoc23)
	pedwarn (loc, OPT_Wpedantic,
		 "array of unknown size with empty initializer");

      type = وڻ_TYPE (decl);
      وڻ_TYPE (DECL_INITIAL (decl)) = type;
      relayout_decl (decl);
    }

  إذا (type == error_mark_ڳنڍ || !COMPLETE_TYPE_P (type))
    {
      c_incomplete_type_error (loc, NULL_وڻ, type);
      أرجع error_mark_ڳنڍ;
    }

  إذا ((وڻ_STATIC (decl) || C_DECL_DECLARED_CONSTEXPR (decl))
      && C_TYPE_VARIABLE_سائيز (type))
    error_at (loc, "storage size isn%'t constant");

  إذا (وڻ_STATIC (decl)
      && !verify_type_context (loc, TCTX_STATIC_STORAGE, type))
    أرجع error_mark_ڳنڍ;

  stmt = build_stmt (DECL_ذريعو_LOCATION (decl), DECL_اظهار, decl);
  complit = build1 (COMPOUND_LITERAL_اظهار, type, stmt);
  وڻ_SIDE_EFFECTS (complit) = 1;

  layout_decl (decl, 0);

  إذا (وڻ_STATIC (decl))
    {
      /* This decl needs a name for the assembler output.  */
      سيٽ_compound_literal_name (decl);
      DECL_DEFER_OUTPUT (decl) = 1;
      DECL_COMDAT (decl) = 1;
      pushdecl (decl);
      rest_جو_decl_compilation (decl, 1, 0);
    }
  وإلا إذا (current_function_decl && !current_scope->parm_flag)
    pushdecl (decl);

  إذا (non_const)
    {
      complit = build2 (C_MAYBE_CONST_اظهار, type, عدم, complit);
      C_MAYBE_CONST_اظهار_NON_CONST (complit) = 1;
    }

  أرجع complit;
}

/* Check the type of a compound literal.  Here we just check that it
   is valid for C++.  */

فراغ
check_compound_literal_type (location_t loc, بنية c_type_name *type_name)
{
  إذا (warn_cxx_compat
      && (type_name->specs->typespec_قسم == ctsk_tagdef
          || type_name->specs->typespec_قسم == ctsk_tagfirstref
	  || type_name->specs->typespec_قسم == ctsk_tagfirstref_attrs))
    warning_at (loc, OPT_Wc___compat,
		"defining a type in a compound literal is invalid in C++");
}

/* Performs sanity checks on the TYPE and WIDTH of the bit-field NAME,
   replacing with appropriate values if they are invalid.  */

ساكن فراغ
check_bitfield_type_and_ويڪر (location_t loc, وڻ *type, وڻ *ويڪر,
			       وڻ orig_name)
{
  وڻ type_mv;
  بنانشان صحيح max_ويڪر;
  بنانشان HOST_WIDE_INT w;
  ثابت حرف *name = (orig_name
		      ? identifier_منزل_locale (IDENTIFIER_اشارو (orig_name))
		      : _("<anonymous>"));

  /* Detect and ignore out of range field width and process valid
     field widths.  */
  إذا (!INTEGRAL_TYPE_P (وڻ_TYPE (*ويڪر)))
    {
      error_at (loc, "bit-field %qs width not an integer constant", name);
      *ويڪر = integer_one_ڳنڍ;
    }
  وإلا
    {
      إذا (وڻ_ڪوڊ (*ويڪر) != INTEGER_CST)
	{
	  *ويڪر = c_fully_fold (*ويڪر, خطأ, عدم);
	  إذا (وڻ_ڪوڊ (*ويڪر) == INTEGER_CST)
	    pedwarn (loc, OPT_Wpedantic,
		     "bit-field %qs width not an integer constant expression",
		     name);
	}
      إذا (وڻ_ڪوڊ (*ويڪر) != INTEGER_CST)
	{
	  error_at (loc, "bit-field %qs width not an integer constant", name);
	  *ويڪر = integer_one_ڳنڍ;
	}
      constant_اظهار_warning (*ويڪر);
      إذا (وڻ_int_cst_sgn (*ويڪر) < 0)
	{
	  error_at (loc, "negative width in bit-field %qs", name);
	  *ويڪر = integer_one_ڳنڍ;
	}
      وإلا إذا (integer_zerop (*ويڪر) && orig_name)
	{
	  error_at (loc, "zero width for bit-field %qs", name);
	  *ويڪر = integer_one_ڳنڍ;
	}
    }

  /* Detect invalid bit-field type.  */
  إذا (وڻ_ڪوڊ (*type) != INTEGER_TYPE
      && وڻ_ڪوڊ (*type) != BOOLEAN_TYPE
      && وڻ_ڪوڊ (*type) != ENUMERAL_TYPE
      && وڻ_ڪوڊ (*type) != BITINT_TYPE)
    {
      error_at (loc, "bit-field %qs has invalid type", name);
      *type = unsigned_type_ڳنڍ;
    }

  إذا (TYPE_WARN_IF_NOT_ALIGN (*type))
    {
      error_at (loc, "cannot declare bit-field %qs with %<warn_if_not_aligned%> type",
		name);
      *type = unsigned_type_ڳنڍ;
    }

  type_mv = TYPE_MAIN_VARIANT (*type);
  إذا (!اندريون_system_سرو_at (داخلا_location)
      && type_mv != integer_type_ڳنڍ
      && type_mv != unsigned_type_ڳنڍ
      && type_mv != boolean_type_ڳنڍ)
    pedwarn_c90 (loc, OPT_Wpedantic,
		 "type of bit-field %qs is a GCC extension", name);

  max_ويڪر = TYPE_PRECISION (*type);

  إذا (compare_وڻ_int (*ويڪر, max_ويڪر) > 0)
    {
      error_at (loc, "width of %qs exceeds its type", name);
      w = max_ويڪر;
      *ويڪر = build_int_cst (integer_type_ڳنڍ, w);
    }
  وإلا
    w = وڻ_منزل_uhwi (*ويڪر);

  /* Truncation of hardbool false and true representation values is always safe:
     either the values remain different, or we'll report a problem when creating
     the narrower type.  */
  إذا (c_hardbool_type_attr (*type))
    أرجع;

  إذا (وڻ_ڪوڊ (*type) == ENUMERAL_TYPE)
    {
      بنية lang_type *lt = TYPE_LANG_SPECIFIC (*type);
      إذا (!lt
	  || w < وڻ_int_cst_min_precision (lt->enum_min, TYPE_SIGN (*type))
	  || w < وڻ_int_cst_min_precision (lt->enum_max, TYPE_SIGN (*type)))
	warning_at (loc, 0, "%qs is narrower than values of its type", name);
    }
}



/* Print warning about variable length array if necessary.  */

ساكن فراغ
warn_variable_ڊيگهائي_array (وڻ name, وڻ سائيز)
{
  إذا (وڻ_CONSTANT (سائيز))
    {
      إذا (name)
	pedwarn_c90 (داخلا_location, OPT_Wvla,
		     "ISO C90 forbids array %qE whose size "
		     "cannot be evaluated", name);
      وإلا
	pedwarn_c90 (داخلا_location, OPT_Wvla, "ISO C90 forbids array "
		     "whose size cannot be evaluated");
    }
  وإلا
    {
      إذا (name)
	pedwarn_c90 (داخلا_location, OPT_Wvla,
		     "ISO C90 forbids variable length array %qE", name);
      وإلا
	pedwarn_c90 (داخلا_location, OPT_Wvla, "ISO C90 forbids variable "
		     "length array");
    }
}

/* Returns the smallest location != UNKNOWN_LOCATION in LOCATIONS,
   considering only those c_declspec_words found in LIST, which
   must be terminated by cdw_number_of_elements.  */

ساكن location_t
سڀ_کان_ننڍو_type_quals_location (ثابت location_t *locations,
			      ثابت c_declspec_لفظ *list)
{
  location_t loc = UNKNOWN_LOCATION;
  طالما (*list != cdw_عدد_جو_elements)
    {
      location_t newloc = locations[*list];
      إذا (loc == UNKNOWN_LOCATION
	  || (newloc != UNKNOWN_LOCATION && newloc < loc))
	loc = newloc;
      list++;
    }

  أرجع loc;
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
ساكن فراغ
جوڙيو_decl_اظهار (location_t loc, وڻ type, وڻ *اظهار, منطقي سيٽ_name_p)
{
  وڻ bind = NULL_وڻ;
  إذا (اظهار)
    {
      bind = build3 (BIND_اظهار, void_type_ڳنڍ, NULL_وڻ, NULL_وڻ,
		     NULL_وڻ);
      وڻ_SIDE_EFFECTS (bind) = 1;
      BIND_اظهار_BODY (bind) = ڌڪو_stmt_list ();
      ڌڪو_scope ();
    }

  وڻ decl = build_decl (loc, TYPE_DECL, NULL_وڻ, type);
  pushdecl (decl);
  DECL_ARTIFICIAL (decl) = 1;
  جوڙيو_stmt (build_stmt (DECL_ذريعو_LOCATION (decl), DECL_اظهار, decl));
  إذا (سيٽ_name_p)
    TYPE_NAME (type) = decl;

  إذا (bind)
    {
      ڪڍو_scope ();
      BIND_اظهار_BODY (bind) = ڪڍو_stmt_list (BIND_اظهار_BODY (bind));
      إذا (*اظهار)
	*اظهار = build2 (COMPOUND_اظهار, void_type_ڳنڍ, *اظهار, bind);
      وإلا
	*اظهار = bind;
    }
}


/* Add attribute "arg spec" to ATTRS corresponding to an array/VLA parameter
   declared with type TYPE.  The attribute has two arguments.  The first is
   a string that encodes the presence of the static keyword.  The second is
   the declared type of the array before adjustment, i.e. as an array type
   including the outermost bound.  */

ساكن وڻ
build_arg_spec_attribute (وڻ type, منطقي static_p, وڻ attrs)
{
  وڻ vbchain = وڻ_cons (NULL_وڻ, type, NULL_وڻ);
  وڻ acsstr = static_p ? build_string (7, "static") :
			   build_string (1, "");
  وڻ دليلون = وڻ_cons (NULL_وڻ, acsstr, vbchain);
  وڻ name = get_identifier ("arg spec");
  أرجع وڻ_cons (name, دليلون, attrs);
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

ساكن وڻ
grokdeclarator (ثابت بنية c_declarator *declarator,
		بنية c_declspecs *declspecs,
		تعداد decl_context decl_context, منطقي initialized, وڻ *ويڪر,
		وڻ *decl_attrs, وڻ *اظهار, منطقي *اظهار_const_operands,
		تعداد deprecated_حالتون deprecated_state)
{
  وڻ type = declspecs->type;
  منطقي threadp = declspecs->thread_p;
  منطقي constexprp = declspecs->constexpr_p;
  تعداد c_storage_class storage_class = declspecs->storage_class;
  صحيح constp;
  صحيح restrictp;
  صحيح volatilep;
  صحيح atomicp;
  صحيح type_quals = TYPE_UNQUALIFIED;
  وڻ name = NULL_وڻ;
  منطقي funcdef_flag = خطأ;
  منطقي funcdef_syntax = خطأ;
  منطقي سائيز_varies = خطأ;
  منطقي سائيز_error = خطأ;
  وڻ decl_attr = declspecs->decl_attr;
  صحيح array_ptr_quals = TYPE_UNQUALIFIED;
  وڻ array_ptr_attrs = NULL_وڻ;
  منطقي array_parm_static = خطأ;
  منطقي array_parm_vla_unspec_p = خطأ;
  وڻ returned_attrs = NULL_وڻ;
  وڻ decl_id_attrs = NULL_وڻ;
  منطقي bitfield = ويڪر != عدم;
  وڻ element_type;
  وڻ orig_qual_type = عدم;
  سائيز_t orig_qual_اڻسڌو = 0;
  بنية c_arg_info *arg_info = 0;
  addr_space_t as1, as2, پتو_space;
  location_t loc = UNKNOWN_LOCATION;
  وڻ اظهار_dummy;
  منطقي اظهار_const_operands_dummy;
  تعداد c_declarator_قسم پهريون_non_attr_قسم;
  بنانشان صحيح alignas_align = 0;

  إذا (type == NULL_وڻ)
    {
      /* This can occur for auto on a parameter in C23 mode.  Set a
	 dummy type here so subsequent code can give diagnostics for
	 this case.  */
      gcc_assert (declspecs->c23_auto_p);
      gcc_assert (decl_context == PARM);
      type = declspecs->type = integer_type_ڳنڍ;
    }
  إذا (وڻ_ڪوڊ (type) == ERROR_MARK)
    أرجع error_mark_ڳنڍ;
  إذا (اظهار == عدم)
    {
      اظهار = &اظهار_dummy;
      اظهار_dummy = NULL_وڻ;
    }
  إذا (اظهار_const_operands == عدم)
    اظهار_const_operands = &اظهار_const_operands_dummy;

  إذا (declspecs->اظهار)
    {
      إذا (*اظهار)
	*اظهار = build2 (COMPOUND_اظهار, وڻ_TYPE (declspecs->اظهار), *اظهار,
			declspecs->اظهار);
      وإلا
	*اظهار = declspecs->اظهار;
    }
  *اظهار_const_operands = declspecs->اظهار_const_operands;

  إذا (decl_context == FUNCDEF)
    funcdef_flag = سچ, decl_context = عام_2;

  /* Look inside a declarator for the name being declared
     and get it as an IDENTIFIER_NODE, for an error message.  */
  {
    ثابت بنية c_declarator *decl = declarator;

    پهريون_non_attr_قسم = cdk_attrs;
    طالما (decl)
      بدل (decl->قسم)
	{
	حالة cdk_array:
	  loc = decl->id_loc;
	  /* FALL THRU.  */

	حالة cdk_function:
	حالة cdk_اشارو:
	  funcdef_syntax = (decl->قسم == cdk_function);
	  إذا (پهريون_non_attr_قسم == cdk_attrs)
	    پهريون_non_attr_قسم = decl->قسم;
	  decl = decl->declarator;
	  اكسر;

	حالة cdk_attrs:
	  decl = decl->declarator;
	  اكسر;

	حالة cdk_id:
	  loc = decl->id_loc;
	  إذا (decl->u.id.id)
	    name = decl->u.id.id;
	  decl_id_attrs = decl->u.id.attrs;
	  إذا (پهريون_non_attr_قسم == cdk_attrs)
	    پهريون_non_attr_قسم = decl->قسم;
	  decl = 0;
	  اكسر;

	افتراضي:
	  gcc_unreachable ();
	}
    إذا (name == NULL_وڻ)
      {
	gcc_assert (decl_context == PARM
		    || decl_context == TYPENAME
		    || decl_context == GENERIC_ASSOC
		    || (decl_context == ميدان
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
  إذا (declspecs->enum_type_specifier_ref_p)
    error_at (loc, "%<enum%> underlying type may not be specified here");

  /* A function definition's declarator must have the form of
     a function declarator.  */

  إذا (funcdef_flag && !funcdef_syntax)
    أرجع NULL_وڻ;

  /* If this looks like a function definition, make it one,
     even if it occurs where parms are expected.
     Then store_parm_decls will reject it and not use it as a parm.  */
  إذا (decl_context == عام_2 && !funcdef_flag && current_scope->parm_flag)
    decl_context = PARM;

  إذا (deprecated_state != UNAVAILABLE_DEPRECATED_SUPPRESS)
    {
      إذا (declspecs->unavailable_p)
	error_unavailable_use (declspecs->type, declspecs->decl_attr);
      وإلا إذا (declspecs->deprecated_p
		&& deprecated_state != DEPRECATED_SUPPRESS)
	warn_deprecated_use (declspecs->type, declspecs->decl_attr);
    }

  إذا ((decl_context == عام_2 || decl_context == ميدان)
      && current_scope == file_scope
      && c_type_variably_modified_p (type))
    {
      إذا (name)
	error_at (loc, "variably modified %qE at file scope", name);
      وإلا
	error_at (loc, "variably modified field at file scope");
      type = integer_type_ڳنڍ;
    }

  سائيز_varies = C_TYPE_VARIABLE_سائيز (type) != 0;

  /* Diagnose defaulting to "int".  */

  إذا (declspecs->default_int_p)
    {
      /* Issue a warning if this is an ISO C 99 program or if
	 -Wreturn-type and this is a function, or if -Wimplicit;
	 prefer the former warning since it is more explicit.  */
      إذا ((warn_implicit_int || warn_return_type > 0 || flag_isoc99)
	  && funcdef_flag)
	warn_about_return_type = 1;
      وإلا
	{
	  إذا (name)
	    permerror_opt (loc, OPT_Wimplicit_int,
			   "type defaults to %<int%> in declaration "
			   "of %qE", name);
	  وإلا
	    permerror_opt (loc, OPT_Wimplicit_int,
			   "type defaults to %<int%> in type name");
	}
    }

  /* Adjust the type if a bit-field is being declared,
     -funsigned-bitfields applied and the type is not explicitly
     "signed".  */
  إذا (bitfield && !flag_signed_bitfields && !declspecs->explicit_signed_p
      && وڻ_ڪوڊ (type) == INTEGER_TYPE)
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
  as1 = declspecs->پتو_space;
  as2 = TYPE_ADDR_SPACE (element_type);
  پتو_space = ADDR_SPACE_GENERIC_P (as1)? as2 : as1;

  إذا (constp > 1)
    pedwarn_c90 (loc, OPT_Wpedantic, "duplicate %<const%>");
  إذا (restrictp > 1)
    pedwarn_c90 (loc, OPT_Wpedantic, "duplicate %<restrict%>");
  إذا (volatilep > 1)
    pedwarn_c90 (loc, OPT_Wpedantic, "duplicate %<volatile%>");
  إذا (atomicp > 1)
    pedwarn_c90 (loc, OPT_Wpedantic, "duplicate %<_Atomic%>");

  إذا (!ADDR_SPACE_GENERIC_P (as1) && !ADDR_SPACE_GENERIC_P (as2) && as1 != as2)
    error_at (loc, "conflicting named address spaces (%s vs %s)",
	      c_addr_space_name (as1), c_addr_space_name (as2));

  إذا ((وڻ_ڪوڊ (type) == ARRAY_TYPE
       || پهريون_non_attr_قسم == cdk_array)
      && TYPE_QUALS (element_type))
    {
      orig_qual_type = type;
      type = c_build_qualified_type (type, TYPE_UNQUALIFIED);
    }
  type_quals = ((constp ? TYPE_QUAL_CONST : 0)
		| (restrictp ? TYPE_QUAL_RESTRICT : 0)
		| (volatilep ? TYPE_QUAL_VOLATILE : 0)
		| (atomicp ? TYPE_QUAL_ATOMIC : 0)
		| ENCODE_QUAL_ADDR_SPACE (پتو_space));
  إذا (type_quals != TYPE_QUALS (element_type))
    orig_qual_type = NULL_وڻ;

  /* Applying the _Atomic qualifier to an array type (through the use
     of typedefs or typeof) must be detected here.  If the qualifier
     is introduced later, any appearance of applying it to an array is
     actually applying it to an element of that array.  */
  إذا (declspecs->atomic_p && وڻ_ڪوڊ (type) == ARRAY_TYPE)
    error_at (loc, "%<_Atomic%>-qualified array type");

  /* Warn about storage classes that are invalid for certain
     kinds of declarations (parameters, typenames, etc.).  */

  إذا (funcdef_flag
      && (threadp
	  || constexprp
	  || storage_class == csc_auto
	  || storage_class == csc_رجسٽر
	  || storage_class == csc_typedef))
    {
      إذا (storage_class == csc_auto)
	pedwarn (loc,
		 (current_scope == file_scope) ? 0 : OPT_Wpedantic,
		 "function definition declared %<auto%>");
      إذا (storage_class == csc_رجسٽر)
	error_at (loc, "function definition declared %<register%>");
      إذا (storage_class == csc_typedef)
	error_at (loc, "function definition declared %<typedef%>");
      إذا (threadp)
	error_at (loc, "function definition declared %qs",
		  declspecs->thread_gnu_p ? "__thread" : "_Thread_local");
      threadp = خطأ;
      /* The parser ensures a constexpr function definition never
	 reaches here.  */
      gcc_assert (!constexprp);
      إذا (storage_class == csc_auto
	  || storage_class == csc_رجسٽر
	  || storage_class == csc_typedef)
	storage_class = csc_none;
    }
  وإلا إذا (decl_context != عام_2 && (storage_class != csc_none
				      || threadp
				      || constexprp
				      || declspecs->c23_auto_p))
    {
      إذا (decl_context == PARM
	  && storage_class == csc_رجسٽر
	  && !constexprp
	  && !declspecs->c23_auto_p)
	;
      وإلا
	{
	  بدل (decl_context)
	    {
	    حالة ميدان:
	      إذا (name)
		error_at (loc, "storage class specified for structure "
		    	  "field %qE", name);
	      وإلا
		error_at (loc, "storage class specified for structure field");
	      اكسر;
	    حالة PARM:
	      إذا (name)
		error_at (loc, "storage class specified for parameter %qE",
		    	  name);
	      وإلا
		error_at (loc, "storage class specified for unnamed parameter");
	      اكسر;
	    افتراضي:
	      error_at (loc, "storage class specified for typename");
	      اكسر;
	    }
	  storage_class = csc_none;
	  threadp = خطأ;
	  constexprp = خطأ;
	}
    }
  وإلا إذا (storage_class == csc_extern
	   && initialized
	   && !funcdef_flag)
    {
      /* 'extern' with initialization is invalid if not at file scope.  */
       إذا (current_scope == file_scope)
         {
           /* It is fine to have 'extern const' when compiling at C
              and C++ intersection.  */
           إذا (!(warn_cxx_compat && constp))
             warning_at (loc, 0, "%qE initialized and declared %<extern%>",
		 	 name);
         }
      وإلا
	error_at (loc, "%qE has both %<extern%> and initializer", name);
    }
  وإلا إذا (current_scope == file_scope)
    {
      إذا (storage_class == csc_auto)
	error_at (loc, "file-scope declaration of %qE specifies %<auto%>",
	    	  name);
      إذا (pedantic && storage_class == csc_رجسٽر)
	pedwarn (داخلا_location, OPT_Wpedantic,
		 "file-scope declaration of %qE specifies %<register%>", name);
    }
  وإلا
    {
      إذا (storage_class == csc_extern && funcdef_flag)
	error_at (loc, "nested function %qE declared %<extern%>", name);
      وإلا إذا (threadp && storage_class == csc_none)
	{
	  error_at (loc, "function-scope %qE implicitly auto and declared "
		    "%qs", name,
		    declspecs->thread_gnu_p ? "__thread" : "_Thread_local");
	  threadp = خطأ;
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

  طالما (declarator && declarator->قسم != cdk_id)
    {
      إذا (type == error_mark_ڳنڍ)
	{
	  declarator = declarator->declarator;
	  استمر;
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

      إذا (array_ptr_quals != TYPE_UNQUALIFIED
	  || array_ptr_attrs != NULL_وڻ
	  || array_parm_static)
	{
	  /* Only the innermost declarator (making a parameter be of
	     array type which is converted to pointer type)
	     may have static or type qualifiers.  */
	  error_at (loc, "static or type qualifiers in non-parameter array declarator");
	  array_ptr_quals = TYPE_UNQUALIFIED;
	  array_ptr_attrs = NULL_وڻ;
	  array_parm_static = خطأ;
	}

      بدل (declarator->قسم)
	{
	حالة cdk_attrs:
	  {
	    /* A declarator with embedded attributes.  */
	    وڻ attrs = declarator->u.attrs;
	    ثابت بنية c_declarator *inner_decl;
	    صحيح attr_flags = 0;
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
	    طالما (inner_decl->قسم == cdk_attrs)
	      inner_decl = inner_decl->declarator;
	    إذا (!cxx11_attribute_p (attrs))
	      {
		إذا (inner_decl->قسم == cdk_id)
		  attr_flags |= (صحيح) ATTR_FLAG_DECL_ايندڙ;
		وإلا إذا (inner_decl->قسم == cdk_function)
		  attr_flags |= (صحيح) ATTR_FLAG_FUNCTION_ايندڙ;
		وإلا إذا (inner_decl->قسم == cdk_array)
		  attr_flags |= (صحيح) ATTR_FLAG_ARRAY_ايندڙ;
	      }
	    attrs = c_warn_type_خاصيتون (type, attrs);
	    returned_attrs = decl_خاصيتون (&type,
					      chainon (returned_attrs, attrs),
					      attr_flags);
	    اكسر;
	  }
	حالة cdk_array:
	  {
	    وڻ itype = NULL_وڻ;
	    وڻ سائيز = declarator->u.array.dimen;
	    /* The index is a signed object `sizetype' bits wide.  */
	    وڻ اشاريو_type = c_common_signed_type (sizetype);

	    array_ptr_quals = declarator->u.array.quals;
	    array_ptr_attrs = declarator->u.array.attrs;
	    array_parm_static = declarator->u.array.static_p;
	    array_parm_vla_unspec_p = declarator->u.array.vla_unspec_p;

	    declarator = declarator->declarator;

	    منطقي flexible_array_member = خطأ;

	    /* Check for some types that there cannot be arrays of.  */

	    إذا (VOID_TYPE_P (type))
	      {
		إذا (name)
		  error_at (loc, "declaration of %qE as array of voids", name);
		وإلا
		  error_at (loc, "declaration of type name as array of voids");
		type = error_mark_ڳنڍ;
	      }

	    إذا (وڻ_ڪوڊ (type) == FUNCTION_TYPE)
	      {
		إذا (name)
		  error_at (loc, "declaration of %qE as array of functions",
		      	    name);
		وإلا
		  error_at (loc, "declaration of type name as array of "
		            "functions");
		type = error_mark_ڳنڍ;
	      }

	    إذا (pedantic && !اندريون_system_سرو_at (داخلا_location)
		&& flexible_array_type_p (type))
	      pedwarn (loc, OPT_Wpedantic,
		       "invalid use of structure with flexible array member");

	    إذا (سائيز == error_mark_ڳنڍ)
	      type = error_mark_ڳنڍ;

	    إذا (type == error_mark_ڳنڍ)
	      استمر;

	    إذا (!verify_type_context (loc, TCTX_ARRAY_ELEMENT, type))
	      {
		type = error_mark_ڳنڍ;
		استمر;
	      }

	    /* If size was specified, set ITYPE to a range-type for
	       that size.  Otherwise, ITYPE remains null.  finish_decl
	       may figure it out from an initial value.  */

	    إذا (سائيز)
	      {
		منطقي سائيز_maybe_const = سچ;
		منطقي سائيز_int_const = (وڻ_ڪوڊ (سائيز) == INTEGER_CST
				       && !وڻ_حد_کان_مٿي (سائيز));
		منطقي this_سائيز_varies = خطأ;

		/* Strip NON_LVALUE_EXPRs since we aren't using as an
		   lvalue.  */
		STRIP_TYPE_NOPS (سائيز);

		إذا (!INTEGRAL_TYPE_P (وڻ_TYPE (سائيز)))
		  {
		    إذا (name)
		      error_at (loc, "size of array %qE has non-integer type",
				name);
		    وإلا
		      error_at (loc,
				"size of unnamed array has non-integer type");
		    سائيز = integer_one_ڳنڍ;
		    سائيز_int_const = سچ;
		    سائيز_error = سچ;
		  }
		/* This can happen with enum forward declaration.  */
		وإلا إذا (!COMPLETE_TYPE_P (وڻ_TYPE (سائيز)))
		  {
		    إذا (name)
		      error_at (loc, "size of array %qE has incomplete type",
				name);
		    وإلا
		      error_at (loc, "size of unnamed array has incomplete "
				"type");
		    سائيز = integer_one_ڳنڍ;
		    سائيز_int_const = سچ;
		    سائيز_error = سچ;
		  }

		سائيز = c_fully_fold (سائيز, خطأ, &سائيز_maybe_const);

		إذا (pedantic && سائيز_maybe_const && integer_zerop (سائيز))
		  {
		    إذا (name)
		      pedwarn (loc, OPT_Wpedantic,
			       "ISO C forbids zero-size array %qE", name);
		    وإلا
		      pedwarn (loc, OPT_Wpedantic,
			       "ISO C forbids zero-size array");
		  }

		إذا (وڻ_ڪوڊ (سائيز) == INTEGER_CST && سائيز_maybe_const)
		  {
		    constant_اظهار_warning (سائيز);
		    إذا (وڻ_int_cst_sgn (سائيز) < 0)
		      {
			إذا (name)
			  error_at (loc, "size of array %qE is negative", name);
			وإلا
			  error_at (loc, "size of unnamed array is negative");
			سائيز = integer_one_ڳنڍ;
			سائيز_int_const = سچ;
			سائيز_error = سچ;
		      }
		    /* Handle a size folded to an integer constant but
		       not an integer constant expression.  */
		    إذا (!سائيز_int_const)
		      {
			/* If this is a file scope declaration of an
			   ordinary identifier, this is invalid code;
			   diagnosing it here and not subsequently
			   treating the type as variable-length avoids
			   more confusing diagnostics later.  */
			إذا ((decl_context == عام_2 || decl_context == ميدان)
			    && current_scope == file_scope)
			  pedwarn (داخلا_location, 0,
				   "variably modified %qE at file scope",
				   name);
			وإلا
			  this_سائيز_varies = سائيز_varies = سچ;
			warn_variable_ڊيگهائي_array (name, سائيز);
		      }
		  }
		وإلا إذا ((decl_context == عام_2 || decl_context == ميدان)
			 && current_scope == file_scope)
		  {
		    error_at (loc, "variably modified %qE at file scope", name);
		    سائيز = integer_one_ڳنڍ;
		  }
		وإلا
		  {
		    /* Make sure the array size remains visibly
		       nonconstant even if it is (eg) a const variable
		       with known value.  */
		    this_سائيز_varies = سائيز_varies = سچ;
		    warn_variable_ڊيگهائي_array (name, سائيز);
		    إذا (sanitize_flags_p (SANITIZE_VLA)
			&& current_function_decl != NULL_وڻ
			&& decl_context == عام_2)
		      {
			/* Evaluate the array size only once.  */
			سائيز = save_اظهار (سائيز);
			سائيز = c_fully_fold (سائيز, خطأ, عدم);
		        سائيز = fold_build2 (COMPOUND_اظهار, وڻ_TYPE (سائيز),
					    ubsan_instrument_vla (loc, سائيز),
					    سائيز);
		      }
		  }

		إذا (integer_zerop (سائيز) && !this_سائيز_varies)
		  {
		    /* A zero-length array cannot be represented with
		       an unsigned index type, which is what we'll
		       get with build_index_type.  Create an
		       open-ended range instead.  */
		    itype = build_اشاريو_type (NULL_وڻ);
		  }
		وإلا
		  {
		    /* Arrange for the SAVE_EXPR on the inside of the
		       MINUS_EXPR, which allows the -1 to get folded
		       with the +1 that happens when building TYPE_SIZE.  */
		    إذا (سائيز_varies)
		      سائيز = save_اظهار (سائيز);
		    إذا (this_سائيز_varies && وڻ_ڪوڊ (سائيز) == INTEGER_CST)
		      سائيز = build2 (COMPOUND_اظهار, وڻ_TYPE (سائيز),
				     integer_zero_ڳنڍ, سائيز);

		    /* Compute the maximum valid index, that is, size
		       - 1.  Do the calculation in index_type, so that
		       if it is a variable the computations will be
		       done in the proper mode.  */
		    itype = fold_build2_loc (loc, MINUS_اظهار, اشاريو_type,
					     convert (اشاريو_type, سائيز),
					     convert (اشاريو_type,
						      سائيز_one_ڳنڍ));

		    /* The above overflows when size does not fit
		       in index_type.
		       ???  While a size of INT_MAX+1 technically shouldn't
		       cause an overflow (because we subtract 1), handling
		       this case seems like an unnecessary complication.  */
		    إذا (وڻ_ڪوڊ (سائيز) == INTEGER_CST
			&& !int_سمائي_type_p (سائيز, اشاريو_type))
		      {
			إذا (name)
			  error_at (loc, "size of array %qE is too large",
			            name);
			وإلا
			  error_at (loc, "size of unnamed array is too large");
			type = error_mark_ڳنڍ;
			استمر;
		      }

		    itype = build_اشاريو_type (itype);
		  }
		إذا (this_سائيز_varies)
		  {
		    إذا (وڻ_SIDE_EFFECTS (سائيز))
		      {
			إذا (*اظهار)
			  *اظهار = build2 (COMPOUND_اظهار, وڻ_TYPE (سائيز),
					  *اظهار, سائيز);
			وإلا
			  *اظهار = سائيز;
		      }
		    *اظهار_const_operands &= سائيز_maybe_const;
		  }
	      }
	    وإلا إذا (decl_context == ميدان)
	      {
		إذا (array_parm_vla_unspec_p)
		  /* Field names can in fact have function prototype
		     scope so [*] is disallowed here through making
		     the field variably modified, not through being
		     something other than a declaration with function
		     prototype scope.  */
		  سائيز_varies = سچ;
		وإلا
		  {
		    ثابت بنية c_declarator *t = declarator;
		    طالما (t->قسم == cdk_attrs)
		      t = t->declarator;
		    flexible_array_member = (t->قسم == cdk_id);
		  }
		إذا (flexible_array_member
		    && !اندريون_system_سرو_at (داخلا_location))
		  pedwarn_c90 (loc, OPT_Wpedantic, "ISO C90 does not "
			       "support flexible array members");

		/* ISO C99 Flexible array members are effectively
		   identical to GCC's zero-length array extension.  */
		إذا (flexible_array_member)
		  itype = build_اشاريو_type (NULL_وڻ);
	      }

	    /* Complain about arrays of incomplete types.  */
	    إذا (!COMPLETE_TYPE_P (type))
	      {
		auto_diagnostic_گروهه d;
		error_at (loc, "array type has incomplete element type %qT",
			  type);
		/* See if we can be more helpful.  */
		إذا (وڻ_ڪوڊ (type) == ARRAY_TYPE)
		  {
		    إذا (name)
		      inform (loc, "declaration of %qE as multidimensional "
			      "array must have bounds for all dimensions "
			      "except the first", name);
		    وإلا
		      inform (loc, "declaration of multidimensional array "
			      "must have bounds for all dimensions except "
			      "the first");
		  }
		type = error_mark_ڳنڍ;
	      }
	    وإلا
	    /* When itype is NULL, a shared incomplete array type is
	       returned for all array of a given type.  Elsewhere we
	       make sure we don't complete that type before copying
	       it, but here we want to make sure we don't ever
	       modify the shared type, so we gcc_assert (itype)
	       below.  */
	      {
		addr_space_t as = DECODE_QUAL_ADDR_SPACE (type_quals);
		إذا (!ADDR_SPACE_GENERIC_P (as) && as != TYPE_ADDR_SPACE (type))
		  type = c_build_qualified_type (type,
						 ENCODE_QUAL_ADDR_SPACE (as));
		إذا (array_parm_vla_unspec_p)
		  type = c_build_array_type_unspecified (type);
		/* The GCC extension for zero-length arrays differs from
		   ISO flexible array members in that sizeof yields
		   zero.  */
		وإلا إذا (سائيز && integer_zerop (سائيز))
		  type = c_build_array_type_zero_سائيز (type);
		وإلا
		  type = c_build_array_type (type, itype);

		إذا (!valid_array_سائيز_p (loc, type, name))
		  type = error_mark_ڳنڍ;
	      }

	    إذا (array_parm_vla_unspec_p)
	      {
		/* C99 6.7.5.2p4 */
		إذا (decl_context == TYPENAME)
		  warning (0, "%<[*]%> not in a declaration");
		وإلا إذا (decl_context != GENERIC_ASSOC
			 && decl_context != PARM
			 && decl_context != ميدان)
		  {
		    error ("%<[*]%> not allowed in other than function prototype scope "
			   "or generic association");
		    type = error_mark_ڳنڍ;
		  }
		سائيز_varies = سچ;
	      }


	    gcc_assert (type == error_mark_ڳنڍ
			|| flexible_array_member
			   == flexible_array_member_type_p (type));

	    إذا (decl_context != PARM
		&& (array_ptr_quals != TYPE_UNQUALIFIED
		    || array_ptr_attrs != NULL_وڻ
		    || array_parm_static))
	      {
		error_at (loc, "static or type qualifiers in non-parameter "
			  "array declarator");
		array_ptr_quals = TYPE_UNQUALIFIED;
		array_ptr_attrs = NULL_وڻ;
		array_parm_static = خطأ;
	      }
	    orig_qual_اڻسڌو++;
	    اكسر;
	  }
	حالة cdk_function:
	  {
	    /* Say it's a definition only for the declarator closest
	       to the identifier, apart possibly from some
	       attributes.  */
	    منطقي really_funcdef = خطأ;
	    وڻ arg_types;
	    orig_qual_type = NULL_وڻ;
	    إذا (funcdef_flag)
	      {
		ثابت بنية c_declarator *t = declarator->declarator;
		طالما (t->قسم == cdk_attrs)
		  t = t->declarator;
		really_funcdef = (t->قسم == cdk_id);
	      }

	    /* Declaring a function type.  Make sure we have a valid
	       type for the function to return.  */
	    إذا (type == error_mark_ڳنڍ)
	      استمر;

	    سائيز_varies = خطأ;

	    /* Warn about some types functions can't return.  */
	    إذا (وڻ_ڪوڊ (type) == FUNCTION_TYPE)
	      {
		إذا (name)
		  error_at (loc, "%qE declared as function returning a "
		      		 "function", name);
		وإلا
		  error_at (loc, "type name declared as function "
			    "returning a function");
		type = integer_type_ڳنڍ;
	      }
	    إذا (وڻ_ڪوڊ (type) == ARRAY_TYPE)
	      {
		إذا (name)
		  error_at (loc, "%qE declared as function returning an array",
		      	    name);
		وإلا
		  error_at (loc, "type name declared as function returning "
		      	    "an array");
		type = integer_type_ڳنڍ;
	      }

	    /* Construct the function type and go to the next
	       inner layer of declarator.  */
	    arg_info = declarator->u.arg_info;
	    arg_types = grokparms (arg_info, really_funcdef);

	    /* Type qualifiers before the return type of the function
	       qualify the return type, not the function type.  */
	    إذا (type_quals)
	      {
		ثابت تعداد c_declspec_لفظ ignored_quals_list[] =
		  {
		    cdw_const, cdw_volatile, cdw_restrict, cdw_پتو_space,
		    cdw_atomic, cdw_عدد_جو_elements
		  };
		location_t specs_loc
		  = سڀ_کان_ننڍو_type_quals_location (declspecs->locations,
						  ignored_quals_list);
		إذا (specs_loc == UNKNOWN_LOCATION)
		  specs_loc = declspecs->locations[cdw_typedef];
		إذا (specs_loc == UNKNOWN_LOCATION)
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
		صحيح quals_استعمال_ٿيل = type_quals;
		إذا (flag_isoc23)
		  quals_استعمال_ٿيل = 0;
		وإلا إذا (flag_isoc11)
		  quals_استعمال_ٿيل &= TYPE_QUAL_ATOMIC;
		إذا (quals_استعمال_ٿيل && VOID_TYPE_P (type) && really_funcdef)
		  pedwarn (specs_loc, 0,
			   "function definition has qualified void "
			   "return type");
		وإلا
		  warning_at (specs_loc, OPT_Wignored_qualifiers,
			      "type qualifiers ignored on function "
			      "return type");

		/* Ensure an error for restrict on invalid types; the
		   DR#423 resolution is not entirely clear about
		   this.  */
		إذا (flag_isoc11
		    && (type_quals & TYPE_QUAL_RESTRICT)
		    && (!اشارو_TYPE_P (type)
			|| !C_TYPE_OBJECT_OR_INCOMPLETE_P (وڻ_TYPE (type))))
		  error_at (loc, "invalid use of %<restrict%>");
		type = c_build_qualified_type (type, quals_استعمال_ٿيل);
	      }
	    type_quals = TYPE_UNQUALIFIED;

	    type = c_build_function_type (type, arg_types,
					  arg_info->no_named_دليلون_stdarg_p);
	    declarator = declarator->declarator;

	    /* Set the TYPE_CONTEXTs for each tagged type which is local to
	       the formal parameter list of this FUNCTION_TYPE to point to
	       the FUNCTION_TYPE node itself.  */
	    {
	      c_arg_ٽيگ *ٽيگ;
	      بنانشان ix;

	      FOR_EACH_VEC_محفوظ_ELT_ابتو (arg_info->ٽيگ_فهرست, ix, ٽيگ)
		TYPE_CONTEXT (ٽيگ->type) = type;
	    }
	    اكسر;
	  }
	حالة cdk_اشارو:
	  {
	    /* Merge any constancy or volatility into the target type
	       for the pointer.  */
	    إذا ((type_quals & TYPE_QUAL_ATOMIC)
		&& وڻ_ڪوڊ (type) == FUNCTION_TYPE)
	      {
		error_at (loc,
			  "%<_Atomic%>-qualified function type");
		type_quals &= ~TYPE_QUAL_ATOMIC;
	      }
	    وإلا إذا (pedantic && وڻ_ڪوڊ (type) == FUNCTION_TYPE
		     && type_quals)
	      pedwarn (loc, OPT_Wpedantic,
		       "ISO C forbids qualified function types");
	    إذا (type_quals)
	      type = c_build_qualified_type (type, type_quals, orig_qual_type,
					     orig_qual_اڻسڌو);
	    orig_qual_type = NULL_وڻ;
	    سائيز_varies = خطأ;

	    /* When the pointed-to type involves components of variable size,
	       care must be taken to ensure that the size evaluation code is
	       emitted early enough to dominate all the possible later uses
	       and late enough for the variables on which it depends to have
	       been assigned.

	       This is expected to happen automatically when the pointed-to
	       type has a name/declaration of it's own, but special attention
	       is required if the type is anonymous. */
	    إذا (!TYPE_NAME (type) && c_type_variably_modified_p (type))
	      {
		منطقي bind_p = decl_context == TYPENAME
			      || decl_context == ميدان
			      || decl_context == PARM;
		جوڙيو_decl_اظهار (loc, type, bind_p ? اظهار : عدم, سچ);
	      }

	    type = c_build_اشارو_type (type);

	    /* Process type qualifiers (such as const or volatile)
	       that were given inside the `*'.  */
	    type_quals = declarator->u.اشارو_quals;

	    declarator = declarator->declarator;
	    اكسر;
	  }
	افتراضي:
	  gcc_unreachable ();
	}
    }
  *decl_attrs = chainon (returned_attrs, *decl_attrs);
  *decl_attrs = chainon (decl_id_attrs, *decl_attrs);

  /* Now TYPE has the actual type, apart from any qualifiers in
     TYPE_QUALS.  */

  /* Warn about address space used for things other than static memory or
     pointers.  */
  پتو_space = DECODE_QUAL_ADDR_SPACE (type_quals);
  إذا (!ADDR_SPACE_GENERIC_P (پتو_space))
    {
      إذا (decl_context == عام_2)
	{
	  بدل (storage_class)
	    {
	    حالة csc_auto:
	      error ("%qs combined with %<auto%> qualifier for %qE",
		     c_addr_space_name (پتو_space), name);
	      اكسر;
	    حالة csc_رجسٽر:
	      error ("%qs combined with %<register%> qualifier for %qE",
		     c_addr_space_name (پتو_space), name);
	      اكسر;
	    حالة csc_none:
	      إذا (current_function_scope)
		{
		  error ("%qs specified for auto variable %qE",
			 c_addr_space_name (پتو_space), name);
		  اكسر;
		}
	      اكسر;
	    حالة csc_static:
	    حالة csc_extern:
	    حالة csc_typedef:
	      اكسر;
	    افتراضي:
	      gcc_unreachable ();
	    }
	}
      وإلا إذا (decl_context == PARM && وڻ_ڪوڊ (type) != ARRAY_TYPE)
	{
	  إذا (name)
	    error ("%qs specified for parameter %qE",
		   c_addr_space_name (پتو_space), name);
	  وإلا
	    error ("%qs specified for unnamed parameter",
		   c_addr_space_name (پتو_space));
	}
      وإلا إذا (decl_context == ميدان)
	{
	  إذا (name)
	    error ("%qs specified for structure field %qE",
		   c_addr_space_name (پتو_space), name);
	  وإلا
	    error ("%qs specified for structure field",
		   c_addr_space_name (پتو_space));
	}
    }

  /* Check the type and width of a bit-field.  */
  إذا (bitfield)
    {
      check_bitfield_type_and_ويڪر (loc, &type, ويڪر, name);
      /* C11 makes it implementation-defined (6.7.2.1#5) whether
	 atomic types are permitted for bit-fields; we have no code to
	 make bit-field accesses atomic, so disallow them.  */
      إذا (type_quals & TYPE_QUAL_ATOMIC)
	{
	  إذا (name)
	    error_at (loc, "bit-field %qE has atomic type", name);
	  وإلا
	    error_at (loc, "bit-field has atomic type");
	  type_quals &= ~TYPE_QUAL_ATOMIC;
	}
    }

  /* Reject invalid uses of _Alignas.  */
  إذا (declspecs->alignas_p)
    {
      إذا (storage_class == csc_typedef)
	error_at (loc, "alignment specified for typedef %qE", name);
      وإلا إذا (storage_class == csc_رجسٽر)
	error_at (loc, "alignment specified for %<register%> object %qE",
		  name);
      وإلا إذا (decl_context == PARM)
	{
	  إذا (name)
	    error_at (loc, "alignment specified for parameter %qE", name);
	  وإلا
	    error_at (loc, "alignment specified for unnamed parameter");
	}
      وإلا إذا (bitfield)
	{
	  إذا (name)
	    error_at (loc, "alignment specified for bit-field %qE", name);
	  وإلا
	    error_at (loc, "alignment specified for unnamed bit-field");
	}
      وإلا إذا (وڻ_ڪوڊ (type) == FUNCTION_TYPE)
	error_at (loc, "alignment specified for function %qE", name);
      وإلا إذا (declspecs->align_log != -1 && TYPE_P (type))
	{
	  alignas_align = 1U << declspecs->align_log;
	  إذا (alignas_align < min_align_جو_type (type))
	    {
	      إذا (name)
		error_at (loc, "%<_Alignas%> specifiers cannot reduce "
			  "alignment of %qE", name);
	      وإلا
		error_at (loc, "%<_Alignas%> specifiers cannot reduce "
			  "alignment of unnamed field");
	      alignas_align = 0;
	    }
	}
    }

  /* If this is declaring a typedef name, return a TYPE_DECL.  */

  إذا (storage_class == csc_typedef)
    {
      وڻ decl;
      إذا ((type_quals & TYPE_QUAL_ATOMIC)
	  && وڻ_ڪوڊ (type) == FUNCTION_TYPE)
	{
	  error_at (loc,
		    "%<_Atomic%>-qualified function type");
	  type_quals &= ~TYPE_QUAL_ATOMIC;
	}
      وإلا إذا (pedantic && وڻ_ڪوڊ (type) == FUNCTION_TYPE
	       && type_quals)
	pedwarn (loc, OPT_Wpedantic,
		 "ISO C forbids qualified function types");
      إذا (type_quals)
	type = c_build_qualified_type (type, type_quals, orig_qual_type,
				       orig_qual_اڻسڌو);
      decl = build_decl (declarator->id_loc,
			 TYPE_DECL, declarator->u.id.id, type);
      إذا (declspecs->explicit_signed_p)
	C_TYPEDEF_EXPLICITLY_SIGNED (decl) = 1;
      إذا (declspecs->inline_p)
	pedwarn (loc, 0,"typedef %q+D declared %<inline%>", decl);
      إذا (declspecs->noreturn_p)
	pedwarn (loc, 0,"typedef %q+D declared %<_Noreturn%>", decl);

      إذا (warn_cxx_compat && declarator->u.id.id != NULL_وڻ)
	{
	  بنية c_binding *b = I_ٽيگ_BINDING (declarator->u.id.id);

	  إذا (b != عدم
	      && b->decl != NULL_وڻ
	      && (B_اندريون_CURRENT_SCOPE (b)
		  || (current_scope == file_scope && B_اندريون_EXTERNAL_SCOPE (b)))
	      && TYPE_MAIN_VARIANT (b->decl) != TYPE_MAIN_VARIANT (type))
	    {
	      auto_diagnostic_گروهه d;
	      إذا (warning_at (declarator->id_loc, OPT_Wc___compat,
			      "using %qD as both a typedef and a tag is "
			      "invalid in C++", decl)
		  && b->locus != UNKNOWN_LOCATION)
		inform (b->locus, "originally defined here");
	    }
	}

      أرجع decl;
    }

  /* If this is a type name (such as, in a cast or sizeof),
     compute the type and return it now.  */

  إذا (decl_context == TYPENAME || decl_context == GENERIC_ASSOC)
    {
      /* Note that the grammar rejects storage classes in typenames
	 and fields.  */
      gcc_assert (storage_class == csc_none && !threadp
		  && !declspecs->inline_p && !declspecs->noreturn_p);
      إذا ((type_quals & TYPE_QUAL_ATOMIC)
	  && وڻ_ڪوڊ (type) == FUNCTION_TYPE)
	{
	  error_at (loc,
		    "%<_Atomic%>-qualified function type");
	  type_quals &= ~TYPE_QUAL_ATOMIC;
	}
      وإلا إذا (pedantic && وڻ_ڪوڊ (type) == FUNCTION_TYPE
	       && type_quals)
	pedwarn (loc, OPT_Wpedantic,
		 "ISO C forbids const or volatile function types");
      إذا (type_quals)
	type = c_build_qualified_type (type, type_quals, orig_qual_type,
				       orig_qual_اڻسڌو);
      أرجع type;
    }

  إذا (pedantic && decl_context == ميدان
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

  إذا (VOID_TYPE_P (type) && decl_context != PARM
      && !((decl_context != ميدان && وڻ_ڪوڊ (type) != FUNCTION_TYPE)
	    && (storage_class == csc_extern
		|| (current_scope == file_scope
		    && !(storage_class == csc_static
			 || storage_class == csc_رجسٽر)))))
    {
      error_at (loc, "variable or field %qE declared void", name);
      type = integer_type_ڳنڍ;
    }

  /* Now create the decl, which may be a VAR_DECL, a PARM_DECL
     or a FUNCTION_DECL, depending on DECL_CONTEXT and TYPE.  */

  {
    وڻ decl;

    إذا (decl_context == PARM)
      {
	وڻ promoted_type;
	منطقي array_parameter_p = خطأ;

	/* A parameter declared as an array of T is really a pointer to T.
	   One declared as a function is really a pointer to a function.  */

	إذا (وڻ_ڪوڊ (type) == ARRAY_TYPE)
	  {
	    إذا (!سائيز_error)
	      *decl_attrs = build_arg_spec_attribute (type, array_parm_static,
						      *decl_attrs);

	    /* Transfer const-ness of array into that of type pointed to.  */
	    type = وڻ_TYPE (type);
	    إذا (orig_qual_type != NULL_وڻ)
	      {
		إذا (orig_qual_اڻسڌو == 0)
		  orig_qual_type = وڻ_TYPE (orig_qual_type);
		وإلا
		  orig_qual_اڻسڌو--;
	      }
	    إذا (type_quals)
	      type = c_build_qualified_type (type, type_quals, orig_qual_type,
					     orig_qual_اڻسڌو);

	    /* The pointed-to type may need a decl expr (see above).  */
	    إذا (!TYPE_NAME (type) && c_type_variably_modified_p (type))
	      {
		منطقي bind_p = decl_context == TYPENAME
			      || decl_context == ميدان
			      || decl_context == PARM;
		جوڙيو_decl_اظهار (loc, type, bind_p ? اظهار : عدم, سچ);
	      }

	    type = c_build_اشارو_type (type);
	    type_quals = array_ptr_quals;
	    إذا (type_quals)
	      type = c_build_qualified_type (type, type_quals);

	    /* We don't yet implement attributes in this context.  */
	    إذا (array_ptr_attrs != NULL_وڻ)
	      warning_at (loc, OPT_Wattributes,
			  "attributes in parameter array declarator ignored");

	    سائيز_varies = خطأ;
	    array_parameter_p = سچ;
	  }
	وإلا إذا (وڻ_ڪوڊ (type) == FUNCTION_TYPE)
	  {
	    إذا (type_quals & TYPE_QUAL_ATOMIC)
	      {
		error_at (loc,
			  "%<_Atomic%>-qualified function type");
		type_quals &= ~TYPE_QUAL_ATOMIC;
	      }
	    وإلا إذا (type_quals)
	      pedwarn (loc, OPT_Wpedantic,
		       "ISO C forbids qualified function types");
	    إذا (type_quals)
	      type = c_build_qualified_type (type, type_quals);
	    type = c_build_اشارو_type (type);
	    type_quals = TYPE_UNQUALIFIED;
	  }
	وإلا إذا (type_quals)
	  type = c_build_qualified_type (type, type_quals);

	decl = build_decl (declarator->id_loc,
			   PARM_DECL, declarator->u.id.id, type);
	إذا (سائيز_varies)
	  C_DECL_VARIABLE_سائيز (decl) = 1;
	C_ARRAY_PARAMETER (decl) = array_parameter_p;

	/* Compute the type actually passed in the parmlist,
	   for the case where there is no prototype.
	   (For example, shorts and chars are passed as ints.)
	   When there is a prototype, this is overridden later.  */

	إذا (type == error_mark_ڳنڍ)
	  promoted_type = type;
	وإلا
	  promoted_type = c_type_promotes_منزل (type);

	DECL_ARG_TYPE (decl) = promoted_type;
	إذا (declspecs->inline_p)
	  pedwarn (loc, 0, "parameter %q+D declared %<inline%>", decl);
	إذا (declspecs->noreturn_p)
	  pedwarn (loc, 0, "parameter %q+D declared %<_Noreturn%>", decl);
      }
    وإلا إذا (decl_context == ميدان)
      {
	/* Note that the grammar rejects storage classes in typenames
	   and fields.  */
	gcc_assert (storage_class == csc_none && !threadp
		    && !declspecs->inline_p && !declspecs->noreturn_p);

	/* Structure field.  It may not be a function.  */

	إذا (وڻ_ڪوڊ (type) == FUNCTION_TYPE)
	  {
	    error_at (loc, "field %qE declared as a function", name);
	    type = c_build_اشارو_type (type);
	  }
	وإلا إذا (وڻ_ڪوڊ (type) != ERROR_MARK
		 && !COMPLETE_OR_UNBOUND_ARRAY_TYPE_P (type))
	  {
	    إذا (name)
	      error_at (loc, "field %qE has incomplete type", name);
	    وإلا
	      error_at (loc, "unnamed field has incomplete type");
	    type = error_mark_ڳنڍ;
	  }
	وإلا إذا (وڻ_ڪوڊ (type) == ARRAY_TYPE
		 && TYPE_DOMAIN (type) == NULL_وڻ)
	  {
	    /* We have a flexible array member through a typedef.
	       Set suitable range.  Whether this is a correct position
	       for a flexible array member will be determined elsewhere.  */
	    إذا (!اندريون_system_سرو_at (داخلا_location))
	      pedwarn_c90 (loc, OPT_Wpedantic, "ISO C90 does not "
			   "support flexible array members");
	    type = build_distinct_type_copy (TYPE_MAIN_VARIANT (type));
	    TYPE_DOMAIN (type) = build_اشاريو_type (NULL_وڻ);
	    إذا (orig_qual_اڻسڌو == 0)
	      orig_qual_type = NULL_وڻ;
	  }
	إذا (type != error_mark_ڳنڍ
	    && !verify_type_context (loc, TCTX_ميدان, type))
	  type = error_mark_ڳنڍ;

	type = c_build_qualified_type (type, type_quals, orig_qual_type,
				       orig_qual_اڻسڌو);
	decl = build_decl (declarator->id_loc,
			   ميدان_DECL, declarator->u.id.id, type);
	DECL_NONADDRESSABLE_P (decl) = bitfield;
	إذا (bitfield && !declarator->u.id.id)
	  DECL_PADDING_P (decl) = 1;

	إذا (سائيز_varies)
	  C_DECL_VARIABLE_سائيز (decl) = 1;
      }
    وإلا إذا (وڻ_ڪوڊ (type) == FUNCTION_TYPE)
      {
	إذا (storage_class == csc_رجسٽر || threadp || constexprp)
	  {
	    error_at (loc, "invalid storage class for function %qE", name);
	  }
	وإلا إذا (current_scope != file_scope)
	  {
	    /* Function declaration not at file scope.  Storage
	       classes other than `extern' are not allowed, C99
	       6.7.1p5, and `extern' makes no difference.  However,
	       GCC allows 'auto', perhaps with 'inline', to support
	       nested functions.  */
	    إذا (storage_class == csc_auto)
		pedwarn (loc, OPT_Wpedantic,
			 "invalid storage class for function %qE", name);
	    وإلا إذا (storage_class == csc_static)
	      {
		error_at (loc, "invalid storage class for function %qE", name);
		إذا (funcdef_flag)
		  storage_class = declspecs->storage_class = csc_none;
		وإلا
		  أرجع NULL_وڻ;
	      }
	  }

	decl = build_decl (declarator->id_loc,
			   FUNCTION_DECL, declarator->u.id.id, type);
	decl = build_decl_attribute_variant (decl, decl_attr);

	إذا (type_quals & TYPE_QUAL_ATOMIC)
	  {
	    error_at (loc,
		      "%<_Atomic%>-qualified function type");
	    type_quals &= ~TYPE_QUAL_ATOMIC;
	  }
	وإلا إذا (pedantic && type_quals && !DECL_اندريون_SYSTEM_سرو (decl))
	  pedwarn (loc, OPT_Wpedantic,
		   "ISO C forbids qualified function types");

	/* Every function declaration is an external reference
	   (DECL_EXTERNAL) except for those which are not at file
	   scope and are explicitly declared "auto".  This is
	   forbidden by standard C (C99 6.7.1p5) and is interpreted by
	   GCC to signify a forward declaration of a nested function.  */
	إذا (storage_class == csc_auto && current_scope != file_scope)
	  DECL_EXTERNAL (decl) = 0;
	/* In C99, a function which is declared 'inline' with 'extern'
	   is not an external reference (which is confusing).  It
	   means that the later definition of the function must be output
	   in this file, C99 6.7.4p6.  In GNU C89, a function declared
	   'extern inline' is an external reference.  */
	وإلا إذا (declspecs->inline_p && storage_class != csc_static)
	  DECL_EXTERNAL (decl) = ((storage_class == csc_extern)
				  == flag_gnu89_inline);
	وإلا
	  DECL_EXTERNAL (decl) = !initialized;

	/* Record absence of global scope for `static' or `auto'.  */
	وڻ_عوامي (decl)
	  = !(storage_class == csc_static || storage_class == csc_auto);

	/* For a function definition, record the argument information
	   block where store_parm_decls will look for it.  */
	إذا (funcdef_flag)
	  current_function_arg_info = arg_info;

	إذا (declspecs->default_int_p)
	  C_FUNCTION_IMPLICIT_INT (decl) = 1;

	/* Record presence of `inline' and `_Noreturn', if it is
	   reasonable.  */
	إذا (flag_hosted && MAIN_NAME_P (declarator->u.id.id))
	  {
	    إذا (declspecs->inline_p)
	      pedwarn (loc, 0, "cannot inline function %<main%>");
	    إذا (declspecs->noreturn_p)
	      pedwarn (loc, 0, "%<main%> declared %<_Noreturn%>");
	  }
	وإلا
	  {
	    إذا (declspecs->inline_p)
	      /* Record that the function is declared `inline'.  */
	      DECL_DECLARED_INLINE_P (decl) = 1;
	    إذا (declspecs->noreturn_p)
	      {
		إذا (flag_isoc99)
		  pedwarn_c99 (loc, OPT_Wpedantic,
			       "ISO C99 does not support %<_Noreturn%>");
		وإلا
		  pedwarn_c99 (loc, OPT_Wpedantic,
			       "ISO C90 does not support %<_Noreturn%>");
		وڻ_THIS_VOLATILE (decl) = 1;
	      }
	  }

	/* C99 6.2.2p7: It is invalid (compile-time undefined
	   behavior) to create an 'extern' declaration for a
	   function if there is a global declaration that is
	   'static' and the global declaration is not visible.
	   (If the static declaration _is_ currently visible,
	   the 'extern' declaration is taken to refer to that decl.) */
	إذا (!initialized
	    && وڻ_عوامي (decl)
	    && current_scope != file_scope)
	  {
	    وڻ global_decl  = identifier_global_قدر (declarator->u.id.id);
	    وڻ visible_decl = lookup_name (declarator->u.id.id);

	    إذا (global_decl
		&& global_decl != visible_decl
		&& VAR_OR_FUNCTION_DECL_P (global_decl)
		&& !وڻ_عوامي (global_decl))
	      error_at (loc, "function previously declared %<static%> "
			"redeclared %<extern%>");
	  }
      }
    وإلا
      {
	/* It's a variable.  */
	/* An uninitialized decl with `extern' is a reference.  */
	صحيح extern_ref = !initialized && storage_class == csc_extern;

	إذا (constexprp)
	  {
	    /* The type of a constexpr variable must not be variably
	       modified, volatile, atomic or restrict qualified or
	       have a member with such a qualifier.  const
	       qualification is implicitly added, and, at file scope,
	       has internal linkage.  */
	    إذا (c_type_variably_modified_p (type))
	      error_at (loc, "%<constexpr%> object has variably modified "
			"type");
	    إذا (type_quals
		& (TYPE_QUAL_VOLATILE | TYPE_QUAL_RESTRICT | TYPE_QUAL_ATOMIC))
	      error_at (loc, "invalid qualifiers for %<constexpr%> object");
	    وإلا
	      {
		وڻ type_no_array = strip_array_types (type);
		إذا (رڪارڊ_OR_UNION_TYPE_P (type_no_array)
		    && C_TYPE_FIELDS_NON_CONSTEXPR (type_no_array))
		  error_at (loc, "invalid qualifiers for field of "
			    "%<constexpr%> object");
	      }
	    type_quals |= TYPE_QUAL_CONST;
	    إذا (current_scope == file_scope)
	      storage_class = csc_static;
	  }

	type = c_build_qualified_type (type, type_quals, orig_qual_type,
				       orig_qual_اڻسڌو);

	/* C99 6.2.2p7: It is invalid (compile-time undefined
	   behavior) to create an 'extern' declaration for a
	   variable if there is a global declaration that is
	   'static' and the global declaration is not visible.
	   (If the static declaration _is_ currently visible,
	   the 'extern' declaration is taken to refer to that decl.) */
	إذا (extern_ref && current_scope != file_scope)
	  {
	    وڻ global_decl  = identifier_global_قدر (declarator->u.id.id);
	    وڻ visible_decl = lookup_name (declarator->u.id.id);

	    إذا (global_decl
		&& global_decl != visible_decl
		&& VAR_P (global_decl)
		&& !وڻ_عوامي (global_decl))
	      error_at (loc, "variable previously declared %<static%> "
			"redeclared %<extern%>");
	  }

	decl = build_decl (declarator->id_loc,
			   VAR_DECL, declarator->u.id.id, type);
	إذا (سائيز_varies)
	  C_DECL_VARIABLE_سائيز (decl) = 1;
	إذا (constexprp)
	  C_DECL_DECLARED_CONSTEXPR (decl) = 1;

	إذا (declspecs->inline_p)
	  pedwarn (loc, 0, "variable %q+D declared %<inline%>", decl);
	إذا (declspecs->noreturn_p)
	  pedwarn (loc, 0, "variable %q+D declared %<_Noreturn%>", decl);

	/* At file scope, an initialized extern declaration may follow
	   a static declaration.  In that case, DECL_EXTERNAL will be
	   reset later in start_decl.  */
	DECL_EXTERNAL (decl) = (storage_class == csc_extern);

	/* At file scope, the presence of a `static' or `register' storage
	   class specifier, or the absence of all storage class specifiers
	   makes this declaration a definition (perhaps tentative).  Also,
	   the absence of `static' makes it public.  */
	إذا (current_scope == file_scope)
	  {
	    وڻ_عوامي (decl) = storage_class != csc_static;
	    وڻ_STATIC (decl) = !extern_ref;
	  }
	/* Not at file scope, only `static' makes a static definition.  */
	وإلا
	  {
	    وڻ_STATIC (decl) = (storage_class == csc_static);
	    وڻ_عوامي (decl) = extern_ref;
	  }

	// NB: Set a tentative TLS model to avoid tls_model attribute
	// warnings due to lack of thread storage duration.  It will
	// be updated by c_decl_attributes later.
	إذا (threadp)
	  سيٽ_decl_tls_model (decl, TLS_MODEL_REAL);
      }

    إذا ((storage_class == csc_extern
	 || (storage_class == csc_none
	     && وڻ_ڪوڊ (type) == FUNCTION_TYPE
	     && !funcdef_flag))
	&& c_type_variably_modified_p (type))
      {
	/* C99 6.7.5.2p2 */
	إذا (وڻ_ڪوڊ (type) == FUNCTION_TYPE)
	  error_at (loc, "non-nested function with variably modified type");
	وإلا
	  error_at (loc, "object with variably modified type must have "
	      	    "no linkage");
      }

    /* For nested functions disqualify ones taking VLAs by value
       from inlining since the middle-end cannot deal with this.
       ???  We should arrange for those to be passed by reference
       with emitting the copy on the caller side in the frontend.  */
    إذا (storage_class == csc_none
	&& وڻ_ڪوڊ (type) == FUNCTION_TYPE)
      لكل (وڻ al = TYPE_ARG_TYPES (type); al; al = وڻ_CHAIN (al))
	{
	  وڻ arg = وڻ_قدر (al);
	  إذا (arg != error_mark_ڳنڍ
	      && C_TYPE_VARIABLE_سائيز (arg))
	    {
	      DECL_UNINLINABLE (decl) = 1;
	      اكسر;
	    }
	}

    /* Record `register' declaration for warnings on &
       and in case doing stupid register allocation.  */

    إذا (storage_class == csc_رجسٽر
	&& وڻ_ڪوڊ (type) != FUNCTION_TYPE)
      {
	C_DECL_رجسٽر (decl) = 1;
	DECL_رجسٽر (decl) = 1;
      }

    /* Record constancy and volatility.  */
    c_apply_type_quals_منزل_decl (type_quals, decl);

    /* Apply _Alignas specifiers.  */
    إذا (alignas_align)
      {
	سيٽ_DECL_ALIGN (decl, alignas_align * بٽ_في_UNIT);
	DECL_USER_ALIGN (decl) = 1;
      }

    /* If a type has volatile components, it should be stored in memory.
       Otherwise, the fact that those components are volatile
       will be ignored, and would even crash the compiler.
       Of course, this only makes sense on  VAR,PARM, and RESULT decl's.   */
    إذا (C_TYPE_FIELDS_VOLATILE (وڻ_TYPE (decl))
	&& (VAR_P (decl) ||  وڻ_ڪوڊ (decl) == PARM_DECL
	  || وڻ_ڪوڊ (decl) == نتيجو_DECL))
      {
	/* It is not an error for a structure with volatile fields to
	   be declared register, but reset DECL_REGISTER since it
	   cannot actually go in a register.  */
	صحيح was_reg = C_DECL_رجسٽر (decl);
	C_DECL_رجسٽر (decl) = 0;
	DECL_رجسٽر (decl) = 0;
	c_mark_addressable (decl);
	C_DECL_رجسٽر (decl) = was_reg;
      }

  /* This is the earliest point at which we might know the assembler
     name of a variable.  Thus, if it's known before this, die horribly.  */
    gcc_assert (!HAS_DECL_ASSEMBLER_NAME_P (decl)
		|| !DECL_ASSEMBLER_NAME_سيٽ_P (decl));

    إذا (warn_cxx_compat
	&& VAR_P (decl)
	&& وڻ_عوامي (decl)
	&& وڻ_STATIC (decl)
	&& (رڪارڊ_OR_UNION_TYPE_P (وڻ_TYPE (decl))
	    || وڻ_ڪوڊ (وڻ_TYPE (decl)) == ENUMERAL_TYPE)
	&& TYPE_NAME (وڻ_TYPE (decl)) == NULL_وڻ)
      warning_at (DECL_ذريعو_LOCATION (decl), OPT_Wc___compat,
		  "non-local variable %qD with anonymous type is "
		  "questionable in C++", decl);

    أرجع decl;
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

ساكن وڻ
grokparms (بنية c_arg_info *arg_info, منطقي funcdef_flag)
{
  وڻ arg_types = arg_info->types;

  إذا (funcdef_flag && arg_info->had_vla_unspec)
    {
      /* A function definition isn't function prototype scope C99 6.2.1p4.  */
      /* C99 6.7.5.2p4 */
      error ("%<[*]%> not allowed in other than function prototype scope");
    }

  إذا (arg_types == NULL_وڻ && !funcdef_flag && !flag_isoc23
      && !اندريون_system_سرو_at (داخلا_location))
    warning (OPT_Wstrict_prototypes,
	     "function declaration isn%'t a prototype");

  إذا (arg_types == error_mark_ڳنڍ)
    /* Don't set TYPE_ARG_TYPES in this case.  */
    أرجع NULL_وڻ;

  وإلا إذا (arg_types && وڻ_ڪوڊ (وڻ_قدر (arg_types)) == IDENTIFIER_ڳنڍ)
    {
      إذا (!funcdef_flag)
	{
	  permerror_opt (داخلا_location,
			 OPT_Wdeclaration_missing_parameter_type,
			 "parameter names (without types) in "
			 "function declaration");
	  arg_info->parms = NULL_وڻ;
	}
      وإلا
	arg_info->parms = arg_info->types;

      arg_info->types = NULL_وڻ;
      أرجع NULL_وڻ;
    }
  وإلا
    {
      وڻ parm, type, typelt;
      بنانشان صحيح parmno;

      /* In C23, convert () to (void).  */
      إذا (flag_isoc23
	  && !arg_types
	  && !arg_info->parms
	  && !arg_info->no_named_دليلون_stdarg_p)
	{
	  arg_types = arg_info->types = void_list_ڳنڍ;
	  arg_info->c23_خالي_جايون_parens = 1;
	}

      /* If there is a parameter of incomplete type in a definition,
	 this is an error.  In a declaration this is valid, and a
	 struct or union type may be completed later, before any calls
	 or definition of the function.  In the case where the tag was
	 first declared within the parameter list, a warning has
	 already been given.  If a parameter has void type, then
	 this has already received an error (constraint violation in C2Y,
	 previously implicitly undefined behavior).  */

      لكل (parm = arg_info->parms, typelt = arg_types, parmno = 1;
	   parm;
	   parm = DECL_CHAIN (parm), typelt = وڻ_CHAIN (typelt), parmno++)
	{
	  type = وڻ_قدر (typelt);
	  إذا (type == error_mark_ڳنڍ)
	    استمر;

	  إذا (!COMPLETE_TYPE_P (type))
	    {
	      إذا (funcdef_flag)
		{
		  إذا (DECL_NAME (parm))
		    error_at (داخلا_location,
			      "parameter %u (%q+D) has incomplete type",
			      parmno, parm);
		  وإلا
		    error_at (DECL_ذريعو_LOCATION (parm),
			      "parameter %u has incomplete type",
			      parmno);

		  وڻ_قدر (typelt) = error_mark_ڳنڍ;
		  وڻ_TYPE (parm) = error_mark_ڳنڍ;
		  arg_types = NULL_وڻ;
		}
	    }

	  إذا (DECL_NAME (parm) && وڻ_استعمال_ٿيل (parm))
	    warn_if_shadowing (parm);
	}
      أرجع arg_types;
    }
}

/* Allocate and initialize a c_arg_info structure from the parser's
   obstack.  */

بنية c_arg_info *
build_arg_info (فراغ)
{
  بنية c_arg_info *ret = XOBNEW (&parser_obstack, بنية c_arg_info);
  ret->parms = NULL_وڻ;
  ret->ٽيگ_فهرست = عدم;
  ret->types = NULL_وڻ;
  ret->others = NULL_وڻ;
  ret->pending_sizes = عدم;
  ret->had_vla_unspec = 0;
  ret->no_named_دليلون_stdarg_p = 0;
  ret->c23_خالي_جايون_parens = 0;
  أرجع ret;
}

/* Take apart the current scope and return a c_arg_info structure with
   info on a parameter list just parsed.

   This structure is later fed to 'grokparms' and 'store_parm_decls'.

   ELLIPSIS being true means the argument list ended in '...' so don't
   append a sentinel (void_list_node) to the end of the type-list.

   EXPR is NULL or an expression that needs to be evaluated for the
   side effects of array size expressions in the parameters.  */

بنية c_arg_info *
get_parm_info (منطقي ellipsis, وڻ اظهار)
{
  بنية c_binding *b = current_scope->bindings;
  بنية c_arg_info *arg_info = build_arg_info ();

  وڻ parms = NULL_وڻ;
  vec<c_arg_ٽيگ, va_gc> *ٽيگ_فهرست = عدم;
  وڻ types = NULL_وڻ;
  وڻ others = NULL_وڻ;

  منطقي gave_void_only_once_err = خطأ;

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
  إذا (b->prev == 0			    /* one binding */
      && وڻ_ڪوڊ (b->decl) == PARM_DECL   /* which is a parameter */
      && !DECL_NAME (b->decl)               /* anonymous */
      && VOID_TYPE_P (وڻ_TYPE (b->decl))) /* of void type */
    {
      إذا (TYPE_QUALS (وڻ_TYPE (b->decl)) != TYPE_UNQUALIFIED
	  || C_DECL_رجسٽر (b->decl))
	error_at (b->locus, "%<void%> as only parameter may not be qualified");

      /* There cannot be an ellipsis.  */
      إذا (ellipsis)
	error_at (b->locus, "%<void%> must be the only parameter");

      arg_info->types = void_list_ڳنڍ;
      أرجع arg_info;
    }

  إذا (!ellipsis)
    types = void_list_ڳنڍ;

  /* Break up the bindings list into parms, tags, types, and others;
     apply sanity checks; purge the name-to-decl bindings.  */
  طالما (b)
    {
      وڻ decl = b->decl;
      وڻ type = وڻ_TYPE (decl);
      c_arg_ٽيگ ٽيگ;
      ثابت حرف *keyword;

      بدل (وڻ_ڪوڊ (decl))
	{
	حالة PARM_DECL:
	  إذا (b->id)
	    {
	      gcc_assert (I_نشان_BINDING (b->id) == b);
	      I_نشان_BINDING (b->id) = b->shadowed;
	    }

	  /* Check for forward decls that never got their actual decl.  */
	  إذا (وڻ_ASM_WRITTEN (decl))
	    error_at (b->locus,
		      "parameter %q+D has just a forward declaration", decl);
	  /* Check for (..., void, ...) and named void parameters and issue an
	     error.  */
	  وإلا إذا (VOID_TYPE_P (type))
	    {
	      إذا (!gave_void_only_once_err)
		{
		  error_at (b->locus,
			    "%<void%> must be the only parameter and unnamed");
		  gave_void_only_once_err = سچ;
		}
	    }
	  وإلا
	    {
	      /* Valid parameter, add it to the list.  */
	      DECL_CHAIN (decl) = parms;
	      parms = decl;

	      /* Since there is a prototype, args are passed in their
		 declared types.  The back end may override this later.  */
	      DECL_ARG_TYPE (decl) = type;
	      types = وڻ_cons (0, type, types);
	    }
	  اكسر;

	حالة ENUMERAL_TYPE: keyword = "enum"; اذهب ٽيگ;
	حالة UNION_TYPE:    keyword = "union"; اذهب ٽيگ;
	حالة رڪارڊ_TYPE:   keyword = "struct"; اذهب ٽيگ;
	ٽيگ:
	  /* Types may not have tag-names, in which case the type
	     appears in the bindings list with b->id NULL.  */
	  إذا (b->id)
	    {
	      gcc_assert (I_ٽيگ_BINDING (b->id) == b);
	      I_ٽيگ_BINDING (b->id) = b->shadowed;
	    }

	  /* Warn about any struct, union or enum tags defined in a
	     parameter list.  The scope of such types is limited to
	     the parameter list, which is rarely if ever desirable
	     (it's impossible to call such a function with type-
	     correct arguments).  An anonymous union parm type is
	     meaningful as a GNU extension, so don't warn for that.  */
	  إذا (وڻ_ڪوڊ (decl) != UNION_TYPE || b->id != NULL_وڻ)
	    {
	      إذا (b->id)
		{
		  /* The %s will be one of 'struct', 'union', or 'enum'.  */
		  إذا (!flag_isoc23 || !COMPLETE_TYPE_P (decl))
		    warning_at (b->locus, 0,
				"%<%s %E%> declared inside parameter list"
				" will not be visible outside of this definition or"
				" declaration", keyword, b->id);
		}
	      وإلا
		/* The %s will be one of 'struct', 'union', or 'enum'.  */
		warning_at (b->locus, 0,
			    "anonymous %s declared inside parameter list"
			    " will not be visible outside of this definition or"
			    " declaration", keyword);
	    }

	  ٽيگ.id = b->id;
	  ٽيگ.type = decl;
	  vec_محفوظ_ڌڪو (ٽيگ_فهرست, ٽيگ);
	  اكسر;

	حالة FUNCTION_DECL:
	  /* FUNCTION_DECLs appear when there is an implicit function
	     declaration in the parameter list.  */
	  gcc_assert (b->nested || ڏٺل_error ());
	  اذهب سيٽ_shadowed;

	حالة CONST_DECL:
	حالة TYPE_DECL:
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

	حالة ERROR_MARK:
	سيٽ_shadowed:
	  /* error_mark_node appears here when we have an undeclared
	     variable.  Just throw it away.  */
	  إذا (b->id)
	    {
	      gcc_assert (I_نشان_BINDING (b->id) == b);
	      I_نشان_BINDING (b->id) = b->shadowed;
	    }
	  اكسر;

	  /* Other things that might be encountered.  */
	حالة LABEL_DECL:
	حالة VAR_DECL:
	افتراضي:
	  gcc_unreachable ();
	}

      b = free_binding_and_advance (b);
    }

  arg_info->parms = parms;
  arg_info->ٽيگ_فهرست = ٽيگ_فهرست;
  arg_info->types = types;
  arg_info->others = others;
  arg_info->pending_sizes = اظهار;
  arg_info->no_named_دليلون_stdarg_p = ellipsis && !types;
  أرجع arg_info;
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

بنية c_typespec
parser_xref_ٽيگ (location_t loc, تعداد وڻ_ڪوڊ_2 ڪوڊ, وڻ name,
		 منطقي have_std_attrs, وڻ attrs, منطقي has_enum_type_specifier)
{
  بنية c_typespec ret;
  وڻ ref;
  location_t refloc;

  ret.اظهار = NULL_وڻ;
  ret.اظهار_const_operands = سچ;
  ret.has_enum_type_specifier = has_enum_type_specifier;

  /* If a cross reference is requested, look up the type already
     defined for this tag and return it.  If an enum type specifier is
     present, only a definition in the current scope is relevant.  */

  ref = lookup_ٽيگ (ڪوڊ, name, has_enum_type_specifier, &refloc);

  /* If the visible type is still being defined, see if there is
     an earlier definition (which may be complete).  We do not
     have to loop because nested redefinitions are not allowed.  */
  إذا (flag_isoc23 && ref && C_TYPE_BEING_DEFINED (ref))
    {
      وڻ vis = اڳيون_ٽيگ (ref);
      إذا (vis)
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
  إذا (ref && وڻ_ڪوڊ (ref) == ڪوڊ)
    {
      decl_خاصيتون (&ref, attrs, (صحيح) ATTR_FLAG_TYPE_اندريون_رکو);
      إذا (C_TYPE_DEFINED_اندريون_STRUCT (ref)
	  && loc != UNKNOWN_LOCATION
	  && warn_cxx_compat)
	{
	  auto_diagnostic_گروهه d;
	  بدل (ڪوڊ)
	    {
	    حالة ENUMERAL_TYPE:
	      إذا (warning_at (loc, OPT_Wc___compat,
			      ("enum type defined in struct or union "
			       "is not visible in C++")))
		  inform (refloc, "enum type defined here");
	      اكسر;
	    حالة رڪارڊ_TYPE:
	      إذا (warning_at (loc, OPT_Wc___compat,
			      ("struct defined in struct or union "
			       "is not visible in C++")))
		inform (refloc, "struct defined here");
	      اكسر;
	    حالة UNION_TYPE:
	      إذا (warning_at (loc, OPT_Wc___compat,
			      ("union defined in struct or union "
			       "is not visible in C++")))
		inform (refloc, "union defined here");
	      اكسر;
	    افتراضي:
	      gcc_unreachable();
	    }
	}

      ret.spec = ref;
      أرجع ret;
    }

  /* If no such tag is yet defined, create a forward-reference node
     and record it as the "definition".
     When a real declaration of this type is found,
     the forward-reference will be altered into a real type.  */

  ref = make_ڳنڍ (ڪوڊ);
  إذا (flag_isoc23 || ڪوڊ == ENUMERAL_TYPE)
    سيٽ_TYPE_STRUCTURAL_EQUALITY (ref);
  إذا (ڪوڊ == ENUMERAL_TYPE)
    {
      /* Give the type a default layout like unsigned int
	 to avoid crashing if it does not get defined.  */
      سيٽ_TYPE_گهڻائي (ref, TYPE_گهڻائي (unsigned_type_ڳنڍ));
      سيٽ_TYPE_ALIGN (ref, TYPE_ALIGN (unsigned_type_ڳنڍ));
      TYPE_USER_ALIGN (ref) = 0;
      TYPE_UNSIGNED (ref) = 1;
      TYPE_PRECISION (ref) = TYPE_PRECISION (unsigned_type_ڳنڍ);
      TYPE_MIN_قدر (ref) = TYPE_MIN_قدر (unsigned_type_ڳنڍ);
      TYPE_MAX_قدر (ref) = TYPE_MAX_قدر (unsigned_type_ڳنڍ);
      ENUM_FIXED_UNDERLYING_TYPE_P (ref) = has_enum_type_specifier;
    }

  pushtag (loc, name, ref);
  decl_خاصيتون (&ref, attrs, (صحيح) ATTR_FLAG_TYPE_اندريون_رکو);
  إذا (اندريون_underspecified_init)
    error_at (loc, "%qT declared in underspecified object initializer",
	      ref);

  ret.spec = ref;
  أرجع ret;
}

/* Get the struct, enum or union (CODE says which) with tag NAME.
   Define the tag as a forward-reference if it is not defined.
   Return a tree for the type.  */

وڻ
xref_ٽيگ (تعداد وڻ_ڪوڊ_2 ڪوڊ, وڻ name)
{
  أرجع parser_xref_ٽيگ (داخلا_location, ڪوڊ, name, خطأ, NULL_وڻ,
			  خطأ).spec;
}

/* Make sure that the tag NAME is defined *in the current scope*
   at least as a forward reference.
   LOC is the location of the struct's definition.
   CODE says which kind of tag NAME ought to be.

   This stores the current value of the file static STRUCT_PARSE_INFO
   in *ENCLOSING_STRUCT_PARSE_INFO, and points STRUCT_PARSE_INFO at a
   new c_struct_parse_info structure.  The old value of
   STRUCT_PARSE_INFO is restored in finish_struct.  */

وڻ
شروعات_struct (location_t loc, تعداد وڻ_ڪوڊ_2 ڪوڊ, وڻ name,
	      صنف c_struct_parse_info **enclosing_struct_parse_info)
{
  /* If there is already a tag defined at this scope
     (as a forward reference), just return it.  */

  وڻ ref = NULL_وڻ;
  location_t refloc = UNKNOWN_LOCATION;

  إذا (name != NULL_وڻ)
    ref = lookup_ٽيگ (ڪوڊ, name, سچ, &refloc);

  /* For C23, even if we already have a completed definition,
     we do not use it. We will check for consistency later.
     If we are in a nested redefinition the type is not
     complete. We will then detect this below.  */
  إذا (flag_isoc23 && ref && TYPE_سائيز (ref))
    ref = NULL_وڻ;

  إذا (ref && وڻ_ڪوڊ (ref) == ڪوڊ)
    {
      إذا (TYPE_STUB_DECL (ref))
	refloc = DECL_ذريعو_LOCATION (TYPE_STUB_DECL (ref));

      إذا (TYPE_سائيز (ref))
	{
	  auto_diagnostic_گروهه d;
	  إذا (ڪوڊ == UNION_TYPE)
	    error_at (loc, "redefinition of %<union %E%>", name);
	  وإلا
	    error_at (loc, "redefinition of %<struct %E%>", name);
	  إذا (refloc != UNKNOWN_LOCATION)
	    inform (refloc, "originally defined here");
	  /* Don't create structures using a name already in use.  */
	  ref = NULL_وڻ;
	}
      وإلا إذا (C_TYPE_BEING_DEFINED (ref))
	{
	  إذا (ڪوڊ == UNION_TYPE)
	    error_at (loc, "nested redefinition of %<union %E%>", name);
	  وإلا
	    error_at (loc, "nested redefinition of %<struct %E%>", name);
	  /* Don't bother to report "originally defined here" for a
	     nested redefinition; the original definition should be
	     obvious.  */
	  /* Don't create structures that contain themselves.  */
	  ref = NULL_وڻ;
	}
    }

  /* Otherwise create a forward-reference just so the tag is in scope.  */

  إذا (ref == NULL_وڻ || وڻ_ڪوڊ (ref) != ڪوڊ)
    {
      ref = make_ڳنڍ (ڪوڊ);
      إذا (flag_isoc23)
	سيٽ_TYPE_STRUCTURAL_EQUALITY (ref);
      pushtag (loc, name, ref);
    }

  C_TYPE_BEING_DEFINED (ref) = 1;
  لكل (وڻ v = TYPE_MAIN_VARIANT (ref); v; v = TYPE_ايندڙ_VARIANT (v))
    TYPE_PACKED (v) = flag_pack_struct;

  *enclosing_struct_parse_info = struct_parse_info;
  struct_parse_info = جديد c_struct_parse_info ();
  struct_parse_info->refloc = refloc;

  /* FIXME: This will issue a warning for a use of a type defined
     within a statement expr used within sizeof, et. al.  This is not
     terribly serious as C++ doesn't permit statement exprs within
     sizeof anyhow.  */
  إذا (warn_cxx_compat
      && (اندريون_sizeof || اندريون_typeof || اندريون_alignof || اندريون_countof))
    warning_at (loc, OPT_Wc___compat,
		"defining type in %qs expression is invalid in C++",
		(اندريون_sizeof ? "sizeof"
		 : اندريون_typeof ? "typeof"
		 : اندريون_alignof ? "alignof"
		 : "_Countof"));

  إذا (اندريون_underspecified_init)
    error_at (loc, "%qT defined in underspecified object initializer", ref);

  أرجع ref;
}

/* Process the specs, declarator and width (NULL if omitted)
   of a structure component, returning a FIELD_DECL node.
   WIDTH is non-NULL for bit-fields only, and is an INTEGER_CST node.
   DECL_ATTRS is as for grokdeclarator.

   LOC is the location of the structure component.

   This is done during the parsing of the struct declaration.
   The FIELD_DECL nodes are chained together and the lot of them
   are ultimately passed to `build_struct' to make the RECORD_TYPE node.  */

وڻ
grokfield (location_t loc,
	   بنية c_declarator *declarator, بنية c_declspecs *declspecs,
	   وڻ ويڪر, وڻ *decl_attrs, وڻ *اظهار)
{
  وڻ قدر;

  إذا (declarator->قسم == cdk_id && declarator->u.id.id == NULL_وڻ
      && ويڪر == NULL_وڻ)
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

      وڻ type = declspecs->type;
      منطقي ok = خطأ;

      إذا (رڪارڊ_OR_UNION_TYPE_P (type)
	  && (flag_ms_extensions
	      || flag_plan9_extensions
	      || !declspecs->typedef_p))
	{
	  إذا (flag_ms_extensions || flag_plan9_extensions)
	    ok = سچ;
	  وإلا إذا (TYPE_NAME (type) == عدم)
	    ok = سچ;
	  وإلا
	    ok = خطأ;
	}
      إذا (!ok)
	{
	  pedwarn (loc, 0, "declaration does not declare anything");
	  أرجع NULL_وڻ;
	}
      إذا (flag_isoc99)
	pedwarn_c99 (loc, OPT_Wpedantic,
		     "ISO C99 doesn%'t support unnamed structs/unions");
      وإلا
	pedwarn_c99 (loc, OPT_Wpedantic,
		     "ISO C90 doesn%'t support unnamed structs/unions");
    }

  قدر = grokdeclarator (declarator, declspecs, ميدان, خطأ,
			  ويڪر ? &ويڪر : عدم, decl_attrs, اظهار, عدم,
			  DEPRECATED_عام);

  /* When this field has name, its type is a top level type, we should
     call verify_counted_by_for_top_anonymous_type.  */
  إذا (DECL_NAME (قدر) != NULL_وڻ
      && declspecs->typespec_قسم == ctsk_tagdef)
    verify_counted_by_for_چوٽي_anonymous_type (declspecs->type);

  پڄاڻي_decl (قدر, loc, NULL_وڻ, NULL_وڻ, NULL_وڻ);
  DECL_INITIAL (قدر) = ويڪر;
  إذا (ويڪر)
    سيٽ_DECL_C_ٻٽو_انگ_ميدان (قدر);

  إذا (warn_cxx_compat && DECL_NAME (قدر) != NULL_وڻ)
    {
      /* If we currently have a binding for this field, set the
	 in_struct field in the binding, so that we warn about lookups
	 which find it.  */
      بنية c_binding *b = I_نشان_BINDING (DECL_NAME (قدر));
      إذا (b != عدم)
	{
	  /* If the in_struct field is not yet set, push it on a list
	     to be cleared when this struct is finished.  */
	  إذا (!b->اندريون_struct)
	    {
	      struct_parse_info->fields.محفوظ_ڌڪو (b);
	      b->اندريون_struct = 1;
	    }
	}
    }

  أرجع قدر;
}

/* Subroutine of detect_field_duplicates: return whether X and Y,
   which are both fields in the same struct, have duplicate field
   names.  */

ساكن منطقي
is_duplicate_ميدان (وڻ x, وڻ y)
{
  إذا (DECL_NAME (x) != NULL_وڻ && DECL_NAME (x) == DECL_NAME (y))
    أرجع سچ;

  /* When using -fplan9-extensions, an anonymous field whose name is a
     typedef can duplicate a field name.  */
  إذا (flag_plan9_extensions
      && (DECL_NAME (x) == NULL_وڻ || DECL_NAME (y) == NULL_وڻ))
    {
      وڻ xt, xn, yt, yn;

      xt = وڻ_TYPE (x);
      إذا (DECL_NAME (x) != NULL_وڻ)
	xn = DECL_NAME (x);
      وإلا إذا (رڪارڊ_OR_UNION_TYPE_P (xt)
	       && TYPE_NAME (xt) != NULL_وڻ
	       && وڻ_ڪوڊ (TYPE_NAME (xt)) == TYPE_DECL)
	xn = DECL_NAME (TYPE_NAME (xt));
      وإلا
	xn = NULL_وڻ;

      yt = وڻ_TYPE (y);
      إذا (DECL_NAME (y) != NULL_وڻ)
	yn = DECL_NAME (y);
      وإلا إذا (رڪارڊ_OR_UNION_TYPE_P (yt)
	       && TYPE_NAME (yt) != NULL_وڻ
	       && وڻ_ڪوڊ (TYPE_NAME (yt)) == TYPE_DECL)
	yn = DECL_NAME (TYPE_NAME (yt));
      وإلا
	yn = NULL_وڻ;

      إذا (xn != NULL_وڻ && xn == yn)
	أرجع سچ;
    }

  أرجع خطأ;
}

/* Subroutine of detect_field_duplicates: add the fields of FIELDLIST
   to HTAB, giving errors for any duplicates.  */

ساكن فراغ
detect_ميدان_duplicates_hash (وڻ fieldlist,
			      hash_جدول<nofree_ptr_hash <وڻ_ڳنڍ> > *htab)
{
  وڻ x, y;
  وڻ_ڳنڍ **جڳهه;

  لكل (x = fieldlist; x ; x = DECL_CHAIN (x))
    إذا ((y = DECL_NAME (x)) != NULL_وڻ)
      {
	جڳهه = htab->ڳوليو_جڳهه (y, وجهو);
	إذا (*جڳهه)
	  {
	    error ("duplicate member %q+D", x);
	    DECL_NAME (x) = NULL_وڻ;
	  }
	*جڳهه = y;
      }
    وإلا إذا (رڪارڊ_OR_UNION_TYPE_P (وڻ_TYPE (x)))
      {
	detect_ميدان_duplicates_hash (TYPE_FIELDS (وڻ_TYPE (x)), htab);

	/* When using -fplan9-extensions, an anonymous field whose
	   name is a typedef can duplicate a field name.  */
	إذا (flag_plan9_extensions
	    && TYPE_NAME (وڻ_TYPE (x)) != NULL_وڻ
	    && وڻ_ڪوڊ (TYPE_NAME (وڻ_TYPE (x))) == TYPE_DECL)
	  {
	    وڻ xn = DECL_NAME (TYPE_NAME (وڻ_TYPE (x)));
	    جڳهه = htab->ڳوليو_جڳهه (xn, وجهو);
	    إذا (*جڳهه)
	      error ("duplicate member %q+D", TYPE_NAME (وڻ_TYPE (x)));
	    *جڳهه = xn;
	  }
      }
}

/* Generate an error for any duplicate field names in FIELDLIST.  Munge
   the list such that this does not present a problem later.  */

ساكن فراغ
detect_ميدان_duplicates (وڻ fieldlist)
{
  وڻ x, y;
  صحيح timeout = 10;

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
  إذا (c_dialect_objc ())
    إذا (objc_detect_ميدان_duplicates (خطأ))
      أرجع;

  /* First, see if there are more than "a few" fields.
     This is trivially true if there are zero or one fields.  */
  إذا (!fieldlist || !DECL_CHAIN (fieldlist))
    أرجع;
  x = fieldlist;
  افعل {
    timeout--;
    إذا (DECL_NAME (x) == NULL_وڻ
	&& رڪارڊ_OR_UNION_TYPE_P (وڻ_TYPE (x)))
      timeout = 0;
    x = DECL_CHAIN (x);
  } طالما (timeout > 0 && x);

  /* If there were "few" fields and no anonymous structures or unions,
     avoid the overhead of allocating a hash table.  Instead just do
     the nested traversal thing.  */
  إذا (timeout > 0)
    {
      لكل (x = DECL_CHAIN (fieldlist); x; x = DECL_CHAIN (x))
	/* When using -fplan9-extensions, we can have duplicates
	   between typedef names and fields.  */
	إذا (DECL_NAME (x)
	    || (flag_plan9_extensions
		&& DECL_NAME (x) == NULL_وڻ
		&& رڪارڊ_OR_UNION_TYPE_P (وڻ_TYPE (x))
		&& TYPE_NAME (وڻ_TYPE (x)) != NULL_وڻ
		&& وڻ_ڪوڊ (TYPE_NAME (وڻ_TYPE (x))) == TYPE_DECL))
	  {
	    لكل (y = fieldlist; y != x; y = وڻ_CHAIN (y))
	      إذا (is_duplicate_ميدان (y, x))
		{
		  error ("duplicate member %q+D", x);
		  DECL_NAME (x) = NULL_وڻ;
		}
	  }
    }
  وإلا
    {
      hash_جدول<nofree_ptr_hash <وڻ_ڳنڍ> > htab (37);
      detect_ميدان_duplicates_hash (fieldlist, &htab);
    }
}

/* Finish up struct info used by -Wc++-compat.  */

ساكن فراغ
warn_cxx_compat_پڄاڻي_struct (وڻ fieldlist, تعداد وڻ_ڪوڊ_2 ڪوڊ,
			       location_t رڪارڊ_loc)
{
  بنانشان صحيح ix;
  وڻ x;
  بنية c_binding *b;

  إذا (fieldlist == NULL_وڻ)
    {
      إذا (ڪوڊ == رڪارڊ_TYPE)
	warning_at (رڪارڊ_loc, OPT_Wc___compat,
		    "empty struct has size 0 in C, size 1 in C++");
      وإلا
	warning_at (رڪارڊ_loc, OPT_Wc___compat,
		    "empty union has size 0 in C, size 1 in C++");
    }

  /* Set the C_TYPE_DEFINED_IN_STRUCT flag for each type defined in
     the current struct.  We do this now at the end of the struct
     because the flag is used to issue visibility warnings, and we
     only want to issue those warnings if the type is referenced
     outside of the struct declaration.  */
  FOR_EACH_VEC_ELT (struct_parse_info->struct_types, ix, x)
    C_TYPE_DEFINED_اندريون_STRUCT (x) = 1;

  /* The TYPEDEFS_SEEN field of STRUCT_PARSE_INFO is a list of
     typedefs used when declaring fields in this struct.  If the name
     of any of the fields is also a typedef name then the struct would
     not parse in C++, because the C++ lookup rules say that the
     typedef name would be looked up in the context of the struct, and
     would thus be the field rather than the typedef.  */
  إذا (!struct_parse_info->typedefs_ڏٺل.is_خالي_جايون ()
      && fieldlist != NULL_وڻ)
    {
      /* Use a hash_set<tree> using the name of the typedef.  We can use
	 a hash_set<tree> because identifiers are interned.  */
      hash_سيٽ<وڻ> tset;

      FOR_EACH_VEC_ELT (struct_parse_info->typedefs_ڏٺل, ix, x)
	tset.جوڙيو (DECL_NAME (x));

      لكل (x = fieldlist; x != NULL_وڻ; x = DECL_CHAIN (x))
	{
	  إذا (DECL_NAME (x) != NULL_وڻ
	      && tset.شامل_آهي (DECL_NAME (x)))
	    {
	      warning_at (DECL_ذريعو_LOCATION (x), OPT_Wc___compat,
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
    b->اندريون_struct = 0;
}

/* Function to help qsort sort FIELD_DECLs by name order.  */

ساكن صحيح
ميدان_decl_cmp (ثابت فراغ *x_p, ثابت فراغ *y_p)
{
  ثابت وڻ *ثابت x = (ثابت وڻ *) x_p;
  ثابت وڻ *ثابت y = (ثابت وڻ *) y_p;

  إذا (DECL_NAME (*x) == DECL_NAME (*y))
    /* A nontype is "greater" than a type.  */
    أرجع (وڻ_ڪوڊ (*y) == TYPE_DECL) - (وڻ_ڪوڊ (*x) == TYPE_DECL);
  إذا (DECL_NAME (*x) == NULL_وڻ)
    أرجع -1;
  إذا (DECL_NAME (*y) == NULL_وڻ)
    أرجع 1;
  إذا (DECL_NAME (*x) < DECL_NAME (*y))
    أرجع -1;
  أرجع 1;
}

/* If this structure or union completes the type of any previous
   variable declaration, lay it out and output its rtl.  */
ساكن فراغ
پڄاڻي_incomplete_vars (وڻ incomplete_vars, منطقي toplevel)
{
  لكل (وڻ x = incomplete_vars; x; x = وڻ_CHAIN (x))
    {
      وڻ decl = وڻ_قدر (x);
      إذا (وڻ_ڪوڊ (وڻ_TYPE (decl)) == ARRAY_TYPE)
	layout_array_type (وڻ_TYPE (decl));
      إذا (وڻ_ڪوڊ (decl) != TYPE_DECL)
	{
	  relayout_decl (decl);
	  إذا (c_dialect_objc ())
	    objc_check_decl (decl);
	  rest_جو_decl_compilation (decl, toplevel, 0);
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

ساكن منطقي
is_flexible_array_member_p (منطقي is_آخري_ميدان,
			    وڻ x)
{
  /* If not the last field, return false.  */
  إذا (!is_آخري_ميدان)
    أرجع خطأ;

  /* If not an array field, return false.  */
  إذا (وڻ_ڪوڊ (وڻ_TYPE (x)) != ARRAY_TYPE)
    أرجع خطأ;

  منطقي is_zero_ڊيگهائي_array = zero_ڊيگهائي_array_type_p (وڻ_TYPE (x));
  منطقي is_one_element_array = one_element_array_type_p (وڻ_TYPE (x));
  منطقي is_flexible_array = flexible_array_member_type_p (وڻ_TYPE (x));

  بنانشان صحيح strict_flex_array_level = c_strict_flex_array_level_جو (x);

  بدل (strict_flex_array_level)
    {
      حالة 0:
	/* Default, all trailing arrays are flexible array members.  */
	أرجع سچ;
      حالة 1:
	/* Level 1: all "[1]", "[0]", and "[]" are flexible array members.  */
	إذا (is_one_element_array)
	  أرجع سچ;
	/* FALLTHROUGH.  */
      حالة 2:
	/* Level 2: all "[0]", and "[]" are flexible array members.  */
	إذا (is_zero_ڊيگهائي_array)
	  أرجع سچ;
	/* FALLTHROUGH.  */
      حالة 3:
	/* Level 3: Only "[]" are flexible array members.  */
	إذا (is_flexible_array)
	  أرجع سچ;
	اكسر;
      افتراضي:
	gcc_unreachable ();
    }
  أرجع خطأ;
}

/* Recompute TYPE_CANONICAL for variants of the type including qualified
   versions of the type and related pointer types after an aggregate type
   has been finalized.
   Will not update array types, pointers to array types, function
   types and other derived types created while the type was still
   incomplete, those will remain TYPE_STRUCTURAL_EQUALITY_P.  */

ساكن فراغ
c_update_type_canonical (وڻ t)
{
  gcc_checking_assert (TYPE_MAIN_VARIANT (t) == t && !TYPE_QUALS (t));
  لكل (وڻ x = t, l = NULL_وڻ; x; l = x, x = TYPE_ايندڙ_VARIANT (x))
    {
      إذا (x != t && TYPE_STRUCTURAL_EQUALITY_P (x))
	{
	  إذا (!TYPE_QUALS (x))
	    TYPE_CANONICAL (x) = TYPE_CANONICAL (t);
	  وإلا
	    {
	      وڻ
		c = c_build_qualified_type (TYPE_CANONICAL (t), TYPE_QUALS (x));
	      إذا (TYPE_STRUCTURAL_EQUALITY_P (c))
		{
		  gcc_checking_assert (TYPE_CANONICAL (t) == t);
		  إذا (c == x)
		    TYPE_CANONICAL (x) = x;
		  وإلا
		    {
		      /* build_qualified_type for this function unhelpfully
			 moved c from some later spot in TYPE_MAIN_VARIANT (t)
			 chain to right after t (or created it there).  Move
			 it right before x and process c and then x.  */
		      gcc_checking_assert (TYPE_ايندڙ_VARIANT (t) == c);
		      إذا (l != t)
			{
			  TYPE_ايندڙ_VARIANT (t) = TYPE_ايندڙ_VARIANT (c);
			  TYPE_ايندڙ_VARIANT (l) = c;
			  TYPE_ايندڙ_VARIANT (c) = x;
			}
		      TYPE_CANONICAL (c) = c;
		      x = c;
		    }
		}
	      وإلا
		TYPE_CANONICAL (x) = TYPE_CANONICAL (c);
	    }
	}
      وإلا إذا (x != t)
	استمر;
      لكل (وڻ p = TYPE_اشارو_منزل (x); p; p = TYPE_ايندڙ_PTR_منزل (p))
	{
	  إذا (!TYPE_STRUCTURAL_EQUALITY_P (p))
	    استمر;
	  إذا (TYPE_CANONICAL (x) != x || TYPE_REF_CAN_ALIAS_ALL (p))
	    TYPE_CANONICAL (p)
	      = c_build_اشارو_type_for_گهڻائي (TYPE_CANONICAL (x), TYPE_گهڻائي (p),
					       خطأ);
	  وإلا
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

ساكن فراغ
c_update_variably_modified (وڻ t)
{
  لكل (وڻ x = t; x; x = TYPE_ايندڙ_VARIANT (x))
    {
      C_TYPE_VARIABLY_MODIFIED (x) = 1;
      لكل (وڻ p = TYPE_اشارو_منزل (x); p; p = TYPE_ايندڙ_PTR_منزل (p))
	c_update_variably_modified (p);
    }
}


/* Verify the argument of the counted_by attribute of each field of
   the containing structure, OUTMOST_STRUCT_TYPE, including its inner
   anonymous struct/union, Report error and remove the corresponding
   attribute when it's not.  */

ساكن فراغ
verify_counted_by_attribute (وڻ outmost_struct_type,
			     وڻ cur_struct_type)
{
  لكل (وڻ ميدان_2 = TYPE_FIELDS (cur_struct_type); ميدان_2;
       ميدان_2 = وڻ_CHAIN (ميدان_2))
    {
      إذا (flexible_array_member_type_p (وڻ_TYPE (ميدان_2))
	   || وڻ_ڪوڊ (وڻ_TYPE (ميدان_2)) == اشارو_TYPE)
	{
	  وڻ attr_counted_by = lookup_attribute ("counted_by",
						   DECL_خاصيتون (ميدان_2));

	  إذا (!attr_counted_by)
	    استمر;

	  /* If there is an counted_by attribute attached to the field,
	     verify it.  */

	  وڻ fieldname = وڻ_قدر (وڻ_قدر (attr_counted_by));

	  /* Verify the argument of the attribute is a valid field of the
	     containing structure.  */

	  وڻ counted_by_ميدان = lookup_ميدان (outmost_struct_type,
						fieldname);

	  /* Error when the field is not found in the containing structure
	     and remove the corresponding counted_by attribute from the
	     field_decl.  */
	  إذا (!counted_by_ميدان)
	    {
	      error_at (DECL_ذريعو_LOCATION (ميدان_2),
		    "argument %qE to the %<counted_by%> attribute"
		    " is not a field declaration in the same structure"
		    " as %qD", fieldname, ميدان_2);
	      DECL_خاصيتون (ميدان_2)
		= remove_attribute ("counted_by", DECL_خاصيتون (ميدان_2));
	    }
	  وإلا
	  /* Error when the field is not with an integer type.  */
	    {
	      طالما (وڻ_CHAIN (counted_by_ميدان))
		counted_by_ميدان = وڻ_CHAIN (counted_by_ميدان);
	      وڻ real_ميدان = وڻ_قدر (counted_by_ميدان);

	      إذا (!INTEGRAL_TYPE_P (وڻ_TYPE (real_ميدان)))
		{
		  error_at (DECL_ذريعو_LOCATION (ميدان_2),
			"argument %qE to the %<counted_by%> attribute"
			" is not a field declaration with an integer type",
			fieldname);
		  DECL_خاصيتون (ميدان_2)
		    = remove_attribute ("counted_by",
				    DECL_خاصيتون (ميدان_2));
		}
	    }
	}
      وإلا إذا (رڪارڊ_OR_UNION_TYPE_P (وڻ_TYPE (ميدان_2))
	       && (DECL_NAME (ميدان_2) == NULL_وڻ))
	verify_counted_by_attribute (outmost_struct_type, وڻ_TYPE (ميدان_2));
    }
}

/* Caller should make sure the TYPE is a top-level type (i.e. not being
   nested in other structure/uniona). For such type, verify its counted_by
   if it is an anonymous structure/union.  */

فراغ
verify_counted_by_for_چوٽي_anonymous_type (وڻ type)
{
  إذا (!رڪارڊ_OR_UNION_TYPE_P (type))
    أرجع;

  إذا (C_TYPE_FIELDS_HAS_COUNTED_BY (type)
      && c_type_ٽيگ (type) == NULL_وڻ)
    verify_counted_by_attribute (type, type);
}

/* TYPE is a struct or union that we're applying may_alias to after the body is
   parsed.  Fixup any POINTER_TO types.  */

ساكن فراغ
c_fixup_may_alias (وڻ type)
{
  لكل (وڻ t = TYPE_اشارو_منزل (type); t; t = TYPE_ايندڙ_PTR_منزل (t))
    لكل (وڻ v = TYPE_MAIN_VARIANT (t); v; v = TYPE_ايندڙ_VARIANT (v))
      TYPE_REF_CAN_ALIAS_ALL (v) = سچ;
}

/* Fill in the fields of a RECORD_TYPE or UNION_TYPE node, T.
   LOC is the location of the RECORD_TYPE or UNION_TYPE's definition.
   FIELDLIST is a chain of FIELD_DECL nodes for the fields.
   ATTRIBUTES are attributes to be applied to the structure.

   ENCLOSING_STRUCT_PARSE_INFO is the value of STRUCT_PARSE_INFO when
   the struct was started.  */

وڻ
پڄاڻي_struct (location_t loc, وڻ t, وڻ fieldlist, وڻ خاصيتون,
	       صنف c_struct_parse_info *enclosing_struct_parse_info,
	       وڻ *اظهار)
{
  وڻ x;
  منطقي toplevel = file_scope == current_scope;

  /* If this type was previously laid out as a forward reference,
     make sure we lay it out again.  */

  TYPE_سائيز (t) = NULL_وڻ;

  decl_خاصيتون (&t, خاصيتون, (صحيح) ATTR_FLAG_TYPE_اندريون_رکو);

  إذا (pedantic)
    {
      لكل (x = fieldlist; x; x = DECL_CHAIN (x))
	{
	  إذا (DECL_NAME (x) != NULL_وڻ)
	    اكسر;
	  إذا (flag_isoc11 && رڪارڊ_OR_UNION_TYPE_P (وڻ_TYPE (x)))
	    اكسر;
	}

      إذا (x == NULL_وڻ)
	{
	  إذا (وڻ_ڪوڊ (t) == UNION_TYPE)
	    {
	      إذا (fieldlist)
		pedwarn (loc, OPT_Wpedantic, "union has no named members");
	      وإلا
		pedwarn (loc, OPT_Wpedantic, "union has no members");
	    }
	  وإلا
	    {
	      إذا (fieldlist)
		pedwarn (loc, OPT_Wpedantic, "struct has no named members");
	      وإلا
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

  منطقي saw_named_ميدان = خطأ;
  لكل (x = fieldlist; x; x = DECL_CHAIN (x))
    {
      /* Whether this field is the last field of the structure or union.
	 for UNION, any field is the last field of it.  */
      منطقي is_آخري_ميدان = (DECL_CHAIN (x) == NULL_وڻ)
			    || (وڻ_ڪوڊ (t) == UNION_TYPE);

      إذا (وڻ_TYPE (x) == error_mark_ڳنڍ)
	استمر;

      DECL_CONTEXT (x) = t;

      وڻ t1 = strip_array_types (وڻ_TYPE (x));
      /* If any field is const, the structure type is pseudo-const.  */
      إذا (وڻ_READONLY (x))
	C_TYPE_FIELDS_READONLY (t) = 1;
      وإلا
	{
	  /* A field that is pseudo-const makes the structure likewise.  */
	  إذا (رڪارڊ_OR_UNION_TYPE_P (t1) && C_TYPE_FIELDS_READONLY (t1))
	    C_TYPE_FIELDS_READONLY (t) = 1;
	}

      /* Any field that is volatile means variables of this type must be
	 treated in some ways as volatile.  */
      إذا (وڻ_THIS_VOLATILE (x))
	{
	  C_TYPE_FIELDS_VOLATILE (t) = 1;
	  C_TYPE_FIELDS_NON_CONSTEXPR (t) = 1;
	}

      /* Any field that is volatile, restrict-qualified or atomic
	 means the type cannot be used for a constexpr object.  */
      إذا (TYPE_QUALS (t1)
	  & (TYPE_QUAL_VOLATILE | TYPE_QUAL_RESTRICT | TYPE_QUAL_ATOMIC))
	C_TYPE_FIELDS_NON_CONSTEXPR (t) = 1;
      وإلا إذا (رڪارڊ_OR_UNION_TYPE_P (t1) && C_TYPE_FIELDS_NON_CONSTEXPR (t1))
	    C_TYPE_FIELDS_NON_CONSTEXPR (t) = 1;

      /* Any field of nominal variable size implies structure is too.  */
      إذا (C_DECL_VARIABLE_سائيز (x))
	C_TYPE_VARIABLE_سائيز (t) = 1;

      /* If any field is variably modified, record this fact. */
      إذا (c_type_variably_modified_p (وڻ_TYPE (x)))
	C_TYPE_VARIABLY_MODIFIED (t) = 1;

      إذا (DECL_C_ٻٽو_انگ_ميدان (x))
	{
	  بنانشان HOST_WIDE_INT ويڪر = وڻ_منزل_uhwi (DECL_INITIAL (x));
	  DECL_سائيز (x) = bitsize_int (ويڪر);
	  DECL_ٻٽو_انگ_ميدان (x) = 1;
	}

      إذا (TYPE_PACKED (t)
	  && (DECL_ٻٽو_انگ_ميدان (x)
	      || TYPE_ALIGN (وڻ_TYPE (x)) > بٽ_في_UNIT))
	DECL_PACKED (x) = 1;

      /* Detect flexible array member in an invalid context.  */
      إذا (flexible_array_member_type_p (وڻ_TYPE (x)))
	{
	  إذا (وڻ_ڪوڊ (t) == UNION_TYPE)
	    pedwarn (DECL_ذريعو_LOCATION (x), OPT_Wpedantic,
		     "flexible array member in union is a GCC extension");
	  وإلا إذا (!is_آخري_ميدان)
	    {
	      error_at (DECL_ذريعو_LOCATION (x),
			"flexible array member not at end of struct");
	      وڻ_TYPE (x) = error_mark_ڳنڍ;
	    }
	  وإلا إذا (!saw_named_ميدان)
	    pedwarn (DECL_ذريعو_LOCATION (x), OPT_Wpedantic,
		     "flexible array member in a struct with no named "
		     "members is a GCC extension");
	  إذا (lookup_attribute ("counted_by", DECL_خاصيتون (x)))
	    C_TYPE_FIELDS_HAS_COUNTED_BY (t) = 1;
	}

      إذا (وڻ_ڪوڊ (وڻ_TYPE (x)) == اشارو_TYPE
	  && lookup_attribute ("counted_by", DECL_خاصيتون (x)))
	C_TYPE_FIELDS_HAS_COUNTED_BY (t) = 1;

      /* If the field is an anonymous structure that includes a field
	 with counted_by attribute, this structure should also be marked
	 too.  */
      إذا (رڪارڊ_OR_UNION_TYPE_P (وڻ_TYPE (x))
	  && C_TYPE_FIELDS_HAS_COUNTED_BY (وڻ_TYPE (x))
	  && DECL_NAME (x) == NULL_وڻ
	  && c_type_ٽيگ (وڻ_TYPE (x)) == NULL_وڻ)
	C_TYPE_FIELDS_HAS_COUNTED_BY (t) = 1;

      إذا (pedantic && وڻ_ڪوڊ (t) == رڪارڊ_TYPE
	  && flexible_array_type_p (وڻ_TYPE (x)))
	pedwarn (DECL_ذريعو_LOCATION (x), OPT_Wpedantic,
		 "invalid use of structure with flexible array member");

      /* Set DECL_NOT_FLEXARRAY flag for FIELD_DECL x.  */
      DECL_NOT_FLEXARRAY (x) = !is_flexible_array_member_p (is_آخري_ميدان, x);

      /* Set TYPE_INCLUDES_FLEXARRAY for the context of x, t.
	 when x is an array and is the last field.
	 There is only one last_field for a structure type, but there might
	 be multiple last_fields for a union type, therefore we should ORed
	 the result for multiple last_fields.  */
      إذا (وڻ_ڪوڊ (وڻ_TYPE (x)) == ARRAY_TYPE)
	TYPE_INCLUDES_FLEXARRAY (t)
	  |= is_آخري_ميدان && flexible_array_member_type_p (وڻ_TYPE (x));
      /* Recursively set TYPE_INCLUDES_FLEXARRAY for the context of x, t
	 when x is an union or record and is the last field.  */
      وإلا إذا (رڪارڊ_OR_UNION_TYPE_P (وڻ_TYPE (x)))
	TYPE_INCLUDES_FLEXARRAY (t)
	  |= is_آخري_ميدان && TYPE_INCLUDES_FLEXARRAY (وڻ_TYPE (x));

      إذا (warn_flex_array_member_not_at_پڇاڙي
	  && !is_آخري_ميدان
	  && رڪارڊ_OR_UNION_TYPE_P (وڻ_TYPE (x))
	  && TYPE_INCLUDES_FLEXARRAY (وڻ_TYPE (x)))
	warning_at (DECL_ذريعو_LOCATION (x),
		    OPT_Wflex_array_member_not_at_پڇاڙي,
		    "structure containing a flexible array member"
		    " is not at the end of another structure");

      إذا (DECL_NAME (x)
	  || رڪارڊ_OR_UNION_TYPE_P (وڻ_TYPE (x)))
	saw_named_ميدان = سچ;

      إذا (AGGREGATE_TYPE_P (وڻ_TYPE (x))
	  && TYPE_TYPELESS_STORAGE (وڻ_TYPE (x)))
	TYPE_TYPELESS_STORAGE (t) = سچ;
    }

  detect_ميدان_duplicates (fieldlist);

  /* Now we have the nearly final fieldlist.  Record it,
     then lay out the structure or union (including the fields).  */

  TYPE_FIELDS (t) = fieldlist;

  maybe_apply_pragma_scalar_storage_ترتيب (t);

  layout_type (t);

  إذا (TYPE_سائيز_UNIT (t)
      && وڻ_ڪوڊ (TYPE_سائيز_UNIT (t)) == INTEGER_CST
      && !وڻ_حد_کان_مٿي (TYPE_سائيز_UNIT (t))
      && !valid_constant_سائيز_p (TYPE_سائيز_UNIT (t)))
    error ("type %qT is too large", t);

  /* Give bit-fields their proper types and rewrite the type of array fields
     with scalar component if the enclosing type has reverse storage order.  */
  لكل (وڻ ميدان_2 = fieldlist; ميدان_2; ميدان_2 = DECL_CHAIN (ميدان_2))
    {
      إذا (وڻ_ڪوڊ (ميدان_2) == ميدان_DECL
	  && DECL_INITIAL (ميدان_2)
	  && وڻ_TYPE (ميدان_2) != error_mark_ڳنڍ)
	{
	  بنانشان HOST_WIDE_INT ويڪر
	    = وڻ_منزل_uhwi (DECL_INITIAL (ميدان_2));
	  وڻ type = وڻ_TYPE (ميدان_2);
	  إذا (ويڪٽر_TYPE_P (type))
	    {
	      error_at (DECL_ذريعو_LOCATION (ميدان_2),
			"bit-field %qD has invalid type", ميدان_2);
	      type = وڻ_TYPE (type);
	      وڻ_TYPE (ميدان_2) = type;
	    }
	  إذا (ويڪر != TYPE_PRECISION (type))
	    {
	      إذا (BITINT_TYPE_P (type)
		  && ويڪر >= ((TYPE_UNSIGNED (type) || flag_isoc2y) ? 1 : 2))
		وڻ_TYPE (ميدان_2)
		  = build_bitint_type (ويڪر, TYPE_UNSIGNED (type));
	      وإلا
		وڻ_TYPE (ميدان_2)
		  = c_build_bitfield_integer_type (ويڪر,
						   TYPE_UNSIGNED (type));
	      إذا (وڻ attr = c_hardbool_type_attr (type))
		decl_خاصيتون (&وڻ_TYPE (ميدان_2),
				 copy_list (attr),
				 0, NULL_وڻ);
	      سيٽ_DECL_گهڻائي (ميدان_2, TYPE_گهڻائي (وڻ_TYPE (ميدان_2)));
	    }
	  DECL_INITIAL (ميدان_2) = NULL_وڻ;
	}
      وإلا إذا (TYPE_ابتو_STORAGE_ترتيب (t)
	       && وڻ_ڪوڊ (ميدان_2) == ميدان_DECL
	       && وڻ_ڪوڊ (وڻ_TYPE (ميدان_2)) == ARRAY_TYPE)
	{
	  وڻ ftype = وڻ_TYPE (ميدان_2);
	  وڻ ctype = strip_array_types (ftype);
	  إذا (!رڪارڊ_OR_UNION_TYPE_P (ctype) && TYPE_گهڻائي (ctype) != QImode)
	    {
	      وڻ fmain_type = TYPE_MAIN_VARIANT (ftype);
	      وڻ *typep = &fmain_type;
	      افعل {
		*typep = build_distinct_type_copy (*typep);
		TYPE_ابتو_STORAGE_ترتيب (*typep) = 1;
		typep = &وڻ_TYPE (*typep);
	      } طالما (وڻ_ڪوڊ (*typep) == ARRAY_TYPE);
	      وڻ_TYPE (ميدان_2)
		= c_build_qualified_type (fmain_type, TYPE_QUALS (ftype));
	    }
	}

      /* Warn on problematic type punning for storage order purposes.  */
      إذا (وڻ_ڪوڊ (t) == UNION_TYPE
	  && وڻ_ڪوڊ (ميدان_2) == ميدان_DECL
	  && AGGREGATE_TYPE_P (وڻ_TYPE (ميدان_2)))
	{
	  وڻ ftype = وڻ_TYPE (ميدان_2);
	  إذا (وڻ_ڪوڊ (ftype) == ARRAY_TYPE)
	    ftype = strip_array_types (ftype);
	  إذا (رڪارڊ_OR_UNION_TYPE_P (ftype)
	      && TYPE_ابتو_STORAGE_ترتيب (ftype)
		 != TYPE_ابتو_STORAGE_ترتيب (t))
	    warning_at (DECL_ذريعو_LOCATION (ميدان_2),
			OPT_Wscalar_storage_ترتيب,
			"type punning toggles scalar storage order");
	}
    }

  /* Now we have the truly final field list.
     Store it in this type and in the variants.  */

  TYPE_FIELDS (t) = fieldlist;

  /* If there are lots of fields, sort so we can look through them fast.
     We arbitrarily consider 16 or more elts to be "a lot".  */

  {
    صحيح len = 0;

    لكل (x = fieldlist; x; x = DECL_CHAIN (x))
      {
	إذا (len > 15 || DECL_NAME (x) == عدم)
	  اكسر;
	len += 1;
      }

    إذا (len > 15)
      {
	وڻ *ميدان_array;
	بنية lang_type *space;
	بنية sorted_fields_type *space2;

	len += list_ڊيگهائي (x);

	/* Use the same allocation policy here that make_node uses, to
	   ensure that this lives as long as the rest of the struct decl.
	   All decls in an inline function need to be saved.  */

	space = ((بنية lang_type *)
		 ggc_اندروني_cleared_alloc (c_dialect_objc ()
					     ? حجم (بنية lang_type)
					     : offsetof (بنية lang_type,
							 info)));
	space2 = ((sorted_fields_type *)
		  ggc_اندروني_alloc (حجم (بنية sorted_fields_type)
				      + len * حجم (وڻ)));

	len = 0;
	space->s = space2;
	ميدان_array = &space2->elts[0];
	لكل (x = fieldlist; x; x = DECL_CHAIN (x))
	  {
	    ميدان_array[len++] = x;

	    /* If there is anonymous struct or union, break out of the loop.  */
	    إذا (DECL_NAME (x) == عدم)
	      اكسر;
	  }
	/* Found no anonymous struct/union.  Add the TYPE_LANG_SPECIFIC.  */
	إذا (x == عدم)
	  {
	    TYPE_LANG_SPECIFIC (t) = space;
	    TYPE_LANG_SPECIFIC (t)->s->len = len;
	    ميدان_array = TYPE_LANG_SPECIFIC (t)->s->elts;
	    qsort (ميدان_array, len, حجم (وڻ), ميدان_decl_cmp);
	  }
      }
  }

  /* If this was supposed to be a transparent union, but we can't
     make it one, warn and turn off the flag.  */
  إذا (وڻ_ڪوڊ (t) == UNION_TYPE
      && TYPE_TRANSPARENT_AGGR (t)
      && (!TYPE_FIELDS (t) || TYPE_گهڻائي (t) != DECL_گهڻائي (TYPE_FIELDS (t))))
    {
      TYPE_TRANSPARENT_AGGR (t) = 0;
      warning_at (loc, 0, "union cannot be made transparent");
    }

  وڻ incomplete_vars = C_TYPE_INCOMPLETE_VARS (TYPE_MAIN_VARIANT (t));
  لكل (x = TYPE_MAIN_VARIANT (t); x; x = TYPE_ايندڙ_VARIANT (x))
    {
      TYPE_FIELDS (x) = TYPE_FIELDS (t);
      TYPE_LANG_SPECIFIC (x) = TYPE_LANG_SPECIFIC (t);
      TYPE_TRANSPARENT_AGGR (x) = TYPE_TRANSPARENT_AGGR (t);
      TYPE_TYPELESS_STORAGE (x) = TYPE_TYPELESS_STORAGE (t);
      C_TYPE_FIELDS_READONLY (x) = C_TYPE_FIELDS_READONLY (t);
      C_TYPE_FIELDS_VOLATILE (x) = C_TYPE_FIELDS_VOLATILE (t);
      C_TYPE_FIELDS_NON_CONSTEXPR (x) = C_TYPE_FIELDS_NON_CONSTEXPR (t);
      C_TYPE_FIELDS_HAS_COUNTED_BY (x) = C_TYPE_FIELDS_HAS_COUNTED_BY (t);
      C_TYPE_VARIABLE_سائيز (x) = C_TYPE_VARIABLE_سائيز (t);
      C_TYPE_VARIABLY_MODIFIED (x) = C_TYPE_VARIABLY_MODIFIED (t);
      C_TYPE_INCOMPLETE_VARS (x) = NULL_وڻ;
      TYPE_INCLUDES_FLEXARRAY (x) = TYPE_INCLUDES_FLEXARRAY (t);
    }

  /* Check for consistency with previous definition.  */
  إذا (flag_isoc23 && عدم != enclosing_struct_parse_info)
    {
      وڻ vistype = اڳيون_ٽيگ (t);
      إذا (vistype
	  && وڻ_ڪوڊ (vistype) == وڻ_ڪوڊ (t)
	  && !C_TYPE_BEING_DEFINED (vistype))
	{
	  TYPE_STUB_DECL (t) = TYPE_STUB_DECL (vistype);
	  إذا (c_type_variably_modified_p (t))
	    {
	      error ("redefinition of struct or union %qT with variably "
		     "modified type", t);
	      إذا (struct_parse_info->refloc != UNKNOWN_LOCATION)
		inform (struct_parse_info->refloc, "originally defined here");
	    }
	  وإلا إذا (!comptypes_same_p (t, vistype))
	    {
	      error ("redefinition of struct or union %qT", t);
	      إذا (struct_parse_info->refloc != UNKNOWN_LOCATION)
		inform (struct_parse_info->refloc, "originally defined here");
	    }
	}
    }

  C_TYPE_BEING_DEFINED (t) = 0;

  إذا (lookup_attribute ("may_alias", TYPE_خاصيتون (t)))
    لكل (x = TYPE_MAIN_VARIANT (t); x; x = TYPE_ايندڙ_VARIANT (x))
      c_fixup_may_alias (x);

  /* Set type canonical based on equivalence class.  */
  إذا (flag_isoc23 && !C_TYPE_VARIABLE_سائيز (t))
    {
      إذا (c_struct_htab == عدم)
	c_struct_htab = hash_جدول<c_struct_hasher>::create_ggc (61);

      hashval_t hash = c_struct_hasher::hash (t);

      gcc_checking_assert (TYPE_STRUCTURAL_EQUALITY_P (t));
      gcc_checking_assert (!TYPE_NAME (t)
			   || وڻ_ڪوڊ (TYPE_NAME (t)) == IDENTIFIER_ڳنڍ);

      وڻ *e = c_struct_htab->ڳوليو_جڳهه_with_hash (t, hash, وجهو);
      إذا (*e)
	TYPE_CANONICAL (t) = TYPE_CANONICAL (*e);
      وإلا
	{
	  TYPE_CANONICAL (t) = c_type_canonical (t);
	  *e = t;
	}
      c_update_type_canonical (t);
    }

  /* Update type location to the one of the definition, instead of e.g.
     a forward declaration.  */
  إذا (TYPE_STUB_DECL (t))
    DECL_ذريعو_LOCATION (TYPE_STUB_DECL (t)) = loc;

  /* Finish debugging output for this type.  */
  rest_جو_type_compilation (t, toplevel);

  پڄاڻي_incomplete_vars (incomplete_vars, toplevel);


  إذا (c_type_variably_modified_p (t))
    {
      c_update_variably_modified (t);
      /* Make sure a DECL_EXPR is created for structs with VLA members.
	 Because we do not know the context, we always pass expr
	 to force creation of a BIND_EXPR which is required in some
	 contexts.  */
      جوڙيو_decl_اظهار (loc, t, اظهار, خطأ);
    }

  إذا (warn_cxx_compat)
    warn_cxx_compat_پڄاڻي_struct (fieldlist, وڻ_ڪوڊ (t), loc);

  إذا (عدم != enclosing_struct_parse_info)
    {
      ميٽيو struct_parse_info;

      struct_parse_info = enclosing_struct_parse_info;

      /* If this struct is defined inside a struct, add it to
	 struct_types.  */
      إذا (warn_cxx_compat
	  && struct_parse_info != عدم
	  && !اندريون_sizeof && !اندريون_typeof && !اندريون_alignof && !اندريون_countof)
	struct_parse_info->struct_types.محفوظ_ڌڪو (t);
     }

  /* Only when the enclosing struct/union type is not anonymous, do more
     verification on the fields with counted_by attributes.  */
  إذا (C_TYPE_FIELDS_HAS_COUNTED_BY (t) && c_type_ٽيگ (t) != NULL_وڻ)
    verify_counted_by_attribute (t, t);

  أرجع t;
}

ساكن بنية {
  gt_اشارو_operator new_قدر;
  فراغ *cookie;
} resort_معلومات;

/* This routine compares two fields like field_decl_cmp but using the
pointer operator in resort_data.  */

ساكن صحيح
resort_ميدان_decl_cmp (ثابت فراغ *x_p, ثابت فراغ *y_p)
{
  ثابت وڻ *ثابت x = (ثابت وڻ *) x_p;
  ثابت وڻ *ثابت y = (ثابت وڻ *) y_p;

  إذا (DECL_NAME (*x) == DECL_NAME (*y))
    /* A nontype is "greater" than a type.  */
    أرجع (وڻ_ڪوڊ (*y) == TYPE_DECL) - (وڻ_ڪوڊ (*x) == TYPE_DECL);
  إذا (DECL_NAME (*x) == NULL_وڻ)
    أرجع -1;
  إذا (DECL_NAME (*y) == NULL_وڻ)
    أرجع 1;
  {
    وڻ d1 = DECL_NAME (*x);
    وڻ d2 = DECL_NAME (*y);
    resort_معلومات.new_قدر (&d1, &d1, resort_معلومات.cookie);
    resort_معلومات.new_قدر (&d2, &d2, resort_معلومات.cookie);
    إذا (d1 < d2)
      أرجع -1;
  }
  أرجع 1;
}

/* Resort DECL_SORTED_FIELDS because pointers have been reordered.  */

فراغ
resort_sorted_fields (فراغ *obj,
		      فراغ * ARG_اڻ_استعمال_ٿيل (orig_obj),
		      gt_اشارو_operator new_قدر,
		      فراغ *cookie)
{
  بنية sorted_fields_type *sf = (بنية sorted_fields_type *) obj;
  resort_معلومات.new_قدر = new_قدر;
  resort_معلومات.cookie = cookie;
  qsort (&sf->elts[0], sf->len, حجم (وڻ),
	 resort_ميدان_decl_cmp);
}

/* Lay out the type T, and its element type, and so on.  */

ساكن فراغ
layout_array_type (وڻ t)
{
  إذا (وڻ_ڪوڊ (وڻ_TYPE (t)) == ARRAY_TYPE)
    layout_array_type (وڻ_TYPE (t));
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

وڻ
شروعات_enum (location_t loc, بنية c_enum_contents *the_enum, وڻ name,
	    وڻ fixed_underlying_type, منطقي potential_nesting_p)
{
  وڻ enumtype = NULL_وڻ;
  location_t enumloc = UNKNOWN_LOCATION;

  /* If this is the real definition for a previous forward reference,
     fill in the contents in the same object that used to be the
     forward reference.  */

  إذا (name != NULL_وڻ)
    enumtype = lookup_ٽيگ (ENUMERAL_TYPE, name, سچ, &enumloc);

  إذا (enumtype != NULL_وڻ && وڻ_ڪوڊ (enumtype) == ENUMERAL_TYPE)
    {
      /* If the type is currently being defined or if we have seen an
	 incomplete version which is now complete, this is a nested
	 redefinition.  The later happens if the redefinition occurs
	 inside the enum specifier itself.  */
      إذا (C_TYPE_BEING_DEFINED (enumtype)
	  || (potential_nesting_p && TYPE_قدرون (enumtype) != NULL_وڻ))
	error_at (loc, "nested redefinition of %<enum %E%>", name);

      /* For C23 we allow redefinitions.  We set to zero and check for
	 consistency later.  */
      إذا (flag_isoc23 && TYPE_قدرون (enumtype) != NULL_وڻ)
	enumtype = NULL_وڻ;
    }

  إذا (enumtype == NULL_وڻ || وڻ_ڪوڊ (enumtype) != ENUMERAL_TYPE)
    {
      enumtype = make_ڳنڍ (ENUMERAL_TYPE);
      TYPE_سائيز (enumtype) = NULL_وڻ;
      سيٽ_TYPE_STRUCTURAL_EQUALITY (enumtype);
      pushtag (loc, name, enumtype);
      إذا (fixed_underlying_type != NULL_وڻ)
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
	  سيٽ_TYPE_ALIGN (enumtype, TYPE_ALIGN (fixed_underlying_type));
	  TYPE_سائيز (enumtype) = NULL_وڻ;
	  TYPE_PRECISION (enumtype) = TYPE_PRECISION (fixed_underlying_type);
	  ENUM_UNDERLYING_TYPE (enumtype) = fixed_underlying_type;
	  TYPE_CANONICAL (enumtype) = TYPE_CANONICAL (fixed_underlying_type);
	  c_update_type_canonical (enumtype);
	  layout_type (enumtype);
	}
    }
  /* Update type location to the one of the definition, instead of e.g.
     a forward declaration.  */
  وإلا إذا (TYPE_STUB_DECL (enumtype))
    {
      enumloc = DECL_ذريعو_LOCATION (TYPE_STUB_DECL (enumtype));
      DECL_ذريعو_LOCATION (TYPE_STUB_DECL (enumtype)) = loc;
    }

  C_TYPE_BEING_DEFINED (enumtype) = 1;

  إذا (TYPE_قدرون (enumtype) != NULL_وڻ)
    {
      /* This enum is a named one that has been declared already.  */
      auto_diagnostic_گروهه d;
      error_at (loc, "redeclaration of %<enum %E%>", name);
      إذا (enumloc != UNKNOWN_LOCATION)
	inform (enumloc, "originally defined here");

      /* Completely replace its old definition.
	 The old enumerators remain defined, however.  */
      TYPE_قدرون (enumtype) = NULL_وڻ;
    }

  إذا (ENUM_FIXED_UNDERLYING_TYPE_P (enumtype)
      && fixed_underlying_type == NULL_وڻ)
    {
      error_at (loc, "%<enum%> declared with but defined without "
		"fixed underlying type");
      ENUM_FIXED_UNDERLYING_TYPE_P (enumtype) = خطأ;
    }

  the_enum->enum_ايندڙ_قدر = integer_zero_ڳنڍ;
  the_enum->enum_type = enumtype;
  the_enum->enum_حد_کان_مٿي = 0;

  إذا (flag_short_enums && !ENUM_FIXED_UNDERLYING_TYPE_P (enumtype))
    لكل (وڻ v = TYPE_MAIN_VARIANT (enumtype); v; v = TYPE_ايندڙ_VARIANT (v))
      TYPE_PACKED (v) = 1;

  /* FIXME: This will issue a warning for a use of a type defined
     within sizeof in a statement expr.  This is not terribly serious
     as C++ doesn't permit statement exprs within sizeof anyhow.  */
  إذا (warn_cxx_compat
      && (اندريون_sizeof || اندريون_typeof || اندريون_alignof || اندريون_countof))
    warning_at (loc, OPT_Wc___compat,
		"defining type in %qs expression is invalid in C++",
		(اندريون_sizeof ? "sizeof"
		 : اندريون_typeof ? "typeof"
		 : اندريون_alignof ? "alignof"
		 : "_Countof"));

  إذا (اندريون_underspecified_init)
    error_at (loc, "%qT defined in underspecified object initializer",
	      enumtype);

  أرجع enumtype;
}

/* After processing and defining all the values of an enumeration type,
   install their decls in the enumeration type and finish it off.
   ENUMTYPE is the type object, VALUES a list of decl-value pairs,
   and ATTRIBUTES are the specified attributes.
   Returns ENUMTYPE.  */

وڻ
پڄاڻي_enum (وڻ enumtype, وڻ قدرون, وڻ خاصيتون)
{
  وڻ pair, tem;
  وڻ minnode = NULL_وڻ, maxnode = NULL_وڻ;
  صحيح precision;
  signop sign;
  منطقي toplevel = (file_scope == current_scope);
  بنية lang_type *lt;

  decl_خاصيتون (&enumtype, خاصيتون, (صحيح) ATTR_FLAG_TYPE_اندريون_رکو);

  /* Calculate the maximum value of any enumerator in this type.  */

  إذا (قدرون == error_mark_ڳنڍ)
    minnode = maxnode = integer_zero_ڳنڍ;
  وإلا
    {
      minnode = maxnode = وڻ_قدر (قدرون);
      لكل (pair = وڻ_CHAIN (قدرون); pair; pair = وڻ_CHAIN (pair))
	{
	  وڻ قدر = وڻ_قدر (pair);
	  إذا (وڻ_int_cst_lt (maxnode, قدر))
	    maxnode = قدر;
	  إذا (وڻ_int_cst_lt (قدر, minnode))
	    minnode = قدر;
	}
    }

  /* Construct the final type of this enumeration.  It is the same
     as one of the integral types - the narrowest one that fits, except
     that normally we only go as narrow as int - and signed iff any of
     the values are negative.  */
  sign = (وڻ_int_cst_sgn (minnode) >= 0) ? UNSIGNED : SIGNED;
  precision = MAX (وڻ_int_cst_min_precision (minnode, sign),
		   وڻ_int_cst_min_precision (maxnode, sign));

  منطقي wider_than_int =
    (وڻ_int_cst_lt (minnode, TYPE_MIN_قدر (integer_type_ڳنڍ))
     || وڻ_int_cst_lt (TYPE_MAX_قدر (integer_type_ڳنڍ), maxnode));


  إذا (!ENUM_FIXED_UNDERLYING_TYPE_P (enumtype))
    {
      /* If the precision of the type was specified with an attribute and it
	 was too small, give an error.  Otherwise, use it.  */
      إذا (TYPE_PRECISION (enumtype) && lookup_attribute ("mode", خاصيتون))
	{
	  إذا (precision > TYPE_PRECISION (enumtype))
	    {
	      TYPE_PRECISION (enumtype) = 0;
	      error ("specified mode too small for enumerated values");
	    }
	  وإلا
	    precision = TYPE_PRECISION (enumtype);
	}
      وإلا
	TYPE_PRECISION (enumtype) = 0;

      إذا (TYPE_PACKED (enumtype)
	  || precision > TYPE_PRECISION (integer_type_ڳنڍ)
	  || TYPE_PRECISION (enumtype))
	{
	  tem = c_common_type_for_سائيز (precision, sign == UNSIGNED ? 1 : 0);
	  إذا (tem == عدم)
	    {
	      /* This should only occur when both signed and unsigned
		 values of maximum precision occur among the
		 enumerators.  */
	      pedwarn (داخلا_location, 0,
		       "enumeration values exceed range of largest integer");
	      tem = widest_integer_literal_type_ڳنڍ;
	    }
	  وإلا إذا (precision > TYPE_PRECISION (intmax_type_ڳنڍ)
		   && !وڻ_int_cst_lt (minnode,
					TYPE_MIN_قدر (intmax_type_ڳنڍ))
		   && !وڻ_int_cst_lt (TYPE_MAX_قدر (uintmax_type_ڳنڍ),
					maxnode))
	    pedwarn (داخلا_location, OPT_Wpedantic,
		     "enumeration values exceed range of %qs",
		     sign == UNSIGNED ? "uintmax_t" : "intmax_t");
	}
      وإلا
	tem = sign == UNSIGNED ? unsigned_type_ڳنڍ : integer_type_ڳنڍ;

      TYPE_MIN_قدر (enumtype) = TYPE_MIN_قدر (tem);
      TYPE_MAX_قدر (enumtype) = TYPE_MAX_قدر (tem);
      TYPE_UNSIGNED (enumtype) = TYPE_UNSIGNED (tem);
      سيٽ_TYPE_ALIGN (enumtype, TYPE_ALIGN (tem));
      TYPE_سائيز (enumtype) = NULL_وڻ;
      TYPE_PRECISION (enumtype) = TYPE_PRECISION (tem);
      ENUM_UNDERLYING_TYPE (enumtype) =
	c_common_type_for_سائيز (TYPE_PRECISION (tem), TYPE_UNSIGNED (tem));

      TYPE_CANONICAL (enumtype) =
	TYPE_CANONICAL (ENUM_UNDERLYING_TYPE (enumtype));
      c_update_type_canonical (enumtype);

      layout_type (enumtype);
    }

  إذا (قدرون != error_mark_ڳنڍ)
    {
      /* Change the type of the enumerators to be the enum type.  We
	 need to do this irrespective of the size of the enum, for
	 proper type checking.  Replace the DECL_INITIALs of the
	 enumerators, and the value slots of the list, with copies
	 that have the enum type; they cannot be modified in place
	 because they may be shared (e.g.  integer_zero_node) Finally,
	 change the purpose slots to point to the names of the decls.  */
      لكل (pair = قدرون; pair; pair = وڻ_CHAIN (pair))
	{
	  وڻ enu = وڻ_PURPOSE (pair);
	  وڻ ini = DECL_INITIAL (enu);

	  وڻ_TYPE (enu) = enumtype;

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
	  إذا (!ENUM_FIXED_UNDERLYING_TYPE_P (enumtype) && wider_than_int)
	    ini = convert (enumtype, ini);

	  DECL_INITIAL (enu) = ini;
	  وڻ_PURPOSE (pair) = DECL_NAME (enu);
	  /* To match the C++ FE, store the CONST_DECL rather than just its
	     value.  */
	  وڻ_قدر (pair) = enu;
	}

      TYPE_قدرون (enumtype) = قدرون;
    }

  /* Record the min/max values so that we can warn about bit-field
     enumerations that are too small for the values.  */
  lt = ((بنية lang_type *)
	ggc_اندروني_cleared_alloc (c_dialect_objc ()
				    ? حجم (بنية lang_type)
				    : offsetof (بنية lang_type, info)));
  lt->enum_min = minnode;
  lt->enum_max = maxnode;
  TYPE_LANG_SPECIFIC (enumtype) = lt;

  /* Fix up all variant types of this enum type.  */
  وڻ incomplete_vars = C_TYPE_INCOMPLETE_VARS (TYPE_MAIN_VARIANT (enumtype));
  لكل (tem = TYPE_MAIN_VARIANT (enumtype); tem; tem = TYPE_ايندڙ_VARIANT (tem))
    {
      C_TYPE_INCOMPLETE_VARS (tem) = NULL_وڻ;
      إذا (tem == enumtype)
	استمر;
      TYPE_قدرون (tem) = TYPE_قدرون (enumtype);
      TYPE_MIN_قدر (tem) = TYPE_MIN_قدر (enumtype);
      TYPE_MAX_قدر (tem) = TYPE_MAX_قدر (enumtype);
      TYPE_سائيز (tem) = TYPE_سائيز (enumtype);
      TYPE_سائيز_UNIT (tem) = TYPE_سائيز_UNIT (enumtype);
      سيٽ_TYPE_گهڻائي (tem, TYPE_گهڻائي (enumtype));
      TYPE_PRECISION (tem) = TYPE_PRECISION (enumtype);
      سيٽ_TYPE_ALIGN (tem, TYPE_ALIGN (enumtype));
      TYPE_USER_ALIGN (tem) = TYPE_USER_ALIGN (enumtype);
      TYPE_UNSIGNED (tem) = TYPE_UNSIGNED (enumtype);
      TYPE_LANG_SPECIFIC (tem) = TYPE_LANG_SPECIFIC (enumtype);
      ENUM_UNDERLYING_TYPE (tem) = ENUM_UNDERLYING_TYPE (enumtype);
      TYPE_PACKED (tem) = TYPE_PACKED (enumtype);
    }

  /* Finish debugging output for this type.  */
  rest_جو_type_compilation (enumtype, toplevel);

  پڄاڻي_incomplete_vars (incomplete_vars, toplevel);

  /* If this enum is defined inside a struct, add it to
     struct_types.  */
  إذا (warn_cxx_compat
      && struct_parse_info != عدم
      && !اندريون_sizeof && !اندريون_typeof && !اندريون_alignof && !اندريون_countof)
    struct_parse_info->struct_types.محفوظ_ڌڪو (enumtype);

  /* Check for consistency with previous definition */
  إذا (flag_isoc23)
    {
      وڻ vistype = اڳيون_ٽيگ (enumtype);
      إذا (vistype
	  && وڻ_ڪوڊ (vistype) == وڻ_ڪوڊ (enumtype)
	  && !C_TYPE_BEING_DEFINED (vistype))
	{
	  TYPE_STUB_DECL (enumtype) = TYPE_STUB_DECL (vistype);
	  إذا (!comptypes_same_p (enumtype, vistype))
	    error("conflicting redefinition of enum %qT", enumtype);
	}
    }

  C_TYPE_BEING_DEFINED (enumtype) = 0;

  أرجع enumtype;
}

/* Build and install a CONST_DECL for one value of the
   current enumeration type (one that was begun with start_enum).
   DECL_LOC is the location of the enumerator.
   LOC is the location of the '=' operator if any, DECL_LOC otherwise.
   Return a tree-list containing the CONST_DECL and its value.
   Assignment of sequential values by default is handled here.  */

وڻ
build_enumerator (location_t decl_loc, location_t loc,
		  بنية c_enum_contents *the_enum, وڻ name, وڻ قدر)
{
  وڻ decl;
  وڻ old_decl;

  /* Validate and default VALUE.  */

  إذا (قدر != NULL_وڻ)
    {
      /* Don't issue more errors for error_mark_node (i.e. an
	 undeclared identifier) - just ignore the value expression.  */
      إذا (قدر == error_mark_ڳنڍ)
	قدر = NULL_وڻ;
      وإلا إذا (!INTEGRAL_TYPE_P (وڻ_TYPE (قدر)))
	{
	  error_at (loc, "enumerator value for %qE is not an integer constant",
		    name);
	  قدر = NULL_وڻ;
	}
      وإلا
	{
	  إذا (وڻ_ڪوڊ (قدر) != INTEGER_CST)
	    {
	      قدر = c_fully_fold (قدر, خطأ, عدم);
	      إذا (وڻ_ڪوڊ (قدر) == INTEGER_CST)
		pedwarn (loc, OPT_Wpedantic,
			 "enumerator value for %qE is not an integer "
			 "constant expression", name);
	    }
	  إذا (وڻ_ڪوڊ (قدر) != INTEGER_CST)
	    {
	      error ("enumerator value for %qE is not an integer constant",
		     name);
	      قدر = NULL_وڻ;
	    }
	  وإلا
	    {
	      قدر = default_conversion (قدر);
	      constant_اظهار_warning (قدر);
	    }
	}
    }

  /* Default based on previous value.  */
  /* It should no longer be possible to have NON_LVALUE_EXPR
     in the default.  */
  إذا (قدر == NULL_وڻ)
    {
      قدر = the_enum->enum_ايندڙ_قدر;
      إذا (the_enum->enum_حد_کان_مٿي)
	error_at (loc, "overflow in enumeration values");
    }
  إذا (ENUM_FIXED_UNDERLYING_TYPE_P (the_enum->enum_type))
    {
      /* Enumeration constants must fit in the fixed underlying type.  */
      إذا (!int_سمائي_type_p (قدر, ENUM_UNDERLYING_TYPE (the_enum->enum_type)))
	error_at (loc,
		  "enumerator value outside the range of underlying type");
      /* Enumeration constants for an enum with fixed underlying type
	 have the enum type, both inside and outside the
	 definition.  */
      قدر = convert (the_enum->enum_type, قدر);
    }
  وإلا إذا (flag_isoc23
	   && (old_decl = lookup_name_اندريون_scope (name, current_scope))
	   && old_decl != error_mark_ڳنڍ
	   && وڻ_TYPE (old_decl)
	   && وڻ_TYPE (وڻ_TYPE (old_decl))
	   && وڻ_ڪوڊ (old_decl) == CONST_DECL)
    {
      /* Enumeration constants in a redeclaration have the previous type.  */
      وڻ اڳيون_type = وڻ_TYPE (DECL_INITIAL (old_decl));
      إذا (!int_سمائي_type_p (قدر, اڳيون_type))
	{
	  error_at (loc, "value of redeclared enumerator outside the range "
			 "of %qT", اڳيون_type);
	  locate_old_decl (old_decl);
	}
      قدر = convert (اڳيون_type, قدر);
    }
  وإلا
    {
      /* Even though the underlying type of an enum is unspecified, the
	 type of enumeration constants is explicitly defined as int
	 (6.4.4.3/2 in the C99 Standard).  C23 allows any integer type, and
	 GCC allows such types for older standards as an extension.  */
      منطقي warned_range = خطأ;
      إذا (!int_سمائي_type_p (قدر,
			    (TYPE_UNSIGNED (وڻ_TYPE (قدر))
			     ? uintmax_type_ڳنڍ
			     : intmax_type_ڳنڍ)))
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
				TYPE_UNSIGNED (وڻ_TYPE (قدر))
				? "uintmax_t"
				: "intmax_t");
      إذا (!warned_range && !int_سمائي_type_p (قدر, integer_type_ڳنڍ))
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
      إذا (int_سمائي_type_p (قدر, integer_type_ڳنڍ))
	قدر = convert (integer_type_ڳنڍ, قدر);
    }

  /* Set basis for default for next value.  */
  إذا (ENUM_FIXED_UNDERLYING_TYPE_P (the_enum->enum_type))
    {
      وڻ underlying_type = ENUM_UNDERLYING_TYPE (the_enum->enum_type);
      إذا (وڻ_ڪوڊ (underlying_type) == BOOLEAN_TYPE)
	/* A value of 2 following a value of 1 overflows bool, but we
	   cannot carry out addition directly on bool without
	   promotion, and converting the result of arithmetic in a
	   wider type back to bool would not produce the right result
	   for this overflow check.  */
	the_enum->enum_ايندڙ_قدر = invert_truthvalue_loc (loc, قدر);
      وإلا
	the_enum->enum_ايندڙ_قدر
	  = build_ٻٽو_op (اظهار_LOC_OR_LOC (قدر, داخلا_location),
			     PLUS_اظهار, convert (underlying_type, قدر),
			     convert (underlying_type, integer_one_ڳنڍ),
			     خطأ);
    }
  وإلا
    {
      /* In a redeclaration the type can already be the enumeral type.  */
      إذا (وڻ_ڪوڊ (وڻ_TYPE (قدر)) == ENUMERAL_TYPE)
	قدر = convert (ENUM_UNDERLYING_TYPE (وڻ_TYPE (قدر)), قدر);
      the_enum->enum_ايندڙ_قدر
	= build_ٻٽو_op (اظهار_LOC_OR_LOC (قدر, داخلا_location),
			   PLUS_اظهار, قدر, integer_one_ڳنڍ, خطأ);
    }
  the_enum->enum_حد_کان_مٿي = وڻ_int_cst_lt (the_enum->enum_ايندڙ_قدر, قدر);
  إذا (the_enum->enum_حد_کان_مٿي
      && !ENUM_FIXED_UNDERLYING_TYPE_P (the_enum->enum_type))
    {
      /* Choose a wider type with the same signedness if
	 available.  */
      صحيح prec = TYPE_PRECISION (وڻ_TYPE (قدر)) + 1;
      منطقي unsignedp = TYPE_UNSIGNED (وڻ_TYPE (قدر));
      وڻ new_type = (unsignedp
		       ? long_unsigned_type_ڳنڍ
		       : long_integer_type_ڳنڍ);
      إذا (prec > TYPE_PRECISION (new_type))
	new_type = (unsignedp
		    ? long_long_unsigned_type_ڳنڍ
		    : long_long_integer_type_ڳنڍ);
      إذا (prec > TYPE_PRECISION (new_type))
	new_type = (unsignedp
		    ? widest_unsigned_literal_type_ڳنڍ
		    : widest_integer_literal_type_ڳنڍ);
      إذا (prec <= TYPE_PRECISION (new_type))
	{
	  the_enum->enum_حد_کان_مٿي = خطأ;
	  the_enum->enum_ايندڙ_قدر
	    = build_ٻٽو_op (اظهار_LOC_OR_LOC (قدر, داخلا_location),
			       PLUS_اظهار, convert (new_type, قدر),
			       integer_one_ڳنڍ, خطأ);
	  gcc_assert (!وڻ_int_cst_lt (the_enum->enum_ايندڙ_قدر, قدر));
	}
    }

  /* Now create a declaration for the enum value name.  */

  decl = build_decl (decl_loc, CONST_DECL, name, وڻ_TYPE (قدر));
  DECL_INITIAL (decl) = قدر;
  DECL_CONTEXT (decl) = the_enum->enum_type;
  pushdecl (decl);

  أرجع وڻ_cons (decl, قدر, NULL_وڻ);
}

/* Implement LANG_HOOKS_SIMULATE_ENUM_DECL.  */

وڻ
c_simulate_enum_decl (location_t loc, ثابت حرف *name,
		      vec<string_int_pair> *قدرون_ptr)
{
  location_t saved_loc = داخلا_location;
  داخلا_location = loc;

  بنية c_enum_contents the_enum;
  وڻ enumtype = شروعات_enum (loc, &the_enum, get_identifier (name),
			      NULL_وڻ, خطأ);

  وڻ قدر_chain = NULL_وڻ;
  string_int_pair *قدر;
  vec<string_int_pair> قدرون = *قدرون_ptr;
  بنانشان صحيح i;
  FOR_EACH_VEC_ELT (قدرون, i, قدر)
    {
      وڻ decl = build_enumerator (loc, loc, &the_enum,
				    get_identifier (قدر->پهريون),
				    build_int_cst (integer_type_ڳنڍ,
						   قدر->ٻيو));
      وڻ_CHAIN (decl) = قدر_chain;
      قدر_chain = decl;
    }

  پڄاڻي_enum (enumtype, nreverse (قدر_chain), NULL_وڻ);

  داخلا_location = saved_loc;
  أرجع enumtype;
}

/* Implement LANG_HOOKS_SIMULATE_RECORD_DECL.  */

وڻ
c_simulate_رڪارڊ_decl (location_t loc, ثابت حرف *name,
			array_ٽڪرو<ثابت وڻ> fields)
{
  location_t saved_loc = داخلا_location;
  داخلا_location = loc;

  صنف c_struct_parse_info *struct_info;
  وڻ ident = get_identifier (name);
  وڻ type = شروعات_struct (loc, رڪارڊ_TYPE, ident, &struct_info);

  لكل (بنانشان صحيح i = 0; i < fields.سائيز (); ++i)
    {
      DECL_ميدان_CONTEXT (fields[i]) = type;
      إذا (i > 0)
	DECL_CHAIN (fields[i - 1]) = fields[i];
    }

  پڄاڻي_struct (loc, type, fields[0], NULL_وڻ, struct_info);

  وڻ decl = build_decl (loc, TYPE_DECL, ident, type);
  سيٽ_underlying_type (decl);
  lang_hooks.decls.pushdecl (decl);

  داخلا_location = saved_loc;
  أرجع type;
}

/* Create the FUNCTION_DECL for a function definition.
   DECLSPECS, DECLARATOR and ATTRIBUTES are the parts of
   the declaration; they describe the function's name and the type it returns,
   but twisted together in a fashion that parallels the syntax of C.

   This function creates a binding context for the function body
   as well as setting up the FUNCTION_DECL in current_function_decl.

   Returns true on success.  If the DECLARATOR is not suitable for a function
   (it defines a datum instead), we return false to report a parse error.  */

منطقي
شروعات_function (بنية c_declspecs *declspecs, بنية c_declarator *declarator,
		وڻ خاصيتون)
{
  وڻ decl1, old_decl;
  وڻ restype, resdecl;
  location_t loc;
  location_t نتيجو_loc;
  وڻ اظهار = عدم;

  current_function_returns_قدر = 0;  /* Assume, until we see it does.  */
  current_function_returns_null = 0;
  current_function_returns_abnormally = 0;
  warn_about_return_type = 0;
  c_switch_ڍير = عدم;

  /* Indicate no valid break/continue context.  */
  اندريون_statement = 0;

  decl1 = grokdeclarator (declarator, declspecs, FUNCDEF, سچ, عدم,
			  &خاصيتون, &اظهار, عدم, DEPRECATED_عام);
  invoke_plugin_callbacks (PLUGIN_شروعات_PARSE_FUNCTION, decl1);

  /* If the declarator is not suitable for a function definition,
     cause a syntax error.  */
  إذا (decl1 == NULL_وڻ
      || وڻ_ڪوڊ (decl1) != FUNCTION_DECL)
    أرجع خطأ;

  /* Nested functions may have variably modified (return) type.
     Make sure the size expression is evaluated at this point.  */
  إذا (اظهار && !current_scope->parm_flag)
    جوڙيو_stmt (fold_convert (void_type_ڳنڍ, اظهار));

  loc = DECL_ذريعو_LOCATION (decl1);

  /* A nested function is not global.  */
  إذا (current_function_decl != NULL_وڻ)
    وڻ_عوامي (decl1) = 0;

  c_decl_خاصيتون (&decl1, خاصيتون, 0);

  إذا (DECL_DECLARED_INLINE_P (decl1)
      && DECL_UNINLINABLE (decl1)
      && lookup_attribute ("noinline", DECL_خاصيتون (decl1)))
    {
      auto_urlify_خاصيتون sentinel;
      warning_at (loc, OPT_Wattributes,
		  "inline function %qD given attribute %qs",
		  decl1, "noinline");
    }

  /* Handle gnu_inline attribute.  */
  إذا (declspecs->inline_p
      && !flag_gnu89_inline
      && وڻ_ڪوڊ (decl1) == FUNCTION_DECL
      && (lookup_attribute ("gnu_inline", DECL_خاصيتون (decl1))
	  || current_function_decl))
    {
      إذا (declspecs->storage_class != csc_static)
	DECL_EXTERNAL (decl1) = !DECL_EXTERNAL (decl1);
    }

  announce_function (decl1);

  إذا (!COMPLETE_OR_VOID_TYPE_P (وڻ_TYPE (وڻ_TYPE (decl1))))
    {
      error_at (loc, "return type is an incomplete type");
      /* Make it return void instead.  */
      وڻ_TYPE (decl1)
	= c_build_function_type (void_type_ڳنڍ,
				 TYPE_ARG_TYPES (وڻ_TYPE (decl1)),
				 TYPE_NO_NAMED_دليلون_STDARG_P (وڻ_TYPE (decl1)));
    }

  إذا (warn_about_return_type)
    permerror_opt (loc, flag_isoc99 ? OPT_Wimplicit_int
		   : (warn_return_type > 0 ? OPT_Wreturn_type
		      : OPT_Wimplicit_int),
		   "return type defaults to %<int%>");

  /* Make the init_value nonzero so pushdecl knows this is not tentative.
     error_mark_node is replaced below (in pop_scope) with the BLOCK.  */
  DECL_INITIAL (decl1) = error_mark_ڳنڍ;

  /* If this definition isn't a prototype and we had a prototype declaration
     before, copy the arg type info from that prototype.  */
  old_decl = lookup_name_اندريون_scope (DECL_NAME (decl1), current_scope);
  إذا (old_decl && وڻ_ڪوڊ (old_decl) != FUNCTION_DECL)
    old_decl = NULL_وڻ;

  current_function_prototype_locus = UNKNOWN_LOCATION;
  current_function_prototype_built_اندريون = خطأ;
  current_function_prototype_arg_types = NULL_وڻ;
  وڻ newtype = وڻ_TYPE (decl1);
  وڻ oldtype = old_decl ? وڻ_TYPE (old_decl) : newtype;
  إذا (!prototype_p (newtype))
    {
      وڻ oldrt = وڻ_TYPE (oldtype);
      وڻ newrt = وڻ_TYPE (newtype);
      إذا (old_decl != NULL_وڻ
	  && وڻ_ڪوڊ (oldtype) == FUNCTION_TYPE
	  && comptypes (oldrt, newrt)
	  && !TYPE_NO_NAMED_دليلون_STDARG_P (oldtype))
	{
	  إذا (stdarg_p (oldtype))
	    {
	      auto_diagnostic_گروهه d;
	      warning_at (loc, 0, "%q+D defined as variadic function "
			  "without prototype", decl1);
	      locate_old_decl (old_decl);
	    }
	  وڻ_TYPE (decl1) = مرکب_type (oldtype, newtype);
	  current_function_prototype_locus = DECL_ذريعو_LOCATION (old_decl);
	  current_function_prototype_built_اندريون
	    = C_DECL_BUILTIN_PROTOTYPE (old_decl);
	  current_function_prototype_arg_types
	    = TYPE_ARG_TYPES (newtype);
	}
      إذا (وڻ_عوامي (decl1))
	{
	  /* If there is an external prototype declaration of this
	     function, record its location but do not copy information
	     to this decl.  This may be an invisible declaration
	     (built-in or in a scope which has finished) or simply
	     have more refined argument types than any declaration
	     found above.  */
	  بنية c_binding *b;
	  لكل (b = I_نشان_BINDING (DECL_NAME (decl1)); b; b = b->shadowed)
	    إذا (B_اندريون_SCOPE (b, external_scope))
	      اكسر;
	  إذا (b)
	    {
	      وڻ ext_decl, ext_type;
	      ext_decl = b->decl;
	      ext_type = b->u.type ? b->u.type : وڻ_TYPE (ext_decl);
	      إذا (وڻ_ڪوڊ (ext_type) == FUNCTION_TYPE
		  && comptypes (وڻ_TYPE (وڻ_TYPE (decl1)),
				وڻ_TYPE (ext_type)))
		{
		  current_function_prototype_locus
		    = DECL_ذريعو_LOCATION (ext_decl);
		  current_function_prototype_built_اندريون
		    = C_DECL_BUILTIN_PROTOTYPE (ext_decl);
		  current_function_prototype_arg_types
		    = TYPE_ARG_TYPES (ext_type);
		}
	    }
	}
    }

  /* Optionally warn about C23 compatibility.  */
  إذا (warn_deprecated_non_prototype
      && old_decl != NULL_وڻ
      && وڻ_ڪوڊ (oldtype) == FUNCTION_TYPE
      && !TYPE_ARG_TYPES (oldtype)
      && !TYPE_NO_NAMED_دليلون_STDARG_P (oldtype)
      && (TYPE_ARG_TYPES (newtype)
	  && وڻ_قدر (TYPE_ARG_TYPES (newtype)) != void_type_ڳنڍ))
    {
      منطقي warned = warning_at (loc, OPT_Wdeprecated_non_prototype,
				"ISO C23 does not allow defining"
				" parameters for function %qE declared"
				" without parameters",
				decl1);
      إذا (warned)
	inform (DECL_ذريعو_LOCATION (old_decl), "declared here");
    }

  /* Optionally warn of old-fashioned def with no previous prototype.  */
  إذا (warn_strict_prototypes
      && old_decl != error_mark_ڳنڍ
      && !prototype_p (وڻ_TYPE (decl1))
      && C_DECL_ISNT_PROTOTYPE (old_decl))
    warning_at (loc, OPT_Wstrict_prototypes,
		"function declaration isn%'t a prototype");
  /* Optionally warn of any global def with no previous prototype.  */
  وإلا إذا (warn_missing_prototypes
	   && old_decl != error_mark_ڳنڍ
	   && وڻ_عوامي (decl1)
	   && !MAIN_NAME_P (DECL_NAME (decl1))
	   && C_DECL_ISNT_PROTOTYPE (old_decl)
	   && !DECL_DECLARED_INLINE_P (decl1))
    warning_at (loc, OPT_Wmissing_prototypes,
		"no previous prototype for %qD", decl1);
  /* Optionally warn of any def with no previous prototype
     if the function has already been used.  */
  وإلا إذا (warn_missing_prototypes
	   && old_decl != NULL_وڻ
	   && old_decl != error_mark_ڳنڍ
	   && وڻ_استعمال_ٿيل (old_decl)
	   && !prototype_p (وڻ_TYPE (old_decl)))
    warning_at (loc, OPT_Wmissing_prototypes,
		"%qD was used with no prototype before its definition", decl1);
  /* Optionally warn of any global def with no previous declaration.  */
  وإلا إذا (warn_missing_declarations
	   && وڻ_عوامي (decl1)
	   && old_decl == NULL_وڻ
	   && !MAIN_NAME_P (DECL_NAME (decl1))
	   && !DECL_DECLARED_INLINE_P (decl1))
    warning_at (loc, OPT_Wmissing_declarations,
		"no previous declaration for %qD",
		decl1);
  /* Optionally warn of any def with no previous declaration
     if the function has already been used.  */
  وإلا إذا (warn_missing_declarations
	   && old_decl != NULL_وڻ
	   && old_decl != error_mark_ڳنڍ
	   && وڻ_استعمال_ٿيل (old_decl)
	   && C_DECL_IMPLICIT (old_decl))
    warning_at (loc, OPT_Wmissing_declarations,
		"%qD was used with no declaration before its definition", decl1);

  /* This function exists in static storage.
     (This does not mean `static' in the C sense!)  */
  وڻ_STATIC (decl1) = 1;

  /* This is the earliest point at which we might know the assembler
     name of the function.  Thus, if it's set before this, die horribly.  */
  gcc_assert (!DECL_ASSEMBLER_NAME_سيٽ_P (decl1));

  /* If #pragma weak was used, mark the decl weak now.  */
  إذا (current_scope == file_scope)
    maybe_apply_pragma_weak (decl1);

  /* Warn for unlikely, improbable, or stupid declarations of `main'.  */
  إذا (warn_main && MAIN_NAME_P (DECL_NAME (decl1)))
    {
      إذا (TYPE_MAIN_VARIANT (وڻ_TYPE (وڻ_TYPE (decl1)))
	  != integer_type_ڳنڍ)
	pedwarn (loc, OPT_Wmain, "return type of %qD is not %<int%>", decl1);
      وإلا إذا (TYPE_ATOMIC (وڻ_TYPE (وڻ_TYPE (decl1))))
	pedwarn (loc, OPT_Wmain, "%<_Atomic%>-qualified return type of %qD",
		 decl1);

      check_main_parameter_types (decl1);

      إذا (!وڻ_عوامي (decl1))
	pedwarn (loc, OPT_Wmain,
		 "%qD is normally a non-static function", decl1);
    }

  وڻ parms = current_function_arg_info->parms;
  إذا (old_decl)
    {
      location_t origloc = DECL_ذريعو_LOCATION (old_decl);
      warn_parms_array_mismatch (origloc, old_decl, parms);
    }

  /* To enable versions to be created across TU's we mark and mangle all
     non-default versioned functions.  */
  إذا (وڻ_ڪوڊ (decl1) == FUNCTION_DECL
      && !هدف_HAS_FMV_هدف_ATTRIBUTE
      && get_هدف_نسخو (decl1).is_valid ())
    {
      maybe_mark_function_versioned (decl1);
      إذا (current_scope != file_scope)
	error ("versioned definitions are only allowed at file scope");
    }

  /* Record the decl so that the function name is defined.
     If we already have a decl for this name, and it is a FUNCTION_DECL,
     use the old decl.  */

  current_function_decl = pushdecl (decl1);

  إذا (وڻ access = build_attr_access_from_parms (parms, خطأ))
    decl_خاصيتون (&current_function_decl, access, ATTR_FLAG_اندروني,
		     old_decl);

  ڌڪو_scope ();
  declare_parm_level ();

  /* Set the result decl source location to the location of the typespec.  */
  نتيجو_loc = (declspecs->locations[cdw_typespec] == UNKNOWN_LOCATION
		? loc : declspecs->locations[cdw_typespec]);
  restype = وڻ_TYPE (وڻ_TYPE (current_function_decl));
  resdecl = build_decl (نتيجو_loc, نتيجو_DECL, NULL_وڻ, restype);
  DECL_ARTIFICIAL (resdecl) = 1;
  DECL_IGNORED_P (resdecl) = 1;
  DECL_نتيجو (current_function_decl) = resdecl;

  شروعات_fname_decls ();

  أرجع سچ;
}

/* Subroutine of store_parm_decls which handles new-style function
   definitions (prototype format). The parms already have decls, so we
   need only record them as in effect and complain if any redundant
   old-style parm decls were written.  */
ساكن فراغ
store_parm_decls_newstyle (وڻ fndecl, ثابت بنية c_arg_info *arg_info)
{
  وڻ decl;
  c_arg_ٽيگ *ٽيگ;
  بنانشان ix;

  إذا (current_scope->bindings)
    {
      error_at (DECL_ذريعو_LOCATION (fndecl),
		"old-style parameter declarations in prototyped "
		"function definition");

      /* Get rid of the old-style declarations.  */
      ڪڍو_scope ();
      ڌڪو_scope ();
    }
  /* Don't issue this warning for nested functions, and don't issue this
     warning if we got here because ARG_INFO_TYPES was error_mark_node
     (this happens when a function definition has just an ellipsis in
     its parameter list).  */
  وإلا إذا (!اندريون_system_سرو_at (داخلا_location)
	   && !current_function_scope
	   && arg_info->types != error_mark_ڳنڍ
	   && !arg_info->c23_خالي_جايون_parens)
    warning_at (DECL_ذريعو_LOCATION (fndecl), OPT_Wtraditional,
		"traditional C rejects ISO C style function definitions");

  /* Now make all the parameter declarations visible in the function body.
     We can bypass most of the grunt work of pushdecl.  */
  لكل (decl = arg_info->parms; decl; decl = DECL_CHAIN (decl))
    {
      DECL_CONTEXT (decl) = current_function_decl;
      إذا (DECL_NAME (decl))
	{
	  bind (DECL_NAME (decl), decl, current_scope,
		/*invisible=*/خطأ, /*nested=*/خطأ,
		UNKNOWN_LOCATION);
	  إذا (!وڻ_استعمال_ٿيل (decl))
	    warn_if_shadowing (decl);
	}
      وإلا
	pedwarn_c11 (DECL_ذريعو_LOCATION (decl), OPT_Wmissing_parameter_name,
		     "ISO C does not support omitting parameter names in "
		     "function definitions before C23");
    }

  /* Record the parameter list in the function declaration.  */
  DECL_ARGUMENTS (fndecl) = arg_info->parms;

  /* Now make all the ancillary declarations visible, likewise.  */
  لكل (decl = arg_info->others; decl; decl = DECL_CHAIN (decl))
    {
      DECL_CONTEXT (decl) = current_function_decl;
      إذا (DECL_NAME (decl))
	bind (DECL_NAME (decl), decl, current_scope,
	      /*invisible=*/خطأ,
	      /*nested=*/(وڻ_ڪوڊ (decl) == FUNCTION_DECL),
	      UNKNOWN_LOCATION);
    }

  /* And all the tag declarations.  */
  FOR_EACH_VEC_محفوظ_ELT_ابتو (arg_info->ٽيگ_فهرست, ix, ٽيگ)
    إذا (ٽيگ->id)
      bind (ٽيگ->id, ٽيگ->type, current_scope,
	    /*invisible=*/خطأ, /*nested=*/خطأ, UNKNOWN_LOCATION);
}

/* Subroutine of store_parm_decls which handles old-style function
   definitions (separate parameter list and declarations).  */

ساكن فراغ
store_parm_decls_oldstyle (وڻ fndecl, ثابت بنية c_arg_info *arg_info)
{
  بنية c_binding *b;
  وڻ parm, decl, آخري;
  وڻ parmids = arg_info->parms;
  hash_سيٽ<وڻ> ڏٺل_دليلون;

  إذا (!اندريون_system_سرو_at (داخلا_location))
    {
      إذا (flag_isoc23)
	pedwarn (DECL_ذريعو_LOCATION (fndecl),
		 OPT_Wold_style_definition, "old-style function definition");
      وإلا
	warning_at (DECL_ذريعو_LOCATION (fndecl),
		    OPT_Wold_style_definition,
		    "old-style function definition");
    }

  إذا (current_scope->had_vla_unspec)
    error ("%<[*]%> not allowed in other than function prototype scope");

  /* Match each formal parameter name with its declaration.  Save each
     decl in the appropriate TREE_PURPOSE slot of the parmids chain.  */
  لكل (parm = parmids; parm; parm = وڻ_CHAIN (parm))
    {
      إذا (وڻ_قدر (parm) == NULL_وڻ)
	{
	  error_at (DECL_ذريعو_LOCATION (fndecl),
		    "parameter name missing from parameter list");
	  وڻ_PURPOSE (parm) = NULL_وڻ;
	  استمر;
	}

      b = I_نشان_BINDING (وڻ_قدر (parm));
      إذا (b && B_اندريون_CURRENT_SCOPE (b))
	{
	  decl = b->decl;
	  /* Skip erroneous parameters.  */
	  إذا (decl == error_mark_ڳنڍ)
	    استمر;
	  /* If we got something other than a PARM_DECL it is an error.  */
	  إذا (وڻ_ڪوڊ (decl) != PARM_DECL)
	    {
	      error_at (DECL_ذريعو_LOCATION (decl),
			"%qD declared as a non-parameter", decl);
	      استمر;
	    }
	  /* If the declaration is already marked, we have a duplicate
	     name.  Complain and ignore the duplicate.  */
	  وإلا إذا (ڏٺل_دليلون.شامل_آهي (decl))
	    {
	      error_at (DECL_ذريعو_LOCATION (decl),
			"multiple parameters named %qD", decl);
	      وڻ_PURPOSE (parm) = NULL_وڻ;
	      استمر;
	    }
	  /* If the declaration says "void", complain and turn it into
	     an int.  */
	  وإلا إذا (VOID_TYPE_P (وڻ_TYPE (decl)))
	    {
	      error_at (DECL_ذريعو_LOCATION (decl),
			"parameter %qD declared with void type", decl);
	      وڻ_TYPE (decl) = integer_type_ڳنڍ;
	      DECL_ARG_TYPE (decl) = integer_type_ڳنڍ;
	      layout_decl (decl, 0);
	    }
	  warn_if_shadowing (decl);
	}
      /* If no declaration found, default to int.  */
      وإلا
	{
	  /* FIXME diagnostics: This should be the location of the argument,
	     not the FNDECL.  E.g., for an old-style declaration

	       int f10(v) { blah; }

	     We should use the location of the V, not the F10.
	     Unfortunately, the V is an IDENTIFIER_NODE which has no
	     location.  In the future we need locations for c_arg_info
	     entries.

	     See gcc.dg/Wshadow-3.c for an example of this problem. */
	  decl = build_decl (DECL_ذريعو_LOCATION (fndecl),
			     PARM_DECL, وڻ_قدر (parm), integer_type_ڳنڍ);
	  DECL_ARG_TYPE (decl) = وڻ_TYPE (decl);
	  pushdecl (decl);
	  warn_if_shadowing (decl);

	  إذا (flag_isoc99)
	    permerror_opt (DECL_ذريعو_LOCATION (decl),
			   OPT_Wimplicit_int, "type of %qD defaults to %<int%>",
			   decl);
	  وإلا
	    warning_at (DECL_ذريعو_LOCATION (decl),
			OPT_Wmissing_parameter_type,
			"type of %qD defaults to %<int%>", decl);
	}

      وڻ_PURPOSE (parm) = decl;
      ڏٺل_دليلون.جوڙيو (decl);
    }

  /* Now examine the parms chain for incomplete declarations
     and declarations with no corresponding names.  */

  لكل (b = current_scope->bindings; b; b = b->prev)
    {
      parm = b->decl;
      إذا (وڻ_ڪوڊ (parm) != PARM_DECL)
	استمر;

      إذا (وڻ_TYPE (parm) != error_mark_ڳنڍ
	  && !COMPLETE_TYPE_P (وڻ_TYPE (parm)))
	{
	  error_at (DECL_ذريعو_LOCATION (parm),
		    "parameter %qD has incomplete type", parm);
	  وڻ_TYPE (parm) = error_mark_ڳنڍ;
	}

      إذا (!ڏٺل_دليلون.شامل_آهي (parm))
	{
	  error_at (DECL_ذريعو_LOCATION (parm),
		    "declaration for parameter %qD but no such parameter",
		    parm);

	  /* Pretend the parameter was not missing.
	     This gets us to a standard state and minimizes
	     further error messages.  */
	  parmids = chainon (parmids, وڻ_cons (parm, 0, 0));
	}
    }

  /* Chain the declarations together in the order of the list of
     names.  Store that chain in the function decl, replacing the
     list of names.  Update the current scope to match.  */
  DECL_ARGUMENTS (fndecl) = NULL_وڻ;

  لكل (parm = parmids; parm; parm = وڻ_CHAIN (parm))
    إذا (وڻ_PURPOSE (parm))
      اكسر;
  إذا (parm && وڻ_PURPOSE (parm))
    {
      آخري = وڻ_PURPOSE (parm);
      DECL_ARGUMENTS (fndecl) = آخري;

      لكل (parm = وڻ_CHAIN (parm); parm; parm = وڻ_CHAIN (parm))
	إذا (وڻ_PURPOSE (parm))
	  {
	    DECL_CHAIN (آخري) = وڻ_PURPOSE (parm);
	    آخري = وڻ_PURPOSE (parm);
	  }
      DECL_CHAIN (آخري) = NULL_وڻ;
    }

  /* If there was a previous prototype,
     set the DECL_ARG_TYPE of each argument according to
     the type previously specified, and report any mismatches.  */

  إذا (current_function_prototype_arg_types)
    {
      وڻ type;
      لكل (parm = DECL_ARGUMENTS (fndecl),
	     type = current_function_prototype_arg_types;
	   parm || (type != NULL_وڻ
		    && وڻ_قدر (type) != error_mark_ڳنڍ
		    && TYPE_MAIN_VARIANT (وڻ_قدر (type)) != void_type_ڳنڍ);
	   parm = DECL_CHAIN (parm), type = وڻ_CHAIN (type))
	{
	  إذا (parm == NULL_وڻ
	      || type == NULL_وڻ
	      || (وڻ_قدر (type) != error_mark_ڳنڍ
		  && TYPE_MAIN_VARIANT (وڻ_قدر (type)) == void_type_ڳنڍ))
	    {
	      إذا (current_function_prototype_built_اندريون)
		warning_at (DECL_ذريعو_LOCATION (fndecl),
			    0, "number of arguments doesn%'t match "
			    "built-in prototype");
	      وإلا
		{
		  /* FIXME diagnostics: This should be the location of
		     FNDECL, but there is bug when a prototype is
		     declared inside function context, but defined
		     outside of it (e.g., gcc.dg/pr15698-2.c).  In
		     which case FNDECL gets the location of the
		     prototype, not the definition.  */
		  error_at (داخلا_location,
			    "number of arguments doesn%'t match prototype");

		  error_at (current_function_prototype_locus,
			    "prototype declaration");
		}
	      اكسر;
	    }
	  /* Type for passing arg must be consistent with that
	     declared for the arg.  ISO C says we take the unqualified
	     type for parameters declared with qualified type.  */
	  إذا (وڻ_TYPE (parm) != error_mark_ڳنڍ
	      && وڻ_قدر (type) != error_mark_ڳنڍ
	      && ((TYPE_ATOMIC (DECL_ARG_TYPE (parm))
		   != TYPE_ATOMIC (وڻ_قدر (type)))
		  || !comptypes (TYPE_MAIN_VARIANT (DECL_ARG_TYPE (parm)),
				 TYPE_MAIN_VARIANT (وڻ_قدر (type)))))
	    {
	      إذا ((TYPE_ATOMIC (DECL_ARG_TYPE (parm))
		   == TYPE_ATOMIC (وڻ_قدر (type)))
		  && (TYPE_MAIN_VARIANT (وڻ_TYPE (parm))
		      == TYPE_MAIN_VARIANT (وڻ_قدر (type))))
		{
		  /* Adjust argument to match prototype.  E.g. a previous
		     `int foo(float);' prototype causes
		     `int foo(x) float x; {...}' to be treated like
		     `int foo(float x) {...}'.  This is particularly
		     useful for argument types like uid_t.  */
		  DECL_ARG_TYPE (parm) = وڻ_TYPE (parm);

		  /* ??? Is it possible to get here with a
		     built-in prototype or will it always have
		     been diagnosed as conflicting with an
		     old-style definition and discarded?  */
		  إذا (current_function_prototype_built_اندريون)
		    warning_at (DECL_ذريعو_LOCATION (parm),
				OPT_Wpedantic, "promoted argument %qD "
				"doesn%'t match built-in prototype", parm);
		  وإلا
		    {
		      pedwarn (DECL_ذريعو_LOCATION (parm),
			       OPT_Wpedantic, "promoted argument %qD "
			       "doesn%'t match prototype", parm);
		      pedwarn (current_function_prototype_locus, OPT_Wpedantic,
			       "prototype declaration");
		    }
		}
	      وإلا
		{
		  إذا (current_function_prototype_built_اندريون)
		    warning_at (DECL_ذريعو_LOCATION (parm),
				0, "argument %qD doesn%'t match "
				"built-in prototype", parm);
		  وإلا
		    {
		      error_at (DECL_ذريعو_LOCATION (parm),
				"argument %qD doesn%'t match prototype", parm);
		      error_at (current_function_prototype_locus,
				"prototype declaration");
		    }
		}
	    }
	}
      TYPE_ACTUAL_ARG_TYPES (وڻ_TYPE (fndecl)) = NULL_وڻ;
    }

  /* Otherwise, create a prototype that would match.  */

  وإلا
    {
      وڻ actual = NULL_وڻ, آخري = NULL_وڻ, type;

      لكل (parm = DECL_ARGUMENTS (fndecl); parm; parm = DECL_CHAIN (parm))
	{
	  type = وڻ_cons (NULL_وڻ, DECL_ARG_TYPE (parm), NULL_وڻ);
	  إذا (آخري)
	    وڻ_CHAIN (آخري) = type;
	  وإلا
	    actual = type;
	  آخري = type;
	}
      type = وڻ_cons (NULL_وڻ, void_type_ڳنڍ, NULL_وڻ);
      إذا (آخري)
	وڻ_CHAIN (آخري) = type;
      وإلا
	actual = type;

      /* We are going to assign a new value for the TYPE_ACTUAL_ARG_TYPES
	 of the type of this function, but we need to avoid having this
	 affect the types of other similarly-typed functions, so we must
	 first force the generation of an identical (but separate) type
	 node for the relevant function type.  The new node we create
	 will be a variant of the main variant of the original function
	 type.  */

      وڻ_TYPE (fndecl) = build_variant_type_copy (وڻ_TYPE (fndecl));

      TYPE_ACTUAL_ARG_TYPES (وڻ_TYPE (fndecl)) = actual;
    }
}

/* Store parameter declarations passed in ARG_INFO into the current
   function declaration.  */

فراغ
store_parm_decls_from (بنية c_arg_info *arg_info)
{
  current_function_arg_info = arg_info;
  store_parm_decls ();
}

/* Called by walk_tree to look for and update context-less labels
   or labels with context in the parent function.  */

ساكن وڻ
سيٽ_labels_context_r (وڻ *tp, صحيح *walk_subtrees, فراغ *معلومات)
{
  وڻ ctx = static_cast<وڻ>(معلومات);
  إذا (وڻ_ڪوڊ (*tp) == LABEL_اظهار
      && (DECL_CONTEXT (LABEL_اظهار_LABEL (*tp)) == NULL_وڻ
	  || DECL_CONTEXT (LABEL_اظهار_LABEL (*tp)) == DECL_CONTEXT (ctx)))
    {
      DECL_CONTEXT (LABEL_اظهار_LABEL (*tp)) = ctx;
      *walk_subtrees = 0;
    }

  أرجع NULL_وڻ;
}

/* Store the parameter declarations into the current function declaration.
   This is called after parsing the parameter declarations, before
   digesting the body of the function.

   For an old-style definition, construct a prototype out of the old-style
   parameter declarations and inject it into the function's type.  */

فراغ
store_parm_decls (فراغ)
{
  وڻ fndecl = current_function_decl;
  منطقي proto;

  /* The argument information block for FNDECL.  */
  بنية c_arg_info *arg_info = current_function_arg_info;
  current_function_arg_info = 0;

  /* True if this definition is written with a prototype.  In C23, an
     empty argument list was converted to (void) in grokparms; in
     older C standard versions, it does not give the function a type
     with a prototype for future calls.  */
  proto = arg_info->types != 0 || arg_info->no_named_دليلون_stdarg_p;

  إذا (proto)
    store_parm_decls_newstyle (fndecl, arg_info);
  وإلا
    store_parm_decls_oldstyle (fndecl, arg_info);

  /* The next call to push_scope will be a function body.  */

  ايندڙ_is_function_body = سچ;

  /* Write a record describing this function definition to the prototypes
     file (if requested).  */

  gen_aux_info_رڪارڊ (fndecl, 1, 0, proto);

  /* Initialize the RTL code for the function.  */
  allocate_struct_function (fndecl, خطأ);

  إذا (warn_اڻ_استعمال_ٿيل_local_typedefs)
    cfun->language = ggc_cleared_alloc<language_function> ();

  /* Begin the statement tree for this function.  */
  DECL_SAVED_وڻ (fndecl) = ڌڪو_stmt_list ();

  /* ??? Insert the contents of the pending sizes list into the function
     to be evaluated.  The only reason left to have this is
	void foo(int n, int array[n++])
     because we throw away the array type in favor of a pointer type, and
     thus won't naturally see the SAVE_EXPR containing the increment.  All
     other pending sizes would be handled by gimplify_parameters.  */
  إذا (arg_info->pending_sizes)
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
      walk_وڻ_without_duplicates (&arg_info->pending_sizes,
				    سيٽ_labels_context_r, fndecl);
      جوڙيو_stmt (arg_info->pending_sizes);
    }
}

/* Store PARM_DECLs in PARMS into scope temporarily.  Used for
   c_finish_omp_declare_simd for function prototypes.  No diagnostics
   should be done.  */

فراغ
عارضي_store_parm_decls (وڻ fndecl, وڻ parms)
{
  ڌڪو_scope ();
  لكل (وڻ p = parms; p; p = DECL_CHAIN (p))
    {
      DECL_CONTEXT (p) = fndecl;
      إذا (DECL_NAME (p))
	bind (DECL_NAME (p), p, current_scope,
	      /*invisible=*/خطأ, /*nested=*/خطأ,
	      UNKNOWN_LOCATION);
    }
}

/* Undo what temp_store_parm_decls did.  */

فراغ
عارضي_ڪڍو_parm_decls (فراغ)
{
  /* Clear all bindings in this temporary scope, so that
     pop_scope doesn't create a BLOCK.  */
  بنية c_binding *b = current_scope->bindings;
  current_scope->bindings = عدم;
  لكل (; b; b = free_binding_and_advance (b))
    {
      gcc_assert (وڻ_ڪوڊ (b->decl) == PARM_DECL
		  || b->decl == error_mark_ڳنڍ);
      gcc_assert (I_نشان_BINDING (b->id) == b);
      I_نشان_BINDING (b->id) = b->shadowed;
      إذا (b->shadowed && b->shadowed->u.type)
	وڻ_TYPE (b->shadowed->decl) = b->shadowed->u.type;
    }
  ڪڍو_scope ();
}


/* Finish up a function declaration and compile that function
   all the way to assembler language output.  Then free the storage
   for the function definition.

   This is called after parsing the body of the function definition.  */

فراغ
پڄاڻي_function (location_t پڇاڙي_loc)
{
  وڻ fndecl = current_function_decl;

  إذا (c_dialect_objc ())
    objc_پڄاڻي_function ();

  إذا (DECL_INITIAL (fndecl) && DECL_INITIAL (fndecl) != error_mark_ڳنڍ)
    بلاڪ_SUPERCONTEXT (DECL_INITIAL (fndecl)) = fndecl;

  /* Must mark the RESULT_DECL as being in this function.  */

  إذا (DECL_نتيجو (fndecl) && DECL_نتيجو (fndecl) != error_mark_ڳنڍ)
    DECL_CONTEXT (DECL_نتيجو (fndecl)) = fndecl;

  إذا (MAIN_NAME_P (DECL_NAME (fndecl)) && !وڻ_THIS_VOLATILE (fndecl)
      && TYPE_MAIN_VARIANT (وڻ_TYPE (وڻ_TYPE (fndecl)))
      == integer_type_ڳنڍ && flag_isoc99)
    {
      /* Hack.  We don't want the middle-end to warn that this return
	 is unreachable, so we mark its location as special.  Using
	 UNKNOWN_LOCATION has the problem that it gets clobbered in
	 annotate_one_with_locus.  A cleaner solution might be to
	 ensure ! should_carry_locus_p (stmt), but that needs a flag.
      */
      c_پڄاڻي_return (BUILTINS_LOCATION, integer_zero_ڳنڍ, NULL_وڻ);
    }

  /* Tie off the statement tree for this function.  */
  DECL_SAVED_وڻ (fndecl) = ڪڍو_stmt_list (DECL_SAVED_وڻ (fndecl));

  پڄاڻي_fname_decls ();

  /* Complain if there's no return statement only if option specified on
     command line.  */
  إذا (warn_return_type > 0
      && وڻ_ڪوڊ (وڻ_TYPE (وڻ_TYPE (fndecl))) != VOID_TYPE
      && !current_function_returns_قدر && !current_function_returns_null
      /* Don't complain if we are no-return.  */
      && !current_function_returns_abnormally
      /* Don't complain if we are declared noreturn.  */
      && !وڻ_THIS_VOLATILE (fndecl)
      /* Don't warn for main().  */
      && !MAIN_NAME_P (DECL_NAME (fndecl))
      /* Or if they didn't actually specify a return type.  */
      && !C_FUNCTION_IMPLICIT_INT (fndecl)
      /* Normally, with -Wreturn-type, flow will complain, but we might
         optimize out static functions.  */
      && !وڻ_عوامي (fndecl)
      && targetm.warn_func_return (fndecl)
      && warning (OPT_Wreturn_type,
		  "no return statement in function returning non-void"))
    suppress_warning (fndecl, OPT_Wreturn_type);

  /* Complain about parameters that are only set, but never otherwise used.  */
  إذا (warn_اڻ_استعمال_ٿيل_but_سيٽ_parameter)
    {
      وڻ decl;

      لكل (decl = DECL_ARGUMENTS (fndecl);
	   decl;
	   decl = DECL_CHAIN (decl))
	إذا (وڻ_استعمال_ٿيل (decl)
	    && وڻ_ڪوڊ (decl) == PARM_DECL
	    && !DECL_READ_P (decl)
	    && DECL_NAME (decl)
	    && !DECL_ARTIFICIAL (decl)
	    && !warning_suppressed_p (decl, OPT_Wunused_but_سيٽ_parameter))
	  warning_at (DECL_ذريعو_LOCATION (decl),
		      OPT_Wunused_but_سيٽ_parameter,
		      "parameter %qD set but not used", decl);
    }

  /* Complain about locally defined typedefs that are not used in this
     function.  */
  maybe_warn_اڻ_استعمال_ٿيل_local_typedefs ();

  /* Possibly warn about unused parameters.  */
  إذا (warn_اڻ_استعمال_ٿيل_parameter)
    do_warn_اڻ_استعمال_ٿيل_parameter (fndecl);

  /* Store the end of the function, so that we get good line number
     info for the epilogue.  */
  cfun->function_پڇاڙي_locus = پڇاڙي_loc;

  /* Finalize the ELF visibility for the function.  */
  c_determine_visibility (fndecl);

  /* For GNU C extern inline functions disregard inline limits.  */
  إذا (DECL_EXTERNAL (fndecl)
      && DECL_DECLARED_INLINE_P (fndecl)
      && (flag_gnu89_inline
	  || lookup_attribute ("gnu_inline", DECL_خاصيتون (fndecl))))
    DECL_DISREGARD_INLINE_LIMITS (fndecl) = 1;

  /* Genericize before inlining.  Delay genericizing nested functions
     until their parent function is genericized.  Since finalizing
     requires GENERIC, delay that as well.  */

  إذا (DECL_INITIAL (fndecl) && DECL_INITIAL (fndecl) != error_mark_ڳنڍ
      && !undef_nested_function)
    {
      إذا (!decl_function_context (fndecl))
	{
	  invoke_plugin_callbacks (PLUGIN_PRE_GENERICIZE, fndecl);
	  c_genericize (fndecl);

	  /* ??? Objc emits functions after finalizing the compilation unit.
	     This should be cleaned up later and this conditional removed.  */
	  إذا (symtab->global_info_ready)
	    {
	      cgraph_ڳنڍ::جوڙيو_new_function (fndecl, خطأ);
	      أرجع;
	    }
	  cgraph_ڳنڍ::finalize_function (fndecl, خطأ);
	}
      وإلا
	{
	  /* Register this function with cgraph just far enough to get it
	    added to our parent's nested function list.  Handy, since the
	    C front end doesn't have such a list.  */
	  (فراغ) cgraph_ڳنڍ::get_create (fndecl);
	}
    }

  إذا (!decl_function_context (fndecl))
    undef_nested_function = خطأ;

  إذا (cfun->language != عدم)
    {
      ggc_free (cfun->language);
      cfun->language = عدم;
    }

  /* We're leaving the context of this function, so zap cfun.
     It's still in DECL_STRUCT_FUNCTION, and we'll restore it in
     tree_rest_of_compilation.  */
  سيٽ_cfun (عدم);
  invoke_plugin_callbacks (PLUGIN_پڄاڻي_PARSE_FUNCTION, current_function_decl);
  current_function_decl = عدم;
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

وڻ
check_for_loop_decls (location_t loc, منطقي turn_off_iso_c99_error)
{
  بنية c_binding *b;
  وڻ one_decl = NULL_وڻ;
  صحيح n_decls = 0;

  إذا (!turn_off_iso_c99_error)
    {
      ساكن منطقي hint = سچ;
      /* If we get here, declarations have been used in a for loop without
	 the C99 for loop scope.  This doesn't make much sense, so don't
	 allow it.  */
      auto_diagnostic_گروهه d;
      error_at (loc, "%<for%> loop initial declarations "
		"are only allowed in C99 or C11 mode");
      إذا (hint)
	{
	  inform (loc,
		  "use option %<-std=c99%>, %<-std=gnu99%>, %<-std=c11%> or "
		  "%<-std=gnu11%> to compile your code");
	  hint = خطأ;
	}
      أرجع NULL_وڻ;
    }
  وإلا
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

  لكل (b = current_scope->bindings; b; b = b->prev)
    {
      وڻ id = b->id;
      وڻ decl = b->decl;

      إذا (!id)
	استمر;

      بدل (وڻ_ڪوڊ (decl))
	{
	حالة VAR_DECL:
	  {
	    location_t decl_loc = DECL_ذريعو_LOCATION (decl);
	    إذا (وڻ_STATIC (decl))
	      pedwarn_c11 (decl_loc, OPT_Wpedantic,
			   "declaration of static variable %qD in %<for%> "
			   "loop initial declaration", decl);
	    وإلا إذا (DECL_EXTERNAL (decl))
	      pedwarn_c11 (decl_loc, OPT_Wpedantic,
			   "declaration of %<extern%> variable %qD in %<for%> "
			   "loop initial declaration", decl);
	  }
	  اكسر;

	حالة رڪارڊ_TYPE:
	  pedwarn_c11 (loc, OPT_Wpedantic,
		       "%<struct %E%> declared in %<for%> loop initial "
		       "declaration", id);
	  اكسر;
	حالة UNION_TYPE:
	  pedwarn_c11 (loc, OPT_Wpedantic,
		       "%<union %E%> declared in %<for%> loop initial "
		       "declaration",
		       id);
	  اكسر;
	حالة ENUMERAL_TYPE:
	  pedwarn_c11 (loc, OPT_Wpedantic,
		       "%<enum %E%> declared in %<for%> loop "
		       "initial declaration", id);
	  اكسر;
	افتراضي:
	  pedwarn_c11 (loc, OPT_Wpedantic, "declaration of non-variable "
		       "%qD in %<for%> loop initial declaration", decl);
	}

      n_decls++;
      one_decl = decl;
    }

  أرجع n_decls == 1 ? one_decl : NULL_وڻ;
}

/* Save and reinitialize the variables
   used during compilation of a C function.  */

فراغ
c_ڌڪو_function_context (فراغ)
{
  بنية language_function *p = cfun->language;
  /* cfun->language might have been already allocated by the use of
     -Wunused-local-typedefs.  In that case, just re-use it.  */
  إذا (p == عدم)
    cfun->language = p = ggc_cleared_alloc<language_function> ();

  p->بنياد.x_stmt_وڻ = c_stmt_وڻ;
  c_stmt_وڻ.x_cur_stmt_list = vec_محفوظ_copy (c_stmt_وڻ.x_cur_stmt_list);
  p->x_اندريون_statement = اندريون_statement;
  p->x_switch_ڍير = c_switch_ڍير;
  p->loop_نالا = loop_نالا;
  loop_نالا = vNULL;
  p->loop_نالا_hash = loop_نالا_hash;
  loop_نالا_hash = عدم;
  p->arg_info = current_function_arg_info;
  p->returns_قدر = current_function_returns_قدر;
  p->returns_null = current_function_returns_null;
  p->returns_abnormally = current_function_returns_abnormally;
  p->warn_about_return_type = warn_about_return_type;

  ڌڪو_function_context ();
}

/* Restore the variables used during compilation of a C function.  */

فراغ
c_ڪڍو_function_context (فراغ)
{
  بنية language_function *p;

  ڪڍو_function_context ();
  p = cfun->language;

  /* When -Wunused-local-typedefs is in effect, cfun->languages is
     used to store data throughout the life time of the current cfun,
     So don't deallocate it.  */
  إذا (!warn_اڻ_استعمال_ٿيل_local_typedefs)
    cfun->language = عدم;

  إذا (DECL_STRUCT_FUNCTION (current_function_decl) == 0
      && DECL_SAVED_وڻ (current_function_decl) == NULL_وڻ)
    {
      /* Stop pointing to the local nodes about to be freed.  */
      /* But DECL_INITIAL must remain nonzero so we know this
	 was an actual function definition.  */
      DECL_INITIAL (current_function_decl) = error_mark_ڳنڍ;
      DECL_ARGUMENTS (current_function_decl) = NULL_وڻ;
    }

  c_stmt_وڻ = p->بنياد.x_stmt_وڻ;
  p->بنياد.x_stmt_وڻ.x_cur_stmt_list = عدم;
  اندريون_statement = p->x_اندريون_statement;
  c_switch_ڍير = p->x_switch_ڍير;
  loop_نالا.release ();
  loop_نالا = p->loop_نالا;
  p->loop_نالا = vNULL;
  ميٽيو loop_نالا_hash;
  loop_نالا_hash = p->loop_نالا_hash;
  p->loop_نالا_hash = عدم;
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

stmt_وڻ
current_stmt_وڻ (فراغ)
{
  أرجع &c_stmt_وڻ;
}

/* Return the global value of T as a symbol.  */

وڻ
identifier_global_قدر	(وڻ t)
{
  بنية c_binding *b;

  لكل (b = I_نشان_BINDING (t); b; b = b->shadowed)
    إذا (B_اندريون_FILE_SCOPE (b) || B_اندريون_EXTERNAL_SCOPE (b))
      أرجع b->decl;

  أرجع NULL_وڻ;
}

/* Return the global value of tag T as a symbol.  */

وڻ
identifier_global_ٽيگ (وڻ t)
{
  بنية c_binding *b;

  لكل (b = I_ٽيگ_BINDING (t); b; b = b->shadowed)
    إذا (B_اندريون_FILE_SCOPE (b) || B_اندريون_EXTERNAL_SCOPE (b))
      أرجع b->decl;

  أرجع NULL_وڻ;
}

/* Returns non-zero (result of __has_builtin) if NAME refers to a built-in
   function or function-like operator.  */

صحيح
نالا_builtin_p (ثابت حرف *name)
{
  وڻ id = get_identifier (name);
  إذا (وڻ decl = identifier_global_قدر (id))
    أرجع وڻ_ڪوڊ (decl) == FUNCTION_DECL && DECL_IS_UNDECLARED_BUILTIN (decl);

  /* Also detect common reserved C words that aren't strictly built-in
     functions.  */
  بدل (C_RID_ڪوڊ (id))
    {
    حالة RID_BUILTIN_ASSOC_BARRIER:
    حالة RID_BUILTIN_BITREVERSEG:
    حالة RID_BUILTIN_BSWAPG:
    حالة RID_BUILTIN_CONVERTVECTOR:
    حالة RID_BUILTIN_HAS_ATTRIBUTE:
    حالة RID_BUILTIN_SHUFFLE:
    حالة RID_BUILTIN_SHUFFLEVECTOR:
    حالة RID_BUILTIN_STDC:
    حالة RID_BUILTIN_COUNTED_BY_REF:
    حالة RID_چونڊيو_اظهار:
    حالة RID_OFFSETOF:
    حالة RID_TYPES_COMPATIBLE_P:
    حالة RID_C23_VA_شروعات:
    حالة RID_VA_ARG:
      أرجع 1;
    افتراضي:
      اكسر;
    }

  أرجع 0;
}

/* In C, the only C-linkage public declaration is at file scope.  */

وڻ
c_linkage_bindings (وڻ name)
{
  أرجع identifier_global_قدر (name);
}

/* Record a builtin type for C.  If NAME is non-NULL, it is the name used;
   otherwise the name is found in ridpointers from RID_INDEX.  */

فراغ
رڪارڊ_builtin_type (تعداد rid rid_اشاريو, ثابت حرف *name, وڻ type)
{
  وڻ id, decl;
  إذا (name == 0)
    id = ridpointers[(صحيح) rid_اشاريو];
  وإلا
    id = get_identifier (name);
  decl = build_decl (UNKNOWN_LOCATION, TYPE_DECL, id, type);
  pushdecl (decl);
  إذا (debug_hooks->type_decl)
    debug_hooks->type_decl (decl, خطأ);
}

/* Return a c_parm structure with the given SPECS, ATTRS and DECLARATOR.  */

بنية c_parm *
build_c_parm (بنية c_declspecs *specs, وڻ attrs,
	      بنية c_declarator *declarator,
	      location_t loc)
{
  بنية c_parm *ret = XOBNEW (&parser_obstack, بنية c_parm);
  ret->specs = specs;
  ret->attrs = attrs;
  ret->declarator = declarator;
  ret->loc = loc;
  أرجع ret;
}

/* Return a declarator with nested attributes.  TARGET is the inner
   declarator to which these attributes apply.  ATTRS are the
   attributes.  */

بنية c_declarator *
build_attrs_declarator (وڻ attrs, بنية c_declarator *هدف)
{
  بنية c_declarator *ret = XOBNEW (&parser_obstack, بنية c_declarator);
  ret->قسم = cdk_attrs;
  ret->declarator = هدف;
  ret->u.attrs = attrs;
  أرجع ret;
}

/* Return a declarator for a function with arguments specified by ARGS
   and return type specified by TARGET.  */

بنية c_declarator *
build_function_declarator (بنية c_arg_info *دليلون,
			   بنية c_declarator *هدف)
{
  بنية c_declarator *ret = XOBNEW (&parser_obstack, بنية c_declarator);
  ret->قسم = cdk_function;
  ret->declarator = هدف;
  ret->u.arg_info = دليلون;
  أرجع ret;
}

/* Return a declarator for the identifier IDENT (which may be
   NULL_TREE for an abstract declarator).  */

بنية c_declarator *
build_id_declarator (وڻ ident)
{
  بنية c_declarator *ret = XOBNEW (&parser_obstack, بنية c_declarator);
  ret->قسم = cdk_id;
  ret->declarator = 0;
  ret->u.id.id = ident;
  ret->u.id.attrs = NULL_وڻ;
  /* Default value - may get reset to a more precise location. */
  ret->id_loc = داخلا_location;
  أرجع ret;
}

/* Return something to represent absolute declarators containing a *.
   TARGET is the absolute declarator that the * contains.
   TYPE_QUALS_ATTRS is a structure for type qualifiers and attributes
   to apply to the pointer type.  */

بنية c_declarator *
make_اشارو_declarator (بنية c_declspecs *type_quals_attrs,
			 بنية c_declarator *هدف)
{
  وڻ attrs;
  صحيح quals = 0;
  بنية c_declarator *itarget = هدف;
  بنية c_declarator *ret = XOBNEW (&parser_obstack, بنية c_declarator);
  إذا (type_quals_attrs)
    {
      attrs = type_quals_attrs->attrs;
      quals = quals_from_declspecs (type_quals_attrs);
      إذا (attrs != NULL_وڻ)
	itarget = build_attrs_declarator (attrs, هدف);
    }
  ret->قسم = cdk_اشارو;
  ret->declarator = itarget;
  ret->u.اشارو_quals = quals;
  أرجع ret;
}

/* Return a pointer to a structure for an empty list of declaration
   specifiers.  */

بنية c_declspecs *
build_null_declspecs (فراغ)
{
  بنية c_declspecs *ret = XOBNEW (&parser_obstack, بنية c_declspecs);
  memset (ret, 0, حجم *ret);
  ret->align_log = -1;
  ret->typespec_لفظ = cts_none;
  ret->storage_class = csc_none;
  ret->اظهار_const_operands = سچ;
  ret->typespec_قسم = ctsk_none;
  ret->پتو_space = ADDR_SPACE_GENERIC;
  أرجع ret;
}

/* Add the address space ADDRSPACE to the declaration specifiers
   SPECS, returning SPECS.  */

بنية c_declspecs *
declspecs_جوڙيو_addrspace (location_t location,
			 بنية c_declspecs *specs, addr_space_t as)
{
  specs->non_sc_ڏٺل_p = سچ;
  specs->declspecs_ڏٺل_p = سچ;
  specs->non_std_attrs_ڏٺل_p = سچ;

  إذا (!ADDR_SPACE_GENERIC_P (specs->پتو_space)
      && specs->پتو_space != as)
    error ("incompatible address space qualifiers %qs and %qs",
	   c_addr_space_name (as),
	   c_addr_space_name (specs->پتو_space));
  وإلا
    {
      specs->پتو_space = as;
      specs->locations[cdw_پتو_space] = location;
    }
  أرجع specs;
}

/* Add the type qualifier QUAL to the declaration specifiers SPECS,
   returning SPECS.  */

بنية c_declspecs *
declspecs_جوڙيو_qual (location_t loc,
		    بنية c_declspecs *specs, وڻ qual)
{
  تعداد rid i;
  منطقي dupe = خطأ;
  specs->non_sc_ڏٺل_p = سچ;
  specs->declspecs_ڏٺل_p = سچ;
  specs->non_std_attrs_ڏٺل_p = سچ;
  gcc_assert (وڻ_ڪوڊ (qual) == IDENTIFIER_ڳنڍ
	      && C_IS_RESERVED_لفظ (qual));
  i = C_RID_ڪوڊ (qual);
  location_t prev_loc = UNKNOWN_LOCATION;
  بدل (i)
    {
    حالة RID_CONST:
      dupe = specs->const_p;
      specs->const_p = سچ;
      prev_loc = specs->locations[cdw_const];
      specs->locations[cdw_const] = loc;
      اكسر;
    حالة RID_VOLATILE:
      dupe = specs->volatile_p;
      specs->volatile_p = سچ;
      prev_loc = specs->locations[cdw_volatile];
      specs->locations[cdw_volatile] = loc;
      اكسر;
    حالة RID_RESTRICT:
      dupe = specs->restrict_p;
      specs->restrict_p = سچ;
      prev_loc = specs->locations[cdw_restrict];
      specs->locations[cdw_restrict] = loc;
      اكسر;
    حالة RID_ATOMIC:
      dupe = specs->atomic_p;
      specs->atomic_p = سچ;
      prev_loc = specs->locations[cdw_atomic];
      specs->locations[cdw_atomic] = loc;
      اكسر;
    افتراضي:
      gcc_unreachable ();
    }
  إذا (dupe)
    {
      منطقي warned = pedwarn_c90 (loc, OPT_Wpedantic,
				 "duplicate %qE declaration specifier", qual);
      إذا (!warned
	  && warn_duplicate_decl_specifier
	  && prev_loc >= RESERVED_LOCATION_ڳڻپ
	  && !from_macro_expansion_at (prev_loc)
	  && !from_macro_expansion_at (loc))
	warning_at (loc, OPT_Wduplicate_decl_specifier,
		    "duplicate %qE declaration specifier", qual);
    }
  أرجع specs;
}

/* Add the type specifier TYPE to the declaration specifiers SPECS,
   returning SPECS.  */

بنية c_declspecs *
declspecs_جوڙيو_type (location_t loc, بنية c_declspecs *specs,
		    بنية c_typespec spec)
{
  وڻ type = spec.spec;
  specs->non_sc_ڏٺل_p = سچ;
  specs->declspecs_ڏٺل_p = سچ;
  specs->non_std_attrs_ڏٺل_p = سچ;
  specs->typespec_قسم = spec.قسم;
  إذا (وڻ_DEPRECATED (type))
    specs->deprecated_p = سچ;
  إذا (وڻ_UNAVAILABLE (type))
    specs->unavailable_p = سچ;

  /* As a type specifier is present, "auto" must be used as a storage
     class specifier, not for type deduction.  */
  إذا (specs->c23_auto_p)
    {
      specs->c23_auto_p = خطأ;
      إذا (specs->storage_class != csc_none)
	error ("multiple storage classes in declaration specifiers");
      وإلا إذا (specs->thread_p)
	error ("%qs used with %<auto%>",
	       specs->thread_gnu_p ? "__thread" : "_Thread_local");
      وإلا إذا (specs->constexpr_p)
	/* auto may only be used with another storage class specifier,
	   such as constexpr, if the type is inferred.  */
	error ("%<auto%> used with %<constexpr%>");
      وإلا
	specs->storage_class = csc_auto;
    }

  /* Handle type specifier keywords.  */
  إذا (وڻ_ڪوڊ (type) == IDENTIFIER_ڳنڍ
      && C_IS_RESERVED_لفظ (type)
      && C_RID_ڪوڊ (type) != RID_CXX_COMPAT_WARN)
    {
      تعداد rid i = C_RID_ڪوڊ (type);
      إذا (specs->type)
	{
	  error_at (loc, "two or more data types in declaration specifiers");
	  أرجع specs;
	}
      إذا ((صحيح) i <= (صحيح) RID_آخري_MODIFIER)
	{
	  /* "long", "short", "signed", "unsigned", "_Complex" or "_Sat".  */
	  منطقي dupe = خطأ;
	  بدل (i)
	    {
	    حالة RID_LONG:
	      إذا (specs->long_long_p)
		{
		  error_at (loc, "%<long long long%> is too long for GCC");
		  اكسر;
		}
	      إذا (specs->long_p)
		{
		  إذا (specs->typespec_لفظ == cts_double)
		    {
		      error_at (loc,
				"both %qs and %qs in declaration specifiers",
				"long long", "double");
		      اكسر;
		    }
		  pedwarn_c90 (loc, OPT_Wlong_long,
			       "ISO C90 does not support %<long long%>");
		  specs->long_long_p = 1;
		  specs->locations[cdw_long_long] = loc;
		  اكسر;
		}
	      إذا (specs->short_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "short");
	      وإلا إذا (specs->typespec_لفظ == cts_auto_type)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "__auto_type");
	      وإلا إذا (specs->typespec_لفظ == cts_void)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "void");
	      وإلا إذا (specs->typespec_لفظ == cts_int_n)
		error_at (loc,
			  "both %qs and %<__int%d%> in declaration specifiers",
			  "long", int_n_معلومات[specs->u.int_n_idx].bitsize);
	      وإلا إذا (specs->typespec_لفظ == cts_bool)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "_Bool");
	      وإلا إذا (specs->typespec_لفظ == cts_bitint)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "_BitInt");
	      وإلا إذا (specs->typespec_لفظ == cts_char)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "char");
	      وإلا إذا (specs->typespec_لفظ == cts_float)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "float");
	      وإلا إذا (specs->typespec_لفظ == cts_floatn_nx)
		error_at (loc,
			  "both %qs and %<_Float%d%s%> in declaration "
			  "specifiers", "long",
			  floatn_nx_types[specs->u.floatn_nx_idx].n,
			  floatn_nx_types[specs->u.floatn_nx_idx].extended
			  ? "x"
			  : "");
	      وإلا إذا (specs->typespec_لفظ == cts_dfloat32)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "_Decimal32");
	      وإلا إذا (specs->typespec_لفظ == cts_dfloat64)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "_Decimal64");
	      وإلا إذا (specs->typespec_لفظ == cts_dfloat128)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "_Decimal128");
	      وإلا إذا (specs->typespec_لفظ == cts_dfloat64x)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "_Decimal64x");
	      وإلا
		{
		  specs->long_p = سچ;
		  specs->locations[cdw_long] = loc;
		}
	      اكسر;
	    حالة RID_SHORT:
	      dupe = specs->short_p;
	      إذا (specs->long_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "short");
	      وإلا إذا (specs->typespec_لفظ == cts_auto_type)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "__auto_type");
	      وإلا إذا (specs->typespec_لفظ == cts_void)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "void");
	      وإلا إذا (specs->typespec_لفظ == cts_int_n)
		error_at (loc,
			  "both %qs and %<__int%d%> in declaration specifiers",
			  "short", int_n_معلومات[specs->u.int_n_idx].bitsize);
	      وإلا إذا (specs->typespec_لفظ == cts_bool)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "_Bool");
	      وإلا إذا (specs->typespec_لفظ == cts_bitint)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "_BitInt");
	      وإلا إذا (specs->typespec_لفظ == cts_char)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "char");
	      وإلا إذا (specs->typespec_لفظ == cts_float)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "float");
	      وإلا إذا (specs->typespec_لفظ == cts_double)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "double");
	      وإلا إذا (specs->typespec_لفظ == cts_floatn_nx)
		error_at (loc,
			  "both %qs and %<_Float%d%s%> in declaration "
			  "specifiers", "short",
			  floatn_nx_types[specs->u.floatn_nx_idx].n,
			  floatn_nx_types[specs->u.floatn_nx_idx].extended
			  ? "x"
			  : "");
	      وإلا إذا (specs->typespec_لفظ == cts_dfloat32)
                error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "_Decimal32");
	      وإلا إذا (specs->typespec_لفظ == cts_dfloat64)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "_Decimal64");
	      وإلا إذا (specs->typespec_لفظ == cts_dfloat128)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "_Decimal128");
	      وإلا إذا (specs->typespec_لفظ == cts_dfloat64x)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "_Decimal64x");
	      وإلا
		{
		  specs->short_p = سچ;
		  specs->locations[cdw_short] = loc;
		}
	      اكسر;
	    حالة RID_SIGNED:
	      dupe = specs->signed_p;
	      إذا (specs->unsigned_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "unsigned");
	      وإلا إذا (specs->typespec_لفظ == cts_auto_type)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "__auto_type");
	      وإلا إذا (specs->typespec_لفظ == cts_void)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "void");
	      وإلا إذا (specs->typespec_لفظ == cts_bool)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "_Bool");
	      وإلا إذا (specs->typespec_لفظ == cts_float)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "float");
	      وإلا إذا (specs->typespec_لفظ == cts_double)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "double");
	      وإلا إذا (specs->typespec_لفظ == cts_floatn_nx)
		error_at (loc,
			  "both %qs and %<_Float%d%s%> in declaration "
			  "specifiers", "signed",
			  floatn_nx_types[specs->u.floatn_nx_idx].n,
			  floatn_nx_types[specs->u.floatn_nx_idx].extended
			  ? "x"
			  : "");
	      وإلا إذا (specs->typespec_لفظ == cts_dfloat32)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "_Decimal32");
	      وإلا إذا (specs->typespec_لفظ == cts_dfloat64)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "_Decimal64");
	      وإلا إذا (specs->typespec_لفظ == cts_dfloat128)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "_Decimal128");
	      وإلا إذا (specs->typespec_لفظ == cts_dfloat64x)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "_Decimal64x");
	      وإلا
		{
		  specs->signed_p = سچ;
		  specs->locations[cdw_signed] = loc;
		}
	      اكسر;
	    حالة RID_UNSIGNED:
	      dupe = specs->unsigned_p;
	      إذا (specs->signed_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "unsigned");
	      وإلا إذا (specs->typespec_لفظ == cts_auto_type)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "__auto_type");
	      وإلا إذا (specs->typespec_لفظ == cts_void)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "void");
	      وإلا إذا (specs->typespec_لفظ == cts_bool)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "_Bool");
	      وإلا إذا (specs->typespec_لفظ == cts_float)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "float");
	      وإلا إذا (specs->typespec_لفظ == cts_double)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "double");
	      وإلا إذا (specs->typespec_لفظ == cts_floatn_nx)
		error_at (loc,
			  "both %qs and %<_Float%d%s%> in declaration "
			  "specifiers", "unsigned",
			  floatn_nx_types[specs->u.floatn_nx_idx].n,
			  floatn_nx_types[specs->u.floatn_nx_idx].extended
			  ? "x"
			  : "");
              وإلا إذا (specs->typespec_لفظ == cts_dfloat32)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "_Decimal32");
	      وإلا إذا (specs->typespec_لفظ == cts_dfloat64)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "_Decimal64");
	      وإلا إذا (specs->typespec_لفظ == cts_dfloat128)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "_Decimal128");
	      وإلا إذا (specs->typespec_لفظ == cts_dfloat64x)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "_Decimal64x");
	      وإلا
		{
		  specs->unsigned_p = سچ;
		  specs->locations[cdw_unsigned] = loc;
		}
	      اكسر;
	    حالة RID_COMPLEX:
	      dupe = specs->complex_p;
	      إذا (!اندريون_system_سرو_at (loc))
		pedwarn_c90 (loc, OPT_Wpedantic,
			     "ISO C90 does not support complex types");
	      إذا (specs->typespec_لفظ == cts_auto_type)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "__auto_type");
	      وإلا إذا (specs->typespec_لفظ == cts_void)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "void");
	      وإلا إذا (specs->typespec_لفظ == cts_bool)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "_Bool");
	      وإلا إذا (specs->typespec_لفظ == cts_bitint)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "_BitInt");
              وإلا إذا (specs->typespec_لفظ == cts_dfloat32)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "_Decimal32");
	      وإلا إذا (specs->typespec_لفظ == cts_dfloat64)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "_Decimal64");
	      وإلا إذا (specs->typespec_لفظ == cts_dfloat128)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "_Decimal128");
	      وإلا إذا (specs->typespec_لفظ == cts_dfloat64x)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "_Decimal64x");
	      وإلا إذا (specs->typespec_لفظ == cts_fract)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "_Fract");
	      وإلا إذا (specs->typespec_لفظ == cts_accum)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "_Accum");
	      وإلا إذا (specs->saturating_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "_Sat");
	      وإلا
		{
		  specs->complex_p = سچ;
		  specs->locations[cdw_complex] = loc;
		}
	      اكسر;
	    حالة RID_SAT:
	      dupe = specs->saturating_p;
	      pedwarn (loc, OPT_Wpedantic,
		       "ISO C does not support saturating types");
	      إذا (specs->typespec_لفظ == cts_int_n)
		error_at (loc,
			  "both %qs and %<__int%d%> in declaration specifiers",
			  "_Sat", int_n_معلومات[specs->u.int_n_idx].bitsize);
	      وإلا إذا (specs->typespec_لفظ == cts_auto_type)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "__auto_type");
	      وإلا إذا (specs->typespec_لفظ == cts_void)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "void");
	      وإلا إذا (specs->typespec_لفظ == cts_bool)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "_Bool");
	      وإلا إذا (specs->typespec_لفظ == cts_bitint)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "_BitInt");
	      وإلا إذا (specs->typespec_لفظ == cts_char)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "char");
	      وإلا إذا (specs->typespec_لفظ == cts_int)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "int");
	      وإلا إذا (specs->typespec_لفظ == cts_float)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "float");
	      وإلا إذا (specs->typespec_لفظ == cts_double)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "double");
	      وإلا إذا (specs->typespec_لفظ == cts_floatn_nx)
		error_at (loc,
			  "both %qs and %<_Float%d%s%> in declaration "
			  "specifiers", "_Sat",
			  floatn_nx_types[specs->u.floatn_nx_idx].n,
			  floatn_nx_types[specs->u.floatn_nx_idx].extended
			  ? "x"
			  : "");
              وإلا إذا (specs->typespec_لفظ == cts_dfloat32)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "_Decimal32");
	      وإلا إذا (specs->typespec_لفظ == cts_dfloat64)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "_Decimal64");
	      وإلا إذا (specs->typespec_لفظ == cts_dfloat128)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "_Decimal128");
	      وإلا إذا (specs->typespec_لفظ == cts_dfloat64x)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "_Decimal64x");
	      وإلا إذا (specs->complex_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "complex");
	      وإلا
		{
		  specs->saturating_p = سچ;
		  specs->locations[cdw_saturating] = loc;
		}
	      اكسر;
	    افتراضي:
	      gcc_unreachable ();
	    }

	  إذا (dupe)
	    error_at (loc, "duplicate %qE", type);

	  أرجع specs;
	}
      وإلا
	{
	  /* "void", "_Bool", "char", "int", "float", "double",
	     "_FloatN", "_FloatNx", "_Decimal32", "__intN",
	     "_Decimal64", "_Decimal128", "_Fract", "_Accum", "_BitInt(N)" or
	     "__auto_type".  */
	  إذا (specs->typespec_لفظ != cts_none)
	    {
	      إذا (i == RID_BOOL)
		{
		  auto_diagnostic_گروهه d;
		  إذا (specs->storage_class == csc_typedef)
		    error_at (loc,
			      "%qs cannot be defined via %<typedef%>",
			      IDENTIFIER_اشارو (type));
		  وإلا
		    error_at (loc,
			      "%qs cannot be used here",
			      IDENTIFIER_اشارو (type));
		  جوڙيو_note_about_new_keyword (loc, type);
		}
	      وإلا
		error_at (loc,
			  "two or more data types in declaration specifiers");
	      أرجع specs;
	    }
	  بدل (i)
	    {
	    حالة RID_AUTO_TYPE:
	      إذا (specs->long_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "__auto_type");
	      وإلا إذا (specs->short_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "__auto_type");
	      وإلا إذا (specs->signed_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "__auto_type");
	      وإلا إذا (specs->unsigned_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "__auto_type");
	      وإلا إذا (specs->complex_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "__auto_type");
	      وإلا إذا (specs->saturating_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "__auto_type");
	      وإلا
		{
		  specs->typespec_لفظ = cts_auto_type;
		  specs->locations[cdw_typespec] = loc;
		}
	      أرجع specs;
	    حالة RID_INT_N_0:
	    حالة RID_INT_N_1:
	    حالة RID_INT_N_2:
	    حالة RID_INT_N_3:
	      specs->u.int_n_idx = i - RID_INT_N_0;
	      إذا (!اندريون_system_سرو_at (داخلا_location)
		  /* If the INT_N type ends in "__", and so is of the format
		     "__intN__", don't pedwarn.  */
		  && (لڙي_ڀيٽ (IDENTIFIER_اشارو (type)
			       + (IDENTIFIER_ڊيگهائي (type) - 2), "__", 2) != 0))
		pedwarn (loc, OPT_Wpedantic,
			 "ISO C does not support %<__int%d%> types",
			 int_n_معلومات[specs->u.int_n_idx].bitsize);

	      إذا (specs->long_p)
		error_at (loc,
			  "both %<__int%d%> and %qs in declaration specifiers",
			  int_n_معلومات[specs->u.int_n_idx].bitsize, "long");
	      وإلا إذا (specs->saturating_p)
		error_at (loc,
			  "both %qs and %<__int%d%> in declaration specifiers",
			  "_Sat", int_n_معلومات[specs->u.int_n_idx].bitsize);
	      وإلا إذا (specs->short_p)
		error_at (loc,
			  "both %<__int%d%> and %qs in declaration specifiers",
			  int_n_معلومات[specs->u.int_n_idx].bitsize, "short");
	      وإلا إذا (! int_n_enabled_p[specs->u.int_n_idx])
		{
		  specs->typespec_لفظ = cts_int_n;
		  error_at (loc,
			    "%<__int%d%> is not supported on this target",
			    int_n_معلومات[specs->u.int_n_idx].bitsize);
		}
	      وإلا
		{
		  specs->typespec_لفظ = cts_int_n;
		  specs->locations[cdw_typespec] = loc;
		}
	      أرجع specs;
	    حالة RID_VOID:
	      إذا (specs->long_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "void");
	      وإلا إذا (specs->short_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "void");
	      وإلا إذا (specs->signed_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "void");
	      وإلا إذا (specs->unsigned_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "void");
	      وإلا إذا (specs->complex_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "void");
	      وإلا إذا (specs->saturating_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "void");
	      وإلا
		{
		  specs->typespec_لفظ = cts_void;
		  specs->locations[cdw_typespec] = loc;
		}
	      أرجع specs;
	    حالة RID_BOOL:
	      إذا (!اندريون_system_سرو_at (loc))
		pedwarn_c90 (loc, OPT_Wpedantic,
			     "ISO C90 does not support boolean types");
	      إذا (specs->long_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "_Bool");
	      وإلا إذا (specs->short_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "_Bool");
	      وإلا إذا (specs->signed_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "_Bool");
	      وإلا إذا (specs->unsigned_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "_Bool");
	      وإلا إذا (specs->complex_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "_Bool");
	      وإلا إذا (specs->saturating_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "_Bool");
	      وإلا
		{
		  specs->typespec_لفظ = cts_bool;
		  specs->locations[cdw_typespec] = loc;
		}
	      أرجع specs;
	    حالة RID_CHAR:
	      إذا (specs->long_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "char");
	      وإلا إذا (specs->short_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "char");
	      وإلا إذا (specs->saturating_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "char");
	      وإلا
		{
		  specs->typespec_لفظ = cts_char;
		  specs->locations[cdw_typespec] = loc;
		}
	      أرجع specs;
	    حالة RID_INT:
	      إذا (specs->saturating_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "int");
	      وإلا
		{
		  specs->typespec_لفظ = cts_int;
		  specs->locations[cdw_typespec] = loc;
		}
	      أرجع specs;
	    حالة RID_FLOAT:
	      إذا (specs->long_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "float");
	      وإلا إذا (specs->short_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "float");
	      وإلا إذا (specs->signed_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "float");
	      وإلا إذا (specs->unsigned_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "float");
	      وإلا إذا (specs->saturating_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "float");
	      وإلا
		{
		  specs->typespec_لفظ = cts_float;
		  specs->locations[cdw_typespec] = loc;
		}
	      أرجع specs;
	    حالة RID_DOUBLE:
	      إذا (specs->long_long_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long long", "double");
	      وإلا إذا (specs->short_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "double");
	      وإلا إذا (specs->signed_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "double");
	      وإلا إذا (specs->unsigned_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "double");
	      وإلا إذا (specs->saturating_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "double");
	      وإلا
		{
		  specs->typespec_لفظ = cts_double;
		  specs->locations[cdw_typespec] = loc;
		}
	      أرجع specs;
	    CASE_RID_FLOATN_NX:
	      specs->u.floatn_nx_idx = i - RID_FLOATN_NX_پهريون;
	      إذا (!اندريون_system_سرو_at (داخلا_location))
		pedwarn_c11 (loc, OPT_Wpedantic,
			     "ISO C does not support the %<_Float%d%s%> type"
			     " before C23",
			     floatn_nx_types[specs->u.floatn_nx_idx].n,
			     floatn_nx_types[specs->u.floatn_nx_idx].extended
			     ? "x"
			     : "");

	      إذا (specs->long_p)
		error_at (loc,
			  "both %qs and %<_Float%d%s%> in declaration "
			  "specifiers", "long",
			  floatn_nx_types[specs->u.floatn_nx_idx].n,
			  floatn_nx_types[specs->u.floatn_nx_idx].extended
			  ? "x"
			  : "");
	      وإلا إذا (specs->short_p)
		error_at (loc,
			  "both %qs and %<_Float%d%s%> in declaration "
			  "specifiers", "short",
			  floatn_nx_types[specs->u.floatn_nx_idx].n,
			  floatn_nx_types[specs->u.floatn_nx_idx].extended
			  ? "x"
			  : "");
	      وإلا إذا (specs->signed_p)
		error_at (loc,
			  "both %qs and %<_Float%d%s%> in declaration "
			  "specifiers", "signed",
			  floatn_nx_types[specs->u.floatn_nx_idx].n,
			  floatn_nx_types[specs->u.floatn_nx_idx].extended
			  ? "x"
			  : "");
	      وإلا إذا (specs->unsigned_p)
		error_at (loc,
			  "both %qs and %<_Float%d%s%> in declaration "
			  "specifiers", "unsigned",
			  floatn_nx_types[specs->u.floatn_nx_idx].n,
			  floatn_nx_types[specs->u.floatn_nx_idx].extended
			  ? "x"
			  : "");
	      وإلا إذا (specs->saturating_p)
		error_at (loc,
			  "both %qs and %<_Float%d%s%> in declaration "
			  "specifiers", "_Sat",
			  floatn_nx_types[specs->u.floatn_nx_idx].n,
			  floatn_nx_types[specs->u.floatn_nx_idx].extended
			  ? "x"
			  : "");
	      وإلا إذا (FLOATN_NX_TYPE_ڳنڍ (specs->u.floatn_nx_idx) == NULL_وڻ)
		{
		  specs->typespec_لفظ = cts_floatn_nx;
		  error_at (loc,
			    "%<_Float%d%s%> is not supported on this target",
			    floatn_nx_types[specs->u.floatn_nx_idx].n,
			    floatn_nx_types[specs->u.floatn_nx_idx].extended
			    ? "x"
			    : "");
		}
	      وإلا
		{
		  specs->typespec_لفظ = cts_floatn_nx;
		  specs->locations[cdw_typespec] = loc;
		}
	      أرجع specs;
	    حالة RID_DFLOAT32:
	    حالة RID_DFLOAT64:
	    حالة RID_DFLOAT128:
	    حالة RID_DFLOAT64X:
	      {
		ثابت حرف *str;
		إذا (i == RID_DFLOAT32)
		  str = "_Decimal32";
		وإلا إذا (i == RID_DFLOAT64)
		  str = "_Decimal64";
		وإلا إذا (i == RID_DFLOAT128)
		  str = "_Decimal128";
		وإلا
		  str = "_Decimal64x";
		إذا (specs->long_long_p)
		  error_at (loc,
			    "both %qs and %qs in declaration specifiers",
			    "long long", str);
		إذا (specs->long_p)
		  error_at (loc,
			    "both %qs and %qs in declaration specifiers",
			    "long", str);
		وإلا إذا (specs->short_p)
		  error_at (loc,
			    "both %qs and %qs in declaration specifiers",
			    "short", str);
		وإلا إذا (specs->signed_p)
		  error_at (loc,
			    "both %qs and %qs in declaration specifiers",
			    "signed", str);
		وإلا إذا (specs->unsigned_p)
		  error_at (loc,
			    "both %qs and %qs in declaration specifiers",
			    "unsigned", str);
                وإلا إذا (specs->complex_p)
                  error_at (loc,
			    "both %qs and %qs in declaration specifiers",
			    "complex", str);
                وإلا إذا (specs->saturating_p)
                  error_at (loc,
			    "both %qs and %qs in declaration specifiers",
			    "_Sat", str);
		وإلا إذا (i == RID_DFLOAT32)
		  specs->typespec_لفظ = cts_dfloat32;
		وإلا إذا (i == RID_DFLOAT64)
		  specs->typespec_لفظ = cts_dfloat64;
		وإلا إذا (i == RID_DFLOAT128)
		  specs->typespec_لفظ = cts_dfloat128;
		وإلا
		  specs->typespec_لفظ = cts_dfloat64x;
		specs->locations[cdw_typespec] = loc;
	      }
	      إذا (!targetm.decimal_float_supported_p ())
		error_at (loc,
			  "decimal floating-point not supported "
			  "for this target");
	      pedwarn_c11 (loc, OPT_Wpedantic,
			   "ISO C does not support decimal floating-point "
			   "before C23");
	      أرجع specs;
	    حالة RID_FRACT:
	    حالة RID_ACCUM:
	      {
		ثابت حرف *str;
		إذا (i == RID_FRACT)
		  str = "_Fract";
		وإلا
		  str = "_Accum";
                إذا (specs->complex_p)
                  error_at (loc,
			    "both %qs and %qs in declaration specifiers",
			    "complex", str);
		وإلا إذا (i == RID_FRACT)
		    specs->typespec_لفظ = cts_fract;
		وإلا
		    specs->typespec_لفظ = cts_accum;
		specs->locations[cdw_typespec] = loc;
	      }
	      إذا (!targetm.fixed_نقطو_supported_p ())
		error_at (loc,
			  "fixed-point types not supported for this target");
	      pedwarn (loc, OPT_Wpedantic,
		       "ISO C does not support fixed-point types");
	      أرجع specs;
	    حالة RID_BITINT:
	      إذا (specs->long_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "_BitInt");
	      وإلا إذا (specs->short_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "_BitInt");
	      وإلا إذا (specs->complex_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "_BitInt");
	      وإلا إذا (specs->saturating_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "_BitInt");
	      وإلا
		{
		  specs->typespec_لفظ = cts_bitint;
		  specs->locations[cdw_typespec] = loc;
		  specs->u.bitint_prec = -1;
		  إذا (error_عمليو_p (spec.اظهار))
		    أرجع specs;
		  إذا (وڻ_ڪوڊ (spec.اظهار) != INTEGER_CST
		      || !INTEGRAL_TYPE_P (وڻ_TYPE (spec.اظهار)))
		    {
		      error_at (loc, "%<_BitInt%> argument is not an integer "
				     "constant expression");
		      أرجع specs;
		    }
		  إذا (وڻ_int_cst_sgn (spec.اظهار) <= 0)
		    {
		      error_at (loc, "%<_BitInt%> argument %qE is not a "
				     "positive integer constant expression",
				spec.اظهار);
		      أرجع specs;
		    }
		  إذا (wi::منزل_widest (spec.اظهار) > WIDE_INT_MAX_PRECISION - 1)
		    {
		      error_at (loc, "%<_BitInt%> argument %qE is larger than "
				     "%<BITINT_MAXWIDTH%> %qd",
				spec.اظهار, (صحيح) WIDE_INT_MAX_PRECISION - 1);
		      أرجع specs;
		    }
		  specs->u.bitint_prec = وڻ_منزل_uhwi (spec.اظهار);
		  بنية bitint_info info;
		  إذا (!targetm.c.bitint_type_info (specs->u.bitint_prec,
						   &info))
		    {
		      sorry_at (loc, "%<_BitInt(%d)%> is not supported on "
				     "this target", specs->u.bitint_prec);
		      specs->u.bitint_prec = -1;
		      أرجع specs;
		    }
		}
	      أرجع specs;
	    افتراضي:
	      /* ObjC reserved word "id", handled below.  */
	      اكسر;
	    }
	}
    }

  /* Now we have a typedef (a TYPE_DECL node), an identifier (some
     form of ObjC type, cases such as "int" and "long" being handled
     above), a TYPE (struct, union, enum and typeof specifiers) or an
     ERROR_MARK.  In none of these cases may there have previously
     been any type specifiers.  */
  إذا (specs->type || specs->typespec_لفظ != cts_none
      || specs->long_p || specs->short_p || specs->signed_p
      || specs->unsigned_p || specs->complex_p)
    error_at (loc, "two or more data types in declaration specifiers");
  وإلا إذا (وڻ_ڪوڊ (type) == TYPE_DECL)
    {
      specs->type = وڻ_TYPE (type);
      إذا (وڻ_TYPE (type) != error_mark_ڳنڍ)
	{
	  mark_decl_استعمال_ٿيل (type, خطأ);
	  specs->decl_attr = DECL_خاصيتون (type);
	  specs->typedef_p = سچ;
	  specs->explicit_signed_p = C_TYPEDEF_EXPLICITLY_SIGNED (type);
	  specs->locations[cdw_typedef] = loc;

	  /* If this typedef name is defined in a struct, then a C++
	     lookup would return a different value.  */
	  إذا (warn_cxx_compat
	      && I_نشان_BINDING (DECL_NAME (type))->اندريون_struct)
	    warning_at (loc, OPT_Wc___compat,
			"C++ lookup of %qD would return a field, not a type",
			type);

	  /* If we are parsing a struct, record that a struct field
	     used a typedef.  */
	  إذا (warn_cxx_compat && struct_parse_info != عدم)
	    struct_parse_info->typedefs_ڏٺل.محفوظ_ڌڪو (type);
	}
    }
  وإلا إذا (وڻ_ڪوڊ (type) == IDENTIFIER_ڳنڍ)
    {
      وڻ t = lookup_name (type);
      إذا (!t || وڻ_ڪوڊ (t) != TYPE_DECL)
	error_at (loc, "%qE fails to be a typedef or built in type", type);
      وإلا إذا (وڻ_TYPE (t) == error_mark_ڳنڍ)
	;
      وإلا
	{
	  specs->type = وڻ_TYPE (t);
	  specs->locations[cdw_typespec] = loc;
	}
    }
  وإلا
    {
      إذا (وڻ_ڪوڊ (type) != ERROR_MARK)
	{
	  إذا (spec.قسم == ctsk_typeof)
	    {
	      specs->typedef_p = سچ;
	      specs->locations[cdw_typedef] = loc;
	    }

	  إذا (وڻ_ڪوڊ (type) == رڪارڊ_TYPE || وڻ_ڪوڊ (type) == UNION_TYPE
	      || وڻ_ڪوڊ (type) == ENUMERAL_TYPE)
	    mark_decl_استعمال_ٿيل (TYPE_STUB_DECL (type), خطأ);

	  إذا (spec.اظهار)
	    {
	      وڻ اظهار = save_اظهار (fold_convert (void_type_ڳنڍ, spec.اظهار));
	      إذا (specs->اظهار)
		specs->اظهار = build2 (COMPOUND_اظهار, وڻ_TYPE (اظهار),
				      specs->اظهار, اظهار);
	      وإلا
		specs->اظهار = اظهار;
	      specs->اظهار_const_operands &= spec.اظهار_const_operands;
	    }
	}
      specs->type = type;
      إذا (spec.has_enum_type_specifier
	  && spec.قسم != ctsk_tagdef)
	specs->enum_type_specifier_ref_p = سچ;
    }

  أرجع specs;
}

/* Add the storage class specifier or function specifier SCSPEC to the
   declaration specifiers SPECS, returning SPECS.  */

بنية c_declspecs *
declspecs_جوڙيو_scspec (location_t loc,
		      بنية c_declspecs *specs,
		      وڻ scspec)
{
  تعداد rid i;
  تعداد c_storage_class n = csc_none;
  منطقي dupe = خطأ;
  specs->declspecs_ڏٺل_p = سچ;
  specs->non_std_attrs_ڏٺل_p = سچ;
  gcc_assert (وڻ_ڪوڊ (scspec) == IDENTIFIER_ڳنڍ
	      && C_IS_RESERVED_لفظ (scspec));
  i = C_RID_ڪوڊ (scspec);
  إذا (specs->non_sc_ڏٺل_p)
    warning (OPT_Wold_style_declaration,
             "%qE is not at beginning of declaration", scspec);
  بدل (i)
    {
    حالة RID_INLINE:
      /* C99 permits duplicate inline.  Although of doubtful utility,
	 it seems simplest to permit it in gnu89 mode as well, as
	 there is also little utility in maintaining this as a
	 difference between gnu89 and C99 inline.  */
      dupe = خطأ;
      specs->inline_p = سچ;
      specs->locations[cdw_inline] = loc;
      اكسر;
    حالة RID_NORETURN:
      /* Duplicate _Noreturn is permitted.  */
      dupe = خطأ;
      specs->noreturn_p = سچ;
      specs->locations[cdw_noreturn] = loc;
      اكسر;
    حالة RID_THREAD:
      dupe = specs->thread_p;
      إذا (specs->storage_class == csc_auto)
	error ("%qE used with %<auto%>", scspec);
      وإلا إذا (specs->storage_class == csc_رجسٽر)
	error ("%qE used with %<register%>", scspec);
      وإلا إذا (specs->storage_class == csc_typedef)
	error ("%qE used with %<typedef%>", scspec);
      وإلا إذا (specs->constexpr_p)
	error ("%qE used with %<constexpr%>", scspec);
      وإلا
	{
	  specs->thread_p = سچ;
	  specs->thread_gnu_p = (strcmp (IDENTIFIER_اشارو (scspec),
					 "__thread") == 0);
	  /* A diagnostic is not required for the use of this
	     identifier in the implementation namespace; only diagnose
	     it for the C11 spelling because of existing code using
	     the other spelling.  */
	  إذا (!specs->thread_gnu_p)
	    {
	      إذا (flag_isoc99)
		pedwarn_c99 (loc, OPT_Wpedantic,
			     "ISO C99 does not support %qE", scspec);
	      وإلا
		pedwarn_c99 (loc, OPT_Wpedantic,
			     "ISO C90 does not support %qE", scspec);
	    }
	  specs->locations[cdw_thread] = loc;
	}
      اكسر;
    حالة RID_AUTO:
      إذا (flag_isoc23
	  && specs->typespec_قسم == ctsk_none
	  && specs->storage_class != csc_typedef)
	{
	  /* "auto" potentially used for type deduction.  */
	  إذا (specs->c23_auto_p)
	    error ("duplicate %qE", scspec);
	  specs->c23_auto_p = سچ;
	  أرجع specs;
	}
      n = csc_auto;
      /* auto may only be used with another storage class specifier,
	 such as constexpr, if the type is inferred.  */
      إذا (specs->constexpr_p)
	error ("%qE used with %<constexpr%>", scspec);
      اكسر;
    حالة RID_EXTERN:
      n = csc_extern;
      /* Diagnose "__thread extern".  */
      إذا (specs->thread_p && specs->thread_gnu_p)
	error ("%<__thread%> before %<extern%>");
      اكسر;
    حالة RID_رجسٽر:
      n = csc_رجسٽر;
      اكسر;
    حالة RID_STATIC:
      n = csc_static;
      /* Diagnose "__thread static".  */
      إذا (specs->thread_p && specs->thread_gnu_p)
	error ("%<__thread%> before %<static%>");
      اكسر;
    حالة RID_TYPEDEF:
      n = csc_typedef;
      إذا (specs->c23_auto_p)
	{
	  error ("%<typedef%> used with %<auto%>");
	  specs->c23_auto_p = خطأ;
	}
      اكسر;
    حالة RID_CONSTEXPR:
      dupe = specs->constexpr_p;
      إذا (specs->storage_class == csc_extern)
	error ("%qE used with %<extern%>", scspec);
      وإلا إذا (specs->storage_class == csc_typedef)
	error ("%qE used with %<typedef%>", scspec);
      وإلا إذا (specs->storage_class == csc_auto)
	/* auto may only be used with another storage class specifier,
	   such as constexpr, if the type is inferred.  */
	error ("%qE used with %<auto%>", scspec);
      وإلا إذا (specs->thread_p)
	error ("%qE used with %qs", scspec,
	       specs->thread_gnu_p ? "__thread" : "_Thread_local");
      وإلا
	specs->constexpr_p = سچ;
      اكسر;
    افتراضي:
      gcc_unreachable ();
    }
  إذا (n != csc_none && n == specs->storage_class)
    dupe = سچ;
  إذا (dupe)
    {
      إذا (i == RID_THREAD)
	error ("duplicate %<_Thread_local%> or %<__thread%>");
      وإلا
	error ("duplicate %qE", scspec);
    }
  إذا (n != csc_none)
    {
      إذا (specs->storage_class != csc_none && n != specs->storage_class)
	{
	  error ("multiple storage classes in declaration specifiers");
	}
      وإلا
	{
	  specs->storage_class = n;
	  specs->locations[cdw_storage_class] = loc;
	  إذا (n != csc_extern && n != csc_static && specs->thread_p)
	    {
	      error ("%qs used with %qE",
		     specs->thread_gnu_p ? "__thread" : "_Thread_local",
		     scspec);
	      specs->thread_p = خطأ;
	    }
	  إذا (n != csc_auto && n != csc_رجسٽر && n != csc_static
	      && specs->constexpr_p)
	    {
	      error ("%<constexpr%> used with %qE", scspec);
	      specs->constexpr_p = خطأ;
	    }
	}
    }
  أرجع specs;
}

/* Add the attributes ATTRS to the declaration specifiers SPECS,
   returning SPECS.  */

بنية c_declspecs *
declspecs_جوڙيو_attrs (location_t loc, بنية c_declspecs *specs, وڻ attrs)
{
  specs->attrs = chainon (attrs, specs->attrs);
  specs->locations[cdw_خاصيتون] = loc;
  specs->declspecs_ڏٺل_p = سچ;
  /* In the case of standard attributes at the start of the
     declaration, the caller will reset this.  */
  specs->non_std_attrs_ڏٺل_p = سچ;
  أرجع specs;
}

/* Add an _Alignas specifier (expression ALIGN, or type whose
   alignment is ALIGN) to the declaration specifiers SPECS, returning
   SPECS.  */
بنية c_declspecs *
declspecs_جوڙيو_alignas (location_t loc,
		       بنية c_declspecs *specs, وڻ align)
{
  specs->alignas_p = سچ;
  specs->locations[cdw_alignas] = loc;
  إذا (align == error_mark_ڳنڍ)
    أرجع specs;

  /* Only accept the alignment if it's valid and greater than
     the current one.  Zero is invalid but by C11 required to
     be silently ignored.  */
  صحيح align_log = check_user_alignment (align, خطأ, /* warn_zero = */خطأ);
  إذا (align_log > specs->align_log)
    specs->align_log = align_log;
  أرجع specs;
}

/* Combine "long", "short", "signed", "unsigned" and "_Complex" type
   specifiers with any other type specifier to determine the resulting
   type.  This is where ISO C checks on complex types are made, since
   "_Complex long" is a prefix of the valid ISO C type "_Complex long
   double".  Also apply postfix standard attributes to modify the type.  */

بنية c_declspecs *
پڄاڻي_declspecs (بنية c_declspecs *specs)
{
  /* If a type was specified as a whole, we have no modifiers and are
     done.  */
  إذا (specs->type != NULL_وڻ)
    {
      gcc_assert (!specs->long_p && !specs->long_long_p && !specs->short_p
		  && !specs->signed_p && !specs->unsigned_p
		  && !specs->complex_p && !specs->c23_auto_p);

      /* Set a dummy type.  */
      إذا (وڻ_ڪوڊ (specs->type) == ERROR_MARK)
        specs->type = integer_type_ڳنڍ;
      اذهب handle_postfix_attrs;
    }

  /* If none of "void", "_Bool", "char", "int", "float" or "double"
     has been specified, treat it as "int" unless "_Complex" is
     present and there are no other specifiers.  If we just have
     "_Complex", it is equivalent to "_Complex double", but e.g.
     "_Complex short" is equivalent to "_Complex short int".  */
  إذا (specs->typespec_لفظ == cts_none)
    {
      إذا (specs->saturating_p)
	{
	  error_at (specs->locations[cdw_saturating],
		    "%<_Sat%> is used without %<_Fract%> or %<_Accum%>");
	  إذا (!targetm.fixed_نقطو_supported_p ())
	    error_at (specs->locations[cdw_saturating],
		      "fixed-point types not supported for this target");
	  specs->typespec_لفظ = cts_fract;
	}
      وإلا إذا (specs->long_p || specs->short_p
	       || specs->signed_p || specs->unsigned_p)
	{
	  specs->typespec_لفظ = cts_int;
	}
      وإلا إذا (specs->complex_p)
	{
	  specs->typespec_لفظ = cts_double;
	  pedwarn (specs->locations[cdw_complex], OPT_Wpedantic,
		   "ISO C does not support plain %<complex%> meaning "
		   "%<double complex%>");
	}
      وإلا إذا (specs->c23_auto_p)
	{
	  /* Type to be filled in later, including applying postfix
	     attributes.  This warning only actually appears for
	     -Wc11-c23-compat in C23 mode; in older modes, there may
	     be a warning or pedwarn for implicit "int" instead, or
	     other errors for use of auto at file scope.  */
	  pedwarn_c11 (داخلا_location, OPT_Wpedantic,
		       "ISO C does not support %<auto%> type deduction "
		       "before C23");
	  أرجع specs;
	}
      وإلا
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
  بدل (specs->typespec_لفظ)
    {
    حالة cts_auto_type:
      gcc_assert (!specs->long_p && !specs->short_p
		  && !specs->signed_p && !specs->unsigned_p
		  && !specs->complex_p);
      /* Type to be filled in later.  */
      إذا (specs->postfix_attrs)
	error ("%<__auto_type%> followed by %<[[]]%> attributes");
      اكسر;
    حالة cts_void:
      gcc_assert (!specs->long_p && !specs->short_p
		  && !specs->signed_p && !specs->unsigned_p
		  && !specs->complex_p);
      specs->type = void_type_ڳنڍ;
      اكسر;
    حالة cts_bool:
      gcc_assert (!specs->long_p && !specs->short_p
		  && !specs->signed_p && !specs->unsigned_p
		  && !specs->complex_p);
      specs->type = boolean_type_ڳنڍ;
      اكسر;
    حالة cts_char:
      gcc_assert (!specs->long_p && !specs->short_p);
      gcc_assert (!(specs->signed_p && specs->unsigned_p));
      إذا (specs->signed_p)
	specs->type = signed_char_type_ڳنڍ;
      وإلا إذا (specs->unsigned_p)
	specs->type = unsigned_char_type_ڳنڍ;
      وإلا
	specs->type = char_type_ڳنڍ;
      إذا (specs->complex_p)
	{
	  pedwarn (specs->locations[cdw_complex], OPT_Wpedantic,
		   "ISO C does not support complex integer types");
	  specs->type = build_complex_type (specs->type);
	}
      اكسر;
    حالة cts_int_n:
      gcc_assert (!specs->long_p && !specs->short_p && !specs->long_long_p);
      gcc_assert (!(specs->signed_p && specs->unsigned_p));
      إذا (! int_n_enabled_p[specs->u.int_n_idx])
	specs->type = integer_type_ڳنڍ;
      وإلا
	specs->type = (specs->unsigned_p
		       ? int_n_trees[specs->u.int_n_idx].unsigned_type
		       : int_n_trees[specs->u.int_n_idx].signed_type);
      إذا (specs->complex_p)
	{
	  pedwarn (specs->locations[cdw_complex], OPT_Wpedantic,
		   "ISO C does not support complex integer types");
	  specs->type = build_complex_type (specs->type);
	}
      اكسر;
    حالة cts_int:
      gcc_assert (!(specs->long_p && specs->short_p));
      gcc_assert (!(specs->signed_p && specs->unsigned_p));
      إذا (specs->long_long_p)
	specs->type = (specs->unsigned_p
		       ? long_long_unsigned_type_ڳنڍ
		       : long_long_integer_type_ڳنڍ);
      وإلا إذا (specs->long_p)
	specs->type = (specs->unsigned_p
		       ? long_unsigned_type_ڳنڍ
		       : long_integer_type_ڳنڍ);
      وإلا إذا (specs->short_p)
	specs->type = (specs->unsigned_p
		       ? short_unsigned_type_ڳنڍ
		       : short_integer_type_ڳنڍ);
      وإلا
	specs->type = (specs->unsigned_p
		       ? unsigned_type_ڳنڍ
		       : integer_type_ڳنڍ);
      إذا (specs->complex_p)
	{
	  pedwarn (specs->locations[cdw_complex], OPT_Wpedantic,
		   "ISO C does not support complex integer types");
	  specs->type = build_complex_type (specs->type);
	}
      اكسر;
    حالة cts_float:
      gcc_assert (!specs->long_p && !specs->short_p
		  && !specs->signed_p && !specs->unsigned_p);
      specs->type = (specs->complex_p
		     ? complex_float_type_ڳنڍ
		     : float_type_ڳنڍ);
      اكسر;
    حالة cts_double:
      gcc_assert (!specs->long_long_p && !specs->short_p
		  && !specs->signed_p && !specs->unsigned_p);
      إذا (specs->long_p)
	{
	  specs->type = (specs->complex_p
			 ? complex_long_double_type_ڳنڍ
			 : long_double_type_ڳنڍ);
	}
      وإلا
	{
	  specs->type = (specs->complex_p
			 ? complex_double_type_ڳنڍ
			 : double_type_ڳنڍ);
	}
      اكسر;
    حالة cts_floatn_nx:
      gcc_assert (!specs->long_p && !specs->short_p
		  && !specs->signed_p && !specs->unsigned_p);
      إذا (FLOATN_NX_TYPE_ڳنڍ (specs->u.floatn_nx_idx) == NULL_وڻ)
	specs->type = integer_type_ڳنڍ;
      وإلا إذا (specs->complex_p)
	specs->type = COMPLEX_FLOATN_NX_TYPE_ڳنڍ (specs->u.floatn_nx_idx);
      وإلا
	specs->type = FLOATN_NX_TYPE_ڳنڍ (specs->u.floatn_nx_idx);
      اكسر;
    حالة cts_dfloat32:
    حالة cts_dfloat64:
    حالة cts_dfloat128:
    حالة cts_dfloat64x:
      gcc_assert (!specs->long_p && !specs->long_long_p && !specs->short_p
		  && !specs->signed_p && !specs->unsigned_p && !specs->complex_p);
      إذا (!targetm.decimal_float_supported_p ())
	specs->type = integer_type_ڳنڍ;
      وإلا إذا (specs->typespec_لفظ == cts_dfloat32)
	specs->type = dfloat32_type_ڳنڍ;
      وإلا إذا (specs->typespec_لفظ == cts_dfloat64)
	specs->type = dfloat64_type_ڳنڍ;
      وإلا إذا (specs->typespec_لفظ == cts_dfloat128)
	specs->type = dfloat128_type_ڳنڍ;
      وإلا
	specs->type = dfloat64x_type_ڳنڍ;
      اكسر;
    حالة cts_fract:
      gcc_assert (!specs->complex_p);
      إذا (!targetm.fixed_نقطو_supported_p ())
	specs->type = integer_type_ڳنڍ;
      وإلا إذا (specs->saturating_p)
	{
	  إذا (specs->long_long_p)
	    specs->type = specs->unsigned_p
			  ? sat_unsigned_long_long_fract_type_ڳنڍ
			  : sat_long_long_fract_type_ڳنڍ;
	  وإلا إذا (specs->long_p)
	    specs->type = specs->unsigned_p
			  ? sat_unsigned_long_fract_type_ڳنڍ
			  : sat_long_fract_type_ڳنڍ;
	  وإلا إذا (specs->short_p)
	    specs->type = specs->unsigned_p
			  ? sat_unsigned_short_fract_type_ڳنڍ
			  : sat_short_fract_type_ڳنڍ;
	  وإلا
	    specs->type = specs->unsigned_p
			  ? sat_unsigned_fract_type_ڳنڍ
			  : sat_fract_type_ڳنڍ;
	}
      وإلا
	{
	  إذا (specs->long_long_p)
	    specs->type = specs->unsigned_p
			  ? unsigned_long_long_fract_type_ڳنڍ
			  : long_long_fract_type_ڳنڍ;
	  وإلا إذا (specs->long_p)
	    specs->type = specs->unsigned_p
			  ? unsigned_long_fract_type_ڳنڍ
			  : long_fract_type_ڳنڍ;
	  وإلا إذا (specs->short_p)
	    specs->type = specs->unsigned_p
			  ? unsigned_short_fract_type_ڳنڍ
			  : short_fract_type_ڳنڍ;
	  وإلا
	    specs->type = specs->unsigned_p
			  ? unsigned_fract_type_ڳنڍ
			  : fract_type_ڳنڍ;
	}
      اكسر;
    حالة cts_accum:
      gcc_assert (!specs->complex_p);
      إذا (!targetm.fixed_نقطو_supported_p ())
	specs->type = integer_type_ڳنڍ;
      وإلا إذا (specs->saturating_p)
	{
	  إذا (specs->long_long_p)
	    specs->type = specs->unsigned_p
			  ? sat_unsigned_long_long_accum_type_ڳنڍ
			  : sat_long_long_accum_type_ڳنڍ;
	  وإلا إذا (specs->long_p)
	    specs->type = specs->unsigned_p
			  ? sat_unsigned_long_accum_type_ڳنڍ
			  : sat_long_accum_type_ڳنڍ;
	  وإلا إذا (specs->short_p)
	    specs->type = specs->unsigned_p
			  ? sat_unsigned_short_accum_type_ڳنڍ
			  : sat_short_accum_type_ڳنڍ;
	  وإلا
	    specs->type = specs->unsigned_p
			  ? sat_unsigned_accum_type_ڳنڍ
			  : sat_accum_type_ڳنڍ;
	}
      وإلا
	{
	  إذا (specs->long_long_p)
	    specs->type = specs->unsigned_p
			  ? unsigned_long_long_accum_type_ڳنڍ
			  : long_long_accum_type_ڳنڍ;
	  وإلا إذا (specs->long_p)
	    specs->type = specs->unsigned_p
			  ? unsigned_long_accum_type_ڳنڍ
			  : long_accum_type_ڳنڍ;
	  وإلا إذا (specs->short_p)
	    specs->type = specs->unsigned_p
			  ? unsigned_short_accum_type_ڳنڍ
			  : short_accum_type_ڳنڍ;
	  وإلا
	    specs->type = specs->unsigned_p
			  ? unsigned_accum_type_ڳنڍ
			  : accum_type_ڳنڍ;
	}
      اكسر;
    حالة cts_bitint:
      gcc_assert (!specs->long_p && !specs->short_p
		  && !specs->complex_p);
      إذا (!specs->unsigned_p && specs->u.bitint_prec == 1 && !flag_isoc2y)
	{
	  error_at (specs->locations[cdw_typespec],
		    "%<signed _BitInt%> argument must be at least 2 "
		    "before C2Y");
	  specs->type = integer_type_ڳنڍ;
	  اكسر;
	}
      إذا (specs->u.bitint_prec == -1)
	specs->type = integer_type_ڳنڍ;
      وإلا
	{
	  pedwarn_c11 (specs->locations[cdw_typespec], OPT_Wpedantic,
		       "ISO C does not support %<%s_BitInt(%d)%> before C23",
		       specs->unsigned_p ? "unsigned "
		       : specs->signed_p ? "signed " : "",
		       specs->u.bitint_prec);
	  specs->type = build_bitint_type (specs->u.bitint_prec,
					   specs->unsigned_p);
	}
      اكسر;
    افتراضي:
      gcc_unreachable ();
    }
 handle_postfix_attrs:
  إذا (specs->type != عدم)
    {
      specs->postfix_attrs
	= c_warn_type_خاصيتون (specs->type, specs->postfix_attrs);
      decl_خاصيتون (&specs->type, specs->postfix_attrs, 0);
      specs->postfix_attrs = NULL_وڻ;
    }

  أرجع specs;
}

/* Perform final processing on one file scope's declarations (or the
   external scope's declarations), GLOBALS.  */

ساكن فراغ
c_write_global_declarations_1 (وڻ globals)
{
  وڻ decl;
  منطقي reconsider;

  /* Process the decls in the order they were written.  */
  لكل (decl = globals; decl; decl = DECL_CHAIN (decl))
    {
      /* Check for used but undefined static functions using the C
	 standard's definition of "used", and set TREE_NO_WARNING so
	 that check_global_declaration doesn't repeat the check.  */
      إذا (وڻ_ڪوڊ (decl) == FUNCTION_DECL
	  && DECL_INITIAL (decl) == NULL_وڻ
	  && DECL_EXTERNAL (decl)
	  && !وڻ_عوامي (decl)
	  && !warning_suppressed_p (decl, OPT_Wunused))
	{
	  إذا (C_DECL_استعمال_ٿيل (decl))
	    {
	      إذا (pedwarn (داخلا_location, 0, "%q+F used but never defined",
			   decl))
		suppress_warning (decl, OPT_Wunused);
	    }
	  /* For -Wunused-function warn about unused static prototypes.  */
	  وإلا إذا (warn_اڻ_استعمال_ٿيل_function
		   && ! DECL_ARTIFICIAL (decl)
		   && warning (OPT_Wunused_function,
			       "%q+F declared %<static%> but never defined",
			       decl))
	    suppress_warning (decl, OPT_Wunused);
	}

      wrapup_global_declaration_1 (decl);
    }

  افعل
    {
      reconsider = خطأ;
      لكل (decl = globals; decl; decl = DECL_CHAIN (decl))
	reconsider |= wrapup_global_declaration_2 (decl);
    }
  طالما (reconsider);
}

/* Preserve the external declarations scope across a garbage collect.  */
ساكن GTY(()) وڻ ext_بلاڪ;

/* Collect all references relevant to SOURCE_FILE.  */

ساكن فراغ
collect_all_refs (ثابت حرف *ذريعو_file)
{
  وڻ t;
  بنانشان i;

  FOR_EACH_VEC_ELT (*all_translation_units, i, t)
    collect_ada_nodes (بلاڪ_VARS (DECL_INITIAL (t)), ذريعو_file);

  collect_ada_nodes (بلاڪ_VARS (ext_بلاڪ), ذريعو_file);
}

/* Collect source file references at global level.  */

ساكن فراغ
collect_ذريعو_refs (فراغ)
{
  وڻ t;
  وڻ decls;
  وڻ decl;
  بنانشان i;

  FOR_EACH_VEC_ELT (*all_translation_units, i, t)
    {
      decls = DECL_INITIAL (t);
      لكل (decl = بلاڪ_VARS (decls); decl; decl = وڻ_CHAIN (decl))
	إذا (!DECL_IS_UNDECLARED_BUILTIN (decl))
	  collect_ذريعو_ref (DECL_ذريعو_FILE (decl));
    }

  لكل (decl = بلاڪ_VARS (ext_بلاڪ); decl; decl = وڻ_CHAIN (decl))
    إذا (!DECL_IS_UNDECLARED_BUILTIN (decl))
      collect_ذريعو_ref (DECL_ذريعو_FILE (decl));
}

/* Free attribute access data that are not needed by the middle end. */

ساكن فراغ
free_attr_access_معلومات ()
{
  بنية cgraph_ڳنڍ *n;

  /* Iterate over all functions declared in the translation unit.  */
  FOR_EACH_FUNCTION (n)
    {
      لكل (وڻ parm = DECL_ARGUMENTS (n->decl); parm; parm = وڻ_CHAIN (parm))
	إذا (وڻ attrs = DECL_خاصيتون (parm))
	  attr_access::free_lang_معلومات (attrs);

      وڻ fntype = وڻ_TYPE (n->decl);
      إذا (!fntype || fntype == error_mark_ڳنڍ)
	استمر;
      وڻ attrs = TYPE_خاصيتون (fntype);
      إذا (!attrs)
	استمر;

      attr_access::free_lang_معلومات (attrs);
    }
}

/* Perform any final parser cleanups and generate initial debugging
   information.  */

فراغ
c_parse_final_cleanups (فراغ)
{
  وڻ t;
  بنانشان i;

  /* We don't want to do this if generating a PCH.  */
  إذا (pch_file)
    أرجع;

  timevar_stop (TV_PHASE_PARSING);
  timevar_شروعات (TV_PHASE_DEFERRED);

  /* Do the Objective-C stuff.  This is where all the Objective-C
     module stuff gets generated (symtab, class/protocol/selector
     lists etc).  */
  إذا (c_dialect_objc ())
    objc_write_global_declarations ();

  /* Close the external scope.  */
  ext_بلاڪ = ڪڍو_scope ();
  external_scope = 0;
  gcc_assert (!current_scope);

  /* Handle -fdump-ada-spec[-slim]. */
  إذا (flag_dump_ada_spec || flag_dump_ada_spec_slim)
    {
      /* Build a table of files to generate specs for */
      collect_ذريعو_ref (main_داخلا_filename);
      إذا (!flag_dump_ada_spec_slim)
	collect_ذريعو_refs ();

      dump_ada_specs (collect_all_refs, عدم);
    }

  /* Process all file scopes in this compilation, and the external_scope,
     through wrapup_global_declarations.  */
  FOR_EACH_VEC_ELT (*all_translation_units, i, t)
    c_write_global_declarations_1 (بلاڪ_VARS (DECL_INITIAL (t)));
  c_write_global_declarations_1 (بلاڪ_VARS (ext_بلاڪ));

  /* Call this to set cpp_implicit_aliases_done on all nodes.  This is
     important for function multiversioning aliases to get resolved.  */
  symtab->process_same_body_aliases ();

  إذا (!اندريون_lto_p)
    free_attr_access_معلومات ();

  timevar_stop (TV_PHASE_DEFERRED);
  timevar_شروعات (TV_PHASE_PARSING);

  ext_بلاڪ = عدم;
}

/* Register reserved keyword WORD as qualifier for address space AS.  */

فراغ
c_رجسٽر_addr_space (ثابت حرف *لفظ, addr_space_t as)
{
  صحيح rid = RID_پهريون_ADDR_SPACE + as;
  وڻ id;

  /* Address space qualifiers are only supported
     in C with GNU extensions enabled.  */
  إذا (c_dialect_objc () || flag_no_asm)
    أرجع;

  id = get_identifier (لفظ);
  C_سيٽ_RID_ڪوڊ (id, rid);
  C_IS_RESERVED_لفظ (id) = 1;
  ridpointers [rid] = id;
}

/* Return identifier to look up for omp declare reduction.  */

وڻ
c_omp_reduction_id (تعداد وڻ_ڪوڊ_2 reduction_ڪوڊ, وڻ reduction_id)
{
  ثابت حرف *p = عدم;
  بدل (reduction_ڪوڊ)
    {
    حالة PLUS_اظهار: p = "+"; اكسر;
    حالة MULT_اظهار: p = "*"; اكسر;
    حالة MINUS_اظهار: p = "-"; اكسر;
    حالة ٻٽو_انگ_AND_اظهار: p = "&"; اكسر;
    حالة ٻٽو_انگ_XOR_اظهار: p = "^"; اكسر;
    حالة ٻٽو_انگ_IOR_اظهار: p = "|"; اكسر;
    حالة TRUTH_ANDIF_اظهار: p = "&&"; اكسر;
    حالة TRUTH_ORIF_اظهار: p = "||"; اكسر;
    حالة MIN_اظهار: p = "min"; اكسر;
    حالة MAX_اظهار: p = "max"; اكسر;
    افتراضي:
      اكسر;
    }

  إذا (p == عدم)
    {
      إذا (وڻ_ڪوڊ (reduction_id) != IDENTIFIER_ڳنڍ)
	أرجع error_mark_ڳنڍ;
      p = IDENTIFIER_اشارو (reduction_id);
    }

  ثابت حرف اڳياڙي[] = "omp declare reduction ";
  سائيز_t lenp = حجم (اڳياڙي);
  سائيز_t len = لڙي_ڊيگهه (p);
  حرف *name = XALLOCAVEC (حرف, lenp + len);
  يادگيري_نقل (name, اڳياڙي, lenp - 1);
  يادگيري_نقل (name + lenp - 1, p, len + 1);
  أرجع get_identifier (name);
}

/* Lookup REDUCTION_ID in the current scope, or create an artificial
   VAR_DECL, bind it into the current scope and return it.  */

وڻ
c_omp_reduction_decl (وڻ reduction_id)
{
  بنية c_binding *b = I_نشان_BINDING (reduction_id);
  إذا (b != عدم && B_اندريون_CURRENT_SCOPE (b))
    أرجع b->decl;

  وڻ decl = build_decl (BUILTINS_LOCATION, VAR_DECL,
			  reduction_id, integer_type_ڳنڍ);
  DECL_ARTIFICIAL (decl) = 1;
  DECL_EXTERNAL (decl) = 1;
  وڻ_STATIC (decl) = 1;
  وڻ_عوامي (decl) = 0;
  bind (reduction_id, decl, current_scope, سچ, خطأ, BUILTINS_LOCATION);
  أرجع decl;
}

/* Lookup REDUCTION_ID in the first scope where it has entry for TYPE.  */

وڻ
c_omp_reduction_lookup (وڻ reduction_id, وڻ type)
{
  بنية c_binding *b = I_نشان_BINDING (reduction_id);
  طالما (b)
    {
      وڻ t;
      لكل (t = DECL_INITIAL (b->decl); t; t = وڻ_CHAIN (t))
	إذا (comptypes (وڻ_PURPOSE (t), type))
	  أرجع وڻ_قدر (t);
      b = b->shadowed;
    }
  أرجع error_mark_ڳنڍ;
}

/* Helper function called via walk_tree, to diagnose invalid
   #pragma omp declare reduction combiners or initializers.  */

وڻ
c_check_omp_declare_reduction_r (وڻ *tp, صحيح *, فراغ *معلومات)
{
  وڻ *vars = (وڻ *) معلومات;
  إذا (SSA_VAR_P (*tp)
      && !DECL_ARTIFICIAL (*tp)
      && *tp != vars[0]
      && *tp != vars[1])
    {
      location_t loc = DECL_ذريعو_LOCATION (vars[0]);
      إذا (strcmp (IDENTIFIER_اشارو (DECL_NAME (vars[0])), "omp_out") == 0)
	error_at (loc, "%<#pragma omp declare reduction%> combiner refers to "
		       "variable %qD which is not %<omp_out%> nor %<omp_in%>",
		  *tp);
      وإلا
	error_at (loc, "%<#pragma omp declare reduction%> initializer refers "
		       "to variable %qD which is not %<omp_priv%> nor "
		       "%<omp_orig%>",
		  *tp);
      أرجع *tp;
    }
  أرجع NULL_وڻ;
}

/* Return identifier to look up for omp declare mapper.  */

وڻ
c_omp_mapper_id (وڻ mapper_id)
{
  ثابت حرف *p = عدم;

  ثابت حرف اڳياڙي[] = "omp declare mapper ";

  إذا (mapper_id == NULL_وڻ)
    p = "<default>";
  وإلا إذا (وڻ_ڪوڊ (mapper_id) == IDENTIFIER_ڳنڍ)
    p = IDENTIFIER_اشارو (mapper_id);
  وإلا
    أرجع error_mark_ڳنڍ;

  سائيز_t lenp = حجم (اڳياڙي);
  سائيز_t len = لڙي_ڊيگهه (p);
  حرف *name = XALLOCAVEC (حرف, lenp + len);
  يادگيري_نقل (name, اڳياڙي, lenp - 1);
  يادگيري_نقل (name + lenp - 1, p, len + 1);
  أرجع get_identifier (name);
}

/* Lookup MAPPER_ID in the current scope, or create an artificial
   VAR_DECL, bind it into the current scope and return it.  */

وڻ
c_omp_mapper_decl (وڻ mapper_id)
{
  بنية c_binding *b = I_نشان_BINDING (mapper_id);
  إذا (b != عدم && B_اندريون_CURRENT_SCOPE (b))
    أرجع b->decl;

  وڻ decl = build_decl (BUILTINS_LOCATION, VAR_DECL,
			  mapper_id, integer_type_ڳنڍ);
  DECL_ARTIFICIAL (decl) = 1;
  DECL_EXTERNAL (decl) = 1;
  وڻ_STATIC (decl) = 1;
  وڻ_عوامي (decl) = 0;
  bind (mapper_id, decl, current_scope, سچ, خطأ, BUILTINS_LOCATION);
  أرجع decl;
}

/* Lookup MAPPER_ID in the first scope where it has entry for TYPE.  */

وڻ
c_omp_mapper_lookup (وڻ mapper_id, وڻ type)
{
  إذا (!رڪارڊ_OR_UNION_TYPE_P (type))
    أرجع NULL_وڻ;

  mapper_id = c_omp_mapper_id (mapper_id);

  بنية c_binding *b = I_نشان_BINDING (mapper_id);
  طالما (b)
    {
      وڻ t;
      لكل (t = DECL_INITIAL (b->decl); t; t = وڻ_CHAIN (t))
	إذا (comptypes (وڻ_PURPOSE (t), type))
	  أرجع وڻ_قدر (t);
      b = b->shadowed;
    }
  أرجع NULL_وڻ;
}

/* For C, we record a pointer to the mapper itself without wrapping it in an
   artificial function or similar.  So, just return it.  */

وڻ
c_omp_ڪڍو_mapper_directive (وڻ mapper)
{
  أرجع mapper;
}

/* For now we can handle singleton OMP_ARRAY_SECTIONs with custom mappers, but
   nothing more complicated.  */

وڻ
c_omp_map_array_section (location_t loc, وڻ t)
{
  وڻ هيٺيون = وڻ_عمليو (t, 1);
  وڻ len = وڻ_عمليو (t, 2);

  إذا (len && integer_onep (len))
    {
      t = وڻ_عمليو (t, 0);

      إذا (!هيٺيون)
	هيٺيون = integer_zero_ڳنڍ;

      t = build_array_ref (loc, t, هيٺيون);
    }

  أرجع t;
}

/* Helper function for below function.  */

ساكن وڻ
c_omp_جاچ_mapper_bindings_r (وڻ *tp, صحيح *walk_subtrees, فراغ *ptr)
{
  وڻ t = *tp;
  omp_mapper_list<وڻ> *mlist = (omp_mapper_list<وڻ> *) ptr;
  وڻ aggr_type = NULL_وڻ;

  إذا (وڻ_ڪوڊ (t) == SIZEOF_اظهار
      || وڻ_ڪوڊ (t) == ALIGNOF_اظهار)
    {
      *walk_subtrees = 0;
      أرجع NULL_وڻ;
    }

  إذا (وڻ_ڪوڊ (t) == OMP_CLAUSE)
    أرجع NULL_وڻ;

  إذا (وڻ_ڪوڊ (t) == COMPONENT_REF
      && رڪارڊ_OR_UNION_TYPE_P (وڻ_TYPE (وڻ_عمليو (t, 0))))
    aggr_type = وڻ_TYPE (وڻ_عمليو (t, 0));
  وإلا إذا ((وڻ_ڪوڊ (t) == VAR_DECL
	    || وڻ_ڪوڊ (t) == PARM_DECL
	    || وڻ_ڪوڊ (t) == نتيجو_DECL)
	   && رڪارڊ_OR_UNION_TYPE_P (وڻ_TYPE (t)))
    aggr_type = وڻ_TYPE (t);

  إذا (aggr_type)
    {
      وڻ mapper_fn = c_omp_mapper_lookup (NULL_وڻ, aggr_type);
      إذا (mapper_fn)
	mlist->جوڙيو_mapper (NULL_وڻ, aggr_type, mapper_fn);
    }

  أرجع NULL_وڻ;
}

/* Scan an offload region's body, and record uses of struct- or union-typed
   variables.  Add _mapper_binding_ fake clauses to *CLAUSES_PTR.  */

فراغ
c_omp_جاچ_mapper_bindings (location_t loc, وڻ *clauses_ptr, وڻ body)
{
  hash_سيٽ<omp_name_type<وڻ>> ڏٺل_types;
  auto_vec<وڻ> mappers;
  omp_mapper_list<وڻ> mlist (&ڏٺل_types, &mappers);

  walk_وڻ_without_duplicates (&body, c_omp_جاچ_mapper_bindings_r, &mlist);

  بنانشان صحيح i;
  وڻ mapper;
  FOR_EACH_VEC_ELT (mappers, i, mapper)
    c_omp_ڳوليو_nested_mappers (&mlist, mapper);

  FOR_EACH_VEC_ELT (mappers, i, mapper)
    {
      إذا (mapper == error_mark_ڳنڍ)
	استمر;
      وڻ mapper_name = OMP_DECLARE_MAPPER_ID (mapper);
      وڻ decl = OMP_DECLARE_MAPPER_DECL (mapper);

      وڻ c = build_omp_clause (loc, OMP_CLAUSE__MAPPER_BINDING_);
      OMP_CLAUSE__MAPPER_BINDING__ID (c) = mapper_name;
      OMP_CLAUSE__MAPPER_BINDING__DECL (c) = decl;
      OMP_CLAUSE__MAPPER_BINDING__MAPPER (c) = mapper;

      OMP_CLAUSE_CHAIN (c) = *clauses_ptr;
      *clauses_ptr = c;
    }
}

منطقي
c_check_اندريون_current_scope (وڻ decl)
{
  بنية c_binding *b = I_نشان_BINDING (DECL_NAME (decl));
  أرجع b != عدم && B_اندريون_CURRENT_SCOPE (b);
}

/* Search for loop or switch names.  BEFORE_LABELS is last statement before
   possible labels and SWITCH_P true for a switch, false for loops.
   Searches through last statements in cur_stmt_list, stops when seeing
   BEFORE_LABELs, or statement other than LABEL_EXPR or CASE_LABEL_EXPR.
   Returns number of loop/switch names found and if any are found, sets
   *LAST_P to the canonical loop/switch name LABEL_DECL.  */

صحيح
c_get_loop_نالا (وڻ before_labels, منطقي switch_p, وڻ *آخري_p)
{
  *آخري_p = NULL_وڻ;
  إذا (!building_stmt_list_p ()
      || !STATEMENT_LIST_HAS_LABEL (cur_stmt_list)
      || before_labels == void_list_ڳنڍ)
    أرجع 0;

  صحيح ret = 0;
  وڻ آخري = NULL_وڻ;
  لكل (وڻ_stmt_iterator tsi = tsi_آخري (cur_stmt_list);
       !tsi_پڇاڙي_p (tsi); tsi_prev (&tsi))
    {
      وڻ stmt = tsi_stmt (tsi);
      إذا (stmt == before_labels)
	اكسر;
      وإلا إذا (وڻ_ڪوڊ (stmt) == LABEL_اظهار)
	{
	  إذا (آخري == NULL_وڻ)
	    آخري = LABEL_اظهار_LABEL (stmt);
	  وإلا
	    {
	      loop_نالا.محفوظ_ڌڪو (LABEL_اظهار_LABEL (stmt));
	      ++ret;
	    }
	}
      وإلا إذا (وڻ_ڪوڊ (stmt) != CASE_LABEL_اظهار
	       && وڻ_ڪوڊ (stmt) != DEBUG_BEGIN_STMT)
	اكسر;
    }
  إذا (آخري)
    {
      إذا (switch_p)
	C_DECL_SWITCH_NAME (آخري) = 1;
      وإلا
	C_DECL_LOOP_NAME (آخري) = 1;
      loop_نالا.محفوظ_ڌڪو (آخري);
      ++ret;
      إذا (loop_نالا.ڊيگهائي () > 16)
	{
	  بنانشان صحيح پهريون = 0, i;
	  وڻ l, c = NULL_وڻ;
	  إذا (loop_نالا_hash == عدم)
	    loop_نالا_hash = جديد decl_وڻ_map (ret);
	  وإلا
	    پهريون = loop_نالا.ڊيگهائي () - ret;
	  FOR_EACH_VEC_ELT_ابتو (loop_نالا, i, l)
	    {
	      إذا (C_DECL_LOOP_NAME (l) || C_DECL_SWITCH_NAME (l))
		c = l;
	      gcc_checking_assert (c);
	      loop_نالا_hash->put (l, c);
	      إذا (i == پهريون)
		اكسر;
	    }
	}
      *آخري_p = آخري;
    }
  أرجع ret;
}

/* Undoes what get_loop_names did when it returned NUM_NAMES.  */

فراغ
c_release_loop_نالا (صحيح انگ_نالا)
{
  بنانشان len = loop_نالا.ڊيگهائي () - انگ_نالا;
  إذا (loop_نالا_hash)
    {
      إذا (len <= 16)
	{
	  ميٽيو loop_نالا_hash;
	  loop_نالا_hash = عدم;
	}
      وإلا
	{
	  بنانشان صحيح i;
	  وڻ l;
	  FOR_EACH_VEC_ELT_ابتو (loop_نالا, i, l)
	    {
	      loop_نالا_hash->remove (l);
	      إذا (i == len)
		اكسر;
	    }
	}
    }
  loop_نالا.truncate (len);
}

/* Finish processing of break or continue identifier operand.
   NAME is the identifier operand of break or continue and
   IS_BREAK is true iff it is break stmt.  Returns the operand
   to use for BREAK_STMT or CONTINUE_STMT, either NULL_TREE or
   canonical loop/switch name LABEL_DECL.  */

وڻ
c_پڄاڻي_bc_name (location_t loc, وڻ name, منطقي is_break)
{
  وڻ label = NULL_وڻ, lab;
  pedwarn_c23 (loc, OPT_Wpedantic,
	       "ISO C does not support %qs statement with an identifier "
	       "operand before C2Y", is_break ? "break" : "continue");

  /* If I_LABEL_DECL is NULL or not from current function, don't waste time
     trying to find it among loop_names, it can't be there.  */
  إذا (!loop_نالا.is_خالي_جايون ()
      && current_function_scope
      && (lab = I_LABEL_DECL (name))
      && DECL_CONTEXT (lab) == current_function_decl)
    {
      بنانشان صحيح i;
      وڻ l, c = NULL_وڻ;
      إذا (loop_نالا_hash)
	{
	  إذا (وڻ *val = loop_نالا_hash->get (lab))
	    label = *val;
	}
      وإلا
	FOR_EACH_VEC_ELT_ابتو (loop_نالا, i, l)
	  {
	    إذا (C_DECL_LOOP_NAME (l) || C_DECL_SWITCH_NAME (l))
	      c = l;
	    gcc_checking_assert (c);
	    إذا (l == lab)
	      {
		label = c;
		اكسر;
	      }
	  }
      إذا (label)
	وڻ_استعمال_ٿيل (lab) = 1;
    }
  إذا (label == NULL_وڻ)
    {
      auto_vec<ثابت حرف *> candidates;
      بنانشان صحيح i;
      وڻ l, c = NULL_وڻ;
      FOR_EACH_VEC_ELT_ابتو (loop_نالا, i, l)
	{
	  إذا (C_DECL_LOOP_NAME (l) || C_DECL_SWITCH_NAME (l))
	    c = l;
	  gcc_checking_assert (c);
	  إذا (is_break || C_DECL_LOOP_NAME (c))
	    candidates.محفوظ_ڌڪو (IDENTIFIER_اشارو (DECL_NAME (l)));
	}
      ثابت حرف *hint = ڳوليو_closest_string (IDENTIFIER_اشارو (name),
					      &candidates);
      إذا (hint)
	{
	  gcc_rich_location richloc (loc);
	  richloc.جوڙيو_fixit_replace (hint);
	  إذا (is_break)
	    error_at (&richloc, "%<break%> statement operand %qE does not "
				"refer to a named loop or %<switch%>; "
				"did you mean %qs?", name, hint);
	  وإلا
	    error_at (&richloc, "%<continue%> statement operand %qE does not "
				"refer to a named loop; did you mean %qs?",
		      name, hint);
	}
      وإلا إذا (is_break)
	error_at (loc, "%<break%> statement operand %qE does not refer to a "
		       "named loop or %<switch%>", name);
      وإلا
	error_at (loc, "%<continue%> statement operand %qE does not refer to "
		       "a named loop", name);
    }
  وإلا إذا (!C_DECL_LOOP_NAME (label) && !is_break)
    {
      auto_diagnostic_گروهه d;
      error_at (loc, "%<continue%> statement operand %qE refers to a named "
		     "%<switch%>", name);
      inform (DECL_ذريعو_LOCATION (label), "%<switch%> name defined here");
      label = NULL_وڻ;
    }
  وإلا إذا (!C_DECL_LOOP_SWITCH_NAME_VALID (label))
    {
      auto_diagnostic_گروهه d;
      إذا (C_DECL_LOOP_NAME (label))
	{
	  error_at (loc, "%qs statement operand %qE refers to a loop outside "
			 "of its body", is_break ? "break" : "continue", name);
	  inform (DECL_ذريعو_LOCATION (label), "loop name defined here");
	}
      وإلا
	{
	  error_at (loc, "%<break%> statement operand %qE refers to a "
			 "%<switch%> outside of its body", name);
	  inform (DECL_ذريعو_LOCATION (label),
		  "%<switch%> name defined here");
	}
      label = NULL_وڻ;
    }
  وإلا إذا (label == loop_نالا.آخري () && (اندريون_statement & اندريون_NAMED_STMT) != 0)
    /* If it is just a fancy reference to the innermost construct, handle it
       just like break; or continue; though tracking cheaply what is the
       innermost loop for continue when nested in switches would require
       another global variable and updating it.  */
    label = NULL_وڻ;
  وإلا
    C_DECL_LOOP_SWITCH_NAME_استعمال_ٿيل (label) = 1;
  أرجع label;
}

#ضمن "gt-c-c-decl.h"
