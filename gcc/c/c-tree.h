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

#अगर_अघोषित GCC_C_वृक्ष_H
#घोषणा GCC_C_वृक्ष_H

#समावेश "c-family/c-common.h"
#समावेश "diagnostic.h"

/* struct lang_identifier is private to c-decl.cc, but langhooks.cc needs to
   know how big it is.  This is sanity-checked in c-decl.cc.  */
#घोषणा C_SIZEOF_STRUCT_LANG_IDENTIFIER \
  (माप (काष्ठा c_common_identifier) + 3 * माप (व्योम *))

/* In a RECORD_TYPE or UNION_TYPE, nonzero if any component is read-only.  */
#घोषणा C_TYPE_FIELDS_READONLY(TYPE) वृक्ष_LANG_FLAG_1 (TYPE)

/* In a RECORD_TYPE or UNION_TYPE, nonzero if any component is volatile.  */
#घोषणा C_TYPE_FIELDS_VOLATILE(TYPE) वृक्ष_LANG_FLAG_2 (TYPE)

/* In a RECORD_TYPE or UNION_TYPE, nonzero if any component is
   volatile, restrict-qualified or atomic; that is, has a type not
   permitted for a constexpr object.  */
#घोषणा C_TYPE_FIELDS_NON_CONSTEXPR(TYPE) वृक्ष_LANG_FLAG_4 (TYPE)

/* In a RECORD_TYPE or UNION_TYPE, nonzero if any component has a
   counted_by attribute.  */
#घोषणा C_TYPE_FIELDS_HAS_COUNTED_BY(TYPE) TYPE_LANG_FLAG_3 (TYPE)

/* In a RECORD_TYPE or UNION_TYPE or ENUMERAL_TYPE
   nonzero if the definition of the type has already started.  */
#घोषणा C_TYPE_BEING_DEFINED(TYPE) TYPE_LANG_FLAG_0 (TYPE)

/* In an incomplete RECORD_TYPE, UNION_TYPE or ENUMERAL_TYPE, a list of
   variable declarations whose type would be completed by completing
   that type.  */
#घोषणा C_TYPE_INCOMPLETE_VARS(TYPE) \
  TYPE_LANG_SLOT_1 (वृक्ष_CHECK4 (TYPE, RECORD_TYPE, UNION_TYPE, \
				 QUAL_UNION_TYPE, ENUMERAL_TYPE))

/* In an IDENTIFIER_NODE, nonzero if this identifier is actually a
   keyword.  C_RID_CODE (node) is then the RID_* value of the keyword.  */
#घोषणा C_IS_RESERVED_WORD(ID) वृक्ष_LANG_FLAG_0 (ID)

/* Record whether a type or decl was written with nonconstant size.
   Note that TYPE_SIZE may have simplified to a constant.  */
#घोषणा C_TYPE_VARIABLE_आकार(TYPE) TYPE_LANG_FLAG_1 (TYPE)
#घोषणा C_DECL_VARIABLE_आकार(TYPE) DECL_LANG_FLAG_0 (TYPE)

/* Record whether a type is variably modified. */
#घोषणा C_TYPE_VARIABLY_MODIFIED(TYPE) TYPE_LANG_FLAG_6 (TYPE)


/* Record whether a type is defined inside a struct or union type.
   This is used for -Wc++-compat. */
#घोषणा C_TYPE_DEFINED_IN_STRUCT(TYPE) TYPE_LANG_FLAG_2 (TYPE)

/* Record whether a typedef for type `int' was actually `signed int'.  */
#घोषणा C_TYPEDEF_EXPLICITLY_SIGNED(EXP) DECL_LANG_FLAG_1 (EXP)

/* For a FUNCTION_DECL, nonzero if it was defined without an explicit
   return type.  */
#घोषणा C_FUNCTION_IMPLICIT_INT(EXP) DECL_LANG_FLAG_1 (EXP)

/* For a FUNCTION_DECL, nonzero if it was an implicit declaration.  */
#घोषणा C_DECL_IMPLICIT(EXP) DECL_LANG_FLAG_2 (EXP)

/* For a PARM_DECL, nonzero if it was declared as an array.  */
#घोषणा C_ARRAY_PARAMETER(गाँठ_2) DECL_LANG_FLAG_0 (गाँठ_2)

/* For FUNCTION_DECLs, evaluates true if the decl is a nested
   function that requires a non-local context.  */
#घोषणा C_FUNC_NONLOCAL_CONTEXT(EXP)		\
  DECL_LANG_FLAG_4 (FUNCTION_DECL_CHECK (EXP))

/* For FUNCTION_DECLs, evaluates true if the decl is built-in but has
   been declared.  */
#घोषणा C_DECL_DECLARED_BUILTIN(EXP)		\
  DECL_LANG_FLAG_3 (FUNCTION_DECL_CHECK (EXP))

/* For FUNCTION_DECLs, evaluates true if the decl is built-in, has a
   built-in prototype and does not have a non-built-in prototype.  */
#घोषणा C_DECL_BUILTIN_PROTOTYPE(EXP)		\
  DECL_LANG_FLAG_6 (FUNCTION_DECL_CHECK (EXP))

/* For LABEL_DECLs marks canonical name of a loop.  */
#घोषणा C_DECL_LOOP_NAME(EXP) DECL_LANG_FLAG_3 (LABEL_DECL_CHECK (EXP))

/* For LABEL_DECLs marks canonical name of a switch.  During parsing of
   ObjC foreach named loop both C_DECL_LOOP_NAME and C_DECL_SWITCH_NAME
   are temporarily set.  */
#घोषणा C_DECL_SWITCH_NAME(EXP) DECL_LANG_FLAG_5 (LABEL_DECL_CHECK (EXP))

/* For LABEL_DECLs marks canonical name of a loop or switch being
   valid for use in break identifier or continue identifier statements.  */
