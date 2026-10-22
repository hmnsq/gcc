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

#ifndef GCC_C_वृक्षः_H
#define GCC_C_वृक्षः_H

#अन्तर्भाव "c-family/c-common.h"
#अन्तर्भाव "diagnostic.h"

/* struct lang_identifier is private to c-decl.cc, but langhooks.cc needs to
   know how big it is.  This is sanity-checked in c-decl.cc.  */
#define C_SIZEOF_STRUCT_LANG_IDENTIFIER \
  (परिमाण (संरचना c_common_identifier) + 3 * परिमाण (शून्य *))

/* In a RECORD_TYPE or UNION_TYPE, nonzero if any component is read-only.  */
#define C_TYPE_FIELDS_READONLY(TYPE) वृक्षः_LANG_FLAG_1 (TYPE)

/* In a RECORD_TYPE or UNION_TYPE, nonzero if any component is volatile.  */
#define C_TYPE_FIELDS_VOLATILE(TYPE) वृक्षः_LANG_FLAG_2 (TYPE)

/* In a RECORD_TYPE or UNION_TYPE, nonzero if any component is
   volatile, restrict-qualified or atomic; that is, has a type not
   permitted for a constexpr object.  */
#define C_TYPE_FIELDS_NON_CONSTEXPR(TYPE) वृक्षः_LANG_FLAG_4 (TYPE)

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
  TYPE_LANG_SLOT_1 (वृक्षः_CHECK4 (TYPE, RECORD_TYPE, UNION_TYPE, \
				 QUAL_UNION_TYPE, ENUMERAL_TYPE))

/* In an IDENTIFIER_NODE, nonzero if this identifier is actually a
   keyword.  C_RID_CODE (node) is then the RID_* value of the keyword.  */
#define C_IS_RESERVED_WORD(ID) वृक्षः_LANG_FLAG_0 (ID)

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
#define C_ARRAY_PARAMETER(ग्रन्थिः_2) DECL_LANG_FLAG_0 (ग्रन्थिः_2)

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
  DECL_LANG_FLAG_4 (वृक्षः_NOT_CHECK (EXP, FUNCTION_DECL))

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
	|| (!prototype_p (वृक्षः_TYPE (EXP))	\
	    && !fndecl_built_in_p (EXP)))

/* For FUNCTION_TYPE, a hidden list of types of arguments.  The same as
   TYPE_ARG_TYPES for functions with prototypes, but created for functions
   without prototypes.  */
#define TYPE_ACTUAL_ARG_TYPES(ग्रन्थिः_2) \
  TYPE_LANG_SLOT_1 (FUNCTION_TYPE_CHECK (ग्रन्थिः_2))

/* For a CONSTRUCTOR, whether some initializer contains a
   subexpression meaning it is not a constant expression.  */
#define CONSTRUCTOR_NON_CONST(व्यञ्जकम्_2) वृक्षः_LANG_FLAG_1 (CONSTRUCTOR_CHECK (व्यञ्जकम्_2))

/* For a SAVE_EXPR, nonzero if the operand of the SAVE_EXPR has already
   been folded.  */
#define SAVE_व्यञ्जकम्_FOLDED_P(EXP)	वृक्षः_LANG_FLAG_1 (SAVE_व्यञ्जकम्_CHECK (EXP))

/* Whether a type has boolean semantics: either a boolean type or an
   enumeration type with a boolean type as its underlying type.  */
#define C_BOOLEAN_TYPE_P(TYPE)						\
  (वृक्षः_CODE (TYPE) == BOOLEAN_TYPE					\
   || (वृक्षः_CODE (TYPE) == ENUMERAL_TYPE				\
       && ENUM_UNDERLYING_TYPE (TYPE) != NULL_वृक्षः			\
       && (वृक्षः_CODE (ENUM_UNDERLYING_TYPE (TYPE)) == BOOLEAN_TYPE	\
	   || c_hardbool_type_attr (TYPE))))

/* Record parser information about an expression that is irrelevant
   for code generation alongside a tree representing its value.  */
संरचना c_व्यञ्जकम्
{
  /* The value of the expression.  */
  वृक्षः मानम्;
  /* Record the original unary/binary operator of an expression, which may
     have been changed by fold, STRING_CST for unparenthesized string
     constants, C_MAYBE_CONST_EXPR for __builtin_constant_p calls
     (even if parenthesized), for subexpressions, and for non-constant
     initializers, or ERROR_MARK for other expressions (including
     parenthesized expressions).  */
  गणना वृक्षः_code original_code;
  /* If not NULL, the original type of an expression.  This will
     differ from the type of the value field for an enum constant.
     The type of an enum constant is a plain integer type, but this
     field will be the enum type.  */
  वृक्षः original_type;

  /* The source range of this expression.  This is redundant
     for node values that have locations, but not all node kinds
     have locations (e.g. constants, and references to params, locals,
     etc), so we stash a copy here.  */
  source_range src_range;

  /* True if this was directly from a decimal constant token.  */
  bool m_decimal : 1;

  /* Access to the first and last locations within the source spelling
     of this expression.  */
  location_t get_start () ध्रुव { प्रत्यागम src_range.m_start; }
  location_t get_finish () ध्रुव { प्रत्यागम src_range.m_finish; }

  location_t get_location () ध्रुव
  {
    जइ (व्यञ्जकम्_HAS_LOCATION (मानम्))
      प्रत्यागम व्यञ्जकम्_LOCATION (मानम्);
    अण्णहा
      प्रत्यागम make_location (get_start (), get_start (), get_finish ());
  }

  /* Set the value to error_mark_node whilst ensuring that src_range
     and m_decimal are initialized.  */
  शून्य set_error ()
  {
    मानम् = error_mark_ग्रन्थिः;
    src_range.m_start = UNKNOWN_LOCATION;
    src_range.m_finish = UNKNOWN_LOCATION;
    m_decimal = 0;
  }
};

