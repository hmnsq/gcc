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

#جيڪڏهن_وصف_نه_ٿيل GCC_C_وڻ_H
#وصف_ڪريو GCC_C_وڻ_H

#ضمن "c-family/c-common.h"
#ضمن "diagnostic.h"

/* struct lang_identifier is private to c-decl.cc, but langhooks.cc needs to
   know how big it is.  This is sanity-checked in c-decl.cc.  */
#وصف_ڪريو C_SIZEOF_STRUCT_LANG_IDENTIFIER \
  (حجم (بنية c_common_identifier) + 3 * حجم (فراغ *))

/* In a RECORD_TYPE or UNION_TYPE, nonzero if any component is read-only.  */
#وصف_ڪريو C_TYPE_FIELDS_READONLY(TYPE) وڻ_LANG_FLAG_1 (TYPE)

/* In a RECORD_TYPE or UNION_TYPE, nonzero if any component is volatile.  */
#وصف_ڪريو C_TYPE_FIELDS_VOLATILE(TYPE) وڻ_LANG_FLAG_2 (TYPE)

/* In a RECORD_TYPE or UNION_TYPE, nonzero if any component is
   volatile, restrict-qualified or atomic; that is, has a type not
   permitted for a constexpr object.  */
#وصف_ڪريو C_TYPE_FIELDS_NON_CONSTEXPR(TYPE) وڻ_LANG_FLAG_4 (TYPE)

/* In a RECORD_TYPE or UNION_TYPE, nonzero if any component has a
   counted_by attribute.  */
#وصف_ڪريو C_TYPE_FIELDS_HAS_COUNTED_BY(TYPE) TYPE_LANG_FLAG_3 (TYPE)

/* In a RECORD_TYPE or UNION_TYPE or ENUMERAL_TYPE
   nonzero if the definition of the type has already started.  */
#وصف_ڪريو C_TYPE_BEING_DEFINED(TYPE) TYPE_LANG_FLAG_0 (TYPE)

/* In an incomplete RECORD_TYPE, UNION_TYPE or ENUMERAL_TYPE, a list of
   variable declarations whose type would be completed by completing
   that type.  */
#وصف_ڪريو C_TYPE_INCOMPLETE_VARS(TYPE) \
  TYPE_LANG_جڳهه_1 (وڻ_CHECK4 (TYPE, رڪارڊ_TYPE, UNION_TYPE, \
				 QUAL_UNION_TYPE, ENUMERAL_TYPE))

/* In an IDENTIFIER_NODE, nonzero if this identifier is actually a
   keyword.  C_RID_CODE (node) is then the RID_* value of the keyword.  */
#وصف_ڪريو C_IS_RESERVED_لفظ(ID) وڻ_LANG_FLAG_0 (ID)

/* Record whether a type or decl was written with nonconstant size.
   Note that TYPE_SIZE may have simplified to a constant.  */
#وصف_ڪريو C_TYPE_VARIABLE_سائيز(TYPE) TYPE_LANG_FLAG_1 (TYPE)
#وصف_ڪريو C_DECL_VARIABLE_سائيز(TYPE) DECL_LANG_FLAG_0 (TYPE)

/* Record whether a type is variably modified. */
#وصف_ڪريو C_TYPE_VARIABLY_MODIFIED(TYPE) TYPE_LANG_FLAG_6 (TYPE)


/* Record whether a type is defined inside a struct or union type.
   This is used for -Wc++-compat. */
#وصف_ڪريو C_TYPE_DEFINED_اندريون_STRUCT(TYPE) TYPE_LANG_FLAG_2 (TYPE)

/* Record whether a typedef for type `int' was actually `signed int'.  */
#وصف_ڪريو C_TYPEDEF_EXPLICITLY_SIGNED(EXP) DECL_LANG_FLAG_1 (EXP)

/* For a FUNCTION_DECL, nonzero if it was defined without an explicit
   return type.  */
#وصف_ڪريو C_FUNCTION_IMPLICIT_INT(EXP) DECL_LANG_FLAG_1 (EXP)

/* For a FUNCTION_DECL, nonzero if it was an implicit declaration.  */
#وصف_ڪريو C_DECL_IMPLICIT(EXP) DECL_LANG_FLAG_2 (EXP)

/* For a PARM_DECL, nonzero if it was declared as an array.  */
#وصف_ڪريو C_ARRAY_PARAMETER(ڳنڍ_2) DECL_LANG_FLAG_0 (ڳنڍ_2)

/* For FUNCTION_DECLs, evaluates true if the decl is a nested
   function that requires a non-local context.  */
#وصف_ڪريو C_FUNC_NONLOCAL_CONTEXT(EXP)		\
  DECL_LANG_FLAG_4 (FUNCTION_DECL_CHECK (EXP))

/* For FUNCTION_DECLs, evaluates true if the decl is built-in but has
   been declared.  */
#وصف_ڪريو C_DECL_DECLARED_BUILTIN(EXP)		\
  DECL_LANG_FLAG_3 (FUNCTION_DECL_CHECK (EXP))

/* For FUNCTION_DECLs, evaluates true if the decl is built-in, has a
   built-in prototype and does not have a non-built-in prototype.  */
#وصف_ڪريو C_DECL_BUILTIN_PROTOTYPE(EXP)		\
  DECL_LANG_FLAG_6 (FUNCTION_DECL_CHECK (EXP))

/* For LABEL_DECLs marks canonical name of a loop.  */
#وصف_ڪريو C_DECL_LOOP_NAME(EXP) DECL_LANG_FLAG_3 (LABEL_DECL_CHECK (EXP))