#घोषणा C_DECL_LOOP_SWITCH_NAME_VALID(EXP) \
  DECL_LANG_FLAG_6 (LABEL_DECL_CHECK (EXP))

/* For LABEL_DECLs marks canonical loop or switch names which were actually
   used in one or more break identifier or continue identifier statements.  */
#घोषणा C_DECL_LOOP_SWITCH_NAME_USED(EXP) \
  DECL_LANG_FLAG_8 (LABEL_DECL_CHECK (EXP))

/* Record whether a decl was declared register.  This is strictly a
   front-end flag, whereas DECL_REGISTER is used for code generation;
   they may differ for structures with volatile fields.  */
#घोषणा C_DECL_REGISTER(EXP) \
  DECL_LANG_FLAG_4 (वृक्ष_NOT_CHECK (EXP, FUNCTION_DECL))

/* Record whether a decl was used in an expression anywhere except an
   unevaluated operand of sizeof / typeof / alignof.  This is only
   used for functions declared static but not defined, though outside
   sizeof and typeof it is set for other function decls as well.  */
#घोषणा C_DECL_USED(EXP) DECL_LANG_FLAG_5 (FUNCTION_DECL_CHECK (EXP))

/* Record whether a variable has been declared threadprivate by
   #pragma omp threadprivate.  */
#घोषणा C_DECL_THREADPRIVATE_P(DECL) DECL_LANG_FLAG_3 (VAR_DECL_CHECK (DECL))

/* Set on VAR_DECLs for compound literals.  */
#घोषणा C_DECL_COMPOUND_LITERAL_P(DECL) \
  DECL_LANG_FLAG_5 (VAR_DECL_CHECK (DECL))

/* Set on decls used as placeholders for a C23 underspecified object
   definition.  */
#घोषणा C_DECL_UNDERSPECIFIED(DECL) DECL_LANG_FLAG_7 (DECL)

/* Set on VAR_DECLs declared as 'constexpr'.  */
#घोषणा C_DECL_DECLARED_CONSTEXPR(DECL) \
  DECL_LANG_FLAG_8 (VAR_DECL_CHECK (DECL))

/* Nonzero for a decl which either doesn't exist or isn't a prototype.
   N.B. Could be simplified if all built-in decls had complete prototypes
   (but this is presently difficult because some of them need FILE*).  */
#घोषणा C_DECL_ISNT_PROTOTYPE(EXP)			\
       (EXP == 0					\
	|| (!prototype_p (वृक्ष_TYPE (EXP))	\
	    && !fndecl_built_in_p (EXP)))

/* For FUNCTION_TYPE, a hidden list of types of arguments.  The same as
   TYPE_ARG_TYPES for functions with prototypes, but created for functions
   without prototypes.  */
#घोषणा TYPE_ACTUAL_ARG_TYPES(गाँठ_2) \
  TYPE_LANG_SLOT_1 (FUNCTION_TYPE_CHECK (गाँठ_2))

/* For a CONSTRUCTOR, whether some initializer contains a
   subexpression meaning it is not a constant expression.  */
#घोषणा CONSTRUCTOR_NON_CONST(व्यंजक_2) वृक्ष_LANG_FLAG_1 (CONSTRUCTOR_CHECK (व्यंजक_2))

/* For a SAVE_EXPR, nonzero if the operand of the SAVE_EXPR has already
   been folded.  */
#घोषणा SAVE_व्यंजक_FOLDED_P(EXP)	वृक्ष_LANG_FLAG_1 (SAVE_व्यंजक_CHECK (EXP))

/* Whether a type has boolean semantics: either a boolean type or an
   enumeration type with a boolean type as its underlying type.  */
#घोषणा C_BOOLEAN_TYPE_P(TYPE)						\
  (वृक्ष_CODE (TYPE) == BOOLEAN_TYPE					\
   || (वृक्ष_CODE (TYPE) == ENUMERAL_TYPE				\
       && ENUM_UNDERLYING_TYPE (TYPE) != NULL_वृक्ष			\
       && (वृक्ष_CODE (ENUM_UNDERLYING_TYPE (TYPE)) == BOOLEAN_TYPE	\
	   || c_hardbool_type_attr (TYPE))))

/* Record parser information about an expression that is irrelevant
   for code generation alongside a tree representing its value.  */
काष्ठा c_व्यंजक
{
  /* The value of the expression.  */
  वृक्ष मूल्य;
  /* Record the original unary/binary operator of an expression, which may
     have been changed by fold, STRING_CST for unparenthesized string
     constants, C_MAYBE_CONST_EXPR for __builtin_constant_p calls
     (even if parenthesized), for subexpressions, and for non-constant
     initializers, or ERROR_MARK for other expressions (including
     parenthesized expressions).  */
  क्रमागत वृक्ष_code original_code;
  /* If not NULL, the original type of an expression.  This will
     differ from the type of the value field for an enum constant.
     The type of an enum constant is a plain integer type, but this
     field will be the enum type.  */
  वृक्ष original_type;

  /* The source range of this expression.  This is redundant
     for node values that have locations, but not all node kinds
     have locations (e.g. constants, and references to params, locals,
     etc), so we stash a copy here.  */
  source_range src_range;

  /* True if this was directly from a decimal constant token.  */
  bool m_decimal : 1;

  /* Access to the first and last locations within the source spelling
     of this expression.  */
  location_t get_start () स्थिर { वापस src_range.m_start; }
  location_t get_finish () स्थिर { वापस src_range.m_finish; }

  location_t get_location () स्थिर
  {
    अगर (व्यंजक_HAS_LOCATION (मूल्य))
      वापस व्यंजक_LOCATION (मूल्य);
    अन्यथा
      वापस make_location (get_start (), get_start (), get_finish ());
  }

  /* Set the value to error_mark_node whilst ensuring that src_range
     and m_decimal are initialized.  */
  व्योम set_error ()
  {
    मूल्य = error_mark_गाँठ;
    src_range.m_start = UNKNOWN_LOCATION;
    src_range.m_finish = UNKNOWN_LOCATION;
    m_decimal = 0;
  }
};

