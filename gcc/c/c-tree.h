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

#اگر_غیر_تعریف_شدہ GCC_C_درخت_H
#تعریف_کرو GCC_C_درخت_H

#شامل "c-family/c-common.h"
#شامل "diagnostic.h"

/* struct lang_identifier is private to c-decl.cc, but langhooks.cc needs to
   know how big it is.  This is sanity-checked in c-decl.cc.  */
#تعریف_کرو C_SIZEOF_STRUCT_LANG_IDENTIFIER \
  (حجم (ساخت c_common_identifier) + 3 * حجم (خالی *))

/* In a RECORD_TYPE or UNION_TYPE, nonzero if any component is read-only.  */
#تعریف_کرو C_TYPE_FIELDS_READONLY(TYPE) درخت_LANG_FLAG_1 (TYPE)

/* In a RECORD_TYPE or UNION_TYPE, nonzero if any component is volatile.  */
#تعریف_کرو C_TYPE_FIELDS_VOLATILE(TYPE) درخت_LANG_FLAG_2 (TYPE)

/* In a RECORD_TYPE or UNION_TYPE, nonzero if any component is
   volatile, restrict-qualified or atomic; that is, has a type not
   permitted for a constexpr object.  */
#تعریف_کرو C_TYPE_FIELDS_NON_CONSTEXPR(TYPE) درخت_LANG_FLAG_4 (TYPE)

/* In a RECORD_TYPE or UNION_TYPE, nonzero if any component has a
   counted_by attribute.  */
#تعریف_کرو C_TYPE_FIELDS_HAS_COUNTED_BY(TYPE) TYPE_LANG_FLAG_3 (TYPE)

/* In a RECORD_TYPE or UNION_TYPE or ENUMERAL_TYPE
   nonzero if the definition of the type has already started.  */
#تعریف_کرو C_TYPE_BEING_DEFINED(TYPE) TYPE_LANG_FLAG_0 (TYPE)

/* In an incomplete RECORD_TYPE, UNION_TYPE or ENUMERAL_TYPE, a list of
   variable declarations whose type would be completed by completing
   that type.  */
#تعریف_کرو C_TYPE_INCOMPLETE_VARS(TYPE) \
  TYPE_LANG_خانہ_1 (درخت_CHECK4 (TYPE, ریکارڈ_TYPE, UNION_TYPE, \
				 QUAL_UNION_TYPE, ENUMERAL_TYPE))

/* In an IDENTIFIER_NODE, nonzero if this identifier is actually a
   keyword.  C_RID_CODE (node) is then the RID_* value of the keyword.  */
#تعریف_کرو C_IS_RESERVED_لفظ(ID) درخت_LANG_FLAG_0 (ID)

/* Record whether a type or decl was written with nonconstant size.
   Note that TYPE_SIZE may have simplified to a constant.  */
#تعریف_کرو C_TYPE_VARIABLE_سائز(TYPE) TYPE_LANG_FLAG_1 (TYPE)
#تعریف_کرو C_DECL_VARIABLE_سائز(TYPE) DECL_LANG_FLAG_0 (TYPE)

/* Record whether a type is variably modified. */
#تعریف_کرو C_TYPE_VARIABLY_MODIFIED(TYPE) TYPE_LANG_FLAG_6 (TYPE)


/* Record whether a type is defined inside a struct or union type.
   This is used for -Wc++-compat. */
#تعریف_کرو C_TYPE_DEFINED_اندر_STRUCT(TYPE) TYPE_LANG_FLAG_2 (TYPE)

/* Record whether a typedef for type `int' was actually `signed int'.  */
#تعریف_کرو C_TYPEDEF_EXPLICITLY_SIGNED(EXP) DECL_LANG_FLAG_1 (EXP)

/* For a FUNCTION_DECL, nonzero if it was defined without an explicit
   return type.  */
#تعریف_کرو C_FUNCTION_IMPLICIT_INT(EXP) DECL_LANG_FLAG_1 (EXP)

/* For a FUNCTION_DECL, nonzero if it was an implicit declaration.  */
#تعریف_کرو C_DECL_IMPLICIT(EXP) DECL_LANG_FLAG_2 (EXP)

/* For a PARM_DECL, nonzero if it was declared as an array.  */
#تعریف_کرو C_ARRAY_PARAMETER(گرہ_2) DECL_LANG_FLAG_0 (گرہ_2)

/* For FUNCTION_DECLs, evaluates true if the decl is a nested
   function that requires a non-local context.  */
#تعریف_کرو C_FUNC_NONLOCAL_CONTEXT(EXP)		\
  DECL_LANG_FLAG_4 (FUNCTION_DECL_CHECK (EXP))

/* For FUNCTION_DECLs, evaluates true if the decl is built-in but has
   been declared.  */
#تعریف_کرو C_DECL_DECLARED_BUILTIN(EXP)		\
  DECL_LANG_FLAG_3 (FUNCTION_DECL_CHECK (EXP))

/* For FUNCTION_DECLs, evaluates true if the decl is built-in, has a
   built-in prototype and does not have a non-built-in prototype.  */
#تعریف_کرو C_DECL_BUILTIN_PROTOTYPE(EXP)		\
  DECL_LANG_FLAG_6 (FUNCTION_DECL_CHECK (EXP))

/* For LABEL_DECLs marks canonical name of a loop.  */
#تعریف_کرو C_DECL_LOOP_NAME(EXP) DECL_LANG_FLAG_3 (LABEL_DECL_CHECK (EXP))

