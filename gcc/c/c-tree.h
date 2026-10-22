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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ GCC_C_ವೃಕ್ಷ_H
#ವ್ಯಾಖ್ಯಾನಿಸು GCC_C_ವೃಕ್ಷ_H

#ಅನ್ತರ್ಭಾವ "c-family/c-common.h"
#ಅನ್ತರ್ಭಾವ "diagnostic.h"

/* struct lang_identifier is private to c-decl.cc, but langhooks.cc needs to
   know how big it is.  This is sanity-checked in c-decl.cc.  */
#ವ್ಯಾಖ್ಯಾನಿಸು C_SIZEOF_STRUCT_LANG_IDENTIFIER \
  (ಗಾತ್ರ (ರಚನೆ c_common_identifier) + 3 * ಗಾತ್ರ (ಶೂನ್ಯ *))

/* In a RECORD_TYPE or UNION_TYPE, nonzero if any component is read-only.  */
#ವ್ಯಾಖ್ಯಾನಿಸು C_TYPE_FIELDS_READONLY(TYPE) ವೃಕ್ಷ_LANG_FLAG_1 (TYPE)

/* In a RECORD_TYPE or UNION_TYPE, nonzero if any component is volatile.  */
#ವ್ಯಾಖ್ಯಾನಿಸು C_TYPE_FIELDS_VOLATILE(TYPE) ವೃಕ್ಷ_LANG_FLAG_2 (TYPE)

/* In a RECORD_TYPE or UNION_TYPE, nonzero if any component is
   volatile, restrict-qualified or atomic; that is, has a type not
   permitted for a constexpr object.  */
#ವ್ಯಾಖ್ಯಾನಿಸು C_TYPE_FIELDS_NON_CONSTEXPR(TYPE) ವೃಕ್ಷ_LANG_FLAG_4 (TYPE)

/* In a RECORD_TYPE or UNION_TYPE, nonzero if any component has a
   counted_by attribute.  */
#ವ್ಯಾಖ್ಯಾನಿಸು C_TYPE_FIELDS_HAS_COUNTED_BY(TYPE) TYPE_LANG_FLAG_3 (TYPE)

/* In a RECORD_TYPE or UNION_TYPE or ENUMERAL_TYPE
   nonzero if the definition of the type has already started.  */
#ವ್ಯಾಖ್ಯಾನಿಸು C_TYPE_BEING_DEFINED(TYPE) TYPE_LANG_FLAG_0 (TYPE)

/* In an incomplete RECORD_TYPE, UNION_TYPE or ENUMERAL_TYPE, a list of
   variable declarations whose type would be completed by completing
   that type.  */
#ವ್ಯಾಖ್ಯಾನಿಸು C_TYPE_INCOMPLETE_VARS(TYPE) \
  TYPE_LANG_ಸ್ಥಾನ_1 (ವೃಕ್ಷ_CHECK4 (TYPE, ದಾಖಲೆ_TYPE, UNION_TYPE, \
				 QUAL_UNION_TYPE, ENUMERAL_TYPE))

/* In an IDENTIFIER_NODE, nonzero if this identifier is actually a
   keyword.  C_RID_CODE (node) is then the RID_* value of the keyword.  */
#ವ್ಯಾಖ್ಯಾನಿಸು C_IS_RESERVED_ಶಬ್ದ(ID) ವೃಕ್ಷ_LANG_FLAG_0 (ID)

/* Record whether a type or decl was written with nonconstant size.
   Note that TYPE_SIZE may have simplified to a constant.  */
#ವ್ಯಾಖ್ಯಾನಿಸು C_TYPE_VARIABLE_ಗಾತ್ರ(TYPE) TYPE_LANG_FLAG_1 (TYPE)
#ವ್ಯಾಖ್ಯಾನಿಸು C_DECL_VARIABLE_ಗಾತ್ರ(TYPE) DECL_LANG_FLAG_0 (TYPE)

/* Record whether a type is variably modified. */
#ವ್ಯಾಖ್ಯಾನಿಸು C_TYPE_VARIABLY_MODIFIED(TYPE) TYPE_LANG_FLAG_6 (TYPE)


/* Record whether a type is defined inside a struct or union type.
   This is used for -Wc++-compat. */
#ವ್ಯಾಖ್ಯಾನಿಸು C_TYPE_DEFINED_ಒಳ_STRUCT(TYPE) TYPE_LANG_FLAG_2 (TYPE)

/* Record whether a typedef for type `int' was actually `signed int'.  */
#ವ್ಯಾಖ್ಯಾನಿಸು C_TYPEDEF_EXPLICITLY_SIGNED(EXP) DECL_LANG_FLAG_1 (EXP)

/* For a FUNCTION_DECL, nonzero if it was defined without an explicit
   return type.  */
#ವ್ಯಾಖ್ಯಾನಿಸು C_FUNCTION_IMPLICIT_INT(EXP) DECL_LANG_FLAG_1 (EXP)

/* For a FUNCTION_DECL, nonzero if it was an implicit declaration.  */
#ವ್ಯಾಖ್ಯಾನಿಸು C_DECL_IMPLICIT(EXP) DECL_LANG_FLAG_2 (EXP)

/* For a PARM_DECL, nonzero if it was declared as an array.  */
#ವ್ಯಾಖ್ಯಾನಿಸು C_ARRAY_PARAMETER(ಗಂಟು_2) DECL_LANG_FLAG_0 (ಗಂಟು_2)

/* For FUNCTION_DECLs, evaluates true if the decl is a nested
   function that requires a non-local context.  */
#ವ್ಯಾಖ್ಯಾನಿಸು C_FUNC_NONLOCAL_CONTEXT(EXP)		\
  DECL_LANG_FLAG_4 (FUNCTION_DECL_CHECK (EXP))

/* For FUNCTION_DECLs, evaluates true if the decl is built-in but has
   been declared.  */
#ವ್ಯಾಖ್ಯಾನಿಸು C_DECL_DECLARED_BUILTIN(EXP)		\
  DECL_LANG_FLAG_3 (FUNCTION_DECL_CHECK (EXP))

/* For FUNCTION_DECLs, evaluates true if the decl is built-in, has a
   built-in prototype and does not have a non-built-in prototype.  */
#ವ್ಯಾಖ್ಯಾನಿಸು C_DECL_BUILTIN_PROTOTYPE(EXP)		\
  DECL_LANG_FLAG_6 (FUNCTION_DECL_CHECK (EXP))

/* For LABEL_DECLs marks canonical name of a loop.  */
#ವ್ಯಾಖ್ಯಾನಿಸು C_DECL_LOOP_NAME(EXP) DECL_LANG_FLAG_3 (LABEL_DECL_CHECK (EXP))

/* For LABEL_DECLs marks canonical name of a switch.  During parsing of
   ObjC foreach named loop both C_DECL_LOOP_NAME and C_DECL_SWITCH_NAME
   are temporarily set.  */
#ವ್ಯಾಖ್ಯಾನಿಸು C_DECL_SWITCH_NAME(EXP) DECL_LANG_FLAG_5 (LABEL_DECL_CHECK (EXP))

/* For LABEL_DECLs marks canonical name of a loop or switch being
   valid for use in break identifier or continue identifier statements.  */
#ವ್ಯಾಖ್ಯಾನಿಸು C_DECL_LOOP_SWITCH_NAME_VALID(EXP) \
  DECL_LANG_FLAG_6 (LABEL_DECL_CHECK (EXP))

/* For LABEL_DECLs marks canonical loop or switch names which were actually
   used in one or more break identifier or continue identifier statements.  */
#ವ್ಯಾಖ್ಯಾನಿಸು C_DECL_LOOP_SWITCH_NAME_ಬಳಸಿದ(EXP) \
  DECL_LANG_FLAG_8 (LABEL_DECL_CHECK (EXP))

/* Record whether a decl was declared register.  This is strictly a
   front-end flag, whereas DECL_REGISTER is used for code generation;
   they may differ for structures with volatile fields.  */
#ವ್ಯಾಖ್ಯಾನಿಸು C_DECL_ರಿಜಿಸ್ಟರ್(EXP) \
  DECL_LANG_FLAG_4 (ವೃಕ್ಷ_NOT_CHECK (EXP, FUNCTION_DECL))

/* Record whether a decl was used in an expression anywhere except an
   unevaluated operand of sizeof / typeof / alignof.  This is only
   used for functions declared static but not defined, though outside
   sizeof and typeof it is set for other function decls as well.  */
#ವ್ಯಾಖ್ಯಾನಿಸು C_DECL_ಬಳಸಿದ(EXP) DECL_LANG_FLAG_5 (FUNCTION_DECL_CHECK (EXP))

/* Record whether a variable has been declared threadprivate by
   #pragma omp threadprivate.  */
#ವ್ಯಾಖ್ಯಾನಿಸು C_DECL_THREADPRIVATE_P(DECL) DECL_LANG_FLAG_3 (VAR_DECL_CHECK (DECL))

