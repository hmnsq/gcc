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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GCC_C_ਰੁੱਖ_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GCC_C_ਰੁੱਖ_H

#ਅਨ੍ਤਰ੍ਭਾਵ "c-family/c-common.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "diagnostic.h"

/* struct lang_identifier is private to c-decl.cc, but langhooks.cc needs to
   know how big it is.  This is sanity-checked in c-decl.cc.  */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ C_SIZEOF_STRUCT_LANG_IDENTIFIER \
  (ਆਕਾਰ (ਬਣਤਰ c_common_identifier) + 3 * ਆਕਾਰ (ਖਾਲੀ *))

/* In a RECORD_TYPE or UNION_TYPE, nonzero if any component is read-only.  */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ C_TYPE_FIELDS_READONLY(TYPE) ਰੁੱਖ_LANG_FLAG_1 (TYPE)

/* In a RECORD_TYPE or UNION_TYPE, nonzero if any component is volatile.  */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ C_TYPE_FIELDS_VOLATILE(TYPE) ਰੁੱਖ_LANG_FLAG_2 (TYPE)

/* In a RECORD_TYPE or UNION_TYPE, nonzero if any component is
   volatile, restrict-qualified or atomic; that is, has a type not
   permitted for a constexpr object.  */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ C_TYPE_FIELDS_NON_CONSTEXPR(TYPE) ਰੁੱਖ_LANG_FLAG_4 (TYPE)

/* In a RECORD_TYPE or UNION_TYPE, nonzero if any component has a
   counted_by attribute.  */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ C_TYPE_FIELDS_HAS_COUNTED_BY(TYPE) TYPE_LANG_FLAG_3 (TYPE)

/* In a RECORD_TYPE or UNION_TYPE or ENUMERAL_TYPE
   nonzero if the definition of the type has already started.  */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ C_TYPE_BEING_DEFINED(TYPE) TYPE_LANG_FLAG_0 (TYPE)

/* In an incomplete RECORD_TYPE, UNION_TYPE or ENUMERAL_TYPE, a list of
   variable declarations whose type would be completed by completing
   that type.  */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ C_TYPE_INCOMPLETE_VARS(TYPE) \
  TYPE_LANG_ਥਾਂ_1 (ਰੁੱਖ_CHECK4 (TYPE, ਰਿਕਾਰਡ_TYPE, UNION_TYPE, \
				 QUAL_UNION_TYPE, ENUMERAL_TYPE))

/* In an IDENTIFIER_NODE, nonzero if this identifier is actually a
   keyword.  C_RID_CODE (node) is then the RID_* value of the keyword.  */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ C_IS_RESERVED_ਸ਼ਬਦ(ID) ਰੁੱਖ_LANG_FLAG_0 (ID)

/* Record whether a type or decl was written with nonconstant size.
   Note that TYPE_SIZE may have simplified to a constant.  */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ C_TYPE_VARIABLE_ਮਾਪ(TYPE) TYPE_LANG_FLAG_1 (TYPE)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ C_DECL_VARIABLE_ਮਾਪ(TYPE) DECL_LANG_FLAG_0 (TYPE)

/* Record whether a type is variably modified. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ C_TYPE_VARIABLY_MODIFIED(TYPE) TYPE_LANG_FLAG_6 (TYPE)


/* Record whether a type is defined inside a struct or union type.
   This is used for -Wc++-compat. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ C_TYPE_DEFINED_ਵਿੱਚ_STRUCT(TYPE) TYPE_LANG_FLAG_2 (TYPE)

/* Record whether a typedef for type `int' was actually `signed int'.  */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ C_TYPEDEF_EXPLICITLY_SIGNED(EXP) DECL_LANG_FLAG_1 (EXP)

/* For a FUNCTION_DECL, nonzero if it was defined without an explicit
   return type.  */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ C_FUNCTION_IMPLICIT_INT(EXP) DECL_LANG_FLAG_1 (EXP)

/* For a FUNCTION_DECL, nonzero if it was an implicit declaration.  */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ C_DECL_IMPLICIT(EXP) DECL_LANG_FLAG_2 (EXP)

/* For a PARM_DECL, nonzero if it was declared as an array.  */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ C_ARRAY_PARAMETER(ਗੰਢ_2) DECL_LANG_FLAG_0 (ਗੰਢ_2)

/* For FUNCTION_DECLs, evaluates true if the decl is a nested
   function that requires a non-local context.  */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ C_FUNC_NONLOCAL_CONTEXT(EXP)		\
  DECL_LANG_FLAG_4 (FUNCTION_DECL_CHECK (EXP))

/* For FUNCTION_DECLs, evaluates true if the decl is built-in but has
   been declared.  */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ C_DECL_DECLARED_BUILTIN(EXP)		\
  DECL_LANG_FLAG_3 (FUNCTION_DECL_CHECK (EXP))

/* For FUNCTION_DECLs, evaluates true if the decl is built-in, has a
   built-in prototype and does not have a non-built-in prototype.  */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ C_DECL_BUILTIN_PROTOTYPE(EXP)		\
  DECL_LANG_FLAG_6 (FUNCTION_DECL_CHECK (EXP))

/* For LABEL_DECLs marks canonical name of a loop.  */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ C_DECL_LOOP_NAME(EXP) DECL_LANG_FLAG_3 (LABEL_DECL_CHECK (EXP))

/* For LABEL_DECLs marks canonical name of a switch.  During parsing of
   ObjC foreach named loop both C_DECL_LOOP_NAME and C_DECL_SWITCH_NAME
   are temporarily set.  */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ C_DECL_SWITCH_NAME(EXP) DECL_LANG_FLAG_5 (LABEL_DECL_CHECK (EXP))

/* For LABEL_DECLs marks canonical name of a loop or switch being
   valid for use in break identifier or continue identifier statements.  */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ C_DECL_LOOP_SWITCH_NAME_VALID(EXP) \
  DECL_LANG_FLAG_6 (LABEL_DECL_CHECK (EXP))

/* For LABEL_DECLs marks canonical loop or switch names which were actually
   used in one or more break identifier or continue identifier statements.  */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ C_DECL_LOOP_SWITCH_NAME_ਵਰਤਿਆ(EXP) \
  DECL_LANG_FLAG_8 (LABEL_DECL_CHECK (EXP))

/* Record whether a decl was declared register.  This is strictly a
   front-end flag, whereas DECL_REGISTER is used for code generation;
   they may differ for structures with volatile fields.  */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ C_DECL_ਰਜਿਸਟਰ(EXP) \
  DECL_LANG_FLAG_4 (ਰੁੱਖ_NOT_CHECK (EXP, FUNCTION_DECL))

/* Record whether a decl was used in an expression anywhere except an
   unevaluated operand of sizeof / typeof / alignof.  This is only
   used for functions declared static but not defined, though outside
   sizeof and typeof it is set for other function decls as well.  */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ C_DECL_ਵਰਤਿਆ(EXP) DECL_LANG_FLAG_5 (FUNCTION_DECL_CHECK (EXP))

/* Record whether a variable has been declared threadprivate by
   #pragma omp threadprivate.  */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ C_DECL_THREADPRIVATE_P(DECL) DECL_LANG_FLAG_3 (VAR_DECL_CHECK (DECL))

/* Set on VAR_DECLs for compound literals.  */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ C_DECL_COMPOUND_LITERAL_P(DECL) \
  DECL_LANG_FLAG_5 (VAR_DECL_CHECK (DECL))

/* Set on decls used as placeholders for a C23 underspecified object
   definition.  */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ C_DECL_UNDERSPECIFIED(DECL) DECL_LANG_FLAG_7 (DECL)

/* Set on VAR_DECLs declared as 'constexpr'.  */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ C_DECL_DECLARED_CONSTEXPR(DECL) \
  DECL_LANG_FLAG_8 (VAR_DECL_CHECK (DECL))

/* Nonzero for a decl which either doesn't exist or isn't a prototype.
   N.B. Could be simplified if all built-in decls had complete prototypes
   (but this is presently difficult because some of them need FILE*).  */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ C_DECL_ISNT_PROTOTYPE(EXP)			\
       (EXP == 0					\
	|| (!prototype_p (ਰੁੱਖ_TYPE (EXP))	\
	    && !fndecl_built_ਵਿੱਚ_p (EXP)))

