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

#ifndef GCC_C_ବୃକ୍ଷ_H
#define GCC_C_ବୃକ୍ଷ_H

#ଅନ୍ତର୍ଭାଵ "c-family/c-common.h"
#ଅନ୍ତର୍ଭାଵ "diagnostic.h"

/* struct lang_identifier is private to c-decl.cc, but langhooks.cc needs to
   know how big it is.  This is sanity-checked in c-decl.cc.  */
#define C_SIZEOF_STRUCT_LANG_IDENTIFIER \
  (ଆକାର (ସଂରଚନା c_common_identifier) + 3 * ଆକାର (ଶୂନ୍ୟ *))

/* In a RECORD_TYPE or UNION_TYPE, nonzero if any component is read-only.  */
#define C_TYPE_FIELDS_READONLY(TYPE) ବୃକ୍ଷ_LANG_FLAG_1 (TYPE)

/* In a RECORD_TYPE or UNION_TYPE, nonzero if any component is volatile.  */
#define C_TYPE_FIELDS_VOLATILE(TYPE) ବୃକ୍ଷ_LANG_FLAG_2 (TYPE)

/* In a RECORD_TYPE or UNION_TYPE, nonzero if any component is
   volatile, restrict-qualified or atomic; that is, has a type not
   permitted for a constexpr object.  */
#define C_TYPE_FIELDS_NON_CONSTEXPR(TYPE) ବୃକ୍ଷ_LANG_FLAG_4 (TYPE)

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
  TYPE_LANG_SLOT_1 (ବୃକ୍ଷ_CHECK4 (TYPE, RECORD_TYPE, UNION_TYPE, \
				 QUAL_UNION_TYPE, ENUMERAL_TYPE))

/* In an IDENTIFIER_NODE, nonzero if this identifier is actually a
   keyword.  C_RID_CODE (node) is then the RID_* value of the keyword.  */
#define C_IS_RESERVED_WORD(ID) ବୃକ୍ଷ_LANG_FLAG_0 (ID)

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
#define C_ARRAY_PARAMETER(ଗଣ୍ଠି_2) DECL_LANG_FLAG_0 (ଗଣ୍ଠି_2)

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
  DECL_LANG_FLAG_4 (ବୃକ୍ଷ_NOT_CHECK (EXP, FUNCTION_DECL))

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
	|| (!prototype_p (ବୃକ୍ଷ_TYPE (EXP))	\
	    && !fndecl_built_in_p (EXP)))

/* For FUNCTION_TYPE, a hidden list of types of arguments.  The same as
   TYPE_ARG_TYPES for functions with prototypes, but created for functions
   without prototypes.  */
#define TYPE_ACTUAL_ARG_TYPES(ଗଣ୍ଠି_2) \
  TYPE_LANG_SLOT_1 (FUNCTION_TYPE_CHECK (ଗଣ୍ଠି_2))

/* For a CONSTRUCTOR, whether some initializer contains a
   subexpression meaning it is not a constant expression.  */
#define CONSTRUCTOR_NON_CONST(ପଦସମଷ୍ଟି_2) ବୃକ୍ଷ_LANG_FLAG_1 (CONSTRUCTOR_CHECK (ପଦସମଷ୍ଟି_2))

/* For a SAVE_EXPR, nonzero if the operand of the SAVE_EXPR has already
   been folded.  */
#define SAVE_ପଦସମଷ୍ଟି_FOLDED_P(EXP)	ବୃକ୍ଷ_LANG_FLAG_1 (SAVE_ପଦସମଷ୍ଟି_CHECK (EXP))

/* Whether a type has boolean semantics: either a boolean type or an
   enumeration type with a boolean type as its underlying type.  */
#define C_BOOLEAN_TYPE_P(TYPE)						\
  (ବୃକ୍ଷ_CODE (TYPE) == BOOLEAN_TYPE					\
   || (ବୃକ୍ଷ_CODE (TYPE) == ENUMERAL_TYPE				\
       && ENUM_UNDERLYING_TYPE (TYPE) != NULL_ବୃକ୍ଷ			\
       && (ବୃକ୍ଷ_CODE (ENUM_UNDERLYING_TYPE (TYPE)) == BOOLEAN_TYPE	\
	   || c_hardbool_type_attr (TYPE))))

/* Record parser information about an expression that is irrelevant
   for code generation alongside a tree representing its value.  */
ସଂରଚନା c_ପଦସମଷ୍ଟି
{
  /* The value of the expression.  */
  ବୃକ୍ଷ ମୂଲ୍ୟ;
  /* Record the original unary/binary operator of an expression, which may
     have been changed by fold, STRING_CST for unparenthesized string
     constants, C_MAYBE_CONST_EXPR for __builtin_constant_p calls
     (even if parenthesized), for subexpressions, and for non-constant
     initializers, or ERROR_MARK for other expressions (including
     parenthesized expressions).  */
  ଗଣନା ବୃକ୍ଷ_code original_code;
  /* If not NULL, the original type of an expression.  This will
     differ from the type of the value field for an enum constant.
     The type of an enum constant is a plain integer type, but this
     field will be the enum type.  */
  ବୃକ୍ଷ original_type;

  /* The source range of this expression.  This is redundant
     for node values that have locations, but not all node kinds
     have locations (e.g. constants, and references to params, locals,
     etc), so we stash a copy here.  */
  source_range src_range;

  /* True if this was directly from a decimal constant token.  */
  bool m_decimal : 1;

  /* Access to the first and last locations within the source spelling
     of this expression.  */
  location_t get_start () ଅଚଳ { ଫେରନ୍ତୁ src_range.m_start; }
  location_t get_finish () ଅଚଳ { ଫେରନ୍ତୁ src_range.m_finish; }

  location_t get_location () ଅଚଳ
  {
    ଯଦି (ପଦସମଷ୍ଟି_HAS_LOCATION (ମୂଲ୍ୟ))
      ଫେରନ୍ତୁ ପଦସମଷ୍ଟି_LOCATION (ମୂଲ୍ୟ);
    ଅନ୍ୟଥା
      ଫେରନ୍ତୁ make_location (get_start (), get_start (), get_finish ());
  }

  /* Set the value to error_mark_node whilst ensuring that src_range
     and m_decimal are initialized.  */
  ଶୂନ୍ୟ set_error ()
  {
    ମୂଲ୍ୟ = error_mark_ଗଣ୍ଠି;
    src_range.m_start = UNKNOWN_LOCATION;
    src_range.m_finish = UNKNOWN_LOCATION;
    m_decimal = 0;
  }
};

/* Type alias for struct c_expr. This allows to use the structure
   inside the VEC types.  */
ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା c_ପଦସମଷ୍ଟି c_ପଦସମଷ୍ଟି_t;

/* A kind of type specifier.  Note that this information is currently
   only used to distinguish tag definitions, tag references and typeof
   uses.  */