/* For LABEL_DECLs marks canonical name of a switch.  During parsing of
   ObjC foreach named loop both C_DECL_LOOP_NAME and C_DECL_SWITCH_NAME
   are temporarily set.  */
#وصف_ڪريو C_DECL_SWITCH_NAME(EXP) DECL_LANG_FLAG_5 (LABEL_DECL_CHECK (EXP))

/* For LABEL_DECLs marks canonical name of a loop or switch being
   valid for use in break identifier or continue identifier statements.  */
#وصف_ڪريو C_DECL_LOOP_SWITCH_NAME_VALID(EXP) \
  DECL_LANG_FLAG_6 (LABEL_DECL_CHECK (EXP))

/* For LABEL_DECLs marks canonical loop or switch names which were actually
   used in one or more break identifier or continue identifier statements.  */
#وصف_ڪريو C_DECL_LOOP_SWITCH_NAME_استعمال_ٿيل(EXP) \
  DECL_LANG_FLAG_8 (LABEL_DECL_CHECK (EXP))

/* Record whether a decl was declared register.  This is strictly a
   front-end flag, whereas DECL_REGISTER is used for code generation;
   they may differ for structures with volatile fields.  */
#وصف_ڪريو C_DECL_رجسٽر(EXP) \
  DECL_LANG_FLAG_4 (وڻ_NOT_CHECK (EXP, FUNCTION_DECL))

/* Record whether a decl was used in an expression anywhere except an
   unevaluated operand of sizeof / typeof / alignof.  This is only
   used for functions declared static but not defined, though outside
   sizeof and typeof it is set for other function decls as well.  */
#وصف_ڪريو C_DECL_استعمال_ٿيل(EXP) DECL_LANG_FLAG_5 (FUNCTION_DECL_CHECK (EXP))

/* Record whether a variable has been declared threadprivate by
   #pragma omp threadprivate.  */
#وصف_ڪريو C_DECL_THREADPRIVATE_P(DECL) DECL_LANG_FLAG_3 (VAR_DECL_CHECK (DECL))

/* Set on VAR_DECLs for compound literals.  */
#وصف_ڪريو C_DECL_COMPOUND_LITERAL_P(DECL) \
  DECL_LANG_FLAG_5 (VAR_DECL_CHECK (DECL))

/* Set on decls used as placeholders for a C23 underspecified object
   definition.  */
#وصف_ڪريو C_DECL_UNDERSPECIFIED(DECL) DECL_LANG_FLAG_7 (DECL)

/* Set on VAR_DECLs declared as 'constexpr'.  */
#وصف_ڪريو C_DECL_DECLARED_CONSTEXPR(DECL) \
  DECL_LANG_FLAG_8 (VAR_DECL_CHECK (DECL))

/* Nonzero for a decl which either doesn't exist or isn't a prototype.
   N.B. Could be simplified if all built-in decls had complete prototypes
   (but this is presently difficult because some of them need FILE*).  */
#وصف_ڪريو C_DECL_ISNT_PROTOTYPE(EXP)			\
       (EXP == 0					\
	|| (!prototype_p (وڻ_TYPE (EXP))	\
	    && !fndecl_built_اندريون_p (EXP)))

/* For FUNCTION_TYPE, a hidden list of types of arguments.  The same as
   TYPE_ARG_TYPES for functions with prototypes, but created for functions
   without prototypes.  */
#وصف_ڪريو TYPE_ACTUAL_ARG_TYPES(ڳنڍ_2) \
  TYPE_LANG_جڳهه_1 (FUNCTION_TYPE_CHECK (ڳنڍ_2))

/* For a CONSTRUCTOR, whether some initializer contains a
   subexpression meaning it is not a constant expression.  */
#وصف_ڪريو CONSTRUCTOR_NON_CONST(اظهار_3) وڻ_LANG_FLAG_1 (CONSTRUCTOR_CHECK (اظهار_3))

/* For a SAVE_EXPR, nonzero if the operand of the SAVE_EXPR has already
   been folded.  */
#وصف_ڪريو SAVE_اظهار_FOLDED_P(EXP)	وڻ_LANG_FLAG_1 (SAVE_اظهار_CHECK (EXP))

/* Whether a type has boolean semantics: either a boolean type or an
   enumeration type with a boolean type as its underlying type.  */
#وصف_ڪريو C_BOOLEAN_TYPE_P(TYPE)						\
  (وڻ_ڪوڊ (TYPE) == BOOLEAN_TYPE					\
   || (وڻ_ڪوڊ (TYPE) == ENUMERAL_TYPE				\
       && ENUM_UNDERLYING_TYPE (TYPE) != NULL_وڻ			\
       && (وڻ_ڪوڊ (ENUM_UNDERLYING_TYPE (TYPE)) == BOOLEAN_TYPE	\
	   || c_hardbool_type_attr (TYPE))))

/* Record parser information about an expression that is irrelevant
   for code generation alongside a tree representing its value.  */
