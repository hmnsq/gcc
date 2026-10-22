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

#ifndef GCC_C_درخت_H
#define GCC_C_درخت_H

#شامل "c-family/c-common.h"
#شامل "diagnostic.h"

/* struct lang_identifier is private to c-decl.cc, but langhooks.cc needs to
   know how big it is.  This is sanity-checked in c-decl.cc.  */
#define C_SIZEOF_STRUCT_LANG_IDENTIFIER \
  (اندازه (ساختار c_common_identifier) + 3 * اندازه (تهی *))

/* In a RECORD_TYPE or UNION_TYPE, nonzero if any component is read-only.  */
#define C_TYPE_FIELDS_READONLY(TYPE) درخت_LANG_FLAG_1 (TYPE)

/* In a RECORD_TYPE or UNION_TYPE, nonzero if any component is volatile.  */
#define C_TYPE_FIELDS_VOLATILE(TYPE) درخت_LANG_FLAG_2 (TYPE)

/* In a RECORD_TYPE or UNION_TYPE, nonzero if any component is
   volatile, restrict-qualified or atomic; that is, has a type not
   permitted for a constexpr object.  */
#define C_TYPE_FIELDS_NON_CONSTEXPR(TYPE) درخت_LANG_FLAG_4 (TYPE)

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
  TYPE_LANG_SLOT_1 (درخت_CHECK4 (TYPE, RECORD_TYPE, UNION_TYPE, \
				 QUAL_UNION_TYPE, ENUMERAL_TYPE))

/* In an IDENTIFIER_NODE, nonzero if this identifier is actually a
   keyword.  C_RID_CODE (node) is then the RID_* value of the keyword.  */
#define C_IS_RESERVED_WORD(ID) درخت_LANG_FLAG_0 (ID)

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
#define C_ARRAY_PARAMETER(گره_2) DECL_LANG_FLAG_0 (گره_2)

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
  DECL_LANG_FLAG_4 (درخت_NOT_CHECK (EXP, FUNCTION_DECL))

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
	|| (!prototype_p (درخت_TYPE (EXP))	\
	    && !fndecl_built_in_p (EXP)))

/* For FUNCTION_TYPE, a hidden list of types of arguments.  The same as
   TYPE_ARG_TYPES for functions with prototypes, but created for functions
   without prototypes.  */
#define TYPE_ACTUAL_ARG_TYPES(گره_2) \
  TYPE_LANG_SLOT_1 (FUNCTION_TYPE_CHECK (گره_2))

/* For a CONSTRUCTOR, whether some initializer contains a
   subexpression meaning it is not a constant expression.  */
#define CONSTRUCTOR_NON_CONST(عبارت_2) درخت_LANG_FLAG_1 (CONSTRUCTOR_CHECK (عبارت_2))

/* For a SAVE_EXPR, nonzero if the operand of the SAVE_EXPR has already
   been folded.  */
#define SAVE_عبارت_FOLDED_P(EXP)	درخت_LANG_FLAG_1 (SAVE_عبارت_CHECK (EXP))

/* Whether a type has boolean semantics: either a boolean type or an
   enumeration type with a boolean type as its underlying type.  */
#define C_BOOLEAN_TYPE_P(TYPE)						\
  (درخت_CODE (TYPE) == BOOLEAN_TYPE					\
   || (درخت_CODE (TYPE) == ENUMERAL_TYPE				\
       && ENUM_UNDERLYING_TYPE (TYPE) != NULL_درخت			\
       && (درخت_CODE (ENUM_UNDERLYING_TYPE (TYPE)) == BOOLEAN_TYPE	\
	   || c_hardbool_type_attr (TYPE))))

/* Record parser information about an expression that is irrelevant
   for code generation alongside a tree representing its value.  */
