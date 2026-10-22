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

#که_نه_تعریف_شوی GCC_C_ونه_H
#تعریف_کړه GCC_C_ونه_H

#ضمن "c-family/c-common.h"
#ضمن "diagnostic.h"

/* struct lang_identifier is private to c-decl.cc, but langhooks.cc needs to
   know how big it is.  This is sanity-checked in c-decl.cc.  */
#تعریف_کړه C_SIZEOF_STRUCT_LANG_IDENTIFIER \
  (حجم (بنية c_common_identifier) + 3 * حجم (فراغ *))

/* In a RECORD_TYPE or UNION_TYPE, nonzero if any component is read-only.  */
#تعریف_کړه C_TYPE_FIELDS_READONLY(TYPE) ونه_LANG_FLAG_1 (TYPE)

/* In a RECORD_TYPE or UNION_TYPE, nonzero if any component is volatile.  */
#تعریف_کړه C_TYPE_FIELDS_VOLATILE(TYPE) ونه_LANG_FLAG_2 (TYPE)

/* In a RECORD_TYPE or UNION_TYPE, nonzero if any component is
   volatile, restrict-qualified or atomic; that is, has a type not
   permitted for a constexpr object.  */
#تعریف_کړه C_TYPE_FIELDS_NON_CONSTEXPR(TYPE) ونه_LANG_FLAG_4 (TYPE)

/* In a RECORD_TYPE or UNION_TYPE, nonzero if any component has a
   counted_by attribute.  */
#تعریف_کړه C_TYPE_FIELDS_HAS_COUNTED_BY(TYPE) TYPE_LANG_FLAG_3 (TYPE)

/* In a RECORD_TYPE or UNION_TYPE or ENUMERAL_TYPE
   nonzero if the definition of the type has already started.  */
#تعریف_کړه C_TYPE_BEING_DEFINED(TYPE) TYPE_LANG_FLAG_0 (TYPE)

/* In an incomplete RECORD_TYPE, UNION_TYPE or ENUMERAL_TYPE, a list of
   variable declarations whose type would be completed by completing
   that type.  */
#تعریف_کړه C_TYPE_INCOMPLETE_VARS(TYPE) \
  TYPE_LANG_خونه_1 (ونه_CHECK4 (TYPE, ریکارډ_TYPE, UNION_TYPE, \
				 QUAL_UNION_TYPE, ENUMERAL_TYPE))

/* In an IDENTIFIER_NODE, nonzero if this identifier is actually a
   keyword.  C_RID_CODE (node) is then the RID_* value of the keyword.  */
#تعریف_کړه C_IS_RESERVED_کلمه(ID) ونه_LANG_FLAG_0 (ID)

/* Record whether a type or decl was written with nonconstant size.
   Note that TYPE_SIZE may have simplified to a constant.  */
#تعریف_کړه C_TYPE_VARIABLE_اندازه(TYPE) TYPE_LANG_FLAG_1 (TYPE)
#تعریف_کړه C_DECL_VARIABLE_اندازه(TYPE) DECL_LANG_FLAG_0 (TYPE)

/* Record whether a type is variably modified. */
#تعریف_کړه C_TYPE_VARIABLY_MODIFIED(TYPE) TYPE_LANG_FLAG_6 (TYPE)


/* Record whether a type is defined inside a struct or union type.
   This is used for -Wc++-compat. */
#تعریف_کړه C_TYPE_DEFINED_دننه_STRUCT(TYPE) TYPE_LANG_FLAG_2 (TYPE)

/* Record whether a typedef for type `int' was actually `signed int'.  */
#تعریف_کړه C_TYPEDEF_EXPLICITLY_SIGNED(EXP) DECL_LANG_FLAG_1 (EXP)

/* For a FUNCTION_DECL, nonzero if it was defined without an explicit
   return type.  */
#تعریف_کړه C_FUNCTION_IMPLICIT_INT(EXP) DECL_LANG_FLAG_1 (EXP)

/* For a FUNCTION_DECL, nonzero if it was an implicit declaration.  */
#تعریف_کړه C_DECL_IMPLICIT(EXP) DECL_LANG_FLAG_2 (EXP)

/* For a PARM_DECL, nonzero if it was declared as an array.  */
#تعریف_کړه C_ARRAY_PARAMETER(غوټه_2) DECL_LANG_FLAG_0 (غوټه_2)

/* For FUNCTION_DECLs, evaluates true if the decl is a nested
   function that requires a non-local context.  */
#تعریف_کړه C_FUNC_NONLOCAL_CONTEXT(EXP)		\
  DECL_LANG_FLAG_4 (FUNCTION_DECL_CHECK (EXP))

/* For FUNCTION_DECLs, evaluates true if the decl is built-in but has
   been declared.  */
#تعریف_کړه C_DECL_DECLARED_BUILTIN(EXP)		\
  DECL_LANG_FLAG_3 (FUNCTION_DECL_CHECK (EXP))

/* For FUNCTION_DECLs, evaluates true if the decl is built-in, has a
   built-in prototype and does not have a non-built-in prototype.  */
#تعریف_کړه C_DECL_BUILTIN_PROTOTYPE(EXP)		\
  DECL_LANG_FLAG_6 (FUNCTION_DECL_CHECK (EXP))

/* For LABEL_DECLs marks canonical name of a loop.  */
#تعریف_کړه C_DECL_LOOP_NAME(EXP) DECL_LANG_FLAG_3 (LABEL_DECL_CHECK (EXP))

/* For LABEL_DECLs marks canonical name of a switch.  During parsing of
   ObjC foreach named loop both C_DECL_LOOP_NAME and C_DECL_SWITCH_NAME
   are temporarily set.  */