/* Set on VAR_DECLs for compound literals.  */
#ವ್ಯಾಖ್ಯಾನಿಸು C_DECL_COMPOUND_LITERAL_P(DECL) \
  DECL_LANG_FLAG_5 (VAR_DECL_CHECK (DECL))

/* Set on decls used as placeholders for a C23 underspecified object
   definition.  */
#ವ್ಯಾಖ್ಯಾನಿಸು C_DECL_UNDERSPECIFIED(DECL) DECL_LANG_FLAG_7 (DECL)

/* Set on VAR_DECLs declared as 'constexpr'.  */
#ವ್ಯಾಖ್ಯಾನಿಸು C_DECL_DECLARED_CONSTEXPR(DECL) \
  DECL_LANG_FLAG_8 (VAR_DECL_CHECK (DECL))

/* Nonzero for a decl which either doesn't exist or isn't a prototype.
   N.B. Could be simplified if all built-in decls had complete prototypes
   (but this is presently difficult because some of them need FILE*).  */
#ವ್ಯಾಖ್ಯಾನಿಸು C_DECL_ISNT_PROTOTYPE(EXP)			\
       (EXP == 0					\
	|| (!prototype_p (ವೃಕ್ಷ_TYPE (EXP))	\
	    && !fndecl_built_ಒಳ_p (EXP)))

/* For FUNCTION_TYPE, a hidden list of types of arguments.  The same as
   TYPE_ARG_TYPES for functions with prototypes, but created for functions
   without prototypes.  */
#ವ್ಯಾಖ್ಯಾನಿಸು TYPE_ACTUAL_ARG_TYPES(ಗಂಟು_2) \
  TYPE_LANG_ಸ್ಥಾನ_1 (FUNCTION_TYPE_CHECK (ಗಂಟು_2))

/* For a CONSTRUCTOR, whether some initializer contains a
   subexpression meaning it is not a constant expression.  */
#ವ್ಯಾಖ್ಯಾನಿಸು CONSTRUCTOR_NON_CONST(ಅಭಿವ್ಯಕ್ತಿ_3) ವೃಕ್ಷ_LANG_FLAG_1 (CONSTRUCTOR_CHECK (ಅಭಿವ್ಯಕ್ತಿ_3))

/* For a SAVE_EXPR, nonzero if the operand of the SAVE_EXPR has already
   been folded.  */
#ವ್ಯಾಖ್ಯಾನಿಸು SAVE_ಅಭಿವ್ಯಕ್ತಿ_FOLDED_P(EXP)	ವೃಕ್ಷ_LANG_FLAG_1 (SAVE_ಅಭಿವ್ಯಕ್ತಿ_CHECK (EXP))

/* Whether a type has boolean semantics: either a boolean type or an
   enumeration type with a boolean type as its underlying type.  */
#ವ್ಯಾಖ್ಯಾನಿಸು C_BOOLEAN_TYPE_P(TYPE)						\
  (ವೃಕ್ಷ_ಸಂಕೇತ (TYPE) == BOOLEAN_TYPE					\
   || (ವೃಕ್ಷ_ಸಂಕೇತ (TYPE) == ENUMERAL_TYPE				\
       && ENUM_UNDERLYING_TYPE (TYPE) != NULL_ವೃಕ್ಷ			\
       && (ವೃಕ್ಷ_ಸಂಕೇತ (ENUM_UNDERLYING_TYPE (TYPE)) == BOOLEAN_TYPE	\
	   || c_hardbool_type_attr (TYPE))))

/* Record parser information about an expression that is irrelevant
   for code generation alongside a tree representing its value.  */
ರಚನೆ c_ಅಭಿವ್ಯಕ್ತಿ
{
  /* The value of the expression.  */
  ವೃಕ್ಷ ಮೌಲ್ಯ;
  /* Record the original unary/binary operator of an expression, which may
     have been changed by fold, STRING_CST for unparenthesized string
     constants, C_MAYBE_CONST_EXPR for __builtin_constant_p calls
     (even if parenthesized), for subexpressions, and for non-constant
     initializers, or ERROR_MARK for other expressions (including
     parenthesized expressions).  */
  ಎಣಿಕೆ ವೃಕ್ಷ_ಸಂಕೇತ_2 original_ಸಂಕೇತ;
  /* If not NULL, the original type of an expression.  This will
     differ from the type of the value field for an enum constant.
     The type of an enum constant is a plain integer type, but this
     field will be the enum type.  */
  ವೃಕ್ಷ original_type;

  /* The source range of this expression.  This is redundant
     for node values that have locations, but not all node kinds
     have locations (e.g. constants, and references to params, locals,
     etc), so we stash a copy here.  */
  ಮೂಲ_range src_range;

  /* True if this was directly from a decimal constant token.  */
  bool m_decimal : 1;

  /* Access to the first and last locations within the source spelling
     of this expression.  */
  location_t get_ಆರಂಭ () ಸ್ಥಿರಾಂಕ { ಹಿಂತಿರುಗಿ src_range.m_ಆರಂಭ; }
  location_t get_ಮುಕ್ತಾಯ () ಸ್ಥಿರಾಂಕ { ಹಿಂತಿರುಗಿ src_range.m_ಮುಕ್ತಾಯ; }

  location_t get_location () ಸ್ಥಿರಾಂಕ
  {
    ಆದರೆ (ಅಭಿವ್ಯಕ್ತಿ_HAS_LOCATION (ಮೌಲ್ಯ))
      ಹಿಂತಿರುಗಿ ಅಭಿವ್ಯಕ್ತಿ_LOCATION (ಮೌಲ್ಯ);
    ಇಲ್ಲದಿದ್ದರೆ
      ಹಿಂತಿರುಗಿ make_location (get_ಆರಂಭ (), get_ಆರಂಭ (), get_ಮುಕ್ತಾಯ ());
  }

  /* Set the value to error_mark_node whilst ensuring that src_range
     and m_decimal are initialized.  */
  ಶೂನ್ಯ ಗಣ_error ()
  {
    ಮೌಲ್ಯ = error_mark_ಗಂಟು;
    src_range.m_ಆರಂಭ = UNKNOWN_LOCATION;
    src_range.m_ಮುಕ್ತಾಯ = UNKNOWN_LOCATION;
    m_decimal = 0;
  }
};

/* Type alias for struct c_expr. This allows to use the structure
   inside the VEC types.  */
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ c_ಅಭಿವ್ಯಕ್ತಿ c_ಅಭಿವ್ಯಕ್ತಿ_t;

/* A kind of type specifier.  Note that this information is currently
   only used to distinguish tag definitions, tag references and typeof
   uses.  */
