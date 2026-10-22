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

#ifndef GCC_C_વૃક્ષ_H
#define GCC_C_વૃક્ષ_H

#અન્તર્ભાવ "c-family/c-common.h"
#અન્તર્ભાવ "diagnostic.h"

/* struct lang_identifier is private to c-decl.cc, but langhooks.cc needs to
   know how big it is.  This is sanity-checked in c-decl.cc.  */
#define C_SIZEOF_STRUCT_LANG_IDENTIFIER \
  (કદ (સંરચના c_common_identifier) + 3 * કદ (શૂન્ય *))

/* In a RECORD_TYPE or UNION_TYPE, nonzero if any component is read-only.  */
#define C_TYPE_FIELDS_READONLY(TYPE) વૃક્ષ_LANG_FLAG_1 (TYPE)

/* In a RECORD_TYPE or UNION_TYPE, nonzero if any component is volatile.  */
#define C_TYPE_FIELDS_VOLATILE(TYPE) વૃક્ષ_LANG_FLAG_2 (TYPE)

/* In a RECORD_TYPE or UNION_TYPE, nonzero if any component is
   volatile, restrict-qualified or atomic; that is, has a type not
   permitted for a constexpr object.  */
#define C_TYPE_FIELDS_NON_CONSTEXPR(TYPE) વૃક્ષ_LANG_FLAG_4 (TYPE)

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
  TYPE_LANG_SLOT_1 (વૃક્ષ_CHECK4 (TYPE, RECORD_TYPE, UNION_TYPE, \
				 QUAL_UNION_TYPE, ENUMERAL_TYPE))

/* In an IDENTIFIER_NODE, nonzero if this identifier is actually a
   keyword.  C_RID_CODE (node) is then the RID_* value of the keyword.  */
#define C_IS_RESERVED_WORD(ID) વૃક્ષ_LANG_FLAG_0 (ID)

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
#define C_ARRAY_PARAMETER(ગાંઠ_2) DECL_LANG_FLAG_0 (ગાંઠ_2)

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
  DECL_LANG_FLAG_4 (વૃક્ષ_NOT_CHECK (EXP, FUNCTION_DECL))

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
	|| (!prototype_p (વૃક્ષ_TYPE (EXP))	\
	    && !fndecl_built_in_p (EXP)))

/* For FUNCTION_TYPE, a hidden list of types of arguments.  The same as
   TYPE_ARG_TYPES for functions with prototypes, but created for functions
   without prototypes.  */
#define TYPE_ACTUAL_ARG_TYPES(ગાંઠ_2) \
  TYPE_LANG_SLOT_1 (FUNCTION_TYPE_CHECK (ગાંઠ_2))

/* For a CONSTRUCTOR, whether some initializer contains a
   subexpression meaning it is not a constant expression.  */
#define CONSTRUCTOR_NON_CONST(પદાવલિ_2) વૃક્ષ_LANG_FLAG_1 (CONSTRUCTOR_CHECK (પદાવલિ_2))

/* For a SAVE_EXPR, nonzero if the operand of the SAVE_EXPR has already
   been folded.  */
#define SAVE_પદાવલિ_FOLDED_P(EXP)	વૃક્ષ_LANG_FLAG_1 (SAVE_પદાવલિ_CHECK (EXP))

/* Whether a type has boolean semantics: either a boolean type or an
   enumeration type with a boolean type as its underlying type.  */
#define C_BOOLEAN_TYPE_P(TYPE)						\
  (વૃક્ષ_CODE (TYPE) == BOOLEAN_TYPE					\
   || (વૃક્ષ_CODE (TYPE) == ENUMERAL_TYPE				\
       && ENUM_UNDERLYING_TYPE (TYPE) != NULL_વૃક્ષ			\
       && (વૃક્ષ_CODE (ENUM_UNDERLYING_TYPE (TYPE)) == BOOLEAN_TYPE	\
	   || c_hardbool_type_attr (TYPE))))

/* Record parser information about an expression that is irrelevant
   for code generation alongside a tree representing its value.  */
સંરચના c_પદાવલિ
{
  /* The value of the expression.  */
  વૃક્ષ કિંમત;
  /* Record the original unary/binary operator of an expression, which may
     have been changed by fold, STRING_CST for unparenthesized string
     constants, C_MAYBE_CONST_EXPR for __builtin_constant_p calls
     (even if parenthesized), for subexpressions, and for non-constant
     initializers, or ERROR_MARK for other expressions (including
     parenthesized expressions).  */
  ગણના વૃક્ષ_code original_code;
  /* If not NULL, the original type of an expression.  This will
     differ from the type of the value field for an enum constant.
     The type of an enum constant is a plain integer type, but this
     field will be the enum type.  */
  વૃક્ષ original_type;

  /* The source range of this expression.  This is redundant
     for node values that have locations, but not all node kinds
     have locations (e.g. constants, and references to params, locals,
     etc), so we stash a copy here.  */
  source_range src_range;

  /* True if this was directly from a decimal constant token.  */
  bool m_decimal : 1;

  /* Access to the first and last locations within the source spelling
     of this expression.  */
  location_t get_start () અચલ { પાછા src_range.m_start; }
  location_t get_finish () અચલ { પાછા src_range.m_finish; }

  location_t get_location () અચલ
  {
    જો (પદાવલિ_HAS_LOCATION (કિંમત))
      પાછા પદાવલિ_LOCATION (કિંમત);
    નહીંતર
      પાછા make_location (get_start (), get_start (), get_finish ());
  }

  /* Set the value to error_mark_node whilst ensuring that src_range
     and m_decimal are initialized.  */
  શૂન્ય set_error ()
  {
    કિંમત = error_mark_ગાંઠ;
    src_range.m_start = UNKNOWN_LOCATION;
    src_range.m_finish = UNKNOWN_LOCATION;
    m_decimal = 0;
  }
};

