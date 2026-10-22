/* Definitions for C parsing and type checking.
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

#నిర్వచితం_కాకపోతే GCC_C_వృక్షం_H
#నిర్వచించు GCC_C_వృక్షం_H

#అన్తర్భావ "c-family/c-common.h"
#అన్తర్భావ "diagnostic.h"

/* struct lang_identifier is private to c-decl.cc, but langhooks.cc needs to
   know how big it is.  This is sanity-checked in c-decl.cc.  */
#నిర్వచించు C_SIZEOF_STRUCT_LANG_IDENTIFIER \
  (పరిమాణం (నిర్మాణం c_common_identifier) + 3 * పరిమాణం (శూన్య *))

/* In a RECORD_TYPE or UNION_TYPE, nonzero if any component is read-only.  */
#నిర్వచించు C_TYPE_FIELDS_READONLY(TYPE) వృక్షం_LANG_FLAG_1 (TYPE)

/* In a RECORD_TYPE or UNION_TYPE, nonzero if any component is volatile.  */
#నిర్వచించు C_TYPE_FIELDS_VOLATILE(TYPE) వృక్షం_LANG_FLAG_2 (TYPE)

/* In a RECORD_TYPE or UNION_TYPE, nonzero if any component is
   volatile, restrict-qualified or atomic; that is, has a type not
   permitted for a constexpr object.  */
#నిర్వచించు C_TYPE_FIELDS_NON_CONSTEXPR(TYPE) వృక్షం_LANG_FLAG_4 (TYPE)

/* In a RECORD_TYPE or UNION_TYPE, nonzero if any component has a
   counted_by attribute.  */
#నిర్వచించు C_TYPE_FIELDS_HAS_COUNTED_BY(TYPE) TYPE_LANG_FLAG_3 (TYPE)

/* In a RECORD_TYPE or UNION_TYPE or ENUMERAL_TYPE
   nonzero if the definition of the type has already started.  */
#నిర్వచించు C_TYPE_BEING_DEFINED(TYPE) TYPE_LANG_FLAG_0 (TYPE)

/* In an incomplete RECORD_TYPE, UNION_TYPE or ENUMERAL_TYPE, a list of
   variable declarations whose type would be completed by completing
   that type.  */
#నిర్వచించు C_TYPE_INCOMPLETE_VARS(TYPE) \
  TYPE_LANG_స్థానం_1 (వృక్షం_CHECK4 (TYPE, రికార్డు_TYPE, UNION_TYPE, \
				 QUAL_UNION_TYPE, ENUMERAL_TYPE))

/* In an IDENTIFIER_NODE, nonzero if this identifier is actually a
   keyword.  C_RID_CODE (node) is then the RID_* value of the keyword.  */
#నిర్వచించు C_IS_RESERVED_మాట(ID) వృక్షం_LANG_FLAG_0 (ID)

/* Record whether a type or decl was written with nonconstant size.
   Note that TYPE_SIZE may have simplified to a constant.  */
#నిర్వచించు C_TYPE_VARIABLE_కొలత(TYPE) TYPE_LANG_FLAG_1 (TYPE)
#నిర్వచించు C_DECL_VARIABLE_కొలత(TYPE) DECL_LANG_FLAG_0 (TYPE)

/* Record whether a type is variably modified. */
#నిర్వచించు C_TYPE_VARIABLY_MODIFIED(TYPE) TYPE_LANG_FLAG_6 (TYPE)


/* Record whether a type is defined inside a struct or union type.
   This is used for -Wc++-compat. */
#నిర్వచించు C_TYPE_DEFINED_లోపల_STRUCT(TYPE) TYPE_LANG_FLAG_2 (TYPE)

/* Record whether a typedef for type `int' was actually `signed int'.  */
#నిర్వచించు C_TYPEDEF_EXPLICITLY_SIGNED(EXP) DECL_LANG_FLAG_1 (EXP)

/* For a FUNCTION_DECL, nonzero if it was defined without an explicit
   return type.  */
#నిర్వచించు C_FUNCTION_IMPLICIT_INT(EXP) DECL_LANG_FLAG_1 (EXP)

/* For a FUNCTION_DECL, nonzero if it was an implicit declaration.  */
#నిర్వచించు C_DECL_IMPLICIT(EXP) DECL_LANG_FLAG_2 (EXP)

/* For a PARM_DECL, nonzero if it was declared as an array.  */
#నిర్వచించు C_ARRAY_PARAMETER(కణుపు_2) DECL_LANG_FLAG_0 (కణుపు_2)

/* For FUNCTION_DECLs, evaluates true if the decl is a nested
   function that requires a non-local context.  */
#నిర్వచించు C_FUNC_NONLOCAL_CONTEXT(EXP)		\
  DECL_LANG_FLAG_4 (FUNCTION_DECL_CHECK (EXP))

/* For FUNCTION_DECLs, evaluates true if the decl is built-in but has
   been declared.  */
#నిర్వచించు C_DECL_DECLARED_BUILTIN(EXP)		\
  DECL_LANG_FLAG_3 (FUNCTION_DECL_CHECK (EXP))

/* For FUNCTION_DECLs, evaluates true if the decl is built-in, has a
   built-in prototype and does not have a non-built-in prototype.  */
#నిర్వచించు C_DECL_BUILTIN_PROTOTYPE(EXP)		\
  DECL_LANG_FLAG_6 (FUNCTION_DECL_CHECK (EXP))

/* For LABEL_DECLs marks canonical name of a loop.  */
#నిర్వచించు C_DECL_LOOP_NAME(EXP) DECL_LANG_FLAG_3 (LABEL_DECL_CHECK (EXP))

/* For LABEL_DECLs marks canonical name of a switch.  During parsing of
   ObjC foreach named loop both C_DECL_LOOP_NAME and C_DECL_SWITCH_NAME
   are temporarily set.  */
#నిర్వచించు C_DECL_SWITCH_NAME(EXP) DECL_LANG_FLAG_5 (LABEL_DECL_CHECK (EXP))

/* For LABEL_DECLs marks canonical name of a loop or switch being
   valid for use in break identifier or continue identifier statements.  */
#నిర్వచించు C_DECL_LOOP_SWITCH_NAME_VALID(EXP) \
  DECL_LANG_FLAG_6 (LABEL_DECL_CHECK (EXP))

/* For LABEL_DECLs marks canonical loop or switch names which were actually
   used in one or more break identifier or continue identifier statements.  */
#నిర్వచించు C_DECL_LOOP_SWITCH_NAME_వాడిన(EXP) \
  DECL_LANG_FLAG_8 (LABEL_DECL_CHECK (EXP))

/* Record whether a decl was declared register.  This is strictly a
   front-end flag, whereas DECL_REGISTER is used for code generation;
   they may differ for structures with volatile fields.  */
#నిర్వచించు C_DECL_రిజిస్టరు(EXP) \
  DECL_LANG_FLAG_4 (వృక్షం_NOT_CHECK (EXP, FUNCTION_DECL))

/* Record whether a decl was used in an expression anywhere except an
   unevaluated operand of sizeof / typeof / alignof.  This is only
   used for functions declared static but not defined, though outside
   sizeof and typeof it is set for other function decls as well.  */
#నిర్వచించు C_DECL_వాడిన(EXP) DECL_LANG_FLAG_5 (FUNCTION_DECL_CHECK (EXP))