ساختار c_عبارت
{
  /* The value of the expression.  */
  درخت مقدار;
  /* Record the original unary/binary operator of an expression, which may
     have been changed by fold, STRING_CST for unparenthesized string
     constants, C_MAYBE_CONST_EXPR for __builtin_constant_p calls
     (even if parenthesized), for subexpressions, and for non-constant
     initializers, or ERROR_MARK for other expressions (including
     parenthesized expressions).  */
  شمارش درخت_code original_code;
  /* If not NULL, the original type of an expression.  This will
     differ from the type of the value field for an enum constant.
     The type of an enum constant is a plain integer type, but this
     field will be the enum type.  */
  درخت original_type;

  /* The source range of this expression.  This is redundant
     for node values that have locations, but not all node kinds
     have locations (e.g. constants, and references to params, locals,
     etc), so we stash a copy here.  */
  source_range src_range;

  /* True if this was directly from a decimal constant token.  */
  bool m_decimal : 1;

  /* Access to the first and last locations within the source spelling
     of this expression.  */
  location_t get_start () ثابت { بازگشت src_range.m_start; }
  location_t get_finish () ثابت { بازگشت src_range.m_finish; }

  location_t get_location () ثابت
  {
    اگر (عبارت_HAS_LOCATION (مقدار))
      بازگشت عبارت_LOCATION (مقدار);
    وگرنه
      بازگشت make_location (get_start (), get_start (), get_finish ());
  }

  /* Set the value to error_mark_node whilst ensuring that src_range
     and m_decimal are initialized.  */
  تهی set_error ()
  {
    مقدار = error_mark_گره;
    src_range.m_start = UNKNOWN_LOCATION;
    src_range.m_finish = UNKNOWN_LOCATION;
    m_decimal = 0;
  }
};

/* Type alias for struct c_expr. This allows to use the structure
   inside the VEC types.  */
تعریفنوع ساختار c_عبارت c_عبارت_t;

/* A kind of type specifier.  Note that this information is currently
   only used to distinguish tag definitions, tag references and typeof
   uses.  */