/* For LABEL_DECLs marks canonical name of a switch.  During parsing of
   ObjC foreach named loop both C_DECL_LOOP_NAME and C_DECL_SWITCH_NAME
   are temporarily set.  */
#تعریف_کرو C_DECL_SWITCH_NAME(EXP) DECL_LANG_FLAG_5 (LABEL_DECL_CHECK (EXP))

/* For LABEL_DECLs marks canonical name of a loop or switch being
   valid for use in break identifier or continue identifier statements.  */
#تعریف_کرو C_DECL_LOOP_SWITCH_NAME_VALID(EXP) \
  DECL_LANG_FLAG_6 (LABEL_DECL_CHECK (EXP))

/* For LABEL_DECLs marks canonical loop or switch names which were actually
   used in one or more break identifier or continue identifier statements.  */
#تعریف_کرو C_DECL_LOOP_SWITCH_NAME_مستعمل(EXP) \
  DECL_LANG_FLAG_8 (LABEL_DECL_CHECK (EXP))

/* Record whether a decl was declared register.  This is strictly a
   front-end flag, whereas DECL_REGISTER is used for code generation;
   they may differ for structures with volatile fields.  */
#تعریف_کرو C_DECL_رجسٹر(EXP) \
  DECL_LANG_FLAG_4 (درخت_NOT_CHECK (EXP, FUNCTION_DECL))

/* Record whether a decl was used in an expression anywhere except an
   unevaluated operand of sizeof / typeof / alignof.  This is only
   used for functions declared static but not defined, though outside
   sizeof and typeof it is set for other function decls as well.  */
#تعریف_کرو C_DECL_مستعمل(EXP) DECL_LANG_FLAG_5 (FUNCTION_DECL_CHECK (EXP))

/* Record whether a variable has been declared threadprivate by
   #pragma omp threadprivate.  */
#تعریف_کرو C_DECL_THREADPRIVATE_P(DECL) DECL_LANG_FLAG_3 (VAR_DECL_CHECK (DECL))

/* Set on VAR_DECLs for compound literals.  */
#تعریف_کرو C_DECL_COMPOUND_LITERAL_P(DECL) \
  DECL_LANG_FLAG_5 (VAR_DECL_CHECK (DECL))

/* Set on decls used as placeholders for a C23 underspecified object
   definition.  */
#تعریف_کرو C_DECL_UNDERSPECIFIED(DECL) DECL_LANG_FLAG_7 (DECL)

/* Set on VAR_DECLs declared as 'constexpr'.  */
#تعریف_کرو C_DECL_DECLARED_CONSTEXPR(DECL) \
  DECL_LANG_FLAG_8 (VAR_DECL_CHECK (DECL))

/* Nonzero for a decl which either doesn't exist or isn't a prototype.
   N.B. Could be simplified if all built-in decls had complete prototypes
   (but this is presently difficult because some of them need FILE*).  */
#تعریف_کرو C_DECL_ISNT_PROTOTYPE(EXP)			\
       (EXP == 0					\
	|| (!prototype_p (درخت_TYPE (EXP))	\
	    && !fndecl_built_اندر_p (EXP)))

/* For FUNCTION_TYPE, a hidden list of types of arguments.  The same as
   TYPE_ARG_TYPES for functions with prototypes, but created for functions
   without prototypes.  */
#تعریف_کرو TYPE_ACTUAL_ARG_TYPES(گرہ_2) \
  TYPE_LANG_خانہ_1 (FUNCTION_TYPE_CHECK (گرہ_2))

/* For a CONSTRUCTOR, whether some initializer contains a
   subexpression meaning it is not a constant expression.  */
#تعریف_کرو CONSTRUCTOR_NON_CONST(اظہاریہ_2) درخت_LANG_FLAG_1 (CONSTRUCTOR_CHECK (اظہاریہ_2))

/* For a SAVE_EXPR, nonzero if the operand of the SAVE_EXPR has already
   been folded.  */
#تعریف_کرو SAVE_اظہاریہ_FOLDED_P(EXP)	درخت_LANG_FLAG_1 (SAVE_اظہاریہ_CHECK (EXP))

/* Whether a type has boolean semantics: either a boolean type or an
   enumeration type with a boolean type as its underlying type.  */
#تعریف_کرو C_BOOLEAN_TYPE_P(TYPE)						\
  (درخت_رمز (TYPE) == BOOLEAN_TYPE					\
   || (درخت_رمز (TYPE) == ENUMERAL_TYPE				\
       && ENUM_UNDERLYING_TYPE (TYPE) != NULL_درخت			\
       && (درخت_رمز (ENUM_UNDERLYING_TYPE (TYPE)) == BOOLEAN_TYPE	\
	   || c_hardbool_type_attr (TYPE))))

/* Record parser information about an expression that is irrelevant
   for code generation alongside a tree representing its value.  */