/* Record whether a variable has been declared threadprivate by
   #pragma omp threadprivate.  */
#నిర్వచించు C_DECL_THREADPRIVATE_P(DECL) DECL_LANG_FLAG_3 (VAR_DECL_CHECK (DECL))

/* Set on VAR_DECLs for compound literals.  */
#నిర్వచించు C_DECL_COMPOUND_LITERAL_P(DECL) \
  DECL_LANG_FLAG_5 (VAR_DECL_CHECK (DECL))

/* Set on decls used as placeholders for a C23 underspecified object
   definition.  */
#నిర్వచించు C_DECL_UNDERSPECIFIED(DECL) DECL_LANG_FLAG_7 (DECL)

/* Set on VAR_DECLs declared as 'constexpr'.  */
#నిర్వచించు C_DECL_DECLARED_CONSTEXPR(DECL) \
  DECL_LANG_FLAG_8 (VAR_DECL_CHECK (DECL))

/* Nonzero for a decl which either doesn't exist or isn't a prototype.
   N.B. Could be simplified if all built-in decls had complete prototypes
   (but this is presently difficult because some of them need FILE*).  */
#నిర్వచించు C_DECL_ISNT_PROTOTYPE(EXP)			\
       (EXP == 0					\
	|| (!prototype_p (వృక్షం_TYPE (EXP))	\
	    && !fndecl_built_లోపల_p (EXP)))

/* For FUNCTION_TYPE, a hidden list of types of arguments.  The same as
   TYPE_ARG_TYPES for functions with prototypes, but created for functions
   without prototypes.  */
#నిర్వచించు TYPE_ACTUAL_ARG_TYPES(కణుపు_2) \
  TYPE_LANG_స్థానం_1 (FUNCTION_TYPE_CHECK (కణుపు_2))

/* For a CONSTRUCTOR, whether some initializer contains a
   subexpression meaning it is not a constant expression.  */
#నిర్వచించు CONSTRUCTOR_NON_CONST(సమాసం_2) వృక్షం_LANG_FLAG_1 (CONSTRUCTOR_CHECK (సమాసం_2))

/* For a SAVE_EXPR, nonzero if the operand of the SAVE_EXPR has already
   been folded.  */
#నిర్వచించు SAVE_సమాసం_FOLDED_P(EXP)	వృక్షం_LANG_FLAG_1 (SAVE_సమాసం_CHECK (EXP))

/* Whether a type has boolean semantics: either a boolean type or an
   enumeration type with a boolean type as its underlying type.  */
#నిర్వచించు C_BOOLEAN_TYPE_P(TYPE)						\
  (వృక్షం_సంకేతం (TYPE) == BOOLEAN_TYPE					\
   || (వృక్షం_సంకేతం (TYPE) == ENUMERAL_TYPE				\
       && ENUM_UNDERLYING_TYPE (TYPE) != NULL_వృక్షం			\
       && (వృక్షం_సంకేతం (ENUM_UNDERLYING_TYPE (TYPE)) == BOOLEAN_TYPE	\
	   || c_hardbool_type_attr (TYPE))))

/* Record parser information about an expression that is irrelevant
   for code generation alongside a tree representing its value.  */
నిర్మాణం c_సమాసం
{
  /* The value of the expression.  */
  వృక్షం విలువ;
  /* Record the original unary/binary operator of an expression, which may
     have been changed by fold, STRING_CST for unparenthesized string
     constants, C_MAYBE_CONST_EXPR for __builtin_constant_p calls
     (even if parenthesized), for subexpressions, and for non-constant
     initializers, or ERROR_MARK for other expressions (including
     parenthesized expressions).  */
  గణన వృక్షం_సంకేతం_2 original_సంకేతం;
  /* If not NULL, the original type of an expression.  This will
     differ from the type of the value field for an enum constant.
     The type of an enum constant is a plain integer type, but this
     field will be the enum type.  */
  వృక్షం original_type;

  /* The source range of this expression.  This is redundant
     for node values that have locations, but not all node kinds
     have locations (e.g. constants, and references to params, locals,
     etc), so we stash a copy here.  */
  ఆధారం_range src_range;

  /* True if this was directly from a decimal constant token.  */
  bool m_decimal : 1;

  /* Access to the first and last locations within the source spelling
     of this expression.  */
  location_t get_ప్రారంభం () స్థిరరాశి { తిరిగి src_range.m_ప్రారంభం; }
  location_t get_ముగింపు () స్థిరరాశి { తిరిగి src_range.m_ముగింపు; }

  location_t get_location () స్థిరరాశి
  {
    ఒకవేళ (సమాసం_HAS_LOCATION (విలువ))
      తిరిగి సమాసం_LOCATION (విలువ);
    లేకపోతే
      తిరిగి make_location (get_ప్రారంభం (), get_ప్రారంభం (), get_ముగింపు ());
  }

  /* Set the value to error_mark_node whilst ensuring that src_range
     and m_decimal are initialized.  */
  శూన్య సమితి_error ()
  {
    విలువ = error_mark_కణుపు;
    src_range.m_ప్రారంభం = UNKNOWN_LOCATION;
    src_range.m_ముగింపు = UNKNOWN_LOCATION;
    m_decimal = 0;
  }
};

/* Type alias for struct c_expr. This allows to use the structure
   inside the VEC types.  */
రకనిర్వచనం నిర్మాణం c_సమాసం c_సమాసం_t;

/* A kind of type specifier.  Note that this information is currently
   only used to distinguish tag definitions, tag references and typeof
   uses.  */
గణన c_typespec_రకం {
  /* No typespec.  This appears only in struct c_declspec.  */
  ctsk_none,
  /* A reserved keyword type specifier.  */
  ctsk_resword,
  /* A reference to a tag, previously declared, such as "struct foo".
     This includes where the previous declaration was as a different
     kind of tag, in which case this is only valid if shadowing that
     tag in an inner scope.  */
  ctsk_tagref,
  /* Likewise, with standard attributes present in the reference.  */
  ctsk_tagref_attrs,
  /* A reference to a tag, not previously declared in a visible
     scope.  */
  ctsk_tagfirstref,
  /* Likewise, with standard attributes present in the reference.  */
  ctsk_tagfirstref_attrs,
  /* A definition of a tag such as "struct foo { int a; }".  */
  ctsk_tagdef,
  /* A typedef name.  */
  ctsk_typedef,
  /* An ObjC-specific kind of type specifier.  */
  ctsk_objc,
  /* A typeof specifier, or _Atomic ( type-name ).  */
  ctsk_typeof
};

/* A type specifier: this structure is created in the parser and
   passed to declspecs_add_type only.  */
నిర్మాణం c_typespec {
  /* What kind of type specifier this is.  */
  గణన c_typespec_రకం రకం;
  /* Whether the expression has operands suitable for use in constant
     expressions.  */
  bool సమాసం_const_operands;
  /* Whether the type specifier includes an enum type specifier (that
     is, ": specifier-qualifier-list" in a declaration using
     "enum").  */
  bool has_enum_type_specifier;
  /* The specifier itself.  */
  వృక్షం spec;
  /* An expression to be evaluated before the type specifier, in the
     case of typeof specifiers, or NULL otherwise or if no such
     expression is required for a particular typeof specifier.  In
     particular, when typeof is applied to an expression of variably
     modified type, that expression must be evaluated in order to
     determine array sizes that form part of the type, but the
     expression itself (as opposed to the array sizes) forms no part
     of the type and so needs to be recorded separately.  */
  వృక్షం సమాసం;
};