/* Type alias for struct c_expr. This allows to use the structure
   inside the VEC types.  */
प्रकार काष्ठा c_व्यंजक c_व्यंजक_t;

/* A kind of type specifier.  Note that this information is currently
   only used to distinguish tag definitions, tag references and typeof
   uses.  */
क्रमागत c_typespec_kind {
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
काष्ठा c_typespec {
  /* What kind of type specifier this is.  */
  क्रमागत c_typespec_kind kind;
  /* Whether the expression has operands suitable for use in constant
     expressions.  */
  bool व्यंजक_const_operands;
  /* Whether the type specifier includes an enum type specifier (that
     is, ": specifier-qualifier-list" in a declaration using
     "enum").  */
  bool has_enum_type_specifier;
  /* The specifier itself.  */
  वृक्ष spec;
  /* An expression to be evaluated before the type specifier, in the
     case of typeof specifiers, or NULL otherwise or if no such
     expression is required for a particular typeof specifier.  In
     particular, when typeof is applied to an expression of variably
     modified type, that expression must be evaluated in order to
     determine array sizes that form part of the type, but the
     expression itself (as opposed to the array sizes) forms no part
     of the type and so needs to be recorded separately.  */
  वृक्ष व्यंजक;
};

/* A storage class specifier.  */
क्रमागत c_storage_class {
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
क्रमागत c_typespec_keyword {
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
क्रमागत c_declspec_word {
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
  cdw_संख्या_of_elements /* This one must always be the last
			    enumerator.  */
};

क्रमागत c_declspec_il {
  cdil_none,
  cdil_gimple,		/* __GIMPLE  */
  cdil_gimple_cfg,	/* __GIMPLE(cfg)  */
  cdil_gimple_ssa,	/* __GIMPLE(ssa)  */
  cdil_rtl		/* __RTL  */
};

/* A sequence of declaration specifiers in C.  When a new declaration
   specifier is added, please update the enum c_declspec_word above
   accordingly.  */
काष्ठा c_declspecs {
  location_t locations[cdw_संख्या_of_elements];
  /* The type specified, if a single type specifier such as a struct,
     union or enum specifier, typedef name or typeof specifies the
     whole type, or NULL_TREE if none or a keyword such as "void" or
     "char" is used.  Does not include qualifiers.  */
  वृक्ष type;
  /* Any expression to be evaluated before the type, from a typeof
     specifier.  */
  वृक्ष व्यंजक;
  /* The attributes from a typedef decl.  */
  वृक्ष decl_attr;
  /* When parsing, the GNU attributes and prefix standard attributes.
     Outside the parser, this will be NULL; attributes (possibly from
     multiple lists) will be passed separately.  */
  वृक्ष attrs;
  /* When parsing, postfix standard attributes (which appertain to the
     type specified by the preceding declaration specifiers, unlike
     prefix standard attributes which appertain to the declaration or
     declarations as a whole).  */
  वृक्ष postfix_attrs;
  /* The pass to start compiling a __GIMPLE or __RTL function with.  */
  अक्षर *gimple_or_rtl_pass;
  /* ENTRY BB count.  */
  profile_गिनती entry_bb_गिनती;
  /* The base-2 log of the greatest alignment required by an _Alignas
     specifier, in bytes, or -1 if no such specifiers with nonzero
     alignment.  */
  पूर्णांक align_log;
  जोड़ {
    /* For the __intN declspec, this stores the index into the int_n_*
       arrays.  */
    पूर्णांक int_n_idx;
    /* For the _FloatN and _FloatNx declspec, this stores the index into
       the floatn_nx_types array.  */
    पूर्णांक floatn_nx_idx;
    /* For _BitInt(N) this stores the N.  */
    पूर्णांक bitint_prec;
  } u;
  /* The storage class specifier, or csc_none if none.  */
  क्रमागत c_storage_class storage_class;
  /* Any type specifier keyword used such as "int", not reflecting
     modifiers such as "short", or cts_none if none.  */
  क्रमागत c_typespec_keyword typespec_word : 8;
  /* The kind of type specifier if one has been seen, ctsk_none
     otherwise.  */
  क्रमागत c_typespec_kind typespec_kind : 4;
  क्रमागत c_declspec_il declspec_il : 3;
  /* Whether any expressions in typeof specifiers may appear in
     constant expressions.  */
  bool व्यंजक_const_operands : 1;
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
क्रमागत c_declarator_kind {
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

काष्ठा c_arg_tag {
  /* The argument name.  */
  वृक्ष id;
  /* The type of the argument.  */
  वृक्ष type;
};


/* Information about the parameters in a function declarator.  */
काष्ठा c_arg_info {
  /* A list of parameter decls.  */
  वृक्ष parms;
  /* A list of structure, union and enum tags defined.  */
  vec<c_arg_tag, va_gc> *tags;
  /* A list of argument types to go in the FUNCTION_TYPE.  */
  वृक्ष types;
  /* A list of non-parameter decls (notably enumeration constants)
     defined with the parameters.  */
  वृक्ष others;
  /* A compound expression of VLA sizes from the parameters, or NULL.
     In a function definition, these are used to ensure that
     side-effects in sizes of arrays converted to pointers (such as a
     parameter int i[n++]) take place; otherwise, they are
     ignored.  */
  वृक्ष pending_sizes;
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
काष्ठा c_declarator {
  /* The kind of declarator.  */
  क्रमागत c_declarator_kind kind;
  location_t id_loc; /* Currently only set for cdk_id, cdk_array. */
  /* Except for cdk_id, the contained declarator.  For cdk_id, NULL.  */
  काष्ठा c_declarator *declarator;
  जोड़ {
    /* For identifiers.  */
    काष्ठा {
      /* An IDENTIFIER_NODE, or NULL_TREE if an abstract
	 declarator.  */
      वृक्ष id;
      /* Any attributes (which apply to the declaration rather than to
	 the type described by the outer declarators).  */
      वृक्ष attrs;
    } id;
    /* For functions.  */
    काष्ठा c_arg_info *arg_info;
    /* For arrays.  */
    काष्ठा {
      /* The array dimension, or NULL for [] and [*].  */
      वृक्ष dimen;
      /* The qualifiers inside [].  */
      पूर्णांक quals;
      /* The attributes (currently ignored) inside [].  */
      वृक्ष attrs;
      /* Whether [static] was used.  */
      bool static_p : 1;
      /* Whether [*] was used.  */
      bool vla_unspec_p : 1;
    } array;
    /* For pointers, the qualifiers on the pointer type.  */
    पूर्णांक pointer_quals;
    /* For attributes.  */
    वृक्ष attrs;
  } u;
};

/* A type name.  */
काष्ठा c_type_name {
  /* The declaration specifiers.  */
  काष्ठा c_declspecs *specs;
  /* The declarator.  */
  काष्ठा c_declarator *declarator;
};

/* A parameter.  */
काष्ठा c_parm {
  /* The declaration specifiers, minus any prefix attributes.  */
  काष्ठा c_declspecs *specs;
  /* The attributes.  */
  वृक्ष attrs;
  /* The declarator.  */
  काष्ठा c_declarator *declarator;
  /* The location of the parameter.  */
  location_t loc;
};

/* Used when parsing an enum.  Initialized by start_enum.  */
काष्ठा c_enum_contents
{
  /* While defining an enum type, this is 1 plus the last enumerator
     constant value.  */
  वृक्ष enum_अग्र_मूल्य;

  /* The enumeration type itself.  */
  वृक्ष enum_type;

  /* Nonzero means that there was overflow computing enum_next_value.  */
  पूर्णांक enum_overflow;
};

/* A type of reference to a static identifier in an inline
   function.  */
क्रमागत c_inline_static_type {
  /* Identifier with internal linkage used in function that may be an
     inline definition (i.e., file-scope static).  */
  csi_internal,
  /* Modifiable object with static storage duration defined in
     function that may be an inline definition (i.e., local
     static).  */
  csi_modifiable
};

/* Record details of decls possibly used inside sizeof or typeof.  */
काष्ठा maybe_used_decl
{
  /* The decl.  */
  वृक्ष decl;
  /* The level seen at (in_sizeof + in_typeof + in_countof + in_generic).  */
  पूर्णांक level;
  /* Seen in address-of.  */
  bool address;
  /* The next one at this level or above, or NULL.  */
  काष्ठा maybe_used_decl *अग्र;
};


/* in c-parser.cc */
काष्ठा c_वृक्ष_token_vec;
बाह्य व्योम c_parse_init (व्योम);
बाह्य bool c_keyword_starts_typename (क्रमागत rid keyword);

/* in c-aux-info.cc */
बाह्य व्योम gen_aux_info_record (वृक्ष, पूर्णांक, पूर्णांक, पूर्णांक);

/* in c-decl.cc */
काष्ठा c_spot_bindings;
class c_struct_parse_info;
बाह्य काष्ठा obstack parser_obstack;
/* Set to IN_ITERATION_STMT if parsing an iteration-statement,
   to IN_OMP_BLOCK if parsing OpenMP structured block and
   IN_OMP_FOR if parsing OpenMP loop.  If parsing a switch statement,
   this is bitwise ORed with IN_SWITCH_STMT, unless parsing an
   iteration-statement, OpenMP block or loop within that switch.
   If the innermost iteration/switch statement is named, IN_NAMED_STMT
   is additionally bitwise ORed into it.  */
#घोषणा IN_SWITCH_STMT		1
#घोषणा IN_ITERATION_STMT	2
#घोषणा IN_OMP_BLOCK		4
#घोषणा IN_OMP_FOR		8
#घोषणा IN_OBJC_FOREACH		16
#घोषणा IN_NAMED_STMT		32
बाह्य अचिन्हित अक्षर in_statement;

बाह्य bool switch_statement_break_seen_p;

बाह्य bool global_bindings_p (व्योम);
बाह्य वृक्ष pushdecl (वृक्ष);
बाह्य अचिन्हित पूर्णांक start_underspecified_init (location_t, वृक्ष);
बाह्य व्योम finish_underspecified_init (वृक्ष, अचिन्हित पूर्णांक);
बाह्य व्योम धकेलो_scope (व्योम);
बाह्य वृक्ष निकालो_scope (व्योम);
बाह्य व्योम c_mark_decl_jump_unsafe_in_current_scope ();
बाह्य व्योम c_bindings_start_stmt_व्यंजक (काष्ठा c_spot_bindings *);
बाह्य व्योम c_bindings_end_stmt_व्यंजक (काष्ठा c_spot_bindings *);

बाह्य व्योम record_inline_static (location_t, वृक्ष, वृक्ष,
				  क्रमागत c_inline_static_type);
बाह्य व्योम c_init_decl_processing (व्योम);
बाह्य व्योम c_print_identifier (खाता *, वृक्ष, पूर्णांक);
बाह्य पूर्णांक quals_from_declspecs (स्थिर काष्ठा c_declspecs *);
बाह्य काष्ठा c_declarator *build_array_declarator (location_t, वृक्ष,
    						    काष्ठा c_declspecs *,
						    bool, bool);
बाह्य वृक्ष build_enumerator (location_t, location_t, काष्ठा c_enum_contents *,
			      वृक्ष, वृक्ष);
बाह्य वृक्ष check_for_loop_decls (location_t, bool);
बाह्य व्योम mark_forward_parm_decls (व्योम);
बाह्य व्योम declare_parm_level (व्योम);
बाह्य व्योम undeclared_variable (location_t, वृक्ष);
बाह्य वृक्ष lookup_label_for_goto (location_t, वृक्ष);
बाह्य वृक्ष declare_label (वृक्ष);
बाह्य वृक्ष define_label (location_t, वृक्ष);
बाह्य काष्ठा c_spot_bindings *c_get_switch_bindings (व्योम);
बाह्य व्योम c_release_switch_bindings (काष्ठा c_spot_bindings *);
बाह्य bool c_check_switch_jump_warnings (काष्ठा c_spot_bindings *,
					  location_t, location_t);
बाह्य व्योम finish_decl (वृक्ष, location_t, वृक्ष, वृक्ष, वृक्ष);
बाह्य वृक्ष finish_enum (वृक्ष, वृक्ष, वृक्ष);
बाह्य व्योम finish_function (location_t = निवेश_location);
बाह्य वृक्ष finish_struct (location_t, वृक्ष, वृक्ष, वृक्ष,
			   class c_struct_parse_info *,
			   वृक्ष *व्यंजक = शून्य);
बाह्य वृक्ष c_simulate_enum_decl (location_t, स्थिर अक्षर *,
				  vec<string_int_pair> *);
बाह्य वृक्ष c_simulate_record_decl (location_t, स्थिर अक्षर *,
				    array_slice<स्थिर वृक्ष>);
बाह्य काष्ठा c_arg_info *build_arg_info (व्योम);
बाह्य काष्ठा c_arg_info *get_parm_info (bool, वृक्ष);
बाह्य वृक्ष grokfield (location_t, काष्ठा c_declarator *,
		       काष्ठा c_declspecs *, वृक्ष, वृक्ष *, वृक्ष *);
बाह्य वृक्ष groktypename (काष्ठा c_type_name *, वृक्ष *, bool *);
बाह्य वृक्ष grokgenassoc (काष्ठा c_type_name *);
बाह्य वृक्ष grokparm (स्थिर काष्ठा c_parm *, वृक्ष *);
बाह्य वृक्ष implicitly_declare (location_t, वृक्ष);
बाह्य व्योम keep_अग्र_level (व्योम);
बाह्य व्योम pending_xref_error (व्योम);
बाह्य व्योम c_धकेलो_function_context (व्योम);
बाह्य व्योम c_निकालो_function_context (व्योम);
बाह्य व्योम धकेलो_parm_decl (स्थिर काष्ठा c_parm *, वृक्ष *);
बाह्य काष्ठा c_declarator *set_array_declarator_inner (काष्ठा c_declarator *,
							काष्ठा c_declarator *);
बाह्य वृक्ष c_builtin_function (वृक्ष);
बाह्य वृक्ष c_builtin_function_ext_scope (वृक्ष);
बाह्य वृक्ष c_simulate_builtin_function_decl (वृक्ष);
बाह्य व्योम c_warn_unused_attributes (वृक्ष);
बाह्य वृक्ष c_warn_type_attributes (वृक्ष, वृक्ष);
बाह्य व्योम shadow_tag (स्थिर काष्ठा c_declspecs *);
बाह्य व्योम shadow_tag_warned (स्थिर काष्ठा c_declspecs *, पूर्णांक);
बाह्य वृक्ष start_enum (location_t, काष्ठा c_enum_contents *, वृक्ष, वृक्ष,
			bool potential_nesting_p);
बाह्य bool start_function (काष्ठा c_declspecs *, काष्ठा c_declarator *, वृक्ष);
बाह्य वृक्ष start_decl (काष्ठा c_declarator *, काष्ठा c_declspecs *, bool,
			वृक्ष, bool = true, location_t * = शून्य);
बाह्य वृक्ष start_struct (location_t, क्रमागत वृक्ष_code, वृक्ष,
			  class c_struct_parse_info **);
बाह्य व्योम store_parm_decls (व्योम);
बाह्य व्योम store_parm_decls_from (काष्ठा c_arg_info *);
बाह्य व्योम अस्थायी_store_parm_decls (वृक्ष, वृक्ष);
बाह्य व्योम अस्थायी_निकालो_parm_decls (व्योम);
बाह्य वृक्ष xref_tag (क्रमागत वृक्ष_code, वृक्ष);
बाह्य काष्ठा c_typespec parser_xref_tag (location_t, क्रमागत वृक्ष_code, वृक्ष,
					  bool, वृक्ष, bool);
बाह्य काष्ठा c_parm *build_c_parm (काष्ठा c_declspecs *, वृक्ष,
				    काष्ठा c_declarator *, location_t);
बाह्य काष्ठा c_declarator *build_attrs_declarator (वृक्ष,
						    काष्ठा c_declarator *);
बाह्य काष्ठा c_declarator *build_function_declarator (काष्ठा c_arg_info *,
						       काष्ठा c_declarator *);
बाह्य काष्ठा c_declarator *build_id_declarator (वृक्ष);
बाह्य काष्ठा c_declarator *make_pointer_declarator (काष्ठा c_declspecs *,
						     काष्ठा c_declarator *);
बाह्य काष्ठा c_declspecs *build_null_declspecs (व्योम);
बाह्य काष्ठा c_declspecs *declspecs_add_qual (location_t,
					       काष्ठा c_declspecs *, वृक्ष);
बाह्य काष्ठा c_declspecs *declspecs_add_type (location_t,
					       काष्ठा c_declspecs *,
					       काष्ठा c_typespec);
बाह्य काष्ठा c_declspecs *declspecs_add_scspec (location_t,
						 काष्ठा c_declspecs *, वृक्ष);
बाह्य काष्ठा c_declspecs *declspecs_add_attrs (location_t,
						काष्ठा c_declspecs *, वृक्ष);
बाह्य काष्ठा c_declspecs *declspecs_add_addrspace (location_t,
						    काष्ठा c_declspecs *,
						    addr_space_t);
बाह्य काष्ठा c_declspecs *declspecs_add_alignas (location_t,
						  काष्ठा c_declspecs *, वृक्ष);
बाह्य काष्ठा c_declspecs *finish_declspecs (काष्ठा c_declspecs *);
बाह्य माप_प्रकार c_वृक्ष_आकार (क्रमागत वृक्ष_code);
बाह्य पूर्णांक c_get_loop_names (वृक्ष, bool, वृक्ष *);
बाह्य व्योम c_release_loop_names (पूर्णांक);
बाह्य वृक्ष c_finish_bc_name (location_t, वृक्ष, bool);

/* in c-objc-common.cc */
बाह्य bool c_objc_common_init (व्योम);
बाह्य bool c_missing_noreturn_ok_p (वृक्ष);
बाह्य bool c_warn_unused_global_decl (const_वृक्ष);
बाह्य व्योम c_initialize_diagnostics (diagnostics::context *);
बाह्य bool c_var_mod_p (वृक्ष x, वृक्ष fn);
बाह्य alias_set_type c_get_alias_set (वृक्ष);
बाह्य पूर्णांक c_type_dwarf_attribute (const_वृक्ष, पूर्णांक);
बाह्य वृक्ष c_enum_underlying_base_type (const_वृक्ष);

/* in c-typeck.cc */
बाह्य पूर्णांक in_alignof;
बाह्य पूर्णांक in_sizeof;
बाह्य पूर्णांक in_countof;
बाह्य पूर्णांक in_typeof;
बाह्य पूर्णांक in_generic;
बाह्य bool c_in_omp_for;
बाह्य bool c_omp_array_section_p;

बाह्य वृक्ष c_last_sizeof_arg;
बाह्य location_t c_last_sizeof_loc;

बाह्य काष्ठा c_switch *c_switch_ढेर;

बाह्य bool null_pointer_constant_p (const_वृक्ष);


अंतरभूत bool
c_type_variably_modified_p (वृक्ष t)
{
  अगर (error_mark_गाँठ == t)
    वापस false;
  अगर (C_TYPE_VARIABLY_MODIFIED (t))
    वापस true;
  अगर (TYPE_STRUCTURAL_EQUALITY_P (t))
    {
      /* The flag may not have been set yet because of incomplete
	 structure or union types completed later.  */
      चयन (वृक्ष_CODE (t))
	{
	हाल ARRAY_TYPE:
	हाल FUNCTION_TYPE:
	हाल POINTER_TYPE:
	  /* Recurse.  */
	  अगर (c_type_variably_modified_p (वृक्ष_TYPE (t)))
	    {
	      C_TYPE_VARIABLY_MODIFIED (t) = 1;
	      वापस true;
	    }
	  अवरोध;
	शेष:
	  अवरोध;
	}
    }
  वापस false;
}

अंतरभूत bool
c_type_unspecified_p (वृक्ष t)
{
  वापस error_mark_गाँठ != t
	 && C_TYPE_VARIABLE_आकार (t) && वृक्ष_CODE (t) == ARRAY_TYPE
	 && TYPE_DOMAIN (t) && TYPE_MAX_मूल्य (TYPE_DOMAIN (t))
	 && वृक्ष_CODE (TYPE_MAX_मूल्य (TYPE_DOMAIN (t))) == COMPOUND_व्यंजक
	 && integer_zerop (वृक्ष_OPERAND (TYPE_MAX_मूल्य (TYPE_DOMAIN (t)), 0))
	 && integer_zerop (वृक्ष_OPERAND (TYPE_MAX_मूल्य (TYPE_DOMAIN (t)), 1));
}

बाह्य bool zero_लंबाई_array_type_p (const_वृक्ष type);
बाह्य bool char_type_p (वृक्ष);
बाह्य वृक्ष c_type_tag (const_वृक्ष t);
बाह्य वृक्ष c_objc_common_truthvalue_conversion (location_t, वृक्ष,
						 वृक्ष = integer_type_गाँठ);
बाह्य वृक्ष require_complete_type (location_t, वृक्ष);
बाह्य bool same_translation_unit_p (const_वृक्ष, const_वृक्ष);
बाह्य bool comptypes (वृक्ष, वृक्ष);
बाह्य bool comptypes_same_p (वृक्ष, वृक्ष);
बाह्य bool comptypes_equiv_p (वृक्ष, वृक्ष);
बाह्य bool comptypes_check_enum_int (वृक्ष, वृक्ष, bool *);
बाह्य bool c_mark_addressable (वृक्ष, bool = false, bool = false);
बाह्य व्योम c_incomplete_type_error (location_t, const_वृक्ष, const_वृक्ष);
बाह्य वृक्ष c_type_promotes_to (वृक्ष);
बाह्य काष्ठा c_व्यंजक default_function_array_conversion (location_t,
							काष्ठा c_व्यंजक);
बाह्य काष्ठा c_व्यंजक default_function_array_read_conversion (location_t,
							     काष्ठा c_व्यंजक);
बाह्य काष्ठा c_व्यंजक convert_lvalue_to_rvalue (location_t, काष्ठा c_व्यंजक,
					       bool, bool, bool = false);
बाह्य वृक्ष decl_constant_मूल्य_1 (वृक्ष, bool);
बाह्य व्योम mark_exp_read (वृक्ष);
बाह्य वृक्ष composite_type (वृक्ष, वृक्ष);
बाह्य वृक्ष lookup_field (const_वृक्ष, वृक्ष);
बाह्य वृक्ष build_component_ref (location_t, वृक्ष, वृक्ष, location_t,
				 location_t);
बाह्य वृक्ष handle_counted_by_for_component_ref (location_t, वृक्ष);
बाह्य वृक्ष build_array_ref (location_t, वृक्ष, वृक्ष);
बाह्य वृक्ष build_omp_array_section (location_t, वृक्ष, वृक्ष, वृक्ष);
बाह्य वृक्ष build_external_ref (location_t, वृक्ष, bool, वृक्ष *);
बाह्य व्योम निकालो_maybe_used (bool);
बाह्य काष्ठा maybe_used_decl *save_maybe_used ();
बाह्य व्योम restore_maybe_used (काष्ठा maybe_used_decl *);
बाह्य व्योम mark_decl_used (वृक्ष, bool);
बाह्य काष्ठा c_व्यंजक c_व्यंजक_sizeof_व्यंजक (location_t, काष्ठा c_व्यंजक);
बाह्य काष्ठा c_व्यंजक c_व्यंजक_sizeof_type (location_t, काष्ठा c_type_name *);
बाह्य काष्ठा c_व्यंजक c_व्यंजक_countof_व्यंजक (location_t, काष्ठा c_व्यंजक);
बाह्य काष्ठा c_व्यंजक c_व्यंजक_countof_type (location_t loc,
					  काष्ठा c_type_name *);
बाह्य काष्ठा c_व्यंजक c_व्यंजक_maxof_type (location_t loc, काष्ठा c_type_name *);
बाह्य काष्ठा c_व्यंजक c_व्यंजक_minof_type (location_t loc, काष्ठा c_type_name *);
बाह्य काष्ठा c_व्यंजक parser_build_unary_op (location_t, क्रमागत वृक्ष_code,
    					    काष्ठा c_व्यंजक);
बाह्य काष्ठा c_व्यंजक parser_build_द्विआधारी_op (location_t,
    					     क्रमागत वृक्ष_code, काष्ठा c_व्यंजक,
					     काष्ठा c_व्यंजक, वृक्ष);
बाह्य वृक्ष build_conditional_व्यंजक (location_t, वृक्ष, bool, वृक्ष, वृक्ष,
				    location_t, वृक्ष, वृक्ष, location_t);
बाह्य वृक्ष build_compound_व्यंजक (location_t, वृक्ष, वृक्ष);
बाह्य वृक्ष c_cast_व्यंजक (location_t, काष्ठा c_type_name *, वृक्ष);
बाह्य वृक्ष build_c_cast (location_t, वृक्ष, वृक्ष);
बाह्य व्योम store_init_मूल्य (location_t, वृक्ष, वृक्ष, वृक्ष);
बाह्य व्योम maybe_warn_string_init (location_t, वृक्ष, काष्ठा c_व्यंजक);
बाह्य व्योम start_init (वृक्ष, वृक्ष, bool, bool, rich_location *);
बाह्य व्योम finish_init (व्योम);
बाह्य व्योम really_start_incremental_init (वृक्ष);
बाह्य व्योम finish_implicit_inits (location_t, काष्ठा obstack *);
बाह्य व्योम धकेलो_init_level (location_t, पूर्णांक, काष्ठा obstack *);
बाह्य काष्ठा c_व्यंजक निकालो_init_level (location_t, पूर्णांक, काष्ठा obstack *,
				     location_t);
बाह्य व्योम set_init_सूचकांक (location_t, वृक्ष, वृक्ष, काष्ठा obstack *);
बाह्य व्योम set_init_label (location_t, वृक्ष, location_t, काष्ठा obstack *);
अचिन्हित c_maybe_optimize_large_byte_initializer (व्योम);
बाह्य व्योम process_init_element (location_t, काष्ठा c_व्यंजक, bool,
				  काष्ठा obstack *);
बाह्य वृक्ष build_compound_literal (location_t, वृक्ष, वृक्ष, bool,
				    अचिन्हित पूर्णांक, काष्ठा c_declspecs *);
बाह्य व्योम check_compound_literal_type (location_t, काष्ठा c_type_name *);
बाह्य वृक्ष c_start_switch (location_t, location_t, वृक्ष, bool, वृक्ष);
बाह्य व्योम c_finish_switch (वृक्ष, वृक्ष);
बाह्य वृक्ष build_asm_व्यंजक (location_t, वृक्ष, वृक्ष, वृक्ष, वृक्ष, वृक्ष, bool,
			    bool);
बाह्य वृक्ष build_asm_stmt (bool, वृक्ष);
बाह्य पूर्णांक c_types_compatible_p (वृक्ष, वृक्ष);
बाह्य वृक्ष c_begin_compound_stmt (bool);
बाह्य वृक्ष c_end_compound_stmt (location_t, वृक्ष, bool);
बाह्य व्योम c_finish_if_stmt (location_t, वृक्ष, वृक्ष, वृक्ष);
बाह्य व्योम c_finish_loop (location_t, location_t, वृक्ष, location_t, वृक्ष,
			   वृक्ष, वृक्ष, वृक्ष, bool);
बाह्य वृक्ष c_begin_stmt_व्यंजक (व्योम);
बाह्य वृक्ष c_finish_stmt_व्यंजक (location_t, वृक्ष);
बाह्य वृक्ष c_process_व्यंजक_stmt (location_t, वृक्ष);
बाह्य वृक्ष c_finish_व्यंजक_stmt (location_t, वृक्ष);
बाह्य वृक्ष c_finish_return (location_t, वृक्ष, वृक्ष, bool = false);
बाह्य वृक्ष c_finish_bc_stmt (location_t, वृक्ष, bool, वृक्ष);
बाह्य वृक्ष c_finish_goto_label (location_t, वृक्ष);
बाह्य वृक्ष c_finish_goto_ptr (location_t, c_व्यंजक val);
बाह्य वृक्ष c_व्यंजक_to_decl (वृक्ष, bool *, bool *);
बाह्य वृक्ष c_finish_omp_construct (location_t, क्रमागत वृक्ष_code, वृक्ष, वृक्ष);
बाह्य वृक्ष c_finish_oacc_तथ्य (location_t, वृक्ष, वृक्ष);
बाह्य वृक्ष c_finish_oacc_host_तथ्य (location_t, वृक्ष, वृक्ष);
बाह्य वृक्ष c_begin_omp_parallel (व्योम);
बाह्य वृक्ष c_finish_omp_parallel (location_t, वृक्ष, वृक्ष);
बाह्य वृक्ष c_begin_omp_task (व्योम);
बाह्य वृक्ष c_finish_omp_task (location_t, वृक्ष, वृक्ष);
बाह्य व्योम c_finish_omp_cancel (location_t, वृक्ष);
बाह्य व्योम c_finish_omp_cancellation_point (location_t, वृक्ष);
बाह्य वृक्ष c_finish_omp_clauses (वृक्ष, क्रमागत c_omp_region_type);
बाह्य वृक्ष c_omp_finish_mapper_clauses (वृक्ष);
बाह्य वृक्ष c_omp_mapper_lookup (वृक्ष, वृक्ष);
बाह्य वृक्ष c_omp_extract_mapper_directive (वृक्ष);
बाह्य वृक्ष c_omp_map_array_section (location_t, वृक्ष);
बाह्य वृक्ष c_build_va_arg (location_t, वृक्ष, location_t, वृक्ष, वृक्ष);
बाह्य वृक्ष c_finish_transaction (location_t, वृक्ष, पूर्णांक);
बाह्य bool c_वृक्ष_equal (वृक्ष, वृक्ष);
बाह्य वृक्ष c_build_function_call_vec (location_t, स्थिर vec<location_t>&,
				       वृक्ष, vec<वृक्ष, va_gc> *,
				       vec<वृक्ष, va_gc> *);
बाह्य वृक्ष c_omp_clause_copy_ctor (वृक्ष, वृक्ष, वृक्ष);
बाह्य वृक्ष c_reconstruct_complex_type (वृक्ष, वृक्ष);
बाह्य वृक्ष c_type_canonical (वृक्ष);
बाह्य वृक्ष c_build_type_attribute_variant (वृक्ष ntype, वृक्ष attrs);
बाह्य वृक्ष c_build_pointer_type (वृक्ष type);
बाह्य वृक्ष c_build_array_type (वृक्ष type, वृक्ष domain);
बाह्य वृक्ष c_build_array_type_unspecified (वृक्ष type);
बाह्य वृक्ष c_build_array_type_zero_आकार (वृक्ष type);
बाह्य वृक्ष c_build_function_type (वृक्ष type, वृक्ष args, bool no = false);
बाह्य वृक्ष c_build_pointer_type_for_mode (वृक्ष type, machine_mode mode, bool m);

/* Set to 0 at beginning of a function definition, set to 1 if
   a return statement that specifies a return value is seen.  */

बाह्य पूर्णांक current_function_returns_मूल्य;

/* Set to 0 at beginning of a function definition, set to 1 if
   a return statement with no argument is seen.  */

बाह्य पूर्णांक current_function_returns_null;

/* Set to 0 at beginning of a function definition, set to 1 if
   a call to a noreturn function is seen.  */

बाह्य पूर्णांक current_function_returns_abnormally;

/* In c-decl.cc */

/* Tell the binding oracle what kind of binding we are looking for.  */

क्रमागत c_oracle_request
{
  C_ORACLE_प्रतीक,
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

प्रकार व्योम c_binding_oracle_function (क्रमागत c_oracle_request, वृक्ष identifier);

बाह्य c_binding_oracle_function *c_binding_oracle;

बाह्य व्योम c_finish_incomplete_decl (वृक्ष);
बाह्य वृक्ष c_omp_reduction_id (क्रमागत वृक्ष_code, वृक्ष);
बाह्य वृक्ष c_omp_reduction_decl (वृक्ष);
बाह्य वृक्ष c_omp_reduction_lookup (वृक्ष, वृक्ष);
बाह्य वृक्ष c_check_omp_declare_reduction_r (वृक्ष *, पूर्णांक *, व्योम *);
बाह्य वृक्ष c_omp_mapper_id (वृक्ष);
बाह्य वृक्ष c_omp_mapper_decl (वृक्ष);
बाह्य व्योम c_omp_scan_mapper_bindings (location_t, वृक्ष *, वृक्ष);
बाह्य bool c_check_in_current_scope (वृक्ष);
बाह्य व्योम c_pushtag (location_t, वृक्ष, वृक्ष);
बाह्य व्योम c_bind (location_t, वृक्ष, bool);
बाह्य bool tag_exists_p (क्रमागत वृक्ष_code, वृक्ष);

बाह्य व्योम verify_counted_by_for_शीर्ष_anonymous_type (वृक्ष);

/* In c-errors.cc */
बाह्य bool pedwarn_c90 (location_t, diagnostics::option_id, स्थिर अक्षर *, ...)
    ATTRIBUTE_GCC_DIAG(3,4);
बाह्य bool pedwarn_c99 (location_t, diagnostics::option_id, स्थिर अक्षर *, ...)
    ATTRIBUTE_GCC_DIAG(3,4);
बाह्य bool pedwarn_c11 (location_t, diagnostics::option_id, स्थिर अक्षर *, ...)
    ATTRIBUTE_GCC_DIAG(3,4);
बाह्य bool pedwarn_c23 (location_t, diagnostics::option_id, स्थिर अक्षर *, ...)
    ATTRIBUTE_GCC_DIAG(3,4);
बाह्य व्योम add_note_about_new_keyword (location_t loc,
					वृक्ष keyword_id);

बाह्य व्योम
set_c_व्यंजक_source_range (c_व्यंजक *व्यंजक,
			 location_t start, location_t finish);

बाह्य व्योम
set_c_व्यंजक_source_range (c_व्यंजक *व्यंजक,
			 source_range src_range);

/* In c-fold.cc */
बाह्य vec<वृक्ष> incomplete_record_decls;

बाह्य स्थिर अक्षर *c_get_sarif_source_language (स्थिर अक्षर *filename);

बाह्य स्थिर काष्ठा scoped_attribute_specs std_attribute_table;

#अगर CHECKING_P
namespace selftest {
  बाह्य व्योम run_c_tests (व्योम);
} // namespace selftest
#पूर्ण_अगर /* #if CHECKING_P */


#पूर्ण_अगर /* ! GCC_C_TREE_H */