بنية c_اظهار
{
  /* The value of the expression.  */
  وڻ قدر;
  /* Record the original unary/binary operator of an expression, which may
     have been changed by fold, STRING_CST for unparenthesized string
     constants, C_MAYBE_CONST_EXPR for __builtin_constant_p calls
     (even if parenthesized), for subexpressions, and for non-constant
     initializers, or ERROR_MARK for other expressions (including
     parenthesized expressions).  */
  تعداد وڻ_ڪوڊ_2 original_ڪوڊ;
  /* If not NULL, the original type of an expression.  This will
     differ from the type of the value field for an enum constant.
     The type of an enum constant is a plain integer type, but this
     field will be the enum type.  */
  وڻ original_type;

  /* The source range of this expression.  This is redundant
     for node values that have locations, but not all node kinds
     have locations (e.g. constants, and references to params, locals,
     etc), so we stash a copy here.  */
  ذريعو_range src_range;

  /* True if this was directly from a decimal constant token.  */
  bool m_decimal : 1;

  /* Access to the first and last locations within the source spelling
     of this expression.  */
  location_t get_شروعات () ثابت { أرجع src_range.m_شروعات; }
  location_t get_پڄاڻي () ثابت { أرجع src_range.m_پڄاڻي; }

  location_t get_location () ثابت
  {
    إذا (اظهار_HAS_LOCATION (قدر))
      أرجع اظهار_LOCATION (قدر);
    وإلا
      أرجع make_location (get_شروعات (), get_شروعات (), get_پڄاڻي ());
  }

  /* Set the value to error_mark_node whilst ensuring that src_range
     and m_decimal are initialized.  */
  فراغ سيٽ_error ()
  {
    قدر = error_mark_ڳنڍ;
    src_range.m_شروعات = UNKNOWN_LOCATION;
    src_range.m_پڄاڻي = UNKNOWN_LOCATION;
    m_decimal = 0;
  }
};

/* Type alias for struct c_expr. This allows to use the structure
   inside the VEC types.  */
تعريفنوع بنية c_اظهار c_اظهار_t;

/* A kind of type specifier.  Note that this information is currently
   only used to distinguish tag definitions, tag references and typeof
   uses.  */
تعداد c_typespec_قسم {
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
  تعداد c_typespec_قسم قسم;
  /* Whether the expression has operands suitable for use in constant
     expressions.  */
  bool اظهار_const_operands;
  /* Whether the type specifier includes an enum type specifier (that
     is, ": specifier-qualifier-list" in a declaration using
     "enum").  */
  bool has_enum_type_specifier;
  /* The specifier itself.  */
  وڻ spec;
  /* An expression to be evaluated before the type specifier, in the
     case of typeof specifiers, or NULL otherwise or if no such
     expression is required for a particular typeof specifier.  In
     particular, when typeof is applied to an expression of variably
     modified type, that expression must be evaluated in order to
     determine array sizes that form part of the type, but the
     expression itself (as opposed to the array sizes) forms no part
     of the type and so needs to be recorded separately.  */
  وڻ اظهار;
};