/* A storage class specifier.  */
గణన c_storage_class {
  csc_none,
  csc_auto,
  csc_extern,
  csc_రిజిస్టరు,
  csc_static,
  csc_typedef
};

/* A type specifier keyword "void", "_Bool", "char", "int", "float",
   "double", "_Decimal32", "_Decimal64", "_Decimal128", "_Decimal64x",
   "_Fract", "_Accum", "_BitInt", or none of these.  */
గణన c_typespec_keyword {
  cts_none,
  cts_void,
  cts_bool,
  cts_char,
  cts_int,
  cts_float,
  cts_int_n,
  cts_double,
  cts_dfloat32,
  cts_dfloat64,
  cts_dfloat128,
  cts_dfloat64x,
  cts_floatn_nx,
  cts_fract,
  cts_accum,
  cts_bitint,
  cts_auto_type
};

/* This enum lists all the possible declarator specifiers, storage
   class or attribute that a user can write.  There is at least one
   enumerator per possible declarator specifier in the struct
   c_declspecs below.

   It is used to index the array of declspec locations in struct
   c_declspecs.  */
గణన c_declspec_మాట {
  cdw_typespec /* A catch-all for a typespec.  */,
  cdw_storage_class  /* A catch-all for a storage class */,
  cdw_లక్షణాలు,
  cdw_typedef,
  cdw_explicit_signed,
  cdw_deprecated,
  cdw_default_int,
  cdw_long,
  cdw_long_long,
  cdw_short,
  cdw_signed,
  cdw_unsigned,
  cdw_complex,
  cdw_inline,
  cdw_noreturn,
  cdw_thread,
  cdw_const,
  cdw_volatile,
  cdw_restrict,
  cdw_atomic,
  cdw_saturating,
  cdw_alignas,
  cdw_చిరునామా_space,
  cdw_gimple,
  cdw_rtl,
  cdw_సంఖ్య_యొక్క_elements /* This one must always be the last
			    enumerator.  */
};

గణన c_declspec_il {
  cdil_none,
  cdil_gimple,		/* __GIMPLE  */
  cdil_gimple_cfg,	/* __GIMPLE(cfg)  */
  cdil_gimple_ssa,	/* __GIMPLE(ssa)  */
  cdil_rtl		/* __RTL  */
};

/* A sequence of declaration specifiers in C.  When a new declaration
   specifier is added, please update the enum c_declspec_word above
   accordingly.  */
నిర్మాణం c_declspecs {
  location_t locations[cdw_సంఖ్య_యొక్క_elements];
  /* The type specified, if a single type specifier such as a struct,
     union or enum specifier, typedef name or typeof specifies the
     whole type, or NULL_TREE if none or a keyword such as "void" or
     "char" is used.  Does not include qualifiers.  */
  వృక్షం type;
  /* Any expression to be evaluated before the type, from a typeof
     specifier.  */
  వృక్షం సమాసం;
  /* The attributes from a typedef decl.  */
  వృక్షం decl_attr;
  /* When parsing, the GNU attributes and prefix standard attributes.
     Outside the parser, this will be NULL; attributes (possibly from
     multiple lists) will be passed separately.  */
  వృక్షం attrs;
  /* When parsing, postfix standard attributes (which appertain to the
     type specified by the preceding declaration specifiers, unlike
     prefix standard attributes which appertain to the declaration or
     declarations as a whole).  */
  వృక్షం postfix_attrs;
  /* The pass to start compiling a __GIMPLE or __RTL function with.  */
  అక్షరం *gimple_or_rtl_pass;
  /* ENTRY BB count.  */
  profile_లెక్క నమోదు_bb_లెక్క;
  /* The base-2 log of the greatest alignment required by an _Alignas
     specifier, in bytes, or -1 if no such specifiers with nonzero
     alignment.  */
  పూర్ణాంకం align_log;
  సంఘం {
    /* For the __intN declspec, this stores the index into the int_n_*
       arrays.  */
    పూర్ణాంకం int_n_idx;
    /* For the _FloatN and _FloatNx declspec, this stores the index into
       the floatn_nx_types array.  */
    పూర్ణాంకం floatn_nx_idx;
    /* For _BitInt(N) this stores the N.  */
    పూర్ణాంకం bitint_prec;
  } u;
  /* The storage class specifier, or csc_none if none.  */
  గణన c_storage_class storage_class;
  /* Any type specifier keyword used such as "int", not reflecting
     modifiers such as "short", or cts_none if none.  */
  గణన c_typespec_keyword typespec_మాట : 8;
  /* The kind of type specifier if one has been seen, ctsk_none
     otherwise.  */
  గణన c_typespec_రకం typespec_రకం : 4;
  గణన c_declspec_il declspec_il : 3;
  /* Whether any expressions in typeof specifiers may appear in
     constant expressions.  */
  bool సమాసం_const_operands : 1;
  /* Whether any declaration specifiers have been seen at all.  */
  bool declspecs_చూసిన_p : 1;
  /* Whether any declaration specifiers other than standard attributes
     have been seen at all.  If only standard attributes have been
     seen, this is an attribute-declaration.  */
  bool non_std_attrs_చూసిన_p : 1;
  /* Whether something other than a storage class specifier or
     attribute has been seen.  This is used to warn for the
     obsolescent usage of storage class specifiers other than at the
     start of the list.  (Doing this properly would require function
     specifiers to be handled separately from storage class
     specifiers.)  */
  bool non_sc_చూసిన_p : 1;
  /* Whether the type is specified by a typedef or typeof name.  */
  bool typedef_p : 1;
  /* Whether the type is explicitly "signed" or specified by a typedef
     whose type is explicitly "signed".  */
  bool explicit_signed_p : 1;
  /* Whether the specifiers include a deprecated typedef.  */
  bool deprecated_p : 1;
  /* Whether the specifiers include an unavailable typedef.  */
  bool unavailable_p : 1;
  /* Whether the type defaulted to "int" because there were no type
     specifiers.  */
  bool default_int_p : 1;
  /* Whether "long" was specified.  */
  bool long_p : 1;
  /* Whether "long" was specified more than once.  */
  bool long_long_p : 1;
  /* Whether "short" was specified.  */
  bool short_p : 1;
  /* Whether "signed" was specified.  */
  bool signed_p : 1;
  /* Whether "unsigned" was specified.  */
  bool unsigned_p : 1;
  /* Whether "complex" was specified.  */
  bool complex_p : 1;
  /* Whether "inline" was specified.  */
  bool inline_p : 1;
  /* Whether "_Noreturn" was specified.  */
  bool noreturn_p : 1;
  /* Whether "__thread" or "_Thread_local" was specified.  */
  bool thread_p : 1;
  /* Whether "__thread" rather than "_Thread_local" was specified.  */
  bool thread_gnu_p : 1;
  /* Whether "const" was specified.  */
  bool const_p : 1;
  /* Whether "volatile" was specified.  */
  bool volatile_p : 1;
  /* Whether "restrict" was specified.  */
  bool restrict_p : 1;
  /* Whether "_Atomic" was specified.  */
  bool atomic_p : 1;
  /* Whether "_Sat" was specified.  */
  bool saturating_p : 1;
  /* Whether any alignment specifier (even with zero alignment) was
     specified.  */
  bool alignas_p : 1;
  /* Whether an enum type specifier (": specifier-qualifier-list") was
     specified other than in a definition of that enum (if so, this is
     invalid unless it is an empty declaration "enum identifier
     enum-type-specifier;", but such an empty declaration is valid in
     C23 when "enum identifier;" would not be).  */
  bool enum_type_specifier_ref_p : 1;
  /* Whether "auto" was specified in C23 (or later) mode and means the
     type is to be deduced from an initializer, or would mean that if
     no type specifier appears later in these declaration
     specifiers.  */
  bool c23_auto_p : 1;
  /* Whether "constexpr" was specified.  */
  bool constexpr_p : 1;
  /* The address space that the declaration belongs to.  */
  addr_space_t చిరునామా_space;
};