/* Type alias for struct c_expr. This allows to use the structure
   inside the VEC types.  */
प्रकारनिर्देश संरचना c_व्यञ्जकम् c_व्यञ्जकम्_t;

/* A kind of type specifier.  Note that this information is currently
   only used to distinguish tag definitions, tag references and typeof
   uses.  */
गणना c_typespec_kind {
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
संरचना c_typespec {
  /* What kind of type specifier this is.  */
  गणना c_typespec_kind kind;
  /* Whether the expression has operands suitable for use in constant
     expressions.  */
  bool व्यञ्जकम्_const_operands;
  /* Whether the type specifier includes an enum type specifier (that
     is, ": specifier-qualifier-list" in a declaration using
     "enum").  */
  bool has_enum_type_specifier;
  /* The specifier itself.  */
  वृक्षः spec;
  /* An expression to be evaluated before the type specifier, in the
     case of typeof specifiers, or NULL otherwise or if no such
     expression is required for a particular typeof specifier.  In
     particular, when typeof is applied to an expression of variably
     modified type, that expression must be evaluated in order to
     determine array sizes that form part of the type, but the
     expression itself (as opposed to the array sizes) forms no part
     of the type and so needs to be recorded separately.  */
  वृक्षः व्यञ्जकम्;
};

/* A storage class specifier.  */
गणना c_storage_class {
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
गणना c_typespec_keyword {
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
गणना c_declspec_word {
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
  cdw_सङ्ख्या_of_elements /* This one must always be the last
			    enumerator.  */
};

गणना c_declspec_il {
  cdil_none,
  cdil_gimple,		/* __GIMPLE  */
  cdil_gimple_cfg,	/* __GIMPLE(cfg)  */
  cdil_gimple_ssa,	/* __GIMPLE(ssa)  */
  cdil_rtl		/* __RTL  */
};

/* A sequence of declaration specifiers in C.  When a new declaration
   specifier is added, please update the enum c_declspec_word above
   accordingly.  */
संरचना c_declspecs {
  location_t locations[cdw_सङ्ख्या_of_elements];
  /* The type specified, if a single type specifier such as a struct,
     union or enum specifier, typedef name or typeof specifies the
     whole type, or NULL_TREE if none or a keyword such as "void" or
     "char" is used.  Does not include qualifiers.  */
  वृक्षः type;
  /* Any expression to be evaluated before the type, from a typeof
     specifier.  */
  वृक्षः व्यञ्जकम्;
  /* The attributes from a typedef decl.  */
  वृक्षः decl_attr;
  /* When parsing, the GNU attributes and prefix standard attributes.
     Outside the parser, this will be NULL; attributes (possibly from
     multiple lists) will be passed separately.  */
  वृक्षः attrs;
  /* When parsing, postfix standard attributes (which appertain to the
     type specified by the preceding declaration specifiers, unlike
     prefix standard attributes which appertain to the declaration or
     declarations as a whole).  */
  वृक्षः postfix_attrs;
  /* The pass to start compiling a __GIMPLE or __RTL function with.  */
  वर्ण *gimple_or_rtl_pass;
  /* ENTRY BB count.  */
  profile_गणनम् entry_bb_गणनम्;
  /* The base-2 log of the greatest alignment required by an _Alignas
     specifier, in bytes, or -1 if no such specifiers with nonzero
     alignment.  */
  पूर्णाङ्क align_log;
  सङ्घ {
    /* For the __intN declspec, this stores the index into the int_n_*
       arrays.  */
    पूर्णाङ्क int_n_idx;
    /* For the _FloatN and _FloatNx declspec, this stores the index into
       the floatn_nx_types array.  */
    पूर्णाङ्क floatn_nx_idx;
    /* For _BitInt(N) this stores the N.  */
    पूर्णाङ्क bitint_prec;
  } u;
  /* The storage class specifier, or csc_none if none.  */
  गणना c_storage_class storage_class;
  /* Any type specifier keyword used such as "int", not reflecting
     modifiers such as "short", or cts_none if none.  */
  गणना c_typespec_keyword typespec_word : 8;
  /* The kind of type specifier if one has been seen, ctsk_none
     otherwise.  */
  गणना c_typespec_kind typespec_kind : 4;
  गणना c_declspec_il declspec_il : 3;
  /* Whether any expressions in typeof specifiers may appear in
     constant expressions.  */
  bool व्यञ्जकम्_const_operands : 1;
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
गणना c_declarator_kind {
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

संरचना c_arg_tag {
  /* The argument name.  */
  वृक्षः id;
  /* The type of the argument.  */
  वृक्षः type;
};


/* Information about the parameters in a function declarator.  */
संरचना c_arg_info {
  /* A list of parameter decls.  */
  वृक्षः parms;
  /* A list of structure, union and enum tags defined.  */
  vec<c_arg_tag, va_gc> *tags;
  /* A list of argument types to go in the FUNCTION_TYPE.  */
  वृक्षः types;
  /* A list of non-parameter decls (notably enumeration constants)
     defined with the parameters.  */
  वृक्षः others;
  /* A compound expression of VLA sizes from the parameters, or NULL.
     In a function definition, these are used to ensure that
     side-effects in sizes of arrays converted to pointers (such as a
     parameter int i[n++]) take place; otherwise, they are
     ignored.  */
  वृक्षः pending_sizes;
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
संरचना c_declarator {
  /* The kind of declarator.  */
  गणना c_declarator_kind kind;
  location_t id_loc; /* Currently only set for cdk_id, cdk_array. */
  /* Except for cdk_id, the contained declarator.  For cdk_id, NULL.  */
  संरचना c_declarator *declarator;
  सङ्घ {
    /* For identifiers.  */
    संरचना {
      /* An IDENTIFIER_NODE, or NULL_TREE if an abstract
	 declarator.  */
      वृक्षः id;
      /* Any attributes (which apply to the declaration rather than to
	 the type described by the outer declarators).  */
      वृक्षः attrs;
    } id;
    /* For functions.  */
    संरचना c_arg_info *arg_info;
    /* For arrays.  */
    संरचना {
      /* The array dimension, or NULL for [] and [*].  */
      वृक्षः dimen;
      /* The qualifiers inside [].  */
      पूर्णाङ्क quals;
      /* The attributes (currently ignored) inside [].  */
      वृक्षः attrs;
      /* Whether [static] was used.  */
      bool static_p : 1;
      /* Whether [*] was used.  */
      bool vla_unspec_p : 1;
    } array;
    /* For pointers, the qualifiers on the pointer type.  */
    पूर्णाङ्क pointer_quals;
    /* For attributes.  */
    वृक्षः attrs;
  } u;
};

/* A type name.  */
संरचना c_type_name {
  /* The declaration specifiers.  */
  संरचना c_declspecs *specs;
  /* The declarator.  */
  संरचना c_declarator *declarator;
};

/* A parameter.  */
संरचना c_parm {
  /* The declaration specifiers, minus any prefix attributes.  */
  संरचना c_declspecs *specs;
  /* The attributes.  */
  वृक्षः attrs;
  /* The declarator.  */
  संरचना c_declarator *declarator;
  /* The location of the parameter.  */
  location_t loc;
};

/* Used when parsing an enum.  Initialized by start_enum.  */
संरचना c_enum_contents
{
  /* While defining an enum type, this is 1 plus the last enumerator
     constant value.  */
  वृक्षः enum_next_मानम्;

  /* The enumeration type itself.  */
  वृक्षः enum_type;

  /* Nonzero means that there was overflow computing enum_next_value.  */
  पूर्णाङ्क enum_overflow;
};

/* A type of reference to a static identifier in an inline
   function.  */
गणना c_inline_static_type {
  /* Identifier with internal linkage used in function that may be an
     inline definition (i.e., file-scope static).  */
  csi_internal,
  /* Modifiable object with static storage duration defined in
     function that may be an inline definition (i.e., local
     static).  */
  csi_modifiable
};

/* Record details of decls possibly used inside sizeof or typeof.  */
संरचना maybe_used_decl
{
  /* The decl.  */
  वृक्षः decl;
  /* The level seen at (in_sizeof + in_typeof + in_countof + in_generic).  */
  पूर्णाङ्क level;
  /* Seen in address-of.  */
  bool address;
  /* The next one at this level or above, or NULL.  */
  संरचना maybe_used_decl *next;
};


/* in c-parser.cc */
संरचना c_वृक्षः_token_vec;
बाह्य शून्य c_parse_init (शून्य);
बाह्य bool c_keyword_starts_typename (गणना rid keyword);

/* in c-aux-info.cc */
बाह्य शून्य gen_aux_info_record (वृक्षः, पूर्णाङ्क, पूर्णाङ्क, पूर्णाङ्क);

/* in c-decl.cc */
संरचना c_spot_bindings;
class c_struct_parse_info;
बाह्य संरचना obstack parser_obstack;
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
बाह्य unsigned वर्ण in_statement;

बाह्य bool switch_statement_break_seen_p;

बाह्य bool global_bindings_p (शून्य);
बाह्य वृक्षः pushdecl (वृक्षः);
बाह्य unsigned पूर्णाङ्क start_underspecified_init (location_t, वृक्षः);
बाह्य शून्य finish_underspecified_init (वृक्षः, unsigned पूर्णाङ्क);
बाह्य शून्य प्रक्षिप_scope (शून्य);
बाह्य वृक्षः निष्कासय_scope (शून्य);
बाह्य शून्य c_mark_decl_jump_unsafe_in_current_scope ();
बाह्य शून्य c_bindings_start_stmt_व्यञ्जकम् (संरचना c_spot_bindings *);
बाह्य शून्य c_bindings_end_stmt_व्यञ्जकम् (संरचना c_spot_bindings *);

बाह्य शून्य record_inline_static (location_t, वृक्षः, वृक्षः,
				  गणना c_inline_static_type);
बाह्य शून्य c_init_decl_processing (शून्य);
बाह्य शून्य c_print_identifier (FILE *, वृक्षः, पूर्णाङ्क);
बाह्य पूर्णाङ्क quals_from_declspecs (ध्रुव संरचना c_declspecs *);
बाह्य संरचना c_declarator *build_array_declarator (location_t, वृक्षः,
    						    संरचना c_declspecs *,
						    bool, bool);
बाह्य वृक्षः build_enumerator (location_t, location_t, संरचना c_enum_contents *,
			      वृक्षः, वृक्षः);
बाह्य वृक्षः check_for_loop_decls (location_t, bool);
बाह्य शून्य mark_forward_parm_decls (शून्य);
बाह्य शून्य declare_parm_level (शून्य);
बाह्य शून्य undeclared_variable (location_t, वृक्षः);
बाह्य वृक्षः lookup_label_for_goto (location_t, वृक्षः);
बाह्य वृक्षः declare_label (वृक्षः);
बाह्य वृक्षः define_label (location_t, वृक्षः);
बाह्य संरचना c_spot_bindings *c_get_switch_bindings (शून्य);
बाह्य शून्य c_release_switch_bindings (संरचना c_spot_bindings *);
बाह्य bool c_check_switch_jump_warnings (संरचना c_spot_bindings *,
					  location_t, location_t);
बाह्य शून्य finish_decl (वृक्षः, location_t, वृक्षः, वृक्षः, वृक्षः);
बाह्य वृक्षः finish_enum (वृक्षः, वृक्षः, वृक्षः);
बाह्य शून्य finish_function (location_t = निवेशः_location);
बाह्य वृक्षः finish_struct (location_t, वृक्षः, वृक्षः, वृक्षः,
			   class c_struct_parse_info *,
			   वृक्षः *व्यञ्जकम् = रिक्त);
बाह्य वृक्षः c_simulate_enum_decl (location_t, ध्रुव वर्ण *,
				  vec<string_int_pair> *);
बाह्य वृक्षः c_simulate_record_decl (location_t, ध्रुव वर्ण *,
				    array_slice<ध्रुव वृक्षः>);
बाह्य संरचना c_arg_info *build_arg_info (शून्य);
बाह्य संरचना c_arg_info *get_parm_info (bool, वृक्षः);
बाह्य वृक्षः grokfield (location_t, संरचना c_declarator *,
		       संरचना c_declspecs *, वृक्षः, वृक्षः *, वृक्षः *);
बाह्य वृक्षः groktypename (संरचना c_type_name *, वृक्षः *, bool *);
बाह्य वृक्षः grokgenassoc (संरचना c_type_name *);
बाह्य वृक्षः grokparm (ध्रुव संरचना c_parm *, वृक्षः *);
बाह्य वृक्षः implicitly_declare (location_t, वृक्षः);
बाह्य शून्य keep_next_level (शून्य);
बाह्य शून्य pending_xref_error (शून्य);
बाह्य शून्य c_प्रक्षिप_function_context (शून्य);
बाह्य शून्य c_निष्कासय_function_context (शून्य);
बाह्य शून्य प्रक्षिप_parm_decl (ध्रुव संरचना c_parm *, वृक्षः *);
बाह्य संरचना c_declarator *set_array_declarator_inner (संरचना c_declarator *,
							संरचना c_declarator *);
बाह्य वृक्षः c_builtin_function (वृक्षः);
बाह्य वृक्षः c_builtin_function_ext_scope (वृक्षः);
बाह्य वृक्षः c_simulate_builtin_function_decl (वृक्षः);
बाह्य शून्य c_warn_unused_attributes (वृक्षः);
बाह्य वृक्षः c_warn_type_attributes (वृक्षः, वृक्षः);
बाह्य शून्य shadow_tag (ध्रुव संरचना c_declspecs *);
बाह्य शून्य shadow_tag_warned (ध्रुव संरचना c_declspecs *, पूर्णाङ्क);
बाह्य वृक्षः start_enum (location_t, संरचना c_enum_contents *, वृक्षः, वृक्षः,
			bool potential_nesting_p);
बाह्य bool start_function (संरचना c_declspecs *, संरचना c_declarator *, वृक्षः);
बाह्य वृक्षः start_decl (संरचना c_declarator *, संरचना c_declspecs *, bool,
			वृक्षः, bool = true, location_t * = रिक्त);
बाह्य वृक्षः start_struct (location_t, गणना वृक्षः_code, वृक्षः,
			  class c_struct_parse_info **);
बाह्य शून्य store_parm_decls (शून्य);
बाह्य शून्य store_parm_decls_from (संरचना c_arg_info *);
बाह्य शून्य temp_store_parm_decls (वृक्षः, वृक्षः);
बाह्य शून्य temp_निष्कासय_parm_decls (शून्य);
बाह्य वृक्षः xref_tag (गणना वृक्षः_code, वृक्षः);
बाह्य संरचना c_typespec parser_xref_tag (location_t, गणना वृक्षः_code, वृक्षः,
					  bool, वृक्षः, bool);
बाह्य संरचना c_parm *build_c_parm (संरचना c_declspecs *, वृक्षः,
				    संरचना c_declarator *, location_t);
बाह्य संरचना c_declarator *build_attrs_declarator (वृक्षः,
						    संरचना c_declarator *);
बाह्य संरचना c_declarator *build_function_declarator (संरचना c_arg_info *,
						       संरचना c_declarator *);
बाह्य संरचना c_declarator *build_id_declarator (वृक्षः);
बाह्य संरचना c_declarator *make_pointer_declarator (संरचना c_declspecs *,
						     संरचना c_declarator *);
बाह्य संरचना c_declspecs *build_null_declspecs (शून्य);
बाह्य संरचना c_declspecs *declspecs_add_qual (location_t,
					       संरचना c_declspecs *, वृक्षः);
बाह्य संरचना c_declspecs *declspecs_add_type (location_t,
					       संरचना c_declspecs *,
					       संरचना c_typespec);
बाह्य संरचना c_declspecs *declspecs_add_scspec (location_t,
						 संरचना c_declspecs *, वृक्षः);
बाह्य संरचना c_declspecs *declspecs_add_attrs (location_t,
						संरचना c_declspecs *, वृक्षः);
बाह्य संरचना c_declspecs *declspecs_add_addrspace (location_t,
						    संरचना c_declspecs *,
						    addr_space_t);
बाह्य संरचना c_declspecs *declspecs_add_alignas (location_t,
						  संरचना c_declspecs *, वृक्षः);
बाह्य संरचना c_declspecs *finish_declspecs (संरचना c_declspecs *);
बाह्य size_t c_वृक्षः_size (गणना वृक्षः_code);
बाह्य पूर्णाङ्क c_get_loop_names (वृक्षः, bool, वृक्षः *);
बाह्य शून्य c_release_loop_names (पूर्णाङ्क);
बाह्य वृक्षः c_finish_bc_name (location_t, वृक्षः, bool);

/* in c-objc-common.cc */
बाह्य bool c_objc_common_init (शून्य);
बाह्य bool c_missing_noreturn_ok_p (वृक्षः);
बाह्य bool c_warn_unused_global_decl (const_वृक्षः);
बाह्य शून्य c_initialize_diagnostics (diagnostics::context *);
बाह्य bool c_var_mod_p (वृक्षः x, वृक्षः fn);
बाह्य alias_set_type c_get_alias_set (वृक्षः);
बाह्य पूर्णाङ्क c_type_dwarf_attribute (const_वृक्षः, पूर्णाङ्क);
बाह्य वृक्षः c_enum_underlying_base_type (const_वृक्षः);

/* in c-typeck.cc */
बाह्य पूर्णाङ्क in_alignof;
बाह्य पूर्णाङ्क in_sizeof;
बाह्य पूर्णाङ्क in_countof;
बाह्य पूर्णाङ्क in_typeof;
बाह्य पूर्णाङ्क in_generic;
बाह्य bool c_in_omp_for;
बाह्य bool c_omp_array_section_p;

बाह्य वृक्षः c_last_sizeof_arg;
बाह्य location_t c_last_sizeof_loc;

बाह्य संरचना c_switch *c_switch_राशिः;

बाह्य bool null_pointer_constant_p (const_वृक्षः);


अन्तःस्थ bool
c_type_variably_modified_p (वृक्षः t)
{
  जइ (error_mark_ग्रन्थिः == t)
    प्रत्यागम false;
  जइ (C_TYPE_VARIABLY_MODIFIED (t))
    प्रत्यागम true;
  जइ (TYPE_STRUCTURAL_EQUALITY_P (t))
    {
      /* The flag may not have been set yet because of incomplete
	 structure or union types completed later.  */
      विकल्प (वृक्षः_CODE (t))
	{
	पक्ष ARRAY_TYPE:
	पक्ष FUNCTION_TYPE:
	पक्ष POINTER_TYPE:
	  /* Recurse.  */
	  जइ (c_type_variably_modified_p (वृक्षः_TYPE (t)))
	    {
	      C_TYPE_VARIABLY_MODIFIED (t) = 1;
	      प्रत्यागम true;
	    }
	  भङ्ग;
	स्वभाव:
	  भङ्ग;
	}
    }
  प्रत्यागम false;
}

अन्तःस्थ bool
c_type_unspecified_p (वृक्षः t)
{
  प्रत्यागम error_mark_ग्रन्थिः != t
	 && C_TYPE_VARIABLE_SIZE (t) && वृक्षः_CODE (t) == ARRAY_TYPE
	 && TYPE_DOMAIN (t) && TYPE_MAX_मानम् (TYPE_DOMAIN (t))
	 && वृक्षः_CODE (TYPE_MAX_मानम् (TYPE_DOMAIN (t))) == COMPOUND_व्यञ्जकम्
	 && integer_zerop (वृक्षः_OPERAND (TYPE_MAX_मानम् (TYPE_DOMAIN (t)), 0))
	 && integer_zerop (वृक्षः_OPERAND (TYPE_MAX_मानम् (TYPE_DOMAIN (t)), 1));
}

बाह्य bool zero_length_array_type_p (const_वृक्षः type);
बाह्य bool char_type_p (वृक्षः);
बाह्य वृक्षः c_type_tag (const_वृक्षः t);
बाह्य वृक्षः c_objc_common_truthvalue_conversion (location_t, वृक्षः,
						 वृक्षः = integer_type_ग्रन्थिः);
बाह्य वृक्षः require_complete_type (location_t, वृक्षः);
बाह्य bool same_translation_unit_p (const_वृक्षः, const_वृक्षः);
बाह्य bool comptypes (वृक्षः, वृक्षः);
बाह्य bool comptypes_same_p (वृक्षः, वृक्षः);
बाह्य bool comptypes_equiv_p (वृक्षः, वृक्षः);
बाह्य bool comptypes_check_enum_int (वृक्षः, वृक्षः, bool *);
बाह्य bool c_mark_addressable (वृक्षः, bool = false, bool = false);
बाह्य शून्य c_incomplete_type_error (location_t, const_वृक्षः, const_वृक्षः);
बाह्य वृक्षः c_type_promotes_to (वृक्षः);
बाह्य संरचना c_व्यञ्जकम् default_function_array_conversion (location_t,
							संरचना c_व्यञ्जकम्);
बाह्य संरचना c_व्यञ्जकम् default_function_array_read_conversion (location_t,
							     संरचना c_व्यञ्जकम्);
बाह्य संरचना c_व्यञ्जकम् convert_lvalue_to_rvalue (location_t, संरचना c_व्यञ्जकम्,
					       bool, bool, bool = false);
बाह्य वृक्षः decl_constant_मानम्_1 (वृक्षः, bool);
बाह्य शून्य mark_exp_read (वृक्षः);
बाह्य वृक्षः composite_type (वृक्षः, वृक्षः);
बाह्य वृक्षः lookup_field (const_वृक्षः, वृक्षः);
बाह्य वृक्षः build_component_ref (location_t, वृक्षः, वृक्षः, location_t,
				 location_t);
बाह्य वृक्षः handle_counted_by_for_component_ref (location_t, वृक्षः);
बाह्य वृक्षः build_array_ref (location_t, वृक्षः, वृक्षः);
बाह्य वृक्षः build_omp_array_section (location_t, वृक्षः, वृक्षः, वृक्षः);
बाह्य वृक्षः build_external_ref (location_t, वृक्षः, bool, वृक्षः *);
बाह्य शून्य निष्कासय_maybe_used (bool);
बाह्य संरचना maybe_used_decl *save_maybe_used ();
बाह्य शून्य restore_maybe_used (संरचना maybe_used_decl *);
बाह्य शून्य mark_decl_used (वृक्षः, bool);
बाह्य संरचना c_व्यञ्जकम् c_व्यञ्जकम्_sizeof_व्यञ्जकम् (location_t, संरचना c_व्यञ्जकम्);
बाह्य संरचना c_व्यञ्जकम् c_व्यञ्जकम्_sizeof_type (location_t, संरचना c_type_name *);
बाह्य संरचना c_व्यञ्जकम् c_व्यञ्जकम्_countof_व्यञ्जकम् (location_t, संरचना c_व्यञ्जकम्);
बाह्य संरचना c_व्यञ्जकम् c_व्यञ्जकम्_countof_type (location_t loc,
					  संरचना c_type_name *);
बाह्य संरचना c_व्यञ्जकम् c_व्यञ्जकम्_maxof_type (location_t loc, संरचना c_type_name *);
बाह्य संरचना c_व्यञ्जकम् c_व्यञ्जकम्_minof_type (location_t loc, संरचना c_type_name *);
बाह्य संरचना c_व्यञ्जकम् parser_build_unary_op (location_t, गणना वृक्षः_code,
    					    संरचना c_व्यञ्जकम्);
बाह्य संरचना c_व्यञ्जकम् parser_build_द्विमान_op (location_t,
    					     गणना वृक्षः_code, संरचना c_व्यञ्जकम्,
					     संरचना c_व्यञ्जकम्, वृक्षः);
बाह्य वृक्षः build_conditional_व्यञ्जकम् (location_t, वृक्षः, bool, वृक्षः, वृक्षः,
				    location_t, वृक्षः, वृक्षः, location_t);
बाह्य वृक्षः build_compound_व्यञ्जकम् (location_t, वृक्षः, वृक्षः);
बाह्य वृक्षः c_cast_व्यञ्जकम् (location_t, संरचना c_type_name *, वृक्षः);
बाह्य वृक्षः build_c_cast (location_t, वृक्षः, वृक्षः);
बाह्य शून्य store_init_मानम् (location_t, वृक्षः, वृक्षः, वृक्षः);
बाह्य शून्य maybe_warn_string_init (location_t, वृक्षः, संरचना c_व्यञ्जकम्);
बाह्य शून्य start_init (वृक्षः, वृक्षः, bool, bool, rich_location *);
बाह्य शून्य finish_init (शून्य);
बाह्य शून्य really_start_incremental_init (वृक्षः);
बाह्य शून्य finish_implicit_inits (location_t, संरचना obstack *);
बाह्य शून्य प्रक्षिप_init_level (location_t, पूर्णाङ्क, संरचना obstack *);
बाह्य संरचना c_व्यञ्जकम् निष्कासय_init_level (location_t, पूर्णाङ्क, संरचना obstack *,
				     location_t);
बाह्य शून्य set_init_index (location_t, वृक्षः, वृक्षः, संरचना obstack *);
बाह्य शून्य set_init_label (location_t, वृक्षः, location_t, संरचना obstack *);
unsigned c_maybe_optimize_large_byte_initializer (शून्य);
बाह्य शून्य process_init_element (location_t, संरचना c_व्यञ्जकम्, bool,
				  संरचना obstack *);
बाह्य वृक्षः build_compound_literal (location_t, वृक्षः, वृक्षः, bool,
				    unsigned पूर्णाङ्क, संरचना c_declspecs *);
बाह्य शून्य check_compound_literal_type (location_t, संरचना c_type_name *);
बाह्य वृक्षः c_start_switch (location_t, location_t, वृक्षः, bool, वृक्षः);
बाह्य शून्य c_finish_switch (वृक्षः, वृक्षः);
बाह्य वृक्षः build_asm_व्यञ्जकम् (location_t, वृक्षः, वृक्षः, वृक्षः, वृक्षः, वृक्षः, bool,
			    bool);
बाह्य वृक्षः build_asm_stmt (bool, वृक्षः);
बाह्य पूर्णाङ्क c_types_compatible_p (वृक्षः, वृक्षः);
बाह्य वृक्षः c_begin_compound_stmt (bool);
बाह्य वृक्षः c_end_compound_stmt (location_t, वृक्षः, bool);
बाह्य शून्य c_finish_if_stmt (location_t, वृक्षः, वृक्षः, वृक्षः);
बाह्य शून्य c_finish_loop (location_t, location_t, वृक्षः, location_t, वृक्षः,
			   वृक्षः, वृक्षः, वृक्षः, bool);
बाह्य वृक्षः c_begin_stmt_व्यञ्जकम् (शून्य);
बाह्य वृक्षः c_finish_stmt_व्यञ्जकम् (location_t, वृक्षः);
बाह्य वृक्षः c_process_व्यञ्जकम्_stmt (location_t, वृक्षः);
बाह्य वृक्षः c_finish_व्यञ्जकम्_stmt (location_t, वृक्षः);
बाह्य वृक्षः c_finish_return (location_t, वृक्षः, वृक्षः, bool = false);
बाह्य वृक्षः c_finish_bc_stmt (location_t, वृक्षः, bool, वृक्षः);
बाह्य वृक्षः c_finish_goto_label (location_t, वृक्षः);
बाह्य वृक्षः c_finish_goto_ptr (location_t, c_व्यञ्जकम् val);
बाह्य वृक्षः c_व्यञ्जकम्_to_decl (वृक्षः, bool *, bool *);
बाह्य वृक्षः c_finish_omp_construct (location_t, गणना वृक्षः_code, वृक्षः, वृक्षः);
बाह्य वृक्षः c_finish_oacc_data (location_t, वृक्षः, वृक्षः);
बाह्य वृक्षः c_finish_oacc_host_data (location_t, वृक्षः, वृक्षः);
बाह्य वृक्षः c_begin_omp_parallel (शून्य);
बाह्य वृक्षः c_finish_omp_parallel (location_t, वृक्षः, वृक्षः);
बाह्य वृक्षः c_begin_omp_task (शून्य);
बाह्य वृक्षः c_finish_omp_task (location_t, वृक्षः, वृक्षः);
बाह्य शून्य c_finish_omp_cancel (location_t, वृक्षः);
बाह्य शून्य c_finish_omp_cancellation_point (location_t, वृक्षः);
बाह्य वृक्षः c_finish_omp_clauses (वृक्षः, गणना c_omp_region_type);
बाह्य वृक्षः c_omp_finish_mapper_clauses (वृक्षः);
बाह्य वृक्षः c_omp_mapper_lookup (वृक्षः, वृक्षः);
बाह्य वृक्षः c_omp_extract_mapper_directive (वृक्षः);
बाह्य वृक्षः c_omp_map_array_section (location_t, वृक्षः);
बाह्य वृक्षः c_build_va_arg (location_t, वृक्षः, location_t, वृक्षः, वृक्षः);
बाह्य वृक्षः c_finish_transaction (location_t, वृक्षः, पूर्णाङ्क);
बाह्य bool c_वृक्षः_equal (वृक्षः, वृक्षः);
बाह्य वृक्षः c_build_function_call_vec (location_t, ध्रुव vec<location_t>&,
				       वृक्षः, vec<वृक्षः, va_gc> *,
				       vec<वृक्षः, va_gc> *);
बाह्य वृक्षः c_omp_clause_copy_ctor (वृक्षः, वृक्षः, वृक्षः);
बाह्य वृक्षः c_reconstruct_complex_type (वृक्षः, वृक्षः);
बाह्य वृक्षः c_type_canonical (वृक्षः);
बाह्य वृक्षः c_build_type_attribute_variant (वृक्षः ntype, वृक्षः attrs);
बाह्य वृक्षः c_build_pointer_type (वृक्षः type);
बाह्य वृक्षः c_build_array_type (वृक्षः type, वृक्षः domain);
बाह्य वृक्षः c_build_array_type_unspecified (वृक्षः type);
बाह्य वृक्षः c_build_array_type_zero_size (वृक्षः type);
बाह्य वृक्षः c_build_function_type (वृक्षः type, वृक्षः args, bool no = false);
बाह्य वृक्षः c_build_pointer_type_for_mode (वृक्षः type, machine_mode mode, bool m);

/* Set to 0 at beginning of a function definition, set to 1 if
   a return statement that specifies a return value is seen.  */

बाह्य पूर्णाङ्क current_function_returns_मानम्;

/* Set to 0 at beginning of a function definition, set to 1 if
   a return statement with no argument is seen.  */

बाह्य पूर्णाङ्क current_function_returns_null;

/* Set to 0 at beginning of a function definition, set to 1 if
   a call to a noreturn function is seen.  */

बाह्य पूर्णाङ्क current_function_returns_abnormally;

/* In c-decl.cc */

/* Tell the binding oracle what kind of binding we are looking for.  */

गणना c_oracle_request
{
  C_ORACLE_चिह्नम्,
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

प्रकारनिर्देश शून्य c_binding_oracle_function (गणना c_oracle_request, वृक्षः identifier);

बाह्य c_binding_oracle_function *c_binding_oracle;

बाह्य शून्य c_finish_incomplete_decl (वृक्षः);
बाह्य वृक्षः c_omp_reduction_id (गणना वृक्षः_code, वृक्षः);
बाह्य वृक्षः c_omp_reduction_decl (वृक्षः);
बाह्य वृक्षः c_omp_reduction_lookup (वृक्षः, वृक्षः);
बाह्य वृक्षः c_check_omp_declare_reduction_r (वृक्षः *, पूर्णाङ्क *, शून्य *);
बाह्य वृक्षः c_omp_mapper_id (वृक्षः);
बाह्य वृक्षः c_omp_mapper_decl (वृक्षः);
बाह्य शून्य c_omp_scan_mapper_bindings (location_t, वृक्षः *, वृक्षः);
बाह्य bool c_check_in_current_scope (वृक्षः);
बाह्य शून्य c_pushtag (location_t, वृक्षः, वृक्षः);
बाह्य शून्य c_bind (location_t, वृक्षः, bool);
बाह्य bool tag_exists_p (गणना वृक्षः_code, वृक्षः);

बाह्य शून्य verify_counted_by_for_शिखरम्_anonymous_type (वृक्षः);

/* In c-errors.cc */
बाह्य bool pedwarn_c90 (location_t, diagnostics::option_id, ध्रुव वर्ण *, ...)
    ATTRIBUTE_GCC_DIAG(3,4);
बाह्य bool pedwarn_c99 (location_t, diagnostics::option_id, ध्रुव वर्ण *, ...)
    ATTRIBUTE_GCC_DIAG(3,4);
बाह्य bool pedwarn_c11 (location_t, diagnostics::option_id, ध्रुव वर्ण *, ...)
    ATTRIBUTE_GCC_DIAG(3,4);
बाह्य bool pedwarn_c23 (location_t, diagnostics::option_id, ध्रुव वर्ण *, ...)
    ATTRIBUTE_GCC_DIAG(3,4);
बाह्य शून्य add_note_about_new_keyword (location_t loc,
					वृक्षः keyword_id);

बाह्य शून्य
set_c_व्यञ्जकम्_source_range (c_व्यञ्जकम् *व्यञ्जकम्,
			 location_t start, location_t finish);

बाह्य शून्य
set_c_व्यञ्जकम्_source_range (c_व्यञ्जकम् *व्यञ्जकम्,
			 source_range src_range);

/* In c-fold.cc */
बाह्य vec<वृक्षः> incomplete_record_decls;

बाह्य ध्रुव वर्ण *c_get_sarif_source_language (ध्रुव वर्ण *filename);

बाह्य ध्रुव संरचना scoped_attribute_specs std_attribute_table;

#जइ CHECKING_P
namespace selftest {
  बाह्य शून्य run_c_tests (शून्य);
} // namespace selftest
#endif /* #if CHECKING_P */


#endif /* ! GCC_C_TREE_H */
