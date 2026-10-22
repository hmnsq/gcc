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

#ifndef GCC_C_വൃക്ഷം_H
#define GCC_C_വൃക്ഷം_H

#അന്തര്ഭാവ "c-family/c-common.h"
#അന്തര്ഭാവ "diagnostic.h"

/* struct lang_identifier is private to c-decl.cc, but langhooks.cc needs to
   know how big it is.  This is sanity-checked in c-decl.cc.  */
#define C_SIZEOF_STRUCT_LANG_IDENTIFIER \
  (വലുപ്പം (ഘടന c_common_identifier) + 3 * വലുപ്പം (ശൂന്യം *))

/* In a RECORD_TYPE or UNION_TYPE, nonzero if any component is read-only.  */
#define C_TYPE_FIELDS_READONLY(TYPE) വൃക്ഷം_LANG_FLAG_1 (TYPE)

/* In a RECORD_TYPE or UNION_TYPE, nonzero if any component is volatile.  */
#define C_TYPE_FIELDS_VOLATILE(TYPE) വൃക്ഷം_LANG_FLAG_2 (TYPE)

/* In a RECORD_TYPE or UNION_TYPE, nonzero if any component is
   volatile, restrict-qualified or atomic; that is, has a type not
   permitted for a constexpr object.  */
#define C_TYPE_FIELDS_NON_CONSTEXPR(TYPE) വൃക്ഷം_LANG_FLAG_4 (TYPE)

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
  TYPE_LANG_SLOT_1 (വൃക്ഷം_CHECK4 (TYPE, RECORD_TYPE, UNION_TYPE, \
				 QUAL_UNION_TYPE, ENUMERAL_TYPE))

/* In an IDENTIFIER_NODE, nonzero if this identifier is actually a
   keyword.  C_RID_CODE (node) is then the RID_* value of the keyword.  */
#define C_IS_RESERVED_WORD(ID) വൃക്ഷം_LANG_FLAG_0 (ID)

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
#define C_ARRAY_PARAMETER(കണ്ണി_2) DECL_LANG_FLAG_0 (കണ്ണി_2)

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
  DECL_LANG_FLAG_4 (വൃക്ഷം_NOT_CHECK (EXP, FUNCTION_DECL))

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
	|| (!prototype_p (വൃക്ഷം_TYPE (EXP))	\
	    && !fndecl_built_in_p (EXP)))

/* For FUNCTION_TYPE, a hidden list of types of arguments.  The same as
   TYPE_ARG_TYPES for functions with prototypes, but created for functions
   without prototypes.  */
#define TYPE_ACTUAL_ARG_TYPES(കണ്ണി_2) \
  TYPE_LANG_SLOT_1 (FUNCTION_TYPE_CHECK (കണ്ണി_2))

/* For a CONSTRUCTOR, whether some initializer contains a
   subexpression meaning it is not a constant expression.  */
#define CONSTRUCTOR_NON_CONST(വ്യഞ്ജകം_2) വൃക്ഷം_LANG_FLAG_1 (CONSTRUCTOR_CHECK (വ്യഞ്ജകം_2))

/* For a SAVE_EXPR, nonzero if the operand of the SAVE_EXPR has already
   been folded.  */
#define SAVE_വ്യഞ്ജകം_FOLDED_P(EXP)	വൃക്ഷം_LANG_FLAG_1 (SAVE_വ്യഞ്ജകം_CHECK (EXP))

/* Whether a type has boolean semantics: either a boolean type or an
   enumeration type with a boolean type as its underlying type.  */
#define C_BOOLEAN_TYPE_P(TYPE)						\
  (വൃക്ഷം_CODE (TYPE) == BOOLEAN_TYPE					\
   || (വൃക്ഷം_CODE (TYPE) == ENUMERAL_TYPE				\
       && ENUM_UNDERLYING_TYPE (TYPE) != NULL_വൃക്ഷം			\
       && (വൃക്ഷം_CODE (ENUM_UNDERLYING_TYPE (TYPE)) == BOOLEAN_TYPE	\
	   || c_hardbool_type_attr (TYPE))))

/* Record parser information about an expression that is irrelevant
   for code generation alongside a tree representing its value.  */
ഘടന c_വ്യഞ്ജകം
{
  /* The value of the expression.  */
  വൃക്ഷം മൂല്യം;
  /* Record the original unary/binary operator of an expression, which may
     have been changed by fold, STRING_CST for unparenthesized string
     constants, C_MAYBE_CONST_EXPR for __builtin_constant_p calls
     (even if parenthesized), for subexpressions, and for non-constant
     initializers, or ERROR_MARK for other expressions (including
     parenthesized expressions).  */
  എണ്ണൽ വൃക്ഷം_code original_code;
  /* If not NULL, the original type of an expression.  This will
     differ from the type of the value field for an enum constant.
     The type of an enum constant is a plain integer type, but this
     field will be the enum type.  */
  വൃക്ഷം original_type;

  /* The source range of this expression.  This is redundant
     for node values that have locations, but not all node kinds
     have locations (e.g. constants, and references to params, locals,
     etc), so we stash a copy here.  */
  source_range src_range;

  /* True if this was directly from a decimal constant token.  */
  bool m_decimal : 1;

  /* Access to the first and last locations within the source spelling
     of this expression.  */
  location_t get_start () സ്ഥിരം { തിരികെ src_range.m_start; }
  location_t get_finish () സ്ഥിരം { തിരികെ src_range.m_finish; }

  location_t get_location () സ്ഥിരം
  {
    എങ്കിൽ (വ്യഞ്ജകം_HAS_LOCATION (മൂല്യം))
      തിരികെ വ്യഞ്ജകം_LOCATION (മൂല്യം);
    അല്ലെങ്കിൽ
      തിരികെ make_location (get_start (), get_start (), get_finish ());
  }

  /* Set the value to error_mark_node whilst ensuring that src_range
     and m_decimal are initialized.  */
  ശൂന്യം set_error ()
  {
    മൂല്യം = error_mark_കണ്ണി;
    src_range.m_start = UNKNOWN_LOCATION;
    src_range.m_finish = UNKNOWN_LOCATION;
    m_decimal = 0;
  }
};