#تعریف_کړه C_DECL_SWITCH_NAME(EXP) DECL_LANG_FLAG_5 (LABEL_DECL_CHECK (EXP))

/* For LABEL_DECLs marks canonical name of a loop or switch being
   valid for use in break identifier or continue identifier statements.  */
#تعریف_کړه C_DECL_LOOP_SWITCH_NAME_VALID(EXP) \
  DECL_LANG_FLAG_6 (LABEL_DECL_CHECK (EXP))

/* For LABEL_DECLs marks canonical loop or switch names which were actually
   used in one or more break identifier or continue identifier statements.  */
#تعریف_کړه C_DECL_LOOP_SWITCH_NAME_کارول_شوی(EXP) \
  DECL_LANG_FLAG_8 (LABEL_DECL_CHECK (EXP))

/* Record whether a decl was declared register.  This is strictly a
   front-end flag, whereas DECL_REGISTER is used for code generation;
   they may differ for structures with volatile fields.  */
#تعریف_کړه C_DECL_ثبتوونکی(EXP) \
  DECL_LANG_FLAG_4 (ونه_NOT_CHECK (EXP, FUNCTION_DECL))

/* Record whether a decl was used in an expression anywhere except an
   unevaluated operand of sizeof / typeof / alignof.  This is only
   used for functions declared static but not defined, though outside
   sizeof and typeof it is set for other function decls as well.  */
#تعریف_کړه C_DECL_کارول_شوی(EXP) DECL_LANG_FLAG_5 (FUNCTION_DECL_CHECK (EXP))

/* Record whether a variable has been declared threadprivate by
   #pragma omp threadprivate.  */
#تعریف_کړه C_DECL_THREADPRIVATE_P(DECL) DECL_LANG_FLAG_3 (VAR_DECL_CHECK (DECL))

/* Set on VAR_DECLs for compound literals.  */
#تعریف_کړه C_DECL_COMPOUND_LITERAL_P(DECL) \
  DECL_LANG_FLAG_5 (VAR_DECL_CHECK (DECL))

/* Set on decls used as placeholders for a C23 underspecified object
   definition.  */
#تعریف_کړه C_DECL_UNDERSPECIFIED(DECL) DECL_LANG_FLAG_7 (DECL)

/* Set on VAR_DECLs declared as 'constexpr'.  */
#تعریف_کړه C_DECL_DECLARED_CONSTEXPR(DECL) \
  DECL_LANG_FLAG_8 (VAR_DECL_CHECK (DECL))

/* Nonzero for a decl which either doesn't exist or isn't a prototype.
   N.B. Could be simplified if all built-in decls had complete prototypes
   (but this is presently difficult because some of them need FILE*).  */
#تعریف_کړه C_DECL_ISNT_PROTOTYPE(EXP)			\
       (EXP == 0					\
	|| (!prototype_p (ونه_TYPE (EXP))	\
	    && !fndecl_built_دننه_p (EXP)))

/* For FUNCTION_TYPE, a hidden list of types of arguments.  The same as
   TYPE_ARG_TYPES for functions with prototypes, but created for functions
   without prototypes.  */
#تعریف_کړه TYPE_ACTUAL_ARG_TYPES(غوټه_2) \
  TYPE_LANG_خونه_1 (FUNCTION_TYPE_CHECK (غوټه_2))

/* For a CONSTRUCTOR, whether some initializer contains a
   subexpression meaning it is not a constant expression.  */
#تعریف_کړه CONSTRUCTOR_NON_CONST(بیان_2) ونه_LANG_FLAG_1 (CONSTRUCTOR_CHECK (بیان_2))

/* For a SAVE_EXPR, nonzero if the operand of the SAVE_EXPR has already
   been folded.  */
#تعریف_کړه SAVE_بیان_FOLDED_P(EXP)	ونه_LANG_FLAG_1 (SAVE_بیان_CHECK (EXP))

/* Whether a type has boolean semantics: either a boolean type or an
   enumeration type with a boolean type as its underlying type.  */
#تعریف_کړه C_BOOLEAN_TYPE_P(TYPE)						\
  (ونه_کوډ (TYPE) == BOOLEAN_TYPE					\
   || (ونه_کوډ (TYPE) == ENUMERAL_TYPE				\
       && ENUM_UNDERLYING_TYPE (TYPE) != NULL_ونه			\
       && (ونه_کوډ (ENUM_UNDERLYING_TYPE (TYPE)) == BOOLEAN_TYPE	\
	   || c_hardbool_type_attr (TYPE))))

/* Record parser information about an expression that is irrelevant
   for code generation alongside a tree representing its value.  */
بنية c_بیان
{
  /* The value of the expression.  */
  ونه ارزښت;
  /* Record the original unary/binary operator of an expression, which may
     have been changed by fold, STRING_CST for unparenthesized string
     constants, C_MAYBE_CONST_EXPR for __builtin_constant_p calls
     (even if parenthesized), for subexpressions, and for non-constant
     initializers, or ERROR_MARK for other expressions (including
     parenthesized expressions).  */
  تعداد ونه_کوډ_2 original_کوډ;
  /* If not NULL, the original type of an expression.  This will
     differ from the type of the value field for an enum constant.
     The type of an enum constant is a plain integer type, but this
     field will be the enum type.  */
  ونه original_type;

  /* The source range of this expression.  This is redundant
     for node values that have locations, but not all node kinds
     have locations (e.g. constants, and references to params, locals,
     etc), so we stash a copy here.  */
  سرچینه_range src_range;

  /* True if this was directly from a decimal constant token.  */
  bool m_decimal : 1;

  /* Access to the first and last locations within the source spelling
     of this expression.  */
  location_t get_پیل () ثابت { أرجع src_range.m_پیل; }
  location_t get_پای () ثابت { أرجع src_range.m_پای; }

  location_t get_location () ثابت
  {
    إذا (بیان_HAS_LOCATION (ارزښت))
      أرجع بیان_LOCATION (ارزښت);
    وإلا
      أرجع make_location (get_پیل (), get_پیل (), get_پای ());
  }

  /* Set the value to error_mark_node whilst ensuring that src_range
     and m_decimal are initialized.  */
  فراغ سېټ_error ()
  {
    ارزښت = error_mark_غوټه;
    src_range.m_پیل = UNKNOWN_LOCATION;
    src_range.m_پای = UNKNOWN_LOCATION;
    m_decimal = 0;
  }
};