/* The various kinds of declarators in C.  */
గణన c_declarator_రకం {
  /* An identifier.  */
  cdk_id,
  /* A function.  */
  cdk_function,
  /* An array.  */
  cdk_array,
  /* A pointer.  */
  cdk_సూచిక,
  /* Parenthesized declarator with nested attributes.  */
  cdk_attrs
};

నిర్మాణం c_arg_ట్యాగ్ {
  /* The argument name.  */
  వృక్షం id;
  /* The type of the argument.  */
  వృక్షం type;
};


/* Information about the parameters in a function declarator.  */
నిర్మాణం c_arg_info {
  /* A list of parameter decls.  */
  వృక్షం parms;
  /* A list of structure, union and enum tags defined.  */
  vec<c_arg_ట్యాగ్, va_gc> *ట్యాగులు;
  /* A list of argument types to go in the FUNCTION_TYPE.  */
  వృక్షం types;
  /* A list of non-parameter decls (notably enumeration constants)
     defined with the parameters.  */
  వృక్షం others;
  /* A compound expression of VLA sizes from the parameters, or NULL.
     In a function definition, these are used to ensure that
     side-effects in sizes of arrays converted to pointers (such as a
     parameter int i[n++]) take place; otherwise, they are
     ignored.  */
  వృక్షం pending_sizes;
  /* True when these arguments had [*].  */
  bool had_vla_unspec : 1;
  /* True when the arguments are a (...) prototype.  */
  bool no_named_వాదనలు_stdarg_p : 1;
  /* True when empty parentheses have been interpreted as (void) in C23 or
     later.  This is only for use by -Wtraditional and is no longer needed if
     -Wtraditional is removed.  */
  bool c23_ఖాళీలు_parens : 1;
};

/* A declarator.  */
నిర్మాణం c_declarator {
  /* The kind of declarator.  */
  గణన c_declarator_రకం రకం;
  location_t id_loc; /* Currently only set for cdk_id, cdk_array. */
  /* Except for cdk_id, the contained declarator.  For cdk_id, NULL.  */
  నిర్మాణం c_declarator *declarator;
  సంఘం {
    /* For identifiers.  */
    నిర్మాణం {
      /* An IDENTIFIER_NODE, or NULL_TREE if an abstract
	 declarator.  */
      వృక్షం id;
      /* Any attributes (which apply to the declaration rather than to
	 the type described by the outer declarators).  */
      వృక్షం attrs;
    } id;
    /* For functions.  */
    నిర్మాణం c_arg_info *arg_info;
    /* For arrays.  */
    నిర్మాణం {
      /* The array dimension, or NULL for [] and [*].  */
      వృక్షం dimen;
      /* The qualifiers inside [].  */
      పూర్ణాంకం quals;
      /* The attributes (currently ignored) inside [].  */
      వృక్షం attrs;
      /* Whether [static] was used.  */
      bool static_p : 1;
      /* Whether [*] was used.  */
      bool vla_unspec_p : 1;
    } array;
    /* For pointers, the qualifiers on the pointer type.  */
    పూర్ణాంకం సూచిక_quals;
    /* For attributes.  */
    వృక్షం attrs;
  } u;
};

/* A type name.  */
నిర్మాణం c_type_name {
  /* The declaration specifiers.  */
  నిర్మాణం c_declspecs *specs;
  /* The declarator.  */
  నిర్మాణం c_declarator *declarator;
};

/* A parameter.  */
నిర్మాణం c_parm {
  /* The declaration specifiers, minus any prefix attributes.  */
  నిర్మాణం c_declspecs *specs;
  /* The attributes.  */
  వృక్షం attrs;
  /* The declarator.  */
  నిర్మాణం c_declarator *declarator;
  /* The location of the parameter.  */
  location_t loc;
};

/* Used when parsing an enum.  Initialized by start_enum.  */
నిర్మాణం c_enum_contents
{
  /* While defining an enum type, this is 1 plus the last enumerator
     constant value.  */
  వృక్షం enum_తదుపరి_విలువ;

  /* The enumeration type itself.  */
  వృక్షం enum_type;

  /* Nonzero means that there was overflow computing enum_next_value.  */
  పూర్ణాంకం enum_అధికప్రవాహం;
};

/* A type of reference to a static identifier in an inline
   function.  */
గణన c_inline_static_type {
  /* Identifier with internal linkage used in function that may be an
     inline definition (i.e., file-scope static).  */
  csi_అంతర్గత,
  /* Modifiable object with static storage duration defined in
     function that may be an inline definition (i.e., local
     static).  */
  csi_modifiable
};

/* Record details of decls possibly used inside sizeof or typeof.  */
నిర్మాణం maybe_వాడిన_decl
{
  /* The decl.  */
  వృక్షం decl;
  /* The level seen at (in_sizeof + in_typeof + in_countof + in_generic).  */
  పూర్ణాంకం level;
  /* Seen in address-of.  */
  bool చిరునామా;
  /* The next one at this level or above, or NULL.  */
  నిర్మాణం maybe_వాడిన_decl *తదుపరి;
};


/* in c-parser.cc */
నిర్మాణం c_వృక్షం_token_vec;
బాహ్య శూన్య c_parse_init (శూన్య);
బాహ్య bool c_keyword_starts_typename (గణన rid keyword);

/* in c-aux-info.cc */
బాహ్య శూన్య gen_aux_info_రికార్డు (వృక్షం, పూర్ణాంకం, పూర్ణాంకం, పూర్ణాంకం);

/* in c-decl.cc */
నిర్మాణం c_spot_bindings;
class c_struct_parse_info;
బాహ్య నిర్మాణం obstack parser_obstack;
/* Set to IN_ITERATION_STMT if parsing an iteration-statement,
   to IN_OMP_BLOCK if parsing OpenMP structured block and
   IN_OMP_FOR if parsing OpenMP loop.  If parsing a switch statement,
   this is bitwise ORed with IN_SWITCH_STMT, unless parsing an
   iteration-statement, OpenMP block or loop within that switch.
   If the innermost iteration/switch statement is named, IN_NAMED_STMT
   is additionally bitwise ORed into it.  */