/* Type alias for struct c_expr. This allows to use the structure
   inside the VEC types.  */
തരനിർവചനം ഘടന c_വ്യഞ്ജകം c_വ്യഞ്ജകം_t;

/* A kind of type specifier.  Note that this information is currently
   only used to distinguish tag definitions, tag references and typeof
   uses.  */
എണ്ണൽ c_typespec_kind {
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
ഘടന c_typespec {
  /* What kind of type specifier this is.  */
  എണ്ണൽ c_typespec_kind kind;
  /* Whether the expression has operands suitable for use in constant
     expressions.  */
  bool വ്യഞ്ജകം_const_operands;
  /* Whether the type specifier includes an enum type specifier (that
     is, ": specifier-qualifier-list" in a declaration using
     "enum").  */
  bool has_enum_type_specifier;
  /* The specifier itself.  */
  വൃക്ഷം spec;
  /* An expression to be evaluated before the type specifier, in the
     case of typeof specifiers, or NULL otherwise or if no such
     expression is required for a particular typeof specifier.  In
     particular, when typeof is applied to an expression of variably
     modified type, that expression must be evaluated in order to
     determine array sizes that form part of the type, but the
     expression itself (as opposed to the array sizes) forms no part
     of the type and so needs to be recorded separately.  */
  വൃക്ഷം വ്യഞ്ജകം;
};

/* A storage class specifier.  */
എണ്ണൽ c_storage_class {
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
എണ്ണൽ c_typespec_keyword {
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
എണ്ണൽ c_declspec_word {
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
  cdw_സംഖ്യ_of_elements /* This one must always be the last
			    enumerator.  */
};

എണ്ണൽ c_declspec_il {
  cdil_none,
  cdil_gimple,		/* __GIMPLE  */
  cdil_gimple_cfg,	/* __GIMPLE(cfg)  */
  cdil_gimple_ssa,	/* __GIMPLE(ssa)  */
  cdil_rtl		/* __RTL  */
};

/* A sequence of declaration specifiers in C.  When a new declaration
   specifier is added, please update the enum c_declspec_word above
   accordingly.  */
ഘടന c_declspecs {
  location_t locations[cdw_സംഖ്യ_of_elements];
  /* The type specified, if a single type specifier such as a struct,
     union or enum specifier, typedef name or typeof specifies the
     whole type, or NULL_TREE if none or a keyword such as "void" or
     "char" is used.  Does not include qualifiers.  */
  വൃക്ഷം type;
  /* Any expression to be evaluated before the type, from a typeof
     specifier.  */
  വൃക്ഷം വ്യഞ്ജകം;
  /* The attributes from a typedef decl.  */
  വൃക്ഷം decl_attr;
  /* When parsing, the GNU attributes and prefix standard attributes.
     Outside the parser, this will be NULL; attributes (possibly from
     multiple lists) will be passed separately.  */
  വൃക്ഷം attrs;
  /* When parsing, postfix standard attributes (which appertain to the
     type specified by the preceding declaration specifiers, unlike
     prefix standard attributes which appertain to the declaration or
     declarations as a whole).  */
  വൃക്ഷം postfix_attrs;
  /* The pass to start compiling a __GIMPLE or __RTL function with.  */
  അക്ഷരം *gimple_or_rtl_pass;
  /* ENTRY BB count.  */
  profile_എണ്ണം entry_bb_എണ്ണം;
  /* The base-2 log of the greatest alignment required by an _Alignas
     specifier, in bytes, or -1 if no such specifiers with nonzero
     alignment.  */
  പൂർണ്ണസംഖ്യ align_log;
  സംഘം {
    /* For the __intN declspec, this stores the index into the int_n_*
       arrays.  */
    പൂർണ്ണസംഖ്യ int_n_idx;
    /* For the _FloatN and _FloatNx declspec, this stores the index into
       the floatn_nx_types array.  */
    പൂർണ്ണസംഖ്യ floatn_nx_idx;
    /* For _BitInt(N) this stores the N.  */
    പൂർണ്ണസംഖ്യ bitint_prec;
  } u;
  /* The storage class specifier, or csc_none if none.  */
  എണ്ണൽ c_storage_class storage_class;
  /* Any type specifier keyword used such as "int", not reflecting
     modifiers such as "short", or cts_none if none.  */
  എണ്ണൽ c_typespec_keyword typespec_word : 8;
  /* The kind of type specifier if one has been seen, ctsk_none
     otherwise.  */
  എണ്ണൽ c_typespec_kind typespec_kind : 4;
  എണ്ണൽ c_declspec_il declspec_il : 3;
  /* Whether any expressions in typeof specifiers may appear in
     constant expressions.  */
  bool വ്യഞ്ജകം_const_operands : 1;
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
എണ്ണൽ c_declarator_kind {
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

ഘടന c_arg_tag {
  /* The argument name.  */
  വൃക്ഷം id;
  /* The type of the argument.  */
  വൃക്ഷം type;
};


/* Information about the parameters in a function declarator.  */
ഘടന c_arg_info {
  /* A list of parameter decls.  */
  വൃക്ഷം parms;
  /* A list of structure, union and enum tags defined.  */
  vec<c_arg_tag, va_gc> *tags;
  /* A list of argument types to go in the FUNCTION_TYPE.  */
  വൃക്ഷം types;
  /* A list of non-parameter decls (notably enumeration constants)
     defined with the parameters.  */
  വൃക്ഷം others;
  /* A compound expression of VLA sizes from the parameters, or NULL.
     In a function definition, these are used to ensure that
     side-effects in sizes of arrays converted to pointers (such as a
     parameter int i[n++]) take place; otherwise, they are
     ignored.  */
  വൃക്ഷം pending_sizes;
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
ഘടന c_declarator {
  /* The kind of declarator.  */
  എണ്ണൽ c_declarator_kind kind;
  location_t id_loc; /* Currently only set for cdk_id, cdk_array. */
  /* Except for cdk_id, the contained declarator.  For cdk_id, NULL.  */
  ഘടന c_declarator *declarator;
  സംഘം {
    /* For identifiers.  */
    ഘടന {
      /* An IDENTIFIER_NODE, or NULL_TREE if an abstract
	 declarator.  */
      വൃക്ഷം id;
      /* Any attributes (which apply to the declaration rather than to
	 the type described by the outer declarators).  */
      വൃക്ഷം attrs;
    } id;
    /* For functions.  */
    ഘടന c_arg_info *arg_info;
    /* For arrays.  */
    ഘടന {
      /* The array dimension, or NULL for [] and [*].  */
      വൃക്ഷം dimen;
      /* The qualifiers inside [].  */
      പൂർണ്ണസംഖ്യ quals;
      /* The attributes (currently ignored) inside [].  */
      വൃക്ഷം attrs;
      /* Whether [static] was used.  */
      bool static_p : 1;
      /* Whether [*] was used.  */
      bool vla_unspec_p : 1;
    } array;
    /* For pointers, the qualifiers on the pointer type.  */
    പൂർണ്ണസംഖ്യ pointer_quals;
    /* For attributes.  */
    വൃക്ഷം attrs;
  } u;
};

/* A type name.  */
ഘടന c_type_name {
  /* The declaration specifiers.  */
  ഘടന c_declspecs *specs;
  /* The declarator.  */
  ഘടന c_declarator *declarator;
};

/* A parameter.  */
ഘടന c_parm {
  /* The declaration specifiers, minus any prefix attributes.  */
  ഘടന c_declspecs *specs;
  /* The attributes.  */
  വൃക്ഷം attrs;
  /* The declarator.  */
  ഘടന c_declarator *declarator;
  /* The location of the parameter.  */
  location_t loc;
};

/* Used when parsing an enum.  Initialized by start_enum.  */
ഘടന c_enum_contents
{
  /* While defining an enum type, this is 1 plus the last enumerator
     constant value.  */
  വൃക്ഷം enum_next_മൂല്യം;

  /* The enumeration type itself.  */
  വൃക്ഷം enum_type;

  /* Nonzero means that there was overflow computing enum_next_value.  */
  പൂർണ്ണസംഖ്യ enum_overflow;
};

/* A type of reference to a static identifier in an inline
   function.  */
എണ്ണൽ c_inline_static_type {
  /* Identifier with internal linkage used in function that may be an
     inline definition (i.e., file-scope static).  */
  csi_internal,
  /* Modifiable object with static storage duration defined in
     function that may be an inline definition (i.e., local
     static).  */
  csi_modifiable
};

/* Record details of decls possibly used inside sizeof or typeof.  */
ഘടന maybe_used_decl
{
  /* The decl.  */
  വൃക്ഷം decl;
  /* The level seen at (in_sizeof + in_typeof + in_countof + in_generic).  */
  പൂർണ്ണസംഖ്യ level;
  /* Seen in address-of.  */
  bool address;
  /* The next one at this level or above, or NULL.  */
  ഘടന maybe_used_decl *next;
};


/* in c-parser.cc */
ഘടന c_വൃക്ഷം_token_vec;
ബാഹ്യ ശൂന്യം c_parse_init (ശൂന്യം);
ബാഹ്യ bool c_keyword_starts_typename (എണ്ണൽ rid keyword);

/* in c-aux-info.cc */
ബാഹ്യ ശൂന്യം gen_aux_info_record (വൃക്ഷം, പൂർണ്ണസംഖ്യ, പൂർണ്ണസംഖ്യ, പൂർണ്ണസംഖ്യ);

/* in c-decl.cc */
ഘടന c_spot_bindings;
class c_struct_parse_info;
ബാഹ്യ ഘടന obstack parser_obstack;
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
ബാഹ്യ unsigned അക്ഷരം in_statement;

ബാഹ്യ bool switch_statement_break_seen_p;

ബാഹ്യ bool global_bindings_p (ശൂന്യം);
ബാഹ്യ വൃക്ഷം pushdecl (വൃക്ഷം);
ബാഹ്യ unsigned പൂർണ്ണസംഖ്യ start_underspecified_init (location_t, വൃക്ഷം);
ബാഹ്യ ശൂന്യം finish_underspecified_init (വൃക്ഷം, unsigned പൂർണ്ണസംഖ്യ);
ബാഹ്യ ശൂന്യം തള്ളുക_scope (ശൂന്യം);
ബാഹ്യ വൃക്ഷം എടുക്കുക_scope (ശൂന്യം);
ബാഹ്യ ശൂന്യം c_mark_decl_jump_unsafe_in_current_scope ();
ബാഹ്യ ശൂന്യം c_bindings_start_stmt_വ്യഞ്ജകം (ഘടന c_spot_bindings *);
ബാഹ്യ ശൂന്യം c_bindings_end_stmt_വ്യഞ്ജകം (ഘടന c_spot_bindings *);

ബാഹ്യ ശൂന്യം record_inline_static (location_t, വൃക്ഷം, വൃക്ഷം,
				  എണ്ണൽ c_inline_static_type);
ബാഹ്യ ശൂന്യം c_init_decl_processing (ശൂന്യം);
ബാഹ്യ ശൂന്യം c_print_identifier (FILE *, വൃക്ഷം, പൂർണ്ണസംഖ്യ);
ബാഹ്യ പൂർണ്ണസംഖ്യ quals_from_declspecs (സ്ഥിരം ഘടന c_declspecs *);
ബാഹ്യ ഘടന c_declarator *build_array_declarator (location_t, വൃക്ഷം,
    						    ഘടന c_declspecs *,
						    bool, bool);
ബാഹ്യ വൃക്ഷം build_enumerator (location_t, location_t, ഘടന c_enum_contents *,
			      വൃക്ഷം, വൃക്ഷം);
ബാഹ്യ വൃക്ഷം check_for_loop_decls (location_t, bool);
ബാഹ്യ ശൂന്യം mark_forward_parm_decls (ശൂന്യം);
ബാഹ്യ ശൂന്യം declare_parm_level (ശൂന്യം);
ബാഹ്യ ശൂന്യം undeclared_variable (location_t, വൃക്ഷം);
ബാഹ്യ വൃക്ഷം lookup_label_for_goto (location_t, വൃക്ഷം);
ബാഹ്യ വൃക്ഷം declare_label (വൃക്ഷം);
ബാഹ്യ വൃക്ഷം define_label (location_t, വൃക്ഷം);
ബാഹ്യ ഘടന c_spot_bindings *c_get_switch_bindings (ശൂന്യം);
ബാഹ്യ ശൂന്യം c_release_switch_bindings (ഘടന c_spot_bindings *);
ബാഹ്യ bool c_check_switch_jump_warnings (ഘടന c_spot_bindings *,
					  location_t, location_t);
ബാഹ്യ ശൂന്യം finish_decl (വൃക്ഷം, location_t, വൃക്ഷം, വൃക്ഷം, വൃക്ഷം);
ബാഹ്യ വൃക്ഷം finish_enum (വൃക്ഷം, വൃക്ഷം, വൃക്ഷം);
ബാഹ്യ ശൂന്യം finish_function (location_t = നിവേശം_location);
ബാഹ്യ വൃക്ഷം finish_struct (location_t, വൃക്ഷം, വൃക്ഷം, വൃക്ഷം,
			   class c_struct_parse_info *,
			   വൃക്ഷം *വ്യഞ്ജകം = ശൂന്യ);
ബാഹ്യ വൃക്ഷം c_simulate_enum_decl (location_t, സ്ഥിരം അക്ഷരം *,
				  vec<string_int_pair> *);
ബാഹ്യ വൃക്ഷം c_simulate_record_decl (location_t, സ്ഥിരം അക്ഷരം *,
				    array_slice<സ്ഥിരം വൃക്ഷം>);
ബാഹ്യ ഘടന c_arg_info *build_arg_info (ശൂന്യം);
ബാഹ്യ ഘടന c_arg_info *get_parm_info (bool, വൃക്ഷം);
ബാഹ്യ വൃക്ഷം grokfield (location_t, ഘടന c_declarator *,
		       ഘടന c_declspecs *, വൃക്ഷം, വൃക്ഷം *, വൃക്ഷം *);
ബാഹ്യ വൃക്ഷം groktypename (ഘടന c_type_name *, വൃക്ഷം *, bool *);
ബാഹ്യ വൃക്ഷം grokgenassoc (ഘടന c_type_name *);
ബാഹ്യ വൃക്ഷം grokparm (സ്ഥിരം ഘടന c_parm *, വൃക്ഷം *);
ബാഹ്യ വൃക്ഷം implicitly_declare (location_t, വൃക്ഷം);
ബാഹ്യ ശൂന്യം keep_next_level (ശൂന്യം);
ബാഹ്യ ശൂന്യം pending_xref_error (ശൂന്യം);
ബാഹ്യ ശൂന്യം c_തള്ളുക_function_context (ശൂന്യം);
ബാഹ്യ ശൂന്യം c_എടുക്കുക_function_context (ശൂന്യം);
ബാഹ്യ ശൂന്യം തള്ളുക_parm_decl (സ്ഥിരം ഘടന c_parm *, വൃക്ഷം *);
ബാഹ്യ ഘടന c_declarator *set_array_declarator_inner (ഘടന c_declarator *,
							ഘടന c_declarator *);
ബാഹ്യ വൃക്ഷം c_builtin_function (വൃക്ഷം);
ബാഹ്യ വൃക്ഷം c_builtin_function_ext_scope (വൃക്ഷം);
ബാഹ്യ വൃക്ഷം c_simulate_builtin_function_decl (വൃക്ഷം);
ബാഹ്യ ശൂന്യം c_warn_unused_attributes (വൃക്ഷം);
ബാഹ്യ വൃക്ഷം c_warn_type_attributes (വൃക്ഷം, വൃക്ഷം);
ബാഹ്യ ശൂന്യം shadow_tag (സ്ഥിരം ഘടന c_declspecs *);
ബാഹ്യ ശൂന്യം shadow_tag_warned (സ്ഥിരം ഘടന c_declspecs *, പൂർണ്ണസംഖ്യ);
ബാഹ്യ വൃക്ഷം start_enum (location_t, ഘടന c_enum_contents *, വൃക്ഷം, വൃക്ഷം,
			bool potential_nesting_p);
ബാഹ്യ bool start_function (ഘടന c_declspecs *, ഘടന c_declarator *, വൃക്ഷം);
ബാഹ്യ വൃക്ഷം start_decl (ഘടന c_declarator *, ഘടന c_declspecs *, bool,
			വൃക്ഷം, bool = true, location_t * = ശൂന്യ);
ബാഹ്യ വൃക്ഷം start_struct (location_t, എണ്ണൽ വൃക്ഷം_code, വൃക്ഷം,
			  class c_struct_parse_info **);
ബാഹ്യ ശൂന്യം store_parm_decls (ശൂന്യം);
ബാഹ്യ ശൂന്യം store_parm_decls_from (ഘടന c_arg_info *);
ബാഹ്യ ശൂന്യം temp_store_parm_decls (വൃക്ഷം, വൃക്ഷം);
ബാഹ്യ ശൂന്യം temp_എടുക്കുക_parm_decls (ശൂന്യം);
ബാഹ്യ വൃക്ഷം xref_tag (എണ്ണൽ വൃക്ഷം_code, വൃക്ഷം);
ബാഹ്യ ഘടന c_typespec parser_xref_tag (location_t, എണ്ണൽ വൃക്ഷം_code, വൃക്ഷം,
					  bool, വൃക്ഷം, bool);
ബാഹ്യ ഘടന c_parm *build_c_parm (ഘടന c_declspecs *, വൃക്ഷം,
				    ഘടന c_declarator *, location_t);
ബാഹ്യ ഘടന c_declarator *build_attrs_declarator (വൃക്ഷം,
						    ഘടന c_declarator *);
ബാഹ്യ ഘടന c_declarator *build_function_declarator (ഘടന c_arg_info *,
						       ഘടന c_declarator *);
ബാഹ്യ ഘടന c_declarator *build_id_declarator (വൃക്ഷം);
ബാഹ്യ ഘടന c_declarator *make_pointer_declarator (ഘടന c_declspecs *,
						     ഘടന c_declarator *);
ബാഹ്യ ഘടന c_declspecs *build_null_declspecs (ശൂന്യം);
ബാഹ്യ ഘടന c_declspecs *declspecs_add_qual (location_t,
					       ഘടന c_declspecs *, വൃക്ഷം);
ബാഹ്യ ഘടന c_declspecs *declspecs_add_type (location_t,
					       ഘടന c_declspecs *,
					       ഘടന c_typespec);
ബാഹ്യ ഘടന c_declspecs *declspecs_add_scspec (location_t,
						 ഘടന c_declspecs *, വൃക്ഷം);
ബാഹ്യ ഘടന c_declspecs *declspecs_add_attrs (location_t,
						ഘടന c_declspecs *, വൃക്ഷം);
ബാഹ്യ ഘടന c_declspecs *declspecs_add_addrspace (location_t,
						    ഘടന c_declspecs *,
						    addr_space_t);
ബാഹ്യ ഘടന c_declspecs *declspecs_add_alignas (location_t,
						  ഘടന c_declspecs *, വൃക്ഷം);
ബാഹ്യ ഘടന c_declspecs *finish_declspecs (ഘടന c_declspecs *);
ബാഹ്യ size_t c_വൃക്ഷം_size (എണ്ണൽ വൃക്ഷം_code);
ബാഹ്യ പൂർണ്ണസംഖ്യ c_get_loop_names (വൃക്ഷം, bool, വൃക്ഷം *);
ബാഹ്യ ശൂന്യം c_release_loop_names (പൂർണ്ണസംഖ്യ);
ബാഹ്യ വൃക്ഷം c_finish_bc_name (location_t, വൃക്ഷം, bool);

/* in c-objc-common.cc */
ബാഹ്യ bool c_objc_common_init (ശൂന്യം);
ബാഹ്യ bool c_missing_noreturn_ok_p (വൃക്ഷം);
ബാഹ്യ bool c_warn_unused_global_decl (const_വൃക്ഷം);
ബാഹ്യ ശൂന്യം c_initialize_diagnostics (diagnostics::context *);
ബാഹ്യ bool c_var_mod_p (വൃക്ഷം x, വൃക്ഷം fn);
ബാഹ്യ alias_set_type c_get_alias_set (വൃക്ഷം);
ബാഹ്യ പൂർണ്ണസംഖ്യ c_type_dwarf_attribute (const_വൃക്ഷം, പൂർണ്ണസംഖ്യ);
ബാഹ്യ വൃക്ഷം c_enum_underlying_base_type (const_വൃക്ഷം);

/* in c-typeck.cc */
ബാഹ്യ പൂർണ്ണസംഖ്യ in_alignof;
ബാഹ്യ പൂർണ്ണസംഖ്യ in_sizeof;
ബാഹ്യ പൂർണ്ണസംഖ്യ in_countof;
ബാഹ്യ പൂർണ്ണസംഖ്യ in_typeof;
ബാഹ്യ പൂർണ്ണസംഖ്യ in_generic;
ബാഹ്യ bool c_in_omp_for;
ബാഹ്യ bool c_omp_array_section_p;

ബാഹ്യ വൃക്ഷം c_last_sizeof_arg;
ബാഹ്യ location_t c_last_sizeof_loc;

ബാഹ്യ ഘടന c_switch *c_switch_അട്ടി;

ബാഹ്യ bool null_pointer_constant_p (const_വൃക്ഷം);


വരിയിൽ bool
c_type_variably_modified_p (വൃക്ഷം t)
{
  എങ്കിൽ (error_mark_കണ്ണി == t)
    തിരികെ false;
  എങ്കിൽ (C_TYPE_VARIABLY_MODIFIED (t))
    തിരികെ true;
  എങ്കിൽ (TYPE_STRUCTURAL_EQUALITY_P (t))
    {
      /* The flag may not have been set yet because of incomplete
	 structure or union types completed later.  */
      തിരഞ്ഞെടുപ്പ് (വൃക്ഷം_CODE (t))
	{
	അവസ്ഥ ARRAY_TYPE:
	അവസ്ഥ FUNCTION_TYPE:
	അവസ്ഥ POINTER_TYPE:
	  /* Recurse.  */
	  എങ്കിൽ (c_type_variably_modified_p (വൃക്ഷം_TYPE (t)))
	    {
	      C_TYPE_VARIABLY_MODIFIED (t) = 1;
	      തിരികെ true;
	    }
	  നിർത്തുക;
	സ്ഥിരസ്ഥിതി:
	  നിർത്തുക;
	}
    }
  തിരികെ false;
}

വരിയിൽ bool
c_type_unspecified_p (വൃക്ഷം t)
{
  തിരികെ error_mark_കണ്ണി != t
	 && C_TYPE_VARIABLE_SIZE (t) && വൃക്ഷം_CODE (t) == ARRAY_TYPE
	 && TYPE_DOMAIN (t) && TYPE_MAX_മൂല്യം (TYPE_DOMAIN (t))
	 && വൃക്ഷം_CODE (TYPE_MAX_മൂല്യം (TYPE_DOMAIN (t))) == COMPOUND_വ്യഞ്ജകം
	 && integer_zerop (വൃക്ഷം_OPERAND (TYPE_MAX_മൂല്യം (TYPE_DOMAIN (t)), 0))
	 && integer_zerop (വൃക്ഷം_OPERAND (TYPE_MAX_മൂല്യം (TYPE_DOMAIN (t)), 1));
}

ബാഹ്യ bool zero_length_array_type_p (const_വൃക്ഷം type);
ബാഹ്യ bool char_type_p (വൃക്ഷം);
ബാഹ്യ വൃക്ഷം c_type_tag (const_വൃക്ഷം t);
ബാഹ്യ വൃക്ഷം c_objc_common_truthvalue_conversion (location_t, വൃക്ഷം,
						 വൃക്ഷം = integer_type_കണ്ണി);
ബാഹ്യ വൃക്ഷം require_complete_type (location_t, വൃക്ഷം);
ബാഹ്യ bool same_translation_unit_p (const_വൃക്ഷം, const_വൃക്ഷം);
ബാഹ്യ bool comptypes (വൃക്ഷം, വൃക്ഷം);
ബാഹ്യ bool comptypes_same_p (വൃക്ഷം, വൃക്ഷം);
ബാഹ്യ bool comptypes_equiv_p (വൃക്ഷം, വൃക്ഷം);
ബാഹ്യ bool comptypes_check_enum_int (വൃക്ഷം, വൃക്ഷം, bool *);
ബാഹ്യ bool c_mark_addressable (വൃക്ഷം, bool = false, bool = false);
ബാഹ്യ ശൂന്യം c_incomplete_type_error (location_t, const_വൃക്ഷം, const_വൃക്ഷം);
ബാഹ്യ വൃക്ഷം c_type_promotes_to (വൃക്ഷം);
ബാഹ്യ ഘടന c_വ്യഞ്ജകം default_function_array_conversion (location_t,
							ഘടന c_വ്യഞ്ജകം);
ബാഹ്യ ഘടന c_വ്യഞ്ജകം default_function_array_read_conversion (location_t,
							     ഘടന c_വ്യഞ്ജകം);
ബാഹ്യ ഘടന c_വ്യഞ്ജകം convert_lvalue_to_rvalue (location_t, ഘടന c_വ്യഞ്ജകം,
					       bool, bool, bool = false);
ബാഹ്യ വൃക്ഷം decl_constant_മൂല്യം_1 (വൃക്ഷം, bool);
ബാഹ്യ ശൂന്യം mark_exp_read (വൃക്ഷം);
ബാഹ്യ വൃക്ഷം composite_type (വൃക്ഷം, വൃക്ഷം);
ബാഹ്യ വൃക്ഷം lookup_field (const_വൃക്ഷം, വൃക്ഷം);
ബാഹ്യ വൃക്ഷം build_component_ref (location_t, വൃക്ഷം, വൃക്ഷം, location_t,
				 location_t);
ബാഹ്യ വൃക്ഷം handle_counted_by_for_component_ref (location_t, വൃക്ഷം);
ബാഹ്യ വൃക്ഷം build_array_ref (location_t, വൃക്ഷം, വൃക്ഷം);
ബാഹ്യ വൃക്ഷം build_omp_array_section (location_t, വൃക്ഷം, വൃക്ഷം, വൃക്ഷം);
ബാഹ്യ വൃക്ഷം build_external_ref (location_t, വൃക്ഷം, bool, വൃക്ഷം *);
ബാഹ്യ ശൂന്യം എടുക്കുക_maybe_used (bool);
ബാഹ്യ ഘടന maybe_used_decl *save_maybe_used ();
ബാഹ്യ ശൂന്യം restore_maybe_used (ഘടന maybe_used_decl *);
ബാഹ്യ ശൂന്യം mark_decl_used (വൃക്ഷം, bool);
ബാഹ്യ ഘടന c_വ്യഞ്ജകം c_വ്യഞ്ജകം_sizeof_വ്യഞ്ജകം (location_t, ഘടന c_വ്യഞ്ജകം);
ബാഹ്യ ഘടന c_വ്യഞ്ജകം c_വ്യഞ്ജകം_sizeof_type (location_t, ഘടന c_type_name *);
ബാഹ്യ ഘടന c_വ്യഞ്ജകം c_വ്യഞ്ജകം_countof_വ്യഞ്ജകം (location_t, ഘടന c_വ്യഞ്ജകം);
ബാഹ്യ ഘടന c_വ്യഞ്ജകം c_വ്യഞ്ജകം_countof_type (location_t loc,
					  ഘടന c_type_name *);
ബാഹ്യ ഘടന c_വ്യഞ്ജകം c_വ്യഞ്ജകം_maxof_type (location_t loc, ഘടന c_type_name *);
ബാഹ്യ ഘടന c_വ്യഞ്ജകം c_വ്യഞ്ജകം_minof_type (location_t loc, ഘടന c_type_name *);
ബാഹ്യ ഘടന c_വ്യഞ്ജകം parser_build_unary_op (location_t, എണ്ണൽ വൃക്ഷം_code,
    					    ഘടന c_വ്യഞ്ജകം);
ബാഹ്യ ഘടന c_വ്യഞ്ജകം parser_build_ദ്വിമാന_op (location_t,
    					     എണ്ണൽ വൃക്ഷം_code, ഘടന c_വ്യഞ്ജകം,
					     ഘടന c_വ്യഞ്ജകം, വൃക്ഷം);
ബാഹ്യ വൃക്ഷം build_conditional_വ്യഞ്ജകം (location_t, വൃക്ഷം, bool, വൃക്ഷം, വൃക്ഷം,
				    location_t, വൃക്ഷം, വൃക്ഷം, location_t);
ബാഹ്യ വൃക്ഷം build_compound_വ്യഞ്ജകം (location_t, വൃക്ഷം, വൃക്ഷം);
ബാഹ്യ വൃക്ഷം c_cast_വ്യഞ്ജകം (location_t, ഘടന c_type_name *, വൃക്ഷം);
ബാഹ്യ വൃക്ഷം build_c_cast (location_t, വൃക്ഷം, വൃക്ഷം);
ബാഹ്യ ശൂന്യം store_init_മൂല്യം (location_t, വൃക്ഷം, വൃക്ഷം, വൃക്ഷം);
ബാഹ്യ ശൂന്യം maybe_warn_string_init (location_t, വൃക്ഷം, ഘടന c_വ്യഞ്ജകം);
ബാഹ്യ ശൂന്യം start_init (വൃക്ഷം, വൃക്ഷം, bool, bool, rich_location *);
ബാഹ്യ ശൂന്യം finish_init (ശൂന്യം);
ബാഹ്യ ശൂന്യം really_start_incremental_init (വൃക്ഷം);
ബാഹ്യ ശൂന്യം finish_implicit_inits (location_t, ഘടന obstack *);
ബാഹ്യ ശൂന്യം തള്ളുക_init_level (location_t, പൂർണ്ണസംഖ്യ, ഘടന obstack *);
ബാഹ്യ ഘടന c_വ്യഞ്ജകം എടുക്കുക_init_level (location_t, പൂർണ്ണസംഖ്യ, ഘടന obstack *,
				     location_t);
ബാഹ്യ ശൂന്യം set_init_index (location_t, വൃക്ഷം, വൃക്ഷം, ഘടന obstack *);
ബാഹ്യ ശൂന്യം set_init_label (location_t, വൃക്ഷം, location_t, ഘടന obstack *);
unsigned c_maybe_optimize_large_byte_initializer (ശൂന്യം);
ബാഹ്യ ശൂന്യം process_init_element (location_t, ഘടന c_വ്യഞ്ജകം, bool,
				  ഘടന obstack *);
ബാഹ്യ വൃക്ഷം build_compound_literal (location_t, വൃക്ഷം, വൃക്ഷം, bool,
				    unsigned പൂർണ്ണസംഖ്യ, ഘടന c_declspecs *);
ബാഹ്യ ശൂന്യം check_compound_literal_type (location_t, ഘടന c_type_name *);
ബാഹ്യ വൃക്ഷം c_start_switch (location_t, location_t, വൃക്ഷം, bool, വൃക്ഷം);
ബാഹ്യ ശൂന്യം c_finish_switch (വൃക്ഷം, വൃക്ഷം);
ബാഹ്യ വൃക്ഷം build_asm_വ്യഞ്ജകം (location_t, വൃക്ഷം, വൃക്ഷം, വൃക്ഷം, വൃക്ഷം, വൃക്ഷം, bool,
			    bool);
ബാഹ്യ വൃക്ഷം build_asm_stmt (bool, വൃക്ഷം);
ബാഹ്യ പൂർണ്ണസംഖ്യ c_types_compatible_p (വൃക്ഷം, വൃക്ഷം);
ബാഹ്യ വൃക്ഷം c_begin_compound_stmt (bool);
ബാഹ്യ വൃക്ഷം c_end_compound_stmt (location_t, വൃക്ഷം, bool);
ബാഹ്യ ശൂന്യം c_finish_if_stmt (location_t, വൃക്ഷം, വൃക്ഷം, വൃക്ഷം);
ബാഹ്യ ശൂന്യം c_finish_loop (location_t, location_t, വൃക്ഷം, location_t, വൃക്ഷം,
			   വൃക്ഷം, വൃക്ഷം, വൃക്ഷം, bool);
ബാഹ്യ വൃക്ഷം c_begin_stmt_വ്യഞ്ജകം (ശൂന്യം);
ബാഹ്യ വൃക്ഷം c_finish_stmt_വ്യഞ്ജകം (location_t, വൃക്ഷം);
ബാഹ്യ വൃക്ഷം c_process_വ്യഞ്ജകം_stmt (location_t, വൃക്ഷം);
ബാഹ്യ വൃക്ഷം c_finish_വ്യഞ്ജകം_stmt (location_t, വൃക്ഷം);
ബാഹ്യ വൃക്ഷം c_finish_return (location_t, വൃക്ഷം, വൃക്ഷം, bool = false);
ബാഹ്യ വൃക്ഷം c_finish_bc_stmt (location_t, വൃക്ഷം, bool, വൃക്ഷം);
ബാഹ്യ വൃക്ഷം c_finish_goto_label (location_t, വൃക്ഷം);
ബാഹ്യ വൃക്ഷം c_finish_goto_ptr (location_t, c_വ്യഞ്ജകം val);
ബാഹ്യ വൃക്ഷം c_വ്യഞ്ജകം_to_decl (വൃക്ഷം, bool *, bool *);
ബാഹ്യ വൃക്ഷം c_finish_omp_construct (location_t, എണ്ണൽ വൃക്ഷം_code, വൃക്ഷം, വൃക്ഷം);
ബാഹ്യ വൃക്ഷം c_finish_oacc_data (location_t, വൃക്ഷം, വൃക്ഷം);
ബാഹ്യ വൃക്ഷം c_finish_oacc_host_data (location_t, വൃക്ഷം, വൃക്ഷം);
ബാഹ്യ വൃക്ഷം c_begin_omp_parallel (ശൂന്യം);
ബാഹ്യ വൃക്ഷം c_finish_omp_parallel (location_t, വൃക്ഷം, വൃക്ഷം);
ബാഹ്യ വൃക്ഷം c_begin_omp_task (ശൂന്യം);
ബാഹ്യ വൃക്ഷം c_finish_omp_task (location_t, വൃക്ഷം, വൃക്ഷം);
ബാഹ്യ ശൂന്യം c_finish_omp_cancel (location_t, വൃക്ഷം);
ബാഹ്യ ശൂന്യം c_finish_omp_cancellation_point (location_t, വൃക്ഷം);
ബാഹ്യ വൃക്ഷം c_finish_omp_clauses (വൃക്ഷം, എണ്ണൽ c_omp_region_type);
ബാഹ്യ വൃക്ഷം c_omp_finish_mapper_clauses (വൃക്ഷം);
ബാഹ്യ വൃക്ഷം c_omp_mapper_lookup (വൃക്ഷം, വൃക്ഷം);
ബാഹ്യ വൃക്ഷം c_omp_extract_mapper_directive (വൃക്ഷം);
ബാഹ്യ വൃക്ഷം c_omp_map_array_section (location_t, വൃക്ഷം);
ബാഹ്യ വൃക്ഷം c_build_va_arg (location_t, വൃക്ഷം, location_t, വൃക്ഷം, വൃക്ഷം);
ബാഹ്യ വൃക്ഷം c_finish_transaction (location_t, വൃക്ഷം, പൂർണ്ണസംഖ്യ);
ബാഹ്യ bool c_വൃക്ഷം_equal (വൃക്ഷം, വൃക്ഷം);
ബാഹ്യ വൃക്ഷം c_build_function_call_vec (location_t, സ്ഥിരം vec<location_t>&,
				       വൃക്ഷം, vec<വൃക്ഷം, va_gc> *,
				       vec<വൃക്ഷം, va_gc> *);
ബാഹ്യ വൃക്ഷം c_omp_clause_copy_ctor (വൃക്ഷം, വൃക്ഷം, വൃക്ഷം);
ബാഹ്യ വൃക്ഷം c_reconstruct_complex_type (വൃക്ഷം, വൃക്ഷം);
ബാഹ്യ വൃക്ഷം c_type_canonical (വൃക്ഷം);
ബാഹ്യ വൃക്ഷം c_build_type_attribute_variant (വൃക്ഷം ntype, വൃക്ഷം attrs);
ബാഹ്യ വൃക്ഷം c_build_pointer_type (വൃക്ഷം type);
ബാഹ്യ വൃക്ഷം c_build_array_type (വൃക്ഷം type, വൃക്ഷം domain);
ബാഹ്യ വൃക്ഷം c_build_array_type_unspecified (വൃക്ഷം type);
ബാഹ്യ വൃക്ഷം c_build_array_type_zero_size (വൃക്ഷം type);
ബാഹ്യ വൃക്ഷം c_build_function_type (വൃക്ഷം type, വൃക്ഷം args, bool no = false);
ബാഹ്യ വൃക്ഷം c_build_pointer_type_for_mode (വൃക്ഷം type, machine_mode mode, bool m);

/* Set to 0 at beginning of a function definition, set to 1 if
   a return statement that specifies a return value is seen.  */

ബാഹ്യ പൂർണ്ണസംഖ്യ current_function_returns_മൂല്യം;

/* Set to 0 at beginning of a function definition, set to 1 if
   a return statement with no argument is seen.  */

ബാഹ്യ പൂർണ്ണസംഖ്യ current_function_returns_null;

/* Set to 0 at beginning of a function definition, set to 1 if
   a call to a noreturn function is seen.  */

ബാഹ്യ പൂർണ്ണസംഖ്യ current_function_returns_abnormally;

/* In c-decl.cc */

/* Tell the binding oracle what kind of binding we are looking for.  */

എണ്ണൽ c_oracle_request
{
  C_ORACLE_ചിഹ്നം,
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

തരനിർവചനം ശൂന്യം c_binding_oracle_function (എണ്ണൽ c_oracle_request, വൃക്ഷം identifier);

ബാഹ്യ c_binding_oracle_function *c_binding_oracle;

ബാഹ്യ ശൂന്യം c_finish_incomplete_decl (വൃക്ഷം);
ബാഹ്യ വൃക്ഷം c_omp_reduction_id (എണ്ണൽ വൃക്ഷം_code, വൃക്ഷം);
ബാഹ്യ വൃക്ഷം c_omp_reduction_decl (വൃക്ഷം);
ബാഹ്യ വൃക്ഷം c_omp_reduction_lookup (വൃക്ഷം, വൃക്ഷം);
ബാഹ്യ വൃക്ഷം c_check_omp_declare_reduction_r (വൃക്ഷം *, പൂർണ്ണസംഖ്യ *, ശൂന്യം *);
ബാഹ്യ വൃക്ഷം c_omp_mapper_id (വൃക്ഷം);
ബാഹ്യ വൃക്ഷം c_omp_mapper_decl (വൃക്ഷം);
ബാഹ്യ ശൂന്യം c_omp_scan_mapper_bindings (location_t, വൃക്ഷം *, വൃക്ഷം);
ബാഹ്യ bool c_check_in_current_scope (വൃക്ഷം);
ബാഹ്യ ശൂന്യം c_pushtag (location_t, വൃക്ഷം, വൃക്ഷം);
ബാഹ്യ ശൂന്യം c_bind (location_t, വൃക്ഷം, bool);
ബാഹ്യ bool tag_exists_p (എണ്ണൽ വൃക്ഷം_code, വൃക്ഷം);

ബാഹ്യ ശൂന്യം verify_counted_by_for_മുകൾ_anonymous_type (വൃക്ഷം);

/* In c-errors.cc */
ബാഹ്യ bool pedwarn_c90 (location_t, diagnostics::option_id, സ്ഥിരം അക്ഷരം *, ...)
    ATTRIBUTE_GCC_DIAG(3,4);
ബാഹ്യ bool pedwarn_c99 (location_t, diagnostics::option_id, സ്ഥിരം അക്ഷരം *, ...)
    ATTRIBUTE_GCC_DIAG(3,4);
ബാഹ്യ bool pedwarn_c11 (location_t, diagnostics::option_id, സ്ഥിരം അക്ഷരം *, ...)
    ATTRIBUTE_GCC_DIAG(3,4);
ബാഹ്യ bool pedwarn_c23 (location_t, diagnostics::option_id, സ്ഥിരം അക്ഷരം *, ...)
    ATTRIBUTE_GCC_DIAG(3,4);
ബാഹ്യ ശൂന്യം add_note_about_new_keyword (location_t loc,
					വൃക്ഷം keyword_id);

ബാഹ്യ ശൂന്യം
set_c_വ്യഞ്ജകം_source_range (c_വ്യഞ്ജകം *വ്യഞ്ജകം,
			 location_t start, location_t finish);

ബാഹ്യ ശൂന്യം
set_c_വ്യഞ്ജകം_source_range (c_വ്യഞ്ജകം *വ്യഞ്ജകം,
			 source_range src_range);

/* In c-fold.cc */
ബാഹ്യ vec<വൃക്ഷം> incomplete_record_decls;

ബാഹ്യ സ്ഥിരം അക്ഷരം *c_get_sarif_source_language (സ്ഥിരം അക്ഷരം *filename);

ബാഹ്യ സ്ഥിരം ഘടന scoped_attribute_specs std_attribute_table;

#എങ്കിൽ CHECKING_P
namespace selftest {
  ബാഹ്യ ശൂന്യം run_c_tests (ശൂന്യം);
} // namespace selftest
#endif /* #if CHECKING_P */


#endif /* ! GCC_C_TREE_H */