ساخت c_اظہاریہ
{
  /* The value of the expression.  */
  درخت قدر;
  /* Record the original unary/binary operator of an expression, which may
     have been changed by fold, STRING_CST for unparenthesized string
     constants, C_MAYBE_CONST_EXPR for __builtin_constant_p calls
     (even if parenthesized), for subexpressions, and for non-constant
     initializers, or ERROR_MARK for other expressions (including
     parenthesized expressions).  */
  شمار درخت_رمز_2 original_رمز;
  /* If not NULL, the original type of an expression.  This will
     differ from the type of the value field for an enum constant.
     The type of an enum constant is a plain integer type, but this
     field will be the enum type.  */
  درخت original_type;

  /* The source range of this expression.  This is redundant
     for node values that have locations, but not all node kinds
     have locations (e.g. constants, and references to params, locals,
     etc), so we stash a copy here.  */
  ماخذ_range src_range;

  /* True if this was directly from a decimal constant token.  */
  bool m_decimal : 1;

  /* Access to the first and last locations within the source spelling
     of this expression.  */
  location_t get_آغاز () ثابت { واپس src_range.m_آغاز; }
  location_t get_اختتام () ثابت { واپس src_range.m_اختتام; }

  location_t get_location () ثابت
  {
    اگر (اظہاریہ_HAS_LOCATION (قدر))
      واپس اظہاریہ_LOCATION (قدر);
    ورنہ
      واپس make_location (get_آغاز (), get_آغاز (), get_اختتام ());
  }

  /* Set the value to error_mark_node whilst ensuring that src_range
     and m_decimal are initialized.  */
  خالی سیٹ_error ()
  {
    قدر = error_mark_گرہ;
    src_range.m_آغاز = UNKNOWN_LOCATION;
    src_range.m_اختتام = UNKNOWN_LOCATION;
    m_decimal = 0;
  }
};

/* Type alias for struct c_expr. This allows to use the structure
   inside the VEC types.  */
قسمتعریف ساخت c_اظہاریہ c_اظہاریہ_t;

/* A kind of type specifier.  Note that this information is currently
   only used to distinguish tag definitions, tag references and typeof
   uses.  */