/* For FUNCTION_TYPE, a hidden list of types of arguments.  The same as
   TYPE_ARG_TYPES for functions with prototypes, but created for functions
   without prototypes.  */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TYPE_ACTUAL_ARG_TYPES(ਗੰਢ_2) \
  TYPE_LANG_ਥਾਂ_1 (FUNCTION_TYPE_CHECK (ਗੰਢ_2))

/* For a CONSTRUCTOR, whether some initializer contains a
   subexpression meaning it is not a constant expression.  */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CONSTRUCTOR_NON_CONST(ਵਿਅੰਜਕ_3) ਰੁੱਖ_LANG_FLAG_1 (CONSTRUCTOR_CHECK (ਵਿਅੰਜਕ_3))

/* For a SAVE_EXPR, nonzero if the operand of the SAVE_EXPR has already
   been folded.  */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SAVE_ਵਿਅੰਜਕ_FOLDED_P(EXP)	ਰੁੱਖ_LANG_FLAG_1 (SAVE_ਵਿਅੰਜਕ_CHECK (EXP))

/* Whether a type has boolean semantics: either a boolean type or an
   enumeration type with a boolean type as its underlying type.  */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ C_BOOLEAN_TYPE_P(TYPE)						\
  (ਰੁੱਖ_ਕੋਡ (TYPE) == BOOLEAN_TYPE					\
   || (ਰੁੱਖ_ਕੋਡ (TYPE) == ENUMERAL_TYPE				\
       && ENUM_UNDERLYING_TYPE (TYPE) != NULL_ਰੁੱਖ			\
       && (ਰੁੱਖ_ਕੋਡ (ENUM_UNDERLYING_TYPE (TYPE)) == BOOLEAN_TYPE	\
	   || c_hardbool_type_attr (TYPE))))

/* Record parser information about an expression that is irrelevant
   for code generation alongside a tree representing its value.  */
ਬਣਤਰ c_ਵਿਅੰਜਕ
{
  /* The value of the expression.  */
  ਰੁੱਖ ਮੁੱਲ;
  /* Record the original unary/binary operator of an expression, which may
     have been changed by fold, STRING_CST for unparenthesized string
     constants, C_MAYBE_CONST_EXPR for __builtin_constant_p calls
     (even if parenthesized), for subexpressions, and for non-constant
     initializers, or ERROR_MARK for other expressions (including
     parenthesized expressions).  */
  ਗਿਣਤੀ ਰੁੱਖ_ਕੋਡ_2 original_ਕੋਡ;
  /* If not NULL, the original type of an expression.  This will
     differ from the type of the value field for an enum constant.
     The type of an enum constant is a plain integer type, but this
     field will be the enum type.  */
  ਰੁੱਖ original_type;

  /* The source range of this expression.  This is redundant
     for node values that have locations, but not all node kinds
     have locations (e.g. constants, and references to params, locals,
     etc), so we stash a copy here.  */
  ਸਰੋਤ_range src_range;

  /* True if this was directly from a decimal constant token.  */
  bool m_decimal : 1;

  /* Access to the first and last locations within the source spelling
     of this expression.  */
  location_t get_ਸ਼ੁਰੂ () ਅਚਲ { ਵਾਪਸ src_range.m_ਸ਼ੁਰੂ; }
  location_t get_ਅੰਤ () ਅਚਲ { ਵਾਪਸ src_range.m_ਅੰਤ; }

  location_t get_location () ਅਚਲ
  {
    ਜੇ (ਵਿਅੰਜਕ_HAS_LOCATION (ਮੁੱਲ))
      ਵਾਪਸ ਵਿਅੰਜਕ_LOCATION (ਮੁੱਲ);
    ਨਹੀਂਤਾਂ
      ਵਾਪਸ make_location (get_ਸ਼ੁਰੂ (), get_ਸ਼ੁਰੂ (), get_ਅੰਤ ());
  }

  /* Set the value to error_mark_node whilst ensuring that src_range
     and m_decimal are initialized.  */
  ਖਾਲੀ ਸੈੱਟ_error ()
  {
    ਮੁੱਲ = error_mark_ਗੰਢ;
    src_range.m_ਸ਼ੁਰੂ = UNKNOWN_LOCATION;
    src_range.m_ਅੰਤ = UNKNOWN_LOCATION;
    m_decimal = 0;
  }
};

/* Type alias for struct c_expr. This allows to use the structure
   inside the VEC types.  */
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ c_ਵਿਅੰਜਕ c_ਵਿਅੰਜਕ_t;

/* A kind of type specifier.  Note that this information is currently
   only used to distinguish tag definitions, tag references and typeof
   uses.  */