ଗଣନା c_typespec_kind {
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
ସଂରଚନା c_typespec {
  /* What kind of type specifier this is.  */
  ଗଣନା c_typespec_kind kind;
  /* Whether the expression has operands suitable for use in constant
     expressions.  */
  bool ପଦସମଷ୍ଟି_const_operands;
  /* Whether the type specifier includes an enum type specifier (that
     is, ": specifier-qualifier-list" in a declaration using
     "enum").  */
  bool has_enum_type_specifier;
  /* The specifier itself.  */
  ବୃକ୍ଷ spec;
  /* An expression to be evaluated before the type specifier, in the
     case of typeof specifiers, or NULL otherwise or if no such
     expression is required for a particular typeof specifier.  In
     particular, when typeof is applied to an expression of variably
     modified type, that expression must be evaluated in order to
     determine array sizes that form part of the type, but the
     expression itself (as opposed to the array sizes) forms no part
     of the type and so needs to be recorded separately.  */
  ବୃକ୍ଷ ପଦସମଷ୍ଟି;
};

/* A storage class specifier.  */
ଗଣନା c_storage_class {
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
ଗଣନା c_typespec_keyword {
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
ଗଣନା c_declspec_word {
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
  cdw_ସଂଖ୍ୟା_of_elements /* This one must always be the last
			    enumerator.  */
};

ଗଣନା c_declspec_il {
  cdil_none,
  cdil_gimple,		/* __GIMPLE  */
  cdil_gimple_cfg,	/* __GIMPLE(cfg)  */
  cdil_gimple_ssa,	/* __GIMPLE(ssa)  */
  cdil_rtl		/* __RTL  */
};

/* A sequence of declaration specifiers in C.  When a new declaration
   specifier is added, please update the enum c_declspec_word above
   accordingly.  */
ସଂରଚନା c_declspecs {
  location_t locations[cdw_ସଂଖ୍ୟା_of_elements];
  /* The type specified, if a single type specifier such as a struct,
     union or enum specifier, typedef name or typeof specifies the
     whole type, or NULL_TREE if none or a keyword such as "void" or
     "char" is used.  Does not include qualifiers.  */
  ବୃକ୍ଷ type;
  /* Any expression to be evaluated before the type, from a typeof
     specifier.  */
  ବୃକ୍ଷ ପଦସମଷ୍ଟି;
  /* The attributes from a typedef decl.  */
  ବୃକ୍ଷ decl_attr;
  /* When parsing, the GNU attributes and prefix standard attributes.
     Outside the parser, this will be NULL; attributes (possibly from
     multiple lists) will be passed separately.  */
  ବୃକ୍ଷ attrs;
  /* When parsing, postfix standard attributes (which appertain to the
     type specified by the preceding declaration specifiers, unlike
     prefix standard attributes which appertain to the declaration or
     declarations as a whole).  */
  ବୃକ୍ଷ postfix_attrs;
  /* The pass to start compiling a __GIMPLE or __RTL function with.  */
  ଅକ୍ଷର *gimple_or_rtl_pass;
  /* ENTRY BB count.  */
  profile_ଗଣନା entry_bb_ଗଣନା;
  /* The base-2 log of the greatest alignment required by an _Alignas
     specifier, in bytes, or -1 if no such specifiers with nonzero
     alignment.  */
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା align_log;
  ସଂଘ {
    /* For the __intN declspec, this stores the index into the int_n_*
       arrays.  */
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା int_n_idx;
    /* For the _FloatN and _FloatNx declspec, this stores the index into
       the floatn_nx_types array.  */
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା floatn_nx_idx;
    /* For _BitInt(N) this stores the N.  */
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା bitint_prec;
  } u;
  /* The storage class specifier, or csc_none if none.  */
  ଗଣନା c_storage_class storage_class;
  /* Any type specifier keyword used such as "int", not reflecting
     modifiers such as "short", or cts_none if none.  */
  ଗଣନା c_typespec_keyword typespec_word : 8;
  /* The kind of type specifier if one has been seen, ctsk_none
     otherwise.  */
  ଗଣନା c_typespec_kind typespec_kind : 4;
  ଗଣନା c_declspec_il declspec_il : 3;
  /* Whether any expressions in typeof specifiers may appear in
     constant expressions.  */
  bool ପଦସମଷ୍ଟି_const_operands : 1;
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
ଗଣନା c_declarator_kind {
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

ସଂରଚନା c_arg_tag {
  /* The argument name.  */
  ବୃକ୍ଷ id;
  /* The type of the argument.  */
  ବୃକ୍ଷ type;
};


/* Information about the parameters in a function declarator.  */
ସଂରଚନା c_arg_info {
  /* A list of parameter decls.  */
  ବୃକ୍ଷ parms;
  /* A list of structure, union and enum tags defined.  */
  vec<c_arg_tag, va_gc> *tags;
  /* A list of argument types to go in the FUNCTION_TYPE.  */
  ବୃକ୍ଷ types;
  /* A list of non-parameter decls (notably enumeration constants)
     defined with the parameters.  */
  ବୃକ୍ଷ others;
  /* A compound expression of VLA sizes from the parameters, or NULL.
     In a function definition, these are used to ensure that
     side-effects in sizes of arrays converted to pointers (such as a
     parameter int i[n++]) take place; otherwise, they are
     ignored.  */
  ବୃକ୍ଷ pending_sizes;
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
ସଂରଚନା c_declarator {
  /* The kind of declarator.  */
  ଗଣନା c_declarator_kind kind;
  location_t id_loc; /* Currently only set for cdk_id, cdk_array. */
  /* Except for cdk_id, the contained declarator.  For cdk_id, NULL.  */
  ସଂରଚନା c_declarator *declarator;
  ସଂଘ {
    /* For identifiers.  */
    ସଂରଚନା {
      /* An IDENTIFIER_NODE, or NULL_TREE if an abstract
	 declarator.  */
      ବୃକ୍ଷ id;
      /* Any attributes (which apply to the declaration rather than to
	 the type described by the outer declarators).  */
      ବୃକ୍ଷ attrs;
    } id;
    /* For functions.  */
    ସଂରଚନା c_arg_info *arg_info;
    /* For arrays.  */
    ସଂରଚନା {
      /* The array dimension, or NULL for [] and [*].  */
      ବୃକ୍ଷ dimen;
      /* The qualifiers inside [].  */
      ପୂର୍ଣ୍ଣସଂଖ୍ୟା quals;
      /* The attributes (currently ignored) inside [].  */
      ବୃକ୍ଷ attrs;
      /* Whether [static] was used.  */
      bool static_p : 1;
      /* Whether [*] was used.  */
      bool vla_unspec_p : 1;
    } array;
    /* For pointers, the qualifiers on the pointer type.  */
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା pointer_quals;
    /* For attributes.  */
    ବୃକ୍ଷ attrs;
  } u;
};

/* A type name.  */
ସଂରଚନା c_type_name {
  /* The declaration specifiers.  */
  ସଂରଚନା c_declspecs *specs;
  /* The declarator.  */
  ସଂରଚନା c_declarator *declarator;
};

/* A parameter.  */
ସଂରଚନା c_parm {
  /* The declaration specifiers, minus any prefix attributes.  */
  ସଂରଚନା c_declspecs *specs;
  /* The attributes.  */
  ବୃକ୍ଷ attrs;
  /* The declarator.  */
  ସଂରଚନା c_declarator *declarator;
  /* The location of the parameter.  */
  location_t loc;
};

/* Used when parsing an enum.  Initialized by start_enum.  */
ସଂରଚନା c_enum_contents
{
  /* While defining an enum type, this is 1 plus the last enumerator
     constant value.  */
  ବୃକ୍ଷ enum_next_ମୂଲ୍ୟ;

  /* The enumeration type itself.  */
  ବୃକ୍ଷ enum_type;

  /* Nonzero means that there was overflow computing enum_next_value.  */
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା enum_overflow;
};

/* A type of reference to a static identifier in an inline
   function.  */
ଗଣନା c_inline_static_type {
  /* Identifier with internal linkage used in function that may be an
     inline definition (i.e., file-scope static).  */
  csi_internal,
  /* Modifiable object with static storage duration defined in
     function that may be an inline definition (i.e., local
     static).  */
  csi_modifiable
};

/* Record details of decls possibly used inside sizeof or typeof.  */
ସଂରଚନା maybe_used_decl
{
  /* The decl.  */
  ବୃକ୍ଷ decl;
  /* The level seen at (in_sizeof + in_typeof + in_countof + in_generic).  */
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା level;
  /* Seen in address-of.  */
  bool address;
  /* The next one at this level or above, or NULL.  */
  ସଂରଚନା maybe_used_decl *next;
};


/* in c-parser.cc */
ସଂରଚନା c_ବୃକ୍ଷ_token_vec;
ବାହ୍ୟ ଶୂନ୍ୟ c_parse_init (ଶୂନ୍ୟ);
ବାହ୍ୟ bool c_keyword_starts_typename (ଗଣନା rid keyword);

/* in c-aux-info.cc */
ବାହ୍ୟ ଶୂନ୍ୟ gen_aux_info_record (ବୃକ୍ଷ, ପୂର୍ଣ୍ଣସଂଖ୍ୟା, ପୂର୍ଣ୍ଣସଂଖ୍ୟା, ପୂର୍ଣ୍ଣସଂଖ୍ୟା);

/* in c-decl.cc */
ସଂରଚନା c_spot_bindings;
class c_struct_parse_info;
ବାହ୍ୟ ସଂରଚନା obstack parser_obstack;
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
ବାହ୍ୟ unsigned ଅକ୍ଷର in_statement;

ବାହ୍ୟ bool switch_statement_break_seen_p;

ବାହ୍ୟ bool global_bindings_p (ଶୂନ୍ୟ);
ବାହ୍ୟ ବୃକ୍ଷ pushdecl (ବୃକ୍ଷ);
ବାହ୍ୟ unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା start_underspecified_init (location_t, ବୃକ୍ଷ);
ବାହ୍ୟ ଶୂନ୍ୟ finish_underspecified_init (ବୃକ୍ଷ, unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା);
ବାହ୍ୟ ଶୂନ୍ୟ ଠେଲ_scope (ଶୂନ୍ୟ);
ବାହ୍ୟ ବୃକ୍ଷ କାଢ଼_scope (ଶୂନ୍ୟ);
ବାହ୍ୟ ଶୂନ୍ୟ c_mark_decl_jump_unsafe_in_current_scope ();
ବାହ୍ୟ ଶୂନ୍ୟ c_bindings_start_stmt_ପଦସମଷ୍ଟି (ସଂରଚନା c_spot_bindings *);
ବାହ୍ୟ ଶୂନ୍ୟ c_bindings_end_stmt_ପଦସମଷ୍ଟି (ସଂରଚନା c_spot_bindings *);

ବାହ୍ୟ ଶୂନ୍ୟ record_inline_static (location_t, ବୃକ୍ଷ, ବୃକ୍ଷ,
				  ଗଣନା c_inline_static_type);
ବାହ୍ୟ ଶୂନ୍ୟ c_init_decl_processing (ଶୂନ୍ୟ);
ବାହ୍ୟ ଶୂନ୍ୟ c_print_identifier (FILE *, ବୃକ୍ଷ, ପୂର୍ଣ୍ଣସଂଖ୍ୟା);
ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା quals_from_declspecs (ଅଚଳ ସଂରଚନା c_declspecs *);
ବାହ୍ୟ ସଂରଚନା c_declarator *build_array_declarator (location_t, ବୃକ୍ଷ,
    						    ସଂରଚନା c_declspecs *,
						    bool, bool);
ବାହ୍ୟ ବୃକ୍ଷ build_enumerator (location_t, location_t, ସଂରଚନା c_enum_contents *,
			      ବୃକ୍ଷ, ବୃକ୍ଷ);
ବାହ୍ୟ ବୃକ୍ଷ check_for_loop_decls (location_t, bool);
ବାହ୍ୟ ଶୂନ୍ୟ mark_forward_parm_decls (ଶୂନ୍ୟ);
ବାହ୍ୟ ଶୂନ୍ୟ declare_parm_level (ଶୂନ୍ୟ);
ବାହ୍ୟ ଶୂନ୍ୟ undeclared_variable (location_t, ବୃକ୍ଷ);
ବାହ୍ୟ ବୃକ୍ଷ lookup_label_for_goto (location_t, ବୃକ୍ଷ);
ବାହ୍ୟ ବୃକ୍ଷ declare_label (ବୃକ୍ଷ);
ବାହ୍ୟ ବୃକ୍ଷ define_label (location_t, ବୃକ୍ଷ);
ବାହ୍ୟ ସଂରଚନା c_spot_bindings *c_get_switch_bindings (ଶୂନ୍ୟ);
ବାହ୍ୟ ଶୂନ୍ୟ c_release_switch_bindings (ସଂରଚନା c_spot_bindings *);
ବାହ୍ୟ bool c_check_switch_jump_warnings (ସଂରଚନା c_spot_bindings *,
					  location_t, location_t);
ବାହ୍ୟ ଶୂନ୍ୟ finish_decl (ବୃକ୍ଷ, location_t, ବୃକ୍ଷ, ବୃକ୍ଷ, ବୃକ୍ଷ);
ବାହ୍ୟ ବୃକ୍ଷ finish_enum (ବୃକ୍ଷ, ବୃକ୍ଷ, ବୃକ୍ଷ);
ବାହ୍ୟ ଶୂନ୍ୟ finish_function (location_t = ନିବେଶ_location);
ବାହ୍ୟ ବୃକ୍ଷ finish_struct (location_t, ବୃକ୍ଷ, ବୃକ୍ଷ, ବୃକ୍ଷ,
			   class c_struct_parse_info *,
			   ବୃକ୍ଷ *ପଦସମଷ୍ଟି = ଖାଲି);
ବାହ୍ୟ ବୃକ୍ଷ c_simulate_enum_decl (location_t, ଅଚଳ ଅକ୍ଷର *,
				  vec<string_int_pair> *);
ବାହ୍ୟ ବୃକ୍ଷ c_simulate_record_decl (location_t, ଅଚଳ ଅକ୍ଷର *,
				    array_slice<ଅଚଳ ବୃକ୍ଷ>);
ବାହ୍ୟ ସଂରଚନା c_arg_info *build_arg_info (ଶୂନ୍ୟ);
ବାହ୍ୟ ସଂରଚନା c_arg_info *get_parm_info (bool, ବୃକ୍ଷ);
ବାହ୍ୟ ବୃକ୍ଷ grokfield (location_t, ସଂରଚନା c_declarator *,
		       ସଂରଚନା c_declspecs *, ବୃକ୍ଷ, ବୃକ୍ଷ *, ବୃକ୍ଷ *);
ବାହ୍ୟ ବୃକ୍ଷ groktypename (ସଂରଚନା c_type_name *, ବୃକ୍ଷ *, bool *);
ବାହ୍ୟ ବୃକ୍ଷ grokgenassoc (ସଂରଚନା c_type_name *);
ବାହ୍ୟ ବୃକ୍ଷ grokparm (ଅଚଳ ସଂରଚନା c_parm *, ବୃକ୍ଷ *);
ବାହ୍ୟ ବୃକ୍ଷ implicitly_declare (location_t, ବୃକ୍ଷ);
ବାହ୍ୟ ଶୂନ୍ୟ keep_next_level (ଶୂନ୍ୟ);
ବାହ୍ୟ ଶୂନ୍ୟ pending_xref_error (ଶୂନ୍ୟ);
ବାହ୍ୟ ଶୂନ୍ୟ c_ଠେଲ_function_context (ଶୂନ୍ୟ);
ବାହ୍ୟ ଶୂନ୍ୟ c_କାଢ଼_function_context (ଶୂନ୍ୟ);
ବାହ୍ୟ ଶୂନ୍ୟ ଠେଲ_parm_decl (ଅଚଳ ସଂରଚନା c_parm *, ବୃକ୍ଷ *);
ବାହ୍ୟ ସଂରଚନା c_declarator *set_array_declarator_inner (ସଂରଚନା c_declarator *,
							ସଂରଚନା c_declarator *);
ବାହ୍ୟ ବୃକ୍ଷ c_builtin_function (ବୃକ୍ଷ);
ବାହ୍ୟ ବୃକ୍ଷ c_builtin_function_ext_scope (ବୃକ୍ଷ);
ବାହ୍ୟ ବୃକ୍ଷ c_simulate_builtin_function_decl (ବୃକ୍ଷ);
ବାହ୍ୟ ଶୂନ୍ୟ c_warn_unused_attributes (ବୃକ୍ଷ);
ବାହ୍ୟ ବୃକ୍ଷ c_warn_type_attributes (ବୃକ୍ଷ, ବୃକ୍ଷ);
ବାହ୍ୟ ଶୂନ୍ୟ shadow_tag (ଅଚଳ ସଂରଚନା c_declspecs *);
ବାହ୍ୟ ଶୂନ୍ୟ shadow_tag_warned (ଅଚଳ ସଂରଚନା c_declspecs *, ପୂର୍ଣ୍ଣସଂଖ୍ୟା);
ବାହ୍ୟ ବୃକ୍ଷ start_enum (location_t, ସଂରଚନା c_enum_contents *, ବୃକ୍ଷ, ବୃକ୍ଷ,
			bool potential_nesting_p);
ବାହ୍ୟ bool start_function (ସଂରଚନା c_declspecs *, ସଂରଚନା c_declarator *, ବୃକ୍ଷ);
ବାହ୍ୟ ବୃକ୍ଷ start_decl (ସଂରଚନା c_declarator *, ସଂରଚନା c_declspecs *, bool,
			ବୃକ୍ଷ, bool = true, location_t * = ଖାଲି);
ବାହ୍ୟ ବୃକ୍ଷ start_struct (location_t, ଗଣନା ବୃକ୍ଷ_code, ବୃକ୍ଷ,
			  class c_struct_parse_info **);
ବାହ୍ୟ ଶୂନ୍ୟ store_parm_decls (ଶୂନ୍ୟ);
ବାହ୍ୟ ଶୂନ୍ୟ store_parm_decls_from (ସଂରଚନା c_arg_info *);
ବାହ୍ୟ ଶୂନ୍ୟ temp_store_parm_decls (ବୃକ୍ଷ, ବୃକ୍ଷ);
ବାହ୍ୟ ଶୂନ୍ୟ temp_କାଢ଼_parm_decls (ଶୂନ୍ୟ);
ବାହ୍ୟ ବୃକ୍ଷ xref_tag (ଗଣନା ବୃକ୍ଷ_code, ବୃକ୍ଷ);
ବାହ୍ୟ ସଂରଚନା c_typespec parser_xref_tag (location_t, ଗଣନା ବୃକ୍ଷ_code, ବୃକ୍ଷ,
					  bool, ବୃକ୍ଷ, bool);
ବାହ୍ୟ ସଂରଚନା c_parm *build_c_parm (ସଂରଚନା c_declspecs *, ବୃକ୍ଷ,
				    ସଂରଚନା c_declarator *, location_t);
ବାହ୍ୟ ସଂରଚନା c_declarator *build_attrs_declarator (ବୃକ୍ଷ,
						    ସଂରଚନା c_declarator *);
ବାହ୍ୟ ସଂରଚନା c_declarator *build_function_declarator (ସଂରଚନା c_arg_info *,
						       ସଂରଚନା c_declarator *);
ବାହ୍ୟ ସଂରଚନା c_declarator *build_id_declarator (ବୃକ୍ଷ);
ବାହ୍ୟ ସଂରଚନା c_declarator *make_pointer_declarator (ସଂରଚନା c_declspecs *,
						     ସଂରଚନା c_declarator *);
ବାହ୍ୟ ସଂରଚନା c_declspecs *build_null_declspecs (ଶୂନ୍ୟ);
ବାହ୍ୟ ସଂରଚନା c_declspecs *declspecs_add_qual (location_t,
					       ସଂରଚନା c_declspecs *, ବୃକ୍ଷ);
ବାହ୍ୟ ସଂରଚନା c_declspecs *declspecs_add_type (location_t,
					       ସଂରଚନା c_declspecs *,
					       ସଂରଚନା c_typespec);
ବାହ୍ୟ ସଂରଚନା c_declspecs *declspecs_add_scspec (location_t,
						 ସଂରଚନା c_declspecs *, ବୃକ୍ଷ);
ବାହ୍ୟ ସଂରଚନା c_declspecs *declspecs_add_attrs (location_t,
						ସଂରଚନା c_declspecs *, ବୃକ୍ଷ);
ବାହ୍ୟ ସଂରଚନା c_declspecs *declspecs_add_addrspace (location_t,
						    ସଂରଚନା c_declspecs *,
						    addr_space_t);
ବାହ୍ୟ ସଂରଚନା c_declspecs *declspecs_add_alignas (location_t,
						  ସଂରଚନା c_declspecs *, ବୃକ୍ଷ);
ବାହ୍ୟ ସଂରଚନା c_declspecs *finish_declspecs (ସଂରଚନା c_declspecs *);
ବାହ୍ୟ size_t c_ବୃକ୍ଷ_size (ଗଣନା ବୃକ୍ଷ_code);
ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା c_get_loop_names (ବୃକ୍ଷ, bool, ବୃକ୍ଷ *);
ବାହ୍ୟ ଶୂନ୍ୟ c_release_loop_names (ପୂର୍ଣ୍ଣସଂଖ୍ୟା);
ବାହ୍ୟ ବୃକ୍ଷ c_finish_bc_name (location_t, ବୃକ୍ଷ, bool);

/* in c-objc-common.cc */
ବାହ୍ୟ bool c_objc_common_init (ଶୂନ୍ୟ);
ବାହ୍ୟ bool c_missing_noreturn_ok_p (ବୃକ୍ଷ);
ବାହ୍ୟ bool c_warn_unused_global_decl (const_ବୃକ୍ଷ);
ବାହ୍ୟ ଶୂନ୍ୟ c_initialize_diagnostics (diagnostics::context *);
ବାହ୍ୟ bool c_var_mod_p (ବୃକ୍ଷ x, ବୃକ୍ଷ fn);
ବାହ୍ୟ alias_set_type c_get_alias_set (ବୃକ୍ଷ);
ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା c_type_dwarf_attribute (const_ବୃକ୍ଷ, ପୂର୍ଣ୍ଣସଂଖ୍ୟା);
ବାହ୍ୟ ବୃକ୍ଷ c_enum_underlying_base_type (const_ବୃକ୍ଷ);

/* in c-typeck.cc */
ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା in_alignof;
ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା in_sizeof;
ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା in_countof;
ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା in_typeof;
ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା in_generic;
ବାହ୍ୟ bool c_in_omp_for;
ବାହ୍ୟ bool c_omp_array_section_p;

ବାହ୍ୟ ବୃକ୍ଷ c_last_sizeof_arg;
ବାହ୍ୟ location_t c_last_sizeof_loc;

ବାହ୍ୟ ସଂରଚନା c_switch *c_switch_ଗଦା;

ବାହ୍ୟ bool null_pointer_constant_p (const_ବୃକ୍ଷ);


ଧାଡ଼ିଭିତରେ bool
c_type_variably_modified_p (ବୃକ୍ଷ t)
{
  ଯଦି (error_mark_ଗଣ୍ଠି == t)
    ଫେରନ୍ତୁ false;
  ଯଦି (C_TYPE_VARIABLY_MODIFIED (t))
    ଫେରନ୍ତୁ true;
  ଯଦି (TYPE_STRUCTURAL_EQUALITY_P (t))
    {
      /* The flag may not have been set yet because of incomplete
	 structure or union types completed later.  */
      ବାଛ (ବୃକ୍ଷ_CODE (t))
	{
	ସ୍ଥିତି ARRAY_TYPE:
	ସ୍ଥିତି FUNCTION_TYPE:
	ସ୍ଥିତି POINTER_TYPE:
	  /* Recurse.  */
	  ଯଦି (c_type_variably_modified_p (ବୃକ୍ଷ_TYPE (t)))
	    {
	      C_TYPE_VARIABLY_MODIFIED (t) = 1;
	      ଫେରନ୍ତୁ true;
	    }
	  ଭାଙ୍ଗ;
	ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
	  ଭାଙ୍ଗ;
	}
    }
  ଫେରନ୍ତୁ false;
}

ଧାଡ଼ିଭିତରେ bool
c_type_unspecified_p (ବୃକ୍ଷ t)
{
  ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି != t
	 && C_TYPE_VARIABLE_SIZE (t) && ବୃକ୍ଷ_CODE (t) == ARRAY_TYPE
	 && TYPE_DOMAIN (t) && TYPE_MAX_ମୂଲ୍ୟ (TYPE_DOMAIN (t))
	 && ବୃକ୍ଷ_CODE (TYPE_MAX_ମୂଲ୍ୟ (TYPE_DOMAIN (t))) == COMPOUND_ପଦସମଷ୍ଟି
	 && integer_zerop (ବୃକ୍ଷ_OPERAND (TYPE_MAX_ମୂଲ୍ୟ (TYPE_DOMAIN (t)), 0))
	 && integer_zerop (ବୃକ୍ଷ_OPERAND (TYPE_MAX_ମୂଲ୍ୟ (TYPE_DOMAIN (t)), 1));
}

ବାହ୍ୟ bool zero_length_array_type_p (const_ବୃକ୍ଷ type);
ବାହ୍ୟ bool char_type_p (ବୃକ୍ଷ);
ବାହ୍ୟ ବୃକ୍ଷ c_type_tag (const_ବୃକ୍ଷ t);
ବାହ୍ୟ ବୃକ୍ଷ c_objc_common_truthvalue_conversion (location_t, ବୃକ୍ଷ,
						 ବୃକ୍ଷ = integer_type_ଗଣ୍ଠି);
ବାହ୍ୟ ବୃକ୍ଷ require_complete_type (location_t, ବୃକ୍ଷ);
ବାହ୍ୟ bool same_translation_unit_p (const_ବୃକ୍ଷ, const_ବୃକ୍ଷ);
ବାହ୍ୟ bool comptypes (ବୃକ୍ଷ, ବୃକ୍ଷ);
ବାହ୍ୟ bool comptypes_same_p (ବୃକ୍ଷ, ବୃକ୍ଷ);
ବାହ୍ୟ bool comptypes_equiv_p (ବୃକ୍ଷ, ବୃକ୍ଷ);
ବାହ୍ୟ bool comptypes_check_enum_int (ବୃକ୍ଷ, ବୃକ୍ଷ, bool *);
ବାହ୍ୟ bool c_mark_addressable (ବୃକ୍ଷ, bool = false, bool = false);
ବାହ୍ୟ ଶୂନ୍ୟ c_incomplete_type_error (location_t, const_ବୃକ୍ଷ, const_ବୃକ୍ଷ);
ବାହ୍ୟ ବୃକ୍ଷ c_type_promotes_to (ବୃକ୍ଷ);
ବାହ୍ୟ ସଂରଚନା c_ପଦସମଷ୍ଟି default_function_array_conversion (location_t,
							ସଂରଚନା c_ପଦସମଷ୍ଟି);
ବାହ୍ୟ ସଂରଚନା c_ପଦସମଷ୍ଟି default_function_array_read_conversion (location_t,
							     ସଂରଚନା c_ପଦସମଷ୍ଟି);
ବାହ୍ୟ ସଂରଚନା c_ପଦସମଷ୍ଟି convert_lvalue_to_rvalue (location_t, ସଂରଚନା c_ପଦସମଷ୍ଟି,
					       bool, bool, bool = false);
ବାହ୍ୟ ବୃକ୍ଷ decl_constant_ମୂଲ୍ୟ_1 (ବୃକ୍ଷ, bool);
ବାହ୍ୟ ଶୂନ୍ୟ mark_exp_read (ବୃକ୍ଷ);
ବାହ୍ୟ ବୃକ୍ଷ composite_type (ବୃକ୍ଷ, ବୃକ୍ଷ);
ବାହ୍ୟ ବୃକ୍ଷ lookup_field (const_ବୃକ୍ଷ, ବୃକ୍ଷ);
ବାହ୍ୟ ବୃକ୍ଷ build_component_ref (location_t, ବୃକ୍ଷ, ବୃକ୍ଷ, location_t,
				 location_t);
ବାହ୍ୟ ବୃକ୍ଷ handle_counted_by_for_component_ref (location_t, ବୃକ୍ଷ);
ବାହ୍ୟ ବୃକ୍ଷ build_array_ref (location_t, ବୃକ୍ଷ, ବୃକ୍ଷ);
ବାହ୍ୟ ବୃକ୍ଷ build_omp_array_section (location_t, ବୃକ୍ଷ, ବୃକ୍ଷ, ବୃକ୍ଷ);
ବାହ୍ୟ ବୃକ୍ଷ build_external_ref (location_t, ବୃକ୍ଷ, bool, ବୃକ୍ଷ *);
ବାହ୍ୟ ଶୂନ୍ୟ କାଢ଼_maybe_used (bool);
ବାହ୍ୟ ସଂରଚନା maybe_used_decl *save_maybe_used ();
ବାହ୍ୟ ଶୂନ୍ୟ restore_maybe_used (ସଂରଚନା maybe_used_decl *);
ବାହ୍ୟ ଶୂନ୍ୟ mark_decl_used (ବୃକ୍ଷ, bool);
ବାହ୍ୟ ସଂରଚନା c_ପଦସମଷ୍ଟି c_ପଦସମଷ୍ଟି_sizeof_ପଦସମଷ୍ଟି (location_t, ସଂରଚନା c_ପଦସମଷ୍ଟି);
ବାହ୍ୟ ସଂରଚନା c_ପଦସମଷ୍ଟି c_ପଦସମଷ୍ଟି_sizeof_type (location_t, ସଂରଚନା c_type_name *);
ବାହ୍ୟ ସଂରଚନା c_ପଦସମଷ୍ଟି c_ପଦସମଷ୍ଟି_countof_ପଦସମଷ୍ଟି (location_t, ସଂରଚନା c_ପଦସମଷ୍ଟି);
ବାହ୍ୟ ସଂରଚନା c_ପଦସମଷ୍ଟି c_ପଦସମଷ୍ଟି_countof_type (location_t loc,
					  ସଂରଚନା c_type_name *);
ବାହ୍ୟ ସଂରଚନା c_ପଦସମଷ୍ଟି c_ପଦସମଷ୍ଟି_maxof_type (location_t loc, ସଂରଚନା c_type_name *);
ବାହ୍ୟ ସଂରଚନା c_ପଦସମଷ୍ଟି c_ପଦସମଷ୍ଟି_minof_type (location_t loc, ସଂରଚନା c_type_name *);
ବାହ୍ୟ ସଂରଚନା c_ପଦସମଷ୍ଟି parser_build_unary_op (location_t, ଗଣନା ବୃକ୍ଷ_code,
    					    ସଂରଚନା c_ପଦସମଷ୍ଟି);
ବାହ୍ୟ ସଂରଚନା c_ପଦସମଷ୍ଟି parser_build_ଦ୍ୱିମିକ_op (location_t,
    					     ଗଣନା ବୃକ୍ଷ_code, ସଂରଚନା c_ପଦସମଷ୍ଟି,
					     ସଂରଚନା c_ପଦସମଷ୍ଟି, ବୃକ୍ଷ);
ବାହ୍ୟ ବୃକ୍ଷ build_conditional_ପଦସମଷ୍ଟି (location_t, ବୃକ୍ଷ, bool, ବୃକ୍ଷ, ବୃକ୍ଷ,
				    location_t, ବୃକ୍ଷ, ବୃକ୍ଷ, location_t);
ବାହ୍ୟ ବୃକ୍ଷ build_compound_ପଦସମଷ୍ଟି (location_t, ବୃକ୍ଷ, ବୃକ୍ଷ);
ବାହ୍ୟ ବୃକ୍ଷ c_cast_ପଦସମଷ୍ଟି (location_t, ସଂରଚନା c_type_name *, ବୃକ୍ଷ);
ବାହ୍ୟ ବୃକ୍ଷ build_c_cast (location_t, ବୃକ୍ଷ, ବୃକ୍ଷ);
ବାହ୍ୟ ଶୂନ୍ୟ store_init_ମୂଲ୍ୟ (location_t, ବୃକ୍ଷ, ବୃକ୍ଷ, ବୃକ୍ଷ);
ବାହ୍ୟ ଶୂନ୍ୟ maybe_warn_string_init (location_t, ବୃକ୍ଷ, ସଂରଚନା c_ପଦସମଷ୍ଟି);
ବାହ୍ୟ ଶୂନ୍ୟ start_init (ବୃକ୍ଷ, ବୃକ୍ଷ, bool, bool, rich_location *);
ବାହ୍ୟ ଶୂନ୍ୟ finish_init (ଶୂନ୍ୟ);
ବାହ୍ୟ ଶୂନ୍ୟ really_start_incremental_init (ବୃକ୍ଷ);
ବାହ୍ୟ ଶୂନ୍ୟ finish_implicit_inits (location_t, ସଂରଚନା obstack *);
ବାହ୍ୟ ଶୂନ୍ୟ ଠେଲ_init_level (location_t, ପୂର୍ଣ୍ଣସଂଖ୍ୟା, ସଂରଚନା obstack *);
ବାହ୍ୟ ସଂରଚନା c_ପଦସମଷ୍ଟି କାଢ଼_init_level (location_t, ପୂର୍ଣ୍ଣସଂଖ୍ୟା, ସଂରଚନା obstack *,
				     location_t);
ବାହ୍ୟ ଶୂନ୍ୟ set_init_index (location_t, ବୃକ୍ଷ, ବୃକ୍ଷ, ସଂରଚନା obstack *);
ବାହ୍ୟ ଶୂନ୍ୟ set_init_label (location_t, ବୃକ୍ଷ, location_t, ସଂରଚନା obstack *);
unsigned c_maybe_optimize_large_byte_initializer (ଶୂନ୍ୟ);
ବାହ୍ୟ ଶୂନ୍ୟ process_init_element (location_t, ସଂରଚନା c_ପଦସମଷ୍ଟି, bool,
				  ସଂରଚନା obstack *);
ବାହ୍ୟ ବୃକ୍ଷ build_compound_literal (location_t, ବୃକ୍ଷ, ବୃକ୍ଷ, bool,
				    unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା, ସଂରଚନା c_declspecs *);
ବାହ୍ୟ ଶୂନ୍ୟ check_compound_literal_type (location_t, ସଂରଚନା c_type_name *);
ବାହ୍ୟ ବୃକ୍ଷ c_start_switch (location_t, location_t, ବୃକ୍ଷ, bool, ବୃକ୍ଷ);
ବାହ୍ୟ ଶୂନ୍ୟ c_finish_switch (ବୃକ୍ଷ, ବୃକ୍ଷ);
ବାହ୍ୟ ବୃକ୍ଷ build_asm_ପଦସମଷ୍ଟି (location_t, ବୃକ୍ଷ, ବୃକ୍ଷ, ବୃକ୍ଷ, ବୃକ୍ଷ, ବୃକ୍ଷ, bool,
			    bool);
ବାହ୍ୟ ବୃକ୍ଷ build_asm_stmt (bool, ବୃକ୍ଷ);
ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା c_types_compatible_p (ବୃକ୍ଷ, ବୃକ୍ଷ);
ବାହ୍ୟ ବୃକ୍ଷ c_begin_compound_stmt (bool);
ବାହ୍ୟ ବୃକ୍ଷ c_end_compound_stmt (location_t, ବୃକ୍ଷ, bool);
ବାହ୍ୟ ଶୂନ୍ୟ c_finish_if_stmt (location_t, ବୃକ୍ଷ, ବୃକ୍ଷ, ବୃକ୍ଷ);
ବାହ୍ୟ ଶୂନ୍ୟ c_finish_loop (location_t, location_t, ବୃକ୍ଷ, location_t, ବୃକ୍ଷ,
			   ବୃକ୍ଷ, ବୃକ୍ଷ, ବୃକ୍ଷ, bool);
ବାହ୍ୟ ବୃକ୍ଷ c_begin_stmt_ପଦସମଷ୍ଟି (ଶୂନ୍ୟ);
ବାହ୍ୟ ବୃକ୍ଷ c_finish_stmt_ପଦସମଷ୍ଟି (location_t, ବୃକ୍ଷ);
ବାହ୍ୟ ବୃକ୍ଷ c_process_ପଦସମଷ୍ଟି_stmt (location_t, ବୃକ୍ଷ);
ବାହ୍ୟ ବୃକ୍ଷ c_finish_ପଦସମଷ୍ଟି_stmt (location_t, ବୃକ୍ଷ);
ବାହ୍ୟ ବୃକ୍ଷ c_finish_return (location_t, ବୃକ୍ଷ, ବୃକ୍ଷ, bool = false);
ବାହ୍ୟ ବୃକ୍ଷ c_finish_bc_stmt (location_t, ବୃକ୍ଷ, bool, ବୃକ୍ଷ);
ବାହ୍ୟ ବୃକ୍ଷ c_finish_goto_label (location_t, ବୃକ୍ଷ);
ବାହ୍ୟ ବୃକ୍ଷ c_finish_goto_ptr (location_t, c_ପଦସମଷ୍ଟି val);
ବାହ୍ୟ ବୃକ୍ଷ c_ପଦସମଷ୍ଟି_to_decl (ବୃକ୍ଷ, bool *, bool *);
ବାହ୍ୟ ବୃକ୍ଷ c_finish_omp_construct (location_t, ଗଣନା ବୃକ୍ଷ_code, ବୃକ୍ଷ, ବୃକ୍ଷ);
ବାହ୍ୟ ବୃକ୍ଷ c_finish_oacc_data (location_t, ବୃକ୍ଷ, ବୃକ୍ଷ);
ବାହ୍ୟ ବୃକ୍ଷ c_finish_oacc_host_data (location_t, ବୃକ୍ଷ, ବୃକ୍ଷ);
ବାହ୍ୟ ବୃକ୍ଷ c_begin_omp_parallel (ଶୂନ୍ୟ);
ବାହ୍ୟ ବୃକ୍ଷ c_finish_omp_parallel (location_t, ବୃକ୍ଷ, ବୃକ୍ଷ);
ବାହ୍ୟ ବୃକ୍ଷ c_begin_omp_task (ଶୂନ୍ୟ);
ବାହ୍ୟ ବୃକ୍ଷ c_finish_omp_task (location_t, ବୃକ୍ଷ, ବୃକ୍ଷ);
ବାହ୍ୟ ଶୂନ୍ୟ c_finish_omp_cancel (location_t, ବୃକ୍ଷ);
ବାହ୍ୟ ଶୂନ୍ୟ c_finish_omp_cancellation_point (location_t, ବୃକ୍ଷ);
ବାହ୍ୟ ବୃକ୍ଷ c_finish_omp_clauses (ବୃକ୍ଷ, ଗଣନା c_omp_region_type);
ବାହ୍ୟ ବୃକ୍ଷ c_omp_finish_mapper_clauses (ବୃକ୍ଷ);
ବାହ୍ୟ ବୃକ୍ଷ c_omp_mapper_lookup (ବୃକ୍ଷ, ବୃକ୍ଷ);
ବାହ୍ୟ ବୃକ୍ଷ c_omp_extract_mapper_directive (ବୃକ୍ଷ);
ବାହ୍ୟ ବୃକ୍ଷ c_omp_map_array_section (location_t, ବୃକ୍ଷ);
ବାହ୍ୟ ବୃକ୍ଷ c_build_va_arg (location_t, ବୃକ୍ଷ, location_t, ବୃକ୍ଷ, ବୃକ୍ଷ);
ବାହ୍ୟ ବୃକ୍ଷ c_finish_transaction (location_t, ବୃକ୍ଷ, ପୂର୍ଣ୍ଣସଂଖ୍ୟା);
ବାହ୍ୟ bool c_ବୃକ୍ଷ_equal (ବୃକ୍ଷ, ବୃକ୍ଷ);
ବାହ୍ୟ ବୃକ୍ଷ c_build_function_call_vec (location_t, ଅଚଳ vec<location_t>&,
				       ବୃକ୍ଷ, vec<ବୃକ୍ଷ, va_gc> *,
				       vec<ବୃକ୍ଷ, va_gc> *);
ବାହ୍ୟ ବୃକ୍ଷ c_omp_clause_copy_ctor (ବୃକ୍ଷ, ବୃକ୍ଷ, ବୃକ୍ଷ);
ବାହ୍ୟ ବୃକ୍ଷ c_reconstruct_complex_type (ବୃକ୍ଷ, ବୃକ୍ଷ);
ବାହ୍ୟ ବୃକ୍ଷ c_type_canonical (ବୃକ୍ଷ);
ବାହ୍ୟ ବୃକ୍ଷ c_build_type_attribute_variant (ବୃକ୍ଷ ntype, ବୃକ୍ଷ attrs);
ବାହ୍ୟ ବୃକ୍ଷ c_build_pointer_type (ବୃକ୍ଷ type);
ବାହ୍ୟ ବୃକ୍ଷ c_build_array_type (ବୃକ୍ଷ type, ବୃକ୍ଷ domain);
ବାହ୍ୟ ବୃକ୍ଷ c_build_array_type_unspecified (ବୃକ୍ଷ type);
ବାହ୍ୟ ବୃକ୍ଷ c_build_array_type_zero_size (ବୃକ୍ଷ type);
ବାହ୍ୟ ବୃକ୍ଷ c_build_function_type (ବୃକ୍ଷ type, ବୃକ୍ଷ args, bool no = false);
ବାହ୍ୟ ବୃକ୍ଷ c_build_pointer_type_for_mode (ବୃକ୍ଷ type, machine_mode mode, bool m);

/* Set to 0 at beginning of a function definition, set to 1 if
   a return statement that specifies a return value is seen.  */

ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା current_function_returns_ମୂଲ୍ୟ;

/* Set to 0 at beginning of a function definition, set to 1 if
   a return statement with no argument is seen.  */

ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା current_function_returns_null;

/* Set to 0 at beginning of a function definition, set to 1 if
   a call to a noreturn function is seen.  */

ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା current_function_returns_abnormally;

/* In c-decl.cc */

/* Tell the binding oracle what kind of binding we are looking for.  */

ଗଣନା c_oracle_request
{
  C_ORACLE_ପ୍ରତୀକ,
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

ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ c_binding_oracle_function (ଗଣନା c_oracle_request, ବୃକ୍ଷ identifier);

ବାହ୍ୟ c_binding_oracle_function *c_binding_oracle;

ବାହ୍ୟ ଶୂନ୍ୟ c_finish_incomplete_decl (ବୃକ୍ଷ);
ବାହ୍ୟ ବୃକ୍ଷ c_omp_reduction_id (ଗଣନା ବୃକ୍ଷ_code, ବୃକ୍ଷ);
ବାହ୍ୟ ବୃକ୍ଷ c_omp_reduction_decl (ବୃକ୍ଷ);
ବାହ୍ୟ ବୃକ୍ଷ c_omp_reduction_lookup (ବୃକ୍ଷ, ବୃକ୍ଷ);
ବାହ୍ୟ ବୃକ୍ଷ c_check_omp_declare_reduction_r (ବୃକ୍ଷ *, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *, ଶୂନ୍ୟ *);
ବାହ୍ୟ ବୃକ୍ଷ c_omp_mapper_id (ବୃକ୍ଷ);
ବାହ୍ୟ ବୃକ୍ଷ c_omp_mapper_decl (ବୃକ୍ଷ);
ବାହ୍ୟ ଶୂନ୍ୟ c_omp_scan_mapper_bindings (location_t, ବୃକ୍ଷ *, ବୃକ୍ଷ);
ବାହ୍ୟ bool c_check_in_current_scope (ବୃକ୍ଷ);
ବାହ୍ୟ ଶୂନ୍ୟ c_pushtag (location_t, ବୃକ୍ଷ, ବୃକ୍ଷ);
ବାହ୍ୟ ଶୂନ୍ୟ c_bind (location_t, ବୃକ୍ଷ, bool);
ବାହ୍ୟ bool tag_exists_p (ଗଣନା ବୃକ୍ଷ_code, ବୃକ୍ଷ);

ବାହ୍ୟ ଶୂନ୍ୟ verify_counted_by_for_ଶୀର୍ଷ_anonymous_type (ବୃକ୍ଷ);

/* In c-errors.cc */
ବାହ୍ୟ bool pedwarn_c90 (location_t, diagnostics::option_id, ଅଚଳ ଅକ୍ଷର *, ...)
    ATTRIBUTE_GCC_DIAG(3,4);
ବାହ୍ୟ bool pedwarn_c99 (location_t, diagnostics::option_id, ଅଚଳ ଅକ୍ଷର *, ...)
    ATTRIBUTE_GCC_DIAG(3,4);
ବାହ୍ୟ bool pedwarn_c11 (location_t, diagnostics::option_id, ଅଚଳ ଅକ୍ଷର *, ...)
    ATTRIBUTE_GCC_DIAG(3,4);
ବାହ୍ୟ bool pedwarn_c23 (location_t, diagnostics::option_id, ଅଚଳ ଅକ୍ଷର *, ...)
    ATTRIBUTE_GCC_DIAG(3,4);
ବାହ୍ୟ ଶୂନ୍ୟ add_note_about_new_keyword (location_t loc,
					ବୃକ୍ଷ keyword_id);

ବାହ୍ୟ ଶୂନ୍ୟ
set_c_ପଦସମଷ୍ଟି_source_range (c_ପଦସମଷ୍ଟି *ପଦସମଷ୍ଟି,
			 location_t start, location_t finish);

ବାହ୍ୟ ଶୂନ୍ୟ
set_c_ପଦସମଷ୍ଟି_source_range (c_ପଦସମଷ୍ଟି *ପଦସମଷ୍ଟି,
			 source_range src_range);

/* In c-fold.cc */
ବାହ୍ୟ vec<ବୃକ୍ଷ> incomplete_record_decls;

ବାହ୍ୟ ଅଚଳ ଅକ୍ଷର *c_get_sarif_source_language (ଅଚଳ ଅକ୍ଷର *filename);

ବାହ୍ୟ ଅଚଳ ସଂରଚନା scoped_attribute_specs std_attribute_table;

#ଯଦି CHECKING_P
namespace selftest {
  ବାହ୍ୟ ଶୂନ୍ୟ run_c_tests (ଶୂନ୍ୟ);
} // namespace selftest
#endif /* #if CHECKING_P */


#endif /* ! GCC_C_TREE_H */