/* Type alias for struct c_expr. This allows to use the structure
   inside the VEC types.  */
تعريفنوع بنية c_بیان c_بیان_t;

/* A kind of type specifier.  Note that this information is currently
   only used to distinguish tag definitions, tag references and typeof
   uses.  */
تعداد c_typespec_ډول {
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
بنية c_typespec {
  /* What kind of type specifier this is.  */
  تعداد c_typespec_ډول ډول;
  /* Whether the expression has operands suitable for use in constant
     expressions.  */
  bool بیان_const_operands;
  /* Whether the type specifier includes an enum type specifier (that
     is, ": specifier-qualifier-list" in a declaration using
     "enum").  */
  bool has_enum_type_specifier;
  /* The specifier itself.  */
  ونه spec;
  /* An expression to be evaluated before the type specifier, in the
     case of typeof specifiers, or NULL otherwise or if no such
     expression is required for a particular typeof specifier.  In
     particular, when typeof is applied to an expression of variably
     modified type, that expression must be evaluated in order to
     determine array sizes that form part of the type, but the
     expression itself (as opposed to the array sizes) forms no part
     of the type and so needs to be recorded separately.  */
  ونه بیان;
};

/* A storage class specifier.  */
تعداد c_storage_class {
  csc_none,
  csc_auto,
  csc_extern,
  csc_ثبتوونکی,
  csc_static,
  csc_typedef
};

/* A type specifier keyword "void", "_Bool", "char", "int", "float",
   "double", "_Decimal32", "_Decimal64", "_Decimal128", "_Decimal64x",
   "_Fract", "_Accum", "_BitInt", or none of these.  */
تعداد c_typespec_keyword {
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
تعداد c_declspec_کلمه {
  cdw_typespec /* A catch-all for a typespec.  */,
  cdw_storage_class  /* A catch-all for a storage class */,
  cdw_ځانګړتیاوې,
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
  cdw_پته_space,
  cdw_gimple,
  cdw_rtl,
  cdw_شمېره_د_elements /* This one must always be the last
			    enumerator.  */
};

تعداد c_declspec_il {
  cdil_none,
  cdil_gimple,		/* __GIMPLE  */
  cdil_gimple_cfg,	/* __GIMPLE(cfg)  */
  cdil_gimple_ssa,	/* __GIMPLE(ssa)  */
  cdil_rtl		/* __RTL  */
};

/* A sequence of declaration specifiers in C.  When a new declaration
   specifier is added, please update the enum c_declspec_word above
   accordingly.  */
بنية c_declspecs {
  location_t locations[cdw_شمېره_د_elements];
  /* The type specified, if a single type specifier such as a struct,
     union or enum specifier, typedef name or typeof specifies the
     whole type, or NULL_TREE if none or a keyword such as "void" or
     "char" is used.  Does not include qualifiers.  */
  ونه type;
  /* Any expression to be evaluated before the type, from a typeof
     specifier.  */
  ونه بیان;
  /* The attributes from a typedef decl.  */
  ونه decl_attr;
  /* When parsing, the GNU attributes and prefix standard attributes.
     Outside the parser, this will be NULL; attributes (possibly from
     multiple lists) will be passed separately.  */
  ونه attrs;
  /* When parsing, postfix standard attributes (which appertain to the
     type specified by the preceding declaration specifiers, unlike
     prefix standard attributes which appertain to the declaration or
     declarations as a whole).  */
  ونه postfix_attrs;
  /* The pass to start compiling a __GIMPLE or __RTL function with.  */
  حرف *gimple_or_rtl_pass;
  /* ENTRY BB count.  */
  profile_شمېر ثبت_bb_شمېر;
  /* The base-2 log of the greatest alignment required by an _Alignas
     specifier, in bytes, or -1 if no such specifiers with nonzero
     alignment.  */
  صحيح align_log;
  اتحاد {
    /* For the __intN declspec, this stores the index into the int_n_*
       arrays.  */
    صحيح int_n_idx;
    /* For the _FloatN and _FloatNx declspec, this stores the index into
       the floatn_nx_types array.  */
    صحيح floatn_nx_idx;
    /* For _BitInt(N) this stores the N.  */
    صحيح bitint_prec;
  } u;
  /* The storage class specifier, or csc_none if none.  */
  تعداد c_storage_class storage_class;
  /* Any type specifier keyword used such as "int", not reflecting
     modifiers such as "short", or cts_none if none.  */
  تعداد c_typespec_keyword typespec_کلمه : 8;
  /* The kind of type specifier if one has been seen, ctsk_none
     otherwise.  */
  تعداد c_typespec_ډول typespec_ډول : 4;
  تعداد c_declspec_il declspec_il : 3;
  /* Whether any expressions in typeof specifiers may appear in
     constant expressions.  */
  bool بیان_const_operands : 1;
  /* Whether any declaration specifiers have been seen at all.  */
  bool declspecs_کتل_شوی_p : 1;
  /* Whether any declaration specifiers other than standard attributes
     have been seen at all.  If only standard attributes have been
     seen, this is an attribute-declaration.  */
  bool non_std_attrs_کتل_شوی_p : 1;
  /* Whether something other than a storage class specifier or
     attribute has been seen.  This is used to warn for the
     obsolescent usage of storage class specifiers other than at the
     start of the list.  (Doing this properly would require function
     specifiers to be handled separately from storage class
     specifiers.)  */
  bool non_sc_کتل_شوی_p : 1;
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
  addr_space_t پته_space;
};

/* The various kinds of declarators in C.  */
تعداد c_declarator_ډول {
  /* An identifier.  */
  cdk_id,
  /* A function.  */
  cdk_function,
  /* An array.  */
  cdk_array,
  /* A pointer.  */
  cdk_اشاره_ګر,
  /* Parenthesized declarator with nested attributes.  */
  cdk_attrs
};

بنية c_arg_نښان {
  /* The argument name.  */
  ونه id;
  /* The type of the argument.  */
  ونه type;
};


/* Information about the parameters in a function declarator.  */
بنية c_arg_info {
  /* A list of parameter decls.  */
  ونه parms;
  /* A list of structure, union and enum tags defined.  */
  vec<c_arg_نښان, va_gc> *نښانونه;
  /* A list of argument types to go in the FUNCTION_TYPE.  */
  ونه types;
  /* A list of non-parameter decls (notably enumeration constants)
     defined with the parameters.  */
  ونه others;
  /* A compound expression of VLA sizes from the parameters, or NULL.
     In a function definition, these are used to ensure that
     side-effects in sizes of arrays converted to pointers (such as a
     parameter int i[n++]) take place; otherwise, they are
     ignored.  */
  ونه pending_sizes;
  /* True when these arguments had [*].  */
  bool had_vla_unspec : 1;
  /* True when the arguments are a (...) prototype.  */
  bool no_named_دلیلونه_stdarg_p : 1;
  /* True when empty parentheses have been interpreted as (void) in C23 or
     later.  This is only for use by -Wtraditional and is no longer needed if
     -Wtraditional is removed.  */
  bool c23_تشه_parens : 1;
};

/* A declarator.  */
بنية c_declarator {
  /* The kind of declarator.  */
  تعداد c_declarator_ډول ډول;
  location_t id_loc; /* Currently only set for cdk_id, cdk_array. */
  /* Except for cdk_id, the contained declarator.  For cdk_id, NULL.  */
  بنية c_declarator *declarator;
  اتحاد {
    /* For identifiers.  */
    بنية {
      /* An IDENTIFIER_NODE, or NULL_TREE if an abstract
	 declarator.  */
      ونه id;
      /* Any attributes (which apply to the declaration rather than to
	 the type described by the outer declarators).  */
      ونه attrs;
    } id;
    /* For functions.  */
    بنية c_arg_info *arg_info;
    /* For arrays.  */
    بنية {
      /* The array dimension, or NULL for [] and [*].  */
      ونه dimen;
      /* The qualifiers inside [].  */
      صحيح quals;
      /* The attributes (currently ignored) inside [].  */
      ونه attrs;
      /* Whether [static] was used.  */
      bool static_p : 1;
      /* Whether [*] was used.  */
      bool vla_unspec_p : 1;
    } array;
    /* For pointers, the qualifiers on the pointer type.  */
    صحيح اشاره_ګر_quals;
    /* For attributes.  */
    ونه attrs;
  } u;
};

/* A type name.  */
بنية c_type_name {
  /* The declaration specifiers.  */
  بنية c_declspecs *specs;
  /* The declarator.  */
  بنية c_declarator *declarator;
};

/* A parameter.  */
بنية c_parm {
  /* The declaration specifiers, minus any prefix attributes.  */
  بنية c_declspecs *specs;
  /* The attributes.  */
  ونه attrs;
  /* The declarator.  */
  بنية c_declarator *declarator;
  /* The location of the parameter.  */
  location_t loc;
};

/* Used when parsing an enum.  Initialized by start_enum.  */
بنية c_enum_contents
{
  /* While defining an enum type, this is 1 plus the last enumerator
     constant value.  */
  ونه enum_بل_ارزښت;

  /* The enumeration type itself.  */
  ونه enum_type;

  /* Nonzero means that there was overflow computing enum_next_value.  */
  صحيح enum_ډکېدنه;
};

/* A type of reference to a static identifier in an inline
   function.  */
تعداد c_inline_static_type {
  /* Identifier with internal linkage used in function that may be an
     inline definition (i.e., file-scope static).  */
  csi_دننی,
  /* Modifiable object with static storage duration defined in
     function that may be an inline definition (i.e., local
     static).  */
  csi_modifiable
};

/* Record details of decls possibly used inside sizeof or typeof.  */
بنية maybe_کارول_شوی_decl
{
  /* The decl.  */
  ونه decl;
  /* The level seen at (in_sizeof + in_typeof + in_countof + in_generic).  */
  صحيح level;
  /* Seen in address-of.  */
  bool پته;
  /* The next one at this level or above, or NULL.  */
  بنية maybe_کارول_شوی_decl *بل;
};


/* in c-parser.cc */
بنية c_ونه_token_vec;
خارجي فراغ c_parse_init (فراغ);
خارجي bool c_keyword_starts_typename (تعداد rid keyword);

/* in c-aux-info.cc */
خارجي فراغ gen_aux_info_ریکارډ (ونه, صحيح, صحيح, صحيح);

/* in c-decl.cc */
بنية c_spot_bindings;
class c_struct_parse_info;
خارجي بنية obstack parser_obstack;
/* Set to IN_ITERATION_STMT if parsing an iteration-statement,
   to IN_OMP_BLOCK if parsing OpenMP structured block and
   IN_OMP_FOR if parsing OpenMP loop.  If parsing a switch statement,
   this is bitwise ORed with IN_SWITCH_STMT, unless parsing an
   iteration-statement, OpenMP block or loop within that switch.
   If the innermost iteration/switch statement is named, IN_NAMED_STMT
   is additionally bitwise ORed into it.  */
#تعریف_کړه دننه_SWITCH_STMT		1
#تعریف_کړه دننه_ITERATION_STMT	2
#تعریف_کړه دننه_OMP_بلاک		4
#تعریف_کړه دننه_OMP_FOR		8
#تعریف_کړه دننه_OBJC_FOREACH		16
#تعریف_کړه دننه_NAMED_STMT		32
خارجي بینښه حرف دننه_statement;

خارجي bool switch_statement_break_کتل_شوی_p;

خارجي bool global_bindings_p (فراغ);
خارجي ونه pushdecl (ونه);
خارجي بینښه صحيح پیل_underspecified_init (location_t, ونه);
خارجي فراغ پای_underspecified_init (ونه, بینښه صحيح);
خارجي فراغ ټېل_scope (فراغ);
خارجي ونه راوباسه_scope (فراغ);
خارجي فراغ c_mark_decl_jump_unsafe_دننه_current_scope ();
خارجي فراغ c_bindings_پیل_stmt_بیان (بنية c_spot_bindings *);
خارجي فراغ c_bindings_پای_ټکی_stmt_بیان (بنية c_spot_bindings *);

خارجي فراغ ریکارډ_inline_static (location_t, ونه, ونه,
				  تعداد c_inline_static_type);
خارجي فراغ c_init_decl_processing (فراغ);
خارجي فراغ c_print_identifier (FILE *, ونه, صحيح);
خارجي صحيح quals_from_declspecs (ثابت بنية c_declspecs *);
خارجي بنية c_declarator *build_array_declarator (location_t, ونه,
    						    بنية c_declspecs *,
						    bool, bool);
خارجي ونه build_enumerator (location_t, location_t, بنية c_enum_contents *,
			      ونه, ونه);
خارجي ونه check_for_loop_decls (location_t, bool);
خارجي فراغ mark_forward_parm_decls (فراغ);
خارجي فراغ declare_parm_level (فراغ);
خارجي فراغ undeclared_variable (location_t, ونه);
خارجي ونه lookup_label_for_goto (location_t, ونه);
خارجي ونه declare_label (ونه);
خارجي ونه define_label (location_t, ونه);
خارجي بنية c_spot_bindings *c_get_switch_bindings (فراغ);
خارجي فراغ c_release_switch_bindings (بنية c_spot_bindings *);
خارجي bool c_check_switch_jump_warnings (بنية c_spot_bindings *,
					  location_t, location_t);
خارجي فراغ پای_decl (ونه, location_t, ونه, ونه, ونه);
خارجي ونه پای_enum (ونه, ونه, ونه);
خارجي فراغ پای_function (location_t = ننوت_location);
خارجي ونه پای_struct (location_t, ونه, ونه, ونه,
			   class c_struct_parse_info *,
			   ونه *بیان = عدم);
خارجي ونه c_simulate_enum_decl (location_t, ثابت حرف *,
				  vec<string_int_pair> *);
خارجي ونه c_simulate_ریکارډ_decl (location_t, ثابت حرف *,
				    array_ټوټه<ثابت ونه>);
خارجي بنية c_arg_info *build_arg_info (فراغ);
خارجي بنية c_arg_info *get_parm_info (bool, ونه);
خارجي ونه grokfield (location_t, بنية c_declarator *,
		       بنية c_declspecs *, ونه, ونه *, ونه *);
خارجي ونه groktypename (بنية c_type_name *, ونه *, bool *);
خارجي ونه grokgenassoc (بنية c_type_name *);
خارجي ونه grokparm (ثابت بنية c_parm *, ونه *);
خارجي ونه implicitly_declare (location_t, ونه);
خارجي فراغ keep_بل_level (فراغ);
خارجي فراغ pending_xref_error (فراغ);
خارجي فراغ c_ټېل_function_context (فراغ);
خارجي فراغ c_راوباسه_function_context (فراغ);
خارجي فراغ ټېل_parm_decl (ثابت بنية c_parm *, ونه *);
خارجي بنية c_declarator *سېټ_array_declarator_inner (بنية c_declarator *,
							بنية c_declarator *);
خارجي ونه c_builtin_function (ونه);
خارجي ونه c_builtin_function_ext_scope (ونه);
خارجي ونه c_simulate_builtin_function_decl (ونه);
خارجي فراغ c_warn_ناکارول_شوی_ځانګړتیاوې (ونه);
خارجي ونه c_warn_type_ځانګړتیاوې (ونه, ونه);
خارجي فراغ shadow_نښان (ثابت بنية c_declspecs *);
خارجي فراغ shadow_نښان_warned (ثابت بنية c_declspecs *, صحيح);
خارجي ونه پیل_enum (location_t, بنية c_enum_contents *, ونه, ونه,
			bool potential_nesting_p);
خارجي bool پیل_function (بنية c_declspecs *, بنية c_declarator *, ونه);
خارجي ونه پیل_decl (بنية c_declarator *, بنية c_declspecs *, bool,
			ونه, bool = true, location_t * = عدم);
خارجي ونه پیل_struct (location_t, تعداد ونه_کوډ_2, ونه,
			  class c_struct_parse_info **);
خارجي فراغ store_parm_decls (فراغ);
خارجي فراغ store_parm_decls_from (بنية c_arg_info *);
خارجي فراغ لنډمهاله_store_parm_decls (ونه, ونه);
خارجي فراغ لنډمهاله_راوباسه_parm_decls (فراغ);
خارجي ونه xref_نښان (تعداد ونه_کوډ_2, ونه);
خارجي بنية c_typespec parser_xref_نښان (location_t, تعداد ونه_کوډ_2, ونه,
					  bool, ونه, bool);
خارجي بنية c_parm *build_c_parm (بنية c_declspecs *, ونه,
				    بنية c_declarator *, location_t);
خارجي بنية c_declarator *build_attrs_declarator (ونه,
						    بنية c_declarator *);
خارجي بنية c_declarator *build_function_declarator (بنية c_arg_info *,
						       بنية c_declarator *);
خارجي بنية c_declarator *build_id_declarator (ونه);
خارجي بنية c_declarator *make_اشاره_ګر_declarator (بنية c_declspecs *,
						     بنية c_declarator *);
خارجي بنية c_declspecs *build_null_declspecs (فراغ);
خارجي بنية c_declspecs *declspecs_جمع_کړه_qual (location_t,
					       بنية c_declspecs *, ونه);
خارجي بنية c_declspecs *declspecs_جمع_کړه_type (location_t,
					       بنية c_declspecs *,
					       بنية c_typespec);
خارجي بنية c_declspecs *declspecs_جمع_کړه_scspec (location_t,
						 بنية c_declspecs *, ونه);
خارجي بنية c_declspecs *declspecs_جمع_کړه_attrs (location_t,
						بنية c_declspecs *, ونه);
خارجي بنية c_declspecs *declspecs_جمع_کړه_addrspace (location_t,
						    بنية c_declspecs *,
						    addr_space_t);
خارجي بنية c_declspecs *declspecs_جمع_کړه_alignas (location_t,
						  بنية c_declspecs *, ونه);
خارجي بنية c_declspecs *پای_declspecs (بنية c_declspecs *);
خارجي اندازه_t c_ونه_اندازه (تعداد ونه_کوډ_2);
خارجي صحيح c_get_loop_نومونه (ونه, bool, ونه *);
خارجي فراغ c_release_loop_نومونه (صحيح);
خارجي ونه c_پای_bc_name (location_t, ونه, bool);

/* in c-objc-common.cc */
خارجي bool c_objc_common_init (فراغ);
خارجي bool c_missing_noreturn_ok_p (ونه);
خارجي bool c_warn_ناکارول_شوی_global_decl (const_ونه);
خارجي فراغ c_initialize_diagnostics (diagnostics::context *);
خارجي bool c_var_mod_p (ونه x, ونه fn);
خارجي alias_سېټ_type c_get_alias_سېټ (ونه);
خارجي صحيح c_type_dwarf_attribute (const_ونه, صحيح);
خارجي ونه c_enum_underlying_بنسټ_type (const_ونه);

/* in c-typeck.cc */
خارجي صحيح دننه_alignof;
خارجي صحيح دننه_sizeof;
خارجي صحيح دننه_countof;
خارجي صحيح دننه_typeof;
خارجي صحيح دننه_generic;
خارجي bool c_دننه_omp_for;
خارجي bool c_omp_array_section_p;

خارجي ونه c_وروستی_sizeof_arg;
خارجي location_t c_وروستی_sizeof_loc;

خارجي بنية c_switch *c_switch_ډېری;

خارجي bool null_اشاره_ګر_constant_p (const_ونه);


مضمن bool
c_type_variably_modified_p (ونه t)
{
  إذا (error_mark_غوټه == t)
    أرجع false;
  إذا (C_TYPE_VARIABLY_MODIFIED (t))
    أرجع true;
  إذا (TYPE_STRUCTURAL_EQUALITY_P (t))
    {
      /* The flag may not have been set yet because of incomplete
	 structure or union types completed later.  */
      بدل (ونه_کوډ (t))
	{
	حالة ARRAY_TYPE:
	حالة FUNCTION_TYPE:
	حالة اشاره_ګر_TYPE:
	  /* Recurse.  */
	  إذا (c_type_variably_modified_p (ونه_TYPE (t)))
	    {
	      C_TYPE_VARIABLY_MODIFIED (t) = 1;
	      أرجع true;
	    }
	  اكسر;
	افتراضي:
	  اكسر;
	}
    }
  أرجع false;
}

مضمن bool
c_type_unspecified_p (ونه t)
{
  أرجع error_mark_غوټه != t
	 && C_TYPE_VARIABLE_اندازه (t) && ونه_کوډ (t) == ARRAY_TYPE
	 && TYPE_DOMAIN (t) && TYPE_MAX_ارزښت (TYPE_DOMAIN (t))
	 && ونه_کوډ (TYPE_MAX_ارزښت (TYPE_DOMAIN (t))) == COMPOUND_بیان
	 && integer_zerop (ونه_عملوند (TYPE_MAX_ارزښت (TYPE_DOMAIN (t)), 0))
	 && integer_zerop (ونه_عملوند (TYPE_MAX_ارزښت (TYPE_DOMAIN (t)), 1));
}

خارجي bool zero_اوږدتیا_array_type_p (const_ونه type);
خارجي bool char_type_p (ونه);
خارجي ونه c_type_نښان (const_ونه t);
خارجي ونه c_objc_common_truthvalue_conversion (location_t, ونه,
						 ونه = integer_type_غوټه);
خارجي ونه require_complete_type (location_t, ونه);
خارجي bool same_translation_unit_p (const_ونه, const_ونه);
خارجي bool comptypes (ونه, ونه);
خارجي bool comptypes_same_p (ونه, ونه);
خارجي bool comptypes_equiv_p (ونه, ونه);
خارجي bool comptypes_check_enum_int (ونه, ونه, bool *);
خارجي bool c_mark_addressable (ونه, bool = false, bool = false);
خارجي فراغ c_incomplete_type_error (location_t, const_ونه, const_ونه);
خارجي ونه c_type_promotes_منزل (ونه);
خارجي بنية c_بیان default_function_array_conversion (location_t,
							بنية c_بیان);
خارجي بنية c_بیان default_function_array_read_conversion (location_t,
							     بنية c_بیان);
خارجي بنية c_بیان convert_lvalue_منزل_rvalue (location_t, بنية c_بیان,
					       bool, bool, bool = false);
خارجي ونه decl_constant_ارزښت_1 (ونه, bool);
خارجي فراغ mark_exp_read (ونه);
خارجي ونه مرکب_type (ونه, ونه);
خارجي ونه lookup_ډګر (const_ونه, ونه);
خارجي ونه build_component_ref (location_t, ونه, ونه, location_t,
				 location_t);
خارجي ونه handle_counted_by_for_component_ref (location_t, ونه);
خارجي ونه build_array_ref (location_t, ونه, ونه);
خارجي ونه build_omp_array_section (location_t, ونه, ونه, ونه);
خارجي ونه build_external_ref (location_t, ونه, bool, ونه *);
خارجي فراغ راوباسه_maybe_کارول_شوی (bool);
خارجي بنية maybe_کارول_شوی_decl *save_maybe_کارول_شوی ();
خارجي فراغ restore_maybe_کارول_شوی (بنية maybe_کارول_شوی_decl *);
خارجي فراغ mark_decl_کارول_شوی (ونه, bool);
خارجي بنية c_بیان c_بیان_sizeof_بیان (location_t, بنية c_بیان);
خارجي بنية c_بیان c_بیان_sizeof_type (location_t, بنية c_type_name *);
خارجي بنية c_بیان c_بیان_countof_بیان (location_t, بنية c_بیان);
خارجي بنية c_بیان c_بیان_countof_type (location_t loc,
					  بنية c_type_name *);
خارجي بنية c_بیان c_بیان_maxof_type (location_t loc, بنية c_type_name *);
خارجي بنية c_بیان c_بیان_minof_type (location_t loc, بنية c_type_name *);
خارجي بنية c_بیان parser_build_unary_op (location_t, تعداد ونه_کوډ_2,
    					    بنية c_بیان);
خارجي بنية c_بیان parser_build_دوګونی_op (location_t,
    					     تعداد ونه_کوډ_2, بنية c_بیان,
					     بنية c_بیان, ونه);
خارجي ونه build_conditional_بیان (location_t, ونه, bool, ونه, ونه,
				    location_t, ونه, ونه, location_t);
خارجي ونه build_compound_بیان (location_t, ونه, ونه);
خارجي ونه c_cast_بیان (location_t, بنية c_type_name *, ونه);
خارجي ونه build_c_cast (location_t, ونه, ونه);
خارجي فراغ store_init_ارزښت (location_t, ونه, ونه, ونه);
خارجي فراغ maybe_warn_string_init (location_t, ونه, بنية c_بیان);
خارجي فراغ پیل_init (ونه, ونه, bool, bool, rich_location *);
خارجي فراغ پای_init (فراغ);
خارجي فراغ really_پیل_incremental_init (ونه);
خارجي فراغ پای_implicit_inits (location_t, بنية obstack *);
خارجي فراغ ټېل_init_level (location_t, صحيح, بنية obstack *);
خارجي بنية c_بیان راوباسه_init_level (location_t, صحيح, بنية obstack *,
				     location_t);
خارجي فراغ سېټ_init_شاخص (location_t, ونه, ونه, بنية obstack *);
خارجي فراغ سېټ_init_label (location_t, ونه, location_t, بنية obstack *);
بینښه c_maybe_optimize_large_byte_initializer (فراغ);
خارجي فراغ process_init_element (location_t, بنية c_بیان, bool,
				  بنية obstack *);
خارجي ونه build_compound_literal (location_t, ونه, ونه, bool,
				    بینښه صحيح, بنية c_declspecs *);
خارجي فراغ check_compound_literal_type (location_t, بنية c_type_name *);
خارجي ونه c_پیل_switch (location_t, location_t, ونه, bool, ونه);
خارجي فراغ c_پای_switch (ونه, ونه);
خارجي ونه build_asm_بیان (location_t, ونه, ونه, ونه, ونه, ونه, bool,
			    bool);
خارجي ونه build_asm_stmt (bool, ونه);
خارجي صحيح c_types_compatible_p (ونه, ونه);
خارجي ونه c_begin_compound_stmt (bool);
خارجي ونه c_پای_ټکی_compound_stmt (location_t, ونه, bool);
خارجي فراغ c_پای_if_stmt (location_t, ونه, ونه, ونه);
خارجي فراغ c_پای_loop (location_t, location_t, ونه, location_t, ونه,
			   ونه, ونه, ونه, bool);
خارجي ونه c_begin_stmt_بیان (فراغ);
خارجي ونه c_پای_stmt_بیان (location_t, ونه);
خارجي ونه c_process_بیان_stmt (location_t, ونه);
خارجي ونه c_پای_بیان_stmt (location_t, ونه);
خارجي ونه c_پای_return (location_t, ونه, ونه, bool = false);
خارجي ونه c_پای_bc_stmt (location_t, ونه, bool, ونه);
خارجي ونه c_پای_goto_label (location_t, ونه);
خارجي ونه c_پای_goto_ptr (location_t, c_بیان val);
خارجي ونه c_بیان_منزل_decl (ونه, bool *, bool *);
خارجي ونه c_پای_omp_construct (location_t, تعداد ونه_کوډ_2, ونه, ونه);
خارجي ونه c_پای_oacc_معلومات (location_t, ونه, ونه);
خارجي ونه c_پای_oacc_host_معلومات (location_t, ونه, ونه);
خارجي ونه c_begin_omp_parallel (فراغ);
خارجي ونه c_پای_omp_parallel (location_t, ونه, ونه);
خارجي ونه c_begin_omp_task (فراغ);
خارجي ونه c_پای_omp_task (location_t, ونه, ونه);
خارجي فراغ c_پای_omp_cancel (location_t, ونه);
خارجي فراغ c_پای_omp_cancellation_ټکی (location_t, ونه);
خارجي ونه c_پای_omp_clauses (ونه, تعداد c_omp_region_type);
خارجي ونه c_omp_پای_mapper_clauses (ونه);
خارجي ونه c_omp_mapper_lookup (ونه, ونه);
خارجي ونه c_omp_ایستل_mapper_directive (ونه);
خارجي ونه c_omp_map_array_section (location_t, ونه);
خارجي ونه c_build_va_arg (location_t, ونه, location_t, ونه, ونه);
خارجي ونه c_پای_transaction (location_t, ونه, صحيح);
خارجي bool c_ونه_equal (ونه, ونه);
خارجي ونه c_build_function_call_vec (location_t, ثابت vec<location_t>&,
				       ونه, vec<ونه, va_gc> *,
				       vec<ونه, va_gc> *);
خارجي ونه c_omp_clause_copy_ctor (ونه, ونه, ونه);
خارجي ونه c_reconstruct_complex_type (ونه, ونه);
خارجي ونه c_type_canonical (ونه);
خارجي ونه c_build_type_attribute_variant (ونه ntype, ونه attrs);
خارجي ونه c_build_اشاره_ګر_type (ونه type);
خارجي ونه c_build_array_type (ونه type, ونه domain);
خارجي ونه c_build_array_type_unspecified (ونه type);
خارجي ونه c_build_array_type_zero_اندازه (ونه type);
خارجي ونه c_build_function_type (ونه type, ونه دلیلونه, bool no = false);
خارجي ونه c_build_اشاره_ګر_type_for_ډېرپېښ (ونه type, machine_ډېرپېښ ډېرپېښ, bool m);

/* Set to 0 at beginning of a function definition, set to 1 if
   a return statement that specifies a return value is seen.  */

خارجي صحيح current_function_returns_ارزښت;

/* Set to 0 at beginning of a function definition, set to 1 if
   a return statement with no argument is seen.  */

خارجي صحيح current_function_returns_null;

/* Set to 0 at beginning of a function definition, set to 1 if
   a call to a noreturn function is seen.  */

خارجي صحيح current_function_returns_abnormally;

/* In c-decl.cc */

/* Tell the binding oracle what kind of binding we are looking for.  */

تعداد c_oracle_request
{
  C_ORACLE_نښه,
  C_ORACLE_نښان,
  C_ORACLE_LABEL
};

/* If this is non-NULL, then it is a "binding oracle" which can lazily
   create bindings when needed by the C compiler.  The oracle is told
   the name and type of the binding to create.  It can call pushdecl
   or the like to ensure the binding is visible; or do nothing,
   leaving the binding untouched.  c-decl.cc takes note of when the
   oracle has been called and will not call it again if it fails to
   create a given binding.  */

تعريفنوع فراغ c_binding_oracle_function (تعداد c_oracle_request, ونه identifier);

خارجي c_binding_oracle_function *c_binding_oracle;

خارجي فراغ c_پای_incomplete_decl (ونه);
خارجي ونه c_omp_reduction_id (تعداد ونه_کوډ_2, ونه);
خارجي ونه c_omp_reduction_decl (ونه);
خارجي ونه c_omp_reduction_lookup (ونه, ونه);
خارجي ونه c_check_omp_declare_reduction_r (ونه *, صحيح *, فراغ *);
خارجي ونه c_omp_mapper_id (ونه);
خارجي ونه c_omp_mapper_decl (ونه);
خارجي فراغ c_omp_لټون_mapper_bindings (location_t, ونه *, ونه);
خارجي bool c_check_دننه_current_scope (ونه);
خارجي فراغ c_pushtag (location_t, ونه, ونه);
خارجي فراغ c_bind (location_t, ونه, bool);
خارجي bool نښان_exists_p (تعداد ونه_کوډ_2, ونه);

خارجي فراغ verify_counted_by_for_سر_anonymous_type (ونه);

/* In c-errors.cc */
خارجي bool pedwarn_c90 (location_t, diagnostics::option_id, ثابت حرف *, ...)
    ATTRIBUTE_GCC_DIAG(3,4);
خارجي bool pedwarn_c99 (location_t, diagnostics::option_id, ثابت حرف *, ...)
    ATTRIBUTE_GCC_DIAG(3,4);
خارجي bool pedwarn_c11 (location_t, diagnostics::option_id, ثابت حرف *, ...)
    ATTRIBUTE_GCC_DIAG(3,4);
خارجي bool pedwarn_c23 (location_t, diagnostics::option_id, ثابت حرف *, ...)
    ATTRIBUTE_GCC_DIAG(3,4);
خارجي فراغ جمع_کړه_note_about_new_keyword (location_t loc,
					ونه keyword_id);

خارجي فراغ
سېټ_c_بیان_سرچینه_range (c_بیان *بیان,
			 location_t پیل, location_t پای);

خارجي فراغ
سېټ_c_بیان_سرچینه_range (c_بیان *بیان,
			 سرچینه_range src_range);

/* In c-fold.cc */
خارجي vec<ونه> incomplete_ریکارډ_decls;

خارجي ثابت حرف *c_get_sarif_سرچینه_language (ثابت حرف *filename);

خارجي ثابت بنية scoped_attribute_specs std_attribute_جدول;

#إذا CHECKING_P
namespace selftest {
  خارجي فراغ پرلپسې_c_tests (فراغ);
} // namespace selftest
#د_که_پای /* #if CHECKING_P */


#د_که_پای /* ! GCC_C_TREE_H */