/* A storage class specifier.  */
تعداد c_storage_class {
  csc_none,
  csc_auto,
  csc_extern,
  csc_رجسٽر,
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
تعداد c_declspec_لفظ {
  cdw_typespec /* A catch-all for a typespec.  */,
  cdw_storage_class  /* A catch-all for a storage class */,
  cdw_خاصيتون,
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
  cdw_پتو_space,
  cdw_gimple,
  cdw_rtl,
  cdw_عدد_جو_elements /* This one must always be the last
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
  location_t locations[cdw_عدد_جو_elements];
  /* The type specified, if a single type specifier such as a struct,
     union or enum specifier, typedef name or typeof specifies the
     whole type, or NULL_TREE if none or a keyword such as "void" or
     "char" is used.  Does not include qualifiers.  */
  وڻ type;
  /* Any expression to be evaluated before the type, from a typeof
     specifier.  */
  وڻ اظهار;
  /* The attributes from a typedef decl.  */
  وڻ decl_attr;
  /* When parsing, the GNU attributes and prefix standard attributes.
     Outside the parser, this will be NULL; attributes (possibly from
     multiple lists) will be passed separately.  */
  وڻ attrs;
  /* When parsing, postfix standard attributes (which appertain to the
     type specified by the preceding declaration specifiers, unlike
     prefix standard attributes which appertain to the declaration or
     declarations as a whole).  */
  وڻ postfix_attrs;
  /* The pass to start compiling a __GIMPLE or __RTL function with.  */
  حرف *gimple_or_rtl_pass;
  /* ENTRY BB count.  */
  profile_ڳڻپ داخلا_bb_ڳڻپ;
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
  تعداد c_typespec_keyword typespec_لفظ : 8;
  /* The kind of type specifier if one has been seen, ctsk_none
     otherwise.  */
  تعداد c_typespec_قسم typespec_قسم : 4;
  تعداد c_declspec_il declspec_il : 3;
  /* Whether any expressions in typeof specifiers may appear in
     constant expressions.  */
  bool اظهار_const_operands : 1;
  /* Whether any declaration specifiers have been seen at all.  */
  bool declspecs_ڏٺل_p : 1;
  /* Whether any declaration specifiers other than standard attributes
     have been seen at all.  If only standard attributes have been
     seen, this is an attribute-declaration.  */
  bool non_std_attrs_ڏٺل_p : 1;
  /* Whether something other than a storage class specifier or
     attribute has been seen.  This is used to warn for the
     obsolescent usage of storage class specifiers other than at the
     start of the list.  (Doing this properly would require function
     specifiers to be handled separately from storage class
     specifiers.)  */
  bool non_sc_ڏٺل_p : 1;
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
  addr_space_t پتو_space;
};

/* The various kinds of declarators in C.  */
تعداد c_declarator_قسم {
  /* An identifier.  */
  cdk_id,
  /* A function.  */
  cdk_function,
  /* An array.  */
  cdk_array,
  /* A pointer.  */
  cdk_اشارو,
  /* Parenthesized declarator with nested attributes.  */
  cdk_attrs
};

بنية c_arg_ٽيگ {
  /* The argument name.  */
  وڻ id;
  /* The type of the argument.  */
  وڻ type;
};


/* Information about the parameters in a function declarator.  */
بنية c_arg_info {
  /* A list of parameter decls.  */
  وڻ parms;
  /* A list of structure, union and enum tags defined.  */
  vec<c_arg_ٽيگ, va_gc> *ٽيگ_فهرست;
  /* A list of argument types to go in the FUNCTION_TYPE.  */
  وڻ types;
  /* A list of non-parameter decls (notably enumeration constants)
     defined with the parameters.  */
  وڻ others;
  /* A compound expression of VLA sizes from the parameters, or NULL.
     In a function definition, these are used to ensure that
     side-effects in sizes of arrays converted to pointers (such as a
     parameter int i[n++]) take place; otherwise, they are
     ignored.  */
  وڻ pending_sizes;
  /* True when these arguments had [*].  */
  bool had_vla_unspec : 1;
  /* True when the arguments are a (...) prototype.  */
  bool no_named_دليلون_stdarg_p : 1;
  /* True when empty parentheses have been interpreted as (void) in C23 or
     later.  This is only for use by -Wtraditional and is no longer needed if
     -Wtraditional is removed.  */
  bool c23_خالي_جايون_parens : 1;
};

/* A declarator.  */
بنية c_declarator {
  /* The kind of declarator.  */
  تعداد c_declarator_قسم قسم;
  location_t id_loc; /* Currently only set for cdk_id, cdk_array. */
  /* Except for cdk_id, the contained declarator.  For cdk_id, NULL.  */
  بنية c_declarator *declarator;
  اتحاد {
    /* For identifiers.  */
    بنية {
      /* An IDENTIFIER_NODE, or NULL_TREE if an abstract
	 declarator.  */
      وڻ id;
      /* Any attributes (which apply to the declaration rather than to
	 the type described by the outer declarators).  */
      وڻ attrs;
    } id;
    /* For functions.  */
    بنية c_arg_info *arg_info;
    /* For arrays.  */
    بنية {
      /* The array dimension, or NULL for [] and [*].  */
      وڻ dimen;
      /* The qualifiers inside [].  */
      صحيح quals;
      /* The attributes (currently ignored) inside [].  */
      وڻ attrs;
      /* Whether [static] was used.  */
      bool static_p : 1;
      /* Whether [*] was used.  */
      bool vla_unspec_p : 1;
    } array;
    /* For pointers, the qualifiers on the pointer type.  */
    صحيح اشارو_quals;
    /* For attributes.  */
    وڻ attrs;
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
  وڻ attrs;
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
  وڻ enum_ايندڙ_قدر;

  /* The enumeration type itself.  */
  وڻ enum_type;

  /* Nonzero means that there was overflow computing enum_next_value.  */
  صحيح enum_حد_کان_مٿي;
};

/* A type of reference to a static identifier in an inline
   function.  */
تعداد c_inline_static_type {
  /* Identifier with internal linkage used in function that may be an
     inline definition (i.e., file-scope static).  */
  csi_اندروني,
  /* Modifiable object with static storage duration defined in
     function that may be an inline definition (i.e., local
     static).  */
  csi_modifiable
};

/* Record details of decls possibly used inside sizeof or typeof.  */
بنية maybe_استعمال_ٿيل_decl
{
  /* The decl.  */
  وڻ decl;
  /* The level seen at (in_sizeof + in_typeof + in_countof + in_generic).  */
  صحيح level;
  /* Seen in address-of.  */
  bool پتو;
  /* The next one at this level or above, or NULL.  */
  بنية maybe_استعمال_ٿيل_decl *ايندڙ;
};


/* in c-parser.cc */
بنية c_وڻ_token_vec;
خارجي فراغ c_parse_init (فراغ);
خارجي bool c_keyword_starts_typename (تعداد rid keyword);

/* in c-aux-info.cc */
خارجي فراغ gen_aux_info_رڪارڊ (وڻ, صحيح, صحيح, صحيح);

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
#وصف_ڪريو اندريون_SWITCH_STMT		1
#وصف_ڪريو اندريون_ITERATION_STMT	2
#وصف_ڪريو اندريون_OMP_بلاڪ		4
#وصف_ڪريو اندريون_OMP_FOR		8
#وصف_ڪريو اندريون_OBJC_FOREACH		16
#وصف_ڪريو اندريون_NAMED_STMT		32
خارجي بنانشان حرف اندريون_statement;

خارجي bool switch_statement_break_ڏٺل_p;

خارجي bool global_bindings_p (فراغ);
خارجي وڻ pushdecl (وڻ);
خارجي بنانشان صحيح شروعات_underspecified_init (location_t, وڻ);
خارجي فراغ پڄاڻي_underspecified_init (وڻ, بنانشان صحيح);
خارجي فراغ ڌڪو_scope (فراغ);
خارجي وڻ ڪڍو_scope (فراغ);
خارجي فراغ c_mark_decl_jump_unsafe_اندريون_current_scope ();
خارجي فراغ c_bindings_شروعات_stmt_اظهار (بنية c_spot_bindings *);
خارجي فراغ c_bindings_پڇاڙي_stmt_اظهار (بنية c_spot_bindings *);

خارجي فراغ رڪارڊ_inline_static (location_t, وڻ, وڻ,
				  تعداد c_inline_static_type);
خارجي فراغ c_init_decl_processing (فراغ);
خارجي فراغ c_print_identifier (FILE *, وڻ, صحيح);
خارجي صحيح quals_from_declspecs (ثابت بنية c_declspecs *);
خارجي بنية c_declarator *build_array_declarator (location_t, وڻ,
    						    بنية c_declspecs *,
						    bool, bool);
خارجي وڻ build_enumerator (location_t, location_t, بنية c_enum_contents *,
			      وڻ, وڻ);
خارجي وڻ check_for_loop_decls (location_t, bool);
خارجي فراغ mark_forward_parm_decls (فراغ);
خارجي فراغ declare_parm_level (فراغ);
خارجي فراغ undeclared_variable (location_t, وڻ);
خارجي وڻ lookup_label_for_goto (location_t, وڻ);
خارجي وڻ declare_label (وڻ);
خارجي وڻ define_label (location_t, وڻ);
خارجي بنية c_spot_bindings *c_get_switch_bindings (فراغ);
خارجي فراغ c_release_switch_bindings (بنية c_spot_bindings *);
خارجي bool c_check_switch_jump_warnings (بنية c_spot_bindings *,
					  location_t, location_t);
خارجي فراغ پڄاڻي_decl (وڻ, location_t, وڻ, وڻ, وڻ);
خارجي وڻ پڄاڻي_enum (وڻ, وڻ, وڻ);
خارجي فراغ پڄاڻي_function (location_t = داخلا_location);
خارجي وڻ پڄاڻي_struct (location_t, وڻ, وڻ, وڻ,
			   class c_struct_parse_info *,
			   وڻ *اظهار = عدم);
خارجي وڻ c_simulate_enum_decl (location_t, ثابت حرف *,
				  vec<string_int_pair> *);
خارجي وڻ c_simulate_رڪارڊ_decl (location_t, ثابت حرف *,
				    array_ٽڪرو<ثابت وڻ>);
خارجي بنية c_arg_info *build_arg_info (فراغ);
خارجي بنية c_arg_info *get_parm_info (bool, وڻ);
خارجي وڻ grokfield (location_t, بنية c_declarator *,
		       بنية c_declspecs *, وڻ, وڻ *, وڻ *);
خارجي وڻ groktypename (بنية c_type_name *, وڻ *, bool *);
خارجي وڻ grokgenassoc (بنية c_type_name *);
خارجي وڻ grokparm (ثابت بنية c_parm *, وڻ *);
خارجي وڻ implicitly_declare (location_t, وڻ);
خارجي فراغ keep_ايندڙ_level (فراغ);
خارجي فراغ pending_xref_error (فراغ);
خارجي فراغ c_ڌڪو_function_context (فراغ);
خارجي فراغ c_ڪڍو_function_context (فراغ);
خارجي فراغ ڌڪو_parm_decl (ثابت بنية c_parm *, وڻ *);
خارجي بنية c_declarator *سيٽ_array_declarator_inner (بنية c_declarator *,
							بنية c_declarator *);
خارجي وڻ c_builtin_function (وڻ);
خارجي وڻ c_builtin_function_ext_scope (وڻ);
خارجي وڻ c_simulate_builtin_function_decl (وڻ);
خارجي فراغ c_warn_اڻ_استعمال_ٿيل_خاصيتون (وڻ);
خارجي وڻ c_warn_type_خاصيتون (وڻ, وڻ);
خارجي فراغ shadow_ٽيگ (ثابت بنية c_declspecs *);
خارجي فراغ shadow_ٽيگ_warned (ثابت بنية c_declspecs *, صحيح);
خارجي وڻ شروعات_enum (location_t, بنية c_enum_contents *, وڻ, وڻ,
			bool potential_nesting_p);
خارجي bool شروعات_function (بنية c_declspecs *, بنية c_declarator *, وڻ);
خارجي وڻ شروعات_decl (بنية c_declarator *, بنية c_declspecs *, bool,
			وڻ, bool = true, location_t * = عدم);
خارجي وڻ شروعات_struct (location_t, تعداد وڻ_ڪوڊ_2, وڻ,
			  class c_struct_parse_info **);
خارجي فراغ store_parm_decls (فراغ);
خارجي فراغ store_parm_decls_from (بنية c_arg_info *);
خارجي فراغ عارضي_store_parm_decls (وڻ, وڻ);
خارجي فراغ عارضي_ڪڍو_parm_decls (فراغ);
خارجي وڻ xref_ٽيگ (تعداد وڻ_ڪوڊ_2, وڻ);
خارجي بنية c_typespec parser_xref_ٽيگ (location_t, تعداد وڻ_ڪوڊ_2, وڻ,
					  bool, وڻ, bool);
خارجي بنية c_parm *build_c_parm (بنية c_declspecs *, وڻ,
				    بنية c_declarator *, location_t);
خارجي بنية c_declarator *build_attrs_declarator (وڻ,
						    بنية c_declarator *);
خارجي بنية c_declarator *build_function_declarator (بنية c_arg_info *,
						       بنية c_declarator *);
خارجي بنية c_declarator *build_id_declarator (وڻ);
خارجي بنية c_declarator *make_اشارو_declarator (بنية c_declspecs *,
						     بنية c_declarator *);
خارجي بنية c_declspecs *build_null_declspecs (فراغ);
خارجي بنية c_declspecs *declspecs_جوڙيو_qual (location_t,
					       بنية c_declspecs *, وڻ);
خارجي بنية c_declspecs *declspecs_جوڙيو_type (location_t,
					       بنية c_declspecs *,
					       بنية c_typespec);
خارجي بنية c_declspecs *declspecs_جوڙيو_scspec (location_t,
						 بنية c_declspecs *, وڻ);
خارجي بنية c_declspecs *declspecs_جوڙيو_attrs (location_t,
						بنية c_declspecs *, وڻ);
خارجي بنية c_declspecs *declspecs_جوڙيو_addrspace (location_t,
						    بنية c_declspecs *,
						    addr_space_t);
خارجي بنية c_declspecs *declspecs_جوڙيو_alignas (location_t,
						  بنية c_declspecs *, وڻ);
خارجي بنية c_declspecs *پڄاڻي_declspecs (بنية c_declspecs *);
خارجي سائيز_t c_وڻ_سائيز (تعداد وڻ_ڪوڊ_2);
خارجي صحيح c_get_loop_نالا (وڻ, bool, وڻ *);
خارجي فراغ c_release_loop_نالا (صحيح);
خارجي وڻ c_پڄاڻي_bc_name (location_t, وڻ, bool);

/* in c-objc-common.cc */
خارجي bool c_objc_common_init (فراغ);
خارجي bool c_missing_noreturn_ok_p (وڻ);
خارجي bool c_warn_اڻ_استعمال_ٿيل_global_decl (const_وڻ);
خارجي فراغ c_initialize_diagnostics (diagnostics::context *);
خارجي bool c_var_mod_p (وڻ x, وڻ fn);
خارجي alias_سيٽ_type c_get_alias_سيٽ (وڻ);
خارجي صحيح c_type_dwarf_attribute (const_وڻ, صحيح);
خارجي وڻ c_enum_underlying_بنياد_type (const_وڻ);

/* in c-typeck.cc */
خارجي صحيح اندريون_alignof;
خارجي صحيح اندريون_sizeof;
خارجي صحيح اندريون_countof;
خارجي صحيح اندريون_typeof;
خارجي صحيح اندريون_generic;
خارجي bool c_اندريون_omp_for;
خارجي bool c_omp_array_section_p;

خارجي وڻ c_آخري_sizeof_arg;
خارجي location_t c_آخري_sizeof_loc;

خارجي بنية c_switch *c_switch_ڍير;

خارجي bool null_اشارو_constant_p (const_وڻ);


مضمن bool
c_type_variably_modified_p (وڻ t)
{
  إذا (error_mark_ڳنڍ == t)
    أرجع false;
  إذا (C_TYPE_VARIABLY_MODIFIED (t))
    أرجع true;
  إذا (TYPE_STRUCTURAL_EQUALITY_P (t))
    {
      /* The flag may not have been set yet because of incomplete
	 structure or union types completed later.  */
      بدل (وڻ_ڪوڊ (t))
	{
	حالة ARRAY_TYPE:
	حالة FUNCTION_TYPE:
	حالة اشارو_TYPE:
	  /* Recurse.  */
	  إذا (c_type_variably_modified_p (وڻ_TYPE (t)))
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
c_type_unspecified_p (وڻ t)
{
  أرجع error_mark_ڳنڍ != t
	 && C_TYPE_VARIABLE_سائيز (t) && وڻ_ڪوڊ (t) == ARRAY_TYPE
	 && TYPE_DOMAIN (t) && TYPE_MAX_قدر (TYPE_DOMAIN (t))
	 && وڻ_ڪوڊ (TYPE_MAX_قدر (TYPE_DOMAIN (t))) == COMPOUND_اظهار
	 && integer_zerop (وڻ_عمليو (TYPE_MAX_قدر (TYPE_DOMAIN (t)), 0))
	 && integer_zerop (وڻ_عمليو (TYPE_MAX_قدر (TYPE_DOMAIN (t)), 1));
}

خارجي bool zero_ڊيگهائي_array_type_p (const_وڻ type);
خارجي bool char_type_p (وڻ);
خارجي وڻ c_type_ٽيگ (const_وڻ t);
خارجي وڻ c_objc_common_truthvalue_conversion (location_t, وڻ,
						 وڻ = integer_type_ڳنڍ);
خارجي وڻ require_complete_type (location_t, وڻ);
خارجي bool same_translation_unit_p (const_وڻ, const_وڻ);
خارجي bool comptypes (وڻ, وڻ);
خارجي bool comptypes_same_p (وڻ, وڻ);
خارجي bool comptypes_equiv_p (وڻ, وڻ);
خارجي bool comptypes_check_enum_int (وڻ, وڻ, bool *);
خارجي bool c_mark_addressable (وڻ, bool = false, bool = false);
خارجي فراغ c_incomplete_type_error (location_t, const_وڻ, const_وڻ);
خارجي وڻ c_type_promotes_منزل (وڻ);
خارجي بنية c_اظهار default_function_array_conversion (location_t,
							بنية c_اظهار);
خارجي بنية c_اظهار default_function_array_read_conversion (location_t,
							     بنية c_اظهار);
خارجي بنية c_اظهار convert_lvalue_منزل_rvalue (location_t, بنية c_اظهار,
					       bool, bool, bool = false);
خارجي وڻ decl_constant_قدر_1 (وڻ, bool);
خارجي فراغ mark_exp_read (وڻ);
خارجي وڻ مرکب_type (وڻ, وڻ);
خارجي وڻ lookup_ميدان (const_وڻ, وڻ);
خارجي وڻ build_component_ref (location_t, وڻ, وڻ, location_t,
				 location_t);
خارجي وڻ handle_counted_by_for_component_ref (location_t, وڻ);
خارجي وڻ build_array_ref (location_t, وڻ, وڻ);
خارجي وڻ build_omp_array_section (location_t, وڻ, وڻ, وڻ);
خارجي وڻ build_external_ref (location_t, وڻ, bool, وڻ *);
خارجي فراغ ڪڍو_maybe_استعمال_ٿيل (bool);
خارجي بنية maybe_استعمال_ٿيل_decl *save_maybe_استعمال_ٿيل ();
خارجي فراغ restore_maybe_استعمال_ٿيل (بنية maybe_استعمال_ٿيل_decl *);
خارجي فراغ mark_decl_استعمال_ٿيل (وڻ, bool);
خارجي بنية c_اظهار c_اظهار_sizeof_اظهار (location_t, بنية c_اظهار);
خارجي بنية c_اظهار c_اظهار_sizeof_type (location_t, بنية c_type_name *);
خارجي بنية c_اظهار c_اظهار_countof_اظهار (location_t, بنية c_اظهار);
خارجي بنية c_اظهار c_اظهار_countof_type (location_t loc,
					  بنية c_type_name *);
خارجي بنية c_اظهار c_اظهار_maxof_type (location_t loc, بنية c_type_name *);
خارجي بنية c_اظهار c_اظهار_minof_type (location_t loc, بنية c_type_name *);
خارجي بنية c_اظهار parser_build_unary_op (location_t, تعداد وڻ_ڪوڊ_2,
    					    بنية c_اظهار);
خارجي بنية c_اظهار parser_build_ٻٽو_op (location_t,
    					     تعداد وڻ_ڪوڊ_2, بنية c_اظهار,
					     بنية c_اظهار, وڻ);
خارجي وڻ build_conditional_اظهار (location_t, وڻ, bool, وڻ, وڻ,
				    location_t, وڻ, وڻ, location_t);
خارجي وڻ build_compound_اظهار (location_t, وڻ, وڻ);
خارجي وڻ c_cast_اظهار (location_t, بنية c_type_name *, وڻ);
خارجي وڻ build_c_cast (location_t, وڻ, وڻ);
خارجي فراغ store_init_قدر (location_t, وڻ, وڻ, وڻ);
خارجي فراغ maybe_warn_string_init (location_t, وڻ, بنية c_اظهار);
خارجي فراغ شروعات_init (وڻ, وڻ, bool, bool, rich_location *);
خارجي فراغ پڄاڻي_init (فراغ);
خارجي فراغ really_شروعات_incremental_init (وڻ);
خارجي فراغ پڄاڻي_implicit_inits (location_t, بنية obstack *);
خارجي فراغ ڌڪو_init_level (location_t, صحيح, بنية obstack *);
خارجي بنية c_اظهار ڪڍو_init_level (location_t, صحيح, بنية obstack *,
				     location_t);
خارجي فراغ سيٽ_init_اشاريو (location_t, وڻ, وڻ, بنية obstack *);
خارجي فراغ سيٽ_init_label (location_t, وڻ, location_t, بنية obstack *);
بنانشان c_maybe_optimize_large_byte_initializer (فراغ);
خارجي فراغ process_init_element (location_t, بنية c_اظهار, bool,
				  بنية obstack *);
خارجي وڻ build_compound_literal (location_t, وڻ, وڻ, bool,
				    بنانشان صحيح, بنية c_declspecs *);
خارجي فراغ check_compound_literal_type (location_t, بنية c_type_name *);
خارجي وڻ c_شروعات_switch (location_t, location_t, وڻ, bool, وڻ);
خارجي فراغ c_پڄاڻي_switch (وڻ, وڻ);
خارجي وڻ build_asm_اظهار (location_t, وڻ, وڻ, وڻ, وڻ, وڻ, bool,
			    bool);
خارجي وڻ build_asm_stmt (bool, وڻ);
خارجي صحيح c_types_compatible_p (وڻ, وڻ);
خارجي وڻ c_begin_compound_stmt (bool);
خارجي وڻ c_پڇاڙي_compound_stmt (location_t, وڻ, bool);
خارجي فراغ c_پڄاڻي_if_stmt (location_t, وڻ, وڻ, وڻ);
خارجي فراغ c_پڄاڻي_loop (location_t, location_t, وڻ, location_t, وڻ,
			   وڻ, وڻ, وڻ, bool);
خارجي وڻ c_begin_stmt_اظهار (فراغ);
خارجي وڻ c_پڄاڻي_stmt_اظهار (location_t, وڻ);
خارجي وڻ c_process_اظهار_stmt (location_t, وڻ);
خارجي وڻ c_پڄاڻي_اظهار_stmt (location_t, وڻ);
خارجي وڻ c_پڄاڻي_return (location_t, وڻ, وڻ, bool = false);
خارجي وڻ c_پڄاڻي_bc_stmt (location_t, وڻ, bool, وڻ);
خارجي وڻ c_پڄاڻي_goto_label (location_t, وڻ);
خارجي وڻ c_پڄاڻي_goto_ptr (location_t, c_اظهار val);
خارجي وڻ c_اظهار_منزل_decl (وڻ, bool *, bool *);
خارجي وڻ c_پڄاڻي_omp_construct (location_t, تعداد وڻ_ڪوڊ_2, وڻ, وڻ);
خارجي وڻ c_پڄاڻي_oacc_معلومات (location_t, وڻ, وڻ);
خارجي وڻ c_پڄاڻي_oacc_host_معلومات (location_t, وڻ, وڻ);
خارجي وڻ c_begin_omp_parallel (فراغ);
خارجي وڻ c_پڄاڻي_omp_parallel (location_t, وڻ, وڻ);
خارجي وڻ c_begin_omp_task (فراغ);
خارجي وڻ c_پڄاڻي_omp_task (location_t, وڻ, وڻ);
خارجي فراغ c_پڄاڻي_omp_cancel (location_t, وڻ);
خارجي فراغ c_پڄاڻي_omp_cancellation_نقطو (location_t, وڻ);
خارجي وڻ c_پڄاڻي_omp_clauses (وڻ, تعداد c_omp_region_type);
خارجي وڻ c_omp_پڄاڻي_mapper_clauses (وڻ);
خارجي وڻ c_omp_mapper_lookup (وڻ, وڻ);
خارجي وڻ c_omp_ڪڍو_mapper_directive (وڻ);
خارجي وڻ c_omp_map_array_section (location_t, وڻ);
خارجي وڻ c_build_va_arg (location_t, وڻ, location_t, وڻ, وڻ);
خارجي وڻ c_پڄاڻي_transaction (location_t, وڻ, صحيح);
خارجي bool c_وڻ_equal (وڻ, وڻ);
خارجي وڻ c_build_function_call_vec (location_t, ثابت vec<location_t>&,
				       وڻ, vec<وڻ, va_gc> *,
				       vec<وڻ, va_gc> *);
خارجي وڻ c_omp_clause_copy_ctor (وڻ, وڻ, وڻ);
خارجي وڻ c_reconstruct_complex_type (وڻ, وڻ);
خارجي وڻ c_type_canonical (وڻ);
خارجي وڻ c_build_type_attribute_variant (وڻ ntype, وڻ attrs);
خارجي وڻ c_build_اشارو_type (وڻ type);
خارجي وڻ c_build_array_type (وڻ type, وڻ domain);
خارجي وڻ c_build_array_type_unspecified (وڻ type);
خارجي وڻ c_build_array_type_zero_سائيز (وڻ type);
خارجي وڻ c_build_function_type (وڻ type, وڻ دليلون, bool no = false);
خارجي وڻ c_build_اشارو_type_for_گهڻائي (وڻ type, machine_گهڻائي گهڻائي, bool m);

/* Set to 0 at beginning of a function definition, set to 1 if
   a return statement that specifies a return value is seen.  */

خارجي صحيح current_function_returns_قدر;

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
  C_ORACLE_نشان,
  C_ORACLE_ٽيگ,
  C_ORACLE_LABEL
};

/* If this is non-NULL, then it is a "binding oracle" which can lazily
   create bindings when needed by the C compiler.  The oracle is told
   the name and type of the binding to create.  It can call pushdecl
   or the like to ensure the binding is visible; or do nothing,
   leaving the binding untouched.  c-decl.cc takes note of when the
   oracle has been called and will not call it again if it fails to
   create a given binding.  */

تعريفنوع فراغ c_binding_oracle_function (تعداد c_oracle_request, وڻ identifier);

خارجي c_binding_oracle_function *c_binding_oracle;

خارجي فراغ c_پڄاڻي_incomplete_decl (وڻ);
خارجي وڻ c_omp_reduction_id (تعداد وڻ_ڪوڊ_2, وڻ);
خارجي وڻ c_omp_reduction_decl (وڻ);
خارجي وڻ c_omp_reduction_lookup (وڻ, وڻ);
خارجي وڻ c_check_omp_declare_reduction_r (وڻ *, صحيح *, فراغ *);
خارجي وڻ c_omp_mapper_id (وڻ);
خارجي وڻ c_omp_mapper_decl (وڻ);
خارجي فراغ c_omp_جاچ_mapper_bindings (location_t, وڻ *, وڻ);
خارجي bool c_check_اندريون_current_scope (وڻ);
خارجي فراغ c_pushtag (location_t, وڻ, وڻ);
خارجي فراغ c_bind (location_t, وڻ, bool);
خارجي bool ٽيگ_exists_p (تعداد وڻ_ڪوڊ_2, وڻ);

خارجي فراغ verify_counted_by_for_چوٽي_anonymous_type (وڻ);

/* In c-errors.cc */
خارجي bool pedwarn_c90 (location_t, diagnostics::option_id, ثابت حرف *, ...)
    ATTRIBUTE_GCC_DIAG(3,4);
خارجي bool pedwarn_c99 (location_t, diagnostics::option_id, ثابت حرف *, ...)
    ATTRIBUTE_GCC_DIAG(3,4);
خارجي bool pedwarn_c11 (location_t, diagnostics::option_id, ثابت حرف *, ...)
    ATTRIBUTE_GCC_DIAG(3,4);
خارجي bool pedwarn_c23 (location_t, diagnostics::option_id, ثابت حرف *, ...)
    ATTRIBUTE_GCC_DIAG(3,4);
خارجي فراغ جوڙيو_note_about_new_keyword (location_t loc,
					وڻ keyword_id);

خارجي فراغ
سيٽ_c_اظهار_ذريعو_range (c_اظهار *اظهار,
			 location_t شروعات, location_t پڄاڻي);

خارجي فراغ
سيٽ_c_اظهار_ذريعو_range (c_اظهار *اظهار,
			 ذريعو_range src_range);

/* In c-fold.cc */
خارجي vec<وڻ> incomplete_رڪارڊ_decls;

خارجي ثابت حرف *c_get_sarif_ذريعو_language (ثابت حرف *filename);

خارجي ثابت بنية scoped_attribute_specs std_attribute_جدول;

#إذا CHECKING_P
namespace selftest {
  خارجي فراغ لاڳيتو_c_tests (فراغ);
} // namespace selftest
#جيڪڏهن_پورو /* #if CHECKING_P */


#جيڪڏهن_پورو /* ! GCC_C_TREE_H */
