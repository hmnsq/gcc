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

#ifndef GCC_C_বৃক্ষ_H
#define GCC_C_বৃক্ষ_H

#অন্তর্ভাব "c-family/c-common.h"
#অন্তর্ভাব "diagnostic.h"

/* struct lang_identifier is private to c-decl.cc, but langhooks.cc needs to
   know how big it is.  This is sanity-checked in c-decl.cc.  */
#define C_SIZEOF_STRUCT_LANG_IDENTIFIER \
  (পরিমাণ (সংরচনা c_common_identifier) + 3 * পরিমাণ (শূন্য *))

/* In a RECORD_TYPE or UNION_TYPE, nonzero if any component is read-only.  */
#define C_TYPE_FIELDS_READONLY(TYPE) বৃক্ষ_LANG_FLAG_1 (TYPE)

/* In a RECORD_TYPE or UNION_TYPE, nonzero if any component is volatile.  */
#define C_TYPE_FIELDS_VOLATILE(TYPE) বৃক্ষ_LANG_FLAG_2 (TYPE)

/* In a RECORD_TYPE or UNION_TYPE, nonzero if any component is
   volatile, restrict-qualified or atomic; that is, has a type not
   permitted for a constexpr object.  */
#define C_TYPE_FIELDS_NON_CONSTEXPR(TYPE) বৃক্ষ_LANG_FLAG_4 (TYPE)

/* In a RECORD_TYPE or UNION_TYPE, nonzero if any component has a
   counted_by attribute.  */
#define C_TYPE_FIELDS_HAS_COUNTED_BY(TYPE) TYPE_LANG_FLAG_3 (TYPE)

/* In a RECORD_TYPE or UNION_TYPE or ENUMERAL_TYPE
   nonzero if the definition of the type has already started.  */
#define C_TYPE_BEING_DEFINED(TYPE) TYPE_LANG_FLAG_0 (TYPE)

/* In an incomplete RECORD_TYPE, UNION_TYPE or ENUMERAL_TYPE, a list of
   variable declarations whose type would be completed by completing
   that type.  */
#define C_TYPE_INCOMPLETE_VARS(TYPE) \
  TYPE_LANG_SLOT_1 (বৃক্ষ_CHECK4 (TYPE, RECORD_TYPE, UNION_TYPE, \
				 QUAL_UNION_TYPE, ENUMERAL_TYPE))

/* In an IDENTIFIER_NODE, nonzero if this identifier is actually a
   keyword.  C_RID_CODE (node) is then the RID_* value of the keyword.  */
#define C_IS_RESERVED_WORD(ID) বৃক্ষ_LANG_FLAG_0 (ID)

/* Record whether a type or decl was written with nonconstant size.
   Note that TYPE_SIZE may have simplified to a constant.  */
#define C_TYPE_VARIABLE_SIZE(TYPE) TYPE_LANG_FLAG_1 (TYPE)
#define C_DECL_VARIABLE_SIZE(TYPE) DECL_LANG_FLAG_0 (TYPE)

/* Record whether a type is variably modified. */
#define C_TYPE_VARIABLY_MODIFIED(TYPE) TYPE_LANG_FLAG_6 (TYPE)


/* Record whether a type is defined inside a struct or union type.
   This is used for -Wc++-compat. */
#define C_TYPE_DEFINED_IN_STRUCT(TYPE) TYPE_LANG_FLAG_2 (TYPE)

/* Record whether a typedef for type `int' was actually `signed int'.  */
#define C_TYPEDEF_EXPLICITLY_SIGNED(EXP) DECL_LANG_FLAG_1 (EXP)

/* For a FUNCTION_DECL, nonzero if it was defined without an explicit
   return type.  */
#define C_FUNCTION_IMPLICIT_INT(EXP) DECL_LANG_FLAG_1 (EXP)

/* For a FUNCTION_DECL, nonzero if it was an implicit declaration.  */
#define C_DECL_IMPLICIT(EXP) DECL_LANG_FLAG_2 (EXP)

/* For a PARM_DECL, nonzero if it was declared as an array.  */
#define C_ARRAY_PARAMETER(গ্রন্থি_2) DECL_LANG_FLAG_0 (গ্রন্থি_2)

/* For FUNCTION_DECLs, evaluates true if the decl is a nested
   function that requires a non-local context.  */
#define C_FUNC_NONLOCAL_CONTEXT(EXP)		\
  DECL_LANG_FLAG_4 (FUNCTION_DECL_CHECK (EXP))

/* For FUNCTION_DECLs, evaluates true if the decl is built-in but has
   been declared.  */
#define C_DECL_DECLARED_BUILTIN(EXP)		\
  DECL_LANG_FLAG_3 (FUNCTION_DECL_CHECK (EXP))

/* For FUNCTION_DECLs, evaluates true if the decl is built-in, has a
   built-in prototype and does not have a non-built-in prototype.  */
#define C_DECL_BUILTIN_PROTOTYPE(EXP)		\
  DECL_LANG_FLAG_6 (FUNCTION_DECL_CHECK (EXP))

/* For LABEL_DECLs marks canonical name of a loop.  */
#define C_DECL_LOOP_NAME(EXP) DECL_LANG_FLAG_3 (LABEL_DECL_CHECK (EXP))

/* For LABEL_DECLs marks canonical name of a switch.  During parsing of
   ObjC foreach named loop both C_DECL_LOOP_NAME and C_DECL_SWITCH_NAME
   are temporarily set.  */
#define C_DECL_SWITCH_NAME(EXP) DECL_LANG_FLAG_5 (LABEL_DECL_CHECK (EXP))

/* For LABEL_DECLs marks canonical name of a loop or switch being
   valid for use in break identifier or continue identifier statements.  */
#define C_DECL_LOOP_SWITCH_NAME_VALID(EXP) \
  DECL_LANG_FLAG_6 (LABEL_DECL_CHECK (EXP))

/* For LABEL_DECLs marks canonical loop or switch names which were actually
   used in one or more break identifier or continue identifier statements.  */
#define C_DECL_LOOP_SWITCH_NAME_USED(EXP) \
  DECL_LANG_FLAG_8 (LABEL_DECL_CHECK (EXP))

/* Record whether a decl was declared register.  This is strictly a
   front-end flag, whereas DECL_REGISTER is used for code generation;
   they may differ for structures with volatile fields.  */
#define C_DECL_REGISTER(EXP) \
  DECL_LANG_FLAG_4 (বৃক্ষ_NOT_CHECK (EXP, FUNCTION_DECL))