ಎಣಿಕೆ c_typespec_ಬಗೆ {
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
ರಚನೆ c_typespec {
  /* What kind of type specifier this is.  */
  ಎಣಿಕೆ c_typespec_ಬಗೆ ಬಗೆ;
  /* Whether the expression has operands suitable for use in constant
     expressions.  */
  bool ಅಭಿವ್ಯಕ್ತಿ_const_operands;
  /* Whether the type specifier includes an enum type specifier (that
     is, ": specifier-qualifier-list" in a declaration using
     "enum").  */
  bool has_enum_type_specifier;
  /* The specifier itself.  */
  ವೃಕ್ಷ spec;
  /* An expression to be evaluated before the type specifier, in the
     case of typeof specifiers, or NULL otherwise or if no such
     expression is required for a particular typeof specifier.  In
     particular, when typeof is applied to an expression of variably
     modified type, that expression must be evaluated in order to
     determine array sizes that form part of the type, but the
     expression itself (as opposed to the array sizes) forms no part
     of the type and so needs to be recorded separately.  */
  ವೃಕ್ಷ ಅಭಿವ್ಯಕ್ತಿ;
};

/* A storage class specifier.  */
ಎಣಿಕೆ c_storage_class {
  csc_none,
  csc_auto,
  csc_extern,
  csc_ರಿಜಿಸ್ಟರ್,
  csc_static,
  csc_typedef
};

/* A type specifier keyword "void", "_Bool", "char", "int", "float",
   "double", "_Decimal32", "_Decimal64", "_Decimal128", "_Decimal64x",
   "_Fract", "_Accum", "_BitInt", or none of these.  */
ಎಣಿಕೆ c_typespec_keyword {
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
ಎಣಿಕೆ c_declspec_ಶಬ್ದ {
  cdw_typespec /* A catch-all for a typespec.  */,
  cdw_storage_class  /* A catch-all for a storage class */,
  cdw_ಗುಣಲಕ್ಷಣಗಳು,
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
  cdw_ವಿಳಾಸ_space,
  cdw_gimple,
  cdw_rtl,
  cdw_ಸಂಖ್ಯೆ_ದ_elements /* This one must always be the last
			    enumerator.  */
};

ಎಣಿಕೆ c_declspec_il {
  cdil_none,
  cdil_gimple,		/* __GIMPLE  */
  cdil_gimple_cfg,	/* __GIMPLE(cfg)  */
  cdil_gimple_ssa,	/* __GIMPLE(ssa)  */
  cdil_rtl		/* __RTL  */
};

/* A sequence of declaration specifiers in C.  When a new declaration
   specifier is added, please update the enum c_declspec_word above
   accordingly.  */
ರಚನೆ c_declspecs {
  location_t locations[cdw_ಸಂಖ್ಯೆ_ದ_elements];
  /* The type specified, if a single type specifier such as a struct,
     union or enum specifier, typedef name or typeof specifies the
     whole type, or NULL_TREE if none or a keyword such as "void" or
     "char" is used.  Does not include qualifiers.  */
  ವೃಕ್ಷ type;
  /* Any expression to be evaluated before the type, from a typeof
     specifier.  */
  ವೃಕ್ಷ ಅಭಿವ್ಯಕ್ತಿ;
  /* The attributes from a typedef decl.  */
  ವೃಕ್ಷ decl_attr;
  /* When parsing, the GNU attributes and prefix standard attributes.
     Outside the parser, this will be NULL; attributes (possibly from
     multiple lists) will be passed separately.  */
  ವೃಕ್ಷ attrs;
  /* When parsing, postfix standard attributes (which appertain to the
     type specified by the preceding declaration specifiers, unlike
     prefix standard attributes which appertain to the declaration or
     declarations as a whole).  */
  ವೃಕ್ಷ postfix_attrs;
  /* The pass to start compiling a __GIMPLE or __RTL function with.  */
  ಅಕ್ಷರ *gimple_or_rtl_pass;
  /* ENTRY BB count.  */
  profile_ಎಣಿಕೆ ನಮೂದು_bb_ಎಣಿಕೆ;
  /* The base-2 log of the greatest alignment required by an _Alignas
     specifier, in bytes, or -1 if no such specifiers with nonzero
     alignment.  */
  ಪೂರ್ಣಾಂಕ align_log;
  ಒಕ್ಕೂಟ {
    /* For the __intN declspec, this stores the index into the int_n_*
       arrays.  */
    ಪೂರ್ಣಾಂಕ int_n_idx;
    /* For the _FloatN and _FloatNx declspec, this stores the index into
       the floatn_nx_types array.  */
    ಪೂರ್ಣಾಂಕ floatn_nx_idx;
    /* For _BitInt(N) this stores the N.  */
    ಪೂರ್ಣಾಂಕ bitint_prec;
  } u;
  /* The storage class specifier, or csc_none if none.  */
  ಎಣಿಕೆ c_storage_class storage_class;
  /* Any type specifier keyword used such as "int", not reflecting
     modifiers such as "short", or cts_none if none.  */
  ಎಣಿಕೆ c_typespec_keyword typespec_ಶಬ್ದ : 8;
  /* The kind of type specifier if one has been seen, ctsk_none
     otherwise.  */
  ಎಣಿಕೆ c_typespec_ಬಗೆ typespec_ಬಗೆ : 4;
  ಎಣಿಕೆ c_declspec_il declspec_il : 3;
  /* Whether any expressions in typeof specifiers may appear in
     constant expressions.  */
  bool ಅಭಿವ್ಯಕ್ತಿ_const_operands : 1;
  /* Whether any declaration specifiers have been seen at all.  */
  bool declspecs_ನೋಡಿದ_p : 1;
  /* Whether any declaration specifiers other than standard attributes
     have been seen at all.  If only standard attributes have been
     seen, this is an attribute-declaration.  */
  bool non_std_attrs_ನೋಡಿದ_p : 1;
  /* Whether something other than a storage class specifier or
     attribute has been seen.  This is used to warn for the
     obsolescent usage of storage class specifiers other than at the
     start of the list.  (Doing this properly would require function
     specifiers to be handled separately from storage class
     specifiers.)  */
  bool non_sc_ನೋಡಿದ_p : 1;
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
  addr_space_t ವಿಳಾಸ_space;
};

/* The various kinds of declarators in C.  */
ಎಣಿಕೆ c_declarator_ಬಗೆ {
  /* An identifier.  */
  cdk_id,
  /* A function.  */
  cdk_function,
  /* An array.  */
  cdk_array,
  /* A pointer.  */
  cdk_ಸೂಚಕ,
  /* Parenthesized declarator with nested attributes.  */
  cdk_attrs
};

ರಚನೆ c_arg_ಟ್ಯಾಗ್ {
  /* The argument name.  */
  ವೃಕ್ಷ id;
  /* The type of the argument.  */
  ವೃಕ್ಷ type;
};


/* Information about the parameters in a function declarator.  */
ರಚನೆ c_arg_info {
  /* A list of parameter decls.  */
  ವೃಕ್ಷ parms;
  /* A list of structure, union and enum tags defined.  */
  vec<c_arg_ಟ್ಯಾಗ್, va_gc> *ಟ್ಯಾಗುಗಳು;
  /* A list of argument types to go in the FUNCTION_TYPE.  */
  ವೃಕ್ಷ types;
  /* A list of non-parameter decls (notably enumeration constants)
     defined with the parameters.  */
  ವೃಕ್ಷ others;
  /* A compound expression of VLA sizes from the parameters, or NULL.
     In a function definition, these are used to ensure that
     side-effects in sizes of arrays converted to pointers (such as a
     parameter int i[n++]) take place; otherwise, they are
     ignored.  */
  ವೃಕ್ಷ pending_sizes;
  /* True when these arguments had [*].  */
  bool had_vla_unspec : 1;
  /* True when the arguments are a (...) prototype.  */
  bool no_named_ವಾದಗಳು_stdarg_p : 1;
  /* True when empty parentheses have been interpreted as (void) in C23 or
     later.  This is only for use by -Wtraditional and is no longer needed if
     -Wtraditional is removed.  */
  bool c23_ಖಾಲಿಗಳು_parens : 1;
};

/* A declarator.  */
ರಚನೆ c_declarator {
  /* The kind of declarator.  */
  ಎಣಿಕೆ c_declarator_ಬಗೆ ಬಗೆ;
  location_t id_loc; /* Currently only set for cdk_id, cdk_array. */
  /* Except for cdk_id, the contained declarator.  For cdk_id, NULL.  */
  ರಚನೆ c_declarator *declarator;
  ಒಕ್ಕೂಟ {
    /* For identifiers.  */
    ರಚನೆ {
      /* An IDENTIFIER_NODE, or NULL_TREE if an abstract
	 declarator.  */
      ವೃಕ್ಷ id;
      /* Any attributes (which apply to the declaration rather than to
	 the type described by the outer declarators).  */
      ವೃಕ್ಷ attrs;
    } id;
    /* For functions.  */
    ರಚನೆ c_arg_info *arg_info;
    /* For arrays.  */
    ರಚನೆ {
      /* The array dimension, or NULL for [] and [*].  */
      ವೃಕ್ಷ dimen;
      /* The qualifiers inside [].  */
      ಪೂರ್ಣಾಂಕ quals;
      /* The attributes (currently ignored) inside [].  */
      ವೃಕ್ಷ attrs;
      /* Whether [static] was used.  */
      bool static_p : 1;
      /* Whether [*] was used.  */
      bool vla_unspec_p : 1;
    } array;
    /* For pointers, the qualifiers on the pointer type.  */
    ಪೂರ್ಣಾಂಕ ಸೂಚಕ_quals;
    /* For attributes.  */
    ವೃಕ್ಷ attrs;
  } u;
};

/* A type name.  */
ರಚನೆ c_type_name {
  /* The declaration specifiers.  */
  ರಚನೆ c_declspecs *specs;
  /* The declarator.  */
  ರಚನೆ c_declarator *declarator;
};

/* A parameter.  */
ರಚನೆ c_parm {
  /* The declaration specifiers, minus any prefix attributes.  */
  ರಚನೆ c_declspecs *specs;
  /* The attributes.  */
  ವೃಕ್ಷ attrs;
  /* The declarator.  */
  ರಚನೆ c_declarator *declarator;
  /* The location of the parameter.  */
  location_t loc;
};

/* Used when parsing an enum.  Initialized by start_enum.  */
ರಚನೆ c_enum_contents
{
  /* While defining an enum type, this is 1 plus the last enumerator
     constant value.  */
  ವೃಕ್ಷ enum_ಮುಂದಿನ_ಮೌಲ್ಯ;

  /* The enumeration type itself.  */
  ವೃಕ್ಷ enum_type;

  /* Nonzero means that there was overflow computing enum_next_value.  */
  ಪೂರ್ಣಾಂಕ enum_ಅತಿಪ್ರವಾಹ;
};

/* A type of reference to a static identifier in an inline
   function.  */
ಎಣಿಕೆ c_inline_static_type {
  /* Identifier with internal linkage used in function that may be an
     inline definition (i.e., file-scope static).  */
  csi_ಆಂತರಿಕ,
  /* Modifiable object with static storage duration defined in
     function that may be an inline definition (i.e., local
     static).  */
  csi_modifiable
};

/* Record details of decls possibly used inside sizeof or typeof.  */
ರಚನೆ maybe_ಬಳಸಿದ_decl
{
  /* The decl.  */
  ವೃಕ್ಷ decl;
  /* The level seen at (in_sizeof + in_typeof + in_countof + in_generic).  */
  ಪೂರ್ಣಾಂಕ level;
  /* Seen in address-of.  */
  bool ವಿಳಾಸ;
  /* The next one at this level or above, or NULL.  */
  ರಚನೆ maybe_ಬಳಸಿದ_decl *ಮುಂದಿನ;
};


/* in c-parser.cc */
ರಚನೆ c_ವೃಕ್ಷ_token_vec;
ಬಾಹ್ಯ ಶೂನ್ಯ c_parse_init (ಶೂನ್ಯ);
ಬಾಹ್ಯ bool c_keyword_starts_typename (ಎಣಿಕೆ rid keyword);

/* in c-aux-info.cc */
ಬಾಹ್ಯ ಶೂನ್ಯ gen_aux_info_ದಾಖಲೆ (ವೃಕ್ಷ, ಪೂರ್ಣಾಂಕ, ಪೂರ್ಣಾಂಕ, ಪೂರ್ಣಾಂಕ);

/* in c-decl.cc */
ರಚನೆ c_spot_bindings;
class c_struct_parse_info;
ಬಾಹ್ಯ ರಚನೆ obstack parser_obstack;
/* Set to IN_ITERATION_STMT if parsing an iteration-statement,
   to IN_OMP_BLOCK if parsing OpenMP structured block and
   IN_OMP_FOR if parsing OpenMP loop.  If parsing a switch statement,
   this is bitwise ORed with IN_SWITCH_STMT, unless parsing an
   iteration-statement, OpenMP block or loop within that switch.
   If the innermost iteration/switch statement is named, IN_NAMED_STMT
   is additionally bitwise ORed into it.  */
#ವ್ಯಾಖ್ಯಾನಿಸು ಒಳ_SWITCH_STMT		1
#ವ್ಯಾಖ್ಯಾನಿಸು ಒಳ_ITERATION_STMT	2
#ವ್ಯಾಖ್ಯಾನಿಸು ಒಳ_OMP_ಖಂಡ		4
#ವ್ಯಾಖ್ಯಾನಿಸು ಒಳ_OMP_FOR		8
#ವ್ಯಾಖ್ಯಾನಿಸು ಒಳ_OBJC_FOREACH		16
#ವ್ಯಾಖ್ಯಾನಿಸು ಒಳ_NAMED_STMT		32
ಬಾಹ್ಯ ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ ಒಳ_statement;

ಬಾಹ್ಯ bool switch_statement_break_ನೋಡಿದ_p;

ಬಾಹ್ಯ bool global_bindings_p (ಶೂನ್ಯ);
ಬಾಹ್ಯ ವೃಕ್ಷ pushdecl (ವೃಕ್ಷ);
ಬಾಹ್ಯ ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ ಆರಂಭ_underspecified_init (location_t, ವೃಕ್ಷ);
ಬಾಹ್ಯ ಶೂನ್ಯ ಮುಕ್ತಾಯ_underspecified_init (ವೃಕ್ಷ, ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ);
ಬಾಹ್ಯ ಶೂನ್ಯ ತಳ್ಳು_scope (ಶೂನ್ಯ);
ಬಾಹ್ಯ ವೃಕ್ಷ ತೆಗೆ_scope (ಶೂನ್ಯ);
ಬಾಹ್ಯ ಶೂನ್ಯ c_mark_decl_jump_unsafe_ಒಳ_current_scope ();
ಬಾಹ್ಯ ಶೂನ್ಯ c_bindings_ಆರಂಭ_stmt_ಅಭಿವ್ಯಕ್ತಿ (ರಚನೆ c_spot_bindings *);
ಬಾಹ್ಯ ಶೂನ್ಯ c_bindings_ಕೊನೆ_stmt_ಅಭಿವ್ಯಕ್ತಿ (ರಚನೆ c_spot_bindings *);

ಬಾಹ್ಯ ಶೂನ್ಯ ದಾಖಲೆ_inline_static (location_t, ವೃಕ್ಷ, ವೃಕ್ಷ,
				  ಎಣಿಕೆ c_inline_static_type);
ಬಾಹ್ಯ ಶೂನ್ಯ c_init_decl_processing (ಶೂನ್ಯ);
ಬಾಹ್ಯ ಶೂನ್ಯ c_print_identifier (FILE *, ವೃಕ್ಷ, ಪೂರ್ಣಾಂಕ);
ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ quals_from_declspecs (ಸ್ಥಿರಾಂಕ ರಚನೆ c_declspecs *);
ಬಾಹ್ಯ ರಚನೆ c_declarator *build_array_declarator (location_t, ವೃಕ್ಷ,
    						    ರಚನೆ c_declspecs *,
						    bool, bool);
ಬಾಹ್ಯ ವೃಕ್ಷ build_enumerator (location_t, location_t, ರಚನೆ c_enum_contents *,
			      ವೃಕ್ಷ, ವೃಕ್ಷ);
ಬಾಹ್ಯ ವೃಕ್ಷ check_for_loop_decls (location_t, bool);
ಬಾಹ್ಯ ಶೂನ್ಯ mark_forward_parm_decls (ಶೂನ್ಯ);
ಬಾಹ್ಯ ಶೂನ್ಯ declare_parm_level (ಶೂನ್ಯ);
ಬಾಹ್ಯ ಶೂನ್ಯ undeclared_variable (location_t, ವೃಕ್ಷ);
ಬಾಹ್ಯ ವೃಕ್ಷ lookup_label_for_goto (location_t, ವೃಕ್ಷ);
ಬಾಹ್ಯ ವೃಕ್ಷ declare_label (ವೃಕ್ಷ);
ಬಾಹ್ಯ ವೃಕ್ಷ define_label (location_t, ವೃಕ್ಷ);
ಬಾಹ್ಯ ರಚನೆ c_spot_bindings *c_get_switch_bindings (ಶೂನ್ಯ);
ಬಾಹ್ಯ ಶೂನ್ಯ c_release_switch_bindings (ರಚನೆ c_spot_bindings *);
ಬಾಹ್ಯ bool c_check_switch_jump_warnings (ರಚನೆ c_spot_bindings *,
					  location_t, location_t);
ಬಾಹ್ಯ ಶೂನ್ಯ ಮುಕ್ತಾಯ_decl (ವೃಕ್ಷ, location_t, ವೃಕ್ಷ, ವೃಕ್ಷ, ವೃಕ್ಷ);
ಬಾಹ್ಯ ವೃಕ್ಷ ಮುಕ್ತಾಯ_enum (ವೃಕ್ಷ, ವೃಕ್ಷ, ವೃಕ್ಷ);
ಬಾಹ್ಯ ಶೂನ್ಯ ಮುಕ್ತಾಯ_function (location_t = ಒಳಹರಿವು_location);
ಬಾಹ್ಯ ವೃಕ್ಷ ಮುಕ್ತಾಯ_struct (location_t, ವೃಕ್ಷ, ವೃಕ್ಷ, ವೃಕ್ಷ,
			   class c_struct_parse_info *,
			   ವೃಕ್ಷ *ಅಭಿವ್ಯಕ್ತಿ = ಖಾಲಿ);
ಬಾಹ್ಯ ವೃಕ್ಷ c_simulate_enum_decl (location_t, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *,
				  vec<string_int_pair> *);
ಬಾಹ್ಯ ವೃಕ್ಷ c_simulate_ದಾಖಲೆ_decl (location_t, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *,
				    array_ತುಂಡು<ಸ್ಥಿರಾಂಕ ವೃಕ್ಷ>);
ಬಾಹ್ಯ ರಚನೆ c_arg_info *build_arg_info (ಶೂನ್ಯ);
ಬಾಹ್ಯ ರಚನೆ c_arg_info *get_parm_info (bool, ವೃಕ್ಷ);
ಬಾಹ್ಯ ವೃಕ್ಷ grokfield (location_t, ರಚನೆ c_declarator *,
		       ರಚನೆ c_declspecs *, ವೃಕ್ಷ, ವೃಕ್ಷ *, ವೃಕ್ಷ *);
ಬಾಹ್ಯ ವೃಕ್ಷ groktypename (ರಚನೆ c_type_name *, ವೃಕ್ಷ *, bool *);
ಬಾಹ್ಯ ವೃಕ್ಷ grokgenassoc (ರಚನೆ c_type_name *);
ಬಾಹ್ಯ ವೃಕ್ಷ grokparm (ಸ್ಥಿರಾಂಕ ರಚನೆ c_parm *, ವೃಕ್ಷ *);
ಬಾಹ್ಯ ವೃಕ್ಷ implicitly_declare (location_t, ವೃಕ್ಷ);
ಬಾಹ್ಯ ಶೂನ್ಯ keep_ಮುಂದಿನ_level (ಶೂನ್ಯ);
ಬಾಹ್ಯ ಶೂನ್ಯ pending_xref_error (ಶೂನ್ಯ);
ಬಾಹ್ಯ ಶೂನ್ಯ c_ತಳ್ಳು_function_context (ಶೂನ್ಯ);
ಬಾಹ್ಯ ಶೂನ್ಯ c_ತೆಗೆ_function_context (ಶೂನ್ಯ);
ಬಾಹ್ಯ ಶೂನ್ಯ ತಳ್ಳು_parm_decl (ಸ್ಥಿರಾಂಕ ರಚನೆ c_parm *, ವೃಕ್ಷ *);
ಬಾಹ್ಯ ರಚನೆ c_declarator *ಗಣ_array_declarator_inner (ರಚನೆ c_declarator *,
							ರಚನೆ c_declarator *);
ಬಾಹ್ಯ ವೃಕ್ಷ c_builtin_function (ವೃಕ್ಷ);
ಬಾಹ್ಯ ವೃಕ್ಷ c_builtin_function_ext_scope (ವೃಕ್ಷ);
ಬಾಹ್ಯ ವೃಕ್ಷ c_simulate_builtin_function_decl (ವೃಕ್ಷ);
ಬಾಹ್ಯ ಶೂನ್ಯ c_warn_ಬಳಸದ_ಗುಣಲಕ್ಷಣಗಳು (ವೃಕ್ಷ);
ಬಾಹ್ಯ ವೃಕ್ಷ c_warn_type_ಗುಣಲಕ್ಷಣಗಳು (ವೃಕ್ಷ, ವೃಕ್ಷ);
ಬಾಹ್ಯ ಶೂನ್ಯ shadow_ಟ್ಯಾಗ್ (ಸ್ಥಿರಾಂಕ ರಚನೆ c_declspecs *);
ಬಾಹ್ಯ ಶೂನ್ಯ shadow_ಟ್ಯಾಗ್_warned (ಸ್ಥಿರಾಂಕ ರಚನೆ c_declspecs *, ಪೂರ್ಣಾಂಕ);
ಬಾಹ್ಯ ವೃಕ್ಷ ಆರಂಭ_enum (location_t, ರಚನೆ c_enum_contents *, ವೃಕ್ಷ, ವೃಕ್ಷ,
			bool potential_nesting_p);
ಬಾಹ್ಯ bool ಆರಂಭ_function (ರಚನೆ c_declspecs *, ರಚನೆ c_declarator *, ವೃಕ್ಷ);
ಬಾಹ್ಯ ವೃಕ್ಷ ಆರಂಭ_decl (ರಚನೆ c_declarator *, ರಚನೆ c_declspecs *, bool,
			ವೃಕ್ಷ, bool = true, location_t * = ಖಾಲಿ);
ಬಾಹ್ಯ ವೃಕ್ಷ ಆರಂಭ_struct (location_t, ಎಣಿಕೆ ವೃಕ್ಷ_ಸಂಕೇತ_2, ವೃಕ್ಷ,
			  class c_struct_parse_info **);
ಬಾಹ್ಯ ಶೂನ್ಯ store_parm_decls (ಶೂನ್ಯ);
ಬಾಹ್ಯ ಶೂನ್ಯ store_parm_decls_from (ರಚನೆ c_arg_info *);
ಬಾಹ್ಯ ಶೂನ್ಯ ತಾತ್ಕಾಲಿಕ_store_parm_decls (ವೃಕ್ಷ, ವೃಕ್ಷ);
ಬಾಹ್ಯ ಶೂನ್ಯ ತಾತ್ಕಾಲಿಕ_ತೆಗೆ_parm_decls (ಶೂನ್ಯ);
ಬಾಹ್ಯ ವೃಕ್ಷ xref_ಟ್ಯಾಗ್ (ಎಣಿಕೆ ವೃಕ್ಷ_ಸಂಕೇತ_2, ವೃಕ್ಷ);
ಬಾಹ್ಯ ರಚನೆ c_typespec parser_xref_ಟ್ಯಾಗ್ (location_t, ಎಣಿಕೆ ವೃಕ್ಷ_ಸಂಕೇತ_2, ವೃಕ್ಷ,
					  bool, ವೃಕ್ಷ, bool);
ಬಾಹ್ಯ ರಚನೆ c_parm *build_c_parm (ರಚನೆ c_declspecs *, ವೃಕ್ಷ,
				    ರಚನೆ c_declarator *, location_t);
ಬಾಹ್ಯ ರಚನೆ c_declarator *build_attrs_declarator (ವೃಕ್ಷ,
						    ರಚನೆ c_declarator *);
ಬಾಹ್ಯ ರಚನೆ c_declarator *build_function_declarator (ರಚನೆ c_arg_info *,
						       ರಚನೆ c_declarator *);
ಬಾಹ್ಯ ರಚನೆ c_declarator *build_id_declarator (ವೃಕ್ಷ);
ಬಾಹ್ಯ ರಚನೆ c_declarator *make_ಸೂಚಕ_declarator (ರಚನೆ c_declspecs *,
						     ರಚನೆ c_declarator *);
ಬಾಹ್ಯ ರಚನೆ c_declspecs *build_null_declspecs (ಶೂನ್ಯ);
ಬಾಹ್ಯ ರಚನೆ c_declspecs *declspecs_ಕೂಡಿಸು_qual (location_t,
					       ರಚನೆ c_declspecs *, ವೃಕ್ಷ);
ಬಾಹ್ಯ ರಚನೆ c_declspecs *declspecs_ಕೂಡಿಸು_type (location_t,
					       ರಚನೆ c_declspecs *,
					       ರಚನೆ c_typespec);
ಬಾಹ್ಯ ರಚನೆ c_declspecs *declspecs_ಕೂಡಿಸು_scspec (location_t,
						 ರಚನೆ c_declspecs *, ವೃಕ್ಷ);
ಬಾಹ್ಯ ರಚನೆ c_declspecs *declspecs_ಕೂಡಿಸು_attrs (location_t,
						ರಚನೆ c_declspecs *, ವೃಕ್ಷ);
ಬಾಹ್ಯ ರಚನೆ c_declspecs *declspecs_ಕೂಡಿಸು_addrspace (location_t,
						    ರಚನೆ c_declspecs *,
						    addr_space_t);
ಬಾಹ್ಯ ರಚನೆ c_declspecs *declspecs_ಕೂಡಿಸು_alignas (location_t,
						  ರಚನೆ c_declspecs *, ವೃಕ್ಷ);
ಬಾಹ್ಯ ರಚನೆ c_declspecs *ಮುಕ್ತಾಯ_declspecs (ರಚನೆ c_declspecs *);
ಬಾಹ್ಯ ಗಾತ್ರ_t c_ವೃಕ್ಷ_ಗಾತ್ರ (ಎಣಿಕೆ ವೃಕ್ಷ_ಸಂಕೇತ_2);
ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ c_get_loop_ಹೆಸರುಗಳು (ವೃಕ್ಷ, bool, ವೃಕ್ಷ *);
ಬಾಹ್ಯ ಶೂನ್ಯ c_release_loop_ಹೆಸರುಗಳು (ಪೂರ್ಣಾಂಕ);
ಬಾಹ್ಯ ವೃಕ್ಷ c_ಮುಕ್ತಾಯ_bc_name (location_t, ವೃಕ್ಷ, bool);

/* in c-objc-common.cc */
ಬಾಹ್ಯ bool c_objc_common_init (ಶೂನ್ಯ);
ಬಾಹ್ಯ bool c_missing_noreturn_ok_p (ವೃಕ್ಷ);
ಬಾಹ್ಯ bool c_warn_ಬಳಸದ_global_decl (const_ವೃಕ್ಷ);
ಬಾಹ್ಯ ಶೂನ್ಯ c_initialize_diagnostics (diagnostics::context *);
ಬಾಹ್ಯ bool c_var_mod_p (ವೃಕ್ಷ x, ವೃಕ್ಷ fn);
ಬಾಹ್ಯ alias_ಗಣ_type c_get_alias_ಗಣ (ವೃಕ್ಷ);
ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ c_type_dwarf_attribute (const_ವೃಕ್ಷ, ಪೂರ್ಣಾಂಕ);
ಬಾಹ್ಯ ವೃಕ್ಷ c_enum_underlying_ತಳ_type (const_ವೃಕ್ಷ);

/* in c-typeck.cc */
ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ ಒಳ_alignof;
ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ ಒಳ_sizeof;
ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ ಒಳ_countof;
ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ ಒಳ_typeof;
ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ ಒಳ_generic;
ಬಾಹ್ಯ bool c_ಒಳ_omp_for;
ಬಾಹ್ಯ bool c_omp_array_section_p;

ಬಾಹ್ಯ ವೃಕ್ಷ c_ಕೊನೆಯ_sizeof_arg;
ಬಾಹ್ಯ location_t c_ಕೊನೆಯ_sizeof_loc;

ಬಾಹ್ಯ ರಚನೆ c_switch *c_switch_ರಾಶಿ;

ಬಾಹ್ಯ bool null_ಸೂಚಕ_constant_p (const_ವೃಕ್ಷ);


ಸಾಲೊಳಗೆ bool
c_type_variably_modified_p (ವೃಕ್ಷ t)
{
  ಆದರೆ (error_mark_ಗಂಟು == t)
    ಹಿಂತಿರುಗಿ false;
  ಆದರೆ (C_TYPE_VARIABLY_MODIFIED (t))
    ಹಿಂತಿರುಗಿ true;
  ಆದರೆ (TYPE_STRUCTURAL_EQUALITY_P (t))
    {
      /* The flag may not have been set yet because of incomplete
	 structure or union types completed later.  */
      ಆಯ್ಕೆ (ವೃಕ್ಷ_ಸಂಕೇತ (t))
	{
	ಸ್ಥಿತಿ ARRAY_TYPE:
	ಸ್ಥಿತಿ FUNCTION_TYPE:
	ಸ್ಥಿತಿ ಸೂಚಕ_TYPE:
	  /* Recurse.  */
	  ಆದರೆ (c_type_variably_modified_p (ವೃಕ್ಷ_TYPE (t)))
	    {
	      C_TYPE_VARIABLY_MODIFIED (t) = 1;
	      ಹಿಂತಿರುಗಿ true;
	    }
	  ನಿಲ್ಲಿಸು;
	ಪೂರ್ವನಿಯೋಜಿತ:
	  ನಿಲ್ಲಿಸು;
	}
    }
  ಹಿಂತಿರುಗಿ false;
}

ಸಾಲೊಳಗೆ bool
c_type_unspecified_p (ವೃಕ್ಷ t)
{
  ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು != t
	 && C_TYPE_VARIABLE_ಗಾತ್ರ (t) && ವೃಕ್ಷ_ಸಂಕೇತ (t) == ARRAY_TYPE
	 && TYPE_DOMAIN (t) && TYPE_MAX_ಮೌಲ್ಯ (TYPE_DOMAIN (t))
	 && ವೃಕ್ಷ_ಸಂಕೇತ (TYPE_MAX_ಮೌಲ್ಯ (TYPE_DOMAIN (t))) == COMPOUND_ಅಭಿವ್ಯಕ್ತಿ
	 && integer_zerop (ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (TYPE_MAX_ಮೌಲ್ಯ (TYPE_DOMAIN (t)), 0))
	 && integer_zerop (ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (TYPE_MAX_ಮೌಲ್ಯ (TYPE_DOMAIN (t)), 1));
}

ಬಾಹ್ಯ bool zero_ಉದ್ದಳತೆ_array_type_p (const_ವೃಕ್ಷ type);
ಬಾಹ್ಯ bool char_type_p (ವೃಕ್ಷ);
ಬಾಹ್ಯ ವೃಕ್ಷ c_type_ಟ್ಯಾಗ್ (const_ವೃಕ್ಷ t);
ಬಾಹ್ಯ ವೃಕ್ಷ c_objc_common_truthvalue_conversion (location_t, ವೃಕ್ಷ,
						 ವೃಕ್ಷ = integer_type_ಗಂಟು);
ಬಾಹ್ಯ ವೃಕ್ಷ require_complete_type (location_t, ವೃಕ್ಷ);
ಬಾಹ್ಯ bool same_translation_unit_p (const_ವೃಕ್ಷ, const_ವೃಕ್ಷ);
ಬಾಹ್ಯ bool comptypes (ವೃಕ್ಷ, ವೃಕ್ಷ);
ಬಾಹ್ಯ bool comptypes_same_p (ವೃಕ್ಷ, ವೃಕ್ಷ);
ಬಾಹ್ಯ bool comptypes_equiv_p (ವೃಕ್ಷ, ವೃಕ್ಷ);
ಬಾಹ್ಯ bool comptypes_check_enum_int (ವೃಕ್ಷ, ವೃಕ್ಷ, bool *);
ಬಾಹ್ಯ bool c_mark_addressable (ವೃಕ್ಷ, bool = false, bool = false);
ಬಾಹ್ಯ ಶೂನ್ಯ c_incomplete_type_error (location_t, const_ವೃಕ್ಷ, const_ವೃಕ್ಷ);
ಬಾಹ್ಯ ವೃಕ್ಷ c_type_promotes_ಗಮ್ಯ (ವೃಕ್ಷ);
ಬಾಹ್ಯ ರಚನೆ c_ಅಭಿವ್ಯಕ್ತಿ default_function_array_conversion (location_t,
							ರಚನೆ c_ಅಭಿವ್ಯಕ್ತಿ);
ಬಾಹ್ಯ ರಚನೆ c_ಅಭಿವ್ಯಕ್ತಿ default_function_array_read_conversion (location_t,
							     ರಚನೆ c_ಅಭಿವ್ಯಕ್ತಿ);
ಬಾಹ್ಯ ರಚನೆ c_ಅಭಿವ್ಯಕ್ತಿ convert_lvalue_ಗಮ್ಯ_rvalue (location_t, ರಚನೆ c_ಅಭಿವ್ಯಕ್ತಿ,
					       bool, bool, bool = false);
ಬಾಹ್ಯ ವೃಕ್ಷ decl_constant_ಮೌಲ್ಯ_1 (ವೃಕ್ಷ, bool);
ಬಾಹ್ಯ ಶೂನ್ಯ mark_exp_read (ವೃಕ್ಷ);
ಬಾಹ್ಯ ವೃಕ್ಷ ಸಂಯುಕ್ತ_type (ವೃಕ್ಷ, ವೃಕ್ಷ);
ಬಾಹ್ಯ ವೃಕ್ಷ lookup_ಕ್ಷೇತ್ರ (const_ವೃಕ್ಷ, ವೃಕ್ಷ);
ಬಾಹ್ಯ ವೃಕ್ಷ build_component_ref (location_t, ವೃಕ್ಷ, ವೃಕ್ಷ, location_t,
				 location_t);
ಬಾಹ್ಯ ವೃಕ್ಷ handle_counted_by_for_component_ref (location_t, ವೃಕ್ಷ);
ಬಾಹ್ಯ ವೃಕ್ಷ build_array_ref (location_t, ವೃಕ್ಷ, ವೃಕ್ಷ);
ಬಾಹ್ಯ ವೃಕ್ಷ build_omp_array_section (location_t, ವೃಕ್ಷ, ವೃಕ್ಷ, ವೃಕ್ಷ);
ಬಾಹ್ಯ ವೃಕ್ಷ build_external_ref (location_t, ವೃಕ್ಷ, bool, ವೃಕ್ಷ *);
ಬಾಹ್ಯ ಶೂನ್ಯ ತೆಗೆ_maybe_ಬಳಸಿದ (bool);
ಬಾಹ್ಯ ರಚನೆ maybe_ಬಳಸಿದ_decl *save_maybe_ಬಳಸಿದ ();
ಬಾಹ್ಯ ಶೂನ್ಯ restore_maybe_ಬಳಸಿದ (ರಚನೆ maybe_ಬಳಸಿದ_decl *);
ಬಾಹ್ಯ ಶೂನ್ಯ mark_decl_ಬಳಸಿದ (ವೃಕ್ಷ, bool);
ಬಾಹ್ಯ ರಚನೆ c_ಅಭಿವ್ಯಕ್ತಿ c_ಅಭಿವ್ಯಕ್ತಿ_sizeof_ಅಭಿವ್ಯಕ್ತಿ (location_t, ರಚನೆ c_ಅಭಿವ್ಯಕ್ತಿ);
ಬಾಹ್ಯ ರಚನೆ c_ಅಭಿವ್ಯಕ್ತಿ c_ಅಭಿವ್ಯಕ್ತಿ_sizeof_type (location_t, ರಚನೆ c_type_name *);
ಬಾಹ್ಯ ರಚನೆ c_ಅಭಿವ್ಯಕ್ತಿ c_ಅಭಿವ್ಯಕ್ತಿ_countof_ಅಭಿವ್ಯಕ್ತಿ (location_t, ರಚನೆ c_ಅಭಿವ್ಯಕ್ತಿ);
ಬಾಹ್ಯ ರಚನೆ c_ಅಭಿವ್ಯಕ್ತಿ c_ಅಭಿವ್ಯಕ್ತಿ_countof_type (location_t loc,
					  ರಚನೆ c_type_name *);
ಬಾಹ್ಯ ರಚನೆ c_ಅಭಿವ್ಯಕ್ತಿ c_ಅಭಿವ್ಯಕ್ತಿ_maxof_type (location_t loc, ರಚನೆ c_type_name *);
ಬಾಹ್ಯ ರಚನೆ c_ಅಭಿವ್ಯಕ್ತಿ c_ಅಭಿವ್ಯಕ್ತಿ_minof_type (location_t loc, ರಚನೆ c_type_name *);
ಬಾಹ್ಯ ರಚನೆ c_ಅಭಿವ್ಯಕ್ತಿ parser_build_unary_op (location_t, ಎಣಿಕೆ ವೃಕ್ಷ_ಸಂಕೇತ_2,
    					    ರಚನೆ c_ಅಭಿವ್ಯಕ್ತಿ);
ಬಾಹ್ಯ ರಚನೆ c_ಅಭಿವ್ಯಕ್ತಿ parser_build_ದ್ವಿಮಾನ_op (location_t,
    					     ಎಣಿಕೆ ವೃಕ್ಷ_ಸಂಕೇತ_2, ರಚನೆ c_ಅಭಿವ್ಯಕ್ತಿ,
					     ರಚನೆ c_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ);
ಬಾಹ್ಯ ವೃಕ್ಷ build_conditional_ಅಭಿವ್ಯಕ್ತಿ (location_t, ವೃಕ್ಷ, bool, ವೃಕ್ಷ, ವೃಕ್ಷ,
				    location_t, ವೃಕ್ಷ, ವೃಕ್ಷ, location_t);
ಬಾಹ್ಯ ವೃಕ್ಷ build_compound_ಅಭಿವ್ಯಕ್ತಿ (location_t, ವೃಕ್ಷ, ವೃಕ್ಷ);
ಬಾಹ್ಯ ವೃಕ್ಷ c_cast_ಅಭಿವ್ಯಕ್ತಿ (location_t, ರಚನೆ c_type_name *, ವೃಕ್ಷ);
ಬಾಹ್ಯ ವೃಕ್ಷ build_c_cast (location_t, ವೃಕ್ಷ, ವೃಕ್ಷ);
ಬಾಹ್ಯ ಶೂನ್ಯ store_init_ಮೌಲ್ಯ (location_t, ವೃಕ್ಷ, ವೃಕ್ಷ, ವೃಕ್ಷ);
ಬಾಹ್ಯ ಶೂನ್ಯ maybe_warn_string_init (location_t, ವೃಕ್ಷ, ರಚನೆ c_ಅಭಿವ್ಯಕ್ತಿ);
ಬಾಹ್ಯ ಶೂನ್ಯ ಆರಂಭ_init (ವೃಕ್ಷ, ವೃಕ್ಷ, bool, bool, rich_location *);
ಬಾಹ್ಯ ಶೂನ್ಯ ಮುಕ್ತಾಯ_init (ಶೂನ್ಯ);
ಬಾಹ್ಯ ಶೂನ್ಯ really_ಆರಂಭ_incremental_init (ವೃಕ್ಷ);
ಬಾಹ್ಯ ಶೂನ್ಯ ಮುಕ್ತಾಯ_implicit_inits (location_t, ರಚನೆ obstack *);
ಬಾಹ್ಯ ಶೂನ್ಯ ತಳ್ಳು_init_level (location_t, ಪೂರ್ಣಾಂಕ, ರಚನೆ obstack *);
ಬಾಹ್ಯ ರಚನೆ c_ಅಭಿವ್ಯಕ್ತಿ ತೆಗೆ_init_level (location_t, ಪೂರ್ಣಾಂಕ, ರಚನೆ obstack *,
				     location_t);
ಬಾಹ್ಯ ಶೂನ್ಯ ಗಣ_init_ಸೂಚ್ಯಂಕ (location_t, ವೃಕ್ಷ, ವೃಕ್ಷ, ರಚನೆ obstack *);
ಬಾಹ್ಯ ಶೂನ್ಯ ಗಣ_init_label (location_t, ವೃಕ್ಷ, location_t, ರಚನೆ obstack *);
ಚಿಹ್ನೆರಹಿತ c_maybe_optimize_large_byte_initializer (ಶೂನ್ಯ);
ಬಾಹ್ಯ ಶೂನ್ಯ process_init_element (location_t, ರಚನೆ c_ಅಭಿವ್ಯಕ್ತಿ, bool,
				  ರಚನೆ obstack *);
ಬಾಹ್ಯ ವೃಕ್ಷ build_compound_literal (location_t, ವೃಕ್ಷ, ವೃಕ್ಷ, bool,
				    ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ, ರಚನೆ c_declspecs *);
ಬಾಹ್ಯ ಶೂನ್ಯ check_compound_literal_type (location_t, ರಚನೆ c_type_name *);
ಬಾಹ್ಯ ವೃಕ್ಷ c_ಆರಂಭ_switch (location_t, location_t, ವೃಕ್ಷ, bool, ವೃಕ್ಷ);
ಬಾಹ್ಯ ಶೂನ್ಯ c_ಮುಕ್ತಾಯ_switch (ವೃಕ್ಷ, ವೃಕ್ಷ);
ಬಾಹ್ಯ ವೃಕ್ಷ build_asm_ಅಭಿವ್ಯಕ್ತಿ (location_t, ವೃಕ್ಷ, ವೃಕ್ಷ, ವೃಕ್ಷ, ವೃಕ್ಷ, ವೃಕ್ಷ, bool,
			    bool);
ಬಾಹ್ಯ ವೃಕ್ಷ build_asm_stmt (bool, ವೃಕ್ಷ);
ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ c_types_compatible_p (ವೃಕ್ಷ, ವೃಕ್ಷ);
ಬಾಹ್ಯ ವೃಕ್ಷ c_begin_compound_stmt (bool);
ಬಾಹ್ಯ ವೃಕ್ಷ c_ಕೊನೆ_compound_stmt (location_t, ವೃಕ್ಷ, bool);
ಬಾಹ್ಯ ಶೂನ್ಯ c_ಮುಕ್ತಾಯ_if_stmt (location_t, ವೃಕ್ಷ, ವೃಕ್ಷ, ವೃಕ್ಷ);
ಬಾಹ್ಯ ಶೂನ್ಯ c_ಮುಕ್ತಾಯ_loop (location_t, location_t, ವೃಕ್ಷ, location_t, ವೃಕ್ಷ,
			   ವೃಕ್ಷ, ವೃಕ್ಷ, ವೃಕ್ಷ, bool);
ಬಾಹ್ಯ ವೃಕ್ಷ c_begin_stmt_ಅಭಿವ್ಯಕ್ತಿ (ಶೂನ್ಯ);
ಬಾಹ್ಯ ವೃಕ್ಷ c_ಮುಕ್ತಾಯ_stmt_ಅಭಿವ್ಯಕ್ತಿ (location_t, ವೃಕ್ಷ);
ಬಾಹ್ಯ ವೃಕ್ಷ c_process_ಅಭಿವ್ಯಕ್ತಿ_stmt (location_t, ವೃಕ್ಷ);
ಬಾಹ್ಯ ವೃಕ್ಷ c_ಮುಕ್ತಾಯ_ಅಭಿವ್ಯಕ್ತಿ_stmt (location_t, ವೃಕ್ಷ);
ಬಾಹ್ಯ ವೃಕ್ಷ c_ಮುಕ್ತಾಯ_return (location_t, ವೃಕ್ಷ, ವೃಕ್ಷ, bool = false);
ಬಾಹ್ಯ ವೃಕ್ಷ c_ಮುಕ್ತಾಯ_bc_stmt (location_t, ವೃಕ್ಷ, bool, ವೃಕ್ಷ);
ಬಾಹ್ಯ ವೃಕ್ಷ c_ಮುಕ್ತಾಯ_goto_label (location_t, ವೃಕ್ಷ);
ಬಾಹ್ಯ ವೃಕ್ಷ c_ಮುಕ್ತಾಯ_goto_ptr (location_t, c_ಅಭಿವ್ಯಕ್ತಿ val);
ಬಾಹ್ಯ ವೃಕ್ಷ c_ಅಭಿವ್ಯಕ್ತಿ_ಗಮ್ಯ_decl (ವೃಕ್ಷ, bool *, bool *);
ಬಾಹ್ಯ ವೃಕ್ಷ c_ಮುಕ್ತಾಯ_omp_construct (location_t, ಎಣಿಕೆ ವೃಕ್ಷ_ಸಂಕೇತ_2, ವೃಕ್ಷ, ವೃಕ್ಷ);
ಬಾಹ್ಯ ವೃಕ್ಷ c_ಮುಕ್ತಾಯ_oacc_ದತ್ತಾಂಶ (location_t, ವೃಕ್ಷ, ವೃಕ್ಷ);
ಬಾಹ್ಯ ವೃಕ್ಷ c_ಮುಕ್ತಾಯ_oacc_host_ದತ್ತಾಂಶ (location_t, ವೃಕ್ಷ, ವೃಕ್ಷ);
ಬಾಹ್ಯ ವೃಕ್ಷ c_begin_omp_parallel (ಶೂನ್ಯ);
ಬಾಹ್ಯ ವೃಕ್ಷ c_ಮುಕ್ತಾಯ_omp_parallel (location_t, ವೃಕ್ಷ, ವೃಕ್ಷ);
ಬಾಹ್ಯ ವೃಕ್ಷ c_begin_omp_task (ಶೂನ್ಯ);
ಬಾಹ್ಯ ವೃಕ್ಷ c_ಮುಕ್ತಾಯ_omp_task (location_t, ವೃಕ್ಷ, ವೃಕ್ಷ);
ಬಾಹ್ಯ ಶೂನ್ಯ c_ಮುಕ್ತಾಯ_omp_cancel (location_t, ವೃಕ್ಷ);
ಬಾಹ್ಯ ಶೂನ್ಯ c_ಮುಕ್ತಾಯ_omp_cancellation_ಬಿಂದು (location_t, ವೃಕ್ಷ);
ಬಾಹ್ಯ ವೃಕ್ಷ c_ಮುಕ್ತಾಯ_omp_clauses (ವೃಕ್ಷ, ಎಣಿಕೆ c_omp_region_type);
ಬಾಹ್ಯ ವೃಕ್ಷ c_omp_ಮುಕ್ತಾಯ_mapper_clauses (ವೃಕ್ಷ);
ಬಾಹ್ಯ ವೃಕ್ಷ c_omp_mapper_lookup (ವೃಕ್ಷ, ವೃಕ್ಷ);
ಬಾಹ್ಯ ವೃಕ್ಷ c_omp_ಹೊರತೆಗೆ_mapper_directive (ವೃಕ್ಷ);
ಬಾಹ್ಯ ವೃಕ್ಷ c_omp_map_array_section (location_t, ವೃಕ್ಷ);
ಬಾಹ್ಯ ವೃಕ್ಷ c_build_va_arg (location_t, ವೃಕ್ಷ, location_t, ವೃಕ್ಷ, ವೃಕ್ಷ);
ಬಾಹ್ಯ ವೃಕ್ಷ c_ಮುಕ್ತಾಯ_transaction (location_t, ವೃಕ್ಷ, ಪೂರ್ಣಾಂಕ);
ಬಾಹ್ಯ bool c_ವೃಕ್ಷ_equal (ವೃಕ್ಷ, ವೃಕ್ಷ);
ಬಾಹ್ಯ ವೃಕ್ಷ c_build_function_call_vec (location_t, ಸ್ಥಿರಾಂಕ vec<location_t>&,
				       ವೃಕ್ಷ, vec<ವೃಕ್ಷ, va_gc> *,
				       vec<ವೃಕ್ಷ, va_gc> *);
ಬಾಹ್ಯ ವೃಕ್ಷ c_omp_clause_copy_ctor (ವೃಕ್ಷ, ವೃಕ್ಷ, ವೃಕ್ಷ);
ಬಾಹ್ಯ ವೃಕ್ಷ c_reconstruct_complex_type (ವೃಕ್ಷ, ವೃಕ್ಷ);
ಬಾಹ್ಯ ವೃಕ್ಷ c_type_canonical (ವೃಕ್ಷ);
ಬಾಹ್ಯ ವೃಕ್ಷ c_build_type_attribute_variant (ವೃಕ್ಷ ntype, ವೃಕ್ಷ attrs);
ಬಾಹ್ಯ ವೃಕ್ಷ c_build_ಸೂಚಕ_type (ವೃಕ್ಷ type);
ಬಾಹ್ಯ ವೃಕ್ಷ c_build_array_type (ವೃಕ್ಷ type, ವೃಕ್ಷ domain);
ಬಾಹ್ಯ ವೃಕ್ಷ c_build_array_type_unspecified (ವೃಕ್ಷ type);
ಬಾಹ್ಯ ವೃಕ್ಷ c_build_array_type_zero_ಗಾತ್ರ (ವೃಕ್ಷ type);
ಬಾಹ್ಯ ವೃಕ್ಷ c_build_function_type (ವೃಕ್ಷ type, ವೃಕ್ಷ ವಾದಗಳು, bool no = false);
ಬಾಹ್ಯ ವೃಕ್ಷ c_build_ಸೂಚಕ_type_for_ಬಹುಲಕ (ವೃಕ್ಷ type, machine_ಬಹುಲಕ ಬಹುಲಕ, bool m);

/* Set to 0 at beginning of a function definition, set to 1 if
   a return statement that specifies a return value is seen.  */

ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ current_function_returns_ಮೌಲ್ಯ;

/* Set to 0 at beginning of a function definition, set to 1 if
   a return statement with no argument is seen.  */

ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ current_function_returns_null;

/* Set to 0 at beginning of a function definition, set to 1 if
   a call to a noreturn function is seen.  */

ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ current_function_returns_abnormally;

/* In c-decl.cc */

/* Tell the binding oracle what kind of binding we are looking for.  */

ಎಣಿಕೆ c_oracle_request
{
  C_ORACLE_ಚಿಹ್ನೆ,
  C_ORACLE_ಟ್ಯಾಗ್,
  C_ORACLE_LABEL
};

/* If this is non-NULL, then it is a "binding oracle" which can lazily
   create bindings when needed by the C compiler.  The oracle is told
   the name and type of the binding to create.  It can call pushdecl
   or the like to ensure the binding is visible; or do nothing,
   leaving the binding untouched.  c-decl.cc takes note of when the
   oracle has been called and will not call it again if it fails to
   create a given binding.  */

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ c_binding_oracle_function (ಎಣಿಕೆ c_oracle_request, ವೃಕ್ಷ identifier);

ಬಾಹ್ಯ c_binding_oracle_function *c_binding_oracle;

ಬಾಹ್ಯ ಶೂನ್ಯ c_ಮುಕ್ತಾಯ_incomplete_decl (ವೃಕ್ಷ);
ಬಾಹ್ಯ ವೃಕ್ಷ c_omp_reduction_id (ಎಣಿಕೆ ವೃಕ್ಷ_ಸಂಕೇತ_2, ವೃಕ್ಷ);
ಬಾಹ್ಯ ವೃಕ್ಷ c_omp_reduction_decl (ವೃಕ್ಷ);
ಬಾಹ್ಯ ವೃಕ್ಷ c_omp_reduction_lookup (ವೃಕ್ಷ, ವೃಕ್ಷ);
ಬಾಹ್ಯ ವೃಕ್ಷ c_check_omp_declare_reduction_r (ವೃಕ್ಷ *, ಪೂರ್ಣಾಂಕ *, ಶೂನ್ಯ *);
ಬಾಹ್ಯ ವೃಕ್ಷ c_omp_mapper_id (ವೃಕ್ಷ);
ಬಾಹ್ಯ ವೃಕ್ಷ c_omp_mapper_decl (ವೃಕ್ಷ);
ಬಾಹ್ಯ ಶೂನ್ಯ c_omp_ಪರಿಶೀಲನೆ_mapper_bindings (location_t, ವೃಕ್ಷ *, ವೃಕ್ಷ);
ಬಾಹ್ಯ bool c_check_ಒಳ_current_scope (ವೃಕ್ಷ);
ಬಾಹ್ಯ ಶೂನ್ಯ c_pushtag (location_t, ವೃಕ್ಷ, ವೃಕ್ಷ);
ಬಾಹ್ಯ ಶೂನ್ಯ c_bind (location_t, ವೃಕ್ಷ, bool);
ಬಾಹ್ಯ bool ಟ್ಯಾಗ್_exists_p (ಎಣಿಕೆ ವೃಕ್ಷ_ಸಂಕೇತ_2, ವೃಕ್ಷ);

ಬಾಹ್ಯ ಶೂನ್ಯ verify_counted_by_for_ತುದಿ_anonymous_type (ವೃಕ್ಷ);

/* In c-errors.cc */
ಬಾಹ್ಯ bool pedwarn_c90 (location_t, diagnostics::option_id, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *, ...)
    ATTRIBUTE_GCC_DIAG(3,4);
ಬಾಹ್ಯ bool pedwarn_c99 (location_t, diagnostics::option_id, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *, ...)
    ATTRIBUTE_GCC_DIAG(3,4);
ಬಾಹ್ಯ bool pedwarn_c11 (location_t, diagnostics::option_id, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *, ...)
    ATTRIBUTE_GCC_DIAG(3,4);
ಬಾಹ್ಯ bool pedwarn_c23 (location_t, diagnostics::option_id, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *, ...)
    ATTRIBUTE_GCC_DIAG(3,4);
ಬಾಹ್ಯ ಶೂನ್ಯ ಕೂಡಿಸು_note_about_new_keyword (location_t loc,
					ವೃಕ್ಷ keyword_id);

ಬಾಹ್ಯ ಶೂನ್ಯ
ಗಣ_c_ಅಭಿವ್ಯಕ್ತಿ_ಮೂಲ_range (c_ಅಭಿವ್ಯಕ್ತಿ *ಅಭಿವ್ಯಕ್ತಿ,
			 location_t ಆರಂಭ, location_t ಮುಕ್ತಾಯ);

ಬಾಹ್ಯ ಶೂನ್ಯ
ಗಣ_c_ಅಭಿವ್ಯಕ್ತಿ_ಮೂಲ_range (c_ಅಭಿವ್ಯಕ್ತಿ *ಅಭಿವ್ಯಕ್ತಿ,
			 ಮೂಲ_range src_range);

/* In c-fold.cc */
ಬಾಹ್ಯ vec<ವೃಕ್ಷ> incomplete_ದಾಖಲೆ_decls;

ಬಾಹ್ಯ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *c_get_sarif_ಮೂಲ_language (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *filename);

ಬಾಹ್ಯ ಸ್ಥಿರಾಂಕ ರಚನೆ scoped_attribute_specs std_attribute_ಕೋಷ್ಟಕ;

#ಆದರೆ CHECKING_P
namespace selftest {
  ಬಾಹ್ಯ ಶೂನ್ಯ ಸತತ_c_tests (ಶೂನ್ಯ);
} // namespace selftest
#ಆದರೆ_ಅಂತ್ಯ /* #if CHECKING_P */


#ಆದರೆ_ಅಂತ್ಯ /* ! GCC_C_TREE_H */