ਗਿਣਤੀ c_typespec_ਕਿਸਮ {
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
ਬਣਤਰ c_typespec {
  /* What kind of type specifier this is.  */
  ਗਿਣਤੀ c_typespec_ਕਿਸਮ ਕਿਸਮ;
  /* Whether the expression has operands suitable for use in constant
     expressions.  */
  bool ਵਿਅੰਜਕ_const_operands;
  /* Whether the type specifier includes an enum type specifier (that
     is, ": specifier-qualifier-list" in a declaration using
     "enum").  */
  bool has_enum_type_specifier;
  /* The specifier itself.  */
  ਰੁੱਖ spec;
  /* An expression to be evaluated before the type specifier, in the
     case of typeof specifiers, or NULL otherwise or if no such
     expression is required for a particular typeof specifier.  In
     particular, when typeof is applied to an expression of variably
     modified type, that expression must be evaluated in order to
     determine array sizes that form part of the type, but the
     expression itself (as opposed to the array sizes) forms no part
     of the type and so needs to be recorded separately.  */
  ਰੁੱਖ ਵਿਅੰਜਕ;
};

/* A storage class specifier.  */
ਗਿਣਤੀ c_storage_class {
  csc_none,
  csc_auto,
  csc_extern,
  csc_ਰਜਿਸਟਰ,
  csc_static,
  csc_typedef
};

/* A type specifier keyword "void", "_Bool", "char", "int", "float",
   "double", "_Decimal32", "_Decimal64", "_Decimal128", "_Decimal64x",
   "_Fract", "_Accum", "_BitInt", or none of these.  */
ਗਿਣਤੀ c_typespec_keyword {
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
ਗਿਣਤੀ c_declspec_ਸ਼ਬਦ {
  cdw_typespec /* A catch-all for a typespec.  */,
  cdw_storage_class  /* A catch-all for a storage class */,
  cdw_ਗੁਣ,
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
  cdw_ਪਤਾ_space,
  cdw_gimple,
  cdw_rtl,
  cdw_ਸੰਖਿਆ_ਦਾ_elements /* This one must always be the last
			    enumerator.  */
};

ਗਿਣਤੀ c_declspec_il {
  cdil_none,
  cdil_gimple,		/* __GIMPLE  */
  cdil_gimple_cfg,	/* __GIMPLE(cfg)  */
  cdil_gimple_ssa,	/* __GIMPLE(ssa)  */
  cdil_rtl		/* __RTL  */
};

/* A sequence of declaration specifiers in C.  When a new declaration
   specifier is added, please update the enum c_declspec_word above
   accordingly.  */
ਬਣਤਰ c_declspecs {
  location_t locations[cdw_ਸੰਖਿਆ_ਦਾ_elements];
  /* The type specified, if a single type specifier such as a struct,
     union or enum specifier, typedef name or typeof specifies the
     whole type, or NULL_TREE if none or a keyword such as "void" or
     "char" is used.  Does not include qualifiers.  */
  ਰੁੱਖ type;
  /* Any expression to be evaluated before the type, from a typeof
     specifier.  */
  ਰੁੱਖ ਵਿਅੰਜਕ;
  /* The attributes from a typedef decl.  */
  ਰੁੱਖ decl_attr;
  /* When parsing, the GNU attributes and prefix standard attributes.
     Outside the parser, this will be NULL; attributes (possibly from
     multiple lists) will be passed separately.  */
  ਰੁੱਖ attrs;
  /* When parsing, postfix standard attributes (which appertain to the
     type specified by the preceding declaration specifiers, unlike
     prefix standard attributes which appertain to the declaration or
     declarations as a whole).  */
  ਰੁੱਖ postfix_attrs;
  /* The pass to start compiling a __GIMPLE or __RTL function with.  */
  ਅੱਖਰ *gimple_or_rtl_pass;
  /* ENTRY BB count.  */
  profile_ਗਿਣਤੀ ਇੰਦਰਾਜ_bb_ਗਿਣਤੀ;
  /* The base-2 log of the greatest alignment required by an _Alignas
     specifier, in bytes, or -1 if no such specifiers with nonzero
     alignment.  */
  ਪੂਰਨ align_log;
  ਸੰਘ {
    /* For the __intN declspec, this stores the index into the int_n_*
       arrays.  */
    ਪੂਰਨ int_n_idx;
    /* For the _FloatN and _FloatNx declspec, this stores the index into
       the floatn_nx_types array.  */
    ਪੂਰਨ floatn_nx_idx;
    /* For _BitInt(N) this stores the N.  */
    ਪੂਰਨ bitint_prec;
  } u;
  /* The storage class specifier, or csc_none if none.  */
  ਗਿਣਤੀ c_storage_class storage_class;
  /* Any type specifier keyword used such as "int", not reflecting
     modifiers such as "short", or cts_none if none.  */
  ਗਿਣਤੀ c_typespec_keyword typespec_ਸ਼ਬਦ : 8;
  /* The kind of type specifier if one has been seen, ctsk_none
     otherwise.  */
  ਗਿਣਤੀ c_typespec_ਕਿਸਮ typespec_ਕਿਸਮ : 4;
  ਗਿਣਤੀ c_declspec_il declspec_il : 3;
  /* Whether any expressions in typeof specifiers may appear in
     constant expressions.  */
  bool ਵਿਅੰਜਕ_const_operands : 1;
  /* Whether any declaration specifiers have been seen at all.  */
  bool declspecs_ਵੇਖਿਆ_p : 1;
  /* Whether any declaration specifiers other than standard attributes
     have been seen at all.  If only standard attributes have been
     seen, this is an attribute-declaration.  */
  bool non_std_attrs_ਵੇਖਿਆ_p : 1;
  /* Whether something other than a storage class specifier or
     attribute has been seen.  This is used to warn for the
     obsolescent usage of storage class specifiers other than at the
     start of the list.  (Doing this properly would require function
     specifiers to be handled separately from storage class
     specifiers.)  */
  bool non_sc_ਵੇਖਿਆ_p : 1;
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
  addr_space_t ਪਤਾ_space;
};

/* The various kinds of declarators in C.  */
ਗਿਣਤੀ c_declarator_ਕਿਸਮ {
  /* An identifier.  */
  cdk_id,
  /* A function.  */
  cdk_function,
  /* An array.  */
  cdk_array,
  /* A pointer.  */
  cdk_ਸੂਚਕ,
  /* Parenthesized declarator with nested attributes.  */
  cdk_attrs
};

ਬਣਤਰ c_arg_ਟੈਗ {
  /* The argument name.  */
  ਰੁੱਖ id;
  /* The type of the argument.  */
  ਰੁੱਖ type;
};


/* Information about the parameters in a function declarator.  */
ਬਣਤਰ c_arg_info {
  /* A list of parameter decls.  */
  ਰੁੱਖ parms;
  /* A list of structure, union and enum tags defined.  */
  vec<c_arg_ਟੈਗ, va_gc> *ਟੈਗ_ਸੂਚੀ;
  /* A list of argument types to go in the FUNCTION_TYPE.  */
  ਰੁੱਖ types;
  /* A list of non-parameter decls (notably enumeration constants)
     defined with the parameters.  */
  ਰੁੱਖ others;
  /* A compound expression of VLA sizes from the parameters, or NULL.
     In a function definition, these are used to ensure that
     side-effects in sizes of arrays converted to pointers (such as a
     parameter int i[n++]) take place; otherwise, they are
     ignored.  */
  ਰੁੱਖ pending_sizes;
  /* True when these arguments had [*].  */
  bool had_vla_unspec : 1;
  /* True when the arguments are a (...) prototype.  */
  bool no_named_ਦਲੀਲਾਂ_stdarg_p : 1;
  /* True when empty parentheses have been interpreted as (void) in C23 or
     later.  This is only for use by -Wtraditional and is no longer needed if
     -Wtraditional is removed.  */
  bool c23_ਖਾਲੀ_ਥਾਵਾਂ_parens : 1;
};

/* A declarator.  */
ਬਣਤਰ c_declarator {
  /* The kind of declarator.  */
  ਗਿਣਤੀ c_declarator_ਕਿਸਮ ਕਿਸਮ;
  location_t id_loc; /* Currently only set for cdk_id, cdk_array. */
  /* Except for cdk_id, the contained declarator.  For cdk_id, NULL.  */
  ਬਣਤਰ c_declarator *declarator;
  ਸੰਘ {
    /* For identifiers.  */
    ਬਣਤਰ {
      /* An IDENTIFIER_NODE, or NULL_TREE if an abstract
	 declarator.  */
      ਰੁੱਖ id;
      /* Any attributes (which apply to the declaration rather than to
	 the type described by the outer declarators).  */
      ਰੁੱਖ attrs;
    } id;
    /* For functions.  */
    ਬਣਤਰ c_arg_info *arg_info;
    /* For arrays.  */
    ਬਣਤਰ {
      /* The array dimension, or NULL for [] and [*].  */
      ਰੁੱਖ dimen;
      /* The qualifiers inside [].  */
      ਪੂਰਨ quals;
      /* The attributes (currently ignored) inside [].  */
      ਰੁੱਖ attrs;
      /* Whether [static] was used.  */
      bool static_p : 1;
      /* Whether [*] was used.  */
      bool vla_unspec_p : 1;
    } array;
    /* For pointers, the qualifiers on the pointer type.  */
    ਪੂਰਨ ਸੂਚਕ_quals;
    /* For attributes.  */
    ਰੁੱਖ attrs;
  } u;
};

/* A type name.  */
ਬਣਤਰ c_type_name {
  /* The declaration specifiers.  */
  ਬਣਤਰ c_declspecs *specs;
  /* The declarator.  */
  ਬਣਤਰ c_declarator *declarator;
};

/* A parameter.  */
ਬਣਤਰ c_parm {
  /* The declaration specifiers, minus any prefix attributes.  */
  ਬਣਤਰ c_declspecs *specs;
  /* The attributes.  */
  ਰੁੱਖ attrs;
  /* The declarator.  */
  ਬਣਤਰ c_declarator *declarator;
  /* The location of the parameter.  */
  location_t loc;
};

/* Used when parsing an enum.  Initialized by start_enum.  */
ਬਣਤਰ c_enum_contents
{
  /* While defining an enum type, this is 1 plus the last enumerator
     constant value.  */
  ਰੁੱਖ enum_ਅਗਲਾ_ਮੁੱਲ;

  /* The enumeration type itself.  */
  ਰੁੱਖ enum_type;

  /* Nonzero means that there was overflow computing enum_next_value.  */
  ਪੂਰਨ enum_ਉਛਾਲ;
};

/* A type of reference to a static identifier in an inline
   function.  */
ਗਿਣਤੀ c_inline_static_type {
  /* Identifier with internal linkage used in function that may be an
     inline definition (i.e., file-scope static).  */
  csi_ਅੰਦਰੂਨੀ,
  /* Modifiable object with static storage duration defined in
     function that may be an inline definition (i.e., local
     static).  */
  csi_modifiable
};

/* Record details of decls possibly used inside sizeof or typeof.  */
ਬਣਤਰ maybe_ਵਰਤਿਆ_decl
{
  /* The decl.  */
  ਰੁੱਖ decl;
  /* The level seen at (in_sizeof + in_typeof + in_countof + in_generic).  */
  ਪੂਰਨ level;
  /* Seen in address-of.  */
  bool ਪਤਾ;
  /* The next one at this level or above, or NULL.  */
  ਬਣਤਰ maybe_ਵਰਤਿਆ_decl *ਅਗਲਾ;
};


/* in c-parser.cc */
ਬਣਤਰ c_ਰੁੱਖ_token_vec;
ਬਾਹਰੀ ਖਾਲੀ c_parse_init (ਖਾਲੀ);
ਬਾਹਰੀ bool c_keyword_starts_typename (ਗਿਣਤੀ rid keyword);

/* in c-aux-info.cc */
ਬਾਹਰੀ ਖਾਲੀ gen_aux_info_ਰਿਕਾਰਡ (ਰੁੱਖ, ਪੂਰਨ, ਪੂਰਨ, ਪੂਰਨ);

/* in c-decl.cc */
ਬਣਤਰ c_spot_bindings;
class c_struct_parse_info;
ਬਾਹਰੀ ਬਣਤਰ obstack parser_obstack;
/* Set to IN_ITERATION_STMT if parsing an iteration-statement,
   to IN_OMP_BLOCK if parsing OpenMP structured block and
   IN_OMP_FOR if parsing OpenMP loop.  If parsing a switch statement,
   this is bitwise ORed with IN_SWITCH_STMT, unless parsing an
   iteration-statement, OpenMP block or loop within that switch.
   If the innermost iteration/switch statement is named, IN_NAMED_STMT
   is additionally bitwise ORed into it.  */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਵਿੱਚ_SWITCH_STMT		1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਵਿੱਚ_ITERATION_STMT	2
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਵਿੱਚ_OMP_ਖੰਡ		4
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਵਿੱਚ_OMP_FOR		8
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਵਿੱਚ_OBJC_FOREACH		16
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਵਿੱਚ_NAMED_STMT		32
ਬਾਹਰੀ ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ ਵਿੱਚ_statement;

ਬਾਹਰੀ bool switch_statement_break_ਵੇਖਿਆ_p;

ਬਾਹਰੀ bool global_bindings_p (ਖਾਲੀ);
ਬਾਹਰੀ ਰੁੱਖ pushdecl (ਰੁੱਖ);
ਬਾਹਰੀ ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ਸ਼ੁਰੂ_underspecified_init (location_t, ਰੁੱਖ);
ਬਾਹਰੀ ਖਾਲੀ ਅੰਤ_underspecified_init (ਰੁੱਖ, ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ);
ਬਾਹਰੀ ਖਾਲੀ ਧੱਕੋ_scope (ਖਾਲੀ);
ਬਾਹਰੀ ਰੁੱਖ ਕੱਢੋ_scope (ਖਾਲੀ);
ਬਾਹਰੀ ਖਾਲੀ c_mark_decl_jump_unsafe_ਵਿੱਚ_current_scope ();
ਬਾਹਰੀ ਖਾਲੀ c_bindings_ਸ਼ੁਰੂ_stmt_ਵਿਅੰਜਕ (ਬਣਤਰ c_spot_bindings *);
ਬਾਹਰੀ ਖਾਲੀ c_bindings_ਸਿਰਾ_stmt_ਵਿਅੰਜਕ (ਬਣਤਰ c_spot_bindings *);

ਬਾਹਰੀ ਖਾਲੀ ਰਿਕਾਰਡ_inline_static (location_t, ਰੁੱਖ, ਰੁੱਖ,
				  ਗਿਣਤੀ c_inline_static_type);
ਬਾਹਰੀ ਖਾਲੀ c_init_decl_processing (ਖਾਲੀ);
ਬਾਹਰੀ ਖਾਲੀ c_print_identifier (FILE *, ਰੁੱਖ, ਪੂਰਨ);
ਬਾਹਰੀ ਪੂਰਨ quals_from_declspecs (ਅਚਲ ਬਣਤਰ c_declspecs *);
ਬਾਹਰੀ ਬਣਤਰ c_declarator *build_array_declarator (location_t, ਰੁੱਖ,
    						    ਬਣਤਰ c_declspecs *,
						    bool, bool);
ਬਾਹਰੀ ਰੁੱਖ build_enumerator (location_t, location_t, ਬਣਤਰ c_enum_contents *,
			      ਰੁੱਖ, ਰੁੱਖ);
ਬਾਹਰੀ ਰੁੱਖ check_for_loop_decls (location_t, bool);
ਬਾਹਰੀ ਖਾਲੀ mark_forward_parm_decls (ਖਾਲੀ);
ਬਾਹਰੀ ਖਾਲੀ declare_parm_level (ਖਾਲੀ);
ਬਾਹਰੀ ਖਾਲੀ undeclared_variable (location_t, ਰੁੱਖ);
ਬਾਹਰੀ ਰੁੱਖ lookup_label_for_goto (location_t, ਰੁੱਖ);
ਬਾਹਰੀ ਰੁੱਖ declare_label (ਰੁੱਖ);
ਬਾਹਰੀ ਰੁੱਖ define_label (location_t, ਰੁੱਖ);
ਬਾਹਰੀ ਬਣਤਰ c_spot_bindings *c_get_switch_bindings (ਖਾਲੀ);
ਬਾਹਰੀ ਖਾਲੀ c_release_switch_bindings (ਬਣਤਰ c_spot_bindings *);
ਬਾਹਰੀ bool c_check_switch_jump_warnings (ਬਣਤਰ c_spot_bindings *,
					  location_t, location_t);
ਬਾਹਰੀ ਖਾਲੀ ਅੰਤ_decl (ਰੁੱਖ, location_t, ਰੁੱਖ, ਰੁੱਖ, ਰੁੱਖ);
ਬਾਹਰੀ ਰੁੱਖ ਅੰਤ_enum (ਰੁੱਖ, ਰੁੱਖ, ਰੁੱਖ);
ਬਾਹਰੀ ਖਾਲੀ ਅੰਤ_function (location_t = ਨਿਵੇਸ਼_location);
ਬਾਹਰੀ ਰੁੱਖ ਅੰਤ_struct (location_t, ਰੁੱਖ, ਰੁੱਖ, ਰੁੱਖ,
			   class c_struct_parse_info *,
			   ਰੁੱਖ *ਵਿਅੰਜਕ = ਨਿਰਾ);
ਬਾਹਰੀ ਰੁੱਖ c_simulate_enum_decl (location_t, ਅਚਲ ਅੱਖਰ *,
				  vec<string_int_pair> *);
ਬਾਹਰੀ ਰੁੱਖ c_simulate_ਰਿਕਾਰਡ_decl (location_t, ਅਚਲ ਅੱਖਰ *,
				    array_ਟੁਕੜਾ<ਅਚਲ ਰੁੱਖ>);
ਬਾਹਰੀ ਬਣਤਰ c_arg_info *build_arg_info (ਖਾਲੀ);
ਬਾਹਰੀ ਬਣਤਰ c_arg_info *get_parm_info (bool, ਰੁੱਖ);
ਬਾਹਰੀ ਰੁੱਖ grokfield (location_t, ਬਣਤਰ c_declarator *,
		       ਬਣਤਰ c_declspecs *, ਰੁੱਖ, ਰੁੱਖ *, ਰੁੱਖ *);
ਬਾਹਰੀ ਰੁੱਖ groktypename (ਬਣਤਰ c_type_name *, ਰੁੱਖ *, bool *);
ਬਾਹਰੀ ਰੁੱਖ grokgenassoc (ਬਣਤਰ c_type_name *);
ਬਾਹਰੀ ਰੁੱਖ grokparm (ਅਚਲ ਬਣਤਰ c_parm *, ਰੁੱਖ *);
ਬਾਹਰੀ ਰੁੱਖ implicitly_declare (location_t, ਰੁੱਖ);
ਬਾਹਰੀ ਖਾਲੀ keep_ਅਗਲਾ_level (ਖਾਲੀ);
ਬਾਹਰੀ ਖਾਲੀ pending_xref_error (ਖਾਲੀ);
ਬਾਹਰੀ ਖਾਲੀ c_ਧੱਕੋ_function_context (ਖਾਲੀ);
ਬਾਹਰੀ ਖਾਲੀ c_ਕੱਢੋ_function_context (ਖਾਲੀ);
ਬਾਹਰੀ ਖਾਲੀ ਧੱਕੋ_parm_decl (ਅਚਲ ਬਣਤਰ c_parm *, ਰੁੱਖ *);
ਬਾਹਰੀ ਬਣਤਰ c_declarator *ਸੈੱਟ_array_declarator_inner (ਬਣਤਰ c_declarator *,
							ਬਣਤਰ c_declarator *);
ਬਾਹਰੀ ਰੁੱਖ c_builtin_function (ਰੁੱਖ);
ਬਾਹਰੀ ਰੁੱਖ c_builtin_function_ext_scope (ਰੁੱਖ);
ਬਾਹਰੀ ਰੁੱਖ c_simulate_builtin_function_decl (ਰੁੱਖ);
ਬਾਹਰੀ ਖਾਲੀ c_warn_ਅਣਵਰਤਿਆ_ਗੁਣ (ਰੁੱਖ);
ਬਾਹਰੀ ਰੁੱਖ c_warn_type_ਗੁਣ (ਰੁੱਖ, ਰੁੱਖ);
ਬਾਹਰੀ ਖਾਲੀ shadow_ਟੈਗ (ਅਚਲ ਬਣਤਰ c_declspecs *);
ਬਾਹਰੀ ਖਾਲੀ shadow_ਟੈਗ_warned (ਅਚਲ ਬਣਤਰ c_declspecs *, ਪੂਰਨ);
ਬਾਹਰੀ ਰੁੱਖ ਸ਼ੁਰੂ_enum (location_t, ਬਣਤਰ c_enum_contents *, ਰੁੱਖ, ਰੁੱਖ,
			bool potential_nesting_p);
ਬਾਹਰੀ bool ਸ਼ੁਰੂ_function (ਬਣਤਰ c_declspecs *, ਬਣਤਰ c_declarator *, ਰੁੱਖ);
ਬਾਹਰੀ ਰੁੱਖ ਸ਼ੁਰੂ_decl (ਬਣਤਰ c_declarator *, ਬਣਤਰ c_declspecs *, bool,
			ਰੁੱਖ, bool = true, location_t * = ਨਿਰਾ);
ਬਾਹਰੀ ਰੁੱਖ ਸ਼ੁਰੂ_struct (location_t, ਗਿਣਤੀ ਰੁੱਖ_ਕੋਡ_2, ਰੁੱਖ,
			  class c_struct_parse_info **);
ਬਾਹਰੀ ਖਾਲੀ store_parm_decls (ਖਾਲੀ);
ਬਾਹਰੀ ਖਾਲੀ store_parm_decls_from (ਬਣਤਰ c_arg_info *);
ਬਾਹਰੀ ਖਾਲੀ ਆਰਜ਼ੀ_store_parm_decls (ਰੁੱਖ, ਰੁੱਖ);
ਬਾਹਰੀ ਖਾਲੀ ਆਰਜ਼ੀ_ਕੱਢੋ_parm_decls (ਖਾਲੀ);
ਬਾਹਰੀ ਰੁੱਖ xref_ਟੈਗ (ਗਿਣਤੀ ਰੁੱਖ_ਕੋਡ_2, ਰੁੱਖ);
ਬਾਹਰੀ ਬਣਤਰ c_typespec parser_xref_ਟੈਗ (location_t, ਗਿਣਤੀ ਰੁੱਖ_ਕੋਡ_2, ਰੁੱਖ,
					  bool, ਰੁੱਖ, bool);
ਬਾਹਰੀ ਬਣਤਰ c_parm *build_c_parm (ਬਣਤਰ c_declspecs *, ਰੁੱਖ,
				    ਬਣਤਰ c_declarator *, location_t);
ਬਾਹਰੀ ਬਣਤਰ c_declarator *build_attrs_declarator (ਰੁੱਖ,
						    ਬਣਤਰ c_declarator *);
ਬਾਹਰੀ ਬਣਤਰ c_declarator *build_function_declarator (ਬਣਤਰ c_arg_info *,
						       ਬਣਤਰ c_declarator *);
ਬਾਹਰੀ ਬਣਤਰ c_declarator *build_id_declarator (ਰੁੱਖ);
ਬਾਹਰੀ ਬਣਤਰ c_declarator *make_ਸੂਚਕ_declarator (ਬਣਤਰ c_declspecs *,
						     ਬਣਤਰ c_declarator *);
ਬਾਹਰੀ ਬਣਤਰ c_declspecs *build_null_declspecs (ਖਾਲੀ);
ਬਾਹਰੀ ਬਣਤਰ c_declspecs *declspecs_ਜੋੜੋ_qual (location_t,
					       ਬਣਤਰ c_declspecs *, ਰੁੱਖ);
ਬਾਹਰੀ ਬਣਤਰ c_declspecs *declspecs_ਜੋੜੋ_type (location_t,
					       ਬਣਤਰ c_declspecs *,
					       ਬਣਤਰ c_typespec);
ਬਾਹਰੀ ਬਣਤਰ c_declspecs *declspecs_ਜੋੜੋ_scspec (location_t,
						 ਬਣਤਰ c_declspecs *, ਰੁੱਖ);
ਬਾਹਰੀ ਬਣਤਰ c_declspecs *declspecs_ਜੋੜੋ_attrs (location_t,
						ਬਣਤਰ c_declspecs *, ਰੁੱਖ);
ਬਾਹਰੀ ਬਣਤਰ c_declspecs *declspecs_ਜੋੜੋ_addrspace (location_t,
						    ਬਣਤਰ c_declspecs *,
						    addr_space_t);
ਬਾਹਰੀ ਬਣਤਰ c_declspecs *declspecs_ਜੋੜੋ_alignas (location_t,
						  ਬਣਤਰ c_declspecs *, ਰੁੱਖ);
ਬਾਹਰੀ ਬਣਤਰ c_declspecs *ਅੰਤ_declspecs (ਬਣਤਰ c_declspecs *);
ਬਾਹਰੀ ਮਾਪ_t c_ਰੁੱਖ_ਮਾਪ (ਗਿਣਤੀ ਰੁੱਖ_ਕੋਡ_2);
ਬਾਹਰੀ ਪੂਰਨ c_get_loop_ਨਾਂ (ਰੁੱਖ, bool, ਰੁੱਖ *);
ਬਾਹਰੀ ਖਾਲੀ c_release_loop_ਨਾਂ (ਪੂਰਨ);
ਬਾਹਰੀ ਰੁੱਖ c_ਅੰਤ_bc_name (location_t, ਰੁੱਖ, bool);

/* in c-objc-common.cc */
ਬਾਹਰੀ bool c_objc_common_init (ਖਾਲੀ);
ਬਾਹਰੀ bool c_missing_noreturn_ok_p (ਰੁੱਖ);
ਬਾਹਰੀ bool c_warn_ਅਣਵਰਤਿਆ_global_decl (const_ਰੁੱਖ);
ਬਾਹਰੀ ਖਾਲੀ c_initialize_diagnostics (diagnostics::context *);
ਬਾਹਰੀ bool c_var_mod_p (ਰੁੱਖ x, ਰੁੱਖ fn);
ਬਾਹਰੀ alias_ਸੈੱਟ_type c_get_alias_ਸੈੱਟ (ਰੁੱਖ);
ਬਾਹਰੀ ਪੂਰਨ c_type_dwarf_attribute (const_ਰੁੱਖ, ਪੂਰਨ);
ਬਾਹਰੀ ਰੁੱਖ c_enum_underlying_ਅਧਾਰ_type (const_ਰੁੱਖ);

/* in c-typeck.cc */
ਬਾਹਰੀ ਪੂਰਨ ਵਿੱਚ_alignof;
ਬਾਹਰੀ ਪੂਰਨ ਵਿੱਚ_sizeof;
ਬਾਹਰੀ ਪੂਰਨ ਵਿੱਚ_countof;
ਬਾਹਰੀ ਪੂਰਨ ਵਿੱਚ_typeof;
ਬਾਹਰੀ ਪੂਰਨ ਵਿੱਚ_generic;
ਬਾਹਰੀ bool c_ਵਿੱਚ_omp_for;
ਬਾਹਰੀ bool c_omp_array_section_p;

ਬਾਹਰੀ ਰੁੱਖ c_ਆਖਰੀ_sizeof_arg;
ਬਾਹਰੀ location_t c_ਆਖਰੀ_sizeof_loc;

ਬਾਹਰੀ ਬਣਤਰ c_switch *c_switch_ਢੇਰ;

ਬਾਹਰੀ bool null_ਸੂਚਕ_constant_p (const_ਰੁੱਖ);


ਸਤਰਅੰਦਰ bool
c_type_variably_modified_p (ਰੁੱਖ t)
{
  ਜੇ (error_mark_ਗੰਢ == t)
    ਵਾਪਸ false;
  ਜੇ (C_TYPE_VARIABLY_MODIFIED (t))
    ਵਾਪਸ true;
  ਜੇ (TYPE_STRUCTURAL_EQUALITY_P (t))
    {
      /* The flag may not have been set yet because of incomplete
	 structure or union types completed later.  */
      ਚੋਣ (ਰੁੱਖ_ਕੋਡ (t))
	{
	ਹਾਲਤ ARRAY_TYPE:
	ਹਾਲਤ FUNCTION_TYPE:
	ਹਾਲਤ ਸੂਚਕ_TYPE:
	  /* Recurse.  */
	  ਜੇ (c_type_variably_modified_p (ਰੁੱਖ_TYPE (t)))
	    {
	      C_TYPE_VARIABLY_MODIFIED (t) = 1;
	      ਵਾਪਸ true;
	    }
	  ਰੋਕੋ;
	ਮੂਲ:
	  ਰੋਕੋ;
	}
    }
  ਵਾਪਸ false;
}

ਸਤਰਅੰਦਰ bool
c_type_unspecified_p (ਰੁੱਖ t)
{
  ਵਾਪਸ error_mark_ਗੰਢ != t
	 && C_TYPE_VARIABLE_ਮਾਪ (t) && ਰੁੱਖ_ਕੋਡ (t) == ARRAY_TYPE
	 && TYPE_DOMAIN (t) && TYPE_MAX_ਮੁੱਲ (TYPE_DOMAIN (t))
	 && ਰੁੱਖ_ਕੋਡ (TYPE_MAX_ਮੁੱਲ (TYPE_DOMAIN (t))) == COMPOUND_ਵਿਅੰਜਕ
	 && integer_zerop (ਰੁੱਖ_ਸੰਕਾਰਜ (TYPE_MAX_ਮੁੱਲ (TYPE_DOMAIN (t)), 0))
	 && integer_zerop (ਰੁੱਖ_ਸੰਕਾਰਜ (TYPE_MAX_ਮੁੱਲ (TYPE_DOMAIN (t)), 1));
}

ਬਾਹਰੀ bool zero_ਲੰਮਾਈ_array_type_p (const_ਰੁੱਖ type);
ਬਾਹਰੀ bool char_type_p (ਰੁੱਖ);
ਬਾਹਰੀ ਰੁੱਖ c_type_ਟੈਗ (const_ਰੁੱਖ t);
ਬਾਹਰੀ ਰੁੱਖ c_objc_common_truthvalue_conversion (location_t, ਰੁੱਖ,
						 ਰੁੱਖ = integer_type_ਗੰਢ);
ਬਾਹਰੀ ਰੁੱਖ require_complete_type (location_t, ਰੁੱਖ);
ਬਾਹਰੀ bool same_translation_unit_p (const_ਰੁੱਖ, const_ਰੁੱਖ);
ਬਾਹਰੀ bool comptypes (ਰੁੱਖ, ਰੁੱਖ);
ਬਾਹਰੀ bool comptypes_same_p (ਰੁੱਖ, ਰੁੱਖ);
ਬਾਹਰੀ bool comptypes_equiv_p (ਰੁੱਖ, ਰੁੱਖ);
ਬਾਹਰੀ bool comptypes_check_enum_int (ਰੁੱਖ, ਰੁੱਖ, bool *);
ਬਾਹਰੀ bool c_mark_addressable (ਰੁੱਖ, bool = false, bool = false);
ਬਾਹਰੀ ਖਾਲੀ c_incomplete_type_error (location_t, const_ਰੁੱਖ, const_ਰੁੱਖ);
ਬਾਹਰੀ ਰੁੱਖ c_type_promotes_ਮੰਜ਼ਿਲ (ਰੁੱਖ);
ਬਾਹਰੀ ਬਣਤਰ c_ਵਿਅੰਜਕ default_function_array_conversion (location_t,
							ਬਣਤਰ c_ਵਿਅੰਜਕ);
ਬਾਹਰੀ ਬਣਤਰ c_ਵਿਅੰਜਕ default_function_array_read_conversion (location_t,
							     ਬਣਤਰ c_ਵਿਅੰਜਕ);
ਬਾਹਰੀ ਬਣਤਰ c_ਵਿਅੰਜਕ convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (location_t, ਬਣਤਰ c_ਵਿਅੰਜਕ,
					       bool, bool, bool = false);
ਬਾਹਰੀ ਰੁੱਖ decl_constant_ਮੁੱਲ_1 (ਰੁੱਖ, bool);
ਬਾਹਰੀ ਖਾਲੀ mark_exp_read (ਰੁੱਖ);
ਬਾਹਰੀ ਰੁੱਖ ਸੰਯੁਕਤ_type (ਰੁੱਖ, ਰੁੱਖ);
ਬਾਹਰੀ ਰੁੱਖ lookup_ਖੇਤਰ (const_ਰੁੱਖ, ਰੁੱਖ);
ਬਾਹਰੀ ਰੁੱਖ build_component_ref (location_t, ਰੁੱਖ, ਰੁੱਖ, location_t,
				 location_t);
ਬਾਹਰੀ ਰੁੱਖ handle_counted_by_for_component_ref (location_t, ਰੁੱਖ);
ਬਾਹਰੀ ਰੁੱਖ build_array_ref (location_t, ਰੁੱਖ, ਰੁੱਖ);
ਬਾਹਰੀ ਰੁੱਖ build_omp_array_section (location_t, ਰੁੱਖ, ਰੁੱਖ, ਰੁੱਖ);
ਬਾਹਰੀ ਰੁੱਖ build_external_ref (location_t, ਰੁੱਖ, bool, ਰੁੱਖ *);
ਬਾਹਰੀ ਖਾਲੀ ਕੱਢੋ_maybe_ਵਰਤਿਆ (bool);
ਬਾਹਰੀ ਬਣਤਰ maybe_ਵਰਤਿਆ_decl *save_maybe_ਵਰਤਿਆ ();
ਬਾਹਰੀ ਖਾਲੀ restore_maybe_ਵਰਤਿਆ (ਬਣਤਰ maybe_ਵਰਤਿਆ_decl *);
ਬਾਹਰੀ ਖਾਲੀ mark_decl_ਵਰਤਿਆ (ਰੁੱਖ, bool);
ਬਾਹਰੀ ਬਣਤਰ c_ਵਿਅੰਜਕ c_ਵਿਅੰਜਕ_sizeof_ਵਿਅੰਜਕ (location_t, ਬਣਤਰ c_ਵਿਅੰਜਕ);
ਬਾਹਰੀ ਬਣਤਰ c_ਵਿਅੰਜਕ c_ਵਿਅੰਜਕ_sizeof_type (location_t, ਬਣਤਰ c_type_name *);
ਬਾਹਰੀ ਬਣਤਰ c_ਵਿਅੰਜਕ c_ਵਿਅੰਜਕ_countof_ਵਿਅੰਜਕ (location_t, ਬਣਤਰ c_ਵਿਅੰਜਕ);
ਬਾਹਰੀ ਬਣਤਰ c_ਵਿਅੰਜਕ c_ਵਿਅੰਜਕ_countof_type (location_t loc,
					  ਬਣਤਰ c_type_name *);
ਬਾਹਰੀ ਬਣਤਰ c_ਵਿਅੰਜਕ c_ਵਿਅੰਜਕ_maxof_type (location_t loc, ਬਣਤਰ c_type_name *);
ਬਾਹਰੀ ਬਣਤਰ c_ਵਿਅੰਜਕ c_ਵਿਅੰਜਕ_minof_type (location_t loc, ਬਣਤਰ c_type_name *);
ਬਾਹਰੀ ਬਣਤਰ c_ਵਿਅੰਜਕ parser_build_unary_op (location_t, ਗਿਣਤੀ ਰੁੱਖ_ਕੋਡ_2,
    					    ਬਣਤਰ c_ਵਿਅੰਜਕ);
ਬਾਹਰੀ ਬਣਤਰ c_ਵਿਅੰਜਕ parser_build_ਦੁਆਧਾਰੀ_op (location_t,
    					     ਗਿਣਤੀ ਰੁੱਖ_ਕੋਡ_2, ਬਣਤਰ c_ਵਿਅੰਜਕ,
					     ਬਣਤਰ c_ਵਿਅੰਜਕ, ਰੁੱਖ);
ਬਾਹਰੀ ਰੁੱਖ build_conditional_ਵਿਅੰਜਕ (location_t, ਰੁੱਖ, bool, ਰੁੱਖ, ਰੁੱਖ,
				    location_t, ਰੁੱਖ, ਰੁੱਖ, location_t);
ਬਾਹਰੀ ਰੁੱਖ build_compound_ਵਿਅੰਜਕ (location_t, ਰੁੱਖ, ਰੁੱਖ);
ਬਾਹਰੀ ਰੁੱਖ c_cast_ਵਿਅੰਜਕ (location_t, ਬਣਤਰ c_type_name *, ਰੁੱਖ);
ਬਾਹਰੀ ਰੁੱਖ build_c_cast (location_t, ਰੁੱਖ, ਰੁੱਖ);
ਬਾਹਰੀ ਖਾਲੀ store_init_ਮੁੱਲ (location_t, ਰੁੱਖ, ਰੁੱਖ, ਰੁੱਖ);
ਬਾਹਰੀ ਖਾਲੀ maybe_warn_string_init (location_t, ਰੁੱਖ, ਬਣਤਰ c_ਵਿਅੰਜਕ);
ਬਾਹਰੀ ਖਾਲੀ ਸ਼ੁਰੂ_init (ਰੁੱਖ, ਰੁੱਖ, bool, bool, rich_location *);
ਬਾਹਰੀ ਖਾਲੀ ਅੰਤ_init (ਖਾਲੀ);
ਬਾਹਰੀ ਖਾਲੀ really_ਸ਼ੁਰੂ_incremental_init (ਰੁੱਖ);
ਬਾਹਰੀ ਖਾਲੀ ਅੰਤ_implicit_inits (location_t, ਬਣਤਰ obstack *);
ਬਾਹਰੀ ਖਾਲੀ ਧੱਕੋ_init_level (location_t, ਪੂਰਨ, ਬਣਤਰ obstack *);
ਬਾਹਰੀ ਬਣਤਰ c_ਵਿਅੰਜਕ ਕੱਢੋ_init_level (location_t, ਪੂਰਨ, ਬਣਤਰ obstack *,
				     location_t);
ਬਾਹਰੀ ਖਾਲੀ ਸੈੱਟ_init_ਸੂਚਕਾਂਕ (location_t, ਰੁੱਖ, ਰੁੱਖ, ਬਣਤਰ obstack *);
ਬਾਹਰੀ ਖਾਲੀ ਸੈੱਟ_init_label (location_t, ਰੁੱਖ, location_t, ਬਣਤਰ obstack *);
ਬਿਨਾਨਿਸ਼ਾਨੀ c_maybe_optimize_large_byte_initializer (ਖਾਲੀ);
ਬਾਹਰੀ ਖਾਲੀ process_init_element (location_t, ਬਣਤਰ c_ਵਿਅੰਜਕ, bool,
				  ਬਣਤਰ obstack *);
ਬਾਹਰੀ ਰੁੱਖ build_compound_literal (location_t, ਰੁੱਖ, ਰੁੱਖ, bool,
				    ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ, ਬਣਤਰ c_declspecs *);
ਬਾਹਰੀ ਖਾਲੀ check_compound_literal_type (location_t, ਬਣਤਰ c_type_name *);
ਬਾਹਰੀ ਰੁੱਖ c_ਸ਼ੁਰੂ_switch (location_t, location_t, ਰੁੱਖ, bool, ਰੁੱਖ);
ਬਾਹਰੀ ਖਾਲੀ c_ਅੰਤ_switch (ਰੁੱਖ, ਰੁੱਖ);
ਬਾਹਰੀ ਰੁੱਖ build_asm_ਵਿਅੰਜਕ (location_t, ਰੁੱਖ, ਰੁੱਖ, ਰੁੱਖ, ਰੁੱਖ, ਰੁੱਖ, bool,
			    bool);
ਬਾਹਰੀ ਰੁੱਖ build_asm_stmt (bool, ਰੁੱਖ);
ਬਾਹਰੀ ਪੂਰਨ c_types_compatible_p (ਰੁੱਖ, ਰੁੱਖ);
ਬਾਹਰੀ ਰੁੱਖ c_begin_compound_stmt (bool);
ਬਾਹਰੀ ਰੁੱਖ c_ਸਿਰਾ_compound_stmt (location_t, ਰੁੱਖ, bool);
ਬਾਹਰੀ ਖਾਲੀ c_ਅੰਤ_if_stmt (location_t, ਰੁੱਖ, ਰੁੱਖ, ਰੁੱਖ);
ਬਾਹਰੀ ਖਾਲੀ c_ਅੰਤ_loop (location_t, location_t, ਰੁੱਖ, location_t, ਰੁੱਖ,
			   ਰੁੱਖ, ਰੁੱਖ, ਰੁੱਖ, bool);
ਬਾਹਰੀ ਰੁੱਖ c_begin_stmt_ਵਿਅੰਜਕ (ਖਾਲੀ);
ਬਾਹਰੀ ਰੁੱਖ c_ਅੰਤ_stmt_ਵਿਅੰਜਕ (location_t, ਰੁੱਖ);
ਬਾਹਰੀ ਰੁੱਖ c_process_ਵਿਅੰਜਕ_stmt (location_t, ਰੁੱਖ);
ਬਾਹਰੀ ਰੁੱਖ c_ਅੰਤ_ਵਿਅੰਜਕ_stmt (location_t, ਰੁੱਖ);
ਬਾਹਰੀ ਰੁੱਖ c_ਅੰਤ_return (location_t, ਰੁੱਖ, ਰੁੱਖ, bool = false);
ਬਾਹਰੀ ਰੁੱਖ c_ਅੰਤ_bc_stmt (location_t, ਰੁੱਖ, bool, ਰੁੱਖ);
ਬਾਹਰੀ ਰੁੱਖ c_ਅੰਤ_goto_label (location_t, ਰੁੱਖ);
ਬਾਹਰੀ ਰੁੱਖ c_ਅੰਤ_goto_ptr (location_t, c_ਵਿਅੰਜਕ val);
ਬਾਹਰੀ ਰੁੱਖ c_ਵਿਅੰਜਕ_ਮੰਜ਼ਿਲ_decl (ਰੁੱਖ, bool *, bool *);
ਬਾਹਰੀ ਰੁੱਖ c_ਅੰਤ_omp_construct (location_t, ਗਿਣਤੀ ਰੁੱਖ_ਕੋਡ_2, ਰੁੱਖ, ਰੁੱਖ);
ਬਾਹਰੀ ਰੁੱਖ c_ਅੰਤ_oacc_ਅੰਕੜੇ (location_t, ਰੁੱਖ, ਰੁੱਖ);
ਬਾਹਰੀ ਰੁੱਖ c_ਅੰਤ_oacc_host_ਅੰਕੜੇ (location_t, ਰੁੱਖ, ਰੁੱਖ);
ਬਾਹਰੀ ਰੁੱਖ c_begin_omp_parallel (ਖਾਲੀ);
ਬਾਹਰੀ ਰੁੱਖ c_ਅੰਤ_omp_parallel (location_t, ਰੁੱਖ, ਰੁੱਖ);
ਬਾਹਰੀ ਰੁੱਖ c_begin_omp_task (ਖਾਲੀ);
ਬਾਹਰੀ ਰੁੱਖ c_ਅੰਤ_omp_task (location_t, ਰੁੱਖ, ਰੁੱਖ);
ਬਾਹਰੀ ਖਾਲੀ c_ਅੰਤ_omp_cancel (location_t, ਰੁੱਖ);
ਬਾਹਰੀ ਖਾਲੀ c_ਅੰਤ_omp_cancellation_ਬਿੰਦੂ (location_t, ਰੁੱਖ);
ਬਾਹਰੀ ਰੁੱਖ c_ਅੰਤ_omp_clauses (ਰੁੱਖ, ਗਿਣਤੀ c_omp_region_type);
ਬਾਹਰੀ ਰੁੱਖ c_omp_ਅੰਤ_mapper_clauses (ਰੁੱਖ);
ਬਾਹਰੀ ਰੁੱਖ c_omp_mapper_lookup (ਰੁੱਖ, ਰੁੱਖ);
ਬਾਹਰੀ ਰੁੱਖ c_omp_ਕੱਢੋ_mapper_directive (ਰੁੱਖ);
ਬਾਹਰੀ ਰੁੱਖ c_omp_map_array_section (location_t, ਰੁੱਖ);
ਬਾਹਰੀ ਰੁੱਖ c_build_va_arg (location_t, ਰੁੱਖ, location_t, ਰੁੱਖ, ਰੁੱਖ);
ਬਾਹਰੀ ਰੁੱਖ c_ਅੰਤ_transaction (location_t, ਰੁੱਖ, ਪੂਰਨ);
ਬਾਹਰੀ bool c_ਰੁੱਖ_equal (ਰੁੱਖ, ਰੁੱਖ);
ਬਾਹਰੀ ਰੁੱਖ c_build_function_call_vec (location_t, ਅਚਲ vec<location_t>&,
				       ਰੁੱਖ, vec<ਰੁੱਖ, va_gc> *,
				       vec<ਰੁੱਖ, va_gc> *);
ਬਾਹਰੀ ਰੁੱਖ c_omp_clause_copy_ctor (ਰੁੱਖ, ਰੁੱਖ, ਰੁੱਖ);
ਬਾਹਰੀ ਰੁੱਖ c_reconstruct_complex_type (ਰੁੱਖ, ਰੁੱਖ);
ਬਾਹਰੀ ਰੁੱਖ c_type_canonical (ਰੁੱਖ);
ਬਾਹਰੀ ਰੁੱਖ c_build_type_attribute_variant (ਰੁੱਖ ntype, ਰੁੱਖ attrs);
ਬਾਹਰੀ ਰੁੱਖ c_build_ਸੂਚਕ_type (ਰੁੱਖ type);
ਬਾਹਰੀ ਰੁੱਖ c_build_array_type (ਰੁੱਖ type, ਰੁੱਖ domain);
ਬਾਹਰੀ ਰੁੱਖ c_build_array_type_unspecified (ਰੁੱਖ type);
ਬਾਹਰੀ ਰੁੱਖ c_build_array_type_zero_ਮਾਪ (ਰੁੱਖ type);
ਬਾਹਰੀ ਰੁੱਖ c_build_function_type (ਰੁੱਖ type, ਰੁੱਖ ਦਲੀਲਾਂ, bool no = false);
ਬਾਹਰੀ ਰੁੱਖ c_build_ਸੂਚਕ_type_for_ਬਹੁਲਕ (ਰੁੱਖ type, machine_ਬਹੁਲਕ ਬਹੁਲਕ, bool m);

/* Set to 0 at beginning of a function definition, set to 1 if
   a return statement that specifies a return value is seen.  */

ਬਾਹਰੀ ਪੂਰਨ current_function_returns_ਮੁੱਲ;

/* Set to 0 at beginning of a function definition, set to 1 if
   a return statement with no argument is seen.  */

ਬਾਹਰੀ ਪੂਰਨ current_function_returns_null;

/* Set to 0 at beginning of a function definition, set to 1 if
   a call to a noreturn function is seen.  */

ਬਾਹਰੀ ਪੂਰਨ current_function_returns_abnormally;

/* In c-decl.cc */

/* Tell the binding oracle what kind of binding we are looking for.  */

ਗਿਣਤੀ c_oracle_request
{
  C_ORACLE_ਚਿੰਨ੍ਹ,
  C_ORACLE_ਟੈਗ,
  C_ORACLE_LABEL
};

/* If this is non-NULL, then it is a "binding oracle" which can lazily
   create bindings when needed by the C compiler.  The oracle is told
   the name and type of the binding to create.  It can call pushdecl
   or the like to ensure the binding is visible; or do nothing,
   leaving the binding untouched.  c-decl.cc takes note of when the
   oracle has been called and will not call it again if it fails to
   create a given binding.  */

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ c_binding_oracle_function (ਗਿਣਤੀ c_oracle_request, ਰੁੱਖ identifier);

ਬਾਹਰੀ c_binding_oracle_function *c_binding_oracle;

ਬਾਹਰੀ ਖਾਲੀ c_ਅੰਤ_incomplete_decl (ਰੁੱਖ);
ਬਾਹਰੀ ਰੁੱਖ c_omp_reduction_id (ਗਿਣਤੀ ਰੁੱਖ_ਕੋਡ_2, ਰੁੱਖ);
ਬਾਹਰੀ ਰੁੱਖ c_omp_reduction_decl (ਰੁੱਖ);
ਬਾਹਰੀ ਰੁੱਖ c_omp_reduction_lookup (ਰੁੱਖ, ਰੁੱਖ);
ਬਾਹਰੀ ਰੁੱਖ c_check_omp_declare_reduction_r (ਰੁੱਖ *, ਪੂਰਨ *, ਖਾਲੀ *);
ਬਾਹਰੀ ਰੁੱਖ c_omp_mapper_id (ਰੁੱਖ);
ਬਾਹਰੀ ਰੁੱਖ c_omp_mapper_decl (ਰੁੱਖ);
ਬਾਹਰੀ ਖਾਲੀ c_omp_ਜਾਂਚ_mapper_bindings (location_t, ਰੁੱਖ *, ਰੁੱਖ);
ਬਾਹਰੀ bool c_check_ਵਿੱਚ_current_scope (ਰੁੱਖ);
ਬਾਹਰੀ ਖਾਲੀ c_pushtag (location_t, ਰੁੱਖ, ਰੁੱਖ);
ਬਾਹਰੀ ਖਾਲੀ c_bind (location_t, ਰੁੱਖ, bool);
ਬਾਹਰੀ bool ਟੈਗ_exists_p (ਗਿਣਤੀ ਰੁੱਖ_ਕੋਡ_2, ਰੁੱਖ);

ਬਾਹਰੀ ਖਾਲੀ verify_counted_by_for_ਸਿਖਰ_anonymous_type (ਰੁੱਖ);

/* In c-errors.cc */
ਬਾਹਰੀ bool pedwarn_c90 (location_t, diagnostics::option_id, ਅਚਲ ਅੱਖਰ *, ...)
    ATTRIBUTE_GCC_DIAG(3,4);
ਬਾਹਰੀ bool pedwarn_c99 (location_t, diagnostics::option_id, ਅਚਲ ਅੱਖਰ *, ...)
    ATTRIBUTE_GCC_DIAG(3,4);
ਬਾਹਰੀ bool pedwarn_c11 (location_t, diagnostics::option_id, ਅਚਲ ਅੱਖਰ *, ...)
    ATTRIBUTE_GCC_DIAG(3,4);
ਬਾਹਰੀ bool pedwarn_c23 (location_t, diagnostics::option_id, ਅਚਲ ਅੱਖਰ *, ...)
    ATTRIBUTE_GCC_DIAG(3,4);
ਬਾਹਰੀ ਖਾਲੀ ਜੋੜੋ_note_about_new_keyword (location_t loc,
					ਰੁੱਖ keyword_id);

ਬਾਹਰੀ ਖਾਲੀ
ਸੈੱਟ_c_ਵਿਅੰਜਕ_ਸਰੋਤ_range (c_ਵਿਅੰਜਕ *ਵਿਅੰਜਕ,
			 location_t ਸ਼ੁਰੂ, location_t ਅੰਤ);

ਬਾਹਰੀ ਖਾਲੀ
ਸੈੱਟ_c_ਵਿਅੰਜਕ_ਸਰੋਤ_range (c_ਵਿਅੰਜਕ *ਵਿਅੰਜਕ,
			 ਸਰੋਤ_range src_range);

/* In c-fold.cc */
ਬਾਹਰੀ vec<ਰੁੱਖ> incomplete_ਰਿਕਾਰਡ_decls;

ਬਾਹਰੀ ਅਚਲ ਅੱਖਰ *c_get_sarif_ਸਰੋਤ_language (ਅਚਲ ਅੱਖਰ *filename);

ਬਾਹਰੀ ਅਚਲ ਬਣਤਰ scoped_attribute_specs std_attribute_ਸਾਰਣੀ;

#ਜੇ CHECKING_P
namespace selftest {
  ਬਾਹਰੀ ਖਾਲੀ ਲੜੀਵਾਰ_c_tests (ਖਾਲੀ);
} // namespace selftest
#ਜੇ_ਅੰਤ /* #if CHECKING_P */


#ਜੇ_ਅੰਤ /* ! GCC_C_TREE_H */