شمار c_typespec_قسم {
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
ساخت c_typespec {
  /* What kind of type specifier this is.  */
  شمار c_typespec_قسم قسم;
  /* Whether the expression has operands suitable for use in constant
     expressions.  */
  bool اظہاریہ_const_operands;
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
  درخت اظہاریہ;
};

/* A storage class specifier.  */
شمار c_storage_class {
  csc_none,
  csc_auto,
  csc_extern,
  csc_رجسٹر,
  csc_static,
  csc_typedef
};

/* A type specifier keyword "void", "_Bool", "char", "int", "float",
   "double", "_Decimal32", "_Decimal64", "_Decimal128", "_Decimal64x",
   "_Fract", "_Accum", "_BitInt", or none of these.  */
شمار c_typespec_keyword {
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
شمار c_declspec_لفظ {
  cdw_typespec /* A catch-all for a typespec.  */,
  cdw_storage_class  /* A catch-all for a storage class */,
  cdw_اوصاف,
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
  cdw_پتہ_space,
  cdw_gimple,
  cdw_rtl,
  cdw_نمبر_کا_elements /* This one must always be the last
			    enumerator.  */
};

شمار c_declspec_il {
  cdil_none,
  cdil_gimple,		/* __GIMPLE  */
  cdil_gimple_cfg,	/* __GIMPLE(cfg)  */
  cdil_gimple_ssa,	/* __GIMPLE(ssa)  */
  cdil_rtl		/* __RTL  */
};

/* A sequence of declaration specifiers in C.  When a new declaration
   specifier is added, please update the enum c_declspec_word above
   accordingly.  */
ساخت c_declspecs {
  location_t locations[cdw_نمبر_کا_elements];
  /* The type specified, if a single type specifier such as a struct,
     union or enum specifier, typedef name or typeof specifies the
     whole type, or NULL_TREE if none or a keyword such as "void" or
     "char" is used.  Does not include qualifiers.  */
  درخت type;
  /* Any expression to be evaluated before the type, from a typeof
     specifier.  */
  درخت اظہاریہ;
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
  حرف *gimple_or_rtl_pass;
  /* ENTRY BB count.  */
  profile_گنتی اندراج_bb_گنتی;
  /* The base-2 log of the greatest alignment required by an _Alignas
     specifier, in bytes, or -1 if no such specifiers with nonzero
     alignment.  */
  صحیح align_log;
  اتحاد {
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
  شمار c_storage_class storage_class;
  /* Any type specifier keyword used such as "int", not reflecting
     modifiers such as "short", or cts_none if none.  */
  شمار c_typespec_keyword typespec_لفظ : 8;
  /* The kind of type specifier if one has been seen, ctsk_none
     otherwise.  */
  شمار c_typespec_قسم typespec_قسم : 4;
  شمار c_declspec_il declspec_il : 3;
  /* Whether any expressions in typeof specifiers may appear in
     constant expressions.  */
  bool اظہاریہ_const_operands : 1;
  /* Whether any declaration specifiers have been seen at all.  */
  bool declspecs_نظر_آیا_p : 1;
  /* Whether any declaration specifiers other than standard attributes
     have been seen at all.  If only standard attributes have been
     seen, this is an attribute-declaration.  */
  bool non_std_attrs_نظر_آیا_p : 1;
  /* Whether something other than a storage class specifier or
     attribute has been seen.  This is used to warn for the
     obsolescent usage of storage class specifiers other than at the
     start of the list.  (Doing this properly would require function
     specifiers to be handled separately from storage class
     specifiers.)  */
  bool non_sc_نظر_آیا_p : 1;
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
  addr_space_t پتہ_space;
};

/* The various kinds of declarators in C.  */
شمار c_declarator_قسم {
  /* An identifier.  */
  cdk_id,
  /* A function.  */
  cdk_function,
  /* An array.  */
  cdk_array,
  /* A pointer.  */
  cdk_اشارہ_گر,
  /* Parenthesized declarator with nested attributes.  */
  cdk_attrs
};

ساخت c_arg_لیبل {
  /* The argument name.  */
  درخت id;
  /* The type of the argument.  */
  درخت type;
};


/* Information about the parameters in a function declarator.  */
ساخت c_arg_info {
  /* A list of parameter decls.  */
  درخت parms;
  /* A list of structure, union and enum tags defined.  */
  vec<c_arg_لیبل, va_gc> *لیبل_فہرست;
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
  bool no_named_دلائل_stdarg_p : 1;
  /* True when empty parentheses have been interpreted as (void) in C23 or
     later.  This is only for use by -Wtraditional and is no longer needed if
     -Wtraditional is removed.  */
  bool c23_خالی_خانے_parens : 1;
};

/* A declarator.  */
ساخت c_declarator {
  /* The kind of declarator.  */
  شمار c_declarator_قسم قسم;
  location_t id_loc; /* Currently only set for cdk_id, cdk_array. */
  /* Except for cdk_id, the contained declarator.  For cdk_id, NULL.  */
  ساخت c_declarator *declarator;
  اتحاد {
    /* For identifiers.  */
    ساخت {
      /* An IDENTIFIER_NODE, or NULL_TREE if an abstract
	 declarator.  */
      درخت id;
      /* Any attributes (which apply to the declaration rather than to
	 the type described by the outer declarators).  */
      درخت attrs;
    } id;
    /* For functions.  */
    ساخت c_arg_info *arg_info;
    /* For arrays.  */
    ساخت {
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
    صحیح اشارہ_گر_quals;
    /* For attributes.  */
    درخت attrs;
  } u;
};

/* A type name.  */
ساخت c_type_name {
  /* The declaration specifiers.  */
  ساخت c_declspecs *specs;
  /* The declarator.  */
  ساخت c_declarator *declarator;
};

/* A parameter.  */
ساخت c_parm {
  /* The declaration specifiers, minus any prefix attributes.  */
  ساخت c_declspecs *specs;
  /* The attributes.  */
  درخت attrs;
  /* The declarator.  */
  ساخت c_declarator *declarator;
  /* The location of the parameter.  */
  location_t loc;
};

/* Used when parsing an enum.  Initialized by start_enum.  */
ساخت c_enum_contents
{
  /* While defining an enum type, this is 1 plus the last enumerator
     constant value.  */
  درخت enum_اگلا_قدر;

  /* The enumeration type itself.  */
  درخت enum_type;

  /* Nonzero means that there was overflow computing enum_next_value.  */
  صحیح enum_حد_سے_تجاوز;
};

/* A type of reference to a static identifier in an inline
   function.  */
شمار c_inline_static_type {
  /* Identifier with internal linkage used in function that may be an
     inline definition (i.e., file-scope static).  */
  csi_اندرونی,
  /* Modifiable object with static storage duration defined in
     function that may be an inline definition (i.e., local
     static).  */
  csi_modifiable
};

/* Record details of decls possibly used inside sizeof or typeof.  */
ساخت maybe_مستعمل_decl
{
  /* The decl.  */
  درخت decl;
  /* The level seen at (in_sizeof + in_typeof + in_countof + in_generic).  */
  صحیح level;
  /* Seen in address-of.  */
  bool پتہ;
  /* The next one at this level or above, or NULL.  */
  ساخت maybe_مستعمل_decl *اگلا;
};


/* in c-parser.cc */
ساخت c_درخت_token_vec;
خارجی خالی c_parse_init (خالی);
خارجی bool c_keyword_starts_typename (شمار rid keyword);

/* in c-aux-info.cc */
خارجی خالی gen_aux_info_ریکارڈ (درخت, صحیح, صحیح, صحیح);

/* in c-decl.cc */
ساخت c_spot_bindings;
class c_struct_parse_info;
خارجی ساخت obstack parser_obstack;
/* Set to IN_ITERATION_STMT if parsing an iteration-statement,
   to IN_OMP_BLOCK if parsing OpenMP structured block and
   IN_OMP_FOR if parsing OpenMP loop.  If parsing a switch statement,
   this is bitwise ORed with IN_SWITCH_STMT, unless parsing an
   iteration-statement, OpenMP block or loop within that switch.
   If the innermost iteration/switch statement is named, IN_NAMED_STMT
   is additionally bitwise ORed into it.  */
#تعریف_کرو اندر_SWITCH_STMT		1
#تعریف_کرو اندر_ITERATION_STMT	2
#تعریف_کرو اندر_OMP_بلاک		4
#تعریف_کرو اندر_OMP_FOR		8
#تعریف_کرو اندر_OBJC_FOREACH		16
#تعریف_کرو اندر_NAMED_STMT		32
خارجی غیرعلامتی حرف اندر_statement;

خارجی bool switch_statement_break_نظر_آیا_p;

خارجی bool global_bindings_p (خالی);
خارجی درخت pushdecl (درخت);
خارجی غیرعلامتی صحیح آغاز_underspecified_init (location_t, درخت);
خارجی خالی اختتام_underspecified_init (درخت, غیرعلامتی صحیح);
خارجی خالی ڈالو_scope (خالی);
خارجی درخت نکالو_scope (خالی);
خارجی خالی c_mark_decl_jump_unsafe_اندر_current_scope ();
خارجی خالی c_bindings_آغاز_stmt_اظہاریہ (ساخت c_spot_bindings *);
خارجی خالی c_bindings_انتہا_stmt_اظہاریہ (ساخت c_spot_bindings *);

خارجی خالی ریکارڈ_inline_static (location_t, درخت, درخت,
				  شمار c_inline_static_type);
خارجی خالی c_init_decl_processing (خالی);
خارجی خالی c_print_identifier (FILE *, درخت, صحیح);
خارجی صحیح quals_from_declspecs (ثابت ساخت c_declspecs *);
خارجی ساخت c_declarator *build_array_declarator (location_t, درخت,
    						    ساخت c_declspecs *,
						    bool, bool);
خارجی درخت build_enumerator (location_t, location_t, ساخت c_enum_contents *,
			      درخت, درخت);
خارجی درخت check_for_loop_decls (location_t, bool);
خارجی خالی mark_forward_parm_decls (خالی);
خارجی خالی declare_parm_level (خالی);
خارجی خالی undeclared_variable (location_t, درخت);
خارجی درخت lookup_label_for_goto (location_t, درخت);
خارجی درخت declare_label (درخت);
خارجی درخت define_label (location_t, درخت);
خارجی ساخت c_spot_bindings *c_get_switch_bindings (خالی);
خارجی خالی c_release_switch_bindings (ساخت c_spot_bindings *);
خارجی bool c_check_switch_jump_warnings (ساخت c_spot_bindings *,
					  location_t, location_t);
خارجی خالی اختتام_decl (درخت, location_t, درخت, درخت, درخت);
خارجی درخت اختتام_enum (درخت, درخت, درخت);
خارجی خالی اختتام_function (location_t = داخلہ_location);
خارجی درخت اختتام_struct (location_t, درخت, درخت, درخت,
			   class c_struct_parse_info *,
			   درخت *اظہاریہ = تہی);
خارجی درخت c_simulate_enum_decl (location_t, ثابت حرف *,
				  vec<string_int_pair> *);
خارجی درخت c_simulate_ریکارڈ_decl (location_t, ثابت حرف *,
				    array_قاش<ثابت درخت>);
خارجی ساخت c_arg_info *build_arg_info (خالی);
خارجی ساخت c_arg_info *get_parm_info (bool, درخت);
خارجی درخت grokfield (location_t, ساخت c_declarator *,
		       ساخت c_declspecs *, درخت, درخت *, درخت *);
خارجی درخت groktypename (ساخت c_type_name *, درخت *, bool *);
خارجی درخت grokgenassoc (ساخت c_type_name *);
خارجی درخت grokparm (ثابت ساخت c_parm *, درخت *);
خارجی درخت implicitly_declare (location_t, درخت);
خارجی خالی keep_اگلا_level (خالی);
خارجی خالی pending_xref_error (خالی);
خارجی خالی c_ڈالو_function_context (خالی);
خارجی خالی c_نکالو_function_context (خالی);
خارجی خالی ڈالو_parm_decl (ثابت ساخت c_parm *, درخت *);
خارجی ساخت c_declarator *سیٹ_array_declarator_inner (ساخت c_declarator *,
							ساخت c_declarator *);
خارجی درخت c_builtin_function (درخت);
خارجی درخت c_builtin_function_ext_scope (درخت);
خارجی درخت c_simulate_builtin_function_decl (درخت);
خارجی خالی c_warn_غیر_مستعمل_اوصاف (درخت);
خارجی درخت c_warn_type_اوصاف (درخت, درخت);
خارجی خالی shadow_لیبل (ثابت ساخت c_declspecs *);
خارجی خالی shadow_لیبل_warned (ثابت ساخت c_declspecs *, صحیح);
خارجی درخت آغاز_enum (location_t, ساخت c_enum_contents *, درخت, درخت,
			bool potential_nesting_p);
خارجی bool آغاز_function (ساخت c_declspecs *, ساخت c_declarator *, درخت);
خارجی درخت آغاز_decl (ساخت c_declarator *, ساخت c_declspecs *, bool,
			درخت, bool = true, location_t * = تہی);
خارجی درخت آغاز_struct (location_t, شمار درخت_رمز_2, درخت,
			  class c_struct_parse_info **);
خارجی خالی store_parm_decls (خالی);
خارجی خالی store_parm_decls_from (ساخت c_arg_info *);
خارجی خالی عارضی_store_parm_decls (درخت, درخت);
خارجی خالی عارضی_نکالو_parm_decls (خالی);
خارجی درخت xref_لیبل (شمار درخت_رمز_2, درخت);
خارجی ساخت c_typespec parser_xref_لیبل (location_t, شمار درخت_رمز_2, درخت,
					  bool, درخت, bool);
خارجی ساخت c_parm *build_c_parm (ساخت c_declspecs *, درخت,
				    ساخت c_declarator *, location_t);
خارجی ساخت c_declarator *build_attrs_declarator (درخت,
						    ساخت c_declarator *);
خارجی ساخت c_declarator *build_function_declarator (ساخت c_arg_info *,
						       ساخت c_declarator *);
خارجی ساخت c_declarator *build_id_declarator (درخت);
خارجی ساخت c_declarator *make_اشارہ_گر_declarator (ساخت c_declspecs *,
						     ساخت c_declarator *);
خارجی ساخت c_declspecs *build_null_declspecs (خالی);
خارجی ساخت c_declspecs *declspecs_جوڑو_qual (location_t,
					       ساخت c_declspecs *, درخت);
خارجی ساخت c_declspecs *declspecs_جوڑو_type (location_t,
					       ساخت c_declspecs *,
					       ساخت c_typespec);
خارجی ساخت c_declspecs *declspecs_جوڑو_scspec (location_t,
						 ساخت c_declspecs *, درخت);
خارجی ساخت c_declspecs *declspecs_جوڑو_attrs (location_t,
						ساخت c_declspecs *, درخت);
خارجی ساخت c_declspecs *declspecs_جوڑو_addrspace (location_t,
						    ساخت c_declspecs *,
						    addr_space_t);
خارجی ساخت c_declspecs *declspecs_جوڑو_alignas (location_t,
						  ساخت c_declspecs *, درخت);
خارجی ساخت c_declspecs *اختتام_declspecs (ساخت c_declspecs *);
خارجی سائز_t c_درخت_سائز (شمار درخت_رمز_2);
خارجی صحیح c_get_loop_نام (درخت, bool, درخت *);
خارجی خالی c_release_loop_نام (صحیح);
خارجی درخت c_اختتام_bc_name (location_t, درخت, bool);

/* in c-objc-common.cc */
خارجی bool c_objc_common_init (خالی);
خارجی bool c_missing_noreturn_ok_p (درخت);
خارجی bool c_warn_غیر_مستعمل_global_decl (const_درخت);
خارجی خالی c_initialize_diagnostics (diagnostics::context *);
خارجی bool c_var_mod_p (درخت x, درخت fn);
خارجی alias_سیٹ_type c_get_alias_سیٹ (درخت);
خارجی صحیح c_type_dwarf_attribute (const_درخت, صحیح);
خارجی درخت c_enum_underlying_بنیاد_type (const_درخت);

/* in c-typeck.cc */
خارجی صحیح اندر_alignof;
خارجی صحیح اندر_sizeof;
خارجی صحیح اندر_countof;
خارجی صحیح اندر_typeof;
خارجی صحیح اندر_generic;
خارجی bool c_اندر_omp_for;
خارجی bool c_omp_array_section_p;

خارجی درخت c_آخری_sizeof_arg;
خارجی location_t c_آخری_sizeof_loc;

خارجی ساخت c_switch *c_switch_ڈھیر;

خارجی bool null_اشارہ_گر_constant_p (const_درخت);


اندرونی bool
c_type_variably_modified_p (درخت t)
{
  اگر (error_mark_گرہ == t)
    واپس false;
  اگر (C_TYPE_VARIABLY_MODIFIED (t))
    واپس true;
  اگر (TYPE_STRUCTURAL_EQUALITY_P (t))
    {
      /* The flag may not have been set yet because of incomplete
	 structure or union types completed later.  */
      انتخاب (درخت_رمز (t))
	{
	حالت ARRAY_TYPE:
	حالت FUNCTION_TYPE:
	حالت اشارہ_گر_TYPE:
	  /* Recurse.  */
	  اگر (c_type_variably_modified_p (درخت_TYPE (t)))
	    {
	      C_TYPE_VARIABLY_MODIFIED (t) = 1;
	      واپس true;
	    }
	  توڑو;
	طےشدہ:
	  توڑو;
	}
    }
  واپس false;
}

اندرونی bool
c_type_unspecified_p (درخت t)
{
  واپس error_mark_گرہ != t
	 && C_TYPE_VARIABLE_سائز (t) && درخت_رمز (t) == ARRAY_TYPE
	 && TYPE_DOMAIN (t) && TYPE_MAX_قدر (TYPE_DOMAIN (t))
	 && درخت_رمز (TYPE_MAX_قدر (TYPE_DOMAIN (t))) == COMPOUND_اظہاریہ
	 && integer_zerop (درخت_عملیہ (TYPE_MAX_قدر (TYPE_DOMAIN (t)), 0))
	 && integer_zerop (درخت_عملیہ (TYPE_MAX_قدر (TYPE_DOMAIN (t)), 1));
}

خارجی bool zero_لمبائی_array_type_p (const_درخت type);
خارجی bool char_type_p (درخت);
خارجی درخت c_type_لیبل (const_درخت t);
خارجی درخت c_objc_common_truthvalue_conversion (location_t, درخت,
						 درخت = integer_type_گرہ);
خارجی درخت require_complete_type (location_t, درخت);
خارجی bool same_translation_unit_p (const_درخت, const_درخت);
خارجی bool comptypes (درخت, درخت);
خارجی bool comptypes_same_p (درخت, درخت);
خارجی bool comptypes_equiv_p (درخت, درخت);
خارجی bool comptypes_check_enum_int (درخت, درخت, bool *);
خارجی bool c_mark_addressable (درخت, bool = false, bool = false);
خارجی خالی c_incomplete_type_error (location_t, const_درخت, const_درخت);
خارجی درخت c_type_promotes_مقصد (درخت);
خارجی ساخت c_اظہاریہ default_function_array_conversion (location_t,
							ساخت c_اظہاریہ);
خارجی ساخت c_اظہاریہ default_function_array_read_conversion (location_t,
							     ساخت c_اظہاریہ);
خارجی ساخت c_اظہاریہ convert_lvalue_مقصد_rvalue (location_t, ساخت c_اظہاریہ,
					       bool, bool, bool = false);
خارجی درخت decl_constant_قدر_1 (درخت, bool);
خارجی خالی mark_exp_read (درخت);
خارجی درخت مرکب_type (درخت, درخت);
خارجی درخت lookup_میدان (const_درخت, درخت);
خارجی درخت build_component_ref (location_t, درخت, درخت, location_t,
				 location_t);
خارجی درخت handle_counted_by_for_component_ref (location_t, درخت);
خارجی درخت build_array_ref (location_t, درخت, درخت);
خارجی درخت build_omp_array_section (location_t, درخت, درخت, درخت);
خارجی درخت build_external_ref (location_t, درخت, bool, درخت *);
خارجی خالی نکالو_maybe_مستعمل (bool);
خارجی ساخت maybe_مستعمل_decl *save_maybe_مستعمل ();
خارجی خالی restore_maybe_مستعمل (ساخت maybe_مستعمل_decl *);
خارجی خالی mark_decl_مستعمل (درخت, bool);
خارجی ساخت c_اظہاریہ c_اظہاریہ_sizeof_اظہاریہ (location_t, ساخت c_اظہاریہ);
خارجی ساخت c_اظہاریہ c_اظہاریہ_sizeof_type (location_t, ساخت c_type_name *);
خارجی ساخت c_اظہاریہ c_اظہاریہ_countof_اظہاریہ (location_t, ساخت c_اظہاریہ);
خارجی ساخت c_اظہاریہ c_اظہاریہ_countof_type (location_t loc,
					  ساخت c_type_name *);
خارجی ساخت c_اظہاریہ c_اظہاریہ_maxof_type (location_t loc, ساخت c_type_name *);
خارجی ساخت c_اظہاریہ c_اظہاریہ_minof_type (location_t loc, ساخت c_type_name *);
خارجی ساخت c_اظہاریہ parser_build_unary_op (location_t, شمار درخت_رمز_2,
    					    ساخت c_اظہاریہ);
خارجی ساخت c_اظہاریہ parser_build_ثنائی_op (location_t,
    					     شمار درخت_رمز_2, ساخت c_اظہاریہ,
					     ساخت c_اظہاریہ, درخت);
خارجی درخت build_conditional_اظہاریہ (location_t, درخت, bool, درخت, درخت,
				    location_t, درخت, درخت, location_t);
خارجی درخت build_compound_اظہاریہ (location_t, درخت, درخت);
خارجی درخت c_cast_اظہاریہ (location_t, ساخت c_type_name *, درخت);
خارجی درخت build_c_cast (location_t, درخت, درخت);
خارجی خالی store_init_قدر (location_t, درخت, درخت, درخت);
خارجی خالی maybe_warn_string_init (location_t, درخت, ساخت c_اظہاریہ);
خارجی خالی آغاز_init (درخت, درخت, bool, bool, rich_location *);
خارجی خالی اختتام_init (خالی);
خارجی خالی really_آغاز_incremental_init (درخت);
خارجی خالی اختتام_implicit_inits (location_t, ساخت obstack *);
خارجی خالی ڈالو_init_level (location_t, صحیح, ساخت obstack *);
خارجی ساخت c_اظہاریہ نکالو_init_level (location_t, صحیح, ساخت obstack *,
				     location_t);
خارجی خالی سیٹ_init_اشاریہ (location_t, درخت, درخت, ساخت obstack *);
خارجی خالی سیٹ_init_label (location_t, درخت, location_t, ساخت obstack *);
غیرعلامتی c_maybe_optimize_large_byte_initializer (خالی);
خارجی خالی process_init_element (location_t, ساخت c_اظہاریہ, bool,
				  ساخت obstack *);
خارجی درخت build_compound_literal (location_t, درخت, درخت, bool,
				    غیرعلامتی صحیح, ساخت c_declspecs *);
خارجی خالی check_compound_literal_type (location_t, ساخت c_type_name *);
خارجی درخت c_آغاز_switch (location_t, location_t, درخت, bool, درخت);
خارجی خالی c_اختتام_switch (درخت, درخت);
خارجی درخت build_asm_اظہاریہ (location_t, درخت, درخت, درخت, درخت, درخت, bool,
			    bool);
خارجی درخت build_asm_stmt (bool, درخت);
خارجی صحیح c_types_compatible_p (درخت, درخت);
خارجی درخت c_begin_compound_stmt (bool);
خارجی درخت c_انتہا_compound_stmt (location_t, درخت, bool);
خارجی خالی c_اختتام_if_stmt (location_t, درخت, درخت, درخت);
خارجی خالی c_اختتام_loop (location_t, location_t, درخت, location_t, درخت,
			   درخت, درخت, درخت, bool);
خارجی درخت c_begin_stmt_اظہاریہ (خالی);
خارجی درخت c_اختتام_stmt_اظہاریہ (location_t, درخت);
خارجی درخت c_process_اظہاریہ_stmt (location_t, درخت);
خارجی درخت c_اختتام_اظہاریہ_stmt (location_t, درخت);
خارجی درخت c_اختتام_return (location_t, درخت, درخت, bool = false);
خارجی درخت c_اختتام_bc_stmt (location_t, درخت, bool, درخت);
خارجی درخت c_اختتام_goto_label (location_t, درخت);
خارجی درخت c_اختتام_goto_ptr (location_t, c_اظہاریہ val);
خارجی درخت c_اظہاریہ_مقصد_decl (درخت, bool *, bool *);
خارجی درخت c_اختتام_omp_construct (location_t, شمار درخت_رمز_2, درخت, درخت);
خارجی درخت c_اختتام_oacc_ڈیٹا (location_t, درخت, درخت);
خارجی درخت c_اختتام_oacc_host_ڈیٹا (location_t, درخت, درخت);
خارجی درخت c_begin_omp_parallel (خالی);
خارجی درخت c_اختتام_omp_parallel (location_t, درخت, درخت);
خارجی درخت c_begin_omp_task (خالی);
خارجی درخت c_اختتام_omp_task (location_t, درخت, درخت);
خارجی خالی c_اختتام_omp_cancel (location_t, درخت);
خارجی خالی c_اختتام_omp_cancellation_نقطہ (location_t, درخت);
خارجی درخت c_اختتام_omp_clauses (درخت, شمار c_omp_region_type);
خارجی درخت c_omp_اختتام_mapper_clauses (درخت);
خارجی درخت c_omp_mapper_lookup (درخت, درخت);
خارجی درخت c_omp_نکالو_mapper_directive (درخت);
خارجی درخت c_omp_map_array_section (location_t, درخت);
خارجی درخت c_build_va_arg (location_t, درخت, location_t, درخت, درخت);
خارجی درخت c_اختتام_transaction (location_t, درخت, صحیح);
خارجی bool c_درخت_equal (درخت, درخت);
خارجی درخت c_build_function_call_vec (location_t, ثابت vec<location_t>&,
				       درخت, vec<درخت, va_gc> *,
				       vec<درخت, va_gc> *);
خارجی درخت c_omp_clause_copy_ctor (درخت, درخت, درخت);
خارجی درخت c_reconstruct_complex_type (درخت, درخت);
خارجی درخت c_type_canonical (درخت);
خارجی درخت c_build_type_attribute_variant (درخت ntype, درخت attrs);
خارجی درخت c_build_اشارہ_گر_type (درخت type);
خارجی درخت c_build_array_type (درخت type, درخت domain);
خارجی درخت c_build_array_type_unspecified (درخت type);
خارجی درخت c_build_array_type_zero_سائز (درخت type);
خارجی درخت c_build_function_type (درخت type, درخت دلائل, bool no = false);
خارجی درخت c_build_اشارہ_گر_type_for_منوال (درخت type, machine_منوال منوال, bool m);

/* Set to 0 at beginning of a function definition, set to 1 if
   a return statement that specifies a return value is seen.  */

خارجی صحیح current_function_returns_قدر;

/* Set to 0 at beginning of a function definition, set to 1 if
   a return statement with no argument is seen.  */

خارجی صحیح current_function_returns_null;

/* Set to 0 at beginning of a function definition, set to 1 if
   a call to a noreturn function is seen.  */

خارجی صحیح current_function_returns_abnormally;

/* In c-decl.cc */

/* Tell the binding oracle what kind of binding we are looking for.  */

شمار c_oracle_request
{
  C_ORACLE_علامت,
  C_ORACLE_لیبل,
  C_ORACLE_LABEL
};

/* If this is non-NULL, then it is a "binding oracle" which can lazily
   create bindings when needed by the C compiler.  The oracle is told
   the name and type of the binding to create.  It can call pushdecl
   or the like to ensure the binding is visible; or do nothing,
   leaving the binding untouched.  c-decl.cc takes note of when the
   oracle has been called and will not call it again if it fails to
   create a given binding.  */

قسمتعریف خالی c_binding_oracle_function (شمار c_oracle_request, درخت identifier);

خارجی c_binding_oracle_function *c_binding_oracle;

خارجی خالی c_اختتام_incomplete_decl (درخت);
خارجی درخت c_omp_reduction_id (شمار درخت_رمز_2, درخت);
خارجی درخت c_omp_reduction_decl (درخت);
خارجی درخت c_omp_reduction_lookup (درخت, درخت);
خارجی درخت c_check_omp_declare_reduction_r (درخت *, صحیح *, خالی *);
خارجی درخت c_omp_mapper_id (درخت);
خارجی درخت c_omp_mapper_decl (درخت);
خارجی خالی c_omp_جائزہ_mapper_bindings (location_t, درخت *, درخت);
خارجی bool c_check_اندر_current_scope (درخت);
خارجی خالی c_pushtag (location_t, درخت, درخت);
خارجی خالی c_bind (location_t, درخت, bool);
خارجی bool لیبل_exists_p (شمار درخت_رمز_2, درخت);

خارجی خالی verify_counted_by_for_چوٹی_anonymous_type (درخت);

/* In c-errors.cc */
خارجی bool pedwarn_c90 (location_t, diagnostics::option_id, ثابت حرف *, ...)
    ATTRIBUTE_GCC_DIAG(3,4);
خارجی bool pedwarn_c99 (location_t, diagnostics::option_id, ثابت حرف *, ...)
    ATTRIBUTE_GCC_DIAG(3,4);
خارجی bool pedwarn_c11 (location_t, diagnostics::option_id, ثابت حرف *, ...)
    ATTRIBUTE_GCC_DIAG(3,4);
خارجی bool pedwarn_c23 (location_t, diagnostics::option_id, ثابت حرف *, ...)
    ATTRIBUTE_GCC_DIAG(3,4);
خارجی خالی جوڑو_note_about_new_keyword (location_t loc,
					درخت keyword_id);

خارجی خالی
سیٹ_c_اظہاریہ_ماخذ_range (c_اظہاریہ *اظہاریہ,
			 location_t آغاز, location_t اختتام);

خارجی خالی
سیٹ_c_اظہاریہ_ماخذ_range (c_اظہاریہ *اظہاریہ,
			 ماخذ_range src_range);

/* In c-fold.cc */
خارجی vec<درخت> incomplete_ریکارڈ_decls;

خارجی ثابت حرف *c_get_sarif_ماخذ_language (ثابت حرف *filename);

خارجی ثابت ساخت scoped_attribute_specs std_attribute_جدول;

#اگر CHECKING_P
namespace selftest {
  خارجی خالی تسلسل_c_tests (خالی);
} // namespace selftest
#اگر_ختم /* #if CHECKING_P */


#اگر_ختم /* ! GCC_C_TREE_H */
