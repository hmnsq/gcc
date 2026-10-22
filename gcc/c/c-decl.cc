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

#அந்தர்பாவ "config.h"
#define INCLUDE_STRING
#அந்தர்பாவ "system.h"
#அந்தர்பாவ "coretypes.h"
#அந்தர்பாவ "target.h"
#அந்தர்பாவ "function.h"
#அந்தர்பாவ "c-tree.h"
#அந்தர்பாவ "timevar.h"
#அந்தர்பாவ "stringpool.h"
#அந்தர்பாவ "cgraph.h"
#அந்தர்பாவ "intl.h"
#அந்தர்பாவ "print-tree.h"
#அந்தர்பாவ "stor-layout.h"
#அந்தர்பாவ "varasm.h"
#அந்தர்பாவ "attribs.h"
#அந்தர்பாவ "toplev.h"
#அந்தர்பாவ "debug.h"
#அந்தர்பாவ "c-family/c-objc.h"
#அந்தர்பாவ "c-family/c-pragma.h"
#அந்தர்பாவ "c-family/c-ubsan.h"
#அந்தர்பாவ "c-lang.h"
#அந்தர்பாவ "langhooks.h"
#அந்தர்பாவ "tree-iterator.h"
#அந்தர்பாவ "dumpfile.h"
#அந்தர்பாவ "plugin.h"
#அந்தர்பாவ "c-family/c-ada-spec.h"
#அந்தர்பாவ "builtins.h"
#அந்தர்பாவ "spellcheck-tree.h"
#அந்தர்பாவ "gcc-rich-location.h"
#அந்தர்பாவ "asan.h"
#அந்தர்பாவ "c-family/name-hint.h"
#அந்தர்பாவ "c-family/known-headers.h"
#அந்தர்பாவ "c-family/c-spellcheck.h"
#அந்தர்பாவ "context.h"  /* For 'g'.  */
#அந்தர்பாவ "omp-general.h"
#அந்தர்பாவ "omp-offload.h"  /* For offload_vars.  */
#அந்தர்பாவ "c-parser.h"
#அந்தர்பாவ "gcc-urlifier.h"

#அந்தர்பாவ "tree-pretty-print.h"

/* In grokdeclarator, distinguish syntactic contexts of declarators.  */
எண்ணிக்கை decl_context
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

எண்ணிக்கை deprecated_states {
  DEPRECATED_NORMAL,
  DEPRECATED_SUPPRESS,
  UNAVAILABLE_DEPRECATED_SUPPRESS
};


/* Nonzero if we have seen an invalid cross reference
   to a struct, union, or enum, but not yet printed the message.  */
மரம் pending_invalid_xref;

/* File and line to appear in the eventual error message.  */
location_t pending_invalid_xref_location;

/* The file and line that the prototype came from if this is an
   old-style definition; used for diagnostics in
   store_parm_decls_oldstyle.  */

நிலையான location_t current_function_prototype_locus;

/* Whether this prototype was built-in.  */

நிலையான தருக்க current_function_prototype_built_in;

/* The argument type information of this prototype.  */

நிலையான மரம் current_function_prototype_arg_types;

/* The argument information structure for the function currently being
   defined.  */

நிலையான கட்டமைப்பு c_arg_info *current_function_arg_info;

/* The obstack on which parser and related data structures, which are
   not live beyond their top-level declaration or definition, are
   allocated.  */
கட்டமைப்பு obstack parser_obstack;

/* The current statement tree.  */

நிலையான GTY(()) கட்டமைப்பு stmt_மரம்_s c_stmt_மரம்;

/* Zero if we are not in an iteration or switch statement, otherwise
   a bitmask.  See bitmask definitions in c-tree.h.  */
unsigned எழுத்து in_statement;

/* A list of decls to be made automatically visible in each file scope.  */
நிலையான GTY(()) மரம் visible_builtins;

/* Set to 0 at beginning of a function definition, set to 1 if
   a return statement that specifies a return value is seen.  */

முழு current_function_returns_மதிப்பு;

/* Set to 0 at beginning of a function definition, set to 1 if
   a return statement with no argument is seen.  */

முழு current_function_returns_null;

/* Set to 0 at beginning of a function definition, set to 1 if
   a call to a noreturn function is seen.  */

முழு current_function_returns_abnormally;

/* Set to nonzero by `grokdeclarator' for a function
   whose return type is defaulted, if warnings for this are desired.  */

நிலையான முழு warn_about_return_type;

/* Nonzero when the current toplevel function contains a declaration
   of a nested function which is never defined.  */

நிலையான தருக்க undef_nested_function;

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
நிலையான vec<மரம்> loop_names;

/* Hash table mapping LABEL_DECLs to the canonical LABEL_DECLs if LOOP_NAMES
   vector becomes too long.  */
நிலையான decl_மரம்_map *loop_names_hash;

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

கட்டமைப்பு GTY((chain_next ("%h.prev"))) c_binding {
  ஒன்றிப்பு GTY(()) {		/* first so GTY desc can use decl */
    மரம் GTY((tag ("0"))) type; /* the type in this scope */
    கட்டமைப்பு c_label_vars * GTY((tag ("1"))) label; /* for warnings */
  } GTY((desc ("TREE_CODE (%0.decl) == LABEL_DECL"))) u;
  மரம் decl;			/* the decl bound */
  மரம் id;			/* the identifier it's bound to */
  கட்டமைப்பு c_binding *prev;	/* the previous decl in this scope */
  கட்டமைப்பு c_binding *shadowed;	/* the innermost decl shadowed by this one */
  unsigned முழு depth : 28;      /* depth of this scope */
  தருக்க invisible : 1;  /* normal lookup should ignore this binding */
  தருக்க nested : 1;     /* do not set DECL_CONTEXT when popping */
  தருக்க inner_comp : 1; /* incomplete array completed in inner scope */
  தருக்க in_struct : 1;	/* currently defined as struct field */
  location_t locus;		/* location for nested bindings */
};
#define B_IN_SCOPE(b1, b2) ((b1)->depth == (b2)->depth)
#define B_IN_CURRENT_SCOPE(b) ((b)->depth == current_scope->depth)
#define B_IN_FILE_SCOPE(b) ((b)->depth == 1 /*file_scope->depth*/)
#define B_IN_EXTERNAL_SCOPE(b) ((b)->depth == 0 /*external_scope->depth*/)

/* Each C symbol points to three linked lists of c_binding structures.
   These describe the values of the identifier in the three different
   namespaces defined by the language.  */

கட்டமைப்பு GTY(()) lang_identifier {
  கட்டமைப்பு c_common_identifier common_id;
  கட்டமைப்பு c_binding *குறியீடு_binding; /* vars, funcs, constants, typedefs */
  கட்டமைப்பு c_binding *tag_binding;    /* struct/union/enum tags */
  கட்டமைப்பு c_binding *label_binding;  /* labels */
};

/* Validate c-lang.cc's assumptions.  */
வெளி எழுத்து C_SIZEOF_STRUCT_LANG_IDENTIFIER_isnt_accurate
[(அளவு(கட்டமைப்பு lang_identifier) == C_SIZEOF_STRUCT_LANG_IDENTIFIER) ? 1 : -1];

/* The binding oracle; see c-tree.h.  */
வெறுமை (*c_binding_oracle) (எண்ணிக்கை c_oracle_request, மரம் identifier);

/* This flag is set on an identifier if we have previously asked the
   binding oracle for this identifier's symbol binding.  */
#define I_குறியீடு_CHECKED(முனை) \
  (மரம்_LANG_FLAG_4 (IDENTIFIER_முனை_CHECK (முனை)))

நிலையான உள்வரி கட்டமைப்பு c_binding* *
i_குறியீடு_binding (மரம் முனை)
{
  கட்டமைப்பு lang_identifier *lid
    = (கட்டமைப்பு lang_identifier *) IDENTIFIER_முனை_CHECK (முனை);

  எனில் (lid->குறியீடு_binding == வெற்று
      && c_binding_oracle != வெற்று
      && !I_குறியீடு_CHECKED (முனை))
    {
      /* Set the "checked" flag first, to avoid infinite recursion
	 when the binding oracle calls back into gcc.  */
      I_குறியீடு_CHECKED (முனை) = 1;
      c_binding_oracle (C_ORACLE_குறியீடு, முனை);
    }

  திரும்பு &lid->குறியீடு_binding;
}

#define I_குறியீடு_BINDING(முனை) (*i_குறியீடு_binding (முனை))

#define I_குறியீடு_DECL(முனை) \
 (I_குறியீடு_BINDING(முனை) ? I_குறியீடு_BINDING(முனை)->decl : 0)

/* This flag is set on an identifier if we have previously asked the
   binding oracle for this identifier's tag binding.  */
#define I_TAG_CHECKED(முனை) \
  (மரம்_LANG_FLAG_5 (IDENTIFIER_முனை_CHECK (முனை)))

நிலையான உள்வரி கட்டமைப்பு c_binding **
i_tag_binding (மரம் முனை)
{
  கட்டமைப்பு lang_identifier *lid
    = (கட்டமைப்பு lang_identifier *) IDENTIFIER_முனை_CHECK (முனை);

  எனில் (lid->tag_binding == வெற்று
      && c_binding_oracle != வெற்று
      && !I_TAG_CHECKED (முனை))
    {
      /* Set the "checked" flag first, to avoid infinite recursion
	 when the binding oracle calls back into gcc.  */
      I_TAG_CHECKED (முனை) = 1;
      c_binding_oracle (C_ORACLE_TAG, முனை);
    }

  திரும்பு &lid->tag_binding;
}

#define I_TAG_BINDING(முனை) (*i_tag_binding (முனை))

#define I_TAG_DECL(முனை) \
 (I_TAG_BINDING(முனை) ? I_TAG_BINDING(முனை)->decl : 0)

/* This flag is set on an identifier if we have previously asked the
   binding oracle for this identifier's label binding.  */
#define I_LABEL_CHECKED(முனை) \
  (மரம்_LANG_FLAG_6 (IDENTIFIER_முனை_CHECK (முனை)))

நிலையான உள்வரி கட்டமைப்பு c_binding **
i_label_binding (மரம் முனை)
{
  கட்டமைப்பு lang_identifier *lid
    = (கட்டமைப்பு lang_identifier *) IDENTIFIER_முனை_CHECK (முனை);

  எனில் (lid->label_binding == வெற்று
      && c_binding_oracle != வெற்று
      && !I_LABEL_CHECKED (முனை))
    {
      /* Set the "checked" flag first, to avoid infinite recursion
	 when the binding oracle calls back into gcc.  */
      I_LABEL_CHECKED (முனை) = 1;
      c_binding_oracle (C_ORACLE_LABEL, முனை);
    }

  திரும்பு &lid->label_binding;
}

#define I_LABEL_BINDING(முனை) (*i_label_binding (முனை))

#define I_LABEL_DECL(முனை) \
 (I_LABEL_BINDING(முனை) ? I_LABEL_BINDING(முனை)->decl : 0)

/* Used by C_TOKEN_VEC tree.  */
கட்டமைப்பு GTY (()) c_மரம்_token_vec {
  கட்டமைப்பு மரம்_base base;
  vec<c_token, va_gc> *tokens;
};

STATIC_ASSERT (அளவு (c_மரம்_token_vec) == அளவு (c_மரம்_token_vec_struct));
STATIC_ASSERT (offsetof (c_மரம்_token_vec, tokens)
	       == offsetof (c_மரம்_token_vec_struct, tokens));

/* The resulting tree type.  */

ஒன்றிப்பு GTY((desc ("TREE_CODE (&%h.generic) == IDENTIFIER_NODE + 2 * (TREE_CODE (&%h.generic) == C_TOKEN_VEC)"),
       chain_next ("(union lang_tree_node *) c_tree_chain_next (&%h.generic)"))) lang_மரம்_முனை
 {
  ஒன்றிப்பு மர_முனை GTY ((tag ("0"),
			desc ("tree_node_structure (&%h)")))
    generic;
  கட்டமைப்பு lang_identifier GTY ((tag ("1"))) identifier;
  கட்டமைப்பு c_மரம்_token_vec GTY ((tag ("2"))) c_token_vec;
};

/* Langhook for tree_size.  */
size_t
c_மரம்_size (எண்ணிக்கை மரம்_code code)
{
  gcc_checking_assert (code >= இலக்கம்_மரம்_CODES);
  தேர்வு (code)
    {
    நிலை C_TOKEN_VEC: திரும்பு அளவு (c_மரம்_token_vec);
    இயல்பு:
      தேர்வு (மரம்_CODE_CLASS (code))
	{
	நிலை tcc_declaration: திரும்பு அளவு (மரம்_decl_non_common);
	நிலை tcc_type: திரும்பு அளவு (மரம்_type_non_common);
	இயல்பு: gcc_unreachable ();
	}
    }
}

/* Track bindings and other things that matter for goto warnings.  For
   efficiency, we do not gather all the decls at the point of
   definition.  Instead, we point into the bindings structure.  As
   scopes are popped, we update these structures and gather the decls
   that matter at that time.  */

கட்டமைப்பு GTY(()) c_spot_bindings {
  /* The currently open scope which holds bindings defined when the
     label was defined or the goto statement was found.  */
  கட்டமைப்பு c_scope *scope;
  /* The bindings in the scope field which were defined at the point
     of the label or goto.  This lets us look at older or newer
     bindings in the scope, as appropriate.  */
  கட்டமைப்பு c_binding *bindings_in_scope;
  /* The number of statement expressions that have started since this
     label or goto statement was defined.  This is zero if we are at
     the same statement expression level.  It is positive if we are in
     a statement expression started since this spot.  It is negative
     if this spot was in a statement expression and we have left
     it.  */
  முழு stmt_exprs;
  /* Whether we started in a statement expression but are no longer in
     it.  This is set to true if stmt_exprs ever goes negative.  */
  தருக்க இடது_stmt_கோவை;
};

/* This structure is used to keep track of bindings seen when a goto
   statement is defined.  This is only used if we see the goto
   statement before we see the label.  */

கட்டமைப்பு GTY(()) c_goto_bindings {
  /* The location of the goto statement.  */
  location_t loc;
  /* The bindings of the goto statement.  */
  கட்டமைப்பு c_spot_bindings goto_bindings;
};

வகைவரை கட்டமைப்பு c_goto_bindings *c_goto_bindings_p;

/* The additional information we keep track of for a label binding.
   These fields are updated as scopes are popped.  */

கட்டமைப்பு GTY(()) c_label_vars {
  /* The shadowed c_label_vars, when one label shadows another (which
     can only happen using a __label__ declaration).  */
  கட்டமைப்பு c_label_vars *shadowed;
  /* The bindings when the label was defined.  */
  கட்டமைப்பு c_spot_bindings label_bindings;
  /* A list of decls that we care about: decls about which we should
     warn if a goto branches to this label from later in the function.
     Decls are added to this list as scopes are popped.  We only add
     the decls that matter.  */
  vec<மரம், va_gc> *decls_in_scope;
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


கட்டமைப்பு GTY((chain_next ("%h.outer"))) c_scope {
  /* The scope containing this one.  */
  கட்டமைப்பு c_scope *outer;

  /* The next outermost function scope.  */
  கட்டமைப்பு c_scope *outer_function;

  /* All bindings in this scope.  */
  கட்டமைப்பு c_binding *bindings;

  /* For each scope (except the global one), a chain of BLOCK nodes
     for all the scopes that were entered and exited one level down.  */
  மரம் blocks;
  மரம் blocks_last;

  /* The depth of this scope.  Used to keep the ->shadowed chain of
     bindings sorted innermost to outermost.  */
  unsigned முழு depth : 28;

  /* True if we are currently filling this scope with parameter
     declarations.  */
  தருக்க parm_flag : 1;

  /* True if we saw [*] in this scope.  Used to give an error messages
     if these appears in a function definition.  */
  தருக்க had_vla_unspec : 1;

  /* True if we parsed a list of forward parameter decls in this scope.  */
  தருக்க had_forward_parm_decls : 1;

  /* True if this is the outermost block scope of a function body.
     This scope contains the parameters, the local variables declared
     in the outermost block, and all the labels (except those in
     nested functions, or declared at block scope with __label__).  */
  தருக்க function_body : 1;

  /* True means make a BLOCK for this scope no matter what.  */
  தருக்க keep : 1;

  /* True means that an unsuffixed float constant is _Decimal64.  */
  தருக்க float_const_decimal64 : 1;

  /* True if this scope has any label bindings.  This is used to speed
     up searching for labels when popping scopes, particularly since
     labels are normally only found at function scope.  */
  தருக்க has_label_bindings : 1;

  /* True if we should issue a warning if a goto statement crosses any
     of the bindings.  We still need to check the list of bindings to
     find the specific ones we need to warn about.  This is true if
     decl_jump_unsafe would return true for any of the bindings.  This
     is used to avoid looping over all the bindings unnecessarily.  */
  தருக்க has_jump_unsafe_decl : 1;
};

/* The scope currently in effect.  */

நிலையான GTY(()) கட்டமைப்பு c_scope *current_scope;

/* The innermost function scope.  Ordinary (not explicitly declared)
   labels, bindings to error_mark_node, and the lazily-created
   bindings of __func__ and its friends get this scope.  */

நிலையான GTY(()) கட்டமைப்பு c_scope *current_function_scope;

/* The C file scope.  This is reset for each input translation unit.  */

நிலையான GTY(()) கட்டமைப்பு c_scope *file_scope;

/* The outermost scope.  This is used for all declarations with
   external linkage, and only these, hence the name.  */

நிலையான GTY(()) கட்டமைப்பு c_scope *external_scope;

/* A chain of c_scope structures awaiting reuse.  */

நிலையான GTY((deletable)) கட்டமைப்பு c_scope *scope_freelist;

/* A chain of c_binding structures awaiting reuse.  */

நிலையான GTY((deletable)) கட்டமைப்பு c_binding *binding_freelist;

/* Append VAR to LIST in scope SCOPE.  */
#define SCOPE_LIST_APPEND(scope, list, decl) செய் {	\
  கட்டமைப்பு c_scope *s_ = (scope);				\
  மரம் d_ = (decl);					\
  எனில் (s_->list##_last)					\
    BLOCK_CHAIN (s_->list##_last) = d_;			\
  இல்லையெனில்							\
    s_->list = d_;					\
  s_->list##_last = d_;					\
} போது (0)

/* Concatenate FROM in scope FSCOPE onto TO in scope TSCOPE.  */
#define SCOPE_LIST_CONCAT(tscope, to, fscope, from) செய் {	\
  கட்டமைப்பு c_scope *t_ = (tscope);				\
  கட்டமைப்பு c_scope *f_ = (fscope);				\
  எனில் (t_->to##_last)						\
    BLOCK_CHAIN (t_->to##_last) = f_->from;			\
  இல்லையெனில்								\
    t_->to = f_->from;						\
  t_->to##_last = f_->from##_last;				\
} போது (0)

/* A c_inline_static structure stores details of a static identifier
   referenced in a definition of a function that may be an inline
   definition if no subsequent declaration of that function uses
   "extern" or does not use "inline".  */

கட்டமைப்பு GTY((chain_next ("%h.next"))) c_inline_static {
  /* The location for a diagnostic.  */
  location_t location;

  /* The function that may be an inline definition.  */
  மரம் function;

  /* The object or function referenced.  */
  மரம் static_decl;

  /* What sort of reference this is.  */
  எண்ணிக்கை c_inline_static_type type;

  /* The next such structure or NULL.  */
  கட்டமைப்பு c_inline_static *next;
};

/* List of static identifiers used or referenced in functions that may
   be inline definitions.  */
நிலையான GTY(()) கட்டமைப்பு c_inline_static *c_inline_statics;

/* True means unconditionally make a BLOCK for the next scope pushed.  */

நிலையான தருக்க keep_next_level_flag;

/* True means the next call to push_scope will be the outermost scope
   of a function body, so do not push a new scope, merely cease
   expecting parameter decls.  */

நிலையான தருக்க next_is_function_body;

/* A vector of pointers to c_binding structures.  */

வகைவரை கட்டமைப்பு c_binding *c_binding_ptr;

/* Information that we keep for a struct or union while it is being
   parsed.  */

வகுப்பு c_struct_parse_info
{
பொது:
  /* If warn_cxx_compat, a list of types defined within this
     struct.  */
  auto_vec<மரம்> struct_types;
  /* If warn_cxx_compat, a list of field names which have bindings,
     and which are defined in this struct, but which are not defined
     in any enclosing struct.  This is used to clear the in_struct
     field of the c_bindings structure.  */
  auto_vec<c_binding_ptr> fields;
  /* If warn_cxx_compat, a list of typedef names used when defining
     fields in this struct.  */
  auto_vec<மரம்> typedefs_seen;
  /* The location of a previous definition of this struct.  */
  location_t refloc;
};


/* Hash table for structs and unions.  */
கட்டமைப்பு c_struct_hasher : ggc_ptr_hash<மர_முனை>
{
  நிலையான hashval_t hash (மரம் t);
  நிலையான தருக்க equal (மரம், மரம்);
};

/* Hash an RECORD OR UNION.  */
hashval_t
c_struct_hasher::hash (மரம் type)
{
  inchash::hash hstate;

  hstate.add_int (மரம்_CODE (type));
  மரம் tag = c_type_tag (type);
  hstate.add_object (tag);

  திரும்பு hstate.end ();
}

/* Compare two RECORD or UNION types.  */
தருக்க
c_struct_hasher::equal (மரம் t1,  மரம் t2)
{
  திரும்பு comptypes_equiv_p (t1, t2);
}

/* All tagged typed so that TYPE_CANONICAL can be set correctly.  */
நிலையான GTY (()) hash_table<c_struct_hasher> *c_struct_htab;

/* Information for the struct or union currently being parsed, or
   NULL if not parsing a struct or union.  */
நிலையான வகுப்பு c_struct_parse_info *struct_parse_info;

/* Forward declarations.  */
நிலையான மரம் lookup_name_in_scope (மரம், கட்டமைப்பு c_scope *);
நிலையான மரம் c_make_fname_decl (location_t, மரம், முழு);
நிலையான மரம் grokdeclarator (மாறிலி கட்டமைப்பு c_declarator *,
			    கட்டமைப்பு c_declspecs *,
			    எண்ணிக்கை decl_context, தருக்க, மரம் *, மரம் *, மரம் *,
			    தருக்க *, எண்ணிக்கை deprecated_states);
நிலையான மரம் grokparms (கட்டமைப்பு c_arg_info *, தருக்க);
நிலையான வெறுமை layout_array_type (மரம்);
நிலையான மாறிலி எழுத்து *header_for_builtin_fn (மரம்);

/* T is a statement.  Add it to the statement-tree.  This is the
   C/ObjC version--C++ has a slightly different version of this
   function.  */

மரம்
add_stmt (மரம் t)
{
  எண்ணிக்கை மரம்_code code = மரம்_CODE (t);

  எனில் (CAN_HAVE_LOCATION_P (t) && code != LABEL_கோவை)
    {
      எனில் (!கோவை_HAS_LOCATION (t))
	SET_கோவை_LOCATION (t, உள்ளீடு_location);
    }

  /* Add T to the statement-tree.  Non-side-effect statements need to be
     recorded during statement expressions.  */
  எனில் (!building_stmt_list_p ())
    தள்ளு_stmt_list ();

  எனில் (code == LABEL_கோவை || code == CASE_LABEL_கோவை)
    STATEMENT_LIST_HAS_LABEL (cur_stmt_list) = 1;

  append_to_statement_list_force (t, &cur_stmt_list);

  திரும்பு t;
}





/* Return true if we will want to say something if a goto statement
   crosses DECL.  */

நிலையான தருக்க
decl_jump_unsafe (மரம் decl)
{
  எனில் (error_operand_p (decl))
    திரும்பு பொய்;

  /* Don't warn for compound literals.  If a goto statement crosses
     their initialization, it should cross also all the places where
     the complit is used or where the complit address might be saved
     into some variable, so code after the label to which goto jumps
     should not be able to refer to the compound literal.  */
  எனில் (VAR_P (decl) && C_DECL_COMPOUND_LITERAL_P (decl))
    திரும்பு பொய்;

  எனில் (flag_openmp
      && VAR_P (decl)
      && lookup_attribute ("omp allocate", DECL_ATTRIBUTES (decl)))
    திரும்பு உண்மை;

  /* Always warn about crossing variably modified types.  */
  எனில் ((VAR_P (decl) || மரம்_CODE (decl) == TYPE_DECL)
      && c_type_variably_modified_p (மரம்_TYPE (decl)))
    திரும்பு உண்மை;

  /* Otherwise, only warn if -Wgoto-misses-init and this is an
     initialized automatic decl.  */
  எனில் (warn_jump_misses_init
      && VAR_P (decl)
      && !மரம்_STATIC (decl)
      && DECL_INITIAL (decl) != NULL_மரம்)
    திரும்பு உண்மை;

  திரும்பு பொய்;
}


வெறுமை
c_print_identifier (FILE *file, மரம் முனை, முழு indent)
{
  வெறுமை (*save) (எண்ணிக்கை c_oracle_request, மரம் identifier);

  /* Temporarily hide any binding oracle.  Without this, calls to
     debug_tree from the debugger will end up calling into the oracle,
     making for a confusing debug session.  As the oracle isn't needed
     here for normal operation, it's simplest to suppress it.  */
  save = c_binding_oracle;
  c_binding_oracle = வெற்று;

  print_முனை (file, "symbol", I_குறியீடு_DECL (முனை), indent + 4);
  print_முனை (file, "tag", I_TAG_DECL (முனை), indent + 4);
  print_முனை (file, "label", I_LABEL_DECL (முனை), indent + 4);
  எனில் (C_IS_RESERVED_WORD (முனை) && C_RID_CODE (முனை) != RID_CXX_COMPAT_WARN)
    {
      மரம் rid = ridpointers[C_RID_CODE (முனை)];
      indent_to (file, indent + 4);
      fprintf (file, "rid " HOST_PTR_PRINTF " \"%s\"",
	       (வெறுமை *) rid, IDENTIFIER_POINTER (rid));
    }

  c_binding_oracle = save;
}

/* Establish that the scope contains declarations that are sensitive to
   jumps that cross a binding.  Together with decl_jump_unsafe, this is
   used to diagnose such jumps.  */
வெறுமை
c_mark_decl_jump_unsafe_in_current_scope ()
{
  current_scope->has_jump_unsafe_decl = 1;
}

/* Establish a binding between NAME, an IDENTIFIER_NODE, and DECL,
   which may be any of several kinds of DECL or TYPE or error_mark_node,
   in the scope SCOPE.  */
நிலையான வெறுமை
bind (மரம் name, மரம் decl, கட்டமைப்பு c_scope *scope, தருக்க invisible,
      தருக்க nested, location_t locus)
{
  கட்டமைப்பு c_binding *b, **here;

  எனில் (binding_freelist)
    {
      b = binding_freelist;
      binding_freelist = b->prev;
    }
  இல்லையெனில்
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

  b->u.type = வெற்று;

  b->prev = scope->bindings;
  scope->bindings = b;

  எனில் (decl_jump_unsafe (decl))
    scope->has_jump_unsafe_decl = 1;

  எனில் (!name)
    திரும்பு;

  தேர்வு (மரம்_CODE (decl))
    {
    நிலை LABEL_DECL:     here = &I_LABEL_BINDING (name);   நிறுத்து;
    நிலை ENUMERAL_TYPE:
    நிலை UNION_TYPE:
    நிலை RECORD_TYPE:    here = &I_TAG_BINDING (name);     நிறுத்து;
    நிலை VAR_DECL:
    நிலை FUNCTION_DECL:
    நிலை TYPE_DECL:
    நிலை CONST_DECL:
    நிலை PARM_DECL:
    நிலை ERROR_MARK:     here = &I_குறியீடு_BINDING (name);  நிறுத்து;

    இயல்பு:
      gcc_unreachable ();
    }

  /* Locate the appropriate place in the chain of shadowed decls
     to insert this binding.  Normally, scope == current_scope and
     this does nothing.  */
  போது (*here && (*here)->depth > scope->depth)
    here = &(*here)->shadowed;

  b->shadowed = *here;
  *here = b;
}

/* Clear the binding structure B, stick it on the binding_freelist,
   and return the former value of b->prev.  This is used by pop_scope
   and get_parm_info to iterate destructively over all the bindings
   from a given scope.  */
நிலையான கட்டமைப்பு c_binding *
free_binding_and_advance (கட்டமைப்பு c_binding *b)
{
  கட்டமைப்பு c_binding *prev = b->prev;

  memset (b, 0, அளவு (கட்டமைப்பு c_binding));
  b->prev = binding_freelist;
  binding_freelist = b;

  திரும்பு prev;
}

/* Bind a label.  Like bind, but skip fields which aren't used for
   labels, and add the LABEL_VARS value.  */
நிலையான வெறுமை
bind_label (மரம் name, மரம் label, கட்டமைப்பு c_scope *scope,
	    கட்டமைப்பு c_label_vars *label_vars)
{
  கட்டமைப்பு c_binding *b;

  bind (name, label, scope, /*invisible=*/பொய், /*nested=*/பொய்,
	UNKNOWN_LOCATION);

  scope->has_label_bindings = உண்மை;

  b = scope->bindings;
  gcc_assert (b->decl == label);
  label_vars->shadowed = b->u.label;
  b->u.label = label_vars;
}

/* Hook called at end of compilation to assume 1 elt
   for a file-scope tentative array defn that wasn't complete before.  */

வெறுமை
c_finish_incomplete_decl (மரம் decl)
{
  எனில் (VAR_P (decl))
    {
      மரம் type = மரம்_TYPE (decl);
      எனில் (type != error_mark_முனை
	  && மரம்_CODE (type) == ARRAY_TYPE
	  && !DECL_EXTERNAL (decl)
	  && TYPE_DOMAIN (type) == NULL_மரம்)
	{
	  எனில் (flag_isoc2y && !மரம்_PUBLIC (decl))
	    error_at (DECL_SOURCE_LOCATION (decl),
		      "array size missing in %q+D", decl);
	  இல்லையெனில்
	    warning_at (DECL_SOURCE_LOCATION (decl),
			0, "array %q+D assumed to have one element", decl);

	  complete_array_type (&மரம்_TYPE (decl), NULL_மரம், உண்மை);

	  relayout_decl (decl);
	}
    }
}

/* Record that inline function FUNC contains a reference (location
   LOC) to static DECL (file-scope or function-local according to
   TYPE).  */

வெறுமை
record_inline_static (location_t loc, மரம் func, மரம் decl,
		      எண்ணிக்கை c_inline_static_type type)
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

நிலையான வெறுமை
check_inline_statics (வெறுமை)
{
  கட்டமைப்பு c_inline_static *csi;
  க்கு (csi = c_inline_statics; csi; csi = csi->next)
    {
      எனில் (DECL_EXTERNAL (csi->function))
	தேர்வு (csi->type)
	  {
	  நிலை csi_internal:
	    pedwarn (csi->location, 0,
		     "%qD is static but used in inline function %qD "
		     "which is not static", csi->static_decl, csi->function);
	    நிறுத்து;
	  நிலை csi_modifiable:
	    pedwarn (csi->location, 0,
		     "%q+D is static but declared in inline function %qD "
		     "which is not static", csi->static_decl, csi->function);
	    நிறுத்து;
	  இயல்பு:
	    gcc_unreachable ();
	  }
    }
  c_inline_statics = வெற்று;
}

/* Fill in a c_spot_bindings structure.  If DEFINING is true, set it
   for the current state, otherwise set it to uninitialized.  */

நிலையான வெறுமை
set_spot_bindings (கட்டமைப்பு c_spot_bindings *p, தருக்க defining)
{
  எனில் (defining)
    {
      p->scope = current_scope;
      p->bindings_in_scope = current_scope->bindings;
    }
  இல்லையெனில்
    {
      p->scope = வெற்று;
      p->bindings_in_scope = வெற்று;
    }
  p->stmt_exprs = 0;
  p->இடது_stmt_கோவை = பொய்;
}

/* Update spot bindings P as we pop out of SCOPE.  Return true if we
   should push decls for a label.  */

நிலையான தருக்க
update_spot_bindings (கட்டமைப்பு c_scope *scope, கட்டமைப்பு c_spot_bindings *p)
{
  எனில் (p->scope != scope)
    {
      /* This label or goto is defined in some other scope, or it is a
	 label which is not yet defined.  There is nothing to
	 update.  */
      திரும்பு பொய்;
    }

  /* Adjust the spot bindings to refer to the bindings already defined
     in the enclosing scope.  */
  p->scope = scope->outer;
  p->bindings_in_scope = p->scope->bindings;

  திரும்பு உண்மை;
}

/* The Objective-C front-end often needs to determine the current scope.  */

வெறுமை *
objc_get_current_scope (வெறுமை)
{
  திரும்பு current_scope;
}

/* The following function is used only by Objective-C.  It needs to live here
   because it accesses the innards of c_scope.  */

வெறுமை
objc_mark_locals_volatile (வெறுமை *enclosing_blk)
{
  கட்டமைப்பு c_scope *scope;
  கட்டமைப்பு c_binding *b;

  க்கு (scope = current_scope;
       scope && scope != enclosing_blk;
       scope = scope->outer)
    {
      க்கு (b = scope->bindings; b; b = b->prev)
	objc_volatilize_decl (b->decl);

      /* Do not climb up past the current function.  */
      எனில் (scope->function_body)
	நிறுத்து;
    }
}

/* Return true if we are in the global binding level.  */

தருக்க
global_bindings_p (வெறுமை)
{
  திரும்பு current_scope == file_scope;
}

/* Return true if we're declaring parameters in an old-style function
   declaration.  */

தருக்க
old_style_parameter_scope (வெறுமை)
{
  /* If processing parameters and there is no function statement list, we
   * have an old-style function declaration.  */
  திரும்பு (current_scope->parm_flag && !DECL_SAVED_மரம் (current_function_decl));
}

வெறுமை
keep_next_level (வெறுமை)
{
  keep_next_level_flag = உண்மை;
}

/* Set the flag for the FLOAT_CONST_DECIMAL64 pragma being ON.  */

வெறுமை
set_float_const_decimal64 (வெறுமை)
{
  current_scope->float_const_decimal64 = உண்மை;
}

/* Clear the flag for the FLOAT_CONST_DECIMAL64 pragma.  */

வெறுமை
clear_float_const_decimal64 (வெறுமை)
{
  current_scope->float_const_decimal64 = பொய்;
}

/* Return nonzero if an unsuffixed float constant is _Decimal64.  */

தருக்க
float_const_decimal64_p (வெறுமை)
{
  திரும்பு current_scope->float_const_decimal64;
}

/* Identify this scope as currently being filled with parameters.  */

வெறுமை
declare_parm_level (வெறுமை)
{
  current_scope->parm_flag = உண்மை;
}

வெறுமை
தள்ளு_scope (வெறுமை)
{
  எனில் (next_is_function_body)
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
      current_scope->parm_flag         = பொய்;
      current_scope->function_body     = உண்மை;
      current_scope->keep              = உண்மை;
      current_scope->outer_function    = current_function_scope;
      current_function_scope           = current_scope;

      keep_next_level_flag = பொய்;
      next_is_function_body = பொய்;

      /* The FLOAT_CONST_DECIMAL64 pragma applies to nested scopes.  */
      எனில் (current_scope->outer)
	current_scope->float_const_decimal64
	  = current_scope->outer->float_const_decimal64;
      இல்லையெனில்
	current_scope->float_const_decimal64 = பொய்;
    }
  இல்லையெனில்
    {
      கட்டமைப்பு c_scope *scope;
      எனில் (scope_freelist)
	{
	  scope = scope_freelist;
	  scope_freelist = scope->outer;
	}
      இல்லையெனில்
	scope = ggc_cleared_alloc<c_scope> ();

      /* The FLOAT_CONST_DECIMAL64 pragma applies to nested scopes.  */
      எனில் (current_scope)
	scope->float_const_decimal64 = current_scope->float_const_decimal64;
      இல்லையெனில்
	scope->float_const_decimal64 = பொய்;

      scope->keep          = keep_next_level_flag;
      scope->outer         = current_scope;
      scope->depth	   = current_scope ? (current_scope->depth + 1) : 0;

      /* Check for scope depth overflow.  Unlikely (2^28 == 268,435,456) but
	 possible.  */
      எனில் (current_scope && scope->depth == 0)
	{
	  scope->depth--;
	  sorry ("GCC supports only %u nested scopes", scope->depth);
	}

      current_scope        = scope;
      keep_next_level_flag = பொய்;
    }
}

/* This is called when we are leaving SCOPE.  For each label defined
   in SCOPE, add any appropriate decls to its decls_in_scope fields.
   These are the decls whose initialization will be skipped by a goto
   later in the function.  */

நிலையான வெறுமை
update_label_decls (கட்டமைப்பு c_scope *scope)
{
  கட்டமைப்பு c_scope *s;

  s = scope;
  போது (s != வெற்று)
    {
      எனில் (s->has_label_bindings)
	{
	  கட்டமைப்பு c_binding *b;

	  க்கு (b = s->bindings; b != வெற்று; b = b->prev)
	    {
	      கட்டமைப்பு c_label_vars *label_vars;
	      கட்டமைப்பு c_binding *b1;
	      தருக்க hjud;
	      unsigned முழு ix;
	      கட்டமைப்பு c_goto_bindings *g;

	      எனில் (மரம்_CODE (b->decl) != LABEL_DECL)
		தொடர்;
	      label_vars = b->u.label;

	      b1 = label_vars->label_bindings.bindings_in_scope;
	      எனில் (label_vars->label_bindings.scope == வெற்று)
		hjud = பொய்;
	      இல்லையெனில்
		hjud = label_vars->label_bindings.scope->has_jump_unsafe_decl;
	      எனில் (update_spot_bindings (scope, &label_vars->label_bindings))
		{
		  /* This label is defined in this scope.  */
		  எனில் (hjud)
		    {
		      க்கு (; b1 != வெற்று; b1 = b1->prev)
			{
			  /* A goto from later in the function to this
			     label will never see the initialization
			     of B1, if any.  Save it to issue a
			     warning if needed.  */
			  எனில் (decl_jump_unsafe (b1->decl))
			    vec_safe_தள்ளு(label_vars->decls_in_scope, b1->decl);
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
      எனில் (s == current_function_scope)
	நிறுத்து;

      s = s->outer;
    }
}

/* Exit a scope.  Restore the state of the identifier-decl mappings
   that were in effect when this scope was entered.  Return a BLOCK
   node containing all the DECLs in this scope that are of interest
   to debug info generation.  */

மரம்
எடு_scope (வெறுமை)
{
  கட்டமைப்பு c_scope *scope = current_scope;
  மரம் block, context, p;
  கட்டமைப்பு c_binding *b;

  தருக்க functionbody = scope->function_body;
  தருக்க keep = functionbody || scope->keep || scope->bindings;

  update_label_decls (scope);

  /* If appropriate, create a BLOCK to record the decls for the life
     of this function.  */
  block = NULL_மரம்;
  எனில் (keep)
    {
      block = make_முனை (BLOCK);
      BLOCK_SUBBLOCKS (block) = scope->blocks;
      மரம்_USED (block) = 1;

      /* In each subblock, record that this is its superior.  */
      க்கு (p = scope->blocks; p; p = BLOCK_CHAIN (p))
	BLOCK_SUPERCONTEXT (p) = block;

      BLOCK_VARS (block) = NULL_மரம்;
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
  எனில் (scope->function_body)
    context = current_function_decl;
  இல்லையெனில் எனில் (scope == file_scope)
    {
      மரம் file_decl
	= build_translation_unit_decl (get_identifier (main_உள்ளீடு_filename));
      context = file_decl;
      debug_hooks->register_main_translation_unit (file_decl);
    }
  இல்லையெனில்
    context = block;

  /* Clear all bindings in this scope.  */
  க்கு (b = scope->bindings; b; b = free_binding_and_advance (b))
    {
      p = b->decl;
      தேர்வு (மரம்_CODE (p))
	{
	நிலை LABEL_DECL:
	  /* Warnings for unused labels, errors for undefined labels.  */
	  எனில் (மரம்_USED (p) && !DECL_INITIAL (p))
	    {
	      error ("label %q+D used but not defined", p);
	      DECL_INITIAL (p) = error_mark_முனை;
	    }
	  இல்லையெனில்
	    warn_for_unused_label (p);

	  /* Labels go in BLOCK_VARS.  */
	  DECL_CHAIN (p) = BLOCK_VARS (block);
	  BLOCK_VARS (block) = p;
	  gcc_assert (I_LABEL_BINDING (b->id) == b);
	  I_LABEL_BINDING (b->id) = b->shadowed;

	  /* Also pop back to the shadowed label_vars.  */
	  release_மரம்_vector (b->u.label->decls_in_scope);
	  b->u.label = b->u.label->shadowed;
	  நிறுத்து;

	நிலை ENUMERAL_TYPE:
	நிலை UNION_TYPE:
	நிலை RECORD_TYPE:

	  /* Types may not have tag-names, in which case the type
	     appears in the bindings list with b->id NULL.  */
	  எனில் (b->id)
	    {
	      gcc_assert (I_TAG_BINDING (b->id) == b);
	      I_TAG_BINDING (b->id) = b->shadowed;
	    }
	  நிறுத்து;

	நிலை FUNCTION_DECL:
	  /* Propagate TREE_ADDRESSABLE from nested functions to their
	     containing functions.  */
	  எனில் (!மரம்_ASM_WRITTEN (p)
	      && DECL_INITIAL (p) != NULL_மரம்
	      && மரம்_ADDRESSABLE (p)
	      && DECL_ABSTRACT_ORIGIN (p) != NULL_மரம்
	      && DECL_ABSTRACT_ORIGIN (p) != p)
	    மரம்_ADDRESSABLE (DECL_ABSTRACT_ORIGIN (p)) = 1;
	  எனில் (!மரம்_PUBLIC (p)
	      && !DECL_INITIAL (p)
	      && !b->nested
	      && scope != file_scope
	      && scope != external_scope)
	    {
	      error ("nested function %q+D declared but never defined", p);
	      undef_nested_function = உண்மை;
	    }
	  இல்லையெனில் எனில் (DECL_DECLARED_INLINE_P (p)
		   && மரம்_PUBLIC (p)
		   && !DECL_INITIAL (p))
	    {
	      /* C99 6.7.4p6: "a function with external linkage... declared
		 with an inline function specifier ... shall also be defined
		 in the same translation unit."  */
	      எனில் (!flag_gnu89_inline
		  && !lookup_attribute ("gnu_inline", DECL_ATTRIBUTES (p))
		  && scope == external_scope)
		pedwarn (உள்ளீடு_location, 0,
			 "inline function %q+D declared but never defined", p);
	      DECL_EXTERNAL (p) = 1;
	    }

	  செல் common_குறியீடு;

	நிலை VAR_DECL:
	  /* Warnings for unused variables.  */
	  எனில் ((!மரம்_USED (p) || !DECL_READ_P (p))
	      && !warning_suppressed_p (p, OPT_Wunused_but_set_variable_)
	      && !DECL_IN_SYSTEM_HEADER (p)
	      && DECL_NAME (p)
	      && !DECL_ARTIFICIAL (p)
	      && scope != file_scope
	      && scope != external_scope)
	    {
	      எனில் (!மரம்_USED (p))
		{
		  warning (OPT_Wunused_variable, "unused variable %q+D", p);
		  suppress_warning (p, OPT_Wunused_variable);
		}
	      இல்லையெனில் எனில் (DECL_CONTEXT (p) == current_function_decl)
		warning_at (DECL_SOURCE_LOCATION (p),
			    OPT_Wunused_but_set_variable_,
			    "variable %qD set but not used", p);
	    }

	  எனில் (b->inner_comp)
	    {
	      error ("type of array %q+D completed incompatibly with"
		     " implicit initialization", p);
	    }

	  /* Fall through.  */
	நிலை TYPE_DECL:
	நிலை CONST_DECL:
	common_குறியீடு:
	  /* All of these go in BLOCK_VARS, but only if this is the
	     binding in the home scope.  */
	  எனில் (!b->nested)
	    {
	      DECL_CHAIN (p) = BLOCK_VARS (block);
	      BLOCK_VARS (block) = p;
	    }
	  இல்லையெனில் எனில் (VAR_OR_FUNCTION_DECL_P (p) && scope != file_scope)
	    {
	      /* For block local externs add a special
		 DECL_EXTERNAL decl for debug info generation.  */
	      மரம் extp = copy_முனை (p);

	      DECL_EXTERNAL (extp) = 1;
	      மரம்_STATIC (extp) = 0;
	      மரம்_PUBLIC (extp) = 1;
	      DECL_INITIAL (extp) = NULL_மரம்;
	      DECL_LANG_SPECIFIC (extp) = வெற்று;
	      DECL_CONTEXT (extp) = current_function_decl;
	      எனில் (மரம்_CODE (p) == FUNCTION_DECL)
		{
		  DECL_RESULT (extp) = NULL_மரம்;
		  DECL_SAVED_மரம் (extp) = NULL_மரம்;
		  DECL_STRUCT_FUNCTION (extp) = வெற்று;
		}
	      எனில் (b->locus != UNKNOWN_LOCATION)
		DECL_SOURCE_LOCATION (extp) = b->locus;
	      DECL_CHAIN (extp) = BLOCK_VARS (block);
	      BLOCK_VARS (block) = extp;
	    }
	  /* If this is the file scope set DECL_CONTEXT of each decl to
	     the TRANSLATION_UNIT_DECL.  This makes same_translation_unit_p
	     work.  */
	  எனில் (scope == file_scope)
	      DECL_CONTEXT (p) = context;

	  gcc_fallthrough ();
	  /* Parameters go in DECL_ARGUMENTS, not BLOCK_VARS, and have
	     already been put there by store_parm_decls.  Unused-
	     parameter warnings are handled by function.cc.
	     error_mark_node obviously does not go in BLOCK_VARS and
	     does not get unused-variable warnings.  */
	நிலை PARM_DECL:
	நிலை ERROR_MARK:
	  /* It is possible for a decl not to have a name.  We get
	     here with b->id NULL in this case.  */
	  எனில் (b->id)
	    {
	      gcc_assert (I_குறியீடு_BINDING (b->id) == b);
	      I_குறியீடு_BINDING (b->id) = b->shadowed;
	      எனில் (b->shadowed && b->shadowed->u.type)
		மரம்_TYPE (b->shadowed->decl) = b->shadowed->u.type;
	    }
	  நிறுத்து;

	இயல்பு:
	  gcc_unreachable ();
	}
    }


  /* Dispose of the block that we just made inside some higher level.  */
  எனில் ((scope->function_body || scope == file_scope) && context)
    {
      DECL_INITIAL (context) = block;
      BLOCK_SUPERCONTEXT (block) = context;
    }
  இல்லையெனில் எனில் (scope->outer)
    {
      எனில் (block)
	SCOPE_LIST_APPEND (scope->outer, blocks, block);
      /* If we did not make a block for the scope just exited, any
	 blocks made for inner scopes must be carried forward so they
	 will later become subblocks of something else.  */
      இல்லையெனில் எனில் (scope->blocks)
	SCOPE_LIST_CONCAT (scope->outer, blocks, scope, blocks);
    }

  /* Pop the current scope, and free the structure for reuse.  */
  current_scope = scope->outer;
  எனில் (scope->function_body)
    current_function_scope = scope->outer_function;

  memset (scope, 0, அளவு (கட்டமைப்பு c_scope));
  scope->outer = scope_freelist;
  scope_freelist = scope;

  திரும்பு block;
}

வெறுமை
தள்ளு_file_scope (வெறுமை)
{
  மரம் decl;

  எனில் (file_scope)
    திரும்பு;

  /* Call the target stack_protect_guard hook if the stack protection
     guard is declared as a global symbol.  */
  எனில் (targetm.அடுக்கு_protect_guard_குறியீடு_p ())
    {
      மரம் decl = targetm.அடுக்கு_protect_guard ();
      DECL_CHAIN (decl) = visible_builtins;
      visible_builtins = decl;
    }

  தள்ளு_scope ();
  file_scope = current_scope;

  start_fname_decls ();

  க்கு (decl = visible_builtins; decl; decl = DECL_CHAIN (decl))
    bind (DECL_NAME (decl), decl, file_scope,
	  /*invisible=*/பொய், /*nested=*/உண்மை, DECL_SOURCE_LOCATION (decl));
}

வெறுமை
எடு_file_scope (வெறுமை)
{
  /* In case there were missing closebraces, get us back to the global
     binding level.  */
  போது (current_scope != file_scope)
    எடு_scope ();

  /* __FUNCTION__ is defined at file scope ("").  This
     call may not be necessary as my tests indicate it
     still works without it.  */
  finish_fname_decls ();

  check_inline_statics ();

  /* This is the point to write out a PCH if we're doing that.
     In that case we do not want to do anything else.  */
  எனில் (pch_file)
    {
      c_common_write_pch ();
      /* Ensure even the callers don't try to finalize the CU.  */
      flag_syntax_only = 1;
      திரும்பு;
    }

  /* Pop off the file scope and close this translation unit.  */
  எடு_scope ();
  file_scope = 0;

  maybe_apply_pending_pragma_weaks ();
}

/* Whether we are currently inside the initializer for an
   underspecified object definition (C23 auto or constexpr).  */
நிலையான தருக்க in_underspecified_init;

/* Start an underspecified object definition for NAME at LOC.  This
   means that NAME is shadowed inside its initializer, so neither the
   definition being initialized, nor any definition from an outer
   scope, may be referenced during that initializer.  Return state to
   be passed to finish_underspecified_init.  If NAME is NULL_TREE, the
   underspecified object is a (constexpr) compound literal; there is
   no shadowing in that case, but all the other restrictions on
   underspecified object definitions still apply.  */
unsigned முழு
start_underspecified_init (location_t loc, மரம் name)
{
  தருக்க prev = in_underspecified_init;
  தருக்க ok;
  எனில் (name == NULL_மரம்)
    ok = உண்மை;
  இல்லையெனில்
    {
      மரம் decl = build_decl (loc, VAR_DECL, name, error_mark_முனை);
      C_DECL_UNDERSPECIFIED (decl) = 1;
      கட்டமைப்பு c_scope *scope = current_scope;
      கட்டமைப்பு c_binding *b = I_குறியீடு_BINDING (name);
      எனில் (b && B_IN_SCOPE (b, scope))
	{
	  error_at (loc, "underspecified declaration of %qE, which is already "
		    "declared in this scope", name);
	  ok = பொய்;
	}
      இல்லையெனில்
	{
	  bind (name, decl, scope, பொய், பொய், loc);
	  ok = உண்மை;
	}
    }
  in_underspecified_init = உண்மை;
  திரும்பு ok | (prev << 1);
}

/* Finish an underspecified object definition for NAME, before that
   name is bound to the real declaration instead of a placeholder.
   PREV_STATE is the value returned by the call to
   start_underspecified_init.  If NAME is NULL_TREE, this means a
   compound literal, as for start_underspecified_init.  */
வெறுமை
finish_underspecified_init (மரம் name, unsigned முழு prev_state)
{
  எனில் (name != NULL_மரம் && (prev_state & 1))
    {
      /* A VAR_DECL was bound to the name to shadow any previous
	 declarations for the name; remove that binding now.  */
      கட்டமைப்பு c_scope *scope = current_scope;
      கட்டமைப்பு c_binding *b = I_குறியீடு_BINDING (name);
      gcc_assert (b);
      gcc_assert (B_IN_SCOPE (b, scope));
      gcc_assert (VAR_P (b->decl));
      gcc_assert (C_DECL_UNDERSPECIFIED (b->decl));
      I_குறியீடு_BINDING (name) = b->shadowed;
      /* In erroneous cases there may be other bindings added to this
	 scope during the initializer.  */
      கட்டமைப்பு c_binding **p = &scope->bindings;
      போது (*p != b)
	p = &((*p)->prev);
      *p = free_binding_and_advance (*p);
    }
  in_underspecified_init = (prev_state & (1u << 1)) >> 1;
}

/* Adjust the bindings for the start of a statement expression.  */

வெறுமை
c_bindings_start_stmt_கோவை (கட்டமைப்பு c_spot_bindings* switch_bindings)
{
  கட்டமைப்பு c_scope *scope;

  க்கு (scope = current_scope; scope != வெற்று; scope = scope->outer)
    {
      கட்டமைப்பு c_binding *b;

      எனில் (!scope->has_label_bindings)
	தொடர்;

      க்கு (b = scope->bindings; b != வெற்று; b = b->prev)
	{
	  கட்டமைப்பு c_label_vars *label_vars;
	  unsigned முழு ix;
	  கட்டமைப்பு c_goto_bindings *g;

	  எனில் (மரம்_CODE (b->decl) != LABEL_DECL)
	    தொடர்;
	  label_vars = b->u.label;
	  ++label_vars->label_bindings.stmt_exprs;
	  FOR_EACH_VEC_SAFE_ELT (label_vars->gotos, ix, g)
	    ++g->goto_bindings.stmt_exprs;
	}
    }

  எனில் (switch_bindings != வெற்று)
    ++switch_bindings->stmt_exprs;
}

/* Adjust the bindings for the end of a statement expression.  */

வெறுமை
c_bindings_end_stmt_கோவை (கட்டமைப்பு c_spot_bindings *switch_bindings)
{
  கட்டமைப்பு c_scope *scope;

  க்கு (scope = current_scope; scope != வெற்று; scope = scope->outer)
    {
      கட்டமைப்பு c_binding *b;

      எனில் (!scope->has_label_bindings)
	தொடர்;

      க்கு (b = scope->bindings; b != வெற்று; b = b->prev)
	{
	  கட்டமைப்பு c_label_vars *label_vars;
	  unsigned முழு ix;
	  கட்டமைப்பு c_goto_bindings *g;

	  எனில் (மரம்_CODE (b->decl) != LABEL_DECL)
	    தொடர்;
	  label_vars = b->u.label;
	  --label_vars->label_bindings.stmt_exprs;
	  எனில் (label_vars->label_bindings.stmt_exprs < 0)
	    {
	      label_vars->label_bindings.இடது_stmt_கோவை = உண்மை;
	      label_vars->label_bindings.stmt_exprs = 0;
	    }
	  FOR_EACH_VEC_SAFE_ELT (label_vars->gotos, ix, g)
	    {
	      --g->goto_bindings.stmt_exprs;
	      எனில் (g->goto_bindings.stmt_exprs < 0)
		{
		  g->goto_bindings.இடது_stmt_கோவை = உண்மை;
		  g->goto_bindings.stmt_exprs = 0;
		}
	    }
	}
    }

  எனில் (switch_bindings != வெற்று)
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

நிலையான வெறுமை
pushtag (location_t loc, மரம் name, மரம் type)
{
  /* Record the identifier as the type's name if it has none.  */
  எனில் (name && !TYPE_NAME (type))
    TYPE_NAME (type) = name;
  bind (name, type, current_scope, /*invisible=*/பொய், /*nested=*/பொய், loc);

  /* Create a fake NULL-named TYPE_DECL node whose TREE_TYPE will be the
     tagged type we just added to the current scope.  This fake
     NULL-named TYPE_DECL node helps dwarfout.c to know when it needs
     to output a representation of a tagged type, and it also gives
     us a convenient place to record the "scope start" address for the
     tagged type, and it is used to track whether the type is used
     in a non-local context via mark_decl_used.  */

  TYPE_STUB_DECL (type) = pushdecl (build_decl (loc,
						TYPE_DECL, NULL_மரம், type));

  /* An approximation for now, so we can tell this is a function-scope tag.
     This will be updated in pop_scope.  */
  TYPE_CONTEXT (type) = DECL_CONTEXT (TYPE_STUB_DECL (type));

  எனில் (warn_cxx_compat && name != NULL_மரம்)
    {
      கட்டமைப்பு c_binding *b = I_குறியீடு_BINDING (name);

      எனில் (b != வெற்று
	  && b->decl != NULL_மரம்
	  && மரம்_CODE (b->decl) == TYPE_DECL
	  && (B_IN_CURRENT_SCOPE (b)
	      || (current_scope == file_scope && B_IN_EXTERNAL_SCOPE (b)))
	  && (TYPE_MAIN_VARIANT (மரம்_TYPE (b->decl))
	      != TYPE_MAIN_VARIANT (type)))
	{
	  auto_diagnostic_group d;
	  எனில் (warning_at (loc, OPT_Wc___compat,
			  "using %qD as both a typedef and a tag is "
			  "invalid in C++", b->decl)
	      && b->locus != UNKNOWN_LOCATION)
	    inform (b->locus, "originally defined here");
	}
    }
}

/* An exported interface to pushtag.  This is used by the gdb plugin's
   binding oracle to introduce a new tag binding.  */

வெறுமை
c_pushtag (location_t loc, மரம் name, மரம் type)
{
  pushtag (loc, name, type);
}

/* An exported interface to bind a declaration.  LOC is the location
   to use.  DECL is the declaration to bind.  The decl's name is used
   to determine how it is bound.  If DECL is a VAR_DECL, then
   IS_GLOBAL determines whether the decl is put into the global (file
   and external) scope or the current function's scope; if DECL is not
   a VAR_DECL then it is always put into the file scope.  */

வெறுமை
c_bind (location_t loc, மரம் decl, தருக்க is_global)
{
  கட்டமைப்பு c_scope *scope;
  தருக்க nested = பொய்;

  எனில் (!VAR_P (decl) || current_function_scope == வெற்று)
    {
      /* Types and functions are always considered to be global.  */
      scope = file_scope;
      DECL_EXTERNAL (decl) = 1;
      மரம்_PUBLIC (decl) = 1;
    }
  இல்லையெனில் எனில் (is_global)
    {
      /* Also bind it into the external scope.  */
      bind (DECL_NAME (decl), decl, external_scope, உண்மை, பொய், loc);
      nested = உண்மை;
      scope = file_scope;
      DECL_EXTERNAL (decl) = 1;
      மரம்_PUBLIC (decl) = 1;
    }
  இல்லையெனில்
    {
      DECL_CONTEXT (decl) = current_function_decl;
      மரம்_PUBLIC (decl) = 0;
      scope = current_function_scope;
    }

  bind (DECL_NAME (decl), decl, scope, பொய், nested, loc);
}


/* Stores the first FILE*, const struct tm* etc. argument type (whatever
   it is) seen in a declaration of a file I/O etc. built-in, corresponding
   to the builtin_structptr_types array.  Subsequent declarations of such
   built-ins are expected to refer to it rather than to fileptr_type_node,
   etc. which is just void* (or to any other type).
   Used only by match_builtin_function_types.  */

நிலையான மாறிலி unsigned builtin_structptr_type_மொத்தம்
  = ARRAY_SIZE (builtin_structptr_types);

நிலையான GTY(()) மரம் last_structptr_types[builtin_structptr_type_மொத்தம்];

/* Returns true if types T1 and T2 representing return types or types
   of function arguments are close enough to be considered interchangeable
   in redeclarations of built-in functions.  */

நிலையான தருக்க
types_close_enough_to_match (மரம் t1, மரம் t2)
{
  திரும்பு (TYPE_MODE (t1) == TYPE_MODE (t2)
	  && POINTER_TYPE_P (t1) == POINTER_TYPE_P (t2)
	  && FUNCTION_POINTER_TYPE_P (t1) == FUNCTION_POINTER_TYPE_P (t2));
}

/* Subroutine of compare_decls.  Allow harmless mismatches in return
   and argument types provided that the type modes match.  Set *STRICT
   and *ARGNO to the expected argument type and number in case of
   an argument type mismatch or null and zero otherwise.  Return
   a unified type given a suitable match, and 0 otherwise.  */

நிலையான மரம்
match_builtin_function_types (மரம் newtype, மரம் oldtype,
			      மரம் *strict, unsigned *argno)
{
  *argno = 0;
  *strict = NULL_மரம்;

  /* Accept the return type of the new declaration if it has the same
     mode and if they're both pointers or if neither is.  */
  மரம் oldrettype = மரம்_TYPE (oldtype);
  மரம் newrettype = மரம்_TYPE (newtype);

  எனில் (!types_close_enough_to_match (oldrettype, newrettype))
    திரும்பு NULL_மரம்;

  /* Check that the return types are compatible but don't fail if they
     are not (e.g., int vs long in ILP32) and just let the caller know.  */
  எனில் (!comptypes (TYPE_MAIN_VARIANT (oldrettype),
		  TYPE_MAIN_VARIANT (newrettype)))
    *strict = oldrettype;

  மரம் oldargs = TYPE_ARG_TYPES (oldtype);
  மரம் newargs = TYPE_ARG_TYPES (newtype);
  மரம் tryargs = newargs;

  மாறிலி unsigned nlst = ARRAY_SIZE (last_structptr_types);
  மாறிலி unsigned nbst = ARRAY_SIZE (builtin_structptr_types);

  gcc_checking_assert (nlst == nbst);

  க்கு (unsigned i = 1; oldargs || newargs; ++i)
    {
      எனில் (!oldargs
	  || !newargs
	  || !மரம்_மதிப்பு (oldargs)
	  || !மரம்_மதிப்பு (newargs))
	திரும்பு NULL_மரம்;

      மரம் oldtype = TYPE_MAIN_VARIANT (மரம்_மதிப்பு (oldargs));
      மரம் newtype = மரம்_மதிப்பு (newargs);
      எனில் (newtype == error_mark_முனை)
       திரும்பு NULL_மரம்;
      newtype = TYPE_MAIN_VARIANT (newtype);

      எனில் (!types_close_enough_to_match (oldtype, newtype))
	திரும்பு NULL_மரம்;

      unsigned j = nbst;
      எனில் (POINTER_TYPE_P (oldtype))
	/* Iterate over well-known struct types like FILE (whose types
	   aren't known to us) and compare the pointer to each to
	   the pointer argument.  */
	க்கு (j = 0; j < nbst; ++j)
	  {
	    எனில் (மரம்_மதிப்பு (oldargs) != builtin_structptr_types[j].முனை)
	      தொடர்;
	    /* Store the first FILE* etc. argument type (whatever it is), and
	       expect any subsequent declarations of file I/O etc. built-ins
	       to refer to it rather than to fileptr_type_node etc. which is
	       just void* (or const void*).  */
	    எனில் (last_structptr_types[j])
	      {
		எனில் (!comptypes (last_structptr_types[j], newtype))
		  {
		    *argno = i;
		    *strict = last_structptr_types[j];
		  }
	      }
	    இல்லையெனில்
	      last_structptr_types[j] = newtype;
	    நிறுத்து;
	  }

      எனில் (j == nbst && !comptypes (oldtype, newtype))
	{
	  எனில் (POINTER_TYPE_P (oldtype))
	    {
	      /* For incompatible pointers, only reject differences in
		 the unqualified variants of the referenced types but
		 consider differences in qualifiers as benign (report
		 those to caller via *STRICT below).  */
	      மரம் oldref = TYPE_MAIN_VARIANT (மரம்_TYPE (oldtype));
	      மரம் newref = TYPE_MAIN_VARIANT (மரம்_TYPE (newtype));
	      எனில் (!comptypes (oldref, newref))
		திரும்பு NULL_மரம்;
	    }

	  எனில் (!*strict)
	    {
	      *argno = i;
	      *strict = oldtype;
	    }
	}

      oldargs = மரம்_CHAIN (oldargs);
      newargs = மரம்_CHAIN (newargs);
    }

  மரம் trytype = c_build_function_type (newrettype, tryargs);

  /* Allow declaration to change transaction_safe attribute.  */
  மரம் oldattrs = TYPE_ATTRIBUTES (oldtype);
  மரம் oldtsafe = lookup_attribute ("transaction_safe", oldattrs);
  மரம் newattrs = TYPE_ATTRIBUTES (newtype);
  மரம் newtsafe = lookup_attribute ("transaction_safe", newattrs);
  எனில் (oldtsafe && !newtsafe)
    oldattrs = remove_attribute ("transaction_safe", oldattrs);
  இல்லையெனில் எனில் (newtsafe && !oldtsafe)
    oldattrs = மரம்_cons (get_identifier ("transaction_safe"),
			  NULL_மரம், oldattrs);

  திரும்பு c_build_type_attribute_variant (trytype, oldattrs);
}

/* Subroutine of diagnose_mismatched_decls.  Check for function type
   mismatch involving an empty arglist vs a nonempty one and give clearer
   diagnostics.  */
நிலையான வெறுமை
diagnose_arglist_conflict (மரம் newdecl, மரம் olddecl,
			   மரம் newtype, மரம் oldtype)
{
  மரம் t;

  எனில் (மரம்_CODE (olddecl) != FUNCTION_DECL
      || !comptypes (மரம்_TYPE (oldtype), மரம்_TYPE (newtype))
      || !((!prototype_p (oldtype) && DECL_INITIAL (olddecl) == NULL_மரம்)
	   || (!prototype_p (newtype) && DECL_INITIAL (newdecl) == NULL_மரம்)))
    திரும்பு;

  t = TYPE_ARG_TYPES (oldtype);
  எனில் (t == NULL_மரம்)
    t = TYPE_ARG_TYPES (newtype);
  க்கு (; t; t = மரம்_CHAIN (t))
    {
      மரம் type = மரம்_மதிப்பு (t);

      எனில் (மரம்_CHAIN (t) == NULL_மரம்
	  && TYPE_MAIN_VARIANT (type) != void_type_முனை)
	{
	  inform (உள்ளீடு_location, "a parameter list with an ellipsis "
		  "cannot match an empty parameter name list declaration");
	  நிறுத்து;
	}

      எனில் (!error_operand_p (type)
	  && c_type_promotes_to (type) != type)
	{
	  inform (உள்ளீடு_location, "an argument type that has a default "
		  "promotion cannot match an empty parameter name list "
		  "declaration");
	  நிறுத்து;
	}
    }
}

/* Another subroutine of diagnose_mismatched_decls.  OLDDECL is an
   old-style function definition, NEWDECL is a prototype declaration.
   Diagnose inconsistencies in the argument list.  Returns TRUE if
   the prototype is compatible, FALSE if not.  */
நிலையான தருக்க
validate_proto_after_old_defn (மரம் newdecl, மரம் newtype, மரம் oldtype)
{
  மரம் newargs, oldargs;
  முழு i;

#define END_OF_ARGLIST(t) ((t) == void_type_முனை)

  oldargs = TYPE_ACTUAL_ARG_TYPES (oldtype);
  newargs = TYPE_ARG_TYPES (newtype);
  i = 1;

  க்கு (;;)
    {
      மரம் oldargtype = மரம்_மதிப்பு (oldargs);
      மரம் newargtype = மரம்_மதிப்பு (newargs);

      எனில் (oldargtype == error_mark_முனை || newargtype == error_mark_முனை)
	திரும்பு பொய்;

      oldargtype = (TYPE_ATOMIC (oldargtype)
		    ? c_build_qualified_type (TYPE_MAIN_VARIANT (oldargtype),
					      TYPE_QUAL_ATOMIC)
		    : TYPE_MAIN_VARIANT (oldargtype));
      newargtype = (TYPE_ATOMIC (newargtype)
		    ? c_build_qualified_type (TYPE_MAIN_VARIANT (newargtype),
					      TYPE_QUAL_ATOMIC)
		    : TYPE_MAIN_VARIANT (newargtype));

      எனில் (END_OF_ARGLIST (oldargtype) && END_OF_ARGLIST (newargtype))
	நிறுத்து;

      /* Reaching the end of just one list means the two decls don't
	 agree on the number of arguments.  */
      எனில் (END_OF_ARGLIST (oldargtype))
	{
	  error ("prototype for %q+D declares more arguments "
		 "than previous old-style definition", newdecl);
	  திரும்பு பொய்;
	}
      இல்லையெனில் எனில் (END_OF_ARGLIST (newargtype))
	{
	  error ("prototype for %q+D declares fewer arguments "
		 "than previous old-style definition", newdecl);
	  திரும்பு பொய்;
	}

      /* Type for passing arg must be consistent with that declared
	 for the arg.  */
      இல்லையெனில் எனில் (!comptypes (oldargtype, newargtype))
	{
	  error ("prototype for %q+D declares argument %d"
		 " with incompatible type",
		 newdecl, i);
	  திரும்பு பொய்;
	}

      oldargs = மரம்_CHAIN (oldargs);
      newargs = மரம்_CHAIN (newargs);
      i++;
    }

  /* If we get here, no errors were found, but do issue a warning
     for this poor-style construct.  */
  warning (0, "prototype for %q+D follows non-prototype definition",
	   newdecl);
  திரும்பு உண்மை;
#undef END_OF_ARGLIST
}

/* Subroutine of diagnose_mismatched_decls.  Report the location of DECL,
   first in a pair of mismatched declarations, using the diagnostic
   function DIAG.  */
நிலையான வெறுமை
locate_old_decl (மரம் decl)
{
  எனில் (மரம்_CODE (decl) == FUNCTION_DECL
      && fndecl_built_in_p (decl)
      && !C_DECL_DECLARED_BUILTIN (decl))
    ;
  இல்லையெனில் எனில் (DECL_INITIAL (decl))
    inform (உள்ளீடு_location,
	    "previous definition of %q+D with type %qT",
	    decl, மரம்_TYPE (decl));
  இல்லையெனில் எனில் (C_DECL_IMPLICIT (decl))
    inform (உள்ளீடு_location,
	    "previous implicit declaration of %q+D with type %qT",
	    decl, மரம்_TYPE (decl));
  இல்லையெனில்
    inform (உள்ளீடு_location,
	    "previous declaration of %q+D with type %qT",
	    decl, மரம்_TYPE (decl));
}


/* Helper function.  For a tagged type, it finds the declaration
   for a visible tag declared in the same scope if such a
   declaration exists.  */
நிலையான மரம்
previous_tag (மரம் type)
{
  கட்டமைப்பு c_binding *b = வெற்று;
  மரம் name = c_type_tag (type);

  எனில் (name)
    b = I_TAG_BINDING (name);

  எனில் (b)
    b = b->shadowed;

  எனில் (b && B_IN_CURRENT_SCOPE (b))
    திரும்பு b->decl;

  திரும்பு NULL_மரம்;
}

/* Subroutine to mark functions as versioned when using the attribute
   'target_version'.  */

நிலையான வெறுமை
maybe_mark_function_versioned (மரம் decl)
{
  எனில் (!DECL_FUNCTION_VERSIONED (decl))
    {
      /* Check if the name of the function has been overridden.  */
      எனில் (DECL_ASSEMBLER_NAME_SET_P (decl)
	  && IDENTIFIER_POINTER (DECL_ASSEMBLER_NAME (decl))[0] == '*')
	error_at (DECL_SOURCE_LOCATION (decl),
		  "cannot use function multiversioning on a renamed function");

      /* We need to insert function version now to make sure the correct
	 pre-mangled assembler name is recorded.  */
      cgraph_முனை *முனை = cgraph_முனை::get_create (decl);

      எனில் (!முனை->function_version ())
	முனை->செருகு_new_function_version ();

      DECL_FUNCTION_VERSIONED (decl) = 1;

      மரம் mangled_name
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

நிலையான தருக்க
diagnose_mismatched_decls (மரம் newdecl, மரம் olddecl,
			   மரம் *newtypep, மரம் *oldtypep)
{
  மரம் newtype, oldtype;
  தருக்க retval = உண்மை;

#define DECL_EXTERN_INLINE(DECL) (DECL_DECLARED_INLINE_P (DECL)  \
				  && DECL_EXTERNAL (DECL))

  /* If we have error_mark_node for either decl or type, just discard
     the previous decl - we're in an error cascade already.  */
  எனில் (olddecl == error_mark_முனை || newdecl == error_mark_முனை)
    திரும்பு பொய்;
  *oldtypep = oldtype = மரம்_TYPE (olddecl);
  *newtypep = newtype = மரம்_TYPE (newdecl);
  எனில் (oldtype == error_mark_முனை || newtype == error_mark_முனை)
    திரும்பு பொய்;

  /* Two different categories of symbol altogether.  This is an error
     unless OLDDECL is a builtin.  OLDDECL will be discarded in any case.  */
  எனில் (மரம்_CODE (olddecl) != மரம்_CODE (newdecl))
    {
      எனில் (!(மரம்_CODE (olddecl) == FUNCTION_DECL
	    && fndecl_built_in_p (olddecl)
	    && !C_DECL_DECLARED_BUILTIN (olddecl)))
	{
	  auto_diagnostic_group d;
	  error ("%q+D redeclared as different kind of symbol", newdecl);
	  locate_old_decl (olddecl);
	}
      இல்லையெனில் எனில் (மரம்_PUBLIC (newdecl))
	warning (OPT_Wbuiltin_declaration_mismatch,
		 "built-in function %q+D declared as non-function",
		 newdecl);
      இல்லையெனில்
	warning (OPT_Wshadow, "declaration of %q+D shadows "
		 "a built-in function", newdecl);
      திரும்பு பொய்;
    }

  /* Enumerators have no linkage, so may only be declared once in a
     given scope.  */
  எனில் (மரம்_CODE (olddecl) == CONST_DECL)
    {
      எனில் (flag_isoc23
	  && TYPE_NAME (DECL_CONTEXT (newdecl))
	  && DECL_CONTEXT (newdecl) != DECL_CONTEXT (olddecl)
	  && TYPE_NAME (DECL_CONTEXT (newdecl)) == TYPE_NAME (DECL_CONTEXT (olddecl)))
	{
	  எனில் (!simple_cst_equal (DECL_INITIAL (olddecl), DECL_INITIAL (newdecl)))
	    {
	      auto_diagnostic_group d;
	      error ("conflicting redeclaration of enumerator %q+D", newdecl);
	      locate_old_decl (olddecl);
	    }
	}
      இல்லையெனில்
	{
	  auto_diagnostic_group d;
	  error ("redeclaration of enumerator %q+D", newdecl);
	  locate_old_decl (olddecl);
	}
      திரும்பு பொய்;
    }

  தருக்க pedwarned = பொய்;
  தருக்க warned = பொய்;
  தருக்க enum_and_int_p = பொய்;
  auto_diagnostic_group d;

  தருக்க comptypes_result = comptypes_check_enum_int (oldtype, newtype,
						    &enum_and_int_p);
  எனில் (!comptypes_result)
    {
      எனில் (மரம்_CODE (olddecl) == FUNCTION_DECL
	  && fndecl_built_in_p (olddecl, BUILT_IN_NORMAL)
	  && !C_DECL_DECLARED_BUILTIN (olddecl))
	{
	  /* Accept "harmless" mismatches in function types such
	     as missing qualifiers or int vs long when they're the same
	     size.  However, diagnose return and argument types that are
	     incompatible according to language rules.  */
	  மரம் mismatch_expect;
	  unsigned mismatch_argno;

	  மரம் trytype = match_builtin_function_types (newtype, oldtype,
						       &mismatch_expect,
						       &mismatch_argno);

	  எனில் (trytype && comptypes (newtype, trytype))
	    *oldtypep = oldtype = trytype;
	  இல்லையெனில்
	    {
	      /* If types don't match for a built-in, throw away the
		 built-in.  No point in calling locate_old_decl here, it
		 won't print anything.  */
	      மாறிலி எழுத்து *header = header_for_builtin_fn (olddecl);
	      location_t loc = DECL_SOURCE_LOCATION (newdecl);
	      எனில் (warning_at (loc, OPT_Wbuiltin_declaration_mismatch,
			      "conflicting types for built-in function %q+D; "
			      "expected %qT",
			      newdecl, oldtype)
		  && header)
		{
		  /* Suggest the right header to include as the preferred
		     solution rather than the spelling of the declaration.  */
		  rich_location richloc (வரி_table, loc);
		  maybe_add_include_fixit (&richloc, header, உண்மை);
		  inform (&richloc,
			  "%qD is declared in header %qs", olddecl, header);
		}
	      திரும்பு பொய்;
	    }

	  எனில் (mismatch_expect && extra_warnings)
	    {
	      location_t newloc = DECL_SOURCE_LOCATION (newdecl);
	      தருக்க warned = பொய்;
	      எனில் (mismatch_argno)
		warned = warning_at (newloc, OPT_Wbuiltin_declaration_mismatch,
				     "mismatch in argument %u type of built-in "
				     "function %qD; expected %qT",
				     mismatch_argno, newdecl, mismatch_expect);
	      இல்லையெனில்
		warned = warning_at (newloc, OPT_Wbuiltin_declaration_mismatch,
				     "mismatch in return type of built-in "
				     "function %qD; expected %qT",
				     newdecl, mismatch_expect);
	      மாறிலி எழுத்து *header = header_for_builtin_fn (olddecl);
	      எனில் (warned && header)
		{
		  rich_location richloc (வரி_table, newloc);
		  maybe_add_include_fixit (&richloc, header, உண்மை);
		  inform (&richloc,
			  "%qD is declared in header %qs", olddecl, header);
		}
	    }
	}
      இல்லையெனில் எனில் (மரம்_CODE (olddecl) == FUNCTION_DECL
	       && DECL_IS_UNDECLARED_BUILTIN (olddecl))
	{
	  /* A conflicting function declaration for a predeclared
	     function that isn't actually built in.  Objective C uses
	     these.  The new declaration silently overrides everything
	     but the volatility (i.e. noreturn) indication.  See also
	     below.  FIXME: Make Objective C use normal builtins.  */
	  மரம்_THIS_VOLATILE (newdecl) |= மரம்_THIS_VOLATILE (olddecl);
	  திரும்பு பொய்;
	}
      /* Permit void foo (...) to match int foo (...) if the latter is
	 the definition and implicit int was used.  See
	 c-torture/compile/920625-2.c.  */
      இல்லையெனில் எனில் (மரம்_CODE (newdecl) == FUNCTION_DECL && DECL_INITIAL (newdecl)
	       && TYPE_MAIN_VARIANT (மரம்_TYPE (oldtype)) == void_type_முனை
	       && TYPE_MAIN_VARIANT (மரம்_TYPE (newtype)) == integer_type_முனை
	       && C_FUNCTION_IMPLICIT_INT (newdecl) && !DECL_INITIAL (olddecl))
	{
	  pedwarned = pedwarn (உள்ளீடு_location, 0,
			       "conflicting types for %q+D", newdecl);
	  /* Make sure we keep void as the return type.  */
	  மரம்_TYPE (newdecl) = *newtypep = newtype = oldtype;
	  C_FUNCTION_IMPLICIT_INT (newdecl) = 0;
	}
      /* Permit void foo (...) to match an earlier call to foo (...) with
	 no declared type (thus, implicitly int).  */
      இல்லையெனில் எனில் (மரம்_CODE (newdecl) == FUNCTION_DECL
	       && TYPE_MAIN_VARIANT (மரம்_TYPE (newtype)) == void_type_முனை
	       && TYPE_MAIN_VARIANT (மரம்_TYPE (oldtype)) == integer_type_முனை
	       && C_DECL_IMPLICIT (olddecl) && !DECL_INITIAL (olddecl))
	{
	  pedwarned = pedwarn (உள்ளீடு_location, 0,
			       "conflicting types for %q+D; have %qT",
			       newdecl, newtype);
	  /* Make sure we keep void as the return type.  */
	  மரம்_TYPE (olddecl) = *oldtypep = oldtype = newtype;
	}
      இல்லையெனில்
	{
	  முழு new_quals = TYPE_QUALS (newtype);
	  முழு old_quals = TYPE_QUALS (oldtype);

	  எனில் (new_quals != old_quals)
	    {
	      addr_space_t new_addr = DECODE_QUAL_ADDR_SPACE (new_quals);
	      addr_space_t old_addr = DECODE_QUAL_ADDR_SPACE (old_quals);
	      எனில் (new_addr != old_addr)
		{
		  எனில் (ADDR_SPACE_GENERIC_P (new_addr))
		    error ("conflicting named address spaces (generic vs %s) "
			   "for %q+D",
			   c_addr_space_name (old_addr), newdecl);
		  இல்லையெனில் எனில் (ADDR_SPACE_GENERIC_P (old_addr))
		    error ("conflicting named address spaces (%s vs generic) "
			   "for %q+D",
			   c_addr_space_name (new_addr), newdecl);
		  இல்லையெனில்
		    error ("conflicting named address spaces (%s vs %s) "
			   "for %q+D",
			   c_addr_space_name (new_addr),
			   c_addr_space_name (old_addr),
			   newdecl);
		}

	      எனில் (CLEAR_QUAL_ADDR_SPACE (new_quals)
		  != CLEAR_QUAL_ADDR_SPACE (old_quals))
		error ("conflicting type qualifiers for %q+D", newdecl);
	    }
	  இல்லையெனில்
	    {
	      எனில் (மரம்_CODE (olddecl) == FUNCTION_DECL)
		{
		  மரம் attrs = TYPE_ATTRIBUTES (மரம்_TYPE (olddecl));
		  எனில் (attrs && !TYPE_ATTRIBUTES (மரம்_TYPE (newdecl)))
		    {
		      /* Similar to the C++ front-end, for FUNCTION_DECL,
			 if OLDDECL has attributes and NEWDECL doesn't,
			 try the type with OLDDECL attributes.  */
		      மரம் rettype = மரம்_TYPE (newtype);
		      மரம் tryargs = TYPE_ARG_TYPES (newtype);
		      மரம் trytype = c_build_function_type (rettype,
							    tryargs);
		      trytype = c_build_type_attribute_variant (trytype,
								attrs);
		      எனில் (comptypes (oldtype, trytype))
			{
			  *newtypep = newtype = trytype;
			  comptypes_result = உண்மை;
			}
		    }
		}

	      எனில் (!comptypes_result)
		error ("conflicting types for %q+D; have %qT", newdecl,
		       newtype);
	    }
	  எனில் (!comptypes_result)
	    {
	      diagnose_arglist_conflict (newdecl, olddecl, newtype,
					 oldtype);
	      locate_old_decl (olddecl);
	      திரும்பு பொய்;
	    }
	}
    }
  /* Warn about enum/integer type mismatches.  They are compatible types
     (C23 6.7.2.2/5), but may pose portability problems.  */
  இல்லையெனில் எனில் (enum_and_int_p
	   && மரம்_CODE (newdecl) != TYPE_DECL
	   /* Don't warn about acc_on_device built-in redeclaration,
	      the built-in is declared with int rather than enum because
	      the enum isn't intrinsic.  */
	   && !(மரம்_CODE (olddecl) == FUNCTION_DECL
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
  எனில் (மரம்_CODE (newdecl) == TYPE_DECL)
    {
      எனில் (!comptypes_same_p (oldtype, newtype))
	{
	  error ("redefinition of typedef %q+D with different type", newdecl);
	  locate_old_decl (olddecl);
	  திரும்பு பொய்;
	}

      எனில் (DECL_IN_SYSTEM_HEADER (newdecl)
	  || DECL_IN_SYSTEM_HEADER (olddecl)
	  || warning_suppressed_p (newdecl, OPT_Wpedantic)
	  || warning_suppressed_p (olddecl, OPT_Wpedantic))
	திரும்பு உண்மை;  /* Allow OLDDECL to continue in use.  */

      எனில் (c_type_variably_modified_p (newtype))
	{
	  error ("redefinition of typedef %q+D with variably modified type",
		 newdecl);
	  locate_old_decl (olddecl);
	}
      இல்லையெனில் எனில் (pedwarn_c99 (உள்ளீடு_location, OPT_Wpedantic,
			    "redefinition of typedef %q+D", newdecl))
	locate_old_decl (olddecl);

      திரும்பு உண்மை;
    }

  /* Function declarations can either be 'static' or 'extern' (no
     qualifier is equivalent to 'extern' - C99 6.2.2p5) and therefore
     can never conflict with each other on account of linkage
     (6.2.2p4).  Multiple definitions are not allowed (6.9p3,5) but
     gnu89 mode permits two definitions if one is 'extern inline' and
     one is not.  The non- extern-inline definition supersedes the
     extern-inline definition.  */

  இல்லையெனில் எனில் (மரம்_CODE (newdecl) == FUNCTION_DECL)
    {
      /* If you declare a built-in function name as static, or
	 define the built-in with an old-style definition (so we
	 can't validate the argument list) the built-in definition is
	 overridden, but optionally warn this was a bad choice of name.  */
      எனில் (fndecl_built_in_p (olddecl)
	  && !C_DECL_DECLARED_BUILTIN (olddecl))
	{
	  எனில் (!மரம்_PUBLIC (newdecl)
	      || (DECL_INITIAL (newdecl)
		  && !prototype_p (மரம்_TYPE (newdecl))))
	    {
	      warning_at (DECL_SOURCE_LOCATION (newdecl),
			  OPT_Wshadow, "declaration of %qD shadows "
			  "a built-in function", newdecl);
	      /* Discard the old built-in function.  */
	      திரும்பு பொய்;
	    }

	  எனில் (!prototype_p (மரம்_TYPE (newdecl)))
	    {
	      /* Set for built-ins that take no arguments.  */
	      தருக்க func_void_args = பொய்;
	      எனில் (மரம் at = TYPE_ARG_TYPES (oldtype))
		func_void_args = VOID_TYPE_P (மரம்_மதிப்பு (at));

	      எனில் (extra_warnings && !func_void_args)
		warning_at (DECL_SOURCE_LOCATION (newdecl),
			    OPT_Wbuiltin_declaration_mismatch,
			    "declaration of built-in function %qD without "
			    "a prototype; expected %qT",
			    newdecl, மரம்_TYPE (olddecl));
	    }
	}

      எனில் (DECL_INITIAL (newdecl))
	{
	  எனில் (DECL_INITIAL (olddecl))
	    {
	      /* If the new declaration isn't overriding an extern inline
		 reject the new decl. In c99, no overriding is allowed
		 in the same translation unit.  */
	      எனில் (!DECL_EXTERN_INLINE (olddecl)
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
		  திரும்பு பொய்;
		}
	    }
	}
      /* If we have a prototype after an old-style function definition,
	 the argument types must be checked specially.  */
      இல்லையெனில் எனில் (DECL_INITIAL (olddecl)
	       && !prototype_p (oldtype) && prototype_p (newtype)
	       && TYPE_ACTUAL_ARG_TYPES (oldtype))
	{
	  auto_diagnostic_group d;
	  எனில் (!validate_proto_after_old_defn (newdecl, newtype, oldtype))
	    {
	      locate_old_decl (olddecl);
	      திரும்பு பொய்;
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
      எனில் (மரம்_PUBLIC (olddecl) && !மரம்_PUBLIC (newdecl))
	{
	  /* Two exceptions to the rule.  If olddecl is an extern
	     inline, or a predeclared function that isn't actually
	     built in, newdecl silently overrides olddecl.  The latter
	     occur only in Objective C; see also above.  (FIXME: Make
	     Objective C use normal builtins.)  */
	  எனில் (!DECL_IS_UNDECLARED_BUILTIN (olddecl)
	      && !DECL_EXTERN_INLINE (olddecl))
	    {
	      auto_diagnostic_group d;
	      error ("static declaration of %q+D follows "
		     "non-static declaration", newdecl);
	      locate_old_decl (olddecl);
	    }
	  திரும்பு பொய்;
	}
      இல்லையெனில் எனில் (மரம்_PUBLIC (newdecl) && !மரம்_PUBLIC (olddecl))
	{
	  எனில் (DECL_CONTEXT (olddecl))
	    {
	      auto_diagnostic_group d;
	      error ("non-static declaration of %q+D follows "
		     "static declaration", newdecl);
	      locate_old_decl (olddecl);
	      திரும்பு பொய்;
	    }
	  இல்லையெனில் எனில் (warn_traditional)
	    {
	      warned |= warning (OPT_Wtraditional,
				 "non-static declaration of %q+D "
				 "follows static declaration", newdecl);
	    }
	}

      /* Make sure gnu_inline attribute is either not present, or
	 present on all inline decls.  */
      எனில் (DECL_DECLARED_INLINE_P (olddecl)
	  && DECL_DECLARED_INLINE_P (newdecl))
	{
	  தருக்க newa = lookup_attribute ("gnu_inline",
					DECL_ATTRIBUTES (newdecl)) != வெற்று;
	  தருக்க olda = lookup_attribute ("gnu_inline",
					DECL_ATTRIBUTES (olddecl)) != வெற்று;
	  எனில் (newa != olda)
	    {
	      auto_diagnostic_group d;
	      error_at (உள்ளீடு_location, "%<gnu_inline%> attribute present on %q+D",
			newa ? newdecl : olddecl);
	      error_at (DECL_SOURCE_LOCATION (newa ? olddecl : newdecl),
			"but not here");
	    }
	}
      /* Check if these are unmergeable overlapping FMV declarations.  */
      எனில் (!TARGET_HAS_FMV_TARGET_ATTRIBUTE
	  && diagnose_versioned_decls (olddecl, newdecl))
	திரும்பு பொய்;
    }
  இல்லையெனில் எனில் (VAR_P (newdecl))
    {
      /* Only variables can be thread-local, and all declarations must
	 agree on this property.  */
      எனில் (C_DECL_THREADPRIVATE_P (olddecl) && !DECL_THREAD_LOCAL_P (newdecl))
	{
	  /* Nothing to check.  Since OLDDECL is marked threadprivate
	     and NEWDECL does not have a thread-local attribute, we
	     will merge the threadprivate attribute into NEWDECL.  */
	  ;
	}
      இல்லையெனில் எனில் (DECL_THREAD_LOCAL_P (newdecl) != DECL_THREAD_LOCAL_P (olddecl))
	{
	  auto_diagnostic_group d;
	  எனில் (DECL_THREAD_LOCAL_P (newdecl))
	    error ("thread-local declaration of %q+D follows "
		   "non-thread-local declaration", newdecl);
	  இல்லையெனில்
	    error ("non-thread-local declaration of %q+D follows "
		   "thread-local declaration", newdecl);

	  locate_old_decl (olddecl);
	  திரும்பு பொய்;
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
      எனில் ((DECL_INITIAL (newdecl) && DECL_INITIAL (olddecl))
	  || (flag_isoc23
	      && DECL_THREAD_LOCAL_P (newdecl)
	      && !DECL_EXTERNAL (newdecl)
	      && !DECL_EXTERNAL (olddecl)))
	{
	  auto_diagnostic_group d;
	  error ("redefinition of %q+D", newdecl);
	  locate_old_decl (olddecl);
	  திரும்பு பொய்;
	}

      /* Objects declared at file scope: if the first declaration had
	 external linkage (even if it was an external reference) the
	 second must have external linkage as well, or the behavior is
	 undefined.  If the first declaration had internal linkage, then
	 the second must too, or else be an external reference (in which
	 case the composite declaration still has internal linkage).
	 As for function declarations, we warn about the static-then-
	 extern case only for -Wtraditional.  See generally 6.2.2p3-5,7.  */
      எனில் (DECL_FILE_SCOPE_P (newdecl)
	  && மரம்_PUBLIC (newdecl) != மரம்_PUBLIC (olddecl))
	{
	  எனில் (DECL_EXTERNAL (newdecl))
	    {
	      எனில் (!DECL_FILE_SCOPE_P (olddecl))
		{
		  auto_diagnostic_group d;
		  error ("extern declaration of %q+D follows "
			 "declaration with no linkage", newdecl);
		  locate_old_decl (olddecl);
		  திரும்பு பொய்;
		}
	      இல்லையெனில் எனில் (warn_traditional)
		{
		  warned |= warning (OPT_Wtraditional,
				     "non-static declaration of %q+D "
				     "follows static declaration", newdecl);
		}
	    }
	  இல்லையெனில்
	    {
	      auto_diagnostic_group d;
	      எனில் (மரம்_PUBLIC (newdecl))
		error ("non-static declaration of %q+D follows "
		       "static declaration", newdecl);
	      இல்லையெனில்
		error ("static declaration of %q+D follows "
		       "non-static declaration", newdecl);

	      locate_old_decl (olddecl);
	      திரும்பு பொய்;
	    }
	}
      /* Two objects with the same name declared at the same block
	 scope must both be external references (6.7p3).  */
      இல்லையெனில் எனில் (!DECL_FILE_SCOPE_P (newdecl))
	{
	  எனில் (DECL_EXTERNAL (newdecl))
	    {
	      /* Extern with initializer at block scope, which will
		 already have received an error.  */
	    }
	  இல்லையெனில் எனில் (DECL_EXTERNAL (olddecl))
	    {
	      auto_diagnostic_group d;
	      error ("declaration of %q+D with no linkage follows "
		     "extern declaration", newdecl);
	      locate_old_decl (olddecl);
	    }
	  இல்லையெனில்
	    {
	      auto_diagnostic_group d;
	      error ("redeclaration of %q+D with no linkage", newdecl);
	      locate_old_decl (olddecl);
	    }

	  திரும்பு பொய்;
	}

      /* C++ does not permit a decl to appear multiple times at file
	 scope.  */
      எனில் (warn_cxx_compat
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
  எனில் (CODE_CONTAINS_STRUCT (மரம்_CODE (newdecl), TS_DECL_WITH_VIS)
      && DECL_VISIBILITY_SPECIFIED (newdecl) && DECL_VISIBILITY_SPECIFIED (olddecl)
      && DECL_VISIBILITY (newdecl) != DECL_VISIBILITY (olddecl))
    {
      warned |= warning (0, "redeclaration of %q+D with different visibility "
			 "(old visibility preserved)", newdecl);
    }

  எனில் (மரம்_CODE (newdecl) == FUNCTION_DECL)
    warned |= diagnose_mismatched_attributes (olddecl, newdecl);
  இல்லையெனில் /* PARM_DECL, VAR_DECL */
    {
      /* Redeclaration of a parameter is a constraint violation (this is
	 not explicitly stated, but follows from C99 6.7p3 [no more than
	 one declaration of the same identifier with no linkage in the
	 same scope, except type tags] and 6.2.2p6 [parameters have no
	 linkage]).  We must check for a forward parameter declaration,
	 indicated by TREE_ASM_WRITTEN on the old declaration - this is
	 an extension, the mandatory diagnostic for which is handled by
	 mark_forward_parm_decls.  */

      எனில் (மரம்_CODE (newdecl) == PARM_DECL
	  && (!மரம்_ASM_WRITTEN (olddecl) || மரம்_ASM_WRITTEN (newdecl)))
	{
	  auto_diagnostic_group d;
	  error ("redefinition of parameter %q+D", newdecl);
	  locate_old_decl (olddecl);
	  திரும்பு பொய்;
	}
    }

  /* Optional warning for completely redundant decls.  */
  எனில் (!warned && !pedwarned
      && warn_redundant_decls
      /* Don't warn about a function declaration followed by a
	 definition.  */
      && !(மரம்_CODE (newdecl) == FUNCTION_DECL
	   && DECL_INITIAL (newdecl) && !DECL_INITIAL (olddecl))
      /* Don't warn about redundant redeclarations of builtins.  */
      && !(மரம்_CODE (newdecl) == FUNCTION_DECL
	   && !fndecl_built_in_p (newdecl)
	   && fndecl_built_in_p (olddecl)
	   && !C_DECL_DECLARED_BUILTIN (olddecl))
      /* Don't warn about an extern followed by a definition.  */
      && !(DECL_EXTERNAL (olddecl) && !DECL_EXTERNAL (newdecl))
      /* Don't warn about forward parameter decls.  */
      && !(மரம்_CODE (newdecl) == PARM_DECL
	   && மரம்_ASM_WRITTEN (olddecl) && !மரம்_ASM_WRITTEN (newdecl))
      /* Don't warn about a variable definition following a declaration.  */
      && !(VAR_P (newdecl)
	   && DECL_INITIAL (newdecl) && !DECL_INITIAL (olddecl)))
    {
      warned = warning (OPT_Wredundant_decls, "redundant redeclaration of %q+D",
			newdecl);
    }

  /* Report location of previous decl/defn.  */
  எனில் (warned || pedwarned)
    locate_old_decl (olddecl);

#undef DECL_EXTERN_INLINE

  திரும்பு retval;
}

/* Subroutine of duplicate_decls.  NEWDECL has been found to be
   consistent with OLDDECL, but carries new information.  Merge the
   new information into OLDDECL.  This function issues no
   diagnostics.  */

நிலையான வெறுமை
merge_decls (மரம் newdecl, மரம் olddecl, மரம் newtype, மரம் oldtype)
{
  தருக்க new_is_definition = (மரம்_CODE (newdecl) == FUNCTION_DECL
			    && DECL_INITIAL (newdecl) != NULL_மரம்);
  தருக்க new_is_prototype = (மரம்_CODE (newdecl) == FUNCTION_DECL
			   && prototype_p (மரம்_TYPE (newdecl)));
  தருக்க old_is_prototype = (மரம்_CODE (olddecl) == FUNCTION_DECL
			   && prototype_p (மரம்_TYPE (olddecl)));

  /* For real parm decl following a forward decl, rechain the old decl
     in its new location and clear TREE_ASM_WRITTEN (it's not a
     forward decl anymore).  */
  எனில் (மரம்_CODE (newdecl) == PARM_DECL
      && மரம்_ASM_WRITTEN (olddecl) && !மரம்_ASM_WRITTEN (newdecl))
    {
      கட்டமைப்பு c_binding *b, **here;

      க்கு (here = &current_scope->bindings; *here; here = &(*here)->prev)
	எனில் ((*here)->decl == olddecl)
	  செல் found;
      gcc_unreachable ();

    found:
      b = *here;
      *here = b->prev;
      b->prev = current_scope->bindings;
      current_scope->bindings = b;

      மரம்_ASM_WRITTEN (olddecl) = 0;
    }

  DECL_ATTRIBUTES (newdecl)
    = targetm.merge_decl_attributes (olddecl, newdecl);

  /* For typedefs use the old type, as the new type's DECL_NAME points
     at newdecl, which will be ggc_freed.  */
  எனில் (மரம்_CODE (newdecl) == TYPE_DECL)
    {
      /* But NEWTYPE might have an attribute, honor that.  */
      மரம் tem = newtype;
      newtype = oldtype;

      எனில் (TYPE_USER_ALIGN (tem))
	{
	  எனில் (TYPE_ALIGN (tem) > TYPE_ALIGN (newtype))
	    SET_TYPE_ALIGN (newtype, TYPE_ALIGN (tem));
	  TYPE_USER_ALIGN (newtype) = உண்மை;
	}

      /* And remove the new type from the variants list.  */
      எனில் (TYPE_NAME (மரம்_TYPE (newdecl)) == newdecl)
	{
	  மரம் remove = மரம்_TYPE (newdecl);
	  எனில் (TYPE_MAIN_VARIANT (remove) == remove)
	    {
	      gcc_assert (TYPE_NEXT_VARIANT (remove) == NULL_மரம்);
	      /* If remove is the main variant, no need to remove that
		 from the list.  One of the DECL_ORIGINAL_TYPE
		 variants, e.g. created for aligned attribute, might still
		 refer to the newdecl TYPE_DECL though, so remove that one
		 in that case.  */
	      எனில் (DECL_ORIGINAL_TYPE (newdecl)
		  && DECL_ORIGINAL_TYPE (newdecl) != remove)
		க்கு (மரம் t = TYPE_MAIN_VARIANT (DECL_ORIGINAL_TYPE (newdecl));
		     t; t = TYPE_MAIN_VARIANT (t))
		  எனில் (TYPE_NAME (TYPE_NEXT_VARIANT (t)) == newdecl)
		    {
		      TYPE_NEXT_VARIANT (t)
			= TYPE_NEXT_VARIANT (TYPE_NEXT_VARIANT (t));
		      நிறுத்து;
		    }
	    }
	  இல்லையெனில்
	    க்கு (மரம் t = TYPE_MAIN_VARIANT (remove); ;
		 t = TYPE_NEXT_VARIANT (t))
	      எனில் (TYPE_NEXT_VARIANT (t) == remove)
		{
		  TYPE_NEXT_VARIANT (t) = TYPE_NEXT_VARIANT (remove);
		  நிறுத்து;
		}
	}

      /* Make sure we refer to the same type as the olddecl.  */
      DECL_ORIGINAL_TYPE (newdecl) = DECL_ORIGINAL_TYPE (olddecl);
    }

  /* Merge the data types specified in the two decls.  */
  மரம்_TYPE (newdecl)
    = மரம்_TYPE (olddecl)
    = composite_type (newtype, oldtype);

  /* Lay the type out, unless already done.  */
  எனில் (!comptypes (oldtype, மரம்_TYPE (newdecl)))
    {
      எனில் (மரம்_TYPE (newdecl) != error_mark_முனை)
	layout_type (மரம்_TYPE (newdecl));
      எனில் (மரம்_CODE (newdecl) != FUNCTION_DECL
	  && மரம்_CODE (newdecl) != TYPE_DECL
	  && மரம்_CODE (newdecl) != CONST_DECL)
	layout_decl (newdecl, 0);
    }
  இல்லையெனில்
    {
      /* Since the type is OLDDECL's, make OLDDECL's size go with.  */
      DECL_SIZE (newdecl) = DECL_SIZE (olddecl);
      DECL_SIZE_UNIT (newdecl) = DECL_SIZE_UNIT (olddecl);
      SET_DECL_MODE (newdecl, DECL_MODE (olddecl));
      எனில் (DECL_ALIGN (olddecl) > DECL_ALIGN (newdecl))
	{
	  SET_DECL_ALIGN (newdecl, DECL_ALIGN (olddecl));
	  DECL_USER_ALIGN (newdecl) |= DECL_USER_ALIGN (olddecl);
	}
      இல்லையெனில் எனில் (DECL_ALIGN (olddecl) == DECL_ALIGN (newdecl)
	       && DECL_USER_ALIGN (olddecl) != DECL_USER_ALIGN (newdecl))
	DECL_USER_ALIGN (newdecl) = 1;
      எனில் (DECL_WARN_IF_NOT_ALIGN (olddecl)
	  > DECL_WARN_IF_NOT_ALIGN (newdecl))
	SET_DECL_WARN_IF_NOT_ALIGN (newdecl,
				    DECL_WARN_IF_NOT_ALIGN (olddecl));
    }

  /* Keep the old rtl since we can safely use it.  */
  எனில் (HAS_RTL_P (olddecl))
    COPY_DECL_RTL (olddecl, newdecl);

  /* Merge the type qualifiers.  */
  எனில் (மரம்_READONLY (newdecl))
    மரம்_READONLY (olddecl) = 1;

  எனில் (மரம்_THIS_VOLATILE (newdecl))
    மரம்_THIS_VOLATILE (olddecl) = 1;

  /* Merge deprecatedness.  */
  எனில் (மரம்_DEPRECATED (newdecl))
    மரம்_DEPRECATED (olddecl) = 1;

  /* Merge unavailability.  */
  எனில் (மரம்_UNAVAILABLE (newdecl))
    மரம்_UNAVAILABLE (olddecl) = 1;

  /* If a decl is in a system header and the other isn't, keep the one on the
     system header. Otherwise, keep source location of definition rather than
     declaration and of prototype rather than non-prototype unless that
     prototype is built-in.  */
  எனில் (HAS_DECL_ASSEMBLER_NAME_P (olddecl)
      && DECL_IN_SYSTEM_HEADER (olddecl)
      && !DECL_IN_SYSTEM_HEADER (newdecl) )
    DECL_SOURCE_LOCATION (newdecl) = DECL_SOURCE_LOCATION (olddecl);
  இல்லையெனில் எனில் (HAS_DECL_ASSEMBLER_NAME_P (olddecl)
	   && DECL_IN_SYSTEM_HEADER (newdecl)
	   && !DECL_IN_SYSTEM_HEADER (olddecl))
    DECL_SOURCE_LOCATION (olddecl) = DECL_SOURCE_LOCATION (newdecl);
  இல்லையெனில் எனில் ((DECL_INITIAL (newdecl) == NULL_மரம்
	    && DECL_INITIAL (olddecl) != NULL_மரம்)
	   || (old_is_prototype && !new_is_prototype
	       && !C_DECL_BUILTIN_PROTOTYPE (olddecl)))
    DECL_SOURCE_LOCATION (newdecl) = DECL_SOURCE_LOCATION (olddecl);

  /* Merge the initialization information.  */
   எனில் (DECL_INITIAL (newdecl) == NULL_மரம்)
    DECL_INITIAL (newdecl) = DECL_INITIAL (olddecl);

  /* Merge 'constexpr' information.  */
  எனில் (VAR_P (olddecl) && VAR_P (newdecl))
    {
      எனில் (C_DECL_DECLARED_CONSTEXPR (olddecl))
	C_DECL_DECLARED_CONSTEXPR (newdecl) = 1;
      இல்லையெனில் எனில் (C_DECL_DECLARED_CONSTEXPR (newdecl))
	C_DECL_DECLARED_CONSTEXPR (olddecl) = 1;
    }

  /* Merge the threadprivate attribute.  */
  எனில் (VAR_P (olddecl) && C_DECL_THREADPRIVATE_P (olddecl))
    C_DECL_THREADPRIVATE_P (newdecl) = 1;

  எனில் (HAS_DECL_ASSEMBLER_NAME_P (olddecl))
    {
      /* Copy the assembler name.
	 Currently, it can only be defined in the prototype.  */
      COPY_DECL_ASSEMBLER_NAME (olddecl, newdecl);

      /* Use visibility of whichever declaration had it specified */
      எனில் (DECL_VISIBILITY_SPECIFIED (olddecl))
	{
	  DECL_VISIBILITY (newdecl) = DECL_VISIBILITY (olddecl);
	  DECL_VISIBILITY_SPECIFIED (newdecl) = 1;
	}

      எனில் (மரம்_CODE (newdecl) == FUNCTION_DECL)
	{
	  DECL_STATIC_CONSTRUCTOR(newdecl) |= DECL_STATIC_CONSTRUCTOR(olddecl);
	  DECL_STATIC_DESTRUCTOR (newdecl) |= DECL_STATIC_DESTRUCTOR (olddecl);
	  DECL_NO_LIMIT_அடுக்கு (newdecl) |= DECL_NO_LIMIT_அடுக்கு (olddecl);
	  DECL_NO_INSTRUMENT_FUNCTION_ENTRY_EXIT (newdecl)
	    |= DECL_NO_INSTRUMENT_FUNCTION_ENTRY_EXIT (olddecl);
	  மரம்_THIS_VOLATILE (newdecl) |= மரம்_THIS_VOLATILE (olddecl);
	  DECL_IS_MALLOC (newdecl) |= DECL_IS_MALLOC (olddecl);
	  எனில் (DECL_IS_OPERATOR_NEW_P (olddecl))
	    DECL_SET_IS_OPERATOR_NEW (newdecl, உண்மை);
	  எனில் (DECL_IS_OPERATOR_DELETE_P (olddecl))
	    DECL_SET_IS_OPERATOR_DELETE (newdecl, உண்மை);
	  மரம்_READONLY (newdecl) |= மரம்_READONLY (olddecl);
	  DECL_PURE_P (newdecl) |= DECL_PURE_P (olddecl);
	  DECL_IS_NOVOPS (newdecl) |= DECL_IS_NOVOPS (olddecl);
	}

      /* Merge the storage class information.  */
      merge_weak (newdecl, olddecl);

      /* For functions, static overrides non-static.  */
      எனில் (மரம்_CODE (newdecl) == FUNCTION_DECL)
	{
	  மரம்_PUBLIC (newdecl) &= மரம்_PUBLIC (olddecl);
	  /* This is since we don't automatically
	     copy the attributes of NEWDECL into OLDDECL.  */
	  மரம்_PUBLIC (olddecl) = மரம்_PUBLIC (newdecl);
	  /* If this clears `static', clear it in the identifier too.  */
	  எனில் (!மரம்_PUBLIC (olddecl))
	    மரம்_PUBLIC (DECL_NAME (olddecl)) = 0;
	}
    }

  /* In c99, 'extern' declaration before (or after) 'inline' means this
     function is not DECL_EXTERNAL, unless 'gnu_inline' attribute
     is present.  */
  எனில் (மரம்_CODE (newdecl) == FUNCTION_DECL
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
  எனில் (new_is_definition
      && (DECL_DECLARED_INLINE_P (newdecl)
	  || DECL_DECLARED_INLINE_P (olddecl))
      && !மரம்_PUBLIC (olddecl))
    DECL_EXTERNAL (newdecl) = 0;

  எனில் (DECL_EXTERNAL (newdecl))
    {
      மரம்_STATIC (newdecl) = மரம்_STATIC (olddecl);
      DECL_EXTERNAL (newdecl) = DECL_EXTERNAL (olddecl);

      /* An extern decl does not override previous storage class.  */
      மரம்_PUBLIC (newdecl) = மரம்_PUBLIC (olddecl);
      எனில் (!DECL_EXTERNAL (newdecl))
	{
	  DECL_CONTEXT (newdecl) = DECL_CONTEXT (olddecl);
	  DECL_COMMON (newdecl) = DECL_COMMON (olddecl);
	}
    }
  இல்லையெனில்
    {
      மரம்_STATIC (olddecl) = மரம்_STATIC (newdecl);
      மரம்_PUBLIC (olddecl) = மரம்_PUBLIC (newdecl);
    }

  எனில் (மரம்_CODE (newdecl) == FUNCTION_DECL)
    {
      எனில் (DECL_FUNCTION_VERSIONED (olddecl)
	  || DECL_FUNCTION_VERSIONED (newdecl))
	{
	  maybe_mark_function_versioned (olddecl);
	  maybe_mark_function_versioned (newdecl);
	}
      /* If we're redefining a function previously defined as extern
	 inline, make sure we emit debug info for the inline before we
	 throw it away, in case it was inlined into a function that
	 hasn't been written out yet.  */
      எனில் (new_is_definition && DECL_INITIAL (olddecl))
	/* The new defn must not be inline.  */
	DECL_UNINLINABLE (newdecl) = 1;
      இல்லையெனில்
	{
	  /* If either decl says `inline', this fn is inline, unless
	     its definition was passed already.  */
	  எனில் (DECL_DECLARED_INLINE_P (newdecl)
	      || DECL_DECLARED_INLINE_P (olddecl))
	    DECL_DECLARED_INLINE_P (newdecl) = 1;

	  DECL_UNINLINABLE (newdecl) = DECL_UNINLINABLE (olddecl)
	    = (DECL_UNINLINABLE (newdecl) || DECL_UNINLINABLE (olddecl));

	  DECL_DISREGARD_INLINE_LIMITS (newdecl)
	    = DECL_DISREGARD_INLINE_LIMITS (olddecl)
	    = (DECL_DISREGARD_INLINE_LIMITS (newdecl)
	       || DECL_DISREGARD_INLINE_LIMITS (olddecl));
	}

      எனில் (fndecl_built_in_p (olddecl))
	{
	  /* If redeclaring a builtin function, it stays built in.
	     But it gets tagged as having been declared.  */
	  copy_decl_built_in_function (newdecl, olddecl);
	  C_DECL_DECLARED_BUILTIN (newdecl) = 1;
	  எனில் (new_is_prototype)
	    {
	      C_DECL_BUILTIN_PROTOTYPE (newdecl) = 0;
	      எனில் (DECL_BUILT_IN_CLASS (newdecl) == BUILT_IN_NORMAL)
		{
		  எண்ணிக்கை built_in_function fncode = DECL_FUNCTION_CODE (newdecl);
		  தேர்வு (fncode)
		    {
		      /* If a compatible prototype of these builtin functions
			 is seen, assume the runtime implements it with the
			 expected semantics.  */
		    நிலை BUILT_IN_STPCPY:
		      எனில் (builtin_decl_explicit_p (fncode))
			set_builtin_decl_implicit_p (fncode, உண்மை);
		      நிறுத்து;
		    இயல்பு:
		      எனில் (builtin_decl_explicit_p (fncode))
			set_builtin_decl_declared_p (fncode, உண்மை);
		      நிறுத்து;
		    }

		  copy_attributes_to_builtin (newdecl);
		}
	    }
	  இல்லையெனில்
	    C_DECL_BUILTIN_PROTOTYPE (newdecl)
	      = C_DECL_BUILTIN_PROTOTYPE (olddecl);
	}

      /* Preserve function specific target and optimization options */
      எனில் (DECL_FUNCTION_SPECIFIC_TARGET (olddecl)
	  && !DECL_FUNCTION_SPECIFIC_TARGET (newdecl))
	DECL_FUNCTION_SPECIFIC_TARGET (newdecl)
	  = DECL_FUNCTION_SPECIFIC_TARGET (olddecl);

      எனில் (DECL_FUNCTION_SPECIFIC_OPTIMIZATION (olddecl)
	  && !DECL_FUNCTION_SPECIFIC_OPTIMIZATION (newdecl))
	DECL_FUNCTION_SPECIFIC_OPTIMIZATION (newdecl)
	  = DECL_FUNCTION_SPECIFIC_OPTIMIZATION (olddecl);

      /* Also preserve various other info from the definition.  */
      எனில் (!new_is_definition)
	{
	  மரம் t;
	  DECL_RESULT (newdecl) = DECL_RESULT (olddecl);
	  DECL_INITIAL (newdecl) = DECL_INITIAL (olddecl);
	  DECL_STRUCT_FUNCTION (newdecl) = DECL_STRUCT_FUNCTION (olddecl);
	  DECL_SAVED_மரம் (newdecl) = DECL_SAVED_மரம் (olddecl);
	  DECL_ARGUMENTS (newdecl) = copy_list (DECL_ARGUMENTS (olddecl));
	  க்கு (t = DECL_ARGUMENTS (newdecl); t ; t = DECL_CHAIN (t))
	    DECL_CONTEXT (t) = newdecl;

	  /* See if we've got a function to instantiate from.  */
	  எனில் (DECL_SAVED_மரம் (olddecl))
	    DECL_ABSTRACT_ORIGIN (newdecl)
	      = DECL_ABSTRACT_ORIGIN (olddecl);
	}
    }

  /* Merge the USED information.  */
  எனில் (மரம்_USED (olddecl))
    மரம்_USED (newdecl) = 1;
  இல்லையெனில் எனில் (மரம்_USED (newdecl))
    மரம்_USED (olddecl) = 1;
  எனில் (VAR_P (olddecl) || மரம்_CODE (olddecl) == PARM_DECL)
    DECL_READ_P (newdecl) |= DECL_READ_P (olddecl);
  எனில் (DECL_PRESERVE_P (olddecl))
    DECL_PRESERVE_P (newdecl) = 1;
  இல்லையெனில் எனில் (DECL_PRESERVE_P (newdecl))
    DECL_PRESERVE_P (olddecl) = 1;

  /* Merge DECL_COMMON */
  எனில் (VAR_P (olddecl) && VAR_P (newdecl)
      && !lookup_attribute ("common", DECL_ATTRIBUTES (newdecl))
      && !lookup_attribute ("nocommon", DECL_ATTRIBUTES (newdecl)))
    DECL_COMMON (newdecl) = DECL_COMMON (newdecl) && DECL_COMMON (olddecl);

  /* Copy most of the decl-specific fields of NEWDECL into OLDDECL.
     But preserve OLDDECL's DECL_UID, DECL_CONTEXT and
     DECL_ARGUMENTS (if appropriate).  */
  {
    unsigned olddecl_uid = DECL_UID (olddecl);
    மரம் olddecl_context = DECL_CONTEXT (olddecl);
    மரம் olddecl_arguments = வெற்று;
    எனில் (மரம்_CODE (olddecl) == FUNCTION_DECL)
      olddecl_arguments = DECL_ARGUMENTS (olddecl);

    memcpy ((எழுத்து *) olddecl + அளவு (கட்டமைப்பு மரம்_common),
	    (எழுத்து *) newdecl + அளவு (கட்டமைப்பு மரம்_common),
	    அளவு (கட்டமைப்பு மரம்_decl_common) - அளவு (கட்டமைப்பு மரம்_common));
    DECL_USER_ALIGN (olddecl) = DECL_USER_ALIGN (newdecl);
    தேர்வு (மரம்_CODE (olddecl))
      {
      நிலை FUNCTION_DECL:
      நிலை VAR_DECL:
	{
	  கட்டமைப்பு symtab_முனை *snode = olddecl->decl_with_vis.symtab_முனை;

	  memcpy ((எழுத்து *) olddecl + அளவு (கட்டமைப்பு மரம்_decl_common),
		  (எழுத்து *) newdecl + அளவு (கட்டமைப்பு மரம்_decl_common),
		  மரம்_code_size (மரம்_CODE (olddecl)) - அளவு (கட்டமைப்பு மரம்_decl_common));
	  olddecl->decl_with_vis.symtab_முனை = snode;

	  எனில் ((DECL_EXTERNAL (olddecl)
	       || மரம்_PUBLIC (olddecl)
	       || மரம்_STATIC (olddecl))
	      && DECL_SECTION_NAME (newdecl) != வெற்று)
	    set_decl_section_name (olddecl, newdecl);

	  /* This isn't quite correct for something like
		int __thread x attribute ((tls_model ("local-exec")));
		extern int __thread x;
	     as we'll lose the "local-exec" model.  */
	  எனில் (VAR_P (olddecl) && DECL_THREAD_LOCAL_P (newdecl))
	    set_decl_tls_model (olddecl, DECL_TLS_MODEL (newdecl));
	  நிறுத்து;
	}

      நிலை FIELD_DECL:
      நிலை PARM_DECL:
      நிலை LABEL_DECL:
      நிலை RESULT_DECL:
      நிலை CONST_DECL:
      நிலை TYPE_DECL:
	memcpy ((எழுத்து *) olddecl + அளவு (கட்டமைப்பு மரம்_decl_common),
		(எழுத்து *) newdecl + அளவு (கட்டமைப்பு மரம்_decl_common),
		மரம்_code_size (மரம்_CODE (olddecl)) - அளவு (கட்டமைப்பு மரம்_decl_common));
	நிறுத்து;

      இயல்பு:

	memcpy ((எழுத்து *) olddecl + அளவு (கட்டமைப்பு மரம்_decl_common),
		(எழுத்து *) newdecl + அளவு (கட்டமைப்பு மரம்_decl_common),
		அளவு (கட்டமைப்பு மரம்_decl_non_common) - அளவு (கட்டமைப்பு மரம்_decl_common));
      }
    DECL_UID (olddecl) = olddecl_uid;
    DECL_CONTEXT (olddecl) = olddecl_context;
    எனில் (மரம்_CODE (olddecl) == FUNCTION_DECL)
      DECL_ARGUMENTS (olddecl) = olddecl_arguments;
  }

  /* If OLDDECL had its DECL_RTL instantiated, re-invoke make_decl_rtl
     so that encode_section_info has a chance to look at the new decl
     flags and attributes.  */
  எனில் (DECL_RTL_SET_P (olddecl)
      && (மரம்_CODE (olddecl) == FUNCTION_DECL
	  || (VAR_P (olddecl) && மரம்_STATIC (olddecl))))
    make_decl_rtl (olddecl);
}

/* Handle when a new declaration NEWDECL has the same name as an old
   one OLDDECL in the same binding contour.  Prints an error message
   if appropriate.

   If safely possible, alter OLDDECL to look like NEWDECL, and return
   true.  Otherwise, return false.  */

நிலையான தருக்க
duplicate_decls (மரம் newdecl, மரம் olddecl)
{
  மரம் newtype = வெற்று, oldtype = வெற்று;

  எனில் (!diagnose_mismatched_decls (newdecl, olddecl, &newtype, &oldtype))
    {
      /* Avoid `unused variable' and other warnings for OLDDECL.  */
      suppress_warning (olddecl, OPT_Wunused);
      /* If the types are completely different, poison them both with
 	 error_mark_node.  */
      எனில் (மரம்_CODE (மரம்_TYPE (newdecl)) != மரம்_CODE (மரம்_TYPE (olddecl))
	  && olddecl != error_mark_முனை
	  && seen_error ())
	{
	  எனில் (மரம்_CODE (olddecl) != FUNCTION_DECL)
	    மரம்_TYPE (olddecl) = error_mark_முனை;
	  எனில் (மரம்_CODE (newdecl) != FUNCTION_DECL)
	    மரம்_TYPE (newdecl) = error_mark_முனை;
	}
      திரும்பு பொய்;
    }

  merge_decls (newdecl, olddecl, newtype, oldtype);

  /* The NEWDECL will no longer be needed.

     Before releasing the node, be sure to remove function from symbol
     table that might have been inserted there to record comdat group.
     Be sure to however do not free DECL_STRUCT_FUNCTION because this
     structure is shared in between NEWDECL and OLDECL.  */
  எனில் (மரம்_CODE (newdecl) == FUNCTION_DECL)
    DECL_STRUCT_FUNCTION (newdecl) = வெற்று;
  எனில் (VAR_OR_FUNCTION_DECL_P (newdecl))
    {
      கட்டமைப்பு symtab_முனை *snode = symtab_முனை::get (newdecl);
      எனில் (snode)
	snode->remove ();
    }
  ggc_free (newdecl);
  திரும்பு உண்மை;
}


/* Check whether decl-node NEW_DECL shadows an existing declaration.  */
நிலையான வெறுமை
warn_if_shadowing (மரம் new_decl)
{
  கட்டமைப்பு c_binding *b;

  /* Shadow warnings wanted?  */
  எனில் (!(warn_shadow
        || warn_shadow_local
        || warn_shadow_compatible_local)
      /* No shadow warnings for internally generated vars.  */
      || DECL_IS_UNDECLARED_BUILTIN (new_decl))
    திரும்பு;

  /* Is anything being shadowed?  Invisible decls do not count.  */
  க்கு (b = I_குறியீடு_BINDING (DECL_NAME (new_decl)); b; b = b->shadowed)
    எனில் (b->decl && b->decl != new_decl && !b->invisible
	&& (b->decl == error_mark_முனை
	    || diagnostic_report_warnings_p (global_dc,
					     DECL_SOURCE_LOCATION (b->decl))))
      {
	மரம் old_decl = b->decl;

	எனில் (old_decl == error_mark_முனை)
	  {
	    warning (OPT_Wshadow, "declaration of %q+D shadows previous "
		     "non-variable", new_decl);
	    நிறுத்து;
	  }

	தருக்க warned = பொய்;
	auto_diagnostic_group d;
	எனில் (மரம்_CODE (old_decl) == PARM_DECL)
	  {
	    எண்ணிக்கை opt_code warning_code;

	    /* If '-Wshadow=compatible-local' is specified without other
	       -Wshadow= flags, we will warn only when the types of the
	       shadowing variable (i.e. new_decl) and the shadowed variable
	       (old_decl) are compatible.  */
	    எனில் (warn_shadow)
	      warning_code = OPT_Wshadow;
	    இல்லையெனில் எனில் (comptypes (மரம்_TYPE (old_decl), மரம்_TYPE (new_decl)))
	      warning_code = OPT_Wshadow_compatible_local;
	    இல்லையெனில்
	      warning_code = OPT_Wshadow_local;
	    warned = warning_at (DECL_SOURCE_LOCATION (new_decl), warning_code,
				 "declaration of %qD shadows a parameter",
				 new_decl);
	  }
	இல்லையெனில் எனில் (DECL_FILE_SCOPE_P (old_decl))
	  {
	    /* Do not warn if a variable shadows a function, unless
	       the variable is a function or a pointer-to-function.  */
	    எனில் (மரம்_CODE (old_decl) == FUNCTION_DECL
		&& மரம்_CODE (new_decl) != FUNCTION_DECL
		&& !FUNCTION_POINTER_TYPE_P (மரம்_TYPE (new_decl)))
		தொடர்;

	    warned = warning_at (DECL_SOURCE_LOCATION (new_decl), OPT_Wshadow,
				 "declaration of %qD shadows a global "
				 "declaration",
				 new_decl);
	  }
	இல்லையெனில் எனில் (மரம்_CODE (old_decl) == FUNCTION_DECL
		 && fndecl_built_in_p (old_decl))
	  {
	    warning (OPT_Wshadow, "declaration of %q+D shadows "
		     "a built-in function", new_decl);
	    நிறுத்து;
	  }
	இல்லையெனில்
	  {
	    எண்ணிக்கை opt_code warning_code;

	    /* If '-Wshadow=compatible-local' is specified without other
	       -Wshadow= flags, we will warn only when the types of the
	       shadowing variable (i.e. new_decl) and the shadowed variable
	       (old_decl) are compatible.  */
	    எனில் (warn_shadow)
	      warning_code = OPT_Wshadow;
	    இல்லையெனில் எனில் (comptypes (மரம்_TYPE (old_decl), மரம்_TYPE (new_decl)))
	      warning_code = OPT_Wshadow_compatible_local;
	    இல்லையெனில்
	      warning_code = OPT_Wshadow_local;
	    warned = warning_at (DECL_SOURCE_LOCATION (new_decl), warning_code,
				 "declaration of %qD shadows a previous local",
				 new_decl);
	  }

	எனில் (warned)
	  inform (DECL_SOURCE_LOCATION (old_decl),
		  "shadowed declaration is here");

	நிறுத்து;
      }
}

/* Record a decl-node X as belonging to the current lexical scope.
   Check for errors (such as an incompatible declaration for the same
   name already seen in the same scope).

   Returns either X or an old decl for the same name.
   If an old decl is returned, it may have been smashed
   to agree with what X says.  */

மரம்
pushdecl (மரம் x)
{
  மரம் name = DECL_NAME (x);
  கட்டமைப்பு c_scope *scope = current_scope;
  கட்டமைப்பு c_binding *b;
  தருக்க nested = பொய்;
  location_t locus = DECL_SOURCE_LOCATION (x);

  /* Must set DECL_CONTEXT for everything not at file scope or
     DECL_FILE_SCOPE_P won't work.  Local externs don't count
     unless they have initializers (which generate code).  We
     also exclude CONST_DECLs because enumerators will get the
     type of the enum as context.  */
  எனில் (current_function_decl
      && மரம்_CODE (x) != CONST_DECL
      && (!VAR_OR_FUNCTION_DECL_P (x)
	  || DECL_INITIAL (x) || !மரம்_PUBLIC (x)))
    DECL_CONTEXT (x) = current_function_decl;

  /* Anonymous decls are just inserted in the scope.  */
  எனில் (!name)
    {
      bind (name, x, scope, /*invisible=*/பொய், /*nested=*/பொய்,
	    locus);
      திரும்பு x;
    }

  /* First, see if there is another declaration with the same name in
     the current scope.  If there is, duplicate_decls may do all the
     work for us.  If duplicate_decls returns false, that indicates
     two incompatible decls in the same scope; we are to silently
     replace the old one (duplicate_decls has issued all appropriate
     diagnostics).  In particular, we should not consider possible
     duplicates in the external scope, or shadowing.  */
  b = I_குறியீடு_BINDING (name);
  எனில் (b && B_IN_SCOPE (b, scope))
    {
      கட்டமைப்பு c_binding *b_ext, *b_use;
      மரம் type = மரம்_TYPE (x);
      மரம் visdecl = b->decl;
      மரம் vistype = மரம்_TYPE (visdecl);
      எனில் (மரம்_CODE (மரம்_TYPE (x)) == ARRAY_TYPE
	  && COMPLETE_TYPE_P (மரம்_TYPE (x)))
	b->inner_comp = பொய்;
      b_use = b;
      b_ext = b;
      /* If this is an external linkage declaration, we should check
	 for compatibility with the type in the external scope before
	 setting the type at this scope based on the visible
	 information only.  */
      எனில் (மரம்_PUBLIC (x) && மரம்_PUBLIC (visdecl))
	{
	  போது (b_ext && !B_IN_EXTERNAL_SCOPE (b_ext))
	    b_ext = b_ext->shadowed;
	  எனில் (b_ext)
	    {
	      b_use = b_ext;
	      எனில் (b_use->u.type)
		மரம்_TYPE (b_use->decl) = b_use->u.type;
	    }
	}

      /* Check if x is part of a FMV set with b_use.
	 FMV is only supported in c for targets with target_version
	 attributes.  */
      எனில் (!TARGET_HAS_FMV_TARGET_ATTRIBUTE
	  && b_use && மரம்_CODE (b_use->decl) == FUNCTION_DECL
	  && மரம்_CODE (x) == FUNCTION_DECL && DECL_FILE_SCOPE_P (b_use->decl)
	  && DECL_FILE_SCOPE_P (x)
	  && disjoint_version_decls (x, b_use->decl)
	  && comptypes (vistype, type))
	{
	  maybe_mark_function_versioned (b_use->decl);
	  maybe_mark_function_versioned (b->decl);
	  maybe_mark_function_versioned (x);

	  cgraph_முனை *b_முனை = cgraph_முனை::get_create (b_use->decl);
	  cgraph_function_version_info *b_v = b_முனை->function_version ();
	  எனில் (!b_v)
	    b_v = b_முனை->செருகு_new_function_version ();

	  /* Check if this new node conflicts with any previous functions
	     in the set.  */
	  cgraph_function_version_info *version = b_v;
	  க்கு (; version; version = version->next)
	    எனில் (!disjoint_version_decls (version->this_முனை->decl, x))
	      {
		/* The decls define overlapping version, so attempt to merge
		   or diagnose the conflict.  */
		எனில் (duplicate_decls (x, version->this_முனை->decl))
		  திரும்பு version->this_முனை->decl;
		இல்லையெனில்
		  திரும்பு error_mark_முனை;
	      }

	  /* This is a new version to be added to FMV structure.  */
	  cgraph_முனை::add_function_version (b_v, x);

	  /* Get the first node from the structure.  */
	  cgraph_function_version_info *default_v = b_v;
	  போது (default_v->prev)
	    default_v = default_v->prev;
	  /* Always use the default node for the bindings.  */
	  b_use->decl = default_v->this_முனை->decl;
	  b->decl = default_v->this_முனை->decl;

	  /* Node is not a duplicate, so no need to do the rest of the
	     checks.  */
	  திரும்பு x;
	}

      எனில் (duplicate_decls (x, b_use->decl))
	{
	  எனில் (b_use != b)
	    {
	      /* Save the updated type in the external scope and
		 restore the proper type for this scope.  */
	      மரம் thistype;
	      எனில் (comptypes (vistype, type))
		thistype = composite_type (vistype, type);
	      இல்லையெனில்
		thistype = மரம்_TYPE (b_use->decl);
	      b_use->u.type = மரம்_TYPE (b_use->decl);
	      எனில் (மரம்_CODE (b_use->decl) == FUNCTION_DECL
		  && fndecl_built_in_p (b_use->decl))
		thistype
		  = c_build_type_attribute_variant (thistype,
						    TYPE_ATTRIBUTES
						    (b_use->u.type));
	      மரம்_TYPE (b_use->decl) = thistype;
	    }
	  திரும்பு b_use->decl;
	}
      இல்லையெனில்
	செல் skip_external_and_shadow_checks;
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
  எனில் ((DECL_EXTERNAL (x) || scope == file_scope)
      && (VAR_OR_FUNCTION_DECL_P (x) || c_dialect_objc ()))
    {
      மரம் type = மரம்_TYPE (x);
      மரம் vistype = NULL_மரம்;
      மரம் visdecl = NULL_மரம்;
      தருக்க type_saved = பொய்;
      எனில் (b && !B_IN_EXTERNAL_SCOPE (b)
	  && VAR_OR_FUNCTION_DECL_P (b->decl)
	  && DECL_FILE_SCOPE_P (b->decl))
	{
	  visdecl = b->decl;
	  vistype = மரம்_TYPE (visdecl);
	}
      எனில் (scope != file_scope
	  && !DECL_IN_SYSTEM_HEADER (x))
	warning_at (locus, OPT_Wnested_externs,
		    "nested extern declaration of %qD", x);

      போது (b && !B_IN_EXTERNAL_SCOPE (b))
	{
	  /* If this decl might be modified, save its type.  This is
	     done here rather than when the decl is first bound
	     because the type may change after first binding, through
	     being completed or through attributes being added.  If we
	     encounter multiple such decls, only the first should have
	     its type saved; the others will already have had their
	     proper types saved and the types will not have changed as
	     their scopes will not have been re-entered.  */
	  எனில் (DECL_P (b->decl) && DECL_FILE_SCOPE_P (b->decl) && !type_saved)
	    {
	      b->u.type = மரம்_TYPE (b->decl);
	      type_saved = உண்மை;
	    }
	  எனில் (B_IN_FILE_SCOPE (b)
	      && VAR_P (b->decl)
	      && மரம்_STATIC (b->decl)
	      && மரம்_CODE (மரம்_TYPE (b->decl)) == ARRAY_TYPE
	      && !TYPE_DOMAIN (மரம்_TYPE (b->decl))
	      && மரம்_CODE (type) == ARRAY_TYPE
	      && TYPE_DOMAIN (type)
	      && TYPE_MAX_மதிப்பு (TYPE_DOMAIN (type))
	      && !integer_zerop (TYPE_MAX_மதிப்பு (TYPE_DOMAIN (type))))
	    {
	      /* Array type completed in inner scope, which should be
		 diagnosed if the completion does not have size 1 and
		 it does not get completed in the file scope.  */
	      b->inner_comp = உண்மை;
	    }
	  b = b->shadowed;
	}

      /* If a matching external declaration has been found, set its
	 type to the composite of all the types of that declaration.
	 After the consistency checks, it will be reset to the
	 composite of the visible types only.  */
      எனில் (b && b->u.type)
	மரம்_TYPE (b->decl) = b->u.type;

      /* the static does not go in the externals scope.  */
      எனில் (b && duplicate_decls (x, b->decl))
	{
	  மரம் thistype;
	  எனில் (vistype)
	    {
	      எனில் (comptypes (vistype, type))
		thistype = composite_type (vistype, type);
	      இல்லையெனில்
		thistype = மரம்_TYPE (b->decl);
	    }
	  இல்லையெனில்
	    thistype = type;
	  b->u.type = மரம்_TYPE (b->decl);
	  /* Propagate the type attributes to the decl.  */
	  thistype
	    = c_build_type_attribute_variant (thistype,
					      TYPE_ATTRIBUTES (b->u.type));
	  மரம்_TYPE (b->decl) = thistype;
	  bind (name, b->decl, scope, /*invisible=*/பொய், /*nested=*/உண்மை,
		locus);
	  திரும்பு b->decl;
	}
      இல்லையெனில் எனில் (மரம்_PUBLIC (x))
	{
	  எனில் (visdecl && !b && duplicate_decls (x, visdecl))
	    {
	      /* An external declaration at block scope referring to a
		 visible entity with internal linkage.  The composite
		 type will already be correct for this scope, so we
		 just need to fall through to make the declaration in
		 this scope.  */
	      nested = உண்மை;
	      x = visdecl;
	    }
	  இல்லையெனில்
	    {
	      bind (name, x, external_scope, /*invisible=*/உண்மை,
		    /*nested=*/பொய், locus);
	      nested = உண்மை;
	    }
	}
    }

  எனில் (மரம்_CODE (x) != PARM_DECL)
    warn_if_shadowing (x);

 skip_external_and_shadow_checks:
  எனில் (மரம்_CODE (x) == TYPE_DECL)
    {
      /* So this is a typedef, set its underlying type.  */
      set_underlying_type (x);

      /* If X is a typedef defined in the current function, record it
	 for the purpose of implementing the -Wunused-local-typedefs
	 warning.  */
      record_locally_defined_typedef (x);
    }

  bind (name, x, scope, /*invisible=*/பொய், nested, locus);

  /* If x's type is incomplete because it's based on a
     structure or union which has not yet been fully declared,
     attach it to that structure or union type, so we can go
     back and complete the variable declaration later, if the
     structure or union gets fully declared.

     If the input is erroneous, we can have error_mark in the type
     slot (e.g. "f(void a, ...)") - that doesn't count as an
     incomplete type.  */
  எனில் (மரம்_TYPE (x) != error_mark_முனை
      && !COMPLETE_TYPE_P (மரம்_TYPE (x)))
    {
      மரம் element = மரம்_TYPE (x);

      போது (மரம்_CODE (element) == ARRAY_TYPE)
	element = மரம்_TYPE (element);
      element = TYPE_MAIN_VARIANT (element);

      எனில் ((RECORD_OR_UNION_TYPE_P (element)
	   || மரம்_CODE (element) == ENUMERAL_TYPE)
	  && (மரம்_CODE (x) != TYPE_DECL
	      || மரம்_CODE (மரம்_TYPE (x)) == ARRAY_TYPE)
	  && !COMPLETE_TYPE_P (element))
	C_TYPE_INCOMPLETE_VARS (element)
	  = மரம்_cons (NULL_மரம், x, C_TYPE_INCOMPLETE_VARS (element));
    }
  திரும்பு x;
}


/* Issue a permerror about implicit function declaration.  ID is the function
   identifier, OLDDECL is a declaration of the function in a different scope,
   or NULL_TREE.  */

நிலையான வெறுமை
implicit_decl_permerror (location_t loc, மரம் id, மரம் olddecl)
{
  எனில் (!warn_implicit_function_declaration)
    திரும்பு;

  தருக்க warned;
  auto_diagnostic_group d;
  name_hint hint;
  எனில் (!olddecl)
    hint = lookup_name_fuzzy (id, FUZZY_LOOKUP_FUNCTION_NAME, loc);

  எனில் (flag_isoc99)
    {
      எனில் (மாறிலி எழுத்து *suggestion = hint.suggestion ())
	{
	  gcc_rich_location richloc (loc);
	  richloc.add_fixit_replace (suggestion);
	  warned = permerror_opt (&richloc, OPT_Wimplicit_function_declaration,
				  "implicit declaration of function %qE;"
				  " did you mean %qs?",
				  id, suggestion);
	}
      இல்லையெனில்
	warned = permerror_opt (loc, OPT_Wimplicit_function_declaration,
				"implicit declaration of function %qE", id);
    }
  இல்லையெனில் எனில் (மாறிலி எழுத்து *suggestion = hint.suggestion ())
    {
      gcc_rich_location richloc (loc);
      richloc.add_fixit_replace (suggestion);
      warned = warning_at
	(&richloc, OPT_Wimplicit_function_declaration,
	 G_("implicit declaration of function %qE; did you mean %qs?"),
	 id, suggestion);
    }
  இல்லையெனில்
    warned = warning_at (loc, OPT_Wimplicit_function_declaration,
			 G_("implicit declaration of function %qE"), id);

  எனில் (warned)
    {
      /* Whether the olddecl is an undeclared builtin function.
	 locate_old_decl will not generate a diagnostic for those,
	 so in that case we want to look elsewhere.  */
      தருக்க undeclared_builtin = (olddecl
				 && மரம்_CODE (olddecl) == FUNCTION_DECL
				 && fndecl_built_in_p (olddecl)
				 && !C_DECL_DECLARED_BUILTIN (olddecl));
      எனில் (undeclared_builtin)
	{
	  மாறிலி எழுத்து *header = header_for_builtin_fn (olddecl);
	  எனில் (header)
	    {
	      rich_location richloc (வரி_table, loc);
	      maybe_add_include_fixit (&richloc, header, உண்மை);
	      inform (&richloc,
		      "include %qs or provide a declaration of %qE",
		      header, id);
	    }
	}
      இல்லையெனில் எனில் (olddecl)
	locate_old_decl (olddecl);
    }

  எனில் (!warned)
    hint.suppress ();
}

/* Return the name of the header file that declares built-in function
   FNDECL, or null if either we don't know or don't expect to see an
   explicit declaration.  */

நிலையான மாறிலி எழுத்து *
header_for_builtin_fn (மரம் fndecl)
{
  எனில் (DECL_BUILT_IN_CLASS (fndecl) != BUILT_IN_NORMAL)
    திரும்பு வெற்று;

  தேர்வு (DECL_FUNCTION_CODE (fndecl))
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
    நிலை BUILT_IN_ISINF:
    நிலை BUILT_IN_ISNAN:
      திரும்பு "<math.h>";
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
      திரும்பு "<complex.h>";
    நிலை BUILT_IN_MEMCHR:
    நிலை BUILT_IN_MEMCMP:
    நிலை BUILT_IN_MEMCPY:
    நிலை BUILT_IN_MEMMOVE:
    நிலை BUILT_IN_MEMSET:
    நிலை BUILT_IN_STRCAT:
    நிலை BUILT_IN_STRCHR:
    நிலை BUILT_IN_STRCMP:
    நிலை BUILT_IN_STRCPY:
    நிலை BUILT_IN_STRCSPN:
    நிலை BUILT_IN_STRLEN:
    நிலை BUILT_IN_STRNCAT:
    நிலை BUILT_IN_STRNCMP:
    நிலை BUILT_IN_STRNCPY:
    நிலை BUILT_IN_STRPBRK:
    நிலை BUILT_IN_STRRCHR:
    நிலை BUILT_IN_STRSPN:
    நிலை BUILT_IN_STRSTR:
      திரும்பு "<string.h>";
    நிலை BUILT_IN_FPRINTF:
    நிலை BUILT_IN_PUTC:
    நிலை BUILT_IN_FPUTC:
    நிலை BUILT_IN_FPUTS:
    நிலை BUILT_IN_FSCANF:
    நிலை BUILT_IN_FWRITE:
    நிலை BUILT_IN_PRINTF:
    நிலை BUILT_IN_PUTCHAR:
    நிலை BUILT_IN_PUTS:
    நிலை BUILT_IN_SCANF:
    நிலை BUILT_IN_SNPRINTF:
    நிலை BUILT_IN_SPRINTF:
    நிலை BUILT_IN_SSCANF:
    நிலை BUILT_IN_VFPRINTF:
    நிலை BUILT_IN_VFSCANF:
    நிலை BUILT_IN_VPRINTF:
    நிலை BUILT_IN_VSCANF:
    நிலை BUILT_IN_VSNPRINTF:
    நிலை BUILT_IN_VSPRINTF:
    நிலை BUILT_IN_VSSCANF:
      திரும்பு "<stdio.h>";
    நிலை BUILT_IN_ISALNUM:
    நிலை BUILT_IN_ISALPHA:
    நிலை BUILT_IN_ISBLANK:
    நிலை BUILT_IN_ISCNTRL:
    நிலை BUILT_IN_ISDIGIT:
    நிலை BUILT_IN_ISGRAPH:
    நிலை BUILT_IN_ISLOWER:
    நிலை BUILT_IN_ISPRINT:
    நிலை BUILT_IN_ISPUNCT:
    நிலை BUILT_IN_ISSPACE:
    நிலை BUILT_IN_ISUPPER:
    நிலை BUILT_IN_ISXDIGIT:
    நிலை BUILT_IN_TOLOWER:
    நிலை BUILT_IN_TOUPPER:
      திரும்பு "<ctype.h>";
    நிலை BUILT_IN_ISWALNUM:
    நிலை BUILT_IN_ISWALPHA:
    நிலை BUILT_IN_ISWBLANK:
    நிலை BUILT_IN_ISWCNTRL:
    நிலை BUILT_IN_ISWDIGIT:
    நிலை BUILT_IN_ISWGRAPH:
    நிலை BUILT_IN_ISWLOWER:
    நிலை BUILT_IN_ISWPRINT:
    நிலை BUILT_IN_ISWPUNCT:
    நிலை BUILT_IN_ISWSPACE:
    நிலை BUILT_IN_ISWUPPER:
    நிலை BUILT_IN_ISWXDIGIT:
    நிலை BUILT_IN_TOWLOWER:
    நிலை BUILT_IN_TOWUPPER:
      திரும்பு "<wctype.h>";
    நிலை BUILT_IN_ABORT:
    நிலை BUILT_IN_ABS:
    நிலை BUILT_IN_CALLOC:
    நிலை BUILT_IN_EXIT:
    நிலை BUILT_IN_FREE:
    நிலை BUILT_IN_LABS:
    நிலை BUILT_IN_LLABS:
    நிலை BUILT_IN_MALLOC:
    நிலை BUILT_IN_REALLOC:
    நிலை BUILT_IN__EXIT2:
    நிலை BUILT_IN_ALIGNED_ALLOC:
      திரும்பு "<stdlib.h>";
    நிலை BUILT_IN_IMAXABS:
      திரும்பு "<inttypes.h>";
    நிலை BUILT_IN_STRFTIME:
      திரும்பு "<time.h>";
    இயல்பு:
      திரும்பு வெற்று;
    }
}

/* Generate an implicit declaration for identifier FUNCTIONID at LOC as a
   function of type int ().  */

மரம்
implicitly_declare (location_t loc, மரம் functionid)
{
  கட்டமைப்பு c_binding *b;
  மரம் decl = NULL_மரம்;
  மரம் asmspec_மரம்;

  க்கு (b = I_குறியீடு_BINDING (functionid); b; b = b->shadowed)
    {
      எனில் (B_IN_SCOPE (b, external_scope))
	{
	  decl = b->decl;
	  நிறுத்து;
	}
    }

  எனில் (decl)
    {
      எனில் (மரம்_CODE (decl) != FUNCTION_DECL)
	திரும்பு decl;

      /* FIXME: Objective-C has weird not-really-builtin functions
	 which are supposed to be visible automatically.  They wind up
	 in the external scope because they're pushed before the file
	 scope gets created.  Catch this here and rebind them into the
	 file scope.  */
      எனில் (!fndecl_built_in_p (decl) && DECL_IS_UNDECLARED_BUILTIN (decl))
	{
	  bind (functionid, decl, file_scope,
		/*invisible=*/பொய், /*nested=*/உண்மை,
		DECL_SOURCE_LOCATION (decl));
	  திரும்பு decl;
	}
      இல்லையெனில்
	{
	  மரம் newtype = default_function_type;
	  எனில் (b->u.type)
	    மரம்_TYPE (decl) = b->u.type;
	  /* Implicit declaration of a function already declared
	     (somehow) in a different scope, or as a built-in.
	     If this is the first time this has happened, warn;
	     then recycle the old declaration but with the new type.  */
	  எனில் (!C_DECL_IMPLICIT (decl))
	    {
	      implicit_decl_permerror (loc, functionid, decl);
	      C_DECL_IMPLICIT (decl) = 1;
	    }
	  எனில் (fndecl_built_in_p (decl))
	    {
	      newtype = c_build_type_attribute_variant (newtype,
							TYPE_ATTRIBUTES
							(மரம்_TYPE (decl)));
	      எனில் (!comptypes (newtype, மரம்_TYPE (decl)))
		{
		  auto_diagnostic_group d;
		  தருக்க warned = warning_at (loc,
					    OPT_Wbuiltin_declaration_mismatch,
					    "incompatible implicit "
					    "declaration of built-in "
					    "function %qD", decl);
		  /* See if we can hint which header to include.  */
		  மாறிலி எழுத்து *header = header_for_builtin_fn (decl);
		  எனில் (header != வெற்று && warned)
		    {
		      rich_location richloc (வரி_table, loc);
		      maybe_add_include_fixit (&richloc, header, உண்மை);
		      inform (&richloc,
			      "include %qs or provide a declaration of %qD",
			      header, decl);
		    }
		  newtype = மரம்_TYPE (decl);
		}
	    }
	  இல்லையெனில்
	    {
	      எனில் (!comptypes (newtype, மரம்_TYPE (decl)))
		{
		  auto_diagnostic_group d;
		  error_at (loc, "incompatible implicit declaration of "
			    "function %qD", decl);
		  locate_old_decl (decl);
		}
	    }
	  b->u.type = மரம்_TYPE (decl);
	  மரம்_TYPE (decl) = newtype;
	  bind (functionid, decl, current_scope,
		/*invisible=*/பொய், /*nested=*/உண்மை,
		DECL_SOURCE_LOCATION (decl));
	  திரும்பு decl;
	}
    }

  /* Not seen before.  */
  decl = build_decl (loc, FUNCTION_DECL, functionid, default_function_type);
  DECL_EXTERNAL (decl) = 1;
  மரம்_PUBLIC (decl) = 1;
  C_DECL_IMPLICIT (decl) = 1;
  implicit_decl_permerror (loc, functionid, 0);
  asmspec_மரம் = maybe_apply_renaming_pragma (decl, /*asmname=*/வெற்று);
  எனில் (asmspec_மரம்)
    set_user_assembler_name (decl, மரம்_STRING_POINTER (asmspec_மரம்));

  /* C89 says implicit declarations are in the innermost block.
     So we record the decl in the standard fashion.  */
  decl = pushdecl (decl);

  /* No need to call objc_check_decl here - it's a function type.  */
  rest_of_decl_compilation (decl, 0, 0);

  /* Write a record describing this implicit function declaration
     to the prototypes file (if requested).  */
  gen_aux_info_record (decl, 0, 1, 0);

  /* Possibly apply some default attributes to this implicit declaration.  */
  decl_attributes (&decl, NULL_மரம், 0);

  திரும்பு decl;
}

/* Issue an error message for a reference to an undeclared variable
   ID, including a reference to a builtin outside of function-call
   context.  Establish a binding of the identifier to error_mark_node
   in an appropriate scope, which will suppress further errors for the
   same identifier.  The error message should be given location LOC.  */
வெறுமை
undeclared_variable (location_t loc, மரம் id)
{
  நிலையான தருக்க already = பொய்;
  கட்டமைப்பு c_scope *scope;

  auto_diagnostic_group d;
  எனில் (current_function_decl == NULL_மரம்)
    {
      name_hint guessed_id = lookup_name_fuzzy (id, FUZZY_LOOKUP_NAME, loc);
      எனில் (மாறிலி எழுத்து *suggestion = guessed_id.suggestion ())
	{
	  gcc_rich_location richloc (loc);
	  richloc.add_fixit_replace (suggestion);
	  error_at (&richloc,
		    "%qE undeclared here (not in a function);"
		    " did you mean %qs?",
		    id, suggestion);
	}
      இல்லையெனில்
	error_at (loc, "%qE undeclared here (not in a function)", id);
      scope = current_scope;
    }
  இல்லையெனில்
    {
      எனில் (!objc_diagnose_private_ivar (id))
	{
	  name_hint guessed_id = lookup_name_fuzzy (id, FUZZY_LOOKUP_NAME, loc);
	  எனில் (மாறிலி எழுத்து *suggestion = guessed_id.suggestion ())
	    {
	      gcc_rich_location richloc (loc);
	      richloc.add_fixit_replace (suggestion);
	      error_at (&richloc,
			"%qE undeclared (first use in this function);"
			" did you mean %qs?",
			id, suggestion);
	    }
	  இல்லையெனில்
	    error_at (loc, "%qE undeclared (first use in this function)", id);
	}
      எனில் (!already)
	{
          inform (loc, "each undeclared identifier is reported only"
                  " once for each function it appears in");
	  already = உண்மை;
	}

      /* If we are parsing old-style parameter decls, current_function_decl
	 will be nonnull but current_function_scope will be null.  */
      scope = current_function_scope ? current_function_scope : current_scope;
    }
  bind (id, error_mark_முனை, scope, /*invisible=*/பொய், /*nested=*/பொய்,
	UNKNOWN_LOCATION);
}

/* Subroutine of lookup_label, declare_label, define_label: construct a
   LABEL_DECL with all the proper frills.  Also create a struct
   c_label_vars initialized for the current scope.  */

நிலையான மரம்
make_label (location_t location, மரம் name, தருக்க defining,
	    கட்டமைப்பு c_label_vars **p_label_vars)
{
  மரம் label = build_decl (location, LABEL_DECL, name, void_type_முனை);
  DECL_CONTEXT (label) = current_function_decl;
  SET_DECL_MODE (label, VOIDmode);

  c_label_vars *label_vars = ggc_alloc<c_label_vars> ();
  label_vars->shadowed = வெற்று;
  set_spot_bindings (&label_vars->label_bindings, defining);
  label_vars->decls_in_scope = make_மரம்_vector ();
  label_vars->gotos = வெற்று;
  *p_label_vars = label_vars;

  திரும்பு label;
}

/* Get the LABEL_DECL corresponding to identifier NAME as a label.
   Create one if none exists so far for the current function.
   This is called when a label is used in a goto expression or
   has its address taken.  */

மரம்
lookup_label (மரம் name)
{
  மரம் label;
  கட்டமைப்பு c_label_vars *label_vars;

  எனில் (current_function_scope == 0)
    {
      error ("label %qE referenced outside of any function", name);
      திரும்பு NULL_மரம்;
    }

  /* Use a label already defined or ref'd with this name, but not if
     it is inherited from a containing function and wasn't declared
     using __label__.  */
  label = I_LABEL_DECL (name);
  எனில் (label && (DECL_CONTEXT (label) == current_function_decl
		|| C_DECLARED_LABEL_FLAG (label)))
    {
      /* If the label has only been declared, update its apparent
	 location to point here, for better diagnostics if it
	 turns out not to have been defined.  */
      எனில் (DECL_INITIAL (label) == NULL_மரம்)
	DECL_SOURCE_LOCATION (label) = உள்ளீடு_location;
      திரும்பு label;
    }

  /* No label binding for that identifier; make one.  */
  label = make_label (உள்ளீடு_location, name, பொய், &label_vars);

  /* Ordinary labels go in the current function scope.  */
  bind_label (name, label, current_function_scope, label_vars);

  திரும்பு label;
}

/* Issue a warning about DECL for a goto statement at GOTO_LOC going
   to LABEL.  */

நிலையான வெறுமை
warn_about_goto (location_t goto_loc, மரம் label, மரம் decl)
{
  auto_diagnostic_group d;
  எனில் (c_type_variably_modified_p (மரம்_TYPE (decl)))
    error_at (goto_loc,
	      "jump into scope of identifier with variably modified type");
  இல்லையெனில் எனில் (flag_openmp
	   && lookup_attribute ("omp allocate", DECL_ATTRIBUTES (decl)))
    error_at (goto_loc, "jump skips OpenMP %<allocate%> allocation");
  இல்லையெனில்
    எனில் (!warning_at (goto_loc, OPT_Wjump_misses_init,
		     "jump skips variable initialization"))
      திரும்பு;
  inform (DECL_SOURCE_LOCATION (label), "label %qD defined here", label);
  inform (DECL_SOURCE_LOCATION (decl), "%qD declared here", decl);
}

/* Look up a label because of a goto statement.  This is like
   lookup_label, but also issues any appropriate warnings.  */

மரம்
lookup_label_for_goto (location_t loc, மரம் name)
{
  மரம் label;
  கட்டமைப்பு c_label_vars *label_vars;
  unsigned முழு ix;
  மரம் decl;

  label = lookup_label (name);
  எனில் (label == NULL_மரம்)
    திரும்பு NULL_மரம்;

  /* If we are jumping to a different function, we can't issue any
     useful warnings.  */
  எனில் (DECL_CONTEXT (label) != current_function_decl)
    {
      gcc_assert (C_DECLARED_LABEL_FLAG (label));
      திரும்பு label;
    }

  label_vars = I_LABEL_BINDING (name)->u.label;

  /* If the label has not yet been defined, then push this goto on a
     list for possible later warnings.  */
  எனில் (label_vars->label_bindings.scope == வெற்று)
    {
      c_goto_bindings *g = ggc_alloc<c_goto_bindings> ();

      g->loc = loc;
      set_spot_bindings (&g->goto_bindings, உண்மை);
      vec_safe_தள்ளு (label_vars->gotos, g);
      திரும்பு label;
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

  எனில் (label_vars->label_bindings.இடது_stmt_கோவை)
    {
      auto_diagnostic_group d;
      error_at (loc, "jump into statement expression");
      inform (DECL_SOURCE_LOCATION (label), "label %qD defined here", label);
    }

  திரும்பு label;
}

/* Make a label named NAME in the current function, shadowing silently
   any that may be inherited from containing functions or containing
   scopes.  This is called for __label__ declarations.  */

மரம்
declare_label (மரம் name)
{
  கட்டமைப்பு c_binding *b = I_LABEL_BINDING (name);
  மரம் label;
  கட்டமைப்பு c_label_vars *label_vars;

  /* Check to make sure that the label hasn't already been declared
     at this scope */
  எனில் (b && B_IN_CURRENT_SCOPE (b))
    {
      auto_diagnostic_group d;
      error ("duplicate label declaration %qE", name);
      locate_old_decl (b->decl);

      /* Just use the previous declaration.  */
      திரும்பு b->decl;
    }

  label = make_label (உள்ளீடு_location, name, பொய், &label_vars);
  C_DECLARED_LABEL_FLAG (label) = 1;

  /* Declared labels go in the current scope.  */
  bind_label (name, label, current_scope, label_vars);

  திரும்பு label;
}

/* When we define a label, issue any appropriate warnings if there are
   any gotos earlier in the function which jump to this label.  */

நிலையான வெறுமை
check_earlier_gotos (மரம் label, கட்டமைப்பு c_label_vars* label_vars)
{
  unsigned முழு ix;
  கட்டமைப்பு c_goto_bindings *g;

  FOR_EACH_VEC_SAFE_ELT (label_vars->gotos, ix, g)
    {
      கட்டமைப்பு c_binding *b;
      கட்டமைப்பு c_scope *scope;

      /* We have a goto to this label.  The goto is going forward.  In
	 g->scope, the goto is going to skip any binding which was
	 defined after g->bindings_in_scope.  */
      எனில் (g->goto_bindings.scope->has_jump_unsafe_decl)
	{
	  க்கு (b = g->goto_bindings.scope->bindings;
	       b != g->goto_bindings.bindings_in_scope;
	       b = b->prev)
	    {
	      எனில் (decl_jump_unsafe (b->decl))
		warn_about_goto (g->loc, label, b->decl);
	    }
	}

      /* We also need to warn about decls defined in any scopes
	 between the scope of the label and the scope of the goto.  */
      க்கு (scope = label_vars->label_bindings.scope;
	   scope != g->goto_bindings.scope;
	   scope = scope->outer)
	{
	  gcc_assert (scope != வெற்று);
	  எனில் (scope->has_jump_unsafe_decl)
	    {
	      எனில் (scope == label_vars->label_bindings.scope)
		b = label_vars->label_bindings.bindings_in_scope;
	      இல்லையெனில்
		b = scope->bindings;
	      க்கு (; b != வெற்று; b = b->prev)
		{
		  எனில் (decl_jump_unsafe (b->decl))
		    warn_about_goto (g->loc, label, b->decl);
		}
	    }
	}

      எனில் (g->goto_bindings.stmt_exprs > 0)
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
  label_vars->gotos = வெற்று;
}

/* Define a label, specifying the location in the source file.
   Return the LABEL_DECL node for the label, if the definition is valid.
   Otherwise return NULL_TREE.  */

மரம்
define_label (location_t location, மரம் name)
{
  /* Find any preexisting label with this name.  It is an error
     if that label has already been defined in this function, or
     if there is a containing function with a declared label with
     the same name.  */
  மரம் label = I_LABEL_DECL (name);

  எனில் (label
      && ((DECL_CONTEXT (label) == current_function_decl
	   && DECL_INITIAL (label) != NULL_மரம்)
	  || (DECL_CONTEXT (label) != current_function_decl
	      && C_DECLARED_LABEL_FLAG (label))))
    {
      auto_diagnostic_group d;
      error_at (location, "duplicate label %qD", label);
      locate_old_decl (label);
      திரும்பு NULL_மரம்;
    }
  இல்லையெனில் எனில் (label && DECL_CONTEXT (label) == current_function_decl)
    {
      கட்டமைப்பு c_label_vars *label_vars = I_LABEL_BINDING (name)->u.label;

      /* The label has been used or declared already in this function,
	 but not defined.  Update its location to point to this
	 definition.  */
      DECL_SOURCE_LOCATION (label) = location;
      set_spot_bindings (&label_vars->label_bindings, உண்மை);

      /* Issue warnings as required about any goto statements from
	 earlier in the function.  */
      check_earlier_gotos (label, label_vars);
    }
  இல்லையெனில்
    {
      கட்டமைப்பு c_label_vars *label_vars;

      /* No label binding for that identifier; make one.  */
      label = make_label (location, name, உண்மை, &label_vars);

      /* Ordinary labels go in the current function scope.  */
      bind_label (name, label, current_function_scope, label_vars);
    }

  எனில் (!in_system_header_at (உள்ளீடு_location) && lookup_name (name))
    warning_at (location, OPT_Wtraditional,
		"traditional C lacks a separate namespace "
		"for labels, identifier %qE conflicts", name);

  /* Mark label as having been defined.  */
  DECL_INITIAL (label) = error_mark_முனை;
  திரும்பு label;
}

/* Get the bindings for a new switch statement.  This is used to issue
   warnings as appropriate for jumps from the switch to case or
   default labels.  */

கட்டமைப்பு c_spot_bindings *
c_get_switch_bindings (வெறுமை)
{
  கட்டமைப்பு c_spot_bindings *switch_bindings;

  switch_bindings = XNEW (கட்டமைப்பு c_spot_bindings);
  set_spot_bindings (switch_bindings, உண்மை);
  திரும்பு switch_bindings;
}

வெறுமை
c_release_switch_bindings (கட்டமைப்பு c_spot_bindings *bindings)
{
  gcc_assert (bindings->stmt_exprs == 0 && !bindings->இடது_stmt_கோவை);
  XDELETE (bindings);
}

/* This is called at the point of a case or default label to issue
   warnings about decls as needed.  It returns true if it found an
   error, not just a warning.  */

தருக்க
c_check_switch_jump_warnings (கட்டமைப்பு c_spot_bindings *switch_bindings,
			      location_t switch_loc, location_t case_loc)
{
  தருக்க saw_error;
  கட்டமைப்பு c_scope *scope;

  saw_error = பொய்;
  க்கு (scope = current_scope;
       scope != switch_bindings->scope;
       scope = scope->outer)
    {
      கட்டமைப்பு c_binding *b;

      gcc_assert (scope != வெற்று);

      எனில் (!scope->has_jump_unsafe_decl)
	தொடர்;

      க்கு (b = scope->bindings; b != வெற்று; b = b->prev)
	{
	  எனில் (decl_jump_unsafe (b->decl))
	    {
	      auto_diagnostic_group d;
	      தருக்க emitted;
	      எனில் (c_type_variably_modified_p (மரம்_TYPE (b->decl)))
		{
		  saw_error = உண்மை;
		  error_at (case_loc,
			    "switch jumps into scope of identifier with "
			    "variably modified type");
		  emitted = உண்மை;
		}
	      இல்லையெனில் எனில் (flag_openmp
		       && lookup_attribute ("omp allocate",
					    DECL_ATTRIBUTES (b->decl)))
		{
		  saw_error = உண்மை;
		  error_at (case_loc,
			    "switch jumps over OpenMP %<allocate%> allocation");
		  emitted = உண்மை;
		}
	      இல்லையெனில்
		emitted
		  = warning_at (case_loc, OPT_Wjump_misses_init,
				"switch jumps over variable initialization");
	      எனில் (emitted)
		{
		  inform (switch_loc, "switch starts here");
		  inform (DECL_SOURCE_LOCATION (b->decl), "%qD declared here",
			  b->decl);
		}
	    }
	}
    }

  எனில் (switch_bindings->stmt_exprs > 0)
    {
      saw_error = உண்மை;
      auto_diagnostic_group d;
      error_at (case_loc, "switch jumps into statement expression");
      inform (switch_loc, "switch starts here");
    }

  திரும்பு saw_error;
}

/* Given NAME, an IDENTIFIER_NODE,
   return the structure (or union or enum) definition for that name.
   If THISLEVEL_ONLY is nonzero, searches only the current_scope.
   CODE says which kind of type the caller wants;
   it is RECORD_TYPE or UNION_TYPE or ENUMERAL_TYPE.
   If PLOC is not NULL and this returns non-null, it sets *PLOC to the
   location where the tag was defined.
   If the wrong kind of type is found, an error is reported.  */

நிலையான மரம்
lookup_tag (எண்ணிக்கை மரம்_code code, மரம் name, தருக்க thislevel_only,
	    location_t *ploc)
{
  கட்டமைப்பு c_binding *b = I_TAG_BINDING (name);
  தருக்க thislevel = பொய்;

  எனில் (!b || !b->decl)
    திரும்பு NULL_மரம்;

  /* We only care about whether it's in this level if
     thislevel_only was set or it might be a type clash.  */
  எனில் (thislevel_only || மரம்_CODE (b->decl) != code)
    {
      /* For our purposes, a tag in the external scope is the same as
	 a tag in the file scope.  (Primarily relevant to Objective-C
	 and its builtin structure tags, which get pushed before the
	 file scope is created.)  */
      எனில் (B_IN_CURRENT_SCOPE (b)
	  || (current_scope == file_scope && B_IN_EXTERNAL_SCOPE (b)))
	thislevel = உண்மை;
    }

  எனில் (thislevel_only && !thislevel)
    திரும்பு NULL_மரம்;

  எனில் (மரம்_CODE (b->decl) != code)
    {
      /* Definition isn't the kind we were looking for.  */
      pending_invalid_xref = name;
      pending_invalid_xref_location = உள்ளீடு_location;

      /* If in the same binding level as a declaration as a tag
	 of a different type, this must not be allowed to
	 shadow that tag, so give the error immediately.
	 (For example, "struct foo; union foo;" is invalid.)  */
      எனில் (thislevel)
	pending_xref_error ();
    }

  எனில் (ploc != வெற்று)
    *ploc = b->locus;

  திரும்பு b->decl;
}

/* Return true if a definition exists for NAME with code CODE.  */

தருக்க
tag_exists_p (எண்ணிக்கை மரம்_code code, மரம் name)
{
  கட்டமைப்பு c_binding *b = I_TAG_BINDING (name);

  எனில் (b == வெற்று || b->decl == NULL_மரம்)
    திரும்பு பொய்;
  திரும்பு மரம்_CODE (b->decl) == code;
}

/* Print an error message now
   for a recent invalid struct, union or enum cross reference.
   We don't print them immediately because they are not invalid
   when used in the `struct foo;' construct for shadowing.  */

வெறுமை
pending_xref_error (வெறுமை)
{
  எனில் (pending_invalid_xref != NULL_மரம்)
    error_at (pending_invalid_xref_location, "%qE defined as wrong kind of tag",
	      pending_invalid_xref);
  pending_invalid_xref = NULL_மரம்;
}


/* Look up NAME in the current scope and its superiors
   in the namespace of variables, functions and typedefs.
   Return a ..._DECL node of some kind representing its definition,
   or return NULL_TREE if it is undefined.  */

மரம்
lookup_name (மரம் name)
{
  கட்டமைப்பு c_binding *b = I_குறியீடு_BINDING (name);
  /* Do not resolve non-default function versions.  */
  எனில் (b
      && மரம்_CODE (b->decl) == FUNCTION_DECL
      && DECL_FUNCTION_VERSIONED (b->decl)
      && !is_function_default_version (b->decl))
    திரும்பு NULL_மரம்;
  எனில் (b && !b->invisible)
    {
      maybe_record_typedef_use (b->decl);
      திரும்பு b->decl;
    }
  திரும்பு NULL_மரம்;
}

/* Similar to `lookup_name' but look only at the indicated scope.  */

நிலையான மரம்
lookup_name_in_scope (மரம் name, கட்டமைப்பு c_scope *scope)
{
  கட்டமைப்பு c_binding *b;

  க்கு (b = I_குறியீடு_BINDING (name); b; b = b->shadowed)
    எனில் (B_IN_SCOPE (b, scope))
      திரும்பு b->decl;
  திரும்பு NULL_மரம்;
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
lookup_name_fuzzy (மரம் name, எண்ணிக்கை lookup_name_fuzzy_kind kind, location_t loc)
{
  gcc_assert (மரம்_CODE (name) == IDENTIFIER_முனை);

  /* Look up function-like macros first; maybe misusing them. */
  auto cpp_முனை = cpp_lookup (parse_in,
			      (மாறிலி unsigned எழுத்து*)IDENTIFIER_POINTER (name),
			      IDENTIFIER_LENGTH (name));
  எனில் (cpp_முனை && cpp_fun_like_macro_p (cpp_முனை))
    திரும்பு name_hint
      (nullptr,
       std::make_unique<macro_like_function_used> (loc,
						   IDENTIFIER_POINTER (name)));

  /* Next, try some well-known names in the C standard library, in case
     the user forgot a #include.  */
  மாறிலி எழுத்து *header_hint
    = get_c_stdlib_header_for_name (IDENTIFIER_POINTER (name));

  எனில் (header_hint)
    திரும்பு name_hint
      (nullptr,
       std::make_unique<suggest_missing_header> (loc,
						 IDENTIFIER_POINTER (name),
						 header_hint));

  /* Next, look for exact matches for builtin defines that would have been
     defined if the user had passed a command-line option (e.g. -fopenmp
     for "_OPENMP").  */
  diagnostics::option_id option_id
    = get_option_for_builtin_define (IDENTIFIER_POINTER (name));
  எனில் (option_id.m_idx > 0)
    திரும்பு name_hint
      (nullptr,
       std::make_unique<suggest_missing_option> (loc,
						 IDENTIFIER_POINTER (name),
						 option_id));

  /* Only suggest names reserved for the implementation if NAME begins
     with an underscore.  */
  தருக்க consider_implementation_names = (IDENTIFIER_POINTER (name)[0] == '_');

  best_match<மரம், மரம்> bm (name);

  /* Look within currently valid scopes.  */
  க்கு (c_scope *scope = current_scope; scope; scope = scope->outer)
    க்கு (c_binding *binding = scope->bindings; binding; binding = binding->prev)
      {
	எனில் (!binding->id || binding->invisible)
	  தொடர்;
	எனில் (binding->decl == error_mark_முனை)
	  தொடர்;
	/* Don't use bindings from implicitly declared functions,
	   as they were likely misspellings themselves.  */
	எனில் (மரம்_CODE (binding->decl) == FUNCTION_DECL)
	  எனில் (C_DECL_IMPLICIT (binding->decl))
	    தொடர்;
	/* Don't suggest names that are reserved for use by the
	   implementation, unless NAME began with an underscore.  */
	எனில் (!consider_implementation_names)
	  {
	    மாறிலி எழுத்து *suggestion_str = IDENTIFIER_POINTER (binding->id);
	    எனில் (name_reserved_for_implementation_p (suggestion_str))
	      தொடர்;
	  }
	தேர்வு (kind)
	  {
	  நிலை FUZZY_LOOKUP_TYPENAME:
	    எனில் (மரம்_CODE (binding->decl) != TYPE_DECL)
	      தொடர்;
	    நிறுத்து;

	  நிலை FUZZY_LOOKUP_FUNCTION_NAME:
	    எனில் (மரம்_CODE (binding->decl) != FUNCTION_DECL)
	      {
		/* Allow function pointers.  */
		எனில் ((VAR_P (binding->decl)
		     || மரம்_CODE (binding->decl) == PARM_DECL)
		    && மரம்_CODE (மரம்_TYPE (binding->decl)) == POINTER_TYPE
		    && (மரம்_CODE (மரம்_TYPE (மரம்_TYPE (binding->decl)))
			== FUNCTION_TYPE))
		  நிறுத்து;
		தொடர்;
	      }
	    நிறுத்து;

	  இயல்பு:
	    நிறுத்து;
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
  எனில் (best_macro)
    {
      மாறிலி எழுத்து *id = (மாறிலி எழுத்து *)best_macro->ident.str;
      மரம் macro_as_identifier
	= get_identifier_with_length (id, best_macro->ident.len);
      bm.set_best_so_far (macro_as_identifier,
			  bmm.get_best_distance (),
			  bmm.get_best_candidate_length ());
    }

  /* Try the "start_typename" keywords to detect
     "singed" vs "signed" typos.  */
  எனில் (kind == FUZZY_LOOKUP_TYPENAME)
    {
      க்கு (unsigned i = 0; i < இலக்கம்_c_common_reswords; i++)
	{
	  மாறிலி c_common_resword *resword = &c_common_reswords[i];
	  எனில் (!c_keyword_starts_typename (resword->rid))
	    தொடர்;
	  மரம் resword_identifier = ridpointers [resword->rid];
	  எனில் (!resword_identifier)
	    தொடர்;
	  gcc_assert (மரம்_CODE (resword_identifier) == IDENTIFIER_முனை);
	  bm.consider (resword_identifier);
	}
    }

  மரம் best = bm.get_best_meaningful_candidate ();
  எனில் (best)
    திரும்பு name_hint (IDENTIFIER_POINTER (best), வெற்று);
  இல்லையெனில்
    திரும்பு name_hint (வெற்று, வெற்று);
}


/* Handle the standard [[nodiscard]] attribute.  */

நிலையான மரம்
handle_nodiscard_attribute (மரம் *முனை, மரம் name, மரம் /*args*/,
			    முழு /*flags*/, தருக்க *no_add_attrs)
{
  எனில் (மரம்_CODE (*முனை) == FUNCTION_DECL)
    {
      எனில் (VOID_TYPE_P (மரம்_TYPE (மரம்_TYPE (*முனை))))
	warning_at (DECL_SOURCE_LOCATION (*முனை),
		    OPT_Wattributes, "%qE attribute applied to %qD with void "
		    "return type", name, *முனை);
    }
  இல்லையெனில் எனில் (RECORD_OR_UNION_TYPE_P (*முனை)
	   || மரம்_CODE (*முனை) == ENUMERAL_TYPE)
    /* OK */;
  இல்லையெனில்
    {
      pedwarn (உள்ளீடு_location,
	       OPT_Wattributes, "%qE attribute can only be applied to "
	       "functions or to structure, union or enumeration types", name);
      *no_add_attrs = உண்மை;
    }
  திரும்பு NULL_மரம்;
}

/* Handle the standard [[noreturn]] attribute.  */

நிலையான மரம்
handle_std_noreturn_attribute (மரம் *முனை, மரம் name, மரம் args,
			       முழு flags, தருக்க *no_add_attrs)
{
  /* Unlike GNU __attribute__ ((noreturn)), the standard [[noreturn]]
     only applies to functions, not function pointers.  */
  எனில் (மரம்_CODE (*முனை) == FUNCTION_DECL)
    திரும்பு handle_noreturn_attribute (முனை, name, args, flags, no_add_attrs);
  இல்லையெனில்
    {
      pedwarn (உள்ளீடு_location, OPT_Wattributes,
	       "standard %qE attribute can only be applied to functions",
	       name);
      *no_add_attrs = உண்மை;
      திரும்பு NULL_மரம்;
    }
}

/* Handle the standard [[unsequenced]] attribute.  */

நிலையான மரம்
handle_std_unsequenced_attribute (மரம் *முனை, மரம் name, மரம் args,
				  முழு flags, தருக்க *no_add_attrs)
{
  /* Unlike GNU __attribute__ ((unsequenced)), the standard [[unsequenced]]
     should be only applied to function declarators or type specifiers which
     have function type.  */
  எனில் (முனை[2])
    {
      auto_diagnostic_group d;
      எனில் (pedwarn (உள்ளீடு_location, OPT_Wattributes,
		   "standard %qE attribute can only be applied to function "
		   "declarators or type specifiers with function type", name))
	inform (உள்ளீடு_location, "did you mean to specify it after %<)%> "
				"following function parameters?");
      *no_add_attrs = உண்மை;
      திரும்பு NULL_மரம்;
    }
  திரும்பு handle_unsequenced_attribute (முனை, name, args, flags, no_add_attrs);
}

/* Handle the standard [[reproducible]] attribute.  */

நிலையான மரம்
handle_std_reproducible_attribute (மரம் *முனை, மரம் name, மரம் args,
				   முழு flags, தருக்க *no_add_attrs)
{
  திரும்பு handle_std_unsequenced_attribute (முனை, name, args, flags,
					   no_add_attrs);
}

/* Table of supported standard (C23) attributes.  */
நிலையான மாறிலி attribute_spec std_attributes[] =
{
  /* { name, min_len, max_len, decl_req, type_req, fn_type_req,
       affects_type_identity, handler, exclude } */
  { "_Noreturn", 0, 0, பொய், பொய், பொய், பொய்,
    handle_std_noreturn_attribute, வெற்று },
  { "deprecated", 0, 1, பொய், பொய், பொய், பொய்,
    handle_deprecated_attribute, வெற்று },
  { "fallthrough", 0, 0, பொய், பொய், பொய், பொய்,
    handle_fallthrough_attribute, வெற்று },
  { "maybe_unused", 0, 0, பொய், பொய், பொய், பொய்,
    handle_unused_attribute, வெற்று },
  { "nodiscard", 0, 1, பொய், பொய், பொய், பொய்,
    handle_nodiscard_attribute, வெற்று },
  { "noreturn", 0, 0, பொய், பொய், பொய், பொய்,
    handle_std_noreturn_attribute, வெற்று },
  { "reproducible", 0, 0, பொய், உண்மை, உண்மை, பொய்,
    handle_std_reproducible_attribute, வெற்று },
  { "unsequenced", 0, 0, பொய், உண்மை, உண்மை, பொய்,
    handle_std_unsequenced_attribute, வெற்று }
};

மாறிலி scoped_attribute_specs std_attribute_table =
{
  nullptr, { std_attributes }
};

/* Create the predefined scalar types of C,
   and some nodes representing standard constants (0, 1, (void *) 0).
   Initialize the global scope.
   Make definitions for built-in primitive functions.  */

வெறுமை
c_init_decl_processing (வெறுமை)
{
  location_t save_loc = உள்ளீடு_location;

  /* Initialize reserved words for parser.  */
  c_parse_init ();

  current_function_decl = NULL_மரம்;

  gcc_obstack_init (&parser_obstack);

  /* Make the externals scope.  */
  தள்ளு_scope ();
  external_scope = current_scope;

  /* Declarations from c_common_nodes_and_builtins must not be associated
     with this input file, lest we get differences between using and not
     using preprocessed headers.  */
  உள்ளீடு_location = BUILTINS_LOCATION;

  c_common_nodes_and_builtins ();

  /* In C, comparisons and TRUTH_* expressions have type int.  */
  truthvalue_type_முனை = integer_type_முனை;
  truthvalue_true_முனை = integer_one_முனை;
  truthvalue_false_முனை = integer_zero_முனை;

  /* Even in C99, which has a real boolean type.  */
  pushdecl (build_decl (UNKNOWN_LOCATION, TYPE_DECL,
			get_identifier (flag_isoc23 ? "bool" : "_Bool"),
			boolean_type_முனை));

  /* C-specific nullptr initialization.  */
  record_builtin_type (RID_MAX, "typeof (nullptr)", nullptr_type_முனை);
  /* The size and alignment of nullptr_t is the same as for a pointer to
     character type.  */
  SET_TYPE_ALIGN (nullptr_type_முனை, GET_MODE_ALIGNMENT (ptr_mode));

  உள்ளீடு_location = save_loc;

  make_fname_decl = c_make_fname_decl;
  start_fname_decls ();

  எனில் (warn_keyword_macro)
    {
      க்கு (unsigned முழு i = 0; i < இலக்கம்_c_common_reswords; ++i)
	/* For C register keywords which don't start with underscore
	   or start with just single underscore.  Don't complain about
	   ObjC or Transactional Memory keywords.  */
	எனில் (c_common_reswords[i].word[0] == '_'
	    && c_common_reswords[i].word[1] == '_')
	  தொடர்;
	இல்லையெனில் எனில் (c_common_reswords[i].disable
		 & (D_TRANSMEM | D_OBJC | D_CXX_OBJC))
	  தொடர்;
	இல்லையெனில்
	  {
	    மரம் id = get_identifier (c_common_reswords[i].word);
	    எனில் (C_IS_RESERVED_WORD (id)
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

நிலையான மரம்
c_make_fname_decl (location_t loc, மரம் id, முழு type_dep)
{
  மாறிலி எழுத்து *name = fname_as_string (type_dep);
  மரம் decl, type, init;
  size_t length = strlen (name);

  type = c_build_array_type (char_type_முனை,
			     build_index_type (size_int (length)));
  type = c_build_qualified_type (type, TYPE_QUAL_CONST);

  decl = build_decl (loc, VAR_DECL, id, type);

  மரம்_STATIC (decl) = 1;
  மரம்_READONLY (decl) = 1;
  DECL_ARTIFICIAL (decl) = 1;

  init = build_string (length + 1, name);
  விடுவி (const_cast<எழுத்து *> (name));
  மரம்_TYPE (init) = type;
  DECL_INITIAL (decl) = init;

  மரம்_USED (decl) = 1;

  எனில் (current_function_decl
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
	    /*invisible=*/பொய், /*nested=*/பொய், UNKNOWN_LOCATION);
    }

  finish_decl (decl, loc, init, NULL_மரம், NULL_மரம்);

  திரும்பு decl;
}

மரம்
c_builtin_function (மரம் decl)
{
  மரம் type = மரம்_TYPE (decl);
  மரம்   id = DECL_NAME (decl);

  மாறிலி எழுத்து *name = IDENTIFIER_POINTER (id);
  C_DECL_BUILTIN_PROTOTYPE (decl) = prototype_p (type);

  /* Should never be called on a symbol with a preexisting meaning.  */
  gcc_assert (!I_குறியீடு_BINDING (id));

  bind (id, decl, external_scope, /*invisible=*/உண்மை, /*nested=*/பொய்,
	UNKNOWN_LOCATION);

  /* Builtins in the implementation namespace are made visible without
     needing to be explicitly declared.  See push_file_scope.  */
  எனில் (name[0] == '_' && (name[1] == '_' || ISUPPER (name[1])))
    {
      DECL_CHAIN (decl) = visible_builtins;
      visible_builtins = decl;
    }

  திரும்பு decl;
}

மரம்
c_builtin_function_ext_scope (மரம் decl)
{
  மரம் type = மரம்_TYPE (decl);
  மரம்   id = DECL_NAME (decl);

  மாறிலி எழுத்து *name = IDENTIFIER_POINTER (id);
  C_DECL_BUILTIN_PROTOTYPE (decl) = prototype_p (type);

  எனில் (external_scope)
    bind (id, decl, external_scope, /*invisible=*/பொய், /*nested=*/பொய்,
	  UNKNOWN_LOCATION);

  /* Builtins in the implementation namespace are made visible without
     needing to be explicitly declared.  See push_file_scope.  */
  எனில் (name[0] == '_' && (name[1] == '_' || ISUPPER (name[1])))
    {
      DECL_CHAIN (decl) = visible_builtins;
      visible_builtins = decl;
    }

  திரும்பு decl;
}

/* Implement LANG_HOOKS_SIMULATE_BUILTIN_FUNCTION_DECL.  */

மரம்
c_simulate_builtin_function_decl (மரம் decl)
{
  மரம் type = மரம்_TYPE (decl);
  C_DECL_BUILTIN_PROTOTYPE (decl) = prototype_p (type);
  திரும்பு pushdecl (decl);
}

/* Warn about attributes in a context where they are unused
   (attribute-declarations, except for the "fallthrough" case, and
   attributes on statements).  */

வெறுமை
c_warn_unused_attributes (மரம் attrs)
{
  க்கு (மரம் t = attrs; t != NULL_மரம்; t = மரம்_CHAIN (t))
    எனில் (get_attribute_namespace (t) == NULL_மரம்)
      /* The specifications of standard attributes mean this is a
	 constraint violation.  */
      pedwarn (உள்ளீடு_location, OPT_Wattributes, "%qE attribute ignored",
	       get_attribute_name (t));
    இல்லையெனில் எனில் (!attribute_ignored_p (t))
      warning (OPT_Wattributes, "%qE attribute ignored",
	       get_attribute_name (t));
}

/* Warn for standard attributes being applied to a type that is not
   being defined, where that is a constraint violation, and return a
   list of attributes with them removed.  */

மரம்
c_warn_type_attributes (மரம் type, மரம் attrs)
{
  மரம் *attr_ptr = &attrs;
  போது (*attr_ptr)
    எனில் (get_attribute_namespace (*attr_ptr) == NULL_மரம்)
      {
	எனில் (மரம்_CODE (type) == FUNCTION_TYPE)
	  {
	    மரம் name = get_attribute_name (*attr_ptr);
	    /* [[unsequenced]] and [[reproducible]] is fine on function
	       types that aren't being defined.  */
	    எனில் (is_attribute_p ("unsequenced", name)
		|| is_attribute_p ("reproducible", name))
	      {
		attr_ptr = &மரம்_CHAIN (*attr_ptr);
		தொடர்;
	      }
	  }
	pedwarn (உள்ளீடு_location, OPT_Wattributes, "%qE attribute ignored",
		 get_attribute_name (*attr_ptr));
	*attr_ptr = மரம்_CHAIN (*attr_ptr);
      }
    இல்லையெனில்
      attr_ptr = &மரம்_CHAIN (*attr_ptr);
  திரும்பு attrs;
}

/* Called when a declaration is seen that contains no names to declare.
   If its type is a reference to a structure, union or enum inherited
   from a containing scope, shadow that tag name for the current scope
   with a forward reference.
   If its type defines a new named structure or union
   or defines an enum, it is valid but we need not do anything here.
   Otherwise, it is an error.  */

வெறுமை
shadow_tag (மாறிலி கட்டமைப்பு c_declspecs *declspecs)
{
  shadow_tag_warned (declspecs, 0);
}

/* WARNED is 1 if we have done a pedwarn, 2 if we have done a warning,
   but no pedwarn.  */
வெறுமை
shadow_tag_warned (மாறிலி கட்டமைப்பு c_declspecs *declspecs, முழு warned)
{
  தருக்க found_tag = பொய்;

  எனில் (declspecs->type && !declspecs->default_int_p && !declspecs->typedef_p)
    {
      மரம் மதிப்பு = declspecs->type;
      எண்ணிக்கை மரம்_code code = மரம்_CODE (மதிப்பு);

      எனில் (code == RECORD_TYPE || code == UNION_TYPE || code == ENUMERAL_TYPE)
	/* Used to test also that TYPE_SIZE (value) != 0.
	   That caused warning for `struct foo;' at top level in the file.  */
	{
	  மரம் name = TYPE_NAME (மதிப்பு);
	  மரம் t;

	  found_tag = உண்மை;

	  எனில் (declspecs->restrict_p)
	    {
	      error ("invalid use of %<restrict%>");
	      warned = 1;
	    }

	  எனில் (in_underspecified_init)
	    {
	      /* This can only occur with extensions such as statement
		 expressions, but is still appropriate as an error to
		 avoid types declared in such a context escaping to
		 the type of an auto variable.  */
	      error ("%qT declared in underspecified object initializer",
		     மதிப்பு);
	      warned = 1;
	    }

	  எனில் (name == NULL_மரம்)
	    {
	      எனில் (warned != 1 && code != ENUMERAL_TYPE)
		/* Empty unnamed enum OK */
		{
		  pedwarn (உள்ளீடு_location, 0,
			   "unnamed struct/union that defines no instances");
		  warned = 1;
		}
	    }
	  இல்லையெனில் எனில் (declspecs->typespec_kind != ctsk_tagdef
                   && declspecs->typespec_kind != ctsk_tagfirstref
		   && declspecs->typespec_kind != ctsk_tagfirstref_attrs
		   && declspecs->storage_class != csc_none)
	    {
	      எனில் (warned != 1)
		pedwarn (உள்ளீடு_location, 0,
			 "empty declaration with storage class specifier "
			 "does not redeclare tag");
	      warned = 1;
	      pending_xref_error ();
	    }
	  இல்லையெனில் எனில் (declspecs->typespec_kind != ctsk_tagdef
                   && declspecs->typespec_kind != ctsk_tagfirstref
                   && declspecs->typespec_kind != ctsk_tagfirstref_attrs
		   && (declspecs->const_p
		       || declspecs->volatile_p
		       || declspecs->atomic_p
		       || declspecs->restrict_p
		       || declspecs->address_space))
	    {
	      எனில் (warned != 1)
		pedwarn (உள்ளீடு_location, 0,
			 "empty declaration with type qualifier "
			  "does not redeclare tag");
	      warned = 1;
	      pending_xref_error ();
	    }
	  இல்லையெனில் எனில் (declspecs->typespec_kind != ctsk_tagdef
                   && declspecs->typespec_kind != ctsk_tagfirstref
                   && declspecs->typespec_kind != ctsk_tagfirstref_attrs
		   && declspecs->alignas_p)
	    {
	      எனில் (warned != 1)
		pedwarn (உள்ளீடு_location, 0,
			 "empty declaration with %<_Alignas%> "
			  "does not redeclare tag");
	      warned = 1;
	      pending_xref_error ();
	    }
	  இல்லையெனில் எனில் (declspecs->typespec_kind != ctsk_tagdef
		   && declspecs->typespec_kind != ctsk_tagfirstref
		   && declspecs->typespec_kind != ctsk_tagfirstref_attrs
		   && code == ENUMERAL_TYPE
		   && !declspecs->enum_type_specifier_ref_p)
	    {
	      தருக்க warned_enum = பொய்;
	      எனில் (warned != 1)
		warned_enum = pedwarn (உள்ளீடு_location, OPT_Wpedantic,
				       "empty declaration of %<enum%> type "
				       "does not redeclare tag");
	      எனில் (warned_enum)
		warned = 1;
	      pending_xref_error ();
	    }
	  இல்லையெனில்
	    {
	      pending_invalid_xref = NULL_மரம்;
	      t = lookup_tag (code, name, உண்மை, வெற்று);

	      எனில் (t == NULL_மரம்)
		{
		  t = make_முனை (code);
		  எனில் (flag_isoc23 || code == ENUMERAL_TYPE)
		    SET_TYPE_STRUCTURAL_EQUALITY (t);
		  pushtag (உள்ளீடு_location, name, t);
		}
	    }
	}
      இல்லையெனில்
	{
	  எனில் (warned != 1 && !in_system_header_at (உள்ளீடு_location))
	    {
	      pedwarn (உள்ளீடு_location, 0,
		       "useless type name in empty declaration");
	      warned = 1;
	    }
	}
    }
  இல்லையெனில் எனில் (warned != 1 && !in_system_header_at (உள்ளீடு_location)
	   && declspecs->typedef_p)
    {
      pedwarn (உள்ளீடு_location, 0, "useless type name in empty declaration");
      warned = 1;
    }

  pending_invalid_xref = NULL_மரம்;

  எனில் (declspecs->inline_p)
    {
      error ("%<inline%> in empty declaration");
      warned = 1;
    }

  எனில் (declspecs->noreturn_p)
    {
      error ("%<_Noreturn%> in empty declaration");
      warned = 1;
    }

  எனில் (declspecs->constexpr_p)
    {
      error ("%<constexpr%> in empty declaration");
      warned = 1;
    }

  எனில் (current_scope == file_scope && declspecs->storage_class == csc_auto)
    {
      error ("%<auto%> in file-scope empty declaration");
      warned = 1;
    }

  எனில் (current_scope == file_scope && declspecs->storage_class == csc_register)
    {
      error ("%<register%> in file-scope empty declaration");
      warned = 1;
    }

  எனில் (declspecs->enum_type_specifier_ref_p && !warned)
    {
      எனில் (declspecs->storage_class != csc_none)
	{
	  error ("storage class specifier in empty declaration with %<enum%> "
		 "underlying type");
	  warned = 1;
	}
      இல்லையெனில் எனில் (declspecs->thread_p)
	{
	  error ("%qs in empty declaration with %<enum%> underlying type",
		 declspecs->thread_gnu_p ? "__thread" : "_Thread_local");
	  warned = 1;
	}
      இல்லையெனில் எனில் (declspecs->const_p
	       || declspecs->volatile_p
	       || declspecs->atomic_p
	       || declspecs->restrict_p
	       || declspecs->address_space)
	{
	  error ("type qualifier in empty declaration with %<enum%> "
		 "underlying type");
	  warned = 1;
	}
      இல்லையெனில் எனில் (declspecs->alignas_p)
	{
	  error ("%<alignas%> in empty declaration with %<enum%> "
		 "underlying type");
	  warned = 1;
	}
    }

  எனில் (!warned && !in_system_header_at (உள்ளீடு_location)
      && declspecs->storage_class != csc_none)
    {
      warning (0, "useless storage class specifier in empty declaration");
      warned = 2;
    }

  எனில் (!warned && !in_system_header_at (உள்ளீடு_location) && declspecs->thread_p)
    {
      warning (0, "useless %qs in empty declaration",
	       declspecs->thread_gnu_p ? "__thread" : "_Thread_local");
      warned = 2;
    }

  எனில் (!warned
      && !in_system_header_at (உள்ளீடு_location)
      && (declspecs->const_p
	  || declspecs->volatile_p
	  || declspecs->atomic_p
	  || declspecs->restrict_p
	  || declspecs->address_space))
    {
      warning (0, "useless type qualifier in empty declaration");
      warned = 2;
    }

  எனில் (!warned && !in_system_header_at (உள்ளீடு_location)
      && declspecs->alignas_p)
    {
      warning (0, "useless %<_Alignas%> in empty declaration");
      warned = 2;
    }

  எனில் (found_tag
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
      pedwarn (உள்ளீடு_location, 0,
	       "invalid use of attributes in empty declaration");
      warned = 1;
    }

  எனில் (warned != 1)
    {
      எனில் (declspecs->declspecs_seen_p
	  && !declspecs->non_std_attrs_seen_p)
	/* An attribute declaration (but not a fallthrough attribute
	   declaration, which was handled separately); warn if there
	   are any attributes being ignored (but not if the attributes
	   were empty).  */
	c_warn_unused_attributes (declspecs->attrs);
      இல்லையெனில் எனில் (!found_tag)
	pedwarn (உள்ளீடு_location, 0, "empty declaration");
    }
}


/* Return the qualifiers from SPECS as a bitwise OR of TYPE_QUAL_*
   bits.  SPECS represents declaration specifiers that the grammar
   only permits to contain type qualifiers and attributes.  */

முழு
quals_from_declspecs (மாறிலி கட்டமைப்பு c_declspecs *specs)
{
  முழு quals = ((specs->const_p ? TYPE_QUAL_CONST : 0)
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
  திரும்பு quals;
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

கட்டமைப்பு c_declarator *
build_array_declarator (location_t loc,
			மரம் கோவை, கட்டமைப்பு c_declspecs *quals, தருக்க static_p,
			தருக்க vla_unspec_p)
{
  கட்டமைப்பு c_declarator *declarator = XOBNEW (&parser_obstack,
					    கட்டமைப்பு c_declarator);
  declarator->id_loc = loc;
  declarator->kind = cdk_array;
  declarator->declarator = 0;
  declarator->u.array.dimen = கோவை;
  எனில் (quals)
    {
      declarator->u.array.attrs = quals->attrs;
      declarator->u.array.quals = quals_from_declspecs (quals);
    }
  இல்லையெனில்
    {
      declarator->u.array.attrs = NULL_மரம்;
      declarator->u.array.quals = 0;
    }
  declarator->u.array.static_p = static_p;
  declarator->u.array.vla_unspec_p = vla_unspec_p;
  எனில் (static_p || quals != வெற்று)
    pedwarn_c90 (loc, OPT_Wpedantic,
		 "ISO C90 does not support %<static%> or type "
		 "qualifiers in parameter array declarators");
  எனில் (vla_unspec_p)
    {
      pedwarn_c90 (loc, OPT_Wpedantic,
		   "ISO C90 does not support %<[*]%> array declarators");
      எனில் (current_scope->parm_flag)
	current_scope->had_vla_unspec = உண்மை;
    }
  திரும்பு declarator;
}

/* Set the contained declarator of an array declarator.  DECL is the
   declarator, as constructed by build_array_declarator; INNER is what
   appears on the left of the [].  */

கட்டமைப்பு c_declarator *
set_array_declarator_inner (கட்டமைப்பு c_declarator *decl,
			    கட்டமைப்பு c_declarator *inner)
{
  decl->declarator = inner;
  திரும்பு decl;
}

/* Determine whether TYPE is a one-element array type "[1]".  */
நிலையான தருக்க
one_element_array_type_p (const_மரம் type)
{
  எனில் (மரம்_CODE (type) != ARRAY_TYPE)
    திரும்பு பொய்;
  திரும்பு integer_zerop (array_type_nelts_minus_one (type));
}

/* Determine whether TYPE is a zero-length array type "[0]".  */
தருக்க
zero_length_array_type_p (const_மரம் type)
{
  எனில் (மரம்_CODE (type) == ARRAY_TYPE
      && COMPLETE_TYPE_P (type)
      && TYPE_DOMAIN (type) != NULL_மரம்
      && (TYPE_MAX_மதிப்பு (TYPE_DOMAIN (type)) == NULL_மரம்
	  || integer_all_onesp (TYPE_MAX_மதிப்பு (TYPE_DOMAIN (type)))))
    திரும்பு உண்மை;
  திரும்பு பொய்;
}

/* INIT is a constructor that forms DECL's initializer.  If the final
   element initializes a flexible array field, adjust the size of the
   DECL with the initializer based on whether the DECL is a union or
   a structure.  */

நிலையான வெறுமை
add_flexible_array_elts_to_size (மரம் decl, மரம் init)
{
  மரம் elt, type;

  எனில் (vec_safe_is_empty (CONSTRUCTOR_ELTS (init)))
    திரும்பு;

  elt = CONSTRUCTOR_ELTS (init)->last ().மதிப்பு;
  type = மரம்_TYPE (elt);
  எனில் (flexible_array_member_type_p (type))
    {
      complete_array_type (&type, elt, பொய்);
      /* For a structure, add the size of the initializer to the DECL's
	 size.  */
      எனில் (மரம்_CODE (மரம்_TYPE (decl)) == RECORD_TYPE)
	{
	  DECL_SIZE (decl)
	    = size_binop (PLUS_கோவை, DECL_SIZE (decl), TYPE_SIZE (type));
	  DECL_SIZE_UNIT (decl)
	    = size_binop (PLUS_கோவை, DECL_SIZE_UNIT (decl),
			  TYPE_SIZE_UNIT (type));
	}
      /* For a union, the DECL's size is the maximum of the current size
	 and the size of the initializer.  */
      இல்லையெனில்
	{
	  DECL_SIZE (decl)
	    = size_binop (MAX_கோவை, DECL_SIZE (decl), TYPE_SIZE (type));
	  DECL_SIZE_UNIT (decl)
	    = size_binop (MAX_கோவை, DECL_SIZE_UNIT (decl),
			  TYPE_SIZE_UNIT (type));
	}
    }
}

/* Decode a "typename", such as "int **", returning a ..._TYPE node.
   Set *EXPR, if EXPR not NULL, to any expression to be evaluated
   before the type name, and set *EXPR_CONST_OPERANDS, if
   EXPR_CONST_OPERANDS not NULL, to indicate whether the type name may
   appear in a constant expression.  */

மரம்
groktypename (கட்டமைப்பு c_type_name *type_name, மரம் *கோவை,
	      தருக்க *கோவை_const_operands)
{
  மரம் type;
  மரம் attrs = type_name->specs->attrs;

  type_name->specs->attrs = NULL_மரம்;

  type = grokdeclarator (type_name->declarator, type_name->specs, TYPENAME,
			 பொய், வெற்று, &attrs, கோவை, கோவை_const_operands,
			 DEPRECATED_NORMAL);

  /* Apply attributes.  */
  attrs = c_warn_type_attributes (type, attrs);
  decl_attributes (&type, attrs, 0);

  திரும்பு type;
}


/* Decode a "typename", such as "int **", returning a ..._TYPE node,
   as for groktypename but setting the context to GENERIC_ASSOC.  */

மரம்
grokgenassoc (கட்டமைப்பு c_type_name *type_name)
{
  மரம் type;
  மரம் attrs = type_name->specs->attrs;

  type_name->specs->attrs = NULL_மரம்;

  type = grokdeclarator (type_name->declarator, type_name->specs, GENERIC_ASSOC,
			 பொய், வெற்று, &attrs, வெற்று, வெற்று, DEPRECATED_NORMAL);

  /* Apply attributes.  */
  attrs = c_warn_type_attributes (type, attrs);
  decl_attributes (&type, attrs, 0);

  திரும்பு type;
}


/* Looks up the most recent pushed declaration corresponding to DECL.  */

நிலையான மரம்
lookup_last_decl (மரம் decl)
{
  மரம் last_decl = lookup_name (DECL_NAME (decl));
  எனில் (!last_decl)
    last_decl = lookup_name_in_scope (DECL_NAME (decl), external_scope);
  திரும்பு last_decl;
}

/* Wrapper for decl_attributes that adds some implicit attributes
   to VAR_DECLs or FUNCTION_DECLs.  */

நிலையான மரம்
c_decl_attributes (மரம் *முனை, மரம் attributes, முழு flags)
{
  /* Add implicit "omp declare target" attribute if requested.  */
  எனில் (vec_safe_length (current_omp_declare_target_attribute)
      && ((VAR_P (*முனை) && is_global_var (*முனை))
	  || மரம்_CODE (*முனை) == FUNCTION_DECL))
    {
      எனில் (VAR_P (*முனை) && !omp_mappable_type (மரம்_TYPE (*முனை)))
	attributes = மரம்_cons (get_identifier ("omp declare target implicit"),
				NULL_மரம், attributes);
      இல்லையெனில்
	attributes = மரம்_cons (get_identifier ("omp declare target"),
				NULL_மரம், attributes);
      எனில் (மரம்_CODE (*முனை) == FUNCTION_DECL)
	{
	  முழு device_type
	    = current_omp_declare_target_attribute->last ().device_type;
	  device_type = MAX (device_type, 0);
	  எனில் ((device_type & OMP_CLAUSE_DEVICE_TYPE_HOST) != 0
	      && !lookup_attribute ("omp declare target host", attributes))
	    attributes
	      = மரம்_cons (get_identifier ("omp declare target host"),
			   NULL_மரம், attributes);
	  எனில் ((device_type & OMP_CLAUSE_DEVICE_TYPE_NOHOST) != 0
	      && !lookup_attribute ("omp declare target nohost", attributes))
	    attributes
	      = மரம்_cons (get_identifier ("omp declare target nohost"),
			   NULL_மரம், attributes);

	  முழு indirect
	    = current_omp_declare_target_attribute->last ().indirect;
	  எனில் (indirect && !lookup_attribute ("omp declare target indirect",
					     attributes))
	    attributes
	      = மரம்_cons (get_identifier ("omp declare target indirect"),
			   NULL_மரம், attributes);
	}
    }

  எனில் (flag_openmp || flag_openmp_simd)
    {
      தருக்க diagnosed = பொய்;
      க்கு (மரம் *pa = &attributes; *pa; )
	{
	  எனில் (is_attribute_namespace_p ("omp", *pa))
	    {
	      மரம் name = get_attribute_name (*pa);
	      எனில் (is_attribute_p ("directive", name)
		  || is_attribute_p ("sequence", name)
		  || is_attribute_p ("decl", name))
		{
		  மாறிலி எழுத்து *p = வெற்று;
		  எனில் (மரம்_மதிப்பு (*pa) == NULL_மரம்)
		    p = IDENTIFIER_POINTER (name);
		  க்கு (மரம் a = மரம்_மதிப்பு (*pa); a; a = மரம்_CHAIN (a))
		    {
		      மரம் d = மரம்_மதிப்பு (a);
		      gcc_assert (மரம்_CODE (d) == C_TOKEN_VEC);
		      எனில் (மரம்_PUBLIC (d)
			  && (VAR_P (*முனை)
			      || மரம்_CODE (*முனை) == FUNCTION_DECL)
			  && c_maybe_parse_omp_decl (*முனை, d))
			தொடர்;
		      p = மரம்_PUBLIC (d) ? "decl" : "directive";
		    }
		  எனில் (p && !diagnosed)
		    {
		      error ("%<omp::%s%> not allowed to be specified in "
			     "this context", p);
		      diagnosed = உண்மை;
		    }
		  எனில் (p)
		    {
		      *pa = மரம்_CHAIN (*pa);
		      தொடர்;
		    }
		}
	    }
	  pa = &மரம்_CHAIN (*pa);
	}
    }

  /* Look up the current declaration with all the attributes merged
     so far so that attributes on the current declaration that's
     about to be pushed that conflict with the former can be detected,
     diagnosed, and rejected as appropriate.  To match the C++ FE, do
     not pass an error_mark_node when we found an undeclared variable.  */
  மரம் last_decl = lookup_last_decl (*முனை);
  எனில் (last_decl == error_mark_முனை)
    last_decl = NULL_மரம்;
  மரம் attr = decl_attributes (முனை, attributes, flags, last_decl);
  எனில் (VAR_P (*முனை) && DECL_THREAD_LOCAL_P (*முனை))
    {
      // tls_model attribute can set a stronger TLS access model.
      tls_model model = DECL_TLS_MODEL (*முனை);
      tls_model default_model = decl_default_tls_model (*முனை);
      எனில் (default_model > model)
	set_decl_tls_model (*முனை, default_model);
    }
  திரும்பு attr;
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

மரம்
start_decl (கட்டமைப்பு c_declarator *declarator, கட்டமைப்பு c_declspecs *declspecs,
	    தருக்க initialized, மரம் attributes, தருக்க do_தள்ளு /* = true */,
	    location_t *lastloc /* = NULL */)
{
  மரம் decl;
  மரம் old_decl;
  மரம் tem;
  மரம் கோவை = NULL_மரம்;
  எண்ணிக்கை deprecated_states deprecated_state = DEPRECATED_NORMAL;

  /* An object declared as __attribute__((unavailable)) suppresses
     warnings and errors from __attribute__((deprecated/unavailable))
     components.
     An object declared as __attribute__((deprecated)) suppresses
     warnings of uses of other deprecated items.  */
  எனில் (lookup_attribute ("unavailable", attributes))
    deprecated_state = UNAVAILABLE_DEPRECATED_SUPPRESS;
  இல்லையெனில் எனில் (lookup_attribute ("deprecated", attributes))
    deprecated_state = DEPRECATED_SUPPRESS;

  decl = grokdeclarator (declarator, declspecs,
			 NORMAL, initialized, வெற்று, &attributes, &கோவை, வெற்று,
			 deprecated_state);
  எனில் (!decl || decl == error_mark_முனை)
    திரும்பு NULL_மரம்;

  old_decl = lookup_last_decl (decl);

  எனில் (மரம் lastdecl = lastloc ? old_decl : NULL_மரம்)
    எனில் (lastdecl != error_mark_முனை)
      *lastloc = DECL_SOURCE_LOCATION (lastdecl);

  /* Make sure the size expression is evaluated at this point.  */
  எனில் (கோவை && !current_scope->parm_flag)
    add_stmt (fold_convert (void_type_முனை, கோவை));

  எனில் (மரம்_CODE (decl) != FUNCTION_DECL && MAIN_NAME_P (DECL_NAME (decl))
      && மரம்_PUBLIC (decl))
    warning (OPT_Wmain, "%q+D is usually a function", decl);

  எனில் (warn_missing_variable_declarations && VAR_P (decl)
      && !DECL_EXTERNAL (decl) && மரம்_PUBLIC (decl) && old_decl == NULL_மரம்)
    warning_at (DECL_SOURCE_LOCATION (decl), OPT_Wmissing_variable_declarations,
		"no previous declaration for %qD", decl);

  எனில் (initialized)
    /* Is it valid for this decl to have an initializer at all?
       If not, set INITIALIZED to zero, which will indirectly
       tell 'finish_decl' to ignore the initializer once it is parsed.  */
    தேர்வு (மரம்_CODE (decl))
      {
      நிலை TYPE_DECL:
	error ("typedef %qD is initialized (use %<__typeof__%> instead)", decl);
	initialized = பொய்;
	நிறுத்து;

      நிலை FUNCTION_DECL:
	error ("function %qD is initialized like a variable", decl);
	initialized = பொய்;
	நிறுத்து;

      நிலை PARM_DECL:
	/* DECL_INITIAL in a PARM_DECL is really DECL_ARG_TYPE.  */
	error ("parameter %qD is initialized", decl);
	initialized = பொய்;
	நிறுத்து;

      இயல்பு:
	/* Don't allow initializations for incomplete types except for
	   arrays which might be completed by the initialization.  */

	/* This can happen if the array size is an undefined macro.
	   We already gave a warning, so we don't need another one.  */
	எனில் (மரம்_TYPE (decl) == error_mark_முனை)
	  initialized = பொய்;
	இல்லையெனில் எனில் (COMPLETE_TYPE_P (மரம்_TYPE (decl)))
	  {
	    /* A complete type is ok if size is fixed.  If the size is
	       variable, an empty initializer is OK and nonempty
	       initializers will be diagnosed in the parser.  */
	  }
	இல்லையெனில் எனில் (மரம்_CODE (மரம்_TYPE (decl)) != ARRAY_TYPE)
	  {
	    error ("variable %qD has initializer but incomplete type", decl);
	    initialized = பொய்;
	  }
      }

  எனில் (initialized)
    {
      எனில் (current_scope == file_scope)
	மரம்_STATIC (decl) = 1;

      /* Tell 'pushdecl' this is an initialized decl
	 even though we don't yet have the initializer expression.
	 Also tell 'finish_decl' it may store the real initializer.  */
      DECL_INITIAL (decl) = error_mark_முனை;
    }

  /* If this is a function declaration, write a record describing it to the
     prototypes file (if requested).  */

  எனில் (மரம்_CODE (decl) == FUNCTION_DECL)
    gen_aux_info_record (decl, 0, 0, prototype_p (மரம்_TYPE (decl)));

  /* ANSI specifies that a tentative definition which is not merged with
     a non-tentative definition behaves exactly like a definition with an
     initializer equal to zero.  (Section 3.7.2)

     -fno-common gives strict ANSI behavior, though this tends to break
     a large body of code that grew up without this rule.

     Thread-local variables are never common, since there's no entrenched
     body of code to break, and it allows more efficient variable references
     in the presence of dynamic linking.  */

  எனில் (VAR_P (decl)
      && !initialized
      && மரம்_PUBLIC (decl)
      && !DECL_THREAD_LOCAL_P (decl)
      && !flag_no_common)
    DECL_COMMON (decl) = 1;

  /* Set attributes here so if duplicate decl, will have proper attributes.  */
  c_decl_attributes (&decl, attributes, 0);

  /* Handle gnu_inline attribute.  */
  எனில் (declspecs->inline_p
      && !flag_gnu89_inline
      && மரம்_CODE (decl) == FUNCTION_DECL
      && (lookup_attribute ("gnu_inline", DECL_ATTRIBUTES (decl))
	  || current_function_decl))
    {
      எனில் (declspecs->storage_class == csc_auto && current_scope != file_scope)
	;
      இல்லையெனில் எனில் (declspecs->storage_class != csc_static)
	DECL_EXTERNAL (decl) = !DECL_EXTERNAL (decl);
    }

  எனில் (மரம்_CODE (decl) == FUNCTION_DECL
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
  எனில் (VAR_P (decl)
      && current_scope != file_scope
      && மரம்_STATIC (decl)
      && !மரம்_READONLY (decl)
      && DECL_DECLARED_INLINE_P (current_function_decl)
      && DECL_EXTERNAL (current_function_decl))
    record_inline_static (உள்ளீடு_location, current_function_decl,
			  decl, csi_modifiable);

  எனில் (c_dialect_objc ()
      && VAR_OR_FUNCTION_DECL_P (decl))
      objc_check_global_decl (decl);

  /* To enable versions to be created across TU's we mark and mangle all
     non-default versioned functions.  */
  எனில் (மரம்_CODE (decl) == FUNCTION_DECL
      && !TARGET_HAS_FMV_TARGET_ATTRIBUTE
      && get_target_version (decl).is_valid ())
    {
      maybe_mark_function_versioned (decl);
      எனில் (current_scope != file_scope)
	error ("versioned declarations are only allowed at file scope");
    }

  /* Add this decl to the current scope.
     TEM may equal DECL or it may be a previous decl of the same name.  */
  எனில் (do_தள்ளு)
    {
      tem = pushdecl (decl);

      எனில் (initialized && DECL_EXTERNAL (tem))
	{
	  DECL_EXTERNAL (tem) = 0;
	  மரம்_STATIC (tem) = 1;
	}

      திரும்பு tem;
    }
  இல்லையெனில்
    திரும்பு decl;
}

/* Subroutine of finish_decl. TYPE is the type of an uninitialized object
   DECL or the non-array element type if DECL is an uninitialized array.
   If that type has a const member, diagnose this. */

நிலையான வெறுமை
diagnose_uninitialized_cst_member (மரம் decl, மரம் type)
{
  மரம் field;
  க்கு (field = TYPE_FIELDS (type); field; field = மரம்_CHAIN (field))
    {
      மரம் field_type;
      எனில் (மரம்_CODE (field) != FIELD_DECL)
	தொடர்;
      field_type = strip_array_types (மரம்_TYPE (field));

      எனில் (TYPE_QUALS (field_type) & TYPE_QUAL_CONST)
      	{
	  auto_diagnostic_group d;
	  எனில் (warning_at (DECL_SOURCE_LOCATION (decl), OPT_Wc___compat,
			  "uninitialized const member in %qT is invalid in C++",
			  strip_array_types (மரம்_TYPE (decl))))
	    inform (DECL_SOURCE_LOCATION (field), "%qD should be initialized", field);
	}

      எனில் (RECORD_OR_UNION_TYPE_P (field_type))
	diagnose_uninitialized_cst_member (decl, field_type);
    }
}

/* Finish processing of a declaration;
   install its initial value.
   If ORIGTYPE is not NULL_TREE, it is the original type of INIT.
   If the length of an array type is not known before,
   it must be determined now, from the initial value, or it is an error.

   INIT_LOC is the location of the initial value.  */

வெறுமை
finish_decl (மரம் decl, location_t init_loc, மரம் init,
	     மரம் origtype, மரம் asmspec_மரம்)
{
  மரம் type;
  தருக்க was_incomplete = (DECL_SIZE (decl) == NULL_மரம்);
  மாறிலி எழுத்து *asmspec = 0;

  /* If a name was specified, get the string.  */
  எனில் (VAR_OR_FUNCTION_DECL_P (decl)
      && DECL_FILE_SCOPE_P (decl))
    asmspec_மரம் = maybe_apply_renaming_pragma (decl, asmspec_மரம்);
  எனில் (asmspec_மரம்)
    asmspec = மரம்_STRING_POINTER (asmspec_மரம்);

  எனில் (VAR_P (decl)
      && மரம்_STATIC (decl)
      && global_bindings_p ())
    /* So decl is a global variable. Record the types it uses
       so that we can decide later to emit debug info for them.  */
    record_types_used_by_current_var_decl (decl);

  /* If `start_decl' didn't like having an initialization, ignore it now.  */
  எனில் (init != NULL_மரம் && DECL_INITIAL (decl) == NULL_மரம்)
    init = NULL_மரம்;

  /* Don't crash if parm is initialized.  */
  எனில் (மரம்_CODE (decl) == PARM_DECL)
    init = NULL_மரம்;

  எனில் (init)
    store_init_மதிப்பு (init_loc, decl, init, origtype);

  எனில் (c_dialect_objc () && (VAR_OR_FUNCTION_DECL_P (decl)
			    || மரம்_CODE (decl) == FIELD_DECL))
    objc_check_decl (decl);

  type = மரம்_TYPE (decl);

  /* Deduce size of array from initialization, if not already known.
     This is only needed for an initialization in the current scope;
     it must not be done for a file-scope initialization of a
     declaration with external linkage, redeclared in an inner scope
     with the outer declaration shadowed in an intermediate scope.  */
  எனில் (மரம்_CODE (type) == ARRAY_TYPE
      && TYPE_DOMAIN (type) == NULL_மரம்
      && மரம்_CODE (decl) != TYPE_DECL
      && !(மரம்_PUBLIC (decl) && current_scope != file_scope))
    {
      தருக்க do_default
	= !மரம்_STATIC (decl) && !DECL_EXTERNAL (decl);
      முழு failure
	= complete_array_type (&மரம்_TYPE (decl), DECL_INITIAL (decl),
			       do_default);

      /* Get the completed type made by complete_array_type.  */
      type = மரம்_TYPE (decl);

      தேர்வு (failure)
	{
	நிலை 1:
	  error ("initializer fails to determine size of %q+D", decl);
	  நிறுத்து;

	நிலை 2:
	  எனில் (do_default)
	    error ("array size missing in %q+D", decl);
	  இல்லையெனில் எனில் (!மரம்_PUBLIC (decl))
	    pedwarn_c23 (DECL_SOURCE_LOCATION (decl), OPT_Wpedantic,
			 "array size missing in %q+D", decl);
	  நிறுத்து;

	நிலை 3:
	  error ("zero or negative size array %q+D", decl);
	  நிறுத்து;

	நிலை 0:
	  /* For global variables, update the copy of the type that
	     exists in the binding.  */
	  எனில் (மரம்_PUBLIC (decl))
	    {
	      கட்டமைப்பு c_binding *b_ext = I_குறியீடு_BINDING (DECL_NAME (decl));
	      போது (b_ext && !B_IN_EXTERNAL_SCOPE (b_ext))
		b_ext = b_ext->shadowed;
	      எனில் (b_ext && மரம்_CODE (decl) == மரம்_CODE (b_ext->decl))
		{
		  எனில் (b_ext->u.type && comptypes (b_ext->u.type, type))
		    b_ext->u.type = composite_type (b_ext->u.type, type);
		  இல்லையெனில்
		    b_ext->u.type = type;
		}
	    }
	  நிறுத்து;

	இயல்பு:
	  gcc_unreachable ();
	}

      எனில் (DECL_INITIAL (decl) && DECL_INITIAL (decl) != error_mark_முனை)
	மரம்_TYPE (DECL_INITIAL (decl)) = type;

      relayout_decl (decl);
    }

  /* Look for braced array initializers for character arrays and
     recursively convert them into STRING_CSTs.  */
  எனில் (மரம் init = DECL_INITIAL (decl))
    DECL_INITIAL (decl) = braced_lists_to_strings (type, init);

  எனில் (VAR_P (decl))
    {
      எனில் (init && மரம்_CODE (init) == CONSTRUCTOR)
	add_flexible_array_elts_to_size (decl, init);

      complete_flexible_array_elts (DECL_INITIAL (decl));

      எனில் (is_global_var (decl))
	{
	  type_context_kind context = (DECL_THREAD_LOCAL_P (decl)
				       ? TCTX_THREAD_STORAGE
				       : TCTX_STATIC_STORAGE);
	  எனில் (!verify_type_context (உள்ளீடு_location, context, மரம்_TYPE (decl)))
	    மரம்_TYPE (decl) = error_mark_முனை;
	}

      எனில் (DECL_SIZE (decl) == NULL_மரம் && மரம்_TYPE (decl) != error_mark_முனை
	  && COMPLETE_TYPE_P (மரம்_TYPE (decl)))
	layout_decl (decl, 0);

      எனில் (DECL_SIZE (decl) == NULL_மரம்
	  /* Don't give an error if we already gave one earlier.  */
	  && மரம்_TYPE (decl) != error_mark_முனை
	  && (மரம்_STATIC (decl)
	      /* A static variable with an incomplete type
		 is an error if it is initialized.
		 Also if it is not file scope.
		 Also if it is thread-local (in C23).
		 Otherwise, let it through, but if it is not `extern'
		 then it may cause an error message later.  */
	      ? (DECL_INITIAL (decl) != NULL_மரம்
		 || !DECL_FILE_SCOPE_P (decl)
		 || (flag_isoc23 && DECL_THREAD_LOCAL_P (decl)))
	      /* An automatic variable with an incomplete type
		 is an error.  */
	      : !DECL_EXTERNAL (decl)))
	 {
	   error ("storage size of %q+D isn%'t known", decl);
	   மரம்_TYPE (decl) = error_mark_முனை;
	 }

      எனில் ((RECORD_OR_UNION_TYPE_P (மரம்_TYPE (decl))
	  || மரம்_CODE (மரம்_TYPE (decl)) == ENUMERAL_TYPE)
	  && DECL_SIZE (decl) == NULL_மரம்
	  && மரம்_STATIC (decl))
	incomplete_record_decls.safe_தள்ளு (decl);

      எனில் (is_global_var (decl)
	  && DECL_SIZE (decl) != NULL_மரம்
	  && மரம்_TYPE (decl) != error_mark_முனை)
	{
	  எனில் (மரம்_CODE (DECL_SIZE (decl)) == INTEGER_CST)
	    constant_expression_warning (DECL_SIZE (decl));
	  இல்லையெனில்
	    {
	      error ("storage size of %q+D isn%'t constant", decl);
	      மரம்_TYPE (decl) = error_mark_முனை;
	    }
	}

      எனில் (மரம்_USED (type))
	{
	  மரம்_USED (decl) = 1;
	  DECL_READ_P (decl) = 1;
	}
    }

  /* If this is a function and an assembler name is specified, reset DECL_RTL
     so we can give it its new name.  Also, update builtin_decl if it
     was a normal built-in.  */
  எனில் (மரம்_CODE (decl) == FUNCTION_DECL && asmspec)
    {
      எனில் (DECL_BUILT_IN_CLASS (decl) == BUILT_IN_NORMAL)
	set_builtin_user_assembler_name (decl, asmspec);
      set_user_assembler_name (decl, asmspec);
    }

  /* If #pragma weak was used, mark the decl weak now.  */
  maybe_apply_pragma_weak (decl);

  /* Output the assembler code and/or RTL code for variables and functions,
     unless the type is an undefined structure or union.
     If not, it will get done when the type is completed.  */

  எனில் (VAR_OR_FUNCTION_DECL_P (decl))
    {
      /* Determine the ELF visibility.  */
      எனில் (மரம்_PUBLIC (decl))
	c_determine_visibility (decl);

      /* This is a no-op in c-lang.cc or something real in objc-act.cc.  */
      எனில் (c_dialect_objc ())
	objc_check_decl (decl);

      எனில் (asmspec)
	{
	  /* If this is not a static variable, issue a warning.
	     It doesn't make any sense to give an ASMSPEC for an
	     ordinary, non-register local variable.  Historically,
	     GCC has accepted -- but ignored -- the ASMSPEC in
	     this case.  */
	  எனில் (!DECL_FILE_SCOPE_P (decl)
	      && VAR_P (decl)
	      && !C_DECL_REGISTER (decl)
	      && !மரம்_STATIC (decl))
	    warning (0, "ignoring %<asm%> specifier for non-static local "
		     "variable %q+D", decl);
	  இல்லையெனில்
	    set_user_assembler_name (decl, asmspec);
	}

      எனில் (DECL_FILE_SCOPE_P (decl))
	{
	  எனில் (DECL_INITIAL (decl) == NULL_மரம்
	      || DECL_INITIAL (decl) == error_mark_முனை)
	    /* Don't output anything
	       when a tentative file-scope definition is seen.
	       But at end of compilation, do output code for them.  */
	    DECL_DEFER_OUTPUT (decl) = 1;
	  எனில் (asmspec && VAR_P (decl) && C_DECL_REGISTER (decl))
	    DECL_HARD_REGISTER (decl) = 1;
	  rest_of_decl_compilation (decl, உண்மை, 0);

	  எனில் (மரம்_CODE (decl) == FUNCTION_DECL)
	    {
	      மரம் parms = DECL_ARGUMENTS (decl);
	      மாறிலி தருக்க builtin = fndecl_built_in_p (decl);
	      எனில் (மரம் access = build_attr_access_from_parms (parms, !builtin))
		decl_attributes (&decl, access, 0);
	    }
	}
      இல்லையெனில்
	{
	  /* In conjunction with an ASMSPEC, the `register'
	     keyword indicates that we should place the variable
	     in a particular register.  */
	  எனில் (asmspec && C_DECL_REGISTER (decl))
	    {
	      DECL_HARD_REGISTER (decl) = 1;
	      /* This cannot be done for a structure with volatile
		 fields, on which DECL_REGISTER will have been
		 reset.  */
	      எனில் (!DECL_REGISTER (decl))
		error ("cannot put object with volatile field into register");
	    }

	  எனில் (மரம்_CODE (decl) != FUNCTION_DECL)
	    {
	      /* If we're building a variable sized type, and we might be
		 reachable other than via the top of the current binding
		 level, then create a new BIND_EXPR so that we deallocate
		 the object at the right time.  */
	      /* Note that DECL_SIZE can be null due to errors.  */
	      எனில் (DECL_SIZE (decl)
		  && !மரம்_CONSTANT (DECL_SIZE (decl))
		  && STATEMENT_LIST_HAS_LABEL (cur_stmt_list))
		{
		  மரம் bind;
		  bind = build3 (BIND_கோவை, void_type_முனை, வெற்று, வெற்று, வெற்று);
		  மரம்_SIDE_EFFECTS (bind) = 1;
		  add_stmt (bind);
		  BIND_கோவை_BODY (bind) = தள்ளு_stmt_list ();
		}
	      add_stmt (build_stmt (DECL_SOURCE_LOCATION (decl),
				    DECL_கோவை, decl));
	    }
	}


      எனில் (!DECL_FILE_SCOPE_P (decl))
	{
	  /* Recompute the RTL of a local array now
	     if it used to be an incomplete type.  */
	  எனில் (was_incomplete && !is_global_var (decl))
	    {
	      /* If we used it already as memory, it must stay in memory.  */
	      மரம்_ADDRESSABLE (decl) = மரம்_USED (decl);
	      /* If it's still incomplete now, no init will save it.  */
	      எனில் (DECL_SIZE (decl) == NULL_மரம்)
		DECL_INITIAL (decl) = NULL_மரம்;
	    }
	}
    }

  எனில் (மரம்_CODE (decl) == TYPE_DECL)
    {
      எனில் (!DECL_FILE_SCOPE_P (decl)
	  && c_type_variably_modified_p (மரம்_TYPE (decl)))
	add_stmt (build_stmt (DECL_SOURCE_LOCATION (decl), DECL_கோவை, decl));

      rest_of_decl_compilation (decl, DECL_FILE_SCOPE_P (decl), 0);
    }

  /* Install a cleanup (aka destructor) if one was given.  */
  எனில் (VAR_P (decl) && !மரம்_STATIC (decl))
    {
      மரம் attr = lookup_attribute ("cleanup", DECL_ATTRIBUTES (decl));
      எனில் (attr)
	{
	  மரம் cleanup_id = மரம்_மதிப்பு (மரம்_மதிப்பு (attr));
	  மரம் cleanup_decl = lookup_name (cleanup_id);
	  மரம் cleanup;
	  vec<மரம், va_gc> *v;

	  /* Build "cleanup(&decl)" for the destructor.  */
	  cleanup = build_unary_op (உள்ளீடு_location, ADDR_கோவை, decl, பொய்);
	  vec_alloc (v, 1);
	  v->quick_தள்ளு (cleanup);
	  cleanup = c_build_function_call_vec (DECL_SOURCE_LOCATION (decl),
					       vNULL, cleanup_decl, v, வெற்று);
	  vec_free (v);

	  /* Don't warn about decl unused; the cleanup uses it.  */
	  மரம்_USED (decl) = 1;
	  மரம்_USED (cleanup_decl) = 1;
	  DECL_READ_P (decl) = 1;

	  தள்ளு_cleanup (decl, cleanup, பொய்);
	}
    }

  எனில் (warn_cxx_compat
      && VAR_P (decl)
      && !DECL_EXTERNAL (decl)
      && DECL_INITIAL (decl) == NULL_மரம்)
    {
      type = strip_array_types (type);
      எனில் (மரம்_READONLY (decl))
	warning_at (DECL_SOURCE_LOCATION (decl), OPT_Wc___compat,
		    "uninitialized %<const %D%> is invalid in C++", decl);
      இல்லையெனில் எனில் (RECORD_OR_UNION_TYPE_P (type)
	       && C_TYPE_FIELDS_READONLY (type))
	diagnose_uninitialized_cst_member (decl, type);
    }

  எனில் (flag_openmp
      && VAR_P (decl)
      && lookup_attribute ("omp declare target implicit",
			   DECL_ATTRIBUTES (decl)))
    {
      DECL_ATTRIBUTES (decl)
	= remove_attribute ("omp declare target implicit",
			    DECL_ATTRIBUTES (decl));
      எனில் (!omp_mappable_type (மரம்_TYPE (decl)))
	error ("%q+D in declare target directive does not have mappable type",
	       decl);
      இல்லையெனில் எனில் (!lookup_attribute ("omp declare target",
				  DECL_ATTRIBUTES (decl))
	       && !lookup_attribute ("omp declare target link",
				     DECL_ATTRIBUTES (decl)))
	{
	  DECL_ATTRIBUTES (decl)
	    = மரம்_cons (get_identifier ("omp declare target"),
			 NULL_மரம், DECL_ATTRIBUTES (decl));
	    symtab_முனை *முனை = symtab_முனை::get (decl);
	    எனில் (முனை != வெற்று)
	      {
		முனை->offloadable = 1;
		எனில் (ENABLE_OFFLOADING)
		  {
		    g->have_offload = உண்மை;
		    எனில் (is_a <varpool_முனை *> (முனை))
		      vec_safe_தள்ளு (offload_vars, decl);
		  }
	      }
	}
    }

  /* This is the last point we can lower alignment so give the target the
     chance to do so.  */
  எனில் (VAR_P (decl)
      && !is_global_var (decl)
      && !DECL_HARD_REGISTER (decl))
    targetm.lower_local_decl_alignment (decl);

  invoke_plugin_callbacks (PLUGIN_FINISH_DECL, decl);
}

/* Given a parsed parameter declaration, decode it into a PARM_DECL.
   EXPR is NULL or a pointer to an expression that needs to be
   evaluated for the side effects of array size expressions in the
   parameters.  */

மரம்
grokparm (மாறிலி கட்டமைப்பு c_parm *parm, மரம் *கோவை)
{
  மரம் attrs = parm->attrs;
  மரம் decl = grokdeclarator (parm->declarator, parm->specs, PARM, பொய்,
			      வெற்று, &attrs, கோவை, வெற்று, DEPRECATED_NORMAL);

  decl_attributes (&decl, attrs, 0);

  திரும்பு decl;
}



/* Given a parsed parameter declaration, decode it into a PARM_DECL
   and push that on the current scope.  EXPR is a pointer to an
   expression that needs to be evaluated for the side effects of array
   size expressions in the parameters.  */

வெறுமை
தள்ளு_parm_decl (மாறிலி கட்டமைப்பு c_parm *parm, மரம் *கோவை)
{
  மரம் attrs = parm->attrs;
  மரம் decl = grokdeclarator (parm->declarator, parm->specs, PARM, பொய், வெற்று,
			      &attrs, கோவை, வெற்று, DEPRECATED_NORMAL);
  எனில் (decl && DECL_P (decl))
    DECL_SOURCE_LOCATION (decl) = parm->loc;

  decl_attributes (&decl, attrs, 0);

  decl = pushdecl (decl);

  finish_decl (decl, உள்ளீடு_location, NULL_மரம், NULL_மரம், NULL_மரம்);
}

/* Mark all the parameter declarations to date as forward decls.
   Also diagnose use of this extension.  */

வெறுமை
mark_forward_parm_decls (வெறுமை)
{
  கட்டமைப்பு c_binding *b;

  எனில் (current_scope->had_forward_parm_decls)
    warning_at (உள்ளீடு_location, OPT_Wmultiple_parameter_fwd_decl_lists,
		"more than one list of forward declarations of parameters");
  எனில் (pedantic && !current_scope->had_forward_parm_decls)
    pedwarn (உள்ளீடு_location, OPT_Wpedantic,
	     "ISO C forbids forward parameter declarations");

  current_scope->had_forward_parm_decls = உண்மை;

  க்கு (b = current_scope->bindings; b; b = b->prev)
    எனில் (மரம்_CODE (b->decl) == PARM_DECL)
      மரம்_ASM_WRITTEN (b->decl) = 1;
}

/* Build a COMPOUND_LITERAL_EXPR.  TYPE is the type given in the compound
   literal, which may be an incomplete array type completed by the
   initializer; INIT is a CONSTRUCTOR at LOC that initializes the compound
   literal.  NON_CONST is true if the initializers contain something
   that cannot occur in a constant expression.  If ALIGNAS_ALIGN is nonzero,
   it is the (valid) alignment for this compound literal, as specified
   with _Alignas.  SCSPECS are the storage class specifiers (C23) from the
   compound literal.  */

மரம்
build_compound_literal (location_t loc, மரம் type, மரம் init, தருக்க non_const,
			unsigned முழு alignas_align,
			கட்டமைப்பு c_declspecs *scspecs)
{
  /* We do not use start_decl here because we have a type, not a declarator;
     and do not use finish_decl because the decl should be stored inside
     the COMPOUND_LITERAL_EXPR rather than added elsewhere as a DECL_EXPR.  */
  மரம் decl;
  மரம் complit;
  மரம் stmt;
  தருக்க threadp = scspecs ? scspecs->thread_p : பொய்;
  எண்ணிக்கை c_storage_class storage_class = (scspecs
					? scspecs->storage_class
					: csc_none);

  எனில் (type == error_mark_முனை
      || init == error_mark_முனை)
    திரும்பு error_mark_முனை;

  எனில் (current_scope == file_scope && storage_class == csc_register)
    {
      error_at (loc, "file-scope compound literal specifies %<register%>");
      storage_class = csc_none;
    }

  எனில் (current_scope != file_scope && threadp && storage_class == csc_none)
    {
      error_at (loc, "compound literal implicitly auto and declared %qs",
		scspecs->thread_gnu_p ? "__thread" : "_Thread_local");
      threadp = பொய்;
    }

  decl = build_decl (loc, VAR_DECL, NULL_மரம், type);
  DECL_EXTERNAL (decl) = 0;
  மரம்_PUBLIC (decl) = 0;
  மரம்_STATIC (decl) = (current_scope == file_scope
			|| storage_class == csc_static);
  DECL_CONTEXT (decl) = current_function_decl;
  மரம்_USED (decl) = 1;
  DECL_READ_P (decl) = 1;
  DECL_ARTIFICIAL (decl) = 1;
  DECL_IGNORED_P (decl) = 1;
  C_DECL_COMPOUND_LITERAL_P (decl) = 1;
  C_DECL_DECLARED_CONSTEXPR (decl) = scspecs && scspecs->constexpr_p;
  மரம்_TYPE (decl) = type;
  எனில் (threadp)
    set_decl_tls_model (decl, decl_default_tls_model (decl));
  எனில் (storage_class == csc_register)
    {
      C_DECL_REGISTER (decl) = 1;
      DECL_REGISTER (decl) = 1;
    }
  c_apply_type_quals_to_decl (TYPE_QUALS (strip_array_types (type)), decl);
  எனில் (alignas_align)
    {
      SET_DECL_ALIGN (decl, alignas_align * BITS_PER_UNIT);
      DECL_USER_ALIGN (decl) = 1;
    }
  store_init_மதிப்பு (loc, decl, init, NULL_மரம்);
  எனில் (current_scope != file_scope
      && மரம்_STATIC (decl)
      && !மரம்_READONLY (decl)
      && DECL_DECLARED_INLINE_P (current_function_decl)
      && DECL_EXTERNAL (current_function_decl))
    record_inline_static (உள்ளீடு_location, current_function_decl,
			  decl, csi_modifiable);

  எனில் (மரம்_CODE (type) == ARRAY_TYPE && !COMPLETE_TYPE_P (type))
    {
      முழு failure = complete_array_type (&மரம்_TYPE (decl),
					 DECL_INITIAL (decl), உண்மை);
      /* If complete_array_type returns 3, it means that the initial value of
         the compound literal is empty.  Allow it with a pedwarn; in pre-C23
         modes, the empty initializer itself has been diagnosed if pedantic so
         does not need to be diagnosed again here.  */
      gcc_assert (failure == 0 || failure == 3);
      எனில் (failure == 3 && flag_isoc23)
	pedwarn (loc, OPT_Wpedantic,
		 "array of unknown size with empty initializer");

      type = மரம்_TYPE (decl);
      மரம்_TYPE (DECL_INITIAL (decl)) = type;
      relayout_decl (decl);
    }

  எனில் (type == error_mark_முனை || !COMPLETE_TYPE_P (type))
    {
      c_incomplete_type_error (loc, NULL_மரம், type);
      திரும்பு error_mark_முனை;
    }

  எனில் ((மரம்_STATIC (decl) || C_DECL_DECLARED_CONSTEXPR (decl))
      && C_TYPE_VARIABLE_SIZE (type))
    error_at (loc, "storage size isn%'t constant");

  எனில் (மரம்_STATIC (decl)
      && !verify_type_context (loc, TCTX_STATIC_STORAGE, type))
    திரும்பு error_mark_முனை;

  stmt = build_stmt (DECL_SOURCE_LOCATION (decl), DECL_கோவை, decl);
  complit = build1 (COMPOUND_LITERAL_கோவை, type, stmt);
  மரம்_SIDE_EFFECTS (complit) = 1;

  layout_decl (decl, 0);

  எனில் (மரம்_STATIC (decl))
    {
      /* This decl needs a name for the assembler output.  */
      set_compound_literal_name (decl);
      DECL_DEFER_OUTPUT (decl) = 1;
      DECL_COMDAT (decl) = 1;
      pushdecl (decl);
      rest_of_decl_compilation (decl, 1, 0);
    }
  இல்லையெனில் எனில் (current_function_decl && !current_scope->parm_flag)
    pushdecl (decl);

  எனில் (non_const)
    {
      complit = build2 (C_MAYBE_CONST_கோவை, type, வெற்று, complit);
      C_MAYBE_CONST_கோவை_NON_CONST (complit) = 1;
    }

  திரும்பு complit;
}

/* Check the type of a compound literal.  Here we just check that it
   is valid for C++.  */

வெறுமை
check_compound_literal_type (location_t loc, கட்டமைப்பு c_type_name *type_name)
{
  எனில் (warn_cxx_compat
      && (type_name->specs->typespec_kind == ctsk_tagdef
          || type_name->specs->typespec_kind == ctsk_tagfirstref
	  || type_name->specs->typespec_kind == ctsk_tagfirstref_attrs))
    warning_at (loc, OPT_Wc___compat,
		"defining a type in a compound literal is invalid in C++");
}

/* Performs sanity checks on the TYPE and WIDTH of the bit-field NAME,
   replacing with appropriate values if they are invalid.  */

நிலையான வெறுமை
check_bitfield_type_and_width (location_t loc, மரம் *type, மரம் *width,
			       மரம் orig_name)
{
  மரம் type_mv;
  unsigned முழு max_width;
  unsigned HOST_WIDE_INT w;
  மாறிலி எழுத்து *name = (orig_name
		      ? identifier_to_locale (IDENTIFIER_POINTER (orig_name))
		      : _("<anonymous>"));

  /* Detect and ignore out of range field width and process valid
     field widths.  */
  எனில் (!INTEGRAL_TYPE_P (மரம்_TYPE (*width)))
    {
      error_at (loc, "bit-field %qs width not an integer constant", name);
      *width = integer_one_முனை;
    }
  இல்லையெனில்
    {
      எனில் (மரம்_CODE (*width) != INTEGER_CST)
	{
	  *width = c_fully_fold (*width, பொய், வெற்று);
	  எனில் (மரம்_CODE (*width) == INTEGER_CST)
	    pedwarn (loc, OPT_Wpedantic,
		     "bit-field %qs width not an integer constant expression",
		     name);
	}
      எனில் (மரம்_CODE (*width) != INTEGER_CST)
	{
	  error_at (loc, "bit-field %qs width not an integer constant", name);
	  *width = integer_one_முனை;
	}
      constant_expression_warning (*width);
      எனில் (மரம்_int_cst_sgn (*width) < 0)
	{
	  error_at (loc, "negative width in bit-field %qs", name);
	  *width = integer_one_முனை;
	}
      இல்லையெனில் எனில் (integer_zerop (*width) && orig_name)
	{
	  error_at (loc, "zero width for bit-field %qs", name);
	  *width = integer_one_முனை;
	}
    }

  /* Detect invalid bit-field type.  */
  எனில் (மரம்_CODE (*type) != INTEGER_TYPE
      && மரம்_CODE (*type) != BOOLEAN_TYPE
      && மரம்_CODE (*type) != ENUMERAL_TYPE
      && மரம்_CODE (*type) != BITINT_TYPE)
    {
      error_at (loc, "bit-field %qs has invalid type", name);
      *type = unsigned_type_முனை;
    }

  எனில் (TYPE_WARN_IF_NOT_ALIGN (*type))
    {
      error_at (loc, "cannot declare bit-field %qs with %<warn_if_not_aligned%> type",
		name);
      *type = unsigned_type_முனை;
    }

  type_mv = TYPE_MAIN_VARIANT (*type);
  எனில் (!in_system_header_at (உள்ளீடு_location)
      && type_mv != integer_type_முனை
      && type_mv != unsigned_type_முனை
      && type_mv != boolean_type_முனை)
    pedwarn_c90 (loc, OPT_Wpedantic,
		 "type of bit-field %qs is a GCC extension", name);

  max_width = TYPE_PRECISION (*type);

  எனில் (compare_மரம்_int (*width, max_width) > 0)
    {
      error_at (loc, "width of %qs exceeds its type", name);
      w = max_width;
      *width = build_int_cst (integer_type_முனை, w);
    }
  இல்லையெனில்
    w = மரம்_to_uhwi (*width);

  /* Truncation of hardbool false and true representation values is always safe:
     either the values remain different, or we'll report a problem when creating
     the narrower type.  */
  எனில் (c_hardbool_type_attr (*type))
    திரும்பு;

  எனில் (மரம்_CODE (*type) == ENUMERAL_TYPE)
    {
      கட்டமைப்பு lang_type *lt = TYPE_LANG_SPECIFIC (*type);
      எனில் (!lt
	  || w < மரம்_int_cst_min_precision (lt->enum_min, TYPE_SIGN (*type))
	  || w < மரம்_int_cst_min_precision (lt->enum_max, TYPE_SIGN (*type)))
	warning_at (loc, 0, "%qs is narrower than values of its type", name);
    }
}



/* Print warning about variable length array if necessary.  */

நிலையான வெறுமை
warn_variable_length_array (மரம் name, மரம் size)
{
  எனில் (மரம்_CONSTANT (size))
    {
      எனில் (name)
	pedwarn_c90 (உள்ளீடு_location, OPT_Wvla,
		     "ISO C90 forbids array %qE whose size "
		     "cannot be evaluated", name);
      இல்லையெனில்
	pedwarn_c90 (உள்ளீடு_location, OPT_Wvla, "ISO C90 forbids array "
		     "whose size cannot be evaluated");
    }
  இல்லையெனில்
    {
      எனில் (name)
	pedwarn_c90 (உள்ளீடு_location, OPT_Wvla,
		     "ISO C90 forbids variable length array %qE", name);
      இல்லையெனில்
	pedwarn_c90 (உள்ளீடு_location, OPT_Wvla, "ISO C90 forbids variable "
		     "length array");
    }
}

/* Returns the smallest location != UNKNOWN_LOCATION in LOCATIONS,
   considering only those c_declspec_words found in LIST, which
   must be terminated by cdw_number_of_elements.  */

நிலையான location_t
smallest_type_quals_location (மாறிலி location_t *locations,
			      மாறிலி c_declspec_word *list)
{
  location_t loc = UNKNOWN_LOCATION;
  போது (*list != cdw_எண்_of_elements)
    {
      location_t newloc = locations[*list];
      எனில் (loc == UNKNOWN_LOCATION
	  || (newloc != UNKNOWN_LOCATION && newloc < loc))
	loc = newloc;
      list++;
    }

  திரும்பு loc;
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
நிலையான வெறுமை
add_decl_கோவை (location_t loc, மரம் type, மரம் *கோவை, தருக்க set_name_p)
{
  மரம் bind = NULL_மரம்;
  எனில் (கோவை)
    {
      bind = build3 (BIND_கோவை, void_type_முனை, NULL_மரம், NULL_மரம்,
		     NULL_மரம்);
      மரம்_SIDE_EFFECTS (bind) = 1;
      BIND_கோவை_BODY (bind) = தள்ளு_stmt_list ();
      தள்ளு_scope ();
    }

  மரம் decl = build_decl (loc, TYPE_DECL, NULL_மரம், type);
  pushdecl (decl);
  DECL_ARTIFICIAL (decl) = 1;
  add_stmt (build_stmt (DECL_SOURCE_LOCATION (decl), DECL_கோவை, decl));
  எனில் (set_name_p)
    TYPE_NAME (type) = decl;

  எனில் (bind)
    {
      எடு_scope ();
      BIND_கோவை_BODY (bind) = எடு_stmt_list (BIND_கோவை_BODY (bind));
      எனில் (*கோவை)
	*கோவை = build2 (COMPOUND_கோவை, void_type_முனை, *கோவை, bind);
      இல்லையெனில்
	*கோவை = bind;
    }
}


/* Add attribute "arg spec" to ATTRS corresponding to an array/VLA parameter
   declared with type TYPE.  The attribute has two arguments.  The first is
   a string that encodes the presence of the static keyword.  The second is
   the declared type of the array before adjustment, i.e. as an array type
   including the outermost bound.  */

நிலையான மரம்
build_arg_spec_attribute (மரம் type, தருக்க static_p, மரம் attrs)
{
  மரம் vbchain = மரம்_cons (NULL_மரம், type, NULL_மரம்);
  மரம் acsstr = static_p ? build_string (7, "static") :
			   build_string (1, "");
  மரம் args = மரம்_cons (NULL_மரம், acsstr, vbchain);
  மரம் name = get_identifier ("arg spec");
  திரும்பு மரம்_cons (name, args, attrs);
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

நிலையான மரம்
grokdeclarator (மாறிலி கட்டமைப்பு c_declarator *declarator,
		கட்டமைப்பு c_declspecs *declspecs,
		எண்ணிக்கை decl_context decl_context, தருக்க initialized, மரம் *width,
		மரம் *decl_attrs, மரம் *கோவை, தருக்க *கோவை_const_operands,
		எண்ணிக்கை deprecated_states deprecated_state)
{
  மரம் type = declspecs->type;
  தருக்க threadp = declspecs->thread_p;
  தருக்க constexprp = declspecs->constexpr_p;
  எண்ணிக்கை c_storage_class storage_class = declspecs->storage_class;
  முழு constp;
  முழு restrictp;
  முழு volatilep;
  முழு atomicp;
  முழு type_quals = TYPE_UNQUALIFIED;
  மரம் name = NULL_மரம்;
  தருக்க funcdef_flag = பொய்;
  தருக்க funcdef_syntax = பொய்;
  தருக்க size_varies = பொய்;
  தருக்க size_error = பொய்;
  மரம் decl_attr = declspecs->decl_attr;
  முழு array_ptr_quals = TYPE_UNQUALIFIED;
  மரம் array_ptr_attrs = NULL_மரம்;
  தருக்க array_parm_static = பொய்;
  தருக்க array_parm_vla_unspec_p = பொய்;
  மரம் returned_attrs = NULL_மரம்;
  மரம் decl_id_attrs = NULL_மரம்;
  தருக்க bitfield = width != வெற்று;
  மரம் element_type;
  மரம் orig_qual_type = வெற்று;
  size_t orig_qual_indirect = 0;
  கட்டமைப்பு c_arg_info *arg_info = 0;
  addr_space_t as1, as2, address_space;
  location_t loc = UNKNOWN_LOCATION;
  மரம் கோவை_dummy;
  தருக்க கோவை_const_operands_dummy;
  எண்ணிக்கை c_declarator_kind first_non_attr_kind;
  unsigned முழு alignas_align = 0;

  எனில் (type == NULL_மரம்)
    {
      /* This can occur for auto on a parameter in C23 mode.  Set a
	 dummy type here so subsequent code can give diagnostics for
	 this case.  */
      gcc_assert (declspecs->c23_auto_p);
      gcc_assert (decl_context == PARM);
      type = declspecs->type = integer_type_முனை;
    }
  எனில் (மரம்_CODE (type) == ERROR_MARK)
    திரும்பு error_mark_முனை;
  எனில் (கோவை == வெற்று)
    {
      கோவை = &கோவை_dummy;
      கோவை_dummy = NULL_மரம்;
    }
  எனில் (கோவை_const_operands == வெற்று)
    கோவை_const_operands = &கோவை_const_operands_dummy;

  எனில் (declspecs->கோவை)
    {
      எனில் (*கோவை)
	*கோவை = build2 (COMPOUND_கோவை, மரம்_TYPE (declspecs->கோவை), *கோவை,
			declspecs->கோவை);
      இல்லையெனில்
	*கோவை = declspecs->கோவை;
    }
  *கோவை_const_operands = declspecs->கோவை_const_operands;

  எனில் (decl_context == FUNCDEF)
    funcdef_flag = உண்மை, decl_context = NORMAL;

  /* Look inside a declarator for the name being declared
     and get it as an IDENTIFIER_NODE, for an error message.  */
  {
    மாறிலி கட்டமைப்பு c_declarator *decl = declarator;

    first_non_attr_kind = cdk_attrs;
    போது (decl)
      தேர்வு (decl->kind)
	{
	நிலை cdk_array:
	  loc = decl->id_loc;
	  /* FALL THRU.  */

	நிலை cdk_function:
	நிலை cdk_pointer:
	  funcdef_syntax = (decl->kind == cdk_function);
	  எனில் (first_non_attr_kind == cdk_attrs)
	    first_non_attr_kind = decl->kind;
	  decl = decl->declarator;
	  நிறுத்து;

	நிலை cdk_attrs:
	  decl = decl->declarator;
	  நிறுத்து;

	நிலை cdk_id:
	  loc = decl->id_loc;
	  எனில் (decl->u.id.id)
	    name = decl->u.id.id;
	  decl_id_attrs = decl->u.id.attrs;
	  எனில் (first_non_attr_kind == cdk_attrs)
	    first_non_attr_kind = decl->kind;
	  decl = 0;
	  நிறுத்து;

	இயல்பு:
	  gcc_unreachable ();
	}
    எனில் (name == NULL_மரம்)
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
  எனில் (declspecs->enum_type_specifier_ref_p)
    error_at (loc, "%<enum%> underlying type may not be specified here");

  /* A function definition's declarator must have the form of
     a function declarator.  */

  எனில் (funcdef_flag && !funcdef_syntax)
    திரும்பு NULL_மரம்;

  /* If this looks like a function definition, make it one,
     even if it occurs where parms are expected.
     Then store_parm_decls will reject it and not use it as a parm.  */
  எனில் (decl_context == NORMAL && !funcdef_flag && current_scope->parm_flag)
    decl_context = PARM;

  எனில் (deprecated_state != UNAVAILABLE_DEPRECATED_SUPPRESS)
    {
      எனில் (declspecs->unavailable_p)
	error_unavailable_use (declspecs->type, declspecs->decl_attr);
      இல்லையெனில் எனில் (declspecs->deprecated_p
		&& deprecated_state != DEPRECATED_SUPPRESS)
	warn_deprecated_use (declspecs->type, declspecs->decl_attr);
    }

  எனில் ((decl_context == NORMAL || decl_context == FIELD)
      && current_scope == file_scope
      && c_type_variably_modified_p (type))
    {
      எனில் (name)
	error_at (loc, "variably modified %qE at file scope", name);
      இல்லையெனில்
	error_at (loc, "variably modified field at file scope");
      type = integer_type_முனை;
    }

  size_varies = C_TYPE_VARIABLE_SIZE (type) != 0;

  /* Diagnose defaulting to "int".  */

  எனில் (declspecs->default_int_p)
    {
      /* Issue a warning if this is an ISO C 99 program or if
	 -Wreturn-type and this is a function, or if -Wimplicit;
	 prefer the former warning since it is more explicit.  */
      எனில் ((warn_implicit_int || warn_return_type > 0 || flag_isoc99)
	  && funcdef_flag)
	warn_about_return_type = 1;
      இல்லையெனில்
	{
	  எனில் (name)
	    permerror_opt (loc, OPT_Wimplicit_int,
			   "type defaults to %<int%> in declaration "
			   "of %qE", name);
	  இல்லையெனில்
	    permerror_opt (loc, OPT_Wimplicit_int,
			   "type defaults to %<int%> in type name");
	}
    }

  /* Adjust the type if a bit-field is being declared,
     -funsigned-bitfields applied and the type is not explicitly
     "signed".  */
  எனில் (bitfield && !flag_signed_bitfields && !declspecs->explicit_signed_p
      && மரம்_CODE (type) == INTEGER_TYPE)
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

  எனில் (constp > 1)
    pedwarn_c90 (loc, OPT_Wpedantic, "duplicate %<const%>");
  எனில் (restrictp > 1)
    pedwarn_c90 (loc, OPT_Wpedantic, "duplicate %<restrict%>");
  எனில் (volatilep > 1)
    pedwarn_c90 (loc, OPT_Wpedantic, "duplicate %<volatile%>");
  எனில் (atomicp > 1)
    pedwarn_c90 (loc, OPT_Wpedantic, "duplicate %<_Atomic%>");

  எனில் (!ADDR_SPACE_GENERIC_P (as1) && !ADDR_SPACE_GENERIC_P (as2) && as1 != as2)
    error_at (loc, "conflicting named address spaces (%s vs %s)",
	      c_addr_space_name (as1), c_addr_space_name (as2));

  எனில் ((மரம்_CODE (type) == ARRAY_TYPE
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
  எனில் (type_quals != TYPE_QUALS (element_type))
    orig_qual_type = NULL_மரம்;

  /* Applying the _Atomic qualifier to an array type (through the use
     of typedefs or typeof) must be detected here.  If the qualifier
     is introduced later, any appearance of applying it to an array is
     actually applying it to an element of that array.  */
  எனில் (declspecs->atomic_p && மரம்_CODE (type) == ARRAY_TYPE)
    error_at (loc, "%<_Atomic%>-qualified array type");

  /* Warn about storage classes that are invalid for certain
     kinds of declarations (parameters, typenames, etc.).  */

  எனில் (funcdef_flag
      && (threadp
	  || constexprp
	  || storage_class == csc_auto
	  || storage_class == csc_register
	  || storage_class == csc_typedef))
    {
      எனில் (storage_class == csc_auto)
	pedwarn (loc,
		 (current_scope == file_scope) ? 0 : OPT_Wpedantic,
		 "function definition declared %<auto%>");
      எனில் (storage_class == csc_register)
	error_at (loc, "function definition declared %<register%>");
      எனில் (storage_class == csc_typedef)
	error_at (loc, "function definition declared %<typedef%>");
      எனில் (threadp)
	error_at (loc, "function definition declared %qs",
		  declspecs->thread_gnu_p ? "__thread" : "_Thread_local");
      threadp = பொய்;
      /* The parser ensures a constexpr function definition never
	 reaches here.  */
      gcc_assert (!constexprp);
      எனில் (storage_class == csc_auto
	  || storage_class == csc_register
	  || storage_class == csc_typedef)
	storage_class = csc_none;
    }
  இல்லையெனில் எனில் (decl_context != NORMAL && (storage_class != csc_none
				      || threadp
				      || constexprp
				      || declspecs->c23_auto_p))
    {
      எனில் (decl_context == PARM
	  && storage_class == csc_register
	  && !constexprp
	  && !declspecs->c23_auto_p)
	;
      இல்லையெனில்
	{
	  தேர்வு (decl_context)
	    {
	    நிலை FIELD:
	      எனில் (name)
		error_at (loc, "storage class specified for structure "
		    	  "field %qE", name);
	      இல்லையெனில்
		error_at (loc, "storage class specified for structure field");
	      நிறுத்து;
	    நிலை PARM:
	      எனில் (name)
		error_at (loc, "storage class specified for parameter %qE",
		    	  name);
	      இல்லையெனில்
		error_at (loc, "storage class specified for unnamed parameter");
	      நிறுத்து;
	    இயல்பு:
	      error_at (loc, "storage class specified for typename");
	      நிறுத்து;
	    }
	  storage_class = csc_none;
	  threadp = பொய்;
	  constexprp = பொய்;
	}
    }
  இல்லையெனில் எனில் (storage_class == csc_extern
	   && initialized
	   && !funcdef_flag)
    {
      /* 'extern' with initialization is invalid if not at file scope.  */
       எனில் (current_scope == file_scope)
         {
           /* It is fine to have 'extern const' when compiling at C
              and C++ intersection.  */
           எனில் (!(warn_cxx_compat && constp))
             warning_at (loc, 0, "%qE initialized and declared %<extern%>",
		 	 name);
         }
      இல்லையெனில்
	error_at (loc, "%qE has both %<extern%> and initializer", name);
    }
  இல்லையெனில் எனில் (current_scope == file_scope)
    {
      எனில் (storage_class == csc_auto)
	error_at (loc, "file-scope declaration of %qE specifies %<auto%>",
	    	  name);
      எனில் (pedantic && storage_class == csc_register)
	pedwarn (உள்ளீடு_location, OPT_Wpedantic,
		 "file-scope declaration of %qE specifies %<register%>", name);
    }
  இல்லையெனில்
    {
      எனில் (storage_class == csc_extern && funcdef_flag)
	error_at (loc, "nested function %qE declared %<extern%>", name);
      இல்லையெனில் எனில் (threadp && storage_class == csc_none)
	{
	  error_at (loc, "function-scope %qE implicitly auto and declared "
		    "%qs", name,
		    declspecs->thread_gnu_p ? "__thread" : "_Thread_local");
	  threadp = பொய்;
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

  போது (declarator && declarator->kind != cdk_id)
    {
      எனில் (type == error_mark_முனை)
	{
	  declarator = declarator->declarator;
	  தொடர்;
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

      எனில் (array_ptr_quals != TYPE_UNQUALIFIED
	  || array_ptr_attrs != NULL_மரம்
	  || array_parm_static)
	{
	  /* Only the innermost declarator (making a parameter be of
	     array type which is converted to pointer type)
	     may have static or type qualifiers.  */
	  error_at (loc, "static or type qualifiers in non-parameter array declarator");
	  array_ptr_quals = TYPE_UNQUALIFIED;
	  array_ptr_attrs = NULL_மரம்;
	  array_parm_static = பொய்;
	}

      தேர்வு (declarator->kind)
	{
	நிலை cdk_attrs:
	  {
	    /* A declarator with embedded attributes.  */
	    மரம் attrs = declarator->u.attrs;
	    மாறிலி கட்டமைப்பு c_declarator *inner_decl;
	    முழு attr_flags = 0;
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
	    போது (inner_decl->kind == cdk_attrs)
	      inner_decl = inner_decl->declarator;
	    எனில் (!cxx11_attribute_p (attrs))
	      {
		எனில் (inner_decl->kind == cdk_id)
		  attr_flags |= (முழு) ATTR_FLAG_DECL_NEXT;
		இல்லையெனில் எனில் (inner_decl->kind == cdk_function)
		  attr_flags |= (முழு) ATTR_FLAG_FUNCTION_NEXT;
		இல்லையெனில் எனில் (inner_decl->kind == cdk_array)
		  attr_flags |= (முழு) ATTR_FLAG_ARRAY_NEXT;
	      }
	    attrs = c_warn_type_attributes (type, attrs);
	    returned_attrs = decl_attributes (&type,
					      chainon (returned_attrs, attrs),
					      attr_flags);
	    நிறுத்து;
	  }
	நிலை cdk_array:
	  {
	    மரம் itype = NULL_மரம்;
	    மரம் size = declarator->u.array.dimen;
	    /* The index is a signed object `sizetype' bits wide.  */
	    மரம் index_type = c_common_signed_type (sizetype);

	    array_ptr_quals = declarator->u.array.quals;
	    array_ptr_attrs = declarator->u.array.attrs;
	    array_parm_static = declarator->u.array.static_p;
	    array_parm_vla_unspec_p = declarator->u.array.vla_unspec_p;

	    declarator = declarator->declarator;

	    தருக்க flexible_array_member = பொய்;

	    /* Check for some types that there cannot be arrays of.  */

	    எனில் (VOID_TYPE_P (type))
	      {
		எனில் (name)
		  error_at (loc, "declaration of %qE as array of voids", name);
		இல்லையெனில்
		  error_at (loc, "declaration of type name as array of voids");
		type = error_mark_முனை;
	      }

	    எனில் (மரம்_CODE (type) == FUNCTION_TYPE)
	      {
		எனில் (name)
		  error_at (loc, "declaration of %qE as array of functions",
		      	    name);
		இல்லையெனில்
		  error_at (loc, "declaration of type name as array of "
		            "functions");
		type = error_mark_முனை;
	      }

	    எனில் (pedantic && !in_system_header_at (உள்ளீடு_location)
		&& flexible_array_type_p (type))
	      pedwarn (loc, OPT_Wpedantic,
		       "invalid use of structure with flexible array member");

	    எனில் (size == error_mark_முனை)
	      type = error_mark_முனை;

	    எனில் (type == error_mark_முனை)
	      தொடர்;

	    எனில் (!verify_type_context (loc, TCTX_ARRAY_ELEMENT, type))
	      {
		type = error_mark_முனை;
		தொடர்;
	      }

	    /* If size was specified, set ITYPE to a range-type for
	       that size.  Otherwise, ITYPE remains null.  finish_decl
	       may figure it out from an initial value.  */

	    எனில் (size)
	      {
		தருக்க size_maybe_const = உண்மை;
		தருக்க size_int_const = (மரம்_CODE (size) == INTEGER_CST
				       && !மரம்_OVERFLOW (size));
		தருக்க this_size_varies = பொய்;

		/* Strip NON_LVALUE_EXPRs since we aren't using as an
		   lvalue.  */
		STRIP_TYPE_NOPS (size);

		எனில் (!INTEGRAL_TYPE_P (மரம்_TYPE (size)))
		  {
		    எனில் (name)
		      error_at (loc, "size of array %qE has non-integer type",
				name);
		    இல்லையெனில்
		      error_at (loc,
				"size of unnamed array has non-integer type");
		    size = integer_one_முனை;
		    size_int_const = உண்மை;
		    size_error = உண்மை;
		  }
		/* This can happen with enum forward declaration.  */
		இல்லையெனில் எனில் (!COMPLETE_TYPE_P (மரம்_TYPE (size)))
		  {
		    எனில் (name)
		      error_at (loc, "size of array %qE has incomplete type",
				name);
		    இல்லையெனில்
		      error_at (loc, "size of unnamed array has incomplete "
				"type");
		    size = integer_one_முனை;
		    size_int_const = உண்மை;
		    size_error = உண்மை;
		  }

		size = c_fully_fold (size, பொய், &size_maybe_const);

		எனில் (pedantic && size_maybe_const && integer_zerop (size))
		  {
		    எனில் (name)
		      pedwarn (loc, OPT_Wpedantic,
			       "ISO C forbids zero-size array %qE", name);
		    இல்லையெனில்
		      pedwarn (loc, OPT_Wpedantic,
			       "ISO C forbids zero-size array");
		  }

		எனில் (மரம்_CODE (size) == INTEGER_CST && size_maybe_const)
		  {
		    constant_expression_warning (size);
		    எனில் (மரம்_int_cst_sgn (size) < 0)
		      {
			எனில் (name)
			  error_at (loc, "size of array %qE is negative", name);
			இல்லையெனில்
			  error_at (loc, "size of unnamed array is negative");
			size = integer_one_முனை;
			size_int_const = உண்மை;
			size_error = உண்மை;
		      }
		    /* Handle a size folded to an integer constant but
		       not an integer constant expression.  */
		    எனில் (!size_int_const)
		      {
			/* If this is a file scope declaration of an
			   ordinary identifier, this is invalid code;
			   diagnosing it here and not subsequently
			   treating the type as variable-length avoids
			   more confusing diagnostics later.  */
			எனில் ((decl_context == NORMAL || decl_context == FIELD)
			    && current_scope == file_scope)
			  pedwarn (உள்ளீடு_location, 0,
				   "variably modified %qE at file scope",
				   name);
			இல்லையெனில்
			  this_size_varies = size_varies = உண்மை;
			warn_variable_length_array (name, size);
		      }
		  }
		இல்லையெனில் எனில் ((decl_context == NORMAL || decl_context == FIELD)
			 && current_scope == file_scope)
		  {
		    error_at (loc, "variably modified %qE at file scope", name);
		    size = integer_one_முனை;
		  }
		இல்லையெனில்
		  {
		    /* Make sure the array size remains visibly
		       nonconstant even if it is (eg) a const variable
		       with known value.  */
		    this_size_varies = size_varies = உண்மை;
		    warn_variable_length_array (name, size);
		    எனில் (sanitize_flags_p (SANITIZE_VLA)
			&& current_function_decl != NULL_மரம்
			&& decl_context == NORMAL)
		      {
			/* Evaluate the array size only once.  */
			size = save_கோவை (size);
			size = c_fully_fold (size, பொய், வெற்று);
		        size = fold_build2 (COMPOUND_கோவை, மரம்_TYPE (size),
					    ubsan_instrument_vla (loc, size),
					    size);
		      }
		  }

		எனில் (integer_zerop (size) && !this_size_varies)
		  {
		    /* A zero-length array cannot be represented with
		       an unsigned index type, which is what we'll
		       get with build_index_type.  Create an
		       open-ended range instead.  */
		    itype = build_index_type (NULL_மரம்);
		  }
		இல்லையெனில்
		  {
		    /* Arrange for the SAVE_EXPR on the inside of the
		       MINUS_EXPR, which allows the -1 to get folded
		       with the +1 that happens when building TYPE_SIZE.  */
		    எனில் (size_varies)
		      size = save_கோவை (size);
		    எனில் (this_size_varies && மரம்_CODE (size) == INTEGER_CST)
		      size = build2 (COMPOUND_கோவை, மரம்_TYPE (size),
				     integer_zero_முனை, size);

		    /* Compute the maximum valid index, that is, size
		       - 1.  Do the calculation in index_type, so that
		       if it is a variable the computations will be
		       done in the proper mode.  */
		    itype = fold_build2_loc (loc, MINUS_கோவை, index_type,
					     convert (index_type, size),
					     convert (index_type,
						      size_one_முனை));

		    /* The above overflows when size does not fit
		       in index_type.
		       ???  While a size of INT_MAX+1 technically shouldn't
		       cause an overflow (because we subtract 1), handling
		       this case seems like an unnecessary complication.  */
		    எனில் (மரம்_CODE (size) == INTEGER_CST
			&& !int_fits_type_p (size, index_type))
		      {
			எனில் (name)
			  error_at (loc, "size of array %qE is too large",
			            name);
			இல்லையெனில்
			  error_at (loc, "size of unnamed array is too large");
			type = error_mark_முனை;
			தொடர்;
		      }

		    itype = build_index_type (itype);
		  }
		எனில் (this_size_varies)
		  {
		    எனில் (மரம்_SIDE_EFFECTS (size))
		      {
			எனில் (*கோவை)
			  *கோவை = build2 (COMPOUND_கோவை, மரம்_TYPE (size),
					  *கோவை, size);
			இல்லையெனில்
			  *கோவை = size;
		      }
		    *கோவை_const_operands &= size_maybe_const;
		  }
	      }
	    இல்லையெனில் எனில் (decl_context == FIELD)
	      {
		எனில் (array_parm_vla_unspec_p)
		  /* Field names can in fact have function prototype
		     scope so [*] is disallowed here through making
		     the field variably modified, not through being
		     something other than a declaration with function
		     prototype scope.  */
		  size_varies = உண்மை;
		இல்லையெனில்
		  {
		    மாறிலி கட்டமைப்பு c_declarator *t = declarator;
		    போது (t->kind == cdk_attrs)
		      t = t->declarator;
		    flexible_array_member = (t->kind == cdk_id);
		  }
		எனில் (flexible_array_member
		    && !in_system_header_at (உள்ளீடு_location))
		  pedwarn_c90 (loc, OPT_Wpedantic, "ISO C90 does not "
			       "support flexible array members");

		/* ISO C99 Flexible array members are effectively
		   identical to GCC's zero-length array extension.  */
		எனில் (flexible_array_member)
		  itype = build_index_type (NULL_மரம்);
	      }

	    /* Complain about arrays of incomplete types.  */
	    எனில் (!COMPLETE_TYPE_P (type))
	      {
		auto_diagnostic_group d;
		error_at (loc, "array type has incomplete element type %qT",
			  type);
		/* See if we can be more helpful.  */
		எனில் (மரம்_CODE (type) == ARRAY_TYPE)
		  {
		    எனில் (name)
		      inform (loc, "declaration of %qE as multidimensional "
			      "array must have bounds for all dimensions "
			      "except the first", name);
		    இல்லையெனில்
		      inform (loc, "declaration of multidimensional array "
			      "must have bounds for all dimensions except "
			      "the first");
		  }
		type = error_mark_முனை;
	      }
	    இல்லையெனில்
	    /* When itype is NULL, a shared incomplete array type is
	       returned for all array of a given type.  Elsewhere we
	       make sure we don't complete that type before copying
	       it, but here we want to make sure we don't ever
	       modify the shared type, so we gcc_assert (itype)
	       below.  */
	      {
		addr_space_t as = DECODE_QUAL_ADDR_SPACE (type_quals);
		எனில் (!ADDR_SPACE_GENERIC_P (as) && as != TYPE_ADDR_SPACE (type))
		  type = c_build_qualified_type (type,
						 ENCODE_QUAL_ADDR_SPACE (as));
		எனில் (array_parm_vla_unspec_p)
		  type = c_build_array_type_unspecified (type);
		/* The GCC extension for zero-length arrays differs from
		   ISO flexible array members in that sizeof yields
		   zero.  */
		இல்லையெனில் எனில் (size && integer_zerop (size))
		  type = c_build_array_type_zero_size (type);
		இல்லையெனில்
		  type = c_build_array_type (type, itype);

		எனில் (!valid_array_size_p (loc, type, name))
		  type = error_mark_முனை;
	      }

	    எனில் (array_parm_vla_unspec_p)
	      {
		/* C99 6.7.5.2p4 */
		எனில் (decl_context == TYPENAME)
		  warning (0, "%<[*]%> not in a declaration");
		இல்லையெனில் எனில் (decl_context != GENERIC_ASSOC
			 && decl_context != PARM
			 && decl_context != FIELD)
		  {
		    error ("%<[*]%> not allowed in other than function prototype scope "
			   "or generic association");
		    type = error_mark_முனை;
		  }
		size_varies = உண்மை;
	      }


	    gcc_assert (type == error_mark_முனை
			|| flexible_array_member
			   == flexible_array_member_type_p (type));

	    எனில் (decl_context != PARM
		&& (array_ptr_quals != TYPE_UNQUALIFIED
		    || array_ptr_attrs != NULL_மரம்
		    || array_parm_static))
	      {
		error_at (loc, "static or type qualifiers in non-parameter "
			  "array declarator");
		array_ptr_quals = TYPE_UNQUALIFIED;
		array_ptr_attrs = NULL_மரம்;
		array_parm_static = பொய்;
	      }
	    orig_qual_indirect++;
	    நிறுத்து;
	  }
	நிலை cdk_function:
	  {
	    /* Say it's a definition only for the declarator closest
	       to the identifier, apart possibly from some
	       attributes.  */
	    தருக்க really_funcdef = பொய்;
	    மரம் arg_types;
	    orig_qual_type = NULL_மரம்;
	    எனில் (funcdef_flag)
	      {
		மாறிலி கட்டமைப்பு c_declarator *t = declarator->declarator;
		போது (t->kind == cdk_attrs)
		  t = t->declarator;
		really_funcdef = (t->kind == cdk_id);
	      }

	    /* Declaring a function type.  Make sure we have a valid
	       type for the function to return.  */
	    எனில் (type == error_mark_முனை)
	      தொடர்;

	    size_varies = பொய்;

	    /* Warn about some types functions can't return.  */
	    எனில் (மரம்_CODE (type) == FUNCTION_TYPE)
	      {
		எனில் (name)
		  error_at (loc, "%qE declared as function returning a "
		      		 "function", name);
		இல்லையெனில்
		  error_at (loc, "type name declared as function "
			    "returning a function");
		type = integer_type_முனை;
	      }
	    எனில் (மரம்_CODE (type) == ARRAY_TYPE)
	      {
		எனில் (name)
		  error_at (loc, "%qE declared as function returning an array",
		      	    name);
		இல்லையெனில்
		  error_at (loc, "type name declared as function returning "
		      	    "an array");
		type = integer_type_முனை;
	      }

	    /* Construct the function type and go to the next
	       inner layer of declarator.  */
	    arg_info = declarator->u.arg_info;
	    arg_types = grokparms (arg_info, really_funcdef);

	    /* Type qualifiers before the return type of the function
	       qualify the return type, not the function type.  */
	    எனில் (type_quals)
	      {
		மாறிலி எண்ணிக்கை c_declspec_word ignored_quals_list[] =
		  {
		    cdw_const, cdw_volatile, cdw_restrict, cdw_address_space,
		    cdw_atomic, cdw_எண்_of_elements
		  };
		location_t specs_loc
		  = smallest_type_quals_location (declspecs->locations,
						  ignored_quals_list);
		எனில் (specs_loc == UNKNOWN_LOCATION)
		  specs_loc = declspecs->locations[cdw_typedef];
		எனில் (specs_loc == UNKNOWN_LOCATION)
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
		முழு quals_used = type_quals;
		எனில் (flag_isoc23)
		  quals_used = 0;
		இல்லையெனில் எனில் (flag_isoc11)
		  quals_used &= TYPE_QUAL_ATOMIC;
		எனில் (quals_used && VOID_TYPE_P (type) && really_funcdef)
		  pedwarn (specs_loc, 0,
			   "function definition has qualified void "
			   "return type");
		இல்லையெனில்
		  warning_at (specs_loc, OPT_Wignored_qualifiers,
			      "type qualifiers ignored on function "
			      "return type");

		/* Ensure an error for restrict on invalid types; the
		   DR#423 resolution is not entirely clear about
		   this.  */
		எனில் (flag_isoc11
		    && (type_quals & TYPE_QUAL_RESTRICT)
		    && (!POINTER_TYPE_P (type)
			|| !C_TYPE_OBJECT_OR_INCOMPLETE_P (மரம்_TYPE (type))))
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
	    நிறுத்து;
	  }
	நிலை cdk_pointer:
	  {
	    /* Merge any constancy or volatility into the target type
	       for the pointer.  */
	    எனில் ((type_quals & TYPE_QUAL_ATOMIC)
		&& மரம்_CODE (type) == FUNCTION_TYPE)
	      {
		error_at (loc,
			  "%<_Atomic%>-qualified function type");
		type_quals &= ~TYPE_QUAL_ATOMIC;
	      }
	    இல்லையெனில் எனில் (pedantic && மரம்_CODE (type) == FUNCTION_TYPE
		     && type_quals)
	      pedwarn (loc, OPT_Wpedantic,
		       "ISO C forbids qualified function types");
	    எனில் (type_quals)
	      type = c_build_qualified_type (type, type_quals, orig_qual_type,
					     orig_qual_indirect);
	    orig_qual_type = NULL_மரம்;
	    size_varies = பொய்;

	    /* When the pointed-to type involves components of variable size,
	       care must be taken to ensure that the size evaluation code is
	       emitted early enough to dominate all the possible later uses
	       and late enough for the variables on which it depends to have
	       been assigned.

	       This is expected to happen automatically when the pointed-to
	       type has a name/declaration of it's own, but special attention
	       is required if the type is anonymous. */
	    எனில் (!TYPE_NAME (type) && c_type_variably_modified_p (type))
	      {
		தருக்க bind_p = decl_context == TYPENAME
			      || decl_context == FIELD
			      || decl_context == PARM;
		add_decl_கோவை (loc, type, bind_p ? கோவை : வெற்று, உண்மை);
	      }

	    type = c_build_pointer_type (type);

	    /* Process type qualifiers (such as const or volatile)
	       that were given inside the `*'.  */
	    type_quals = declarator->u.pointer_quals;

	    declarator = declarator->declarator;
	    நிறுத்து;
	  }
	இயல்பு:
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
  எனில் (!ADDR_SPACE_GENERIC_P (address_space))
    {
      எனில் (decl_context == NORMAL)
	{
	  தேர்வு (storage_class)
	    {
	    நிலை csc_auto:
	      error ("%qs combined with %<auto%> qualifier for %qE",
		     c_addr_space_name (address_space), name);
	      நிறுத்து;
	    நிலை csc_register:
	      error ("%qs combined with %<register%> qualifier for %qE",
		     c_addr_space_name (address_space), name);
	      நிறுத்து;
	    நிலை csc_none:
	      எனில் (current_function_scope)
		{
		  error ("%qs specified for auto variable %qE",
			 c_addr_space_name (address_space), name);
		  நிறுத்து;
		}
	      நிறுத்து;
	    நிலை csc_static:
	    நிலை csc_extern:
	    நிலை csc_typedef:
	      நிறுத்து;
	    இயல்பு:
	      gcc_unreachable ();
	    }
	}
      இல்லையெனில் எனில் (decl_context == PARM && மரம்_CODE (type) != ARRAY_TYPE)
	{
	  எனில் (name)
	    error ("%qs specified for parameter %qE",
		   c_addr_space_name (address_space), name);
	  இல்லையெனில்
	    error ("%qs specified for unnamed parameter",
		   c_addr_space_name (address_space));
	}
      இல்லையெனில் எனில் (decl_context == FIELD)
	{
	  எனில் (name)
	    error ("%qs specified for structure field %qE",
		   c_addr_space_name (address_space), name);
	  இல்லையெனில்
	    error ("%qs specified for structure field",
		   c_addr_space_name (address_space));
	}
    }

  /* Check the type and width of a bit-field.  */
  எனில் (bitfield)
    {
      check_bitfield_type_and_width (loc, &type, width, name);
      /* C11 makes it implementation-defined (6.7.2.1#5) whether
	 atomic types are permitted for bit-fields; we have no code to
	 make bit-field accesses atomic, so disallow them.  */
      எனில் (type_quals & TYPE_QUAL_ATOMIC)
	{
	  எனில் (name)
	    error_at (loc, "bit-field %qE has atomic type", name);
	  இல்லையெனில்
	    error_at (loc, "bit-field has atomic type");
	  type_quals &= ~TYPE_QUAL_ATOMIC;
	}
    }

  /* Reject invalid uses of _Alignas.  */
  எனில் (declspecs->alignas_p)
    {
      எனில் (storage_class == csc_typedef)
	error_at (loc, "alignment specified for typedef %qE", name);
      இல்லையெனில் எனில் (storage_class == csc_register)
	error_at (loc, "alignment specified for %<register%> object %qE",
		  name);
      இல்லையெனில் எனில் (decl_context == PARM)
	{
	  எனில் (name)
	    error_at (loc, "alignment specified for parameter %qE", name);
	  இல்லையெனில்
	    error_at (loc, "alignment specified for unnamed parameter");
	}
      இல்லையெனில் எனில் (bitfield)
	{
	  எனில் (name)
	    error_at (loc, "alignment specified for bit-field %qE", name);
	  இல்லையெனில்
	    error_at (loc, "alignment specified for unnamed bit-field");
	}
      இல்லையெனில் எனில் (மரம்_CODE (type) == FUNCTION_TYPE)
	error_at (loc, "alignment specified for function %qE", name);
      இல்லையெனில் எனில் (declspecs->align_log != -1 && TYPE_P (type))
	{
	  alignas_align = 1U << declspecs->align_log;
	  எனில் (alignas_align < min_align_of_type (type))
	    {
	      எனில் (name)
		error_at (loc, "%<_Alignas%> specifiers cannot reduce "
			  "alignment of %qE", name);
	      இல்லையெனில்
		error_at (loc, "%<_Alignas%> specifiers cannot reduce "
			  "alignment of unnamed field");
	      alignas_align = 0;
	    }
	}
    }

  /* If this is declaring a typedef name, return a TYPE_DECL.  */

  எனில் (storage_class == csc_typedef)
    {
      மரம் decl;
      எனில் ((type_quals & TYPE_QUAL_ATOMIC)
	  && மரம்_CODE (type) == FUNCTION_TYPE)
	{
	  error_at (loc,
		    "%<_Atomic%>-qualified function type");
	  type_quals &= ~TYPE_QUAL_ATOMIC;
	}
      இல்லையெனில் எனில் (pedantic && மரம்_CODE (type) == FUNCTION_TYPE
	       && type_quals)
	pedwarn (loc, OPT_Wpedantic,
		 "ISO C forbids qualified function types");
      எனில் (type_quals)
	type = c_build_qualified_type (type, type_quals, orig_qual_type,
				       orig_qual_indirect);
      decl = build_decl (declarator->id_loc,
			 TYPE_DECL, declarator->u.id.id, type);
      எனில் (declspecs->explicit_signed_p)
	C_TYPEDEF_EXPLICITLY_SIGNED (decl) = 1;
      எனில் (declspecs->inline_p)
	pedwarn (loc, 0,"typedef %q+D declared %<inline%>", decl);
      எனில் (declspecs->noreturn_p)
	pedwarn (loc, 0,"typedef %q+D declared %<_Noreturn%>", decl);

      எனில் (warn_cxx_compat && declarator->u.id.id != NULL_மரம்)
	{
	  கட்டமைப்பு c_binding *b = I_TAG_BINDING (declarator->u.id.id);

	  எனில் (b != வெற்று
	      && b->decl != NULL_மரம்
	      && (B_IN_CURRENT_SCOPE (b)
		  || (current_scope == file_scope && B_IN_EXTERNAL_SCOPE (b)))
	      && TYPE_MAIN_VARIANT (b->decl) != TYPE_MAIN_VARIANT (type))
	    {
	      auto_diagnostic_group d;
	      எனில் (warning_at (declarator->id_loc, OPT_Wc___compat,
			      "using %qD as both a typedef and a tag is "
			      "invalid in C++", decl)
		  && b->locus != UNKNOWN_LOCATION)
		inform (b->locus, "originally defined here");
	    }
	}

      திரும்பு decl;
    }

  /* If this is a type name (such as, in a cast or sizeof),
     compute the type and return it now.  */

  எனில் (decl_context == TYPENAME || decl_context == GENERIC_ASSOC)
    {
      /* Note that the grammar rejects storage classes in typenames
	 and fields.  */
      gcc_assert (storage_class == csc_none && !threadp
		  && !declspecs->inline_p && !declspecs->noreturn_p);
      எனில் ((type_quals & TYPE_QUAL_ATOMIC)
	  && மரம்_CODE (type) == FUNCTION_TYPE)
	{
	  error_at (loc,
		    "%<_Atomic%>-qualified function type");
	  type_quals &= ~TYPE_QUAL_ATOMIC;
	}
      இல்லையெனில் எனில் (pedantic && மரம்_CODE (type) == FUNCTION_TYPE
	       && type_quals)
	pedwarn (loc, OPT_Wpedantic,
		 "ISO C forbids const or volatile function types");
      எனில் (type_quals)
	type = c_build_qualified_type (type, type_quals, orig_qual_type,
				       orig_qual_indirect);
      திரும்பு type;
    }

  எனில் (pedantic && decl_context == FIELD
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

  எனில் (VOID_TYPE_P (type) && decl_context != PARM
      && !((decl_context != FIELD && மரம்_CODE (type) != FUNCTION_TYPE)
	    && (storage_class == csc_extern
		|| (current_scope == file_scope
		    && !(storage_class == csc_static
			 || storage_class == csc_register)))))
    {
      error_at (loc, "variable or field %qE declared void", name);
      type = integer_type_முனை;
    }

  /* Now create the decl, which may be a VAR_DECL, a PARM_DECL
     or a FUNCTION_DECL, depending on DECL_CONTEXT and TYPE.  */

  {
    மரம் decl;

    எனில் (decl_context == PARM)
      {
	மரம் promoted_type;
	தருக்க array_parameter_p = பொய்;

	/* A parameter declared as an array of T is really a pointer to T.
	   One declared as a function is really a pointer to a function.  */

	எனில் (மரம்_CODE (type) == ARRAY_TYPE)
	  {
	    எனில் (!size_error)
	      *decl_attrs = build_arg_spec_attribute (type, array_parm_static,
						      *decl_attrs);

	    /* Transfer const-ness of array into that of type pointed to.  */
	    type = மரம்_TYPE (type);
	    எனில் (orig_qual_type != NULL_மரம்)
	      {
		எனில் (orig_qual_indirect == 0)
		  orig_qual_type = மரம்_TYPE (orig_qual_type);
		இல்லையெனில்
		  orig_qual_indirect--;
	      }
	    எனில் (type_quals)
	      type = c_build_qualified_type (type, type_quals, orig_qual_type,
					     orig_qual_indirect);

	    /* The pointed-to type may need a decl expr (see above).  */
	    எனில் (!TYPE_NAME (type) && c_type_variably_modified_p (type))
	      {
		தருக்க bind_p = decl_context == TYPENAME
			      || decl_context == FIELD
			      || decl_context == PARM;
		add_decl_கோவை (loc, type, bind_p ? கோவை : வெற்று, உண்மை);
	      }

	    type = c_build_pointer_type (type);
	    type_quals = array_ptr_quals;
	    எனில் (type_quals)
	      type = c_build_qualified_type (type, type_quals);

	    /* We don't yet implement attributes in this context.  */
	    எனில் (array_ptr_attrs != NULL_மரம்)
	      warning_at (loc, OPT_Wattributes,
			  "attributes in parameter array declarator ignored");

	    size_varies = பொய்;
	    array_parameter_p = உண்மை;
	  }
	இல்லையெனில் எனில் (மரம்_CODE (type) == FUNCTION_TYPE)
	  {
	    எனில் (type_quals & TYPE_QUAL_ATOMIC)
	      {
		error_at (loc,
			  "%<_Atomic%>-qualified function type");
		type_quals &= ~TYPE_QUAL_ATOMIC;
	      }
	    இல்லையெனில் எனில் (type_quals)
	      pedwarn (loc, OPT_Wpedantic,
		       "ISO C forbids qualified function types");
	    எனில் (type_quals)
	      type = c_build_qualified_type (type, type_quals);
	    type = c_build_pointer_type (type);
	    type_quals = TYPE_UNQUALIFIED;
	  }
	இல்லையெனில் எனில் (type_quals)
	  type = c_build_qualified_type (type, type_quals);

	decl = build_decl (declarator->id_loc,
			   PARM_DECL, declarator->u.id.id, type);
	எனில் (size_varies)
	  C_DECL_VARIABLE_SIZE (decl) = 1;
	C_ARRAY_PARAMETER (decl) = array_parameter_p;

	/* Compute the type actually passed in the parmlist,
	   for the case where there is no prototype.
	   (For example, shorts and chars are passed as ints.)
	   When there is a prototype, this is overridden later.  */

	எனில் (type == error_mark_முனை)
	  promoted_type = type;
	இல்லையெனில்
	  promoted_type = c_type_promotes_to (type);

	DECL_ARG_TYPE (decl) = promoted_type;
	எனில் (declspecs->inline_p)
	  pedwarn (loc, 0, "parameter %q+D declared %<inline%>", decl);
	எனில் (declspecs->noreturn_p)
	  pedwarn (loc, 0, "parameter %q+D declared %<_Noreturn%>", decl);
      }
    இல்லையெனில் எனில் (decl_context == FIELD)
      {
	/* Note that the grammar rejects storage classes in typenames
	   and fields.  */
	gcc_assert (storage_class == csc_none && !threadp
		    && !declspecs->inline_p && !declspecs->noreturn_p);

	/* Structure field.  It may not be a function.  */

	எனில் (மரம்_CODE (type) == FUNCTION_TYPE)
	  {
	    error_at (loc, "field %qE declared as a function", name);
	    type = c_build_pointer_type (type);
	  }
	இல்லையெனில் எனில் (மரம்_CODE (type) != ERROR_MARK
		 && !COMPLETE_OR_UNBOUND_ARRAY_TYPE_P (type))
	  {
	    எனில் (name)
	      error_at (loc, "field %qE has incomplete type", name);
	    இல்லையெனில்
	      error_at (loc, "unnamed field has incomplete type");
	    type = error_mark_முனை;
	  }
	இல்லையெனில் எனில் (மரம்_CODE (type) == ARRAY_TYPE
		 && TYPE_DOMAIN (type) == NULL_மரம்)
	  {
	    /* We have a flexible array member through a typedef.
	       Set suitable range.  Whether this is a correct position
	       for a flexible array member will be determined elsewhere.  */
	    எனில் (!in_system_header_at (உள்ளீடு_location))
	      pedwarn_c90 (loc, OPT_Wpedantic, "ISO C90 does not "
			   "support flexible array members");
	    type = build_distinct_type_copy (TYPE_MAIN_VARIANT (type));
	    TYPE_DOMAIN (type) = build_index_type (NULL_மரம்);
	    எனில் (orig_qual_indirect == 0)
	      orig_qual_type = NULL_மரம்;
	  }
	எனில் (type != error_mark_முனை
	    && !verify_type_context (loc, TCTX_FIELD, type))
	  type = error_mark_முனை;

	type = c_build_qualified_type (type, type_quals, orig_qual_type,
				       orig_qual_indirect);
	decl = build_decl (declarator->id_loc,
			   FIELD_DECL, declarator->u.id.id, type);
	DECL_NONADDRESSABLE_P (decl) = bitfield;
	எனில் (bitfield && !declarator->u.id.id)
	  DECL_PADDING_P (decl) = 1;

	எனில் (size_varies)
	  C_DECL_VARIABLE_SIZE (decl) = 1;
      }
    இல்லையெனில் எனில் (மரம்_CODE (type) == FUNCTION_TYPE)
      {
	எனில் (storage_class == csc_register || threadp || constexprp)
	  {
	    error_at (loc, "invalid storage class for function %qE", name);
	  }
	இல்லையெனில் எனில் (current_scope != file_scope)
	  {
	    /* Function declaration not at file scope.  Storage
	       classes other than `extern' are not allowed, C99
	       6.7.1p5, and `extern' makes no difference.  However,
	       GCC allows 'auto', perhaps with 'inline', to support
	       nested functions.  */
	    எனில் (storage_class == csc_auto)
		pedwarn (loc, OPT_Wpedantic,
			 "invalid storage class for function %qE", name);
	    இல்லையெனில் எனில் (storage_class == csc_static)
	      {
		error_at (loc, "invalid storage class for function %qE", name);
		எனில் (funcdef_flag)
		  storage_class = declspecs->storage_class = csc_none;
		இல்லையெனில்
		  திரும்பு NULL_மரம்;
	      }
	  }

	decl = build_decl (declarator->id_loc,
			   FUNCTION_DECL, declarator->u.id.id, type);
	decl = build_decl_attribute_variant (decl, decl_attr);

	எனில் (type_quals & TYPE_QUAL_ATOMIC)
	  {
	    error_at (loc,
		      "%<_Atomic%>-qualified function type");
	    type_quals &= ~TYPE_QUAL_ATOMIC;
	  }
	இல்லையெனில் எனில் (pedantic && type_quals && !DECL_IN_SYSTEM_HEADER (decl))
	  pedwarn (loc, OPT_Wpedantic,
		   "ISO C forbids qualified function types");

	/* Every function declaration is an external reference
	   (DECL_EXTERNAL) except for those which are not at file
	   scope and are explicitly declared "auto".  This is
	   forbidden by standard C (C99 6.7.1p5) and is interpreted by
	   GCC to signify a forward declaration of a nested function.  */
	எனில் (storage_class == csc_auto && current_scope != file_scope)
	  DECL_EXTERNAL (decl) = 0;
	/* In C99, a function which is declared 'inline' with 'extern'
	   is not an external reference (which is confusing).  It
	   means that the later definition of the function must be output
	   in this file, C99 6.7.4p6.  In GNU C89, a function declared
	   'extern inline' is an external reference.  */
	இல்லையெனில் எனில் (declspecs->inline_p && storage_class != csc_static)
	  DECL_EXTERNAL (decl) = ((storage_class == csc_extern)
				  == flag_gnu89_inline);
	இல்லையெனில்
	  DECL_EXTERNAL (decl) = !initialized;

	/* Record absence of global scope for `static' or `auto'.  */
	மரம்_PUBLIC (decl)
	  = !(storage_class == csc_static || storage_class == csc_auto);

	/* For a function definition, record the argument information
	   block where store_parm_decls will look for it.  */
	எனில் (funcdef_flag)
	  current_function_arg_info = arg_info;

	எனில் (declspecs->default_int_p)
	  C_FUNCTION_IMPLICIT_INT (decl) = 1;

	/* Record presence of `inline' and `_Noreturn', if it is
	   reasonable.  */
	எனில் (flag_hosted && MAIN_NAME_P (declarator->u.id.id))
	  {
	    எனில் (declspecs->inline_p)
	      pedwarn (loc, 0, "cannot inline function %<main%>");
	    எனில் (declspecs->noreturn_p)
	      pedwarn (loc, 0, "%<main%> declared %<_Noreturn%>");
	  }
	இல்லையெனில்
	  {
	    எனில் (declspecs->inline_p)
	      /* Record that the function is declared `inline'.  */
	      DECL_DECLARED_INLINE_P (decl) = 1;
	    எனில் (declspecs->noreturn_p)
	      {
		எனில் (flag_isoc99)
		  pedwarn_c99 (loc, OPT_Wpedantic,
			       "ISO C99 does not support %<_Noreturn%>");
		இல்லையெனில்
		  pedwarn_c99 (loc, OPT_Wpedantic,
			       "ISO C90 does not support %<_Noreturn%>");
		மரம்_THIS_VOLATILE (decl) = 1;
	      }
	  }

	/* C99 6.2.2p7: It is invalid (compile-time undefined
	   behavior) to create an 'extern' declaration for a
	   function if there is a global declaration that is
	   'static' and the global declaration is not visible.
	   (If the static declaration _is_ currently visible,
	   the 'extern' declaration is taken to refer to that decl.) */
	எனில் (!initialized
	    && மரம்_PUBLIC (decl)
	    && current_scope != file_scope)
	  {
	    மரம் global_decl  = identifier_global_மதிப்பு (declarator->u.id.id);
	    மரம் visible_decl = lookup_name (declarator->u.id.id);

	    எனில் (global_decl
		&& global_decl != visible_decl
		&& VAR_OR_FUNCTION_DECL_P (global_decl)
		&& !மரம்_PUBLIC (global_decl))
	      error_at (loc, "function previously declared %<static%> "
			"redeclared %<extern%>");
	  }
      }
    இல்லையெனில்
      {
	/* It's a variable.  */
	/* An uninitialized decl with `extern' is a reference.  */
	முழு extern_ref = !initialized && storage_class == csc_extern;

	எனில் (constexprp)
	  {
	    /* The type of a constexpr variable must not be variably
	       modified, volatile, atomic or restrict qualified or
	       have a member with such a qualifier.  const
	       qualification is implicitly added, and, at file scope,
	       has internal linkage.  */
	    எனில் (c_type_variably_modified_p (type))
	      error_at (loc, "%<constexpr%> object has variably modified "
			"type");
	    எனில் (type_quals
		& (TYPE_QUAL_VOLATILE | TYPE_QUAL_RESTRICT | TYPE_QUAL_ATOMIC))
	      error_at (loc, "invalid qualifiers for %<constexpr%> object");
	    இல்லையெனில்
	      {
		மரம் type_no_array = strip_array_types (type);
		எனில் (RECORD_OR_UNION_TYPE_P (type_no_array)
		    && C_TYPE_FIELDS_NON_CONSTEXPR (type_no_array))
		  error_at (loc, "invalid qualifiers for field of "
			    "%<constexpr%> object");
	      }
	    type_quals |= TYPE_QUAL_CONST;
	    எனில் (current_scope == file_scope)
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
	எனில் (extern_ref && current_scope != file_scope)
	  {
	    மரம் global_decl  = identifier_global_மதிப்பு (declarator->u.id.id);
	    மரம் visible_decl = lookup_name (declarator->u.id.id);

	    எனில் (global_decl
		&& global_decl != visible_decl
		&& VAR_P (global_decl)
		&& !மரம்_PUBLIC (global_decl))
	      error_at (loc, "variable previously declared %<static%> "
			"redeclared %<extern%>");
	  }

	decl = build_decl (declarator->id_loc,
			   VAR_DECL, declarator->u.id.id, type);
	எனில் (size_varies)
	  C_DECL_VARIABLE_SIZE (decl) = 1;
	எனில் (constexprp)
	  C_DECL_DECLARED_CONSTEXPR (decl) = 1;

	எனில் (declspecs->inline_p)
	  pedwarn (loc, 0, "variable %q+D declared %<inline%>", decl);
	எனில் (declspecs->noreturn_p)
	  pedwarn (loc, 0, "variable %q+D declared %<_Noreturn%>", decl);

	/* At file scope, an initialized extern declaration may follow
	   a static declaration.  In that case, DECL_EXTERNAL will be
	   reset later in start_decl.  */
	DECL_EXTERNAL (decl) = (storage_class == csc_extern);

	/* At file scope, the presence of a `static' or `register' storage
	   class specifier, or the absence of all storage class specifiers
	   makes this declaration a definition (perhaps tentative).  Also,
	   the absence of `static' makes it public.  */
	எனில் (current_scope == file_scope)
	  {
	    மரம்_PUBLIC (decl) = storage_class != csc_static;
	    மரம்_STATIC (decl) = !extern_ref;
	  }
	/* Not at file scope, only `static' makes a static definition.  */
	இல்லையெனில்
	  {
	    மரம்_STATIC (decl) = (storage_class == csc_static);
	    மரம்_PUBLIC (decl) = extern_ref;
	  }

	// NB: Set a tentative TLS model to avoid tls_model attribute
	// warnings due to lack of thread storage duration.  It will
	// be updated by c_decl_attributes later.
	எனில் (threadp)
	  set_decl_tls_model (decl, TLS_MODEL_REAL);
      }

    எனில் ((storage_class == csc_extern
	 || (storage_class == csc_none
	     && மரம்_CODE (type) == FUNCTION_TYPE
	     && !funcdef_flag))
	&& c_type_variably_modified_p (type))
      {
	/* C99 6.7.5.2p2 */
	எனில் (மரம்_CODE (type) == FUNCTION_TYPE)
	  error_at (loc, "non-nested function with variably modified type");
	இல்லையெனில்
	  error_at (loc, "object with variably modified type must have "
	      	    "no linkage");
      }

    /* For nested functions disqualify ones taking VLAs by value
       from inlining since the middle-end cannot deal with this.
       ???  We should arrange for those to be passed by reference
       with emitting the copy on the caller side in the frontend.  */
    எனில் (storage_class == csc_none
	&& மரம்_CODE (type) == FUNCTION_TYPE)
      க்கு (மரம் al = TYPE_ARG_TYPES (type); al; al = மரம்_CHAIN (al))
	{
	  மரம் arg = மரம்_மதிப்பு (al);
	  எனில் (arg != error_mark_முனை
	      && C_TYPE_VARIABLE_SIZE (arg))
	    {
	      DECL_UNINLINABLE (decl) = 1;
	      நிறுத்து;
	    }
	}

    /* Record `register' declaration for warnings on &
       and in case doing stupid register allocation.  */

    எனில் (storage_class == csc_register
	&& மரம்_CODE (type) != FUNCTION_TYPE)
      {
	C_DECL_REGISTER (decl) = 1;
	DECL_REGISTER (decl) = 1;
      }

    /* Record constancy and volatility.  */
    c_apply_type_quals_to_decl (type_quals, decl);

    /* Apply _Alignas specifiers.  */
    எனில் (alignas_align)
      {
	SET_DECL_ALIGN (decl, alignas_align * BITS_PER_UNIT);
	DECL_USER_ALIGN (decl) = 1;
      }

    /* If a type has volatile components, it should be stored in memory.
       Otherwise, the fact that those components are volatile
       will be ignored, and would even crash the compiler.
       Of course, this only makes sense on  VAR,PARM, and RESULT decl's.   */
    எனில் (C_TYPE_FIELDS_VOLATILE (மரம்_TYPE (decl))
	&& (VAR_P (decl) ||  மரம்_CODE (decl) == PARM_DECL
	  || மரம்_CODE (decl) == RESULT_DECL))
      {
	/* It is not an error for a structure with volatile fields to
	   be declared register, but reset DECL_REGISTER since it
	   cannot actually go in a register.  */
	முழு was_reg = C_DECL_REGISTER (decl);
	C_DECL_REGISTER (decl) = 0;
	DECL_REGISTER (decl) = 0;
	c_mark_addressable (decl);
	C_DECL_REGISTER (decl) = was_reg;
      }

  /* This is the earliest point at which we might know the assembler
     name of a variable.  Thus, if it's known before this, die horribly.  */
    gcc_assert (!HAS_DECL_ASSEMBLER_NAME_P (decl)
		|| !DECL_ASSEMBLER_NAME_SET_P (decl));

    எனில் (warn_cxx_compat
	&& VAR_P (decl)
	&& மரம்_PUBLIC (decl)
	&& மரம்_STATIC (decl)
	&& (RECORD_OR_UNION_TYPE_P (மரம்_TYPE (decl))
	    || மரம்_CODE (மரம்_TYPE (decl)) == ENUMERAL_TYPE)
	&& TYPE_NAME (மரம்_TYPE (decl)) == NULL_மரம்)
      warning_at (DECL_SOURCE_LOCATION (decl), OPT_Wc___compat,
		  "non-local variable %qD with anonymous type is "
		  "questionable in C++", decl);

    திரும்பு decl;
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

நிலையான மரம்
grokparms (கட்டமைப்பு c_arg_info *arg_info, தருக்க funcdef_flag)
{
  மரம் arg_types = arg_info->types;

  எனில் (funcdef_flag && arg_info->had_vla_unspec)
    {
      /* A function definition isn't function prototype scope C99 6.2.1p4.  */
      /* C99 6.7.5.2p4 */
      error ("%<[*]%> not allowed in other than function prototype scope");
    }

  எனில் (arg_types == NULL_மரம் && !funcdef_flag && !flag_isoc23
      && !in_system_header_at (உள்ளீடு_location))
    warning (OPT_Wstrict_prototypes,
	     "function declaration isn%'t a prototype");

  எனில் (arg_types == error_mark_முனை)
    /* Don't set TYPE_ARG_TYPES in this case.  */
    திரும்பு NULL_மரம்;

  இல்லையெனில் எனில் (arg_types && மரம்_CODE (மரம்_மதிப்பு (arg_types)) == IDENTIFIER_முனை)
    {
      எனில் (!funcdef_flag)
	{
	  permerror_opt (உள்ளீடு_location,
			 OPT_Wdeclaration_missing_parameter_type,
			 "parameter names (without types) in "
			 "function declaration");
	  arg_info->parms = NULL_மரம்;
	}
      இல்லையெனில்
	arg_info->parms = arg_info->types;

      arg_info->types = NULL_மரம்;
      திரும்பு NULL_மரம்;
    }
  இல்லையெனில்
    {
      மரம் parm, type, typelt;
      unsigned முழு parmno;

      /* In C23, convert () to (void).  */
      எனில் (flag_isoc23
	  && !arg_types
	  && !arg_info->parms
	  && !arg_info->no_named_args_stdarg_p)
	{
	  arg_types = arg_info->types = void_list_முனை;
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

      க்கு (parm = arg_info->parms, typelt = arg_types, parmno = 1;
	   parm;
	   parm = DECL_CHAIN (parm), typelt = மரம்_CHAIN (typelt), parmno++)
	{
	  type = மரம்_மதிப்பு (typelt);
	  எனில் (type == error_mark_முனை)
	    தொடர்;

	  எனில் (!COMPLETE_TYPE_P (type))
	    {
	      எனில் (funcdef_flag)
		{
		  எனில் (DECL_NAME (parm))
		    error_at (உள்ளீடு_location,
			      "parameter %u (%q+D) has incomplete type",
			      parmno, parm);
		  இல்லையெனில்
		    error_at (DECL_SOURCE_LOCATION (parm),
			      "parameter %u has incomplete type",
			      parmno);

		  மரம்_மதிப்பு (typelt) = error_mark_முனை;
		  மரம்_TYPE (parm) = error_mark_முனை;
		  arg_types = NULL_மரம்;
		}
	    }

	  எனில் (DECL_NAME (parm) && மரம்_USED (parm))
	    warn_if_shadowing (parm);
	}
      திரும்பு arg_types;
    }
}

/* Allocate and initialize a c_arg_info structure from the parser's
   obstack.  */

கட்டமைப்பு c_arg_info *
build_arg_info (வெறுமை)
{
  கட்டமைப்பு c_arg_info *ret = XOBNEW (&parser_obstack, கட்டமைப்பு c_arg_info);
  ret->parms = NULL_மரம்;
  ret->tags = வெற்று;
  ret->types = NULL_மரம்;
  ret->others = NULL_மரம்;
  ret->pending_sizes = வெற்று;
  ret->had_vla_unspec = 0;
  ret->no_named_args_stdarg_p = 0;
  ret->c23_empty_parens = 0;
  திரும்பு ret;
}

/* Take apart the current scope and return a c_arg_info structure with
   info on a parameter list just parsed.

   This structure is later fed to 'grokparms' and 'store_parm_decls'.

   ELLIPSIS being true means the argument list ended in '...' so don't
   append a sentinel (void_list_node) to the end of the type-list.

   EXPR is NULL or an expression that needs to be evaluated for the
   side effects of array size expressions in the parameters.  */

கட்டமைப்பு c_arg_info *
get_parm_info (தருக்க ellipsis, மரம் கோவை)
{
  கட்டமைப்பு c_binding *b = current_scope->bindings;
  கட்டமைப்பு c_arg_info *arg_info = build_arg_info ();

  மரம் parms = NULL_மரம்;
  vec<c_arg_tag, va_gc> *tags = வெற்று;
  மரம் types = NULL_மரம்;
  மரம் others = NULL_மரம்;

  தருக்க gave_void_only_once_err = பொய்;

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
  எனில் (b->prev == 0			    /* one binding */
      && மரம்_CODE (b->decl) == PARM_DECL   /* which is a parameter */
      && !DECL_NAME (b->decl)               /* anonymous */
      && VOID_TYPE_P (மரம்_TYPE (b->decl))) /* of void type */
    {
      எனில் (TYPE_QUALS (மரம்_TYPE (b->decl)) != TYPE_UNQUALIFIED
	  || C_DECL_REGISTER (b->decl))
	error_at (b->locus, "%<void%> as only parameter may not be qualified");

      /* There cannot be an ellipsis.  */
      எனில் (ellipsis)
	error_at (b->locus, "%<void%> must be the only parameter");

      arg_info->types = void_list_முனை;
      திரும்பு arg_info;
    }

  எனில் (!ellipsis)
    types = void_list_முனை;

  /* Break up the bindings list into parms, tags, types, and others;
     apply sanity checks; purge the name-to-decl bindings.  */
  போது (b)
    {
      மரம் decl = b->decl;
      மரம் type = மரம்_TYPE (decl);
      c_arg_tag tag;
      மாறிலி எழுத்து *keyword;

      தேர்வு (மரம்_CODE (decl))
	{
	நிலை PARM_DECL:
	  எனில் (b->id)
	    {
	      gcc_assert (I_குறியீடு_BINDING (b->id) == b);
	      I_குறியீடு_BINDING (b->id) = b->shadowed;
	    }

	  /* Check for forward decls that never got their actual decl.  */
	  எனில் (மரம்_ASM_WRITTEN (decl))
	    error_at (b->locus,
		      "parameter %q+D has just a forward declaration", decl);
	  /* Check for (..., void, ...) and named void parameters and issue an
	     error.  */
	  இல்லையெனில் எனில் (VOID_TYPE_P (type))
	    {
	      எனில் (!gave_void_only_once_err)
		{
		  error_at (b->locus,
			    "%<void%> must be the only parameter and unnamed");
		  gave_void_only_once_err = உண்மை;
		}
	    }
	  இல்லையெனில்
	    {
	      /* Valid parameter, add it to the list.  */
	      DECL_CHAIN (decl) = parms;
	      parms = decl;

	      /* Since there is a prototype, args are passed in their
		 declared types.  The back end may override this later.  */
	      DECL_ARG_TYPE (decl) = type;
	      types = மரம்_cons (0, type, types);
	    }
	  நிறுத்து;

	நிலை ENUMERAL_TYPE: keyword = "enum"; செல் tag;
	நிலை UNION_TYPE:    keyword = "union"; செல் tag;
	நிலை RECORD_TYPE:   keyword = "struct"; செல் tag;
	tag:
	  /* Types may not have tag-names, in which case the type
	     appears in the bindings list with b->id NULL.  */
	  எனில் (b->id)
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
	  எனில் (மரம்_CODE (decl) != UNION_TYPE || b->id != NULL_மரம்)
	    {
	      எனில் (b->id)
		{
		  /* The %s will be one of 'struct', 'union', or 'enum'.  */
		  எனில் (!flag_isoc23 || !COMPLETE_TYPE_P (decl))
		    warning_at (b->locus, 0,
				"%<%s %E%> declared inside parameter list"
				" will not be visible outside of this definition or"
				" declaration", keyword, b->id);
		}
	      இல்லையெனில்
		/* The %s will be one of 'struct', 'union', or 'enum'.  */
		warning_at (b->locus, 0,
			    "anonymous %s declared inside parameter list"
			    " will not be visible outside of this definition or"
			    " declaration", keyword);
	    }

	  tag.id = b->id;
	  tag.type = decl;
	  vec_safe_தள்ளு (tags, tag);
	  நிறுத்து;

	நிலை FUNCTION_DECL:
	  /* FUNCTION_DECLs appear when there is an implicit function
	     declaration in the parameter list.  */
	  gcc_assert (b->nested || seen_error ());
	  செல் set_shadowed;

	நிலை CONST_DECL:
	நிலை TYPE_DECL:
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

	நிலை ERROR_MARK:
	set_shadowed:
	  /* error_mark_node appears here when we have an undeclared
	     variable.  Just throw it away.  */
	  எனில் (b->id)
	    {
	      gcc_assert (I_குறியீடு_BINDING (b->id) == b);
	      I_குறியீடு_BINDING (b->id) = b->shadowed;
	    }
	  நிறுத்து;

	  /* Other things that might be encountered.  */
	நிலை LABEL_DECL:
	நிலை VAR_DECL:
	இயல்பு:
	  gcc_unreachable ();
	}

      b = free_binding_and_advance (b);
    }

  arg_info->parms = parms;
  arg_info->tags = tags;
  arg_info->types = types;
  arg_info->others = others;
  arg_info->pending_sizes = கோவை;
  arg_info->no_named_args_stdarg_p = ellipsis && !types;
  திரும்பு arg_info;
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

கட்டமைப்பு c_typespec
parser_xref_tag (location_t loc, எண்ணிக்கை மரம்_code code, மரம் name,
		 தருக்க have_std_attrs, மரம் attrs, தருக்க has_enum_type_specifier)
{
  கட்டமைப்பு c_typespec ret;
  மரம் ref;
  location_t refloc;

  ret.கோவை = NULL_மரம்;
  ret.கோவை_const_operands = உண்மை;
  ret.has_enum_type_specifier = has_enum_type_specifier;

  /* If a cross reference is requested, look up the type already
     defined for this tag and return it.  If an enum type specifier is
     present, only a definition in the current scope is relevant.  */

  ref = lookup_tag (code, name, has_enum_type_specifier, &refloc);

  /* If the visible type is still being defined, see if there is
     an earlier definition (which may be complete).  We do not
     have to loop because nested redefinitions are not allowed.  */
  எனில் (flag_isoc23 && ref && C_TYPE_BEING_DEFINED (ref))
    {
      மரம் vis = previous_tag (ref);
      எனில் (vis)
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
  எனில் (ref && மரம்_CODE (ref) == code)
    {
      decl_attributes (&ref, attrs, (முழு) ATTR_FLAG_TYPE_IN_PLACE);
      எனில் (C_TYPE_DEFINED_IN_STRUCT (ref)
	  && loc != UNKNOWN_LOCATION
	  && warn_cxx_compat)
	{
	  auto_diagnostic_group d;
	  தேர்வு (code)
	    {
	    நிலை ENUMERAL_TYPE:
	      எனில் (warning_at (loc, OPT_Wc___compat,
			      ("enum type defined in struct or union "
			       "is not visible in C++")))
		  inform (refloc, "enum type defined here");
	      நிறுத்து;
	    நிலை RECORD_TYPE:
	      எனில் (warning_at (loc, OPT_Wc___compat,
			      ("struct defined in struct or union "
			       "is not visible in C++")))
		inform (refloc, "struct defined here");
	      நிறுத்து;
	    நிலை UNION_TYPE:
	      எனில் (warning_at (loc, OPT_Wc___compat,
			      ("union defined in struct or union "
			       "is not visible in C++")))
		inform (refloc, "union defined here");
	      நிறுத்து;
	    இயல்பு:
	      gcc_unreachable();
	    }
	}

      ret.spec = ref;
      திரும்பு ret;
    }

  /* If no such tag is yet defined, create a forward-reference node
     and record it as the "definition".
     When a real declaration of this type is found,
     the forward-reference will be altered into a real type.  */

  ref = make_முனை (code);
  எனில் (flag_isoc23 || code == ENUMERAL_TYPE)
    SET_TYPE_STRUCTURAL_EQUALITY (ref);
  எனில் (code == ENUMERAL_TYPE)
    {
      /* Give the type a default layout like unsigned int
	 to avoid crashing if it does not get defined.  */
      SET_TYPE_MODE (ref, TYPE_MODE (unsigned_type_முனை));
      SET_TYPE_ALIGN (ref, TYPE_ALIGN (unsigned_type_முனை));
      TYPE_USER_ALIGN (ref) = 0;
      TYPE_UNSIGNED (ref) = 1;
      TYPE_PRECISION (ref) = TYPE_PRECISION (unsigned_type_முனை);
      TYPE_MIN_மதிப்பு (ref) = TYPE_MIN_மதிப்பு (unsigned_type_முனை);
      TYPE_MAX_மதிப்பு (ref) = TYPE_MAX_மதிப்பு (unsigned_type_முனை);
      ENUM_FIXED_UNDERLYING_TYPE_P (ref) = has_enum_type_specifier;
    }

  pushtag (loc, name, ref);
  decl_attributes (&ref, attrs, (முழு) ATTR_FLAG_TYPE_IN_PLACE);
  எனில் (in_underspecified_init)
    error_at (loc, "%qT declared in underspecified object initializer",
	      ref);

  ret.spec = ref;
  திரும்பு ret;
}

/* Get the struct, enum or union (CODE says which) with tag NAME.
   Define the tag as a forward-reference if it is not defined.
   Return a tree for the type.  */

மரம்
xref_tag (எண்ணிக்கை மரம்_code code, மரம் name)
{
  திரும்பு parser_xref_tag (உள்ளீடு_location, code, name, பொய், NULL_மரம்,
			  பொய்).spec;
}

/* Make sure that the tag NAME is defined *in the current scope*
   at least as a forward reference.
   LOC is the location of the struct's definition.
   CODE says which kind of tag NAME ought to be.

   This stores the current value of the file static STRUCT_PARSE_INFO
   in *ENCLOSING_STRUCT_PARSE_INFO, and points STRUCT_PARSE_INFO at a
   new c_struct_parse_info structure.  The old value of
   STRUCT_PARSE_INFO is restored in finish_struct.  */

மரம்
start_struct (location_t loc, எண்ணிக்கை மரம்_code code, மரம் name,
	      வகுப்பு c_struct_parse_info **enclosing_struct_parse_info)
{
  /* If there is already a tag defined at this scope
     (as a forward reference), just return it.  */

  மரம் ref = NULL_மரம்;
  location_t refloc = UNKNOWN_LOCATION;

  எனில் (name != NULL_மரம்)
    ref = lookup_tag (code, name, உண்மை, &refloc);

  /* For C23, even if we already have a completed definition,
     we do not use it. We will check for consistency later.
     If we are in a nested redefinition the type is not
     complete. We will then detect this below.  */
  எனில் (flag_isoc23 && ref && TYPE_SIZE (ref))
    ref = NULL_மரம்;

  எனில் (ref && மரம்_CODE (ref) == code)
    {
      எனில் (TYPE_STUB_DECL (ref))
	refloc = DECL_SOURCE_LOCATION (TYPE_STUB_DECL (ref));

      எனில் (TYPE_SIZE (ref))
	{
	  auto_diagnostic_group d;
	  எனில் (code == UNION_TYPE)
	    error_at (loc, "redefinition of %<union %E%>", name);
	  இல்லையெனில்
	    error_at (loc, "redefinition of %<struct %E%>", name);
	  எனில் (refloc != UNKNOWN_LOCATION)
	    inform (refloc, "originally defined here");
	  /* Don't create structures using a name already in use.  */
	  ref = NULL_மரம்;
	}
      இல்லையெனில் எனில் (C_TYPE_BEING_DEFINED (ref))
	{
	  எனில் (code == UNION_TYPE)
	    error_at (loc, "nested redefinition of %<union %E%>", name);
	  இல்லையெனில்
	    error_at (loc, "nested redefinition of %<struct %E%>", name);
	  /* Don't bother to report "originally defined here" for a
	     nested redefinition; the original definition should be
	     obvious.  */
	  /* Don't create structures that contain themselves.  */
	  ref = NULL_மரம்;
	}
    }

  /* Otherwise create a forward-reference just so the tag is in scope.  */

  எனில் (ref == NULL_மரம் || மரம்_CODE (ref) != code)
    {
      ref = make_முனை (code);
      எனில் (flag_isoc23)
	SET_TYPE_STRUCTURAL_EQUALITY (ref);
      pushtag (loc, name, ref);
    }

  C_TYPE_BEING_DEFINED (ref) = 1;
  க்கு (மரம் v = TYPE_MAIN_VARIANT (ref); v; v = TYPE_NEXT_VARIANT (v))
    TYPE_PACKED (v) = flag_pack_struct;

  *enclosing_struct_parse_info = struct_parse_info;
  struct_parse_info = புதிய c_struct_parse_info ();
  struct_parse_info->refloc = refloc;

  /* FIXME: This will issue a warning for a use of a type defined
     within a statement expr used within sizeof, et. al.  This is not
     terribly serious as C++ doesn't permit statement exprs within
     sizeof anyhow.  */
  எனில் (warn_cxx_compat
      && (in_sizeof || in_typeof || in_alignof || in_countof))
    warning_at (loc, OPT_Wc___compat,
		"defining type in %qs expression is invalid in C++",
		(in_sizeof ? "sizeof"
		 : in_typeof ? "typeof"
		 : in_alignof ? "alignof"
		 : "_Countof"));

  எனில் (in_underspecified_init)
    error_at (loc, "%qT defined in underspecified object initializer", ref);

  திரும்பு ref;
}

/* Process the specs, declarator and width (NULL if omitted)
   of a structure component, returning a FIELD_DECL node.
   WIDTH is non-NULL for bit-fields only, and is an INTEGER_CST node.
   DECL_ATTRS is as for grokdeclarator.

   LOC is the location of the structure component.

   This is done during the parsing of the struct declaration.
   The FIELD_DECL nodes are chained together and the lot of them
   are ultimately passed to `build_struct' to make the RECORD_TYPE node.  */

மரம்
grokfield (location_t loc,
	   கட்டமைப்பு c_declarator *declarator, கட்டமைப்பு c_declspecs *declspecs,
	   மரம் width, மரம் *decl_attrs, மரம் *கோவை)
{
  மரம் மதிப்பு;

  எனில் (declarator->kind == cdk_id && declarator->u.id.id == NULL_மரம்
      && width == NULL_மரம்)
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

      மரம் type = declspecs->type;
      தருக்க ok = பொய்;

      எனில் (RECORD_OR_UNION_TYPE_P (type)
	  && (flag_ms_extensions
	      || flag_plan9_extensions
	      || !declspecs->typedef_p))
	{
	  எனில் (flag_ms_extensions || flag_plan9_extensions)
	    ok = உண்மை;
	  இல்லையெனில் எனில் (TYPE_NAME (type) == வெற்று)
	    ok = உண்மை;
	  இல்லையெனில்
	    ok = பொய்;
	}
      எனில் (!ok)
	{
	  pedwarn (loc, 0, "declaration does not declare anything");
	  திரும்பு NULL_மரம்;
	}
      எனில் (flag_isoc99)
	pedwarn_c99 (loc, OPT_Wpedantic,
		     "ISO C99 doesn%'t support unnamed structs/unions");
      இல்லையெனில்
	pedwarn_c99 (loc, OPT_Wpedantic,
		     "ISO C90 doesn%'t support unnamed structs/unions");
    }

  மதிப்பு = grokdeclarator (declarator, declspecs, FIELD, பொய்,
			  width ? &width : வெற்று, decl_attrs, கோவை, வெற்று,
			  DEPRECATED_NORMAL);

  /* When this field has name, its type is a top level type, we should
     call verify_counted_by_for_top_anonymous_type.  */
  எனில் (DECL_NAME (மதிப்பு) != NULL_மரம்
      && declspecs->typespec_kind == ctsk_tagdef)
    verify_counted_by_for_உச்சி_anonymous_type (declspecs->type);

  finish_decl (மதிப்பு, loc, NULL_மரம், NULL_மரம், NULL_மரம்);
  DECL_INITIAL (மதிப்பு) = width;
  எனில் (width)
    SET_DECL_C_BIT_FIELD (மதிப்பு);

  எனில் (warn_cxx_compat && DECL_NAME (மதிப்பு) != NULL_மரம்)
    {
      /* If we currently have a binding for this field, set the
	 in_struct field in the binding, so that we warn about lookups
	 which find it.  */
      கட்டமைப்பு c_binding *b = I_குறியீடு_BINDING (DECL_NAME (மதிப்பு));
      எனில் (b != வெற்று)
	{
	  /* If the in_struct field is not yet set, push it on a list
	     to be cleared when this struct is finished.  */
	  எனில் (!b->in_struct)
	    {
	      struct_parse_info->fields.safe_தள்ளு (b);
	      b->in_struct = 1;
	    }
	}
    }

  திரும்பு மதிப்பு;
}

/* Subroutine of detect_field_duplicates: return whether X and Y,
   which are both fields in the same struct, have duplicate field
   names.  */

நிலையான தருக்க
is_duplicate_field (மரம் x, மரம் y)
{
  எனில் (DECL_NAME (x) != NULL_மரம் && DECL_NAME (x) == DECL_NAME (y))
    திரும்பு உண்மை;

  /* When using -fplan9-extensions, an anonymous field whose name is a
     typedef can duplicate a field name.  */
  எனில் (flag_plan9_extensions
      && (DECL_NAME (x) == NULL_மரம் || DECL_NAME (y) == NULL_மரம்))
    {
      மரம் xt, xn, yt, yn;

      xt = மரம்_TYPE (x);
      எனில் (DECL_NAME (x) != NULL_மரம்)
	xn = DECL_NAME (x);
      இல்லையெனில் எனில் (RECORD_OR_UNION_TYPE_P (xt)
	       && TYPE_NAME (xt) != NULL_மரம்
	       && மரம்_CODE (TYPE_NAME (xt)) == TYPE_DECL)
	xn = DECL_NAME (TYPE_NAME (xt));
      இல்லையெனில்
	xn = NULL_மரம்;

      yt = மரம்_TYPE (y);
      எனில் (DECL_NAME (y) != NULL_மரம்)
	yn = DECL_NAME (y);
      இல்லையெனில் எனில் (RECORD_OR_UNION_TYPE_P (yt)
	       && TYPE_NAME (yt) != NULL_மரம்
	       && மரம்_CODE (TYPE_NAME (yt)) == TYPE_DECL)
	yn = DECL_NAME (TYPE_NAME (yt));
      இல்லையெனில்
	yn = NULL_மரம்;

      எனில் (xn != NULL_மரம் && xn == yn)
	திரும்பு உண்மை;
    }

  திரும்பு பொய்;
}

/* Subroutine of detect_field_duplicates: add the fields of FIELDLIST
   to HTAB, giving errors for any duplicates.  */

நிலையான வெறுமை
detect_field_duplicates_hash (மரம் fieldlist,
			      hash_table<nofree_ptr_hash <மர_முனை> > *htab)
{
  மரம் x, y;
  மர_முனை **slot;

  க்கு (x = fieldlist; x ; x = DECL_CHAIN (x))
    எனில் ((y = DECL_NAME (x)) != NULL_மரம்)
      {
	slot = htab->find_slot (y, செருகு);
	எனில் (*slot)
	  {
	    error ("duplicate member %q+D", x);
	    DECL_NAME (x) = NULL_மரம்;
	  }
	*slot = y;
      }
    இல்லையெனில் எனில் (RECORD_OR_UNION_TYPE_P (மரம்_TYPE (x)))
      {
	detect_field_duplicates_hash (TYPE_FIELDS (மரம்_TYPE (x)), htab);

	/* When using -fplan9-extensions, an anonymous field whose
	   name is a typedef can duplicate a field name.  */
	எனில் (flag_plan9_extensions
	    && TYPE_NAME (மரம்_TYPE (x)) != NULL_மரம்
	    && மரம்_CODE (TYPE_NAME (மரம்_TYPE (x))) == TYPE_DECL)
	  {
	    மரம் xn = DECL_NAME (TYPE_NAME (மரம்_TYPE (x)));
	    slot = htab->find_slot (xn, செருகு);
	    எனில் (*slot)
	      error ("duplicate member %q+D", TYPE_NAME (மரம்_TYPE (x)));
	    *slot = xn;
	  }
      }
}

/* Generate an error for any duplicate field names in FIELDLIST.  Munge
   the list such that this does not present a problem later.  */

நிலையான வெறுமை
detect_field_duplicates (மரம் fieldlist)
{
  மரம் x, y;
  முழு timeout = 10;

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
  எனில் (c_dialect_objc ())
    எனில் (objc_detect_field_duplicates (பொய்))
      திரும்பு;

  /* First, see if there are more than "a few" fields.
     This is trivially true if there are zero or one fields.  */
  எனில் (!fieldlist || !DECL_CHAIN (fieldlist))
    திரும்பு;
  x = fieldlist;
  செய் {
    timeout--;
    எனில் (DECL_NAME (x) == NULL_மரம்
	&& RECORD_OR_UNION_TYPE_P (மரம்_TYPE (x)))
      timeout = 0;
    x = DECL_CHAIN (x);
  } போது (timeout > 0 && x);

  /* If there were "few" fields and no anonymous structures or unions,
     avoid the overhead of allocating a hash table.  Instead just do
     the nested traversal thing.  */
  எனில் (timeout > 0)
    {
      க்கு (x = DECL_CHAIN (fieldlist); x; x = DECL_CHAIN (x))
	/* When using -fplan9-extensions, we can have duplicates
	   between typedef names and fields.  */
	எனில் (DECL_NAME (x)
	    || (flag_plan9_extensions
		&& DECL_NAME (x) == NULL_மரம்
		&& RECORD_OR_UNION_TYPE_P (மரம்_TYPE (x))
		&& TYPE_NAME (மரம்_TYPE (x)) != NULL_மரம்
		&& மரம்_CODE (TYPE_NAME (மரம்_TYPE (x))) == TYPE_DECL))
	  {
	    க்கு (y = fieldlist; y != x; y = மரம்_CHAIN (y))
	      எனில் (is_duplicate_field (y, x))
		{
		  error ("duplicate member %q+D", x);
		  DECL_NAME (x) = NULL_மரம்;
		}
	  }
    }
  இல்லையெனில்
    {
      hash_table<nofree_ptr_hash <மர_முனை> > htab (37);
      detect_field_duplicates_hash (fieldlist, &htab);
    }
}

/* Finish up struct info used by -Wc++-compat.  */

நிலையான வெறுமை
warn_cxx_compat_finish_struct (மரம் fieldlist, எண்ணிக்கை மரம்_code code,
			       location_t record_loc)
{
  unsigned முழு ix;
  மரம் x;
  கட்டமைப்பு c_binding *b;

  எனில் (fieldlist == NULL_மரம்)
    {
      எனில் (code == RECORD_TYPE)
	warning_at (record_loc, OPT_Wc___compat,
		    "empty struct has size 0 in C, size 1 in C++");
      இல்லையெனில்
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
  எனில் (!struct_parse_info->typedefs_seen.is_empty ()
      && fieldlist != NULL_மரம்)
    {
      /* Use a hash_set<tree> using the name of the typedef.  We can use
	 a hash_set<tree> because identifiers are interned.  */
      hash_set<மரம்> tset;

      FOR_EACH_VEC_ELT (struct_parse_info->typedefs_seen, ix, x)
	tset.add (DECL_NAME (x));

      க்கு (x = fieldlist; x != NULL_மரம்; x = DECL_CHAIN (x))
	{
	  எனில் (DECL_NAME (x) != NULL_மரம்
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

நிலையான முழு
field_decl_cmp (மாறிலி வெறுமை *x_p, மாறிலி வெறுமை *y_p)
{
  மாறிலி மரம் *மாறிலி x = (மாறிலி மரம் *) x_p;
  மாறிலி மரம் *மாறிலி y = (மாறிலி மரம் *) y_p;

  எனில் (DECL_NAME (*x) == DECL_NAME (*y))
    /* A nontype is "greater" than a type.  */
    திரும்பு (மரம்_CODE (*y) == TYPE_DECL) - (மரம்_CODE (*x) == TYPE_DECL);
  எனில் (DECL_NAME (*x) == NULL_மரம்)
    திரும்பு -1;
  எனில் (DECL_NAME (*y) == NULL_மரம்)
    திரும்பு 1;
  எனில் (DECL_NAME (*x) < DECL_NAME (*y))
    திரும்பு -1;
  திரும்பு 1;
}

/* If this structure or union completes the type of any previous
   variable declaration, lay it out and output its rtl.  */
நிலையான வெறுமை
finish_incomplete_vars (மரம் incomplete_vars, தருக்க toplevel)
{
  க்கு (மரம் x = incomplete_vars; x; x = மரம்_CHAIN (x))
    {
      மரம் decl = மரம்_மதிப்பு (x);
      எனில் (மரம்_CODE (மரம்_TYPE (decl)) == ARRAY_TYPE)
	layout_array_type (மரம்_TYPE (decl));
      எனில் (மரம்_CODE (decl) != TYPE_DECL)
	{
	  relayout_decl (decl);
	  எனில் (c_dialect_objc ())
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

நிலையான தருக்க
is_flexible_array_member_p (தருக்க is_last_field,
			    மரம் x)
{
  /* If not the last field, return false.  */
  எனில் (!is_last_field)
    திரும்பு பொய்;

  /* If not an array field, return false.  */
  எனில் (மரம்_CODE (மரம்_TYPE (x)) != ARRAY_TYPE)
    திரும்பு பொய்;

  தருக்க is_zero_length_array = zero_length_array_type_p (மரம்_TYPE (x));
  தருக்க is_one_element_array = one_element_array_type_p (மரம்_TYPE (x));
  தருக்க is_flexible_array = flexible_array_member_type_p (மரம்_TYPE (x));

  unsigned முழு strict_flex_array_level = c_strict_flex_array_level_of (x);

  தேர்வு (strict_flex_array_level)
    {
      நிலை 0:
	/* Default, all trailing arrays are flexible array members.  */
	திரும்பு உண்மை;
      நிலை 1:
	/* Level 1: all "[1]", "[0]", and "[]" are flexible array members.  */
	எனில் (is_one_element_array)
	  திரும்பு உண்மை;
	/* FALLTHROUGH.  */
      நிலை 2:
	/* Level 2: all "[0]", and "[]" are flexible array members.  */
	எனில் (is_zero_length_array)
	  திரும்பு உண்மை;
	/* FALLTHROUGH.  */
      நிலை 3:
	/* Level 3: Only "[]" are flexible array members.  */
	எனில் (is_flexible_array)
	  திரும்பு உண்மை;
	நிறுத்து;
      இயல்பு:
	gcc_unreachable ();
    }
  திரும்பு பொய்;
}

/* Recompute TYPE_CANONICAL for variants of the type including qualified
   versions of the type and related pointer types after an aggregate type
   has been finalized.
   Will not update array types, pointers to array types, function
   types and other derived types created while the type was still
   incomplete, those will remain TYPE_STRUCTURAL_EQUALITY_P.  */

நிலையான வெறுமை
c_update_type_canonical (மரம் t)
{
  gcc_checking_assert (TYPE_MAIN_VARIANT (t) == t && !TYPE_QUALS (t));
  க்கு (மரம் x = t, l = NULL_மரம்; x; l = x, x = TYPE_NEXT_VARIANT (x))
    {
      எனில் (x != t && TYPE_STRUCTURAL_EQUALITY_P (x))
	{
	  எனில் (!TYPE_QUALS (x))
	    TYPE_CANONICAL (x) = TYPE_CANONICAL (t);
	  இல்லையெனில்
	    {
	      மரம்
		c = c_build_qualified_type (TYPE_CANONICAL (t), TYPE_QUALS (x));
	      எனில் (TYPE_STRUCTURAL_EQUALITY_P (c))
		{
		  gcc_checking_assert (TYPE_CANONICAL (t) == t);
		  எனில் (c == x)
		    TYPE_CANONICAL (x) = x;
		  இல்லையெனில்
		    {
		      /* build_qualified_type for this function unhelpfully
			 moved c from some later spot in TYPE_MAIN_VARIANT (t)
			 chain to right after t (or created it there).  Move
			 it right before x and process c and then x.  */
		      gcc_checking_assert (TYPE_NEXT_VARIANT (t) == c);
		      எனில் (l != t)
			{
			  TYPE_NEXT_VARIANT (t) = TYPE_NEXT_VARIANT (c);
			  TYPE_NEXT_VARIANT (l) = c;
			  TYPE_NEXT_VARIANT (c) = x;
			}
		      TYPE_CANONICAL (c) = c;
		      x = c;
		    }
		}
	      இல்லையெனில்
		TYPE_CANONICAL (x) = TYPE_CANONICAL (c);
	    }
	}
      இல்லையெனில் எனில் (x != t)
	தொடர்;
      க்கு (மரம் p = TYPE_POINTER_TO (x); p; p = TYPE_NEXT_PTR_TO (p))
	{
	  எனில் (!TYPE_STRUCTURAL_EQUALITY_P (p))
	    தொடர்;
	  எனில் (TYPE_CANONICAL (x) != x || TYPE_REF_CAN_ALIAS_ALL (p))
	    TYPE_CANONICAL (p)
	      = c_build_pointer_type_for_mode (TYPE_CANONICAL (x), TYPE_MODE (p),
					       பொய்);
	  இல்லையெனில்
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

நிலையான வெறுமை
c_update_variably_modified (மரம் t)
{
  க்கு (மரம் x = t; x; x = TYPE_NEXT_VARIANT (x))
    {
      C_TYPE_VARIABLY_MODIFIED (x) = 1;
      க்கு (மரம் p = TYPE_POINTER_TO (x); p; p = TYPE_NEXT_PTR_TO (p))
	c_update_variably_modified (p);
    }
}


/* Verify the argument of the counted_by attribute of each field of
   the containing structure, OUTMOST_STRUCT_TYPE, including its inner
   anonymous struct/union, Report error and remove the corresponding
   attribute when it's not.  */

நிலையான வெறுமை
verify_counted_by_attribute (மரம் outmost_struct_type,
			     மரம் cur_struct_type)
{
  க்கு (மரம் field = TYPE_FIELDS (cur_struct_type); field;
       field = மரம்_CHAIN (field))
    {
      எனில் (flexible_array_member_type_p (மரம்_TYPE (field))
	   || மரம்_CODE (மரம்_TYPE (field)) == POINTER_TYPE)
	{
	  மரம் attr_counted_by = lookup_attribute ("counted_by",
						   DECL_ATTRIBUTES (field));

	  எனில் (!attr_counted_by)
	    தொடர்;

	  /* If there is an counted_by attribute attached to the field,
	     verify it.  */

	  மரம் fieldname = மரம்_மதிப்பு (மரம்_மதிப்பு (attr_counted_by));

	  /* Verify the argument of the attribute is a valid field of the
	     containing structure.  */

	  மரம் counted_by_field = lookup_field (outmost_struct_type,
						fieldname);

	  /* Error when the field is not found in the containing structure
	     and remove the corresponding counted_by attribute from the
	     field_decl.  */
	  எனில் (!counted_by_field)
	    {
	      error_at (DECL_SOURCE_LOCATION (field),
		    "argument %qE to the %<counted_by%> attribute"
		    " is not a field declaration in the same structure"
		    " as %qD", fieldname, field);
	      DECL_ATTRIBUTES (field)
		= remove_attribute ("counted_by", DECL_ATTRIBUTES (field));
	    }
	  இல்லையெனில்
	  /* Error when the field is not with an integer type.  */
	    {
	      போது (மரம்_CHAIN (counted_by_field))
		counted_by_field = மரம்_CHAIN (counted_by_field);
	      மரம் real_field = மரம்_மதிப்பு (counted_by_field);

	      எனில் (!INTEGRAL_TYPE_P (மரம்_TYPE (real_field)))
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
      இல்லையெனில் எனில் (RECORD_OR_UNION_TYPE_P (மரம்_TYPE (field))
	       && (DECL_NAME (field) == NULL_மரம்))
	verify_counted_by_attribute (outmost_struct_type, மரம்_TYPE (field));
    }
}

/* Caller should make sure the TYPE is a top-level type (i.e. not being
   nested in other structure/uniona). For such type, verify its counted_by
   if it is an anonymous structure/union.  */

வெறுமை
verify_counted_by_for_உச்சி_anonymous_type (மரம் type)
{
  எனில் (!RECORD_OR_UNION_TYPE_P (type))
    திரும்பு;

  எனில் (C_TYPE_FIELDS_HAS_COUNTED_BY (type)
      && c_type_tag (type) == NULL_மரம்)
    verify_counted_by_attribute (type, type);
}

/* TYPE is a struct or union that we're applying may_alias to after the body is
   parsed.  Fixup any POINTER_TO types.  */

நிலையான வெறுமை
c_fixup_may_alias (மரம் type)
{
  க்கு (மரம் t = TYPE_POINTER_TO (type); t; t = TYPE_NEXT_PTR_TO (t))
    க்கு (மரம் v = TYPE_MAIN_VARIANT (t); v; v = TYPE_NEXT_VARIANT (v))
      TYPE_REF_CAN_ALIAS_ALL (v) = உண்மை;
}

/* Fill in the fields of a RECORD_TYPE or UNION_TYPE node, T.
   LOC is the location of the RECORD_TYPE or UNION_TYPE's definition.
   FIELDLIST is a chain of FIELD_DECL nodes for the fields.
   ATTRIBUTES are attributes to be applied to the structure.

   ENCLOSING_STRUCT_PARSE_INFO is the value of STRUCT_PARSE_INFO when
   the struct was started.  */

மரம்
finish_struct (location_t loc, மரம் t, மரம் fieldlist, மரம் attributes,
	       வகுப்பு c_struct_parse_info *enclosing_struct_parse_info,
	       மரம் *கோவை)
{
  மரம் x;
  தருக்க toplevel = file_scope == current_scope;

  /* If this type was previously laid out as a forward reference,
     make sure we lay it out again.  */

  TYPE_SIZE (t) = NULL_மரம்;

  decl_attributes (&t, attributes, (முழு) ATTR_FLAG_TYPE_IN_PLACE);

  எனில் (pedantic)
    {
      க்கு (x = fieldlist; x; x = DECL_CHAIN (x))
	{
	  எனில் (DECL_NAME (x) != NULL_மரம்)
	    நிறுத்து;
	  எனில் (flag_isoc11 && RECORD_OR_UNION_TYPE_P (மரம்_TYPE (x)))
	    நிறுத்து;
	}

      எனில் (x == NULL_மரம்)
	{
	  எனில் (மரம்_CODE (t) == UNION_TYPE)
	    {
	      எனில் (fieldlist)
		pedwarn (loc, OPT_Wpedantic, "union has no named members");
	      இல்லையெனில்
		pedwarn (loc, OPT_Wpedantic, "union has no members");
	    }
	  இல்லையெனில்
	    {
	      எனில் (fieldlist)
		pedwarn (loc, OPT_Wpedantic, "struct has no named members");
	      இல்லையெனில்
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

  தருக்க saw_named_field = பொய்;
  க்கு (x = fieldlist; x; x = DECL_CHAIN (x))
    {
      /* Whether this field is the last field of the structure or union.
	 for UNION, any field is the last field of it.  */
      தருக்க is_last_field = (DECL_CHAIN (x) == NULL_மரம்)
			    || (மரம்_CODE (t) == UNION_TYPE);

      எனில் (மரம்_TYPE (x) == error_mark_முனை)
	தொடர்;

      DECL_CONTEXT (x) = t;

      மரம் t1 = strip_array_types (மரம்_TYPE (x));
      /* If any field is const, the structure type is pseudo-const.  */
      எனில் (மரம்_READONLY (x))
	C_TYPE_FIELDS_READONLY (t) = 1;
      இல்லையெனில்
	{
	  /* A field that is pseudo-const makes the structure likewise.  */
	  எனில் (RECORD_OR_UNION_TYPE_P (t1) && C_TYPE_FIELDS_READONLY (t1))
	    C_TYPE_FIELDS_READONLY (t) = 1;
	}

      /* Any field that is volatile means variables of this type must be
	 treated in some ways as volatile.  */
      எனில் (மரம்_THIS_VOLATILE (x))
	{
	  C_TYPE_FIELDS_VOLATILE (t) = 1;
	  C_TYPE_FIELDS_NON_CONSTEXPR (t) = 1;
	}

      /* Any field that is volatile, restrict-qualified or atomic
	 means the type cannot be used for a constexpr object.  */
      எனில் (TYPE_QUALS (t1)
	  & (TYPE_QUAL_VOLATILE | TYPE_QUAL_RESTRICT | TYPE_QUAL_ATOMIC))
	C_TYPE_FIELDS_NON_CONSTEXPR (t) = 1;
      இல்லையெனில் எனில் (RECORD_OR_UNION_TYPE_P (t1) && C_TYPE_FIELDS_NON_CONSTEXPR (t1))
	    C_TYPE_FIELDS_NON_CONSTEXPR (t) = 1;

      /* Any field of nominal variable size implies structure is too.  */
      எனில் (C_DECL_VARIABLE_SIZE (x))
	C_TYPE_VARIABLE_SIZE (t) = 1;

      /* If any field is variably modified, record this fact. */
      எனில் (c_type_variably_modified_p (மரம்_TYPE (x)))
	C_TYPE_VARIABLY_MODIFIED (t) = 1;

      எனில் (DECL_C_BIT_FIELD (x))
	{
	  unsigned HOST_WIDE_INT width = மரம்_to_uhwi (DECL_INITIAL (x));
	  DECL_SIZE (x) = bitsize_int (width);
	  DECL_BIT_FIELD (x) = 1;
	}

      எனில் (TYPE_PACKED (t)
	  && (DECL_BIT_FIELD (x)
	      || TYPE_ALIGN (மரம்_TYPE (x)) > BITS_PER_UNIT))
	DECL_PACKED (x) = 1;

      /* Detect flexible array member in an invalid context.  */
      எனில் (flexible_array_member_type_p (மரம்_TYPE (x)))
	{
	  எனில் (மரம்_CODE (t) == UNION_TYPE)
	    pedwarn (DECL_SOURCE_LOCATION (x), OPT_Wpedantic,
		     "flexible array member in union is a GCC extension");
	  இல்லையெனில் எனில் (!is_last_field)
	    {
	      error_at (DECL_SOURCE_LOCATION (x),
			"flexible array member not at end of struct");
	      மரம்_TYPE (x) = error_mark_முனை;
	    }
	  இல்லையெனில் எனில் (!saw_named_field)
	    pedwarn (DECL_SOURCE_LOCATION (x), OPT_Wpedantic,
		     "flexible array member in a struct with no named "
		     "members is a GCC extension");
	  எனில் (lookup_attribute ("counted_by", DECL_ATTRIBUTES (x)))
	    C_TYPE_FIELDS_HAS_COUNTED_BY (t) = 1;
	}

      எனில் (மரம்_CODE (மரம்_TYPE (x)) == POINTER_TYPE
	  && lookup_attribute ("counted_by", DECL_ATTRIBUTES (x)))
	C_TYPE_FIELDS_HAS_COUNTED_BY (t) = 1;

      /* If the field is an anonymous structure that includes a field
	 with counted_by attribute, this structure should also be marked
	 too.  */
      எனில் (RECORD_OR_UNION_TYPE_P (மரம்_TYPE (x))
	  && C_TYPE_FIELDS_HAS_COUNTED_BY (மரம்_TYPE (x))
	  && DECL_NAME (x) == NULL_மரம்
	  && c_type_tag (மரம்_TYPE (x)) == NULL_மரம்)
	C_TYPE_FIELDS_HAS_COUNTED_BY (t) = 1;

      எனில் (pedantic && மரம்_CODE (t) == RECORD_TYPE
	  && flexible_array_type_p (மரம்_TYPE (x)))
	pedwarn (DECL_SOURCE_LOCATION (x), OPT_Wpedantic,
		 "invalid use of structure with flexible array member");

      /* Set DECL_NOT_FLEXARRAY flag for FIELD_DECL x.  */
      DECL_NOT_FLEXARRAY (x) = !is_flexible_array_member_p (is_last_field, x);

      /* Set TYPE_INCLUDES_FLEXARRAY for the context of x, t.
	 when x is an array and is the last field.
	 There is only one last_field for a structure type, but there might
	 be multiple last_fields for a union type, therefore we should ORed
	 the result for multiple last_fields.  */
      எனில் (மரம்_CODE (மரம்_TYPE (x)) == ARRAY_TYPE)
	TYPE_INCLUDES_FLEXARRAY (t)
	  |= is_last_field && flexible_array_member_type_p (மரம்_TYPE (x));
      /* Recursively set TYPE_INCLUDES_FLEXARRAY for the context of x, t
	 when x is an union or record and is the last field.  */
      இல்லையெனில் எனில் (RECORD_OR_UNION_TYPE_P (மரம்_TYPE (x)))
	TYPE_INCLUDES_FLEXARRAY (t)
	  |= is_last_field && TYPE_INCLUDES_FLEXARRAY (மரம்_TYPE (x));

      எனில் (warn_flex_array_member_not_at_end
	  && !is_last_field
	  && RECORD_OR_UNION_TYPE_P (மரம்_TYPE (x))
	  && TYPE_INCLUDES_FLEXARRAY (மரம்_TYPE (x)))
	warning_at (DECL_SOURCE_LOCATION (x),
		    OPT_Wflex_array_member_not_at_end,
		    "structure containing a flexible array member"
		    " is not at the end of another structure");

      எனில் (DECL_NAME (x)
	  || RECORD_OR_UNION_TYPE_P (மரம்_TYPE (x)))
	saw_named_field = உண்மை;

      எனில் (AGGREGATE_TYPE_P (மரம்_TYPE (x))
	  && TYPE_TYPELESS_STORAGE (மரம்_TYPE (x)))
	TYPE_TYPELESS_STORAGE (t) = உண்மை;
    }

  detect_field_duplicates (fieldlist);

  /* Now we have the nearly final fieldlist.  Record it,
     then lay out the structure or union (including the fields).  */

  TYPE_FIELDS (t) = fieldlist;

  maybe_apply_pragma_scalar_storage_order (t);

  layout_type (t);

  எனில் (TYPE_SIZE_UNIT (t)
      && மரம்_CODE (TYPE_SIZE_UNIT (t)) == INTEGER_CST
      && !மரம்_OVERFLOW (TYPE_SIZE_UNIT (t))
      && !valid_constant_size_p (TYPE_SIZE_UNIT (t)))
    error ("type %qT is too large", t);

  /* Give bit-fields their proper types and rewrite the type of array fields
     with scalar component if the enclosing type has reverse storage order.  */
  க்கு (மரம் field = fieldlist; field; field = DECL_CHAIN (field))
    {
      எனில் (மரம்_CODE (field) == FIELD_DECL
	  && DECL_INITIAL (field)
	  && மரம்_TYPE (field) != error_mark_முனை)
	{
	  unsigned HOST_WIDE_INT width
	    = மரம்_to_uhwi (DECL_INITIAL (field));
	  மரம் type = மரம்_TYPE (field);
	  எனில் (VECTOR_TYPE_P (type))
	    {
	      error_at (DECL_SOURCE_LOCATION (field),
			"bit-field %qD has invalid type", field);
	      type = மரம்_TYPE (type);
	      மரம்_TYPE (field) = type;
	    }
	  எனில் (width != TYPE_PRECISION (type))
	    {
	      எனில் (BITINT_TYPE_P (type)
		  && width >= ((TYPE_UNSIGNED (type) || flag_isoc2y) ? 1 : 2))
		மரம்_TYPE (field)
		  = build_bitint_type (width, TYPE_UNSIGNED (type));
	      இல்லையெனில்
		மரம்_TYPE (field)
		  = c_build_bitfield_integer_type (width,
						   TYPE_UNSIGNED (type));
	      எனில் (மரம் attr = c_hardbool_type_attr (type))
		decl_attributes (&மரம்_TYPE (field),
				 copy_list (attr),
				 0, NULL_மரம்);
	      SET_DECL_MODE (field, TYPE_MODE (மரம்_TYPE (field)));
	    }
	  DECL_INITIAL (field) = NULL_மரம்;
	}
      இல்லையெனில் எனில் (TYPE_REVERSE_STORAGE_ORDER (t)
	       && மரம்_CODE (field) == FIELD_DECL
	       && மரம்_CODE (மரம்_TYPE (field)) == ARRAY_TYPE)
	{
	  மரம் ftype = மரம்_TYPE (field);
	  மரம் ctype = strip_array_types (ftype);
	  எனில் (!RECORD_OR_UNION_TYPE_P (ctype) && TYPE_MODE (ctype) != QImode)
	    {
	      மரம் fmain_type = TYPE_MAIN_VARIANT (ftype);
	      மரம் *typep = &fmain_type;
	      செய் {
		*typep = build_distinct_type_copy (*typep);
		TYPE_REVERSE_STORAGE_ORDER (*typep) = 1;
		typep = &மரம்_TYPE (*typep);
	      } போது (மரம்_CODE (*typep) == ARRAY_TYPE);
	      மரம்_TYPE (field)
		= c_build_qualified_type (fmain_type, TYPE_QUALS (ftype));
	    }
	}

      /* Warn on problematic type punning for storage order purposes.  */
      எனில் (மரம்_CODE (t) == UNION_TYPE
	  && மரம்_CODE (field) == FIELD_DECL
	  && AGGREGATE_TYPE_P (மரம்_TYPE (field)))
	{
	  மரம் ftype = மரம்_TYPE (field);
	  எனில் (மரம்_CODE (ftype) == ARRAY_TYPE)
	    ftype = strip_array_types (ftype);
	  எனில் (RECORD_OR_UNION_TYPE_P (ftype)
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
    முழு len = 0;

    க்கு (x = fieldlist; x; x = DECL_CHAIN (x))
      {
	எனில் (len > 15 || DECL_NAME (x) == வெற்று)
	  நிறுத்து;
	len += 1;
      }

    எனில் (len > 15)
      {
	மரம் *field_array;
	கட்டமைப்பு lang_type *space;
	கட்டமைப்பு sorted_fields_type *space2;

	len += list_length (x);

	/* Use the same allocation policy here that make_node uses, to
	   ensure that this lives as long as the rest of the struct decl.
	   All decls in an inline function need to be saved.  */

	space = ((கட்டமைப்பு lang_type *)
		 ggc_internal_cleared_alloc (c_dialect_objc ()
					     ? அளவு (கட்டமைப்பு lang_type)
					     : offsetof (கட்டமைப்பு lang_type,
							 info)));
	space2 = ((sorted_fields_type *)
		  ggc_internal_alloc (அளவு (கட்டமைப்பு sorted_fields_type)
				      + len * அளவு (மரம்)));

	len = 0;
	space->s = space2;
	field_array = &space2->elts[0];
	க்கு (x = fieldlist; x; x = DECL_CHAIN (x))
	  {
	    field_array[len++] = x;

	    /* If there is anonymous struct or union, break out of the loop.  */
	    எனில் (DECL_NAME (x) == வெற்று)
	      நிறுத்து;
	  }
	/* Found no anonymous struct/union.  Add the TYPE_LANG_SPECIFIC.  */
	எனில் (x == வெற்று)
	  {
	    TYPE_LANG_SPECIFIC (t) = space;
	    TYPE_LANG_SPECIFIC (t)->s->len = len;
	    field_array = TYPE_LANG_SPECIFIC (t)->s->elts;
	    qsort (field_array, len, அளவு (மரம்), field_decl_cmp);
	  }
      }
  }

  /* If this was supposed to be a transparent union, but we can't
     make it one, warn and turn off the flag.  */
  எனில் (மரம்_CODE (t) == UNION_TYPE
      && TYPE_TRANSPARENT_AGGR (t)
      && (!TYPE_FIELDS (t) || TYPE_MODE (t) != DECL_MODE (TYPE_FIELDS (t))))
    {
      TYPE_TRANSPARENT_AGGR (t) = 0;
      warning_at (loc, 0, "union cannot be made transparent");
    }

  மரம் incomplete_vars = C_TYPE_INCOMPLETE_VARS (TYPE_MAIN_VARIANT (t));
  க்கு (x = TYPE_MAIN_VARIANT (t); x; x = TYPE_NEXT_VARIANT (x))
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
      C_TYPE_INCOMPLETE_VARS (x) = NULL_மரம்;
      TYPE_INCLUDES_FLEXARRAY (x) = TYPE_INCLUDES_FLEXARRAY (t);
    }

  /* Check for consistency with previous definition.  */
  எனில் (flag_isoc23 && வெற்று != enclosing_struct_parse_info)
    {
      மரம் vistype = previous_tag (t);
      எனில் (vistype
	  && மரம்_CODE (vistype) == மரம்_CODE (t)
	  && !C_TYPE_BEING_DEFINED (vistype))
	{
	  TYPE_STUB_DECL (t) = TYPE_STUB_DECL (vistype);
	  எனில் (c_type_variably_modified_p (t))
	    {
	      error ("redefinition of struct or union %qT with variably "
		     "modified type", t);
	      எனில் (struct_parse_info->refloc != UNKNOWN_LOCATION)
		inform (struct_parse_info->refloc, "originally defined here");
	    }
	  இல்லையெனில் எனில் (!comptypes_same_p (t, vistype))
	    {
	      error ("redefinition of struct or union %qT", t);
	      எனில் (struct_parse_info->refloc != UNKNOWN_LOCATION)
		inform (struct_parse_info->refloc, "originally defined here");
	    }
	}
    }

  C_TYPE_BEING_DEFINED (t) = 0;

  எனில் (lookup_attribute ("may_alias", TYPE_ATTRIBUTES (t)))
    க்கு (x = TYPE_MAIN_VARIANT (t); x; x = TYPE_NEXT_VARIANT (x))
      c_fixup_may_alias (x);

  /* Set type canonical based on equivalence class.  */
  எனில் (flag_isoc23 && !C_TYPE_VARIABLE_SIZE (t))
    {
      எனில் (c_struct_htab == வெற்று)
	c_struct_htab = hash_table<c_struct_hasher>::create_ggc (61);

      hashval_t hash = c_struct_hasher::hash (t);

      gcc_checking_assert (TYPE_STRUCTURAL_EQUALITY_P (t));
      gcc_checking_assert (!TYPE_NAME (t)
			   || மரம்_CODE (TYPE_NAME (t)) == IDENTIFIER_முனை);

      மரம் *e = c_struct_htab->find_slot_with_hash (t, hash, செருகு);
      எனில் (*e)
	TYPE_CANONICAL (t) = TYPE_CANONICAL (*e);
      இல்லையெனில்
	{
	  TYPE_CANONICAL (t) = c_type_canonical (t);
	  *e = t;
	}
      c_update_type_canonical (t);
    }

  /* Update type location to the one of the definition, instead of e.g.
     a forward declaration.  */
  எனில் (TYPE_STUB_DECL (t))
    DECL_SOURCE_LOCATION (TYPE_STUB_DECL (t)) = loc;

  /* Finish debugging output for this type.  */
  rest_of_type_compilation (t, toplevel);

  finish_incomplete_vars (incomplete_vars, toplevel);


  எனில் (c_type_variably_modified_p (t))
    {
      c_update_variably_modified (t);
      /* Make sure a DECL_EXPR is created for structs with VLA members.
	 Because we do not know the context, we always pass expr
	 to force creation of a BIND_EXPR which is required in some
	 contexts.  */
      add_decl_கோவை (loc, t, கோவை, பொய்);
    }

  எனில் (warn_cxx_compat)
    warn_cxx_compat_finish_struct (fieldlist, மரம்_CODE (t), loc);

  எனில் (வெற்று != enclosing_struct_parse_info)
    {
      delete struct_parse_info;

      struct_parse_info = enclosing_struct_parse_info;

      /* If this struct is defined inside a struct, add it to
	 struct_types.  */
      எனில் (warn_cxx_compat
	  && struct_parse_info != வெற்று
	  && !in_sizeof && !in_typeof && !in_alignof && !in_countof)
	struct_parse_info->struct_types.safe_தள்ளு (t);
     }

  /* Only when the enclosing struct/union type is not anonymous, do more
     verification on the fields with counted_by attributes.  */
  எனில் (C_TYPE_FIELDS_HAS_COUNTED_BY (t) && c_type_tag (t) != NULL_மரம்)
    verify_counted_by_attribute (t, t);

  திரும்பு t;
}

நிலையான கட்டமைப்பு {
  gt_pointer_operator new_மதிப்பு;
  வெறுமை *cookie;
} resort_data;

/* This routine compares two fields like field_decl_cmp but using the
pointer operator in resort_data.  */

நிலையான முழு
resort_field_decl_cmp (மாறிலி வெறுமை *x_p, மாறிலி வெறுமை *y_p)
{
  மாறிலி மரம் *மாறிலி x = (மாறிலி மரம் *) x_p;
  மாறிலி மரம் *மாறிலி y = (மாறிலி மரம் *) y_p;

  எனில் (DECL_NAME (*x) == DECL_NAME (*y))
    /* A nontype is "greater" than a type.  */
    திரும்பு (மரம்_CODE (*y) == TYPE_DECL) - (மரம்_CODE (*x) == TYPE_DECL);
  எனில் (DECL_NAME (*x) == NULL_மரம்)
    திரும்பு -1;
  எனில் (DECL_NAME (*y) == NULL_மரம்)
    திரும்பு 1;
  {
    மரம் d1 = DECL_NAME (*x);
    மரம் d2 = DECL_NAME (*y);
    resort_data.new_மதிப்பு (&d1, &d1, resort_data.cookie);
    resort_data.new_மதிப்பு (&d2, &d2, resort_data.cookie);
    எனில் (d1 < d2)
      திரும்பு -1;
  }
  திரும்பு 1;
}

/* Resort DECL_SORTED_FIELDS because pointers have been reordered.  */

வெறுமை
resort_sorted_fields (வெறுமை *obj,
		      வெறுமை * ARG_UNUSED (orig_obj),
		      gt_pointer_operator new_மதிப்பு,
		      வெறுமை *cookie)
{
  கட்டமைப்பு sorted_fields_type *sf = (கட்டமைப்பு sorted_fields_type *) obj;
  resort_data.new_மதிப்பு = new_மதிப்பு;
  resort_data.cookie = cookie;
  qsort (&sf->elts[0], sf->len, அளவு (மரம்),
	 resort_field_decl_cmp);
}

/* Lay out the type T, and its element type, and so on.  */

நிலையான வெறுமை
layout_array_type (மரம் t)
{
  எனில் (மரம்_CODE (மரம்_TYPE (t)) == ARRAY_TYPE)
    layout_array_type (மரம்_TYPE (t));
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

மரம்
start_enum (location_t loc, கட்டமைப்பு c_enum_contents *the_enum, மரம் name,
	    மரம் fixed_underlying_type, தருக்க potential_nesting_p)
{
  மரம் enumtype = NULL_மரம்;
  location_t enumloc = UNKNOWN_LOCATION;

  /* If this is the real definition for a previous forward reference,
     fill in the contents in the same object that used to be the
     forward reference.  */

  எனில் (name != NULL_மரம்)
    enumtype = lookup_tag (ENUMERAL_TYPE, name, உண்மை, &enumloc);

  எனில் (enumtype != NULL_மரம் && மரம்_CODE (enumtype) == ENUMERAL_TYPE)
    {
      /* If the type is currently being defined or if we have seen an
	 incomplete version which is now complete, this is a nested
	 redefinition.  The later happens if the redefinition occurs
	 inside the enum specifier itself.  */
      எனில் (C_TYPE_BEING_DEFINED (enumtype)
	  || (potential_nesting_p && TYPE_மதிப்புகள் (enumtype) != NULL_மரம்))
	error_at (loc, "nested redefinition of %<enum %E%>", name);

      /* For C23 we allow redefinitions.  We set to zero and check for
	 consistency later.  */
      எனில் (flag_isoc23 && TYPE_மதிப்புகள் (enumtype) != NULL_மரம்)
	enumtype = NULL_மரம்;
    }

  எனில் (enumtype == NULL_மரம் || மரம்_CODE (enumtype) != ENUMERAL_TYPE)
    {
      enumtype = make_முனை (ENUMERAL_TYPE);
      TYPE_SIZE (enumtype) = NULL_மரம்;
      SET_TYPE_STRUCTURAL_EQUALITY (enumtype);
      pushtag (loc, name, enumtype);
      எனில் (fixed_underlying_type != NULL_மரம்)
	{
	  /* For an enum definition with a fixed underlying type, the
	     type is complete during the definition and the
	     enumeration constants have that type.  If there was a
	     tag, the type was completed in c_parser_enum_specifier.
	     If not, it must be completed here.  */
	  ENUM_FIXED_UNDERLYING_TYPE_P (enumtype) = உண்மை;
	  TYPE_MIN_மதிப்பு (enumtype) = TYPE_MIN_மதிப்பு (fixed_underlying_type);
	  TYPE_MAX_மதிப்பு (enumtype) = TYPE_MAX_மதிப்பு (fixed_underlying_type);
	  TYPE_UNSIGNED (enumtype) = TYPE_UNSIGNED (fixed_underlying_type);
	  SET_TYPE_ALIGN (enumtype, TYPE_ALIGN (fixed_underlying_type));
	  TYPE_SIZE (enumtype) = NULL_மரம்;
	  TYPE_PRECISION (enumtype) = TYPE_PRECISION (fixed_underlying_type);
	  ENUM_UNDERLYING_TYPE (enumtype) = fixed_underlying_type;
	  TYPE_CANONICAL (enumtype) = TYPE_CANONICAL (fixed_underlying_type);
	  c_update_type_canonical (enumtype);
	  layout_type (enumtype);
	}
    }
  /* Update type location to the one of the definition, instead of e.g.
     a forward declaration.  */
  இல்லையெனில் எனில் (TYPE_STUB_DECL (enumtype))
    {
      enumloc = DECL_SOURCE_LOCATION (TYPE_STUB_DECL (enumtype));
      DECL_SOURCE_LOCATION (TYPE_STUB_DECL (enumtype)) = loc;
    }

  C_TYPE_BEING_DEFINED (enumtype) = 1;

  எனில் (TYPE_மதிப்புகள் (enumtype) != NULL_மரம்)
    {
      /* This enum is a named one that has been declared already.  */
      auto_diagnostic_group d;
      error_at (loc, "redeclaration of %<enum %E%>", name);
      எனில் (enumloc != UNKNOWN_LOCATION)
	inform (enumloc, "originally defined here");

      /* Completely replace its old definition.
	 The old enumerators remain defined, however.  */
      TYPE_மதிப்புகள் (enumtype) = NULL_மரம்;
    }

  எனில் (ENUM_FIXED_UNDERLYING_TYPE_P (enumtype)
      && fixed_underlying_type == NULL_மரம்)
    {
      error_at (loc, "%<enum%> declared with but defined without "
		"fixed underlying type");
      ENUM_FIXED_UNDERLYING_TYPE_P (enumtype) = பொய்;
    }

  the_enum->enum_next_மதிப்பு = integer_zero_முனை;
  the_enum->enum_type = enumtype;
  the_enum->enum_overflow = 0;

  எனில் (flag_short_enums && !ENUM_FIXED_UNDERLYING_TYPE_P (enumtype))
    க்கு (மரம் v = TYPE_MAIN_VARIANT (enumtype); v; v = TYPE_NEXT_VARIANT (v))
      TYPE_PACKED (v) = 1;

  /* FIXME: This will issue a warning for a use of a type defined
     within sizeof in a statement expr.  This is not terribly serious
     as C++ doesn't permit statement exprs within sizeof anyhow.  */
  எனில் (warn_cxx_compat
      && (in_sizeof || in_typeof || in_alignof || in_countof))
    warning_at (loc, OPT_Wc___compat,
		"defining type in %qs expression is invalid in C++",
		(in_sizeof ? "sizeof"
		 : in_typeof ? "typeof"
		 : in_alignof ? "alignof"
		 : "_Countof"));

  எனில் (in_underspecified_init)
    error_at (loc, "%qT defined in underspecified object initializer",
	      enumtype);

  திரும்பு enumtype;
}

/* After processing and defining all the values of an enumeration type,
   install their decls in the enumeration type and finish it off.
   ENUMTYPE is the type object, VALUES a list of decl-value pairs,
   and ATTRIBUTES are the specified attributes.
   Returns ENUMTYPE.  */

மரம்
finish_enum (மரம் enumtype, மரம் மதிப்புகள், மரம் attributes)
{
  மரம் pair, tem;
  மரம் minnode = NULL_மரம், maxnode = NULL_மரம்;
  முழு precision;
  signop sign;
  தருக்க toplevel = (file_scope == current_scope);
  கட்டமைப்பு lang_type *lt;

  decl_attributes (&enumtype, attributes, (முழு) ATTR_FLAG_TYPE_IN_PLACE);

  /* Calculate the maximum value of any enumerator in this type.  */

  எனில் (மதிப்புகள் == error_mark_முனை)
    minnode = maxnode = integer_zero_முனை;
  இல்லையெனில்
    {
      minnode = maxnode = மரம்_மதிப்பு (மதிப்புகள்);
      க்கு (pair = மரம்_CHAIN (மதிப்புகள்); pair; pair = மரம்_CHAIN (pair))
	{
	  மரம் மதிப்பு = மரம்_மதிப்பு (pair);
	  எனில் (மரம்_int_cst_lt (maxnode, மதிப்பு))
	    maxnode = மதிப்பு;
	  எனில் (மரம்_int_cst_lt (மதிப்பு, minnode))
	    minnode = மதிப்பு;
	}
    }

  /* Construct the final type of this enumeration.  It is the same
     as one of the integral types - the narrowest one that fits, except
     that normally we only go as narrow as int - and signed iff any of
     the values are negative.  */
  sign = (மரம்_int_cst_sgn (minnode) >= 0) ? UNSIGNED : SIGNED;
  precision = MAX (மரம்_int_cst_min_precision (minnode, sign),
		   மரம்_int_cst_min_precision (maxnode, sign));

  தருக்க wider_than_int =
    (மரம்_int_cst_lt (minnode, TYPE_MIN_மதிப்பு (integer_type_முனை))
     || மரம்_int_cst_lt (TYPE_MAX_மதிப்பு (integer_type_முனை), maxnode));


  எனில் (!ENUM_FIXED_UNDERLYING_TYPE_P (enumtype))
    {
      /* If the precision of the type was specified with an attribute and it
	 was too small, give an error.  Otherwise, use it.  */
      எனில் (TYPE_PRECISION (enumtype) && lookup_attribute ("mode", attributes))
	{
	  எனில் (precision > TYPE_PRECISION (enumtype))
	    {
	      TYPE_PRECISION (enumtype) = 0;
	      error ("specified mode too small for enumerated values");
	    }
	  இல்லையெனில்
	    precision = TYPE_PRECISION (enumtype);
	}
      இல்லையெனில்
	TYPE_PRECISION (enumtype) = 0;

      எனில் (TYPE_PACKED (enumtype)
	  || precision > TYPE_PRECISION (integer_type_முனை)
	  || TYPE_PRECISION (enumtype))
	{
	  tem = c_common_type_for_size (precision, sign == UNSIGNED ? 1 : 0);
	  எனில் (tem == வெற்று)
	    {
	      /* This should only occur when both signed and unsigned
		 values of maximum precision occur among the
		 enumerators.  */
	      pedwarn (உள்ளீடு_location, 0,
		       "enumeration values exceed range of largest integer");
	      tem = widest_integer_literal_type_முனை;
	    }
	  இல்லையெனில் எனில் (precision > TYPE_PRECISION (intmax_type_முனை)
		   && !மரம்_int_cst_lt (minnode,
					TYPE_MIN_மதிப்பு (intmax_type_முனை))
		   && !மரம்_int_cst_lt (TYPE_MAX_மதிப்பு (uintmax_type_முனை),
					maxnode))
	    pedwarn (உள்ளீடு_location, OPT_Wpedantic,
		     "enumeration values exceed range of %qs",
		     sign == UNSIGNED ? "uintmax_t" : "intmax_t");
	}
      இல்லையெனில்
	tem = sign == UNSIGNED ? unsigned_type_முனை : integer_type_முனை;

      TYPE_MIN_மதிப்பு (enumtype) = TYPE_MIN_மதிப்பு (tem);
      TYPE_MAX_மதிப்பு (enumtype) = TYPE_MAX_மதிப்பு (tem);
      TYPE_UNSIGNED (enumtype) = TYPE_UNSIGNED (tem);
      SET_TYPE_ALIGN (enumtype, TYPE_ALIGN (tem));
      TYPE_SIZE (enumtype) = NULL_மரம்;
      TYPE_PRECISION (enumtype) = TYPE_PRECISION (tem);
      ENUM_UNDERLYING_TYPE (enumtype) =
	c_common_type_for_size (TYPE_PRECISION (tem), TYPE_UNSIGNED (tem));

      TYPE_CANONICAL (enumtype) =
	TYPE_CANONICAL (ENUM_UNDERLYING_TYPE (enumtype));
      c_update_type_canonical (enumtype);

      layout_type (enumtype);
    }

  எனில் (மதிப்புகள் != error_mark_முனை)
    {
      /* Change the type of the enumerators to be the enum type.  We
	 need to do this irrespective of the size of the enum, for
	 proper type checking.  Replace the DECL_INITIALs of the
	 enumerators, and the value slots of the list, with copies
	 that have the enum type; they cannot be modified in place
	 because they may be shared (e.g.  integer_zero_node) Finally,
	 change the purpose slots to point to the names of the decls.  */
      க்கு (pair = மதிப்புகள்; pair; pair = மரம்_CHAIN (pair))
	{
	  மரம் enu = மரம்_PURPOSE (pair);
	  மரம் ini = DECL_INITIAL (enu);

	  மரம்_TYPE (enu) = enumtype;

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
	  எனில் (!ENUM_FIXED_UNDERLYING_TYPE_P (enumtype) && wider_than_int)
	    ini = convert (enumtype, ini);

	  DECL_INITIAL (enu) = ini;
	  மரம்_PURPOSE (pair) = DECL_NAME (enu);
	  /* To match the C++ FE, store the CONST_DECL rather than just its
	     value.  */
	  மரம்_மதிப்பு (pair) = enu;
	}

      TYPE_மதிப்புகள் (enumtype) = மதிப்புகள்;
    }

  /* Record the min/max values so that we can warn about bit-field
     enumerations that are too small for the values.  */
  lt = ((கட்டமைப்பு lang_type *)
	ggc_internal_cleared_alloc (c_dialect_objc ()
				    ? அளவு (கட்டமைப்பு lang_type)
				    : offsetof (கட்டமைப்பு lang_type, info)));
  lt->enum_min = minnode;
  lt->enum_max = maxnode;
  TYPE_LANG_SPECIFIC (enumtype) = lt;

  /* Fix up all variant types of this enum type.  */
  மரம் incomplete_vars = C_TYPE_INCOMPLETE_VARS (TYPE_MAIN_VARIANT (enumtype));
  க்கு (tem = TYPE_MAIN_VARIANT (enumtype); tem; tem = TYPE_NEXT_VARIANT (tem))
    {
      C_TYPE_INCOMPLETE_VARS (tem) = NULL_மரம்;
      எனில் (tem == enumtype)
	தொடர்;
      TYPE_மதிப்புகள் (tem) = TYPE_மதிப்புகள் (enumtype);
      TYPE_MIN_மதிப்பு (tem) = TYPE_MIN_மதிப்பு (enumtype);
      TYPE_MAX_மதிப்பு (tem) = TYPE_MAX_மதிப்பு (enumtype);
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
  எனில் (warn_cxx_compat
      && struct_parse_info != வெற்று
      && !in_sizeof && !in_typeof && !in_alignof && !in_countof)
    struct_parse_info->struct_types.safe_தள்ளு (enumtype);

  /* Check for consistency with previous definition */
  எனில் (flag_isoc23)
    {
      மரம் vistype = previous_tag (enumtype);
      எனில் (vistype
	  && மரம்_CODE (vistype) == மரம்_CODE (enumtype)
	  && !C_TYPE_BEING_DEFINED (vistype))
	{
	  TYPE_STUB_DECL (enumtype) = TYPE_STUB_DECL (vistype);
	  எனில் (!comptypes_same_p (enumtype, vistype))
	    error("conflicting redefinition of enum %qT", enumtype);
	}
    }

  C_TYPE_BEING_DEFINED (enumtype) = 0;

  திரும்பு enumtype;
}

/* Build and install a CONST_DECL for one value of the
   current enumeration type (one that was begun with start_enum).
   DECL_LOC is the location of the enumerator.
   LOC is the location of the '=' operator if any, DECL_LOC otherwise.
   Return a tree-list containing the CONST_DECL and its value.
   Assignment of sequential values by default is handled here.  */

மரம்
build_enumerator (location_t decl_loc, location_t loc,
		  கட்டமைப்பு c_enum_contents *the_enum, மரம் name, மரம் மதிப்பு)
{
  மரம் decl;
  மரம் old_decl;

  /* Validate and default VALUE.  */

  எனில் (மதிப்பு != NULL_மரம்)
    {
      /* Don't issue more errors for error_mark_node (i.e. an
	 undeclared identifier) - just ignore the value expression.  */
      எனில் (மதிப்பு == error_mark_முனை)
	மதிப்பு = NULL_மரம்;
      இல்லையெனில் எனில் (!INTEGRAL_TYPE_P (மரம்_TYPE (மதிப்பு)))
	{
	  error_at (loc, "enumerator value for %qE is not an integer constant",
		    name);
	  மதிப்பு = NULL_மரம்;
	}
      இல்லையெனில்
	{
	  எனில் (மரம்_CODE (மதிப்பு) != INTEGER_CST)
	    {
	      மதிப்பு = c_fully_fold (மதிப்பு, பொய், வெற்று);
	      எனில் (மரம்_CODE (மதிப்பு) == INTEGER_CST)
		pedwarn (loc, OPT_Wpedantic,
			 "enumerator value for %qE is not an integer "
			 "constant expression", name);
	    }
	  எனில் (மரம்_CODE (மதிப்பு) != INTEGER_CST)
	    {
	      error ("enumerator value for %qE is not an integer constant",
		     name);
	      மதிப்பு = NULL_மரம்;
	    }
	  இல்லையெனில்
	    {
	      மதிப்பு = default_conversion (மதிப்பு);
	      constant_expression_warning (மதிப்பு);
	    }
	}
    }

  /* Default based on previous value.  */
  /* It should no longer be possible to have NON_LVALUE_EXPR
     in the default.  */
  எனில் (மதிப்பு == NULL_மரம்)
    {
      மதிப்பு = the_enum->enum_next_மதிப்பு;
      எனில் (the_enum->enum_overflow)
	error_at (loc, "overflow in enumeration values");
    }
  எனில் (ENUM_FIXED_UNDERLYING_TYPE_P (the_enum->enum_type))
    {
      /* Enumeration constants must fit in the fixed underlying type.  */
      எனில் (!int_fits_type_p (மதிப்பு, ENUM_UNDERLYING_TYPE (the_enum->enum_type)))
	error_at (loc,
		  "enumerator value outside the range of underlying type");
      /* Enumeration constants for an enum with fixed underlying type
	 have the enum type, both inside and outside the
	 definition.  */
      மதிப்பு = convert (the_enum->enum_type, மதிப்பு);
    }
  இல்லையெனில் எனில் (flag_isoc23
	   && (old_decl = lookup_name_in_scope (name, current_scope))
	   && old_decl != error_mark_முனை
	   && மரம்_TYPE (old_decl)
	   && மரம்_TYPE (மரம்_TYPE (old_decl))
	   && மரம்_CODE (old_decl) == CONST_DECL)
    {
      /* Enumeration constants in a redeclaration have the previous type.  */
      மரம் previous_type = மரம்_TYPE (DECL_INITIAL (old_decl));
      எனில் (!int_fits_type_p (மதிப்பு, previous_type))
	{
	  error_at (loc, "value of redeclared enumerator outside the range "
			 "of %qT", previous_type);
	  locate_old_decl (old_decl);
	}
      மதிப்பு = convert (previous_type, மதிப்பு);
    }
  இல்லையெனில்
    {
      /* Even though the underlying type of an enum is unspecified, the
	 type of enumeration constants is explicitly defined as int
	 (6.4.4.3/2 in the C99 Standard).  C23 allows any integer type, and
	 GCC allows such types for older standards as an extension.  */
      தருக்க warned_range = பொய்;
      எனில் (!int_fits_type_p (மதிப்பு,
			    (TYPE_UNSIGNED (மரம்_TYPE (மதிப்பு))
			     ? uintmax_type_முனை
			     : intmax_type_முனை)))
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
				TYPE_UNSIGNED (மரம்_TYPE (மதிப்பு))
				? "uintmax_t"
				: "intmax_t");
      எனில் (!warned_range && !int_fits_type_p (மதிப்பு, integer_type_முனை))
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
      எனில் (int_fits_type_p (மதிப்பு, integer_type_முனை))
	மதிப்பு = convert (integer_type_முனை, மதிப்பு);
    }

  /* Set basis for default for next value.  */
  எனில் (ENUM_FIXED_UNDERLYING_TYPE_P (the_enum->enum_type))
    {
      மரம் underlying_type = ENUM_UNDERLYING_TYPE (the_enum->enum_type);
      எனில் (மரம்_CODE (underlying_type) == BOOLEAN_TYPE)
	/* A value of 2 following a value of 1 overflows bool, but we
	   cannot carry out addition directly on bool without
	   promotion, and converting the result of arithmetic in a
	   wider type back to bool would not produce the right result
	   for this overflow check.  */
	the_enum->enum_next_மதிப்பு = invert_truthvalue_loc (loc, மதிப்பு);
      இல்லையெனில்
	the_enum->enum_next_மதிப்பு
	  = build_இருமம்_op (கோவை_LOC_OR_LOC (மதிப்பு, உள்ளீடு_location),
			     PLUS_கோவை, convert (underlying_type, மதிப்பு),
			     convert (underlying_type, integer_one_முனை),
			     பொய்);
    }
  இல்லையெனில்
    {
      /* In a redeclaration the type can already be the enumeral type.  */
      எனில் (மரம்_CODE (மரம்_TYPE (மதிப்பு)) == ENUMERAL_TYPE)
	மதிப்பு = convert (ENUM_UNDERLYING_TYPE (மரம்_TYPE (மதிப்பு)), மதிப்பு);
      the_enum->enum_next_மதிப்பு
	= build_இருமம்_op (கோவை_LOC_OR_LOC (மதிப்பு, உள்ளீடு_location),
			   PLUS_கோவை, மதிப்பு, integer_one_முனை, பொய்);
    }
  the_enum->enum_overflow = மரம்_int_cst_lt (the_enum->enum_next_மதிப்பு, மதிப்பு);
  எனில் (the_enum->enum_overflow
      && !ENUM_FIXED_UNDERLYING_TYPE_P (the_enum->enum_type))
    {
      /* Choose a wider type with the same signedness if
	 available.  */
      முழு prec = TYPE_PRECISION (மரம்_TYPE (மதிப்பு)) + 1;
      தருக்க unsignedp = TYPE_UNSIGNED (மரம்_TYPE (மதிப்பு));
      மரம் new_type = (unsignedp
		       ? long_unsigned_type_முனை
		       : long_integer_type_முனை);
      எனில் (prec > TYPE_PRECISION (new_type))
	new_type = (unsignedp
		    ? long_long_unsigned_type_முனை
		    : long_long_integer_type_முனை);
      எனில் (prec > TYPE_PRECISION (new_type))
	new_type = (unsignedp
		    ? widest_unsigned_literal_type_முனை
		    : widest_integer_literal_type_முனை);
      எனில் (prec <= TYPE_PRECISION (new_type))
	{
	  the_enum->enum_overflow = பொய்;
	  the_enum->enum_next_மதிப்பு
	    = build_இருமம்_op (கோவை_LOC_OR_LOC (மதிப்பு, உள்ளீடு_location),
			       PLUS_கோவை, convert (new_type, மதிப்பு),
			       integer_one_முனை, பொய்);
	  gcc_assert (!மரம்_int_cst_lt (the_enum->enum_next_மதிப்பு, மதிப்பு));
	}
    }

  /* Now create a declaration for the enum value name.  */

  decl = build_decl (decl_loc, CONST_DECL, name, மரம்_TYPE (மதிப்பு));
  DECL_INITIAL (decl) = மதிப்பு;
  DECL_CONTEXT (decl) = the_enum->enum_type;
  pushdecl (decl);

  திரும்பு மரம்_cons (decl, மதிப்பு, NULL_மரம்);
}

/* Implement LANG_HOOKS_SIMULATE_ENUM_DECL.  */

மரம்
c_simulate_enum_decl (location_t loc, மாறிலி எழுத்து *name,
		      vec<string_int_pair> *மதிப்புகள்_ptr)
{
  location_t saved_loc = உள்ளீடு_location;
  உள்ளீடு_location = loc;

  கட்டமைப்பு c_enum_contents the_enum;
  மரம் enumtype = start_enum (loc, &the_enum, get_identifier (name),
			      NULL_மரம், பொய்);

  மரம் மதிப்பு_chain = NULL_மரம்;
  string_int_pair *மதிப்பு;
  vec<string_int_pair> மதிப்புகள் = *மதிப்புகள்_ptr;
  unsigned முழு i;
  FOR_EACH_VEC_ELT (மதிப்புகள், i, மதிப்பு)
    {
      மரம் decl = build_enumerator (loc, loc, &the_enum,
				    get_identifier (மதிப்பு->first),
				    build_int_cst (integer_type_முனை,
						   மதிப்பு->second));
      மரம்_CHAIN (decl) = மதிப்பு_chain;
      மதிப்பு_chain = decl;
    }

  finish_enum (enumtype, nreverse (மதிப்பு_chain), NULL_மரம்);

  உள்ளீடு_location = saved_loc;
  திரும்பு enumtype;
}

/* Implement LANG_HOOKS_SIMULATE_RECORD_DECL.  */

மரம்
c_simulate_record_decl (location_t loc, மாறிலி எழுத்து *name,
			array_slice<மாறிலி மரம்> fields)
{
  location_t saved_loc = உள்ளீடு_location;
  உள்ளீடு_location = loc;

  வகுப்பு c_struct_parse_info *struct_info;
  மரம் ident = get_identifier (name);
  மரம் type = start_struct (loc, RECORD_TYPE, ident, &struct_info);

  க்கு (unsigned முழு i = 0; i < fields.size (); ++i)
    {
      DECL_FIELD_CONTEXT (fields[i]) = type;
      எனில் (i > 0)
	DECL_CHAIN (fields[i - 1]) = fields[i];
    }

  finish_struct (loc, type, fields[0], NULL_மரம், struct_info);

  மரம் decl = build_decl (loc, TYPE_DECL, ident, type);
  set_underlying_type (decl);
  lang_hooks.decls.pushdecl (decl);

  உள்ளீடு_location = saved_loc;
  திரும்பு type;
}

/* Create the FUNCTION_DECL for a function definition.
   DECLSPECS, DECLARATOR and ATTRIBUTES are the parts of
   the declaration; they describe the function's name and the type it returns,
   but twisted together in a fashion that parallels the syntax of C.

   This function creates a binding context for the function body
   as well as setting up the FUNCTION_DECL in current_function_decl.

   Returns true on success.  If the DECLARATOR is not suitable for a function
   (it defines a datum instead), we return false to report a parse error.  */

தருக்க
start_function (கட்டமைப்பு c_declspecs *declspecs, கட்டமைப்பு c_declarator *declarator,
		மரம் attributes)
{
  மரம் decl1, old_decl;
  மரம் restype, resdecl;
  location_t loc;
  location_t result_loc;
  மரம் கோவை = வெற்று;

  current_function_returns_மதிப்பு = 0;  /* Assume, until we see it does.  */
  current_function_returns_null = 0;
  current_function_returns_abnormally = 0;
  warn_about_return_type = 0;
  c_switch_அடுக்கு = வெற்று;

  /* Indicate no valid break/continue context.  */
  in_statement = 0;

  decl1 = grokdeclarator (declarator, declspecs, FUNCDEF, உண்மை, வெற்று,
			  &attributes, &கோவை, வெற்று, DEPRECATED_NORMAL);
  invoke_plugin_callbacks (PLUGIN_START_PARSE_FUNCTION, decl1);

  /* If the declarator is not suitable for a function definition,
     cause a syntax error.  */
  எனில் (decl1 == NULL_மரம்
      || மரம்_CODE (decl1) != FUNCTION_DECL)
    திரும்பு பொய்;

  /* Nested functions may have variably modified (return) type.
     Make sure the size expression is evaluated at this point.  */
  எனில் (கோவை && !current_scope->parm_flag)
    add_stmt (fold_convert (void_type_முனை, கோவை));

  loc = DECL_SOURCE_LOCATION (decl1);

  /* A nested function is not global.  */
  எனில் (current_function_decl != NULL_மரம்)
    மரம்_PUBLIC (decl1) = 0;

  c_decl_attributes (&decl1, attributes, 0);

  எனில் (DECL_DECLARED_INLINE_P (decl1)
      && DECL_UNINLINABLE (decl1)
      && lookup_attribute ("noinline", DECL_ATTRIBUTES (decl1)))
    {
      auto_urlify_attributes sentinel;
      warning_at (loc, OPT_Wattributes,
		  "inline function %qD given attribute %qs",
		  decl1, "noinline");
    }

  /* Handle gnu_inline attribute.  */
  எனில் (declspecs->inline_p
      && !flag_gnu89_inline
      && மரம்_CODE (decl1) == FUNCTION_DECL
      && (lookup_attribute ("gnu_inline", DECL_ATTRIBUTES (decl1))
	  || current_function_decl))
    {
      எனில் (declspecs->storage_class != csc_static)
	DECL_EXTERNAL (decl1) = !DECL_EXTERNAL (decl1);
    }

  announce_function (decl1);

  எனில் (!COMPLETE_OR_VOID_TYPE_P (மரம்_TYPE (மரம்_TYPE (decl1))))
    {
      error_at (loc, "return type is an incomplete type");
      /* Make it return void instead.  */
      மரம்_TYPE (decl1)
	= c_build_function_type (void_type_முனை,
				 TYPE_ARG_TYPES (மரம்_TYPE (decl1)),
				 TYPE_NO_NAMED_ARGS_STDARG_P (மரம்_TYPE (decl1)));
    }

  எனில் (warn_about_return_type)
    permerror_opt (loc, flag_isoc99 ? OPT_Wimplicit_int
		   : (warn_return_type > 0 ? OPT_Wreturn_type
		      : OPT_Wimplicit_int),
		   "return type defaults to %<int%>");

  /* Make the init_value nonzero so pushdecl knows this is not tentative.
     error_mark_node is replaced below (in pop_scope) with the BLOCK.  */
  DECL_INITIAL (decl1) = error_mark_முனை;

  /* If this definition isn't a prototype and we had a prototype declaration
     before, copy the arg type info from that prototype.  */
  old_decl = lookup_name_in_scope (DECL_NAME (decl1), current_scope);
  எனில் (old_decl && மரம்_CODE (old_decl) != FUNCTION_DECL)
    old_decl = NULL_மரம்;

  current_function_prototype_locus = UNKNOWN_LOCATION;
  current_function_prototype_built_in = பொய்;
  current_function_prototype_arg_types = NULL_மரம்;
  மரம் newtype = மரம்_TYPE (decl1);
  மரம் oldtype = old_decl ? மரம்_TYPE (old_decl) : newtype;
  எனில் (!prototype_p (newtype))
    {
      மரம் oldrt = மரம்_TYPE (oldtype);
      மரம் newrt = மரம்_TYPE (newtype);
      எனில் (old_decl != NULL_மரம்
	  && மரம்_CODE (oldtype) == FUNCTION_TYPE
	  && comptypes (oldrt, newrt)
	  && !TYPE_NO_NAMED_ARGS_STDARG_P (oldtype))
	{
	  எனில் (stdarg_p (oldtype))
	    {
	      auto_diagnostic_group d;
	      warning_at (loc, 0, "%q+D defined as variadic function "
			  "without prototype", decl1);
	      locate_old_decl (old_decl);
	    }
	  மரம்_TYPE (decl1) = composite_type (oldtype, newtype);
	  current_function_prototype_locus = DECL_SOURCE_LOCATION (old_decl);
	  current_function_prototype_built_in
	    = C_DECL_BUILTIN_PROTOTYPE (old_decl);
	  current_function_prototype_arg_types
	    = TYPE_ARG_TYPES (newtype);
	}
      எனில் (மரம்_PUBLIC (decl1))
	{
	  /* If there is an external prototype declaration of this
	     function, record its location but do not copy information
	     to this decl.  This may be an invisible declaration
	     (built-in or in a scope which has finished) or simply
	     have more refined argument types than any declaration
	     found above.  */
	  கட்டமைப்பு c_binding *b;
	  க்கு (b = I_குறியீடு_BINDING (DECL_NAME (decl1)); b; b = b->shadowed)
	    எனில் (B_IN_SCOPE (b, external_scope))
	      நிறுத்து;
	  எனில் (b)
	    {
	      மரம் ext_decl, ext_type;
	      ext_decl = b->decl;
	      ext_type = b->u.type ? b->u.type : மரம்_TYPE (ext_decl);
	      எனில் (மரம்_CODE (ext_type) == FUNCTION_TYPE
		  && comptypes (மரம்_TYPE (மரம்_TYPE (decl1)),
				மரம்_TYPE (ext_type)))
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
  எனில் (warn_deprecated_non_prototype
      && old_decl != NULL_மரம்
      && மரம்_CODE (oldtype) == FUNCTION_TYPE
      && !TYPE_ARG_TYPES (oldtype)
      && !TYPE_NO_NAMED_ARGS_STDARG_P (oldtype)
      && (TYPE_ARG_TYPES (newtype)
	  && மரம்_மதிப்பு (TYPE_ARG_TYPES (newtype)) != void_type_முனை))
    {
      தருக்க warned = warning_at (loc, OPT_Wdeprecated_non_prototype,
				"ISO C23 does not allow defining"
				" parameters for function %qE declared"
				" without parameters",
				decl1);
      எனில் (warned)
	inform (DECL_SOURCE_LOCATION (old_decl), "declared here");
    }

  /* Optionally warn of old-fashioned def with no previous prototype.  */
  எனில் (warn_strict_prototypes
      && old_decl != error_mark_முனை
      && !prototype_p (மரம்_TYPE (decl1))
      && C_DECL_ISNT_PROTOTYPE (old_decl))
    warning_at (loc, OPT_Wstrict_prototypes,
		"function declaration isn%'t a prototype");
  /* Optionally warn of any global def with no previous prototype.  */
  இல்லையெனில் எனில் (warn_missing_prototypes
	   && old_decl != error_mark_முனை
	   && மரம்_PUBLIC (decl1)
	   && !MAIN_NAME_P (DECL_NAME (decl1))
	   && C_DECL_ISNT_PROTOTYPE (old_decl)
	   && !DECL_DECLARED_INLINE_P (decl1))
    warning_at (loc, OPT_Wmissing_prototypes,
		"no previous prototype for %qD", decl1);
  /* Optionally warn of any def with no previous prototype
     if the function has already been used.  */
  இல்லையெனில் எனில் (warn_missing_prototypes
	   && old_decl != NULL_மரம்
	   && old_decl != error_mark_முனை
	   && மரம்_USED (old_decl)
	   && !prototype_p (மரம்_TYPE (old_decl)))
    warning_at (loc, OPT_Wmissing_prototypes,
		"%qD was used with no prototype before its definition", decl1);
  /* Optionally warn of any global def with no previous declaration.  */
  இல்லையெனில் எனில் (warn_missing_declarations
	   && மரம்_PUBLIC (decl1)
	   && old_decl == NULL_மரம்
	   && !MAIN_NAME_P (DECL_NAME (decl1))
	   && !DECL_DECLARED_INLINE_P (decl1))
    warning_at (loc, OPT_Wmissing_declarations,
		"no previous declaration for %qD",
		decl1);
  /* Optionally warn of any def with no previous declaration
     if the function has already been used.  */
  இல்லையெனில் எனில் (warn_missing_declarations
	   && old_decl != NULL_மரம்
	   && old_decl != error_mark_முனை
	   && மரம்_USED (old_decl)
	   && C_DECL_IMPLICIT (old_decl))
    warning_at (loc, OPT_Wmissing_declarations,
		"%qD was used with no declaration before its definition", decl1);

  /* This function exists in static storage.
     (This does not mean `static' in the C sense!)  */
  மரம்_STATIC (decl1) = 1;

  /* This is the earliest point at which we might know the assembler
     name of the function.  Thus, if it's set before this, die horribly.  */
  gcc_assert (!DECL_ASSEMBLER_NAME_SET_P (decl1));

  /* If #pragma weak was used, mark the decl weak now.  */
  எனில் (current_scope == file_scope)
    maybe_apply_pragma_weak (decl1);

  /* Warn for unlikely, improbable, or stupid declarations of `main'.  */
  எனில் (warn_main && MAIN_NAME_P (DECL_NAME (decl1)))
    {
      எனில் (TYPE_MAIN_VARIANT (மரம்_TYPE (மரம்_TYPE (decl1)))
	  != integer_type_முனை)
	pedwarn (loc, OPT_Wmain, "return type of %qD is not %<int%>", decl1);
      இல்லையெனில் எனில் (TYPE_ATOMIC (மரம்_TYPE (மரம்_TYPE (decl1))))
	pedwarn (loc, OPT_Wmain, "%<_Atomic%>-qualified return type of %qD",
		 decl1);

      check_main_parameter_types (decl1);

      எனில் (!மரம்_PUBLIC (decl1))
	pedwarn (loc, OPT_Wmain,
		 "%qD is normally a non-static function", decl1);
    }

  மரம் parms = current_function_arg_info->parms;
  எனில் (old_decl)
    {
      location_t origloc = DECL_SOURCE_LOCATION (old_decl);
      warn_parms_array_mismatch (origloc, old_decl, parms);
    }

  /* To enable versions to be created across TU's we mark and mangle all
     non-default versioned functions.  */
  எனில் (மரம்_CODE (decl1) == FUNCTION_DECL
      && !TARGET_HAS_FMV_TARGET_ATTRIBUTE
      && get_target_version (decl1).is_valid ())
    {
      maybe_mark_function_versioned (decl1);
      எனில் (current_scope != file_scope)
	error ("versioned definitions are only allowed at file scope");
    }

  /* Record the decl so that the function name is defined.
     If we already have a decl for this name, and it is a FUNCTION_DECL,
     use the old decl.  */

  current_function_decl = pushdecl (decl1);

  எனில் (மரம் access = build_attr_access_from_parms (parms, பொய்))
    decl_attributes (&current_function_decl, access, ATTR_FLAG_INTERNAL,
		     old_decl);

  தள்ளு_scope ();
  declare_parm_level ();

  /* Set the result decl source location to the location of the typespec.  */
  result_loc = (declspecs->locations[cdw_typespec] == UNKNOWN_LOCATION
		? loc : declspecs->locations[cdw_typespec]);
  restype = மரம்_TYPE (மரம்_TYPE (current_function_decl));
  resdecl = build_decl (result_loc, RESULT_DECL, NULL_மரம், restype);
  DECL_ARTIFICIAL (resdecl) = 1;
  DECL_IGNORED_P (resdecl) = 1;
  DECL_RESULT (current_function_decl) = resdecl;

  start_fname_decls ();

  திரும்பு உண்மை;
}

/* Subroutine of store_parm_decls which handles new-style function
   definitions (prototype format). The parms already have decls, so we
   need only record them as in effect and complain if any redundant
   old-style parm decls were written.  */
நிலையான வெறுமை
store_parm_decls_newstyle (மரம் fndecl, மாறிலி கட்டமைப்பு c_arg_info *arg_info)
{
  மரம் decl;
  c_arg_tag *tag;
  unsigned ix;

  எனில் (current_scope->bindings)
    {
      error_at (DECL_SOURCE_LOCATION (fndecl),
		"old-style parameter declarations in prototyped "
		"function definition");

      /* Get rid of the old-style declarations.  */
      எடு_scope ();
      தள்ளு_scope ();
    }
  /* Don't issue this warning for nested functions, and don't issue this
     warning if we got here because ARG_INFO_TYPES was error_mark_node
     (this happens when a function definition has just an ellipsis in
     its parameter list).  */
  இல்லையெனில் எனில் (!in_system_header_at (உள்ளீடு_location)
	   && !current_function_scope
	   && arg_info->types != error_mark_முனை
	   && !arg_info->c23_empty_parens)
    warning_at (DECL_SOURCE_LOCATION (fndecl), OPT_Wtraditional,
		"traditional C rejects ISO C style function definitions");

  /* Now make all the parameter declarations visible in the function body.
     We can bypass most of the grunt work of pushdecl.  */
  க்கு (decl = arg_info->parms; decl; decl = DECL_CHAIN (decl))
    {
      DECL_CONTEXT (decl) = current_function_decl;
      எனில் (DECL_NAME (decl))
	{
	  bind (DECL_NAME (decl), decl, current_scope,
		/*invisible=*/பொய், /*nested=*/பொய்,
		UNKNOWN_LOCATION);
	  எனில் (!மரம்_USED (decl))
	    warn_if_shadowing (decl);
	}
      இல்லையெனில்
	pedwarn_c11 (DECL_SOURCE_LOCATION (decl), OPT_Wmissing_parameter_name,
		     "ISO C does not support omitting parameter names in "
		     "function definitions before C23");
    }

  /* Record the parameter list in the function declaration.  */
  DECL_ARGUMENTS (fndecl) = arg_info->parms;

  /* Now make all the ancillary declarations visible, likewise.  */
  க்கு (decl = arg_info->others; decl; decl = DECL_CHAIN (decl))
    {
      DECL_CONTEXT (decl) = current_function_decl;
      எனில் (DECL_NAME (decl))
	bind (DECL_NAME (decl), decl, current_scope,
	      /*invisible=*/பொய்,
	      /*nested=*/(மரம்_CODE (decl) == FUNCTION_DECL),
	      UNKNOWN_LOCATION);
    }

  /* And all the tag declarations.  */
  FOR_EACH_VEC_SAFE_ELT_REVERSE (arg_info->tags, ix, tag)
    எனில் (tag->id)
      bind (tag->id, tag->type, current_scope,
	    /*invisible=*/பொய், /*nested=*/பொய், UNKNOWN_LOCATION);
}

/* Subroutine of store_parm_decls which handles old-style function
   definitions (separate parameter list and declarations).  */

நிலையான வெறுமை
store_parm_decls_oldstyle (மரம் fndecl, மாறிலி கட்டமைப்பு c_arg_info *arg_info)
{
  கட்டமைப்பு c_binding *b;
  மரம் parm, decl, last;
  மரம் parmids = arg_info->parms;
  hash_set<மரம்> seen_args;

  எனில் (!in_system_header_at (உள்ளீடு_location))
    {
      எனில் (flag_isoc23)
	pedwarn (DECL_SOURCE_LOCATION (fndecl),
		 OPT_Wold_style_definition, "old-style function definition");
      இல்லையெனில்
	warning_at (DECL_SOURCE_LOCATION (fndecl),
		    OPT_Wold_style_definition,
		    "old-style function definition");
    }

  எனில் (current_scope->had_vla_unspec)
    error ("%<[*]%> not allowed in other than function prototype scope");

  /* Match each formal parameter name with its declaration.  Save each
     decl in the appropriate TREE_PURPOSE slot of the parmids chain.  */
  க்கு (parm = parmids; parm; parm = மரம்_CHAIN (parm))
    {
      எனில் (மரம்_மதிப்பு (parm) == NULL_மரம்)
	{
	  error_at (DECL_SOURCE_LOCATION (fndecl),
		    "parameter name missing from parameter list");
	  மரம்_PURPOSE (parm) = NULL_மரம்;
	  தொடர்;
	}

      b = I_குறியீடு_BINDING (மரம்_மதிப்பு (parm));
      எனில் (b && B_IN_CURRENT_SCOPE (b))
	{
	  decl = b->decl;
	  /* Skip erroneous parameters.  */
	  எனில் (decl == error_mark_முனை)
	    தொடர்;
	  /* If we got something other than a PARM_DECL it is an error.  */
	  எனில் (மரம்_CODE (decl) != PARM_DECL)
	    {
	      error_at (DECL_SOURCE_LOCATION (decl),
			"%qD declared as a non-parameter", decl);
	      தொடர்;
	    }
	  /* If the declaration is already marked, we have a duplicate
	     name.  Complain and ignore the duplicate.  */
	  இல்லையெனில் எனில் (seen_args.contains (decl))
	    {
	      error_at (DECL_SOURCE_LOCATION (decl),
			"multiple parameters named %qD", decl);
	      மரம்_PURPOSE (parm) = NULL_மரம்;
	      தொடர்;
	    }
	  /* If the declaration says "void", complain and turn it into
	     an int.  */
	  இல்லையெனில் எனில் (VOID_TYPE_P (மரம்_TYPE (decl)))
	    {
	      error_at (DECL_SOURCE_LOCATION (decl),
			"parameter %qD declared with void type", decl);
	      மரம்_TYPE (decl) = integer_type_முனை;
	      DECL_ARG_TYPE (decl) = integer_type_முனை;
	      layout_decl (decl, 0);
	    }
	  warn_if_shadowing (decl);
	}
      /* If no declaration found, default to int.  */
      இல்லையெனில்
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
			     PARM_DECL, மரம்_மதிப்பு (parm), integer_type_முனை);
	  DECL_ARG_TYPE (decl) = மரம்_TYPE (decl);
	  pushdecl (decl);
	  warn_if_shadowing (decl);

	  எனில் (flag_isoc99)
	    permerror_opt (DECL_SOURCE_LOCATION (decl),
			   OPT_Wimplicit_int, "type of %qD defaults to %<int%>",
			   decl);
	  இல்லையெனில்
	    warning_at (DECL_SOURCE_LOCATION (decl),
			OPT_Wmissing_parameter_type,
			"type of %qD defaults to %<int%>", decl);
	}

      மரம்_PURPOSE (parm) = decl;
      seen_args.add (decl);
    }

  /* Now examine the parms chain for incomplete declarations
     and declarations with no corresponding names.  */

  க்கு (b = current_scope->bindings; b; b = b->prev)
    {
      parm = b->decl;
      எனில் (மரம்_CODE (parm) != PARM_DECL)
	தொடர்;

      எனில் (மரம்_TYPE (parm) != error_mark_முனை
	  && !COMPLETE_TYPE_P (மரம்_TYPE (parm)))
	{
	  error_at (DECL_SOURCE_LOCATION (parm),
		    "parameter %qD has incomplete type", parm);
	  மரம்_TYPE (parm) = error_mark_முனை;
	}

      எனில் (!seen_args.contains (parm))
	{
	  error_at (DECL_SOURCE_LOCATION (parm),
		    "declaration for parameter %qD but no such parameter",
		    parm);

	  /* Pretend the parameter was not missing.
	     This gets us to a standard state and minimizes
	     further error messages.  */
	  parmids = chainon (parmids, மரம்_cons (parm, 0, 0));
	}
    }

  /* Chain the declarations together in the order of the list of
     names.  Store that chain in the function decl, replacing the
     list of names.  Update the current scope to match.  */
  DECL_ARGUMENTS (fndecl) = NULL_மரம்;

  க்கு (parm = parmids; parm; parm = மரம்_CHAIN (parm))
    எனில் (மரம்_PURPOSE (parm))
      நிறுத்து;
  எனில் (parm && மரம்_PURPOSE (parm))
    {
      last = மரம்_PURPOSE (parm);
      DECL_ARGUMENTS (fndecl) = last;

      க்கு (parm = மரம்_CHAIN (parm); parm; parm = மரம்_CHAIN (parm))
	எனில் (மரம்_PURPOSE (parm))
	  {
	    DECL_CHAIN (last) = மரம்_PURPOSE (parm);
	    last = மரம்_PURPOSE (parm);
	  }
      DECL_CHAIN (last) = NULL_மரம்;
    }

  /* If there was a previous prototype,
     set the DECL_ARG_TYPE of each argument according to
     the type previously specified, and report any mismatches.  */

  எனில் (current_function_prototype_arg_types)
    {
      மரம் type;
      க்கு (parm = DECL_ARGUMENTS (fndecl),
	     type = current_function_prototype_arg_types;
	   parm || (type != NULL_மரம்
		    && மரம்_மதிப்பு (type) != error_mark_முனை
		    && TYPE_MAIN_VARIANT (மரம்_மதிப்பு (type)) != void_type_முனை);
	   parm = DECL_CHAIN (parm), type = மரம்_CHAIN (type))
	{
	  எனில் (parm == NULL_மரம்
	      || type == NULL_மரம்
	      || (மரம்_மதிப்பு (type) != error_mark_முனை
		  && TYPE_MAIN_VARIANT (மரம்_மதிப்பு (type)) == void_type_முனை))
	    {
	      எனில் (current_function_prototype_built_in)
		warning_at (DECL_SOURCE_LOCATION (fndecl),
			    0, "number of arguments doesn%'t match "
			    "built-in prototype");
	      இல்லையெனில்
		{
		  /* FIXME diagnostics: This should be the location of
		     FNDECL, but there is bug when a prototype is
		     declared inside function context, but defined
		     outside of it (e.g., gcc.dg/pr15698-2.c).  In
		     which case FNDECL gets the location of the
		     prototype, not the definition.  */
		  error_at (உள்ளீடு_location,
			    "number of arguments doesn%'t match prototype");

		  error_at (current_function_prototype_locus,
			    "prototype declaration");
		}
	      நிறுத்து;
	    }
	  /* Type for passing arg must be consistent with that
	     declared for the arg.  ISO C says we take the unqualified
	     type for parameters declared with qualified type.  */
	  எனில் (மரம்_TYPE (parm) != error_mark_முனை
	      && மரம்_மதிப்பு (type) != error_mark_முனை
	      && ((TYPE_ATOMIC (DECL_ARG_TYPE (parm))
		   != TYPE_ATOMIC (மரம்_மதிப்பு (type)))
		  || !comptypes (TYPE_MAIN_VARIANT (DECL_ARG_TYPE (parm)),
				 TYPE_MAIN_VARIANT (மரம்_மதிப்பு (type)))))
	    {
	      எனில் ((TYPE_ATOMIC (DECL_ARG_TYPE (parm))
		   == TYPE_ATOMIC (மரம்_மதிப்பு (type)))
		  && (TYPE_MAIN_VARIANT (மரம்_TYPE (parm))
		      == TYPE_MAIN_VARIANT (மரம்_மதிப்பு (type))))
		{
		  /* Adjust argument to match prototype.  E.g. a previous
		     `int foo(float);' prototype causes
		     `int foo(x) float x; {...}' to be treated like
		     `int foo(float x) {...}'.  This is particularly
		     useful for argument types like uid_t.  */
		  DECL_ARG_TYPE (parm) = மரம்_TYPE (parm);

		  /* ??? Is it possible to get here with a
		     built-in prototype or will it always have
		     been diagnosed as conflicting with an
		     old-style definition and discarded?  */
		  எனில் (current_function_prototype_built_in)
		    warning_at (DECL_SOURCE_LOCATION (parm),
				OPT_Wpedantic, "promoted argument %qD "
				"doesn%'t match built-in prototype", parm);
		  இல்லையெனில்
		    {
		      pedwarn (DECL_SOURCE_LOCATION (parm),
			       OPT_Wpedantic, "promoted argument %qD "
			       "doesn%'t match prototype", parm);
		      pedwarn (current_function_prototype_locus, OPT_Wpedantic,
			       "prototype declaration");
		    }
		}
	      இல்லையெனில்
		{
		  எனில் (current_function_prototype_built_in)
		    warning_at (DECL_SOURCE_LOCATION (parm),
				0, "argument %qD doesn%'t match "
				"built-in prototype", parm);
		  இல்லையெனில்
		    {
		      error_at (DECL_SOURCE_LOCATION (parm),
				"argument %qD doesn%'t match prototype", parm);
		      error_at (current_function_prototype_locus,
				"prototype declaration");
		    }
		}
	    }
	}
      TYPE_ACTUAL_ARG_TYPES (மரம்_TYPE (fndecl)) = NULL_மரம்;
    }

  /* Otherwise, create a prototype that would match.  */

  இல்லையெனில்
    {
      மரம் actual = NULL_மரம், last = NULL_மரம், type;

      க்கு (parm = DECL_ARGUMENTS (fndecl); parm; parm = DECL_CHAIN (parm))
	{
	  type = மரம்_cons (NULL_மரம், DECL_ARG_TYPE (parm), NULL_மரம்);
	  எனில் (last)
	    மரம்_CHAIN (last) = type;
	  இல்லையெனில்
	    actual = type;
	  last = type;
	}
      type = மரம்_cons (NULL_மரம், void_type_முனை, NULL_மரம்);
      எனில் (last)
	மரம்_CHAIN (last) = type;
      இல்லையெனில்
	actual = type;

      /* We are going to assign a new value for the TYPE_ACTUAL_ARG_TYPES
	 of the type of this function, but we need to avoid having this
	 affect the types of other similarly-typed functions, so we must
	 first force the generation of an identical (but separate) type
	 node for the relevant function type.  The new node we create
	 will be a variant of the main variant of the original function
	 type.  */

      மரம்_TYPE (fndecl) = build_variant_type_copy (மரம்_TYPE (fndecl));

      TYPE_ACTUAL_ARG_TYPES (மரம்_TYPE (fndecl)) = actual;
    }
}

/* Store parameter declarations passed in ARG_INFO into the current
   function declaration.  */

வெறுமை
store_parm_decls_from (கட்டமைப்பு c_arg_info *arg_info)
{
  current_function_arg_info = arg_info;
  store_parm_decls ();
}

/* Called by walk_tree to look for and update context-less labels
   or labels with context in the parent function.  */

நிலையான மரம்
set_labels_context_r (மரம் *tp, முழு *walk_subtrees, வெறுமை *data)
{
  மரம் ctx = static_cast<மரம்>(data);
  எனில் (மரம்_CODE (*tp) == LABEL_கோவை
      && (DECL_CONTEXT (LABEL_கோவை_LABEL (*tp)) == NULL_மரம்
	  || DECL_CONTEXT (LABEL_கோவை_LABEL (*tp)) == DECL_CONTEXT (ctx)))
    {
      DECL_CONTEXT (LABEL_கோவை_LABEL (*tp)) = ctx;
      *walk_subtrees = 0;
    }

  திரும்பு NULL_மரம்;
}

/* Store the parameter declarations into the current function declaration.
   This is called after parsing the parameter declarations, before
   digesting the body of the function.

   For an old-style definition, construct a prototype out of the old-style
   parameter declarations and inject it into the function's type.  */

வெறுமை
store_parm_decls (வெறுமை)
{
  மரம் fndecl = current_function_decl;
  தருக்க proto;

  /* The argument information block for FNDECL.  */
  கட்டமைப்பு c_arg_info *arg_info = current_function_arg_info;
  current_function_arg_info = 0;

  /* True if this definition is written with a prototype.  In C23, an
     empty argument list was converted to (void) in grokparms; in
     older C standard versions, it does not give the function a type
     with a prototype for future calls.  */
  proto = arg_info->types != 0 || arg_info->no_named_args_stdarg_p;

  எனில் (proto)
    store_parm_decls_newstyle (fndecl, arg_info);
  இல்லையெனில்
    store_parm_decls_oldstyle (fndecl, arg_info);

  /* The next call to push_scope will be a function body.  */

  next_is_function_body = உண்மை;

  /* Write a record describing this function definition to the prototypes
     file (if requested).  */

  gen_aux_info_record (fndecl, 1, 0, proto);

  /* Initialize the RTL code for the function.  */
  allocate_struct_function (fndecl, பொய்);

  எனில் (warn_unused_local_typedefs)
    cfun->language = ggc_cleared_alloc<language_function> ();

  /* Begin the statement tree for this function.  */
  DECL_SAVED_மரம் (fndecl) = தள்ளு_stmt_list ();

  /* ??? Insert the contents of the pending sizes list into the function
     to be evaluated.  The only reason left to have this is
	void foo(int n, int array[n++])
     because we throw away the array type in favor of a pointer type, and
     thus won't naturally see the SAVE_EXPR containing the increment.  All
     other pending sizes would be handled by gimplify_parameters.  */
  எனில் (arg_info->pending_sizes)
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
      walk_மரம்_without_duplicates (&arg_info->pending_sizes,
				    set_labels_context_r, fndecl);
      add_stmt (arg_info->pending_sizes);
    }
}

/* Store PARM_DECLs in PARMS into scope temporarily.  Used for
   c_finish_omp_declare_simd for function prototypes.  No diagnostics
   should be done.  */

வெறுமை
temp_store_parm_decls (மரம் fndecl, மரம் parms)
{
  தள்ளு_scope ();
  க்கு (மரம் p = parms; p; p = DECL_CHAIN (p))
    {
      DECL_CONTEXT (p) = fndecl;
      எனில் (DECL_NAME (p))
	bind (DECL_NAME (p), p, current_scope,
	      /*invisible=*/பொய், /*nested=*/பொய்,
	      UNKNOWN_LOCATION);
    }
}

/* Undo what temp_store_parm_decls did.  */

வெறுமை
temp_எடு_parm_decls (வெறுமை)
{
  /* Clear all bindings in this temporary scope, so that
     pop_scope doesn't create a BLOCK.  */
  கட்டமைப்பு c_binding *b = current_scope->bindings;
  current_scope->bindings = வெற்று;
  க்கு (; b; b = free_binding_and_advance (b))
    {
      gcc_assert (மரம்_CODE (b->decl) == PARM_DECL
		  || b->decl == error_mark_முனை);
      gcc_assert (I_குறியீடு_BINDING (b->id) == b);
      I_குறியீடு_BINDING (b->id) = b->shadowed;
      எனில் (b->shadowed && b->shadowed->u.type)
	மரம்_TYPE (b->shadowed->decl) = b->shadowed->u.type;
    }
  எடு_scope ();
}


/* Finish up a function declaration and compile that function
   all the way to assembler language output.  Then free the storage
   for the function definition.

   This is called after parsing the body of the function definition.  */

வெறுமை
finish_function (location_t end_loc)
{
  மரம் fndecl = current_function_decl;

  எனில் (c_dialect_objc ())
    objc_finish_function ();

  எனில் (DECL_INITIAL (fndecl) && DECL_INITIAL (fndecl) != error_mark_முனை)
    BLOCK_SUPERCONTEXT (DECL_INITIAL (fndecl)) = fndecl;

  /* Must mark the RESULT_DECL as being in this function.  */

  எனில் (DECL_RESULT (fndecl) && DECL_RESULT (fndecl) != error_mark_முனை)
    DECL_CONTEXT (DECL_RESULT (fndecl)) = fndecl;

  எனில் (MAIN_NAME_P (DECL_NAME (fndecl)) && !மரம்_THIS_VOLATILE (fndecl)
      && TYPE_MAIN_VARIANT (மரம்_TYPE (மரம்_TYPE (fndecl)))
      == integer_type_முனை && flag_isoc99)
    {
      /* Hack.  We don't want the middle-end to warn that this return
	 is unreachable, so we mark its location as special.  Using
	 UNKNOWN_LOCATION has the problem that it gets clobbered in
	 annotate_one_with_locus.  A cleaner solution might be to
	 ensure ! should_carry_locus_p (stmt), but that needs a flag.
      */
      c_finish_return (BUILTINS_LOCATION, integer_zero_முனை, NULL_மரம்);
    }

  /* Tie off the statement tree for this function.  */
  DECL_SAVED_மரம் (fndecl) = எடு_stmt_list (DECL_SAVED_மரம் (fndecl));

  finish_fname_decls ();

  /* Complain if there's no return statement only if option specified on
     command line.  */
  எனில் (warn_return_type > 0
      && மரம்_CODE (மரம்_TYPE (மரம்_TYPE (fndecl))) != VOID_TYPE
      && !current_function_returns_மதிப்பு && !current_function_returns_null
      /* Don't complain if we are no-return.  */
      && !current_function_returns_abnormally
      /* Don't complain if we are declared noreturn.  */
      && !மரம்_THIS_VOLATILE (fndecl)
      /* Don't warn for main().  */
      && !MAIN_NAME_P (DECL_NAME (fndecl))
      /* Or if they didn't actually specify a return type.  */
      && !C_FUNCTION_IMPLICIT_INT (fndecl)
      /* Normally, with -Wreturn-type, flow will complain, but we might
         optimize out static functions.  */
      && !மரம்_PUBLIC (fndecl)
      && targetm.warn_func_return (fndecl)
      && warning (OPT_Wreturn_type,
		  "no return statement in function returning non-void"))
    suppress_warning (fndecl, OPT_Wreturn_type);

  /* Complain about parameters that are only set, but never otherwise used.  */
  எனில் (warn_unused_but_set_parameter)
    {
      மரம் decl;

      க்கு (decl = DECL_ARGUMENTS (fndecl);
	   decl;
	   decl = DECL_CHAIN (decl))
	எனில் (மரம்_USED (decl)
	    && மரம்_CODE (decl) == PARM_DECL
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
  எனில் (warn_unused_parameter)
    do_warn_unused_parameter (fndecl);

  /* Store the end of the function, so that we get good line number
     info for the epilogue.  */
  cfun->function_end_locus = end_loc;

  /* Finalize the ELF visibility for the function.  */
  c_determine_visibility (fndecl);

  /* For GNU C extern inline functions disregard inline limits.  */
  எனில் (DECL_EXTERNAL (fndecl)
      && DECL_DECLARED_INLINE_P (fndecl)
      && (flag_gnu89_inline
	  || lookup_attribute ("gnu_inline", DECL_ATTRIBUTES (fndecl))))
    DECL_DISREGARD_INLINE_LIMITS (fndecl) = 1;

  /* Genericize before inlining.  Delay genericizing nested functions
     until their parent function is genericized.  Since finalizing
     requires GENERIC, delay that as well.  */

  எனில் (DECL_INITIAL (fndecl) && DECL_INITIAL (fndecl) != error_mark_முனை
      && !undef_nested_function)
    {
      எனில் (!decl_function_context (fndecl))
	{
	  invoke_plugin_callbacks (PLUGIN_PRE_GENERICIZE, fndecl);
	  c_genericize (fndecl);

	  /* ??? Objc emits functions after finalizing the compilation unit.
	     This should be cleaned up later and this conditional removed.  */
	  எனில் (symtab->global_info_ready)
	    {
	      cgraph_முனை::add_new_function (fndecl, பொய்);
	      திரும்பு;
	    }
	  cgraph_முனை::finalize_function (fndecl, பொய்);
	}
      இல்லையெனில்
	{
	  /* Register this function with cgraph just far enough to get it
	    added to our parent's nested function list.  Handy, since the
	    C front end doesn't have such a list.  */
	  (வெறுமை) cgraph_முனை::get_create (fndecl);
	}
    }

  எனில் (!decl_function_context (fndecl))
    undef_nested_function = பொய்;

  எனில் (cfun->language != வெற்று)
    {
      ggc_free (cfun->language);
      cfun->language = வெற்று;
    }

  /* We're leaving the context of this function, so zap cfun.
     It's still in DECL_STRUCT_FUNCTION, and we'll restore it in
     tree_rest_of_compilation.  */
  set_cfun (வெற்று);
  invoke_plugin_callbacks (PLUGIN_FINISH_PARSE_FUNCTION, current_function_decl);
  current_function_decl = வெற்று;
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

மரம்
check_for_loop_decls (location_t loc, தருக்க turn_off_iso_c99_error)
{
  கட்டமைப்பு c_binding *b;
  மரம் one_decl = NULL_மரம்;
  முழு n_decls = 0;

  எனில் (!turn_off_iso_c99_error)
    {
      நிலையான தருக்க hint = உண்மை;
      /* If we get here, declarations have been used in a for loop without
	 the C99 for loop scope.  This doesn't make much sense, so don't
	 allow it.  */
      auto_diagnostic_group d;
      error_at (loc, "%<for%> loop initial declarations "
		"are only allowed in C99 or C11 mode");
      எனில் (hint)
	{
	  inform (loc,
		  "use option %<-std=c99%>, %<-std=gnu99%>, %<-std=c11%> or "
		  "%<-std=gnu11%> to compile your code");
	  hint = பொய்;
	}
      திரும்பு NULL_மரம்;
    }
  இல்லையெனில்
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

  க்கு (b = current_scope->bindings; b; b = b->prev)
    {
      மரம் id = b->id;
      மரம் decl = b->decl;

      எனில் (!id)
	தொடர்;

      தேர்வு (மரம்_CODE (decl))
	{
	நிலை VAR_DECL:
	  {
	    location_t decl_loc = DECL_SOURCE_LOCATION (decl);
	    எனில் (மரம்_STATIC (decl))
	      pedwarn_c11 (decl_loc, OPT_Wpedantic,
			   "declaration of static variable %qD in %<for%> "
			   "loop initial declaration", decl);
	    இல்லையெனில் எனில் (DECL_EXTERNAL (decl))
	      pedwarn_c11 (decl_loc, OPT_Wpedantic,
			   "declaration of %<extern%> variable %qD in %<for%> "
			   "loop initial declaration", decl);
	  }
	  நிறுத்து;

	நிலை RECORD_TYPE:
	  pedwarn_c11 (loc, OPT_Wpedantic,
		       "%<struct %E%> declared in %<for%> loop initial "
		       "declaration", id);
	  நிறுத்து;
	நிலை UNION_TYPE:
	  pedwarn_c11 (loc, OPT_Wpedantic,
		       "%<union %E%> declared in %<for%> loop initial "
		       "declaration",
		       id);
	  நிறுத்து;
	நிலை ENUMERAL_TYPE:
	  pedwarn_c11 (loc, OPT_Wpedantic,
		       "%<enum %E%> declared in %<for%> loop "
		       "initial declaration", id);
	  நிறுத்து;
	இயல்பு:
	  pedwarn_c11 (loc, OPT_Wpedantic, "declaration of non-variable "
		       "%qD in %<for%> loop initial declaration", decl);
	}

      n_decls++;
      one_decl = decl;
    }

  திரும்பு n_decls == 1 ? one_decl : NULL_மரம்;
}

/* Save and reinitialize the variables
   used during compilation of a C function.  */

வெறுமை
c_தள்ளு_function_context (வெறுமை)
{
  கட்டமைப்பு language_function *p = cfun->language;
  /* cfun->language might have been already allocated by the use of
     -Wunused-local-typedefs.  In that case, just re-use it.  */
  எனில் (p == வெற்று)
    cfun->language = p = ggc_cleared_alloc<language_function> ();

  p->base.x_stmt_மரம் = c_stmt_மரம்;
  c_stmt_மரம்.x_cur_stmt_list = vec_safe_copy (c_stmt_மரம்.x_cur_stmt_list);
  p->x_in_statement = in_statement;
  p->x_switch_அடுக்கு = c_switch_அடுக்கு;
  p->loop_names = loop_names;
  loop_names = vNULL;
  p->loop_names_hash = loop_names_hash;
  loop_names_hash = வெற்று;
  p->arg_info = current_function_arg_info;
  p->returns_மதிப்பு = current_function_returns_மதிப்பு;
  p->returns_null = current_function_returns_null;
  p->returns_abnormally = current_function_returns_abnormally;
  p->warn_about_return_type = warn_about_return_type;

  தள்ளு_function_context ();
}

/* Restore the variables used during compilation of a C function.  */

வெறுமை
c_எடு_function_context (வெறுமை)
{
  கட்டமைப்பு language_function *p;

  எடு_function_context ();
  p = cfun->language;

  /* When -Wunused-local-typedefs is in effect, cfun->languages is
     used to store data throughout the life time of the current cfun,
     So don't deallocate it.  */
  எனில் (!warn_unused_local_typedefs)
    cfun->language = வெற்று;

  எனில் (DECL_STRUCT_FUNCTION (current_function_decl) == 0
      && DECL_SAVED_மரம் (current_function_decl) == NULL_மரம்)
    {
      /* Stop pointing to the local nodes about to be freed.  */
      /* But DECL_INITIAL must remain nonzero so we know this
	 was an actual function definition.  */
      DECL_INITIAL (current_function_decl) = error_mark_முனை;
      DECL_ARGUMENTS (current_function_decl) = NULL_மரம்;
    }

  c_stmt_மரம் = p->base.x_stmt_மரம்;
  p->base.x_stmt_மரம்.x_cur_stmt_list = வெற்று;
  in_statement = p->x_in_statement;
  c_switch_அடுக்கு = p->x_switch_அடுக்கு;
  loop_names.release ();
  loop_names = p->loop_names;
  p->loop_names = vNULL;
  delete loop_names_hash;
  loop_names_hash = p->loop_names_hash;
  p->loop_names_hash = வெற்று;
  current_function_arg_info = p->arg_info;
  current_function_returns_மதிப்பு = p->returns_மதிப்பு;
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

stmt_மரம்
current_stmt_மரம் (வெறுமை)
{
  திரும்பு &c_stmt_மரம்;
}

/* Return the global value of T as a symbol.  */

மரம்
identifier_global_மதிப்பு	(மரம் t)
{
  கட்டமைப்பு c_binding *b;

  க்கு (b = I_குறியீடு_BINDING (t); b; b = b->shadowed)
    எனில் (B_IN_FILE_SCOPE (b) || B_IN_EXTERNAL_SCOPE (b))
      திரும்பு b->decl;

  திரும்பு NULL_மரம்;
}

/* Return the global value of tag T as a symbol.  */

மரம்
identifier_global_tag (மரம் t)
{
  கட்டமைப்பு c_binding *b;

  க்கு (b = I_TAG_BINDING (t); b; b = b->shadowed)
    எனில் (B_IN_FILE_SCOPE (b) || B_IN_EXTERNAL_SCOPE (b))
      திரும்பு b->decl;

  திரும்பு NULL_மரம்;
}

/* Returns non-zero (result of __has_builtin) if NAME refers to a built-in
   function or function-like operator.  */

முழு
names_builtin_p (மாறிலி எழுத்து *name)
{
  மரம் id = get_identifier (name);
  எனில் (மரம் decl = identifier_global_மதிப்பு (id))
    திரும்பு மரம்_CODE (decl) == FUNCTION_DECL && DECL_IS_UNDECLARED_BUILTIN (decl);

  /* Also detect common reserved C words that aren't strictly built-in
     functions.  */
  தேர்வு (C_RID_CODE (id))
    {
    நிலை RID_BUILTIN_ASSOC_BARRIER:
    நிலை RID_BUILTIN_BITREVERSEG:
    நிலை RID_BUILTIN_BSWAPG:
    நிலை RID_BUILTIN_CONVERTVECTOR:
    நிலை RID_BUILTIN_HAS_ATTRIBUTE:
    நிலை RID_BUILTIN_SHUFFLE:
    நிலை RID_BUILTIN_SHUFFLEVECTOR:
    நிலை RID_BUILTIN_STDC:
    நிலை RID_BUILTIN_COUNTED_BY_REF:
    நிலை RID_CHOOSE_கோவை:
    நிலை RID_OFFSETOF:
    நிலை RID_TYPES_COMPATIBLE_P:
    நிலை RID_C23_VA_START:
    நிலை RID_VA_ARG:
      திரும்பு 1;
    இயல்பு:
      நிறுத்து;
    }

  திரும்பு 0;
}

/* In C, the only C-linkage public declaration is at file scope.  */

மரம்
c_linkage_bindings (மரம் name)
{
  திரும்பு identifier_global_மதிப்பு (name);
}

/* Record a builtin type for C.  If NAME is non-NULL, it is the name used;
   otherwise the name is found in ridpointers from RID_INDEX.  */

வெறுமை
record_builtin_type (எண்ணிக்கை rid rid_index, மாறிலி எழுத்து *name, மரம் type)
{
  மரம் id, decl;
  எனில் (name == 0)
    id = ridpointers[(முழு) rid_index];
  இல்லையெனில்
    id = get_identifier (name);
  decl = build_decl (UNKNOWN_LOCATION, TYPE_DECL, id, type);
  pushdecl (decl);
  எனில் (debug_hooks->type_decl)
    debug_hooks->type_decl (decl, பொய்);
}

/* Return a c_parm structure with the given SPECS, ATTRS and DECLARATOR.  */

கட்டமைப்பு c_parm *
build_c_parm (கட்டமைப்பு c_declspecs *specs, மரம் attrs,
	      கட்டமைப்பு c_declarator *declarator,
	      location_t loc)
{
  கட்டமைப்பு c_parm *ret = XOBNEW (&parser_obstack, கட்டமைப்பு c_parm);
  ret->specs = specs;
  ret->attrs = attrs;
  ret->declarator = declarator;
  ret->loc = loc;
  திரும்பு ret;
}

/* Return a declarator with nested attributes.  TARGET is the inner
   declarator to which these attributes apply.  ATTRS are the
   attributes.  */

கட்டமைப்பு c_declarator *
build_attrs_declarator (மரம் attrs, கட்டமைப்பு c_declarator *target)
{
  கட்டமைப்பு c_declarator *ret = XOBNEW (&parser_obstack, கட்டமைப்பு c_declarator);
  ret->kind = cdk_attrs;
  ret->declarator = target;
  ret->u.attrs = attrs;
  திரும்பு ret;
}

/* Return a declarator for a function with arguments specified by ARGS
   and return type specified by TARGET.  */

கட்டமைப்பு c_declarator *
build_function_declarator (கட்டமைப்பு c_arg_info *args,
			   கட்டமைப்பு c_declarator *target)
{
  கட்டமைப்பு c_declarator *ret = XOBNEW (&parser_obstack, கட்டமைப்பு c_declarator);
  ret->kind = cdk_function;
  ret->declarator = target;
  ret->u.arg_info = args;
  திரும்பு ret;
}

/* Return a declarator for the identifier IDENT (which may be
   NULL_TREE for an abstract declarator).  */

கட்டமைப்பு c_declarator *
build_id_declarator (மரம் ident)
{
  கட்டமைப்பு c_declarator *ret = XOBNEW (&parser_obstack, கட்டமைப்பு c_declarator);
  ret->kind = cdk_id;
  ret->declarator = 0;
  ret->u.id.id = ident;
  ret->u.id.attrs = NULL_மரம்;
  /* Default value - may get reset to a more precise location. */
  ret->id_loc = உள்ளீடு_location;
  திரும்பு ret;
}

/* Return something to represent absolute declarators containing a *.
   TARGET is the absolute declarator that the * contains.
   TYPE_QUALS_ATTRS is a structure for type qualifiers and attributes
   to apply to the pointer type.  */

கட்டமைப்பு c_declarator *
make_pointer_declarator (கட்டமைப்பு c_declspecs *type_quals_attrs,
			 கட்டமைப்பு c_declarator *target)
{
  மரம் attrs;
  முழு quals = 0;
  கட்டமைப்பு c_declarator *itarget = target;
  கட்டமைப்பு c_declarator *ret = XOBNEW (&parser_obstack, கட்டமைப்பு c_declarator);
  எனில் (type_quals_attrs)
    {
      attrs = type_quals_attrs->attrs;
      quals = quals_from_declspecs (type_quals_attrs);
      எனில் (attrs != NULL_மரம்)
	itarget = build_attrs_declarator (attrs, target);
    }
  ret->kind = cdk_pointer;
  ret->declarator = itarget;
  ret->u.pointer_quals = quals;
  திரும்பு ret;
}

/* Return a pointer to a structure for an empty list of declaration
   specifiers.  */

கட்டமைப்பு c_declspecs *
build_null_declspecs (வெறுமை)
{
  கட்டமைப்பு c_declspecs *ret = XOBNEW (&parser_obstack, கட்டமைப்பு c_declspecs);
  memset (ret, 0, அளவு *ret);
  ret->align_log = -1;
  ret->typespec_word = cts_none;
  ret->storage_class = csc_none;
  ret->கோவை_const_operands = உண்மை;
  ret->typespec_kind = ctsk_none;
  ret->address_space = ADDR_SPACE_GENERIC;
  திரும்பு ret;
}

/* Add the address space ADDRSPACE to the declaration specifiers
   SPECS, returning SPECS.  */

கட்டமைப்பு c_declspecs *
declspecs_add_addrspace (location_t location,
			 கட்டமைப்பு c_declspecs *specs, addr_space_t as)
{
  specs->non_sc_seen_p = உண்மை;
  specs->declspecs_seen_p = உண்மை;
  specs->non_std_attrs_seen_p = உண்மை;

  எனில் (!ADDR_SPACE_GENERIC_P (specs->address_space)
      && specs->address_space != as)
    error ("incompatible address space qualifiers %qs and %qs",
	   c_addr_space_name (as),
	   c_addr_space_name (specs->address_space));
  இல்லையெனில்
    {
      specs->address_space = as;
      specs->locations[cdw_address_space] = location;
    }
  திரும்பு specs;
}

/* Add the type qualifier QUAL to the declaration specifiers SPECS,
   returning SPECS.  */

கட்டமைப்பு c_declspecs *
declspecs_add_qual (location_t loc,
		    கட்டமைப்பு c_declspecs *specs, மரம் qual)
{
  எண்ணிக்கை rid i;
  தருக்க dupe = பொய்;
  specs->non_sc_seen_p = உண்மை;
  specs->declspecs_seen_p = உண்மை;
  specs->non_std_attrs_seen_p = உண்மை;
  gcc_assert (மரம்_CODE (qual) == IDENTIFIER_முனை
	      && C_IS_RESERVED_WORD (qual));
  i = C_RID_CODE (qual);
  location_t prev_loc = UNKNOWN_LOCATION;
  தேர்வு (i)
    {
    நிலை RID_CONST:
      dupe = specs->const_p;
      specs->const_p = உண்மை;
      prev_loc = specs->locations[cdw_const];
      specs->locations[cdw_const] = loc;
      நிறுத்து;
    நிலை RID_VOLATILE:
      dupe = specs->volatile_p;
      specs->volatile_p = உண்மை;
      prev_loc = specs->locations[cdw_volatile];
      specs->locations[cdw_volatile] = loc;
      நிறுத்து;
    நிலை RID_RESTRICT:
      dupe = specs->restrict_p;
      specs->restrict_p = உண்மை;
      prev_loc = specs->locations[cdw_restrict];
      specs->locations[cdw_restrict] = loc;
      நிறுத்து;
    நிலை RID_ATOMIC:
      dupe = specs->atomic_p;
      specs->atomic_p = உண்மை;
      prev_loc = specs->locations[cdw_atomic];
      specs->locations[cdw_atomic] = loc;
      நிறுத்து;
    இயல்பு:
      gcc_unreachable ();
    }
  எனில் (dupe)
    {
      தருக்க warned = pedwarn_c90 (loc, OPT_Wpedantic,
				 "duplicate %qE declaration specifier", qual);
      எனில் (!warned
	  && warn_duplicate_decl_specifier
	  && prev_loc >= RESERVED_LOCATION_மொத்தம்
	  && !from_macro_expansion_at (prev_loc)
	  && !from_macro_expansion_at (loc))
	warning_at (loc, OPT_Wduplicate_decl_specifier,
		    "duplicate %qE declaration specifier", qual);
    }
  திரும்பு specs;
}

/* Add the type specifier TYPE to the declaration specifiers SPECS,
   returning SPECS.  */

கட்டமைப்பு c_declspecs *
declspecs_add_type (location_t loc, கட்டமைப்பு c_declspecs *specs,
		    கட்டமைப்பு c_typespec spec)
{
  மரம் type = spec.spec;
  specs->non_sc_seen_p = உண்மை;
  specs->declspecs_seen_p = உண்மை;
  specs->non_std_attrs_seen_p = உண்மை;
  specs->typespec_kind = spec.kind;
  எனில் (மரம்_DEPRECATED (type))
    specs->deprecated_p = உண்மை;
  எனில் (மரம்_UNAVAILABLE (type))
    specs->unavailable_p = உண்மை;

  /* As a type specifier is present, "auto" must be used as a storage
     class specifier, not for type deduction.  */
  எனில் (specs->c23_auto_p)
    {
      specs->c23_auto_p = பொய்;
      எனில் (specs->storage_class != csc_none)
	error ("multiple storage classes in declaration specifiers");
      இல்லையெனில் எனில் (specs->thread_p)
	error ("%qs used with %<auto%>",
	       specs->thread_gnu_p ? "__thread" : "_Thread_local");
      இல்லையெனில் எனில் (specs->constexpr_p)
	/* auto may only be used with another storage class specifier,
	   such as constexpr, if the type is inferred.  */
	error ("%<auto%> used with %<constexpr%>");
      இல்லையெனில்
	specs->storage_class = csc_auto;
    }

  /* Handle type specifier keywords.  */
  எனில் (மரம்_CODE (type) == IDENTIFIER_முனை
      && C_IS_RESERVED_WORD (type)
      && C_RID_CODE (type) != RID_CXX_COMPAT_WARN)
    {
      எண்ணிக்கை rid i = C_RID_CODE (type);
      எனில் (specs->type)
	{
	  error_at (loc, "two or more data types in declaration specifiers");
	  திரும்பு specs;
	}
      எனில் ((முழு) i <= (முழு) RID_LAST_MODIFIER)
	{
	  /* "long", "short", "signed", "unsigned", "_Complex" or "_Sat".  */
	  தருக்க dupe = பொய்;
	  தேர்வு (i)
	    {
	    நிலை RID_LONG:
	      எனில் (specs->long_long_p)
		{
		  error_at (loc, "%<long long long%> is too long for GCC");
		  நிறுத்து;
		}
	      எனில் (specs->long_p)
		{
		  எனில் (specs->typespec_word == cts_double)
		    {
		      error_at (loc,
				"both %qs and %qs in declaration specifiers",
				"long long", "double");
		      நிறுத்து;
		    }
		  pedwarn_c90 (loc, OPT_Wlong_long,
			       "ISO C90 does not support %<long long%>");
		  specs->long_long_p = 1;
		  specs->locations[cdw_long_long] = loc;
		  நிறுத்து;
		}
	      எனில் (specs->short_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "short");
	      இல்லையெனில் எனில் (specs->typespec_word == cts_auto_type)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "__auto_type");
	      இல்லையெனில் எனில் (specs->typespec_word == cts_void)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "void");
	      இல்லையெனில் எனில் (specs->typespec_word == cts_int_n)
		error_at (loc,
			  "both %qs and %<__int%d%> in declaration specifiers",
			  "long", int_n_data[specs->u.int_n_idx].bitsize);
	      இல்லையெனில் எனில் (specs->typespec_word == cts_bool)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "_Bool");
	      இல்லையெனில் எனில் (specs->typespec_word == cts_bitint)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "_BitInt");
	      இல்லையெனில் எனில் (specs->typespec_word == cts_char)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "char");
	      இல்லையெனில் எனில் (specs->typespec_word == cts_float)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "float");
	      இல்லையெனில் எனில் (specs->typespec_word == cts_floatn_nx)
		error_at (loc,
			  "both %qs and %<_Float%d%s%> in declaration "
			  "specifiers", "long",
			  floatn_nx_types[specs->u.floatn_nx_idx].n,
			  floatn_nx_types[specs->u.floatn_nx_idx].extended
			  ? "x"
			  : "");
	      இல்லையெனில் எனில் (specs->typespec_word == cts_dfloat32)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "_Decimal32");
	      இல்லையெனில் எனில் (specs->typespec_word == cts_dfloat64)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "_Decimal64");
	      இல்லையெனில் எனில் (specs->typespec_word == cts_dfloat128)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "_Decimal128");
	      இல்லையெனில் எனில் (specs->typespec_word == cts_dfloat64x)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "_Decimal64x");
	      இல்லையெனில்
		{
		  specs->long_p = உண்மை;
		  specs->locations[cdw_long] = loc;
		}
	      நிறுத்து;
	    நிலை RID_SHORT:
	      dupe = specs->short_p;
	      எனில் (specs->long_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "short");
	      இல்லையெனில் எனில் (specs->typespec_word == cts_auto_type)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "__auto_type");
	      இல்லையெனில் எனில் (specs->typespec_word == cts_void)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "void");
	      இல்லையெனில் எனில் (specs->typespec_word == cts_int_n)
		error_at (loc,
			  "both %qs and %<__int%d%> in declaration specifiers",
			  "short", int_n_data[specs->u.int_n_idx].bitsize);
	      இல்லையெனில் எனில் (specs->typespec_word == cts_bool)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "_Bool");
	      இல்லையெனில் எனில் (specs->typespec_word == cts_bitint)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "_BitInt");
	      இல்லையெனில் எனில் (specs->typespec_word == cts_char)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "char");
	      இல்லையெனில் எனில் (specs->typespec_word == cts_float)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "float");
	      இல்லையெனில் எனில் (specs->typespec_word == cts_double)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "double");
	      இல்லையெனில் எனில் (specs->typespec_word == cts_floatn_nx)
		error_at (loc,
			  "both %qs and %<_Float%d%s%> in declaration "
			  "specifiers", "short",
			  floatn_nx_types[specs->u.floatn_nx_idx].n,
			  floatn_nx_types[specs->u.floatn_nx_idx].extended
			  ? "x"
			  : "");
	      இல்லையெனில் எனில் (specs->typespec_word == cts_dfloat32)
                error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "_Decimal32");
	      இல்லையெனில் எனில் (specs->typespec_word == cts_dfloat64)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "_Decimal64");
	      இல்லையெனில் எனில் (specs->typespec_word == cts_dfloat128)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "_Decimal128");
	      இல்லையெனில் எனில் (specs->typespec_word == cts_dfloat64x)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "_Decimal64x");
	      இல்லையெனில்
		{
		  specs->short_p = உண்மை;
		  specs->locations[cdw_short] = loc;
		}
	      நிறுத்து;
	    நிலை RID_SIGNED:
	      dupe = specs->signed_p;
	      எனில் (specs->unsigned_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "unsigned");
	      இல்லையெனில் எனில் (specs->typespec_word == cts_auto_type)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "__auto_type");
	      இல்லையெனில் எனில் (specs->typespec_word == cts_void)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "void");
	      இல்லையெனில் எனில் (specs->typespec_word == cts_bool)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "_Bool");
	      இல்லையெனில் எனில் (specs->typespec_word == cts_float)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "float");
	      இல்லையெனில் எனில் (specs->typespec_word == cts_double)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "double");
	      இல்லையெனில் எனில் (specs->typespec_word == cts_floatn_nx)
		error_at (loc,
			  "both %qs and %<_Float%d%s%> in declaration "
			  "specifiers", "signed",
			  floatn_nx_types[specs->u.floatn_nx_idx].n,
			  floatn_nx_types[specs->u.floatn_nx_idx].extended
			  ? "x"
			  : "");
	      இல்லையெனில் எனில் (specs->typespec_word == cts_dfloat32)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "_Decimal32");
	      இல்லையெனில் எனில் (specs->typespec_word == cts_dfloat64)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "_Decimal64");
	      இல்லையெனில் எனில் (specs->typespec_word == cts_dfloat128)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "_Decimal128");
	      இல்லையெனில் எனில் (specs->typespec_word == cts_dfloat64x)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "_Decimal64x");
	      இல்லையெனில்
		{
		  specs->signed_p = உண்மை;
		  specs->locations[cdw_signed] = loc;
		}
	      நிறுத்து;
	    நிலை RID_UNSIGNED:
	      dupe = specs->unsigned_p;
	      எனில் (specs->signed_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "unsigned");
	      இல்லையெனில் எனில் (specs->typespec_word == cts_auto_type)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "__auto_type");
	      இல்லையெனில் எனில் (specs->typespec_word == cts_void)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "void");
	      இல்லையெனில் எனில் (specs->typespec_word == cts_bool)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "_Bool");
	      இல்லையெனில் எனில் (specs->typespec_word == cts_float)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "float");
	      இல்லையெனில் எனில் (specs->typespec_word == cts_double)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "double");
	      இல்லையெனில் எனில் (specs->typespec_word == cts_floatn_nx)
		error_at (loc,
			  "both %qs and %<_Float%d%s%> in declaration "
			  "specifiers", "unsigned",
			  floatn_nx_types[specs->u.floatn_nx_idx].n,
			  floatn_nx_types[specs->u.floatn_nx_idx].extended
			  ? "x"
			  : "");
              இல்லையெனில் எனில் (specs->typespec_word == cts_dfloat32)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "_Decimal32");
	      இல்லையெனில் எனில் (specs->typespec_word == cts_dfloat64)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "_Decimal64");
	      இல்லையெனில் எனில் (specs->typespec_word == cts_dfloat128)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "_Decimal128");
	      இல்லையெனில் எனில் (specs->typespec_word == cts_dfloat64x)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "_Decimal64x");
	      இல்லையெனில்
		{
		  specs->unsigned_p = உண்மை;
		  specs->locations[cdw_unsigned] = loc;
		}
	      நிறுத்து;
	    நிலை RID_COMPLEX:
	      dupe = specs->complex_p;
	      எனில் (!in_system_header_at (loc))
		pedwarn_c90 (loc, OPT_Wpedantic,
			     "ISO C90 does not support complex types");
	      எனில் (specs->typespec_word == cts_auto_type)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "__auto_type");
	      இல்லையெனில் எனில் (specs->typespec_word == cts_void)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "void");
	      இல்லையெனில் எனில் (specs->typespec_word == cts_bool)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "_Bool");
	      இல்லையெனில் எனில் (specs->typespec_word == cts_bitint)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "_BitInt");
              இல்லையெனில் எனில் (specs->typespec_word == cts_dfloat32)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "_Decimal32");
	      இல்லையெனில் எனில் (specs->typespec_word == cts_dfloat64)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "_Decimal64");
	      இல்லையெனில் எனில் (specs->typespec_word == cts_dfloat128)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "_Decimal128");
	      இல்லையெனில் எனில் (specs->typespec_word == cts_dfloat64x)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "_Decimal64x");
	      இல்லையெனில் எனில் (specs->typespec_word == cts_fract)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "_Fract");
	      இல்லையெனில் எனில் (specs->typespec_word == cts_accum)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "_Accum");
	      இல்லையெனில் எனில் (specs->saturating_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "_Sat");
	      இல்லையெனில்
		{
		  specs->complex_p = உண்மை;
		  specs->locations[cdw_complex] = loc;
		}
	      நிறுத்து;
	    நிலை RID_SAT:
	      dupe = specs->saturating_p;
	      pedwarn (loc, OPT_Wpedantic,
		       "ISO C does not support saturating types");
	      எனில் (specs->typespec_word == cts_int_n)
		error_at (loc,
			  "both %qs and %<__int%d%> in declaration specifiers",
			  "_Sat", int_n_data[specs->u.int_n_idx].bitsize);
	      இல்லையெனில் எனில் (specs->typespec_word == cts_auto_type)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "__auto_type");
	      இல்லையெனில் எனில் (specs->typespec_word == cts_void)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "void");
	      இல்லையெனில் எனில் (specs->typespec_word == cts_bool)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "_Bool");
	      இல்லையெனில் எனில் (specs->typespec_word == cts_bitint)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "_BitInt");
	      இல்லையெனில் எனில் (specs->typespec_word == cts_char)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "char");
	      இல்லையெனில் எனில் (specs->typespec_word == cts_int)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "int");
	      இல்லையெனில் எனில் (specs->typespec_word == cts_float)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "float");
	      இல்லையெனில் எனில் (specs->typespec_word == cts_double)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "double");
	      இல்லையெனில் எனில் (specs->typespec_word == cts_floatn_nx)
		error_at (loc,
			  "both %qs and %<_Float%d%s%> in declaration "
			  "specifiers", "_Sat",
			  floatn_nx_types[specs->u.floatn_nx_idx].n,
			  floatn_nx_types[specs->u.floatn_nx_idx].extended
			  ? "x"
			  : "");
              இல்லையெனில் எனில் (specs->typespec_word == cts_dfloat32)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "_Decimal32");
	      இல்லையெனில் எனில் (specs->typespec_word == cts_dfloat64)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "_Decimal64");
	      இல்லையெனில் எனில் (specs->typespec_word == cts_dfloat128)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "_Decimal128");
	      இல்லையெனில் எனில் (specs->typespec_word == cts_dfloat64x)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "_Decimal64x");
	      இல்லையெனில் எனில் (specs->complex_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "complex");
	      இல்லையெனில்
		{
		  specs->saturating_p = உண்மை;
		  specs->locations[cdw_saturating] = loc;
		}
	      நிறுத்து;
	    இயல்பு:
	      gcc_unreachable ();
	    }

	  எனில் (dupe)
	    error_at (loc, "duplicate %qE", type);

	  திரும்பு specs;
	}
      இல்லையெனில்
	{
	  /* "void", "_Bool", "char", "int", "float", "double",
	     "_FloatN", "_FloatNx", "_Decimal32", "__intN",
	     "_Decimal64", "_Decimal128", "_Fract", "_Accum", "_BitInt(N)" or
	     "__auto_type".  */
	  எனில் (specs->typespec_word != cts_none)
	    {
	      எனில் (i == RID_BOOL)
		{
		  auto_diagnostic_group d;
		  எனில் (specs->storage_class == csc_typedef)
		    error_at (loc,
			      "%qs cannot be defined via %<typedef%>",
			      IDENTIFIER_POINTER (type));
		  இல்லையெனில்
		    error_at (loc,
			      "%qs cannot be used here",
			      IDENTIFIER_POINTER (type));
		  add_note_about_new_keyword (loc, type);
		}
	      இல்லையெனில்
		error_at (loc,
			  "two or more data types in declaration specifiers");
	      திரும்பு specs;
	    }
	  தேர்வு (i)
	    {
	    நிலை RID_AUTO_TYPE:
	      எனில் (specs->long_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "__auto_type");
	      இல்லையெனில் எனில் (specs->short_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "__auto_type");
	      இல்லையெனில் எனில் (specs->signed_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "__auto_type");
	      இல்லையெனில் எனில் (specs->unsigned_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "__auto_type");
	      இல்லையெனில் எனில் (specs->complex_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "__auto_type");
	      இல்லையெனில் எனில் (specs->saturating_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "__auto_type");
	      இல்லையெனில்
		{
		  specs->typespec_word = cts_auto_type;
		  specs->locations[cdw_typespec] = loc;
		}
	      திரும்பு specs;
	    நிலை RID_INT_N_0:
	    நிலை RID_INT_N_1:
	    நிலை RID_INT_N_2:
	    நிலை RID_INT_N_3:
	      specs->u.int_n_idx = i - RID_INT_N_0;
	      எனில் (!in_system_header_at (உள்ளீடு_location)
		  /* If the INT_N type ends in "__", and so is of the format
		     "__intN__", don't pedwarn.  */
		  && (strncmp (IDENTIFIER_POINTER (type)
			       + (IDENTIFIER_LENGTH (type) - 2), "__", 2) != 0))
		pedwarn (loc, OPT_Wpedantic,
			 "ISO C does not support %<__int%d%> types",
			 int_n_data[specs->u.int_n_idx].bitsize);

	      எனில் (specs->long_p)
		error_at (loc,
			  "both %<__int%d%> and %qs in declaration specifiers",
			  int_n_data[specs->u.int_n_idx].bitsize, "long");
	      இல்லையெனில் எனில் (specs->saturating_p)
		error_at (loc,
			  "both %qs and %<__int%d%> in declaration specifiers",
			  "_Sat", int_n_data[specs->u.int_n_idx].bitsize);
	      இல்லையெனில் எனில் (specs->short_p)
		error_at (loc,
			  "both %<__int%d%> and %qs in declaration specifiers",
			  int_n_data[specs->u.int_n_idx].bitsize, "short");
	      இல்லையெனில் எனில் (! int_n_enabled_p[specs->u.int_n_idx])
		{
		  specs->typespec_word = cts_int_n;
		  error_at (loc,
			    "%<__int%d%> is not supported on this target",
			    int_n_data[specs->u.int_n_idx].bitsize);
		}
	      இல்லையெனில்
		{
		  specs->typespec_word = cts_int_n;
		  specs->locations[cdw_typespec] = loc;
		}
	      திரும்பு specs;
	    நிலை RID_VOID:
	      எனில் (specs->long_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "void");
	      இல்லையெனில் எனில் (specs->short_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "void");
	      இல்லையெனில் எனில் (specs->signed_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "void");
	      இல்லையெனில் எனில் (specs->unsigned_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "void");
	      இல்லையெனில் எனில் (specs->complex_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "void");
	      இல்லையெனில் எனில் (specs->saturating_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "void");
	      இல்லையெனில்
		{
		  specs->typespec_word = cts_void;
		  specs->locations[cdw_typespec] = loc;
		}
	      திரும்பு specs;
	    நிலை RID_BOOL:
	      எனில் (!in_system_header_at (loc))
		pedwarn_c90 (loc, OPT_Wpedantic,
			     "ISO C90 does not support boolean types");
	      எனில் (specs->long_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "_Bool");
	      இல்லையெனில் எனில் (specs->short_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "_Bool");
	      இல்லையெனில் எனில் (specs->signed_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "_Bool");
	      இல்லையெனில் எனில் (specs->unsigned_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "_Bool");
	      இல்லையெனில் எனில் (specs->complex_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "_Bool");
	      இல்லையெனில் எனில் (specs->saturating_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "_Bool");
	      இல்லையெனில்
		{
		  specs->typespec_word = cts_bool;
		  specs->locations[cdw_typespec] = loc;
		}
	      திரும்பு specs;
	    நிலை RID_CHAR:
	      எனில் (specs->long_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "char");
	      இல்லையெனில் எனில் (specs->short_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "char");
	      இல்லையெனில் எனில் (specs->saturating_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "char");
	      இல்லையெனில்
		{
		  specs->typespec_word = cts_char;
		  specs->locations[cdw_typespec] = loc;
		}
	      திரும்பு specs;
	    நிலை RID_INT:
	      எனில் (specs->saturating_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "int");
	      இல்லையெனில்
		{
		  specs->typespec_word = cts_int;
		  specs->locations[cdw_typespec] = loc;
		}
	      திரும்பு specs;
	    நிலை RID_FLOAT:
	      எனில் (specs->long_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "float");
	      இல்லையெனில் எனில் (specs->short_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "float");
	      இல்லையெனில் எனில் (specs->signed_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "float");
	      இல்லையெனில் எனில் (specs->unsigned_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "float");
	      இல்லையெனில் எனில் (specs->saturating_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "float");
	      இல்லையெனில்
		{
		  specs->typespec_word = cts_float;
		  specs->locations[cdw_typespec] = loc;
		}
	      திரும்பு specs;
	    நிலை RID_DOUBLE:
	      எனில் (specs->long_long_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long long", "double");
	      இல்லையெனில் எனில் (specs->short_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "double");
	      இல்லையெனில் எனில் (specs->signed_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "signed", "double");
	      இல்லையெனில் எனில் (specs->unsigned_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "unsigned", "double");
	      இல்லையெனில் எனில் (specs->saturating_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "double");
	      இல்லையெனில்
		{
		  specs->typespec_word = cts_double;
		  specs->locations[cdw_typespec] = loc;
		}
	      திரும்பு specs;
	    CASE_RID_FLOATN_NX:
	      specs->u.floatn_nx_idx = i - RID_FLOATN_NX_FIRST;
	      எனில் (!in_system_header_at (உள்ளீடு_location))
		pedwarn_c11 (loc, OPT_Wpedantic,
			     "ISO C does not support the %<_Float%d%s%> type"
			     " before C23",
			     floatn_nx_types[specs->u.floatn_nx_idx].n,
			     floatn_nx_types[specs->u.floatn_nx_idx].extended
			     ? "x"
			     : "");

	      எனில் (specs->long_p)
		error_at (loc,
			  "both %qs and %<_Float%d%s%> in declaration "
			  "specifiers", "long",
			  floatn_nx_types[specs->u.floatn_nx_idx].n,
			  floatn_nx_types[specs->u.floatn_nx_idx].extended
			  ? "x"
			  : "");
	      இல்லையெனில் எனில் (specs->short_p)
		error_at (loc,
			  "both %qs and %<_Float%d%s%> in declaration "
			  "specifiers", "short",
			  floatn_nx_types[specs->u.floatn_nx_idx].n,
			  floatn_nx_types[specs->u.floatn_nx_idx].extended
			  ? "x"
			  : "");
	      இல்லையெனில் எனில் (specs->signed_p)
		error_at (loc,
			  "both %qs and %<_Float%d%s%> in declaration "
			  "specifiers", "signed",
			  floatn_nx_types[specs->u.floatn_nx_idx].n,
			  floatn_nx_types[specs->u.floatn_nx_idx].extended
			  ? "x"
			  : "");
	      இல்லையெனில் எனில் (specs->unsigned_p)
		error_at (loc,
			  "both %qs and %<_Float%d%s%> in declaration "
			  "specifiers", "unsigned",
			  floatn_nx_types[specs->u.floatn_nx_idx].n,
			  floatn_nx_types[specs->u.floatn_nx_idx].extended
			  ? "x"
			  : "");
	      இல்லையெனில் எனில் (specs->saturating_p)
		error_at (loc,
			  "both %qs and %<_Float%d%s%> in declaration "
			  "specifiers", "_Sat",
			  floatn_nx_types[specs->u.floatn_nx_idx].n,
			  floatn_nx_types[specs->u.floatn_nx_idx].extended
			  ? "x"
			  : "");
	      இல்லையெனில் எனில் (FLOATN_NX_TYPE_முனை (specs->u.floatn_nx_idx) == NULL_மரம்)
		{
		  specs->typespec_word = cts_floatn_nx;
		  error_at (loc,
			    "%<_Float%d%s%> is not supported on this target",
			    floatn_nx_types[specs->u.floatn_nx_idx].n,
			    floatn_nx_types[specs->u.floatn_nx_idx].extended
			    ? "x"
			    : "");
		}
	      இல்லையெனில்
		{
		  specs->typespec_word = cts_floatn_nx;
		  specs->locations[cdw_typespec] = loc;
		}
	      திரும்பு specs;
	    நிலை RID_DFLOAT32:
	    நிலை RID_DFLOAT64:
	    நிலை RID_DFLOAT128:
	    நிலை RID_DFLOAT64X:
	      {
		மாறிலி எழுத்து *str;
		எனில் (i == RID_DFLOAT32)
		  str = "_Decimal32";
		இல்லையெனில் எனில் (i == RID_DFLOAT64)
		  str = "_Decimal64";
		இல்லையெனில் எனில் (i == RID_DFLOAT128)
		  str = "_Decimal128";
		இல்லையெனில்
		  str = "_Decimal64x";
		எனில் (specs->long_long_p)
		  error_at (loc,
			    "both %qs and %qs in declaration specifiers",
			    "long long", str);
		எனில் (specs->long_p)
		  error_at (loc,
			    "both %qs and %qs in declaration specifiers",
			    "long", str);
		இல்லையெனில் எனில் (specs->short_p)
		  error_at (loc,
			    "both %qs and %qs in declaration specifiers",
			    "short", str);
		இல்லையெனில் எனில் (specs->signed_p)
		  error_at (loc,
			    "both %qs and %qs in declaration specifiers",
			    "signed", str);
		இல்லையெனில் எனில் (specs->unsigned_p)
		  error_at (loc,
			    "both %qs and %qs in declaration specifiers",
			    "unsigned", str);
                இல்லையெனில் எனில் (specs->complex_p)
                  error_at (loc,
			    "both %qs and %qs in declaration specifiers",
			    "complex", str);
                இல்லையெனில் எனில் (specs->saturating_p)
                  error_at (loc,
			    "both %qs and %qs in declaration specifiers",
			    "_Sat", str);
		இல்லையெனில் எனில் (i == RID_DFLOAT32)
		  specs->typespec_word = cts_dfloat32;
		இல்லையெனில் எனில் (i == RID_DFLOAT64)
		  specs->typespec_word = cts_dfloat64;
		இல்லையெனில் எனில் (i == RID_DFLOAT128)
		  specs->typespec_word = cts_dfloat128;
		இல்லையெனில்
		  specs->typespec_word = cts_dfloat64x;
		specs->locations[cdw_typespec] = loc;
	      }
	      எனில் (!targetm.decimal_float_supported_p ())
		error_at (loc,
			  "decimal floating-point not supported "
			  "for this target");
	      pedwarn_c11 (loc, OPT_Wpedantic,
			   "ISO C does not support decimal floating-point "
			   "before C23");
	      திரும்பு specs;
	    நிலை RID_FRACT:
	    நிலை RID_ACCUM:
	      {
		மாறிலி எழுத்து *str;
		எனில் (i == RID_FRACT)
		  str = "_Fract";
		இல்லையெனில்
		  str = "_Accum";
                எனில் (specs->complex_p)
                  error_at (loc,
			    "both %qs and %qs in declaration specifiers",
			    "complex", str);
		இல்லையெனில் எனில் (i == RID_FRACT)
		    specs->typespec_word = cts_fract;
		இல்லையெனில்
		    specs->typespec_word = cts_accum;
		specs->locations[cdw_typespec] = loc;
	      }
	      எனில் (!targetm.fixed_point_supported_p ())
		error_at (loc,
			  "fixed-point types not supported for this target");
	      pedwarn (loc, OPT_Wpedantic,
		       "ISO C does not support fixed-point types");
	      திரும்பு specs;
	    நிலை RID_BITINT:
	      எனில் (specs->long_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "long", "_BitInt");
	      இல்லையெனில் எனில் (specs->short_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "short", "_BitInt");
	      இல்லையெனில் எனில் (specs->complex_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "complex", "_BitInt");
	      இல்லையெனில் எனில் (specs->saturating_p)
		error_at (loc,
			  "both %qs and %qs in declaration specifiers",
			  "_Sat", "_BitInt");
	      இல்லையெனில்
		{
		  specs->typespec_word = cts_bitint;
		  specs->locations[cdw_typespec] = loc;
		  specs->u.bitint_prec = -1;
		  எனில் (error_operand_p (spec.கோவை))
		    திரும்பு specs;
		  எனில் (மரம்_CODE (spec.கோவை) != INTEGER_CST
		      || !INTEGRAL_TYPE_P (மரம்_TYPE (spec.கோவை)))
		    {
		      error_at (loc, "%<_BitInt%> argument is not an integer "
				     "constant expression");
		      திரும்பு specs;
		    }
		  எனில் (மரம்_int_cst_sgn (spec.கோவை) <= 0)
		    {
		      error_at (loc, "%<_BitInt%> argument %qE is not a "
				     "positive integer constant expression",
				spec.கோவை);
		      திரும்பு specs;
		    }
		  எனில் (wi::to_widest (spec.கோவை) > WIDE_INT_MAX_PRECISION - 1)
		    {
		      error_at (loc, "%<_BitInt%> argument %qE is larger than "
				     "%<BITINT_MAXWIDTH%> %qd",
				spec.கோவை, (முழு) WIDE_INT_MAX_PRECISION - 1);
		      திரும்பு specs;
		    }
		  specs->u.bitint_prec = மரம்_to_uhwi (spec.கோவை);
		  கட்டமைப்பு bitint_info info;
		  எனில் (!targetm.c.bitint_type_info (specs->u.bitint_prec,
						   &info))
		    {
		      sorry_at (loc, "%<_BitInt(%d)%> is not supported on "
				     "this target", specs->u.bitint_prec);
		      specs->u.bitint_prec = -1;
		      திரும்பு specs;
		    }
		}
	      திரும்பு specs;
	    இயல்பு:
	      /* ObjC reserved word "id", handled below.  */
	      நிறுத்து;
	    }
	}
    }

  /* Now we have a typedef (a TYPE_DECL node), an identifier (some
     form of ObjC type, cases such as "int" and "long" being handled
     above), a TYPE (struct, union, enum and typeof specifiers) or an
     ERROR_MARK.  In none of these cases may there have previously
     been any type specifiers.  */
  எனில் (specs->type || specs->typespec_word != cts_none
      || specs->long_p || specs->short_p || specs->signed_p
      || specs->unsigned_p || specs->complex_p)
    error_at (loc, "two or more data types in declaration specifiers");
  இல்லையெனில் எனில் (மரம்_CODE (type) == TYPE_DECL)
    {
      specs->type = மரம்_TYPE (type);
      எனில் (மரம்_TYPE (type) != error_mark_முனை)
	{
	  mark_decl_used (type, பொய்);
	  specs->decl_attr = DECL_ATTRIBUTES (type);
	  specs->typedef_p = உண்மை;
	  specs->explicit_signed_p = C_TYPEDEF_EXPLICITLY_SIGNED (type);
	  specs->locations[cdw_typedef] = loc;

	  /* If this typedef name is defined in a struct, then a C++
	     lookup would return a different value.  */
	  எனில் (warn_cxx_compat
	      && I_குறியீடு_BINDING (DECL_NAME (type))->in_struct)
	    warning_at (loc, OPT_Wc___compat,
			"C++ lookup of %qD would return a field, not a type",
			type);

	  /* If we are parsing a struct, record that a struct field
	     used a typedef.  */
	  எனில் (warn_cxx_compat && struct_parse_info != வெற்று)
	    struct_parse_info->typedefs_seen.safe_தள்ளு (type);
	}
    }
  இல்லையெனில் எனில் (மரம்_CODE (type) == IDENTIFIER_முனை)
    {
      மரம் t = lookup_name (type);
      எனில் (!t || மரம்_CODE (t) != TYPE_DECL)
	error_at (loc, "%qE fails to be a typedef or built in type", type);
      இல்லையெனில் எனில் (மரம்_TYPE (t) == error_mark_முனை)
	;
      இல்லையெனில்
	{
	  specs->type = மரம்_TYPE (t);
	  specs->locations[cdw_typespec] = loc;
	}
    }
  இல்லையெனில்
    {
      எனில் (மரம்_CODE (type) != ERROR_MARK)
	{
	  எனில் (spec.kind == ctsk_typeof)
	    {
	      specs->typedef_p = உண்மை;
	      specs->locations[cdw_typedef] = loc;
	    }

	  எனில் (மரம்_CODE (type) == RECORD_TYPE || மரம்_CODE (type) == UNION_TYPE
	      || மரம்_CODE (type) == ENUMERAL_TYPE)
	    mark_decl_used (TYPE_STUB_DECL (type), பொய்);

	  எனில் (spec.கோவை)
	    {
	      மரம் கோவை = save_கோவை (fold_convert (void_type_முனை, spec.கோவை));
	      எனில் (specs->கோவை)
		specs->கோவை = build2 (COMPOUND_கோவை, மரம்_TYPE (கோவை),
				      specs->கோவை, கோவை);
	      இல்லையெனில்
		specs->கோவை = கோவை;
	      specs->கோவை_const_operands &= spec.கோவை_const_operands;
	    }
	}
      specs->type = type;
      எனில் (spec.has_enum_type_specifier
	  && spec.kind != ctsk_tagdef)
	specs->enum_type_specifier_ref_p = உண்மை;
    }

  திரும்பு specs;
}

/* Add the storage class specifier or function specifier SCSPEC to the
   declaration specifiers SPECS, returning SPECS.  */

கட்டமைப்பு c_declspecs *
declspecs_add_scspec (location_t loc,
		      கட்டமைப்பு c_declspecs *specs,
		      மரம் scspec)
{
  எண்ணிக்கை rid i;
  எண்ணிக்கை c_storage_class n = csc_none;
  தருக்க dupe = பொய்;
  specs->declspecs_seen_p = உண்மை;
  specs->non_std_attrs_seen_p = உண்மை;
  gcc_assert (மரம்_CODE (scspec) == IDENTIFIER_முனை
	      && C_IS_RESERVED_WORD (scspec));
  i = C_RID_CODE (scspec);
  எனில் (specs->non_sc_seen_p)
    warning (OPT_Wold_style_declaration,
             "%qE is not at beginning of declaration", scspec);
  தேர்வு (i)
    {
    நிலை RID_INLINE:
      /* C99 permits duplicate inline.  Although of doubtful utility,
	 it seems simplest to permit it in gnu89 mode as well, as
	 there is also little utility in maintaining this as a
	 difference between gnu89 and C99 inline.  */
      dupe = பொய்;
      specs->inline_p = உண்மை;
      specs->locations[cdw_inline] = loc;
      நிறுத்து;
    நிலை RID_NORETURN:
      /* Duplicate _Noreturn is permitted.  */
      dupe = பொய்;
      specs->noreturn_p = உண்மை;
      specs->locations[cdw_noreturn] = loc;
      நிறுத்து;
    நிலை RID_THREAD:
      dupe = specs->thread_p;
      எனில் (specs->storage_class == csc_auto)
	error ("%qE used with %<auto%>", scspec);
      இல்லையெனில் எனில் (specs->storage_class == csc_register)
	error ("%qE used with %<register%>", scspec);
      இல்லையெனில் எனில் (specs->storage_class == csc_typedef)
	error ("%qE used with %<typedef%>", scspec);
      இல்லையெனில் எனில் (specs->constexpr_p)
	error ("%qE used with %<constexpr%>", scspec);
      இல்லையெனில்
	{
	  specs->thread_p = உண்மை;
	  specs->thread_gnu_p = (strcmp (IDENTIFIER_POINTER (scspec),
					 "__thread") == 0);
	  /* A diagnostic is not required for the use of this
	     identifier in the implementation namespace; only diagnose
	     it for the C11 spelling because of existing code using
	     the other spelling.  */
	  எனில் (!specs->thread_gnu_p)
	    {
	      எனில் (flag_isoc99)
		pedwarn_c99 (loc, OPT_Wpedantic,
			     "ISO C99 does not support %qE", scspec);
	      இல்லையெனில்
		pedwarn_c99 (loc, OPT_Wpedantic,
			     "ISO C90 does not support %qE", scspec);
	    }
	  specs->locations[cdw_thread] = loc;
	}
      நிறுத்து;
    நிலை RID_AUTO:
      எனில் (flag_isoc23
	  && specs->typespec_kind == ctsk_none
	  && specs->storage_class != csc_typedef)
	{
	  /* "auto" potentially used for type deduction.  */
	  எனில் (specs->c23_auto_p)
	    error ("duplicate %qE", scspec);
	  specs->c23_auto_p = உண்மை;
	  திரும்பு specs;
	}
      n = csc_auto;
      /* auto may only be used with another storage class specifier,
	 such as constexpr, if the type is inferred.  */
      எனில் (specs->constexpr_p)
	error ("%qE used with %<constexpr%>", scspec);
      நிறுத்து;
    நிலை RID_EXTERN:
      n = csc_extern;
      /* Diagnose "__thread extern".  */
      எனில் (specs->thread_p && specs->thread_gnu_p)
	error ("%<__thread%> before %<extern%>");
      நிறுத்து;
    நிலை RID_REGISTER:
      n = csc_register;
      நிறுத்து;
    நிலை RID_STATIC:
      n = csc_static;
      /* Diagnose "__thread static".  */
      எனில் (specs->thread_p && specs->thread_gnu_p)
	error ("%<__thread%> before %<static%>");
      நிறுத்து;
    நிலை RID_TYPEDEF:
      n = csc_typedef;
      எனில் (specs->c23_auto_p)
	{
	  error ("%<typedef%> used with %<auto%>");
	  specs->c23_auto_p = பொய்;
	}
      நிறுத்து;
    நிலை RID_CONSTEXPR:
      dupe = specs->constexpr_p;
      எனில் (specs->storage_class == csc_extern)
	error ("%qE used with %<extern%>", scspec);
      இல்லையெனில் எனில் (specs->storage_class == csc_typedef)
	error ("%qE used with %<typedef%>", scspec);
      இல்லையெனில் எனில் (specs->storage_class == csc_auto)
	/* auto may only be used with another storage class specifier,
	   such as constexpr, if the type is inferred.  */
	error ("%qE used with %<auto%>", scspec);
      இல்லையெனில் எனில் (specs->thread_p)
	error ("%qE used with %qs", scspec,
	       specs->thread_gnu_p ? "__thread" : "_Thread_local");
      இல்லையெனில்
	specs->constexpr_p = உண்மை;
      நிறுத்து;
    இயல்பு:
      gcc_unreachable ();
    }
  எனில் (n != csc_none && n == specs->storage_class)
    dupe = உண்மை;
  எனில் (dupe)
    {
      எனில் (i == RID_THREAD)
	error ("duplicate %<_Thread_local%> or %<__thread%>");
      இல்லையெனில்
	error ("duplicate %qE", scspec);
    }
  எனில் (n != csc_none)
    {
      எனில் (specs->storage_class != csc_none && n != specs->storage_class)
	{
	  error ("multiple storage classes in declaration specifiers");
	}
      இல்லையெனில்
	{
	  specs->storage_class = n;
	  specs->locations[cdw_storage_class] = loc;
	  எனில் (n != csc_extern && n != csc_static && specs->thread_p)
	    {
	      error ("%qs used with %qE",
		     specs->thread_gnu_p ? "__thread" : "_Thread_local",
		     scspec);
	      specs->thread_p = பொய்;
	    }
	  எனில் (n != csc_auto && n != csc_register && n != csc_static
	      && specs->constexpr_p)
	    {
	      error ("%<constexpr%> used with %qE", scspec);
	      specs->constexpr_p = பொய்;
	    }
	}
    }
  திரும்பு specs;
}

/* Add the attributes ATTRS to the declaration specifiers SPECS,
   returning SPECS.  */

கட்டமைப்பு c_declspecs *
declspecs_add_attrs (location_t loc, கட்டமைப்பு c_declspecs *specs, மரம் attrs)
{
  specs->attrs = chainon (attrs, specs->attrs);
  specs->locations[cdw_attributes] = loc;
  specs->declspecs_seen_p = உண்மை;
  /* In the case of standard attributes at the start of the
     declaration, the caller will reset this.  */
  specs->non_std_attrs_seen_p = உண்மை;
  திரும்பு specs;
}

/* Add an _Alignas specifier (expression ALIGN, or type whose
   alignment is ALIGN) to the declaration specifiers SPECS, returning
   SPECS.  */
கட்டமைப்பு c_declspecs *
declspecs_add_alignas (location_t loc,
		       கட்டமைப்பு c_declspecs *specs, மரம் align)
{
  specs->alignas_p = உண்மை;
  specs->locations[cdw_alignas] = loc;
  எனில் (align == error_mark_முனை)
    திரும்பு specs;

  /* Only accept the alignment if it's valid and greater than
     the current one.  Zero is invalid but by C11 required to
     be silently ignored.  */
  முழு align_log = check_user_alignment (align, பொய், /* warn_zero = */பொய்);
  எனில் (align_log > specs->align_log)
    specs->align_log = align_log;
  திரும்பு specs;
}

/* Combine "long", "short", "signed", "unsigned" and "_Complex" type
   specifiers with any other type specifier to determine the resulting
   type.  This is where ISO C checks on complex types are made, since
   "_Complex long" is a prefix of the valid ISO C type "_Complex long
   double".  Also apply postfix standard attributes to modify the type.  */

கட்டமைப்பு c_declspecs *
finish_declspecs (கட்டமைப்பு c_declspecs *specs)
{
  /* If a type was specified as a whole, we have no modifiers and are
     done.  */
  எனில் (specs->type != NULL_மரம்)
    {
      gcc_assert (!specs->long_p && !specs->long_long_p && !specs->short_p
		  && !specs->signed_p && !specs->unsigned_p
		  && !specs->complex_p && !specs->c23_auto_p);

      /* Set a dummy type.  */
      எனில் (மரம்_CODE (specs->type) == ERROR_MARK)
        specs->type = integer_type_முனை;
      செல் handle_postfix_attrs;
    }

  /* If none of "void", "_Bool", "char", "int", "float" or "double"
     has been specified, treat it as "int" unless "_Complex" is
     present and there are no other specifiers.  If we just have
     "_Complex", it is equivalent to "_Complex double", but e.g.
     "_Complex short" is equivalent to "_Complex short int".  */
  எனில் (specs->typespec_word == cts_none)
    {
      எனில் (specs->saturating_p)
	{
	  error_at (specs->locations[cdw_saturating],
		    "%<_Sat%> is used without %<_Fract%> or %<_Accum%>");
	  எனில் (!targetm.fixed_point_supported_p ())
	    error_at (specs->locations[cdw_saturating],
		      "fixed-point types not supported for this target");
	  specs->typespec_word = cts_fract;
	}
      இல்லையெனில் எனில் (specs->long_p || specs->short_p
	       || specs->signed_p || specs->unsigned_p)
	{
	  specs->typespec_word = cts_int;
	}
      இல்லையெனில் எனில் (specs->complex_p)
	{
	  specs->typespec_word = cts_double;
	  pedwarn (specs->locations[cdw_complex], OPT_Wpedantic,
		   "ISO C does not support plain %<complex%> meaning "
		   "%<double complex%>");
	}
      இல்லையெனில் எனில் (specs->c23_auto_p)
	{
	  /* Type to be filled in later, including applying postfix
	     attributes.  This warning only actually appears for
	     -Wc11-c23-compat in C23 mode; in older modes, there may
	     be a warning or pedwarn for implicit "int" instead, or
	     other errors for use of auto at file scope.  */
	  pedwarn_c11 (உள்ளீடு_location, OPT_Wpedantic,
		       "ISO C does not support %<auto%> type deduction "
		       "before C23");
	  திரும்பு specs;
	}
      இல்லையெனில்
	{
	  specs->typespec_word = cts_int;
	  specs->default_int_p = உண்மை;
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
  தேர்வு (specs->typespec_word)
    {
    நிலை cts_auto_type:
      gcc_assert (!specs->long_p && !specs->short_p
		  && !specs->signed_p && !specs->unsigned_p
		  && !specs->complex_p);
      /* Type to be filled in later.  */
      எனில் (specs->postfix_attrs)
	error ("%<__auto_type%> followed by %<[[]]%> attributes");
      நிறுத்து;
    நிலை cts_void:
      gcc_assert (!specs->long_p && !specs->short_p
		  && !specs->signed_p && !specs->unsigned_p
		  && !specs->complex_p);
      specs->type = void_type_முனை;
      நிறுத்து;
    நிலை cts_bool:
      gcc_assert (!specs->long_p && !specs->short_p
		  && !specs->signed_p && !specs->unsigned_p
		  && !specs->complex_p);
      specs->type = boolean_type_முனை;
      நிறுத்து;
    நிலை cts_char:
      gcc_assert (!specs->long_p && !specs->short_p);
      gcc_assert (!(specs->signed_p && specs->unsigned_p));
      எனில் (specs->signed_p)
	specs->type = signed_char_type_முனை;
      இல்லையெனில் எனில் (specs->unsigned_p)
	specs->type = unsigned_char_type_முனை;
      இல்லையெனில்
	specs->type = char_type_முனை;
      எனில் (specs->complex_p)
	{
	  pedwarn (specs->locations[cdw_complex], OPT_Wpedantic,
		   "ISO C does not support complex integer types");
	  specs->type = build_complex_type (specs->type);
	}
      நிறுத்து;
    நிலை cts_int_n:
      gcc_assert (!specs->long_p && !specs->short_p && !specs->long_long_p);
      gcc_assert (!(specs->signed_p && specs->unsigned_p));
      எனில் (! int_n_enabled_p[specs->u.int_n_idx])
	specs->type = integer_type_முனை;
      இல்லையெனில்
	specs->type = (specs->unsigned_p
		       ? int_n_trees[specs->u.int_n_idx].unsigned_type
		       : int_n_trees[specs->u.int_n_idx].signed_type);
      எனில் (specs->complex_p)
	{
	  pedwarn (specs->locations[cdw_complex], OPT_Wpedantic,
		   "ISO C does not support complex integer types");
	  specs->type = build_complex_type (specs->type);
	}
      நிறுத்து;
    நிலை cts_int:
      gcc_assert (!(specs->long_p && specs->short_p));
      gcc_assert (!(specs->signed_p && specs->unsigned_p));
      எனில் (specs->long_long_p)
	specs->type = (specs->unsigned_p
		       ? long_long_unsigned_type_முனை
		       : long_long_integer_type_முனை);
      இல்லையெனில் எனில் (specs->long_p)
	specs->type = (specs->unsigned_p
		       ? long_unsigned_type_முனை
		       : long_integer_type_முனை);
      இல்லையெனில் எனில் (specs->short_p)
	specs->type = (specs->unsigned_p
		       ? short_unsigned_type_முனை
		       : short_integer_type_முனை);
      இல்லையெனில்
	specs->type = (specs->unsigned_p
		       ? unsigned_type_முனை
		       : integer_type_முனை);
      எனில் (specs->complex_p)
	{
	  pedwarn (specs->locations[cdw_complex], OPT_Wpedantic,
		   "ISO C does not support complex integer types");
	  specs->type = build_complex_type (specs->type);
	}
      நிறுத்து;
    நிலை cts_float:
      gcc_assert (!specs->long_p && !specs->short_p
		  && !specs->signed_p && !specs->unsigned_p);
      specs->type = (specs->complex_p
		     ? complex_float_type_முனை
		     : float_type_முனை);
      நிறுத்து;
    நிலை cts_double:
      gcc_assert (!specs->long_long_p && !specs->short_p
		  && !specs->signed_p && !specs->unsigned_p);
      எனில் (specs->long_p)
	{
	  specs->type = (specs->complex_p
			 ? complex_long_double_type_முனை
			 : long_double_type_முனை);
	}
      இல்லையெனில்
	{
	  specs->type = (specs->complex_p
			 ? complex_double_type_முனை
			 : double_type_முனை);
	}
      நிறுத்து;
    நிலை cts_floatn_nx:
      gcc_assert (!specs->long_p && !specs->short_p
		  && !specs->signed_p && !specs->unsigned_p);
      எனில் (FLOATN_NX_TYPE_முனை (specs->u.floatn_nx_idx) == NULL_மரம்)
	specs->type = integer_type_முனை;
      இல்லையெனில் எனில் (specs->complex_p)
	specs->type = COMPLEX_FLOATN_NX_TYPE_முனை (specs->u.floatn_nx_idx);
      இல்லையெனில்
	specs->type = FLOATN_NX_TYPE_முனை (specs->u.floatn_nx_idx);
      நிறுத்து;
    நிலை cts_dfloat32:
    நிலை cts_dfloat64:
    நிலை cts_dfloat128:
    நிலை cts_dfloat64x:
      gcc_assert (!specs->long_p && !specs->long_long_p && !specs->short_p
		  && !specs->signed_p && !specs->unsigned_p && !specs->complex_p);
      எனில் (!targetm.decimal_float_supported_p ())
	specs->type = integer_type_முனை;
      இல்லையெனில் எனில் (specs->typespec_word == cts_dfloat32)
	specs->type = dfloat32_type_முனை;
      இல்லையெனில் எனில் (specs->typespec_word == cts_dfloat64)
	specs->type = dfloat64_type_முனை;
      இல்லையெனில் எனில் (specs->typespec_word == cts_dfloat128)
	specs->type = dfloat128_type_முனை;
      இல்லையெனில்
	specs->type = dfloat64x_type_முனை;
      நிறுத்து;
    நிலை cts_fract:
      gcc_assert (!specs->complex_p);
      எனில் (!targetm.fixed_point_supported_p ())
	specs->type = integer_type_முனை;
      இல்லையெனில் எனில் (specs->saturating_p)
	{
	  எனில் (specs->long_long_p)
	    specs->type = specs->unsigned_p
			  ? sat_unsigned_long_long_fract_type_முனை
			  : sat_long_long_fract_type_முனை;
	  இல்லையெனில் எனில் (specs->long_p)
	    specs->type = specs->unsigned_p
			  ? sat_unsigned_long_fract_type_முனை
			  : sat_long_fract_type_முனை;
	  இல்லையெனில் எனில் (specs->short_p)
	    specs->type = specs->unsigned_p
			  ? sat_unsigned_short_fract_type_முனை
			  : sat_short_fract_type_முனை;
	  இல்லையெனில்
	    specs->type = specs->unsigned_p
			  ? sat_unsigned_fract_type_முனை
			  : sat_fract_type_முனை;
	}
      இல்லையெனில்
	{
	  எனில் (specs->long_long_p)
	    specs->type = specs->unsigned_p
			  ? unsigned_long_long_fract_type_முனை
			  : long_long_fract_type_முனை;
	  இல்லையெனில் எனில் (specs->long_p)
	    specs->type = specs->unsigned_p
			  ? unsigned_long_fract_type_முனை
			  : long_fract_type_முனை;
	  இல்லையெனில் எனில் (specs->short_p)
	    specs->type = specs->unsigned_p
			  ? unsigned_short_fract_type_முனை
			  : short_fract_type_முனை;
	  இல்லையெனில்
	    specs->type = specs->unsigned_p
			  ? unsigned_fract_type_முனை
			  : fract_type_முனை;
	}
      நிறுத்து;
    நிலை cts_accum:
      gcc_assert (!specs->complex_p);
      எனில் (!targetm.fixed_point_supported_p ())
	specs->type = integer_type_முனை;
      இல்லையெனில் எனில் (specs->saturating_p)
	{
	  எனில் (specs->long_long_p)
	    specs->type = specs->unsigned_p
			  ? sat_unsigned_long_long_accum_type_முனை
			  : sat_long_long_accum_type_முனை;
	  இல்லையெனில் எனில் (specs->long_p)
	    specs->type = specs->unsigned_p
			  ? sat_unsigned_long_accum_type_முனை
			  : sat_long_accum_type_முனை;
	  இல்லையெனில் எனில் (specs->short_p)
	    specs->type = specs->unsigned_p
			  ? sat_unsigned_short_accum_type_முனை
			  : sat_short_accum_type_முனை;
	  இல்லையெனில்
	    specs->type = specs->unsigned_p
			  ? sat_unsigned_accum_type_முனை
			  : sat_accum_type_முனை;
	}
      இல்லையெனில்
	{
	  எனில் (specs->long_long_p)
	    specs->type = specs->unsigned_p
			  ? unsigned_long_long_accum_type_முனை
			  : long_long_accum_type_முனை;
	  இல்லையெனில் எனில் (specs->long_p)
	    specs->type = specs->unsigned_p
			  ? unsigned_long_accum_type_முனை
			  : long_accum_type_முனை;
	  இல்லையெனில் எனில் (specs->short_p)
	    specs->type = specs->unsigned_p
			  ? unsigned_short_accum_type_முனை
			  : short_accum_type_முனை;
	  இல்லையெனில்
	    specs->type = specs->unsigned_p
			  ? unsigned_accum_type_முனை
			  : accum_type_முனை;
	}
      நிறுத்து;
    நிலை cts_bitint:
      gcc_assert (!specs->long_p && !specs->short_p
		  && !specs->complex_p);
      எனில் (!specs->unsigned_p && specs->u.bitint_prec == 1 && !flag_isoc2y)
	{
	  error_at (specs->locations[cdw_typespec],
		    "%<signed _BitInt%> argument must be at least 2 "
		    "before C2Y");
	  specs->type = integer_type_முனை;
	  நிறுத்து;
	}
      எனில் (specs->u.bitint_prec == -1)
	specs->type = integer_type_முனை;
      இல்லையெனில்
	{
	  pedwarn_c11 (specs->locations[cdw_typespec], OPT_Wpedantic,
		       "ISO C does not support %<%s_BitInt(%d)%> before C23",
		       specs->unsigned_p ? "unsigned "
		       : specs->signed_p ? "signed " : "",
		       specs->u.bitint_prec);
	  specs->type = build_bitint_type (specs->u.bitint_prec,
					   specs->unsigned_p);
	}
      நிறுத்து;
    இயல்பு:
      gcc_unreachable ();
    }
 handle_postfix_attrs:
  எனில் (specs->type != வெற்று)
    {
      specs->postfix_attrs
	= c_warn_type_attributes (specs->type, specs->postfix_attrs);
      decl_attributes (&specs->type, specs->postfix_attrs, 0);
      specs->postfix_attrs = NULL_மரம்;
    }

  திரும்பு specs;
}

/* Perform final processing on one file scope's declarations (or the
   external scope's declarations), GLOBALS.  */

நிலையான வெறுமை
c_write_global_declarations_1 (மரம் globals)
{
  மரம் decl;
  தருக்க reconsider;

  /* Process the decls in the order they were written.  */
  க்கு (decl = globals; decl; decl = DECL_CHAIN (decl))
    {
      /* Check for used but undefined static functions using the C
	 standard's definition of "used", and set TREE_NO_WARNING so
	 that check_global_declaration doesn't repeat the check.  */
      எனில் (மரம்_CODE (decl) == FUNCTION_DECL
	  && DECL_INITIAL (decl) == NULL_மரம்
	  && DECL_EXTERNAL (decl)
	  && !மரம்_PUBLIC (decl)
	  && !warning_suppressed_p (decl, OPT_Wunused))
	{
	  எனில் (C_DECL_USED (decl))
	    {
	      எனில் (pedwarn (உள்ளீடு_location, 0, "%q+F used but never defined",
			   decl))
		suppress_warning (decl, OPT_Wunused);
	    }
	  /* For -Wunused-function warn about unused static prototypes.  */
	  இல்லையெனில் எனில் (warn_unused_function
		   && ! DECL_ARTIFICIAL (decl)
		   && warning (OPT_Wunused_function,
			       "%q+F declared %<static%> but never defined",
			       decl))
	    suppress_warning (decl, OPT_Wunused);
	}

      wrapup_global_declaration_1 (decl);
    }

  செய்
    {
      reconsider = பொய்;
      க்கு (decl = globals; decl; decl = DECL_CHAIN (decl))
	reconsider |= wrapup_global_declaration_2 (decl);
    }
  போது (reconsider);
}

/* Preserve the external declarations scope across a garbage collect.  */
நிலையான GTY(()) மரம் ext_block;

/* Collect all references relevant to SOURCE_FILE.  */

நிலையான வெறுமை
collect_all_refs (மாறிலி எழுத்து *source_file)
{
  மரம் t;
  unsigned i;

  FOR_EACH_VEC_ELT (*all_translation_units, i, t)
    collect_ada_nodes (BLOCK_VARS (DECL_INITIAL (t)), source_file);

  collect_ada_nodes (BLOCK_VARS (ext_block), source_file);
}

/* Collect source file references at global level.  */

நிலையான வெறுமை
collect_source_refs (வெறுமை)
{
  மரம் t;
  மரம் decls;
  மரம் decl;
  unsigned i;

  FOR_EACH_VEC_ELT (*all_translation_units, i, t)
    {
      decls = DECL_INITIAL (t);
      க்கு (decl = BLOCK_VARS (decls); decl; decl = மரம்_CHAIN (decl))
	எனில் (!DECL_IS_UNDECLARED_BUILTIN (decl))
	  collect_source_ref (DECL_SOURCE_FILE (decl));
    }

  க்கு (decl = BLOCK_VARS (ext_block); decl; decl = மரம்_CHAIN (decl))
    எனில் (!DECL_IS_UNDECLARED_BUILTIN (decl))
      collect_source_ref (DECL_SOURCE_FILE (decl));
}

/* Free attribute access data that are not needed by the middle end. */

நிலையான வெறுமை
free_attr_access_data ()
{
  கட்டமைப்பு cgraph_முனை *n;

  /* Iterate over all functions declared in the translation unit.  */
  FOR_EACH_FUNCTION (n)
    {
      க்கு (மரம் parm = DECL_ARGUMENTS (n->decl); parm; parm = மரம்_CHAIN (parm))
	எனில் (மரம் attrs = DECL_ATTRIBUTES (parm))
	  attr_access::free_lang_data (attrs);

      மரம் fntype = மரம்_TYPE (n->decl);
      எனில் (!fntype || fntype == error_mark_முனை)
	தொடர்;
      மரம் attrs = TYPE_ATTRIBUTES (fntype);
      எனில் (!attrs)
	தொடர்;

      attr_access::free_lang_data (attrs);
    }
}

/* Perform any final parser cleanups and generate initial debugging
   information.  */

வெறுமை
c_parse_final_cleanups (வெறுமை)
{
  மரம் t;
  unsigned i;

  /* We don't want to do this if generating a PCH.  */
  எனில் (pch_file)
    திரும்பு;

  timevar_stop (TV_PHASE_PARSING);
  timevar_start (TV_PHASE_DEFERRED);

  /* Do the Objective-C stuff.  This is where all the Objective-C
     module stuff gets generated (symtab, class/protocol/selector
     lists etc).  */
  எனில் (c_dialect_objc ())
    objc_write_global_declarations ();

  /* Close the external scope.  */
  ext_block = எடு_scope ();
  external_scope = 0;
  gcc_assert (!current_scope);

  /* Handle -fdump-ada-spec[-slim]. */
  எனில் (flag_dump_ada_spec || flag_dump_ada_spec_slim)
    {
      /* Build a table of files to generate specs for */
      collect_source_ref (main_உள்ளீடு_filename);
      எனில் (!flag_dump_ada_spec_slim)
	collect_source_refs ();

      dump_ada_specs (collect_all_refs, வெற்று);
    }

  /* Process all file scopes in this compilation, and the external_scope,
     through wrapup_global_declarations.  */
  FOR_EACH_VEC_ELT (*all_translation_units, i, t)
    c_write_global_declarations_1 (BLOCK_VARS (DECL_INITIAL (t)));
  c_write_global_declarations_1 (BLOCK_VARS (ext_block));

  /* Call this to set cpp_implicit_aliases_done on all nodes.  This is
     important for function multiversioning aliases to get resolved.  */
  symtab->process_same_body_aliases ();

  எனில் (!in_lto_p)
    free_attr_access_data ();

  timevar_stop (TV_PHASE_DEFERRED);
  timevar_start (TV_PHASE_PARSING);

  ext_block = வெற்று;
}

/* Register reserved keyword WORD as qualifier for address space AS.  */

வெறுமை
c_register_addr_space (மாறிலி எழுத்து *word, addr_space_t as)
{
  முழு rid = RID_FIRST_ADDR_SPACE + as;
  மரம் id;

  /* Address space qualifiers are only supported
     in C with GNU extensions enabled.  */
  எனில் (c_dialect_objc () || flag_no_asm)
    திரும்பு;

  id = get_identifier (word);
  C_SET_RID_CODE (id, rid);
  C_IS_RESERVED_WORD (id) = 1;
  ridpointers [rid] = id;
}

/* Return identifier to look up for omp declare reduction.  */

மரம்
c_omp_reduction_id (எண்ணிக்கை மரம்_code reduction_code, மரம் reduction_id)
{
  மாறிலி எழுத்து *p = வெற்று;
  தேர்வு (reduction_code)
    {
    நிலை PLUS_கோவை: p = "+"; நிறுத்து;
    நிலை MULT_கோவை: p = "*"; நிறுத்து;
    நிலை MINUS_கோவை: p = "-"; நிறுத்து;
    நிலை BIT_AND_கோவை: p = "&"; நிறுத்து;
    நிலை BIT_XOR_கோவை: p = "^"; நிறுத்து;
    நிலை BIT_IOR_கோவை: p = "|"; நிறுத்து;
    நிலை TRUTH_ANDIF_கோவை: p = "&&"; நிறுத்து;
    நிலை TRUTH_ORIF_கோவை: p = "||"; நிறுத்து;
    நிலை MIN_கோவை: p = "min"; நிறுத்து;
    நிலை MAX_கோவை: p = "max"; நிறுத்து;
    இயல்பு:
      நிறுத்து;
    }

  எனில் (p == வெற்று)
    {
      எனில் (மரம்_CODE (reduction_id) != IDENTIFIER_முனை)
	திரும்பு error_mark_முனை;
      p = IDENTIFIER_POINTER (reduction_id);
    }

  மாறிலி எழுத்து prefix[] = "omp declare reduction ";
  size_t lenp = அளவு (prefix);
  size_t len = strlen (p);
  எழுத்து *name = XALLOCAVEC (எழுத்து, lenp + len);
  memcpy (name, prefix, lenp - 1);
  memcpy (name + lenp - 1, p, len + 1);
  திரும்பு get_identifier (name);
}

/* Lookup REDUCTION_ID in the current scope, or create an artificial
   VAR_DECL, bind it into the current scope and return it.  */

மரம்
c_omp_reduction_decl (மரம் reduction_id)
{
  கட்டமைப்பு c_binding *b = I_குறியீடு_BINDING (reduction_id);
  எனில் (b != வெற்று && B_IN_CURRENT_SCOPE (b))
    திரும்பு b->decl;

  மரம் decl = build_decl (BUILTINS_LOCATION, VAR_DECL,
			  reduction_id, integer_type_முனை);
  DECL_ARTIFICIAL (decl) = 1;
  DECL_EXTERNAL (decl) = 1;
  மரம்_STATIC (decl) = 1;
  மரம்_PUBLIC (decl) = 0;
  bind (reduction_id, decl, current_scope, உண்மை, பொய், BUILTINS_LOCATION);
  திரும்பு decl;
}

/* Lookup REDUCTION_ID in the first scope where it has entry for TYPE.  */

மரம்
c_omp_reduction_lookup (மரம் reduction_id, மரம் type)
{
  கட்டமைப்பு c_binding *b = I_குறியீடு_BINDING (reduction_id);
  போது (b)
    {
      மரம் t;
      க்கு (t = DECL_INITIAL (b->decl); t; t = மரம்_CHAIN (t))
	எனில் (comptypes (மரம்_PURPOSE (t), type))
	  திரும்பு மரம்_மதிப்பு (t);
      b = b->shadowed;
    }
  திரும்பு error_mark_முனை;
}

/* Helper function called via walk_tree, to diagnose invalid
   #pragma omp declare reduction combiners or initializers.  */

மரம்
c_check_omp_declare_reduction_r (மரம் *tp, முழு *, வெறுமை *data)
{
  மரம் *vars = (மரம் *) data;
  எனில் (SSA_VAR_P (*tp)
      && !DECL_ARTIFICIAL (*tp)
      && *tp != vars[0]
      && *tp != vars[1])
    {
      location_t loc = DECL_SOURCE_LOCATION (vars[0]);
      எனில் (strcmp (IDENTIFIER_POINTER (DECL_NAME (vars[0])), "omp_out") == 0)
	error_at (loc, "%<#pragma omp declare reduction%> combiner refers to "
		       "variable %qD which is not %<omp_out%> nor %<omp_in%>",
		  *tp);
      இல்லையெனில்
	error_at (loc, "%<#pragma omp declare reduction%> initializer refers "
		       "to variable %qD which is not %<omp_priv%> nor "
		       "%<omp_orig%>",
		  *tp);
      திரும்பு *tp;
    }
  திரும்பு NULL_மரம்;
}

/* Return identifier to look up for omp declare mapper.  */

மரம்
c_omp_mapper_id (மரம் mapper_id)
{
  மாறிலி எழுத்து *p = வெற்று;

  மாறிலி எழுத்து prefix[] = "omp declare mapper ";

  எனில் (mapper_id == NULL_மரம்)
    p = "<default>";
  இல்லையெனில் எனில் (மரம்_CODE (mapper_id) == IDENTIFIER_முனை)
    p = IDENTIFIER_POINTER (mapper_id);
  இல்லையெனில்
    திரும்பு error_mark_முனை;

  size_t lenp = அளவு (prefix);
  size_t len = strlen (p);
  எழுத்து *name = XALLOCAVEC (எழுத்து, lenp + len);
  memcpy (name, prefix, lenp - 1);
  memcpy (name + lenp - 1, p, len + 1);
  திரும்பு get_identifier (name);
}

/* Lookup MAPPER_ID in the current scope, or create an artificial
   VAR_DECL, bind it into the current scope and return it.  */

மரம்
c_omp_mapper_decl (மரம் mapper_id)
{
  கட்டமைப்பு c_binding *b = I_குறியீடு_BINDING (mapper_id);
  எனில் (b != வெற்று && B_IN_CURRENT_SCOPE (b))
    திரும்பு b->decl;

  மரம் decl = build_decl (BUILTINS_LOCATION, VAR_DECL,
			  mapper_id, integer_type_முனை);
  DECL_ARTIFICIAL (decl) = 1;
  DECL_EXTERNAL (decl) = 1;
  மரம்_STATIC (decl) = 1;
  மரம்_PUBLIC (decl) = 0;
  bind (mapper_id, decl, current_scope, உண்மை, பொய், BUILTINS_LOCATION);
  திரும்பு decl;
}

/* Lookup MAPPER_ID in the first scope where it has entry for TYPE.  */

மரம்
c_omp_mapper_lookup (மரம் mapper_id, மரம் type)
{
  எனில் (!RECORD_OR_UNION_TYPE_P (type))
    திரும்பு NULL_மரம்;

  mapper_id = c_omp_mapper_id (mapper_id);

  கட்டமைப்பு c_binding *b = I_குறியீடு_BINDING (mapper_id);
  போது (b)
    {
      மரம் t;
      க்கு (t = DECL_INITIAL (b->decl); t; t = மரம்_CHAIN (t))
	எனில் (comptypes (மரம்_PURPOSE (t), type))
	  திரும்பு மரம்_மதிப்பு (t);
      b = b->shadowed;
    }
  திரும்பு NULL_மரம்;
}

/* For C, we record a pointer to the mapper itself without wrapping it in an
   artificial function or similar.  So, just return it.  */

மரம்
c_omp_extract_mapper_directive (மரம் mapper)
{
  திரும்பு mapper;
}

/* For now we can handle singleton OMP_ARRAY_SECTIONs with custom mappers, but
   nothing more complicated.  */

மரம்
c_omp_map_array_section (location_t loc, மரம் t)
{
  மரம் கீழ் = மரம்_OPERAND (t, 1);
  மரம் len = மரம்_OPERAND (t, 2);

  எனில் (len && integer_onep (len))
    {
      t = மரம்_OPERAND (t, 0);

      எனில் (!கீழ்)
	கீழ் = integer_zero_முனை;

      t = build_array_ref (loc, t, கீழ்);
    }

  திரும்பு t;
}

/* Helper function for below function.  */

நிலையான மரம்
c_omp_scan_mapper_bindings_r (மரம் *tp, முழு *walk_subtrees, வெறுமை *ptr)
{
  மரம் t = *tp;
  omp_mapper_list<மரம்> *mlist = (omp_mapper_list<மரம்> *) ptr;
  மரம் aggr_type = NULL_மரம்;

  எனில் (மரம்_CODE (t) == SIZEOF_கோவை
      || மரம்_CODE (t) == ALIGNOF_கோவை)
    {
      *walk_subtrees = 0;
      திரும்பு NULL_மரம்;
    }

  எனில் (மரம்_CODE (t) == OMP_CLAUSE)
    திரும்பு NULL_மரம்;

  எனில் (மரம்_CODE (t) == COMPONENT_REF
      && RECORD_OR_UNION_TYPE_P (மரம்_TYPE (மரம்_OPERAND (t, 0))))
    aggr_type = மரம்_TYPE (மரம்_OPERAND (t, 0));
  இல்லையெனில் எனில் ((மரம்_CODE (t) == VAR_DECL
	    || மரம்_CODE (t) == PARM_DECL
	    || மரம்_CODE (t) == RESULT_DECL)
	   && RECORD_OR_UNION_TYPE_P (மரம்_TYPE (t)))
    aggr_type = மரம்_TYPE (t);

  எனில் (aggr_type)
    {
      மரம் mapper_fn = c_omp_mapper_lookup (NULL_மரம், aggr_type);
      எனில் (mapper_fn)
	mlist->add_mapper (NULL_மரம், aggr_type, mapper_fn);
    }

  திரும்பு NULL_மரம்;
}

/* Scan an offload region's body, and record uses of struct- or union-typed
   variables.  Add _mapper_binding_ fake clauses to *CLAUSES_PTR.  */

வெறுமை
c_omp_scan_mapper_bindings (location_t loc, மரம் *clauses_ptr, மரம் body)
{
  hash_set<omp_name_type<மரம்>> seen_types;
  auto_vec<மரம்> mappers;
  omp_mapper_list<மரம்> mlist (&seen_types, &mappers);

  walk_மரம்_without_duplicates (&body, c_omp_scan_mapper_bindings_r, &mlist);

  unsigned முழு i;
  மரம் mapper;
  FOR_EACH_VEC_ELT (mappers, i, mapper)
    c_omp_find_nested_mappers (&mlist, mapper);

  FOR_EACH_VEC_ELT (mappers, i, mapper)
    {
      எனில் (mapper == error_mark_முனை)
	தொடர்;
      மரம் mapper_name = OMP_DECLARE_MAPPER_ID (mapper);
      மரம் decl = OMP_DECLARE_MAPPER_DECL (mapper);

      மரம் c = build_omp_clause (loc, OMP_CLAUSE__MAPPER_BINDING_);
      OMP_CLAUSE__MAPPER_BINDING__ID (c) = mapper_name;
      OMP_CLAUSE__MAPPER_BINDING__DECL (c) = decl;
      OMP_CLAUSE__MAPPER_BINDING__MAPPER (c) = mapper;

      OMP_CLAUSE_CHAIN (c) = *clauses_ptr;
      *clauses_ptr = c;
    }
}

தருக்க
c_check_in_current_scope (மரம் decl)
{
  கட்டமைப்பு c_binding *b = I_குறியீடு_BINDING (DECL_NAME (decl));
  திரும்பு b != வெற்று && B_IN_CURRENT_SCOPE (b);
}

/* Search for loop or switch names.  BEFORE_LABELS is last statement before
   possible labels and SWITCH_P true for a switch, false for loops.
   Searches through last statements in cur_stmt_list, stops when seeing
   BEFORE_LABELs, or statement other than LABEL_EXPR or CASE_LABEL_EXPR.
   Returns number of loop/switch names found and if any are found, sets
   *LAST_P to the canonical loop/switch name LABEL_DECL.  */

முழு
c_get_loop_names (மரம் before_labels, தருக்க switch_p, மரம் *last_p)
{
  *last_p = NULL_மரம்;
  எனில் (!building_stmt_list_p ()
      || !STATEMENT_LIST_HAS_LABEL (cur_stmt_list)
      || before_labels == void_list_முனை)
    திரும்பு 0;

  முழு ret = 0;
  மரம் last = NULL_மரம்;
  க்கு (மரம்_stmt_iterator tsi = tsi_last (cur_stmt_list);
       !tsi_end_p (tsi); tsi_prev (&tsi))
    {
      மரம் stmt = tsi_stmt (tsi);
      எனில் (stmt == before_labels)
	நிறுத்து;
      இல்லையெனில் எனில் (மரம்_CODE (stmt) == LABEL_கோவை)
	{
	  எனில் (last == NULL_மரம்)
	    last = LABEL_கோவை_LABEL (stmt);
	  இல்லையெனில்
	    {
	      loop_names.safe_தள்ளு (LABEL_கோவை_LABEL (stmt));
	      ++ret;
	    }
	}
      இல்லையெனில் எனில் (மரம்_CODE (stmt) != CASE_LABEL_கோவை
	       && மரம்_CODE (stmt) != DEBUG_BEGIN_STMT)
	நிறுத்து;
    }
  எனில் (last)
    {
      எனில் (switch_p)
	C_DECL_SWITCH_NAME (last) = 1;
      இல்லையெனில்
	C_DECL_LOOP_NAME (last) = 1;
      loop_names.safe_தள்ளு (last);
      ++ret;
      எனில் (loop_names.length () > 16)
	{
	  unsigned முழு first = 0, i;
	  மரம் l, c = NULL_மரம்;
	  எனில் (loop_names_hash == வெற்று)
	    loop_names_hash = புதிய decl_மரம்_map (ret);
	  இல்லையெனில்
	    first = loop_names.length () - ret;
	  FOR_EACH_VEC_ELT_REVERSE (loop_names, i, l)
	    {
	      எனில் (C_DECL_LOOP_NAME (l) || C_DECL_SWITCH_NAME (l))
		c = l;
	      gcc_checking_assert (c);
	      loop_names_hash->put (l, c);
	      எனில் (i == first)
		நிறுத்து;
	    }
	}
      *last_p = last;
    }
  திரும்பு ret;
}

/* Undoes what get_loop_names did when it returned NUM_NAMES.  */

வெறுமை
c_release_loop_names (முழு இலக்கம்_names)
{
  unsigned len = loop_names.length () - இலக்கம்_names;
  எனில் (loop_names_hash)
    {
      எனில் (len <= 16)
	{
	  delete loop_names_hash;
	  loop_names_hash = வெற்று;
	}
      இல்லையெனில்
	{
	  unsigned முழு i;
	  மரம் l;
	  FOR_EACH_VEC_ELT_REVERSE (loop_names, i, l)
	    {
	      loop_names_hash->remove (l);
	      எனில் (i == len)
		நிறுத்து;
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

மரம்
c_finish_bc_name (location_t loc, மரம் name, தருக்க is_break)
{
  மரம் label = NULL_மரம், lab;
  pedwarn_c23 (loc, OPT_Wpedantic,
	       "ISO C does not support %qs statement with an identifier "
	       "operand before C2Y", is_break ? "break" : "continue");

  /* If I_LABEL_DECL is NULL or not from current function, don't waste time
     trying to find it among loop_names, it can't be there.  */
  எனில் (!loop_names.is_empty ()
      && current_function_scope
      && (lab = I_LABEL_DECL (name))
      && DECL_CONTEXT (lab) == current_function_decl)
    {
      unsigned முழு i;
      மரம் l, c = NULL_மரம்;
      எனில் (loop_names_hash)
	{
	  எனில் (மரம் *val = loop_names_hash->get (lab))
	    label = *val;
	}
      இல்லையெனில்
	FOR_EACH_VEC_ELT_REVERSE (loop_names, i, l)
	  {
	    எனில் (C_DECL_LOOP_NAME (l) || C_DECL_SWITCH_NAME (l))
	      c = l;
	    gcc_checking_assert (c);
	    எனில் (l == lab)
	      {
		label = c;
		நிறுத்து;
	      }
	  }
      எனில் (label)
	மரம்_USED (lab) = 1;
    }
  எனில் (label == NULL_மரம்)
    {
      auto_vec<மாறிலி எழுத்து *> candidates;
      unsigned முழு i;
      மரம் l, c = NULL_மரம்;
      FOR_EACH_VEC_ELT_REVERSE (loop_names, i, l)
	{
	  எனில் (C_DECL_LOOP_NAME (l) || C_DECL_SWITCH_NAME (l))
	    c = l;
	  gcc_checking_assert (c);
	  எனில் (is_break || C_DECL_LOOP_NAME (c))
	    candidates.safe_தள்ளு (IDENTIFIER_POINTER (DECL_NAME (l)));
	}
      மாறிலி எழுத்து *hint = find_closest_string (IDENTIFIER_POINTER (name),
					      &candidates);
      எனில் (hint)
	{
	  gcc_rich_location richloc (loc);
	  richloc.add_fixit_replace (hint);
	  எனில் (is_break)
	    error_at (&richloc, "%<break%> statement operand %qE does not "
				"refer to a named loop or %<switch%>; "
				"did you mean %qs?", name, hint);
	  இல்லையெனில்
	    error_at (&richloc, "%<continue%> statement operand %qE does not "
				"refer to a named loop; did you mean %qs?",
		      name, hint);
	}
      இல்லையெனில் எனில் (is_break)
	error_at (loc, "%<break%> statement operand %qE does not refer to a "
		       "named loop or %<switch%>", name);
      இல்லையெனில்
	error_at (loc, "%<continue%> statement operand %qE does not refer to "
		       "a named loop", name);
    }
  இல்லையெனில் எனில் (!C_DECL_LOOP_NAME (label) && !is_break)
    {
      auto_diagnostic_group d;
      error_at (loc, "%<continue%> statement operand %qE refers to a named "
		     "%<switch%>", name);
      inform (DECL_SOURCE_LOCATION (label), "%<switch%> name defined here");
      label = NULL_மரம்;
    }
  இல்லையெனில் எனில் (!C_DECL_LOOP_SWITCH_NAME_VALID (label))
    {
      auto_diagnostic_group d;
      எனில் (C_DECL_LOOP_NAME (label))
	{
	  error_at (loc, "%qs statement operand %qE refers to a loop outside "
			 "of its body", is_break ? "break" : "continue", name);
	  inform (DECL_SOURCE_LOCATION (label), "loop name defined here");
	}
      இல்லையெனில்
	{
	  error_at (loc, "%<break%> statement operand %qE refers to a "
			 "%<switch%> outside of its body", name);
	  inform (DECL_SOURCE_LOCATION (label),
		  "%<switch%> name defined here");
	}
      label = NULL_மரம்;
    }
  இல்லையெனில் எனில் (label == loop_names.last () && (in_statement & IN_NAMED_STMT) != 0)
    /* If it is just a fancy reference to the innermost construct, handle it
       just like break; or continue; though tracking cheaply what is the
       innermost loop for continue when nested in switches would require
       another global variable and updating it.  */
    label = NULL_மரம்;
  இல்லையெனில்
    C_DECL_LOOP_SWITCH_NAME_USED (label) = 1;
  திரும்பு label;
}

#அந்தர்பாவ "gt-c-c-decl.h"