#నిర్వచించు లోపల_SWITCH_STMT		1
#నిర్వచించు లోపల_ITERATION_STMT	2
#నిర్వచించు లోపల_OMP_ఖండం		4
#నిర్వచించు లోపల_OMP_FOR		8
#నిర్వచించు లోపల_OBJC_FOREACH		16
#నిర్వచించు లోపల_NAMED_STMT		32
బాహ్య గుర్తులేని అక్షరం లోపల_statement;

బాహ్య bool switch_statement_break_చూసిన_p;

బాహ్య bool global_bindings_p (శూన్య);
బాహ్య వృక్షం pushdecl (వృక్షం);
బాహ్య గుర్తులేని పూర్ణాంకం ప్రారంభం_underspecified_init (location_t, వృక్షం);
బాహ్య శూన్య ముగింపు_underspecified_init (వృక్షం, గుర్తులేని పూర్ణాంకం);
బాహ్య శూన్య నెట్టు_scope (శూన్య);
బాహ్య వృక్షం తీయి_scope (శూన్య);
బాహ్య శూన్య c_mark_decl_jump_unsafe_లోపల_current_scope ();
బాహ్య శూన్య c_bindings_ప్రారంభం_stmt_సమాసం (నిర్మాణం c_spot_bindings *);
బాహ్య శూన్య c_bindings_చివర_stmt_సమాసం (నిర్మాణం c_spot_bindings *);

బాహ్య శూన్య రికార్డు_inline_static (location_t, వృక్షం, వృక్షం,
				  గణన c_inline_static_type);
బాహ్య శూన్య c_init_decl_processing (శూన్య);
బాహ్య శూన్య c_print_identifier (FILE *, వృక్షం, పూర్ణాంకం);
బాహ్య పూర్ణాంకం quals_from_declspecs (స్థిరరాశి నిర్మాణం c_declspecs *);
బాహ్య నిర్మాణం c_declarator *build_array_declarator (location_t, వృక్షం,
    						    నిర్మాణం c_declspecs *,
						    bool, bool);
బాహ్య వృక్షం build_enumerator (location_t, location_t, నిర్మాణం c_enum_contents *,
			      వృక్షం, వృక్షం);
బాహ్య వృక్షం check_for_loop_decls (location_t, bool);
బాహ్య శూన్య mark_forward_parm_decls (శూన్య);
బాహ్య శూన్య declare_parm_level (శూన్య);
బాహ్య శూన్య undeclared_variable (location_t, వృక్షం);
బాహ్య వృక్షం lookup_label_for_goto (location_t, వృక్షం);
బాహ్య వృక్షం declare_label (వృక్షం);
బాహ్య వృక్షం define_label (location_t, వృక్షం);
బాహ్య నిర్మాణం c_spot_bindings *c_get_switch_bindings (శూన్య);
బాహ్య శూన్య c_release_switch_bindings (నిర్మాణం c_spot_bindings *);
బాహ్య bool c_check_switch_jump_warnings (నిర్మాణం c_spot_bindings *,
					  location_t, location_t);
బాహ్య శూన్య ముగింపు_decl (వృక్షం, location_t, వృక్షం, వృక్షం, వృక్షం);
బాహ్య వృక్షం ముగింపు_enum (వృక్షం, వృక్షం, వృక్షం);
బాహ్య శూన్య ముగింపు_function (location_t = ఆదానం_location);
బాహ్య వృక్షం ముగింపు_struct (location_t, వృక్షం, వృక్షం, వృక్షం,
			   class c_struct_parse_info *,
			   వృక్షం *సమాసం = ఖాళీ);
బాహ్య వృక్షం c_simulate_enum_decl (location_t, స్థిరరాశి అక్షరం *,
				  vec<string_int_pair> *);
బాహ్య వృక్షం c_simulate_రికార్డు_decl (location_t, స్థిరరాశి అక్షరం *,
				    array_ముక్క<స్థిరరాశి వృక్షం>);
బాహ్య నిర్మాణం c_arg_info *build_arg_info (శూన్య);
బాహ్య నిర్మాణం c_arg_info *get_parm_info (bool, వృక్షం);
బాహ్య వృక్షం grokfield (location_t, నిర్మాణం c_declarator *,
		       నిర్మాణం c_declspecs *, వృక్షం, వృక్షం *, వృక్షం *);
బాహ్య వృక్షం groktypename (నిర్మాణం c_type_name *, వృక్షం *, bool *);
బాహ్య వృక్షం grokgenassoc (నిర్మాణం c_type_name *);
బాహ్య వృక్షం grokparm (స్థిరరాశి నిర్మాణం c_parm *, వృక్షం *);
బాహ్య వృక్షం implicitly_declare (location_t, వృక్షం);
బాహ్య శూన్య keep_తదుపరి_level (శూన్య);
బాహ్య శూన్య pending_xref_error (శూన్య);
బాహ్య శూన్య c_నెట్టు_function_context (శూన్య);
బాహ్య శూన్య c_తీయి_function_context (శూన్య);
బాహ్య శూన్య నెట్టు_parm_decl (స్థిరరాశి నిర్మాణం c_parm *, వృక్షం *);
బాహ్య నిర్మాణం c_declarator *సమితి_array_declarator_inner (నిర్మాణం c_declarator *,
							నిర్మాణం c_declarator *);
బాహ్య వృక్షం c_builtin_function (వృక్షం);
బాహ్య వృక్షం c_builtin_function_ext_scope (వృక్షం);
బాహ్య వృక్షం c_simulate_builtin_function_decl (వృక్షం);
బాహ్య శూన్య c_warn_వాడని_లక్షణాలు (వృక్షం);
బాహ్య వృక్షం c_warn_type_లక్షణాలు (వృక్షం, వృక్షం);
బాహ్య శూన్య shadow_ట్యాగ్ (స్థిరరాశి నిర్మాణం c_declspecs *);
బాహ్య శూన్య shadow_ట్యాగ్_warned (స్థిరరాశి నిర్మాణం c_declspecs *, పూర్ణాంకం);
బాహ్య వృక్షం ప్రారంభం_enum (location_t, నిర్మాణం c_enum_contents *, వృక్షం, వృక్షం,
			bool potential_nesting_p);
బాహ్య bool ప్రారంభం_function (నిర్మాణం c_declspecs *, నిర్మాణం c_declarator *, వృక్షం);
బాహ్య వృక్షం ప్రారంభం_decl (నిర్మాణం c_declarator *, నిర్మాణం c_declspecs *, bool,
			వృక్షం, bool = true, location_t * = ఖాళీ);
బాహ్య వృక్షం ప్రారంభం_struct (location_t, గణన వృక్షం_సంకేతం_2, వృక్షం,
			  class c_struct_parse_info **);
బాహ్య శూన్య store_parm_decls (శూన్య);
బాహ్య శూన్య store_parm_decls_from (నిర్మాణం c_arg_info *);
బాహ్య శూన్య తాత్కాలిక_store_parm_decls (వృక్షం, వృక్షం);
బాహ్య శూన్య తాత్కాలిక_తీయి_parm_decls (శూన్య);
బాహ్య వృక్షం xref_ట్యాగ్ (గణన వృక్షం_సంకేతం_2, వృక్షం);
బాహ్య నిర్మాణం c_typespec parser_xref_ట్యాగ్ (location_t, గణన వృక్షం_సంకేతం_2, వృక్షం,
					  bool, వృక్షం, bool);