/* Type alias for struct c_expr. This allows to use the structure
   inside the VEC types.  */
પ્રકારવ્યાખ્યા સંરચના c_પદાવલિ c_પદાવલિ_t;

/* A kind of type specifier.  Note that this information is currently
   only used to distinguish tag definitions, tag references and typeof
   uses.  */
ગણના c_typespec_kind {
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
સંરચના c_typespec {
  /* What kind of type specifier this is.  */
  ગણના c_typespec_kind kind;
  /* Whether the expression has operands suitable for use in constant
     expressions.  */
  bool પદાવલિ_const_operands;
  /* Whether the type specifier includes an enum type specifier (that
     is, ": specifier-qualifier-list" in a declaration using
     "enum").  */
  bool has_enum_type_specifier;
  /* The specifier itself.  */
  વૃક્ષ spec;
  /* An expression to be evaluated before the type specifier, in the
     case of typeof specifiers, or NULL otherwise or if no such
     expression is required for a particular typeof specifier.  In
     particular, when typeof is applied to an expression of variably
     modified type, that expression must be evaluated in order to
     determine array sizes that form part of the type, but the
     expression itself (as opposed to the array sizes) forms no part
     of the type and so needs to be recorded separately.  */
  વૃક્ષ પદાવલિ;
};

/* A storage class specifier.  */
ગણના c_storage_class {
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
ગણના c_typespec_keyword {
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
ગણના c_declspec_word {
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
  cdw_સંખ્યા_of_elements /* This one must always be the last
			    enumerator.  */
};

ગણના c_declspec_il {
  cdil_none,
  cdil_gimple,		/* __GIMPLE  */
  cdil_gimple_cfg,	/* __GIMPLE(cfg)  */
  cdil_gimple_ssa,	/* __GIMPLE(ssa)  */
  cdil_rtl		/* __RTL  */
};

/* A sequence of declaration specifiers in C.  When a new declaration
   specifier is added, please update the enum c_declspec_word above
   accordingly.  */
સંરચના c_declspecs {
  location_t locations[cdw_સંખ્યા_of_elements];
  /* The type specified, if a single type specifier such as a struct,
     union or enum specifier, typedef name or typeof specifies the
     whole type, or NULL_TREE if none or a keyword such as "void" or
     "char" is used.  Does not include qualifiers.  */
  વૃક્ષ type;
  /* Any expression to be evaluated before the type, from a typeof
     specifier.  */
  વૃક્ષ પદાવલિ;
  /* The attributes from a typedef decl.  */
  વૃક્ષ decl_attr;
  /* When parsing, the GNU attributes and prefix standard attributes.
     Outside the parser, this will be NULL; attributes (possibly from
     multiple lists) will be passed separately.  */
  વૃક્ષ attrs;
  /* When parsing, postfix standard attributes (which appertain to the
     type specified by the preceding declaration specifiers, unlike
     prefix standard attributes which appertain to the declaration or
     declarations as a whole).  */
  વૃક્ષ postfix_attrs;
  /* The pass to start compiling a __GIMPLE or __RTL function with.  */
  અક્ષર *gimple_or_rtl_pass;
  /* ENTRY BB count.  */
  profile_ગણતરી entry_bb_ગણતરી;
  /* The base-2 log of the greatest alignment required by an _Alignas
     specifier, in bytes, or -1 if no such specifiers with nonzero
     alignment.  */
  પૂર્ણાંક align_log;
  સંઘ {
    /* For the __intN declspec, this stores the index into the int_n_*
       arrays.  */
    પૂર્ણાંક int_n_idx;
    /* For the _FloatN and _FloatNx declspec, this stores the index into
       the floatn_nx_types array.  */
    પૂર્ણાંક floatn_nx_idx;
    /* For _BitInt(N) this stores the N.  */
    પૂર્ણાંક bitint_prec;
  } u;
  /* The storage class specifier, or csc_none if none.  */
  ગણના c_storage_class storage_class;
  /* Any type specifier keyword used such as "int", not reflecting
     modifiers such as "short", or cts_none if none.  */
  ગણના c_typespec_keyword typespec_word : 8;
  /* The kind of type specifier if one has been seen, ctsk_none
     otherwise.  */
  ગણના c_typespec_kind typespec_kind : 4;
  ગણના c_declspec_il declspec_il : 3;
  /* Whether any expressions in typeof specifiers may appear in
     constant expressions.  */
  bool પદાવલિ_const_operands : 1;
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
ગણના c_declarator_kind {
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

સંરચના c_arg_tag {
  /* The argument name.  */
  વૃક્ષ id;
  /* The type of the argument.  */
  વૃક્ષ type;
};


/* Information about the parameters in a function declarator.  */
સંરચના c_arg_info {
  /* A list of parameter decls.  */
  વૃક્ષ parms;
  /* A list of structure, union and enum tags defined.  */
  vec<c_arg_tag, va_gc> *tags;
  /* A list of argument types to go in the FUNCTION_TYPE.  */
  વૃક્ષ types;
  /* A list of non-parameter decls (notably enumeration constants)
     defined with the parameters.  */
  વૃક્ષ others;
  /* A compound expression of VLA sizes from the parameters, or NULL.
     In a function definition, these are used to ensure that
     side-effects in sizes of arrays converted to pointers (such as a
     parameter int i[n++]) take place; otherwise, they are
     ignored.  */
  વૃક્ષ pending_sizes;
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
સંરચના c_declarator {
  /* The kind of declarator.  */
  ગણના c_declarator_kind kind;
  location_t id_loc; /* Currently only set for cdk_id, cdk_array. */
  /* Except for cdk_id, the contained declarator.  For cdk_id, NULL.  */
  સંરચના c_declarator *declarator;
  સંઘ {
    /* For identifiers.  */
    સંરચના {
      /* An IDENTIFIER_NODE, or NULL_TREE if an abstract
	 declarator.  */
      વૃક્ષ id;
      /* Any attributes (which apply to the declaration rather than to
	 the type described by the outer declarators).  */
      વૃક્ષ attrs;
    } id;
    /* For functions.  */
    સંરચના c_arg_info *arg_info;
    /* For arrays.  */
    સંરચના {
      /* The array dimension, or NULL for [] and [*].  */
      વૃક્ષ dimen;
      /* The qualifiers inside [].  */
      પૂર્ણાંક quals;
      /* The attributes (currently ignored) inside [].  */
      વૃક્ષ attrs;
      /* Whether [static] was used.  */
      bool static_p : 1;
      /* Whether [*] was used.  */
      bool vla_unspec_p : 1;
    } array;
    /* For pointers, the qualifiers on the pointer type.  */
    પૂર્ણાંક pointer_quals;
    /* For attributes.  */
    વૃક્ષ attrs;
  } u;
};

/* A type name.  */
સંરચના c_type_name {
  /* The declaration specifiers.  */
  સંરચના c_declspecs *specs;
  /* The declarator.  */
  સંરચના c_declarator *declarator;
};

/* A parameter.  */
સંરચના c_parm {
  /* The declaration specifiers, minus any prefix attributes.  */
  સંરચના c_declspecs *specs;
  /* The attributes.  */
  વૃક્ષ attrs;
  /* The declarator.  */
  સંરચના c_declarator *declarator;
  /* The location of the parameter.  */
  location_t loc;
};

/* Used when parsing an enum.  Initialized by start_enum.  */
સંરચના c_enum_contents
{
  /* While defining an enum type, this is 1 plus the last enumerator
     constant value.  */
  વૃક્ષ enum_next_કિંમત;

  /* The enumeration type itself.  */
  વૃક્ષ enum_type;

  /* Nonzero means that there was overflow computing enum_next_value.  */
  પૂર્ણાંક enum_overflow;
};

/* A type of reference to a static identifier in an inline
   function.  */
ગણના c_inline_static_type {
  /* Identifier with internal linkage used in function that may be an
     inline definition (i.e., file-scope static).  */
  csi_internal,
  /* Modifiable object with static storage duration defined in
     function that may be an inline definition (i.e., local
     static).  */
  csi_modifiable
};

/* Record details of decls possibly used inside sizeof or typeof.  */
સંરચના maybe_used_decl
{
  /* The decl.  */
  વૃક્ષ decl;
  /* The level seen at (in_sizeof + in_typeof + in_countof + in_generic).  */
  પૂર્ણાંક level;
  /* Seen in address-of.  */
  bool address;
  /* The next one at this level or above, or NULL.  */
  સંરચના maybe_used_decl *next;
};


/* in c-parser.cc */
સંરચના c_વૃક્ષ_token_vec;
બાહ્ય શૂન્ય c_parse_init (શૂન્ય);
બાહ્ય bool c_keyword_starts_typename (ગણના rid keyword);

/* in c-aux-info.cc */
બાહ્ય શૂન્ય gen_aux_info_record (વૃક્ષ, પૂર્ણાંક, પૂર્ણાંક, પૂર્ણાંક);

/* in c-decl.cc */
સંરચના c_spot_bindings;
class c_struct_parse_info;
બાહ્ય સંરચના obstack parser_obstack;
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
બાહ્ય unsigned અક્ષર in_statement;

બાહ્ય bool switch_statement_break_seen_p;

બાહ્ય bool global_bindings_p (શૂન્ય);
બાહ્ય વૃક્ષ pushdecl (વૃક્ષ);
બાહ્ય unsigned પૂર્ણાંક start_underspecified_init (location_t, વૃક્ષ);
બાહ્ય શૂન્ય finish_underspecified_init (વૃક્ષ, unsigned પૂર્ણાંક);
બાહ્ય શૂન્ય ધકેલો_scope (શૂન્ય);
બાહ્ય વૃક્ષ કાઢો_scope (શૂન્ય);
બાહ્ય શૂન્ય c_mark_decl_jump_unsafe_in_current_scope ();
બાહ્ય શૂન્ય c_bindings_start_stmt_પદાવલિ (સંરચના c_spot_bindings *);
બાહ્ય શૂન્ય c_bindings_end_stmt_પદાવલિ (સંરચના c_spot_bindings *);

બાહ્ય શૂન્ય record_inline_static (location_t, વૃક્ષ, વૃક્ષ,
				  ગણના c_inline_static_type);
બાહ્ય શૂન્ય c_init_decl_processing (શૂન્ય);
બાહ્ય શૂન્ય c_print_identifier (FILE *, વૃક્ષ, પૂર્ણાંક);
બાહ્ય પૂર્ણાંક quals_from_declspecs (અચલ સંરચના c_declspecs *);
બાહ્ય સંરચના c_declarator *build_array_declarator (location_t, વૃક્ષ,
    						    સંરચના c_declspecs *,
						    bool, bool);
બાહ્ય વૃક્ષ build_enumerator (location_t, location_t, સંરચના c_enum_contents *,
			      વૃક્ષ, વૃક્ષ);
બાહ્ય વૃક્ષ check_for_loop_decls (location_t, bool);
બાહ્ય શૂન્ય mark_forward_parm_decls (શૂન્ય);
બાહ્ય શૂન્ય declare_parm_level (શૂન્ય);
બાહ્ય શૂન્ય undeclared_variable (location_t, વૃક્ષ);
બાહ્ય વૃક્ષ lookup_label_for_goto (location_t, વૃક્ષ);
બાહ્ય વૃક્ષ declare_label (વૃક્ષ);
બાહ્ય વૃક્ષ define_label (location_t, વૃક્ષ);
બાહ્ય સંરચના c_spot_bindings *c_get_switch_bindings (શૂન્ય);
બાહ્ય શૂન્ય c_release_switch_bindings (સંરચના c_spot_bindings *);
બાહ્ય bool c_check_switch_jump_warnings (સંરચના c_spot_bindings *,
					  location_t, location_t);
બાહ્ય શૂન્ય finish_decl (વૃક્ષ, location_t, વૃક્ષ, વૃક્ષ, વૃક્ષ);
બાહ્ય વૃક્ષ finish_enum (વૃક્ષ, વૃક્ષ, વૃક્ષ);
બાહ્ય શૂન્ય finish_function (location_t = આગત_location);
બાહ્ય વૃક્ષ finish_struct (location_t, વૃક્ષ, વૃક્ષ, વૃક્ષ,
			   class c_struct_parse_info *,
			   વૃક્ષ *પદાવલિ = ખાલી);
બાહ્ય વૃક્ષ c_simulate_enum_decl (location_t, અચલ અક્ષર *,
				  vec<string_int_pair> *);
બાહ્ય વૃક્ષ c_simulate_record_decl (location_t, અચલ અક્ષર *,
				    array_slice<અચલ વૃક્ષ>);
બાહ્ય સંરચના c_arg_info *build_arg_info (શૂન્ય);
બાહ્ય સંરચના c_arg_info *get_parm_info (bool, વૃક્ષ);
બાહ્ય વૃક્ષ grokfield (location_t, સંરચના c_declarator *,
		       સંરચના c_declspecs *, વૃક્ષ, વૃક્ષ *, વૃક્ષ *);
બાહ્ય વૃક્ષ groktypename (સંરચના c_type_name *, વૃક્ષ *, bool *);
બાહ્ય વૃક્ષ grokgenassoc (સંરચના c_type_name *);
બાહ્ય વૃક્ષ grokparm (અચલ સંરચના c_parm *, વૃક્ષ *);
બાહ્ય વૃક્ષ implicitly_declare (location_t, વૃક્ષ);
બાહ્ય શૂન્ય keep_next_level (શૂન્ય);
બાહ્ય શૂન્ય pending_xref_error (શૂન્ય);
બાહ્ય શૂન્ય c_ધકેલો_function_context (શૂન્ય);
બાહ્ય શૂન્ય c_કાઢો_function_context (શૂન્ય);
બાહ્ય શૂન્ય ધકેલો_parm_decl (અચલ સંરચના c_parm *, વૃક્ષ *);
બાહ્ય સંરચના c_declarator *set_array_declarator_inner (સંરચના c_declarator *,
							સંરચના c_declarator *);
બાહ્ય વૃક્ષ c_builtin_function (વૃક્ષ);
બાહ્ય વૃક્ષ c_builtin_function_ext_scope (વૃક્ષ);
બાહ્ય વૃક્ષ c_simulate_builtin_function_decl (વૃક્ષ);
બાહ્ય શૂન્ય c_warn_unused_attributes (વૃક્ષ);
બાહ્ય વૃક્ષ c_warn_type_attributes (વૃક્ષ, વૃક્ષ);
બાહ્ય શૂન્ય shadow_tag (અચલ સંરચના c_declspecs *);
બાહ્ય શૂન્ય shadow_tag_warned (અચલ સંરચના c_declspecs *, પૂર્ણાંક);
બાહ્ય વૃક્ષ start_enum (location_t, સંરચના c_enum_contents *, વૃક્ષ, વૃક્ષ,
			bool potential_nesting_p);
બાહ્ય bool start_function (સંરચના c_declspecs *, સંરચના c_declarator *, વૃક્ષ);
બાહ્ય વૃક્ષ start_decl (સંરચના c_declarator *, સંરચના c_declspecs *, bool,
			વૃક્ષ, bool = true, location_t * = ખાલી);
બાહ્ય વૃક્ષ start_struct (location_t, ગણના વૃક્ષ_code, વૃક્ષ,
			  class c_struct_parse_info **);
બાહ્ય શૂન્ય store_parm_decls (શૂન્ય);
બાહ્ય શૂન્ય store_parm_decls_from (સંરચના c_arg_info *);
બાહ્ય શૂન્ય temp_store_parm_decls (વૃક્ષ, વૃક્ષ);
બાહ્ય શૂન્ય temp_કાઢો_parm_decls (શૂન્ય);
બાહ્ય વૃક્ષ xref_tag (ગણના વૃક્ષ_code, વૃક્ષ);
બાહ્ય સંરચના c_typespec parser_xref_tag (location_t, ગણના વૃક્ષ_code, વૃક્ષ,
					  bool, વૃક્ષ, bool);
બાહ્ય સંરચના c_parm *build_c_parm (સંરચના c_declspecs *, વૃક્ષ,
				    સંરચના c_declarator *, location_t);
બાહ્ય સંરચના c_declarator *build_attrs_declarator (વૃક્ષ,
						    સંરચના c_declarator *);
બાહ્ય સંરચના c_declarator *build_function_declarator (સંરચના c_arg_info *,
						       સંરચના c_declarator *);
બાહ્ય સંરચના c_declarator *build_id_declarator (વૃક્ષ);
બાહ્ય સંરચના c_declarator *make_pointer_declarator (સંરચના c_declspecs *,
						     સંરચના c_declarator *);
બાહ્ય સંરચના c_declspecs *build_null_declspecs (શૂન્ય);
બાહ્ય સંરચના c_declspecs *declspecs_add_qual (location_t,
					       સંરચના c_declspecs *, વૃક્ષ);
બાહ્ય સંરચના c_declspecs *declspecs_add_type (location_t,
					       સંરચના c_declspecs *,
					       સંરચના c_typespec);
બાહ્ય સંરચના c_declspecs *declspecs_add_scspec (location_t,
						 સંરચના c_declspecs *, વૃક્ષ);
બાહ્ય સંરચના c_declspecs *declspecs_add_attrs (location_t,
						સંરચના c_declspecs *, વૃક્ષ);
બાહ્ય સંરચના c_declspecs *declspecs_add_addrspace (location_t,
						    સંરચના c_declspecs *,
						    addr_space_t);
બાહ્ય સંરચના c_declspecs *declspecs_add_alignas (location_t,
						  સંરચના c_declspecs *, વૃક્ષ);
બાહ્ય સંરચના c_declspecs *finish_declspecs (સંરચના c_declspecs *);
બાહ્ય size_t c_વૃક્ષ_size (ગણના વૃક્ષ_code);
બાહ્ય પૂર્ણાંક c_get_loop_names (વૃક્ષ, bool, વૃક્ષ *);
બાહ્ય શૂન્ય c_release_loop_names (પૂર્ણાંક);
બાહ્ય વૃક્ષ c_finish_bc_name (location_t, વૃક્ષ, bool);

/* in c-objc-common.cc */
બાહ્ય bool c_objc_common_init (શૂન્ય);
બાહ્ય bool c_missing_noreturn_ok_p (વૃક્ષ);
બાહ્ય bool c_warn_unused_global_decl (const_વૃક્ષ);
બાહ્ય શૂન્ય c_initialize_diagnostics (diagnostics::context *);
બાહ્ય bool c_var_mod_p (વૃક્ષ x, વૃક્ષ fn);
બાહ્ય alias_set_type c_get_alias_set (વૃક્ષ);
બાહ્ય પૂર્ણાંક c_type_dwarf_attribute (const_વૃક્ષ, પૂર્ણાંક);
બાહ્ય વૃક્ષ c_enum_underlying_base_type (const_વૃક્ષ);

/* in c-typeck.cc */
બાહ્ય પૂર્ણાંક in_alignof;
બાહ્ય પૂર્ણાંક in_sizeof;
બાહ્ય પૂર્ણાંક in_countof;
બાહ્ય પૂર્ણાંક in_typeof;
બાહ્ય પૂર્ણાંક in_generic;
બાહ્ય bool c_in_omp_for;
બાહ્ય bool c_omp_array_section_p;

બાહ્ય વૃક્ષ c_last_sizeof_arg;
બાહ્ય location_t c_last_sizeof_loc;

બાહ્ય સંરચના c_switch *c_switch_ઢગલો;

બાહ્ય bool null_pointer_constant_p (const_વૃક્ષ);


અંતઃરેખ bool
c_type_variably_modified_p (વૃક્ષ t)
{
  જો (error_mark_ગાંઠ == t)
    પાછા false;
  જો (C_TYPE_VARIABLY_MODIFIED (t))
    પાછા true;
  જો (TYPE_STRUCTURAL_EQUALITY_P (t))
    {
      /* The flag may not have been set yet because of incomplete
	 structure or union types completed later.  */
      પસંદગી (વૃક્ષ_CODE (t))
	{
	સ્થિતિ ARRAY_TYPE:
	સ્થિતિ FUNCTION_TYPE:
	સ્થિતિ POINTER_TYPE:
	  /* Recurse.  */
	  જો (c_type_variably_modified_p (વૃક્ષ_TYPE (t)))
	    {
	      C_TYPE_VARIABLY_MODIFIED (t) = 1;
	      પાછા true;
	    }
	  તોડો;
	મૂળભૂત:
	  તોડો;
	}
    }
  પાછા false;
}

અંતઃરેખ bool
c_type_unspecified_p (વૃક્ષ t)
{
  પાછા error_mark_ગાંઠ != t
	 && C_TYPE_VARIABLE_SIZE (t) && વૃક્ષ_CODE (t) == ARRAY_TYPE
	 && TYPE_DOMAIN (t) && TYPE_MAX_કિંમત (TYPE_DOMAIN (t))
	 && વૃક્ષ_CODE (TYPE_MAX_કિંમત (TYPE_DOMAIN (t))) == COMPOUND_પદાવલિ
	 && integer_zerop (વૃક્ષ_OPERAND (TYPE_MAX_કિંમત (TYPE_DOMAIN (t)), 0))
	 && integer_zerop (વૃક્ષ_OPERAND (TYPE_MAX_કિંમત (TYPE_DOMAIN (t)), 1));
}

બાહ્ય bool zero_length_array_type_p (const_વૃક્ષ type);
બાહ્ય bool char_type_p (વૃક્ષ);
બાહ્ય વૃક્ષ c_type_tag (const_વૃક્ષ t);
બાહ્ય વૃક્ષ c_objc_common_truthvalue_conversion (location_t, વૃક્ષ,
						 વૃક્ષ = integer_type_ગાંઠ);
બાહ્ય વૃક્ષ require_complete_type (location_t, વૃક્ષ);
બાહ્ય bool same_translation_unit_p (const_વૃક્ષ, const_વૃક્ષ);
બાહ્ય bool comptypes (વૃક્ષ, વૃક્ષ);
બાહ્ય bool comptypes_same_p (વૃક્ષ, વૃક્ષ);
બાહ્ય bool comptypes_equiv_p (વૃક્ષ, વૃક્ષ);
બાહ્ય bool comptypes_check_enum_int (વૃક્ષ, વૃક્ષ, bool *);
બાહ્ય bool c_mark_addressable (વૃક્ષ, bool = false, bool = false);
બાહ્ય શૂન્ય c_incomplete_type_error (location_t, const_વૃક્ષ, const_વૃક્ષ);
બાહ્ય વૃક્ષ c_type_promotes_to (વૃક્ષ);
બાહ્ય સંરચના c_પદાવલિ default_function_array_conversion (location_t,
							સંરચના c_પદાવલિ);
બાહ્ય સંરચના c_પદાવલિ default_function_array_read_conversion (location_t,
							     સંરચના c_પદાવલિ);
બાહ્ય સંરચના c_પદાવલિ convert_lvalue_to_rvalue (location_t, સંરચના c_પદાવલિ,
					       bool, bool, bool = false);
બાહ્ય વૃક્ષ decl_constant_કિંમત_1 (વૃક્ષ, bool);
બાહ્ય શૂન્ય mark_exp_read (વૃક્ષ);
બાહ્ય વૃક્ષ composite_type (વૃક્ષ, વૃક્ષ);
બાહ્ય વૃક્ષ lookup_field (const_વૃક્ષ, વૃક્ષ);
બાહ્ય વૃક્ષ build_component_ref (location_t, વૃક્ષ, વૃક્ષ, location_t,
				 location_t);
બાહ્ય વૃક્ષ handle_counted_by_for_component_ref (location_t, વૃક્ષ);
બાહ્ય વૃક્ષ build_array_ref (location_t, વૃક્ષ, વૃક્ષ);
બાહ્ય વૃક્ષ build_omp_array_section (location_t, વૃક્ષ, વૃક્ષ, વૃક્ષ);
બાહ્ય વૃક્ષ build_external_ref (location_t, વૃક્ષ, bool, વૃક્ષ *);
બાહ્ય શૂન્ય કાઢો_maybe_used (bool);
બાહ્ય સંરચના maybe_used_decl *save_maybe_used ();
બાહ્ય શૂન્ય restore_maybe_used (સંરચના maybe_used_decl *);
બાહ્ય શૂન્ય mark_decl_used (વૃક્ષ, bool);
બાહ્ય સંરચના c_પદાવલિ c_પદાવલિ_sizeof_પદાવલિ (location_t, સંરચના c_પદાવલિ);
બાહ્ય સંરચના c_પદાવલિ c_પદાવલિ_sizeof_type (location_t, સંરચના c_type_name *);
બાહ્ય સંરચના c_પદાવલિ c_પદાવલિ_countof_પદાવલિ (location_t, સંરચના c_પદાવલિ);
બાહ્ય સંરચના c_પદાવલિ c_પદાવલિ_countof_type (location_t loc,
					  સંરચના c_type_name *);
બાહ્ય સંરચના c_પદાવલિ c_પદાવલિ_maxof_type (location_t loc, સંરચના c_type_name *);
બાહ્ય સંરચના c_પદાવલિ c_પદાવલિ_minof_type (location_t loc, સંરચના c_type_name *);
બાહ્ય સંરચના c_પદાવલિ parser_build_unary_op (location_t, ગણના વૃક્ષ_code,
    					    સંરચના c_પદાવલિ);
બાહ્ય સંરચના c_પદાવલિ parser_build_દ્વિઅંકી_op (location_t,
    					     ગણના વૃક્ષ_code, સંરચના c_પદાવલિ,
					     સંરચના c_પદાવલિ, વૃક્ષ);
બાહ્ય વૃક્ષ build_conditional_પદાવલિ (location_t, વૃક્ષ, bool, વૃક્ષ, વૃક્ષ,
				    location_t, વૃક્ષ, વૃક્ષ, location_t);
બાહ્ય વૃક્ષ build_compound_પદાવલિ (location_t, વૃક્ષ, વૃક્ષ);
બાહ્ય વૃક્ષ c_cast_પદાવલિ (location_t, સંરચના c_type_name *, વૃક્ષ);
બાહ્ય વૃક્ષ build_c_cast (location_t, વૃક્ષ, વૃક્ષ);
બાહ્ય શૂન્ય store_init_કિંમત (location_t, વૃક્ષ, વૃક્ષ, વૃક્ષ);
બાહ્ય શૂન્ય maybe_warn_string_init (location_t, વૃક્ષ, સંરચના c_પદાવલિ);
બાહ્ય શૂન્ય start_init (વૃક્ષ, વૃક્ષ, bool, bool, rich_location *);
બાહ્ય શૂન્ય finish_init (શૂન્ય);
બાહ્ય શૂન્ય really_start_incremental_init (વૃક્ષ);
બાહ્ય શૂન્ય finish_implicit_inits (location_t, સંરચના obstack *);
બાહ્ય શૂન્ય ધકેલો_init_level (location_t, પૂર્ણાંક, સંરચના obstack *);
બાહ્ય સંરચના c_પદાવલિ કાઢો_init_level (location_t, પૂર્ણાંક, સંરચના obstack *,
				     location_t);
બાહ્ય શૂન્ય set_init_index (location_t, વૃક્ષ, વૃક્ષ, સંરચના obstack *);
બાહ્ય શૂન્ય set_init_label (location_t, વૃક્ષ, location_t, સંરચના obstack *);
unsigned c_maybe_optimize_large_byte_initializer (શૂન્ય);
બાહ્ય શૂન્ય process_init_element (location_t, સંરચના c_પદાવલિ, bool,
				  સંરચના obstack *);
બાહ્ય વૃક્ષ build_compound_literal (location_t, વૃક્ષ, વૃક્ષ, bool,
				    unsigned પૂર્ણાંક, સંરચના c_declspecs *);
બાહ્ય શૂન્ય check_compound_literal_type (location_t, સંરચના c_type_name *);
બાહ્ય વૃક્ષ c_start_switch (location_t, location_t, વૃક્ષ, bool, વૃક્ષ);
બાહ્ય શૂન્ય c_finish_switch (વૃક્ષ, વૃક્ષ);
બાહ્ય વૃક્ષ build_asm_પદાવલિ (location_t, વૃક્ષ, વૃક્ષ, વૃક્ષ, વૃક્ષ, વૃક્ષ, bool,
			    bool);
બાહ્ય વૃક્ષ build_asm_stmt (bool, વૃક્ષ);
બાહ્ય પૂર્ણાંક c_types_compatible_p (વૃક્ષ, વૃક્ષ);
બાહ્ય વૃક્ષ c_begin_compound_stmt (bool);
બાહ્ય વૃક્ષ c_end_compound_stmt (location_t, વૃક્ષ, bool);
બાહ્ય શૂન્ય c_finish_if_stmt (location_t, વૃક્ષ, વૃક્ષ, વૃક્ષ);
બાહ્ય શૂન્ય c_finish_loop (location_t, location_t, વૃક્ષ, location_t, વૃક્ષ,
			   વૃક્ષ, વૃક્ષ, વૃક્ષ, bool);
બાહ્ય વૃક્ષ c_begin_stmt_પદાવલિ (શૂન્ય);
બાહ્ય વૃક્ષ c_finish_stmt_પદાવલિ (location_t, વૃક્ષ);
બાહ્ય વૃક્ષ c_process_પદાવલિ_stmt (location_t, વૃક્ષ);
બાહ્ય વૃક્ષ c_finish_પદાવલિ_stmt (location_t, વૃક્ષ);
બાહ્ય વૃક્ષ c_finish_return (location_t, વૃક્ષ, વૃક્ષ, bool = false);
બાહ્ય વૃક્ષ c_finish_bc_stmt (location_t, વૃક્ષ, bool, વૃક્ષ);
બાહ્ય વૃક્ષ c_finish_goto_label (location_t, વૃક્ષ);
બાહ્ય વૃક્ષ c_finish_goto_ptr (location_t, c_પદાવલિ val);
બાહ્ય વૃક્ષ c_પદાવલિ_to_decl (વૃક્ષ, bool *, bool *);
બાહ્ય વૃક્ષ c_finish_omp_construct (location_t, ગણના વૃક્ષ_code, વૃક્ષ, વૃક્ષ);
બાહ્ય વૃક્ષ c_finish_oacc_data (location_t, વૃક્ષ, વૃક્ષ);
બાહ્ય વૃક્ષ c_finish_oacc_host_data (location_t, વૃક્ષ, વૃક્ષ);
બાહ્ય વૃક્ષ c_begin_omp_parallel (શૂન્ય);
બાહ્ય વૃક્ષ c_finish_omp_parallel (location_t, વૃક્ષ, વૃક્ષ);
બાહ્ય વૃક્ષ c_begin_omp_task (શૂન્ય);
બાહ્ય વૃક્ષ c_finish_omp_task (location_t, વૃક્ષ, વૃક્ષ);
બાહ્ય શૂન્ય c_finish_omp_cancel (location_t, વૃક્ષ);
બાહ્ય શૂન્ય c_finish_omp_cancellation_point (location_t, વૃક્ષ);
બાહ્ય વૃક્ષ c_finish_omp_clauses (વૃક્ષ, ગણના c_omp_region_type);
બાહ્ય વૃક્ષ c_omp_finish_mapper_clauses (વૃક્ષ);
બાહ્ય વૃક્ષ c_omp_mapper_lookup (વૃક્ષ, વૃક્ષ);
બાહ્ય વૃક્ષ c_omp_extract_mapper_directive (વૃક્ષ);
બાહ્ય વૃક્ષ c_omp_map_array_section (location_t, વૃક્ષ);
બાહ્ય વૃક્ષ c_build_va_arg (location_t, વૃક્ષ, location_t, વૃક્ષ, વૃક્ષ);
બાહ્ય વૃક્ષ c_finish_transaction (location_t, વૃક્ષ, પૂર્ણાંક);
બાહ્ય bool c_વૃક્ષ_equal (વૃક્ષ, વૃક્ષ);
બાહ્ય વૃક્ષ c_build_function_call_vec (location_t, અચલ vec<location_t>&,
				       વૃક્ષ, vec<વૃક્ષ, va_gc> *,
				       vec<વૃક્ષ, va_gc> *);
બાહ્ય વૃક્ષ c_omp_clause_copy_ctor (વૃક્ષ, વૃક્ષ, વૃક્ષ);
બાહ્ય વૃક્ષ c_reconstruct_complex_type (વૃક્ષ, વૃક્ષ);
બાહ્ય વૃક્ષ c_type_canonical (વૃક્ષ);
બાહ્ય વૃક્ષ c_build_type_attribute_variant (વૃક્ષ ntype, વૃક્ષ attrs);
બાહ્ય વૃક્ષ c_build_pointer_type (વૃક્ષ type);
બાહ્ય વૃક્ષ c_build_array_type (વૃક્ષ type, વૃક્ષ domain);
બાહ્ય વૃક્ષ c_build_array_type_unspecified (વૃક્ષ type);
બાહ્ય વૃક્ષ c_build_array_type_zero_size (વૃક્ષ type);
બાહ્ય વૃક્ષ c_build_function_type (વૃક્ષ type, વૃક્ષ args, bool no = false);
બાહ્ય વૃક્ષ c_build_pointer_type_for_mode (વૃક્ષ type, machine_mode mode, bool m);

/* Set to 0 at beginning of a function definition, set to 1 if
   a return statement that specifies a return value is seen.  */

બાહ્ય પૂર્ણાંક current_function_returns_કિંમત;

/* Set to 0 at beginning of a function definition, set to 1 if
   a return statement with no argument is seen.  */

બાહ્ય પૂર્ણાંક current_function_returns_null;

/* Set to 0 at beginning of a function definition, set to 1 if
   a call to a noreturn function is seen.  */

બાહ્ય પૂર્ણાંક current_function_returns_abnormally;

/* In c-decl.cc */

/* Tell the binding oracle what kind of binding we are looking for.  */

ગણના c_oracle_request
{
  C_ORACLE_પ્રતીક,
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

પ્રકારવ્યાખ્યા શૂન્ય c_binding_oracle_function (ગણના c_oracle_request, વૃક્ષ identifier);

બાહ્ય c_binding_oracle_function *c_binding_oracle;

બાહ્ય શૂન્ય c_finish_incomplete_decl (વૃક્ષ);
બાહ્ય વૃક્ષ c_omp_reduction_id (ગણના વૃક્ષ_code, વૃક્ષ);
બાહ્ય વૃક્ષ c_omp_reduction_decl (વૃક્ષ);
બાહ્ય વૃક્ષ c_omp_reduction_lookup (વૃક્ષ, વૃક્ષ);
બાહ્ય વૃક્ષ c_check_omp_declare_reduction_r (વૃક્ષ *, પૂર્ણાંક *, શૂન્ય *);
બાહ્ય વૃક્ષ c_omp_mapper_id (વૃક્ષ);
બાહ્ય વૃક્ષ c_omp_mapper_decl (વૃક્ષ);
બાહ્ય શૂન્ય c_omp_scan_mapper_bindings (location_t, વૃક્ષ *, વૃક્ષ);
બાહ્ય bool c_check_in_current_scope (વૃક્ષ);
બાહ્ય શૂન્ય c_pushtag (location_t, વૃક્ષ, વૃક્ષ);
બાહ્ય શૂન્ય c_bind (location_t, વૃક્ષ, bool);
બાહ્ય bool tag_exists_p (ગણના વૃક્ષ_code, વૃક્ષ);

બાહ્ય શૂન્ય verify_counted_by_for_ટોચ_anonymous_type (વૃક્ષ);

/* In c-errors.cc */
બાહ્ય bool pedwarn_c90 (location_t, diagnostics::option_id, અચલ અક્ષર *, ...)
    ATTRIBUTE_GCC_DIAG(3,4);
બાહ્ય bool pedwarn_c99 (location_t, diagnostics::option_id, અચલ અક્ષર *, ...)
    ATTRIBUTE_GCC_DIAG(3,4);
બાહ્ય bool pedwarn_c11 (location_t, diagnostics::option_id, અચલ અક્ષર *, ...)
    ATTRIBUTE_GCC_DIAG(3,4);
બાહ્ય bool pedwarn_c23 (location_t, diagnostics::option_id, અચલ અક્ષર *, ...)
    ATTRIBUTE_GCC_DIAG(3,4);
બાહ્ય શૂન્ય add_note_about_new_keyword (location_t loc,
					વૃક્ષ keyword_id);

બાહ્ય શૂન્ય
set_c_પદાવલિ_source_range (c_પદાવલિ *પદાવલિ,
			 location_t start, location_t finish);

બાહ્ય શૂન્ય
set_c_પદાવલિ_source_range (c_પદાવલિ *પદાવલિ,
			 source_range src_range);

/* In c-fold.cc */
બાહ્ય vec<વૃક્ષ> incomplete_record_decls;

બાહ્ય અચલ અક્ષર *c_get_sarif_source_language (અચલ અક્ષર *filename);

બાહ્ય અચલ સંરચના scoped_attribute_specs std_attribute_table;

#જો CHECKING_P
namespace selftest {
  બાહ્ય શૂન્ય run_c_tests (શૂન્ય);
} // namespace selftest
#endif /* #if CHECKING_P */


#endif /* ! GCC_C_TREE_H */