/* Record whether a decl was used in an expression anywhere except an
   unevaluated operand of sizeof / typeof / alignof.  This is only
   used for functions declared static but not defined, though outside
   sizeof and typeof it is set for other function decls as well.  */
#define C_DECL_USED(EXP) DECL_LANG_FLAG_5 (FUNCTION_DECL_CHECK (EXP))

/* Record whether a variable has been declared threadprivate by
   #pragma omp threadprivate.  */
#define C_DECL_THREADPRIVATE_P(DECL) DECL_LANG_FLAG_3 (VAR_DECL_CHECK (DECL))

/* Set on VAR_DECLs for compound literals.  */
#define C_DECL_COMPOUND_LITERAL_P(DECL) \
  DECL_LANG_FLAG_5 (VAR_DECL_CHECK (DECL))

/* Set on decls used as placeholders for a C23 underspecified object
   definition.  */
#define C_DECL_UNDERSPECIFIED(DECL) DECL_LANG_FLAG_7 (DECL)

/* Set on VAR_DECLs declared as 'constexpr'.  */
#define C_DECL_DECLARED_CONSTEXPR(DECL) \
  DECL_LANG_FLAG_8 (VAR_DECL_CHECK (DECL))

/* Nonzero for a decl which either doesn't exist or isn't a prototype.
   N.B. Could be simplified if all built-in decls had complete prototypes
   (but this is presently difficult because some of them need FILE*).  */
#define C_DECL_ISNT_PROTOTYPE(EXP)			\
       (EXP == 0					\
	|| (!prototype_p (বৃক্ষ_TYPE (EXP))	\
	    && !fndecl_built_in_p (EXP)))

/* For FUNCTION_TYPE, a hidden list of types of arguments.  The same as
   TYPE_ARG_TYPES for functions with prototypes, but created for functions
   without prototypes.  */
#define TYPE_ACTUAL_ARG_TYPES(গ্রন্থি_2) \
  TYPE_LANG_SLOT_1 (FUNCTION_TYPE_CHECK (গ্রন্থি_2))

/* For a CONSTRUCTOR, whether some initializer contains a
   subexpression meaning it is not a constant expression.  */
#define CONSTRUCTOR_NON_CONST(রাশিমালা_2) বৃক্ষ_LANG_FLAG_1 (CONSTRUCTOR_CHECK (রাশিমালা_2))

/* For a SAVE_EXPR, nonzero if the operand of the SAVE_EXPR has already
   been folded.  */
#define SAVE_রাশিমালা_FOLDED_P(EXP)	বৃক্ষ_LANG_FLAG_1 (SAVE_রাশিমালা_CHECK (EXP))

/* Whether a type has boolean semantics: either a boolean type or an
   enumeration type with a boolean type as its underlying type.  */
#define C_BOOLEAN_TYPE_P(TYPE)						\
  (বৃক্ষ_CODE (TYPE) == BOOLEAN_TYPE					\
   || (বৃক্ষ_CODE (TYPE) == ENUMERAL_TYPE				\
       && ENUM_UNDERLYING_TYPE (TYPE) != NULL_বৃক্ষ			\
       && (বৃক্ষ_CODE (ENUM_UNDERLYING_TYPE (TYPE)) == BOOLEAN_TYPE	\
	   || c_hardbool_type_attr (TYPE))))

/* Record parser information about an expression that is irrelevant
   for code generation alongside a tree representing its value.  */
সংরচনা c_রাশিমালা
{
  /* The value of the expression.  */
  বৃক্ষ মান;
  /* Record the original unary/binary operator of an expression, which may
     have been changed by fold, STRING_CST for unparenthesized string
     constants, C_MAYBE_CONST_EXPR for __builtin_constant_p calls
     (even if parenthesized), for subexpressions, and for non-constant
     initializers, or ERROR_MARK for other expressions (including
     parenthesized expressions).  */
  গণনা বৃক্ষ_code original_code;
  /* If not NULL, the original type of an expression.  This will
     differ from the type of the value field for an enum constant.
     The type of an enum constant is a plain integer type, but this
     field will be the enum type.  */
  বৃক্ষ original_type;

  /* The source range of this expression.  This is redundant
     for node values that have locations, but not all node kinds
     have locations (e.g. constants, and references to params, locals,
     etc), so we stash a copy here.  */
  source_range src_range;

  /* True if this was directly from a decimal constant token.  */
  bool m_decimal : 1;

  /* Access to the first and last locations within the source spelling
     of this expression.  */
  location_t get_start () ধ্রুব { প্রত্যাগম src_range.m_start; }
  location_t get_finish () ধ্রুব { প্রত্যাগম src_range.m_finish; }

  location_t get_location () ধ্রুব
  {
    যদি (রাশিমালা_HAS_LOCATION (মান))
      প্রত্যাগম রাশিমালা_LOCATION (মান);
    অন্যথা
      প্রত্যাগম make_location (get_start (), get_start (), get_finish ());
  }

  /* Set the value to error_mark_node whilst ensuring that src_range
     and m_decimal are initialized.  */
  শূন্য set_error ()
  {
    মান = error_mark_গ্রন্থি;
    src_range.m_start = UNKNOWN_LOCATION;
    src_range.m_finish = UNKNOWN_LOCATION;
    m_decimal = 0;
  }
};

/* Type alias for struct c_expr. This allows to use the structure
   inside the VEC types.  */
প্রকারনির্দেশ সংরচনা c_রাশিমালা c_রাশিমালা_t;

/* A kind of type specifier.  Note that this information is currently
   only used to distinguish tag definitions, tag references and typeof
   uses.  */