బాహ్య నిర్మాణం c_parm *build_c_parm (నిర్మాణం c_declspecs *, వృక్షం,
				    నిర్మాణం c_declarator *, location_t);
బాహ్య నిర్మాణం c_declarator *build_attrs_declarator (వృక్షం,
						    నిర్మాణం c_declarator *);
బాహ్య నిర్మాణం c_declarator *build_function_declarator (నిర్మాణం c_arg_info *,
						       నిర్మాణం c_declarator *);
బాహ్య నిర్మాణం c_declarator *build_id_declarator (వృక్షం);
బాహ్య నిర్మాణం c_declarator *make_సూచిక_declarator (నిర్మాణం c_declspecs *,
						     నిర్మాణం c_declarator *);
బాహ్య నిర్మాణం c_declspecs *build_null_declspecs (శూన్య);
బాహ్య నిర్మాణం c_declspecs *declspecs_కూడు_qual (location_t,
					       నిర్మాణం c_declspecs *, వృక్షం);
బాహ్య నిర్మాణం c_declspecs *declspecs_కూడు_type (location_t,
					       నిర్మాణం c_declspecs *,
					       నిర్మాణం c_typespec);
బాహ్య నిర్మాణం c_declspecs *declspecs_కూడు_scspec (location_t,
						 నిర్మాణం c_declspecs *, వృక్షం);
బాహ్య నిర్మాణం c_declspecs *declspecs_కూడు_attrs (location_t,
						నిర్మాణం c_declspecs *, వృక్షం);
బాహ్య నిర్మాణం c_declspecs *declspecs_కూడు_addrspace (location_t,
						    నిర్మాణం c_declspecs *,
						    addr_space_t);
బాహ్య నిర్మాణం c_declspecs *declspecs_కూడు_alignas (location_t,
						  నిర్మాణం c_declspecs *, వృక్షం);
బాహ్య నిర్మాణం c_declspecs *ముగింపు_declspecs (నిర్మాణం c_declspecs *);
బాహ్య కొలత_t c_వృక్షం_కొలత (గణన వృక్షం_సంకేతం_2);
బాహ్య పూర్ణాంకం c_get_loop_పేర్లు (వృక్షం, bool, వృక్షం *);
బాహ్య శూన్య c_release_loop_పేర్లు (పూర్ణాంకం);
బాహ్య వృక్షం c_ముగింపు_bc_name (location_t, వృక్షం, bool);

/* in c-objc-common.cc */
బాహ్య bool c_objc_common_init (శూన్య);
బాహ్య bool c_missing_noreturn_ok_p (వృక్షం);
బాహ్య bool c_warn_వాడని_global_decl (const_వృక్షం);
బాహ్య శూన్య c_initialize_diagnostics (diagnostics::context *);
బాహ్య bool c_var_mod_p (వృక్షం x, వృక్షం fn);
బాహ్య alias_సమితి_type c_get_alias_సమితి (వృక్షం);
బాహ్య పూర్ణాంకం c_type_dwarf_attribute (const_వృక్షం, పూర్ణాంకం);
బాహ్య వృక్షం c_enum_underlying_పునాది_type (const_వృక్షం);

/* in c-typeck.cc */
బాహ్య పూర్ణాంకం లోపల_alignof;
బాహ్య పూర్ణాంకం లోపల_sizeof;
బాహ్య పూర్ణాంకం లోపల_countof;
బాహ్య పూర్ణాంకం లోపల_typeof;
బాహ్య పూర్ణాంకం లోపల_generic;
బాహ్య bool c_లోపల_omp_for;
బాహ్య bool c_omp_array_section_p;

బాహ్య వృక్షం c_చివరి_sizeof_arg;
బాహ్య location_t c_చివరి_sizeof_loc;

బాహ్య నిర్మాణం c_switch *c_switch_దొంతర;

బాహ్య bool null_సూచిక_constant_p (const_వృక్షం);


అంతఃవరుస bool
c_type_variably_modified_p (వృక్షం t)
{
  ఒకవేళ (error_mark_కణుపు == t)
    తిరిగి false;
  ఒకవేళ (C_TYPE_VARIABLY_MODIFIED (t))
    తిరిగి true;
  ఒకవేళ (TYPE_STRUCTURAL_EQUALITY_P (t))
    {
      /* The flag may not have been set yet because of incomplete
	 structure or union types completed later.  */
      ఎంపిక (వృక్షం_సంకేతం (t))
	{
	స్థితి ARRAY_TYPE:
	స్థితి FUNCTION_TYPE:
	స్థితి సూచిక_TYPE:
	  /* Recurse.  */
	  ఒకవేళ (c_type_variably_modified_p (వృక్షం_TYPE (t)))
	    {
	      C_TYPE_VARIABLY_MODIFIED (t) = 1;
	      తిరిగి true;
	    }
	  ఆపు;
	అప్రమేయ:
	  ఆపు;
	}
    }
  తిరిగి false;
}

అంతఃవరుస bool
c_type_unspecified_p (వృక్షం t)
{
  తిరిగి error_mark_కణుపు != t
	 && C_TYPE_VARIABLE_కొలత (t) && వృక్షం_సంకేతం (t) == ARRAY_TYPE
	 && TYPE_DOMAIN (t) && TYPE_MAX_విలువ (TYPE_DOMAIN (t))
	 && వృక్షం_సంకేతం (TYPE_MAX_విలువ (TYPE_DOMAIN (t))) == COMPOUND_సమాసం
	 && integer_zerop (వృక్షం_నిర్వాహ్యం (TYPE_MAX_విలువ (TYPE_DOMAIN (t)), 0))
	 && integer_zerop (వృక్షం_నిర్వాహ్యం (TYPE_MAX_విలువ (TYPE_DOMAIN (t)), 1));
}

బాహ్య bool zero_నిడివి_array_type_p (const_వృక్షం type);
బాహ్య bool char_type_p (వృక్షం);
బాహ్య వృక్షం c_type_ట్యాగ్ (const_వృక్షం t);
బాహ్య వృక్షం c_objc_common_truthvalue_conversion (location_t, వృక్షం,
						 వృక్షం = integer_type_కణుపు);
బాహ్య వృక్షం require_complete_type (location_t, వృక్షం);
బాహ్య bool same_translation_unit_p (const_వృక్షం, const_వృక్షం);
బాహ్య bool comptypes (వృక్షం, వృక్షం);
బాహ్య bool comptypes_same_p (వృక్షం, వృక్షం);
బాహ్య bool comptypes_equiv_p (వృక్షం, వృక్షం);
బాహ్య bool comptypes_check_enum_int (వృక్షం, వృక్షం, bool *);
బాహ్య bool c_mark_addressable (వృక్షం, bool = false, bool = false);
బాహ్య శూన్య c_incomplete_type_error (location_t, const_వృక్షం, const_వృక్షం);
బాహ్య వృక్షం c_type_promotes_గమ్యం (వృక్షం);
బాహ్య నిర్మాణం c_సమాసం default_function_array_conversion (location_t,
							నిర్మాణం c_సమాసం);
బాహ్య నిర్మాణం c_సమాసం default_function_array_read_conversion (location_t,
							     నిర్మాణం c_సమాసం);
బాహ్య నిర్మాణం c_సమాసం convert_lvalue_గమ్యం_rvalue (location_t, నిర్మాణం c_సమాసం,
					       bool, bool, bool = false);
