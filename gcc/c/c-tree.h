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

#ifndef GCC_C_மரம்_H
#define GCC_C_மரம்_H

#அந்தர்பாவ "c-family/c-common.h"
#அந்தர்பாவ "diagnostic.h"

/* struct lang_identifier is private to c-decl.cc, but langhooks.cc needs to
   know how big it is.  This is sanity-checked in c-decl.cc.  */
#define C_SIZEOF_STRUCT_LANG_IDENTIFIER \
  (அளவு (கட்டமைப்பு c_common_identifier) + 3 * அளவு (வெறுமை *))

/* In a RECORD_TYPE or UNION_TYPE, nonzero if any component is read-only.  */
#define C_TYPE_FIELDS_READONLY(TYPE) மரம்_LANG_FLAG_1 (TYPE)

/* In a RECORD_TYPE or UNION_TYPE, nonzero if any component is volatile.  */
#define C_TYPE_FIELDS_VOLATILE(TYPE) மரம்_LANG_FLAG_2 (TYPE)

/* In a RECORD_TYPE or UNION_TYPE, nonzero if any component is
   volatile, restrict-qualified or atomic; that is, has a type not
   permitted for a constexpr object.  */
#define C_TYPE_FIELDS_NON_CONSTEXPR(TYPE) மரம்_LANG_FLAG_4 (TYPE)

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
  TYPE_LANG_SLOT_1 (மரம்_CHECK4 (TYPE, RECORD_TYPE, UNION_TYPE, \
				 QUAL_UNION_TYPE, ENUMERAL_TYPE))

/* In an IDENTIFIER_NODE, nonzero if this identifier is actually a
   keyword.  C_RID_CODE (node) is then the RID_* value of the keyword.  */
#define C_IS_RESERVED_WORD(ID) மரம்_LANG_FLAG_0 (ID)

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
#define C_ARRAY_PARAMETER(முனை_2) DECL_LANG_FLAG_0 (முனை_2)

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
  DECL_LANG_FLAG_4 (மரம்_NOT_CHECK (EXP, FUNCTION_DECL))

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
	|| (!prototype_p (மரம்_TYPE (EXP))	\
	    && !fndecl_built_in_p (EXP)))

/* For FUNCTION_TYPE, a hidden list of types of arguments.  The same as
   TYPE_ARG_TYPES for functions with prototypes, but created for functions
   without prototypes.  */
#define TYPE_ACTUAL_ARG_TYPES(முனை_2) \
  TYPE_LANG_SLOT_1 (FUNCTION_TYPE_CHECK (முனை_2))

/* For a CONSTRUCTOR, whether some initializer contains a
   subexpression meaning it is not a constant expression.  */
#define CONSTRUCTOR_NON_CONST(கோவை_2) மரம்_LANG_FLAG_1 (CONSTRUCTOR_CHECK (கோவை_2))

/* For a SAVE_EXPR, nonzero if the operand of the SAVE_EXPR has already
   been folded.  */
#define SAVE_கோவை_FOLDED_P(EXP)	மரம்_LANG_FLAG_1 (SAVE_கோவை_CHECK (EXP))

/* Whether a type has boolean semantics: either a boolean type or an
   enumeration type with a boolean type as its underlying type.  */
#define C_BOOLEAN_TYPE_P(TYPE)						\
  (மரம்_CODE (TYPE) == BOOLEAN_TYPE					\
   || (மரம்_CODE (TYPE) == ENUMERAL_TYPE				\
       && ENUM_UNDERLYING_TYPE (TYPE) != NULL_மரம்			\
       && (மரம்_CODE (ENUM_UNDERLYING_TYPE (TYPE)) == BOOLEAN_TYPE	\
	   || c_hardbool_type_attr (TYPE))))

/* Record parser information about an expression that is irrelevant
   for code generation alongside a tree representing its value.  */
கட்டமைப்பு c_கோவை
{
  /* The value of the expression.  */
  மரம் மதிப்பு;
  /* Record the original unary/binary operator of an expression, which may
     have been changed by fold, STRING_CST for unparenthesized string
     constants, C_MAYBE_CONST_EXPR for __builtin_constant_p calls
     (even if parenthesized), for subexpressions, and for non-constant
     initializers, or ERROR_MARK for other expressions (including
     parenthesized expressions).  */
  எண்ணிக்கை மரம்_code original_code;
  /* If not NULL, the original type of an expression.  This will
     differ from the type of the value field for an enum constant.
     The type of an enum constant is a plain integer type, but this
     field will be the enum type.  */
  மரம் original_type;

  /* The source range of this expression.  This is redundant
     for node values that have locations, but not all node kinds
     have locations (e.g. constants, and references to params, locals,
     etc), so we stash a copy here.  */
  source_range src_range;

  /* True if this was directly from a decimal constant token.  */
  bool m_decimal : 1;

  /* Access to the first and last locations within the source spelling
     of this expression.  */
  location_t get_start () மாறிலி { திரும்பு src_range.m_start; }
  location_t get_finish () மாறிலி { திரும்பு src_range.m_finish; }

  location_t get_location () மாறிலி
  {
    எனில் (கோவை_HAS_LOCATION (மதிப்பு))
      திரும்பு கோவை_LOCATION (மதிப்பு);
    இல்லையெனில்
      திரும்பு make_location (get_start (), get_start (), get_finish ());
  }

  /* Set the value to error_mark_node whilst ensuring that src_range
     and m_decimal are initialized.  */
  வெறுமை set_error ()
  {
    மதிப்பு = error_mark_முனை;
    src_range.m_start = UNKNOWN_LOCATION;
    src_range.m_finish = UNKNOWN_LOCATION;
    m_decimal = 0;
  }
};