شمارش c_typespec_kind {
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
ساختار c_typespec {
  /* What kind of type specifier this is.  */
  شمارش c_typespec_kind kind;
  /* Whether the expression has operands suitable for use in constant
     expressions.  */
  bool عبارت_const_operands;
  /* Whether the type specifier includes an enum type specifier (that
     is, ": specifier-qualifier-list" in a declaration using
     "enum").  */
  bool has_enum_type_specifier;
  /* The specifier itself.  */
  درخت spec;
  /* An expression to be evaluated before the type specifier, in the
     case of typeof specifiers, or NULL otherwise or if no such
     expression is required for a particular typeof specifier.  In
     particular, when typeof is applied to an expression of variably
     modified type, that expression must be evaluated in order to
     determine array sizes that form part of the type, but the
     expression itself (as opposed to the array sizes) forms no part
     of the type and so needs to be recorded separately.  */
  درخت عبارت;
};

/* A storage class specifier.  */
شمارش c_storage_class {
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
شمارش c_typespec_keyword {
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
شمارش c_declspec_word {
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
  cdw_عدد_of_elements /* This one must always be the last
			    enumerator.  */
};

شمارش c_declspec_il {
  cdil_none,
  cdil_gimple,		/* __GIMPLE  */
  cdil_gimple_cfg,	/* __GIMPLE(cfg)  */
  cdil_gimple_ssa,	/* __GIMPLE(ssa)  */
  cdil_rtl		/* __RTL  */
};

/* A sequence of declaration specifiers in C.  When a new declaration
   specifier is added, please update the enum c_declspec_word above
   accordingly.  */
ساختار c_declspecs {
  location_t locations[cdw_عدد_of_elements];
  /* The type specified, if a single type specifier such as a struct,
     union or enum specifier, typedef name or typeof specifies the
     whole type, or NULL_TREE if none or a keyword such as "void" or
     "char" is used.  Does not include qualifiers.  */
  درخت type;
  /* Any expression to be evaluated before the type, from a typeof
     specifier.  */
  درخت عبارت;
  /* The attributes from a typedef decl.  */
  درخت decl_attr;
  /* When parsing, the GNU attributes and prefix standard attributes.
     Outside the parser, this will be NULL; attributes (possibly from
     multiple lists) will be passed separately.  */
  درخت attrs;
  /* When parsing, postfix standard attributes (which appertain to the
     type specified by the preceding declaration specifiers, unlike
     prefix standard attributes which appertain to the declaration or
     declarations as a whole).  */
  درخت postfix_attrs;
  /* The pass to start compiling a __GIMPLE or __RTL function with.  */
  نویسه *gimple_or_rtl_pass;
  /* ENTRY BB count.  */
  profile_شمار entry_bb_شمار;
  /* The base-2 log of the greatest alignment required by an _Alignas
     specifier, in bytes, or -1 if no such specifiers with nonzero
     alignment.  */
  صحیح align_log;
  اجتماع {
    /* For the __intN declspec, this stores the index into the int_n_*
       arrays.  */
    صحیح int_n_idx;
    /* For the _FloatN and _FloatNx declspec, this stores the index into
       the floatn_nx_types array.  */
    صحیح floatn_nx_idx;
    /* For _BitInt(N) this stores the N.  */
    صحیح bitint_prec;
  } u;
  /* The storage class specifier, or csc_none if none.  */
  شمارش c_storage_class storage_class;
  /* Any type specifier keyword used such as "int", not reflecting
     modifiers such as "short", or cts_none if none.  */
  شمارش c_typespec_keyword typespec_word : 8;
  /* The kind of type specifier if one has been seen, ctsk_none
     otherwise.  */
  شمارش c_typespec_kind typespec_kind : 4;
  شمارش c_declspec_il declspec_il : 3;
  /* Whether any expressions in typeof specifiers may appear in
     constant expressions.  */
  bool عبارت_const_operands : 1;
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
شمارش c_declarator_kind {
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

ساختار c_arg_tag {
  /* The argument name.  */
  درخت id;
  /* The type of the argument.  */
  درخت type;
};


/* Information about the parameters in a function declarator.  */
ساختار c_arg_info {
  /* A list of parameter decls.  */
  درخت parms;
  /* A list of structure, union and enum tags defined.  */
  vec<c_arg_tag, va_gc> *tags;
  /* A list of argument types to go in the FUNCTION_TYPE.  */
  درخت types;
  /* A list of non-parameter decls (notably enumeration constants)
     defined with the parameters.  */
  درخت others;
  /* A compound expression of VLA sizes from the parameters, or NULL.
     In a function definition, these are used to ensure that
     side-effects in sizes of arrays converted to pointers (such as a
     parameter int i[n++]) take place; otherwise, they are
     ignored.  */
  درخت pending_sizes;
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
ساختار c_declarator {
  /* The kind of declarator.  */
  شمارش c_declarator_kind kind;
  location_t id_loc; /* Currently only set for cdk_id, cdk_array. */
  /* Except for cdk_id, the contained declarator.  For cdk_id, NULL.  */
  ساختار c_declarator *declarator;
  اجتماع {
    /* For identifiers.  */
    ساختار {
      /* An IDENTIFIER_NODE, or NULL_TREE if an abstract
	 declarator.  */
      درخت id;
      /* Any attributes (which apply to the declaration rather than to
	 the type described by the outer declarators).  */
      درخت attrs;
    } id;
    /* For functions.  */
    ساختار c_arg_info *arg_info;
    /* For arrays.  */
    ساختار {
      /* The array dimension, or NULL for [] and [*].  */
      درخت dimen;
      /* The qualifiers inside [].  */
      صحیح quals;
      /* The attributes (currently ignored) inside [].  */
      درخت attrs;
      /* Whether [static] was used.  */
      bool static_p : 1;
      /* Whether [*] was used.  */
      bool vla_unspec_p : 1;
    } array;
    /* For pointers, the qualifiers on the pointer type.  */
    صحیح pointer_quals;
    /* For attributes.  */
    درخت attrs;
  } u;
};

/* A type name.  */
ساختار c_type_name {
  /* The declaration specifiers.  */
  ساختار c_declspecs *specs;
  /* The declarator.  */
  ساختار c_declarator *declarator;
};

/* A parameter.  */
ساختار c_parm {
  /* The declaration specifiers, minus any prefix attributes.  */
  ساختار c_declspecs *specs;
  /* The attributes.  */
  درخت attrs;
  /* The declarator.  */
  ساختار c_declarator *declarator;
  /* The location of the parameter.  */
  location_t loc;
};

/* Used when parsing an enum.  Initialized by start_enum.  */
ساختار c_enum_contents
{
  /* While defining an enum type, this is 1 plus the last enumerator
     constant value.  */
  درخت enum_next_مقدار;

  /* The enumeration type itself.  */
  درخت enum_type;

  /* Nonzero means that there was overflow computing enum_next_value.  */
  صحیح enum_overflow;
};

/* A type of reference to a static identifier in an inline
   function.  */
شمارش c_inline_static_type {
  /* Identifier with internal linkage used in function that may be an
     inline definition (i.e., file-scope static).  */
  csi_internal,
  /* Modifiable object with static storage duration defined in
     function that may be an inline definition (i.e., local
     static).  */
  csi_modifiable
};

/* Record details of decls possibly used inside sizeof or typeof.  */
ساختار maybe_used_decl
{
  /* The decl.  */
  درخت decl;
  /* The level seen at (in_sizeof + in_typeof + in_countof + in_generic).  */
  صحیح level;
  /* Seen in address-of.  */
  bool address;
  /* The next one at this level or above, or NULL.  */
  ساختار maybe_used_decl *next;
};


/* in c-parser.cc */
ساختار c_درخت_token_vec;
بیرونی تهی c_parse_init (تهی);
بیرونی bool c_keyword_starts_typename (شمارش rid keyword);

/* in c-aux-info.cc */
بیرونی تهی gen_aux_info_record (درخت, صحیح, صحیح, صحیح);

/* in c-decl.cc */
ساختار c_spot_bindings;
class c_struct_parse_info;
بیرونی ساختار obstack parser_obstack;
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
بیرونی unsigned نویسه in_statement;

بیرونی bool switch_statement_break_seen_p;

بیرونی bool global_bindings_p (تهی);
بیرونی درخت pushdecl (درخت);
بیرونی unsigned صحیح start_underspecified_init (location_t, درخت);
بیرونی تهی finish_underspecified_init (درخت, unsigned صحیح);
بیرونی تهی افزودن_scope (تهی);
بیرونی درخت برداشت_scope (تهی);
بیرونی تهی c_mark_decl_jump_unsafe_in_current_scope ();
بیرونی تهی c_bindings_start_stmt_عبارت (ساختار c_spot_bindings *);
بیرونی تهی c_bindings_end_stmt_عبارت (ساختار c_spot_bindings *);

بیرونی تهی record_inline_static (location_t, درخت, درخت,
				  شمارش c_inline_static_type);
بیرونی تهی c_init_decl_processing (تهی);
بیرونی تهی c_print_identifier (FILE *, درخت, صحیح);
بیرونی صحیح quals_from_declspecs (ثابت ساختار c_declspecs *);
بیرونی ساختار c_declarator *build_array_declarator (location_t, درخت,
    						    ساختار c_declspecs *,
						    bool, bool);
بیرونی درخت build_enumerator (location_t, location_t, ساختار c_enum_contents *,
			      درخت, درخت);
بیرونی درخت check_for_loop_decls (location_t, bool);
بیرونی تهی mark_forward_parm_decls (تهی);
بیرونی تهی declare_parm_level (تهی);
بیرونی تهی undeclared_variable (location_t, درخت);
بیرونی درخت lookup_label_for_goto (location_t, درخت);
بیرونی درخت declare_label (درخت);
بیرونی درخت define_label (location_t, درخت);
بیرونی ساختار c_spot_bindings *c_get_switch_bindings (تهی);
بیرونی تهی c_release_switch_bindings (ساختار c_spot_bindings *);
بیرونی bool c_check_switch_jump_warnings (ساختار c_spot_bindings *,
					  location_t, location_t);
بیرونی تهی finish_decl (درخت, location_t, درخت, درخت, درخت);
بیرونی درخت finish_enum (درخت, درخت, درخت);
بیرونی تهی finish_function (location_t = درون_داد_location);
بیرونی درخت finish_struct (location_t, درخت, درخت, درخت,
			   class c_struct_parse_info *,
			   درخت *عبارت = پوچ);
بیرونی درخت c_simulate_enum_decl (location_t, ثابت نویسه *,
				  vec<string_int_pair> *);
بیرونی درخت c_simulate_record_decl (location_t, ثابت نویسه *,
				    array_slice<ثابت درخت>);
بیرونی ساختار c_arg_info *build_arg_info (تهی);
بیرونی ساختار c_arg_info *get_parm_info (bool, درخت);
بیرونی درخت grokfield (location_t, ساختار c_declarator *,
		       ساختار c_declspecs *, درخت, درخت *, درخت *);
بیرونی درخت groktypename (ساختار c_type_name *, درخت *, bool *);
بیرونی درخت grokgenassoc (ساختار c_type_name *);
بیرونی درخت grokparm (ثابت ساختار c_parm *, درخت *);
بیرونی درخت implicitly_declare (location_t, درخت);
بیرونی تهی keep_next_level (تهی);
بیرونی تهی pending_xref_error (تهی);
بیرونی تهی c_افزودن_function_context (تهی);
بیرونی تهی c_برداشت_function_context (تهی);
بیرونی تهی افزودن_parm_decl (ثابت ساختار c_parm *, درخت *);
بیرونی ساختار c_declarator *set_array_declarator_inner (ساختار c_declarator *,
							ساختار c_declarator *);
بیرونی درخت c_builtin_function (درخت);
بیرونی درخت c_builtin_function_ext_scope (درخت);
بیرونی درخت c_simulate_builtin_function_decl (درخت);
بیرونی تهی c_warn_unused_attributes (درخت);
بیرونی درخت c_warn_type_attributes (درخت, درخت);
بیرونی تهی shadow_tag (ثابت ساختار c_declspecs *);
بیرونی تهی shadow_tag_warned (ثابت ساختار c_declspecs *, صحیح);
بیرونی درخت start_enum (location_t, ساختار c_enum_contents *, درخت, درخت,
			bool potential_nesting_p);
بیرونی bool start_function (ساختار c_declspecs *, ساختار c_declarator *, درخت);
بیرونی درخت start_decl (ساختار c_declarator *, ساختار c_declspecs *, bool,
			درخت, bool = true, location_t * = پوچ);
بیرونی درخت start_struct (location_t, شمارش درخت_code, درخت,
			  class c_struct_parse_info **);
بیرونی تهی store_parm_decls (تهی);
بیرونی تهی store_parm_decls_from (ساختار c_arg_info *);
بیرونی تهی temp_store_parm_decls (درخت, درخت);
بیرونی تهی temp_برداشت_parm_decls (تهی);
بیرونی درخت xref_tag (شمارش درخت_code, درخت);
بیرونی ساختار c_typespec parser_xref_tag (location_t, شمارش درخت_code, درخت,
					  bool, درخت, bool);
بیرونی ساختار c_parm *build_c_parm (ساختار c_declspecs *, درخت,
				    ساختار c_declarator *, location_t);
بیرونی ساختار c_declarator *build_attrs_declarator (درخت,
						    ساختار c_declarator *);
بیرونی ساختار c_declarator *build_function_declarator (ساختار c_arg_info *,
						       ساختار c_declarator *);
بیرونی ساختار c_declarator *build_id_declarator (درخت);
بیرونی ساختار c_declarator *make_pointer_declarator (ساختار c_declspecs *,
						     ساختار c_declarator *);
بیرونی ساختار c_declspecs *build_null_declspecs (تهی);
بیرونی ساختار c_declspecs *declspecs_add_qual (location_t,
					       ساختار c_declspecs *, درخت);
بیرونی ساختار c_declspecs *declspecs_add_type (location_t,
					       ساختار c_declspecs *,
					       ساختار c_typespec);
بیرونی ساختار c_declspecs *declspecs_add_scspec (location_t,
						 ساختار c_declspecs *, درخت);
بیرونی ساختار c_declspecs *declspecs_add_attrs (location_t,
						ساختار c_declspecs *, درخت);
بیرونی ساختار c_declspecs *declspecs_add_addrspace (location_t,
						    ساختار c_declspecs *,
						    addr_space_t);
بیرونی ساختار c_declspecs *declspecs_add_alignas (location_t,
						  ساختار c_declspecs *, درخت);
بیرونی ساختار c_declspecs *finish_declspecs (ساختار c_declspecs *);
بیرونی size_t c_درخت_size (شمارش درخت_code);
بیرونی صحیح c_get_loop_names (درخت, bool, درخت *);
بیرونی تهی c_release_loop_names (صحیح);
بیرونی درخت c_finish_bc_name (location_t, درخت, bool);

/* in c-objc-common.cc */
بیرونی bool c_objc_common_init (تهی);
بیرونی bool c_missing_noreturn_ok_p (درخت);
بیرونی bool c_warn_unused_global_decl (const_درخت);
بیرونی تهی c_initialize_diagnostics (diagnostics::context *);
بیرونی bool c_var_mod_p (درخت x, درخت fn);
بیرونی alias_set_type c_get_alias_set (درخت);
بیرونی صحیح c_type_dwarf_attribute (const_درخت, صحیح);
بیرونی درخت c_enum_underlying_base_type (const_درخت);

/* in c-typeck.cc */
بیرونی صحیح in_alignof;
بیرونی صحیح in_sizeof;
بیرونی صحیح in_countof;
بیرونی صحیح in_typeof;
بیرونی صحیح in_generic;
بیرونی bool c_in_omp_for;
بیرونی bool c_omp_array_section_p;

بیرونی درخت c_last_sizeof_arg;
بیرونی location_t c_last_sizeof_loc;

بیرونی ساختار c_switch *c_switch_پشته;

بیرونی bool null_pointer_constant_p (const_درخت);


درونخطی bool
c_type_variably_modified_p (درخت t)
{
  اگر (error_mark_گره == t)
    بازگشت false;
  اگر (C_TYPE_VARIABLY_MODIFIED (t))
    بازگشت true;
  اگر (TYPE_STRUCTURAL_EQUALITY_P (t))
    {
      /* The flag may not have been set yet because of incomplete
	 structure or union types completed later.  */
      انتخاب (درخت_CODE (t))
	{
	حالت ARRAY_TYPE:
	حالت FUNCTION_TYPE:
	حالت POINTER_TYPE:
	  /* Recurse.  */
	  اگر (c_type_variably_modified_p (درخت_TYPE (t)))
	    {
	      C_TYPE_VARIABLY_MODIFIED (t) = 1;
	      بازگشت true;
	    }
	  بشکن;
	پیشفرض:
	  بشکن;
	}
    }
  بازگشت false;
}

درونخطی bool
c_type_unspecified_p (درخت t)
{
  بازگشت error_mark_گره != t
	 && C_TYPE_VARIABLE_SIZE (t) && درخت_CODE (t) == ARRAY_TYPE
	 && TYPE_DOMAIN (t) && TYPE_MAX_مقدار (TYPE_DOMAIN (t))
	 && درخت_CODE (TYPE_MAX_مقدار (TYPE_DOMAIN (t))) == COMPOUND_عبارت
	 && integer_zerop (درخت_OPERAND (TYPE_MAX_مقدار (TYPE_DOMAIN (t)), 0))
	 && integer_zerop (درخت_OPERAND (TYPE_MAX_مقدار (TYPE_DOMAIN (t)), 1));
}

بیرونی bool zero_length_array_type_p (const_درخت type);
بیرونی bool char_type_p (درخت);
بیرونی درخت c_type_tag (const_درخت t);
بیرونی درخت c_objc_common_truthvalue_conversion (location_t, درخت,
						 درخت = integer_type_گره);
بیرونی درخت require_complete_type (location_t, درخت);
بیرونی bool same_translation_unit_p (const_درخت, const_درخت);
بیرونی bool comptypes (درخت, درخت);
بیرونی bool comptypes_same_p (درخت, درخت);
بیرونی bool comptypes_equiv_p (درخت, درخت);
بیرونی bool comptypes_check_enum_int (درخت, درخت, bool *);
بیرونی bool c_mark_addressable (درخت, bool = false, bool = false);
بیرونی تهی c_incomplete_type_error (location_t, const_درخت, const_درخت);
بیرونی درخت c_type_promotes_to (درخت);
بیرونی ساختار c_عبارت default_function_array_conversion (location_t,
							ساختار c_عبارت);
بیرونی ساختار c_عبارت default_function_array_read_conversion (location_t,
							     ساختار c_عبارت);
بیرونی ساختار c_عبارت convert_lvalue_to_rvalue (location_t, ساختار c_عبارت,
					       bool, bool, bool = false);
بیرونی درخت decl_constant_مقدار_1 (درخت, bool);
بیرونی تهی mark_exp_read (درخت);
بیرونی درخت composite_type (درخت, درخت);
بیرونی درخت lookup_field (const_درخت, درخت);
بیرونی درخت build_component_ref (location_t, درخت, درخت, location_t,
				 location_t);
بیرونی درخت handle_counted_by_for_component_ref (location_t, درخت);
بیرونی درخت build_array_ref (location_t, درخت, درخت);
بیرونی درخت build_omp_array_section (location_t, درخت, درخت, درخت);
بیرونی درخت build_external_ref (location_t, درخت, bool, درخت *);
بیرونی تهی برداشت_maybe_used (bool);
بیرونی ساختار maybe_used_decl *save_maybe_used ();
بیرونی تهی restore_maybe_used (ساختار maybe_used_decl *);
بیرونی تهی mark_decl_used (درخت, bool);
بیرونی ساختار c_عبارت c_عبارت_sizeof_عبارت (location_t, ساختار c_عبارت);
بیرونی ساختار c_عبارت c_عبارت_sizeof_type (location_t, ساختار c_type_name *);
بیرونی ساختار c_عبارت c_عبارت_countof_عبارت (location_t, ساختار c_عبارت);
بیرونی ساختار c_عبارت c_عبارت_countof_type (location_t loc,
					  ساختار c_type_name *);
بیرونی ساختار c_عبارت c_عبارت_maxof_type (location_t loc, ساختار c_type_name *);
بیرونی ساختار c_عبارت c_عبارت_minof_type (location_t loc, ساختار c_type_name *);
بیرونی ساختار c_عبارت parser_build_unary_op (location_t, شمارش درخت_code,
    					    ساختار c_عبارت);
بیرونی ساختار c_عبارت parser_build_دودویی_op (location_t,
    					     شمارش درخت_code, ساختار c_عبارت,
					     ساختار c_عبارت, درخت);
بیرونی درخت build_conditional_عبارت (location_t, درخت, bool, درخت, درخت,
				    location_t, درخت, درخت, location_t);
بیرونی درخت build_compound_عبارت (location_t, درخت, درخت);
بیرونی درخت c_cast_عبارت (location_t, ساختار c_type_name *, درخت);
بیرونی درخت build_c_cast (location_t, درخت, درخت);
بیرونی تهی store_init_مقدار (location_t, درخت, درخت, درخت);
بیرونی تهی maybe_warn_string_init (location_t, درخت, ساختار c_عبارت);
بیرونی تهی start_init (درخت, درخت, bool, bool, rich_location *);
بیرونی تهی finish_init (تهی);
بیرونی تهی really_start_incremental_init (درخت);
بیرونی تهی finish_implicit_inits (location_t, ساختار obstack *);
بیرونی تهی افزودن_init_level (location_t, صحیح, ساختار obstack *);
بیرونی ساختار c_عبارت برداشت_init_level (location_t, صحیح, ساختار obstack *,
				     location_t);
بیرونی تهی set_init_index (location_t, درخت, درخت, ساختار obstack *);
بیرونی تهی set_init_label (location_t, درخت, location_t, ساختار obstack *);
unsigned c_maybe_optimize_large_byte_initializer (تهی);
بیرونی تهی process_init_element (location_t, ساختار c_عبارت, bool,
				  ساختار obstack *);
بیرونی درخت build_compound_literal (location_t, درخت, درخت, bool,
				    unsigned صحیح, ساختار c_declspecs *);
بیرونی تهی check_compound_literal_type (location_t, ساختار c_type_name *);
بیرونی درخت c_start_switch (location_t, location_t, درخت, bool, درخت);
بیرونی تهی c_finish_switch (درخت, درخت);
بیرونی درخت build_asm_عبارت (location_t, درخت, درخت, درخت, درخت, درخت, bool,
			    bool);
بیرونی درخت build_asm_stmt (bool, درخت);
بیرونی صحیح c_types_compatible_p (درخت, درخت);
بیرونی درخت c_begin_compound_stmt (bool);
بیرونی درخت c_end_compound_stmt (location_t, درخت, bool);
بیرونی تهی c_finish_if_stmt (location_t, درخت, درخت, درخت);
بیرونی تهی c_finish_loop (location_t, location_t, درخت, location_t, درخت,
			   درخت, درخت, درخت, bool);
بیرونی درخت c_begin_stmt_عبارت (تهی);
بیرونی درخت c_finish_stmt_عبارت (location_t, درخت);
بیرونی درخت c_process_عبارت_stmt (location_t, درخت);
بیرونی درخت c_finish_عبارت_stmt (location_t, درخت);
بیرونی درخت c_finish_return (location_t, درخت, درخت, bool = false);
بیرونی درخت c_finish_bc_stmt (location_t, درخت, bool, درخت);
بیرونی درخت c_finish_goto_label (location_t, درخت);
بیرونی درخت c_finish_goto_ptr (location_t, c_عبارت val);
بیرونی درخت c_عبارت_to_decl (درخت, bool *, bool *);
بیرونی درخت c_finish_omp_construct (location_t, شمارش درخت_code, درخت, درخت);
بیرونی درخت c_finish_oacc_data (location_t, درخت, درخت);
بیرونی درخت c_finish_oacc_host_data (location_t, درخت, درخت);
بیرونی درخت c_begin_omp_parallel (تهی);
بیرونی درخت c_finish_omp_parallel (location_t, درخت, درخت);
بیرونی درخت c_begin_omp_task (تهی);
بیرونی درخت c_finish_omp_task (location_t, درخت, درخت);
بیرونی تهی c_finish_omp_cancel (location_t, درخت);
بیرونی تهی c_finish_omp_cancellation_point (location_t, درخت);
بیرونی درخت c_finish_omp_clauses (درخت, شمارش c_omp_region_type);
بیرونی درخت c_omp_finish_mapper_clauses (درخت);
بیرونی درخت c_omp_mapper_lookup (درخت, درخت);
بیرونی درخت c_omp_extract_mapper_directive (درخت);
بیرونی درخت c_omp_map_array_section (location_t, درخت);
بیرونی درخت c_build_va_arg (location_t, درخت, location_t, درخت, درخت);
بیرونی درخت c_finish_transaction (location_t, درخت, صحیح);
بیرونی bool c_درخت_equal (درخت, درخت);
بیرونی درخت c_build_function_call_vec (location_t, ثابت vec<location_t>&,
				       درخت, vec<درخت, va_gc> *,
				       vec<درخت, va_gc> *);
بیرونی درخت c_omp_clause_copy_ctor (درخت, درخت, درخت);
بیرونی درخت c_reconstruct_complex_type (درخت, درخت);
بیرونی درخت c_type_canonical (درخت);
بیرونی درخت c_build_type_attribute_variant (درخت ntype, درخت attrs);
بیرونی درخت c_build_pointer_type (درخت type);
بیرونی درخت c_build_array_type (درخت type, درخت domain);
بیرونی درخت c_build_array_type_unspecified (درخت type);
بیرونی درخت c_build_array_type_zero_size (درخت type);
بیرونی درخت c_build_function_type (درخت type, درخت args, bool no = false);
بیرونی درخت c_build_pointer_type_for_mode (درخت type, machine_mode mode, bool m);

/* Set to 0 at beginning of a function definition, set to 1 if
   a return statement that specifies a return value is seen.  */

بیرونی صحیح current_function_returns_مقدار;

/* Set to 0 at beginning of a function definition, set to 1 if
   a return statement with no argument is seen.  */

بیرونی صحیح current_function_returns_null;

/* Set to 0 at beginning of a function definition, set to 1 if
   a call to a noreturn function is seen.  */

بیرونی صحیح current_function_returns_abnormally;

/* In c-decl.cc */

/* Tell the binding oracle what kind of binding we are looking for.  */

شمارش c_oracle_request
{
  C_ORACLE_نماد,
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

تعریفنوع تهی c_binding_oracle_function (شمارش c_oracle_request, درخت identifier);

بیرونی c_binding_oracle_function *c_binding_oracle;

بیرونی تهی c_finish_incomplete_decl (درخت);
بیرونی درخت c_omp_reduction_id (شمارش درخت_code, درخت);
بیرونی درخت c_omp_reduction_decl (درخت);
بیرونی درخت c_omp_reduction_lookup (درخت, درخت);
بیرونی درخت c_check_omp_declare_reduction_r (درخت *, صحیح *, تهی *);
بیرونی درخت c_omp_mapper_id (درخت);
بیرونی درخت c_omp_mapper_decl (درخت);
بیرونی تهی c_omp_scan_mapper_bindings (location_t, درخت *, درخت);
بیرونی bool c_check_in_current_scope (درخت);
بیرونی تهی c_pushtag (location_t, درخت, درخت);
بیرونی تهی c_bind (location_t, درخت, bool);
بیرونی bool tag_exists_p (شمارش درخت_code, درخت);

بیرونی تهی verify_counted_by_for_بالاترین_anonymous_type (درخت);

/* In c-errors.cc */
بیرونی bool pedwarn_c90 (location_t, diagnostics::option_id, ثابت نویسه *, ...)
    ATTRIBUTE_GCC_DIAG(3,4);
بیرونی bool pedwarn_c99 (location_t, diagnostics::option_id, ثابت نویسه *, ...)
    ATTRIBUTE_GCC_DIAG(3,4);
بیرونی bool pedwarn_c11 (location_t, diagnostics::option_id, ثابت نویسه *, ...)
    ATTRIBUTE_GCC_DIAG(3,4);
بیرونی bool pedwarn_c23 (location_t, diagnostics::option_id, ثابت نویسه *, ...)
    ATTRIBUTE_GCC_DIAG(3,4);
بیرونی تهی add_note_about_new_keyword (location_t loc,
					درخت keyword_id);

بیرونی تهی
set_c_عبارت_source_range (c_عبارت *عبارت,
			 location_t start, location_t finish);

بیرونی تهی
set_c_عبارت_source_range (c_عبارت *عبارت,
			 source_range src_range);

/* In c-fold.cc */
بیرونی vec<درخت> incomplete_record_decls;

بیرونی ثابت نویسه *c_get_sarif_source_language (ثابت نویسه *filename);

بیرونی ثابت ساختار scoped_attribute_specs std_attribute_table;

#اگر CHECKING_P
namespace selftest {
  بیرونی تهی run_c_tests (تهی);
} // namespace selftest
#endif /* #if CHECKING_P */


#endif /* ! GCC_C_TREE_H */