బాహ్య వృక్షం decl_constant_విలువ_1 (వృక్షం, bool);
బాహ్య శూన్య mark_exp_read (వృక్షం);
బాహ్య వృక్షం సంయుక్త_type (వృక్షం, వృక్షం);
బాహ్య వృక్షం lookup_క్షేత్రం (const_వృక్షం, వృక్షం);
బాహ్య వృక్షం build_component_ref (location_t, వృక్షం, వృక్షం, location_t,
				 location_t);
బాహ్య వృక్షం handle_counted_by_for_component_ref (location_t, వృక్షం);
బాహ్య వృక్షం build_array_ref (location_t, వృక్షం, వృక్షం);
బాహ్య వృక్షం build_omp_array_section (location_t, వృక్షం, వృక్షం, వృక్షం);
బాహ్య వృక్షం build_external_ref (location_t, వృక్షం, bool, వృక్షం *);
బాహ్య శూన్య తీయి_maybe_వాడిన (bool);
బాహ్య నిర్మాణం maybe_వాడిన_decl *save_maybe_వాడిన ();
బాహ్య శూన్య restore_maybe_వాడిన (నిర్మాణం maybe_వాడిన_decl *);
బాహ్య శూన్య mark_decl_వాడిన (వృక్షం, bool);
బాహ్య నిర్మాణం c_సమాసం c_సమాసం_sizeof_సమాసం (location_t, నిర్మాణం c_సమాసం);
బాహ్య నిర్మాణం c_సమాసం c_సమాసం_sizeof_type (location_t, నిర్మాణం c_type_name *);
బాహ్య నిర్మాణం c_సమాసం c_సమాసం_countof_సమాసం (location_t, నిర్మాణం c_సమాసం);
బాహ్య నిర్మాణం c_సమాసం c_సమాసం_countof_type (location_t loc,
					  నిర్మాణం c_type_name *);
బాహ్య నిర్మాణం c_సమాసం c_సమాసం_maxof_type (location_t loc, నిర్మాణం c_type_name *);
బాహ్య నిర్మాణం c_సమాసం c_సమాసం_minof_type (location_t loc, నిర్మాణం c_type_name *);
బాహ్య నిర్మాణం c_సమాసం parser_build_unary_op (location_t, గణన వృక్షం_సంకేతం_2,
    					    నిర్మాణం c_సమాసం);
బాహ్య నిర్మాణం c_సమాసం parser_build_ద్విమాన_op (location_t,
    					     గణన వృక్షం_సంకేతం_2, నిర్మాణం c_సమాసం,
					     నిర్మాణం c_సమాసం, వృక్షం);
బాహ్య వృక్షం build_conditional_సమాసం (location_t, వృక్షం, bool, వృక్షం, వృక్షం,
				    location_t, వృక్షం, వృక్షం, location_t);
బాహ్య వృక్షం build_compound_సమాసం (location_t, వృక్షం, వృక్షం);
బాహ్య వృక్షం c_cast_సమాసం (location_t, నిర్మాణం c_type_name *, వృక్షం);
బాహ్య వృక్షం build_c_cast (location_t, వృక్షం, వృక్షం);
బాహ్య శూన్య store_init_విలువ (location_t, వృక్షం, వృక్షం, వృక్షం);
బాహ్య శూన్య maybe_warn_string_init (location_t, వృక్షం, నిర్మాణం c_సమాసం);
బాహ్య శూన్య ప్రారంభం_init (వృక్షం, వృక్షం, bool, bool, rich_location *);
బాహ్య శూన్య ముగింపు_init (శూన్య);
బాహ్య శూన్య really_ప్రారంభం_incremental_init (వృక్షం);
బాహ్య శూన్య ముగింపు_implicit_inits (location_t, నిర్మాణం obstack *);
బాహ్య శూన్య నెట్టు_init_level (location_t, పూర్ణాంకం, నిర్మాణం obstack *);
బాహ్య నిర్మాణం c_సమాసం తీయి_init_level (location_t, పూర్ణాంకం, నిర్మాణం obstack *,
				     location_t);
బాహ్య శూన్య సమితి_init_సూచీ (location_t, వృక్షం, వృక్షం, నిర్మాణం obstack *);
బాహ్య శూన్య సమితి_init_label (location_t, వృక్షం, location_t, నిర్మాణం obstack *);
గుర్తులేని c_maybe_optimize_large_byte_initializer (శూన్య);
బాహ్య శూన్య process_init_element (location_t, నిర్మాణం c_సమాసం, bool,
				  నిర్మాణం obstack *);
బాహ్య వృక్షం build_compound_literal (location_t, వృక్షం, వృక్షం, bool,
				    గుర్తులేని పూర్ణాంకం, నిర్మాణం c_declspecs *);
బాహ్య శూన్య check_compound_literal_type (location_t, నిర్మాణం c_type_name *);
బాహ్య వృక్షం c_ప్రారంభం_switch (location_t, location_t, వృక్షం, bool, వృక్షం);
బాహ్య శూన్య c_ముగింపు_switch (వృక్షం, వృక్షం);
బాహ్య వృక్షం build_asm_సమాసం (location_t, వృక్షం, వృక్షం, వృక్షం, వృక్షం, వృక్షం, bool,
			    bool);
బాహ్య వృక్షం build_asm_stmt (bool, వృక్షం);
బాహ్య పూర్ణాంకం c_types_compatible_p (వృక్షం, వృక్షం);
బాహ్య వృక్షం c_begin_compound_stmt (bool);
బాహ్య వృక్షం c_చివర_compound_stmt (location_t, వృక్షం, bool);
బాహ్య శూన్య c_ముగింపు_if_stmt (location_t, వృక్షం, వృక్షం, వృక్షం);
బాహ్య శూన్య c_ముగింపు_loop (location_t, location_t, వృక్షం, location_t, వృక్షం,
			   వృక్షం, వృక్షం, వృక్షం, bool);