/* Type alias for struct c_expr. This allows to use the structure
   inside the VEC types.  */
வகைவரை கட்டமைப்பு c_கோவை c_கோவை_t;

/* A kind of type specifier.  Note that this information is currently
   only used to distinguish tag definitions, tag references and typeof
   uses.  */
எண்ணிக்கை c_typespec_kind {
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
கட்டமைப்பு c_typespec {
  /* What kind of type specifier this is.  */
  எண்ணிக்கை c_typespec_kind kind;
  /* Whether the expression has operands suitable for use in constant
     expressions.  */
  bool கோவை_const_operands;
  /* Whether the type specifier includes an enum type specifier (that
     is, ": specifier-qualifier-list" in a declaration using
     "enum").  */
  bool has_enum_type_specifier;
  /* The specifier itself.  */
  மரம் spec;
  /* An expression to be evaluated before the type specifier, in the
     case of typeof specifiers, or NULL otherwise or if no such
     expression is required for a particular typeof specifier.  In
     particular, when typeof is applied to an expression of variably
     modified type, that expression must be evaluated in order to
     determine array sizes that form part of the type, but the
     expression itself (as opposed to the array sizes) forms no part
     of the type and so needs to be recorded separately.  */
  மரம் கோவை;
};

/* A storage class specifier.  */
எண்ணிக்கை c_storage_class {
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
எண்ணிக்கை c_typespec_keyword {
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
எண்ணிக்கை c_declspec_word {
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
  cdw_எண்_of_elements /* This one must always be the last
			    enumerator.  */
};

எண்ணிக்கை c_declspec_il {
  cdil_none,
  cdil_gimple,		/* __GIMPLE  */
  cdil_gimple_cfg,	/* __GIMPLE(cfg)  */
  cdil_gimple_ssa,	/* __GIMPLE(ssa)  */
  cdil_rtl		/* __RTL  */
};

/* A sequence of declaration specifiers in C.  When a new declaration
   specifier is added, please update the enum c_declspec_word above
   accordingly.  */
கட்டமைப்பு c_declspecs {
  location_t locations[cdw_எண்_of_elements];
  /* The type specified, if a single type specifier such as a struct,
     union or enum specifier, typedef name or typeof specifies the
     whole type, or NULL_TREE if none or a keyword such as "void" or
     "char" is used.  Does not include qualifiers.  */
  மரம் type;
  /* Any expression to be evaluated before the type, from a typeof
     specifier.  */
  மரம் கோவை;
  /* The attributes from a typedef decl.  */
  மரம் decl_attr;
  /* When parsing, the GNU attributes and prefix standard attributes.
     Outside the parser, this will be NULL; attributes (possibly from
     multiple lists) will be passed separately.  */
  மரம் attrs;
  /* When parsing, postfix standard attributes (which appertain to the
     type specified by the preceding declaration specifiers, unlike
     prefix standard attributes which appertain to the declaration or
     declarations as a whole).  */
  மரம் postfix_attrs;
  /* The pass to start compiling a __GIMPLE or __RTL function with.  */
  எழுத்து *gimple_or_rtl_pass;
  /* ENTRY BB count.  */
  profile_மொத்தம் entry_bb_மொத்தம்;
  /* The base-2 log of the greatest alignment required by an _Alignas
     specifier, in bytes, or -1 if no such specifiers with nonzero
     alignment.  */
  முழு align_log;
  ஒன்றிப்பு {
    /* For the __intN declspec, this stores the index into the int_n_*
       arrays.  */
    முழு int_n_idx;
    /* For the _FloatN and _FloatNx declspec, this stores the index into
       the floatn_nx_types array.  */
    முழு floatn_nx_idx;
    /* For _BitInt(N) this stores the N.  */
    முழு bitint_prec;
  } u;
  /* The storage class specifier, or csc_none if none.  */
  எண்ணிக்கை c_storage_class storage_class;
  /* Any type specifier keyword used such as "int", not reflecting
     modifiers such as "short", or cts_none if none.  */
  எண்ணிக்கை c_typespec_keyword typespec_word : 8;
  /* The kind of type specifier if one has been seen, ctsk_none
     otherwise.  */
  எண்ணிக்கை c_typespec_kind typespec_kind : 4;
  எண்ணிக்கை c_declspec_il declspec_il : 3;
  /* Whether any expressions in typeof specifiers may appear in
     constant expressions.  */
  bool கோவை_const_operands : 1;
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
எண்ணிக்கை c_declarator_kind {
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

கட்டமைப்பு c_arg_tag {
  /* The argument name.  */
  மரம் id;
  /* The type of the argument.  */
  மரம் type;
};


/* Information about the parameters in a function declarator.  */
கட்டமைப்பு c_arg_info {
  /* A list of parameter decls.  */
  மரம் parms;
  /* A list of structure, union and enum tags defined.  */
  vec<c_arg_tag, va_gc> *tags;
  /* A list of argument types to go in the FUNCTION_TYPE.  */
  மரம் types;
  /* A list of non-parameter decls (notably enumeration constants)
     defined with the parameters.  */
  மரம் others;
  /* A compound expression of VLA sizes from the parameters, or NULL.
     In a function definition, these are used to ensure that
     side-effects in sizes of arrays converted to pointers (such as a
     parameter int i[n++]) take place; otherwise, they are
     ignored.  */
  மரம் pending_sizes;
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
கட்டமைப்பு c_declarator {
  /* The kind of declarator.  */
  எண்ணிக்கை c_declarator_kind kind;
  location_t id_loc; /* Currently only set for cdk_id, cdk_array. */
  /* Except for cdk_id, the contained declarator.  For cdk_id, NULL.  */
  கட்டமைப்பு c_declarator *declarator;
  ஒன்றிப்பு {
    /* For identifiers.  */
    கட்டமைப்பு {
      /* An IDENTIFIER_NODE, or NULL_TREE if an abstract
	 declarator.  */
      மரம் id;
      /* Any attributes (which apply to the declaration rather than to
	 the type described by the outer declarators).  */
      மரம் attrs;
    } id;
    /* For functions.  */
    கட்டமைப்பு c_arg_info *arg_info;
    /* For arrays.  */
    கட்டமைப்பு {
      /* The array dimension, or NULL for [] and [*].  */
      மரம் dimen;
      /* The qualifiers inside [].  */
      முழு quals;
      /* The attributes (currently ignored) inside [].  */
      மரம் attrs;
      /* Whether [static] was used.  */
      bool static_p : 1;
      /* Whether [*] was used.  */
      bool vla_unspec_p : 1;
    } array;
    /* For pointers, the qualifiers on the pointer type.  */
    முழு pointer_quals;
    /* For attributes.  */
    மரம் attrs;
  } u;
};

/* A type name.  */
கட்டமைப்பு c_type_name {
  /* The declaration specifiers.  */
  கட்டமைப்பு c_declspecs *specs;
  /* The declarator.  */
  கட்டமைப்பு c_declarator *declarator;
};

/* A parameter.  */
கட்டமைப்பு c_parm {
  /* The declaration specifiers, minus any prefix attributes.  */
  கட்டமைப்பு c_declspecs *specs;
  /* The attributes.  */
  மரம் attrs;
  /* The declarator.  */
  கட்டமைப்பு c_declarator *declarator;
  /* The location of the parameter.  */
  location_t loc;
};

/* Used when parsing an enum.  Initialized by start_enum.  */
கட்டமைப்பு c_enum_contents
{
  /* While defining an enum type, this is 1 plus the last enumerator
     constant value.  */
  மரம் enum_next_மதிப்பு;

  /* The enumeration type itself.  */
  மரம் enum_type;

  /* Nonzero means that there was overflow computing enum_next_value.  */
  முழு enum_overflow;
};

/* A type of reference to a static identifier in an inline
   function.  */
எண்ணிக்கை c_inline_static_type {
  /* Identifier with internal linkage used in function that may be an
     inline definition (i.e., file-scope static).  */
  csi_internal,
  /* Modifiable object with static storage duration defined in
     function that may be an inline definition (i.e., local
     static).  */
  csi_modifiable
};

/* Record details of decls possibly used inside sizeof or typeof.  */
கட்டமைப்பு maybe_used_decl
{
  /* The decl.  */
  மரம் decl;
  /* The level seen at (in_sizeof + in_typeof + in_countof + in_generic).  */
  முழு level;
  /* Seen in address-of.  */
  bool address;
  /* The next one at this level or above, or NULL.  */
  கட்டமைப்பு maybe_used_decl *next;
};


/* in c-parser.cc */
கட்டமைப்பு c_மரம்_token_vec;
வெளி வெறுமை c_parse_init (வெறுமை);
வெளி bool c_keyword_starts_typename (எண்ணிக்கை rid keyword);

/* in c-aux-info.cc */
வெளி வெறுமை gen_aux_info_record (மரம், முழு, முழு, முழு);

/* in c-decl.cc */
கட்டமைப்பு c_spot_bindings;
class c_struct_parse_info;
வெளி கட்டமைப்பு obstack parser_obstack;
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
வெளி unsigned எழுத்து in_statement;

வெளி bool switch_statement_break_seen_p;

வெளி bool global_bindings_p (வெறுமை);
வெளி மரம் pushdecl (மரம்);
வெளி unsigned முழு start_underspecified_init (location_t, மரம்);
வெளி வெறுமை finish_underspecified_init (மரம், unsigned முழு);
வெளி வெறுமை தள்ளு_scope (வெறுமை);
வெளி மரம் எடு_scope (வெறுமை);
வெளி வெறுமை c_mark_decl_jump_unsafe_in_current_scope ();
வெளி வெறுமை c_bindings_start_stmt_கோவை (கட்டமைப்பு c_spot_bindings *);
வெளி வெறுமை c_bindings_end_stmt_கோவை (கட்டமைப்பு c_spot_bindings *);

வெளி வெறுமை record_inline_static (location_t, மரம், மரம்,
				  எண்ணிக்கை c_inline_static_type);
வெளி வெறுமை c_init_decl_processing (வெறுமை);
வெளி வெறுமை c_print_identifier (FILE *, மரம், முழு);
வெளி முழு quals_from_declspecs (மாறிலி கட்டமைப்பு c_declspecs *);
வெளி கட்டமைப்பு c_declarator *build_array_declarator (location_t, மரம்,
    						    கட்டமைப்பு c_declspecs *,
						    bool, bool);
வெளி மரம் build_enumerator (location_t, location_t, கட்டமைப்பு c_enum_contents *,
			      மரம், மரம்);
வெளி மரம் check_for_loop_decls (location_t, bool);
வெளி வெறுமை mark_forward_parm_decls (வெறுமை);
வெளி வெறுமை declare_parm_level (வெறுமை);
வெளி வெறுமை undeclared_variable (location_t, மரம்);
வெளி மரம் lookup_label_for_goto (location_t, மரம்);
வெளி மரம் declare_label (மரம்);
வெளி மரம் define_label (location_t, மரம்);
வெளி கட்டமைப்பு c_spot_bindings *c_get_switch_bindings (வெறுமை);
வெளி வெறுமை c_release_switch_bindings (கட்டமைப்பு c_spot_bindings *);
வெளி bool c_check_switch_jump_warnings (கட்டமைப்பு c_spot_bindings *,
					  location_t, location_t);
வெளி வெறுமை finish_decl (மரம், location_t, மரம், மரம், மரம்);
வெளி மரம் finish_enum (மரம், மரம், மரம்);
வெளி வெறுமை finish_function (location_t = உள்ளீடு_location);
வெளி மரம் finish_struct (location_t, மரம், மரம், மரம்,
			   class c_struct_parse_info *,
			   மரம் *கோவை = வெற்று);
வெளி மரம் c_simulate_enum_decl (location_t, மாறிலி எழுத்து *,
				  vec<string_int_pair> *);
வெளி மரம் c_simulate_record_decl (location_t, மாறிலி எழுத்து *,
				    array_slice<மாறிலி மரம்>);
வெளி கட்டமைப்பு c_arg_info *build_arg_info (வெறுமை);
வெளி கட்டமைப்பு c_arg_info *get_parm_info (bool, மரம்);
வெளி மரம் grokfield (location_t, கட்டமைப்பு c_declarator *,
		       கட்டமைப்பு c_declspecs *, மரம், மரம் *, மரம் *);
வெளி மரம் groktypename (கட்டமைப்பு c_type_name *, மரம் *, bool *);
வெளி மரம் grokgenassoc (கட்டமைப்பு c_type_name *);
வெளி மரம் grokparm (மாறிலி கட்டமைப்பு c_parm *, மரம் *);
வெளி மரம் implicitly_declare (location_t, மரம்);
வெளி வெறுமை keep_next_level (வெறுமை);
வெளி வெறுமை pending_xref_error (வெறுமை);
வெளி வெறுமை c_தள்ளு_function_context (வெறுமை);
வெளி வெறுமை c_எடு_function_context (வெறுமை);
வெளி வெறுமை தள்ளு_parm_decl (மாறிலி கட்டமைப்பு c_parm *, மரம் *);
வெளி கட்டமைப்பு c_declarator *set_array_declarator_inner (கட்டமைப்பு c_declarator *,
							கட்டமைப்பு c_declarator *);
வெளி மரம் c_builtin_function (மரம்);
வெளி மரம் c_builtin_function_ext_scope (மரம்);
வெளி மரம் c_simulate_builtin_function_decl (மரம்);
வெளி வெறுமை c_warn_unused_attributes (மரம்);
வெளி மரம் c_warn_type_attributes (மரம், மரம்);
வெளி வெறுமை shadow_tag (மாறிலி கட்டமைப்பு c_declspecs *);
வெளி வெறுமை shadow_tag_warned (மாறிலி கட்டமைப்பு c_declspecs *, முழு);
வெளி மரம் start_enum (location_t, கட்டமைப்பு c_enum_contents *, மரம், மரம்,
			bool potential_nesting_p);
வெளி bool start_function (கட்டமைப்பு c_declspecs *, கட்டமைப்பு c_declarator *, மரம்);
வெளி மரம் start_decl (கட்டமைப்பு c_declarator *, கட்டமைப்பு c_declspecs *, bool,
			மரம், bool = true, location_t * = வெற்று);
வெளி மரம் start_struct (location_t, எண்ணிக்கை மரம்_code, மரம்,
			  class c_struct_parse_info **);
வெளி வெறுமை store_parm_decls (வெறுமை);
வெளி வெறுமை store_parm_decls_from (கட்டமைப்பு c_arg_info *);
வெளி வெறுமை temp_store_parm_decls (மரம், மரம்);
வெளி வெறுமை temp_எடு_parm_decls (வெறுமை);
வெளி மரம் xref_tag (எண்ணிக்கை மரம்_code, மரம்);
வெளி கட்டமைப்பு c_typespec parser_xref_tag (location_t, எண்ணிக்கை மரம்_code, மரம்,
					  bool, மரம், bool);
வெளி கட்டமைப்பு c_parm *build_c_parm (கட்டமைப்பு c_declspecs *, மரம்,
				    கட்டமைப்பு c_declarator *, location_t);
வெளி கட்டமைப்பு c_declarator *build_attrs_declarator (மரம்,
						    கட்டமைப்பு c_declarator *);
வெளி கட்டமைப்பு c_declarator *build_function_declarator (கட்டமைப்பு c_arg_info *,
						       கட்டமைப்பு c_declarator *);
வெளி கட்டமைப்பு c_declarator *build_id_declarator (மரம்);
வெளி கட்டமைப்பு c_declarator *make_pointer_declarator (கட்டமைப்பு c_declspecs *,
						     கட்டமைப்பு c_declarator *);
வெளி கட்டமைப்பு c_declspecs *build_null_declspecs (வெறுமை);
வெளி கட்டமைப்பு c_declspecs *declspecs_add_qual (location_t,
					       கட்டமைப்பு c_declspecs *, மரம்);
வெளி கட்டமைப்பு c_declspecs *declspecs_add_type (location_t,
					       கட்டமைப்பு c_declspecs *,
					       கட்டமைப்பு c_typespec);
வெளி கட்டமைப்பு c_declspecs *declspecs_add_scspec (location_t,
						 கட்டமைப்பு c_declspecs *, மரம்);
வெளி கட்டமைப்பு c_declspecs *declspecs_add_attrs (location_t,
						கட்டமைப்பு c_declspecs *, மரம்);
வெளி கட்டமைப்பு c_declspecs *declspecs_add_addrspace (location_t,
						    கட்டமைப்பு c_declspecs *,
						    addr_space_t);
வெளி கட்டமைப்பு c_declspecs *declspecs_add_alignas (location_t,
						  கட்டமைப்பு c_declspecs *, மரம்);
வெளி கட்டமைப்பு c_declspecs *finish_declspecs (கட்டமைப்பு c_declspecs *);
வெளி size_t c_மரம்_size (எண்ணிக்கை மரம்_code);
வெளி முழு c_get_loop_names (மரம், bool, மரம் *);
வெளி வெறுமை c_release_loop_names (முழு);
வெளி மரம் c_finish_bc_name (location_t, மரம், bool);

/* in c-objc-common.cc */
வெளி bool c_objc_common_init (வெறுமை);
வெளி bool c_missing_noreturn_ok_p (மரம்);
வெளி bool c_warn_unused_global_decl (const_மரம்);
வெளி வெறுமை c_initialize_diagnostics (diagnostics::context *);
வெளி bool c_var_mod_p (மரம் x, மரம் fn);
வெளி alias_set_type c_get_alias_set (மரம்);
வெளி முழு c_type_dwarf_attribute (const_மரம், முழு);
வெளி மரம் c_enum_underlying_base_type (const_மரம்);

/* in c-typeck.cc */
வெளி முழு in_alignof;
வெளி முழு in_sizeof;
வெளி முழு in_countof;
வெளி முழு in_typeof;
வெளி முழு in_generic;
வெளி bool c_in_omp_for;
வெளி bool c_omp_array_section_p;

வெளி மரம் c_last_sizeof_arg;
வெளி location_t c_last_sizeof_loc;

வெளி கட்டமைப்பு c_switch *c_switch_அடுக்கு;

வெளி bool null_pointer_constant_p (const_மரம்);


உள்வரி bool
c_type_variably_modified_p (மரம் t)
{
  எனில் (error_mark_முனை == t)
    திரும்பு false;
  எனில் (C_TYPE_VARIABLY_MODIFIED (t))
    திரும்பு true;
  எனில் (TYPE_STRUCTURAL_EQUALITY_P (t))
    {
      /* The flag may not have been set yet because of incomplete
	 structure or union types completed later.  */
      தேர்வு (மரம்_CODE (t))
	{
	நிலை ARRAY_TYPE:
	நிலை FUNCTION_TYPE:
	நிலை POINTER_TYPE:
	  /* Recurse.  */
	  எனில் (c_type_variably_modified_p (மரம்_TYPE (t)))
	    {
	      C_TYPE_VARIABLY_MODIFIED (t) = 1;
	      திரும்பு true;
	    }
	  நிறுத்து;
	இயல்பு:
	  நிறுத்து;
	}
    }
  திரும்பு false;
}

உள்வரி bool
c_type_unspecified_p (மரம் t)
{
  திரும்பு error_mark_முனை != t
	 && C_TYPE_VARIABLE_SIZE (t) && மரம்_CODE (t) == ARRAY_TYPE
	 && TYPE_DOMAIN (t) && TYPE_MAX_மதிப்பு (TYPE_DOMAIN (t))
	 && மரம்_CODE (TYPE_MAX_மதிப்பு (TYPE_DOMAIN (t))) == COMPOUND_கோவை
	 && integer_zerop (மரம்_OPERAND (TYPE_MAX_மதிப்பு (TYPE_DOMAIN (t)), 0))
	 && integer_zerop (மரம்_OPERAND (TYPE_MAX_மதிப்பு (TYPE_DOMAIN (t)), 1));
}

வெளி bool zero_length_array_type_p (const_மரம் type);
வெளி bool char_type_p (மரம்);
வெளி மரம் c_type_tag (const_மரம் t);
வெளி மரம் c_objc_common_truthvalue_conversion (location_t, மரம்,
						 மரம் = integer_type_முனை);
வெளி மரம் require_complete_type (location_t, மரம்);
வெளி bool same_translation_unit_p (const_மரம், const_மரம்);
வெளி bool comptypes (மரம், மரம்);
வெளி bool comptypes_same_p (மரம், மரம்);
வெளி bool comptypes_equiv_p (மரம், மரம்);
வெளி bool comptypes_check_enum_int (மரம், மரம், bool *);
வெளி bool c_mark_addressable (மரம், bool = false, bool = false);
வெளி வெறுமை c_incomplete_type_error (location_t, const_மரம், const_மரம்);
வெளி மரம் c_type_promotes_to (மரம்);
வெளி கட்டமைப்பு c_கோவை default_function_array_conversion (location_t,
							கட்டமைப்பு c_கோவை);
வெளி கட்டமைப்பு c_கோவை default_function_array_read_conversion (location_t,
							     கட்டமைப்பு c_கோவை);
வெளி கட்டமைப்பு c_கோவை convert_lvalue_to_rvalue (location_t, கட்டமைப்பு c_கோவை,
					       bool, bool, bool = false);
வெளி மரம் decl_constant_மதிப்பு_1 (மரம், bool);
வெளி வெறுமை mark_exp_read (மரம்);
வெளி மரம் composite_type (மரம், மரம்);
வெளி மரம் lookup_field (const_மரம், மரம்);
வெளி மரம் build_component_ref (location_t, மரம், மரம், location_t,
				 location_t);
வெளி மரம் handle_counted_by_for_component_ref (location_t, மரம்);
வெளி மரம் build_array_ref (location_t, மரம், மரம்);
வெளி மரம் build_omp_array_section (location_t, மரம், மரம், மரம்);
வெளி மரம் build_external_ref (location_t, மரம், bool, மரம் *);
வெளி வெறுமை எடு_maybe_used (bool);
வெளி கட்டமைப்பு maybe_used_decl *save_maybe_used ();
வெளி வெறுமை restore_maybe_used (கட்டமைப்பு maybe_used_decl *);
வெளி வெறுமை mark_decl_used (மரம், bool);
வெளி கட்டமைப்பு c_கோவை c_கோவை_sizeof_கோவை (location_t, கட்டமைப்பு c_கோவை);
வெளி கட்டமைப்பு c_கோவை c_கோவை_sizeof_type (location_t, கட்டமைப்பு c_type_name *);
வெளி கட்டமைப்பு c_கோவை c_கோவை_countof_கோவை (location_t, கட்டமைப்பு c_கோவை);
வெளி கட்டமைப்பு c_கோவை c_கோவை_countof_type (location_t loc,
					  கட்டமைப்பு c_type_name *);
வெளி கட்டமைப்பு c_கோவை c_கோவை_maxof_type (location_t loc, கட்டமைப்பு c_type_name *);
வெளி கட்டமைப்பு c_கோவை c_கோவை_minof_type (location_t loc, கட்டமைப்பு c_type_name *);
வெளி கட்டமைப்பு c_கோவை parser_build_unary_op (location_t, எண்ணிக்கை மரம்_code,
    					    கட்டமைப்பு c_கோவை);
வெளி கட்டமைப்பு c_கோவை parser_build_இருமம்_op (location_t,
    					     எண்ணிக்கை மரம்_code, கட்டமைப்பு c_கோவை,
					     கட்டமைப்பு c_கோவை, மரம்);
வெளி மரம் build_conditional_கோவை (location_t, மரம், bool, மரம், மரம்,
				    location_t, மரம், மரம், location_t);
வெளி மரம் build_compound_கோவை (location_t, மரம், மரம்);
வெளி மரம் c_cast_கோவை (location_t, கட்டமைப்பு c_type_name *, மரம்);
வெளி மரம் build_c_cast (location_t, மரம், மரம்);
வெளி வெறுமை store_init_மதிப்பு (location_t, மரம், மரம், மரம்);
வெளி வெறுமை maybe_warn_string_init (location_t, மரம், கட்டமைப்பு c_கோவை);
வெளி வெறுமை start_init (மரம், மரம், bool, bool, rich_location *);
வெளி வெறுமை finish_init (வெறுமை);
வெளி வெறுமை really_start_incremental_init (மரம்);
வெளி வெறுமை finish_implicit_inits (location_t, கட்டமைப்பு obstack *);
வெளி வெறுமை தள்ளு_init_level (location_t, முழு, கட்டமைப்பு obstack *);
வெளி கட்டமைப்பு c_கோவை எடு_init_level (location_t, முழு, கட்டமைப்பு obstack *,
				     location_t);
வெளி வெறுமை set_init_index (location_t, மரம், மரம், கட்டமைப்பு obstack *);
வெளி வெறுமை set_init_label (location_t, மரம், location_t, கட்டமைப்பு obstack *);
unsigned c_maybe_optimize_large_byte_initializer (வெறுமை);
வெளி வெறுமை process_init_element (location_t, கட்டமைப்பு c_கோவை, bool,
				  கட்டமைப்பு obstack *);
வெளி மரம் build_compound_literal (location_t, மரம், மரம், bool,
				    unsigned முழு, கட்டமைப்பு c_declspecs *);
வெளி வெறுமை check_compound_literal_type (location_t, கட்டமைப்பு c_type_name *);
வெளி மரம் c_start_switch (location_t, location_t, மரம், bool, மரம்);
வெளி வெறுமை c_finish_switch (மரம், மரம்);
வெளி மரம் build_asm_கோவை (location_t, மரம், மரம், மரம், மரம், மரம், bool,
			    bool);
வெளி மரம் build_asm_stmt (bool, மரம்);
வெளி முழு c_types_compatible_p (மரம், மரம்);
வெளி மரம் c_begin_compound_stmt (bool);
வெளி மரம் c_end_compound_stmt (location_t, மரம், bool);
வெளி வெறுமை c_finish_if_stmt (location_t, மரம், மரம், மரம்);
வெளி வெறுமை c_finish_loop (location_t, location_t, மரம், location_t, மரம்,
			   மரம், மரம், மரம், bool);
வெளி மரம் c_begin_stmt_கோவை (வெறுமை);
வெளி மரம் c_finish_stmt_கோவை (location_t, மரம்);
வெளி மரம் c_process_கோவை_stmt (location_t, மரம்);
வெளி மரம் c_finish_கோவை_stmt (location_t, மரம்);
வெளி மரம் c_finish_return (location_t, மரம், மரம், bool = false);
வெளி மரம் c_finish_bc_stmt (location_t, மரம், bool, மரம்);
வெளி மரம் c_finish_goto_label (location_t, மரம்);
வெளி மரம் c_finish_goto_ptr (location_t, c_கோவை val);
வெளி மரம் c_கோவை_to_decl (மரம், bool *, bool *);
வெளி மரம் c_finish_omp_construct (location_t, எண்ணிக்கை மரம்_code, மரம், மரம்);
வெளி மரம் c_finish_oacc_data (location_t, மரம், மரம்);
வெளி மரம் c_finish_oacc_host_data (location_t, மரம், மரம்);
வெளி மரம் c_begin_omp_parallel (வெறுமை);
வெளி மரம் c_finish_omp_parallel (location_t, மரம், மரம்);
வெளி மரம் c_begin_omp_task (வெறுமை);
வெளி மரம் c_finish_omp_task (location_t, மரம், மரம்);
வெளி வெறுமை c_finish_omp_cancel (location_t, மரம்);
வெளி வெறுமை c_finish_omp_cancellation_point (location_t, மரம்);
வெளி மரம் c_finish_omp_clauses (மரம், எண்ணிக்கை c_omp_region_type);
வெளி மரம் c_omp_finish_mapper_clauses (மரம்);
வெளி மரம் c_omp_mapper_lookup (மரம், மரம்);
வெளி மரம் c_omp_extract_mapper_directive (மரம்);
வெளி மரம் c_omp_map_array_section (location_t, மரம்);
வெளி மரம் c_build_va_arg (location_t, மரம், location_t, மரம், மரம்);
வெளி மரம் c_finish_transaction (location_t, மரம், முழு);
வெளி bool c_மரம்_equal (மரம், மரம்);
வெளி மரம் c_build_function_call_vec (location_t, மாறிலி vec<location_t>&,
				       மரம், vec<மரம், va_gc> *,
				       vec<மரம், va_gc> *);
வெளி மரம் c_omp_clause_copy_ctor (மரம், மரம், மரம்);
வெளி மரம் c_reconstruct_complex_type (மரம், மரம்);
வெளி மரம் c_type_canonical (மரம்);
வெளி மரம் c_build_type_attribute_variant (மரம் ntype, மரம் attrs);
வெளி மரம் c_build_pointer_type (மரம் type);
வெளி மரம் c_build_array_type (மரம் type, மரம் domain);
வெளி மரம் c_build_array_type_unspecified (மரம் type);
வெளி மரம் c_build_array_type_zero_size (மரம் type);
வெளி மரம் c_build_function_type (மரம் type, மரம் args, bool no = false);
வெளி மரம் c_build_pointer_type_for_mode (மரம் type, machine_mode mode, bool m);

/* Set to 0 at beginning of a function definition, set to 1 if
   a return statement that specifies a return value is seen.  */

வெளி முழு current_function_returns_மதிப்பு;

/* Set to 0 at beginning of a function definition, set to 1 if
   a return statement with no argument is seen.  */

வெளி முழு current_function_returns_null;

/* Set to 0 at beginning of a function definition, set to 1 if
   a call to a noreturn function is seen.  */

வெளி முழு current_function_returns_abnormally;

/* In c-decl.cc */

/* Tell the binding oracle what kind of binding we are looking for.  */

எண்ணிக்கை c_oracle_request
{
  C_ORACLE_குறியீடு,
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

வகைவரை வெறுமை c_binding_oracle_function (எண்ணிக்கை c_oracle_request, மரம் identifier);

வெளி c_binding_oracle_function *c_binding_oracle;

வெளி வெறுமை c_finish_incomplete_decl (மரம்);
வெளி மரம் c_omp_reduction_id (எண்ணிக்கை மரம்_code, மரம்);
வெளி மரம் c_omp_reduction_decl (மரம்);
வெளி மரம் c_omp_reduction_lookup (மரம், மரம்);
வெளி மரம் c_check_omp_declare_reduction_r (மரம் *, முழு *, வெறுமை *);
வெளி மரம் c_omp_mapper_id (மரம்);
வெளி மரம் c_omp_mapper_decl (மரம்);
வெளி வெறுமை c_omp_scan_mapper_bindings (location_t, மரம் *, மரம்);
வெளி bool c_check_in_current_scope (மரம்);
வெளி வெறுமை c_pushtag (location_t, மரம், மரம்);
வெளி வெறுமை c_bind (location_t, மரம், bool);
வெளி bool tag_exists_p (எண்ணிக்கை மரம்_code, மரம்);

வெளி வெறுமை verify_counted_by_for_உச்சி_anonymous_type (மரம்);

/* In c-errors.cc */
வெளி bool pedwarn_c90 (location_t, diagnostics::option_id, மாறிலி எழுத்து *, ...)
    ATTRIBUTE_GCC_DIAG(3,4);
வெளி bool pedwarn_c99 (location_t, diagnostics::option_id, மாறிலி எழுத்து *, ...)
    ATTRIBUTE_GCC_DIAG(3,4);
வெளி bool pedwarn_c11 (location_t, diagnostics::option_id, மாறிலி எழுத்து *, ...)
    ATTRIBUTE_GCC_DIAG(3,4);
வெளி bool pedwarn_c23 (location_t, diagnostics::option_id, மாறிலி எழுத்து *, ...)
    ATTRIBUTE_GCC_DIAG(3,4);
வெளி வெறுமை add_note_about_new_keyword (location_t loc,
					மரம் keyword_id);

வெளி வெறுமை
set_c_கோவை_source_range (c_கோவை *கோவை,
			 location_t start, location_t finish);

வெளி வெறுமை
set_c_கோவை_source_range (c_கோவை *கோவை,
			 source_range src_range);

/* In c-fold.cc */
வெளி vec<மரம்> incomplete_record_decls;

வெளி மாறிலி எழுத்து *c_get_sarif_source_language (மாறிலி எழுத்து *filename);

வெளி மாறிலி கட்டமைப்பு scoped_attribute_specs std_attribute_table;

#எனில் CHECKING_P
namespace selftest {
  வெளி வெறுமை run_c_tests (வெறுமை);
} // namespace selftest
#endif /* #if CHECKING_P */


#endif /* ! GCC_C_TREE_H */