গণনা c_typespec_kind {
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
সংরচনা c_typespec {
  /* What kind of type specifier this is.  */
  গণনা c_typespec_kind kind;
  /* Whether the expression has operands suitable for use in constant
     expressions.  */
  bool রাশিমালা_const_operands;
  /* Whether the type specifier includes an enum type specifier (that
     is, ": specifier-qualifier-list" in a declaration using
     "enum").  */
  bool has_enum_type_specifier;
  /* The specifier itself.  */
  বৃক্ষ spec;
  /* An expression to be evaluated before the type specifier, in the
     case of typeof specifiers, or NULL otherwise or if no such
     expression is required for a particular typeof specifier.  In
     particular, when typeof is applied to an expression of variably
     modified type, that expression must be evaluated in order to
     determine array sizes that form part of the type, but the
     expression itself (as opposed to the array sizes) forms no part
     of the type and so needs to be recorded separately.  */
  বৃক্ষ রাশিমালা;
};

/* A storage class specifier.  */
গণনা c_storage_class {
  csc_none,
  csc_auto,
  csc_extern,
  csc_register,
  csc_static,
  csc_typedef
};

/* A type specifier keyword "void", "_Bool", "char", "int", "float",
   "double", "_Decimal32", "_Decimal64", "_Decimal128", "_Decimal64x",
   "_Fract", "_Accum", "_BitInt", or none of these.  */
গণনা c_typespec_keyword {
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
গণনা c_declspec_word {
  cdw_typespec /* A catch-all for a typespec.  */,
  cdw_storage_class  /* A catch-all for a storage class */,
  cdw_attributes,
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
  cdw_address_space,
  cdw_gimple,
  cdw_rtl,
  cdw_সংখ্যা_of_elements /* This one must always be the last
			    enumerator.  */
};

গণনা c_declspec_il {
  cdil_none,
  cdil_gimple,		/* __GIMPLE  */
  cdil_gimple_cfg,	/* __GIMPLE(cfg)  */
  cdil_gimple_ssa,	/* __GIMPLE(ssa)  */
  cdil_rtl		/* __RTL  */
};

/* A sequence of declaration specifiers in C.  When a new declaration
   specifier is added, please update the enum c_declspec_word above
   accordingly.  */
সংরচনা c_declspecs {
  location_t locations[cdw_সংখ্যা_of_elements];
  /* The type specified, if a single type specifier such as a struct,
     union or enum specifier, typedef name or typeof specifies the
     whole type, or NULL_TREE if none or a keyword such as "void" or
     "char" is used.  Does not include qualifiers.  */
  বৃক্ষ type;
  /* Any expression to be evaluated before the type, from a typeof
     specifier.  */
  বৃক্ষ রাশিমালা;
  /* The attributes from a typedef decl.  */
  বৃক্ষ decl_attr;
  /* When parsing, the GNU attributes and prefix standard attributes.
     Outside the parser, this will be NULL; attributes (possibly from
     multiple lists) will be passed separately.  */
  বৃক্ষ attrs;
  /* When parsing, postfix standard attributes (which appertain to the
     type specified by the preceding declaration specifiers, unlike
     prefix standard attributes which appertain to the declaration or
     declarations as a whole).  */
  বৃক্ষ postfix_attrs;
  /* The pass to start compiling a __GIMPLE or __RTL function with.  */
  বর্ণ *gimple_or_rtl_pass;
  /* ENTRY BB count.  */
  profile_গুনতি entry_bb_গুনতি;
  /* The base-2 log of the greatest alignment required by an _Alignas
     specifier, in bytes, or -1 if no such specifiers with nonzero
     alignment.  */
  পূর্ণাঙ্ক align_log;
  সঙ্ঘ {
    /* For the __intN declspec, this stores the index into the int_n_*
       arrays.  */
    পূর্ণাঙ্ক int_n_idx;
    /* For the _FloatN and _FloatNx declspec, this stores the index into
       the floatn_nx_types array.  */
    পূর্ণাঙ্ক floatn_nx_idx;
    /* For _BitInt(N) this stores the N.  */
    পূর্ণাঙ্ক bitint_prec;
  } u;
  /* The storage class specifier, or csc_none if none.  */
  গণনা c_storage_class storage_class;
  /* Any type specifier keyword used such as "int", not reflecting
     modifiers such as "short", or cts_none if none.  */
  গণনা c_typespec_keyword typespec_word : 8;
  /* The kind of type specifier if one has been seen, ctsk_none
     otherwise.  */
  গণনা c_typespec_kind typespec_kind : 4;
  গণনা c_declspec_il declspec_il : 3;
  /* Whether any expressions in typeof specifiers may appear in
     constant expressions.  */
  bool রাশিমালা_const_operands : 1;
  /* Whether any declaration specifiers have been seen at all.  */
  bool declspecs_seen_p : 1;
  /* Whether any declaration specifiers other than standard attributes
     have been seen at all.  If only standard attributes have been
     seen, this is an attribute-declaration.  */
  bool non_std_attrs_seen_p : 1;
  /* Whether something other than a storage class specifier or
     attribute has been seen.  This is used to warn for the
     obsolescent usage of storage class specifiers other than at the
     start of the list.  (Doing this properly would require function
     specifiers to be handled separately from storage class
     specifiers.)  */
  bool non_sc_seen_p : 1;
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
  addr_space_t address_space;
};

/* The various kinds of declarators in C.  */
গণনা c_declarator_kind {
  /* An identifier.  */
  cdk_id,
  /* A function.  */
  cdk_function,
  /* An array.  */
  cdk_array,
  /* A pointer.  */
  cdk_pointer,
  /* Parenthesized declarator with nested attributes.  */
  cdk_attrs
};

সংরচনা c_arg_tag {
  /* The argument name.  */
  বৃক্ষ id;
  /* The type of the argument.  */
  বৃক্ষ type;
};


/* Information about the parameters in a function declarator.  */
সংরচনা c_arg_info {
  /* A list of parameter decls.  */
  বৃক্ষ parms;
  /* A list of structure, union and enum tags defined.  */
  vec<c_arg_tag, va_gc> *tags;
  /* A list of argument types to go in the FUNCTION_TYPE.  */
  বৃক্ষ types;
  /* A list of non-parameter decls (notably enumeration constants)
     defined with the parameters.  */
  বৃক্ষ others;
  /* A compound expression of VLA sizes from the parameters, or NULL.
     In a function definition, these are used to ensure that
     side-effects in sizes of arrays converted to pointers (such as a
     parameter int i[n++]) take place; otherwise, they are
     ignored.  */
  বৃক্ষ pending_sizes;
  /* True when these arguments had [*].  */
  bool had_vla_unspec : 1;
  /* True when the arguments are a (...) prototype.  */
  bool no_named_args_stdarg_p : 1;
  /* True when empty parentheses have been interpreted as (void) in C23 or
     later.  This is only for use by -Wtraditional and is no longer needed if
     -Wtraditional is removed.  */
  bool c23_empty_parens : 1;
};

/* A declarator.  */
সংরচনা c_declarator {
  /* The kind of declarator.  */
  গণনা c_declarator_kind kind;
  location_t id_loc; /* Currently only set for cdk_id, cdk_array. */
  /* Except for cdk_id, the contained declarator.  For cdk_id, NULL.  */
  সংরচনা c_declarator *declarator;
  সঙ্ঘ {
    /* For identifiers.  */
    সংরচনা {
      /* An IDENTIFIER_NODE, or NULL_TREE if an abstract
	 declarator.  */
      বৃক্ষ id;
      /* Any attributes (which apply to the declaration rather than to
	 the type described by the outer declarators).  */
      বৃক্ষ attrs;
    } id;
    /* For functions.  */
    সংরচনা c_arg_info *arg_info;
    /* For arrays.  */
    সংরচনা {
      /* The array dimension, or NULL for [] and [*].  */
      বৃক্ষ dimen;
      /* The qualifiers inside [].  */
      পূর্ণাঙ্ক quals;
      /* The attributes (currently ignored) inside [].  */
      বৃক্ষ attrs;
      /* Whether [static] was used.  */
      bool static_p : 1;
      /* Whether [*] was used.  */
      bool vla_unspec_p : 1;
    } array;
    /* For pointers, the qualifiers on the pointer type.  */
    পূর্ণাঙ্ক pointer_quals;
    /* For attributes.  */
    বৃক্ষ attrs;
  } u;
};

/* A type name.  */
সংরচনা c_type_name {
  /* The declaration specifiers.  */
  সংরচনা c_declspecs *specs;
  /* The declarator.  */
  সংরচনা c_declarator *declarator;
};

/* A parameter.  */
সংরচনা c_parm {
  /* The declaration specifiers, minus any prefix attributes.  */
  সংরচনা c_declspecs *specs;
  /* The attributes.  */
  বৃক্ষ attrs;
  /* The declarator.  */
  সংরচনা c_declarator *declarator;
  /* The location of the parameter.  */
  location_t loc;
};

/* Used when parsing an enum.  Initialized by start_enum.  */
সংরচনা c_enum_contents
{
  /* While defining an enum type, this is 1 plus the last enumerator
     constant value.  */
  বৃক্ষ enum_next_মান;

  /* The enumeration type itself.  */
  বৃক্ষ enum_type;

  /* Nonzero means that there was overflow computing enum_next_value.  */
  পূর্ণাঙ্ক enum_overflow;
};

/* A type of reference to a static identifier in an inline
   function.  */
গণনা c_inline_static_type {
  /* Identifier with internal linkage used in function that may be an
     inline definition (i.e., file-scope static).  */
  csi_internal,
  /* Modifiable object with static storage duration defined in
     function that may be an inline definition (i.e., local
     static).  */
  csi_modifiable
};

/* Record details of decls possibly used inside sizeof or typeof.  */
সংরচনা maybe_used_decl
{
  /* The decl.  */
  বৃক্ষ decl;
  /* The level seen at (in_sizeof + in_typeof + in_countof + in_generic).  */
  পূর্ণাঙ্ক level;
  /* Seen in address-of.  */
  bool address;
  /* The next one at this level or above, or NULL.  */
  সংরচনা maybe_used_decl *next;
};


/* in c-parser.cc */
সংরচনা c_বৃক্ষ_token_vec;
বাহ্য শূন্য c_parse_init (শূন্য);
বাহ্য bool c_keyword_starts_typename (গণনা rid keyword);

/* in c-aux-info.cc */
বাহ্য শূন্য gen_aux_info_record (বৃক্ষ, পূর্ণাঙ্ক, পূর্ণাঙ্ক, পূর্ণাঙ্ক);

/* in c-decl.cc */
সংরচনা c_spot_bindings;
class c_struct_parse_info;
বাহ্য সংরচনা obstack parser_obstack;
/* Set to IN_ITERATION_STMT if parsing an iteration-statement,
   to IN_OMP_BLOCK if parsing OpenMP structured block and
   IN_OMP_FOR if parsing OpenMP loop.  If parsing a switch statement,
   this is bitwise ORed with IN_SWITCH_STMT, unless parsing an
   iteration-statement, OpenMP block or loop within that switch.
   If the innermost iteration/switch statement is named, IN_NAMED_STMT
   is additionally bitwise ORed into it.  */
#define IN_SWITCH_STMT		1
#define IN_ITERATION_STMT	2
#define IN_OMP_BLOCK		4
#define IN_OMP_FOR		8
#define IN_OBJC_FOREACH		16
#define IN_NAMED_STMT		32
বাহ্য unsigned বর্ণ in_statement;

বাহ্য bool switch_statement_break_seen_p;

বাহ্য bool global_bindings_p (শূন্য);
বাহ্য বৃক্ষ pushdecl (বৃক্ষ);
বাহ্য unsigned পূর্ণাঙ্ক start_underspecified_init (location_t, বৃক্ষ);
বাহ্য শূন্য finish_underspecified_init (বৃক্ষ, unsigned পূর্ণাঙ্ক);
বাহ্য শূন্য ঠেলো_scope (শূন্য);
বাহ্য বৃক্ষ বের_করো_scope (শূন্য);
বাহ্য শূন্য c_mark_decl_jump_unsafe_in_current_scope ();
বাহ্য শূন্য c_bindings_start_stmt_রাশিমালা (সংরচনা c_spot_bindings *);
বাহ্য শূন্য c_bindings_end_stmt_রাশিমালা (সংরচনা c_spot_bindings *);

বাহ্য শূন্য record_inline_static (location_t, বৃক্ষ, বৃক্ষ,
				  গণনা c_inline_static_type);
বাহ্য শূন্য c_init_decl_processing (শূন্য);
বাহ্য শূন্য c_print_identifier (FILE *, বৃক্ষ, পূর্ণাঙ্ক);
বাহ্য পূর্ণাঙ্ক quals_from_declspecs (ধ্রুব সংরচনা c_declspecs *);
বাহ্য সংরচনা c_declarator *build_array_declarator (location_t, বৃক্ষ,
    						    সংরচনা c_declspecs *,
						    bool, bool);
বাহ্য বৃক্ষ build_enumerator (location_t, location_t, সংরচনা c_enum_contents *,
			      বৃক্ষ, বৃক্ষ);
বাহ্য বৃক্ষ check_for_loop_decls (location_t, bool);
বাহ্য শূন্য mark_forward_parm_decls (শূন্য);
বাহ্য শূন্য declare_parm_level (শূন্য);
বাহ্য শূন্য undeclared_variable (location_t, বৃক্ষ);
বাহ্য বৃক্ষ lookup_label_for_goto (location_t, বৃক্ষ);
বাহ্য বৃক্ষ declare_label (বৃক্ষ);
বাহ্য বৃক্ষ define_label (location_t, বৃক্ষ);
বাহ্য সংরচনা c_spot_bindings *c_get_switch_bindings (শূন্য);
বাহ্য শূন্য c_release_switch_bindings (সংরচনা c_spot_bindings *);
বাহ্য bool c_check_switch_jump_warnings (সংরচনা c_spot_bindings *,
					  location_t, location_t);
বাহ্য শূন্য finish_decl (বৃক্ষ, location_t, বৃক্ষ, বৃক্ষ, বৃক্ষ);
বাহ্য বৃক্ষ finish_enum (বৃক্ষ, বৃক্ষ, বৃক্ষ);
বাহ্য শূন্য finish_function (location_t = প্রবেশ_location);
বাহ্য বৃক্ষ finish_struct (location_t, বৃক্ষ, বৃক্ষ, বৃক্ষ,
			   class c_struct_parse_info *,
			   বৃক্ষ *রাশিমালা = রিক্ত);
বাহ্য বৃক্ষ c_simulate_enum_decl (location_t, ধ্রুব বর্ণ *,
				  vec<string_int_pair> *);
বাহ্য বৃক্ষ c_simulate_record_decl (location_t, ধ্রুব বর্ণ *,
				    array_slice<ধ্রুব বৃক্ষ>);
বাহ্য সংরচনা c_arg_info *build_arg_info (শূন্য);
বাহ্য সংরচনা c_arg_info *get_parm_info (bool, বৃক্ষ);
বাহ্য বৃক্ষ grokfield (location_t, সংরচনা c_declarator *,
		       সংরচনা c_declspecs *, বৃক্ষ, বৃক্ষ *, বৃক্ষ *);
বাহ্য বৃক্ষ groktypename (সংরচনা c_type_name *, বৃক্ষ *, bool *);
বাহ্য বৃক্ষ grokgenassoc (সংরচনা c_type_name *);
বাহ্য বৃক্ষ grokparm (ধ্রুব সংরচনা c_parm *, বৃক্ষ *);
বাহ্য বৃক্ষ implicitly_declare (location_t, বৃক্ষ);
বাহ্য শূন্য keep_next_level (শূন্য);
বাহ্য শূন্য pending_xref_error (শূন্য);
বাহ্য শূন্য c_ঠেলো_function_context (শূন্য);
বাহ্য শূন্য c_বের_করো_function_context (শূন্য);
বাহ্য শূন্য ঠেলো_parm_decl (ধ্রুব সংরচনা c_parm *, বৃক্ষ *);
বাহ্য সংরচনা c_declarator *set_array_declarator_inner (সংরচনা c_declarator *,
							সংরচনা c_declarator *);
বাহ্য বৃক্ষ c_builtin_function (বৃক্ষ);
বাহ্য বৃক্ষ c_builtin_function_ext_scope (বৃক্ষ);
বাহ্য বৃক্ষ c_simulate_builtin_function_decl (বৃক্ষ);
বাহ্য শূন্য c_warn_unused_attributes (বৃক্ষ);
বাহ্য বৃক্ষ c_warn_type_attributes (বৃক্ষ, বৃক্ষ);
বাহ্য শূন্য shadow_tag (ধ্রুব সংরচনা c_declspecs *);
বাহ্য শূন্য shadow_tag_warned (ধ্রুব সংরচনা c_declspecs *, পূর্ণাঙ্ক);
বাহ্য বৃক্ষ start_enum (location_t, সংরচনা c_enum_contents *, বৃক্ষ, বৃক্ষ,
			bool potential_nesting_p);
বাহ্য bool start_function (সংরচনা c_declspecs *, সংরচনা c_declarator *, বৃক্ষ);
বাহ্য বৃক্ষ start_decl (সংরচনা c_declarator *, সংরচনা c_declspecs *, bool,
			বৃক্ষ, bool = true, location_t * = রিক্ত);
বাহ্য বৃক্ষ start_struct (location_t, গণনা বৃক্ষ_code, বৃক্ষ,
			  class c_struct_parse_info **);
বাহ্য শূন্য store_parm_decls (শূন্য);
বাহ্য শূন্য store_parm_decls_from (সংরচনা c_arg_info *);
বাহ্য শূন্য temp_store_parm_decls (বৃক্ষ, বৃক্ষ);
বাহ্য শূন্য temp_বের_করো_parm_decls (শূন্য);
বাহ্য বৃক্ষ xref_tag (গণনা বৃক্ষ_code, বৃক্ষ);
বাহ্য সংরচনা c_typespec parser_xref_tag (location_t, গণনা বৃক্ষ_code, বৃক্ষ,
					  bool, বৃক্ষ, bool);
বাহ্য সংরচনা c_parm *build_c_parm (সংরচনা c_declspecs *, বৃক্ষ,
				    সংরচনা c_declarator *, location_t);
বাহ্য সংরচনা c_declarator *build_attrs_declarator (বৃক্ষ,
						    সংরচনা c_declarator *);
বাহ্য সংরচনা c_declarator *build_function_declarator (সংরচনা c_arg_info *,
						       সংরচনা c_declarator *);
বাহ্য সংরচনা c_declarator *build_id_declarator (বৃক্ষ);
বাহ্য সংরচনা c_declarator *make_pointer_declarator (সংরচনা c_declspecs *,
						     সংরচনা c_declarator *);
বাহ্য সংরচনা c_declspecs *build_null_declspecs (শূন্য);
বাহ্য সংরচনা c_declspecs *declspecs_add_qual (location_t,
					       সংরচনা c_declspecs *, বৃক্ষ);
বাহ্য সংরচনা c_declspecs *declspecs_add_type (location_t,
					       সংরচনা c_declspecs *,
					       সংরচনা c_typespec);
বাহ্য সংরচনা c_declspecs *declspecs_add_scspec (location_t,
						 সংরচনা c_declspecs *, বৃক্ষ);
বাহ্য সংরচনা c_declspecs *declspecs_add_attrs (location_t,
						সংরচনা c_declspecs *, বৃক্ষ);
বাহ্য সংরচনা c_declspecs *declspecs_add_addrspace (location_t,
						    সংরচনা c_declspecs *,
						    addr_space_t);
বাহ্য সংরচনা c_declspecs *declspecs_add_alignas (location_t,
						  সংরচনা c_declspecs *, বৃক্ষ);
বাহ্য সংরচনা c_declspecs *finish_declspecs (সংরচনা c_declspecs *);
বাহ্য size_t c_বৃক্ষ_size (গণনা বৃক্ষ_code);
বাহ্য পূর্ণাঙ্ক c_get_loop_names (বৃক্ষ, bool, বৃক্ষ *);
বাহ্য শূন্য c_release_loop_names (পূর্ণাঙ্ক);
বাহ্য বৃক্ষ c_finish_bc_name (location_t, বৃক্ষ, bool);

/* in c-objc-common.cc */
বাহ্য bool c_objc_common_init (শূন্য);
বাহ্য bool c_missing_noreturn_ok_p (বৃক্ষ);
বাহ্য bool c_warn_unused_global_decl (const_বৃক্ষ);
বাহ্য শূন্য c_initialize_diagnostics (diagnostics::context *);
বাহ্য bool c_var_mod_p (বৃক্ষ x, বৃক্ষ fn);
বাহ্য alias_set_type c_get_alias_set (বৃক্ষ);
বাহ্য পূর্ণাঙ্ক c_type_dwarf_attribute (const_বৃক্ষ, পূর্ণাঙ্ক);
বাহ্য বৃক্ষ c_enum_underlying_base_type (const_বৃক্ষ);

/* in c-typeck.cc */
বাহ্য পূর্ণাঙ্ক in_alignof;
বাহ্য পূর্ণাঙ্ক in_sizeof;
বাহ্য পূর্ণাঙ্ক in_countof;
বাহ্য পূর্ণাঙ্ক in_typeof;
বাহ্য পূর্ণাঙ্ক in_generic;
বাহ্য bool c_in_omp_for;
বাহ্য bool c_omp_array_section_p;

বাহ্য বৃক্ষ c_last_sizeof_arg;
বাহ্য location_t c_last_sizeof_loc;

বাহ্য সংরচনা c_switch *c_switch_স্তূপ;

বাহ্য bool null_pointer_constant_p (const_বৃক্ষ);


অন্তঃস্থ bool
c_type_variably_modified_p (বৃক্ষ t)
{
  যদি (error_mark_গ্রন্থি == t)
    প্রত্যাগম false;
  যদি (C_TYPE_VARIABLY_MODIFIED (t))
    প্রত্যাগম true;
  যদি (TYPE_STRUCTURAL_EQUALITY_P (t))
    {
      /* The flag may not have been set yet because of incomplete
	 structure or union types completed later.  */
      বিকল্প (বৃক্ষ_CODE (t))
	{
	পক্ষ ARRAY_TYPE:
	পক্ষ FUNCTION_TYPE:
	পক্ষ POINTER_TYPE:
	  /* Recurse.  */
	  যদি (c_type_variably_modified_p (বৃক্ষ_TYPE (t)))
	    {
	      C_TYPE_VARIABLY_MODIFIED (t) = 1;
	      প্রত্যাগম true;
	    }
	  ভঙ্গ;
	স্বভাব:
	  ভঙ্গ;
	}
    }
  প্রত্যাগম false;
}

অন্তঃস্থ bool
c_type_unspecified_p (বৃক্ষ t)
{
  প্রত্যাগম error_mark_গ্রন্থি != t
	 && C_TYPE_VARIABLE_SIZE (t) && বৃক্ষ_CODE (t) == ARRAY_TYPE
	 && TYPE_DOMAIN (t) && TYPE_MAX_মান (TYPE_DOMAIN (t))
	 && বৃক্ষ_CODE (TYPE_MAX_মান (TYPE_DOMAIN (t))) == COMPOUND_রাশিমালা
	 && integer_zerop (বৃক্ষ_OPERAND (TYPE_MAX_মান (TYPE_DOMAIN (t)), 0))
	 && integer_zerop (বৃক্ষ_OPERAND (TYPE_MAX_মান (TYPE_DOMAIN (t)), 1));
}

বাহ্য bool zero_length_array_type_p (const_বৃক্ষ type);
বাহ্য bool char_type_p (বৃক্ষ);
বাহ্য বৃক্ষ c_type_tag (const_বৃক্ষ t);
বাহ্য বৃক্ষ c_objc_common_truthvalue_conversion (location_t, বৃক্ষ,
						 বৃক্ষ = integer_type_গ্রন্থি);
বাহ্য বৃক্ষ require_complete_type (location_t, বৃক্ষ);
বাহ্য bool same_translation_unit_p (const_বৃক্ষ, const_বৃক্ষ);
বাহ্য bool comptypes (বৃক্ষ, বৃক্ষ);
বাহ্য bool comptypes_same_p (বৃক্ষ, বৃক্ষ);
বাহ্য bool comptypes_equiv_p (বৃক্ষ, বৃক্ষ);
বাহ্য bool comptypes_check_enum_int (বৃক্ষ, বৃক্ষ, bool *);
বাহ্য bool c_mark_addressable (বৃক্ষ, bool = false, bool = false);
বাহ্য শূন্য c_incomplete_type_error (location_t, const_বৃক্ষ, const_বৃক্ষ);
বাহ্য বৃক্ষ c_type_promotes_to (বৃক্ষ);
বাহ্য সংরচনা c_রাশিমালা default_function_array_conversion (location_t,
							সংরচনা c_রাশিমালা);
বাহ্য সংরচনা c_রাশিমালা default_function_array_read_conversion (location_t,
							     সংরচনা c_রাশিমালা);
বাহ্য সংরচনা c_রাশিমালা convert_lvalue_to_rvalue (location_t, সংরচনা c_রাশিমালা,
					       bool, bool, bool = false);
বাহ্য বৃক্ষ decl_constant_মান_1 (বৃক্ষ, bool);
বাহ্য শূন্য mark_exp_read (বৃক্ষ);
বাহ্য বৃক্ষ composite_type (বৃক্ষ, বৃক্ষ);
বাহ্য বৃক্ষ lookup_field (const_বৃক্ষ, বৃক্ষ);
বাহ্য বৃক্ষ build_component_ref (location_t, বৃক্ষ, বৃক্ষ, location_t,
				 location_t);
বাহ্য বৃক্ষ handle_counted_by_for_component_ref (location_t, বৃক্ষ);
বাহ্য বৃক্ষ build_array_ref (location_t, বৃক্ষ, বৃক্ষ);
বাহ্য বৃক্ষ build_omp_array_section (location_t, বৃক্ষ, বৃক্ষ, বৃক্ষ);
বাহ্য বৃক্ষ build_external_ref (location_t, বৃক্ষ, bool, বৃক্ষ *);
বাহ্য শূন্য বের_করো_maybe_used (bool);
বাহ্য সংরচনা maybe_used_decl *save_maybe_used ();
বাহ্য শূন্য restore_maybe_used (সংরচনা maybe_used_decl *);
বাহ্য শূন্য mark_decl_used (বৃক্ষ, bool);
বাহ্য সংরচনা c_রাশিমালা c_রাশিমালা_sizeof_রাশিমালা (location_t, সংরচনা c_রাশিমালা);
বাহ্য সংরচনা c_রাশিমালা c_রাশিমালা_sizeof_type (location_t, সংরচনা c_type_name *);
বাহ্য সংরচনা c_রাশিমালা c_রাশিমালা_countof_রাশিমালা (location_t, সংরচনা c_রাশিমালা);
বাহ্য সংরচনা c_রাশিমালা c_রাশিমালা_countof_type (location_t loc,
					  সংরচনা c_type_name *);
বাহ্য সংরচনা c_রাশিমালা c_রাশিমালা_maxof_type (location_t loc, সংরচনা c_type_name *);
বাহ্য সংরচনা c_রাশিমালা c_রাশিমালা_minof_type (location_t loc, সংরচনা c_type_name *);
বাহ্য সংরচনা c_রাশিমালা parser_build_unary_op (location_t, গণনা বৃক্ষ_code,
    					    সংরচনা c_রাশিমালা);
বাহ্য সংরচনা c_রাশিমালা parser_build_দ্বিমিক_op (location_t,
    					     গণনা বৃক্ষ_code, সংরচনা c_রাশিমালা,
					     সংরচনা c_রাশিমালা, বৃক্ষ);
বাহ্য বৃক্ষ build_conditional_রাশিমালা (location_t, বৃক্ষ, bool, বৃক্ষ, বৃক্ষ,
				    location_t, বৃক্ষ, বৃক্ষ, location_t);
বাহ্য বৃক্ষ build_compound_রাশিমালা (location_t, বৃক্ষ, বৃক্ষ);
বাহ্য বৃক্ষ c_cast_রাশিমালা (location_t, সংরচনা c_type_name *, বৃক্ষ);
বাহ্য বৃক্ষ build_c_cast (location_t, বৃক্ষ, বৃক্ষ);
বাহ্য শূন্য store_init_মান (location_t, বৃক্ষ, বৃক্ষ, বৃক্ষ);
বাহ্য শূন্য maybe_warn_string_init (location_t, বৃক্ষ, সংরচনা c_রাশিমালা);
বাহ্য শূন্য start_init (বৃক্ষ, বৃক্ষ, bool, bool, rich_location *);
বাহ্য শূন্য finish_init (শূন্য);
বাহ্য শূন্য really_start_incremental_init (বৃক্ষ);
বাহ্য শূন্য finish_implicit_inits (location_t, সংরচনা obstack *);
বাহ্য শূন্য ঠেলো_init_level (location_t, পূর্ণাঙ্ক, সংরচনা obstack *);
বাহ্য সংরচনা c_রাশিমালা বের_করো_init_level (location_t, পূর্ণাঙ্ক, সংরচনা obstack *,
				     location_t);
বাহ্য শূন্য set_init_index (location_t, বৃক্ষ, বৃক্ষ, সংরচনা obstack *);
বাহ্য শূন্য set_init_label (location_t, বৃক্ষ, location_t, সংরচনা obstack *);
unsigned c_maybe_optimize_large_byte_initializer (শূন্য);
বাহ্য শূন্য process_init_element (location_t, সংরচনা c_রাশিমালা, bool,
				  সংরচনা obstack *);
বাহ্য বৃক্ষ build_compound_literal (location_t, বৃক্ষ, বৃক্ষ, bool,
				    unsigned পূর্ণাঙ্ক, সংরচনা c_declspecs *);
বাহ্য শূন্য check_compound_literal_type (location_t, সংরচনা c_type_name *);
বাহ্য বৃক্ষ c_start_switch (location_t, location_t, বৃক্ষ, bool, বৃক্ষ);
বাহ্য শূন্য c_finish_switch (বৃক্ষ, বৃক্ষ);
বাহ্য বৃক্ষ build_asm_রাশিমালা (location_t, বৃক্ষ, বৃক্ষ, বৃক্ষ, বৃক্ষ, বৃক্ষ, bool,
			    bool);
বাহ্য বৃক্ষ build_asm_stmt (bool, বৃক্ষ);
বাহ্য পূর্ণাঙ্ক c_types_compatible_p (বৃক্ষ, বৃক্ষ);
বাহ্য বৃক্ষ c_begin_compound_stmt (bool);
বাহ্য বৃক্ষ c_end_compound_stmt (location_t, বৃক্ষ, bool);
বাহ্য শূন্য c_finish_if_stmt (location_t, বৃক্ষ, বৃক্ষ, বৃক্ষ);
বাহ্য শূন্য c_finish_loop (location_t, location_t, বৃক্ষ, location_t, বৃক্ষ,
			   বৃক্ষ, বৃক্ষ, বৃক্ষ, bool);
বাহ্য বৃক্ষ c_begin_stmt_রাশিমালা (শূন্য);
বাহ্য বৃক্ষ c_finish_stmt_রাশিমালা (location_t, বৃক্ষ);
বাহ্য বৃক্ষ c_process_রাশিমালা_stmt (location_t, বৃক্ষ);
বাহ্য বৃক্ষ c_finish_রাশিমালা_stmt (location_t, বৃক্ষ);
বাহ্য বৃক্ষ c_finish_return (location_t, বৃক্ষ, বৃক্ষ, bool = false);
বাহ্য বৃক্ষ c_finish_bc_stmt (location_t, বৃক্ষ, bool, বৃক্ষ);
বাহ্য বৃক্ষ c_finish_goto_label (location_t, বৃক্ষ);
বাহ্য বৃক্ষ c_finish_goto_ptr (location_t, c_রাশিমালা val);
বাহ্য বৃক্ষ c_রাশিমালা_to_decl (বৃক্ষ, bool *, bool *);
বাহ্য বৃক্ষ c_finish_omp_construct (location_t, গণনা বৃক্ষ_code, বৃক্ষ, বৃক্ষ);
বাহ্য বৃক্ষ c_finish_oacc_data (location_t, বৃক্ষ, বৃক্ষ);
বাহ্য বৃক্ষ c_finish_oacc_host_data (location_t, বৃক্ষ, বৃক্ষ);
বাহ্য বৃক্ষ c_begin_omp_parallel (শূন্য);
বাহ্য বৃক্ষ c_finish_omp_parallel (location_t, বৃক্ষ, বৃক্ষ);
বাহ্য বৃক্ষ c_begin_omp_task (শূন্য);
বাহ্য বৃক্ষ c_finish_omp_task (location_t, বৃক্ষ, বৃক্ষ);
বাহ্য শূন্য c_finish_omp_cancel (location_t, বৃক্ষ);
বাহ্য শূন্য c_finish_omp_cancellation_point (location_t, বৃক্ষ);
বাহ্য বৃক্ষ c_finish_omp_clauses (বৃক্ষ, গণনা c_omp_region_type);
বাহ্য বৃক্ষ c_omp_finish_mapper_clauses (বৃক্ষ);
বাহ্য বৃক্ষ c_omp_mapper_lookup (বৃক্ষ, বৃক্ষ);
বাহ্য বৃক্ষ c_omp_extract_mapper_directive (বৃক্ষ);
বাহ্য বৃক্ষ c_omp_map_array_section (location_t, বৃক্ষ);
বাহ্য বৃক্ষ c_build_va_arg (location_t, বৃক্ষ, location_t, বৃক্ষ, বৃক্ষ);
বাহ্য বৃক্ষ c_finish_transaction (location_t, বৃক্ষ, পূর্ণাঙ্ক);
বাহ্য bool c_বৃক্ষ_equal (বৃক্ষ, বৃক্ষ);
বাহ্য বৃক্ষ c_build_function_call_vec (location_t, ধ্রুব vec<location_t>&,
				       বৃক্ষ, vec<বৃক্ষ, va_gc> *,
				       vec<বৃক্ষ, va_gc> *);
বাহ্য বৃক্ষ c_omp_clause_copy_ctor (বৃক্ষ, বৃক্ষ, বৃক্ষ);
বাহ্য বৃক্ষ c_reconstruct_complex_type (বৃক্ষ, বৃক্ষ);
বাহ্য বৃক্ষ c_type_canonical (বৃক্ষ);
বাহ্য বৃক্ষ c_build_type_attribute_variant (বৃক্ষ ntype, বৃক্ষ attrs);
বাহ্য বৃক্ষ c_build_pointer_type (বৃক্ষ type);
বাহ্য বৃক্ষ c_build_array_type (বৃক্ষ type, বৃক্ষ domain);
বাহ্য বৃক্ষ c_build_array_type_unspecified (বৃক্ষ type);
বাহ্য বৃক্ষ c_build_array_type_zero_size (বৃক্ষ type);
বাহ্য বৃক্ষ c_build_function_type (বৃক্ষ type, বৃক্ষ args, bool no = false);
বাহ্য বৃক্ষ c_build_pointer_type_for_mode (বৃক্ষ type, machine_mode mode, bool m);

/* Set to 0 at beginning of a function definition, set to 1 if
   a return statement that specifies a return value is seen.  */

বাহ্য পূর্ণাঙ্ক current_function_returns_মান;

/* Set to 0 at beginning of a function definition, set to 1 if
   a return statement with no argument is seen.  */

বাহ্য পূর্ণাঙ্ক current_function_returns_null;

/* Set to 0 at beginning of a function definition, set to 1 if
   a call to a noreturn function is seen.  */

বাহ্য পূর্ণাঙ্ক current_function_returns_abnormally;

/* In c-decl.cc */

/* Tell the binding oracle what kind of binding we are looking for.  */

গণনা c_oracle_request
{
  C_ORACLE_প্রতীক,
  C_ORACLE_TAG,
  C_ORACLE_LABEL
};

/* If this is non-NULL, then it is a "binding oracle" which can lazily
   create bindings when needed by the C compiler.  The oracle is told
   the name and type of the binding to create.  It can call pushdecl
   or the like to ensure the binding is visible; or do nothing,
   leaving the binding untouched.  c-decl.cc takes note of when the
   oracle has been called and will not call it again if it fails to
   create a given binding.  */

প্রকারনির্দেশ শূন্য c_binding_oracle_function (গণনা c_oracle_request, বৃক্ষ identifier);

বাহ্য c_binding_oracle_function *c_binding_oracle;

বাহ্য শূন্য c_finish_incomplete_decl (বৃক্ষ);
বাহ্য বৃক্ষ c_omp_reduction_id (গণনা বৃক্ষ_code, বৃক্ষ);
বাহ্য বৃক্ষ c_omp_reduction_decl (বৃক্ষ);
বাহ্য বৃক্ষ c_omp_reduction_lookup (বৃক্ষ, বৃক্ষ);
বাহ্য বৃক্ষ c_check_omp_declare_reduction_r (বৃক্ষ *, পূর্ণাঙ্ক *, শূন্য *);
বাহ্য বৃক্ষ c_omp_mapper_id (বৃক্ষ);
বাহ্য বৃক্ষ c_omp_mapper_decl (বৃক্ষ);
বাহ্য শূন্য c_omp_scan_mapper_bindings (location_t, বৃক্ষ *, বৃক্ষ);
বাহ্য bool c_check_in_current_scope (বৃক্ষ);
বাহ্য শূন্য c_pushtag (location_t, বৃক্ষ, বৃক্ষ);
বাহ্য শূন্য c_bind (location_t, বৃক্ষ, bool);
বাহ্য bool tag_exists_p (গণনা বৃক্ষ_code, বৃক্ষ);

বাহ্য শূন্য verify_counted_by_for_শীর্ষ_anonymous_type (বৃক্ষ);

/* In c-errors.cc */
বাহ্য bool pedwarn_c90 (location_t, diagnostics::option_id, ধ্রুব বর্ণ *, ...)
    ATTRIBUTE_GCC_DIAG(3,4);
বাহ্য bool pedwarn_c99 (location_t, diagnostics::option_id, ধ্রুব বর্ণ *, ...)
    ATTRIBUTE_GCC_DIAG(3,4);
বাহ্য bool pedwarn_c11 (location_t, diagnostics::option_id, ধ্রুব বর্ণ *, ...)
    ATTRIBUTE_GCC_DIAG(3,4);
বাহ্য bool pedwarn_c23 (location_t, diagnostics::option_id, ধ্রুব বর্ণ *, ...)
    ATTRIBUTE_GCC_DIAG(3,4);
বাহ্য শূন্য add_note_about_new_keyword (location_t loc,
					বৃক্ষ keyword_id);

বাহ্য শূন্য
set_c_রাশিমালা_source_range (c_রাশিমালা *রাশিমালা,
			 location_t start, location_t finish);

বাহ্য শূন্য
set_c_রাশিমালা_source_range (c_রাশিমালা *রাশিমালা,
			 source_range src_range);

/* In c-fold.cc */
বাহ্য vec<বৃক্ষ> incomplete_record_decls;

বাহ্য ধ্রুব বর্ণ *c_get_sarif_source_language (ধ্রুব বর্ণ *filename);

বাহ্য ধ্রুব সংরচনা scoped_attribute_specs std_attribute_table;

#যদি CHECKING_P
namespace selftest {
  বাহ্য শূন্য run_c_tests (শূন্য);
} // namespace selftest
#endif /* #if CHECKING_P */


#endif /* ! GCC_C_TREE_H */