బాహ్య వృక్షం c_begin_stmt_సమాసం (శూన్య);
బాహ్య వృక్షం c_ముగింపు_stmt_సమాసం (location_t, వృక్షం);
బాహ్య వృక్షం c_process_సమాసం_stmt (location_t, వృక్షం);
బాహ్య వృక్షం c_ముగింపు_సమాసం_stmt (location_t, వృక్షం);
బాహ్య వృక్షం c_ముగింపు_return (location_t, వృక్షం, వృక్షం, bool = false);
బాహ్య వృక్షం c_ముగింపు_bc_stmt (location_t, వృక్షం, bool, వృక్షం);
బాహ్య వృక్షం c_ముగింపు_goto_label (location_t, వృక్షం);
బాహ్య వృక్షం c_ముగింపు_goto_ptr (location_t, c_సమాసం val);
బాహ్య వృక్షం c_సమాసం_గమ్యం_decl (వృక్షం, bool *, bool *);
బాహ్య వృక్షం c_ముగింపు_omp_construct (location_t, గణన వృక్షం_సంకేతం_2, వృక్షం, వృక్షం);
బాహ్య వృక్షం c_ముగింపు_oacc_దత్తాంశం (location_t, వృక్షం, వృక్షం);
బాహ్య వృక్షం c_ముగింపు_oacc_host_దత్తాంశం (location_t, వృక్షం, వృక్షం);
బాహ్య వృక్షం c_begin_omp_parallel (శూన్య);
బాహ్య వృక్షం c_ముగింపు_omp_parallel (location_t, వృక్షం, వృక్షం);
బాహ్య వృక్షం c_begin_omp_task (శూన్య);
బాహ్య వృక్షం c_ముగింపు_omp_task (location_t, వృక్షం, వృక్షం);
బాహ్య శూన్య c_ముగింపు_omp_cancel (location_t, వృక్షం);
బాహ్య శూన్య c_ముగింపు_omp_cancellation_బిందువు (location_t, వృక్షం);
బాహ్య వృక్షం c_ముగింపు_omp_clauses (వృక్షం, గణన c_omp_region_type);
బాహ్య వృక్షం c_omp_ముగింపు_mapper_clauses (వృక్షం);
బాహ్య వృక్షం c_omp_mapper_lookup (వృక్షం, వృక్షం);
బాహ్య వృక్షం c_omp_వెలికితీయి_mapper_directive (వృక్షం);
బాహ్య వృక్షం c_omp_map_array_section (location_t, వృక్షం);
బాహ్య వృక్షం c_build_va_arg (location_t, వృక్షం, location_t, వృక్షం, వృక్షం);
బాహ్య వృక్షం c_ముగింపు_transaction (location_t, వృక్షం, పూర్ణాంకం);
బాహ్య bool c_వృక్షం_equal (వృక్షం, వృక్షం);
బాహ్య వృక్షం c_build_function_call_vec (location_t, స్థిరరాశి vec<location_t>&,
				       వృక్షం, vec<వృక్షం, va_gc> *,
				       vec<వృక్షం, va_gc> *);
బాహ్య వృక్షం c_omp_clause_copy_ctor (వృక్షం, వృక్షం, వృక్షం);
బాహ్య వృక్షం c_reconstruct_complex_type (వృక్షం, వృక్షం);
బాహ్య వృక్షం c_type_canonical (వృక్షం);
బాహ్య వృక్షం c_build_type_attribute_variant (వృక్షం ntype, వృక్షం attrs);
బాహ్య వృక్షం c_build_సూచిక_type (వృక్షం type);
బాహ్య వృక్షం c_build_array_type (వృక్షం type, వృక్షం domain);
బాహ్య వృక్షం c_build_array_type_unspecified (వృక్షం type);
బాహ్య వృక్షం c_build_array_type_zero_కొలత (వృక్షం type);
బాహ్య వృక్షం c_build_function_type (వృక్షం type, వృక్షం వాదనలు, bool no = false);
బాహ్య వృక్షం c_build_సూచిక_type_for_బహుళకం (వృక్షం type, machine_బహుళకం బహుళకం, bool m);

/* Set to 0 at beginning of a function definition, set to 1 if
   a return statement that specifies a return value is seen.  */

బాహ్య పూర్ణాంకం current_function_returns_విలువ;

/* Set to 0 at beginning of a function definition, set to 1 if
   a return statement with no argument is seen.  */

బాహ్య పూర్ణాంకం current_function_returns_null;

/* Set to 0 at beginning of a function definition, set to 1 if
   a call to a noreturn function is seen.  */

బాహ్య పూర్ణాంకం current_function_returns_abnormally;

/* In c-decl.cc */

/* Tell the binding oracle what kind of binding we are looking for.  */

గణన c_oracle_request
{
  C_ORACLE_చిహ్నం,
  C_ORACLE_ట్యాగ్,
  C_ORACLE_LABEL
};

/* If this is non-NULL, then it is a "binding oracle" which can lazily
   create bindings when needed by the C compiler.  The oracle is told
   the name and type of the binding to create.  It can call pushdecl
   or the like to ensure the binding is visible; or do nothing,
   leaving the binding untouched.  c-decl.cc takes note of when the
   oracle has been called and will not call it again if it fails to
   create a given binding.  */

రకనిర్వచనం శూన్య c_binding_oracle_function (గణన c_oracle_request, వృక్షం identifier);

బాహ్య c_binding_oracle_function *c_binding_oracle;

బాహ్య శూన్య c_ముగింపు_incomplete_decl (వృక్షం);
బాహ్య వృక్షం c_omp_reduction_id (గణన వృక్షం_సంకేతం_2, వృక్షం);
బాహ్య వృక్షం c_omp_reduction_decl (వృక్షం);
బాహ్య వృక్షం c_omp_reduction_lookup (వృక్షం, వృక్షం);
బాహ్య వృక్షం c_check_omp_declare_reduction_r (వృక్షం *, పూర్ణాంకం *, శూన్య *);
బాహ్య వృక్షం c_omp_mapper_id (వృక్షం);
బాహ్య వృక్షం c_omp_mapper_decl (వృక్షం);
బాహ్య శూన్య c_omp_పరిశీలన_mapper_bindings (location_t, వృక్షం *, వృక్షం);
బాహ్య bool c_check_లోపల_current_scope (వృక్షం);
బాహ్య శూన్య c_pushtag (location_t, వృక్షం, వృక్షం);
బాహ్య శూన్య c_bind (location_t, వృక్షం, bool);
బాహ్య bool ట్యాగ్_exists_p (గణన వృక్షం_సంకేతం_2, వృక్షం);

బాహ్య శూన్య verify_counted_by_for_శిఖరం_anonymous_type (వృక్షం);

/* In c-errors.cc */
బాహ్య bool pedwarn_c90 (location_t, diagnostics::option_id, స్థిరరాశి అక్షరం *, ...)
    ATTRIBUTE_GCC_DIAG(3,4);
బాహ్య bool pedwarn_c99 (location_t, diagnostics::option_id, స్థిరరాశి అక్షరం *, ...)
    ATTRIBUTE_GCC_DIAG(3,4);
బాహ్య bool pedwarn_c11 (location_t, diagnostics::option_id, స్థిరరాశి అక్షరం *, ...)
    ATTRIBUTE_GCC_DIAG(3,4);
బాహ్య bool pedwarn_c23 (location_t, diagnostics::option_id, స్థిరరాశి అక్షరం *, ...)
    ATTRIBUTE_GCC_DIAG(3,4);
బాహ్య శూన్య కూడు_note_about_new_keyword (location_t loc,
					వృక్షం keyword_id);

బాహ్య శూన్య
సమితి_c_సమాసం_ఆధారం_range (c_సమాసం *సమాసం,
			 location_t ప్రారంభం, location_t ముగింపు);

బాహ్య శూన్య
సమితి_c_సమాసం_ఆధారం_range (c_సమాసం *సమాసం,
			 ఆధారం_range src_range);

/* In c-fold.cc */
బాహ్య vec<వృక్షం> incomplete_రికార్డు_decls;

బాహ్య స్థిరరాశి అక్షరం *c_get_sarif_ఆధారం_language (స్థిరరాశి అక్షరం *filename);

బాహ్య స్థిరరాశి నిర్మాణం scoped_attribute_specs std_attribute_పట్టిక;

#ఒకవేళ CHECKING_P
namespace selftest {
  బాహ్య శూన్య నిరంతరం_c_tests (శూన్య);
} // namespace selftest
#అయితే_ముగింపు /* #if CHECKING_P */


#అయితే_ముగింపు /* ! GCC_C_TREE_H */
